#pragma once
// Auto-generated: CGameData

#include "UIItem.h"

class CScreenMode;
class CUtil;
class SceneObj;
class UIScene;
class UIWnd;

class CGameData {
public:
    // vtable (7 methods, order matches binary layout)

    void * _vftable; // +0x0
    int m_nRoleCount; // +0x4
    int m_nItemCount; // +0x8
    int m_nMagicCount; // +0xC
    int m_nSceneCount; // +0x10
    int m_nStateFlags; // +0x14
    char * m_pItemData; // +0x18
    char * m_pMagicData; // +0x1C
    int m_nDataVersion; // +0x20
    char _gap_024[16]; // +0x24
    int m_bDataLoaded; // +0x34
    char _gap_038[4]; // +0x38
    int m_nLoadResult; // +0x3C
    int m_nGameTick; // +0x40
    int _field_044; // +0x44
    int m_nDataCRC; // +0x48
    int _d04C; // +0x4C
    int _d050; // +0x50
    int _d054; // +0x54
    int _d058; // +0x58
    int _d05C; // +0x5C
    int _d060; // +0x60
    int _d064; // +0x64
    float _d068; // +0x68
    int _d06C; // +0x6C
    int _d070; // +0x70
    char _gap_074[8]; // +0x74
    UIWnd * _d07C; // +0x7C
    char _gap_080[92]; // +0x80
    int m_nConfigFlags; // +0xDC
    char _gap_0E0[20]; // +0xE0
    UIScene * m_pStartScene; // +0xF4
    char _gap_0F8[8]; // +0xF8
    short m_nStartPos; // +0x100
    char _gap_102[2]; // +0x102
    UIWnd * m_nInit; // +0x104
    char _gap_108[12]; // +0x108
    UIWnd * m_nInitRoles; // +0x114
    char _gap_118[48]; // +0x118
    int _field_0148; // +0x148
    char _gap_14C[24]; // +0x14C
    int m_nSaveSlot; // +0x164
    char _gap_168[48]; // +0x168
    int m_nSceneTransFlag; // +0x198
    char _gap_19C[16]; // +0x19C
    int m_subObjA; // +0x1AC
    char _gap_1B0[80]; // +0x1B0
    int _todo_200; // +0x200
    char _gap_204[108]; // +0x204
    int m_nPlayerMoney; // +0x270
    int m_nMoneyAdd; // +0x274
    int m_nMoneySub; // +0x278
    int m_nStorePriceMod; // +0x27C
    BYTE m_bFlag280; // +0x280
    BYTE m_bFlag281; // +0x281
    BYTE m_bFlag282; // +0x282
    char _gap_283[1]; // +0x283
    int m_nReputation; // +0x284
    int m_nSceneLoadParam; // +0x288
    char m_bSceneLoaded; // +0x28C
    BYTE m_bSceneActive; // +0x28D
    char _gap_28E[2]; // +0x28E
    int m_nGameMode; // +0x290
    char _gap_294[68]; // +0x294
    int m_nBattleResult; // +0x2D8
    char _gap_2DC[4]; // +0x2DC
    int m_nMissionState; // +0x2E0
    char _gap_2E4[28]; // +0x2E4
    int m_nBattleCount; // +0x300
    char _gap_304[112]; // +0x304
    CScreenMode * m_RoleDataA; // +0x374
    char _gap_378[100]; // +0x378
    int _d3DC; // +0x3DC
    int _d3E0; // +0x3E0
    char _gap_3E4[28]; // +0x3E4
    int m_nWinCount; // +0x400
    char _gap_404[200]; // +0x404
    CScreenMode * m_RoleDataB; // +0x4CC
    char _gap_4D0[48]; // +0x4D0
    int m_nLossCount; // +0x500
    char _gap_504[48]; // +0x504
    int _d534; // +0x534
    int _d538; // +0x538
    char _gap_53C[196]; // +0x53C
    int m_nEscapeCount; // +0x600
    char _gap_604[32]; // +0x604
    CScreenMode * m_RoleDataC; // +0x624
    char _gap_628[100]; // +0x628
    int _d68C; // +0x68C
    int _d690; // +0x690
    char _gap_694[60]; // +0x694
    float m_fAnimTimer; // +0x6D0
    float m_fAnimSpeed; // +0x6D4
    char _gap_6D8[36]; // +0x6D8
    BYTE m_bAnimPaused; // +0x6FC
    char _gap_6FD[51]; // +0x6FD
    BYTE m_bAnimLoop; // +0x730
    char _gap_731[75]; // +0x731
    UIItem m_ItemSlotA; // +0x77C
    char _gap_780[300]; // +0x780
    void * m_pItemArray; // +0x8AC
    char _gap_8B0[4]; // +0x8B0
    int m_nInitItems; // +0x8B4
    int m_nItemCount2; // +0x8B8
    char _gap_8BC[12]; // +0x8BC
    int m_nEquipCount; // +0x8C8
    char _gap_8CC[8]; // +0x8CC
    int m_nConsumableCount; // +0x8D4
    char _gap_8D8[40]; // +0x8D8
    int m_nKeyItemCount; // +0x900
    char _gap_904[172]; // +0x904
    float m_fBGMVolume; // +0x9B0
    int m_nBGMState; // +0x9B4
    char _gap_9B8[796]; // +0x9B8
    BYTE m_bInitRoles; // +0xCD4
    char _gap_CD5[3]; // +0xCD5
    int _todo_CD8; // +0xCD8
    char _gap_CDC[12]; // +0xCDC
    BYTE _todo_CE8; // +0xCE8
    BYTE _todo_CE9; // +0xCE9
    char _gap_CEA[2]; // +0xCEA
    UIItem m_ItemSlotB; // +0xCEC
    char _gap_CF0[484]; // +0xCF0
    int m_nUIDialogId; // +0xED4
    char _gap_ED8[29]; // +0xED8
    BYTE m_bDialogActive; // +0xEF5
    char _gap_EF6[74]; // +0xEF6
    int m_nRender; // +0xF40
    char _gap_F44[68]; // +0xF44
    int m_nUIFlags; // +0xF88
    char _gap_F8C[468]; // +0xF8C
    float m_fUIColorR; // +0x1160
    int m_nUIColorMode; // +0x1164
    char _gap_1168[220]; // +0x1168
    UIItem m_ItemSlotC; // +0x1244
    char _gap_1248[332]; // +0x1248
    int m_UITitle; // +0x1394
    char _gap_1398[88]; // +0x1398
    float m_fUITransition; // +0x13F0
    char _gap_13F4[652]; // +0x13F4
    float m_fUIFadeAlpha; // +0x1680
    int m_nUIFadeState; // +0x1684
    char _gap_1688[276]; // +0x1688
    UIItem m_ItemSlotD; // +0x179C
    char _gap_17A0[368]; // +0x17A0
    float m_fSceneTimer; // +0x1910
    int m_nSceneState; // +0x1914
    char _gap_1918[648]; // +0x1918
    float m_fD90060; // +0x1BA0
    char _gap_1BA4[336]; // +0x1BA4
    int m_nScriptResult; // +0x1CF4
    BYTE m_bScriptActive; // +0x1CF8
    char _gap_1CF9[311]; // +0x1CF9
    float m_fEffectTimer; // +0x1E30
    int m_nEffectState; // +0x1E34
    char _gap_1E38[1752]; // +0x1E38
    int m_nScriptHandleA; // +0x2510
    int m_nScriptHandleB; // +0x2514
    int m_nScriptHandleC; // +0x2518
    int m_nScriptHandleD; // +0x251C
    int m_nScriptHandleE; // +0x2520
    int m_nScriptHandleF; // +0x2524
    BYTE m_bScriptRunning; // +0x2528
    char _gap_2529[839]; // +0x2529
    float m_fScriptTimer; // +0x2870
    char _gap_2874[8]; // +0x2874
    int m_nScriptPhase; // +0x287C
    char _gap_2880[640]; // +0x2880
    float m_fDialogTimer; // +0x2B00
    int m_nDialogState; // +0x2B04
    char _gap_2B08[1976]; // +0x2B08
    float m_fUIColorParam; // +0x32C0
    char _gap_32C4[1528]; // +0x32C4
    int m_nGameFlags; // +0x38BC
    char * m_pDialog; // +0x38C0
    SceneObj * m_pSceneObjRef; // +0x38C4
    int m_nPrevSceneState; // +0x38C8
    int m_nSceneTransition; // +0x38CC
    int m_aItemData; // +0x38D0
    char _gap_38D4[1876]; // +0x38D4
    BYTE m_bGameUpdating; // +0x4028
    char _gap_4029[679]; // +0x4029
    int m_nPostGame; // +0x42D0
    char _gap_42D4[11068]; // +0x42D4
    char * m_pGameObj; // +0x6E10
    int m_nMode; // +0x6E14
    char * m_pGameObjB; // +0x6E18
    char _tail_6E1C[80]; // +0x6E1C
    // total size: 0x6E6C (28268)

    virtual ~CGameData() {}

    virtual int ProcessDialog(); // 0x0044F5B0
    virtual int SceneUpdate(int nVal, int nVal2); // 0x0044F4C0
    virtual void Cleanup(); // 0x0044F430
    char SetDefaultColors(); // 0x00445A60
    int InitRoles(int nVal); // 0x0044ADE0
    int InitItems(int nVal); // 0x0044E660
    void ctor(); // 0x0044F050
    int Load(CUtil *pUtil); // 0x0044F610
    int SetMode(int nVal); // 0x0044F8A0
    int GetMode(); // 0x0044FF60
};
