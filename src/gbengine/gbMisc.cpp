/**
 * gbengine.dll - gbMisc
 * Auto-generated from Ghidra decompilation
 * Functions: 28
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


/* ======== BEZIER ======== */

class BEZIER {
public:
    // 0x100241c0 (25B)
    void computerCoefficient(void) {}
    // 0x100241e0 (50B)
    BEZIER(gbVec3D * p1) {}
    // 0x10024220 (47B)
    BEZIER(void) {}
    // 0x10024250 (27B)
    void SetControlPt(gbVec3D * p1) {}
    // 0x10024270 (233B)
    gbVec3D getInterpolatePoint(float p1) { gbVec3D r = {0}; return r; }
    // 0x10024360 (363B)
    gbVec3D getTangentVector(float p1) { gbVec3D r = {0}; return r; }
};


/* ======== gbColorFlt (defined in header) ======== */


/* ======== gbColorQuad (defined in header) ======== */


/* ======== gbNameVarBuf ======== */

class gbNameVarBuf {
public:
    // 0x1002ed80 (25B)
    gbNameVarBuf(void) {}
    // 0x1002edd0 (304B)
    void RegVariant(int p1, int p2, int p3) {}
    // 0x1002ef00 (44B)
    int IsVarExist(int p1) { return 0; }
    // 0x1002ef30 (84B)
    void GetVariant(int p1, void * p2) {}
    // 0x1002ef90 (87B)
    void SetVariant(int p1, void * p2) {}
    // 0x1002eff0 (92B)
    void * LockVariant(int p1, int * p2) { return NULL; }
    // 0x1002f050 (8B)
    void UnlockVariant(void) {}
};


/* ======== gbPixelFormat (defined in header) ======== */


/* ======== gbTimeCounter ======== */

class gbTimeCounter {
public:
    // 0x1002fd70 (283B)
    void gbTimeCounterInit(void) {}
    // 0x1002ff00 (97B)
    void On(void) {}
    // 0x1002ff70 (135B)
    double Off(void) { return 0.0f; }
};


/* ======== gbUIRect (defined in header) ======== */

