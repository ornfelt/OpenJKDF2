//====== Copyright Valve Corporation, All rights reserved. ====================

#ifndef STEAMNETWORKINGSOCKETS_CONNECTIONS_H
#define STEAMNETWORKINGSOCKETS_CONNECTIONS_H
#pragma once

#include "../steamnetworkingsockets_internal.h"
#ifndef STEAMNETWORKINGSOCKETS_OPENSOURCE
#include "../steamdatagram_internal.h"
#include <steam/steamdatagram_tickets.h>
#endif
#include "../steamnetworking_statsutils.h"
#include <tier1/utlhashmap.h>
#include "steamnetworkingsockets_lowlevel.h"
#include "../steamnetworkingsockets_thinker.h"
#include "keypair.h"
#include "crypto.h"
#include "crypto_25519.h"
#include <tier0/memdbgoff.h>
#include <steamnetworkingsockets_messages.pb.h>
#include <tier0/memdbgon.h>

#include "steamnetworkingsockets_snp.h"

struct SteamNetConnectionStatusChangedCallback_t;
class ISteamNetworkingSocketsSerialized;
class CGameNetworkingUI_ConnectionState;

namespace SteamNetworkingSocketsLib {

const SteamNetworkingMicroseconds k_usecConnectRetryInterval = k_nMillion/2;
const SteamNetworkingMicroseconds k_usecFinWaitTimeout = 5*k_nMillion;

typedef char ConnectionEndDebugMsg[ k_cchSteamNetworkingMaxConnectionCloseReason ];

// Connection-type-specific info of the connection description.
typedef char ConnectionTypeDescription_t[80];

class CSteamNetworkingSockets;
class CSteamNetworkingMessages;
class CSteamNetworkConnectionBase;
class CSteamNetworkConnectionP2P;
class CSharedSocket;
class CConnectionTransport;
struct SNPPacketSerializeHelper;
struct SNPEncodedSegment;
struct CertAuthScope;
class CMessagesEndPoint;
class CMessagesEndPointSession;
template<bool k_bUnreliableOnly, bool k_bSingleLane> struct SNPSegmentCollector;

enum EUnsignedCert
{
	k_EUnsignedCert_Disallow,
	k_EUnsignedCert_AllowWarn,
	k_EUnsignedCert_Allow,
};

// Fixed size byte array that automatically wipes itself upon destruction.
// Used for storage of secret keys, etc.
template <int N>
class AutoWipeFixedSizeBuffer
{
public:
	enum { k_nSize = N };
	uint8 m_buf[ N ];

	// You can wipe before destruction if you want
	inline void Wipe() { SecureZeroMemory( m_buf, N ); }

	// Wipe on destruction
	inline ~AutoWipeFixedSizeBuffer() { Wipe(); }
};

/// In various places, we need a key in a map of remote connections.
struct RemoteConnectionKey_t
{
	SteamNetworkingIdentity m_identity;
	uint32 m_unConnectionID;

	// NOTE: If we assume that peers are well behaved, then we
	// could just use the connection ID, which is a random number.
	// but let's not assume that.  In fact, if we really need to
	// protect against malicious clients we might have to include
	// some random private data so that they don't know how our hash
	// function works.  We'll assume for now that this isn't a problem
	struct Hash { uint32 operator()( const RemoteConnectionKey_t &x ) const { return SteamNetworkingIdentityHash{}( x.m_identity ) ^ x.m_unConnectionID; } };
	inline bool operator ==( const RemoteConnectionKey_t &x ) const
	{
		return m_unConnectionID == x.m_unConnectionID && m_identity == x.m_identity;
	}
};

/// Base class for connection-type-specific context structure 
struct SendPacketContext_t
{
	inline SendPacketContext_t( SteamNetworkingMicroseconds usecNow, const char *pszReason ) : m_usecNow( usecNow ), m_pszReason( pszReason ) {}
	const SteamNetworkingMicroseconds m_usecNow;
	int m_cbMaxEncryptedPayload;
	const char *m_pszReason; // Why are we sending this packet?
};

/// Context used when receiving a data packet
struct RecvPacketContext_t
{

//
// Must be filled in by transport
//

	/// Current time
	SteamNetworkingMicroseconds m_usecNow;

	/// What transport is receiving this packet?
	CConnectionTransport *m_pTransport;

	/// Jitter measurement, if present
	//int m_usecTimeSinceLast;

	/// For dual path, is this the primary or secondary path?
	int m_idxMultiPath = 0;

//
// Output of DecryptDataChunk
//

	/// Expanded packet number
	int64 m_nPktNum;

	/// Pointer to decrypted data.  Will either point to to the caller's original packet,
	/// if the packet was not encrypted, or m_decrypted, if it was encrypted and we
	/// decrypted it
	const void *m_pPlainText;

	/// Size of plaintext
	int m_cbPlainText;

	// Temporary buffer to hold decrypted data, if we were actually encrypted
	uint8 m_decrypted[ k_cbSteamNetworkingSocketsMaxPlaintextPayloadRecv ];
};

template<typename TStatsMsg>
struct SendPacketContext : SendPacketContext_t
{
	inline SendPacketContext( SteamNetworkingMicroseconds usecNow, const char *pszReason ) : SendPacketContext_t( usecNow, pszReason ) {}

	uint32 m_nFlags; // Message flags that we need to set.
	TStatsMsg msg; // Type-specific stats message
	int m_cbMsgSize; // Size of message
	int m_cbTotalSize; // Size needed in the header, including the serialized size field

	void SlamFlagsAndCalcSize()
	{
		SetStatsMsgFlagsIfNotImplied( msg, m_nFlags );
		m_cbTotalSize = m_cbMsgSize = ProtoMsgByteSize( msg );
		if ( m_cbMsgSize > 0 )
			m_cbTotalSize += VarIntSerializedSize( (uint32)m_cbMsgSize );
	}

	bool Serialize( byte *&p )
	{
		if ( m_cbTotalSize <= 0 )
			return false;

		// Serialize the stats size, var-int encoded
		byte *pOut = SerializeVarInt( p, uint32( m_cbMsgSize ) );

		// Serialize the actual message
		pOut = msg.SerializeWithCachedSizesToArray( pOut );

		// Make sure we wrote the number of bytes we expected
		if ( pOut != p + m_cbTotalSize )
		{
			// ABORT!
			AssertMsg( false, "Size mismatch after serializing inline stats blob" );
			return false;
		}

		// Advance pointer
		p = pOut;
		return true;
	}

	void CalcMaxEncryptedPayloadSize( size_t cbHdrReserve, CSteamNetworkConnectionBase *pConnection );
};

/// Replace internal states that are not visible outside of the API with
/// the corresponding state that we show the the application.
inline ESteamNetworkingConnectionState CollapseConnectionStateToAPIState( ESteamNetworkingConnectionState eState )
{
	// All the hidden internal states are assigned negative values
	if ( eState < 0 )
		return k_ESteamNetworkingConnectionState_None;
	return eState;
}

/// We use one global lock to protect all queues of
/// received messages.  (On connections and poll groups!)
extern ShortDurationLock g_lockAllRecvMessageQueues;

#ifdef STEAMNETWORKINGSOCKETS_ENABLE_FAKEIP

struct FakeIPKey;

// Struct that holds a reference, so that we don't forget about FakeIPs that are actually in use
struct FakeIPReference
{
	~FakeIPReference() { Clear(); }

	/// Return true if we are in use
	inline bool IsValid() const { return m_nHandle >= 0; }

	/// If we hold a reference, clear it
	void Clear();

	/// Setup to hold a reference to the given FakeIP.  Returns false if we don't
	/// know who is on the other end of that identity
	bool Lookup( const SteamNetworkingIPAddr &addr );

	/// Setup to hold a reference to the given FakeIP and the known remote identity
	void Setup( const SteamNetworkingIPAddr &addr, const SteamNetworkingIdentity &identity );

	/// Allocate a new local FakeIP for the given identity.  Returns false if we fail (which should
	/// really never happen)
	bool SetupNewLocalIP( const SteamNetworkingIdentity &identity, SteamNetworkingIPAddr *pOutLocalFakeIP );

	/// Get the real identity and/or fake IP.  Returns false if we do not hold a reference
	bool GetInfo( SteamNetworkingIdentity *pOutIdentity, SteamNetworkingIPAddr *pOutFakeIP ) const;

private:
	void InsertInternal( const FakeIPKey &key, const SteamNetworkingIdentity &identity );
	void AddRefInternal( int handle, const SteamNetworkingIdentity *pIdentity );

	int m_nHandle = -1;
};

#endif // #ifdef STEAMNETWORKINGSOCKETS_ENABLE_FAKEIP

/////////////////////////////////////////////////////////////////////////////
//
// CSteamNetworkPollGroup
//
/////////////////////////////////////////////////////////////////////////////

class CSteamNetworkPollGroup;
struct PollGroupLock : Lock<RecursiveTimedMutexImpl> {
	PollGroupLock() : Lock<RecursiveTimedMutexImpl>( "pollgroup", LockDebugInfo::k_nFlag_PollGroup ) {}
};
using PollGroupScopeLock = ScopeLock<PollGroupLock>;

class CSteamNetworkPollGroup
{
public:
	CSteamNetworkPollGroup( CSteamNetworkingSockets *pInterface );
	~CSteamNetworkPollGroup();

	PollGroupLock m_lock;

	/// What interface is responsible for this listen socket?
	CSteamNetworkingSockets *const m_pSteamNetworkingSocketsInterface;

	/// Linked list of messages received through any connection on this listen socket
	SteamNetworkingMessageQueue m_queueRecvMessages;

	/// Index into the global list
	HSteamNetPollGroup m_hPollGroupSelf;

	/// List of connections that are in this poll group
	CUtlVector<CSteamNetworkConnectionBase *> m_vecConnections;

	void AssignHandleAndAddToGlobalTable();
};

/////////////////////////////////////////////////////////////////////////////
//
// CSteamNetworkListenSocketBase
//
/////////////////////////////////////////////////////////////////////////////

/// Abstract base class for a listen socket that can accept connections.
class CSteamNetworkListenSocketBase
{
public:

	/// Destroy the listen socket, and all of its accepted connections
	virtual void Destroy();

	/// Called when we receive a connection attempt, to setup the linkage.
	bool BAddChildConnection( CSteamNetworkConnectionBase *pConn, SteamNetworkingErrMsg &errMsg );

	/// This gets called on an accepted connection before it gets destroyed
	virtual void AboutToDestroyChildConnection( CSteamNetworkConnectionBase *pConn );

	virtual bool APIGetAddress( SteamNetworkingIPAddr *pAddress );

	/// Map of child connections
	CUtlHashMap<RemoteConnectionKey_t, CSteamNetworkConnectionBase *, std::equal_to<RemoteConnectionKey_t>, RemoteConnectionKey_t::Hash > m_mapChildConnections;

	/// Index into the global list
	HSteamListenSocket m_hListenSocketSelf;

	/// What interface is responsible for this listen socket?
	CSteamNetworkingSockets *const m_pSteamNetworkingSocketsInterface;

	/// Configuration options that will apply to all connections accepted through this listen socket
	ConnectionConfig m_connectionConfig;

	/// Symmetric mode
	inline bool BSymmetricMode() const { return m_connectionConfig.m_SymmetricConnect.Get() != 0; }
	virtual bool BSupportsSymmetricMode();

	// Some listen sockets are used by ad-hoc style messages endpoints
	#ifdef STEAMNETWORKINGSOCKETS_ENABLE_STEAMNETWORKINGMESSAGES
	CMessagesEndPoint *m_pMessagesEndPointOwner = nullptr;
	#else
	static constexpr CMessagesEndPoint *m_pMessagesEndPointOwner = nullptr;
	#endif

	/// For legacy interface.
	#ifdef STEAMNETWORKINGSOCKETS_STEAMCLIENT
	std::unique_ptr<CSteamNetworkPollGroup> m_pLegacyPollGroup;
	#endif

protected:
	CSteamNetworkListenSocketBase( CSteamNetworkingSockets *pSteamNetworkingSocketsInterface );
	virtual ~CSteamNetworkListenSocketBase(); // hidden destructor, don't call directly.  Use Destroy()

	bool BInitListenSocketCommon( int nOptions, const SteamNetworkingConfigValue_t *pOptions, SteamDatagramErrMsg &errMsg );
};

/////////////////////////////////////////////////////////////////////////////
//
// CSteamNetworkConnectionBase
//
/////////////////////////////////////////////////////////////////////////////

struct ConnectionLock : Lock<RecursiveTimedMutexImpl> {
	ConnectionLock() : Lock<RecursiveTimedMutexImpl>( "connection", LockDebugInfo::k_nFlag_Connection ) {}
};
struct ConnectionScopeLock : ScopeLock<ConnectionLock>
{
	ConnectionScopeLock() = default;
	ConnectionScopeLock( ConnectionLock &lock, const char *pszTag = nullptr ) : ScopeLock<ConnectionLock>( lock, pszTag ) {}
	ConnectionScopeLock( CSteamNetworkConnectionBase &conn, const char *pszTag = nullptr );
	void Lock( ConnectionLock &lock, const char *pszTag = nullptr ) { ScopeLock<ConnectionLock>::Lock( lock, pszTag ); }
	void Lock( CSteamNetworkConnectionBase &conn, const char *pszTag = nullptr );
};

/// Abstract interface for a connection to a remote host over any underlying
/// transport.  Most of the common functionality for implementing reliable
/// connections on top of unreliable datagrams, connection quality measurement,
/// etc is implemented here. 
class CSteamNetworkConnectionBase : public ILockableThinker< ConnectionLock >
{
public:

//
// API entry points
//

	/// Called when we close the connection locally
	void APICloseConnection( int nReason, const char *pszDebug, bool bEnableLinger );

	/// Send a message
	EResult APISendMessageToConnection( const void *pData, uint32 cbData, int nSendFlags, int64 *pOutMessageNumber );

	/// Send a message.  Returns the assigned message number, or a negative EResult value
	int64 APISendMessageToConnection( CSteamNetworkingMessage *pMsg, SteamNetworkingMicroseconds usecNow, bool *pbThinkImmediately = nullptr );

	/// Flush any messages queued for Nagle
	EResult APIFlushMessageOnConnection();

	/// Receive the next message(s)
	int APIReceiveMessages( SteamNetworkingMessage_t **ppOutMessages, int nMaxMessages );

	/// Accept a connection.  This will involve sending a message
	/// to the client, and calling ConnectionState_Connected on the connection
	/// to transition it to the connected state.
	EResult APIAcceptConnection();
	virtual EResult AcceptConnection( SteamNetworkingMicroseconds usecNow );

	/// Fill in realtime connection stats
	EResult APIGetRealTimeStatus( SteamNetConnectionRealTimeStatus_t *pStatus, int nLanes, SteamNetConnectionRealTimeLaneStatus_t *pLanes );

	/// Fill in detailed connection stats
	virtual void APIGetDetailedConnectionStatus( SteamNetworkingDetailedConnectionStatus &stats, SteamNetworkingMicroseconds usecNow );

	/// Hook to allow connections to customize message sending.
	/// (E.g. loopback.)
	virtual int64 _APISendMessageToConnection( CSteamNetworkingMessage *pMsg, SteamNetworkingMicroseconds usecNow, bool *pbThinkImmediately );

//
// Accessor
//

	// Get/set user data
	inline int64 GetUserData() const
	{
		// User data is locked when we create a connection!
		Assert( m_connectionConfig.m_ConnectionUserData.IsSet() );
		return m_connectionConfig.m_ConnectionUserData.m_data;
	}
	void SetUserData( int64 nUserData );

	// Get/set name
	inline const char *GetAppName() const { return m_szAppName; }
	void SetAppName( const char *pszName );

	// Debug description
	inline const char *GetDescription() const { return m_szDescription; }

	/// When something changes that goes into the description, call this to rebuild the description
	void SetDescription();

	/// High level state of the connection
	ESteamNetworkingConnectionState GetState() const { return m_eConnectionState; }
	ESteamNetworkingConnectionState GetWireState() const { return m_eConnectionWireState; }

	/// Check if the connection is 'connected' from the perspective of the wire protocol.
	/// (The wire protocol doesn't care about local states such as linger)
	bool BStateIsConnectedForWirePurposes() const { return m_eConnectionWireState == k_ESteamNetworkingConnectionState_Connected; }

	/// Return true if the connection is still "active" in some way.
	bool BStateIsActive() const
	{
		return
			m_eConnectionWireState == k_ESteamNetworkingConnectionState_Connecting
			|| m_eConnectionWireState == k_ESteamNetworkingConnectionState_FindingRoute
			|| m_eConnectionWireState == k_ESteamNetworkingConnectionState_Connected;
	}

	/// Reason connection ended
	ESteamNetConnectionEnd GetConnectionEndReason() const { return m_eEndReason; }
	const char *GetConnectionEndDebugString() const { return m_szEndDebug; }

	/// When did we enter the current state?
	inline SteamNetworkingMicroseconds GetTimeEnteredConnectionState() const { return m_usecWhenEnteredConnectionState; }

	/// Fill in connection details
	void ConnectionPopulateInfo( SteamNetConnectionInfo_t &info ) const;

//
// Lifetime management
//

	/// Schedule destruction at the next possible opportunity
	void ConnectionQueueDestroy();
	static void ProcessDeletionList();

	/// Free up all resources.  Close sockets, etc
	virtual void FreeResources();

	/// Nuke all transports
	virtual void DestroyTransport();

//
// Connection state machine
// Functions to transition to the specified state.
//

	void ConnectionState_ProblemDetectedLocally( ESteamNetConnectionEnd eReason, PRINTF_FORMAT_STRING const char *pszFmt, ... ) FMTFUNCTION( 3, 4 );
	void ConnectionState_ClosedByPeer( int nReason, const char *pszDebug );
	void ConnectionState_FindingRoute( SteamNetworkingMicroseconds usecNow );
	bool BConnectionState_Connecting( SteamNetworkingMicroseconds usecNow, SteamNetworkingErrMsg &errMsg );
	void ConnectionState_Connected( SteamNetworkingMicroseconds usecNow );
	void ConnectionState_FinWait();

//
// Misc internal stuff
//

	/// What interface is responsible for this connection?
	CSteamNetworkingSockets *const m_pSteamNetworkingSocketsInterface;

	/// Current active transport for this connection.
	/// MIGHT BE NULL in certain failure / edge cases!
	/// Might change during the connection lifetime.
	CConnectionTransport *m_pTransport;

	/// Our public handle
	HSteamNetConnection m_hConnectionSelf;

	/// Who is on the other end?  This might be invalid if we don't know yet.  (E.g. direct UDP connections.)
	SteamNetworkingIdentity m_identityRemote;

	/// Who are we?
	SteamNetworkingIdentity m_identityLocal;

	/// The listen socket through which we were accepted, if any.
	CSteamNetworkListenSocketBase *m_pParentListenSocket;

	/// What poll group are we assigned to?
	CSteamNetworkPollGroup *m_pPollGroup;

	/// Assign poll group
	void SetPollGroup( CSteamNetworkPollGroup *pPollGroup );

	/// Remove us from the poll group we are in (if any)
	void RemoveFromPollGroup();

	/// Was this connection initiated locally (we are the "client") or remotely (we are the "server")?
	/// In *most* use cases, "server" connections have a listen socket, but not always.
	bool m_bConnectionInitiatedRemotely;

	/// Our handle in our parent's m_listAcceptedConnections (if we were accepted on a listen socket)
	int m_hSelfInParentListenSocketMap;

	// Linked list of received messages
	SteamNetworkingMessageQueue m_queueRecvMessages;

	/// The unique 64-bit end-to-end connection ID.  Each side picks 32 bits
	uint32 m_unConnectionIDLocal;
	uint32 m_unConnectionIDRemote;

	/// Track end-to-end stats for this connection.
	LinkStatsTracker<LinkStatsTrackerEndToEnd> m_statsEndToEnd;

	/// When we accept a connection, they will send us a timestamp we should send back
	/// to them, so that they can estimate the ping
	uint64 m_ulHandshakeRemoteTimestamp;
	SteamNetworkingMicroseconds m_usecWhenReceivedHandshakeRemoteTimestamp;

	/// Connection configuration
	ConnectionConfig m_connectionConfig;

	/// The reason code for why the connection was closed.
	ESteamNetConnectionEnd m_eEndReason;
	ConnectionEndDebugMsg m_szEndDebug;

	/// MTU values for this connection
	int m_cbMTUPacketSize = 0;
	int m_cbMaxPlaintextPayloadSend = 0;
	int m_cbMaxMessageNoFragment = 0;
	int m_cbMaxReliableMessageSegment = 0;
	int m_cbEncryptionOverhead = 0;

	void UpdateMTUFromConfig( bool bForceRecalc );

	/// Handy accessor to the local virtual port configuration option, which is used
	/// a lot by P2P connections.
	inline int LocalVirtualPort() const { return m_connectionConfig.m_LocalVirtualPort.Get(); }

	// Each connection is protected by a lock.  The actual lock to use is IThinker::m_pLock.
	// Almost all connections use this default lock.  (A few special cases use a different lock
	// so that they are locked at the same time as other objects.)
	ConnectionLock m_defaultLock;

	/// Make sure the global lock and this lock are both held
	/// by the current thread.  Don't call this directly, use
	/// the AssertLocksHeldByCurrentThread macro to provide
	/// the file and line number.
	void _AssertLocksHeldByCurrentThread( const char *pszFile, int line, const char *pszTag = nullptr ) const
	{
		SteamNetworkingGlobalLock::_AssertHeldByCurrentThread( pszFile, line, pszTag );
		m_pLock->_AssertHeldByCurrentThread( pszFile, line );
	}

	/// Expand the packet number, and decrypt the data chunk.
	/// Returns true if everything is OK and we should continue
	/// processing the packet
	bool DecryptDataChunk( uint16 nWireSeqNum, int cbPacketSize, const void *pChunk, int cbChunk, RecvPacketContext_t &ctx );

	/// Decode the plaintext.  Returns false if the packet seems corrupt or bogus, or should abort further
	/// processing.
	bool ProcessPlainTextDataChunk( int usecTimeSinceLast, RecvPacketContext_t &ctx );

	/// Called when we receive an (end-to-end) packet with a sequence number
	void RecvNonDataSequencedPacket( int64 nPktNum, SteamNetworkingMicroseconds usecNow );

	// Called from SNP to update transmit/receive speeds
	void UpdateSpeeds( int nTXSpeed, int nRXSpeed );

	/// Called when the async process to request a cert has failed.
	void CertRequestFailed( ESteamNetConnectionEnd nConnectionEndReason, const char *pszMsg );
	bool BHasLocalCert() const { return m_msgSignedCertLocal.has_cert(); }
	void SetLocalCert( const CMsgSteamDatagramCertificateSigned &msgSignedCert, const CECSigningPrivateKey &keyPrivate, bool bCertHasIdentity );
	void InterfaceGotCert();

	bool SNP_BHasAnyBufferedRecvData() const;
	bool SNP_BHasAnyUnackedSentReliableData() const
	{
		return m_senderState.m_cbPendingReliable > 0 || m_senderState.m_cbSentUnackedReliable > 0;
	}

	/// Return true if we have any reason to send a packet.  This doesn't mean we have the bandwidth
	/// to send it now, it just means we would like to send something ASAP
	inline bool SNP_WantsToSendPacket() const
	{
		return m_receiverState.TimeWhenFlushAcks() < INT64_MAX || SNP_TimeWhenWantToSendNextPacket() < INT64_MAX;
	}

	inline int SNP_PendingUnreliable() const { return m_senderState.m_cbPendingUnreliable; }

	/// Send a data packet now, even if we don't have the bandwidth available.  Returns true if a packet was
	/// sent successfully, false if there was a problem.  This will call SendEncryptedDataChunk to do the work
	bool SNP_SendPacket( CConnectionTransport *pTransport, SendPacketContext_t &ctx );

	/// Record that we sent a non-data packet.  This is so that if the peer acks,
	/// we can record it as a ping
	void SNP_SentNonDataPacket( CConnectionTransport *pTransport, int cbPkt, SteamNetworkingMicroseconds usecNow );

	/// Called after the connection state changes.  Default behavior is to notify
	/// the active transport, if any
	virtual void ConnectionStateChanged( ESteamNetworkingConnectionState eOldState );

	/// Called to post a callback
	int m_nSupressStateChangeCallbacks;
	void PostConnectionStateChangedCallback( ESteamNetworkingConnectionState eOldAPIState, ESteamNetworkingConnectionState eNewAPIState );

	void QueueEndToEndAck( bool bImmediate, SteamNetworkingMicroseconds usecNow )
	{
		if ( bImmediate )
		{
			SNP_DebugCheckPacketGapMapSentinel();
			m_receiverState.QueueFlushAllAcks( k_nThinkTime_ASAP );
			SetNextThinkTimeASAP();
		}
		else
		{
			QueueFlushAllAcks( usecNow + k_usecMaxDataAckDelay );
		}
	}

	void QueueFlushAllAcks( SteamNetworkingMicroseconds usecWhen )
	{
		SNP_DebugCheckPacketGapMapSentinel();
		m_receiverState.QueueFlushAllAcks( usecWhen );
		EnsureMinThinkTime( m_receiverState.TimeWhenFlushAcks() );
	}

	inline const CMsgSteamDatagramSessionCryptInfoSigned &GetSignedCryptLocal() { return m_msgSignedCryptLocal; }
	inline const CMsgSteamDatagramCertificateSigned &GetSignedCertLocal() { return m_msgSignedCertLocal; }
	inline bool BCertHasIdentity() const { return m_bCertHasIdentity; }
	inline bool BCryptKeysValid() const { return m_bCryptKeysValid; }

	/// Called when we send an end-to-end connect request
	void SentEndToEndConnectRequest( SteamNetworkingMicroseconds usecNow )
	{

		// Reset timeout/retry for this reply.  But if it fails, we'll start
		// the whole handshake over again.  It keeps the code simpler, and the
		// challenge value has a relatively short expiry anyway.
		m_usecWhenSentConnectRequest = usecNow;
		EnsureMinThinkTime( usecNow + k_usecConnectRetryInterval );
	}

	/// Symmetric mode
	inline bool BSymmetricMode() const { return m_connectionConfig.m_SymmetricConnect.Get() != 0; }
	virtual bool BSupportsSymmetricMode();

	// Check the certs, save keys, etc
	ESteamNetConnectionEnd RecvCryptoHandshake( const CMsgSteamDatagramCertificateSigned &msgCert, const CMsgSteamDatagramSessionCryptInfoSigned &msgSessionInfo, bool bServer, SteamNetworkingErrMsg &errMsg );
	ESteamNetConnectionEnd FinishCryptoHandshake( bool bServer, SteamNetworkingErrMsg &errMsg );

	// Process crypto handshake, and terminate the connection if it fails
	bool BRecvCryptoHandshake( const CMsgSteamDatagramCertificateSigned &msgCert, const CMsgSteamDatagramSessionCryptInfoSigned &msgSessionInfo, bool bServer );

	/// Basically the same as Think(), but can be called when we don't already have
	/// the global lock.  If we can take the necessary locks now, without blocking,
	/// then we'll go ahead and take action now.  If we cannot, we will just schedule
	/// a wakeup call
	void CheckConnectionStateOrScheduleWakeUp( SteamNetworkingMicroseconds usecNow );

	// Upcasts.  So we don't have to compile with RTTI
	virtual CSteamNetworkConnectionP2P *AsSteamNetworkConnectionP2P();

	/// Is this an internal connection (e.g. for the ISteamMessages interface)?
	/// We *mostly* work on top of the sockets system, but in a few places we
	/// need to break the abstraction and do things other clients of the API
	/// could not do easily
	#ifdef STEAMNETWORKINGSOCKETS_ENABLE_STEAMNETWORKINGMESSAGES
	CMessagesEndPointSession *m_pMessagesEndPointSessionOwner = nullptr;
	#else
	static constexpr CMessagesEndPointSession *m_pMessagesEndPointSessionOwner = nullptr;
	#endif

	/// Time when we would like to send our next connection diagnostics
	/// update.  This is initialized the first time we enter the "connecting"
	/// state and we are on a platform that wants those updates.
	/// Once we wish to stop sending them, we set it to "never"
	#ifdef STEAMNETWORKINGSOCKETS_ENABLE_DIAGNOSTICSUI
		SteamNetworkingMicroseconds m_usecWhenNextDiagnosticsUpdate;
		void CheckScheduleDiagnosticsUpdateASAP();

		/// Fill out diagnostics message to send to steam client with current state of the
		/// connection, and also schedule the next check, if the connection is active.
		virtual void ConnectionPopulateDiagnostics( ESteamNetworkingConnectionState eOldState, CGameNetworkingUI_ConnectionState &msgConnectionState, SteamNetworkingMicroseconds usecNow );
	#else
		inline void CheckScheduleDiagnosticsUpdateASAP() {}
		static constexpr SteamNetworkingMicroseconds m_usecWhenNextDiagnosticsUpdate = k_nThinkTime_Never;
	#endif

	//
	// FakeIP
	//
	#ifdef STEAMNETWORKINGSOCKETS_ENABLE_FAKEIP
	FakeIPReference m_fakeIPRefRemote;
	#endif

	/// Timestamp when we were created
	SteamNetworkingMicroseconds m_usecWhenCreated;

	/// Setup lanes
	EResult SNP_ConfigureLanes( int nLanes, const int *pLanePriorities, const uint16 *pLaneWeights );

protected:
	CSteamNetworkConnectionBase( CSteamNetworkingSockets *pSteamNetworkingSocketsInterface, ConnectionScopeLock &scopeLock );
	virtual ~CSteamNetworkConnectionBase(); // hidden destructor, don't call directly.  Use ConnectionQueueDestroy()

	/// Initialize connection bookkeeping
	bool BInitConnection( SteamNetworkingMicroseconds usecNow, int nOptions, const SteamNetworkingConfigValue_t *pOptions, SteamDatagramErrMsg &errMsg );

	/// Called from BInitConnection, to start obtaining certs, etc
	virtual void InitConnectionCrypto( SteamNetworkingMicroseconds usecNow );

	/// Name assigned by app (for debugging)
	char m_szAppName[ k_cchSteamNetworkingMaxConnectionAppName ];

	/// More complete debug description (for debugging)
	char m_szDescription[ k_cchSteamNetworkingMaxConnectionDescription ];

	/// Set the connection description.  Should include the connection type and peer address.
	virtual void GetConnectionTypeDescription( ConnectionTypeDescription_t &szDescription ) const = 0;

	/// Misc periodic processing.
	/// Called from within CheckConnectionStateAndSetNextThinkTime.
	/// Will be called in any connection state.
	virtual void ThinkConnection( SteamNetworkingMicroseconds usecNow );

	/// Called from the connection Think() state machine, for connections that have been
	/// initiated locally and that are in the connecting state.
	///
	/// Should return the next time when it needs to be woken up.  Or it can set the next
	/// think time directly, if it is awkward to return.  That is slightly
	/// less efficient.
	///
	/// Base class sends connect requests (including periodic retry) through the current
	/// transport.
	virtual SteamNetworkingMicroseconds ThinkConnection_ClientConnecting( SteamNetworkingMicroseconds usecNow );

	/// Called from the connection Think() state machine, when the connection is in the finding
	/// route state.  The connection should return the next time when it needs to be woken up.
	/// Or it can set the next think time directly, if it is awkward to return.  That is slightly
	/// less efficient.
	virtual SteamNetworkingMicroseconds ThinkConnection_FindingRoute( SteamNetworkingMicroseconds usecNow );

	/// Called when a timeout is detected
	void ConnectionTimedOut( SteamNetworkingMicroseconds usecNow );

	/// Called when a timeout is detected to tried to provide a more specific error
	/// message.
	virtual void ConnectionGuessTimeoutReason( ESteamNetConnectionEnd &nReasonCode, ConnectionEndDebugMsg &msg, SteamNetworkingMicroseconds usecNow );

	/// Called when we receive a complete message.  Should allocate a message object and put it into the proper queues
	bool ReceivedMessageData( const void *pData, int cbData, int idxLane, int64 nMsgNum, int nFlags, SteamNetworkingMicroseconds usecNow );
	void ReceivedMessage( CSteamNetworkingMessage *pMsg );
	CSteamNetworkingMessage *AllocateNewRecvMessage( uint32 cbSize, int nFlags, SteamNetworkingMicroseconds usecNow );

	/// Timestamp when we last sent an end-to-end connection request packet
	SteamNetworkingMicroseconds m_usecWhenSentConnectRequest;

	//
	// Crypto
	//

	void ClearCrypto();
	bool BThinkCryptoReady( SteamNetworkingMicroseconds usecNow );
	void SetLocalCertUnsigned();
	void ClearLocalCrypto();
	void FinalizeLocalCrypto();
	void SetCryptoCipherList();

	// Remote cert and crypt info.  We need to hand on to the original serialized version briefly
	std::string m_sCertRemote;
	std::string m_sCryptRemote;
	CMsgSteamDatagramCertificate m_msgCertRemote;
	CMsgSteamDatagramSessionCryptInfo m_msgCryptRemote;
	bool m_bRemoteCertHasTrustedCASignature; // Could expand this to an enum of different states

	// Local crypto info for this connection
	CECSigningPrivateKey m_keyPrivate; // Private key corresponding to our cert.  We'll wipe this in FinalizeLocalCrypto, as soon as we've locked in the crypto properties we're going to use
	CECKeyExchangePrivateKey m_keyExchangePrivateKeyLocal;
	CMsgSteamDatagramSessionCryptInfo m_msgCryptLocal;
	CMsgSteamDatagramSessionCryptInfoSigned m_msgSignedCryptLocal;
	CMsgSteamDatagramCertificateSigned m_msgSignedCertLocal;
	bool m_bCertHasIdentity; // Does the cert contain the identity we will use for this connection?
	ESteamNetworkingSocketsCipher m_eNegotiatedCipher;

	// Encryption/decryption contexts.  This has the negotiated key
	bool m_bCryptKeysValid;
	std::unique_ptr<ISymmetricEncryptContext> m_pCryptContextSend;
	std::unique_ptr<ISymmetricDecryptContext> m_pCryptContextRecv;

	// Initialization vector for per-packet encryption.  These are
	// combined with the packet number so that the effective IV is
	// unique per packet.  We use a 96-bit IV, which is what TLS uses
	// (RFC5288), what NIST recommends (https://dl.acm.org/citation.cfm?id=2206251),
	// and what makes GCM the most efficient. 
	AutoWipeFixedSizeBuffer<12> m_cryptIVSend;
	AutoWipeFixedSizeBuffer<12> m_cryptIVRecv;

	/// Check if the remote cert (m_msgCertRemote) is acceptable.  If not, return the
	/// appropriate connection code and error message.  If pCACertAuthScope is NULL, the
	/// cert is not signed.  (The base class will check if this is allowed.)  If pCACertAuthScope
	/// is present, the cert was signed and the chain of trust has been verified, and the CA trust
	/// chain has authorized the specified rights.
	virtual ESteamNetConnectionEnd CheckRemoteCert( const CertAuthScope *pCACertAuthScope, SteamNetworkingErrMsg &errMsg );

	/// Called when we the remote host presents us with an unsigned cert.
	virtual EUnsignedCert AllowRemoteUnsignedCert();

	/// Called to decide if we want to try to proceed without a signed cert for ourselves
	virtual EUnsignedCert AllowLocalUnsignedCert();

	//
	// "SNP" - Steam Networking Protocol.  (Sort of audacious to stake out this acronym, don't you think...?)
	//         The layer that does end-to-end reliability and bandwidth estimation
	//

	void SNP_InitializeConnection( SteamNetworkingMicroseconds usecNow );
	void SNP_ShutdownConnection();
	int64 SNP_SendMessage( CSteamNetworkingMessage *pSendMessage, SteamNetworkingMicroseconds usecNow, bool *pbThinkImmediately );
	SteamNetworkingMicroseconds SNP_ThinkSendState( SteamNetworkingMicroseconds usecNow );
	SteamNetworkingMicroseconds SNP_GetNextThinkTime( SteamNetworkingMicroseconds usecNow );
	SteamNetworkingMicroseconds SNP_TimeWhenWantToSendNextPacket() const;
	void SNP_PrepareFeedback( SteamNetworkingMicroseconds usecNow );
	void SNP_ReceiveUnreliableSegment( int64 nMsgNum, int nOffset, const void *pSegmentData, int cbSegmentSize, bool bLastSegmentInMessage, int idxLane, SteamNetworkingMicroseconds usecNow );
	bool SNP_ReceiveReliableSegment( int64 nPktNum, int64 nSegBegin, const uint8 *pSegmentData, int cbSegmentSize, int idxLane, SteamNetworkingMicroseconds usecNow );
	int SNP_ClampSendRate();
	void SNP_PopulateDetailedStats( SteamDatagramLinkStats &info );
	void SNP_PopulateRealTimeStatus( SteamNetConnectionRealTimeStatus_t *pStatus, int nLanes, SteamNetConnectionRealTimeLaneStatus_t *pLanes, SteamNetworkingMicroseconds usecNow );
	void SNP_RecordReceivedPktNum( int64 nPktNum, SteamNetworkingMicroseconds usecNow, bool bScheduleAck );
	EResult SNP_FlushMessage( SteamNetworkingMicroseconds usecNow );

	/// Accumulate "tokens" into our bucket base on the current calculated send rate
	void SNP_TokenBucket_Accumulate( SteamNetworkingMicroseconds usecNow );

	/// Mark a packet as dropped
	void SNP_SenderProcessPacketNack( int64 nPktNum, SNPInFlightPacket_t &pkt, const char *pszDebug );

	/// Check in flight packets.  Expire any that need to be, and return the time when the
	/// next one that is not yet expired will be expired.
	SteamNetworkingMicroseconds SNP_SenderCheckInFlightPackets( SteamNetworkingMicroseconds usecNow );

	SSNPSenderState m_senderState;
	SSNPReceiverState m_receiverState;

	/// Bandwidth estimation data
	SSendRateData m_sendRateData; // FIXME Move this to transport!

	/// Called from SNP layer when it decodes a packet that serves as a ping measurement
	virtual void ProcessSNPPing( int msPing, RecvPacketContext_t &ctx );

private:

	void SNP_GatherAckBlocks( SNPPacketSerializeHelper &helper );

	template<bool k_bUnreliableOnly, bool k_bSingleLane>
	int SNP_SerializePacketInternal( SNPPacketSerializeHelper &helper );

	template<bool k_bUnreliableOnly, bool k_bSingleLane>
	uint8 *SNP_SerializeSegments( uint8 *pPayloadPtr, SNPPacketSerializeHelper &helper, SNPSegmentCollector<k_bUnreliableOnly, k_bSingleLane> &segmentCollector );

	template<bool k_bUnreliableOnly>
	uint8 *SNP_SerializeSegments_MultiLane( uint8 *pPayloadPtr, SNPPacketSerializeHelper &helper, SNPSegmentCollector<k_bUnreliableOnly, false> &segmentCollector );

	template<bool k_bUnreliableOnly>
	uint8 *SNP_SerializeSegmentArray( uint8 *pPayloadPtr, SNPPacketSerializeHelper &helper, SNPEncodedSegment *pSegBegin, SNPEncodedSegment *pSegEnd, bool bLastLane );

	uint8 *SNP_SerializeAckBlocks( const SNPPacketSerializeHelper &helper, uint8 *pOut, const uint8 *pOutEnd );
	uint8 *SNP_SerializeStopWaitingFrame( SNPPacketSerializeHelper &helper, uint8 *pOut );
	void SNP_QueueReliableSegmentsForRetry( SNPInFlightPacket_t &pkt, int64 nPktNumForDebug, const char *pszDebug );

	void SetState( ESteamNetworkingConnectionState eNewState, SteamNetworkingMicroseconds usecNow );
	ESteamNetworkingConnectionState m_eConnectionState;

	/// State of the connection as our peer would observe it.
	/// (Certain local state transitions are not meaningful.)
	///
	/// Differs from m_eConnectionState in two ways:
	/// - Linger is not used.  Instead, to the peer we are "connected."
	/// - When the local connection state transitions
	///   from ProblemDetectedLocally or ClosedByPeer to FinWait,
	///   when the application closes the connection, this value
	///   will not change.  It will retain the previous state,
	///   so that while we are in the FinWait state, we can send
	///   appropriate cleanup messages.
	ESteamNetworkingConnectionState m_eConnectionWireState;

	/// Timestamp when we entered the current state.  Used for various
	/// timeouts.
	SteamNetworkingMicroseconds m_usecWhenEnteredConnectionState;

	/// Return true if we're ready to exit the linger state and go to FinWait
	bool BReadyToExitLingerState() const;

	// !DEBUG! Log of packets we sent.
	#ifdef SNP_ENABLE_PACKETSENDLOG
	struct PacketSendLog
	{
		// State before we sent anything
		SteamNetworkingMicroseconds m_usecTime;
		int m_cbPendingReliable;
		int m_cbPendingUnreliable;
		int m_nPacketGaps;
		float m_fltokens;
		int64 m_nPktNumNextPendingAck;
		SteamNetworkingMicroseconds m_usecNextPendingAckTime;
		int64 m_nMaxPktRecv;
		int64 m_nMinPktNumToSendAcks;

		int m_nAckBlocksNeeded;

		// What we sent
		int m_nAckBlocksSent;
		int64 m_nAckEnd;
		int m_nReliableSegmentsRetry;
		int m_nSegmentsSent;
		int m_cbSent;
	};
	std_vector<PacketSendLog> m_vecSendLog;
	#endif

	/// Check invariants in debug.
	#if STEAMNETWORKINGSOCKETS_SNP_PARANOIA > 0
		inline void SNP_DebugCheckPacketGapMap() const
		{
			SNP_DebugCheckPacketGapMapSentinel();
			m_receiverState.DebugCheckPacketGapMap();
		}
		void SNP_DebugCheckPacketGapMapSentinel() const;
	#else
		inline void SNP_DebugCheckPacketGapMap() const {}
		inline void SNP_DebugCheckPacketGapMapSentinel() const {}
	#endif

	// Implements IThinker.
	// Connections must not override this, or call it directly.
	// Do any periodic work in ThinkConnection()
	virtual void Think( SteamNetworkingMicroseconds usecNow ) override final;
};

/// Abstract base class for sending end-to-end data for a connection.
///
/// Many connection classes only have one transport, but some may
/// may have more than one transport, and dynamically switch between
/// them.  (E.g. it will try local LAN, NAT piercing, then fallback to relay)
class CConnectionTransport
{
public:

	/// The connection we were created to service.  A given transport object
	/// is always created for a single connection (and that will not change,
	/// hence this is a reference and not a pointer).  However, a connection may
	/// create more than one transport.
	CSteamNetworkConnectionBase &m_connection;

	/// Use this function to actually delete the object.  Do not use operator delete
	void TransportDestroySelfNow();

	/// Free up transport resources.  Called just before destruction.  If you have cleanup
	/// that might involved calling virtual methods, do it in here
	virtual void TransportFreeResources();

	/// Called by SNP pacing layer, when it has some data to send and there is bandwidth available.
	/// The derived class should setup a context, reserving the space it needs, and then call SNP_SendPacket.
	/// Returns true if a packet was sent successfully, false if there was a problem.
	virtual bool SendDataPacket( SteamNetworkingMicroseconds usecNow ) = 0;

	/// Connection will call this to ask the transport to surround the
	/// "chunk" with the appropriate framing, and route it to the 
	/// appropriate host.  A "chunk" might contain a mix of reliable 
	/// and unreliable data.  We use the same framing for data 
	/// payloads for all connection types.  Return value is 
	/// the number of bytes written to the network layer, UDP/IP 
	/// header is not included.
	///
	/// ctx is whatever the transport passed to SNP_SendPacket, if the
	/// connection initiated the sending of the packet
	virtual int SendEncryptedDataChunk( const void *pChunk, int cbChunk, SendPacketContext_t &ctx ) = 0;

	/// Return true if we are currently able to send end-to-end messages.
	virtual bool BCanSendEndToEndConnectRequest() const;
	virtual bool BCanSendEndToEndData() const = 0;
	virtual void SendEndToEndConnectRequest( SteamNetworkingMicroseconds usecNow );
	virtual void SendEndToEndStatsMsg( EStatsReplyRequest eRequest, SteamNetworkingMicroseconds usecNow, const char *pszReason ) = 0;
	virtual void TransportPopulateConnectionInfo( SteamNetConnectionInfo_t &info ) const;
	virtual void GetDetailedConnectionStatus( SteamNetworkingDetailedConnectionStatus &stats, SteamNetworkingMicroseconds usecNow );
	#ifdef STEAMNETWORKINGSOCKETS_ENABLE_DIAGNOSTICSUI
		virtual void TransportPopulateDiagnostics( CGameNetworkingUI_ConnectionState &msgConnectionState, SteamNetworkingMicroseconds usecNow );
	#endif

	/// Called when the connection state changes.  Some transports need to do stuff
	virtual void TransportConnectionStateChanged( ESteamNetworkingConnectionState eOldState );

	/// Called when a timeout is detected to tried to provide a more specific error
	/// message
	virtual void TransportGuessTimeoutReason( ESteamNetConnectionEnd &nReasonCode, ConnectionEndDebugMsg &msg, SteamNetworkingMicroseconds usecNow );

	// Some accessors for commonly needed info
	inline ESteamNetworkingConnectionState ConnectionState() const { return m_connection.GetState(); }
	inline ESteamNetworkingConnectionState ConnectionWireState() const { return m_connection.GetWireState(); }
	inline uint32 ConnectionIDLocal() const { return m_connection.m_unConnectionIDLocal; }
	inline uint32 ConnectionIDRemote() const { return m_connection.m_unConnectionIDRemote; }
	inline CSteamNetworkListenSocketBase *ListenSocket() const { return m_connection.m_pParentListenSocket; }
	inline const SteamNetworkingIdentity &IdentityLocal() const { return m_connection.m_identityLocal; }
	inline const SteamNetworkingIdentity &IdentityRemote() const { return m_connection.m_identityRemote; }
	inline const char *ConnectionDescription() const { return m_connection.GetDescription(); }

	void _AssertLocksHeldByCurrentThread( const char *pszFile, int line, const char *pszTag = nullptr ) const
	{
		m_connection._AssertLocksHeldByCurrentThread( pszFile, line, pszTag );
	}

	// Useful so we can use ScheduledMethodThinkerLockable
	bool TryLock() { return m_connection.TryLock(); }
	void Unlock() { m_connection.Unlock(); }

protected:

	inline CConnectionTransport( CSteamNetworkConnectionBase &conn ) : m_connection( conn ) {}
	virtual ~CConnectionTransport() {} // Destructor protected -- use TransportDestroySelfNow()
};

// Delayed inline
inline ConnectionScopeLock::ConnectionScopeLock( CSteamNetworkConnectionBase &conn, const char *pszTag ) : ScopeLock<ConnectionLock>( *conn.m_pLock, pszTag ) {}
inline void ConnectionScopeLock::Lock( CSteamNetworkConnectionBase &conn, const char *pszTag ) { ScopeLock<ConnectionLock>::Lock( *conn.m_pLock, pszTag ); }

/// Dummy loopback/pipe connection that doesn't actually do any network work.
/// For these types of connections, the distinction between connection and transport
/// is not really useful
class CSteamNetworkConnectionPipe final : public CSteamNetworkConnectionBase, public CConnectionTransport
, public CTaskTarget // Should we promote this to a base class?
{
public:

	/// Create a pair of loopback connections that are immediately connected to each other
	/// No callbacks are posted.
	static bool APICreateSocketPair( CSteamNetworkingSockets *pSteamNetworkingSocketsInterface, CSteamNetworkConnectionPipe **pOutConnections, const SteamNetworkingIdentity pIdentity[2] );

	/// Create a pair of loopback connections that act like normal connections, but use internal transport.
	/// The two connections will be placed in the "connecting" state, and will go through the ordinary
	/// state machine.
	///
	/// The client connection is returned.
	static CSteamNetworkConnectionPipe *CreateLoopbackConnection(
		CSteamNetworkingSockets *pClientInstance,
		int nOptions, const SteamNetworkingConfigValue_t *pOptions,
		CSteamNetworkListenSocketBase *pListenSocket, const SteamNetworkingIdentity &identityServerInitial,
		SteamNetworkingErrMsg &errMsg,
		ConnectionScopeLock &scopeLock );

	/// The guy who is on the other end.
	/// This linkage can only be changed (or our partner deleted)
	/// while the global lock is held, AND both connection locks are held
	CSteamNetworkConnectionPipe *m_pPartner;

	// CSteamNetworkConnectionBase overrides
	virtual int64 _APISendMessageToConnection( CSteamNetworkingMessage *pMsg, SteamNetworkingMicroseconds usecNow, bool *pbThinkImmediately ) override;
	virtual EResult AcceptConnection( SteamNetworkingMicroseconds usecNow ) override;
	virtual void InitConnectionCrypto( SteamNetworkingMicroseconds usecNow ) override;
	virtual EUnsignedCert AllowRemoteUnsignedCert() override;
	virtual EUnsignedCert AllowLocalUnsignedCert() override;
	virtual void GetConnectionTypeDescription( ConnectionTypeDescription_t &szDescription ) const override;
	virtual void DestroyTransport() override;
	virtual void ConnectionStateChanged( ESteamNetworkingConnectionState eOldState ) override;
	virtual bool BSupportsSymmetricMode() override;

	// CConnectionTransport
	virtual bool SendDataPacket( SteamNetworkingMicroseconds usecNow ) override;
	virtual bool BCanSendEndToEndConnectRequest() const override;
	virtual bool BCanSendEndToEndData() const override;
	virtual void SendEndToEndConnectRequest( SteamNetworkingMicroseconds usecNow ) override;
	virtual void SendEndToEndStatsMsg( EStatsReplyRequest eRequest, SteamNetworkingMicroseconds usecNow, const char *pszReason ) override;
	virtual int SendEncryptedDataChunk( const void *pChunk, int cbChunk, SendPacketContext_t &ctx ) override;
	virtual void TransportPopulateConnectionInfo( SteamNetConnectionInfo_t &info ) const override;

private:

	// Use CreateSocketPair!
	CSteamNetworkConnectionPipe( CSteamNetworkingSockets *pSteamNetworkingSocketsInterface, const SteamNetworkingIdentity &identity, ConnectionScopeLock &scopeLock, bool bUseFastPath );
	virtual ~CSteamNetworkConnectionPipe();

	/// Setup the server side of a loopback connection
	bool BBeginAccept( CSteamNetworkListenSocketBase *pListenSocket, SteamNetworkingMicroseconds usecNow, ConnectionScopeLock &scopeLock, SteamDatagramErrMsg &errMsg );

	/// Act like we sent a sequenced packet
	void FakeSendStatsAndRecv( SteamNetworkingMicroseconds usecNow, int cbPktSize );

	uint16 FakeSendStats( SteamNetworkingMicroseconds usecNow, int cbPktSize );
	void FakeRecvStats( SteamNetworkingMicroseconds usecNow, int cbPktSize, uint16 nWirePktNum );
};

// Had to delay this until CSteamNetworkConnectionBase was defined
template<typename TStatsMsg>
inline void SendPacketContext<TStatsMsg>::CalcMaxEncryptedPayloadSize( size_t cbHdrReserve, CSteamNetworkConnectionBase *pConnection )
{
	Assert( m_cbTotalSize >= 0 );
	m_cbMaxEncryptedPayload = pConnection->m_cbMTUPacketSize - (int)cbHdrReserve - m_cbTotalSize;
	Assert( m_cbMaxEncryptedPayload >= 0 );
}

/////////////////////////////////////////////////////////////////////////////
//
// Misc globals
//
/////////////////////////////////////////////////////////////////////////////

extern CUtlHashMap<uint16, CSteamNetworkConnectionBase *, std::equal_to<uint16>, Identity<uint16> > g_mapConnections;
extern CUtlHashMap<int, CSteamNetworkPollGroup *, std::equal_to<int>, Identity<int> > g_mapPollGroups;

// All of the tables above are projected by the same lock, since we expect to only access it briefly
struct TableLock : Lock<RecursiveTimedMutexImpl> {
	TableLock() : Lock<RecursiveTimedMutexImpl>( "table", LockDebugInfo::k_nFlag_Table ) {}
}; 
using TableScopeLock = ScopeLock<TableLock>;
extern TableLock g_tables_lock;

// This table is protected by the global lock
extern CUtlHashMap<int, CSteamNetworkListenSocketBase *, std::equal_to<int>, Identity<int> > g_mapListenSockets;

extern bool BCheckGlobalSpamReplyRateLimit( SteamNetworkingMicroseconds usecNow );
extern CSteamNetworkConnectionBase *GetConnectionByHandle( HSteamNetConnection sock, ConnectionScopeLock &scopeLock );
extern CSteamNetworkPollGroup *GetPollGroupByHandle( HSteamNetPollGroup hPollGroup, PollGroupScopeLock &scopeLock, const char *pszLockTag );

inline CSteamNetworkConnectionBase *FindConnectionByLocalID( uint32 nLocalConnectionID, ConnectionScopeLock &scopeLock )
{
	// We use the wire connection ID as the API handle, so these two operations
	// are currently the same.
	return GetConnectionByHandle( HSteamNetConnection( nLocalConnectionID ), scopeLock );
}

} // namespace SteamNetworkingSocketsLib

#endif // STEAMNETWORKINGSOCKETS_CONNECTIONS_H
