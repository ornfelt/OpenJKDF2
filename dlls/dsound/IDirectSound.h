
#ifndef IDIRECTSOUND_H
#define IDIRECTSOUND_H

#include <stdint.h>
#include <QObject>
#include <unicorn/unicorn.h>

#include "vm.h"
#include "dlls/kernel32.h"
#include "dlls/winutils.h"

typedef struct WAVEFORMATEX 
{
    uint16_t wFormatTag;
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
    uint16_t cbSize;
} WAVEFORMATEX;

typedef struct DSBUFFERDESC 
{
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwBufferBytes;
    uint32_t dwReserved;
    vm_ptr<WAVEFORMATEX*> lpwfxFormat;
    uint8_t guid3DAlgorithm[0x20];
} DSBUFFERDESC;

struct dsndbuffer_ext
{
    uint32_t lpVtbl;
    uint8_t padding[0x200];
    vm_ptr<uint8_t *> buffer;
    uint32_t size;
    int channel;
    int volume;
};

class IDirectSound : public QObject
{
Q_OBJECT

public:

    Q_INVOKABLE IDirectSound() {}

    /*** Base ***/
    Q_INVOKABLE uint32_t QueryInterface(void* this_ptr, uint8_t* iid, uint32_t* lpInterface)
    {
        std::string iid_str = guid_to_string(iid);
        printf("STUB: IDirectSound::QueryInterface %s\n", iid_str.c_str());
        
        return GlobalQueryInterface(iid_str, lpInterface);
    }

    Q_INVOKABLE void AddRef(void* this_ptr)
    {
        printf("STUB: IDirectSound::AddRef\n");
    }

    Q_INVOKABLE void Release(void* this_ptr)
    {
        printf("STUB: IDirectSound::Release\n");
        
        GlobalRelease(this_ptr);
    }
    
    /*** IDirectSound ***/
    Q_INVOKABLE uint32_t CreateSoundBuffer(void* this_ptr, DSBUFFERDESC* pcDSBufferDesc, uint32_t *ppDSBuffer, void* pUnkOuter)
    {
        printf("STUB: IDirectSound::CreateSoundBuffer desc(%x %x)", pcDSBufferDesc->dwFlags, pcDSBufferDesc->dwBufferBytes);
        if (pcDSBufferDesc->lpwfxFormat.translated())
        {
            WAVEFORMATEX* format = pcDSBufferDesc->lpwfxFormat.translated();
            printf(" format(tag %x, channels %u, samples/sec %u, avg bytes/sec 0x%x, block align %x, bits/sample %u, cbSize %x)",
                   format->wFormatTag, format->nChannels, format->nSamplesPerSec, format->nAvgBytesPerSec, format->nBlockAlign,
                   format->wBitsPerSample, format->cbSize);
            //TODO: SDL_AudioStream
        }
        printf("\n");
        
        *ppDSBuffer = CreateInterfaceInstance("IDirectSoundBuffer", 200);
        struct dsndbuffer_ext* new_obj = (struct dsndbuffer_ext*)vm_ptr_to_real_ptr(*ppDSBuffer);
        new_obj->volume = 0;

        return 0;
    }

    Q_INVOKABLE uint32_t GetCaps(void* this_ptr, uint32_t a)
    {
        printf("STUB: IDirectSound::GetCaps\n");
    }
    
    Q_INVOKABLE uint32_t DuplicateSoundBuffer(void* this_ptr, struct dsndbuffer_ext* orig, uint32_t* duplicate)
    {
        printf("STUB: IDirectSound::DuplicateSoundBuffer\n");
        
        *duplicate = CreateInterfaceInstance("IDirectSoundBuffer", 200);
        
        struct dsndbuffer_ext* dup = (struct dsndbuffer_ext*)vm_ptr_to_real_ptr(*duplicate);
        dup->buffer = 0;
        dup->size = orig->size;
        dup->channel = -1;
        dup->volume = orig->volume;
        
        if (orig->buffer.translated())
        {
            dup->buffer = kernel32->VirtualAlloc(0, dup->size, 0, 0);
            memcpy(dup->buffer.translated(), orig->buffer.translated(), dup->size);
        }
        
        return 0;
    }

    Q_INVOKABLE uint32_t SetCooperativeLevel(void* this_ptr, uint32_t a, uint32_t b)
    {
        printf("STUB: IDirectSound::SetCooperativeLevel\n");
    }

    Q_INVOKABLE uint32_t Compact(void* this_ptr)
    {
        printf("STUB: IDirectSound::Compact\n");
    }

    Q_INVOKABLE uint32_t GetSpeakerConfig(void* this_ptr, uint32_t a)
    {
        printf("STUB: IDirectSound::GetSpeakerConfig\n");
    }

    Q_INVOKABLE uint32_t SetSpeakerConfig(void* this_ptr, uint32_t b)
    {
        printf("STUB: IDirectSound::SetSpeakerConfig\n");
    }

    Q_INVOKABLE uint32_t Initialize(void* this_ptr, uint32_t a)
    {
        printf("STUB: IDirectSound::Initialize\n");
    }

//    Q_INVOKABLE uint32_t ();
};

extern IDirectSound* idirectsound;

#endif // IDIRECTSOUND_H
