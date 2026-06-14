#pragma once
// Auto-generated: UIScenePanel

#include "UIScene.h"
#include "UIStatic.h"
#include "UIWnd.h"

class UIScenePanel : public UIScene {
public:
    char _gap_000[344]; // +0x0
    int m_SlotData; // +0x158
    char _gap_15C[12]; // +0x15C
    UIStatic m_Static_360; // +0x168
    char _gap_16C[148]; // +0x16C
    int m_pSubPanel; // +0x200
    char _gap_204[642]; // +0x204
    BYTE m_bPanelActive; // +0x486
    char _gap_487[1265]; // +0x487
    int m_pPanelSlot0; // +0x978
    char _gap_97C[148]; // +0x97C
    int m_pPanelSlot1; // +0xA10
    char _gap_A14[148]; // +0xA14
    int m_pPanelSlot2; // +0xAA8
    char _gap_AAC[148]; // +0xAAC
    int m_pPanelSlot3; // +0xB40
    char _gap_B44[148]; // +0xB44
    int m_pPanelSlot4; // +0xBD8
    char _gap_BDC[240]; // +0xBDC
    int m_pPanelSlot5; // +0xCCC
    char _gap_CD0[148]; // +0xCD0
    int m_pPanelSlot6; // +0xD64
    char _gap_D68[148]; // +0xD68
    int m_pPanelSlot7; // +0xDFC
    char _gap_E00[240]; // +0xE00
    int m_pPanelSlot8; // +0xEF0
    char _gap_EF4[1260]; // +0xEF4
    void * _todo_13E0; // +0x13E0
    char _gap_13E4[3324]; // +0x13E4
    void * _todo_20E0; // +0x20E0
    char _gap_20E4[2076]; // +0x20E4
    UIStatic m_Static_10496; // +0x2900
    char _gap_2904[148]; // +0x2904
    UIStatic m_Static_10648; // +0x2998
    char _gap_299C[148]; // +0x299C
    UIStatic m_Static_10800; // +0x2A30
    char _gap_2A34[148]; // +0x2A34
    UIStatic m_Static_10952; // +0x2AC8
    char _gap_2ACC[160]; // +0x2ACC
    UIWnd m_Wnd_11116; // +0x2B6C
    char _gap_2B70[188]; // +0x2B70
    UIWnd m_Wnd_11308; // +0x2C2C
    char _gap_2C30[188]; // +0x2C30
    UIScene m_SceneA; // +0x2CEC
    char _gap_2CF0[388]; // +0x2CF0
    UIScene m_SceneB; // +0x2E74
    char _gap_2E78[388]; // +0x2E78
    UIScene m_SceneC; // +0x2FFC
    char _gap_3000[388]; // +0x3000
    UIScene m_SceneD; // +0x3184
    char _gap_3188[388]; // +0x3188
    UIScene m_SceneE; // +0x330C
    char _gap_3310[388]; // +0x3310
    UIScene m_SceneF; // +0x3494
    char _gap_3498[368]; // +0x3498
    BYTE _todo_361C; // +0x3608
    BYTE _todo_361D; // +0x3609
    char _gap_360A[2]; // +0x360A
    int _todo_3620; // +0x360C
    int _todo_3624; // +0x3610
    int _todo_3628; // +0x3614
    int _todo_362C; // +0x3618
    char _gap_361C[12]; // +0x361C
    int m_hSettingsUI; // +0x3628
    char _gap_362C[4]; // +0x362C
    BYTE m_bPanelFlagA; // +0x3630
    BYTE _todo_3645; // +0x3631
    BYTE _todo_3632; // +0x3632
    char _gap_3633[1]; // +0x3633
    int m_nPanelState; // +0x3634
    char _gap_3638[4]; // +0x3638
    int m_nSceneIdx; // +0x363C
    char _gap_3640[4]; // +0x3640
    BYTE m_bFlags0; // +0x3644
    BYTE m_bFlags1; // +0x3645
    char _gap_3646[10]; // +0x3646
    UIStatic m_Static_13904; // +0x3650
    char _gap_3654[172]; // +0x3654
    UIStatic m_Static_14080; // +0x3700
    char _tail_3704[148]; // +0x3704
    // total size: 0x3798 (14232)

    virtual int StopAllSounds(float fFade, int nFlags); // 0x0044DB70
    void Destroy(); // 0x0044C910
    void _UIScenePanel(); // 0x0043B3E0
    int ctor_BA60(); // 0x0044BA60
    void ctor(); // 0x0044BE80
    void CreateSettingsUI(); // 0x0044C120
    char ValidateIndex(int nVal); // 0x0046DF10
    int ActivatePanel(int id); // 0x0052CAF0
    int LayoutSlot(int arg0, int nVal, int nVal2, int nVal3, int nVal4); // 0x0052CD40
};
