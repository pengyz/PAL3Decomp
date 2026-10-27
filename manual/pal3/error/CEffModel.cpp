#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffModel.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffSParticle.h"
#include "Effect/CEffect.h"
#include "Effect/CEffgbParticle.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffModel.h"
#include "Misc/GeomNode.h"
#include "Misc/tag17A7BData.h"
#include "Misc/tagEffMgrData.h"
#include "Misc/tagEffTaskParam.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
void __cdecl nullsub_86(void);
void __cdecl nullsub_87(void);
void __cdecl nullsub_88(void);

// 0x004CEC80
int CEffModel::CreateInstance(CEffModel *pSrc, int nVal, CEffModel *pParam)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  int v9; // eax
  int v10; // [esp+0x0] [ebp-0x1C]

  v4 = 0;
  for ( i = (_BYTE *)&this->m_bVisible; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pSrc);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = unk_C10D38;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  if ( operator new(0x10B0u) )
    v9 = CEffModel_Reset(v10);
  else
    v9 = 0;
  *((_DWORD *)v7 + 24) = v9;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pSrc);
  return v4;
}

// 0x004CFC70
CEffModel::CEffModel()
{
  CEffModel *result; // eax
this->m_pEM = ((CEffMgr *)0);
  this->m_bIdle = 0;
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 1) = 0;
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 2) = 0;
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3) = 0;
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 4) = -1;
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 5) = -1;
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 6) = 0;
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 7) = 0;
  this->CTaskTpl_tagEffTaskParam_CEffModel::m_pGeomNode = 0;
  *((_DWORD *)&this->m_pGeomNode + 1) = 0;
  *((_DWORD *)&this->m_pGeomNode + 2) = 0;
  *((_DWORD *)&this->m_pGeomNode + 3) = 0;
  this->m_vecOffsetPos.x = 0.0f;
  this->m_vecOffsetPos.y = 0.0f;
  this->m_vecOffsetPos.z = 0.0f;
  this->m_vecRot.x = 0.0f;
  this->m_vecRot.y = 0.0f;
  this->m_vecRot.z = 0.0f;
  this->m_pGeomNode = ((gbGeomNode *)0);
  *((_DWORD *)&this->m_pGeomNode + 3) = 0;
  *((_DWORD *)&this->m_pGeomNode + 2) = 0;
  *((_DWORD *)&this->m_pGeomNode + 1) = 0;
  this->m_vecOffsetPos.z = 0.0f;
  this->m_vecOffsetPos.y = 0.0f;
  this->m_vecOffsetPos.x = 0.0f;
  this->m_vecRot.z = 0.0f;
  this->m_vecRot.y = 0.0f;
  this->m_vecRot.x = 0.0f;
  this->m_bVisible = 0;
  this->m_bAdditiveBlend = 0;
  this->m_bNoZTest = 0;
  this->m_fSizeX = 1.0f;
  this->m_fSizeY = 1.0f;
  this->m_fSizeZ = 1.0f;
  result;
}

// 0x004CFD00
CEffModel * CEffModel::CreateEffModel()
{
  CEffModel *v0; // eax

  v0 = (CEffModel *)operator new(0x68u);
  if ( v0 )
    return v0->CEffModel::CEffModel();
  else
    return 0;
}

// 0x004CFEB0
bool CEffModel::LoadFromNode(int nVal)
{
  void *v3; // eax
  int v4; // ebp
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v11; // ebx
  int v12; // edi

  v3 = (void *)operator new(0x4C0u);
  *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3) = (unsigned long)v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
      *(_DWORD *)(*((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3) + v5) = (unsigned long)operator new(0x2D0u);
      if ( !*(_DWORD *)(*((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3) + v5) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
        *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 7) = 8;
        this->CTaskTpl_tagEffTaskParam_CEffModel::m_pGeomNode = (gbGeomNode *)10;
        v7 = 0;
        do
        {
          *(_BYTE *)(*((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3) + v7 + 148) = 0;
          v8 = 0;
          if ( (int)this->CTaskTpl_tagEffTaskParam_CEffModel::m_pGeomNode > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
              *(_BYTE *)(v9 + *(_DWORD *)(v7 + *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3)) - 8) = 0;
            }
            while ( v8 < (int)this->CTaskTpl_tagEffTaskParam_CEffModel::m_pGeomNode );
          }
          ++v6;
          v7 += 152;
        }
        while ( v6 < *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 7) );
        return (((GeomNode *)this))->GeomNode::LoadFromNode((const gbGeomNode *)(nVal + 40));
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v11 = v4;
      v12 = 152 * (v4 - 1);
      do
      {
        operator delete(*(void **)(*((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3) + v12));
        v12 -= 152;
        --v11;
      }
      while ( v11 );
    }
    operator delete(*((void **)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 3));
  }
  return (((GeomNode *)this))->GeomNode::LoadFromNode((const gbGeomNode *)(nVal + 40));
}

// 0x004D01C0
void CEffModel::RenderScenePass()
{
  gbMatrixStack *v2; // edi
  float v3; // st7
  float v4; // st7
  gbGeomNode *m_pGeomNode; // esi
  float v6; // [esp+0x4] [ebp-0x18]
  float v7; // [esp+0x8] [ebp-0x14]
  float v8; // [esp+0xC] [ebp-0x10]
  struct gbVec3D v9; // [esp+0x10] [ebp-0xC] BYREF

  if ( (g_bgbMatrixStackFlag_17A7B84 & 1) == 0 )
  {
    g_17A7BData.m_nEffParam24 = 1065353216;
    g_bgbMatrixStackFlag_17A7B84 |= 1u;
    g_17A7BData.m_nEffTypeCode = 0;
    g_17A7BData.m_nEffParam2C = 0;
    atexit(nullsub_88);
  }
  if ( (g_bgbMatrixStackFlag_17A7B84 & 2) == 0 )
  {
    g_17A7BData.m_nEffParam14 = 0;
    g_bgbMatrixStackFlag_17A7B84 |= 2u;
    g_17A7BData.m_nEffParam1 = 1065353216;
    g_17A7BData.m_nEffParam1C = 0;
    atexit(nullsub_87);
  }
  if ( (g_bgbMatrixStackFlag_17A7B84 & 4) == 0 )
  {
    g_17A7BData.m_nEffParamBase[1] = 0;
    g_bgbMatrixStackFlag_17A7B84 |= 4u;
    g_17A7BData.m_nEffParamBase[2] = 0;
    g_17A7BData.m_nEffParam0 = 1065353216;
    atexit(nullsub_86);
  }
  if ( !this->m_bIdle && this->m_bVisible )
  {
    v2 = (gbMatrixStack *)*(gbMatrixStack **)(*(_DWORD *)this->m_pEM + 216);
    (((gbMatrixStack *)v2))->gbMatrixStack::Push();
    v6 = this->m_vecOffsetPos.x + *((float *)&this->m_pGeomNode + 1);
    v3 = this->m_vecOffsetPos.y + *((float *)&this->m_pGeomNode + 2);
    v9.x = v6;
    v7 = v3;
    v4 = this->m_vecOffsetPos.z + *((float *)&this->m_pGeomNode + 3);
    v9.y = v7;
    v8 = v4;
    v9.z = v8;
    (((gbMatrixStack *)v2))->gbMatrixStack::Translate(v9);
    (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(this->m_vecRot.x, * (gbVec3D *)&g_17A7BData.m_nEffParam24);
    (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(this->m_vecRot.y, * (gbVec3D *)&g_17A7BData.m_nEffParam14);
    (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(this->m_vecRot.z, * (gbVec3D *)&g_17A7BData.m_nEffParamBase[1]);
    (((gbMatrixStack *)v2))->gbMatrixStack::Scale(this->m_fSizeX,   this->m_fSizeY,   this->m_fSizeZ);
    m_pGeomNode = (gbGeomNode *)this->m_pGeomNode;
    if ( m_pGeomNode )
      (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)((gbChain1DNode *)m_pGeomNode) + 16))(m_pGeomNode, 0);
    (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
  }
}

// 0x004D0390
void CEffModel::GetRenderNode(int a2)
{
  gbGeomNode *m_pGeomNode; // ecx

  m_pGeomNode = (gbGeomNode *)this->m_pGeomNode;
  if ( m_pGeomNode )
    (((gbVisNode *)m_pGeomNode))->gbVisNode::SetTimeScale(*(float *)&a2);
}

// 0x004D03B0
void CEffModel::RenderModel(int a2)
{
  CTaskTpl_tagEffTaskParam_CEffModel *v2; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int m_pGeomNode; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v2 = ((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12));
  v3 = *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 7);
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *((_DWORD *)v2 + 3);
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 148) = 1;
    *(_BYTE *)(*((_DWORD *)v2 + 3) + v7 + 149) = 1;
    v8 = ++g_nEffectUID;
    if ( !g_nEffectUID || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nEffectUID = 1;
    }
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 16) = v8;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 8) = 0;
    *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 20) = 0;
    if ( a2 )
      qmemcpy((void *)(*((_DWORD *)v2 + 3) + v7 + 24), (const void *)a2, 0x7Cu);
    else
      memset((void *)(*((_DWORD *)v2 + 3) + v7 + 24), 0, 0x7Cu);
    ++*((_DWORD *)v2 + 6);
    if ( v4 != -1 )
    {
      m_pGeomNode = (int)v2->m_pGeomNode;
      v10 = 0;
      if ( m_pGeomNode > 0 )
      {
        v11 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= m_pGeomNode )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *(int (CEffect::**)(int))v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nEffectUID;
        if ( !g_nEffectUID || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nEffectUID = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_22:
      v15 = (int)v2->m_pGeomNode;
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*((_DWORD *)v2 + 3) + 152 * v4);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *(int (CEffect::**)(int))v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nEffectUID;
        if ( !g_nEffectUID || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nEffectUID = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 4);
      }
LABEL_31:
      (((GeomNode *)v2))->GeomNode::DestroyChildren(v4);
      *(_DWORD *)(*((_DWORD *)v2 + 3) + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*((_DWORD *)v2 + 3) + v7) + 16) = *((_DWORD *)v2 + 1);
    }
  }
}

// 0x004D0850
int CEffModel::GetModelType(int nVal)
{
  int result; // eax

  switch ( nVal )
  {
    case 0:
      result = (int)&g_EffMgrData._tail_000[676];
      break;
    case 1:
      result = (int)&g_EffMgrData._tail_000[148];
      break;
    case 2:
      result = (int)&g_EffMgrData._tail_000[140];
      break;
    case 3:
      result = (int)&g_EffMgrData._tail_000[132];
      break;
    case 4:
      result = (int)&g_EffMgrData._tail_000[120];
      break;
    case 5:
      result = (int)&g_EffMgrData._tail_000[668];
      break;
    case 6:
      result = (int)&g_EffMgrData._tail_000[660];
      break;
    case 7:
      result = (int)&g_EffMgrData._tail_000[652];
      break;
    case 9:
      result = (int)&g_EffMgrData._tail_000[72];
      break;
    case 10:
      result = (int)&g_EffMgrData._tail_000[1028];
      break;
    case 12:
      result = (int)&g_EffMgrData._tail_000[40];
      break;
    case 13:
      result = (int)&g_EffMgrData._tail_000[32];
      break;
    case 14:
      result = (int)&g_EffMgrData._tail_000[24];
      break;
    case 15:
      result = (int)&g_EffMgrData._tail_000[12];
      break;
    case 16:
      result = (int)&g_EffMgrData;
      break;
    case 20:
      result = (int)&g_pszEditorDesc;
      break;
    case 21:
      result = (int)&g_EffMgrData._tail_000[580];
      break;
    default:
      result = (int)g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004D0BD0
void CEffModel::UpdateDuration(int nVal1)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi

  v3 = *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 4);
  if ( v3 || *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 5) )
  {
    v4 = 0;
    if ( v3 > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(*(_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + v5));
        ++v4;
        *(_DWORD *)(*(_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + v5) = 0;
        v5 += 152;
      }
      while ( v4 < *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 4) );
    }
    operator delete(*(void **)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)));
    *(_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) = 0;
    *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 4) = 0;
    *((_DWORD *)((CTaskTpl_tagEffTaskParam_CEffModel *)((char *)this + 12)) + 5) = 0;
  }
  if ( (nVal1 & 1) != 0 )
    operator delete(this);
}
