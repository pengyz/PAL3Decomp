/**
 * gbengine.dll - CPK
 * Auto-generated from Ghidra decompilation
 * Functions: 25
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


/* ======== CPK ======== */

class CPK {
public:
    // 0x10005dd0 (10B)
    unsigned long Tell(CPKFile * p1) { return 0; }
    // 0x10005de0 (10B)
    unsigned long GetSize(CPKFile * p1) { return 0; }
    // 0x10005df0 (14B)
    void Rewind(CPKFile * p1) {}
    // 0x1002c4b0 (211B)
    CPK(void) {}
    // 0x1002c5d0 (101B)
    void Reset(void) {}
    // 0x1002c640 (20B)
    void SetOpenMode(int p1) {}
    // 0x1002c660 (731B)
    int Load(char * p1) { return 0; }
    // 0x1002c940 (158B)
    int Unload(void) { return 0; }
    // 0x1002c9e0 (227B)
    int IsValidCPK(char * p1) { return 0; }
    // 0x1002cad0 (375B)
    int IsFileExist(char * p1) { return 0; }
    // 0x1002cc50 (1336B)
    CPKFile * Open(char * p1) { return NULL; }
    // 0x1002d1a0 (207B)
    int Close(CPKFile * p1) { return 0; }
    // 0x1002d270 (105B)
    int Read(void * p1, int p2, CPKFile * p3) { return 0; }
    // 0x1002d2e0 (106B)
    unsigned long Seek(CPKFile * p1, int p2, int p3) { return 0; }
    // 0x1002d350 (39B)
    int ReadChar(CPKFile * p1) { return 0; }
    // 0x1002d380 (101B)
    char * ReadLine(char * p1, int p2, CPKFile * p3) { return NULL; }
    // 0x1002d3f0 (744B)
    unsigned long LoadFile(void * p1, char * p2) { return 0; }
    // 0x1002d6e0 (72B)
    unsigned long Compress(void * p1, void * p2, int p3) { return 0; }
    // 0x1002d730 (79B)
    unsigned long DeCompress(void * p1, void * p2, int p3) { return 0; }
    // 0x1002d780 (191B)
    int GetFileSize(unsigned long * p1, unsigned long * p2, int p3) { return 0; }
    // 0x1002d840 (137B)
    int IsDir(int p1) { return 0; }
    // 0x1002d8d0 (291B)
    int GetTableIndex(char * p1) { return 0; }
    // 0x1002da00 (108B)
    int GetTableIndexFromCRC(int p1) { return 0; }
    // 0x1002da70 (22B)
    unsigned long GetAllocationGranularity(void) { return 0; }
};


/* ======== CPKFile ======== */

class CPKFile {
public:
    // 0x10005d80 (13B)
    CPKFile(void) {}
};

