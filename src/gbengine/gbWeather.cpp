/**
 * gbengine.dll - gbWeather
 * Auto-generated from Ghidra decompilation
 * Functions: 13
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


/* ======== gbDropGroup ======== */

class gbDropGroup {
public:
    // 0x10031e40 (244B)
    gbDropGroup(int p1, void * p2, char * p3) {}
    // 0x10031f40 (146B)
    void Render(gbCamera * p1) {}
    // 0x10031fe0 (271B)
    void CreateUnit(float p1, gbCamera * p2) {}
    // 0x100328e0 (117B)
    gbDropGroup(gbDropGroup * p1) {}
};


/* ======== gbDropUnit ======== */

class gbDropUnit {
public:
    // 0x10032870 (32B)
    gbDropUnit(void) {}
};


/* ======== gbRain ======== */

class gbRain {
public:
    // 0x100320f0 (37B)
    gbRain(int p1, void * p2, char * p3) {}
    // 0x10032150 (156B)
    void Update(float p1) {}
    // 0x100321f0 (678B)
    void Draw(void) {}
    // 0x10032a50 (117B)
    gbRain(gbRain * p1) {}
};


/* ======== gbSnow ======== */

class gbSnow {
public:
    // 0x100324a0 (44B)
    gbSnow(int p1, void * p2, char * p3, float p4) {}
    // 0x100324d0 (219B)
    void Update(float p1) {}
    // 0x100325b0 (665B)
    void Draw(void) {}
    // 0x10032b30 (129B)
    gbSnow(gbSnow * p1) {}
};

