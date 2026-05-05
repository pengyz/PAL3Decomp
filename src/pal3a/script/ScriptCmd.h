#ifndef PAL3A_SCRIPTCMD_H
#define PAL3A_SCRIPTCMD_H

#include "pal3a_types.h"

class RoleFadeIn {
public:
    char _data[20];

    int IsWaiting();
    void ScriptUpdate(float deltatime);
    RoleFadeIn(Role * role);
};

class RoleFadeOut {
public:
    char _data[20];

    void ScriptUpdate(float deltatime);
    RoleFadeOut(Role * role);
    int IsWaiting();
};

class RotateInvObj {
public:
    char _data[28];

    void ScriptUpdate(float deltatime);
    int IsWaiting();
    RotateInvObj(gbVec3D * rotate);
};

class RotateObj {
public:
    char _data[36];

    RotateObj(gbVec3D * rotate, float rotatetime, uchar mode);
    void ScriptUpdate(float deltatime);
    ~RotateObj();
    int IsWaiting();
};

class ScriptWaitFrm {
public:
    char _data[12];

    ScriptWaitFrm(PAL3_FRAME frm);
    int IsWaiting();
};

class XJ_Pic {
public:
    char _data[16];

    int IsWaiting();
    ~XJ_Pic();
    XJ_Pic();
    void ScriptUpdate(float fDeltaTime);
};

void cmd_NGHVarianceCombat();
void cmd_StopSkyEff();
void cmd_RoleTurnFace();
void cmd_ENCAMP_Entry();
void cmd_WalkToByAct();
void cmd_RoleTurnFaceA();
void cmd_CombatWithMusic();
void cmd_EntrySmeltSys();
void cmd_RoleOverlap();
void cmd_AddMoney();
void cmd_RoleStop();
void cmd_CEft_Role();
void cmd_ActiveComposeRole();
void cmd_KF_Entry();
void cmd_SetRoleTexture();
void cmd_FogH();
void cmd_WaterMagic();
void cmd_FOP();
void cmd_GetHS_UnHock_type();
void cmd_RolePathTo();
void cmd_CameraMove();
void cmd_StartNGHEffect();
void cmd_AverageLv();
void cmd_RoleSetPos();
void cmd_LockCamForward();
void cmd_HaveItem();
void cmd_AddRoleAtt();
void cmd_Movie();
void cmd_FinalSave();
void cmd_InTeam();
void cmd_Rand();
void cmd_DlgFont();
void cmd_GetHS_Period_type();
void cmd_Dlg();
void cmd_RoleMoveTo();
void cmd_SelectEmote();
void cmd_ShowActAutoStand();
void cmd_GetSwitch();
void cmd_RoleFaceRole();
void cmd_GetRoleAtt();
void cmd_Specify_Compos();
void cmd_SetRoleAtt();
void cmd_JT_Exhibit();
void cmd_CombatMustFail();
void cmd_Between();
void cmd_HY_FLY();
void cmd_GetSelectEmote();
Role * FindRole(ushort id);
void cmd_DlgTime();
void cmd_DlgHead();
void cmd_Start_HideFight();
void cmd_GetMoney();
void cmd_GetDislike();
void cmd_RoleEmoteNW();
void cmd_CEft_Load();
void cmd_GoTo();
void cmd_HS_Entry();
void cmd_GetHS_ManageType();
void cmd_CameraFocusObject();
void cmd_RoleFadeOut();
void cmd_CameraFocusRole();
void cmd_CameraTrans();
void cmd_SetRolePosY();
void cmd_UnLockCamCenter();
void cmd_EntryRow();
void cmd_JT_EquipSword();
void cmd_AddTask();
void cmd_WPXVarianceCombat();
void cmd_GetHSLv();
void cmd_ScriptRunMode();
void cmd_DlgSel();
void cmd_RoleShowAction();
void cmd_RoleSpaceWalk();
void cmd_StopMusic();
void cmd_Caption2();
void cmd_CameraRotate_Vertical();
void cmd_CameraPush();
void cmd_HY_Mode();
void cmd_ScriptLockInput();
void cmd_StopNGHEffect();
void ClearCamObj();
void cmd_BOXActiveEX();
void cmd_SwitchRS();
void cmd_Idle();
void cmd_Get_Appr();
void cmd_GetCombat();
void cmd_FadeNormal();
void cmd_Enable_Sword();
void cmd_PX_Wild();
void cmd_ScrEft();
void cmd_RunSkyEff();
ACTION_KIND _Script_MapAct(ulong p);
void cmd_SetPXVariance();
void cmd_GetImbibeNimbusTimes();
void cmd_UnLockCamForward();
void cmd_Climb();
void cmd_FadeOut();
void cmd_APPR_Entry();
void cmd_EntrySkee();
void cmd_ObjectMove();
void cmd_ShowChatRest();
void cmd_CEft();
void cmd_FadeWhite();
void cmd_RoleSetFace();
void cmd_ShowAttackAct();
void cmd_Trigger();
void cmd_SetFiveNimbus();
void cmd_FavorAdd();
void cmd_InTeamNoMsg();
void cmd_Enable_JusticeBook();
void cmd_CameraRotate_Horizon();
void cmd_LK_Ghost();
void cmd_TeamOpen();
void cmd_TeamClose();
void AddCamObjToRuningInst(PalScriptWaitObj * obj);
void cmd_RemoveItem();
void cmd_PlaySound();
void cmd_CameraYaw();
void cmd_TeamOpenA();
void cmd_LoadScene();
void cmd_CameraDefault();
void cmd_Enable_SwordSkill();
void cmd_RotateInv();
void cmd_LockCamCenter();
void cmd_Music();
void cmd_Rain();
void cmd_RoleActive();
void cmd_Quake();
void cmd_RoleEndAction();
void cmd_RoleScript();
void cmd_TeamCloseA();
void cmd_DlgPos();
void cmd_ObjectActive();
void KillRuningInst();
void cmd_PushNote();
void cmd_CameraWag();
void cmd_FullRoleAtt();
void cmd_FinalCombat();
void cmd_SKEE_Entry();
void cmd_CG();
void cmd_CameraRotate();
void cmd_Dist();
void cmd_GiveCloth();
void cmd_Call();
void cmd_UnLockCamera();
void cmd_FullTeamAtt();
void cmd_CombatBoss();
void cmd_CombatNotGameOver();
void cmd_RoleScale();
void cmd_Add();
void cmd_ActiveFYS();
void cmd_GT();
scVARIANT * _SC_GET_PARAM();
void cmd_CameraPopState();
void cmd_GetFavor();
void cmd_Compose();
void cmd_SeekToSaveLoad();
void cmd_Bee();
void cmd_RolePathOut();
void cmd_LEQ();
void cmd_NEQ();
void cmd_Let();
void cmd_SetNPCNoTurn();
void cmd_GEQ();
void cmd_Sub();
void cmd_Start_Wolf();
void cmd_XJ_Pic();
void cmd_CombatMaxRound();
void cmd_FadeIn();
void cmd_RoleInput();
void _ScriptLog(char * s);
void ApplyFlag(int ret);
void cmd_OpenDoor();
void cmd_DoorClose();
void cmd_InitFlower();
void cmd_ObjNotLoad();
void cmd_CameraSet();
void AddWaitObjToRuningInst(PalScriptWaitObj * obj);
void cmd_GetDlgSel();
void cmd_RoleSetLayer();
void cmd_RefreshMapRect();
void cmd_GetHS_Accrual_type();
void cmd_FogD();
void cmd_SetRoleBlend();
void cmd_FNOT();
void cmd_AddSkill();
void cmd_CameraFree();
void cmd_CEft_Pos();
void cmd_RoleEmote();
void cmd_Switch2Menu();
void cmd_LS();
void cmd_FC();
void cmd_SetBigMapElement();
void cmd_AddItem();
void cmd_Note();
void cmd_LockCamera();
void cmd_CameraFocusPoint();
void cmd_Combat();
void cmd_Snow();
void cmd_Caption();
void cmd_Team();
void cmd_LoadAct();
void cmd_GetFavorite();
void cmd_CameraPushState();
void cmd_RoleCtrl();
void cmd_Rotate();
void cmd_DlgFace();
void cmd_TestGoto();
void cmd_CheckCameraRefer();
void cmd_IfInTeam();
void cmd_FinishTask();
void cmd_RoleMoveBack();
void cmd_Deal();
void cmd_EQ();
void cmd_RoleFadeIn();
void cmd_GetTimeSel();

#endif // PAL3A_SCRIPTCMD_H
