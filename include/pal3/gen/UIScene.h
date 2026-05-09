#pragma once
// Auto-generated from IDA decomp - UIScene
// 7 methods

class UIScene {
public:
    int Render(int a2);  // 0x004200A0
    int RenderWithStack(void *pStack);  // 0x00420110
    int NotifyRender();  // 0x00421A10
    int EffectRender();  // 0x00421C00
    int OverlayRender(int a2);  // 0x004220A0
    static int __cdecl() CombatCheck();  // 0x004234D0
    void LoadResource(char *path);  // 0x0043A4C0
};
