#pragma once

#include "gbengine/gbengine_types.h"

// Forward declarations (defined later in this file)
class gbAudioManager;
class gbSound3DNode;
class gbSound2DNode;

/* ======== gbAudioMgrDesc ======== */

struct gbAudioMgrDesc {
    int freq;             // +0x00
    int bits;             // +0x04
    int channels;         // +0x08
    char providerName[256]; // +0x0C (provider string; [0]==0 = use default)
    // sizeof = 0x10C = 268

    gbAudioMgrDesc();
    gbAudioMgrDesc& operator=(const gbAudioMgrDesc& other);
};


/* ======== gbSoundData ======== */

// gbSoundData is a resource type that holds loaded audio file data
// Layout: vtable(4) + refCount(4) + name(4) + nameCrc(4) + unknown(4) + manager(4) + fileData(4) = 0x1C
class gbSoundData {
public:
    int refCount;            // +0x04 (vtable at +0x00 implied by virtual)
    char* name;              // +0x08
    unsigned int nameCrc;    // +0x0C
    void* unknown10;         // +0x10
    void* manager;           // +0x14
    void* fileData;          // +0x18 (loaded WAV/sound data pointer)

    gbSoundData();
    ~gbSoundData();

    int Load(char* filename);
    void SetName(const char* newName);
    void IncRef();
    void Release();
};


/* ======== 3D/2D sample slot structures ======== */

// Layout verified from IDA constructor (handles allocated at slot+4, nodes at slot+0)
struct gb3DSampleSlot {
    gbSound3DNode* node;     // +0x00
    void* handle;            // +0x04 (H3DSAMPLE)
    int flags;               // +0x08 (allocation counter stamp)
};

struct gb2DSampleSlot {
    gbSound2DNode* node;     // +0x00
    void* handle;            // +0x04 (HSAMPLE)
    int flags;               // +0x08
};

#define MAX_3D_SAMPLES 10
#define MAX_2D_SAMPLES 4
#define MAX_STREAMS    3


/* ======== gbSound3DNode ======== */

class gbSound3DNode {
public:
    gbSoundData* soundData;   // +0x00
    void* sampleHandle;       // +0x04 (H3DSAMPLE) - non-null means attached
    gbVec3D position;         // +0x08
    gbVec3D velocity;         // +0x14
    gbVec3D orientation;      // +0x20
    int field_2C;             // +0x2C
    float volume;             // +0x30
    int loopCount;            // +0x34
    float minDist;            // +0x38
    float maxDist;            // +0x3C

    static gbAudioManager* pAudioMgr;

    gbSound3DNode();
    ~gbSound3DNode();
    gbSound3DNode& operator=(const gbSound3DNode& other);

    int LoadFromFile(char* filename);
    void Play();
    void Stop();
    int IsPlaying();
    void SetPosition(gbVec3D& pos);
    void GetPosition(gbVec3D& pos);
    void SetOrientation(gbVec3D& ori);
    void SetVelocity(gbVec3D& vel);
    void SetVolume(float vol);
    void SetLoopNum(int num);
    void SetDistParam(float minD, float maxD);
    float GetMinDist();
    float GetMaxDist();
    int GetPlayLoop();
    bool IfAttached();
    int Update(double deltaTime);
};


/* ======== gbSound2DNode ======== */

class gbSound2DNode {
public:
    gbSoundData* soundData;   // +0x00
    void* sampleHandle;       // +0x04 (HSAMPLE)
    int loopCount;            // +0x08
    float volume;             // +0x0C

    static gbAudioManager* pAudioMgr;

    gbSound2DNode();
    ~gbSound2DNode();
    gbSound2DNode& operator=(const gbSound2DNode& other);

    int LoadFromFile(char* filename);
    void Play();
    void Stop();
    bool IsPlaying();
    void Pause();
    void Resume();
    void SetLoopNum(int num);
    void SetVolume(float vol);
};


/* ======== gbResManagerStub ======== */

// Minimal resource manager stub (matches layout of gbResManager: 3 fields = 12 bytes)
struct gbResManagerStub {
    void** array;    // +0x00
    int capacity;    // +0x04
    int count;       // +0x08

    void Init();
    void Destroy();
};


/* ======== gbAudioManager ======== */

// Layout verified from IDA constructor at 0x10001120
// sizeof = 0xF4 (streams + slots + volumes + listener + listenerPos + resManager)
class gbAudioManager {
public:
    void* streams[MAX_STREAMS];            // +0x00 (HSTREAM, DWORD[0..2])
    int streamStatus[MAX_STREAMS];         // +0x0C (DWORD[3..5])
    void* digitalDriver;                   // +0x18 (HDIGDRIVER, DWORD[6])
    void* provider3D;                      // +0x1C (H3DPROVIDER, DWORD[7])
    gb3DSampleSlot slots3D[MAX_3D_SAMPLES];// +0x20 (10*12=120B, DWORD[8..37], ends at +0x98)
    gb2DSampleSlot slots2D[MAX_2D_SAMPLES];// +0x98 (4*12=48B, DWORD[38..49], ends at +0xC8)
    int allocCounter;                      // +0xC8 (DWORD[50], 3D sample allocation stamp)
    float volume3D;                        // +0xCC (DWORD[51])
    float volume2D;                        // +0xD0 (DWORD[52])
    float musicMasterVolume;               // +0xD4 (DWORD[53])
    void* listener;                        // +0xD8 (H3DLISTENER, DWORD[54])
    gbVec3D listenerPosition;              // +0xDC (DWORD[55..57])
    gbResManagerStub soundResManager;      // +0xE8 (12 bytes, DWORD[58..60])

    // Constructor - 0x10001120 (675B)
    gbAudioManager(int& result, gbAudioMgrDesc* desc);
    // Copy constructor - 0x10002240 (276B)
    gbAudioManager(const gbAudioManager& other);
    // Destructor
    ~gbAudioManager();
    // operator=
    gbAudioManager& operator=(const gbAudioManager& other);

    // 0x10001560 (125B)
    gbSoundData* LoadSoundFile(char* filename);
    // 0x100015f0 (12B)
    void DeleteSoundData(gbSoundData* data);
    // 0x10001620 (392B)
    void AttachSampleHandle(gbSound3DNode* node);
    // 0x100018d0 (58B)
    void DetachSampleHandle(gbSound3DNode* node);
    // 0x10001970 (54B)
    void DetachAll3D();
    // 0x10001a10 (240B)
    void AttachSampleHandle(gbSound2DNode* node);
    // 0x10001b00 (61B)
    void DetachSampleHandle(gbSound2DNode* node);
    // 0x10001da0 (115B)
    int CanBeHeard(gbSound3DNode* node);

    // Stream functions
    // 0x10001bc0 (136B)
    void PlaySoundStream(int index, char* filename, int loop);
    // 0x10001b70 (78B)
    void ReStartSoundStream(int index);
    // 0x10001c50 (42B)
    void StopSoundStream(int index);
    // 0x10001cd0 (23B)
    void PauseSoundStream(int index);
    // 0x10001cf0 (23B)
    void ResumeSoundStream(int index);
    // 0x10001d10 (11B)
    int GetStreamStatus(int index);

    // Listener
    // 0x10001d20 (62B)
    void SetListenerPosition(const gbVec3D& pos);
    // 0x10001d60 (56B)
    void SetListenerOrientation(gbVec3D& front, gbVec3D& top);
    // 0x10002210 (33B)
    void GetListenerPosition(gbVec3D& pos);

    // Volume
    // 0x100021c0 (13B)
    void Set2DMasterVolume(float vol);
    float Get2DMasterVolume();
    // 0x100021e0 (13B)
    void Set3DMasterVolume(float vol);
    float Get3DMasterVolume();
    // 0x10001c80 (67B)
    void SetMusicMasterVolume(float vol);
    float GetMusicMasterVolume();

private:
    // 0x10001020 (250B)
    unsigned long Get3DProvider(char* providerName);
};
