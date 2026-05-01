/**
 * gbengine.dll - gbChain
 * Auto-generated from Ghidra decompilation
 * Functions: 41
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


/* ======== gbBinaryTree ======== */

class gbBinaryTree {
public:
    // 0x10004690 (9B)
    gbBinaryTree(void) {}
    // 0x10004790 (9B)
    void SetRoot(gbBinaryTreeNode * p1) {}
};


/* ======== gbBinaryTreeNode ======== */

class gbBinaryTreeNode {
public:
    // 0x100046c0 (20B)
    gbBinaryTreeNode(void) {}
    // 0x100046e0 (33B)
    gbBinaryTreeNode(gbBinaryTreeNode * p1) {}
};


/* ======== gbChain1D ======== */

class gbChain1D {
public:
    // 0x10003a00 (11B)
    void ClearAllNodePtr(void) {}
    // 0x10003b00 (10B)
    gbChain1DNode * Iterate(void) { return NULL; }
    // 0x1002ea50 (13B)
    gbChain1D(void) {}
    // 0x1002ea80 (27B)
    void AddNodeOnHead(gbChain1DNode * p1) {}
    // 0x1002eaa0 (41B)
    void AddNode(gbChain1DNode * p1) {}
    // 0x1002ead0 (112B)
    void InsertBefore(gbChain1DNode * p1, gbChain1DNode * p2) {}
    // 0x1002eb40 (70B)
    void InsertAfter(gbChain1DNode * p1, gbChain1DNode * p2) {}
    // 0x1002eb90 (112B)
    void DelNodeFromChain(gbChain1DNode * p1) {}
    // 0x1002ec00 (31B)
    int IsContainNode(gbChain1DNode * p1) { return 0; }
};


/* ======== gbChain1DNode ======== */

class gbChain1DNode {
public:
    // 0x10003950 (9B)
    gbChain1DNode(void) {}
    // 0x10003960 (21B)
    gbChain1DNode(gbChain1DNode * p1) {}
};


/* ======== gbChain2D ======== */

class gbChain2D {
public:
    // 0x10003b10 (31B)
    gbChain2DNode * BeginIterate(int p1) { return NULL; }
    // 0x10003b30 (27B)
    gbChain2DNode * Iterate(void) { return NULL; }
    // 0x1002ec40 (13B)
    gbChain2D(void) {}
    // 0x1002ec70 (54B)
    void AddNode(gbChain2DNode * p1) {}
    // 0x1002ecb0 (119B)
    void DelNodeFromChain(gbChain2DNode * p1) {}
    // 0x1002ed30 (31B)
    int IsContainNode(gbChain2DNode * p1) { return 0; }
};


/* ======== gbChain2DNode ======== */

class gbChain2DNode {
public:
    // 0x10003a20 (9B)
    gbChain2DNode(void) {}
    // 0x10003a30 (27B)
    gbChain2DNode(gbChain2DNode * p1) {}
};


/* ======== gbNBTreeNode ======== */

class gbNBTreeNode {
public:
    // 0x10004460 (82B)
    gbNBTreeNode(void) {}
    // 0x10004520 (25B)
    void AddChildOnHead(gbNBTreeNode * p1) {}
    // 0x10004540 (25B)
    void AddChild(gbNBTreeNode * p1) {}
    // 0x10004560 (16B)
    void DelChildFromChain(gbNBTreeNode * p1) {}
    // 0x10004570 (21B)
    int IsChild(gbNBTreeNode * p1) { return 0; }
    // 0x100045a0 (10B)
    gbNBTreeNode * IterateChild(void) { return NULL; }
    // 0x100045b0 (63B)
    gbNBTreeNode(gbNBTreeNode * p1) {}
    // 0x100047a0 (16B)
    gbNBTreeNode * GetChild(int p1) { return NULL; }
};


/* ======== gbStaticChain ======== */

class gbStaticChain {
public:
    // 0x10014ad0 (15B)
    void * GetNode(int p1) { return NULL; }
    // 0x10014ae0 (16B)
    gbStaticChain(void) {}
    // 0x1002f810 (151B)
    void InitBuffer(int p1, int p2) {}
    // 0x1002f8b0 (10B)
    void ReleaseBuffer(void) {}
    // 0x1002f8c0 (56B)
    void * NewOneNode(void) { return NULL; }
    // 0x1002f900 (72B)
    void DelOneNode(void * p1) {}
    // 0x1002f960 (10B)
    void * Iterate(void) { return NULL; }
    // 0x1002f970 (26B)
    void * BeginReverseIterate(void) { return NULL; }
    // 0x1002f990 (9B)
    void * ReverseIterate(void) { return NULL; }
    // 0x1002f9b0 (19B)
    void * GetOldestNode(void) { return NULL; }
};

