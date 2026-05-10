#pragma once
// Auto-generated: UIScene

class UIScene {
public:
    int Render(int a2); // 0x004200A0
    int RenderWithStack(void *pStack); // 0x00420110
    int NotifyRender(); // 0x00421A10
    int EffectRender(); // 0x00421C00
    int OverlayRender(int a2); // 0x004220A0
    static int CombatCheck(); // 0x004234D0
    static BOOL ProcessInput(char *String1, char *a2); // 0x004235B0
    void LoadResource(char *path); // 0x0043A4C0
    void _UIScene(); // 0x0043A770
    void Destroy2(); // 0x0043A810
    int OnMessage2(); // 0x0043AB00
    BOOL Update2(int a2, int a3); // 0x0043AB20
    int Create2(); // 0x0043AD40
};
