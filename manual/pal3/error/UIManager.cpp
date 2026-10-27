#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIManager.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Role/RoleSystem.h"
#include "Scene/Scene.h"
#include "Misc/UIBigMap.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x0041F370
void UIManager::Render()
{
  gbTexture *v2; // eax
  Scene *v3; // eax
  int v4; // edi
  UIManager *v5; // esi
  int *p_m_bInView; // ebp
  int *v7; // ebp
  UIManager *v8; // esi
  gbDynVertBuf *DynVertBuf; // eax
  const gbMatrix4 *Top; // esi
  const gbMatrix4 *v11; // edi
  gbRenderEffect *v12; // ecx
  float *v13; // [esp+0x1C] [ebp-0x12C]
  int v14; // [esp+0x2C] [ebp-0x11C]
  int m_nTodo_e0e0; // [esp+0x2C] [ebp-0x11C]
  gbDynVertBuf *v16; // [esp+0x30] [ebp-0x118]
  _DWORD v17[4]; // [esp+0x34] [ebp-0x114] BYREF
  gbMatrix4 v18; // [esp+0x44] [ebp-0x104] BYREF
  gbMatrix4 v19; // [esp+0x84] [ebp-C4h] BYREF
  struct gbTextureArray v20; // [esp+C4h] [ebp-0x84] BYREF
  gbMatrix4 v21; // [esp+0x108] [ebp-0x40] BYREF

  v2 = (gbTexture *)this[1];
  v20.nTex = 1;
  v20.pTexPt[0] = v2;
  v3 = UISceneUpdate();
  v4 = 0;
  v14 = 0;
  if ( v3->m_nTodo_e0e0 > 0 )
  {
    v5 = this + 16;
    p_m_bInView = (int *)&v3->m_roles[0].m_bInView;
    m_nTodo_e0e0 = v3->m_nTodo_e0e0;
    do
    {
      if ( p_m_bInView[122] )
      {
        if ( *p_m_bInView )
        {
          v5[1] = 0;
          *v5 = 0;
          v5[3] = (UIManager)1065353216;
          v5[2] = (UIManager)1065353216;
          if ( (((UIBigMap *)(p_m_bInView - 36)))->UIBigMap::UpdateTransform((int)&v5[-12], v13) )
          {
            ++v4;
            v5 += 17;
          }
        }
      }
      p_m_bInView += 2176;
      --m_nTodo_e0e0;
    }
    while ( m_nTodo_e0e0 );
    v14 = v4;
  }
  if ( g_nSceneState != 9 )
  {
    v7 = (int *)(&g_RoleSlotBuf.dword_17AA450 + 186);
    v8 = (UIManager *)&this[17 * v4 + 16];
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
          if ( (((UIBigMap *)(v7 - 36)))->UIBigMap::UpdateTransform((int)&v8[-12], v13) )
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
    DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
    v16 = (gbDynVertBuf *)DynVertBuf;
    if ( gfxMgr->FogParam.type == 1 )
    {
      Top = (((gbMatrixStack *)gfxMgr->pMatrixStack[1]))->gbMatrixStack::GetTop();
      v11 = (((gbMatrixStack *)gfxMgr->pMatrixStack[0]))->gbMatrixStack::GetTop();
      (((gbMatrix4 *)&v19))->gbMatrix4::LoadIdentity();
      v19.zz = -1.0f;
      (((gbMatrix4 *)&v18))->gbMatrix4::operator=(*(Top));
      (((gbMatrix4 *)&v18))->gbMatrix4::RightMultiply(&v19);
      (((gbMatrix4 *)&v18))->gbMatrix4::RightMultiply(v11);
      (((gbRenderEffect *)*(gbRenderEffect **)&this[3]))->gbRenderEffect::SetVariant(GBPARAM_WORLDMATRIX, &v18);
      v17[0] = LODWORD(gfxMgr->FogParam.start);
      v17[1] = LODWORD(gfxMgr->FogParam.end);
      v12 = (gbRenderEffect *)this[3];
      v17[2] = LODWORD(gfxMgr->FogParam.density);
      v17[3] = 1065353216;
      (((gbRenderEffect *)v12))->gbRenderEffect::SetVariant(GBPARAM_PROJMATRIX, v17);
      qmemcpy(&v21, Top, sizeof(v21));
      (((gbMatrix4 *)&v21))->gbMatrix4::RightMultiply(&v19);
      (((gbRenderEffect *)*(gbRenderEffect **)&this[3]))->gbRenderEffect::SetVariant("viewm", &v21);
      (((gbDynVertBuf *)v16))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&this[4], v14, *(gbRenderEffect **)&this[3], &v20);
    }
    else
    {
      (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&this[4], v4, *(gbRenderEffect **)&this[2], &v20);
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
  v2 = (gbTexture *)gfxMgr->NewTexture("shadow.tga");
  this[1] = (UIManager)v2;
  (((gbTexture *)v2))->gbTexture::LoadTexture(1);
  this[2] = (UIManager)(((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect("gfxscript\\shadow.gbf", 0);
  this[3] = (UIManager)(((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect("gfxscript\\shadow_F2.gbf", 0);
  v5 = -1;
  ((OpenNULLFile *)&v4)->OpenNULLFile::OpenNULLFile();
  return result;
}
