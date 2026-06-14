#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffSParticle.h"

// Forward declarations for unnamed functions
int sub_4D4EA0(...);
void __cdecl todo_401800(void);

// 0x004C15D0
void CEffSParticle::UpdateParticles()
{
  int v1; // ebp
  int v2; // esi
  int v3; // edi
  int v4; // eax
  _DWORD *v5; // edx

  v1 = 0;
  if ( *((int *)this + 10) > 0 )
  {
    v2 = 0;
    do
    {
      if ( *(_BYTE *)(*((_DWORD *)this + 6) + v2 + 148) )
      {
        v3 = 0;
        if ( *((int *)this + 11) > 0 )
        {
          v4 = 0;
          do
          {
            v5 = (_DWORD *)(v2 + *((_DWORD *)this + 6));
            if ( *(_BYTE *)(*v5 + v4 + 64) )
              *(_BYTE *)(*v5 + v4 + 66) = 1;
            ++v3;
            v4 += 72;
          }
          while ( v3 < *((_DWORD *)this + 11) );
        }
        *(_BYTE *)(*((_DWORD *)this + 6) + v2 + 149) = 1;
      }
      ++v1;
      v2 += 152;
    }
    while ( v1 < *((_DWORD *)this + 10) );
  }
}

// 0x004D4EE0
CEffSParticle::CEffSParticle()
{
  void *v1; // eax

  v1 = operator new(0x30u);
  if ( v1 )
    sub_4D4EA0(v1);
}

// 0x004D4F20
void CEffSParticle::_CEffSParticle()
{
  CEffObj *v1; // esi
  int v2; // ebx
  int v3; // edi

  v1 = this != 0 ? this + 1 : 0;
// [VFTABLE] if ( v1[2].m_pEM || (this != 0 ? (CEffObj *)((char *)this + 44) : (CEffObj *)32)->__vftable )
  {
    v2 = 0;
// [VFTABLE] if ( (int)(this != 0 ? (CEffObj *)((char *)this + 40) : (CEffObj *)28)->__vftable > 0 )
    {
      v3 = 0;
      do
      {
// [VFTABLE] operator delete(*(void **)((char *)v1[1].__vftable + v3));
        ++v2;
// [VFTABLE] *(_DWORD *)((char *)v1[1].__vftable + v3) = 0;
        v3 += 152;
      }
      while ( v2 < (int)v1[2].m_pEM );
    }
// [VFTABLE] operator delete(v1[1].__vftable);
// [VFTABLE] v1[1].__vftable = 0;
    v1[2].m_pEM = 0;
    *(_DWORD *)&v1[2].m_bIdle = 0;
  }
}

// 0x004D4FC0
int CEffSParticle::Create(float pType)
{
  CEffObj *v2; // esi
  int v3; // ebx
  char *v4; // ebp
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
  CEffMgr *pTypea; // [esp+0x18] [ebp+0x4]

  v2 = this + 1;
  v3 = 0;
*((float *)this + 5) = pType - *((float *)this + 4);
  *((float *)this + 4) = pType;
  pTypea = 0;
  if ( *((int *)this + 10) <= 0 )
    goto LABEL_34;
  do
  {
// [VFTABLE] v4 = (char *)v2[1].__vftable + v3;
    if ( v4[148] )
    {
      if ( *((_DWORD *)v4 + 3) == 3 )
      {
        v5 = 0;
        v17 = 0;
        if ( *(int *)&v2[2].m_bIdle > 0 )
        {
          v6 = 0;
          do
          {
            v7 = *(_DWORD *)v4;
            if ( !*(_BYTE *)(v6 + *(_DWORD *)v4 + 64) || v6 > 0 && *(_DWORD *)(v6 + v7 - 64) == 2 )
              break;
            switch ( *(_DWORD *)(v6 + v7 + 8) )
            {
              case 2:
                if ( v6 > 0 )
                {
                  if ( *(float *)(v6 + v7 + 20) >= 0.0 )
                  {
                    if ( *(float *)&v2->m_pEM - *(float *)(v6 + v7 - 56) > *(float *)(v6 + v7 + 20) )
                    {
LABEL_24:
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v3) + v6 + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v3) + v6 + 16) = v2->m_pEM;
                      v2[1].m_pEM = pTypea;
                      *(_DWORD *)&v2[1].m_bIdle = v17;
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
                *(_DWORD *)&v2[1].m_bIdle = v5;
                v2[1].m_pEM = pTypea;
LABEL_25:
// [VFTABLE] (*((void ( **)(CEffObj *, _DWORD, _DWORD, _DWORD))v2->__vftable + 1))(
// [VFTABLE]   v2,
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v4 + v6),
// [VFTABLE]   *(_DWORD *)(*(_DWORD *)v4 + v6 + 4),
// [VFTABLE]   0);
                break;
              case 4:
                v8 = 0;
// [VFTABLE] v9 = (char *)v2[1].__vftable + v3;
                v10 = v9[1];
                if ( v10 <= 0 )
                {
LABEL_16:
                  v12 = *((_DWORD *)v4 + 1);
                  *((_DWORD *)v4 + 3) = 4;
                  v13 = 9 * v12;
                  LOBYTE(v12) = v4[149];
                  *((_DWORD *)v4 + 5) = *(_DWORD *)(*(_DWORD *)v4 + 8 * v13 - 12);
                  if ( (_BYTE)v12 == 1 )
                  {
                    v14 = 0;
// [VFTABLE] *((_BYTE *)v2[1].__vftable + v3 + 148) = 0;
                    if ( *(int *)&v2[2].m_bIdle > 0 )
                    {
                      v15 = 0;
                      do
                      {
                        ++v14;
                        v15 += 72;
// [VFTABLE] *(_BYTE *)(*(_DWORD *)((char *)v2[1].__vftable + v3) + v15 - 8) = 0;
                      }
                      while ( v14 < *(_DWORD *)&v2[2].m_bIdle );
                    }
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v3 + 4) = 0;
// [VFTABLE] --v2[2].__vftable;
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
          while ( v17 < *(_DWORD *)&v2[2].m_bIdle );
        }
      }
    }
LABEL_32:
    v3 += 152;
    pTypea = (CEffMgr *)((char *)pTypea + 1);
  }
  while ( (int)pTypea < (int)v2[2].m_pEM );
  this = v18;
LABEL_34:
  result = *((_DWORD *)this + 9);
  if ( result <= 0 )
    this->m_bIdle = 1;
  return result;
}

// 0x004D51B0
void CEffSParticle::Init(int *pType)
{
  CEffObj *v2; // ebx
  int v3; // ecx
  int v4; // edx
  char *vftable; // esi
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

  v2 = this + 1;
  v3 = *((_DWORD *)this + 10);
  v4 = 0;
  if ( v3 > 0 )
  {
// [VFTABLE] vftable = (char *)v2[1].__vftable;
    for ( i = vftable + 148; *i; i += 152 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = 152 * v4;
    *(_DWORD *)&vftable[v7 + 12] = 2;
// [VFTABLE] *((_BYTE *)v2[1].__vftable + v7 + 148) = 1;
// [VFTABLE] *((_BYTE *)v2[1].__vftable + v7 + 149) = 1;
    v8 = ++g_nEffSParticleCount;
    if ( !g_nEffSParticleCount || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nEffSParticleCount = 1;
    }
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 16) = v8;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 4) = 0;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 8) = 0;
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 20) = 0;
    if ( pType )
// [VFTABLE] qmemcpy((char *)v2[1].__vftable + v7 + 24, pType, 0x7Cu);
    else
// [VFTABLE] memset((char *)v2[1].__vftable + v7 + 24, 0, 0x7Cu);
// [VFTABLE] ++v2[2].__vftable;
    if ( v4 != -1 )
    {
      v9 = *(_DWORD *)&v2[2].m_bIdle;
      v10 = 0;
      if ( v9 > 0 )
      {
// [VFTABLE] v11 = *((_DWORD *)v2[1].__vftable + 38 * v4);
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
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++g_nEffSParticleCount;
        if ( !g_nEffSParticleCount || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          g_nEffSParticleCount = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v2[1].__vftable + v7 + 4);
      }
LABEL_22:
      v15 = *(_DWORD *)&v2[2].m_bIdle;
      v16 = 0;
      if ( v15 > 0 )
      {
// [VFTABLE] v17 = *((_DWORD *)v2[1].__vftable + 38 * v4);
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
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++g_nEffSParticleCount;
        if ( !g_nEffSParticleCount || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          g_nEffSParticleCount = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v2[1].__vftable + v7 + 4);
      }
LABEL_31:
      ((CEffSParticle *)v2)->Render(v4, 0 /* TODO: (int)CEffSParticle::Attach */, 0, 0, pType[18], pType[19]);
// [VFTABLE] *(_DWORD *)((char *)v2[1].__vftable + v7 + 12) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v7) + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v2[1].__vftable + v7) + 16) = v2->m_pEM;
    }
  }
}

// 0x004D53E0
int CEffSParticle::Attach(int nVal)
{
  int v3; // edi
  int v4; // ebx
  CCBSystem *m_pCBSystem; // ecx
  float m_AbsDeltaTime; // [esp+0xC] [ebp-0xC]
  float m_fAbsTimeFund; // [esp+0x10] [ebp-0x8]
  float formal; // [esp+0x14] [ebp-0x4]
  float formala; // [esp+0x14] [ebp-0x4]

  v3 = *((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7);
  v4 = *(_DWORD *)v3 + 72 * *((_DWORD *)this + 8);
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  if ( (g_bScriptFlag & 1) == 0 )
  {
    g_bScriptFlag |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  if ( !*(_BYTE *)(v4 + 65) )
  {
    *(float *)(v4 + 56) = this->m_pEM->m_pCBSystem->m_fAbsTimeFund;
    if ( *(_BYTE *)(v3 + 113) )
      *(float *)(v4 + 44) = this->m_pEM->m_pCBSystem->m_fTimeScale;
    if ( *(_BYTE *)(v3 + 114) )
      ((CCBSystem *)this->m_pEM->m_pCBSystem)->ProcAI(*(float *)(v3 + 24));
    *(_BYTE *)(v4 + 65) = 1;
  }
  m_pCBSystem = this->m_pEM->m_pCBSystem;
  m_AbsDeltaTime = m_pCBSystem->m_AbsDeltaTime;
  m_fAbsTimeFund = m_pCBSystem->m_fAbsTimeFund;
  if ( m_fAbsTimeFund - *(float *)(v4 + 56) > *(float *)(v3 + 28) )
  {
    formal = m_pCBSystem->m_fTimeScale + m_AbsDeltaTime * *(float *)(v3 + 32);
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( formal <= 20.0 )
    {
      if ( formal < 0.0 )
        formal = 0.0;
      ((CCBSystem *)this->m_pEM->m_pCBSystem)->ProcAI(formal);
    }
    else
    {
      ((CCBSystem *)this->m_pEM->m_pCBSystem)->ProcAI(20.0);
    }
  }
  if ( m_fAbsTimeFund - *(float *)(v4 + 56) > *(float *)(v3 + 36) )
  {
    formala = this->m_pEM->m_pCBSystem->m_fTimeScale + m_AbsDeltaTime * *(float *)(v3 + 56);
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    if ( formala <= 20.0 )
    {
      if ( formala < 0.0 )
        formala = 0.0;
      ((CCBSystem *)this->m_pEM->m_pCBSystem)->ProcAI(formala);
    }
    else
    {
      ((CCBSystem *)this->m_pEM->m_pCBSystem)->ProcAI(20.0);
    }
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || m_fAbsTimeFund - *(float *)(v4 + 56) >= *(float *)(v4 + 24) )
  {
    if ( *(_BYTE *)(v3 + 113) )
      ((CCBSystem *)this->m_pEM->m_pCBSystem)->ProcAI(1.0);
    *(_DWORD *)(v4 + 8) = 4;
  }
  return 0;
}

// 0x004D5620
int * CEffSParticle::Update(float fCurTime)
{
  int *result; // eax

  switch ( LODWORD(fCurTime) )
  {
    case 0:
      result = &pTarget.m_nTargetType + 53;
      break;
    case 1:
    case 3:
      result = &pTarget.m_nTargetType + 50;
      break;
    case 2:
    case 4:
      result = &pTarget.m_nTargetType + 48;
      break;
    case 9:
      result = &g_EffEditorState;
      break;
    case 0x14:
      result = (int *)&g_pszEditorDesc;
      break;
    case 0x16:
      result = &pTarget.m_nTargetType + 43;
      break;
    case 0x17:
      result = &pTarget.m_nTargetType + 37;
      break;
    default:
      result = &g_EffCylinderEditorData;
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

  v8 = *((_DWORD *)this + 8);
  v9 = 0;
  if ( v8 <= 0 )
    return -1;
  v10 = *(_DWORD *)(*((_DWORD *)this + 3) + 152 * nVal);
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
  v14 = ++g_nEffSParticleCount;
  if ( !g_nEffSParticleCount || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    g_nEffSParticleCount = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = nVal4;
  v13[6] = nVal5;
  if ( p_DWORD )
  {
    v15 = v13 + 7;
    *v15 = *p_DWORD;
    v15[1] = p_DWORD[1];
    v15[2] = p_DWORD[2];
    v15[3] = p_DWORD[3];
  }
  ++*(_DWORD *)(*((_DWORD *)this + 3) + 152 * nVal + 4);
  return v9;
}

// 0x004D5790
void * CEffSParticle::SetTimeScale(CEffSParticle *Block, char fTimeScale)
{
  int v4; // eax
  int v5; // ebx
  int v6; // edi

  v4 = *((_DWORD *)this + 7);
  if ( v4 || *((_DWORD *)this + 8) )
  {
    v5 = 0;
    if ( v4 > 0 )
    {
      v6 = 0;
      do
      {
        operator delete(*(void **)(*((_DWORD *)this + 3) + v6));
        ++v5;
        *(_DWORD *)(*((_DWORD *)this + 3) + v6) = 0;
        v6 += 152;
      }
      while ( v5 < *((_DWORD *)this + 7) );
    }
    operator delete(*((void **)this + 3));
    *((_DWORD *)this + 3) = 0;
    *((_DWORD *)this + 7) = 0;
    *((_DWORD *)this + 8) = 0;
  }
  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004D5860
char * CEffSParticle::CreateTask(char p)
{
  char *v2; // esi

  v2 = (char *)this - 12;
  ((CEffSParticle *)((char *)this - 12))->_CEffSParticle();
  if ( (p & 1) != 0 )
    operator delete(v2);
  return v2;
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
// [VFTABLE] v9 = *((_DWORD *)&this->__vftable + HIBYTE(i));
    v10 = v7 | (i << 8);
    v7 = v4[1];
    i = v9 ^ v10;
  }
  return (const char *)~i;
}
