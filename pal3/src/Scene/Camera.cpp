#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/Camera.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
void sub_536D20(Actor *_this, const char *a2, int a3); // from annotations

// Unnamed globals (extern)
extern char byte_80AC01;
extern char byte_80AC02;
extern char byte_80AC03;
extern char byte_80AC04;
extern char byte_80AC05;
extern char byte_80AC06;
extern char byte_80AC07;
extern char byte_ABC00B;
extern int dword_DDAF3C;
extern RoleSystem stru_C059A0;

// 0x004125D0
void Camera::InitFromScene(const char *pszSceneName)
{
  long double v3; // st7
  gbMatrix4 actionId; // [esp+0x8] [ebp-0x4C] BYREF
  float v5; // [esp+0x48] [ebp-0xC]
  float v6; // [esp+0x50] [ebp-0x4]

  if ( pszSceneName )
  {
    ((PalScript *)this)->DestroyScript();
    sub_536D20((Actor *)(&this->m_ScriptResult + 69), pszSceneName, 0);
    *(&this->m_ScriptResult + 220) = 0;
    ((RoleSystem *)this)->UpdateTransform();
    ((RoleSystem *)this)->SetBlendMode(1.0);
    ((Actor *)(&this->m_ScriptResult + 69))->PlayAction((int)&actionId);
    v3 = sqrt(v6 * v6 + v5 * v5) * 0.40000001;
    *(float *)&this->m_nStepRotate = v3;
    if ( v3 < 6.0 )
      *(&this->m_ScriptResult + 263) = 1;
    *(&this->m_ScriptResult + 238) = 0;
  }
}

// 0x0041BE80
Camera::Camera(gbGfxManager *p)
{
  this->m_fCameraTimer = 0.0;
  this->m_fLerpSpeed = 0.0;
  this->m_fLerpProgress = 0.0;
  this->m_bLerpActive = (_BYTE)p;
  ((PalScriptMgr *)&this->m_ScriptResult)->Get_result();
  *(&this->m_ScriptResult + 4) = 0;
  *(&this->m_ScriptResult + 5) = 0;
  *(&this->m_ScriptResult + 6) = 0;
  *(&this->m_ScriptResult + 7) = 0;
  *(&this->m_ScriptResult + 8) = 0;
  *(&this->m_ScriptResult + 9) = 0;
  *(&this->m_ScriptResult + 10) = 0;
  *(&this->m_ScriptResult + 19) = 0;
  *(&this->m_ScriptResult + 20) = 0;
  *(&this->m_ScriptResult + 21) = 0;
  *(&this->m_ScriptResult + 22) = 0;
  *(&this->m_ScriptResult + 23) = 0;
  *(&this->m_ScriptResult + 24) = 0;
  *(&this->m_ScriptResult + 25) = 0;
  *(&this->m_ScriptResult + 26) = 0;
  *(&this->m_ScriptResult + 27) = 0;
  *(&this->m_ScriptResult + 28) = 0;
  *(&this->m_ScriptResult + 29) = 0;
  *(&this->m_ScriptResult + 30) = 0;
  *(&this->m_ScriptResult + 31) = 0;
  *(&this->m_ScriptResult + 32) = 0;
  *(&this->m_ScriptResult + 33) = 0;
  this->m_nCameraTick = 0;
  this->m_nPrevCameraTick = 0;
  *(&this->m_ScriptResult + 15) = 0;
  old_sbh_page_manage((__old_sbh_page_struct *)this, 0);
  *(&this->m_ScriptResult + 17) = 0;
  *(&this->m_ScriptResult + 18) = 0;
  *(&this->m_ScriptResult + 14) = 0;
  *(&this->m_ScriptResult + 11) = 1;
  *(&this->m_ScriptResult + 34) = 1107296256;
  this;
}

// 0x0041E7D0
int Camera::CheckCollision1(void *pBounds, float *pDist)
{
  int v3; // ebx
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
  struct gbVec3D v17; // [esp+0x10] [ebp-0x3C] BYREF
  struct gbVec3D pTarget[2]; // [esp+0x1C] [ebp-0x30] BYREF
  gbRay v19; // [esp+0x34] [ebp-0x18] BYREF

  *pDist = 0.0;
  v3 = UISceneUpdate() + 492772;
  qmemcpy(&v19, ((CameraCtrl *)&g_pCameraCtrl)->GetViewTarget(pTarget, pPos), sizeof(v19));
  v4 = g_pCameraCtrl->m_fCamDist - 300.0;
  v17.x = v19.Direction.x * v4;
  v17.y = v19.Direction.y * v4;
  v19.Origin.x = v17.x + v19.Origin.x;
  v19.Origin.y = v19.Origin.y + v17.y;
  v19.Origin.z = v19.Origin.z + v4 * v19.Direction.z;
  if ( *(int *)v3 <= 1 )
  {
    v12 = UISceneUpdate();
    if ( ((GRPinput *)(v12 + 493104))->GetState() )
      return 1;
  }
  else
  {
    memset(&v17, 0, sizeof(v17));
    if ( ((GRPinput *)(v3 + 348))->GetState() )
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
    if ( ((GRPinput *)(v3 + 332))->GetState() )
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
  if ( !g_pRoleSystem )
    return 0;
  pTarget[0].x = 0.0;
  pTarget[0].y = 1.0;
  pTarget[0].z = 0.0;
  v17 = *(gbVec3D *)&g_pRoleSystem->m_fPosX;
  v13 = ((gbRay *)&v19)->IntersectPlane(pTarget, v17);
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
int Camera::CheckCollision2(int rolePtr, void *pBounds)
{
  RoleSystem *v3; // eax
  char *MapNodePtr; // ebx
  double v5; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st6
  float v10; // edx
  struct gbVec3D v11; // [esp+0xC] [ebp-0x3C] BYREF
  float pTarget; // [esp+0x18] [ebp-0x30] BYREF
  float v13; // [esp+0x1C] [ebp-0x2C]
  float v14; // [esp+0x20] [ebp-0x28]
  gbRay v15; // [esp+0x30] [ebp-0x18] BYREF

  v3 = (RoleSystem *)UISceneUpdate();
  MapNodePtr = ((RoleSystem *)v3)->GetMapNodePtr(rolePtr);
  qmemcpy(&v15, ((CameraCtrl *)&g_pCameraCtrl)->GetViewTarget(&pTarget, pPos), sizeof(v15));
  v5 = g_pCameraCtrl->m_fCamDist - 100.0;
  v11.x = v15.Direction.x * v5;
  v11.y = v15.Direction.y * v5;
  v15.Origin.x = v11.x + v15.Origin.x;
  v15.Origin.y = v15.Origin.y + v11.y;
  v15.Origin.z = v15.Origin.z + v5 * v15.Direction.z;
  if ( ((GRPinput *)MapNodePtr)->GetState() )
    return 1;
  v11.x = 0.0;
  v11.y = 1.0;
  v11.z = 0.0;
  v7 = ((gbRay *)&v15)->IntersectPlane(v11, (gbVec3D *)&g_pRoleSystem->m_fPosX);
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
  RoleSystem *v1; // eax
  int RolePtr; // eax
  RoleSystem *v3; // eax
  int *v4; // eax
  char v6; // al
  int v7; // [esp-0xC] [ebp-0x18]
  int v8; // [esp-0x8] [ebp-0x14]
  int v9; // [esp-0x4] [ebp-0x10]
  int v10; // [esp-0x4] [ebp-0x10]

  v9 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
  v1 = (RoleSystem *)UISceneUpdate();
  RolePtr = ((RoleSystem *)v1)->GetRolePtr(v9);
  v10 = (__int64)((*(float *)&g_pRoleSystem->m_id - *(float *)(RolePtr + 136)) / g_fTileSize);
  v8 = (__int64)((*(float *)&g_pRoleSystem->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fTileSize);
  v7 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
  v3 = (RoleSystem *)UISceneUpdate();
  v4 = ((RoleSystem *)v3)->IsTileInBounds(v7, v8, v10);
  if ( !v4 )
    return 0;
  v6 = *((_BYTE *)v4 + 244);
  return v6 == 44 || v6 == 38;
}

// 0x00439850
void Camera::UpdateCameraLookAt(int nScreenX, int nScreenY)
{
  gbCamera *m_pCamera; // ecx
  double v5; // st7
  float y; // eax
  float z; // edx
  struct gbVec3D v8; // [esp+0xC] [ebp-0x24] BYREF
  struct gbVec3D v9; // [esp+0x18] [ebp-0x18] BYREF
  struct gbVec3D v10; // [esp+0x24] [ebp-0xC] BYREF
  float nScreenXa; // [esp+0x34] [ebp+0x4]

  m_pCamera = this->m_pCamera;
  v10.x = 0.0;
  v10.y = 1.0;
  v10.z = 0.0;
  v9.z = 1600.0;
  v8.z = 0.0;
  v5 = (((double)nScreenX + (double)nScreenX) / (double)g_DrvInfo.width - 1.0) * this->m_fFovTan;
  v8.y = (1.0 - ((double)nScreenY + (double)nScreenY) / (double)g_DrvInfo.height) * this->m_fFovTan;
  v9.x = -v5;
  nScreenXa = -v8.y;
  v9.y = nScreenXa;
  v8.y = nScreenXa;
  v8.x = v9.x;
  ((gbCamera *)m_pCamera)->SetLookAt(&v9, &v8, &v10);
  y = v8.y;
  this->m_vRayDir.x = v8.x;
  z = v8.z;
  this->m_vRayDir.y = y;
  this->m_vRayDir.z = z;
  this->m_vRayDir.x = this->m_vRayDir.x - v9.x;
  this->m_vRayDir.y = this->m_vRayDir.y - v9.y;
  this->m_vRayDir.z = this->m_vRayDir.z - v9.z;
  ((gbVec3D *)&this->m_vRayDir)->Normalize();
}

// 0x00439930
void Camera::UpdateCameraLookAt(int nScreenX, int nScreenY, int nOffsetY)
{
  gbCamera *m_pCamera; // ecx
  double v6; // st7
  float y; // edx
  float z; // eax
  struct gbVec3D v9; // [esp+0xC] [ebp-0x30] BYREF
  struct gbVec3D v10; // [esp+0x18] [ebp-0x24] BYREF
  struct gbVec3D v11; // [esp+0x24] [ebp-0x18] BYREF
  float v12; // [esp+0x34] [ebp-0x8]

  m_pCamera = this->m_pCamera;
  v11.x = 0.0;
  v11.y = 1.0;
  v11.z = 0.0;
  v9.z = 1600.0;
  v10.z = 0.0;
  v6 = (((double)nScreenX + (double)nScreenX) / (double)g_DrvInfo.width - 1.0) * this->m_fFovTan;
  v12 = (1.0 - ((double)nScreenY + (double)nScreenY) / (double)g_DrvInfo.height) * this->m_fFovTan;
  v9.y = (float)nOffsetY;
  v9.x = -v6;
  v9.y = v9.y - v12;
  v10.x = v9.x;
  v10.y = -v12;
  ((gbCamera *)m_pCamera)->SetLookAt(&v9, &v10, &v11);
  y = v10.y;
  this->m_vRayDir.x = v10.x;
  z = v10.z;
  this->m_vRayDir.y = y;
  this->m_vRayDir.z = z;
  this->m_vRayDir.x = this->m_vRayDir.x - v9.x;
  this->m_vRayDir.y = this->m_vRayDir.y - v9.y;
  this->m_vRayDir.z = this->m_vRayDir.z - v9.z;
  ((gbVec3D *)&this->m_vRayDir)->Normalize();
}

// 0x0052BEB0
void Camera::InitUIElements()
{
  int v2; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int *v9; // edi
  int v10; // edx
  int v11; // edx
  int v12; // ecx
  int v13; // ebp
  int v14; // eax
  int v15; // eax
  int v16; // ebp
  int v17; // ecx
  int v18; // edi
  int v19; // ebp
  int v20; // kr04_4
  int v21; // eax
  double v22; // st7
  int i; // edi
  RoleSystem *v24; // edi
  int *v25; // eax
  int v26; // ebp
  int v27; // edx
  int v28; // edx
  int v29; // ecx
  int v30; // edx
  int v31; // [esp+0x6C] [ebp-0x64]
  int v32; // [esp+0x70] [ebp-0x60] BYREF
  int v33; // [esp+0x74] [ebp-0x5C]
  int v34; // [esp+0x78] [ebp-0x58]
  int v35; // [esp+0x7C] [ebp-0x54]
  int v36; // [esp+0x80] [ebp-0x50] BYREF
  int v37; // [esp+0x84] [ebp-0x4C]
  int v38; // [esp+0x88] [ebp-0x48]
  int v39; // [esp+0x8C] [ebp-0x44]
  int v40; // [esp+0x90] [ebp-0x40] BYREF
  int v41; // [esp+0x94] [ebp-0x3C]
  int v42; // [esp+0x98] [ebp-0x38]
  int v43; // [esp+0x9C] [ebp-0x34]
  _DWORD v44[4]; // [esp+A0h] [ebp-0x30] BYREF
  int nVal[4]; // [esp+B0h] [ebp-0x20] BYREF
  int v46[4]; // [esp+C0h] [ebp-0x10] BYREF

  v2 = *((_DWORD *)&this->m_pLookAtData + 3);
  v3 = *((_DWORD *)&this->m_pLookAtData + 4);
  *((_DWORD *)&this->m_pLookAtData + 1) = v2;
  *((_DWORD *)&this->m_pLookAtData + 2) = v3;
  this->m_pLookAtData = 0;
  this->m_fLookAtProgress = 0.0;
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, *((_DWORD *)&this->m_pLookAtData + 1), *((_DWORD *)&this->m_pLookAtData + 2), 0);
  ((PalScript *)this)->LoadEncampConfig();
  v4 = *(&this->m_ScriptResult + 429);
  v37 = 172;
  v36 = 125;
  v38 = 675;
  v39 = 428;
  (*(void ( **)(int *, char *, int *, Camera *))(v4 + 16))(
    &this->m_ScriptResult + 429,
    &byte_80AC07,
    &v36,
    this);
  ((UIStatic *)(&this->m_ScriptResult + 429))->CreateFromTemplate();
  v36 += 68;
  v39 -= 50;
  v5 = *(&this->m_ScriptResult + 467);
  v37 += 50;
  v38 -= 68;
  (*(void ( **)(int *, char *, int *, Camera *))(v5 + 16))(
    &this->m_ScriptResult + 467,
    &byte_80AC07,
    &v36,
    this);
  sub_446010(&this->m_ScriptResult + 467);
  ((UICaption *)(&this->m_ScriptResult + 467))->SetEnable((int)(&this->m_ScriptResult + 118), 0);
  v6 = *(&this->m_ScriptResult + 183) + 160;
  v42 = *(&this->m_ScriptResult + 182) + 200;
  v7 = *(&this->m_ScriptResult + 186);
  v43 = v6;
  v8 = *(&this->m_ScriptResult + 187);
  v41 = 160;
  v33 = 160;
  v35 = v8 + 160;
  v9 = &this->m_ScriptResult + 273;
  v34 = v7 + 370;
  v10 = *(&this->m_ScriptResult + 273);
  v40 = 200;
  v32 = 370;
  (*(void ( **)(int *, char *, int *, Camera *))(v10 + 16))(
    &this->m_ScriptResult + 273,
    &byte_80AC03,
    &v32,
    this);
  ((UIStatic *)(&this->m_ScriptResult + 273))->CreateFromTemplate();
  v11 = *(&this->m_ScriptResult + 186);
  v32 = v40 + 2;
  v12 = *(&this->m_ScriptResult + 187);
  v33 = v41 + 176;
  v35 = v41 + 176 + v12;
  v34 = v40 + 2 + v11;
  (*(void ( **)(int *, char *, int *, Camera *))(*(&this->m_ScriptResult + 311) + 16))(
    &this->m_ScriptResult + 311,
    &byte_80AC04,
    &v32,
    this);
  ((UIStatic *)(&this->m_ScriptResult + 311))->CreateFromTemplate();
  v13 = v40 + 170 + *(&this->m_ScriptResult + 186);
  v33 = v43 - *(&this->m_ScriptResult + 187) - 4;
  v32 = v40 + 170;
  v34 = v13;
  v14 = *(&this->m_ScriptResult + 349);
  v35 = v43 - 4;
  (*(void ( **)(int *, char *, int *, Camera *))(v14 + 16))(
    &this->m_ScriptResult + 349,
    &byte_80AC05,
    &v32,
    this);
  ((UIStatic *)(&this->m_ScriptResult + 349))->CreateFromTemplate();
  v32 = v42 - *(&this->m_ScriptResult + 186) - 2;
  v15 = *(&this->m_ScriptResult + 187);
  v34 = v42 - 2;
  v35 = v41 + 176 + v15;
  v33 = v41 + 176;
  (*(void ( **)(int *, char *, int *, Camera *))(*(&this->m_ScriptResult + 387) + 16))(
    &this->m_ScriptResult + 387,
    &byte_80AC06,
    &v32,
    this);
  ((UIStatic *)(&this->m_ScriptResult + 387))->CreateFromTemplate();
  ((UIStatic *)(&this->m_ScriptResult + 387))->CreateFromTemplate();
  v16 = 4;
  do
  {
    (*(void ( **)(int *, _DWORD))*v9)(v9, 0);
    v9 += 38;
    --v16;
  }
  while ( v16 );
  (*(void ( **)(int *, char *, int *, Camera *))(*(&this->m_ScriptResult + 189) + 16))(
    &this->m_ScriptResult + 189,
    &byte_80AC01,
    &v40,
    this);
  ((UIStatic *)(&this->m_ScriptResult + 189))->CreateFromTemplate();
  (**((void ( ***)(int *, _DWORD))&this->m_ScriptResult + 189))(&this->m_ScriptResult + 189, 0);
  v17 = *(&this->m_ScriptResult + 185);
  v18 = *(&this->m_ScriptResult + 184);
  v19 = *(&this->m_ScriptResult + 183) / 2 - v17 / 2 + v41 - 1;
  v20 = *(&this->m_ScriptResult + 182);
  v44[3] = v19 + v17;
  v44[1] = v19;
  v44[0] = v20 / 2 - v18 / 2 + v40 - 2;
  v21 = *(&this->m_ScriptResult + 227);
  v44[2] = v44[0] + v18;
  (*(void ( **)(int *, char *, _DWORD *, Camera *))(v21 + 16))(
    &this->m_ScriptResult + 227,
    &byte_80AC02,
    v44,
    this);
  ((UIStatic *)(&this->m_ScriptResult + 227))->CreateFromTemplate();
  (**((void ( ***)(int *, _DWORD))&this->m_ScriptResult + 227))(&this->m_ScriptResult + 227, 0);
  *(&this->m_ScriptResult + 266) = 2;
  v22 = *((float *)&this->m_ScriptResult + 2447);
  if ( v22 > 0.0 )
  {
    *((float *)&this->m_ScriptResult + 268) = *((float *)&this->m_ScriptResult + 2447);
    *((float *)&this->m_ScriptResult + 272) = v22;
    *((_BYTE *)&this->m_ScriptResult + 1080) = 0;
  }
  else
  {
    *(&this->m_ScriptResult + 268) = 0;
    *((_BYTE *)&this->m_ScriptResult + 1080) = 1;
  }
  *(&this->m_ScriptResult + 269) = 1;
  for ( i = 0; i < 5; ++i )
    ((UIScenePanel *)this)->ActivatePanel(i);
  nVal[1] = 245;
  nVal[0] = 246;
  nVal[2] = 446;
  nVal[3] = 345;
  ((ARC_PlayerAtt *)(&this->m_ScriptResult + 2451))->Create((int)&byte_ABC00B, (int)nVal);
  ((UIItem *)(&this->m_ScriptResult + 2451))->SetData(31);
  v31 = 0;
  v24 = &Buffer;
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v31) )
    {
      ((RoleSystem *)v24)->RecalcAggregatedStats(0);
      v25 = (int *)&v24->m_partyActor.m_curact[39];
      v26 = 12;
      do
      {
        v27 = *(v25 - 12);
        if ( *v25 < v27 )
        {
          if ( *v25 <= 0 )
            *v25 = 0;
        }
        else
        {
          *v25 = v27;
        }
        ++v25;
        --v26;
      }
      while ( v26 );
    }
    v24 = (RoleSystem *)((char *)v24 + 1408);
    ++v31;
  }
  while ( (int)v24 < (int)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY );
  v46[1] = 200;
  v46[0] = 250;
  v46[2] = 550;
  v46[3] = 328;
  ((ARC_PlayerAtt *)(&this->m_ScriptResult + 2793))->Create(-5520641, (int)v46);
  ((UIItem *)(&this->m_ScriptResult + 2793))->SetData(31);
  v28 = *(&this->m_ScriptResult + 2814) + 28;
  *(&this->m_ScriptResult + 2817) = *(&this->m_ScriptResult + 2813) + 6;
  v29 = *(&this->m_ScriptResult + 2816);
  *(&this->m_ScriptResult + 2818) = v28;
  v30 = *(&this->m_ScriptResult + 2815) - 6;
  *(&this->m_ScriptResult + 2820) = v29 - 38;
  *(&this->m_ScriptResult + 3129) = 0;
  *(&this->m_ScriptResult + 3130) = 22;
  *(&this->m_ScriptResult + 2819) = v30;
  sub_445FA0(&this->m_ScriptResult + 2907);
  ((UICaption *)(&this->m_ScriptResult + 2907))->SetEnable((int)dword_DDAF3C, 0);
  *((_BYTE *)&this->m_ScriptResult + 12540) = 0;
  *(&this->m_ScriptResult + 3136) = 0;
  *((_BYTE *)&this->m_ScriptResult + 12548) = 0;
}
