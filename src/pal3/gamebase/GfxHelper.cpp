// PAL3.exe gamebase/GfxHelper.cpp
// Uses gbGfxManager public API

#include "pal3/pal3_globals.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_internal.h"
#include "gbengine/gbRenderEffect.h"

// 0x00540FA0 - PopMatrixStacks (34B)
extern "C" void __cdecl PopMatrixStacks(void)
{
    gbMatrixStack *pWorld = g_pGfxManager->GetMatrixStack(1);
    g_pGfxManager->GetMatrixStack(0)->Pop();
    pWorld->Pop();
}

// 0x00540F60 - PushMatrixStacks (58B)
extern "C" void __cdecl PushMatrixStacks(void)
{
    gbMatrixStack *pWorld = g_pGfxManager->GetMatrixStack(1);
    gbMatrixStack *pView = g_pGfxManager->GetMatrixStack(0);
    pWorld->Push();
    pView->Push();
    pWorld->LoadIdentity();
    pView->LoadIdentity();
}

// 0x004B65F0 - RenderTarget3_Init (55B)
extern "C" int __cdecl RenderTarget3_Init(int *pThis)
{
    gbEffectMgr *pEffMgr = (gbEffectMgr *)g_pGfxManager->GetResManager();
    pThis[0] = (int)pEffMgr->NewRenderEffect(aGfxscriptGlowG, 0);
    pThis[1] = (int)pEffMgr->NewRenderEffect(aGfxscriptGeomG, 1);
    return 1;
}
