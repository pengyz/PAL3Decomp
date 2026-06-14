#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SceneProp.h"

// 0x005330F0
char SceneProp::CalculateWorldPos(float fVal)
{
  double v3; // st7
  int v4; // eax
  float v5; // edx
  double v6; // st7
  int v7; // ecx
  int v8; // eax
  char v9; // al
  gbGeomNode *pGeom; // ecx
  char result; // al
  double v12; // st7
  double v13; // st7
  _BYTE v14[48]; // [esp-0x44] [ebp-E4h] BYREF
  float v15; // [esp-0x14] [ebp-B4h]
  int v16; // [esp-0x10] [ebp-B0h]
  float v17; // [esp-0xC] [ebp-ACh]
  int v18; // [esp-0x8] [ebp-A8h]
  int v19; // [esp-0x4] [ebp-A4h]
  float v20; // [esp+0xC] [ebp-0x94]
  float v21; // [esp+0x10] [ebp-0x90]
  float v22; // [esp+0x14] [ebp-0x8C]
  _BYTE v23[48]; // [esp+0x18] [ebp-0x88] BYREF
  float v24; // [esp+0x48] [ebp-0x58]
  int v25; // [esp+0x4C] [ebp-0x54]
  float v26; // [esp+0x50] [ebp-0x50]
  int v27; // [esp+0x54] [ebp-0x4C]
  int v28; // [esp+0x58] [ebp-0x48]
  int v29[17]; // [esp+0x5C] [ebp-0x44] BYREF

  v20 = this->vecFling.y + *(float *)&this->rect.right;
  v3 = this->vecFling.z + *(float *)&this->rect.bottom;
  v17 = v20;
  v21 = v3;
  v22 = this->lastFling.x + this->fCurTime;
  v4 = ((ArcLocaleRole *)v29)->TransformPoint(v20, v21, v22);
  v5 = *(float *)(v4 + 56);
  v6 = *(float *)(v4 + 48);
  qmemcpy(v23, (const void *)v4, sizeof(v23));
  v24 = v6;
  v25 = *(_DWORD *)(v4 + 52);
  v7 = *(_DWORD *)(v4 + 60);
  v8 = *(_DWORD *)(v4 + 64);
  v26 = v5;
  v27 = v7;
  v28 = v8;
  qmemcpy(v14, v23, sizeof(v14));
  v15 = v6;
  v16 = v25;
  v17 = v5;
  v18 = v7;
  v19 = v8;
  v9 = ((RoleSystem *)this)->ResetPathState();
  pGeom = this->pGeom;
  LOBYTE(this->parabola.B.x) = v9;
  LOBYTE(pGeom->PosCtrl) = v9;
  if ( !v9 )
    BYTE1(pGeom->PosCtrl) = 0;
  result = LOBYTE(this->parabola.B.x);
  BYTE1(this->parabola.B.x) = result;
  if ( result )
  {
    this->parabola.B.y = this->vecFling.y;
    v12 = fVal * 0.57999998;
    this->parabola.B.z = this->vecFling.z;
    this->parabola.H = this->lastFling.x;
    result = this->parabola.m_state;
    BYTE1(this->parabola.B.x) = 1;
    if ( result )
      v13 = this->parabola.G - v12;
    else
      v13 = v12 + this->parabola.G;
    this->parabola.G = v13;
  }
  else
  {
    this->parabola.G = 0.0;
  }
  return result;
}

// 0x00533BC0
char SceneProp::CalcScreenPosition()
{
  LONG top; // esi
  int v2; // ebx
  __int64 v3; // rax

  top = this->rect.top;
  v2 = (__int64)((this->vecFling.y - *(float *)(top + 128)) / g_fSceneScale);
  v3 = (__int64)((this->lastFling.x - *(float *)(top + 136)) / g_fSceneScale);
  if ( v2 < 0
    || v2 >= *(_DWORD *)(top + 152)
    || (int)v3 < 0
    || (int)v3 >= *(_DWORD *)(top + 156)
    || *(_BYTE *)(*(_DWORD *)(top + 160) + 8 * (v2 + v3 * *(_DWORD *)(top + 152)) + 5) != 5 )
  {
    return 0;
  }
  BYTE1(this->parabola.m_state) = 1;
  return 1;
}
