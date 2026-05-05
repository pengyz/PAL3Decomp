"""
IDAPython: 批量导入 PDB 结构体定义 (57 个)
自动生成 by gen_ida_struct_import.py
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
import idautils
import idc
import traceback
import os

LOG_FILE = r"D:\workspace\project-x\tools\fulldump\ida_struct_import_log.txt"
TEXT_START = 0x00401000
TEXT_END = 0x00558000

STRUCT_HEADER = r"""
struct gbResManager;
struct gbPixelFormat;
struct gbImage2D;
struct gbPrintFont;
struct gbEmitterShape;
struct gbPartParamControl;
struct gbPartEmitter;
struct gbRefObject;
struct CPK;
struct gbBinkVideo;
struct gbMatrixStack;
struct gbChain1D;
struct gbIndexPool;
struct gbVertPoolMgr;
struct gbPrintFontMgr;
struct gbActorMgr;
struct gbActorDef;
struct CD3DEnumeration;
struct CD3DSettings;
struct gbGfxManager_D3D;
struct gbTexture_D3D;
struct gbNBTreeNode;
struct gbCursorRes;
struct gbGfxManager;
struct gbCamera;
struct gbSound2DNode;
struct gbResource;
struct gbMeshSection;
struct gbRenderEffect;
struct gbChain1DNode;
struct gbVisNode;
struct gbLightObj;
struct gbParticleGroup;
struct gbAudioManager;
struct gbActor;
struct gbVFileSystem;
struct gbVertexBubble;
struct gbDropGroup;
struct gbSnow;
struct gbKeyControler;
struct gbVFile1;
struct gbParticleEffect;
struct gbSoundData;
struct gbIndexBubble;
struct gbGeomNode;
struct gbTexture;
struct gbEffectMgr;
struct gbVertexPool;
struct gbBaseMesh;
struct gbAnimScript;
struct gbDynVertBuf;
struct gbCamControler;
struct gbVolModNode;
struct gbSound3DNode;
struct gbSceneGraph;

struct gbResManager {
    gbDynArray<gbResource *> AllResPt;
};

struct gbPixelFormat {
    char Type[4]; // gbPixelFmtType
    int Bpp;
    void * Pal;
    unsigned int r_mask;
    unsigned int g_mask;
    unsigned int b_mask;
    unsigned int a_mask;
    unsigned int r_shift;
    unsigned int g_shift;
    unsigned int b_shift;
    unsigned int a_shift;
};

struct gbImage2D {
    char ImgInfo[128]; // gbImage2DInfo
    int Width;
    int Height;
    gbPixelFormat PixelFmt;
    int BitCount;
    unsigned char * pBits;
    void * pPalette;
    int numPalEntry;
    char ColorKey[4]; // gbColorQuad
};

struct gbPrintFont {
    char _gap_0[4];
    void * ptInfo;
    void * pSortInfo;
    int maxInfo;
    int numInfo;
    void * pt3DInfo;
    int num3DInfo;
    int max3DInfo;
    unsigned char * strBuffer;
    int maxStrBuffer;
    int curStrLoc;
    char curColor[4]; // gbColorQuad
    float ScaleX;
    float ScaleY;
    float PitchX;
    float PitchY;
    float ZValue;
    gbRenderEffect * pEffect[2];
};

struct gbEmitterShape {
    void * intervec;
    float * disarray;
    int m_iVecnum;
    char curmat[64]; // gbMatrix4
};

struct gbPartParamControl {
    int nCurve;
    int nCtrlPt;
    char Name[64];
    char Descript[128];
    char MinPt[12]; // gbVec3D
    char MaxPt[12]; // gbVec3D
    char CtrlPt[720]; // gbVec3D[3][20]
    char Segment[3636]; // gbVec3D[3][101]
};

struct gbPartEmitter {
    char name[64];
    char relative_position[12]; // gbVec3D
    char emission_scope[12]; // gbVec3D
    char cs_name[64];
    int emitter_shape;
    float cyclelen_start;
    float cyclelen_end;
    int cycle_loop;
    int lighton;
    char square[24]; // gbEmitterSquare
    char sphere[8]; // gbEmitterSphere
    gbEmitterShape shape;
    float m_fSpeedMulti;
    float m_fSizeMulti;
    gbPartParamControl DirectionCtrl;
    gbPartParamControl RandomVelCtrl;
    gbPartParamControl EmitRateCtrl;
    gbPartParamControl UnitLifeCtrl;
    gbPartParamControl UnitScaleCtrl;
    gbPartParamControl UnitRotCtrl;
};

struct gbRefObject {
    char _gap_0[4];
    int RefCount;
};

struct CPK {
    unsigned int m_dwAllocGranularity;
    char m_eMode[4]; // ECPKMode
    char m_CPKHeader[128]; // tagCPKHeader
    char m_CPKTable[917504]; // tagCPKTable[32768]
    void * m_pgbVFile[8];
    unsigned char m_bLoaded;
    unsigned int m_dwCPKHandle;
    unsigned int m_dwCPKMappingHandle;
    char m_szCPKFileName[260];
    int m_nOpenedFileNum;
};

struct gbBinkVideo {
    char _gap_0[4];
    char m_pos[8]; // tagPOINT
    void * m_hBink;
    CPK m_Cpk;
    CPK m_Cpk2;
};

struct gbMatrixStack {
    void * pMatBuf;
    int MaxVol;
    int CurPos;
    int ValidFlag;
};

struct gbChain1D {
    gbChain1DNode * m_Head;
    gbChain1DNode * m_Tail;
    int m_numNode;
    gbChain1DNode * m_Cur;
};

struct gbIndexPool {
    char _gap_0[8];
    char Type[4]; // gbPoolType
    int EleSize;
    void * pMemBuf;
    int TotalIndex;
    gbChain1D FreeIndexBub;
    gbChain1D UsedIndexBub;
};

struct gbVertPoolMgr {
    gbChain1D StaticPool[32];
    unsigned int StaticPoolFVF[32];
    gbChain1D StaticIndex;
    gbDynVertBuf * pDynPool[32];
    unsigned int DynPoolFVF[32];
    gbChain1D ReadOnlyPool[32];
    unsigned int ReadOnlyPoolFVF[32];
    int VertPoolSize;
    int IndexPoolSize;
    int DynVertPoolSize;
    int ReadOnlyPoolSize;
    gbGfxManager * pGfxMgr;
};

struct gbPrintFontMgr {
    gbPrintFont * pAllFont[5];
};

struct gbActorMgr {
    gbResManager AllActorDef;
};

struct gbActorDef {
    char _gap_0[24];
    void * m_ActionCache[16];
    int m_nFilledSlot;
};

struct CD3DEnumeration {
    void * m_pD3D;
    CArrayList * m_pAdapterInfoList;
    void * ConfirmDeviceCallback;
    unsigned int AppMinFullscreenWidth;
    unsigned int AppMinFullscreenHeight;
    unsigned int AppMinColorChannelBits;
    unsigned int AppMinAlphaChannelBits;
    unsigned int AppMinDepthBits;
    unsigned int AppMinStencilBits;
    unsigned char AppUsesDepthBuffer;
    unsigned char AppUsesMixedVP;
    unsigned char AppRequiresWindowed;
    unsigned char AppRequiresFullscreen;
    CArrayList * m_pAllowedAdapterFormatList;
};

struct CD3DSettings {
    unsigned char IsWindowed;
    void * pWindowed_AdapterInfo;
    void * pWindowed_DeviceInfo;
    void * pWindowed_DeviceCombo;
    char Windowed_DisplayMode[16]; // _D3DDISPLAYMODE
    char Windowed_DepthStencilBufferFormat[4]; // _D3DFORMAT
    char Windowed_MultisampleType[4]; // _D3DMULTISAMPLE_TYPE
    unsigned int Windowed_MultisampleQuality;
    char Windowed_VertexProcessingType[4]; // VertexProcessingType
    unsigned int Windowed_PresentInterval;
    int Windowed_Width;
    int Windowed_Height;
    void * pFullscreen_AdapterInfo;
    void * pFullscreen_DeviceInfo;
    void * pFullscreen_DeviceCombo;
    char Fullscreen_DisplayMode[16]; // _D3DDISPLAYMODE
    char Fullscreen_DepthStencilBufferFormat[4]; // _D3DFORMAT
    char Fullscreen_MultisampleType[4]; // _D3DMULTISAMPLE_TYPE
    unsigned int Fullscreen_MultisampleQuality;
    char Fullscreen_VertexProcessingType[4]; // VertexProcessingType
    unsigned int Fullscreen_PresentInterval;
};

struct gbGfxManager_D3D {
    char _gap_0[1520];
    CD3DEnumeration m_d3dEnumeration;
    int m_bWindowed;
    char m_rcWindowClient[16]; // tagRECT
    char m_rcWindowBounds[16]; // tagRECT
    unsigned int m_dwWindowStyle;
    void * m_hWnd;
    unsigned char m_bMinimized;
    unsigned char m_bMaximized;
    unsigned char m_bClipCursorWhenFullscreen;
    unsigned char m_bShowCursorWhenFullscreen;
    unsigned char m_bActive;
    unsigned int m_dwCreateFlags;
    char m_DriverBug[4]; // D3DDriverBug
    gbResManager m_CursorMgr;
    gbCursorRes * m_pActiveCursor;
    int m_bShowCursor;
    int m_bSoftVPMode;
    CD3DSettings m_d3dSettings;
    char m_d3dpp[56]; // _D3DPRESENT_PARAMETERS_
    void * m_pD3D;
    void * m_pd3dDevice;
    char m_d3dCaps[304]; // _D3DCAPS9
    char m_d3dsdBackBuffer[32]; // _D3DSURFACE_DESC
    char m_strDeviceStats[90];
    long m_ErrorCode;
    int m_bDeviceLost;
    void * m_pBackBuffer;
    int m_DXTSupported[5];
    void * m_pCacheVB;
    void * m_pCacheIB;
};

struct gbTexture_D3D {
    char _gap_0[84];
    void * pTex;
    void * pDS;
    unsigned int m_ImgFormat;
};

struct gbNBTreeNode {
    char _gap_0[8];
    gbNBTreeNode * pFather;
    gbChain1D Children;
};

struct gbCursorRes {
    char _gap_0[24];
    void * m_pSurface;
    int m_OriginX;
    int m_OriginY;
};

struct gbGfxManager {
    char _gap_0[8];
    unsigned int hGfxWnd;
    char DrvInfo[184]; // gbGfxDriverInfo
    gbVertPoolMgr * pVertPoolMgr;
    gbEffectMgr * pEffectMgr;
    gbResManager * pTexResMgr;
    gbPrintFontMgr * pFontMgr;
    gbMatrixStack * pMatrixStack[4];
    char ViewMatrix[64]; // gbMatrix4
    char InvViewMatrix[64]; // gbMatrix4
    char WorldMatrix[64]; // gbMatrix4
    int CurZBias;
    int bWireMode;
    char AmbientLight[16]; // gbColorFlt
    float fSelfIllum;
    gbSceneGraph * pSceneGraph;
    char Viewport[24]; // gbViewPort
    char ClearParam[20]; // gbClearParam
    double LastTime;
    double CurTime;
    unsigned int LastTick;
    unsigned int CurTick;
    char Stat[48]; // gbGfxStatistic
    char AllLight[832]; // gbLight[8]
    int LightEnable[8];
    char FogParam[52]; // gbFogParam
    gbTexture * m_pCurTexture[8];
};

struct gbCamera {
    float fov;
    float OrthoSize;
    float Wscreen;
    float Hscreen;
    float zNear;
    float zFar;
    char Viewport[24]; // gbViewPort
    char Plane[96]; // float[6][4]
    int numPlane;
    char ViewMatrix[64]; // gbMatrix4
    char InvVMatrix[64]; // gbMatrix4
    gbCamControler * pControl[16];
    int CurCtrl;
    gbGfxManager * pGfxMgr;
    char eyeLoc[12]; // gbVec3D
    char eyeDir[16]; // gbQuaternion
};

struct gbSound2DNode {
    gbSoundData * pData;
    void * hSample;
    int nLoop;
    float Volume;
};

struct gbResource {
    char _gap_0[8];
    char * pName;
    unsigned int NameCrc32;
    int IsLoaded;
    gbResManager * pMgr;
};

struct gbMeshSection {
    int BlendFlags;
    int bBakedLight;
    char TexArray[68]; // gbTextureArray
    char Material[68]; // gbMaterial
    gbIndexBubble * pIndexBub;
    unsigned int VertStart;
    unsigned int VertEnd;
    char Point[12]; // gbVec3D
    gbRenderEffect * pCustomEffect;
    char TexAnim[16]; // gbTexFlipAnim
};

struct gbRenderEffect {
    char _gap_0[24];
    void * m_pEffect;
    unsigned int m_Flags;
    void * m_DeclHandle;
    unsigned int m_ParamHandle[8];
};

struct gbChain1DNode {
    char _gap_0[4];
    gbChain1DNode * next;
};

struct gbVisNode {
    char _gap_0[28];
    gbCycleQueue<gbNodeMsgObj> MsgBuffer;
    int Priority;
    float TimeScale;
    int bShow;
    int bDoShadow;
    void * pCullObj;
    gbVisNode * pCullPrev;
    gbVisNode * pCullNext;
    float BlendParam;
    char BlendFlag[4]; // NodeBlend
};

struct gbLightObj {
    char _gap_0[8];
    char m_LightType[4]; // gbLightObj::LIGHT_TYPE
    char m_Color[16]; // gbColorFlt
    char m_Ambient[16]; // gbColorFlt
    int m_UseDiffuse;
    int m_UseSpecular;
    float m_NearStart;
    float m_NearEnd;
    float m_FarStart;
    float m_FarEnd;
    char m_DecayType[4]; // gbLightObj::DECAY_TYPE
    float m_DecayRadius;
    char m_LightShape[4]; // gbLightObj::LIGHT_SHAPE
    float m_HotSize;
    float m_Falloff;
    float m_Aspect;
    char m_BoundSphere[16]; // gbSphere
    char m_SysLight[104]; // gbLight
    int m_BakedLight;
};

struct gbParticleGroup {
    char Name[64];
    double Life;
    char EmitterData[48]; // gbEmitterData
    void * pGroupParam;
    gbPartEmitter * pEmitter;
    void * pAllUnits;
    int MaxUnits;
    int nAlivePart;
    gbParticleEffect * pParticleEffect;
};

struct gbAudioManager {
    void * hStreamArray[3];
    int StreamStatus[3];
    void * h2DDriver;
    unsigned int h3DProvider;
    char Attach3D[120]; // SoundAttachObj[10]
    char Attach2D[48]; // SoundAttachObj[4]
    unsigned int CurTime;
    float S_3DMasterVol;
    float S_2DMasterVol;
    float MusicMasterVol;
    void * hListener;
    char ListenerPos[12]; // gbVec3D
    gbResManager SndDataMgr;
};

struct gbActor {
    char _gap_0[88];
    gbActorDef * pBody;
    int curSkin;
    void * pMixInfo;
    int NumMixInfo;
    void * pExpNode;
    int nExpNode;
    int MaxExpNode;
};

struct gbVFileSystem {
    int IsInit;
    char * rtDirectory;
    void * pFileBuffer;
    char Type[4]; // gbVFileSystem::__unnamed
    void * m_pckfp;
    unsigned int m_itemcount;
    CPK m_cpk;
};

struct gbVertexBubble {
    char _gap_0[8];
    gbVertexPool * pPool;
    int Start;
    int BubSize;
    int nVerts;
    float * pXYZ;
    float * pNormal;
    void * pColor1;
    void * pColor2;
    float * pUV[4];
};

struct gbDropGroup {
    char _gap_0[8];
    int m_MaxUnit;
    int m_nAliveUnit;
    float m_UnitSize;
    float m_Range;
    int m_EmitRate;
    float m_MinLife;
    float m_MaxLife;
    float m_MinEmitVel;
    float m_MaxEmitVel;
    float m_MinHeight;
    float m_MaxHeight;
    double m_LastFrameTime;
    float m_LeftTimeAccum;
    void * m_pUnits;
    gbTexture * m_pTex;
    gbRenderEffect * m_pEffect;
};

struct gbSnow {
    char _gap_0[80];
    float m_VelXZ;
};

struct gbKeyControler {
    char _gap_0[4];
    void * pKeys;
    int KeySize;
    char KeyType[4]; // gbKeyType
    int nKey;
};

struct gbVFile1 {
    unsigned int OpenMode;
    unsigned int EntryAddr;
    unsigned int FileSize;
    char pFilePath[256];
    unsigned int m_NowAddr;
};

struct gbParticleEffect {
    char _gap_0[88];
    char Name[64];
    int nPartGroup;
    int nGroupParam;
    int nEmitter;
    gbParticleGroup * pPartGroups;
    void * pGroupParams;
    gbPartEmitter * pEmitters;
    int maxparticle;
    int emittedto;
    int npwmr;
    void * pParticles;
    float gravity;
    float timescale;
    int maxfps;
    int camerafollow;
    float camerafollowdis;
    int gravityeffect;
    float frontplane;
    float backplane;
    char objectoffset[12]; // gbVec3D
    char systemoffset[12]; // gbVec3D
    char systemvelocity[16]; // gbVec3D
    double CurTime;
    double ElapseTime;
    float SpaceScale;
    char m_ToWorld[68]; // gbMatrix4
};

struct gbSoundData {
    char _gap_0[24];
    void * pimage;
};

struct gbIndexBubble {
    char _gap_0[8];
    gbIndexPool * pPool;
    char Type[4]; // gbPrimType
    int nIndex;
    int BubSize;
    int Start;
    int StartVert;
    int EndVert;
};

struct gbGeomNode {
    char _gap_0[88];
    char CacheToW[64]; // gbMatrix4
    char OffMat[64]; // gbMatrix4
    gbKeyControler * PosCtrl;
    gbKeyControler * ScaleCtrl;
    gbKeyControler * RotCtrl;
    float DegScale;
    int UseControl;
    gbAnimScript * pScript;
    double CurTime;
    float AnimMaxTime;
    int nLoop;
    int nLoopPast;
    int bBlade;
    gbBaseMesh * pMesh;
    void * pTags;
    int nTag;
    int nXBlade;
    void * pXTagBlade;
};

struct gbTexture {
    char _gap_0[24];
    int Width;
    int Height;
    gbImage2D * pTexImage;
    gbPixelFormat InFmt;
    int nLevels;
};

struct gbEffectMgr {
    char _gap_0[12];
    gbGfxManager * m_pGfxMgr;
    gbTexture * m_pWhiteTex;
    gbTexture * m_pGrayTex;
    gbRenderEffect * m_pDefEffect;
    char m_AllHandle[2048]; // gbEffectMgr::HandleObj[64]
    int m_nHandle;
    gbRenderEffect * pCurEffect;
    int bDoPassOutside;
};

struct gbVertexPool {
    char _gap_0[8];
    char Type[4]; // gbPoolType
    void * pMemBuf;
    int VertNum;
    unsigned int VertType;
    int Stride;
    gbChain1D FreeVertBub;
    gbChain1D UsedVertBub;
};

struct gbBaseMesh {
    char _gap_0[24];
    char Type[4]; // gbMeshType
    char ObjName[32];
    unsigned int VertFVF;
    gbMeshSection * pSections;
    int nSection;
    char MemCache[16]; // gbMeshMemCache
    char BoundBox[24]; // gbAABBox
    float CurTime;
    gbGfxManager * pGfxMgr;
};

struct gbAnimScript {
    int BeginPos;
    int EndPos;
    int CurPos;
    float Var_Flt[8];
    int Var_Int[8];
    float AnimSpeed;
    char Vel[12]; // gbVec3D
    char Accel[12]; // gbVec3D
    char Offset[12]; // gbVec3D
    int IsHide;
    double CurTime;
    double NextTime;
};

struct gbDynVertBuf {
    char _gap_0[4];
    char Type[4]; // gbPoolType
    int VertNum;
    unsigned int VertType;
    int Stride;
    int BaseIndex;
    int LockVertNum;
    float * pXYZ;
    float * pNormal;
    void * pColor1;
    void * pColor2;
    float * pUV[4];
};

struct gbCamControler {
    char _gap_0[8];
    gbCamera * pCamera;
    double CtrlTime;
    double CtrlAge;
};

struct gbVolModNode {
    char _gap_0[88];
    char m_ToWorld[64]; // gbMatrix4
    char m_ToView[64]; // gbMatrix4
    void * m_pModObj;
};

struct gbSound3DNode {
    gbSoundData * pData;
    void * hSample;
    char Position[12]; // gbVec3D
    char Velocity[12]; // gbVec3D
    char Orientation[12]; // gbVec3D
    int EffectType;
    float Volume;
    int nLoop;
    float MinDist;
    float MaxDist;
};

struct gbSceneGraph {
    void * pAllRObj;
    int index[4096];
    int CurRObjPos;
    void * pnodebuf[4096];
    void * pOctree;
    gbVisNode * pSceneRoot;
    char pAllShadowObj[1792]; // gbRenderInfoObj[16]
    int nShadowObj;
    gbVolModNode * pAllVolMod[256];
    char VolModXform[16384]; // gbMatrix4[256]
    int nVolModNode;
    gbGfxManager * pGfxMgr;
    gbVisNode * pSkyBox;
    gbRenderEffect * pShadowQuadEffect;
    gbCamera * pCamera;
    void * pBladeMgr;
    char m_WaterNode[14336]; // gbRenderInfoObj[128]
    int m_nWaterNode;
    char m_CVDNode[896]; // gbRenderInfoObj[8]
    int m_nCVDNode;
    unsigned char m_renderOctree;
    unsigned char m_renderWater;
    unsigned char m_bAttachSceneWater;
};

"""


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        # Step 1: Parse all struct definitions
        log("[STEP 1] 导入结构体定义...")
        ret = idc.parse_decls(STRUCT_HEADER, idc.PT_TYP)
        log(f"  parse_decls 返回: {ret} (0=成功)")

        # Verify
        til = ida_typeinf.get_idati()
        count = 0
        for name in ['gbResManager', 'gbImage2D', 'gbPrintFont', 'gbPartEmitter', 'gbRefObject', 'gbEmitterShape', 'gbBinkVideo', 'gbMatrixStack', 'gbIndexPool', 'gbVertPoolMgr', 'gbPrintFontMgr', 'gbCycleQueue<gbNodeMsgObj>', 'gbPixelFormat', 'gbActorMgr', 'gbActorDef', 'gbGfxManager_D3D', 'gbTexture_D3D', 'gbNBTreeNode', 'gbCursorRes', 'gbGfxManager', 'gbPartParamControl', 'gbCamera', 'gbSound2DNode', 'CD3DSettings', 'gbResource', 'gbMeshSection', 'gbRenderEffect', 'CPK', 'gbChain1DNode', 'gbVisNode', 'gbLightObj', 'gbDynArray<gbResource *>', 'CD3DEnumeration', 'gbParticleGroup', 'gbAudioManager', 'gbChain1D', 'gbActor', 'gbVFileSystem', 'gbVertexBubble', 'gbDropGroup', 'gbSnow', 'gbKeyControler', 'gbVFile1', 'gbParticleEffect', 'gbSoundData', 'gbIndexBubble', 'gbGeomNode', 'gbTexture', 'gbEffectMgr', 'gbVertexPool', 'gbBaseMesh', 'gbAnimScript', 'gbDynVertBuf', 'gbCamControler', 'gbVolModNode', 'gbSound3DNode', 'gbSceneGraph']:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                count += 1
        log(f"  可访问结构体: {count}/57")

        # Step 2: Clear Hex-Rays cache for affected functions
        log("")
        log("[STEP 2] 清除 Hex-Rays 反编译缓存...")
        cleared = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Only clear functions belonging to imported classes
            cls = name.split("::")[0] if "::" in name else ""
            if cls in {'gbResManager', 'gbImage2D', 'gbPrintFont', 'gbPartEmitter', 'gbRefObject', 'gbEmitterShape', 'gbBinkVideo', 'gbMatrixStack', 'gbIndexPool', 'gbVertPoolMgr', 'gbPrintFontMgr', 'gbCycleQueue<gbNodeMsgObj>', 'gbPixelFormat', 'gbActorMgr', 'gbActorDef', 'gbGfxManager_D3D', 'gbTexture_D3D', 'gbNBTreeNode', 'gbCursorRes', 'gbGfxManager', 'gbPartParamControl', 'gbCamera', 'gbSound2DNode', 'CD3DSettings', 'gbResource', 'gbMeshSection', 'gbRenderEffect', 'CPK', 'gbChain1DNode', 'gbVisNode', 'gbLightObj', 'gbDynArray<gbResource *>', 'CD3DEnumeration', 'gbParticleGroup', 'gbAudioManager', 'gbChain1D', 'gbActor', 'gbVFileSystem', 'gbVertexBubble', 'gbDropGroup', 'gbSnow', 'gbKeyControler', 'gbVFile1', 'gbParticleEffect', 'gbSoundData', 'gbIndexBubble', 'gbGeomNode', 'gbTexture', 'gbEffectMgr', 'gbVertexPool', 'gbBaseMesh', 'gbAnimScript', 'gbDynVertBuf', 'gbCamControler', 'gbVolModNode', 'gbSound3DNode', 'gbSceneGraph'}:
                try:
                    ida_hexrays.mark_cfunc_dirty(ea)
                    cleared += 1
                except:
                    pass
        log(f"  标记需重新反编译: {cleared} 个函数")

        # Step 3: Save
        log("")
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    try:
        idc.qexit(0)
    except:
        pass


main()
