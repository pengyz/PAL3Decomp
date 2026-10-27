#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffSParticle.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Effect/CEffMgr.h"
#include "Misc/CEffObj.h"
#include "Effect/CEffect.h"
#include "Misc/CTaskTpl_tagEffTaskParam_CEffSParticle.h"
#include "Misc/PtrArray.h"
#include "Misc/tagEffMgrData.h"
#include "Misc/tagEffSParticleSys.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4D4EA0(...);

// 0x004D4EE0
CEffSParticle::CEffSParticle()
{
  void *v1; // eax

  v1 = (void *)operator new(0x30u);
  if ( v1 )
    sub_4D4EA0(v1);
}

// 0x004D4F20
CEffSParticle::~CEffSParticle()
{
  CTaskTpl_tagEffTaskParam_CEffSParticle *v1; // esi
  int v2; // ebx
  int v3; // edi

  v1 = this != 0 ? ((CTaskTpl_tagEffTaskParam_CEffSParticle *)((char *)this + 12)) : 0;
  if ( *(_DWORD *)&v1->_tail_000[28] || *(this != 0 ? (_DWORD *)&this->_tail_000[32] : (_DWORD *)32) )
  {
    v2 = 0;
    if ( *(this != 0 ? (int *)&this->_tail_000[28] : (int *)28) > 0 )
    {
      v3 = 0;
      do
      {
        operator delete(*(void **)(v3 + *(_DWORD *)&v1->_tail_000[12]));
        ++v2;
        *(_DWORD *)(v3 + *(_DWORD *)&v1->_tail_000[12]) = 0;
        v3 += 152;
      }
      while ( v2 < *(_DWORD *)&v1->_tail_000[28] );
    }
    operator delete(*(void **)&v1->_tail_000[12]);
    *(_DWORD *)&v1->_tail_000[12] = 0;
    *(_DWORD *)&v1->_tail_000[28] = 0;
    *(_DWORD *)&v1->_tail_000[32] = 0;
  }
}

// 0x004D4FC0
int CEffSParticle::Create(float pType)
{
    CEffSParticle *_this = this;
  CTaskTpl_tagEffTaskParam_CEffSParticle *v2; // esi
  int v3; // ebx
  int *v4; // ebp
  int v5; // edx
  int v6; // edi
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // edx
  _DWORD *v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int result; // eax
  int v17; // [esp+0xC] [ebp-0x8]
  CEffSParticle *v18; // [esp+0x10] [ebp-0x4]
  int pTypea; // [esp+0x18] [ebp+0x4]

  v2 = ((CTaskTpl_tagEffTaskParam_CEffSParticle *)((char *)_this + 12));
  v3 = 0;
  v18 = _this;
  *(float *)&_this->_tail_000[8] = pType - *(float *)&_this->_tail_000[4];
  *(float *)&_this->_tail_000[4] = pType;
  pTypea = 0;
  if ( *(int *)&_this->_tail_000[28] <= 0 )
    goto LABEL_34;
  do
  {
    v4 = (int *)(v3 + *(_DWORD *)&v2->_tail_000[12]);
    if ( *((_BYTE *)v4 + 148) )
    {
      if ( v4[3] == 3 )
      {
        v5 = 0;
        v17 = 0;
        if ( *(int *)&v2->_tail_000[32] > 0 )
        {
          v6 = 0;
          do
          {
            v7 = (unsigned long)*v4;
            if ( !*(_BYTE *)(v6 + *v4 + 64) || v6 > 0 && *(_DWORD *)(v6 + v7 - 64) == 2 )
              break;
            switch ( *(_DWORD *)(v6 + v7 + 8) )
            {
              case 2:
                if ( v6 > 0 )
                {
                  if ( *(float *)(v6 + v7 + 20) >= 0.0f )
                  {
                    if ( *(float *)&v2->_tail_000[4] - *(float *)(v6 + v7 - 56) > *(float *)(v6 + v7 + 20) )
                    {
LABEL_24:
                      *(_DWORD *)(*(_DWORD *)(v3 + *(_DWORD *)&v2->_tail_000[12]) + v6 + 8) = 3;
                      *(_DWORD *)(*(_DWORD *)(v3 + *(_DWORD *)&v2->_tail_000[12]) + v6 + 16) = *(_DWORD *)&v2->_tail_000[4];
                      *(_DWORD *)&v2->_tail_000[16] = pTypea;
                      *(_DWORD *)&v2->_tail_000[20] = v17;
                      goto LABEL_25;
                    }
                  }
                  else if ( *(_DWORD *)(v6 + v7 - 64) == 4 )
                  {
                    goto LABEL_24;
                  }
                }
                break;
              case 3:
                *(_DWORD *)&v2->_tail_000[20] = v5;
                *(_DWORD *)&v2->_tail_000[16] = pTypea;
LABEL_25:
                (*(void ( **)(CTaskTpl_tagEffTaskParam_CEffSParticle *, _DWORD, _DWORD, _DWORD))(*(_DWORD *)*(void**)(v2) + 4))(
                  v2,
                  *(_DWORD *)(*v4 + v6),
                  *(_DWORD *)(*v4 + v6 + 4),
                  0);
                break;
              case 4:
                v8 = 0;
                v9 = (_DWORD *)(v3 + *(_DWORD *)&v2->_tail_000[12]);
                v10 = (unsigned long)v9[1];
                if ( v10 <= 0 )
                {
LABEL_16:
                  v12 = (unsigned long)v4[1];
                  v4[3] = 4;
                  v13 = 9 * v12;
                  LOBYTE(v12) = *((_BYTE *)v4 + 149);
                  v4[5] = *(_DWORD *)(*v4 + 8 * v13 - 12);
                  if ( (_BYTE)v12 == 1 )
                  {
                    v14 = 0;
                    *(_BYTE *)(v3 + *(_DWORD *)&v2->_tail_000[12] + 148) = 0;
                    if ( *(int *)&v2->_tail_000[32] > 0 )
                    {
                      v15 = 0;
                      do
                      {
                        ++v14;
                        v15 += 72;
                        *(_BYTE *)(*(_DWORD *)(v3 + *(_DWORD *)&v2->_tail_000[12]) + v15 - 8) = 0;
                      }
                      while ( v14 < *(_DWORD *)&v2->_tail_000[32] );
                    }
                    *(_DWORD *)(v3 + *(_DWORD *)&v2->_tail_000[12] + 4) = 0;
                    --*(_DWORD *)&v2->_tail_000[24];
                    goto LABEL_32;
                  }
                }
                else
                {
                  v11 = (_DWORD *)(*v9 + 8);
                  while ( *v11 == 4 )
                  {
                    ++v8;
                    v11 += 18;
                    if ( v8 >= v10 )
                      goto LABEL_16;
                  }
                }
                break;
            }
            v5 = v17 + 1;
            v6 += 72;
            ++v17;
          }
          while ( v17 < *(_DWORD *)&v2->_tail_000[32] );
        }
      }
    }
LABEL_32:
    v3 += 152;
    ++pTypea;
  }
  while ( pTypea < *(_DWORD *)&v2->_tail_000[28] );
  _this = v18;
LABEL_34:
  result = *(_DWORD *)&_this->_tail_000[24];
  if ( result <= 0 )
    _this->m_bIdle = 1;
  return result;
}

// 0x004D51B0
void CEffSParticle::Init(int *pType)
{
  CTaskTpl_tagEffTaskParam_CEffSParticle *v2; // ebx
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

  v2 = ((CTaskTpl_tagEffTaskParam_CEffSParticle *)((char *)this + 12));
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
    v8 = ++g_SParticleSys.m_nEffCount;
    if ( !g_SParticleSys.m_nEffCount || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_SParticleSys.m_nEffCount = 1;
    }
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 16) = v8;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4) = 0;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 8) = 0;
    *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 20) = 0;
    if ( pType )
      qmemcpy((void *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 24), pType, 0x7Cu);
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
        v14 = ++g_SParticleSys.m_nEffCount;
        if ( !g_SParticleSys.m_nEffCount || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_SParticleSys.m_nEffCount = 1;
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
        v20 = ++g_SParticleSys.m_nEffCount;
        if ( !g_SParticleSys.m_nEffCount || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_SParticleSys.m_nEffCount = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
        ++*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 4);
      }
LABEL_31:
      (((CEffSParticle *)v2))->CEffSParticle::Render(v4, 0 /* TODO: pmf_to_u32((int (CEffSParticle::*)(int))CEffSParticle::Attach) */, 0, 0, pType[18], pType[19]);
      *(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7 + 12) = 3;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7) + 8) = 3;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)&v2->_tail_000[12] + v7) + 16) = *(_DWORD *)&v2->_tail_000[4];
    }
  }
}

// 0x004D53E0
int CEffSParticle::Attach(int nVal)
{
  int v3; // edi
  int v4; // ebx
  int v5; // ecx
  float v7; // [esp+0xC] [ebp-0xC]
  float v8; // [esp+0x10] [ebp-0x8]
  float formal; // [esp+0x14] [ebp-0x4]
  float formala; // [esp+0x14] [ebp-0x4]

  v3 = *(_DWORD *)&this->_tail_000[12] + 152 * *(_DWORD *)&this->_tail_000[16];
  v4 = *(_DWORD *)v3 + 72 * *(_DWORD *)&this->_tail_000[20];
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  if ( !*(_BYTE *)(v4 + 65) )
  {
    *(float *)(v4 + 56) = *(float *)(*(_DWORD *)&this->m_pEM->CEffObj::_tail_000[4] + 104);
    if ( *(_BYTE *)(v3 + 113) )
      *(float *)(v4 + 44) = *(float *)(*(_DWORD *)&this->m_pEM->CEffObj::_tail_000[4] + 108);
    if ( *(_BYTE *)(v3 + 114) )
      (((CCBSystem *)*(CCBSystem **)&this->m_pEM->CEffObj::_tail_000[4]))->CCBSystem::ProcAI(*(float *)(v3 + 24));
    *(_BYTE *)(v4 + 65) = 1;
  }
  v5 = *(_DWORD *)&this->m_pEM->CEffObj::_tail_000[4];
  v7 = *(double *)(v5 + 88);
  v8 = *(float *)(v5 + 104);
  if ( v8 - *(float *)(v4 + 56) > *(float *)(v3 + 28) )
  {
    formal = *(float *)(v5 + 108) + v7 * *(float *)(v3 + 32);
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( formal <= 20.0f )
    {
      if ( formal < 0.0f )
        formal = 0.0f;
      (((CCBSystem *)*(CCBSystem **)&this->m_pEM->CEffObj::_tail_000[4]))->CCBSystem::ProcAI(formal);
    }
    else
    {
      (((CCBSystem *)*(CCBSystem **)&this->m_pEM->CEffObj::_tail_000[4]))->CCBSystem::ProcAI(20.0);
    }
  }
  if ( v8 - *(float *)(v4 + 56) > *(float *)(v3 + 36) )
  {
    formala = *(float *)(*(_DWORD *)&this->m_pEM->CEffObj::_tail_000[4] + 108) + v7 * *(float *)(v3 + 56);
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( formala <= 20.0f )
    {
      if ( formala < 0.0f )
        formala = 0.0f;
      (((CCBSystem *)*(CCBSystem **)&this->m_pEM->CEffObj::_tail_000[4]))->CCBSystem::ProcAI(formala);
    }
    else
    {
      (((CCBSystem *)*(CCBSystem **)&this->m_pEM->CEffObj::_tail_000[4]))->CCBSystem::ProcAI(20.0);
    }
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || v8 - *(float *)(v4 + 56) >= *(float *)(v4 + 24) )
  {
    if ( *(_BYTE *)(v3 + 113) )
      (((CCBSystem *)*(CCBSystem **)&this->m_pEM->CEffObj::_tail_000[4]))->CCBSystem::ProcAI(1.0);
    *(_DWORD *)(v4 + 8) = 4;
  }
  return 0;
}

// 0x004D5620
int * CEffSParticle::GetEffTypeData(float fCurTime)
{
  int *result; // eax

  switch ( LODWORD(fCurTime) )
  {
    case 0:
      result = (int *)&unk_5D576C;
      break;
    case 1:
    case 3:
      result = (int *)&unk_5D5760;
      break;
    case 2:
    case 4:
      result = (int *)&unk_5D5758;
      break;
    case 9:
      result = (int *)&g_EffMgrData._tail_000[72];
      break;
    case 0x14:
      result = (int *)&g_pszEditorDesc;
      break;
    case 0x16:
      result = (int *)&unk_5D5744;
      break;
    case 0x17:
      result = (int *)&unk_5D572C;
      break;
    default:
      result = (int *)g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004D56B0
int CEffSParticle::Render(
        
        int nVal,
        int nVal2,
        int nVal3,
        int *p_DWORD,
        int nVal4,
        int nVal5)
{
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  int *v15; // edx

  v8 = *(_DWORD *)&this->_tail_000[20];
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*(_DWORD *)*(void**)(this) + 152 * nVal);
  for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
  {
    if ( ++v9 >= v8 )
      return -1;
  }
  v13 = (int *)(v10 + 72 * v9);
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = nVal2;
  v13[1] = nVal3;
  v13[2] = 2;
  v14 = ++g_SParticleSys.m_nEffCount;
  if ( !g_SParticleSys.m_nEffCount || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_SParticleSys.m_nEffCount = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = (int *)(v13 + 7);
    *v15 = *p_DWORD;
    v15[1] = (unsigned long)p_DWORD[1];
    v15[2] = (unsigned long)p_DWORD[2];
    v15[3] = (unsigned long)p_DWORD[3];
  }
  ++*(_DWORD *)(*(_DWORD *)*(void**)(this) + 152 * nVal + 4);
  return v9;
}

// 0x004D5790
void * CEffSParticle::SetTimeScale(CEffSParticle *Block, char fTimeScale)
{
  int v4; // eax
  int v5; // ebx
  int v6; // edi

  v4 = *(_DWORD *)&this->_tail_000[16];
  if ( v4 || *(_DWORD *)&this->_tail_000[20] )
  {
    v5 = 0;
    if ( v4 > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(*(_DWORD *)*(void**)(this) + v6));
        ++v5;
        *(_DWORD *)(*(_DWORD *)*(void**)(this) + v6) = 0;
        v6 += 152;
      }
      while ( v5 < *(_DWORD *)&this->_tail_000[16] );
    }
    operator delete(*(void **)*(void**)(this));
    *(_DWORD *)*(void**)(this) = 0;
    *(_DWORD *)&this->_tail_000[16] = 0;
    *(_DWORD *)&this->_tail_000[20] = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004D5850
void CEffSParticle::Create_adjthunk()
{
  float v1; // [esp+0x4] [ebp+0x4]

  (((CEffSParticle *)((char *)this - 12)))->CEffSParticle::Create(v1);
}

// 0x004D5860
char * CEffSParticle::CreateTask(char p)
{
  return (((CEffSParticle *)((char *)this - 12)))->CEffSParticle::_scalar_dtor_4F00(p);
}

// 0x004D58D0
const char * CEffSParticle::GetEditorTaskDescription(int nIndex)
{
  unsigned __int8 *v4; // edx
  int v5; // esi
  unsigned __int16 v6; // cx
  unsigned __int8 v7; // bl
  unsigned int i; // eax
  int v9; // ecx
  int v10; // eax

  if ( !*(_BYTE *)nIndex )
    return 0;
  v4 = (unsigned __int8 *)(nIndex + 1);
  v5 = *(unsigned __int8 *)nIndex << 24;
  if ( *(_BYTE *)(nIndex + 1) )
  {
    v5 |= *(unsigned __int8 *)(nIndex + 1) << 16;
    v4 = (unsigned __int8 *)(nIndex + 2);
    if ( *(_BYTE *)(nIndex + 2) )
    {
      LOBYTE(v6) = 0;
      HIBYTE(v6) = *(_BYTE *)(nIndex + 2);
      v5 |= v6;
      v4 = (unsigned __int8 *)(nIndex + 3);
      if ( *(_BYTE *)(nIndex + 3) )
      {
        v5 |= *(unsigned __int8 *)(nIndex + 3);
        v4 = (unsigned __int8 *)(nIndex + 4);
      }
    }
  }
  v7 = *v4;
  for ( i = ~v5; v7; ++v4 )
  {
    v9 = *((_DWORD *)&this->vfptr + HIBYTE(i));
    v10 = v7 | (i << 8);
    v7 = v4[1];
    i = v9 ^ v10;
  }
  return (const char *)~i;
}
