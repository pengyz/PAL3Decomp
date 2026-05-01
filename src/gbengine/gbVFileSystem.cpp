/**
 * gbengine.dll - gbVFileSystem
 * Auto-generated from Ghidra decompilation
 * Functions: 27
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


/* ======== gbVFile ======== */

class gbVFile {
public:
    // 0x10005e50 (17B)
    gbVFile(void) {}
};


/* ======== gbVFile1 ======== */

class gbVFile1 {
public:
    // 0x10030130 (77B)
    char * GetFileName(char * p1, int p2) { return NULL; }
    // 0x10030180 (73B)
    char * GetDir(char * p1, int p2) { return NULL; }
    // 0x100301d0 (99B)
    char * GetTitle(char * p1, int p2) { return NULL; }
};


/* ======== gbVFileSystem ======== */

class gbVFileSystem {
public:
    // 0x10005e90 (13B)
    void DelFileEntry(gbVFile * p1) {}
    // 0x10005ea0 (28B)
    gbVFileSystem(void) {}
    // 0x10030240 (611B)
    int Init(char * p1) { return 0; }
    // 0x100304b0 (92B)
    void Release(void) {}
    // 0x10030510 (36B)
    gbVFile * NewFileEntry(void) { return NULL; }
    // 0x10030540 (604B)
    gbVFile * OpenFile(char * p1, int p2) { return NULL; }
    // 0x100307a0 (111B)
    void CloseFile(gbVFile * p1) {}
    // 0x10030810 (168B)
    void Read(void * p1, int p2, gbVFile * p3) {}
    // 0x100308c0 (194B)
    void Write(void * p1, int p2, gbVFile * p3) {}
    // 0x10030990 (104B)
    int ReadChar(gbVFile * p1) { return 0; }
    // 0x10030a00 (285B)
    void Seek(gbVFile * p1, long p2, int p3) {}
    // 0x10030b20 (83B)
    void Rewind(gbVFile * p1) {}
    // 0x10030b80 (87B)
    long TellPos(gbVFile * p1) { return 0; }
    // 0x10030be0 (179B)
    long GetFileSize(gbVFile * p1) { return 0; }
    // 0x10030ca0 (281B)
    int FileExistNum(char * p1) { return 0; }
    // 0x10030dc0 (193B)
    char * ReadLine(char * p1, int p2, gbVFile * p3) { return NULL; }
    // 0x10030e90 (103B)
    int FindItem(char * p1) { return 0; }
};


/* ======== gbVTextFile ======== */

class gbVTextFile {
public:
    // 0x10030fa0 (13B)
    gbVTextFile(void) {}
    // 0x10030fb0 (36B)
    gbVTextFile(char * p1) {}
    // 0x10031050 (142B)
    void Open(char * p1) {}
    // 0x100310e0 (135B)
    void Close(void) {}
    // 0x10031170 (23B)
    void Rewind(void) {}
    // 0x10031190 (25B)
    char * ReadLine(void) { return NULL; }
};

