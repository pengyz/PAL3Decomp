#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/CameraCtrl.h"
#include "Role/Actor.h"
#include "Misc/Array.h"
#include "Combat/CCBAI.h"
#include "Combat/CCBCamControl.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Misc/CCBPanelSlot.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageCam.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Scene/CameraCtrl.h"
#include "Combat/Combat.h"
#include "Misc/GRP_KEYREG.h"
#include "GameBase/GRPinput.h"
#include "GameBase/InputSystem.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget2.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneMgr.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/UI3DCtrl.h"
#include "UI/UICamera.h"
#include "Misc/UIFrameWnd.h"
#include "Misc/UIGameOver.h"
#include "Misc/UILoadingFrm.h"
#include "UI/UIQuadManager.h"
#include "UI/UIWnd.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/scVarStack.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern CHAR byte_DCD03C[256];
extern CHAR byte_DCD13C[256];

// 0x0041C1B0
int CameraCtrl::InitParams(void *pParams)
{
  int result; // eax

  this->m_nInitParams = 0;
  this->m_nParamState = 0;
  this->m_nParamA = *(_DWORD *)pParams;
  this->m_nParamB = *((_DWORD *)pParams + 1);
  result = *((_DWORD *)pParams + 2);
  this->m_nParamC = result;
  return result;
}

// 0x0041C630
void CameraCtrl::SetAsCurrent(int flags)
{
  if ( (flags & 2) != 0 )
    (((gbCamera *)&this->m_fMinDist))->gbCamera::SetLookAt(&this->m_vecLookAt, (gbVec3D *)&this->m_nAsCurrent, &this->m_vecUpDir);
  (((gbCamera *)&this->m_fMinDist))->gbCamera::SetAsCurrent(flags);
}

// 0x0041C670
float * CameraCtrl::CalcOrbitalPos(
        
        float *pfOut,
        float fTargetX,
        float fTargetY,
        float fTargetZ)
{
  long double v5; // st7
  float *result; // eax
  long double v7; // st7
  float m_fCamDist; // st6
  float v9; // [esp+0x0] [ebp-0x18]
  float v10; // [esp+0x0] [ebp-0x18]
  float v11; // [esp+0x4] [ebp-0x14]
  float v12; // [esp+0x4] [ebp-0x14]
  float v13; // [esp+0x8] [ebp-0x10]
  float v14; // [esp+0xC] [ebp-0xC]
  float v15; // [esp+0x10] [ebp-0x8]

  v5 = cos(this->m_fAngle);
  result = (float *)pfOut;
  v9 = sin(this->m_fOrbitAngle) * v5;
  v11 = sin(this->m_fAngle);
  v7 = -(v5 * cos(this->m_fOrbitAngle));
  m_fCamDist = this->m_fCamDist;
  v14 = m_fCamDist * v9;
  v15 = m_fCamDist * v11;
  v10 = fTargetX - v14;
  *pfOut = v10;
  v12 = fTargetY - v15;
  pfOut[1] = v12;
  v13 = fTargetZ - v7 * m_fCamDist;
  pfOut[2] = v13;
  return result;
}

// 0x0041CA90
void CameraCtrl::SetDimention(int w, int h)
{
  this->m_nWidth = w;
  this->m_nHeight = h;
  (((gbCamera *)&this->m_fMinDist))->gbCamera::SetDimention(w, h);
}

// 0x0041CAC0
void * CameraCtrl::GetViewTarget(void *pTarget, float *pPos)
{
  float *p_m_fMinDist; // ecx
  float v4; // st7
  float v5; // st6
  void *result; // eax
  float v7; // [esp+0x8] [ebp-0x20]
  float v8; // [esp+0xC] [ebp-0x1C]
  struct gbRay v9; // [esp+0x10] [ebp-0x18] BYREF

  p_m_fMinDist = (float *)&this->m_fMinDist;
  v4 = (float)*(int *)pPos;
  v5 = (float)*((int *)p_m_fMinDist + 117);
  memset(&v9, 0, sizeof(v9));
  v7 = v4 / (v5 * 0.5f) - 1.0f;
  v8 = 1.0f - (float)*((int *)pPos + 1) / ((float)*((int *)p_m_fMinDist + 118) * 0.5f);
  (((gbCamera *)p_m_fMinDist))->gbCamera::GetRayToScreen(v7, v8, &v9);
  result = (void *)pTarget;
  qmemcpy(pTarget, &v9, 0x18u);
  return result;
}

// 0x0041CBD0
BOOL CameraCtrl::IsAngleBelowTarget()
{
  return this->m_fCurAngle < (double)this->m_fTargetAngle;
}

// 0x0041CBF0
float * CameraCtrl::GetLerpPos(
        
        float *pResult,
        float fCurrent,
        float fTarget,
        float fFactor)
{
  float *result; // eax
  long double v6; // st7

  result = (float *)(this->m_nCamState - 1);
  if ( this->m_nCamState == 1 )
  {
    v6 = (1.0 - cos(fFactor * 3.1415927)) * 0.5;
    *pResult = (1.0 - v6) * fCurrent + fTarget * v6;
  }
  else
  {
    result = (float *)pResult;
    *pResult = (1.0 - fFactor) * fCurrent + fTarget * fFactor;
  }
  return result;
}

// 0x0041CC50
int CameraCtrl::UpdateTransition(float fDelta)
{
  float v3; // st7
  int result; // eax
  int v5; // edx
  float *v6; // eax
  float v7; // st6
  float m_fLerpPosX; // st7
  float m_fLerpPosZ; // ecx
  float fFactor; // [esp+0x0] [ebp-0x10]
  float v11; // [esp+0x8] [ebp-0x8]

  v3 = fDelta + this->m_fCurAngle;
  this->m_fCurAngle = v3;
  if ( v3 >= this->m_fTargetAngle )
    this->m_fCurAngle = this->m_fTargetAngle;
  result = this->m_nFlags - 1;
  fFactor = this->m_fCurAngle / this->m_fTargetAngle;
  switch ( this->m_nFlags )
  {
    case 1:
      this->CameraCtrl::GetLerpPos((float *)this->m_pTarget[13]._tail_000, this->m_fAngleSrc, this->m_fAngleDest, fFactor);
      (((InputSystem *)this->m_pTarget))->InputSystem::ProcessKeyboard(1);
      break;
    case 2:
    case 4:
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[12]._tail_000[24], this->m_fFOVLerp, this->m_fFOV, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[12]._tail_000[20], this->m_fParamF, *(float *)&this->m_bCamFlag, fFactor);
      (((InputSystem *)this->m_pTarget))->InputSystem::ProcessKeyboard(this->m_nFlags == 2);
      result = (int)this->m_pTarget;
      *(_DWORD *)(result + 460) = 0;
      break;
    case 3:
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[13]._tail_000[24], this->m_fLerpTargetX, this->m_fLerpPosX, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[13]._tail_000[28], this->m_fLerpTargetY, this->m_fLerpPosY, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[13]._tail_000[32], this->m_fLerpTargetZ, this->m_fLerpPosZ, fFactor);
      (((InputSystem *)this->m_pTarget))->InputSystem::ProcessKeyboard(0);
      break;
    case 6:
      this->CameraCtrl::GetLerpPos((float *)this->m_pTarget[13]._tail_000, this->m_fAngleSrc, this->m_fAngleDest, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[12]._tail_000[24], this->m_fFOVLerp, this->m_fFOV, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[12]._tail_000[20], this->m_fParamF, *(float *)&this->m_bCamFlag, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[13]._tail_000[24], this->m_fLerpTargetX, this->m_fLerpPosX, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[13]._tail_000[28], this->m_fLerpTargetY, this->m_fLerpPosY, fFactor);
      this->CameraCtrl::GetLerpPos((float *)&this->m_pTarget[13]._tail_000[32], this->m_fLerpTargetZ, this->m_fLerpPosZ, fFactor);
      (((InputSystem *)this->m_pTarget))->InputSystem::ProcessKeyboard(0);
      *(_DWORD *)&this->m_pTarget[12]._tail_000[28] = 0;
      break;
    case 7:
      v5 = rand() % 100;
      v6 = (float *)&this->m_pTarget[13]._tail_000[24];
      v7 = fDelta * 60.0f + this->m_fFOV;
      this->m_fFOV = v7;
      m_fLerpPosX = this->m_fLerpPosX;
      v11 = ((float)v5 * 0.009999999776482582f + sin(v7))
          * ((1.0 - this->m_fCurAngle / this->m_fTargetAngle)
           * 0.5)
          * this->m_fAngleDest
          + this->m_fLerpPosY;
      m_fLerpPosZ = this->m_fLerpPosZ;
      v6[1] = v11;
      *v6 = m_fLerpPosX;
      v6[2] = m_fLerpPosZ;
      (((InputSystem *)this->m_pTarget))->InputSystem::ProcessKeyboard(0);
      break;
    default:
      return result;
  }
  return result;
}

// 0x0041CEE0
int CameraCtrl::SetupFollow(int nVal, int nVal2, int nVal3, int nVal4)
{
  int result; // eax

  this->m_pTarget = ((InputSystem *)((InputSystem *)nVal));
  LODWORD(this->m_fAngleDest) = nVal2;
  this->m_fAngleSrc = *(float *)(nVal + 468);
  result = nVal4;
  this->m_nFlags = 1;
  LODWORD(this->m_fTargetAngle) = nVal3;
  this->m_fCurAngle = 0.0f;
  this->m_nCamState = nVal4;
  return result;
}

// 0x0041CF20
int CameraCtrl::SetupOrbit(int nVal, int nVal2, int nVal3, int nVal4, int nVal5)
{
  int result; // eax

  this->m_pTarget = ((InputSystem *)((InputSystem *)nVal));
  LODWORD(this->m_fFOV) = nVal2;
  this->m_fFOVLerp = *(float *)(nVal + 456);
  this->m_bCamFlag = nVal3;
  this->m_fParamF = *(float *)(nVal + 452);
  result = nVal5;
  this->m_nFlags = 2;
  LODWORD(this->m_fTargetAngle) = nVal4;
  this->m_fCurAngle = 0.0f;
  this->m_nCamState = nVal5;
  return result;
}

// 0x0041CF70
int CameraCtrl::SetupTrack(int nVal, int nVal2, int nVal3, int nVal4, int nVal5)
{
  int result; // eax

  this->m_pTarget = ((InputSystem *)((InputSystem *)nVal));
  LODWORD(this->m_fFOV) = nVal2;
  this->m_fFOVLerp = *(float *)(nVal + 456);
  this->m_bCamFlag = nVal3;
  this->m_fParamF = *(float *)(nVal + 452);
  result = nVal5;
  this->m_nFlags = 4;
  LODWORD(this->m_fTargetAngle) = nVal4;
  this->m_fCurAngle = 0.0f;
  this->m_nCamState = nVal5;
  return result;
}

// 0x0041CFC0
int CameraCtrl::SetupDirect(int *p_DWORD, int nVal, int nVal2)
{
  int result; // eax

  this->m_pTarget = ((InputSystem *)((InputSystem *)p_DWORD));
  LODWORD(this->m_fLerpPosX) = (unsigned long)p_DWORD[123];
  LODWORD(this->m_fLerpPosY) = (unsigned long)p_DWORD[124];
  LODWORD(this->m_fLerpPosZ) = (unsigned long)p_DWORD[125];
  LODWORD(this->m_fAngleDest) = nVal2;
  LODWORD(this->m_fTargetAngle) = nVal;
  result = 0;
  this->m_nFlags = 7;
  this->m_fCurAngle = 0.0f;
  this->m_fFOV = 0.0f;
  return result;
}

// 0x0041D010
int CameraCtrl::SetupLerp(int nVal, int *p_DWORD, int nVal2, int nVal3)
{
  float *v5; // eax
  int result; // eax

  this->m_pTarget = ((InputSystem *)((InputSystem *)nVal));
  LODWORD(this->m_fLerpPosX) = (unsigned long)*p_DWORD;
  LODWORD(this->m_fLerpPosY) = (unsigned long)p_DWORD[1];
  LODWORD(this->m_fLerpPosZ) = (unsigned long)p_DWORD[2];
  v5 = (float *)&this->m_pTarget[13]._tail_000[24];
  this->m_fLerpTargetX = *v5;
  this->m_fLerpTargetY = v5[1];
  this->m_fLerpTargetZ = v5[2];
  result = nVal3;
  this->m_nFlags = 3;
  LODWORD(this->m_fTargetAngle) = nVal2;
  this->m_fCurAngle = 0.0f;
  this->m_nCamState = nVal3;
  return result;
}

// 0x0041D070
int CameraCtrl::SmoothTransition(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int *p_DWORD,
        int nVal5)
{
  float *v7; // eax
  InputSystem *m_pTarget; // eax
  int result; // eax

  this->m_pTarget = ((InputSystem *)((InputSystem *)nVal));
  this->m_nFlags = 6;
  LODWORD(this->m_fTargetAngle) = nVal5;
  this->m_fCurAngle = 0.0f;
  this->m_nCamState = 1;
  LODWORD(this->m_fLerpPosX) = (unsigned long)*p_DWORD;
  LODWORD(this->m_fLerpPosY) = (unsigned long)p_DWORD[1];
  LODWORD(this->m_fLerpPosZ) = (unsigned long)p_DWORD[2];
  v7 = (float *)&this->m_pTarget[13]._tail_000[24];
  this->m_fLerpTargetX = *v7;
  this->m_fLerpTargetY = v7[1];
  this->m_fLerpTargetZ = v7[2];
  m_pTarget = (InputSystem *)this->m_pTarget;
  LODWORD(this->m_fFOV) = nVal2;
  this->m_fFOVLerp = *(float *)&m_pTarget[12]._tail_000[24];
  this->m_bCamFlag = nVal3;
  this->m_fParamF = *(float *)&m_pTarget[12]._tail_000[20];
  LODWORD(this->m_fAngleDest) = nVal4;
  result = *(_DWORD *)m_pTarget[13]._tail_000;
  LODWORD(this->m_fAngleSrc) = result;
  return result;
}

// 0x0041D5B0
int CameraCtrl::SetCamMode(int mode)
{
  int result; // eax

  result = mode;
  LODWORD(this->m_mode) = mode;
  return result;
}

// 0x0041D5C0
int CameraCtrl::SetCamDist(int nVal)
{
  int result; // eax

  result = nVal;
  LODWORD(this->m_fCamDist) = nVal;
  return result;
}

// 0x0041D5D0
char * CameraCtrl::UpdateFOVLerp()
{
  char *v2; // ebx
  _DWORD *v3; // eax
  char *v4; // edi
  char *result; // eax
  float *v6; // ebx
  float *v7; // esi
  float v8; // ecx
  float m_fAngleSrc; // eax
  _DWORD *v10; // eax
  float *v11; // esi
  float v12; // ecx
  int v13; // ebp
  size_t v14; // eax
  float v15; // eax
  float m_fTargetAngle; // ecx
  char *v17; // edi
  int v18; // eax
  char *v19; // edx
  int v20; // ebp
  float *p_m_fMinDist; // ebp
  float *p_m_fCurAngle; // esi
  int v23; // edx
  float v24; // ecx
  int v25; // [esp+0xC] [ebp-0x18]
  float v26; // [esp+0x10] [ebp-0x14]
  int m_nFlags; // [esp+0x1C] [ebp-0x8]

  v2 = (char *)operator new(0xFF8u);
  if ( this->m_bCamFlag )
  {
    m_fAngleSrc = this->m_fAngleSrc;
    if ( LODWORD(m_fAngleSrc) >= LODWORD(this->m_fFOV) + 4 * LODWORD(this->m_fFOVLerp) - 4 )
    {
      v13 = ((LODWORD(m_fAngleSrc) - LODWORD(this->m_fTargetAngle)) >> 2) + 1;
      v25 = v13;
      v14 = 8 * v13;
      if ( (v13 & 0x10000000) != 0 )
        v14 = 0;
      v15 = _pal3_coerce_f32(operator new(v14));
      m_fTargetAngle = this->m_fTargetAngle;
      v26 = v15;
      v17 = (char *)(LODWORD(v15) + 4 * ((unsigned int)(2 * v13) >> 2));
      v18 = LODWORD(this->m_fAngleSrc) + 4;
      v19 = (char *)v17;
      if ( LODWORD(m_fTargetAngle) != v18 )
      {
        do
        {
          v20 = *(_DWORD *)LODWORD(m_fTargetAngle);
          LODWORD(m_fTargetAngle) += 4;
          *(_DWORD *)v19 = v20;
          v19 += 4;
        }
        while ( LODWORD(m_fTargetAngle) != v18 );
        v13 = v25;
      }
      operator delete((void *)LODWORD(this->m_fFOV));
      this->m_fFOV = v26;
      LODWORD(this->m_fFOVLerp) = 2 * v13;
      result = (char *)&v17[4 * v13];
      *(_DWORD *)result = (_DWORD)v2;
      m_nFlags = this->m_nFlags;
      p_m_fMinDist = (float *)&this->m_fMinDist;
      p_m_fCurAngle = (float *)&this->m_fCurAngle;
      v23 = *(_DWORD *)v17 + 4088;
      *p_m_fMinDist = *(float *)v17;
      *((_DWORD *)p_m_fMinDist + 1) = v23;
      *((_DWORD *)p_m_fMinDist + 2) = m_nFlags;
      *((_DWORD *)p_m_fMinDist + 3) = (unsigned long)v17;
      v24 = *(float *)result;
      *p_m_fCurAngle = *(float *)result;
      *((_DWORD *)p_m_fCurAngle + 1) = LODWORD(v24) + 4088;
      *((_DWORD *)p_m_fCurAngle + 2) = (unsigned long)v2;
      *((_DWORD *)p_m_fCurAngle + 3) = (unsigned long)result;
    }
    else
    {
      v10 = (_DWORD *)(LODWORD(m_fAngleSrc) + 4);
      LODWORD(this->m_fAngleSrc) = (unsigned long)v10;
      v11 = (float *)&this->m_fCurAngle;
      *v10 = (_DWORD)v2;
      result = (char *)*((_DWORD *)v11 + 3);
      v12 = *(float *)result;
      *v11 = *(float *)result;
      *((_DWORD *)v11 + 1) = LODWORD(v12) + 4088;
      *((_DWORD *)v11 + 2) = (unsigned long)v2;
      *((_DWORD *)v11 + 3) = (unsigned long)result;
    }
  }
  else
  {
    LODWORD(this->m_fFOVLerp) = 2;
    v3 = (_DWORD *)operator new(8u);
    LODWORD(this->m_fFOV) = (unsigned long)v3;
    v3[1] = (_DWORD)v2;
    v4 = (char *)(v2 + 2044);
    result = (char *)(LODWORD(this->m_fFOV) + 4);
    v6 = (float *)&this->m_fMinDist;
    v7 = (float *)&this->m_fCurAngle;
    v8 = *(float *)result;
    *v7 = *(float *)result;
    *v6 = v8;
    *((_DWORD *)v7 + 1) = LODWORD(v8) + 4088;
    *((_DWORD *)v6 + 1) = LODWORD(v8) + 4088;
    *((_DWORD *)v7 + 2) = (unsigned long)v4;
    *((_DWORD *)v6 + 2) = (unsigned long)v4;
    *((_DWORD *)v7 + 3) = (unsigned long)result;
    *((_DWORD *)v6 + 3) = (unsigned long)result;
  }
  return result;
}

// 0x0041D730
void CameraCtrl::PopState()
{
  float m_fAngleSrc; // eax
  float m_fTargetAngle; // eax
  float v4; // eax
  float *p_m_fCurAngle; // esi
  int v6; // edx
  float m_fFOV; // [esp-0x8] [ebp-0x10]

  m_fAngleSrc = this->m_fAngleSrc;
  LODWORD(this->m_fAngleSrc) = LODWORD(m_fAngleSrc) - 4;
  operator delete(*(void **)LODWORD(m_fAngleSrc));
  if ( this->m_bCamFlag )
  {
    v4 = this->m_fAngleSrc;
    p_m_fCurAngle = (float *)&this->m_fCurAngle;
    v6 = *(_DWORD *)LODWORD(v4);
    *p_m_fCurAngle = *(float *)LODWORD(v4);
    *((_DWORD *)p_m_fCurAngle + 1) = v6 + 4088;
    *((_DWORD *)p_m_fCurAngle + 2) = v6 + 4088;
    p_m_fCurAngle[3] = v4;
  }
  else
  {
    m_fTargetAngle = this->m_fTargetAngle;
    if ( LODWORD(m_fTargetAngle) == LODWORD(this->m_fAngleSrc) )
      operator delete(*(void **)LODWORD(m_fTargetAngle));
    this->m_fMinDist = 0.0f;
    this->m_pTarget = ((InputSystem *)0);
    this->m_nFlags = 0;
    this->m_fTargetAngle = 0.0f;
    this->m_fCurAngle = 0.0f;
    this->m_nCamState = 0;
    m_fFOV = this->m_fFOV;
    this->m_fAngleDest = 0.0f;
    this->m_fAngleSrc = 0.0f;
    operator delete((void *)LODWORD(m_fFOV));
  }
}

// 0x0041D7C0
int * CameraCtrl::SetCameraSource(int nVal, int *p_DWORD)
{
  int *result; // eax
  float v4; // edx

  result = (int *)this;
  this->m_pCamera = ((gbCamera *)((gbCamera *)*p_DWORD));
  LODWORD(v4) = (unsigned long)(*p_DWORD + 4088);
  this->m_nFlags = (int)p_DWORD;
  this->m_fMinDist = v4;
  this->m_pTarget = ((InputSystem *)((InputSystem *)nVal));
  return result;
}

// 0x0041D7F0
unsigned int CameraCtrl::SetupCameraArray(int nVal)
{
  int v2; // edi
  unsigned int result; // eax
  gbCamera **v4; // ebx
  gbCamera *v5; // edx
  unsigned int v6; // edi

  v2 = ((char *)this->m_pTarget + 28 * nVal - (char *)this->m_pCamera) / 28;
  if ( v2 < 0 )
    result = -((145 - v2) / 0x92u);
  else
    result = v2 / 0x92u;
  if ( result )
  {
    v4 = (gbCamera **)(4 * result + this->m_nFlags);
    this->m_nFlags = (int)v4;
    v5 = (gbCamera *)*v4;
    this->m_pCamera = ((gbCamera *)(*v4));
    LODWORD(this->m_fMinDist) = (unsigned long)&v5[10].pControl[13];
    v6 = v2 - 146 * result;
    result = (unsigned int)this->m_pCamera;
    this->m_pTarget = ((InputSystem *)((InputSystem *)((char *)this->m_pCamera + 28 * v6)));
  }
  else
  {
    this->m_pTarget = ((InputSystem *)((InputSystem *)((char *)this->m_pTarget + 28 * nVal)));
  }
  return result;
}

// 0x0041D960
void CameraCtrl::ResetSceneMgrParams()
{
  g_fCheckCollision1Out = 0;
  dword_C11424 = 0;
  dword_C11428 = 0;
}

// 0x0041D9A0
void CameraCtrl::UpdateInternal(float fDelta)
{
  CScreenMode *v2; // ecx
  float v3; // st7
  float v4; // st7
  float *p_m_fMinDist; // eax
  float v6; // st7
  CScreenMode *SoundList; // eax
  CScreenMode *v8; // ecx
  CScreenMode *v9; // eax
  Camera *v10; // ecx
  scAsmDecoder *v11; // eax
  RoleSystem *v12; // esi
  GRP_KEYREG *KeyInfo; // eax
  int v14; // edx
  int v15; // ebp
  int v16; // ebx
  int v17; // eax
  int v18; // edi
  float *v19; // eax
  int v20; // esi
  float v21; // st7
  float v22; // st7
  float v23; // st7
  float v24; // st7
  float v25; // st7
  char v26; // al
  bool v27; // cl
  int PressTime; // ecx
  int v29; // eax
  int v30; // esi
  int m_nState; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // esi
  UICamera *v36; // ecx
  int v37; // eax
  int v38; // eax
  float v39; // edx
  float v40; // eax
  float v41; // eax
  float v42; // eax
  float v43; // st7
  int v44; // [esp+0x0] [ebp-0x5C]
  float pDist; // [esp+0x10] [ebp-0x4C] BYREF
  int v46; // [esp+0x14] [ebp-0x48]
  float pOut2; // [esp+0x18] [ebp-0x44] BYREF
  float v48; // [esp+0x1C] [ebp-0x40] BYREF
  gbVec3D pfVal; // [esp+0x20] [ebp-0x3C] BYREF
  struct gbVec3D pOut[2]; // [esp+0x2C] [ebp-0x30] BYREF
  float pMat[6]; // [esp+0x44] [ebp-0x18] BYREF

  if ( g_nCameraUpdateCount <= 0 || !g_pRoleSystem )
    return;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pPos);
  if ( g_nRoleSystem_58B234 && g_ScriptSystemData.m_nGameMode != 1 )
  {
    v46 = *(_DWORD *)&g_Input.MouseState[8];
    if ( *(_DWORD *)&g_Input.MouseState[8] )
    {
      v3 = (float)v46 * 0.0013962633674964309f;
      pDist = v3;
      if ( v3 <= 1.5700001f )
      {
        if ( pDist < -1.5700001f )
          pDist = -1.5700000524520874f;
        (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamMode(SLODWORD(pDist));
      }
      else
      {
        pDist = 1.5700000524520874f;
        (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamMode(1070134723);
      }
    }
    else
    {
      v2 = (CScreenMode *)(g_Input.KeyInfo[13].Data & 0xF);
      if ( (_BYTE)v2 == 1 )
      {
        (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamMode(1034147594);
      }
      else if ( (g_Input.KeyInfo[14].Data & 0xF) == 1 )
      {
        (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamMode(-1113336054);
      }
    }
  }
  if ( dword_C116F0 )
  {
    v4 = 0.0f;
    if ( (g_Input.KeyInfo[4].Data & 0xF) == 1 )
    {
      v4 = 1.0f;
    }
    else if ( (g_Input.KeyInfo[5].Data & 0xF) == 1 )
    {
      v4 = -1.0f;
    }
    if ( (g_Input.KeyInfo[38].Data & 0xF) == 1 )
    {
      p_m_fMinDist = (float *)&g_pCameraCtrl->m_fMinDist;
      v6 = v4 + g_pCameraCtrl->m_fMinDist;
      g_pCameraCtrl->m_pTarget = 0;
      *p_m_fMinDist = v6;
    }
    else if ( (g_Input.KeyInfo[39].Data & 0xF) == 1 )
    {
      g_pCameraCtrl->m_fCamDist = v4 * 8.0 + g_pCameraCtrl->m_fCamDist;
    }
    else if ( (g_Input.KeyInfo[40].Data & 0xF) == 1 )
    {
      g_pCameraCtrl->m_fAngle = v4 * 0.039250001 + g_pCameraCtrl->m_fAngle;
    }
    else if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      *((float *)&g_pCameraCtrl->m_vecUpDir + 6) = v4 + v4 + *((float *)&g_pCameraCtrl->m_vecUpDir + 6);
    }
    return;
  }
  SoundList = (CScreenMode *)(((CScreenMode *)v2))->CScreenMode::GetSoundList();
  (((CScreenMode *)SoundList))->CScreenMode::SetAudioParam();
  v9 = (CScreenMode *)(((CScreenMode *)v8))->CScreenMode::GetSoundList();
  if ( (((CScreenMode *)v9))->CScreenMode::IsAudioReady() && !byte_C10CC0 )
  {
    if ( g_nSceneState == 2 && g_ScriptSystemData.m_nGameMode == 2 && g_Input.KeyInfo[12].PressTime == 1 )
    {
      v10 = (Camera *)(g_Input.KeyInfo[12].Data & 0xF);
      if ( (_BYTE)v10 == 1
        && !(*(int ( **)(int *))(g_pRoleSystem->m_bvisible + 4))(&g_pRoleSystem->m_bvisible) )
      {
        v11 = (scAsmDecoder *)((char *)&dword_C10CC8->m_stack + 1);
        if ( (int)&dword_C10CC8->m_stack + 1 > 4 )
          v11 = 0;
        if ( !*((_BYTE *)&v11->m_stack + (_DWORD)(&g_RoleSlotBuf.dword_17AA450 + 148)) )
        {
          do
          {
            v11 = (scAsmDecoder *)((char *)v11 + 1);
            if ( (int)v11 > 4 )
              v11 = 0;
          }
          while ( v11 != dword_C10CC8 && !*((_BYTE *)&v11->m_stack + (_DWORD)(&g_RoleSlotBuf.dword_17AA450 + 148)) );
        }
        (((scAsmDecoder *)dword_C10CC8))->scAsmDecoder::Execute((int)v11, 1);
      }
    }
    v12 = g_pRoleSystem;
    if ( g_pRoleSystem->m_nMoveMode != 4 )
      goto LABEL_51;
    if ( *(&g_pRoleSystem->m_partyActor.m_nUpdateMode + 5) == 44 )
    {
      KeyInfo = g_Input.KeyInfo;
      v14 = 0;
      while ( 1 )
      {
        v10 = (Camera *)(KeyInfo->Data & 0xF);
        if ( (_BYTE)v10 == 1 )
          break;
        v14 += 16;
        ++KeyInfo;
        if ( v14 >= 656 )
          goto LABEL_50;
      }
      (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
      v12 = g_pRoleSystem;
    }
LABEL_50:
    if ( v12->m_nMoveMode != 4 )
    {
LABEL_51:
      LOBYTE(v46) = 0;
      if ( g_ScriptSystemData.m_nGameMode == 2 )
        LOBYTE(v46) = (((Camera *)v10))->Camera::IsTransitioning();
      (((CCBPanelSlot *)&g_palScript))->CCBPanelSlot::ShowClipped((unsigned __int8)v46);
      if ( (_BYTE)v46 )
      {
        memset(pOut, 0, 12);
        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetDirection(&pOut[0].x);
        pOut[0].y = pOut[0].y + 10.0;
        // [overlay-fix 2026-10-27] C2664: PointWorldToScr 形参 float& 实传 float*（签名标注错）——待语义修复
        // (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::PointWorldToScr(pOut, &v48, &pOut2);
        (((UIWnd *)&g_palScript))->UIWnd::MoveToAbsolute((__int64)((v48 + 1.0) * (double)g_DrvInfo.width * 0.5), (__int64)((1.0 - pOut2) * (double)g_DrvInfo.height * 0.5));
      }
      v15 = 0;
      v16 = 0;
      pDist = 0.0f;
      qmemcpy(pMat, (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::GetViewTarget(pOut, (float *)&pPos.x), sizeof(pMat));
      if ( g_nSceneState != 2 && g_nSceneState != 8 )
        goto LABEL_107;
      v17 = sub_4232D0();
      v18 = v17;
      if ( v17 && *(_DWORD *)(v17 + 1264) == 7 )
        v18 = 0;
      UISceneUpdate();
      v19 = (float *)sub_420E50(pMat);
      v20 = (int)v19;
      if ( !v19 )
      {
LABEL_90:
        if ( v18 && *(_BYTE *)(v18 + 173) != 2 && *(_DWORD *)(v18 + 264) )
        {
          UIQuadManager::GetInstance();
          crt_sub_00541590();
        }
        if ( v20 )
        {
          UIQuadManager::GetInstance();
          crt_sub_00541590();
        }
        if ( !v18 && !v20 )
        {
          UIQuadManager::GetInstance();
          crt_sub_00541590();
        }
        PressTime = g_Input.KeyInfo[0].PressTime;
        if ( g_Input.KeyInfo[0].PressTime != 1 )
          goto LABEL_109;
        if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 )
          goto LABEL_108;
        if ( v18 )
        {
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::UpdateAnimation((float *)v18);
          v15 = 1;
        }
        else
        {
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetActiveRole();
        }
        if ( v20 )
        {
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::SetState(v20);
          goto LABEL_153;
        }
        if ( v15 )
          goto LABEL_153;
LABEL_107:
        PressTime = g_Input.KeyInfo[0].PressTime;
        if ( g_Input.KeyInfo[0].PressTime == 1 )
        {
LABEL_108:
          if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 )
            goto LABEL_115;
        }
LABEL_109:
        v29 = g_Input.KeyInfo[0].Data & 0xF;
        if ( v29 != 1
          && (PressTime != 1 || v29 != 2)
          && (g_Input.KeyInfo[0].Data & 0xFu) <= 1
          && (g_Input.KeyInfo[1].PressTime != 1 || (g_Input.KeyInfo[1].Data & 0xF) != 1) )
        {
          goto LABEL_153;
        }
LABEL_115:
        if ( !Camera::CheckCollision1((float *)&pPos.x, &g_fCheckCollision1Out, &pDist)
          && !Camera::CheckCollision2((float *)&pPos.x, g_pRoleSystem->m_partyActor.m_nState, &g_fCheckCollision1Out) )
        {
          goto LABEL_153;
        }
        LODWORD(pfVal.x) = g_fCheckCollision1Out;
        LODWORD(pfVal.z) = dword_C11428;
        pfVal.y = 0.0f;
        v30 = 0;
        (((GRPinput *)&g_Input))->GRPinput::GetMousePos(&v48, &pOut2);
        if ( v48 != 0.0f || pOut2 != 0.0f )
          v30 = 1;
        g_pRoleSystem->m_nMoveRole = 0;
        if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
        {
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::UpdateRole(&pfVal.x, SLODWORD(pDist), 1);
          m_nState = g_pRoleSystem->m_partyActor.m_nState;
          if ( LODWORD(pDist) != m_nState
            && !g_pRoleSystem->m_nMoveSubMode
            && Camera::CheckCollision2((float *)&pPos.x, m_nState, &pfVal) )
          {
            pfVal.y = 0.0f;
            (((RoleSystem *)&g_pRoleSystem))->RoleSystem::UpdateRole(&pfVal.x, g_pRoleSystem->m_partyActor.m_nState, 1);
          }
        }
        else if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 && (double)g_Input.KeyInfo[0].PressTime * fDelta > 0.5 )
        {
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::MoveRole(&pfVal.x, SLODWORD(pDist), 1, v30);
          v32 = g_pRoleSystem->m_partyActor.m_nState;
          if ( LODWORD(pDist) != v32
            && !g_pRoleSystem->m_nMoveSubMode
            && Camera::CheckCollision2((float *)&pPos.x, v32, &pfVal) )
          {
            pfVal.y = 0.0f;
            (((RoleSystem *)&g_pRoleSystem))->RoleSystem::MoveRole(&pfVal.x, g_pRoleSystem->m_partyActor.m_nState, 1, 1);
          }
        }
        else if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
        {
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::UpdateRole(&pfVal.x, SLODWORD(pDist), 2);
          v33 = g_pRoleSystem->m_partyActor.m_nState;
          if ( LODWORD(pDist) != v33
            && !g_pRoleSystem->m_nMoveSubMode
            && Camera::CheckCollision2((float *)&pPos.x, v33, &pfVal) )
          {
            pfVal.y = 0.0f;
            (((RoleSystem *)&g_pRoleSystem))->RoleSystem::UpdateRole(&pfVal.x, g_pRoleSystem->m_partyActor.m_nState, 2);
          }
        }
        else
        {
          if ( (g_Input.KeyInfo[0].Data & 0xFu) <= 1 || (double)g_Input.KeyInfo[0].PressTime * fDelta <= 0.5 )
          {
LABEL_145:
            if ( (g_bPathEnabled || (_BYTE)v46 && g_ScriptSystemData.m_nGameMode == 2)
              && g_Input.KeyInfo[1].PressTime == 1
              && (g_Input.KeyInfo[1].Data & 0xF) == 1
              && g_pRoleSystem->m_partyActor.m_nState == LODWORD(pDist) )
            {
              (((RoleSystem *)&g_pRoleSystem))->RoleSystem::PathFind(&pfVal.x);
              v16 = 4;
              goto LABEL_166;
            }
            if ( v16 )
              goto LABEL_166;
LABEL_153:
            v35 = 0;
            memset(&pfVal, 0, sizeof(pfVal));
            if ( g_Input.KeyInfo[6].PressTime == 1 )
            {
              v36 = (UICamera *)(g_Input.KeyInfo[6].Data & 0xF);
              if ( (_BYTE)v36 == 1 )
              {
                if ( g_nSceneState == 2 )
                {
                  v37 = sub_4230D0(v36);
                  if ( v37 && *(_DWORD *)(v37 + 1264) != 7 )
                  {
                    if ( *(_BYTE *)(v37 + 173) != 2 && *(_DWORD *)(v37 + 264) )
                      (((RoleSystem *)&g_pRoleSystem))->RoleSystem::UpdateAnimation((float *)v37);
                  }
                  else
                  {
                    UISceneUpdate();
                    v38 = sub_420CD0(v44);
                    if ( v38 )
                      (((RoleSystem *)&g_pRoleSystem))->RoleSystem::SetState(v38);
                  }
                }
                goto LABEL_163;
              }
            }
            if ( (g_Input.KeyInfo[3].Data & 0xF) == 1 )
            {
              v35 = 1;
              pfVal.x = *((float *)&g_pCameraCtrl->m_vecUpDir + 3);
              pfVal.y = *((float *)&g_pCameraCtrl->m_vecUpDir + 4);
              pfVal.z = *((float *)&g_pCameraCtrl->m_vecUpDir + 5);
LABEL_176:
              v16 = 3;
              goto LABEL_177;
            }
            if ( (g_Input.KeyInfo[3].Data & 0xFu) <= 1 )
            {
              if ( (g_Input.KeyInfo[2].Data & 0xF) == 1 )
              {
                pfVal.x = -*((float *)&g_pCameraCtrl->m_vecUpDir + 3);
                pfVal.y = -*((float *)&g_pCameraCtrl->m_vecUpDir + 4);
                pfVal.z = -*((float *)&g_pCameraCtrl->m_vecUpDir + 5);
                v35 = 1;
                goto LABEL_176;
              }
              if ( (g_Input.KeyInfo[2].Data & 0xFu) <= 1 )
              {
LABEL_177:
                if ( (g_Input.KeyInfo[4].Data & 0xF) == 1 )
                {
                  pOut[0].x = *((float *)&g_pCameraCtrl->m_vecLookAt + 3);
                  pOut[0].y = *((float *)&g_pCameraCtrl->m_vecLookAt + 4);
                  v39 = *((float *)&g_pCameraCtrl->m_vecLookAt + 5);
                  pOut[0].y = 0.0;
                  pOut[0].z = v39;
                  (((gbVec3D *)pOut))->gbVec3D::Normalize();
                  v35 = 1;
                  v16 = 3;
                  pfVal.x = pOut[0].x + pfVal.x;
                  pfVal.y = pfVal.y + pOut[0].y;
                  pfVal.z = pfVal.z + pOut[0].z;
                }
                else if ( (g_Input.KeyInfo[4].Data & 0xFu) <= 1 )
                {
                  if ( (g_Input.KeyInfo[5].Data & 0xF) == 1 )
                  {
                    pOut[0].x = *((float *)&g_pCameraCtrl->m_vecLookAt + 3);
                    pOut[0].y = *((float *)&g_pCameraCtrl->m_vecLookAt + 4);
                    v41 = *((float *)&g_pCameraCtrl->m_vecLookAt + 5);
                    pOut[0].y = 0.0;
                    pOut[0].z = v41;
                    (((gbVec3D *)pOut))->gbVec3D::Normalize();
                    v35 = 1;
                    v16 = 3;
                    pfVal.x = pfVal.x - pOut[0].x;
                    pfVal.y = pfVal.y - pOut[0].y;
                    pfVal.z = pfVal.z - pOut[0].z;
                  }
                  else if ( (g_Input.KeyInfo[5].Data & 0xFu) <= 1 )
                  {
                    if ( v16 != 3 )
                    {
LABEL_163:
                      if ( g_pRoleSystem->m_nMoveMode == 3 )
                      {
                        memset(pOut, 0, 12);
                        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetPosition(&pOut[0].x, 0);
                      }
                      v43 = g_fCameraBlendWeight + fDelta;
                      g_fCameraBlendWeight = v43;
                      if ( v43 > g_fCameraDefaultDist )
                      {
                        g_fCameraBlendWeight = 0.0;
                        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetCount();
                        g_fCameraDefaultDist = (float)(rand() % 30 + 30);
                      }
                      return;
                    }
                  }
                  else
                  {
                    pOut[0].x = *((float *)&g_pCameraCtrl->m_vecLookAt + 3);
                    pOut[0].y = *((float *)&g_pCameraCtrl->m_vecLookAt + 4);
                    v42 = *((float *)&g_pCameraCtrl->m_vecLookAt + 5);
                    pOut[0].y = 0.0;
                    pOut[0].z = v42;
                    (((gbVec3D *)pOut))->gbVec3D::Normalize();
                    v35 = 2;
                    v16 = 3;
                    pfVal.x = pfVal.x - pOut[0].x;
                    pfVal.y = pfVal.y - pOut[0].y;
                    pfVal.z = pfVal.z - pOut[0].z;
                  }
                }
                else
                {
                  pOut[0].x = *((float *)&g_pCameraCtrl->m_vecLookAt + 3);
                  pOut[0].y = *((float *)&g_pCameraCtrl->m_vecLookAt + 4);
                  v40 = *((float *)&g_pCameraCtrl->m_vecLookAt + 5);
                  pOut[0].y = 0.0;
                  pOut[0].z = v40;
                  (((gbVec3D *)pOut))->gbVec3D::Normalize();
                  v35 = 2;
                  v16 = 3;
                  pfVal.x = pOut[0].x + pfVal.x;
                  pfVal.y = pfVal.y + pOut[0].y;
                  pfVal.z = pfVal.z + pOut[0].z;
                }
                (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetActiveRole();
                if ( g_pRoleSystem->m_nCoreState == 2 )
                  v35 = 2;
                (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetPosition(&pfVal.x, v35);
LABEL_166:
                g_pRoleSystem->m_nMoveMode = v16;
                g_fCameraBlendWeight = 0.0;
                return;
              }
              pfVal.x = -*((float *)&g_pCameraCtrl->m_vecUpDir + 3);
              pfVal.y = -*((float *)&g_pCameraCtrl->m_vecUpDir + 4);
              pfVal.z = -*((float *)&g_pCameraCtrl->m_vecUpDir + 5);
            }
            else
            {
              pfVal.x = *((float *)&g_pCameraCtrl->m_vecUpDir + 3);
              pfVal.y = *((float *)&g_pCameraCtrl->m_vecUpDir + 4);
              pfVal.z = *((float *)&g_pCameraCtrl->m_vecUpDir + 5);
            }
            v35 = 2;
            goto LABEL_176;
          }
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::MoveRole(&pfVal.x, SLODWORD(pDist), 2, v30);
          v34 = g_pRoleSystem->m_partyActor.m_nState;
          if ( LODWORD(pDist) != v34
            && !g_pRoleSystem->m_nMoveSubMode
            && Camera::CheckCollision2((float *)&pPos.x, v34, &pfVal) )
          {
            pfVal.y = 0.0f;
            (((RoleSystem *)&g_pRoleSystem))->RoleSystem::MoveRole(&pfVal.x, g_pRoleSystem->m_partyActor.m_nState, 2, 1);
          }
        }
        v16 = 2;
        goto LABEL_145;
      }
      if ( v18 )
      {
        pOut[0].x = g_pRoleSystem->m_fPosX - v19[10];
        v21 = g_pRoleSystem->m_fPosY - v19[11];
        pfVal.x = pOut[0].x;
        pOut[0].y = v21;
        v22 = g_pRoleSystem->m_fPosZ - v19[12];
        pfVal.y = pOut[0].y;
        pOut[0].z = v22;
        pfVal.z = pOut[0].z;
        v48 = (((gbVec3D *)&pfVal))->gbVec3D::Length();
        pOut[0].x = g_pRoleSystem->m_fPosX - *(float *)(v18 + 160);
        v23 = g_pRoleSystem->m_fPosY - *(float *)(v18 + 164);
        pfVal.x = pOut[0].x;
        pOut[0].y = v23;
        v24 = g_pRoleSystem->m_fPosZ - *(float *)(v18 + 168);
        pfVal.y = pOut[0].y;
        pOut[0].z = v24;
        pfVal.z = pOut[0].z;
        v25 = (((gbVec3D *)&pfVal))->gbVec3D::Length();
        if ( v25 < v48 )
        {
LABEL_89:
          v20 = 0;
          goto LABEL_90;
        }
        v18 = 0;
      }
      if ( *(_BYTE *)(v20 + 173) )
      {
        v26 = *(_BYTE *)(v20 + 244);
        if ( v26 != 14 || *(unsigned __int8 *)(v20 + 246) == g_pRoleSystem->m_partyActor.m_nState )
        {
          v27 = v26 == 11
             || v26 == 12
             || v26 == 14
             || v26 == 15
             || v26 == 16
             || v26 == 20
             || v26 == 23
             || v26 == 24
             || v26 == 26
             || v26 == 27
             || v26 == 42
             || v26 == 41;
          if ( v26 == 26 && (*(_BYTE *)(v20 + 80) || *(_BYTE *)(v20 + 81) >= 3u) )
            v27 = 0;
          if ( (v26 != 23 || *(_BYTE *)(v20 + 174) && *(_DWORD *)(v20 + 252) != 1) && v27 )
            goto LABEL_90;
        }
      }
      goto LABEL_89;
    }
  }
}

// 0x0041E720
void CameraCtrl::AttachToRole(int nVal)
{
  int v1; // eax
  PAL3 *v2; // ecx
  RoleSystem *v3; // esi
  float pOut[3]; // [esp+0x0] [ebp-0xC] BYREF

  if ( nVal )
    v1 = g_nCameraUpdateCount + 1;
  else
    v1 = g_nCameraUpdateCount - 1;
  g_nCameraUpdateCount = v1;
  if ( v1 > 0 )
  {
    v3 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
    do
    {
      (((RoleSystem *)v3))->RoleSystem::GetActiveRole();
      v3 = (RoleSystem *)((char *)v3 + 8704);
    }
    while ( (int)v3 < (int)&g_RoleSystemArrayEnd );
    g_fCameraBlendWeight = 0.0;
  }
  else
  {
    UIQuadManager::GetInstance();
    crt_sub_00541590();
    (((PAL3 *)v2))->PAL3::UIPostProcess();
    if ( g_pRoleSystem->m_nMoveMode == 3 )
    {
      memset(pOut, 0, sizeof(pOut));
      (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetPosition(pOut, 0);
      g_pRoleSystem->m_nMoveMode = 2;
    }
    g_fCameraBlendWeight = 0.0;
  }
}

// 0x0041EB50
int CameraCtrl::GetModeByIndex(int nVal)
{
  switch ( nVal )
  {
    case 5:
      return 2;
    case 7:
      return 1;
    case 11:
      return 3;
  }
  return 0;
}

// 0x0041EF30
int CameraCtrl::InitPathState()
{
  int result; // eax

  byte_C11748 = 0;
  dword_C1171C = 0x7FFFFFFF;
  strcpy((char *)&unk_C11720, (const char *)&dir[32]);
  result = 1;
  unk_C11720.m_bEnabled = 1;
  unk_C11720.m_nTodo_02C = -1;
  unk_C11720.m_nTodo_024 = 0;
  unk_C11720.m_nTodo_34 = 0;
  byte_C11750 = 0;
  byte_C11752 = 1;
  return result;
}

// 0x00487610
int * CameraCtrl::LoadRoleParams()
{
  int *result; // eax
  float *p_m_roleParams; // esi
  float *v3; // ecx
  int v4; // edx
  int v5; // edi

  result = (int *)g_fCamRoleParams;
  p_m_roleParams = (float *)&this->m_roleParams;
  do
  {
    v3 = (float *)p_m_roleParams;
    v4 = 5;
    do
    {
      v5 = (unsigned long)(*result++);
      *(_DWORD *)v3++ = v5;
      --v4;
    }
    while ( v4 );
    p_m_roleParams += 75;
  }
  while ( (int)result < (int)g_ScriptCounters );
  return result;
}

// 0x0048B370
int CameraCtrl::BuildRenderLists()
{
  int m_nViewMode; // ecx
  int v3; // eax
  unsigned int v4; // edx
  unsigned int m_nViewFlags; // eax
  gbCamera **v6; // eax
  gbCamera *v7; // edx
  int v8; // edi
  int v9; // ecx
  int v10; // edx
  gbCamera **v11; // ebx
  gbCamera **v12; // edx
  float zNear; // ebx
  gbCamera *v14; // ebp
  gbCamera *v15; // edx
  gbCamera *v16; // eax
  int v17; // edi
  int v18; // edx
  int v19; // ecx
  gbCamera **v20; // ebx
  gbCamera **v21; // edx
  float zFar; // ebp
  gbCamera *v23; // ebp
  gbCamera *v24; // edx
  gbCamera *v25; // eax
  int v26; // edi
  int v27; // edx
  int v28; // ecx
  gbCamera **v29; // ebx
  gbCamera **v30; // ecx
  gbCamera *v31; // ebp
  float v32; // edx
  InputSystem *v33; // eax
  int v34; // edi
  int v35; // edx
  int v36; // ecx
  CameraCtrl *v37; // ebx
  CameraCtrl *v38; // edx
  float Hscreen; // ebx
  gbCamera *v40; // ebp
  gbCamera *v41; // edx
  gbCamera *v42; // eax
  int v43; // edi
  int v44; // edx
  int v45; // ecx
  gbCamera **v46; // ebx
  gbCamera **v47; // ecx
  gbCamera *v48; // ebp
  gbCamera *v49; // edx
  gbCamera *v50; // eax
  int v51; // edi
  int v52; // edx
  int v53; // ecx
  gbCamera **v54; // ebx
  gbCamera **v55; // ecx
  gbCamera *v56; // ebp
  gbCamera *v57; // edx
  gbCamera *v58; // eax
  int v59; // edi
  int v60; // edx
  int v61; // ecx
  gbCamera **v62; // ebx
  gbCamera **v63; // ecx
  int result; // eax
  float v65; // [esp+0x14] [ebp-0x14]
  float Wscreen; // [esp+0x18] [ebp-0x10]
  gbCamera *v67; // [esp+0x20] [ebp-0x8]
  gbCamera *v68; // [esp+0x20] [ebp-0x8]
  float v69; // [esp+0x20] [ebp-0x8]
  gbCamera *v70; // [esp+0x20] [ebp-0x8]
  gbCamera *v71; // [esp+0x20] [ebp-0x8]
  gbCamera *v72; // [esp+0x20] [ebp-0x8]

  RefreshPartyRoleData();
  memset(&this->m_CamBlocks, 0, 0xBA40u);
  this->m_nViewMode = 0;
  do
  {
    this->m_nViewFlags = 0;
    while ( 1 )
    {
      m_nViewMode = this->m_nViewMode;
      v3 = *(&g_SceneMgrPrefix.m_nSize + 4 * m_nViewMode);
      v4 = v3 ? (*((_DWORD *)&g_SceneMgrPrefix.m_pData + 4 * m_nViewMode) - v3) / 12 : 0;
      m_nViewFlags = this->m_nViewFlags;
      if ( m_nViewFlags >= v4 )
        break;
      v6 = (gbCamera **)(*(&g_SceneMgrPrefix.m_nSize + 4 * m_nViewMode) + 12 * m_nViewFlags);
      v7 = (gbCamera *)v6[2];
      if ( LOBYTE(v7->OrthoSize) )
      {
        zNear = v7->zNear;
        v65 = zNear;
        if ( zNear == 0.0f
          || LODWORD(v7->zFar) == 1
          || LODWORD(v7->Wscreen) == 1
          || LODWORD(v7->Hscreen) == 1
          || v7->Viewport.x == 1 )
        {
          zFar = v7->zFar;
          if ( zFar == 0.0f
            || LODWORD(zNear) == 1
            || LODWORD(v7->Wscreen) == 1
            || LODWORD(v7->Hscreen) == 1
            || v7->Viewport.x == 1 )
          {
            Wscreen = v7->Wscreen;
            if ( Wscreen == 0.0f
              || LODWORD(zNear) == 1
              || LODWORD(zFar) == 1
              || LODWORD(v7->Hscreen) == 1
              || v7->Viewport.x == 1 )
            {
              Hscreen = v7->Hscreen;
              if ( Hscreen == 0.0f )
                goto LABEL_59;
              zFar = v7->zFar;
              if ( LODWORD(v65) == 1 || LODWORD(v7->zFar) == 1 )
                goto LABEL_59;
              if ( LODWORD(Wscreen) == 1 || v7->Viewport.x == 1 )
              {
                zFar = v7->zFar;
LABEL_59:
                if ( !v7->Viewport.x
                  || LODWORD(v65) == 1
                  || LODWORD(zFar) == 1
                  || LODWORD(Wscreen) == 1
                  || LODWORD(Hscreen) == 1 )
                {
                  v56 = (gbCamera *)*v6;
                  v57 = (gbCamera *)v6[1];
                  v58 = (gbCamera *)v6[2];
                  v72 = (gbCamera *)v57;
                  if ( *((_BYTE *)&v58[1].ViewMatrix.tx + m_nViewMode) )
                  {
                    v59 = 0;
                    v60 = 9536 * m_nViewMode;
                    v61 = *((_DWORD *)&this[2].m_nViewBase + 2384 * m_nViewMode + 71);
                    if ( v61 <= 0 )
                    {
LABEL_75:
                      v63 = (gbCamera **)((char *)&this[2].m_nViewBase + 12 * v61 + v60 + 288);
                      *v63 = v56;
                      v63[1] = v72;
                      v63[2] = v58;
                      ++*((_DWORD *)&this[2].m_nViewBase + 2384 * this->m_nViewMode + 71);
                    }
                    else
                    {
                      v62 = (gbCamera **)((char *)&this[2].m_nViewBase + v60 + 288);
                      while ( v56 != *v62 )
                      {
                        ++v59;
                        v62 += 3;
                        if ( v59 >= v61 )
                          goto LABEL_75;
                      }
                    }
                  }
LABEL_76:
                  ++this->m_nViewFlags;
                }
                else
                {
                  v48 = (gbCamera *)*v6;
                  v49 = (gbCamera *)v6[1];
                  v50 = (gbCamera *)v6[2];
                  v71 = (gbCamera *)v49;
                  if ( !*((_BYTE *)&v50[1].ViewMatrix.tx + m_nViewMode) )
                    goto LABEL_76;
                  v51 = 0;
                  v52 = 9536 * m_nViewMode;
                  v53 = *(&this[2].m_nSlotParam + 2384 * m_nViewMode + 52);
                  if ( v53 > 0 )
                  {
                    v54 = (gbCamera **)((char *)&this[2].m_nSlotParam + v52 + 212);
                    while ( v48 != *v54 )
                    {
                      ++v51;
                      v54 += 3;
                      if ( v51 >= v53 )
                        goto LABEL_69;
                    }
                    goto LABEL_76;
                  }
LABEL_69:
                  v55 = (gbCamera **)((char *)&this[2].m_nSlotParam + 12 * v53 + v52 + 212);
                  *v55 = v48;
                  v55[1] = v71;
                  v55[2] = v50;
                  ++*(&this[2].m_nSlotParam + 2384 * this->m_nViewMode + 52);
                  ++this->m_nViewFlags;
                }
              }
              else
              {
                v40 = (gbCamera *)*v6;
                v41 = (gbCamera *)v6[1];
                v42 = (gbCamera *)v6[2];
                v70 = (gbCamera *)v41;
                if ( !*((_BYTE *)&v42[1].ViewMatrix.tx + m_nViewMode) )
                  goto LABEL_76;
                v43 = 0;
                v44 = 9536 * m_nViewMode;
                v45 = *(&this[1].m_nViewState + 2384 * m_nViewMode + 96);
                if ( v45 > 0 )
                {
                  v46 = (gbCamera **)((char *)&this[1].m_nViewState + v44 + 388);
                  while ( v40 != *v46 )
                  {
                    ++v43;
                    v46 += 3;
                    if ( v43 >= v45 )
                      goto LABEL_57;
                  }
                  goto LABEL_76;
                }
LABEL_57:
                v47 = (gbCamera **)((char *)&this[1].m_nViewState + 12 * v45 + v44 + 388);
                *v47 = v40;
                v47[1] = v70;
                v47[2] = v42;
                ++*(&this[1].m_nViewState + 2384 * this->m_nViewMode + 96);
                ++this->m_nViewFlags;
              }
            }
            else
            {
              v31 = (gbCamera *)*v6;
              v32 = *((float *)v6 + 1);
              v33 = (InputSystem *)v6[2];
              v69 = v32;
              if ( !v33[15]._tail_000[m_nViewMode + 32] )
                goto LABEL_76;
              v34 = 0;
              v35 = 9536 * m_nViewMode;
              v36 = *((_DWORD *)&this[1].m_fOrbitAngle + 2384 * m_nViewMode);
              if ( v36 > 0 )
              {
                v37 = (CameraCtrl *)((char *)this + v35 + 4548);
                while ( v31 != v37->m_pCamera )
                {
                  ++v34;
                  v37 = (CameraCtrl *)((char *)v37 + 12);
                  if ( v34 >= v36 )
                    goto LABEL_46;
                }
                goto LABEL_76;
              }
LABEL_46:
              v38 = (CameraCtrl *)((char *)this + 12 * v36 + v35 + 4548);
              v38->m_pCamera = v31;
              v38->m_fMinDist = v69;
              v38->m_pTarget = v33;
              ++*((_DWORD *)&this[1].m_fOrbitAngle + 2384 * this->m_nViewMode);
              ++this->m_nViewFlags;
            }
          }
          else
          {
            v23 = (gbCamera *)*v6;
            v24 = (gbCamera *)v6[1];
            v25 = (gbCamera *)v6[2];
            v68 = (gbCamera *)v24;
            if ( !*((_BYTE *)&v25[1].ViewMatrix.tx + m_nViewMode) )
              goto LABEL_76;
            v26 = 0;
            v27 = 9536 * m_nViewMode;
            v28 = *((_DWORD *)&this[1].m_nViewBase + 2384 * m_nViewMode + 199);
            if ( v28 > 0 )
            {
              v29 = (gbCamera **)((char *)&this[1].m_nViewBase + v27 + 800);
              while ( v23 != *v29 )
              {
                ++v26;
                v29 += 3;
                if ( v26 >= v28 )
                  goto LABEL_35;
              }
              goto LABEL_76;
            }
LABEL_35:
            v30 = (gbCamera **)((char *)&this[1].m_nViewBase + 12 * v28 + v27 + 800);
            *v30 = v23;
            v30[1] = v68;
            v30[2] = v25;
            ++*((_DWORD *)&this[1].m_nViewBase + 2384 * this->m_nViewMode + 199);
            ++this->m_nViewFlags;
          }
        }
        else
        {
          v14 = (gbCamera *)*v6;
          v15 = (gbCamera *)v6[1];
          v16 = (gbCamera *)v6[2];
          v67 = (gbCamera *)v15;
          if ( !*((_BYTE *)&v16[1].ViewMatrix.tx + m_nViewMode) )
            goto LABEL_76;
          v17 = 0;
          v18 = 9536 * m_nViewMode;
          v19 = *(&this[1].m_CamBlocks + 2384 * m_nViewMode + 170);
          if ( v19 > 0 )
          {
            v20 = (gbCamera **)((char *)&this[1].m_CamBlocks + v18 + 684);
            while ( v14 != *v20 )
            {
              ++v17;
              v20 += 3;
              if ( v17 >= v19 )
                goto LABEL_24;
            }
            goto LABEL_76;
          }
LABEL_24:
          v21 = (gbCamera **)((char *)&this[1].m_CamBlocks + 12 * v19 + v18 + 684);
          *v21 = v14;
          v21[1] = v67;
          v21[2] = v16;
          ++*(&this[1].m_CamBlocks + 2384 * this->m_nViewMode + 170);
          ++this->m_nViewFlags;
        }
      }
      else
      {
        if ( !*((_BYTE *)&v7[1].ViewMatrix.tx + m_nViewMode) )
          goto LABEL_76;
        v8 = 0;
        v9 = 9536 * m_nViewMode;
        v10 = *(int *)((char *)&this->m_CamBlocks + v9);
        if ( v10 > 0 )
        {
          v11 = (gbCamera **)((char *)&this->m_CamBlocks + v9 + 4);
          while ( *v6 != *v11 )
          {
            ++v8;
            v11 += 3;
            if ( v8 >= v10 )
              goto LABEL_13;
          }
          goto LABEL_76;
        }
LABEL_13:
        v12 = (gbCamera **)((char *)&this->m_CamBlocks + 12 * v10 + v9 + 4);
        *v12 = *v6;
        v12[1] = v6[1];
        v12[2] = v6[2];
        ++*(&this->m_CamBlocks + 2384 * this->m_nViewMode);
        ++this->m_nViewFlags;
      }
    }
    result = this->m_nViewMode + 1;
    this->m_nViewMode = result;
  }
  while ( result < 5 );
  return result;
}

// 0x0048C520
void CameraCtrl::CalcStatPower(int nVal)
{
  int v2; // ebx
  int v3; // esi
  int v4; // edx
  __int16 *v5; // edi
  int v6; // [esp+0x18] [ebp+0x8]

  v2 = *(_DWORD *)(nVal + 8);
  v3 = 0;
  v4 = 0;
  v5 = (__int16 *)(v2 + 592);
  do
  {
    if ( *v5 > 0 )
      v3 += *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * v6 + v4)
          - g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * v6 + 2 + v4];
    ++v4;
    ++v5;
  }
  while ( v4 < 12 );
}

// 0x0048D040
void CameraCtrl::UpdateBlendWeight(int arg0, int nVal)
{
  float *p_m_szText; // edi
  int v5; // ebx
  int v6; // eax
  gbCamera **v7; // ecx
  gbCamera *v8; // edx
  float *v9; // edx
  int v10; // eax
  int v11; // eax
  int *v12; // ecx
  int v13; // eax
  int v14; // edx
  gbCamera **v15; // eax
  int v16; // ecx
  int *TargetRole; // ecx
  int v18; // eax
  gbCamera **v19; // ecx
  int v20; // edx
  int v21; // ecx
  gbCamera **v22; // eax
  int v23; // edx
  CScreenMode *Instance; // eax
  const void *v25; // [esp-0x8] [ebp-0x48]
  int v26; // [esp+0x0] [ebp-0x40]
  gbCamera *v27; // [esp+0x10] [ebp-0x30]
  gbCamera *v28; // [esp+0x14] [ebp-0x2C] BYREF
  gbCamera *v29; // [esp+0x18] [ebp-0x28]
  int p_DWORD; // [esp+0x1C] [ebp-0x24] BYREF
  int m_nBlendTimer; // [esp+0x20] [ebp-0x20]
  int v32; // [esp+0x24] [ebp-0x1C]
  int pConfig; // [esp+0x28] [ebp-0x18] BYREF
  int v34; // [esp+0x2C] [ebp-0x14]
  int SkillNum; // [esp+0x30] [ebp-0x10]
  _BYTE pOut[12]; // [esp+0x34] [ebp-0xC] BYREF
  int nVala; // [esp+0x48] [ebp+0x8]

  p_m_szText = (float *)&this->m_szText;
  sprintf((char *const)&this->m_szText, "%s", unk_C10D38);
  v5 = nVal;
  this->m_bBlendActive = 1;
  v6 = 3 * *((unsigned __int8 *)&this[75].m_dist + nVal) + 12;
  v7 = (gbCamera **)(&this->m_pCamera + 75 * *((unsigned __int8 *)&this[75].m_dist + nVal));
  v27 = (gbCamera *)v7[297];
  v8 = (gbCamera *)v7[298];
  v29 = (gbCamera *)v7[299];
  v28 = (gbCamera *)v8;
  *((float *)&this->m_pCamera + 20 * v6 + 5 * v6 + arg0) = *((float *)&this->m_pCamera + 20 * v6 + 5 * v6 + arg0)
                                                         + 0.0099999998;
  v9 = (float *)&this->m_roleParams
     + 60 * *((unsigned __int8 *)&this[75].m_dist + v5)
     + 15 * *((unsigned __int8 *)&this[75].m_dist + v5)
     + arg0;
  if ( *v9 >= 1.0f )
    *v9 = 1.0;
  v10 = *((unsigned __int8 *)&this[75].m_dist + nVal);
  g_fCamRoleParams[4 * v10 + arg0 + v10] = *(&this->m_roleParams + 60 * v10 + 15 * v10 + arg0);
  if ( !(((UIFrameWnd *)this))->UIFrameWnd::RollProbability(*(&this->m_roleParams
          + 60 * *((unsigned __int8 *)&this[75].m_dist + nVal)
          + 15 * *((unsigned __int8 *)&this[75].m_dist + nVal)
          + arg0)) /* [ROWTABLE] */ )
  {
    if ( (unsigned __int8)CameraCtrl_InitBlendState(nVal) )
    {
      p_DWORD = 0xFFFF;
      m_nBlendTimer = 0;
      v32 = 0;
      this->m_nViewMode = 0;
      if ( ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount() > 0 )
      {
        while ( 1 )
        {
          TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
          v18 = (unsigned long)*TargetRole;
          p_DWORD = (unsigned long)*TargetRole;
          m_nBlendTimer = (unsigned long)TargetRole[1];
          v32 = (unsigned long)TargetRole[2];
          if ( this->m_nBlendTimer <= 0 )
          {
            if ( (gbCamera *)v18 == v27 || (gbCamera *)v18 == v28 || (gbCamera *)v18 == v29 )
            {
              m_nBlendTimer = 1;
              (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
              this->m_nBlendTimer = 0;
              lstrcatA((LPSTR)p_m_szText, "    ");
              lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
              lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
              sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)&dword_DC373C, 1);
              lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
              v5 = nVal;
            }
          }
          else
          {
            v19 = (gbCamera **)(&this->m_pCamera + 75 * *((unsigned __int8 *)&this[75].m_dist + v5));
            if ( (gbCamera *)v18 == v19[297] || (gbCamera *)v18 == v19[298] || (gbCamera *)v18 == v19[299] )
            {
              m_nBlendTimer = this->m_nBlendTimer;
              (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
              this->m_nBlendTimer = 0;
              lstrcatA((LPSTR)p_m_szText, "    ");
              lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
              lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
              v21 = 1;
              v22 = (gbCamera **)&v28;
              v23 = 2;
              do
              {
                if ( v27 == *v22 )
                  ++v21;
                ++v22;
                --v23;
              }
              while ( v23 );
              sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)&dword_DC373C, v21);
              lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
              break;
            }
          }
          v20 = this->m_nViewMode + 1;
          this->m_nViewMode = v20;
          if ( v20 >= ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount() )
          {
            CCBCamControl_ProcessRenderQueue(v26);
            this->m_bBlendPause = 0;
            goto LABEL_45;
          }
        }
      }
      CCBCamControl_ProcessRenderQueue(v26);
      this->m_bBlendPause = 0;
      goto LABEL_45;
    }
    this->m_nBlendTimer = 0;
    this->m_bBlendActive = 0;
LABEL_44:
    sub_445E50((int)(&this[60].m_nViewBase + 236));
    goto LABEL_45;
  }
  if ( !(unsigned __int8)CameraCtrl_InitBlendState(nVal) )
  {
    this->m_bBlendActive = 0;
    this->m_nBlendTimer = 0;
    goto LABEL_44;
  }
  pConfig = 0xFFFF;
  v34 = 0;
  SkillNum = 0;
  v11 = *(&this->m_nSlotParam + 75 * *((unsigned __int8 *)&this[75].m_dist + nVal));
  v34 = 1;
  pConfig = v11;
  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v11);
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&pConfig);
  lstrcatA((LPSTR)p_m_szText, "    ");
  lstrcatA((LPSTR)p_m_szText, byte_DCD03C);
  lstrcatA((LPSTR)p_m_szText, (LPCSTR)(SkillNum + 4));
  sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)&dword_DC373C, 1);
  lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
  p_DWORD = 0xFFFF;
  m_nBlendTimer = 0;
  v32 = 0;
  this->m_nViewMode = 0;
  if ( ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount() <= 0 )
    goto LABEL_22;
  while ( 1 )
  {
    v12 = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
    v13 = (unsigned long)*v12;
    p_DWORD = (unsigned long)*v12;
    m_nBlendTimer = (unsigned long)v12[1];
    v32 = (unsigned long)v12[2];
    if ( this->m_nBlendTimer <= 0 )
    {
      if ( (gbCamera *)v13 == v27 || (gbCamera *)v13 == v28 || (gbCamera *)v13 == v29 )
      {
        m_nBlendTimer = 1;
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
        this->m_nBlendTimer = 0;
        lstrcatA((LPSTR)p_m_szText, "    ");
        lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
        lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
        sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)&dword_DC373C, 1);
        lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
      }
      goto LABEL_15;
    }
    if ( (gbCamera *)v13 == v27 || (gbCamera *)v13 == v28 || (gbCamera *)v13 == v29 )
      break;
LABEL_15:
    v14 = this->m_nViewMode + 1;
    this->m_nViewMode = v14;
    if ( v14 >= ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount() )
    {
      CCBCamControl_ProcessRenderQueue(v26);
      this->m_bBlendPause = 1;
      goto LABEL_45;
    }
  }
  m_nBlendTimer = this->m_nBlendTimer;
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
  this->m_nBlendTimer = 0;
  lstrcatA((LPSTR)p_m_szText, "    ");
  lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
  lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
  nVala = 1;
  v15 = (gbCamera **)&v28;
  v16 = 2;
  do
  {
    if ( v27 == *v15 )
      ++nVala;
    ++v15;
    --v16;
  }
  while ( v16 );
  sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)&dword_DC373C, nVala);
  lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
LABEL_22:
  CCBCamControl_ProcessRenderQueue(v26);
  this->m_bBlendPause = 1;
LABEL_45:
  v25 = (const void *)off_5C778C;
  Instance = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v25, 1);
  this->m_nBlendWeight = 7;
  this->m_bBlendWeight = 0;
}

// 0x0048EE00
int CameraCtrl::FindNextValidSlot(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  ++*pCounter;
  while ( 1 )
  {
    v2 = (unsigned long)*pCounter;
    if ( *(&this->m_bCamEventFlag + *pCounter) )
    {
      if ( v2 <= 4 )
        break;
    }
    v3 = v2 + 1;
    *pCounter = v3;
    if ( v3 > 4 )
      *pCounter = 0;
  }
  return *pCounter;
}

// 0x0048EE30
int CameraCtrl::FindPrevValidSlot(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  --*pCounter;
  while ( 1 )
  {
    v2 = (unsigned long)*pCounter;
    if ( *(&this->m_bCamEventFlag + *pCounter) )
    {
      if ( v2 >= 0 )
        break;
    }
    v3 = v2 - 1;
    *pCounter = v3;
    if ( v3 < 0 )
      *pCounter = 4;
  }
  return *pCounter;
}

// 0x004BE910
void CameraCtrl::OnIdle()
{
  this->CameraCtrl::_nearby_41cbc0();
}

// 0x004BEAA0
void CameraCtrl::OnIdleB()
{
  this->CameraCtrl::_nearby_41cbc0();
}

// 0x004BEBF0
void CameraCtrl::RenderFadeEffect()
{
  this->CameraCtrl::_nearby_41cbc0();
}

// 0x004BED40
void CameraCtrl::RenderFadeEffectB()
{
  this->CameraCtrl::_nearby_41cbc0();
}

// 0x00504510
char CameraCtrl::InitFromConfig()
{
  this->CameraCtrl::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  (((CIniFile *)this))->CIniFile::LoadStructuredConfig();
  return 1;
}

// 0x00504540
char CameraCtrl::InitFromScreen()
{
  _DWORD pParams[3]; // [esp+0x4] [ebp-0xC] BYREF

  this->CameraCtrl::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  this->m_pTarget = ((InputSystem *)0);
  this->m_fMinDist = 50.0f;
  pParams[0] = 0;
  pParams[1] = -1018691584;
  pParams[2] = 0;
  this->CameraCtrl::InitParams(pParams);
  this->CameraCtrl::SetAsCurrent(3);
  this->m_fCamDist = 10000.0f;
  (((InputSystem *)this))->InputSystem::ProcessKeyboard(0);
  return 1;
}

// 0x0052EBE0
void CameraCtrl::SetViewport(int nFlags)
{
  (((UILoadingFrm *)this))->UILoadingFrm::CheckProgress(nFlags) /* [ROWTABLE] */;
  (((CCBFiveNimbusWindow *)this))->CCBFiveNimbusWindow::UpdateAnimation(nFlags) /* [ROWTABLE] */;
  (((UIGameOver *)this))->UIGameOver::SetupDisplay(nFlags);
  (((UI3DCtrl *)this))->UI3DCtrl::UpdateTransform(nFlags) /* [ROWTABLE] */;
  (((gbCamera *)this->m_pCamera))->gbCamera::SetLookAt((gbVec3D *)&this->m_fMinDist, (gbVec3D *)&this->m_fTargetAngle, (gbVec3D *)&this->m_fAngleDest);
}

// 0x00533EA0
char CameraCtrl::InitDefaultView()
{
  this->CameraCtrl::SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  this->m_pTarget = ((InputSystem *)0);
  this->m_fMinDist = 50.0f;
  this->m_fDefaultPosY = 0.0f;
  this->m_fDefaultPosZ = -200.0f;
  this->m_fDefaultOffset = 0.0f;
  (((RoleAtt *)this))->RoleAtt::UpdatePosition(0.0, -200.0, 0.0) /* [ROWTABLE] */;
  this->m_fViewDistance = 300.0f;
  this->m_fViewPitch = -39.56305694580078f;
  this->m_fViewYaw = 302.5511474609375f;
  this->m_fDefaultPosX = -439.63275146484375f;
  (((RoleAtt *)this))->RoleAtt::InterpolateMotion(-39.563057, 302.55115, -439.63275, 300.0, 0.0) /* [ROWTABLE] */;
  this->m_fCurAngle = 50.0f;
  this->m_nCamState = 1176256512;
  return 1;
}

// 0x00534DC0
int CameraCtrl::SetFOVIfValid(int nVal)
{
  int result; // eax

  result = nVal;
  if ( nVal )
    this->m_pCamera = ((gbCamera *)((gbCamera *)nVal));
  return result;
}
