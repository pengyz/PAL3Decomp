/**
 * gbengine.dll - gbGeomNode
 * Auto-generated from Ghidra decompilation
 * Functions: 23
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


/* ======== gbGeomNode ======== */

class gbGeomNode {
public:
    // 0x1000c9e0 (13B)
    void EnableBlade(int p1) {}
    // 0x1000c9f0 (356B)
    gbGeomNode(gbGeomNode * p1) {}
    // 0x1000fc10 (195B)
    gbGeomNode(void) {}
    // 0x1000fde0 (214B)
    gbOBBox * GetOBBox(gbOBBox * p1) { return NULL; }
    // 0x1000fec0 (929B)
    gbOBBox * GetTotalOBBox(gbOBBox * p1) { return NULL; }
    // 0x100102c0 (1478B)
    int LoadFromFile(char * p1, char * p2, void * p3) { return 0; }
    // 0x100108b0 (852B)
    int LoadCVDFile(char * p1) { return 0; }
    // 0x10010cd0 (483B)
    void LoadCVDFromStream(gbVFile * p1, float p2) {}
    // 0x10010ec0 (619B)
    void Update(void) {}
    // 0x10011130 (754B)
    void AttachSelf(gbRenderEffect * p1) {}
    // 0x10011440 (32B)
    int Attach(gbRenderEffect * p1) { return 0; }
    // 0x10011460 (184B)
    void Render(void * p1) {}
    // 0x10011520 (181B)
    void RenderShadowVolume(void * p1) {}
    // 0x100115e0 (110B)
    void Reset(float p1) {}
    // 0x10011650 (228B)
    void GetBoundSphere(gbSphere * p1) {}
    // 0x10011740 (63B)
    void SetAnimLoop(int p1) {}
    // 0x10011780 (34B)
    void EnableShadow(int p1) {}
    // 0x100117b0 (39B)
    int GetAABBox(gbAABBox * p1) { return 0; }
    // 0x100117e0 (26B)
    void SetBladeTime(float p1) {}
    // 0x10011800 (26B)
    void SetBladeTimeScale(float p1) {}
    // 0x10011820 (23B)
    gbVec3D * GetLastBladePos(gbGeomNode * p1) { return NULL; }
    // 0x10011840 (58B)
    void ReplaceTexture(char * p1) {}
    // 0x10011880 (23B)
    void ReplaceTexture(gbTexture * p1) {}
};

