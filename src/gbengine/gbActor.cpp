/**
 * gbengine.dll - gbActor
 * Auto-generated from Ghidra decompilation
 * Functions: 38
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


/* ======== gbActor ======== */

class gbActor {
public:
    // 0x10002ad0 (287B)
    gbActor(void * p1) {}
    // 0x10002cd0 (256B)
    void UpdateExportNodes(void) {}
    // 0x10002dd0 (42B)
    void GotoAction(char * p1, int p2) {}
    // 0x10002e00 (67B)
    void GotoAction(char * p1, float p2, float p3) {}
    // 0x10002e50 (203B)
    void GotoAction(char * p1, char * p2, char * p3) {}
    // 0x10002f20 (200B)
    void GotoAction(int p1, int p2, int p3, int p4, int p5) {}
    // 0x10002ff0 (81B)
    void LockAction(char * p1, float p2) {}
    // 0x10003050 (64B)
    void UnlockAction(char * p1) {}
    // 0x10003090 (16B)
    unsigned int GetActionDuration(char * p1) { return 0; }
    // 0x100030a0 (68B)
    void EnableActionTransMtl(char * p1, int p2) {}
    // 0x100030f0 (85B)
    int GetTagNodeTM(gbMatrix4 * p1, char * p2) { return 0; }
    // 0x10003180 (61B)
    void Render(void * p1) {}
    // 0x100031c0 (61B)
    void RenderShadowVolume(void * p1) {}
    // 0x10003200 (81B)
    int Attach(gbRenderEffect * p1) { return 0; }
    // 0x10003260 (126B)
    void Reset(float p1) {}
    // 0x100032e0 (516B)
    void Update(void) {}
    // 0x100034f0 (82B)
    unsigned int GetEventTime(char * p1, char * p2) { return 0; }
    // 0x10003550 (37B)
    void GetBoundSphere(gbSphere * p1) {}
    // 0x10003580 (31B)
    void EnableShadow(int p1) {}
    // 0x10005050 (19B)
    void GetCollideOBB(gbOBBox * p1) {}
    // 0x10005070 (8B)
    gbAABBox * GetCollideAABBox(void) { return NULL; }
    // 0x100050c0 (16B)
    void SetCurMaterial(char * p1) {}
    // 0x100050d0 (186B)
    gbActor(gbActor * p1) {}
};


/* ======== gbActorMgr ======== */

class gbActorMgr {
public:
    // 0x100035a0 (125B)
    gbActorMgr(gbGfxManager * p1) {}
    // 0x10003680 (337B)
    gbActor * LoadActorFile(char * p1) { return NULL; }
    // 0x100037e0 (17B)
    void DestroyActor(gbActor * p1) {}
    // 0x100052a0 (79B)
    gbActorMgr(gbActorMgr * p1) {}
};


/* ======== gbAnimNodeGroup ======== */

class gbAnimNodeGroup {
public:
    // 0x1000c3c0 (145B)
    gbAnimNodeGroup(gbGfxManager * p1) {}
    // 0x1000c490 (319B)
    gbAnimNodeGroup * Clone(void) { return NULL; }
    // 0x1000c5d0 (307B)
    void LoadFromFile(char * p1) {}
    // 0x1000c710 (36B)
    void SetPosition(gbVec3D * p1) {}
    // 0x1000c740 (16B)
    void SetPosition(gbMatrix4 * p1) {}
    // 0x1000c750 (68B)
    void Attach(void) {}
    // 0x1000c7a0 (237B)
    void Update(void) {}
    // 0x1000c890 (103B)
    void Reset(void) {}
    // 0x1000c900 (85B)
    void SetPriority(int p1) {}
    // 0x1000cd10 (11B)
    int IsDead(void) { return 0; }
    // 0x1000cd20 (8B)
    void SetToDead(void) {}
};

