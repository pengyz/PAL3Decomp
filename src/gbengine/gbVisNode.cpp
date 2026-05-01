/**
 * gbengine.dll - gbVisNode
 * Auto-generated from Ghidra decompilation
 * Functions: 17
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


/* ======== gbVisNode ======== */

class gbVisNode {
public:
    // 0x10004a60 (138B)
    gbVisNode(gbVisNode * p1) {}
    // 0x10016590 (163B)
    gbVisNode(void) {}
    // 0x10016640 (89B)
    void PushMessage(void * p1) {}
    // 0x100166a0 (75B)
    int PopMessage(void * p1) { return 0; }
    // 0x100166f0 (64B)
    int Attach(gbRenderEffect * p1) { return 0; }
    // 0x10016730 (33B)
    void Update(void) {}
    // 0x10016760 (42B)
    void Reset(float p1) {}
    // 0x10016790 (45B)
    void ShowNode(int p1) {}
    // 0x100167c0 (47B)
    void SetTimeScale(float p1) {}
    // 0x100167f0 (45B)
    void SetRenderPriority(int p1) {}
    // 0x10016820 (13B)
    void GetBoundSphere(gbSphere * p1) {}
    // 0x10016830 (10B)
    void EnableShadow(int p1) {}
    // 0x10016840 (17B)
    void SetBlend(int p1, float p2) {}
    // 0x10016860 (15B)
    int GetBlend(float * p1) { return 0; }
    // 0x10016870 (57B)
    void SetBlendRecursive(int p1, float p2) {}
    // 0x100168b0 (722B)
    void GetTotalBoundSphere(gbSphere * p1) {}
    // 0x10016b90 (142B)
    int GetAABBox(gbAABBox * p1) { return 0; }
};

