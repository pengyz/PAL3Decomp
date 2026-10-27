#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffMgr.h"
#include "Misc/CEffAudio.h"
#include "Misc/CEffBase.h"
#include "Effect/CEffCylinder.h"
#include "Effect/CEffModel.h"
#include "Effect/CEffSParticle.h"
#include "Effect/CEffShock.h"
#include "Effect/CEffgbParticle.h"
#include "GameBase/Logger.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/ParticleEffect.h"
#include "Render/RenderTarget2.h"
#include "UI/UIWnd.h"
#include "Misc/tag17A7BData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4C9550(...);
int sub_4CB3A0(...);
int sub_4CD340(...);
int sub_4D3870(...);
int sub_4D4EA0(...);
int sub_4D5A00(...);

// Unnamed globals (extern)
extern CPK stru_DE9CB0;

// 0x004B7340
void CEffMgr::UpdateTimedTrigger(float fVal)
{
  float v3; // st7
  bool v4; // zf
  char v5; // al
  int v6; // eax
  int v7; // eax

  v3 = fVal + *(float *)&this->_tail_000[112];
  v4 = *(_DWORD *)&this->_tail_000[92] == 275;
  *(float *)&this->_tail_000[112] = v3;
  if ( v4 )
  {
    if ( v3 >= 9.5f )
    {
      LOBYTE(v7) = (((CEffMgr *)g_pSceneManager))->CEffMgr::Init(275, *(_DWORD *)&this->_tail_000[100], *(_DWORD *)&this->_tail_000[104], *(_DWORD *)&this->_tail_000[108], 0);
      *(_DWORD *)&this->_tail_000[96] = v7;
      *(_DWORD *)&this->_tail_000[112] = 0;
    }
  }
  else
  {
    (((CEffMgr *)g_pSceneManager))->CEffMgr::Render(*(_DWORD *)&this->_tail_000[96]);
    if ( !v5 )
    {
      LOBYTE(v6) = (((CEffMgr *)g_pSceneManager))->CEffMgr::Init(*(_DWORD *)&this->_tail_000[92], *(_DWORD *)&this->_tail_000[100], *(_DWORD *)&this->_tail_000[104], *(_DWORD *)&this->_tail_000[108], 0);
      *(_DWORD *)&this->_tail_000[96] = v6;
    }
  }
}

// 0x004B73F0
int CEffMgr::SetEffectClass(int nVal, int nVal2, int nVal3)
{
  int result; // eax

  *(_DWORD *)&this->_tail_000[100] = nVal;
  *(_DWORD *)&this->_tail_000[104] = nVal2;
  *(_DWORD *)&this->_tail_000[108] = nVal3;
  LOBYTE(result) = (((CEffMgr *)g_pSceneManager))->CEffMgr::Init(*(_DWORD *)&this->_tail_000[92], *(_DWORD *)&this->_tail_000[100], nVal2, nVal3, 0);
  *(_DWORD *)&this->_tail_000[96] = result;
  *(_DWORD *)&this->_tail_000[112] = 0;
  return result;
}

// 0x004C2F30
int CEffMgr::ProcessEffectPass(int nVal)
{
  int v3; // edi
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

  v3 = *(_DWORD *)&this->_tail_000[24] + 152 * *(_DWORD *)&this->_tail_000[28];
  v4 = *(_DWORD *)v3 + 72 * *(_DWORD *)&this->_tail_000[32];
  if ( !*(_BYTE *)(v4 + 65) )
  {
    if ( *(float *)(v3 + 24) != 0.0f )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      *(float *)&nVal4 = *(float *)(v3 + 36) + *(float *)&this->_tail_000[56];
      *(float *)&nVal3 = *(float *)(v3 + 32) + *(float *)&this->_tail_000[52];
      *(float *)&nVal2 = *(float *)(v3 + 28) + *(float *)&this->_tail_000[48];
      (((CEffMgr *)*(CEffMgr **)&this->_tail_000[4]))->CEffMgr::Init((int)*(float *)(v3 + 24), nVal2, nVal3, nVal4, *(_DWORD *)&this->_tail_000[60]);
    }
    if ( *(float *)(v3 + 56) != 0.0f )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      *(float *)&nVal4a = *(float *)(v3 + 72) + *(float *)&this->_tail_000[56];
      *(float *)&nVal3a = *(float *)(v3 + 68) + *(float *)&this->_tail_000[52];
      *(float *)&nVal2a = *(float *)(v3 + 64) + *(float *)&this->_tail_000[48];
      (((CEffMgr *)*(CEffMgr **)&this->_tail_000[4]))->CEffMgr::Init((int)*(float *)(v3 + 56), nVal2a, nVal3a, nVal4a, *(_DWORD *)&this->_tail_000[60]);
    }
    if ( *(float *)(v3 + 44) != 0.0f )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      *(float *)&nVal4b = *(float *)(v3 + 60) + *(float *)&this->_tail_000[56];
      *(float *)&nVal3b = *(float *)(v3 + 52) + *(float *)&this->_tail_000[52];
      *(float *)&nVal2b = *(float *)(v3 + 48) + *(float *)&this->_tail_000[48];
      (((CEffMgr *)*(CEffMgr **)&this->_tail_000[4]))->CEffMgr::Init((int)*(float *)(v3 + 44), nVal2b, nVal3b, nVal4b, *(_DWORD *)&this->_tail_000[60]);
    }
    if ( *(float *)(v3 + 80) != 0.0f )
    {
      if ( (g_bScriptFlag & 1) == 0 )
      {
        g_bScriptFlag |= 1u;
        (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
        atexit(j_j_codecvt_base);
      }
      *(float *)&nVal4c = *(float *)(v3 + 92) + *(float *)&this->_tail_000[56];
      *(float *)&nVal3c = *(float *)(v3 + 88) + *(float *)&this->_tail_000[52];
      *(float *)&nVal2c = *(float *)(v3 + 84) + *(float *)&this->_tail_000[48];
      (((CEffMgr *)*(CEffMgr **)&this->_tail_000[4]))->CEffMgr::Init((int)*(float *)(v3 + 80), nVal2c, nVal3c, nVal4c, *(_DWORD *)&this->_tail_000[60]);
    }
    *(_BYTE *)(v4 + 65) = 1;
  }
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->_tail_000[16] - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
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
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  double v16; // st4
  double v17; // st4
  double v18; // st4
  double v19; // st3
  double v20; // st2
  float *v21; // ecx
  int v22; // ecx
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
  float v38; // [esp+0x2C] [ebp-0xC]
  float v39; // [esp+0x30] [ebp-0x8]
  float v40; // [esp+0x30] [ebp-0x8]
  float v41; // [esp+0x34] [ebp-0x4]
  float v42; // [esp+0x34] [ebp-0x4]

  v1 = 0.0;
  v3 = 0;
  v30 = 0.0f;
  v4 = *(_DWORD *)&this->_tail_000[112];
  v5 = 1;
  v41 = *(float *)&this->_tail_000[104] / (float)v4;
  v6 = *(float *)&this->_tail_000[108];
  v7 = 0.0;
  v8 = sin(0.0);
  v32 = v8;
  v9 = v8 * *(float *)&this->_tail_000[124];
  v10 = cos(0.0);
  v28 = v10 * *(float *)&this->_tail_000[124];
  v29 = v32 * *(float *)&this->_tail_000[128];
  v31 = v10 * *(float *)&this->_tail_000[128];
  if ( v4 > 0 )
  {
    v11 = 0;
    do
    {
      v12 = *(_DWORD *)&this->_tail_000[48];
      *(float *)(v12 + v11 + 36) = v9;
      v13 = v12 + v11 + 36;
      *(float *)(v13 + 8) = v28;
      *(float *)(v13 + 4) = v6;
      v14 = *(_DWORD *)&this->_tail_000[48];
      *(float *)(v14 + v11) = v29;
      v15 = v11 + v14;
      *(float *)(v15 + 4) = v30;
      v1 = v1 + v41;
      *(float *)(v15 + 8) = v31;
      v39 = v41 * *(float *)&this->_tail_000[132] + *(float *)&this->_tail_000[124];
      v16 = v41 * *(float *)&this->_tail_000[136];
      *(float *)&this->_tail_000[124] = v39;
      v33 = v16 + *(float *)&this->_tail_000[128];
      *(float *)&this->_tail_000[128] = v33;
      v6 = v6 + v41 * *(float *)&this->_tail_000[140];
      v7 = v7 + v41 * *(float *)&this->_tail_000[144];
      v30 = v7;
      v37 = sin(v1 * 0.01745329238474369f);
      v35 = cos(v1 * 0.01745329238474369f);
      v17 = v39;
      if ( v5 )
      {
        v18 = v17 - *(float *)&this->_tail_000[116];
        v40 = v18;
        v9 = v18 * v37;
        v19 = v40 * v35;
        v28 = v19;
        v20 = v33 - *(float *)&this->_tail_000[120];
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
      v21 = (float *)(*(_DWORD *)&this->_tail_000[48] + v11 + 24);
      v31 = v20 * v35;
      v5 = !v5;
      *v21 = v9;
      ++v3;
      v21[1] = v6;
      v21[2] = v19;
      v22 = *(_DWORD *)&this->_tail_000[48];
      *(float *)(v22 + v11 + 12) = v29;
      v23 = v22 + v11 + 12;
      v11 += 68;
      *(float *)(v23 + 8) = v31;
      *(float *)(v23 + 4) = v7;
      *(_DWORD *)(*(_DWORD *)&this->_tail_000[48] + v11 - 20) = *(_DWORD *)&this->_tail_000[196];
      *(_DWORD *)(*(_DWORD *)&this->_tail_000[48] + v11 - 12) = *(_DWORD *)&this->_tail_000[204];
      *(_DWORD *)(*(_DWORD *)&this->_tail_000[48] + v11 - 16) = *(_DWORD *)&this->_tail_000[200];
      *(_DWORD *)(*(_DWORD *)&this->_tail_000[48] + v11 - 8) = *(_DWORD *)&this->_tail_000[208];
      *(_DWORD *)(*(_DWORD *)&this->_tail_000[48] + v11 - 4) = *(_DWORD *)&this->_tail_000[76];
    }
    while ( v3 < *(_DWORD *)&this->_tail_000[112] );
  }
  v38 = *(float *)&this->_tail_000[196];
  v36 = *(float *)&this->_tail_000[200];
  v34 = *(float *)&this->_tail_000[208];
  v42 = *(float *)&this->_tail_000[148]
      / (double)*(int *)&this->_tail_000[112]
      * (*(float *)&this->_tail_000[204] - v38);
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  v24 = (double)(int)v36;
  if ( v24 > 1.0 )
  {
    v36 = v36 - v24;
    v34 = v34 - v24;
  }
  result = *(_DWORD *)&this->_tail_000[112];
  v26 = 0;
  if ( result > 0 )
  {
    v27 = v38;
    result = 0;
    do
    {
      ++v26;
      *(float *)(*(_DWORD *)&this->_tail_000[48] + result + 48) = v27;
      v27 = v27 + v42;
      result += 68;
      *(float *)(*(_DWORD *)&this->_tail_000[48] + result - 12) = v27;
      *(float *)(*(_DWORD *)&this->_tail_000[48] + result - 16) = v36;
      *(float *)(*(_DWORD *)&this->_tail_000[48] + result - 8) = v34;
    }
    while ( v26 < *(_DWORD *)&this->_tail_000[112] );
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
  float v16; // st7
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
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  v19 = (int)*(float *)&this->_tail_000[124];
  v29 = *(float *)&this->_tail_000[128];
  if ( v19 <= 0 )
    v19 = 2;
  if ( *(float *)&this->_tail_000[144] < 0.0f )
    *(_DWORD *)&this->_tail_000[144] = 0;
  result = *(_DWORD *)&this->_tail_000[108];
  v20 = 0;
  if ( result > 0 )
  {
    do
    {
      v22 = 0;
      if ( *(int *)&this->_tail_000[112] > 0 )
      {
        v4 = 24 * v1;
        do
        {
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
            atexit(j_j_codecvt_base);
          }
          v5 = v22 - *(_DWORD *)&this->_tail_000[108] / 2;
          v18 = (float)v19;
          v23 = v18
              - (double)(int)((HIDWORD(v5) ^ v5) - HIDWORD(v5))
              * (double)(int)abs32(v20 - *(_DWORD *)&this->_tail_000[112] / 2)
              * *(float *)&this->_tail_000[144];
          v6 = (int)v23;
          if ( (double)v6 < v29 )
          {
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v6 = (int)v29;
          }
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
            atexit(j_j_codecvt_base);
          }
          ++g_nRandCount;
          v7 = 214013 * g_nRandSeed + 2531011;
          g_nRandSeed = v7;
          v28 = (float)(v6 / 2);
          v26 = (float)(((v7 >> 16) & 0x7FFF) % v6) - v28;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
            atexit(j_j_codecvt_base);
            v7 = g_nRandSeed;
          }
          ++g_nRandCount;
          v8 = 214013 * v7 + 2531011;
          g_nRandSeed = v8;
          v24 = (float)(((v8 >> 16) & 0x7FFF) % v6) - v28;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
            atexit(j_j_codecvt_base);
            v8 = g_nRandSeed;
          }
          ++g_nRandCount;
          g_nRandSeed = 214013 * v8 + 2531011;
          v9 = (((int)g_nRandSeed >> 16) & 0x7FFF) % v6;
          v10 = (float *)(*(_DWORD *)&this->_tail_000[52] + v4);
          *v10 = v26;
          v10[1] = v24;
          v10[2] = (double)v9 - v28;
          if ( (((gbVec3D *)(*(_DWORD *)&this->_tail_000[52] + v4)))->gbVec3D::Length() < (double)v29 )
          {
            (((gbVec3D *)(*(_DWORD *)&this->_tail_000[52] + v4)))->gbVec3D::Normalize();
            v11 = (float *)(*(_DWORD *)&this->_tail_000[52] + v4);
            *v11 = v29 * *v11;
            v11[1] = v29 * v11[1];
            v11[2] = v29 * v11[2];
          }
          v12 = (float *)(*(_DWORD *)&this->_tail_000[52] + v4);
          *v12 = *(float *)&this->_tail_000[132] + *v12;
          v12[1] = *(float *)&this->_tail_000[136] + v12[1];
          v12[2] = v12[2] + *(float *)&this->_tail_000[140];
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
            atexit(j_j_codecvt_base);
          }
          ++g_nRandCount;
          g_nRandSeed = 214013 * g_nRandSeed + 2531011;
          v13 = g_nRandSeed;
          v27 = ((float)((((int)g_nRandSeed >> 16) & 0x7FFF) % 160) - 80.0f) * 16.0f;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
            atexit(j_j_codecvt_base);
            v13 = g_nRandSeed;
          }
          ++g_nRandCount;
          v14 = 214013 * v13 + 2531011;
          g_nRandSeed = v14;
          v25 = ((float)(((v14 >> 16) & 0x7FFF) % 160) - 80.0f) * 16.0f;
          if ( (g_bEffSystemFlags & 1) == 0 )
          {
            g_bEffSystemFlags |= 1u;
            (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
            atexit(j_j_codecvt_base);
            v14 = g_nRandSeed;
          }
          ++g_nRandCount;
          g_nRandSeed = 214013 * v14 + 2531011;
          v15 = (float *)(v4 + *(_DWORD *)&this->_tail_000[52] + 12);
          v4 += 24;
          v16 = (float)((((int)g_nRandSeed >> 16) & 0x7FFF) % 160) - 80.0f;
          *v15 = v27;
          v15[1] = v25;
          v15[2] = v16 * 16.0;
          v17 = ++v22 < *(_DWORD *)&this->_tail_000[112];
          ++v21;
        }
        while ( v17 );
        v1 = v21;
      }
      result = ++v20;
    }
    while ( v20 < *(_DWORD *)&this->_tail_000[108] );
  }
  *(_DWORD *)&this->_tail_000[188] = 1080117166;
  return result;
}

// 0x004CCEF0
int CEffMgr::UpdateEffect(float fVal, int nVal)
{
  int v4; // eax
  int result; // eax
  int v6; // edi
  int v7; // ebx
  int v8; // ecx
  float v9; // st7
  float *v10; // eax
  float v11; // st6
  float *v12; // eax
  int v13; // eax
  float v14; // st7
  float v15; // st6
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

  v4 = *(_DWORD *)&this->_tail_000[4];
  *(float *)&this->_tail_000[140] = fVal + *(float *)&this->_tail_000[140];
  fVala = *(float *)(v4 + 43308) * 0.019999999552965164f;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  v23 = *(float *)&this->_tail_000[140] / fVala;
  result = (int)v23;
  *(float *)&this->_tail_000[140] = *(float *)&this->_tail_000[140] - (double)result * fVala;
  if ( result > 0 )
  {
    v24 = (int)v23;
    do
    {
      v6 = 0;
      v25 = 0;
      if ( *(int *)&this->_tail_000[116] > 0 )
      {
        v7 = 0;
        do
        {
          v8 = *(_DWORD *)&this->_tail_000[56];
          v9 = *(float *)(v6 + v8 + 36) - *(float *)(v6 + v8);
          v10 = (float *)(v6 + v8);
          v21 = *(float *)(v6 + v8 + 40) - *(float *)(v6 + v8 + 4);
          v11 = *(float *)(v6 + v8 + 44) - *(float *)(v6 + v8 + 8);
          v10[7] = v21;
          v22 = v11;
          v10[6] = v9;
          v10[8] = v22;
          v12 = (float *)(v6 + *(_DWORD *)&this->_tail_000[56]);
          v19 = fVala * v12[7];
          v20 = fVala * v12[8];
          v12[3] = fVala * v12[6] + v12[3];
          v12[4] = v19 + v12[4];
          v12[5] = v20 + v12[5];
          v13 = *(_DWORD *)&this->_tail_000[56];
          v14 = fVala * *(float *)(v13 + v6 + 12);
          v15 = fVala * *(float *)(v13 + v6 + 16);
          v16 = (float *)(v6 + v13);
          v17 = v15;
          v18 = fVala * v16[5];
          *v16 = v14 + *v16;
          v16[1] = v17 + v16[1];
          v16[2] = v18 + v16[2];
          sub_4CD340(*(_DWORD *)&this->_tail_000[56] + v6, LODWORD(fVala));
          v6 += 48;
          v7 += 56;
          ++v25;
        }
        while ( v25 < *(_DWORD *)&this->_tail_000[116] );
      }
      result = --v24;
    }
    while ( v24 );
  }
  return result;
}

// 0x004CDAE0
char CEffMgr::ReleaseAllRefs()
{
  _DWORD *v2; // esi
  int v3; // ebx
  _DWORD *v4; // esi
  int v5; // edi
  char result; // al

  (((gbRefObject *)*(gbRefObject **)&this->_tail_000[16]))->gbRefObject::Release();
  (((gbRefObject *)*(gbRefObject **)&this->_tail_000[20]))->gbRefObject::Release();
  (((gbRefObject *)*(gbRefObject **)&this->_tail_000[8]))->gbRefObject::Release();
  (((gbRefObject *)*(gbRefObject **)&this->_tail_000[12]))->gbRefObject::Release();
  v2 = (_DWORD *)&this->_tail_000[96];
  v3 = 32;
  do
  {
    if ( *((_BYTE *)v2 - 8) )
    {
      if ( !*((_BYTE *)v2 - 7) )
      {
        (*(void ( **)(_DWORD))(*(_DWORD *)*v2 + 12))(*v2);
        if ( *v2 )
          (**(void ( ***)(_DWORD, int))*v2)((_DWORD)(*v2), (int)(1));
      }
    }
    v2 += 18;
    --v3;
  }
  while ( v3 );
  v4 = (_DWORD *)&this->_tail_000[2348];
  v5 = 2048;
  do
  {
    result = *((_BYTE *)v4 - 4);
    if ( result )
    {
      result = (*(int ( **)(_DWORD))(*(_DWORD *)*v4 + 12))(*v4);
      if ( *v4 )
        result = (**(int ( ***)(_DWORD, int))*v4)((_DWORD)(*v4), (int)(1));
    }
    v4 += 5;
    --v5;
  }
  while ( v5 );
  return result;
}

// 0x004CDC50
char CEffMgr::SetEffectsTimeScale(int nVal)
{
  _DWORD *v2; // esi
  int v3; // ebx
  char result; // al

  *(_DWORD *)&this->_tail_000[43308] = nVal;
  v2 = (_DWORD *)&this->_tail_000[2348];
  v3 = 2048;
  do
  {
    result = *((_BYTE *)v2 - 4);
    if ( result )
    {
      if ( *(v2 - 4) == -211379188 )
        result = (*(int ( **)(_DWORD, int))(*(_DWORD *)*v2 + 44))(*v2, nVal);
      if ( *(v2 - 4) == 1140548963 )
        result = (*(int ( **)(_DWORD, int))(*(_DWORD *)*v2 + 44))(*v2, nVal);
    }
    v2 += 5;
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
  _BYTE *v11; // eax
  int v12; // ebp
  _BYTE *v13; // eax
  char *pEffObj; // edi
  char *v16; // eax
  char *v17; // esi
  char v18; // al
  int v19; // edx
  void ( ***v20)(_DWORD, int); // ecx
  int EffSlot; // [esp+0x14] [ebp-0x8]
  int v22; // [esp+0x18] [ebp-0x4]

  v7 = 35 * this->CEffMgr::FindEffByID(nVal);
  v8 = *(_DWORD *)&g_EffTable[8 * v7];
  v9 = 8 * v7 + 24433456;
  v22 = v8;
  EffSlot = this->CEffMgr::FindEffSlot(v8);
  v10 = 0;
  v11 = (_BYTE *)&this->_tail_000[2332];
  do
  {
    if ( *((_DWORD *)v11 + 1) == nVal && *(_DWORD *)v11 == v8 && v11[12] && v11[13] && *((_DWORD *)v11 + 4) )
    {
      *(_DWORD *)&this->_tail_000[20 * v10 + 2340] = nVal2;
      pEffObj = (char *)&this->_tail_000[20 * v10];
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
    v11 += 20;
  }
  while ( v10 < 2048 );
LABEL_8:
  v12 = 0;
  v13 = (_BYTE *)&this->_tail_000[2344];
  while ( *v13 )
  {
    ++v12;
    v13 += 20;
    if ( v12 >= 2048 )
    {
      ((void(*)(void))0)(this);
      if ( *(int *)&this->_tail_000[43292] >= 2048 )
      {
        this->CEffMgr::ReleaseCompletedEffects();
        if ( *(int *)&this->_tail_000[43292] >= 2048 )
          return -1;
      }
      goto LABEL_8;
    }
  }
  v16 = (char *)&this->_tail_000[72 * EffSlot];
  v17 = (char *)&this->_tail_000[20 * v12];
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
  ++*(_DWORD *)&this->_tail_000[43292];
  v17[2344] = 1;
  *(_DWORD *)(*((_DWORD *)v17 + 587) + 4) = (_DWORD)this;
  *((_DWORD *)v17 + 583) = v22;
  *((_DWORD *)v17 + 584) = nVal;
  *(_DWORD *)&this->_tail_000[20 * v12 + 2340] = nVal2;
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
        (**v20)((_DWORD)((_DWORD)(v20)), (int)(1));
      *((_DWORD *)v17 + 587) = 0;
    }
    v17[2344] = 0;
    *((_DWORD *)v17 + 583) = 0;
    *((_DWORD *)v17 + 584) = 0;
    v17[2345] = 0;
    --*(_DWORD *)&this->_tail_000[43292];
    return -1;
  }
  (*(void ( **)(int, int, int, int))(v19 + 8))(v9, nVal3, nVal4, nVal5);
  return v12;
}

// 0x004CDFD0
int CEffMgr::FindEffSlot(int nVal)
{
  int result; // eax
  _DWORD *i; // ecx

  result = 0;
  for ( i = &this->_tail_000[92]; !*((_BYTE *)i - 4) || *i != nVal; i += 18 )
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
  v3 = (char *)&g_EffTable[36];
  while ( !v3[176] || *(_DWORD *)v3 != nVal )
  {
    v3 += 280;
    ++result;
    if ( (int)v3 >= (int)((char *)&g_17A7BData.m_nEffParam1C + 4) )
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
    v1 = (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::OpenFile(aCbdataFlexeffD, 0x201u);
    if ( !v1 )
    {
      qmemcpy(
        pExceptionObject,
        (((Logger *)&ArgList))->Logger::FormatException(aCouldnTOpenEff, pSrc.m_fSize, 447),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    v2 = (void *)malloc(0x2C047u);
    v3 = (char *)malloc((size_t)&g_nLoadBufferSize);
    v4 = (char *)v3;
    if ( !v2 || !v3 )
      goto LABEL_8;
    (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v1, 0, 1);
    (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2, 0x2C047u, v1);
    (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::CloseFile(v1);
    if ( (int *)(((CPK *)&stru_DE9CB0))->CPK::DeCompress(v4, v2, 0x2C047u) != &g_nLoadBufferSize )
    {
      free(v2);
      free(v4);
LABEL_8:
      v8 = -1;
      ((OpenNULLFile *)&v5)->OpenNULLFile::OpenNULLFile();
      return;
    }
    qmemcpy(g_EffTable, v4, sizeof(g_EffTable));
    qmemcpy(&g_nSaveSlot0, v4 + 370720, 0x8834C0u);
    free(v2);
    free(v4);
    g_nCEffMgr_17A7B50 = 1;
    v8 = -1;
    ((OpenNULLFile *)&v5)->OpenNULLFile::OpenNULLFile();
  }
}

// 0x004CE2A0
CEffMgr::~CEffMgr()
{
  FILE *v1; // eax
  FILE *v2; // esi
  char pExceptionObject[1024]; // [esp+0x4] [ebp-0x800] BYREF
  char ArgList; // [esp+0x404] [ebp-0x400] BYREF

  v1 = fopen((const char *)FileName_0, Mode);
  v2 = (FILE *)v1;
  if ( !v1 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(aCouldnTOpenCbE, pSrc.m_fSize, 521),
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
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
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
  v8 = (int *)&g_nSaveSlotBase[v7];
  for ( nVal5a = (int *)((char *)&g_nSaveSlot1 + v7 * 4); ; ++nVal5a )
  {
    Effect = this->CEffMgr::CreateEffect(*nVal5a, v13, nVal2, nVal3, nVal4);
    if ( Effect == -1 )
      break;
    v10 = 8;
    do
    {
      if ( *((_BYTE *)v8 + 88) )
        (*(void ( **)(_DWORD, int *))(**(_DWORD **)&this->_tail_000[20 * Effect + 2348] + 48))(
          *(_DWORD *)&this->_tail_000[20 * Effect + 2348],
          v8);
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
  _BYTE *v3; // eax

  if ( nVal )
  {
    v2 = 0;
    v3 = (_BYTE *)&this->_tail_000[2344];
    do
    {
      if ( *((_DWORD *)v3 - 1) == nVal && *v3 && !v3[1] )
        break;
      ++v2;
      v3 += 20;
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
    v4 = (int *)&g_nSaveSlot1;
    while ( 2 )
    {
      v5 = 0;
      v6 = (int *)v4;
      do
      {
        if ( *v6 == v2 )
        {
          sprintf(Text, &unk_5D55AC, v3, v5);
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
char CEffMgr::CreateEff(const char *szEffTypeName, unsigned int dwRunID, float fx, float fy, float fz)
{
  const char *EditorTaskDescription; // eax
  int v6; // ecx
  unsigned __int8 v7; // al
  int v8; // ebp
  bool v9; // zf
  char *v10; // ecx

  LOBYTE(EditorTaskDescription) = g_EffTable[280 * (_DWORD)szEffTypeName + 212];
  if ( (_BYTE)EditorTaskDescription )
  {
    v6 = 0;
    EditorTaskDescription = (const char *)&g_EffTable[212];
    while ( *EditorTaskDescription )
    {
      EditorTaskDescription += 280;
      ++v6;
      if ( (int)EditorTaskDescription >= (int)&g_EffTaskEnd )
        return (char)EditorTaskDescription;
    }
    v7 = g_bEffSystemFlags;
    v8 = 280 * v6;
    v9 = (g_bEffSystemFlags & 1) == 0;
    qmemcpy(&g_EffTable[280 * v6], &g_EffTable[280 * (_DWORD)szEffTypeName], 0x118u);
    if ( v9 )
    {
      g_bEffSystemFlags = v7 | 1;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    (((UIWnd *)&g_EffTable[v8 + 4]))->UIWnd::BringWindowToTop();
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
LABEL_9:
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
LABEL_10:
    EditorTaskDescription = (((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)&g_EffTable[v8 + 4]);
    v10 = (char *)&g_EffTable[36];
    do
    {
      if ( v10[176] && *(const char **)v10 == EditorTaskDescription )
      {
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        (((UIWnd *)&g_EffTable[v8 + 4]))->UIWnd::BringWindowToTop();
        if ( (g_bEffSystemFlags & 1) != 0 )
          goto LABEL_10;
        goto LABEL_9;
      }
      v10 += 280;
    }
    while ( (int)v10 < (int)((char *)&g_17A7BData.m_nEffParam1C + 4) );
    *(_DWORD *)&g_EffTable[v8 + 36] = (_DWORD)EditorTaskDescription;
  }
  return (char)EditorTaskDescription;
}

// 0x004CEA80
char CEffMgr::ReleaseCompletedEffects()
{
  int v2; // ebx
  _DWORD *v3; // esi
  int v4; // eax
  _DWORD *v5; // edx

  v2 = 2048;
  v3 = (_DWORD *)&this->_tail_000[2348];
  do
  {
    LOBYTE(v4) = *((_BYTE *)v3 - 4);
    if ( (_BYTE)v4 )
    {
      (*(void ( **)(_DWORD))(*(_DWORD *)*v3 + 12))(*v3);
      if ( !*((_BYTE *)v3 - 2) && !(*(unsigned __int8 ( **)(_DWORD))(*(_DWORD *)*v3 + 32))(*v3) && *v3 )
        (**(void ( ***)(_DWORD, int))*v3)((_DWORD)(*v3), (int)(1));
      *v3 = 0;
      v4 = *(_DWORD *)&this->_tail_000[43292] - 1;
      v5 = (_DWORD *)(v3 - 4);
      *(_DWORD *)&this->_tail_000[43292] = v4;
      *v5 = 0;
      v5[1] = 0;
      v5[2] = 0;
      v5[3] = 0;
      *v3 = 0;
    }
    v3 += 5;
    --v2;
  }
  while ( v2 );
  return v4;
}

// 0x004CEDA0
unsigned int CEffMgr::RunEffGroup(char *nGroup, float fx, char *fy, float fz, unsigned int dwID)
{
  int v5; // ecx
  unsigned int v6; // ebp
  _BYTE *i; // eax
  int v9; // ebx
  char *v10; // edi
  RenderTarget2 *v11; // eax
  CEffBase **v12; // eax

  v6 = 0;
  for ( i = (_BYTE *)(v5 + 88); *i; i += 72 )
  {
    if ( (int)++v6 >= 32 )
      return -1;
  }
  v9 = v5 + 72 * v6;
  strcpy((char *)(v9 + 28), nGroup);
  v10 = fy;
  if ( !fy )
    v10 = unk_C10D38;
  strcpy((char *)(v9 + 58), v10);
  *(_BYTE *)(v9 + 88) = 1;
  v11 = (RenderTarget2 *)operator new(0x34u);
  if ( v11 )
    v12 = (((RenderTarget2 *)v11))->RenderTarget2::ClearTarget();
  else
    v12 = 0;
  *(_DWORD *)(v9 + 96) = (unsigned long)v12;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *(_DWORD *)(v9 + 92) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)nGroup);
  return v6;
}

// 0x004CEFE0
int CEffMgr::CreateSParticleEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  CEffMgr *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  strcpy(v7 + 28, *(void**)(pEffMgr));
  v8 = (CEffMgr *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = (CEffMgr *)unk_C10D38;
  strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (void *)operator new(0x30u);
  if ( v9 )
    v10 = sub_4D4EA0(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF100
bool CEffMgr::IsAllEffGroupStop(char *pszBuf, int nVal, char *pszBuf2)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  char *v8; // edi
  CEffCylinder *v9; // eax
  CEffCylinder **v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  strcpy(v7 + 28, pszBuf);
  v8 = (char *)pszBuf2;
  if ( !pszBuf2 )
    v8 = unk_C10D38;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffCylinder *)operator new(0x10C4u);
  if ( v9 )
    v10 = (((CEffCylinder *)v9))->CEffCylinder::Init();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = (unsigned long)v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pszBuf);
  return v4;
}

// 0x004CF220
int CEffMgr::CreateModelEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  CEffMgr *v8; // edi
  CEffModel *v9; // eax
  CEffModel *v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  strcpy(v7 + 28, *(void**)(pEffMgr));
  v8 = (CEffMgr *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = (CEffMgr *)unk_C10D38;
  strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (CEffModel *)operator new(0x68u);
  if ( v9 )
    v10 = (CEffModel *)v9->CEffModel::CEffModel();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = (unsigned long)v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF460
int CEffMgr::CreateEffectType3(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  CEffMgr *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  strcpy(v7 + 28, *(void**)(pEffMgr));
  v8 = (CEffMgr *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = (CEffMgr *)unk_C10D38;
  strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (void *)operator new(0x10B8u);
  if ( v9 )
    v10 = sub_4C9550(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF6A0
int CEffMgr::CreateEffectType4(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  CEffMgr *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  strcpy(v7 + 28, *(void**)(pEffMgr));
  v8 = (CEffMgr *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = (CEffMgr *)unk_C10D38;
  strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (void *)operator new(0x10D0u);
  if ( v9 )
    v10 = sub_4CB3A0(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CF7C0
void CEffMgr::CopyObjInGroup(char *nGroup, int nObj, char *nObjType)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v6; // ebx
  char *v7; // edi
  RenderTarget2 *v8; // eax
  CEffAudio **v9; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return;
  }
  v6 = (char *)&this->_tail_000[72 * v4];
  strcpy(v6 + 28, nGroup);
  v7 = (char *)nObjType;
  if ( !nObjType )
    v7 = unk_C10D38;
  strcpy(v6 + 58, v7);
  v6[88] = 1;
  v8 = (RenderTarget2 *)operator new(0x130u);
  if ( v8 )
    v9 = (((RenderTarget2 *)v8))->RenderTarget2::Reset();
  else
    v9 = 0;
  *((_DWORD *)v6 + 24) = (unsigned long)v9;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v6 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)nGroup);
}

// 0x004CF8E0
int CEffMgr::CreateEffectType5(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  CEffMgr *v8; // edi
  void *v9; // eax
  int v10; // eax

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  strcpy(v7 + 28, *(void**)(pEffMgr));
  v8 = (CEffMgr *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = (CEffMgr *)unk_C10D38;
  strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (void *)operator new(0x10B0u);
  if ( v9 )
    v10 = sub_4D3870(v9);
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004CFB20
int CEffMgr::CreateShockEffect(CEffMgr *pEffMgr, int nVal, CEffMgr *pEffMgr2)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  CEffMgr *v8; // edi
  CEffShock *v9; // eax
  const char *EditorTaskDescription; // eax
  int v11; // [esp+0x0] [ebp-0x1C]

  v4 = 0;
  for ( i = &this->_tail_000[88]; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)&this->_tail_000[72 * v4];
  strcpy(v7 + 28, *(void**)(pEffMgr));
  v8 = (CEffMgr *)pEffMgr2;
  if ( !pEffMgr2 )
    v8 = (CEffMgr *)unk_C10D38;
  strcpy(v7 + 58, *(void**)(v8));
  v7[88] = 1;
  v9 = (CEffShock *)operator new(0x30u);
  if ( v9 )
    EditorTaskDescription = (((CEffShock *)v9))->CEffShock::GetEditorTaskDescription(v11);
  else
    EditorTaskDescription = 0;
  *((_DWORD *)v7 + 24) = (unsigned long)EditorTaskDescription;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
    atexit(j_j_codecvt_base);
  }
  *((_DWORD *)v7 + 23) = (unsigned long)(((CEffSParticle *)&g_pCEffMgrBackup))->CEffSParticle::GetEditorTaskDescription((int)pEffMgr);
  return v4;
}

// 0x004D22F0
int CEffMgr::UpdateKeyframe(int nVal)
{
  int v3; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  float v7; // st7
  int v8; // eax
  int v9; // ebx
  float *v10; // eax
  float *v11; // ecx
  float v12; // st7
  float *v13; // ecx
  float v14; // st7
  int v15; // ecx
  float v16; // st7
  float *v17; // ecx
  float v18; // st7
  float *v19; // ecx
  float v20; // st7
  unsigned __int16 v21; // cx
  int v22; // eax
  int v23; // ebx
  int v24; // edx
  float *v25; // ecx
  float v26; // st7
  int v27; // ecx
  float v28; // st7
  float *v29; // ecx
  float v30; // st7
  float *v31; // ecx
  float v32; // st7
  float *v33; // ecx
  float v34; // st7
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

  v3 = *(_DWORD *)&this->_tail_000[24] + 152 * *(_DWORD *)&this->_tail_000[28];
  v4 = *(_DWORD *)&this->_tail_000[32];
  v5 = 9 * v4;
  LOBYTE(v4) = *(_BYTE *)(*(_DWORD *)v3 + 72 * v4 + 65);
  v6 = *(_DWORD *)v3 + 8 * v5;
  v49 = v6;
  if ( !(_BYTE)v4 )
    *(_BYTE *)(v6 + 65) = 1;
  v7 = *(float *)&this->_tail_000[16] - *(float *)(v6 + 16);
  v50 = *(float *)&this->_tail_000[20];
  if ( v7 > *(float *)(v6 + 24) )
    v50 = v50 - (v7 - *(float *)(v6 + 24));
  memset(&v43, 0, sizeof(v43));
  memset(&v42, 0, sizeof(v42));
  memset(&v41, 0, sizeof(v41));
  if ( *(_BYTE *)(v3 + 114) )
  {
    v8 = *(_DWORD *)&this->_tail_000[72];
    if ( v8 != -1 )
    {
      v9 = 80 * v8;
      *(float *)(80 * v8 + *(_DWORD *)&this->_tail_000[156] + 28) = v50 * *(float *)(v3 + 24)
                                                                  + *(float *)(80 * v8
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 28);
      *(float *)(80 * v8 + *(_DWORD *)&this->_tail_000[156] + 32) = v50 * *(float *)(v3 + 116)
                                                                  + *(float *)(80 * v8
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 32);
      v10 = (float *)(80 * v8 + *(_DWORD *)&this->_tail_000[156] + 48);
      *v10 = v50 * *(float *)(v3 + 40) + *v10;
      if ( *(float *)(v3 + 68) != 0.0f )
        *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 48) = v50 * *(float *)(v3 + 68)
                                                               + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 48);
      *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 52) = v50 * *(float *)(v3 + 64)
                                                             + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 52);
      *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 56) = v50 * *(float *)(v3 + 72)
                                                             + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 56);
      if ( *(float *)(v3 + 80) != 0.0f
        || *(float *)(v3 + 84) != 0.0f
        || *(float *)(v3 + 92) != 0.0f
        || *(float *)(v3 + 88) != 0.0f )
      {
        *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 60) = v50 * *(float *)(v3 + 80)
                                                               + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 60);
        *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 64) = v50 * *(float *)(v3 + 84)
                                                               + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 64);
        *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 68) = v50 * *(float *)(v3 + 88)
                                                               + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 68);
        *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 72) = v50 * *(float *)(v3 + 92)
                                                               + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 72);
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v11 = (float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 60);
        if ( *v11 <= 255.0f )
        {
          if ( *v11 >= 0.0f )
            v12 = *v11;
          else
            v12 = 0.0f;
        }
        else
        {
          v12 = 255.0f;
        }
        *v11 = v12;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v13 = (float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 64);
        if ( *v13 <= 255.0f )
        {
          if ( *v13 >= 0.0f )
            v14 = *v13;
          else
            v14 = 0.0f;
        }
        else
        {
          v14 = 255.0f;
        }
        *v13 = v14;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v15 = *(_DWORD *)&this->_tail_000[156];
        v16 = *(float *)(v9 + v15 + 68);
        v17 = (float *)(v9 + v15 + 68);
        if ( v16 <= 255.0f )
        {
          if ( *v17 >= 0.0f )
            v18 = *v17;
          else
            v18 = 0.0f;
        }
        else
        {
          v18 = 255.0f;
        }
        *v17 = v18;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v19 = (float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 72);
        if ( *v19 <= 255.0f )
        {
          if ( *v19 >= 0.0f )
            v20 = *v19;
          else
            v20 = 0.0f;
        }
        else
        {
          v20 = 255.0f;
        }
        *v19 = v20;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v48 = *(int *)(v9 + *(_DWORD *)&this->_tail_000[156] + 60);
        LODWORD(v47) = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v48 = *(int *)(v9 + *(_DWORD *)&this->_tail_000[156] + 64);
        LODWORD(v46) = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v48 = *(int *)(v9 + *(_DWORD *)&this->_tail_000[156] + 68);
        LODWORD(v45) = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        v48 = *(int *)(v9 + *(_DWORD *)&this->_tail_000[156] + 72);
        v48 = (int)*(float *)&v48;
        if ( (g_bEffSystemFlags & 1) == 0 )
        {
          g_bEffSystemFlags |= 1u;
          (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
          atexit(j_j_codecvt_base);
        }
        HIBYTE(v21) = LOBYTE(v47);
        LOBYTE(v21) = LOBYTE(v46);
        *(_DWORD *)(v9 + *(_DWORD *)&this->_tail_000[156] + 76) = (unsigned __int8)v48
                                                                | ((LOBYTE(v45) | (v21 << 8)) << 8);
        *(_DWORD *)(*(_DWORD *)&this->_tail_000[160] + 68 * *(_DWORD *)(v9 + *(_DWORD *)&this->_tail_000[156]) + 64) = *(_DWORD *)(v9 + *(_DWORD *)&this->_tail_000[156] + 76);
      }
      *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 16) = v50 * *(float *)(v3 + 28)
                                                             + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 16);
      *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 20) = v50 * *(float *)(v3 + 32)
                                                             + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 20);
      *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 24) = v50 * *(float *)(v3 + 36)
                                                             + *(float *)(v9 + *(_DWORD *)&this->_tail_000[156] + 24);
      (((gbMatrix4 *)&v40))->gbMatrix4::LoadIdentity();
      v43 = *(gbVec3D *)(v3 + 44);
      (((gbVec3D *)&v43))->gbVec3D::Normalize();
      v38 = (*(float *)&this->_tail_000[16] - *(float *)(v49 + 16)) * *(float *)(v3 + 60);
      (((gbMatrix4 *)&v40))->gbMatrix4::SetAxisAngle(&v43, v38);
      v42.z = *(float *)(v3 + 56);
      v42.x = 0.0;
      v42.y = 0.0;
      (((gbMatrix4 *)&v40))->gbMatrix4::Rotate(&v42, &v41);
      *(gbVec3D *)(v9 + *(_DWORD *)&this->_tail_000[156] + 36) = v41;
    }
  }
  else
  {
    v22 = *(_DWORD *)&this->_tail_000[60];
    *(float *)&v48 = 0.0;
    if ( v22 > 0 )
    {
      v23 = 0;
      do
      {
        v24 = *(_DWORD *)&this->_tail_000[156];
        if ( *(_BYTE *)(v23 + v24 + 4) )
        {
          *(float *)(v23 + v24 + 28) = v50 * *(float *)(v3 + 24) + *(float *)(v23 + v24 + 28);
          *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 32) = v50 * *(float *)(v3 + 116)
                                                                  + *(float *)(v23
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 32);
          *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 48) = v50 * *(float *)(v3 + 40)
                                                                  + *(float *)(v23
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 48);
          if ( *(float *)(v3 + 68) != 0.0f )
            *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 48) = v50 * *(float *)(v3 + 68)
                                                                    + *(float *)(v23
                                                                               + *(_DWORD *)&this->_tail_000[156]
                                                                               + 48);
          *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 52) = v50 * *(float *)(v3 + 64)
                                                                  + *(float *)(v23
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 52);
          *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 56) = v50 * *(float *)(v3 + 72)
                                                                  + *(float *)(v23
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 56);
          if ( *(float *)(v3 + 80) != 0.0f
            || *(float *)(v3 + 84) != 0.0f
            || *(float *)(v3 + 92) != 0.0f
            || *(float *)(v3 + 88) != 0.0f )
          {
            *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 60) = v50 * *(float *)(v3 + 80)
                                                                    + *(float *)(v23
                                                                               + *(_DWORD *)&this->_tail_000[156]
                                                                               + 60);
            *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 64) = v50 * *(float *)(v3 + 84)
                                                                    + *(float *)(v23
                                                                               + *(_DWORD *)&this->_tail_000[156]
                                                                               + 64);
            *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 68) = v50 * *(float *)(v3 + 88)
                                                                    + *(float *)(v23
                                                                               + *(_DWORD *)&this->_tail_000[156]
                                                                               + 68);
            *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 72) = v50 * *(float *)(v3 + 92)
                                                                    + *(float *)(v23
                                                                               + *(_DWORD *)&this->_tail_000[156]
                                                                               + 72);
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v25 = (float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 60);
            if ( *v25 <= 255.0f )
            {
              if ( *v25 >= 0.0f )
                v26 = *v25;
              else
                v26 = 0.0f;
            }
            else
            {
              v26 = 255.0f;
            }
            *v25 = v26;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v27 = *(_DWORD *)&this->_tail_000[156];
            v28 = *(float *)(v23 + v27 + 64);
            v29 = (float *)(v23 + v27 + 64);
            if ( v28 <= 255.0f )
            {
              if ( *v29 >= 0.0f )
                v30 = *v29;
              else
                v30 = 0.0f;
            }
            else
            {
              v30 = 255.0f;
            }
            *v29 = v30;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v31 = (float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 68);
            if ( *v31 <= 255.0f )
            {
              if ( *v31 >= 0.0f )
                v32 = *v31;
              else
                v32 = 0.0f;
            }
            else
            {
              v32 = 255.0f;
            }
            *v31 = v32;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v33 = (float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 72);
            if ( *v33 <= 255.0f )
            {
              if ( *v33 >= 0.0f )
                v34 = *v33;
              else
                v34 = 0.0f;
            }
            else
            {
              v34 = 255.0f;
            }
            *v33 = v34;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v45 = *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 60) + 12582912.0f;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v46 = *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 64) + 12582912.0f;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v47 = *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 68) + 12582912.0f;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            v44 = *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 72) + 12582912.0f;
            if ( (g_bEffSystemFlags & 1) == 0 )
            {
              g_bEffSystemFlags |= 1u;
              (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
              atexit(j_j_codecvt_base);
            }
            HIBYTE(v35) = LOBYTE(v45);
            LOBYTE(v35) = LOBYTE(v46);
            *(_DWORD *)(v23 + *(_DWORD *)&this->_tail_000[156] + 76) = LOBYTE(v44) | ((LOBYTE(v47) | (v35 << 8)) << 8);
            *(_DWORD *)(*(_DWORD *)&this->_tail_000[160] + 68 * *(_DWORD *)(v23 + *(_DWORD *)&this->_tail_000[156]) + 64) = *(_DWORD *)(v23 + *(_DWORD *)&this->_tail_000[156] + 76);
          }
          *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 16) = v50 * *(float *)(v3 + 28)
                                                                  + *(float *)(v23
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 16);
          *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 20) = v50 * *(float *)(v3 + 32)
                                                                  + *(float *)(v23
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 20);
          *(float *)(v23 + *(_DWORD *)&this->_tail_000[156] + 24) = v50 * *(float *)(v3 + 36)
                                                                  + *(float *)(v23
                                                                             + *(_DWORD *)&this->_tail_000[156]
                                                                             + 24);
          (((gbMatrix4 *)&v40))->gbMatrix4::LoadIdentity();
          v43 = *(gbVec3D *)(v3 + 44);
          (((gbVec3D *)&v43))->gbVec3D::Normalize();
          v39 = (*(float *)&this->_tail_000[16] - *(float *)(v49 + 16)) * *(float *)(v3 + 60);
          (((gbMatrix4 *)&v40))->gbMatrix4::SetAxisAngle(&v43, v39);
          v42.z = *(float *)(v3 + 56);
          v42.x = 0.0;
          v42.y = 0.0;
          (((gbMatrix4 *)&v40))->gbMatrix4::Rotate(&v42, &v41);
          *(gbVec3D *)(v23 + *(_DWORD *)&this->_tail_000[156] + 36) = v41;
        }
        v36 = *(_DWORD *)&this->_tail_000[60];
        v23 += 80;
        ++v48;
      }
      while ( v48 < v36 );
    }
  }
  if ( *(_BYTE *)(v49 + 66) == 1 || *(float *)&this->_tail_000[16] - *(float *)(v49 + 16) >= *(float *)(v49 + 24) )
    *(_DWORD *)(v49 + 8) = 4;
  return 0;
}

// 0x004D58A0
int * CEffMgr::Reset()
{
  sub_4D5A00();
  *(_DWORD *)&this->_tail_000[1024] = 1;
  *(_DWORD *)&this->_tail_000[1028] = timeGetTime();
  *(_DWORD *)&this->_tail_000[1032] = 0;
  return (int *)this;
}
