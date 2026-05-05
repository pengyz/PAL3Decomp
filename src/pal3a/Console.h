#ifndef PAL3A_CONSOLE_H
#define PAL3A_CONSOLE_H

#include "pal3a_types.h"

class _Console {
public:
    char _data[10540];

    void _CON_Help(char * agv);
    ~_Console();
    void Render();
    void Init();
    void OnChar(char c);
    void SetActive(int bActive);
    void RegCommand(void * fun, char * keyword, char * help);
    void RunCommand(char * str);
    void RunCommand();
    void Print(char * format);
    _Console();
};

void _CON_CameraEdit(char * agv);
void _CON_SwitchFrm(char * agv);
void _CON_RoleEmote(char * agv);
void _CON_RunScript(char * agv);
void _CON_RoleInTeam(char * agv);
void _CON_CBChangeMonster(char * agv);
void _CON_FinalSave(char * agv);
void _CON_Load(char * agv);
void _CON_GotoObject(char * agv);
void _CON_JumpFree(char * agv);
void _CON_ResetScn(char * agv);
void _CON_Camera(char * agv);
void _CON_CBLoadScene(char * agv);
void _CON_Caption2(char * agv);
void _CON_Caption(char * agv);
void _CON_CB_Nimbus(char * agv);
void _CON_CBRestart(char * agv);
char * GetCmdFromStr(char * pStr, int nCmdIndex);
void _CON_SkyEff(char * agv);
void _CON_CamLockHeight(char * agv);
void _CON_SetRoleBlend(char * agv);
void _CON_CB_ImbibeNimbus(char * agv);
void _CON_CBChangeWeapon(char * agv);
void _CON_Compose(char * agv);
void _CON_Exit(char * agv);
void _CON_CB_CoAtk(char * agv);
void _CON_SetFiveNimbus(char * agv);
void _CON_SetLV(char * agv);
void _CON_TestCombat(char * agv);
void _CON_FinishRoleTask(char * agv);
void _CON_ShowRoleRenderPos(char * agv);
void _CON_SelectEmote(char * agv);
void _CON_RolePosSety(char * agv);
void _CON_ActivePlayer(char * agv);
void _CON_AddItem(char * agv);
void _CON_Var(char * agv);
void _CON_LoadScript(char * agv);
void _CON_Save(char * agv);
void _CON_CB_WIN(char * agv);
void _CON_Favour(char * agv);
void _CON_AddRoleTask(char * agv);
void _CON_SetNimbus(char * agv);
void _CON_AddMoney(char * agv);
void _CON_EXP(char * agv);
void _CON_GameState(char * agv);
void _CON_LoadScene(char * agv);
void _CON_TEST_CG(char * agv);
void _CON_DisableFog(char * agv);
void _CON_Layer(char * agv);
void _CON_CamCollideMethod(char * agv);
void _CON_Nimbus(char * agv);

#endif // PAL3A_CONSOLE_H
