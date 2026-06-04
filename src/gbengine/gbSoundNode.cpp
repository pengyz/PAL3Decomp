/**
 * gbengine.dll - Audio nodes
 * gbSound3DNode (Miles Sound System 3D wrapper)
 */

#define GBVEC3D_NO_CTOR
#include "gbengine/gbAudio.h"
#include <string.h>

// Miles Sound System external functions (imported from mss32.dll)
#define AILCALL __stdcall
typedef void* H3DSAMPLE;

extern "C" {
__declspec(dllimport) void AILCALL AIL_start_3D_sample(H3DSAMPLE sample);
__declspec(dllimport) void AILCALL AIL_stop_3D_sample(H3DSAMPLE sample);
__declspec(dllimport) unsigned int AILCALL AIL_3D_sample_status(H3DSAMPLE sample);
__declspec(dllimport) void AILCALL AIL_set_3D_sample_volume(H3DSAMPLE sample, int volume);
__declspec(dllimport) void AILCALL AIL_set_3D_sample_loop_count(H3DSAMPLE sample, int count);
__declspec(dllimport) void AILCALL AIL_set_3D_sample_distances(H3DSAMPLE sample, float maxDist, float minDist);
__declspec(dllimport) void AILCALL AIL_set_3D_position(void* obj, float x, float y, float z);
__declspec(dllimport) void AILCALL AIL_set_3D_velocity(void* obj, float dx, float dy, float dz, float mag);
__declspec(dllimport) void AILCALL AIL_auto_update_3D_position(H3DSAMPLE sample, int flag);
__declspec(dllimport) void AILCALL AIL_WAV_info(void* data, void* info);
__declspec(dllimport) void AILCALL AIL_set_3D_sample_file(H3DSAMPLE sample, void* data);

// 2D sample functions
typedef void* HSAMPLE;
__declspec(dllimport) void AILCALL AIL_start_sample(HSAMPLE sample);
__declspec(dllimport) void AILCALL AIL_stop_sample(HSAMPLE sample);
__declspec(dllimport) void AILCALL AIL_end_sample(HSAMPLE sample);
__declspec(dllimport) void AILCALL AIL_resume_sample(HSAMPLE sample);
__declspec(dllimport) unsigned int AILCALL AIL_sample_status(HSAMPLE sample);
__declspec(dllimport) void AILCALL AIL_set_sample_volume(HSAMPLE sample, int volume);
__declspec(dllimport) void AILCALL AIL_set_sample_loop_count(HSAMPLE sample, int count);
}

void gbReportError(char* fmt, ...);

// Static member
gbAudioManager* gbSound3DNode::pAudioMgr = NULL;

// 0x10002640
gbSound3DNode::gbSound3DNode()
{
    *(int*)&position.x = 0;
    *(int*)&position.y = 0;
    *(int*)&position.z = 0;
    *(int*)&velocity.x = 0;
    *(int*)&velocity.y = 0;
    *(int*)&velocity.z = 0;
    *(int*)&orientation.x = 0;
    *(int*)&orientation.y = 0;
    *(int*)&orientation.z = 0;
    soundData = NULL;
    sampleHandle = NULL;
    minDist = 10000.0f;
    maxDist = 100000.0f;
    nLoop = 1;
    volume = 1.0f;
    field_2C = 0;
    position.Zero();
    velocity.Zero();
    orientation.Zero();
    orientation.z = 1.0f;
}

// 0x100026b0
gbSound3DNode::~gbSound3DNode()
{
    if (sampleHandle)
        pAudioMgr->DetachSampleHandle(this);
    if (soundData) {
        if (pAudioMgr) {
            if (sampleHandle)
                AIL_stop_3D_sample((H3DSAMPLE)sampleHandle);
        }
        pAudioMgr->DeleteSoundData(soundData);
    }
}

// 0x100025b0
gbSound3DNode& gbSound3DNode::operator=(const gbSound3DNode& other)
{
    soundData = other.soundData;
    sampleHandle = other.sampleHandle;
    position.x = other.position.x;
    position.y = other.position.y;
    position.z = other.position.z;
    velocity.x = other.velocity.x;
    velocity.y = other.velocity.y;
    velocity.z = other.velocity.z;
    orientation.x = other.orientation.x;
    orientation.y = other.orientation.y;
    orientation.z = other.orientation.z;
    field_2C = other.field_2C;
    volume = other.volume;
    nLoop = other.nLoop;
    minDist = other.minDist;
    maxDist = other.maxDist;
    return *this;
}

// 0x10002700
int gbSound3DNode::LoadFromFile(char* filename)
{
    if (pAudioMgr) {
        soundData = pAudioMgr->LoadSoundFile(filename);
        if (soundData) {
            struct { char data[20]; int nChannels; char pad[12]; } info;
            AIL_WAV_info(((void**)soundData)[6], &info);
            if (info.nChannels == 1)
                return 1;
            gbReportError("3D sound <%s> is stereo", filename);
        }
    }
    return 0;
}

// 0x10002760
void gbSound3DNode::Play()
{
    if (pAudioMgr && pAudioMgr->CanBeHeard(this)) {
        if (!sampleHandle)
            pAudioMgr->AttachSampleHandle(this);
        H3DSAMPLE h = (H3DSAMPLE)sampleHandle;
        AIL_set_3D_sample_volume(h, (int)(pAudioMgr->S_3DMasterVol * volume * 127.0f));
        float negZ = -position.z;
        AIL_set_3D_position(h, position.x, position.y, negZ);
        AIL_set_3D_sample_distances(h, maxDist, minDist);
        AIL_set_3D_sample_loop_count(h, nLoop);
        AIL_set_3D_velocity(h, 0.0f, 0.0f, 0.0f, 1.0f);
        AIL_auto_update_3D_position(h, 0);
        AIL_start_3D_sample(h);
    }
}

// 0x10002810
void gbSound3DNode::Stop()
{
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_stop_3D_sample((H3DSAMPLE)sampleHandle);
    }
}

// 0x10002830
int gbSound3DNode::IsPlaying()
{
    if (!pAudioMgr)
        return 0;
    if (!sampleHandle)
        return 0;
    return AIL_3D_sample_status((H3DSAMPLE)sampleHandle) == 4;
}

// 0x10002860
int gbSound3DNode::Update(double a2)
{
    float v7;
    float v6;

    if (pAudioMgr) {
        v7 = velocity.x * a2 + position.x;
        position.x = v7;
        v6 = velocity.y * a2 + position.y;
        position.y = v6;
        position.z = velocity.z * a2 + position.z;
        if (!sampleHandle)
            return 0;
        AIL_set_3D_position(sampleHandle, v7, v6, -position.z);
    }
    return 1;
}

// 0x100024d0
bool gbSound3DNode::IfAttached()
{
    return sampleHandle != NULL;
}

// 0x100024f0
void gbSound3DNode::SetLoopNum(int num)
{
    nLoop = num;
}

// 0x10002500
void gbSound3DNode::SetPosition(gbVec3D& pos)
{
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
}

// 0x10002520
void gbSound3DNode::SetVelocity(gbVec3D& vel)
{
    velocity.x = vel.x;
    velocity.y = vel.y;
    velocity.z = vel.z;
}

// 0x10002540
void gbSound3DNode::SetOrientation(gbVec3D& ori)
{
    orientation.x = ori.x;
    orientation.y = ori.y;
    orientation.z = ori.z;
}

// 0x100024e0
void gbSound3DNode::SetVolume(float vol)
{
    volume = vol;
}

// 0x10002560
void gbSound3DNode::GetPosition(gbVec3D& pos)
{
    pos.x = position.x;
    pos.y = position.y;
    pos.z = position.z;
}

// 0x10002590
float gbSound3DNode::GetMaxDist()
{
    return maxDist;
}

// GetMinDist
float gbSound3DNode::GetMinDist()
{
    return minDist;
}

// GetPlayLoop
int gbSound3DNode::GetPlayLoop()
{
    return nLoop;
}

// 0x10004420
void gbSound3DNode::SetDistParam(float minD, float maxD)
{
    minDist = minD;
    maxDist = maxD;
}


/* ======== gbSound2DNode ======== */

gbAudioManager* gbSound2DNode::pAudioMgr = NULL;

// 0x100028d0
gbSound2DNode::gbSound2DNode()
{
    soundData = NULL;
    sampleHandle = NULL;
    nLoop = 1;
    volume = 1.0f;
}

// 0x100028f0
gbSound2DNode::~gbSound2DNode()
{
    if (sampleHandle)
        pAudioMgr->DetachSampleHandle(this);
    if (soundData) {
        if (pAudioMgr) {
            if (sampleHandle)
                AIL_end_sample((HSAMPLE)sampleHandle);
        }
        pAudioMgr->DeleteSoundData(soundData);
    }
}

// 0x10002940
int gbSound2DNode::LoadFromFile(char* filename)
{
    if (!pAudioMgr)
        return 0;
    soundData = pAudioMgr->LoadSoundFile(filename);
    return soundData != NULL;
}

// 0x10002970
void gbSound2DNode::Play()
{
    if (pAudioMgr) {
        if (!sampleHandle)
            pAudioMgr->AttachSampleHandle(this);
        HSAMPLE h = (HSAMPLE)sampleHandle;
        AIL_set_sample_volume(h, (int)(pAudioMgr->S_2DMasterVol * volume * 127.0f));
        AIL_set_sample_loop_count(h, nLoop);
        AIL_start_sample(h);
    }
}

// 0x100029d0
void gbSound2DNode::Stop()
{
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_end_sample((HSAMPLE)sampleHandle);
    }
}

// 0x100029f0
bool gbSound2DNode::IsPlaying()
{
    if (!sampleHandle)
        return false;
    return AIL_sample_status((HSAMPLE)sampleHandle) == 4;
}

// 0x10002a10
void gbSound2DNode::Pause()
{
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_stop_sample((HSAMPLE)sampleHandle);
    }
}

// 0x10002a30
void gbSound2DNode::Resume()
{
    if (pAudioMgr) {
        if (sampleHandle)
            AIL_resume_sample((HSAMPLE)sampleHandle);
    }
}

// 0x10002620
void gbSound2DNode::SetVolume(float vol)
{
    volume = vol;
}

// 0x10002630
void gbSound2DNode::SetLoopNum(int num)
{
    nLoop = num;
}

// operator=
gbSound2DNode& gbSound2DNode::operator=(const gbSound2DNode& other)
{
    if (this != &other) {
        soundData = other.soundData;
        sampleHandle = other.sampleHandle;
        nLoop = other.nLoop;
        volume = other.volume;
    }
    return *this;
}
