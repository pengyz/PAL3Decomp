/**
 * gbengine.dll - gbParticle
 * Auto-generated from Ghidra decompilation
 * Functions: 38
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


/* ======== gbEmitterData ======== */

class gbEmitterData {
public:
    // 0x1000d360 (13B)
    gbEmitterData(void) {}
};


/* ======== gbPartEmitter ======== */

class gbPartEmitter {
public:
    // 0x1000d3f0 (520B)
    gbPartEmitter(void) {}
    // 0x10029cf0 (1486B)
    void LoadFromFile(gbVFile * p1) {}
    // 0x1002a2c0 (320B)
    int ComputeEmitterData(gbEmitterData * p1, double p2, double p3) { return 0; }
    // 0x1002a400 (390B)
    void ComputeParticleInitPos(gbParticleUnit * p1) {}
    // 0x1002a590 (137B)
    void ComputeParticleInitVel(gbEmitterData * p1, gbParticleUnit * p2) {}
    // 0x1002c3c0 (18B)
    void SetLoopEmit(int p1) {}
};


/* ======== gbPartGroupParam ======== */

class gbPartGroupParam {
public:
    // 0x1002a620 (375B)
    gbPartGroupParam(void) {}
    // 0x1002a7f0 (1414B)
    void LoadFromFile(gbVFile * p1) {}
    // 0x1002ad80 (323B)
    void ComputeAirResist(gbParticleUnit * p1, float p2) {}
    // 0x1002aed0 (239B)
    void ComputeParticleParam(gbParticleUnit * p1, float p2, float p3) {}
    // 0x1002afc0 (172B)
    void InitParticleParam(gbParticleUnit * p1) {}
};


/* ======== gbPartParamControl ======== */

class gbPartParamControl {
public:
    // 0x1000cd90 (93B)
    gbPartParamControl(void) {}
    // 0x100298e0 (194B)
    void LoadFromFile(gbVFile * p1) {}
    // 0x100299b0 (252B)
    void GetValue(float * p1, float p2) {}
};


/* ======== gbParticleEffect ======== */

class gbParticleEffect {
public:
    // 0x1000da30 (13B)
    void SetSpaceScale(float p1) {}
    // 0x1000da40 (541B)
    gbParticleEffect(gbParticleEffect * p1) {}
    // 0x1002baf0 (175B)
    gbParticleEffect(void) {}
    // 0x1002bca0 (809B)
    int LoadFromFile(char * p1) { return 0; }
    // 0x1002bfd0 (157B)
    void Reset(float p1) {}
    // 0x1002c070 (92B)
    void Update(void) {}
    // 0x1002c0d0 (129B)
    void UpdateInternal(void) {}
    // 0x1002c160 (346B)
    int Attach(gbRenderEffect * p1) { return 0; }
    // 0x1002c2c0 (28B)
    void GetBoundSphere(gbSphere * p1) {}
    // 0x1002c2e0 (118B)
    void Render(void * p1) {}
    // 0x1002c360 (21B)
    gbParticleGroup * GetParticleGroup(int p1) { return NULL; }
    // 0x1002c380 (27B)
    gbPartGroupParam * GetGroupParam(int p1) { return NULL; }
    // 0x1002c3a0 (30B)
    gbPartEmitter * GetEmitter(int p1) { return NULL; }
};


/* ======== gbParticleGroup ======== */

class gbParticleGroup {
public:
    // 0x1002b070 (20B)
    gbParticleGroup(void) {}
    // 0x1002b0b0 (294B)
    void LoadFromFile(gbVFile * p1, gbParticleEffect * p2) {}
    // 0x1002b1e0 (70B)
    void Reset(void) {}
    // 0x1002b230 (105B)
    gbParticleUnit * GetOldestParticle(void) { return NULL; }
    // 0x1002b2a0 (747B)
    gbParticleUnit * CreateOneParticle(gbEmitterData * p1) { return NULL; }
    // 0x1002b590 (264B)
    int UpdateOneParticle(gbParticleUnit * p1, double p2) { return 0; }
    // 0x1002b6a0 (204B)
    void Update(double p1) {}
    // 0x1002b770 (885B)
    void Render(void) {}
};


/* ======== gbParticleUnit ======== */

class gbParticleUnit {
public:
    // 0x1000cee0 (32B)
    gbParticleUnit(void) {}
    // 0x1000cf00 (144B)
    gbParticleUnit(gbParticleUnit * p1) {}
};

