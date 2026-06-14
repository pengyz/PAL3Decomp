#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffMgr.h"

// Forward declarations for unnamed functions
int sub_4C9550(...);
int sub_4CB3A0(...);
int sub_4CD340(...);
int sub_4D3870(...);
int sub_4D4EA0(...);
int sub_4D5A00(...);
void __cdecl todo_401800(void);

// 0x004B7340
void CEffMgr::UpdateTimedTrigger(float fVal)
{
  double v3; // st7
  bool v4; // zf
  char v5; // al
  tagEffClass v6; // eax
  tagEffClass v7; // eax

  v3 = fVal + *(float *)&this->m_EffClass[21];
  v4 = *(_DWORD *)&this->m_EffClass[16] == 275;
  *(float *)&this->m_EffClass[21] = v3;
  if ( v4 )
  {
    if ( v3 >= 9.5 )
    {
      v7._tail_000[0] = ((CEffMgr *)g_pSceneManager)->Init(275, *(_DWORD *)&this->m_EffClass[18], *(_DWORD *)&this->m_EffClass[19], *(_DWORD *)&this->m_EffClass[20], 0);
      this->m_EffClass[17] = v7;
      this->m_EffClass[21] = 0;
    }
  }
  else
  {
    ((CEffMgr *)g_pSceneManager)->Render(*(_DWORD *)&this->m_EffClass[17]);
    if ( !v5 )
    {
      v6._tail_000[0] = ((CEffMgr *)g_pSceneManager)->Init(*(_DWORD *)&this->m_EffClass[16], *(_DWORD *)&this->m_EffClass[18], *(_DWORD *)&this->m_EffClass[19], *(_DWORD *)&this->m_EffClass[20], 0);
      this->m_EffClass[17] = v6;
    }
  }
}

// 0x004B73D0
int CEffMgr::SetComponent(int nVal)
{
  this->m_EffClass[16] = (tagEffClass)nVal;
  return nVal;
}

// 0x004B73F0
int CEffMgr::SetEffectClass(int nVal, int nVal2, int nVal3)
{
  int result; // eax

  this->m_EffClass[18] = (tagEffClass)nVal;
  this->m_EffClass[19] = (tagEffClass)nVal2;
  this->m_EffClass[20] = (tagEffClass)nVal3;
  LOBYTE(result) = ((CEffMgr *)g_pSceneManager)->Init(*(_DWORD *)&this->m_EffClass[16], *(_DWORD *)&this->m_EffClass[18], nVal2, nVal3, 0);
  this->m_EffClass[17] = (tagEffClass)result;
  this->m_EffClass[21] = 0;
  return result;
}

// 0x004C2F30
int CEffMgr::ProcessEffectPass(int nVal)
{
  float *v3; // edi
  int v4; // ebx
  int nVal2; // [esp+0x0] [ebp-0x20]
  int nVal2a; // [esp+0x0] [ebp-0x20]
  int nVal2b; // [esp+0x0] [ebp-0x20]
  int nVal2c; // [esp+0x0] [ebp-0x20]
  int nVal3; // [esp+0x4] [ebp-0x1C]
  int nVal3a; // [esp+0x4] [ebp-0x1C]
  int nVal3b; // [esp+0x4] [ebp-0x1C]
  int nVal3c; // [esp+0x4] [ebp-0x1C]
  int nVal4; // [esp+0x8] [ebp-0x18]
  int nVal4a; // [esp+0x8] [ebp-0x18]
  int nVal4b; // [esp+0x8] [ebp-0x18]
  int nVal4c; // [esp+0x8] [ebp-0x18]

  v3 = &this->m_pCam->fov + 38 * *(_DWORD *)this->m_EffClass;
  v4 = *(_DWORD *)v3 + 72 * *(_DWORD *)&this->m_EffClass[1];
  if ( !*(_BYTE *)(v4 + 65) )
  {
    if ( v3[6] != 0.0 )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      *(float *)&nVal4 = v3[9] + *(float *)&this->m_EffClass[7];
      *(float *)&nVal3 = v3[8] + *(float *)&this->m_EffClass[6];
      *(float *)&nVal2 = v3[7] + *(float *)&this->m_EffClass[5];
      ((CEffMgr *)this->m_pCBSystem)->Init((int)v3[6], nVal2, nVal3, nVal4, *(_DWORD *)&this->m_EffClass[8]);
    }
    if ( v3[14] != 0.0 )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      *(float *)&nVal4a = v3[18] + *(float *)&this->m_EffClass[7];
      *(float *)&nVal3a = v3[17] + *(float *)&this->m_EffClass[6];
      *(float *)&nVal2a = v3[16] + *(float *)&this->m_EffClass[5];
      ((CEffMgr *)this->m_pCBSystem)->Init((int)v3[14], nVal2a, nVal3a, nVal4a, *(_DWORD *)&this->m_EffClass[8]);
    }
    if ( v3[11] != 0.0 )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      *(float *)&nVal4b = v3[15] + *(float *)&this->m_EffClass[7];
      *(float *)&nVal3b = v3[13] + *(float *)&this->m_EffClass[6];
      *(float *)&nVal2b = v3[12] + *(float *)&this->m_EffClass[5];
      ((CEffMgr *)this->m_pCBSystem)->Init((int)v3[11], nVal2b, nVal3b, nVal4b, *(_DWORD *)&this->m_EffClass[8]);
    }
    if ( v3[20] != 0.0 )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
        atexit(todo_401800);
      }
      *(float *)&nVal4c = v3[23] + *(float *)&this->m_EffClass[7];
      *(float *)&nVal3c = v3[22] + *(float *)&this->m_EffClass[6];
      *(float *)&nVal2c = v3[21] + *(float *)&this->m_EffClass[5];
      ((CEffMgr *)this->m_pCBSystem)->Init((int)v3[20], nVal2c, nVal3c, nVal4c, *(_DWORD *)&this->m_EffClass[8]);
    }
    *(_BYTE *)(v4 + 65) = 1;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_pAdditiveBlend - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004C5350
int CEffMgr::UpdateParticlePositions()
{
  double v1; // st7
  int v3; // edi
  int v4; // eax
  bool v5; // dl
  double v6; // st6
  double v7; // st5
  long double v8; // st4
  double v9; // st4
  long double v10; // st3
  int v11; // eax
  tagEffClass v12; // ecx
  int v13; // ecx
  tagEffClass v14; // ecx
  int v15; // ecx
  double v16; // st4
  double v17; // st4
  double v18; // st4
  double v19; // st3
  double v20; // st2
  float *v21; // ecx
  tagEffClass v22; // ecx
  int v23; // ecx
  double v24; // st7
  int result; // eax
  int v26; // ecx
  double v27; // st7
  float v28; // [esp+0x14] [ebp-0x24]
  float v29; // [esp+0x18] [ebp-0x20]
  float v30; // [esp+0x1C] [ebp-0x1C]
  float v31; // [esp+0x20] [ebp-0x18]
  float v32; // [esp+0x24] [ebp-0x14]
  float v33; // [esp+0x24] [ebp-0x14]
  float v34; // [esp+0x24] [ebp-0x14]
  float v35; // [esp+0x28] [ebp-0x10]
  float v36; // [esp+0x28] [ebp-0x10]
  float v37; // [esp+0x2C] [ebp-0xC]
  float m_fScaleZ; // [esp+0x2C] [ebp-0xC]
  float v39; // [esp+0x30] [ebp-0x8]
  float v40; // [esp+0x30] [ebp-0x8]
  float v41; // [esp+0x34] [ebp-0x4]
  float v42; // [esp+0x34] [ebp-0x4]

  v1 = 0.0;
  v3 = 0;
  v30 = 0.0;
  v4 = (int)this->m_EffClass[21];
  v5 = 1;
  v41 = *(float *)&this->m_EffClass[19] / (double)v4;
  v6 = *(float *)&this->m_EffClass[20];
  v7 = 0.0;
  v8 = sin(0.0);
  v32 = v8;
  v9 = v8 * *(float *)&this->m_EffClass[24];
  v10 = cos(0.0);
  v28 = v10 * *(float *)&this->m_EffClass[24];
  v29 = v32 * *(float *)&this->m_EffClass[25];
  v31 = v10 * *(float *)&this->m_EffClass[25];
  if ( v4 > 0 )
  {
    v11 = 0;
    do
    {
      v12 = this->m_EffClass[5];
      *(float *)(*(_DWORD *)&v12 + v11 + 36) = v9;
      v13 = *(_DWORD *)&v12 + v11 + 36;
      *(float *)(v13 + 8) = v28;
      *(float *)(v13 + 4) = v6;
      v14 = this->m_EffClass[5];
      *(float *)(*(_DWORD *)&v14 + v11) = v29;
      v15 = v11 + *(_DWORD *)&v14;
      *(float *)(v15 + 4) = v30;
      v1 = v1 + v41;
      *(float *)(v15 + 8) = v31;
      v39 = v41 * *(float *)&this->m_EffClass[26] + *(float *)&this->m_EffClass[24];
      v16 = v41 * *(float *)&this->m_EffClass[27];
      *(float *)&this->m_EffClass[24] = v39;
      v33 = v16 + *(float *)&this->m_EffClass[25];
      *(float *)&this->m_EffClass[25] = v33;
      v6 = v6 + v41 * *(float *)&this->m_EffClass[28];
      v7 = v7 + v41 * *(float *)&this->m_EffClass[29];
      v30 = v7;
      v37 = sin(v1 * 0.017453292);
      v35 = cos(v1 * 0.017453292);
      v17 = v39;
      if ( v5 )
      {
        v18 = v17 - *(float *)&this->m_EffClass[22];
        v40 = v18;
        v9 = v18 * v37;
        v19 = v40 * v35;
        v28 = v19;
        v20 = v33 - *(float *)&this->m_EffClass[23];
        v29 = v20 * v37;
      }
      else
      {
        v9 = v17 * v37;
        v19 = v39 * v35;
        v28 = v19;
        v29 = v33 * v37;
        v20 = v33;
      }
      v21 = (float *)(*(_DWORD *)&this->m_EffClass[5] + v11 + 24);
      v31 = v20 * v35;
      v5 = !v5;
      *v21 = v9;
      ++v3;
      v21[1] = v6;
      v21[2] = v19;
      v22 = this->m_EffClass[5];
      *(float *)(*(_DWORD *)&v22 + v11 + 12) = v29;
      v23 = *(_DWORD *)&v22 + v11 + 12;
      v11 += 68;
      *(float *)(v23 + 8) = v31;
      *(float *)(v23 + 4) = v7;
      *(float *)(*(_DWORD *)&this->m_EffClass[5] + v11 - 20) = this->m_fScaleZ;
      *(_DWORD *)(*(_DWORD *)&this->m_EffClass[5] + v11 - 12) = *(_DWORD *)&this->m_szEffectPath[4];
      *(_DWORD *)(*(_DWORD *)&this->m_EffClass[5] + v11 - 16) = *(_DWORD *)this->m_szEffectPath;
      *(_DWORD *)(*(_DWORD *)&this->m_EffClass[5] + v11 - 8) = *(_DWORD *)&this->m_szEffectPath[8];
      *(tagEffClass *)(*(_DWORD *)&this->m_EffClass[5] + v11 - 4) = this->m_EffClass[12];
    }
    while ( v3 < *(_DWORD *)&this->m_EffClass[21] );
  }
  m_fScaleZ = this->m_fScaleZ;
  v36 = *(float *)this->m_szEffectPath;
  v34 = *(float *)&this->m_szEffectPath[8];
  v42 = *(float *)&this->m_EffClass[30]
      / (double)(int)this->m_EffClass[21]
      * (*(float *)&this->m_szEffectPath[4] - m_fScaleZ);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  v24 = (double)(int)v36;
  if ( v24 > 1.0 )
  {
    v36 = v36 - v24;
    v34 = v34 - v24;
  }
  result = (int)this->m_EffClass[21];
  v26 = 0;
  if ( result > 0 )
  {
    v27 = m_fScaleZ;
    result = 0;
    do
    {
      ++v26;
      *(float *)(*(_DWORD *)&this->m_EffClass[5] + result + 48) = v27;
      v27 = v27 + v42;
      result += 68;
      *(float *)(*(_DWORD *)&this->m_EffClass[5] + result - 12) = v27;
      *(float *)(*(_DWORD *)&this->m_EffClass[5] + result - 16) = v36;
      *(float *)(*(_DWORD *)&this->m_EffClass[5] + result - 8) = v34;
    }
    while ( v26 < *(_DWORD *)&this->m_EffClass[21] );
  }
  return result;
}

// 0x004C7E60
int CEffMgr::EmitParticles()
{
  int v1; // ebx
  int result; // eax
  int v4; // ebx
  __int64 v5; // rax
  int v6; // edi
  signed int v7; // ecx
  int v8; // ecx
  int v9; // edx
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  unsigned int v13; // ecx
  int v14; // ecx
  float *v15; // eax
  double v16; // st7
  bool v17; // cc
  float v18; // [esp+0x14] [ebp-0x28]
  int v19; // [esp+0x1C] [ebp-0x20]
  int v20; // [esp+0x20] [ebp-0x1C]
  int v21; // [esp+0x24] [ebp-0x18]
  int v22; // [esp+0x28] [ebp-0x14]
  float v23; // [esp+0x2C] [ebp-0x10]
  float v24; // [esp+0x2C] [ebp-0x10]
  float v25; // [esp+0x2C] [ebp-0x10]
  float v26; // [esp+0x30] [ebp-0xC]
  float v27; // [esp+0x30] [ebp-0xC]
  float v28; // [esp+0x34] [ebp-0x8]
  float v29; // [esp+0x38] [ebp-0x4]

  v1 = 0;
  v21 = 0;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  v19 = (int)this->m_EffClass[24];
  v29 = *(float *)&this->m_EffClass[25];
  if ( v19 <= 0 )
    v19 = 2;
  if ( *(float *)&this->m_EffClass[29] < 0.0 )
    this->m_EffClass[29] = 0;
  result = (int)this->m_EffClass[20];
  v20 = 0;
  if ( result > 0 )
  {
    do
    {
      v22 = 0;
      if ( *(_DWORD *)&this->m_EffClass[21] > 0 )
      {
        v4 = 24 * v1;
        do
        {
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
            atexit(todo_401800);
          }
          v5 = v22 - *(_DWORD *)&this->m_EffClass[20] / 2;
          v18 = (float)v19;
          v23 = v18
              - (double)(int)((HIDWORD(v5) ^ v5) - HIDWORD(v5))
              * (double)(int)abs32(v20 - *(_DWORD *)&this->m_EffClass[21] / 2)
              * *(float *)&this->m_EffClass[29];
          v6 = (int)v23;
          if ( (double)v6 < v29 )
          {
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v6 = (int)v29;
          }
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
            atexit(todo_401800);
          }
          ++g_nRandCount;
          v7 = 214013 * g_nRandSeed + 2531011;
          g_nRandSeed = v7;
          v28 = (float)(v6 / 2);
          v26 = (double)(((v7 >> 16) & 0x7FFF) % v6) - v28;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
            atexit(todo_401800);
            v7 = g_nRandSeed;
          }
          ++g_nRandCount;
          v8 = 214013 * v7 + 2531011;
          g_nRandSeed = v8;
          v24 = (double)(((v8 >> 16) & 0x7FFF) % v6) - v28;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
            atexit(todo_401800);
            v8 = g_nRandSeed;
          }
          ++g_nRandCount;
          g_nRandSeed = 214013 * v8 + 2531011;
          v9 = (((int)g_nRandSeed >> 16) & 0x7FFF) % v6;
          v10 = (float *)(*(_DWORD *)&this->m_EffClass[6] + v4);
          *v10 = v26;
          v10[1] = v24;
          v10[2] = (double)v9 - v28;
          if ( ((gbVec3D *)(*(_DWORD *)&this->m_EffClass[6] + v4))->Length() < (double)v29 )
          {
            ((gbVec3D *)(*(_DWORD *)&this->m_EffClass[6] + v4))->Normalize();
            v11 = (float *)(*(_DWORD *)&this->m_EffClass[6] + v4);
            *v11 = v29 * *v11;
            v11[1] = v29 * v11[1];
            v11[2] = v29 * v11[2];
          }
          v12 = (float *)(*(_DWORD *)&this->m_EffClass[6] + v4);
          *v12 = *(float *)&this->m_EffClass[26] + *v12;
          v12[1] = *(float *)&this->m_EffClass[27] + v12[1];
          v12[2] = v12[2] + *(float *)&this->m_EffClass[28];
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
            atexit(todo_401800);
          }
          ++g_nRandCount;
          g_nRandSeed = 214013 * g_nRandSeed + 2531011;
          v13 = g_nRandSeed;
          v27 = ((double)((((int)g_nRandSeed >> 16) & 0x7FFF) % 160) - 80.0) * 16.0;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
            atexit(todo_401800);
            v13 = g_nRandSeed;
          }
          ++g_nRandCount;
          v14 = 214013 * v13 + 2531011;
          g_nRandSeed = v14;
          v25 = ((double)(((v14 >> 16) & 0x7FFF) % 160) - 80.0) * 16.0;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
            atexit(todo_401800);
            v14 = g_nRandSeed;
          }
          ++g_nRandCount;
          g_nRandSeed = 214013 * v14 + 2531011;
          v15 = (float *)(v4 + *(_DWORD *)&this->m_EffClass[6] + 12);
          v4 += 24;
          v16 = (double)((((int)g_nRandSeed >> 16) & 0x7FFF) % 160) - 80.0;
          *v15 = v27;
          v15[1] = v25;
          v15[2] = v16 * 16.0;
          v17 = ++v22 < *(_DWORD *)&this->m_EffClass[21];
          ++v21;
        }
        while ( v17 );
        v1 = v21;
      }
      result = ++v20;
    }
    while ( v20 < *(_DWORD *)&this->m_EffClass[20] );
  }
  this->m_fScaleX = 3.52;
  return result;
}

// 0x004CCEF0
int CEffMgr::UpdateEffect(float fVal, int nVal)
{
  CCBSystem *m_pCBSystem; // eax
  int result; // eax
  int v6; // edi
  int v7; // ebx
  tagEffClass v8; // ecx
  double v9; // st7
  float *v10; // eax
  double v11; // st6
  float *v12; // eax
  tagEffClass v13; // eax
  double v14; // st7
  double v15; // st6
  float *v16; // eax
  float v17; // [esp+0x4] [ebp-0x28]
  float v18; // [esp+0x8] [ebp-0x24]
  float v19; // [esp+0x10] [ebp-0x1C]
  float v20; // [esp+0x14] [ebp-0x18]
  float v21; // [esp+0x1C] [ebp-0x10]
  float v22; // [esp+0x20] [ebp-0xC]
  float v23; // [esp+0x24] [ebp-0x8]
  int v24; // [esp+0x24] [ebp-0x8]
  int v25; // [esp+0x28] [ebp-0x4]
  float fVala; // [esp+0x34] [ebp+0x8]

  m_pCBSystem = this->m_pCBSystem;
  *(float *)&this->m_EffClass[28] = fVal + *(float *)&this->m_EffClass[28];
  fVala = *(float *)&m_pCBSystem->m_Thread[490].bValid * 0.02;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  v23 = *(float *)&this->m_EffClass[28] / fVala;
  result = (int)v23;
  *(float *)&this->m_EffClass[28] = *(float *)&this->m_EffClass[28] - (double)result * fVala;
  if ( result > 0 )
  {
    v24 = (int)v23;
    do
    {
      v6 = 0;
      v25 = 0;
      if ( *(_DWORD *)&this->m_EffClass[22] > 0 )
      {
        v7 = 0;
        do
        {
          v8 = this->m_EffClass[7];
          v9 = *(float *)(v6 + *(_DWORD *)&v8 + 36) - *(float *)(v6 + *(_DWORD *)&v8);
          v10 = (float *)(v6 + *(_DWORD *)&v8);
          v21 = *(float *)(v6 + *(_DWORD *)&v8 + 40) - *(float *)(v6 + *(_DWORD *)&v8 + 4);
          v11 = *(float *)(v6 + *(_DWORD *)&v8 + 44) - *(float *)(v6 + *(_DWORD *)&v8 + 8);
          v10[7] = v21;
          v22 = v11;
          v10[6] = v9;
          v10[8] = v22;
          v12 = (float *)(v6 + *(_DWORD *)&this->m_EffClass[7]);
          v19 = fVala * v12[7];
          v20 = fVala * v12[8];
          v12[3] = fVala * v12[6] + v12[3];
          v12[4] = v19 + v12[4];
          v12[5] = v20 + v12[5];
          v13 = this->m_EffClass[7];
          v14 = fVala * *(float *)(*(_DWORD *)&v13 + v6 + 12);
          v15 = fVala * *(float *)(*(_DWORD *)&v13 + v6 + 16);
          v16 = (float *)(v6 + *(_DWORD *)&v13);
          v17 = v15;
          v18 = fVala * v16[5];
          *v16 = v14 + *v16;
          v16[1] = v17 + v16[1];
          v16[2] = v18 + v16[2];
          sub_4CD340(*(_DWORD *)&this->m_EffClass[7] + v6, LODWORD(fVala));
          v6 += 48;
          v7 += 56;
          ++v25;
        }
        while ( v25 < *(_DWORD *)&this->m_EffClass[22] );
      }
      result = --v24;
    }
    while ( v24 );
  }
  return result;
}

// 0x004CDC50
char CEffMgr::SetEffectsTimeScale(int nVal)
{
  CEffObj **p_pEffect; // esi
  int v3; // ebx
  char result; // al

  *(_DWORD *)&this->m_sz5D8C3C[1848] = nVal;
  p_pEffect = &this->m_EffTable[92].pEffect;
  v3 = 2048;
  do
  {
    result = *((_BYTE *)p_pEffect - 4);
    if ( result )
    {
      if ( *(p_pEffect - 4) == (CEffObj *)-211379188 )
// [VFTABLE] result = (*((int ( **)(CEffObj *, int))(*p_pEffect)->__vftable + 11))(*p_pEffect, nVal);
      if ( *(p_pEffect - 4) == (CEffObj *)1140548963 )
// [VFTABLE] result = (*((int ( **)(CEffObj *, int))(*p_pEffect)->__vftable + 11))(*p_pEffect, nVal);
    }
    p_pEffect += 5;
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x004CDCA0
int CEffMgr::CreateEffect(int nVal, int nVal2, int nVal3, int nVal4, int nVal5)
{
  int v7; // eax
  int v8; // ebp
  int v9; // ebx
  int v10; // esi
  tagEffObj *v11; // eax
  int v12; // ebp
  _BYTE *p_bValid; // eax
  char *pEffObj; // edi
  char *v16; // eax
  char *v17; // esi
  char v18; // al
  int v19; // edx
  void ( ***v20)(_DWORD, int); // ecx
  int EffSlot; // [esp+0x14] [ebp-0x8]
  int v22; // [esp+0x18] [ebp-0x4]

  v7 = 35 * this->FindEffByID(nVal);
  v8 = *(_DWORD *)&g_EffTable[8 * v7];
  v9 = 8 * v7 + 24433456;
  v22 = v8;
  EffSlot = this->FindEffSlot(v8);
  v10 = 0;
  v11 = &this->m_EffTable[92];
  do
  {
    if ( v11->dwTypeNameCRC == nVal && v11->dwClassNameCRC == v8 && v11->bValid && v11->bIdle && v11->pEffect )
    {
      this->m_EffTable[v10 + 92].dwRunGroupID = nVal2;
      pEffObj = (char *)this + 20 * v10;
      (*(void ( **)(_DWORD, int, int, int, int))(**((_DWORD **)pEffObj + 587) + 8))(
        *((_DWORD *)pEffObj + 587),
        v9,
        nVal3,
        nVal4,
        nVal5);
      pEffObj[2345] = 0;
      return v10;
    }
    ++v10;
    ++v11;
  }
  while ( v10 < 2048 );
LABEL_8:
  v12 = 0;
  p_bValid = &this->m_EffTable[92].bValid;
  while ( *p_bValid )
  {
    ++v12;
    p_bValid += 20;
    if ( v12 >= 2048 )
    {
      ((void(*)(void))0)(this);
      if ( *(int *)&this->m_sz5D8C3C[1832] >= 2048 )
      {

        if ( *(int *)&this->m_sz5D8C3C[1832] >= 2048 )
          return -1;
      }
      goto LABEL_8;
    }
  }
  v16 = (char *)this + 72 * EffSlot;
  v17 = (char *)this + 20 * v12;
  if ( v16[89] )
  {
    *((_DWORD *)v17 + 587) = (*(int ( **)(_DWORD))(**((_DWORD **)v16 + 24) + 28))(*((_DWORD *)v16 + 24));
    v17[2346] = 0;
  }
  else
  {
    *((_DWORD *)v17 + 587) = *((_DWORD *)v16 + 24);
    v17[2346] = 1;
    v16[89] = 1;
  }
  ++*(_DWORD *)&this->m_sz5D8C3C[1832];
  v17[2344] = 1;
  *(_DWORD *)(*((_DWORD *)v17 + 587) + 4) = this;
  *((_DWORD *)v17 + 583) = v22;
  *((_DWORD *)v17 + 584) = nVal;
  this->m_EffTable[v12 + 92].dwRunGroupID = nVal2;
  v17[2345] = 0;
  v18 = (*(int ( **)(_DWORD, int))(**((_DWORD **)v17 + 587) + 4))(*((_DWORD *)v17 + 587), v9);
  v19 = **((_DWORD **)v17 + 587);
  if ( !v18 )
  {
    (*(void (**)(void))(v19 + 12))();
    if ( !v17[2346] )
    {
      v20 = (void ( ***)(_DWORD, int))*((_DWORD *)v17 + 587);
      if ( v20 )
        (**v20)(v20, 1);
      *((_DWORD *)v17 + 587) = 0;
    }
    v17[2344] = 0;
    *((_DWORD *)v17 + 583) = 0;
    *((_DWORD *)v17 + 584) = 0;
    v17[2345] = 0;
    --*(_DWORD *)&this->m_sz5D8C3C[1832];
    return -1;
  }
  (*(void ( **)(int, int, int, int))(v19 + 8))(v9, nVal3, nVal4, nVal5);
  return v12;
}

// 0x004CDFD0
int CEffMgr::FindEffSlot(int nVal)
{
  int result; // eax
  tagEffClass *i; // ecx

  result = 0;
  for ( i = &this->m_EffClass[16]; !i[-1]._tail_000[0] || *i != nVal; i += 18 )
  {
    if ( ++result >= 32 )
      return -1;
  }
  return result;
}

// 0x004CE000
int CEffMgr::FindEffByID(int nVal)
{
  int result; // eax
  char *v3; // ecx

  result = 0;
  v3 = &g_EffTable[36];
  while ( !v3[176] || *(_DWORD *)v3 != nVal )
  {
    v3 += 280;
    ++result;
    if ( (int)v3 >= (int)&g_EffTableEnd )
      return -1;
  }
  return result;
}

// 0x004CE100
CEffMgr::CEffMgr()
{
  gbVFile *v1; // esi
  void *v2; // ebx
  char *v3; // eax
  char *v4; // ebp
  OpenBaseFile v5; // [esp+0x30] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x34] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x434] [ebp-0x40C] BYREF
  int v8; // [esp+0x83C] [ebp-0x4]

  if ( !g_nCEffMgr_17A7B50 )
  {
    v8 = 0;
    v1 = ((gbVFileSystem *)g_pVFileSys)->OpenFile((const char *)&pTarget.m_nTargetSize + 4, 0x201u);
    if ( !v1 )
    {
      qmemcpy(
        pExceptionObject,
        ((Logger *)&ArgList)->FormatException((char *)&pTarget.m_fSoundTimeout, (char *)&pTarget.m_nTargetId, 447),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    v2 = malloc(0x2C047u);
    v3 = (char *)malloc((size_t)&g_nLoadBufferSize);
    v4 = v3;
    if ( !v2 || !v3 )
      goto LABEL_8;
    ((gbVFileSystem *)g_pVFileSys)->Seek(v1, 0, 1);
    ((gbVFileSystem *)g_pVFileSys)->Read(v2, 0x2C047u, v1);
    ((gbVFileSystem *)g_pVFileSys)->CloseFile(v1);
    if ( (int *)((CPK *)(&g_PAL3.m_nMeteorChainCount + 2))->DeCompress(v4, v2, 0x2C047u) != &g_nLoadBufferSize )
    {
      free(v2);
      free(v4);
LABEL_8:
      v8 = -1;
      return;
    }
    qmemcpy(g_EffTable, v4, sizeof(g_EffTable));
    qmemcpy(&g_nSaveSlot0, v4 + 370720, 0x8834C0u);
    free(v2);
    free(v4);
    g_nCEffMgr_17A7B50 = 1;
    v8 = -1;
  }
}

// 0x004CE2A0
void CEffMgr::_CEffMgr()
{
  FILE *v1; // eax
  FILE *v2; // esi
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x800] BYREF
  char ArgList; // [esp+0x404] [ebp-0x400] BYREF

  v1 = fopen((const char *)&pTarget.m_pfnStageSetup + 28, Mode);
  v2 = v1;
  if ( !v1 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException((char *)&pTarget.m_nTargetSize + 24, (char *)&pTarget.m_nTargetId, 521),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  fseek(v1, 0, 0);
  fwrite(g_EffTable, 0x5A820u, 1u, v2);
  fwrite(&g_nSaveSlot0, (size_t)&g_nSaveDataSize, 1u, v2);
  fclose(v2);
}

// 0x004CE340
bool CEffMgr::Init(int nVal, int nVal2, int nVal3, int nVal4, int nVal5)
{
  int v6; // eax
  int v7; // ebx
  int *v8; // esi
  int Effect; // edi
  int v10; // ebp
  int v13; // [esp+0x10] [ebp-0xC]
  int v15; // [esp+0x18] [ebp-0x4]
  int *nVal5a; // [esp+0x30] [ebp+0x14]

  v13 = nVal5;
  if ( !nVal5 )
  {
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v6 = g_nCEffect_1895980;
    if ( g_nCEffect_1895980 == -1 )
      v6 = 1;
    v13 = v6;
    g_nCEffect_1895980 = v6 + 1;
  }
  v15 = 0;
  v7 = 3985 * nVal;
  if ( *(&g_nSaveSlot0 + 3985 * nVal) <= 0 )
    return v13;
  v8 = &g_nSaveSlotBase[v7];
  for ( nVal5a = (int *)((char *)&g_nSaveSlot1 + v7 * 4); ; ++nVal5a )
  {
    Effect = this->CreateEffect(*nVal5a, v13, nVal2, nVal3, nVal4);
    if ( Effect == -1 )
      break;
    v10 = 8;
    do
    {
      if ( *((_BYTE *)v8 + 88) )
// [VFTABLE] (*((void ( **)(CEffObj *, int *))this->m_EffTable[Effect + 92].pEffect->__vftable + 12))(
// [VFTABLE]   this->m_EffTable[Effect + 92].pEffect,
// [VFTABLE]   v8);
      v8 += 31;
      --v10;
    }
    while ( v10 );
    if ( ++v15 >= *(&g_nSaveSlot0 + 3985 * nVal) )
      return v13;
  }
  return 0;
}

// 0x004CE580
void CEffMgr::Render(int nVal)
{
  int v2; // edx
  _BYTE *p_bValid; // eax

  if ( nVal )
  {
    v2 = 0;
    p_bValid = &this->m_EffTable[92].bValid;
    do
    {
      if ( *((_DWORD *)p_bValid - 1) == nVal && *p_bValid && !p_bValid[1] )
        break;
      ++v2;
      p_bValid += 20;
    }
    while ( v2 < 2048 );
  }
}

// 0x004CE5F0
void CEffMgr::SetTimeScale(float fScale)
{
  int v2; // esi
  int v3; // ebx
  int *v4; // edx
  int v5; // eax
  int *v6; // ecx
  CHAR Text[256]; // [esp+0xC] [ebp-0x100] BYREF

  v2 = *(_DWORD *)&g_EffTable[280 * LODWORD(fScale) + 36];
  if ( v2 )
  {
    v3 = 0;
    v4 = &g_nSaveSlot1;
    while ( 2 )
    {
      v5 = 0;
      v6 = v4;
      do
      {
        if ( *v6 == v2 )
        {
          sprintf(Text, (const char *const)&pTarget.m_pfnStagePostFx + 12, v3, v5);
          MessageBoxA(0, Text, Caption, 0);
          return;
        }
        ++v5;
        ++v6;
      }
      while ( v5 < 16 );
      v4 += 3985;
      ++v3;
      if ( (int)v4 < (int)&g_EffTable[4] )
        continue;
      break;
    }
  }
  memset(&g_EffTable[280 * LODWORD(fScale)], 0, 0x118u);
}

// 0x004CE690
char CEffMgr::CreateEff@<al>(
        CEffMgr *this@<ecx>,
        
        unsigned int a3,
        float a4,
        float a5,
        int a6)
{
  const char *EditorTaskDescription; // eax
  int v7; // ecx
  unsigned __int8 v8; // al
  int v9; // ebp
  bool v10; // zf
  char *v11; // ecx

  LOBYTE(EditorTaskDescription) = g_EffTable[280 * (_DWORD)a2 + 212];
  if ( (_BYTE)EditorTaskDescription )
  {
    v7 = 0;
    EditorTaskDescription = &g_EffTable[212];
    while ( *EditorTaskDescription )
    {
      EditorTaskDescription += 280;
      ++v7;
      if ( (int)EditorTaskDescription >= (int)&g_EffTaskEnd )
        return (char)EditorTaskDescription;
    }
    v8 = g_bEffSystemFlags;
    v9 = 280 * v7;
    v10 = (g_bEffSystemFlags & 1) == 0;
    qmemcpy(&g_EffTable[280 * v7], &g_EffTable[280 * (_DWORD)a2], 0x118u);
    if ( v10 )
    {
      g_bEffSystemFlags = v8 | 1;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    BringWindowToTop();
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
LABEL_9:
      g_bEffSystemFlags |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
LABEL_10:
    EditorTaskDescription = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)&g_EffTable[v9 + 4]);
    v11 = &g_EffTable[36];
    do
    {
      if ( v11[176] && *(const char **)v11 == EditorTaskDescription )
      {
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        BringWindowToTop();
        if ( (g_bEffSystemFlags & 1) != 0 )
          goto LABEL_10;
        goto LABEL_9;
      }
      v11 += 280;
    }
    while ( (int)v11 < (int)&g_EffTableEnd );
    *(_DWORD *)&g_EffTable[v9 + 36] = EditorTaskDescription;
  }
  return (char)EditorTaskDescription;
}

// 0x004CEA80
char CEffMgr::ReleaseCompletedEffects()
{
  int v2; // ebx
  CEffObj **p_pEffect; // esi
  int v4; // eax
  CEffObj **v5; // edx

  v2 = 2048;
  p_pEffect = &this->m_EffTable[92].pEffect;
  do
  {
    LOBYTE(v4) = *((_BYTE *)p_pEffect - 4);
    if ( (_BYTE)v4 )
    {
// [VFTABLE] (*((void ( **)(CEffObj *))(*p_pEffect)->__vftable + 3))(*p_pEffect);
      if ( !*((_BYTE *)p_pEffect - 2)
// [VFTABLE] && !(*((unsigned __int8 ( **)(CEffObj *))(*p_pEffect)->__vftable + 8))(*p_pEffect)
        && *p_pEffect )
      {
// [VFTABLE] (*(void ( **)(CEffObj *, int))(*p_pEffect)->__vftable)(*p_pEffect, 1);
      }
      *p_pEffect = 0;
      v4 = *(_DWORD *)&this->m_sz5D8C3C[1832] - 1;
      v5 = p_pEffect - 4;
      *(_DWORD *)&this->m_sz5D8C3C[1832] = v4;
      *v5 = 0;
      v5[1] = 0;
      v5[2] = 0;
      v5[3] = 0;
      *p_pEffect = 0;
    }
    p_pEffect += 5;
    --v2;
  }
  while ( v2 );
  return v4;
}

// 0x004CEDA0
int CEffMgr::RunEffGroup(char *nIndex, float a3, char *a4, float a5, int a6)
{
  int v6; // ebp
  tagEffClass *i; // eax
  char *v9; // ebx
  char *v10; // edi
  RenderTarget2 *v11; // eax
  CEffBase **v12; // eax

  v6 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v6 >= 32 )
      return -1;
  }
  v9 = (char *)this + 72 * v6;
  strcpy(v9 + 28, nIndex);
  v10 = a4;
  if ( !a4 )
    v10 = g_szSceneUIText;
  strcpy(v9 + 58, v10);
  v9[88] = 1;
  v11 = (RenderTarget2 *)operator new(0x34u);
  if ( v11 )
    v12 = ((RenderTarget2 *)v11)->ClearTarget();
  else
    v12 = 0;
  *((_DWORD *)v9 + 24) = v12;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v9 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)nIndex);
  return v6;
}

// 0x004CEFE0
int CEffMgr::CreateSParticleEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pEffMgr);
  v8 = (const char *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = operator new(0x30u);
  if ( v9 )
    v10 = sub_4D4EA0(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF100
bool CEffMgr::IsAllEffGroupStop(char *pszBuf, int nVal, char *pszBuf2)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v7; // ebx
  char *v8; // edi
  CEffCylinder *v9; // eax
  CEffCylinder **v10; // eax

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, pszBuf);
  v8 = pszBuf2;
  if ( !pszBuf2 )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffCylinder *)operator new(0x10C4u);
  if ( v9 )
    v10 = ((CEffCylinder *)v9)->Init();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pszBuf);
  return v4;
}

// 0x004CF220
int CEffMgr::CreateModelEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  CEffModel *v9; // eax
  CEffModel *v10; // eax

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pEffMgr);
  v8 = (const char *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffModel *)operator new(0x68u);
  if ( v9 )
    // [AUTO-COMMENTED] v10 = ((CEffModel *)v9)->CEffModel();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF460
int CEffMgr::CreateEffectType3(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pEffMgr);
  v8 = (const char *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = operator new(0x10B8u);
  if ( v9 )
    v10 = sub_4C9550(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF6A0
int CEffMgr::CreateEffectType4(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pEffMgr);
  v8 = (const char *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = operator new(0x10D0u);
  if ( v9 )
    v10 = sub_4CB3A0(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF7C0
void CEffMgr::CopyObjInGroup(char *nGroup, int nObj, char *nObjType)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v6; // ebx
  char *v7; // edi
  RenderTarget2 *v8; // eax
  CEffAudio **v9; // eax

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return;
  }
  v6 = (char *)this + 72 * v4;
  strcpy(v6 + 28, nGroup);
  v7 = nObjType;
  if ( !nObjType )
    v7 = g_szSceneUIText;
  strcpy(v6 + 58, v7);
  v6[88] = 1;
  v8 = (RenderTarget2 *)operator new(0x130u);
  if ( v8 )
    v9 = ((RenderTarget2 *)v8)->Reset();
  else
    v9 = 0;
  *((_DWORD *)v6 + 24) = v9;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v6 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)nGroup);
}

// 0x004CF8E0
int CEffMgr::CreateEffectType5(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pEffMgr);
  v8 = (const char *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = operator new(0x10B0u);
  if ( v9 )
    v10 = sub_4D3870(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CFB20
int CEffMgr::CreateShockEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  tagEffClass *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  CEffShock *v9; // eax
  const char *EditorTaskDescription; // eax
  int v11; // [esp+0x0] [ebp-0x1C]

  v4 = 0;
  for ( i = &this->m_EffClass[15]; i->_tail_000[0]; i += 18 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pEffMgr);
  v8 = (const char *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffShock *)operator new(0x30u);
  if ( v9 )
    EditorTaskDescription = ((CEffShock *)v9)->GetEditorTaskDescription(v11);
  else
    EditorTaskDescription = 0;
  *((_DWORD *)v7 + 24) = EditorTaskDescription;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004D22F0
int CEffMgr::UpdateKeyframe(int nVal)
{
  char *v3; // edi
  tagEffClass v4; // eax
  int v5; // ecx
  int v6; // ecx
  double v7; // st7
  tagEffClass v8; // eax
  int v9; // ebx
  float *v10; // eax
  float *v11; // ecx
  double v12; // st7
  float *v13; // ecx
  double v14; // st7
  float m_fEffParam; // ecx
  double v16; // st7
  float *v17; // ecx
  double v18; // st7
  float *v19; // ecx
  double v20; // st7
  unsigned __int16 v21; // cx
  int v22; // eax
  int v23; // ebx
  float v24; // edx
  float *v25; // ecx
  double v26; // st7
  float v27; // ecx
  double v28; // st7
  float *v29; // ecx
  double v30; // st7
  float *v31; // ecx
  double v32; // st7
  float *v33; // ecx
  double v34; // st7
  unsigned __int16 v35; // dx
  int v36; // ecx
  float v38; // [esp+0x0] [ebp-0x90]
  float v39; // [esp+0x0] [ebp-0x90]
  gbMatrix4 v40; // [esp+0x10] [ebp-0x80] BYREF
  struct gbVec3D v41; // [esp+0x50] [ebp-0x40] BYREF
  struct gbVec3D v42; // [esp+0x5C] [ebp-0x34] BYREF
  gbVec3D v43; // [esp+0x68] [ebp-0x28] BYREF
  float v44; // [esp+0x74] [ebp-0x1C]
  float v45; // [esp+0x78] [ebp-0x18]
  float v46; // [esp+0x7C] [ebp-0x14]
  float v47; // [esp+0x80] [ebp-0x10]
  int v48; // [esp+0x84] [ebp-0xC]
  int v49; // [esp+0x88] [ebp-0x8]
  float v50; // [esp+0x8C] [ebp-0x4]

  v3 = (char *)this->m_pCam + 152 * *(_DWORD *)this->m_EffClass;
  v4 = this->m_EffClass[1];
  v5 = 9 * *(_DWORD *)&v4;
  v4._tail_000[0] = *(_BYTE *)(*(_DWORD *)v3 + 72 * *(_DWORD *)&v4 + 65);
  v6 = *(_DWORD *)v3 + 8 * v5;
  v49 = v6;
  if ( !v4._tail_000[0] )
    *(_BYTE *)(v6 + 65) = 1;
  v7 = *(float *)&this->m_pAdditiveBlend - *(float *)(v6 + 16);
  v50 = *(float *)&this->m_pAlphaBlend;
  if ( v7 > *(float *)(v6 + 24) )
    v50 = v50 - (v7 - *(float *)(v6 + 24));
  memset(&v43, 0, sizeof(v43));
  memset(&v42, 0, sizeof(v42));
  memset(&v41, 0, sizeof(v41));
  if ( v3[114] )
  {
    v8 = this->m_EffClass[11];
    if ( v8 != -1 )
    {
      v9 = 80 * *(_DWORD *)&v8;
      *(float *)(80 * *(_DWORD *)&v8 + LODWORD(this->m_fEffParam) + 28) = v50 * *((float *)v3 + 6)
                                                                        + *(float *)(80 * *(_DWORD *)&v8
                                                                                   + LODWORD(this->m_fEffParam)
                                                                                   + 28);
      *(float *)(80 * *(_DWORD *)&v8 + LODWORD(this->m_fEffParam) + 32) = v50 * *((float *)v3 + 29)
                                                                        + *(float *)(80 * *(_DWORD *)&v8
                                                                                   + LODWORD(this->m_fEffParam)
                                                                                   + 32);
      v10 = (float *)(80 * *(_DWORD *)&v8 + LODWORD(this->m_fEffParam) + 48);
      *v10 = v50 * *((float *)v3 + 10) + *v10;
      if ( *((float *)v3 + 17) != 0.0 )
        *(float *)(v9 + LODWORD(this->m_fEffParam) + 48) = v50 * *((float *)v3 + 17)
                                                         + *(float *)(v9 + LODWORD(this->m_fEffParam) + 48);
      *(float *)(v9 + LODWORD(this->m_fEffParam) + 52) = v50 * *((float *)v3 + 16)
                                                       + *(float *)(v9 + LODWORD(this->m_fEffParam) + 52);
      *(float *)(v9 + LODWORD(this->m_fEffParam) + 56) = v50 * *((float *)v3 + 18)
                                                       + *(float *)(v9 + LODWORD(this->m_fEffParam) + 56);
      if ( *((float *)v3 + 20) != 0.0
        || *((float *)v3 + 21) != 0.0
        || *((float *)v3 + 23) != 0.0
        || *((float *)v3 + 22) != 0.0 )
      {
        *(float *)(v9 + LODWORD(this->m_fEffParam) + 60) = v50 * *((float *)v3 + 20)
                                                         + *(float *)(v9 + LODWORD(this->m_fEffParam) + 60);
        *(float *)(v9 + LODWORD(this->m_fEffParam) + 64) = v50 * *((float *)v3 + 21)
                                                         + *(float *)(v9 + LODWORD(this->m_fEffParam) + 64);
        *(float *)(v9 + LODWORD(this->m_fEffParam) + 68) = v50 * *((float *)v3 + 22)
                                                         + *(float *)(v9 + LODWORD(this->m_fEffParam) + 68);
        *(float *)(v9 + LODWORD(this->m_fEffParam) + 72) = v50 * *((float *)v3 + 23)
                                                         + *(float *)(v9 + LODWORD(this->m_fEffParam) + 72);
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v11 = (float *)(v9 + LODWORD(this->m_fEffParam) + 60);
        if ( *v11 <= 255.0 )
        {
          if ( *v11 >= 0.0 )
            v12 = *v11;
          else
            v12 = 0.0;
        }
        else
        {
          v12 = 255.0;
        }
        *v11 = v12;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v13 = (float *)(v9 + LODWORD(this->m_fEffParam) + 64);
        if ( *v13 <= 255.0 )
        {
          if ( *v13 >= 0.0 )
            v14 = *v13;
          else
            v14 = 0.0;
        }
        else
        {
          v14 = 255.0;
        }
        *v13 = v14;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        m_fEffParam = this->m_fEffParam;
        v16 = *(float *)(v9 + LODWORD(m_fEffParam) + 68);
        v17 = (float *)(v9 + LODWORD(m_fEffParam) + 68);
        if ( v16 <= 255.0 )
        {
          if ( *v17 >= 0.0 )
            v18 = *v17;
          else
            v18 = 0.0;
        }
        else
        {
          v18 = 255.0;
        }
        *v17 = v18;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v19 = (float *)(v9 + LODWORD(this->m_fEffParam) + 72);
        if ( *v19 <= 255.0 )
        {
          if ( *v19 >= 0.0 )
            v20 = *v19;
          else
            v20 = 0.0;
        }
        else
        {
          v20 = 255.0;
        }
        *v19 = v20;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v48 = *(int *)(v9 + LODWORD(this->m_fEffParam) + 60);
        LODWORD(v47) = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v48 = *(int *)(v9 + LODWORD(this->m_fEffParam) + 64);
        LODWORD(v46) = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v48 = *(int *)(v9 + LODWORD(this->m_fEffParam) + 68);
        LODWORD(v45) = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        v48 = *(int *)(v9 + LODWORD(this->m_fEffParam) + 72);
        v48 = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
          atexit(todo_401800);
        }
        HIBYTE(v21) = LOBYTE(v47);
        LOBYTE(v21) = LOBYTE(v46);
        *(_DWORD *)(v9 + LODWORD(this->m_fEffParam) + 76) = (unsigned __int8)v48 | ((LOBYTE(v45) | (v21 << 8)) << 8);
        *(_DWORD *)(LODWORD(this->m_fPosX) + 68 * *(_DWORD *)(v9 + LODWORD(this->m_fEffParam)) + 64) = *(_DWORD *)(v9 + LODWORD(this->m_fEffParam) + 76);
      }
      *(float *)(v9 + LODWORD(this->m_fEffParam) + 16) = v50 * *((float *)v3 + 7)
                                                       + *(float *)(v9 + LODWORD(this->m_fEffParam) + 16);
      *(float *)(v9 + LODWORD(this->m_fEffParam) + 20) = v50 * *((float *)v3 + 8)
                                                       + *(float *)(v9 + LODWORD(this->m_fEffParam) + 20);
      *(float *)(v9 + LODWORD(this->m_fEffParam) + 24) = v50 * *((float *)v3 + 9)
                                                       + *(float *)(v9 + LODWORD(this->m_fEffParam) + 24);
      ((gbMatrix4 *)&v40)->LoadIdentity();
      v43 = *(gbVec3D *)(v3 + 44);
      ((gbVec3D *)&v43)->Normalize();
      v38 = (*(float *)&this->m_pAdditiveBlend - *(float *)(v49 + 16)) * *((float *)v3 + 15);
      ((gbMatrix4 *)&v40)->SetAxisAngle(&v43, v38);
      v42.z = *((float *)v3 + 14);
      v42.x = 0.0;
      v42.y = 0.0;
      ((gbMatrix4 *)&v40)->Rotate(&v42, v41);
      *(gbVec3D *)(v9 + LODWORD(this->m_fEffParam) + 36) = v41;
    }
  }
  else
  {
    v22 = (int)this->m_EffClass[8];
    *(float *)&v48 = 0.0;
    if ( v22 > 0 )
    {
      v23 = 0;
      do
      {
        v24 = this->m_fEffParam;
        if ( *(_BYTE *)(v23 + LODWORD(v24) + 4) )
        {
          *(float *)(v23 + LODWORD(v24) + 28) = v50 * *((float *)v3 + 6) + *(float *)(v23 + LODWORD(v24) + 28);
          *(float *)(v23 + LODWORD(this->m_fEffParam) + 32) = v50 * *((float *)v3 + 29)
                                                            + *(float *)(v23 + LODWORD(this->m_fEffParam) + 32);
          *(float *)(v23 + LODWORD(this->m_fEffParam) + 48) = v50 * *((float *)v3 + 10)
                                                            + *(float *)(v23 + LODWORD(this->m_fEffParam) + 48);
          if ( *((float *)v3 + 17) != 0.0 )
            *(float *)(v23 + LODWORD(this->m_fEffParam) + 48) = v50 * *((float *)v3 + 17)
                                                              + *(float *)(v23 + LODWORD(this->m_fEffParam) + 48);
          *(float *)(v23 + LODWORD(this->m_fEffParam) + 52) = v50 * *((float *)v3 + 16)
                                                            + *(float *)(v23 + LODWORD(this->m_fEffParam) + 52);
          *(float *)(v23 + LODWORD(this->m_fEffParam) + 56) = v50 * *((float *)v3 + 18)
                                                            + *(float *)(v23 + LODWORD(this->m_fEffParam) + 56);
          if ( *((float *)v3 + 20) != 0.0
            || *((float *)v3 + 21) != 0.0
            || *((float *)v3 + 23) != 0.0
            || *((float *)v3 + 22) != 0.0 )
          {
            *(float *)(v23 + LODWORD(this->m_fEffParam) + 60) = v50 * *((float *)v3 + 20)
                                                              + *(float *)(v23 + LODWORD(this->m_fEffParam) + 60);
            *(float *)(v23 + LODWORD(this->m_fEffParam) + 64) = v50 * *((float *)v3 + 21)
                                                              + *(float *)(v23 + LODWORD(this->m_fEffParam) + 64);
            *(float *)(v23 + LODWORD(this->m_fEffParam) + 68) = v50 * *((float *)v3 + 22)
                                                              + *(float *)(v23 + LODWORD(this->m_fEffParam) + 68);
            *(float *)(v23 + LODWORD(this->m_fEffParam) + 72) = v50 * *((float *)v3 + 23)
                                                              + *(float *)(v23 + LODWORD(this->m_fEffParam) + 72);
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v25 = (float *)(v23 + LODWORD(this->m_fEffParam) + 60);
            if ( *v25 <= 255.0 )
            {
              if ( *v25 >= 0.0 )
                v26 = *v25;
              else
                v26 = 0.0;
            }
            else
            {
              v26 = 255.0;
            }
            *v25 = v26;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v27 = this->m_fEffParam;
            v28 = *(float *)(v23 + LODWORD(v27) + 64);
            v29 = (float *)(v23 + LODWORD(v27) + 64);
            if ( v28 <= 255.0 )
            {
              if ( *v29 >= 0.0 )
                v30 = *v29;
              else
                v30 = 0.0;
            }
            else
            {
              v30 = 255.0;
            }
            *v29 = v30;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v31 = (float *)(v23 + LODWORD(this->m_fEffParam) + 68);
            if ( *v31 <= 255.0 )
            {
              if ( *v31 >= 0.0 )
                v32 = *v31;
              else
                v32 = 0.0;
            }
            else
            {
              v32 = 255.0;
            }
            *v31 = v32;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v33 = (float *)(v23 + LODWORD(this->m_fEffParam) + 72);
            if ( *v33 <= 255.0 )
            {
              if ( *v33 >= 0.0 )
                v34 = *v33;
              else
                v34 = 0.0;
            }
            else
            {
              v34 = 255.0;
            }
            *v33 = v34;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v45 = *(float *)(v23 + LODWORD(this->m_fEffParam) + 60) + 12582912.0;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v46 = *(float *)(v23 + LODWORD(this->m_fEffParam) + 64) + 12582912.0;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v47 = *(float *)(v23 + LODWORD(this->m_fEffParam) + 68) + 12582912.0;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            v44 = *(float *)(v23 + LODWORD(this->m_fEffParam) + 72) + 12582912.0;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
              atexit(todo_401800);
            }
            HIBYTE(v35) = LOBYTE(v45);
            LOBYTE(v35) = LOBYTE(v46);
            *(_DWORD *)(v23 + LODWORD(this->m_fEffParam) + 76) = LOBYTE(v44) | ((LOBYTE(v47) | (v35 << 8)) << 8);
            *(_DWORD *)(LODWORD(this->m_fPosX) + 68 * *(_DWORD *)(v23 + LODWORD(this->m_fEffParam)) + 64) = *(_DWORD *)(v23 + LODWORD(this->m_fEffParam) + 76);
          }
          *(float *)(v23 + LODWORD(this->m_fEffParam) + 16) = v50 * *((float *)v3 + 7)
                                                            + *(float *)(v23 + LODWORD(this->m_fEffParam) + 16);
          *(float *)(v23 + LODWORD(this->m_fEffParam) + 20) = v50 * *((float *)v3 + 8)
                                                            + *(float *)(v23 + LODWORD(this->m_fEffParam) + 20);
          *(float *)(v23 + LODWORD(this->m_fEffParam) + 24) = v50 * *((float *)v3 + 9)
                                                            + *(float *)(v23 + LODWORD(this->m_fEffParam) + 24);
          ((gbMatrix4 *)&v40)->LoadIdentity();
          v43 = *(gbVec3D *)(v3 + 44);
          ((gbVec3D *)&v43)->Normalize();
          v39 = (*(float *)&this->m_pAdditiveBlend - *(float *)(v49 + 16)) * *((float *)v3 + 15);
          ((gbMatrix4 *)&v40)->SetAxisAngle(&v43, v39);
          v42.z = *((float *)v3 + 14);
          v42.x = 0.0;
          v42.y = 0.0;
          ((gbMatrix4 *)&v40)->Rotate(&v42, v41);
          *(gbVec3D *)(v23 + LODWORD(this->m_fEffParam) + 36) = v41;
        }
        v36 = (int)this->m_EffClass[8];
        v23 += 80;
        ++v48;
      }
      while ( v48 < v36 );
    }
  }
  if ( *(_BYTE *)(v49 + 66) == 1 || *(float *)&this->m_pAdditiveBlend - *(float *)(v49 + 16) >= *(float *)(v49 + 24) )
    *(_DWORD *)(v49 + 8) = 4;
  return 0;
}

// 0x004D58A0
int * CEffMgr::Reset()
{
  sub_4D5A00();
  *(_DWORD *)&this->m_EffTable[26].bValid = 1;
  this->m_EffTable[26].pEffect = (CEffObj *)timeGetTime();
  this->m_EffTable[27].dwClassNameCRC = 0;
  return (int *)this;
}
