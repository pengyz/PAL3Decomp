/**
 * gbengine.dll - CIniFile
 * Auto-generated from Ghidra decompilation
 * Functions: 16
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


/* ======== CIniFile ======== */

class CIniFile {
public:
    // 0x100311b0 (16B)
    CIniFile(void) {}
    // 0x10031210 (102B)
    int OpenFileRead(char * p1) { return 0; }
    // 0x10031280 (106B)
    int OpenFileWrite(char * p1) { return 0; }
    // 0x100312f0 (32B)
    void CloseFile(void) {}
    // 0x10031310 (195B)
    int ReadSection(char * p1) { return 0; }
    // 0x100313e0 (370B)
    int ReadLine(char * p1, char * p2, int p3) { return 0; }
    // 0x10031560 (75B)
    int ReadLine(char * p1, int * p2) { return 0; }
    // 0x100315b0 (75B)
    int ReadLine(char * p1, float * p2) { return 0; }
    // 0x10031600 (75B)
    int ReadLine(char * p1, double * p2) { return 0; }
    // 0x10031650 (19B)
    void ReadStart(void) {}
    // 0x10031670 (27B)
    void WriteSection(char * p1) {}
    // 0x10031690 (32B)
    void WriteLine(char * p1, char * p2) {}
    // 0x100316b0 (32B)
    void WriteLine(char * p1, int p2) {}
    // 0x100316d0 (37B)
    void WriteLine(char * p1, float p2) {}
    // 0x10031700 (37B)
    void WriteLine(char * p1, double p2) {}
    // 0x10031730 (20B)
    void WriteLineSeperator(void) {}
};

