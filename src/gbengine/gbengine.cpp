/**
 * gbengine.dll - gbengine
 * Auto-generated from Ghidra decompilation
 * Functions: 46
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


/* ======== Global Functions ======== */

// 0x10003df0 (65B)
int gbVertexBubble(gbVertexPool * p1, int p2, int p3, int p4)
{
    return 0;
}

// 0x10003e60 (105B)
int gbVertexBubble(void * p1)
{
    return 0;
}

// 0x100052f0 (16B)
int gbVolumeModifier(void)
{
    return 0;
}

// 0x10005300 (21B)
int gbVolumeModifier(void * p1)
{
    return 0;
}

// 0x10005700 (188B)
int gbVolModNode(void * p1)
{
    return 0;
}

// 0x10013040 (106B)
int gbVolModNode(void)
{
    return 0;
}

// 0x100135a0 (735B)
gbVisNode * gbLoadLightFile(char * p1)
{
    return NULL;
}

// 0x1001e0c0 (145B)
gbGfxManager * gbCreateGraphManager(void * p1)
{
    return NULL;
}

// 0x10022a00 (29B)
int gbConvertToSBC(void * p1, int p2, void * p3, int p4)
{
    return 0;
}

// 0x10027730 (55B)
void gbCrc32Init(void)
{
}

// 0x10027770 (106B)
unsigned int gbCrc32Compute(char * p1, int p2)
{
    return 0;
}

// 0x100277e0 (118B)
unsigned int gbCrc32Compute(char * p1)
{
    return 0;
}

// 0x10028f80 (1067B)
int gbIntersectTriangle(gbVec3D * p1, gbVec3D * p2, gbVec3D * p3, gbVec3D * p4, gbVec3D * p5, gbVec3D * p6)
{
    return 0;
}

// 0x1002e930 (72B)
void gbLogInfo(char * p1, int)
{
}

// 0x1002e980 (79B)
void gbReportError(char * p1, int)
{
}

// 0x1002e9d0 (79B)
void gbPopErrorBox(char * p1, int)
{
}

// 0x1002ed50 (34B)
void gbMemCopy(void * p1, void * p2, int p3)
{
}

// 0x1002f0b0 (179B)
void gbInitDispSetting(void)
{
}

// 0x1002f170 (580B)
int gbChangeDispMode(int p1, int p2, int p3)
{
    return 0;
}

// 0x1002f3c0 (11B)
void gbRestoreDispMode(void)
{
}

// 0x1002f3d0 (45B)
void gbPushDispMode(void)
{
}

// 0x1002f400 (88B)
void gbPopDispMode(void)
{
}

// 0x1002f460 (36B)
void gbGetCurDispMode(int * p1, int * p2, int * p3)
{
}

// 0x1002f490 (150B)
int gbExecProgram(char * p1)
{
    return 0;
}

// 0x1002f530 (193B)
void gbEnableSystemKeys(void * p1, int p2)
{
}

// 0x1002f670 (21B)
int gbGetOSUserName(char * p1, int p2)
{
    return 0;
}

// 0x1002f690 (332B)
int gbGetCPU_MHZ(void)
{
    return 0;
}

// 0x1002f9d0 (37B)
char * gbstrchr(char * p1, char p2)
{
    return NULL;
}

// 0x1002fa00 (85B)
char * gbstrindex(char * p1, int p2)
{
    return NULL;
}

// 0x1002fa60 (59B)
char * gbStrChr(char * p1, char * p2)
{
    return NULL;
}

// 0x1002faa0 (75B)
char * gbStrRChr(char * p1, char * p2)
{
    return NULL;
}

// 0x1002faf0 (108B)
int gbGetINIValue(char * p1, char * p2, char * p3)
{
    return 0;
}

// 0x1002fb60 (43B)
void gbStrToLowCase(char * p1, char * p2)
{
}

// 0x1002fb90 (206B)
int gbstricmp(char * p1, char * p2)
{
    return 0;
}

// 0x1002fc60 (83B)
int gbIsMultiChar(char * p1, int p2)
{
    return 0;
}

// 0x1002fcc0 (79B)
int gbIsMultiCharHead(char * p1, int p2)
{
    return 0;
}

// 0x1002fd10 (84B)
int gbIsMultiCharTail(char * p1, int p2)
{
    return 0;
}

// 0x1002fe90 (100B)
double gbUpdateCurTime(void)
{
    return 0.0f;
}

// 0x10030000 (50B)
float gbGetDeltaTime(void)
{
    return 0.0f;
}

// 0x10030040 (125B)
void gbGetRealWorldTime(void * p1)
{
}

// 0x10030f00 (70B)
char * gbVfgetdir(char * p1, char * p2, int p3)
{
    return NULL;
}

// 0x10030f50 (76B)
char * gbVfgetname(char * p1, char * p2, int p3)
{
    return NULL;
}

// 0x10031750 (46B)
void ProfileInit(void)
{
}

// 0x10031780 (258B)
void ProfileBegin(char * p1)
{
}

// 0x10031890 (277B)
void ProfileEnd(char * p1)
{
}

// 0x100319b0 (79B)
void ProfileDumpOutputToFile(char * p1)
{
}

