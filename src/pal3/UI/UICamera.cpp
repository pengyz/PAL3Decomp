#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UICamera.h"

// Forward declarations for unnamed functions
int sub_4180B0(...);
int sub_419EF0(...);
int sub_41A070(...);
int sub_429A90(...);

// Unnamed globals (extern)
extern int dword_C300C8;
extern int dword_D8BBEC;

// 0x00420CD0
int UICamera::GetViewMode(int a1)
{
  int v1; // ecx
  int v2; // ebp
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  __int32 m_pCollisionNode; // ecx
  int v7; // esi
  float v8; // eax
  float v9; // eax
  double v10; // st7
  double v11; // st7
  double v12; // st7
  float v14; // [esp+Ch] [ebp-14h]
  float v15; // [esp+10h] [ebp-10h]
  float v16; // [esp+14h] [ebp-Ch] BYREF
  float v17; // [esp+18h] [ebp-8h]
  float v18; // [esp+1Ch] [ebp-4h]

  v2 = v1;
  v3 = -1;
  v4 = 0;
  v5 = *(_DWORD *)(v1 + 220);
  v16 = 0.0;
  v17 = 0.0;
  v18 = 0.0;
  v15 = 3.4028235e38;
  if ( v5 <= 0 )
    return 0;
  m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
  v7 = v2 + 272;
  do
  {
    if ( *(_BYTE *)(v7 + 125)
      && (*(_BYTE *)(v7 + 160) & 2) != 0
      && *(_BYTE *)(v7 + 126)
      && *(unsigned __int8 *)(v7 + 198) == *(_DWORD *)(m_pCollisionNode + 628) )
    {
      v8 = *(float *)v7;
      v16 = *(float *)(v7 - 8);
      v18 = v8;
      v17 = 0.0;
      if ( sub_41A070((float *)m_pCollisionNode, &v16, 1) )
      {
        v9 = *(float *)(v7 - 8);
        v18 = *(float *)v7;
        m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
        v16 = v9;
        v17 = 0.0;
        v16 = v9 - *(float *)(g_SceneMgr.m_pCollisionNode + 4);
        v17 = -*(float *)(g_SceneMgr.m_pCollisionNode + 8);
        v10 = v18 - *(float *)(g_SceneMgr.m_pCollisionNode + 12);
        v18 = v10;
        v11 = v10 * v18 + v16 * v16 + v17 * v17;
        v14 = v11;
        if ( v11 < v15 )
        {
          v3 = v4;
          v15 = v11;
        }
      }
      else
      {
        m_pCollisionNode = g_SceneMgr.m_pCollisionNode;
      }
    }
    ++v4;
    v7 += 896;
  }
  while ( v4 < *(_DWORD *)(v2 + 220) );
  if ( v3 < 0 )
    return 0;
  v12 = *(float *)(896 * v3 + v2 + 1104);
  if ( v14 - v12 * v12 >= 10000.0 )
    return 0;
  else
    return 896 * v3 + v2 + 224;
}

// 0x00420E50
float * UICamera::CalcPosition(float *pMat)
{
  int v1; // ecx
  int v2; // ebp
  int v3; // ebx
  int v4; // edi
  int v5; // esi
  double v6; // st6
  double v7; // st5
  double v8; // st3
  double v9; // st4
  float v11; // [esp+Ch] [ebp-4h]

  v2 = v1;
  v3 = -1;
  v4 = 0;
  v11 = 3.4028235e38;
  if ( *(int *)(v1 + 220) <= 0 )
    return 0;
  v5 = v1 + 272;
  do
  {
    if ( *(_BYTE *)(v5 + 125)
      && (*(_BYTE *)(v5 + 160) & 2) != 0
      && *(_BYTE *)(v5 + 126)
      && sub_429A90(v5 - 48, (gbRay *)pMat) )
    {
      v6 = *(float *)(g_Input.KeyInfo[177].CountMode + 496) - *(float *)(v5 - 4);
      v7 = *(float *)(g_Input.KeyInfo[177].CountMode + 500) - *(float *)v5;
      v8 = *(float *)(g_Input.KeyInfo[177].CountMode + 492) - *(float *)(v5 - 8);
      v9 = v7 * v7 + v8 * v8 + v6 * v6;
      if ( v9 < v11 )
      {
        v11 = v9;
        v3 = v4;
      }
    }
    ++v4;
    v5 += 896;
  }
  while ( v4 < *(_DWORD *)(v2 + 220) );
  if ( v3 >= 0 )
    return (float *)(896 * v3 + v2 + 224);
  else
    return 0;
}

// 0x004230D0
int UICamera::GetState()
{
  int v0; // ebp
  int v1; // ebx
  int v2; // edi
  int v3; // esi
  double v4; // st7
  double v5; // st7
  double v6; // st7
  int v7; // edi
  __int8 *v8; // esi
  double v9; // st7
  double v10; // st7
  double v11; // st7
  float v13; // [esp+4h] [ebp-1Ch]
  float v14; // [esp+8h] [ebp-18h]
  float v15; // [esp+8h] [ebp-18h]
  float v16; // [esp+Ch] [ebp-14h]
  float v17; // [esp+Ch] [ebp-14h]
  float v18; // [esp+10h] [ebp-10h]
  float v19; // [esp+10h] [ebp-10h]
  gbVec3D v20; // [esp+14h] [ebp-Ch] BYREF

  v0 = 0;
  v13 = 3.4028235e38;
  v1 = 0;
  v2 = 493156 * (dword_D8BBEC == 1) + 12722152;
  if ( dword_C300C8[123289 * (dword_D8BBEC == 1)] > 0 )
  {
    v3 = 493156 * (dword_D8BBEC == 1) + 12779892;
    do
    {
      if ( *(_DWORD *)(v3 + 464) )
      {
        if ( *(_DWORD *)(v3 - 24) )
        {
          if ( *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628) == *(_DWORD *)(v3 + 460) )
          {
            if ( sub_419EF0(g_SceneMgr.m_pCollisionNode, (float *)(v3 - 164)) )
            {
              v14 = *(float *)(g_SceneMgr.m_pCollisionNode + 160) - *(float *)(v3 - 8);
              v4 = *(float *)(g_SceneMgr.m_pCollisionNode + 164) - *(float *)(v3 - 4);
              v20.x = v14;
              v16 = v4;
              v5 = *(float *)(g_SceneMgr.m_pCollisionNode + 168) - *(float *)v3;
              v20.y = v16;
              v18 = v5;
              v20.z = v18;
              v6 = ((gbVec3D *)&v20)->Length();
              if ( v6 < v13 )
              {
                v13 = v6;
                v0 = v3 - 168;
              }
            }
          }
        }
      }
      ++v1;
      v3 += 8704;
    }
    while ( v1 < *(_DWORD *)(v2 + 57568) );
  }
  v7 = 0;
  v8 = (__int8 *)&g_SceneMgr.m_slot4[1008];
  do
  {
    if ( v7 != g_SceneMgr.m_nCameraState )
    {
      if ( *((_DWORD *)v8 + 116) )
      {
        if ( sub_41A070((float *)g_SceneMgr.m_pCollisionNode, (float *)v8 - 41, 1) )
        {
          v15 = *(float *)(g_SceneMgr.m_pCollisionNode + 160) - *((float *)v8 - 2);
          v9 = *(float *)(g_SceneMgr.m_pCollisionNode + 164) - *((float *)v8 - 1);
          v20.x = v15;
          v17 = v9;
          v10 = *(float *)(g_SceneMgr.m_pCollisionNode + 168) - *(float *)v8;
          v20.y = v17;
          v19 = v10;
          v20.z = v19;
          v11 = ((gbVec3D *)&v20)->Length();
          if ( v11 < v13 )
          {
            v13 = v11;
            v0 = (int)(v8 - 168);
          }
        }
      }
    }
    v8 += 8704;
    ++v7;
  }
  while ( (int)v8 < (int)&g_SceneMgr._gap_c5e0[152] );
  if ( v0 && 12.0 * 4.5 < v13 - *(float *)(v0 + 16) )
    return 0;
  else
    return v0;
}

// 0x004232D0
int UICamera::GetTarget(float *pMat)
{
  int v1; // edi
  char v2; // bl
  int v3; // ebp
  int v4; // esi
  double v5; // st6
  double v6; // st5
  double v7; // st3
  double v8; // st4
  int v9; // edi
  __int8 *v10; // esi
  double v11; // st6
  double v12; // st5
  double v13; // st3
  double v14; // st4
  float v16; // [esp+0h] [ebp-8h]
  int v17; // [esp+4h] [ebp-4h]

  v16 = 3.4028235e38;
  v17 = -1;
  v1 = 0;
  v2 = 1;
  v3 = 493156 * (dword_D8BBEC == 1) + 12722152;
  if ( dword_C300C8[123289 * (dword_D8BBEC == 1)] > 0 )
  {
    v4 = 493156 * (dword_D8BBEC == 1) + 12779892;
    do
    {
      if ( *(_DWORD *)(v4 + 464) )
      {
        if ( *(_DWORD *)(v4 - 24) )
        {
          if ( sub_4180B0(v4 - 168, (gbRay *)pMat) )
          {
            v5 = *(float *)(g_Input.KeyInfo[177].CountMode + 496) - *(float *)(v4 - 4);
            v6 = *(float *)(g_Input.KeyInfo[177].CountMode + 500) - *(float *)v4;
            v7 = *(float *)(g_Input.KeyInfo[177].CountMode + 492) - *(float *)(v4 - 8);
            v8 = v6 * v6 + v5 * v5 + v7 * v7;
            if ( v8 < v16 )
            {
              v16 = v8;
              v17 = v1;
              v2 = 1;
            }
          }
        }
      }
      ++v1;
      v4 += 8704;
    }
    while ( v1 < *(_DWORD *)(v3 + 57568) );
  }
  v9 = 0;
  v10 = (__int8 *)&g_SceneMgr.m_slot4[1008];
  do
  {
    if ( v9 != g_SceneMgr.m_nCameraState )
    {
      if ( *((_DWORD *)v10 + 116) )
      {
        if ( sub_4180B0((int)(v10 - 168), (gbRay *)pMat) )
        {
          v11 = *(float *)(g_Input.KeyInfo[177].CountMode + 496) - *((float *)v10 - 1);
          v12 = *(float *)(g_Input.KeyInfo[177].CountMode + 500) - *(float *)v10;
          v13 = *(float *)(g_Input.KeyInfo[177].CountMode + 492) - *((float *)v10 - 2);
          v14 = v12 * v12 + v11 * v11 + v13 * v13;
          if ( v14 < v16 )
          {
            v16 = v14;
            v17 = v9;
            v2 = 0;
          }
        }
      }
    }
    v10 += 8704;
    ++v9;
  }
  while ( (int)v10 < (int)&g_SceneMgr._gap_c5e0[152] );
  if ( v17 < 0 )
    return 0;
  if ( v2 )
    return 8704 * v17 + v3 + 57572;
  return (int)&g_SceneMgr.m_slot4[8704 * v17 + 840];
}
