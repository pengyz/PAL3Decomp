#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStageShadow.h"

// 0x00511EE0
char sub_511EE0()
{
  gbTexture *v2; // eax
  _DWORD *v3; // eax
  int v4; // ecx
  char pExceptionObject[1024]; // [esp+10h] [ebp-800h] BYREF
  char ArgList; // [esp+410h] [ebp-400h] BYREF

  v2 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      aShadowTga_0);
  *(this + 1) = v2;
  v2->LoadTexture(1);
  *(this + 2) = gbEffectMgr::NewRenderEffect(*(gbEffectMgr **)(g_pGfxManager + 200), aGfxscriptShado, 0);
  v3 = operator new(0x44u);
  if ( v3 )
  {
    v4 = *(this + 1);
    v3[16] = 1;
    *v3 = v4;
  }
  else
  {
    v3 = 0;
  }
  *(this + 3) = v3;
  if ( !v3 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)&ArgList, (int)aCNewFailed_0, (int)aDProjectPal3Co_9, 85),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return 1;
}

// 0x00511F90
char sub_511F90(int this)
{
  gbRefObject::Release(*(gbRefObject **)(this + 4));
  gbRefObject::Release(*(gbRefObject **)(this + 8));
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
  float *v4; // edi
  float *WorldPos; // esi
  double v6; // st7
  _BYTE v8[76]; // [esp+14h] [ebp-4Ch] BYREF

  sub_511E80((char *)this);
  (gbMatrix4 *->gbMatrix4()v8);
  v2 = 0;
  v3 = -1488 - (_DWORD)this;
  v4 = (float *)&this->m_ShadowQuad[6];
  do
  {
    if ( BYTE1(this->m_pStage->m_pCBSystem->m_pRoleState->m_bMustFail[0].sModel[v2 + 4]) )
    {
      WorldPos = CCBStageRole::GetWorldPos(*(CCBStageRole **)((char *)v4 + v3 + (unsigned int)this->m_pStage));
      gbMatrix4::operator=(v8, WorldPos);
      *(float *)&v8[64] = WorldPos[16];
      *(float *)&v8[68] = WorldPos[17];
      *(float *)&v8[72] = WorldPos[18];
      if ( *(float *)&v8[64] >= (double)*(float *)&v8[72] )
        v6 = *(float *)&v8[72];
      else
        v6 = *(float *)&v8[64];
      *v4 = v6;
      v3 = -1488 - (_DWORD)this;
    }
    else
    {
      *v4 = 0.5;
    }
    v2 += 223;
    ++v4;
  }
  while ( v2 < 2453 );
  (float *->Destroy()this);
  return 1;
}

// 0x00512080
void CCBStageShadow::Create()
{
  CCBRoleState *v2; // esi
  int v3; // ebx
  float *v4; // edi
  float *v5; // esi
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
  char *v17; // [esp+14h] [ebp-50h]
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

  v2 = this->m_pStage->m_pCBSystem->m_pRoleState;
  v19 = v2;
  gbVertPoolMgr::GetDynVertBuf(*(gbVertPoolMgr **)&g_pGfxManager[196], 0x15u);
  v18 = 0;
  v17 = (char *)&v2->m_bMustFail[0].sModel[4] + 1;
  roleIdx = 0;
  v3 = 24;
  v4 = (float *)&this->m_ShadowInitQuad[8].sv;
  v5 = (float *)&this->m_ShadowInitQuad[0].vec[0].z;
  do
  {
    v6 = *(int *)((char *)&this->m_pStage->m_pCBSystem + v3);
    v20 = v6;
    if ( !*v17 )
      goto LABEL_8;
    if ( *(_BYTE *)(v6 + 272) )
      goto LABEL_7;
    if ( v3 < 44 && v19->SetRoleField(roleIdx, 0) > 0 )
    {
      v6 = v20;
LABEL_7:
      v7 = *(float *)(v6 + 6584);
      v8 = v7 + *(v5 - 2);
      v21 = *(float *)(v6 + 6588);
      v22 = *(float *)(v6 + 6592);
      v23 = v21 + *(v5 - 1);
      v9 = v22 + *v5;
      *(v4 - 1) = v23;
      v24 = v9;
      *(v4 - 2) = v8;
      *v4 = v24;
      v10 = v7 + v5[1];
      v25 = v21 + v5[2];
      v11 = v22 + v5[3];
      v4[2] = v25;
      v26 = v11;
      v4[1] = v10;
      v4[3] = v26;
      v12 = v7 + v5[4];
      v27 = v21 + v5[5];
      v13 = v22 + v5[6];
      v4[5] = v27;
      v28 = v13;
      v4[4] = v12;
      v4[6] = v28;
      v14 = v7 + v5[7];
      v29 = v21 + v5[8];
      v15 = v22 + v5[9];
      v4[8] = v29;
      v30 = v15;
      v4[7] = v14;
      v4[9] = v30;
      v4 += 17;
      ++v18;
    }
LABEL_8:
    v3 += 4;
    v5 += 17;
    ++roleIdx;
    v17 += 892;
  }
  while ( v3 < 68 );
  if ( v18 > 0 )
    (struct gbGeomQuad *->RenderGeomQuad()&this->m_ShadowInitQuad[8].vec[3].z,
      v18,
      this->m_pEffect,
      this->m_pTextureArray);
}

// 0x00512240
float * sub_512240()
{
  float *v1; // edx
  float *result; // eax
  int v3; // esi
  double v4; // st7
  float v5; // [esp+8h] [ebp-1Ch]

  v1 = this + 378;
  result = this + 6;
  v3 = 11;
  do
  {
    v4 = *v1;
    v5 = -v4;
    *(result - 2) = v5;
    *(result - 1) = 0.5;
    ++v1;
    *result = v4;
    result[2] = 0.5;
    result[1] = v4;
    result[3] = v4;
    result[5] = 0.5;
    result += 17;
    --v3;
    *(result - 13) = v4;
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
int sub_5122F0()
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
