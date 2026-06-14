#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStageShadow.h"

// Unnamed globals (extern)
extern int dword_17ACA7C;

// 0x00511E80
float * CCBStageShadow::UpdateShadowMesh()
{
  float *p_sv; // eax
  int v2; // edi

  p_sv = &this->m_ShadowInitQuad[0].sv;
  v2 = 11;
  do
  {
    *(p_sv - 1) = 0.0;
    *p_sv = 0.0;
    p_sv[1] = 1.0;
    p_sv[2] = 1.0;
    p_sv[186] = 0.0;
    p_sv[187] = 0.0;
    p_sv[188] = 1.0;
    p_sv[189] = 1.0;
    *((_BYTE *)p_sv + 762) = -1;
    *((_BYTE *)p_sv + 761) = -1;
    *((_BYTE *)p_sv + 760) = -1;
    p_sv += 17;
    --v2;
  }
  while ( v2 );
  return this->Destroy();
}

// 0x00511EE0
CCBStageShadow::CCBStageShadow()
{
  gbTexture *v2; // eax
  gbTextureArray *v3; // eax
  gbTexture *m_pTexture; // ecx
  char pExceptionObject[1024]; // [esp+0x10] [ebp-0x800] BYREF
  char ArgList; // [esp+0x410] [ebp-0x400] BYREF

  v2 = (gbTexture *)(*(int (**)(gbGfxManager *, void *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, &g_EffMgr);
  this->m_pTexture = v2;
  ((gbTexture *)v2)->LoadTexture(1);
  this->m_pEffect = ((gbEffectMgr *)gfxMgr->pEffectMgr)->NewRenderEffect("gfxscript\\shadow.gbf", 0);
  v3 = (gbTextureArray *)operator new(0x44u);
  if ( v3 )
  {
    m_pTexture = this->m_pTexture;
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
      ((Logger *)&ArgList)->FormatException("C++ new failed!", aDProjectPal3Co_7, 85),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
}

// 0x00511F90
void CCBStageShadow::_CCBStageShadow()
{
  ((gbRefObject *)this->m_pTexture)->Release();
// [VFTABLE] ((gbRefObject *)&this->m_pEffect->__vftable)->Release();
  if ( this->m_pTextureArray )
  {
    operator delete(this->m_pTextureArray);
    this->m_pTextureArray = 0;
  }
}

// 0x00511FC0
void CCBStageShadow::Reset()
{
  int v2; // ebx
  int v3; // ecx
  float *m_fShadowRadius; // edi
  float *WorldPos; // esi
  double v6; // st7
  gbMatrix4 v7; // [esp+0x14] [ebp-0x4C] BYREF
  float v8; // [esp+0x54] [ebp-0xC]
  int v9; // [esp+0x58] [ebp-0x8]
  float v10; // [esp+0x5C] [ebp-0x4]

  v2 = 0;
  v3 = -1488 - (_DWORD)this;
  m_fShadowRadius = this->m_fShadowRadius;
  do
  {
    if ( this->m_pStage->m_pCBSystem->m_pRoleState->m_Role[0].bMagicMastered[5][v2 + 4] )
    {
      WorldPos = ((CCBStageRole *)*(CCBStageRole **)((char *)m_fShadowRadius + v3
                                                                                      + (unsigned int)this->m_pStage))->GetWorldPos();
      ((gbMatrix4 *)&v7)->operator=(WorldPos);
      v8 = WorldPos[16];
      v9 = *((_DWORD *)WorldPos + 17);
      v10 = WorldPos[18];
      if ( v8 >= (double)v10 )
        v6 = v10;
      else
        v6 = v8;
      *m_fShadowRadius = v6;
      v3 = -1488 - (_DWORD)this;
    }
    else
    {
      *m_fShadowRadius = 0.5;
    }
    v2 += 892;
    ++m_fShadowRadius;
  }
  while ( v2 < 9812 );

}

// 0x00512080
void CCBStageShadow::Create()
{
  CCBRoleState *m_pRoleState; // esi
  int v3; // ebx
  float *p_z; // edi
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
  int roleIdx; // [esp+0x10] [ebp-0x54]
  _BYTE *v17; // [esp+0x14] [ebp-0x50]
  int v18; // [esp+0x18] [ebp-0x4C]
  CCBRoleState *v19; // [esp+0x1C] [ebp-0x48]
  int v20; // [esp+0x20] [ebp-0x44]
  float v21; // [esp+0x2C] [ebp-0x38]
  float v22; // [esp+0x30] [ebp-0x34]
  float v23; // [esp+0x38] [ebp-0x2C]
  float v24; // [esp+0x3C] [ebp-0x28]
  float v25; // [esp+0x44] [ebp-0x20]
  float v26; // [esp+0x48] [ebp-0x1C]
  float v27; // [esp+0x50] [ebp-0x14]
  float v28; // [esp+0x54] [ebp-0x10]
  float v29; // [esp+0x5C] [ebp-0x8]
  float v30; // [esp+0x60] [ebp-0x4]

  m_pRoleState = this->m_pStage->m_pCBSystem->m_pRoleState;
  v19 = m_pRoleState;
  ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x15u);
  v18 = 0;
  v17 = &m_pRoleState->m_Role[0].bMagicMastered[5][4];
  roleIdx = 0;
  v3 = 24;
  p_z = &this->m_ShadowQuad[0].vec[0].z;
  v5 = &this->m_ShadowInitQuad[0].vec[0].z;
  do
  {
    v6 = *(int *)((char *)&this->m_pStage->m_pCBSystem + v3);
    v20 = v6;
    if ( !*v17 )
      goto LABEL_8;
    if ( *(_BYTE *)(v6 + 272) )
      goto LABEL_7;
    if ( v3 < 44 && ((CCBRoleState *)v19)->SetRoleField(roleIdx, 0) > 0 )
    {
      v6 = v20;
LABEL_7:
      v7 = *(float *)(v6 + 6584);
      v8 = v7 + *(v5 - 2);
      v21 = *(float *)(v6 + 6588);
      v22 = *(float *)(v6 + 6592);
      v23 = v21 + *(v5 - 1);
      v9 = v22 + *v5;
      *(p_z - 1) = v23;
      v24 = v9;
      *(p_z - 2) = v8;
      *p_z = v24;
      v10 = v7 + v5[1];
      v25 = v21 + v5[2];
      v11 = v22 + v5[3];
      p_z[2] = v25;
      v26 = v11;
      p_z[1] = v10;
      p_z[3] = v26;
      v12 = v7 + v5[4];
      v27 = v21 + v5[5];
      v13 = v22 + v5[6];
      p_z[5] = v27;
      v28 = v13;
      p_z[4] = v12;
      p_z[6] = v28;
      v14 = v7 + v5[7];
      v29 = v21 + v5[8];
      v15 = v22 + v5[9];
      p_z[8] = v29;
      v30 = v15;
      p_z[7] = v14;
      p_z[9] = v30;
      p_z += 17;
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
    ((gbDynVertBuf *)this->m_ShadowQuad)->RenderGeomQuad(v18, this->m_pEffect, this->m_pTextureArray);
}

// 0x00512240
float * CCBStageShadow::Destroy()
{
  float *m_fShadowRadius; // edx
  float *result; // eax
  int v3; // esi
  double v4; // st7
  float v5; // [esp+0x8] [ebp-0x1C]

  m_fShadowRadius = this->m_fShadowRadius;
  result = &this->m_ShadowInitQuad[0].vec[0].z;
  v3 = 11;
  do
  {
    v4 = *m_fShadowRadius;
    v5 = -v4;
    *(result - 2) = v5;
    *(result - 1) = 0.5;
    ++m_fShadowRadius;
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
void CCBStageShadow::Update()
{

}

// 0x005122F0
void CCBStageShadow::Render()
{
  dword_17ACA7C = 1094713344;
}

// 0x00512300
// attributes: thunk
void CCBStageShadow::FillShadowQuad()
{
  ((CCBSystem *)this)->HandleInput();
}
