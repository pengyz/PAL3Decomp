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

// gbCrc32Init, gbCrc32Compute - moved to gbMisc.cpp

// gbIntersectTriangle - moved to gbMath.cpp

// gbLogInfo, gbReportError, gbPopErrorBox, gbMemCopy - moved to gbMisc.cpp

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

// gbstrchr, gbstrindex, gbStrChr, gbStrRChr - moved to gbMisc.cpp

// 0x1002faf0 (108B)
int gbGetINIValue(char * p1, char * p2, char * p3)
{
    return 0;
}

// gbStrToLowCase, gbstricmp, gbIsMultiChar, gbIsMultiCharHead, gbIsMultiCharTail - moved to gbMisc.cpp

// gbUpdateCurTime, gbGetDeltaTime - moved to gbMisc.cpp

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

// ProfileInit, ProfileBegin, ProfileEnd, ProfileDumpOutputToFile - moved to gbMisc.cpp

