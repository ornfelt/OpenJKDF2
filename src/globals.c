#include "globals.h"

#include "General/stdStrTable.h"
#include "Primitives/rdModel3.h"
#include "Primitives/rdVector.h"
#include "Primitives/rdMatrix.h"
#include "Raster/rdFace.h"
#include "Raster/rdCache.h"
#include "Engine/rdKeyframe.h"
#include "Engine/sithRender.h"
#include "World/sithWorld.h"
#include "World/sithSector.h"
#include "World/sithThing.h"

#include "jk.h"

#ifdef NO_JK_MMAP
// Vars
stdHashTable* sithAIClass_hashmap = NULL;
char std_genBuffer[1024] = {0};
struct HostServices* std_pHS = NULL;
rdGeoset* rdModel3_pCurGeoset = NULL;
rdVector3 localCamera = {0};
rdVector3 aFaceVerts[32] = {0};
rdMeshinfo vertexDst = {0};
int curGeometryMode = 0;
rdLight* apGeoLights[64] = {0};
rdVector3 rdModel3_aLocalLightPos[64] = {0};
rdVector3 rdModel3_aLocalLightDir[64] = {0};
int meshFrustrumCull = 0;
int curTextureMode = 0;
rdVector3 aView[512] = {0};
rdMesh* pCurMesh = NULL;
int thingFrustrumCull = 0;
rdMeshinfo vertexSrc = {0};
rdModel3* pCurModel3 = NULL;
int rdModel3_textureMode = 0;
int curLightingMode = 0;
rdLight* apMeshLights[64] = {0};
rdThing* pCurThing = NULL;
int rdModel3_lightingMode = 0;
int rdModel3_geometryMode = 0;
int rdModel3_numDrawnModels = 0;
model3Loader_t pModel3Loader = {0};
model3Unloader_t pModel3Unloader = {0};
uint32_t rdModel3_numGeoLights = {0};
int rdModel3_numMeshLights = 0;
float rdModel3_fRadius = 0.0f;
stdHashTable* sithPuppet_hashtable = NULL;
stdHashTable* sithPuppet_keyframesHashtable = NULL;
stdHashTable* sithPuppet_animNamesToIdxHashtable = NULL;
keyframeLoader_t pKeyframeLoader = {0};
keyframeUnloader_t pKeyframeUnloader = {0};
int32_t sithTime_deltaMs = {0};
float sithTime_deltaSeconds = 0.0f;
float  sithTime_TickHz = {0};
uint32_t sithTime_curMs = {0};
float sithTime_curSeconds = 0.0f;
uint32_t sithTime_curMsAbsolute = {0};
int32_t sithTime_pauseTimeMs = {0};
int sithTime_bRunning = 0;
int sithRender_texMode = 0;
int sithRender_flag = 0;
int sithRender_geoMode = 0;
int sithRender_lightMode = 0;
int sithRender_lightingIRMode = 0;
float sithRender_f_83198C = 0.0f;
float sithRender_f_831990 = 0.0f;
int sithRender_needsAspectReset = 0;
int32_t sithRender_numSectors = {0};
int32_t sithRender_numClipFrustums = {0};
int32_t sithRender_numLights = {0};
int32_t sithRender_numSectors2 = {0};
uint32_t sithRender_82F4B4 = {0};
int sithRender_sectorsDrawn = 0;
int32_t sithRender_numSurfaces = {0};
int sithRender_geoThingsDrawn = 0;
int sithRender_nongeoThingsDrawn = 0;
float  sithRender_f_82F4B0 =  0.0;
rdVertexIdxInfo sithRender_idxInfo = {0};
rdMeshinfo meshinfo_out = {0};
sithRender_weapRendFunc_t sithRender_weaponRenderHandle = {0};
rdLight sithRender_aLights[32] = {0};
sithSector* sithRender_aSectors[SITH_MAX_VISIBLE_SECTORS] = {0};
rdClipFrustum sithRender_clipFrustums[SITH_MAX_VISIBLE_SECTORS] = {0};
sithSector* sithRender_aSectors2[SITH_MAX_VISIBLE_SECTORS_2+2] = {0};
rdVector3 sithRender_aVerticesTmp[32] = {0};
rdVector3 sithRender_aVerticesTmp_projected[32] = {0};
sithSurface* sithRender_aSurfaces[SITH_MAX_VISIBLE_ALPHA_SURFACES] = {0};
int sithRender_lastRenderTick = 0;
sithSurface* aSithSurfaces[SITH_MAX_VISIBLE_ALPHA_SURFACES] = {0};
sithCamera sithCamera_cameras[SITHCAMERA_NUMCAMERAS] = {0};
int sithCamera_dword_8EE5A0 = 0;
int sithCamera_state = 0;
int sithCamera_curCameraIdx = 0;
rdVector3 sithCamera_povShakeVector1 = {0};
rdVector3 sithCamera_povShakeVector2 = {0};
float sithCamera_povShakeF1 = 0.0f;
float sithCamera_povShakeF2 = 0.0f;
sithCamera* sithCamera_currentCamera = NULL;
int sithCamera_bInitted = 0;
rdMatrix34 sithCamera_viewMat = {0};
rdMatrix34 sithCamera_focusMat = {0};
int sithCamera_bOpen = 0;
rdVector4  rdroid_aMipDistances =  {10.0, 20.0, 40.0, 80.0};
int rdroid_frameTrue = 0;
int bRDroidStartup = 0;
int bRDroidOpen = 0;
int rdroid_curLightingMode = 0;
struct HostServices* rdroid_pHS = NULL;
int rdroid_curGeometryMode = 0;
stdPalEffect rdroid_curColorEffects = {0};
int rdroid_curOcclusionMethod = 0;
rdZBufferMethod_t rdroid_curZBufferMethod = {0};
int rdroid_curProcFaceUserData = 0;
int rdroid_curSortingMethod = 0;
int rdroid_curAcceleration = 0;
int rdroid_curTextureMode = 0;
int rdroid_curRenderOptions = 0;
int rdroid_curCullFlags = 0;
stdHashTable* sithMaterial_hashmap = NULL;
rdMaterial** sithMaterial_aMaterials = NULL;
int sithMaterial_numMaterials = 0;
rdTri rdCache_aHWSolidTris[RDCACHE_MAX_TRIS] = {0};
int rdCache_totalNormalTris = 0;
float rdCache_aIntensities[RDCACHE_MAX_VERTICES] = {0};
rdVector3 rdCache_aVertices[RDCACHE_MAX_VERTICES] = {0};
int rdCache_totalVerts = 0;
rdVector2 rdCache_aTexVertices[RDCACHE_MAX_VERTICES] = {0};
rdTri rdCache_aHWNormalTris[RDCACHE_MAX_TRIS] = {0};
int rdCache_totalSolidTris = 0;
D3DVERTEX rdCache_aHWVertices[RDCACHE_MAX_VERTICES] = {0};
int rdCache_drawnFaces = 0;
int rdCache_numUsedVertices = 0;
int rdCache_numUsedTexVertices = 0;
int rdCache_numUsedIntensities = 0;
rdVector2i rdCache_ulcExtent = {0};
rdVector2i rdCache_lrcExtent = {0};
int rdCache_numProcFaces = 0;
rdProcEntry rdCache_aProcFaces[RDCACHE_MAX_TRIS] = {0};
int rdCache_dword_865258 = 0;
wchar_t sithMulti_name[32] = {0};
sithMultiHandler_t sithMulti_handlerIdk = {0};
int sithMulti_multiModeFlags = 0;
uint32_t sithMulti_dword_83265C = {0};
int sithMulti_arr_832218[256] = {0};
uint32_t sithMulti_leaveJoinWaitMs = {0};
int sithMulti_dword_832654 = 0;
uint32_t sithMulti_lastScoreUpdateMs = {0};
uint32_t sithMulti_requestConnectIdx = {0};
int sithMulti_dword_832664 = 0;
rdColormap* rdColormap_pCurMap = NULL;
rdColormap* rdColormap_pIdentityMap = NULL;
sithEvent sithEvent_aEvents[256] = {0};
sithEvent* sithEvent_list = NULL;
int sithEvent_arrLut[256] = {0};
sithEventTask sithEvent_aTasks[SITH_NUM_EVENTS] = {0};
int sithEvent_numFreeEventBuffers = 0;
int sithEvent_bInit = 0;
int sithEvent_bOpen = 0;
int rdClip_faceStatus = 0;
rdVector3* pSourceVert = NULL;
float workIVerts[32] = {0};
rdVector3 workVerts[32] = {0};
rdVector3* pDestVert = NULL;
float* pDestIVert = NULL;
rdVector2 workTVerts[32] = {0};
float* pSourceIVert = NULL;
rdVector2* pSourceTVert = NULL;
rdVector2* pDestTVert = NULL;
int sithSoundMixer_dword_835FCC = 0;
int sithSoundMixer_bPlayingMci = 0;
int sithSoundMixer_bInitted = 0;
float sithSoundMixer_flt_835FD8 = 0.0f;
int sithSoundMixer_bIsMuted = 0;
float  sithSoundMixer_musicVolume =  1.0f;
float  sithSoundMixer_globalVolume =  1.0f;
int sithSoundMixer_numSoundsAvailable2 = 0;
int sithSoundMixer_numSoundsAvailable = 0;
sithPlayingSound sithSoundMixer_aPlayingSounds[SITH_MIXER_NUMPLAYINGSOUNDS] = {0};
int sithSoundMixer_aIdk[SITH_MIXER_NUMPLAYINGSOUNDS] = {0};
int sithSoundMixer_activeChannels = 0;
int sithSoundMixer_bOpened = 0;
sithSector* sithSoundMixer_pLastSectorSoundSector = NULL;
int sithSoundMixer_dword_836BFC = 0;
int sithSoundMixer_trackFrom = 0;
int sithSoundMixer_trackTo = 0;
sithPlayingSound* sithSoundMixer_pPlayingSoundIdk = NULL;
int sithSoundMixer_dword_836C00 = 0;
int  sithSoundMixer_nextSoundIdx =  1;
int sithSoundMixer_dword_836C04 = 0;
sithThing* sithSoundMixer_pFocusedThing = NULL;
int  sithSound_maxDataLoaded =  0x400000;
int  sithSound_var3 =  1;
int sithSound_curDataLoaded = 0;
int sithSound_bInit = 0;
stdHashTable* sithSound_hashtable = NULL;
int sithSound_var4 = 0;
int sithSound_var5 = 0;
int sithControl_inputFuncToControlType[74] = {0};
stdControlKeyInfo sithControl_aInputFuncToKeyinfo[74] = {0};
uint32_t sithControl_msIdle = {0};
int sithControl_bInitted = 0;
int sithControl_bOpened = 0;
sithControl_handler_t sithControl_aHandlers[SITHCONTROL_NUM_HANDLERS] = {0};
int sithControl_numHandlers = 0;
int sithControl_death_msgtimer = 0;
rdVector3  sithControl_vec3_54A570 =  {0.0, -1.0, 0.0};
float  sithControl_flt_54A57C =  0.2f;
sithSaveHandler_t sithGamesave_func1 = {0};
sithSaveHandler_t sithGamesave_func2 = {0};
sithSaveHandler_t sithGamesave_func3 = {0};
sithSaveHandler_t sithGamesave_funcWrite = {0};
sithSaveHandler_t sithGamesave_funcRead = {0};
char sithGamesave_autosave_fname[128] = {0};
sithGamesaveState_t sithGamesave_currentState = {0};
int sithGamesave_dword_835914 = 0;
char sithGamesave_fpath[132] = {0};
wchar_t sithGamesave_wsaveName[256] = {0};
char sithGamesave_saveName[128] = {0};
sithGamesave_Header sithGamesave_headerTmp = {0};
rdCamera* rdCamera_pCurCamera = NULL;
rdMatrix34 rdCamera_camMatrix = {0};
int sithNet_MultiModeFlags = 0;
int sithNet_scorelimit = 0;
int sithNet_teamScore[5] = {0};
int sithNet_multiplayer_timelimit = 0;
int sithMulti_multiplayerTimelimit = 0;
int sithNet_isMulti = 0;
int sithNet_isServer = 0;
int sithMulti_bTimelimitMet = 0;
int sithNet_serverNetId = 0;
int sithNet_things[SITH_MAX_THINGS] = {0};
int sithNet_thingsIdx = 0;
int sithNet_syncIdx = 0;
int sithNet_aSyncFlags[SITH_MAX_SYNC_THINGS] = {0};
sithThing* sithNet_aSyncThings[SITH_MAX_SYNC_THINGS] = {0};
int  sithNet_tickrate =  180;
int sithNet_dword_8C4BA8 = 0;
int sithNet_dword_83262C = 0;
int sithMulti_leaveJoinType = 0;
int sithNet_checksum = 0;
int sithNet_bNeedsFullThingSyncForLeaveJoin = 0;
int sithMulti_sendto_id = 0;
int sithNet_bSyncScores = 0;
int sithNet_dword_832620 = 0;
float  sithOverlayMap_flMapSize =  100.0;
rdMatrix34 sithOverlayMap_matrix = {0};
sithThing* sithOverlayMap_pPlayer = NULL;
rdCanvas* sithOverlayMap_pCanvas = NULL;
int sithOverlayMap_x1 = 0;
int sithOverlayMap_y1 = 0;
sithMapView sithOverlayMap_inst = {0};
int sithOverlayMap_bShowMap = 0;
int sithOverlayMap_bInitted = 0;
stdHashTable* sithSoundClass_hashtable = NULL;
stdHashTable* sithSoundClass_nameToKeyHashtable = NULL;
void* sithTemplate_alloc = NULL;
stdHashTable* sithTemplate_hashmap = NULL;
int sithTemplate_count = 0;
stdHashTable* sithTemplate_oldHashtable = NULL;
rdEdge activeEdgeTail = {0};
rdEdge activeEdgeHead = {0};
rdEdge* apNewActiveEdges[1024] = {0};
rdEdge* apRemoveActiveEdges[1024] = {0};
int yMinEdge = 0;
int yMaxEdge = 0;
int numActiveSpans = 0;
int numActiveFaces = 0;
int numActiveEdges = 0;
rdEdge aActiveEdges[1024]  = {0};
int rdActive_drawnFaces = 0;
int sithMain_bEndLevel = 0;
int sithMain_bInitialized = 0;
int sithMain_bOpened = 0;
int sithSurface_numAvail = 0;
int sithSurface_aAvail[256+1] = {0};
int sithSurface_numSurfaces = 0;
rdSurface sithSurface_aSurfaces[256] = {0};
int sithSurface_bOpened = 0;
uint32_t  sithSurface_byte_8EE668 =  0;
int sithSurface_numSurfaces_0 = 0;
rdMaterialLoader_t pMaterialsLoader = {0};
rdMaterialUnloader_t pMaterialsUnloader = {0};
stdHashTable* sithSprite_hashmap = NULL;
WindowDrawHandler_t Window_drawAndFlip = {0};
WindowDrawHandler_t Window_setCooperativeLevel = {0};
wm_handler Window_ext_handlers[16] = {0};
HWND Window_aDialogHwnds[16] = {0};
int DebugGui_aIdk[32] = {0};
int DebugGui_idk = 0;
int DebugGui_some_line_amt = 0;
int DebugGui_some_num_lines = 0;
char DebugLog_buffer[4072] = {0};
stdDebugConsoleCmd* sithConsole_aCmds = NULL;
stdHashTable* sithConsole_pCmdHashtable = NULL;
int sithConsole_bOpened = 0;
int sithConsole_bInitted = 0;
int sithConsole_maxCmds = 0;
int sithConsole_numRegisteredCmds = 0;
uint32_t DebugGui_maxLines = {0};
DebugConsolePrintFunc_t DebugGui_fnPrint = {0};
DebugConsolePrintUniStrFunc_t DebugGui_fnPrintUniStr = {0};
stdSound_buffer_t* sithConsole_alertSound = NULL;
int16_t sithConsole_idk2 = {0};
uint32_t d3d_maxVertices = {0};
d3d_device* d3d_device_ptr = NULL;
rdRect std3D_rectViewIdk = {0};
float std3D_aViewIdk[32] = {0};
rdTri std3D_aViewTris[2] = {0};
int  std3D_gpuMaxTexSizeMaybe =  1;
int  std3D_dword_53D66C =  1;
int  std3D_dword_53D670 =  0x100;
int  std3D_dword_53D674 =  0x100;
intptr_t std3D_renderList = {0};
int stdComm_dword_8321F8 = 0;
int stdComm_bInitted = 0;
int stdComm_dword_8321F0 = 0;
int stdComm_dword_8321F4 = 0;
int stdComm_dplayIdSelf = 0;
int stdComm_dword_832204 = 0;
int stdComm_dword_832208 = 0;
int stdComm_currentBigSyncStage = 0;
int stdComm_dword_8321E0 = 0;
int stdComm_bIsServer = 0;
int stdComm_dword_8321E8 = 0;
wchar_t stdComm_waIdk[32] = {0};
int stdComm_dword_8321DC = 0;
int stdComm_dword_832200 = 0;
int stdComm_dword_832210 = 0;
sithCogMsg stdComm_cogMsgTmp = {0};
MCIDEVICEID stdMci_mciId = {0};
int stdMci_dwVolume = 0;
int stdMci_bInitted = 0;
int stdMci_uDeviceID = 0;
int wuRegistry_bInitted = 0;
uint8_t wuRegistry_lpClass[4] = {0};
uint8_t wuRegistry_byte_855EB4[4] = {0};
HKEY wuRegistry_hKey = {0};
LPCSTR wuRegistry_lpSubKey = {0};
uint32_t WinIdk_aDplayGuid[4] = {0};
stdVideoDevice stdDisplay_aDevices[16] = {0};
int stdDisplay_gammaTableLen = 0;
double* stdDisplay_paGammaTable = NULL;
rdColor24 stdDisplay_gammaPalette[256] = {0};
stdVideoDevice* stdDisplay_pCurDevice = NULL;
stdVideoMode* stdDisplay_pCurVideoMode = NULL;
int stdDisplay_bStartup = 0;
int stdDisplay_bOpen = 0;
int stdDisplay_bModeSet = 0;
int stdDisplay_numVideoModes = 0;
int stdDisplay_bPaged = 0;
uint8_t stdDisplay_tmpGammaPal[0x300] = {0};
int stdDisplay_gammaIdx = 0;
uint16_t word_860800 = {0};
uint16_t word_860802 = {0};
uint16_t word_860804 = {0};
uint16_t word_860806 = {0};
int  stdControl_bReadMouse =  1;
float  stdControl_updateKHz =  1.0f;
float  stdControl_updateHz =  1.0f;
float  stdControl_mouseXSensitivity =  1.0f;
float  stdControl_mouseYSensitivity =  1.0f;
float  stdControl_mouseZSensitivity =  1.0f;
int stdControl_aAxisEnabled[JK_NUM_JOYSTICKS] = {0};
int stdControl_aAxisPos[JK_NUM_AXES] = {0};
int stdControl_aInput1[JK_NUM_KEYS] = {0};
int stdControl_aKeyInfo[JK_NUM_KEYS] = {0};
int stdControl_aAxisConnected[JK_NUM_JOYSTICKS] = {0};
int stdControl_aInput2[JK_NUM_KEYS] = {0};
int stdControl_bStartup = 0;
int stdControl_bOpen = 0;
int stdControl_bDisableKeyboard = 0;
int stdControl_bControlsIdle = 0;
int stdControl_bControlsActive = 0;
void* stdControl_ppDI = NULL;
void* stdControl_mouseDirectInputDevice = NULL;
void* stdControl_keyboardIDirectInputDevice = NULL;
int stdControl_bHasJoysticks = 0;
uint32_t stdControl_curReadTime = {0};
uint32_t stdControl_msLast = {0};
uint32_t stdControl_msDelta = {0};
int32_t stdControl_dwLastMouseX = {0};
int32_t stdControl_dwLastMouseY = {0};
int stdControl_aJoystickEnabled[JK_NUM_JOYSTICKS] = {0};
int stdControl_aJoystickExists[4] = {0};
stdControlJoystickEntry stdControl_aJoysticks[JK_NUM_AXES] = {0};
int stdControl_aJoystickMaxButtons[JK_NUM_JOYSTICKS] = {0};
int Windows_installType = 0;
uint8_t Video_aGammaTable[80]  =  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x17, 0x5D, 0x74, 0xD1, 0x45, 0x17, 0xED, 0x3F, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xEA, 0x3F, 0xB7, 0x6D, 0xDB, 0xB6, 0x6D, 0xDB, 0xE6, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE4, 0x3F, 0x72, 0x1C, 0xC7, 0x71, 0x1C, 0xC7, 0xE1, 0x3F, 0x79, 0x0D, 0xE5, 0x35, 0x94, 0xD7, 0xE0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0x9E, 0xE7, 0x79, 0x9E, 0xE7, 0x79, 0xDE, 0x3F, 0xBE, 0xE9, 0x4D, 0x6F, 0x7A, 0xD3, 0xDB, 0x3F};
int  Video_fillColor =  0;
videoModeStruct Video_modeStruct = {0};
stdVBuffer Video_otherBuf = {0};
int Video_dword_866D78 = 0;
int Video_curMode = 0;
stdVideoMode Video_renderSurface[9]  = {0};
stdVBuffer Video_menuBuffer = {0};
stdVBuffer* Video_pOtherBuf = NULL;
stdVBuffer* Video_pMenuBuffer = NULL;
int Video_bInitted = 0;
int Video_bOpened = 0;
float Video_flt_55289C = 0.0f;
int Video_dword_5528A0 = 0;
int Video_dword_5528A4 = 0;
int Video_dword_5528A8 = 0;
int Video_lastTimeMsec = 0;
int Video_dword_5528B0 = 0;
stdVBuffer* Video_pVbufIdk = NULL;
rdCanvas* Video_pCanvas = NULL;
rdColor24 Video_aPalette[0x100] = {0};
stdVBufferTexFmt Video_format = {0};
stdVBufferTexFmt Video_format2 = {0};
videoModeStruct Video_modeStruct2 = {0};
stdVBuffer Video_bufIdk = {0};
uint16_t stdConsole_foregroundAttr = {0};
uint16_t stdConsole_wAttributes = {0};
int stdConsole_cursorHidden = 0;
CONSOLE_CURSOR_INFO stdConsole_ConsoleCursorInfo = {0};
HANDLE stdConsole_hConsoleOutput = {0};
HANDLE stdConsole_hConsoleInput = {0};
int rdRaster_aOneDivXQuantLUT[2048] = {0};
float rdRaster_aOtherLUT[16] = {0};
float rdRaster_aOneDivXLUT[2048] = {0};
float  rdRaster_fixedScale =  65536.0f;
sithThing* sithCogFunctionAI_apViewThings[32] = {0};
int sithCogFunctionAI_unk1 = 0;
int sithCogFunctionAI_viewThingIdx = 0;
sithCogMsg sithComm_MsgTmpBuf[32] = {0};
sithCogMsg_Pair sithComm_aMsgPairs[128] = {0};
cogMsg_Handler sithComm_msgFuncs[65] = {0};
int sithComm_needsSync = 0;
int sithComm_multiplayerFlags = 0;
int sithComm_bSyncMultiplayer = 0;
int sithComm_idk2 = 0;
int sithComm_bInit = 0;
uint32_t sithComm_dword_847E84 = {0};
int  sithComm_msgId =  1;
sithCogMsg sithComm_MsgTmpBuf2 = {0};
sithCogMsg sithComm_netMsgTmp = {0};
wchar_t jkCog_emptystring[2] = {0};
wchar_t jkCog_jkstring[130] = {0};
int jkCog_bInitted = 0;
stdStrTable jkCog_strings = {0};
int sithCog_bOpened = 0;
stdHashTable* sithCog_pScriptHashtable = NULL;
sithCogSectorLink sithCog_aSectorLinks[SITHCOG_MAX_LINKS] = {0};
int sithCog_numSectorLinks = 0;
sithCogThingLink sithCog_aThingLinks[SITHCOG_MAX_LINKS] = {0};
int sithCog_numThingLinks = 0;
int sithCog_numSurfaceLinks = 0;
sithCogSurfaceLink sithCog_aSurfaceLinks[SITHCOG_MAX_LINKS] = {0};
sithCog* sithCog_masterCog = NULL;
rdVector2i jkDev_aEntryPositions[10] = {0};
jkDevLogEnt jkDev_aEntries[5] = {0};
int jkDev_log_55A4A4 = 0;
int jkDev_bScreenNeedsUpdate = 0;
stdDebugConsoleCmd jkDev_aCheatCmds[JKDEV_NUM_CHEATS] = {0};
uint32_t jkDev_numCheats = {0};
int jkDev_bInitted = 0;
int jkDev_bOpened = 0;
stdHashTable* jkDev_cheatHashtable = NULL;
HWND jkDev_hDlg = {0};
stdVBuffer* jkDev_vbuf = NULL;
int jkDev_BMFontHeight = 0;
int jkDev_ColorKey = 0;
int jkDev_dword_55A9D0 = 0;
float jkDev_amt = 0.0f;
int jkSmack_gameMode = 0;
int jkSmack_bInit = 0;
int jkSmack_stopTick = 0;
int jkSmack_currentGuiState = 0;
int jkSmack_nextGuiState = 0;
void* jkSmack_alloc = NULL;
jkEpisode jkEpisode_aEpisodes[64] = {0};
char jkEpisode_var4[128] = {0};
char jkEpisode_var5[128] = {0};
uint32_t jkEpisode_var2 = {0};
jkEpisodeLoad jkEpisode_mLoad = {0};
uint32_t  jkHud_targetRed =  1;
uint32_t  jkHud_targetBlue =  2;
uint32_t  jkHud_targetGreen =  3;
float jkHud_aFltIdk[6]  =  {0.2, 0.4, 0.8, 1.0, 2.0, 0.0};
int jkHud_aColors8bpp[6]  =  {1,2,3,4,5,0};
int jkHud_aTeamColors8bpp[5]  =  {0x0, 0x6, 0x69, 0x1F, 0x2};
char jkHud_chatStr[128] = {0};
int jkHud_aTeamColors16bpp[5] = {0};
uint32_t jkHud_rightBlitX = {0};
uint32_t jkHud_leftBlitX = {0};
sithMapViewConfig jkHud_mapRendConfig = {0};
int jkHud_chatStrPos = 0;
int jkHud_rightBlitY = 0;
jkHudTeamScore jkHud_aTeamScores[5] = {0};
int jkHud_dword_552D10 = 0;
int jkHud_aColors16bpp[6] = {0};
jkHudPlayerScore jkHud_aPlayerScores[32] = {0};
int jkHud_blittedAmmoAmt = 0;
int jkHud_idk14 = 0;
int jkHud_blittedHealthIdx = 0;
int jkHud_blittedBatteryAmt = 0;
int jkHud_blittedFieldlightAmt = 0;
int jkHud_blittedShieldIdx = 0;
int jkHud_isSuper = 0;
int jkHud_idk15 = 0;
int jkHud_blittedForceIdx = 0;
int jkHud_idk16 = 0;
int jkHud_leftBlitY = 0;
rdRect jkHud_rectViewScores = {0};
stdFont* jkHud_pMsgFontSft = NULL;
stdBitmap* jkHud_pStatusLeftBm = NULL;
stdBitmap* jkHud_pStatusRightBm = NULL;
int jkHud_bHasTarget = 0;
sithThing* jkHud_pTargetThing = NULL;
uint32_t jkHud_targetRed16 = {0};
uint32_t jkHud_targetGreen16 = {0};
uint32_t jkHud_targetBlue16 = {0};
int jkHud_bChatOpen = 0;
stdFont* jkHud_pHelthNumSft = NULL;
stdFont* jkHud_pAmoNumsSft = NULL;
stdFont* jkHud_pAmoNumsSuperSft = NULL;
stdFont* jkHud_pArmorNumSft = NULL;
stdFont* jkHud_pArmorNumsSuperSft = NULL;
int jkHud_bInitted = 0;
int jkHud_bOpened = 0;
stdBitmap* jkHud_pFieldlightBm = NULL;
stdBitmap* jkHud_pStBatBm = NULL;
stdBitmap* jkHud_pStHealthBm = NULL;
stdBitmap* jkHud_pStShieldBm = NULL;
stdBitmap* jkHud_pStFrcBm = NULL;
stdBitmap* jkHud_pStFrcSuperBm = NULL;
int jkHud_bViewScores = 0;
int jkHud_dword_553ED0 = 0;
int jkHud_tallyWhich = 0;
uint32_t jkHud_numPlayers = {0};
int jkHud_dword_553EDC = 0;
int jkHud_dword_553EE0 = 0;
jkHudInvInfo jkHudInv_info = {0};
rdTexformat jkHudInv_itemTexfmt = {0};
int jkHudInv_flags = 0;
int jkHudInv_dword_553F64 = 0;
jkHudInvScroll jkHudInv_scroll = {0};
stdBitmap* jkHudInv_aBitmaps[3] = {0};
stdFont* jkHudInv_font = NULL;
int jkHudInv_rend_isshowing_maybe = 0;
int jkHudInv_dword_553F94 = 0;
int jkHudInv_numItems = 0;
int* jkHudInv_aItems = NULL;
int Main_bDevMode = 0;
int Main_bDisplayConfig = 0;
int Main_bWindowGUI = 0;
int Main_dword_86078C = 0;
int Main_bFrameRate = 0;
int Main_bDispStats = 0;
int Main_bNoHUD = 0;
int Main_logLevel = 0;
int Main_verboseLevel = 0;
char Main_path[128] = {0};
stdFile_t  debug_log_fp =  0;
HostServices* pHS = NULL;
char jkCredits_aPalette[0x300] = {0};
stdVBuffer* jkCredits_pVbuffer2 = NULL;
int jkCredits_dword_55AD64 = 0;
int jkCredits_dword_55AD68 = 0;
stdStrTable jkCredits_table = {0};
int jkCredits_startMs = 0;
int jkCredits_dword_55AD84 = 0;
int jkCredits_strIdx = 0;
char* jkCredits_aIdk = NULL;
stdVBuffer* jkCredits_pVbuffer = NULL;
int jkCredits_dword_55AD94 = 0;
stdFont* jkCredits_fontLarge = NULL;
stdFont* jkCredits_fontSmall = NULL;
int jkCredits_dword_55ADA0 = 0;
int jkCredits_bInitted = 0;
int jkCredits_dword_55ADA8 = 0;
int g_sithMode = 0;
int g_submodeFlags = 0;
int g_debugmodeFlags = 0;
int g_mapModeFlags = 0;
int jkGame_gamma = 0;
int jkGame_screenSize = 0;
int jkGame_bInitted = 0;
int jkGame_updateMsecsTotal = 0;
int jkGame_dword_552B5C = 0;
int jkGame_isDDraw = 0;
HostServices* jkRes_pHS = NULL;
char jkRes_episodeGobName[32]  =  {0};
char jkRes_curDir[128]  =  {0};
int jkRes_bHookedHS = 0;
jkResFile jkRes_aFiles[32] = {0};
jkRes jkRes_gCtx = {0};
HostServices* pLowLevelHS = NULL;
HostServices lowLevelHS = {0};
char jkRes_idkGobPath[128] = {0};
rdRect jkCutscene_rect1 = {0};
rdRect jkCutscene_rect2 = {0};
stdStrTable jkCutscene_strings = {0};
stdFont* jkCutscene_subtitlefont = NULL;
int jkCutscene_bInitted = 0;
int jkCutscene_isRendering = 0;
int jkCutscene_dword_55B750 = 0;
int jkCutscene_dword_55AA50 = 0;
int jkCutscene_55AA54 = 0;
char jkMain_aLevelJklFname[128] = {0};
int  thing_nine =  1;
int jkMain_bInit = 0;
int thing_six = 0;
int thing_eight = 0;
int jkMain_dword_552B98 = 0;
int jkMain_lastTickMs = 0;
int idx_13b4_related = 0;
char gamemode_1_str[128] = {0};
char jkMain_strIdk[128] = {0};
wchar_t jkMain_wstrIdk[128] = {0};
sithWorldParser sithWorld_aSectionParsers[32] = {0};
uint32_t sithWorld_some_integer_4 = {0};
sithWorld* sithWorld_pCurrentWorld = NULL;
sithWorld* sithWorld_pStatic = NULL;
sithWorld* sithWorld_pLoading = NULL;
uint32_t sithWorld_numParsers = {0};
uint32_t sithWorld_bInitted = {0};
int sithWorld_bLoaded = 0;
char sithWorld_episodeName[32] = {0};
sithKeybind sithInventory_powerKeybinds[SITHINVENTORY_NUM_POWERKEYBINDS] = {0};
int  sithInventory_549FA0 =  1;
sithItemDescriptor sithInventory_aDescriptors[SITHBIN_NUMBINS] = {0};
int sithInventory_bUnk = 0;
int sithInventory_bUnkPower = 0;
int sithInventory_8339EC = 0;
int sithInventory_bRendIsHidden = 0;
int sithInventory_8339F4 = 0;
uint32_t sithWeapon_controlOptions = {0};
float g_flt_8BD040 = 0.0f;
float g_flt_8BD044 = 0.0f;
float g_flt_8BD048 = 0.0f;
float g_flt_8BD04C = 0.0f;
float g_flt_8BD050 = 0.0f;
float g_flt_8BD054 = 0.0f;
float g_flt_8BD058 = 0.0f;
int sithWeapon_CurWeaponMode = 0;
int sithWeapon_bAutoPickup = 0;
int sithWeapon_bAutoSwitch = 0;
int sithWeapon_bAutoReload = 0;
int sithWeapon_bMultiAutoPickup = 0;
int sithWeapon_bMultiplayerAutoSwitch = 0;
int sithWeapon_bMultiAutoReload = 0;
int sithWeapon_bAutoAim = 0;
float sithWeapon_mountWait = 0.0f;
float sithWeapon_8BD0A0[2] = {0};
float sithWeapon_fireWait = 0.0f;
float sithWeapon_fireRate = 0.0f;
float sithWeapon_LastFireTimeSecs = 0.0f;
int sithWeapon_a8BD030[4] = {0};
int sithWeapon_8BD05C = 0;
float sithWeapon_8BD060 = 0.0f;
int sithWeapon_8BD008[6] = {0};
int sithWeapon_8BD024 = 0;
int sithWeapon_senderIndex = 0;
sithPlayerInfo jkPlayer_playerInfos[32] = {0};
wchar_t jkPlayer_playerShortName[32] = {0};
int jkPlayer_numOtherThings = 0;
int jkPlayer_numThings = 0;
jkPlayerInfo jkPlayer_otherThings[NUM_JKPLAYER_THINGS] = {0};
int  jkPlayer_dword_525470 =  1;
int bShowInvisibleThings = 0;
int playerThingIdx = 0;
uint32_t jkPlayer_maxPlayers = {0};
sithThing* sithPlayer_pLocalPlayerThing = NULL;
sithPlayerInfo* sithPlayer_pLocalPlayer = NULL;
jkPlayerInfo playerThings[32] = {0};
rdMatrix34 jkSaber_rotateMat = {0};
int jkPlayer_setRotateOverlayMap = 0;
int jkPlayer_setDrawStatus = 0;
int jkPlayer_setCrosshair = 0;
int jkPlayer_setSaberCam = 0;
int jkPlayer_setFullSubtitles = 0;
int jkPlayer_setDisableCutscenes = 0;
int jkPlayer_aCutsceneVal[32] = {0};
char jkPlayer_cutscenePath[1024] = {0};
int jkPlayer_setNumCutscenes = 0;
int jkPlayer_setDiff = 0;
rdVector3 jkPlayer_waggleVec = {0};
float jkPlayer_waggleMag = 0.0f;
int jkPlayer_mpcInfoSet = 0;
float jkPlayer_waggleAngle = 0.0f;
rdVector3 jkSaber_rotateVec = {0};
wchar_t jkPlayer_name[32] = {0};
char jkPlayer_model[32] = {0};
char jkPlayer_soundClass[32] = {0};
char jkPlayer_sideMat[32] = {0};
char jkPlayer_tipMat[32] = {0};
int sithCollision_stackIdk[4] = {0};
sithCollisionEntry sithCollision_collisionHandlers[144] = {0};
sithCollisionHitHandler_t sithCollision_funcList[12] = {0};
sithCollisionSearchResult sithCollision_searchStack[4] = {0};
int sithCollision_searchNumResults[4] = {0};
int  sithCollision_searchStackIdx =  -1;
sithCollisionSectorEntry sithCollision_stackSectors[4] = {0};
int sithCollision_dword_8B4BE4 = 0;
rdVector3 sithCollision_collideHurtIdk = {0};
rdVector3  sithSector_surfaceNormal =  {0.0, 0.0, -1.0};
sithSectorEntry sithAIAwareness_aEntries[32] = {0};
sithSectorAlloc* sithAIAwareness_aSectors = NULL;
int sithAIAwareness_numEntries = 0;
int sithAIAwareness_bInitted = 0;
int sithAIAwareness_timerTicks = 0;
float sithSector_flt_8553B8 = 0.0f;
float sithSector_horizontalPixelsPerRev = 0.0f;
float sithSector_flt_8553C0 = 0.0f;
float sithSector_flt_8553C4 = 0.0f;
float sithSector_flt_8553C8 = 0.0f;
rdVector3 sithSector_zMaxVec = {0};
float sithSector_ceilingSky = 0.0f;
rdVector3 sithSector_zMinVec = {0};
float sithSector_horizontalPixelsPerRev_idk = 0.0f;
float sithSector_horizontalDist = 0.0f;
float sithSector_flt_8553F4 = 0.0f;
sithSector* sithSector_aSyncIdk[16] = {0};
int sithSector_aSyncIdk2[16] = {0};
uint32_t sithSector_numSync = {0};
stdHashTable* sithThing_paramKeyToParamValMap = NULL;
sithThing_handler_t sithThing_handler = {0};
uint16_t  sithThing_inittedThings =  1;
wchar_t jkGuiSaveLoad_wtextEpisode[256] = {0};
wchar_t jkGuiSaveLoad_wtextHealth[64] = {0};
int jkGuiSaveLoad_numEntries = 0;
wchar_t jkGuiSaveLoad_wtextShields[64] = {0};
wchar_t jkGuiSaveLoad_word_559830[256] = {0};
int jkGuiSaveLoad_bIsSaveMenu = 0;
wchar_t jkGuiSaveLoad_wtextSaveName[256] = {0};
Darray jkGuiSaveLoad_DarrayEntries = {0};
wchar_t jkGuiSaveLoad_word_559C54[10] = {0};
char jkGuiSaveLoad_byte_559C50[4] = {0};
int  jkGuiTitle_verMajor =  1;
int  jkGuiTitle_verMinor =  0;
int  jkGuiTitle_verRevision =  0;
jkGuiStringEntry jkGuiTitle_aTexts[20] = {0};
int jkGuiTitle_whichLoading = 0;
float  jkGuiSound_sfxVolume =  0.8;
uint32_t  jkGuiSound_numChannels =  16;
int jkGuiSound_bLowResSound = 0;
int  jkGuiSound_b3DSound =  1;
int  jkGuiSound_b3DSound_2 =  1;
int  jkGuiSound_b3DSound_3 =  1;
float jkGuiSound_musicVolume = 0.0f;
char jkGui_unkstr[32] = {0};
int jkGui_GdiMode = 0;
int jkGui_modesets = 0;
stdBitmap* jkGui_stdBitmaps[0x27] = {0};
stdFont* jkGui_stdFonts[16] = {0};
jkEpisodeLoad jkGui_episodeLoad = {0};
stdBitmap* jkGuiSingleTally_foStars = NULL;
int jkGuiNetHost_maxRank = 0;
int jkGuiNetHost_timeLimit = 0;
int jkGuiNetHost_scoreLimit = 0;
int jkGuiNetHost_maxPlayers = 0;
int jkGuiNetHost_sessionFlags = 0;
int jkGuiNetHost_gameFlags = 0;
int jkGuiNetHost_tickRate = 0;
wchar_t jkGuiNetHost_gameName[32] = {0};
int jkGuiMultiplayer_checksumSeed = 0;
int jkGuiMultiplayer_dword_5564EC = 0;
int jkGuiMultiplayer_dword_5564E8 = 0;
jkMultiEntry jkGuiMultiplayer_multiEntry = {0};
int jkGuiMultiplayer_dword_5564F0 = 0;
HINSTANCE g_hInstance = {0};
sithCogSymboltable* sithCog_pSymbolTable = NULL;
struct HostServices* pSithHS = NULL;
HWND g_hWnd = {0};
uint32_t g_nShowCmd = {0};
uint32_t g_app_suspended = {0};
uint32_t g_window_active = {0};
uint32_t g_app_active = {0};
uint32_t g_should_exit = {0};
uint32_t g_thing_two_some_dialog_count = {0};
uint32_t g_handler_count = {0};
uint32_t g_855E8C = {0};
uint32_t g_855E90 = {0};
uint32_t g_window_not_destroyed = {0};
stdPalEffectsState stdPalEffects_state = {0};
rdColor24 stdPalEffects_palette[256] = {0};
uint32_t stdPalEffects_numEffectRequests = {0};
stdPalEffectRequest stdPalEffects_aEffects[32] = {0};
stdPalEffectSetPaletteFunc_t stdPalEffects_setPalette = {0};
uint16_t stdPalEffects_aPalette[256] = {0};
char aFilenameStack[2560] = {0};
char* apBufferStack[20] = {0};
int linenumStack[20] = {0};
char aEntryStack[0x14*(STDCONF_LINEBUFFER_LEN+4)] = {0};
int openFileStack[20] = {0};
char printfBuffer[STDCONF_LINEBUFFER_LEN] = {0};
int stdConffile_linenum = 0;
int stdConffile_bOpen = 0;
stdFile_t openFile = {0};
stdFile_t writeFile = {0};
uint32_t stackLevel = {0};
char stdConffile_aWriteFilename[128] = {0};
stdConffileEntry stdConffile_entry = {0};
char stdConffile_pFilename[128] = {0};
char* stdConffile_aLine = NULL;
int stdMemory_bInitted = 0;
int stdMemory_bOpened = 0;
stdMemoryInfo stdMemory_info = {0};
stdFile_t yyin = {0};
stdFile_t yyout = {0};
sithCogSymboltable* sithCogParse_pSymbolTable = NULL;
int yacc_linenum = 0;
int  cog_yacc_loop_depth =  1;
int cog_parser_node_stackpos[SITHCOG_NODE_STACKDEPTH] = {0};
int cogvm_stackpos = 0;
sith_cog_parser_node* cogparser_nodes_alloc = NULL;
sith_cog_parser_node* cogparser_topnode = NULL;
int* cogvm_stack = NULL;
int cogparser_num_nodes = 0;
int cogparser_current_nodeidx = 0;
sithCogScript* parsing_script = NULL;
int  parsing_script_idk =  1;
int dplay_dword_55D618 = 0;
int dplay_dword_55D61C = 0;
GUID_idk jkGui_guid_556040 = {0};
int jkGuiMultiplayer_numConnections = 0;
sith_dplay_connection jkGuiMultiplayer_aConnections[32] = {0};
jkMultiEntry jkGuiMultiplayer_aEntries[32] = {0};
jkMultiEntry2 jkGuiMultiplayer_stru_556168 = {0};
jkPlayerMpcInfo jkGuiMultiplayer_mpcInfo = {0};
Darray jkGuiMultiplayer_stru_5564A8 = {0};
int jkGuiMouse_bOpen = 0;
Darray jkGuiMouse_Darray_556698 = {0};
int jkGuiMouse_dword_5566B0 = 0;
Darray jkGuiMouse_Darray_5566B8 = {0};
Darray jkGuiMouse_Darray_5566D0 = {0};
wchar_t* jkGuiMouse_pWStr_5566E8 = NULL;
int jkGuiEsc_bInitialized = 0;
int jkGuiKeyboard_dword_555DE0 = 0;
int jkGuiKeyboard_bOnceIdk = 0;
int jkGuiKeyboard_funcIdx = 0;
int jkGuiKeyboard_flags = 0;
Darray jkGuiKeyboard_darrEntries = {0};
int jkGuiKeyboard_dword_555E10 = 0;
wchar_t jkGuiKeyboard_wstr_555E18[257] = {0};
wchar_t* jkGuiKeyboard_pWStr_55601C = NULL;
rdVector3 jkGuiMap_vec3Idk2 = {0};
rdCanvas* jkGuiMap_pCanvas = NULL;
rdMatrix34 jkGuiMap_viewMat = {0};
rdMatrix34 jkGuiMap_matTmp = {0};
stdVBuffer* jkGuiMap_pVbuffer = NULL;
sithMap jkGuiMap_unk4 = {0};
rdVector3 jkGuiMap_vec3Idk = {0};
rdCamera* jkGuiMap_pCamera = NULL;
int jkGuiMap_dword_556660 = 0;
int jkGuiMap_dword_556664 = 0;
int jkGuiMap_dword_556668 = 0;
int jkGuiMap_dword_55666C = 0;
float sithMap_unkArr[12]  =  {0.5, 1.0, 1.5, 2.0, 2.5, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 0.0};
sithThing* sithMap_pPlayerThing = NULL;
rdMatrix34 sithMap_invMatrix = {0};
float sithMap_flt_84DEA8 = 0.0f;
float sithMap_flt_84DEAC = 0.0f;
sithMap sithMap_ctx = {0};
sithWorld* sithMap_pCurWorld = NULL;
rdMatrix34 sithMap_camera = {0};
rdCamera* sithMap_pCurCamera = NULL;
int sithMap_bInitted = 0;
int sithMap_var = 0;
uint32_t DirectPlay_numPlayers = {0};
sithDplayPlayer DirectPlay_aPlayers[32] = {0};
#endif

void OpenJKDF2_Globals_Reset()
{
// Vars
sithAIClass_hashmap = NULL;
stdHashTable* __sithAIClass_hashmap_origValue = NULL;
_memcpy(&sithAIClass_hashmap, &__sithAIClass_hashmap_origValue, sizeof(sithAIClass_hashmap));
_memset(&std_genBuffer, 0, sizeof(std_genBuffer));
std_pHS = NULL;
struct HostServices* __std_pHS_origValue = NULL;
_memcpy(&std_pHS, &__std_pHS_origValue, sizeof(std_pHS));
rdModel3_pCurGeoset = NULL;
rdGeoset* __rdModel3_pCurGeoset_origValue = NULL;
_memcpy(&rdModel3_pCurGeoset, &__rdModel3_pCurGeoset_origValue, sizeof(rdModel3_pCurGeoset));
_memset(&localCamera, 0, sizeof(localCamera));
_memset(&aFaceVerts, 0, sizeof(aFaceVerts));
_memset(&vertexDst, 0, sizeof(vertexDst));
curGeometryMode = 0;
int __curGeometryMode_origValue = 0;
_memcpy(&curGeometryMode, &__curGeometryMode_origValue, sizeof(curGeometryMode));
_memset(&apGeoLights, 0, sizeof(apGeoLights));
_memset(&rdModel3_aLocalLightPos, 0, sizeof(rdModel3_aLocalLightPos));
_memset(&rdModel3_aLocalLightDir, 0, sizeof(rdModel3_aLocalLightDir));
meshFrustrumCull = 0;
int __meshFrustrumCull_origValue = 0;
_memcpy(&meshFrustrumCull, &__meshFrustrumCull_origValue, sizeof(meshFrustrumCull));
curTextureMode = 0;
int __curTextureMode_origValue = 0;
_memcpy(&curTextureMode, &__curTextureMode_origValue, sizeof(curTextureMode));
_memset(&aView, 0, sizeof(aView));
pCurMesh = NULL;
rdMesh* __pCurMesh_origValue = NULL;
_memcpy(&pCurMesh, &__pCurMesh_origValue, sizeof(pCurMesh));
thingFrustrumCull = 0;
int __thingFrustrumCull_origValue = 0;
_memcpy(&thingFrustrumCull, &__thingFrustrumCull_origValue, sizeof(thingFrustrumCull));
_memset(&vertexSrc, 0, sizeof(vertexSrc));
pCurModel3 = NULL;
rdModel3* __pCurModel3_origValue = NULL;
_memcpy(&pCurModel3, &__pCurModel3_origValue, sizeof(pCurModel3));
rdModel3_textureMode = 0;
int __rdModel3_textureMode_origValue = 0;
_memcpy(&rdModel3_textureMode, &__rdModel3_textureMode_origValue, sizeof(rdModel3_textureMode));
curLightingMode = 0;
int __curLightingMode_origValue = 0;
_memcpy(&curLightingMode, &__curLightingMode_origValue, sizeof(curLightingMode));
_memset(&apMeshLights, 0, sizeof(apMeshLights));
pCurThing = NULL;
rdThing* __pCurThing_origValue = NULL;
_memcpy(&pCurThing, &__pCurThing_origValue, sizeof(pCurThing));
rdModel3_lightingMode = 0;
int __rdModel3_lightingMode_origValue = 0;
_memcpy(&rdModel3_lightingMode, &__rdModel3_lightingMode_origValue, sizeof(rdModel3_lightingMode));
rdModel3_geometryMode = 0;
int __rdModel3_geometryMode_origValue = 0;
_memcpy(&rdModel3_geometryMode, &__rdModel3_geometryMode_origValue, sizeof(rdModel3_geometryMode));
rdModel3_numDrawnModels = 0;
int __rdModel3_numDrawnModels_origValue = 0;
_memcpy(&rdModel3_numDrawnModels, &__rdModel3_numDrawnModels_origValue, sizeof(rdModel3_numDrawnModels));
_memset(&pModel3Loader, 0, sizeof(pModel3Loader));
_memset(&pModel3Unloader, 0, sizeof(pModel3Unloader));
_memset(&rdModel3_numGeoLights, 0, sizeof(rdModel3_numGeoLights));
rdModel3_numMeshLights = 0;
int __rdModel3_numMeshLights_origValue = 0;
_memcpy(&rdModel3_numMeshLights, &__rdModel3_numMeshLights_origValue, sizeof(rdModel3_numMeshLights));
rdModel3_fRadius = 0.0f;
float __rdModel3_fRadius_origValue = 0.0f;
_memcpy(&rdModel3_fRadius, &__rdModel3_fRadius_origValue, sizeof(rdModel3_fRadius));
sithPuppet_hashtable = NULL;
stdHashTable* __sithPuppet_hashtable_origValue = NULL;
_memcpy(&sithPuppet_hashtable, &__sithPuppet_hashtable_origValue, sizeof(sithPuppet_hashtable));
sithPuppet_keyframesHashtable = NULL;
stdHashTable* __sithPuppet_keyframesHashtable_origValue = NULL;
_memcpy(&sithPuppet_keyframesHashtable, &__sithPuppet_keyframesHashtable_origValue, sizeof(sithPuppet_keyframesHashtable));
sithPuppet_animNamesToIdxHashtable = NULL;
stdHashTable* __sithPuppet_animNamesToIdxHashtable_origValue = NULL;
_memcpy(&sithPuppet_animNamesToIdxHashtable, &__sithPuppet_animNamesToIdxHashtable_origValue, sizeof(sithPuppet_animNamesToIdxHashtable));
_memset(&pKeyframeLoader, 0, sizeof(pKeyframeLoader));
_memset(&pKeyframeUnloader, 0, sizeof(pKeyframeUnloader));
_memset(&sithTime_deltaMs, 0, sizeof(sithTime_deltaMs));
sithTime_deltaSeconds = 0.0f;
float __sithTime_deltaSeconds_origValue = 0.0f;
_memcpy(&sithTime_deltaSeconds, &__sithTime_deltaSeconds_origValue, sizeof(sithTime_deltaSeconds));
_memset(&sithTime_TickHz, 0, sizeof(sithTime_TickHz));
_memset(&sithTime_curMs, 0, sizeof(sithTime_curMs));
sithTime_curSeconds = 0.0f;
float __sithTime_curSeconds_origValue = 0.0f;
_memcpy(&sithTime_curSeconds, &__sithTime_curSeconds_origValue, sizeof(sithTime_curSeconds));
_memset(&sithTime_curMsAbsolute, 0, sizeof(sithTime_curMsAbsolute));
_memset(&sithTime_pauseTimeMs, 0, sizeof(sithTime_pauseTimeMs));
sithTime_bRunning = 0;
int __sithTime_bRunning_origValue = 0;
_memcpy(&sithTime_bRunning, &__sithTime_bRunning_origValue, sizeof(sithTime_bRunning));
sithRender_texMode = 0;
int __sithRender_texMode_origValue = 0;
_memcpy(&sithRender_texMode, &__sithRender_texMode_origValue, sizeof(sithRender_texMode));
sithRender_flag = 0;
int __sithRender_flag_origValue = 0;
_memcpy(&sithRender_flag, &__sithRender_flag_origValue, sizeof(sithRender_flag));
sithRender_geoMode = 0;
int __sithRender_geoMode_origValue = 0;
_memcpy(&sithRender_geoMode, &__sithRender_geoMode_origValue, sizeof(sithRender_geoMode));
sithRender_lightMode = 0;
int __sithRender_lightMode_origValue = 0;
_memcpy(&sithRender_lightMode, &__sithRender_lightMode_origValue, sizeof(sithRender_lightMode));
sithRender_lightingIRMode = 0;
int __sithRender_lightingIRMode_origValue = 0;
_memcpy(&sithRender_lightingIRMode, &__sithRender_lightingIRMode_origValue, sizeof(sithRender_lightingIRMode));
sithRender_f_83198C = 0.0f;
float __sithRender_f_83198C_origValue = 0.0f;
_memcpy(&sithRender_f_83198C, &__sithRender_f_83198C_origValue, sizeof(sithRender_f_83198C));
sithRender_f_831990 = 0.0f;
float __sithRender_f_831990_origValue = 0.0f;
_memcpy(&sithRender_f_831990, &__sithRender_f_831990_origValue, sizeof(sithRender_f_831990));
sithRender_needsAspectReset = 0;
int __sithRender_needsAspectReset_origValue = 0;
_memcpy(&sithRender_needsAspectReset, &__sithRender_needsAspectReset_origValue, sizeof(sithRender_needsAspectReset));
_memset(&sithRender_numSectors, 0, sizeof(sithRender_numSectors));
_memset(&sithRender_numClipFrustums, 0, sizeof(sithRender_numClipFrustums));
_memset(&sithRender_numLights, 0, sizeof(sithRender_numLights));
_memset(&sithRender_numSectors2, 0, sizeof(sithRender_numSectors2));
_memset(&sithRender_82F4B4, 0, sizeof(sithRender_82F4B4));
sithRender_sectorsDrawn = 0;
int __sithRender_sectorsDrawn_origValue = 0;
_memcpy(&sithRender_sectorsDrawn, &__sithRender_sectorsDrawn_origValue, sizeof(sithRender_sectorsDrawn));
_memset(&sithRender_numSurfaces, 0, sizeof(sithRender_numSurfaces));
sithRender_geoThingsDrawn = 0;
int __sithRender_geoThingsDrawn_origValue = 0;
_memcpy(&sithRender_geoThingsDrawn, &__sithRender_geoThingsDrawn_origValue, sizeof(sithRender_geoThingsDrawn));
sithRender_nongeoThingsDrawn = 0;
int __sithRender_nongeoThingsDrawn_origValue = 0;
_memcpy(&sithRender_nongeoThingsDrawn, &__sithRender_nongeoThingsDrawn_origValue, sizeof(sithRender_nongeoThingsDrawn));
float  __sithRender_f_82F4B0_origValue =  0.0;
_memcpy(&sithRender_f_82F4B0, &__sithRender_f_82F4B0_origValue, sizeof(sithRender_f_82F4B0));
_memset(&sithRender_idxInfo, 0, sizeof(sithRender_idxInfo));
_memset(&meshinfo_out, 0, sizeof(meshinfo_out));
_memset(&sithRender_weaponRenderHandle, 0, sizeof(sithRender_weaponRenderHandle));
_memset(&sithRender_aLights, 0, sizeof(sithRender_aLights));
_memset(&sithRender_aSectors, 0, sizeof(sithRender_aSectors));
_memset(&sithRender_clipFrustums, 0, sizeof(sithRender_clipFrustums));
_memset(&sithRender_aSectors2, 0, sizeof(sithRender_aSectors2));
_memset(&sithRender_aVerticesTmp, 0, sizeof(sithRender_aVerticesTmp));
_memset(&sithRender_aVerticesTmp_projected, 0, sizeof(sithRender_aVerticesTmp_projected));
_memset(&sithRender_aSurfaces, 0, sizeof(sithRender_aSurfaces));
sithRender_lastRenderTick = 0;
int __sithRender_lastRenderTick_origValue = 0;
_memcpy(&sithRender_lastRenderTick, &__sithRender_lastRenderTick_origValue, sizeof(sithRender_lastRenderTick));
_memset(&aSithSurfaces, 0, sizeof(aSithSurfaces));
_memset(&sithCamera_cameras, 0, sizeof(sithCamera_cameras));
sithCamera_dword_8EE5A0 = 0;
int __sithCamera_dword_8EE5A0_origValue = 0;
_memcpy(&sithCamera_dword_8EE5A0, &__sithCamera_dword_8EE5A0_origValue, sizeof(sithCamera_dword_8EE5A0));
sithCamera_state = 0;
int __sithCamera_state_origValue = 0;
_memcpy(&sithCamera_state, &__sithCamera_state_origValue, sizeof(sithCamera_state));
sithCamera_curCameraIdx = 0;
int __sithCamera_curCameraIdx_origValue = 0;
_memcpy(&sithCamera_curCameraIdx, &__sithCamera_curCameraIdx_origValue, sizeof(sithCamera_curCameraIdx));
_memset(&sithCamera_povShakeVector1, 0, sizeof(sithCamera_povShakeVector1));
_memset(&sithCamera_povShakeVector2, 0, sizeof(sithCamera_povShakeVector2));
sithCamera_povShakeF1 = 0.0f;
float __sithCamera_povShakeF1_origValue = 0.0f;
_memcpy(&sithCamera_povShakeF1, &__sithCamera_povShakeF1_origValue, sizeof(sithCamera_povShakeF1));
sithCamera_povShakeF2 = 0.0f;
float __sithCamera_povShakeF2_origValue = 0.0f;
_memcpy(&sithCamera_povShakeF2, &__sithCamera_povShakeF2_origValue, sizeof(sithCamera_povShakeF2));
sithCamera_currentCamera = NULL;
sithCamera* __sithCamera_currentCamera_origValue = NULL;
_memcpy(&sithCamera_currentCamera, &__sithCamera_currentCamera_origValue, sizeof(sithCamera_currentCamera));
sithCamera_bInitted = 0;
int __sithCamera_bInitted_origValue = 0;
_memcpy(&sithCamera_bInitted, &__sithCamera_bInitted_origValue, sizeof(sithCamera_bInitted));
_memset(&sithCamera_viewMat, 0, sizeof(sithCamera_viewMat));
_memset(&sithCamera_focusMat, 0, sizeof(sithCamera_focusMat));
sithCamera_bOpen = 0;
int __sithCamera_bOpen_origValue = 0;
_memcpy(&sithCamera_bOpen, &__sithCamera_bOpen_origValue, sizeof(sithCamera_bOpen));
rdVector4  __rdroid_aMipDistances_origValue =  {10.0, 20.0, 40.0, 80.0};
_memcpy(&rdroid_aMipDistances, &__rdroid_aMipDistances_origValue, sizeof(rdroid_aMipDistances));
rdroid_frameTrue = 0;
int __rdroid_frameTrue_origValue = 0;
_memcpy(&rdroid_frameTrue, &__rdroid_frameTrue_origValue, sizeof(rdroid_frameTrue));
bRDroidStartup = 0;
int __bRDroidStartup_origValue = 0;
_memcpy(&bRDroidStartup, &__bRDroidStartup_origValue, sizeof(bRDroidStartup));
bRDroidOpen = 0;
int __bRDroidOpen_origValue = 0;
_memcpy(&bRDroidOpen, &__bRDroidOpen_origValue, sizeof(bRDroidOpen));
rdroid_curLightingMode = 0;
int __rdroid_curLightingMode_origValue = 0;
_memcpy(&rdroid_curLightingMode, &__rdroid_curLightingMode_origValue, sizeof(rdroid_curLightingMode));
rdroid_pHS = NULL;
struct HostServices* __rdroid_pHS_origValue = NULL;
_memcpy(&rdroid_pHS, &__rdroid_pHS_origValue, sizeof(rdroid_pHS));
rdroid_curGeometryMode = 0;
int __rdroid_curGeometryMode_origValue = 0;
_memcpy(&rdroid_curGeometryMode, &__rdroid_curGeometryMode_origValue, sizeof(rdroid_curGeometryMode));
_memset(&rdroid_curColorEffects, 0, sizeof(rdroid_curColorEffects));
rdroid_curOcclusionMethod = 0;
int __rdroid_curOcclusionMethod_origValue = 0;
_memcpy(&rdroid_curOcclusionMethod, &__rdroid_curOcclusionMethod_origValue, sizeof(rdroid_curOcclusionMethod));
_memset(&rdroid_curZBufferMethod, 0, sizeof(rdroid_curZBufferMethod));
rdroid_curProcFaceUserData = 0;
int __rdroid_curProcFaceUserData_origValue = 0;
_memcpy(&rdroid_curProcFaceUserData, &__rdroid_curProcFaceUserData_origValue, sizeof(rdroid_curProcFaceUserData));
rdroid_curSortingMethod = 0;
int __rdroid_curSortingMethod_origValue = 0;
_memcpy(&rdroid_curSortingMethod, &__rdroid_curSortingMethod_origValue, sizeof(rdroid_curSortingMethod));
rdroid_curAcceleration = 0;
int __rdroid_curAcceleration_origValue = 0;
_memcpy(&rdroid_curAcceleration, &__rdroid_curAcceleration_origValue, sizeof(rdroid_curAcceleration));
rdroid_curTextureMode = 0;
int __rdroid_curTextureMode_origValue = 0;
_memcpy(&rdroid_curTextureMode, &__rdroid_curTextureMode_origValue, sizeof(rdroid_curTextureMode));
rdroid_curRenderOptions = 0;
int __rdroid_curRenderOptions_origValue = 0;
_memcpy(&rdroid_curRenderOptions, &__rdroid_curRenderOptions_origValue, sizeof(rdroid_curRenderOptions));
rdroid_curCullFlags = 0;
int __rdroid_curCullFlags_origValue = 0;
_memcpy(&rdroid_curCullFlags, &__rdroid_curCullFlags_origValue, sizeof(rdroid_curCullFlags));
sithMaterial_hashmap = NULL;
stdHashTable* __sithMaterial_hashmap_origValue = NULL;
_memcpy(&sithMaterial_hashmap, &__sithMaterial_hashmap_origValue, sizeof(sithMaterial_hashmap));
sithMaterial_aMaterials = NULL;
rdMaterial** __sithMaterial_aMaterials_origValue = NULL;
_memcpy(&sithMaterial_aMaterials, &__sithMaterial_aMaterials_origValue, sizeof(sithMaterial_aMaterials));
sithMaterial_numMaterials = 0;
int __sithMaterial_numMaterials_origValue = 0;
_memcpy(&sithMaterial_numMaterials, &__sithMaterial_numMaterials_origValue, sizeof(sithMaterial_numMaterials));
_memset(&rdCache_aHWSolidTris, 0, sizeof(rdCache_aHWSolidTris));
rdCache_totalNormalTris = 0;
int __rdCache_totalNormalTris_origValue = 0;
_memcpy(&rdCache_totalNormalTris, &__rdCache_totalNormalTris_origValue, sizeof(rdCache_totalNormalTris));
_memset(&rdCache_aIntensities, 0, sizeof(rdCache_aIntensities));
_memset(&rdCache_aVertices, 0, sizeof(rdCache_aVertices));
rdCache_totalVerts = 0;
int __rdCache_totalVerts_origValue = 0;
_memcpy(&rdCache_totalVerts, &__rdCache_totalVerts_origValue, sizeof(rdCache_totalVerts));
_memset(&rdCache_aTexVertices, 0, sizeof(rdCache_aTexVertices));
_memset(&rdCache_aHWNormalTris, 0, sizeof(rdCache_aHWNormalTris));
rdCache_totalSolidTris = 0;
int __rdCache_totalSolidTris_origValue = 0;
_memcpy(&rdCache_totalSolidTris, &__rdCache_totalSolidTris_origValue, sizeof(rdCache_totalSolidTris));
_memset(&rdCache_aHWVertices, 0, sizeof(rdCache_aHWVertices));
rdCache_drawnFaces = 0;
int __rdCache_drawnFaces_origValue = 0;
_memcpy(&rdCache_drawnFaces, &__rdCache_drawnFaces_origValue, sizeof(rdCache_drawnFaces));
rdCache_numUsedVertices = 0;
int __rdCache_numUsedVertices_origValue = 0;
_memcpy(&rdCache_numUsedVertices, &__rdCache_numUsedVertices_origValue, sizeof(rdCache_numUsedVertices));
rdCache_numUsedTexVertices = 0;
int __rdCache_numUsedTexVertices_origValue = 0;
_memcpy(&rdCache_numUsedTexVertices, &__rdCache_numUsedTexVertices_origValue, sizeof(rdCache_numUsedTexVertices));
rdCache_numUsedIntensities = 0;
int __rdCache_numUsedIntensities_origValue = 0;
_memcpy(&rdCache_numUsedIntensities, &__rdCache_numUsedIntensities_origValue, sizeof(rdCache_numUsedIntensities));
_memset(&rdCache_ulcExtent, 0, sizeof(rdCache_ulcExtent));
_memset(&rdCache_lrcExtent, 0, sizeof(rdCache_lrcExtent));
rdCache_numProcFaces = 0;
int __rdCache_numProcFaces_origValue = 0;
_memcpy(&rdCache_numProcFaces, &__rdCache_numProcFaces_origValue, sizeof(rdCache_numProcFaces));
_memset(&rdCache_aProcFaces, 0, sizeof(rdCache_aProcFaces));
rdCache_dword_865258 = 0;
int __rdCache_dword_865258_origValue = 0;
_memcpy(&rdCache_dword_865258, &__rdCache_dword_865258_origValue, sizeof(rdCache_dword_865258));
_memset(&sithMulti_name, 0, sizeof(sithMulti_name));
_memset(&sithMulti_handlerIdk, 0, sizeof(sithMulti_handlerIdk));
sithMulti_multiModeFlags = 0;
int __sithMulti_multiModeFlags_origValue = 0;
_memcpy(&sithMulti_multiModeFlags, &__sithMulti_multiModeFlags_origValue, sizeof(sithMulti_multiModeFlags));
_memset(&sithMulti_dword_83265C, 0, sizeof(sithMulti_dword_83265C));
_memset(&sithMulti_arr_832218, 0, sizeof(sithMulti_arr_832218));
_memset(&sithMulti_leaveJoinWaitMs, 0, sizeof(sithMulti_leaveJoinWaitMs));
sithMulti_dword_832654 = 0;
int __sithMulti_dword_832654_origValue = 0;
_memcpy(&sithMulti_dword_832654, &__sithMulti_dword_832654_origValue, sizeof(sithMulti_dword_832654));
_memset(&sithMulti_lastScoreUpdateMs, 0, sizeof(sithMulti_lastScoreUpdateMs));
_memset(&sithMulti_requestConnectIdx, 0, sizeof(sithMulti_requestConnectIdx));
sithMulti_dword_832664 = 0;
int __sithMulti_dword_832664_origValue = 0;
_memcpy(&sithMulti_dword_832664, &__sithMulti_dword_832664_origValue, sizeof(sithMulti_dword_832664));
rdColormap_pCurMap = NULL;
rdColormap* __rdColormap_pCurMap_origValue = NULL;
_memcpy(&rdColormap_pCurMap, &__rdColormap_pCurMap_origValue, sizeof(rdColormap_pCurMap));
rdColormap_pIdentityMap = NULL;
rdColormap* __rdColormap_pIdentityMap_origValue = NULL;
_memcpy(&rdColormap_pIdentityMap, &__rdColormap_pIdentityMap_origValue, sizeof(rdColormap_pIdentityMap));
_memset(&sithEvent_aEvents, 0, sizeof(sithEvent_aEvents));
sithEvent_list = NULL;
sithEvent* __sithEvent_list_origValue = NULL;
_memcpy(&sithEvent_list, &__sithEvent_list_origValue, sizeof(sithEvent_list));
_memset(&sithEvent_arrLut, 0, sizeof(sithEvent_arrLut));
_memset(&sithEvent_aTasks, 0, sizeof(sithEvent_aTasks));
sithEvent_numFreeEventBuffers = 0;
int __sithEvent_numFreeEventBuffers_origValue = 0;
_memcpy(&sithEvent_numFreeEventBuffers, &__sithEvent_numFreeEventBuffers_origValue, sizeof(sithEvent_numFreeEventBuffers));
sithEvent_bInit = 0;
int __sithEvent_bInit_origValue = 0;
_memcpy(&sithEvent_bInit, &__sithEvent_bInit_origValue, sizeof(sithEvent_bInit));
sithEvent_bOpen = 0;
int __sithEvent_bOpen_origValue = 0;
_memcpy(&sithEvent_bOpen, &__sithEvent_bOpen_origValue, sizeof(sithEvent_bOpen));
rdClip_faceStatus = 0;
int __rdClip_faceStatus_origValue = 0;
_memcpy(&rdClip_faceStatus, &__rdClip_faceStatus_origValue, sizeof(rdClip_faceStatus));
pSourceVert = NULL;
rdVector3* __pSourceVert_origValue = NULL;
_memcpy(&pSourceVert, &__pSourceVert_origValue, sizeof(pSourceVert));
_memset(&workIVerts, 0, sizeof(workIVerts));
_memset(&workVerts, 0, sizeof(workVerts));
pDestVert = NULL;
rdVector3* __pDestVert_origValue = NULL;
_memcpy(&pDestVert, &__pDestVert_origValue, sizeof(pDestVert));
pDestIVert = NULL;
float* __pDestIVert_origValue = NULL;
_memcpy(&pDestIVert, &__pDestIVert_origValue, sizeof(pDestIVert));
_memset(&workTVerts, 0, sizeof(workTVerts));
pSourceIVert = NULL;
float* __pSourceIVert_origValue = NULL;
_memcpy(&pSourceIVert, &__pSourceIVert_origValue, sizeof(pSourceIVert));
pSourceTVert = NULL;
rdVector2* __pSourceTVert_origValue = NULL;
_memcpy(&pSourceTVert, &__pSourceTVert_origValue, sizeof(pSourceTVert));
pDestTVert = NULL;
rdVector2* __pDestTVert_origValue = NULL;
_memcpy(&pDestTVert, &__pDestTVert_origValue, sizeof(pDestTVert));
sithSoundMixer_dword_835FCC = 0;
int __sithSoundMixer_dword_835FCC_origValue = 0;
_memcpy(&sithSoundMixer_dword_835FCC, &__sithSoundMixer_dword_835FCC_origValue, sizeof(sithSoundMixer_dword_835FCC));
sithSoundMixer_bPlayingMci = 0;
int __sithSoundMixer_bPlayingMci_origValue = 0;
_memcpy(&sithSoundMixer_bPlayingMci, &__sithSoundMixer_bPlayingMci_origValue, sizeof(sithSoundMixer_bPlayingMci));
sithSoundMixer_bInitted = 0;
int __sithSoundMixer_bInitted_origValue = 0;
_memcpy(&sithSoundMixer_bInitted, &__sithSoundMixer_bInitted_origValue, sizeof(sithSoundMixer_bInitted));
sithSoundMixer_flt_835FD8 = 0.0f;
float __sithSoundMixer_flt_835FD8_origValue = 0.0f;
_memcpy(&sithSoundMixer_flt_835FD8, &__sithSoundMixer_flt_835FD8_origValue, sizeof(sithSoundMixer_flt_835FD8));
sithSoundMixer_bIsMuted = 0;
int __sithSoundMixer_bIsMuted_origValue = 0;
_memcpy(&sithSoundMixer_bIsMuted, &__sithSoundMixer_bIsMuted_origValue, sizeof(sithSoundMixer_bIsMuted));
float  __sithSoundMixer_musicVolume_origValue =  1.0f;
_memcpy(&sithSoundMixer_musicVolume, &__sithSoundMixer_musicVolume_origValue, sizeof(sithSoundMixer_musicVolume));
float  __sithSoundMixer_globalVolume_origValue =  1.0f;
_memcpy(&sithSoundMixer_globalVolume, &__sithSoundMixer_globalVolume_origValue, sizeof(sithSoundMixer_globalVolume));
sithSoundMixer_numSoundsAvailable2 = 0;
int __sithSoundMixer_numSoundsAvailable2_origValue = 0;
_memcpy(&sithSoundMixer_numSoundsAvailable2, &__sithSoundMixer_numSoundsAvailable2_origValue, sizeof(sithSoundMixer_numSoundsAvailable2));
sithSoundMixer_numSoundsAvailable = 0;
int __sithSoundMixer_numSoundsAvailable_origValue = 0;
_memcpy(&sithSoundMixer_numSoundsAvailable, &__sithSoundMixer_numSoundsAvailable_origValue, sizeof(sithSoundMixer_numSoundsAvailable));
_memset(&sithSoundMixer_aPlayingSounds, 0, sizeof(sithSoundMixer_aPlayingSounds));
_memset(&sithSoundMixer_aIdk, 0, sizeof(sithSoundMixer_aIdk));
sithSoundMixer_activeChannels = 0;
int __sithSoundMixer_activeChannels_origValue = 0;
_memcpy(&sithSoundMixer_activeChannels, &__sithSoundMixer_activeChannels_origValue, sizeof(sithSoundMixer_activeChannels));
sithSoundMixer_bOpened = 0;
int __sithSoundMixer_bOpened_origValue = 0;
_memcpy(&sithSoundMixer_bOpened, &__sithSoundMixer_bOpened_origValue, sizeof(sithSoundMixer_bOpened));
sithSoundMixer_pLastSectorSoundSector = NULL;
sithSector* __sithSoundMixer_pLastSectorSoundSector_origValue = NULL;
_memcpy(&sithSoundMixer_pLastSectorSoundSector, &__sithSoundMixer_pLastSectorSoundSector_origValue, sizeof(sithSoundMixer_pLastSectorSoundSector));
sithSoundMixer_dword_836BFC = 0;
int __sithSoundMixer_dword_836BFC_origValue = 0;
_memcpy(&sithSoundMixer_dword_836BFC, &__sithSoundMixer_dword_836BFC_origValue, sizeof(sithSoundMixer_dword_836BFC));
sithSoundMixer_trackFrom = 0;
int __sithSoundMixer_trackFrom_origValue = 0;
_memcpy(&sithSoundMixer_trackFrom, &__sithSoundMixer_trackFrom_origValue, sizeof(sithSoundMixer_trackFrom));
sithSoundMixer_trackTo = 0;
int __sithSoundMixer_trackTo_origValue = 0;
_memcpy(&sithSoundMixer_trackTo, &__sithSoundMixer_trackTo_origValue, sizeof(sithSoundMixer_trackTo));
sithSoundMixer_pPlayingSoundIdk = NULL;
sithPlayingSound* __sithSoundMixer_pPlayingSoundIdk_origValue = NULL;
_memcpy(&sithSoundMixer_pPlayingSoundIdk, &__sithSoundMixer_pPlayingSoundIdk_origValue, sizeof(sithSoundMixer_pPlayingSoundIdk));
sithSoundMixer_dword_836C00 = 0;
int __sithSoundMixer_dword_836C00_origValue = 0;
_memcpy(&sithSoundMixer_dword_836C00, &__sithSoundMixer_dword_836C00_origValue, sizeof(sithSoundMixer_dword_836C00));
int  __sithSoundMixer_nextSoundIdx_origValue =  1;
_memcpy(&sithSoundMixer_nextSoundIdx, &__sithSoundMixer_nextSoundIdx_origValue, sizeof(sithSoundMixer_nextSoundIdx));
sithSoundMixer_dword_836C04 = 0;
int __sithSoundMixer_dword_836C04_origValue = 0;
_memcpy(&sithSoundMixer_dword_836C04, &__sithSoundMixer_dword_836C04_origValue, sizeof(sithSoundMixer_dword_836C04));
sithSoundMixer_pFocusedThing = NULL;
sithThing* __sithSoundMixer_pFocusedThing_origValue = NULL;
_memcpy(&sithSoundMixer_pFocusedThing, &__sithSoundMixer_pFocusedThing_origValue, sizeof(sithSoundMixer_pFocusedThing));
int  __sithSound_maxDataLoaded_origValue =  0x400000;
_memcpy(&sithSound_maxDataLoaded, &__sithSound_maxDataLoaded_origValue, sizeof(sithSound_maxDataLoaded));
int  __sithSound_var3_origValue =  1;
_memcpy(&sithSound_var3, &__sithSound_var3_origValue, sizeof(sithSound_var3));
sithSound_curDataLoaded = 0;
int __sithSound_curDataLoaded_origValue = 0;
_memcpy(&sithSound_curDataLoaded, &__sithSound_curDataLoaded_origValue, sizeof(sithSound_curDataLoaded));
sithSound_bInit = 0;
int __sithSound_bInit_origValue = 0;
_memcpy(&sithSound_bInit, &__sithSound_bInit_origValue, sizeof(sithSound_bInit));
sithSound_hashtable = NULL;
stdHashTable* __sithSound_hashtable_origValue = NULL;
_memcpy(&sithSound_hashtable, &__sithSound_hashtable_origValue, sizeof(sithSound_hashtable));
sithSound_var4 = 0;
int __sithSound_var4_origValue = 0;
_memcpy(&sithSound_var4, &__sithSound_var4_origValue, sizeof(sithSound_var4));
sithSound_var5 = 0;
int __sithSound_var5_origValue = 0;
_memcpy(&sithSound_var5, &__sithSound_var5_origValue, sizeof(sithSound_var5));
_memset(&sithControl_inputFuncToControlType, 0, sizeof(sithControl_inputFuncToControlType));
_memset(&sithControl_aInputFuncToKeyinfo, 0, sizeof(sithControl_aInputFuncToKeyinfo));
_memset(&sithControl_msIdle, 0, sizeof(sithControl_msIdle));
sithControl_bInitted = 0;
int __sithControl_bInitted_origValue = 0;
_memcpy(&sithControl_bInitted, &__sithControl_bInitted_origValue, sizeof(sithControl_bInitted));
sithControl_bOpened = 0;
int __sithControl_bOpened_origValue = 0;
_memcpy(&sithControl_bOpened, &__sithControl_bOpened_origValue, sizeof(sithControl_bOpened));
_memset(&sithControl_aHandlers, 0, sizeof(sithControl_aHandlers));
sithControl_numHandlers = 0;
int __sithControl_numHandlers_origValue = 0;
_memcpy(&sithControl_numHandlers, &__sithControl_numHandlers_origValue, sizeof(sithControl_numHandlers));
sithControl_death_msgtimer = 0;
int __sithControl_death_msgtimer_origValue = 0;
_memcpy(&sithControl_death_msgtimer, &__sithControl_death_msgtimer_origValue, sizeof(sithControl_death_msgtimer));
rdVector3  __sithControl_vec3_54A570_origValue =  {0.0, -1.0, 0.0};
_memcpy(&sithControl_vec3_54A570, &__sithControl_vec3_54A570_origValue, sizeof(sithControl_vec3_54A570));
float  __sithControl_flt_54A57C_origValue =  0.2f;
_memcpy(&sithControl_flt_54A57C, &__sithControl_flt_54A57C_origValue, sizeof(sithControl_flt_54A57C));
_memset(&sithGamesave_func1, 0, sizeof(sithGamesave_func1));
_memset(&sithGamesave_func2, 0, sizeof(sithGamesave_func2));
_memset(&sithGamesave_func3, 0, sizeof(sithGamesave_func3));
_memset(&sithGamesave_funcWrite, 0, sizeof(sithGamesave_funcWrite));
_memset(&sithGamesave_funcRead, 0, sizeof(sithGamesave_funcRead));
_memset(&sithGamesave_autosave_fname, 0, sizeof(sithGamesave_autosave_fname));
_memset(&sithGamesave_currentState, 0, sizeof(sithGamesave_currentState));
sithGamesave_dword_835914 = 0;
int __sithGamesave_dword_835914_origValue = 0;
_memcpy(&sithGamesave_dword_835914, &__sithGamesave_dword_835914_origValue, sizeof(sithGamesave_dword_835914));
_memset(&sithGamesave_fpath, 0, sizeof(sithGamesave_fpath));
_memset(&sithGamesave_wsaveName, 0, sizeof(sithGamesave_wsaveName));
_memset(&sithGamesave_saveName, 0, sizeof(sithGamesave_saveName));
_memset(&sithGamesave_headerTmp, 0, sizeof(sithGamesave_headerTmp));
rdCamera_pCurCamera = NULL;
rdCamera* __rdCamera_pCurCamera_origValue = NULL;
_memcpy(&rdCamera_pCurCamera, &__rdCamera_pCurCamera_origValue, sizeof(rdCamera_pCurCamera));
_memset(&rdCamera_camMatrix, 0, sizeof(rdCamera_camMatrix));
sithNet_MultiModeFlags = 0;
int __sithNet_MultiModeFlags_origValue = 0;
_memcpy(&sithNet_MultiModeFlags, &__sithNet_MultiModeFlags_origValue, sizeof(sithNet_MultiModeFlags));
sithNet_scorelimit = 0;
int __sithNet_scorelimit_origValue = 0;
_memcpy(&sithNet_scorelimit, &__sithNet_scorelimit_origValue, sizeof(sithNet_scorelimit));
_memset(&sithNet_teamScore, 0, sizeof(sithNet_teamScore));
sithNet_multiplayer_timelimit = 0;
int __sithNet_multiplayer_timelimit_origValue = 0;
_memcpy(&sithNet_multiplayer_timelimit, &__sithNet_multiplayer_timelimit_origValue, sizeof(sithNet_multiplayer_timelimit));
sithMulti_multiplayerTimelimit = 0;
int __sithMulti_multiplayerTimelimit_origValue = 0;
_memcpy(&sithMulti_multiplayerTimelimit, &__sithMulti_multiplayerTimelimit_origValue, sizeof(sithMulti_multiplayerTimelimit));
sithNet_isMulti = 0;
int __sithNet_isMulti_origValue = 0;
_memcpy(&sithNet_isMulti, &__sithNet_isMulti_origValue, sizeof(sithNet_isMulti));
sithNet_isServer = 0;
int __sithNet_isServer_origValue = 0;
_memcpy(&sithNet_isServer, &__sithNet_isServer_origValue, sizeof(sithNet_isServer));
sithMulti_bTimelimitMet = 0;
int __sithMulti_bTimelimitMet_origValue = 0;
_memcpy(&sithMulti_bTimelimitMet, &__sithMulti_bTimelimitMet_origValue, sizeof(sithMulti_bTimelimitMet));
sithNet_serverNetId = 0;
int __sithNet_serverNetId_origValue = 0;
_memcpy(&sithNet_serverNetId, &__sithNet_serverNetId_origValue, sizeof(sithNet_serverNetId));
_memset(&sithNet_things, 0, sizeof(sithNet_things));
sithNet_thingsIdx = 0;
int __sithNet_thingsIdx_origValue = 0;
_memcpy(&sithNet_thingsIdx, &__sithNet_thingsIdx_origValue, sizeof(sithNet_thingsIdx));
sithNet_syncIdx = 0;
int __sithNet_syncIdx_origValue = 0;
_memcpy(&sithNet_syncIdx, &__sithNet_syncIdx_origValue, sizeof(sithNet_syncIdx));
_memset(&sithNet_aSyncFlags, 0, sizeof(sithNet_aSyncFlags));
_memset(&sithNet_aSyncThings, 0, sizeof(sithNet_aSyncThings));
int  __sithNet_tickrate_origValue =  180;
_memcpy(&sithNet_tickrate, &__sithNet_tickrate_origValue, sizeof(sithNet_tickrate));
sithNet_dword_8C4BA8 = 0;
int __sithNet_dword_8C4BA8_origValue = 0;
_memcpy(&sithNet_dword_8C4BA8, &__sithNet_dword_8C4BA8_origValue, sizeof(sithNet_dword_8C4BA8));
sithNet_dword_83262C = 0;
int __sithNet_dword_83262C_origValue = 0;
_memcpy(&sithNet_dword_83262C, &__sithNet_dword_83262C_origValue, sizeof(sithNet_dword_83262C));
sithMulti_leaveJoinType = 0;
int __sithMulti_leaveJoinType_origValue = 0;
_memcpy(&sithMulti_leaveJoinType, &__sithMulti_leaveJoinType_origValue, sizeof(sithMulti_leaveJoinType));
sithNet_checksum = 0;
int __sithNet_checksum_origValue = 0;
_memcpy(&sithNet_checksum, &__sithNet_checksum_origValue, sizeof(sithNet_checksum));
sithNet_bNeedsFullThingSyncForLeaveJoin = 0;
int __sithNet_bNeedsFullThingSyncForLeaveJoin_origValue = 0;
_memcpy(&sithNet_bNeedsFullThingSyncForLeaveJoin, &__sithNet_bNeedsFullThingSyncForLeaveJoin_origValue, sizeof(sithNet_bNeedsFullThingSyncForLeaveJoin));
sithMulti_sendto_id = 0;
int __sithMulti_sendto_id_origValue = 0;
_memcpy(&sithMulti_sendto_id, &__sithMulti_sendto_id_origValue, sizeof(sithMulti_sendto_id));
sithNet_bSyncScores = 0;
int __sithNet_bSyncScores_origValue = 0;
_memcpy(&sithNet_bSyncScores, &__sithNet_bSyncScores_origValue, sizeof(sithNet_bSyncScores));
sithNet_dword_832620 = 0;
int __sithNet_dword_832620_origValue = 0;
_memcpy(&sithNet_dword_832620, &__sithNet_dword_832620_origValue, sizeof(sithNet_dword_832620));
float  __sithOverlayMap_flMapSize_origValue =  100.0;
_memcpy(&sithOverlayMap_flMapSize, &__sithOverlayMap_flMapSize_origValue, sizeof(sithOverlayMap_flMapSize));
_memset(&sithOverlayMap_matrix, 0, sizeof(sithOverlayMap_matrix));
sithOverlayMap_pPlayer = NULL;
sithThing* __sithOverlayMap_pPlayer_origValue = NULL;
_memcpy(&sithOverlayMap_pPlayer, &__sithOverlayMap_pPlayer_origValue, sizeof(sithOverlayMap_pPlayer));
sithOverlayMap_pCanvas = NULL;
rdCanvas* __sithOverlayMap_pCanvas_origValue = NULL;
_memcpy(&sithOverlayMap_pCanvas, &__sithOverlayMap_pCanvas_origValue, sizeof(sithOverlayMap_pCanvas));
sithOverlayMap_x1 = 0;
int __sithOverlayMap_x1_origValue = 0;
_memcpy(&sithOverlayMap_x1, &__sithOverlayMap_x1_origValue, sizeof(sithOverlayMap_x1));
sithOverlayMap_y1 = 0;
int __sithOverlayMap_y1_origValue = 0;
_memcpy(&sithOverlayMap_y1, &__sithOverlayMap_y1_origValue, sizeof(sithOverlayMap_y1));
_memset(&sithOverlayMap_inst, 0, sizeof(sithOverlayMap_inst));
sithOverlayMap_bShowMap = 0;
int __sithOverlayMap_bShowMap_origValue = 0;
_memcpy(&sithOverlayMap_bShowMap, &__sithOverlayMap_bShowMap_origValue, sizeof(sithOverlayMap_bShowMap));
sithOverlayMap_bInitted = 0;
int __sithOverlayMap_bInitted_origValue = 0;
_memcpy(&sithOverlayMap_bInitted, &__sithOverlayMap_bInitted_origValue, sizeof(sithOverlayMap_bInitted));
sithSoundClass_hashtable = NULL;
stdHashTable* __sithSoundClass_hashtable_origValue = NULL;
_memcpy(&sithSoundClass_hashtable, &__sithSoundClass_hashtable_origValue, sizeof(sithSoundClass_hashtable));
sithSoundClass_nameToKeyHashtable = NULL;
stdHashTable* __sithSoundClass_nameToKeyHashtable_origValue = NULL;
_memcpy(&sithSoundClass_nameToKeyHashtable, &__sithSoundClass_nameToKeyHashtable_origValue, sizeof(sithSoundClass_nameToKeyHashtable));
sithTemplate_alloc = NULL;
void* __sithTemplate_alloc_origValue = NULL;
_memcpy(&sithTemplate_alloc, &__sithTemplate_alloc_origValue, sizeof(sithTemplate_alloc));
sithTemplate_hashmap = NULL;
stdHashTable* __sithTemplate_hashmap_origValue = NULL;
_memcpy(&sithTemplate_hashmap, &__sithTemplate_hashmap_origValue, sizeof(sithTemplate_hashmap));
sithTemplate_count = 0;
int __sithTemplate_count_origValue = 0;
_memcpy(&sithTemplate_count, &__sithTemplate_count_origValue, sizeof(sithTemplate_count));
sithTemplate_oldHashtable = NULL;
stdHashTable* __sithTemplate_oldHashtable_origValue = NULL;
_memcpy(&sithTemplate_oldHashtable, &__sithTemplate_oldHashtable_origValue, sizeof(sithTemplate_oldHashtable));
_memset(&activeEdgeTail, 0, sizeof(activeEdgeTail));
_memset(&activeEdgeHead, 0, sizeof(activeEdgeHead));
_memset(&apNewActiveEdges, 0, sizeof(apNewActiveEdges));
_memset(&apRemoveActiveEdges, 0, sizeof(apRemoveActiveEdges));
yMinEdge = 0;
int __yMinEdge_origValue = 0;
_memcpy(&yMinEdge, &__yMinEdge_origValue, sizeof(yMinEdge));
yMaxEdge = 0;
int __yMaxEdge_origValue = 0;
_memcpy(&yMaxEdge, &__yMaxEdge_origValue, sizeof(yMaxEdge));
numActiveSpans = 0;
int __numActiveSpans_origValue = 0;
_memcpy(&numActiveSpans, &__numActiveSpans_origValue, sizeof(numActiveSpans));
numActiveFaces = 0;
int __numActiveFaces_origValue = 0;
_memcpy(&numActiveFaces, &__numActiveFaces_origValue, sizeof(numActiveFaces));
numActiveEdges = 0;
int __numActiveEdges_origValue = 0;
_memcpy(&numActiveEdges, &__numActiveEdges_origValue, sizeof(numActiveEdges));
_memset(&aActiveEdges, 0, sizeof(aActiveEdges));
rdActive_drawnFaces = 0;
int __rdActive_drawnFaces_origValue = 0;
_memcpy(&rdActive_drawnFaces, &__rdActive_drawnFaces_origValue, sizeof(rdActive_drawnFaces));
sithMain_bEndLevel = 0;
int __sithMain_bEndLevel_origValue = 0;
_memcpy(&sithMain_bEndLevel, &__sithMain_bEndLevel_origValue, sizeof(sithMain_bEndLevel));
sithMain_bInitialized = 0;
int __sithMain_bInitialized_origValue = 0;
_memcpy(&sithMain_bInitialized, &__sithMain_bInitialized_origValue, sizeof(sithMain_bInitialized));
sithMain_bOpened = 0;
int __sithMain_bOpened_origValue = 0;
_memcpy(&sithMain_bOpened, &__sithMain_bOpened_origValue, sizeof(sithMain_bOpened));
sithSurface_numAvail = 0;
int __sithSurface_numAvail_origValue = 0;
_memcpy(&sithSurface_numAvail, &__sithSurface_numAvail_origValue, sizeof(sithSurface_numAvail));
_memset(&sithSurface_aAvail, 0, sizeof(sithSurface_aAvail));
sithSurface_numSurfaces = 0;
int __sithSurface_numSurfaces_origValue = 0;
_memcpy(&sithSurface_numSurfaces, &__sithSurface_numSurfaces_origValue, sizeof(sithSurface_numSurfaces));
_memset(&sithSurface_aSurfaces, 0, sizeof(sithSurface_aSurfaces));
sithSurface_bOpened = 0;
int __sithSurface_bOpened_origValue = 0;
_memcpy(&sithSurface_bOpened, &__sithSurface_bOpened_origValue, sizeof(sithSurface_bOpened));
uint32_t  __sithSurface_byte_8EE668_origValue =  0;
_memcpy(&sithSurface_byte_8EE668, &__sithSurface_byte_8EE668_origValue, sizeof(sithSurface_byte_8EE668));
sithSurface_numSurfaces_0 = 0;
int __sithSurface_numSurfaces_0_origValue = 0;
_memcpy(&sithSurface_numSurfaces_0, &__sithSurface_numSurfaces_0_origValue, sizeof(sithSurface_numSurfaces_0));
_memset(&pMaterialsLoader, 0, sizeof(pMaterialsLoader));
_memset(&pMaterialsUnloader, 0, sizeof(pMaterialsUnloader));
sithSprite_hashmap = NULL;
stdHashTable* __sithSprite_hashmap_origValue = NULL;
_memcpy(&sithSprite_hashmap, &__sithSprite_hashmap_origValue, sizeof(sithSprite_hashmap));
_memset(&Window_drawAndFlip, 0, sizeof(Window_drawAndFlip));
_memset(&Window_setCooperativeLevel, 0, sizeof(Window_setCooperativeLevel));
_memset(&Window_ext_handlers, 0, sizeof(Window_ext_handlers));
_memset(&Window_aDialogHwnds, 0, sizeof(Window_aDialogHwnds));
_memset(&DebugGui_aIdk, 0, sizeof(DebugGui_aIdk));
DebugGui_idk = 0;
int __DebugGui_idk_origValue = 0;
_memcpy(&DebugGui_idk, &__DebugGui_idk_origValue, sizeof(DebugGui_idk));
DebugGui_some_line_amt = 0;
int __DebugGui_some_line_amt_origValue = 0;
_memcpy(&DebugGui_some_line_amt, &__DebugGui_some_line_amt_origValue, sizeof(DebugGui_some_line_amt));
DebugGui_some_num_lines = 0;
int __DebugGui_some_num_lines_origValue = 0;
_memcpy(&DebugGui_some_num_lines, &__DebugGui_some_num_lines_origValue, sizeof(DebugGui_some_num_lines));
_memset(&DebugLog_buffer, 0, sizeof(DebugLog_buffer));
sithConsole_aCmds = NULL;
stdDebugConsoleCmd* __sithConsole_aCmds_origValue = NULL;
_memcpy(&sithConsole_aCmds, &__sithConsole_aCmds_origValue, sizeof(sithConsole_aCmds));
sithConsole_pCmdHashtable = NULL;
stdHashTable* __sithConsole_pCmdHashtable_origValue = NULL;
_memcpy(&sithConsole_pCmdHashtable, &__sithConsole_pCmdHashtable_origValue, sizeof(sithConsole_pCmdHashtable));
sithConsole_bOpened = 0;
int __sithConsole_bOpened_origValue = 0;
_memcpy(&sithConsole_bOpened, &__sithConsole_bOpened_origValue, sizeof(sithConsole_bOpened));
sithConsole_bInitted = 0;
int __sithConsole_bInitted_origValue = 0;
_memcpy(&sithConsole_bInitted, &__sithConsole_bInitted_origValue, sizeof(sithConsole_bInitted));
sithConsole_maxCmds = 0;
int __sithConsole_maxCmds_origValue = 0;
_memcpy(&sithConsole_maxCmds, &__sithConsole_maxCmds_origValue, sizeof(sithConsole_maxCmds));
sithConsole_numRegisteredCmds = 0;
int __sithConsole_numRegisteredCmds_origValue = 0;
_memcpy(&sithConsole_numRegisteredCmds, &__sithConsole_numRegisteredCmds_origValue, sizeof(sithConsole_numRegisteredCmds));
_memset(&DebugGui_maxLines, 0, sizeof(DebugGui_maxLines));
_memset(&DebugGui_fnPrint, 0, sizeof(DebugGui_fnPrint));
_memset(&DebugGui_fnPrintUniStr, 0, sizeof(DebugGui_fnPrintUniStr));
sithConsole_alertSound = NULL;
stdSound_buffer_t* __sithConsole_alertSound_origValue = NULL;
_memcpy(&sithConsole_alertSound, &__sithConsole_alertSound_origValue, sizeof(sithConsole_alertSound));
_memset(&sithConsole_idk2, 0, sizeof(sithConsole_idk2));
_memset(&d3d_maxVertices, 0, sizeof(d3d_maxVertices));
d3d_device_ptr = NULL;
d3d_device* __d3d_device_ptr_origValue = NULL;
_memcpy(&d3d_device_ptr, &__d3d_device_ptr_origValue, sizeof(d3d_device_ptr));
_memset(&std3D_rectViewIdk, 0, sizeof(std3D_rectViewIdk));
_memset(&std3D_aViewIdk, 0, sizeof(std3D_aViewIdk));
_memset(&std3D_aViewTris, 0, sizeof(std3D_aViewTris));
int  __std3D_gpuMaxTexSizeMaybe_origValue =  1;
_memcpy(&std3D_gpuMaxTexSizeMaybe, &__std3D_gpuMaxTexSizeMaybe_origValue, sizeof(std3D_gpuMaxTexSizeMaybe));
int  __std3D_dword_53D66C_origValue =  1;
_memcpy(&std3D_dword_53D66C, &__std3D_dword_53D66C_origValue, sizeof(std3D_dword_53D66C));
int  __std3D_dword_53D670_origValue =  0x100;
_memcpy(&std3D_dword_53D670, &__std3D_dword_53D670_origValue, sizeof(std3D_dword_53D670));
int  __std3D_dword_53D674_origValue =  0x100;
_memcpy(&std3D_dword_53D674, &__std3D_dword_53D674_origValue, sizeof(std3D_dword_53D674));
_memset(&std3D_renderList, 0, sizeof(std3D_renderList));
stdComm_dword_8321F8 = 0;
int __stdComm_dword_8321F8_origValue = 0;
_memcpy(&stdComm_dword_8321F8, &__stdComm_dword_8321F8_origValue, sizeof(stdComm_dword_8321F8));
stdComm_bInitted = 0;
int __stdComm_bInitted_origValue = 0;
_memcpy(&stdComm_bInitted, &__stdComm_bInitted_origValue, sizeof(stdComm_bInitted));
stdComm_dword_8321F0 = 0;
int __stdComm_dword_8321F0_origValue = 0;
_memcpy(&stdComm_dword_8321F0, &__stdComm_dword_8321F0_origValue, sizeof(stdComm_dword_8321F0));
stdComm_dword_8321F4 = 0;
int __stdComm_dword_8321F4_origValue = 0;
_memcpy(&stdComm_dword_8321F4, &__stdComm_dword_8321F4_origValue, sizeof(stdComm_dword_8321F4));
stdComm_dplayIdSelf = 0;
int __stdComm_dplayIdSelf_origValue = 0;
_memcpy(&stdComm_dplayIdSelf, &__stdComm_dplayIdSelf_origValue, sizeof(stdComm_dplayIdSelf));
stdComm_dword_832204 = 0;
int __stdComm_dword_832204_origValue = 0;
_memcpy(&stdComm_dword_832204, &__stdComm_dword_832204_origValue, sizeof(stdComm_dword_832204));
stdComm_dword_832208 = 0;
int __stdComm_dword_832208_origValue = 0;
_memcpy(&stdComm_dword_832208, &__stdComm_dword_832208_origValue, sizeof(stdComm_dword_832208));
stdComm_currentBigSyncStage = 0;
int __stdComm_currentBigSyncStage_origValue = 0;
_memcpy(&stdComm_currentBigSyncStage, &__stdComm_currentBigSyncStage_origValue, sizeof(stdComm_currentBigSyncStage));
stdComm_dword_8321E0 = 0;
int __stdComm_dword_8321E0_origValue = 0;
_memcpy(&stdComm_dword_8321E0, &__stdComm_dword_8321E0_origValue, sizeof(stdComm_dword_8321E0));
stdComm_bIsServer = 0;
int __stdComm_bIsServer_origValue = 0;
_memcpy(&stdComm_bIsServer, &__stdComm_bIsServer_origValue, sizeof(stdComm_bIsServer));
stdComm_dword_8321E8 = 0;
int __stdComm_dword_8321E8_origValue = 0;
_memcpy(&stdComm_dword_8321E8, &__stdComm_dword_8321E8_origValue, sizeof(stdComm_dword_8321E8));
_memset(&stdComm_waIdk, 0, sizeof(stdComm_waIdk));
stdComm_dword_8321DC = 0;
int __stdComm_dword_8321DC_origValue = 0;
_memcpy(&stdComm_dword_8321DC, &__stdComm_dword_8321DC_origValue, sizeof(stdComm_dword_8321DC));
stdComm_dword_832200 = 0;
int __stdComm_dword_832200_origValue = 0;
_memcpy(&stdComm_dword_832200, &__stdComm_dword_832200_origValue, sizeof(stdComm_dword_832200));
stdComm_dword_832210 = 0;
int __stdComm_dword_832210_origValue = 0;
_memcpy(&stdComm_dword_832210, &__stdComm_dword_832210_origValue, sizeof(stdComm_dword_832210));
_memset(&stdComm_cogMsgTmp, 0, sizeof(stdComm_cogMsgTmp));
_memset(&stdMci_mciId, 0, sizeof(stdMci_mciId));
stdMci_dwVolume = 0;
int __stdMci_dwVolume_origValue = 0;
_memcpy(&stdMci_dwVolume, &__stdMci_dwVolume_origValue, sizeof(stdMci_dwVolume));
stdMci_bInitted = 0;
int __stdMci_bInitted_origValue = 0;
_memcpy(&stdMci_bInitted, &__stdMci_bInitted_origValue, sizeof(stdMci_bInitted));
stdMci_uDeviceID = 0;
int __stdMci_uDeviceID_origValue = 0;
_memcpy(&stdMci_uDeviceID, &__stdMci_uDeviceID_origValue, sizeof(stdMci_uDeviceID));
wuRegistry_bInitted = 0;
int __wuRegistry_bInitted_origValue = 0;
_memcpy(&wuRegistry_bInitted, &__wuRegistry_bInitted_origValue, sizeof(wuRegistry_bInitted));
_memset(&wuRegistry_lpClass, 0, sizeof(wuRegistry_lpClass));
_memset(&wuRegistry_byte_855EB4, 0, sizeof(wuRegistry_byte_855EB4));
_memset(&wuRegistry_hKey, 0, sizeof(wuRegistry_hKey));
_memset(&wuRegistry_lpSubKey, 0, sizeof(wuRegistry_lpSubKey));
_memset(&WinIdk_aDplayGuid, 0, sizeof(WinIdk_aDplayGuid));
_memset(&stdDisplay_aDevices, 0, sizeof(stdDisplay_aDevices));
stdDisplay_gammaTableLen = 0;
int __stdDisplay_gammaTableLen_origValue = 0;
_memcpy(&stdDisplay_gammaTableLen, &__stdDisplay_gammaTableLen_origValue, sizeof(stdDisplay_gammaTableLen));
stdDisplay_paGammaTable = NULL;
double* __stdDisplay_paGammaTable_origValue = NULL;
_memcpy(&stdDisplay_paGammaTable, &__stdDisplay_paGammaTable_origValue, sizeof(stdDisplay_paGammaTable));
_memset(&stdDisplay_gammaPalette, 0, sizeof(stdDisplay_gammaPalette));
stdDisplay_pCurDevice = NULL;
stdVideoDevice* __stdDisplay_pCurDevice_origValue = NULL;
_memcpy(&stdDisplay_pCurDevice, &__stdDisplay_pCurDevice_origValue, sizeof(stdDisplay_pCurDevice));
stdDisplay_pCurVideoMode = NULL;
stdVideoMode* __stdDisplay_pCurVideoMode_origValue = NULL;
_memcpy(&stdDisplay_pCurVideoMode, &__stdDisplay_pCurVideoMode_origValue, sizeof(stdDisplay_pCurVideoMode));
stdDisplay_bStartup = 0;
int __stdDisplay_bStartup_origValue = 0;
_memcpy(&stdDisplay_bStartup, &__stdDisplay_bStartup_origValue, sizeof(stdDisplay_bStartup));
stdDisplay_bOpen = 0;
int __stdDisplay_bOpen_origValue = 0;
_memcpy(&stdDisplay_bOpen, &__stdDisplay_bOpen_origValue, sizeof(stdDisplay_bOpen));
stdDisplay_bModeSet = 0;
int __stdDisplay_bModeSet_origValue = 0;
_memcpy(&stdDisplay_bModeSet, &__stdDisplay_bModeSet_origValue, sizeof(stdDisplay_bModeSet));
stdDisplay_numVideoModes = 0;
int __stdDisplay_numVideoModes_origValue = 0;
_memcpy(&stdDisplay_numVideoModes, &__stdDisplay_numVideoModes_origValue, sizeof(stdDisplay_numVideoModes));
stdDisplay_bPaged = 0;
int __stdDisplay_bPaged_origValue = 0;
_memcpy(&stdDisplay_bPaged, &__stdDisplay_bPaged_origValue, sizeof(stdDisplay_bPaged));
_memset(&stdDisplay_tmpGammaPal, 0, sizeof(stdDisplay_tmpGammaPal));
stdDisplay_gammaIdx = 0;
int __stdDisplay_gammaIdx_origValue = 0;
_memcpy(&stdDisplay_gammaIdx, &__stdDisplay_gammaIdx_origValue, sizeof(stdDisplay_gammaIdx));
_memset(&word_860800, 0, sizeof(word_860800));
_memset(&word_860802, 0, sizeof(word_860802));
_memset(&word_860804, 0, sizeof(word_860804));
_memset(&word_860806, 0, sizeof(word_860806));
int  __stdControl_bReadMouse_origValue =  1;
_memcpy(&stdControl_bReadMouse, &__stdControl_bReadMouse_origValue, sizeof(stdControl_bReadMouse));
float  __stdControl_updateKHz_origValue =  1.0f;
_memcpy(&stdControl_updateKHz, &__stdControl_updateKHz_origValue, sizeof(stdControl_updateKHz));
float  __stdControl_updateHz_origValue =  1.0f;
_memcpy(&stdControl_updateHz, &__stdControl_updateHz_origValue, sizeof(stdControl_updateHz));
float  __stdControl_mouseXSensitivity_origValue =  1.0f;
_memcpy(&stdControl_mouseXSensitivity, &__stdControl_mouseXSensitivity_origValue, sizeof(stdControl_mouseXSensitivity));
float  __stdControl_mouseYSensitivity_origValue =  1.0f;
_memcpy(&stdControl_mouseYSensitivity, &__stdControl_mouseYSensitivity_origValue, sizeof(stdControl_mouseYSensitivity));
float  __stdControl_mouseZSensitivity_origValue =  1.0f;
_memcpy(&stdControl_mouseZSensitivity, &__stdControl_mouseZSensitivity_origValue, sizeof(stdControl_mouseZSensitivity));
_memset(&stdControl_aAxisEnabled, 0, sizeof(stdControl_aAxisEnabled));
_memset(&stdControl_aAxisPos, 0, sizeof(stdControl_aAxisPos));
_memset(&stdControl_aInput1, 0, sizeof(stdControl_aInput1));
_memset(&stdControl_aKeyInfo, 0, sizeof(stdControl_aKeyInfo));
_memset(&stdControl_aAxisConnected, 0, sizeof(stdControl_aAxisConnected));
_memset(&stdControl_aInput2, 0, sizeof(stdControl_aInput2));
stdControl_bStartup = 0;
int __stdControl_bStartup_origValue = 0;
_memcpy(&stdControl_bStartup, &__stdControl_bStartup_origValue, sizeof(stdControl_bStartup));
stdControl_bOpen = 0;
int __stdControl_bOpen_origValue = 0;
_memcpy(&stdControl_bOpen, &__stdControl_bOpen_origValue, sizeof(stdControl_bOpen));
stdControl_bDisableKeyboard = 0;
int __stdControl_bDisableKeyboard_origValue = 0;
_memcpy(&stdControl_bDisableKeyboard, &__stdControl_bDisableKeyboard_origValue, sizeof(stdControl_bDisableKeyboard));
stdControl_bControlsIdle = 0;
int __stdControl_bControlsIdle_origValue = 0;
_memcpy(&stdControl_bControlsIdle, &__stdControl_bControlsIdle_origValue, sizeof(stdControl_bControlsIdle));
stdControl_bControlsActive = 0;
int __stdControl_bControlsActive_origValue = 0;
_memcpy(&stdControl_bControlsActive, &__stdControl_bControlsActive_origValue, sizeof(stdControl_bControlsActive));
stdControl_ppDI = NULL;
void* __stdControl_ppDI_origValue = NULL;
_memcpy(&stdControl_ppDI, &__stdControl_ppDI_origValue, sizeof(stdControl_ppDI));
stdControl_mouseDirectInputDevice = NULL;
void* __stdControl_mouseDirectInputDevice_origValue = NULL;
_memcpy(&stdControl_mouseDirectInputDevice, &__stdControl_mouseDirectInputDevice_origValue, sizeof(stdControl_mouseDirectInputDevice));
stdControl_keyboardIDirectInputDevice = NULL;
void* __stdControl_keyboardIDirectInputDevice_origValue = NULL;
_memcpy(&stdControl_keyboardIDirectInputDevice, &__stdControl_keyboardIDirectInputDevice_origValue, sizeof(stdControl_keyboardIDirectInputDevice));
stdControl_bHasJoysticks = 0;
int __stdControl_bHasJoysticks_origValue = 0;
_memcpy(&stdControl_bHasJoysticks, &__stdControl_bHasJoysticks_origValue, sizeof(stdControl_bHasJoysticks));
_memset(&stdControl_curReadTime, 0, sizeof(stdControl_curReadTime));
_memset(&stdControl_msLast, 0, sizeof(stdControl_msLast));
_memset(&stdControl_msDelta, 0, sizeof(stdControl_msDelta));
_memset(&stdControl_dwLastMouseX, 0, sizeof(stdControl_dwLastMouseX));
_memset(&stdControl_dwLastMouseY, 0, sizeof(stdControl_dwLastMouseY));
_memset(&stdControl_aJoystickEnabled, 0, sizeof(stdControl_aJoystickEnabled));
_memset(&stdControl_aJoystickExists, 0, sizeof(stdControl_aJoystickExists));
_memset(&stdControl_aJoysticks, 0, sizeof(stdControl_aJoysticks));
_memset(&stdControl_aJoystickMaxButtons, 0, sizeof(stdControl_aJoystickMaxButtons));
Windows_installType = 0;
int __Windows_installType_origValue = 0;
_memcpy(&Windows_installType, &__Windows_installType_origValue, sizeof(Windows_installType));
uint8_t __Video_aGammaTable_origValue[80]  =  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x17, 0x5D, 0x74, 0xD1, 0x45, 0x17, 0xED, 0x3F, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xEA, 0x3F, 0xB7, 0x6D, 0xDB, 0xB6, 0x6D, 0xDB, 0xE6, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE4, 0x3F, 0x72, 0x1C, 0xC7, 0x71, 0x1C, 0xC7, 0xE1, 0x3F, 0x79, 0x0D, 0xE5, 0x35, 0x94, 0xD7, 0xE0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0x9E, 0xE7, 0x79, 0x9E, 0xE7, 0x79, 0xDE, 0x3F, 0xBE, 0xE9, 0x4D, 0x6F, 0x7A, 0xD3, 0xDB, 0x3F};
_memcpy(&Video_aGammaTable, &__Video_aGammaTable_origValue, sizeof(Video_aGammaTable));
int  __Video_fillColor_origValue =  0;
_memcpy(&Video_fillColor, &__Video_fillColor_origValue, sizeof(Video_fillColor));
_memset(&Video_modeStruct, 0, sizeof(Video_modeStruct));
_memset(&Video_otherBuf, 0, sizeof(Video_otherBuf));
Video_dword_866D78 = 0;
int __Video_dword_866D78_origValue = 0;
_memcpy(&Video_dword_866D78, &__Video_dword_866D78_origValue, sizeof(Video_dword_866D78));
Video_curMode = 0;
int __Video_curMode_origValue = 0;
_memcpy(&Video_curMode, &__Video_curMode_origValue, sizeof(Video_curMode));
_memset(&Video_renderSurface, 0, sizeof(Video_renderSurface));
_memset(&Video_menuBuffer, 0, sizeof(Video_menuBuffer));
Video_pOtherBuf = NULL;
stdVBuffer* __Video_pOtherBuf_origValue = NULL;
_memcpy(&Video_pOtherBuf, &__Video_pOtherBuf_origValue, sizeof(Video_pOtherBuf));
Video_pMenuBuffer = NULL;
stdVBuffer* __Video_pMenuBuffer_origValue = NULL;
_memcpy(&Video_pMenuBuffer, &__Video_pMenuBuffer_origValue, sizeof(Video_pMenuBuffer));
Video_bInitted = 0;
int __Video_bInitted_origValue = 0;
_memcpy(&Video_bInitted, &__Video_bInitted_origValue, sizeof(Video_bInitted));
Video_bOpened = 0;
int __Video_bOpened_origValue = 0;
_memcpy(&Video_bOpened, &__Video_bOpened_origValue, sizeof(Video_bOpened));
Video_flt_55289C = 0.0f;
float __Video_flt_55289C_origValue = 0.0f;
_memcpy(&Video_flt_55289C, &__Video_flt_55289C_origValue, sizeof(Video_flt_55289C));
Video_dword_5528A0 = 0;
int __Video_dword_5528A0_origValue = 0;
_memcpy(&Video_dword_5528A0, &__Video_dword_5528A0_origValue, sizeof(Video_dword_5528A0));
Video_dword_5528A4 = 0;
int __Video_dword_5528A4_origValue = 0;
_memcpy(&Video_dword_5528A4, &__Video_dword_5528A4_origValue, sizeof(Video_dword_5528A4));
Video_dword_5528A8 = 0;
int __Video_dword_5528A8_origValue = 0;
_memcpy(&Video_dword_5528A8, &__Video_dword_5528A8_origValue, sizeof(Video_dword_5528A8));
Video_lastTimeMsec = 0;
int __Video_lastTimeMsec_origValue = 0;
_memcpy(&Video_lastTimeMsec, &__Video_lastTimeMsec_origValue, sizeof(Video_lastTimeMsec));
Video_dword_5528B0 = 0;
int __Video_dword_5528B0_origValue = 0;
_memcpy(&Video_dword_5528B0, &__Video_dword_5528B0_origValue, sizeof(Video_dword_5528B0));
Video_pVbufIdk = NULL;
stdVBuffer* __Video_pVbufIdk_origValue = NULL;
_memcpy(&Video_pVbufIdk, &__Video_pVbufIdk_origValue, sizeof(Video_pVbufIdk));
Video_pCanvas = NULL;
rdCanvas* __Video_pCanvas_origValue = NULL;
_memcpy(&Video_pCanvas, &__Video_pCanvas_origValue, sizeof(Video_pCanvas));
_memset(&Video_aPalette, 0, sizeof(Video_aPalette));
_memset(&Video_format, 0, sizeof(Video_format));
_memset(&Video_format2, 0, sizeof(Video_format2));
_memset(&Video_modeStruct2, 0, sizeof(Video_modeStruct2));
_memset(&Video_bufIdk, 0, sizeof(Video_bufIdk));
_memset(&stdConsole_foregroundAttr, 0, sizeof(stdConsole_foregroundAttr));
_memset(&stdConsole_wAttributes, 0, sizeof(stdConsole_wAttributes));
stdConsole_cursorHidden = 0;
int __stdConsole_cursorHidden_origValue = 0;
_memcpy(&stdConsole_cursorHidden, &__stdConsole_cursorHidden_origValue, sizeof(stdConsole_cursorHidden));
_memset(&stdConsole_ConsoleCursorInfo, 0, sizeof(stdConsole_ConsoleCursorInfo));
_memset(&stdConsole_hConsoleOutput, 0, sizeof(stdConsole_hConsoleOutput));
_memset(&stdConsole_hConsoleInput, 0, sizeof(stdConsole_hConsoleInput));
_memset(&rdRaster_aOneDivXQuantLUT, 0, sizeof(rdRaster_aOneDivXQuantLUT));
_memset(&rdRaster_aOtherLUT, 0, sizeof(rdRaster_aOtherLUT));
_memset(&rdRaster_aOneDivXLUT, 0, sizeof(rdRaster_aOneDivXLUT));
float  __rdRaster_fixedScale_origValue =  65536.0f;
_memcpy(&rdRaster_fixedScale, &__rdRaster_fixedScale_origValue, sizeof(rdRaster_fixedScale));
_memset(&sithCogFunctionAI_apViewThings, 0, sizeof(sithCogFunctionAI_apViewThings));
sithCogFunctionAI_unk1 = 0;
int __sithCogFunctionAI_unk1_origValue = 0;
_memcpy(&sithCogFunctionAI_unk1, &__sithCogFunctionAI_unk1_origValue, sizeof(sithCogFunctionAI_unk1));
sithCogFunctionAI_viewThingIdx = 0;
int __sithCogFunctionAI_viewThingIdx_origValue = 0;
_memcpy(&sithCogFunctionAI_viewThingIdx, &__sithCogFunctionAI_viewThingIdx_origValue, sizeof(sithCogFunctionAI_viewThingIdx));
_memset(&sithComm_MsgTmpBuf, 0, sizeof(sithComm_MsgTmpBuf));
_memset(&sithComm_aMsgPairs, 0, sizeof(sithComm_aMsgPairs));
_memset(&sithComm_msgFuncs, 0, sizeof(sithComm_msgFuncs));
sithComm_needsSync = 0;
int __sithComm_needsSync_origValue = 0;
_memcpy(&sithComm_needsSync, &__sithComm_needsSync_origValue, sizeof(sithComm_needsSync));
sithComm_multiplayerFlags = 0;
int __sithComm_multiplayerFlags_origValue = 0;
_memcpy(&sithComm_multiplayerFlags, &__sithComm_multiplayerFlags_origValue, sizeof(sithComm_multiplayerFlags));
sithComm_bSyncMultiplayer = 0;
int __sithComm_bSyncMultiplayer_origValue = 0;
_memcpy(&sithComm_bSyncMultiplayer, &__sithComm_bSyncMultiplayer_origValue, sizeof(sithComm_bSyncMultiplayer));
sithComm_idk2 = 0;
int __sithComm_idk2_origValue = 0;
_memcpy(&sithComm_idk2, &__sithComm_idk2_origValue, sizeof(sithComm_idk2));
sithComm_bInit = 0;
int __sithComm_bInit_origValue = 0;
_memcpy(&sithComm_bInit, &__sithComm_bInit_origValue, sizeof(sithComm_bInit));
_memset(&sithComm_dword_847E84, 0, sizeof(sithComm_dword_847E84));
int  __sithComm_msgId_origValue =  1;
_memcpy(&sithComm_msgId, &__sithComm_msgId_origValue, sizeof(sithComm_msgId));
_memset(&sithComm_MsgTmpBuf2, 0, sizeof(sithComm_MsgTmpBuf2));
_memset(&sithComm_netMsgTmp, 0, sizeof(sithComm_netMsgTmp));
_memset(&jkCog_emptystring, 0, sizeof(jkCog_emptystring));
_memset(&jkCog_jkstring, 0, sizeof(jkCog_jkstring));
jkCog_bInitted = 0;
int __jkCog_bInitted_origValue = 0;
_memcpy(&jkCog_bInitted, &__jkCog_bInitted_origValue, sizeof(jkCog_bInitted));
_memset(&jkCog_strings, 0, sizeof(jkCog_strings));
sithCog_bOpened = 0;
int __sithCog_bOpened_origValue = 0;
_memcpy(&sithCog_bOpened, &__sithCog_bOpened_origValue, sizeof(sithCog_bOpened));
sithCog_pScriptHashtable = NULL;
stdHashTable* __sithCog_pScriptHashtable_origValue = NULL;
_memcpy(&sithCog_pScriptHashtable, &__sithCog_pScriptHashtable_origValue, sizeof(sithCog_pScriptHashtable));
_memset(&sithCog_aSectorLinks, 0, sizeof(sithCog_aSectorLinks));
sithCog_numSectorLinks = 0;
int __sithCog_numSectorLinks_origValue = 0;
_memcpy(&sithCog_numSectorLinks, &__sithCog_numSectorLinks_origValue, sizeof(sithCog_numSectorLinks));
_memset(&sithCog_aThingLinks, 0, sizeof(sithCog_aThingLinks));
sithCog_numThingLinks = 0;
int __sithCog_numThingLinks_origValue = 0;
_memcpy(&sithCog_numThingLinks, &__sithCog_numThingLinks_origValue, sizeof(sithCog_numThingLinks));
sithCog_numSurfaceLinks = 0;
int __sithCog_numSurfaceLinks_origValue = 0;
_memcpy(&sithCog_numSurfaceLinks, &__sithCog_numSurfaceLinks_origValue, sizeof(sithCog_numSurfaceLinks));
_memset(&sithCog_aSurfaceLinks, 0, sizeof(sithCog_aSurfaceLinks));
sithCog_masterCog = NULL;
sithCog* __sithCog_masterCog_origValue = NULL;
_memcpy(&sithCog_masterCog, &__sithCog_masterCog_origValue, sizeof(sithCog_masterCog));
_memset(&jkDev_aEntryPositions, 0, sizeof(jkDev_aEntryPositions));
_memset(&jkDev_aEntries, 0, sizeof(jkDev_aEntries));
jkDev_log_55A4A4 = 0;
int __jkDev_log_55A4A4_origValue = 0;
_memcpy(&jkDev_log_55A4A4, &__jkDev_log_55A4A4_origValue, sizeof(jkDev_log_55A4A4));
jkDev_bScreenNeedsUpdate = 0;
int __jkDev_bScreenNeedsUpdate_origValue = 0;
_memcpy(&jkDev_bScreenNeedsUpdate, &__jkDev_bScreenNeedsUpdate_origValue, sizeof(jkDev_bScreenNeedsUpdate));
_memset(&jkDev_aCheatCmds, 0, sizeof(jkDev_aCheatCmds));
_memset(&jkDev_numCheats, 0, sizeof(jkDev_numCheats));
jkDev_bInitted = 0;
int __jkDev_bInitted_origValue = 0;
_memcpy(&jkDev_bInitted, &__jkDev_bInitted_origValue, sizeof(jkDev_bInitted));
jkDev_bOpened = 0;
int __jkDev_bOpened_origValue = 0;
_memcpy(&jkDev_bOpened, &__jkDev_bOpened_origValue, sizeof(jkDev_bOpened));
jkDev_cheatHashtable = NULL;
stdHashTable* __jkDev_cheatHashtable_origValue = NULL;
_memcpy(&jkDev_cheatHashtable, &__jkDev_cheatHashtable_origValue, sizeof(jkDev_cheatHashtable));
_memset(&jkDev_hDlg, 0, sizeof(jkDev_hDlg));
jkDev_vbuf = NULL;
stdVBuffer* __jkDev_vbuf_origValue = NULL;
_memcpy(&jkDev_vbuf, &__jkDev_vbuf_origValue, sizeof(jkDev_vbuf));
jkDev_BMFontHeight = 0;
int __jkDev_BMFontHeight_origValue = 0;
_memcpy(&jkDev_BMFontHeight, &__jkDev_BMFontHeight_origValue, sizeof(jkDev_BMFontHeight));
jkDev_ColorKey = 0;
int __jkDev_ColorKey_origValue = 0;
_memcpy(&jkDev_ColorKey, &__jkDev_ColorKey_origValue, sizeof(jkDev_ColorKey));
jkDev_dword_55A9D0 = 0;
int __jkDev_dword_55A9D0_origValue = 0;
_memcpy(&jkDev_dword_55A9D0, &__jkDev_dword_55A9D0_origValue, sizeof(jkDev_dword_55A9D0));
jkDev_amt = 0.0f;
float __jkDev_amt_origValue = 0.0f;
_memcpy(&jkDev_amt, &__jkDev_amt_origValue, sizeof(jkDev_amt));
jkSmack_gameMode = 0;
int __jkSmack_gameMode_origValue = 0;
_memcpy(&jkSmack_gameMode, &__jkSmack_gameMode_origValue, sizeof(jkSmack_gameMode));
jkSmack_bInit = 0;
int __jkSmack_bInit_origValue = 0;
_memcpy(&jkSmack_bInit, &__jkSmack_bInit_origValue, sizeof(jkSmack_bInit));
jkSmack_stopTick = 0;
int __jkSmack_stopTick_origValue = 0;
_memcpy(&jkSmack_stopTick, &__jkSmack_stopTick_origValue, sizeof(jkSmack_stopTick));
jkSmack_currentGuiState = 0;
int __jkSmack_currentGuiState_origValue = 0;
_memcpy(&jkSmack_currentGuiState, &__jkSmack_currentGuiState_origValue, sizeof(jkSmack_currentGuiState));
jkSmack_nextGuiState = 0;
int __jkSmack_nextGuiState_origValue = 0;
_memcpy(&jkSmack_nextGuiState, &__jkSmack_nextGuiState_origValue, sizeof(jkSmack_nextGuiState));
jkSmack_alloc = NULL;
void* __jkSmack_alloc_origValue = NULL;
_memcpy(&jkSmack_alloc, &__jkSmack_alloc_origValue, sizeof(jkSmack_alloc));
_memset(&jkEpisode_aEpisodes, 0, sizeof(jkEpisode_aEpisodes));
_memset(&jkEpisode_var4, 0, sizeof(jkEpisode_var4));
_memset(&jkEpisode_var5, 0, sizeof(jkEpisode_var5));
_memset(&jkEpisode_var2, 0, sizeof(jkEpisode_var2));
_memset(&jkEpisode_mLoad, 0, sizeof(jkEpisode_mLoad));
uint32_t  __jkHud_targetRed_origValue =  1;
_memcpy(&jkHud_targetRed, &__jkHud_targetRed_origValue, sizeof(jkHud_targetRed));
uint32_t  __jkHud_targetBlue_origValue =  2;
_memcpy(&jkHud_targetBlue, &__jkHud_targetBlue_origValue, sizeof(jkHud_targetBlue));
uint32_t  __jkHud_targetGreen_origValue =  3;
_memcpy(&jkHud_targetGreen, &__jkHud_targetGreen_origValue, sizeof(jkHud_targetGreen));
float __jkHud_aFltIdk_origValue[6]  =  {0.2, 0.4, 0.8, 1.0, 2.0, 0.0};
_memcpy(&jkHud_aFltIdk, &__jkHud_aFltIdk_origValue, sizeof(jkHud_aFltIdk));
int __jkHud_aColors8bpp_origValue[6]  =  {1,2,3,4,5,0};
_memcpy(&jkHud_aColors8bpp, &__jkHud_aColors8bpp_origValue, sizeof(jkHud_aColors8bpp));
int __jkHud_aTeamColors8bpp_origValue[5]  =  {0x0, 0x6, 0x69, 0x1F, 0x2};
_memcpy(&jkHud_aTeamColors8bpp, &__jkHud_aTeamColors8bpp_origValue, sizeof(jkHud_aTeamColors8bpp));
_memset(&jkHud_chatStr, 0, sizeof(jkHud_chatStr));
_memset(&jkHud_aTeamColors16bpp, 0, sizeof(jkHud_aTeamColors16bpp));
_memset(&jkHud_rightBlitX, 0, sizeof(jkHud_rightBlitX));
_memset(&jkHud_leftBlitX, 0, sizeof(jkHud_leftBlitX));
_memset(&jkHud_mapRendConfig, 0, sizeof(jkHud_mapRendConfig));
jkHud_chatStrPos = 0;
int __jkHud_chatStrPos_origValue = 0;
_memcpy(&jkHud_chatStrPos, &__jkHud_chatStrPos_origValue, sizeof(jkHud_chatStrPos));
jkHud_rightBlitY = 0;
int __jkHud_rightBlitY_origValue = 0;
_memcpy(&jkHud_rightBlitY, &__jkHud_rightBlitY_origValue, sizeof(jkHud_rightBlitY));
_memset(&jkHud_aTeamScores, 0, sizeof(jkHud_aTeamScores));
jkHud_dword_552D10 = 0;
int __jkHud_dword_552D10_origValue = 0;
_memcpy(&jkHud_dword_552D10, &__jkHud_dword_552D10_origValue, sizeof(jkHud_dword_552D10));
_memset(&jkHud_aColors16bpp, 0, sizeof(jkHud_aColors16bpp));
_memset(&jkHud_aPlayerScores, 0, sizeof(jkHud_aPlayerScores));
jkHud_blittedAmmoAmt = 0;
int __jkHud_blittedAmmoAmt_origValue = 0;
_memcpy(&jkHud_blittedAmmoAmt, &__jkHud_blittedAmmoAmt_origValue, sizeof(jkHud_blittedAmmoAmt));
jkHud_idk14 = 0;
int __jkHud_idk14_origValue = 0;
_memcpy(&jkHud_idk14, &__jkHud_idk14_origValue, sizeof(jkHud_idk14));
jkHud_blittedHealthIdx = 0;
int __jkHud_blittedHealthIdx_origValue = 0;
_memcpy(&jkHud_blittedHealthIdx, &__jkHud_blittedHealthIdx_origValue, sizeof(jkHud_blittedHealthIdx));
jkHud_blittedBatteryAmt = 0;
int __jkHud_blittedBatteryAmt_origValue = 0;
_memcpy(&jkHud_blittedBatteryAmt, &__jkHud_blittedBatteryAmt_origValue, sizeof(jkHud_blittedBatteryAmt));
jkHud_blittedFieldlightAmt = 0;
int __jkHud_blittedFieldlightAmt_origValue = 0;
_memcpy(&jkHud_blittedFieldlightAmt, &__jkHud_blittedFieldlightAmt_origValue, sizeof(jkHud_blittedFieldlightAmt));
jkHud_blittedShieldIdx = 0;
int __jkHud_blittedShieldIdx_origValue = 0;
_memcpy(&jkHud_blittedShieldIdx, &__jkHud_blittedShieldIdx_origValue, sizeof(jkHud_blittedShieldIdx));
jkHud_isSuper = 0;
int __jkHud_isSuper_origValue = 0;
_memcpy(&jkHud_isSuper, &__jkHud_isSuper_origValue, sizeof(jkHud_isSuper));
jkHud_idk15 = 0;
int __jkHud_idk15_origValue = 0;
_memcpy(&jkHud_idk15, &__jkHud_idk15_origValue, sizeof(jkHud_idk15));
jkHud_blittedForceIdx = 0;
int __jkHud_blittedForceIdx_origValue = 0;
_memcpy(&jkHud_blittedForceIdx, &__jkHud_blittedForceIdx_origValue, sizeof(jkHud_blittedForceIdx));
jkHud_idk16 = 0;
int __jkHud_idk16_origValue = 0;
_memcpy(&jkHud_idk16, &__jkHud_idk16_origValue, sizeof(jkHud_idk16));
jkHud_leftBlitY = 0;
int __jkHud_leftBlitY_origValue = 0;
_memcpy(&jkHud_leftBlitY, &__jkHud_leftBlitY_origValue, sizeof(jkHud_leftBlitY));
_memset(&jkHud_rectViewScores, 0, sizeof(jkHud_rectViewScores));
jkHud_pMsgFontSft = NULL;
stdFont* __jkHud_pMsgFontSft_origValue = NULL;
_memcpy(&jkHud_pMsgFontSft, &__jkHud_pMsgFontSft_origValue, sizeof(jkHud_pMsgFontSft));
jkHud_pStatusLeftBm = NULL;
stdBitmap* __jkHud_pStatusLeftBm_origValue = NULL;
_memcpy(&jkHud_pStatusLeftBm, &__jkHud_pStatusLeftBm_origValue, sizeof(jkHud_pStatusLeftBm));
jkHud_pStatusRightBm = NULL;
stdBitmap* __jkHud_pStatusRightBm_origValue = NULL;
_memcpy(&jkHud_pStatusRightBm, &__jkHud_pStatusRightBm_origValue, sizeof(jkHud_pStatusRightBm));
jkHud_bHasTarget = 0;
int __jkHud_bHasTarget_origValue = 0;
_memcpy(&jkHud_bHasTarget, &__jkHud_bHasTarget_origValue, sizeof(jkHud_bHasTarget));
jkHud_pTargetThing = NULL;
sithThing* __jkHud_pTargetThing_origValue = NULL;
_memcpy(&jkHud_pTargetThing, &__jkHud_pTargetThing_origValue, sizeof(jkHud_pTargetThing));
_memset(&jkHud_targetRed16, 0, sizeof(jkHud_targetRed16));
_memset(&jkHud_targetGreen16, 0, sizeof(jkHud_targetGreen16));
_memset(&jkHud_targetBlue16, 0, sizeof(jkHud_targetBlue16));
jkHud_bChatOpen = 0;
int __jkHud_bChatOpen_origValue = 0;
_memcpy(&jkHud_bChatOpen, &__jkHud_bChatOpen_origValue, sizeof(jkHud_bChatOpen));
jkHud_pHelthNumSft = NULL;
stdFont* __jkHud_pHelthNumSft_origValue = NULL;
_memcpy(&jkHud_pHelthNumSft, &__jkHud_pHelthNumSft_origValue, sizeof(jkHud_pHelthNumSft));
jkHud_pAmoNumsSft = NULL;
stdFont* __jkHud_pAmoNumsSft_origValue = NULL;
_memcpy(&jkHud_pAmoNumsSft, &__jkHud_pAmoNumsSft_origValue, sizeof(jkHud_pAmoNumsSft));
jkHud_pAmoNumsSuperSft = NULL;
stdFont* __jkHud_pAmoNumsSuperSft_origValue = NULL;
_memcpy(&jkHud_pAmoNumsSuperSft, &__jkHud_pAmoNumsSuperSft_origValue, sizeof(jkHud_pAmoNumsSuperSft));
jkHud_pArmorNumSft = NULL;
stdFont* __jkHud_pArmorNumSft_origValue = NULL;
_memcpy(&jkHud_pArmorNumSft, &__jkHud_pArmorNumSft_origValue, sizeof(jkHud_pArmorNumSft));
jkHud_pArmorNumsSuperSft = NULL;
stdFont* __jkHud_pArmorNumsSuperSft_origValue = NULL;
_memcpy(&jkHud_pArmorNumsSuperSft, &__jkHud_pArmorNumsSuperSft_origValue, sizeof(jkHud_pArmorNumsSuperSft));
jkHud_bInitted = 0;
int __jkHud_bInitted_origValue = 0;
_memcpy(&jkHud_bInitted, &__jkHud_bInitted_origValue, sizeof(jkHud_bInitted));
jkHud_bOpened = 0;
int __jkHud_bOpened_origValue = 0;
_memcpy(&jkHud_bOpened, &__jkHud_bOpened_origValue, sizeof(jkHud_bOpened));
jkHud_pFieldlightBm = NULL;
stdBitmap* __jkHud_pFieldlightBm_origValue = NULL;
_memcpy(&jkHud_pFieldlightBm, &__jkHud_pFieldlightBm_origValue, sizeof(jkHud_pFieldlightBm));
jkHud_pStBatBm = NULL;
stdBitmap* __jkHud_pStBatBm_origValue = NULL;
_memcpy(&jkHud_pStBatBm, &__jkHud_pStBatBm_origValue, sizeof(jkHud_pStBatBm));
jkHud_pStHealthBm = NULL;
stdBitmap* __jkHud_pStHealthBm_origValue = NULL;
_memcpy(&jkHud_pStHealthBm, &__jkHud_pStHealthBm_origValue, sizeof(jkHud_pStHealthBm));
jkHud_pStShieldBm = NULL;
stdBitmap* __jkHud_pStShieldBm_origValue = NULL;
_memcpy(&jkHud_pStShieldBm, &__jkHud_pStShieldBm_origValue, sizeof(jkHud_pStShieldBm));
jkHud_pStFrcBm = NULL;
stdBitmap* __jkHud_pStFrcBm_origValue = NULL;
_memcpy(&jkHud_pStFrcBm, &__jkHud_pStFrcBm_origValue, sizeof(jkHud_pStFrcBm));
jkHud_pStFrcSuperBm = NULL;
stdBitmap* __jkHud_pStFrcSuperBm_origValue = NULL;
_memcpy(&jkHud_pStFrcSuperBm, &__jkHud_pStFrcSuperBm_origValue, sizeof(jkHud_pStFrcSuperBm));
jkHud_bViewScores = 0;
int __jkHud_bViewScores_origValue = 0;
_memcpy(&jkHud_bViewScores, &__jkHud_bViewScores_origValue, sizeof(jkHud_bViewScores));
jkHud_dword_553ED0 = 0;
int __jkHud_dword_553ED0_origValue = 0;
_memcpy(&jkHud_dword_553ED0, &__jkHud_dword_553ED0_origValue, sizeof(jkHud_dword_553ED0));
jkHud_tallyWhich = 0;
int __jkHud_tallyWhich_origValue = 0;
_memcpy(&jkHud_tallyWhich, &__jkHud_tallyWhich_origValue, sizeof(jkHud_tallyWhich));
_memset(&jkHud_numPlayers, 0, sizeof(jkHud_numPlayers));
jkHud_dword_553EDC = 0;
int __jkHud_dword_553EDC_origValue = 0;
_memcpy(&jkHud_dword_553EDC, &__jkHud_dword_553EDC_origValue, sizeof(jkHud_dword_553EDC));
jkHud_dword_553EE0 = 0;
int __jkHud_dword_553EE0_origValue = 0;
_memcpy(&jkHud_dword_553EE0, &__jkHud_dword_553EE0_origValue, sizeof(jkHud_dword_553EE0));
_memset(&jkHudInv_info, 0, sizeof(jkHudInv_info));
_memset(&jkHudInv_itemTexfmt, 0, sizeof(jkHudInv_itemTexfmt));
jkHudInv_flags = 0;
int __jkHudInv_flags_origValue = 0;
_memcpy(&jkHudInv_flags, &__jkHudInv_flags_origValue, sizeof(jkHudInv_flags));
jkHudInv_dword_553F64 = 0;
int __jkHudInv_dword_553F64_origValue = 0;
_memcpy(&jkHudInv_dword_553F64, &__jkHudInv_dword_553F64_origValue, sizeof(jkHudInv_dword_553F64));
_memset(&jkHudInv_scroll, 0, sizeof(jkHudInv_scroll));
_memset(&jkHudInv_aBitmaps, 0, sizeof(jkHudInv_aBitmaps));
jkHudInv_font = NULL;
stdFont* __jkHudInv_font_origValue = NULL;
_memcpy(&jkHudInv_font, &__jkHudInv_font_origValue, sizeof(jkHudInv_font));
jkHudInv_rend_isshowing_maybe = 0;
int __jkHudInv_rend_isshowing_maybe_origValue = 0;
_memcpy(&jkHudInv_rend_isshowing_maybe, &__jkHudInv_rend_isshowing_maybe_origValue, sizeof(jkHudInv_rend_isshowing_maybe));
jkHudInv_dword_553F94 = 0;
int __jkHudInv_dword_553F94_origValue = 0;
_memcpy(&jkHudInv_dword_553F94, &__jkHudInv_dword_553F94_origValue, sizeof(jkHudInv_dword_553F94));
jkHudInv_numItems = 0;
int __jkHudInv_numItems_origValue = 0;
_memcpy(&jkHudInv_numItems, &__jkHudInv_numItems_origValue, sizeof(jkHudInv_numItems));
jkHudInv_aItems = NULL;
int* __jkHudInv_aItems_origValue = NULL;
_memcpy(&jkHudInv_aItems, &__jkHudInv_aItems_origValue, sizeof(jkHudInv_aItems));
Main_bDevMode = 0;
int __Main_bDevMode_origValue = 0;
_memcpy(&Main_bDevMode, &__Main_bDevMode_origValue, sizeof(Main_bDevMode));
Main_bDisplayConfig = 0;
int __Main_bDisplayConfig_origValue = 0;
_memcpy(&Main_bDisplayConfig, &__Main_bDisplayConfig_origValue, sizeof(Main_bDisplayConfig));
Main_bWindowGUI = 0;
int __Main_bWindowGUI_origValue = 0;
_memcpy(&Main_bWindowGUI, &__Main_bWindowGUI_origValue, sizeof(Main_bWindowGUI));
Main_dword_86078C = 0;
int __Main_dword_86078C_origValue = 0;
_memcpy(&Main_dword_86078C, &__Main_dword_86078C_origValue, sizeof(Main_dword_86078C));
Main_bFrameRate = 0;
int __Main_bFrameRate_origValue = 0;
_memcpy(&Main_bFrameRate, &__Main_bFrameRate_origValue, sizeof(Main_bFrameRate));
Main_bDispStats = 0;
int __Main_bDispStats_origValue = 0;
_memcpy(&Main_bDispStats, &__Main_bDispStats_origValue, sizeof(Main_bDispStats));
Main_bNoHUD = 0;
int __Main_bNoHUD_origValue = 0;
_memcpy(&Main_bNoHUD, &__Main_bNoHUD_origValue, sizeof(Main_bNoHUD));
Main_logLevel = 0;
int __Main_logLevel_origValue = 0;
_memcpy(&Main_logLevel, &__Main_logLevel_origValue, sizeof(Main_logLevel));
Main_verboseLevel = 0;
int __Main_verboseLevel_origValue = 0;
_memcpy(&Main_verboseLevel, &__Main_verboseLevel_origValue, sizeof(Main_verboseLevel));
_memset(&Main_path, 0, sizeof(Main_path));
stdFile_t  __debug_log_fp_origValue =  0;
_memcpy(&debug_log_fp, &__debug_log_fp_origValue, sizeof(debug_log_fp));
pHS = NULL;
HostServices* __pHS_origValue = NULL;
_memcpy(&pHS, &__pHS_origValue, sizeof(pHS));
_memset(&jkCredits_aPalette, 0, sizeof(jkCredits_aPalette));
jkCredits_pVbuffer2 = NULL;
stdVBuffer* __jkCredits_pVbuffer2_origValue = NULL;
_memcpy(&jkCredits_pVbuffer2, &__jkCredits_pVbuffer2_origValue, sizeof(jkCredits_pVbuffer2));
jkCredits_dword_55AD64 = 0;
int __jkCredits_dword_55AD64_origValue = 0;
_memcpy(&jkCredits_dword_55AD64, &__jkCredits_dword_55AD64_origValue, sizeof(jkCredits_dword_55AD64));
jkCredits_dword_55AD68 = 0;
int __jkCredits_dword_55AD68_origValue = 0;
_memcpy(&jkCredits_dword_55AD68, &__jkCredits_dword_55AD68_origValue, sizeof(jkCredits_dword_55AD68));
_memset(&jkCredits_table, 0, sizeof(jkCredits_table));
jkCredits_startMs = 0;
int __jkCredits_startMs_origValue = 0;
_memcpy(&jkCredits_startMs, &__jkCredits_startMs_origValue, sizeof(jkCredits_startMs));
jkCredits_dword_55AD84 = 0;
int __jkCredits_dword_55AD84_origValue = 0;
_memcpy(&jkCredits_dword_55AD84, &__jkCredits_dword_55AD84_origValue, sizeof(jkCredits_dword_55AD84));
jkCredits_strIdx = 0;
int __jkCredits_strIdx_origValue = 0;
_memcpy(&jkCredits_strIdx, &__jkCredits_strIdx_origValue, sizeof(jkCredits_strIdx));
jkCredits_aIdk = NULL;
char* __jkCredits_aIdk_origValue = NULL;
_memcpy(&jkCredits_aIdk, &__jkCredits_aIdk_origValue, sizeof(jkCredits_aIdk));
jkCredits_pVbuffer = NULL;
stdVBuffer* __jkCredits_pVbuffer_origValue = NULL;
_memcpy(&jkCredits_pVbuffer, &__jkCredits_pVbuffer_origValue, sizeof(jkCredits_pVbuffer));
jkCredits_dword_55AD94 = 0;
int __jkCredits_dword_55AD94_origValue = 0;
_memcpy(&jkCredits_dword_55AD94, &__jkCredits_dword_55AD94_origValue, sizeof(jkCredits_dword_55AD94));
jkCredits_fontLarge = NULL;
stdFont* __jkCredits_fontLarge_origValue = NULL;
_memcpy(&jkCredits_fontLarge, &__jkCredits_fontLarge_origValue, sizeof(jkCredits_fontLarge));
jkCredits_fontSmall = NULL;
stdFont* __jkCredits_fontSmall_origValue = NULL;
_memcpy(&jkCredits_fontSmall, &__jkCredits_fontSmall_origValue, sizeof(jkCredits_fontSmall));
jkCredits_dword_55ADA0 = 0;
int __jkCredits_dword_55ADA0_origValue = 0;
_memcpy(&jkCredits_dword_55ADA0, &__jkCredits_dword_55ADA0_origValue, sizeof(jkCredits_dword_55ADA0));
jkCredits_bInitted = 0;
int __jkCredits_bInitted_origValue = 0;
_memcpy(&jkCredits_bInitted, &__jkCredits_bInitted_origValue, sizeof(jkCredits_bInitted));
jkCredits_dword_55ADA8 = 0;
int __jkCredits_dword_55ADA8_origValue = 0;
_memcpy(&jkCredits_dword_55ADA8, &__jkCredits_dword_55ADA8_origValue, sizeof(jkCredits_dword_55ADA8));
g_sithMode = 0;
int __g_sithMode_origValue = 0;
_memcpy(&g_sithMode, &__g_sithMode_origValue, sizeof(g_sithMode));
g_submodeFlags = 0;
int __g_submodeFlags_origValue = 0;
_memcpy(&g_submodeFlags, &__g_submodeFlags_origValue, sizeof(g_submodeFlags));
g_debugmodeFlags = 0;
int __g_debugmodeFlags_origValue = 0;
_memcpy(&g_debugmodeFlags, &__g_debugmodeFlags_origValue, sizeof(g_debugmodeFlags));
g_mapModeFlags = 0;
int __g_mapModeFlags_origValue = 0;
_memcpy(&g_mapModeFlags, &__g_mapModeFlags_origValue, sizeof(g_mapModeFlags));
jkGame_gamma = 0;
int __jkGame_gamma_origValue = 0;
_memcpy(&jkGame_gamma, &__jkGame_gamma_origValue, sizeof(jkGame_gamma));
jkGame_screenSize = 0;
int __jkGame_screenSize_origValue = 0;
_memcpy(&jkGame_screenSize, &__jkGame_screenSize_origValue, sizeof(jkGame_screenSize));
jkGame_bInitted = 0;
int __jkGame_bInitted_origValue = 0;
_memcpy(&jkGame_bInitted, &__jkGame_bInitted_origValue, sizeof(jkGame_bInitted));
jkGame_updateMsecsTotal = 0;
int __jkGame_updateMsecsTotal_origValue = 0;
_memcpy(&jkGame_updateMsecsTotal, &__jkGame_updateMsecsTotal_origValue, sizeof(jkGame_updateMsecsTotal));
jkGame_dword_552B5C = 0;
int __jkGame_dword_552B5C_origValue = 0;
_memcpy(&jkGame_dword_552B5C, &__jkGame_dword_552B5C_origValue, sizeof(jkGame_dword_552B5C));
jkGame_isDDraw = 0;
int __jkGame_isDDraw_origValue = 0;
_memcpy(&jkGame_isDDraw, &__jkGame_isDDraw_origValue, sizeof(jkGame_isDDraw));
jkRes_pHS = NULL;
HostServices* __jkRes_pHS_origValue = NULL;
_memcpy(&jkRes_pHS, &__jkRes_pHS_origValue, sizeof(jkRes_pHS));
char __jkRes_episodeGobName_origValue[32]  =  {0};
_memcpy(&jkRes_episodeGobName, &__jkRes_episodeGobName_origValue, sizeof(jkRes_episodeGobName));
char __jkRes_curDir_origValue[128]  =  {0};
_memcpy(&jkRes_curDir, &__jkRes_curDir_origValue, sizeof(jkRes_curDir));
jkRes_bHookedHS = 0;
int __jkRes_bHookedHS_origValue = 0;
_memcpy(&jkRes_bHookedHS, &__jkRes_bHookedHS_origValue, sizeof(jkRes_bHookedHS));
_memset(&jkRes_aFiles, 0, sizeof(jkRes_aFiles));
_memset(&jkRes_gCtx, 0, sizeof(jkRes_gCtx));
pLowLevelHS = NULL;
HostServices* __pLowLevelHS_origValue = NULL;
_memcpy(&pLowLevelHS, &__pLowLevelHS_origValue, sizeof(pLowLevelHS));
_memset(&lowLevelHS, 0, sizeof(lowLevelHS));
_memset(&jkRes_idkGobPath, 0, sizeof(jkRes_idkGobPath));
_memset(&jkCutscene_rect1, 0, sizeof(jkCutscene_rect1));
_memset(&jkCutscene_rect2, 0, sizeof(jkCutscene_rect2));
_memset(&jkCutscene_strings, 0, sizeof(jkCutscene_strings));
jkCutscene_subtitlefont = NULL;
stdFont* __jkCutscene_subtitlefont_origValue = NULL;
_memcpy(&jkCutscene_subtitlefont, &__jkCutscene_subtitlefont_origValue, sizeof(jkCutscene_subtitlefont));
jkCutscene_bInitted = 0;
int __jkCutscene_bInitted_origValue = 0;
_memcpy(&jkCutscene_bInitted, &__jkCutscene_bInitted_origValue, sizeof(jkCutscene_bInitted));
jkCutscene_isRendering = 0;
int __jkCutscene_isRendering_origValue = 0;
_memcpy(&jkCutscene_isRendering, &__jkCutscene_isRendering_origValue, sizeof(jkCutscene_isRendering));
jkCutscene_dword_55B750 = 0;
int __jkCutscene_dword_55B750_origValue = 0;
_memcpy(&jkCutscene_dword_55B750, &__jkCutscene_dword_55B750_origValue, sizeof(jkCutscene_dword_55B750));
jkCutscene_dword_55AA50 = 0;
int __jkCutscene_dword_55AA50_origValue = 0;
_memcpy(&jkCutscene_dword_55AA50, &__jkCutscene_dword_55AA50_origValue, sizeof(jkCutscene_dword_55AA50));
jkCutscene_55AA54 = 0;
int __jkCutscene_55AA54_origValue = 0;
_memcpy(&jkCutscene_55AA54, &__jkCutscene_55AA54_origValue, sizeof(jkCutscene_55AA54));
_memset(&jkMain_aLevelJklFname, 0, sizeof(jkMain_aLevelJklFname));
int  __thing_nine_origValue =  1;
_memcpy(&thing_nine, &__thing_nine_origValue, sizeof(thing_nine));
jkMain_bInit = 0;
int __jkMain_bInit_origValue = 0;
_memcpy(&jkMain_bInit, &__jkMain_bInit_origValue, sizeof(jkMain_bInit));
thing_six = 0;
int __thing_six_origValue = 0;
_memcpy(&thing_six, &__thing_six_origValue, sizeof(thing_six));
thing_eight = 0;
int __thing_eight_origValue = 0;
_memcpy(&thing_eight, &__thing_eight_origValue, sizeof(thing_eight));
jkMain_dword_552B98 = 0;
int __jkMain_dword_552B98_origValue = 0;
_memcpy(&jkMain_dword_552B98, &__jkMain_dword_552B98_origValue, sizeof(jkMain_dword_552B98));
jkMain_lastTickMs = 0;
int __jkMain_lastTickMs_origValue = 0;
_memcpy(&jkMain_lastTickMs, &__jkMain_lastTickMs_origValue, sizeof(jkMain_lastTickMs));
idx_13b4_related = 0;
int __idx_13b4_related_origValue = 0;
_memcpy(&idx_13b4_related, &__idx_13b4_related_origValue, sizeof(idx_13b4_related));
_memset(&gamemode_1_str, 0, sizeof(gamemode_1_str));
_memset(&jkMain_strIdk, 0, sizeof(jkMain_strIdk));
_memset(&jkMain_wstrIdk, 0, sizeof(jkMain_wstrIdk));
_memset(&sithWorld_aSectionParsers, 0, sizeof(sithWorld_aSectionParsers));
_memset(&sithWorld_some_integer_4, 0, sizeof(sithWorld_some_integer_4));
sithWorld_pCurrentWorld = NULL;
sithWorld* __sithWorld_pCurrentWorld_origValue = NULL;
_memcpy(&sithWorld_pCurrentWorld, &__sithWorld_pCurrentWorld_origValue, sizeof(sithWorld_pCurrentWorld));
sithWorld_pStatic = NULL;
sithWorld* __sithWorld_pStatic_origValue = NULL;
_memcpy(&sithWorld_pStatic, &__sithWorld_pStatic_origValue, sizeof(sithWorld_pStatic));
sithWorld_pLoading = NULL;
sithWorld* __sithWorld_pLoading_origValue = NULL;
_memcpy(&sithWorld_pLoading, &__sithWorld_pLoading_origValue, sizeof(sithWorld_pLoading));
_memset(&sithWorld_numParsers, 0, sizeof(sithWorld_numParsers));
_memset(&sithWorld_bInitted, 0, sizeof(sithWorld_bInitted));
sithWorld_bLoaded = 0;
int __sithWorld_bLoaded_origValue = 0;
_memcpy(&sithWorld_bLoaded, &__sithWorld_bLoaded_origValue, sizeof(sithWorld_bLoaded));
_memset(&sithWorld_episodeName, 0, sizeof(sithWorld_episodeName));
_memset(&sithInventory_powerKeybinds, 0, sizeof(sithInventory_powerKeybinds));
int  __sithInventory_549FA0_origValue =  1;
_memcpy(&sithInventory_549FA0, &__sithInventory_549FA0_origValue, sizeof(sithInventory_549FA0));
_memset(&sithInventory_aDescriptors, 0, sizeof(sithInventory_aDescriptors));
sithInventory_bUnk = 0;
int __sithInventory_bUnk_origValue = 0;
_memcpy(&sithInventory_bUnk, &__sithInventory_bUnk_origValue, sizeof(sithInventory_bUnk));
sithInventory_bUnkPower = 0;
int __sithInventory_bUnkPower_origValue = 0;
_memcpy(&sithInventory_bUnkPower, &__sithInventory_bUnkPower_origValue, sizeof(sithInventory_bUnkPower));
sithInventory_8339EC = 0;
int __sithInventory_8339EC_origValue = 0;
_memcpy(&sithInventory_8339EC, &__sithInventory_8339EC_origValue, sizeof(sithInventory_8339EC));
sithInventory_bRendIsHidden = 0;
int __sithInventory_bRendIsHidden_origValue = 0;
_memcpy(&sithInventory_bRendIsHidden, &__sithInventory_bRendIsHidden_origValue, sizeof(sithInventory_bRendIsHidden));
sithInventory_8339F4 = 0;
int __sithInventory_8339F4_origValue = 0;
_memcpy(&sithInventory_8339F4, &__sithInventory_8339F4_origValue, sizeof(sithInventory_8339F4));
_memset(&sithWeapon_controlOptions, 0, sizeof(sithWeapon_controlOptions));
g_flt_8BD040 = 0.0f;
float __g_flt_8BD040_origValue = 0.0f;
_memcpy(&g_flt_8BD040, &__g_flt_8BD040_origValue, sizeof(g_flt_8BD040));
g_flt_8BD044 = 0.0f;
float __g_flt_8BD044_origValue = 0.0f;
_memcpy(&g_flt_8BD044, &__g_flt_8BD044_origValue, sizeof(g_flt_8BD044));
g_flt_8BD048 = 0.0f;
float __g_flt_8BD048_origValue = 0.0f;
_memcpy(&g_flt_8BD048, &__g_flt_8BD048_origValue, sizeof(g_flt_8BD048));
g_flt_8BD04C = 0.0f;
float __g_flt_8BD04C_origValue = 0.0f;
_memcpy(&g_flt_8BD04C, &__g_flt_8BD04C_origValue, sizeof(g_flt_8BD04C));
g_flt_8BD050 = 0.0f;
float __g_flt_8BD050_origValue = 0.0f;
_memcpy(&g_flt_8BD050, &__g_flt_8BD050_origValue, sizeof(g_flt_8BD050));
g_flt_8BD054 = 0.0f;
float __g_flt_8BD054_origValue = 0.0f;
_memcpy(&g_flt_8BD054, &__g_flt_8BD054_origValue, sizeof(g_flt_8BD054));
g_flt_8BD058 = 0.0f;
float __g_flt_8BD058_origValue = 0.0f;
_memcpy(&g_flt_8BD058, &__g_flt_8BD058_origValue, sizeof(g_flt_8BD058));
sithWeapon_CurWeaponMode = 0;
int __sithWeapon_CurWeaponMode_origValue = 0;
_memcpy(&sithWeapon_CurWeaponMode, &__sithWeapon_CurWeaponMode_origValue, sizeof(sithWeapon_CurWeaponMode));
sithWeapon_bAutoPickup = 0;
int __sithWeapon_bAutoPickup_origValue = 0;
_memcpy(&sithWeapon_bAutoPickup, &__sithWeapon_bAutoPickup_origValue, sizeof(sithWeapon_bAutoPickup));
sithWeapon_bAutoSwitch = 0;
int __sithWeapon_bAutoSwitch_origValue = 0;
_memcpy(&sithWeapon_bAutoSwitch, &__sithWeapon_bAutoSwitch_origValue, sizeof(sithWeapon_bAutoSwitch));
sithWeapon_bAutoReload = 0;
int __sithWeapon_bAutoReload_origValue = 0;
_memcpy(&sithWeapon_bAutoReload, &__sithWeapon_bAutoReload_origValue, sizeof(sithWeapon_bAutoReload));
sithWeapon_bMultiAutoPickup = 0;
int __sithWeapon_bMultiAutoPickup_origValue = 0;
_memcpy(&sithWeapon_bMultiAutoPickup, &__sithWeapon_bMultiAutoPickup_origValue, sizeof(sithWeapon_bMultiAutoPickup));
sithWeapon_bMultiplayerAutoSwitch = 0;
int __sithWeapon_bMultiplayerAutoSwitch_origValue = 0;
_memcpy(&sithWeapon_bMultiplayerAutoSwitch, &__sithWeapon_bMultiplayerAutoSwitch_origValue, sizeof(sithWeapon_bMultiplayerAutoSwitch));
sithWeapon_bMultiAutoReload = 0;
int __sithWeapon_bMultiAutoReload_origValue = 0;
_memcpy(&sithWeapon_bMultiAutoReload, &__sithWeapon_bMultiAutoReload_origValue, sizeof(sithWeapon_bMultiAutoReload));
sithWeapon_bAutoAim = 0;
int __sithWeapon_bAutoAim_origValue = 0;
_memcpy(&sithWeapon_bAutoAim, &__sithWeapon_bAutoAim_origValue, sizeof(sithWeapon_bAutoAim));
sithWeapon_mountWait = 0.0f;
float __sithWeapon_mountWait_origValue = 0.0f;
_memcpy(&sithWeapon_mountWait, &__sithWeapon_mountWait_origValue, sizeof(sithWeapon_mountWait));
_memset(&sithWeapon_8BD0A0, 0, sizeof(sithWeapon_8BD0A0));
sithWeapon_fireWait = 0.0f;
float __sithWeapon_fireWait_origValue = 0.0f;
_memcpy(&sithWeapon_fireWait, &__sithWeapon_fireWait_origValue, sizeof(sithWeapon_fireWait));
sithWeapon_fireRate = 0.0f;
float __sithWeapon_fireRate_origValue = 0.0f;
_memcpy(&sithWeapon_fireRate, &__sithWeapon_fireRate_origValue, sizeof(sithWeapon_fireRate));
sithWeapon_LastFireTimeSecs = 0.0f;
float __sithWeapon_LastFireTimeSecs_origValue = 0.0f;
_memcpy(&sithWeapon_LastFireTimeSecs, &__sithWeapon_LastFireTimeSecs_origValue, sizeof(sithWeapon_LastFireTimeSecs));
_memset(&sithWeapon_a8BD030, 0, sizeof(sithWeapon_a8BD030));
sithWeapon_8BD05C = 0;
int __sithWeapon_8BD05C_origValue = 0;
_memcpy(&sithWeapon_8BD05C, &__sithWeapon_8BD05C_origValue, sizeof(sithWeapon_8BD05C));
sithWeapon_8BD060 = 0.0f;
float __sithWeapon_8BD060_origValue = 0.0f;
_memcpy(&sithWeapon_8BD060, &__sithWeapon_8BD060_origValue, sizeof(sithWeapon_8BD060));
_memset(&sithWeapon_8BD008, 0, sizeof(sithWeapon_8BD008));
sithWeapon_8BD024 = 0;
int __sithWeapon_8BD024_origValue = 0;
_memcpy(&sithWeapon_8BD024, &__sithWeapon_8BD024_origValue, sizeof(sithWeapon_8BD024));
sithWeapon_senderIndex = 0;
int __sithWeapon_senderIndex_origValue = 0;
_memcpy(&sithWeapon_senderIndex, &__sithWeapon_senderIndex_origValue, sizeof(sithWeapon_senderIndex));
_memset(&jkPlayer_playerInfos, 0, sizeof(jkPlayer_playerInfos));
_memset(&jkPlayer_playerShortName, 0, sizeof(jkPlayer_playerShortName));
jkPlayer_numOtherThings = 0;
int __jkPlayer_numOtherThings_origValue = 0;
_memcpy(&jkPlayer_numOtherThings, &__jkPlayer_numOtherThings_origValue, sizeof(jkPlayer_numOtherThings));
jkPlayer_numThings = 0;
int __jkPlayer_numThings_origValue = 0;
_memcpy(&jkPlayer_numThings, &__jkPlayer_numThings_origValue, sizeof(jkPlayer_numThings));
_memset(&jkPlayer_otherThings, 0, sizeof(jkPlayer_otherThings));
int  __jkPlayer_dword_525470_origValue =  1;
_memcpy(&jkPlayer_dword_525470, &__jkPlayer_dword_525470_origValue, sizeof(jkPlayer_dword_525470));
bShowInvisibleThings = 0;
int __bShowInvisibleThings_origValue = 0;
_memcpy(&bShowInvisibleThings, &__bShowInvisibleThings_origValue, sizeof(bShowInvisibleThings));
playerThingIdx = 0;
int __playerThingIdx_origValue = 0;
_memcpy(&playerThingIdx, &__playerThingIdx_origValue, sizeof(playerThingIdx));
_memset(&jkPlayer_maxPlayers, 0, sizeof(jkPlayer_maxPlayers));
sithPlayer_pLocalPlayerThing = NULL;
sithThing* __sithPlayer_pLocalPlayerThing_origValue = NULL;
_memcpy(&sithPlayer_pLocalPlayerThing, &__sithPlayer_pLocalPlayerThing_origValue, sizeof(sithPlayer_pLocalPlayerThing));
sithPlayer_pLocalPlayer = NULL;
sithPlayerInfo* __sithPlayer_pLocalPlayer_origValue = NULL;
_memcpy(&sithPlayer_pLocalPlayer, &__sithPlayer_pLocalPlayer_origValue, sizeof(sithPlayer_pLocalPlayer));
_memset(&playerThings, 0, sizeof(playerThings));
_memset(&jkSaber_rotateMat, 0, sizeof(jkSaber_rotateMat));
jkPlayer_setRotateOverlayMap = 0;
int __jkPlayer_setRotateOverlayMap_origValue = 0;
_memcpy(&jkPlayer_setRotateOverlayMap, &__jkPlayer_setRotateOverlayMap_origValue, sizeof(jkPlayer_setRotateOverlayMap));
jkPlayer_setDrawStatus = 0;
int __jkPlayer_setDrawStatus_origValue = 0;
_memcpy(&jkPlayer_setDrawStatus, &__jkPlayer_setDrawStatus_origValue, sizeof(jkPlayer_setDrawStatus));
jkPlayer_setCrosshair = 0;
int __jkPlayer_setCrosshair_origValue = 0;
_memcpy(&jkPlayer_setCrosshair, &__jkPlayer_setCrosshair_origValue, sizeof(jkPlayer_setCrosshair));
jkPlayer_setSaberCam = 0;
int __jkPlayer_setSaberCam_origValue = 0;
_memcpy(&jkPlayer_setSaberCam, &__jkPlayer_setSaberCam_origValue, sizeof(jkPlayer_setSaberCam));
jkPlayer_setFullSubtitles = 0;
int __jkPlayer_setFullSubtitles_origValue = 0;
_memcpy(&jkPlayer_setFullSubtitles, &__jkPlayer_setFullSubtitles_origValue, sizeof(jkPlayer_setFullSubtitles));
jkPlayer_setDisableCutscenes = 0;
int __jkPlayer_setDisableCutscenes_origValue = 0;
_memcpy(&jkPlayer_setDisableCutscenes, &__jkPlayer_setDisableCutscenes_origValue, sizeof(jkPlayer_setDisableCutscenes));
_memset(&jkPlayer_aCutsceneVal, 0, sizeof(jkPlayer_aCutsceneVal));
_memset(&jkPlayer_cutscenePath, 0, sizeof(jkPlayer_cutscenePath));
jkPlayer_setNumCutscenes = 0;
int __jkPlayer_setNumCutscenes_origValue = 0;
_memcpy(&jkPlayer_setNumCutscenes, &__jkPlayer_setNumCutscenes_origValue, sizeof(jkPlayer_setNumCutscenes));
jkPlayer_setDiff = 0;
int __jkPlayer_setDiff_origValue = 0;
_memcpy(&jkPlayer_setDiff, &__jkPlayer_setDiff_origValue, sizeof(jkPlayer_setDiff));
_memset(&jkPlayer_waggleVec, 0, sizeof(jkPlayer_waggleVec));
jkPlayer_waggleMag = 0.0f;
float __jkPlayer_waggleMag_origValue = 0.0f;
_memcpy(&jkPlayer_waggleMag, &__jkPlayer_waggleMag_origValue, sizeof(jkPlayer_waggleMag));
jkPlayer_mpcInfoSet = 0;
int __jkPlayer_mpcInfoSet_origValue = 0;
_memcpy(&jkPlayer_mpcInfoSet, &__jkPlayer_mpcInfoSet_origValue, sizeof(jkPlayer_mpcInfoSet));
jkPlayer_waggleAngle = 0.0f;
float __jkPlayer_waggleAngle_origValue = 0.0f;
_memcpy(&jkPlayer_waggleAngle, &__jkPlayer_waggleAngle_origValue, sizeof(jkPlayer_waggleAngle));
_memset(&jkSaber_rotateVec, 0, sizeof(jkSaber_rotateVec));
_memset(&jkPlayer_name, 0, sizeof(jkPlayer_name));
_memset(&jkPlayer_model, 0, sizeof(jkPlayer_model));
_memset(&jkPlayer_soundClass, 0, sizeof(jkPlayer_soundClass));
_memset(&jkPlayer_sideMat, 0, sizeof(jkPlayer_sideMat));
_memset(&jkPlayer_tipMat, 0, sizeof(jkPlayer_tipMat));
_memset(&sithCollision_stackIdk, 0, sizeof(sithCollision_stackIdk));
_memset(&sithCollision_collisionHandlers, 0, sizeof(sithCollision_collisionHandlers));
_memset(&sithCollision_funcList, 0, sizeof(sithCollision_funcList));
_memset(&sithCollision_searchStack, 0, sizeof(sithCollision_searchStack));
_memset(&sithCollision_searchNumResults, 0, sizeof(sithCollision_searchNumResults));
int  __sithCollision_searchStackIdx_origValue =  -1;
_memcpy(&sithCollision_searchStackIdx, &__sithCollision_searchStackIdx_origValue, sizeof(sithCollision_searchStackIdx));
_memset(&sithCollision_stackSectors, 0, sizeof(sithCollision_stackSectors));
sithCollision_dword_8B4BE4 = 0;
int __sithCollision_dword_8B4BE4_origValue = 0;
_memcpy(&sithCollision_dword_8B4BE4, &__sithCollision_dword_8B4BE4_origValue, sizeof(sithCollision_dword_8B4BE4));
_memset(&sithCollision_collideHurtIdk, 0, sizeof(sithCollision_collideHurtIdk));
rdVector3  __sithSector_surfaceNormal_origValue =  {0.0, 0.0, -1.0};
_memcpy(&sithSector_surfaceNormal, &__sithSector_surfaceNormal_origValue, sizeof(sithSector_surfaceNormal));
_memset(&sithAIAwareness_aEntries, 0, sizeof(sithAIAwareness_aEntries));
sithAIAwareness_aSectors = NULL;
sithSectorAlloc* __sithAIAwareness_aSectors_origValue = NULL;
_memcpy(&sithAIAwareness_aSectors, &__sithAIAwareness_aSectors_origValue, sizeof(sithAIAwareness_aSectors));
sithAIAwareness_numEntries = 0;
int __sithAIAwareness_numEntries_origValue = 0;
_memcpy(&sithAIAwareness_numEntries, &__sithAIAwareness_numEntries_origValue, sizeof(sithAIAwareness_numEntries));
sithAIAwareness_bInitted = 0;
int __sithAIAwareness_bInitted_origValue = 0;
_memcpy(&sithAIAwareness_bInitted, &__sithAIAwareness_bInitted_origValue, sizeof(sithAIAwareness_bInitted));
sithAIAwareness_timerTicks = 0;
int __sithAIAwareness_timerTicks_origValue = 0;
_memcpy(&sithAIAwareness_timerTicks, &__sithAIAwareness_timerTicks_origValue, sizeof(sithAIAwareness_timerTicks));
sithSector_flt_8553B8 = 0.0f;
float __sithSector_flt_8553B8_origValue = 0.0f;
_memcpy(&sithSector_flt_8553B8, &__sithSector_flt_8553B8_origValue, sizeof(sithSector_flt_8553B8));
sithSector_horizontalPixelsPerRev = 0.0f;
float __sithSector_horizontalPixelsPerRev_origValue = 0.0f;
_memcpy(&sithSector_horizontalPixelsPerRev, &__sithSector_horizontalPixelsPerRev_origValue, sizeof(sithSector_horizontalPixelsPerRev));
sithSector_flt_8553C0 = 0.0f;
float __sithSector_flt_8553C0_origValue = 0.0f;
_memcpy(&sithSector_flt_8553C0, &__sithSector_flt_8553C0_origValue, sizeof(sithSector_flt_8553C0));
sithSector_flt_8553C4 = 0.0f;
float __sithSector_flt_8553C4_origValue = 0.0f;
_memcpy(&sithSector_flt_8553C4, &__sithSector_flt_8553C4_origValue, sizeof(sithSector_flt_8553C4));
sithSector_flt_8553C8 = 0.0f;
float __sithSector_flt_8553C8_origValue = 0.0f;
_memcpy(&sithSector_flt_8553C8, &__sithSector_flt_8553C8_origValue, sizeof(sithSector_flt_8553C8));
_memset(&sithSector_zMaxVec, 0, sizeof(sithSector_zMaxVec));
sithSector_ceilingSky = 0.0f;
float __sithSector_ceilingSky_origValue = 0.0f;
_memcpy(&sithSector_ceilingSky, &__sithSector_ceilingSky_origValue, sizeof(sithSector_ceilingSky));
_memset(&sithSector_zMinVec, 0, sizeof(sithSector_zMinVec));
sithSector_horizontalPixelsPerRev_idk = 0.0f;
float __sithSector_horizontalPixelsPerRev_idk_origValue = 0.0f;
_memcpy(&sithSector_horizontalPixelsPerRev_idk, &__sithSector_horizontalPixelsPerRev_idk_origValue, sizeof(sithSector_horizontalPixelsPerRev_idk));
sithSector_horizontalDist = 0.0f;
float __sithSector_horizontalDist_origValue = 0.0f;
_memcpy(&sithSector_horizontalDist, &__sithSector_horizontalDist_origValue, sizeof(sithSector_horizontalDist));
sithSector_flt_8553F4 = 0.0f;
float __sithSector_flt_8553F4_origValue = 0.0f;
_memcpy(&sithSector_flt_8553F4, &__sithSector_flt_8553F4_origValue, sizeof(sithSector_flt_8553F4));
_memset(&sithSector_aSyncIdk, 0, sizeof(sithSector_aSyncIdk));
_memset(&sithSector_aSyncIdk2, 0, sizeof(sithSector_aSyncIdk2));
_memset(&sithSector_numSync, 0, sizeof(sithSector_numSync));
sithThing_paramKeyToParamValMap = NULL;
stdHashTable* __sithThing_paramKeyToParamValMap_origValue = NULL;
_memcpy(&sithThing_paramKeyToParamValMap, &__sithThing_paramKeyToParamValMap_origValue, sizeof(sithThing_paramKeyToParamValMap));
_memset(&sithThing_handler, 0, sizeof(sithThing_handler));
uint16_t  __sithThing_inittedThings_origValue =  1;
_memcpy(&sithThing_inittedThings, &__sithThing_inittedThings_origValue, sizeof(sithThing_inittedThings));
_memset(&jkGuiSaveLoad_wtextEpisode, 0, sizeof(jkGuiSaveLoad_wtextEpisode));
_memset(&jkGuiSaveLoad_wtextHealth, 0, sizeof(jkGuiSaveLoad_wtextHealth));
jkGuiSaveLoad_numEntries = 0;
int __jkGuiSaveLoad_numEntries_origValue = 0;
_memcpy(&jkGuiSaveLoad_numEntries, &__jkGuiSaveLoad_numEntries_origValue, sizeof(jkGuiSaveLoad_numEntries));
_memset(&jkGuiSaveLoad_wtextShields, 0, sizeof(jkGuiSaveLoad_wtextShields));
_memset(&jkGuiSaveLoad_word_559830, 0, sizeof(jkGuiSaveLoad_word_559830));
jkGuiSaveLoad_bIsSaveMenu = 0;
int __jkGuiSaveLoad_bIsSaveMenu_origValue = 0;
_memcpy(&jkGuiSaveLoad_bIsSaveMenu, &__jkGuiSaveLoad_bIsSaveMenu_origValue, sizeof(jkGuiSaveLoad_bIsSaveMenu));
_memset(&jkGuiSaveLoad_wtextSaveName, 0, sizeof(jkGuiSaveLoad_wtextSaveName));
_memset(&jkGuiSaveLoad_DarrayEntries, 0, sizeof(jkGuiSaveLoad_DarrayEntries));
_memset(&jkGuiSaveLoad_word_559C54, 0, sizeof(jkGuiSaveLoad_word_559C54));
_memset(&jkGuiSaveLoad_byte_559C50, 0, sizeof(jkGuiSaveLoad_byte_559C50));
int  __jkGuiTitle_verMajor_origValue =  1;
_memcpy(&jkGuiTitle_verMajor, &__jkGuiTitle_verMajor_origValue, sizeof(jkGuiTitle_verMajor));
int  __jkGuiTitle_verMinor_origValue =  0;
_memcpy(&jkGuiTitle_verMinor, &__jkGuiTitle_verMinor_origValue, sizeof(jkGuiTitle_verMinor));
int  __jkGuiTitle_verRevision_origValue =  0;
_memcpy(&jkGuiTitle_verRevision, &__jkGuiTitle_verRevision_origValue, sizeof(jkGuiTitle_verRevision));
_memset(&jkGuiTitle_aTexts, 0, sizeof(jkGuiTitle_aTexts));
jkGuiTitle_whichLoading = 0;
int __jkGuiTitle_whichLoading_origValue = 0;
_memcpy(&jkGuiTitle_whichLoading, &__jkGuiTitle_whichLoading_origValue, sizeof(jkGuiTitle_whichLoading));
float  __jkGuiSound_sfxVolume_origValue =  0.8;
_memcpy(&jkGuiSound_sfxVolume, &__jkGuiSound_sfxVolume_origValue, sizeof(jkGuiSound_sfxVolume));
uint32_t  __jkGuiSound_numChannels_origValue =  16;
_memcpy(&jkGuiSound_numChannels, &__jkGuiSound_numChannels_origValue, sizeof(jkGuiSound_numChannels));
jkGuiSound_bLowResSound = 0;
int __jkGuiSound_bLowResSound_origValue = 0;
_memcpy(&jkGuiSound_bLowResSound, &__jkGuiSound_bLowResSound_origValue, sizeof(jkGuiSound_bLowResSound));
int  __jkGuiSound_b3DSound_origValue =  1;
_memcpy(&jkGuiSound_b3DSound, &__jkGuiSound_b3DSound_origValue, sizeof(jkGuiSound_b3DSound));
int  __jkGuiSound_b3DSound_2_origValue =  1;
_memcpy(&jkGuiSound_b3DSound_2, &__jkGuiSound_b3DSound_2_origValue, sizeof(jkGuiSound_b3DSound_2));
int  __jkGuiSound_b3DSound_3_origValue =  1;
_memcpy(&jkGuiSound_b3DSound_3, &__jkGuiSound_b3DSound_3_origValue, sizeof(jkGuiSound_b3DSound_3));
jkGuiSound_musicVolume = 0.0f;
float __jkGuiSound_musicVolume_origValue = 0.0f;
_memcpy(&jkGuiSound_musicVolume, &__jkGuiSound_musicVolume_origValue, sizeof(jkGuiSound_musicVolume));
_memset(&jkGui_unkstr, 0, sizeof(jkGui_unkstr));
jkGui_GdiMode = 0;
int __jkGui_GdiMode_origValue = 0;
_memcpy(&jkGui_GdiMode, &__jkGui_GdiMode_origValue, sizeof(jkGui_GdiMode));
jkGui_modesets = 0;
int __jkGui_modesets_origValue = 0;
_memcpy(&jkGui_modesets, &__jkGui_modesets_origValue, sizeof(jkGui_modesets));
_memset(&jkGui_stdBitmaps, 0, sizeof(jkGui_stdBitmaps));
_memset(&jkGui_stdFonts, 0, sizeof(jkGui_stdFonts));
_memset(&jkGui_episodeLoad, 0, sizeof(jkGui_episodeLoad));
jkGuiSingleTally_foStars = NULL;
stdBitmap* __jkGuiSingleTally_foStars_origValue = NULL;
_memcpy(&jkGuiSingleTally_foStars, &__jkGuiSingleTally_foStars_origValue, sizeof(jkGuiSingleTally_foStars));
jkGuiNetHost_maxRank = 0;
int __jkGuiNetHost_maxRank_origValue = 0;
_memcpy(&jkGuiNetHost_maxRank, &__jkGuiNetHost_maxRank_origValue, sizeof(jkGuiNetHost_maxRank));
jkGuiNetHost_timeLimit = 0;
int __jkGuiNetHost_timeLimit_origValue = 0;
_memcpy(&jkGuiNetHost_timeLimit, &__jkGuiNetHost_timeLimit_origValue, sizeof(jkGuiNetHost_timeLimit));
jkGuiNetHost_scoreLimit = 0;
int __jkGuiNetHost_scoreLimit_origValue = 0;
_memcpy(&jkGuiNetHost_scoreLimit, &__jkGuiNetHost_scoreLimit_origValue, sizeof(jkGuiNetHost_scoreLimit));
jkGuiNetHost_maxPlayers = 0;
int __jkGuiNetHost_maxPlayers_origValue = 0;
_memcpy(&jkGuiNetHost_maxPlayers, &__jkGuiNetHost_maxPlayers_origValue, sizeof(jkGuiNetHost_maxPlayers));
jkGuiNetHost_sessionFlags = 0;
int __jkGuiNetHost_sessionFlags_origValue = 0;
_memcpy(&jkGuiNetHost_sessionFlags, &__jkGuiNetHost_sessionFlags_origValue, sizeof(jkGuiNetHost_sessionFlags));
jkGuiNetHost_gameFlags = 0;
int __jkGuiNetHost_gameFlags_origValue = 0;
_memcpy(&jkGuiNetHost_gameFlags, &__jkGuiNetHost_gameFlags_origValue, sizeof(jkGuiNetHost_gameFlags));
jkGuiNetHost_tickRate = 0;
int __jkGuiNetHost_tickRate_origValue = 0;
_memcpy(&jkGuiNetHost_tickRate, &__jkGuiNetHost_tickRate_origValue, sizeof(jkGuiNetHost_tickRate));
_memset(&jkGuiNetHost_gameName, 0, sizeof(jkGuiNetHost_gameName));
jkGuiMultiplayer_checksumSeed = 0;
int __jkGuiMultiplayer_checksumSeed_origValue = 0;
_memcpy(&jkGuiMultiplayer_checksumSeed, &__jkGuiMultiplayer_checksumSeed_origValue, sizeof(jkGuiMultiplayer_checksumSeed));
jkGuiMultiplayer_dword_5564EC = 0;
int __jkGuiMultiplayer_dword_5564EC_origValue = 0;
_memcpy(&jkGuiMultiplayer_dword_5564EC, &__jkGuiMultiplayer_dword_5564EC_origValue, sizeof(jkGuiMultiplayer_dword_5564EC));
jkGuiMultiplayer_dword_5564E8 = 0;
int __jkGuiMultiplayer_dword_5564E8_origValue = 0;
_memcpy(&jkGuiMultiplayer_dword_5564E8, &__jkGuiMultiplayer_dword_5564E8_origValue, sizeof(jkGuiMultiplayer_dword_5564E8));
_memset(&jkGuiMultiplayer_multiEntry, 0, sizeof(jkGuiMultiplayer_multiEntry));
jkGuiMultiplayer_dword_5564F0 = 0;
int __jkGuiMultiplayer_dword_5564F0_origValue = 0;
_memcpy(&jkGuiMultiplayer_dword_5564F0, &__jkGuiMultiplayer_dword_5564F0_origValue, sizeof(jkGuiMultiplayer_dword_5564F0));
_memset(&g_hInstance, 0, sizeof(g_hInstance));
sithCog_pSymbolTable = NULL;
sithCogSymboltable* __sithCog_pSymbolTable_origValue = NULL;
_memcpy(&sithCog_pSymbolTable, &__sithCog_pSymbolTable_origValue, sizeof(sithCog_pSymbolTable));
pSithHS = NULL;
struct HostServices* __pSithHS_origValue = NULL;
_memcpy(&pSithHS, &__pSithHS_origValue, sizeof(pSithHS));
_memset(&g_hWnd, 0, sizeof(g_hWnd));
_memset(&g_nShowCmd, 0, sizeof(g_nShowCmd));
_memset(&g_app_suspended, 0, sizeof(g_app_suspended));
_memset(&g_window_active, 0, sizeof(g_window_active));
_memset(&g_app_active, 0, sizeof(g_app_active));
_memset(&g_should_exit, 0, sizeof(g_should_exit));
_memset(&g_thing_two_some_dialog_count, 0, sizeof(g_thing_two_some_dialog_count));
_memset(&g_handler_count, 0, sizeof(g_handler_count));
_memset(&g_855E8C, 0, sizeof(g_855E8C));
_memset(&g_855E90, 0, sizeof(g_855E90));
_memset(&g_window_not_destroyed, 0, sizeof(g_window_not_destroyed));
_memset(&stdPalEffects_state, 0, sizeof(stdPalEffects_state));
_memset(&stdPalEffects_palette, 0, sizeof(stdPalEffects_palette));
_memset(&stdPalEffects_numEffectRequests, 0, sizeof(stdPalEffects_numEffectRequests));
_memset(&stdPalEffects_aEffects, 0, sizeof(stdPalEffects_aEffects));
_memset(&stdPalEffects_setPalette, 0, sizeof(stdPalEffects_setPalette));
_memset(&stdPalEffects_aPalette, 0, sizeof(stdPalEffects_aPalette));
_memset(&aFilenameStack, 0, sizeof(aFilenameStack));
_memset(&apBufferStack, 0, sizeof(apBufferStack));
_memset(&linenumStack, 0, sizeof(linenumStack));
_memset(&aEntryStack, 0, sizeof(aEntryStack));
_memset(&openFileStack, 0, sizeof(openFileStack));
_memset(&printfBuffer, 0, sizeof(printfBuffer));
stdConffile_linenum = 0;
int __stdConffile_linenum_origValue = 0;
_memcpy(&stdConffile_linenum, &__stdConffile_linenum_origValue, sizeof(stdConffile_linenum));
stdConffile_bOpen = 0;
int __stdConffile_bOpen_origValue = 0;
_memcpy(&stdConffile_bOpen, &__stdConffile_bOpen_origValue, sizeof(stdConffile_bOpen));
_memset(&openFile, 0, sizeof(openFile));
_memset(&writeFile, 0, sizeof(writeFile));
_memset(&stackLevel, 0, sizeof(stackLevel));
_memset(&stdConffile_aWriteFilename, 0, sizeof(stdConffile_aWriteFilename));
_memset(&stdConffile_entry, 0, sizeof(stdConffile_entry));
_memset(&stdConffile_pFilename, 0, sizeof(stdConffile_pFilename));
stdConffile_aLine = NULL;
char* __stdConffile_aLine_origValue = NULL;
_memcpy(&stdConffile_aLine, &__stdConffile_aLine_origValue, sizeof(stdConffile_aLine));
stdMemory_bInitted = 0;
int __stdMemory_bInitted_origValue = 0;
_memcpy(&stdMemory_bInitted, &__stdMemory_bInitted_origValue, sizeof(stdMemory_bInitted));
stdMemory_bOpened = 0;
int __stdMemory_bOpened_origValue = 0;
_memcpy(&stdMemory_bOpened, &__stdMemory_bOpened_origValue, sizeof(stdMemory_bOpened));
_memset(&stdMemory_info, 0, sizeof(stdMemory_info));
_memset(&yyin, 0, sizeof(yyin));
_memset(&yyout, 0, sizeof(yyout));
sithCogParse_pSymbolTable = NULL;
sithCogSymboltable* __sithCogParse_pSymbolTable_origValue = NULL;
_memcpy(&sithCogParse_pSymbolTable, &__sithCogParse_pSymbolTable_origValue, sizeof(sithCogParse_pSymbolTable));
yacc_linenum = 0;
int __yacc_linenum_origValue = 0;
_memcpy(&yacc_linenum, &__yacc_linenum_origValue, sizeof(yacc_linenum));
int  __cog_yacc_loop_depth_origValue =  1;
_memcpy(&cog_yacc_loop_depth, &__cog_yacc_loop_depth_origValue, sizeof(cog_yacc_loop_depth));
_memset(&cog_parser_node_stackpos, 0, sizeof(cog_parser_node_stackpos));
cogvm_stackpos = 0;
int __cogvm_stackpos_origValue = 0;
_memcpy(&cogvm_stackpos, &__cogvm_stackpos_origValue, sizeof(cogvm_stackpos));
cogparser_nodes_alloc = NULL;
sith_cog_parser_node* __cogparser_nodes_alloc_origValue = NULL;
_memcpy(&cogparser_nodes_alloc, &__cogparser_nodes_alloc_origValue, sizeof(cogparser_nodes_alloc));
cogparser_topnode = NULL;
sith_cog_parser_node* __cogparser_topnode_origValue = NULL;
_memcpy(&cogparser_topnode, &__cogparser_topnode_origValue, sizeof(cogparser_topnode));
cogvm_stack = NULL;
int* __cogvm_stack_origValue = NULL;
_memcpy(&cogvm_stack, &__cogvm_stack_origValue, sizeof(cogvm_stack));
cogparser_num_nodes = 0;
int __cogparser_num_nodes_origValue = 0;
_memcpy(&cogparser_num_nodes, &__cogparser_num_nodes_origValue, sizeof(cogparser_num_nodes));
cogparser_current_nodeidx = 0;
int __cogparser_current_nodeidx_origValue = 0;
_memcpy(&cogparser_current_nodeidx, &__cogparser_current_nodeidx_origValue, sizeof(cogparser_current_nodeidx));
parsing_script = NULL;
sithCogScript* __parsing_script_origValue = NULL;
_memcpy(&parsing_script, &__parsing_script_origValue, sizeof(parsing_script));
int  __parsing_script_idk_origValue =  1;
_memcpy(&parsing_script_idk, &__parsing_script_idk_origValue, sizeof(parsing_script_idk));
dplay_dword_55D618 = 0;
int __dplay_dword_55D618_origValue = 0;
_memcpy(&dplay_dword_55D618, &__dplay_dword_55D618_origValue, sizeof(dplay_dword_55D618));
dplay_dword_55D61C = 0;
int __dplay_dword_55D61C_origValue = 0;
_memcpy(&dplay_dword_55D61C, &__dplay_dword_55D61C_origValue, sizeof(dplay_dword_55D61C));
_memset(&jkGui_guid_556040, 0, sizeof(jkGui_guid_556040));
jkGuiMultiplayer_numConnections = 0;
int __jkGuiMultiplayer_numConnections_origValue = 0;
_memcpy(&jkGuiMultiplayer_numConnections, &__jkGuiMultiplayer_numConnections_origValue, sizeof(jkGuiMultiplayer_numConnections));
_memset(&jkGuiMultiplayer_aConnections, 0, sizeof(jkGuiMultiplayer_aConnections));
_memset(&jkGuiMultiplayer_aEntries, 0, sizeof(jkGuiMultiplayer_aEntries));
_memset(&jkGuiMultiplayer_stru_556168, 0, sizeof(jkGuiMultiplayer_stru_556168));
_memset(&jkGuiMultiplayer_mpcInfo, 0, sizeof(jkGuiMultiplayer_mpcInfo));
_memset(&jkGuiMultiplayer_stru_5564A8, 0, sizeof(jkGuiMultiplayer_stru_5564A8));
jkGuiMouse_bOpen = 0;
int __jkGuiMouse_bOpen_origValue = 0;
_memcpy(&jkGuiMouse_bOpen, &__jkGuiMouse_bOpen_origValue, sizeof(jkGuiMouse_bOpen));
_memset(&jkGuiMouse_Darray_556698, 0, sizeof(jkGuiMouse_Darray_556698));
jkGuiMouse_dword_5566B0 = 0;
int __jkGuiMouse_dword_5566B0_origValue = 0;
_memcpy(&jkGuiMouse_dword_5566B0, &__jkGuiMouse_dword_5566B0_origValue, sizeof(jkGuiMouse_dword_5566B0));
_memset(&jkGuiMouse_Darray_5566B8, 0, sizeof(jkGuiMouse_Darray_5566B8));
_memset(&jkGuiMouse_Darray_5566D0, 0, sizeof(jkGuiMouse_Darray_5566D0));
jkGuiMouse_pWStr_5566E8 = NULL;
wchar_t* __jkGuiMouse_pWStr_5566E8_origValue = NULL;
_memcpy(&jkGuiMouse_pWStr_5566E8, &__jkGuiMouse_pWStr_5566E8_origValue, sizeof(jkGuiMouse_pWStr_5566E8));
jkGuiEsc_bInitialized = 0;
int __jkGuiEsc_bInitialized_origValue = 0;
_memcpy(&jkGuiEsc_bInitialized, &__jkGuiEsc_bInitialized_origValue, sizeof(jkGuiEsc_bInitialized));
jkGuiKeyboard_dword_555DE0 = 0;
int __jkGuiKeyboard_dword_555DE0_origValue = 0;
_memcpy(&jkGuiKeyboard_dword_555DE0, &__jkGuiKeyboard_dword_555DE0_origValue, sizeof(jkGuiKeyboard_dword_555DE0));
jkGuiKeyboard_bOnceIdk = 0;
int __jkGuiKeyboard_bOnceIdk_origValue = 0;
_memcpy(&jkGuiKeyboard_bOnceIdk, &__jkGuiKeyboard_bOnceIdk_origValue, sizeof(jkGuiKeyboard_bOnceIdk));
jkGuiKeyboard_funcIdx = 0;
int __jkGuiKeyboard_funcIdx_origValue = 0;
_memcpy(&jkGuiKeyboard_funcIdx, &__jkGuiKeyboard_funcIdx_origValue, sizeof(jkGuiKeyboard_funcIdx));
jkGuiKeyboard_flags = 0;
int __jkGuiKeyboard_flags_origValue = 0;
_memcpy(&jkGuiKeyboard_flags, &__jkGuiKeyboard_flags_origValue, sizeof(jkGuiKeyboard_flags));
_memset(&jkGuiKeyboard_darrEntries, 0, sizeof(jkGuiKeyboard_darrEntries));
jkGuiKeyboard_dword_555E10 = 0;
int __jkGuiKeyboard_dword_555E10_origValue = 0;
_memcpy(&jkGuiKeyboard_dword_555E10, &__jkGuiKeyboard_dword_555E10_origValue, sizeof(jkGuiKeyboard_dword_555E10));
_memset(&jkGuiKeyboard_wstr_555E18, 0, sizeof(jkGuiKeyboard_wstr_555E18));
jkGuiKeyboard_pWStr_55601C = NULL;
wchar_t* __jkGuiKeyboard_pWStr_55601C_origValue = NULL;
_memcpy(&jkGuiKeyboard_pWStr_55601C, &__jkGuiKeyboard_pWStr_55601C_origValue, sizeof(jkGuiKeyboard_pWStr_55601C));
_memset(&jkGuiMap_vec3Idk2, 0, sizeof(jkGuiMap_vec3Idk2));
jkGuiMap_pCanvas = NULL;
rdCanvas* __jkGuiMap_pCanvas_origValue = NULL;
_memcpy(&jkGuiMap_pCanvas, &__jkGuiMap_pCanvas_origValue, sizeof(jkGuiMap_pCanvas));
_memset(&jkGuiMap_viewMat, 0, sizeof(jkGuiMap_viewMat));
_memset(&jkGuiMap_matTmp, 0, sizeof(jkGuiMap_matTmp));
jkGuiMap_pVbuffer = NULL;
stdVBuffer* __jkGuiMap_pVbuffer_origValue = NULL;
_memcpy(&jkGuiMap_pVbuffer, &__jkGuiMap_pVbuffer_origValue, sizeof(jkGuiMap_pVbuffer));
_memset(&jkGuiMap_unk4, 0, sizeof(jkGuiMap_unk4));
_memset(&jkGuiMap_vec3Idk, 0, sizeof(jkGuiMap_vec3Idk));
jkGuiMap_pCamera = NULL;
rdCamera* __jkGuiMap_pCamera_origValue = NULL;
_memcpy(&jkGuiMap_pCamera, &__jkGuiMap_pCamera_origValue, sizeof(jkGuiMap_pCamera));
jkGuiMap_dword_556660 = 0;
int __jkGuiMap_dword_556660_origValue = 0;
_memcpy(&jkGuiMap_dword_556660, &__jkGuiMap_dword_556660_origValue, sizeof(jkGuiMap_dword_556660));
jkGuiMap_dword_556664 = 0;
int __jkGuiMap_dword_556664_origValue = 0;
_memcpy(&jkGuiMap_dword_556664, &__jkGuiMap_dword_556664_origValue, sizeof(jkGuiMap_dword_556664));
jkGuiMap_dword_556668 = 0;
int __jkGuiMap_dword_556668_origValue = 0;
_memcpy(&jkGuiMap_dword_556668, &__jkGuiMap_dword_556668_origValue, sizeof(jkGuiMap_dword_556668));
jkGuiMap_dword_55666C = 0;
int __jkGuiMap_dword_55666C_origValue = 0;
_memcpy(&jkGuiMap_dword_55666C, &__jkGuiMap_dword_55666C_origValue, sizeof(jkGuiMap_dword_55666C));
float __sithMap_unkArr_origValue[12]  =  {0.5, 1.0, 1.5, 2.0, 2.5, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 0.0};
_memcpy(&sithMap_unkArr, &__sithMap_unkArr_origValue, sizeof(sithMap_unkArr));
sithMap_pPlayerThing = NULL;
sithThing* __sithMap_pPlayerThing_origValue = NULL;
_memcpy(&sithMap_pPlayerThing, &__sithMap_pPlayerThing_origValue, sizeof(sithMap_pPlayerThing));
_memset(&sithMap_invMatrix, 0, sizeof(sithMap_invMatrix));
sithMap_flt_84DEA8 = 0.0f;
float __sithMap_flt_84DEA8_origValue = 0.0f;
_memcpy(&sithMap_flt_84DEA8, &__sithMap_flt_84DEA8_origValue, sizeof(sithMap_flt_84DEA8));
sithMap_flt_84DEAC = 0.0f;
float __sithMap_flt_84DEAC_origValue = 0.0f;
_memcpy(&sithMap_flt_84DEAC, &__sithMap_flt_84DEAC_origValue, sizeof(sithMap_flt_84DEAC));
_memset(&sithMap_ctx, 0, sizeof(sithMap_ctx));
sithMap_pCurWorld = NULL;
sithWorld* __sithMap_pCurWorld_origValue = NULL;
_memcpy(&sithMap_pCurWorld, &__sithMap_pCurWorld_origValue, sizeof(sithMap_pCurWorld));
_memset(&sithMap_camera, 0, sizeof(sithMap_camera));
sithMap_pCurCamera = NULL;
rdCamera* __sithMap_pCurCamera_origValue = NULL;
_memcpy(&sithMap_pCurCamera, &__sithMap_pCurCamera_origValue, sizeof(sithMap_pCurCamera));
sithMap_bInitted = 0;
int __sithMap_bInitted_origValue = 0;
_memcpy(&sithMap_bInitted, &__sithMap_bInitted_origValue, sizeof(sithMap_bInitted));
sithMap_var = 0;
int __sithMap_var_origValue = 0;
_memcpy(&sithMap_var, &__sithMap_var_origValue, sizeof(sithMap_var));
_memset(&DirectPlay_numPlayers, 0, sizeof(DirectPlay_numPlayers));
_memset(&DirectPlay_aPlayers, 0, sizeof(DirectPlay_aPlayers));
}

const size_t embeddedResource_aFiles_num = 17;
const embeddedResource_t embeddedResource_aFiles[17] = {
{"shaders/blur_f.glsl", 
"uniform sampler2D tex;\n"
"uniform vec2 iResolution;\n"
"uniform float param1;\n"
"uniform float param2;\n"
"uniform float param3;\n"
"in vec4 f_color;\n"
"in vec2 f_uv;\n"
"in vec3 f_coord;\n"
"out vec4 fragColor;\n"
"\n"
"void main(void)\n"
"{\n"
"    float Pi = 6.28318530718; // Pi*2\n"
"    \n"
"    // GAUSSIAN BLUR SETTINGS {{{\n"
"    float Directions = param1; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)\n"
"    float Quality = param2; // BLUR QUALITY (Default 4.0 - More is better but slower)\n"
"    float Size = param3; // BLUR SIZE (Radius)\n"
"    // GAUSSIAN BLUR SETTINGS }}}\n"
"   \n"
"    vec2 Radius = Size/iResolution.xy;\n"
"    \n"
"    // Pixel colour\n"
"    vec4 Color = texture(tex, f_uv, 1.0);\n"
"    \n"
"    // Blur calculations\n"
"    for( float d=0.0; d<Pi; d+=Pi/Directions)\n"
"    {\n"
"        for(float i=1.0/Quality; i<=1.0; i+=1.0/Quality)\n"
"        {\n"
"            Color += texture( tex, f_uv+vec2(cos(d),sin(d))*Radius*i, 1.0);     \n"
"        }\n"
"    }\n"
"    \n"
"    // Output to screen\n"
"    Color /= Quality * Directions;// - (Directions == 16.0 ? 15.0 : 0.0); // HACK\n"
"\n"
"    fragColor = Color;\n"
"    //fragColor.a = 1.0;\n"
"\n"
"    //fragColor = vec4(1.0, 1.0, 0.0, 0.5);\n"
"}\n"
"\n"
, 0x44e},
{"shaders/blur_v.glsl", 
"in vec3 coord3d;\n"
"in vec4 v_color;\n"
"in vec2 v_uv;\n"
"uniform mat4 mvp;\n"
"out vec4 f_color;\n"
"out vec2 f_uv;\n"
"out vec3 f_coord;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 pos = mvp * vec4(coord3d, 1.0);\n"
"    pos.w = 1.0/(1.0-coord3d.z);\n"
"    pos.xyz *= pos.w;\n"
"    gl_Position = pos;\n"
"    f_color = v_color;\n"
"    f_uv = v_uv;\n"
"    f_coord = coord3d;\n"
"}\n"
"\n"
, 0x140},
{"shaders/default_f.glsl", 
"#ifdef GL_ARB_texture_gather\n"
"#define HAS_TEXTUREGATHER\n"
"#endif\n"
"\n"
"#ifdef HAS_TEXTUREGATHER\n"
"vec4 impl_textureGather(sampler2D tex, vec2 uv)\n"
"{\n"
"    return textureGather(tex, uv);\n"
"}\n"
"#else\n"
"float modI(float a,float b) {\n"
"    float m=a-floor((a+0.5)/b)*b;\n"
"    return floor(m+0.5);\n"
"}\n"
"\n"
"vec4 impl_textureGather(sampler2D tex, vec2 uv)\n"
"{\n"
"    ivec2 idims = textureSize(tex,0) - ivec2(1, 1);\n"
"    vec2 dims = vec2(idims);\n"
"\n"
"    ivec2 base = ivec2(dims*uv);\n"
"    if (base.x < 0) {\n"
"        //base.x = -base.x;\n"
"    }\n"
"    if (base.y < 0) {\n"
"        //base.y = -base.y;\n"
"    }\n"
"\n"
"    base.x = int(modI(float(base.x), dims.x));\n"
"    base.y = int(modI(float(base.y), dims.y));\n"
"\n"
"    return vec4(texelFetch(tex,base+ivec2(0,1),0).x,\n"
"        texelFetch(tex,base+ivec2(1,1),0).x,\n"
"        texelFetch(tex,base+ivec2(1,0),0).x,\n"
"        texelFetch(tex,base+ivec2(0,0),0).x\n"
"    );\n"
"}\n"
"#endif\n"
"\n"
"#define LIGHT_DIVISOR (6.0)\n"
"#define TEX_MODE_TEST 0\n"
"#define TEX_MODE_WORLDPAL 1\n"
"#define TEX_MODE_BILINEAR 2\n"
"#define TEX_MODE_16BPP 5\n"
"#define TEX_MODE_BILINEAR_16BPP 6\n"
"\n"
"#define D3DBLEND_ONE             (2)\n"
"#define D3DBLEND_SRCALPHA        (5)\n"
"#define D3DBLEND_INVSRCALPHA     (6)\n"
"\n"
"uniform sampler2D tex;\n"
"uniform sampler2D texEmiss;\n"
"uniform sampler2D worldPalette;\n"
"uniform sampler2D worldPaletteLights;\n"
"uniform sampler2D displacement_map;\n"
"uniform int tex_mode;\n"
"uniform int blend_mode;\n"
"uniform vec3 colorEffects_tint;\n"
"uniform vec3 colorEffects_filter;\n"
"uniform float colorEffects_fade;\n"
"uniform vec3 colorEffects_add;\n"
"uniform vec3 emissiveFactor;\n"
"uniform vec4 albedoFactor;\n"
"uniform float displacement_factor;\n"
"uniform float light_mult;\n"
"uniform vec2 iResolution;\n"
"\n"
"in vec4 f_color;\n"
"in float f_light;\n"
"in vec2 f_uv;\n"
"in vec3 f_coord;\n"
"\n"
"layout(location = 0) out vec4 fragColor;\n"
"layout(location = 1) out vec4 fragColorEmiss;\n"
"layout(location = 2) out vec4 fragColorPos;\n"
"layout(location = 3) out vec4 fragColorNormal;\n"
"\n"
"float luminance(vec3 c_rgb)\n"
"{\n"
"    const vec3 W = vec3(0.2125, 0.7154, 0.0721);\n"
"    return dot(c_rgb, W);\n"
"}\n"
"\n"
"vec3 normals(vec3 pos) {\n"
"    vec3 fdx = dFdx(pos);\n"
"    vec3 fdy = dFdy(pos);\n"
"    return normalize(cross(fdx, fdy));\n"
"}\n"
"\n"
"mat3 construct_tbn(vec3 vp_normal, vec3 adjusted_coords)\n"
"{\n"
"    vec3 n = normalize(vp_normal);\n"
"\n"
"    vec3 dp1 = dFdx(adjusted_coords);\n"
"    vec3 dp2 = dFdy(adjusted_coords);\n"
"    vec2 duv1 = dFdx(f_uv);\n"
"    vec2 duv2 = dFdy(f_uv);\n"
"\n"
"    vec3 dp2perp = cross(dp2, n);\n"
"    vec3 dp1perp = cross(n, dp1);\n"
"\n"
"    vec3 t = dp2perp * duv1.x + dp1perp * duv2.x;\n"
"    vec3 b = dp2perp * duv1.y + dp1perp * duv2.y;\n"
"\n"
"    float invmax = inversesqrt(max(dot(t, t), dot(b, b)));\n"
"    return mat3(t * invmax, b * invmax, n);\n"
"}\n"
"\n"
"vec2 parallax_mapping(vec2 tc, vec3 vp_normal, vec3 adjusted_coords)\n"
"{\n"
"    /*if (f_coord.x < 0.5) {\n"
"        return tc;\n"
"    }*/\n"
"\n"
"    // The injector world space view position is always considered (0, 0, 0):\n"
"    vec3 view_dir = -normalize(transpose(construct_tbn(vp_normal, adjusted_coords)) * adjusted_coords);\n"
"\n"
"    const float min_layers = 32.0;\n"
"    const float max_layers = 128.0;\n"
"    float num_layers = mix(max_layers, min_layers, abs(dot(vec3(0.0, 0.0, 1.0), view_dir)));\n"
"\n"
"    float layer_depth = 1.0 / num_layers;\n"
"    float current_layer_depth = 0.0;\n"
"    vec2 shift_per_layer = (view_dir.xy / view_dir.z) * displacement_factor;\n"
"    vec2 d_tc = shift_per_layer / num_layers;\n"
"\n"
"    vec2 current_tc = tc;\n"
"    float current_sample = texture(displacement_map, current_tc).r;\n"
"\n"
"    while(current_layer_depth < current_sample) {\n"
"        current_tc -= d_tc;\n"
"        current_sample = texture(displacement_map, current_tc).r;\n"
"        current_layer_depth += layer_depth;\n"
"    }\n"
"\n"
"    vec2 prev_tc = current_tc + d_tc;\n"
"\n"
"    float after_col_depth = current_sample - current_layer_depth;\n"
"    float before_col_depth = texture(displacement_map, prev_tc).r - current_layer_depth + layer_depth;\n"
"\n"
"    float a = after_col_depth / (after_col_depth - before_col_depth);\n"
"    vec2 adj_tc = mix(current_tc, prev_tc, a);\n"
"\n"
"    return adj_tc;\n"
"}\n"
"\n"
"#ifdef CAN_BILINEAR_FILTER\n"
"vec4 bilinear_paletted()\n"
"{\n"
"    // Get texture size in pixels:\n"
"    vec2 colorTextureSize = vec2(textureSize(tex, 0));\n"
"\n"
"    // Convert UV coordinates to pixel coordinates and get pixel index of top left pixel (assuming UVs are relative to top left corner of texture)\n"
"    vec2 pixCoord = f_uv * colorTextureSize - 0.5f;    // First pixel goes from -0.5 to +0.4999 (0.0 is center) last pixel goes from (size - 1.5) to (size - 0.5000001)\n"
"    vec2 originPixCoord = floor(pixCoord);              // Pixel index coordinates of bottom left pixel of set of 4 we will be blending\n"
"\n"
"    // For Gather we want UV coordinates of bottom right corner of top left pixel\n"
"    vec2 gUV = (originPixCoord + 1.0f) / colorTextureSize;\n"
"\n"
"    vec4 gIndex   = impl_textureGather(tex, gUV);\n"
"\n"
"    vec4 c00   = texture(worldPalette, vec2(gIndex.w, 0.5));\n"
"    vec4 c01 = texture(worldPalette, vec2(gIndex.x, 0.5));\n"
"    vec4 c11  = texture(worldPalette, vec2(gIndex.y, 0.5));\n"
"    vec4 c10 = texture(worldPalette, vec2(gIndex.z, 0.5));\n"
"\n"
"    if (blend_mode == D3DBLEND_SRCALPHA || blend_mode == D3DBLEND_INVSRCALPHA) {\n"
"        if (gIndex.x == 0.0) {\n"
"            c01.a = 0.0;\n"
"        }\n"
"        if (gIndex.y == 0.0) {\n"
"            c11.a = 0.0;\n"
"        }\n"
"        if (gIndex.z == 0.0) {\n"
"            c10.a = 0.0;\n"
"        }\n"
"        if (gIndex.w == 0.0) {\n"
"            c00.a = 0.0;\n"
"        }\n"
"    }\n"
"\n"
"    vec2 filterWeight = pixCoord - originPixCoord;\n"
" \n"
"    // Bi-linear mixing:\n"
"    vec4 temp0 = mix(c01, c11, filterWeight.x);\n"
"    vec4 temp1 = mix(c00, c10, filterWeight.x);\n"
"    vec4 blendColor = mix(temp1, temp0, filterWeight.y);\n"
"\n"
"    return vec4(blendColor.r, blendColor.g, blendColor.b, blendColor.a);\n"
"}\n"
"\n"
"vec4 bilinear_paletted_light(float index)\n"
"{\n"
"    // Makes sure light is in a sane range\n"
"    float light = clamp(f_light, 0.0, 1.0);\n"
"\n"
"    // Special case for lightsabers\n"
"    //if (index * 255.0 >= 16.0 && index * 255.0 < 17.0)\n"
"    //    light = 0.0;\n"
"\n"
"    // Take the fragment light, and divide by 4.0 to select for colors\n"
"    // which glow in the dark\n"
"    float light_idx = light / LIGHT_DIVISOR;\n"
"\n"
"    // Get texture size in pixels:\n"
"    vec2 colorTextureSize = vec2(textureSize(tex, 0));\n"
"\n"
"    // Convert UV coordinates to pixel coordinates and get pixel index of top left pixel (assuming UVs are relative to top left corner of texture)\n"
"    vec2 pixCoord = f_uv * colorTextureSize - 0.5f;    // First pixel goes from -0.5 to +0.4999 (0.0 is center) last pixel goes from (size - 1.5) to (size - 0.5000001)\n"
"    vec2 originPixCoord = floor(pixCoord);              // Pixel index coordinates of bottom left pixel of set of 4 we will be blending\n"
"\n"
"    // For Gather we want UV coordinates of bottom right corner of top left pixel\n"
"    vec2 gUV = (originPixCoord + 1.0f) / colorTextureSize;\n"
"\n"
"    vec4 gIndex   = impl_textureGather(tex, gUV);\n"
"\n"
"    vec4 c00   = texture(worldPalette, vec2(texture(worldPaletteLights, vec2(gIndex.w, light_idx)).r, 0.5));\n"
"    vec4 c01 = texture(worldPalette, vec2(texture(worldPaletteLights, vec2(gIndex.x, light_idx)).r, 0.5));\n"
"    vec4 c11  = texture(worldPalette, vec2(texture(worldPaletteLights, vec2(gIndex.y, light_idx)).r, 0.5));\n"
"    vec4 c10 = texture(worldPalette, vec2(texture(worldPaletteLights, vec2(gIndex.z, light_idx)).r, 0.5));\n"
"\n"
"    /*if (blend_mode == D3DBLEND_SRCALPHA || blend_mode == D3DBLEND_INVSRCALPHA) {\n"
"        if (gIndex.x == 0.0) {\n"
"            c01.a = 0.0;\n"
"        }\n"
"        if (gIndex.y == 0.0) {\n"
"            c11.a = 0.0;\n"
"        }\n"
"        if (gIndex.z == 0.0) {\n"
"            c10.a = 0.0;\n"
"        }\n"
"        if (gIndex.w == 0.0) {\n"
"            c00.a = 0.0;\n"
"        }\n"
"    }*/\n"
"\n"
"    vec2 filterWeight = pixCoord - originPixCoord;\n"
" \n"
"    // Bi-linear mixing:\n"
"    vec4 temp0 = mix(c01, c11, filterWeight.x);\n"
"    vec4 temp1 = mix(c00, c10, filterWeight.x);\n"
"    vec4 blendColor = mix(temp1, temp0, filterWeight.y);\n"
"    vec4 light_mult_quad = vec4(light_mult, light_mult, light_mult, 1.0);\n"
"\n"
"    return vec4(blendColor.r, blendColor.g, blendColor.b, 1.0) * light_mult_quad ;//* (1.0 - light) * light_mult;\n"
"}\n"
"#endif\n"
"\n"
"void main(void)\n"
"{\n"
"    float originalZ = gl_FragCoord.z / gl_FragCoord.w;\n"
"    vec3 adjusted_coords = vec3(f_coord.x/iResolution.x, f_coord.y/iResolution.y, originalZ);\n"
"    vec3 adjusted_coords_norms = vec3(gl_FragCoord.x/iResolution.x, gl_FragCoord.y/iResolution.y, 1.0/gl_FragCoord.z);\n"
"    vec3 adjusted_coords_parallax = vec3(adjusted_coords_norms.x - 0.5, adjusted_coords_norms.y - 0.5, gl_FragCoord.z);\n"
"    vec3 face_normals = normals(adjusted_coords_norms);\n"
"    vec3 face_normals_parallax = normals(adjusted_coords_parallax);\n"
"\n"
"    vec2 adj_texcoords = f_uv;\n"
"    if(displacement_factor != 0.0) {\n"
"        adj_texcoords = parallax_mapping(f_uv, face_normals_parallax, adjusted_coords_parallax);\n"
"    }\n"
"\n"
"    vec4 sampled = texture(tex, adj_texcoords);\n"
"    vec4 sampledEmiss = texture(texEmiss, adj_texcoords);\n"
"    vec4 sampled_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
"    vec4 vertex_color = f_color;\n"
"    float index = sampled.r;\n"
"    vec4 palval = texture(worldPalette, vec2(index, 0.5));\n"
"    vec4 color_add = vec4(0.0, 0.0, 0.0, 1.0);\n"
"    vec4 color_add_emiss = vec4(0.0, 0.0, 0.0, 0.0);\n"
"\n"
"    if (tex_mode == TEX_MODE_TEST) {\n"
"        sampled_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
"    }\n"
"    else if (tex_mode == TEX_MODE_16BPP\n"
"    || tex_mode == TEX_MODE_BILINEAR_16BPP\n"
"    )\n"
"    {\n"
"        sampled_color = vec4(sampled.b, sampled.g, sampled.r, sampled.a);\n"
"    }\n"
"    else if (tex_mode == TEX_MODE_WORLDPAL\n"
"#ifndef CAN_BILINEAR_FILTER\n"
"    || tex_mode == TEX_MODE_BILINEAR\n"
"#endif\n"
"    )\n"
"\n"
"    {\n"
"        if (index == 0.0 && (blend_mode == D3DBLEND_SRCALPHA || blend_mode == D3DBLEND_INVSRCALPHA))\n"
"            discard;\n"
"\n"
"        // Makes sure light is in a sane range\n"
"        float light = clamp(f_light, 0.0, 1.0);\n"
"\n"
"        // Special case for lightsabers\n"
"        //if (index * 255.0 >= 16.0 && index * 255.0 < 17.0)\n"
"        //    light = 0.0;\n"
"\n"
"        // Take the fragment light, and divide by 4.0 to select for colors\n"
"        // which glow in the dark\n"
"        float light_idx = light / LIGHT_DIVISOR;\n"
"\n"
"        // Get the shaded palette index\n"
"        float light_worldpalidx = texture(worldPaletteLights, vec2(index, light_idx)).r;\n"
"\n"
"        // Now take our index and look up the corresponding palette value\n"
"        vec4 lightPalval = texture(worldPalette, vec2(light_worldpalidx, 0.5));\n"
"\n"
"        // Add more of the emissive color depending on the darkness of the fragment\n"
"        color_add = (lightPalval  * light_mult); // * (1.0 - light)\n"
"        sampled_color = palval;\n"
"    }\n"
"#ifdef CAN_BILINEAR_FILTER\n"
"    else if (tex_mode == TEX_MODE_BILINEAR)\n"
"    {\n"
"        sampled_color = bilinear_paletted();\n"
"        color_add = bilinear_paletted_light(index);\n"
"\n"
"        if (sampled_color.a < 0.01) {\n"
"            discard;\n"
"        }\n"
"    }\n"
"#endif\n"
"\n"
"    vec4 albedoFactor_copy = albedoFactor;\n"
"\n"
"    if (blend_mode == D3DBLEND_INVSRCALPHA)\n"
"    {\n"
"        if (vertex_color.a < 0.01) {\n"
"            discard;\n"
"        }\n"
"        //albedoFactor_copy.a = (1.0 - albedoFactor_copy.a);\n"
"        //vertex_color.a = (1.0 - vertex_color.a);\n"
"        //sampled_color.a = (1.0 - sampled_color.a);\n"
"    }\n"
"\n"
"    if (blend_mode != D3DBLEND_SRCALPHA && blend_mode != D3DBLEND_INVSRCALPHA && vertex_color.a != 0.0)\n"
"    {\n"
"        vertex_color.a = 1.0;\n"
"    }\n"
"\n"
"    vec4 main_color = (sampled_color * vertex_color);\n"
"    vec4 effectAdd_color = vec4(colorEffects_add.r, colorEffects_add.g, colorEffects_add.b, 0.0);\n"
"    \n"
"    main_color *= albedoFactor_copy;\n"
"    float should_write_normals = 1.0;\n"
"    float orig_alpha = main_color.a;\n"
"\n"
"    if (main_color.a < 0.01 && sampledEmiss.r == 0.0 && sampledEmiss.g == 0.0 && sampledEmiss.b == 0.0) {\n"
"        discard;\n"
"    }\n"
"    \n"
"    if (blend_mode == D3DBLEND_INVSRCALPHA)\n"
"    {\n"
"        main_color.rgb *= (1.0 - main_color.a);\n"
"        main_color.a = (1.0 - main_color.a);\n"
"    }\n"
"\n"
"    //if (blend_mode == D3DBLEND_SRCALPHA || blend_mode == D3DBLEND_INVSRCALPHA)\n"
"    {\n"
"        should_write_normals = main_color.a;\n"
"    }\n"
"\n"
"    //if (sampledEmiss.r != 0.0 || sampledEmiss.g != 0.0 || sampledEmiss.b != 0.0)\n"
"    {\n"
"        color_add.rgb += sampledEmiss.rgb * emissiveFactor * 0.1;\n"
"    }\n"
"\n"
"    if (sampledEmiss.r != 0.0 || sampledEmiss.g != 0.0 || sampledEmiss.b != 0.0)\n"
"    {\n"
"        color_add_emiss.rgb += sampledEmiss.rgb * 0.1;\n"
"    }\n"
"\n"
"    fragColor = main_color + effectAdd_color;// + color_add;\n"
"\n"
"    color_add.a = orig_alpha;\n"
"\n"
"    float luma = luminance(color_add.rgb) * 0.5;// * 4.0;\n"
"\n"
"    if (emissiveFactor.r != 0.0 || emissiveFactor.g != 0.0 || emissiveFactor.b != 0.0)\n"
"    {\n"
"        //color_add = vec4(1.0, 1.0, 1.0, 1.0);\n"
"        luma = 1.0;\n"
"    }\n"
"    else\n"
"    {\n"
"        // The emissive maps also include slight amounts of darkly-rendered geometry,\n"
"        // so we want to ramp the amount that gets added based on luminance/brightness.\n"
"        \n"
"\n"
"        color_add.r *= luma;\n"
"        color_add.g *= luma;\n"
"        color_add.b *= luma;\n"
"    }\n"
"\n"
"    vec3 tint = normalize(colorEffects_tint + 1.0) * sqrt(3.0);\n"
"\n"
"    color_add.r *= tint.r;\n"
"    color_add.g *= tint.g;\n"
"    color_add.b *= tint.b;\n"
"\n"
"    color_add.r *= colorEffects_fade;\n"
"    color_add.g *= colorEffects_fade;\n"
"    color_add.b *= colorEffects_fade;\n"
"\n"
"    color_add.r *= colorEffects_filter.r;\n"
"    color_add.g *= colorEffects_filter.g;\n"
"    color_add.b *= colorEffects_filter.b;\n"
"\n"
"    //color_add = vec4(0.0, 0.0, 0.0, 1.0);\n"
"\n"
"    // Dont include any windows or transparent objects in emissivity output\n"
"    if (luma < 0.01 && orig_alpha < 0.5 && (blend_mode == D3DBLEND_SRCALPHA || blend_mode == 6))\n"
"    {\n"
"        color_add = vec4(0.0, 0.0, 0.0, 0.0);\n"
"    }\n"
"\n"
"    if (blend_mode == D3DBLEND_INVSRCALPHA) {\n"
"        //color_add.a = (1.0 - color_add.a);\n"
"        //should_write_normals = 1.0 - should_write_normals;\n"
"    }\n"
"\n"
"    fragColorEmiss = color_add_emiss + color_add;\n"
"\n"
"    //fragColor = vec4(face_normals_parallax.x, face_normals_parallax.y, face_normals_parallax.z, 1.0);\n"
"    //fragColor = vec4(face_normals*0.5 + 0.5,1.0);\n"
"    //vec4 test_norms = (main_color + effectAdd_color);\n"
"    //test_norms.xyz *= dot(vec3(1.0, 0.0, -0.7), face_normals);\n"
"    //fragColor = test_norms;\n"
"\n"
"    fragColorPos = vec4(adjusted_coords.x, adjusted_coords.y, adjusted_coords.z, should_write_normals);\n"
"    fragColorNormal = vec4(face_normals, should_write_normals);\n"
"    gl_FragDepth = gl_FragCoord.z;\n"
"}\n"
"\n"
, 0x3742},
{"shaders/default_v.glsl", 
"in vec3 coord3d;\n"
"in vec4 v_color;\n"
"in float v_light;\n"
"in vec2 v_uv;\n"
"uniform mat4 mvp;\n"
"out vec4 f_color;\n"
"out float f_light;\n"
"out vec2 f_uv;\n"
"out vec3 f_coord;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 pos = mvp * vec4(coord3d, 1.0);\n"
"    pos.w = 1.0/(1.0-coord3d.z);\n"
"    pos.xyz *= pos.w;\n"
"    gl_Position = pos;\n"
"    f_color = v_color.bgra;\n"
"    f_uv = v_uv;\n"
"    f_coord = coord3d;\n"
"    f_light = v_light;\n"
"}\n"
"\n"
, 0x181},
{"shaders/menu_f.glsl", 
"uniform sampler2D tex;\n"
"uniform sampler2D worldPalette;\n"
"uniform sampler2D displayPalette;\n"
"in vec4 f_color;\n"
"in vec2 f_uv;\n"
"out vec4 fragColor;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 sampled = texture(tex, f_uv);\n"
"    vec4 sampled_color = vec4(0.0, 0.0, 0.0, 0.0);\n"
"    vec4 vertex_color = f_color;\n"
"    float index = sampled.r;\n"
"    vec4 palval = texture(worldPalette, vec2(index, 0.5));\n"
"    vec4 palvald = texture(displayPalette, vec2(index, 0.5));\n"
"    vec4 blend = vec4(1.0, 1.0, 1.0, 1.0);\n"
"\n"
"    float transparency = 1.0;\n"
"    if (index == 0.0)\n"
"        discard;\n"
"    sampled_color = vec4(palvald.r, palvald.g, palvald.b, transparency);\n"
"\n"
"    fragColor = sampled_color * vertex_color * blend;\n"
"}\n"
"\n"
, 0x2a3},
{"shaders/menu_v.glsl", 
"in vec3 coord3d;\n"
"in vec4 v_color;\n"
"in vec2 v_uv;\n"
"uniform mat4 mvp;\n"
"out vec4 f_color;\n"
"out vec2 f_uv;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 pos = mvp * vec4(coord3d, 1.0);\n"
"    pos.w = 1.0/(1.0-coord3d.z);\n"
"    pos.xyz *= pos.w;\n"
"    gl_Position = pos;\n"
"    f_color = v_color;\n"
"    f_uv = v_uv;\n"
"}\n"
"\n"
, 0x117},
{"shaders/ssao_f.glsl", 
"uniform sampler2D tex;\n"
"uniform sampler2D tex2;\n"
"uniform sampler2D tex3;\n"
"uniform vec2 iResolution;\n"
"uniform float param1;\n"
"uniform float param2;\n"
"uniform float param3;\n"
"in vec4 f_color;\n"
"in vec2 f_uv;\n"
"in vec3 f_coord;\n"
"out vec4 fragColor;\n"
"\n"
"#define PI 3.14159265359\n"
"#define AOradius 1.0\n"
"#define Samples 8.0\n"
"\n"
"// --------------------------------------\n"
"// oldschool rand() from Visual Studio\n"
"// --------------------------------------\n"
"int   seed = 1;\n"
"void  srand(int s ) { seed = s; }\n"
"int   rand(void)  { seed=seed*0x343fd+0x269ec3; return (seed>>16)&32767; }\n"
"float frand(void) { return float(rand())/32767.0; }\n"
"// --------------------------------------\n"
"// hash by Hugo Elias\n"
"// --------------------------------------\n"
"int hash( int n ) { n=(n<<13)^n; return n*(n*n*15731+789221)+1376312589; }\n"
"\n"
"// Color curve stuff idk\n"
"float gamma = 0.35;\n"
"float Cubic (float value) {\n"
"    \n"
"    // Possibly slightly faster calculation\n"
"    // when compared to Sigmoid\n"
"    \n"
"    if (value < 0.5)\n"
"    {\n"
"        return value * value * value * value * value * 16.0; \n"
"    }\n"
"    \n"
"    value -= 1.0;\n"
"    \n"
"    return value * value * value * value * value * 16.0 + 1.0;\n"
"}\n"
"\n"
"vec3 hemisphereVolumeRandPoint()\n"
"{\n"
"    vec3 p = vec3(frand() * 2.0 - 1.0,frand() * 2.0 - 1.0,frand());\n"
"\n"
"    return normalize(p);\n"
"}\n"
"\n"
"float depth(vec2 coord)\n"
"{\n"
"    vec2 uv = coord*vec2(iResolution.y/iResolution.x,1.0);\n"
"    return texture(tex, uv).z;\n"
"}\n"
"\n"
"float SSAO(vec2 coord)\n"
"{\n"
"    float cd = depth(coord);\n"
"    float screenRadius = 0.5 * (AOradius / cd) / 0.53135;\n"
"    float li = 0.0;\n"
"    float count = 0.0;\n"
"    vec2 fragCoord = f_uv*iResolution.xy;\n"
"\n"
"    vec3 normal = texture(tex2, f_uv).rgb;\n"
"    normal *= vec3(1.0, 1.0, -1.0);\n"
"    normal = normalize(normal);\n"
"\n"
"    vec3 rvec = texture(tex3, (f_uv*iResolution.xy) / vec2(4.0)).rgb;\n"
"\n"
"    vec3 tangent = normalize(rvec - normal * dot(rvec, normal));\n"
"    vec3 bitangent = cross(normal, tangent);\n"
"    mat3 tbn = mat3(tangent, bitangent, normal);\n"
"\n"
"    vec3 kernels[128];\n"
"    for (int i = 0; i < int(Samples); i++)\n"
"    {\n"
"        kernels[i] = hemisphereVolumeRandPoint();// * frand();\n"
"\n"
"        // Sample points should concentrate near the center of the hemisphere\n"
"        float scale = float(i) / Samples;\n"
"        scale = mix(0.1f, 1.0f, scale * scale);\n"
"        kernels[i] *= scale;\n"
"    }\n"
"\n"
"    ivec2 q = ivec2(fragCoord);\n"
"    srand( hash(q.x+hash(q.y+hash(1117 * int(param1)))));\n"
"\n"
"    for(float i=0.0; i<Samples; i++)\n"
"    {\n"
"        vec3 p = kernels[int(i)];\n"
"\n"
"        p *= frand();\n"
"\n"
"        // Rotate the hemisphere\n"
"        p = tbn * p;\n"
"\n"
"        vec2 sp = vec2(coord.x + p.x * screenRadius, coord.y + p.y * screenRadius);\n"
"        float d = depth(sp);\n"
"        float at = pow(length(p)-1.0, 2.0);\n"
"        li += step(cd + p.z * AOradius, d) * at;\n"
"        count += at;\n"
"    }\n"
"    return li / count;\n"
"}\n"
"\n"
"void main(void)\n"
"{\n"
"    vec2 fragCoord = f_uv*iResolution.xy;\n"
"\n"
"    // init random seed\n"
"    //ivec2 q = ivec2(fragCoord);\n"
"    srand( hash(1117 * int(param1)));\n"
"\n"
"    // coordinate\n"
"    vec2 uv = fragCoord/(iResolution.xy);\n"
"    vec2 coord = fragCoord/(iResolution.y);\n"
"\n"
"    vec4 sampled_color = vec4(1.0, 1.0, 1.0, 1.0);\n"
"    float d = depth(coord);\n"
"    vec3 ao = vec3(0.7) * SSAO(coord);\n"
"    vec3 color = mix(sampled_color.rgb, ao, 1.0 - smoothstep(0.0, 0.99, d*d/1e9));\n"
"    //color = mix(color, sampled_color.rgb, 1.0 - smoothstep(0.0, 0.1, d*d/15));\n"
"    \n"
"    // Color curve stuff, idk\n"
"    //color = pow(color,vec3(1.0/2.2)); // gamma\n"
"    color = vec3(Cubic(color.r),Cubic(color.g),Cubic(color.b));\n"
"    color = pow(color, vec3(gamma));\n"
"\n"
"    //vec3 normal = texture(tex2, f_uv).rgb;\n"
"    //fragColor = vec4(normal, 1.0);\n"
"    fragColor = vec4(color, 1.0);\n"
"}\n"
, 0xe1f},
{"shaders/ssao_mix_f.glsl", 
"uniform sampler2D tex;\n"
"uniform sampler2D tex2;\n"
"uniform vec2 iResolution;\n"
"uniform float param1;\n"
"uniform float param2;\n"
"uniform float param3;\n"
"in vec4 f_color;\n"
"in vec2 f_uv;\n"
"in vec3 f_coord;\n"
"out vec4 fragColor;\n"
"\n"
"//#define SSAO_CHECK_LEVELS\n"
"//#define SSAO_COMPARISON\n"
"\n"
"void main(void)\n"
"{\n"
"#ifdef SSAO_CHECK_LEVELS\n"
"    vec4 sampled_color = vec4(0.5, 0.5, 0.5, 1.0);\n"
"#else\n"
"    vec4 sampled_color = texture(tex2, f_uv);\n"
"#endif\n"
"    \n"
"    // The background we're applying to\n"
"    vec4 color = texture(tex, f_uv);\n"
"\n"
"    float scaleFactor = 1.1;\n"
"\n"
"#ifdef SSAO_COMPARISON\n"
"    if (f_uv.x < 0.5) {\n"
"        fragColor = sampled_color;\n"
"    }\n"
"    else\n"
"    {\n"
"#ifdef SSAO_CHECK_LEVELS\n"
"        if (f_uv.y > 0.5)\n"
"        {\n"
"            fragColor = vec4(scaleFactor * color.rgb * vec3(0.5, 0.5, 0.5), 1.0);\n"
"        }\n"
"        else\n"
"#endif\n"
"        {\n"
"            fragColor = vec4(scaleFactor * color.rgb * sampled_color.rgb, 1.0);\n"
"        }\n"
"    }\n"
"#else\n"
"    fragColor = vec4(scaleFactor * color.rgb * sampled_color.rgb, sampled_color.a);\n"
"#endif\n"
"\n"
"    fragColor.rgb = pow(fragColor.rgb, vec3(1.0/param3));\n"
"}\n"
, 0x42c},
{"shaders/ssao_mix_v.glsl", 
"in vec3 coord3d;\n"
"in vec4 v_color;\n"
"in vec2 v_uv;\n"
"uniform mat4 mvp;\n"
"out vec4 f_color;\n"
"out vec2 f_uv;\n"
"out vec3 f_coord;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 pos = mvp * vec4(coord3d, 1.0);\n"
"    pos.w = 1.0/(1.0-coord3d.z);\n"
"    pos.xyz *= pos.w;\n"
"    gl_Position = pos;\n"
"    f_color = v_color;\n"
"    f_uv = v_uv;\n"
"    f_coord = coord3d;\n"
"}\n"
"\n"
, 0x140},
{"shaders/ssao_v.glsl", 
"in vec3 coord3d;\n"
"in vec4 v_color;\n"
"in vec2 v_uv;\n"
"uniform mat4 mvp;\n"
"out vec4 f_color;\n"
"out vec2 f_uv;\n"
"out vec3 f_coord;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 pos = mvp * vec4(coord3d, 1.0);\n"
"    pos.w = 1.0/(1.0-coord3d.z);\n"
"    pos.xyz *= pos.w;\n"
"    gl_Position = pos;\n"
"    f_color = v_color;\n"
"    f_uv = v_uv;\n"
"    f_coord = coord3d;\n"
"}\n"
"\n"
, 0x140},
{"shaders/texfbo_f.glsl", 
"uniform sampler2D tex;\n"
"uniform vec2 iResolution;\n"
"uniform float param1;\n"
"uniform float param2;\n"
"uniform float param3;\n"
"in vec4 f_color;\n"
"in vec2 f_uv;\n"
"in vec3 f_coord;\n"
"out vec4 fragColor;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 sampled_color = texture(tex, f_uv);\n"
"    vec4 vertex_color = f_color;\n"
"    vec4 blend = vec4(param2, param2, param2, param1);\n"
"\n"
"    fragColor = sampled_color * vertex_color * blend;\n"
"    fragColor.rgb = pow(fragColor.rgb, vec3(1.0/param3));\n"
"    fragColor.rgba = clamp(fragColor.rgba, 0.0, 1.0);\n"
"    //fragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
"}\n"
"\n"
, 0x224},
{"shaders/texfbo_v.glsl", 
"in vec3 coord3d;\n"
"in vec4 v_color;\n"
"in vec2 v_uv;\n"
"uniform mat4 mvp;\n"
"out vec4 f_color;\n"
"out vec2 f_uv;\n"
"out vec3 f_coord;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 pos = mvp * vec4(coord3d, 1.0);\n"
"    pos.w = 1.0/(1.0-coord3d.z);\n"
"    pos.xyz *= pos.w;\n"
"    gl_Position = pos;\n"
"    f_color = v_color;\n"
"    f_uv = v_uv;\n"
"    f_coord = coord3d;\n"
"}\n"
"\n"
, 0x140},
{"shaders/ui_f.glsl", 
"uniform sampler2D tex;\n"
"uniform vec2 iResolution;\n"
"uniform float param1;\n"
"uniform float param2;\n"
"uniform float param3;\n"
"in vec4 f_color;\n"
"in vec2 f_uv;\n"
"in vec3 f_coord;\n"
"out vec4 fragColor;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 sampled_color = texture(tex, f_uv);\n"
"    vec4 vertex_color = f_color;\n"
"    if (sampled_color.a < 0.01) {\n"
"        if (param1 == 1.0)\n"
"        {\n"
"            discard;\n"
"        }\n"
"        else {\n"
"            sampled_color = vec4(sampled_color.r, sampled_color.g, sampled_color.b, 1.0);\n"
"            //sampled_color = vec4(0.0, 0.0, 0.0, 0.0);\n"
"        }\n"
"    }\n"
"\n"
"    fragColor = sampled_color * vertex_color;\n"
"    fragColor.rgb = pow(fragColor.rgb, vec3(1.0/param3));\n"
"    fragColor.rgba = clamp(fragColor.rgba, 0.0, 1.0);\n"
"    //fragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
"}\n"
"\n"
, 0x2fc},
{"shaders/ui_v.glsl", 
"in vec3 coord3d;\n"
"in vec4 v_color;\n"
"in vec2 v_uv;\n"
"uniform mat4 mvp;\n"
"out vec4 f_color;\n"
"out vec2 f_uv;\n"
"out vec3 f_coord;\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 pos = mvp * vec4(coord3d, 1.0);\n"
"    pos.w = 1.0/(1.0-coord3d.z);\n"
"    pos.xyz *= pos.w;\n"
"    gl_Position = pos;\n"
"    f_color = v_color;\n"
"    f_uv = v_uv;\n"
"    f_coord = coord3d;\n"
"}\n"
"\n"
, 0x140},
{"ssl/cacert.pem", 
"##\n"
"## Bundle of CA Root Certificates\n"
"##\n"
"## Certificate data from Mozilla as of: Sat Oct  2 10:58:04 2021 GMT\n"
"##\n"
"## This is a bundle of X.509 certificates of public Certificate Authorities\n"
"## (CA). These were automatically extracted from Mozilla's root certificates\n"
"## file (certdata.txt).  This file can be found in the mozilla source tree:\n"
"## https://hg.mozilla.org/releases/mozilla-release/raw-file/default/security/nss/lib/ckfw/builtins/certdata.txt\n"
"##\n"
"## It contains the certificates in PEM format and therefore\n"
"## can be directly used with curl / libcurl / php_curl, or with\n"
"## an Apache+mod_ssl webserver for SSL client authentication.\n"
"## Just configure this file as the SSLCACertificateFile.\n"
"##\n"
"## Conversion done with mk-ca-bundle.pl version 1.28.\n"
"## SHA256: c8f6733d1ff4e6a4769c182971a1234f95ae079247a9c439a13423fe8ba5c24f\n"
"##\n"
"\n"
"\n"
"GlobalSign Root CA\n"
"==================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkGA1UEBhMCQkUx\n"
"GTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jvb3QgQ0ExGzAZBgNVBAMTEkds\n"
"b2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAwMDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNV\n"
"BAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYD\n"
"VQQDExJHbG9iYWxTaWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDa\n"
"DuaZjc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavpxy0Sy6sc\n"
"THAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp1Wrjsok6Vjk4bwY8iGlb\n"
"Kk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdGsnUOhugZitVtbNV4FpWi6cgKOOvyJBNP\n"
"c1STE4U6G7weNLWLBYy5d4ux2x8gkasJU26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrX\n"
"gzT/LCrBbBlDSgeF59N89iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n"
"HRMBAf8EBTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0BAQUF\n"
"AAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOzyj1hTdNGCbM+w6Dj\n"
"Y1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE38NflNUVyRRBnMRddWQVDf9VMOyG\n"
"j/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymPAbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhH\n"
"hm4qxFYxldBniYUr+WymXUadDKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveC\n"
"X4XSQRjbgbMEHMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n"
"-----END CERTIFICATE-----\n"
"\n"
"GlobalSign Root CA - R2\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4GA1UECxMXR2xv\n"
"YmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNpZ24xEzARBgNVBAMTCkdsb2Jh\n"
"bFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxT\n"
"aWduIFJvb3QgQ0EgLSBSMjETMBEGA1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2ln\n"
"bjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6\n"
"ErPLv4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8eoLrvozp\n"
"s6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklqtTleiDTsvHgMCJiEbKjN\n"
"S7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzdC9XZzPnqJworc5HGnRusyMvo4KD0L5CL\n"
"TfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pazq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6C\n"
"ygPCm48CAwEAAaOBnDCBmTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4E\n"
"FgQUm+IHV2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5nbG9i\n"
"YWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG3lm0mi3f3BmGLjAN\n"
"BgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4GsJ0/WwbgcQ3izDJr86iw8bmEbTUsp\n"
"9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu\n"
"01yiPqFbQfXf5WRDLenVOavSot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG7\n"
"9G+dwfCMNYxdAfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n"
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Entrust.net Premium 2048 Secure Server CA\n"
"=========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEKjCCAxKgAwIBAgIEOGPe+DANBgkqhkiG9w0BAQUFADCBtDEUMBIGA1UEChMLRW50cnVzdC5u\n"
"ZXQxQDA+BgNVBAsUN3d3dy5lbnRydXN0Lm5ldC9DUFNfMjA0OCBpbmNvcnAuIGJ5IHJlZi4gKGxp\n"
"bWl0cyBsaWFiLikxJTAjBgNVBAsTHChjKSAxOTk5IEVudHJ1c3QubmV0IExpbWl0ZWQxMzAxBgNV\n"
"BAMTKkVudHJ1c3QubmV0IENlcnRpZmljYXRpb24gQXV0aG9yaXR5ICgyMDQ4KTAeFw05OTEyMjQx\n"
"NzUwNTFaFw0yOTA3MjQxNDE1MTJaMIG0MRQwEgYDVQQKEwtFbnRydXN0Lm5ldDFAMD4GA1UECxQ3\n"
"d3d3LmVudHJ1c3QubmV0L0NQU18yMDQ4IGluY29ycC4gYnkgcmVmLiAobGltaXRzIGxpYWIuKTEl\n"
"MCMGA1UECxMcKGMpIDE5OTkgRW50cnVzdC5uZXQgTGltaXRlZDEzMDEGA1UEAxMqRW50cnVzdC5u\n"
"ZXQgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkgKDIwNDgpMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8A\n"
"MIIBCgKCAQEArU1LqRKGsuqjIAcVFmQqK0vRvwtKTY7tgHalZ7d4QMBzQshowNtTK91euHaYNZOL\n"
"Gp18EzoOH1u3Hs/lJBQesYGpjX24zGtLA/ECDNyrpUAkAH90lKGdCCmziAv1h3edVc3kw37XamSr\n"
"hRSGlVuXMlBvPci6Zgzj/L24ScF2iUkZ/cCovYmjZy/Gn7xxGWC4LeksyZB2ZnuU4q941mVTXTzW\n"
"nLLPKQP5L6RQstRIzgUyVYr9smRMDuSYB3Xbf9+5CFVghTAp+XtIpGmG4zU/HoZdenoVve8AjhUi\n"
"VBcAkCaTvA5JaJG/+EfTnZVCwQ5N328mz8MYIWJmQ3DW1cAH4QIDAQABo0IwQDAOBgNVHQ8BAf8E\n"
"BAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUVeSB0RGAvtiJuQijMfmhJAkWuXAwDQYJ\n"
"KoZIhvcNAQEFBQADggEBADubj1abMOdTmXx6eadNl9cZlZD7Bh/KM3xGY4+WZiT6QBshJ8rmcnPy\n"
"T/4xmf3IDExoU8aAghOY+rat2l098c5u9hURlIIM7j+VrxGrD9cv3h8Dj1csHsm7mhpElesYT6Yf\n"
"zX1XEC+bBAlahLVu2B064dae0Wx5XnkcFMXj0EyTO2U87d89vqbllRrDtRnDvV5bu/8j72gZyxKT\n"
"J1wDLW8w0B62GqzeWvfRqqgnpv55gcR5mTNXuhKwqeBCbJPKVt7+bYQLCIt+jerXmCHG8+c8eS9e\n"
"nNFMFY3h7CI3zJpDC5fcgJCNs2ebb0gIFVbPv/ErfF6adulZkMV8gzURZVE=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Baltimore CyberTrust Root\n"
"=========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJRTESMBAGA1UE\n"
"ChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3li\n"
"ZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoXDTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMC\n"
"SUUxEjAQBgNVBAoTCUJhbHRpbW9yZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFs\n"
"dGltb3JlIEN5YmVyVHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKME\n"
"uyKrmD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjrIZ3AQSsB\n"
"UnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeKmpYcqWe4PwzV9/lSEy/C\n"
"G9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSuXmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9\n"
"XbIGevOF6uvUA65ehD5f/xXtabz5OTZydc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjpr\n"
"l3RjM71oGDHweI12v/yejl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoI\n"
"VDaGezq1BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3DQEB\n"
"BQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT929hkTI7gQCvlYpNRh\n"
"cL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3WgxjkzSswF07r51XgdIGn9w/xZchMB5\n"
"hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsa\n"
"Y71k5h+3zvDyny67G7fyUIhzksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9H\n"
"RCwBXbsdtTLSR9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n"
"-----END CERTIFICATE-----\n"
"\n"
"Entrust Root Certification Authority\n"
"====================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEkTCCA3mgAwIBAgIERWtQVDANBgkqhkiG9w0BAQUFADCBsDELMAkGA1UEBhMCVVMxFjAUBgNV\n"
"BAoTDUVudHJ1c3QsIEluYy4xOTA3BgNVBAsTMHd3dy5lbnRydXN0Lm5ldC9DUFMgaXMgaW5jb3Jw\n"
"b3JhdGVkIGJ5IHJlZmVyZW5jZTEfMB0GA1UECxMWKGMpIDIwMDYgRW50cnVzdCwgSW5jLjEtMCsG\n"
"A1UEAxMkRW50cnVzdCBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5MB4XDTA2MTEyNzIwMjM0\n"
"MloXDTI2MTEyNzIwNTM0MlowgbAxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1FbnRydXN0LCBJbmMu\n"
"MTkwNwYDVQQLEzB3d3cuZW50cnVzdC5uZXQvQ1BTIGlzIGluY29ycG9yYXRlZCBieSByZWZlcmVu\n"
"Y2UxHzAdBgNVBAsTFihjKSAyMDA2IEVudHJ1c3QsIEluYy4xLTArBgNVBAMTJEVudHJ1c3QgUm9v\n"
"dCBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"
"ALaVtkNC+sZtKm9I35RMOVcF7sN5EUFoNu3s/poBj6E4KPz3EEZmLk0eGrEaTsbRwJWIsMn/MYsz\n"
"A9u3g3s+IIRe7bJWKKf44LlAcTfFy0cOlypowCKVYhXbR9n10Cv/gkvJrT7eTNuQgFA/CYqEAOww\n"
"Cj0Yzfv9KlmaI5UXLEWeH25DeW0MXJj+SKfFI0dcXv1u5x609mhF0YaDW6KKjbHjKYD+JXGIrb68\n"
"j6xSlkuqUY3kEzEZ6E5Nn9uss2rVvDlUccp6en+Q3X0dgNmBu1kmwhH+5pPi94DkZfs0Nw4pgHBN\n"
"rziGLp5/V6+eF67rHMsoIV+2HNjnogQi+dPa2MsCAwEAAaOBsDCBrTAOBgNVHQ8BAf8EBAMCAQYw\n"
"DwYDVR0TAQH/BAUwAwEB/zArBgNVHRAEJDAigA8yMDA2MTEyNzIwMjM0MlqBDzIwMjYxMTI3MjA1\n"
"MzQyWjAfBgNVHSMEGDAWgBRokORnpKZTgMeGZqTx90tD+4S9bTAdBgNVHQ4EFgQUaJDkZ6SmU4DH\n"
"hmak8fdLQ/uEvW0wHQYJKoZIhvZ9B0EABBAwDhsIVjcuMTo0LjADAgSQMA0GCSqGSIb3DQEBBQUA\n"
"A4IBAQCT1DCw1wMgKtD5Y+iRDAUgqV8ZyntyTtSx29CW+1RaGSwMCPeyvIWonX9tO1KzKtvn1ISM\n"
"Y/YPyyYBkVBs9F8U4pN0wBOeMDpQ47RgxRzwIkSNcUesyBrJ6ZuaAGAT/3B+XxFNSRuzFVJ7yVTa\n"
"v52Vr2ua2J7p8eRDjeIRRDq/r72DQnNSi6q7pynP9WQcCk3RvKqsnyrQ/39/2n3qse0wJcGE2jTS\n"
"W3iDVuycNsMm4hH2Z0kdkquM++v/eu6FSqdQgPCnXEqULl8FmTxSQeDNtGPPAUO6nIPcj2A781q0\n"
"tHuu2guQOHXvgR1m0vdXcDazv/wor3ElhVsT/h5/WrQ8\n"
"-----END CERTIFICATE-----\n"
"\n"
"Comodo AAA Services root\n"
"========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEMjCCAxqgAwIBAgIBATANBgkqhkiG9w0BAQUFADB7MQswCQYDVQQGEwJHQjEbMBkGA1UECAwS\n"
"R3JlYXRlciBNYW5jaGVzdGVyMRAwDgYDVQQHDAdTYWxmb3JkMRowGAYDVQQKDBFDb21vZG8gQ0Eg\n"
"TGltaXRlZDEhMB8GA1UEAwwYQUFBIENlcnRpZmljYXRlIFNlcnZpY2VzMB4XDTA0MDEwMTAwMDAw\n"
"MFoXDTI4MTIzMTIzNTk1OVowezELMAkGA1UEBhMCR0IxGzAZBgNVBAgMEkdyZWF0ZXIgTWFuY2hl\n"
"c3RlcjEQMA4GA1UEBwwHU2FsZm9yZDEaMBgGA1UECgwRQ29tb2RvIENBIExpbWl0ZWQxITAfBgNV\n"
"BAMMGEFBQSBDZXJ0aWZpY2F0ZSBTZXJ2aWNlczCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC\n"
"ggEBAL5AnfRu4ep2hxxNRUSOvkbIgwadwSr+GB+O5AL686tdUIoWMQuaBtDFcCLNSS1UY8y2bmhG\n"
"C1Pqy0wkwLxyTurxFa70VJoSCsN6sjNg4tqJVfMiWPPe3M/vg4aijJRPn2jymJBGhCfHdr/jzDUs\n"
"i14HZGWCwEiwqJH5YZ92IFCokcdmtet4YgNW8IoaE+oxox6gmf049vYnMlhvB/VruPsUK6+3qszW\n"
"Y19zjNoFmag4qMsXeDZRrOme9Hg6jc8P2ULimAyrL58OAd7vn5lJ8S3frHRNG5i1R8XlKdH5kBjH\n"
"Ypy+g8cmez6KJcfA3Z3mNWgQIJ2P2N7Sw4ScDV7oL8kCAwEAAaOBwDCBvTAdBgNVHQ4EFgQUoBEK\n"
"Iz6W8Qfs4q8p74Klf9AwpLQwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wewYDVR0f\n"
"BHQwcjA4oDagNIYyaHR0cDovL2NybC5jb21vZG9jYS5jb20vQUFBQ2VydGlmaWNhdGVTZXJ2aWNl\n"
"cy5jcmwwNqA0oDKGMGh0dHA6Ly9jcmwuY29tb2RvLm5ldC9BQUFDZXJ0aWZpY2F0ZVNlcnZpY2Vz\n"
"LmNybDANBgkqhkiG9w0BAQUFAAOCAQEACFb8AvCb6P+k+tZ7xkSAzk/ExfYAWMymtrwUSWgEdujm\n"
"7l3sAg9g1o1QGE8mTgHj5rCl7r+8dFRBv/38ErjHT1r0iWAFf2C3BUrz9vHCv8S5dIa2LX1rzNLz\n"
"Rt0vxuBqw8M0Ayx9lt1awg6nCpnBBYurDC/zXDrPbDdVCYfeU0BsWO/8tqtlbgT2G9w84FoVxp7Z\n"
"8VlIMCFlA2zs6SFz7JsDoeA3raAVGI/6ugLOpyypEBMs1OUIJqsil2D4kF501KKaU73yqWjgom7C\n"
"12yxow+ev+to51byrvLjKzg6CYG1a4XXvi3tPxq3smPi9WIsgtRqAEFQ8TmDn5XpNpaYbg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"QuoVadis Root CA 2\n"
"==================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"QuoVadis Root CA 3\n"
"==================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIGnTCCBIWgAwIBAgICBcYwDQYJKoZIhvcNAQEFBQAwRTELMAkGA1UEBhMCQk0xGTAXBgNVBAoT\n"
"EFF1b1ZhZGlzIExpbWl0ZWQxGzAZBgNVBAMTElF1b1ZhZGlzIFJvb3QgQ0EgMzAeFw0wNjExMjQx\n"
"OTExMjNaFw0zMTExMjQxOTA2NDRaMEUxCzAJBgNVBAYTAkJNMRkwFwYDVQQKExBRdW9WYWRpcyBM\n"
"aW1pdGVkMRswGQYDVQQDExJRdW9WYWRpcyBSb290IENBIDMwggIiMA0GCSqGSIb3DQEBAQUAA4IC\n"
"DwAwggIKAoICAQDMV0IWVJzmmNPTTe7+7cefQzlKZbPoFog02w1ZkXTPkrgEQK0CSzGrvI2RaNgg\n"
"DhoB4hp7Thdd4oq3P5kazethq8Jlph+3t723j/z9cI8LoGe+AaJZz3HmDyl2/7FWeUUrH556VOij\n"
"KTVopAFPD6QuN+8bv+OPEKhyq1hX51SGyMnzW9os2l2ObjyjPtr7guXd8lyyBTNvijbO0BNO/79K\n"
"DDRMpsMhvVAEVeuxu537RR5kFd5VAYwCdrXLoT9CabwvvWhDFlaJKjdhkf2mrk7AyxRllDdLkgbv\n"
"BNDInIjbC3uBr7E9KsRlOni27tyAsdLTmZw67mtaa7ONt9XOnMK+pUsvFrGeaDsGb659n/je7Mwp\n"
"p5ijJUMv7/FfJuGITfhebtfZFG4ZM2mnO4SJk8RTVROhUXhA+LjJou57ulJCg54U7QVSWllWp5f8\n"
"nT8KKdjcT5EOE7zelaTfi5m+rJsziO+1ga8bxiJTyPbH7pcUsMV8eFLI8M5ud2CEpukqdiDtWAEX\n"
"MJPpGovgc2PZapKUSU60rUqFxKMiMPwJ7Wgic6aIDFUhWMXhOp8q3crhkODZc6tsgLjoC2SToJyM\n"
"Gf+z0gzskSaHirOi4XCPLArlzW1oUevaPwV/izLmE1xr/l9A4iLItLRkT9a6fUg+qGkM17uGcclz\n"
"uD87nSVL2v9A6wIDAQABo4IBlTCCAZEwDwYDVR0TAQH/BAUwAwEB/zCB4QYDVR0gBIHZMIHWMIHT\n"
"BgkrBgEEAb5YAAMwgcUwgZMGCCsGAQUFBwICMIGGGoGDQW55IHVzZSBvZiB0aGlzIENlcnRpZmlj\n"
"YXRlIGNvbnN0aXR1dGVzIGFjY2VwdGFuY2Ugb2YgdGhlIFF1b1ZhZGlzIFJvb3QgQ0EgMyBDZXJ0\n"
"aWZpY2F0ZSBQb2xpY3kgLyBDZXJ0aWZpY2F0aW9uIFByYWN0aWNlIFN0YXRlbWVudC4wLQYIKwYB\n"
"BQUHAgEWIWh0dHA6Ly93d3cucXVvdmFkaXNnbG9iYWwuY29tL2NwczALBgNVHQ8EBAMCAQYwHQYD\n"
"VR0OBBYEFPLAE+CCQz777i9nMpY1XNu4ywLQMG4GA1UdIwRnMGWAFPLAE+CCQz777i9nMpY1XNu4\n"
"ywLQoUmkRzBFMQswCQYDVQQGEwJCTTEZMBcGA1UEChMQUXVvVmFkaXMgTGltaXRlZDEbMBkGA1UE\n"
"AxMSUXVvVmFkaXMgUm9vdCBDQSAzggIFxjANBgkqhkiG9w0BAQUFAAOCAgEAT62gLEz6wPJv92ZV\n"
"qyM07ucp2sNbtrCD2dDQ4iH782CnO11gUyeim/YIIirnv6By5ZwkajGxkHon24QRiSemd1o417+s\n"
"hvzuXYO8BsbRd2sPbSQvS3pspweWyuOEn62Iix2rFo1bZhfZFvSLgNLd+LJ2w/w4E6oM3kJpK27z\n"
"POuAJ9v1pkQNn1pVWQvVDVJIxa6f8i+AxeoyUDUSly7B4f/xI4hROJ/yZlZ25w9Rl6VSDE1JUZU2\n"
"Pb+iSwwQHYaZTKrzchGT5Or2m9qoXadNt54CrnMAyNojA+j56hl0YgCUyyIgvpSnWbWCar6ZeXqp\n"
"8kokUvd0/bpO5qgdAm6xDYBEwa7TIzdfu4V8K5Iu6H6li92Z4b8nby1dqnuH/grdS/yO9SbkbnBC\n"
"bjPsMZ57k8HkyWkaPcBrTiJt7qtYTcbQQcEr6k8Sh17rRdhs9ZgC06DYVYoGmRmioHfRMJ6szHXu\n"
"g/WwYjnPbFfiTNKRCw51KBuav/0aQ/HKd/s7j2G4aSgWQgRecCocIdiP4b0jWy10QJLZYxkNc91p\n"
"vGJHvOB0K7Lrfb5BG7XARsWhIstfTsEokt4YutUqKLsRixeTmJlglFwjz1onl14LBQaTNx47aTbr\n"
"qZ5hHY8y2o4M1nQ+ewkk2gF3R8Q7zTSMmfXK4SVhM7JZG+Ju1zdXtg2pEto=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Security Communication Root CA\n"
"==============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIBADANBgkqhkiG9w0BAQUFADBQMQswCQYDVQQGEwJKUDEYMBYGA1UEChMP\n"
"U0VDT00gVHJ1c3QubmV0MScwJQYDVQQLEx5TZWN1cml0eSBDb21tdW5pY2F0aW9uIFJvb3RDQTEw\n"
"HhcNMDMwOTMwMDQyMDQ5WhcNMjMwOTMwMDQyMDQ5WjBQMQswCQYDVQQGEwJKUDEYMBYGA1UEChMP\n"
"U0VDT00gVHJ1c3QubmV0MScwJQYDVQQLEx5TZWN1cml0eSBDb21tdW5pY2F0aW9uIFJvb3RDQTEw\n"
"ggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCzs/5/022x7xZ8V6UMbXaKL0u/ZPtM7orw\n"
"8yl89f/uKuDp6bpbZCKamm8sOiZpUQWZJtzVHGpxxpp9Hp3dfGzGjGdnSj74cbAZJ6kJDKaVv0uM\n"
"DPpVmDvY6CKhS3E4eayXkmmziX7qIWgGmBSWh9JhNrxtJ1aeV+7AwFb9Ms+k2Y7CI9eNqPPYJayX\n"
"5HA49LY6tJ07lyZDo6G8SVlyTCMwhwFY9k6+HGhWZq/NQV3Is00qVUarH9oe4kA92819uZKAnDfd\n"
"DJZkndwi92SL32HeFZRSFaB9UslLqCHJxrHty8OVYNEP8Ktw+N/LTX7s1vqr2b1/VPKl6Xn62dZ2\n"
"JChzAgMBAAGjPzA9MB0GA1UdDgQWBBSgc0mZaNyFW2XjmygvV5+9M7wHSDALBgNVHQ8EBAMCAQYw\n"
"DwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQUFAAOCAQEAaECpqLvkT115swW1F7NgE+vGkl3g\n"
"0dNq/vu+m22/xwVtWSDEHPC32oRYAmP6SBbvT6UL90qY8j+eG61Ha2POCEfrUj94nK9NrvjVT8+a\n"
"mCoQQTlSxN3Zmw7vkwGusi7KaEIkQmywszo+zenaSMQVy+n5Bw+SUEmK3TGXX8npN6o7WWWXlDLJ\n"
"s58+OmJYxUmtYg5xpTKqL8aJdkNAExNnPaJUJRDL8Try2frbSVa7pv6nQTXD4IhhyYjH3zYQIphZ\n"
"6rBK+1YWc26sTfcioU+tHXotRSflMMFe8toTyyVCUZVHA4xsIcx0Qu1T/zOLjw9XARYvz6buyXAi\n"
"FL39vmwLAw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"XRamp Global CA Root\n"
"====================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEMDCCAxigAwIBAgIQUJRs7Bjq1ZxN1ZfvdY+grTANBgkqhkiG9w0BAQUFADCBgjELMAkGA1UE\n"
"BhMCVVMxHjAcBgNVBAsTFXd3dy54cmFtcHNlY3VyaXR5LmNvbTEkMCIGA1UEChMbWFJhbXAgU2Vj\n"
"dXJpdHkgU2VydmljZXMgSW5jMS0wKwYDVQQDEyRYUmFtcCBHbG9iYWwgQ2VydGlmaWNhdGlvbiBB\n"
"dXRob3JpdHkwHhcNMDQxMTAxMTcxNDA0WhcNMzUwMTAxMDUzNzE5WjCBgjELMAkGA1UEBhMCVVMx\n"
"HjAcBgNVBAsTFXd3dy54cmFtcHNlY3VyaXR5LmNvbTEkMCIGA1UEChMbWFJhbXAgU2VjdXJpdHkg\n"
"U2VydmljZXMgSW5jMS0wKwYDVQQDEyRYUmFtcCBHbG9iYWwgQ2VydGlmaWNhdGlvbiBBdXRob3Jp\n"
"dHkwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCYJB69FbS638eMpSe2OAtp87ZOqCwu\n"
"IR1cRN8hXX4jdP5efrRKt6atH67gBhbim1vZZ3RrXYCPKZ2GG9mcDZhtdhAoWORlsH9KmHmf4MMx\n"
"foArtYzAQDsRhtDLooY2YKTVMIJt2W7QDxIEM5dfT2Fa8OT5kavnHTu86M/0ay00fOJIYRyO82FE\n"
"zG+gSqmUsE3a56k0enI4qEHMPJQRfevIpoy3hsvKMzvZPTeL+3o+hiznc9cKV6xkmxnr9A8ECIqs\n"
"AxcZZPRaJSKNNCyy9mgdEm3Tih4U2sSPpuIjhdV6Db1q4Ons7Be7QhtnqiXtRYMh/MHJfNViPvry\n"
"xS3T/dRlAgMBAAGjgZ8wgZwwEwYJKwYBBAGCNxQCBAYeBABDAEEwCwYDVR0PBAQDAgGGMA8GA1Ud\n"
"EwEB/wQFMAMBAf8wHQYDVR0OBBYEFMZPoj0GY4QJnM5i5ASsjVy16bYbMDYGA1UdHwQvMC0wK6Ap\n"
"oCeGJWh0dHA6Ly9jcmwueHJhbXBzZWN1cml0eS5jb20vWEdDQS5jcmwwEAYJKwYBBAGCNxUBBAMC\n"
"AQEwDQYJKoZIhvcNAQEFBQADggEBAJEVOQMBG2f7Shz5CmBbodpNl2L5JFMn14JkTpAuw0kbK5rc\n"
"/Kh4ZzXxHfARvbdI4xD2Dd8/0sm2qlWkSLoC295ZLhVbO50WfUfXN+pfTXYSNrsf16GBBEYgoyxt\n"
"qZ4Bfj8pzgCT3/3JknOJiWSe5yvkHJEs0rnOfc5vMZnT5r7SHpDwCRR5XCOrTdLaIR9NmXmd4c8n\n"
"nxCbHIgNsIpkQTG4DmyQJKSbXHGPurt+HBvbaoAPIbzp26a3QPSyi6mx5O+aGtA9aZnuqCij4Tyz\n"
"8LIRnM98QObd50N9otg6tamN8jSZxNQQ4Qb9CYQQO+7ETPTsJ3xCwnR8gooJybQDJbw=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Go Daddy Class 2 CA\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEADCCAuigAwIBAgIBADANBgkqhkiG9w0BAQUFADBjMQswCQYDVQQGEwJVUzEhMB8GA1UEChMY\n"
"VGhlIEdvIERhZGR5IEdyb3VwLCBJbmMuMTEwLwYDVQQLEyhHbyBEYWRkeSBDbGFzcyAyIENlcnRp\n"
"ZmljYXRpb24gQXV0aG9yaXR5MB4XDTA0MDYyOTE3MDYyMFoXDTM0MDYyOTE3MDYyMFowYzELMAkG\n"
"A1UEBhMCVVMxITAfBgNVBAoTGFRoZSBHbyBEYWRkeSBHcm91cCwgSW5jLjExMC8GA1UECxMoR28g\n"
"RGFkZHkgQ2xhc3MgMiBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTCCASAwDQYJKoZIhvcNAQEBBQAD\n"
"ggENADCCAQgCggEBAN6d1+pXGEmhW+vXX0iG6r7d/+TvZxz0ZWizV3GgXne77ZtJ6XCAPVYYYwhv\n"
"2vLM0D9/AlQiVBDYsoHUwHU9S3/Hd8M+eKsaA7Ugay9qK7HFiH7Eux6wwdhFJ2+qN1j3hybX2C32\n"
"qRe3H3I2TqYXP2WYktsqbl2i/ojgC95/5Y0V4evLOtXiEqITLdiOr18SPaAIBQi2XKVlOARFmR6j\n"
"YGB0xUGlcmIbYsUfb18aQr4CUWWoriMYavx4A6lNf4DD+qta/KFApMoZFv6yyO9ecw3ud72a9nmY\n"
"vLEHZ6IVDd2gWMZEewo+YihfukEHU1jPEX44dMX4/7VpkI+EdOqXG68CAQOjgcAwgb0wHQYDVR0O\n"
"BBYEFNLEsNKR1EwRcbNhyz2h/t2oatTjMIGNBgNVHSMEgYUwgYKAFNLEsNKR1EwRcbNhyz2h/t2o\n"
"atTjoWekZTBjMQswCQYDVQQGEwJVUzEhMB8GA1UEChMYVGhlIEdvIERhZGR5IEdyb3VwLCBJbmMu\n"
"MTEwLwYDVQQLEyhHbyBEYWRkeSBDbGFzcyAyIENlcnRpZmljYXRpb24gQXV0aG9yaXR5ggEAMAwG\n"
"A1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEFBQADggEBADJL87LKPpH8EsahB4yOd6AzBhRckB4Y9wim\n"
"PQoZ+YeAEW5p5JYXMP80kWNyOO7MHAGjHZQopDH2esRU1/blMVgDoszOYtuURXO1v0XJJLXVggKt\n"
"I3lpjbi2Tc7PTMozI+gciKqdi0FuFskg5YmezTvacPd+mSYgFFQlq25zheabIZ0KbIIOqPjCDPoQ\n"
"HmyW74cNxA9hi63ugyuV+I6ShHI56yDqg+2DzZduCLzrTia2cyvk0/ZM/iZx4mERdEr/VxqHD3VI\n"
"Ls9RaRegAhJhldXRQLIQTO7ErBBDpqWeCtWVYpoNz4iCxTIM5CufReYNnyicsbkqWletNw+vHX/b\n"
"vZ8=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Starfield Class 2 CA\n"
"====================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEDzCCAvegAwIBAgIBADANBgkqhkiG9w0BAQUFADBoMQswCQYDVQQGEwJVUzElMCMGA1UEChMc\n"
"U3RhcmZpZWxkIFRlY2hub2xvZ2llcywgSW5jLjEyMDAGA1UECxMpU3RhcmZpZWxkIENsYXNzIDIg\n"
"Q2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMDQwNjI5MTczOTE2WhcNMzQwNjI5MTczOTE2WjBo\n"
"MQswCQYDVQQGEwJVUzElMCMGA1UEChMcU3RhcmZpZWxkIFRlY2hub2xvZ2llcywgSW5jLjEyMDAG\n"
"A1UECxMpU3RhcmZpZWxkIENsYXNzIDIgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwggEgMA0GCSqG\n"
"SIb3DQEBAQUAA4IBDQAwggEIAoIBAQC3Msj+6XGmBIWtDBFk385N78gDGIc/oav7PKaf8MOh2tTY\n"
"bitTkPskpD6E8J7oX+zlJ0T1KKY/e97gKvDIr1MvnsoFAZMej2YcOadN+lq2cwQlZut3f+dZxkqZ\n"
"JRRU6ybH838Z1TBwj6+wRir/resp7defqgSHo9T5iaU0X9tDkYI22WY8sbi5gv2cOj4QyDvvBmVm\n"
"epsZGD3/cVE8MC5fvj13c7JdBmzDI1aaK4UmkhynArPkPw2vCHmCuDY96pzTNbO8acr1zJ3o/WSN\n"
"F4Azbl5KXZnJHoe0nRrA1W4TNSNe35tfPe/W93bC6j67eA0cQmdrBNj41tpvi/JEoAGrAgEDo4HF\n"
"MIHCMB0GA1UdDgQWBBS/X7fRzt0fhvRbVazc1xDCDqmI5zCBkgYDVR0jBIGKMIGHgBS/X7fRzt0f\n"
"hvRbVazc1xDCDqmI56FspGowaDELMAkGA1UEBhMCVVMxJTAjBgNVBAoTHFN0YXJmaWVsZCBUZWNo\n"
"bm9sb2dpZXMsIEluYy4xMjAwBgNVBAsTKVN0YXJmaWVsZCBDbGFzcyAyIENlcnRpZmljYXRpb24g\n"
"QXV0aG9yaXR5ggEAMAwGA1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEFBQADggEBAAWdP4id0ckaVaGs\n"
"afPzWdqbAYcaT1epoXkJKtv3L7IezMdeatiDh6GX70k1PncGQVhiv45YuApnP+yz3SFmH8lU+nLM\n"
"PUxA2IGvd56Deruix/U0F47ZEUD0/CwqTRV/p2JdLiXTAAsgGh1o+Re49L2L7ShZ3U0WixeDyLJl\n"
"xy16paq8U4Zt3VekyvggQQto8PT7dL5WXXp59fkdheMtlb71cZBDzI0fmgAKhynpVSJYACPq4xJD\n"
"KVtHCN2MQWplBqjlIapBtJUhlbl90TSrE9atvNziPTnNvT51cKEYWQPJIrSPnNVeKtelttQKbfi3\n"
"QBFGmh95DmK/D5fs4C8fF5Q=\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert Assured ID Root CA\n"
"===========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDtzCCAp+gAwIBAgIQDOfg5RfYRv6P5WD8G/AwOTANBgkqhkiG9w0BAQUFADBlMQswCQYDVQQG\n"
"EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSQw\n"
"IgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgQ0EwHhcNMDYxMTEwMDAwMDAwWhcNMzEx\n"
"MTEwMDAwMDAwWjBlMQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQL\n"
"ExB3d3cuZGlnaWNlcnQuY29tMSQwIgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgQ0Ew\n"
"ggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCtDhXO5EOAXLGH87dg+XESpa7cJpSIqvTO\n"
"9SA5KFhgDPiA2qkVlTJhPLWxKISKityfCgyDF3qPkKyK53lTXDGEKvYPmDI2dsze3Tyoou9q+yHy\n"
"UmHfnyDXH+Kx2f4YZNISW1/5WBg1vEfNoTb5a3/UsDg+wRvDjDPZ2C8Y/igPs6eD1sNuRMBhNZYW\n"
"/lmci3Zt1/GiSw0r/wty2p5g0I6QNcZ4VYcgoc/lbQrISXwxmDNsIumH0DJaoroTghHtORedmTpy\n"
"oeb6pNnVFzF1roV9Iq4/AUaG9ih5yLHa5FcXxH4cDrC0kqZWs72yl+2qp/C3xag/lRbQ/6GW6whf\n"
"GHdPAgMBAAGjYzBhMA4GA1UdDwEB/wQEAwIBhjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBRF\n"
"66Kv9JLLgjEtUYunpyGd823IDzAfBgNVHSMEGDAWgBRF66Kv9JLLgjEtUYunpyGd823IDzANBgkq\n"
"hkiG9w0BAQUFAAOCAQEAog683+Lt8ONyc3pklL/3cmbYMuRCdWKuh+vy1dneVrOfzM4UKLkNl2Bc\n"
"EkxY5NM9g0lFWJc1aRqoR+pWxnmrEthngYTffwk8lOa4JiwgvT2zKIn3X/8i4peEH+ll74fg38Fn\n"
"SbNd67IJKusm7Xi+fT8r87cmNW1fiQG2SVufAQWbqz0lwcy2f8Lxb4bG+mRo64EtlOtCt/qMHt1i\n"
"8b5QZ7dsvfPxH2sMNgcWfzd8qVttevESRmCD1ycEvkvOl77DZypoEd+A5wwzZr8TDRRu838fYxAe\n"
"+o0bJW1sj6W3YQGx0qMmoRBxna3iw/nDmVG3KwcIzi7mULKn+gpFL6Lw8g==\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert Global Root CA\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBhMQswCQYDVQQG\n"
"EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSAw\n"
"HgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBDQTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAw\n"
"MDAwMDBaMGExCzAJBgNVBAYTAlVTMRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3\n"
"dy5kaWdpY2VydC5jb20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkq\n"
"hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsBCSDMAZOn\n"
"TjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97nh6Vfe63SKMI2tavegw5\n"
"BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt43C/dxC//AH2hdmoRBBYMql1GNXRor5H\n"
"4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7PT19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y\n"
"7vrTC0LUq7dBMtoM1O/4gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQAB\n"
"o2MwYTAOBgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbRTLtm\n"
"8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUwDQYJKoZIhvcNAQEF\n"
"BQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/EsrhMAtudXH/vTBH1jLuG2cenTnmCmr\n"
"EbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIt\n"
"tep3Sp+dWOIrWcBAI+0tKIJFPnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886\n"
"UAb3LujEV0lsYSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\n"
"CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert High Assurance EV Root CA\n"
"==================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBsMQswCQYDVQQG\n"
"EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSsw\n"
"KQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5jZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAw\n"
"MFoXDTMxMTExMDAwMDAwMFowbDELMAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZ\n"
"MBcGA1UECxMQd3d3LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFu\n"
"Y2UgRVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm+9S75S0t\n"
"Mqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTWPNt0OKRKzE0lgvdKpVMS\n"
"OO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEMxChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3\n"
"MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFBIk5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQ\n"
"NAQTXKFx01p8VdteZOE3hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUe\n"
"h10aUAsgEsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQFMAMB\n"
"Af8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaAFLE+w2kD+L9HAdSY\n"
"JhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3NecnzyIZgYIVyHbIUf4KmeqvxgydkAQ\n"
"V8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6zeM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFp\n"
"myPInngiK3BD41VHMWEZ71jFhS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkK\n"
"mNEVX58Svnw2Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe\n"
"vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep+OkuE6N36B9K\n"
"-----END CERTIFICATE-----\n"
"\n"
"SwissSign Gold CA - G2\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"SwissSign Silver CA - G2\n"
"========================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"SecureTrust CA\n"
"==============\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDuDCCAqCgAwIBAgIQDPCOXAgWpa1Cf/DrJxhZ0DANBgkqhkiG9w0BAQUFADBIMQswCQYDVQQG\n"
"EwJVUzEgMB4GA1UEChMXU2VjdXJlVHJ1c3QgQ29ycG9yYXRpb24xFzAVBgNVBAMTDlNlY3VyZVRy\n"
"dXN0IENBMB4XDTA2MTEwNzE5MzExOFoXDTI5MTIzMTE5NDA1NVowSDELMAkGA1UEBhMCVVMxIDAe\n"
"BgNVBAoTF1NlY3VyZVRydXN0IENvcnBvcmF0aW9uMRcwFQYDVQQDEw5TZWN1cmVUcnVzdCBDQTCC\n"
"ASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKukgeWVzfX2FI7CT8rU4niVWJxB4Q2ZQCQX\n"
"OZEzZum+4YOvYlyJ0fwkW2Gz4BERQRwdbvC4u/jep4G6pkjGnx29vo6pQT64lO0pGtSO0gMdA+9t\n"
"DWccV9cGrcrI9f4Or2YlSASWC12juhbDCE/RRvgUXPLIXgGZbf2IzIaowW8xQmxSPmjL8xk037uH\n"
"GFaAJsTQ3MBv396gwpEWoGQRS0S8Hvbn+mPeZqx2pHGj7DaUaHp3pLHnDi+BeuK1cobvomuL8A/b\n"
"01k/unK8RCSc43Oz969XL0Imnal0ugBS8kvNU3xHCzaFDmapCJcWNFfBZveA4+1wVMeT4C4oFVmH\n"
"ursCAwEAAaOBnTCBmjATBgkrBgEEAYI3FAIEBh4EAEMAQTALBgNVHQ8EBAMCAYYwDwYDVR0TAQH/\n"
"BAUwAwEB/zAdBgNVHQ4EFgQUQjK2FvoE/f5dS3rD/fdMQB1aQ68wNAYDVR0fBC0wKzApoCegJYYj\n"
"aHR0cDovL2NybC5zZWN1cmV0cnVzdC5jb20vU1RDQS5jcmwwEAYJKwYBBAGCNxUBBAMCAQAwDQYJ\n"
"KoZIhvcNAQEFBQADggEBADDtT0rhWDpSclu1pqNlGKa7UTt36Z3q059c4EVlew3KW+JwULKUBRSu\n"
"SceNQQcSc5R+DCMh/bwQf2AQWnL1mA6s7Ll/3XpvXdMc9P+IBWlCqQVxyLesJugutIxq/3HcuLHf\n"
"mbx8IVQr5Fiiu1cprp6poxkmD5kuCLDv/WnPmRoJjeOnnyvJNjR7JLN4TJUXpAYmHrZkUjZfYGfZ\n"
"nMUFdAvnZyPSCPyI6a6Lf+Ew9Dd+/cYy2i2eRDAwbO4H3tI0/NL/QPZL9GZGBlSm8jIKYyYwa5vR\n"
"3ItHuuG51WLQoqD0ZwV4KWMabwTW+MZMo5qxN7SN5ShLHZ4swrhovO0C7jE=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Secure Global CA\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDvDCCAqSgAwIBAgIQB1YipOjUiolN9BPI8PjqpTANBgkqhkiG9w0BAQUFADBKMQswCQYDVQQG\n"
"EwJVUzEgMB4GA1UEChMXU2VjdXJlVHJ1c3QgQ29ycG9yYXRpb24xGTAXBgNVBAMTEFNlY3VyZSBH\n"
"bG9iYWwgQ0EwHhcNMDYxMTA3MTk0MjI4WhcNMjkxMjMxMTk1MjA2WjBKMQswCQYDVQQGEwJVUzEg\n"
"MB4GA1UEChMXU2VjdXJlVHJ1c3QgQ29ycG9yYXRpb24xGTAXBgNVBAMTEFNlY3VyZSBHbG9iYWwg\n"
"Q0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvNS7YrGxVaQZx5RNoJLNP2MwhR/jx\n"
"YDiJiQPpvepeRlMJ3Fz1Wuj3RSoC6zFh1ykzTM7HfAo3fg+6MpjhHZevj8fcyTiW89sa/FHtaMbQ\n"
"bqR8JNGuQsiWUGMu4P51/pinX0kuleM5M2SOHqRfkNJnPLLZ/kG5VacJjnIFHovdRIWCQtBJwB1g\n"
"8NEXLJXr9qXBkqPFwqcIYA1gBBCWeZ4WNOaptvolRTnIHmX5k/Wq8VLcmZg9pYYaDDUz+kulBAYV\n"
"HDGA76oYa8J719rO+TMg1fW9ajMtgQT7sFzUnKPiXB3jqUJ1XnvUd+85VLrJChgbEplJL4hL/VBi\n"
"0XPnj3pDAgMBAAGjgZ0wgZowEwYJKwYBBAGCNxQCBAYeBABDAEEwCwYDVR0PBAQDAgGGMA8GA1Ud\n"
"EwEB/wQFMAMBAf8wHQYDVR0OBBYEFK9EBMJBfkiD2045AuzshHrmzsmkMDQGA1UdHwQtMCswKaAn\n"
"oCWGI2h0dHA6Ly9jcmwuc2VjdXJldHJ1c3QuY29tL1NHQ0EuY3JsMBAGCSsGAQQBgjcVAQQDAgEA\n"
"MA0GCSqGSIb3DQEBBQUAA4IBAQBjGghAfaReUw132HquHw0LURYD7xh8yOOvaliTFGCRsoTciE6+\n"
"OYo68+aCiV0BN7OrJKQVDpI1WkpEXk5X+nXOH0jOZvQ8QCaSmGwb7iRGDBezUqXbpZGRzzfTb+cn\n"
"CDpOGR86p1hcF895P4vkp9MmI50mD1hp/Ed+stCNi5O/KU9DaXR2Z0vPB4zmAve14bRDtUstFJ/5\n"
"3CYNv6ZHdAbYiNE6KTCEztI5gGIbqMdXSbxqVVFnFUq+NQfk1XWYN3kwFNspnWzFacxHVaIw98xc\n"
"f8LDmBxrThaA63p4ZUWiABqvDA1VZDRIuJK58bRQKfJPIx/abKwfROHdI3hRW8cW\n"
"-----END CERTIFICATE-----\n"
"\n"
"COMODO Certification Authority\n"
"==============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEHTCCAwWgAwIBAgIQToEtioJl4AsC7j41AkblPTANBgkqhkiG9w0BAQUFADCBgTELMAkGA1UE\n"
"BhMCR0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgG\n"
"A1UEChMRQ09NT0RPIENBIExpbWl0ZWQxJzAlBgNVBAMTHkNPTU9ETyBDZXJ0aWZpY2F0aW9uIEF1\n"
"dGhvcml0eTAeFw0wNjEyMDEwMDAwMDBaFw0yOTEyMzEyMzU5NTlaMIGBMQswCQYDVQQGEwJHQjEb\n"
"MBkGA1UECBMSR3JlYXRlciBNYW5jaGVzdGVyMRAwDgYDVQQHEwdTYWxmb3JkMRowGAYDVQQKExFD\n"
"T01PRE8gQ0EgTGltaXRlZDEnMCUGA1UEAxMeQ09NT0RPIENlcnRpZmljYXRpb24gQXV0aG9yaXR5\n"
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0ECLi3LjkRv3UcEbVASY06m/weaKXTuH\n"
"+7uIzg3jLz8GlvCiKVCZrts7oVewdFFxze1CkU1B/qnI2GqGd0S7WWaXUF601CxwRM/aN5VCaTww\n"
"xHGzUvAhTaHYujl8HJ6jJJ3ygxaYqhZ8Q5sVW7euNJH+1GImGEaaP+vB+fGQV+useg2L23IwambV\n"
"4EajcNxo2f8ESIl33rXp+2dtQem8Ob0y2WIC8bGoPW43nOIv4tOiJovGuFVDiOEjPqXSJDlqR6sA\n"
"1KGzqSX+DT+nHbrTUcELpNqsOO9VUCQFZUaTNE8tja3G1CEZ0o7KBWFxB3NH5YoZEr0ETc5OnKVI\n"
"rLsm9wIDAQABo4GOMIGLMB0GA1UdDgQWBBQLWOWLxkwVN6RAqTCpIb5HNlpW/zAOBgNVHQ8BAf8E\n"
"BAMCAQYwDwYDVR0TAQH/BAUwAwEB/zBJBgNVHR8EQjBAMD6gPKA6hjhodHRwOi8vY3JsLmNvbW9k\n"
"b2NhLmNvbS9DT01PRE9DZXJ0aWZpY2F0aW9uQXV0aG9yaXR5LmNybDANBgkqhkiG9w0BAQUFAAOC\n"
"AQEAPpiem/Yb6dc5t3iuHXIYSdOH5EOC6z/JqvWote9VfCFSZfnVDeFs9D6Mk3ORLgLETgdxb8CP\n"
"OGEIqB6BCsAvIC9Bi5HcSEW88cbeunZrM8gALTFGTO3nnc+IlP8zwFboJIYmuNg4ON8qa90SzMc/\n"
"RxdMosIGlgnW2/4/PEZB31jiVg88O8EckzXZOFKs7sjsLjBOlDW0JB9LeGna8gI4zJVSk/BwJVmc\n"
"IGfE7vmLV2H0knZ9P4SNVbfo5azV8fUZVqZa+5Acr5Pr5RzUZ5ddBA6+C4OmF4O5MBKgxTMVBbkN\n"
"+8cFduPYSo38NBejxiEovjBFMR7HeL5YYTisO+IBZQ==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Network Solutions Certificate Authority\n"
"=======================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIID5jCCAs6gAwIBAgIQV8szb8JcFuZHFhfjkDFo4DANBgkqhkiG9w0BAQUFADBiMQswCQYDVQQG\n"
"EwJVUzEhMB8GA1UEChMYTmV0d29yayBTb2x1dGlvbnMgTC5MLkMuMTAwLgYDVQQDEydOZXR3b3Jr\n"
"IFNvbHV0aW9ucyBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkwHhcNMDYxMjAxMDAwMDAwWhcNMjkxMjMx\n"
"MjM1OTU5WjBiMQswCQYDVQQGEwJVUzEhMB8GA1UEChMYTmV0d29yayBTb2x1dGlvbnMgTC5MLkMu\n"
"MTAwLgYDVQQDEydOZXR3b3JrIFNvbHV0aW9ucyBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkwggEiMA0G\n"
"CSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDkvH6SMG3G2I4rC7xGzuAnlt7e+foS0zwzc7MEL7xx\n"
"jOWftiJgPl9dzgn/ggwbmlFQGiaJ3dVhXRncEg8tCqJDXRfQNJIg6nPPOCwGJgl6cvf6UDL4wpPT\n"
"aaIjzkGxzOTVHzbRijr4jGPiFFlp7Q3Tf2vouAPlT2rlmGNpSAW+Lv8ztumXWWn4Zxmuk2GWRBXT\n"
"crA/vGp97Eh/jcOrqnErU2lBUzS1sLnFBgrEsEX1QV1uiUV7PTsmjHTC5dLRfbIR1PtYMiKagMnc\n"
"/Qzpf14Dl847ABSHJ3A4qY5usyd2mFHgBeMhqxrVhSI8KbWaFsWAqPS7azCPL0YCorEMIuDTAgMB\n"
"AAGjgZcwgZQwHQYDVR0OBBYEFCEwyfsA106Y2oeqKtCnLrFAMadMMA4GA1UdDwEB/wQEAwIBBjAP\n"
"BgNVHRMBAf8EBTADAQH/MFIGA1UdHwRLMEkwR6BFoEOGQWh0dHA6Ly9jcmwubmV0c29sc3NsLmNv\n"
"bS9OZXR3b3JrU29sdXRpb25zQ2VydGlmaWNhdGVBdXRob3JpdHkuY3JsMA0GCSqGSIb3DQEBBQUA\n"
"A4IBAQC7rkvnt1frf6ott3NHhWrB5KUd5Oc86fRZZXe1eltajSU24HqXLjjAV2CDmAaDn7l2em5Q\n"
"4LqILPxFzBiwmZVRDuwduIj/h1AcgsLj4DKAv6ALR8jDMe+ZZzKATxcheQxpXN5eNK4CtSbqUN9/\n"
"GGUsyfJj4akH/nxxH2szJGoeBfcFaMBqEssuXmHLrijTfsK0ZpEmXzwuJF/LWA/rKOyvEZbz3Htv\n"
"wKeI8lN3s2Berq4o2jUsbzRF0ybh3uxbTydrFny9RAQYgrOJeRcQcT16ohZO9QHNpGxlaKFJdlxD\n"
"ydi8NmdspZS11My5vWo1ViHe2MPr+8ukYEywVaCge1ey\n"
"-----END CERTIFICATE-----\n"
"\n"
"COMODO ECC Certification Authority\n"
"==================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICiTCCAg+gAwIBAgIQH0evqmIAcFBUTAGem2OZKjAKBggqhkjOPQQDAzCBhTELMAkGA1UEBhMC\n"
"R0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgGA1UE\n"
"ChMRQ09NT0RPIENBIExpbWl0ZWQxKzApBgNVBAMTIkNPTU9ETyBFQ0MgQ2VydGlmaWNhdGlvbiBB\n"
"dXRob3JpdHkwHhcNMDgwMzA2MDAwMDAwWhcNMzgwMTE4MjM1OTU5WjCBhTELMAkGA1UEBhMCR0Ix\n"
"GzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgGA1UEChMR\n"
"Q09NT0RPIENBIExpbWl0ZWQxKzApBgNVBAMTIkNPTU9ETyBFQ0MgQ2VydGlmaWNhdGlvbiBBdXRo\n"
"b3JpdHkwdjAQBgcqhkjOPQIBBgUrgQQAIgNiAAQDR3svdcmCFYX7deSRFtSrYpn1PlILBs5BAH+X\n"
"4QokPB0BBO490o0JlwzgdeT6+3eKKvUDYEs2ixYjFq0JcfRK9ChQtP6IHG4/bC8vCVlbpVsLM5ni\n"
"wz2J+Wos77LTBumjQjBAMB0GA1UdDgQWBBR1cacZSBm8nZ3qQUfflMRId5nTeTAOBgNVHQ8BAf8E\n"
"BAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAKBggqhkjOPQQDAwNoADBlAjEA7wNbeqy3eApyt4jf/7VG\n"
"FAkK+qDmfQjGGoe9GKhzvSbKYAydzpmfz1wPMOG+FDHqAjAU9JM8SaczepBGR7NjfRObTrdvGDeA\n"
"U/7dIOA1mjbRxwG55tzd8/8dLDoWV9mSOdY=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Certigna\n"
"========\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDqDCCApCgAwIBAgIJAP7c4wEPyUj/MA0GCSqGSIb3DQEBBQUAMDQxCzAJBgNVBAYTAkZSMRIw\n"
"EAYDVQQKDAlEaGlteW90aXMxETAPBgNVBAMMCENlcnRpZ25hMB4XDTA3MDYyOTE1MTMwNVoXDTI3\n"
"MDYyOTE1MTMwNVowNDELMAkGA1UEBhMCRlIxEjAQBgNVBAoMCURoaW15b3RpczERMA8GA1UEAwwI\n"
"Q2VydGlnbmEwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDIaPHJ1tazNHUmgh7stL7q\n"
"XOEm7RFHYeGifBZ4QCHkYJ5ayGPhxLGWkv8YbWkj4Sti993iNi+RB7lIzw7sebYs5zRLcAglozyH\n"
"GxnygQcPOJAZ0xH+hrTy0V4eHpbNgGzOOzGTtvKg0KmVEn2lmsxryIRWijOp5yIVUxbwzBfsV1/p\n"
"ogqYCd7jX5xv3EjjhQsVWqa6n6xI4wmy9/Qy3l40vhx4XUJbzg4ij02Q130yGLMLLGq/jj8UEYkg\n"
"DncUtT2UCIf3JR7VsmAA7G8qKCVuKj4YYxclPz5EIBb2JsglrgVKtOdjLPOMFlN+XPsRGgjBRmKf\n"
"Irjxwo1p3Po6WAbfAgMBAAGjgbwwgbkwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUGu3+QTmQ\n"
"tCRZvgHyUtVF9lo53BEwZAYDVR0jBF0wW4AUGu3+QTmQtCRZvgHyUtVF9lo53BGhOKQ2MDQxCzAJ\n"
"BgNVBAYTAkZSMRIwEAYDVQQKDAlEaGlteW90aXMxETAPBgNVBAMMCENlcnRpZ25hggkA/tzjAQ/J\n"
"SP8wDgYDVR0PAQH/BAQDAgEGMBEGCWCGSAGG+EIBAQQEAwIABzANBgkqhkiG9w0BAQUFAAOCAQEA\n"
"hQMeknH2Qq/ho2Ge6/PAD/Kl1NqV5ta+aDY9fm4fTIrv0Q8hbV6lUmPOEvjvKtpv6zf+EwLHyzs+\n"
"ImvaYS5/1HI93TDhHkxAGYwP15zRgzB7mFncfca5DClMoTOi62c6ZYTTluLtdkVwj7Ur3vkj1klu\n"
"PBS1xp81HlDQwY9qcEQCYsuuHWhBp6pX6FOqB9IG9tUUBguRA3UsbHK1YZWaDYu5Def131TN3ubY\n"
"1gkIl2PlwS6wt0QmwCbAr1UwnjvVNioZBPRcHv/PLLf/0P2HQBHVESO7SMAhqaQoLf0V+LBOK/Qw\n"
"WyH8EZE0vkHve52Xdf+XlcCWWC/qu0bXu+TZLg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Cybertrust Global Root\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDoTCCAomgAwIBAgILBAAAAAABD4WqLUgwDQYJKoZIhvcNAQEFBQAwOzEYMBYGA1UEChMPQ3li\n"
"ZXJ0cnVzdCwgSW5jMR8wHQYDVQQDExZDeWJlcnRydXN0IEdsb2JhbCBSb290MB4XDTA2MTIxNTA4\n"
"MDAwMFoXDTIxMTIxNTA4MDAwMFowOzEYMBYGA1UEChMPQ3liZXJ0cnVzdCwgSW5jMR8wHQYDVQQD\n"
"ExZDeWJlcnRydXN0IEdsb2JhbCBSb290MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA\n"
"+Mi8vRRQZhP/8NN57CPytxrHjoXxEnOmGaoQ25yiZXRadz5RfVb23CO21O1fWLE3TdVJDm71aofW\n"
"0ozSJ8bi/zafmGWgE07GKmSb1ZASzxQG9Dvj1Ci+6A74q05IlG2OlTEQXO2iLb3VOm2yHLtgwEZL\n"
"AfVJrn5GitB0jaEMAs7u/OePuGtm839EAL9mJRQr3RAwHQeWP032a7iPt3sMpTjr3kfb1V05/Iin\n"
"89cqdPHoWqI7n1C6poxFNcJQZZXcY4Lv3b93TZxiyWNzFtApD0mpSPCzqrdsxacwOUBdrsTiXSZT\n"
"8M4cIwhhqJQZugRiQOwfOHB3EgZxpzAYXSUnpQIDAQABo4GlMIGiMA4GA1UdDwEB/wQEAwIBBjAP\n"
"BgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBS2CHsNesysIEyGVjJez6tuhS1wVzA/BgNVHR8EODA2\n"
"MDSgMqAwhi5odHRwOi8vd3d3Mi5wdWJsaWMtdHJ1c3QuY29tL2NybC9jdC9jdHJvb3QuY3JsMB8G\n"
"A1UdIwQYMBaAFLYIew16zKwgTIZWMl7Pq26FLXBXMA0GCSqGSIb3DQEBBQUAA4IBAQBW7wojoFRO\n"
"lZfJ+InaRcHUowAl9B8Tq7ejhVhpwjCt2BWKLePJzYFa+HMjWqd8BfP9IjsO0QbE2zZMcwSO5bAi\n"
"5MXzLqXZI+O4Tkogp24CJJ8iYGd7ix1yCcUxXOl5n4BHPa2hCwcUPUf/A2kaDAtE52Mlp3+yybh2\n"
"hO0j9n0Hq0V+09+zv+mKts2oomcrUtW3ZfA5TGOgkXmTUg9U3YO7n9GPp1Nzw8v/MOx8BLjYRB+T\n"
"X3EJIrduPuocA06dGiBh+4E37F78CkWr1+cXVdCg6mCbpvbjjFspwgZgFJ0tl0ypkxWdYcQBX0jW\n"
"WL1WMRJOEcgh4LMRkWXbtKaIOM5V\n"
"-----END CERTIFICATE-----\n"
"\n"
"ePKI Root Certification Authority\n"
"=================================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"certSIGN ROOT CA\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDODCCAiCgAwIBAgIGIAYFFnACMA0GCSqGSIb3DQEBBQUAMDsxCzAJBgNVBAYTAlJPMREwDwYD\n"
"VQQKEwhjZXJ0U0lHTjEZMBcGA1UECxMQY2VydFNJR04gUk9PVCBDQTAeFw0wNjA3MDQxNzIwMDRa\n"
"Fw0zMTA3MDQxNzIwMDRaMDsxCzAJBgNVBAYTAlJPMREwDwYDVQQKEwhjZXJ0U0lHTjEZMBcGA1UE\n"
"CxMQY2VydFNJR04gUk9PVCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALczuX7I\n"
"JUqOtdu0KBuqV5Do0SLTZLrTk+jUrIZhQGpgV2hUhE28alQCBf/fm5oqrl0Hj0rDKH/v+yv6efHH\n"
"rfAQUySQi2bJqIirr1qjAOm+ukbuW3N7LBeCgV5iLKECZbO9xSsAfsT8AzNXDe3i+s5dRdY4zTW2\n"
"ssHQnIFKquSyAVwdj1+ZxLGt24gh65AIgoDzMKND5pCCrlUoSe1b16kQOA7+j0xbm0bqQfWwCHTD\n"
"0IgztnzXdN/chNFDDnU5oSVAKOp4yw4sLjmdjItuFhwvJoIQ4uNllAoEwF73XVv4EOLQunpL+943\n"
"AAAaWyjj0pxzPjKHmKHJUS/X3qwzs08CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8B\n"
"Af8EBAMCAcYwHQYDVR0OBBYEFOCMm9slSbPxfIbWskKHC9BroNnkMA0GCSqGSIb3DQEBBQUAA4IB\n"
"AQA+0hyJLjX8+HXd5n9liPRyTMks1zJO890ZeUe9jjtbkw9QSSQTaxQGcu8J06Gh40CEyecYMnQ8\n"
"SG4Pn0vU9x7Tk4ZkVJdjclDVVc/6IJMCopvDI5NOFlV2oHB5bc0hH88vLbwZ44gx+FkagQnIl6Z0\n"
"x2DEW8xXjrJ1/RsCCdtZb3KTafcxQdaIOL+Hsr0Wefmq5L6IJd1hJyMctTEHBDa0GpC9oHRxUIlt\n"
"vBTjD4au8as+x6AJzKNI0eDbZOeStc+vckNwi/nDhDwTqn6Sm1dTk/pwwpEOMfmbZ13pljheX7Nz\n"
"TogVZ96edhBiIL5VaZVDADlN9u6wWk5JRFRYX0KD\n"
"-----END CERTIFICATE-----\n"
"\n"
"NetLock Arany (Class Gold) FÅ‘tanÃºsÃ­tvÃ¡ny\n"
"========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEFTCCAv2gAwIBAgIGSUEs5AAQMA0GCSqGSIb3DQEBCwUAMIGnMQswCQYDVQQGEwJIVTERMA8G\n"
"A1UEBwwIQnVkYXBlc3QxFTATBgNVBAoMDE5ldExvY2sgS2Z0LjE3MDUGA1UECwwuVGFuw7pzw610\n"
"dsOhbnlraWFkw7NrIChDZXJ0aWZpY2F0aW9uIFNlcnZpY2VzKTE1MDMGA1UEAwwsTmV0TG9jayBB\n"
"cmFueSAoQ2xhc3MgR29sZCkgRsWRdGFuw7pzw610dsOhbnkwHhcNMDgxMjExMTUwODIxWhcNMjgx\n"
"MjA2MTUwODIxWjCBpzELMAkGA1UEBhMCSFUxETAPBgNVBAcMCEJ1ZGFwZXN0MRUwEwYDVQQKDAxO\n"
"ZXRMb2NrIEtmdC4xNzA1BgNVBAsMLlRhbsO6c8OtdHbDoW55a2lhZMOzayAoQ2VydGlmaWNhdGlv\n"
"biBTZXJ2aWNlcykxNTAzBgNVBAMMLE5ldExvY2sgQXJhbnkgKENsYXNzIEdvbGQpIEbFkXRhbsO6\n"
"c8OtdHbDoW55MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAxCRec75LbRTDofTjl5Bu\n"
"0jBFHjzuZ9lk4BqKf8owyoPjIMHj9DrTlF8afFttvzBPhCf2nx9JvMaZCpDyD/V/Q4Q3Y1GLeqVw\n"
"/HpYzY6b7cNGbIRwXdrzAZAj/E4wqX7hJ2Pn7WQ8oLjJM2P+FpD/sLj916jAwJRDC7bVWaaeVtAk\n"
"H3B5r9s5VA1lddkVQZQBr17s9o3x/61k/iCa11zr/qYfCGSji3ZVrR47KGAuhyXoqq8fxmRGILdw\n"
"fzzeSNuWU7c5d+Qa4scWhHaXWy+7GRWF+GmF9ZmnqfI0p6m2pgP8b4Y9VHx2BJtr+UBdADTHLpl1\n"
"neWIA6pN+APSQnbAGwIDAKiLo0UwQzASBgNVHRMBAf8ECDAGAQH/AgEEMA4GA1UdDwEB/wQEAwIB\n"
"BjAdBgNVHQ4EFgQUzPpnk/C2uNClwB7zU/2MU9+D15YwDQYJKoZIhvcNAQELBQADggEBAKt/7hwW\n"
"qZw8UQCgwBEIBaeZ5m8BiFRhbvG5GK1Krf6BQCOUL/t1fC8oS2IkgYIL9WHxHG64YTjrgfpioTta\n"
"YtOUZcTh5m2C+C8lcLIhJsFyUR+MLMOEkMNaj7rP9KdlpeuY0fsFskZ1FSNqb4VjMIDw1Z4fKRzC\n"
"bLBQWV2QWzuoDTDPv31/zvGdg73JRm4gpvlhUbohL3u+pRVjodSVh/GeufOJ8z2FuLjbvrW5Kfna\n"
"NwUASZQDhETnv0Mxz3WLJdH0pmT1kvarBes96aULNmLazAZfNou2XjG4Kvte9nHfRCaexOYNkbQu\n"
"dZWAUWpLMKawYqGT8ZvYzsRjdT9ZR7E=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Hongkong Post Root CA 1\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDMDCCAhigAwIBAgICA+gwDQYJKoZIhvcNAQEFBQAwRzELMAkGA1UEBhMCSEsxFjAUBgNVBAoT\n"
"DUhvbmdrb25nIFBvc3QxIDAeBgNVBAMTF0hvbmdrb25nIFBvc3QgUm9vdCBDQSAxMB4XDTAzMDUx\n"
"NTA1MTMxNFoXDTIzMDUxNTA0NTIyOVowRzELMAkGA1UEBhMCSEsxFjAUBgNVBAoTDUhvbmdrb25n\n"
"IFBvc3QxIDAeBgNVBAMTF0hvbmdrb25nIFBvc3QgUm9vdCBDQSAxMIIBIjANBgkqhkiG9w0BAQEF\n"
"AAOCAQ8AMIIBCgKCAQEArP84tulmAknjorThkPlAj3n54r15/gK97iSSHSL22oVyaf7XPwnU3ZG1\n"
"ApzQjVrhVcNQhrkpJsLj2aDxaQMoIIBFIi1WpztUlVYiWR8o3x8gPW2iNr4joLFutbEnPzlTCeqr\n"
"auh0ssJlXI6/fMN4hM2eFvz1Lk8gKgifd/PFHsSaUmYeSF7jEAaPIpjhZY4bXSNmO7ilMlHIhqqh\n"
"qZ5/dpTCpmy3QfDVyAY45tQM4vM7TG1QjMSDJ8EThFk9nnV0ttgCXjqQesBCNnLsak3c78QA3xMY\n"
"V18meMjWCnl3v/evt3a5pQuEF10Q6m/hq5URX208o1xNg1vysxmKgIsLhwIDAQABoyYwJDASBgNV\n"
"HRMBAf8ECDAGAQH/AgEDMA4GA1UdDwEB/wQEAwIBxjANBgkqhkiG9w0BAQUFAAOCAQEADkbVPK7i\n"
"h9legYsCmEEIjEy82tvuJxuC52pF7BaLT4Wg87JwvVqWuspube5Gi27nKi6Wsxkz67SfqLI37pio\n"
"l7Yutmcn1KZJ/RyTZXaeQi/cImyaT/JaFTmxcdcrUehtHJjA2Sr0oYJ71clBoiMBdDhViw+5Lmei\n"
"IAQ32pwL0xch4I+XeTRvhEgCIDMb5jREn5Fw9IBehEPCKdJsEhTkYY2sEJCehFC78JZvRZ+K88ps\n"
"T/oROhUVRsPNH4NbLUES7VBnQRM9IauUiqpOfMGx+6fWtScvl6tu4B3i0RwsH0Ti/L6RoZz71ilT\n"
"c4afU9hDDl3WY4JxHYB0yvbiAmvZWg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"SecureSign RootCA11\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDbTCCAlWgAwIBAgIBATANBgkqhkiG9w0BAQUFADBYMQswCQYDVQQGEwJKUDErMCkGA1UEChMi\n"
"SmFwYW4gQ2VydGlmaWNhdGlvbiBTZXJ2aWNlcywgSW5jLjEcMBoGA1UEAxMTU2VjdXJlU2lnbiBS\n"
"b290Q0ExMTAeFw0wOTA0MDgwNDU2NDdaFw0yOTA0MDgwNDU2NDdaMFgxCzAJBgNVBAYTAkpQMSsw\n"
"KQYDVQQKEyJKYXBhbiBDZXJ0aWZpY2F0aW9uIFNlcnZpY2VzLCBJbmMuMRwwGgYDVQQDExNTZWN1\n"
"cmVTaWduIFJvb3RDQTExMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA/XeqpRyQBTvL\n"
"TJszi1oURaTnkBbR31fSIRCkF/3frNYfp+TbfPfs37gD2pRY/V1yfIw/XwFndBWW4wI8h9uuywGO\n"
"wvNmxoVF9ALGOrVisq/6nL+k5tSAMJjzDbaTj6nU2DbysPyKyiyhFTOVMdrAG/LuYpmGYz+/3ZMq\n"
"g6h2uRMft85OQoWPIucuGvKVCbIFtUROd6EgvanyTgp9UK31BQ1FT0Zx/Sg+U/sE2C3XZR1KG/rP\n"
"O7AxmjVuyIsG0wCR8pQIZUyxNAYAeoni8McDWc/V1uinMrPmmECGxc0nEovMe863ETxiYAcjPitA\n"
"bpSACW22s293bzUIUPsCh8U+iQIDAQABo0IwQDAdBgNVHQ4EFgQUW/hNT7KlhtQ60vFjmqC+CfZX\n"
"t94wDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQEFBQADggEBAKCh\n"
"OBZmLqdWHyGcBvod7bkixTgm2E5P7KN/ed5GIaGHd48HCJqypMWvDzKYC3xmKbabfSVSSUOrTC4r\n"
"bnpwrxYO4wJs+0LmGJ1F2FXI6Dvd5+H0LgscNFxsWEr7jIhQX5Ucv+2rIrVls4W6ng+4reV6G4pQ\n"
"Oh29Dbx7VFALuUKvVaAYga1lme++5Jy/xIWrQbJUb9wlze144o4MjQlJ3WN7WmmWAiGovVJZ6X01\n"
"y8hSyn+B/tlr0/cR7SXf+Of5pPpyl4RTDaXQMhhRdlkUbA/r7F+AjHVDg8OFmP9Mni0N5HeDk061\n"
"lgeLKBObjBmNQSdJQO7e5iNEOdyhIta6A/I=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Microsec e-Szigno Root CA 2009\n"
"==============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIECjCCAvKgAwIBAgIJAMJ+QwRORz8ZMA0GCSqGSIb3DQEBCwUAMIGCMQswCQYDVQQGEwJIVTER\n"
"MA8GA1UEBwwIQnVkYXBlc3QxFjAUBgNVBAoMDU1pY3Jvc2VjIEx0ZC4xJzAlBgNVBAMMHk1pY3Jv\n"
"c2VjIGUtU3ppZ25vIFJvb3QgQ0EgMjAwOTEfMB0GCSqGSIb3DQEJARYQaW5mb0BlLXN6aWduby5o\n"
"dTAeFw0wOTA2MTYxMTMwMThaFw0yOTEyMzAxMTMwMThaMIGCMQswCQYDVQQGEwJIVTERMA8GA1UE\n"
"BwwIQnVkYXBlc3QxFjAUBgNVBAoMDU1pY3Jvc2VjIEx0ZC4xJzAlBgNVBAMMHk1pY3Jvc2VjIGUt\n"
"U3ppZ25vIFJvb3QgQ0EgMjAwOTEfMB0GCSqGSIb3DQEJARYQaW5mb0BlLXN6aWduby5odTCCASIw\n"
"DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOn4j/NjrdqG2KfgQvvPkd6mJviZpWNwrZuuyjNA\n"
"fW2WbqEORO7hE52UQlKavXWFdCyoDh2Tthi3jCyoz/tccbna7P7ofo/kLx2yqHWH2Leh5TvPmUpG\n"
"0IMZfcChEhyVbUr02MelTTMuhTlAdX4UfIASmFDHQWe4oIBhVKZsTh/gnQ4H6cm6M+f+wFUoLAKA\n"
"pxn1ntxVUwOXewdI/5n7N4okxFnMUBBjjqqpGrCEGob5X7uxUG6k0QrM1XF+H6cbfPVTbiJfyyvm\n"
"1HxdrtbCxkzlBQHZ7Vf8wSN5/PrIJIOV87VqUQHQd9bpEqH5GoP7ghu5sJf0dgYzQ0mg/wu1+rUC\n"
"AwEAAaOBgDB+MA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgEGMB0GA1UdDgQWBBTLD8bf\n"
"QkPMPcu1SCOhGnqmKrs0aDAfBgNVHSMEGDAWgBTLD8bfQkPMPcu1SCOhGnqmKrs0aDAbBgNVHREE\n"
"FDASgRBpbmZvQGUtc3ppZ25vLmh1MA0GCSqGSIb3DQEBCwUAA4IBAQDJ0Q5eLtXMs3w+y/w9/w0o\n"
"lZMEyL/azXm4Q5DwpL7v8u8hmLzU1F0G9u5C7DBsoKqpyvGvivo/C3NqPuouQH4frlRheesuCDfX\n"
"I/OMn74dseGkddug4lQUsbocKaQY9hK6ohQU4zE1yED/t+AFdlfBHFny+L/k7SViXITwfn4fs775\n"
"tyERzAMBVnCnEJIeGzSBHq2cGsMEPO0CYdYeBvNfOofyK/FFh+U9rNHHV4S9a67c2Pm2G2JwCz02\n"
"yULyMtd6YebS2z3PyKnJm9zbWETXbzivf3jTo60adbocwTZ8jx5tHMN1Rq41Bab2XD0h7lbwyYIi\n"
"LXpUq3DDfSJlgnCW\n"
"-----END CERTIFICATE-----\n"
"\n"
"GlobalSign Root CA - R3\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDXzCCAkegAwIBAgILBAAAAAABIVhTCKIwDQYJKoZIhvcNAQELBQAwTDEgMB4GA1UECxMXR2xv\n"
"YmFsU2lnbiBSb290IENBIC0gUjMxEzARBgNVBAoTCkdsb2JhbFNpZ24xEzARBgNVBAMTCkdsb2Jh\n"
"bFNpZ24wHhcNMDkwMzE4MTAwMDAwWhcNMjkwMzE4MTAwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxT\n"
"aWduIFJvb3QgQ0EgLSBSMzETMBEGA1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2ln\n"
"bjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMwldpB5BngiFvXAg7aEyiie/QV2EcWt\n"
"iHL8RgJDx7KKnQRfJMsuS+FggkbhUqsMgUdwbN1k0ev1LKMPgj0MK66X17YUhhB5uzsTgHeMCOFJ\n"
"0mpiLx9e+pZo34knlTifBtc+ycsmWQ1z3rDI6SYOgxXG71uL0gRgykmmKPZpO/bLyCiR5Z2KYVc3\n"
"rHQU3HTgOu5yLy6c+9C7v/U9AOEGM+iCK65TpjoWc4zdQQ4gOsC0p6Hpsk+QLjJg6VfLuQSSaGjl\n"
"OCZgdbKfd/+RFO+uIEn8rUAVSNECMWEZXriX7613t2Saer9fwRPvm2L7DWzgVGkWqQPabumDk3F2\n"
"xmmFghcCAwEAAaNCMEAwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYE\n"
"FI/wS3+oLkUkrk1Q+mOai97i3Ru8MA0GCSqGSIb3DQEBCwUAA4IBAQBLQNvAUKr+yAzv95ZURUm7\n"
"lgAJQayzE4aGKAczymvmdLm6AC2upArT9fHxD4q/c2dKg8dEe3jgr25sbwMpjjM5RcOO5LlXbKr8\n"
"EpbsU8Yt5CRsuZRj+9xTaGdWPoO4zzUhw8lo/s7awlOqzJCK6fBdRoyV3XpYKBovHd7NADdBj+1E\n"
"bddTKJd+82cEHhXXipa0095MJ6RMG3NzdvQXmcIfeg7jLQitChws/zyrVQ4PkX4268NXSb7hLi18\n"
"YIvDQVETI53O9zJrlAGomecsMx86OyXShkDOOyyGeMlhLxS67ttVb9+E7gUJTb0o2HLO02JQZR7r\n"
"kpeDMdmztcpHWD9f\n"
"-----END CERTIFICATE-----\n"
"\n"
"Autoridad de Certificacion Firmaprofesional CIF A62634068\n"
"=========================================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIGFDCCA/ygAwIBAgIIU+w77vuySF8wDQYJKoZIhvcNAQEFBQAwUTELMAkGA1UEBhMCRVMxQjBA\n"
"BgNVBAMMOUF1dG9yaWRhZCBkZSBDZXJ0aWZpY2FjaW9uIEZpcm1hcHJvZmVzaW9uYWwgQ0lGIEE2\n"
"MjYzNDA2ODAeFw0wOTA1MjAwODM4MTVaFw0zMDEyMzEwODM4MTVaMFExCzAJBgNVBAYTAkVTMUIw\n"
"QAYDVQQDDDlBdXRvcmlkYWQgZGUgQ2VydGlmaWNhY2lvbiBGaXJtYXByb2Zlc2lvbmFsIENJRiBB\n"
"NjI2MzQwNjgwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQDKlmuO6vj78aI14H9M2uDD\n"
"Utd9thDIAl6zQyrET2qyyhxdKJp4ERppWVevtSBC5IsP5t9bpgOSL/UR5GLXMnE42QQMcas9UX4P\n"
"B99jBVzpv5RvwSmCwLTaUbDBPLutN0pcyvFLNg4kq7/DhHf9qFD0sefGL9ItWY16Ck6WaVICqjaY\n"
"7Pz6FIMMNx/Jkjd/14Et5cS54D40/mf0PmbR0/RAz15iNA9wBj4gGFrO93IbJWyTdBSTo3OxDqqH\n"
"ECNZXyAFGUftaI6SEspd/NYrspI8IM/hX68gvqB2f3bl7BqGYTM+53u0P6APjqK5am+5hyZvQWyI\n"
"plD9amML9ZMWGxmPsu2bm8mQ9QEM3xk9Dz44I8kvjwzRAv4bVdZO0I08r0+k8/6vKtMFnXkIoctX\n"
"MbScyJCyZ/QYFpM6/EfY0XiWMR+6KwxfXZmtY4laJCB22N/9q06mIqqdXuYnin1oKaPnirjaEbsX\n"
"LZmdEyRG98Xi2J+Of8ePdG1asuhy9azuJBCtLxTa/y2aRnFHvkLfuwHb9H/TKI8xWVvTyQKmtFLK\n"
"bpf7Q8UIJm+K9Lv9nyiqDdVF8xM6HdjAeI9BZzwelGSuewvF6NkBiDkal4ZkQdU7hwxu+g/GvUgU\n"
"vzlN1J5Bto+WHWOWk9mVBngxaJ43BjuAiUVhOSPHG0SjFeUc+JIwuwIDAQABo4HvMIHsMBIGA1Ud\n"
"EwEB/wQIMAYBAf8CAQEwDgYDVR0PAQH/BAQDAgEGMB0GA1UdDgQWBBRlzeurNR4APn7VdMActHNH\n"
"DhpkLzCBpgYDVR0gBIGeMIGbMIGYBgRVHSAAMIGPMC8GCCsGAQUFBwIBFiNodHRwOi8vd3d3LmZp\n"
"cm1hcHJvZmVzaW9uYWwuY29tL2NwczBcBggrBgEFBQcCAjBQHk4AUABhAHMAZQBvACAAZABlACAA\n"
"bABhACAAQgBvAG4AYQBuAG8AdgBhACAANAA3ACAAQgBhAHIAYwBlAGwAbwBuAGEAIAAwADgAMAAx\n"
"ADcwDQYJKoZIhvcNAQEFBQADggIBABd9oPm03cXF661LJLWhAqvdpYhKsg9VSytXjDvlMd3+xDLx\n"
"51tkljYyGOylMnfX40S2wBEqgLk9am58m9Ot/MPWo+ZkKXzR4Tgegiv/J2Wv+xYVxC5xhOW1//qk\n"
"R71kMrv2JYSiJ0L1ILDCExARzRAVukKQKtJE4ZYm6zFIEv0q2skGz3QeqUvVhyj5eTSSPi5E6PaP\n"
"T481PyWzOdxjKpBrIF/EUhJOlywqrJ2X3kjyo2bbwtKDlaZmp54lD+kLM5FlClrD2VQS3a/DTg4f\n"
"Jl4N3LON7NWBcN7STyQF82xO9UxJZo3R/9ILJUFI/lGExkKvgATP0H5kSeTy36LssUzAKh3ntLFl\n"
"osS88Zj0qnAHY7S42jtM+kAiMFsRpvAFDsYCA0irhpuF3dvd6qJ2gHN99ZwExEWN57kci57q13XR\n"
"crHedUTnQn3iV2t93Jm8PYMo6oCTjcVMZcFwgbg4/EMxsvYDNEeyrPsiBsse3RdHHF9mudMaotoR\n"
"saS8I8nkvof/uZS2+F0gStRf571oe2XyFR7SOqkt6dhrJKyXWERHrVkY8SFlcN7ONGCoQPHzPKTD\n"
"KCOM/iczQ0CgFzzr6juwcqajuUpLXhZI9LK8yIySxZ2frHI2vDSANGupi5LAuBft7HZT9SQBjLMi\n"
"6Et8Vcad+qMUu2WFbm5PEn4KPJ2V\n"
"-----END CERTIFICATE-----\n"
"\n"
"Izenpe.com\n"
"==========\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"Go Daddy Root Certificate Authority - G2\n"
"========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDxTCCAq2gAwIBAgIBADANBgkqhkiG9w0BAQsFADCBgzELMAkGA1UEBhMCVVMxEDAOBgNVBAgT\n"
"B0FyaXpvbmExEzARBgNVBAcTClNjb3R0c2RhbGUxGjAYBgNVBAoTEUdvRGFkZHkuY29tLCBJbmMu\n"
"MTEwLwYDVQQDEyhHbyBEYWRkeSBSb290IENlcnRpZmljYXRlIEF1dGhvcml0eSAtIEcyMB4XDTA5\n"
"MDkwMTAwMDAwMFoXDTM3MTIzMTIzNTk1OVowgYMxCzAJBgNVBAYTAlVTMRAwDgYDVQQIEwdBcml6\n"
"b25hMRMwEQYDVQQHEwpTY290dHNkYWxlMRowGAYDVQQKExFHb0RhZGR5LmNvbSwgSW5jLjExMC8G\n"
"A1UEAxMoR28gRGFkZHkgUm9vdCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgLSBHMjCCASIwDQYJKoZI\n"
"hvcNAQEBBQADggEPADCCAQoCggEBAL9xYgjx+lk09xvJGKP3gElY6SKDE6bFIEMBO4Tx5oVJnyfq\n"
"9oQbTqC023CYxzIBsQU+B07u9PpPL1kwIuerGVZr4oAH/PMWdYA5UXvl+TW2dE6pjYIT5LY/qQOD\n"
"+qK+ihVqf94Lw7YZFAXK6sOoBJQ7RnwyDfMAZiLIjWltNowRGLfTshxgtDj6AozO091GB94KPutd\n"
"fMh8+7ArU6SSYmlRJQVhGkSBjCypQ5Yj36w6gZoOKcUcqeldHraenjAKOc7xiID7S13MMuyFYkMl\n"
"NAJWJwGRtDtwKj9useiciAF9n9T521NtYJ2/LOdYq7hfRvzOxBsDPAnrSTFcaUaz4EcCAwEAAaNC\n"
"MEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYEFDqahQcQZyi27/a9\n"
"BUFuIMGU2g/eMA0GCSqGSIb3DQEBCwUAA4IBAQCZ21151fmXWWcDYfF+OwYxdS2hII5PZYe096ac\n"
"vNjpL9DbWu7PdIxztDhC2gV7+AJ1uP2lsdeu9tfeE8tTEH6KRtGX+rcuKxGrkLAngPnon1rpN5+r\n"
"5N9ss4UXnT3ZJE95kTXWXwTrgIOrmgIttRD02JDHBHNA7XIloKmf7J6raBKZV8aPEjoJpL1E/QYV\n"
"N8Gb5DKj7Tjo2GTzLH4U/ALqn83/B2gX2yKQOC16jdFU8WnjXzPKej17CuPKf1855eJ1usV2GDPO\n"
"LPAvTK33sefOT6jEm0pUBsV/fdUID+Ic/n4XuKxe9tQWskMJDE32p2u0mYRlynqI4uJEvlz36hz1\n"
"-----END CERTIFICATE-----\n"
"\n"
"Starfield Root Certificate Authority - G2\n"
"=========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIID3TCCAsWgAwIBAgIBADANBgkqhkiG9w0BAQsFADCBjzELMAkGA1UEBhMCVVMxEDAOBgNVBAgT\n"
"B0FyaXpvbmExEzARBgNVBAcTClNjb3R0c2RhbGUxJTAjBgNVBAoTHFN0YXJmaWVsZCBUZWNobm9s\n"
"b2dpZXMsIEluYy4xMjAwBgNVBAMTKVN0YXJmaWVsZCBSb290IENlcnRpZmljYXRlIEF1dGhvcml0\n"
"eSAtIEcyMB4XDTA5MDkwMTAwMDAwMFoXDTM3MTIzMTIzNTk1OVowgY8xCzAJBgNVBAYTAlVTMRAw\n"
"DgYDVQQIEwdBcml6b25hMRMwEQYDVQQHEwpTY290dHNkYWxlMSUwIwYDVQQKExxTdGFyZmllbGQg\n"
"VGVjaG5vbG9naWVzLCBJbmMuMTIwMAYDVQQDEylTdGFyZmllbGQgUm9vdCBDZXJ0aWZpY2F0ZSBB\n"
"dXRob3JpdHkgLSBHMjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL3twQP89o/8ArFv\n"
"W59I2Z154qK3A2FWGMNHttfKPTUuiUP3oWmb3ooa/RMgnLRJdzIpVv257IzdIvpy3Cdhl+72WoTs\n"
"bhm5iSzchFvVdPtrX8WJpRBSiUZV9Lh1HOZ/5FSuS/hVclcCGfgXcVnrHigHdMWdSL5stPSksPNk\n"
"N3mSwOxGXn/hbVNMYq/NHwtjuzqd+/x5AJhhdM8mgkBj87JyahkNmcrUDnXMN/uLicFZ8WJ/X7Nf\n"
"ZTD4p7dNdloedl40wOiWVpmKs/B/pM293DIxfJHP4F8R+GuqSVzRmZTRouNjWwl2tVZi4Ut0HZbU\n"
"JtQIBFnQmA4O5t78w+wfkPECAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AQYwHQYDVR0OBBYEFHwMMh+n2TB/xH1oo2Kooc6rB1snMA0GCSqGSIb3DQEBCwUAA4IBAQARWfol\n"
"TwNvlJk7mh+ChTnUdgWUXuEok21iXQnCoKjUsHU48TRqneSfioYmUeYs0cYtbpUgSpIB7LiKZ3sx\n"
"4mcujJUDJi5DnUox9g61DLu34jd/IroAow57UvtruzvE03lRTs2Q9GcHGcg8RnoNAX3FWOdt5oUw\n"
"F5okxBDgBPfg8n/Uqgr/Qh037ZTlZFkSIHc40zI+OIF1lnP6aI+xy84fxez6nH7PfrHxBy22/L/K\n"
"pL/QlwVKvOoYKAKQvVR4CSFx09F9HdkWsKlhPdAKACL8x3vLCWRFCztAgfd9fDL1mMpYjn0q7pBZ\n"
"c2T5NnReJaH1ZgUufzkVqSr7UIuOhWn0\n"
"-----END CERTIFICATE-----\n"
"\n"
"Starfield Services Root Certificate Authority - G2\n"
"==================================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIID7zCCAtegAwIBAgIBADANBgkqhkiG9w0BAQsFADCBmDELMAkGA1UEBhMCVVMxEDAOBgNVBAgT\n"
"B0FyaXpvbmExEzARBgNVBAcTClNjb3R0c2RhbGUxJTAjBgNVBAoTHFN0YXJmaWVsZCBUZWNobm9s\n"
"b2dpZXMsIEluYy4xOzA5BgNVBAMTMlN0YXJmaWVsZCBTZXJ2aWNlcyBSb290IENlcnRpZmljYXRl\n"
"IEF1dGhvcml0eSAtIEcyMB4XDTA5MDkwMTAwMDAwMFoXDTM3MTIzMTIzNTk1OVowgZgxCzAJBgNV\n"
"BAYTAlVTMRAwDgYDVQQIEwdBcml6b25hMRMwEQYDVQQHEwpTY290dHNkYWxlMSUwIwYDVQQKExxT\n"
"dGFyZmllbGQgVGVjaG5vbG9naWVzLCBJbmMuMTswOQYDVQQDEzJTdGFyZmllbGQgU2VydmljZXMg\n"
"Um9vdCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgLSBHMjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\n"
"AQoCggEBANUMOsQq+U7i9b4Zl1+OiFOxHz/Lz58gE20pOsgPfTz3a3Y4Y9k2YKibXlwAgLIvWX/2\n"
"h/klQ4bnaRtSmpDhcePYLQ1Ob/bISdm28xpWriu2dBTrz/sm4xq6HZYuajtYlIlHVv8loJNwU4Pa\n"
"hHQUw2eeBGg6345AWh1KTs9DkTvnVtYAcMtS7nt9rjrnvDH5RfbCYM8TWQIrgMw0R9+53pBlbQLP\n"
"LJGmpufehRhJfGZOozptqbXuNC66DQO4M99H67FrjSXZm86B0UVGMpZwh94CDklDhbZsc7tk6mFB\n"
"rMnUVN+HL8cisibMn1lUaJ/8viovxFUcdUBgF4UCVTmLfwUCAwEAAaNCMEAwDwYDVR0TAQH/BAUw\n"
"AwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYEFJxfAN+qAdcwKziIorhtSpzyEZGDMA0GCSqG\n"
"SIb3DQEBCwUAA4IBAQBLNqaEd2ndOxmfZyMIbw5hyf2E3F/YNoHN2BtBLZ9g3ccaaNnRbobhiCPP\n"
"E95Dz+I0swSdHynVv/heyNXBve6SbzJ08pGCL72CQnqtKrcgfU28elUSwhXqvfdqlS5sdJ/PHLTy\n"
"xQGjhdByPq1zqwubdQxtRbeOlKyWN7Wg0I8VRw7j6IPdj/3vQQF3zCepYoUz8jcI73HPdwbeyBkd\n"
"iEDPfUYd/x7H4c7/I9vG+o1VTqkC50cRRj70/b17KSa7qWFiNyi2LSr2EIZkyXCn0q23KXB56jza\n"
"YyWf/Wi3MOxw+3WKt21gZ7IeyLnp2KhvAotnDU0mV3HaIPzBSlCNsSi6\n"
"-----END CERTIFICATE-----\n"
"\n"
"AffirmTrust Commercial\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDTDCCAjSgAwIBAgIId3cGJyapsXwwDQYJKoZIhvcNAQELBQAwRDELMAkGA1UEBhMCVVMxFDAS\n"
"BgNVBAoMC0FmZmlybVRydXN0MR8wHQYDVQQDDBZBZmZpcm1UcnVzdCBDb21tZXJjaWFsMB4XDTEw\n"
"MDEyOTE0MDYwNloXDTMwMTIzMTE0MDYwNlowRDELMAkGA1UEBhMCVVMxFDASBgNVBAoMC0FmZmly\n"
"bVRydXN0MR8wHQYDVQQDDBZBZmZpcm1UcnVzdCBDb21tZXJjaWFsMIIBIjANBgkqhkiG9w0BAQEF\n"
"AAOCAQ8AMIIBCgKCAQEA9htPZwcroRX1BiLLHwGy43NFBkRJLLtJJRTWzsO3qyxPxkEylFf6Eqdb\n"
"DuKPHx6GGaeqtS25Xw2Kwq+FNXkyLbscYjfysVtKPcrNcV/pQr6U6Mje+SJIZMblq8Yrba0F8PrV\n"
"C8+a5fBQpIs7R6UjW3p6+DM/uO+Zl+MgwdYoic+U+7lF7eNAFxHUdPALMeIrJmqbTFeurCA+ukV6\n"
"BfO9m2kVrn1OIGPENXY6BwLJN/3HR+7o8XYdcxXyl6S1yHp52UKqK39c/s4mT6NmgTWvRLpUHhww\n"
"MmWd5jyTXlBOeuM61G7MGvv50jeuJCqrVwMiKA1JdX+3KNp1v47j3A55MQIDAQABo0IwQDAdBgNV\n"
"HQ4EFgQUnZPGU4teyq8/nx4P5ZmVvCT2lI8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AQYwDQYJKoZIhvcNAQELBQADggEBAFis9AQOzcAN/wr91LoWXym9e2iZWEnStB03TX8nfUYGXUPG\n"
"hi4+c7ImfU+TqbbEKpqrIZcUsd6M06uJFdhrJNTxFq7YpFzUf1GO7RgBsZNjvbz4YYCanrHOQnDi\n"
"qX0GJX0nof5v7LMeJNrjS1UaADs1tDvZ110w/YETifLCBivtZ8SOyUOyXGsViQK8YvxO8rUzqrJv\n"
"0wqiUOP2O+guRMLbZjipM1ZI8W0bM40NjD9gN53Tym1+NH4Nn3J2ixufcv1SNUFFApYvHLKac0kh\n"
"sUlHRUe072o0EclNmsxZt9YCnlpOZbWUrhvfKbAW8b8Angc6F2S1BLUjIZkKlTuXfO8=\n"
"-----END CERTIFICATE-----\n"
"\n"
"AffirmTrust Networking\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDTDCCAjSgAwIBAgIIfE8EORzUmS0wDQYJKoZIhvcNAQEFBQAwRDELMAkGA1UEBhMCVVMxFDAS\n"
"BgNVBAoMC0FmZmlybVRydXN0MR8wHQYDVQQDDBZBZmZpcm1UcnVzdCBOZXR3b3JraW5nMB4XDTEw\n"
"MDEyOTE0MDgyNFoXDTMwMTIzMTE0MDgyNFowRDELMAkGA1UEBhMCVVMxFDASBgNVBAoMC0FmZmly\n"
"bVRydXN0MR8wHQYDVQQDDBZBZmZpcm1UcnVzdCBOZXR3b3JraW5nMIIBIjANBgkqhkiG9w0BAQEF\n"
"AAOCAQ8AMIIBCgKCAQEAtITMMxcua5Rsa2FSoOujz3mUTOWUgJnLVWREZY9nZOIG41w3SfYvm4SE\n"
"Hi3yYJ0wTsyEheIszx6e/jarM3c1RNg1lho9Nuh6DtjVR6FqaYvZ/Ls6rnla1fTWcbuakCNrmreI\n"
"dIcMHl+5ni36q1Mr3Lt2PpNMCAiMHqIjHNRqrSK6mQEubWXLviRmVSRLQESxG9fhwoXA3hA/Pe24\n"
"/PHxI1Pcv2WXb9n5QHGNfb2V1M6+oF4nI979ptAmDgAp6zxG8D1gvz9Q0twmQVGeFDdCBKNwV6gb\n"
"h+0t+nvujArjqWaJGctB+d1ENmHP4ndGyH329JKBNv3bNPFyfvMMFr20FQIDAQABo0IwQDAdBgNV\n"
"HQ4EFgQUBx/S55zawm6iQLSwelAQUHTEyL0wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AQYwDQYJKoZIhvcNAQEFBQADggEBAIlXshZ6qML91tmbmzTCnLQyFE2npN/svqe++EPbkTfOtDIu\n"
"UFUaNU52Q3Eg75N3ThVwLofDwR1t3Mu1J9QsVtFSUzpE0nPIxBsFZVpikpzuQY0x2+c06lkh1QF6\n"
"12S4ZDnNye2v7UsDSKegmQGA3GWjNq5lWUhPgkvIZfFXHeVZLgo/bNjR9eUJtGxUAArgFU2HdW23\n"
"WJZa3W3SAKD0m0i+wzekujbgfIeFlxoVot4uolu9rxj5kFDNcFn4J2dHy8egBzp90SxdbBk6ZrV9\n"
"/ZFvgrG+CJPbFEfxojfHRZ48x3evZKiT3/Zpg4Jg8klCNO1aAFSFHBY2kgxc+qatv9s=\n"
"-----END CERTIFICATE-----\n"
"\n"
"AffirmTrust Premium\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFRjCCAy6gAwIBAgIIbYwURrGmCu4wDQYJKoZIhvcNAQEMBQAwQTELMAkGA1UEBhMCVVMxFDAS\n"
"BgNVBAoMC0FmZmlybVRydXN0MRwwGgYDVQQDDBNBZmZpcm1UcnVzdCBQcmVtaXVtMB4XDTEwMDEy\n"
"OTE0MTAzNloXDTQwMTIzMTE0MTAzNlowQTELMAkGA1UEBhMCVVMxFDASBgNVBAoMC0FmZmlybVRy\n"
"dXN0MRwwGgYDVQQDDBNBZmZpcm1UcnVzdCBQcmVtaXVtMIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\n"
"MIICCgKCAgEAxBLfqV/+Qd3d9Z+K4/as4Tx4mrzY8H96oDMq3I0gW64tb+eT2TZwamjPjlGjhVtn\n"
"BKAQJG9dKILBl1fYSCkTtuG+kU3fhQxTGJoeJKJPj/CihQvL9Cl/0qRY7iZNyaqoe5rZ+jjeRFcV\n"
"5fiMyNlI4g0WJx0eyIOFJbe6qlVBzAMiSy2RjYvmia9mx+n/K+k8rNrSs8PhaJyJ+HoAVt70VZVs\n"
"+7pk3WKL3wt3MutizCaam7uqYoNMtAZ6MMgpv+0GTZe5HMQxK9VfvFMSF5yZVylmd2EhMQcuJUmd\n"
"GPLu8ytxjLW6OQdJd/zvLpKQBY0tL3d770O/Nbua2Plzpyzy0FfuKE4mX4+QaAkvuPjcBukumj5R\n"
"p9EixAqnOEhss/n/fauGV+O61oV4d7pD6kh/9ti+I20ev9E2bFhc8e6kGVQa9QPSdubhjL08s9NI\n"
"S+LI+H+SqHZGnEJlPqQewQcDWkYtuJfzt9WyVSHvutxMAJf7FJUnM7/oQ0dG0giZFmA7mn7S5u04\n"
"6uwBHjxIVkkJx0w3AJ6IDsBz4W9m6XJHMD4Q5QsDyZpCAGzFlH5hxIrff4IaC1nEWTJ3s7xgaVY5\n"
"/bQGeyzWZDbZvUjthB9+pSKPKrhC9IK31FOQeE4tGv2Bb0TXOwF0lkLgAOIua+rF7nKsu7/+6qqo\n"
"+Nz2snmKtmcCAwEAAaNCMEAwHQYDVR0OBBYEFJ3AZ6YMItkm9UWrpmVSESfYRaxjMA8GA1UdEwEB\n"
"/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3DQEBDAUAA4ICAQCzV00QYk465KzquByv\n"
"MiPIs0laUZx2KI15qldGF9X1Uva3ROgIRL8YhNILgM3FEv0AVQVhh0HctSSePMTYyPtwni94loMg\n"
"Nt58D2kTiKV1NpgIpsbfrM7jWNa3Pt668+s0QNiigfV4Py/VpfzZotReBA4Xrf5B8OWycvpEgjNC\n"
"6C1Y91aMYj+6QrCcDFx+LmUmXFNPALJ4fqENmS2NuB2OosSw/WDQMKSOyARiqcTtNd56l+0OOF6S\n"
"L5Nwpamcb6d9Ex1+xghIsV5n61EIJenmJWtSKZGc0jlzCFfemQa0W50QBuHCAKi4HEoCChTQwUHK\n"
"+4w1IX2COPKpVJEZNZOUbWo6xbLQu4mGk+ibyQ86p3q4ofB4Rvr8Ny/lioTz3/4E2aFooC8k4gmV\n"
"BtWVyuEklut89pMFu+1z6S3RdTnX5yTb2E5fQ4+e0BQ5v1VwSJlXMbSc7kqYA5YwH2AG7hsj/oFg\n"
"IxpHYoWlzBk0gG+zrBrjn/B7SK3VAdlntqlyk+otZrWyuOQ9PLLvTIzq6we/qzWaVYa8GKa1qF60\n"
"g2xraUDTn9zxw2lrueFtCfTxqlB2Cnp9ehehVZZCmTEJ3WARjQUwfuaORtGdFNrHF+QFlozEJLUb\n"
"zxQHskD4o55BhrwE0GuWyCqANP2/7waj3VjFhT0+j/6eKeC2uAloGRwYQw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"AffirmTrust Premium ECC\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIB/jCCAYWgAwIBAgIIdJclisc/elQwCgYIKoZIzj0EAwMwRTELMAkGA1UEBhMCVVMxFDASBgNV\n"
"BAoMC0FmZmlybVRydXN0MSAwHgYDVQQDDBdBZmZpcm1UcnVzdCBQcmVtaXVtIEVDQzAeFw0xMDAx\n"
"MjkxNDIwMjRaFw00MDEyMzExNDIwMjRaMEUxCzAJBgNVBAYTAlVTMRQwEgYDVQQKDAtBZmZpcm1U\n"
"cnVzdDEgMB4GA1UEAwwXQWZmaXJtVHJ1c3QgUHJlbWl1bSBFQ0MwdjAQBgcqhkjOPQIBBgUrgQQA\n"
"IgNiAAQNMF4bFZ0D0KF5Nbc6PJJ6yhUczWLznCZcBz3lVPqj1swS6vQUX+iOGasvLkjmrBhDeKzQ\n"
"N8O9ss0s5kfiGuZjuD0uL3jET9v0D6RoTFVya5UdThhClXjMNzyR4ptlKymjQjBAMB0GA1UdDgQW\n"
"BBSaryl6wBE1NSZRMADDav5A1a7WPDAPBgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBBjAK\n"
"BggqhkjOPQQDAwNnADBkAjAXCfOHiFBar8jAQr9HX/VsaobgxCd05DhT1wV/GzTjxi+zygk8N53X\n"
"57hG8f2h4nECMEJZh0PUUd+60wkyWs6Iflc9nF9Ca/UHLbXwgpP5WW+uZPpY5Yse42O+tYHNbwKM\n"
"eQ==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Certum Trusted Network CA\n"
"=========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDuzCCAqOgAwIBAgIDBETAMA0GCSqGSIb3DQEBBQUAMH4xCzAJBgNVBAYTAlBMMSIwIAYDVQQK\n"
"ExlVbml6ZXRvIFRlY2hub2xvZ2llcyBTLkEuMScwJQYDVQQLEx5DZXJ0dW0gQ2VydGlmaWNhdGlv\n"
"biBBdXRob3JpdHkxIjAgBgNVBAMTGUNlcnR1bSBUcnVzdGVkIE5ldHdvcmsgQ0EwHhcNMDgxMDIy\n"
"MTIwNzM3WhcNMjkxMjMxMTIwNzM3WjB+MQswCQYDVQQGEwJQTDEiMCAGA1UEChMZVW5pemV0byBU\n"
"ZWNobm9sb2dpZXMgUy5BLjEnMCUGA1UECxMeQ2VydHVtIENlcnRpZmljYXRpb24gQXV0aG9yaXR5\n"
"MSIwIAYDVQQDExlDZXJ0dW0gVHJ1c3RlZCBOZXR3b3JrIENBMIIBIjANBgkqhkiG9w0BAQEFAAOC\n"
"AQ8AMIIBCgKCAQEA4/t9o3K6wvDJFIf1awFO4W5AB7ptJ11/91sts1rHUV+rpDKmYYe2bg+G0jAC\n"
"l/jXaVehGDldamR5xgFZrDwxSjh80gTSSyjoIF87B6LMTXPb865Px1bVWqeWifrzq2jUI4ZZJ88J\n"
"J7ysbnKDHDBy3+Ci6dLhdHUZvSqeexVUBBvXQzmtVSjF4hq79MDkrjhJM8x2hZ85RdKknvISjFH4\n"
"fOQtf/WsX+sWn7Et0brMkUJ3TCXJkDhv2/DM+44el1k+1WBO5gUo7Ul5E0u6SNsv+XLTOcr+H9g0\n"
"cvW0QM8xAcPs3hEtF10fuFDRXhmnad4HMyjKUJX5p1TLVIZQRan5SQIDAQABo0IwQDAPBgNVHRMB\n"
"Af8EBTADAQH/MB0GA1UdDgQWBBQIds3LB/8k9sXN7buQvOKEN0Z19zAOBgNVHQ8BAf8EBAMCAQYw\n"
"DQYJKoZIhvcNAQEFBQADggEBAKaorSLOAT2mo/9i0Eidi15ysHhE49wcrwn9I0j6vSrEuVUEtRCj\n"
"jSfeC4Jj0O7eDDd5QVsisrCaQVymcODU0HfLI9MA4GxWL+FpDQ3Zqr8hgVDZBqWo/5U30Kr+4rP1\n"
"mS1FhIrlQgnXdAIv94nYmem8J9RHjboNRhx3zxSkHLmkMcScKHQDNP8zGSal6Q10tz6XxnboJ5aj\n"
"Zt3hrvJBW8qYVoNzcOSGGtIxQbovvi0TWnZvTuhOgQ4/WwMioBK+ZlgRSssDxLQqKi2WF+A5VLxI\n"
"03YnnZotBqbJ7DnSq9ufmgsnAjUpsUCV5/nonFWIGUbWtzT1fs45mtk48VH3Tyw=\n"
"-----END CERTIFICATE-----\n"
"\n"
"TWCA Root Certification Authority\n"
"=================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDezCCAmOgAwIBAgIBATANBgkqhkiG9w0BAQUFADBfMQswCQYDVQQGEwJUVzESMBAGA1UECgwJ\n"
"VEFJV0FOLUNBMRAwDgYDVQQLDAdSb290IENBMSowKAYDVQQDDCFUV0NBIFJvb3QgQ2VydGlmaWNh\n"
"dGlvbiBBdXRob3JpdHkwHhcNMDgwODI4MDcyNDMzWhcNMzAxMjMxMTU1OTU5WjBfMQswCQYDVQQG\n"
"EwJUVzESMBAGA1UECgwJVEFJV0FOLUNBMRAwDgYDVQQLDAdSb290IENBMSowKAYDVQQDDCFUV0NB\n"
"IFJvb3QgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n"
"AoIBAQCwfnK4pAOU5qfeCTiRShFAh6d8WWQUe7UREN3+v9XAu1bihSX0NXIP+FPQQeFEAcK0HMMx\n"
"QhZHhTMidrIKbw/lJVBPhYa+v5guEGcevhEFhgWQxFnQfHgQsIBct+HHK3XLfJ+utdGdIzdjp9xC\n"
"oi2SBBtQwXu4PhvJVgSLL1KbralW6cH/ralYhzC2gfeXRfwZVzsrb+RH9JlF/h3x+JejiB03HFyP\n"
"4HYlmlD4oFT/RJB2I9IyxsOrBr/8+7/zrX2SYgJbKdM1o5OaQ2RgXbL6Mv87BK9NQGr5x+PvI/1r\n"
"y+UPizgN7gr8/g+YnzAx3WxSZfmLgb4i4RxYA7qRG4kHAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIB\n"
"BjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBRqOFsmjd6LWvJPelSDGRjjCDWmujANBgkqhkiG\n"
"9w0BAQUFAAOCAQEAPNV3PdrfibqHDAhUaiBQkr6wQT25JmSDCi/oQMCXKCeCMErJk/9q56YAf4lC\n"
"mtYR5VPOL8zy2gXE/uJQxDqGfczafhAJO5I1KlOy/usrBdlsXebQ79NqZp4VKIV66IIArB6nCWlW\n"
"QtNoURi+VJq/REG6Sb4gumlc7rh3zc5sH62Dlhh9DrUUOYTxKOkto557HnpyWoOzeW/vtPzQCqVY\n"
"T0bf+215WfKEIlKuD8z7fDvnaspHYcN6+NOSBB+4IIThNlQWx0DeO4pz3N/GCUzf7Nr/1FNCocny\n"
"Yh0igzyXxfkZYiesZSLX0zzG5Y6yU8xJzrww/nsOM5D77dIUkR8Hrw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Security Communication RootCA2\n"
"==============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDdzCCAl+gAwIBAgIBADANBgkqhkiG9w0BAQsFADBdMQswCQYDVQQGEwJKUDElMCMGA1UEChMc\n"
"U0VDT00gVHJ1c3QgU3lzdGVtcyBDTy4sTFRELjEnMCUGA1UECxMeU2VjdXJpdHkgQ29tbXVuaWNh\n"
"dGlvbiBSb290Q0EyMB4XDTA5MDUyOTA1MDAzOVoXDTI5MDUyOTA1MDAzOVowXTELMAkGA1UEBhMC\n"
"SlAxJTAjBgNVBAoTHFNFQ09NIFRydXN0IFN5c3RlbXMgQ08uLExURC4xJzAlBgNVBAsTHlNlY3Vy\n"
"aXR5IENvbW11bmljYXRpb24gUm9vdENBMjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"
"ANAVOVKxUrO6xVmCxF1SrjpDZYBLx/KWvNs2l9amZIyoXvDjChz335c9S672XewhtUGrzbl+dp++\n"
"+T42NKA7wfYxEUV0kz1XgMX5iZnK5atq1LXaQZAQwdbWQonCv/Q4EpVMVAX3NuRFg3sUZdbcDE3R\n"
"3n4MqzvEFb46VqZab3ZpUql6ucjrappdUtAtCms1FgkQhNBqyjoGADdH5H5XTz+L62e4iKrFvlNV\n"
"spHEfbmwhRkGeC7bYRr6hfVKkaHnFtWOojnflLhwHyg/i/xAXmODPIMqGplrz95Zajv8bxbXH/1K\n"
"EOtOghY6rCcMU/Gt1SSwawNQwS08Ft1ENCcadfsCAwEAAaNCMEAwHQYDVR0OBBYEFAqFqXdlBZh8\n"
"QIH4D5csOPEK7DzPMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEB\n"
"CwUAA4IBAQBMOqNErLlFsceTfsgLCkLfZOoc7llsCLqJX2rKSpWeeo8HxdpFcoJxDjrSzG+ntKEj\n"
"u/Ykn8sX/oymzsLS28yN/HH8AynBbF0zX2S2ZTuJbxh2ePXcokgfGT+Ok+vx+hfuzU7jBBJV1uXk\n"
"3fs+BXziHV7Gp7yXT2g69ekuCkO2r1dcYmh8t/2jioSgrGK+KwmHNPBqAbubKVY8/gA3zyNs8U6q\n"
"tnRGEmyR7jTV7JqR50S+kDFy1UkC9gLl9B/rfNmWVan/7Ir5mUf/NVoCqgTLiluHcSmRvaS0eg29\n"
"mvVXIwAHIRc/SjnRBUkLp7Y3gaVdjKozXoEofKd9J+sAro03\n"
"-----END CERTIFICATE-----\n"
"\n"
"EC-ACC\n"
"======\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFVjCCBD6gAwIBAgIQ7is969Qh3hSoYqwE893EATANBgkqhkiG9w0BAQUFADCB8zELMAkGA1UE\n"
"BhMCRVMxOzA5BgNVBAoTMkFnZW5jaWEgQ2F0YWxhbmEgZGUgQ2VydGlmaWNhY2lvIChOSUYgUS0w\n"
"ODAxMTc2LUkpMSgwJgYDVQQLEx9TZXJ2ZWlzIFB1YmxpY3MgZGUgQ2VydGlmaWNhY2lvMTUwMwYD\n"
"VQQLEyxWZWdldSBodHRwczovL3d3dy5jYXRjZXJ0Lm5ldC92ZXJhcnJlbCAoYykwMzE1MDMGA1UE\n"
"CxMsSmVyYXJxdWlhIEVudGl0YXRzIGRlIENlcnRpZmljYWNpbyBDYXRhbGFuZXMxDzANBgNVBAMT\n"
"BkVDLUFDQzAeFw0wMzAxMDcyMzAwMDBaFw0zMTAxMDcyMjU5NTlaMIHzMQswCQYDVQQGEwJFUzE7\n"
"MDkGA1UEChMyQWdlbmNpYSBDYXRhbGFuYSBkZSBDZXJ0aWZpY2FjaW8gKE5JRiBRLTA4MDExNzYt\n"
"SSkxKDAmBgNVBAsTH1NlcnZlaXMgUHVibGljcyBkZSBDZXJ0aWZpY2FjaW8xNTAzBgNVBAsTLFZl\n"
"Z2V1IGh0dHBzOi8vd3d3LmNhdGNlcnQubmV0L3ZlcmFycmVsIChjKTAzMTUwMwYDVQQLEyxKZXJh\n"
"cnF1aWEgRW50aXRhdHMgZGUgQ2VydGlmaWNhY2lvIENhdGFsYW5lczEPMA0GA1UEAxMGRUMtQUND\n"
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAsyLHT+KXQpWIR4NA9h0X84NzJB5R85iK\n"
"w5K4/0CQBXCHYMkAqbWUZRkiFRfCQ2xmRJoNBD45b6VLeqpjt4pEndljkYRm4CgPukLjbo73FCeT\n"
"ae6RDqNfDrHrZqJyTxIThmV6PttPB/SnCWDaOkKZx7J/sxaVHMf5NLWUhdWZXqBIoH7nF2W4onW4\n"
"HvPlQn2v7fOKSGRdghST2MDk/7NQcvJ29rNdQlB50JQ+awwAvthrDk4q7D7SzIKiGGUzE3eeml0a\n"
"E9jD2z3Il3rucO2n5nzbcc8tlGLfbdb1OL4/pYUKGbio2Al1QnDE6u/LDsg0qBIimAy4E5S2S+zw\n"
"0JDnJwIDAQABo4HjMIHgMB0GA1UdEQQWMBSBEmVjX2FjY0BjYXRjZXJ0Lm5ldDAPBgNVHRMBAf8E\n"
"BTADAQH/MA4GA1UdDwEB/wQEAwIBBjAdBgNVHQ4EFgQUoMOLRKo3pUW/l4Ba0fF4opvpXY0wfwYD\n"
"VR0gBHgwdjB0BgsrBgEEAfV4AQMBCjBlMCwGCCsGAQUFBwIBFiBodHRwczovL3d3dy5jYXRjZXJ0\n"
"Lm5ldC92ZXJhcnJlbDA1BggrBgEFBQcCAjApGidWZWdldSBodHRwczovL3d3dy5jYXRjZXJ0Lm5l\n"
"dC92ZXJhcnJlbCAwDQYJKoZIhvcNAQEFBQADggEBAKBIW4IB9k1IuDlVNZyAelOZ1Vr/sXE7zDkJ\n"
"lF7W2u++AVtd0x7Y/X1PzaBB4DSTv8vihpw3kpBWHNzrKQXlxJ7HNd+KDM3FIUPpqojlNcAZQmNa\n"
"Al6kSBg6hW/cnbw/nZzBh7h6YQjpdwt/cKt63dmXLGQehb+8dJahw3oS7AwaboMMPOhyRp/7SNVe\n"
"l+axofjk70YllJyJ22k4vuxcDlbHZVHlUIiIv0LVKz3l+bqeLrPK9HOSAgu+TGbrIP65y7WZf+a2\n"
"E/rKS03Z7lNGBjvGTq2TWoF+bCpLagVFjPIhpDGQh2xlnJ2lYJU6Un/10asIbvPuW/mIPX64b24D\n"
"5EI=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Hellenic Academic and Research Institutions RootCA 2011\n"
"=======================================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEMTCCAxmgAwIBAgIBADANBgkqhkiG9w0BAQUFADCBlTELMAkGA1UEBhMCR1IxRDBCBgNVBAoT\n"
"O0hlbGxlbmljIEFjYWRlbWljIGFuZCBSZXNlYXJjaCBJbnN0aXR1dGlvbnMgQ2VydC4gQXV0aG9y\n"
"aXR5MUAwPgYDVQQDEzdIZWxsZW5pYyBBY2FkZW1pYyBhbmQgUmVzZWFyY2ggSW5zdGl0dXRpb25z\n"
"IFJvb3RDQSAyMDExMB4XDTExMTIwNjEzNDk1MloXDTMxMTIwMTEzNDk1MlowgZUxCzAJBgNVBAYT\n"
"AkdSMUQwQgYDVQQKEztIZWxsZW5pYyBBY2FkZW1pYyBhbmQgUmVzZWFyY2ggSW5zdGl0dXRpb25z\n"
"IENlcnQuIEF1dGhvcml0eTFAMD4GA1UEAxM3SGVsbGVuaWMgQWNhZGVtaWMgYW5kIFJlc2VhcmNo\n"
"IEluc3RpdHV0aW9ucyBSb290Q0EgMjAxMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"
"AKlTAOMupvaO+mDYLZU++CwqVE7NuYRhlFhPjz2L5EPzdYmNUeTDN9KKiE15HrcS3UN4SoqS5tdI\n"
"1Q+kOilENbgH9mgdVc04UfCMJDGFr4PJfel3r+0ae50X+bOdOFAPplp5kYCvN66m0zH7tSYJnTxa\n"
"71HFK9+WXesyHgLacEnsbgzImjeN9/E2YEsmLIKe0HjzDQ9jpFEw4fkrJxIH2Oq9GGKYsFk3fb7u\n"
"8yBRQlqD75O6aRXxYp2fmTmCobd0LovUxQt7L/DICto9eQqakxylKHJzkUOap9FNhYS5qXSPFEDH\n"
"3N6sQWRstBmbAmNtJGSPRLIl6s5ddAxjMlyNh+UCAwEAAaOBiTCBhjAPBgNVHRMBAf8EBTADAQH/\n"
"MAsGA1UdDwQEAwIBBjAdBgNVHQ4EFgQUppFC/RNhSiOeCKQp5dgTBCPuQSUwRwYDVR0eBEAwPqA8\n"
"MAWCAy5ncjAFggMuZXUwBoIELmVkdTAGggQub3JnMAWBAy5ncjAFgQMuZXUwBoEELmVkdTAGgQQu\n"
"b3JnMA0GCSqGSIb3DQEBBQUAA4IBAQAf73lB4XtuP7KMhjdCSk4cNx6NZrokgclPEg8hwAOXhiVt\n"
"XdMiKahsog2p6z0GW5k6x8zDmjR/qw7IThzh+uTczQ2+vyT+bOdrwg3IBp5OjWEopmr95fZi6hg8\n"
"TqBTnbI6nOulnJEWtk2C4AwFSKls9cz4y51JtPACpf1wA+2KIaWuE4ZJwzNzvoc7dIsXRSZMFpGD\n"
"/md9zU1jZ/rzAxKWeAaNsWftjj++n08C9bMJL/NMh98qy5V8AcysNnq/onN694/BtZqhFLKPM58N\n"
"7yLcZnuEvUUXBj08yrl3NI/K6s8/MT7jiOOASSXIl7WdmplNsDz4SgCbZN2fOUvRJ9e4\n"
"-----END CERTIFICATE-----\n"
"\n"
"Actalis Authentication Root CA\n"
"==============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFuzCCA6OgAwIBAgIIVwoRl0LE48wwDQYJKoZIhvcNAQELBQAwazELMAkGA1UEBhMCSVQxDjAM\n"
"BgNVBAcMBU1pbGFuMSMwIQYDVQQKDBpBY3RhbGlzIFMucC5BLi8wMzM1ODUyMDk2NzEnMCUGA1UE\n"
"AwweQWN0YWxpcyBBdXRoZW50aWNhdGlvbiBSb290IENBMB4XDTExMDkyMjExMjIwMloXDTMwMDky\n"
"MjExMjIwMlowazELMAkGA1UEBhMCSVQxDjAMBgNVBAcMBU1pbGFuMSMwIQYDVQQKDBpBY3RhbGlz\n"
"IFMucC5BLi8wMzM1ODUyMDk2NzEnMCUGA1UEAwweQWN0YWxpcyBBdXRoZW50aWNhdGlvbiBSb290\n"
"IENBMIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAp8bEpSmkLO/lGMWwUKNvUTufClrJ\n"
"wkg4CsIcoBh/kbWHuUA/3R1oHwiD1S0eiKD4j1aPbZkCkpAW1V8IbInX4ay8IMKx4INRimlNAJZa\n"
"by/ARH6jDuSRzVju3PvHHkVH3Se5CAGfpiEd9UEtL0z9KK3giq0itFZljoZUj5NDKd45RnijMCO6\n"
"zfB9E1fAXdKDa0hMxKufgFpbOr3JpyI/gCczWw63igxdBzcIy2zSekciRDXFzMwujt0q7bd9Zg1f\n"
"YVEiVRvjRuPjPdA1YprbrxTIW6HMiRvhMCb8oJsfgadHHwTrozmSBp+Z07/T6k9QnBn+locePGX2\n"
"oxgkg4YQ51Q+qDp2JE+BIcXjDwL4k5RHILv+1A7TaLndxHqEguNTVHnd25zS8gebLra8Pu2Fbe8l\n"
"EfKXGkJh90qX6IuxEAf6ZYGyojnP9zz/GPvG8VqLWeICrHuS0E4UT1lF9gxeKF+w6D9Fz8+vm2/7\n"
"hNN3WpVvrJSEnu68wEqPSpP4RCHiMUVhUE4Q2OM1fEwZtN4Fv6MGn8i1zeQf1xcGDXqVdFUNaBr8\n"
"EBtiZJ1t4JWgw5QHVw0U5r0F+7if5t+L4sbnfpb2U8WANFAoWPASUHEXMLrmeGO89LKtmyuy/uE5\n"
"jF66CyCU3nuDuP/jVo23Eek7jPKxwV2dpAtMK9myGPW1n0sCAwEAAaNjMGEwHQYDVR0OBBYEFFLY\n"
"iDrIn3hm7YnzezhwlMkCAjbQMA8GA1UdEwEB/wQFMAMBAf8wHwYDVR0jBBgwFoAUUtiIOsifeGbt\n"
"ifN7OHCUyQICNtAwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3DQEBCwUAA4ICAQALe3KHwGCmSUyI\n"
"WOYdiPcUZEim2FgKDk8TNd81HdTtBjHIgT5q1d07GjLukD0R0i70jsNjLiNmsGe+b7bAEzlgqqI0\n"
"JZN1Ut6nna0Oh4lScWoWPBkdg/iaKWW+9D+a2fDzWochcYBNy+A4mz+7+uAwTc+G02UQGRjRlwKx\n"
"K3JCaKygvU5a2hi/a5iB0P2avl4VSM0RFbnAKVy06Ij3Pjaut2L9HmLecHgQHEhb2rykOLpn7VU+\n"
"Xlff1ANATIGk0k9jpwlCCRT8AKnCgHNPLsBA2RF7SOp6AsDT6ygBJlh0wcBzIm2Tlf05fbsq4/aC\n"
"4yyXX04fkZT6/iyj2HYauE2yOE+b+h1IYHkm4vP9qdCa6HCPSXrW5b0KDtst842/6+OkfcvHlXHo\n"
"2qN8xcL4dJIEG4aspCJTQLas/kx2z/uUMsA1n3Y/buWQbqCmJqK4LL7RK4X9p2jIugErsWx0Hbhz\n"
"lefut8cl8ABMALJ+tguLHPPAUJ4lueAI3jZm/zel0btUZCzJJ7VLkn5l/9Mt4blOvH+kQSGQQXem\n"
"OR/qnuOf0GZvBeyqdn6/axag67XH/JJULysRJyU3eExRarDzzFhdFPFqSBX/wge2sY0PjlxQRrM9\n"
"vwGYT7JZVEc+NHt4bVaTLnPqZih4zR0Uv6CPLy64Lo7yFIrM6bV8+2ydDKXhlg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Buypass Class 2 Root CA\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFWTCCA0GgAwIBAgIBAjANBgkqhkiG9w0BAQsFADBOMQswCQYDVQQGEwJOTzEdMBsGA1UECgwU\n"
"QnV5cGFzcyBBUy05ODMxNjMzMjcxIDAeBgNVBAMMF0J1eXBhc3MgQ2xhc3MgMiBSb290IENBMB4X\n"
"DTEwMTAyNjA4MzgwM1oXDTQwMTAyNjA4MzgwM1owTjELMAkGA1UEBhMCTk8xHTAbBgNVBAoMFEJ1\n"
"eXBhc3MgQVMtOTgzMTYzMzI3MSAwHgYDVQQDDBdCdXlwYXNzIENsYXNzIDIgUm9vdCBDQTCCAiIw\n"
"DQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBANfHXvfBB9R3+0Mh9PT1aeTuMgHbo4Yf5FkNuud1\n"
"g1Lr6hxhFUi7HQfKjK6w3Jad6sNgkoaCKHOcVgb/S2TwDCo3SbXlzwx87vFKu3MwZfPVL4O2fuPn\n"
"9Z6rYPnT8Z2SdIrkHJasW4DptfQxh6NR/Md+oW+OU3fUl8FVM5I+GC911K2GScuVr1QGbNgGE41b\n"
"/+EmGVnAJLqBcXmQRFBoJJRfuLMR8SlBYaNByyM21cHxMlAQTn/0hpPshNOOvEu/XAFOBz3cFIqU\n"
"CqTqc/sLUegTBxj6DvEr0VQVfTzh97QZQmdiXnfgolXsttlpF9U6r0TtSsWe5HonfOV116rLJeff\n"
"awrbD02TTqigzXsu8lkBarcNuAeBfos4GzjmCleZPe4h6KP1DBbdi+w0jpwqHAAVF41og9JwnxgI\n"
"zRFo1clrUs3ERo/ctfPYV3Me6ZQ5BL/T3jjetFPsaRyifsSP5BtwrfKi+fv3FmRmaZ9JUaLiFRhn\n"
"Bkp/1Wy1TbMz4GHrXb7pmA8y1x1LPC5aAVKRCfLf6o3YBkBjqhHk/sM3nhRSP/TizPJhk9H9Z2vX\n"
"Uq6/aKtAQ6BXNVN48FP4YUIHZMbXb5tMOA1jrGKvNouicwoN9SG9dKpN6nIDSdvHXx1iY8f93ZHs\n"
"M+71bbRuMGjeyNYmsHVee7QHIJihdjK4TWxPAgMBAAGjQjBAMA8GA1UdEwEB/wQFMAMBAf8wHQYD\n"
"VR0OBBYEFMmAd+BikoL1RpzzuvdMw964o605MA4GA1UdDwEB/wQEAwIBBjANBgkqhkiG9w0BAQsF\n"
"AAOCAgEAU18h9bqwOlI5LJKwbADJ784g7wbylp7ppHR/ehb8t/W2+xUbP6umwHJdELFx7rxP462s\n"
"A20ucS6vxOOto70MEae0/0qyexAQH6dXQbLArvQsWdZHEIjzIVEpMMpghq9Gqx3tOluwlN5E40EI\n"
"osHsHdb9T7bWR9AUC8rmyrV7d35BH16Dx7aMOZawP5aBQW9gkOLo+fsicdl9sz1Gv7SEr5AcD48S\n"
"aq/v7h56rgJKihcrdv6sVIkkLE8/trKnToyokZf7KcZ7XC25y2a2t6hbElGFtQl+Ynhw/qlqYLYd\n"
"DnkM/crqJIByw5c/8nerQyIKx+u2DISCLIBrQYoIwOula9+ZEsuK1V6ADJHgJgg2SMX6OBE1/yWD\n"
"LfJ6v9r9jv6ly0UsH8SIU653DtmadsWOLB2jutXsMq7Aqqz30XpN69QH4kj3Io6wpJ9qzo6ysmD0\n"
"oyLQI+uUWnpp3Q+/QFesa1lQ2aOZ4W7+jQF5JyMV3pKdewlNWudLSDBaGOYKbeaP4NK75t98biGC\n"
"wWg5TbSYWGZizEqQXsP6JwSxeRV0mcy+rSDeJmAc61ZRpqPq5KM/p/9h3PFaTWwyI0PurKju7koS\n"
"CTxdccK+efrCh2gdC/1cacwG0Jp9VJkqyTkaGa9LKkPzY11aWOIv4x3kqdbQCtCev9eBCfHJxyYN\n"
"rJgWVqA=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Buypass Class 3 Root CA\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFWTCCA0GgAwIBAgIBAjANBgkqhkiG9w0BAQsFADBOMQswCQYDVQQGEwJOTzEdMBsGA1UECgwU\n"
"QnV5cGFzcyBBUy05ODMxNjMzMjcxIDAeBgNVBAMMF0J1eXBhc3MgQ2xhc3MgMyBSb290IENBMB4X\n"
"DTEwMTAyNjA4Mjg1OFoXDTQwMTAyNjA4Mjg1OFowTjELMAkGA1UEBhMCTk8xHTAbBgNVBAoMFEJ1\n"
"eXBhc3MgQVMtOTgzMTYzMzI3MSAwHgYDVQQDDBdCdXlwYXNzIENsYXNzIDMgUm9vdCBDQTCCAiIw\n"
"DQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAKXaCpUWUOOV8l6ddjEGMnqb8RB2uACatVI2zSRH\n"
"sJ8YZLya9vrVediQYkwiL944PdbgqOkcLNt4EemOaFEVcsfzM4fkoF0LXOBXByow9c3EN3coTRiR\n"
"5r/VUv1xLXA+58bEiuPwKAv0dpihi4dVsjoT/Lc+JzeOIuOoTyrvYLs9tznDDgFHmV0ST9tD+leh\n"
"7fmdvhFHJlsTmKtdFoqwNxxXnUX/iJY2v7vKB3tvh2PX0DJq1l1sDPGzbjniazEuOQAnFN44wOwZ\n"
"ZoYS6J1yFhNkUsepNxz9gjDthBgd9K5c/3ATAOux9TN6S9ZV+AWNS2mw9bMoNlwUxFFzTWsL8TQH\n"
"2xc519woe2v1n/MuwU8XKhDzzMro6/1rqy6any2CbgTUUgGTLT2G/H783+9CHaZr77kgxve9oKeV\n"
"/afmiSTYzIw0bOIjL9kSGiG5VZFvC5F5GQytQIgLcOJ60g7YaEi7ghM5EFjp2CoHxhLbWNvSO1UQ\n"
"RwUVZ2J+GGOmRj8JDlQyXr8NYnon74Do29lLBlo3WiXQCBJ31G8JUJc9yB3D34xFMFbG02SrZvPA\n"
"Xpacw8Tvw3xrizp5f7NJzz3iiZ+gMEuFuZyUJHmPfWupRWgPK9Dx2hzLabjKSWJtyNBjYt1gD1iq\n"
"j6G8BaVmos8bdrKEZLFMOVLAMLrwjEsCsLa3AgMBAAGjQjBAMA8GA1UdEwEB/wQFMAMBAf8wHQYD\n"
"VR0OBBYEFEe4zf/lb+74suwvTg75JbCOPGvDMA4GA1UdDwEB/wQEAwIBBjANBgkqhkiG9w0BAQsF\n"
"AAOCAgEAACAjQTUEkMJAYmDv4jVM1z+s4jSQuKFvdvoWFqRINyzpkMLyPPgKn9iB5btb2iUspKdV\n"
"cSQy9sgL8rxq+JOssgfCX5/bzMiKqr5qb+FJEMwx14C7u8jYog5kV+qi9cKpMRXSIGrs/CIBKM+G\n"
"uIAeqcwRpTzyFrNHnfzSgCHEy9BHcEGhyoMZCCxt8l13nIoUE9Q2HJLw5QY33KbmkJs4j1xrG0aG\n"
"Q0JfPgEHU1RdZX33inOhmlRaHylDFCfChQ+1iHsaO5S3HWCntZznKWlXWpuTekMwGwPXYshApqr8\n"
"ZORK15FTAaggiG6cX0S5y2CBNOxv033aSF/rtJC8LakcC6wc1aJoIIAE1vyxjy+7SjENSoYc6+I2\n"
"KSb12tjE8nVhz36udmNKekBlk4f4HoCMhuWG1o8O/FMsYOgWYRqiPkN7zTlgVGr18okmAWiDSKIz\n"
"6MkEkbIRNBE+6tBDGR8Dk5AM/1E9V/RBbuHLoL7ryWPNbczk+DaqaJ3tvV2XcEQNtg413OEMXbug\n"
"UZTLfhbrES+jkkXITHHZvMmZUldGL1DPvTVp9D0VzgalLA8+9oG6lLvDu79leNKGef9JOxqDDPDe\n"
"eOzI8k1MGt6CKfjBWtrt7uYnXuhF0J0cUahoq0Tj0Itq4/g7u9xN12TyUb7mqqta6THuBrxzvxNi\n"
"Cp/HuZc=\n"
"-----END CERTIFICATE-----\n"
"\n"
"T-TeleSec GlobalRoot Class 3\n"
"============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDwzCCAqugAwIBAgIBATANBgkqhkiG9w0BAQsFADCBgjELMAkGA1UEBhMCREUxKzApBgNVBAoM\n"
"IlQtU3lzdGVtcyBFbnRlcnByaXNlIFNlcnZpY2VzIEdtYkgxHzAdBgNVBAsMFlQtU3lzdGVtcyBU\n"
"cnVzdCBDZW50ZXIxJTAjBgNVBAMMHFQtVGVsZVNlYyBHbG9iYWxSb290IENsYXNzIDMwHhcNMDgx\n"
"MDAxMTAyOTU2WhcNMzMxMDAxMjM1OTU5WjCBgjELMAkGA1UEBhMCREUxKzApBgNVBAoMIlQtU3lz\n"
"dGVtcyBFbnRlcnByaXNlIFNlcnZpY2VzIEdtYkgxHzAdBgNVBAsMFlQtU3lzdGVtcyBUcnVzdCBD\n"
"ZW50ZXIxJTAjBgNVBAMMHFQtVGVsZVNlYyBHbG9iYWxSb290IENsYXNzIDMwggEiMA0GCSqGSIb3\n"
"DQEBAQUAA4IBDwAwggEKAoIBAQC9dZPwYiJvJK7genasfb3ZJNW4t/zN8ELg63iIVl6bmlQdTQyK\n"
"9tPPcPRStdiTBONGhnFBSivwKixVA9ZIw+A5OO3yXDw/RLyTPWGrTs0NvvAgJ1gORH8EGoel15YU\n"
"NpDQSXuhdfsaa3Ox+M6pCSzyU9XDFES4hqX2iys52qMzVNn6chr3IhUciJFrf2blw2qAsCTz34ZF\n"
"iP0Zf3WHHx+xGwpzJFu5ZeAsVMhg02YXP+HMVDNzkQI6pn97djmiH5a2OK61yJN0HZ65tOVgnS9W\n"
"0eDrXltMEnAMbEQgqxHY9Bn20pxSN+f6tsIxO0rUFJmtxxr1XV/6B7h8DR/Wgx6zAgMBAAGjQjBA\n"
"MA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgEGMB0GA1UdDgQWBBS1A/d2O2GCahKqGFPr\n"
"AyGUv/7OyjANBgkqhkiG9w0BAQsFAAOCAQEAVj3vlNW92nOyWL6ukK2YJ5f+AbGwUgC4TeQbIXQb\n"
"fsDuXmkqJa9c1h3a0nnJ85cp4IaH3gRZD/FZ1GSFS5mvJQQeyUapl96Cshtwn5z2r3Ex3XsFpSzT\n"
"ucpH9sry9uetuUg/vBa3wW306gmv7PO15wWeph6KU1HWk4HMdJP2udqmJQV0eVp+QD6CSyYRMG7h\n"
"P0HHRwA11fXT91Q+gT3aSWqas+8QPebrb9HIIkfLzM8BMZLZGOMivgkeGj5asuRrDFR6fUNOuIml\n"
"e9eiPZaGzPImNC1qkp2aGtAw4l1OBLBfiyB+d8E9lYLRRpo7PHi4b6HQDWSieB4pTpPDpFQUWw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"D-TRUST Root Class 3 CA 2 2009\n"
"==============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEMzCCAxugAwIBAgIDCYPzMA0GCSqGSIb3DQEBCwUAME0xCzAJBgNVBAYTAkRFMRUwEwYDVQQK\n"
"DAxELVRydXN0IEdtYkgxJzAlBgNVBAMMHkQtVFJVU1QgUm9vdCBDbGFzcyAzIENBIDIgMjAwOTAe\n"
"Fw0wOTExMDUwODM1NThaFw0yOTExMDUwODM1NThaME0xCzAJBgNVBAYTAkRFMRUwEwYDVQQKDAxE\n"
"LVRydXN0IEdtYkgxJzAlBgNVBAMMHkQtVFJVU1QgUm9vdCBDbGFzcyAzIENBIDIgMjAwOTCCASIw\n"
"DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANOySs96R+91myP6Oi/WUEWJNTrGa9v+2wBoqOAD\n"
"ER03UAifTUpolDWzU9GUY6cgVq/eUXjsKj3zSEhQPgrfRlWLJ23DEE0NkVJD2IfgXU42tSHKXzlA\n"
"BF9bfsyjxiupQB7ZNoTWSPOSHjRGICTBpFGOShrvUD9pXRl/RcPHAY9RySPocq60vFYJfxLLHLGv\n"
"KZAKyVXMD9O0Gu1HNVpK7ZxzBCHQqr0ME7UAyiZsxGsMlFqVlNpQmvH/pStmMaTJOKDfHR+4CS7z\n"
"p+hnUquVH+BGPtikw8paxTGA6Eian5Rp/hnd2HN8gcqW3o7tszIFZYQ05ub9VxC1X3a/L7AQDcUC\n"
"AwEAAaOCARowggEWMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFP3aFMSfMN4hvR5COfyrYyNJ\n"
"4PGEMA4GA1UdDwEB/wQEAwIBBjCB0wYDVR0fBIHLMIHIMIGAoH6gfIZ6bGRhcDovL2RpcmVjdG9y\n"
"eS5kLXRydXN0Lm5ldC9DTj1ELVRSVVNUJTIwUm9vdCUyMENsYXNzJTIwMyUyMENBJTIwMiUyMDIw\n"
"MDksTz1ELVRydXN0JTIwR21iSCxDPURFP2NlcnRpZmljYXRlcmV2b2NhdGlvbmxpc3QwQ6BBoD+G\n"
"PWh0dHA6Ly93d3cuZC10cnVzdC5uZXQvY3JsL2QtdHJ1c3Rfcm9vdF9jbGFzc18zX2NhXzJfMjAw\n"
"OS5jcmwwDQYJKoZIhvcNAQELBQADggEBAH+X2zDI36ScfSF6gHDOFBJpiBSVYEQBrLLpME+bUMJm\n"
"2H6NMLVwMeniacfzcNsgFYbQDfC+rAF1hM5+n02/t2A7nPPKHeJeaNijnZflQGDSNiH+0LS4F9p0\n"
"o3/U37CYAqxva2ssJSRyoWXuJVrl5jLn8t+rSfrzkGkj2wTZ51xY/GXUl77M/C4KzCUqNQT4YJEV\n"
"dT1B/yMfGchs64JTBKbkTCJNjYy6zltz7GRUUG3RnFX7acM2w4y8PIWmawomDeCTmGCufsYkl4ph\n"
"X5GOZpIJhzbNi5stPvZR1FDUWSi9g/LMKHtThm3YJohw1+qRzT65ysCQblrGXnRl11z+o+I=\n"
"-----END CERTIFICATE-----\n"
"\n"
"D-TRUST Root Class 3 CA 2 EV 2009\n"
"=================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEQzCCAyugAwIBAgIDCYP0MA0GCSqGSIb3DQEBCwUAMFAxCzAJBgNVBAYTAkRFMRUwEwYDVQQK\n"
"DAxELVRydXN0IEdtYkgxKjAoBgNVBAMMIUQtVFJVU1QgUm9vdCBDbGFzcyAzIENBIDIgRVYgMjAw\n"
"OTAeFw0wOTExMDUwODUwNDZaFw0yOTExMDUwODUwNDZaMFAxCzAJBgNVBAYTAkRFMRUwEwYDVQQK\n"
"DAxELVRydXN0IEdtYkgxKjAoBgNVBAMMIUQtVFJVU1QgUm9vdCBDbGFzcyAzIENBIDIgRVYgMjAw\n"
"OTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJnxhDRwui+3MKCOvXwEz75ivJn9gpfS\n"
"egpnljgJ9hBOlSJzmY3aFS3nBfwZcyK3jpgAvDw9rKFs+9Z5JUut8Mxk2og+KbgPCdM03TP1YtHh\n"
"zRnp7hhPTFiu4h7WDFsVWtg6uMQYZB7jM7K1iXdODL/ZlGsTl28So/6ZqQTMFexgaDbtCHu39b+T\n"
"7WYxg4zGcTSHThfqr4uRjRxWQa4iN1438h3Z0S0NL2lRp75mpoo6Kr3HGrHhFPC+Oh25z1uxav60\n"
"sUYgovseO3Dvk5h9jHOW8sXvhXCtKSb8HgQ+HKDYD8tSg2J87otTlZCpV6LqYQXY+U3EJ/pure35\n"
"11H3a6UCAwEAAaOCASQwggEgMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFNOUikxiEyoZLsyv\n"
"cop9NteaHNxnMA4GA1UdDwEB/wQEAwIBBjCB3QYDVR0fBIHVMIHSMIGHoIGEoIGBhn9sZGFwOi8v\n"
"ZGlyZWN0b3J5LmQtdHJ1c3QubmV0L0NOPUQtVFJVU1QlMjBSb290JTIwQ2xhc3MlMjAzJTIwQ0El\n"
"MjAyJTIwRVYlMjAyMDA5LE89RC1UcnVzdCUyMEdtYkgsQz1ERT9jZXJ0aWZpY2F0ZXJldm9jYXRp\n"
"b25saXN0MEagRKBChkBodHRwOi8vd3d3LmQtdHJ1c3QubmV0L2NybC9kLXRydXN0X3Jvb3RfY2xh\n"
"c3NfM19jYV8yX2V2XzIwMDkuY3JsMA0GCSqGSIb3DQEBCwUAA4IBAQA07XtaPKSUiO8aEXUHL7P+\n"
"PPoeUSbrh/Yp3uDx1MYkCenBz1UbtDDZzhr+BlGmFaQt77JLvyAoJUnRpjZ3NOhk31KxEcdzes05\n"
"nsKtjHEh8lprr988TlWvsoRlFIm5d8sqMb7Po23Pb0iUMkZv53GMoKaEGTcH8gNFCSuGdXzfX2lX\n"
"ANtu2KZyIktQ1HWYVt+3GP9DQ1CuekR78HlR10M9p9OB0/DJT7naxpeG0ILD5EJt/rDiZE4OJudA\n"
"NCa1CInXCGNjOCd1HjPqbqjdn5lPdE2BiYBL3ZqXKVwvvoFBuYz/6n1gBp7N1z3TLqMVvKjmJuVv\n"
"w9y4AyHqnxbxLFS1\n"
"-----END CERTIFICATE-----\n"
"\n"
"CA Disig Root R2\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFaTCCA1GgAwIBAgIJAJK4iNuwisFjMA0GCSqGSIb3DQEBCwUAMFIxCzAJBgNVBAYTAlNLMRMw\n"
"EQYDVQQHEwpCcmF0aXNsYXZhMRMwEQYDVQQKEwpEaXNpZyBhLnMuMRkwFwYDVQQDExBDQSBEaXNp\n"
"ZyBSb290IFIyMB4XDTEyMDcxOTA5MTUzMFoXDTQyMDcxOTA5MTUzMFowUjELMAkGA1UEBhMCU0sx\n"
"EzARBgNVBAcTCkJyYXRpc2xhdmExEzARBgNVBAoTCkRpc2lnIGEucy4xGTAXBgNVBAMTEENBIERp\n"
"c2lnIFJvb3QgUjIwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCio8QACdaFXS1tFPbC\n"
"w3OeNcJxVX6B+6tGUODBfEl45qt5WDza/3wcn9iXAng+a0EE6UG9vgMsRfYvZNSrXaNHPWSb6Wia\n"
"xswbP7q+sos0Ai6YVRn8jG+qX9pMzk0DIaPY0jSTVpbLTAwAFjxfGs3Ix2ymrdMxp7zo5eFm1tL7\n"
"A7RBZckQrg4FY8aAamkw/dLukO8NJ9+flXP04SXabBbeQTg06ov80egEFGEtQX6sx3dOy1FU+16S\n"
"GBsEWmjGycT6txOgmLcRK7fWV8x8nhfRyyX+hk4kLlYMeE2eARKmK6cBZW58Yh2EhN/qwGu1pSqV\n"
"g8NTEQxzHQuyRpDRQjrOQG6Vrf/GlK1ul4SOfW+eioANSW1z4nuSHsPzwfPrLgVv2RvPN3YEyLRa\n"
"5Beny912H9AZdugsBbPWnDTYltxhh5EF5EQIM8HauQhl1K6yNg3ruji6DOWbnuuNZt2Zz9aJQfYE\n"
"koopKW1rOhzndX0CcQ7zwOe9yxndnWCywmZgtrEE7snmhrmaZkCo5xHtgUUDi/ZnWejBBhG93c+A\n"
"Ak9lQHhcR1DIm+YfgXvkRKhbhZri3lrVx/k6RGZL5DJUfORsnLMOPReisjQS1n6yqEm70XooQL6i\n"
"Fh/f5DcfEXP7kAplQ6INfPgGAVUzfbANuPT1rqVCV3w2EYx7XsQDnYx5nQIDAQABo0IwQDAPBgNV\n"
"HRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBBjAdBgNVHQ4EFgQUtZn4r7CU9eMg1gqtzk5WpC5u\n"
"Qu0wDQYJKoZIhvcNAQELBQADggIBACYGXnDnZTPIgm7ZnBc6G3pmsgH2eDtpXi/q/075KMOYKmFM\n"
"tCQSin1tERT3nLXK5ryeJ45MGcipvXrA1zYObYVybqjGom32+nNjf7xueQgcnYqfGopTpti72TVV\n"
"sRHFqQOzVju5hJMiXn7B9hJSi+osZ7z+Nkz1uM/Rs0mSO9MpDpkblvdhuDvEK7Z4bLQjb/D907Je\n"
"dR+Zlais9trhxTF7+9FGs9K8Z7RiVLoJ92Owk6Ka+elSLotgEqv89WBW7xBci8QaQtyDW2QOy7W8\n"
"1k/BfDxujRNt+3vrMNDcTa/F1balTFtxyegxvug4BkihGuLq0t4SOVga/4AOgnXmt8kHbA7v/zjx\n"
"mHHEt38OFdAlab0inSvtBfZGR6ztwPDUO+Ls7pZbkBNOHlY667DvlruWIxG68kOGdGSVyCh13x01\n"
"utI3gzhTODY7z2zp+WsO0PsE6E9312UBeIYMej4hYvF/Y3EMyZ9E26gnonW+boE+18DrG5gPcFw0\n"
"sorMwIUY6256s/daoQe/qUKS82Ail+QUoQebTnbAjn39pCXHR+3/H3OszMOl6W8KjptlwlCFtaOg\n"
"UxLMVYdh84GuEEZhvUQhuMI9dM9+JDX6HAcOmz0iyu8xL4ysEr3vQCj8KWefshNPZiTEUxnpHikV\n"
"7+ZtsH8tZ/3zbBt1RqPlShfppNcL\n"
"-----END CERTIFICATE-----\n"
"\n"
"ACCVRAIZ1\n"
"=========\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIH0zCCBbugAwIBAgIIXsO3pkN/pOAwDQYJKoZIhvcNAQEFBQAwQjESMBAGA1UEAwwJQUNDVlJB\n"
"SVoxMRAwDgYDVQQLDAdQS0lBQ0NWMQ0wCwYDVQQKDARBQ0NWMQswCQYDVQQGEwJFUzAeFw0xMTA1\n"
"MDUwOTM3MzdaFw0zMDEyMzEwOTM3MzdaMEIxEjAQBgNVBAMMCUFDQ1ZSQUlaMTEQMA4GA1UECwwH\n"
"UEtJQUNDVjENMAsGA1UECgwEQUNDVjELMAkGA1UEBhMCRVMwggIiMA0GCSqGSIb3DQEBAQUAA4IC\n"
"DwAwggIKAoICAQCbqau/YUqXry+XZpp0X9DZlv3P4uRm7x8fRzPCRKPfmt4ftVTdFXxpNRFvu8gM\n"
"jmoYHtiP2Ra8EEg2XPBjs5BaXCQ316PWywlxufEBcoSwfdtNgM3802/J+Nq2DoLSRYWoG2ioPej0\n"
"RGy9ocLLA76MPhMAhN9KSMDjIgro6TenGEyxCQ0jVn8ETdkXhBilyNpAlHPrzg5XPAOBOp0KoVdD\n"
"aaxXbXmQeOW1tDvYvEyNKKGno6e6Ak4l0Squ7a4DIrhrIA8wKFSVf+DuzgpmndFALW4ir50awQUZ\n"
"0m/A8p/4e7MCQvtQqR0tkw8jq8bBD5L/0KIV9VMJcRz/RROE5iZe+OCIHAr8Fraocwa48GOEAqDG\n"
"WuzndN9wrqODJerWx5eHk6fGioozl2A3ED6XPm4pFdahD9GILBKfb6qkxkLrQaLjlUPTAYVtjrs7\n"
"8yM2x/474KElB0iryYl0/wiPgL/AlmXz7uxLaL2diMMxs0Dx6M/2OLuc5NF/1OVYm3z61PMOm3WR\n"
"5LpSLhl+0fXNWhn8ugb2+1KoS5kE3fj5tItQo05iifCHJPqDQsGH+tUtKSpacXpkatcnYGMN285J\n"
"9Y0fkIkyF/hzQ7jSWpOGYdbhdQrqeWZ2iE9x6wQl1gpaepPluUsXQA+xtrn13k/c4LOsOxFwYIRK\n"
"Q26ZIMApcQrAZQIDAQABo4ICyzCCAscwfQYIKwYBBQUHAQEEcTBvMEwGCCsGAQUFBzAChkBodHRw\n"
"Oi8vd3d3LmFjY3YuZXMvZmlsZWFkbWluL0FyY2hpdm9zL2NlcnRpZmljYWRvcy9yYWl6YWNjdjEu\n"
"Y3J0MB8GCCsGAQUFBzABhhNodHRwOi8vb2NzcC5hY2N2LmVzMB0GA1UdDgQWBBTSh7Tj3zcnk1X2\n"
"VuqB5TbMjB4/vTAPBgNVHRMBAf8EBTADAQH/MB8GA1UdIwQYMBaAFNKHtOPfNyeTVfZW6oHlNsyM\n"
"Hj+9MIIBcwYDVR0gBIIBajCCAWYwggFiBgRVHSAAMIIBWDCCASIGCCsGAQUFBwICMIIBFB6CARAA\n"
"QQB1AHQAbwByAGkAZABhAGQAIABkAGUAIABDAGUAcgB0AGkAZgBpAGMAYQBjAGkA8wBuACAAUgBh\n"
"AO0AegAgAGQAZQAgAGwAYQAgAEEAQwBDAFYAIAAoAEEAZwBlAG4AYwBpAGEAIABkAGUAIABUAGUA\n"
"YwBuAG8AbABvAGcA7QBhACAAeQAgAEMAZQByAHQAaQBmAGkAYwBhAGMAaQDzAG4AIABFAGwAZQBj\n"
"AHQAcgDzAG4AaQBjAGEALAAgAEMASQBGACAAUQA0ADYAMAAxADEANQA2AEUAKQAuACAAQwBQAFMA\n"
"IABlAG4AIABoAHQAdABwADoALwAvAHcAdwB3AC4AYQBjAGMAdgAuAGUAczAwBggrBgEFBQcCARYk\n"
"aHR0cDovL3d3dy5hY2N2LmVzL2xlZ2lzbGFjaW9uX2MuaHRtMFUGA1UdHwROMEwwSqBIoEaGRGh0\n"
"dHA6Ly93d3cuYWNjdi5lcy9maWxlYWRtaW4vQXJjaGl2b3MvY2VydGlmaWNhZG9zL3JhaXphY2N2\n"
"MV9kZXIuY3JsMA4GA1UdDwEB/wQEAwIBBjAXBgNVHREEEDAOgQxhY2N2QGFjY3YuZXMwDQYJKoZI\n"
"hvcNAQEFBQADggIBAJcxAp/n/UNnSEQU5CmH7UwoZtCPNdpNYbdKl02125DgBS4OxnnQ8pdpD70E\n"
"R9m+27Up2pvZrqmZ1dM8MJP1jaGo/AaNRPTKFpV8M9xii6g3+CfYCS0b78gUJyCpZET/LtZ1qmxN\n"
"YEAZSUNUY9rizLpm5U9EelvZaoErQNV/+QEnWCzI7UiRfD+mAM/EKXMRNt6GGT6d7hmKG9Ww7Y49\n"
"nCrADdg9ZuM8Db3VlFzi4qc1GwQA9j9ajepDvV+JHanBsMyZ4k0ACtrJJ1vnE5Bc5PUzolVt3OAJ\n"
"TS+xJlsndQAJxGJ3KQhfnlmstn6tn1QwIgPBHnFk/vk4CpYY3QIUrCPLBhwepH2NDd4nQeit2hW3\n"
"sCPdK6jT2iWH7ehVRE2I9DZ+hJp4rPcOVkkO1jMl1oRQQmwgEh0q1b688nCBpHBgvgW1m54ERL5h\n"
"I6zppSSMEYCUWqKiuUnSwdzRp+0xESyeGabu4VXhwOrPDYTkF7eifKXeVSUG7szAh1xA2syVP1Xg\n"
"Nce4hL60Xc16gwFy7ofmXx2utYXGJt/mwZrpHgJHnyqobalbz+xFd3+YJ5oyXSrjhO7FmGYvliAd\n"
"3djDJ9ew+f7Zfc3Qn48LFFhRny+Lwzgt3uiP1o2HpPVWQxaZLPSkVrQ0uGE3ycJYgBugl6H8WY3p\n"
"EfbRD0tVNEYqi4Y7\n"
"-----END CERTIFICATE-----\n"
"\n"
"TWCA Global Root CA\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFQTCCAymgAwIBAgICDL4wDQYJKoZIhvcNAQELBQAwUTELMAkGA1UEBhMCVFcxEjAQBgNVBAoT\n"
"CVRBSVdBTi1DQTEQMA4GA1UECxMHUm9vdCBDQTEcMBoGA1UEAxMTVFdDQSBHbG9iYWwgUm9vdCBD\n"
"QTAeFw0xMjA2MjcwNjI4MzNaFw0zMDEyMzExNTU5NTlaMFExCzAJBgNVBAYTAlRXMRIwEAYDVQQK\n"
"EwlUQUlXQU4tQ0ExEDAOBgNVBAsTB1Jvb3QgQ0ExHDAaBgNVBAMTE1RXQ0EgR2xvYmFsIFJvb3Qg\n"
"Q0EwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCwBdvI64zEbooh745NnHEKH1Jw7W2C\n"
"nJfF10xORUnLQEK1EjRsGcJ0pDFfhQKX7EMzClPSnIyOt7h52yvVavKOZsTuKwEHktSz0ALfUPZV\n"
"r2YOy+BHYC8rMjk1Ujoog/h7FsYYuGLWRyWRzvAZEk2tY/XTP3VfKfChMBwqoJimFb3u/Rk28OKR\n"
"Q4/6ytYQJ0lM793B8YVwm8rqqFpD/G2Gb3PpN0Wp8DbHzIh1HrtsBv+baz4X7GGqcXzGHaL3SekV\n"
"tTzWoWH1EfcFbx39Eb7QMAfCKbAJTibc46KokWofwpFFiFzlmLhxpRUZyXx1EcxwdE8tmx2RRP1W\n"
"KKD+u4ZqyPpcC1jcxkt2yKsi2XMPpfRaAok/T54igu6idFMqPVMnaR1sjjIsZAAmY2E2TqNGtz99\n"
"sy2sbZCilaLOz9qC5wc0GZbpuCGqKX6mOL6OKUohZnkfs8O1CWfe1tQHRvMq2uYiN2DLgbYPoA/p\n"
"yJV/v1WRBXrPPRXAb94JlAGD1zQbzECl8LibZ9WYkTunhHiVJqRaCPgrdLQABDzfuBSO6N+pjWxn\n"
"kjMdwLfS7JLIvgm/LCkFbwJrnu+8vyq8W8BQj0FwcYeyTbcEqYSjMq+u7msXi7Kx/mzhkIyIqJdI\n"
"zshNy/MGz19qCkKxHh53L46g5pIOBvwFItIm4TFRfTLcDwIDAQABoyMwITAOBgNVHQ8BAf8EBAMC\n"
"AQYwDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAgEAXzSBdu+WHdXltdkCY4QWwa6g\n"
"cFGn90xHNcgL1yg9iXHZqjNB6hQbbCEAwGxCGX6faVsgQt+i0trEfJdLjbDorMjupWkEmQqSpqsn\n"
"LhpNgb+E1HAerUf+/UqdM+DyucRFCCEK2mlpc3INvjT+lIutwx4116KD7+U4x6WFH6vPNOw/KP4M\n"
"8VeGTslV9xzU2KV9Bnpv1d8Q34FOIWWxtuEXeZVFBs5fzNxGiWNoRI2T9GRwoD2dKAXDOXC4Ynsg\n"
"/eTb6QihuJ49CcdP+yz4k3ZB3lLg4VfSnQO8d57+nile98FRYB/e2guyLXW3Q0iT5/Z5xoRdgFlg\n"
"lPx4mI88k1HtQJAH32RjJMtOcQWh15QaiDLxInQirqWm2BJpTGCjAu4r7NRjkgtevi92a6O2JryP\n"
"A9gK8kxkRr05YuWW6zRjESjMlfGt7+/cgFhI6Uu46mWs6fyAtbXIRfmswZ/ZuepiiI7E8UuDEq3m\n"
"i4TWnsLrgxifarsbJGAzcMzs9zLzXNl5fe+epP7JI8Mk7hWSsT2RTyaGvWZzJBPqpK5jwa19hAM8\n"
"EHiGG3njxPPyBJUgriOCxLM6AGK/5jYk4Ve6xx6QddVfP5VhK8E7zeWzaGHQRiapIVJpLesux+t3\n"
"zqY6tQMzT3bR51xUAV3LePTJDL/PEo4XLSNolOer/qmyKwbQBM0=\n"
"-----END CERTIFICATE-----\n"
"\n"
"TeliaSonera Root CA v1\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFODCCAyCgAwIBAgIRAJW+FqD3LkbxezmCcvqLzZYwDQYJKoZIhvcNAQEFBQAwNzEUMBIGA1UE\n"
"CgwLVGVsaWFTb25lcmExHzAdBgNVBAMMFlRlbGlhU29uZXJhIFJvb3QgQ0EgdjEwHhcNMDcxMDE4\n"
"MTIwMDUwWhcNMzIxMDE4MTIwMDUwWjA3MRQwEgYDVQQKDAtUZWxpYVNvbmVyYTEfMB0GA1UEAwwW\n"
"VGVsaWFTb25lcmEgUm9vdCBDQSB2MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAMK+\n"
"6yfwIaPzaSZVfp3FVRaRXP3vIb9TgHot0pGMYzHw7CTww6XScnwQbfQ3t+XmfHnqjLWCi65ItqwA\n"
"3GV17CpNX8GH9SBlK4GoRz6JI5UwFpB/6FcHSOcZrr9FZ7E3GwYq/t75rH2D+1665I+XZ75Ljo1k\n"
"B1c4VWk0Nj0TSO9P4tNmHqTPGrdeNjPUtAa9GAH9d4RQAEX1jF3oI7x+/jXh7VB7qTCNGdMJjmhn\n"
"Xb88lxhTuylixcpecsHHltTbLaC0H2kD7OriUPEMPPCs81Mt8Bz17Ww5OXOAFshSsCPN4D7c3TxH\n"
"oLs1iuKYaIu+5b9y7tL6pe0S7fyYGKkmdtwoSxAgHNN/Fnct7W+A90m7UwW7XWjH1Mh1Fj+JWov3\n"
"F0fUTPHSiXk+TT2YqGHeOh7S+F4D4MHJHIzTjU3TlTazN19jY5szFPAtJmtTfImMMsJu7D0hADnJ\n"
"oWjiUIMusDor8zagrC/kb2HCUQk5PotTubtn2txTuXZZNp1D5SDgPTJghSJRt8czu90VL6R4pgd7\n"
"gUY2BIbdeTXHlSw7sKMXNeVzH7RcWe/a6hBle3rQf5+ztCo3O3CLm1u5K7fsslESl1MpWtTwEhDc\n"
"TwK7EpIvYtQ/aUN8Ddb8WHUBiJ1YFkveupD/RwGJBmr2X7KQarMCpgKIv7NHfirZ1fpoeDVNAgMB\n"
"AAGjPzA9MA8GA1UdEwEB/wQFMAMBAf8wCwYDVR0PBAQDAgEGMB0GA1UdDgQWBBTwj1k4ALP1j5qW\n"
"DNXr+nuqF+gTEjANBgkqhkiG9w0BAQUFAAOCAgEAvuRcYk4k9AwI//DTDGjkk0kiP0Qnb7tt3oNm\n"
"zqjMDfz1mgbldxSR651Be5kqhOX//CHBXfDkH1e3damhXwIm/9fH907eT/j3HEbAek9ALCI18Bmx\n"
"0GtnLLCo4MBANzX2hFxc469CeP6nyQ1Q6g2EdvZR74NTxnr/DlZJLo961gzmJ1TjTQpgcmLNkQfW\n"
"pb/ImWvtxBnmq0wROMVvMeJuScg/doAmAyYp4Db29iBT4xdwNBedY2gea+zDTYa4EzAvXUYNR0PV\n"
"G6pZDrlcjQZIrXSHX8f8MVRBE+LHIQ6e4B4N4cB7Q4WQxYpYxmUKeFfyxiMPAdkgS94P+5KFdSpc\n"
"c41teyWRyu5FrgZLAMzTsVlQ2jqIOylDRl6XK1TOU2+NSueW+r9xDkKLfP0ooNBIytrEgUy7onOT\n"
"JsjrDNYmiLbAJM+7vVvrdX3pCI6GMyx5dwlppYn8s3CQh3aP0yK7Qs69cwsgJirQmz1wHiRszYd2\n"
"qReWt88NkvuOGKmYSdGe/mBEciG5Ge3C9THxOUiIkCR1VBatzvT4aRRkOfujuLpwQMcnHL/EVlP6\n"
"Y2XQ8xwOFvVrhlhNGNTkDY6lnVuR3HYkUD/GKvvZt5y11ubQ2egZixVxSK236thZiNSQvxaz2ems\n"
"WWFUyBy6ysHK4bkgTI86k4mloMy/0/Z1pHWWbVY=\n"
"-----END CERTIFICATE-----\n"
"\n"
"E-Tugra Certification Authority\n"
"===============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIGSzCCBDOgAwIBAgIIamg+nFGby1MwDQYJKoZIhvcNAQELBQAwgbIxCzAJBgNVBAYTAlRSMQ8w\n"
"DQYDVQQHDAZBbmthcmExQDA+BgNVBAoMN0UtVHXEn3JhIEVCRyBCaWxpxZ9pbSBUZWtub2xvamls\n"
"ZXJpIHZlIEhpem1ldGxlcmkgQS7Fni4xJjAkBgNVBAsMHUUtVHVncmEgU2VydGlmaWthc3lvbiBN\n"
"ZXJrZXppMSgwJgYDVQQDDB9FLVR1Z3JhIENlcnRpZmljYXRpb24gQXV0aG9yaXR5MB4XDTEzMDMw\n"
"NTEyMDk0OFoXDTIzMDMwMzEyMDk0OFowgbIxCzAJBgNVBAYTAlRSMQ8wDQYDVQQHDAZBbmthcmEx\n"
"QDA+BgNVBAoMN0UtVHXEn3JhIEVCRyBCaWxpxZ9pbSBUZWtub2xvamlsZXJpIHZlIEhpem1ldGxl\n"
"cmkgQS7Fni4xJjAkBgNVBAsMHUUtVHVncmEgU2VydGlmaWthc3lvbiBNZXJrZXppMSgwJgYDVQQD\n"
"DB9FLVR1Z3JhIENlcnRpZmljYXRpb24gQXV0aG9yaXR5MIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\n"
"MIICCgKCAgEA4vU/kwVRHoViVF56C/UYB4Oufq9899SKa6VjQzm5S/fDxmSJPZQuVIBSOTkHS0vd\n"
"hQd2h8y/L5VMzH2nPbxHD5hw+IyFHnSOkm0bQNGZDbt1bsipa5rAhDGvykPL6ys06I+XawGb1Q5K\n"
"CKpbknSFQ9OArqGIW66z6l7LFpp3RMih9lRozt6Plyu6W0ACDGQXwLWTzeHxE2bODHnv0ZEoq1+g\n"
"ElIwcxmOj+GMB6LDu0rw6h8VqO4lzKRG+Bsi77MOQ7osJLjFLFzUHPhdZL3Dk14opz8n8Y4e0ypQ\n"
"BaNV2cvnOVPAmJ6MVGKLJrD3fY185MaeZkJVgkfnsliNZvcHfC425lAcP9tDJMW/hkd5s3kc91r0\n"
"E+xs+D/iWR+V7kI+ua2oMoVJl0b+SzGPWsutdEcf6ZG33ygEIqDUD13ieU/qbIWGvaimzuT6w+Gz\n"
"rt48Ue7LE3wBf4QOXVGUnhMMti6lTPk5cDZvlsouDERVxcr6XQKj39ZkjFqzAQqptQpHF//vkUAq\n"
"jqFGOjGY5RH8zLtJVor8udBhmm9lbObDyz51Sf6Pp+KJxWfXnUYTTjF2OySznhFlhqt/7x3U+Lzn\n"
"rFpct1pHXFXOVbQicVtbC/DP3KBhZOqp12gKY6fgDT+gr9Oq0n7vUaDmUStVkhUXU8u3Zg5mTPj5\n"
"dUyQ5xJwx0UCAwEAAaNjMGEwHQYDVR0OBBYEFC7j27JJ0JxUeVz6Jyr+zE7S6E5UMA8GA1UdEwEB\n"
"/wQFMAMBAf8wHwYDVR0jBBgwFoAULuPbsknQnFR5XPonKv7MTtLoTlQwDgYDVR0PAQH/BAQDAgEG\n"
"MA0GCSqGSIb3DQEBCwUAA4ICAQAFNzr0TbdF4kV1JI+2d1LoHNgQk2Xz8lkGpD4eKexd0dCrfOAK\n"
"kEh47U6YA5n+KGCRHTAduGN8qOY1tfrTYXbm1gdLymmasoR6d5NFFxWfJNCYExL/u6Au/U5Mh/jO\n"
"XKqYGwXgAEZKgoClM4so3O0409/lPun++1ndYYRP0lSWE2ETPo+Aab6TR7U1Q9Jauz1c77NCR807\n"
"VRMGsAnb/WP2OogKmW9+4c4bU2pEZiNRCHu8W1Ki/QY3OEBhj0qWuJA3+GbHeJAAFS6LrVE1Uweo\n"
"a2iu+U48BybNCAVwzDk/dr2l02cmAYamU9JgO3xDf1WKvJUawSg5TB9D0pH0clmKuVb8P7Sd2nCc\n"
"dlqMQ1DujjByTd//SffGqWfZbawCEeI6FiWnWAjLb1NBnEg4R2gz0dfHj9R0IdTDBZB6/86WiLEV\n"
"KV0jq9BgoRJP3vQXzTLlyb/IQ639Lo7xr+L0mPoSHyDYwKcMhcWQ9DstliaxLL5Mq+ux0orJ23gT\n"
"Dx4JnW2PAJ8C2sH6H3p6CcRK5ogql5+Ji/03X186zjhZhkuvcQu02PJwT58yE+Owp1fl2tpDy4Q0\n"
"8ijE6m30Ku/Ba3ba+367hTzSU8JNvnHhRdH9I2cNE3X7z2VnIp2usAnRCf8dNL/+I5c30jn6PQ0G\n"
"C7TbO6Orb1wdtn7os4I07QZcJA==\n"
"-----END CERTIFICATE-----\n"
"\n"
"T-TeleSec GlobalRoot Class 2\n"
"============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDwzCCAqugAwIBAgIBATANBgkqhkiG9w0BAQsFADCBgjELMAkGA1UEBhMCREUxKzApBgNVBAoM\n"
"IlQtU3lzdGVtcyBFbnRlcnByaXNlIFNlcnZpY2VzIEdtYkgxHzAdBgNVBAsMFlQtU3lzdGVtcyBU\n"
"cnVzdCBDZW50ZXIxJTAjBgNVBAMMHFQtVGVsZVNlYyBHbG9iYWxSb290IENsYXNzIDIwHhcNMDgx\n"
"MDAxMTA0MDE0WhcNMzMxMDAxMjM1OTU5WjCBgjELMAkGA1UEBhMCREUxKzApBgNVBAoMIlQtU3lz\n"
"dGVtcyBFbnRlcnByaXNlIFNlcnZpY2VzIEdtYkgxHzAdBgNVBAsMFlQtU3lzdGVtcyBUcnVzdCBD\n"
"ZW50ZXIxJTAjBgNVBAMMHFQtVGVsZVNlYyBHbG9iYWxSb290IENsYXNzIDIwggEiMA0GCSqGSIb3\n"
"DQEBAQUAA4IBDwAwggEKAoIBAQCqX9obX+hzkeXaXPSi5kfl82hVYAUdAqSzm1nzHoqvNK38DcLZ\n"
"SBnuaY/JIPwhqgcZ7bBcrGXHX+0CfHt8LRvWurmAwhiCFoT6ZrAIxlQjgeTNuUk/9k9uN0goOA/F\n"
"vudocP05l03Sx5iRUKrERLMjfTlH6VJi1hKTXrcxlkIF+3anHqP1wvzpesVsqXFP6st4vGCvx970\n"
"2cu+fjOlbpSD8DT6IavqjnKgP6TeMFvvhk1qlVtDRKgQFRzlAVfFmPHmBiiRqiDFt1MmUUOyCxGV\n"
"WOHAD3bZwI18gfNycJ5v/hqO2V81xrJvNHy+SE/iWjnX2J14np+GPgNeGYtEotXHAgMBAAGjQjBA\n"
"MA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgEGMB0GA1UdDgQWBBS/WSA2AHmgoCJrjNXy\n"
"YdK4LMuCSjANBgkqhkiG9w0BAQsFAAOCAQEAMQOiYQsfdOhyNsZt+U2e+iKo4YFWz827n+qrkRk4\n"
"r6p8FU3ztqONpfSO9kSpp+ghla0+AGIWiPACuvxhI+YzmzB6azZie60EI4RYZeLbK4rnJVM3YlNf\n"
"vNoBYimipidx5joifsFvHZVwIEoHNN/q/xWA5brXethbdXwFeilHfkCoMRN3zUA7tFFHei4R40cR\n"
"3p1m0IvVVGb6g1XqfMIpiRvpb7PO4gWEyS8+eIVibslfwXhjdFjASBgMmTnrpMwatXlajRWc2BQN\n"
"9noHV8cigwUtPJslJj0Ys6lDfMjIq2SPDqO/nBudMNva0Bkuqjzx+zOAduTNrRlPBSeOE6Fuwg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Atos TrustedRoot 2011\n"
"=====================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDdzCCAl+gAwIBAgIIXDPLYixfszIwDQYJKoZIhvcNAQELBQAwPDEeMBwGA1UEAwwVQXRvcyBU\n"
"cnVzdGVkUm9vdCAyMDExMQ0wCwYDVQQKDARBdG9zMQswCQYDVQQGEwJERTAeFw0xMTA3MDcxNDU4\n"
"MzBaFw0zMDEyMzEyMzU5NTlaMDwxHjAcBgNVBAMMFUF0b3MgVHJ1c3RlZFJvb3QgMjAxMTENMAsG\n"
"A1UECgwEQXRvczELMAkGA1UEBhMCREUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCV\n"
"hTuXbyo7LjvPpvMpNb7PGKw+qtn4TaA+Gke5vJrf8v7MPkfoepbCJI419KkM/IL9bcFyYie96mvr\n"
"54rMVD6QUM+A1JX76LWC1BTFtqlVJVfbsVD2sGBkWXppzwO3bw2+yj5vdHLqqjAqc2K+SZFhyBH+\n"
"DgMq92og3AIVDV4VavzjgsG1xZ1kCWyjWZgHJ8cblithdHFsQ/H3NYkQ4J7sVaE3IqKHBAUsR320\n"
"HLliKWYoyrfhk/WklAOZuXCFteZI6o1Q/NnezG8HDt0Lcp2AMBYHlT8oDv3FdU9T1nSatCQujgKR\n"
"z3bFmx5VdJx4IbHwLfELn8LVlhgf8FQieowHAgMBAAGjfTB7MB0GA1UdDgQWBBSnpQaxLKYJYO7R\n"
"l+lwrrw7GWzbITAPBgNVHRMBAf8EBTADAQH/MB8GA1UdIwQYMBaAFKelBrEspglg7tGX6XCuvDsZ\n"
"bNshMBgGA1UdIAQRMA8wDQYLKwYBBAGwLQMEAQEwDgYDVR0PAQH/BAQDAgGGMA0GCSqGSIb3DQEB\n"
"CwUAA4IBAQAmdzTblEiGKkGdLD4GkGDEjKwLVLgfuXvTBznk+j57sj1O7Z8jvZfza1zv7v1Apt+h\n"
"k6EKhqzvINB5Ab149xnYJDE0BAGmuhWawyfc2E8PzBhj/5kPDpFrdRbhIfzYJsdHt6bPWHJxfrrh\n"
"TZVHO8mvbaG0weyJ9rQPOLXiZNwlz6bb65pcmaHFCN795trV1lpFDMS3wrUU77QR/w4VtfX128a9\n"
"61qn8FYiqTxlVMYVqL2Gns2Dlmh6cYGJ4Qvh6hEbaAjMaZ7snkGeRDImeuKHCnE96+RapNLbxc3G\n"
"3mB/ufNPRJLvKrcYPqcZ2Qt9sTdBQrC6YB3y/gkRsPCHe6ed\n"
"-----END CERTIFICATE-----\n"
"\n"
"QuoVadis Root CA 1 G3\n"
"=====================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFYDCCA0igAwIBAgIUeFhfLq0sGUvjNwc1NBMotZbUZZMwDQYJKoZIhvcNAQELBQAwSDELMAkG\n"
"A1UEBhMCQk0xGTAXBgNVBAoTEFF1b1ZhZGlzIExpbWl0ZWQxHjAcBgNVBAMTFVF1b1ZhZGlzIFJv\n"
"b3QgQ0EgMSBHMzAeFw0xMjAxMTIxNzI3NDRaFw00MjAxMTIxNzI3NDRaMEgxCzAJBgNVBAYTAkJN\n"
"MRkwFwYDVQQKExBRdW9WYWRpcyBMaW1pdGVkMR4wHAYDVQQDExVRdW9WYWRpcyBSb290IENBIDEg\n"
"RzMwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCgvlAQjunybEC0BJyFuTHK3C3kEakE\n"
"PBtVwedYMB0ktMPvhd6MLOHBPd+C5k+tR4ds7FtJwUrVu4/sh6x/gpqG7D0DmVIB0jWerNrwU8lm\n"
"PNSsAgHaJNM7qAJGr6Qc4/hzWHa39g6QDbXwz8z6+cZM5cOGMAqNF34168Xfuw6cwI2H44g4hWf6\n"
"Pser4BOcBRiYz5P1sZK0/CPTz9XEJ0ngnjybCKOLXSoh4Pw5qlPafX7PGglTvF0FBM+hSo+LdoIN\n"
"ofjSxxR3W5A2B4GbPgb6Ul5jxaYA/qXpUhtStZI5cgMJYr2wYBZupt0lwgNm3fME0UDiTouG9G/l\n"
"g6AnhF4EwfWQvTA9xO+oabw4m6SkltFi2mnAAZauy8RRNOoMqv8hjlmPSlzkYZqn0ukqeI1RPToV\n"
"7qJZjqlc3sX5kCLliEVx3ZGZbHqfPT2YfF72vhZooF6uCyP8Wg+qInYtyaEQHeTTRCOQiJ/GKubX\n"
"9ZqzWB4vMIkIG1SitZgj7Ah3HJVdYdHLiZxfokqRmu8hqkkWCKi9YSgxyXSthfbZxbGL0eUQMk1f\n"
"iyA6PEkfM4VZDdvLCXVDaXP7a3F98N/ETH3Goy7IlXnLc6KOTk0k+17kBL5yG6YnLUlamXrXXAkg\n"
"t3+UuU/xDRxeiEIbEbfnkduebPRq34wGmAOtzCjvpUfzUwIDAQABo0IwQDAPBgNVHRMBAf8EBTAD\n"
"AQH/MA4GA1UdDwEB/wQEAwIBBjAdBgNVHQ4EFgQUo5fW816iEOGrRZ88F2Q87gFwnMwwDQYJKoZI\n"
"hvcNAQELBQADggIBABj6W3X8PnrHX3fHyt/PX8MSxEBd1DKquGrX1RUVRpgjpeaQWxiZTOOtQqOC\n"
"MTaIzen7xASWSIsBx40Bz1szBpZGZnQdT+3Btrm0DWHMY37XLneMlhwqI2hrhVd2cDMT/uFPpiN3\n"
"GPoajOi9ZcnPP/TJF9zrx7zABC4tRi9pZsMbj/7sPtPKlL92CiUNqXsCHKnQO18LwIE6PWThv6ct\n"
"Tr1NxNgpxiIY0MWscgKCP6o6ojoilzHdCGPDdRS5YCgtW2jgFqlmgiNR9etT2DGbe+m3nUvriBbP\n"
"+V04ikkwj+3x6xn0dxoxGE1nVGwvb2X52z3sIexe9PSLymBlVNFxZPT5pqOBMzYzcfCkeF9OrYMh\n"
"3jRJjehZrJ3ydlo28hP0r+AJx2EqbPfgna67hkooby7utHnNkDPDs3b69fBsnQGQ+p6Q9pxyz0fa\n"
"wx/kNSBT8lTR32GDpgLiJTjehTItXnOQUl1CxM49S+H5GYQd1aJQzEH7QRTDvdbJWqNjZgKAvQU6\n"
"O0ec7AAmTPWIUb+oI38YB7AL7YsmoWTTYUrrXJ/es69nA7Mf3W1daWhpq1467HxpvMc7hU6eFbm0\n"
"FU/DlXpY18ls6Wy58yljXrQs8C097Vpl4KlbQMJImYFtnh8GKjwStIsPm6Ik8KaN1nrgS7ZklmOV\n"
"hMJKzRwuJIczYOXD\n"
"-----END CERTIFICATE-----\n"
"\n"
"QuoVadis Root CA 2 G3\n"
"=====================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFYDCCA0igAwIBAgIURFc0JFuBiZs18s64KztbpybwdSgwDQYJKoZIhvcNAQELBQAwSDELMAkG\n"
"A1UEBhMCQk0xGTAXBgNVBAoTEFF1b1ZhZGlzIExpbWl0ZWQxHjAcBgNVBAMTFVF1b1ZhZGlzIFJv\n"
"b3QgQ0EgMiBHMzAeFw0xMjAxMTIxODU5MzJaFw00MjAxMTIxODU5MzJaMEgxCzAJBgNVBAYTAkJN\n"
"MRkwFwYDVQQKExBRdW9WYWRpcyBMaW1pdGVkMR4wHAYDVQQDExVRdW9WYWRpcyBSb290IENBIDIg\n"
"RzMwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQChriWyARjcV4g/Ruv5r+LrI3HimtFh\n"
"ZiFfqq8nUeVuGxbULX1QsFN3vXg6YOJkApt8hpvWGo6t/x8Vf9WVHhLL5hSEBMHfNrMWn4rjyduY\n"
"NM7YMxcoRvynyfDStNVNCXJJ+fKH46nafaF9a7I6JaltUkSs+L5u+9ymc5GQYaYDFCDy54ejiK2t\n"
"oIz/pgslUiXnFgHVy7g1gQyjO/Dh4fxaXc6AcW34Sas+O7q414AB+6XrW7PFXmAqMaCvN+ggOp+o\n"
"MiwMzAkd056OXbxMmO7FGmh77FOm6RQ1o9/NgJ8MSPsc9PG/Srj61YxxSscfrf5BmrODXfKEVu+l\n"
"V0POKa2Mq1W/xPtbAd0jIaFYAI7D0GoT7RPjEiuA3GfmlbLNHiJuKvhB1PLKFAeNilUSxmn1uIZo\n"
"L1NesNKqIcGY5jDjZ1XHm26sGahVpkUG0CM62+tlXSoREfA7T8pt9DTEceT/AFr2XK4jYIVz8eQQ\n"
"sSWu1ZK7E8EM4DnatDlXtas1qnIhO4M15zHfeiFuuDIIfR0ykRVKYnLP43ehvNURG3YBZwjgQQvD\n"
"6xVu+KQZ2aKrr+InUlYrAoosFCT5v0ICvybIxo/gbjh9Uy3l7ZizlWNof/k19N+IxWA1ksB8aRxh\n"
"lRbQ694Lrz4EEEVlWFA4r0jyWbYW8jwNkALGcC4BrTwV1wIDAQABo0IwQDAPBgNVHRMBAf8EBTAD\n"
"AQH/MA4GA1UdDwEB/wQEAwIBBjAdBgNVHQ4EFgQU7edvdlq/YOxJW8ald7tyFnGbxD0wDQYJKoZI\n"
"hvcNAQELBQADggIBAJHfgD9DCX5xwvfrs4iP4VGyvD11+ShdyLyZm3tdquXK4Qr36LLTn91nMX66\n"
"AarHakE7kNQIXLJgapDwyM4DYvmL7ftuKtwGTTwpD4kWilhMSA/ohGHqPHKmd+RCroijQ1h5fq7K\n"
"pVMNqT1wvSAZYaRsOPxDMuHBR//47PERIjKWnML2W2mWeyAMQ0GaW/ZZGYjeVYg3UQt4XAoeo0L9\n"
"x52ID8DyeAIkVJOviYeIyUqAHerQbj5hLja7NQ4nlv1mNDthcnPxFlxHBlRJAHpYErAK74X9sbgz\n"
"dWqTHBLmYF5vHX/JHyPLhGGfHoJE+V+tYlUkmlKY7VHnoX6XOuYvHxHaU4AshZ6rNRDbIl9qxV6X\n"
"U/IyAgkwo1jwDQHVcsaxfGl7w/U2Rcxhbl5MlMVerugOXou/983g7aEOGzPuVBj+D77vfoRrQ+Nw\n"
"mNtddbINWQeFFSM51vHfqSYP1kjHs6Yi9TM3WpVHn3u6GBVv/9YUZINJ0gpnIdsPNWNgKCLjsZWD\n"
"zYWm3S8P52dSbrsvhXz1SnPnxT7AvSESBT/8twNJAlvIJebiVDj1eYeMHVOyToV7BjjHLPj4sHKN\n"
"JeV3UvQDHEimUF+IIDBu8oJDqz2XhOdT+yHBTw8imoa4WSr2Rz0ZiC3oheGe7IUIarFsNMkd7Egr\n"
"O3jtZsSOeWmD3n+M\n"
"-----END CERTIFICATE-----\n"
"\n"
"QuoVadis Root CA 3 G3\n"
"=====================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFYDCCA0igAwIBAgIULvWbAiin23r/1aOp7r0DoM8Sah0wDQYJKoZIhvcNAQELBQAwSDELMAkG\n"
"A1UEBhMCQk0xGTAXBgNVBAoTEFF1b1ZhZGlzIExpbWl0ZWQxHjAcBgNVBAMTFVF1b1ZhZGlzIFJv\n"
"b3QgQ0EgMyBHMzAeFw0xMjAxMTIyMDI2MzJaFw00MjAxMTIyMDI2MzJaMEgxCzAJBgNVBAYTAkJN\n"
"MRkwFwYDVQQKExBRdW9WYWRpcyBMaW1pdGVkMR4wHAYDVQQDExVRdW9WYWRpcyBSb290IENBIDMg\n"
"RzMwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCzyw4QZ47qFJenMioKVjZ/aEzHs286\n"
"IxSR/xl/pcqs7rN2nXrpixurazHb+gtTTK/FpRp5PIpM/6zfJd5O2YIyC0TeytuMrKNuFoM7pmRL\n"
"Mon7FhY4futD4tN0SsJiCnMK3UmzV9KwCoWdcTzeo8vAMvMBOSBDGzXRU7Ox7sWTaYI+FrUoRqHe\n"
"6okJ7UO4BUaKhvVZR74bbwEhELn9qdIoyhA5CcoTNs+cra1AdHkrAj80//ogaX3T7mH1urPnMNA3\n"
"I4ZyYUUpSFlob3emLoG+B01vr87ERRORFHAGjx+f+IdpsQ7vw4kZ6+ocYfx6bIrc1gMLnia6Et3U\n"
"VDmrJqMz6nWB2i3ND0/kA9HvFZcba5DFApCTZgIhsUfei5pKgLlVj7WiL8DWM2fafsSntARE60f7\n"
"5li59wzweyuxwHApw0BiLTtIadwjPEjrewl5qW3aqDCYz4ByA4imW0aucnl8CAMhZa634RylsSqi\n"
"Md5mBPfAdOhx3v89WcyWJhKLhZVXGqtrdQtEPREoPHtht+KPZ0/l7DxMYIBpVzgeAVuNVejH38DM\n"
"dyM0SXV89pgR6y3e7UEuFAUCf+D+IOs15xGsIs5XPd7JMG0QA4XN8f+MFrXBsj6IbGB/kE+V9/Yt\n"
"rQE5BwT6dYB9v0lQ7e/JxHwc64B+27bQ3RP+ydOc17KXqQIDAQABo0IwQDAPBgNVHRMBAf8EBTAD\n"
"AQH/MA4GA1UdDwEB/wQEAwIBBjAdBgNVHQ4EFgQUxhfQvKjqAkPyGwaZXSuQILnXnOQwDQYJKoZI\n"
"hvcNAQELBQADggIBADRh2Va1EodVTd2jNTFGu6QHcrxfYWLopfsLN7E8trP6KZ1/AvWkyaiTt3px\n"
"KGmPc+FSkNrVvjrlt3ZqVoAh313m6Tqe5T72omnHKgqwGEfcIHB9UqM+WXzBusnIFUBhynLWcKzS\n"
"t/Ac5IYp8M7vaGPQtSCKFWGafoaYtMnCdvvMujAWzKNhxnQT5WvvoxXqA/4Ti2Tk08HS6IT7SdEQ\n"
"TXlm66r99I0xHnAUrdzeZxNMgRVhvLfZkXdxGYFgu/BYpbWcC/ePIlUnwEsBbTuZDdQdm2NnL9Du\n"
"DcpmvJRPpq3t/O5jrFc/ZSXPsoaP0Aj/uHYUbt7lJ+yreLVTubY/6CD50qi+YUbKh4yE8/nxoGib\n"
"Ih6BJpsQBJFxwAYf3KDTuVan45gtf4Od34wrnDKOMpTwATwiKp9Dwi7DmDkHOHv8XgBCH/MyJnmD\n"
"hPbl8MFREsALHgQjDFSlTC9JxUrRtm5gDWv8a4uFJGS3iQ6rJUdbPM9+Sb3H6QrG2vd+DhcI00iX\n"
"0HGS8A85PjRqHH3Y8iKuu2n0M7SmSFXRDw4m6Oy2Cy2nhTXN/VnIn9HNPlopNLk9hM6xZdRZkZFW\n"
"dSHBd575euFgndOtBBj0fOtek49TSiIp+EgrPk2GrFt/ywaZWWDYWGWVjUTR939+J399roD1B0y2\n"
"PpxxVJkES/1Y+Zj0\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert Assured ID Root G2\n"
"===========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDljCCAn6gAwIBAgIQC5McOtY5Z+pnI7/Dr5r0SzANBgkqhkiG9w0BAQsFADBlMQswCQYDVQQG\n"
"EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSQw\n"
"IgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgRzIwHhcNMTMwODAxMTIwMDAwWhcNMzgw\n"
"MTE1MTIwMDAwWjBlMQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQL\n"
"ExB3d3cuZGlnaWNlcnQuY29tMSQwIgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgRzIw\n"
"ggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDZ5ygvUj82ckmIkzTz+GoeMVSAn61UQbVH\n"
"35ao1K+ALbkKz3X9iaV9JPrjIgwrvJUXCzO/GU1BBpAAvQxNEP4HteccbiJVMWWXvdMX0h5i89vq\n"
"bFCMP4QMls+3ywPgym2hFEwbid3tALBSfK+RbLE4E9HpEgjAALAcKxHad3A2m67OeYfcgnDmCXRw\n"
"VWmvo2ifv922ebPynXApVfSr/5Vh88lAbx3RvpO704gqu52/clpWcTs/1PPRCv4o76Pu2ZmvA9OP\n"
"YLfykqGxvYmJHzDNw6YuYjOuFgJ3RFrngQo8p0Quebg/BLxcoIfhG69Rjs3sLPr4/m3wOnyqi+Rn\n"
"lTGNAgMBAAGjQjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBTO\n"
"w0q5mVXyuNtgv6l+vVa1lzan1jANBgkqhkiG9w0BAQsFAAOCAQEAyqVVjOPIQW5pJ6d1Ee88hjZv\n"
"0p3GeDgdaZaikmkuOGybfQTUiaWxMTeKySHMq2zNixya1r9I0jJmwYrA8y8678Dj1JGG0VDjA9tz\n"
"d29KOVPt3ibHtX2vK0LRdWLjSisCx1BL4GnilmwORGYQRI+tBev4eaymG+g3NJ1TyWGqolKvSnAW\n"
"hsI6yLETcDbYz+70CjTVW0z9B5yiutkBclzzTcHdDrEcDcRjvq30FPuJ7KJBDkzMyFdA0G4Dqs0M\n"
"jomZmWzwPDCvON9vvKO+KSAnq3T/EyJ43pdSVR6DtVQgA+6uwE9W3jfMw3+qBCe703e4YtsXfJwo\n"
"IhNzbM8m9Yop5w==\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert Assured ID Root G3\n"
"===========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICRjCCAc2gAwIBAgIQC6Fa+h3foLVJRK/NJKBs7DAKBggqhkjOPQQDAzBlMQswCQYDVQQGEwJV\n"
"UzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSQwIgYD\n"
"VQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgRzMwHhcNMTMwODAxMTIwMDAwWhcNMzgwMTE1\n"
"MTIwMDAwWjBlMQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
"d3cuZGlnaWNlcnQuY29tMSQwIgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgRzMwdjAQ\n"
"BgcqhkjOPQIBBgUrgQQAIgNiAAQZ57ysRGXtzbg/WPuNsVepRC0FFfLvC/8QdJ+1YlJfZn4f5dwb\n"
"RXkLzMZTCp2NXQLZqVneAlr2lSoOjThKiknGvMYDOAdfVdp+CW7if17QRSAPWXYQ1qAk8C3eNvJs\n"
"KTmjQjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBTL0L2p4ZgF\n"
"UaFNN6KDec6NHSrkhDAKBggqhkjOPQQDAwNnADBkAjAlpIFFAmsSS3V0T8gj43DydXLefInwz5Fy\n"
"YZ5eEJJZVrmDxxDnOOlYJjZ91eQ0hjkCMHw2U/Aw5WJjOpnitqM7mzT6HtoQknFekROn3aRukswy\n"
"1vUhZscv6pZjamVFkpUBtA==\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert Global Root G2\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDjjCCAnagAwIBAgIQAzrx5qcRqaC7KGSxHQn65TANBgkqhkiG9w0BAQsFADBhMQswCQYDVQQG\n"
"EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSAw\n"
"HgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBHMjAeFw0xMzA4MDExMjAwMDBaFw0zODAxMTUx\n"
"MjAwMDBaMGExCzAJBgNVBAYTAlVTMRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3\n"
"dy5kaWdpY2VydC5jb20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IEcyMIIBIjANBgkq\n"
"hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuzfNNNx7a8myaJCtSnX/RrohCgiN9RlUyfuI2/Ou8jqJ\n"
"kTx65qsGGmvPrC3oXgkkRLpimn7Wo6h+4FR1IAWsULecYxpsMNzaHxmx1x7e/dfgy5SDN67sH0NO\n"
"3Xss0r0upS/kqbitOtSZpLYl6ZtrAGCSYP9PIUkY92eQq2EGnI/yuum06ZIya7XzV+hdG82MHauV\n"
"BJVJ8zUtluNJbd134/tJS7SsVQepj5WztCO7TG1F8PapspUwtP1MVYwnSlcUfIKdzXOS0xZKBgyM\n"
"UNGPHgm+F6HmIcr9g+UQvIOlCsRnKPZzFBQ9RnbDhxSJITRNrw9FDKZJobq7nMWxM4MphQIDAQAB\n"
"o0IwQDAPBgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBhjAdBgNVHQ4EFgQUTiJUIBiV5uNu\n"
"5g/6+rkS7QYXjzkwDQYJKoZIhvcNAQELBQADggEBAGBnKJRvDkhj6zHd6mcY1Yl9PMWLSn/pvtsr\n"
"F9+wX3N3KjITOYFnQoQj8kVnNeyIv/iPsGEMNKSuIEyExtv4NeF22d+mQrvHRAiGfzZ0JFrabA0U\n"
"WTW98kndth/Jsw1HKj2ZL7tcu7XUIOGZX1NGFdtom/DzMNU+MeKNhJ7jitralj41E6Vf8PlwUHBH\n"
"QRFXGU7Aj64GxJUTFy8bJZ918rGOmaFvE7FBcf6IKshPECBV1/MUReXgRPTqh5Uykw7+U0b6LJ3/\n"
"iyK5S9kJRaTepLiaWN0bfVKfjllDiIGknibVb63dDcY3fe0Dkhvld1927jyNxF1WW6LZZm6zNTfl\n"
"MrY=\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert Global Root G3\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICPzCCAcWgAwIBAgIQBVVWvPJepDU1w6QP1atFcjAKBggqhkjOPQQDAzBhMQswCQYDVQQGEwJV\n"
"UzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSAwHgYD\n"
"VQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBHMzAeFw0xMzA4MDExMjAwMDBaFw0zODAxMTUxMjAw\n"
"MDBaMGExCzAJBgNVBAYTAlVTMRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5k\n"
"aWdpY2VydC5jb20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IEczMHYwEAYHKoZIzj0C\n"
"AQYFK4EEACIDYgAE3afZu4q4C/sLfyHS8L6+c/MzXRq8NOrexpu80JX28MzQC7phW1FGfp4tn+6O\n"
"YwwX7Adw9c+ELkCDnOg/QW07rdOkFFk2eJ0DQ+4QE2xy3q6Ip6FrtUPOZ9wj/wMco+I+o0IwQDAP\n"
"BgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBhjAdBgNVHQ4EFgQUs9tIpPmhxdiuNkHMEWNp\n"
"Yim8S8YwCgYIKoZIzj0EAwMDaAAwZQIxAK288mw/EkrRLTnDCgmXc/SINoyIJ7vmiI1Qhadj+Z4y\n"
"3maTD/HMsQmP3Wyr+mt/oAIwOWZbwmSNuJ5Q3KjVSaLtx9zRSX8XAbjIho9OjIgrqJqpisXRAL34\n"
"VOKa5Vt8sycX\n"
"-----END CERTIFICATE-----\n"
"\n"
"DigiCert Trusted Root G4\n"
"========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFkDCCA3igAwIBAgIQBZsbV56OITLiOQe9p3d1XDANBgkqhkiG9w0BAQwFADBiMQswCQYDVQQG\n"
"EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSEw\n"
"HwYDVQQDExhEaWdpQ2VydCBUcnVzdGVkIFJvb3QgRzQwHhcNMTMwODAxMTIwMDAwWhcNMzgwMTE1\n"
"MTIwMDAwWjBiMQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
"d3cuZGlnaWNlcnQuY29tMSEwHwYDVQQDExhEaWdpQ2VydCBUcnVzdGVkIFJvb3QgRzQwggIiMA0G\n"
"CSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQC/5pBzaN675F1KPDAiMGkz7MKnJS7JIT3yithZwuEp\n"
"pz1Yq3aaza57G4QNxDAf8xukOBbrVsaXbR2rsnnyyhHS5F/WBTxSD1Ifxp4VpX6+n6lXFllVcq9o\n"
"k3DCsrp1mWpzMpTREEQQLt+C8weE5nQ7bXHiLQwb7iDVySAdYyktzuxeTsiT+CFhmzTrBcZe7Fsa\n"
"vOvJz82sNEBfsXpm7nfISKhmV1efVFiODCu3T6cw2Vbuyntd463JT17lNecxy9qTXtyOj4DatpGY\n"
"QJB5w3jHtrHEtWoYOAMQjdjUN6QuBX2I9YI+EJFwq1WCQTLX2wRzKm6RAXwhTNS8rhsDdV14Ztk6\n"
"MUSaM0C/CNdaSaTC5qmgZ92kJ7yhTzm1EVgX9yRcRo9k98FpiHaYdj1ZXUJ2h4mXaXpI8OCiEhtm\n"
"mnTK3kse5w5jrubU75KSOp493ADkRSWJtppEGSt+wJS00mFt6zPZxd9LBADMfRyVw4/3IbKyEbe7\n"
"f/LVjHAsQWCqsWMYRJUadmJ+9oCw++hkpjPRiQfhvbfmQ6QYuKZ3AeEPlAwhHbJUKSWJbOUOUlFH\n"
"dL4mrLZBdd56rF+NP8m800ERElvlEFDrMcXKchYiCd98THU/Y+whX8QgUWtvsauGi0/C1kVfnSD8\n"
"oR7FwI+isX4KJpn15GkvmB0t9dmpsh3lGwIDAQABo0IwQDAPBgNVHRMBAf8EBTADAQH/MA4GA1Ud\n"
"DwEB/wQEAwIBhjAdBgNVHQ4EFgQU7NfjgtJxXWRM3y5nP+e6mK4cD08wDQYJKoZIhvcNAQEMBQAD\n"
"ggIBALth2X2pbL4XxJEbw6GiAI3jZGgPVs93rnD5/ZpKmbnJeFwMDF/k5hQpVgs2SV1EY+CtnJYY\n"
"ZhsjDT156W1r1lT40jzBQ0CuHVD1UvyQO7uYmWlrx8GnqGikJ9yd+SeuMIW59mdNOj6PWTkiU0Tr\n"
"yF0Dyu1Qen1iIQqAyHNm0aAFYF/opbSnr6j3bTWcfFqK1qI4mfN4i/RN0iAL3gTujJtHgXINwBQy\n"
"7zBZLq7gcfJW5GqXb5JQbZaNaHqasjYUegbyJLkJEVDXCLG4iXqEI2FCKeWjzaIgQdfRnGTZ6iah\n"
"ixTXTBmyUEFxPT9NcCOGDErcgdLMMpSEDQgJlxxPwO5rIHQw0uA5NBCFIRUBCOhVMt5xSdkoF1BN\n"
"5r5N0XWs0Mr7QbhDparTwwVETyw2m+L64kW4I1NsBm9nVX9GtUw/bihaeSbSpKhil9Ie4u1Ki7wb\n"
"/UdKDd9nZn6yW0HQO+T0O/QEY+nvwlQAUaCKKsnOeMzV6ocEGLPOr0mIr/OSmbaz5mEP0oUA51Aa\n"
"5BuVnRmhuZyxm7EAHu/QD09CbMkKvO5D+jpxpchNJqU1/YldvIViHTLSoCtU7ZpXwdv6EM8Zt4tK\n"
"G48BtieVU+i2iW1bvGjUI+iLUaJW+fCmgKDWHrO8Dw9TdSmq6hN35N6MgSGtBxBHEa2HPQfRdbzP\n"
"82Z+\n"
"-----END CERTIFICATE-----\n"
"\n"
"COMODO RSA Certification Authority\n"
"==================================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"LaZRfyHBNVOFBkpdn627G190\n"
"-----END CERTIFICATE-----\n"
"\n"
"USERTrust RSA Certification Authority\n"
"=====================================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"Q+6IHdfGjjxDah2nGN59PRbxYvnKkKj9\n"
"-----END CERTIFICATE-----\n"
"\n"
"USERTrust ECC Certification Authority\n"
"=====================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICjzCCAhWgAwIBAgIQXIuZxVqUxdJxVt7NiYDMJjAKBggqhkjOPQQDAzCBiDELMAkGA1UEBhMC\n"
"VVMxEzARBgNVBAgTCk5ldyBKZXJzZXkxFDASBgNVBAcTC0plcnNleSBDaXR5MR4wHAYDVQQKExVU\n"
"aGUgVVNFUlRSVVNUIE5ldHdvcmsxLjAsBgNVBAMTJVVTRVJUcnVzdCBFQ0MgQ2VydGlmaWNhdGlv\n"
"biBBdXRob3JpdHkwHhcNMTAwMjAxMDAwMDAwWhcNMzgwMTE4MjM1OTU5WjCBiDELMAkGA1UEBhMC\n"
"VVMxEzARBgNVBAgTCk5ldyBKZXJzZXkxFDASBgNVBAcTC0plcnNleSBDaXR5MR4wHAYDVQQKExVU\n"
"aGUgVVNFUlRSVVNUIE5ldHdvcmsxLjAsBgNVBAMTJVVTRVJUcnVzdCBFQ0MgQ2VydGlmaWNhdGlv\n"
"biBBdXRob3JpdHkwdjAQBgcqhkjOPQIBBgUrgQQAIgNiAAQarFRaqfloI+d61SRvU8Za2EurxtW2\n"
"0eZzca7dnNYMYf3boIkDuAUU7FfO7l0/4iGzzvfUinngo4N+LZfQYcTxmdwlkWOrfzCjtHDix6Ez\n"
"nPO/LlxTsV+zfTJ/ijTjeXmjQjBAMB0GA1UdDgQWBBQ64QmG1M8ZwpZ2dEl23OA1xmNjmjAOBgNV\n"
"HQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAKBggqhkjOPQQDAwNoADBlAjA2Z6EWCNzklwBB\n"
"HU6+4WMBzzuqQhFkoJ2UOQIReVx7Hfpkue4WQrO/isIJxOzksU0CMQDpKmFHjFJKS04YcPbWRNZu\n"
"9YO6bVi9JNlWSOrvxKJGgYhqOkbRqZtNyWHa0V1Xahg=\n"
"-----END CERTIFICATE-----\n"
"\n"
"GlobalSign ECC Root CA - R4\n"
"===========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIB4TCCAYegAwIBAgIRKjikHJYKBN5CsiilC+g0mAIwCgYIKoZIzj0EAwIwUDEkMCIGA1UECxMb\n"
"R2xvYmFsU2lnbiBFQ0MgUm9vdCBDQSAtIFI0MRMwEQYDVQQKEwpHbG9iYWxTaWduMRMwEQYDVQQD\n"
"EwpHbG9iYWxTaWduMB4XDTEyMTExMzAwMDAwMFoXDTM4MDExOTAzMTQwN1owUDEkMCIGA1UECxMb\n"
"R2xvYmFsU2lnbiBFQ0MgUm9vdCBDQSAtIFI0MRMwEQYDVQQKEwpHbG9iYWxTaWduMRMwEQYDVQQD\n"
"EwpHbG9iYWxTaWduMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEuMZ5049sJQ6fLjkZHAOkrprl\n"
"OQcJFspjsbmG+IpXwVfOQvpzofdlQv8ewQCybnMO/8ch5RikqtlxP6jUuc6MHaNCMEAwDgYDVR0P\n"
"AQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYEFFSwe61FuOJAf/sKbvu+M8k8o4TV\n"
"MAoGCCqGSM49BAMCA0gAMEUCIQDckqGgE6bPA7DmxCGXkPoUVy0D7O48027KqGx2vKLeuwIgJ6iF\n"
"JzWbVsaj8kfSt24bAgAXqmemFZHe+pTsewv4n4Q=\n"
"-----END CERTIFICATE-----\n"
"\n"
"GlobalSign ECC Root CA - R5\n"
"===========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICHjCCAaSgAwIBAgIRYFlJ4CYuu1X5CneKcflK2GwwCgYIKoZIzj0EAwMwUDEkMCIGA1UECxMb\n"
"R2xvYmFsU2lnbiBFQ0MgUm9vdCBDQSAtIFI1MRMwEQYDVQQKEwpHbG9iYWxTaWduMRMwEQYDVQQD\n"
"EwpHbG9iYWxTaWduMB4XDTEyMTExMzAwMDAwMFoXDTM4MDExOTAzMTQwN1owUDEkMCIGA1UECxMb\n"
"R2xvYmFsU2lnbiBFQ0MgUm9vdCBDQSAtIFI1MRMwEQYDVQQKEwpHbG9iYWxTaWduMRMwEQYDVQQD\n"
"EwpHbG9iYWxTaWduMHYwEAYHKoZIzj0CAQYFK4EEACIDYgAER0UOlvt9Xb/pOdEh+J8LttV7HpI6\n"
"SFkc8GIxLcB6KP4ap1yztsyX50XUWPrRd21DosCHZTQKH3rd6zwzocWdTaRvQZU4f8kehOvRnkmS\n"
"h5SHDDqFSmafnVmTTZdhBoZKo0IwQDAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAd\n"
"BgNVHQ4EFgQUPeYpSJvqB8ohREom3m7e0oPQn1kwCgYIKoZIzj0EAwMDaAAwZQIxAOVpEslu28Yx\n"
"uglB4Zf4+/2a4n0Sye18ZNPLBSWLVtmg515dTguDnFt2KaAJJiFqYgIwcdK1j1zqO+F4CYWodZI7\n"
"yFz9SO8NdCKoCOJuxUnOxwy8p2Fp8fc74SrL+SvzZpA3\n"
"-----END CERTIFICATE-----\n"
"\n"
"Staat der Nederlanden EV Root CA\n"
"================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFcDCCA1igAwIBAgIEAJiWjTANBgkqhkiG9w0BAQsFADBYMQswCQYDVQQGEwJOTDEeMBwGA1UE\n"
"CgwVU3RhYXQgZGVyIE5lZGVybGFuZGVuMSkwJwYDVQQDDCBTdGFhdCBkZXIgTmVkZXJsYW5kZW4g\n"
"RVYgUm9vdCBDQTAeFw0xMDEyMDgxMTE5MjlaFw0yMjEyMDgxMTEwMjhaMFgxCzAJBgNVBAYTAk5M\n"
"MR4wHAYDVQQKDBVTdGFhdCBkZXIgTmVkZXJsYW5kZW4xKTAnBgNVBAMMIFN0YWF0IGRlciBOZWRl\n"
"cmxhbmRlbiBFViBSb290IENBMIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA48d+ifkk\n"
"SzrSM4M1LGns3Amk41GoJSt5uAg94JG6hIXGhaTK5skuU6TJJB79VWZxXSzFYGgEt9nCUiY4iKTW\n"
"O0Cmws0/zZiTs1QUWJZV1VD+hq2kY39ch/aO5ieSZxeSAgMs3NZmdO3dZ//BYY1jTw+bbRcwJu+r\n"
"0h8QoPnFfxZpgQNH7R5ojXKhTbImxrpsX23Wr9GxE46prfNeaXUmGD5BKyF/7otdBwadQ8QpCiv8\n"
"Kj6GyzyDOvnJDdrFmeK8eEEzduG/L13lpJhQDBXd4Pqcfzho0LKmeqfRMb1+ilgnQ7O6M5HTp5gV\n"
"XJrm0w912fxBmJc+qiXbj5IusHsMX/FjqTf5m3VpTCgmJdrV8hJwRVXj33NeN/UhbJCONVrJ0yPr\n"
"08C+eKxCKFhmpUZtcALXEPlLVPxdhkqHz3/KRawRWrUgUY0viEeXOcDPusBCAUCZSCELa6fS/ZbV\n"
"0b5GnUngC6agIk440ME8MLxwjyx1zNDFjFE7PZQIZCZhfbnDZY8UnCHQqv0XcgOPvZuM5l5Tnrmd\n"
"74K74bzickFbIZTTRTeU0d8JOV3nI6qaHcptqAqGhYqCvkIH1vI4gnPah1vlPNOePqc7nvQDs/nx\n"
"fRN0Av+7oeX6AHkcpmZBiFxgV6YuCcS6/ZrPpx9Aw7vMWgpVSzs4dlG4Y4uElBbmVvMCAwEAAaNC\n"
"MEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYEFP6rAJCYniT8qcwa\n"
"ivsnuL8wbqg7MA0GCSqGSIb3DQEBCwUAA4ICAQDPdyxuVr5Os7aEAJSrR8kN0nbHhp8dB9O2tLsI\n"
"eK9p0gtJ3jPFrK3CiAJ9Brc1AsFgyb/E6JTe1NOpEyVa/m6irn0F3H3zbPB+po3u2dfOWBfoqSmu\n"
"c0iH55vKbimhZF8ZE/euBhD/UcabTVUlT5OZEAFTdfETzsemQUHSv4ilf0X8rLiltTMMgsT7B/Zq\n"
"5SWEXwbKwYY5EdtYzXc7LMJMD16a4/CrPmEbUCTCwPTxGfARKbalGAKb12NMcIxHowNDXLldRqAN\n"
"b/9Zjr7dn3LDWyvfjFvO5QxGbJKyCqNMVEIYFRIYvdr8unRu/8G2oGTYqV9Vrp9canaW2HNnh/tN\n"
"f1zuacpzEPuKqf2evTY4SUmH9A4U8OmHuD+nT3pajnnUk+S7aFKErGzp85hwVXIy+TSrK0m1zSBi\n"
"5Dp6Z2Orltxtrpfs/J92VoguZs9btsmksNcFuuEnL5O7Jiqik7Ab846+HUCjuTaPPoIaGl6I6lD4\n"
"WeKDRikL40Rc4ZW2aZCaFG+XroHPaO+Zmr615+F/+PoTRxZMzG0IQOeLeG9QgkRQP2YGiqtDhFZK\n"
"DyAthg710tvSeopLzaXoTvFeJiUBWSOgftL2fiFX1ye8FVdMpEbB4IMeDExNH08GGeL5qPQ6gqGy\n"
"eUN51q1veieQA6TqJIc/2b3Z6fJfUEkc7uzXLg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"IdenTrust Commercial Root CA 1\n"
"==============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFYDCCA0igAwIBAgIQCgFCgAAAAUUjyES1AAAAAjANBgkqhkiG9w0BAQsFADBKMQswCQYDVQQG\n"
"EwJVUzESMBAGA1UEChMJSWRlblRydXN0MScwJQYDVQQDEx5JZGVuVHJ1c3QgQ29tbWVyY2lhbCBS\n"
"b290IENBIDEwHhcNMTQwMTE2MTgxMjIzWhcNMzQwMTE2MTgxMjIzWjBKMQswCQYDVQQGEwJVUzES\n"
"MBAGA1UEChMJSWRlblRydXN0MScwJQYDVQQDEx5JZGVuVHJ1c3QgQ29tbWVyY2lhbCBSb290IENB\n"
"IDEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCnUBneP5k91DNG8W9RYYKyqU+PZ4ld\n"
"hNlT3Qwo2dfw/66VQ3KZ+bVdfIrBQuExUHTRgQ18zZshq0PirK1ehm7zCYofWjK9ouuU+ehcCuz/\n"
"mNKvcbO0U59Oh++SvL3sTzIwiEsXXlfEU8L2ApeN2WIrvyQfYo3fw7gpS0l4PJNgiCL8mdo2yMKi\n"
"1CxUAGc1bnO/AljwpN3lsKImesrgNqUZFvX9t++uP0D1bVoE/c40yiTcdCMbXTMTEl3EASX2MN0C\n"
"XZ/g1Ue9tOsbobtJSdifWwLziuQkkORiT0/Br4sOdBeo0XKIanoBScy0RnnGF7HamB4HWfp1IYVl\n"
"3ZBWzvurpWCdxJ35UrCLvYf5jysjCiN2O/cz4ckA82n5S6LgTrx+kzmEB/dEcH7+B1rlsazRGMzy\n"
"NeVJSQjKVsk9+w8YfYs7wRPCTY/JTw436R+hDmrfYi7LNQZReSzIJTj0+kuniVyc0uMNOYZKdHzV\n"
"WYfCP04MXFL0PfdSgvHqo6z9STQaKPNBiDoT7uje/5kdX7rL6B7yuVBgwDHTc+XvvqDtMwt0viAg\n"
"xGds8AgDelWAf0ZOlqf0Hj7h9tgJ4TNkK2PXMl6f+cB7D3hvl7yTmvmcEpB4eoCHFddydJxVdHix\n"
"uuFucAS6T6C6aMN7/zHwcz09lCqxC0EOoP5NiGVreTO01wIDAQABo0IwQDAOBgNVHQ8BAf8EBAMC\n"
"AQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQU7UQZwNPwBovupHu+QucmVMiONnYwDQYJKoZI\n"
"hvcNAQELBQADggIBAA2ukDL2pkt8RHYZYR4nKM1eVO8lvOMIkPkp165oCOGUAFjvLi5+U1KMtlwH\n"
"6oi6mYtQlNeCgN9hCQCTrQ0U5s7B8jeUeLBfnLOic7iPBZM4zY0+sLj7wM+x8uwtLRvM7Kqas6pg\n"
"ghstO8OEPVeKlh6cdbjTMM1gCIOQ045U8U1mwF10A0Cj7oV+wh93nAbowacYXVKV7cndJZ5t+qnt\n"
"ozo00Fl72u1Q8zW/7esUTTHHYPTa8Yec4kjixsU3+wYQ+nVZZjFHKdp2mhzpgq7vmrlR94gjmmmV\n"
"YjzlVYA211QC//G5Xc7UI2/YRYRKW2XviQzdFKcgyxilJbQN+QHwotL0AMh0jqEqSI5l2xPE4iUX\n"
"feu+h1sXIFRRk0pTAwvsXcoz7WL9RccvW9xYoIA55vrX/hMUpu09lEpCdNTDd1lzzY9GvlU47/ro\n"
"kTLql1gEIt44w8y8bckzOmoKaT+gyOpyj4xjhiO9bTyWnpXgSUyqorkqG5w2gXjtw+hG4iZZRHUe\n"
"2XWJUc0QhJ1hYMtd+ZciTY6Y5uN/9lu7rs3KSoFrXgvzUeF0K+l+J6fZmUlO+KWA2yUPHGNiiskz\n"
"Z2s8EIPGrd6ozRaOjfAHN3Gf8qv8QfXBi+wAN10J5U6A7/qxXDgGpRtK4dw4LTzcqx+QGtVKnO7R\n"
"cGzM7vRX+Bi6hG6H\n"
"-----END CERTIFICATE-----\n"
"\n"
"IdenTrust Public Sector Root CA 1\n"
"=================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFZjCCA06gAwIBAgIQCgFCgAAAAUUjz0Z8AAAAAjANBgkqhkiG9w0BAQsFADBNMQswCQYDVQQG\n"
"EwJVUzESMBAGA1UEChMJSWRlblRydXN0MSowKAYDVQQDEyFJZGVuVHJ1c3QgUHVibGljIFNlY3Rv\n"
"ciBSb290IENBIDEwHhcNMTQwMTE2MTc1MzMyWhcNMzQwMTE2MTc1MzMyWjBNMQswCQYDVQQGEwJV\n"
"UzESMBAGA1UEChMJSWRlblRydXN0MSowKAYDVQQDEyFJZGVuVHJ1c3QgUHVibGljIFNlY3RvciBS\n"
"b290IENBIDEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQC2IpT8pEiv6EdrCvsnduTy\n"
"P4o7ekosMSqMjbCpwzFrqHd2hCa2rIFCDQjrVVi7evi8ZX3yoG2LqEfpYnYeEe4IFNGyRBb06tD6\n"
"Hi9e28tzQa68ALBKK0CyrOE7S8ItneShm+waOh7wCLPQ5CQ1B5+ctMlSbdsHyo+1W/CD80/HLaXI\n"
"rcuVIKQxKFdYWuSNG5qrng0M8gozOSI5Cpcu81N3uURF/YTLNiCBWS2ab21ISGHKTN9T0a9SvESf\n"
"qy9rg3LvdYDaBjMbXcjaY8ZNzaxmMc3R3j6HEDbhuaR672BQssvKplbgN6+rNBM5Jeg5ZuSYeqoS\n"
"mJxZZoY+rfGwyj4GD3vwEUs3oERte8uojHH01bWRNszwFcYr3lEXsZdMUD2xlVl8BX0tIdUAvwFn\n"
"ol57plzy9yLxkA2T26pEUWbMfXYD62qoKjgZl3YNa4ph+bz27nb9cCvdKTz4Ch5bQhyLVi9VGxyh\n"
"LrXHFub4qjySjmm2AcG1hp2JDws4lFTo6tyePSW8Uybt1as5qsVATFSrsrTZ2fjXctscvG29ZV/v\n"
"iDUqZi/u9rNl8DONfJhBaUYPQxxp+pu10GFqzcpL2UyQRqsVWaFHVCkugyhfHMKiq3IXAAaOReyL\n"
"4jM9f9oZRORicsPfIsbyVtTdX5Vy7W1f90gDW/3FKqD2cyOEEBsB5wIDAQABo0IwQDAOBgNVHQ8B\n"
"Af8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQU43HgntinQtnbcZFrlJPrw6PRFKMw\n"
"DQYJKoZIhvcNAQELBQADggIBAEf63QqwEZE4rU1d9+UOl1QZgkiHVIyqZJnYWv6IAcVYpZmxI1Qj\n"
"t2odIFflAWJBF9MJ23XLblSQdf4an4EKwt3X9wnQW3IV5B4Jaj0z8yGa5hV+rVHVDRDtfULAj+7A\n"
"mgjVQdZcDiFpboBhDhXAuM/FSRJSzL46zNQuOAXeNf0fb7iAaJg9TaDKQGXSc3z1i9kKlT/YPyNt\n"
"GtEqJBnZhbMX73huqVjRI9PHE+1yJX9dsXNw0H8GlwmEKYBhHfpe/3OsoOOJuBxxFcbeMX8S3OFt\n"
"m6/n6J91eEyrRjuazr8FGF1NFTwWmhlQBJqymm9li1JfPFgEKCXAZmExfrngdbkaqIHWchezxQMx\n"
"NRF4eKLg6TCMf4DfWN88uieW4oA0beOY02QnrEh+KHdcxiVhJfiFDGX6xDIvpZgF5PgLZxYWxoK4\n"
"Mhn5+bl53B/N66+rDt0b20XkeucC4pVd/GnwU2lhlXV5C15V5jgclKlZM57IcXR5f1GJtshquDDI\n"
"ajjDbp7hNxbqBWJMWxJH7ae0s1hWx0nzfxJoCTFx8G34Tkf71oXuxVhAGaQdp/lLQzfcaFpPz+vC\n"
"ZHTetBXZ9FRUGi8c15dxVJCO2SCdUyt/q4/i6jC8UDfv8Ue1fXwsBOxonbRJRBD0ckscZOf85muQ\n"
"3Wl9af0AVqW3rLatt8o+Ae+c\n"
"-----END CERTIFICATE-----\n"
"\n"
"Entrust Root Certification Authority - G2\n"
"=========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEPjCCAyagAwIBAgIESlOMKDANBgkqhkiG9w0BAQsFADCBvjELMAkGA1UEBhMCVVMxFjAUBgNV\n"
"BAoTDUVudHJ1c3QsIEluYy4xKDAmBgNVBAsTH1NlZSB3d3cuZW50cnVzdC5uZXQvbGVnYWwtdGVy\n"
"bXMxOTA3BgNVBAsTMChjKSAyMDA5IEVudHJ1c3QsIEluYy4gLSBmb3IgYXV0aG9yaXplZCB1c2Ug\n"
"b25seTEyMDAGA1UEAxMpRW50cnVzdCBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRzIw\n"
"HhcNMDkwNzA3MTcyNTU0WhcNMzAxMjA3MTc1NTU0WjCBvjELMAkGA1UEBhMCVVMxFjAUBgNVBAoT\n"
"DUVudHJ1c3QsIEluYy4xKDAmBgNVBAsTH1NlZSB3d3cuZW50cnVzdC5uZXQvbGVnYWwtdGVybXMx\n"
"OTA3BgNVBAsTMChjKSAyMDA5IEVudHJ1c3QsIEluYy4gLSBmb3IgYXV0aG9yaXplZCB1c2Ugb25s\n"
"eTEyMDAGA1UEAxMpRW50cnVzdCBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRzIwggEi\n"
"MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC6hLZy254Ma+KZ6TABp3bqMriVQRrJ2mFOWHLP\n"
"/vaCeb9zYQYKpSfYs1/TRU4cctZOMvJyig/3gxnQaoCAAEUesMfnmr8SVycco2gvCoe9amsOXmXz\n"
"HHfV1IWNcCG0szLni6LVhjkCsbjSR87kyUnEO6fe+1R9V77w6G7CebI6C1XiUJgWMhNcL3hWwcKU\n"
"s/Ja5CeanyTXxuzQmyWC48zCxEXFjJd6BmsqEZ+pCm5IO2/b1BEZQvePB7/1U1+cPvQXLOZprE4y\n"
"TGJ36rfo5bs0vBmLrpxR57d+tVOxMyLlbc9wPBr64ptntoP0jaWvYkxN4FisZDQSA/i2jZRjJKRx\n"
"AgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBRqciZ6\n"
"0B7vfec7aVHUbI2fkBJmqzANBgkqhkiG9w0BAQsFAAOCAQEAeZ8dlsa2eT8ijYfThwMEYGprmi5Z\n"
"iXMRrEPR9RP/jTkrwPK9T3CMqS/qF8QLVJ7UG5aYMzyorWKiAHarWWluBh1+xLlEjZivEtRh2woZ\n"
"Rkfz6/djwUAFQKXSt/S1mja/qYh2iARVBCuch38aNzx+LaUa2NSJXsq9rD1s2G2v1fN2D807iDgi\n"
"nWyTmsQ9v4IbZT+mD12q/OWyFcq1rca8PdCE6OoGcrBNOTJ4vz4RnAuknZoh8/CbCzB428Hch0P+\n"
"vGOaysXCHMnHjf87ElgI5rY97HosTvuDls4MPGmHVHOkc8KT/1EQrBVUAdj8BbGJoX90g5pJ19xO\n"
"e4pIb4tF9g==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Entrust Root Certification Authority - EC1\n"
"==========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIC+TCCAoCgAwIBAgINAKaLeSkAAAAAUNCR+TAKBggqhkjOPQQDAzCBvzELMAkGA1UEBhMCVVMx\n"
"FjAUBgNVBAoTDUVudHJ1c3QsIEluYy4xKDAmBgNVBAsTH1NlZSB3d3cuZW50cnVzdC5uZXQvbGVn\n"
"YWwtdGVybXMxOTA3BgNVBAsTMChjKSAyMDEyIEVudHJ1c3QsIEluYy4gLSBmb3IgYXV0aG9yaXpl\n"
"ZCB1c2Ugb25seTEzMDEGA1UEAxMqRW50cnVzdCBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5\n"
"IC0gRUMxMB4XDTEyMTIxODE1MjUzNloXDTM3MTIxODE1NTUzNlowgb8xCzAJBgNVBAYTAlVTMRYw\n"
"FAYDVQQKEw1FbnRydXN0LCBJbmMuMSgwJgYDVQQLEx9TZWUgd3d3LmVudHJ1c3QubmV0L2xlZ2Fs\n"
"LXRlcm1zMTkwNwYDVQQLEzAoYykgMjAxMiBFbnRydXN0LCBJbmMuIC0gZm9yIGF1dGhvcml6ZWQg\n"
"dXNlIG9ubHkxMzAxBgNVBAMTKkVudHJ1c3QgUm9vdCBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eSAt\n"
"IEVDMTB2MBAGByqGSM49AgEGBSuBBAAiA2IABIQTydC6bUF74mzQ61VfZgIaJPRbiWlH47jCffHy\n"
"AsWfoPZb1YsGGYZPUxBtByQnoaD41UcZYUx9ypMn6nQM72+WCf5j7HBdNq1nd67JnXxVRDqiY1Ef\n"
"9eNi1KlHBz7MIKNCMEAwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0OBBYE\n"
"FLdj5xrdjekIplWDpOBqUEFlEUJJMAoGCCqGSM49BAMDA2cAMGQCMGF52OVCR98crlOZF7ZvHH3h\n"
"vxGU0QOIdeSNiaSKd0bebWHvAvX7td/M/k7//qnmpwIwW5nXhTcGtXsI/esni0qU+eH6p44mCOh8\n"
"kmhtc9hvJqwhAriZtyZBWyVgrtBIGu4G\n"
"-----END CERTIFICATE-----\n"
"\n"
"CFCA EV ROOT\n"
"============\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"OISTE WISeKey Global Root GB CA\n"
"===============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDtTCCAp2gAwIBAgIQdrEgUnTwhYdGs/gjGvbCwDANBgkqhkiG9w0BAQsFADBtMQswCQYDVQQG\n"
"EwJDSDEQMA4GA1UEChMHV0lTZUtleTEiMCAGA1UECxMZT0lTVEUgRm91bmRhdGlvbiBFbmRvcnNl\n"
"ZDEoMCYGA1UEAxMfT0lTVEUgV0lTZUtleSBHbG9iYWwgUm9vdCBHQiBDQTAeFw0xNDEyMDExNTAw\n"
"MzJaFw0zOTEyMDExNTEwMzFaMG0xCzAJBgNVBAYTAkNIMRAwDgYDVQQKEwdXSVNlS2V5MSIwIAYD\n"
"VQQLExlPSVNURSBGb3VuZGF0aW9uIEVuZG9yc2VkMSgwJgYDVQQDEx9PSVNURSBXSVNlS2V5IEds\n"
"b2JhbCBSb290IEdCIENBMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2Be3HEokKtaX\n"
"scriHvt9OO+Y9bI5mE4nuBFde9IllIiCFSZqGzG7qFshISvYD06fWvGxWuR51jIjK+FTzJlFXHtP\n"
"rby/h0oLS5daqPZI7H17Dc0hBt+eFf1Biki3IPShehtX1F1Q/7pn2COZH8g/497/b1t3sWtuuMlk\n"
"9+HKQUYOKXHQuSP8yYFfTvdv37+ErXNku7dCjmn21HYdfp2nuFeKUWdy19SouJVUQHMD9ur06/4o\n"
"Qnc/nSMbsrY9gBQHTC5P99UKFg29ZkM3fiNDecNAhvVMKdqOmq0NpQSHiB6F4+lT1ZvIiwNjeOvg\n"
"GUpuuy9rM2RYk61pv48b74JIxwIDAQABo1EwTzALBgNVHQ8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB\n"
"/zAdBgNVHQ4EFgQUNQ/INmNe4qPs+TtmFc5RUuORmj0wEAYJKwYBBAGCNxUBBAMCAQAwDQYJKoZI\n"
"hvcNAQELBQADggEBAEBM+4eymYGQfp3FsLAmzYh7KzKNbrghcViXfa43FK8+5/ea4n32cZiZBKpD\n"
"dHij40lhPnOMTZTg+XHEthYOU3gf1qKHLwI5gSk8rxWYITD+KJAAjNHhy/peyP34EEY7onhCkRd0\n"
"VQreUGdNZtGn//3ZwLWoo4rOZvUPQ82nK1d7Y0Zqqi5S2PTt4W2tKZB4SLrhI6qjiey1q5bAtEui\n"
"HZeeevJuQHHfaPFlTc58Bd9TZaml8LGXBHAVRgOY1NK/VLSgWH1Sb9pWJmLU2NuJMW8c8CLC02Ic\n"
"Nc1MaRVUGpCY3useX8p3x8uOPUNpnJpY0CQ73xtAln41rYHHTnG6iBM=\n"
"-----END CERTIFICATE-----\n"
"\n"
"SZAFIR ROOT CA2\n"
"===============\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDcjCCAlqgAwIBAgIUPopdB+xV0jLVt+O2XwHrLdzk1uQwDQYJKoZIhvcNAQELBQAwUTELMAkG\n"
"A1UEBhMCUEwxKDAmBgNVBAoMH0tyYWpvd2EgSXpiYSBSb3psaWN6ZW5pb3dhIFMuQS4xGDAWBgNV\n"
"BAMMD1NaQUZJUiBST09UIENBMjAeFw0xNTEwMTkwNzQzMzBaFw0zNTEwMTkwNzQzMzBaMFExCzAJ\n"
"BgNVBAYTAlBMMSgwJgYDVQQKDB9LcmFqb3dhIEl6YmEgUm96bGljemVuaW93YSBTLkEuMRgwFgYD\n"
"VQQDDA9TWkFGSVIgUk9PVCBDQTIwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC3vD5Q\n"
"qEvNQLXOYeeWyrSh2gwisPq1e3YAd4wLz32ohswmUeQgPYUM1ljj5/QqGJ3a0a4m7utT3PSQ1hNK\n"
"DJA8w/Ta0o4NkjrcsbH/ON7Dui1fgLkCvUqdGw+0w8LBZwPd3BucPbOw3gAeqDRHu5rr/gsUvTaE\n"
"2g0gv/pby6kWIK05YO4vdbbnl5z5Pv1+TW9NL++IDWr63fE9biCloBK0TXC5ztdyO4mTp4CEHCdJ\n"
"ckm1/zuVnsHMyAHs6A6KCpbns6aH5db5BSsNl0BwPLqsdVqc1U2dAgrSS5tmS0YHF2Wtn2yIANwi\n"
"ieDhZNRnvDF5YTy7ykHNXGoAyDw4jlivAgMBAAGjQjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0P\n"
"AQH/BAQDAgEGMB0GA1UdDgQWBBQuFqlKGLXLzPVvUPMjX/hd56zwyDANBgkqhkiG9w0BAQsFAAOC\n"
"AQEAtXP4A9xZWx126aMqe5Aosk3AM0+qmrHUuOQn/6mWmc5G4G18TKI4pAZw8PRBEew/R40/cof5\n"
"O/2kbytTAOD/OblqBw7rHRz2onKQy4I9EYKL0rufKq8h5mOGnXkZ7/e7DDWQw4rtTw/1zBLZpD67\n"
"oPwglV9PJi8RI4NOdQcPv5vRtB3pEAT+ymCPoky4rc/hkA/NrgrHXXu3UNLUYfrVFdvXn4dRVOul\n"
"4+vJhaAlIDf7js4MNIThPIGyd05DpYhfhmehPea0XGG2Ptv+tyjFogeutcrKjSoS75ftwjCkySp6\n"
"+/NNIxuZMzSgLvWpCz/UXeHPhJ/iGcJfitYgHuNztw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Certum Trusted Network CA 2\n"
"===========================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIF0jCCA7qgAwIBAgIQIdbQSk8lD8kyN/yqXhKN6TANBgkqhkiG9w0BAQ0FADCBgDELMAkGA1UE\n"
"BhMCUEwxIjAgBgNVBAoTGVVuaXpldG8gVGVjaG5vbG9naWVzIFMuQS4xJzAlBgNVBAsTHkNlcnR1\n"
"bSBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTEkMCIGA1UEAxMbQ2VydHVtIFRydXN0ZWQgTmV0d29y\n"
"ayBDQSAyMCIYDzIwMTExMDA2MDgzOTU2WhgPMjA0NjEwMDYwODM5NTZaMIGAMQswCQYDVQQGEwJQ\n"
"TDEiMCAGA1UEChMZVW5pemV0byBUZWNobm9sb2dpZXMgUy5BLjEnMCUGA1UECxMeQ2VydHVtIENl\n"
"cnRpZmljYXRpb24gQXV0aG9yaXR5MSQwIgYDVQQDExtDZXJ0dW0gVHJ1c3RlZCBOZXR3b3JrIENB\n"
"IDIwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQC9+Xj45tWADGSdhhuWZGc/IjoedQF9\n"
"7/tcZ4zJzFxrqZHmuULlIEub2pt7uZld2ZuAS9eEQCsn0+i6MLs+CRqnSZXvK0AkwpfHp+6bJe+o\n"
"CgCXhVqqndwpyeI1B+twTUrWwbNWuKFBOJvR+zF/j+Bf4bE/D44WSWDXBo0Y+aomEKsq09DRZ40b\n"
"Rr5HMNUuctHFY9rnY3lEfktjJImGLjQ/KUxSiyqnwOKRKIm5wFv5HdnnJ63/mgKXwcZQkpsCLL2p\n"
"uTRZCr+ESv/f/rOf69me4Jgj7KZrdxYq28ytOxykh9xGc14ZYmhFV+SQgkK7QtbwYeDBoz1mo130\n"
"GO6IyY0XRSmZMnUCMe4pJshrAua1YkV/NxVaI2iJ1D7eTiew8EAMvE0Xy02isx7QBlrd9pPPV3WZ\n"
"9fqGGmd4s7+W/jTcvedSVuWz5XV710GRBdxdaeOVDUO5/IOWOZV7bIBaTxNyxtd9KXpEulKkKtVB\n"
"Rgkg/iKgtlswjbyJDNXXcPiHUv3a76xRLgezTv7QCdpw75j6VuZt27VXS9zlLCUVyJ4ueE742pye\n"
"hizKV/Ma5ciSixqClnrDvFASadgOWkaLOusm+iPJtrCBvkIApPjW/jAux9JG9uWOdf3yzLnQh1vM\n"
"BhBgu4M1t15n3kfsmUjxpKEV/q2MYo45VU85FrmxY53/twIDAQABo0IwQDAPBgNVHRMBAf8EBTAD\n"
"AQH/MB0GA1UdDgQWBBS2oVQ5AsOgP46KvPrU+Bym0ToO/TAOBgNVHQ8BAf8EBAMCAQYwDQYJKoZI\n"
"hvcNAQENBQADggIBAHGlDs7k6b8/ONWJWsQCYftMxRQXLYtPU2sQF/xlhMcQSZDe28cmk4gmb3DW\n"
"Al45oPePq5a1pRNcgRRtDoGCERuKTsZPpd1iHkTfCVn0W3cLN+mLIMb4Ck4uWBzrM9DPhmDJ2vuA\n"
"L55MYIR4PSFk1vtBHxgP58l1cb29XN40hz5BsA72udY/CROWFC/emh1auVbONTqwX3BNXuMp8SMo\n"
"clm2q8KMZiYcdywmdjWLKKdpoPk79SPdhRB0yZADVpHnr7pH1BKXESLjokmUbOe3lEu6LaTaM4tM\n"
"pkT/WjzGHWTYtTHkpjx6qFcL2+1hGsvxznN3Y6SHb0xRONbkX8eftoEq5IVIeVheO/jbAoJnwTnb\n"
"w3RLPTYe+SmTiGhbqEQZIfCn6IENLOiTNrQ3ssqwGyZ6miUfmpqAnksqP/ujmv5zMnHCnsZy4Ypo\n"
"J/HkD7TETKVhk/iXEAcqMCWpuchxuO9ozC1+9eB+D4Kob7a6bINDd82Kkhehnlt4Fj1F4jNy3eFm\n"
"ypnTycUm/Q1oBEauttmbjL4ZvrHG8hnjXALKLNhvSgfZyTXaQHXyxKcZb55CEJh15pWLYLztxRLX\n"
"is7VmFxWlgPF7ncGNf/P5O4/E2Hu29othfDNrp2yGAlFw5Khchf8R7agCyzxxN5DaAhqXzvwdmP7\n"
"zAYspsbiDrW5viSP\n"
"-----END CERTIFICATE-----\n"
"\n"
"Hellenic Academic and Research Institutions RootCA 2015\n"
"=======================================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIGCzCCA/OgAwIBAgIBADANBgkqhkiG9w0BAQsFADCBpjELMAkGA1UEBhMCR1IxDzANBgNVBAcT\n"
"BkF0aGVuczFEMEIGA1UEChM7SGVsbGVuaWMgQWNhZGVtaWMgYW5kIFJlc2VhcmNoIEluc3RpdHV0\n"
"aW9ucyBDZXJ0LiBBdXRob3JpdHkxQDA+BgNVBAMTN0hlbGxlbmljIEFjYWRlbWljIGFuZCBSZXNl\n"
"YXJjaCBJbnN0aXR1dGlvbnMgUm9vdENBIDIwMTUwHhcNMTUwNzA3MTAxMTIxWhcNNDAwNjMwMTAx\n"
"MTIxWjCBpjELMAkGA1UEBhMCR1IxDzANBgNVBAcTBkF0aGVuczFEMEIGA1UEChM7SGVsbGVuaWMg\n"
"QWNhZGVtaWMgYW5kIFJlc2VhcmNoIEluc3RpdHV0aW9ucyBDZXJ0LiBBdXRob3JpdHkxQDA+BgNV\n"
"BAMTN0hlbGxlbmljIEFjYWRlbWljIGFuZCBSZXNlYXJjaCBJbnN0aXR1dGlvbnMgUm9vdENBIDIw\n"
"MTUwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQDC+Kk/G4n8PDwEXT2QNrCROnk8Zlrv\n"
"bTkBSRq0t89/TSNTt5AA4xMqKKYx8ZEA4yjsriFBzh/a/X0SWwGDD7mwX5nh8hKDgE0GPt+sr+eh\n"
"iGsxr/CL0BgzuNtFajT0AoAkKAoCFZVedioNmToUW/bLy1O8E00BiDeUJRtCvCLYjqOWXjrZMts+\n"
"6PAQZe104S+nfK8nNLspfZu2zwnI5dMK/IhlZXQK3HMcXM1AsRzUtoSMTFDPaI6oWa7CJ06CojXd\n"
"FPQf/7J31Ycvqm59JCfnxssm5uX+Zwdj2EUN3TpZZTlYepKZcj2chF6IIbjV9Cz82XBST3i4vTwr\n"
"i5WY9bPRaM8gFH5MXF/ni+X1NYEZN9cRCLdmvtNKzoNXADrDgfgXy5I2XdGj2HUb4Ysn6npIQf1F\n"
"GQatJ5lOwXBH3bWfgVMS5bGMSF0xQxfjjMZ6Y5ZLKTBOhE5iGV48zpeQpX8B653g+IuJ3SWYPZK2\n"
"fu/Z8VFRfS0myGlZYeCsargqNhEEelC9MoS+L9xy1dcdFkfkR2YgP/SWxa+OAXqlD3pk9Q0Yh9mu\n"
"iNX6hME6wGkoLfINaFGq46V3xqSQDqE3izEjR8EJCOtu93ib14L8hCCZSRm2Ekax+0VVFqmjZayc\n"
"Bw/qa9wfLgZy7IaIEuQt218FL+TwA9MmM+eAws1CoRc0CwIDAQABo0IwQDAPBgNVHRMBAf8EBTAD\n"
"AQH/MA4GA1UdDwEB/wQEAwIBBjAdBgNVHQ4EFgQUcRVnyMjJvXVdctA4GGqd83EkVAswDQYJKoZI\n"
"hvcNAQELBQADggIBAHW7bVRLqhBYRjTyYtcWNl0IXtVsyIe9tC5G8jH4fOpCtZMWVdyhDBKg2mF+\n"
"D1hYc2Ryx+hFjtyp8iY/xnmMsVMIM4GwVhO+5lFc2JsKT0ucVlMC6U/2DWDqTUJV6HwbISHTGzrM\n"
"d/K4kPFox/la/vot9L/J9UUbzjgQKjeKeaO04wlshYaT/4mWJ3iBj2fjRnRUjtkNaeJK9E10A/+y\n"
"d+2VZ5fkscWrv2oj6NSU4kQoYsRL4vDY4ilrGnB+JGGTe08DMiUNRSQrlrRGar9KC/eaj8GsGsVn\n"
"82800vpzY4zvFrCopEYq+OsS7HK07/grfoxSwIuEVPkvPuNVqNxmsdnhX9izjFk0WaSrT2y7Hxjb\n"
"davYy5LNlDhhDgcGH0tGEPEVvo2FXDtKK4F5D7Rpn0lQl033DlZdwJVqwjbDG2jJ9SrcR5q+ss7F\n"
"Jej6A7na+RZukYT1HCjI/CbM1xyQVqdfbzoEvM14iQuODy+jqk+iGxI9FghAD/FGTNeqewjBCvVt\n"
"J94Cj8rDtSvK6evIIVM4pcw72Hc3MKJP2W/R8kCtQXoXxdZKNYm3QdV8hn9VTYNKpXMgwDqvkPGa\n"
"JI7ZjnHKe7iG2rKPmT4dEw0SEe7Uq/DpFXYC5ODfqiAeW2GFZECpkJcNrVPSWh2HagCXZWK0vm9q\n"
"p/UsQu0yrbYhnr68\n"
"-----END CERTIFICATE-----\n"
"\n"
"Hellenic Academic and Research Institutions ECC RootCA 2015\n"
"===========================================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICwzCCAkqgAwIBAgIBADAKBggqhkjOPQQDAjCBqjELMAkGA1UEBhMCR1IxDzANBgNVBAcTBkF0\n"
"aGVuczFEMEIGA1UEChM7SGVsbGVuaWMgQWNhZGVtaWMgYW5kIFJlc2VhcmNoIEluc3RpdHV0aW9u\n"
"cyBDZXJ0LiBBdXRob3JpdHkxRDBCBgNVBAMTO0hlbGxlbmljIEFjYWRlbWljIGFuZCBSZXNlYXJj\n"
"aCBJbnN0aXR1dGlvbnMgRUNDIFJvb3RDQSAyMDE1MB4XDTE1MDcwNzEwMzcxMloXDTQwMDYzMDEw\n"
"MzcxMlowgaoxCzAJBgNVBAYTAkdSMQ8wDQYDVQQHEwZBdGhlbnMxRDBCBgNVBAoTO0hlbGxlbmlj\n"
"IEFjYWRlbWljIGFuZCBSZXNlYXJjaCBJbnN0aXR1dGlvbnMgQ2VydC4gQXV0aG9yaXR5MUQwQgYD\n"
"VQQDEztIZWxsZW5pYyBBY2FkZW1pYyBhbmQgUmVzZWFyY2ggSW5zdGl0dXRpb25zIEVDQyBSb290\n"
"Q0EgMjAxNTB2MBAGByqGSM49AgEGBSuBBAAiA2IABJKgQehLgoRc4vgxEZmGZE4JJS+dQS8KrjVP\n"
"dJWyUWRrjWvmP3CV8AVER6ZyOFB2lQJajq4onvktTpnvLEhvTCUp6NFxW98dwXU3tNf6e3pCnGoK\n"
"Vlp8aQuqgAkkbH7BRqNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0O\n"
"BBYEFLQiC4KZJAEOnLvkDv2/+5cgk5kqMAoGCCqGSM49BAMCA2cAMGQCMGfOFmI4oqxiRaeplSTA\n"
"GiecMjvAwNW6qef4BENThe5SId6d9SWDPp5YSy/XZxMOIQIwBeF1Ad5o7SofTUwJCA3sS61kFyjn\n"
"dc5FZXIhF8siQQ6ME5g4mlRtm8rifOoCWCKR\n"
"-----END CERTIFICATE-----\n"
"\n"
"ISRG Root X1\n"
"============\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAwTzELMAkGA1UE\n"
"BhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2VhcmNoIEdyb3VwMRUwEwYDVQQD\n"
"EwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQG\n"
"EwJVUzEpMCcGA1UEChMgSW50ZXJuZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMT\n"
"DElTUkcgUm9vdCBYMTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54r\n"
"Vygch77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+0TM8ukj1\n"
"3Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6UA5/TR5d8mUgjU+g4rk8K\n"
"b4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sWT8KOEUt+zwvo/7V3LvSye0rgTBIlDHCN\n"
"Aymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyHB5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ\n"
"4Q7e2RCOFvu396j3x+UCB5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf\n"
"1b0SHzUvKBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWnOlFu\n"
"hjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTnjh8BCNAw1FtxNrQH\n"
"usEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbwqHyGO0aoSCqI3Haadr8faqU9GY/r\n"
"OPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CIrU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4G\n"
"A1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY\n"
"9umbbjANBgkqhkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n"
"ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ3BebYhtF8GaV\n"
"0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KKNFtY2PwByVS5uCbMiogziUwt\n"
"hDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJw\n"
"TdwJx4nLCgdNbOhdjsnvzqvHu7UrTkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nx\n"
"e5AW0wdeRlN8NwdCjNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZA\n"
"JzVcoyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq4RgqsahD\n"
"YVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPAmRGunUHBcnWEvgJBQl9n\n"
"JEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57demyPxgcYxn/eR44/KJ4EBs+lVDR3veyJ\n"
"m+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n"
"-----END CERTIFICATE-----\n"
"\n"
"AC RAIZ FNMT-RCM\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFgzCCA2ugAwIBAgIPXZONMGc2yAYdGsdUhGkHMA0GCSqGSIb3DQEBCwUAMDsxCzAJBgNVBAYT\n"
"AkVTMREwDwYDVQQKDAhGTk1ULVJDTTEZMBcGA1UECwwQQUMgUkFJWiBGTk1ULVJDTTAeFw0wODEw\n"
"MjkxNTU5NTZaFw0zMDAxMDEwMDAwMDBaMDsxCzAJBgNVBAYTAkVTMREwDwYDVQQKDAhGTk1ULVJD\n"
"TTEZMBcGA1UECwwQQUMgUkFJWiBGTk1ULVJDTTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoC\n"
"ggIBALpxgHpMhm5/yBNtwMZ9HACXjywMI7sQmkCpGreHiPibVmr75nuOi5KOpyVdWRHbNi63URcf\n"
"qQgfBBckWKo3Shjf5TnUV/3XwSyRAZHiItQDwFj8d0fsjz50Q7qsNI1NOHZnjrDIbzAzWHFctPVr\n"
"btQBULgTfmxKo0nRIBnuvMApGGWn3v7v3QqQIecaZ5JCEJhfTzC8PhxFtBDXaEAUwED653cXeuYL\n"
"j2VbPNmaUtu1vZ5Gzz3rkQUCwJaydkxNEJY7kvqcfw+Z374jNUUeAlz+taibmSXaXvMiwzn15Cou\n"
"08YfxGyqxRxqAQVKL9LFwag0Jl1mpdICIfkYtwb1TplvqKtMUejPUBjFd8g5CSxJkjKZqLsXF3mw\n"
"WsXmo8RZZUc1g16p6DULmbvkzSDGm0oGObVo/CK67lWMK07q87Hj/LaZmtVC+nFNCM+HHmpxffnT\n"
"tOmlcYF7wk5HlqX2doWjKI/pgG6BU6VtX7hI+cL5NqYuSf+4lsKMB7ObiFj86xsc3i1w4peSMKGJ\n"
"47xVqCfWS+2QrYv6YyVZLag13cqXM7zlzced0ezvXg5KkAYmY6252TUtB7p2ZSysV4999AeU14EC\n"
"ll2jB0nVetBX+RvnU0Z1qrB5QstocQjpYL05ac70r8NWQMetUqIJ5G+GR4of6ygnXYMgrwTJbFaa\n"
"i0b1AgMBAAGjgYMwgYAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYE\n"
"FPd9xf3E6Jobd2Sn9R2gzL+HYJptMD4GA1UdIAQ3MDUwMwYEVR0gADArMCkGCCsGAQUFBwIBFh1o\n"
"dHRwOi8vd3d3LmNlcnQuZm5tdC5lcy9kcGNzLzANBgkqhkiG9w0BAQsFAAOCAgEAB5BK3/MjTvDD\n"
"nFFlm5wioooMhfNzKWtN/gHiqQxjAb8EZ6WdmF/9ARP67Jpi6Yb+tmLSbkyU+8B1RXxlDPiyN8+s\n"
"D8+Nb/kZ94/sHvJwnvDKuO+3/3Y3dlv2bojzr2IyIpMNOmqOFGYMLVN0V2Ue1bLdI4E7pWYjJ2cJ\n"
"j+F3qkPNZVEI7VFY/uY5+ctHhKQV8Xa7pO6kO8Rf77IzlhEYt8llvhjho6Tc+hj507wTmzl6NLrT\n"
"Qfv6MooqtyuGC2mDOL7Nii4LcK2NJpLuHvUBKwrZ1pebbuCoGRw6IYsMHkCtA+fdZn71uSANA+iW\n"
"+YJF1DngoABd15jmfZ5nc8OaKveri6E6FO80vFIOiZiaBECEHX5FaZNXzuvO+FB8TxxuBEOb+dY7\n"
"Ixjp6o7RTUaN8Tvkasq6+yO3m/qZASlaWFot4/nUbQ4mrcFuNLwy+AwF+mWj2zs3gyLp1txyM/1d\n"
"8iC9djwj2ij3+RvrWWTV3F9yfiD8zYm1kGdNYno/Tq0dwzn+evQoFt9B9kiABdcPUXmsEKvU7ANm\n"
"5mqwujGSQkBqvjrTcuFqN1W8rB2Vt2lh8kORdOag0wokRqEIr9baRRmW1FMdW4R58MD3R++Lj8UG\n"
"rp1MYp3/RgT408m2ECVAdf4WqslKYIYvuu8wd+RU4riEmViAqhOLUTpPSPaLtrM=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Amazon Root CA 1\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsFADA5MQswCQYD\n"
"VQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24gUm9vdCBDQSAxMB4XDTE1\n"
"MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTELMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpv\n"
"bjEZMBcGA1UEAxMQQW1hem9uIFJvb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC\n"
"ggEBALJ4gHHKeNXjca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgH\n"
"FzZM9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qwIFAGbHrQ\n"
"gLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6VOujw5H5SNz/0egwLX0t\n"
"dHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L93FcXmn/6pUCyziKrlA4b9v7LWIbxcce\n"
"VOF34GfID5yHI9Y/QCB/IIDEgEw+OyQmjgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB\n"
"/zAOBgNVHQ8BAf8EBAMCAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3\n"
"DQEBCwUAA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDIU5PM\n"
"CCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUsN+gDS63pYaACbvXy\n"
"8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vvo/ufQJVtMVT8QtPHRh8jrdkPSHCa\n"
"2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2\n"
"xJNDd2ZhwLnoQdeXeGADbkpyrqXRfboQnoZsG4q5WTP468SQvvG5\n"
"-----END CERTIFICATE-----\n"
"\n"
"Amazon Root CA 2\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFQTCCAymgAwIBAgITBmyf0pY1hp8KD+WGePhbJruKNzANBgkqhkiG9w0BAQwFADA5MQswCQYD\n"
"VQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24gUm9vdCBDQSAyMB4XDTE1\n"
"MDUyNjAwMDAwMFoXDTQwMDUyNjAwMDAwMFowOTELMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpv\n"
"bjEZMBcGA1UEAxMQQW1hem9uIFJvb3QgQ0EgMjCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoC\n"
"ggIBAK2Wny2cSkxKgXlRmeyKy2tgURO8TW0G/LAIjd0ZEGrHJgw12MBvIITplLGbhQPDW9tK6Mj4\n"
"kHbZW0/jTOgGNk3Mmqw9DJArktQGGWCsN0R5hYGCrVo34A3MnaZMUnbqQ523BNFQ9lXg1dKmSYXp\n"
"N+nKfq5clU1Imj+uIFptiJXZNLhSGkOQsL9sBbm2eLfq0OQ6PBJTYv9K8nu+NQWpEjTj82R0Yiw9\n"
"AElaKP4yRLuH3WUnAnE72kr3H9rN9yFVkE8P7K6C4Z9r2UXTu/Bfh+08LDmG2j/e7HJV63mjrdvd\n"
"fLC6HM783k81ds8P+HgfajZRRidhW+mez/CiVX18JYpvL7TFz4QuK/0NURBs+18bvBt+xa47mAEx\n"
"kv8LV/SasrlX6avvDXbR8O70zoan4G7ptGmh32n2M8ZpLpcTnqWHsFcQgTfJU7O7f/aS0ZzQGPSS\n"
"btqDT6ZjmUyl+17vIWR6IF9sZIUVyzfpYgwLKhbcAS4y2j5L9Z469hdAlO+ekQiG+r5jqFoz7Mt0\n"
"Q5X5bGlSNscpb/xVA1wf+5+9R+vnSUeVC06JIglJ4PVhHvG/LopyboBZ/1c6+XUyo05f7O0oYtlN\n"
"c/LMgRdg7c3r3NunysV+Ar3yVAhU/bQtCSwXVEqY0VThUWcI0u1ufm8/0i2BWSlmy5A5lREedCf+\n"
"3euvAgMBAAGjQjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBSw\n"
"DPBMMPQFWAJI/TPlUq9LhONmUjANBgkqhkiG9w0BAQwFAAOCAgEAqqiAjw54o+Ci1M3m9Zh6O+oA\n"
"A7CXDpO8Wqj2LIxyh6mx/H9z/WNxeKWHWc8w4Q0QshNabYL1auaAn6AFC2jkR2vHat+2/XcycuUY\n"
"+gn0oJMsXdKMdYV2ZZAMA3m3MSNjrXiDCYZohMr/+c8mmpJ5581LxedhpxfL86kSk5Nrp+gvU5LE\n"
"YFiwzAJRGFuFjWJZY7attN6a+yb3ACfAXVU3dJnJUH/jWS5E4ywl7uxMMne0nxrpS10gxdr9HIcW\n"
"xkPo1LsmmkVwXqkLN1PiRnsn/eBG8om3zEK2yygmbtmlyTrIQRNg91CMFa6ybRoVGld45pIq2WWQ\n"
"gj9sAq+uEjonljYE1x2igGOpm/HlurR8FLBOybEfdF849lHqm/osohHUqS0nGkWxr7JOcQ3AWEbW\n"
"aQbLU8uz/mtBzUF+fUwPfHJ5elnNXkoOrJupmHN5fLT0zLm4BwyydFy4x2+IoZCn9Kr5v2c69BoV\n"
"Yh63n749sSmvZ6ES8lgQGVMDMBu4Gon2nL2XA46jCfMdiyHxtN/kHNGfZQIG6lzWE7OE76KlXIx3\n"
"KadowGuuQNKotOrN8I1LOJwZmhsoVLiJkO/KdYE+HvJkJMcYr07/R54H9jVlpNMKVv/1F2Rs76gi\n"
"JUmTtt8AF9pYfl3uxRuw0dFfIRDH+fO6AgonB8Xx1sfT4PsJYGw=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Amazon Root CA 3\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIBtjCCAVugAwIBAgITBmyf1XSXNmY/Owua2eiedgPySjAKBggqhkjOPQQDAjA5MQswCQYDVQQG\n"
"EwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24gUm9vdCBDQSAzMB4XDTE1MDUy\n"
"NjAwMDAwMFoXDTQwMDUyNjAwMDAwMFowOTELMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZ\n"
"MBcGA1UEAxMQQW1hem9uIFJvb3QgQ0EgMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABCmXp8ZB\n"
"f8ANm+gBG1bG8lKlui2yEujSLtf6ycXYqm0fc4E7O5hrOXwzpcVOho6AF2hiRVd9RFgdszflZwjr\n"
"Zt6jQjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBSrttvXBp43\n"
"rDCGB5Fwx5zEGbF4wDAKBggqhkjOPQQDAgNJADBGAiEA4IWSoxe3jfkrBqWTrBqYaGFy+uGh0Psc\n"
"eGCmQ5nFuMQCIQCcAu/xlJyzlvnrxir4tiz+OpAUFteMYyRIHN8wfdVoOw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Amazon Root CA 4\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIB8jCCAXigAwIBAgITBmyf18G7EEwpQ+Vxe3ssyBrBDjAKBggqhkjOPQQDAzA5MQswCQYDVQQG\n"
"EwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24gUm9vdCBDQSA0MB4XDTE1MDUy\n"
"NjAwMDAwMFoXDTQwMDUyNjAwMDAwMFowOTELMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZ\n"
"MBcGA1UEAxMQQW1hem9uIFJvb3QgQ0EgNDB2MBAGByqGSM49AgEGBSuBBAAiA2IABNKrijdPo1MN\n"
"/sGKe0uoe0ZLY7Bi9i0b2whxIdIA6GO9mif78DluXeo9pcmBqqNbIJhFXRbb/egQbeOc4OO9X4Ri\n"
"83BkM6DLJC9wuoihKqB1+IGuYgbEgds5bimwHvouXKNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n"
"HQ8BAf8EBAMCAYYwHQYDVR0OBBYEFNPsxzplbszh2naaVvuc84ZtV+WBMAoGCCqGSM49BAMDA2gA\n"
"MGUCMDqLIfG9fhGt0O9Yli/W651+kI0rz2ZVwyzjKKlwCkcO8DdZEv8tmZQoTipPNU0zWgIxAOp1\n"
"AE47xDqUEpHJWEadIRNyp4iciuRMStuW1KyLa2tJElMzrdfkviT8tQp21KW8EA==\n"
"-----END CERTIFICATE-----\n"
"\n"
"TUBITAK Kamu SM SSL Kok Sertifikasi - Surum 1\n"
"=============================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEYzCCA0ugAwIBAgIBATANBgkqhkiG9w0BAQsFADCB0jELMAkGA1UEBhMCVFIxGDAWBgNVBAcT\n"
"D0dlYnplIC0gS29jYWVsaTFCMEAGA1UEChM5VHVya2l5ZSBCaWxpbXNlbCB2ZSBUZWtub2xvamlr\n"
"IEFyYXN0aXJtYSBLdXJ1bXUgLSBUVUJJVEFLMS0wKwYDVQQLEyRLYW11IFNlcnRpZmlrYXN5b24g\n"
"TWVya2V6aSAtIEthbXUgU00xNjA0BgNVBAMTLVRVQklUQUsgS2FtdSBTTSBTU0wgS29rIFNlcnRp\n"
"ZmlrYXNpIC0gU3VydW0gMTAeFw0xMzExMjUwODI1NTVaFw00MzEwMjUwODI1NTVaMIHSMQswCQYD\n"
"VQQGEwJUUjEYMBYGA1UEBxMPR2ViemUgLSBLb2NhZWxpMUIwQAYDVQQKEzlUdXJraXllIEJpbGlt\n"
"c2VsIHZlIFRla25vbG9qaWsgQXJhc3Rpcm1hIEt1cnVtdSAtIFRVQklUQUsxLTArBgNVBAsTJEth\n"
"bXUgU2VydGlmaWthc3lvbiBNZXJrZXppIC0gS2FtdSBTTTE2MDQGA1UEAxMtVFVCSVRBSyBLYW11\n"
"IFNNIFNTTCBLb2sgU2VydGlmaWthc2kgLSBTdXJ1bSAxMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8A\n"
"MIIBCgKCAQEAr3UwM6q7a9OZLBI3hNmNe5eA027n/5tQlT6QlVZC1xl8JoSNkvoBHToP4mQ4t4y8\n"
"6Ij5iySrLqP1N+RAjhgleYN1Hzv/bKjFxlb4tO2KRKOrbEz8HdDc72i9z+SqzvBV96I01INrN3wc\n"
"wv61A+xXzry0tcXtAA9TNypN9E8Mg/uGz8v+jE69h/mniyFXnHrfA2eJLJ2XYacQuFWQfw4tJzh0\n"
"3+f92k4S400VIgLI4OD8D62K18lUUMw7D8oWgITQUVbDjlZ/iSIzL+aFCr2lqBs23tPcLG07xxO9\n"
"WSMs5uWk99gL7eqQQESolbuT1dCANLZGeA4fAJNG4e7p+exPFwIDAQABo0IwQDAdBgNVHQ4EFgQU\n"
"ZT/HiobGPN08VFw1+DrtUgxHV8gwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wDQYJ\n"
"KoZIhvcNAQELBQADggEBACo/4fEyjq7hmFxLXs9rHmoJ0iKpEsdeV31zVmSAhHqT5Am5EM2fKifh\n"
"AHe+SMg1qIGf5LgsyX8OsNJLN13qudULXjS99HMpw+0mFZx+CFOKWI3QSyjfwbPfIPP54+M638yc\n"
"lNhOT8NrF7f3cuitZjO1JVOr4PhMqZ398g26rrnZqsZr+ZO7rqu4lzwDGrpDxpa5RXI4s6ehlj2R\n"
"e37AIVNMh+3yC1SVUZPVIqUNivGTDj5UDrDYyU7c8jEyVupk+eq1nRZmQnLzf9OxMUP8pI4X8W0j\n"
"q5Rm+K37DwhuJi1/FwcJsoz7UMCflo3Ptv0AnVoUmr8CRPXBwp8iXqIPoeM=\n"
"-----END CERTIFICATE-----\n"
"\n"
"GDCA TrustAUTH R5 ROOT\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"TrustCor RootCert CA-1\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEMDCCAxigAwIBAgIJANqb7HHzA7AZMA0GCSqGSIb3DQEBCwUAMIGkMQswCQYDVQQGEwJQQTEP\n"
"MA0GA1UECAwGUGFuYW1hMRQwEgYDVQQHDAtQYW5hbWEgQ2l0eTEkMCIGA1UECgwbVHJ1c3RDb3Ig\n"
"U3lzdGVtcyBTLiBkZSBSLkwuMScwJQYDVQQLDB5UcnVzdENvciBDZXJ0aWZpY2F0ZSBBdXRob3Jp\n"
"dHkxHzAdBgNVBAMMFlRydXN0Q29yIFJvb3RDZXJ0IENBLTEwHhcNMTYwMjA0MTIzMjE2WhcNMjkx\n"
"MjMxMTcyMzE2WjCBpDELMAkGA1UEBhMCUEExDzANBgNVBAgMBlBhbmFtYTEUMBIGA1UEBwwLUGFu\n"
"YW1hIENpdHkxJDAiBgNVBAoMG1RydXN0Q29yIFN5c3RlbXMgUy4gZGUgUi5MLjEnMCUGA1UECwwe\n"
"VHJ1c3RDb3IgQ2VydGlmaWNhdGUgQXV0aG9yaXR5MR8wHQYDVQQDDBZUcnVzdENvciBSb290Q2Vy\n"
"dCBDQS0xMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAv463leLCJhJrMxnHQFgKq1mq\n"
"jQCj/IDHUHuO1CAmujIS2CNUSSUQIpidRtLByZ5OGy4sDjjzGiVoHKZaBeYei0i/mJZ0PmnK6bV4\n"
"pQa81QBeCQryJ3pS/C3Vseq0iWEk8xoT26nPUu0MJLq5nux+AHT6k61sKZKuUbS701e/s/OojZz0\n"
"JEsq1pme9J7+wH5COucLlVPat2gOkEz7cD+PSiyU8ybdY2mplNgQTsVHCJCZGxdNuWxu72CVEY4h\n"
"gLW9oHPY0LJ3xEXqWib7ZnZ2+AYfYW0PVcWDtxBWcgYHpfOxGgMFZA6dWorWhnAbJN7+KIor0Gqw\n"
"/Hqi3LJ5DotlDwIDAQABo2MwYTAdBgNVHQ4EFgQU7mtJPHo/DeOxCbeKyKsZn3MzUOcwHwYDVR0j\n"
"BBgwFoAU7mtJPHo/DeOxCbeKyKsZn3MzUOcwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AYYwDQYJKoZIhvcNAQELBQADggEBACUY1JGPE+6PHh0RU9otRCkZoB5rMZ5NDp6tPVxBb5UrJKF5\n"
"mDo4Nvu7Zp5I/5CQ7z3UuJu0h3U/IJvOcs+hVcFNZKIZBqEHMwwLKeXx6quj7LUKdJDHfXLy11yf\n"
"ke+Ri7fc7Waiz45mO7yfOgLgJ90WmMCV1Aqk5IGadZQ1nJBfiDcGrVmVCrDRZ9MZyonnMlo2HD6C\n"
"qFqTvsbQZJG2z9m2GM/bftJlo6bEjhcxwft+dtvTheNYsnd6djtsL1Ac59v2Z3kf9YKVmgenFK+P\n"
"3CghZwnS1k1aHBkcjndcw5QkPTJrS37UeJSDvjdNzl/HHk484IkzlQsPpTLWPFp5LBk=\n"
"-----END CERTIFICATE-----\n"
"\n"
"TrustCor RootCert CA-2\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIGLzCCBBegAwIBAgIIJaHfyjPLWQIwDQYJKoZIhvcNAQELBQAwgaQxCzAJBgNVBAYTAlBBMQ8w\n"
"DQYDVQQIDAZQYW5hbWExFDASBgNVBAcMC1BhbmFtYSBDaXR5MSQwIgYDVQQKDBtUcnVzdENvciBT\n"
"eXN0ZW1zIFMuIGRlIFIuTC4xJzAlBgNVBAsMHlRydXN0Q29yIENlcnRpZmljYXRlIEF1dGhvcml0\n"
"eTEfMB0GA1UEAwwWVHJ1c3RDb3IgUm9vdENlcnQgQ0EtMjAeFw0xNjAyMDQxMjMyMjNaFw0zNDEy\n"
"MzExNzI2MzlaMIGkMQswCQYDVQQGEwJQQTEPMA0GA1UECAwGUGFuYW1hMRQwEgYDVQQHDAtQYW5h\n"
"bWEgQ2l0eTEkMCIGA1UECgwbVHJ1c3RDb3IgU3lzdGVtcyBTLiBkZSBSLkwuMScwJQYDVQQLDB5U\n"
"cnVzdENvciBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkxHzAdBgNVBAMMFlRydXN0Q29yIFJvb3RDZXJ0\n"
"IENBLTIwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCnIG7CKqJiJJWQdsg4foDSq8Gb\n"
"ZQWU9MEKENUCrO2fk8eHyLAnK0IMPQo+QVqedd2NyuCb7GgypGmSaIwLgQ5WoD4a3SwlFIIvl9Nk\n"
"RvRUqdw6VC0xK5mC8tkq1+9xALgxpL56JAfDQiDyitSSBBtlVkxs1Pu2YVpHI7TYabS3OtB0PAx1\n"
"oYxOdqHp2yqlO/rOsP9+aij9JxzIsekp8VduZLTQwRVtDr4uDkbIXvRR/u8OYzo7cbrPb1nKDOOb\n"
"XUm4TOJXsZiKQlecdu/vvdFoqNL0Cbt3Nb4lggjEFixEIFapRBF37120Hapeaz6LMvYHL1cEksr1\n"
"/p3C6eizjkxLAjHZ5DxIgif3GIJ2SDpxsROhOdUuxTTCHWKF3wP+TfSvPd9cW436cOGlfifHhi5q\n"
"jxLGhF5DUVCcGZt45vz27Ud+ez1m7xMTiF88oWP7+ayHNZ/zgp6kPwqcMWmLmaSISo5uZk3vFsQP\n"
"eSghYA2FFn3XVDjxklb9tTNMg9zXEJ9L/cb4Qr26fHMC4P99zVvh1Kxhe1fVSntb1IVYJ12/+Ctg\n"
"rKAmrhQhJ8Z3mjOAPF5GP/fDsaOGM8boXg25NSyqRsGFAnWAoOsk+xWq5Gd/bnc/9ASKL3x74xdh\n"
"8N0JqSDIvgmk0H5Ew7IwSjiqqewYmgeCK9u4nBit2uBGF6zPXQIDAQABo2MwYTAdBgNVHQ4EFgQU\n"
"2f4hQG6UnrybPZx9mCAZ5YwwYrIwHwYDVR0jBBgwFoAU2f4hQG6UnrybPZx9mCAZ5YwwYrIwDwYD\n"
"VR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAYYwDQYJKoZIhvcNAQELBQADggIBAJ5Fngw7tu/h\n"
"Osh80QA9z+LqBrWyOrsGS2h60COXdKcs8AjYeVrXWoSK2BKaG9l9XE1wxaX5q+WjiYndAfrs3fnp\n"
"kpfbsEZC89NiqpX+MWcUaViQCqoL7jcjx1BRtPV+nuN79+TMQjItSQzL/0kMmx40/W5ulop5A7Zv\n"
"2wnL/V9lFDfhOPXzYRZY5LVtDQsEGz9QLX+zx3oaFoBg+Iof6Rsqxvm6ARppv9JYx1RXCI/hOWB3\n"
"S6xZhBqI8d3LT3jX5+EzLfzuQfogsL7L9ziUwOHQhQ+77Sxzq+3+knYaZH9bDTMJBzN7Bj8RpFxw\n"
"PIXAz+OQqIN3+tvmxYxoZxBnpVIt8MSZj3+/0WvitUfW2dCFmU2Umw9Lje4AWkcdEQOsQRivh7dv\n"
"DDqPys/cA8GiCcjl/YBeyGBCARsaU1q7N6a3vLqE6R5sGtRk2tRD/pOLS/IseRYQ1JMLiI+h2IYU\n"
"RpFHmygk71dSTlxCnKr3Sewn6EAes6aJInKc9Q0ztFijMDvd1GpUk74aTfOTlPf8hAs/hCBcNANE\n"
"xdqtvArBAs8e5ZTZ845b2EzwnexhF7sUMlQMAimTHpKG9n/v55IFDlndmQguLvqcAFLTxWYp5KeX\n"
"RKQOKIETNcX2b2TmQcTVL8w0RSXPQQCWPUouwpaYT05KnJe32x+SMsj/D1Fu1uwJ\n"
"-----END CERTIFICATE-----\n"
"\n"
"TrustCor ECA-1\n"
"==============\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIEIDCCAwigAwIBAgIJAISCLF8cYtBAMA0GCSqGSIb3DQEBCwUAMIGcMQswCQYDVQQGEwJQQTEP\n"
"MA0GA1UECAwGUGFuYW1hMRQwEgYDVQQHDAtQYW5hbWEgQ2l0eTEkMCIGA1UECgwbVHJ1c3RDb3Ig\n"
"U3lzdGVtcyBTLiBkZSBSLkwuMScwJQYDVQQLDB5UcnVzdENvciBDZXJ0aWZpY2F0ZSBBdXRob3Jp\n"
"dHkxFzAVBgNVBAMMDlRydXN0Q29yIEVDQS0xMB4XDTE2MDIwNDEyMzIzM1oXDTI5MTIzMTE3Mjgw\n"
"N1owgZwxCzAJBgNVBAYTAlBBMQ8wDQYDVQQIDAZQYW5hbWExFDASBgNVBAcMC1BhbmFtYSBDaXR5\n"
"MSQwIgYDVQQKDBtUcnVzdENvciBTeXN0ZW1zIFMuIGRlIFIuTC4xJzAlBgNVBAsMHlRydXN0Q29y\n"
"IENlcnRpZmljYXRlIEF1dGhvcml0eTEXMBUGA1UEAwwOVHJ1c3RDb3IgRUNBLTEwggEiMA0GCSqG\n"
"SIb3DQEBAQUAA4IBDwAwggEKAoIBAQDPj+ARtZ+odnbb3w9U73NjKYKtR8aja+3+XzP4Q1HpGjOR\n"
"MRegdMTUpwHmspI+ap3tDvl0mEDTPwOABoJA6LHip1GnHYMma6ve+heRK9jGrB6xnhkB1Zem6g23\n"
"xFUfJ3zSCNV2HykVh0A53ThFEXXQmqc04L/NyFIduUd+Dbi7xgz2c1cWWn5DkR9VOsZtRASqnKmc\n"
"p0yJF4OuowReUoCLHhIlERnXDH19MURB6tuvsBzvgdAsxZohmz3tQjtQJvLsznFhBmIhVE5/wZ0+\n"
"fyCMgMsq2JdiyIMzkX2woloPV+g7zPIlstR8L+xNxqE6FXrntl019fZISjZFZtS6mFjBAgMBAAGj\n"
"YzBhMB0GA1UdDgQWBBREnkj1zG1I1KBLf/5ZJC+Dl5mahjAfBgNVHSMEGDAWgBREnkj1zG1I1KBL\n"
"f/5ZJC+Dl5mahjAPBgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBhjANBgkqhkiG9w0BAQsF\n"
"AAOCAQEABT41XBVwm8nHc2FvcivUwo/yQ10CzsSUuZQRg2dd4mdsdXa/uwyqNsatR5Nj3B5+1t4u\n"
"/ukZMjgDfxT2AHMsWbEhBuH7rBiVDKP/mZb3Kyeb1STMHd3BOuCYRLDE5D53sXOpZCz2HAF8P11F\n"
"hcCF5yWPldwX8zyfGm6wyuMdKulMY/okYWLW2n62HGz1Ah3UKt1VkOsqEUc8Ll50soIipX1TH0Xs\n"
"J5F95yIW6MBoNtjG8U+ARDL54dHRHareqKucBK+tIA5kmE2la8BIWJZpTdwHjFGTot+fDz2LYLSC\n"
"jaoITmJF4PkL0uDgPFveXHEnJcLmA4GLEFPjx1WitJ/X5g==\n"
"-----END CERTIFICATE-----\n"
"\n"
"SSL.com Root Certification Authority RSA\n"
"========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"WuuA8ShYIc2wBlX7Jz9TkHCpBB5XJ7k=\n"
"-----END CERTIFICATE-----\n"
"\n"
"SSL.com Root Certification Authority ECC\n"
"========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICjTCCAhSgAwIBAgIIdebfy8FoW6gwCgYIKoZIzj0EAwIwfDELMAkGA1UEBhMCVVMxDjAMBgNV\n"
"BAgMBVRleGFzMRAwDgYDVQQHDAdIb3VzdG9uMRgwFgYDVQQKDA9TU0wgQ29ycG9yYXRpb24xMTAv\n"
"BgNVBAMMKFNTTC5jb20gUm9vdCBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eSBFQ0MwHhcNMTYwMjEy\n"
"MTgxNDAzWhcNNDEwMjEyMTgxNDAzWjB8MQswCQYDVQQGEwJVUzEOMAwGA1UECAwFVGV4YXMxEDAO\n"
"BgNVBAcMB0hvdXN0b24xGDAWBgNVBAoMD1NTTCBDb3Jwb3JhdGlvbjExMC8GA1UEAwwoU1NMLmNv\n"
"bSBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IEVDQzB2MBAGByqGSM49AgEGBSuBBAAiA2IA\n"
"BEVuqVDEpiM2nl8ojRfLliJkP9x6jh3MCLOicSS6jkm5BBtHllirLZXI7Z4INcgn64mMU1jrYor+\n"
"8FsPazFSY0E7ic3s7LaNGdM0B9y7xgZ/wkWV7Mt/qCPgCemB+vNH06NjMGEwHQYDVR0OBBYEFILR\n"
"hXMw5zUE044CkvvlpNHEIejNMA8GA1UdEwEB/wQFMAMBAf8wHwYDVR0jBBgwFoAUgtGFczDnNQTT\n"
"jgKS++Wk0cQh6M0wDgYDVR0PAQH/BAQDAgGGMAoGCCqGSM49BAMCA2cAMGQCMG/n61kRpGDPYbCW\n"
"e+0F+S8Tkdzt5fxQaxFGRrMcIQBiu77D5+jNB5n5DQtdcj7EqgIwH7y6C+IwJPt8bYBVCpk+gA0z\n"
"5Wajs6O7pdWLjwkspl1+4vAHCGht0nxpbl/f5Wpl\n"
"-----END CERTIFICATE-----\n"
"\n"
"SSL.com EV Root Certification Authority RSA R2\n"
"==============================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIF6zCCA9OgAwIBAgIIVrYpzTS8ePYwDQYJKoZIhvcNAQELBQAwgYIxCzAJBgNVBAYTAlVTMQ4w\n"
"DAYDVQQIDAVUZXhhczEQMA4GA1UEBwwHSG91c3RvbjEYMBYGA1UECgwPU1NMIENvcnBvcmF0aW9u\n"
"MTcwNQYDVQQDDC5TU0wuY29tIEVWIFJvb3QgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkgUlNBIFIy\n"
"MB4XDTE3MDUzMTE4MTQzN1oXDTQyMDUzMDE4MTQzN1owgYIxCzAJBgNVBAYTAlVTMQ4wDAYDVQQI\n"
"DAVUZXhhczEQMA4GA1UEBwwHSG91c3RvbjEYMBYGA1UECgwPU1NMIENvcnBvcmF0aW9uMTcwNQYD\n"
"VQQDDC5TU0wuY29tIEVWIFJvb3QgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkgUlNBIFIyMIICIjAN\n"
"BgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAjzZlQOHWTcDXtOlG2mvqM0fNTPl9fb69LT3w23jh\n"
"hqXZuglXaO1XPqDQCEGD5yhBJB/jchXQARr7XnAjssufOePPxU7Gkm0mxnu7s9onnQqG6YE3Bf7w\n"
"cXHswxzpY6IXFJ3vG2fThVUCAtZJycxa4bH3bzKfydQ7iEGonL3Lq9ttewkfokxykNorCPzPPFTO\n"
"Zw+oz12WGQvE43LrrdF9HSfvkusQv1vrO6/PgN3B0pYEW3p+pKk8OHakYo6gOV7qd89dAFmPZiw+\n"
"B6KjBSYRaZfqhbcPlgtLyEDhULouisv3D5oi53+aNxPN8k0TayHRwMwi8qFG9kRpnMphNQcAb9Zh\n"
"CBHqurj26bNg5U257J8UZslXWNvNh2n4ioYSA0e/ZhN2rHd9NCSFg83XqpyQGp8hLH94t2S42Oim\n"
"9HizVcuE0jLEeK6jj2HdzghTreyI/BXkmg3mnxp3zkyPuBQVPWKchjgGAGYS5Fl2WlPAApiiECto\n"
"RHuOec4zSnaqW4EWG7WK2NAAe15itAnWhmMOpgWVSbooi4iTsjQc2KRVbrcc0N6ZVTsj9CLg+Slm\n"
"JuwgUHfbSguPvuUCYHBBXtSuUDkiFCbLsjtzdFVHB3mBOagwE0TlBIqulhMlQg+5U8Sb/M3kHN48\n"
"+qvWBkofZ6aYMBzdLNvcGJVXZsb/XItW9XcCAwEAAaNjMGEwDwYDVR0TAQH/BAUwAwEB/zAfBgNV\n"
"HSMEGDAWgBT5YLvU49U09rj1BoAlp3PbRmmonjAdBgNVHQ4EFgQU+WC71OPVNPa49QaAJadz20Zp\n"
"qJ4wDgYDVR0PAQH/BAQDAgGGMA0GCSqGSIb3DQEBCwUAA4ICAQBWs47LCp1Jjr+kxJG7ZhcFUZh1\n"
"++VQLHqe8RT6q9OKPv+RKY9ji9i0qVQBDb6Thi/5Sm3HXvVX+cpVHBK+Rw82xd9qt9t1wkclf7nx\n"
"Y/hoLVUE0fKNsKTPvDxeH3jnpaAgcLAExbf3cqfeIg29MyVGjGSSJuM+LmOW2puMPfgYCdcDzH2G\n"
"guDKBAdRUNf/ktUM79qGn5nX67evaOI5JpS6aLe/g9Pqemc9YmeuJeVy6OLk7K4S9ksrPJ/psEDz\n"
"OFSz/bdoyNrGj1E8svuR3Bznm53htw1yj+KkxKl4+esUrMZDBcJlOSgYAsOCsp0FvmXtll9ldDz7\n"
"CTUue5wT/RsPXcdtgTpWD8w74a8CLyKsRspGPKAcTNZEtF4uXBVmCeEmKf7GUmG6sXP/wwyc5Wxq\n"
"lD8UykAWlYTzWamsX0xhk23RO8yilQwipmdnRC652dKKQbNmC1r7fSOl8hqw/96bg5Qu0T/fkreR\n"
"rwU7ZcegbLHNYhLDkBvjJc40vG93drEQw/cFGsDWr3RiSBd3kmmQYRzelYB0VI8YHMPzA9C/pEN1\n"
"hlMYegouCRw2n5H9gooiS9EOUCXdywMMF8mDAAhONU2Ki+3wApRmLER/y5UnlhetCTCstnEXbosX\n"
"9hwJ1C07mKVx01QT2WDz9UtmT/rx7iASjbSsV7FFY6GsdqnC+w==\n"
"-----END CERTIFICATE-----\n"
"\n"
"SSL.com EV Root Certification Authority ECC\n"
"===========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIClDCCAhqgAwIBAgIILCmcWxbtBZUwCgYIKoZIzj0EAwIwfzELMAkGA1UEBhMCVVMxDjAMBgNV\n"
"BAgMBVRleGFzMRAwDgYDVQQHDAdIb3VzdG9uMRgwFgYDVQQKDA9TU0wgQ29ycG9yYXRpb24xNDAy\n"
"BgNVBAMMK1NTTC5jb20gRVYgUm9vdCBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eSBFQ0MwHhcNMTYw\n"
"MjEyMTgxNTIzWhcNNDEwMjEyMTgxNTIzWjB/MQswCQYDVQQGEwJVUzEOMAwGA1UECAwFVGV4YXMx\n"
"EDAOBgNVBAcMB0hvdXN0b24xGDAWBgNVBAoMD1NTTCBDb3Jwb3JhdGlvbjE0MDIGA1UEAwwrU1NM\n"
"LmNvbSBFViBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IEVDQzB2MBAGByqGSM49AgEGBSuB\n"
"BAAiA2IABKoSR5CYG/vvw0AHgyBO8TCCogbR8pKGYfL2IWjKAMTH6kMAVIbc/R/fALhBYlzccBYy\n"
"3h+Z1MzFB8gIH2EWB1E9fVwHU+M1OIzfzZ/ZLg1KthkuWnBaBu2+8KGwytAJKaNjMGEwHQYDVR0O\n"
"BBYEFFvKXuXe0oGqzagtZFG22XKbl+ZPMA8GA1UdEwEB/wQFMAMBAf8wHwYDVR0jBBgwFoAUW8pe\n"
"5d7SgarNqC1kUbbZcpuX5k8wDgYDVR0PAQH/BAQDAgGGMAoGCCqGSM49BAMCA2gAMGUCMQCK5kCJ\n"
"N+vp1RPZytRrJPOwPYdGWBrssd9v+1a6cGvHOMzosYxPD/fxZ3YOg9AeUY8CMD32IygmTMZgh5Mm\n"
"m7I1HrrW9zzRHM76JTymGoEVW/MSD2zuZYrJh6j5B+BimoxcSg==\n"
"-----END CERTIFICATE-----\n"
"\n"
"GlobalSign Root CA - R6\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"OISTE WISeKey Global Root GC CA\n"
"===============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICaTCCAe+gAwIBAgIQISpWDK7aDKtARb8roi066jAKBggqhkjOPQQDAzBtMQswCQYDVQQGEwJD\n"
"SDEQMA4GA1UEChMHV0lTZUtleTEiMCAGA1UECxMZT0lTVEUgRm91bmRhdGlvbiBFbmRvcnNlZDEo\n"
"MCYGA1UEAxMfT0lTVEUgV0lTZUtleSBHbG9iYWwgUm9vdCBHQyBDQTAeFw0xNzA1MDkwOTQ4MzRa\n"
"Fw00MjA1MDkwOTU4MzNaMG0xCzAJBgNVBAYTAkNIMRAwDgYDVQQKEwdXSVNlS2V5MSIwIAYDVQQL\n"
"ExlPSVNURSBGb3VuZGF0aW9uIEVuZG9yc2VkMSgwJgYDVQQDEx9PSVNURSBXSVNlS2V5IEdsb2Jh\n"
"bCBSb290IEdDIENBMHYwEAYHKoZIzj0CAQYFK4EEACIDYgAETOlQwMYPchi82PG6s4nieUqjFqdr\n"
"VCTbUf/q9Akkwwsin8tqJ4KBDdLArzHkdIJuyiXZjHWd8dvQmqJLIX4Wp2OQ0jnUsYd4XxiWD1Ab\n"
"NTcPasbc2RNNpI6QN+a9WzGRo1QwUjAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAd\n"
"BgNVHQ4EFgQUSIcUrOPDnpBgOtfKie7TrYy0UGYwEAYJKwYBBAGCNxUBBAMCAQAwCgYIKoZIzj0E\n"
"AwMDaAAwZQIwJsdpW9zV57LnyAyMjMPdeYwbY9XJUpROTYJKcx6ygISpJcBMWm1JKWB4E+J+SOtk\n"
"AjEA2zQgMgj/mkkCtojeFK9dbJlxjRo/i9fgojaGHAeCOnZT/cKi7e97sIBPWA9LUzm9\n"
"-----END CERTIFICATE-----\n"
"\n"
"GTS Root R1\n"
"===========\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFWjCCA0KgAwIBAgIQbkepxUtHDA3sM9CJuRz04TANBgkqhkiG9w0BAQwFADBHMQswCQYDVQQG\n"
"EwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJv\n"
"b3QgUjEwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAwMDAwWjBHMQswCQYDVQQGEwJVUzEiMCAG\n"
"A1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjEwggIi\n"
"MA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQC2EQKLHuOhd5s73L+UPreVp0A8of2C+X0yBoJx\n"
"9vaMf/vo27xqLpeXo4xL+Sv2sfnOhB2x+cWX3u+58qPpvBKJXqeqUqv4IyfLpLGcY9vXmX7wCl7r\n"
"aKb0xlpHDU0QM+NOsROjyBhsS+z8CZDfnWQpJSMHobTSPS5g4M/SCYe7zUjwTcLCeoiKu7rPWRnW\n"
"r4+wB7CeMfGCwcDfLqZtbBkOtdh+JhpFAz2weaSUKK0PfyblqAj+lug8aJRT7oM6iCsVlgmy4HqM\n"
"LnXWnOunVmSPlk9orj2XwoSPwLxAwAtcvfaHszVsrBhQf4TgTM2S0yDpM7xSma8ytSmzJSq0SPly\n"
"4cpk9+aCEI3oncKKiPo4Zor8Y/kB+Xj9e1x3+naH+uzfsQ55lVe0vSbv1gHR6xYKu44LtcXFilWr\n"
"06zqkUspzBmkMiVOKvFlRNACzqrOSbTqn3yDsEB750Orp2yjj32JgfpMpf/VjsPOS+C12LOORc92\n"
"wO1AK/1TD7Cn1TsNsYqiA94xrcx36m97PtbfkSIS5r762DL8EGMUUXLeXdYWk70paDPvOmbsB4om\n"
"3xPXV2V4J95eSRQAogB/mqghtqmxlbCluQ0WEdrHbEg8QOB+DVrNVjzRlwW5y0vtOUucxD/SVRNu\n"
"JLDWcfr0wbrM7Rv1/oFB2ACYPTrIrnqYNxgFlQIDAQABo0IwQDAOBgNVHQ8BAf8EBAMCAQYwDwYD\n"
"VR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQU5K8rJnEaK0gnhS9SZizv8IkTcT4wDQYJKoZIhvcNAQEM\n"
"BQADggIBADiWCu49tJYeX++dnAsznyvgyv3SjgofQXSlfKqE1OXyHuY3UjKcC9FhHb8owbZEKTV1\n"
"d5iyfNm9dKyKaOOpMQkpAWBz40d8U6iQSifvS9efk+eCNs6aaAyC58/UEBZvXw6ZXPYfcX3v73sv\n"
"fuo21pdwCxXu11xWajOl40k4DLh9+42FpLFZXvRq4d2h9mREruZRgyFmxhE+885H7pwoHyXa/6xm\n"
"ld01D1zvICxi/ZG6qcz8WpyTgYMpl0p8WnK0OdC3d8t5/Wk6kjftbjhlRn7pYL15iJdfOBL07q9b\n"
"gsiG1eGZbYwE8na6SfZu6W0eX6DvJ4J2QPim01hcDyxC2kLGe4g0x8HYRZvBPsVhHdljUEn2NIVq\n"
"4BjFbkerQUIpm/ZgDdIx02OYI5NaAIFItO/Nis3Jz5nu2Z6qNuFoS3FJFDYoOj0dzpqPJeaAcWEr\n"
"tXvM+SUWgeExX6GjfhaknBZqlxi9dnKlC54dNuYvoS++cJEPqOba+MSSQGwlfnuzCdyyF62ARPBo\n"
"pY+Udf90WuioAnwMCeKpSwughQtiue+hMZL77/ZRBIls6Kl0obsXs7X9SQ98POyDGCBDTtWTurQ0\n"
"sR8WNh8M5mQ5Fkzc4P4dyKliPUDqysU0ArSuiYgzNdwsE3PYJ/HQcu51OyLemGhmW/HGY0dVHLql\n"
"CFF1pkgl\n"
"-----END CERTIFICATE-----\n"
"\n"
"GTS Root R2\n"
"===========\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFWjCCA0KgAwIBAgIQbkepxlqz5yDFMJo/aFLybzANBgkqhkiG9w0BAQwFADBHMQswCQYDVQQG\n"
"EwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJv\n"
"b3QgUjIwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAwMDAwWjBHMQswCQYDVQQGEwJVUzEiMCAG\n"
"A1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjIwggIi\n"
"MA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQDO3v2m++zsFDQ8BwZabFn3GTXd98GdVarTzTuk\n"
"k3LvCvptnfbwhYBboUhSnznFt+4orO/LdmgUud+tAWyZH8QiHZ/+cnfgLFuv5AS/T3KgGjSY6Dlo\n"
"7JUle3ah5mm5hRm9iYz+re026nO8/4Piy33B0s5Ks40FnotJk9/BW9BuXvAuMC6C/Pq8tBcKSOWI\n"
"m8Wba96wyrQD8Nr0kLhlZPdcTK3ofmZemde4wj7I0BOdre7kRXuJVfeKH2JShBKzwkCX44ofR5Gm\n"
"dFrS+LFjKBC4swm4VndAoiaYecb+3yXuPuWgf9RhD1FLPD+M2uFwdNjCaKH5wQzpoeJ/u1U8dgbu\n"
"ak7MkogwTZq9TwtImoS1mKPV+3PBV2HdKFZ1E66HjucMUQkQdYhMvI35ezzUIkgfKtzra7tEscsz\n"
"cTJGr61K8YzodDqs5xoic4DSMPclQsciOzsSrZYuxsN2B6ogtzVJV+mSSeh2FnIxZyuWfoqjx5RW\n"
"Ir9qS34BIbIjMt/kmkRtWVtd9QCgHJvGeJeNkP+byKq0rxFROV7Z+2et1VsRnTKaG73Vululycsl\n"
"aVNVJ1zgyjbLiGH7HrfQy+4W+9OmTN6SpdTi3/UGVN4unUu0kzCqgc7dGtxRcw1PcOnlthYhGXmy\n"
"5okLdWTK1au8CcEYof/UVKGFPP0UJAOyh9OktwIDAQABo0IwQDAOBgNVHQ8BAf8EBAMCAQYwDwYD\n"
"VR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUu//KjiOfT5nK2+JopqUVJxce2Q4wDQYJKoZIhvcNAQEM\n"
"BQADggIBALZp8KZ3/p7uC4Gt4cCpx/k1HUCCq+YEtN/L9x0Pg/B+E02NjO7jMyLDOfxA325BS0JT\n"
"vhaI8dI4XsRomRyYUpOM52jtG2pzegVATX9lO9ZY8c6DR2Dj/5epnGB3GFW1fgiTz9D2PGcDFWEJ\n"
"+YF59exTpJ/JjwGLc8R3dtyDovUMSRqodt6Sm2T4syzFJ9MHwAiApJiS4wGWAqoC7o87xdFtCjMw\n"
"c3i5T1QWvwsHoaRc5svJXISPD+AVdyx+Jn7axEvbpxZ3B7DNdehyQtaVhJ2Gg/LkkM0JR9SLA3Da\n"
"WsYDQvTtN6LwG1BUSw7YhN4ZKJmBR64JGz9I0cNv4rBgF/XuIwKl2gBbbZCr7qLpGzvpx0QnRY5r\n"
"n/WkhLx3+WuXrD5RRaIRpsyF7gpo8j5QOHokYh4XIDdtak23CZvJ/KRY9bb7nE4Yu5UC56Gtmwfu\n"
"Nmsk0jmGwZODUNKBRqhfYlcsu2xkiAhu7xNUX90txGdj08+JN7+dIPT7eoOboB6BAFDC5AwiWVIQ\n"
"7UNWhwD4FFKnHYuTjKJNRn8nxnGbJN7k2oaLDX5rIMHAnuFl2GqjpuiFizoHCBy69Y9Vmhh1fuXs\n"
"gWbRIXOhNUQLgD1bnF5vKheW0YMjiGZt5obicDIvUiLnyOd/xCxgXS/Dr55FBcOEArf9LAhST4Ld\n"
"o/DUhgkC\n"
"-----END CERTIFICATE-----\n"
"\n"
"GTS Root R3\n"
"===========\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICDDCCAZGgAwIBAgIQbkepx2ypcyRAiQ8DVd2NHTAKBggqhkjOPQQDAzBHMQswCQYDVQQGEwJV\n"
"UzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3Qg\n"
"UjMwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAwMDAwWjBHMQswCQYDVQQGEwJVUzEiMCAGA1UE\n"
"ChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjMwdjAQBgcq\n"
"hkjOPQIBBgUrgQQAIgNiAAQfTzOHMymKoYTey8chWEGJ6ladK0uFxh1MJ7x/JlFyb+Kf1qPKzEUU\n"
"Rout736GjOyxfi//qXGdGIRFBEFVbivqJn+7kAHjSxm65FSWRQmx1WyRRK2EE46ajA2ADDL24Cej\n"
"QjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBTB8Sa6oC2uhYHP\n"
"0/EqEr24Cmf9vDAKBggqhkjOPQQDAwNpADBmAjEAgFukfCPAlaUs3L6JbyO5o91lAFJekazInXJ0\n"
"glMLfalAvWhgxeG4VDvBNhcl2MG9AjEAnjWSdIUlUfUk7GRSJFClH9voy8l27OyCbvWFGFPouOOa\n"
"KaqW04MjyaR7YbPMAuhd\n"
"-----END CERTIFICATE-----\n"
"\n"
"GTS Root R4\n"
"===========\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICCjCCAZGgAwIBAgIQbkepyIuUtui7OyrYorLBmTAKBggqhkjOPQQDAzBHMQswCQYDVQQGEwJV\n"
"UzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3Qg\n"
"UjQwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAwMDAwWjBHMQswCQYDVQQGEwJVUzEiMCAGA1UE\n"
"ChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjQwdjAQBgcq\n"
"hkjOPQIBBgUrgQQAIgNiAATzdHOnaItgrkO4NcWBMHtLSZ37wWHO5t5GvWvVYRg1rkDdc/eJkTBa\n"
"6zzuhXyiQHY7qca4R9gq55KRanPpsXI5nymfopjTX15YhmUPoYRlBtHci8nHc8iMai/lxKvRHYqj\n"
"QjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBSATNbrdP9JNqPV\n"
"2Py1PsVq8JQdjDAKBggqhkjOPQQDAwNnADBkAjBqUFJ0CMRw3J5QdCHojXohw0+WbhXRIjVhLfoI\n"
"N+4Zba3bssx9BzT1YBkstTTZbyACMANxsbqjYAuG7ZoIapVon+Kz4ZNkfF6Tpt95LY2F45TPI11x\n"
"zPKwTdb+mciUqXWi4w==\n"
"-----END CERTIFICATE-----\n"
"\n"
"UCA Global G2 Root\n"
"==================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFRjCCAy6gAwIBAgIQXd+x2lqj7V2+WmUgZQOQ7zANBgkqhkiG9w0BAQsFADA9MQswCQYDVQQG\n"
"EwJDTjERMA8GA1UECgwIVW5pVHJ1c3QxGzAZBgNVBAMMElVDQSBHbG9iYWwgRzIgUm9vdDAeFw0x\n"
"NjAzMTEwMDAwMDBaFw00MDEyMzEwMDAwMDBaMD0xCzAJBgNVBAYTAkNOMREwDwYDVQQKDAhVbmlU\n"
"cnVzdDEbMBkGA1UEAwwSVUNBIEdsb2JhbCBHMiBSb290MIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\n"
"MIICCgKCAgEAxeYrb3zvJgUno4Ek2m/LAfmZmqkywiKHYUGRO8vDaBsGxUypK8FnFyIdK+35KYmT\n"
"oni9kmugow2ifsqTs6bRjDXVdfkX9s9FxeV67HeToI8jrg4aA3++1NDtLnurRiNb/yzmVHqUwCoV\n"
"8MmNsHo7JOHXaOIxPAYzRrZUEaalLyJUKlgNAQLx+hVRZ2zA+te2G3/RVogvGjqNO7uCEeBHANBS\n"
"h6v7hn4PJGtAnTRnvI3HLYZveT6OqTwXS3+wmeOwcWDcC/Vkw85DvG1xudLeJ1uK6NjGruFZfc8o\n"
"LTW4lVYa8bJYS7cSN8h8s+1LgOGN+jIjtm+3SJUIsUROhYw6AlQgL9+/V087OpAh18EmNVQg7Mc/\n"
"R+zvWr9LesGtOxdQXGLYD0tK3Cv6brxzks3sx1DoQZbXqX5t2Okdj4q1uViSukqSKwxW/YDrCPBe\n"
"KW4bHAyvj5OJrdu9o54hyokZ7N+1wxrrFv54NkzWbtA+FxyQF2smuvt6L78RHBgOLXMDj6DlNaBa\n"
"4kx1HXHhOThTeEDMg5PXCp6dW4+K5OXgSORIskfNTip1KnvyIvbJvgmRlld6iIis7nCs+dwp4wwc\n"
"OxJORNanTrAmyPPZGpeRaOrvjUYG0lZFWJo8DA+DuAUlwznPO6Q0ibd5Ei9Hxeepl2n8pndntd97\n"
"8XplFeRhVmUCAwEAAaNCMEAwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wHQYDVR0O\n"
"BBYEFIHEjMz15DD/pQwIX4wVZyF0Ad/fMA0GCSqGSIb3DQEBCwUAA4ICAQATZSL1jiutROTL/7lo\n"
"5sOASD0Ee/ojL3rtNtqyzm325p7lX1iPyzcyochltq44PTUbPrw7tgTQvPlJ9Zv3hcU2tsu8+Mg5\n"
"1eRfB70VVJd0ysrtT7q6ZHafgbiERUlMjW+i67HM0cOU2kTC5uLqGOiiHycFutfl1qnN3e92mI0A\n"
"Ds0b+gO3joBYDic/UvuUospeZcnWhNq5NXHzJsBPd+aBJ9J3O5oUb3n09tDh05S60FdRvScFDcH9\n"
"yBIw7m+NESsIndTUv4BFFJqIRNow6rSn4+7vW4LVPtateJLbXDzz2K36uGt/xDYotgIVilQsnLAX\n"
"c47QN6MUPJiVAAwpBVueSUmxX8fjy88nZY41F7dXyDDZQVu5FLbowg+UMaeUmMxq67XhJ/UQqAHo\n"
"jhJi6IjMtX9Gl8CbEGY4GjZGXyJoPd/JxhMnq1MGrKI8hgZlb7F+sSlEmqO6SWkoaY/X5V+tBIZk\n"
"bxqgDMUIYs6Ao9Dz7GjevjPHF1t/gMRMTLGmhIrDO7gJzRSBuhjjVFc2/tsvfEehOjPI+Vg7RE+x\n"
"ygKJBJYoaMVLuCaJu9YzL1DV/pqJuhgyklTGW+Cd+V7lDSKb9triyCGyYiGqhkCyLmTTX8jjfhFn\n"
"RR8F/uOi77Oos/N9j/gMHyIfLXC0uAE0djAA5SN4p1bXUB+K+wb1whnw0A==\n"
"-----END CERTIFICATE-----\n"
"\n"
"UCA Extended Validation Root\n"
"============================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFWjCCA0KgAwIBAgIQT9Irj/VkyDOeTzRYZiNwYDANBgkqhkiG9w0BAQsFADBHMQswCQYDVQQG\n"
"EwJDTjERMA8GA1UECgwIVW5pVHJ1c3QxJTAjBgNVBAMMHFVDQSBFeHRlbmRlZCBWYWxpZGF0aW9u\n"
"IFJvb3QwHhcNMTUwMzEzMDAwMDAwWhcNMzgxMjMxMDAwMDAwWjBHMQswCQYDVQQGEwJDTjERMA8G\n"
"A1UECgwIVW5pVHJ1c3QxJTAjBgNVBAMMHFVDQSBFeHRlbmRlZCBWYWxpZGF0aW9uIFJvb3QwggIi\n"
"MA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCpCQcoEwKwmeBkqh5DFnpzsZGgdT6o+uM4AHrs\n"
"iWogD4vFsJszA1qGxliG1cGFu0/GnEBNyr7uaZa4rYEwmnySBesFK5pI0Lh2PpbIILvSsPGP2KxF\n"
"Rv+qZ2C0d35qHzwaUnoEPQc8hQ2E0B92CvdqFN9y4zR8V05WAT558aopO2z6+I9tTcg1367r3CTu\n"
"eUWnhbYFiN6IXSV8l2RnCdm/WhUFhvMJHuxYMjMR83dksHYf5BA1FxvyDrFspCqjc/wJHx4yGVMR\n"
"59mzLC52LqGj3n5qiAno8geK+LLNEOfic0CTuwjRP+H8C5SzJe98ptfRr5//lpr1kXuYC3fUfugH\n"
"0mK1lTnj8/FtDw5lhIpjVMWAtuCeS31HJqcBCF3RiJ7XwzJE+oJKCmhUfzhTA8ykADNkUVkLo4KR\n"
"el7sFsLzKuZi2irbWWIQJUoqgQtHB0MGcIfS+pMRKXpITeuUx3BNr2fVUbGAIAEBtHoIppB/TuDv\n"
"B0GHr2qlXov7z1CymlSvw4m6WC31MJixNnI5fkkE/SmnTHnkBVfblLkWU41Gsx2VYVdWf6/wFlth\n"
"WG82UBEL2KwrlRYaDh8IzTY0ZRBiZtWAXxQgXy0MoHgKaNYs1+lvK9JKBZP8nm9rZ/+I8U6laUpS\n"
"NwXqxhaN0sSZ0YIrO7o1dfdRUVjzyAfd5LQDfwIDAQABo0IwQDAdBgNVHQ4EFgQU2XQ65DA9DfcS\n"
"3H5aBZ8eNJr34RQwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAYYwDQYJKoZIhvcNAQEL\n"
"BQADggIBADaNl8xCFWQpN5smLNb7rhVpLGsaGvdftvkHTFnq88nIua7Mui563MD1sC3AO6+fcAUR\n"
"ap8lTwEpcOPlDOHqWnzcSbvBHiqB9RZLcpHIojG5qtr8nR/zXUACE/xOHAbKsxSQVBcZEhrxH9cM\n"
"aVr2cXj0lH2RC47skFSOvG+hTKv8dGT9cZr4QQehzZHkPJrgmzI5c6sq1WnIeJEmMX3ixzDx/BR4\n"
"dxIOE/TdFpS/S2d7cFOFyrC78zhNLJA5wA3CXWvp4uXViI3WLL+rG761KIcSF3Ru/H38j9CHJrAb\n"
"+7lsq+KePRXBOy5nAliRn+/4Qh8st2j1da3Ptfb/EX3C8CSlrdP6oDyp+l3cpaDvRKS+1ujl5BOW\n"
"F3sGPjLtx7dCvHaj2GU4Kzg1USEODm8uNBNA4StnDG1KQTAYI1oyVZnJF+A83vbsea0rWBmirSwi\n"
"GpWOvpaQXUJXxPkUAzUrHC1RVwinOt4/5Mi0A3PCwSaAuwtCH60NryZy2sy+s6ODWA2CxR9GUeOc\n"
"GMyNm43sSet1UNWMKFnKdDTajAshqx7qG+XH/RU+wBeq+yNuJkbL+vmxcmtpzyKEC2IPrNkZAJSi\n"
"djzULZrtBJ4tBmIQN1IchXIbJ+XMxjHsN+xjWZsLHXbMfjKaiJUINlK73nZfdklJrX+9ZSCyycEr\n"
"dhh2n1ax\n"
"-----END CERTIFICATE-----\n"
"\n"
"Certigna Root CA\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIGWzCCBEOgAwIBAgIRAMrpG4nxVQMNo+ZBbcTjpuEwDQYJKoZIhvcNAQELBQAwWjELMAkGA1UE\n"
"BhMCRlIxEjAQBgNVBAoMCURoaW15b3RpczEcMBoGA1UECwwTMDAwMiA0ODE0NjMwODEwMDAzNjEZ\n"
"MBcGA1UEAwwQQ2VydGlnbmEgUm9vdCBDQTAeFw0xMzEwMDEwODMyMjdaFw0zMzEwMDEwODMyMjda\n"
"MFoxCzAJBgNVBAYTAkZSMRIwEAYDVQQKDAlEaGlteW90aXMxHDAaBgNVBAsMEzAwMDIgNDgxNDYz\n"
"MDgxMDAwMzYxGTAXBgNVBAMMEENlcnRpZ25hIFJvb3QgQ0EwggIiMA0GCSqGSIb3DQEBAQUAA4IC\n"
"DwAwggIKAoICAQDNGDllGlmx6mQWDoyUJJV8g9PFOSbcDO8WV43X2KyjQn+Cyu3NW9sOty3tRQgX\n"
"stmzy9YXUnIo245Onoq2C/mehJpNdt4iKVzSs9IGPjA5qXSjklYcoW9MCiBtnyN6tMbaLOQdLNyz\n"
"KNAT8kxOAkmhVECe5uUFoC2EyP+YbNDrihqECB63aCPuI9Vwzm1RaRDuoXrC0SIxwoKF0vJVdlB8\n"
"JXrJhFwLrN1CTivngqIkicuQstDuI7pmTLtipPlTWmR7fJj6o0ieD5Wupxj0auwuA0Wv8HT4Ks16\n"
"XdG+RCYyKfHx9WzMfgIhC59vpD++nVPiz32pLHxYGpfhPTc3GGYo0kDFUYqMwy3OU4gkWGQwFsWq\n"
"4NYKpkDfePb1BHxpE4S80dGnBs8B92jAqFe7OmGtBIyT46388NtEbVncSVmurJqZNjBBe3YzIoej\n"
"wpKGbvlw7q6Hh5UbxHq9MfPU0uWZ/75I7HX1eBYdpnDBfzwboZL7z8g81sWTCo/1VTp2lc5ZmIoJ\n"
"lXcymoO6LAQ6l73UL77XbJuiyn1tJslV1c/DeVIICZkHJC1kJWumIWmbat10TWuXekG9qxf5kBdI\n"
"jzb5LdXF2+6qhUVB+s06RbFo5jZMm5BX7CO5hwjCxAnxl4YqKE3idMDaxIzb3+KhF1nOJFl0Mdp/\n"
"/TBt2dzhauH8XwIDAQABo4IBGjCCARYwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYw\n"
"HQYDVR0OBBYEFBiHVuBud+4kNTxOc5of1uHieX4rMB8GA1UdIwQYMBaAFBiHVuBud+4kNTxOc5of\n"
"1uHieX4rMEQGA1UdIAQ9MDswOQYEVR0gADAxMC8GCCsGAQUFBwIBFiNodHRwczovL3d3d3cuY2Vy\n"
"dGlnbmEuZnIvYXV0b3JpdGVzLzBtBgNVHR8EZjBkMC+gLaArhilodHRwOi8vY3JsLmNlcnRpZ25h\n"
"LmZyL2NlcnRpZ25hcm9vdGNhLmNybDAxoC+gLYYraHR0cDovL2NybC5kaGlteW90aXMuY29tL2Nl\n"
"cnRpZ25hcm9vdGNhLmNybDANBgkqhkiG9w0BAQsFAAOCAgEAlLieT/DjlQgi581oQfccVdV8AOIt\n"
"OoldaDgvUSILSo3L6btdPrtcPbEo/uRTVRPPoZAbAh1fZkYJMyjhDSSXcNMQH+pkV5a7XdrnxIxP\n"
"TGRGHVyH41neQtGbqH6mid2PHMkwgu07nM3A6RngatgCdTer9zQoKJHyBApPNeNgJgH60BGM+RFq\n"
"7q89w1DTj18zeTyGqHNFkIwgtnJzFyO+B2XleJINugHA64wcZr+shncBlA2c5uk5jR+mUYyZDDl3\n"
"4bSb+hxnV29qao6pK0xXeXpXIs/NX2NGjVxZOob4Mkdio2cNGJHc+6Zr9UhhcyNZjgKnvETq9Emd\n"
"8VRY+WCv2hikLyhF3HqgiIZd8zvn/yk1gPxkQ5Tm4xxvvq0OKmOZK8l+hfZx6AYDlf7ej0gcWtSS\n"
"6Cvu5zHbugRqh5jnxV/vfaci9wHYTfmJ0A6aBVmknpjZbyvKcL5kwlWj9Omvw5Ip3IgWJJk8jSaY\n"
"tlu3zM63Nwf9JtmYhST/WSMDmu2dnajkXjjO11INb9I/bbEFa0nOipFGc/T2L/Coc3cOZayhjWZS\n"
"aX5LaAzHHjcng6WMxwLkFM1JAbBzs/3GkDpv0mztO+7skb6iQ12LAEpmJURw3kAP+HwV96LOPNde\n"
"E4yBFxgX0b3xdxA61GU5wSesVywlVP+i2k+KYTlerj1KjL0=\n"
"-----END CERTIFICATE-----\n"
"\n"
"emSign Root CA - G1\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDlDCCAnygAwIBAgIKMfXkYgxsWO3W2DANBgkqhkiG9w0BAQsFADBnMQswCQYDVQQGEwJJTjET\n"
"MBEGA1UECxMKZW1TaWduIFBLSTElMCMGA1UEChMcZU11ZGhyYSBUZWNobm9sb2dpZXMgTGltaXRl\n"
"ZDEcMBoGA1UEAxMTZW1TaWduIFJvb3QgQ0EgLSBHMTAeFw0xODAyMTgxODMwMDBaFw00MzAyMTgx\n"
"ODMwMDBaMGcxCzAJBgNVBAYTAklOMRMwEQYDVQQLEwplbVNpZ24gUEtJMSUwIwYDVQQKExxlTXVk\n"
"aHJhIFRlY2hub2xvZ2llcyBMaW1pdGVkMRwwGgYDVQQDExNlbVNpZ24gUm9vdCBDQSAtIEcxMIIB\n"
"IjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAk0u76WaK7p1b1TST0Bsew+eeuGQzf2N4aLTN\n"
"LnF115sgxk0pvLZoYIr3IZpWNVrzdr3YzZr/k1ZLpVkGoZM0Kd0WNHVO8oG0x5ZOrRkVUkr+PHB1\n"
"cM2vK6sVmjM8qrOLqs1D/fXqcP/tzxE7lM5OMhbTI0Aqd7OvPAEsbO2ZLIvZTmmYsvePQbAyeGHW\n"
"DV/D+qJAkh1cF+ZwPjXnorfCYuKrpDhMtTk1b+oDafo6VGiFbdbyL0NVHpENDtjVaqSW0RM8LHhQ\n"
"6DqS0hdW5TUaQBw+jSztOd9C4INBdN+jzcKGYEho42kLVACL5HZpIQ15TjQIXhTCzLG3rdd8cIrH\n"
"hQIDAQABo0IwQDAdBgNVHQ4EFgQU++8Nhp6w492pufEhF38+/PB3KxowDgYDVR0PAQH/BAQDAgEG\n"
"MA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEBAFn/8oz1h31xPaOfG1vR2vjTnGs2\n"
"vZupYeveFix0PZ7mddrXuqe8QhfnPZHr5X3dPpzxz5KsbEjMwiI/aTvFthUvozXGaCocV685743Q\n"
"NcMYDHsAVhzNixl03r4PEuDQqqE/AjSxcM6dGNYIAwlG7mDgfrbESQRRfXBgvKqy/3lyeqYdPV8q\n"
"+Mri/Tm3R7nrft8EI6/6nAYH6ftjk4BAtcZsCjEozgyfz7MjNYBBjWzEN3uBL4ChQEKF6dk4jeih\n"
"U80Bv2noWgbyRQuQ+q7hv53yrlc8pa6yVvSLZUDp/TGBLPQ5Cdjua6e0ph0VpZj3AYHYhX3zUVxx\n"
"iN66zB+Afko=\n"
"-----END CERTIFICATE-----\n"
"\n"
"emSign ECC Root CA - G3\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICTjCCAdOgAwIBAgIKPPYHqWhwDtqLhDAKBggqhkjOPQQDAzBrMQswCQYDVQQGEwJJTjETMBEG\n"
"A1UECxMKZW1TaWduIFBLSTElMCMGA1UEChMcZU11ZGhyYSBUZWNobm9sb2dpZXMgTGltaXRlZDEg\n"
"MB4GA1UEAxMXZW1TaWduIEVDQyBSb290IENBIC0gRzMwHhcNMTgwMjE4MTgzMDAwWhcNNDMwMjE4\n"
"MTgzMDAwWjBrMQswCQYDVQQGEwJJTjETMBEGA1UECxMKZW1TaWduIFBLSTElMCMGA1UEChMcZU11\n"
"ZGhyYSBUZWNobm9sb2dpZXMgTGltaXRlZDEgMB4GA1UEAxMXZW1TaWduIEVDQyBSb290IENBIC0g\n"
"RzMwdjAQBgcqhkjOPQIBBgUrgQQAIgNiAAQjpQy4LRL1KPOxst3iAhKAnjlfSU2fySU0WXTsuwYc\n"
"58Byr+iuL+FBVIcUqEqy6HyC5ltqtdyzdc6LBtCGI79G1Y4PPwT01xySfvalY8L1X44uT6EYGQIr\n"
"MgqCZH0Wk9GjQjBAMB0GA1UdDgQWBBR8XQKEE9TMipuBzhccLikenEhjQjAOBgNVHQ8BAf8EBAMC\n"
"AQYwDwYDVR0TAQH/BAUwAwEB/zAKBggqhkjOPQQDAwNpADBmAjEAvvNhzwIQHWSVB7gYboiFBS+D\n"
"CBeQyh+KTOgNG3qxrdWBCUfvO6wIBHxcmbHtRwfSAjEAnbpV/KlK6O3t5nYBQnvI+GDZjVGLVTv7\n"
"jHvrZQnD+JbNR6iC8hZVdyR+EhCVBCyj\n"
"-----END CERTIFICATE-----\n"
"\n"
"emSign Root CA - C1\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIDczCCAlugAwIBAgILAK7PALrEzzL4Q7IwDQYJKoZIhvcNAQELBQAwVjELMAkGA1UEBhMCVVMx\n"
"EzARBgNVBAsTCmVtU2lnbiBQS0kxFDASBgNVBAoTC2VNdWRocmEgSW5jMRwwGgYDVQQDExNlbVNp\n"
"Z24gUm9vdCBDQSAtIEMxMB4XDTE4MDIxODE4MzAwMFoXDTQzMDIxODE4MzAwMFowVjELMAkGA1UE\n"
"BhMCVVMxEzARBgNVBAsTCmVtU2lnbiBQS0kxFDASBgNVBAoTC2VNdWRocmEgSW5jMRwwGgYDVQQD\n"
"ExNlbVNpZ24gUm9vdCBDQSAtIEMxMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAz+up\n"
"ufGZBczYKCFK83M0UYRWEPWgTywS4/oTmifQz/l5GnRfHXk5/Fv4cI7gklL35CX5VIPZHdPIWoU/\n"
"Xse2B+4+wM6ar6xWQio5JXDWv7V7Nq2s9nPczdcdioOl+yuQFTdrHCZH3DspVpNqs8FqOp099cGX\n"
"OFgFixwR4+S0uF2FHYP+eF8LRWgYSKVGczQ7/g/IdrvHGPMF0Ybzhe3nudkyrVWIzqa2kbBPrH4V\n"
"I5b2P/AgNBbeCsbEBEV5f6f9vtKppa+cxSMq9zwhbL2vj07FOrLzNBL834AaSaTUqZX3noleooms\n"
"lMuoaJuvimUnzYnu3Yy1aylwQ6BpC+S5DwIDAQABo0IwQDAdBgNVHQ4EFgQU/qHgcB4qAzlSWkK+\n"
"XJGFehiqTbUwDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQAD\n"
"ggEBAMJKVvoVIXsoounlHfv4LcQ5lkFMOycsxGwYFYDGrK9HWS8mC+M2sO87/kOXSTKZEhVb3xEp\n"
"/6tT+LvBeA+snFOvV71ojD1pM/CjoCNjO2RnIkSt1XHLVip4kqNPEjE2NuLe/gDEo2APJ62gsIq1\n"
"NnpSob0n9CAnYuhNlCQT5AoE6TyrLshDCUrGYQTlSTR+08TI9Q/Aqum6VF7zYytPT1DU/rl7mYw9\n"
"wC68AivTxEDkigcxHpvOJpkT+xHqmiIMERnHXhuBUDDIlhJu58tBf5E7oke3VIAb3ADMmpDqw8NQ\n"
"BmIMMMAVSKeoWXzhriKi4gp6D/piq1JM4fHfyr6DDUI=\n"
"-----END CERTIFICATE-----\n"
"\n"
"emSign ECC Root CA - C3\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICKzCCAbGgAwIBAgIKe3G2gla4EnycqDAKBggqhkjOPQQDAzBaMQswCQYDVQQGEwJVUzETMBEG\n"
"A1UECxMKZW1TaWduIFBLSTEUMBIGA1UEChMLZU11ZGhyYSBJbmMxIDAeBgNVBAMTF2VtU2lnbiBF\n"
"Q0MgUm9vdCBDQSAtIEMzMB4XDTE4MDIxODE4MzAwMFoXDTQzMDIxODE4MzAwMFowWjELMAkGA1UE\n"
"BhMCVVMxEzARBgNVBAsTCmVtU2lnbiBQS0kxFDASBgNVBAoTC2VNdWRocmEgSW5jMSAwHgYDVQQD\n"
"ExdlbVNpZ24gRUNDIFJvb3QgQ0EgLSBDMzB2MBAGByqGSM49AgEGBSuBBAAiA2IABP2lYa57JhAd\n"
"6bciMK4G9IGzsUJxlTm801Ljr6/58pc1kjZGDoeVjbk5Wum739D+yAdBPLtVb4OjavtisIGJAnB9\n"
"SMVK4+kiVCJNk7tCDK93nCOmfddhEc5lx/h//vXyqaNCMEAwHQYDVR0OBBYEFPtaSNCAIEDyqOkA\n"
"B2kZd6fmw/TPMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8EBTADAQH/MAoGCCqGSM49BAMDA2gA\n"
"MGUCMQC02C8Cif22TGK6Q04ThHK1rt0c3ta13FaPWEBaLd4gTCKDypOofu4SQMfWh0/434UCMBwU\n"
"ZOR8loMRnLDRWmFLpg9J0wD8ofzkpf9/rdcw0Md3f76BB1UwUCAU9Vc4CqgxUQ==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Hongkong Post Root CA 3\n"
"=======================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"dBb9HxEGmpv0\n"
"-----END CERTIFICATE-----\n"
"\n"
"Entrust Root Certification Authority - G4\n"
"=========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIGSzCCBDOgAwIBAgIRANm1Q3+vqTkPAAAAAFVlrVgwDQYJKoZIhvcNAQELBQAwgb4xCzAJBgNV\n"
"BAYTAlVTMRYwFAYDVQQKEw1FbnRydXN0LCBJbmMuMSgwJgYDVQQLEx9TZWUgd3d3LmVudHJ1c3Qu\n"
"bmV0L2xlZ2FsLXRlcm1zMTkwNwYDVQQLEzAoYykgMjAxNSBFbnRydXN0LCBJbmMuIC0gZm9yIGF1\n"
"dGhvcml6ZWQgdXNlIG9ubHkxMjAwBgNVBAMTKUVudHJ1c3QgUm9vdCBDZXJ0aWZpY2F0aW9uIEF1\n"
"dGhvcml0eSAtIEc0MB4XDTE1MDUyNzExMTExNloXDTM3MTIyNzExNDExNlowgb4xCzAJBgNVBAYT\n"
"AlVTMRYwFAYDVQQKEw1FbnRydXN0LCBJbmMuMSgwJgYDVQQLEx9TZWUgd3d3LmVudHJ1c3QubmV0\n"
"L2xlZ2FsLXRlcm1zMTkwNwYDVQQLEzAoYykgMjAxNSBFbnRydXN0LCBJbmMuIC0gZm9yIGF1dGhv\n"
"cml6ZWQgdXNlIG9ubHkxMjAwBgNVBAMTKUVudHJ1c3QgUm9vdCBDZXJ0aWZpY2F0aW9uIEF1dGhv\n"
"cml0eSAtIEc0MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAsewsQu7i0TD/pZJH4i3D\n"
"umSXbcr3DbVZwbPLqGgZ2K+EbTBwXX7zLtJTmeH+H17ZSK9dE43b/2MzTdMAArzE+NEGCJR5WIoV\n"
"3imz/f3ET+iq4qA7ec2/a0My3dl0ELn39GjUu9CH1apLiipvKgS1sqbHoHrmSKvS0VnM1n4j5pds\n"
"8ELl3FFLFUHtSUrJ3hCX1nbB76W1NhSXNdh4IjVS70O92yfbYVaCNNzLiGAMC1rlLAHGVK/XqsEQ\n"
"e9IFWrhAnoanw5CGAlZSCXqc0ieCU0plUmr1POeo8pyvi73TDtTUXm6Hnmo9RR3RXRv06QqsYJn7\n"
"ibT/mCzPfB3pAqoEmh643IhuJbNsZvc8kPNXwbMv9W3y+8qh+CmdRouzavbmZwe+LGcKKh9asj5X\n"
"xNMhIWNlUpEbsZmOeX7m640A2Vqq6nPopIICR5b+W45UYaPrL0swsIsjdXJ8ITzI9vF01Bx7owVV\n"
"7rtNOzK+mndmnqxpkCIHH2E6lr7lmk/MBTwoWdPBDFSoWWG9yHJM6Nyfh3+9nEg2XpWjDrk4JFX8\n"
"dWbrAuMINClKxuMrLzOg2qOGpRKX/YAr2hRC45K9PvJdXmd0LhyIRyk0X+IyqJwlN4y6mACXi0mW\n"
"Hv0liqzc2thddG5msP9E36EYxr5ILzeUePiVSj9/E15dWf10hkNjc0kCAwEAAaNCMEAwDwYDVR0T\n"
"AQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYEFJ84xFYjwznooHFs6FRM5Og6sb9n\n"
"MA0GCSqGSIb3DQEBCwUAA4ICAQAS5UKme4sPDORGpbZgQIeMJX6tuGguW8ZAdjwD+MlZ9POrYs4Q\n"
"jbRaZIxowLByQzTSGwv2LFPSypBLhmb8qoMi9IsabyZIrHZ3CL/FmFz0Jomee8O5ZDIBf9PD3Vht\n"
"7LGrhFV0d4QEJ1JrhkzO3bll/9bGXp+aEJlLdWr+aumXIOTkdnrG0CSqkM0gkLpHZPt/B7NTeLUK\n"
"YvJzQ85BK4FqLoUWlFPUa19yIqtRLULVAJyZv967lDtX/Zr1hstWO1uIAeV8KEsD+UmDfLJ/fOPt\n"
"jqF/YFOOVZ1QNBIPt5d7bIdKROf1beyAN/BYGW5KaHbwH5Lk6rWS02FREAutp9lfx1/cH6NcjKF+\n"
"m7ee01ZvZl4HliDtC3T7Zk6LERXpgUl+b7DUUH8i119lAg2m9IUe2K4GS0qn0jFmwvjO5QimpAKW\n"
"RGhXxNUzzxkvFMSUHHuk2fCfDrGA4tGeEWSpiBE6doLlYsKA2KSD7ZPvfC+QsDJMlhVoSFLUmQjA\n"
"JOgc47OlIQ6SwJAfzyBfyjs4x7dtOvPmRLgOMWuIjnDrnBdSqEGULoe256YSxXXfW8AKbnuk5F6G\n"
"+TaU33fD6Q3AOfF5u0aOq0NZJ7cguyPpVkAh7DE9ZapD8j3fcEThuk0mEDuYn/PIjhs4ViFqUZPT\n"
"kcpG2om3PVODLAgfi49T3f+sHw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"Microsoft ECC Root Certificate Authority 2017\n"
"=============================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICWTCCAd+gAwIBAgIQZvI9r4fei7FK6gxXMQHC7DAKBggqhkjOPQQDAzBlMQswCQYDVQQGEwJV\n"
"UzEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMTYwNAYDVQQDEy1NaWNyb3NvZnQgRUND\n"
"IFJvb3QgQ2VydGlmaWNhdGUgQXV0aG9yaXR5IDIwMTcwHhcNMTkxMjE4MjMwNjQ1WhcNNDIwNzE4\n"
"MjMxNjA0WjBlMQswCQYDVQQGEwJVUzEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMTYw\n"
"NAYDVQQDEy1NaWNyb3NvZnQgRUNDIFJvb3QgQ2VydGlmaWNhdGUgQXV0aG9yaXR5IDIwMTcwdjAQ\n"
"BgcqhkjOPQIBBgUrgQQAIgNiAATUvD0CQnVBEyPNgASGAlEvaqiBYgtlzPbKnR5vSmZRogPZnZH6\n"
"thaxjG7efM3beaYvzrvOcS/lpaso7GMEZpn4+vKTEAXhgShC48Zo9OYbhGBKia/teQ87zvH2RPUB\n"
"eMCjVDBSMA4GA1UdDwEB/wQEAwIBhjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBTIy5lycFIM\n"
"+Oa+sgRXKSrPQhDtNTAQBgkrBgEEAYI3FQEEAwIBADAKBggqhkjOPQQDAwNoADBlAjBY8k3qDPlf\n"
"Xu5gKcs68tvWMoQZP3zVL8KxzJOuULsJMsbG7X7JNpQS5GiFBqIb0C8CMQCZ6Ra0DvpWSNSkMBaR\n"
"eNtUjGUBiudQZsIxtzm6uBoiB078a1QWIP8rtedMDE2mT3M=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Microsoft RSA Root Certificate Authority 2017\n"
"=============================================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"5KbvtwEwXlGjefVwaaZBRA+GsCyRxj3qrg+E\n"
"-----END CERTIFICATE-----\n"
"\n"
"e-Szigno Root CA 2017\n"
"=====================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICQDCCAeWgAwIBAgIMAVRI7yH9l1kN9QQKMAoGCCqGSM49BAMCMHExCzAJBgNVBAYTAkhVMREw\n"
"DwYDVQQHDAhCdWRhcGVzdDEWMBQGA1UECgwNTWljcm9zZWMgTHRkLjEXMBUGA1UEYQwOVkFUSFUt\n"
"MjM1ODQ0OTcxHjAcBgNVBAMMFWUtU3ppZ25vIFJvb3QgQ0EgMjAxNzAeFw0xNzA4MjIxMjA3MDZa\n"
"Fw00MjA4MjIxMjA3MDZaMHExCzAJBgNVBAYTAkhVMREwDwYDVQQHDAhCdWRhcGVzdDEWMBQGA1UE\n"
"CgwNTWljcm9zZWMgTHRkLjEXMBUGA1UEYQwOVkFUSFUtMjM1ODQ0OTcxHjAcBgNVBAMMFWUtU3pp\n"
"Z25vIFJvb3QgQ0EgMjAxNzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABJbcPYrYsHtvxie+RJCx\n"
"s1YVe45DJH0ahFnuY2iyxl6H0BVIHqiQrb1TotreOpCmYF9oMrWGQd+HWyx7xf58etqjYzBhMA8G\n"
"A1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgEGMB0GA1UdDgQWBBSHERUI0arBeAyxr87GyZDv\n"
"vzAEwDAfBgNVHSMEGDAWgBSHERUI0arBeAyxr87GyZDvvzAEwDAKBggqhkjOPQQDAgNJADBGAiEA\n"
"tVfd14pVCzbhhkT61NlojbjcI4qKDdQvfepz7L9NbKgCIQDLpbQS+ue16M9+k/zzNY9vTlp8tLxO\n"
"svxyqltZ+efcMQ==\n"
"-----END CERTIFICATE-----\n"
"\n"
"certSIGN Root CA G2\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFRzCCAy+gAwIBAgIJEQA0tk7GNi02MA0GCSqGSIb3DQEBCwUAMEExCzAJBgNVBAYTAlJPMRQw\n"
"EgYDVQQKEwtDRVJUU0lHTiBTQTEcMBoGA1UECxMTY2VydFNJR04gUk9PVCBDQSBHMjAeFw0xNzAy\n"
"MDYwOTI3MzVaFw00MjAyMDYwOTI3MzVaMEExCzAJBgNVBAYTAlJPMRQwEgYDVQQKEwtDRVJUU0lH\n"
"TiBTQTEcMBoGA1UECxMTY2VydFNJR04gUk9PVCBDQSBHMjCCAiIwDQYJKoZIhvcNAQEBBQADggIP\n"
"ADCCAgoCggIBAMDFdRmRfUR0dIf+DjuW3NgBFszuY5HnC2/OOwppGnzC46+CjobXXo9X69MhWf05\n"
"N0IwvlDqtg+piNguLWkh59E3GE59kdUWX2tbAMI5Qw02hVK5U2UPHULlj88F0+7cDBrZuIt4Imfk\n"
"abBoxTzkbFpG583H+u/E7Eu9aqSs/cwoUe+StCmrqzWaTOTECMYmzPhpn+Sc8CnTXPnGFiWeI8Mg\n"
"wT0PPzhAsP6CRDiqWhqKa2NYOLQV07YRaXseVO6MGiKscpc/I1mbySKEwQdPzH/iV8oScLumZfNp\n"
"dWO9lfsbl83kqK/20U6o2YpxJM02PbyWxPFsqa7lzw1uKA2wDrXKUXt4FMMgL3/7FFXhEZn91Qqh\n"
"ngLjYl/rNUssuHLoPj1PrCy7Lobio3aP5ZMqz6WryFyNSwb/EkaseMsUBzXgqd+L6a8VTxaJW732\n"
"jcZZroiFDsGJ6x9nxUWO/203Nit4ZoORUSs9/1F3dmKh7Gc+PoGD4FapUB8fepmrY7+EF3fxDTvf\n"
"95xhszWYijqy7DwaNz9+j5LP2RIUZNoQAhVB/0/E6xyjyfqZ90bp4RjZsbgyLcsUDFDYg2WD7rlc\n"
"z8sFWkz6GZdr1l0T08JcVLwyc6B49fFtHsufpaafItzRUZ6CeWRgKRM+o/1Pcmqr4tTluCRVLERL\n"
"iohEnMqE0yo7AgMBAAGjQjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgEGMB0GA1Ud\n"
"DgQWBBSCIS1mxteg4BXrzkwJd8RgnlRuAzANBgkqhkiG9w0BAQsFAAOCAgEAYN4auOfyYILVAzOB\n"
"ywaK8SJJ6ejqkX/GM15oGQOGO0MBzwdw5AgeZYWR5hEit/UCI46uuR59H35s5r0l1ZUa8gWmr4UC\n"
"b6741jH/JclKyMeKqdmfS0mbEVeZkkMR3rYzpMzXjWR91M08KCy0mpbqTfXERMQlqiCA2ClV9+BB\n"
"/AYm/7k29UMUA2Z44RGx2iBfRgB4ACGlHgAoYXhvqAEBj500mv/0OJD7uNGzcgbJceaBxXntC6Z5\n"
"8hMLnPddDnskk7RI24Zf3lCGeOdA5jGokHZwYa+cNywRtYK3qq4kNFtyDGkNzVmf9nGvnAvRCjj5\n"
"BiKDUyUM/FHE5r7iOZULJK2v0ZXkltd0ZGtxTgI8qoXzIKNDOXZbbFD+mpwUHmUUihW9o4JFWklW\n"
"atKcsWMy5WHgUyIOpwpJ6st+H6jiYoD2EEVSmAYY3qXNL3+q1Ok+CHLsIwMCPKaq2LxndD0UF/tU\n"
"Sxfj03k9bWtJySgOLnRQvwzZRjoQhsmnP+mg7H/rpXdYaXHmgwo38oZJar55CJD2AhZkPuXaTH4M\n"
"NMn5X7azKFGnpyuqSfqNZSlO42sTp5SjLVFteAxEy9/eCG/Oo2Sr05WE1LlSVHJ7liXMvGnjSG4N\n"
"0MedJ5qq+BOS3R7fY581qRY27Iy4g/Q9iY/NtBde17MXQRBdJ3NghVdJIgc=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Trustwave Global Certification Authority\n"
"========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"29FpHOTKyeC2nOnOcXHebD8WpHk=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Trustwave Global ECC P256 Certification Authority\n"
"=================================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICYDCCAgegAwIBAgIMDWpfCD8oXD5Rld9dMAoGCCqGSM49BAMCMIGRMQswCQYDVQQGEwJVUzER\n"
"MA8GA1UECBMISWxsaW5vaXMxEDAOBgNVBAcTB0NoaWNhZ28xITAfBgNVBAoTGFRydXN0d2F2ZSBI\n"
"b2xkaW5ncywgSW5jLjE6MDgGA1UEAxMxVHJ1c3R3YXZlIEdsb2JhbCBFQ0MgUDI1NiBDZXJ0aWZp\n"
"Y2F0aW9uIEF1dGhvcml0eTAeFw0xNzA4MjMxOTM1MTBaFw00MjA4MjMxOTM1MTBaMIGRMQswCQYD\n"
"VQQGEwJVUzERMA8GA1UECBMISWxsaW5vaXMxEDAOBgNVBAcTB0NoaWNhZ28xITAfBgNVBAoTGFRy\n"
"dXN0d2F2ZSBIb2xkaW5ncywgSW5jLjE6MDgGA1UEAxMxVHJ1c3R3YXZlIEdsb2JhbCBFQ0MgUDI1\n"
"NiBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABH77bOYj\n"
"43MyCMpg5lOcunSNGLB4kFKA3TjASh3RqMyTpJcGOMoNFWLGjgEqZZ2q3zSRLoHB5DOSMcT9CTqm\n"
"P62jQzBBMA8GA1UdEwEB/wQFMAMBAf8wDwYDVR0PAQH/BAUDAwcGADAdBgNVHQ4EFgQUo0EGrJBt\n"
"0UrrdaVKEJmzsaGLSvcwCgYIKoZIzj0EAwIDRwAwRAIgB+ZU2g6gWrKuEZ+Hxbb/ad4lvvigtwjz\n"
"RM4q3wghDDcCIC0mA6AFvWvR9lz4ZcyGbbOcNEhjhAnFjXca4syc4XR7\n"
"-----END CERTIFICATE-----\n"
"\n"
"Trustwave Global ECC P384 Certification Authority\n"
"=================================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICnTCCAiSgAwIBAgIMCL2Fl2yZJ6SAaEc7MAoGCCqGSM49BAMDMIGRMQswCQYDVQQGEwJVUzER\n"
"MA8GA1UECBMISWxsaW5vaXMxEDAOBgNVBAcTB0NoaWNhZ28xITAfBgNVBAoTGFRydXN0d2F2ZSBI\n"
"b2xkaW5ncywgSW5jLjE6MDgGA1UEAxMxVHJ1c3R3YXZlIEdsb2JhbCBFQ0MgUDM4NCBDZXJ0aWZp\n"
"Y2F0aW9uIEF1dGhvcml0eTAeFw0xNzA4MjMxOTM2NDNaFw00MjA4MjMxOTM2NDNaMIGRMQswCQYD\n"
"VQQGEwJVUzERMA8GA1UECBMISWxsaW5vaXMxEDAOBgNVBAcTB0NoaWNhZ28xITAfBgNVBAoTGFRy\n"
"dXN0d2F2ZSBIb2xkaW5ncywgSW5jLjE6MDgGA1UEAxMxVHJ1c3R3YXZlIEdsb2JhbCBFQ0MgUDM4\n"
"NCBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTB2MBAGByqGSM49AgEGBSuBBAAiA2IABGvaDXU1CDFH\n"
"Ba5FmVXxERMuSvgQMSOjfoPTfygIOiYaOs+Xgh+AtycJj9GOMMQKmw6sWASr9zZ9lCOkmwqKi6vr\n"
"/TklZvFe/oyujUF5nQlgziip04pt89ZF1PKYhDhloKNDMEEwDwYDVR0TAQH/BAUwAwEB/zAPBgNV\n"
"HQ8BAf8EBQMDBwYAMB0GA1UdDgQWBBRVqYSJ0sEyvRjLbKYHTsjnnb6CkDAKBggqhkjOPQQDAwNn\n"
"ADBkAjA3AZKXRRJ+oPM+rRk6ct30UJMDEr5E0k9BpIycnR+j9sKS50gU/k6bpZFXrsY3crsCMGcl\n"
"CrEMXu6pY5Jv5ZAL/mYiykf9ijH3g/56vxC+GCsej/YpHpRZ744hN8tRmKVuSw==\n"
"-----END CERTIFICATE-----\n"
"\n"
"NAVER Global Root Certification Authority\n"
"=========================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFojCCA4qgAwIBAgIUAZQwHqIL3fXFMyqxQ0Rx+NZQTQ0wDQYJKoZIhvcNAQEMBQAwaTELMAkG\n"
"A1UEBhMCS1IxJjAkBgNVBAoMHU5BVkVSIEJVU0lORVNTIFBMQVRGT1JNIENvcnAuMTIwMAYDVQQD\n"
"DClOQVZFUiBHbG9iYWwgUm9vdCBDZXJ0aWZpY2F0aW9uIEF1dGhvcml0eTAeFw0xNzA4MTgwODU4\n"
"NDJaFw0zNzA4MTgyMzU5NTlaMGkxCzAJBgNVBAYTAktSMSYwJAYDVQQKDB1OQVZFUiBCVVNJTkVT\n"
"UyBQTEFURk9STSBDb3JwLjEyMDAGA1UEAwwpTkFWRVIgR2xvYmFsIFJvb3QgQ2VydGlmaWNhdGlv\n"
"biBBdXRob3JpdHkwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQC21PGTXLVAiQqrDZBb\n"
"UGOukJR0F0Vy1ntlWilLp1agS7gvQnXp2XskWjFlqxcX0TM62RHcQDaH38dq6SZeWYp34+hInDEW\n"
"+j6RscrJo+KfziFTowI2MMtSAuXaMl3Dxeb57hHHi8lEHoSTGEq0n+USZGnQJoViAbbJAh2+g1G7\n"
"XNr4rRVqmfeSVPc0W+m/6imBEtRTkZazkVrd/pBzKPswRrXKCAfHcXLJZtM0l/aM9BhK4dA9WkW2\n"
"aacp+yPOiNgSnABIqKYPszuSjXEOdMWLyEz59JuOuDxp7W87UC9Y7cSw0BwbagzivESq2M0UXZR4\n"
"Yb8ObtoqvC8MC3GmsxY/nOb5zJ9TNeIDoKAYv7vxvvTWjIcNQvcGufFt7QSUqP620wbGQGHfnZ3z\n"
"VHbOUzoBppJB7ASjjw2i1QnK1sua8e9DXcCrpUHPXFNwcMmIpi3Ua2FzUCaGYQ5fG8Ir4ozVu53B\n"
"A0K6lNpfqbDKzE0K70dpAy8i+/Eozr9dUGWokG2zdLAIx6yo0es+nPxdGoMuK8u180SdOqcXYZai\n"
"cdNwlhVNt0xz7hlcxVs+Qf6sdWA7G2POAN3aCJBitOUt7kinaxeZVL6HSuOpXgRM6xBtVNbv8ejy\n"
"YhbLgGvtPe31HzClrkvJE+2KAQHJuFFYwGY6sWZLxNUxAmLpdIQM201GLQIDAQABo0IwQDAdBgNV\n"
"HQ4EFgQU0p+I36HNLL3s9TsBAZMzJ7LrYEswDgYDVR0PAQH/BAQDAgEGMA8GA1UdEwEB/wQFMAMB\n"
"Af8wDQYJKoZIhvcNAQEMBQADggIBADLKgLOdPVQG3dLSLvCkASELZ0jKbY7gyKoNqo0hV4/GPnrK\n"
"21HUUrPUloSlWGB/5QuOH/XcChWB5Tu2tyIvCZwTFrFsDDUIbatjcu3cvuzHV+YwIHHW1xDBE1UB\n"
"jCpD5EHxzzp6U5LOogMFDTjfArsQLtk70pt6wKGm+LUx5vR1yblTmXVHIloUFcd4G7ad6Qz4G3bx\n"
"hYTeodoS76TiEJd6eN4MUZeoIUCLhr0N8F5OSza7OyAfikJW4Qsav3vQIkMsRIz75Sq0bBwcupTg\n"
"E34h5prCy8VCZLQelHsIJchxzIdFV4XTnyliIoNRlwAYl3dqmJLJfGBs32x9SuRwTMKeuB330DTH\n"
"D8z7p/8Dvq1wkNoL3chtl1+afwkyQf3NosxabUzyqkn+Zvjp2DXrDige7kgvOtB5CTh8piKCk5XQ\n"
"A76+AqAF3SAi428diDRgxuYKuQl1C/AH6GmWNcf7I4GOODm4RStDeKLRLBT/DShycpWbXgnbiUSY\n"
"qqFJu3FS8r/2/yehNq+4tneI3TqkbZs0kNwUXTC/t+sX5Ie3cdCh13cV1ELX8vMxmV2b3RZtP+oG\n"
"I/hGoiLtk/bdmuYqh7GYVPEi92tF4+KOdh2ajcQGjTa3FPOdVGm3jjzVpG2Tgbet9r1ke8LJaDmg\n"
"kpzNNIaRkPpkUZ3+/uul9XXeifdy\n"
"-----END CERTIFICATE-----\n"
"\n"
"AC RAIZ FNMT-RCM SERVIDORES SEGUROS\n"
"===================================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICbjCCAfOgAwIBAgIQYvYybOXE42hcG2LdnC6dlTAKBggqhkjOPQQDAzB4MQswCQYDVQQGEwJF\n"
"UzERMA8GA1UECgwIRk5NVC1SQ00xDjAMBgNVBAsMBUNlcmVzMRgwFgYDVQRhDA9WQVRFUy1RMjgy\n"
"NjAwNEoxLDAqBgNVBAMMI0FDIFJBSVogRk5NVC1SQ00gU0VSVklET1JFUyBTRUdVUk9TMB4XDTE4\n"
"MTIyMDA5MzczM1oXDTQzMTIyMDA5MzczM1oweDELMAkGA1UEBhMCRVMxETAPBgNVBAoMCEZOTVQt\n"
"UkNNMQ4wDAYDVQQLDAVDZXJlczEYMBYGA1UEYQwPVkFURVMtUTI4MjYwMDRKMSwwKgYDVQQDDCNB\n"
"QyBSQUlaIEZOTVQtUkNNIFNFUlZJRE9SRVMgU0VHVVJPUzB2MBAGByqGSM49AgEGBSuBBAAiA2IA\n"
"BPa6V1PIyqvfNkpSIeSX0oNnnvBlUdBeh8dHsVnyV0ebAAKTRBdp20LHsbI6GA60XYyzZl2hNPk2\n"
"LEnb80b8s0RpRBNm/dfF/a82Tc4DTQdxz69qBdKiQ1oKUm8BA06Oi6NCMEAwDwYDVR0TAQH/BAUw\n"
"AwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYEFAG5L++/EYZg8k/QQW6rcx/n0m5JMAoGCCqG\n"
"SM49BAMDA2kAMGYCMQCuSuMrQMN0EfKVrRYj3k4MGuZdpSRea0R7/DjiT8ucRRcRTBQnJlU5dUoD\n"
"zBOQn5ICMQD6SmxgiHPz7riYYqnOK8LZiqZwMR2vsJRM60/G49HzYqc8/5MuB1xJAWdpEgJyv+c=\n"
"-----END CERTIFICATE-----\n"
"\n"
"GlobalSign Root R46\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFWjCCA0KgAwIBAgISEdK7udcjGJ5AXwqdLdDfJWfRMA0GCSqGSIb3DQEBDAUAMEYxCzAJBgNV\n"
"BAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMRwwGgYDVQQDExNHbG9iYWxTaWduIFJv\n"
"b3QgUjQ2MB4XDTE5MDMyMDAwMDAwMFoXDTQ2MDMyMDAwMDAwMFowRjELMAkGA1UEBhMCQkUxGTAX\n"
"BgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExHDAaBgNVBAMTE0dsb2JhbFNpZ24gUm9vdCBSNDYwggIi\n"
"MA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCsrHQy6LNl5brtQyYdpokNRbopiLKkHWPd08Es\n"
"CVeJOaFV6Wc0dwxu5FUdUiXSE2te4R2pt32JMl8Nnp8semNgQB+msLZ4j5lUlghYruQGvGIFAha/\n"
"r6gjA7aUD7xubMLL1aa7DOn2wQL7Id5m3RerdELv8HQvJfTqa1VbkNud316HCkD7rRlr+/fKYIje\n"
"2sGP1q7Vf9Q8g+7XFkyDRTNrJ9CG0Bwta/OrffGFqfUo0q3v84RLHIf8E6M6cqJaESvWJ3En7YEt\n"
"bWaBkoe0G1h6zD8K+kZPTXhc+CtI4wSEy132tGqzZfxCnlEmIyDLPRT5ge1lFgBPGmSXZgjPjHvj\n"
"K8Cd+RTyG/FWaha/LIWFzXg4mutCagI0GIMXTpRW+LaCtfOW3T3zvn8gdz57GSNrLNRyc0NXfeD4\n"
"12lPFzYE+cCQYDdF3uYM2HSNrpyibXRdQr4G9dlkbgIQrImwTDsHTUB+JMWKmIJ5jqSngiCNI/on\n"
"ccnfxkF0oE32kRbcRoxfKWMxWXEM2G/CtjJ9++ZdU6Z+Ffy7dXxd7Pj2Fxzsx2sZy/N78CsHpdls\n"
"eVR2bJ0cpm4O6XkMqCNqo98bMDGfsVR7/mrLZqrcZdCinkqaByFrgY/bxFn63iLABJzjqls2k+g9\n"
"vXqhnQt2sQvHnf3PmKgGwvgqo6GDoLclcqUC4wIDAQABo0IwQDAOBgNVHQ8BAf8EBAMCAYYwDwYD\n"
"VR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA1yrc4GHqMywptWU4jaWSf8FmSwwDQYJKoZIhvcNAQEM\n"
"BQADggIBAHx47PYCLLtbfpIrXTncvtgdokIzTfnvpCo7RGkerNlFo048p9gkUbJUHJNOxO97k4Vg\n"
"JuoJSOD1u8fpaNK7ajFxzHmuEajwmf3lH7wvqMxX63bEIaZHU1VNaL8FpO7XJqti2kM3S+LGteWy\n"
"gxk6x9PbTZ4IevPuzz5i+6zoYMzRx6Fcg0XERczzF2sUyQQCPtIkpnnpHs6i58FZFZ8d4kuaPp92\n"
"CC1r2LpXFNqD6v6MVenQTqnMdzGxRBF6XLE+0xRFFRhiJBPSy03OXIPBNvIQtQ6IbbjhVp+J3pZm\n"
"OUdkLG5NrmJ7v2B0GbhWrJKsFjLtrWhV/pi60zTe9Mlhww6G9kuEYO4Ne7UyWHmRVSyBQ7N0H3qq\n"
"JZ4d16GLuc1CLgSkZoNNiTW2bKg2SnkheCLQQrzRQDGQob4Ez8pn7fXwgNNgyYMqIgXQBztSvwye\n"
"qiv5u+YfjyW6hY0XHgL+XVAEV8/+LbzvXMAaq7afJMbfc2hIkCwU9D9SGuTSyxTDYWnP4vkYxboz\n"
"nxSjBF25cfe1lNj2M8FawTSLfJvdkzrnE6JwYZ+vj+vYxXX4M2bUdGc6N3ec592kD3ZDZopD8p/7\n"
"DEJ4Y9HiD2971KE9dJeFt0g5QdYg/NA6s/rob8SKunE3vouXsXgxT7PntgMTzlSdriVZzH81Xwj3\n"
"QEUxeCp6\n"
"-----END CERTIFICATE-----\n"
"\n"
"GlobalSign Root E46\n"
"===================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICCzCCAZGgAwIBAgISEdK7ujNu1LzmJGjFDYQdmOhDMAoGCCqGSM49BAMDMEYxCzAJBgNVBAYT\n"
"AkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMRwwGgYDVQQDExNHbG9iYWxTaWduIFJvb3Qg\n"
"RTQ2MB4XDTE5MDMyMDAwMDAwMFoXDTQ2MDMyMDAwMDAwMFowRjELMAkGA1UEBhMCQkUxGTAXBgNV\n"
"BAoTEEdsb2JhbFNpZ24gbnYtc2ExHDAaBgNVBAMTE0dsb2JhbFNpZ24gUm9vdCBFNDYwdjAQBgcq\n"
"hkjOPQIBBgUrgQQAIgNiAAScDrHPt+ieUnd1NPqlRqetMhkytAepJ8qUuwzSChDH2omwlwxwEwkB\n"
"jtjqR+q+soArzfwoDdusvKSGN+1wCAB16pMLey5SnCNoIwZD7JIvU4Tb+0cUB+hflGddyXqBPCCj\n"
"QjBAMA4GA1UdDwEB/wQEAwIBhjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBQxCpCPtsad0kRL\n"
"gLWi5h+xEk8blTAKBggqhkjOPQQDAwNoADBlAjEA31SQ7Zvvi5QCkxeCmb6zniz2C5GMn0oUsfZk\n"
"vLtoURMMA/cVi4RguYv/Uo7njLwcAjA8+RHUjE7AwWHCFUyqqx0LMV87HOIAl0Qx5v5zli/altP+\n"
"CAezNIm8BZ/3Hobui3A=\n"
"-----END CERTIFICATE-----\n"
"\n"
"GLOBALTRUST 2020\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"ANF Secure Server Root CA\n"
"=========================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
"Certum EC-384 CA\n"
"================\n"
"-----BEGIN CERTIFICATE-----\n"
"MIICZTCCAeugAwIBAgIQeI8nXIESUiClBNAt3bpz9DAKBggqhkjOPQQDAzB0MQswCQYDVQQGEwJQ\n"
"TDEhMB8GA1UEChMYQXNzZWNvIERhdGEgU3lzdGVtcyBTLkEuMScwJQYDVQQLEx5DZXJ0dW0gQ2Vy\n"
"dGlmaWNhdGlvbiBBdXRob3JpdHkxGTAXBgNVBAMTEENlcnR1bSBFQy0zODQgQ0EwHhcNMTgwMzI2\n"
"MDcyNDU0WhcNNDMwMzI2MDcyNDU0WjB0MQswCQYDVQQGEwJQTDEhMB8GA1UEChMYQXNzZWNvIERh\n"
"dGEgU3lzdGVtcyBTLkEuMScwJQYDVQQLEx5DZXJ0dW0gQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkx\n"
"GTAXBgNVBAMTEENlcnR1bSBFQy0zODQgQ0EwdjAQBgcqhkjOPQIBBgUrgQQAIgNiAATEKI6rGFtq\n"
"vm5kN2PkzeyrOvfMobgOgknXhimfoZTy42B4mIF4Bk3y7JoOV2CDn7TmFy8as10CW4kjPMIRBSqn\n"
"iBMY81CE1700LCeJVf/OTOffph8oxPBUw7l8t1Ot68KjQjBAMA8GA1UdEwEB/wQFMAMBAf8wHQYD\n"
"VR0OBBYEFI0GZnQkdjrzife81r1HfS+8EF9LMA4GA1UdDwEB/wQEAwIBBjAKBggqhkjOPQQDAwNo\n"
"ADBlAjADVS2m5hjEfO/JUG7BJw+ch69u1RsIGL2SKcHvlJF40jocVYli5RsJHrpka/F2tNQCMQC0\n"
"QoSZ/6vnnvuRlydd3LBbMHHOXjgaatkl5+r3YZJW+OraNsKHZZYuciUvf9/DE8k=\n"
"-----END CERTIFICATE-----\n"
"\n"
"Certum Trusted Root CA\n"
"======================\n"
"-----BEGIN CERTIFICATE-----\n"
"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\n"
"-----END CERTIFICATE-----\n"
"\n"
, 0x318ff},
{"ui/openjkdf2.uni", 
"MSGS 100          # <--- DON'T FORGET TO UPDATE THIS COUNT\n"
"\n"
"#  \"<key>\"     <unused number>   \"<string>\"\n"
"\n"
"#******************************\n"
"#  OpenJKDF2 added UI strings\n"
"#******************************\n"
"   \"OPENJKDF2_EXAMPLE\"    0  \"Example!\"\n"
"\n"
"#******************************\n"
"#  Gameplay\n"
"#******************************\n"
"   \"GUIEXT_SHOW_SABER_CROSSHAIR\"          0 \"Show Crosshair with lightsaber\"\n"
"   \"GUIEXT_SHOW_SABER_CROSSHAIR_HINT\"     0 \"When this is enabled the crosshair is shown when the lightsaber is equipped\"\n"
"   \"GUIEXT_SHOW_FIST_CROSSHAIR\"           0 \"Show Crosshair with fist\"\n"
"   \"GUIEXT_SHOW_FIST_CROSSHAIR_HINT\"      0 \"When this is enabled the crosshair is shown when the fist is equipped\"\n"
"   \"GUIEXT_CROSSHAIR_SCALE\"               0 \"Crosshair Scale\"\n"
"   \"GUIEXT_CROSSHAIR_SCALE_HINT\"          0 \"Adjust the size of the crosshair (from 0% to 200%)\"\n"
"\n"
"#******************************\n"
"#  Display\n"
"#******************************\n"
"   \"GUIEXT_FOV\"                           0 \"FOV\"\n"
"   \"GUIEXT_FOV_HINT\"                      0 \"Set FOV\"\n"
"   \"GUIEXT_FOV_VERTICAL\"                  0 \"FOV is vertical (Hor+)\"\n"
"   \"GUIEXT_EN_FULLSCREEN\"                 0 \"Enable Fullscreen\"\n"
"   \"GUIEXT_EN_HIDPI\"                      0 \"Enable HiDPI\"\n"
"   \"GUIEXT_EN_TEXTURE_FILTERING\"          0 \"Enable Texture Filtering\"\n"
"   \"GUIEXT_EN_SQUARE_ASPECT\"              0 \"Use 1:1 aspect\"\n"
"   \"GUIEXT_FPS_LIMIT\"                     0 \"FPS Limit\"\n"
"   \"GUIEXT_FPS_LIMIT_HINT\"                0 \"Set FPS limit\"\n"
"   \"GUIEXT_EN_VSYNC\"                      0 \"Enable VSync\"\n"
"   \"GUIEXT_EN_BLOOM\"                      0 \"Enable Bloom\"\n"
"   \"GUIEXT_EN_SSAO\"                       0 \"Enable SSAO\"\n"
"   \"GUIEXT_SSAA_MULT\"                     0 \"SSAA Multiplier:\"\n"
"   \"GUIEXT_GAMMA_VAL\"                     0 \"Gamma Value:\"\n"
"   \"GUIEXT_HUD_SCALE\"                     0 \"HUD Scale:\"\n"
"\n"
"   \"GUIEXT_EN_JKGFXMOD\"                   0 \"Enable jkgfxmod\"\n"
"   \"GUIEXT_EN_JKGFXMOD_HINT\"              0 \"Overrides in-game textures with textures from jkgm folder.\"\n"
"   \"GUIEXT_EN_TEXTURE_PRECACHE\"           0 \"Enable texture precaching\"\n"
"   \"GUIEXT_EN_TEXTURE_PRECACHE_HINT\"      0 \"Loads all material textures ahead-of-time instead of just-in-time.\"\n"
"\n"
"#******************************\n"
"#  Quake Console and Updates\n"
"#******************************\n"
"   \"GUIEXT_UPDATE_IS_AVAIL\"                   0 \"An update is available: %S => %S\"\n"
"   \"GUIEXT_UPDATE_CLICK_TO_DL\"                0 \"Click here to download.\"\n"
"   \"GUIEXT_UPDATE_DOWNLOADING\"                0 \"Downloading...\"\n"
"   \"GUIEXT_UPDATE_COMPLETE_RESTART\"           0 \"Update complete, restart to apply.\"\n"
"   \"GUIEXT_UPDATE_COMPLETE_SEMIAUTO\"          0 \"Update downloaded, complete installation and restart.\"\n"
"\n"
"\n"
"#******************************\n"
"#  Multiplayer Setup\n"
"#******************************\n"
"   \"GUIEXT_DEDICATED_SERVER\"        0 \"Dedicated Server\"\n"
"   \"GUIEXT_DEDICATED_SERVER_HINT\"   0 \"Launch server without participating as a player.\"\n"
"   \"GUIEXT_COOP\"                    0 \"Experimental Co-op\"\n"
"   \"GUIEXT_COOP_HINT\"               0 \"Launch server with actors enabled.\"\n"
"   \"GUIEXT_SERVER_PORT\"             0 \"Server Port:\"\n"
"\n"
"   #\"GUIEXT_\"                0 \"\"\n"
"\n"
"#******************************\n"
"#  General\n"
"#******************************\n"
"   \"GUIEXT_DISABLE_MISSION_CONFIRMATION\"        0 \"Disable mission start confirmation.\"\n"
"   \"GUIEXT_DISABLE_MISSION_CONFIRMATION_HINT\"   0 \"Enter the mission as soon as the level is loaded.\"\n"
"\n"
"   \"GUIEXT_INCONSISTENT_PHYS\"                   0 \"Restore inconsistent physics\"\n"
"   \"GUIEXT_INCONSISTENT_PHYS_HINT\"              0 \"Sets physics delta to the render framerate instead of 150Hz.\"\n"
"\n"
"   \"GUIEXT_CORPSE_DESPAWN\"                      0 \"Disable corpse despawning\"\n"
"   \"GUIEXT_CORPSE_DESPAWN_HINT\"                 0 \"Don't automatically despawn corpse bodies.\"\n"
"\n"
"   \"GUIEXT_50HZ_MIDAIR_PHYS\"                    0 \"Restore 50Hz midair player physics\"\n"
"   \"GUIEXT_50HZ_MIDAIR_PHYS_HINT\"               0 \"Player physics and POV will be stepped at 50Hz while midair.\"\n"
"\n"
"END\n"
"\n"
, 0xf96},
{"ui/openjkdf2_i8n.uni", 
"MSGS 2          # <--- DON'T FORGET TO UPDATE THIS COUNT\n"
"\n"
"#  \"<key>\"     <unused number>   \"<string>\"\n"
"\n"
"#******************************\n"
"#  This file can override the following:\n"
"#   - ui/openjkdf2.uni\n"
"#   - ui/jkstrings.uni\n"
"#   - misc/cogStrings.uni (in some circumstances, WIP)\n"
"#   - misc/sithStrings.uni\n"
"#******************************\n"
"   \"OPENJKDF2_EXAMPLE\"    0  \"Example override!\"\n"
"\n"
"END\n"
"\n"
, 0x186},
};
