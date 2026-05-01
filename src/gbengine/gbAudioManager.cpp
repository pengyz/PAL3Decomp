/**
 * gbengine.dll - gbAudioManager
 * Auto-generated from Ghidra decompilation
 * Functions: 46
 */

#include "gbengine/gbengine_types.h"

// Forward declarations
class BEZIER;
class CIniFile;
class CPK;
class CPKFile;
class gbActor;
class gbActorMgr;
class gbAnimNodeGroup;
class gbAudioManager;
class gbAudioMgrDesc;
class gbBaseMesh;
class gbBinaryTree;
class gbBinaryTreeNode;
class gbCamControler;
class gbCamQuakeControl;
class gbCamSpringControl;
class gbCamera;
class gbChain1D;
class gbChain1DNode;
class gbChain2D;
class gbChain2DNode;
class gbDropGroup;
class gbDropUnit;
class gbDynVertBuf;
class gbEffectMgr;
class gbEmitterData;
class gbEmitterSquare;
class gbGeomNode;
class gbGfxManager;
class gbGfxManager_D3D;
class gbImage2D;
class gbImage2DInfo;
class gbIndexBubble;
class gbIndexPool;
class gbLightObj;
class gbMatrixStack;
class gbNBTree;
class gbNBTreeNode;
class gbNameVarBuf;
class gbPartEmitter;
class gbPartGroupParam;
class gbPartParamControl;
class gbParticleEffect;
class gbParticleGroup;
class gbParticleUnit;
class gbPrintFont;
class gbPrintFontMgr;
class gbRain;
class gbRefObject;
class gbRenderEffect;
class gbResManager;
class gbResource;
class gbSceneGraph;
class gbSnow;
class gbSound2DNode;
class gbSound3DNode;
class gbStaticChain;
class gbStaticMesh;
class gbTexture;
class gbTextureArray;
class gbTexture_D3D;
class gbTimeCounter;
class gbVFile;
class gbVFile1;
class gbVFileSystem;
class gbVTextFile;
class gbVertPoolMgr;
class gbVertexPool;
class gbVisNode;


/* ======== gbAudioManager ======== */

class gbAudioManager {
public:
    // 0x10001020 (250B)
    unsigned long Get3DProvider(char * p1) { return 0; }
    // 0x10001120 (675B)
    gbAudioManager(int * p1, gbAudioMgrDesc * p2) {}
    // 0x10001560 (125B)
    void * LoadSoundFile(char * p1) { return NULL; }
    // 0x100015f0 (12B)
    void DeleteSoundData(void * p1) {}
    // 0x10001620 (392B)
    void AttachSampleHandle(gbSound3DNode * p1) {}
    // 0x100018d0 (58B)
    void DetachSampleHandle(gbSound3DNode * p1) {}
    // 0x10001970 (54B)
    void DetachAll3D(void) {}
    // 0x10001a10 (240B)
    void AttachSampleHandle(gbSound2DNode * p1) {}
    // 0x10001b00 (61B)
    void DetachSampleHandle(gbSound2DNode * p1) {}
    // 0x10001b70 (78B)
    void ReStartSoundStream(int p1) {}
    // 0x10001bc0 (136B)
    void PlaySoundStream(int p1, char * p2, int p3) {}
    // 0x10001c50 (42B)
    void StopSoundStream(int p1) {}
    // 0x10001c80 (67B)
    void SetMusicMasterVolume(float p1) {}
    // 0x10001cd0 (23B)
    void PauseSoundStream(int p1) {}
    // 0x10001cf0 (23B)
    void ResumeSoundStream(int p1) {}
    // 0x10001d10 (11B)
    int GetStreamStatus(int p1) { return 0; }
    // 0x10001d20 (62B)
    void SetListenerPosition(gbVec3D * p1) {}
    // 0x10001d60 (56B)
    void SetListenerOrientation(gbVec3D * p1, gbVec3D * p2) {}
    // 0x10001da0 (115B)
    int CanBeHeard(gbSound3DNode * p1) { return 0; }
    // 0x100021c0 (13B)
    void Set2DMasterVolume(float p1) {}
    // 0x100021e0 (13B)
    void Set3DMasterVolume(float p1) {}
    // 0x10002210 (33B)
    void GetListenerPosition(gbVec3D * p1) {}
    // 0x10002240 (276B)
    gbAudioManager(gbAudioManager * p1) {}
};


/* ======== gbAudioMgrDesc ======== */

class gbAudioMgrDesc {
public:
    // 0x10001000 (27B)
    gbAudioMgrDesc(void) {}
};


/* ======== gbSound2DNode ======== */

class gbSound2DNode {
public:
    // 0x10002620 (10B)
    void SetVolume(float p1) {}
    // 0x10002630 (10B)
    void SetLoopNum(int p1) {}
    // 0x100028d0 (30B)
    gbSound2DNode(void) {}
    // 0x10002940 (44B)
    int LoadFromFile(char * p1) { return 0; }
    // 0x10002970 (85B)
    void Play(void) {}
    // 0x100029d0 (24B)
    void Stop(void) {}
    // 0x100029f0 (28B)
    int IsPlaying(void) { return 0; }
    // 0x10002a10 (24B)
    void Pause(void) {}
    // 0x10002a30 (24B)
    void Resume(void) {}
};


/* ======== gbSound3DNode ======== */

class gbSound3DNode {
public:
    // 0x100024d0 (11B)
    int IfAttached(void) { return 0; }
    // 0x100024e0 (10B)
    void SetVolume(float p1) {}
    // 0x100024f0 (10B)
    void SetLoopNum(int p1) {}
    // 0x10002500 (24B)
    void SetPosition(gbVec3D * p1) {}
    // 0x10002520 (24B)
    void SetVelocity(gbVec3D * p1) {}
    // 0x10002540 (24B)
    void SetOrientation(gbVec3D * p1) {}
    // 0x10002560 (24B)
    void GetPosition(gbVec3D * p1) {}
    // 0x10002640 (99B)
    gbSound3DNode(void) {}
    // 0x10002700 (85B)
    int LoadFromFile(char * p1) { return 0; }
    // 0x10002760 (174B)
    void Play(void) {}
    // 0x10002810 (24B)
    void Stop(void) {}
    // 0x10002830 (38B)
    int IsPlaying(void) { return 0; }
    // 0x10002860 (110B)
    int Update(double p1) { return 0; }
};

