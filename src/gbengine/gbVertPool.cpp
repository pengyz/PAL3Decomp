/**
 * gbengine.dll - gbVertPool
 * Auto-generated from Ghidra decompilation
 * Functions: 27
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


/* ======== gbIndexBubble ======== */

class gbIndexBubble {
public:
    // 0x10003b50 (55B)
    gbIndexBubble(gbIndexPool * p1, int p2, int p3, int p4, int p5) {}
    // 0x10003b90 (24B)
    void Set(int p1, int p2, int p3) {}
    // 0x10003bb0 (17B)
    void SetRange(int p1, int p2) {}
    // 0x10003bd0 (69B)
    gbIndexBubble(gbIndexBubble * p1) {}
    // 0x10020900 (21B)
    void * Lock16(void) { return NULL; }
    // 0x10020920 (8B)
    void Unlock(void) {}
};


/* ======== gbIndexPool ======== */

class gbIndexPool {
public:
    // 0x10003cd0 (16B)
    int IsEmpty(void) { return 0; }
    // 0x10003cf0 (112B)
    gbIndexPool(gbIndexPool * p1) {}
    // 0x10020930 (182B)
    gbIndexPool(int p1, int p2, int p3) {}
    // 0x10020a50 (201B)
    gbIndexBubble * NewBubble(int p1, int p2) { return NULL; }
    // 0x10020b20 (216B)
    void DelBubble(gbIndexBubble * p1) {}
};


/* ======== gbVertPoolMgr ======== */

class gbVertPoolMgr {
public:
    // 0x100210c0 (216B)
    gbVertPoolMgr(gbGfxManager * p1, int p2, int p3, int p4, int p5) {}
    // 0x10021240 (47B)
    int OnLostDevice(void) { return 0; }
    // 0x10021270 (47B)
    int OnResetDevice(void) { return 0; }
    // 0x100212a0 (58B)
    int FindVertexPoolIndex(unsigned int * p1, int p2) { return 0; }
    // 0x100212e0 (182B)
    void * NewVertexBubble(int p1, int p2) { return NULL; }
    // 0x100213a0 (144B)
    void DelVertexBubble(void * p1) {}
    // 0x10021430 (185B)
    void * NewSrcVertBub(int p1, int p2) { return NULL; }
    // 0x100214f0 (145B)
    void DelSrcVertBub(void * p1) {}
    // 0x10021590 (135B)
    gbIndexBubble * NewIndexBubble(int p1, int p2) { return NULL; }
    // 0x10021620 (85B)
    void DelIndexBubble(gbIndexBubble * p1) {}
    // 0x10021680 (121B)
    gbDynVertBuf * GetDynVertBuf(int p1) { return NULL; }
};


/* ======== gbVertexPool ======== */

class gbVertexPool {
public:
    // 0x10003fb0 (16B)
    int IsEmpty(void) { return 0; }
    // 0x10003fc0 (118B)
    gbVertexPool(gbVertexPool * p1) {}
    // 0x10020d90 (282B)
    gbVertexPool(int p1, int p2, int p3) {}
    // 0x10020f10 (202B)
    void * NewBubble(int p1) { return NULL; }
    // 0x10020fe0 (216B)
    void DelBubble(void * p1) {}
};

