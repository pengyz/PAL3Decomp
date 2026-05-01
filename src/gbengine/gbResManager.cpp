/**
 * gbengine.dll - gbResManager
 * Auto-generated from Ghidra decompilation
 * Functions: 11
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


/* ======== gbRefObject ======== */

class gbRefObject {
public:
    // 0x100015e0 (16B)
    gbRefObject(void) {}
    // 0x100017c0 (21B)
    gbRefObject(gbRefObject * p1) {}
    // 0x1002f7f0 (20B)
    void Release(void) {}
};


/* ======== gbResManager ======== */

class gbResManager {
public:
    // 0x10020190 (13B)
    gbResManager(void) {}
    // 0x100201b0 (71B)
    gbResource * FindResByName(char * p1) { return NULL; }
    // 0x10020200 (116B)
    void AddResource(gbResource * p1) {}
    // 0x10020280 (147B)
    void DelResource(gbResource * p1) {}
    // 0x10020320 (72B)
    void CleanAllResource(void) {}
};


/* ======== gbResource ======== */

class gbResource {
public:
    // 0x10001840 (27B)
    gbResource(void) {}
    // 0x10001860 (51B)
    gbResource(gbResource * p1) {}
    // 0x10020040 (143B)
    void SetName(char * p1) {}
};

