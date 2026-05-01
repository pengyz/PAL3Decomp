/**
 * gbengine.dll - gbMesh
 * Auto-generated from Ghidra decompilation
 * Functions: 22
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


/* ======== gbBaseMesh ======== */

class gbBaseMesh {
public:
    // 0x100047c0 (21B)
    void * GetMeshSection(int p1) { return NULL; }
    // 0x100047f0 (10B)
    void SetCurTime(float p1) {}
    // 0x10004810 (152B)
    gbBaseMesh(gbBaseMesh * p1) {}
    // 0x1000e860 (191B)
    gbBaseMesh(gbGfxManager * p1) {}
    // 0x1000eac0 (55B)
    int GetNumFaces(void) { return 0; }
    // 0x1000eb60 (120B)
    void SetTexture(int p1, gbTexture * p2) {}
    // 0x1000ebe0 (42B)
    void ReplaceTexture(char * p1) {}
    // 0x1000ec10 (13B)
    void ReplaceTexture(gbTexture * p1) {}
};


/* ======== gbDynVertBuf ======== */

class gbDynVertBuf {
public:
    // 0x10004260 (11B)
    float * GetUV(int p1) { return NULL; }
    // 0x10004270 (106B)
    gbDynVertBuf(gbDynVertBuf * p1) {}
    // 0x1001c790 (56B)
    gbDynVertBuf(int p1, int p2) {}
    // 0x1001c7e0 (126B)
    void StepVertexPtr(void) {}
    // 0x1001c860 (578B)
    void RenderUIQuad(void * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4) {}
    // 0x1001cab0 (350B)
    void RenderGeomQuad(void * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4) {}
    // 0x1001cc10 (313B)
    void RenderGeomQuadViaStrip(void * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4, int p5) {}
    // 0x1001cd50 (242B)
    void RenderGeomQuadViaStrip(void * p1, int p2, gbRenderEffect * p3, gbTextureArray * p4) {}
    // 0x1001ce50 (147B)
    void RenderLineStrip(gbColorQuad p2, gbVec3D * p3, int p4, gbRenderEffect * p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12) {}
};


/* ======== gbStaticMesh ======== */

class gbStaticMesh {
public:
    // 0x10011950 (182B)
    gbStaticMesh(gbStaticMesh * p1) {}
    // 0x10015630 (42B)
    gbStaticMesh(gbGfxManager * p1) {}
    // 0x10015ca0 (105B)
    void DrawSubSet(int p1, void * p2) {}
    // 0x10015e80 (1285B)
    int LoadFromStream(gbVFile * p1, int p2, void * p3) { return 0; }
    // 0x10016390 (501B)
    void ComputeShadowVolume(void) {}
};

