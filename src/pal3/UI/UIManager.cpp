#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIManager.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"

// Forward declarations for unnamed functions
int sub_418260(...);

// Unnamed globals (extern)
extern char aGfxscriptShado[];
extern char aGfxscriptShado_0[];
extern char aShadowTga[];
extern char aViewm[];

// 0x0041F370
void UIManager::Render()
{
  gbTexture *v2; // eax
  int v3; // eax
  int v4; // edi
  _DWORD *v5; // esi
  _DWORD *v6; // ebp
  float *p_y; // ebp
  _DWORD *v8; // esi
  struct gbMatrix4 *Top; // esi
  const struct gbMatrix4 *v10; // edi
  gbRenderEffect *v11; // ecx
  float *v12; // [esp+1Ch] [ebp-12Ch]
  int v13; // [esp+2Ch] [ebp-11Ch]
  int v14; // [esp+2Ch] [ebp-11Ch]
  _DWORD v15[4]; // [esp+34h] [ebp-114h] BYREF
  gbMatrix4 v16; // [esp+44h] [ebp-104h] BYREF
  struct gbTextureArray v17; // [esp+C4h] [ebp-84h] BYREF
  _BYTE v18[64]; // [esp+108h] [ebp-40h] BYREF

  v2 = (gbTexture *)*((_DWORD *)this + 1);
  v17.nTex = 1;
  v17.pTexPt[0] = v2;
  v3 = UISceneUpdate();
  v4 = 0;
  v13 = 0;
  if ( *(int *)(v3 + 57568) > 0 )
  {
    v5 = (_DWORD *)((char *)this + 64);
    v6 = (_DWORD *)(v3 + 57716);
    v14 = *(_DWORD *)(v3 + 57568);
    do
    {
      if ( v6[122] )
      {
        if ( *v6 )
        {
          v5[1] = 0;
          *v5 = 0;
          v5[3] = 1065353216;
          v5[2] = 1065353216;
          if ( sub_418260((int)(v6 - 36), (int)(v5 - 12), v12) )
          {
            ++v4;
            v5 += 17;
          }
        }
      }
      v6 += 2176;
      --v14;
    }
    while ( v14 );
    v13 = v4;
  }
  if ( g_nGameState != 9 )
  {
    p_y = (float *)&g_SceneMgr.m_npc[0].m_path.normal[95].y;
    v8 = (_DWORD *)((char *)this + 68 * v4 + 64);
    do
    {
      if ( *((_DWORD *)p_y + 122) )
      {
        if ( *(_DWORD *)p_y )
        {
          v8[1] = 0;
          *v8 = 0;
          v8[3] = 1065353216;
          v8[2] = 1065353216;
          if ( sub_418260((int)(p_y - 36), (int)(v8 - 12), v12) )
          {
            ++v4;
            v8 += 17;
          }
        }
      }
      p_y += 2176;
    }
    while ( (int)p_y < (int)&g_SceneMgr.m_npc[5].m_path.normal[70].y );
    v13 = v4;
  }
  if ( v4 > 0 )
  {
    gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)&g_pGfxManager[196], 0x15u);
    if ( *(_DWORD *)&g_pGfxManager[1432] == 1 )
    {
      Top = (struct gbMatrix4 *)gbMatrixStack::GetTop(*(gbMatrixStack **)&g_pGfxManager[216]);
      v10 = (const struct gbMatrix4 *)gbMatrixStack::GetTop(*(gbMatrixStack **)&g_pGfxManager[212]);
      gbMatrix4::gbMatrix4((gbMatrix4 *)v16.m);
      gbMatrix4::gbMatrix4(&v16);
      gbMatrix4::LoadIdentity((gbMatrix4 *)v16.m);
      v16.m[2][2] = -1.0;
      gbMatrix4::operator=(&v16, Top);
      gbMatrix4::RightMultiply(&v16, (gbMatrix4 *)v16.m);
      gbMatrix4::RightMultiply(&v16, v10);
      gbRenderEffect::SetVariant(*((gbRenderEffect **)this + 3), PARAM_HANDLE_ALLTM, &v16);
      v15[0] = *(_DWORD *)&g_pGfxManager[1456];
      v15[1] = *(_DWORD *)&g_pGfxManager[1460];
      v11 = (gbRenderEffect *)*((_DWORD *)this + 3);
      v15[2] = *(_DWORD *)&g_pGfxManager[1464];
      v15[3] = 1065353216;
      v11->SetVariant(PARAM_HANDLE_FOGPLANE, v15);
      qmemcpy(v18, Top, sizeof(v18));
      gbMatrix4::RightMultiply((gbMatrix4 *)v18, (gbMatrix4 *)v16.m);
      gbRenderEffect::SetVariant(*((gbRenderEffect **)this + 3), aViewm, v18);
      gbDynVertBuf::RenderGeomQuad(
        (struct gbGeomQuad *)((char *)this + 16),
        v13,
        *((struct gbRenderEffect **)this + 3),
        &v17);
    }
    else
    {
      gbDynVertBuf::RenderGeomQuad(
        (struct gbGeomQuad *)((char *)this + 16),
        v4,
        *((struct gbRenderEffect **)this + 2),
        &v17);
    }
  }
}

// 0x0041F5E0
void * UIManager::LoadShadowTexture()
{
  gbTexture *v2; // eax
  struct gbVFileSystem *v4; // [esp+18h] [ebp-10h] BYREF
  int v5; // [esp+24h] [ebp-4h]

  OpenBaseFile::OpenBaseFile(&v4);
  v5 = 0;
  v2 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aShadowTga);
  *((_DWORD *)this + 1) = v2;
  v2->LoadTexture(1);
  *((_DWORD *)this + 2) = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)&g_pGfxManager[200], aGfxscriptShado, 0);
  *((_DWORD *)this + 3) = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)&g_pGfxManager[200], aGfxscriptShado_0, 0);
  v5 = -1;
  return OpenNULLFile::OpenNULLFile(&v4);
}
