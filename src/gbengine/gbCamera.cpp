/**
 * gbengine.dll - gbCamera
 * Auto-generated from Ghidra decompilation
 * Functions: 42
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


/* ======== gbCamControler ======== */

class gbCamControler {
public:
    // 0x10005b20 (9B)
    gbCamControler(void) {}
    // 0x10005b30 (45B)
    gbCamControler(gbCamControler * p1) {}
};


/* ======== gbCamQuakeControl ======== */

class gbCamQuakeControl {
public:
    // 0x10005c90 (29B)
    gbCamQuakeControl(void) {}
    // 0x10005cb0 (111B)
    gbCamQuakeControl(gbCamQuakeControl * p1) {}
    // 0x10021830 (149B)
    void Update(double p1) {}
};


/* ======== gbCamSpringControl ======== */

class gbCamSpringControl {
public:
    // 0x10005b90 (43B)
    gbCamSpringControl(void) {}
    // 0x10005bc0 (111B)
    gbCamSpringControl(gbCamSpringControl * p1) {}
    // 0x10021700 (295B)
    void Update(double p1) {}
};


/* ======== gbCamera ======== */

class gbCamera {
public:
    // 0x100058d0 (33B)
    void SetEyeLoc(float p1, float p2, float p3) {}
    // 0x10005900 (42B)
    void SetEyeDir(gbQuaternion * p1) {}
    // 0x10005930 (16B)
    void SetOrthoSize(float p1) {}
    // 0x10005940 (16B)
    void SetFOV(float p1) {}
    // 0x10005950 (17B)
    void SetZRange(float p1, float p2) {}
    // 0x100059c0 (24B)
    void RotateVector(gbVec3D * p1, gbVec3D * p2) {}
    // 0x10005a00 (14B)
    gbCamControler * GetCurControl(void) { return NULL; }
    // 0x10005a10 (14B)
    int IsCurCtrlDefault(void) { return 0; }
    // 0x100218d0 (157B)
    gbCamera(gbGfxManager * p1) {}
    // 0x10021970 (155B)
    void SetLookAt(gbVec3D * p1, gbVec3D * p2, gbVec3D * p3) {}
    // 0x10021a10 (97B)
    void GetViewSizeOnNearPlane(float * p1, float * p2) {}
    // 0x10021a80 (460B)
    void SetAsCurrent(int p1) {}
    // 0x10021c50 (39B)
    void SetDimention(int p1, int p2) {}
    // 0x10021c80 (253B)
    unsigned int ClipAABBox(gbVec3D * p1, gbVec3D * p2, int p3) { return 0; }
    // 0x10021d80 (381B)
    int ClipOBBox(gbOBBox * p1) { return 0; }
    // 0x10021f00 (82B)
    int ClipPoint(gbVec3D * p1) { return 0; }
    // 0x10021f60 (90B)
    int ClipSphere(gbVec3D * p1, float p2) { return 0; }
    // 0x10021fc0 (111B)
    void PointScrToWorld(float p1, float p2, gbVec3D * p3) {}
    // 0x10022030 (24B)
    void PointWorldToEye(gbVec3D * p1, gbVec3D * p2) {}
    // 0x10022050 (91B)
    void PointScrToEye(float p1, float p2, gbVec3D * p3) {}
    // 0x100220b0 (184B)
    void PointEyeToScr(gbVec3D * p1, float * p2, float * p3) {}
    // 0x10022170 (217B)
    void PointEyeToScr(gbVec3D * p1, gbVec3D * p2) {}
    // 0x10022250 (24B)
    void PointEyetoWorld(gbVec3D * p1, gbVec3D * p2) {}
    // 0x10022270 (80B)
    void PointWorldToScr(gbVec3D * p1, float * p2, float * p3) {}
    // 0x100222c0 (268B)
    void GetRayToScreen(float p1, float p2, gbRay * p3) {}
    // 0x100223d0 (109B)
    void GetViewPort(float * p1, float * p2, float * p3, float * p4) {}
    // 0x10022440 (67B)
    void PointDevToScr(int * p1, int * p2, float p3, float p4) {}
    // 0x10022490 (24B)
    void RotateVector(gbVec3D * p1, gbVec3D * p2, int p3) {}
    // 0x100224b0 (39B)
    void OffsetZBuffer(double p1) {}
    // 0x100224e0 (25B)
    void RecoverZBuffer(void) {}
    // 0x10022500 (130B)
    void MoveInEyeDir(float p1) {}
    // 0x10022590 (83B)
    void Update(double p1) {}
    // 0x100225f0 (54B)
    void AddControler(gbCamControler * p1, double p2) {}
    // 0x10022630 (171B)
    void PointWorld2Scr_NR(gbVec3D * p1, float * p2, float * p3) {}
};

