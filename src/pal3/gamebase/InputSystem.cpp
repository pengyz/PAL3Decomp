#include "pal3/gen/InputSystem.h"

// 0x0041C540
void InputSystem::ProcessMouse(int a1)
{
  int v1; // ecx
  int v2; // esi
  _DWORD *v3; // eax
  double v4; // st7
  double v5; // st7
  float v6; // [esp+4h] [ebp-1Ch]
  float v7; // [esp+4h] [ebp-1Ch]
  float v8[2]; // [esp+8h] [ebp-18h] BYREF
  float v9; // [esp+10h] [ebp-10h]
  float v10; // [esp+14h] [ebp-Ch]
  int v11; // [esp+18h] [ebp-8h]
  float v12; // [esp+1Ch] [ebp-4h]

  v2 = v1;
  v8[0] = 0.0;
  v8[1] = 0.0;
  v9 = 0.0;
  v10 = 0.0;
  v11 = 0;
  v12 = 0.0;
  v3 = (_DWORD *)UISceneUpdate();
  if ( sub_421A40(v3, v8) )
  {
    v4 = v10 - 120.0;
    v6 = v8[0] + 120.0;
    if ( v4 < *(float *)(v2 + 480) )
      *(float *)(v2 + 480) = v4;
    if ( *(float *)(v2 + 480) < (double)v6 )
      *(float *)(v2 + 480) = v6;
    v5 = v12 - 120.0;
    v7 = v9 + 120.0;
    if ( v5 < *(float *)(v2 + 488) )
      *(float *)(v2 + 488) = v5;
    if ( *(float *)(v2 + 488) < (double)v7 )
      *(float *)(v2 + 488) = v7;
  }
}

// 0x0041C710
int InputSystem::ProcessKeyboard(int a1)
{
  float *v1; // ecx
  long double v2; // st7
  long double v3; // st6
  long double v4; // st5
  double v5; // st5
  double v6; // st4
  double v7; // st3
  double v8; // st4
  double v9; // st5
  double v10; // st4
  double v11; // st7
  double v12; // st6
  double v13; // st5
  float v15; // [esp+0h] [ebp-1Ch]
  float v16; // [esp+4h] [ebp-18h]
  float v17; // [esp+8h] [ebp-14h]
  float v18; // [esp+Ch] [ebp-10h]
  float v19; // [esp+10h] [ebp-Ch]
  float v20; // [esp+14h] [ebp-8h]
  float v21; // [esp+14h] [ebp-8h]
  float v22; // [esp+14h] [ebp-8h]
  float v23; // [esp+14h] [ebp-8h]
  float v24; // [esp+18h] [ebp-4h]
  float v25; // [esp+18h] [ebp-4h]
  float v26; // [esp+18h] [ebp-4h]

  v2 = cos(v1[114]);
  v3 = cos(v1[113]);
  v17 = cos(v1[116]);
  v15 = sin(v1[114]);
  v16 = sin(v1[113]);
  v4 = sin(v1[116]);
  v1[127] = v16;
  v18 = v4;
  v1[126] = v15 * v3;
  v1[128] = -(v3 * v2);
  v5 = v1[117];
  v19 = v5 * v1[126];
  v20 = v5 * v1[127];
  if ( a1 )
  {
    v6 = v1[120] - v19;
    v21 = v1[121] - v20;
    v7 = v1[122] - v5 * v1[128];
    v1[124] = v21;
    v24 = v7;
    v1[123] = v6;
    v1[125] = v24;
  }
  else
  {
    v22 = v20 + v1[124];
    v8 = v5 * v1[128];
    v9 = v19 + v1[123];
    v10 = v8 + v1[125];
    v1[121] = v22;
    v25 = v10;
    v1[120] = v9;
    v1[122] = v25;
  }
  v1[129] = -(v18 * v2) - v16 * v15 * v17;
  v1[130] = v17 * v3;
  v1[131] = -(v18 * v15) - -(v16 * v17 * v2);
  v11 = v1[131] * v1[127] - v1[128] * v1[130];
  v23 = v1[128] * v1[129] - v1[131] * v1[126];
  v12 = v1[126] * v1[130];
  v13 = v1[129] * v1[127];
  v1[133] = v23;
  v26 = v12 - v13;
  v1[132] = v11;
  v1[134] = v26;
  return LODWORD(v26);
}
