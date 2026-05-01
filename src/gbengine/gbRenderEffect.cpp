/**
 * gbengine.dll - gbRenderEffect
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


/* ======== gbRenderEffect ======== */

class gbRenderEffect {
public:
    // 0x10004be0 (10B)
    void SetDeclHandle(void * p1) {}
    // 0x10004bf0 (92B)
    gbRenderEffect(gbRenderEffect * p1) {}
    // 0x1001cef0 (139B)
    gbRenderEffect(void * p1, int p2) {}
    // 0x1001cfe0 (32B)
    int Compare(gbRenderEffect * p1) { return 0; }
    // 0x1001d000 (119B)
    int Validate(void) { return 0; }
    // 0x1001d080 (26B)
    int Begin(void) { return 0; }
    // 0x1001d0a0 (52B)
    void Pass(int p1) {}
    // 0x1001d0e0 (20B)
    void End(void) {}
    // 0x1001d100 (72B)
    void Apply(void) {}
    // 0x1001d150 (30B)
    void GetVariant(int p1, void * p2) {}
    // 0x1001d170 (30B)
    void SetVariant(int p1, void * p2) {}
    // 0x1001d190 (40B)
    void GetVariant(char * p1, void * p2) {}
    // 0x1001d1c0 (40B)
    void SetVariant(char * p1, void * p2) {}
};

