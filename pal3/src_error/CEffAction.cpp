#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CEffAction.h"
#include "Role/Actor.h"
#include "Combat/CCBStage.h"
#include "Effect/CEffMgr.h"
#include "Misc/CEffObj.h"
#include "Effect/CEffect.h"
#include "Effect/CEffgbParticle.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffAction.h"
#include "Render/RenderTarget2.h"
#include "Misc/tagEffMgrData.h"
#include "Misc/tagEffTaskParam.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern int dword_5D4D44;
extern int dword_5D4D58;
extern int dword_5D4D70;
extern int dword_5D4D88;
extern int dword_5D4D94;
extern int dword_5D4DA0;

// 0x004C0500
bool CEffAction::OnTest()
{
  return 0;
}

// 0x004C0510
int CEffAction::sub_4C0510(int a2)
{
  return (int)g_EffCylinderEditorData;
}

// 0x004C0520
void CEffAction::AllocRenderTarget()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x34u);
  if ( v1 )
    (((RenderTarget2 *)v1))->RenderTarget2::ClearTarget();
}

// 0x004C0540
char * CEffAction::_sdtor_call_dtor(char a2)
{
  (((RenderTarget2 *)this))->RenderTarget2::ExecutePasses() /* [ROWTABLE] */;
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return (char *)this;
}

// 0x004C0640
void CEffAction::ResetState(int nVal1, int nVal2, int nVal3, int nVal4)
{
  this->m_bIdle = 0;
  this->m_nController = -1;
}

// 0x004C0650
char CEffAction::AllocSegments(int nVal)
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
  *(_DWORD *)&this->_tail_000[12] = (_DWORD)v3;
  if ( !v3 )
    return 1;
  v4 = 0;
  v5 = 0;
  while ( 1 )
  {
    *(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + v5) = (unsigned long)operator new(0x2D0u);
    if ( !*(_DWORD *)(*(_DWORD *)&this->_tail_000[12] + v5) )
      break;
    v5 += 152;
    ++v4;
    if ( v5 >= 1216 )
    {
      v6 = 0;
      *(_DWORD *)&this->_tail_000[28] = 8;
      *(_DWORD *)&this->_tail_000[32] = 10;
      v7 = 0;
      do
      {
        *(_BYTE *)(*(_DWORD *)&this->_tail_000[12] + v7 + 148) = 0;
        v8 = 0;
        if ( *(int *)&this->_tail_000[32] > 0 )
        {
          v9 = 0;
          do
          {
            ++v8;
            v9 += 72;
            *(_BYTE *)(v9 + *(_DWORD *)(v7 + *(_DWORD *)&this->_tail_000[12]) - 8) = 0;
          }
          while ( v8 < *(_DWORD *)&this->_tail_000[32] );
        }
        ++v6;
        v7 += 152;
      }
      while ( v6 < *(_DWORD *)&this->_tail_000[28] );
      return 1;
    }
  }
  if ( v4 > 0 && v4 - 1 >= 0 )
  {
    v11 = v4;
    v12 = 152 * (v4 - 1);
    do
    {
      operator delete(*(void **)(*(_DWORD *)&this->_tail_000[12] + v12));
      v12 -= 152;
      --v11;
    }
    while ( v11 );
  }
  operator delete(*(void **)&this->_tail_000[12]);
  return 1;
}

// 0x004C0740
void CEffAction::UpdateFrame(float fVal)
{
    CEffAction *_this = this;
  CTaskTpl_tagEffTaskParam_CEffAction *v2; // esi
  int v3; // edx
  int v4; // ebp
  int v5; // ebx
  int v6; // edi
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  bool v10; // cc
  int m_nController; // eax
  int v12; // [esp+0x0] [ebp-0x8]
  CEffAction *v13; // [esp+0x4] [ebp-0x4]
  int fVala; // [esp+0xC] [ebp+0x4]

  v2 = ((CTaskTpl_tagEffTaskParam_CEffAction *)((char *)_this + 12));
  v13 = _this;
  *(float *)&_this->_tail_000[8] = fVal - *(float *)&_this->_tail_000[4];
  *(float *)&_this->_tail_000[4] = fVal;
  if ( *(float *)&_this->_tail_000[8] > 0.0f )
  {
    v3 = 0;
    fVala = 0;
    if ( *(int *)&_this->_tail_000[28] > 0 )
    {
      v12 = 0;
      while ( 1 )
      {
        v4 = v12 + *(_DWORD *)&v2->_tail_000[12];
        if ( *(_BYTE *)(v4 + 148) )
        {
          if ( *(_DWORD *)(v4 + 12) == 3 )
          {
            v5 = 0;
            if ( *(int *)&v2->_tail_000[32] > 0 )
              break;
          }
        }
LABEL_29:
        v3 = fVala + 1;
        v10 = ++fVala < *(_DWORD *)&v2->_tail_000[28];
        v12 += 152;
        if ( !v10 )
        {
          _this = v13;
          goto LABEL_31;
        }
      }
      v6 = 0;
      while ( 1 )
      {
        v7 = v6 + *(_DWORD *)v4;
        if ( !*(_BYTE *)(v7 + 64) || v6 > 0 && *(_DWORD *)(v7 - 64) == 2 )
          goto LABEL_29;
        if ( *(_DWORD *)(v7 + 8) == 2 )
          break;
        if ( *(_DWORD *)(v7 + 8) == 3 )
          goto LABEL_22;
        if ( *(_DWORD *)(v7 + 8) == 4 )
        {
          if ( (((CCBStage *)v2))->CCBStage::SetTaskState(v3) )
          {
            v8 = *(_DWORD *)(v4 + 4);
            *(_DWORD *)(v4 + 12) = 4;
            v9 = 9 * v8;
            LOBYTE(v8) = *(_BYTE *)(v4 + 149);
            *(_DWORD *)(v4 + 20) = *(_DWORD *)(*(_DWORD *)v4 + 8 * v9 - 12);
            if ( (_BYTE)v8 == 1 )
            {
              (((CEffgbParticle *)v2))->CEffgbParticle::Init(fVala);
              goto LABEL_29;
            }
          }
        }
LABEL_26:
        ++v5;
        v6 += 72;
        if ( v5 >= *(_DWORD *)&v2->_tail_000[32] )
          goto LABEL_29;
        v3 = fVala;
      }
      if ( v6 <= 0 )
        goto LABEL_26;
      if ( *(float *)(v7 + 20) >= 0.0f )
      {
        if ( *(float *)&v2->_tail_000[4] - *(float *)(v7 - 56) <= *(float *)(v7 + 20) )
          goto LABEL_26;
        (((CCBStage *)v2))->CCBStage::GetTaskParam(v3, v5);
        *(_DWORD *)&v2->_tail_000[16] = fVala;
      }
      else
      {
        if ( *(_DWORD *)(v7 - 64) != 4 )
          goto LABEL_26;
        *(_DWORD *)(*(_DWORD *)(v12 + *(_DWORD *)&v2->_tail_000[12]) + v6 + 8) = 3;
        *(_DWORD *)(*(_DWORD *)(v12 + *(_DWORD *)&v2->_tail_000[12]) + v6 + 16) = *(_DWORD *)&v2->_tail_000[4];
LABEL_22:
        *(_DWORD *)&v2->_tail_000[16] = v3;
      }
      *(_DWORD *)&v2->_tail_000[20] = v5;
      (*(void ( **)(CTaskTpl_tagEffTaskParam_CEffAction *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)*(void**)(v2)
                                                                                            + 4))(
        v2,
        *(_DWORD *)(*(_DWORD *)v4 + v6),
        *(_DWORD *)(*(_DWORD *)v4 + v6 + 4),
        0);
      goto LABEL_26;
    }
LABEL_31:
    if ( *(int *)&_this->_tail_000[24] <= 0 )
    {
      m_nController = _this->m_nController;
      _this->m_bIdle = 1;
      if ( m_nController != -1 )
        *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&_this->m_pEM->CEffObj::_tail_000[4] + 20) + 4 * m_nController + 24)
                 + 380) = 0;
    }
  }
}

// 0x004C0920
void CEffAction::PrepareEffect(int nVal)
{
  unsigned int v3; // [esp+0x4] [ebp-0x4]
  int nVala; // [esp+0x10] [ebp+0x8]

  if ( *(_DWORD *)&this->m_pEM->CEffObj::_tail_000[4] )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v3 = (int)*(float *)(nVal + 84);
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    nVala = (int)*(float *)nVal;
    if ( v3 <= 0xA && nVala > 0 )
      (((Actor *)*(Actor **)(*(_DWORD *)(*(_DWORD *)&this->m_pEM->CEffObj::_tail_000[4] + 20) + 4 * v3 + 24)))->Actor::GetAnimDurationByIndex(nVala);
  }
}

// 0x004C09E0
void CEffAction::RenderScene(int a2)
{
  CTaskTpl_tagEffTaskParam_CEffAction *v2; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // esi
  _BYTE *i; // eax
  int v7; // ebp
  unsigned int v8; // eax
  int v9; // ecx
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

  v2 = ((CTaskTpl_tagEffTaskParam_CEffAction *)((char *)this + 12));
  v3 = *(_DWORD *)&this->_tail_000[28];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *(_DWORD *)&v2->_tail_000[12];
    for ( i = (_BYTE *)(v5 + 148); *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)(v5 + v7 + 12) = 2;
    *(_BYTE *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 148) = 1;
    *(_BYTE *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 149) = 1;
    v8 = ++g_nRenderSceneSeq;
    if ( !g_nRenderSceneSeq || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nRenderSceneSeq = 1;
    }
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 16) = v8;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4) = 0;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 8) = 0;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 20) = 0;
    if ( a2 )
      qmemcpy((void *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 24), (const void *)a2, 0x7Cu);
    else
      memset((void *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 24), 0, 0x7Cu);
    ++*(_DWORD *)&v2->_tail_000[24];
    if ( v4 != -1 )
    {
      v9 = *(_DWORD *)&v2->_tail_000[32];
      v10 = 0;
      if ( v9 > 0 )
      {
        v11 = *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + 152 * v4);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *(int (CEffect::**)(int))v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nRenderSceneSeq;
        if ( !g_nRenderSceneSeq || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nRenderSceneSeq = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
        ++*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4);
      }
LABEL_22:
      v15 = *(_DWORD *)&v2->_tail_000[32];
      v16 = 0;
      if ( v15 > 0 )
      {
        v17 = *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + 152 * v4);
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
        v20 = ++g_nRenderSceneSeq;
        if ( !g_nRenderSceneSeq || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nRenderSceneSeq = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4);
      }
LABEL_31:
      (((RenderTarget2 *)v2))->RenderTarget2::RenderScene(v4, 0 /* TODO: pmf_to_u32((int (RenderTarget2::*)(int))RenderTarget2::SceneRoleCallback) */, 0, 0, *(_DWORD *)(a2 + 72), *(_DWORD *)(a2 + 76));
      *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7) + 16) = *(_DWORD *)&v2->_tail_000[4];
    }
  }
}

// 0x004C1270
int CEffAction::sub_4C1270(int a2)
{
  int result; // eax

  switch ( a2 )
  {
    case 0:
      result = (int)&g_EffMgrData._tail_000[156];
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
      result = (int)&g_EffMgrData._tail_000[112];
      break;
    case 6:
      result = (int)&g_EffMgrData._tail_000[104];
      break;
    case 7:
      result = (int)&g_EffMgrData._tail_000[96];
      break;
    case 8:
      result = (int)&g_EffMgrData._tail_000[84];
      break;
    case 9:
      result = (int)&g_EffMgrData._tail_000[72];
      break;
    case 10:
      result = (int)&g_EffMgrData._tail_000[60];
      break;
    case 11:
      result = (int)&g_EffMgrData._tail_000[48];
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
    case 17:
      result = (int)dword_5D4DA0;
      break;
    case 18:
      result = (int)dword_5D4D94;
      break;
    case 19:
      result = (int)dword_5D4D88;
      break;
    case 20:
      result = (int)&g_pszEditorDesc;
      break;
    case 21:
      result = (int)dword_5D4D70;
      break;
    case 22:
      result = (int)dword_5D4D58;
      break;
    case 23:
      result = (int)dword_5D4D44;
      break;
    default:
      result = (int)g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004C15D0
void CEffAction::UpdateParticles()
{
  int v1; // ebp
  int v2; // esi
  int v3; // edi
  int v4; // eax
  _DWORD *v5; // edx

  v1 = 0;
  if ( *(int *)&this->_tail_000[28] > 0 )
  {
    v2 = 0;
    do
    {
      if ( *(_BYTE *)(*(_DWORD *)&this->_tail_000[12] + v2 + 148) )
      {
        v3 = 0;
        if ( *(int *)&this->_tail_000[32] > 0 )
        {
          v4 = 0;
          do
          {
            v5 = (_DWORD *)(v2 + *(_DWORD *)&this->_tail_000[12]);
            if ( *(_BYTE *)(*v5 + v4 + 64) )
              *(_BYTE *)(*v5 + v4 + 66) = 1;
            ++v3;
            v4 += 72;
          }
          while ( v3 < *(_DWORD *)&this->_tail_000[32] );
        }
        *(_BYTE *)(*(_DWORD *)&this->_tail_000[12] + v2 + 149) = 1;
      }
      ++v1;
      v2 += 152;
    }
    while ( v1 < *(_DWORD *)&this->_tail_000[28] );
  }
}
