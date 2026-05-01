/**
 * gbengine.dll - gbTexture
 * Auto-generated from Ghidra decompilation
 * Functions: 20
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


/* ======== gbTexture ======== */

class gbTexture {
public:
    // 0x10004190 (12B)
    int IsInit(void) { return 0; }
    // 0x10020370 (37B)
    gbTexture(void) {}
    // 0x10020430 (85B)
    int GetInternalFormat(gbImage2D * p1) { return 0; }
    // 0x10020490 (269B)
    void LoadFromImage2D(gbImage2D * p1) {}
    // 0x100205a0 (443B)
    void LoadTexture(int p1) {}
    // 0x10020760 (102B)
    void CreateTexture(int p1, int p2, int p3, int p4) {}
    // 0x100207d0 (15B)
    void * GetBits(void) { return NULL; }
    // 0x100207e0 (53B)
    int GetPixelChannel(int p1, int p2, int p3) { return 0; }
    // 0x10020820 (52B)
    void UpdateTexture(int p1, int p2, gbImage2D * p3) {}
    // 0x10020860 (40B)
    void UpdateTexture(gbImage2D * p1) {}
};


/* ======== gbTextureArray ======== */

class gbTextureArray {
public:
    // 0x100041b0 (10B)
    gbTextureArray(void) {}
    // 0x100041c0 (18B)
    gbTextureArray(gbTexture * p1) {}
    // 0x100041e0 (25B)
    gbTextureArray(gbTexture * p1, gbTexture * p2) {}
    // 0x10004200 (16B)
    void SetTexture(gbTexture * p1) {}
};


/* ======== gbTexture_D3D ======== */

class gbTexture_D3D {
public:
    // 0x1001ba60 (29B)
    gbTexture_D3D(void) {}
    // 0x1001bd30 (356B)
    void CreateFromMemory(int p1, int p2, int p3, int p4, int p5, void * p6) {}
    // 0x1001bea0 (219B)
    void UpdateTexture(int p1, int p2, int p3, int p4, int p5, void * p6) {}
    // 0x1001bf80 (144B)
    int CreateForRenderTarget(int p1, int p2, int p3) { return 0; }
    // 0x1001c010 (344B)
    void CreateFromFileMemory(void * p1, int p2) {}
    // 0x1001c170 (144B)
    int GetByte(int p1, int p2) { return 0; }
};

