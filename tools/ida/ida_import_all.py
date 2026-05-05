"""
IDAPython: 批量导入 PDB 结构体定义 (420 个)
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

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "ida_import_all_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x00558000

STRUCT_HEADER = r"""
struct gbNodeMsgObj;

struct gbDynArray_pgbResource {
    void ** pBuffer;
    int MaxNum;
    int CurNum;
};

struct gbCycleQueue_gbNodeMsgObj {
    gbNodeMsgObj * pBuffer;
    int MaxNum;
    int CurNum;
    int Flags;
    int Head;
    int Tail;
};

struct CCBControlWindow;
struct CParticleEffect;
struct CCBStageRole;
struct UITextureArray;
struct UIStaticFlex;
struct UINote;
struct std::locale;
struct gbResManager;
struct gbAudioManager;
struct _TimeMgr;
struct UIButton;
struct UIStatic;
struct MUIDialog;
struct Inventory;
struct gbPixelFormat;
struct gbImage2D;
struct PurgeEffect;
struct UIPar_TimeCtrl;
struct UIParticle;
struct UIFlexBar;
struct UIScrollBar;
struct UIListBox;
struct TimeCtl;
struct UI3DObj;
struct UI3DCtrl;
struct SwordUI;
struct CJ_FindFile;
struct ScriptWaitFrm;
struct gbSoundData;
struct gbParticleEffect;
struct TxtFile;
struct RoleTaskPool;
struct PalScriptIdleObj;
struct CD3DSettings;
struct CD3DEnumeration;
struct gbGfxManager_D3D;
struct gbMeshSection;
struct UIStaticEX;
struct UIProgressBar;
struct UILoadingFrm;
struct gbCursorRes;
struct CArrayList;
struct CG_Edit;
struct CCBResultWindow;
struct _Item;
struct GrayScale;
struct CCBStage;
struct UITitle_XJTM;
struct sg_emission_control;
struct _TextureLib_Data;
struct CCBAI;
struct FindArc;
struct ARC_PAL_GDB;
struct UIButtonEXA;
struct gbBaseMesh;
struct SkyboxEff;
struct MXCEft;
struct UIPar_Star;
struct std::logic_error;
struct gbSceneGraph;
struct UIAnimateCtrl;
struct UITabBtn;
struct EquipUI;
struct ParabolaCalculator;
struct StateUI;
struct TaskBookUI;
struct MXPoisonFog;
struct UIAnimateCtrlEX;
struct gbVisNode;
struct MeshFx;
struct UIStaticFlip;
struct UITextArea;
struct UIRoleDialog;
struct gbDynVertBuf;
struct CCBDisplayChain;
struct gbVolModNode;
struct ConfigFile;
struct gbActorDef;
struct gbActorMgr;
struct CG_Entry;
struct CPK;
struct SoundMgr;
struct Object3D;
struct LineupComp;
struct UIRoleSelect;
struct Comp_DonateUI;
struct CEffQuad;
struct CMeteorChain;
struct gbCamera;
struct CCBAttackSequen;
struct UIPar_Meteor;
struct SceneMapObj;
struct ORect;
struct UIDragBar;
struct UIStaticRM;
struct CEffTrackCustomShape;
struct UISceneMap;
struct PtrArray;
struct CG_UI;
struct C3DSpark;
struct gbGeomNode;
struct ParticleEffect;
struct MXTransport;
struct gbSound3DNode;
struct CEmitter;
struct gbIndexBubble;
struct sg_customshape;
struct sg_emitter;
struct gbEmitterShape;
struct gbPartParamControl;
struct gbPartEmitter;
struct CResistanceMotionPolicy;
struct Reoccupy;
struct UICursor;
struct CEffgbParticle;
struct CEffect;
struct CAcceleratedMotionPolicy;
struct UITitle_BBTY;
struct PropUI;
struct CCBProtectWindow;
struct UIHeadDialog;
struct ScreenFadeIn;
struct UnderWater;
struct ComposeUI;
struct CCBRoleState;
struct gbDropGroup;
struct UITabCtrl;
struct CEffSParticle;
struct CEffCylinder;
struct GRPinput;
struct RestScript;
struct gbLightObj;
struct gbActor;
struct UIAnimate;
struct CEffectSystem;
struct gbBinkVideo;
struct UIStaticCB;
struct UIPushButton;
struct ProtectPanel;
struct MainEquipUI;
struct C2DSpark;
struct CEffTrackCylinder;
struct CEffCustomShape;
struct SkyboxEffMgr;
struct MyMdl;
struct SceneObj;
struct NavigationInfo;
struct Actor;
struct Role;
struct Scene;
struct CCBEditor;
struct _Item_List_Info;
struct CIniFile;
struct UIEmote;
struct CCBStageCam;
struct HeadMsg;
struct COnceFramePolicy;
struct scSCEFile;
struct UITitle_JDHY;
struct SwitchVariable;
struct CCBParabolaWindow;
struct BillBoardFace;
struct gbChain1D;
struct gbNBTreeNode;
struct ARC_Reoccupy;
struct gbTexture_D3D;
struct RenderTarget;
struct std::runtime_error;
struct CEffShock;
struct gbKeyControler;
struct gbSound2DNode;
struct util;
struct CEffCallBack;
struct CFadeColorPolicy;
struct CCBSystem;
struct _Console;
struct StringTable;
struct gbSnow;
struct SceneMap;
struct gbIndexPool;
struct RoleCamera;
struct Archive;
struct CPolicy;
struct MXFire;
struct CCBAIWindow;
struct gbPrintFontMgr;
struct LineupUI;
struct CEffBink;
struct UIButtonEX;
struct SaleUI;
struct CPKFile;
struct CEffTrackSParticle;
struct ChoseCompose;
struct CParticleSystem;
struct CCBMagicWindow;
struct MXSavePoint;
struct CCBSkillWindow;
struct GlowObj;
struct std::locale::id;
struct gbTexture;
struct CEffTrackGrid;
struct sg_particle;
struct ScreenEffect;
struct UICaption;
struct PalScriptWaitObj;
struct CCBItemWindow;
struct CCBUI;
struct CCBFiveNimbusWindow;
struct gbMatrixStack;
struct gbRenderEffect;
struct std::locale::_Locimp;
struct MainPropUI;
struct CEffTrackQuad;
struct CEffGrid;
struct CReBackFramePolicy;
struct RoleCameraCtrl;
struct gbGfxManager;
struct UIFrameWnd;
struct UIWnd;
struct KeyFrame;
struct gbVFile1;
struct CEffTrackModel;
struct CEffMgr;
struct RoleFadeOut;
struct gbVertPoolMgr;
struct RoleShadow;
struct UIChatRest;
struct UIGameFrm;
struct CCBStageShadow;
struct PathFinder;
struct RoleFadeIn;
struct CEffObj;
struct gbVertexBubble;
struct gbParticleGroup;
struct std::locale::facet;
struct SkyBox;
struct gbRefObject;
struct MagicUI;
struct Glow;
struct gbPrintFont;
struct CCCTData;
struct CEffModel;
struct NameSys;
struct PalScript;
struct OpenBaseFile;
struct DealUI;
struct LayerNode;
struct UIDialog;
struct std::_Timevec;
struct ObjLockInput;
struct std::ios_base;
struct UISceneFace;
struct UISceneFrm;
struct UIStaticEXA;
struct CEffExplosive;
struct ObjectCamera;
struct ARC_Inventory;
struct UIMap;
struct graph;
struct MU_SortFun;
struct RotateInvObj;
struct CCBLineupWindow;
struct OpenNULLFile;
struct Object;
struct t3DModel;
struct scVarStack;
struct CTrail;
struct UITitle_YXXX;
struct SceneMapPlayer;
struct Average;
struct gbVertexPool;
struct UIBigMap;
struct RotateObj;
struct UIRoleSelectDialog;
struct CRotateEmitterPolicy;
struct SCNFile;
struct gbEffectMgr;
struct CSEHException;
struct CCBControl;
struct CCBStageEffect;
struct XJ_Pic;
struct CEffAudio;
struct gbResource;
struct UIPosMaker;
struct UIGroupCtrl;
struct CG_Scene;
struct sg_particle_scene;
struct CLoad3DS;
struct CEffAction;
struct UITitle_QCYM;
struct exception;
struct gbChain1DNode;
struct std::_Locinfo;
struct UICoverFrm;
struct AStarPathFinder;
struct ScreenEffectMgr;
struct gbCamControler;
struct UIGameOver;
struct CCBCamControl;
struct SystemUI;
struct gbVFileSystem;
struct CEffMeteor;
struct UITitle_ArcSave;
struct gbAnimScript;
struct PAL_GDB;
struct DealData;
struct PlayerItemSortFun;
struct JusticeBookUI;
struct CCBStageScene;

struct CCBControlWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIButton * m_pButtonAttack;
    UIButton * m_pButtonSkill;
    UIButton * m_pButtonMagic;
    UIButton * m_pButtonItem;
    UIButton * m_pButtonDefence;
    UIButton * m_pButtonLineup;
    UIButton * m_pButtonAI;
    UIButton * m_pButtonFlee;
    UIButton * m_pButtonProtect;
    int m_CurCtrl;
};

struct CParticleEffect {
    int _bPlay;
    float _fTimeScale;
    int _tBlendType;
    float _fTime;
    char _ParticleSystems[16]; // std::vector<CParticleSystem *,std::allocator<CParticleSystem *> >
    gbRenderEffect * _pRenderEffect;
    gbGfxManager * _pGfxMgr;
    unsigned int _dwReserved[4];
};

struct CCBStageRole {
    CCBStage * m_pStage;
    CCBRoleState * m_pRoleState;
    char m_sLastRole[256];
    unsigned char m_bValid;
    unsigned char m_bVisible;
    unsigned char m_bPaused;
    unsigned char m_bAbsTime;
    float m_fTimeScale;
    unsigned char m_bAlive;
    unsigned char m_bRun;
    unsigned char m_bFlash;
    unsigned char m_bFlashCounter;
    float m_fFlashTimeKey;
    unsigned char m_bShowWeapon;
    float m_fBlend;
    unsigned char m_bBeSelected;
    int m_nIndex;
    unsigned int m_dwID;
    Actor * m_pActor;
    Actor * m_pRawActor;
    gbGeomNode * m_pWeaponModel;
    char m_vecWeapon[12]; // gbVec3D
    char m_rotWeapon[12]; // gbVec3D
    char m_vNoteThrowPos[12]; // gbVec3D
    char m_vThrowVec[12]; // gbVec3D
    char m_vecLen[12]; // gbVec3D
    unsigned char m_bShowWeaponModel;
    unsigned char m_bCatching;
    int m_iState;
    unsigned char m_bForceFinishThrowingWeapon;
    float m_fMaxThrowSpeed;
    float m_fThrowSpeed;
    float m_fThrowLen;
    char m_ThrowCmdData[44]; // tagCmdData
    char m_OBBox[76]; // gbOBBox
    unsigned char m_bTransMtl;
    unsigned char m_bSpecTransport;
    unsigned char m_bGrabed;
    unsigned char m_bNormalGrab;
    unsigned int m_dwStageTaskID;
    unsigned char m_bExternalTask;
    float m_fLeftWeapon;
    float m_fRightWeapon;
    int m_nTask;
    int m_nCurTask;
    void * m_fp;
    char m_Task[6144]; // tagRoleTask[64]
    unsigned int m_dwCurWeaponIndex;
    char m_eRoleActState[4]; // ERoleActState
    char m_eCurAction[4]; // ACTION_KIND
    char m_vecSunDir[12]; // gbVec3D
    char m_vecPos[12]; // gbVec3D
    char m_vecInitPos[12]; // gbVec3D
    char m_vecRunTarget[12]; // gbVec3D
    char m_vecRunVelocity[12]; // gbVec3D
    float m_fFaceDir;
    float m_fInitFaceDir;
    unsigned int m_dwCurAniFlag;
    unsigned int m_dwAniFlagOver;
    unsigned int m_dwAniFlagWork;
    unsigned int m_dwAniFlagWork1;
    unsigned int m_dwAniFlagWork2;
    unsigned int m_dwAniFlagWork3;
    unsigned int m_dwAniFlagPause;
    unsigned int m_dwAniFlagStore;
    unsigned int m_dwAniFlagFlyup;
    unsigned int m_dwAniFlagFlydown;
    unsigned int m_dwAniFlagThrowED;
    unsigned int m_dwAniFlagCatchED;
    unsigned int m_dwAniFlagSJump;
    unsigned int m_dwAniFlagEJump;
    unsigned int m_dwLastExternalActionCRC;
};

struct UITextureArray {
    gbTexture * m_ptex[16];
    int m_num;
};

struct UIStaticFlex {
    char _gap_0[68];
    float DURATION;
    char m_text[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char m_currect[16]; // tagRECT
    UITextureArray m_texs;
    char m_state[4]; // UIStaticFlex::State
    float m_statetime;
    char m_fonttype[4]; // gbFontType
    int m_tilesize;
    int m_openstyle;
};

struct UINote {
    char _gap_0[72];
    UIStaticFlex m_static;
    float time;
};

struct std::locale {
    void * _Ptr;
};

struct gbResManager {
    gbDynArray_pgbResource AllResPt;
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

struct _TimeMgr {
    unsigned int newtick;
    unsigned int oldtick;
    unsigned char bNote;
};

struct UIButton {
    char _gap_0[68];
    unsigned char m_hasDBclk;
    float m_ratiow;
    float m_ratioh;
    char m_drawrc[16]; // tagRECT
    char m_state[4]; // UIButton::UIBUTTON_STATE
    unsigned char m_canctrl;
    unsigned char m_bLockUpdate;
    int m_offsetx;
    int m_offsety;
    unsigned char m_bBigFont;
    UITextureArray m_texarray;
    void * m_texarrayInfo[3];
    gbTexture * m_disablepic;
    void * m_disablepicInfo;
    unsigned char m_mouseoff;
    unsigned char m_mouseon;
    int m_alignmode;
    char m_caption[128];
    unsigned char m_benable_snd;
};

struct UIStatic {
    char _gap_0[68];
    int m_bordersize;
    int m_align;
    float m_ratiow;
    float m_ratioh;
    int m_textx;
    int m_texty;
    char m_fonttype[4]; // gbFontType
    char m_text[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    gbTexture * m_pbk;
    void * m_pbkInfo;
    gbTexture * m_ppic;
    void * m_ppicInfo;
    gbTexture * m_disablepic;
    void * m_disablepicInfo;
    gbTexture * m_pbk2;
    unsigned char m_mouseoff;
    int m_FVF;
    int m_nTextW;
    unsigned char m_PureColor;
    int m_richtext;
};

struct MUIDialog {
    char _gap_0[72];
    UIWnd * ptr_Dlg;
    unsigned int m_DlgId;
    char m_rect[16]; // tagRECT
    char m_textRc[16]; // tagRECT
    UIStaticFlex m_bk;
    UIStatic m_static;
    UIStatic m_text;
    int m_btnW;
    int m_btnH;
    char m_btRc[16]; // tagRECT
    UIButton mb_Yes;
    UIButton mb_No;
    int Lacune;
    char m_type[4]; // DLG_TYPE
    char m_getMsg[4]; // DLG_MSG
    int dft_W;
    int dft_H;
    unsigned char m_IsModel;
    unsigned char m_isDoModel;
    int m_xOffset;
    int m_yOffset;
    _TimeMgr _m_timeMgr;
    unsigned char _m_canEndDlg;
    unsigned char _haveSound;
};

struct Inventory {
    char m_items[16]; // std::vector<PlayerItem,std::allocator<PlayerItem> >
    int m_curtype;
    char m_typeitems[16]; // std::vector<PlayerItem,std::allocator<PlayerItem> >
    int m_money;
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

struct PurgeEffect {
    gbTexture * pSrcTex;
    gbImage2D pSrcImg;
    gbImage2D pDstImg;
    int m_ItemNum;
    char EffItem[16]; // std::vector<EffectItem,std::allocator<EffectItem> >
    unsigned char m_isUpdateMerge;
};

struct UIPar_TimeCtrl {
    unsigned int newtick;
    unsigned int oldtick;
    unsigned char bNote;
};

struct UIParticle {
    char m_viewRect[16]; // tagRECT
    int view_radiusX;
    int view_radiusY;
    int par_radiusX;
    int par_radiusY;
    int _W;
    int _H;
    unsigned char m_bGetBottom;
    unsigned char m_bBounceX;
    float m_HelixAngle;
    float m_tempx;
    float m_tempy;
    float m_helix_rx;
    float m_helix_ry;
    unsigned char m_isDiffuse;
    float m_posx;
    float m_posy;
    int m_FlareTime;
    unsigned char m_isSubA;
    char m_rainbowColor[4]; // gbColorQuad
    unsigned char m_bGetTop;
    float m_riseY;
    int m_xflag;
    int m_state;
    unsigned char m_iscolorfade;
    UIPar_TimeCtrl m_time;
    unsigned int m_sec;
    char m_color[4]; // gbColorQuad
    unsigned char _isActive;
    float _fade;
    float _x;
    float _y;
    float _xi;
    float _yi;
    float _xg;
    float _yg;
    char _texName[256];
    gbTexture * _ptex;
    UIStatic _element;
    int _sizeX;
    int _sizeY;
    float _speed;
};

struct UIFlexBar {
    char _gap_0[68];
    int m_tilewidth;
    int m_tileheight;
    gbTexture * m_tex;
    char m_style[4]; // UIFlexBar::STYLE
};

struct UIScrollBar {
    char _gap_0[68];
    unsigned char m_bPress;
    unsigned char m_bPressed;
    UIFlexBar m_bk;
    int m_DragState;
    unsigned char m_bDrag;
    char m_lastPt[8]; // tagPOINT
    int m_btnH;
    char m_mouseat[4]; // UIScrollBar::SB_AREA
    int m_min;
    int m_max;
    int m_pos;
    float m_lastpos;
    float m_drawpos;
    float m_step;
    int m_pagesize;
    UITextureArray m_texarray;
    void * m_texarrayInfo[10];
    float m_keytime;
    char m_btnrect[32]; // tagRECT[2]
    int m_slideroffset;
    int m_slidertboffset;
    int m_sliderw;
    int m_sliderh;
};

struct UIListBox {
    char _gap_0[68];
    char m_selcolor[4]; // gbColorQuad
    int m_showGrayBk;
    unsigned char m_hasKeyCtrl;
    UIScrollBar m_scrollbar;
    int m_numcol;
    char m_column[736]; // UILBColumn[8]
    int m_itemheight;
    int m_fontsize;
    int m_firstshow;
    int m_onsel;
    int m_locksel;
    char m_scrollRc[16]; // tagRECT
    gbTexture * m_pbkpic;
    void * m_pbkpicInfo;
    gbTexture * m_selpic;
    void * m_selpicInfo;
    int m_seloffset;
    int m_seloffsetL;
    int m_seloffsetR;
    int m_scrollW;
    char m_seltexcolor[4]; // gbColorQuad
    char m_itemoffset[8]; // tagPOINT
    int m_movesel;
    char m_rowenable[16]; // std::vector<int,std::allocator<int> >
};

struct TimeCtl {
    unsigned int newtick;
    unsigned int oldtick;
    unsigned char bNote;
};

struct UI3DObj {
    unsigned char m_mouseoff;
    int m_enable;
    int m_needdel;
    int m_type;
    gbGeomNode * m_pol;
    Actor * m_actor;
    char m_pos[12]; // gbVec3D
};

struct UI3DCtrl {
    char _gap_0[68];
    int m_numobj;
    UI3DObj m_obj[5];
    float m_orthosize;
    int m_rotatemode;
    unsigned char m_isrotateto;
    int m_speed;
    float m_rotate;
    float m_rotatetarget;
    float m_rotx;
    float m_rotz;
    float m_dropx;
    float m_dropy;
    float m_dropz;
    float m_scalex;
    float m_scaley;
    float m_scalez;
    gbLightObj * m_lightobj;
    gbCamera * m_camera;
    char m_raydir[12]; // gbVec3D
};

struct SwordUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    int m_ljsNum;
    UIStatic m_ljsNumber;
    int m_purgeEquipNum;
    int m_purgeWeaponNum;
    int m_avgWeaponWU;
    int m_avgAdornWU;
    int m_avgAdornFANG;
    int m_avgDefFANG;
    int m_adornNum;
    int m_defNum;
    char m_WSkill[21280]; // FightSkill[28]
    int m_wskillNum;
    unsigned char m_IsMsg;
    int m_CtrlRole;
    unsigned char m_IsActive;
    unsigned char m_IsCreateable;
    unsigned char m_IsLunar;
    unsigned char m_is3dLunar;
    int m_SelNum;
    int m_CurPage;
    float m_angle;
    float rot;
    char m_Distribute[1584]; // S_Distribute[99]
    int FetchVal;
    int GuVal;
    StateUI * pStateUI;
    UIStatic m_FrameLine;
    UIStatic m_TimeMoney;
    UIStatic stp_BarL;
    UIStatic stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    UIStatic m_GameTime;
    UIStatic m_GameMoney;
    char m_btnPar[66304]; // UIParticle[7][16]
    char m_btnPar2[66304]; // UIParticle[7][16]
    char m_btnParRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    UIStatic Sword_Name;
    UIStatic Sword_Att;
    UIStatic m_Ljs;
    UIStatic m_WulingCtrl;
    UI3DCtrl m_Sword;
    UI3DCtrl m_ljs3D;
    UIStatic m_SwordFrame;
    UIStatic m_SwordRemarkBk;
    UIStatic m_SwordRemark;
    UIButton m_Yjfx;
    char m_RemarkRc[16]; // tagRECT
    char m_SwordRemarkRc[16]; // tagRECT
    char m_NoteSwordRemarkRc[16]; // tagRECT
    unsigned short m_SwordDstX;
    unsigned short m_SwordNoteX;
    int m_bSwordRemarkOut;
    UIButton mb_Positive[5];
    UIStatic ms_Positive[5];
    UIButton mb_Lunar[5];
    UIStatic ms_Lunar[5];
    UIStatic ms_Perfect[5];
    unsigned char m_CanCtrlBtn;
    UIButton mb_Test;
    UIParticle m_parSword[168];
    char m_parSwordRc[16]; // tagRECT
    UIParticle m_parPurge[168];
    UIButton m_PositiveBtn;
    UIButton m_LunarBtn;
    char Purge_rectA[80]; // tagRECT[5]
    char Purge_rectB[80]; // tagRECT[5]
    char dstRect[80]; // tagRECT[5]
    PurgeEffect m_PurgeEffect;
    TimeCtl m_effTime;
    unsigned char m_bSwordMotion;
    unsigned char m_bSwordEff;
    unsigned char m_bSwordRot;
    unsigned char m_bEff;
    int m_curpar;
    TimeCtl m_swdTime;
    int m_Orthosize;
    int m_FinalOrthosize;
    char m_PURGEINFO[88]; // _PURGE_INFO[11]
    UIFlexBar m_SmallBar;
    UIFlexBar m_BigBar;
    UIButton m_Pushbtn[5];
    UIStatic m_equipFlag;
    UIStatic m_purgeFlag;
    UIFlexBar m_ListTitle;
    UIStatic m_EquipTitle;
    UIStatic m_PurgeTitle;
    UIStatic m_ListTitlePurge;
    UIStatic m_ListFrame;
    UIStatic m_ListFramePurge;
    UIStatic m_ListGrid[12];
    UIStatic m_ListGridPurge[12];
    UIListBox m_WeaponList;
    UIListBox m_ClothList;
    UIListBox m_HatList;
    UIListBox m_ShoesList;
    UIListBox m_AdornList;
    UIListBox m_StuffList;
    char m_StrRc[16]; // tagRECT
    UIStatic m_EquipStr;
    UIStatic m_StuffStr;
    UIStatic m_GuVal;
    char m_MsgRc[16]; // tagRECT
    UIStatic m_PurgeMsg;
    UIFlexBar m_PurgeBottom;
    char m_BtnRc[16]; // tagRECT
    UIButton m_OK;
    UIButton m_Cancel;
    UIButton m_SortEquipbyPrice;
    UIButton m_SortEquipbyGu;
    UIButton m_SortStuffbyPrice;
    UIButton m_SortStuffbyGu;
    int m_SortState;
    Inventory m_ItemArray;
    MUIDialog m_Dlg;
    MUIDialog m_Msg;
    char note_purgenum[4]; // WuLing
    unsigned char m_bHasWeapon;
};

struct CJ_FindFile {
    char m_strRoot[324];
    void * m_pNextInfo;
    void * m_hContext;
    void * m_pFoundInfo;
    char m_fileName[324];
    char m_strbuf[324];
    unsigned char m_bClosed;
};

struct ScriptWaitFrm {
    char _gap_0[8];
    char m_frm[4]; // PAL3_FRAME
};

struct gbSoundData {
    char _gap_0[24];
    void * pimage;
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

struct TxtFile {
    char m_token[512];
    char * m_buf;
    char * m_sectionstart;
    char * m_curpos;
};

struct RoleTaskPool {
    char m_TaskData[16]; // std::vector<RoleTask,std::allocator<RoleTask> >
    char m_TaskLine[16]; // std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >
    TxtFile m_taskFile;
    char _TaskPicFolder[128];
};

struct PalScriptIdleObj {
    char _gap_0[8];
    float m_time;
    float m_passedtime;
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

struct UIStaticEX {
    char _gap_0[160];
    float m_rotate;
    int m_rotmode;
    float m_rotdst;
    float m_rotspeed;
    int m_rotdir;
    unsigned char m_isStoped;
    float m_accelerate;
    float m_notespeed;
};

struct UIProgressBar {
    char _gap_0[68];
    int m_mode;
    int m_dir;
    char m_ProgressRc[16]; // tagRECT
    char m_decorateRc[16]; // tagRECT
    float m_progress;
    float m_speed;
    float m_SetProgress;
    float m_Lenth;
    float m_MaxVal;
    float m_stepval;
    float m_radius;
    float m_lradius;
    float m_rradius;
    float m_tradius;
    float m_bradius;
    float m_step;
    float m_Val;
    unsigned char m_IsGetit;
    char m_bkColor[4]; // gbColorQuad
    char m_foColor[4]; // gbColorQuad
    gbTexture * m_pbk;
    void * m_pbkInfo;
    gbTexture * m_ppic;
    void * m_ppicInfo;
    gbTexture * m_pdecorate;
    void * m_pdecorateInfo;
    int m_decorateW;
    int m_decorateH;
    int m_decorateOffsetX;
    int m_decorateOffsetY;
    char m_pgrmode[4]; // PGR_MODE
    char m_color[4]; // gbColorQuad
    int m_dstAlpha;
    int m_alpha;
    int m_minAlpha;
    float m_fadespeed;
    unsigned char m_isAdd;
    unsigned char m_isFlash;
    unsigned char m_stop;
    int m_warningval;
};

struct UILoadingFrm {
    char _gap_0[72];
    UIProgressBar m_LoadProgress;
    float m_anitime;
    int m_aniFlag;
    float m_MaxValue;
    unsigned char m_isOverProgress;
};

struct gbCursorRes {
    char _gap_0[24];
    void * m_pSurface;
    int m_OriginX;
    int m_OriginY;
};

struct CArrayList {
    char m_ArrayListType[4]; // ArrayListType
    void * m_pData;
    unsigned int m_BytesPerEntry;
    unsigned int m_NumEntries;
    unsigned int m_NumEntriesAllocated;
};

struct CG_Edit {
    CG_Entry * m_pFather;
    char m_MousePt[8]; // tagPOINT
    char m_Param[12]; // _FLOORPARAM
    float m_fYaw;
    float m_fPitch;
    float m_fDist;
    float m_fCamX;
    float m_fCamY;
    float m_fCamZ;
    char m_vCamForward[12]; // gbVec3D
    gbRenderEffect * EFT_LINE;
    gbRenderEffect * EFT_GEOM_NOTEX;
    gbRenderEffect * EFT_GEOM_NOTEX_LINE;
    unsigned char m_bWaitForEditArea;
    char m_rTouchArea[16]; // tagRECT
    char m_rLastObjArea[16]; // tagRECT
    char m_pLastGroundPt[8]; // tagPOINT
    int m_nNoteMoney;
};

struct CCBResultWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIStatic * m_pWind;
    UIStatic * m_pThunder;
    UIStatic * m_pWater;
    UIStatic * m_pFire;
    UIStatic * m_pEarth;
    UIStatic * m_pDouble;
    UIStatic * m_pEXP;
    UIStatic * m_pLevel;
    UIStatic * m_pFace[11];
    UIStatic * m_pHGM;
    UIProgressBar * m_pHP;
    UIProgressBar * m_pGP;
    UIProgressBar * m_pMP;
    CCBUI * m_pUI;
    int m_nIndex;
    unsigned char m_bClosed;
};

struct _Item {
    char title[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char info[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    unsigned char bHasChild;
    int nChildNum;
    unsigned char bIsPic;
    void * ppChildren;
};

struct GrayScale {
    unsigned char m_bEnable;
    gbTexture * m_pTex;
};

struct CCBStage {
    CCBSystem * m_pCBSystem;
    CCBRoleState * m_pRoleState;
    CCBEditor * m_pEditor;
    CCBStageCam * m_pCam;
    CCBCamControl * m_pCamControl;
    CCBStageScene * m_pScene;
    CCBStageRole * m_pRole[11];
    Actor * m_TempStorageNGH;
    Actor * m_NGHVariance;
    Actor * m_TempStorageWPX;
    Actor * m_WPXVariance;
    CCBDisplayChain * m_pDisplayChain;
    CCBStageShadow * m_pShadow;
    CCBStageEffect * m_pEffect;
    int m_BFARole;
    int m_BFARound;
    char m_ptMousePos[8]; // tagPOINT
    int m_nSelectedRole;
    unsigned char m_bRoleSelected[11];
    unsigned char m_bHideSceneAndRole;
    float m_fDamageNumPosY[11];
    float m_fMusicVolume;
    unsigned char m_bPaused;
    int m_nTask;
    int m_nCurTask;
    int m_nCurSubTask;
    char m_Task[673792]; // tagStageTask[256]
    unsigned int m_dwAniFlagOver;
};

struct UITitle_XJTM {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic m_background;
    UIStatic m_title;
    UIButton m_exit;
    unsigned char m_IsActive;
    UICoverFrm * m_pMgr;
    _Item m_Item;
    int m_SelFirstRow;
    int m_SelSecondRow;
    unsigned char m_SelFirstChanged;
    unsigned char m_SelSecondChanged;
    unsigned char m_SelZeroChanged;
    UIStatic m_WordBk;
    UIStatic m_BtnBk;
    UIButton m_BtnFirstRow[4];
    UIButton m_BtnSecondRow[5];
    UIStatic m_ItemInfo;
    UIStatic m_ItemPic;
};

struct sg_emission_control {
    char name[64];
    int particle_pointer;
    int emitter_pointer;
    float elapsetime;
    float total_elatime;
    int maxparticle;
    int first_time;
    float cyclelength;
    int replacestyle;
    char particle_array[36800]; // sg_particle_data[400]
    char emitter[44]; // sg_emitter_data
    sg_particle * pparticle;
    sg_emitter * pemitter;
    sg_particle_scene * scene_pointer;
};

struct _TextureLib_Data {
    char _gap_0[4];
    char * Seps;
    char * tok;
    char _libfolder[512];
    int _realNum;
    void * m_pData;
    unsigned char _isLoadTLI;
};

struct CCBAI {
    unsigned char m_bNewRole[11];
    CCBSystem * m_pCBSystem;
    CCBRoleState * m_pRoleState;
    void * m_pUtil;
    char m_VA[24]; // tagVA
    char m_VAO[512]; // tagVAO[32]
    char m_VAF[1024]; // tagVAF[32]
    char m_Demand[1760]; // tagDemand[11][10]
    char m_EnemyDemand[160]; // tagDemand[10]
    char m_FriendDemand[160]; // tagDemand[10]
};

struct FindArc {
    char mPal3SetUpPath[256];
    char arcPos[9216]; // ArcPosition[36]
    int mRealNum;
};

struct ARC_PAL_GDB {
    char m_head[160]; // ARC_OutFile
    char m_RoleData[170400]; // ARC_RoleAtt[200]
    char m_SkillData[228000]; // ARC_FightSkill[300]
    char m_ItemData[400000]; // ARC_FightItem[500]
    char m_ComboData[6320]; // ARC_ComboAttack[10]
    int i;
    unsigned char mLoaded;
};

struct UIButtonEXA {
    char _gap_0[344];
    char m_optData[16]; // _btnOPTDATA
    int m_EnableMode;
    char m_color[4]; // gbColorQuad
    char m_enablecolor[4]; // gbColorQuad
    char m_surecolor[4]; // gbColorQuad
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

struct SkyboxEff {
    gbRenderEffect * m_pEffectNormal;
    void * m_pEffTex;
    int m_nFrameNum;
    float m_fWaitTime;
    float m_fValidTime;
    float m_fps;
    float m_fSizeScale;
    float m_nEffWidth;
    float m_nEffHeight;
    char m_eEffMode[12]; // EffModeParam
    char m_vHalfSize[12]; // gbVec3D
    float m_fTime;
    float m_fPassTime;
    int m_nCurFrame;
    float m_fWidth;
    float m_fHeight;
    unsigned char m_bIsTime;
    unsigned char m_bOver;
    unsigned char m_bValid;
    unsigned char m_bDelyTime;
    float m_fNoteTime;
    unsigned int m_nameCrc;
    gbRenderEffect * m_pSkyboxEff;
    char m_vRender[48]; // gbVec3D[4]
};

struct MXCEft {
    char _gap_0[92];
    unsigned int m_dwEffectID;
    unsigned int m_hEffect;
    char m_pos[12]; // gbVec3D
    float m_fTime;
};

struct UIPar_Star {
    char _gap_0[68];
    gbTexture * m_pTex;
    char m_color[4]; // gbColorQuad
    int m_nFinalAlpha;
    int m_nMinAlpha;
    int m_nFade;
    int m_IsFadeRand;
    int m_IsFadeOut;
    int m_nLastTime;
    int m_IsLastTimeRand;
    int m_IsHighPoint;
    int m_IsInFlash;
    int m_nNextTime;
    int m_IsNextTimeRand;
    int m_nFrame;
};

struct std::logic_error {
    char _gap_0[12];
    char _Str[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
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

struct UIAnimateCtrl {
    char _gap_0[68];
    float m_FPS;
    float m_passtime;
    UITextureArray m_texarray;
    int m_curframe;
    int m_numframe;
    int m_looppassed;
    int m_nLoop;
    int m_mode;
};

struct UITabBtn {
    char m_BtnAndID[16]; // std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >
    int m_SelBtn;
    UIWnd * m_pFather;
};

struct EquipUI {
    char _gap_0[72];
    int bkWndX;
    int bkWndY;
    char buf[256];
    int m_SelNum;
    int * m_ListNum;
    int m_x;
    int m_y;
    int m_Sum;
    int i;
    int j;
    int k;
    unsigned char _isCreatable;
    float _flashSpeed;
    char m_EquipData[17504]; // st_Manager
    void * p_DealData;
    char m_TempData[7620]; // PlayerAtt[5]
    char rc[16]; // tagRECT
    UIStatic m_Frame;
    UIFlexBar m_FrameBar;
    UIStatic m_Flag;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIAnimateCtrl m_ani;
    UIStatic m_Role[5];
    char m_RoleRc[80]; // tagRECT[5]
    int RoleX;
    int RoleY;
    int HeadW;
    int HeadH;
    unsigned char m_Is[5];
    char m_Arrow[38400]; // UIStatic[5][6][8]
    char m_ArrowNum[12800]; // UIStatic[5][2][8]
    char m_ArrowRc[3840]; // tagRECT[5][6][8]
    char m_IsArrow[240]; // uchar[5][6][8]
    int m_OldSelect;
    char m_IsMove[240]; // uchar[5][6][8]
    char m_AnimateRc[3840]; // tagRECT[5][6][8]
    char m_ArrowMove[12480]; // UIAnimate[5][6][8]
    char m_Icon[5640]; // UIStaticRM[5][6]
    char m_Select[4800]; // UIStatic[5][6]
    unsigned char m_IsControlEquip;
    char m_IsEquip[30]; // uchar[5][6]
    unsigned char m_IsMsg;
    int * m_EquipingNum;
    char m_Equiping[120]; // int[5][6]
    int * m_UnEquipingNum;
    int * m_MaxNum;
    char m_Adorn[12]; // uchar[5][2]
    UI3DCtrl m_3DObj;
    MUIDialog m_Msg;
    UIStatic m_TalkFrame;
    UIStatic m_Ready;
    char m_ReadyRc[16]; // tagRECT
    UIButton mb_EquipYes;
    UIButton mb_EquipNo;
    UIStatic m_EquipTalk;
    char m_EquipRc[16]; // tagRECT
    UIStatic m_ListFrame;
    UIStatic m_ListGrid[14];
    UIStatic m_ScrollHB;
    UIStatic m_EquipFlag;
    UIStatic m_ListEquipTitle;
    UIListBox ml_ListEquip;
    char ml_ListEquipRc[16]; // tagRECT
    char m_btnGroup[740]; // BtnGroup
    float m_ctrlTime;
    unsigned char m_bCanUpdate1;
    unsigned char m_bCanUpdate2;
    UIStatic m_EquipRemarkBk;
    UIStatic m_EquipRemark;
    char m_EquipRemarkRc[16]; // tagRECT
    UIStatic m_EquipAtt;
    char m_EquipAttRc[16]; // tagRECT
    UIStatic m_MoneyRemark;
    char m_MoneyRc[16]; // tagRECT
    UIStatic m_SumEquip;
    char m_SumRc[16]; // tagRECT
    UIButton mb_OK;
    char mb_OKRc[16]; // tagRECT
    unsigned char m_IsDicker;
    UIButton mb_Cancel;
    char mb_CancelRc[16]; // tagRECT
    UIButton mb_Exit;
    char mb_ExitRc[16]; // tagRECT
    UITabBtn m_TabBtn;
    char mb_DKRc[16]; // tagRECT
    char haveRc[16]; // tagRECT
    unsigned char m_isCancelTalk;
    unsigned char m_IsRefuse;
    char m_strIn[512]; // char[2][256]
    unsigned char m_IsTalk;
    int m_TalkCount;
    int m_talker;
    int m_TalkFlag;
    unsigned char m_bDK;
    int m_DkNum;
    int mb_DkFlag;
    unsigned int * m_DealID;
    int DealNum;
    int curID;
    unsigned char m_IsUse;
    unsigned char m_IsDeal;
    DealUI * pDealUI;
    unsigned char m_isSetData;
};

struct ParabolaCalculator {
    char velocity[12]; // gbVec3D
    char A[12]; // gbVec3D
    char B[12]; // gbVec3D
    float H;
    float G;
    char m_state[4]; // ParabolaCalculator::PRBL_STATE
};

struct StateUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    unsigned char m_IsMsg;
    unsigned char m_Is[5];
    int m_CtrlRole;
    unsigned char m_IsActive;
    unsigned char m_IsCreateable;
    UIStatic m_Frame;
    UIStatic m_TimeMoney;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic stp_BarL;
    UIFlexBar stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_TaskBook;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    UIStatic m_GameTime;
    UIStatic m_GameMoney;
    char m_par[66304]; // UIParticle[7][16]
    char m_par2[66304]; // UIParticle[7][16]
    char m_parRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    char m_PortraitRc[16]; // tagRECT
    UIStatic m_Portrait;
    UIStatic m_TeamState;
    UIStatic m_Time;
    UIStatic m_Money;
    char m_TeamStateRc[16]; // tagRECT
    char m_RoleState[19740]; // s_RoleState[5]
    UIStatic m_State[4];
    UIStatic m_Alignment;
    char m_AlignmentRc[16]; // tagRECT
    UIStatic m_Head[5];
    char m_HeadRc[80]; // tagRECT[5]
    UIStatic m_TopFrame;
    UIButton m_LeaveHere;
    char m_LeaveRc[16]; // tagRECT
    UI3DCtrl m_3DObj;
    MUIDialog m_DlgEx;
    LineupUI * p_LineupUI;
    MagicUI * p_MagicUI;
    MainEquipUI * p_mEquipUI;
    MainPropUI * p_mPropUI;
    SwordUI * p_SwordUI;
    JusticeBookUI * p_JusticeBookUI;
    TaskBookUI * p_TaskBookUI;
    SystemUI * p_SystemUI;
    int m_curRender;
    unsigned char m_saveflag_note;
    unsigned char m_isSeekSAVELOAD;
    UIStatic m_test;
    gbTexture * pInterceptTex;
    float sv;
    float ev;
    unsigned char m_isExit;
    char m_SpecialPropItem[40]; // s_SpecialPropItem[5]
};

struct TaskBookUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    unsigned char m_IsCreateable;
    unsigned char m_IsActive;
    StateUI * pStateUI;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic stp_BarL;
    UIFlexBar stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_TaskBook;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    MUIDialog m_DlgEx;
    char m_btnPar[66304]; // UIParticle[7][16]
    char m_btnPar2[66304]; // UIParticle[7][16]
    char m_btnParRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    UIStatic m_ListBK;
    UIStatic m_ListTitle;
    UIButton m_ListBtn[9];
    UIStatic m_ListBtnBkL;
    UIStatic m_ListBtnBkR;
    UIScrollBar m_Scroll;
    int m_IsScroll;
    UIStatic m_ScrollHB;
    UIStatic m_TaskBk;
    UIStatic m_TaskPicBk;
    UIStatic m_TaskPic;
    UIStatic m_TaskDesc;
    UIStatic m_TaskTitle;
    UIStatic m_TaskState;
    int m_SelItem;
    int m_FirstItem;
    int m_TotalItem;
    UIStatic m_FrameUp;
    UIStatic m_FrameDw;
    UIStatic m_FrameRight;
};

struct MXPoisonFog {
    char _gap_0[92];
    gbParticleEffect * m_pfog;
};

struct UIAnimateCtrlEX {
    char _gap_0[164];
    unsigned char m_isrot;
    float m_rotate;
    int m_rotmode;
    float m_rotdst;
    float m_rotspeed;
    int m_rotdir;
    unsigned char m_isStoped;
    float m_notespeed;
    gbTexture * m_singletex;
    unsigned char m_isRenderSingle;
};

struct gbVisNode {
    char _gap_0[28];
    gbCycleQueue_gbNodeMsgObj MsgBuffer;
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

struct MeshFx {
    char _gap_0[88];
    int m_iCurrentState;
};

struct UIStaticFlip {
    char _gap_0[160];
    char flipMode[4]; // _FLIP
};

struct UITextArea {
    char _gap_0[68];
    char m_buf[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char m_page[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    unsigned char m_bInvalidate;
};

struct UIRoleDialog {
    char _gap_0[80];
    UIStatic m_bk;
    UIAnimateCtrl m_ani;
    UIStaticFlip m_face;
    UITextArea m_static;
    float m_fPosY;
    float m_SfPosY;
    unsigned char m_bReady;
    int m_dlgh;
    char m_bkRc[16]; // tagRECT
    int m_mode;
    int m_leftright;
    float m_time;
    int m_sel;
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

struct CCBDisplayChain {
    CCBStage * m_pStage;
    CCBStageScene * m_pScene;
    char m_DefaultColor[4]; // tagRGBQUAD
    char m_ScreenQuadColor[4]; // gbColorQuad
    int m_nItemNum;
    char m_ShowItem[17920]; // tagShowItem[64]
    unsigned char m_byScreenQuadAlpha;
};

struct gbVolModNode {
    char _gap_0[88];
    char m_ToWorld[64]; // gbMatrix4
    char m_ToView[64]; // gbMatrix4
    void * m_pModObj;
};

struct ConfigFile {
    char m_filename[260];
};

struct gbActorDef {
    char _gap_0[24];
    void * m_ActionCache[16];
    int m_nFilledSlot;
};

struct gbActorMgr {
    gbResManager AllActorDef;
};

struct CG_Entry {
    unsigned char m_bActive;
    unsigned char m_bUIActive;
    CG_Scene * m_pScene;
    CG_UI * m_pUI;
    CG_Edit * m_pEdit;
    char m_LEVELPARAM[40]; // LEVELPARAM[5]
    char m_EntryFrame[4]; // PAL3_FRAME
    char m_EntryRolePos[12]; // gbVec3D
    char m_EntryCityName[64];
    char m_EntryName[64];
    unsigned char b_NoteJumpFree;
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

struct SoundMgr {
    char _gap_0[4];
    unsigned char m_bScriptMusic;
    char m_szScriptMusic[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    int m_nScriptLoop;
    char m_szSceneMusic[256];
    TxtFile m_MusicTable;
    gbAudioManager * m_audiodrv;
    float DEF3DMasterVol;
    float DEF2DMasterVol;
    float DEFMusicMasterVol;
    unsigned char m_bValidDetectSceneMusic;
    char m_cbbuf[16]; // std::vector<SoundItem,std::allocator<SoundItem> >
    int m_cbcursor;
    CPK m_Cpk;
};

struct Object3D {
    unsigned char m_isLoadObj;
    unsigned int m_type;
    gbGeomNode * m_pol;
    Actor * m_actor;
    gbGeomNode * m_subObj;
    unsigned int m_subType;
    unsigned char m_isLoadSubObj;
    unsigned char m_showSubObj;
    float m_subObjHeight;
    float m_height;
    char m_position[12]; // gbVec3D
    char RelativePos[12]; // gbVec3D
    float m_roty;
    float m_rotx;
    float m_rotz;
    float m_dropx;
    float m_dropy;
    float m_dropz;
    unsigned char m_visible;
    ObjectCamera * m_pCamera;
    float m_yaw;
    float m_pitch;
    float m_roll;
    float m_dist;
    char m_forward[12]; // gbVec3D
    float m_degreeToScreen;
    unsigned char m_isActionRelativeRot;
    unsigned char m_bRotDstDegree;
    float m_rotRelative;
    float m_rotDegree;
    float m_rotDstDegree;
    float m_rotDstSpeed;
    int m_rotDstDir;
    int m_rotDstMode;
    char m_action[4]; // ACTION_KIND
};

struct LineupComp {
    char _gap_0[68];
    char m_ObjPos[72]; // gbVec3D[6]
    Object3D m_LineupObj;
    Object3D m_3DRole[5];
    unsigned char m_isRoleIn[5];
    Object3D m_3DNone[6];
    unsigned char m_is3DNoneIn[6];
    ObjectCamera * m_pCamera;
    float m_objCamPitch;
    float m_objRotSpeed;
    float m_pointerHeight;
    unsigned char m_isRotLineup;
    int m_RoleId;
    int m_nRole;
    unsigned char m_bClickRole;
};

struct UIRoleSelect {
    char _gap_0[80];
    int m_sel;
    int m_maxlen;
    UIListBox m_list;
    UIStaticFlex m_bk;
};

struct Comp_DonateUI {
    char _gap_0[72];
    int m_RoleId;
    char m_CompDonate[280]; // Comp_Donate_Detail[10]
    int m_keynum;
    int m_curitem;
    char m_state[40]; // Comp_DonateUI::CDState[10]
    char m_lang[20480]; // char[5][16][256]
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic m_TopFrame;
    UIButton m_ExitBtn;
    UIButton m_Btn[10];
    UIStatic m_BtnStatic[10];
    int m_mouseon;
    UIRoleDialog m_RoleDlg;
    UIRoleSelect m_SelectDlg;
    unsigned char m_IfSel;
    unsigned char m_IfGetSel;
    char m_RoleDlgRc[16]; // tagRECT
    int m_AddIntimacyDonate[5];
    int m_AddIntimacyComp[5];
    char m_RoleLang[10240]; // char[5][4][512]
    int m_SelBtn;
    MUIDialog m_Msg;
    MUIDialog m_ActiveDlg;
    MUIDialog m_ExitDlg;
    unsigned char m_IsActive;
    unsigned char m_IsOver;
    LineupComp m_LineupComp;
    UIStatic m_BK;
};

struct CEffQuad {
    char _gap_0[48];
    unsigned char m_bActive;
    unsigned char m_bVisible;
    unsigned char m_bAniFrame;
    unsigned char m_bBillBoard;
    unsigned char m_bAdditiveBlend;
    unsigned char m_bNoZTest;
    unsigned char m_byMaxFrame;
    int m_nRequireLoops;
    int m_nQuadNum;
    int m_nGeomQuadNum;
    int m_nMaxQuad;
    int m_nLastCreatedQuad;
    char m_StartQuad[80]; // tagQuad
    void * m_pQuad;
    void * m_pGeomQuad;
    int * m_pnG2Q;
    char m_DefaultUVSet[4096]; // tagUV[256]
    gbTexture * m_pTexture;
    void * m_pTextureArray;
};

struct CMeteorChain {
    CEffMgr * m_pEM;
    void * m_pGeomQuad;
    unsigned char m_bHaveTexture;
    void * m_pTextureArray;
    int m_nNumOfNode;
    void * m_pFirstNode;
    void * m_pLastNode;
    float m_fCurTime;
    float m_fLastTime;
    unsigned int m_dwColor;
    float m_fMaxLum;
    float m_fLumDecSpeed;
    float m_fMaxWidth;
    float m_fWidthDecSpeed;
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

struct CCBAttackSequen {
    CCBSystem * m_pCBSystem;
    CCBUI * m_pUI;
    CCBRoleState * m_pRole;
    char m_Sequen[440]; // tagAttackSequen[11]
    unsigned char m_bEnable;
    unsigned char m_bPause;
    unsigned char m_bVisible;
    unsigned char m_bLocked;
    char m_eLockFlag[44]; // ECBStageLockFlag[11]
};

struct UIPar_Meteor {
    char _gap_0[68];
    gbTexture * m_pTex[2];
    char m_color[4]; // gbColorQuad
    int m_nWidth;
    int m_nHeight;
    char m_StartToEnd[16]; // tagRECT
    char m_tmpPt[8]; // tagPOINT
    char m_TailPt[128]; // tagPOINT[16]
    int m_nTailNum;
    int m_ntmpTailNum;
    int m_nFrameNumBetweenTail;
    float m_fVelocityX;
    float m_fVelocityY;
    float m_passtime;
    int m_IsInMeteor;
    int m_nNextTime;
    int m_nFrame;
};

struct SceneMapObj {
    char _gap_0[16];
    Scene * m_scene;
};

struct ORect {
    char m_pt[32]; // tagPOINT[4]
    int m_numpt;
};

struct UIDragBar {
    char _gap_0[68];
    UIWnd * p_Wnd;
    unsigned int m_id;
    char m_fatherRc[16]; // tagRECT
    int m_SX;
    int m_SY;
    int m_xOffSet;
    unsigned char m_bDrag;
    unsigned char m_bClick;
    int m_DragState;
    char m_lastPt[8]; // tagPOINT
    char m_DragRc[16]; // tagRECT
    char m_bkRc[16]; // tagRECT
    char m_ProgressRc[16]; // tagRECT
    char m_DragColor[4]; // gbColorQuad
    char m_bkColor[4]; // gbColorQuad
    char m_foColor[4]; // gbColorQuad
    gbTexture * m_DragTex[3];
    void * m_DragTexInfo[3];
    gbTexture * m_pbk;
    void * m_pbkInfo;
    gbTexture * m_ppic;
    void * m_ppicInfo;
    float m_progress;
    float m_Lenth;
    float m_MaxVal;
    float m_Val;
    float m_radius;
    float m_step;
    int m_dragRadius;
    float m_lradius;
    float m_rradius;
    float m_tradius;
    float m_bradius;
    int m_mode;
    int m_dir;
};

struct UIStaticRM {
    char _gap_0[160];
    char m_color[4]; // gbColorQuad
    int m_dstAlpha;
    int m_alpha;
    int m_minAlpha;
    float m_fadespeed;
    unsigned char m_isAdd;
    unsigned char m_isFlash;
    unsigned char m_stop;
    char m_mode[4]; // UIS_RM_Mode
};

struct CEffTrackCustomShape {
    char _gap_0[172];
    t3DModel * m_pTrack;
    float m_fTrackSpeed;
    float m_fTrackDecPart;
    int m_nCurrTrackPos;
    float m_fx;
    float m_fy;
    float m_fz;
};

struct UISceneMap {
    char _gap_0[68];
    unsigned char m_bLeft;
    unsigned char m_bPlayer;
    float m_lastZ;
    char m_lastLookAt[12]; // gbVec3D
    UIButton m_probe;
    UIStatic m_base;
    UIStatic m_addin;
    UIStaticEX m_compass;
    UIStaticFlex m_mapbk;
    UITextureArray m_icons;
    int m_state;
};

struct PtrArray {
    void * m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
};

struct CG_UI {
    char _gap_0[72];
    char buf[256];
    char m_ParentRc[16]; // tagRECT
    CG_Entry * m_pFather;
    int m_SelType;
    int m_SelPropType;
    int m_nResultValue;
    int m_nWinState;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic m_pTime;
    UIStatic m_pMoney;
    UIStatic m_pTools;
    UIButton m_pItems[9];
    UIStatic m_pName;
    UIStatic m_pPrice;
    UIStatic m_pHurt;
    UIStatic m_pInfo;
    UIButton m_pBuy;
    UIButton m_pRun;
    UIStatic m_pProp;
    UIButton m_pProps[5];
    UIStatic m_pPropsNum[5];
    UIStatic m_pHP;
    UIProgressBar m_pBossHP;
    UIProgressBar m_pRoleHP;
    UIStatic m_pRoleFace;
    UIStatic m_pBossFace;
    UIStatic m_pTimeBackground;
    UIStaticRM m_pTimeHunDigit;
    UIStaticRM m_pTimeTenDigit;
    UIStaticRM m_pTimeSinDigit;
    UIStatic m_pResult;
    MUIDialog m_pWinAnswer;
    MUIDialog m_pLoseAnswer;
    MUIDialog m_pNoMoneyMsg;
    MUIDialog m_pSurpassMsg;
    MUIDialog m_pAccountMsg;
    MUIDialog m_pOverGameMsg;
    MUIDialog m_pExitDlg;
    PtrArray m_ComboBuffer;
    UISceneMap m_SceneMap;
    UIButton m_Exit;
    unsigned char m_IsExit;
    char m_InvalidRc0[16]; // tagRECT
    char m_InvalidRc1[16]; // tagRECT
    char m_InvalidRc2[16]; // tagRECT
    int m_nTimeSec;
    int m_nBossHP;
    float m_fBossHP;
    int m_nRoleFullHP;
    int m_nRoleCurHP;
    float m_ComboHitLastTime;
    float m_ComboHitTime;
    int m_nComboHit;
    int m_nTotalComboHit;
    UIStatic m_pCombo;
    unsigned char m_mouseon[9];
    int m_nPropCost;
    int m_nNoteMoney;
    PropUI * m_pBuyUI;
    unsigned char m_bRenderBuyUI;
    char m_PropData[17504]; // st_Manager
    unsigned char bUseKeyLocked;
    unsigned int m_nPropNum[5];
    unsigned int m_dwCurPropID;
};

struct C3DSpark {
    char m_Spark[7168]; // C3DSpark::tagSpark[128]
    int m_nCurrentSpark;
    gbRenderEffect * m_pAdditiveBlend;
    gbTexture * m_pRedBig;
    void * m_pRedBigArray;
    gbTexture * m_pBlue16;
    void * m_pBlue16Array;
    gbTexture * m_pGreen16;
    void * m_pGreen16Array;
    gbTexture * m_pRed16;
    void * m_pRed16Array;
    gbTexture * m_pYellow16;
    void * m_pYellow16Array;
    char m_GeomQuad[8704]; // gbGeomQuad[128]
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

struct ParticleEffect {
    char _gap_0[362836];
    int active_parnum;
    gbTexture_D3D * m_pTexture[4];
    float deltatime;
};

struct MXTransport {
    char _gap_0[92];
    float m_fTime;
    gbTexture * m_pTransTex;
    char m_aTex[68]; // gbTextureArray
    gbRenderEffect * m_pEffect;
    gbRenderEffect * m_pEffectA;
    char m_quads[408]; // gbGeomQuad[6]
    char m_quads2[408]; // gbGeomQuad[6]
    char m_trans[68]; // gbGeomQuad
    char m_height[32]; // gbVec2D[4]
    int m_ok[4];
    ParticleEffect m_test;
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

struct CEmitter {
    char _attr[220]; // CParticleSystem::EmitterAttribute
    int _nCurrTrackPos;
    float _fTrackDecPart;
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

struct sg_customshape {
    void * intervec;
    float * disarray;
    int m_iVecnum;
    char curmat[64]; // D3DXMATRIX
};

struct sg_emitter {
    char name[64];
    char relative_position[12]; // D3DXVECTOR3
    char emission_scope[12]; // D3DXVECTOR3
    char cs_name[64];
    int emitter_shape;
    float cyclelen_start;
    float cyclelen_end;
    int cycle_loop;
    int lighton;
    float m_fSpeedMulti;
    float m_fSizeMulti;
    char direction_graph[5300]; // direction_emitter_graph
    char elerandvec_graph[5300]; // elerandvec_emitter_graph
    char emissionrate_graph[5300]; // emissionrate_emitter_graph
    char elelife_graph[5300]; // elelife_emitter_graph
    char sizemulti_graph[5300]; // sizemulti_emitter_graph
    char rotmulti_graph[5300]; // rotmulti_emitter_graph
    char square[24]; // sg_emitter_square
    char sphere[8]; // sg_emitter_sphere
    sg_customshape m_pCS;
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

struct CResistanceMotionPolicy {
    char _gap_0[12];
    char _vAcceleration[12]; // gbVec3D
    float _fConstant;
};

struct Reoccupy {
    char m_id[16]; // std::vector<unsigned long,std::allocator<unsigned long> >
};

struct UICursor {
    unsigned int m_dwID[3];
    char m_active[4]; // CURSOR_TYPE
    gbTexture * m_tex[3];
    unsigned char m_bShow;
    unsigned char m_bSoftMode;
};

struct CEffgbParticle {
    char _gap_0[48];
    ParticleEffect * m_pEffect;
    float m_fSize;
    float m_fX;
    float m_fY;
    float m_fZ;
    float m_fPX;
    float m_fPY;
    float m_fPZ;
};

struct CEffect {
    char _gap_0[8];
    char m_eKind[4]; // EEffect
    unsigned char m_bActive;
    unsigned char m_bVisible;
    double m_DeltaTime;
    int m_nPartical;
    char m_Partical[98304]; // tagPartical[2048]
    int m_nQuad;
    char m_QuadBuffer[139264]; // gbGeomQuad[2048]
    int m_nQ2PIndex[2048];
    gbTexture * m_pTexture;
    void * m_pTextureArray;
};

struct CAcceleratedMotionPolicy {
    char _gap_0[12];
    char _vAcceleration[12]; // gbVec3D
};

struct UITitle_BBTY {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    UIStatic m_background;
    UIStatic m_remark;
    UIButtonEXA m_btn[3];
    UIButton m_exit;
    UIStatic m_Name;
    UIStatic m_Left;
    UIStatic m_Right;
    UIStatic m_FlagT;
    UIStatic m_FlagB;
    UIButton m_Start;
    UIButton m_Notes;
    UIButton m_Exit;
    MUIDialog m_Msg;
    char m_appr_note[8]; // _better_note
    unsigned int m_gamestate;
    unsigned char m_isgoto;
    UICoverFrm * m_pMgr;
};

struct PropUI {
    char _gap_0[72];
    int bkWndX;
    int bkWndY;
    int m_ListWidth;
    int m_ListHeight;
    char m_PropData[17504]; // st_Manager
    void * p_DealData;
    char buf[256];
    char remarkbuf[256];
    int m_SelNum;
    int * m_ListSelNum;
    int * m_MaxNum;
    int m_x;
    int m_y;
    int m_Sum;
    int i;
    int j;
    unsigned char _isCreatable;
    UIStatic m_Frame;
    UIFlexBar m_FrameBar;
    UIStatic m_Flag;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    char mb_ExitRc[16]; // tagRECT
    UIButton mb_Exit;
    UIAnimateCtrl m_ani;
    UIStatic m_Role[5];
    char m_RoleRc[80]; // tagRECT[5]
    int RoleX;
    int RoleY;
    int HeadW;
    int HeadH;
    unsigned char m_Is[5];
    MUIDialog m_Msg;
    UI3DCtrl m_3DObj;
    UIStatic m_Dlg;
    char m_DlgRc[16]; // tagRECT
    UIStatic m_TalkFrame;
    UIStatic m_Ready;
    char m_ReadyRc[16]; // tagRECT
    UIStatic m_ListFrame;
    UIStatic m_ListGrid[14];
    UIStatic m_ScrollHB;
    UIStatic m_EquipFlag;
    UIStatic m_ListPropTitle;
    char m_ListPropTitleRc[16]; // tagRECT
    UIListBox ml_ListProp;
    char ml_ListPropRc[16]; // tagRECT
    char m_btnGroup[740]; // BtnGroup
    float m_ctrlTime;
    unsigned char m_bCanUpdate1;
    unsigned char m_bCanUpdate2;
    UIStatic m_PropRemarkBk;
    UIStatic m_PropRemark;
    UIStatic m_PropAtt;
    UIStatic m_MoneyRemark;
    char m_MoneyRc[16]; // tagRECT
    UIStatic m_SumProp;
    char m_SumRc[16]; // tagRECT
    UIButton mb_OK;
    char mb_OKRc[16]; // tagRECT
    unsigned char m_IsDeal;
    UIButton mb_Cancel;
    char mb_CancelRc[16]; // tagRECT
    unsigned int * m_DealID;
    int DealNum;
    int curID;
    unsigned char m_isBuy;
    unsigned char b_IsExterior;
    int exterior_num;
    float discount_price;
    int m_extmode;
    DealUI * pDealUI;
    UITabBtn m_TabBtn;
    unsigned char m_opt;
};

struct CCBProtectWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIPushButton * m_pWHFace;
    UIPushButton * m_pWPXFace;
    UIProgressBar * m_pWHLove;
    UIProgressBar * m_pWPXLove;
    UIButton * m_pOk;
};

struct UIHeadDialog {
    char _gap_0[80];
    Role * m_role;
    int m_width;
    int m_height;
    gbTexture * m_bktex;
    char m_text[256];
};

struct ScreenFadeIn {
    char _gap_0[24];
    int m_first;
};

struct UnderWater {
    unsigned char m_bEnable;
    void * m_pIB;
    void * m_pVB;
    void * m_pBumpmapTex;
    int m_iMode;
    float m_fTime;
};

struct ComposeUI {
    char _gap_0[72];
    int m_CurRender;
    unsigned char m_isCreatable;
    UIStatic m_TopFrame;
    UIStatic m_BottomFrame;
    UIStatic m_MiddleFrame[3];
    UIButton m_Talk;
    UIButton m_Compose;
    UIButton m_Exit;
    int m_SelBtn;
    int m_RoleId;
    char m_RoleLang[2048]; // char[4][512]
    gbTexture * pInterceptTex;
    float sv;
    float ev;
    UITabBtn m_TabBtn;
    Comp_DonateUI * pC_DUI;
};

struct CCBRoleState {
    char m_sCombatDialog[512];
    float m_fLastDialogTime;
    unsigned char m_bCombatDialog;
    CCBSystem * m_pCBSystem;
    CCBStage * m_pStage;
    CCBUI * m_pUI;
    void * m_pUtil;
    unsigned char m_bWeSneakAttackEnemy;
    unsigned char m_bEnemySneakAttackUs;
    int m_nMaxRound;
    int m_nBossRound;
    unsigned char m_bMustFail;
    unsigned char m_bFleeAlwaysSuccess;
    unsigned char m_bCreatedNewRole;
    char m_Role[11440]; // tagRoleState[11]
    char m_RoleXor[11440]; // tagRoleState[11]
    unsigned int m_dwEXPTable[100];
    unsigned int m_dwWinTaskID;
    int m_bNGHDeadVariance;
    char m_eSameRow[36]; // ECBFiveLineup[3][3]
    char m_eSameColumn[24]; // ECBFiveLineup[3][2]
    float m_fSwordStarTime;
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

struct UITabCtrl {
    char _gap_0[68];
    int m_itemwidth;
    UITextureArray m_texarray;
    int m_numpage;
    int m_onpage;
};

struct CEffSParticle {
    char _gap_0[48];
    CParticleEffect * m_pEffect;
    char m_vecPos[12]; // gbVec3D
    float m_fX;
    float m_fY;
    float m_fZ;
    float m_fPX;
    float m_fPY;
    float m_fPZ;
    float m_fRotX;
    float m_fRotY;
    float m_fRotZ;
};

struct CEffCylinder {
    char _gap_0[48];
    void * m_pGeomQuad;
    gbTexture * m_pTexture;
    void * m_pTextureArray;
    unsigned char m_bVisible;
    unsigned char m_bAdditiveBlend;
    unsigned char m_bNoZTest;
    unsigned char m_byMaxFrame;
    int m_nRequireLoops;
    int m_nLoops;
    float m_fCurFrame;
    unsigned int m_dwStartColor;
    float m_fAlpha;
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fSize;
    float m_fHeight;
    float m_fRotAngle;
    float m_fWide;
    int m_nDivision;
    float m_fTopShrink;
    float m_fBottomShrink;
    float m_fTopRadius;
    float m_fBottomRadius;
    float m_fTopRadiusIncSpeed;
    float m_fBottomRadiusIncSpeed;
    float m_fTopRiseSpeed;
    float m_fBottomRiseSpeed;
    float m_fTextureRepeat;
    float m_fFramePerSec;
    float m_fCurTextureV;
    char m_vecRot[12]; // gbVec3D
    char m_vecPos[12]; // gbVec3D
    char m_vecOffsetPos[12]; // gbVec3D
    char m_DefaultUVSet[4096]; // tagUV[256]
};

struct GRPinput {
    void * m_lpDI;
    void * m_lpDIDKeyboard;
    void * m_lpDIDMouse;
    float m_mouseSensitivity;
    long m_mouseMinX;
    long m_mouseMinY;
    long m_mouseMaxX;
    long m_mouseMaxY;
    long m_joystickMinX;
    long m_joystickMinY;
    long m_joystickMaxX;
    long m_joystickMaxY;
    char m_mousept[8]; // tagPOINT
    long m_mouseX;
    long m_mouseY;
    long m_mouseFreeX;
    long m_mouseFreeY;
    long m_mouseDeltaX;
    long m_mouseDeltaY;
    long m_joystickX;
    long m_joystickY;
    long m_joystickFreeX;
    long m_joystickFreeY;
    long m_joystickDeltaX;
    long m_joystickDeltaY;
    unsigned char m_keyStates[270];
    unsigned char m_keyRaw[256];
    unsigned int m_keyPressTimes[270];
    char m_keyDragStartPositions[2160]; // ulong[270][2]
    unsigned char m_shiftedKeyStates[270];
    unsigned int m_DIKToKEY[256];
    char MouseState[20]; // _DIMOUSESTATE2
    unsigned int charTOscan[256];
    int KeyTransformation[10];
    int m_bMouse;
    int m_bKeyboard;
    int m_bJoystick;
    char KeyInfo[4320]; // GRP_KEYREG[270]
};

struct RestScript {
    TxtFile m_LoadRest;
    char m_lastFile[256];
    char m_Data[1288]; // ScriptData
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

struct UIAnimate {
    unsigned int m_sec;
    char m_Rc[16]; // tagRECT
    char m_Rc2[16]; // tagRECT
    unsigned char m_IsLoop[4];
    TimeCtl m_Time;
};

struct CEffectSystem {
    gbGfxManager * m_pDisplay;
    gbDynVertBuf * m_pVertexBuffer;
    gbRenderEffect * m_pAdditiveBlend;
    gbRenderEffect * m_pAlphaBlend;
    char m_DefaultUVSet[256]; // tagUVSet[16]
    unsigned char m_bInitialized;
    int m_nEffect;
    CEffect * m_pEffect[8];
    double m_dDeltaTime;
    double m_dTimeFund;
    float m_fTimeFund;
    float m_fTimeScale;
    float m_fWindDirection;
    float m_fWindSpeed;
};

struct gbBinkVideo {
    char _gap_0[4];
    char m_pos[8]; // tagPOINT
    void * m_hBink;
    CPK m_Cpk;
    CPK m_Cpk2;
};

struct UIStaticCB {
    char _gap_0[160];
    int m_showct;
};

struct UIPushButton {
    char _gap_0[68];
    unsigned char m_isDown;
    unsigned char m_isCtrl;
    unsigned char m_mouseoff;
    char m_fontcolor[4]; // gbColorQuad
    char m_fonttype[4]; // gbFontType
    char m_state[4]; // UIPushButton::UIPUSHBUTTON_STATE
    gbTexture * m_texarray[2];
    void * m_texarrayInfo[2];
    unsigned char m_bOn;
    gbTexture * m_onpic;
    void * m_onpicInfo;
    gbTexture * m_disablepic;
    void * m_disablepicInfo;
    char m_caption[128];
    int m_TextTopOffset;
};

struct ProtectPanel {
    char _gap_0[72];
    UIStatic m_BK;
    UIPushButton m_WHFace;
    UIPushButton m_WPXFace;
    UIProgressBar m_WHFavor;
    UIProgressBar m_WPXFavor;
    char m_WHFaceRc[16]; // tagRECT
    char m_WHFavorRc[16]; // tagRECT
    char m_WPXFaceRc[16]; // tagRECT
    char m_WPXFavorRc[16]; // tagRECT
};

struct MainEquipUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    unsigned char m_IsMsg;
    unsigned char m_Is[5];
    unsigned char m_IsActive;
    unsigned char m_IsCreateable;
    int m_SelNum;
    int m_PutOnType;
    char m_CurType[4]; // PlayerItem_Type
    StateUI * pStateUI;
    UIStatic m_Frame;
    UIStatic m_TimeMoney;
    UIStatic m_TopFrame;
    UIStatic m_TopFrameZB;
    UIStatic m_ScrollHB;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic stp_BarL;
    UIFlexBar stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_TaskBook;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    UIStatic m_GameTime;
    UIStatic m_GameMoney;
    MUIDialog m_DlgEx;
    char m_btnPar[66304]; // UIParticle[7][16]
    char m_btnPar2[66304]; // UIParticle[7][16]
    char m_btnParRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    char me_Role[48500]; // me_RoleState[5]
    UIStatic m_WeaponName;
    UIStatic m_ClothName;
    UIStatic m_ShoesName;
    UIStatic m_HatName;
    UIStatic m_Adorn1Name;
    UIStatic m_Adorn2Name;
    UIStatic m_RemarkBk;
    UIStatic m_Remark;
    UIStatic m_RemarkVal;
    UIStatic m_typeWord;
    char m_remarkRc[16]; // tagRECT
    char m_role[4260]; // RoleAtt[5]
    MUIDialog m_Dlg;
    UIButton m_Ctrlbtn[5];
    UIStatic m_ClothIcon;
    UIStatic m_HatIcon;
    UIStatic m_ShoesIcon;
    UIStatic m_WeaponIcon;
    UIStatic m_AdornIcon1;
    UIStatic m_AdornIcon2;
    char m_SelRc[16]; // tagRECT
    UIButton m_SelRole[5];
    int m_CurSelRole;
    UIFlexBar m_ListTitle;
    UIStatic m_ListFrame;
    UIStatic m_ListGrid[14];
    UIStatic m_title;
    UIListBox ml_Equiplist;
    int last_index;
    char m_SortRc[16]; // tagRECT
    UIButton mb_SortDefault;
    UIButton mb_SortPrice;
    UIButton mb_SortUse;
    int m_SortState;
    UI3DCtrl m_3DObj;
};

struct C2DSpark {
    char m_Spark[24576]; // C2DSpark::tagSpark[512]
    float m_fDisplayWidth;
    float m_fDisplayHeight;
    int m_nCurrentSpark;
    float m_fBigLum;
    int m_nBigLumX;
    int m_nBigLumY;
    unsigned char m_bMouseTrack;
    gbRenderEffect * m_pAdditiveBlend;
    gbTexture * m_pRedBig;
    void * m_pRedBigArray;
    gbTexture * m_pBlue16;
    void * m_pBlue16Array;
    gbTexture * m_pGreen16;
    void * m_pGreen16Array;
    gbTexture * m_pRed16;
    void * m_pRed16Array;
    gbTexture * m_pYellow16;
    void * m_pYellow16Array;
    char m_Quad[40]; // gbUIQuad
};

struct CEffTrackCylinder {
    char _gap_0[4292];
    t3DModel * m_pTrack;
    float m_fTrackSpeed;
    float m_fTrackDecPart;
    int m_nCurrTrackPos;
    float m_fx;
    float m_fy;
    float m_fz;
};

struct CEffCustomShape {
    char _gap_0[48];
    unsigned char m_bVisible;
    char m_vecPos[12]; // gbVec3D
    char m_vecOffsetPos[12]; // gbVec3D
    char m_vecRot[12]; // gbVec3D
    float m_fAlpha;
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fScaleX;
    float m_fScaleY;
    float m_fScaleZ;
    t3DModel * m_pModel;
    gbTexture * m_pTexture;
    gbRenderEffect * m_pRenderEffect;
    gbIndexBubble * m_pIndexBubble;
    int m_nCurrFrame;
    int m_nFrameNum;
    float m_fFrameU;
    float m_fFrameV;
    float m_fSpeed;
    float m_fTimeCount;
    char m_UVData[16]; // std::vector<gbVec2D,std::allocator<gbVec2D> >
};

struct SkyboxEffMgr {
    float m_fSkyboxSize;
    SkyboxEff m_pEffArray[54];
};

struct MyMdl {
    int m_mdltype;
    gbActor * m_actor;
    gbGeomNode * m_geom;
    MeshFx * m_fx;
    char box[76]; // gbOBBox
};

struct SceneObj {
    char _gap_0[76];
    char _SaveTaskInfo[12]; // SaveTask
    float m_fTime;
    float m_fDeltaTime;
    float m_fTimeScale;
    float m_deltatime;
    int m_bLockPropUI;
    unsigned char m_bLockCamera;
    int m_bProcessLinkObj;
    int m_bCallProcessGroupObj;
    int m_bMainGroupObj;
    unsigned int dwEffGroupRunningID;
    unsigned char bCGObj;
    char sCGSHELF[64];
    char rCGSelfArea[16]; // tagRECT
    char rTouchAreaCG[16]; // tagRECT
    float fLastTime;
    char mParam[72]; // subPARAM
    char mVelocity[12]; // gbVec3D
    float mTime;
    char mStorePos[12]; // gbVec3D
    int mRetrorse;
    int mTouchCounter;
    int m_iState;
    unsigned char m_bCVDOver;
    char mOBBox[76]; // gbOBBox
    char m_pObjMsgBuffer[256];
    char m_pObjMsgBuffer2[256];
    char m_renderpos[12]; // gbVec3D
    char m_subobj[36]; // SceneObj::SubObj
    MyMdl m_mdl;
    char m_info[604]; // ObjectInfo
    void * m_path;
    SceneMapObj * m_pmap;
    unsigned char m_mapindex;
    int m_pushboxdir;
    char m_maprect[16]; // tagRECT
    int m_liftrole;
    char m_common[48]; // std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >
    gbSound3DNode * m_snd;
    float m_radius;
    PalScript * m_runscript;
    float m_fRotateX;
    float m_fRotateY;
    float m_fRotateZ;
    float m_fParam;
};

struct NavigationInfo {
    int m_numlayer;
    char m_tilelayer[328]; // NavTileLayer[2]
    char m_facelayer[32]; // NavFaceLayer[2]
};

struct Actor {
    char m_actarray[16]; // std::vector<gbActor *,std::allocator<gbActor *> >
    gbActor * m_pact;
    char m_name[260];
    char m_szTexture[260];
    unsigned int m_dwMatMsg[11];
    unsigned char m_bChangedMat;
    char m_curact[8];
};

struct Role {
    char _gap_0[96];
    char m_cmdqueue[48]; // std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >
    int m_bInView;
    char m_groundpos[12]; // gbVec3D
    char m_renderpos[12]; // gbVec3D
    char m_npcinfo[456]; // NPCInfo
    int m_onlayer;
    int m_active;
    unsigned char bCGMonster;
    int nCGMonsterID;
    int nCGMonsterType;
    unsigned char bRelive;
    unsigned char bInvincible;
    float fRattrapWait;
    float fMirrorWait;
    unsigned char bMirror;
    float fCGBIXIE;
    unsigned char bCGBIXIE;
    unsigned char bCrossAlpha;
    float fCrossAlpha;
    unsigned char bCGMonsterHitObj;
    unsigned char bStill;
    void * pCG_SceneProp;
    Actor m_actor;
    unsigned char m_MachineryID;
    int m_bPet;
    float m_scale;
    char m_tri[36]; // NavTriangle
    char m_specact[36]; // Role::SPECIAL_ACTION
    char m_ctrlmode[4]; // ROLE_CTRL
    char m_curbehaviour[4]; // ROLE_BEHAVIOUR
    int m_bPathOut;
    int m_bShowActAutoStand;
    unsigned char m_bNeedShowActEnd;
    char m_curact[4]; // ACTION_KIND
    float m_curspeed;
    float m_curforce;
    char m_velocity[12]; // gbVec3D
    char m_desirevel[12]; // gbVec3D
    char m_steer[12]; // gbVec3D
    char m_lastautodir[12]; // gbVec3D
    char m_targetpt[12]; // gbVec3D
    int m_targetlayer;
    int m_targetportal;
    char m_startpt[12]; // gbVec3D
    char m_wanderdir[12]; // gbVec3D
    int m_talkflag;
    Role * m_talknpc;
    PalScript * m_talkscript;
    char m_talkoldbeh[4]; // ROLE_BEHAVIOUR
    char m_talkoldact[4]; // ACTION_KIND
    float m_talkoldface;
    SceneObj * m_talkobj;
    int m_mstate;
    void * m_matt;
    float m_mfreedist;
    float m_mattackrange;
    float m_mfindradius;
    float m_statetime;
    gbGeomNode * m_weapon;
    unsigned char m_bLeftWeapon;
    unsigned char m_bRightWeapon;
    int m_nRad;
    int m_nRealHeadPos;
    int m_nOverlapState;
    char m_tpos[8]; // tagPOINT
    char m_vTagHeadPos[12]; // gbVec3D
    int m_overlap;
    int m_bPathMove;
    int m_pathMoveCounter;
    char m_lastpos[12]; // gbVec3D
    char m_notePos[12]; // gbVec3D
    char m_path[7208]; // PathObj
    float m_rotate;
    char m_wanapos[12]; // gbVec3D
};

struct Scene {
    char m_info[132]; // SceneInfo
    gbGeomNode * m_geomnode;
    gbVisNode * m_lights;
    char m_aabb[24]; // gbAABBox
    PtrArray m_bbArray;
    SceneMapObj m_objmap[2];
    int m_numobj;
    SceneObj m_obj[256];
    int m_numnpc;
    Role m_npc[72];
    NavigationInfo m_nav;
    gbGeomNode * m_cvd;
    NavigationInfo m_CamCollide;
    unsigned char m_bHasNavCollide;
    int m_bLoad;
    int m_battached;
    unsigned char m_lastobj;
    int m_bStar;
};

struct CCBEditor {
    CCBSystem * m_pCBSystem;
    CCBRoleState * m_pRoleState;
    char m_NewItem[8000]; // tagNewItem[500]
    int m_dwSelectFighter[11];
    int m_nCurCCTList;
    int m_nCurCCT;
    int m_nCurEffClass;
    int m_nCurEffObjType;
    int m_nCurEffGroup;
    int m_nCurEffObjInGroup;
    int m_nCurEffObjTask;
    unsigned int m_dwTrickID[384];
    int m_nCurSelectedEffGroup;
    int m_nCurSelectedTrick;
};

struct _Item_List_Info {
    char _gap_0[72];
    UIStatic m_background;
    unsigned char m_IsActive;
    _Item * m_pItem;
    UIButton m_BtnItem[12];
    UIStatic ms_Title;
    UIStatic ms_Info;
    UIStatic ms_Pic;
    UIButton mb_Prev;
    UIButton mb_Next;
    UIButton mb_Back;
    int m_SelItemNum;
    int m_SelFocusOn;
};

struct CIniFile {
    void * m_fp;
    int m_bRead;
};

struct UIEmote {
    char _gap_0[76];
    char m_cur[4]; // UIEMOTE
    UIAnimateCtrl m_ani[14];
    Role * m_role;
    int m_loopcount;
    int m_nLoop[14];
};

struct CCBStageCam {
    char _gap_0[692];
    CCBStage * m_pStage;
    void * m_pUtil;
    float m_fLastMouseX;
    float m_fLastMouseY;
    void * m_fp;
    int m_nTask;
    int m_nCurTask;
    char m_Task[4000]; // tagCamTask[50]
    char m_EditorCam[1536]; // tagCam[64]
};

struct HeadMsg {
    char _gap_0[4];
    unsigned char m_bEnable;
    char m_szMsg[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    float m_fTime;
    int m_nType;
    int m_nY;
    UIStatic * m_pMsgDlg;
    int m_nMsgWidth;
    int m_nMsgHeight;
    int m_nShowPointW;
    float m_fHeadModeTime;
    float m_fAttenSpeed;
    unsigned char m_bAtten;
    unsigned char m_ucAlpha;
    Role * m_pRole;
};

struct COnceFramePolicy {
    char _gap_0[12];
    float _fSpeed;
};

struct scSCEFile {
    void * m_fp;
    char m_blocks[16]; // std::vector<scScriptBlock *,std::allocator<scScriptBlock *> >
    unsigned short m_blocknum;
    void * m_pindex;
};

struct UITitle_JDHY {
    char _gap_0[72];
    char rc[16]; // tagRECT
    char buf[256];
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic m_background;
    UIButton m_exit;
    unsigned char m_isItemShow[99];
    char m_NoteItem[369072]; // Note_Item[99]
    UIStatic m_Title_JDHY;
    UIStatic m_TopBar;
    UIStatic m_BottomBar;
    UIStatic m_BackBar;
    UIStatic m_BackBar2;
    UIPushButton m_pbPage[10];
    UIScrollBar m_Scroll;
    int m_CurScrollPos;
    int m_ItemH;
    int m_ItemW;
    int m_firstItem;
    int m_selItem;
    int m_getNote;
    int m_loading;
    float m_passtime;
    UIButton m_LoadBtn;
    UIButton m_DeleteBtn;
    char m_noteState[4]; // NOTE_STATE
    MUIDialog m_YesNo;
    MUIDialog m_MsgBox;
    int m_IsArcSave;
    int m_IsReadFinishSave;
    int m_nShowNoteNum;
    UICoverFrm * m_pMgr;
    UILoadingFrm * m_pLoadingFrm;
};

struct SwitchVariable {
    unsigned int m_switchlimit;
};

struct CCBParabolaWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIStatic * m_pDescription;
    UIListBox * m_pItemList;
};

struct BillBoardFace {
    char m_texarray[68]; // gbTextureArray
    int m_curtex;
    int m_id;
    char m_pos[12]; // gbVec3D
    gbRenderEffect * m_effect;
};

struct gbChain1D {
    gbChain1DNode * m_Head;
    gbChain1DNode * m_Tail;
    int m_numNode;
    gbChain1DNode * m_Cur;
};

struct gbNBTreeNode {
    char _gap_0[8];
    gbNBTreeNode * pFather;
    gbChain1D Children;
};

struct ARC_Reoccupy {
    char m_id[16]; // std::vector<unsigned long,std::allocator<unsigned long> >
};

struct gbTexture_D3D {
    char _gap_0[84];
    void * pTex;
    void * pDS;
    unsigned int m_ImgFormat;
};

struct RenderTarget {
    int m_iMode;
    gbTexture_D3D m_Texture;
    gbTexture_D3D m_ScreenPlane;
    int m_nState;
};

struct std::runtime_error {
    char _gap_0[12];
    char _Str[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
};

struct CEffShock {
    char _gap_0[48];
    char m_DefaultUVSet[4096]; // tagUV[256]
    gbTexture * m_pTexture;
    void * m_pTextureArray;
    int m_nMaxGeomQuad;
    void * m_pGeomQuad;
    void * m_pShock;
    unsigned char m_bVisible;
    unsigned char m_bAdditiveBlend;
    unsigned char m_bNoZTest;
    float m_fFramePerSec;
    unsigned char m_byMaxFrame;
    int m_nRequireLoops;
    int m_nLoops;
    float m_fCurFrame;
    unsigned int m_dwStartColor;
    float m_fAlpha;
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fSize;
    char m_vecRot[12]; // gbVec3D
    char m_vecPos[12]; // gbVec3D
    char m_vecOffsetPos[12]; // gbVec3D
    int m_nNodeOfShock;
    int m_nCascade;
    float m_fWidthOfNode;
    float m_fHeightOfNode;
    float m_fSpeedOfDisappear;
    float m_fInterleaving;
};

struct gbKeyControler {
    char _gap_0[4];
    void * pKeys;
    int KeySize;
    char KeyType[4]; // gbKeyType
    int nKey;
};

struct gbSound2DNode {
    gbSoundData * pData;
    void * hSample;
    int nLoop;
    float Volume;
};

struct util {
    unsigned int Crc32Table[256];
    unsigned int m_dwIDHolder;
    int m_nRandHolder;
    int m_nRandCallCount;
    CIniFile * m_pIniReader;
    CLoad3DS * m_pLoader3DS;
};

struct CEffCallBack {
    char _gap_0[48];
    float m_fStartX;
    float m_fStartY;
    float m_fStartZ;
    unsigned int m_dwRunningID;
};

struct CFadeColorPolicy {
    char _gap_0[12];
    char _vBeginColor[12]; // gbVec3D
    char _vEndColor[12]; // gbVec3D
};

struct CCBSystem {
    void * m_pUtil;
    CCBUI * m_pUI;
    CCBControl * m_pControl;
    CCBAttackSequen * m_pAttackSequen;
    CCBRoleState * m_pRoleState;
    CCBStage * m_pStage;
    CCBAI * m_pAI;
    CCBEditor * m_pEditor;
    CEffectSystem * m_pES;
    void * m_pEffectSimple;
    TxtFile * m_pConfig;
    CEffMgr * m_pEffMgr;
    CEffMgr * m_pATSEffMgr;
    C2DSpark * m_p2DSpark;
    C3DSpark * m_p3DSpark;
    double m_DeltaTime;
    double m_dTimeFund;
    float m_fTimeFund;
    double m_AbsDeltaTime;
    double m_dAbsTimeFund;
    float m_fAbsTimeFund;
    float m_fTimeScale;
    void * m_pFightInfo;
    unsigned char m_bQuitFlag;
    unsigned char m_bPause;
    char m_eState[4]; // ECBCombatState
    char m_eResult[4]; // ECBCombatResult
    unsigned char m_bFiveNimbus;
    unsigned char m_bPXVariance;
    int m_nTimesOfCombat;
    unsigned char m_bAuto;
    unsigned char m_bEditor;
    unsigned char m_bLockCam;
    unsigned char m_bFirstRender;
    unsigned int m_dwIDHolder;
    int m_nThread;
    int m_nCurThread;
    char m_Thread[90112]; // tagThread[1024]
    char m_Player[576]; // tagPlayerSet[11]
};

struct _Console {
    int m_numcmd;
    char m_cmd[8704]; // _Console::_ConCmd[64]
    char m_rect[16]; // tagRECT
    int m_bactive;
    int m_bEnable;
    char m_color[4]; // gbColorQuad
    char m_inputbuf[100];
    char m_showbuf[1700]; // char[17][100]
    char m_fontcolor[4]; // gbColorQuad
};

struct StringTable {
    char m_data[16]; // std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:83de5b43
};

struct gbSnow {
    char _gap_0[80];
    float m_VelXZ;
};

struct SceneMap {
    char _gap_0[4];
    int m_width;
    int m_height;
    unsigned char * m_map;
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

struct RoleCamera {
    char _gap_0[380];
    Role * m_ptarget;
    SceneObj * m_pobj;
    char m_targetpos[12]; // gbVec3D
    char m_lastFrom[12]; // gbVec3D
    char m_fromVec[12]; // gbVec3D
    float m_yaw;
    float m_fCtrlYaw;
    float m_dist;
    float m_pitch;
    float m_roll;
    float m_nextYAW;
    float m_lastYAW;
    char m_camVelocity[12]; // gbVec3D
    char m_argstack[48]; // std::stack<RC_ARG,std::deque<RC_ARG,std::allocator<RC_ARG> > >
    int m_bFree;
    int m_bLockForward;
    int m_bLockCenter;
    int m_bProcessCollision;
    int m_CollideTriangleNum;
    char polygonList[16]; // std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >
    char polygonListBackup[16]; // std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >
    char m_CollideData[12]; // std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >
    int m_clientwidth;
    int m_clientheight;
    unsigned char CAMERA_LOCK_HALFRADIUS;
    unsigned char CAMERA_COLLIDE_METHOD;
    char m_lookat[12]; // gbVec3D
    char m_from[12]; // gbVec3D
    char m_forward[12]; // gbVec3D
    char m_up[12]; // gbVec3D
    char m_side[12]; // gbVec3D
    char m_LockForward[12]; // gbVec3D
    char m_LockCenter[12]; // gbVec3D
    unsigned char m_bCollide;
    float m_roomHeight;
    char m_lastUP[12]; // gbVec3D
};

struct Archive {
    char m_scene[16]; // std::vector<ArcScene,std::allocator<ArcScene> >
    char m_past[16]; // std::vector<ArcPastScene,std::allocator<ArcPastScene> >
    char m_objNotLoad[16]; // std::vector<unsigned long,std::allocator<unsigned long> >
};

struct CPolicy {
    char _gap_0[4];
    CParticleSystem * _pParticleSystem;
    unsigned int _dwPolicyId;
};

struct MXFire {
    char _gap_0[92];
    int m_nCurTex;
    float m_fTime;
    gbRenderEffect * m_pEffect;
    gbTexture * m_pTexs[16];
    char m_ta[68]; // gbTextureArray
    gbTexture * m_pFlare;
    gbGeomNode * m_candle;
    unsigned int m_type;
};

struct CCBAIWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIStatic * m_pName[5];
    UIPushButton * m_pAttack;
    UIPushButton * m_pItem;
    UIPushButton * m_pSkill;
    UIPushButton * m_pMagic;
    UIPushButton * m_pAffirmative;
    UIPushButton * m_pAI;
    UIButton * m_pOk;
    int m_nIndex;
};

struct gbPrintFontMgr {
    gbPrintFont * pAllFont[5];
};

struct LineupUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    unsigned char m_IsMsg;
    unsigned char m_Is[5];
    UIStatic m_Frame;
    UIStatic m_TimeMoney;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic stp_BarL;
    UIFlexBar stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_TaskBook;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    UIStatic m_GameTime;
    UIStatic m_GameMoney;
    MUIDialog m_DlgEx;
    UIStatic m_ZhenLie;
    char m_btnPar[66304]; // UIParticle[7][16]
    char m_btnPar2[66304]; // UIParticle[7][16]
    char m_btnParRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    char m_LineupInfo[30]; // LINEUPINFO[5]
    char m_Sequence[6]; // LINEUP_SEQUENCE
    char roleRc[16]; // tagRECT
    UIStatic m_RoleFrame;
    UIButton m_RoleBtn[5];
    int m_RoleBtnIndex[5];
    UIStatic m_NoBody[5];
    UIStatic m_RoleLeader[5];
    char m_headRc[80]; // tagRECT[5]
    int m_headRole;
    MUIDialog m_Msg;
    float m_objCamPitch;
    float m_objRotSpeed;
    ObjectCamera * m_pCamera;
    float m_pointerHeight;
    unsigned char m_bPeek;
    int m_nPeek;
    int m_nLastPeek;
    unsigned char m_isRotLineup;
    char m_ObjPos[72]; // gbVec3D[6]
    Object3D m_LineupObj;
    Object3D m_3DRole[5];
    unsigned char m_IsRole[6];
    int m_RoleId[6];
    Object3D m_3DNone[6];
    char m_CtrlPlank[9960]; // LineupPlank[5]
    ProtectPanel m_ProtectPanel;
    unsigned char m_ProFlag;
    StateUI * pStateUI;
};

struct CEffBink {
    char _gap_0[48];
    char m_szBinkNamePrefix[128];
    char m_szBinkName[128];
};

struct UIButtonEX {
    char _gap_0[344];
    char m_optData[48]; // _btnOPTDATA[3]
};

struct SaleUI {
    char _gap_0[72];
    int bkWidth;
    int bkHeight;
    char buf[256];
    char remarkbuf[256];
    int m_SelNum;
    char m_data[17504]; // st_Manager
    char m_sort[11960]; // SaleUI::SortData[5][299]
    char m_ListSelNum[5980]; // int[5][299]
    char m_Max[5980]; // int[5][299]
    int m_Sum[5];
    unsigned char _isCreatable;
    char m_SaleData[17940]; // PlayerItem[5][299]
    char m_TempData[17940]; // PlayerItem[5][299]
    char m_NotesNull[5980]; // int[5][299]
    char m_IsEquip[1495]; // uchar[5][299]
    char m_TempIsEquip[1497]; // uchar[5][299]
    int x;
    char rc[16]; // tagRECT
    UIStatic m_Frame;
    UIFlexBar m_FrameBar;
    UIStatic m_Flag;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIButton mb_Exit;
    char m_ExitRc[16]; // tagRECT
    UIAnimateCtrl m_ani;
    UIStatic m_Role[5];
    char m_RoleRc[80]; // tagRECT[5]
    int RoleX;
    int RoleY;
    int HeadW;
    int HeadH;
    unsigned char m_Is[5];
    MUIDialog m_Msg;
    UI3DCtrl m_3DObj;
    char m_FlagRc[16]; // tagRECT
    UIStatic m_TalkFrame;
    UIStatic m_Ready;
    char m_ReadyRc[16]; // tagRECT
    char m_entryTalk[256];
    UIButton m_btn[5];
    char m_TabRc[16]; // tagRECT
    UIStatic m_ListSaleTitle;
    char m_ListEquipTitleRc[16]; // tagRECT
    char m_Icon[4700]; // UIStaticRM[5][5]
    UIStatic m_ListFrame;
    UIStatic m_ScrollHB;
    UIStatic m_ListGrid[14];
    char m_ListRc[16]; // tagRECT
    UIListBox ml_ResumeList;
    int ResumeNum;
    UIListBox ml_TreasureList;
    int TreasureNum;
    UIListBox ml_AttackList;
    int AttackNum;
    UIListBox ml_SmeltList;
    int SmeltNum;
    UIListBox ml_AncientList;
    int AncientNum;
    UIListBox ml_EquipList;
    int EquipNum;
    int curPage;
    int curNum;
    char m_btnGroup[740]; // BtnGroup
    float m_ctrlTime;
    unsigned char m_bCanUpdate1;
    unsigned char m_bCanUpdate2;
    UIButton m_Sortfunc;
    UIButton m_Sortprice;
    int m_sortstate;
    char m_ButtonRc[16]; // tagRECT
    UIButton mb_OK;
    UIButton mb_Cancel;
    UIStatic m_SaleRemarkBk;
    UIStatic m_SaleRemark;
    UIStatic m_ItemFlag;
    char m_RemarkRc[16]; // tagRECT
    UIStatic m_SaleAtt;
    char m_SaleAttRc[16]; // tagRECT
    UIStatic m_MoneyRemark;
    char m_MoneyRc[16]; // tagRECT
    UIStatic m_SumSale;
    char m_SumRc[16]; // tagRECT
    unsigned char b_IsAdd;
    unsigned char b_IsSub;
    int m_extmode;
    DealUI * pDealUI;
    void * pEntryUI;
    unsigned char m_IsSale;
    int m_curPage;
    UITabBtn m_TabBtn;
    unsigned char m_opt;
};

struct CPKFile {
    unsigned char bValid;
    unsigned int dwCRC;
    unsigned int dwFatherCRC;
    int nTableIndex;
    void * lpMapAddress;
    void * lpStartAddress;
    unsigned int dwOffset;
    unsigned char bCompressed;
    void * lpMem;
    unsigned int dwFileSize;
    unsigned int dwPointer;
    void * pTableItem;
};

struct CEffTrackSParticle {
    char _gap_0[100];
    t3DModel * m_pTrack;
    float m_fTrackSpeed;
    float m_fTrackDecPart;
    int m_nCurrTrackPos;
};

struct ChoseCompose {
    char _gap_0[80];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    char bkRc[16]; // tagRECT
    unsigned int m_id;
    unsigned char m_isExit;
    UIStaticFlex m_bk;
    UIStatic m_ComposeInfo;
    UIButton m_RoleName[5];
    MUIDialog m_Msg;
    unsigned char m_isCtrl[5];
    unsigned char m_isActive;
    unsigned char m_isExtented;
};

struct CParticleSystem {
    int _bVisible;
    int _bPlay;
    int _bCycle;
    int _bManual;
    char _strParticleName[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    unsigned int _dwParticleId;
    CPolicy * _pPositionPolicy;
    CPolicy * _pDirectionPolicy;
    CPolicy * _pColorPolicy;
    CPolicy * _pAlphaPolicy;
    CPolicy * _pFramePolicy;
    CPolicy * _pEmitterPolicy;
    void * _pParticles;
    CEmitter * _pEmitter;
    char _KeyFrames[16]; // std::vector<KeyFrame *,std::allocator<KeyFrame *> >
    int _nNumOfParticles;
    int _nMaxNum;
    unsigned int _dwNumOfKeyFrames;
    unsigned int _dwNumOfUnitFrames;
    int _nCurrFrame;
    int _nLastFrame;
    float _fTimeCounter;
    float _fEmitDecPart;
    unsigned int _dwVBFlush;
    char _matTransform[64]; // gbMatrix4
    float _fWidthScale;
    float _fHeightScale;
    char _TexCoordData[16]; // std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >
    gbTexture * _pTexture;
    gbRenderEffect * _pRenderEffect;
    gbGfxManager * _pGfxMgr;
};

struct CCBMagicWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIListBox * m_pMagicList[6];
    UIPushButton * m_pButtonWater;
    UIPushButton * m_pButtonFire;
    UIPushButton * m_pButtonThunder;
    UIPushButton * m_pButtonWind;
    UIPushButton * m_pButtonEarth;
    UIPushButton * m_pButtonDouble;
    int m_nActivePage;
};

struct MXSavePoint {
    char _gap_0[92];
    float m_fTime;
    char m_aTex[68]; // gbTextureArray
    gbTexture * m_pTex;
    gbRenderEffect * m_pEffect;
    char m_trans[68]; // gbGeomQuad
    char m_quads[816]; // gbGeomQuad[12]
    gbGeomNode * m_stone;
};

struct CCBSkillWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIStatic * m_pDescription;
    UIListBox * m_pSkillList[1];
};

struct GlowObj {
    char _gap_0[4];
    unsigned char m_bEnable;
    int m_nStepSize;
    int m_nPass;
    char m_GeomColor[16]; // gbColorFlt
};

struct std::locale::id {
    unsigned int _Id;
};

struct gbTexture {
    char _gap_0[24];
    int Width;
    int Height;
    gbImage2D * pTexImage;
    gbPixelFormat InFmt;
    int nLevels;
};

struct CEffTrackGrid {
    char _gap_0[4280];
    t3DModel * m_pTrack;
    float m_fTrackSpeed;
    float m_fTrackDecPart;
    int m_nCurrTrackPos;
    float m_fx;
    float m_fy;
    float m_fz;
};

struct sg_particle {
    char particle_name[32];
    int particle_lighting;
    float gravity;
    float noresis;
    int aresis_velocity;
    int aresis_size;
    float aresis_constant;
    char filename[256];
    int particlesize;
    int framenums;
    int framesets;
    int animation_type;
    int animation_fps;
    int random_1stframe;
    int random_rotstart;
    int random_rotend;
    int random_rotdir;
    int random_mirroringx;
    int random_mirroringy;
    float m_fSizeMulti;
    int chainnum;
    int framenum;
    int blendmode;
    char size_graph[5300]; // size_particle_graph
    char rotation_graph[5300]; // rotation_particle_graph
    char vertexalpha_graph[5300]; // vertexalpha_particle_graph
    char rgbcolor_graph[5300]; // rgbcolor_particle_graph
};

struct ScreenEffect {
    char _gap_0[8];
    int m_blive;
    float m_life;
    float m_age;
    unsigned char m_hold;
};

struct UICaption {
    char _gap_0[76];
    gbTexture * m_tex;
    int m_numline;
    int m_lineheight;
    int m_curline;
    float m_linetime;
    gbTexture * m_tex2;
    int m_numline2;
    int m_curline2;
    float m_linetime2;
    char m_rect2[16]; // tagRECT
    unsigned char m_bHas2;
    unsigned char m_bDraw2;
};

struct PalScriptWaitObj {
    char _gap_0[4];
    int m_needscriptdel;
};

struct CCBItemWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIStatic * m_pDescription;
    UIListBox * m_pItemList[3];
    UIPushButton * m_pButtonRecover;
    UIPushButton * m_pButtonAttack;
    UIPushButton * m_pButtonTreasure;
    int m_nActivePage;
};

struct CCBUI {
    char _gap_0[72];
    UIStatic * m_pAttackSequenBack;
    UIStatic * pPanel;
    UIStatic * m_pBattleFieldAttr[6];
    UIStatic * m_pAttackSequenFace[11];
    UIStatic * m_pRoleStatePanel[4];
    UIStatic * m_pRoleStateFace[5];
    UIStatic * m_pRoleStateFaceName[5];
    UIStatic * m_pRoleStateAttackInc[11];
    UIStatic * m_pRoleStateAttackDec[11];
    UIStatic * m_pRoleStateDefenceInc[11];
    UIStatic * m_pRoleStateDefenceDec[11];
    UIStatic * m_pRoleStateLuckInc[11];
    UIStatic * m_pRoleStateLuckDec[11];
    UIStatic * m_pRoleStateSpeedInc[11];
    UIStatic * m_pRoleStateSpeedDec[11];
    UIStatic * m_pRoleStateStable[11];
    UIStatic * m_pRoleStateBlank[11];
    UIStatic * m_pRoleStateForbid[11];
    UIStatic * m_pRoleStateSleep[11];
    UIStatic * m_pRoleStateChaos[11];
    UIStatic * m_pRoleStateMad[11];
    UIStatic * m_pRoleStateMirror[11];
    UIStatic * m_pRoleStateWall[11];
    UIStatic * m_pRoleStateBound[11];
    UIStatic * m_pRoleStateHermit[11];
    UIStatic * m_pRoleStateImmunity[11];
    UIStatic * m_pWinPanel;
    UIStatic * m_pLosePanel;
    UIProgressBar * m_pRoleStateHP[4];
    UIProgressBar * m_pRoleStateGP[4];
    UIProgressBar * m_pRoleStateMP[4];
    UIProgressBar * m_pRoleStateSword;
    UIStaticCB * m_pTrickName;
    UIStaticCB * m_pTrickName2;
    UIStatic * m_pDialogBack;
    UIStatic * m_pResultLevelup;
    UIStatic * m_pResultWindLvup;
    UIStatic * m_pResultThunderLvup;
    UIStatic * m_pResultWaterLvup;
    UIStatic * m_pResultFireLvup;
    UIStatic * m_pResultEarthLvup;
    UIStatic * m_pResultDoubleLvup;
    UIStatic * m_pResultGetItem;
    CCBControlWindow * m_pMain;
    CCBItemWindow * m_pItemWindow;
    CCBParabolaWindow * m_pParabolaWindow;
    CCBMagicWindow * m_pMagicWindow;
    CCBSkillWindow * m_pSkillWindow;
    CCBAIWindow * m_pAIWindow;
    CCBLineupWindow * m_pLineupWindow;
    CCBProtectWindow * m_pProtectWindow;
    CCBResultWindow * m_pResultWindow[4];
    CCBFiveNimbusWindow * m_pFiveNimbusWindow;
    CCBSystem * m_pCBSystem;
    void * m_pUtil;
    char m_Task[2304]; // tagUITask[32]
    unsigned char m_bShowResult;
    void * m_fp;
    int m_nTask;
    int m_nCurTask;
    int mImbibeNimbusNum;
    void * m_pImbibeNimbus;
};

struct CCBFiveNimbusWindow {
    char _gap_0[72];
    UIButtonEX * pCtrlButton[5];
    UIButtonEX * pMiddle;
    char m_OpenWindow[12]; // OpenFNWindow
    int m_nimbus[5];
    int m_state[5];
    int m_nimbusStep;
    unsigned char m_bShow;
    unsigned char m_bLock;
    int m_counter;
};

struct gbMatrixStack {
    void * pMatBuf;
    int MaxVol;
    int CurPos;
    int ValidFlag;
};

struct gbRenderEffect {
    char _gap_0[24];
    void * m_pEffect;
    unsigned int m_Flags;
    void * m_DeclHandle;
    unsigned int m_ParamHandle[8];
};

struct std::locale::_Locimp {
    char _gap_0[8];
    void * _Fv;
    unsigned int _Nfv;
    int _Cat;
    unsigned char _Xpar;
    char _Name[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
};

struct MainPropUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    int s_x;
    char buf[256];
    char remarkbuf[256];
    unsigned char m_IsMsg;
    unsigned char m_Is[5];
    int m_CurSelRole;
    int m_CurNeedRole;
    unsigned char m_IsActive;
    unsigned char m_IsCreateable;
    int curPage;
    int curList;
    int m_SelNum;
    int m_UseNum;
    unsigned char m_LockUse;
    unsigned char m_IsUsed;
    unsigned char m_IsCanUse;
    unsigned char m_IsAllUse;
    StateUI * pStateUI;
    UIStatic m_Frame;
    UIStatic m_TimeMoney;
    UIStatic m_TopFrame;
    UIStatic m_TopFrameWP;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic stp_BarL;
    UIFlexBar stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_TaskBook;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    UIStatic m_GameTime;
    UIStatic m_GameMoney;
    MUIDialog m_DlgEx;
    char m_btnPar[66304]; // UIParticle[7][16]
    char m_btnPar2[66304]; // UIParticle[7][16]
    char m_btnParRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    MUIDialog m_Dlg;
    char m_Role[21460]; // p_RoleState[5]
    UIStatic m_RemarkBk;
    UIStatic m_Remark;
    UIStatic m_RemarkVal;
    char m_RemarkRc[16]; // tagRECT
    UIStatic m_typeWord;
    UIStatic m_PageBk;
    UIButton m_Ctrlbtn[5];
    UIPushButton m_Pushbtn[5];
    UIStatic m_Title;
    UIStatic m_ListFrame;
    UIStatic m_ListGrid[14];
    UIStatic m_ScrollHB;
    UIListBox ml_Resume;
    UIListBox ml_Attack;
    UIListBox ml_Treasure;
    UIListBox ml_Smelt;
    UIListBox ml_Special;
    UIAnimate m_Animate[5];
    char m_AnimateRc[80]; // tagRECT[5]
    char m_SortRc[16]; // tagRECT
    UIButton mb_SortDefault;
    UIButton mb_SortPrice;
    UIButton mb_SortUse;
    int m_SortState;
    UI3DCtrl m_3DObj;
    char m_parSingle[35520]; // UIParticle[5][12]
    char m_parDouble[35520]; // UIParticle[5][12]
    char m_parRc[80]; // tagRECT[5]
    int m_nUsedID;
};

struct CEffTrackQuad {
    char _gap_0[4272];
    t3DModel * m_pTrack;
    float m_fTrackSpeed;
    float m_fTrackDecPart;
    int m_nCurrTrackPos;
    float m_fx;
    float m_fy;
    float m_fz;
};

struct CEffGrid {
    char _gap_0[48];
    void * m_pGeomQuad;
    void * m_pMesh;
    void * m_pMesh2;
    gbTexture * m_pTexture;
    void * m_pTextureArray;
    unsigned char m_bVisible;
    unsigned char m_bAdditiveBlend;
    unsigned char m_bNoZTest;
    unsigned char m_byMaxFrame;
    int m_nRequireLoops;
    int m_nLoops;
    float m_fCurFrame;
    unsigned int m_dwStartColor;
    float m_fAlpha;
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fXSize;
    float m_fZSize;
    int m_nXDivision;
    int m_nZDivision;
    float m_fGridSize;
    int m_nQuad;
    float m_fWavePower;
    float m_fWaveSpeed;
    float m_fFlapPower;
    float m_fFlapSpeed;
    float m_fFramePerSec;
    char m_vecRot[12]; // gbVec3D
    char m_vecPos[12]; // gbVec3D
    char m_vecOffsetPos[12]; // gbVec3D
    char m_DefaultUVSet[4096]; // tagUV[256]
};

struct CReBackFramePolicy {
    char _gap_0[12];
    float _fSpeed;
};

struct RoleCameraCtrl {
    char _gap_0[8];
    RoleCamera * m_camera;
    char m_type[4]; // RCC_TYPE
    float m_time;
    float m_passtime;
    int m_itype;
    float m_targetdist;
    float m_startdist;
    float m_targetyaw;
    float m_startyaw;
    float m_targetpitch;
    float m_startpitch;
    char m_targetfrom[12]; // gbVec3D
    char m_startfrom[12]; // gbVec3D
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

struct UIFrameWnd {
    char _gap_0[68];
    gbTexture * m_pbktex;
};

struct UIWnd {
    char _gap_0[4];
    char m_fontcolor[4]; // gbColorQuad
    char m_wndcolor[4]; // gbColorQuad
    unsigned int m_id;
    char m_rect[16]; // tagRECT
    UIWnd * m_pfather;
    PtrArray m_childs;
    int m_bcreateok;
    int m_bvisible;
    int m_benable;
    int m_bfocus;
};

struct KeyFrame {
    char emitterAttr[220]; // CParticleSystem::EmitterAttribute
    CPolicy * pPositionPolicy;
    CPolicy * pDirectionPolicy;
    CPolicy * pColorPolicy;
    CPolicy * pAlphaPolicy;
    CPolicy * pFramePolicy;
    CPolicy * pEmitterPolicy;
    float fTime;
    unsigned int dwReserved[4];
};

struct gbVFile1 {
    unsigned int OpenMode;
    unsigned int EntryAddr;
    unsigned int FileSize;
    char pFilePath[256];
    unsigned int m_NowAddr;
};

struct CEffTrackModel {
    char _gap_0[104];
    t3DModel * m_pTrack;
    float m_fTrackSpeed;
    float m_fTrackDecPart;
    int m_nCurrTrackPos;
    float m_fx;
    float m_fy;
    float m_fz;
};

struct CEffMgr {
    gbGfxManager * m_pDisplay;
    CCBSystem * m_pCBSystem;
    gbRenderEffect * m_pAdditiveBlendNoZ;
    gbRenderEffect * m_pAlphaBlendNoZ;
    gbRenderEffect * m_pAdditiveBlend;
    gbRenderEffect * m_pAlphaBlend;
    gbCamera * m_pCam;
    char m_EffClass[2304]; // tagEffClass[32]
    char m_EffTable[40960]; // tagEffObj[2048]
    int m_nEff;
    float m_fCurTime;
    float m_fDeltaTime;
    float m_fTimer;
    float m_fTimeScale;
};

struct RoleFadeOut {
    char _gap_0[8];
    float m_passedtime;
    Role * m_role;
    unsigned char end;
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

struct RoleShadow {
    char _gap_0[4];
    gbTexture * m_shadowtex;
    gbRenderEffect * m_effect;
    gbRenderEffect * m_effectFog;
    gbRenderEffect * m_effectFrame;
    char m_quad[5236]; // gbGeomQuad[77]
    char m_CtrlRoleQuad[68]; // gbGeomQuad
    void * m_pFrameShadow;
    int m_nFrameNum;
    int m_nCurFrame;
    int m_nFrameFPS;
    unsigned char m_bFrameShadow;
};

struct UIChatRest {
    char _gap_0[68];
    char m_pt[8]; // tagPOINT
    char rc[16]; // tagRECT
    char bkrc[16]; // tagRECT
    int m_startX;
    int m_startY;
    int mbWidth;
    int mbHeight;
    UIStatic m_FlagT;
    UIStatic m_FlagB;
    UIStatic m_FlagM[3];
    UIButton m_Chat;
    UIButton m_Rest;
    UIButton m_Exit;
    UITabBtn m_TabBtn;
    MUIDialog m_answerDlg;
    unsigned char m_bAnswer;
    ScreenEffect * eft;
    TimeCtl m_timewait;
    unsigned char m_isFadeOut;
    unsigned char m_isFadeIn;
    MUIDialog m_noenoughmsg;
    MUIDialog m_enough;
    MUIDialog m_restover;
    unsigned int m_status;
    unsigned char m_isExit;
    RestScript m_RestScript;
    int m_CANREST_ID;
    int m_CANNOTREST_ID;
    int m_RESTOVER_ID;
    PalScript * pRest;
    PalScript * pCantRest;
    PalScript * pRestOver;
    unsigned char m_bActive;
    Comp_DonateUI * pC_DUI;
    unsigned char m_bC_DUIOver;
    UIStatic m_BK;
    unsigned char m_FadeOutAlpha;
    float m_age;
    float m_life;
};

struct UIGameFrm {
    char _gap_0[76];
    unsigned int m_bigMapElement[16];
    unsigned char m_newbigmap[16];
    UICaption m_cap;
    UINote m_note;
    unsigned int m_SmeltChatScript;
    unsigned int m_HockShopScript;
    unsigned int m_EncampFlag;
    unsigned int m_ExitRow;
    unsigned char m_SDTY;
    unsigned char m_APPR;
    unsigned char m_SKEE;
    unsigned int m_ExitSkee;
    ScreenEffect * eft;
    unsigned char m_isFadeOut;
    unsigned char m_overFade;
    UIRoleSelect m_seldlg;
    UIHeadDialog m_headdlg[5];
    UIRoleDialog m_roledlg;
    UIChatRest m_ChatRest;
    unsigned int m_ChatRestStatus;
    UIFrameWnd * m_curfrm;
    char m_curfrmid[4]; // PAL3_FRAME
    char m_lastfrmid[4]; // PAL3_FRAME
    UIEmote m_emote[6];
    UISceneFrm * m_scenefrm;
    StateUI * m_sysfrm;
    UIStatic m_selemote_frame;
    UIButton m_selemote_BTN1;
    UIButton m_selemote_BTN2;
    int m_selemote_nSel;
    unsigned char m_selemote_create;
    MUIDialog m_FinishSave;
};

struct CCBStageShadow {
    CCBStage * m_pStage;
    gbTexture * m_pTexture;
    gbRenderEffect * m_pEffect;
    void * m_pTextureArray;
    char m_ShadowInitQuad[748]; // gbGeomQuad[11]
    char m_ShadowQuad[748]; // gbGeomQuad[11]
    float m_fShadowRadius[11];
};

struct PathFinder {
    char _gap_0[24];
    void * m_curlayer;
    int m_layer;
    Role * m_pRole;
};

struct RoleFadeIn {
    char _gap_0[8];
    float m_passedtime;
    Role * m_role;
    unsigned char end;
};

struct CEffObj {
    char _gap_0[4];
    CEffMgr * m_pEM;
    unsigned char m_bIdle;
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

struct std::locale::facet {
    char _gap_0[4];
    unsigned int _Refs;
};

struct SkyBox {
    char _gap_0[4];
    char m_fogColor[4]; // gbColorQuad
    gbTexture * m_pTexture[6];
    char m_vHalfSize[12]; // gbVec3D
    gbRenderEffect * m_pEffect;
    gbRenderEffect * m_pEffectNormal;
    unsigned char m_bValid;
};

struct gbRefObject {
    char _gap_0[4];
    int RefCount;
};

struct MagicUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    char remarkbuf[256];
    int s_x;
    unsigned char m_IsMsg;
    unsigned char m_Is[5];
    int m_CtrlRole;
    unsigned char m_IsActive;
    unsigned char m_IsCreateable;
    int curPage;
    int m_SelNum;
    int m_CurType;
    int m_usemagicRole;
    unsigned char m_isuseMagic;
    unsigned char m_LockUse;
    unsigned char m_IsUsed;
    unsigned char m_IsCanUse;
    unsigned char m_IsAllUse;
    char pt[8]; // tagPOINT
    char m_RoleSkill[41720]; // SkillData[5][7]
    StateUI * pStateUI;
    UIStatic m_Frame;
    UIStatic m_TimeMoney;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic stp_BarL;
    UIFlexBar stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_TaskBook;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    char titleRc[16]; // tagRECT
    UIStatic m_title[4];
    UIStatic m_GameTime;
    UIStatic m_GameMoney;
    MUIDialog m_DlgEx;
    char m_btnPar[66304]; // UIParticle[7][16]
    char m_btnPar2[66304]; // UIParticle[7][16]
    char m_btnParRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    int m_CurSelRole;
    int m_CurNeedRole;
    MUIDialog m_Dlg;
    MUIDialog m_Msg;
    char m_DlgMsg[4]; // DLG_MSG
    UIAnimate m_Animate[5];
    char m_AnimateRc[80]; // tagRECT[5]
    UIStatic m_ListFrame;
    UIStatic m_ListGrid[8];
    UIStatic m_RemarkBk;
    UIStatic m_Remark;
    UIStatic m_RemarkVal;
    UIStatic m_UnCom;
    char m_Role[21460]; // m_RoleState[5]
    UIButton m_Ctrlbtn[7];
    UIListBox ml_SpeList;
    UIListBox ml_FengList;
    UIListBox ml_LeiList;
    UIListBox ml_ShuiList;
    UIListBox ml_HuoList;
    UIListBox ml_TuList;
    UIListBox ml_SuangList;
    UIStatic m_TopFrame;
    UIStatic m_TopFrameXS;
    char m_parRainbow[23680]; // UIParticle[5][8]
    char m_parRise[23680]; // UIParticle[5][8]
    char m_parRc[80]; // tagRECT[5]
};

struct Glow {
    gbRenderEffect * m_eft;
    gbRenderEffect * m_pGeomEft;
    int m_nPass;
    char m_pObjArray[16]; // std::vector<GlowObj *,std::allocator<GlowObj *> >
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

struct CCCTData {
    char m_Pool[408000]; // tagCCT[2000]
    unsigned char m_bPoolInUse[2000];
    char m_nCCTIndex[20000]; // int[100][50]
};

struct CEffModel {
    char _gap_0[48];
    gbGeomNode * m_pGeomNode;
    char m_vecCurPos[12]; // gbVec3D
    char m_vecOffsetPos[12]; // gbVec3D
    char m_vecRot[12]; // gbVec3D
    unsigned char m_bVisible;
    unsigned char m_bAdditiveBlend;
    unsigned char m_bNoZTest;
    float m_fSizeX;
    float m_fSizeY;
    float m_fSizeZ;
};

struct NameSys {
    char m_Flag[8]; // std::bitset<48>
    char m_FlagZZCC[4]; // std::bitset<10>
    int m_Ref[28];
    int m_RefMax[28];
    unsigned int m_CheckMax[10];
    char m_LastName[4]; // NameSys::NAMEFLAG
};

struct PalScript {
    unsigned char m_bLoadSceneScript;
    void * m_pinst;
    PtrArray m_waitobj;
    PtrArray m_CamObj;
};

struct OpenBaseFile {
    gbVFileSystem * m_plastsys;
};

struct DealUI {
    char _gap_0[72];
    char m_pt[8]; // tagPOINT
    char rc[16]; // tagRECT
    char bkrc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int bkWidth;
    int bkHeight;
    int mbWidth;
    int mbHeight;
    int m_startX;
    int m_startY;
    int m_x;
    int m_y;
    unsigned char _isCreatable;
    unsigned char m_Is[5];
    unsigned short m_ST;
    unsigned short m_ID;
    UIStatic m_FlagT;
    UIStatic m_FlagB;
    UIStatic m_FlagM[5];
    UIButton mb_BuyEquip;
    UIButton mb_BuyProp;
    UIButton mb_Sale;
    UIButton mb_Talk;
    unsigned char m_IsExit;
    UIButton mb_Exit;
    UITabBtn m_TabBtn;
    UIStatic m_BkWnd;
    int m_curRender;
    EquipUI * pEquipUI;
    PropUI * pPropUI;
    SaleUI * pSaleUI;
    gbTexture * pInterceptTex;
    float sv;
    float ev;
    unsigned char m_opt;
};

struct LayerNode {
    char m_bound[24]; // gbAABBox
    int m_lv;
    char m_tri[16]; // std::vector<Triangle,std::allocator<Triangle> >
    LayerNode * m_child[4];
};

struct UIDialog {
    char _gap_0[68];
    int m_bmodal;
};

struct std::_Timevec {
    void * _Ptr;
};

struct ObjLockInput {
    PtrArray m_objs;
    PtrArray m_scripts;
    PtrArray m_scriptabs;
};

struct std::ios_base {
    char _gap_0[4];
    int _State;
    int _Except;
    int _Fmtfl;
    int _Prec;
    int _Wide;
    void * _Arr;
    void * _Calls;
    char _Loc[4]; // std::locale
    unsigned int _Stdstr;
};

struct UISceneFace {
    char _gap_0[68];
    UIProgressBar m_hp;
    UIProgressBar m_mp;
    UIStatic m_face[3];
    UIStatic m_bk;
    float m_clicktime;
    int m_onclick;
    UIStatic m_state[4];
};

struct UISceneFrm {
    char _gap_0[72];
    UISceneMap m_map;
    UISceneFace m_face;
};

struct UIStaticEXA {
    char _gap_0[192];
    int center_x;
    int center_y;
};

struct CEffExplosive {
    char _gap_0[48];
    void * m_pGeomQuad;
    void * m_pExplosive;
    gbTexture * m_pTexture;
    void * m_pTextureArray;
    unsigned char m_bVisible;
    unsigned char m_bAdditiveBlend;
    unsigned char m_bNoZTest;
    unsigned char m_byMaxFrame;
    int m_nRequireLoops;
    int m_nLoops;
    float m_fCurFrame;
    unsigned int m_dwStartColor;
    float m_fAlpha;
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fXSize;
    float m_fZSize;
    int m_nXDivision;
    int m_nZDivision;
    float m_fGridSize;
    int m_nQuad;
    float m_fMaxExplosivePower;
    float m_fMinExplosivePower;
    char m_vecExplosiveDir[12]; // gbVec3D
    float m_fPowerDec;
    float m_fFramePerSec;
    char m_vecRot[12]; // gbVec3D
    char m_vecPos[12]; // gbVec3D
    char m_vecOffsetPos[12]; // gbVec3D
    float m_fResistance;
    char m_DefaultUVSet[4096]; // tagUV[256]
};

struct ObjectCamera {
    gbCamera * m_pCamera;
    char m_camFrom[12]; // gbVec3D
    char m_camTo[12]; // gbVec3D
    char m_camUp[12]; // gbVec3D
    char m_camDirect[12]; // gbVec3D
    float m_yaw;
    float m_pitch;
    float m_roll;
    float m_dist;
    float m_nyaw;
    float m_npitch;
    float m_nroll;
    char m_forward[12]; // gbVec3D
    char m_side[12]; // gbVec3D
    float m_stepRotSpeed;
    float m_stepRot;
    int m_stepRotMode;
    int m_stepRotAxis;
    unsigned char m_bStepRot;
};

struct ARC_Inventory {
    char m_items[16]; // std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >
    int m_curtype;
    char m_typeitems[16]; // std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >
    int m_money;
};

struct UIMap {
    char _gap_0[68];
    int m_mapwidth;
    int m_mapheight;
    char m_screenArea[16]; // tagRECT
    int m_screenWidth;
    int m_screenHeight;
    int m_xMapNum;
    int m_yMapNum;
    int m_MapNum;
    void * m_pSubMap;
    float m_moveSpeed;
    unsigned char m_isMoving;
    float m_offsetx;
    float m_offsety;
    float m_moveoffsetx;
    float m_moveoffsety;
    unsigned char m_bCreate;
    float timescale;
    unsigned char m_bLock;
};

struct graph {
    int curve_num;
    int cp_num;
    char graphname[64];
    char describe[128];
    char min[12]; // D3DXVECTOR3
    char max[12]; // D3DXVECTOR3
    char disdata[720]; // D3DXVECTOR3[3][20]
    char realdata[720]; // D3DXVECTOR3[3][20]
    char interpolate[3636]; // D3DXVECTOR3[3][101]
};

struct MU_SortFun {
    int m_by;
};

struct RotateInvObj {
    char _gap_0[8];
    float m_passedtime;
    unsigned char end;
    char m_rotate[12]; // gbVec3D
};

struct CCBLineupWindow {
    char _gap_0[72];
    int m_nInitRoleFaceLineup[5];
    UIStatic * m_pBack;
    UIStatic * m_pFace[5];
    int m_nSelected;
    CCBUI * m_pUI;
};

struct OpenNULLFile {
    gbVFileSystem * m_plastsys;
};

struct Object {
    char _gap_0[4];
    char position[12]; // gbVec3D
    float radius;
    char forward[12]; // gbVec3D
    char side[12]; // gbVec3D
    char up[12]; // gbVec3D
};

struct t3DModel {
    int numOfObjects;
    int numOfMaterials;
    char pMaterials[16]; // std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >
    char pObject[16]; // std::vector<t3DObject,std::allocator<t3DObject> >
};

struct scVarStack {
    int m_counter;
    char m_vararray[256]; // scVARIANT[32]
};

struct CTrail {
    float m_fTime;
    unsigned char m_bSupport;
    unsigned char m_bEnable;
    gbCamera * m_pCam;
    char m_ScreenQuad[40]; // gbUIQuad
    unsigned int m_dwRenderCounter;
    unsigned int m_dwRT;
    unsigned char m_bReady;
    gbTexture_D3D m_texRT[8];
    gbRenderEffect * m_eft;
    void * m_OriginSurface;
};

struct UITitle_YXXX {
    char _gap_0[72];
    char rc[16]; // tagRECT
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic m_background;
    UIStatic m_title;
    UIButton m_exit;
    UIButton m_ZZRY;
    UIButton m_XGWZ;
    UIStatic m_WordBk;
    UIStatic ms_Info;
    UIStatic ms_Pic;
    unsigned char m_bIsChanged;
    unsigned char m_IsActive;
    _Item m_Item;
    UICoverFrm * m_pMgr;
};

struct SceneMapPlayer {
    char _gap_0[16];
    int m_nLayerIndex;
    char m_playerpt[8]; // tagPOINT
    char m_playerfov[16]; // tagRECT
    int m_maxwidth;
    int m_maxheight;
    gbTexture * m_tex;
    gbImage2D m_img;
    void * m_layer;
    unsigned char m_bBuild;
    char m_szName[128];
};

struct Average {
    unsigned int _size;
    float * _data;
    float ret;
    unsigned int _cur;
    unsigned int _real;
    unsigned char _initialize;
    unsigned char _invalid;
    unsigned char _full;
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

struct UIBigMap {
    char _gap_0[72];
    char screenrect[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    UIStatic ms_BigMap;
    char m_Element[6272]; // _MapElement[16]
    char m_spiritRect[16]; // tagRECT
    UIAnimateCtrl m_spirit;
    float m_spiritPosX;
    float m_spiritPosY;
    char m_spiritPos[8]; // tagPOINT
    char m_movetopos[8]; // tagPOINT
    float m_movetoX;
    float m_movetoY;
    int m_spiritspeed;
    float m_speedFX;
    float m_speedFY;
    unsigned char m_bSpiritCanMove;
    unsigned char m_isSpiritMoveTo;
    float m_timescale;
    int m_stopdir;
    char m_curElement[4]; // _BIGMAP_ELEMENT
    MUIDialog m_Answer;
    MUIDialog m_Msg;
    TxtFile scnname;
    unsigned char m_haveopen;
    unsigned char m_bupalpha;
    int m_alpha;
    int m_alphatime;
};

struct RotateObj {
    char _gap_0[8];
    float m_passedtime;
    unsigned char end;
    char m_rotate[12]; // gbVec3D
    float m_rotatetime;
    unsigned char m_mode;
};

struct UIRoleSelectDialog {
    char _gap_0[72];
    int m_state;
    UIStaticFlex m_bk;
    UIAnimateCtrl m_ani;
    UIStaticFlip m_face;
    UITextArea m_static;
    int m_texth;
    UIListBox m_list;
    int m_maxlen;
    float m_last;
    int m_sel;
    int m_mode;
};

struct CRotateEmitterPolicy {
    char _gap_0[12];
    char _vAxis[12]; // gbVec3D
    float _fSpeed;
    float _fAngle;
};

struct SCNFile {
    char m_info[132]; // SceneInfo
    int m_numnpc;
    char m_npc[32832]; // NPCInfo[72]
    int m_numobj;
    char m_obj[154624]; // ObjectInfo[256]
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

struct CSEHException {
    unsigned int m_uiErrCode;
    char m_szExceptionString[260];
};

struct CCBControl {
    CCBSystem * m_pCBSystem;
    CCBAttackSequen * m_pAttackSequen;
    CCBStage * m_pStage;
    CCBRoleState * m_pRoleState;
    CCBUI * m_pUI;
    double m_DeltaTime;
    int m_nController;
    unsigned char m_bActive;
    unsigned char m_bForceRelease;
    char m_InputData[16]; // tagControlData
    char m_CmdData[44]; // tagCmdData
    unsigned char m_bShowRightPanel;
    int m_nCurThread;
    int m_nThread;
    char m_Thread[1280]; // tagControlThread[20]
};

struct CCBStageEffect {
    double m_DeltaTime;
    CCBStage * m_pStage;
    CCBSystem * m_pCBSystem;
    gbVolModNode m_EnvLight;
    gbVolModNode m_Light[10];
    gbRenderEffect * m_pGeomFlashEffect;
    gbRenderEffect * m_pGeomFlashEffect_t;
    char m_Linker[23044]; // tagEffLinker[384]
};

struct XJ_Pic {
    char _gap_0[8];
    float m_fElapsed;
    unsigned char m_bEnd;
};

struct CEffAudio {
    char _gap_0[48];
    char m_szSoundNamePrefix[128];
    char m_szSoundName[512]; // char[4][128]
};

struct gbResource {
    char _gap_0[8];
    char * pName;
    unsigned int NameCrc32;
    int IsLoaded;
    gbResManager * pMgr;
};

struct UIPosMaker {
    unsigned char m_bIsLoaded;
    void * m_pUIPos;
    int m_nPosNum;
};

struct UIGroupCtrl {
    char m_bkRc[16]; // tagRECT
    unsigned char m_isCreat;
    int m_ItemNum;
    int m_lBTNSel;
    int m_rBTNSel;
    int m_ItemW;
    int m_ItemH;
    void * pRect;
    void * pKeepRect;
    char m_color[4]; // gbColorQuad
    float rollSpeed;
    float speedstep;
    int rollID;
    unsigned char isCtrl;
    int m_PageState;
    int m_showNum;
    unsigned char * pEnable;
    gbTexture * m_pbk;
    void * m_pbkInfo;
};

struct CG_Scene {
    void * m_pBarrier;
    int m_nBarrier;
    unsigned char m_bShowHelper;
    CG_Entry * m_pFather;
    Scene * m_pScene;
    RoleCameraCtrl m_CameraCtrl;
    Role * m_pNPC;
    void * m_pRelive;
    SceneObj m_OBJ[256];
    char m_ObjHelper[12288]; // OBJHELPER[256]
    char m_OBJPARAM[4068]; // ObjParam[9]
    char m_GHOSTPARAM[192]; // GhostParam[4]
    Role * m_pBOSS;
    char m_BossHurt[20]; // BOSSHURT
    char m_NGHHurt[20]; // NGHHURT
    unsigned char m_bEdit;
    int m_nLevel;
    int m_nNPC;
    int m_nOBJ;
    int m_nSpecialOBJ;
    float m_fEffTime;
    unsigned char m_bGameOver;
    TxtFile m_ObjFile;
    gbRenderEffect * EFT_LINE;
    gbRenderEffect * EFT_GEOM;
    gbRenderEffect * EFT_GEOM_NOTEX;
    gbRenderEffect * EFT_GEOM_NOTEX_LINE;
    gbTexture * m_pObjFlagTex;
    char m_SpecialObjPos[192]; // gbVec3D[16]
    unsigned char m_DoFlingAct;
    char m_propinfo[4]; // CG_PROPINFO
    unsigned int m_propid;
    char m_tmpPos[12]; // gbVec3D
    char m_PropArray[12]; // std::list<SceneProp *,std::allocator<SceneProp *> >
};

struct sg_particle_scene {
    char name[256];
    int emission_controlnum;
    int particle_num;
    int emitter_num;
    int active_particle;
    int active_emitter;
    int active_emissioncontrol;
    sg_emission_control econtrol[4];
    int ecenable[4];
    int cur_sel;
    sg_particle particle[4];
    sg_emitter emitter[4];
    int maxparticle;
    int emittedto;
    int npwmr;
    float gravity;
    float timescale;
    int maxfps;
    int camerafollow;
    float camerafollowdis;
    int gravityeffect;
    float frontplane;
    float backplane;
    char objectoffset[12]; // D3DXVECTOR3
    char systemoffset[12]; // D3DXVECTOR3
    char systemvelocity[12]; // D3DXVECTOR3
    float m_fMultisize;
};

struct CLoad3DS {
    void * m_FilePointer;
    int m_pBuffer[50000];
};

struct CEffAction {
    char _gap_0[48];
    int m_nController;
};

struct UITitle_QCYM {
    char _gap_0[72];
    char rc[16]; // tagRECT
    char buf[256];
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic m_background;
    UIStatic m_title;
    UIButtonEXA m_btn[30];
    UIStatic m_NoMovieBK[30];
    UIButton m_exit;
    UIStatic m_info;
    UIStatic m_infoBK;
    unsigned char m_isPlayMovie;
    unsigned char m_isJustOver;
    float m_fpasstime;
    UICoverFrm * m_pMgr;
};

struct exception {
    char _gap_0[4];
    char * _m_what;
    int _m_doFree;
};

struct gbChain1DNode {
    char _gap_0[4];
    gbChain1DNode * next;
};

struct std::_Locinfo {
    char _Days[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char _Months[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char _Oname[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char _Nname[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
};

struct UICoverFrm {
    char _gap_0[72];
    char rc[16]; // tagRECT
    char buf[256];
    UIStatic m_background;
    UIPar_Star m_Star[13];
    UIPar_Meteor m_Meteor;
    char m_cloud[2160]; // _CLOUD[10]
    char m_midCloud[1080]; // _CLOUD[5]
    char m_smlCloud[1080]; // _CLOUD[5]
    char m_testCloud[1944]; // _CLOUD[9]
    UIStatic m_mountainA;
    UIStatic m_mountainB;
    UIStatic m_frame;
    UIStatic m_Logo;
    unsigned char m_isAlpha;
    float m_alpha;
    UIStaticEXA m_tjA;
    UIStaticEXA m_tjB;
    UIButtonEX m_XDGS;
    UIButtonEX m_QCYM;
    UIButtonEX m_XJTM;
    UIButtonEX m_LKYX;
    UIButtonEX m_YXXX;
    UIButtonEX m_JDHY;
    UIButtonEX * m_CtrlBtn[6];
    int m_SelBtn;
    unsigned char m_ExitGame;
    UITitle_QCYM * pQCYM;
    UITitle_JDHY * pJDHY;
    UITitle_YXXX * pYXXX;
    UITitle_XJTM * pXJTM;
    UITitle_ArcSave * pArcSave;
    UILoadingFrm * pLoadingFrm;
    char m_MenuType[4]; // MENU_TYPE
    Average m_timeAverage;
    unsigned char m_gotogame;
    unsigned int m_flag;
    UIStatic m_test;
    MUIDialog m_ArcDlg;
    MUIDialog m_Not1stDlg;
    unsigned char m_goingin;
    unsigned char m_ArcSaveSuc;
    unsigned char m_IsReadFinishSave;
};

struct AStarPathFinder {
    char _gap_0[4];
    void * OPEN;
    void * CLOSED;
    void * PATH;
    void * Stack;
    int m_TestTimer;
};

struct ScreenEffectMgr {
    char _gap_0[4];
    ScreenFadeIn m_fadeIn;
    char m_fadeOut[24]; // ScreenFadeOut
    char m_fadeWhite[24]; // ScreenFadeWhite
    char m_fadeWhite2[24]; // ScreenFadeWhite2
    char m_activeQueue[48]; // std::queue<ScreenEffect *,std::deque<ScreenEffect *,std::allocator<ScreenEffect *> > >
};

struct gbCamControler {
    char _gap_0[8];
    gbCamera * pCamera;
    double CtrlTime;
    double CtrlAge;
};

struct UIGameOver {
    char _gap_0[72];
    gbTexture * m_pbktex;
    UIStatic m_Blood;
    float m_fTime;
};

struct CCBCamControl {
    CCCTData m_CCT;
    CCBStage * m_pStage;
    CCBStageCam * m_pCam;
    void * m_pUtil;
    unsigned char m_bRunning;
    void * m_fp;
    int m_nCurList;
    int m_nCurTask;
    float m_fStartSpeed;
    float m_fNextSpeed;
    char m_vecSpeed[12]; // gbVec3D
    char m_vecNextSpeed[12]; // gbVec3D
    float m_fDistance;
    float m_fQuake;
    float m_fQuakeDec;
    float m_fQuakeFre;
    char m_StartPos[24]; // tagCam
    char m_CurPos[24]; // tagCam
    char m_vecCurPos[12]; // gbVec3D
    char m_OBBox[76]; // gbOBBox
    gbGeomNode * m_pPointer;
    char m_vecCircleCenter[12]; // gbVec3D
    char m_vecCircleEnd[12]; // gbVec3D
    unsigned char m_bShowCircleSet;
    unsigned char m_bCircleCenterSelected;
    unsigned char m_bCircleEndSelected;
};

struct SystemUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    unsigned char m_IsMsg;
    StateUI * pStateUI;
    UIStatic m_Frame;
    UIStatic m_TimeMoney;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UIStatic stp_BarL;
    UIFlexBar stp_BarM;
    UIStatic stp_BarR;
    UIButton stp_State;
    UIButton stp_Magic;
    UIButton stp_Equip;
    UIButton stp_Prop;
    UIButton stp_BattleArray;
    UIButton stp_TaskBook;
    UIButton stp_System;
    UIButton stp_Exit;
    UIStatic stp_Effect;
    char stp_Rect[16]; // tagRECT
    UIStatic m_GameTime;
    UIStatic m_GameMoney;
    char m_par[66304]; // UIParticle[7][16]
    char m_par2[66304]; // UIParticle[7][16]
    char m_parRc[112]; // tagRECT[7]
    unsigned char _isParBtn[7];
    int _curParEffect;
    UIStatic m_TopBar;
    UIStatic m_BottomBar;
    UIButton m_ExitGame;
    UIButton m_SaveBtn;
    UIButton m_LoadBtn;
    UIButton m_DeleteBtn;
    UIPushButton m_pbPage[10];
    unsigned char m_isItemShow[99];
    char m_NoteItem[369072]; // Note_Item[99]
    UIScrollBar m_Scroll;
    int m_CurScrollPos;
    UIStatic m_BackBar;
    UIStatic m_BackBar2;
    UIDragBar m_MusicBar;
    UIDragBar m_MusicEffectBar;
    UIStatic m_MusicText;
    UIStatic m_MusicEffectText;
    int m_ItemH;
    int m_ItemW;
    int m_firstItem;
    int m_selItem;
    int m_getNote;
    char m_noteState[4]; // NOTE_STATE
    int m_loading;
    float m_passtime;
    unsigned char m_isExit;
    MUIDialog m_MsgBox;
    MUIDialog m_DlgEx;
    MUIDialog m_YesNo_Btn;
    int m_bFinishSave;
    int m_nShowNoteNum;
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

struct CEffMeteor {
    char _gap_0[48];
    void * m_pGeomQuad;
    CMeteorChain * m_pChain;
    void * m_pMeteor;
    gbTexture * m_pTexture;
    void * m_pTextureArray;
    unsigned char m_bVisible;
    unsigned char m_bAdditiveBlend;
    unsigned char m_bNoZTest;
    unsigned char m_bHaveHead;
    unsigned char m_byMaxFrame;
    int m_nRequireLoops;
    int m_nLoops;
    float m_fCurFrame;
    unsigned int m_dwStartColor;
    float m_fAlpha;
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fXSize;
    float m_fZSize;
    int m_nMaxChain;
    float m_fMeteorWidth;
    int m_nMaxTrail;
    float m_fLumDecSpeed;
    float m_fWidthDecSpeed;
    float m_fMaxLum;
    float m_fUpdateTimeFund;
    float m_fFramePerSec;
    char m_vecRot[12]; // gbVec3D
    char m_vecPos[12]; // gbVec3D
    char m_vecOffsetPos[12]; // gbVec3D
    char m_vecTarget[12]; // gbVec3D
    char m_vecStartSpeed[12]; // gbVec3D
    char m_DefaultUVSet[4096]; // tagUV[256]
};

struct UITitle_ArcSave {
    char _gap_0[72];
    MUIDialog m_YesNo;
    MUIDialog m_Yes;
    MUIDialog m_Not1stDlg;
    UICoverFrm * m_father;
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

struct PAL_GDB {
    char m_head[160]; // OutFile
    char m_RoleData[170400]; // RoleAtt[200]
    char m_SkillData[228000]; // FightSkill[300]
    char m_ItemData[409600]; // FightItem[512]
    char m_ComboData[6360]; // ComboAttack[10]
    int i;
};

struct DealData {
    unsigned char m_IsLoadTxt;
    TxtFile m_LoadTxt;
    PAL_GDB m_LoadGDB;
    unsigned char m_IsLang;
    TxtFile m_LoadLang;
    char m_lastFile[256];
    char m_ManagerData[17504]; // st_Manager
};

struct PlayerItemSortFun {
    int m_by;
};

struct JusticeBookUI {
    char _gap_0[72];
    char rc[16]; // tagRECT
    int bkWndX;
    int bkWndY;
    int i;
    int j;
    char buf[256];
    unsigned char m_IsMsg;
    unsigned char m_IsActive;
    unsigned char m_IsExit;
    unsigned char m_IsOpen;
    UIStatic m_BK;
    UIButton m_Exit;
    UIStatic m_OutFrameT;
    UIStatic m_OutFrameR;
    UIStatic m_OutFrameL;
    UIStatic m_OutFrameB;
    UI3DCtrl m_JusticeBook;
    UI3DCtrl m_Monster;
    UIStatic m_Name;
    UIStatic m_H;
    UIStatic m_S;
    UIStatic m_Wuling[5];
    UIStatic m_Att[5];
    UIStatic m_Sorcery[4];
    char m_SorceryRc[64]; // tagRECT[4]
    UIStatic m_Remark;
    UIStatic m_Number;
    UIButton m_PgUp;
    UIButton m_PgDw;
    UIPushButton m_tpGods;
    UIPushButton m_tpImmortal;
    UIPushButton m_tpGhost;
    UIPushButton m_tpDemon;
    UIPushButton m_tpHuman;
    UIPushButton m_tpMagic;
    UIPushButton m_tpGods_unopen;
    UIPushButton m_tpImmortal_unopen;
    UIPushButton m_tpGhost_unopen;
    UIPushButton m_tpDemon_unopen;
    UIPushButton m_tpHuman_unopen;
    UIPushButton m_tpMagic_unopen;
    unsigned int * m_allMonsters;
    int m_MonstersNum;
    int m_tpNum[6];
    char m_tpID[2400]; // ulong[6][100]
    char m_bookMark[4]; // JB_TYPE
    char m_curMark[4]; // JB_TYPE
    int m_Page;
    int m_curPage;
    char l_bookMarkRc[96]; // tagRECT[6]
    char r_bookMarkRc[96]; // tagRECT[6]
    int bookMarkLR[6];
    char m_OpenBookRc[16]; // tagRECT
    unsigned char m_showElement;
    unsigned char m_isSetBookMark;
    int m_isSetBookMarkLR;
    char m_bookState[4]; // JB_STATE
    char m_color[4]; // gbColorQuad
    float m_alpha;
    unsigned char m_isAlpha;
};

struct CCBStageScene {
    CCBStage * m_pStage;
    void * m_pUtil;
    char m_vecFiveLineup[84]; // gbVec3D[7]
    char m_vecInitFiveLineup[84]; // gbVec3D[7]
    char m_vecEnemyLineup[84]; // gbVec3D[7]
    char m_vecInitEnemyLineup[84]; // gbVec3D[7]
    unsigned char m_bLoaded;
    char m_sLastScene[256];
    gbGeomNode * m_pGeomNode;
    gbGeomNode * m_pCvd;
    gbVisNode * m_pLights;
    gbGeomNode * m_pPointer;
    gbGeomNode * m_pCorpse[11];
    gbGeomNode * m_pFling;
    char m_vecFling[12]; // gbVec3D
    char m_rotFling[12]; // gbVec3D
    unsigned char m_bShowFling;
    gbRenderEffect * m_pFiveLineupEffect;
    gbTexture * m_pFiveLineupTexture;
    void * m_pFiveLineupTextureArray;
    gbTexture * m_pFiveLineupCenterTexture;
    void * m_pFiveLineupCenterTextureArray;
    char m_FiveLineupQuad[68]; // gbGeomQuad
    char m_FiveLineupCenterQuad[68]; // gbGeomQuad
    char m_EnemyFiveLineupQuad[68]; // gbGeomQuad
    char m_vecFiveLineupPos[12]; // gbVec3D
    char m_vecFiveLineupInitPos[12]; // gbVec3D
    float m_fFiveLineupRadius;
    float m_fFiveLineupInitRadius;
    float m_fFiveLineupRoll;
    float m_fFiveLineupInitRoll;
    char m_vecEnemyFiveLineupPos[12]; // gbVec3D
    float m_fEnemyFiveLineupRadius;
    float m_fEnemyFiveLineupRoll;
    char m_vecPointerPos[12]; // gbVec3D
    unsigned char m_bShowPointer;
    unsigned char m_bShowAxis;
    unsigned char m_bShowRoleIndex;
    unsigned char m_bShowFiveLineup;
    unsigned char m_bFiveLineupSelected;
    char m_eSceneFiveMagicAttrib[4]; // ECBFiveMagic
    char m_eBattleFieldAttr[4]; // ECBBattleFieldAttr
    char m_eBFAForce[4]; // ECBForce
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
        for name in ['CCBControlWindow', 'CParticleEffect', 'CCBStageRole', 'UINote', 'std::vector<ArcPastScene,std::allocator<ArcPastScene> >', 'std::vector<ArcScene,std::allocator<ArcScene> >', 'std::locale', 'gbAudioManager', 'SwordUI', 'CJ_FindFile', 'std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >', 'ScriptWaitFrm', 'gbSoundData', 'gbParticleEffect', 'RoleTaskPool', 'PalScriptIdleObj', 'gbGfxManager_D3D', 'gbMeshSection', 'std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAction::*)(unsigned long)>', 'UIStaticEX', 'UILoadingFrm', 'gbCursorRes', 'std::numpunct<char>', 'CArrayList', 'CG_Edit', 'std::bitset<48>', 'std::list<SceneProp *,std::allocator<SceneProp *> >::const_iterator', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCallBack::*)(unsigned long)>', 'UIPar_TimeCtrl', 'CCBResultWindow', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >', '_Item', 'GrayScale', 'std::vector<EffectInfo,std::allocator<EffectInfo> >', 'CCBStage', 'UITitle_XJTM', 'gbPixelFormat', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffExplosive::*)(unsigned long)>', 'sg_emission_control', '_TextureLib_Data', 'CCBAI', 'FindArc', 'ARC_PAL_GDB', 'UIStaticFlex', 'std::bitset<10>::reference', 'UIButtonEXA', 'std::binder2nd<std::not_equal_to<COLLIDE_DATA> >', 'gbBaseMesh', 'SkyboxEff', 'UIParticle', 'MXCEft', 'std::basic_streambuf<char,std::char_traits<char> >', 'std::basic_string<unsigned short,std::char_traits<unsigned short>,std::allocator<unsigned short> >', 'UIPar_Star', 'vert<float>', 'std::vector<scScriptBlock *,std::allocator<scScriptBlock *> >', 'std::logic_error', 'gbSceneGraph', 'matrix<3,4,float>', 'EquipUI', 'std::vector<PlayerSkill,std::allocator<PlayerSkill> >', 'ParabolaCalculator', 'StateUI', 'TaskBookUI', 'MXPoisonFog', 'UIAnimateCtrlEX', 'std::list<SceneProp *,std::allocator<SceneProp *> >', 'gbVisNode', 'std::basic_ios<unsigned short,std::char_traits<unsigned short> >', 'MUIDialog', 'MeshFx', 'UITextureArray', 'UIRoleDialog', 'gbDynVertBuf', 'CCBDisplayChain', 'UIProgressBar', 'gbVolModNode', 'ConfigFile', 'gbActorDef', 'gbActorMgr', 'CG_Entry', 'SoundMgr', 'std::ctype<char>', 'Comp_DonateUI', 'CEffQuad', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCustomShape::*)(unsigned long)>', 'std::bitset<10>', 'CD3DSettings', 'gbCycleQueue_gbNodeMsgObj', 'CMeteorChain', 'gbCamera', 'CCBAttackSequen', 'CD3DEnumeration', 'UIPar_Meteor', 'TxtFile', 'SceneMapObj', 'ORect', 'UIScrollBar', 'UIDragBar', 'UIStaticRM', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTime::*)(unsigned long)>', 'CEffTrackCustomShape', 'matrix<2,1,float>', 'std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >', 'std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >', 'CG_UI', 'C3DSpark', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffModel::*)(unsigned long)>', 'std::vector<RoleTask,std::allocator<RoleTask> >', 'primitive<3,float>', 'gbGeomNode', 'MXTransport', 'gbSound3DNode', 'CEmitter', 'gbIndexBubble', 'sg_emitter', 'gbPartEmitter', 'PtrArray', 'CResistanceMotionPolicy', 'Reoccupy', 'UICursor', 'gbImage2D', 'std::vector<sCollision,std::allocator<sCollision> >', 'CEffgbParticle', 'CEffect', 'CAcceleratedMotionPolicy', 'UITitle_BBTY', 'PropUI', 'std::basic_ios<char,std::char_traits<char> >', 'CCBProtectWindow', 'std::vector<unsigned long,std::allocator<unsigned long> >', 'UIHeadDialog', 'std::basic_streambuf<unsigned short,std::char_traits<unsigned short> >', 'UIFlexBar', 'ScreenFadeIn', 'UnderWater', 'std::basic_ostream<char,std::char_traits<char> >::sentry', 'ComposeUI', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<sdffb3b8a', 'CCBRoleState', '_TimeMgr', 'gbDropGroup', 'UIListBox', 'UITabCtrl', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAudio::*)(unsigned long)>', 'CEffSParticle', 'CEffCylinder', 'GRPinput', 'std::vector<CParticleSystem *,std::allocator<CParticleSystem *> >', 'RestScript', 'gbLightObj', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >::const_iterator', 'gbEmitterShape', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffShock::*)(unsigned long)>', 'gbActor', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffgbParticle::*)(unsigned long)>', 'UIAnimate', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >::const_iterator', 'matrix<4,1,float>', 'Collide_Ray<3,float>', 'CEffectSystem', 'gbBinkVideo', 'std::deque<RC_ARG,std::allocator<RC_ARG> >', 'UIStaticCB', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:7cbc3be5', 'gbPartParamControl', 'ProtectPanel', 'MainEquipUI', 'std::vector<vert<float>,std::allocator<vert<float> > >', 'C2DSpark', 'CEffTrackCylinder', 'CEffCustomShape', 'SkyboxEffMgr', 'std::vector<ArcSceneObject,std::allocator<ArcSceneObject> >', 'std::ctype<unsigned short>', 'UIRoleSelect', 'Scene', 'UIAnimateCtrl', 'NavigationInfo', 'CCBEditor', '_Item_List_Info', 'CIniFile', 'UIEmote', 'Inventory', 'std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >', 'CCBStageCam', 'MyMdl', 'HeadMsg', 'COnceFramePolicy', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >::sentry', 'std::stack<RC_ARG,std::deque<RC_ARG,std::allocator<RC_ARG> > >', 'scSCEFile', 'UITitle_JDHY', 'SwitchVariable', 'CCBParabolaWindow', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:83de5b43', 'BillBoardFace', 'gbNBTreeNode', 'ARC_Reoccupy', 'RenderTarget', 'std::vector<SoundItem,std::allocator<SoundItem> >', 'std::runtime_error', 'CEffShock', 'gbKeyControler', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuad::*)(unsigned long)>', 'gbSound2DNode', 'util', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >', 'CPK', 'CEffCallBack', 'TaskMgr<SceneObjParam,unsigned long (__thiscall SceneObj::*)(unsigned long)>', 'CFadeColorPolicy', 'CCBSystem', 'UI3DObj', '_Console', 'StringTable', 'gbSnow', 'SceneMap', 'gbIndexPool', 'RoleCamera', 'Object3D', 'UIButton', 'std::basic_ostream<unsigned short,std::char_traits<unsigned short> >::sentry', 'Archive', 'CPolicy', 'MXFire', 'std::vector<EffectItem,std::allocator<EffectItem> >', 'CCBAIWindow', 'gbPrintFontMgr', 'LineupUI', 'UISceneMap', 'CEffBink', 'UIButtonEX', 'SaleUI', 'CPKFile', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >::const_iterator', 'CEffTrackSParticle', 'ChoseCompose', 'CParticleSystem', 'CCBMagicWindow', 'MXSavePoint', 'std::codecvt<char,char,int>', 'CCBSkillWindow', 'GlowObj', 'std::locale::id', 'gbTexture', 'CEffTrackGrid', 'sg_particle', 'ScreenEffect', 'UICaption', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffGrid::*)(unsigned long)>', 'PalScriptWaitObj', 'LineupComp', 'CCBItemWindow', 'CCBUI', 'CCBFiveNimbusWindow', 'gbMatrixStack', 'gbRenderEffect', 'std::fpos<int>', 'std::locale::_Locimp', 'MainPropUI', 'CEffTrackQuad', 'CEffGrid', 'CReBackFramePolicy', 'RoleCameraCtrl', 'gbGfxManager', 'UIFrameWnd', 'UIWnd', 'KeyFrame', 'gbVFile1', 'CEffTrackModel', 'CEffMgr', 'RoleFadeOut', 'gbVertPoolMgr', 'std::basic_filebuf<char,std::char_traits<char> >', 'std::bitset<48>::reference', 'RoleShadow', 'SceneObj', 'UIGameFrm', 'CCBStageShadow', 'PathFinder', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuake::*)(unsigned long)>', 'RoleFadeIn', 'CEffObj', 'gbVertexBubble', 'PurgeEffect', 'gbParticleGroup', 'sg_customshape', 'std::deque<RC_ARG,std::allocator<RC_ARG> >::const_iterator', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffSParticle::*)(unsigned long)>', 'std::locale::facet', 'std::basic_filebuf<unsigned short,std::char_traits<unsigned short> >', 'SkyBox', 'matrix<3,3,float>', 'gbRefObject', 'MagicUI', 'Glow', 'std::vector<gbVec3D,std::allocator<gbVec3D> >', 'gbPrintFont', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >', 'CCCTData', 'CEffModel', 'NameSys', 'PalScript', 'OpenBaseFile', 'Role', 'DealUI', 'gbChain1D', 'gbTexture_D3D', 'LayerNode', 'UIDialog', 'std::_Timevec', 'ObjLockInput', 'std::ios_base', 'UISceneFrm', 'UIStaticEXA', 'UI3DCtrl', 'CEffExplosive', 'ObjectCamera', 'ARC_Inventory', 'UIMap', 'std::vector<PlayerItem,std::allocator<PlayerItem> >', 'graph', 'std::vector<int,std::allocator<int> >', 'std::basic_istream<char,std::char_traits<char> >::sentry', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >::const_iterator', 'std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >', 'std::vector<gbVec2D,std::allocator<gbVec2D> >', 'MU_SortFun', 'RotateInvObj', 'CCBLineupWindow', 'std::vector<ArcSceneMonster,std::allocator<ArcSceneMonster> >', 'OpenNULLFile', 'gbResManager', 'Object', 't3DModel', 'scVarStack', 'CTrail', 'std::binder2nd<std::not_equal_to<SceneProp *> >', 'UITitle_YXXX', 'ParticleEffect', 'gbDynArray_pgbResource', 'std::basic_istream<char,std::char_traits<char> >', 'SceneMapPlayer', 'Average', 'gbVertexPool', 'UIBigMap', 'RotateObj', 'UIRoleSelectDialog', 'CRotateEmitterPolicy', 'TimeCtl', 'matrix<3,2,float>', 'UIChatRest', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCamera::*)(unsigned long)>', 'SCNFile', 'gbEffectMgr', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTemplate::*)(unsigned long)>', 'UIStatic', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffBink::*)(unsigned long)>', 'UISceneFace', 'CSEHException', 'UIPushButton', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >', 'std::vector<t3DObject,std::allocator<t3DObject> >', 'std::basic_string<char,std::char_traits<char>,std::allocator<char> >', 'CCBControl', 'CCBStageEffect', 'XJ_Pic', 'CEffAudio', 'std::numpunct<unsigned short>', 'gbResource', 'UIPosMaker', 'std::ostreambuf_iterator<char,std::char_traits<char> >', 'std::vector<GlowObj *,std::allocator<GlowObj *> >', 'UIGroupCtrl', 'CG_Scene', 'UITextArea', 'sg_particle_scene', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<s11db03a2', 'CLoad3DS', 'CEffAction', 'std::istreambuf_iterator<char,std::char_traits<char> >', 'UIStaticFlip', 'UITitle_QCYM', 'exception', 'gbChain1DNode', 'std::_Locinfo', 'std::vector<KeyFrame *,std::allocator<KeyFrame *> >', 'std::vector<Triangle,std::allocator<Triangle> >', 'UICoverFrm', 'AStarPathFinder', 'ScreenEffectMgr', 'gbCamControler', 'std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >', 'std::codecvt<unsigned short,char,int>', 'UIGameOver', 'std::vector<gbActor *,std::allocator<gbActor *> >', 'CCBCamControl', 'Actor', 'SystemUI', 'UITabBtn', 'std::ostreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'gbVFileSystem', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCylinder::*)(unsigned long)>', 'std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >', 'CEffMeteor', 'std::queue<ScreenEffect *,std::deque<ScreenEffect *,std::allocator<ScreenEffect *> > >', 'UITitle_ArcSave', 'gbAnimScript', 'DealData', 'std::istreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'PlayerItemSortFun', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffMeteor::*)(unsigned long)>', 'matrix<3,1,float>', 'JusticeBookUI', 'CCBStageScene', 'PAL_GDB', 'std::vector<primitive<3,float> *,std::allocator<primitive<3,float> *> >']:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                count += 1
        log(f"  可访问结构体: {count}/420")

        # Step 2: Clear Hex-Rays cache for affected functions
        log("")
        log("[STEP 2] 清除 Hex-Rays 反编译缓存...")
        cleared = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Only clear functions belonging to imported classes
            cls = name.split("::")[0] if "::" in name else ""
            if cls in {'CCBControlWindow', 'CParticleEffect', 'CCBStageRole', 'UINote', 'std::vector<ArcPastScene,std::allocator<ArcPastScene> >', 'std::vector<ArcScene,std::allocator<ArcScene> >', 'std::locale', 'gbAudioManager', 'SwordUI', 'CJ_FindFile', 'std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >', 'ScriptWaitFrm', 'gbSoundData', 'gbParticleEffect', 'RoleTaskPool', 'PalScriptIdleObj', 'gbGfxManager_D3D', 'gbMeshSection', 'std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAction::*)(unsigned long)>', 'UIStaticEX', 'UILoadingFrm', 'gbCursorRes', 'std::numpunct<char>', 'CArrayList', 'CG_Edit', 'std::bitset<48>', 'std::list<SceneProp *,std::allocator<SceneProp *> >::const_iterator', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCallBack::*)(unsigned long)>', 'UIPar_TimeCtrl', 'CCBResultWindow', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >', '_Item', 'GrayScale', 'std::vector<EffectInfo,std::allocator<EffectInfo> >', 'CCBStage', 'UITitle_XJTM', 'gbPixelFormat', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffExplosive::*)(unsigned long)>', 'sg_emission_control', '_TextureLib_Data', 'CCBAI', 'FindArc', 'ARC_PAL_GDB', 'UIStaticFlex', 'std::bitset<10>::reference', 'UIButtonEXA', 'std::binder2nd<std::not_equal_to<COLLIDE_DATA> >', 'gbBaseMesh', 'SkyboxEff', 'UIParticle', 'MXCEft', 'std::basic_streambuf<char,std::char_traits<char> >', 'std::basic_string<unsigned short,std::char_traits<unsigned short>,std::allocator<unsigned short> >', 'UIPar_Star', 'vert<float>', 'std::vector<scScriptBlock *,std::allocator<scScriptBlock *> >', 'std::logic_error', 'gbSceneGraph', 'matrix<3,4,float>', 'EquipUI', 'std::vector<PlayerSkill,std::allocator<PlayerSkill> >', 'ParabolaCalculator', 'StateUI', 'TaskBookUI', 'MXPoisonFog', 'UIAnimateCtrlEX', 'std::list<SceneProp *,std::allocator<SceneProp *> >', 'gbVisNode', 'std::basic_ios<unsigned short,std::char_traits<unsigned short> >', 'MUIDialog', 'MeshFx', 'UITextureArray', 'UIRoleDialog', 'gbDynVertBuf', 'CCBDisplayChain', 'UIProgressBar', 'gbVolModNode', 'ConfigFile', 'gbActorDef', 'gbActorMgr', 'CG_Entry', 'SoundMgr', 'std::ctype<char>', 'Comp_DonateUI', 'CEffQuad', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCustomShape::*)(unsigned long)>', 'std::bitset<10>', 'CD3DSettings', 'gbCycleQueue_gbNodeMsgObj', 'CMeteorChain', 'gbCamera', 'CCBAttackSequen', 'CD3DEnumeration', 'UIPar_Meteor', 'TxtFile', 'SceneMapObj', 'ORect', 'UIScrollBar', 'UIDragBar', 'UIStaticRM', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTime::*)(unsigned long)>', 'CEffTrackCustomShape', 'matrix<2,1,float>', 'std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >', 'std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >', 'CG_UI', 'C3DSpark', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffModel::*)(unsigned long)>', 'std::vector<RoleTask,std::allocator<RoleTask> >', 'primitive<3,float>', 'gbGeomNode', 'MXTransport', 'gbSound3DNode', 'CEmitter', 'gbIndexBubble', 'sg_emitter', 'gbPartEmitter', 'PtrArray', 'CResistanceMotionPolicy', 'Reoccupy', 'UICursor', 'gbImage2D', 'std::vector<sCollision,std::allocator<sCollision> >', 'CEffgbParticle', 'CEffect', 'CAcceleratedMotionPolicy', 'UITitle_BBTY', 'PropUI', 'std::basic_ios<char,std::char_traits<char> >', 'CCBProtectWindow', 'std::vector<unsigned long,std::allocator<unsigned long> >', 'UIHeadDialog', 'std::basic_streambuf<unsigned short,std::char_traits<unsigned short> >', 'UIFlexBar', 'ScreenFadeIn', 'UnderWater', 'std::basic_ostream<char,std::char_traits<char> >::sentry', 'ComposeUI', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<sdffb3b8a', 'CCBRoleState', '_TimeMgr', 'gbDropGroup', 'UIListBox', 'UITabCtrl', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAudio::*)(unsigned long)>', 'CEffSParticle', 'CEffCylinder', 'GRPinput', 'std::vector<CParticleSystem *,std::allocator<CParticleSystem *> >', 'RestScript', 'gbLightObj', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >::const_iterator', 'gbEmitterShape', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffShock::*)(unsigned long)>', 'gbActor', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffgbParticle::*)(unsigned long)>', 'UIAnimate', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >::const_iterator', 'matrix<4,1,float>', 'Collide_Ray<3,float>', 'CEffectSystem', 'gbBinkVideo', 'std::deque<RC_ARG,std::allocator<RC_ARG> >', 'UIStaticCB', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:7cbc3be5', 'gbPartParamControl', 'ProtectPanel', 'MainEquipUI', 'std::vector<vert<float>,std::allocator<vert<float> > >', 'C2DSpark', 'CEffTrackCylinder', 'CEffCustomShape', 'SkyboxEffMgr', 'std::vector<ArcSceneObject,std::allocator<ArcSceneObject> >', 'std::ctype<unsigned short>', 'UIRoleSelect', 'Scene', 'UIAnimateCtrl', 'NavigationInfo', 'CCBEditor', '_Item_List_Info', 'CIniFile', 'UIEmote', 'Inventory', 'std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >', 'CCBStageCam', 'MyMdl', 'HeadMsg', 'COnceFramePolicy', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >::sentry', 'std::stack<RC_ARG,std::deque<RC_ARG,std::allocator<RC_ARG> > >', 'scSCEFile', 'UITitle_JDHY', 'SwitchVariable', 'CCBParabolaWindow', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:83de5b43', 'BillBoardFace', 'gbNBTreeNode', 'ARC_Reoccupy', 'RenderTarget', 'std::vector<SoundItem,std::allocator<SoundItem> >', 'std::runtime_error', 'CEffShock', 'gbKeyControler', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuad::*)(unsigned long)>', 'gbSound2DNode', 'util', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >', 'CPK', 'CEffCallBack', 'TaskMgr<SceneObjParam,unsigned long (__thiscall SceneObj::*)(unsigned long)>', 'CFadeColorPolicy', 'CCBSystem', 'UI3DObj', '_Console', 'StringTable', 'gbSnow', 'SceneMap', 'gbIndexPool', 'RoleCamera', 'Object3D', 'UIButton', 'std::basic_ostream<unsigned short,std::char_traits<unsigned short> >::sentry', 'Archive', 'CPolicy', 'MXFire', 'std::vector<EffectItem,std::allocator<EffectItem> >', 'CCBAIWindow', 'gbPrintFontMgr', 'LineupUI', 'UISceneMap', 'CEffBink', 'UIButtonEX', 'SaleUI', 'CPKFile', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >::const_iterator', 'CEffTrackSParticle', 'ChoseCompose', 'CParticleSystem', 'CCBMagicWindow', 'MXSavePoint', 'std::codecvt<char,char,int>', 'CCBSkillWindow', 'GlowObj', 'std::locale::id', 'gbTexture', 'CEffTrackGrid', 'sg_particle', 'ScreenEffect', 'UICaption', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffGrid::*)(unsigned long)>', 'PalScriptWaitObj', 'LineupComp', 'CCBItemWindow', 'CCBUI', 'CCBFiveNimbusWindow', 'gbMatrixStack', 'gbRenderEffect', 'std::fpos<int>', 'std::locale::_Locimp', 'MainPropUI', 'CEffTrackQuad', 'CEffGrid', 'CReBackFramePolicy', 'RoleCameraCtrl', 'gbGfxManager', 'UIFrameWnd', 'UIWnd', 'KeyFrame', 'gbVFile1', 'CEffTrackModel', 'CEffMgr', 'RoleFadeOut', 'gbVertPoolMgr', 'std::basic_filebuf<char,std::char_traits<char> >', 'std::bitset<48>::reference', 'RoleShadow', 'SceneObj', 'UIGameFrm', 'CCBStageShadow', 'PathFinder', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuake::*)(unsigned long)>', 'RoleFadeIn', 'CEffObj', 'gbVertexBubble', 'PurgeEffect', 'gbParticleGroup', 'sg_customshape', 'std::deque<RC_ARG,std::allocator<RC_ARG> >::const_iterator', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffSParticle::*)(unsigned long)>', 'std::locale::facet', 'std::basic_filebuf<unsigned short,std::char_traits<unsigned short> >', 'SkyBox', 'matrix<3,3,float>', 'gbRefObject', 'MagicUI', 'Glow', 'std::vector<gbVec3D,std::allocator<gbVec3D> >', 'gbPrintFont', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >', 'CCCTData', 'CEffModel', 'NameSys', 'PalScript', 'OpenBaseFile', 'Role', 'DealUI', 'gbChain1D', 'gbTexture_D3D', 'LayerNode', 'UIDialog', 'std::_Timevec', 'ObjLockInput', 'std::ios_base', 'UISceneFrm', 'UIStaticEXA', 'UI3DCtrl', 'CEffExplosive', 'ObjectCamera', 'ARC_Inventory', 'UIMap', 'std::vector<PlayerItem,std::allocator<PlayerItem> >', 'graph', 'std::vector<int,std::allocator<int> >', 'std::basic_istream<char,std::char_traits<char> >::sentry', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >::const_iterator', 'std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >', 'std::vector<gbVec2D,std::allocator<gbVec2D> >', 'MU_SortFun', 'RotateInvObj', 'CCBLineupWindow', 'std::vector<ArcSceneMonster,std::allocator<ArcSceneMonster> >', 'OpenNULLFile', 'gbResManager', 'Object', 't3DModel', 'scVarStack', 'CTrail', 'std::binder2nd<std::not_equal_to<SceneProp *> >', 'UITitle_YXXX', 'ParticleEffect', 'gbDynArray_pgbResource', 'std::basic_istream<char,std::char_traits<char> >', 'SceneMapPlayer', 'Average', 'gbVertexPool', 'UIBigMap', 'RotateObj', 'UIRoleSelectDialog', 'CRotateEmitterPolicy', 'TimeCtl', 'matrix<3,2,float>', 'UIChatRest', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCamera::*)(unsigned long)>', 'SCNFile', 'gbEffectMgr', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTemplate::*)(unsigned long)>', 'UIStatic', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffBink::*)(unsigned long)>', 'UISceneFace', 'CSEHException', 'UIPushButton', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >', 'std::vector<t3DObject,std::allocator<t3DObject> >', 'std::basic_string<char,std::char_traits<char>,std::allocator<char> >', 'CCBControl', 'CCBStageEffect', 'XJ_Pic', 'CEffAudio', 'std::numpunct<unsigned short>', 'gbResource', 'UIPosMaker', 'std::ostreambuf_iterator<char,std::char_traits<char> >', 'std::vector<GlowObj *,std::allocator<GlowObj *> >', 'UIGroupCtrl', 'CG_Scene', 'UITextArea', 'sg_particle_scene', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<s11db03a2', 'CLoad3DS', 'CEffAction', 'std::istreambuf_iterator<char,std::char_traits<char> >', 'UIStaticFlip', 'UITitle_QCYM', 'exception', 'gbChain1DNode', 'std::_Locinfo', 'std::vector<KeyFrame *,std::allocator<KeyFrame *> >', 'std::vector<Triangle,std::allocator<Triangle> >', 'UICoverFrm', 'AStarPathFinder', 'ScreenEffectMgr', 'gbCamControler', 'std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >', 'std::codecvt<unsigned short,char,int>', 'UIGameOver', 'std::vector<gbActor *,std::allocator<gbActor *> >', 'CCBCamControl', 'Actor', 'SystemUI', 'UITabBtn', 'std::ostreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'gbVFileSystem', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCylinder::*)(unsigned long)>', 'std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >', 'CEffMeteor', 'std::queue<ScreenEffect *,std::deque<ScreenEffect *,std::allocator<ScreenEffect *> > >', 'UITitle_ArcSave', 'gbAnimScript', 'DealData', 'std::istreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'PlayerItemSortFun', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffMeteor::*)(unsigned long)>', 'matrix<3,1,float>', 'JusticeBookUI', 'CCBStageScene', 'PAL_GDB', 'std::vector<primitive<3,float> *,std::allocator<primitive<3,float> *> >'}:
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

    import builtins
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
