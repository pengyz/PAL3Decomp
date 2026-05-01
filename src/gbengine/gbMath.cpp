/**
 * gbengine.dll - gbMath
 * Auto-generated from Ghidra decompilation
 * Functions: 105
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


/* ======== gbAABBox (defined in header) ======== */


/* ======== gbMatrix4 (defined in header) ======== */


/* ======== gbMatrixStack ======== */

class gbMatrixStack {
public:
    // 0x10026fe0 (149B)
    gbMatrixStack(int p1) {}
    // 0x10027090 (41B)
    void Push(void) {}
    // 0x100270c0 (15B)
    void Pop(void) {}
    // 0x100270d0 (51B)
    void LoadIdentity(void) {}
    // 0x10027110 (37B)
    void LoadMatrix(gbMatrix4 * p1) {}
    // 0x10027140 (145B)
    void MultMatrix(gbMatrix4 * p1) {}
    // 0x100271e0 (276B)
    void Rotate(float p1, gbVec3D * p2) {}
    // 0x10027300 (221B)
    void Rotate(gbQuaternion * p1) {}
    // 0x100273e0 (104B)
    void Translate(gbVec3D * p1) {}
    // 0x10027450 (96B)
    void Scale(gbVec3D * p1) {}
    // 0x100274b0 (112B)
    void Translate(float p1, float p2, float p3) {}
    // 0x10027520 (108B)
    void Scale(float p1, float p2, float p3) {}
    // 0x10027590 (11B)
    gbMatrix4 * GetTop(void) { return NULL; }
};


/* ======== gbOBBox (defined in header) ======== */


/* ======== gbPlane (defined in header) ======== */


/* ======== gbQuaternion (defined in header) ======== */


/* ======== gbRay (defined in header) ======== */


/* ======== gbRotMatrix (defined in header) ======== */


/* ======== gbSphere (defined in header) ======== */


/* ======== gbVec3D (defined in header) ======== */

