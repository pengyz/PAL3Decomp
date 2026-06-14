#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIManager.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations

// Unnamed globals (extern)
extern int dword_C109F0;
extern RoleSystem stru_C059A0;

// 0x0041F370
void UIManager::Render()
{
  gbTexture *v2; // eax
  int v3; // eax
  int v4; // edi
  UIManager *v5; // esi
  _DWORD *v6; // ebp
  int *v7; // ebp
  UIManager *v8; // esi
  gbDynVertBuf *DynVertBuf; // eax
  gbMatrix4 *Top; // esi
  const gbMatrix4 *v11; // edi
  int v12; // ecx
  float *v13; // [esp+0x1C] [ebp-0x12C]
  int v14; // [esp+0x2C] [ebp-0x11C]
  int v15; // [esp+0x2C] [ebp-0x11C]
  gbDynVertBuf *v16; // [esp+0x30] [ebp-0x118]
  _DWORD v17[4]; // [esp+0x34] [ebp-0x114] BYREF
  gbMatrix4 v18; // [esp+0x44] [ebp-0x104] BYREF
  gbMatrix4 v19; // [esp+0x84] [ebp-C4h] BYREF
  struct gbTextureArray v20; // [esp+C4h] [ebp-0x84] BYREF
  gbMatrix4 v21; // [esp+0x108] [ebp-0x40] BYREF

  v2 = (gbTexture *)*((_DWORD *)this + 1);
  v20.nTex = 1;
  v20.pTexPt[0] = v2;
  v3 = UISceneUpdate();
  v4 = 0;
  v14 = 0;
  if ( *(int *)(v3 + 57568) > 0 )
  {
    v5 = this + 16;
    v6 = (_DWORD *)(v3 + 57716);
    v15 = *(_DWORD *)(v3 + 57568);
    do
    {
      if ( v6[122] )
      {
        if ( *v6 )
        {
          v5[1] = 0;
          *v5 = 0;
          v5[3] = (UIManager)1065353216;
          v5[2] = (UIManager)1065353216;
          if ( ((UIBigMap *)(v6 - 36))->Update((int)&v5[-12], v13) )
          {
            ++v4;
            v5 += 17;
          }
        }
      }
      v6 += 2176;
      --v15;
    }
    while ( v15 );
    v14 = v4;
  }
  if ( g_nSceneState != 9 )
  {
    v7 = &((RoleSystem *)&stru_C059A0)->m_teamSlots[29];
    v8 = this + 17 * v4 + 16;
    do
    {
      if ( v7[122] )
      {
        if ( *v7 )
        {
          v8[1] = 0;
          *v8 = 0;
          v8[3] = (UIManager)1065353216;
          v8[2] = (UIManager)1065353216;
          if ( ((UIBigMap *)(v7 - 36))->Update((int)&v8[-12], v13) )
          {
            ++v4;
            v8 += 17;
          }
        }
      }
      v7 += 2176;
    }
    while ( (int)v7 < (int)dword_C109F0 );
    v14 = v4;
  }
  if ( v4 > 0 )
  {
    DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
    v16 = DynVertBuf;
    if ( gfxMgr->FogParam.type == 1 )
    {
      Top = ((gbMatrixStack *)gfxMgr->pMatrixStack[1])->GetTop();
      v11 = ((gbMatrixStack *)gfxMgr->pMatrixStack[0])->GetTop();
      ((gbMatrix4 *)&v19)->LoadIdentity();
      v19.zz = -1.0;
      ((gbMatrix4 *)&v18)->operator=(Top);
      ((gbMatrix4 *)&v18)->RightMultiply(&v19);
      ((gbMatrix4 *)&v18)->RightMultiply(v11);
      ((gbRenderEffect *)*((_DWORD *)this + 3))->SetVariant(0, &v18);
      v17[0] = LODWORD(gfxMgr->FogParam.start);
      v17[1] = LODWORD(gfxMgr->FogParam.end);
      v12 = *((_DWORD *)this + 3);
      v17[2] = LODWORD(gfxMgr->FogParam.density);
      v17[3] = 1065353216;
      ((gbRenderEffect *)v12)->SetVariant(2, v17);
      qmemcpy(&v21, Top, sizeof(v21));
      ((gbMatrix4 *)&v21)->RightMultiply(&v19);
      ((gbRenderEffect *)*((gbRenderEffect **)this + 3))->SetVariant("viewm", &v21);
      ((gbDynVertBuf *)v16)->RenderGeomQuad((gbGeomQuad *)(this + 4), v14, *((gbRenderEffect **)this + 3), &v20);
    }
    else
    {
      ((gbDynVertBuf *)DynVertBuf)->RenderGeomQuad((gbGeomQuad *)(this + 4), v4, *((gbRenderEffect **)this + 2), &v20);
    }
  }
}

// 0x0041F5E0
void * UIManager::LoadShadowTexture()
{
  gbTexture *v2; // eax
  void *result; // eax
  OpenBaseFile v4; // [esp+0x18] [ebp-0x10] BYREF
  int v5; // [esp+0x24] [ebp-0x4]

  v5 = 0;
  v2 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, "shadow.tga");
  *((_DWORD *)this + 1) = v2;
  ((gbTexture *)v2)->LoadTexture(1);
  *((_DWORD *)this + 2) = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\shadow.gbf", 0);
  *((_DWORD *)this + 3) = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\shadow_F2.gbf", 0);
  v5 = -1;
  return result;
}
