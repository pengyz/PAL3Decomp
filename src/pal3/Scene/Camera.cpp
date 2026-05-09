#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/Camera.h"

// 0x004125D0
void Camera::SetParams(int a2)
{
  long double v3; // st7
  _BYTE actionId[76]; // [esp+8h] [ebp-4Ch] BYREF

  if ( a2 )
  {
    (ScriptObj *->Destroy()this);
    (Actor *->LoadModel()((char *)this + 680));
    *((_DWORD *)this + 321) = 0;
    this->UpdateTransform();
    sub_41AEA0((gbVisNode **)this, 1.0);
    (gbMatrix4 *->gbMatrix4()actionId);
    (Actor *->PlayAction()((char *)this + 680), (int)actionId);
    v3 = sqrt(*(float *)&actionId[72] * *(float *)&actionId[72] + *(float *)&actionId[64] * *(float *)&actionId[64])
       * 0.40000001;
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
  double v5; // st7
  float v6; // edx
  float v7; // ecx
  double v9; // st7
  float v10; // ecx
  float v11; // edx
  double v12; // st7
  double v13; // st7
  double v14; // st6
  float v15; // ecx
  float v16; // [esp+10h] [ebp-3Ch] BYREF
  float v17; // [esp+14h] [ebp-38h]
  float v18; // [esp+18h] [ebp-34h]
  int pTarget; // [esp+1Ch] [ebp-30h] BYREF
  float v20; // [esp+20h] [ebp-2Ch]
  float v21; // [esp+24h] [ebp-28h]
  float v22[6]; // [esp+34h] [ebp-18h] BYREF

  *pDist = 0.0;
  v3 = (int *)(UISceneUpdate() + 492772);
  qmemcpy(v22, (CameraCtrl *->GetViewTarget()g_pCamera, &pTarget, (float *)pPos), sizeof(v22));
  v4 = *((float *)g_pCamera + 117) - 300.0;
  v16 = v22[3] * v4;
  v17 = v22[4] * v4;
  v22[0] = v16 + v22[0];
  v22[1] = v22[1] + v17;
  v22[2] = v22[2] + v4 * v22[5];
  if ( *v3 <= 1 )
  {
    UISceneUpdate();
    if ( sub_4031D0((int)v22, (int)pBounds, 0) )
      return 1;
  }
  else
  {
    v16 = 0.0;
    v17 = 0.0;
    v18 = 0.0;
    if ( sub_4031D0((int)v22, (int)&v16, 0) )
    {
      v5 = v16;
      v6 = v17;
      v7 = v18;
      *(_DWORD *)pDist = 1;
      *(float *)pBounds = v5;
      *((float *)pBounds + 1) = v6;
      *((float *)pBounds + 2) = v7;
      return 1;
    }
    if ( sub_4031D0((int)v22, (int)&v16, 0) )
    {
      v9 = v16;
      v10 = v17;
      v11 = v18;
      *pDist = 0.0;
      *(float *)pBounds = v9;
      *((float *)pBounds + 1) = v10;
      *((float *)pBounds + 2) = v11;
      return 1;
    }
  }
  if ( !*(_DWORD *)&g_SceneMgr.m_info[54108] )
    return 0;
  pTarget = 0;
  v20 = 1.0;
  v21 = 0.0;
  v16 = *(float *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 160);
  v17 = *(float *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 164);
  v18 = *(float *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 168);
  v12 = (gbRay *->IntersectPlane()v22, (struct gbVec3D *)&pTarget, (struct gbVec3D *)&v16);
  if ( v12 == 3.4028235e38 )
    return 0;
  v20 = v22[4] * v12;
  v21 = v22[5] * v12;
  v13 = v22[3] * v12 + v22[0];
  v17 = v22[1] + v20;
  v14 = v22[2] + v21;
  *((float *)pBounds + 1) = v17;
  v18 = v14;
  v15 = v18;
  *(float *)pBounds = v13;
  *((float *)pBounds + 2) = v15;
  return 1;
}

// 0x0041EA00
int Camera::CheckCollision2(void *pPos, int rolePtr, void *pBounds)
{
  char *v3; // eax
  double v4; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st6
  float v9; // edx
  float v10; // [esp+Ch] [ebp-3Ch] BYREF
  float v11; // [esp+10h] [ebp-38h]
  float v12; // [esp+14h] [ebp-34h]
  float pTarget; // [esp+18h] [ebp-30h] BYREF
  float v14; // [esp+1Ch] [ebp-2Ch]
  float v15; // [esp+20h] [ebp-28h]
  float v16[6]; // [esp+30h] [ebp-18h] BYREF

  v3 = (char *)UISceneUpdate();
  sub_420F50(v3, rolePtr);
  qmemcpy(v16, (CameraCtrl *->GetViewTarget()g_pCamera, &pTarget, (float *)pPos), sizeof(v16));
  v4 = *((float *)g_pCamera + 117) - 100.0;
  v10 = v16[3] * v4;
  v11 = v16[4] * v4;
  v16[0] = v10 + v16[0];
  v16[1] = v16[1] + v11;
  v16[2] = v16[2] + v4 * v16[5];
  if ( sub_4031D0((int)v16, (int)pBounds, 0) )
    return 1;
  v10 = 0.0;
  v11 = 1.0;
  v12 = 0.0;
  v6 = (gbRay *->IntersectPlane()v16,
         (struct gbVec3D *)&v10,
         (struct gbVec3D *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 160));
  if ( v6 >= 3.4028235e38 )
    return 0;
  v11 = v16[4] * v6;
  v12 = v16[5] * v6;
  v7 = v16[3] * v6 + v16[0];
  v14 = v16[1] + v11;
  v8 = v16[2] + v12;
  *((float *)pBounds + 1) = v14;
  v15 = v8;
  v9 = v15;
  *(float *)pBounds = v7;
  *((float *)pBounds + 2) = v9;
  return 1;
}

// 0x0041EE60
char Camera::IsTransitioning()
{
  void *v0; // eax
  int v1; // eax
  _DWORD *v2; // eax
  int v3; // eax
  char v5; // al
  int v6; // [esp-Ch] [ebp-18h]
  int v7; // [esp-8h] [ebp-14h]
  int v8; // [esp-4h] [ebp-10h]
  int v9; // [esp-4h] [ebp-10h]

  v8 = *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 628);
  v0 = (void *)UISceneUpdate();
  v1 = v0->GetRolePtr(v8);
  v9 = (__int64)((*(float *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 12) - *(float *)(v1 + 136))
               / *(float *)&g_SceneMgr.m_info[54068]);
  v7 = (__int64)((*(float *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 4) - *(float *)(v1 + 128))
               / *(float *)&g_SceneMgr.m_info[54068]);
  v6 = *(_DWORD *)(*(_DWORD *)&g_SceneMgr.m_info[54108] + 628);
  v2 = (_DWORD *)UISceneUpdate();
  v3 = sub_420A10(v2, v6, v7, v9);
  if ( !v3 )
    return 0;
  v5 = *(_BYTE *)(v3 + 244);
  return v5 == 44 || v5 == 38;
}
