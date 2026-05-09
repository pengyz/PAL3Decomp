#pragma once
// Auto-generated from IDA decomp - CCBLineupWindow
// 15 methods

class CCBLineupWindow {
public:
    static char CCBLineupWindow(_DWORD *a1);  // 0x0051CFB0
    static char ~CCBLineupWindow(_DWORD *a1);  // 0x0051D070
    static char Reset(_DWORD *a1);  // 0x0051D120
    static char Create(_DWORD *a1);  // 0x0051D1D0
    static char Destroy(_DWORD *a1);  // 0x0051D290
    static char OnMessage(_DWORD *a1);  // 0x0051D340
    static char Update(_DWORD *a1);  // 0x0051D3F0
    static char Render(_DWORD *a1);  // 0x0051D4A0
    static int() IsPtOnFace();  // 0x0051D580
    static int() IsPtOnFace();  // 0x0051D590
    static void() IsPtOnInitPos();  // 0x0051D5A0
    static void() IsPtOnInitPos();  // 0x0051D5B0
    static char() IsFaceOnInitPos();  // 0x0051D5F0
    static char SetFaceLineup(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, _DWORD *a9);  // 0x0051D610
    static int() RefreshFacePos();  // 0x0051D6D0
};
