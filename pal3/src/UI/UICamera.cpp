#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UICamera.h"

// Forward declarations for unnamed functions
int sub_429A90(...);

// Unnamed globals (extern)
extern int dword_C10A08;
extern int dword_C300C8[];
extern int dword_D8BBEC;
extern RoleSystem stru_C059A0;

// 0x0041A070
BOOL UICamera::IsPointVisible(float *pfTargetPos, char bNearVisible)
{
  double v4; // st7
  double v5; // st6
  gbVec3D v7; // [esp+0x4] [ebp-0x18] BYREF
  float v8; // [esp+0x14] [ebp-0x8]
  float v9; // [esp+0x18] [ebp-0x4]
  float pfTargetPosa; // [esp+0x20] [ebp+0x4]

  v4 = *pfTargetPos - *((float *)this + 1);
  v8 = pfTargetPos[1] - *((float *)this + 2);
  v5 = pfTargetPos[2] - *((float *)this + 3);
  v7.y = v8;
  v9 = v5;
  v7.x = v4;
  v7.z = v9;
  pfTargetPosa = ((gbVec3D *)&v7)->Length();
  if ( 0.87 * 500.0 < pfTargetPosa )
    return 0;
  if ( bNearVisible && 12.0 * 8.0 > pfTargetPosa )
    return 1;
  return v7.z / pfTargetPosa * *((float *)this + 7)
       + v7.y / pfTargetPosa * *((float *)this + 6)
       + v7.x / pfTargetPosa * *((float *)this + 5) > 0.87;
}

// 0x00420CD0
int UICamera::GetViewMode(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  UICamera *v6; // ecx
  int v7; // esi
  float v8; // eax
  float v9; // eax
  double v10; // st7
  double v11; // st7
  double v12; // st7
  float v14; // [esp+0xC] [ebp-0x14]
  float v15; // [esp+0x10] [ebp-0x10]
  float pfTargetPos; // [esp+0x14] [ebp-0xC] BYREF
  float v17; // [esp+0x18] [ebp-0x8]
  float v18; // [esp+0x1C] [ebp-0x4]

  v2 = v1;
  v3 = -1;
  v4 = 0;
  v5 = *(_DWORD *)(v1 + 220);
  pfTargetPos = 0.0;
  v17 = 0.0;
  v18 = 0.0;
  v15 = 3.4028235e38;
  if ( v5 <= 0 )
    return 0;
  v6 = (UICamera *)g_pRoleSystem;
  v7 = v2 + 272;
  do
  {
    if ( *(_BYTE *)(v7 + 125)
      && (*(_BYTE *)(v7 + 160) & 2) != 0
      && *(_BYTE *)(v7 + 126)
      && *(unsigned __int8 *)(v7 + 198) == v6->m_hCameraHandle )
    {
      v8 = *(float *)v7;
      pfTargetPos = *(float *)(v7 - 8);
      v18 = v8;
      v17 = 0.0;
      if ( ((UICamera *)v6)->IsPointVisible(&pfTargetPos, 1) )
      {
        v9 = *(float *)(v7 - 8);
        v18 = *(float *)v7;
        v6 = (UICamera *)g_pRoleSystem;
        pfTargetPos = v9;
        v17 = 0.0;
        pfTargetPos = v9 - *(float *)&g_pRoleSystem->m_fontcolor.Color;
        v17 = -*(float *)&g_pRoleSystem->m_wndcolor.Color;
        v10 = v18 - *(float *)&g_pRoleSystem->m_id;
        v18 = v10;
        v11 = v10 * v18 + pfTargetPos * pfTargetPos + v17 * v17;
        v14 = v11;
        if ( v11 < v15 )
        {
          v3 = v4;
          v15 = v11;
        }
      }
      else
      {
        v6 = (UICamera *)g_pRoleSystem;
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
float * UICamera::CalcPosition()
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
  float v11; // [esp+0xC] [ebp-0x4]

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
      && sub_429A90((Object3D *)(v5 - 48), pMat) )
    {
      v6 = g_pCameraCtrl->m_vecLookAt.y - *(float *)(v5 - 4);
      v7 = g_pCameraCtrl->m_vecLookAt.z - *(float *)v5;
      v8 = g_pCameraCtrl->m_vecLookAt.x - *(float *)(v5 - 8);
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
  int v1; // ebp
  int v2; // ebx
  int v3; // edi
  int v4; // esi
  double v5; // st7
  double v6; // st7
  double v7; // st7
  int v8; // edi
  int *v9; // esi
  double v10; // st7
  double v11; // st7
  double v12; // st7
  float v14; // [esp+0x4] [ebp-0x1C]
  float v15; // [esp+0x8] [ebp-0x18]
  float v16; // [esp+0x8] [ebp-0x18]
  float v17; // [esp+0xC] [ebp-0x14]
  float v18; // [esp+0xC] [ebp-0x14]
  float v19; // [esp+0x10] [ebp-0x10]
  float v20; // [esp+0x10] [ebp-0x10]
  gbVec3D v21; // [esp+0x14] [ebp-0xC] BYREF

  v1 = 0;
  v14 = 3.4028235e38;
  v2 = 0;
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
          if ( *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture == *(_DWORD *)(v4 + 460) )
          {
            if ( ((RoleSystem *)&g_pRoleSystem)->AdvancePathStep((float *)(v4 - 164)) )
            {
              v15 = g_pRoleSystem->m_fPosX - *(float *)(v4 - 8);
              v5 = g_pRoleSystem->m_fPosY - *(float *)(v4 - 4);
              v21.x = v15;
              v17 = v5;
              v6 = g_pRoleSystem->m_fPosZ - *(float *)v4;
              v21.y = v17;
              v19 = v6;
              v21.z = v19;
              v7 = ((gbVec3D *)&v21)->Length();
              if ( v7 < v14 )
              {
                v14 = v7;
                v1 = v4 - 168;
              }
            }
          }
        }
      }
      ++v2;
      v4 += 8704;
    }
    while ( v2 < *(_DWORD *)(v3 + 57568) );
  }
  v8 = 0;
  v9 = &((RoleSystem *)&stru_C059A0)->m_teamSlots[35];
  do
  {
    if ( v8 != g_nCurrentRoleSlot )
    {
      if ( v9[116] )
      {
        if ( ((UICamera *)g_pRoleSystem)->IsPointVisible((float *)v9 - 41, 1) )
        {
          v16 = g_pRoleSystem->m_fPosX - *((float *)v9 - 2);
          v10 = g_pRoleSystem->m_fPosY - *((float *)v9 - 1);
          v21.x = v16;
          v18 = v10;
          v11 = g_pRoleSystem->m_fPosZ - *(float *)v9;
          v21.y = v18;
          v20 = v11;
          v21.z = v20;
          v12 = ((gbVec3D *)&v21)->Length();
          if ( v12 < v14 )
          {
            v14 = v12;
            v1 = (int)(v9 - 42);
          }
        }
      }
    }
    v9 += 2176;
    ++v8;
  }
  while ( (int)v9 < (int)&dword_C10A08 );
  if ( v1 && 12.0 * 4.5 < v14 - *(float *)(v1 + 16) )
    return 0;
  else
    return v1;
}

// 0x004232D0
int UICamera::GetTarget()
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
  int *v10; // esi
  double v11; // st6
  double v12; // st5
  double v13; // st3
  double v14; // st4
  float v16; // [esp+0x0] [ebp-0x8]
  int v17; // [esp+0x4] [ebp-0x4]

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
          if ( ((RoleSystem *)(v4 - 168))->CheckWidgetReady((gbRay *)pMat) )
          {
            v5 = g_pCameraCtrl->m_vecLookAt.y - *(float *)(v4 - 4);
            v6 = g_pCameraCtrl->m_vecLookAt.z - *(float *)v4;
            v7 = g_pCameraCtrl->m_vecLookAt.x - *(float *)(v4 - 8);
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
  v10 = &((RoleSystem *)&stru_C059A0)->m_teamSlots[35];
  do
  {
    if ( v9 != g_nCurrentRoleSlot )
    {
      if ( v10[116] )
      {
        if ( ((RoleSystem *)(v10 - 42))->CheckWidgetReady((gbRay *)pMat) )
        {
          v11 = g_pCameraCtrl->m_vecLookAt.y - *((float *)v10 - 1);
          v12 = g_pCameraCtrl->m_vecLookAt.z - *(float *)v10;
          v13 = g_pCameraCtrl->m_vecLookAt.x - *((float *)v10 - 2);
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
    v10 += 2176;
    ++v9;
  }
  while ( (int)v10 < (int)&dword_C10A08 );
  if ( v17 < 0 )
    return 0;
  if ( v2 )
    return 8704 * v17 + v3 + 57572;
  return (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * v17 - 7];
}
