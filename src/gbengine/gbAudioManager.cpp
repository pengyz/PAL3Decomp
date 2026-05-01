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

// Miles Sound System stub implementations (real game links mss32.dll)
static void AIL_set_redist_directory(const char* dir) {}
static int AIL_startup(void) { return 1; }
static void AIL_shutdown(void) {}

static HDIGDRIVER AIL_open_digital_driver(unsigned int freq, int bits, int channels, unsigned int flags) { return (HDIGDRIVER)1; }
static void AIL_close_digital_driver(HDIGDRIVER driver) {}

static int AIL_enumerate_3D_providers(HPROVIDER* dest, void** query, unsigned int* count) { return 0; }
static H3DPROVIDER AIL_open_3D_provider(HPROVIDER provider) { return (H3DPROVIDER)1; }
static void AIL_close_3D_provider(H3DPROVIDER provider) {}

static H3DLISTENER AIL_open_3D_listener(H3DPROVIDER provider) { return (H3DLISTENER)1; }
static void AIL_close_3D_listener(H3DLISTENER listener) {}
static void AIL_set_3D_position(void* obj, float x, float y, float z) {}
static void AIL_set_3D_orientation(void* obj, float fx, float fy, float fz, float ux, float uy, float uz) {}
static void AIL_3D_position(void* obj, float* x, float* y, float* z) { if(x)*x=0; if(y)*y=0; if(z)*z=0; }

static H3DSAMPLE AIL_allocate_3D_sample_handle(H3DPROVIDER provider) { return (H3DSAMPLE)1; }
static void AIL_release_3D_sample_handle(H3DSAMPLE sample) {}
static void AIL_set_3D_sample_file(H3DSAMPLE sample, void* data) {}
static void AIL_start_3D_sample(H3DSAMPLE sample) {}
static void AIL_stop_3D_sample(H3DSAMPLE sample) {}
static void AIL_resume_3D_sample(H3DSAMPLE sample) {}
static unsigned int AIL_3D_sample_status(H3DSAMPLE sample) { return SMP_DONE; }
static void AIL_set_3D_sample_volume(H3DSAMPLE sample, float volume) {}
static void AIL_set_3D_sample_loop_count(H3DSAMPLE sample, int count) {}
static void AIL_set_3D_sample_distances(H3DSAMPLE sample, float maxDist, float minDist) {}
static void AIL_set_3D_velocity(void* obj, float dx, float dy, float dz) {}

static HSAMPLE AIL_allocate_sample_handle(HDIGDRIVER driver) { return (HSAMPLE)1; }
static void AIL_release_sample_handle(HSAMPLE sample) {}
static void AIL_set_sample_file(HSAMPLE sample, void* data, int block) {}
static void AIL_start_sample(HSAMPLE sample) {}
static void AIL_stop_sample(HSAMPLE sample) {}
static void AIL_resume_sample(HSAMPLE sample) {}
static void AIL_pause_sample(HSAMPLE sample) {}
static unsigned int AIL_sample_status(HSAMPLE sample) { return SMP_DONE; }
static void AIL_set_sample_volume(HSAMPLE sample, int volume) {}
static void AIL_set_sample_loop_count(HSAMPLE sample, int count) {}

static HSTREAM AIL_open_stream(HDIGDRIVER driver, const char* filename, int block) { return NULL; }
static void AIL_close_stream(HSTREAM stream) {}
static void AIL_start_stream(HSTREAM stream) {}
static void AIL_pause_stream(HSTREAM stream, int onoff) {}
static void AIL_set_stream_volume(HSTREAM stream, int volume) {}
static unsigned int AIL_stream_status(HSTREAM stream) { return SMP_DONE; }

static void* AIL_file_read(const char* filename, void* dest) { return NULL; }
static void AIL_mem_free_lock(void* ptr) {}

// External functions (from gbResManager.cpp)
extern unsigned int gbCrc32Compute(const char* str);

// gbResManagerStub method implementations
void gbResManagerStub::Init() { array = NULL; capacity = 0; count = 0; }
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

void gbSoundData::IncRef() { refCount++; }

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
    providerName = 0;    // use default provider
}

// operator=
gbAudioMgrDesc& gbAudioMgrDesc::operator=(const gbAudioMgrDesc& other) {
    freq = other.freq;
    bits = other.bits;
    channels = other.channels;
    providerName = other.providerName;
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
    num2DSamples = 0;
    listener = NULL;
    volume2D = 1.0f;
    volume3D = 1.0f;
    musicVolume = 1.0f;
    musicMasterVolume = 1.0f;
    reserved = 0;

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
    if (desc->providerName != 0) {
        provName = &desc->providerName;
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
    num2DSamples = MAX_2D_SAMPLES;

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
    num2DSamples = other.num2DSamples;
    listener = other.listener;
    volume2D = other.volume2D;
    volume3D = other.volume3D;
    musicVolume = other.musicVolume;
    musicMasterVolume = other.musicMasterVolume;
    reserved = other.reserved;

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
    for (i = 0; i < num2DSamples; i++) {
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
        num2DSamples = other.num2DSamples;
        listener = other.listener;
        volume2D = other.volume2D;
        volume3D = other.volume3D;
        musicVolume = other.musicVolume;
        musicMasterVolume = other.musicMasterVolume;
        reserved = other.reserved;
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
    void* query;
    unsigned int count;

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
    if (data != NULL) {
        data->Release();
    }
}

// AttachSampleHandle (3D) - 0x10001620 (392B)
void gbAudioManager::AttachSampleHandle(gbSound3DNode* node) {
    if (node == NULL || node->soundData == NULL) {
        return;
    }

    // Find a free 3D sample slot
    int freeSlot = -1;
    for (int i = 0; i < num3DSamples; i++) {
        if (slots3D[i].flags == 0) {
            freeSlot = i;
            break;
        }
    }

    if (freeSlot == -1) {
        // No free slot - try to steal one that finished playing
        for (int i = 0; i < num3DSamples; i++) {
            if (slots3D[i].handle != NULL) {
                unsigned int status = AIL_3D_sample_status(slots3D[i].handle);
                if (status == SMP_DONE || status == SMP_STOPPED) {
                    // Detach the old node
                    if (slots3D[i].node != NULL) {
                        slots3D[i].node->sampleHandle = NULL;
                        slots3D[i].node->attached = 0;
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
    H3DSAMPLE sample = slots3D[freeSlot].handle;
    AIL_set_3D_sample_file(sample, node->soundData->fileData);
    AIL_set_3D_sample_volume(sample, node->volume * volume3D);
    AIL_set_3D_sample_loop_count(sample, node->loopCount);
    AIL_set_3D_sample_distances(sample, node->maxDist, node->minDist);
    AIL_set_3D_position(sample, node->position.x, node->position.y, node->position.z);
    AIL_set_3D_velocity(sample, node->velocity.x, node->velocity.y, node->velocity.z);

    // Link node to slot
    node->sampleHandle = sample;
    node->attached = 1;
    slots3D[freeSlot].node = node;
    slots3D[freeSlot].flags = 1;
}

// DetachSampleHandle (3D) - 0x100018d0 (58B)
void gbAudioManager::DetachSampleHandle(gbSound3DNode* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < num3DSamples; i++) {
        if (slots3D[i].node == node) {
            AIL_stop_3D_sample(slots3D[i].handle);
            slots3D[i].node = NULL;
            slots3D[i].flags = 0;
            node->sampleHandle = NULL;
            node->attached = 0;
            break;
        }
    }
}

// DetachAll3D - 0x10001970 (54B)
void gbAudioManager::DetachAll3D() {
    for (int i = 0; i < num3DSamples; i++) {
        if (slots3D[i].flags != 0) {
            AIL_stop_3D_sample(slots3D[i].handle);
            if (slots3D[i].node != NULL) {
                slots3D[i].node->sampleHandle = NULL;
                slots3D[i].node->attached = 0;
            }
            slots3D[i].node = NULL;
            slots3D[i].flags = 0;
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
    for (int i = 0; i < num2DSamples; i++) {
        if (slots2D[i].flags == 0) {
            freeSlot = i;
            break;
        }
    }

    if (freeSlot == -1) {
        // Try to steal a finished slot
        for (int i = 0; i < num2DSamples; i++) {
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

    for (int i = 0; i < num2DSamples; i++) {
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
    if (index < 0 || index >= MAX_STREAMS) {
        return;
    }

    if (streams[index] != NULL) {
        AIL_close_stream(streams[index]);
        streams[index] = NULL;
        streamStatus[index] = 0;
    }
}

// PauseSoundStream - 0x10001cd0 (23B)
void gbAudioManager::PauseSoundStream(int index) {
    if (index < 0 || index >= MAX_STREAMS) {
        return;
    }
    if (streams[index] != NULL) {
        AIL_pause_stream(streams[index], 1);
        streamStatus[index] = 2;
    }
}

// ResumeSoundStream - 0x10001cf0 (23B)
void gbAudioManager::ResumeSoundStream(int index) {
    if (index < 0 || index >= MAX_STREAMS) {
        return;
    }
    if (streams[index] != NULL) {
        AIL_pause_stream(streams[index], 0);
        streamStatus[index] = 1;
    }
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
    if (listener != NULL) {
        AIL_set_3D_position(listener, pos.x, pos.y, pos.z);
    }
}

// SetListenerOrientation - 0x10001d60 (56B)
void gbAudioManager::SetListenerOrientation(gbVec3D& front, gbVec3D& top) {
    if (listener != NULL) {
        AIL_set_3D_orientation(listener, front.x, front.y, front.z, top.x, top.y, top.z);
    }
}

// GetListenerPosition - 0x10002210 (33B)
void gbAudioManager::GetListenerPosition(gbVec3D& pos) {
    if (listener != NULL) {
        AIL_3D_position(listener, &pos.x, &pos.y, &pos.z);
    }
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
    soundData = NULL;
    sampleHandle = NULL;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;
    orientation.x = 0.0f;
    orientation.y = 0.0f;
    orientation.z = 1.0f;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.z = 0.0f;
    attached = 0;
    volume = 1.0f;
    loopCount = 1;
    minDist = 10000.0f;
    maxDist = 100000.0f;
}

// Destructor
gbSound3DNode::~gbSound3DNode() {
    if (attached && pAudioMgr != NULL) {
        pAudioMgr->DetachSampleHandle(this);
    }
    if (soundData != NULL) {
        soundData->Release();
        soundData = NULL;
    }
}

// operator=
gbSound3DNode& gbSound3DNode::operator=(const gbSound3DNode& other) {
    if (this != &other) {
        soundData = other.soundData;
        sampleHandle = other.sampleHandle;
        position = other.position;
        orientation = other.orientation;
        velocity = other.velocity;
        attached = other.attached;
        volume = other.volume;
        loopCount = other.loopCount;
        minDist = other.minDist;
        maxDist = other.maxDist;
    }
    return *this;
}

// LoadFromFile - 0x10002700 (85B)
int gbSound3DNode::LoadFromFile(char* filename) {
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

// Play - 0x10002760 (174B)
void gbSound3DNode::Play() {
    if (pAudioMgr == NULL || soundData == NULL) {
        return;
    }

    // Attach sample handle if not already attached
    if (!attached) {
        pAudioMgr->AttachSampleHandle(this);
    }

    if (!attached || sampleHandle == NULL) {
        return;
    }

    // Configure and start playback
    AIL_set_3D_sample_volume(sampleHandle, volume * pAudioMgr->volume3D);
    AIL_set_3D_sample_loop_count(sampleHandle, loopCount);
    AIL_set_3D_sample_distances(sampleHandle, maxDist, minDist);
    AIL_set_3D_position(sampleHandle, position.x, position.y, position.z);
    AIL_set_3D_velocity(sampleHandle, velocity.x, velocity.y, velocity.z);
    AIL_start_3D_sample(sampleHandle);
}

// Stop - 0x10002810 (24B)
void gbSound3DNode::Stop() {
    if (sampleHandle != NULL) {
        AIL_stop_3D_sample(sampleHandle);
    }
}

// IsPlaying - 0x10002830 (38B)
int gbSound3DNode::IsPlaying() {
    if (sampleHandle == NULL) {
        return 0;
    }
    unsigned int status = AIL_3D_sample_status(sampleHandle);
    return (status == SMP_PLAYING) ? 1 : 0;
}

// SetPosition - 0x10002500 (24B)
void gbSound3DNode::SetPosition(gbVec3D& pos) {
    position = pos;
    if (sampleHandle != NULL) {
        AIL_set_3D_position(sampleHandle, pos.x, pos.y, pos.z);
    }
}

// GetPosition - 0x10002560 (24B)
void gbSound3DNode::GetPosition(gbVec3D& pos) {
    pos = position;
}

// SetOrientation - 0x10002540 (24B)
void gbSound3DNode::SetOrientation(gbVec3D& ori) {
    orientation = ori;
}

// SetVelocity - 0x10002520 (24B)
void gbSound3DNode::SetVelocity(gbVec3D& vel) {
    velocity = vel;
    if (sampleHandle != NULL) {
        AIL_set_3D_velocity(sampleHandle, vel.x, vel.y, vel.z);
    }
}

// SetVolume - 0x100024e0 (10B)
void gbSound3DNode::SetVolume(float vol) {
    volume = vol;
}

// SetLoopNum - 0x100024f0 (10B)
void gbSound3DNode::SetLoopNum(int num) {
    loopCount = num;
}

// SetDistParam
void gbSound3DNode::SetDistParam(float minD, float maxD) {
    minDist = minD;
    maxDist = maxD;
    if (sampleHandle != NULL) {
        AIL_set_3D_sample_distances(sampleHandle, maxDist, minDist);
    }
}

// GetMinDist
float gbSound3DNode::GetMinDist() {
    return minDist;
}

// GetMaxDist
float gbSound3DNode::GetMaxDist() {
    return maxDist;
}

// GetPlayLoop
int gbSound3DNode::GetPlayLoop() {
    return loopCount;
}

// IfAttached - 0x100024d0 (11B)
bool gbSound3DNode::IfAttached() {
    return attached != 0;
}

// Update - 0x10002860 (110B)
int gbSound3DNode::Update(double deltaTime) {
    if (!attached || sampleHandle == NULL) {
        return 0;
    }

    // Check if playback has finished
    unsigned int status = AIL_3D_sample_status(sampleHandle);
    if (status == SMP_DONE || status == SMP_STOPPED) {
        // Sound finished - detach
        if (pAudioMgr != NULL) {
            pAudioMgr->DetachSampleHandle(this);
        }
        return 0;
    }

    // Update 3D position for moving sounds
    AIL_set_3D_position(sampleHandle, position.x, position.y, position.z);
    AIL_set_3D_velocity(sampleHandle, velocity.x, velocity.y, velocity.z);

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
    if (sampleHandle != NULL) {
        AIL_stop_sample(sampleHandle);
    }
}

// IsPlaying - 0x100029f0 (28B)
bool gbSound2DNode::IsPlaying() {
    if (sampleHandle == NULL) {
        return false;
    }
    unsigned int status = AIL_sample_status(sampleHandle);
    return (status == SMP_PLAYING);
}

// Pause - 0x10002a10 (24B)
void gbSound2DNode::Pause() {
    if (sampleHandle != NULL) {
        AIL_pause_sample(sampleHandle);
    }
}

// Resume - 0x10002a30 (24B)
void gbSound2DNode::Resume() {
    if (sampleHandle != NULL) {
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
