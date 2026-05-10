#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageShadow.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/Logger.h"

// Forward declarations for unnamed functions
int sub_511E80(...);

// Unnamed globals (extern)
extern char aCNewFailed_0[];
extern char aDProjectPal3Co_9[];
extern char aGfxscriptShado[];
extern char aShadowTga_0[];
extern int dword_17ACA7C;

// 0x00511EE0
CCBStageShadow::CCBStageShadow()
{
  gbTexture *v2; // eax
  gbTextureArray *v3; // eax
  gbTexture *m_pTexture; // ecx
  char pExceptionObject[1024]; // [esp+10h] [ebp-800h] BYREF
  char ArgList[1024]; // [esp+410h] [ebp-400h] BYREF

  v2 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                      g_Input.KeyInfo[177].Data,
                      aShadowTga_0);
  this->m_pTexture = v2;
  v2->LoadTexture(1);
  this->m_pEffect = ((gbEffectMgr *)*(gbEffectMgr **)(g_Input.KeyInfo[177].Data + 200))->NewRenderEffect(aGfxscriptShado, 0);
  v3 = (gbTextureArray *)((operator *)0x44u)->new();
  if ( v3 )
  {
    m_pTexture = (gbTexture *)this->m_pTexture;
    v3->nTex = 1;
    v3->pTexPt[0] = m_pTexture;
  }
  else
  {
    v3 = 0;
  }
  this->m_pTextureArray = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed_0, aDProjectPal3Co_9, 85),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x00511F90
CCBStageShadow::~CCBStageShadow(int _this)
{
  ((gbRefObject *)*(gbRefObject **)(this + 4))->Release();
  ((gbRefObject *)*(gbRefObject **)(this + 8))->Release();
  if ( *(_DWORD *)(this + 12) )
  {
    operator delete(*(void **)(this + 12));
    *(_DWORD *)(this + 12) = 0;
  }
  return 1;
}

// 0x00511FC0
char CCBStageShadow::Reset()
{
  int v2; // ebx
  int v3; // ecx
  gbGeomQuad *v4; // edi
  float *WorldPos; // esi
  double v6; // st7
  _BYTE v8[64]; // [esp+14h] [ebp-4Ch] BYREF
  float v9; // [esp+54h] [ebp-Ch]
  int v10; // [esp+58h] [ebp-8h]
  float v11; // [esp+5Ch] [ebp-4h]

  sub_511E80(this);
  ((gbMatrix4 *)v8)->gbMatrix4();
  v2 = 0;
  v3 = -1488 - (_DWORD)this;
  v4 = (gbGeomQuad *)&this->m_ShadowQuad[6];
  do
  {
    if ( this->m_pStage->m_pCBSystem->m_pRoleState->m_Role[v2].bValid )
    {
      WorldPos = ((CCBStageRole *)*(CCBStageRole **)((char *)&v4->vec[0].x + v3 + (unsigned int)this->m_pStage))->GetWorldPos();
      v8->operator=(WorldPos);
      v9 = WorldPos[16];
      v10 = *((_DWORD *)WorldPos + 17);
      v11 = WorldPos[18];
      if ( v9 >= (double)v11 )
        v6 = v11;
      else
        v6 = v9;
      v4->vec[0].x = v6;
      v3 = -1488 - (_DWORD)this;
    }
    else
    {
      v4->vec[0].x = 0.5;
    }
    ++v2;
    v4 = (gbGeomQuad *)((char *)v4 + 4);
  }
  while ( v2 < 11 );
  this->Destroy();
  return 1;
}

// 0x00512080
void CCBStageShadow::Create()
{
  CCBRoleState *m_pRoleState; // esi
  int v3; // ebx
  float *p_sv; // edi
  float *p_z; // esi
  int v6; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st6
  double v11; // st5
  double v12; // st6
  double v13; // st5
  double v14; // st7
  double v15; // st6
  int roleIdx; // [esp+10h] [ebp-54h]
  unsigned __int8 *p_bValid; // [esp+14h] [ebp-50h]
  int v18; // [esp+18h] [ebp-4Ch]
  CCBRoleState *v19; // [esp+1Ch] [ebp-48h]
  int v20; // [esp+20h] [ebp-44h]
  float v21; // [esp+2Ch] [ebp-38h]
  float v22; // [esp+30h] [ebp-34h]
  float v23; // [esp+38h] [ebp-2Ch]
  float v24; // [esp+3Ch] [ebp-28h]
  float v25; // [esp+44h] [ebp-20h]
  float v26; // [esp+48h] [ebp-1Ch]
  float v27; // [esp+50h] [ebp-14h]
  float v28; // [esp+54h] [ebp-10h]
  float v29; // [esp+5Ch] [ebp-8h]
  float v30; // [esp+60h] [ebp-4h]

  m_pRoleState = (CCBRoleState *)this->m_pStage->m_pCBSystem->m_pRoleState;
  v19 = m_pRoleState;
  ((gbVertPoolMgr *)*(gbVertPoolMgr **)(g_Input.KeyInfo[177].Data + 196))->GetDynVertBuf(0x15u);
  v18 = 0;
  p_bValid = (unsigned __int8 *)&m_pRoleState->m_Role[0].bValid;
  roleIdx = 0;
  v3 = 24;
  p_sv = (float *)&this->m_ShadowInitQuad[8].sv;
  p_z = (float *)&this->m_ShadowInitQuad[0].vec[0].z;
  do
  {
    v6 = *(int *)((char *)&this->m_pStage->m_pCBSystem + v3);
    v20 = v6;
    if ( !*p_bValid )
      goto LABEL_8;
    if ( *(_BYTE *)(v6 + 272) )
      goto LABEL_7;
    if ( v3 < 44 && v19->SetRoleField(roleIdx, 0) > 0 )
    {
      v6 = v20;
LABEL_7:
      v7 = *(float *)(v6 + 6584);
      v8 = v7 + *(p_z - 2);
      v21 = *(float *)(v6 + 6588);
      v22 = *(float *)(v6 + 6592);
      v23 = v21 + *(p_z - 1);
      v9 = v22 + *p_z;
      *(p_sv - 1) = v23;
      v24 = v9;
      *(p_sv - 2) = v8;
      *p_sv = v24;
      v10 = v7 + p_z[1];
      v25 = v21 + p_z[2];
      v11 = v22 + p_z[3];
      p_sv[2] = v25;
      v26 = v11;
      p_sv[1] = v10;
      p_sv[3] = v26;
      v12 = v7 + p_z[4];
      v27 = v21 + p_z[5];
      v13 = v22 + p_z[6];
      p_sv[5] = v27;
      v28 = v13;
      p_sv[4] = v12;
      p_sv[6] = v28;
      v14 = v7 + p_z[7];
      v29 = v21 + p_z[8];
      v15 = v22 + p_z[9];
      p_sv[8] = v29;
      v30 = v15;
      p_sv[7] = v14;
      p_sv[9] = v30;
      p_sv += 17;
      ++v18;
    }
LABEL_8:
    v3 += 4;
    p_z += 17;
    ++roleIdx;
    p_bValid += 892;
  }
  while ( v3 < 68 );
  if ( v18 > 0 )
    ((struct gbGeomQuad *)&this->m_ShadowInitQuad[8].vec[3].z)->RenderGeomQuad(v18, this->m_pEffect, this->m_pTextureArray);
}

// 0x00512240
float * CCBStageShadow::Destroy()
{
  gbGeomQuad *v1; // edx
  float *result; // eax
  int v3; // esi
  double x; // st7
  float v5; // [esp+8h] [ebp-1Ch]

  v1 = (gbGeomQuad *)&this->m_ShadowQuad[6];
  result = (float *)&this->m_ShadowInitQuad[0].vec[0].z;
  v3 = 11;
  do
  {
    x = v1->vec[0].x;
    v5 = -x;
    *(result - 2) = v5;
    *(result - 1) = 0.5;
    v1 = (gbGeomQuad *)((char *)v1 + 4);
    *result = x;
    result[2] = 0.5;
    result[1] = x;
    result[3] = x;
    result[5] = 0.5;
    result += 17;
    --v3;
    *(result - 13) = x;
    *(result - 11) = v5;
    *(result - 10) = v5;
    *(result - 9) = 0.5;
    *(result - 8) = v5;
  }
  while ( v3 );
  return result;
}

// 0x005122E0
// attributes: thunk
int CCBStageShadow::Update()
{
  return CCBStageShadow::Render();
}

// 0x005122F0
int CCBStageShadow::Render()
{
  dword_17ACA7C = 1094713344;
  return 1094713344;
}

// 0x00512300
// attributes: thunk
void CCBStageShadow::FillShadowQuad()
{
  CCBSystem::HandleInput();
}
