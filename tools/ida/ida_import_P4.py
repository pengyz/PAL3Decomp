"""
IDAPython: 批量导入 PDB 结构体定义 (314 个)
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
LOG_FILE = os.path.join(LOG_DIR, "ida_import_P4_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x00558000

STRUCT_HEADER = r"""
struct UnderWater;
struct UITextureArray;
struct UIAnimateCtrl;
struct UIEmote;
struct UIDragBar;
struct CEffgbParticle;
struct CArrayList;
struct CEffMeteor;
struct ScriptWaitFrm;
struct MXPoisonFog;
struct UIButtonEXA;
struct UIStaticFlex;
struct UIStatic;
struct _TimeMgr;
struct UIButton;
struct MUIDialog;
struct UITitle_BBTY;
struct UITabBtn;
struct ParticleEffect;
struct MXTransport;
struct CLoad3DS;
struct CEffectSystem;
struct UIProgressBar;
struct UIPushButton;
struct ProtectPanel;
struct CEffMgr;
struct sg_emission_control;
struct C3DSpark;
struct UIFlexBar;
struct UIScrollBar;
struct sg_customshape;
struct sg_emitter;
struct sg_particle;
struct sg_particle_scene;
struct GlowObj;
struct std::locale::_Locimp;
struct CEffTrackCustomShape;
struct RoleCamera;
struct CEffTrackSParticle;
struct _Console;
struct TxtFile;
struct PAL_GDB;
struct DealData;
struct std::locale;
struct CEffGrid;
struct UIGroupCtrl;
struct CCCTData;
struct UIButtonEX;
struct HeadMsg;
struct gbImage2D;
struct COnceFramePolicy;
struct CEffect;
struct CEffModel;
struct ARC_PAL_GDB;
struct ARC_Inventory;
struct ScreenFadeIn;
struct ScreenEffectMgr;
struct scVarStack;
struct std::locale::facet;
struct SceneMap;
struct CReBackFramePolicy;
struct std::_Timevec;
struct SceneMapPlayer;
struct C2DSpark;
struct std::logic_error;
struct CPK;
struct RoleCameraCtrl;
struct PathFinder;
struct RestScript;
struct CRotateEmitterPolicy;
struct TimeCtl;
struct UIAnimate;
struct Object;
struct CEmitter;
struct UIPar_Meteor;
struct Average;
struct UIPar_Star;
struct UIStaticEXA;
struct UICoverFrm;
struct PtrArray;
struct UIWnd;
struct UITitle_JDHY;
struct RotateObj;
struct CJ_FindFile;
struct KeyFrame;
struct UITitle_QCYM;
struct CEffBink;
struct RoleFadeOut;
struct UI3DObj;
struct UI3DCtrl;
struct CEffQuad;
struct StringTable;
struct GRPinput;
struct XJ_Pic;
struct MXCEft;
struct MeshFx;
struct CEffSParticle;
struct ConfigFile;
struct _Item_List_Info;
struct PurgeEffect;
struct MXSavePoint;
struct ScreenEffect;
struct UICursor;
struct CSEHException;
struct PalScriptWaitObj;
struct UIPosMaker;
struct UIMap;
struct UIAnimateCtrlEX;
struct FindArc;
struct UIListBox;
struct UIRoleSelect;
struct UISceneFace;
struct OpenNULLFile;
struct CEffCallBack;
struct CEffTrackModel;
struct ARC_Reoccupy;
struct BillBoardFace;
struct UIChatRest;
struct GrayScale;
struct RoleShadow;
struct CEffAudio;
struct gbTexture_D3D;
struct RenderTarget;
struct _Item;
struct UITitle_XJTM;
struct UIStaticEX;
struct UISceneMap;
struct UISceneFrm;
struct UIStaticFlip;
struct CPKFile;
struct Object3D;
struct LineupComp;
struct RotateInvObj;
struct CEffExplosive;
struct OpenBaseFile;
struct ChoseCompose;
struct UIHeadDialog;
struct UIStaticCB;
struct CEffObj;
struct t3DModel;
struct CEffAction;
struct CEffCylinder;
struct UICaption;
struct UITextArea;
struct UIRoleDialog;
struct UINote;
struct UIGameFrm;
struct std::ios_base;
struct SwitchVariable;
struct CD3DEnumeration;
struct CPolicy;
struct UILoadingFrm;
struct SkyboxEff;
struct SkyboxEffMgr;
struct SCNFile;
struct SoundMgr;
struct Reoccupy;
struct AStarPathFinder;
struct _TextureLib_Data;
struct CAcceleratedMotionPolicy;
struct CResistanceMotionPolicy;
struct CEffTrackQuad;
struct UITitle_ArcSave;
struct RoleFadeIn;
struct ORect;
struct Archive;
struct graph;
struct Inventory;
struct LayerNode;
struct CParticleEffect;
struct UIPar_TimeCtrl;
struct exception;
struct MU_SortFun;
struct UIGameOver;
struct CIniFile;
struct ObjLockInput;
struct MXFire;
struct UITitle_YXXX;
struct std::locale::id;
struct CMeteorChain;
struct CTrail;
struct Glow;
struct NameSys;
struct std::_Locinfo;
struct SkyBox;
struct UIStaticRM;
struct ObjectCamera;
struct CEffTrackGrid;
struct CEffCustomShape;
struct PalScriptIdleObj;
struct RoleTaskPool;
struct CD3DSettings;
struct util;
struct ParabolaCalculator;
struct scSCEFile;
struct UIBigMap;
struct CParticleSystem;
struct CEffTrackCylinder;
struct CEffShock;
struct UIFrameWnd;
struct PlayerItemSortFun;
struct UITabCtrl;
struct UIParticle;
struct std::runtime_error;
struct CFadeColorPolicy;

struct UnderWater {
    unsigned char m_bEnable;
    void * m_pIB;
    void * m_pVB;
    void * m_pBumpmapTex;
    int m_iMode;
    float m_fTime;
};

struct UITextureArray {
    gbTexture * m_ptex[16];
    int m_num;
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

struct UIEmote {
    char _gap_0[76];
    char m_cur[4]; // UIEMOTE
    UIAnimateCtrl m_ani[14];
    Role * m_role;
    int m_loopcount;
    int m_nLoop[14];
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

struct CArrayList {
    char m_ArrayListType[4]; // ArrayListType
    void * m_pData;
    unsigned int m_BytesPerEntry;
    unsigned int m_NumEntries;
    unsigned int m_NumEntriesAllocated;
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

struct ScriptWaitFrm {
    char _gap_0[8];
    char m_frm[4]; // PAL3_FRAME
};

struct MXPoisonFog {
    char _gap_0[92];
    gbParticleEffect * m_pfog;
};

struct UIButtonEXA {
    char _gap_0[344];
    char m_optData[16]; // _btnOPTDATA
    int m_EnableMode;
    char m_color[4]; // gbColorQuad
    char m_enablecolor[4]; // gbColorQuad
    char m_surecolor[4]; // gbColorQuad
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

struct UITabBtn {
    char m_BtnAndID[16]; // std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >
    int m_SelBtn;
    UIWnd * m_pFather;
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

struct CLoad3DS {
    void * m_FilePointer;
    int m_pBuffer[50000];
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

struct GlowObj {
    char _gap_0[4];
    unsigned char m_bEnable;
    int m_nStepSize;
    int m_nPass;
    char m_GeomColor[16]; // gbColorFlt
};

struct std::locale::_Locimp {
    char _gap_0[8];
    void * _Fv;
    unsigned int _Nfv;
    int _Cat;
    unsigned char _Xpar;
    char _Name[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
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

struct CEffTrackSParticle {
    char _gap_0[100];
    t3DModel * m_pTrack;
    float m_fTrackSpeed;
    float m_fTrackDecPart;
    int m_nCurrTrackPos;
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

struct TxtFile {
    char m_token[512];
    char * m_buf;
    char * m_sectionstart;
    char * m_curpos;
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

struct std::locale {
    void * _Ptr;
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

struct CCCTData {
    char m_Pool[408000]; // tagCCT[2000]
    unsigned char m_bPoolInUse[2000];
    char m_nCCTIndex[20000]; // int[100][50]
};

struct UIButtonEX {
    char _gap_0[344];
    char m_optData[48]; // _btnOPTDATA[3]
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

struct COnceFramePolicy {
    char _gap_0[12];
    float _fSpeed;
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

struct ARC_PAL_GDB {
    char m_head[160]; // ARC_OutFile
    char m_RoleData[170400]; // ARC_RoleAtt[200]
    char m_SkillData[228000]; // ARC_FightSkill[300]
    char m_ItemData[400000]; // ARC_FightItem[500]
    char m_ComboData[6320]; // ARC_ComboAttack[10]
    int i;
    unsigned char mLoaded;
};

struct ARC_Inventory {
    char m_items[16]; // std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >
    int m_curtype;
    char m_typeitems[16]; // std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >
    int m_money;
};

struct ScreenFadeIn {
    char _gap_0[24];
    int m_first;
};

struct ScreenEffectMgr {
    char _gap_0[4];
    ScreenFadeIn m_fadeIn;
    char m_fadeOut[24]; // ScreenFadeOut
    char m_fadeWhite[24]; // ScreenFadeWhite
    char m_fadeWhite2[24]; // ScreenFadeWhite2
    char m_activeQueue[48]; // std::queue<ScreenEffect *,std::deque<ScreenEffect *,std::allocator<ScreenEffect *> > >
};

struct scVarStack {
    int m_counter;
    char m_vararray[256]; // scVARIANT[32]
};

struct std::locale::facet {
    char _gap_0[4];
    unsigned int _Refs;
};

struct SceneMap {
    char _gap_0[4];
    int m_width;
    int m_height;
    unsigned char * m_map;
};

struct CReBackFramePolicy {
    char _gap_0[12];
    float _fSpeed;
};

struct std::_Timevec {
    void * _Ptr;
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

struct std::logic_error {
    char _gap_0[12];
    char _Str[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
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

struct PathFinder {
    char _gap_0[24];
    void * m_curlayer;
    int m_layer;
    Role * m_pRole;
};

struct RestScript {
    TxtFile m_LoadRest;
    char m_lastFile[256];
    char m_Data[1288]; // ScriptData
};

struct CRotateEmitterPolicy {
    char _gap_0[12];
    char _vAxis[12]; // gbVec3D
    float _fSpeed;
    float _fAngle;
};

struct TimeCtl {
    unsigned int newtick;
    unsigned int oldtick;
    unsigned char bNote;
};

struct UIAnimate {
    unsigned int m_sec;
    char m_Rc[16]; // tagRECT
    char m_Rc2[16]; // tagRECT
    unsigned char m_IsLoop[4];
    TimeCtl m_Time;
};

struct Object {
    char _gap_0[4];
    char position[12]; // gbVec3D
    float radius;
    char forward[12]; // gbVec3D
    char side[12]; // gbVec3D
    char up[12]; // gbVec3D
};

struct CEmitter {
    char _attr[220]; // CParticleSystem::EmitterAttribute
    int _nCurrTrackPos;
    float _fTrackDecPart;
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

struct UIStaticEXA {
    char _gap_0[192];
    int center_x;
    int center_y;
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

struct PtrArray {
    void * m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
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

struct RotateObj {
    char _gap_0[8];
    float m_passedtime;
    unsigned char end;
    char m_rotate[12]; // gbVec3D
    float m_rotatetime;
    unsigned char m_mode;
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

struct CEffBink {
    char _gap_0[48];
    char m_szBinkNamePrefix[128];
    char m_szBinkName[128];
};

struct RoleFadeOut {
    char _gap_0[8];
    float m_passedtime;
    Role * m_role;
    unsigned char end;
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

struct StringTable {
    char m_data[16]; // std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:83de5b43
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

struct XJ_Pic {
    char _gap_0[8];
    float m_fElapsed;
    unsigned char m_bEnd;
};

struct MXCEft {
    char _gap_0[92];
    unsigned int m_dwEffectID;
    unsigned int m_hEffect;
    char m_pos[12]; // gbVec3D
    float m_fTime;
};

struct MeshFx {
    char _gap_0[88];
    int m_iCurrentState;
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

struct ConfigFile {
    char m_filename[260];
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

struct PurgeEffect {
    gbTexture * pSrcTex;
    gbImage2D pSrcImg;
    gbImage2D pDstImg;
    int m_ItemNum;
    char EffItem[16]; // std::vector<EffectItem,std::allocator<EffectItem> >
    unsigned char m_isUpdateMerge;
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

struct ScreenEffect {
    char _gap_0[8];
    int m_blive;
    float m_life;
    float m_age;
    unsigned char m_hold;
};

struct UICursor {
    unsigned int m_dwID[3];
    char m_active[4]; // CURSOR_TYPE
    gbTexture * m_tex[3];
    unsigned char m_bShow;
    unsigned char m_bSoftMode;
};

struct CSEHException {
    unsigned int m_uiErrCode;
    char m_szExceptionString[260];
};

struct PalScriptWaitObj {
    char _gap_0[4];
    int m_needscriptdel;
};

struct UIPosMaker {
    unsigned char m_bIsLoaded;
    void * m_pUIPos;
    int m_nPosNum;
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

struct FindArc {
    char mPal3SetUpPath[256];
    char arcPos[9216]; // ArcPosition[36]
    int mRealNum;
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

struct UIRoleSelect {
    char _gap_0[80];
    int m_sel;
    int m_maxlen;
    UIListBox m_list;
    UIStaticFlex m_bk;
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

struct OpenNULLFile {
    gbVFileSystem * m_plastsys;
};

struct CEffCallBack {
    char _gap_0[48];
    float m_fStartX;
    float m_fStartY;
    float m_fStartZ;
    unsigned int m_dwRunningID;
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

struct ARC_Reoccupy {
    char m_id[16]; // std::vector<unsigned long,std::allocator<unsigned long> >
};

struct BillBoardFace {
    char m_texarray[68]; // gbTextureArray
    int m_curtex;
    int m_id;
    char m_pos[12]; // gbVec3D
    gbRenderEffect * m_effect;
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

struct GrayScale {
    unsigned char m_bEnable;
    gbTexture * m_pTex;
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

struct CEffAudio {
    char _gap_0[48];
    char m_szSoundNamePrefix[128];
    char m_szSoundName[512]; // char[4][128]
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

struct _Item {
    char title[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char info[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    unsigned char bHasChild;
    int nChildNum;
    unsigned char bIsPic;
    void * ppChildren;
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

struct UISceneFrm {
    char _gap_0[72];
    UISceneMap m_map;
    UISceneFace m_face;
};

struct UIStaticFlip {
    char _gap_0[160];
    char flipMode[4]; // _FLIP
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

struct RotateInvObj {
    char _gap_0[8];
    float m_passedtime;
    unsigned char end;
    char m_rotate[12]; // gbVec3D
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

struct OpenBaseFile {
    gbVFileSystem * m_plastsys;
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

struct UIHeadDialog {
    char _gap_0[80];
    Role * m_role;
    int m_width;
    int m_height;
    gbTexture * m_bktex;
    char m_text[256];
};

struct UIStaticCB {
    char _gap_0[160];
    int m_showct;
};

struct CEffObj {
    char _gap_0[4];
    CEffMgr * m_pEM;
    unsigned char m_bIdle;
};

struct t3DModel {
    int numOfObjects;
    int numOfMaterials;
    char pMaterials[16]; // std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >
    char pObject[16]; // std::vector<t3DObject,std::allocator<t3DObject> >
};

struct CEffAction {
    char _gap_0[48];
    int m_nController;
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

struct UINote {
    char _gap_0[72];
    UIStaticFlex m_static;
    float time;
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

struct SwitchVariable {
    unsigned int m_switchlimit;
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

struct CPolicy {
    char _gap_0[4];
    CParticleSystem * _pParticleSystem;
    unsigned int _dwPolicyId;
};

struct UILoadingFrm {
    char _gap_0[72];
    UIProgressBar m_LoadProgress;
    float m_anitime;
    int m_aniFlag;
    float m_MaxValue;
    unsigned char m_isOverProgress;
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

struct SkyboxEffMgr {
    float m_fSkyboxSize;
    SkyboxEff m_pEffArray[54];
};

struct SCNFile {
    char m_info[132]; // SceneInfo
    int m_numnpc;
    char m_npc[32832]; // NPCInfo[72]
    int m_numobj;
    char m_obj[154624]; // ObjectInfo[256]
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

struct Reoccupy {
    char m_id[16]; // std::vector<unsigned long,std::allocator<unsigned long> >
};

struct AStarPathFinder {
    char _gap_0[4];
    void * OPEN;
    void * CLOSED;
    void * PATH;
    void * Stack;
    int m_TestTimer;
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

struct CAcceleratedMotionPolicy {
    char _gap_0[12];
    char _vAcceleration[12]; // gbVec3D
};

struct CResistanceMotionPolicy {
    char _gap_0[12];
    char _vAcceleration[12]; // gbVec3D
    float _fConstant;
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

struct UITitle_ArcSave {
    char _gap_0[72];
    MUIDialog m_YesNo;
    MUIDialog m_Yes;
    MUIDialog m_Not1stDlg;
    UICoverFrm * m_father;
};

struct RoleFadeIn {
    char _gap_0[8];
    float m_passedtime;
    Role * m_role;
    unsigned char end;
};

struct ORect {
    char m_pt[32]; // tagPOINT[4]
    int m_numpt;
};

struct Archive {
    char m_scene[16]; // std::vector<ArcScene,std::allocator<ArcScene> >
    char m_past[16]; // std::vector<ArcPastScene,std::allocator<ArcPastScene> >
    char m_objNotLoad[16]; // std::vector<unsigned long,std::allocator<unsigned long> >
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

struct Inventory {
    char m_items[16]; // std::vector<PlayerItem,std::allocator<PlayerItem> >
    int m_curtype;
    char m_typeitems[16]; // std::vector<PlayerItem,std::allocator<PlayerItem> >
    int m_money;
};

struct LayerNode {
    char m_bound[24]; // gbAABBox
    int m_lv;
    char m_tri[16]; // std::vector<Triangle,std::allocator<Triangle> >
    LayerNode * m_child[4];
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

struct UIPar_TimeCtrl {
    unsigned int newtick;
    unsigned int oldtick;
    unsigned char bNote;
};

struct exception {
    char _gap_0[4];
    char * _m_what;
    int _m_doFree;
};

struct MU_SortFun {
    int m_by;
};

struct UIGameOver {
    char _gap_0[72];
    gbTexture * m_pbktex;
    UIStatic m_Blood;
    float m_fTime;
};

struct CIniFile {
    void * m_fp;
    int m_bRead;
};

struct ObjLockInput {
    PtrArray m_objs;
    PtrArray m_scripts;
    PtrArray m_scriptabs;
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

struct std::locale::id {
    unsigned int _Id;
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

struct Glow {
    gbRenderEffect * m_eft;
    gbRenderEffect * m_pGeomEft;
    int m_nPass;
    char m_pObjArray[16]; // std::vector<GlowObj *,std::allocator<GlowObj *> >
};

struct NameSys {
    char m_Flag[8]; // std::bitset<48>
    char m_FlagZZCC[4]; // std::bitset<10>
    int m_Ref[28];
    int m_RefMax[28];
    unsigned int m_CheckMax[10];
    char m_LastName[4]; // NameSys::NAMEFLAG
};

struct std::_Locinfo {
    char _Days[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char _Months[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char _Oname[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char _Nname[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
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

struct PalScriptIdleObj {
    char _gap_0[8];
    float m_time;
    float m_passedtime;
};

struct RoleTaskPool {
    char m_TaskData[16]; // std::vector<RoleTask,std::allocator<RoleTask> >
    char m_TaskLine[16]; // std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >
    TxtFile m_taskFile;
    char _TaskPicFolder[128];
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

struct util {
    unsigned int Crc32Table[256];
    unsigned int m_dwIDHolder;
    int m_nRandHolder;
    int m_nRandCallCount;
    CIniFile * m_pIniReader;
    CLoad3DS * m_pLoader3DS;
};

struct ParabolaCalculator {
    char velocity[12]; // gbVec3D
    char A[12]; // gbVec3D
    char B[12]; // gbVec3D
    float H;
    float G;
    char m_state[4]; // ParabolaCalculator::PRBL_STATE
};

struct scSCEFile {
    void * m_fp;
    char m_blocks[16]; // std::vector<scScriptBlock *,std::allocator<scScriptBlock *> >
    unsigned short m_blocknum;
    void * m_pindex;
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

struct UIFrameWnd {
    char _gap_0[68];
    gbTexture * m_pbktex;
};

struct PlayerItemSortFun {
    int m_by;
};

struct UITabCtrl {
    char _gap_0[68];
    int m_itemwidth;
    UITextureArray m_texarray;
    int m_numpage;
    int m_onpage;
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

struct std::runtime_error {
    char _gap_0[12];
    char _Str[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
};

struct CFadeColorPolicy {
    char _gap_0[12];
    char _vBeginColor[12]; // gbVec3D
    char _vEndColor[12]; // gbVec3D
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
        for name in ['UnderWater', 'UIEmote', 'UIDragBar', 'CEffgbParticle', 'CArrayList', 'CEffMeteor', 'ScriptWaitFrm', 'MXPoisonFog', 'std::bitset<10>::reference', 'UITitle_BBTY', 'std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >', 'UITabBtn', 'MXTransport', 'CLoad3DS', 'CEffectSystem', 'vert<float>', 'ProtectPanel', 'CEffMgr', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCustomShape::*)(unsigned long)>', 'sg_emission_control', 'C3DSpark', 'UIScrollBar', 'sg_particle_scene', 'GlowObj', 'matrix<4,1,float>', 'std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >', 'std::vector<vert<float>,std::allocator<vert<float> > >', 'std::locale::_Locimp', 'CEffTrackCustomShape', 'std::vector<PlayerItem,std::allocator<PlayerItem> >', 'RoleCamera', 'std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >', 'std::stack<RC_ARG,std::deque<RC_ARG,std::allocator<RC_ARG> > >', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >', 'CEffTrackSParticle', '_Console', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAudio::*)(unsigned long)>', 'std::codecvt<char,char,int>', 'DealData', 'std::basic_streambuf<char,std::char_traits<char> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTemplate::*)(unsigned long)>', 'std::vector<SoundItem,std::allocator<SoundItem> >', 'CEffGrid', 'std::basic_istream<char,std::char_traits<char> >', 'UIGroupCtrl', 'CCCTData', 'UIButtonEX', 'HeadMsg', 'gbImage2D', 'COnceFramePolicy', 'CEffect', 'Collide_Ray<3,float>', 'std::list<SceneProp *,std::allocator<SceneProp *> >::const_iterator', 'CEffModel', 'ARC_PAL_GDB', 'UIButtonEXA', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCylinder::*)(unsigned long)>', 'ARC_Inventory', 'ScreenEffectMgr', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffExplosive::*)(unsigned long)>', 'scVarStack', 'std::locale::facet', 'SceneMap', 'CReBackFramePolicy', 'std::_Timevec', 'SceneMapPlayer', 'std::locale', 'C2DSpark', 'std::logic_error', 'CPK', 'RoleCameraCtrl', 'std::vector<gbVec3D,std::allocator<gbVec3D> >', 'std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >', 'PathFinder', 'RestScript', 'CRotateEmitterPolicy', 'UIAnimate', '_TimeMgr', 'Object', 'CEmitter', 'std::list<SceneProp *,std::allocator<SceneProp *> >', 'UICoverFrm', 'UIWnd', 'UITitle_JDHY', 'RotateObj', 'CJ_FindFile', 'KeyFrame', 'std::vector<sCollision,std::allocator<sCollision> >', 'std::basic_istream<char,std::char_traits<char> >::sentry', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffModel::*)(unsigned long)>', 'std::vector<ArcSceneObject,std::allocator<ArcSceneObject> >', 'std::vector<ArcScene,std::allocator<ArcScene> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTime::*)(unsigned long)>', 'UITitle_QCYM', 'CEffBink', 'RoleFadeOut', 'UI3DCtrl', 'sg_emitter', 'sg_customshape', 'CEffQuad', 'UIProgressBar', 'std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >', 'UIStatic', 'StringTable', 'std::binder2nd<std::not_equal_to<SceneProp *> >', 'GRPinput', 'std::queue<ScreenEffect *,std::deque<ScreenEffect *,std::allocator<ScreenEffect *> > >', 'XJ_Pic', 'std::fpos<int>', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffgbParticle::*)(unsigned long)>', 'MXCEft', 'std::numpunct<char>', 'std::codecvt<unsigned short,char,int>', 'MeshFx', 'std::vector<primitive<3,float> *,std::allocator<primitive<3,float> *> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffGrid::*)(unsigned long)>', 'CEffSParticle', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAction::*)(unsigned long)>', 'ConfigFile', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCallBack::*)(unsigned long)>', '_Item_List_Info', 'std::istreambuf_iterator<char,std::char_traits<char> >', 'PurgeEffect', 'MXSavePoint', 'ScreenEffect', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffSParticle::*)(unsigned long)>', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuad::*)(unsigned long)>', 'UICursor', 'PtrArray', 'std::bitset<10>', 'CSEHException', 'PalScriptWaitObj', 'UIPosMaker', 'UIMap', 'UIAnimateCtrl', 'UIAnimateCtrlEX', 'FindArc', 'UIRoleSelect', 'sg_particle', 'std::vector<ArcSceneMonster,std::allocator<ArcSceneMonster> >', 'std::basic_ios<unsigned short,std::char_traits<unsigned short> >', 'UISceneFace', 'std::vector<unsigned long,std::allocator<unsigned long> >', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >::const_iterator', 'UIPar_Star', 'matrix<3,1,float>', 'std::vector<CParticleSystem *,std::allocator<CParticleSystem *> >', 'OpenNULLFile', 'std::vector<gbActor *,std::allocator<gbActor *> >', 'CEffCallBack', 'CEffTrackModel', 'ARC_Reoccupy', 'BillBoardFace', 'UIChatRest', 'std::vector<t3DObject,std::allocator<t3DObject> >', 'UI3DObj', 'GrayScale', 'std::basic_filebuf<unsigned short,std::char_traits<unsigned short> >', 'PAL_GDB', 'RoleShadow', 'std::vector<EffectItem,std::allocator<EffectItem> >', 'CEffAudio', 'std::vector<scScriptBlock *,std::allocator<scScriptBlock *> >', 'RenderTarget', 'UITitle_XJTM', 'matrix<3,4,float>', 'UISceneFrm', 'std::bitset<48>', 'UIStaticFlip', 'gbTexture_D3D', 'CPKFile', 'LineupComp', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >', 'std::basic_filebuf<char,std::char_traits<char> >', 'std::deque<RC_ARG,std::allocator<RC_ARG> >::const_iterator', 'RotateInvObj', 'CEffExplosive', 'OpenBaseFile', 'UIButton', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:7cbc3be5', 'std::vector<GlowObj *,std::allocator<GlowObj *> >', 'ChoseCompose', 'std::vector<KeyFrame *,std::allocator<KeyFrame *> >', 'UIHeadDialog', 'UIStaticCB', 'CEffObj', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >::sentry', 't3DModel', 'std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >', 'CEffAction', '_Item', 'CEffCylinder', 'UIGameFrm', 'primitive<3,float>', 'std::ios_base', 'SwitchVariable', 'CD3DEnumeration', 'CPolicy', 'UILoadingFrm', 'matrix<3,2,float>', 'SkyboxEffMgr', 'UITextureArray', 'std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >', 'SCNFile', 'SoundMgr', 'Reoccupy', 'AStarPathFinder', 'UIRoleDialog', '_TextureLib_Data', 'CAcceleratedMotionPolicy', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<sdffb3b8a', 'CResistanceMotionPolicy', 'CEffTrackQuad', 'UITitle_ArcSave', 'TaskMgr<SceneObjParam,unsigned long (__thiscall SceneObj::*)(unsigned long)>', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >::const_iterator', 'std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuake::*)(unsigned long)>', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >::const_iterator', 'ParticleEffect', 'std::vector<RoleTask,std::allocator<RoleTask> >', 'RoleFadeIn', 'ORect', 'std::vector<gbVec2D,std::allocator<gbVec2D> >', 'std::vector<Triangle,std::allocator<Triangle> >', 'std::vector<EffectInfo,std::allocator<EffectInfo> >', 'UIStaticFlex', 'Archive', 'graph', 'Inventory', 'Object3D', 'TimeCtl', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffBink::*)(unsigned long)>', 'std::basic_ostream<char,std::char_traits<char> >::sentry', 'UINote', 'LayerNode', 'CParticleEffect', 'std::ostreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'UIPar_TimeCtrl', 'UIStaticEX', 'std::basic_ostream<unsigned short,std::char_traits<unsigned short> >::sentry', 'exception', 'MU_SortFun', 'UISceneMap', 'UIGameOver', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:83de5b43', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >', 'CIniFile', 'std::basic_streambuf<unsigned short,std::char_traits<unsigned short> >', 'ObjLockInput', 'MXFire', 'UITitle_YXXX', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCamera::*)(unsigned long)>', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<s11db03a2', 'std::basic_string<char,std::char_traits<char>,std::allocator<char> >', 'std::vector<PlayerSkill,std::allocator<PlayerSkill> >', 'std::locale::id', 'SkyboxEff', 'CMeteorChain', 'UIPushButton', 'std::ctype<char>', 'std::numpunct<unsigned short>', 'UIListBox', 'CTrail', 'std::vector<ArcPastScene,std::allocator<ArcPastScene> >', 'Glow', 'NameSys', 'std::_Locinfo', 'std::bitset<48>::reference', 'std::binder2nd<std::not_equal_to<COLLIDE_DATA> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffShock::*)(unsigned long)>', 'SkyBox', 'UIStaticRM', 'UICaption', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffMeteor::*)(unsigned long)>', 'ObjectCamera', 'CEffTrackGrid', 'CEffCustomShape', 'UIStaticEXA', 'PalScriptIdleObj', 'RoleTaskPool', 'std::basic_string<unsigned short,std::char_traits<unsigned short>,std::allocator<unsigned short> >', 'CD3DSettings', 'util', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >::const_iterator', 'MUIDialog', 'ParabolaCalculator', 'UITextArea', 'scSCEFile', 'UIFlexBar', 'UIBigMap', 'CParticleSystem', 'Average', 'std::deque<RC_ARG,std::allocator<RC_ARG> >', 'std::vector<int,std::allocator<int> >', 'CEffTrackCylinder', 'TxtFile', 'CEffShock', 'UIFrameWnd', 'UIPar_Meteor', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >', 'PlayerItemSortFun', 'std::basic_ios<char,std::char_traits<char> >', 'std::istreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'matrix<2,1,float>', 'std::ostreambuf_iterator<char,std::char_traits<char> >', 'matrix<3,3,float>', 'UITabCtrl', 'UIParticle', 'std::runtime_error', 'ScreenFadeIn', 'std::ctype<unsigned short>', 'CFadeColorPolicy']:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                count += 1
        log(f"  可访问结构体: {count}/314")

        # Step 2: Clear Hex-Rays cache for affected functions
        log("")
        log("[STEP 2] 清除 Hex-Rays 反编译缓存...")
        cleared = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Only clear functions belonging to imported classes
            cls = name.split("::")[0] if "::" in name else ""
            if cls in {'UnderWater', 'UIEmote', 'UIDragBar', 'CEffgbParticle', 'CArrayList', 'CEffMeteor', 'ScriptWaitFrm', 'MXPoisonFog', 'std::bitset<10>::reference', 'UITitle_BBTY', 'std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >', 'UITabBtn', 'MXTransport', 'CLoad3DS', 'CEffectSystem', 'vert<float>', 'ProtectPanel', 'CEffMgr', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCustomShape::*)(unsigned long)>', 'sg_emission_control', 'C3DSpark', 'UIScrollBar', 'sg_particle_scene', 'GlowObj', 'matrix<4,1,float>', 'std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >', 'std::vector<vert<float>,std::allocator<vert<float> > >', 'std::locale::_Locimp', 'CEffTrackCustomShape', 'std::vector<PlayerItem,std::allocator<PlayerItem> >', 'RoleCamera', 'std::vector<CParticleSystem::TexCoordQuad,std::allocator<CParticleSystem::TexCoordQuad> >', 'std::stack<RC_ARG,std::deque<RC_ARG,std::allocator<RC_ARG> > >', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >', 'CEffTrackSParticle', '_Console', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAudio::*)(unsigned long)>', 'std::codecvt<char,char,int>', 'DealData', 'std::basic_streambuf<char,std::char_traits<char> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTemplate::*)(unsigned long)>', 'std::vector<SoundItem,std::allocator<SoundItem> >', 'CEffGrid', 'std::basic_istream<char,std::char_traits<char> >', 'UIGroupCtrl', 'CCCTData', 'UIButtonEX', 'HeadMsg', 'gbImage2D', 'COnceFramePolicy', 'CEffect', 'Collide_Ray<3,float>', 'std::list<SceneProp *,std::allocator<SceneProp *> >::const_iterator', 'CEffModel', 'ARC_PAL_GDB', 'UIButtonEXA', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCylinder::*)(unsigned long)>', 'ARC_Inventory', 'ScreenEffectMgr', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffExplosive::*)(unsigned long)>', 'scVarStack', 'std::locale::facet', 'SceneMap', 'CReBackFramePolicy', 'std::_Timevec', 'SceneMapPlayer', 'std::locale', 'C2DSpark', 'std::logic_error', 'CPK', 'RoleCameraCtrl', 'std::vector<gbVec3D,std::allocator<gbVec3D> >', 'std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >', 'PathFinder', 'RestScript', 'CRotateEmitterPolicy', 'UIAnimate', '_TimeMgr', 'Object', 'CEmitter', 'std::list<SceneProp *,std::allocator<SceneProp *> >', 'UICoverFrm', 'UIWnd', 'UITitle_JDHY', 'RotateObj', 'CJ_FindFile', 'KeyFrame', 'std::vector<sCollision,std::allocator<sCollision> >', 'std::basic_istream<char,std::char_traits<char> >::sentry', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffModel::*)(unsigned long)>', 'std::vector<ArcSceneObject,std::allocator<ArcSceneObject> >', 'std::vector<ArcScene,std::allocator<ArcScene> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffTime::*)(unsigned long)>', 'UITitle_QCYM', 'CEffBink', 'RoleFadeOut', 'UI3DCtrl', 'sg_emitter', 'sg_customshape', 'CEffQuad', 'UIProgressBar', 'std::vector<primitive<3,float>,std::allocator<primitive<3,float> > >', 'UIStatic', 'StringTable', 'std::binder2nd<std::not_equal_to<SceneProp *> >', 'GRPinput', 'std::queue<ScreenEffect *,std::deque<ScreenEffect *,std::allocator<ScreenEffect *> > >', 'XJ_Pic', 'std::fpos<int>', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffgbParticle::*)(unsigned long)>', 'MXCEft', 'std::numpunct<char>', 'std::codecvt<unsigned short,char,int>', 'MeshFx', 'std::vector<primitive<3,float> *,std::allocator<primitive<3,float> *> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffGrid::*)(unsigned long)>', 'CEffSParticle', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffAction::*)(unsigned long)>', 'ConfigFile', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCallBack::*)(unsigned long)>', '_Item_List_Info', 'std::istreambuf_iterator<char,std::char_traits<char> >', 'PurgeEffect', 'MXSavePoint', 'ScreenEffect', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffSParticle::*)(unsigned long)>', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuad::*)(unsigned long)>', 'UICursor', 'PtrArray', 'std::bitset<10>', 'CSEHException', 'PalScriptWaitObj', 'UIPosMaker', 'UIMap', 'UIAnimateCtrl', 'UIAnimateCtrlEX', 'FindArc', 'UIRoleSelect', 'sg_particle', 'std::vector<ArcSceneMonster,std::allocator<ArcSceneMonster> >', 'std::basic_ios<unsigned short,std::char_traits<unsigned short> >', 'UISceneFace', 'std::vector<unsigned long,std::allocator<unsigned long> >', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >::const_iterator', 'UIPar_Star', 'matrix<3,1,float>', 'std::vector<CParticleSystem *,std::allocator<CParticleSystem *> >', 'OpenNULLFile', 'std::vector<gbActor *,std::allocator<gbActor *> >', 'CEffCallBack', 'CEffTrackModel', 'ARC_Reoccupy', 'BillBoardFace', 'UIChatRest', 'std::vector<t3DObject,std::allocator<t3DObject> >', 'UI3DObj', 'GrayScale', 'std::basic_filebuf<unsigned short,std::char_traits<unsigned short> >', 'PAL_GDB', 'RoleShadow', 'std::vector<EffectItem,std::allocator<EffectItem> >', 'CEffAudio', 'std::vector<scScriptBlock *,std::allocator<scScriptBlock *> >', 'RenderTarget', 'UITitle_XJTM', 'matrix<3,4,float>', 'UISceneFrm', 'std::bitset<48>', 'UIStaticFlip', 'gbTexture_D3D', 'CPKFile', 'LineupComp', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >', 'std::basic_filebuf<char,std::char_traits<char> >', 'std::deque<RC_ARG,std::allocator<RC_ARG> >::const_iterator', 'RotateInvObj', 'CEffExplosive', 'OpenBaseFile', 'UIButton', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:7cbc3be5', 'std::vector<GlowObj *,std::allocator<GlowObj *> >', 'ChoseCompose', 'std::vector<KeyFrame *,std::allocator<KeyFrame *> >', 'UIHeadDialog', 'UIStaticCB', 'CEffObj', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >::sentry', 't3DModel', 'std::vector<RoleTaskLine,std::allocator<RoleTaskLine> >', 'CEffAction', '_Item', 'CEffCylinder', 'UIGameFrm', 'primitive<3,float>', 'std::ios_base', 'SwitchVariable', 'CD3DEnumeration', 'CPolicy', 'UILoadingFrm', 'matrix<3,2,float>', 'SkyboxEffMgr', 'UITextureArray', 'std::vector<ARC_PlayerItem,std::allocator<ARC_PlayerItem> >', 'SCNFile', 'SoundMgr', 'Reoccupy', 'AStarPathFinder', 'UIRoleDialog', '_TextureLib_Data', 'CAcceleratedMotionPolicy', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<sdffb3b8a', 'CResistanceMotionPolicy', 'CEffTrackQuad', 'UITitle_ArcSave', 'TaskMgr<SceneObjParam,unsigned long (__thiscall SceneObj::*)(unsigned long)>', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >::const_iterator', 'std::vector<tMaterialInfo,std::allocator<tMaterialInfo> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffQuake::*)(unsigned long)>', 'std::list<COLLIDE_DATA,std::allocator<COLLIDE_DATA> >::const_iterator', 'ParticleEffect', 'std::vector<RoleTask,std::allocator<RoleTask> >', 'RoleFadeIn', 'ORect', 'std::vector<gbVec2D,std::allocator<gbVec2D> >', 'std::vector<Triangle,std::allocator<Triangle> >', 'std::vector<EffectInfo,std::allocator<EffectInfo> >', 'UIStaticFlex', 'Archive', 'graph', 'Inventory', 'Object3D', 'TimeCtl', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffBink::*)(unsigned long)>', 'std::basic_ostream<char,std::char_traits<char> >::sentry', 'UINote', 'LayerNode', 'CParticleEffect', 'std::ostreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'UIPar_TimeCtrl', 'UIStaticEX', 'std::basic_ostream<unsigned short,std::char_traits<unsigned short> >::sentry', 'exception', 'MU_SortFun', 'UISceneMap', 'UIGameOver', 'std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std:83de5b43', 'std::basic_istream<unsigned short,std::char_traits<unsigned short> >', 'std::deque<ScreenEffect *,std::allocator<ScreenEffect *> >', 'CIniFile', 'std::basic_streambuf<unsigned short,std::char_traits<unsigned short> >', 'ObjLockInput', 'MXFire', 'UITitle_YXXX', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffCamera::*)(unsigned long)>', 'std::_Tree<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char> > const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::map<s11db03a2', 'std::basic_string<char,std::char_traits<char>,std::allocator<char> >', 'std::vector<PlayerSkill,std::allocator<PlayerSkill> >', 'std::locale::id', 'SkyboxEff', 'CMeteorChain', 'UIPushButton', 'std::ctype<char>', 'std::numpunct<unsigned short>', 'UIListBox', 'CTrail', 'std::vector<ArcPastScene,std::allocator<ArcPastScene> >', 'Glow', 'NameSys', 'std::_Locinfo', 'std::bitset<48>::reference', 'std::binder2nd<std::not_equal_to<COLLIDE_DATA> >', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffShock::*)(unsigned long)>', 'SkyBox', 'UIStaticRM', 'UICaption', 'CTaskTpl<tagEffTaskParam,unsigned long (__thiscall CEffMeteor::*)(unsigned long)>', 'ObjectCamera', 'CEffTrackGrid', 'CEffCustomShape', 'UIStaticEXA', 'PalScriptIdleObj', 'RoleTaskPool', 'std::basic_string<unsigned short,std::char_traits<unsigned short>,std::allocator<unsigned short> >', 'CD3DSettings', 'util', 'std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> >::const_iterator', 'MUIDialog', 'ParabolaCalculator', 'UITextArea', 'scSCEFile', 'UIFlexBar', 'UIBigMap', 'CParticleSystem', 'Average', 'std::deque<RC_ARG,std::allocator<RC_ARG> >', 'std::vector<int,std::allocator<int> >', 'CEffTrackCylinder', 'TxtFile', 'CEffShock', 'UIFrameWnd', 'UIPar_Meteor', 'std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> >', 'PlayerItemSortFun', 'std::basic_ios<char,std::char_traits<char> >', 'std::istreambuf_iterator<unsigned short,std::char_traits<unsigned short> >', 'matrix<2,1,float>', 'std::ostreambuf_iterator<char,std::char_traits<char> >', 'matrix<3,3,float>', 'UITabCtrl', 'UIParticle', 'std::runtime_error', 'ScreenFadeIn', 'std::ctype<unsigned short>', 'CFadeColorPolicy'}:
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
