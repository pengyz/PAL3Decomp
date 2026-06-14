#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Scene/CameraCtrl.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations
int sub_445E50(int a2); // from annotations
void * sub_446010(void *a2); // from annotations

int crt_sub_00541590(void); // from annotations
int RefreshPartyRoleData(void); // from annotations

// Unnamed globals (extern)
extern CHAR asc_5C9190[];
extern char byte_5967B0[3];
extern char byte_A00001;
extern char byte_A00215;
extern char byte_A00217;
extern char byte_A00218;
extern char byte_A00219;
extern char byte_A00220;
extern char byte_A00221;
extern char byte_A00222;
extern char byte_A00223;
extern char byte_A00224;
extern char byte_A00225;
extern char byte_A00226;
extern char byte_A00227;
extern char byte_A00228;
extern char byte_A00229;
extern char byte_A00230;
extern char byte_A00231;
extern char byte_ABC000;
extern char byte_ABC001;
extern CHAR byte_DCD03C[256];
extern CHAR byte_DCD13C[256];
extern int dword_A00234;
extern int dword_C11420;
extern int dword_C11424;
extern int dword_C11428;
extern int dword_C116F0;
extern int dword_C1171C;
extern int dword_D8BBEC;
extern int dword_DC373C;
extern int dword_DC8A3C;
extern int dword_DC8B3C;
extern int dword_DC8C3C;
extern int dword_DC9F3C;
extern int dword_DCA03C;
extern int dword_DCCC3C;
extern int dword_DD213C;
extern int dword_DD273C;
extern const char * off_56C548;
extern void * off_5C7764;
extern void *off_5C7770;
extern void * off_5C7774;
extern void * off_5C778C;
extern int off_5C91C8;
extern RoleSystem stru_C059A0;
extern PalScript stru_C11720;
extern int word_A00232;
extern int word_ABC002;

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
    ((gbCamera *)&this->m_fMinDist)->SetLookAt(&this->m_vecLookAt, (gbVec3D *)&this->m_nAsCurrent, &this->m_vecUpDir);
  ((gbCamera *)&this->m_fMinDist)->SetAsCurrent(flags);
}

// 0x0041C670
float * CameraCtrl::CalcOrbitalPos(
        
        float *pfOut,
        float fTargetX,
        float fTargetY,
        float fTargetZ)
{
  long double v5; // st7
  long double v7; // st7
  double m_fCamDist; // st6
  float v9; // [esp+0x0] [ebp-0x18]
  float v10; // [esp+0x0] [ebp-0x18]
  float v11; // [esp+0x4] [ebp-0x14]
  float v12; // [esp+0x4] [ebp-0x14]
  float v13; // [esp+0x8] [ebp-0x10]
  float v14; // [esp+0xC] [ebp-0xC]
  float v15; // [esp+0x10] [ebp-0x8]

  v5 = cos(this->m_fAngle);
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
  return pfOut;
}

// 0x0041CA90
void CameraCtrl::SetDimention(int w, int h)
{
  this->m_nWidth = w;
  this->m_nHeight = h;
  ((gbCamera *)&this->m_fMinDist)->SetDimention(w, h);
}

// 0x0041CAC0
void * CameraCtrl::GetViewTarget(void *pTarget, float *pPos)
{
  float *p_m_fMinDist; // ecx
  double v4; // st7
  double v5; // st6
  float v7; // [esp+0x8] [ebp-0x20]
  float v8; // [esp+0xC] [ebp-0x1C]
  struct gbRay v9; // [esp+0x10] [ebp-0x18] BYREF

  p_m_fMinDist = &this->m_fMinDist;
  v4 = (double)*(int *)pPos;
  v5 = (double)*((int *)p_m_fMinDist + 117);
  memset(&v9, 0, sizeof(v9));
  v7 = v4 / (v5 * 0.5) - 1.0;
  v8 = 1.0 - (double)*((int *)pPos + 1) / ((double)*((int *)p_m_fMinDist + 118) * 0.5);
  ((gbCamera *)p_m_fMinDist)->GetRayToScreen(v7, v8, &v9);
  qmemcpy(pTarget, &v9, 0x18u);
  return pTarget;
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
    *pResult = (1.0 - fFactor) * fCurrent + fTarget * fFactor;
    return pResult;
  }
  return result;
}

// 0x0041CC50
int CameraCtrl::UpdateTransition(float fDelta)
{
  double v3; // st7
  int result; // eax
  int v5; // edx
  float *v6; // eax
  double v7; // st6
  double m_fLerpPosX; // st7
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
      this->GetLerpPos((float *)this->m_pTarget + 117, this->m_fAngleSrc, this->m_fAngleDest, fFactor);
      ((InputSystem *)this->m_pTarget)->InputSystem::ProcessKeyboard();
      break;
    case 2:
    case 4:
      this->GetLerpPos((float *)this->m_pTarget + 114, this->m_fFOVLerp, this->m_fFOV, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 113, this->m_fParamF, *(float *)&this->m_bCamFlag, fFactor);
      ((InputSystem *)this->m_pTarget)->InputSystem::ProcessKeyboard();
      result = (int)this->m_pTarget;
      *(_DWORD *)(result + 460) = 0;
      break;
    case 3:
      this->GetLerpPos((float *)this->m_pTarget + 123, this->m_fLerpTargetX, this->m_fLerpPosX, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 124, this->m_fLerpTargetY, this->m_fLerpPosY, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 125, this->m_fLerpTargetZ, this->m_fLerpPosZ, fFactor);
      ((InputSystem *)this->m_pTarget)->InputSystem::ProcessKeyboard();
      break;
    case 6:
      this->GetLerpPos((float *)this->m_pTarget + 117, this->m_fAngleSrc, this->m_fAngleDest, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 114, this->m_fFOVLerp, this->m_fFOV, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 113, this->m_fParamF, *(float *)&this->m_bCamFlag, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 123, this->m_fLerpTargetX, this->m_fLerpPosX, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 124, this->m_fLerpTargetY, this->m_fLerpPosY, fFactor);
      this->GetLerpPos((float *)this->m_pTarget + 125, this->m_fLerpTargetZ, this->m_fLerpPosZ, fFactor);
      ((InputSystem *)this->m_pTarget)->InputSystem::ProcessKeyboard();
      *((_DWORD *)this->m_pTarget + 115) = 0;
      break;
    case 7:
      v5 = rand() % 100;
      v6 = (float *)((char *)this->m_pTarget + 492);
      v7 = fDelta * 60.0 + this->m_fFOV;
      this->m_fFOV = v7;
      m_fLerpPosX = this->m_fLerpPosX;
      v11 = ((double)v5 * 0.0099999998 + sin(v7))
          * ((1.0 - this->m_fCurAngle / this->m_fTargetAngle)
           * 0.5)
          * this->m_fAngleDest
          + this->m_fLerpPosY;
      m_fLerpPosZ = this->m_fLerpPosZ;
      v6[1] = v11;
      *v6 = m_fLerpPosX;
      v6[2] = m_fLerpPosZ;
      ((InputSystem *)this->m_pTarget)->InputSystem::ProcessKeyboard();
      break;
    default:
      return result;
  }
  return result;
}

// 0x0041CEE0
int CameraCtrl::SetupFollow(int nVal, int nVal2, int nVal3, int nVal4)
{
  this->m_pTarget = (void *)nVal;
  LODWORD(this->m_fAngleDest) = nVal2;
  this->m_fAngleSrc = *(float *)(nVal + 468);
  this->m_nFlags = 1;
  LODWORD(this->m_fTargetAngle) = nVal3;
  this->m_fCurAngle = 0.0;
  this->m_nCamState = nVal4;
  return nVal4;
}

// 0x0041CF20
int CameraCtrl::SetupOrbit(int nVal, int nVal2, int nVal3, int nVal4, int nVal5)
{
  this->m_pTarget = (void *)nVal;
  LODWORD(this->m_fFOV) = nVal2;
  this->m_fFOVLerp = *(float *)(nVal + 456);
  this->m_bCamFlag = nVal3;
  this->m_fParamF = *(float *)(nVal + 452);
  this->m_nFlags = 2;
  LODWORD(this->m_fTargetAngle) = nVal4;
  this->m_fCurAngle = 0.0;
  this->m_nCamState = nVal5;
  return nVal5;
}

// 0x0041CF70
int CameraCtrl::SetupTrack(int nVal, int nVal2, int nVal3, int nVal4, int nVal5)
{
  this->m_pTarget = (void *)nVal;
  LODWORD(this->m_fFOV) = nVal2;
  this->m_fFOVLerp = *(float *)(nVal + 456);
  this->m_bCamFlag = nVal3;
  this->m_fParamF = *(float *)(nVal + 452);
  this->m_nFlags = 4;
  LODWORD(this->m_fTargetAngle) = nVal4;
  this->m_fCurAngle = 0.0;
  this->m_nCamState = nVal5;
  return nVal5;
}

// 0x0041CFC0
int CameraCtrl::SetupDirect(int *p_DWORD, int nVal, int nVal2)
{
  this->m_pTarget = p_DWORD;
  LODWORD(this->m_fLerpPosX) = p_DWORD[123];
  LODWORD(this->m_fLerpPosY) = p_DWORD[124];
  LODWORD(this->m_fLerpPosZ) = p_DWORD[125];
  LODWORD(this->m_fAngleDest) = nVal2;
  LODWORD(this->m_fTargetAngle) = nVal;
  this->m_nFlags = 7;
  this->m_fCurAngle = 0.0;
  this->m_fFOV = 0.0;
  return 0;
}

// 0x0041D010
int CameraCtrl::SetupLerp(int nVal, int *p_DWORD, int nVal2, int nVal3)
{
  float *v5; // eax

  this->m_pTarget = (void *)nVal;
  LODWORD(this->m_fLerpPosX) = *p_DWORD;
  LODWORD(this->m_fLerpPosY) = p_DWORD[1];
  LODWORD(this->m_fLerpPosZ) = p_DWORD[2];
  v5 = (float *)((char *)this->m_pTarget + 492);
  this->m_fLerpTargetX = *v5;
  this->m_fLerpTargetY = v5[1];
  this->m_fLerpTargetZ = v5[2];
  this->m_nFlags = 3;
  LODWORD(this->m_fTargetAngle) = nVal2;
  this->m_fCurAngle = 0.0;
  this->m_nCamState = nVal3;
  return nVal3;
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
  float *m_pTarget; // eax
  int result; // eax

  this->m_pTarget = (void *)nVal;
  this->m_nFlags = 6;
  LODWORD(this->m_fTargetAngle) = nVal5;
  this->m_fCurAngle = 0.0;
  this->m_nCamState = 1;
  LODWORD(this->m_fLerpPosX) = *p_DWORD;
  LODWORD(this->m_fLerpPosY) = p_DWORD[1];
  LODWORD(this->m_fLerpPosZ) = p_DWORD[2];
  v7 = (float *)((char *)this->m_pTarget + 492);
  this->m_fLerpTargetX = *v7;
  this->m_fLerpTargetY = v7[1];
  this->m_fLerpTargetZ = v7[2];
  m_pTarget = (float *)this->m_pTarget;
  LODWORD(this->m_fFOV) = nVal2;
  this->m_fFOVLerp = m_pTarget[114];
  this->m_bCamFlag = nVal3;
  this->m_fParamF = m_pTarget[113];
  LODWORD(this->m_fAngleDest) = nVal4;
  result = *((_DWORD *)m_pTarget + 117);
  LODWORD(this->m_fAngleSrc) = result;
  return result;
}

// 0x0041D5B0
int CameraCtrl::SetCamMode(int mode)
{
  LODWORD(this->m_mode) = mode;
  return mode;
}

// 0x0041D5C0
int CameraCtrl::SetCamDist(int nVal)
{
  LODWORD(this->m_fCamDist) = nVal;
  return nVal;
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
  int v8; // ecx
  float m_fAngleSrc; // eax
  _DWORD *v10; // eax
  float *v11; // esi
  int v12; // ecx
  int v13; // ebp
  size_t v14; // eax
  char *v15; // eax
  float m_fTargetAngle; // ecx
  char *v17; // edi
  int v18; // eax
  char *v19; // edx
  int v20; // ebp
  float *p_m_fMinDist; // ebp
  float *p_m_fCurAngle; // esi
  int v23; // edx
  int v24; // ecx
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
      v15 = (char *)operator new(v14);
      m_fTargetAngle = this->m_fTargetAngle;
      v26 = *(float *)&v15;
      v17 = &v15[4 * ((unsigned int)(2 * v13) >> 2)];
      v18 = LODWORD(this->m_fAngleSrc) + 4;
      v19 = v17;
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
      result = &v17[4 * v13];
      *(_DWORD *)result = v2;
      m_nFlags = this->m_nFlags;
      p_m_fMinDist = &this->m_fMinDist;
      p_m_fCurAngle = &this->m_fCurAngle;
      v23 = *(_DWORD *)v17 + 4088;
      *p_m_fMinDist = *(float *)v17;
      *((_DWORD *)p_m_fMinDist + 1) = v23;
      *((_DWORD *)p_m_fMinDist + 2) = m_nFlags;
      *((_DWORD *)p_m_fMinDist + 3) = v17;
      v24 = *(_DWORD *)result;
      *p_m_fCurAngle = *(float *)result;
      *((_DWORD *)p_m_fCurAngle + 1) = v24 + 4088;
      *((_DWORD *)p_m_fCurAngle + 2) = v2;
      *((_DWORD *)p_m_fCurAngle + 3) = result;
    }
    else
    {
      v10 = (_DWORD *)(LODWORD(m_fAngleSrc) + 4);
      LODWORD(this->m_fAngleSrc) = v10;
      v11 = &this->m_fCurAngle;
      *v10 = v2;
      result = (char *)*((_DWORD *)v11 + 3);
      v12 = *(_DWORD *)result;
      *v11 = *(float *)result;
      *((_DWORD *)v11 + 1) = v12 + 4088;
      *((_DWORD *)v11 + 2) = v2;
      *((_DWORD *)v11 + 3) = result;
    }
  }
  else
  {
    LODWORD(this->m_fFOVLerp) = 2;
    v3 = operator new(8u);
    LODWORD(this->m_fFOV) = v3;
    v3[1] = v2;
    v4 = v2 + 2044;
    result = (char *)(LODWORD(this->m_fFOV) + 4);
    v6 = &this->m_fMinDist;
    v7 = &this->m_fCurAngle;
    v8 = *(_DWORD *)result;
    *v7 = *(float *)result;
    *(_DWORD *)v6 = v8;
    *((_DWORD *)v7 + 1) = v8 + 4088;
    *((_DWORD *)v6 + 1) = v8 + 4088;
    *((_DWORD *)v7 + 2) = v4;
    *((_DWORD *)v6 + 2) = v4;
    *((_DWORD *)v7 + 3) = result;
    *((_DWORD *)v6 + 3) = result;
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
    p_m_fCurAngle = &this->m_fCurAngle;
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
    this->m_fMinDist = 0.0;
    this->m_pTarget = 0;
    this->m_nFlags = 0;
    this->m_fTargetAngle = 0.0;
    this->m_fCurAngle = 0.0;
    this->m_nCamState = 0;
    m_fFOV = this->m_fFOV;
    this->m_fAngleDest = 0.0;
    this->m_fAngleSrc = 0.0;
    operator delete((void *)LODWORD(m_fFOV));
  }
}

// 0x0041D7C0
int * CameraCtrl::SetCameraSource(int nVal, int *p_DWORD)
{
  float v4; // edx

  this->m_pCamera = (gbCamera *)*p_DWORD;
  LODWORD(v4) = *p_DWORD + 4088;
  this->m_nFlags = (int)p_DWORD;
  this->m_fMinDist = v4;
  this->m_pTarget = (void *)nVal;
  return (int *)this;
}

// 0x0041D7F0
unsigned int CameraCtrl::SetupCameraArray(int a2)
{
  int v2; // edi
  unsigned int result; // eax
  gbCamera **v4; // ebx
  gbCamera *v5; // edx
  unsigned int v6; // edi

  v2 = ((char *)this->m_pTarget + 28 * a2 - (char *)this->m_pCamera) / 28;
  if ( v2 < 0 )
    result = -((145 - v2) / 0x92u);
  else
    result = v2 / 0x92u;
  if ( result )
  {
    v4 = (gbCamera **)(4 * result + this->m_nFlags);
    this->m_nFlags = (int)v4;
    v5 = *v4;
    this->m_pCamera = *v4;
    LODWORD(this->m_fMinDist) = (unsigned long)&v5[10].pControl[13];
    v6 = v2 - 146 * result;
    result = (unsigned int)this->m_pCamera;
    this->m_pTarget = (char *)this->m_pCamera + 28 * v6;
  }
  else
  {
    this->m_pTarget = (char *)this->m_pTarget + 28 * a2;
  }
  return result;
}

// 0x0041D960
void CameraCtrl::ResetSceneMgrParams()
{
  dword_C11420 = 0;
  dword_C11424 = 0;
  dword_C11428 = 0;
}

// 0x0041D9A0
void CameraCtrl::UpdateInternal(float fDelta)
{
  CScreenMode *v2; // ecx
  double v3; // st7
  double v4; // st7
  float *p_m_fMinDist; // eax
  double v6; // st7
  CScreenMode *SoundList; // eax
  CScreenMode *v8; // ecx
  CScreenMode *v9; // eax
  Camera *v10; // ecx
  int v11; // eax
  RoleSystem *v12; // esi
  GRP_KEYREG *KeyInfo; // eax
  int v14; // edx
  int v15; // ebp
  LONG v16; // ebx
  int Target; // eax
  int v18; // edi
  float *v19; // eax
  int v20; // esi
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  double v25; // st7
  char v26; // al
  bool v27; // cl
  int PressTime; // ecx
  int v29; // eax
  int v30; // esi
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // esi
  UICamera *v36; // ecx
  int State; // eax
  int ViewMode; // eax
  float v39; // edx
  float v40; // eax
  float v41; // eax
  float v42; // eax
  double v43; // st7
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
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( g_nRoleSystem_58B234 && dword_D8BBEC != 1 )
  {
    v46 = *(_DWORD *)&g_Input.MouseState[8];
    if ( *(_DWORD *)&g_Input.MouseState[8] )
    {
      v3 = (double)v46 * 0.0013962634;
      pDist = v3;
      if ( v3 <= 1.5700001 )
      {
        if ( pDist < -1.5700001 )
          pDist = -1.5700001;
        ((CameraCtrl *)&g_pCameraCtrl)->SetCamMode(SLODWORD(pDist));
      }
      else
      {
        pDist = 1.5700001;
        ((CameraCtrl *)&g_pCameraCtrl)->SetCamMode(1070134723);
      }
    }
    else
    {
      v2 = (CScreenMode *)(g_Input.KeyInfo[13].Data & 0xF);
      if ( (_BYTE)v2 == 1 )
      {
        ((CameraCtrl *)&g_pCameraCtrl)->SetCamMode(1034147594);
      }
      else if ( (g_Input.KeyInfo[14].Data & 0xF) == 1 )
      {
        ((CameraCtrl *)&g_pCameraCtrl)->SetCamMode(-1113336054);
      }
    }
  }
  if ( dword_C116F0 )
  {
    v4 = 0.0;
    if ( (g_Input.KeyInfo[4].Data & 0xF) == 1 )
    {
      v4 = 1.0;
    }
    else if ( (g_Input.KeyInfo[5].Data & 0xF) == 1 )
    {
      v4 = -1.0;
    }
    if ( (g_Input.KeyInfo[38].Data & 0xF) == 1 )
    {
      p_m_fMinDist = &g_pCameraCtrl->m_fMinDist;
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
  SoundList = (CScreenMode *)((CScreenMode *)v2)->GetSoundList();
  ((CScreenMode *)SoundList)->SetAudioParam();
  v9 = (CScreenMode *)((CScreenMode *)v8)->GetSoundList();
  if ( ((CScreenMode *)v9)->IsAudioReady() && !g_bFormationReady )
  {
    if ( g_nSceneState == 2 && dword_D8BBEC == 2 && g_Input.KeyInfo[12].PressTime == 1 )
    {
      v10 = (Camera *)(g_Input.KeyInfo[12].Data & 0xF);
      if ( (_BYTE)v10 == 1
        && !(*(int ( **)(int *))(g_pRoleSystem->m_bvisible + 4))(&g_pRoleSystem->m_bvisible) )
      {
        v11 = g_nCurrentRoleSlot + 1;
        if ( g_nCurrentRoleSlot + 1 > 4 )
          v11 = 0;
        if ( !*((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v11) )
        {
          do
          {
            if ( ++v11 > 4 )
              v11 = 0;
          }
          while ( v11 != g_nCurrentRoleSlot && !*((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v11) );
        }
        ((scAsmDecoder *)g_nCurrentRoleSlot)->Execute(v11, 1);
      }
    }
    v12 = g_pRoleSystem;
    if ( g_pRoleSystem->m_FrameA.m_rect.right != 4 )
      goto LABEL_51;
    if ( LODWORD(g_pRoleSystem->m_fRotAxisZ) == 44 )
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
      ((RoleSystem *)&g_pRoleSystem)->Notify();
      v12 = g_pRoleSystem;
    }
LABEL_50:
    if ( v12->m_FrameA.m_rect.right != 4 )
    {
LABEL_51:
      LOBYTE(v46) = 0;
      if ( dword_D8BBEC == 2 )
        LOBYTE(v46) = ((Camera *)v10)->IsTransitioning();
      ((PalScript *)&g_UIScript)->ShowWindow((unsigned __int8)v46);
      if ( (_BYTE)v46 )
      {
        memset(pOut, 0, 12);
        ((RoleSystem *)&g_pRoleSystem)->GetDirection(&pOut[0].x);
        pOut[0].y = pOut[0].y + 10.0;
        ((gbCamera *)&g_pCameraCtrl->m_fMinDist)->PointWorldToScr(pOut, &v48, &pOut2);
        sub_445D20(
          (__int64)((v48 + 1.0) * (double)g_DrvInfo.width * 0.5),
          (__int64)((1.0 - pOut2) * (double)g_DrvInfo.height * 0.5));
      }
      v15 = 0;
      v16 = 0;
      pDist = 0.0;
      qmemcpy(pMat, ((CameraCtrl *)&g_pCameraCtrl)->GetViewTarget(pOut, (float *)&pPos.x), sizeof(pMat));
      if ( g_nSceneState != 2 && g_nSceneState != 8 )
        goto LABEL_107;
      Target = ((UICamera *)pMat)->GetTarget();
      v18 = Target;
      if ( Target && *(_DWORD *)(Target + 1264) == 7 )
        v18 = 0;
      UISceneUpdate();
      v19 = ((UICamera *)pMat)->CalcPosition();
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
          ((RoleSystem *)&g_pRoleSystem)->UpdateAnimation((float *)v18);
          v15 = 1;
        }
        else
        {
          ((RoleSystem *)&g_pRoleSystem)->GetActiveRole();
        }
        if ( v20 )
        {
          ((RoleSystem *)&g_pRoleSystem)->SetState(v20);
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
        if ( !((Camera *)&pPos.x)->CheckCollision1(&dword_C11420, &pDist)
          && !((Camera *)&pPos.x)->CheckCollision2(*(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture, &dword_C11420) )
        {
          goto LABEL_153;
        }
        LODWORD(pfVal.x) = dword_C11420;
        LODWORD(pfVal.z) = dword_C11428;
        pfVal.y = 0.0;
        v30 = 0;
        ((GRPinput *)&g_Input)->GetMousePos(&v48, &pOut2);
        if ( v48 != 0.0 || pOut2 != 0.0 )
          v30 = 1;
        g_pRoleSystem->_embed_UIWnd_624.m_rect.bottom = 0;
        if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
        {
          ((RoleSystem *)&g_pRoleSystem)->UpdateRole(&pfVal.x, SLODWORD(pDist), 1);
          v31 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
          if ( LODWORD(pDist) != v31
            && !g_pRoleSystem->m_FrameA.m_rect.bottom
            && ((Camera *)&pPos.x)->CheckCollision2(v31, &pfVal) )
          {
            pfVal.y = 0.0;
            ((RoleSystem *)&g_pRoleSystem)->UpdateRole(&pfVal.x, *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture, 1);
          }
        }
        else if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 && (double)g_Input.KeyInfo[0].PressTime * fDelta > 0.5 )
        {
          ((RoleSystem *)&g_pRoleSystem)->MoveRole(&pfVal.x, SLODWORD(pDist), 1, v30);
          v32 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
          if ( LODWORD(pDist) != v32
            && !g_pRoleSystem->m_FrameA.m_rect.bottom
            && ((Camera *)&pPos.x)->CheckCollision2(v32, &pfVal) )
          {
            pfVal.y = 0.0;
            ((RoleSystem *)&g_pRoleSystem)->MoveRole(&pfVal.x, *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture, 1, 1);
          }
        }
        else if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 )
        {
          ((RoleSystem *)&g_pRoleSystem)->UpdateRole(&pfVal.x, SLODWORD(pDist), 2);
          v33 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
          if ( LODWORD(pDist) != v33
            && !g_pRoleSystem->m_FrameA.m_rect.bottom
            && ((Camera *)&pPos.x)->CheckCollision2(v33, &pfVal) )
          {
            pfVal.y = 0.0;
            ((RoleSystem *)&g_pRoleSystem)->UpdateRole(&pfVal.x, *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture, 2);
          }
        }
        else
        {
          if ( (g_Input.KeyInfo[0].Data & 0xFu) <= 1 || (double)g_Input.KeyInfo[0].PressTime * fDelta <= 0.5 )
          {
LABEL_145:
            if ( (m_bPathEnabled || (_BYTE)v46 && dword_D8BBEC == 2)
              && g_Input.KeyInfo[1].PressTime == 1
              && (g_Input.KeyInfo[1].Data & 0xF) == 1
              && *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture == LODWORD(pDist) )
            {
              ((RoleSystem *)&g_pRoleSystem)->PathFind(&pfVal.x);
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
                  State = ((UICamera *)v36)->GetState();
                  if ( State && *(_DWORD *)(State + 1264) != 7 )
                  {
                    if ( *(_BYTE *)(State + 173) != 2 && *(_DWORD *)(State + 264) )
                      ((RoleSystem *)&g_pRoleSystem)->UpdateAnimation((float *)State);
                  }
                  else
                  {
                    UISceneUpdate();
                    ViewMode = ((UICamera *)v44)->GetViewMode();
                    if ( ViewMode )
                      ((RoleSystem *)&g_pRoleSystem)->SetState(ViewMode);
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
                  ((gbVec3D *)pOut)->Normalize();
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
                    ((gbVec3D *)pOut)->Normalize();
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
                      if ( g_pRoleSystem->m_FrameA.m_rect.right == 3 )
                      {
                        memset(pOut, 0, 12);
                        ((RoleSystem *)&g_pRoleSystem)->GetPosition(pOut[0].x,   0);
                      }
                      v43 = g_fCameraBlendWeight + fDelta;
                      g_fCameraBlendWeight = v43;
                      if ( v43 > g_fCameraDefaultDist )
                      {
                        g_fCameraBlendWeight = 0.0;
                        ((RoleSystem *)&g_pRoleSystem)->GetCount();
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
                    ((gbVec3D *)pOut)->Normalize();
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
                  ((gbVec3D *)pOut)->Normalize();
                  v35 = 2;
                  v16 = 3;
                  pfVal.x = pOut[0].x + pfVal.x;
                  pfVal.y = pfVal.y + pOut[0].y;
                  pfVal.z = pfVal.z + pOut[0].z;
                }
                ((RoleSystem *)&g_pRoleSystem)->GetActiveRole();
                if ( g_pRoleSystem->m_FrameA.m_childs.m_nSize == 2 )
                  v35 = 2;
                ((RoleSystem *)&g_pRoleSystem)->GetPosition(pfVal.x,   v35);
LABEL_166:
                g_pRoleSystem->m_FrameA.m_rect.right = v16;
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
          ((RoleSystem *)&g_pRoleSystem)->MoveRole(&pfVal.x, SLODWORD(pDist), 2, v30);
          v34 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
          if ( LODWORD(pDist) != v34
            && !g_pRoleSystem->m_FrameA.m_rect.bottom
            && ((Camera *)&pPos.x)->CheckCollision2(v34, &pfVal) )
          {
            pfVal.y = 0.0;
            ((RoleSystem *)&g_pRoleSystem)->MoveRole(&pfVal.x, *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture, 2, 1);
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
        v48 = ((gbVec3D *)&pfVal)->Length();
        pOut[0].x = g_pRoleSystem->m_fPosX - *(float *)(v18 + 160);
        v23 = g_pRoleSystem->m_fPosY - *(float *)(v18 + 164);
        pfVal.x = pOut[0].x;
        pOut[0].y = v23;
        v24 = g_pRoleSystem->m_fPosZ - *(float *)(v18 + 168);
        pfVal.y = pOut[0].y;
        pOut[0].z = v24;
        pfVal.z = pOut[0].z;
        v25 = ((gbVec3D *)&pfVal)->Length();
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
        if ( v26 != 14 || *(unsigned __int8 *)(v20 + 246) == *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture )
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
  int *p_capacity; // esi
  float pOut[3]; // [esp+0x0] [ebp-0xC] BYREF

  if ( nVal )
    v1 = g_nCameraUpdateCount + 1;
  else
    v1 = g_nCameraUpdateCount - 1;
  g_nCameraUpdateCount = v1;
  if ( v1 > 0 )
  {
    p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
    do
    {
      ((RoleSystem *)p_capacity)->GetActiveRole();
      p_capacity += 2176;
    }
    while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
    g_fCameraBlendWeight = 0.0;
  }
  else
  {
    UIQuadManager::GetInstance();
    crt_sub_00541590();
    ((PAL3 *)v2)->UIPostProcess();
    if ( g_pRoleSystem->m_FrameA.m_rect.right == 3 )
    {
      memset(pOut, 0, sizeof(pOut));
      ((RoleSystem *)&g_pRoleSystem)->GetPosition(pOut,   0);
      g_pRoleSystem->m_FrameA.m_rect.right = 2;
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
  LOBYTE(((PalScript *)&stru_C11720)->_todo_028) = 0;
  dword_C1171C = 0x7FFFFFFF;
  strcpy((char *)&stru_C11720, &dir[32]);
  ((PalScript *)&stru_C11720)->m_bEnabled = 1;
  ((PalScript *)&stru_C11720)->_todo_44 = -1;
  *(_DWORD *)&((PalScript *)&stru_C11720)->_todo_024 = 0;
  ((PalScript *)&stru_C11720)->_todo_034 = 0;
  LOBYTE(((PalScript *)&stru_C11720)->_todo_48) = 0;
  BYTE2(((PalScript *)&stru_C11720)->_todo_48) = 1;
  return 1;
}

// 0x00487480
int CameraCtrl::ResetToDefaults()
{
  memset(g_SaveSlotFlags, 0, sizeof(g_SaveSlotFlags));
  *(&this->m_nBlendTimer + 1) = -1;
  this->m_nBlendState = -1;
  this->m_nSlotParam = 6202;
  this->m_nBlendWeightA = 6201;
  this->m_nBlendWeightB = 6201;
  this->m_nBlendWeightC = 0;
  *((_DWORD *)&this->m_roleParams + 5) = -1;
  *((_DWORD *)&this->m_roleParams + 6) = -1;
  *((_DWORD *)&this->m_roleParams + 7) = 6204;
  *(&this->m_nViewState + 56) = 6203;
  *(&this->m_nViewState + 57) = 6203;
  *(&this->m_nViewState + 58) = 0;
  *(&this->m_nViewState + 64) = -1;
  *(&this->m_nViewState + 65) = -1;
  *(&this->m_nViewState + 66) = 6210;
  *(&this->m_nViewState + 131) = 6204;
  *((_DWORD *)&this->_todo_7FC + 11) = 6205;
  *((_DWORD *)&this->_todo_7FC + 12) = 6205;
  *((_DWORD *)&this->_todo_7FC + 163) = 6224;
  *((_DWORD *)&this->_todo_7FC + 171) = 6224;
  *(&this->m_nViewState + 141) = 6206;
  *((_DWORD *)&this->_todo_7FC + 311) = 6206;
  *((_DWORD *)&this->_todo_7FC + 312) = 6206;
  *((_DWORD *)&this->_todo_7FC + 313) = 6206;
  *(&this->m_nViewState + 132) = 6208;
  *(&this->m_nViewState + 133) = 0;
  *(&this->m_nViewState + 139) = -1;
  *(&this->m_nViewState + 140) = -1;
  *((_DWORD *)&this->_todo_7FC + 13) = 0;
  *((_DWORD *)&this->_todo_7FC + 19) = -1;
  *((_DWORD *)&this->_todo_7FC + 20) = -1;
  *((_DWORD *)&this->_todo_7FC + 21) = 6223;
  *((_DWORD *)&this->_todo_7FC + 86) = 6214;
  *((_DWORD *)&this->_todo_7FC + 87) = 6215;
  *((_DWORD *)&this->_todo_7FC + 88) = 0;
  *((_DWORD *)&this->_todo_7FC + 94) = -1;
  *((_DWORD *)&this->_todo_7FC + 95) = -1;
  *((_DWORD *)&this->_todo_7FC + 96) = 6230;
  *((_DWORD *)&this->_todo_7FC + 161) = 6216;
  *((_DWORD *)&this->_todo_7FC + 162) = 6219;
  *((_DWORD *)&this->_todo_7FC + 169) = -1;
  *((_DWORD *)&this->_todo_7FC + 170) = -1;
  *((_DWORD *)&this->_todo_7FC + 236) = 6217;
  *((_DWORD *)&this->_todo_7FC + 237) = 6218;
  *((_DWORD *)&this->_todo_7FC + 238) = 0;
  *((_DWORD *)&this->_todo_7FC + 244) = -1;
  *((_DWORD *)&this->_todo_7FC + 245) = -1;
  *((_DWORD *)&this->_todo_7FC + 246) = 6208;
  return -1;
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
  p_m_roleParams = &this->m_roleParams;
  do
  {
    v3 = p_m_roleParams;
    v4 = 5;
    do
    {
      v5 = *result++;
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
  CameraCtrl *v20; // ebx
  CameraCtrl *v21; // edx
  float zFar; // ebp
  gbCamera *v23; // ebp
  gbCamera *v24; // edx
  gbCamera *v25; // eax
  int v26; // edi
  int v27; // edx
  int v28; // ecx
  CameraCtrl *v29; // ebx
  CameraCtrl *v30; // ecx
  gbCamera *v31; // ebp
  gbCamera *v32; // edx
  gbCamera *v33; // eax
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
  CameraCtrl *v46; // ebx
  CameraCtrl *v47; // ecx
  gbCamera *v48; // ebp
  gbCamera *v49; // edx
  gbCamera *v50; // eax
  int v51; // edi
  int v52; // edx
  int v53; // ecx
  CameraCtrl *v54; // ebx
  CameraCtrl *v55; // ecx
  gbCamera *v56; // ebp
  gbCamera *v57; // edx
  gbCamera *v58; // eax
  int v59; // edi
  int v60; // edx
  int v61; // ecx
  CameraCtrl *v62; // ebx
  CameraCtrl *v63; // ecx
  int result; // eax
  float v65; // [esp+0x14] [ebp-0x14]
  float Wscreen; // [esp+0x18] [ebp-0x10]
  float v67; // [esp+0x20] [ebp-0x8]
  float v68; // [esp+0x20] [ebp-0x8]
  float v69; // [esp+0x20] [ebp-0x8]
  float v70; // [esp+0x20] [ebp-0x8]
  float v71; // [esp+0x20] [ebp-0x8]
  float v72; // [esp+0x20] [ebp-0x8]

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
      v7 = v6[2];
      if ( LOBYTE(v7->OrthoSize) )
      {
        zNear = v7->zNear;
        v65 = zNear;
        if ( zNear == 0.0
          || LODWORD(v7->zFar) == 1
          || LODWORD(v7->Wscreen) == 1
          || LODWORD(v7->Hscreen) == 1
          || v7->Viewport.x == 1 )
        {
          zFar = v7->zFar;
          if ( zFar == 0.0
            || LODWORD(zNear) == 1
            || LODWORD(v7->Wscreen) == 1
            || LODWORD(v7->Hscreen) == 1
            || v7->Viewport.x == 1 )
          {
            Wscreen = v7->Wscreen;
            if ( Wscreen == 0.0
              || LODWORD(zNear) == 1
              || LODWORD(zFar) == 1
              || LODWORD(v7->Hscreen) == 1
              || v7->Viewport.x == 1 )
            {
              Hscreen = v7->Hscreen;
              if ( Hscreen == 0.0 )
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
                  v56 = *v6;
                  v57 = v6[1];
                  v58 = v6[2];
                  v72 = *(float *)&v57;
                  if ( *((_BYTE *)&v58[1].ViewMatrix.tx + m_nViewMode) )
                  {
                    v59 = 0;
                    v60 = 9536 * m_nViewMode;
                    v61 = *((_DWORD *)this + 2384 * m_nViewMode + 2626);
                    if ( v61 <= 0 )
                    {
LABEL_75:
                      v63 = (CameraCtrl *)((char *)this + 12 * v61 + v60 + 10508);
                      v63->m_pCamera = v56;
                      v63->m_fMinDist = v72;
                      v63->m_pTarget = v58;
                      ++*((_DWORD *)this + 2384 * this->m_nViewMode + 2626);
                    }
                    else
                    {
                      v62 = (CameraCtrl *)((char *)this + v60 + 10508);
                      while ( v56 != v62->m_pCamera )
                      {
                        ++v59;
                        v62 = (CameraCtrl *)((char *)v62 + 12);
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
                  v48 = *v6;
                  v49 = v6[1];
                  v50 = v6[2];
                  v71 = *(float *)&v49;
                  if ( !*((_BYTE *)&v50[1].ViewMatrix.tx + m_nViewMode) )
                    goto LABEL_76;
                  v51 = 0;
                  v52 = 9536 * m_nViewMode;
                  v53 = *((_DWORD *)this + 2384 * m_nViewMode + 2328);
                  if ( v53 > 0 )
                  {
                    v54 = (CameraCtrl *)((char *)this + v52 + 9316);
                    while ( v48 != v54->m_pCamera )
                    {
                      ++v51;
                      v54 = (CameraCtrl *)((char *)v54 + 12);
                      if ( v51 >= v53 )
                        goto LABEL_69;
                    }
                    goto LABEL_76;
                  }
LABEL_69:
                  v55 = (CameraCtrl *)((char *)this + 12 * v53 + v52 + 9316);
                  v55->m_pCamera = v48;
                  v55->m_fMinDist = v71;
                  v55->m_pTarget = v50;
                  ++*((_DWORD *)this + 2384 * this->m_nViewMode + 2328);
                  ++this->m_nViewFlags;
                }
              }
              else
              {
                v40 = *v6;
                v41 = v6[1];
                v42 = v6[2];
                v70 = *(float *)&v41;
                if ( !*((_BYTE *)&v42[1].ViewMatrix.tx + m_nViewMode) )
                  goto LABEL_76;
                v43 = 0;
                v44 = 9536 * m_nViewMode;
                v45 = *((_DWORD *)this + 2384 * m_nViewMode + 1434);
                if ( v45 > 0 )
                {
                  v46 = (CameraCtrl *)((char *)this + v44 + 5740);
                  while ( v40 != v46->m_pCamera )
                  {
                    ++v43;
                    v46 = (CameraCtrl *)((char *)v46 + 12);
                    if ( v43 >= v45 )
                      goto LABEL_57;
                  }
                  goto LABEL_76;
                }
LABEL_57:
                v47 = (CameraCtrl *)((char *)this + 12 * v45 + v44 + 5740);
                v47->m_pCamera = v40;
                v47->m_fMinDist = v70;
                v47->m_pTarget = v42;
                ++*((_DWORD *)this + 2384 * this->m_nViewMode + 1434);
                ++this->m_nViewFlags;
              }
            }
            else
            {
              v31 = *v6;
              v32 = v6[1];
              v33 = v6[2];
              v69 = *(float *)&v32;
              if ( !*((_BYTE *)&v33[1].ViewMatrix.tx + m_nViewMode) )
                goto LABEL_76;
              v34 = 0;
              v35 = 9536 * m_nViewMode;
              v36 = *((_DWORD *)this + 2384 * m_nViewMode + 1136);
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
              ++*((_DWORD *)this + 2384 * this->m_nViewMode + 1136);
              ++this->m_nViewFlags;
            }
          }
          else
          {
            v23 = *v6;
            v24 = v6[1];
            v25 = v6[2];
            v68 = *(float *)&v24;
            if ( !*((_BYTE *)&v25[1].ViewMatrix.tx + m_nViewMode) )
              goto LABEL_76;
            v26 = 0;
            v27 = 9536 * m_nViewMode;
            v28 = *((_DWORD *)this + 2384 * m_nViewMode + 1732);
            if ( v28 > 0 )
            {
              v29 = (CameraCtrl *)((char *)this + v27 + 6932);
              while ( v23 != v29->m_pCamera )
              {
                ++v26;
                v29 = (CameraCtrl *)((char *)v29 + 12);
                if ( v26 >= v28 )
                  goto LABEL_35;
              }
              goto LABEL_76;
            }
LABEL_35:
            v30 = (CameraCtrl *)((char *)this + 12 * v28 + v27 + 6932);
            v30->m_pCamera = v23;
            v30->m_fMinDist = v68;
            v30->m_pTarget = v25;
            ++*((_DWORD *)this + 2384 * this->m_nViewMode + 1732);
            ++this->m_nViewFlags;
          }
        }
        else
        {
          v14 = *v6;
          v15 = v6[1];
          v16 = v6[2];
          v67 = *(float *)&v15;
          if ( !*((_BYTE *)&v16[1].ViewMatrix.tx + m_nViewMode) )
            goto LABEL_76;
          v17 = 0;
          v18 = 9536 * m_nViewMode;
          v19 = *((_DWORD *)this + 2384 * m_nViewMode + 2030);
          if ( v19 > 0 )
          {
            v20 = (CameraCtrl *)((char *)this + v18 + 8124);
            while ( v14 != v20->m_pCamera )
            {
              ++v17;
              v20 = (CameraCtrl *)((char *)v20 + 12);
              if ( v17 >= v19 )
                goto LABEL_24;
            }
            goto LABEL_76;
          }
LABEL_24:
          v21 = (CameraCtrl *)((char *)this + 12 * v19 + v18 + 8124);
          v21->m_pCamera = v14;
          v21->m_fMinDist = v67;
          v21->m_pTarget = v16;
          ++*((_DWORD *)this + 2384 * this->m_nViewMode + 2030);
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
      v3 += Buffer.m_partyActor.m_dwMatMsg[352 * v6 + 9 + v4]
          - *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * v6 + 39 + 4 * v4];
    ++v4;
    ++v5;
  }
  while ( v4 < 12 );
}

// 0x0048C610
BOOL CameraCtrl::HandleCameraEvent(int nParam, BOOL bFlag)
{
  int v4; // ebp
  int v5; // eax
  BOOL result; // eax
  int v7; // ebx
  int v8; // esi
  char v9; // al
  CScreenMode *Instance; // eax
  _BYTE *p_m_bCamEventFlag; // eax
  unsigned __int8 *p_m_bActionActive; // edx
  int v13; // ecx
  _WORD *v14; // eax
  __int16 *v15; // esi
  int v16; // ecx
  char v17; // al
  LONG v18; // ebp
  _BYTE *v19; // edx
  unsigned int *v20; // ecx
  int v21; // esi
  int v22; // eax
  const void *v23; // [esp-0x8] [ebp-0x38]
  char v24; // [esp+0x13] [ebp-0x1D]
  int v25; // [esp+0x14] [ebp-0x1C]
  _BYTE *v26; // [esp+0x18] [ebp-0x18]
  int nParama; // [esp+0x34] [ebp+0x4]
  char v28; // [esp+0x3C] [ebp+0xC]

  v4 = 0;
  v24 = 1;
  v5 = *((_DWORD *)this + 51446);
  this->m_bHandleEvent = 1;
  result = (BOOL)(&this->m_CamBlocks + 2384 * v5 + 298 * bFlag + 3 * nParam + 1);
  v25 = result;
  if ( !*(_DWORD *)(result + 8) )
    goto LABEL_56;
  if ( v28 )
  {
    v7 = 0;
    v8 = 0;
    while ( 1 )
    {
      if ( *(&this->m_bCamEventFlag + v8) )
      {
        this->CalcStatPower(result);
        if ( v9 )
          ++v7;
      }
      if ( ++v8 >= 5 )
        break;
      result = v25;
    }
    if ( v7 <= 0 )
    {
      sprintf(this->m_szCamPath, "\\n        %s", (const char *)dword_DC9F3C);
      ((UICaption *)((char *)this + 207612))->SetEnable((int)this->m_szCamPath, 0);
      ((UIRoleSelect *)((char *)this + 207156))->SetByte(1);
      v23 = off_5C7764;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v23, 1);
      this->m_bHandleEvent = 0;
      LOBYTE(result) = 0;
      return result;
    }
  }
  p_m_bCamEventFlag = &this->m_bCamEventFlag;
  nParama = 0;
  v26 = &this->m_bCamEventFlag;
  p_m_bActionActive = &Buffer.m_partyActor.m_bActionActive;
  do
  {
    if ( *p_m_bCamEventFlag )
    {
      v13 = 0;
      v14 = *(_WORD **)(v25 + 8);
      v15 = v14 + 296;
      do
      {
        if ( *v15 > 0 )
          v4 += Buffer.m_partyActor.m_dwMatMsg[v13 + 9 + nParama]
              - *(_DWORD *)&Buffer.m_partyActor.m_curact[4 * v13 + 39 + 4 * nParama];
        if ( v14[311] )
          v4 += *(p_m_bActionActive - 1);
        if ( v14[312] )
          v4 += *p_m_bActionActive;
        if ( v14[309] )
          v4 += *(p_m_bActionActive - 3);
        if ( v14[310] )
          v4 += *(p_m_bActionActive - 2);
        if ( v14[313] )
          v4 += p_m_bActionActive[1];
        ++v13;
        ++v15;
      }
      while ( v13 < 12 );
    }
    p_m_bActionActive += 1408;
    p_m_bCamEventFlag = ++v26;
    nParama += 352;
  }
  while ( (int)p_m_bActionActive < (int)((unsigned __int8 *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[148] + 3) );
  if ( v4 > 0 )
    v24 = 0;
  v16 = *(_DWORD *)(v25 + 8);
  v17 = *(_BYTE *)(v16 + 577);
  if ( v17 == 1 || v17 == 2 )
  {
    result = 1408 * *((_DWORD *)this + 51446);
    if ( *(_DWORD *)&Buffer.m_partyActor.m_curact[result + 43] < *(_DWORD *)(v16 + 688)
      || *(_DWORD *)&Buffer.m_partyActor.m_curact[result + 47] < *(_DWORD *)(v16 + 692) )
    {
      if ( bFlag )
        sprintf(this->m_szCamPath, "\\n      %s", (const char *)dword_DCA03C);
      else
        sprintf(this->m_szCamPath, "\\n      %s", (const char *)dword_DD213C);
      ((UICaption *)((char *)this + 207612))->SetEnable((int)this->m_szCamPath, 0);
      if ( !v28 )
        goto LABEL_55;
      goto LABEL_54;
    }
    if ( *(_DWORD *)(v16 + 696) == 10 )
    {
      v18 = 0;
      v19 = &this->m_bCamEventFlag;
      v20 = &Buffer.m_partyActor.m_dwMatMsg[9];
      v21 = 2 * *(_DWORD *)&Buffer.m_partyActor.m_szTexture[result + 4] + 40;
      do
      {
        if ( *v19 )
        {
          v22 = *v20 - v20[12];
          if ( v22 >= v21 )
            v22 = v21;
          v18 += v22;
        }
        v20 += 352;
        ++v19;
      }
      while ( (int)v20 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[208] );
      result = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
      if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom < v18
        || ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom <= 0
        || v18 <= 0 )
      {
        sprintf(this->m_szCamPath, "\\n      %s", (const char *)dword_DD273C);
        ((UICaption *)((char *)this + 207612))->SetEnable((int)this->m_szCamPath, 0);
        if ( v28 )
        {
          result = ((UIRoleSelect *)((char *)this + 207156))->SetByte(1);
          LOBYTE(result) = 0;
          return result;
        }
        goto LABEL_56;
      }
    }
    if ( !v24 )
    {
      LOBYTE(result) = 1;
      return result;
    }
  }
  sprintf(this->m_szCamPath, "\\n        %s", (const char *)dword_DC9F3C);
  ((UICaption *)((char *)this + 207612))->SetEnable((int)this->m_szCamPath, 0);
  if ( v28 )
LABEL_54:
    result = ((UIRoleSelect *)((char *)this + 207156))->SetByte(1);
LABEL_55:
  this->m_bHandleEvent = 0;
LABEL_56:
  LOBYTE(result) = 0;
  return result;
}

// 0x0048C9A0
int CameraCtrl::ProcessCameraTask(int a2, int a3)
{
  int v4; // edx
  int v5; // ecx
  char *v6; // esi
  int v7; // edi
  int v8; // ecx
  unsigned int *v9; // esi
  unsigned __int8 *p_m_bActionActive; // edx
  int v11; // eax
  _WORD *v12; // edi
  int v13; // ecx
  int v14; // ebx
  char *v15; // esi
  int v16; // edi
  int v18; // eax
  int v19; // edi
  int v20; // esi
  int v21; // eax
  int *v22; // edx
  char v23; // al
  char v24; // al
  int v25; // esi
  char *v26; // edi
  char v27; // al
  char v28; // [esp+0x13] [ebp-0x41]
  unsigned int *v29; // [esp+0x14] [ebp-0x40]
  int v30; // [esp+0x18] [ebp-0x3C]
  char *nVal; // [esp+0x1C] [ebp-0x38]
  int v32; // [esp+0x20] [ebp-0x34]
  _DWORD v33[5]; // [esp+0x2C] [ebp-0x28] BYREF
  _DWORD v34[5]; // [esp+0x40] [ebp-0x14] BYREF
  _BYTE *p_m_bCamEventFlag; // [esp+0x58] [ebp+0x4]

  memset(&v33[1], 0, 16);
  memset(&v34[1], 0, 16);
  v4 = *((_DWORD *)this + 51446);
  this->m_bHandleEvent = 1;
  v32 = 12 * a2;
  v33[0] = 0;
  v34[0] = 0;
  v28 = 1;
  v5 = 12 * a2 + 1192 * (a3 + 8 * v4);
  nVal = (char *)&this->m_CamBlocks + v5 + 4;
  if ( !*(int *)((char *)&this->m_CamBlocks + v5 + 12) )
  {
    v6 = (char *)this + 217324;
    v7 = 5;
    do
    {
      (**(void ( ***)(char *, _DWORD))v6)(v6, 0);
      v6 += 4892;
      --v7;
    }
    while ( v7 );
  }
  v8 = 592;
  v9 = &Buffer.m_partyActor.m_dwMatMsg[9];
  v30 = 592;
  v29 = &Buffer.m_partyActor.m_dwMatMsg[9];
  do
  {
    p_m_bActionActive = &Buffer.m_partyActor.m_bActionActive;
    p_m_bCamEventFlag = &this->m_bCamEventFlag;
    v11 = 0;
    do
    {
      if ( *p_m_bCamEventFlag )
      {
        v12 = (_WORD *)*((_DWORD *)nVal + 2);
        if ( *(_WORD *)((char *)v12 + v8) )
        {
          v13 = *((_DWORD *)this + 51446);
          v33[v11] += *v9 - v9[12];
          v14 = *(int *)((char *)&this->m_CamBlocks + 9536 * v13 + 1192 * a3 + v32 + 12);
          v8 = v30;
          v34[v11] += *(__int16 *)(v14 + v30);
        }
        if ( v12[311] )
        {
          v33[v11] += *(p_m_bActionActive - 1);
          ++v34[v11];
        }
        if ( v12[312] )
        {
          v33[v11] += *p_m_bActionActive;
          ++v34[v11];
        }
        if ( v12[309] )
        {
          v33[v11] += *(p_m_bActionActive - 3);
          ++v34[v11];
        }
        if ( v12[310] )
        {
          v33[v11] += *(p_m_bActionActive - 2);
          ++v34[v11];
        }
        if ( v12[313] )
        {
          v33[v11] += p_m_bActionActive[1];
          ++v34[v11];
        }
        if ( (int)v34[v11] > 0 )
          v28 = 0;
      }
      p_m_bActionActive += 1408;
      v9 += 352;
      ++v11;
      ++p_m_bCamEventFlag;
    }
    while ( (int)p_m_bActionActive < (int)((unsigned __int8 *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[148] + 3) );
    v8 += 2;
    v9 = v29 + 1;
    v30 = v8;
    ++v29;
  }
  while ( (int)v29 < (int)&Buffer.m_partyActor.m_curact[39] );
  if ( v28 )
  {
    v15 = (char *)this + 217324;
    v16 = 5;
    do
    {
      (**(void ( ***)(char *, _DWORD))v15)(v15, 0);
      v15 += 4892;
      --v16;
    }
    while ( v16 );
    this->m_bHandleEvent = 0;
    return -2;
  }
  else
  {
    v18 = 0;
    while ( !*(&this->m_bCamEventFlag + v18) )
    {
      if ( ++v18 >= 5 )
      {
        v19 = 0;
        goto LABEL_32;
      }
    }
    v19 = v33[v18];
LABEL_32:
    v20 = 0;
    v21 = 0;
    v22 = v33;
    do
    {
      if ( *(&this->m_bCamEventFlag + v21) && *v22 > v19 )
      {
        v19 = *v22;
        v20 = v21;
      }
      ++v21;
      ++v22;
    }
    while ( v21 < 5 );
    if ( !v33[v20] )
      v20 = v19;
    v23 = *(_BYTE *)(*((_DWORD *)nVal + 2) + 577);
    if ( v23 == 1 )
    {
      this->CalcStatPower((int)nVal);
      if ( v24 )
        (**((void ( ***)(char *, int))this + 1223 * v20 + 54331))((char *)this + 4892 * v20 + 217324, 1);
      this->m_bAutoRotate = 0;
      return v20;
    }
    else if ( v23 == 2 )
    {
      v25 = 0;
      v26 = (char *)this + 217324;
      do
      {
        if ( *(&this->m_bCamEventFlag + v25) )
        {
          this->CalcStatPower((int)nVal);
          if ( v27 )
            (**(void ( ***)(char *, int))v26)(v26, 1);
        }
        else
        {
          (**(void ( ***)(char *, _DWORD))v26)(v26, 0);
        }
        ++v25;
        v26 += 4892;
      }
      while ( v25 < 5 );
      this->m_bAutoRotate = 1;
      return -1;
    }
    else
    {
      return -3;
    }
  }
}

// 0x0048CCE0
char CameraCtrl::InitBlendState(int a2, int a3)
{
  int v4; // ebx
  int v5; // ecx
  int v6; // edi
  int *p_m_nBlendState; // eax
  int v9; // ebp
  char *v10; // ebx
  int *TargetRole; // edx
  int v12; // eax
  int v13; // ecx
  int *v14; // eax
  int v15; // ecx
  int m_nBlendTimer; // ecx
  int *v17; // eax
  char *m_szCamPath; // edi
  int v19; // [esp+0x10] [ebp-0x1C]
  int p_DWORD; // [esp+0x14] [ebp-0x18] BYREF
  int v21; // [esp+0x18] [ebp-0x14]
  int SkillNum; // [esp+0x1C] [ebp-0x10]
  char pOut[12]; // [esp+0x20] [ebp-0xC] BYREF
  int v24; // [esp+0x30] [ebp+0x4]

  v4 = 0;
  v5 = *((_DWORD *)this + 51446);
  v6 = 0;
  p_m_nBlendState = &this->m_nBlendState;
  while ( v5 != *(p_m_nBlendState - 1) || a2 != *p_m_nBlendState )
  {
    ++v6;
    p_m_nBlendState += 75;
    if ( v6 >= 8 )
      goto LABEL_5;
  }
  p_DWORD = 0xFFFF;
  v21 = 0;
  SkillNum = 0;
  v19 = 0;
  v24 = 0;
  v9 = 0;
  if ( ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount() > 0 )
  {
    v10 = (char *)this + 300 * v6;
    do
    {
      TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
      v12 = *TargetRole;
      p_DWORD = v12;
      v13 = TargetRole[1];
      v21 = v13;
      SkillNum = TargetRole[2];
      if ( v12 == *((_DWORD *)v10 + 297) )
        v19 = v13;
      if ( v12 == *((_DWORD *)v10 + 298) )
        v24 = v13;
      ++v9;
    }
    while ( v9 < ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount() );
    v4 = v19;
  }
  v14 = (int *)((char *)this + 300 * v6);
  if ( v14[297] == v14[298] )
    this->m_nBlendTimer = 2;
  else
    this->m_nBlendTimer = 0;
  v15 = v14[297];
  if ( v15 == v14[298] && v15 == v14[299] )
    this->m_nBlendTimer = 3;
  m_nBlendTimer = this->m_nBlendTimer;
  if ( v4 < m_nBlendTimer && v24 < m_nBlendTimer || v4 <= 0 && v24 <= 0 || v4 < 1 || v24 < 1 )
  {
    m_szCamPath = this->m_szCamPath;
    sprintf(this->m_szCamPath, "\\n\\n\\n        %s", dword_DC8A3C);
  }
  else
  {
    p_DWORD = v14[232];
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(p_DWORD);
    v17 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD);
    if ( !v17 || v17[1] < 99 )
    {
LABEL_5:
      ((MainPropUI *)this)->FindValidSaveSlot();
      return 1;
    }
    m_szCamPath = this->m_szCamPath;
    sprintf(this->m_szCamPath, "\\n\\n\\n         %s", dword_DCCC3C);
  }
  ((UICaption *)((char *)this + 206244))->SetEnable((int)m_szCamPath, 0);
  ((UIRoleSelect *)((char *)this + 205788))->SetByte(1);
  sub_445E50((int)this + 248268);
  this->m_bHandleEvent = 0;
  this->m_nBlendTimer = 0;
  return 0;
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
  int *v26; // [esp+0x0] [ebp-0x40]
  gbCamera *v27; // [esp+0x10] [ebp-0x30]
  gbCamera *v28; // [esp+0x14] [ebp-0x2C] BYREF
  gbCamera *v29; // [esp+0x18] [ebp-0x28]
  int p_DWORD; // [esp+0x1C] [ebp-0x24] BYREF
  int m_nBlendTimer; // [esp+0x20] [ebp-0x20]
  int v32; // [esp+0x24] [ebp-0x1C]
  int v33; // [esp+0x28] [ebp-0x18] BYREF
  int v34; // [esp+0x2C] [ebp-0x14]
  int SkillNum; // [esp+0x30] [ebp-0x10]
  _BYTE pOut[12]; // [esp+0x34] [ebp-0xC] BYREF
  int nVala; // [esp+0x48] [ebp+0x8]

  p_m_szText = &this->m_szText;
  sprintf((char *const)&this->m_szText, byte_5967B0, g_szSceneUIText);
  v5 = nVal;
  this->m_bBlendActive = 1;
  v6 = 3 * *((unsigned __int8 *)this + nVal + 307032) + 12;
  v7 = &this->m_pCamera + 75 * *((unsigned __int8 *)this + nVal + 307032);
  v27 = v7[297];
  v8 = v7[298];
  v29 = v7[299];
  v28 = v8;
  *((float *)&this->m_pCamera + 20 * v6 + 5 * v6 + arg0) = *((float *)&this->m_pCamera + 20 * v6 + 5 * v6 + arg0)
                                                         + 0.0099999998;
  v9 = &this->m_roleParams
     + 60 * *((unsigned __int8 *)this + v5 + 307032)
     + 15 * *((unsigned __int8 *)this + v5 + 307032)
     + arg0;
  if ( *v9 >= 1.0 )
    *v9 = 1.0;
  v10 = *((unsigned __int8 *)this + nVal + 307032);
  g_fCamRoleParams[4 * v10 + arg0 + v10] = *(&this->m_roleParams + 60 * v10 + 15 * v10 + arg0);
  if ( !((UIFrameWnd *)this)->RollProbability(*(&this->m_roleParams
          + 60 * *((unsigned __int8 *)this + nVal + 307032)
          + 15 * *((unsigned __int8 *)this + nVal + 307032)
          + arg0)) )
  {
    if ( this->InitBlendState(nVal, 7) )
    {
      p_DWORD = 0xFFFF;
      m_nBlendTimer = 0;
      v32 = 0;
      this->m_nViewMode = 0;
      if ( ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount() > 0 )
      {
        while ( 1 )
        {
          TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
          v18 = *TargetRole;
          p_DWORD = *TargetRole;
          m_nBlendTimer = TargetRole[1];
          v32 = TargetRole[2];
          if ( this->m_nBlendTimer <= 0 )
          {
            if ( (gbCamera *)v18 == v27 || (gbCamera *)v18 == v28 || (gbCamera *)v18 == v29 )
            {
              m_nBlendTimer = 1;
              ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
              this->m_nBlendTimer = 0;
              lstrcatA((LPSTR)p_m_szText, asc_5C9190);
              lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
              lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
              sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)dword_DC373C, 1);
              lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
              v5 = nVal;
            }
          }
          else
          {
            v19 = &this->m_pCamera + 75 * *((unsigned __int8 *)this + v5 + 307032);
            if ( (gbCamera *)v18 == v19[297] || (gbCamera *)v18 == v19[298] || (gbCamera *)v18 == v19[299] )
            {
              m_nBlendTimer = this->m_nBlendTimer;
              ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
              this->m_nBlendTimer = 0;
              lstrcatA((LPSTR)p_m_szText, asc_5C9190);
              lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
              lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
              v21 = 1;
              v22 = &v28;
              v23 = 2;
              do
              {
                if ( v27 == *v22 )
                  ++v21;
                ++v22;
                --v23;
              }
              while ( v23 );
              sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)dword_DC373C, v21);
              lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
              break;
            }
          }
          v20 = this->m_nViewMode + 1;
          this->m_nViewMode = v20;
          if ( v20 >= ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount() )
          {
            ((CCBCamControl *)this)->ProcessRenderQueue();
            this->m_bBlendPause = 0;
            goto LABEL_45;
          }
        }
      }
      ((CCBCamControl *)this)->ProcessRenderQueue();
      this->m_bBlendPause = 0;
      goto LABEL_45;
    }
    this->m_nBlendTimer = 0;
    this->m_bBlendActive = 0;
LABEL_44:
    sub_445E50((int)this + 248268);
    goto LABEL_45;
  }
  if ( !this->InitBlendState(nVal, 7) )
  {
    this->m_bBlendActive = 0;
    this->m_nBlendTimer = 0;
    goto LABEL_44;
  }
  v33 = 0xFFFF;
  v34 = 0;
  SkillNum = 0;
  v11 = *(&this->m_nSlotParam + 75 * *((unsigned __int8 *)this + nVal + 307032));
  v34 = 1;
  v33 = v11;
  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v11);
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&v33, v26);
  lstrcatA((LPSTR)p_m_szText, asc_5C9190);
  lstrcatA((LPSTR)p_m_szText, byte_DCD03C);
  lstrcatA((LPSTR)p_m_szText, (LPCSTR)(SkillNum + 4));
  sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)dword_DC373C, 1);
  lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
  p_DWORD = 0xFFFF;
  m_nBlendTimer = 0;
  v32 = 0;
  this->m_nViewMode = 0;
  if ( ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount() <= 0 )
    goto LABEL_22;
  while ( 1 )
  {
    v12 = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
    v13 = *v12;
    p_DWORD = *v12;
    m_nBlendTimer = v12[1];
    v32 = v12[2];
    if ( this->m_nBlendTimer <= 0 )
    {
      if ( (gbCamera *)v13 == v27 || (gbCamera *)v13 == v28 || (gbCamera *)v13 == v29 )
      {
        m_nBlendTimer = 1;
        ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
        this->m_nBlendTimer = 0;
        lstrcatA((LPSTR)p_m_szText, asc_5C9190);
        lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
        lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
        sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)dword_DC373C, 1);
        lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
      }
      goto LABEL_15;
    }
    if ( (gbCamera *)v13 == v27 || (gbCamera *)v13 == v28 || (gbCamera *)v13 == v29 )
      break;
LABEL_15:
    v14 = this->m_nViewMode + 1;
    this->m_nViewMode = v14;
    if ( v14 >= ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount() )
    {
      ((CCBCamControl *)this)->ProcessRenderQueue();
      this->m_bBlendPause = 1;
      goto LABEL_45;
    }
  }
  m_nBlendTimer = this->m_nBlendTimer;
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
  this->m_nBlendTimer = 0;
  lstrcatA((LPSTR)p_m_szText, asc_5C9190);
  lstrcatA((LPSTR)p_m_szText, byte_DCD13C);
  lstrcatA((LPSTR)p_m_szText, (LPCSTR)(v32 + 4));
  nVala = 1;
  v15 = &v28;
  v16 = 2;
  do
  {
    if ( v27 == *v15 )
      ++nVala;
    ++v15;
    --v16;
  }
  while ( v16 );
  sprintf(this->m_szCamPath, " [%s%d]\\n", (const char *)dword_DC373C, nVala);
  lstrcatA((LPSTR)p_m_szText, this->m_szCamPath);
LABEL_22:
  ((CCBCamControl *)this)->ProcessRenderQueue();
  this->m_bBlendPause = 1;
LABEL_45:
  v25 = off_5C778C;
  Instance = CScreenMode::GetInstance();
  ((CScreenMode *)Instance)->AudioSetPosition(v25, 1);
  this->m_nBlendWeight = 7;
  this->m_bBlendWeight = 0;
}

// 0x0048D5D0
void * CameraCtrl::CreateCameraUI(int nVal)
{
  float *p_m_fLerpTargetZ; // edi
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // ecx
  UIScene *v13; // edi
  int v14; // ecx
  int v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int v24; // eax
  int v25; // ecx
  int v26; // eax
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  int v30; // eax
  UIStatic *v31; // edi
  int v32; // ebx
  int v33; // eax
  int v34; // edx
  int v35; // edx
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // edx
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // eax
  int i; // edi
  int v48; // eax
  int v49; // edx
  int v50; // eax
  int v51; // edx
  int v52; // eax
  void *result; // eax
  int v54; // [esp+0x244] [ebp-B8h]
  int *v55; // [esp+0x248] [ebp-B4h]
  int v56; // [esp+0x24C] [ebp-B0h]
  _DWORD v57[2]; // [esp+0x258] [ebp-A4h] BYREF
  int v58; // [esp+0x260] [ebp-0x9C]
  int v59; // [esp+0x264] [ebp-0x98]
  int v60; // [esp+0x268] [ebp-0x94] BYREF
  int v61; // [esp+0x26C] [ebp-0x90]
  int v62; // [esp+0x270] [ebp-0x8C]
  int v63; // [esp+0x274] [ebp-0x88]
  int pnVal; // [esp+0x278] [ebp-0x84] BYREF
  int v65; // [esp+0x27C] [ebp-0x80]
  int v66; // [esp+0x280] [ebp-0x7C]
  int v67; // [esp+0x284] [ebp-0x78]
  int v68; // [esp+0x288] [ebp-0x74] BYREF
  int v69; // [esp+0x28C] [ebp-0x70]
  int v70; // [esp+0x290] [ebp-0x6C]
  int v71; // [esp+0x294] [ebp-0x68]
  int v72; // [esp+0x298] [ebp-0x64] BYREF
  int v73; // [esp+0x29C] [ebp-0x60]
  int v74; // [esp+0x2A0] [ebp-0x5C]
  int v75; // [esp+0x2A4] [ebp-0x58]
  int v76; // [esp+0x2A8] [ebp-0x54] BYREF
  int v77; // [esp+0x2AC] [ebp-0x50]
  int v78; // [esp+0x2B0] [ebp-0x4C]
  int v79; // [esp+0x2B4] [ebp-0x48]
  int v80; // [esp+0x2B8] [ebp-0x44]
  int v81; // [esp+0x2BC] [ebp-0x40] BYREF
  int v82; // [esp+0x2C0] [ebp-0x3C]
  int v83; // [esp+0x2C4] [ebp-0x38]
  int v84; // [esp+0x2C8] [ebp-0x34]
  int v85; // [esp+0x2CC] [ebp-0x30] BYREF
  int v86; // [esp+0x2D0] [ebp-0x2C]
  int v87; // [esp+0x2D4] [ebp-0x28]
  int v88; // [esp+0x2D8] [ebp-0x24]
  _DWORD v89[4]; // [esp+0x2DC] [ebp-0x20] BYREF
  int nVal2[4]; // [esp+0x2EC] [ebp-0x10] BYREF

  p_m_fLerpTargetZ = &this->m_fLerpTargetZ;
  this->m_nUIPosX = 0;
  this->m_fLerpTargetZ = 0.0;
  this->m_nUIWidgetW = this->m_nUIWidgetSavedW;
  this->m_nUIWidgetH = LODWORD(this->m_fUIWidgetSavedH);
  ((UIListBox *)this)->SetSelTexture(-1, LODWORD(this->m_fLerpTargetZ), this->m_nUIPosX, this->m_nUIWidgetW, this->m_nUIWidgetH, 0);
  v4 = this->m_nUIPosX + 18;
  v76 = *(_DWORD *)p_m_fLerpTargetZ + 592;
  v77 = v4;
  v78 = v76 + 192;
  v79 = v4 + 526;
  (*(void ( **)(char *, int, int *, CameraCtrl *))(*((_DWORD *)this + 12759) + 16))(
    (char *)this + 51036,
    161,
    &v76,
    this);
  ((UIStatic *)((char *)this + 51036))->CreateFromTemplate();
  v5 = *((_DWORD *)this + 12797);
  v77 += 26;
  v76 = v78;
  v79 = v77 + 526;
  v78 += 17;
  (*(void ( **)(char *, int, int *, CameraCtrl *))(v5 + 16))((char *)this + 51188, 161, &v76, this);
  ((UIStatic *)((char *)this + 51188))->CreateFromTemplate();
  v69 = 0;
  v68 = v78 - 205;
  v70 = v78 - 205 + 203;
  v6 = *((_DWORD *)this + 12835);
  v71 = 64;
  (*(void ( **)(char *, int, int *, CameraCtrl *))(v6 + 16))((char *)this + 51340, 161, &v68, this);
  ((UIStatic *)((char *)this + 51340))->CreateFromTemplate();
  v7 = *((_DWORD *)this + 13997);
  v69 = -4;
  v68 = 618;
  v70 = 738;
  v71 = 28;
  (*(void ( **)(char *, int, int *, CameraCtrl *))(v7 + 16))((char *)this + 55988, 161, &v68, this);
  ((UIScene *)((char *)this + 55988))->SetShow(0);
  sub_446010((char *)this + 55988);
  v8 = *((_DWORD *)this + 13959);
  v69 = 16;
  v68 = 668;
  v70 = 748;
  v71 = 48;
  (*(void ( **)(char *, int, int *, CameraCtrl *))(v8 + 16))((char *)this + 55836, 161, &v68, this);
  ((UIScene *)((char *)this + 55836))->SetShow(0);
  sub_446010((char *)this + 55836);
  ((MainPropUI *)this)->CreateCoverTemplate();
  v9 = *((_DWORD *)this + 52580);
  v82 = 125;
  v81 = 213;
  v83 = 586;
  v84 = 519;
  (*(void ( **)(char *, char *, int *, CameraCtrl *))(v9 + 16))(
    (char *)this + 210320,
    &byte_A00001,
    &v81,
    this);
  ((UIStatic *)((char *)this + 210320))->CreateFromTemplate();
  v10 = *((_DWORD *)this + 52559);
  v89[1] = v82;
  v89[0] = v81 + 7;
  v89[3] = v82 + 32;
  v89[2] = v81 + 365;
  (*(void ( **)(char *, char *, _DWORD *, char *, _DWORD, CameraCtrl *))(v10 + 28))(
    (char *)this + 210236,
    &byte_A00001,
    v89,
    "UI\\Flex\\Bar.tga",
    0,
    this);
  ((CScreenMode *)((char *)this + 210236))->SetPosition(32,   32);
  v11 = v81 + 18;
  *((_DWORD *)this + 13804) = v82 + 52;
  *((_DWORD *)this + 13803) = v11;
  v12 = *((_DWORD *)this + 13804);
  *((_DWORD *)this + 13805) = v11 + 376;
  *((_DWORD *)this + 13806) = v12 + 32;
  v13 = (UIScene *)((char *)this + 55228);
  v80 = 4;
  do
  {
// [VFTABLE] ((void ( *)(UIScene *, char *, char *, CameraCtrl *))v13->__vftable->Create)(
// [VFTABLE]   v13,
// [VFTABLE]   &byte_A00001,
// [VFTABLE]   (char *)this + 55212,
// [VFTABLE]   this);
    ((UIScene *)v13)->SetShow(0);
    sub_446010(v13);
// [VFTABLE] ((void ( *)(UIScene *, _DWORD))v13->__vftable->ShowWindow)(v13, 0);
    v13 = (UIScene *)((char *)v13 + 152);
    --v80;
  }
  while ( v80 );
  LOBYTE(v14) = g_bDebugMode;
  v15 = *((_DWORD *)this + 59953);
  v73 = 207;
  v72 = 232;
  v74 = 566;
  v75 = 485;
  v16 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(v15 + 28))(
          (char *)this + 239812,
          &byte_A00217,
          &v72,
          this,
          0,
          0,
          v14);
  LOBYTE(v16) = g_bDebugMode;
  ((UIListBox *)((char *)this + 239812))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v16);
  *((_DWORD *)this + 60243) = -8;
  *((_DWORD *)this + 60244) = -8;
  *((_DWORD *)this + 60245) = 14;
  ((UIListBox *)((char *)this + 239812))->SetLockSel();
  ((UIListBox *)((char *)this + 239812))->SetFirstShow((int)"Name", 276);
  ((UIListBox *)((char *)this + 239812))->SetFirstShow((int)&off_5C91C8, 92);
  (**((void ( ***)(char *, _DWORD))this + 59953))((char *)this + 239812, 0);
  LOBYTE(v17) = g_bDebugMode;
  v18 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(*((_DWORD *)this + 60255) + 28))(
          (char *)this + 241020,
          &byte_A00218,
          &v72,
          this,
          0,
          0,
          v17);
  LOBYTE(v18) = g_bDebugMode;
  ((UIListBox *)((char *)this + 241020))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v18);
  *((_DWORD *)this + 60545) = -8;
  *((_DWORD *)this + 60546) = -8;
  *((_DWORD *)this + 60547) = 14;
  ((UIListBox *)((char *)this + 241020))->SetLockSel();
  ((UIListBox *)((char *)this + 241020))->SetFirstShow((int)"Name", 150);
  ((UIListBox *)((char *)this + 241020))->SetFirstShow((int)&off_5C91C8, 72);
  ((UIListBox *)((char *)this + 241020))->SetFirstShow((int)"Lv", 38);
  ((UIListBox *)((char *)this + 241020))->SetFirstShow((int)"UseTimes", 72);
  (**((void ( ***)(char *, _DWORD))this + 60255))((char *)this + 241020, 0);
  LOBYTE(v19) = g_bDebugMode;
  v20 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(*((_DWORD *)this + 60557) + 28))(
          (char *)this + 242228,
          byte_A00219,
          &v72,
          this,
          0,
          0,
          v19);
  LOBYTE(v20) = g_bDebugMode;
  ((UIListBox *)((char *)this + 242228))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v20);
  *((_DWORD *)this + 60847) = -8;
  *((_DWORD *)this + 60848) = -8;
  *((_DWORD *)this + 60849) = 14;
  ((UIListBox *)((char *)this + 242228))->SetLockSel();
  ((UIListBox *)((char *)this + 242228))->SetFirstShow((int)"Name", 150);
  ((UIListBox *)((char *)this + 242228))->SetFirstShow((int)&off_5C91C8, 72);
  ((UIListBox *)((char *)this + 242228))->SetFirstShow((int)"Lv", 38);
  ((UIListBox *)((char *)this + 242228))->SetFirstShow((int)"UseTimes", 72);
  (**((void ( ***)(char *, _DWORD))this + 60557))((char *)this + 242228, 0);
  LOBYTE(v21) = g_bDebugMode;
  v22 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(*((_DWORD *)this + 60859) + 28))(
          (char *)this + 243436,
          &byte_A00220,
          &v72,
          this,
          0,
          0,
          v21);
  LOBYTE(v22) = g_bDebugMode;
  ((UIListBox *)((char *)this + 243436))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v22);
  *((_DWORD *)this + 61149) = -8;
  *((_DWORD *)this + 61150) = -8;
  *((_DWORD *)this + 61151) = 14;
  ((UIListBox *)((char *)this + 243436))->SetLockSel();
  ((UIListBox *)((char *)this + 243436))->SetFirstShow((int)"Name", 150);
  ((UIListBox *)((char *)this + 243436))->SetFirstShow((int)&off_5C91C8, 72);
  ((UIListBox *)((char *)this + 243436))->SetFirstShow((int)"Lv", 38);
  ((UIListBox *)((char *)this + 243436))->SetFirstShow((int)"UseTimes", 72);
  (**((void ( ***)(char *, _DWORD))this + 60859))((char *)this + 243436, 0);
  LOBYTE(v23) = g_bDebugMode;
  v24 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(*((_DWORD *)this + 61161) + 28))(
          (char *)this + 244644,
          &byte_A00221,
          &v72,
          this,
          0,
          0,
          v23);
  LOBYTE(v24) = g_bDebugMode;
  ((UIListBox *)((char *)this + 244644))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v24);
  *((_DWORD *)this + 61451) = -8;
  *((_DWORD *)this + 61452) = -8;
  *((_DWORD *)this + 61453) = 14;
  ((UIListBox *)((char *)this + 244644))->SetLockSel();
  ((UIListBox *)((char *)this + 244644))->SetFirstShow((int)"Name", 150);
  ((UIListBox *)((char *)this + 244644))->SetFirstShow((int)&off_5C91C8, 72);
  ((UIListBox *)((char *)this + 244644))->SetFirstShow((int)"Lv", 38);
  ((UIListBox *)((char *)this + 244644))->SetFirstShow((int)"UseTimes", 72);
  (**((void ( ***)(char *, _DWORD))this + 61161))((char *)this + 244644, 0);
  LOBYTE(v25) = g_bDebugMode;
  v26 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(*((_DWORD *)this + 61463) + 28))(
          (char *)this + 245852,
          &byte_A00222,
          &v72,
          this,
          0,
          0,
          v25);
  LOBYTE(v26) = g_bDebugMode;
  ((UIListBox *)((char *)this + 245852))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v26);
  *((_DWORD *)this + 61753) = -8;
  *((_DWORD *)this + 61754) = -8;
  *((_DWORD *)this + 61755) = 14;
  ((UIListBox *)((char *)this + 245852))->SetLockSel();
  ((UIListBox *)((char *)this + 245852))->SetFirstShow((int)"Name", 150);
  ((UIListBox *)((char *)this + 245852))->SetFirstShow((int)&off_5C91C8, 72);
  ((UIListBox *)((char *)this + 245852))->SetFirstShow((int)"Lv", 38);
  ((UIListBox *)((char *)this + 245852))->SetFirstShow((int)"UseTimes", 72);
  (**((void ( ***)(char *, _DWORD))this + 61463))((char *)this + 245852, 0);
  LOBYTE(v27) = g_bDebugMode;
  v28 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(*((_DWORD *)this + 61765) + 28))(
          (char *)this + 247060,
          &byte_A00223,
          &v72,
          this,
          0,
          0,
          v27);
  LOBYTE(v28) = g_bDebugMode;
  ((UIListBox *)((char *)this + 247060))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v28);
  *((_DWORD *)this + 62055) = -8;
  *((_DWORD *)this + 62056) = -8;
  *((_DWORD *)this + 62057) = 14;
  ((UIListBox *)((char *)this + 247060))->SetLockSel();
  ((UIListBox *)((char *)this + 247060))->SetFirstShow((int)"Name", 150);
  ((UIListBox *)((char *)this + 247060))->SetFirstShow((int)&off_5C91C8, 72);
  ((UIListBox *)((char *)this + 247060))->SetFirstShow((int)"Lv", 38);
  ((UIListBox *)((char *)this + 247060))->SetFirstShow((int)"UseTimes", 72);
  (**((void ( ***)(char *, _DWORD))this + 61765))((char *)this + 247060, 0);
  LOBYTE(v29) = g_bDebugMode;
  v30 = (*(int ( **)(char *, char *, int *, CameraCtrl *, _DWORD, _DWORD, int))(*((_DWORD *)this + 62067) + 28))(
          (char *)this + 248268,
          &byte_A00224,
          &v72,
          this,
          0,
          0,
          v29);
  LOBYTE(v30) = g_bDebugMode;
  ((UIListBox *)((char *)this + 248268))->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v30);
  *((_DWORD *)this + 62357) = -8;
  *((_DWORD *)this + 62358) = -8;
  *((_DWORD *)this + 62359) = 14;
  ((UIListBox *)((char *)this + 248268))->SetLockSel();
  ((UIListBox *)((char *)this + 248268))->SetFirstShow((int)"Com1", 98);
  ((UIListBox *)((char *)this + 248268))->SetFirstShow((int)"Com2", 98);
  ((UIListBox *)((char *)this + 248268))->SetFirstShow((int)"Com3", 98);
  ((UIListBox *)((char *)this + 248268))->SetFirstShow((int)"Percent", 36);
  (**((void ( ***)(char *, _DWORD))this + 62067))((char *)this + 248268, 0);
  v85 = v72;
  v86 = v73;
  v87 = v72 + 333;
  v88 = v73 + 29;
  v31 = (UIStatic *)((char *)this + 210472);
  v32 = 9;
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, char *, int *, CameraCtrl *))v31->__vftable->Create)(
// [VFTABLE]   v31,
// [VFTABLE]   &byte_A00001,
// [VFTABLE]   &v85,
// [VFTABLE]   this);
    ((UIStatic *)v31++)->CreateFromTemplate();
    v86 = v88;
    v33 = v88 + 29;
    --v32;
    v88 += 29;
  }
  while ( v32 );
  LOBYTE(v33) = g_bDebugMode;
  v34 = *((_DWORD *)this + 59265);
  v57[1] = 124;
  v57[0] = 229;
  v58 = 271;
  v59 = 174;
  (*(void ( **)(char *, char *, _DWORD *, CameraCtrl *, char *, int, int))(v34 + 28))(
    (char *)this + 237060,
    &byte_A00225,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Skill",
    1,
    v33);
  ((PalScript *)((char *)this + 237060))->OpenScript("UI\\GameMainUI\\Magic\\Skill2.tga", g_bDebugMode);
  sub_445E50((int)this + 237060);
  v35 = *((_DWORD *)this + 59351);
  v57[0] = v58 + 1;
  v58 += 43;
  v36 = v58;
  LOBYTE(v36) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, CameraCtrl *, char *, int, int))(v35 + 28))(
    (char *)this + 237404,
    &byte_A00226,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Shui",
    1,
    v36);
  ((PalScript *)((char *)this + 237404))->OpenScript("UI\\GameMainUI\\Magic\\Shui2.tga", g_bDebugMode);
  v37 = *((_DWORD *)this + 59437);
  v57[0] = v58 + 1;
  v58 += 43;
  v38 = v58;
  LOBYTE(v38) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, CameraCtrl *, char *, int, int))(v37 + 28))(
    (char *)this + 237748,
    &byte_A00227,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Huo",
    1,
    v38);
  ((PalScript *)((char *)this + 237748))->OpenScript("UI\\GameMainUI\\Magic\\Huo2.tga", g_bDebugMode);
  v57[0] = v58 + 1;
  v58 += 43;
  v39 = v58;
  LOBYTE(v39) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, CameraCtrl *, char *, int, int))(*((_DWORD *)this + 59523) + 28))(
    (char *)this + 238092,
    &byte_A00228,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Lei",
    1,
    v39);
  ((PalScript *)((char *)this + 238092))->OpenScript("UI\\GameMainUI\\Magic\\Lei2.tga", g_bDebugMode);
  v40 = *((_DWORD *)this + 59609);
  v57[0] = v58 + 1;
  v58 += 43;
  v41 = v58;
  LOBYTE(v41) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, CameraCtrl *, char *, int, int))(v40 + 28))(
    (char *)this + 238436,
    byte_A00229,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Feng",
    1,
    v41);
  ((PalScript *)((char *)this + 238436))->OpenScript("UI\\GameMainUI\\Magic\\Feng2.tga", g_bDebugMode);
  v42 = *((_DWORD *)this + 59695);
  v57[0] = v58 + 1;
  v58 += 43;
  v43 = v58;
  LOBYTE(v43) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, CameraCtrl *, char *, int, int))(v42 + 28))(
    (char *)this + 238780,
    &byte_A00230,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Tu",
    1,
    v43);
  ((PalScript *)((char *)this + 238780))->OpenScript("UI\\GameMainUI\\Magic\\Tu2.tga", g_bDebugMode);
  v44 = *((_DWORD *)this + 59781);
  v57[0] = v58 + 1;
  v58 += 43;
  v45 = v58;
  LOBYTE(v45) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, CameraCtrl *, char *, int, int))(v44 + 28))(
    (char *)this + 239124,
    &byte_A00231,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Suang",
    1,
    v45);
  ((PalScript *)((char *)this + 239124))->OpenScript("UI\\GameMainUI\\Magic\\Suang2.tga", g_bDebugMode);
  v57[0] = v58;
  v58 += 42;
  v46 = v58;
  LOBYTE(v46) = g_bDebugMode;
  (*(void ( **)(char *, __int16 *, _DWORD *, CameraCtrl *, char *, int, int))(*((_DWORD *)this + 59867) + 28))(
    (char *)this + 239468,
    &word_A00232,
    v57,
    this,
    "UI\\GameMainUI\\Magic\\Combo",
    1,
    v46);
  ((PalScript *)((char *)this + 239468))->OpenScript("UI\\GameMainUI\\Magic\\Combo2.tga", g_bDebugMode);
  v65 = 0;
  pnVal = 0;
  v66 = 0;
  v67 = 32;
  nVal2[1] = 0;
  nVal2[0] = 12;
  nVal2[2] = 590;
  nVal2[3] = 126;
  for ( i = 0; i < 5; ++i )
  {
    ((UITitle_XJTM *)this)->UpdateMonsterEntry(i, &pnVal);
    ((ArcSceneMonster *)this)->CreateInfoPanel(i, (int)nVal2, v54, v55, v56);
  }
  v48 = *((_DWORD *)this + 52960);
  v61 = 125;
  v60 = 10;
  v62 = 200;
  v63 = 539;
  (*(void ( **)(char *, char *, int *, CameraCtrl *))(v48 + 16))(
    (char *)this + 211840,
    byte_A00215,
    &v60,
    this);
  ((UIStatic *)((char *)this + 211840))->CreateFromTemplate();
  v49 = *((_DWORD *)this + 53074);
  v61 = 128;
  v60 = 18;
  v62 = 194;
  v63 = 370;
  (*(void ( **)(char *, char *, int *, CameraCtrl *))(v49 + 16))(
    (char *)this + 212296,
    byte_A00215,
    &v60,
    this);
  ((UIStatic *)((char *)this + 212296))->CreateFromTemplate();
  v50 = *((_DWORD *)this + 52998);
  v61 = 386;
  v60 = 22;
  v62 = 194;
  v63 = 492;
  (*(void ( **)(char *, char *, int *, CameraCtrl *))(v50 + 16))(
    (char *)this + 211992,
    byte_A00215,
    &v60,
    this);
  ((UIScene *)((char *)this + 211992))->SetShow(0);
  sub_446010((char *)this + 211992);
  v51 = *((_DWORD *)this + 53036);
  v61 = 510;
  v60 = 22;
  v62 = 178;
  v63 = 542;
  (*(void ( **)(char *, char *, int *, CameraCtrl *))(v51 + 16))(
    (char *)this + 212144,
    byte_A00215,
    &v60,
    this);
  ((UIScene *)((char *)this + 212144))->SetShow(0);
  sub_446010((char *)this + 212144);
  v52 = *((_DWORD *)this + 53112);
  v61 = 130;
  v60 = 56;
  v62 = 156;
  v63 = 162;
  (*(void ( **)(char *, char *, int *, CameraCtrl *))(v52 + 16))(
    (char *)this + 212448,
    byte_A00215,
    &v60,
    this);
  ((UIScene *)((char *)this + 212448))->SetShow(0);
  sub_446010((char *)this + 212448);
  ((CCBFiveNimbusWindow *)((char *)this + 249476))->CreateScriptAndCamera((int)dword_A00234, (int)this);
  if ( !strcmp("D16", g_szSceneUIText) )
    sprintf(this->m_szCamPath, byte_5967B0, "NONE");
  else
    sprintf(this->m_szCamPath, "Item\\%s\\%s.pol", "D16", "D16");
  ((PalScript *)((char *)this + 249548))->LoadModel(this->m_szCamPath, 0);
  *((_DWORD *)this + 62388) = 0;
  *((_DWORD *)this + 62386) = 1;
  ((CCBFiveNimbusWindow *)((char *)this + 249476))->SetFloatParam(160.0);
  ((Camera *)((char *)this + 249476))->UpdateCameraLookAt(110, 268, 600);
  ((UIPushButton *)((char *)this + 249476))->SetAnimOffset(1, 0, *(float *)&v54);

  v65 = 200;
  pnVal = 300;
  v66 = 556;
  v67 = 356;
  ((ARC_PlayerAtt *)((char *)this + 205788))->Create((int)&byte_ABC000, (int)&pnVal);
  ((UIItem *)((char *)this + 205788))->SetData(31);
  ((ARC_PlayerAtt *)((char *)this + 208524))->Create((int)&byte_ABC001, (int)&pnVal);
  ((UIItem *)((char *)this + 208524))->SetData(31);
  v66 = pnVal + 218;
  v67 = v65 + 96;
  ((ARC_PlayerAtt *)((char *)this + 207156))->Create((int)&word_ABC002, (int)&pnVal);
  result = ((UIItem *)((char *)this + 207156))->SetData(31);
  *((_DWORD *)this + 76755) = 206;
  *((_DWORD *)this + 76754) = 88;
  *((_DWORD *)this + 76756) = 168;
  *((_DWORD *)this + 76757) = 286;
  *((_DWORD *)this + 12758) = nVal;
  this->m_bCamDirty = 1;
  return result;
}

// 0x0048EE00
int CameraCtrl::FindNextValidSlot(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  ++*pCounter;
  while ( 1 )
  {
    v2 = *pCounter;
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
    v2 = *pCounter;
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

// 0x0048EE60
char CameraCtrl::ProcessSaveSlotNav()
{
  char result; // al
  int PrevValidSlot; // eax
  gbCamera *m_pCamera; // edx
  int NextValidSlot; // eax
  gbCamera *v6; // edx
  int v7; // eax
  int v8; // eax

  result = *((_BYTE *)this + 207129);
  if ( !result )
  {
    result = *((_BYTE *)this + 208497);
    if ( !result )
    {
      result = *((_BYTE *)this + 209865);
      if ( !result )
      {
        result = 1;
        if ( g_Input.KeyInfo[10].PressTime == 1 )
        {
          PrevValidSlot = this->FindPrevValidSlot((int *)this + 51446);
          m_pCamera = this->m_pCamera;
          *((_DWORD *)this + 51446) = PrevValidSlot;
          return ((char ( *)(CameraCtrl *, int, int, _DWORD))m_pCamera->Viewport.x)(
                   this,
                   1001,
                   g_MonsterEntryTable[PrevValidSlot],
                   0);
        }
        if ( g_Input.KeyInfo[9].PressTime == 1 )
        {
          NextValidSlot = this->FindNextValidSlot((int *)this + 51446);
          v6 = this->m_pCamera;
          *((_DWORD *)this + 51446) = NextValidSlot;
          return ((char ( *)(CameraCtrl *, int, int, _DWORD))v6->Viewport.x)(
                   this,
                   1001,
                   g_MonsterEntryTable[NextValidSlot],
                   0);
        }
        if ( g_Input.KeyInfo[2].PressTime == 1 )
        {
          v7 = this->m_nBlendWeight - 1;
          this->m_nBlendWeight = v7;
          if ( v7 < 0 )
            this->m_nBlendWeight = 0;
          return ((char ( *)(CameraCtrl *, int, const char *, _DWORD))this->m_pCamera->Viewport.x)(
                   this,
                   1001,
                   (&off_56C548)[this->m_nBlendWeight],
                   0);
        }
        if ( g_Input.KeyInfo[3].PressTime == 1 )
        {
          v8 = this->m_nBlendWeight + 1;
          this->m_nBlendWeight = v8;
          if ( v8 > 7 )
            this->m_nBlendWeight = 7;
          return ((char ( *)(CameraCtrl *, int, const char *, _DWORD))this->m_pCamera->Viewport.x)(
                   this,
                   1001,
                   (&off_56C548)[this->m_nBlendWeight],
                   0);
        }
        if ( g_Input.KeyInfo[8].PressTime == 1 )
          return ((char ( *)(CameraCtrl *, int, _DWORD, _DWORD))this->m_pCamera->Viewport.x)(this, 1010, 0, 0);
      }
    }
  }
  return result;
}

// 0x0048EF80
int CameraCtrl::ValidateDevice(int a2, int a3)
{
  __int64 v4; // rax
  int v5; // ebx
  int m_nViewMode; // eax
  int v7; // eax
  char v8; // cl
  float *v9; // eax
  int v10; // eax
  char v11; // cl
  float *v12; // eax
  float *v13; // eax
  int v14; // eax
  int State; // eax
  DWORD TickCount; // eax
  DWORD v17; // eax
  unsigned int v18; // edx
  char m_bBlendPause; // al
  CScreenMode *Instance; // eax
  char *v22; // [esp-0x8] [ebp-0x2C]
  int v23; // [esp-0x4] [ebp-0x28]
  float *p_m_szText; // [esp-0x4] [ebp-0x28]
  int v25; // [esp+0x20] [ebp-0x4]

  v4 = (__int64)g_fGameTimer;
  v5 = (int)v4 / 3600;
  v25 = (int)v4 / 60 % 60;
  v23 = (int)v4 % 60;
  if ( (int)v4 / 3600 < 100 )
    sprintf(this->m_szCamPath, "%02d:%02d:%02d", v5, v25, v23);
  else
    sprintf(this->m_szCamPath, "%03d:%02d:%02d", v5, v25, v23);
  ((UICaption *)((char *)this + 55836))->SetEnable((int)this->m_szCamPath, 0);
  sprintf(this->m_szCamPath, &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)((char *)this + 55988))->SetEnable((int)this->m_szCamPath, 0);
  if ( this->m_bPageMode )
  {

    this->m_nViewMode = 0;
    do
    {
      m_nViewMode = this->m_nViewMode;
      if ( *(&this->m_bCamEventFlag + m_nViewMode) )
      {
        v7 = 4892 * m_nViewMode;
        v8 = *((_BYTE *)this + v7 + 213560);
        v9 = (float *)((char *)this + v7);
        if ( !v8 )
        {
          sprintf(
            this->m_szCamPath,
            "%d/%d",
            (int)v9[53389],
            Buffer.m_partyActor.m_dwMatMsg[352 * this->m_nViewMode + 9]);
          ((UICaption *)((char *)this + 4892 * this->m_nViewMode + 213644))->SetEnable((int)this->m_szCamPath, 0);
        }
        v10 = 4892 * this->m_nViewMode;
        v11 = *((_BYTE *)this + v10 + 214656);
        v12 = (float *)((char *)this + v10);
        if ( !v11 )
        {
          sprintf(
            this->m_szCamPath,
            "%d/%d",
            (int)v12[53663],
            Buffer.m_partyActor.m_dwMatMsg[352 * this->m_nViewMode + 10]);
          ((UICaption *)((char *)this + 4892 * this->m_nViewMode + 214740))->SetEnable((int)this->m_szCamPath, 0);
        }
        v13 = (float *)((char *)this + 4892 * this->m_nViewMode);
        if ( !*((_BYTE *)v13 + 214108) )
        {
          sprintf(
            this->m_szCamPath,
            "%d/%d",
            (int)v13[53526],
            Buffer.m_partyActor.m_dwMatMsg[352 * this->m_nViewMode + 11]);
          ((UICaption *)((char *)this + 4892 * this->m_nViewMode + 214192))->SetEnable((int)this->m_szCamPath, 0);
        }
        ((UIFrameWnd *)((char *)this + 52 * this->m_nViewMode + 209896))->ProcessTimer(1, 1, 2, *((_DWORD *)this + 4 * this->m_nViewMode + 52539));
      }
      v14 = this->m_nViewMode + 1;
      this->m_nViewMode = v14;
    }
    while ( v14 < 5 );
  }
  State = ((UIParabolaCtrl *)(UIParabolaCtrl *)this + 52131)->GetState();
  *((_DWORD *)this + 52473) = State;
  if ( State )
  {
    if ( State != 1 )
      goto LABEL_20;
    ((MainPropUI *)this)->SetPage(1u);
  }
  else
  {
    this->UpdateBlendWeight(*((_DWORD *)this + 51446), *(_DWORD *)&this->m_bBlendUpdate);
  }
  *((_DWORD *)this + 52473) = -1;
LABEL_20:
  if ( this->m_bBlendActive )
  {
    if ( !this->m_bTickInit )
    {
      TickCount = GetTickCount();
      this->m_nTickCount = TickCount;
      this->m_nTickStamp = TickCount;
      this->m_bTickInit = 1;
    }
    v17 = GetTickCount();
    v18 = v17 - this->m_nTickStamp;
    this->m_nTickCount = v17;
    if ( v18 > 0x1388 )
    {
      this->m_nTickStamp = v17;
      this->m_bTickInit = 0;
      m_bBlendPause = this->m_bBlendPause;
      this->m_bBlendActive = 0;
      p_m_szText = &this->m_szText;
      if ( m_bBlendPause )
      {
        sprintf(this->m_szCamPath, "\\n    %s\\n%s", (const char *)dword_DC8B3C, (const char *)p_m_szText);
        ((UICaption *)((char *)this + 206244))->SetEnable((int)this->m_szCamPath, 0);
        lstrcpyA((LPSTR)&this->m_szText, g_szSceneUIText);
        v22 = off_5C7770[0];
      }
      else
      {
        sprintf(this->m_szCamPath, "\\n    %s\\n%s", (const char *)dword_DC8C3C, (const char *)p_m_szText);
        ((UICaption *)((char *)this + 206244))->SetEnable((int)this->m_szCamPath, 0);
        lstrcpyA((LPSTR)&this->m_szText, g_szSceneUIText);
        v22 = (char *)off_5C7774;
      }
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v22, 1);
      ((UIRoleSelect *)((char *)this + 205788))->SetByte(1);
      ((MainPropUI *)this)->SetPage(1u);
      ((MagicUI *)this)->UpdateViewListItems();
      ((MagicUI *)this)->InitUILayout();
    }
  }
  return ((UIListBox *)this)->Update(a2, a3);
}

// 0x004BE8F0
CameraCtrl * CameraCtrl::_sdtor_17(CameraCtrl *Block, char a2)
{

  if ( ((unsigned __int8)Block & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004BE910
void CameraCtrl::OnIdle()
{
  CameraCtrl::_nearby_41cbc0();
}

// 0x004BEAA0
void CameraCtrl::OnIdleB()
{
  CameraCtrl::_nearby_41cbc0();
}

// 0x004BEBF0
void CameraCtrl::RenderFadeEffect()
{
  CameraCtrl::_nearby_41cbc0();
}

// 0x004BED40
void CameraCtrl::RenderFadeEffectB()
{
  CameraCtrl::_nearby_41cbc0();
}

// 0x00504510
char CameraCtrl::InitFromConfig()
{
  this->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  ((CIniFile *)this)->LoadStructuredConfig();
  return 1;
}

// 0x00504540
char CameraCtrl::InitFromScreen()
{
  _DWORD pParams[3]; // [esp+0x4] [ebp-0xC] BYREF

  this->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  this->m_pTarget = 0;
  this->m_fMinDist = 50.0;
  pParams[0] = 0;
  pParams[1] = -1018691584;
  pParams[2] = 0;
  this->InitParams(pParams);
  this->SetAsCurrent(3);
  this->m_fCamDist = 10000.0;
  ((InputSystem *)this)->InputSystem::ProcessKeyboard();
  return 1;
}

// 0x0052EBE0
void CameraCtrl::SetViewport(int nFlags)
{
  ((UILoadingFrm *)this)->CheckProgress(nFlags);
  ((CCBFiveNimbusWindow *)this)->UpdateAnimation(nFlags);
  ((UIGameOver *)this)->SetupDisplay(nFlags);
  ((UI3DCtrl *)this)->UpdateTransform(nFlags);
  ((gbCamera *)this->m_pCamera)->SetLookAt((gbVec3D *)&this->m_fMinDist, (gbVec3D *)&this->m_fTargetAngle, (gbVec3D *)&this->m_fAngleDest);
}

// 0x00533EA0
char CameraCtrl::InitDefaultView()
{
  this->SetDimention(g_DrvInfo.width, g_DrvInfo.height);
  this->m_pTarget = 0;
  this->m_fMinDist = 50.0;
  this->m_fDefaultPosY = 0.0;
  this->m_fDefaultPosZ = -200.0;
  this->m_fDefaultOffset = 0.0;
  ((RoleAtt *)this)->UpdatePosition(0.0, -200.0, 0.0);
  this->m_fViewDistance = 300.0;
  this->m_fViewPitch = -39.563057;
  this->m_fViewYaw = 302.55115;
  this->m_fDefaultPosX = -439.63275;
  ((RoleAtt *)this)->InterpolateMotion(-39.563057, 302.55115, -439.63275, 300.0, 0.0);
  this->m_fCurAngle = 50.0;
  this->m_nCamState = 1176256512;
  return 1;
}

// 0x00534DC0
int CameraCtrl::SetFOVIfValid(int nVal)
{
  int result; // eax

  result = nVal;
  if ( nVal )
    this->m_pCamera = (gbCamera *)nVal;
  return result;
}
