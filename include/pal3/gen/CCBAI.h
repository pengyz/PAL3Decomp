#pragma once
// Auto-generated from IDA decomp - CCBAI
// 52 methods

class CCBAI {
public:
    static char Thunk_GetValue(int a1, int a2);  // 0x004014F0
    static void *__thiscall(CCBAI *this, void *pOut) GetTargetRole();  // 0x0040CFE0
    static int() CCBAI();  // 0x004D6FF0
    static int() ~CCBAI();  // 0x004D7030
    static int() Reset();  // 0x004D7040
    static _DWORD *__thiscall(_DWORD *this, _DWORD *a2) Create();  // 0x004D7080
    char Init();  // 0x004D70C0
    int Update();  // 0x004D7100
    char Render(int a2);  // 0x004D7120
    char HandleEnemyAction(int a2);  // 0x004D71E0
    char HandleEnemyWell(int a2);  // 0x004D7820
    char HandleEnemyWeak(int a2);  // 0x004D7EF0
    char HandleEnemyChaos(int a2);  // 0x004D86D0
    char HandleFriendAction(int a2);  // 0x004D8760
    char HandleFriendNegative(int a2);  // 0x004D8AF0
    char HandleFriendAffirmative(int a2, char a3);  // 0x004D8F20
    char HandlePlayerNormalAttack(int a2, int a3);  // 0x004D9130
    static void *__thiscall(_DWORD *this) RepeatPlayerLastOperation();  // 0x004D9360
    static _DWORD *__thiscall(_DWORD *this) SetNewRole();  // 0x004D9380
    int FillAllDemandSatisfy();  // 0x004D93D0
    char DemandThreadTracer();  // 0x004D94F0
    char DemandChecker(unsigned int a2, int a3, int a4);  // 0x004D9740
    char CastNormalAttack(int a2, int a3, int a4);  // 0x004D9920
    char CastRecoverMagic(int a2, int a3);  // 0x004D9A70
    char CastRecoverBigMagic(int a2, int a3, int a4);  // 0x004D9BA0
    char CastAttackMagic(int a2, int a3);  // 0x004D9D00
    char CastAttackBigMagic(int a2, int a3);  // 0x004D9E20
    char CastSpecifyMagic(int a2, int a3, int a4);  // 0x004D9F50
    char CastBFAMagic(int a2, int a3);  // 0x004DA0A0
    char CastBFAAttackMagic(int a2, int a3, int a4);  // 0x004DA1D0
    char CastRandEnemyMagic(int a2, int a3);  // 0x004DA350
    char CastRecoverSkill(int a2, int a3, int a4);  // 0x004DA4F0
    char CastRecoverBigSkill(int a2, int a3);  // 0x004DA640
    char CastAttackSkill(int a2, int a3, int a4);  // 0x004DA770
    char CastAttackBigSkill(int a2, int a3);  // 0x004DA900
    char CastRecoverItem(int a2, int a3, int a4);  // 0x004DAA40
    char CastRecoverBigItem(int a2, int a3, int a4);  // 0x004DAB70
    char CastAttackItem(int a2, int a3, int a4);  // 0x004DACA0
    char CastAttackBigItem(int a2, int a3, int a4);  // 0x004DADD0
    char CastBossPhysicalAttack(int a2, int a3, int a4);  // 0x004DAF00
    char CastReviveMagic(int a2, int a3, int a4);  // 0x004DB030
    char CastReviveSkill(int a2);  // 0x004DB160
    static int() CastCureSpecStateMagic();  // 0x004DB270
    static int() CastCureSpecStateSkill();  // 0x004DB280
    static void() CastCureSpecStateItem();  // 0x004DB290
    static void() HasVeryPunyFiveMagicRole();  // 0x004DB2A0
    static int() CreateValueAutomation();  // 0x004DB2B0
    static int() AddValueFunction();  // 0x004DB2C0
    static int() AddValueItem();  // 0x004DB300
    static int() DestroyValueAutomation();  // 0x004DB310
    static int() RunValueAutomation();  // 0x004DB350
    static int() SpecAI();  // 0x004DB360
};
