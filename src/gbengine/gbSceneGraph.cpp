/**
 * gbengine.dll - gbSceneGraph
 * Auto-generated from Ghidra decompilation
 * Functions: 18
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


/* ======== gbLightObj ======== */

class gbLightObj {
public:
    // 0x10005390 (63B)
    gbLightObj(void) {}
    // 0x100053d0 (218B)
    gbLightObj(gbLightObj * p1) {}
    // 0x100131f0 (123B)
    void Init(int p1) {}
    // 0x10013280 (18B)
    void ComputeBoundSphere(void) {}
    // 0x100132a0 (175B)
    float GetEffectOnPoint(gbVec3D * p1, int p2) { return 0.0f; }
    // 0x10013350 (581B)
    void Compute(void * p1) {}
};


/* ======== gbSceneGraph ======== */

class gbSceneGraph {
public:
    // 0x10014b10 (322B)
    gbSceneGraph(gbGfxManager * p1, gbVec3D * p2, float p3) {}
    // 0x10014cd0 (13B)
    void AddSkyBox(gbVisNode * p1) {}
    // 0x10014ce0 (37B)
    void Begin(gbCamera * p1) {}
    // 0x10014d10 (83B)
    void * NewOneRenderObj(gbVisNode * p1) { return NULL; }
    // 0x10014d70 (25B)
    void * NewShadowVolume(gbVisNode * p1) { return NULL; }
    // 0x10014d90 (33B)
    void AddVolModNode(void * p1) {}
    // 0x10014dc0 (322B)
    void CalEffectiveVolMod(void * p1, gbVec3D * p2, int p3) {}
    // 0x10014f40 (1403B)
    void End(void) {}
    // 0x100155a0 (39B)
    void AddVisNode(gbVisNode * p1) {}
    // 0x100155d0 (42B)
    void DelVisNode(gbVisNode * p1) {}
    // 0x10015600 (19B)
    void SetBladeTimeScale(float p1) {}
    // 0x10015620 (11B)
    void ResetBladeMgr(void) {}
};

