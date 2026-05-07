/**
 * gbengine.dll - gbAudioManager, gbAudioMgrDesc, gbSound3DNode, gbSound2DNode, gbSoundData
 * Audio system implementation using Miles Sound System (AIL)
 * Functions: 46 exports
 */

#include "gbengine/gbAudio.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Miles Sound System types
typedef void* HSAMPLE;
typedef void* H3DSAMPLE;
typedef void* HSTREAM;
typedef void* HDIGDRIVER;
typedef void* H3DPROVIDER;
typedef void* H3DLISTENER;
typedef void* HPROVIDER;

// Miles Sound System constants
#define SMP_PLAYING  4
#define SMP_STOPPED  2
#define SMP_DONE     1

// Miles Sound System external declarations (mss32.dll, __stdcall + dllimport)
#define AILCALL __declspec(dllimport) __stdcall

extern "C" {
void AILCALL AIL_set_redist_directory(const char* dir);
int AILCALL AIL_startup(void);
void AILCALL AIL_shutdown(void);

HDIGDRIVER AILCALL AIL_open_digital_driver(unsigned int freq, int bits, int channels, unsigned int flags);
void AILCALL AIL_close_digital_driver(HDIGDRIVER driver);

int AILCALL AIL_enumerate_3D_providers(HPROVIDER* dest, void** query, unsigned int* count);
H3DPROVIDER AILCALL AIL_open_3D_provider(HPROVIDER provider);
void AILCALL AIL_close_3D_provider(H3DPROVIDER provider);

H3DLISTENER AILCALL AIL_open_3D_listener(H3DPROVIDER provider);
void AILCALL AIL_close_3D_listener(H3DLISTENER listener);
void AILCALL AIL_set_3D_position(void* obj, float x, float y, float z);
void AILCALL AIL_set_3D_orientation(void* obj, float fx, float fy, float fz, float ux, float uy, float uz);
void AILCALL AIL_3D_position(void* obj, float* x, float* y, float* z);

H3DSAMPLE AILCALL AIL_allocate_3D_sample_handle(H3DPROVIDER provider);
void AILCALL AIL_release_3D_sample_handle(H3DSAMPLE sample);
void AILCALL AIL_set_3D_sample_file(H3DSAMPLE sample, void* data);
void AILCALL AIL_start_3D_sample(H3DSAMPLE sample);
void AILCALL AIL_stop_3D_sample(H3DSAMPLE sample);
void AILCALL AIL_end_3D_sample(H3DSAMPLE sample);
void AILCALL AIL_resume_3D_sample(H3DSAMPLE sample);
unsigned int AILCALL AIL_3D_sample_status(H3DSAMPLE sample);
void AILCALL AIL_set_3D_sample_volume(H3DSAMPLE sample, int volume);
void AILCALL AIL_set_3D_sample_loop_count(H3DSAMPLE sample, int count);
void AILCALL AIL_set_3D_sample_distances(H3DSAMPLE sample, float maxDist, float minDist);
void AILCALL AIL_set_3D_velocity(void* obj, float dx, float dy, float dz);
void AILCALL AIL_auto_update_3D_position(H3DSAMPLE sample, int flag);
void AILCALL AIL_WAV_info(void* data, void* info);

HSAMPLE AILCALL AIL_allocate_sample_handle(HDIGDRIVER driver);
void AILCALL AIL_release_sample_handle(HSAMPLE sample);
void AILCALL AIL_set_sample_file(HSAMPLE sample, void* data, int block);
void AILCALL AIL_start_sample(HSAMPLE sample);
void AILCALL AIL_stop_sample(HSAMPLE sample);
void AILCALL AIL_end_sample(HSAMPLE sample);
void AILCALL AIL_resume_sample(HSAMPLE sample);
void AILCALL AIL_pause_sample(HSAMPLE sample);
unsigned int AILCALL AIL_sample_status(HSAMPLE sample);
void AILCALL AIL_set_sample_volume(HSAMPLE sample, int volume);
void AILCALL AIL_set_sample_loop_count(HSAMPLE sample, int count);

HSTREAM AILCALL AIL_open_stream(HDIGDRIVER driver, const char* filename, int block);
void AILCALL AIL_close_stream(HSTREAM stream);
void AILCALL AIL_start_stream(HSTREAM stream);
void AILCALL AIL_pause_stream(HSTREAM stream, int onoff);
void AILCALL AIL_set_stream_volume(HSTREAM stream, int volume);
unsigned int AILCALL AIL_stream_status(HSTREAM stream);

__declspec(dllimport) void* __stdcall AIL_file_read(const char* filename, void* dest);
void AILCALL AIL_mem_free_lock(void* ptr);
}

// External functions (from gbResManager.cpp)
extern unsigned int gbCrc32Compute(const char* str);
extern void gbReportError(const char* fmt, ...);

// gbResManagerStub method implementations
void gbResManagerStub::Init() {
    array = NULL; capacity = 0; count = 0;
}
void gbResManagerStub::Destroy() { if (array != NULL) { free(array); array = NULL; } }


/* ======== gbSoundData implementation ======== */

gbSoundData::gbSoundData() {
    refCount = 1;
    name = NULL;
    nameCrc = 0;
    unknown10 = NULL;
    manager = NULL;
    fileData = NULL;
}

gbSoundData::~gbSoundData() {
    if (fileData != NULL) {
        AIL_mem_free_lock(fileData);
        fileData = NULL;
    }
    if (name != NULL) {
        free(name);
        name = NULL;
    }
}

void gbSoundData::SetName(const char* newName) {
    if (name != NULL) {
        free(name);
    }
    if (newName == NULL || newName[0] == '\0') {
        name = NULL;
        nameCrc = 0;
        return;
    }
    size_t len = strlen(newName) + 1;
    size_t allocSize = (len < 16) ? 16 : len;
    name = (char*)malloc(allocSize);
    strcpy(name, newName);
    nameCrc = gbCrc32Compute(newName);
}

void gbSoundData::IncRef() {
    refCount++;
}

void gbSoundData::Release() {
    refCount--;
    if (refCount == 0) {
        delete this;
    }
}

// Helper: find sound resource by name in the embedded resource manager
static gbSoundData* FindSoundByName(gbResManagerStub* mgr, const char* name) {
    if (name == NULL || mgr->count == 0) {
        return NULL;
    }
    unsigned int crc = gbCrc32Compute(name);
    for (int i = 0; i < mgr->count; i++) {
        gbSoundData* snd = (gbSoundData*)(mgr->array[i]);
        if (snd->nameCrc == crc) {
            snd->IncRef();
            return snd;
        }
    }
    return NULL;
}

// Helper: add sound resource to embedded resource manager
static void AddSoundResource(gbResManagerStub* mgr, gbSoundData* snd) {
    snd->manager = mgr;
    if (mgr->count == mgr->capacity) {
        int newCap = mgr->capacity * 2;
        if (newCap == 0) newCap = 16;
        void** newArr = (void**)malloc(newCap * sizeof(void*));
        if (mgr->count != 0) {
            memcpy(newArr, mgr->array, mgr->count * sizeof(void*));
        }
        if (mgr->array != NULL) {
            free(mgr->array);
        }
        mgr->array = newArr;
        mgr->capacity = newCap;
    }
    mgr->array[mgr->count] = snd;
    mgr->count++;
}


/* ======== gbAudioMgrDesc implementation ======== */

// Constructor - 0x10001000 (27B)
gbAudioMgrDesc::gbAudioMgrDesc() {
    freq = 0x5622;       // 22050 Hz
    bits = 0x10;         // 16-bit
    channels = 2;        // stereo
    providerName[0] = 0; // use default provider
}

// operator= - 0x100021a0 (22B)
gbAudioMgrDesc& gbAudioMgrDesc::operator=(const gbAudioMgrDesc& other) {
    memcpy(this, &other, 0x10C);
    return *this;
}




gbAudioManager* gbSound3DNode::pAudioMgr = NULL;


gbAudioManager* gbSound2DNode::pAudioMgr = NULL;


/* ======== Global pointer (DAT_1012b980) ======== */

static gbAudioManager* g_pAudioManager = NULL;


/* ================================================================
 * gbAudioManager implementation
 * ================================================================ */

// Constructor - 0x10001120
gbAudioManager::gbAudioManager(int& result, gbAudioMgrDesc* desc) {
    int i;

    // Zero streams and status
    for (i = 0; i < MAX_STREAMS; i++) {
        streams[i] = NULL;
        streamStatus[i] = 0;
    }

    digitalDriver = NULL;
    provider3D = NULL;
    num3DSamples = 0;
    volume3D = 1.0f;
    volume2D = 1.0f;
    musicMasterVolume = 1.0f;
    listener = NULL;
    field_DC = 0;
    field_E0 = 0;
    field_E4 = 0;

    // Initialize embedded resource manager
    soundResManager.Init();

    // Zero sample slots
    for (i = 0; i < MAX_3D_SAMPLES; i++) {
        slots3D[i].handle = NULL;
        slots3D[i].node = NULL;
        slots3D[i].flags = 0;
    }
    for (i = 0; i < MAX_2D_SAMPLES; i++) {
        slots2D[i].handle = NULL;
        slots2D[i].node = NULL;
        slots2D[i].flags = 0;
    }

    // Initialize Miles Sound System
    AIL_set_redist_directory("miles\\win32\\");
    result = AIL_startup();
    if (result == 0) {
        return;
    }

    // Open digital driver with descriptor parameters
    digitalDriver = AIL_open_digital_driver((unsigned int)desc->freq, desc->bits, desc->channels, 0);
    if (digitalDriver == NULL) {
        result = 0;
        return;
    }

    // Get 3D audio provider
    char* provName = NULL;
    if (desc->providerName[0] != 0) {
        provName = desc->providerName;
    }
    if (Get3DProvider(provName) == 0) {
        result = 0;
        return;
    }

    // Allocate 3D sample handles
    for (i = 0; i < MAX_3D_SAMPLES; i++) {
        slots3D[i].handle = AIL_allocate_3D_sample_handle(provider3D);
        slots3D[i].node = NULL;
        slots3D[i].flags = 0;
    }
    num3DSamples = MAX_3D_SAMPLES;

    // Allocate 2D sample handles
    for (i = 0; i < MAX_2D_SAMPLES; i++) {
        slots2D[i].handle = AIL_allocate_sample_handle(digitalDriver);
        slots2D[i].node = NULL;
        slots2D[i].flags = 0;
    }

    // Create 3D listener
    listener = AIL_open_3D_listener(provider3D);

    // Set static audio manager pointers
    gbSound3DNode::pAudioMgr = this;
    gbSound2DNode::pAudioMgr = this;
    g_pAudioManager = this;

    result = 1;
}

// Copy constructor - 0x10002240
gbAudioManager::gbAudioManager(const gbAudioManager& other) {
    int i;

    for (i = 0; i < MAX_STREAMS; i++) {
        streams[i] = other.streams[i];
        streamStatus[i] = other.streamStatus[i];
    }

    digitalDriver = other.digitalDriver;
    provider3D = other.provider3D;
    num3DSamples = other.num3DSamples;
    listener = other.listener;
    volume2D = other.volume2D;
    volume3D = other.volume3D;
    musicMasterVolume = other.musicMasterVolume;
    field_DC = other.field_DC;
    field_E0 = other.field_E0;
    field_E4 = other.field_E4;

    soundResManager.array = other.soundResManager.array;
    soundResManager.capacity = other.soundResManager.capacity;
    soundResManager.count = other.soundResManager.count;

    for (i = 0; i < MAX_3D_SAMPLES; i++) {
        slots3D[i] = other.slots3D[i];
    }
    for (i = 0; i < MAX_2D_SAMPLES; i++) {
        slots2D[i] = other.slots2D[i];
    }
}

// Destructor
gbAudioManager::~gbAudioManager() {
    int i;

    // Clear global pointers
    g_pAudioManager = NULL;
    gbSound3DNode::pAudioMgr = NULL;
    gbSound2DNode::pAudioMgr = NULL;

    // Stop and release 3D samples
    for (i = 0; i < num3DSamples; i++) {
        if (slots3D[i].handle != NULL) {
            AIL_stop_3D_sample(slots3D[i].handle);
            AIL_release_3D_sample_handle(slots3D[i].handle);
            slots3D[i].handle = NULL;
            slots3D[i].node = NULL;
            slots3D[i].flags = 0;
        }
    }

    // Stop and release 2D samples
    for (i = 0; i < MAX_2D_SAMPLES; i++) {
        if (slots2D[i].handle != NULL) {
            AIL_stop_sample(slots2D[i].handle);
            AIL_release_sample_handle(slots2D[i].handle);
            slots2D[i].handle = NULL;
            slots2D[i].node = NULL;
            slots2D[i].flags = 0;
        }
    }

    // Close streams
    for (i = 0; i < MAX_STREAMS; i++) {
        if (streams[i] != NULL) {
            AIL_close_stream(streams[i]);
            streams[i] = NULL;
        }
    }

    // Close listener
    if (listener != NULL) {
        AIL_close_3D_listener(listener);
        listener = NULL;
    }

    // Close 3D provider
    if (provider3D != NULL) {
        AIL_close_3D_provider(provider3D);
        provider3D = NULL;
    }

    // Close digital driver
    if (digitalDriver != NULL) {
        AIL_close_digital_driver(digitalDriver);
        digitalDriver = NULL;
    }

    // Shutdown Miles
    AIL_shutdown();

    // Destroy resource manager
    soundResManager.Destroy();
}

// operator=
gbAudioManager& gbAudioManager::operator=(const gbAudioManager& other) {
    int i;
    if (this != &other) {
        for (i = 0; i < MAX_STREAMS; i++) {
            streams[i] = other.streams[i];
            streamStatus[i] = other.streamStatus[i];
        }
        digitalDriver = other.digitalDriver;
        provider3D = other.provider3D;
        num3DSamples = other.num3DSamples;
        listener = other.listener;
        volume2D = other.volume2D;
        volume3D = other.volume3D;
        musicMasterVolume = other.musicMasterVolume;
        field_DC = other.field_DC;
        field_E0 = other.field_E0;
        field_E4 = other.field_E4;
        soundResManager.array = other.soundResManager.array;
        soundResManager.capacity = other.soundResManager.capacity;
        soundResManager.count = other.soundResManager.count;
        for (i = 0; i < MAX_3D_SAMPLES; i++) {
            slots3D[i] = other.slots3D[i];
        }
        for (i = 0; i < MAX_2D_SAMPLES; i++) {
            slots2D[i] = other.slots2D[i];
        }
    }
    return *this;
}

// Get3DProvider - 0x10001020 (250B)
unsigned long gbAudioManager::Get3DProvider(char* providerName) {
    HPROVIDER dest;
    void* query = NULL;
    unsigned int count = 0;

    // Default provider name if none specified
    const char* defaultName = "Miles Fast 2D Positional Audio";
    const char* searchName = (providerName != NULL) ? providerName : defaultName;

    // Enumerate available 3D providers
    int enumResult = AIL_enumerate_3D_providers(&dest, &query, &count);
    if (enumResult == 0) {
        return 0;
    }

    // The query result is an array of {HPROVIDER, char*} pairs
    // Search for the requested provider by name
    struct ProvEntry { HPROVIDER prov; char* name; };
    ProvEntry* entries = (ProvEntry*)query;

    HPROVIDER foundProvider = NULL;
    for (unsigned int i = 0; i < count; i++) {
        if (entries[i].name != NULL && strcmp(entries[i].name, searchName) == 0) {
            foundProvider = entries[i].prov;
            break;
        }
    }

    if (foundProvider == NULL) {
        return 0;
    }

    // Open the 3D provider
    provider3D = AIL_open_3D_provider(foundProvider);
    if (provider3D == NULL) {
        return 0;
    }

    return 1;
}

// LoadSoundFile - 0x10001560 (125B)
gbSoundData* gbAudioManager::LoadSoundFile(char* filename) {
    if (filename == NULL) {
        return NULL;
    }

    // Check if already loaded
    gbSoundData* existing = FindSoundByName(&soundResManager, filename);
    if (existing != NULL) {
        return existing;
    }

    // Load file data via Miles
    void* fileData = AIL_file_read(filename, NULL);
    if (fileData == NULL) {
        return NULL;
    }

    // Create new sound data object
    gbSoundData* sndData = new gbSoundData();
    sndData->SetName(filename);
    sndData->fileData = fileData;

    // Register with resource manager
    AddSoundResource(&soundResManager, sndData);

    return sndData;
}

// DeleteSoundData - 0x100015f0 (12B)
void gbAudioManager::DeleteSoundData(gbSoundData* data) {
    ((gbSoundData*)data)->Release();
}

// AttachSampleHandle (3D) - 0x10001620 (392B)
void gbAudioManager::AttachSampleHandle(gbSound3DNode* node) {
    unsigned int freeSlot = 0xFFFF;
    int v4 = *(((int*)this) + 50);
    int* v5 = (int*)((char*)this + 32);
    *(((int*)this) + 50) = v4 + 1;

    for (int i = 0; i < 10; i++) {
        if (!*v5) {
            freeSlot = i;
            goto LABEL_15;
        }
        v5 += 3;
    }

    {
        int v7 = 0;
        int* v8 = (int*)((char*)this + 36);
        do {
            if (AIL_3D_sample_status((void*)*v8) == SMP_STOPPED) {
                AIL_end_3D_sample(slots3D[v7].handle);
                freeSlot = v7;
                *(int*)(*(((int*)this) + 3 * v7 + 8) + 4) = 0;
                goto LABEL_15;
            }
            v7++;
            v8 += 3;
        } while (v7 < 10);
    }

    {
        float dx = node->position.x - *((float*)this + 55);
        float dy = node->position.y - *((float*)this + 56);
        float dz = node->position.z - *((float*)this + 57);
        float distSq = dz * dz + dy * dy + dx * dx;
        int* v15 = (int*)((char*)this + 32);
        for (int v11 = 0; v11 < 10; v11++) {
            float sx = *(float*)(*v15 + 8) - *((float*)this + 55);
            float sy = *(float*)(*v15 + 12) - *((float*)this + 56);
            float sz = *(float*)(*v15 + 16) - *((float*)this + 57);
            float d2 = sz * sz + sy * sy + sx * sx;
            if (d2 > distSq) {
                distSq = d2;
                freeSlot = v11;
            }
            v15 += 3;
        }
        if (freeSlot > 9)
            return;
        AIL_end_3D_sample(slots3D[freeSlot].handle);
        *(int*)(*(((int*)this) + 3 * freeSlot + 8) + 4) = 0;
    }

LABEL_15:
    {
        char* v20 = (char*)this + 12 * freeSlot;
        *(((int*)v20) + 10) = *(((int*)this) + 50);
        *(((int*)v20) + 8) = (int)node;
        void* h = slots3D[freeSlot].handle;
        node->sampleHandle = h;
        AIL_set_3D_sample_file(h, node->soundData->fileData);
    }
}

// DetachSampleHandle (3D) - 0x100018d0 (58B)
void gbAudioManager::DetachSampleHandle(gbSound3DNode* node) {
    gbSound3DNode** v2 = (gbSound3DNode**)((char*)this + 32);
    int v3 = 10;
    do {
        if (*v2 == node) {
            AIL_end_3D_sample(node->sampleHandle);
            node->sampleHandle = NULL;
            *v2 = NULL;
        }
        v2 += 3;
        --v3;
    } while (v3);
}

// DetachAll3D - 0x10001970 (54B)
void gbAudioManager::DetachAll3D() {
    for (int i = 0; i < num3DSamples; i++) {
        if (slots3D[i].node != NULL) {
            AIL_end_3D_sample(slots3D[i].handle);
            slots3D[i].node->sampleHandle = NULL;
            slots3D[i].node = NULL;
        }
    }
}

// AttachSampleHandle (2D) - 0x10001a10 (240B)
void gbAudioManager::AttachSampleHandle(gbSound2DNode* node) {
    if (node == NULL || node->soundData == NULL) {
        return;
    }

    // Find a free 2D sample slot
    int freeSlot = -1;
    for (int i = 0; i < MAX_2D_SAMPLES; i++) {
        if (slots2D[i].flags == 0) {
            freeSlot = i;
            break;
        }
    }

    if (freeSlot == -1) {
        // Try to steal a finished slot
        for (int i = 0; i < MAX_2D_SAMPLES; i++) {
            if (slots2D[i].handle != NULL) {
                unsigned int status = AIL_sample_status(slots2D[i].handle);
                if (status == SMP_DONE || status == SMP_STOPPED) {
                    if (slots2D[i].node != NULL) {
                        slots2D[i].node->sampleHandle = NULL;
                    }
                    freeSlot = i;
                    break;
                }
            }
        }
    }

    if (freeSlot == -1) {
        return;
    }

    // Configure the sample
    HSAMPLE sample = slots2D[freeSlot].handle;
    AIL_set_sample_file(sample, node->soundData->fileData, 0);
    int vol = (int)(node->volume * volume2D * 127.0f);
    if (vol > 127) vol = 127;
    if (vol < 0) vol = 0;
    AIL_set_sample_volume(sample, vol);
    AIL_set_sample_loop_count(sample, node->loopCount);

    // Link node to slot
    node->sampleHandle = sample;
    slots2D[freeSlot].node = node;
    slots2D[freeSlot].flags = 1;
}

// DetachSampleHandle (2D) - 0x10001b00 (61B)
void gbAudioManager::DetachSampleHandle(gbSound2DNode* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < MAX_2D_SAMPLES; i++) {
        if (slots2D[i].node == node) {
            AIL_stop_sample(slots2D[i].handle);
            slots2D[i].node = NULL;
            slots2D[i].flags = 0;
            node->sampleHandle = NULL;
            break;
        }
    }
}

// CanBeHeard - 0x10001da0 (115B)
int gbAudioManager::CanBeHeard(gbSound3DNode* node) {
    if (node == NULL || listener == NULL) {
        return 0;
    }

    // Get listener position
    float lx, ly, lz;
    AIL_3D_position(listener, &lx, &ly, &lz);

    // Calculate squared distance from listener to node
    float dx = node->position.x - lx;
    float dy = node->position.y - ly;
    float dz = node->position.z - lz;
    float distSq = dx * dx + dy * dy + dz * dz;

    // Compare with max hearing distance
    float maxDist = node->maxDist;
    if (distSq > maxDist * maxDist) {
        return 0;
    }

    return 1;
}

// PlaySoundStream - 0x10001bc0 (136B)
void gbAudioManager::PlaySoundStream(int index, char* filename, int loop) {
    if (index < 0 || index >= MAX_STREAMS) {
        return;
    }

    // Close existing stream if any
    if (streams[index] != NULL) {
        AIL_close_stream(streams[index]);
        streams[index] = NULL;
    }

    // Open new stream file
    HSTREAM stream = AIL_open_stream(digitalDriver, filename, 0);
    if (stream == NULL) {
        streamStatus[index] = 0;
        return;
    }

    streams[index] = stream;

    // Set music volume
    int vol = (int)(musicMasterVolume * 127.0f);
    if (vol > 127) vol = 127;
    if (vol < 0) vol = 0;
    AIL_set_stream_volume(stream, vol);

    // Start playback
    AIL_start_stream(stream);
    streamStatus[index] = 1;
}

// ReStartSoundStream - 0x10001b70 (78B)
void gbAudioManager::ReStartSoundStream(int index) {
    if (index < 0 || index >= MAX_STREAMS) {
        return;
    }

    if (streams[index] != NULL) {
        AIL_start_stream(streams[index]);
        streamStatus[index] = 1;
    }
}

// StopSoundStream - 0x10001c50 (42B)
void gbAudioManager::StopSoundStream(int index) {
    if (*(((int*)this) + index)) {
        AIL_close_stream((void*)*(((int*)this) + index));
        *(((int*)this) + index) = 0;
        *(((int*)this) + index + 3) = 2;
    }
}

// PauseSoundStream - 0x10001cd0 (23B)
void gbAudioManager::PauseSoundStream(int index) {
    void* v2 = *(((void**)this) + index);
    if (v2)
        AIL_pause_stream(v2, 1);
}

// ResumeSoundStream - 0x10001cf0 (23B)
void gbAudioManager::ResumeSoundStream(int index) {
    void* v2 = *(((void**)this) + index);
    if (v2)
        AIL_pause_stream(v2, 0);
}

// GetStreamStatus - 0x10001d10 (11B)
int gbAudioManager::GetStreamStatus(int index) {
    return streamStatus[index];
}

// SetMusicMasterVolume - 0x10001c80 (67B)
void gbAudioManager::SetMusicMasterVolume(float vol) {
    musicMasterVolume = vol;

    // Update volume on all active streams
    int intVol = (int)(vol * 127.0f);
    if (intVol > 127) intVol = 127;
    if (intVol < 0) intVol = 0;

    for (int i = 0; i < MAX_STREAMS; i++) {
        if (streams[i] != NULL) {
            AIL_set_stream_volume(streams[i], intVol);
        }
    }
}

// GetMusicMasterVolume
float gbAudioManager::GetMusicMasterVolume() {
    return musicMasterVolume;
}

// SetListenerPosition - 0x10001d20 (62B)
void gbAudioManager::SetListenerPosition(const gbVec3D& pos) {
    *(((int*)this) + 55) = *(((int*)&pos) + 0);
    *(((int*)this) + 56) = *(((int*)&pos) + 1);
    *(((int*)this) + 57) = *(((int*)&pos) + 2);
    float negZ = -pos.z;
    AIL_set_3D_position(*(((void**)this) + 54), pos.x, pos.y, negZ);
}

// SetListenerOrientation - 0x10001d60 (56B)
void gbAudioManager::SetListenerOrientation(gbVec3D& front, gbVec3D& top) {
    float negTopZ = -top.z;
    float negFrontZ = -front.z;
    AIL_set_3D_orientation(*(((void**)this) + 54), front.x, front.y, negFrontZ, top.x, top.y, negTopZ);
}

// GetListenerPosition - 0x10002210 (33B)
void gbAudioManager::GetListenerPosition(gbVec3D& pos) {
    *(((int*)&pos) + 0) = *(((int*)this) + 55);
    *(((int*)&pos) + 1) = *(((int*)this) + 56);
    *(((int*)&pos) + 2) = *(((int*)this) + 57);
}

// Set2DMasterVolume - 0x100021c0 (13B)
void gbAudioManager::Set2DMasterVolume(float vol) {
    volume2D = vol;
}

// Get2DMasterVolume
float gbAudioManager::Get2DMasterVolume() {
    return volume2D;
}

// Set3DMasterVolume - 0x100021e0 (13B)
void gbAudioManager::Set3DMasterVolume(float vol) {
    volume3D = vol;
}

// Get3DMasterVolume
float gbAudioManager::Get3DMasterVolume() {
    return volume3D;
}


/* ================================================================
 * gbSound3DNode implementation
 * ================================================================ */

// Constructor - 0x10002640 (99B)
gbSound3DNode::gbSound3DNode() {
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.z = 0.0f;
    orientation.x = 0.0f;
    orientation.y = 0.0f;
    orientation.z = 0.0f;
    soundData = NULL;
    sampleHandle = NULL;
    minDist = 10000.0f;
    maxDist = 100000.0f;
    loopCount = 1;
    volume = 1.0f;
    field_2C = 0;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.z = 0.0f;
    orientation.x = 0.0f;
    orientation.y = 0.0f;
    orientation.z = 0.0f;
    orientation.z = 1.0f;
}

// Destructor - 0x100026b0 (78B)
gbSound3DNode::~gbSound3DNode() {
    if (sampleHandle)
        pAudioMgr->DetachSampleHandle(this);
    if (soundData) {
        if (pAudioMgr) {
            if (sampleHandle)
                AIL_stop_3D_sample(sampleHandle);
        }
        pAudioMgr->DeleteSoundData(soundData);
    }
}

// operator= - 0x100025b0 (138B)
gbSound3DNode& gbSound3DNode::operator=(const gbSound3DNode& other) {
    *(((int*)this) + 0) = *(((int*)&other) + 0);
    *(((int*)this) + 1) = *(((int*)&other) + 1);
    *(((int*)this) + 2) = *(((int*)&other) + 2);
    *(((int*)this) + 3) = *(((int*)&other) + 3);
    *(((int*)this) + 4) = *(((int*)&other) + 4);
    *(((int*)this) + 5) = *(((int*)&other) + 5);
    *(((int*)this) + 6) = *(((int*)&other) + 6);
    *(((int*)this) + 7) = *(((int*)&other) + 7);
    *(((int*)this) + 8) = *(((int*)&other) + 8);
    *(((int*)this) + 9) = *(((int*)&other) + 9);
    *(((int*)this) + 10) = *(((int*)&other) + 10);
    *(((int*)this) + 11) = *(((int*)&other) + 11);
    *(((int*)this) + 12) = *(((int*)&other) + 12);
    *(((int*)this) + 13) = *(((int*)&other) + 13);
    *(((int*)this) + 14) = *(((int*)&other) + 14);
    *(((int*)this) + 15) = *(((int*)&other) + 15);
    return *this;
}

// LoadFromFile - 0x10002700 (85B)
int gbSound3DNode::LoadFromFile(char* filename) {
    if (pAudioMgr) {
        gbSoundData* snd = pAudioMgr->LoadSoundFile(filename);
        soundData = snd;
        if (snd)
            return 1;
    }
    return 0;
}

// Play - 0x10002760 (174B)
void gbSound3DNode::Play() {
    if (pAudioMgr && pAudioMgr->CanBeHeard(this)) {
        if (!sampleHandle)
            pAudioMgr->AttachSampleHandle(this);
        void* h = sampleHandle;
        AIL_set_3D_sample_volume(h, (int)(pAudioMgr->volume3D * volume * 127.0f));
        float negZ = -position.z;
        AIL_set_3D_position(h, position.x, position.y, negZ);
        AIL_set_3D_sample_distances(h, maxDist, minDist);
        AIL_set_3D_sample_loop_count(h, loopCount);
        AIL_set_3D_velocity(h, 0.0f, 0.0f, 0.0f);
        AIL_start_3D_sample(h);
    }
}

// Stop - 0x10002810 (24B)
void gbSound3DNode::Stop() {
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_stop_3D_sample(sampleHandle);
    }
}

// IsPlaying - 0x10002830 (38B)
int gbSound3DNode::IsPlaying() {
    if (!pAudioMgr)
        return 0;
    if (!sampleHandle)
        return 0;
    return AIL_3D_sample_status(sampleHandle) == SMP_PLAYING;
}

// SetPosition - 0x10002500 (24B)
void gbSound3DNode::SetPosition(gbVec3D& pos) {
    *(((int*)this) + 2) = *(((int*)&pos) + 0);
    *(((int*)this) + 3) = *(((int*)&pos) + 1);
    *(((int*)this) + 4) = *(((int*)&pos) + 2);
}

// SetVelocity - 0x10002520 (24B)
void gbSound3DNode::SetVelocity(gbVec3D& vel) {
    *(((int*)this) + 5) = *(((int*)&vel) + 0);
    *(((int*)this) + 6) = *(((int*)&vel) + 1);
    *(((int*)this) + 7) = *(((int*)&vel) + 2);
}

// SetOrientation - 0x10002540 (24B)
void gbSound3DNode::SetOrientation(gbVec3D& ori) {
    *(((int*)this) + 8) = *(((int*)&ori) + 0);
    *(((int*)this) + 9) = *(((int*)&ori) + 1);
    *(((int*)this) + 10) = *(((int*)&ori) + 2);
}

// GetPosition - 0x10002560 (24B)
void gbSound3DNode::GetPosition(gbVec3D& pos) {
    *(((int*)&pos) + 0) = *(((int*)this) + 2);
    *(((int*)&pos) + 1) = *(((int*)this) + 3);
    *(((int*)&pos) + 2) = *(((int*)this) + 4);
}

// SetVolume - 0x100024e0 (10B)
void gbSound3DNode::SetVolume(float vol) {
    volume = vol;
}

// SetLoopNum - 0x100024f0 (10B)
void gbSound3DNode::SetLoopNum(int num) {
    loopCount = num;
}

// SetDistParam - 0x10004420 (13B)
void gbSound3DNode::SetDistParam(float minD, float maxD) {
    minDist = minD;
    maxDist = maxD;
}

// GetMinDist
float gbSound3DNode::GetMinDist() {
    return minDist;
}

// GetMaxDist - 0x10002590 (7B)
float gbSound3DNode::GetMaxDist() {
    return maxDist;
}

// GetPlayLoop
int gbSound3DNode::GetPlayLoop() {
    return loopCount;
}

// IfAttached - 0x100024d0 (11B)
bool gbSound3DNode::IfAttached() {
    return sampleHandle != 0;
}

// Update - 0x10002860 (110B)
int gbSound3DNode::Update(double deltaTime) {
    if (pAudioMgr) {
        float a2 = (float)deltaTime;
        position.x = velocity.x * a2 + position.x;
        position.y = velocity.y * a2 + position.y;
        float newZ = velocity.z * a2 + position.z;
        position.z = newZ;
        void* h = sampleHandle;
        if (!h)
            return 0;
        float negZ = -newZ;
        AIL_set_3D_position(h, position.x, position.y, negZ);
    }
    return 1;
}


/* ================================================================
 * gbSound2DNode implementation
 * ================================================================ */

// Constructor - 0x100028d0 (30B)
gbSound2DNode::gbSound2DNode() {
    soundData = NULL;
    sampleHandle = NULL;
    loopCount = 1;
    volume = 1.0f;
}

// Destructor
gbSound2DNode::~gbSound2DNode() {
    if (sampleHandle != NULL && pAudioMgr != NULL) {
        pAudioMgr->DetachSampleHandle(this);
    }
    if (soundData != NULL) {
        soundData->Release();
        soundData = NULL;
    }
}

// operator=
gbSound2DNode& gbSound2DNode::operator=(const gbSound2DNode& other) {
    if (this != &other) {
        soundData = other.soundData;
        sampleHandle = other.sampleHandle;
        loopCount = other.loopCount;
        volume = other.volume;
    }
    return *this;
}

// LoadFromFile - 0x10002940 (44B)
int gbSound2DNode::LoadFromFile(char* filename) {
    if (pAudioMgr == NULL) {
        return 0;
    }

    // Release old sound data
    if (soundData != NULL) {
        soundData->Release();
        soundData = NULL;
    }

    // Load via audio manager
    soundData = pAudioMgr->LoadSoundFile(filename);
    if (soundData == NULL) {
        return 0;
    }

    return 1;
}

// Play - 0x10002970 (85B)
void gbSound2DNode::Play() {
    if (pAudioMgr == NULL || soundData == NULL) {
        return;
    }

    // Attach sample handle if not attached
    if (sampleHandle == NULL) {
        pAudioMgr->AttachSampleHandle(this);
    }

    if (sampleHandle == NULL) {
        return;
    }

    // Set volume and loop, then start
    int vol = (int)(volume * pAudioMgr->volume2D * 127.0f);
    if (vol > 127) vol = 127;
    if (vol < 0) vol = 0;
    AIL_set_sample_volume(sampleHandle, vol);
    AIL_set_sample_loop_count(sampleHandle, loopCount);
    AIL_start_sample(sampleHandle);
}

// Stop - 0x100029d0 (24B)
void gbSound2DNode::Stop() {
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_end_sample(sampleHandle);
    }
}

// IsPlaying - 0x100029f0 (28B)
bool gbSound2DNode::IsPlaying() {
    if (!sampleHandle)
        return false;
    return AIL_sample_status(sampleHandle) == SMP_PLAYING;
}

// Pause - 0x10002a10 (24B)
void gbSound2DNode::Pause() {
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_stop_sample(sampleHandle);
    }
}

// Resume - 0x10002a30 (24B)
void gbSound2DNode::Resume() {
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_resume_sample(sampleHandle);
    }
}

// SetLoopNum - 0x10002630 (10B)
void gbSound2DNode::SetLoopNum(int num) {
    loopCount = num;
}

// SetVolume - 0x10002620 (10B)
void gbSound2DNode::SetVolume(float vol) {
    volume = vol;
}
