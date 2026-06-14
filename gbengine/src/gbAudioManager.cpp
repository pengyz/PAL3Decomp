/**
 * gbengine.dll - gbAudioManager, gbAudioMgrDesc, gbSound3DNode, gbSound2DNode, gbSoundData
 * Audio system implementation using Miles Sound System (AIL)
 * Functions: 46 exports
 */

#include "gbengine/gbAudio.h"
#include "gbengine/gbTexture.h"
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

int AILCALL AIL_enumerate_3D_providers(HPROVIDER* next, HPROVIDER* dest, char** name);
int AILCALL AIL_open_3D_provider(HPROVIDER provider);
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
int AILCALL AIL_file_size(const char* filename);
int AILCALL AIL_file_type(void* data, int size);
void AILCALL AIL_decompress_ASI(void* data, int size, const char* filename, void* dest, int a5, int a6);
void AILCALL AIL_decompress_ADPCM(void* info, void* dest, int a3);
void AILCALL AIL_mem_free_lock(void* ptr);
}

// External functions (from gbResManager.cpp)
extern unsigned int gbCrc32Compute(const char* str);
extern void gbReportError(char* fmt, ...);

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

// Load - 0x10001e40 (191B)
// Loads a sound file, decompressing ADPCM/ASI formats as needed.
// AIL_file_type returns: 1=raw PCM, 2=WAV/ADPCM, 13=ASI compressed
// NOTE: nested if/else matches original codegen (not a switch)
int gbSoundData::Load(char* filename) {
    int dataSize = AIL_file_size(filename);
    void* data = AIL_file_read(filename, 0);
    if (!data) {
        gbReportError("read sound file(%s) error", filename);
        return 0;
    }

    int fileType = AIL_file_type(data, dataSize);
    if (fileType == 1) {
        // Raw PCM - use data buffer directly
        fileData = data;
    } else if (fileType == 2) {
        // WAV/ADPCM - decompress
        char wavInfo[36];
        AIL_WAV_info(data, wavInfo);
        AIL_decompress_ADPCM(wavInfo, &fileData, 0);
        AIL_mem_free_lock(data);
    } else if (fileType == 13) {
        // ASI compressed
        AIL_decompress_ASI(data, dataSize, filename, &fileData, 0, 0);
        AIL_mem_free_lock(data);
    } else {
        // Unknown format
        AIL_mem_free_lock(data);
        return 0;
    }

    SetName(filename);
    return 1;
}

// ======== gbSoundResource ========
// A sound resource that inherits from gbResource.
// Layout: gbResource(0x18) + pSoundData(4) = 0x1C
class gbSoundResource : public gbResource {
public:
    void* pSoundData;    // +0x18: loaded sound data (freed with AIL_mem_free_lock)

    virtual ~gbSoundResource();
};

// 0x10001F00 (32B)
gbSoundResource::~gbSoundResource() {
    if (pSoundData) {
        AIL_mem_free_lock(pSoundData);
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




/* ======== Global pointer (DAT_1012b980) ======== */

static gbAudioManager* g_pAudioManager = NULL;


/* ================================================================
 * gbAudioManager implementation
 * ================================================================ */

// Constructor - 0x10001120 (675B)
// Reconstructed from IDA disassembly
gbAudioManager::gbAudioManager(int& result, gbAudioMgrDesc* desc) {
    int i;

    // Zero listener position
    listenerPosition.x = 0.0f;
    listenerPosition.y = 0.0f;
    listenerPosition.z = 0.0f;

    // Initialize embedded resource manager (at +0xE8)
    soundResManager.Init();

    result = 0;

    // Initialize Miles Sound System
    AIL_set_redist_directory("miles\\win32\\");
    AIL_startup();

    // Open digital driver
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

    // Zero and allocate 3D sample slots
    memset(slots3D, 0, sizeof(slots3D));
    for (i = 0; i < MAX_3D_SAMPLES; i++) {
        slots3D[i].handle = AIL_allocate_3D_sample_handle(provider3D);
    }

    // Zero and allocate 2D sample slots
    memset(slots2D, 0, sizeof(slots2D));
    for (i = 0; i < MAX_2D_SAMPLES; i++) {
        slots2D[i].handle = AIL_allocate_sample_handle(digitalDriver);
    }

    // Initialize counters and volumes
    allocCounter = 0;
    S_3DMasterVol = 1.0f;
    S_2DMasterVol = 1.0f;
    MusicMasterVol = 1.0f;

    // Create 3D listener
    listener = AIL_open_3D_listener(provider3D);
    listenerPosition.x = 0.0f;
    listenerPosition.y = 0.0f;
    listenerPosition.z = 0.0f;
    AIL_set_3D_position(listener, 0.0f, 0.0f, 0.0f);
    AIL_set_3D_orientation(listener, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

    // Initialize streams
    for (i = 0; i < MAX_STREAMS; i++) {
        streams[i] = NULL;
        streamStatus[i] = 2;
    }

    // Set static audio manager pointers
    g_pAudioManager = this;
    gbSound3DNode::pAudioMgr = this;
    gbSound2DNode::pAudioMgr = this;

    result = 1;
}

// Copy constructor - 0x10002240 (276B)
gbAudioManager::gbAudioManager(const gbAudioManager& other) {
    int i;

    for (i = 0; i < MAX_STREAMS; i++) {
        streams[i] = other.streams[i];
        streamStatus[i] = other.streamStatus[i];
    }

    digitalDriver = other.digitalDriver;
    provider3D = other.provider3D;
    allocCounter = other.allocCounter;
    listener = other.listener;
    S_2DMasterVol = other.S_2DMasterVol;
    S_3DMasterVol = other.S_3DMasterVol;
    MusicMasterVol = other.MusicMasterVol;
    listenerPosition = other.listenerPosition;

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
    for (i = 0; i < MAX_3D_SAMPLES; i++) {
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

// operator= - 0x10002360 (368B)
gbAudioManager& gbAudioManager::operator=(const gbAudioManager& other) {
    int i;
    for (i = 0; i < MAX_STREAMS; i++) {
        streams[i] = other.streams[i];
    }
    for (i = 0; i < MAX_STREAMS; i++) {
        streamStatus[i] = other.streamStatus[i];
    }
    digitalDriver = other.digitalDriver;
    provider3D = other.provider3D;
    for (i = 0; i < MAX_3D_SAMPLES; i++) {
        slots3D[i] = other.slots3D[i];
    }
    for (i = 0; i < MAX_2D_SAMPLES; i++) {
        slots2D[i] = other.slots2D[i];
    }
    allocCounter = other.allocCounter;
    listener = other.listener;
    S_2DMasterVol = other.S_2DMasterVol;
    S_3DMasterVol = other.S_3DMasterVol;
    MusicMasterVol = other.MusicMasterVol;
    listenerPosition = other.listenerPosition;
    if (soundResManager.array) {
        free(soundResManager.array);
    }
    soundResManager.capacity = other.soundResManager.capacity;
    soundResManager.count = other.soundResManager.count;
    if (other.soundResManager.capacity) {
        soundResManager.array = (void**)malloc(4 * other.soundResManager.capacity);
    } else {
        soundResManager.array = NULL;
    }
    if (soundResManager.count) {
        memcpy(soundResManager.array, other.soundResManager.array, 4 * soundResManager.count);
    }
    return *this;
}

// Get3DProvider - 0x10001020 (250B)
unsigned long gbAudioManager::Get3DProvider(char* providerName) {
    HPROVIDER next = 0;
    HPROVIDER dest;
    char* name;

    const char* defaultName = "Miles Fast 2D Positional Audio";
    const char* searchName = (providerName != NULL) ? providerName : defaultName;

    HPROVIDER foundProvider = 0;
    while (AIL_enumerate_3D_providers(&next, &dest, &name)) {
        if (name != NULL && strcmp(name, searchName) == 0) {
            foundProvider = dest;
            break;
        }
    }

    if (foundProvider == 0) {
        return 0;
    }

    int openResult = AIL_open_3D_provider(foundProvider);
    if (openResult != 0) {
        return 0;
    }
    provider3D = (H3DPROVIDER)foundProvider;

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
    ((gbRefObject*)data)->Release();
}

// AttachSampleHandle (3D) - 0x10001620 (392B)
// Reconstructed from IDA disassembly with correct field names
void gbAudioManager::AttachSampleHandle(gbSound3DNode* node) {
    unsigned int freeSlot = 0xFFFF;
    int i;

    // Increment allocation counter
    allocCounter++;

    // Strategy 1: find an empty slot (node == NULL)
    for (i = 0; i < MAX_3D_SAMPLES; i++) {
        if (slots3D[i].node == NULL) {
            freeSlot = i;
            goto ATTACH;
        }
    }

    // Strategy 2: find a stopped sample and evict it
    for (i = 0; i < MAX_3D_SAMPLES; i++) {
        if (AIL_3D_sample_status(slots3D[i].handle) == SMP_STOPPED) {
            AIL_end_3D_sample(slots3D[i].handle);
            freeSlot = i;
            slots3D[i].node->sampleHandle = NULL;
            goto ATTACH;
        }
    }

    // Strategy 3: evict the farthest sample from listener
    {
        float dx = node->position.x - listenerPosition.x;
        float dy = node->position.y - listenerPosition.y;
        float dz = node->position.z - listenerPosition.z;
        float distSq = dz * dz + dy * dy + dx * dx;

        for (i = 0; i < MAX_3D_SAMPLES; i++) {
            float sx = slots3D[i].node->position.x - listenerPosition.x;
            float sy = slots3D[i].node->position.y - listenerPosition.y;
            float sz = slots3D[i].node->position.z - listenerPosition.z;
            float d2 = sz * sz + sy * sy + sx * sx;
            if (d2 > distSq) {
                distSq = d2;
                freeSlot = i;
            }
        }

        if (freeSlot > 9)
            return;

        AIL_end_3D_sample(slots3D[freeSlot].handle);
        slots3D[freeSlot].node->sampleHandle = NULL;
    }

ATTACH:
    slots3D[freeSlot].flags = allocCounter;
    slots3D[freeSlot].node = node;
    node->sampleHandle = slots3D[freeSlot].handle;
    AIL_set_3D_sample_file(slots3D[freeSlot].handle, node->soundData->fileData);
}

// DetachSampleHandle (3D) - 0x100018d0 (58B)
void gbAudioManager::DetachSampleHandle(gbSound3DNode* node) {
    for (int i = 0; i < MAX_3D_SAMPLES; i++) {
        if (slots3D[i].node == node) {
            AIL_end_3D_sample(node->sampleHandle);
            node->sampleHandle = NULL;
            slots3D[i].node = NULL;
        }
    }
}

// DetachAll3D - 0x10001970 (54B)
void gbAudioManager::DetachAll3D() {
    for (int i = 0; i < MAX_3D_SAMPLES; i++) {
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
    int vol = (int)(node->volume * S_2DMasterVol * 127.0f);
    if (vol > 127) vol = 127;
    if (vol < 0) vol = 0;
    AIL_set_sample_volume(sample, vol);
    AIL_set_sample_loop_count(sample, node->nLoop);

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

// StreamEndCallback - 0x10001b40 (44B)
// Miles Sound System stream end callback (__stdcall)
static int __stdcall StreamEndCallback(int streamHandle) {
    int result = 0;
    int* pStreams = (int*)&g_pAudioManager->streams[0];
    for (; *pStreams != streamHandle; ++pStreams) {
        if (++result >= MAX_STREAMS)
            return result;
    }
    g_pAudioManager->streamStatus[result] = 2;
    return result;
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
    int vol = (int)(MusicMasterVol * 127.0f);
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
    if (streams[index] != NULL) {
        AIL_close_stream(streams[index]);
        streams[index] = NULL;
        streamStatus[index] = 2;
    }
}

// PauseSoundStream - 0x10001cd0 (23B)
void gbAudioManager::PauseSoundStream(int index) {
    if (streams[index] != NULL)
        AIL_pause_stream(streams[index], 1);
}

// ResumeSoundStream - 0x10001cf0 (23B)
void gbAudioManager::ResumeSoundStream(int index) {
    if (streams[index] != NULL)
        AIL_pause_stream(streams[index], 0);
}

// GetStreamStatus - 0x10001d10 (11B)
int gbAudioManager::GetStreamStatus(int index) {
    return streamStatus[index];
}

// SetMusicMasterVolume - 0x10001c80 (67B)
void gbAudioManager::SetMusicMasterVolume(float vol) {
    MusicMasterVol = vol;

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
    return MusicMasterVol;
}

// SetListenerPosition - 0x10001d20 (62B)
void gbAudioManager::SetListenerPosition(const gbVec3D& pos) {
    listenerPosition = pos;
    float negZ = -pos.z;
    AIL_set_3D_position(listener, pos.x, pos.y, negZ);
}

// SetListenerOrientation - 0x10001d60 (56B)
void gbAudioManager::SetListenerOrientation(gbVec3D& front, gbVec3D& top) {
    float negTopZ = -top.z;
    float negFrontZ = -front.z;
    AIL_set_3D_orientation(listener, front.x, front.y, negFrontZ, top.x, top.y, negTopZ);
}

// GetListenerPosition - 0x10002210 (33B)
void gbAudioManager::GetListenerPosition(gbVec3D& pos) {
    pos.x = listenerPosition.x;
    pos.y = listenerPosition.y;
    pos.z = listenerPosition.z;
}

// Set2DMasterVolume - 0x100021c0 (13B)
void gbAudioManager::Set2DMasterVolume(float vol) {
    S_2DMasterVol = vol;
}

// Get2DMasterVolume
float gbAudioManager::Get2DMasterVolume() {
    return S_2DMasterVol;
}

// Set3DMasterVolume - 0x100021e0 (13B)
void gbAudioManager::Set3DMasterVolume(float vol) {
    S_3DMasterVol = vol;
}

// Get3DMasterVolume
float gbAudioManager::Get3DMasterVolume() {
    return S_3DMasterVol;
}


