#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Camera.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/RoleSystem.h"
#include "pal3/gen/ScriptObj.h"

// Forward declarations for unnamed functions
int UISceneUpdate(...);
int sub_4031D0(...);
int sub_41AEA0(...);
int sub_420A10(...);
int sub_420F50(...);

// Unnamed globals (extern)
extern int dword_BFDA68;

// 0x004125D0
void Camera::SetParams(int a2)
{
  long double v3; // st7
  int actionId[16]; // [esp+8h] [ebp-4Ch] BYREF
  float v5; // [esp+48h] [ebp-Ch]
  float v6; // [esp+50h] [ebp-4h]

  if ( a2 )
  {
    ((ScriptObj *)this)->Destroy();
    ((Actor *)((char *)this + 680))->LoadModel();
    *((_DWORD *)this + 321) = 0;
    this->UpdateTransform();
    sub_41AEA0((gbVisNode **)this, 1.0);
    ((gbMatrix4 *)actionId)->gbMatrix4();
    ((Actor *)((char *)this + 680))->PlayAction((int)actionId);
    v3 = sqrt(v6 * v6 + v5 * v5) * 0.40000001;
    *((float *)this + 4) = v3;
    if ( v3 < 6.0 )
      *((_DWORD *)this + 364) = 1;
    *((_DWORD *)this + 339) = 0;
  }
}

// 0x0041E7D0
int Camera::CheckCollision1(void *pPos, void *pBounds, float *pDist)
{
  int *v3; // ebx
  double v4; // st7
  double x; // st7
  float y; // edx
  float z; // ecx
  double v9; // st7
  float v10; // ecx
  float v11; // edx
  int v12; // eax
  double v13; // st7
  double v14; // st7
  double v15; // st6
  float v16; // ecx
  struct gbVec3D v17; // [esp+10h] [ebp-3Ch] BYREF
  struct gbVec3D pTarget[2]; // [esp+1Ch] [ebp-30h] BYREF
  gbRay v19; // [esp+34h] [ebp-18h] BYREF

  *pDist = 0.0;
  v3 = (int *)(UISceneUpdate() + 492772);
  qmemcpy(&v19, ((CameraCtrl *)dword_BFDA68)->GetViewTarget(pTarget, (float *)pPos), sizeof(v19));
  v4 = *(float *)&dword_BFDA68->CurCtrl - 300.0;
  v17.x = v19.Direction.x * v4;
  v17.y = v19.Direction.y * v4;
  v19.Origin.x = v17.x + v19.Origin.x;
  v19.Origin.y = v19.Origin.y + v17.y;
  v19.Origin.z = v19.Origin.z + v4 * v19.Direction.z;
  if ( *v3 <= 1 )
  {
    v12 = UISceneUpdate();
    if ( sub_4031D0((int *)(v12 + 493104), &v19, (int)pBounds, 0) )
      return 1;
  }
  else
  {
    memset(&v17, 0, sizeof(v17));
    if ( sub_4031D0(v3 + 87, &v19, (int)&v17, 0) )
    {
      x = v17.x;
      y = v17.y;
      z = v17.z;
      *(_DWORD *)pDist = 1;
      *(float *)pBounds = x;
      *((float *)pBounds + 1) = y;
      *((float *)pBounds + 2) = z;
      return 1;
    }
    if ( sub_4031D0(v3 + 83, &v19, (int)&v17, 0) )
    {
      v9 = v17.x;
      v10 = v17.y;
      v11 = v17.z;
      *pDist = 0.0;
      *(float *)pBounds = v9;
      *((float *)pBounds + 1) = v10;
      *((float *)pBounds + 2) = v11;
      return 1;
    }
  }
  if ( !g_SceneMgr.m_pCollisionNode )
    return 0;
  pTarget[0].x = 0.0;
  pTarget[0].y = 1.0;
  pTarget[0].z = 0.0;
  v17 = *(struct gbVec3D *)(g_SceneMgr.m_pCollisionNode + 160);
  v13 = ((gbRay *)&v19)->IntersectPlane(pTarget, &v17);
  if ( v13 == 3.4028235e38 )
    return 0;
  pTarget[0].y = v19.Direction.y * v13;
  pTarget[0].z = v19.Direction.z * v13;
  v14 = v19.Direction.x * v13 + v19.Origin.x;
  v17.y = v19.Origin.y + pTarget[0].y;
  v15 = v19.Origin.z + pTarget[0].z;
  *((_DWORD *)pBounds + 1) = LODWORD(v17.y);
  v17.z = v15;
  v16 = v17.z;
  *(float *)pBounds = v14;
  *((float *)pBounds + 2) = v16;
  return 1;
}

// 0x0041EA00
int Camera::CheckCollision2(void *pPos, int rolePtr, void *pBounds)
{
  char *v3; // eax
  int *v4; // ebx
  double v5; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st6
  float v10; // edx
  struct gbVec3D v11; // [esp+Ch] [ebp-3Ch] BYREF
  float pTarget; // [esp+18h] [ebp-30h] BYREF
  float v13; // [esp+1Ch] [ebp-2Ch]
  float v14; // [esp+20h] [ebp-28h]
  gbRay v15; // [esp+30h] [ebp-18h] BYREF

  v3 = (char *)UISceneUpdate();
  v4 = (int *)sub_420F50(v3, rolePtr);
  qmemcpy(&v15, ((CameraCtrl *)dword_BFDA68)->GetViewTarget(&pTarget, (float *)pPos), sizeof(v15));
  v5 = *(float *)&dword_BFDA68->CurCtrl - 100.0;
  v11.x = v15.Direction.x * v5;
  v11.y = v15.Direction.y * v5;
  v15.Origin.x = v11.x + v15.Origin.x;
  v15.Origin.y = v15.Origin.y + v11.y;
  v15.Origin.z = v15.Origin.z + v5 * v15.Direction.z;
  if ( sub_4031D0(v4, &v15, (int)pBounds, 0) )
    return 1;
  v11.x = 0.0;
  v11.y = 1.0;
  v11.z = 0.0;
  v7 = ((gbRay *)&v15)->IntersectPlane(&v11, (struct gbVec3D *)(g_SceneMgr.m_pCollisionNode + 160));
  if ( v7 >= 3.4028235e38 )
    return 0;
  v11.y = v15.Direction.y * v7;
  v11.z = v15.Direction.z * v7;
  v8 = v15.Direction.x * v7 + v15.Origin.x;
  v13 = v15.Origin.y + v11.y;
  v9 = v15.Origin.z + v11.z;
  *((float *)pBounds + 1) = v13;
  v14 = v9;
  v10 = v14;
  *(float *)pBounds = v8;
  *((float *)pBounds + 2) = v10;
  return 1;
}

// 0x0041EE60
char Camera::IsTransitioning()
{
  RoleSystem *v0; // eax
  int RolePtr; // eax
  _DWORD *v2; // eax
  _DWORD *v3; // eax
  char v5; // al
  int v6; // [esp-Ch] [ebp-18h]
  int v7; // [esp-8h] [ebp-14h]
  int v8; // [esp-4h] [ebp-10h]
  int v9; // [esp-4h] [ebp-10h]

  v8 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
  v0 = (RoleSystem *)UISceneUpdate();
  RolePtr = v0->GetRolePtr(v8);
  v9 = (__int64)((*(float *)(g_SceneMgr.m_pCollisionNode + 12) - *(float *)(RolePtr + 136))
               / *(float *)&g_SceneMgr._gap_cd10[1572]);
  v7 = (__int64)((*(float *)(g_SceneMgr.m_pCollisionNode + 4) - *(float *)(RolePtr + 128))
               / *(float *)&g_SceneMgr._gap_cd10[1572]);
  v6 = *(_DWORD *)(g_SceneMgr.m_pCollisionNode + 628);
  v2 = (_DWORD *)UISceneUpdate();
  v3 = (_DWORD *)sub_420A10(v2, v6, v7, v9);
  if ( !v3 )
    return 0;
  v5 = *((_BYTE *)v3 + 244);
  return v5 == 44 || v5 == 38;
}
