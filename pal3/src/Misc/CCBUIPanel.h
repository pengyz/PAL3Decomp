#include "UIListBox.h"
#pragma once
// Auto-generated: CCBUIPanel

#include "CCBPanelSlot.h"
#include "UIItem.h"
#include "UIScene.h"
#include "UIStatic.h"

class UIListBox;
class vtbl_0056B22C;

class CCBUIPanel : public UIListBox {
public:
    char _gap_000[1344]; // +0x0
    int m_nPanelOffsetX; // +0x540
    int m_nPanelOffsetY; // +0x544
    char _gap_548[108]; // +0x548
    int _todo_5B4; // +0x5B4
    char _gap_5B8[4]; // +0x5B8
    int m_nPanelX; // +0x5BC
    int m_nPanelY; // +0x5C0
    int m_nChildX; // +0x5C4
    int m_nChildY; // +0x5C8
    int m_nChildW; // +0x5CC
    int m_nChildH; // +0x5D0
    int m_nBorderL; // +0x5D4
    int m_nBorderR; // +0x5D8
    float m_fPanelW; // +0x5DC
    float m_fPanelH; // +0x5E0
    int m_nGridX; // +0x5E4
    int m_nGridY; // +0x5E8
    int m_nGridW; // +0x5EC
    int m_nGridH; // +0x5F0
    int m_nItemW; // +0x5F4
    int m_nItemH; // +0x5F8
    int m_nSpacingX; // +0x5FC
    int m_nSpacingY; // +0x600
    int m_nItemNum; // +0x604
    int m_nMaxItemNum; // +0x608
    char _gap_60C[12]; // +0x60C
    vtbl_0056B22C * m_pVfTable; // +0x618
    char _gap_61C[228]; // +0x61C
    UIScene m_Scene_1792; // +0x700
    char _gap_704[340]; // +0x704
    UIStatic m_Static_2136; // +0x858
    char _gap_85C[148]; // +0x85C
    UIStatic m_Static_2288; // +0x8F0
    char _gap_8F4[148]; // +0x8F4
    UIStatic m_Static_2440; // +0x988
    char _gap_98C[148]; // +0x98C
    UIStatic m_Static_2592; // +0xA20
    char _gap_A24[148]; // +0xA24
    UIStatic m_Static_2744; // +0xAB8
    char _gap_ABC[148]; // +0xABC
    UIScene m_Scene_2896; // +0xB50
    char _gap_B54[340]; // +0xB54
    UIScene m_Scene_3240; // +0xCA8
    char _gap_CAC[340]; // +0xCAC
    UIScene m_Scene_3584; // +0xE00
    char _gap_E04[340]; // +0xE04
    UIItem m_Item_3928; // +0xF58
    char _gap_F5C[384]; // +0xF5C
    BYTE m_bActive; // +0x10DC
    char _gap_10DD[7]; // +0x10DD
    CCBPanelSlot m_Slots[30]; // +0x10E4
    char _gap_115C[16116]; // +0x115C
    int _todo_5050; // +0x5050
    int _todo_5054; // +0x5054
    char _gap_5058[96]; // +0x5058
    void * _todo_50B8; // +0x50B8
    char _gap_50BC[888]; // +0x50BC
    char m_Data[512]; // +0x5434
    // total size: 0x5634 (22068)

    virtual ~CCBUIPanel() {}

    virtual BOOL ProcessInput(double st7_0); // 0x0044A1B0
    virtual void Destroy(UIListBox **thisa, int a3); // 0x00449990
    virtual int OnMessage_a540(int nVal, int nVal2, int nVal3); // 0x0044A540
    virtual char RenderIfUnlocked(); // 0x00454550
    virtual BOOL ProcessInputIfUnlocked(int nVal, int nVal2); // 0x00454560
    virtual int OnMessage(int nVal, int nVal2, int nVal3); // 0x00454590
    int * ctor_60D0(); // 0x004460D0
    void ctor_6200(); // 0x00446200
    void InitPanel(); // 0x004462C0
    void SetUserData(); // 0x00449980
    int CenterSlot(unsigned int nSlotIdx); // 0x00449AB0
    char FocusCurrentRole(); // 0x00449B90
    int UpdateSlotClipping(); // 0x00449C50
    char UpdateSlotPositions(int nVal); // 0x00449CF0
    void EnsureSize(int nVal, int nVal2); // 0x00449E60
    int SetAllSlotsVisible(unsigned __int8 bVisible); // 0x0044A180
    void ActivateSlot(unsigned int nSlotIdx); // 0x0044A4F0
    int ctor_3D10(); // 0x00453D10
    void ctor(); // 0x00453E70
    int UpdateButtonVisibility(); // 0x004544F0
    int InitSlots(); // 0x0048A170
    int InitScrollState(); // 0x004A3EC0
};
