#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SceneInfo.h"

// Forward declarations for unnamed functions
int sub_4A13E0(...);

// 0x00443CE0
char SceneInfo::ProcessCollision(int nVal, int nVal2)
{
  int v4; // eax
  int v5; // ebp
  int v6; // edi
  int v7; // ebx
  int v8; // edi
  double v9; // st7
  int v10; // ecx
  int v11; // ebx
  int v12; // edi
  int v13; // eax
  int v14; // ebx
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  int v19; // edi
  bool v21; // [esp+0x12] [ebp-0x6]
  bool v22; // [esp+0x13] [ebp-0x5]
  int v23; // [esp+0x14] [ebp-0x4]
  int v24; // [esp+0x14] [ebp-0x4]
  int v25; // [esp+0x14] [ebp-0x4]

  v4 = *(_DWORD *)&this->mdl[12];
  LOBYTE(this->reserve[3]) = 0;
  v5 = *(_DWORD *)&this->mdl[20];
  v6 = nVal2;
  v21 = nVal2 < *(_DWORD *)&this->mdl[16];
  v22 = nVal2 > *(_DWORD *)&this->mdl[24];
  if ( nVal >= v4 )
  {
    if ( nVal <= v5 )
      goto LABEL_14;
    v10 = nVal - v5;
    v11 = 0;
    if ( (int)this->reserve[0] > 0 )
    {
      v12 = 0;
      do
      {
        *(float *)(v12 + this->reserve[1] + 36) = *(float *)(v12 + this->reserve[1] + 36) - (double)(nVal - v5);
        *(_DWORD *)(v12 + this->reserve[1] + 4) = (__int64)*(float *)(v12 + this->reserve[1] + 36);
        *(_DWORD *)(v12 + this->reserve[1] + 12) = *(_DWORD *)(v12 + this->reserve[1] + 4) + 256;
        *(_DWORD *)(v12 + this->reserve[1] + 48) = *(_DWORD *)(v12 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[12];
        ++v11;
        *(_DWORD *)(v12 + this->reserve[1] + 52) = *(_DWORD *)(v12 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[20];
        v12 += 80;
      }
      while ( v11 < (int)this->reserve[0] );
      v6 = nVal2;
      v10 = nVal - v5;
    }
    v9 = (double)-v10;
  }
  else
  {
    v7 = 0;
    v23 = v4 - nVal;
    if ( (int)this->reserve[0] > 0 )
    {
      v8 = 0;
      do
      {
        *(float *)(v8 + this->reserve[1] + 36) = (double)v23 + *(float *)(v8 + this->reserve[1] + 36);
        *(_DWORD *)(v8 + this->reserve[1] + 4) = (__int64)*(float *)(v8 + this->reserve[1] + 36);
        *(_DWORD *)(v8 + this->reserve[1] + 12) = *(_DWORD *)(v8 + this->reserve[1] + 4) + 256;
        *(_DWORD *)(v8 + this->reserve[1] + 48) = *(_DWORD *)(v8 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[12];
        ++v7;
        *(_DWORD *)(v8 + this->reserve[1] + 52) = *(_DWORD *)(v8 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[20];
        v8 += 80;
      }
      while ( v7 < (int)this->reserve[0] );
      v6 = nVal2;
    }
    v9 = (double)v23;
  }
  *(float *)&this->reserve[4] = v9;
LABEL_14:
  if ( v21 )
  {
    v13 = this->reserve[0];
    v14 = 0;
    v24 = *(_DWORD *)&this->mdl[16] - v6;
    if ( v13 > 0 )
    {
      v15 = 0;
      do
      {
        *(float *)(v15 + this->reserve[1] + 40) = (double)v24 + *(float *)(v15 + this->reserve[1] + 40);
        *(_DWORD *)(v15 + this->reserve[1] + 8) = (__int64)*(float *)(v15 + this->reserve[1] + 40);
        *(_DWORD *)(v15 + this->reserve[1] + 16) = *(_DWORD *)(v15 + this->reserve[1] + 8) + 256;
        *(_DWORD *)(v15 + this->reserve[1] + 56) = *(_DWORD *)(v15 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[16];
        ++v14;
        *(_DWORD *)(v15 + this->reserve[1] + 60) = *(_DWORD *)(v15 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[24];
        v13 = this->reserve[0];
        v15 += 80;
      }
      while ( v14 < v13 );
    }
    LOBYTE(this->reserve[3]) = 1;
    *(float *)&this->reserve[5] = (float)v24;
  }
  else
  {
    LOBYTE(v13) = v22;
    if ( v22 )
    {
      v16 = *(_DWORD *)&this->mdl[24];
      if ( v6 <= v16 )
      {
        v25 = 0;
        v17 = 0;
      }
      else
      {
        v17 = v6 - v16;
        v25 = v17;
      }
      v18 = 0;
      if ( (int)this->reserve[0] > 0 )
      {
        v19 = 0;
        do
        {
          *(float *)(v19 + this->reserve[1] + 40) = *(float *)(v19 + this->reserve[1] + 40) - (double)v25;
          *(_DWORD *)(v19 + this->reserve[1] + 8) = (__int64)*(float *)(v19 + this->reserve[1] + 40);
          *(_DWORD *)(v19 + this->reserve[1] + 16) = *(_DWORD *)(v19 + this->reserve[1] + 8) + 256;
          *(_DWORD *)(v19 + this->reserve[1] + 56) = *(_DWORD *)(v19 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[16];
          ++v18;
          *(_DWORD *)(v19 + this->reserve[1] + 60) = *(_DWORD *)(v19 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[24];
          v19 += 80;
        }
        while ( v18 < (int)this->reserve[0] );
        v17 = v25;
      }
      v13 = -v17;
      *(float *)&this->reserve[5] = (float)v13;
    }
    LOBYTE(this->reserve[3]) = 1;
  }
  return v13;
}

// 0x00443FC0
char SceneInfo::ProcessSceneChange(float fVal, int nVal, int nVal2)
{
  int v5; // eax
  int v6; // ecx
  int v7; // ebx
  int v8; // edi
  int v9; // ebp
  int v10; // edx
  int v11; // edx
  float v12; // edi
  float v13; // edi

  if ( (g_bSceneChangeFlags & 1) == 0 )
  {
    g_bSceneChangeFlags |= 1u;
    atexit((void ( *)())sub_4A13E0);
  }
  LOBYTE(v5) = g_nUILayoutFlags;
  if ( g_nUILayoutFlags <= 0 )
  {
    v6 = *(_DWORD *)&this->mdl[28];
    v7 = *(_DWORD *)&this->type;
    v8 = *(_DWORD *)&this->mdl[12];
    v9 = v6 / 3;
    v10 = v7 / 3;
    v5 = -1;
    if ( nVal < v8 + v6 - 1 )
    {
      if ( nVal <= v8 )
      {
        if ( nVal2 >= v10 )
          v5 = (nVal2 >= 2 * v10) + 2;
        else
          v5 = 1;
      }
    }
    else if ( nVal2 >= v10 )
    {
      v5 = (nVal2 < 2 * v10) + 5;
    }
    else
    {
      v5 = 7;
    }
    v11 = *(_DWORD *)&this->mdl[16];
    if ( nVal2 < v11 + v7 - 1 )
    {
      if ( nVal2 <= v11 )
      {
        if ( nVal >= v9 )
          v5 = nVal >= 2 * v9 ? 7 : 0;
        else
          v5 = 1;
      }
    }
    else if ( nVal >= v9 )
    {
      v5 = (nVal >= 2 * v9) + 4;
    }
    else
    {
      v5 = 3;
    }
    switch ( v5 )
    {
      case 0:
        LOBYTE(v5) = this->CheckHitBottom(fVal);
        break;
      case 1:
        v12 = fVal;
        LOBYTE(v5) = this->CheckBoundsBottomCombo(fVal);
        if ( !(_BYTE)v5 )
        {
          LOBYTE(v5) = this->UpdateScaling(fVal);
          if ( !(_BYTE)v5 )
            goto LABEL_36;
        }
        break;
      case 2:
        LOBYTE(v5) = this->UpdateScaling(fVal);
        break;
      case 3:
        v13 = fVal;
        LOBYTE(v5) = this->CheckBoundsRightCombo(fVal);
        if ( !(_BYTE)v5 )
        {
          LOBYTE(v5) = this->UpdateScaling(fVal);
          goto LABEL_28;
        }
        break;
      case 4:
        LOBYTE(v5) = this->CheckHitRight(fVal);
        break;
      case 5:
        v13 = fVal;
        LOBYTE(v5) = this->CheckBoundsHorizontal(fVal);
        if ( !(_BYTE)v5 )
        {
          LOBYTE(v5) = this->CheckHitLeft(fVal);
LABEL_28:
          if ( !(_BYTE)v5 )
            LOBYTE(v5) = this->CheckHitRight(v13);
        }
        break;
      case 6:
        LOBYTE(v5) = this->CheckHitLeft(fVal);
        break;
      case 7:
        v12 = fVal;
        LOBYTE(v5) = this->CheckBoundsLeftCombo(fVal);
        if ( !(_BYTE)v5 )
        {
          LOBYTE(v5) = this->CheckHitLeft(fVal);
          if ( !(_BYTE)v5 )
LABEL_36:
            LOBYTE(v5) = this->CheckHitBottom(v12);
        }
        break;
      default:
        return v5;
    }
  }
  return v5;
}

// 0x004441E0
bool SceneInfo::CheckHitLeft(float fVal)
{
  int v3; // edi
  bool result; // al
  int i; // ebx
  double v6; // st7

  v3 = 0;
  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  result = ((CCBFiveNimbusWindow *)this)->IsHitLeft(fVal);
  if ( result )
  {
    for ( i = 0; i < (int)this->reserve[0]; v3 += 80 )
    {
      *(float *)(v3 + this->reserve[1] + 36) = *(float *)(v3 + this->reserve[1] + 36)
                                             - fVal * *((float *)this + 36) * *(float *)&this->reserve[2];
      *(_DWORD *)(v3 + this->reserve[1] + 4) = (__int64)*(float *)(v3 + this->reserve[1] + 36);
      *(_DWORD *)(v3 + this->reserve[1] + 12) = *(_DWORD *)(v3 + this->reserve[1] + 4) + 256;
      *(_DWORD *)(v3 + this->reserve[1] + 48) = *(_DWORD *)(v3 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[12];
      ++i;
      *(_DWORD *)(v3 + this->reserve[1] + 52) = *(_DWORD *)(v3 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[20];
    }
    v6 = fVal * *((float *)this + 36);
    this->reserve[5] = 0;
    LOBYTE(this->reserve[3]) = 1;
    *(float *)&this->reserve[4] = -(v6 * *(float *)&this->reserve[2]);
  }
  return result;
}

// 0x004442B0
bool SceneInfo::UpdateScaling(float fVal)
{
  int v3; // edi
  bool result; // al
  int i; // ebx
  double v6; // st7

  v3 = 0;
  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  result = ((CCBFiveNimbusWindow *)this)->IsAboveThreshold(fVal);
  if ( result )
  {
    for ( i = 0; i < (int)this->reserve[0]; v3 += 80 )
    {
      *(float *)(v3 + this->reserve[1] + 36) = fVal * *((float *)this + 36) * *(float *)&this->reserve[2]
                                             + *(float *)(v3 + this->reserve[1] + 36);
      *(_DWORD *)(v3 + this->reserve[1] + 4) = (__int64)*(float *)(v3 + this->reserve[1] + 36);
      *(_DWORD *)(v3 + this->reserve[1] + 12) = *(_DWORD *)(v3 + this->reserve[1] + 4) + 256;
      *(_DWORD *)(v3 + this->reserve[1] + 48) = *(_DWORD *)(v3 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[12];
      ++i;
      *(_DWORD *)(v3 + this->reserve[1] + 52) = *(_DWORD *)(v3 + this->reserve[1] + 4) - *(_DWORD *)&this->mdl[20];
    }
    v6 = fVal * *((float *)this + 36);
    this->reserve[5] = 0;
    LOBYTE(this->reserve[3]) = 1;
    *(float *)&this->reserve[4] = v6 * *(float *)&this->reserve[2];
  }
  return result;
}

// 0x00444380
bool SceneInfo::CheckHitRight(float fVal)
{
  int v3; // edi
  bool result; // al
  int i; // ebx
  double v6; // st7

  v3 = 0;
  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  result = ((CCBFiveNimbusWindow *)this)->IsHitRight(fVal);
  if ( result )
  {
    for ( i = 0; i < (int)this->reserve[0]; v3 += 80 )
    {
      *(float *)(v3 + this->reserve[1] + 40) = *(float *)(v3 + this->reserve[1] + 40)
                                             - fVal * *((float *)this + 36) * *(float *)&this->reserve[2];
      *(_DWORD *)(v3 + this->reserve[1] + 8) = (__int64)*(float *)(v3 + this->reserve[1] + 40);
      *(_DWORD *)(v3 + this->reserve[1] + 16) = *(_DWORD *)(v3 + this->reserve[1] + 8) + 256;
      *(_DWORD *)(v3 + this->reserve[1] + 56) = *(_DWORD *)(v3 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[16];
      ++i;
      *(_DWORD *)(v3 + this->reserve[1] + 60) = *(_DWORD *)(v3 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[24];
    }
    v6 = fVal * *((float *)this + 36);
    this->reserve[4] = 0;
    LOBYTE(this->reserve[3]) = 1;
    *(float *)&this->reserve[5] = -(v6 * *(float *)&this->reserve[2]);
  }
  return result;
}

// 0x00444450
bool SceneInfo::CheckHitBottom(float fVal)
{
  int v3; // edi
  bool result; // al
  int i; // ebx
  double v6; // st7

  v3 = 0;
  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  result = ((CCBFiveNimbusWindow *)this)->IsHitBottom(fVal);
  if ( result )
  {
    for ( i = 0; i < (int)this->reserve[0]; v3 += 80 )
    {
      *(float *)(v3 + this->reserve[1] + 40) = fVal * *((float *)this + 36) * *(float *)&this->reserve[2]
                                             + *(float *)(v3 + this->reserve[1] + 40);
      *(_DWORD *)(v3 + this->reserve[1] + 8) = (__int64)*(float *)(v3 + this->reserve[1] + 40);
      *(_DWORD *)(v3 + this->reserve[1] + 16) = *(_DWORD *)(v3 + this->reserve[1] + 8) + 256;
      *(_DWORD *)(v3 + this->reserve[1] + 56) = *(_DWORD *)(v3 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[16];
      ++i;
      *(_DWORD *)(v3 + this->reserve[1] + 60) = *(_DWORD *)(v3 + this->reserve[1] + 8) - *(_DWORD *)&this->mdl[24];
    }
    v6 = fVal * *((float *)this + 36);
    this->reserve[4] = 0;
    LOBYTE(this->reserve[3]) = 1;
    *(float *)&this->reserve[5] = v6 * *(float *)&this->reserve[2];
  }
  return result;
}

// 0x00444520
char SceneInfo::CheckBoundsHorizontal(float fVal)
{
  int v4; // ebp
  int v5; // edi
  double v6; // st7
  double v7; // st7

  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  if ( !((CCBFiveNimbusWindow *)this)->IsHitLeft(fVal)
    || !((CCBFiveNimbusWindow *)this)->IsHitRight(fVal) )
  {
    return 0;
  }
  v4 = 0;
  if ( (int)this->reserve[0] > 0 )
  {
    v5 = 0;
    do
    {
      *(float *)(this->reserve[1] + v5 + 36) = *(float *)(this->reserve[1] + v5 + 36)
                                             - fVal * *((float *)this + 36) * *(float *)&this->reserve[2];
      *(float *)(this->reserve[1] + v5 + 40) = *(float *)(this->reserve[1] + v5 + 40)
                                             - fVal * *((float *)this + 36) * *(float *)&this->reserve[2];
      *(_DWORD *)(this->reserve[1] + v5 + 4) = (__int64)*(float *)(this->reserve[1] + v5 + 36);
      *(_DWORD *)(this->reserve[1] + v5 + 8) = (__int64)*(float *)(this->reserve[1] + v5 + 40);
      *(_DWORD *)(this->reserve[1] + v5 + 12) = *(_DWORD *)(this->reserve[1] + v5 + 4) + 256;
      *(_DWORD *)(v5 + this->reserve[1] + 16) = *(_DWORD *)(v5 + this->reserve[1] + 8) + 256;
      *(_DWORD *)(this->reserve[1] + v5 + 48) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[12];
      *(_DWORD *)(this->reserve[1] + v5 + 52) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[20];
      *(_DWORD *)(this->reserve[1] + v5 + 56) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[16];
      ++v4;
      *(_DWORD *)(this->reserve[1] + v5 + 60) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[24];
      v5 += 80;
    }
    while ( v4 < (int)this->reserve[0] );
  }
  v6 = fVal * *((float *)this + 36);
  LOBYTE(this->reserve[3]) = 1;
  v7 = -(v6 * *(float *)&this->reserve[2]);
  *(float *)&this->reserve[4] = v7;
  *(float *)&this->reserve[5] = v7;
  return 1;
}

// 0x00444660
char SceneInfo::CheckBoundsLeftCombo(float fVal)
{
  int v4; // ebp
  int v5; // edi
  double v6; // st7
  double v7; // st7

  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  if ( !((CCBFiveNimbusWindow *)this)->IsHitLeft(fVal)
    || !((CCBFiveNimbusWindow *)this)->IsHitBottom(fVal) )
  {
    return 0;
  }
  v4 = 0;
  if ( (int)this->reserve[0] > 0 )
  {
    v5 = 0;
    do
    {
      *(float *)(this->reserve[1] + v5 + 36) = *(float *)(this->reserve[1] + v5 + 36)
                                             - fVal * *((float *)this + 36) * *(float *)&this->reserve[2];
      *(float *)(this->reserve[1] + v5 + 40) = fVal * *((float *)this + 36) * *(float *)&this->reserve[2]
                                             + *(float *)(this->reserve[1] + v5 + 40);
      *(_DWORD *)(this->reserve[1] + v5 + 4) = (__int64)*(float *)(this->reserve[1] + v5 + 36);
      *(_DWORD *)(this->reserve[1] + v5 + 8) = (__int64)*(float *)(this->reserve[1] + v5 + 40);
      *(_DWORD *)(this->reserve[1] + v5 + 12) = *(_DWORD *)(this->reserve[1] + v5 + 4) + 256;
      *(_DWORD *)(v5 + this->reserve[1] + 16) = *(_DWORD *)(v5 + this->reserve[1] + 8) + 256;
      *(_DWORD *)(this->reserve[1] + v5 + 48) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[12];
      *(_DWORD *)(this->reserve[1] + v5 + 52) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[20];
      *(_DWORD *)(this->reserve[1] + v5 + 56) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[16];
      ++v4;
      *(_DWORD *)(this->reserve[1] + v5 + 60) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[24];
      v5 += 80;
    }
    while ( v4 < (int)this->reserve[0] );
  }
  v6 = fVal * *((float *)this + 36);
  LOBYTE(this->reserve[3]) = 1;
  v7 = v6 * *(float *)&this->reserve[2];
  *(float *)&this->reserve[4] = -v7;
  *(float *)&this->reserve[5] = v7;
  return 1;
}

// 0x004447A0
char SceneInfo::CheckBoundsRightCombo(float fVal)
{
  int v4; // ebp
  int v5; // edi
  double v6; // st7
  double v7; // st7

  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  if ( !((CCBFiveNimbusWindow *)this)->IsAboveThreshold(fVal)
    || !((CCBFiveNimbusWindow *)this)->IsHitRight(fVal) )
  {
    return 0;
  }
  v4 = 0;
  if ( (int)this->reserve[0] > 0 )
  {
    v5 = 0;
    do
    {
      *(float *)(this->reserve[1] + v5 + 36) = fVal * *((float *)this + 36) * *(float *)&this->reserve[2]
                                             + *(float *)(this->reserve[1] + v5 + 36);
      *(float *)(this->reserve[1] + v5 + 40) = *(float *)(this->reserve[1] + v5 + 40)
                                             - fVal * *((float *)this + 36) * *(float *)&this->reserve[2];
      *(_DWORD *)(this->reserve[1] + v5 + 4) = (__int64)*(float *)(this->reserve[1] + v5 + 36);
      *(_DWORD *)(this->reserve[1] + v5 + 8) = (__int64)*(float *)(this->reserve[1] + v5 + 40);
      *(_DWORD *)(this->reserve[1] + v5 + 12) = *(_DWORD *)(this->reserve[1] + v5 + 4) + 256;
      *(_DWORD *)(v5 + this->reserve[1] + 16) = *(_DWORD *)(v5 + this->reserve[1] + 8) + 256;
      *(_DWORD *)(this->reserve[1] + v5 + 48) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[12];
      *(_DWORD *)(this->reserve[1] + v5 + 52) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[20];
      *(_DWORD *)(this->reserve[1] + v5 + 56) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[16];
      ++v4;
      *(_DWORD *)(this->reserve[1] + v5 + 60) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[24];
      v5 += 80;
    }
    while ( v4 < (int)this->reserve[0] );
  }
  v6 = fVal * *((float *)this + 36);
  LOBYTE(this->reserve[3]) = 1;
  v7 = v6 * *(float *)&this->reserve[2];
  *(float *)&this->reserve[4] = v7;
  *(float *)&this->reserve[5] = -v7;
  return 1;
}

// 0x004448E0
char SceneInfo::CheckBoundsBottomCombo(float fVal)
{
  int v4; // ebp
  int v5; // edi
  double v6; // st7
  double v7; // st7

  LOBYTE(this->reserve[3]) = 0;
  this->reserve[5] = 0;
  this->reserve[4] = 0;
  if ( !((CCBFiveNimbusWindow *)this)->IsAboveThreshold(fVal)
    || !((CCBFiveNimbusWindow *)this)->IsHitBottom(fVal) )
  {
    return 0;
  }
  v4 = 0;
  if ( (int)this->reserve[0] > 0 )
  {
    v5 = 0;
    do
    {
      *(float *)(this->reserve[1] + v5 + 36) = fVal * *((float *)this + 36) * *(float *)&this->reserve[2]
                                             + *(float *)(this->reserve[1] + v5 + 36);
      *(float *)(this->reserve[1] + v5 + 40) = fVal * *((float *)this + 36) * *(float *)&this->reserve[2]
                                             + *(float *)(this->reserve[1] + v5 + 40);
      *(_DWORD *)(this->reserve[1] + v5 + 4) = (__int64)*(float *)(this->reserve[1] + v5 + 36);
      *(_DWORD *)(this->reserve[1] + v5 + 8) = (__int64)*(float *)(this->reserve[1] + v5 + 40);
      *(_DWORD *)(this->reserve[1] + v5 + 12) = *(_DWORD *)(this->reserve[1] + v5 + 4) + 256;
      *(_DWORD *)(v5 + this->reserve[1] + 16) = *(_DWORD *)(v5 + this->reserve[1] + 8) + 256;
      *(_DWORD *)(this->reserve[1] + v5 + 48) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[12];
      *(_DWORD *)(this->reserve[1] + v5 + 52) = *(_DWORD *)(this->reserve[1] + v5 + 4) - *(_DWORD *)&this->mdl[20];
      *(_DWORD *)(this->reserve[1] + v5 + 56) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[16];
      ++v4;
      *(_DWORD *)(this->reserve[1] + v5 + 60) = *(_DWORD *)(this->reserve[1] + v5 + 8) - *(_DWORD *)&this->mdl[24];
      v5 += 80;
    }
    while ( v4 < (int)this->reserve[0] );
  }
  v6 = fVal * *((float *)this + 36);
  LOBYTE(this->reserve[3]) = 1;
  v7 = v6 * *(float *)&this->reserve[2];
  *(float *)&this->reserve[4] = v7;
  *(float *)&this->reserve[5] = v7;
  return 1;
}
