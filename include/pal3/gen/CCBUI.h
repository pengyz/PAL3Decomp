#pragma once
// Auto-generated from IDA decomp - CCBUI
// 47 methods

class CCBUI {
public:
    int GetState();  // 0x004DC560
    int SetParam(int a2, int a3);  // 0x004DC5C0
    int Update();  // 0x004E04C0
    char UpdateInput();  // 0x004E0690
    char UpdateDisplay();  // 0x004E0740
    char UpdateAnimation();  // 0x004E0820
    char UpdateState();  // 0x004E0980
    char ~CCBUI();  // 0x00517650
    char Reset();  // 0x005177B0
    char CreateCombatPanel();  // 0x00517B30
    char CreateAttackSequen();  // 0x00517C10
    char CreateBattleFieldAttr();  // 0x00517C80
    char CreateControlWindow();  // 0x00517D60
    char CreateItemWindow();  // 0x00517DF0
    char CreateParaWindow();  // 0x005181E0
    static int (__thiscall ***__thiscall(_DWORD *this))(_DWORD, _DWORD) CreateMagicWindow();  // 0x005183C0
    int CreateSkillWindow(char a2);  // 0x005184C0
    int CreateLineupWindow(int a2, char a3);  // 0x00518AF0
    char CreateProtectWindow();  // 0x00518B20
    char CreateResultWindow(char a2);  // 0x00518B30
    int CreateFiveNimbus(char a2);  // 0x00518D40
    int HideAll();  // 0x00518E60
    int ShowBattleFieldAttr(int a2);  // 0x00518FE0
    int ShowControlWindow(int a2);  // 0x00519080
    int ShowDialogWindow();  // 0x00519200
    char ShowAIWindow(int a2);  // 0x00519230
    char IsResultWindowClosed(int a2, int a3, int a4, int a5, int a6, int a7, int a8, const void *a9);  // 0x00519260
    static stdiobuf *__thiscall(stdiobuf *Block, char a2) ShowLineupWindow();  // 0x00519360
    int OnMessage();  // 0x005193D0
    char CreateImbibeNimbus(_DWORD *a2, int a3);  // 0x00519400
    int ConfigImbibeNimbus();  // 0x00519510
    int CheckNimbusMove(int a2, unsigned int a3, int a4);  // 0x005195E0
    BOOL IsImbibeNimbusNotFinish(int a2, int a3);  // 0x00519660
    static struct gbVFileSystem *__thiscall(gbRefObject ***this) SetNimbusToNimbusControl();  // 0x005196C0
    char WriteNimbusToPlayerMgr(_DWORD *a2, int a3, int a4, int a5);  // 0x00519A10
    static stdiobuf *__thiscall(stdiobuf *Block, char a2) GetNimbusColor();  // 0x00519B40
    int Render();  // 0x00519BB0
    static char __userpurge@<al>(int a1@<ecx>, int a2@<ebx>, int a3@<ebp>, int a4@<edi>, int a5@<esi>, _DWORD *a6, int a7) CreateButton();  // 0x00519BD0
    int DeleteUIObj();  // 0x00519F50
    int AddRightControlButtonAni(int a2, unsigned int a3, int a4);  // 0x00519FE0
    BOOL AddResultWindowAni(int a2, int a3);  // 0x0051A090
    int ChangeSpecStateLum();  // 0x0051A0F0
    char LineMove(_DWORD *a2, int a3, int a4, int a5);  // 0x0051A1D0
    int GravityDown(int a2);  // 0x0051A2B0
    static _DWORD *__thiscall(_DWORD *this) ChangeNumTxt();  // 0x0051A340
    static stdiobuf *__thiscall(stdiobuf *Block, char a2) DoTask();  // 0x0051A390
    char AddTask(_DWORD *a2, int a3);  // 0x0051A430
};
