#pragma once
// Auto-generated: UIWnd

#include "PtrArray.h"

class UIWnd {
public:
    gbColorQuad m_fontcolor; // +0x4
    gbColorQuad m_wndcolor; // +0x8
    unsigned int m_id; // +0xC
    tagRECT m_rect; // +0x10
    UIWnd * m_pfather; // +0x20
    PtrArray m_childs; // +0x24
    int m_bcreateok; // +0x34
    int m_bvisible; // +0x38
    int m_benable; // +0x3C
    int m_bfocus; // +0x40
    // total size: 0x44 (68)

    _DWORD * ctor_9030(); // 0x00439030
    void ctor_9130(); // 0x00439130
    void ctor_A160(); // 0x0043A160
    void ctor_A1F0(); // 0x0043A1F0
    _DWORD * ctor_BB70(); // 0x0043BB70
    void ctor_BBB0(); // 0x0043BBB0
    _DWORD * ctor_BCE0(); // 0x0043BCE0
    ~UIWnd(); // 0x0043BE30
    _DWORD * ctor_D830(); // 0x0043D830
    void ctor_D880(); // 0x0043D880
    int CreateChild(); // 0x0043F560
    _DWORD * ctor_F7F0(); // 0x0043F7F0
    void GetChildCount(LPCSTR lpString, char a3); // 0x0043FA00
    void GetChildAt(LPCSTR lpString, char a3); // 0x0043FAE0
    void FindChild(float a2); // 0x0043FCA0
    void SetFrameRate(int a2); // 0x0043FDB0
    void GetWidth(int a2); // 0x0043FDC0
    void GetHeight(int a2); // 0x0043FDD0
    void GetPosition(int a2); // 0x0043FDE0
    void FindChildByName(float a2); // 0x0043FDF0
    int AddChild(_DWORD *a2); // 0x0043FEC0
    _DWORD * ctor_10F0(); // 0x004410F0
    void ctor_11D0(); // 0x004411D0
    void CreateFromTemplate(LPCSTR lpString1, char a3); // 0x004426B0
    int SetShow(int a2); // 0x004427A0
    void SetEnable(const char *a2, int a3); // 0x004427C0
    void ctor_2E10(); // 0x00442E10
    void ctor_2E80(); // 0x00442E80
    int Reset(); // 0x00445920
    int SetState(int state); // 0x00445930
    UIWnd(); // 0x00445AA0
    void _UIWnd(); // 0x00445B40
    int Create(int id, void *pRect, int parent); // 0x00445B90
    void UpdateChildren(); // 0x00445C10
    BOOL HitTest(int a2, int a3); // 0x00445C60
    int GetID(); // 0x00445CD0
    static int SendMessage(int a1, int a2, int a3); // 0x00445D10
    int ScreenToClient(int a2, int a3); // 0x00445D20
    int ClientToScreen(int a2, int a3); // 0x00445D40
    int SetVisible(int bVisible); // 0x00445DB0
    int Destroy(int a2); // 0x00445E70
    void * DestroyChildren(); // 0x00445EA0
    int MoveWindow(); // 0x00445F20
    int GetRect(_DWORD *a2); // 0x00445FA0
    _DWORD * SetRect(_DWORD *a2); // 0x00445FE0
    int GetChild(int id); // 0x00446010
    _DWORD * ctor_60D0(); // 0x004460D0
    void ctor_6200(); // 0x00446200
    int ctor_A540(int a2, int a3, int a4); // 0x0044A540
    int ctor_AB90(); // 0x0044AB90
    void ctor_ACE0(); // 0x0044ACE0
    int ctor_BA60(); // 0x0044BA60
    void ctor_BE80(); // 0x0044BE80
    void ctor_F050(); // 0x0044F050
    int ctor_FFE0(); // 0x0044FFE0
    void ctor_90(); // 0x00450090
    _DWORD * ctor_710(); // 0x00450710
    void ctor_790(); // 0x00450790
    int ctor_1CC0(); // 0x00451CC0
    void ctor_1DA0(); // 0x00451DA0
    void ctor_2600(); // 0x00452600
    int ctor_2790(); // 0x00452790
    void ctor_2850(); // 0x00452850
    int ctor_2FD0(); // 0x00452FD0
    void ctor_3030(); // 0x00453030
    int ctor_3D10(); // 0x00453D10
    void ctor_3E70(); // 0x00453E70
    int ctor_4590(int a2, int a3, int a4); // 0x00454590
    int ctor_4830(); // 0x00454830
    void ctor_4BA0(); // 0x00454BA0
    int ctor_6AB0(); // 0x00456AB0
    void ctor_6B80(); // 0x00456B80
    int ctor_7070(int a2, int a3, int a4); // 0x00457070
    int ctor_90D0(); // 0x004590D0
    void ctor_9260(); // 0x00459260
    int ctor_A7B0(); // 0x0045A7B0
    void ctor_AE60(); // 0x0045AE60
    int ctor_D140(); // 0x0046D140
    void ctor_D4E0(); // 0x0046D4E0
    int ctor_A60(); // 0x00470A60
    void ctor_F40(); // 0x00470F40
    int ctor_7BB0(int a2, int a3, int a4); // 0x00477BB0
    int ctor_9300(); // 0x00479300
    void ctor_9680(); // 0x00479680
    int ctor_BBF0(); // 0x0047BBF0
    void ctor_BD20(); // 0x0047BD20
    int ctor_E5C0(); // 0x0047E5C0
    void ctor_E910(); // 0x0047E910
    int ctor_2ED0(); // 0x00482ED0
    void ctor_3380(); // 0x00483380
    int ctor_67F0(); // 0x004867F0
    void ctor_70C0(); // 0x004870C0
    int ctor_9F0(); // 0x004909F0
    void ctor_12D0(); // 0x004912D0
    int ctor_8820(); // 0x00498820
    void ctor_9030_0(); // 0x00499030
    void ctor_2450(); // 0x004A2450
    int ctor_6F10(); // 0x004A6F10
    int ctor_1D0(); // 0x004B01D0
    void ctor_540(); // 0x004B0540
    _DWORD * ctor_60A0(int a2); // 0x005160A0
    _DWORD * ctor_9310(); // 0x00519310
    int ctor_3F30(); // 0x00523F30
    void ctor_4130(); // 0x00524130
    int ctor_5120(); // 0x00525120
    void ctor_5540(); // 0x00525540
    _DWORD * ctor_57B0(int a2); // 0x005257B0
    int ctor_6A40(int a2, _BYTE *a3, int a4); // 0x00526A40
    int ctor_7950(); // 0x00527950
    void ctor_79F0(); // 0x005279F0
    int ctor_82E0(); // 0x005282E0
    void ctor_84E0(); // 0x005284E0
    int ctor_95F0(); // 0x005295F0
    void ctor_9790(); // 0x00529790
    int ctor_BA10(); // 0x0052BA10
    void ctor_BD50(); // 0x0052BD50
    int ctor_1D20(); // 0x00531D20
    void ctor_1E70(); // 0x00531E70
};
