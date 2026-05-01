/**
 * gbengine.dll - gbImage2D
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


/* ======== gbImage2D ======== */

class gbImage2D {
public:
    // 0x10004150 (44B)
    void * GetBits(int p1, int p2) { return NULL; }
    // 0x10004180 (16B)
    gbColorQuad * GetPalEntry(int p1) { return NULL; }
    // 0x1001e3e0 (47B)
    gbImage2D(void) {}
    // 0x1001e490 (1262B)
    int LoadImageFile(char * p1, int p2) { return 0; }
    // 0x1001e980 (162B)
    void ScaleTo(int p1, int p2) {}
    // 0x1001ea30 (131B)
    void * CreateImage(int p1, int p2, int p3) { return NULL; }
    // 0x1001efc0 (224B)
    void WriteTGAImage(char * p1) {}
    // 0x1001f5f0 (193B)
    void WriteJpegImage(char * p1, int p2) {}
    // 0x1001f6c0 (265B)
    int WriteJpegToBuffer(void * p1, int p2) { return 0; }
};


/* ======== gbImage2DInfo ======== */

class gbImage2DInfo {
public:
    // 0x1001e470 (22B)
    int IsPreferAlpha(void) { return 0; }
};

