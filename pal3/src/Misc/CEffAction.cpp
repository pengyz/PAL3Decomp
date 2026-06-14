#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CEffAction.h"

// Forward declarations for unnamed functions
void __cdecl todo_401800(void);

// 0x004C0500
int CEffAction::OnTest()
{
  int result; // eax

  LOBYTE(result) = 0;
  return result;
}

// 0x004C0520
void CEffAction::AllocRenderTarget()
{
  RenderTarget2 *v1; // eax

  v1 = (RenderTarget2 *)operator new(0x34u);
  if ( v1 )
    ((RenderTarget2 *)v1)->ClearTarget();
}

// 0x004C0540
char * CEffAction::ExecutePasses(char a2)
{
  ((RenderTarget2 *)this)->ExecutePasses();
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return (char *)this;
}

// 0x004C0640
void CEffAction::ResetState()
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

  v3 = operator new(0x4C0u);
// [VFTABLE] *((_DWORD *)&this->__vftable + 3) = v3;
  if ( !v3 )
    return 1;
  v4 = 0;
  v5 = 0;
  while ( 1 )
  {
// [VFTABLE] *(_DWORD *)(*((_DWORD *)&this->__vftable + 3) + v5) = operator new(0x2D0u);
// [VFTABLE] if ( !*(_DWORD *)(*((_DWORD *)&this->__vftable + 3) + v5) )
      break;
    v5 += 152;
    ++v4;
    if ( v5 >= 1216 )
    {
      v6 = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 7) = 8;
// [VFTABLE] *((_DWORD *)&this->__vftable + 8) = 10;
      v7 = 0;
      do
      {
// [VFTABLE] *(_BYTE *)(*((_DWORD *)&this->__vftable + 3) + v7 + 148) = 0;
        v8 = 0;
// [VFTABLE] if ( *((int *)&this->__vftable + 8) > 0 )
        {
          v9 = 0;
          do
          {
            ++v8;
            v9 += 72;
// [VFTABLE] *(_BYTE *)(v9 + *(_DWORD *)(v7 + *((_DWORD *)&this->__vftable + 3)) - 8) = 0;
          }
// [VFTABLE] while ( v8 < *((_DWORD *)&this->__vftable + 8) );
        }
        ++v6;
        v7 += 152;
      }
// [VFTABLE] while ( v6 < *((_DWORD *)&this->__vftable + 7) );
      return 1;
    }
  }
  if ( v4 > 0 && v4 - 1 >= 0 )
  {
    v11 = v4;
    v12 = 152 * (v4 - 1);
    do
    {
// [VFTABLE] operator delete(*(void **)(*((_DWORD *)&this->__vftable + 3) + v12));
      v12 -= 152;
      --v11;
    }
    while ( v11 );
  }
// [VFTABLE] operator delete(*(&this->__vftable + 3));
  return 1;
}

// 0x004C0740
void CEffAction::UpdateFrame(float fVal)
{
  CTaskTpl_tagEffTaskParam_CEffAction *p_vftable; // esi
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

// [VFTABLE] p_vftable = (CTaskTpl_tagEffTaskParam_CEffAction *)&this->__vftable;
// [VFTABLE] *((float *)&this->__vftable + 2) = fVal - *((float *)&this->__vftable + 1);
// [VFTABLE] *((float *)&this->__vftable + 1) = fVal;
// [VFTABLE] if ( *((float *)&this->__vftable + 2) > 0.0 )
  {
    v3 = 0;
    fVala = 0;
// [VFTABLE] if ( *((int *)&this->__vftable + 7) > 0 )
    {
      v12 = 0;
      while ( 1 )
      {
// [VFTABLE] v4 = v12 + *((_DWORD *)&p_vftable->__vftable + 3);
        if ( *(_BYTE *)(v4 + 148) )
        {
          if ( *(_DWORD *)(v4 + 12) == 3 )
          {
            v5 = 0;
// [VFTABLE] if ( *((int *)&p_vftable->__vftable + 8) > 0 )
              break;
          }
        }
LABEL_29:
        v3 = fVala + 1;
// [VFTABLE] v10 = ++fVala < *((_DWORD *)&p_vftable->__vftable + 7);
        v12 += 152;
        if ( !v10 )
        {
          this = v13;
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
          if ( ((CCBStage *)p_vftable)->SetTaskState(v3) )
          {
            v8 = *(_DWORD *)(v4 + 4);
            *(_DWORD *)(v4 + 12) = 4;
            v9 = 9 * v8;
            LOBYTE(v8) = *(_BYTE *)(v4 + 149);
            *(_DWORD *)(v4 + 20) = *(_DWORD *)(*(_DWORD *)v4 + 8 * v9 - 12);
            if ( (_BYTE)v8 == 1 )
            {
              ((CEffgbParticle *)p_vftable)->Init(fVala);
              goto LABEL_29;
            }
          }
        }
LABEL_26:
        ++v5;
        v6 += 72;
// [VFTABLE] if ( v5 >= *((_DWORD *)&p_vftable->__vftable + 8) )
          goto LABEL_29;
        v3 = fVala;
      }
      if ( v6 <= 0 )
        goto LABEL_26;
      if ( *(float *)(v7 + 20) >= 0.0 )
      {
// [VFTABLE] if ( *((float *)&p_vftable->__vftable + 1) - *(float *)(v7 - 56) <= *(float *)(v7 + 20) )
          goto LABEL_26;
        ((CCBStage *)p_vftable)->GetTaskParam(v3, v5);
// [VFTABLE] *((_DWORD *)&p_vftable->__vftable + 4) = fVala;
      }
      else
      {
        if ( *(_DWORD *)(v7 - 64) != 4 )
          goto LABEL_26;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)(v12 + *((_DWORD *)&p_vftable->__vftable + 3)) + v6 + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)(v12 + *((_DWORD *)&p_vftable->__vftable + 3)) + v6 + 16) = *((_DWORD *)&p_vftable->__vftable
// [VFTABLE]   + 1);
LABEL_22:
// [VFTABLE] *((_DWORD *)&p_vftable->__vftable + 4) = v3;
      }
// [VFTABLE] *((_DWORD *)&p_vftable->__vftable + 5) = v5;
// [VFTABLE] (*((void ( **)(CTaskTpl_tagEffTaskParam_CEffAction *, _DWORD, _DWORD, _DWORD))p_vftable->__vftable + 1))(
// [VFTABLE]   p_vftable,
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v4 + v6),
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v4 + v6 + 4),
// [VFTABLE]   0);
      goto LABEL_26;
    }
LABEL_31:
// [VFTABLE] if ( *((int *)&this->__vftable + 6) <= 0 )
    {
      m_nController = this->m_nController;
      this->m_bIdle = 1;
      if ( m_nController != -1 )
        this->m_pEM->m_pCBSystem->m_pStage->m_pRole[m_nController]->m_bForceFinishThrowingWeapon = 0;
    }
  }
}

// 0x004C0920
void CEffAction::PrepareEffect()
{
  unsigned int v2; // [esp+0x4] [ebp-0x4]
  float *nVal; // [esp+0x10] [ebp+0x8]
  int nVala; // [esp+0x10] [ebp+0x8]

  if ( this->m_pEM->m_pCBSystem )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v2 = (int)nVal[21];
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    nVala = (int)*nVal;
    if ( v2 <= 0xA && nVala > 0 )
      ((Actor *)this->m_pEM->m_pCBSystem->m_pStage->m_pRole[v2])->GetAnimDurationByIndex(nVala);
  }
}

// 0x004C09E0
void CEffAction::RenderScene()
{
  RenderTarget2 *p_vftable; // ebx
  int v2; // ecx
  int v3; // edx
  int m_SubObj; // esi
  _BYTE *i; // eax
  int v6; // ebp
  unsigned int v7; // eax
  int m_nCurPass; // ecx
  int v9; // eax
  int v10; // edi
  _BYTE *v11; // esi
  int ( **v12)(CEffect *, int); // esi
  unsigned int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // edi
  _BYTE *v17; // esi
  int ( **v18)(CEffect *, int); // esi
  unsigned int v19; // eax
  int *v20; // [esp+0x18] [ebp+0x4]

// [VFTABLE] p_vftable = (RenderTarget2 *)&this->__vftable;
// [VFTABLE] v2 = *((_DWORD *)&this->__vftable + 7);
  v3 = 0;
  if ( v2 > 0 )
  {
    m_SubObj = p_vftable->m_SubObj;
    for ( i = (_BYTE *)(m_SubObj + 148); *i; i += 152 )
    {
      if ( ++v3 >= v2 )
        return;
    }
    v6 = 152 * v3;
    *(_DWORD *)(m_SubObj + v6 + 12) = 2;
    *(_BYTE *)(p_vftable->m_SubObj + v6 + 148) = 1;
    *(_BYTE *)(p_vftable->m_SubObj + v6 + 149) = 1;
    v7 = ++g_PAL3.m_nRenderTarget2Count;
    if ( !g_PAL3.m_nRenderTarget2Count || v7 >= 0x7FFFFFFF )
    {
      v7 = 1;
      g_PAL3.m_nRenderTarget2Count = 1;
    }
    *(_DWORD *)(p_vftable->m_SubObj + v6 + 16) = v7;
    *(_DWORD *)(p_vftable->m_SubObj + v6 + 4) = 0;
    *(_DWORD *)(p_vftable->m_SubObj + v6 + 8) = 0;
    *(_DWORD *)(p_vftable->m_SubObj + v6 + 20) = 0;
    if ( v20 )
      qmemcpy((void *)(p_vftable->m_SubObj + v6 + 24), v20, 0x7Cu);
    else
      memset((void *)(p_vftable->m_SubObj + v6 + 24), 0, 0x7Cu);
    ++p_vftable->m_pTargetArray;
    if ( v3 != -1 )
    {
      m_nCurPass = p_vftable->m_nCurPass;
      v9 = 0;
      if ( m_nCurPass > 0 )
      {
        v10 = *(_DWORD *)(p_vftable->m_SubObj + 152 * v3);
        v11 = (_BYTE *)(v10 + 64);
        while ( *v11 )
        {
          ++v9;
          v11 += 72;
          if ( v9 >= m_nCurPass )
            goto LABEL_22;
        }
        v12 = (int ( **)(CEffect *, int))(v10 + 72 * v9);
        memset(v12, 0, 0x48u);
        *v12 = CEffect::SetParam;
        *((_BYTE *)v12 + 64) = 1;
        *((_BYTE *)v12 + 65) = 0;
        v12[1] = 0;
        v12[2] = (int ( *)(CEffect *, int))2;
        v13 = ++g_PAL3.m_nRenderTarget2Count;
        if ( !g_PAL3.m_nRenderTarget2Count || v13 >= 0x7FFFFFFF )
        {
          v13 = 1;
          g_PAL3.m_nRenderTarget2Count = 1;
        }
        v12[3] = (int ( *)(CEffect *, int))v13;
        v12[5] = 0;
        v12[4] = 0;
        v12[6] = 0;
        ++*(_DWORD *)(p_vftable->m_SubObj + v6 + 4);
      }
LABEL_22:
      v14 = p_vftable->m_nCurPass;
      v15 = 0;
      if ( v14 > 0 )
      {
        v16 = *(_DWORD *)(p_vftable->m_SubObj + 152 * v3);
        v17 = (_BYTE *)(v16 + 64);
        while ( *v17 )
        {
          ++v15;
          v17 += 72;
          if ( v15 >= v14 )
            goto LABEL_31;
        }
        v18 = (int ( **)(CEffect *, int))(v16 + 72 * v15);
        memset(v18, 0, 0x48u);
        *v18 = CEffect::SetParam;
        *((_BYTE *)v18 + 64) = 1;
        *((_BYTE *)v18 + 65) = 0;
        v18[1] = 0;
        v18[2] = (int ( *)(CEffect *, int))2;
        v19 = ++g_PAL3.m_nRenderTarget2Count;
        if ( !g_PAL3.m_nRenderTarget2Count || v19 >= 0x7FFFFFFF )
        {
          v19 = 1;
          g_PAL3.m_nRenderTarget2Count = 1;
        }
        v18[3] = (int ( *)(CEffect *, int))v19;
        v18[5] = 0;
        v18[4] = 0;
        v18[6] = 0;
        ++*(_DWORD *)(p_vftable->m_SubObj + v6 + 4);
      }
LABEL_31:
      ((RenderTarget2 *)p_vftable)->RenderScene(v3, 0 /* TODO: (int)RenderTarget2::SceneRoleCallback */, 0, 0, v20[18], v20[19]);
      *(_DWORD *)(p_vftable->m_SubObj + v6 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(p_vftable->m_SubObj + v6) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(p_vftable->m_SubObj + v6) + 16) = p_vftable->m_pSurface;
    }
  }
}
