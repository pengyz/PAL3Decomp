"""
IDAPython: 批量导入 PDB 结构体定义 (43 个)
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
LOG_FILE = os.path.join(LOG_DIR, "ida_import_P3_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x00558000

STRUCT_HEADER = r"""
struct UIHeadDialog;
struct UIStatic;
struct UIStaticFlex;
struct UIButton;
struct _TimeMgr;
struct MUIDialog;
struct UIFlexBar;
struct UIScrollBar;
struct UIListBox;
struct UITabBtn;
struct UIAnimateCtrl;
struct UI3DCtrl;
struct SaleUI;
struct TaskBookUI;
struct PurgeEffect;
struct EquipUI;
struct UIParticle;
struct Inventory;
struct TimeCtl;
struct SwordUI;
struct UIPushButton;
struct ProtectPanel;
struct Object3D;
struct LineupUI;
struct UITextArea;
struct PropUI;
struct StateUI;
struct UIDialog;
struct MainEquipUI;
struct UIAnimate;
struct MagicUI;
struct UIDragBar;
struct SystemUI;
struct DealUI;
struct UIRoleSelect;
struct UIStaticFlip;
struct UIRoleDialog;
struct LineupComp;
struct Comp_DonateUI;
struct MainPropUI;
struct JusticeBookUI;
struct UIRoleSelectDialog;
struct ComposeUI;

struct UIHeadDialog {
    char _gap_0[80];
    Role * m_role;
    int m_width;
    int m_height;
    gbTexture * m_bktex;
    char m_text[256];
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

struct _TimeMgr {
    unsigned int newtick;
    unsigned int oldtick;
    unsigned char bNote;
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

struct UITabBtn {
    char m_BtnAndID[16]; // std::vector<_Btn_BtnID,std::allocator<_Btn_BtnID> >
    int m_SelBtn;
    UIWnd * m_pFather;
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

struct PurgeEffect {
    gbTexture * pSrcTex;
    gbImage2D pSrcImg;
    gbImage2D pDstImg;
    int m_ItemNum;
    char EffItem[16]; // std::vector<EffectItem,std::allocator<EffectItem> >
    unsigned char m_isUpdateMerge;
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

struct Inventory {
    char m_items[16]; // std::vector<PlayerItem,std::allocator<PlayerItem> >
    int m_curtype;
    char m_typeitems[16]; // std::vector<PlayerItem,std::allocator<PlayerItem> >
    int m_money;
};

struct TimeCtl {
    unsigned int newtick;
    unsigned int oldtick;
    unsigned char bNote;
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

struct UITextArea {
    char _gap_0[68];
    char m_buf[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    char m_page[16]; // std::basic_string<char,std::char_traits<char>,std::allocator<char> >
    unsigned char m_bInvalidate;
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

struct UIDialog {
    char _gap_0[68];
    int m_bmodal;
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

struct UIAnimate {
    unsigned int m_sec;
    char m_Rc[16]; // tagRECT
    char m_Rc2[16]; // tagRECT
    unsigned char m_IsLoop[4];
    TimeCtl m_Time;
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

struct UIRoleSelect {
    char _gap_0[80];
    int m_sel;
    int m_maxlen;
    UIListBox m_list;
    UIStaticFlex m_bk;
};

struct UIStaticFlip {
    char _gap_0[160];
    char flipMode[4]; // _FLIP
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
        for name in ['UIHeadDialog', 'SaleUI', 'TaskBookUI', 'PurgeEffect', 'EquipUI', 'UIScrollBar', 'UIStatic', 'SwordUI', 'LineupUI', 'UITextArea', 'PropUI', 'StateUI', 'UIDialog', 'UIFlexBar', 'TimeCtl', '_TimeMgr', 'MainEquipUI', 'MagicUI', 'ProtectPanel', 'SystemUI', 'Inventory', 'DealUI', 'UITabBtn', 'Comp_DonateUI', 'UI3DCtrl', 'MainPropUI', 'UIStaticFlip', 'UIRoleDialog', 'JusticeBookUI', 'UIRoleSelectDialog', 'UIParticle', 'UIPushButton', 'UIStaticFlex', 'UIButton', 'UIAnimate', 'ComposeUI', 'UIDragBar', 'UIRoleSelect', 'MUIDialog', 'UIListBox', 'Object3D', 'UIAnimateCtrl', 'LineupComp']:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                count += 1
        log(f"  可访问结构体: {count}/43")

        # Step 2: Clear Hex-Rays cache for affected functions
        log("")
        log("[STEP 2] 清除 Hex-Rays 反编译缓存...")
        cleared = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Only clear functions belonging to imported classes
            cls = name.split("::")[0] if "::" in name else ""
            if cls in {'UIHeadDialog', 'SaleUI', 'TaskBookUI', 'PurgeEffect', 'EquipUI', 'UIScrollBar', 'UIStatic', 'SwordUI', 'LineupUI', 'UITextArea', 'PropUI', 'StateUI', 'UIDialog', 'UIFlexBar', 'TimeCtl', '_TimeMgr', 'MainEquipUI', 'MagicUI', 'ProtectPanel', 'SystemUI', 'Inventory', 'DealUI', 'UITabBtn', 'Comp_DonateUI', 'UI3DCtrl', 'MainPropUI', 'UIStaticFlip', 'UIRoleDialog', 'JusticeBookUI', 'UIRoleSelectDialog', 'UIParticle', 'UIPushButton', 'UIStaticFlex', 'UIButton', 'UIAnimate', 'ComposeUI', 'UIDragBar', 'UIRoleSelect', 'MUIDialog', 'UIListBox', 'Object3D', 'UIAnimateCtrl', 'LineupComp'}:
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
