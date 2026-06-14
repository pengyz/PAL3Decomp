#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffShock.h"

// Forward declarations for unnamed functions
int sub_4D3870(...);
void __cdecl todo_401800(void);
int todo_408BD0(...);

// 0x004D3280
const char * CEffShock::GetEditorTaskDescription(int nIndex)
{
  this->m_pEM = 0;
  this->m_bIdle = 0;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 7) = -1;
  *((_DWORD *)this + 8) = -1;
  *((_DWORD *)this + 9) = 0;
  *((_DWORD *)this + 10) = 0;
  *((_DWORD *)this + 11) = 0;
  return (const char *)this;
}

// 0x004D3910
CEffShock::CEffShock(CEffShock *thisa)
{
  CEffShock *v2; // eax

  v2 = (CEffShock *)operator new(0x10B0u);
  if ( v2 )
  sub_4D3870(v2, thisa);
  else
  0;
}

// 0x004D4570
int CEffShock::UpdateSegment(int nVal)
{
  _DWORD *v3; // ecx
  int v4; // edi
  void *v6; // [esp+0x0] [ebp-0x8]

  v3 = (_DWORD *)(*((_DWORD *)this + 6) + 152 * *((_DWORD *)this + 7));
  v4 = *v3 + 72 * *((_DWORD *)this + 8);
  if ( !*(_BYTE *)(v4 + 65) )
  {
    this->StartShock(v3[26]);
    *(_BYTE *)(v4 + 65) = 1;
  }
  todo_408BD0(v6);
  if ( *(_BYTE *)(v4 + 66) == 1 || *((float *)this + 4) - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004D45D0
void CEffShock::StartShock(int nRequireLoops)
{
  int i; // edi
  tagShockUnit *m_pShock; // ecx
  double v5; // st7
  float *p_fRequireLoops; // eax
  int v7; // edx
  int j; // edi
  int v9; // ecx
  double v10; // st7
  tagShockUnit *v11; // eax
  float v12; // [esp+0x8] [ebp-0x4]
  int nRequireLoopsa; // [esp+0x10] [ebp+0x4]

  for ( i = 0; i < this->m_nMaxGeomQuad; *p_fRequireLoops = v5 )
  {
    if ( (g_bScriptFlag & 1) == 0 )
    {
      g_bScriptFlag |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    ++g_nRandCount;
    g_nRandSeed = 214013 * g_nRandSeed + 2531011;
    this->m_pShock[i].fCurFrame = (double)((((int)g_nRandSeed >> 16) & 0x7FFF)
                                         % (100 * (unsigned __int8)this->m_byMaxFrame))
                                * 0.0099999998;
    v12 = (float)nRequireLoops;
    this->m_pShock[i].fRequireLoops = v12;
    m_pShock = this->m_pShock;
    v5 = m_pShock[i].fCurFrame + m_pShock[i].fRequireLoops;
    p_fRequireLoops = &m_pShock[i++].fRequireLoops;
  }
  v7 = 0;
  for ( j = 0; j < this->m_nNodeOfShock; ++j )
  {
    v9 = 0;
    for ( nRequireLoopsa = 0;
          v9 < this->m_nCascade;
          v11->fRequireLoops = v10 * this->m_fSpeedOfDisappear + v11->fRequireLoops )
    {
      v10 = (double)nRequireLoopsa;
      nRequireLoopsa = ++v9;
      v11 = &this->m_pShock[v7++];
    }
  }
}

// 0x004D49F0
void CEffShock::CreateGeom(int nVal, int nVal2)
{
  int v3; // ebx
  float *p_eu; // edi
  int v6; // esi
  int v7; // ecx
  float *v8; // eax
  double v9; // st7
  double v10; // st7
  double v11; // st6
  float v12; // [esp+0x0] [ebp-0x14]
  float v13; // [esp+0x4] [ebp-0x10]
  int v14; // [esp+0x8] [ebp-0xC]
  float v15; // [esp+0x8] [ebp-0xC]
  float v16; // [esp+0xC] [ebp-0x8]
  float v17; // [esp+0x10] [ebp-0x4]
  int nVala; // [esp+0x18] [ebp+0x4]

  v3 = 0;
  v13 = (float)nVal;
  v14 = 0;
  v12 = (float)nVal2;
  if ( nVal2 > 0 )
  {
    p_eu = &this->m_DefaultUVSet[0].eu;
    v6 = 16 * nVal;
    do
    {
      v7 = 0;
      nVala = 0;
      if ( nVal > 0 )
      {
        v8 = p_eu;
        p_eu = (float *)((char *)p_eu + v6);
        v9 = (double)v14 / v12;
        v16 = 1.0 / v12;
        v15 = 1.0 - (v9 + v16);
        v10 = 1.0 - v9;
        do
        {
          v8 += 4;
          ++v7;
          v11 = (double)nVala / v13;
          nVala = v7;
          *(v8 - 6) = v11;
          v17 = 1.0 / v13;
          *(v8 - 4) = v11 + v17;
          *(v8 - 5) = v15;
          *(v8 - 3) = v10;
        }
        while ( v7 < nVal );
      }
      v14 = ++v3;
    }
    while ( v3 < nVal2 );
  }
}

// 0x004D4B50
void CEffShock::LoadTexture(
        
        int pFileName,
        int nVal,
        int nVal2,
        int *p_DWORD,
        int nVal3,
        int nVal4)
{
  int v8; // ecx
  int v9; // esi
  int v10; // edx
  _BYTE *i; // eax
  int *v12; // edx
  unsigned int v13; // eax
  int *v14; // edx

  v8 = *((_DWORD *)this + 8);
  v9 = 0;
  if ( v8 > 0 )
  {
    v10 = *(_DWORD *)(*((_DWORD *)this + 3) + 152 * pFileName);
    for ( i = (_BYTE *)(v10 + 64); *i; i += 72 )
    {
      if ( ++v9 >= v8 )
        return;
    }
    v12 = (int *)(v10 + 72 * v9);
    memset(v12, 0, 0x48u);
    *((_BYTE *)v12 + 65) = 0;
    *((_BYTE *)v12 + 64) = 1;
    *v12 = nVal;
    v12[1] = nVal2;
    v12[2] = 2;
    v13 = ++g_nEffShockCount;
    if ( !g_nEffShockCount || v13 >= 0x7FFFFFFF )
    {
      v13 = 1;
      g_nEffShockCount = 1;
    }
    v12[3] = v13;
    v12[4] = 0;
    v12[5] = nVal3;
    v12[6] = nVal4;
    if ( p_DWORD )
    {
      v14 = v12 + 7;
      *v14 = *p_DWORD;
      v14[1] = p_DWORD[1];
      v14[2] = p_DWORD[2];
      v14[3] = p_DWORD[3];
    }
    ++*(_DWORD *)(*((_DWORD *)this + 3) + 152 * pFileName + 4);
  }
}
