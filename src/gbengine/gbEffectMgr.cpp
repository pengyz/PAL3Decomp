/**
 * gbengine.dll - gbEffectMgr
 * Auto-generated from Ghidra decompilation
 * Functions: 10
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


/* ======== gbEffectMgr ======== */

class gbEffectMgr {
public:
    // 0x10004d20 (12B)
    gbEffectMgr(void) {}
    // 0x10004d30 (148B)
    gbEffectMgr(gbEffectMgr * p1) {}
    // 0x1001d1f0 (786B)
    void Init(gbGfxManager * p1) {}
    // 0x1001d510 (67B)
    void Release(void) {}
    // 0x1001d560 (50B)
    int OnLostDevice(void) { return 0; }
    // 0x1001d5a0 (50B)
    int OnResetDevice(void) { return 0; }
    // 0x1001d5e0 (232B)
    void * RegisterVertexFormat(char * p1, void * p2) { return NULL; }
    // 0x1001d6d0 (353B)
    gbRenderEffect * NewRenderEffect(char * p1, int p2) { return NULL; }
    // 0x1001d840 (107B)
    gbRenderEffect * NewTrivalEffect(int p1) { return NULL; }
    // 0x1001d8b0 (39B)
    gbRenderEffect * GetRenderEffect(int p1) { return NULL; }
};

