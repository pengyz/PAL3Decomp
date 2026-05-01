/**
 * gbengine.dll - gbPrintFont
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


/* ======== gbPrintFont ======== */

class gbPrintFont {
public:
    // 0x10004340 (90B)
    void SetFontColor(int p1, int p2, int p3) {}
    // 0x100043a0 (96B)
    void SetFontColor(int p1, int p2, int p3, int p4) {}
    // 0x10004400 (17B)
    void SetCurFontScale(float p1, float p2) {}
    // 0x10004420 (17B)
    void SetCurFontPitch(float p1, float p2) {}
    // 0x10004440 (10B)
    void SetCurFontDepth(float p1) {}
    // 0x10022a20 (147B)
    gbPrintFont(int p1, int p2, int p3) {}
    // 0x10022b00 (63B)
    int Init(void) { return 0; }
    // 0x10022b40 (36B)
    void Release(void) {}
    // 0x10022b70 (123B)
    void PrintCenterLine(char * p1, float p2, float p3, float p4, float p5) {}
    // 0x10022bf0 (285B)
    void PrintString(char * p1, float p2, float p3, float p4, float p5) {}
    // 0x10022d60 (472B)
    void Print3DString(char * p1, float p2, float p3, float p4) {}
};


/* ======== gbPrintFontMgr ======== */

class gbPrintFontMgr {
public:
    // 0x10004450 (10B)
    gbPrintFont * GetFont(int p1) { return NULL; }
    // 0x10022f40 (21B)
    gbPrintFontMgr(void) {}
    // 0x10022f60 (484B)
    int Init(gbGfxManager * p1) { return 0; }
    // 0x10023150 (94B)
    void Release(void) {}
    // 0x100231b0 (26B)
    void Flush(void) {}
    // 0x100231d0 (25B)
    void Flush3D(void) {}
};

