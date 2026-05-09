// PAL3.exe gamebase/GfxHelper.cpp — gbGfxManager 辅助函数
// 这些函数操作 g_pGfxManager 的 MatrixStack 子系统
// Addresses: 0x00540F60, 0x00540FA0

// gbGfxManager 布局 (from PDB, size=1520):
//   +0x00 vtable
//   +0x04 _pad
//   +0x08 hGfxWnd
//   +0x0C gbGfxDriverInfo DrvInfo (184B)
//   +0xC4 gbVertPoolMgr*
//   +0xC8 gbEffectMgr*
//   +0xCC gbResManager*
//   +0xD0 gbPrintFontMgr*
//   +0xD4 gbMatrixStack* pMatrixStack[4]  <-- 关键!
//     [0] = +0xD4 (offset 212 in IDA dword units)
//     [1] = +0xD8 (offset 216)
//     [2] = +0xDC (offset 220)
//     [3] = +0xE0 (offset 224)

struct gbMatrixStack {
    void Push(void);
    void Pop(void);
    void LoadIdentity(void);
};

struct gbGfxManager_Partial {
    char _pad[0xD4];
    gbMatrixStack *pMatrixStack[4]; // +0xD4
};

extern "C" gbGfxManager_Partial *g_pGfxManager;

// 0x00540FA0 - PopMatrixStacks (34B)
// Pop pMatrixStack[0] and pMatrixStack[1]
extern "C" void __cdecl PopMatrixStacks(void)
{
    gbMatrixStack *pStack1 = g_pGfxManager->pMatrixStack[1];
    g_pGfxManager->pMatrixStack[0]->Pop();
    pStack1->Pop();
}

// 0x00540F60 - PushMatrixStacks (58B)
// Push+LoadIdentity on pMatrixStack[0] and pMatrixStack[1]
extern "C" void __cdecl PushMatrixStacks(void)
{
    gbMatrixStack *pWorld = g_pGfxManager->pMatrixStack[1];
    gbMatrixStack *pView = g_pGfxManager->pMatrixStack[0];
    pWorld->Push();
    pView->Push();
    pWorld->LoadIdentity();
    pView->LoadIdentity();
}
