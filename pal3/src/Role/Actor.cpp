#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/Actor.h"

// Forward declarations for unnamed functions
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc); // from annotations
int UISceneUpdate(void); // from annotations
int sub_407790(...);
int sub_43FD90(float *_this, int a2); // from annotations
void sub_43FDB0(float *_this, int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
int sub_52FC50(int a2); // from annotations
void sub_536D20(Actor *_this, const char *a2, int a3); // from annotations
int sub_538260(...);

void Actor_CopyConstruct_1C(void *pDst, const void *pSrc); // from annotations
void Actor_CopyConstruct_40(void *pDst, const void *pSrc); // from annotations
void ActVec_Insert_char(Actor *_this, char *pszBuf, unsigned int dwVal, char *pszBuf2); // from annotations
_WORD * ActVec_Insert_word(Actor *_this, _WORD *p_WORD, unsigned int dwVal, _WORD *p_WORD2); // from annotations
unsigned int ActVec_InsertN(Actor *_this, char *pszBuf, unsigned int nX, char *nY); // from annotations
char * ActVec_InsertRange(Actor *_this, char *pszBuf, unsigned int dwVal, const void *pData); // from annotations
int * AssignInt(int *pDst, int *pSrc); // from annotations
BOOL CheckDirectoryExists(LPCSTR lpFileName); // from annotations
void CopyRoleData(int pDst, int pSrc); // from annotations
int * ctor_0x431870(int *_this); // from annotations
int GetRoleDataOffset(int nRoleIndex); // from annotations
int * LoadGameState(FILE *fp); // from annotations
struct gbVFileSystem * LoadScene(double sceneNames, char *arg8, char *pszBuf, char pData, char pData2); // from annotations
BOOL ReadRegistryString(const char *szSubKey, const char *szValueName, char *szOutBuf); // from annotations
void SaveGameState(FILE *fp); // from annotations
gbVec3D * __stdcall Vec3D_CopyStruct(gbVec3D *pDst, gbVec3D *pSrc, gbVec3D *pExtra); // from annotations

// Unnamed globals (extern)
extern char byte_17AB808[16];
extern char byte_17AFB04;
extern char byte_BFDA40;
extern char byte_BFDA41;
extern char byte_D92785;
extern int dword_17AFAE8;
extern int dword_17AFAEC;
extern int dword_17AFAF0;
extern int dword_17AFAF8;
extern int dword_17AFAFC;
extern int dword_17AFB00;
extern int dword_17B129C;
extern int dword_17B154C;
extern int dword_C10CC4;
extern int dword_C10CD4;
extern int dword_D8BC30;
extern int dword_D8BC34;
extern int dword_D8BC38;
extern int dword_DD893C;
extern int dword_DD8B3C;
extern int dword_DDAD3C;
extern float flt_17B1298;
extern float flt_17B1548;
void __cdecl nullsub_2(...);
void __cdecl nullsub_71(void);
void __cdecl nullsub_72(void);
extern const char * off_570904;
extern LPCSTR off_59DD18;
extern int off_59DD60;
extern int off_59DD70;
extern const char * off_5F50B4;
extern const char * off_5F50BC;
extern const char * off_5F50C0;
extern const char * off_5F50C4;
extern const char * off_5F50C8;
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C0A360;
extern GRPinput stru_D8C2B8;

// 0x00419690
void Actor::UpdatePhysics(float fVal)
{
  Actor *v3; // edi
  double v4; // st7
  char v6; // c0
  long double v7; // st7

  v3 = (Actor *)(&this->m_fAngleDeg + 1);
  ((Actor *)(&this->m_fAngleDeg + 1))->QueryState();
  v4 = fVal + *((float *)this + 314);
  *((float *)this + 314) = v4;
  if ( v6 )
  {
    v7 = (1.0 - cos(v4 / *((float *)this + 313) * 3.1415927)) * 0.5;
    this->m_vecTargetPos.x = *((float *)this + 341) * (1.0 - v7) + *((float *)this + 336) * v7;
    this->m_vecTargetPos.y = *((float *)this + 342) * (1.0 - v7) + *((float *)this + 337) * v7;
    this->m_vecTargetPos.z = *((float *)this + 343) * (1.0 - v7) + *((float *)this + 338) * v7;
  }
  else
  {
    this->m_vecTargetPos.x = *((float *)this + 336);
    this->m_vecTargetPos.y = *((float *)this + 337);
    this->m_vecTargetPos.z = *((float *)this + 338);
    *((_DWORD *)this + 317) = 0;
    ((Actor *)v3)->CompareActionName(0, 0);
  }
}

// 0x0041B9F0
unsigned int Actor::GetInnerAnimDuration(int animId)
{
  return ((Actor *)(&this->m_fAngleDeg + 1))->GetAnimDuration(animId);
}

// 0x0041BCA0
int Actor::SetActionByName(unsigned __int8 *pbyName)
{
  int result; // eax
  float v4; // edx

  LODWORD(this->m_fDirX) = *pbyName;
  result = *((_DWORD *)this + 317);
  if ( result != 3 )
  {
    ((RoleSystem *)this)->NotifySceneChange();
    if ( *((_DWORD *)this + 317) == 3 )
    {
      v4 = *((float *)pbyName + 1);
      this->m_vecTargetPos.x = v4;
      this->m_vecTargetPos.y = *((float *)pbyName + 2);
      this->m_vecTargetPos.z = *((float *)pbyName + 3);
      *(float *)&this->m_actarray[4] = v4;
      *(float *)&this->m_actarray[8] = this->m_vecTargetPos.y;
      *(float *)&this->m_actarray[12] = this->m_vecTargetPos.z;
      *(_DWORD *)&this->m_actarray[8] = 0;
    }
    else
    {
      ((RoleSystem *)this)->SetTargetRotation((gbVec3D *)(pbyName + 4));
    }
    result = ((RoleSystem *)this)->UpdateMovement(*((float *)pbyName + 5), 1);
    this->m_nCmdParam = *((_DWORD *)pbyName + 6);
  }
  return result;
}

// 0x0044CB30
int Actor::InitParticles()
{
  LPCSTR *v2; // ebp
  void **p_m_pParticleData; // esi
  unsigned int v4; // edi
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  _DWORD *v8; // edx
  int v9; // eax
  int v10; // ecx
  int v12; // [esp+0x10] [ebp-0x14]
  int v13; // [esp+0x14] [ebp-0x10] BYREF
  int v14; // [esp+0x18] [ebp-0xC]
  int v15; // [esp+0x1C] [ebp-0x8]
  int v16; // [esp+0x20] [ebp-0x4]

  v13 = 0;
  v14 = 0;
  v15 = 128;
  v16 = 128;
  ((RoleSystem *)this)->InitDefaultPositions();
  v2 = &off_59DD18;
  p_m_pParticleData = &this->m_pParticleData;
  do
  {
    (*((void ( **)(void **, _DWORD, int *, Actor *))*p_m_pParticleData + 4))(p_m_pParticleData, 0, &v13, this);
    if ( (int)v2 < (int)&off_59DD60 )
    {
      ((UIStatic *)p_m_pParticleData)->CreateFromTemplate();
    }
    else
    {
      v4 = rand() % 0x12u;
      ((UIStatic *)p_m_pParticleData)->CreateFromTemplate();
      p_m_pParticleData[43] = (void *)*((_DWORD *)&this->m_bDirFlag + 52 * v4);
      p_m_pParticleData[44] = (void *)*((_DWORD *)&this->m_bDirFlag + 52 * v4 + 1);
    }
    *((float *)p_m_pParticleData + 46) = (float)(rand() % 255);
    ++v2;
    v5 = rand() % 10;
    v6 = v13;
    v7 = v14;
    v12 = v5 + 10;
    v8 = p_m_pParticleData + 38;
    p_m_pParticleData += 52;
    *((float *)p_m_pParticleData - 5) = (double)v12 * 0.1;
    *((_BYTE *)p_m_pParticleData - 16) = 1;
    *v8 = v6;
    v9 = v15;
    v8[1] = v7;
    v10 = v16;
    v8[2] = v9;
    v8[3] = v10;
  }
  while ( (int)v2 < (int)&off_59DD70 );
  return ((RoleCamera *)this)->InitParticles();
}

// 0x00456EE0
int Actor::ApplyStateArray()
{
  int v2; // esi
  void **p_m_pParticleData; // edi
  int result; // eax

  v2 = 0;
  p_m_pParticleData = &this->m_pParticleData;
  do
  {
    result = (*(int ( **)(void **, _DWORD))*p_m_pParticleData)(p_m_pParticleData, g_bStateFlags[v2++]);
    p_m_pParticleData += 94;
  }
  while ( v2 < 52 );
  return result;
}

// 0x00456F10
char * Actor::SaveState()
{
  char *result; // eax
  int v2; // eax
  int i; // ecx
  int v4; // esi
  int v5; // eax
  int v6; // ecx
  BYTE Data[4]; // [esp+0x8] [ebp-0x8] BYREF
  BYTE v8[4]; // [esp+0xC] [ebp-0x4] BYREF

  memset(g_bStateFlags, 0, 0x34u);
  *(_DWORD *)Data = 0;
  *(_DWORD *)v8 = 0;
  result = (char *)ReadRegistryString(szSubKey, szValueName, (char *)Data);
  if ( (_BYTE)result )
  {
    result = (char *)ReadRegistryString(szSubKey, "MOVIE_B", (char *)v8);
    if ( (_BYTE)result )
    {
      v2 = *(_DWORD *)Data;
      for ( i = 0; i < 32; ++i )
        g_bStateFlags[i] = ((1 << i) & v2) != 0;
      v4 = *(_DWORD *)v8;
      v5 = i;
      v6 = 0;
      result = (char *)&g_bStateFlags[v5];
      do
      {
        *result++ = ((1 << v6) & v4) != 0;
        if ( (int)result >= (int)&g_bListNeedsRefresh )
          break;
        ++v6;
      }
      while ( v6 < 32 );
    }
  }
  return result;
}

// 0x0050ACF0
unsigned int Actor::GetAnimDurationByIndex(int nVal)
{
  unsigned int result; // eax

  result = nVal;
  if ( nVal > 0 )
  {
    sprintf(byte_17AB808, "z%02d", nVal);
    return ((Actor *)*(Actor **)&this->m_szTexture[12])->GetAnimDuration((int)byte_17AB808);
  }
  return result;
}

// 0x005309A0
int Actor::ResetTransformState()
{
  int v2; // eax
  int v3; // ecx
  float v4; // edx
  double v5; // st7
  double v6; // st7
  int v7; // eax
  int v9; // et2
  int v10; // [esp+0xC] [ebp-0x8]
  float v11; // [esp+0x10] [ebp-0x4]

  v2 = ((ArcSceneMonster *)&this->m_dwMatMsg[6])->CheckDistance(0.0);
  v10 = *(_DWORD *)(v2 + 4);
  v3 = *(_DWORD *)(v2 + 8);
  *(_DWORD *)&this->m_curact[11] = *(_DWORD *)v2;
  *(_DWORD *)&this->m_curact[15] = v10;
  *(_DWORD *)&this->m_curact[19] = v3;
  *(_DWORD *)&this->m_bChangedMat = *(_DWORD *)&this->m_curact[11];
  *(_DWORD *)&this->m_curact[3] = *(_DWORD *)&this->m_curact[15];
  *(_DWORD *)&this->m_curact[7] = *(_DWORD *)&this->m_curact[19];
  *(_DWORD *)&this->m_curact[23] = 0;
  *(_DWORD *)&this->m_curact[27] = 0;
  *(_DWORD *)&this->m_curact[31] = 0;
  *(_DWORD *)&this->m_curact[35] = 0;
  *(_DWORD *)&this->m_curact[39] = *(_DWORD *)&this->m_curact[27];
  *(_DWORD *)&this->m_curact[43] = *(_DWORD *)&this->m_curact[31];
  v4 = *(float *)(v2 + 4);
  v11 = *(float *)(v2 + 8);
  this->m_fDirX = *(float *)v2;
  this->m_fDirY = v4;
  this->m_fDirZ = v11;
  this->m_fNormX = 0.0;
  this->m_fNormY = 0.0;
  this->m_fNormZ = -0.001;
  this->m_fDistAccum = 0.0;
  *((_DWORD *)&this->m_fSpeed + 2) = 1093517967;
  *((_DWORD *)&this->m_fSpeed + 3) = 1105649992;
  this->m_fSpeed = 10.86;
  *((_DWORD *)&this->m_fSpeed + 1) = 1093517967;
  this->m_fAngleDeg = 0.0;
  *((_DWORD *)&this->m_fAngleDeg + 1) = 0;
  this->m_nUpdateMode = 0;
  *(&this->m_nUpdateMode + 1) = 0;
  ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)lpString2);
  lstrcpyA((LPSTR)&this->m_fMatrixC, lpString2);
  v5 = this->m_fBlendWeight * 0.33333334;
  *(&this->m_bDirFlag + 21) = 0;
  *(&this->m_bDirFlag + 22) = 0;
  this->m_bDirFlag = 0;
  *((_DWORD *)&this->m_bDirFlag + 1) = 0;
  *(&this->m_bDirFlag + 1) = 1;
  *((_BYTE *)&this->m_nAnimCounter + 46) = 0;
  *((_DWORD *)&this->m_bDirFlag + 6) = 1145241600;
  *((_DWORD *)&this->m_bDirFlag + 7) = 1119092736;
  *((_DWORD *)&this->m_bDirFlag + 8) = -1033895936;
  *((_DWORD *)&this->m_bDirFlag + 9) = 1104150528;
  v6 = v5 + this->m_fBlendWeight;
  *(&this->m_nUpdateMode + 5) = 0;
  *(&this->m_nUpdateMode + 6) = 1086324736;
  *(&this->m_nUpdateMode + 7) = 1086324736;
  *(&this->m_nUpdateMode + 8) = 1022739087;
  *((_DWORD *)this + 205) = 0;
  *((float *)&this->m_nUpdateMode + 4) = v6;
  *((_BYTE *)&this->m_nUpdateMode + 14) = 1;
  *((_BYTE *)&this->m_nUpdateMode + 15) = 1;
  *(&this->m_nUpdateMode + 2) = 1039516303;
  *((_BYTE *)&this->m_nUpdateMode + 13) = 1;
  *((_BYTE *)&this->m_nAnimCounter + 44) = 0;
  v7 = rand();
  this->m_bStateFlag = 0;
  v9 = v7 % 2600;
  *((_BYTE *)&this->m_nAnimCounter + 45) = 0;
  *(&this->m_nAnimCounter + 4) = v9;
  return v7 / 2600;
}

// 0x00530C00
bool Actor::UpdateAnimState(char pData)
{
  unsigned int v3; // ecx
  RoleSystem *v4; // ecx

  ((UIAnimateCtrlEX *)this)->SwapBuffer(3);
  ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)lpString2);
  v3 = this->m_dwMatMsg[10];
  *((_BYTE *)&this->m_nAnimCounter + 45) = pData;
  ((ScreenEffectMgr *)*(ScreenEffectMgr **)(v3 + 1312))->ProcessInstance();
  v4 = (RoleSystem *)this->m_dwMatMsg[10];
  *(&this->m_bDirFlag + 21) = 1;
  ((RoleSystem *)v4)->StopBlinkUI();
  *(_BYTE *)(this->m_dwMatMsg[10] + 4524) = 1;
  *((_BYTE *)&this->m_nAnimCounter + 46) = pData == 0;
  return pData == 0;
}

// 0x00530F20
bool Actor::GetBoundRadius()
{
  char *m_pRoleState; // ecx
  gbOBBox *OBBox; // eax
  long double v5; // [esp+0x0] [ebp-0x8]

  m_pRoleState = this->m_pRoleState;
  v5 = fabs(this->m_fDistAccum - *((float *)m_pRoleState + 932));
  OBBox = ((MiniGame2Scene *)m_pRoleState)->GetOBBox();
  return ((gbOBBox *)OBBox)->GetRadius() > v5;
}

// 0x00530F70
void Actor::BlendAnimation(float fVal)
{
  double v3; // st7
  double v4; // st7
  Actor *v5; // ecx
  double v6; // st7
  float v7; // edx

  if ( !*((_BYTE *)&this->m_nUpdateMode + 13) )
  {
    v3 = fVal * *((float *)&this->m_nUpdateMode + 2);
    if ( *((_BYTE *)&this->m_nUpdateMode + 12) )
    {
      v4 = this->m_fSpeed - v3;
      this->m_fSpeed = v4;
      if ( v4 <= 0.0 )
      {
        v5 = *(Actor **)this->m_actarray;
        *((_BYTE *)&this->m_nUpdateMode + 12) = 0;
        ((Actor *)v5)->SetMaterialName((void *)off_5F50B4);
        ((UIAnimateCtrlEX *)this)->SwapBuffer(0);
      }
    }
    else
    {
      v6 = v3 + this->m_fSpeed;
      this->m_fSpeed = v6;
      if ( v6 >= *(&this->m_fSpeed + 2) )
      {
        v7 = *(&this->m_fSpeed + 2);
        *((_BYTE *)&this->m_nUpdateMode + 12) = 1;
        this->m_fSpeed = v7;
        *((_BYTE *)&this->m_nUpdateMode + 13) = 1;
      }
      *((_BYTE *)&this->m_nUpdateMode + 15) = 1;
    }
  }
}

// 0x00531260
void Actor::UpdateFrame(float arg0)
{
  unsigned int m_nAnimCounter; // eax
  float *v4; // eax
  double v5; // st7
  float *p_m_fDirX; // ebx
  double v7; // st6
  float v8; // ecx
  double v9; // st7
  double v10; // st7
  float m_fDirZ; // ecx
  double v12; // st7
  float v13; // ecx
  double v14; // st7
  float v15; // edx
  float v16; // ecx
  double v17; // st7
  double v18; // st7
  long double v19; // st7
  int v20; // esi
  int m_nUpdateMode; // eax
  float v22; // eax
  unsigned int v23; // edi
  DWORD TickCount; // eax
  DWORD v25; // eax
  unsigned int v26; // edx
  int v27; // edx
  int v28; // edx
  CHAR *v29; // edx
  double v30; // st7
  gbOBBox *SlotA; // eax
  double v32; // st7
  int v33; // ecx
  bool v34; // zf
  double v35; // st7
  gbOBBox *v36; // eax
  Actor *v37; // ecx
  int v38; // esi
  gbOBBox *SlotB; // eax
  int v40; // eax
  unsigned int v41; // eax
  DWORD v42; // eax
  DWORD v43; // eax
  unsigned int v44; // ecx
  int v45; // eax
  int msg; // [esp+0x0] [ebp-0x9C]
  float v47; // [esp+0x4] [ebp-0x98]
  int nVal; // [esp+0x1C] [ebp-0x80]
  gbVec3D v49; // [esp+0x20] [ebp-0x7C] BYREF
  gbVec3D v50; // [esp+0x2C] [ebp-0x70] BYREF
  int p_DWORD; // [esp+0x38] [ebp-0x64] BYREF
  float v52; // [esp+0x3C] [ebp-0x60]
  float v53; // [esp+0x40] [ebp-0x5C]
  float m_fDirX; // [esp+0x44] [ebp-0x58]
  float m_fDirY; // [esp+0x48] [ebp-0x54]
  float v56; // [esp+0x4C] [ebp-0x50]
  float v57[19]; // [esp+0x50] [ebp-0x4C] BYREF

  m_nAnimCounter = this->m_nAnimCounter;
  if ( m_nAnimCounter <= 2 )
  {
    this->m_nAnimCounter = m_nAnimCounter + 1;
  }
  else if ( !*(_BYTE *)(this->m_dwMatMsg[10] + 7276) )
  {
    return;
  }
  switch ( this->m_nUpdateMode )
  {
    case 1:
      this->BlendAnimation(arg0);
      break;
    case 2:
      ((RoleAtt *)this)->ApplySpeedFactor(arg0);
      break;
    case 3:
      ((RoleAtt *)this)->UpdateTimedBuff(arg0);
      break;
  }
  if ( this->m_bStateFlag )
  {
    ((Actor *)*(Actor **)this->m_actarray)->QueryState();
    return;
  }
  v4 = (float *)((ArcSceneMonster *)&this->m_dwMatMsg[6])->CheckDistance(this->m_fDistAccum);
  if ( !v4 )
  {
    this->m_bDirFlag = 0;
    ((s_RoleState *)this->m_pRoleState)->CopyRoleData(0, 0);
    this->m_bStateFlag = 1;
    this->UpdateAnimState(0);
    return;
  }
  v5 = *v4 - this->m_fDirX;
  p_m_fDirX = &this->m_fDirX;
  m_fDirY = v4[1] - this->m_fDirY;
  v7 = v4[2] - this->m_fDirZ;
  this->m_fNormY = m_fDirY;
  v56 = v7;
  v8 = v56;
  this->m_fNormX = v5;
  this->m_fNormZ = v8;
  ((gbVec3D *)&this->m_fNormX)->Normalize();
  v9 = arg0 * this->m_fSpeed;
  *(_DWORD *)&this->m_bChangedMat = *(_DWORD *)&this->m_curact[11];
  *(_DWORD *)&this->m_curact[3] = *(_DWORD *)&this->m_curact[15];
  v10 = v9 * this->m_fNormX;
  *(_DWORD *)&this->m_curact[7] = *(_DWORD *)&this->m_curact[19];
  *(float *)&this->m_curact[11] = this->m_fDirX;
  m_fDirZ = this->m_fDirZ;
  *(float *)&this->m_curact[15] = this->m_fDirY;
  *(float *)&this->m_curact[19] = m_fDirZ;
  v12 = v10 + this->m_fDirX;
  p_DWORD = *(int *)&this->m_curact[11];
  v13 = *(float *)&this->m_curact[15];
  this->m_fDirX = v12;
  v14 = this->m_fNormY * this->m_fSpeed;
  v15 = *(float *)&this->m_curact[19];
  v52 = v13;
  v53 = v15;
  this->m_fDirY = v14 * arg0 + this->m_fDirY;
  this->m_fDirZ = this->m_fNormZ * this->m_fSpeed * arg0 + this->m_fDirZ;
  m_fDirX = this->m_fDirX;
  v16 = this->m_fDirZ;
  m_fDirY = this->m_fDirY;
  v56 = v16;
  this->m_fDistAccum = sqrt(
                         (v52 - m_fDirY) * (v52 - m_fDirY)
                       + (v53 - v16) * (v53 - v16)
                       + (*(float *)&p_DWORD - m_fDirX) * (*(float *)&p_DWORD - m_fDirX))
                     + this->m_fDistAccum;
  m_fDirX = this->m_fDirX - *(float *)&this->m_curact[11];
  v17 = this->m_fDirY - *(float *)&this->m_curact[15];
  v50.x = m_fDirX;
  m_fDirY = v17;
  v18 = this->m_fDirZ - *(float *)&this->m_curact[19];
  v50.y = m_fDirY;
  v56 = v18;
  v50.z = v56;
  ((gbVec3D *)&v50)->Normalize();
  v49 = v50;
  ((gbVec3D *)&v49)->Normalize();
  if ( (byte_17AFB04 & 1) == 0 )
  {
    dword_17AFAF8 = 0;
    byte_17AFB04 |= 1u;
    dword_17AFAFC = 0;
    dword_17AFB00 = 1065353216;
    atexit(nullsub_72);
  }
  v19 = acos(v49.z * *(float *)&dword_17AFB00 + v49.y * *(float *)&dword_17AFAFC + *(float *)&dword_17AFAF8 * v49.x);
  this->m_fAngleDeg = v19;
  if ( v49.x < 0.0 )
    this->m_fAngleDeg = 6.2831855 - v19;
  this->m_fAngleDeg = this->m_fAngleDeg * 57.29578;
  if ( (byte_17AFB04 & 2) == 0 )
  {
    dword_17AFAE8 = 0;
    byte_17AFB04 |= 2u;
    dword_17AFAEC = 1065353216;
    dword_17AFAF0 = 0;
    atexit(nullsub_71);
  }
  *(&this->m_fAngleDeg + 1) = acos(
                                v49.z * *(float *)&dword_17AFAF0
                              + v49.y * *(float *)&dword_17AFAEC
                              + *(float *)&dword_17AFAE8 * v49.x)
                            * 57.29578;
  m_fDirX = *p_m_fDirX;
  m_fDirY = this->m_fDirY + 200.0;
  v56 = this->m_fDirZ;
  ((RoleCameraCtrl *)this->m_dwMatMsg[9])->ComputeViewVector(SLODWORD(m_fDirX), SLODWORD(m_fDirY), SLODWORD(v56));
  m_fDirX = *p_m_fDirX;
  v20 = 0;
  m_fDirY = this->m_fDirY + 200.0;
  v56 = this->m_fDirZ;
  ((RoleCameraCtrl *)this->m_dwMatMsg[9])->SetViewPosition(SLODWORD(m_fDirX), SLODWORD(m_fDirY), SLODWORD(v56), 0);
  ((UIScene *)this->m_dwMatMsg[9])->LoadMapData();
  *(float *)&msg = *((float *)&this->m_bDirFlag + 7) - (this->m_fAngleDeg - 90.0);
  ((UIBigMap *)this->m_dwMatMsg[9])->SetBounds(msg, *((_DWORD *)&this->m_bDirFlag + 8), 0);
  m_nUpdateMode = this->m_nUpdateMode;
  if ( m_nUpdateMode != 1 && m_nUpdateMode != 3 && m_nUpdateMode != 2 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
  {
    v22 = this->m_fDirY;
    *(&this->m_nUpdateMode + 6) = *(&this->m_nUpdateMode + 7);
    *((_BYTE *)&this->m_nUpdateMode + 15) = 0;
    *((float *)this + 205) = v22;
    *((_BYTE *)&this->m_nUpdateMode + 14) = 1;
    *(&this->m_nUpdateMode + 5) = 0;
    ((UIAnimateCtrlEX *)this)->SwapBuffer(2);
    ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)off_5F50C0);
  }
  if ( *(&this->m_nUpdateMode + 1) == 2 )
  {
    if ( ((Object3D *)*(Object3D **)this->m_actarray)->GetVisNode() )
    {
      ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)off_5F50C4);
      *(&this->m_nUpdateMode + 1) = 0;
    }
    if ( *(&this->m_nUpdateMode + 1) == 2 && ((Object3D *)*(Object3D **)this->m_actarray)->GetVisNode() )
    {
      *(&this->m_nUpdateMode + 1) = 0;
      ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)lpString2);
    }
  }
  if ( !*(&this->m_nUpdateMode + 1) && ((Object3D *)*(Object3D **)this->m_actarray)->GetVisNode() )
  {
    v23 = *(&this->m_nAnimCounter + 4);
    if ( !*((_BYTE *)&this->m_nAnimCounter + 28) )
    {
      TickCount = GetTickCount();
      *(&this->m_nAnimCounter + 5) = TickCount;
      *(&this->m_nAnimCounter + 6) = TickCount;
      *((_BYTE *)&this->m_nAnimCounter + 28) = 1;
    }
    v25 = GetTickCount();
    v26 = v25 - *(&this->m_nAnimCounter + 6);
    *(&this->m_nAnimCounter + 5) = v25;
    if ( v26 <= v23 )
    {
      v29 = (CHAR *)lpString2;
    }
    else
    {
      *(&this->m_nAnimCounter + 6) = v25;
      *((_BYTE *)&this->m_nAnimCounter + 28) = 0;
      *(&this->m_nAnimCounter + 4) = rand() % 2600 + 1000;
      v27 = rand() % 300 / 10 / 10;
      if ( !v27 )
      {
        ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)lpString2);
        goto LABEL_45;
      }
      v28 = v27 - 1;
      if ( !v28 )
      {
        ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)off_5F50BC);
        goto LABEL_45;
      }
      if ( v28 != 1 )
        goto LABEL_45;
      v29 = (CHAR *)off_5F50C4;
    }
    ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName(v29);
  }
LABEL_45:
  if ( !this->m_nUpdateMode )
  {
    if ( this->m_bDirFlag )
    {
      if ( g_Input.KeyInfo[0].PressTime == 1 )
      {
        v30 = this->m_fSpeed + 0.2;
        this->m_fSpeed = v30;
        if ( v30 >= *(&this->m_fSpeed + 3) )
          this->m_fSpeed = *(&this->m_fSpeed + 3);
      }
    }
  }
  if ( *(&this->m_nUpdateMode + 1) == 1 )
  {
    if ( ((Object3D *)*(Object3D **)this->m_actarray)->GetVisNode() )
    {
      *(&this->m_nUpdateMode + 1) = 0;
      ((Actor *)*(Actor **)this->m_actarray)->SetMaterialName((void *)lpString2);
    }
    ((Actor *)*(Actor **)this->m_actarray)->PlayAction((int)&this->m_obbox);
    this->m_fAnimDelta = this->m_fAnimDelta + *p_m_fDirX;
    *(float *)this->m_dwMatMsg = this->m_fDirY + *(float *)this->m_dwMatMsg;
    *(float *)&this->m_dwMatMsg[1] = this->m_fDirZ + *(float *)&this->m_dwMatMsg[1];
    while ( 1 )
    {
      SlotA = (gbOBBox *)((CCBFiveNimbusWindow *)this->m_pRoleState)->GetSlotA(v20);
      if ( ((gbOBBox *)&this->m_obbox)->IsColOBB(SlotA) )
        break;
      if ( ++v20 >= 6 )
        goto LABEL_62;
    }
    qmemcpy(
      v57,
      (const void *)((CCBFiveNimbusWindow *)this->m_pRoleState)->GetSlotA(v20),
      sizeof(v57));
    v32 = v57[16];
    if ( v57[17] > (double)v57[16] )
      v32 = v57[17];
    if ( v57[18] > v32 )
      v32 = v57[18];
    *(float *)&nVal = v32 + v32 + this->m_fDistAccum;
    this->m_fDistAccum = *(float *)&nVal;
    ((RoleAtt *)this)->InterpolateStats(nVal);
LABEL_62:
    v20 = 0;
  }
  v33 = this->m_nUpdateMode;
  if ( v33 != 1 )
  {
    if ( v33 != 3 && this->m_fSpeed < (double)*(&this->m_fSpeed + 2) )
      this->m_fSpeed = *((float *)&this->m_nUpdateMode + 2) + this->m_fSpeed;
    if ( v33 != 3 )
    {
      ((Actor *)*(Actor **)this->m_actarray)->PlayAction((int)&this->m_obbox);
      v34 = this->m_nUpdateMode == 2;
      this->m_fAnimDelta = this->m_fAnimDelta + *p_m_fDirX;
      if ( v34 )
        v35 = *((float *)this + 205);
      else
        v35 = this->m_fDirY;
      *(float *)this->m_dwMatMsg = v35 + *(float *)this->m_dwMatMsg;
      *(float *)&this->m_dwMatMsg[1] = this->m_fDirZ + *(float *)&this->m_dwMatMsg[1];
      while ( 1 )
      {
        v36 = (gbOBBox *)((CCBFiveNimbusWindow *)this->m_pRoleState)->GetSlotA(v20);
        if ( ((gbOBBox *)&this->m_obbox)->IsColOBB(v36) )
          break;
        if ( ++v20 >= 6 )
          goto LABEL_76;
      }
      ((UIAnimateCtrlEX *)this)->SwapBuffer(1);
      v37 = *(Actor **)this->m_actarray;
      *((_BYTE *)&this->m_nUpdateMode + 13) = 0;
      *((_BYTE *)&this->m_nUpdateMode + 12) = 1;
      ((Actor *)v37)->SetMaterialName((void *)off_5F50C8);
LABEL_76:
      v38 = 0;
      while ( 1 )
      {
        SlotB = (gbOBBox *)((CCBFiveNimbusWindow *)this->m_pRoleState)->GetSlotB(v38);
        if ( ((gbOBBox *)&this->m_obbox)->IsColOBB(SlotB) )
          break;
        if ( ++v38 >= 3 )
          goto LABEL_82;
      }
      p_DWORD = 0xFFFF;
      v52 = 0.0;
      v53 = 0.0;
      *(float *)&p_DWORD = COERCE_FLOAT(sub_52FC50(v38));
      v53 = COERCE_FLOAT(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(p_DWORD));
      LODWORD(v52) = 1;
      if ( !((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD) )
      {
        this->m_pRoleState[v38 + 3328] = 0;
        v40 = sub_52FC50(v38);
        ((CCBFiveNimbusWindow *)this)->ApplySelection(v40);
      }
    }
  }
LABEL_82:
  if ( this->GetBoundRadius() && this->m_bDirFlag )
  {
    this->m_bStateFlag = 1;
    this->UpdateAnimState(1);
  }
  ((Actor *)*(Actor **)this->m_actarray)->QueryState();
  if ( this->m_bDirFlag )
  {
    if ( *(&this->m_bDirFlag + 1) )
    {
      if ( !*(&this->m_bDirFlag + 16) )
      {
        v42 = GetTickCount();
        *((_DWORD *)&this->m_bDirFlag + 2) = v42;
        *((_DWORD *)&this->m_bDirFlag + 3) = v42;
        *(&this->m_bDirFlag + 16) = 1;
      }
      v43 = GetTickCount();
      v44 = v43 - *((_DWORD *)&this->m_bDirFlag + 3);
      *((_DWORD *)&this->m_bDirFlag + 2) = v43;
      if ( v44 > 0x12C )
      {
        *((_DWORD *)&this->m_bDirFlag + 3) = v43;
        *(&this->m_bDirFlag + 16) = 0;
        v47 = *((float *)&this->m_bDirFlag + 1);
        *(&this->m_bDirFlag + 1) = 0;
        v45 = ((ArcSceneMonster *)&this->m_dwMatMsg[6])->ValidateRange(v47);
        ((s_RoleState *)this->m_pRoleState)->CopyRoleData(v45, 1);
      }
    }
  }
  else if ( *(float *)&this->m_dwMatMsg[8] * 0.5 <= this->m_fDistAccum )
  {
    this->m_bDirFlag = 1;
    *((_DWORD *)&this->m_bDirFlag + 1) = LODWORD(this->m_fDistAccum);
    v41 = this->m_dwMatMsg[9];
    *(_DWORD *)(v41 + 168) = 1117782016;
    *(_DWORD *)(v41 + 172) = 0;
    *(_DWORD *)(v41 + 176) = 0;
    *(_DWORD *)(v41 + 180) = 0;
    *(_DWORD *)(v41 + 220) = 2600;
    *(_DWORD *)(v41 + 196) = 0;
    *(_DWORD *)(v41 + 192) = 0;
    *(_DWORD *)(v41 + 188) = 0;
    *(_DWORD *)(v41 + 184) = 0;
    *(_BYTE *)(v41 + 216) = 1;
    *(_BYTE *)(v41 + 217) = 0;
    *(_BYTE *)(v41 + 224) = 0;
    ((RoleSystem *)this->m_dwMatMsg[10])->StartBlinkUI();
  }
}

// 0x00536160
int Actor::SetParam(int nVal)
{
  int v3; // eax
  int result; // eax
  int v5; // ecx
  int v6; // ecx
  float v7[17]; // [esp+0x4] [ebp-0x44] BYREF

  if ( this->m_fScale )
  {
    v3 = rand();
    ((Actor *)*(Actor **)&this->m_fMatrixB)->SetActorAction(-83 - v3 % 34);
    this->m_bParamFlag = 1;
  }
  ((gbGeomNode *)*(gbGeomNode **)this->m_actarray)->GetTotalOBBox((gbOBBox *)&this->m_actarray[12]);
  ((ArcLocaleRole *)this->m_actarray)->TransformPoint(v7, this->m_vecTargetPos.z, this->m_fInterpStart, this->m_fInterpEnd);
  result = (*(int ( **)(_DWORD))(**(_DWORD **)this->m_actarray + 20))(*(_DWORD *)this->m_actarray);
  v5 = *(_DWORD *)&this->m_actarray[4];
  if ( v5 )
    result = (*(int ( **)(int))(*(_DWORD *)v5 + 20))(v5);
  v6 = *(_DWORD *)&this->m_actarray[8];
  if ( v6 )
    return (*(int ( **)(int))(*(_DWORD *)v6 + 20))(v6);
  return result;
}

// 0x00536220
// attributes: thunk
int Actor::GetDefaultFOV_thunk()
{
  return this->SetDefaultFOV();
}

// 0x00536230
int Actor::SetDefaultFOV()
{
  dword_17B129C = 1094713344;
  return 1094713344;
}

// 0x00536240
// attributes: thunk
int Actor::GetDefaultDist_thunk()
{
  int result; // eax

  return result;
}

// 0x00536250
void Actor::SetDefaultDist()
{
  flt_17B1298 = 12.0 + 12.0;
}

// 0x00536310
void Actor::DestroyInternalData()
{
  ((UIFrameWnd *)((char *)this + 3340))->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)(UIButton *)this + 9)->_UIButton();
  ((UIRoleDialog *)((char *)this + 1728))->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_nHandleEvent)->_UIRoleDialog();
  ((UIListBox *)this)->_UIListBox();
}

// 0x005363A0
int Actor::ResetDefaultState()
{
  this->m_nActionState = 0;
  this->m_nActionType = 0;
  this->m_bActionFlag1 = 0;
  return 0;
}

// 0x005363E0
void Actor::SetActorAction(int actionId)
{
  int m_nHP; // eax
  int v4; // eax
  float fValue; // [esp+0x8] [ebp-0xC]
  float fValuea; // [esp+0x8] [ebp-0xC]

  if ( this->m_nActionResult )
  {
    m_nHP = this->m_nHP;
    if ( m_nHP )
    {
      v4 = actionId + m_nHP;
      this->m_nActionResult = 0;
      this->m_nHP = v4;
      if ( v4 <= 0 )
      {
        (**((void ( ***)(char *, _DWORD))this + 774))((char *)this + 3096, 0);
        (**((void ( ***)(char *, _DWORD))this + 835))((char *)this + 3340, 0);
        sprintf(
          (char *const)&this->m_pRoleParam3,
          "       %s\\n       %s",
          (const char *)dword_DD893C,
          (const char *)dword_DD8B3C);
        ((UICaption *)(&this->m_nUpdateMode + 8))->SetEnable((int)&this->m_pRoleParam3, 0);
        ((UIRoleSelect *)&this->m_nHandleEvent)->SetByte(1);
        this->m_nHP = 0;
      }
      fValue = (float)this->m_nMaxHP;
      ((UIScrollBar *)((char *)this + 3096))->SetRange(fValue);
      fValuea = (float)this->m_nHP;
      ((UIProgressBar *)((char *)this + 3096))->FindChildByName(fValuea);
      this->m_nActionType = 1;
    }
  }
}

// 0x005364B0
int Actor::InitActorComponents()
{
  int m_nHP; // eax
  void ( **v3)(char *, bool); // edx
  float fValue; // [esp+0x0] [ebp-0xC]
  float fValuea; // [esp+0x0] [ebp-0xC]

  this->m_bInitialized = 0;
  ((UICaption *)((char *)this + 2184))->SetEnable((int)dword_DDAD3C, 0);
  ((UIRoleSelect *)((char *)this + 1728))->SetByte(1);
  this->m_nHP = 1000;
  this->m_nMaxHP = 1000;
  ((UIListBox *)((char *)this + 3096))->GetCurSel();
  fValue = (float)this->m_nMaxHP;
  ((UIScrollBar *)((char *)this + 3096))->SetRange(fValue);
  fValuea = (float)this->m_nHP;
  ((UIProgressBar *)((char *)this + 3096))->FindChildByName(fValuea);
  m_nHP = this->m_nHP;
  v3 = (void ( **)(char *, bool))*((_DWORD *)this + 774);
  this->m_bHPVisible = m_nHP <= 0;
  (*v3)((char *)this + 3096, m_nHP > 0);
  return (**((int ( ***)(char *, bool))this + 835))((char *)this + 3340, this->m_nHP > 0);
}

// 0x00536560
char Actor::ProcessActorFrame()
{
  _BYTE *v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  RoleAtt *v6; // edx
  RoleAtt *v7; // ecx
  RoleAtt *v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  float fValue; // [esp+0xC] [ebp-0x58]
  float fValuea; // [esp+0xC] [ebp-0x58]
  int v15; // [esp+0x24] [ebp-0x40] BYREF
  int v16; // [esp+0x28] [ebp-0x3C]
  int v17; // [esp+0x2C] [ebp-0x38]
  int v18; // [esp+0x30] [ebp-0x34]
  _DWORD v19[4]; // [esp+0x34] [ebp-0x30] BYREF
  int nVal[4]; // [esp+0x44] [ebp-0x20] BYREF
  int v21[4]; // [esp+0x54] [ebp-0x10] BYREF

  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, 800, 600, 0);
  v2 = operator new(0xCu);
  if ( v2 )
  {
    v2[8] = 0;
    *((_DWORD *)v2 + 1) = 0;
    *(_DWORD *)v2 = 0;
  }
  else
  {
    v2 = 0;
  }
  this->m_nActionState = (int)v2;
  this->m_nHP = 1000;
  this->m_nMaxHP = 1000;
  v3 = *((_DWORD *)this + 774);
  this->m_bActionFlag3 = -58;
  this->m_bActionFlag2 = 116;
  this->m_nActionParam = 36;
  v16 = 310;
  v15 = 350;
  v17 = 440;
  v18 = 322;
  (*(void ( **)(char *, int, int *, Actor *))(v3 + 16))((char *)this + 3096, -5570049, &v15, this);
  ((UIScene *)(UIScene *)this + 9)->GetChildCount();
  ((UIScene *)(UIScene *)this + 9)->GetChildAt();
  sub_43FD90((float *)this + 774, 2);
  ((UIWnd *)((char *)this + 3096))->GetWidth(2);
  sub_43FDB0((float *)this + 774, 2);
  ((UIWnd *)((char *)this + 3096))->GetHeight(2);
  ((UIWnd *)((char *)this + 3096))->GetPosition(1);
  *((_DWORD *)this + 827) = 1;
  fValue = (float)this->m_nMaxHP;
  ((UIScrollBar *)((char *)this + 3096))->SetRange(fValue);
  fValuea = (float)this->m_nHP;
  ((UIProgressBar *)((char *)this + 3096))->FindChildByName(fValuea);
  v4 = v17;
  v19[0] = v15;
  v5 = v16;
  *((_DWORD *)this + 834) = 400;
  v19[1] = v5 - 26;
  v19[2] = v4;
  *((_DWORD *)this + 832) = 1101004800;
  *((_DWORD *)this + 829) = 255;
  v19[3] = v5 - 26 + 32;
  (*(void ( **)(char *, int, _DWORD *, Actor *))(*((_DWORD *)this + 835) + 16))(
    (char *)this + 3340,
    -5570049,
    v19,
    this);
  ((UIScene *)((char *)this + 3340))->SetShow(0);
  sub_446010((char *)this + 3340);
  nVal[1] = 250;
  nVal[0] = 300;
  nVal[2] = 500;
  nVal[3] = 370;
  ((ARC_PlayerAtt *)&this->m_nHandleEvent)->Create(-5569793, (int)nVal);
  v6 = (RoleAtt *)(this->m_nTransitionParam + 22);
  this->m_pEquipAtt1[2] = (RoleAtt *)(this->m_nAnimFrames + 6);
  v7 = this->m_pEquipAtt1[1];
  this->m_pEquipAtt2[0] = v6;
  v8 = (RoleAtt *)((char *)this->m_pEquipAtt1[0] - 6);
  this->m_pEquipAtt2[2] = (RoleAtt *)((char *)v7 - 38);
  *((_DWORD *)this + 426) = 0;
  *((_DWORD *)this + 427) = 16;
  this->m_pEquipAtt2[1] = v8;
  sub_445FA0(&this->m_nUpdateMode + 8);
  ((UIItem *)&this->m_nHandleEvent)->SetData(31);
  this->m_bHPVisible = 0;
  this->m_nActionResult = 1;
  this->m_bInitialized = 0;
  v21[1] = 200;
  v21[0] = 250;
  v21[2] = 550;
  v21[3] = 328;
  ((ARC_PlayerAtt *)((char *)this + 1728))->Create(-5520641, (int)v21);
  ((UIItem *)((char *)this + 1728))->SetData(31);
  v9 = *((_DWORD *)this + 452);
  v10 = *((_DWORD *)this + 454);
  *((_DWORD *)this + 457) = *((_DWORD *)this + 453) + 26;
  *((_DWORD *)this + 456) = v9 + 6;
  v11 = *((_DWORD *)this + 455) - 38;
  *((_DWORD *)this + 768) = 0;
  *((_DWORD *)this + 769) = 20;
  *((_DWORD *)this + 458) = v10 - 6;
  *((_DWORD *)this + 459) = v11;
  sub_445FA0((char *)this + 2184);
  ((UICaption *)((char *)this + 2184))->SetEnable((int)dword_DDAD3C, 0);
  ((UIRoleSelect *)((char *)this + 1728))->SetByte(1);
  return 1;
}

// 0x00536A40
// attributes: thunk
int Actor::GetDefaultFOV2_thunk()
{
  return this->SetDefaultFOV2();
}

// 0x00536A50
int Actor::SetDefaultFOV2()
{
  dword_17B154C = 1094713344;
  return 1094713344;
}

// 0x00536A60
// attributes: thunk
int Actor::GetDefaultDist2_thunk()
{
  int result; // eax

  return result;
}

// 0x00536A70
void Actor::SetDefaultDist2()
{
  flt_17B1548 = 12.0 + 12.0;
}

// 0x00536A80
void Actor::FastInit()
{
  this->m_actarray[0] = HIBYTE(this);
  *(_DWORD *)&this->m_actarray[4] = 0;
  *(_DWORD *)&this->m_actarray[8] = 0;
  *(_DWORD *)&this->m_actarray[12] = 0;
  this->m_dwMatMsg[0] = 0;
  this->m_dwMatMsg[1] = 0;
  memset(this->m_name, 0, 0x104u);
  memset(this->m_szTexture, 0, 0x104u);
}

// 0x00536AC0
int Actor::SetMaterialName(void *name)
{
  unsigned int *m_dwMatMsg; // ebx
  char *v5; // edi
  unsigned int v6; // kr04_4
  int v7; // eax
  unsigned int v8; // esi
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  gbActor *v13; // ecx
  char *m_szTexture; // esi
  gbActor *v15; // ebp
  gbActor *m_pact; // [esp-0x4] [ebp-0x30]
  struct gbNodeMsgObj v17; // [esp+0x10] [ebp-0x1C] BYREF
  int v18; // [esp+0x28] [ebp-0x4]

  m_dwMatMsg = this->m_dwMatMsg;
  if ( !strcmp((const char *)name, (const char *)this->m_dwMatMsg) )
    return 1;
  v6 = strlen((const char *)name) + 1;
  v5 = (char *)name + v6;
  qmemcpy(m_dwMatMsg, name, 4 * (v6 >> 2));
  qmemcpy(&m_dwMatMsg[v6 >> 2], &v5[4 * (v6 >> 2) - v6], v6 & 3);
  _strlwr((char *)m_dwMatMsg);
  v7 = *(_DWORD *)&this->m_actarray[4];
  v8 = 0;
  if ( v7 && (unsigned int)((*(_DWORD *)&this->m_actarray[8] - v7) >> 2) > 1 )
  {
    this->m_pact = 0;
    v9 = gbCrc32Compute((const char *)m_dwMatMsg);
    while ( 1 )
    {
      v10 = *(_DWORD *)&this->m_actarray[4];
      if ( !v10 || v8 >= (*(_DWORD *)&this->m_actarray[8] - v10) >> 2 )
        break;
      if ( this->ValidateInput(v9, *(_DWORD *)(v10 + 4 * v8)) )
      {
        this->m_pact = *(gbActor **)(*(_DWORD *)&this->m_actarray[4] + 4 * v8);
        break;
      }
      ++v8;
    }
  }
  m_pact = this->m_pact;
  v11 = gbCrc32Compute((const char *)m_dwMatMsg);
  v12 = this->ValidateInput(v11, (int)m_pact);
  v13 = this->m_pact;
  if ( !v13 || !v12 )
    return 0;
  ((gbActor *)v13)->GotoAction((char *)m_dwMatMsg, 0);
  while ( ((gbVisNode *)this->m_pact)->PopMessage(v17) )
    ;
  m_szTexture = this->m_szTexture;
  if ( this->m_szTexture[0] )
  {
    v15 = this->m_pact;
    v18 = 0;
// [VFTABLE] (*((void ( **)(gbActorDef *, char *))v15->pBody->__vftable + 15))(v15->pBody, m_szTexture);
    v18 = -1;
  }
  return 1;
}

// 0x00536C50
int Actor::CompareActionName(int actionIdx, int nVal)
{
  if ( !strcmp((&off_570904)[actionIdx], (const char *)this->m_dwMatMsg) )
    return 1;
  else
    return this->SetMaterialName((void *)(&off_570904)[actionIdx]);
}

// 0x00536CC0
unsigned int Actor::GetAnimDuration(int animId)
{
  return ((gbActor *)this->m_pact)->GetActionDuration((char *)animId);
}

// 0x00536CE0
void Actor::EnableTransition(int nVal, int nVal2)
{
  ((gbActor *)this->m_pact)->EnableActionTransMtl((char *)nVal, nVal2);
}

// 0x00536D00
void Actor::SetTimeScale(float scale)
{
  ((gbVisNode *)this->m_pact)->SetTimeScale(scale);
}

// 0x00536FB0
int Actor::QueryState()
{
  return (*(int ( **)(gbActor *))(*(_DWORD *)this->m_pact + 20))(this->m_pact);
}

// 0x00536FC0
int Actor::DispatchAction(int actionId)
{
  return (*(int ( **)(gbActor *, int))(*(_DWORD *)this->m_pact + 16))(this->m_pact, actionId);
}

// 0x00536FD0
int Actor::PlayAction(int actionId)
{
// [VFTABLE] return (*((int ( **)(gbActorDef *, int, gbActor *))this->m_pact->pBody->__vftable + 7))(
// [VFTABLE]   this->m_pact->pBody,
// [VFTABLE]   actionId,
// [VFTABLE]   this->m_pact);
}

// 0x00536FF0
int Actor::UpdateAllActions()
{
  unsigned int i; // edi
  int v3; // eax
  int result; // eax
  unsigned int *m_dwMatMsg; // esi

  for ( i = 0; ; ++i )
  {
    v3 = *(_DWORD *)&this->m_actarray[4];
    if ( !v3 || i >= (*(_DWORD *)&this->m_actarray[8] - v3) >> 2 )
      break;
    ((gbActorMgr *)g_pActorMgr)->DestroyActor(*(gbActor **)(v3 + 4 * i));
  }
  result = *(_DWORD *)&this->m_actarray[8];
  *(_DWORD *)&this->m_actarray[8] = *(_DWORD *)&this->m_actarray[4];
  this->m_pact = 0;
  m_dwMatMsg = this->m_dwMatMsg;
  *m_dwMatMsg = 0;
  m_dwMatMsg[1] = 0;
  return result;
}

// 0x005370E0
int Actor::ValidateInput(int nVal, int nVal2)
{
  int v3; // ecx
  int v4; // eax
  _DWORD *i; // edx

  if ( !nVal2 )
    return 0;
  v3 = *(_DWORD *)(nVal2 + 100);
  v4 = 0;
  if ( v3 <= 0 )
    return 0;
  for ( i = (_DWORD *)(*(_DWORD *)(nVal2 + 96) + 4); *i != nVal; i += 9 )
  {
    if ( ++v4 >= v3 )
      return 0;
  }
  return 1;
}

// 0x00537120
void Actor::SetTextureName(const char *pszName)
{
  if ( pszName )
  {
    strcpy(this->m_szTexture, pszName);
    if ( this->m_szTexture[0] )
    {
// [VFTABLE] (*((void ( **)(gbActorDef *, char *))this->m_pact->pBody->__vftable + 15))(
// [VFTABLE]   this->m_pact->pBody,
// [VFTABLE]   this->m_szTexture);
    }
  }
}

// 0x005371B0
void Actor::SetVisible(int bVisible)
{
  int v3; // eax
  int v4; // eax
  gbActor *v5; // ecx
  char *m_szTexture; // esi
  gbActor *v7; // ebx
  gbActor *m_pact; // [esp+0x0] [ebp-0x2C]
  struct gbNodeMsgObj v9; // [esp+0x10] [ebp-0x1C] BYREF
  int v10; // [esp+0x28] [ebp-0x4]
  char *v11; // [esp+0x34] [ebp+0x8]
  char *v12; // [esp+0x38] [ebp+0xC]

  if ( bVisible )
  {
    strcpy((char *)this->m_dwMatMsg, (const char *)bVisible);
    _strlwr((char *)this->m_dwMatMsg);
  }
  m_pact = this->m_pact;
  v3 = gbCrc32Compute((const char *)this->m_dwMatMsg);
  v4 = this->ValidateInput(v3, (int)m_pact);
  v5 = this->m_pact;
  if ( v5 && v4 )
  {
    ((gbActor *)v5)->GotoAction((char *)this->m_dwMatMsg, v11, v12);
    while ( ((gbVisNode *)this->m_pact)->PopMessage(v9) )
      ;
    m_szTexture = this->m_szTexture;
    if ( this->m_szTexture[0] )
    {
      v7 = this->m_pact;
      v10 = 0;
// [VFTABLE] (*((void ( **)(gbActorDef *, char *))v7->pBody->__vftable + 15))(v7->pBody, m_szTexture);
      v10 = -1;
    }
  }
}

// 0x005372B0
int Actor::GetArrayCount()
{
  int v1; // edx

  v1 = *(_DWORD *)&this->m_actarray[4];
  if ( v1 )
    return (*(_DWORD *)&this->m_actarray[8] - v1) >> 2;
  else
    return 0;
}

// 0x005372D0
int * Actor::LoadActionSequence(int *p_DWORD, unsigned int dwVal, int *p_DWORD2)
{
  Actor *v5; // edi
  int *result; // eax
  int v7; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  int *v11; // ecx
  int *n; // eax
  int *v13; // eax
  unsigned int v14; // edx
  int *v15; // edi
  int *v16; // edx
  int *v17; // eax
  int v18; // ecx
  int v19; // eax
  unsigned int v20; // ebx
  int *v21; // esi
  int *v22; // ecx
  _DWORD *v23; // eax
  unsigned int k; // ebp
  int *v25; // ecx
  int *m; // eax
  unsigned int v27; // ebp
  int *v28; // esi
  int *i; // ecx
  _DWORD *v30; // ecx
  int *j; // eax
  int v32; // esi
  int v34; // [esp+0x14] [ebp-0x4]
  int *dwVala; // [esp+0x20] [ebp+0x8]
result = *(int **)&this->m_actarray[8];
  if ( (*(_DWORD *)&this->m_actarray[12] - (int)result) >> 2 >= dwVal )
  {
    if ( result - p_DWORD >= dwVal )
    {
      if ( dwVal )
      {
        v27 = 4 * dwVal;
        v28 = *(int **)&this->m_actarray[8];
        for ( i = &result[-dwVal]; i != result; ++v28 )
        {
          if ( v28 )
            *v28 = *i;
          ++i;
        }
        v30 = *(_DWORD **)&this->m_actarray[8];
        for ( j = &v30[v27 / 0xFFFFFFFC]; j != p_DWORD; *v30 = v32 )
        {
          v32 = *--j;
          --v30;
        }
        for ( result = p_DWORD; result != &p_DWORD[v27 / 4]; ++result )
          *result = *p_DWORD2;
        *(_DWORD *)&this->m_actarray[8] += v27;
      }
    }
    else
    {
      v20 = 4 * dwVal;
      v21 = &p_DWORD[dwVal];
      if ( p_DWORD != result )
      {
        v22 = &v21[v20 / 0xFFFFFFFC];
        do
        {
          if ( v21 )
          {
            *v21 = *v22;
}
          ++v22;
          ++v21;
        }
        while ( v22 != result );
      }
      v23 = *(_DWORD **)&this->m_actarray[8];
      for ( k = dwVal - (v23 - p_DWORD); k; --k )
      {
        if ( v23 )
          *v23 = *p_DWORD2;
        ++v23;
      }
      v25 = *(int **)&this->m_actarray[8];
      for ( m = p_DWORD; m != v25; ++m )
        *m = *p_DWORD2;
      result = (int *)(v20 + *(_DWORD *)&this->m_actarray[8]);
      *(_DWORD *)&this->m_actarray[8] = result;
    }
  }
  else
  {
    v7 = *(_DWORD *)&this->m_actarray[4];
    if ( !v7 || (v8 = ((int)result - v7) >> 2, dwVal >= v8) )
      v8 = dwVal;
    if ( v7 )
      v9 = ((int)result - v7) >> 2;
    else
      v9 = 0;
    v10 = v8 + v9;
    v34 = v10;
    if ( v10 < 0 )
      v10 = 0;
    dwVala = (int *)operator new(4 * v10);
    v11 = dwVala;
    for ( n = *(int **)&this->m_actarray[4]; n != p_DWORD; ++v11 )
    {
      if ( v11 )
        *v11 = *n;
      ++n;
    }
    v13 = v11;
    if ( dwVal )
    {
      v14 = dwVal;
      do
      {
        if ( v13 )
        {
          *v13 = *p_DWORD2;
}
        ++v13;
        --v14;
      }
      while ( v14 );
    }
    v15 = *(int **)&this->m_actarray[8];
    v16 = &v11[dwVal];
    if ( p_DWORD != v15 )
    {
      v17 = p_DWORD;
      do
      {
        if ( v16 )
          *v16 = *v17;
        ++v17;
        ++v16;
      }
      while ( v17 != v15 );
    }
    operator delete(*(void **)&this->m_actarray[4]);
    *(_DWORD *)&this->m_actarray[12] = &dwVala[v34];
    v18 = *(_DWORD *)&this->m_actarray[4];
    if ( v18 )
    {
      v19 = *(_DWORD *)&this->m_actarray[8];
      *(_DWORD *)&this->m_actarray[4] = dwVala;
      result = &dwVala[dwVal + ((v19 - v18) >> 2)];
    }
    else
    {
      *(_DWORD *)&this->m_actarray[4] = dwVala;
      result = &dwVala[dwVal];
    }
    *(_DWORD *)&this->m_actarray[8] = result;
  }
  return result;
}

// 0x00537510
int Actor::StoreParam(int nVal, int nVal2)
{
  int result; // eax
  int v4; // ecx
  _DWORD *v5; // [esp+0xC] [ebp+0xC]

  result = nVal2;
  if ( nVal2 )
  {
    v4 = nVal2;
    result = nVal;
    do
    {
      if ( result )
        *(_DWORD *)result = *v5;
      result += 4;
      --v4;
    }
    while ( v4 );
  }
  return result;
}

// 0x005375B0
int Actor::ClearArrayEntry(int nVal)
{
  *(_BYTE *)nVal = HIBYTE(nVal);
  *(_DWORD *)(nVal + 4) = 0;
  *(_DWORD *)(nVal + 8) = 0;
  *(_DWORD *)(nVal + 12) = 0;
  *(_BYTE *)(nVal + 16) = HIBYTE(nVal);
  *(_DWORD *)(nVal + 20) = 0;
  *(_DWORD *)(nVal + 24) = 0;
  *(_DWORD *)(nVal + 28) = 0;
  *(_BYTE *)(nVal + 32) = HIBYTE(nVal);
  *(_DWORD *)(nVal + 36) = 0;
  *(_DWORD *)(nVal + 40) = 0;
  *(_DWORD *)(nVal + 44) = 0;
  return nVal;
}

// 0x005375F0
void Actor::ClearPathBuffer()
{
  int v2; // edi
  int i; // [esp+0x10] [ebp-0x10]

  operator delete(this->m_pAllocBuf);
  this->m_pAllocBuf = 0;
  this->m_fTransitionSpeed = 0.0;
  this->m_fTransitionPos = 0.0;
  operator delete(*(void **)this->m_name);
  *(_DWORD *)this->m_name = 0;
  *(_DWORD *)&this->m_name[4] = 0;
  this->m_fMoveSpeed = 0.0;
  v2 = *(_DWORD *)&this->m_actarray[4];
  for ( i = *(_DWORD *)&this->m_actarray[8]; v2 != i; v2 += 164 )
  {
    nullsub_2(*(_DWORD *)(v2 + 152), *(_DWORD *)(v2 + 156));
    operator delete(*(void **)(v2 + 152));
    *(_DWORD *)(v2 + 152) = 0;
    *(_DWORD *)(v2 + 156) = 0;
    *(_DWORD *)(v2 + 160) = 0;
    ((Array *)(v2 + 132))->Free();
  }
  operator delete(*(void **)&this->m_actarray[4]);
  *(_DWORD *)&this->m_actarray[4] = 0;
  *(_DWORD *)&this->m_actarray[8] = 0;
  *(_DWORD *)&this->m_actarray[12] = 0;
}

// 0x005376E0
int Actor::LoadSaveData(char *pszSlotIdx)
{
  int result; // eax
  FILE *v3; // ebx
  _BYTE v4[72]; // [esp+0x4] [ebp-0x1E0] BYREF
  char v5[80]; // [esp+0x4C] [ebp-0x198] BYREF
  char Buffer[260]; // [esp+E0h] [ebp-0x104] BYREF
  char *v7; // [esp+0x1EC] [ebp+0x8]

  sprintf(Buffer, "save\\pal%02d.arc", pszSlotIdx);
  result = (int)fopen(Buffer, "rb");
  v3 = (FILE *)result;
  if ( result )
  {
    fread(v4, 0xDCu, 1u, (FILE *)result);
    qmemcpy(v7, v5, 0x50u);
    fclose(v3);
    return 1;
  }
  return result;
}

// 0x00537770
int Actor::LoadActions(FILE *Stream, int *pnVal)
{
  int v4; // ebx
  char **v5; // ebx
  char *v6; // eax
  int v7; // ebx
  int v8; // edx
  gbActor **p_m_pact; // ebx
  int result; // eax
  int v11; // esi
  char **v12; // [esp-0x1C] [ebp-0x130]
  char *v13; // [esp-0xC] [ebp-0x120]
  FILE *v14; // [esp+0x0] [ebp-0x114]
  int v15; // [esp+0x10] [ebp-0x104]
  int v16; // [esp+0x10] [ebp-0x104]
  int v17; // [esp+0x10] [ebp-0x104]
  char pActionType; // [esp+0x17] [ebp-FDh] BYREF
  int v19; // [esp+0x18] [ebp-FCh] BYREF
  char *a4; // [esp+0x1C] [ebp-F8h] BYREF
  int Buffer; // [esp+0x20] [ebp-F4h] BYREF
  char nY[132]; // [esp+0x24] [ebp-F0h] BYREF
  Array v23; // [esp+A8h] [ebp-0x6C] BYREF
  char v24; // [esp+B8h] [ebp-0x5C] BYREF
  void *Block; // [esp+BCh] [ebp-0x58]
  int v26; // [esp+C0h] [ebp-0x54]
  int v27; // [esp+C4h] [ebp-0x50]
  _BYTE pData[64]; // [esp+C8h] [ebp-0x4C] BYREF
  int v29; // [esp+0x110] [ebp-0x4]

  fseek(Stream, pnVal[40], 0);
  fread(&Buffer, 4u, 1u, Stream);
  v4 = 0;
  if ( Buffer > 0 )
  {
    v15 = 0;
    do
    {
      fread((void *)(((GRPinput *)&stru_D8C2B8)->KeyInfo[148].Data + v15), 0x18u, 1u, Stream);
      ++v4;
      v15 += 24;
    }
    while ( v4 < Buffer );
  }
  fseek(Stream, pnVal[41], 0);
  a4 = 0;
  fread(&a4, 4u, 1u, Stream);
  v5 = ActVec_UninitCopy(
         *(_DWORD *)&this->m_actarray[8],
         *(unsigned int **)&this->m_actarray[8],
         *(unsigned int **)&this->m_actarray[4],
         v12);
  this->DestroyActionRange((int)v5, *(_DWORD *)&this->m_actarray[8]);
  v6 = a4;
  *(_DWORD *)&this->m_actarray[8] = v5;
  v16 = 0;
  if ( (int)v6 > 0 )
  {
    do
    {
      memset(&v23.m_nSize, 0, 12);
      LOBYTE(v23.m_pDataStart) = pActionType;
      v29 = 0;
      ((Actor *)&v24)->InitAction(&pActionType);
      v13 = *(char **)&this->m_actarray[8];
      v29 = 1;
      ActVec_InsertN(this, v13, 1u, nY);
      v7 = *(_DWORD *)&this->m_actarray[4];
      if ( v7 )
        v8 = (*(_DWORD *)&this->m_actarray[8] - v7) / 164;
      else
        v8 = 0;
      ((UIBigMap *)(v7 + 164 * v8 - 164))->SetElementVisible(Stream, v14);
      v29 = 2;
      nullsub_2(Block, v26);
      operator delete(Block);
      Block = 0;
      v26 = 0;
      v27 = 0;
      v29 = -1;
      ((Array *)&v23)->Free();
      ++v16;
    }
    while ( v16 < (int)a4 );
  }
  fseek(Stream, pnVal[46], 0);
  v19 = 0;
  fread(&v19, 4u, 1u, Stream);
  p_m_pact = &this->m_pact;
  v17 = *(_DWORD *)this->m_name;
  nullsub_2(v17, *(_DWORD *)&this->m_name[4]);
  result = v19;
  *(_DWORD *)&this->m_name[4] = v17;
  v11 = 0;
  if ( result > 0 )
  {
    do
    {
      memset(pData, 0, sizeof(pData));
      fread(pData, 0x40u, 1u, Stream);
      ActVec_InsertRange((Actor *)p_m_pact, (char *)p_m_pact[2], 1u, pData);
      result = v19;
      ++v11;
    }
    while ( v11 < v19 );
  }
  return result;
}

// 0x00537A30
void Actor::ClearAllocBuffers()
{
  operator delete((void *)this->m_nAnimBuffer);
  this->m_nAnimBuffer = 0;
  this->m_nParticleBuffer = 0;
  this->m_vecTargetPos.x = 0.0;
  operator delete((void *)LODWORD(this->m_vecBonePos.x));
  this->m_vecBonePos.x = 0.0;
  this->m_vecBonePos.y = 0.0;
  this->m_vecBonePos.z = 0.0;
}

// 0x00537A90
FILE * Actor::DoSceneTransition(double pData, int nVal)
{
  char v3; // di
  char v4; // si
  FILE *result; // eax
  FILE *v6; // ebp
  char *v7; // esi
  int v8; // edi
  _BYTE *v9; // edx
  int v10; // esi
  void *v11; // edi
  int v12; // ecx
  unsigned __int8 **v13; // eax
  unsigned __int8 *v14; // edx
  int v15; // esi
  SceneObj *p_m_nScreenFlags; // ebx
  Actor *v17; // esi
  gbImage2D *m_needscriptdel; // ecx
  CScreenMode *Instance; // eax
  gbVec3D *p_m_lastFrom; // ebx
  float m_fCtrlYaw; // edi
  float m_yaw; // ecx
  float y; // eax
  int *p_capacity; // esi
  unsigned __int8 *p_pbyName; // edi
  scAsmDecoder *v26; // ecx
  PAL3 *v27; // ecx
  RenderTarget3 *v28; // eax
  PAL3 *v29; // ecx
  ScreenEffectMgr *Instance_fd20; // eax
  CScreenMode *v31; // eax
  gbAudioManager *AudioManager; // eax
  int *v33; // edi
  int v34; // esi
  int *v35; // ebx
  RoleSystem *RoleDataOffset; // eax
  int v37; // esi
  int v38; // eax
  Actor *v39; // edi
  double v40; // [esp-0x10] [ebp-0x280B0]
  char v41; // [esp+0x0] [ebp-0x280A0]
  char v42; // [esp+0x4] [ebp-0x2809C]
  Actor *v43; // [esp+0x10] [ebp-0x28090] BYREF
  float v44; // [esp+0x14] [ebp-0x2808C] BYREF
  float v45; // [esp+0x18] [ebp-0x28088]
  float v46; // [esp+0x1C] [ebp-0x28084]
  unsigned __int8 v47[4]; // [esp+0x20] [ebp-0x28080] BYREF
  int v48; // [esp+0x24] [ebp-0x2807C]
  int v49; // [esp+0x28] [ebp-0x28078]
  int v50; // [esp+0x2C] [ebp-0x28074]
  double sceneNames[4]; // [esp+0x3C] [ebp-0x28064] BYREF
  char v52; // [esp+0x5C] [ebp-0x28044] BYREF
  _DWORD pSrc[7]; // [esp+C0h] [ebp-0x27FE0] BYREF
  unsigned __int8 pbyName; // [esp+DCh] [ebp-0x27FC4] BYREF
  unsigned __int8 v55[137]; // [esp+E0h] [ebp-0x27FC0] BYREF
  char String2[35]; // [esp+0x169] [ebp-0x27F37] BYREF
  int v57; // [esp+0x18C] [ebp-0x27F14]
  float v58; // [esp+0x190] [ebp-0x27F10]
  int v59; // [esp+0x194] [ebp-0x27F0C]
  int v60; // [esp+0x198] [ebp-0x27F08]
  int v61; // [esp+0x19C] [ebp-0x27F04]
  unsigned int v62; // [esp+0x1A0] [ebp-0x27F00]
  int v63; // [esp+0x1A4] [ebp-0x27EFC]
  int v64; // [esp+0x1A8] [ebp-0x27EF8]
  unsigned __int8 v65; // [esp+0x1AC] [ebp-0x27EF4]
  float v66; // [esp+0x1B0] [ebp-0x27EF0]
  char v67; // [esp+0x1B4] [ebp-0x27EEC]
  unsigned __int8 v68; // [esp+0x1B5] [ebp-0x27EEB]
  char v69[20]; // [esp+0x1B6] [ebp-0x27EEA] BYREF
  int v70; // [esp+0x1CA] [ebp-0x27ED6]
  int pnVal[44]; // [esp+0x20C] [ebp-0x27E94] BYREF
  char v72; // [esp+0x2BC] [ebp-0x27DE4] BYREF
  int v73; // [esp+0x2C8] [ebp-0x27DD8]
  char Buffer[260]; // [esp+0x2E8] [ebp-0x27DB8] BYREF
  int v75; // [esp+0x3EC] [ebp-0x27CB4] BYREF
  int v76; // [esp+0x3F0] [ebp-0x27CB0]
  _DWORD v77[3]; // [esp+0x3F4] [ebp-0x27CAC]
  __int16 v78; // [esp+0x400] [ebp-0x27CA0]
  int v79; // [esp+0x402] [ebp-0x27C9E]
  char v80; // [esp+0x406] [ebp-0x27C9A]
  int v81; // [esp+0x408] [ebp-0x27C98]
  unsigned __int8 v82; // [esp+0x40C] [ebp-0x27C94]
  _BYTE v83[41]; // [esp+0x40D] [ebp-0x27C93] BYREF
  __int16 v84; // [esp+0x436] [ebp-0x27C6A]
  int v85; // [esp+0x438] [ebp-0x27C68]
  int v86; // [esp+0x43C] [ebp-0x27C64]
  int v87; // [esp+0x440] [ebp-0x27C60]
  _BYTE v88[40]; // [esp+0x444] [ebp-0x27C5C]
  int v89; // [esp+0x46C] [ebp-0x27C34]
  _BYTE v90[160]; // [esp+0x470] [ebp-0x27C30] BYREF
  int v91; // [esp+0x510] [ebp-0x27B90]
  _DWORD v92[40466]; // [esp+0x514] [ebp-0x27B8C] BYREF
  char v93; // [esp+0x27D5C] [ebp-0x344]
  int v94; // [esp+0x27D60] [ebp-0x340]
  _BYTE v95[828]; // [esp+0x27D64] [ebp-0x33C] BYREF
sub_407790();
  sprintf(Buffer, "save\\pal%02d.arc", LODWORD(pData));
  result = fopen(Buffer, "rb");
  v6 = result;
  if ( result )
  {
    v42 = v4;
    v41 = v3;
    fread(pnVal, 0xDCu, 1u, result);
    memset(&pSrc[4], 0, 12);
    v7 = (char *)v55;
    v8 = 5;
    do
    {
      v7 += 28;
      --v8;
    }
    while ( v8 );
    v59 = 0;
    v60 = 0;
    v61 = 0;
    fseek(v6, pnVal[38], 0);
    fread(sceneNames, 0x1D0u, 1u, v6);
    fseek(v6, pnVal[39], 0);
    LoadGameState(v6);
    ((Actor *)v43)->LoadActions(v6, pnVal);
    fseek(v6, pnVal[42], 0);
    v44 = 1.0;
    v45 = 1.0;
    v46 = 1.0;
    fread(&v44, 0xCu, 1u, v6);
    fseek(v6, pnVal[43], 0);
    v75 = 0;
    v76 = 0;
    memset(v92, 0, 12);
    v77[0] = 1;
    ((Actor *)&v92[3])->InitAnimSequence();
    ArraySort((int)&v92[58], 808, 200, (int)sub_538260);
    v92[40465] = 0;
    v92[40462] = 1;
    v92[40463] = 1;
    v92[40464] = 1;
    v9 = v95;
    v10 = 11;
    do
    {
      v11 = v9;
      v9 += 52;
      --v10;
      memset(v11, 0, 0x2Cu);
    }
    while ( v10 );
    fread(&v75, 0x27CB4u, 1u, v6);
    dword_D8BC38 = v77[0];
    dword_D8BC34 = v76;
    g_nRoleParam = v77[1];
    LOBYTE(g_nActor_DE5F9C) = v80;
    dword_C10CC4 = v81;
    dword_D8BC30 = v75;
    LOWORD(g_nActor_DE5FA8) = v78;
    g_nActorState = v79;
    LOBYTE(g_dwUISettings) = v83[40];
    g_nRoleState = v77[2];
    qmemcpy(g_SaveSlotFlags, v83, sizeof(g_SaveSlotFlags));
    g_bUIWnd_DE625A = v82;
    *(_WORD *)((char *)&g_dwUISettings + 1) = v84;
    g_nUpdateInterval = v87;
    g_bRoleFlag1 = v85 == 1;
    g_bRoleFlag2 = v86 == 1;
    v12 = 0;
    v13 = &g_pSceneTransitionBegin;
    do
    {
      ++v13;
      v14 = (unsigned __int8 *)(unsigned __int8)v88[v12++];
      *(v13 - 1) = v14;
    }
    while ( (int)v13 < (int)&g_pSceneTransitionEnd );
    qmemcpy(g_fCamRoleParams, v90, sizeof(g_fCamRoleParams));
    g_nFiveNimbusCount = v91;
    qmemcpy(pCmd, v92, 0x27848u);
    g_nWolfIndex = v89;
    byte_D92785 = v93;
    dword_C10CD4 = v94;
    qmemcpy(g_pCBSystem->m_Player, v95, sizeof(g_pCBSystem->m_Player));
    g_fGameTimer = *(float *)&pnVal[18];
    CScreenMode::GetInstance()->m_bRenderAlt = v67;
    v15 = v68;
    CScreenMode::GetInstance()->m_nFadeState = v15;
    p_m_nScreenFlags = (SceneObj *)&CScreenMode::GetInstance()->m_nScreenFlags;
    v17 = (Actor *)strlen(v69);
    v43 = v17;
    if ( ((SceneObj *)p_m_nScreenFlags)->UpdateAutoDelete((unsigned int)v17) )
    {
      qmemcpy(p_m_nScreenFlags->m_needscriptdel, v69, (unsigned int)v17);
      m_needscriptdel = p_m_nScreenFlags->m_needscriptdel;
// [VFTABLE] p_m_nScreenFlags->__vftable = v17;
      v17->m_actarray[(_DWORD)m_needscriptdel] = 0;
    }
    if ( CScreenMode::GetInstance()->m_bRenderAlt )
    {
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioFadeOut();
    }
    HIDWORD(v40) = (unsigned long)&v52;
    LODWORD(v40) = sceneNames;
    LoadScene(v40, (char *)1, 0, v41, v42);
    p_m_lastFrom = &g_pCameraCtrl->m_lastFrom;
    if ( !LODWORD(g_pCameraCtrl->m_nextYAW)
      || (m_fCtrlYaw = g_pCameraCtrl->m_fCtrlYaw, m_yaw = g_pCameraCtrl->m_yaw, LODWORD(m_fCtrlYaw) == LODWORD(m_yaw)) )
    {
      ((CameraCtrl *)&g_pCameraCtrl->m_lastFrom)->UpdateFOVLerp();
      y = p_m_lastFrom[2].y;
      LODWORD(p_m_lastFrom[2].y) = LODWORD(y) + 28;
      Actor_CopyConstruct_1C((void *)LODWORD(y), pSrc);
    }
    else
    {
      LODWORD(g_pCameraCtrl->m_fCtrlYaw) = LODWORD(m_fCtrlYaw) + 28;
      if ( LODWORD(m_fCtrlYaw) + 28 == LODWORD(m_yaw) )
      {
        Actor_CopyConstruct_1C((void *)LODWORD(m_fCtrlYaw), pSrc);
        ((CameraCtrl *)p_m_lastFrom)->UpdateFOVLerp();
      }
      else if ( m_fCtrlYaw != 0.0 )
      {
        qmemcpy((void *)LODWORD(m_fCtrlYaw), pSrc, 0x1Cu);
      }
    }
    ++LODWORD(p_m_lastFrom[3].z);
    ((RoleCamera *)g_pCameraCtrl)->PushState();
    p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
    p_pbyName = &pbyName;
    do
    {
      ((Actor *)p_capacity)->SetActionByName(p_pbyName);
      p_capacity += 2176;
      p_pbyName += 28;
    }
    while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
    if ( _strcmpi(&((RoleSystem *)&stru_C0A360)->m_nAnimState, String2) )
    {
      sub_536D20((Actor *)&((RoleSystem *)&stru_C0A360)->m_partyActor.m_nActionType, String2, 0);
      strcpy(&((RoleSystem *)&stru_C0A360)->m_nAnimState, String2);
      ((RoleSystem *)&stru_C0A360)->UpdateTransform();
    }
    ((scAsmDecoder *)v26)->Execute(v55[136], 0);
    g_nScriptEventParam = v57;
    g_fScriptEventParam2 = v58;
    g_nScriptRolePosX = v59;
    g_nScriptRolePosY = v60;
    v27 = (PAL3 *)v63;
    g_nScriptRolePosZ = v61;
    g_nCurrentEventId = v62;
    g_nActor_BFDBA8 = v63;
    LOBYTE(v27) = v65;
    g_nActor_BFDBAC = v64;
    g_fFadeTimer = v66;
    g_nSceneTransitionParam2 = v65;
    v28 = ((PAL3 *)v27)->GetInstance();
// [VFTABLE] LOBYTE(v28->__vftable) = v69[16];
    Instance_fd20 = ((PAL3 *)v29)->GetInstance_fd20();
    LOBYTE(Instance_fd20->m_pVtable) = v69[17];
    byte_BFDA40 = v69[19];
    byte_BFDA41 = v69[18];
    ((PalScript *)(unsigned __int8)v70)->InitParticleSlht((PalScript *)(unsigned __int8)v70);
    v31 = CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)((CScreenMode *)v31)->GetAudioManager();
    if ( AudioManager )
    {
      AudioManager->S_2DMasterVol = v44;
      AudioManager->S_3DMasterVol = v45;
      ((gbAudioManager *)AudioManager)->SetMusicMasterVolume(v46);
    }
    v33 = (int *)(UISceneUpdate() + 492772);
    v34 = 0;
    if ( *v33 > 0 )
    {
      v35 = (int *)&v72;
      do
      {
        if ( *v35 )
        {
          fseek(v6, *v35, 0);
          RoleDataOffset = (RoleSystem *)GetRoleDataOffset(v34);
          ((RoleSystem *)RoleDataOffset)->ClearPathData(v6);
        }
        ++v34;
        ++v35;
      }
      while ( v34 < *v33 );
    }
    v37 = 0;
    if ( v73 )
    {
      fseek(v6, v73, 0);
      v43 = 0;
      fread(&v43, 4u, 1u, v6);
      v38 = UISceneUpdate();
      v48 = 0;
      v49 = 0;
      v50 = 0;
      if ( (int)v43 > 0 )
      {
        v39 = (Actor *)(v38 + 57572);
        do
        {
          fread(v47, 0x1Cu, 1u, v6);
          ((Actor *)v39)->SetActionByName(v47);
          ++v37;
          v39 = (Actor *)((char *)v39 + 8704);
        }
        while ( v37 < (int)v43 );
      }
    }
    fclose(v6);
    return (FILE *)1;
  }
  return result;
}

// 0x005381D0
char * Actor::InitAnimSequence()
{
  char *v1; // esi
  int v2; // ebx
  float *p_m_fRoleParam2; // eax
  float *v4; // ebp
  float *v5; // ebp
  float *v6; // ebp

  v1 = &this->m_name[4];
  v2 = 4;
  p_m_fRoleParam2 = &this->m_fRoleParam2;
  do
  {
    v4 = p_m_fRoleParam2 - 6;
    *(_DWORD *)v1 = 0;
    *(p_m_fRoleParam2 - 8) = 0.0;
    *(p_m_fRoleParam2 - 7) = 0.0;
    *v4 = 0.0;
    v1 += 48;
    v4[1] = 0.0;
    v4[2] = 0.0;
    v5 = p_m_fRoleParam2 - 3;
    *(p_m_fRoleParam2 - 3) = 0.0;
    v5[1] = 0.0;
    v5[2] = 0.0;
    v6 = p_m_fRoleParam2;
    p_m_fRoleParam2 += 12;
    --v2;
    *v6 = 0.0;
    v6[1] = 0.0;
    v6[2] = 0.0;
  }
  while ( v2 );
  this->m_actarray[0] = 0;
  this->m_actarray[1] = 0;
  this->m_actarray[2] = 0;
  this->m_actarray[3] = 0;
  this->m_actarray[4] = 0;
  this->m_actarray[5] = 0;
  this->m_actarray[6] = 0;
  *(_DWORD *)&this->m_actarray[12] = 0;
  this->m_pact = 0;
  *(_DWORD *)this->m_name = 0;
  *(_DWORD *)&this->m_fScale = 0;
  *(_DWORD *)&this->m_actarray[8] = 1065353216;
  memset(&this->m_name[4], 0, 0xC0u);
  return this->m_actarray;
}

// 0x00538320
BOOL Actor::EnsureDirectory()
{
  return CheckDirectoryExists(PathName) || CreateDirectoryA(PathName, 0);
}

// 0x00538500
BOOL Actor::LoadActorModel(int nVal)
{
  int v2; // edi
// [IDA_MISID]   _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  BOOL result; // eax
  int v6; // ebx
  FILE *v7; // ebp
  _DWORD *v8; // eax
  int v9; // ecx
  int *p_capacity; // esi
  float *v11; // edi
  float v12; // edx
  gbVec3D *p_m_lastFrom; // esi
  float z; // eax
  float v15; // eax
  const char *m_nField0C; // eax
  PAL3 *v17; // ecx
  PAL3 *v18; // ecx
  int v19; // eax
  CHAR *v20; // esi
  int v21; // edi
  _BYTE *v22; // edx
  int v23; // esi
  void *v24; // edi
  int v25; // ecx
  unsigned __int8 **v26; // eax
  char v27; // dl
  int v28; // esi
  int *v29; // edi
  RoleSystem *RoleDataOffset; // eax
  int v31; // esi
  RoleSystem *v32; // edi
  int v33; // [esp-0x10] [ebp-0x282C0]
  int v34; // [esp+0x0] [ebp-0x282B0] BYREF
  Actor *v35; // [esp+0x4] [ebp-0x282AC]
  _DWORD v36[2]; // [esp+0x8] [ebp-0x282A8] BYREF
  float m_fCtrlYaw; // [esp+0x10] [ebp-0x282A0]
  int m_dist; // [esp+0x14] [ebp-0x2829C]
  float v39[7]; // [esp+0x18] [ebp-0x28298] BYREF
  _DWORD v40[116]; // [esp+0x34] [ebp-0x2827C] BYREF
  int p_DWORD2[55]; // [esp+0x204] [ebp-0x280AC] BYREF
  char String1[524]; // [esp+0x2E0] [ebp-0x27FD0] BYREF
  char Buffer[260]; // [esp+0x4EC] [ebp-0x27DC4] BYREF
  int v44; // [esp+0x5F0] [ebp-0x27CC0] BYREF
  int v45; // [esp+0x5F4] [ebp-0x27CBC]
  int v46; // [esp+0x5F8] [ebp-0x27CB8]
  int v47; // [esp+0x5FC] [ebp-0x27CB4]
  int v48; // [esp+0x600] [ebp-0x27CB0]
  __int16 v49; // [esp+0x604] [ebp-0x27CAC]
  int v50; // [esp+0x606] [ebp-0x27CAA]
  char v51; // [esp+0x60A] [ebp-0x27CA6]
  int v52; // [esp+0x60C] [ebp-0x27CA4]
  unsigned __int8 v53; // [esp+0x610] [ebp-0x27CA0]
  _BYTE v54[41]; // [esp+0x611] [ebp-0x27C9F] BYREF
  __int16 v55; // [esp+0x63A] [ebp-0x27C76]
  int v56; // [esp+0x63C] [ebp-0x27C74]
  int v57; // [esp+0x640] [ebp-0x27C70]
  int v58; // [esp+0x644] [ebp-0x27C6C]
  _BYTE v59[40]; // [esp+0x648] [ebp-0x27C68]
  int v60; // [esp+0x670] [ebp-0x27C40]
  _BYTE v61[160]; // [esp+0x674] [ebp-0x27C3C] BYREF
  int v62; // [esp+0x714] [ebp-0x27B9C]
  _DWORD v63[40466]; // [esp+0x718] [ebp-0x27B98] BYREF
  char v64; // [esp+0x27F60] [ebp-0x350]
  int v65; // [esp+0x27F64] [ebp-0x34C]
  _BYTE v66[828]; // [esp+0x27F68] [ebp-0x348] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v67; // [esp+0x282A4] [ebp-0xC]
  void *v68; // [esp+0x282A8] [ebp-0x8]
  int v69; // [esp+0x282AC] [ebp-0x4]

  v69 = -1;
// [IDA_MISID]   ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v68 = ((void*)0);
// [IDA_MISID]   v67 = ExceptionList;
  v4 = alloca(164516);
result = this->EnsureDirectory();
  if ( result )
  {
    v6 = UISceneUpdate();
    memset(p_DWORD2, 0, sizeof(p_DWORD2));
    *(float *)&p_DWORD2[18] = g_fGameTimer;
    p_DWORD2[19] = (int)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather;
    LOBYTE(p_DWORD2[20]) = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_pData;
    p_DWORD2[37] = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
    ctor_0x431870((int *)String1);
    v69 = 0;
    ((PalScript *)String1)->LoadFromFile("datascript\\SceneName.txt");
    ((PalScript *)String1)->SetDirectory((char *)v6);
    if ( !((PalScript *)String1)->FindSaveStateString((PalScript *)(v6 + 32), (char *)&p_DWORD2[20] + 1, (char *)0x40, v2) )
      ((PalScript *)String1)->FindSaveStateString((PalScript *)&dir[12], (char *)&p_DWORD2[20] + 1, (char *)0x40, v33);
    sprintf(Buffer, "save\\pal%02d.arc", nVal);
    v7 = fopen(Buffer, Mode);
    if ( v7 )
    {
      memset(&v40[37], 0, 12);
      v8 = &v40[43];
      v9 = 5;
      do
      {
        *(v8 - 2) = 0;
        *(v8 - 1) = 0;
        *v8 = 0;
        v8 += 7;
        --v9;
      }
      while ( v9 );
      memset(v40, 0, sizeof(v40));
      qmemcpy(v40, (const void *)v6, 0x84u);
      p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
      v11 = (float *)&v40[40];
      do
      {
        ((RoleSystem *)p_capacity)->ExportRoleData(v11);
        p_capacity += 2176;
        v11 += 7;
      }
      while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
      LOBYTE(v40[75]) = g_nCurrentRoleSlot;
      v12 = g_fScriptEventParam2;
      strcpy((char *)&v40[75] + 1, &((RoleSystem *)&stru_C0A360)->m_nAnimState);
      *(float *)&v40[85] = v12;
      v40[84] = g_nScriptEventParam;
      v40[86] = g_nScriptRolePosX;
      v40[87] = g_nScriptRolePosY;
      v40[88] = g_nScriptRolePosZ;
      v40[90] = g_nActor_BFDBA8;
      v40[89] = g_nCurrentEventId;
      LOBYTE(v40[92]) = g_nSceneTransitionParam2;
      v40[91] = g_nActor_BFDBAC;
      *(float *)&v40[93] = g_fFadeTimer;
      ((RoleSystem *)g_pCameraCtrl)->AddCameraKeyframe();
      v36[0] = LODWORD(g_pCameraCtrl->m_fromVec.z);
      v36[1] = LODWORD(g_pCameraCtrl->m_yaw);
      m_fCtrlYaw = g_pCameraCtrl->m_fCtrlYaw;
      m_dist = g_pCameraCtrl->m_dist;
      ((CameraCtrl *)v36)->SetupCameraArray(-1);
      v40[33] = *(_DWORD *)LODWORD(m_fCtrlYaw);
      v40[34] = *(_DWORD *)(LODWORD(m_fCtrlYaw) + 4);
      v40[35] = *(_DWORD *)(LODWORD(m_fCtrlYaw) + 8);
      v40[36] = *(_DWORD *)(LODWORD(m_fCtrlYaw) + 12);
      v40[37] = *(_DWORD *)(LODWORD(m_fCtrlYaw) + 16);
      v40[38] = *(_DWORD *)(LODWORD(m_fCtrlYaw) + 20);
      v40[39] = *(_DWORD *)(LODWORD(m_fCtrlYaw) + 24);
      p_m_lastFrom = &g_pCameraCtrl->m_lastFrom;
      if ( LODWORD(g_pCameraCtrl->m_fCtrlYaw) == LODWORD(g_pCameraCtrl->m_fromVec.z) )
        ((CameraCtrl *)&g_pCameraCtrl->m_lastFrom)->PopState();
      z = p_m_lastFrom[3].z;
      if ( z != 0.0 )
        LODWORD(p_m_lastFrom[2].y) -= 28;
      LODWORD(v15) = LODWORD(z) - 1;
      p_m_lastFrom[3].z = v15;
      if ( v15 == 0.0 )
        ((CameraCtrl *)p_m_lastFrom)->PopState();
      LOBYTE(v40[94]) = CScreenMode::GetInstance()->m_bRenderAlt;
      BYTE1(v40[94]) = CScreenMode::GetInstance()->m_nFadeState;
      m_nField0C = (const char *)CScreenMode::GetInstance()->m_nField0C;
      if ( !m_nField0C )
        m_nField0C = (const char *)&g_bActorFlag;
      strncpy((char *)&v40[94] + 2, m_nField0C, 0x10u);
// [VFTABLE] BYTE2(v40[98]) = ((PAL3 *)v17)->GetInstance()->__vftable;
      HIBYTE(v40[98]) = ((PAL3 *)v18)->GetInstance_fd20()->m_pVtable;
      BYTE1(v40[99]) = byte_BFDA40;
      LOBYTE(v40[99]) = byte_BFDA41;
      BYTE2(v40[99]) = g_pCurrentScript != 0;
      ((Actor *)v35)->BuildCollisionMesh((int *)v6);
      fwrite(p_DWORD2, 0xDCu, 1u, v7);
      p_DWORD2[38] = ftell(v7);
      fwrite(v40, 0x1D0u, 1u, v7);
      p_DWORD2[39] = ftell(v7);
      SaveGameState(v7);
      ((CScreenMode *)this->m_actarray)->LoadAudioFromFile(v7, p_DWORD2);
      v19 = ftell(v7);
      v44 = 0;
      v45 = 0;
      v46 = 1;
      p_DWORD2[43] = v19;
      memset(v63, 0, 12);
      ArraySort((int)&v63[9], 48, 4, 0 /* TODO: (int)CCBStageRole::ClearRoleState */);
      ((Actor *)&v63[3])->ClearActionFlags();
      v20 = (CHAR *)&v63[58];
      v21 = 200;
      do
      {
        sub_538260(v20);
        v20 += 808;
        --v21;
      }
      while ( v21 );
      v63[40465] = 0;
      v63[40462] = 1;
      v63[40463] = 1;
      v63[40464] = 1;
      v22 = v66;
      v23 = 11;
      do
      {
        v24 = v22;
        v22 += 52;
        --v23;
        memset(v24, 0, 0x2Cu);
      }
      while ( v23 );
      v44 = dword_D8BC30;
      v45 = dword_D8BC34;
      v46 = dword_D8BC38;
      v50 = g_nActorState;
      v51 = g_nActor_DE5F9C;
      v47 = g_nRoleParam;
      v48 = g_nRoleState;
      v49 = g_nActor_DE5FA8;
      v52 = dword_C10CC4;
      v58 = g_nUpdateInterval;
      qmemcpy(v54, g_SaveSlotFlags, 0x28u);
      v55 = *(_WORD *)((char *)&g_dwUISettings + 1);
      v54[40] = g_dwUISettings;
      v53 = g_bUIWnd_DE625A;
      v57 = g_bRoleFlag2;
      v56 = g_bRoleFlag1;
      v25 = 0;
      v26 = &g_pSceneTransitionBegin;
      do
      {
        v27 = *(_BYTE *)v26++;
        v59[v25++] = v27;
      }
      while ( (int)v26 < (int)&g_pSceneTransitionEnd );
      v60 = g_nWolfIndex;
      qmemcpy(v61, g_fCamRoleParams, sizeof(v61));
      v62 = g_nFiveNimbusCount;
      qmemcpy(v63, pCmd, sizeof(v63));
      v64 = byte_D92785;
      v65 = dword_C10CD4;
      qmemcpy(v66, g_pCBSystem->m_Player, 0x23Cu);
      fwrite(&v44, 0x27CB4u, 1u, v7);
      if ( *(_DWORD *)(v6 + 96) == 2 )
      {
        v28 = 0;
        if ( *(int *)(v6 + 492772) > 0 )
        {
          v29 = &p_DWORD2[44];
          do
          {
            *v29 = ftell(v7);
            RoleDataOffset = (RoleSystem *)GetRoleDataOffset(v28);
            ((RoleSystem *)RoleDataOffset)->GetFontColor(v7);
            ++v28;
            ++v29;
          }
          while ( v28 < *(_DWORD *)(v6 + 492772) );
        }
      }
      p_DWORD2[47] = ftell(v7);
      v34 = *(_DWORD *)(v6 + 57568);
      fwrite(&v34, 4u, 1u, v7);
      v31 = 0;
      memset(&v39[1], 0, 12);
      if ( v34 > 0 )
      {
        v32 = (RoleSystem *)(v6 + 57572);
        do
        {
          ((RoleSystem *)v32)->ExportRoleData(v39);
          fwrite(v39, 0x1Cu, 1u, v7);
          ++v31;
          v32 = (RoleSystem *)((char *)v32 + 8704);
        }
        while ( v31 < v34 );
      }
      fseek(v7, 0, 0);
      strcpy((char *)p_DWORD2, "PAL");
      LOBYTE(p_DWORD2[1]) = 1;
      fwrite(p_DWORD2, 0xDCu, 1u, v7);
      fclose(v7);
      v69 = -1;
      ((PalScript *)String1)->Cleanup();
      return 1;
    }
    else
    {
      v69 = -1;
      ((PalScript *)String1)->Cleanup();
      return 0;
    }
  }
  return result;
}

// 0x00538CE0
int Actor::ClearActionFlags()
{
  this->m_actarray[0] = 0;
  this->m_actarray[1] = 0;
  this->m_actarray[2] = 0;
  this->m_actarray[3] = 0;
  this->m_actarray[4] = 0;
  this->m_actarray[5] = 0;
  this->m_actarray[6] = 0;
  *(_DWORD *)&this->m_actarray[8] = 1065353216;
  *(_DWORD *)&this->m_actarray[12] = 0;
  this->m_pact = 0;
  *(_DWORD *)this->m_name = 0;
  *(_DWORD *)&this->m_fScale = 0;
  memset(&this->m_name[4], 0, 0xC0u);
  return 0;
}

// 0x00538D20
BOOL Actor::CompareModelName(char *String2)
{
  return !_strcmpi(String1, String2) && !_strcmpi(String1 + 32, String2 + 32);
}

// 0x00538FA0
void Actor::BuildCollisionMesh(int *pOut)
{
  int v3; // esi
  int v4; // edi
  int *v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ebp
  char *v9; // esi
  int v10; // ebx
  int *v11; // eax
  int v12; // edi
  int *v13; // esi
  int v14; // eax
  int v15; // edx
  int v16; // eax
  char v17; // al
  int v18; // ecx
  int v19; // edi
  _BYTE *v20; // esi
  char v21; // dl
  char *v22; // [esp+0x0] [ebp-0x3FC]
  int v23; // [esp+0x4] [ebp-0x3F8]
  char pActionType; // [esp+0x13] [ebp-0x3E9] BYREF
  __int16 p_WORD2; // [esp+0x14] [ebp-0x3E8] BYREF
  char v26; // [esp+0x16] [ebp-0x3E6] BYREF
  char v27; // [esp+0x17] [ebp-0x3E5] BYREF
  char String2[132]; // [esp+0x18] [ebp-0x3E4] BYREF
  Array v29; // [esp+0x9C] [ebp-0x360] BYREF
  Actor v30; // [esp+ACh] [ebp-0x350] BYREF
  char v31; // [esp+0x3E8] [ebp-0x14]
  char v32; // [esp+0x3E9] [ebp-0x13]
  int v33; // [esp+0x3EC] [ebp-0x10]
  int v34; // [esp+0x3F8] [ebp-0x4]

  LOBYTE(v29.m_pDataStart) = pActionType;
  memset(&v29.m_nSize, 0, 12);
  v34 = 0;
  ((Actor *)&v30)->InitAction(&pActionType);
  qmemcpy(String2, pOut, sizeof(String2));
  v34 = 1;
  ((Actor *)&v30.m_nPathBuffer)->InitAction(&v27);
  LOBYTE(v34) = 2;
  ((Actor *)&v30.m_vecTargetPos.y)->InitAction(&v26);
  v3 = *(_DWORD *)&this->m_actarray[8];
  v4 = *(_DWORD *)&this->m_actarray[4];
  for ( LOBYTE(v34) = 3; v4 != v3; v4 += 164 )
  {
    if ( ((Actor *)v4)->CompareModelName(String2) )
      break;
  }
  v5 = *(int **)&this->m_actarray[8];
  if ( (int *)v4 == v5 )
  {
    this->InsertAction(v5, (char **)&v30.m_pact);
    v6 = *(_DWORD *)&this->m_actarray[4];
    if ( v6 )
      v7 = (*(_DWORD *)&this->m_actarray[8] - v6) / 164;
    else
      v7 = 0;
    v4 = v6 + 164 * v7 - 164;
  }
  v8 = v4 + 132;
  v9 = ActVec_Reallocate(*(_DWORD *)(v4 + 140), *(char **)(v4 + 140), *(char **)(v4 + 136), v22, v23);
  nullsub_2(v9, *(_DWORD *)(v4 + 140));
  v10 = v4 + 148;
  *(_DWORD *)(v4 + 140) = v9;
  ((Actor *)(v4 + 148))->GetActionArrayEnd(*(_WORD **)(v4 + 152), *(__int16 **)(v4 + 156));
  qmemcpy((void *)v4, pOut, 0x84u);
  ((Actor *)(&v30.m_nUpdateMode + 4))->ClearActionArrays();
  v11 = pOut;
  v12 = 0;
  if ( pOut[55] > 0 )
  {
    v13 = pOut + 72;
    do
    {
      if ( ((PalScriptMgr *)(v13 - 16))->IsInputBlocked() )
      {
        ((Actor *)&v30.m_nInterpFrames)->ActionEntry_Assign((int)(v13 + 27));
        v14 = *(v13 - 3);
        v15 = *(v13 - 1);
        *(&v30.m_nUpdateMode + 5) = *(v13 - 2);
        *(&v30.m_nUpdateMode + 4) = v14;
        v16 = *v13;
        *(&v30.m_nUpdateMode + 6) = v15;
        *(&v30.m_nUpdateMode + 7) = v16;
        ((gbVec3D *)&v30.m_nUpdateMode + 8)->operator=(v13 + 1);
        v17 = *((_BYTE *)v13 + 17);
        v18 = v13[5];
        v31 = *((_BYTE *)v13 + 16);
        v32 = v17;
        v33 = v18;
        ActVec_Insert_char((Actor *)v8, *(char **)(v8 + 8), 1u, (char *)&v30.m_nInterpFrames);
      }
      v11 = pOut;
      ++v12;
      v13 += 224;
    }
    while ( v12 < pOut[55] );
  }
  v19 = 0;
  if ( v11[14392] > 0 )
  {
    v20 = (char *)v11 + 57873;
    do
    {
      if ( *(v20 - 128) == 2 && !*v20 )
      {
        v21 = v20[331];
        LOBYTE(p_WORD2) = *(v20 - 129);
        HIBYTE(p_WORD2) = v21;
        ActVec_Insert_word((Actor *)v10, *(_WORD **)(v10 + 8), 1u, &p_WORD2);
        v11 = pOut;
      }
      ++v19;
      v20 += 8704;
    }
    while ( v19 < v11[14392] );
  }
  LOBYTE(v34) = 1;
  ((Array *)&v30.m_vecTargetPos.y)->Free();
  ((Array *)&v30.m_nPathBuffer)->Free();
  v34 = -1;
  ((Array *)&v30)->Free();
  ((Array *)&v29)->Free();
}

// 0x005392C0
char * Actor::ActionEntry_Assign(int nVal)
{
  char *result; // eax
  int v4; // ebp
  char *v5; // esi
  char *v6; // edx
  int v7; // esi
  char *v8; // esi
  int *v9; // esi
  char *v10; // edx
  int v11; // ebx
  char *v12; // esi
  char *v13; // esi
  char *v14; // ecx
  int v15; // edx
  int nVala; // [esp+0x10] [ebp+0x4]

  result = (char *)this;
  v4 = nVal - (_DWORD)result;
  *(_DWORD *)result = *(_DWORD *)nVal;
  v5 = result + 4;
  do
  {
    *v5 = v5[v4];
    ++v5;
  }
  while ( (unsigned int)&v5[-4 - (_DWORD)result] < 0x20 );
  result[36] = *(_BYTE *)(nVal + 36);
  result[37] = *(_BYTE *)(nVal + 37);
  *((_DWORD *)result + 10) = *(_DWORD *)(nVal + 40);
  *((_DWORD *)result + 11) = *(_DWORD *)(nVal + 44);
  *((_DWORD *)result + 12) = *(_DWORD *)(nVal + 48);
  *((_DWORD *)result + 13) = *(_DWORD *)(nVal + 52);
  *((_DWORD *)result + 14) = *(_DWORD *)(nVal + 56);
  *((_DWORD *)result + 15) = *(_DWORD *)(nVal + 60);
  *((_DWORD *)result + 16) = *(_DWORD *)(nVal + 64);
  *((_DWORD *)result + 17) = *(_DWORD *)(nVal + 68);
  result[72] = *(_BYTE *)(nVal + 72);
  result[73] = *(_BYTE *)(nVal + 73);
  result[74] = *(_BYTE *)(nVal + 74);
  result[75] = *(_BYTE *)(nVal + 75);
  v6 = result + 76;
  v7 = 6;
  do
  {
    *(_DWORD *)v6 = *(_DWORD *)&v6[v4];
    v6 += 4;
    --v7;
  }
  while ( v7 );
  result[100] = *(_BYTE *)(nVal + 100);
  *((_WORD *)result + 51) = *(_WORD *)(nVal + 102);
  *((_WORD *)result + 52) = *(_WORD *)(nVal + 104);
  *((_WORD *)result + 53) = *(_WORD *)(nVal + 106);
  *((_WORD *)result + 54) = *(_WORD *)(nVal + 108);
  result[110] = *(_BYTE *)(nVal + 110);
  v8 = result + 111;
  do
  {
    *v8 = v8[v4];
    ++v8;
  }
  while ( (unsigned int)&v8[-111 - (_DWORD)result] < 0x10 );
  *((_DWORD *)result + 32) = *(_DWORD *)(nVal + 128);
  v9 = (int *)(nVal + 136);
  *((_DWORD *)result + 33) = *(_DWORD *)(nVal + 132);
  v10 = result + 140;
  nVala = 16;
  do
  {
    v11 = *v9;
    v9 += 3;
    *((_DWORD *)v10 - 1) = v11;
    *(_DWORD *)v10 = *(_DWORD *)&v10[nVal - (_DWORD)result];
    *((_DWORD *)v10 + 1) = *(v9 - 1);
    v10 += 12;
    --nVala;
  }
  while ( nVala );
  *((_WORD *)result + 164) = *(_WORD *)(nVal + 328);
  v12 = result + 330;
  do
  {
    *v12 = v12[v4];
    ++v12;
  }
  while ( (unsigned int)&v12[-330 - (_DWORD)result] < 0x20 );
  result[362] = *(_BYTE *)(nVal + 362);
  *((_DWORD *)result + 91) = *(_DWORD *)(nVal + 364);
  *((_DWORD *)result + 92) = *(_DWORD *)(nVal + 368);
  *((_DWORD *)result + 93) = *(_DWORD *)(nVal + 372);
  *((_DWORD *)result + 94) = *(_DWORD *)(nVal + 376);
  *((_DWORD *)result + 95) = *(_DWORD *)(nVal + 380);
  *((_DWORD *)result + 96) = *(_DWORD *)(nVal + 384);
  *((_DWORD *)result + 97) = *(_DWORD *)(nVal + 388);
  v13 = result + 392;
  do
  {
    *v13 = v13[v4];
    ++v13;
  }
  while ( (unsigned int)&v13[-392 - (_DWORD)result] < 8 );
  *((_DWORD *)result + 100) = *(_DWORD *)(nVal + 400);
  *((_DWORD *)result + 101) = *(_DWORD *)(nVal + 404);
  *((_DWORD *)result + 102) = *(_DWORD *)(nVal + 408);
  v14 = result + 412;
  v15 = 52;
  do
  {
    *(_DWORD *)v14 = *(_DWORD *)&v14[v4];
    v14 += 4;
    --v15;
  }
  while ( v15 );
  return result;
}

// 0x005394D0
int * Actor::ClearActionArrays()
{
  *(_DWORD *)&this->m_actarray[4] = 0;
  *(_DWORD *)&this->m_actarray[8] = 0;
  *(_DWORD *)&this->m_actarray[12] = 0;
  this->m_pact = 0;
  *(_DWORD *)this->m_name = 0;
  *(_DWORD *)&this->m_name[4] = 0;
  return (int *)this->m_actarray;
}

// 0x00539540
int Actor::AddActionByName(const char *pszName, const char *pszName2, int nVal)
{
  int v4; // ebp
  int v6; // edi
  int i; // esi
  int v8; // ebx
  unsigned int j; // edi
  int v10; // edi
  char pActionType; // [esp+0x13] [ebp-B1h] BYREF
  char String2[32]; // [esp+0x14] [ebp-B0h] BYREF
  char v14[104]; // [esp+0x34] [ebp-0x90] BYREF
  void *v15; // [esp+0x9C] [ebp-0x28]
  int v16; // [esp+A0h] [ebp-0x24]
  int v17; // [esp+A4h] [ebp-0x20]
  char v18; // [esp+A8h] [ebp-0x1C] BYREF
  void *Block; // [esp+ACh] [ebp-0x18]
  int v20; // [esp+B0h] [ebp-0x14]
  int v21; // [esp+B4h] [ebp-0x10]
  int v22; // [esp+C0h] [ebp-0x4]

  v4 = 0;
  v14[100] = pActionType;
  v15 = 0;
  v16 = 0;
  v17 = 0;
  v22 = 0;
  ((Actor *)&v18)->InitAction(&pActionType);
  strcpy(String2, pszName);
  strcpy(v14, pszName2);
  v6 = *(_DWORD *)&this->m_actarray[8];
  for ( i = *(_DWORD *)&this->m_actarray[4]; i != v6; i += 164 )
  {
    if ( ((Actor *)i)->CompareModelName(String2) )
      break;
  }
  if ( i != *(_DWORD *)&this->m_actarray[8] )
  {
    v8 = *(_DWORD *)(i + 136);
    for ( j = 0; v8 && j < (*(_DWORD *)(i + 140) - v8) / 656; ++j )
    {
      if ( *(unsigned __int8 *)(*(_DWORD *)(i + 136) + v4) == nVal )
      {
        v10 = *(_DWORD *)(i + 136) + 656 * j;
        operator delete(Block);
        Block = 0;
        v20 = 0;
        v21 = 0;
        operator delete(v15);
        return v10;
      }
      v4 += 656;
    }
  }
  operator delete(Block);
  Block = 0;
  v20 = 0;
  v21 = 0;
  operator delete(v15);
  return 0;
}

// 0x00539700
void Actor::GetAnimDataBuffer(void **Buffer, int Stream)
{
  FILE *v3; // ebx
  float x; // eax
  float i; // edi
  int m_nAnimBuffer; // eax
  char *j; // edi
  int Buffera; // [esp+0xC] [ebp-0x4] BYREF

  v3 = (FILE *)Buffer;
  if ( Buffer )
  {
    fwrite(this, 0x84u, 1u, (FILE *)Buffer);
    x = this->m_vecBonePos.x;
    if ( x == 0.0 )
      Buffer = 0;
    else
      Buffer = (void **)((LODWORD(this->m_vecBonePos.y) - LODWORD(x)) / 656);
    fwrite(&Buffer, 4u, 1u, v3);
    if ( (int)Buffer > 0 )
    {
      for ( i = this->m_vecBonePos.x; LODWORD(i) != LODWORD(this->m_vecBonePos.y); LODWORD(i) += 656 )
        fwrite((const void *)LODWORD(i), 0x290u, 1u, v3);
    }
    m_nAnimBuffer = this->m_nAnimBuffer;
    if ( m_nAnimBuffer )
      Buffera = (this->m_nParticleBuffer - m_nAnimBuffer) >> 1;
    else
      Buffera = 0;
    fwrite(&Buffera, 4u, 1u, v3);
    if ( Buffera > 0 )
    {
      for ( j = (char *)this->m_nAnimBuffer; j != (char *)this->m_nParticleBuffer; j += 2 )
        fwrite(j, 2u, 1u, v3);
    }
  }
}

// 0x005399E0
void Actor::IterateActiveActors()
{
  Actor *v2; // ebp
  Actor *v3; // ebx
  Actor *i; // esi

  v2 = *(Actor **)&this->m_actarray[4];
  v3 = *(Actor **)&this->m_actarray[8];
  for ( i = v2; i != v3; i = (Actor *)((char *)i + 164) )
    ((Actor *)i)->ClearAllocBuffers();
  *(_DWORD *)&this->m_actarray[8] = v2;
}

// 0x00539A90
char Actor::SearchAnimByIndex(char *String1, char *pszBuf)
{
  unsigned int v3; // ebp
  int i; // ebx
  int v6; // eax
  int v7; // esi

  v3 = 0;
  for ( i = 0; ; i += 64 )
  {
    v6 = *(_DWORD *)this->m_name;
    if ( !v6 || v3 >= (*(_DWORD *)&this->m_name[4] - v6) >> 6 )
      break;
    v7 = i + v6;
    if ( !_strcmpi(String1, (const char *)(i + v6)) && !_strcmpi(pszBuf, (const char *)(v7 + 32)) )
      return 1;
    ++v3;
  }
  return 0;
}

// 0x00539AF0
void Actor::RegisterAnim(char *pszName, char *pszBuf)
{
  gbActor **p_m_pact; // ebx
  char *v5; // eax
  char *v6; // ebp
  gbActor *v7; // edx
  unsigned int v8; // ecx
  int v9; // eax
  unsigned int v10; // esi
  int v11; // eax
  char *v12; // edi
  char *v13; // eax
  gbActor *v14; // eax
  int v15; // ecx
  char *v16; // eax
  char *v17; // edi
  char pData[64]; // [esp+0x10] [ebp-0x40] BYREF
  char *String1; // [esp+0x54] [ebp+0x4]
  char *pszBufa; // [esp+0x58] [ebp+0x8]

  if ( pszName && pszBuf && strlen(pszName) && strlen(pszBuf) && !this->SearchAnimByIndex(pszName, pszBuf) )
  {
    memset(pData, 0, sizeof(pData));
    p_m_pact = &this->m_pact;
    strcpy(pData, pszName);
    strcpy(&pData[32], pszBuf);
    v5 = (char *)p_m_pact[2];
    v6 = v5;
    if ( ((char *)p_m_pact[3] - v5) >> 6 )
    {
      ((Actor *)p_m_pact)->CopyBufferBlocks(v5, v5, v5 + 64);
      ((Actor *)p_m_pact)->CopyIfValid((char *)p_m_pact[2], (char *)(1 - (((char *)p_m_pact[2] - v6) >> 6)), pData);
      v16 = (char *)p_m_pact[2];
      if ( v6 == v16 )
      {
        p_m_pact[2] = (gbActor *)((char *)p_m_pact[2] + 64);
      }
      else
      {
        do
        {
          v17 = v6;
          v6 += 64;
          qmemcpy(v17, pData, 0x40u);
        }
        while ( v6 != v16 );
        p_m_pact[2] = (gbActor *)((char *)p_m_pact[2] + 64);
      }
    }
    else
    {
      v7 = p_m_pact[1];
      if ( !v7 || (v8 = (v5 - (char *)v7) >> 6, v8 <= 1) )
        v8 = 1;
      if ( v7 )
        v9 = (v5 - (char *)v7) >> 6;
      else
        v9 = 0;
      v10 = v9 + v8;
      v11 = v9 + v8;
      if ( v11 < 0 )
        v11 = 0;
      pszBufa = (char *)operator new(v11 << 6);
      v12 = pszBufa;
      v13 = (char *)p_m_pact[1];
      String1 = v13;
      if ( v13 != v6 )
      {
        while ( 1 )
        {
          Actor_CopyConstruct_40(v12, v13);
          v12 += 64;
          String1 += 64;
          if ( String1 == v6 )
            break;
          v13 = String1;
        }
      }
      ((Actor *)p_m_pact)->CopyIfValid(v12, (char *)1, pData);
      ((Actor *)p_m_pact)->CopyBufferBlocks(v6, (char *)p_m_pact[2], v12 + 64);
      nullsub_2(p_m_pact[1], p_m_pact[2]);
      operator delete(p_m_pact[1]);
      v14 = p_m_pact[1];
      p_m_pact[3] = (gbActor *)&pszBufa[64 * v10];
      if ( v14 )
      {
        v15 = (((char *)p_m_pact[2] - (char *)v14) >> 6) + 1;
        p_m_pact[1] = (gbActor *)pszBufa;
        p_m_pact[2] = (gbActor *)&pszBufa[64 * v15];
      }
      else
      {
        p_m_pact[1] = (gbActor *)pszBufa;
        p_m_pact[2] = (gbActor *)(pszBufa + 64);
      }
    }
  }
}

// 0x00539D60
int * Actor::ClearAllActions()
{
  int *result; // eax
  int v2; // ebp
  Actor *v3; // edi
  Actor *v4; // esi

  result = (int *)this;
  *(_DWORD *)&this->m_name[4] = *(_DWORD *)this->m_name;
  v2 = *(_DWORD *)&this->m_actarray[4];
  v3 = *(Actor **)&this->m_actarray[8];
  v4 = (Actor *)v2;
  if ( (Actor *)v2 != v3 )
  {
    do
    {
      ((Actor *)v4)->ClearAllocBuffers();
      v4 = (Actor *)((char *)v4 + 164);
    }
    while ( v4 != v3 );
    result = (int *)this;
  }
  result[2] = v2;
  result[10] = result[9];
  return result;
}

// 0x00539E70
char * Actor::InsertAnimFrame(float fVal)
{
  float m_fTransitionSpeed; // eax
  float *p_m_fMoveRange; // esi
  gbVec3D *v4; // edi
  char *m_pAllocBuf; // edx
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // eax
  char *v9; // eax
  int *v10; // ebp
  int i; // ebx
  int v12; // eax
  char *result; // eax
  int v14; // ecx
  gbVec3D *v15; // eax
  char *v16; // [esp+0x8] [ebp-0x8]
  int v17; // [esp+0xC] [ebp-0x4]

  m_fTransitionSpeed = this->m_fTransitionSpeed;
  p_m_fMoveRange = &this->m_fMoveRange;
  v4 = (gbVec3D *)LODWORD(m_fTransitionSpeed);
  if ( (LODWORD(this->m_fTransitionPos) - LODWORD(m_fTransitionSpeed)) >> 2 )
  {
    Vec3D_CopyStruct(
      (gbVec3D *)LODWORD(m_fTransitionSpeed),
      (gbVec3D *)LODWORD(m_fTransitionSpeed),
      (gbVec3D *)(LODWORD(m_fTransitionSpeed) + 4));
    ((Actor *)p_m_fMoveRange)->StoreParam(*((_DWORD *)p_m_fMoveRange + 2), 1 - ((*((_DWORD *)p_m_fMoveRange + 2) - (int)v4) >> 2));
    v15 = (gbVec3D *)*((_DWORD *)p_m_fMoveRange + 2);
    if ( v4 == v15 )
    {
      result = (char *)(*((_DWORD *)p_m_fMoveRange + 2) + 4);
      *((_DWORD *)p_m_fMoveRange + 2) = result;
    }
    else
    {
      do
      {
        v4->x = fVal;
        v4 = (gbVec3D *)((char *)v4 + 4);
      }
      while ( v4 != v15 );
      result = (char *)(*((_DWORD *)p_m_fMoveRange + 2) + 4);
      *((_DWORD *)p_m_fMoveRange + 2) = result;
    }
  }
  else
  {
    m_pAllocBuf = this->m_pAllocBuf;
    if ( !m_pAllocBuf || (v6 = (LODWORD(m_fTransitionSpeed) - (int)m_pAllocBuf) >> 2, v6 <= 1) )
      v6 = 1;
    if ( m_pAllocBuf )
      v7 = (LODWORD(m_fTransitionSpeed) - (int)m_pAllocBuf) >> 2;
    else
      v7 = 0;
    v8 = v6 + v7;
    v17 = v8;
    if ( v8 < 0 )
      v8 = 0;
    v9 = (char *)operator new(4 * v8);
    v10 = (int *)*((_DWORD *)p_m_fMoveRange + 1);
    v16 = v9;
    for ( i = (int)v9; v10 != (int *)v4; i += 4 )
      AssignInt((int *)i, v10++);
    ((Actor *)p_m_fMoveRange)->StoreParam(i, 1);
    Vec3D_CopyStruct(v4, *((gbVec3D **)p_m_fMoveRange + 2), (gbVec3D *)(i + 4));
    nullsub_2(*((_DWORD *)p_m_fMoveRange + 1), *((_DWORD *)p_m_fMoveRange + 2));
    operator delete(*((void **)p_m_fMoveRange + 1));
    v12 = *((_DWORD *)p_m_fMoveRange + 1);
    *((_DWORD *)p_m_fMoveRange + 3) = &v16[4 * v17];
    if ( v12 )
    {
      v14 = *((_DWORD *)p_m_fMoveRange + 2);
      *((_DWORD *)p_m_fMoveRange + 1) = v16;
      result = &v16[4 * ((v14 - v12) >> 2) + 4];
      *((_DWORD *)p_m_fMoveRange + 2) = result;
    }
    else
    {
      *((_DWORD *)p_m_fMoveRange + 1) = v16;
      *((_DWORD *)p_m_fMoveRange + 2) = v16 + 4;
      return v16 + 4;
    }
  }
  return result;
}

// 0x0053A020
char Actor::IterateAllocBuffer(int nVal)
{
  char *m_pAllocBuf; // edx
  unsigned int i; // eax

  m_pAllocBuf = this->m_pAllocBuf;
  for ( i = 0; m_pAllocBuf && i < (LODWORD(this->m_fTransitionSpeed) - (int)m_pAllocBuf) >> 2; ++i )
  {
    if ( *(_DWORD *)&this->m_pAllocBuf[4 * i] == nVal )
      return 1;
  }
  return 0;
}

// 0x0053A060
int * Actor::InitAction(_BYTE *pActionType)
{
  this->m_actarray[0] = *pActionType;
  *(_DWORD *)&this->m_actarray[4] = 0;
  *(_DWORD *)&this->m_actarray[8] = 0;
  *(_DWORD *)&this->m_actarray[12] = 0;
  return (int *)this->m_actarray;
}

// 0x0053A080
_WORD * Actor::GetActionArrayEnd(_WORD *p_WORD, __int16 *pnVal)
{
  __int16 *v3; // edx
  _WORD *result; // eax
  __int16 *v5; // edi
  _WORD *v6; // esi
  __int16 v7; // bx

  v3 = pnVal;
  result = p_WORD;
  v5 = *(__int16 **)&this->m_actarray[8];
  v6 = p_WORD;
  if ( pnVal != v5 )
  {
    do
    {
      v7 = *v3++;
      *v6++ = v7;
    }
    while ( v3 != v5 );
  }
  *(_DWORD *)&this->m_actarray[8] = v6;
  return result;
}

// 0x0053A0C0
int Actor::InsertAction(int *p_DWORD, char **nY)
{
  int v5; // ebx
  int v6; // ecx
  int v7; // ebp
  unsigned int v8; // ebp
  int v9; // edx
  unsigned int v10; // eax
  char *v11; // eax
  int *v12; // ebx
  int i; // ebp
  int ActionCount; // eax
  char **v16; // [esp-0xC] [ebp-0x24]
  char **v17; // [esp+0x0] [ebp-0x18]
  unsigned int v18; // [esp+0x10] [ebp-0x8]
  char *v19; // [esp+0x14] [ebp-0x4]
  int *p_DWORDa; // [esp+0x1C] [ebp+0x4]

  v5 = *(_DWORD *)&this->m_actarray[4];
  v6 = *(_DWORD *)&this->m_actarray[8];
  v7 = ((int)p_DWORD - v5) / 164;
  p_DWORDa = (int *)v7;
  if ( (*(_DWORD *)&this->m_actarray[12] - v6) / 164 )
  {
    if ( (v6 - (int)p_DWORD) / 164 )
    {
      this->FindMatchingEntry(v6 - 164, v6, v6);
      ActVec_UninitFill((int)p_DWORD, *(_DWORD *)&this->m_actarray[8] - 164, *(_DWORD *)&this->m_actarray[8], v17);
      ActVec_UninitCopy2((int)p_DWORD, p_DWORD + 41, (int *)nY, v16);
    }
    else
    {
      this->FindMatchingEntry((int)p_DWORD, v6, (int)(p_DWORD + 41));
      this->SetVideoRegions(*(_DWORD *)&this->m_actarray[8], 1 - (*(_DWORD *)&this->m_actarray[8] - (int)p_DWORD) / 164, (int)nY);
      ActVec_UninitCopy2((int)p_DWORD, *(int **)&this->m_actarray[8], (int *)nY, v17);
    }
    *(_DWORD *)&this->m_actarray[8] += 164;
  }
  else
  {
    if ( !v5 || (v8 = (v6 - v5) / 164, v8 <= 1) )
      v8 = 1;
    if ( v5 )
      v9 = (v6 - v5) / 164;
    else
      v9 = 0;
    v10 = v9 + v8;
    v18 = v9 + v8;
    if ( (int)(v9 + v8) < 0 )
      v10 = 0;
    v11 = (char *)operator new(164 * v10);
    v12 = *(int **)&this->m_actarray[4];
    v19 = v11;
    for ( i = (int)v11; v12 != p_DWORD; i += 164 )
    {
      ((VideoPlayer *)i)->SetRegion((int)v12);
      v12 += 41;
    }
    ((VideoPlayer *)i)->SetRegion((int)nY);
    this->FindMatchingEntry((int)p_DWORD, *(_DWORD *)&this->m_actarray[8], i + 164);
    this->DestroyActionRange(*(_DWORD *)&this->m_actarray[4], *(_DWORD *)&this->m_actarray[8]);
    operator delete(*(void **)&this->m_actarray[4]);
    *(_DWORD *)&this->m_actarray[12] = &v19[164 * v18];
    ActionCount = this->GetActionCount();
    v7 = (int)p_DWORDa;
    *(_DWORD *)&this->m_actarray[4] = v19;
    *(_DWORD *)&this->m_actarray[8] = &v19[164 * ActionCount + 164];
  }
  return *(_DWORD *)&this->m_actarray[4] + 164 * v7;
}

// 0x0053A2E0
int Actor::GetActionCount()
{
  int result; // eax

  result = *(_DWORD *)&this->m_actarray[4];
  if ( result )
    return (*(_DWORD *)&this->m_actarray[8] - result) / 164;
  return result;
}

// 0x0053A310
void Actor::DestroyActionRange(int nVal, int nVal2)
{
  Actor *i; // esi

  for ( i = (Actor *)nVal; i != (Actor *)nVal2; i = (Actor *)((char *)i + 164) )
    ((Actor *)i)->ClearAllocBuffers();
}

// 0x0053A670
int * Actor::CopyActionData(int nVal)
{
  *(_DWORD *)this->m_actarray = *(_DWORD *)nVal;
  *(_DWORD *)&this->m_actarray[4] = *(_DWORD *)(nVal + 4);
  *(_DWORD *)&this->m_actarray[8] = *(_DWORD *)(nVal + 8);
  *(_DWORD *)&this->m_actarray[12] = *(_DWORD *)(nVal + 12);
  this->m_pact = *(gbActor **)(nVal + 16);
  *(_QWORD *)this->m_name = *(_QWORD *)(nVal + 20);
  LOBYTE(this->m_fMoveSpeed) = *(_BYTE *)(nVal + 28);
  BYTE1(this->m_fMoveSpeed) = *(_BYTE *)(nVal + 29);
  this->m_fMoveRange = *(float *)(nVal + 32);
  return (int *)this->m_actarray;
}

// 0x0053AF30
int Actor::FindMatchingEntry(int nY, int nVal, int nX)
{
  int v4; // esi
  int v5; // edi

  v4 = nY;
  if ( nY == nVal )
    return nX;
  v5 = nX;
  do
  {
    ((VideoPlayer *)v5)->SetRegion(v4);
    v4 += 164;
    v5 += 164;
  }
  while ( v4 != nVal );
  return v5;
}

// 0x0053AF70
void Actor::SetVideoRegions(int nX, int nVal, int nY)
{
  int i; // edi

  for ( i = nVal; i; --i )
  {
    ((VideoPlayer *)nX)->SetRegion(nY);
    nX += 164;
  }
}

// 0x0053AFA0
char * Actor::CopyBufferBlocks(char *pszDst, char *pszSrc, char *pszBuf3)
{
  char *v4; // edx
  char *result; // eax

  v4 = pszDst;
  if ( pszDst == pszSrc )
    return pszBuf3;
  result = pszBuf3;
  do
  {
    if ( result )
      qmemcpy(result, v4, 0x40u);
    v4 += 64;
    result += 64;
  }
  while ( v4 != pszSrc );
  return result;
}

// 0x0053AFE0
char * Actor::CopyIfValid(char *pszBuf, char *pszBuf2, const void *pData)
{
  char *result; // eax
  char *v5; // edx

  result = pszBuf2;
  if ( pszBuf2 )
  {
    v5 = pszBuf2;
    result = pszBuf;
    do
    {
      if ( result )
        qmemcpy(result, pData, 0x40u);
      result += 64;
      --v5;
    }
    while ( v5 );
  }
  return result;
}

// 0x0053B230
int Actor::GetCount()
{
  int result; // eax

  result = *(_DWORD *)&this->m_actarray[4];
  if ( result )
    return (*(_DWORD *)&this->m_actarray[8] - result) / 656;
  return result;
}

// 0x0053B260
char * Actor::CompareBuffers(char *pszBuf, char *pszBuf2, char *pszBuf3)
{
  char *v4; // edx
  char *result; // eax

  v4 = pszBuf;
  if ( pszBuf == pszBuf2 )
    return pszBuf3;
  result = pszBuf3;
  do
  {
    if ( result )
      qmemcpy(result, v4, 0x290u);
    v4 += 656;
    result += 656;
  }
  while ( v4 != pszBuf2 );
  return result;
}

// 0x0053B2A0
int * Actor::SelectPointer(int *pnVal2, int *pnVal3)
{
  int *v3; // ecx
  int *result; // eax
  int v5; // esi

  v3 = pnVal;
  if ( pnVal == pnVal2 )
    return pnVal3;
  result = pnVal3;
  do
  {
    v5 = *v3++;
    *result++ = v5;
  }
  while ( v3 != pnVal2 );
  return result;
}

// 0x0053B890
char * Actor::SetCurrentAction(int nVal)
{
  int v4; // ebx
  char *v5; // eax
  int *p_m_nCachedA; // eax
  int v7; // ecx
  _BYTE *v8; // eax
  int v9; // ecx
  gbVec3D *p_m_vecBonePos; // ebp
  signed __int16 *v11; // eax
  float *p_m_fActionAssignParam; // eax
  float *p_m_fFacingAngle; // eax
  int v14; // ecx
  int v16; // [esp+0x10] [ebp-0x4]
  int nVala; // [esp+0x18] [ebp+0x4]

  v4 = nVal - (_DWORD)this;
  *(_DWORD *)this->m_actarray = *(_DWORD *)nVal;
  v5 = &this->m_actarray[4];
  do
  {
    *v5 = v5[v4];
    ++v5;
  }
  while ( (unsigned int)&v5[-4 - (_DWORD)this] < 0x20 );
  LOBYTE(this->m_pAllocBuf) = *(_BYTE *)(nVal + 36);
  BYTE1(this->m_pAllocBuf) = *(_BYTE *)(nVal + 37);
  this->m_fTransitionSpeed = *(float *)(nVal + 40);
  this->m_fTransitionPos = *(float *)(nVal + 44);
  this->m_nRoleParam0 = *(_DWORD *)(nVal + 48);
  this->m_fRoleParam1 = *(float *)(nVal + 52);
  this->m_fRoleParam = *(float *)(nVal + 56);
  this->m_fRoleParam2 = *(float *)(nVal + 60);
  this->m_fRoleParam3 = *(float *)(nVal + 64);
  this->m_nRoleParam2 = *(_DWORD *)(nVal + 68);
  this->m_pRoleParam3 = *(char **)(nVal + 72);
  p_m_nCachedA = &this->m_nCachedA;
  v7 = 6;
  do
  {
    *p_m_nCachedA = *(int *)((char *)p_m_nCachedA + v4);
    ++p_m_nCachedA;
    --v7;
  }
  while ( v7 );
  LOBYTE(this->m_szText) = *(_BYTE *)(nVal + 100);
  HIWORD(this->m_szText) = *(_WORD *)(nVal + 102);
  *((_WORD *)&this->m_szText + 2) = *(_WORD *)(nVal + 104);
  *((_WORD *)&this->m_szText + 3) = *(_WORD *)(nVal + 106);
  *((_WORD *)&this->m_szText + 4) = *(_WORD *)(nVal + 108);
  *((_BYTE *)&this->m_szText + 10) = *(_BYTE *)(nVal + 110);
  v8 = (char *)&this->m_szText + 11;
  do
  {
    *v8 = v8[v4];
    ++v8;
  }
  while ( (unsigned int)&v8[-111 - (_DWORD)this] < 0x10 );
  this->m_nAnimParam0 = *(_DWORD *)(nVal + 128);
  v9 = nVal - (_DWORD)this;
  this->m_nAnimParam1 = *(_DWORD *)(nVal + 132);
  p_m_vecBonePos = &this->m_vecBonePos;
  v16 = nVal - (_DWORD)this;
  nVala = 16;
  while ( 1 )
  {
    ((gbVec3D *)p_m_vecBonePos)->operator=((char *)p_m_vecBonePos + v9);
    ++p_m_vecBonePos;
    if ( !--nVala )
      break;
    v9 = v16;
  }
  this->m_nAnimState = *(_WORD *)(nVal + 328);
  v11 = &this->m_nAnimState + 1;
  do
  {
    *(_BYTE *)v11 = *((_BYTE *)v11 + v4);
    v11 = (signed __int16 *)((char *)v11 + 1);
  }
  while ( (unsigned int)v11 - 330 - (unsigned int)this < 0x20 );
  BYTE2(this->m_nHandleEvent) = *(_BYTE *)(nVal + 362);
  ((gbVec3D *)&this->m_vecPos)->operator=(nVal + 364);
  ((gbVec3D *)&this->m_vecRot)->operator=(nVal + 376);
  this->m_nCloneParam = *(_DWORD *)(nVal + 388);
  p_m_fActionAssignParam = &this->m_fActionAssignParam;
  do
  {
    *(_BYTE *)p_m_fActionAssignParam = *((_BYTE *)p_m_fActionAssignParam + v4);
    p_m_fActionAssignParam = (float *)((char *)p_m_fActionAssignParam + 1);
  }
  while ( (unsigned int)p_m_fActionAssignParam - 392 - (unsigned int)this < 8 );
  this->m_nCloneState = *(_DWORD *)(nVal + 400);
  this->m_nCloneFlag1 = *(_DWORD *)(nVal + 404);
  this->m_nCloneFlag2 = *(_DWORD *)(nVal + 408);
  p_m_fFacingAngle = &this->m_fFacingAngle;
  v14 = 52;
  do
  {
    *p_m_fFacingAngle = *(float *)((char *)p_m_fFacingAngle + v4);
    ++p_m_fFacingAngle;
    --v14;
  }
  while ( v14 );
  *(_DWORD *)&this->m_curact[35] = *(_DWORD *)(nVal + 620);
  *(_DWORD *)&this->m_curact[39] = *(_DWORD *)(nVal + 624);
  *(_DWORD *)&this->m_curact[43] = *(_DWORD *)(nVal + 628);
  this->m_fDirX = *(float *)(nVal + 632);
  ((gbVec3D *)&this->m_fDirY)->operator=(nVal + 636);
  LOBYTE(this->m_fNormY) = *(_BYTE *)(nVal + 648);
  BYTE1(this->m_fNormY) = *(_BYTE *)(nVal + 649);
  this->m_fNormZ = *(float *)(nVal + 652);
  return this->m_actarray;
}

// 0x0053BAE0
int * Actor::ActArray_Assign(int *p_DWORD)
{
  Actor *v3; // esi
  int v4; // edi
  unsigned int v5; // ebp
  Actor *v6; // ecx
  unsigned int v7; // edx
  int v8; // esi
  Actor *v9; // ebp
  int v10; // eax
  int v11; // edx
  unsigned int v13; // ebp
  unsigned int v14; // edx
  int v15; // edx
  Actor *v16; // ebp
  char *j; // esi
  int v18; // ebp
  int *v19; // ecx
  char *v20; // eax
  char *k; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  char *v27; // eax
  int v28; // ebp
  char *v29; // edx
  char *i; // eax
  int *p_DWORDa; // [esp+0x18] [ebp+0x4]
if ( this == (Actor *)p_DWORD )
    return (int *)this->m_actarray;
  v4 = p_DWORD[1];
  if ( v4 )
    v5 = (p_DWORD[2] - v4) / 656;
  else
    v5 = 0;
  v6 = *(Actor **)&this->m_actarray[4];
  if ( v6 )
    v7 = (*(_DWORD *)&this->m_actarray[8] - (int)v6) / 656;
  else
    v7 = 0;
  if ( v5 <= v7 )
  {
    v8 = p_DWORD[1];
    p_DWORDa = (int *)p_DWORD[2];
    v9 = v6;
    if ( (int *)v4 != p_DWORDa )
    {
      do
      {
        ((Actor *)v9)->SetCurrentAction(v8);
        v8 += 656;
        v9 = (Actor *)((char *)v9 + 656);
      }
      while ( (int *)v8 != p_DWORDa );
    }
    v10 = p_DWORD[1];
    if ( v10 )
      v11 = (p_DWORD[2] - v10) / 656;
    else
      v11 = 0;
    *(_DWORD *)&this->m_actarray[8] = *(_DWORD *)&this->m_actarray[4] + 656 * v11;
    return (int *)this->m_actarray;
  }
  if ( v4 )
    v13 = (p_DWORD[2] - v4) / 656;
  else
    v13 = 0;
  if ( v6 )
    v14 = (*(_DWORD *)&this->m_actarray[12] - (int)v6) / 656;
  else
    v14 = 0;
  if ( v13 > v14 )
  {
    operator delete(*(void **)&this->m_actarray[4]);
    v24 = p_DWORD[1];
    if ( v24 )
      v25 = (p_DWORD[2] - v24) / 656;
    else
      v25 = 0;
    v26 = v25;
    if ( v25 < 0 )
      v26 = 0;
    v27 = (char *)operator new(656 * v26);
    *(_DWORD *)&this->m_actarray[4] = v27;
    v28 = p_DWORD[2];
    v29 = v27;
    for ( i = (char *)p_DWORD[1]; i != (char *)v28; v29 += 656 )
    {
      if ( v29 )
      {
        qmemcpy(v29, i, 0x290u);
}
      i += 656;
    }
    *(_DWORD *)&this->m_actarray[8] = v29;
    *(_DWORD *)&this->m_actarray[12] = v29;
    return (int *)this->m_actarray;
  }
  if ( v6 )
    v15 = (*(_DWORD *)&this->m_actarray[8] - (int)v6) / 656;
  else
    v15 = 0;
  v16 = *(Actor **)&this->m_actarray[4];
  for ( j = (char *)(v4 + 656 * v15); (char *)v4 != j; v16 = (Actor *)((char *)v16 + 656) )
  {
    ((Actor *)v16)->SetCurrentAction(v4);
    v4 += 656;
  }
  v18 = p_DWORD[2];
  v19 = (int *)this;
  v20 = j;
  for ( k = *(char **)&this->m_actarray[8]; v20 != (char *)v18; k += 656 )
  {
    if ( k )
    {
      qmemcpy(k, v20, 0x290u);
      v19 = (int *)this;
    }
    v20 += 656;
  }
  v22 = p_DWORD[1];
  if ( v22 )
    v23 = (p_DWORD[2] - v22) / 656;
  else
    v23 = 0;
  v19[2] = v19[1] + 656 * v23;
  return v19;
}

// 0x0053BD30
int * Actor::BoneIndexVec_Assign(int *pnVal)
{
  __int16 *v3; // eax
  unsigned int v4; // edi
  _WORD *v5; // edx
  unsigned int v6; // ecx
  int i; // ecx
  __int16 v8; // di
  int v9; // eax
  int v10; // ecx
  unsigned int v12; // edi
  unsigned int v13; // ecx
  int v14; // ecx
  __int16 *k; // ecx
  __int16 v16; // di
  int v17; // edi
  __int16 *v18; // edx
  __int16 *m; // eax
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  _WORD *v23; // eax
  int v24; // edx
  _WORD *v25; // ecx
  _WORD *j; // eax

  if ( this == (Actor *)pnVal )
    return (int *)this->m_actarray;
  v3 = (__int16 *)pnVal[1];
  if ( v3 )
    v4 = (pnVal[2] - (int)v3) >> 1;
  else
    v4 = 0;
  v5 = *(_WORD **)&this->m_actarray[4];
  if ( v5 )
    v6 = (*(_DWORD *)&this->m_actarray[8] - (int)v5) >> 1;
  else
    v6 = 0;
  if ( v4 <= v6 )
  {
    for ( i = pnVal[2]; v3 != (__int16 *)i; ++v5 )
    {
      v8 = *v3++;
      *v5 = v8;
    }
    v9 = pnVal[1];
    if ( v9 )
      v10 = *(_DWORD *)&this->m_actarray[4] + 2 * ((pnVal[2] - v9) >> 1);
    else
      v10 = *(_DWORD *)&this->m_actarray[4];
    *(_DWORD *)&this->m_actarray[8] = v10;
    return (int *)this->m_actarray;
  }
  if ( v3 )
    v12 = (pnVal[2] - (int)v3) >> 1;
  else
    v12 = 0;
  if ( v5 )
    v13 = (*(_DWORD *)&this->m_actarray[12] - (int)v5) >> 1;
  else
    v13 = 0;
  if ( v12 > v13 )
  {
    operator delete(*(void **)&this->m_actarray[4]);
    v21 = pnVal[1];
    if ( v21 )
      v22 = (pnVal[2] - v21) >> 1;
    else
      v22 = 0;
    if ( v22 < 0 )
      v22 = 0;
    v23 = operator new(2 * v22);
    *(_DWORD *)&this->m_actarray[4] = v23;
    v24 = pnVal[2];
    v25 = v23;
    for ( j = (_WORD *)pnVal[1]; j != (_WORD *)v24; ++v25 )
    {
      if ( v25 )
        *v25 = *j;
      ++j;
    }
    *(_DWORD *)&this->m_actarray[8] = v25;
    *(_DWORD *)&this->m_actarray[12] = v25;
    return (int *)this->m_actarray;
  }
  if ( v5 )
    v14 = (*(_DWORD *)&this->m_actarray[8] - (int)v5) >> 1;
  else
    v14 = 0;
  for ( k = &v3[v14]; v3 != k; ++v5 )
  {
    v16 = *v3++;
    *v5 = v16;
  }
  v17 = pnVal[2];
  v18 = *(__int16 **)&this->m_actarray[8];
  for ( m = k; m != (__int16 *)v17; ++v18 )
  {
    if ( v18 )
      *v18 = *m;
    ++m;
  }
  v20 = pnVal[1];
  if ( v20 )
    *(_DWORD *)&this->m_actarray[8] = *(_DWORD *)&this->m_actarray[4] + 2 * ((pnVal[2] - v20) >> 1);
  else
    *(_DWORD *)&this->m_actarray[8] = *(_DWORD *)&this->m_actarray[4];
  return (int *)this->m_actarray;
}

// 0x0053BEB0
int Actor::GetActionCountEx()
{
  int result; // eax

  result = *(_DWORD *)&this->m_actarray[4];
  if ( result )
    return (*(_DWORD *)&this->m_actarray[12] - result) / 656;
  return result;
}
