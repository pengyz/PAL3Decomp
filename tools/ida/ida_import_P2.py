"""
IDAPython: 批量导入 PDB 结构体定义 (42 个)
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
LOG_FILE = os.path.join(LOG_DIR, "ida_import_P2_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x00558000

STRUCT_HEADER = r"""
struct UIButton;
struct UIStatic;
struct MUIDialog;
struct CG_Entry;
struct CCBFiveNimbusWindow;
struct CCBSkillWindow;
struct CCBResultWindow;
struct CCBItemWindow;
struct CCBDisplayChain;
struct CCBAttackSequen;
struct UISceneMap;
struct UIProgressBar;
struct CCBStageCam;
struct TxtFile;
struct RoleCameraCtrl;
struct SceneObj;
struct CG_Scene;
struct CCBEditor;
struct gbVolModNode;
struct CCBStageEffect;
struct CCBStageScene;
struct CG_Edit;
struct CCBUI;
struct CCBRoleState;
struct CCBMagicWindow;
struct UIStaticRM;
struct PtrArray;
struct CCBParabolaWindow;
struct CCBStage;
struct CCBProtectWindow;
struct CCBAI;
struct CG_UI;
struct CCCTData;
struct CCBCamControl;
struct CCBControl;
struct CCBLineupWindow;
struct CCBStageShadow;
struct CCBSystem;
struct CCBStageRole;
struct CCBAIWindow;
struct CCBControlWindow;

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

struct CCBSkillWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIStatic * m_pDescription;
    UIListBox * m_pSkillList[1];
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

struct CCBDisplayChain {
    CCBStage * m_pStage;
    CCBStageScene * m_pScene;
    char m_DefaultColor[4]; // tagRGBQUAD
    char m_ScreenQuadColor[4]; // gbColorQuad
    int m_nItemNum;
    char m_ShowItem[17920]; // tagShowItem[64]
    unsigned char m_byScreenQuadAlpha;
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

struct TxtFile {
    char m_token[512];
    char * m_buf;
    char * m_sectionstart;
    char * m_curpos;
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

struct gbVolModNode {
    char _gap_0[88];
    char m_ToWorld[64]; // gbMatrix4
    char m_ToView[64]; // gbMatrix4
    void * m_pModObj;
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

struct PtrArray {
    void * m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
};

struct CCBParabolaWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIStatic * m_pDescription;
    UIListBox * m_pItemList;
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

struct CCBProtectWindow {
    char _gap_0[72];
    UIStatic * m_pBack;
    UIPushButton * m_pWHFace;
    UIPushButton * m_pWPXFace;
    UIProgressBar * m_pWHLove;
    UIProgressBar * m_pWPXLove;
    UIButton * m_pOk;
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

struct CCCTData {
    char m_Pool[408000]; // tagCCT[2000]
    unsigned char m_bPoolInUse[2000];
    char m_nCCTIndex[20000]; // int[100][50]
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

struct CCBLineupWindow {
    char _gap_0[72];
    int m_nInitRoleFaceLineup[5];
    UIStatic * m_pBack;
    UIStatic * m_pFace[5];
    int m_nSelected;
    CCBUI * m_pUI;
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
        for name in ['MUIDialog', 'CG_Entry', 'CCBFiveNimbusWindow', 'CCBSkillWindow', 'CCBResultWindow', 'CCBItemWindow', 'CCBDisplayChain', 'CCBAttackSequen', 'UISceneMap', 'UIStatic', 'UIProgressBar', 'CCBStageCam', 'CG_Scene', 'CCBEditor', 'CCBStageEffect', 'TxtFile', 'CCBStageScene', 'CG_Edit', 'CCBUI', 'CCBRoleState', 'std::list<SceneProp *,std::allocator<SceneProp *> >', 'SceneObj', 'RoleCameraCtrl', 'CCBMagicWindow', 'UIButton', 'UIStaticRM', 'PtrArray', 'CCBParabolaWindow', 'CCBStage', 'CCBProtectWindow', 'CCBAI', 'CG_UI', 'CCBCamControl', 'CCBControl', 'CCBLineupWindow', 'CCBStageShadow', 'gbVolModNode', 'CCBSystem', 'CCCTData', 'CCBStageRole', 'CCBAIWindow', 'CCBControlWindow']:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                count += 1
        log(f"  可访问结构体: {count}/42")

        # Step 2: Clear Hex-Rays cache for affected functions
        log("")
        log("[STEP 2] 清除 Hex-Rays 反编译缓存...")
        cleared = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Only clear functions belonging to imported classes
            cls = name.split("::")[0] if "::" in name else ""
            if cls in {'MUIDialog', 'CG_Entry', 'CCBFiveNimbusWindow', 'CCBSkillWindow', 'CCBResultWindow', 'CCBItemWindow', 'CCBDisplayChain', 'CCBAttackSequen', 'UISceneMap', 'UIStatic', 'UIProgressBar', 'CCBStageCam', 'CG_Scene', 'CCBEditor', 'CCBStageEffect', 'TxtFile', 'CCBStageScene', 'CG_Edit', 'CCBUI', 'CCBRoleState', 'std::list<SceneProp *,std::allocator<SceneProp *> >', 'SceneObj', 'RoleCameraCtrl', 'CCBMagicWindow', 'UIButton', 'UIStaticRM', 'PtrArray', 'CCBParabolaWindow', 'CCBStage', 'CCBProtectWindow', 'CCBAI', 'CG_UI', 'CCBCamControl', 'CCBControl', 'CCBLineupWindow', 'CCBStageShadow', 'gbVolModNode', 'CCBSystem', 'CCCTData', 'CCBStageRole', 'CCBAIWindow', 'CCBControlWindow'}:
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
