/**
 * gbengine.dll - gbGfxManager
 * Auto-generated from Ghidra decompilation
 * Functions: 25
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


/* ======== gbGfxManager ======== */

class gbGfxManager {
public:
    // 0x10004ea0 (13B)
    void SetSceneGraph(gbSceneGraph * p1) {}
    // 0x10004ed0 (14B)
    gbMatrixStack * GetMatrixStack(int p1) { return NULL; }
    // 0x10004ee0 (16B)
    gbPrintFont * GetPrintFont(int p1) { return NULL; }
    // 0x10004f50 (20B)
    void * GetLight(int p1) { return NULL; }
    // 0x10004f70 (14B)
    int IsLightEnable(int p1) { return 0; }
    // 0x10004f90 (35B)
    void SetAmbientLight(gbColorFlt * p1) {}
    // 0x10004fc0 (39B)
    gbColorFlt GetAmbientLight(int p1) { gbColorFlt r = {0}; return r; }
    // 0x10004ff0 (34B)
    void EnableEmissive(int p1) {}
    // 0x10005020 (13B)
    void SetEmissiveFactor(float p1) {}
    // 0x1001d910 (394B)
    gbGfxManager(int * p1, void * p2) {}
    // 0x1001dac0 (34B)
    double GetDeltaTime(void) { return 0.0f; }
    // 0x1001daf0 (27B)
    unsigned int GetDeltaTick(void) { return 0; }
    // 0x1001db10 (222B)
    int BeginScene(void) { return 0; }
    // 0x1001df40 (37B)
    void GetTMMatrix(int p1, gbMatrix4 * p2) {}
    // 0x1001e070 (24B)
    void GetViewport(void * p1) {}
    // 0x1001e090 (35B)
    void SetClearParam(void * p1) {}
    // 0x1001e160 (189B)
    gbBaseMesh * NewMesh(char * p1, int p2) { return NULL; }
    // 0x1001e220 (158B)
    int ClipBoundVolume(gbAABBox * p1) { return 0; }
    // 0x1001e2c0 (36B)
    void OffsetZBuffer(int p1) {}
    // 0x1001e2f0 (13B)
    void SetWireMode(int p1) {}
    // 0x1001e300 (38B)
    void SetFog(void * p1) {}
    // 0x1001e330 (55B)
    gbMatrix4 * GetWorldMatrix(void) { return NULL; }
    // 0x1001e380 (19B)
    void IdentityWorldMatrix(void) {}
    // 0x1001e3a0 (43B)
    void SetCameraMatrix(gbMatrix4 * p1, gbMatrix4 * p2) {}
};


/* ======== gbGfxManager_D3D ======== */

class gbGfxManager_D3D {
public:
    // 0x1001b410 (162B)
    void SetTexture(gbTextureArray * p1) {}
};

