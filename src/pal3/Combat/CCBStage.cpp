#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStage.h"
#include "pal3/gen/C3DSpark.h"
#include "pal3/gen/CCBCamControl.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/CCBStageScene.h"
#include "pal3/gen/CCBStageShadow.h"
#include "pal3/gen/CCBSystem.h"
#include "pal3/gen/CCCTData.h"
#include "pal3/gen/CEffMgr.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/Combat.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/InputSystem.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/NPC.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/SceneMgr.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_4C5C20(...);
int sub_4DF6B0(...);
int sub_4DF700(...);
int sub_4DF710(...);
int sub_4DFA10(...);
int sub_4DFF90(...);
int sub_4DFFF0(...);
int sub_4EED60(...);
int sub_4F06C0(...);
int sub_4F6CD0(...);
int sub_500840(...);
int sub_5009C0(...);
int sub_500AD0(...);
int sub_503680(...);
int sub_503AE0(...);
int sub_503FA0(...);
int sub_504510(...);
int sub_504540(...);
int sub_5049F0(...);
int sub_504A80(...);
int sub_508460(...);
int sub_50A4B0(...);
int sub_50E160(...);
int sub_50E360(...);
int sub_50E550(...);
int sub_50EB00(...);
int sub_50FD00(...);
int sub_511E20(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aCamFovF[];
extern char aCamXFYFZF[];
extern char aCamYawFPitchFR[];
extern char aDProjectPal3Co_5[];
extern char aEnemysneakatta[];
extern char aMoney[];
extern char aNewFailedAtCre[];
extern char aOver[];
extern char aWe013[];
extern char aWesneakattacke[];
extern char aWitch[];
extern unsigned char byte_17A9927;
extern unsigned char byte_17AA870;
extern unsigned char byte_17AA89C;
extern unsigned char byte_17AA91C;
extern unsigned char byte_17AA920;
extern unsigned char byte_17AAA2C;
extern unsigned char byte_17AB6E4;
extern unsigned char byte_5DB6C4;
extern int dword_17A990C;
extern int dword_17AA880;
extern int dword_17AA884;
extern int dword_17AA888;
extern int dword_17AA890;
extern int dword_17AA894;
extern int dword_17AA898;
extern int dword_17AA910;
extern int dword_17AA914;
extern int dword_17AA918;
extern int dword_17AAA20;
extern int dword_17AAA24;
extern int dword_17AAA28;
extern int dword_17AAD3C;
extern int dword_17AB6B8;
extern int dword_17AB6BC;
extern int dword_17AB6C0;
extern int dword_17AB6C8;
extern int dword_17AB6CC;
extern int dword_17AB6D0;
extern int dword_17AB6D8;
extern int dword_17AB6DC;
extern int dword_17AB6E0;
extern float flt_17ABCDC;
extern float flt_56A610;
extern float flt_56A64C;
extern float flt_56A77C;
extern int nullsub_20;
extern int nullsub_21;
extern int nullsub_28;
extern int nullsub_29;
extern int nullsub_3;
extern int nullsub_30;
extern int nullsub_55;
extern int nullsub_56;
extern int nullsub_57;

// 0x004DFAA0
int CCBStage::InitRound()
{
  int result; // eax
  const char *v2; // [esp+10h] [ebp+4h]
  float v3; // [esp+14h] [ebp+8h]
  float v4; // [esp+18h] [ebp+Ch]
  int v5; // [esp+1Ch] [ebp+10h]

  strcpy((char *)&this->m_pRole[70 * (int)this->m_pCamControl], v2);
  *((float *)&this->m_Task[0].SubTask[0].param.n1 + 70 * (int)this->m_pCamControl) = v3;
  *((float *)&this->m_Task[0].SubTask[0].param.dw1 + 70 * (int)this->m_pCamControl) = v4;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 1;
  *(&this->m_Task[0].SubTask[0].param.n2 + 70 * (int)this->m_pCamControl) = 1103101952;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT.m_Pool[0].fp + 1)) = v5;
  result = (int)&this->m_pCamControl->m_CCT.m_Pool[0].fp + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFED0
int CCBStage::EndRound()
{
  int result; // eax
  float v2; // [esp+4h] [ebp+4h]
  float v3; // [esp+8h] [ebp+8h]
  float v4; // [esp+Ch] [ebp+Ch]
  float v5; // [esp+10h] [ebp+10h]
  char v6; // [esp+14h] [ebp+14h]

  *((float *)&this->m_Task[0].SubTask[0].param.n1 + 70 * (int)this->m_pCamControl) = v2;
  *((float *)&this->m_Task[0].SubTask[0].param.dw1 + 70 * (int)this->m_pCamControl) = v3;
  *(&this->m_Task[0].SubTask[0].param.f1 + 70 * (int)this->m_pCamControl) = v4;
  *((float *)&this->m_Task[0].SubTask[0].param.n2 + 70 * (int)this->m_pCamControl) = v5;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 5;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT.m_Pool[0].fp + 1)) = this->m_pEditor;
  *((_BYTE *)&this->m_Task[0].SubTask[0].bRequireToEnd + 280 * (int)this->m_pCamControl + 3) = v6;
  result = (int)&this->m_pCamControl->m_CCT.m_Pool[0].fp + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004FB9A0
CCBStage::CCBStage(int a2)
{
  float *p_f2; // edx
  int v3; // esi
  float *v4; // edi

  p_f2 = (float *)&this->m_Task[0].SubTask[17].param.f2;
  v3 = 256;
  do
  {
    v4 = p_f2;
    p_f2 += 658;
    --v3;
    memset(v4, 0, 0x2Cu);
  }
  while ( v3 );
  memset(this, 0, 0xA48B0u);
  this->m_pCBSystem = (CCBSystem *)a2;
  this->m_pRoleState = *(CCBRoleState **)(a2 + 16);
  &this->m_pCBSystem;
}

// 0x004FB9F0
CCBStage::~CCBStage()
{
  Actor **p_m_WPXVariance; // ecx
  unsigned int result; // eax

  p_m_WPXVariance = &this->m_WPXVariance;
  *p_m_WPXVariance = 0;
  p_m_WPXVariance[1] = 0;
  LOBYTE(this->m_bRoleSelected[9]) = 0;
  this->m_bRoleSelected[10] = 0;
  memset(&this->m_fDamageNumPosY[1], 0, 0xA4800u);
  this->m_bHideSceneAndRole = -1;
  this->m_fDamageNumPosY[0] = NAN;
  this->m_pShadow = (CCBStageShadow *)-1;
  this->m_pEffect = 0;
  this->m_BFARole = 0;
  LOWORD(this->m_BFARound) = 0;
  BYTE2(this->m_BFARound) = 0;
  memset(&this->m_ptMousePos, 0, 0x2Cu);
  this->m_bRoleSelected[8] = 0;
  result = gbCrc32Compute(aOver);
  this->m_Task[141].SubTask[21].dwTemp1 = result;
  result;
}

// 0x004FBA70
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char CCBStage::Reset()
{
  char *v2; // eax
  unsigned int v3; // edi
  char *v4; // eax
  char result; // al
  CCBStageRole **i; // ebx
  CCBStageRole *v7; // eax
  char *OBBox; // eax
  _DWORD *v9; // eax
  CCBStageCam *v10; // eax
  CCBStageCam *v11; // eax
  CCBCamControl *v12; // eax
  _DWORD *v13; // eax
  Actor *v14; // eax
  _DWORD *v15; // eax
  Actor *v16; // eax
  CCBCamControl *v17; // eax
  char *v18; // eax
  char pExceptionObject[1024]; // [esp+10h] [ebp-100Ch] BYREF
  char ArgList[1024]; // [esp+410h] [ebp-C0Ch] BYREF
  char v21[1024]; // [esp+810h] [ebp-80Ch] BYREF
  char v22[1024]; // [esp+C10h] [ebp-40Ch] BYREF
  int v23; // [esp+1018h] [ebp-4h]

  v2 = (char *)operator new(0x3CCu);
  v3 = 0;
  v23 = 0;
  if ( v2 )
    v4 = (char *)sub_50FD00(v2, this);
  else
    v4 = 0;
  v23 = -1;
  this->m_pScene = (CCBStageScene *)v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_5, 6003),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( ((CCBStageScene *)v4)->CCBStageScene() )
  {
    for ( i = this->m_pRole; ; ++i )
    {
      v7 = (CCBStageRole *)operator new(0x1A18u);
      v23 = 1;
      if ( v7 )
        OBBox = (char *)v7->GetOBBox((int)this);
      else
        OBBox = 0;
      v23 = -1;
      *i = (CCBStageRole *)OBBox;
      if ( !OBBox )
      {
        qmemcpy(
          pExceptionObject,
          ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_5, 109),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      if ( !((CCBStageRole *)OBBox)->IsIdle(v3) )
        break;
      if ( (int)++v3 >= 11 )
      {
        v9 = (_DWORD *)operator new(0x17E8u);
        v23 = 2;
        if ( v9 )
          v10 = (CCBStageCam *)sub_503FA0((int)v9, this, (struct gbGfxManager *)g_Input.KeyInfo[177].Data);
        else
          v10 = 0;
        this->m_pCam = v10;
        v23 = -1;
        if ( !v10 )
        {
          qmemcpy(
            pExceptionObject,
            ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_5, 124),
            sizeof(pExceptionObject));
          _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
        }
        result = sub_504510((CameraCtrl *)v10);
        if ( result )
        {
          v11 = (CCBStageCam *)operator new(0x690B0u);
          v23 = 3;
          if ( v11 )
            v12 = (CCBCamControl *)v11->SetCamPos((int **)this, (int)this->m_pCam);
          else
            v12 = 0;
          v23 = -1;
          this->m_pCamControl = v12;
          if ( !v12 )
          {
            qmemcpy(
              pExceptionObject,
              ((Logger *)ArgList)->FormatException(aNewFailedAtCre, aDProjectPal3Co_5, 135),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = ((CCBStageCam *)v12)->Destroy();
          if ( result )
          {
            v13 = (_DWORD *)operator new(0x4618u);
            v23 = 4;
            if ( v13 )
              v14 = (Actor *)sub_4DF6B0(v13, (int)this);
            else
              v14 = 0;
            v23 = -1;
            this->m_TempStorageNGH = v14;
            if ( !v14 )
            {
              qmemcpy(
                pExceptionObject,
                ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_5, 6003),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = ((std *)v14)->codecvt_base::do_always_noconv();
            if ( result )
            {
              v15 = (_DWORD *)operator new(0x614u);
              v23 = 5;
              if ( v15 )
                v16 = (Actor *)sub_511E20(v15, (int)this);
              else
                v16 = 0;
              v23 = -1;
              this->m_NGHVariance = v16;
              if ( !v16 )
              {
                qmemcpy(
                  pExceptionObject,
                  ((Logger *)ArgList)->FormatException(aCNewFailed, aDProjectPal3Co_5, 6003),
                  sizeof(pExceptionObject));
                _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = ((CCBStageShadow *)v16)->CCBStageShadow();
              if ( result )
              {
                v17 = (CCBCamControl *)operator new(0x6390u);
                v23 = 6;
                if ( v17 )
                  v18 = (char *)v17->SetCircle((int)this);
                else
                  v18 = 0;
                v23 = -1;
                this->m_TempStorageWPX = (Actor *)v18;
                if ( !v18 )
                {
                  qmemcpy(
                    v21,
                    ((Logger *)v22)->FormatException(aCNewFailed, aDProjectPal3Co_5, 6003),
                    sizeof(v21));
                  _CxxThrowException(v21, (_ThrowInfo *)&_TI1_AV_Exception__);
                }
                return ((CCBCamControl *)v18)->IsPointerUnderMouse() != 0;
              }
            }
          }
        }
        return result;
      }
    }
  }
  return 0;
}

// 0x004FBE50
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char CCBStage::Create()
{
  int v2; // ebp
  CCBStageScene *m_pScene; // ecx
  CCBStageScene *v4; // edi
  CCBStageRole **i; // edi
  CCBStageRole *v6; // ebx
  std::codecvt_base *m_pCam; // ecx
  CCBStageCam *v8; // ecx
  CCBStageCam *m_pCamControl; // ecx
  CCBCamControl *v10; // edi
  std::codecvt_base *m_TempStorageNGH; // ecx
  Actor *v12; // edi
  Actor *m_NGHVariance; // ecx
  Actor *v14; // edi
  CCBCamControl **m_TempStorageWPX; // ecx
  Actor *v16; // edi

  v2 = 0;
  m_pScene = (CCBStageScene *)this->m_pScene;
  if ( m_pScene )
  {
    m_pScene->~CCBStageScene();
    v4 = (CCBStageScene *)this->m_pScene;
    if ( v4 )
    {
      nullsub_3(this->m_pScene);
      operator delete(v4);
    }
    this->m_pScene = 0;
    for ( i = this->m_pRole; *i; ++i )
    {
      ((CCBStageRole *)*i)->IsAtInitPos();
      v6 = (CCBStageRole *)*i;
      if ( *i )
      {
        nullsub_3(*i);
        operator delete(v6);
      }
      *i = 0;
      if ( ++v2 >= 11 )
      {
        m_pCam = (std::codecvt_base *)this->m_pCam;
        if ( m_pCam )
        {
          m_pCam->codecvt_base::do_always_noconv();
          v8 = (CCBStageCam *)this->m_pCam;
          if ( v8 )
            (*(void (**)(CCBStageCam *, int))LODWORD(v8->fov))(v8, 1);
          this->m_pCam = 0;
          m_pCamControl = (CCBStageCam *)this->m_pCamControl;
          if ( m_pCamControl )
          {
            m_pCamControl->Init();
            v10 = (CCBCamControl *)this->m_pCamControl;
            if ( v10 )
            {
              ((j_std *)this->m_pCamControl)->codecvt_base::do_always_noconv();
              operator delete(v10);
            }
            this->m_pCamControl = 0;
            m_TempStorageNGH = (std::codecvt_base *)this->m_TempStorageNGH;
            if ( m_TempStorageNGH )
            {
              m_TempStorageNGH->codecvt_base::do_always_noconv();
              v12 = (Actor *)this->m_TempStorageNGH;
              if ( v12 )
              {
                nullsub_3(this->m_TempStorageNGH);
                operator delete(v12);
              }
              this->m_TempStorageNGH = 0;
              m_NGHVariance = (Actor *)this->m_NGHVariance;
              if ( m_NGHVariance )
              {
                ((CCBStageShadow *)m_NGHVariance)->~CCBStageShadow();
                v14 = (Actor *)this->m_NGHVariance;
                if ( v14 )
                {
                  nullsub_3(this->m_NGHVariance);
                  operator delete(v14);
                }
                this->m_NGHVariance = 0;
                m_TempStorageWPX = (CCBCamControl **)this->m_TempStorageWPX;
                if ( m_TempStorageWPX )
                {
                  m_TempStorageWPX->DoList();
                  v16 = (Actor *)this->m_TempStorageWPX;
                  if ( v16 )
                  {
                    sub_508460((char *)this->m_TempStorageWPX);
                    operator delete(v16);
                  }
                  this->m_TempStorageWPX = 0;
                  return 1;
                }
              }
            }
          }
        }
        return 0;
      }
    }
  }
  return 0;
}

// 0x004FBF90
char CCBStage::Destroy()
{
  CCBStageScene *m_pScene; // ecx
  int v4; // ebx
  int v5; // edi
  CCBStageRole **m_pRole; // esi
  CCBStageRole *v7; // ecx
  CCBStageCam *m_pCam; // ecx
  CCBStageCam *m_pCamControl; // ecx
  Actor *m_NGHVariance; // ecx
  Actor *m_TempStorageWPX; // ecx
  Actor *m_TempStorageNGH; // ecx

  this->~CCBStage();
  this->m_pEditor = this->m_pCBSystem->m_pEditor;
  m_pScene = (CCBStageScene *)this->m_pScene;
  if ( !m_pScene || !m_pScene->Reset() )
    return 0;
  v4 = 0;
  v5 = 0;
  m_pRole = this->m_pRole;
  do
  {
    if ( !*m_pRole )
      return 0;
    ((CCBStageRole *)*m_pRole)->GetRotAngle();
    v7 = (CCBStageRole *)*m_pRole;
    if ( this->m_pRoleState->m_Role[v5].bValid )
    {
      if ( !v7->IsAtProtectPos(v4, 0, 0) )
        return 0;
    }
    else if ( !v7->IsAtProtectPos(v4, 0, 0) )
    {
      return 0;
    }
    ++v5;
    ++v4;
    ++m_pRole;
  }
  while ( v5 < 11 );
  m_pCam = (CCBStageCam *)this->m_pCam;
  if ( !m_pCam || !sub_504540((CameraCtrl *)m_pCam) )
    return 0;
  m_pCamControl = (CCBStageCam *)this->m_pCamControl;
  if ( !m_pCamControl || !m_pCamControl->Update() )
    return 0;
  m_NGHVariance = (Actor *)this->m_NGHVariance;
  if ( !m_NGHVariance || !((CCBStageShadow *)m_NGHVariance)->Reset() )
    return 0;
  m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
  if ( !m_TempStorageWPX || !(unsigned __int8)((CCBCamControl *)m_TempStorageWPX)->ResetListFlag() )
    return 0;
  m_TempStorageNGH = (Actor *)this->m_TempStorageNGH;
  if ( !m_TempStorageNGH || !sub_4DF700(m_TempStorageNGH) )
    return 0;
  sub_4DFFF0((int)this->m_TempStorageNGH, 0.0, 0);
  return 1;
}

// 0x004FC0A0
int CCBStage::Update()
{
  CCBStageRole **m_pRole; // esi
  int v3; // ebx
  CEffectSystem *v4; // eax
  int result; // eax
  float a2; // [esp+0h] [ebp-10h]

  if ( LOBYTE(this->m_bRoleSelected[9]) != 1 )
  {
    ((GRPinput *)&this->m_WPXVariance)->GetCursorPos();
    ((CCBStageScene *)this->m_pScene)->SetBattleFieldAttr();
    if ( dword_17A990C == 1 )
      this->Update();
    else
      this->Render();
    m_pRole = this->m_pRole;
    v3 = 11;
    do
    {
      if ( LOBYTE((*m_pRole)->m_bValid) )
        ((CCBStageRole *)*m_pRole)->IsTaskFinished((int)this);
      ++m_pRole;
      --v3;
    }
    while ( v3 );
    ((CCBStage *)this->m_pCam)->ProcessTurn();
    ((CCBStageCam *)this->m_pCamControl)->DoTask();
    nullsub_3(this->m_TempStorageNGH);
    nullsub_3(this->m_NGHVariance);
    this->UpdatePhysics();
    a2 = this->m_pCBSystem->m_DeltaTime;
    v4 = (CEffectSystem *)CEffectSystem::DestroyAllEffect();
    v4->SetVisible(a2);
  }
  return result;
}

// 0x004FC150
int CCBStage::Update()
{
  CCBDisplayChain *m_pDisplayChain; // ecx
  CCBStageCam *m_pCam; // ecx
  char *ViewTarget; // edi
  double v5; // st7
  gbVec3D *v6; // eax
  int z_low; // eax
  CCBStageShadow *m_pShadow; // eax
  CCBStageRole *v9; // eax
  int result; // eax
  float v11; // ecx
  int v12; // edx
  float v13; // [esp+1Ch] [ebp-7Ch]
  float v14; // [esp+20h] [ebp-78h]
  float v15; // [esp+24h] [ebp-74h]
  int pOut; // [esp+30h] [ebp-68h] BYREF
  int pOut2; // [esp+34h] [ebp-64h] BYREF
  float pPos; // [esp+38h] [ebp-60h] BYREF
  float y; // [esp+3Ch] [ebp-5Ch]
  int v20; // [esp+40h] [ebp-58h]
  float v21; // [esp+44h] [ebp-54h] BYREF
  float v22; // [esp+48h] [ebp-50h]
  int v23; // [esp+4Ch] [ebp-4Ch]
  struct gbVec3D v24; // [esp+50h] [ebp-48h] BYREF
  struct gbVec3D v25; // [esp+5Ch] [ebp-3Ch] BYREF
  gbVec3D pTarget[2]; // [esp+68h] [ebp-30h] BYREF
  gbRay v27; // [esp+80h] [ebp-18h] BYREF

  v25.y = 1.0;
  y = 0.0;
  v25.x = 0.0;
  v25.z = 0.0;
  pPos = 1.0;
  v20 = 1065353216;
  v24.y = 0.0;
  v21 = 0.0;
  v22 = 0.0;
  v23 = 0;
  v24.x = 1.0;
  v24.z = 1.0;
  memset(&v27, 0, 12);
  ((gbVec3D *)&v27.Direction)->gbVec3D(0.0, 0.0, 0.0);
  m_pDisplayChain = (CCBDisplayChain *)this->m_pDisplayChain;
  pPos = *(float *)&this->m_WPXVariance;
  y = *(float *)&m_pDisplayChain;
  m_pCam = (CCBStageCam *)this->m_pCam;
  pOut = 0;
  pOut2 = 0;
  ViewTarget = (char *)((CameraCtrl *)m_pCam)->GetViewTarget(pTarget, &pPos);
  ((gbVec3D *)&v27)->operator=(ViewTarget);
  ((gbVec3D *)&v27.Direction)->operator=(ViewTarget + 12);
  v5 = ((gbRay *)&v27)->IntersectPlane(&v25, &v24);
  pPos = v27.Direction.x * v5;
  y = v27.Direction.y * v5;
  v15 = v27.Origin.z + v5 * v27.Direction.z;
  v14 = v27.Origin.y + y;
  v13 = pPos + v27.Origin.x;
  v6 = (gbVec3D *)pTarget->gbVec3D(v13, v14, v15);
  pPos = v6->x;
  y = v6->y;
  z_low = LODWORD(v6->z);
  v21 = pPos;
  v20 = z_low;
  v23 = z_low;
  m_pShadow = (CCBStageShadow *)this->m_pShadow;
  v22 = y;
  if ( m_pShadow != (CCBStageShadow *)-1 )
  {
    ((gbVec3D *)&this->m_pRole[(_DWORD)m_pShadow]->m_Task[35].cmd.bDestRole[10])->operator=(&v21);
    v9 = (CCBStageRole *)this->m_pRole[(int)this->m_pShadow];
    *(float *)&v9->m_Task[35].cmd.bDestRole[7] = v21;
    v9 = (CCBStageRole *)((char *)v9 + 6584);
    *(float *)&v9->m_pRoleState = v22;
    *(_DWORD *)v9->m_sLastRole = v23;
  }
  result = (int)this->m_pScene;
  if ( *(_BYTE *)(result + 964) )
  {
    if ( (g_Input.m_shiftedKeyStates[264] & 0xF) == 1 )
    {
      pPos = v21;
      y = v22;
      v20 = v23;
      v11 = v22;
      *(float *)(result + 888) = v21;
      v12 = v20;
      *(float *)(result + 892) = v11;
      *(_DWORD *)(result + 896) = v12;
    }
    else
    {
      ((GRPinput *)&g_Input)->GetMousePos(&pOut, &pOut2);
      result = (int)this->m_pScene;
      *(float *)(result + 912) = (double)pOut + *(float *)(result + 912);
      this->m_pScene->m_EnemyFiveLineupQuad.vec[2].y = (double)pOut2 * 0.016666668
                                                     + this->m_pScene->m_EnemyFiveLineupQuad.vec[2].y;
    }
  }
  return result;
}

// 0x004FC3A0
int CCBStage::EditorUpdate()
{
  int v2; // ebp
  CCBStageCam *m_pCam; // eax
  float *p_OrthoSize; // eax
  CEffectSystem *v5; // eax
  CCBStageCam *v6; // eax
  int v7; // ebx
  struct gbCamera *v8; // eax
  gbMatrixStack *v9; // edi
  __int8 *v10; // eax
  CCBStageRole **v11; // eax
  CCBStageRole *v12; // ecx
  long double v13; // st7
  bool v14; // cc
  CCBStageCam *v15; // eax
  struct gbCamera *v16; // eax
  CCBStageScene *m_pScene; // ecx
  CCBStageScene *v18; // ecx
  CEffectSystem *v19; // eax
  int v21; // [esp+18h] [ebp-3Ch]
  float v22; // [esp+20h] [ebp-34h]
  CCBStageRole **m_pRole; // [esp+38h] [ebp-1Ch]
  int v24; // [esp+38h] [ebp-1Ch]
  float v25; // [esp+3Ch] [ebp-18h]
  CCBStageRole **v26; // [esp+40h] [ebp-14h]
  float v27; // [esp+48h] [ebp-Ch] BYREF
  float v28; // [esp+4Ch] [ebp-8h]
  float v29; // [esp+50h] [ebp-4h]

  v2 = 0;
  *(_DWORD *)(g_Input.KeyInfo[177].Data + 444) = 0;
  m_pCam = (CCBStageCam *)this->m_pCam;
  if ( m_pCam )
    p_OrthoSize = (float *)&m_pCam->OrthoSize;
  else
    p_OrthoSize = 0;
  v21 = (int)p_OrthoSize;
  v5 = (CEffectSystem *)CEffectSystem::DestroyAllEffect();
  v5->HandleViewMove(v21);
  v6 = (CCBStageCam *)this->m_pCam;
  v7 = *(_DWORD *)(g_Input.KeyInfo[177].Data + 448);
  if ( v6 )
    v8 = (CCBStageCam *)&v6->OrthoSize;
  else
    v8 = 0;
  ((gbSceneGraph *)v7)->Begin(v8);
  *(_BYTE *)(v7 + 19244) = 0;
  v9 = (gbMatrixStack *)*(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 216);
  ((CameraCtrl *)this->m_pCam)->SetAsCurrent(3);
  v9->Push();
  (*(void (**)(char *, _DWORD))(*(_DWORD *)&this->m_TempStorageWPX->m_name[8] + 16))(
    &this->m_TempStorageWPX->m_name[8],
    0);
  if ( !HIBYTE(this->m_BFARound) )
  {
    ((CCBStageScene *)this->m_pScene)->GetBattleFieldSubdueAttr(v9);
    m_pRole = this->m_pRole;
    do
    {
      if ( dword_17A990C == 1 || (v10 = &this->m_pRoleState->m_sCombatDialog[v2], v10[577]) && !v10[1432] )
        ((CCBStageRole *)*m_pRole)->IsDoTask(v9);
      v2 += 892;
      ++m_pRole;
    }
    while ( v2 < 9812 );
    v11 = this->m_pRole;
    v24 = 0;
    v26 = this->m_pRole;
    do
    {
      v12 = (CCBStageRole *)*v11;
      if ( LOBYTE((*v11)->m_fTimeScale) )
      {
        v27 = 0.0;
        v28 = 0.0;
        v29 = 0.0;
        v12->DoTask(&v27);
        v13 = sin(this->m_pCBSystem->m_fTimeFund * 10.0 + (double)v24);
        v25 = v13;
        v28 = v13 * 5.0 + v28 + 6.0;
        v9->Push();
        v9->Translate(v27, v28, v29);
        v22 = v25 * 0.2 + 1.0;
        v9->Scale(1.0, v22, 1.0);
        (*(void (**)(gbGeomNode *, _DWORD))(*(_DWORD *)this->m_pScene->m_pPointer + 16))(
          this->m_pScene->m_pPointer,
          0);
        v9->Pop();
      }
      v11 = v26 + 1;
      v14 = ++v24 < 5;
      ++v26;
    }
    while ( v14 );
  }
  ((SceneMgr *)this->m_pCBSystem->m_pEffMgr)->RenderUpdate();
  ((SceneMgr *)this->m_pCBSystem->m_pATSEffMgr)->RenderUpdate();
  v9->Pop();
  ((gbSceneGraph *)v7)->End();
  ((CCBStageShadow *)this->m_NGHVariance)->Create();
  v15 = (CCBStageCam *)this->m_pCam;
  if ( v15 )
    v16 = (CCBStageCam *)&v15->OrthoSize;
  else
    v16 = 0;
  ((gbSceneGraph *)v7)->Begin(v16);
  *(_BYTE *)(v7 + 19244) = 0;
  (*(void (**)(char *, _DWORD))(*(_DWORD *)&this->m_TempStorageWPX->m_name[8] + 16))(
    &this->m_TempStorageWPX->m_name[8],
    0);
  (*(void (**)(gbVisNode *, _DWORD))(*(_DWORD *)this->m_pScene->m_pLights + 16))(
    this->m_pScene->m_pLights,
    0);
  ((SceneMgr *)this->m_pCBSystem->m_pEffMgr)->RenderAll();
  ((SceneMgr *)this->m_pCBSystem->m_pATSEffMgr)->RenderAll();
  ((C3DSpark *)this->m_pCBSystem->m_p3DSpark->m_Spark)->Render((struct gbVec3D *)gbSceneGraph::End);
  ((gbSceneGraph *)v7)->End();
  if ( byte_17A9927 )
  {
    ((CCBStageScene *)this->m_pScene)->IsSameBattleFieldAttr();
    ((CCBStageScene *)this->m_pScene)->GetBFASubdueFM();
  }
  if ( BYTE1(this->m_pCBSystem->m_bFiveNimbus) )
  {
    if ( dword_17A990C == 1 )
    {
      m_pScene = (CCBStageScene *)this->m_pScene;
      if ( !HIBYTE(m_pScene->m_EnemyFiveLineupQuad.color.Blue) )
        goto LABEL_31;
      m_pScene->LoadPointer(60);
    }
    if ( dword_17A990C == 4 )
    {
      v18 = (CCBStageScene *)this->m_pScene;
      if ( HIBYTE(v18->m_EnemyFiveLineupQuad.color.Blue) )
        v18->LoadPointer(60);
      ((CCCTData *)&this->m_pCamControl->m_CCT)->~CCCTData();
    }
  }
LABEL_31:
  sub_4DFA10(&this->m_TempStorageNGH->m_actarray);
  v19 = (CEffectSystem *)CEffectSystem::DestroyAllEffect();
  v19->Update();
  sub_4C5C20((int *)g_Input.KeyInfo[178].Data);
  PushMatrixStacks();
  v29 = 0.0;
  ((CGameData *)&g_GameData)->Render();
  sub_4DF710((int)this->m_TempStorageNGH);
  if ( !g_Input.KeyInfo[180].CountMode )
    ((Logger *)g_Logger)->Render();
  v29 = NAN;
  return (int)PopMatrixStacks();
}

// 0x004FC6F0
// attributes: thunk
void CCBStage::Render()
{
  this->GetTask();
}

// 0x004FC700
int CCBStage::GetRoleIndex(int a2, const void *a3, char a4)
{
  int v5; // ebp
  int *i; // eax
  char *v8; // edi

  if ( this->m_bRoleSelected[10] >= 246 )
    ((CCBSystem *)this->m_pCBSystem)->CreateObj(byte_5DB6C4, 0, 0x30u);
  v5 = 0;
  for ( i = &this->m_Task[0].SubTask[17].nTemp2; *(_BYTE *)i; i += 658 )
  {
    if ( ++v5 >= 256 )
      return -1;
  }
  v8 = (char *)this + 2632 * v5;
  *((_DWORD *)v8 + 43) = 2;
  v8[2796] = 1;
  v8[2797] = a4;
  *((_DWORD *)v8 + 686) = ((CCBSystem *)this->m_pCBSystem)->ProcProtect();
  *((_DWORD *)v8 + 44) = 0;
  *((_DWORD *)v8 + 42) = a2;
  *((_DWORD *)v8 + 687) = 0;
  if ( a3 )
    qmemcpy(v8 + 2752, a3, 0x2Cu);
  else
    *((_DWORD *)v8 + 690) = -1;
  ++this->m_bRoleSelected[10];
  return v5;
}

// 0x004FC7D0
int CCBStage::GetRoleName(
        CCBStage *this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        _DWORD *a7,
        int a8,
        int a9)
{
  int v9; // ebp
  int v10; // ebx
  int *i; // eax
  float *v13; // esi
  _DWORD *v14; // esi

  v9 = 0;
  v10 = 658 * a2;
  for ( i = &this->m_nCurSubTask + 658 * a2; *(_BYTE *)i; i += 20 )
  {
    if ( ++v9 >= 32 )
      return -1;
  }
  v13 = (float *)&this->m_fDamageNumPosY[20 * v9 + 5 + v10];
  memset(v13, 0, 0x50u);
  *((_BYTE *)&this->m_nCurSubTask + 80 * v9 + v10 * 4 + 1) = 0;
  *((_BYTE *)&this->m_nCurSubTask + 80 * v9 + v10 * 4) = 1;
  LODWORD(this->m_fDamageNumPosY[20 * v9 + 9 + v10]) = 2;
  *(_DWORD *)v13 = a3;
  LODWORD(this->m_fDamageNumPosY[20 * v9 + 6 + v10]) = a4;
  LODWORD(this->m_fDamageNumPosY[20 * v9 + 7 + v10]) = a5;
  LODWORD(this->m_fDamageNumPosY[20 * v9 + 8 + v10]) = a6;
  *((_DWORD *)v13 + 5) = ((CCBSystem *)this->m_pCBSystem)->ProcProtect();
  *((_DWORD *)v13 + 7) = a8;
  v13[6] = 0.0;
  *((_DWORD *)v13 + 8) = a9;
  if ( a7 )
  {
    v14 = (_DWORD *)v13 + 11;
    * v14 = (*)*a7;
    v14[1] = a7[1];
    v14[2] = a7[2];
  }
  ++LODWORD(this->m_fDamageNumPosY[v10 + 3]);
  return v9;
}

// 0x004FC8B0
char CCBStage::Procced(int a2)
{
  char *v2; // edx
  int v3; // ecx
  _BYTE *v4; // eax

  v2 = (char *)this + 2632 * a2;
  v3 = 32;
  v4 = (_BYTE *)v2 + 227;
  do
  {
    if ( *(v4 - 3) )
      *v4 = 1;
    v4 += 80;
    --v3;
  }
  while ( v3 );
  v2[2797] = 1;
  return 1;
}

// 0x004FC980
int CCBStage::IsDoTask(int a2)
{
  return (int)&this->m_fDamageNumPosY[658 * a2 + 1];
}

// 0x004FC9A0
int CCBStage::EndTask(int a2)
{
  return *(&this->m_Task[0].SubTask[17].param.n2 + 658 * a2);
}

// 0x004FC9C0
char * CCBStage::DelTask(int a2, _BYTE *a3, _DWORD *a4)
{
  char *result; // eax

  *a3 = 0;
  *a4 = 0;
  result = (char *)this + 2632 * a2;
  if ( *((_DWORD *)result + 43) == 4 )
  {
    *a3 = 1;
    * a4 = (*)*((_DWORD *)result + 687);
  }
  return result;
}

// 0x004FCA00
char CCBStage::ForceDelTask(int a2)
{
  float *v2; // eax
  int v3; // edx

  v2 = (float *)&this->m_fDamageNumPosY[1];
  v3 = 0;
  while ( !*((_BYTE *)v2 + 2628) || a2 != *(_DWORD *)v2 || *((_DWORD *)v2 + 1) == 4 )
  {
    ++v3;
    v2 += 658;
    if ( v3 >= 256 )
      return 0;
  }
  return 1;
}

// 0x004FCA80
void CCBStage::GetTask()
{
  int v2; // ebx
  int *p_nTemp2; // edi
  int v4; // ebp
  int *v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int (*v9)(CCBStage *, int); // ecx
  int *v10; // [esp+10h] [ebp-4h]

  v2 = 0;
  p_nTemp2 = (int *)&this->m_Task[0].SubTask[17].nTemp2;
  v10 = (int *)&this->m_Task[0].SubTask[17].nTemp2;
  do
  {
    if ( *(_BYTE *)p_nTemp2 == 1 && *(p_nTemp2 - 656) == 3 )
    {
      v4 = 0;
      v5 = (int *)p_nTemp2 - 669;
      do
      {
        if ( !*((_BYTE *)v5 + 104) || v4 > 0 && *v5 == 2 )
          break;
        if ( v5[20] == 2 )
        {
          if ( v4 > 0 )
          {
            if ( *((float *)v5 + 23) >= 0.0 )
            {
              if ( this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 2) > *((float *)v5 + 23) )
              {
LABEL_25:
                this->GetTaskID(v2, v4);
LABEL_26:
                this->m_bHideSceneAndRole = v2;
                LODWORD(this->m_fDamageNumPosY[0]) = v4;
                ((void (*)(char *, _DWORD))v5[16])((char *)this + v5[17], 0);
              }
            }
            else if ( *v5 == 4 )
            {
              goto LABEL_25;
            }
          }
        }
        else
        {
          if ( v5[20] == 3 )
            goto LABEL_26;
          if ( v5[20] == 4 && this->GetTaskState(v2) == 1 )
          {
            v6 = *(v10 - 655);
            *(v10 - 656) = 4;
            v6 *= 80;
            v7 = *(int *)((char *)v10 + v6 - 2656);
            v8 = (int)v10 + v6 - 2628;
            *(v10 - 12) = v7;
            v9 = *(int (**)(CCBStage *, int))(v8 - 64);
            if ( v9 == CCBStage::ProcFiveLienupFadeOut
              && (!v9 || !*(_DWORD *)(v8 - 60) && !*(_DWORD *)(v8 - 56) && !*(_DWORD *)(v8 - 52)) )
            {
              *(v10 - 12) = *(_DWORD *)(v8 - 108);
            }
            if ( *((_BYTE *)v10 + 1) == 1 )
            {
              ((CCBSystem *)this)->GetStageRole(v2);
              break;
            }
          }
        }
        ++v4;
        v5 += 20;
      }
      while ( v4 < 32 );
    }
    ++v2;
    p_nTemp2 = (int *)v10 + 658;
    v10 += 658;
  }
  while ( v2 < 256 );
}

// 0x004FCBD0
char CCBStage::GetTaskID(int a2, int a3)
{
  char *v3; // eax

  v3 = (char *)this + 2632 * a2 + 80 * a3;
  *((_DWORD *)v3 + 50) = 3;
  *((float *)v3 + 52) = this->m_pCBSystem->m_fTimeFund;
  return 1;
}

// 0x004FCC10
char CCBStage::GetTaskState(int a2)
{
  int v2; // edx
  char *v3; // ecx
  int v4; // eax
  _DWORD *i; // ecx

  v2 = 0;
  v3 = (char *)this + 2632 * a2;
  v4 = *((_DWORD *)v3 + 44);
  if ( v4 <= 0 )
    return 1;
  for ( i = v3 + 200; *i == 4; i += 20 )
  {
    if ( ++v2 >= v4 )
      return 1;
  }
  return 0;
}

// 0x004FCC50
char CCBStage::GetTaskState(int a2)
{
  int v2; // ebx
  int *i; // edx
  int v4; // eax
  int v5; // esi
  int *v6; // eax
  int v7; // ecx

  v2 = 0;
  for ( i = &this->m_Task[0].SubTask[17].nTemp2; ; i += 658 )
  {
    if ( *(_BYTE *)i )
    {
      if ( *(i - 656) != 4 && *(i - 657) == 11 )
      {
        v4 = *(i - 9);
        if ( v4 >= 5 && v4 < 11 )
          break;
      }
    }
LABEL_18:
    if ( ++v2 >= 256 )
      return 0;
  }
  v5 = 0;
  v6 = (int *)i - 653;
  while ( 1 )
  {
    if ( (int (*)(CCBStage *, int))*v6 == CCBStage::HandleKeyCtrl && (!*v6 || !v6[1] && !v6[2] && !v6[3]) )
    {
      if ( v6[4] == 4 )
        goto LABEL_18;
      v7 = *(i - 8);
      if ( v7 == a2 || v7 == -1 && *((_BYTE *)i + a2 - 15) )
        return 1;
    }
    ++v5;
    v6 += 20;
    if ( v5 >= 32 )
      goto LABEL_18;
  }
}

// 0x004FCD00
int CCBStage::IsTaskFinished(int a2)
{
  int result; // eax
  __int32 *p_dw3; // edx
  int v5; // ebx

  ((CCBStageRole *)this->m_pRole[a2])->GetState();
  p_dw3 = (__int32 *)&this->m_Task[0].SubTask[17].param.dw3;
  v5 = 256;
  do
  {
    LOBYTE(result) = *((_BYTE *)p_dw3 + 36);
    if ( (_BYTE)result )
    {
      if ( *p_dw3 == a2 )
      {
        result = 0;
        memset(p_dw3 - 648, 0, 0xA48u);
        --this->m_bRoleSelected[10];
      }
    }
    p_dw3 += 658;
    --v5;
  }
  while ( v5 );
  return result;
}

// 0x004FCD50
_BYTE * ((CCBStage *)_BYTE *result@<eax>)->IsTaskValidButNotFinish@<eax>(int, a2@<ecx>, int, a3)
{
  int v3; // edx
  int v4; // esi
  int v5; // ecx

  v3 = a2 + 2760;
  v4 = 256;
  do
  {
    LOBYTE(result) = *(_BYTE *)(v3 + 36);
    if ( (_BYTE)result && *(_DWORD *)v3 == a3 )
    {
      result = (_BYTE *)(v3 - 2533);
      v5 = 32;
      do
      {
        if ( *(result - 3) )
          *result = 1;
        result += 80;
        --v5;
      }
      while ( v5 );
    }
    v3 += 2632;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCDA0
int CCBStage::IsTaskExist(int a2)
{
  int result; // eax
  __int32 *p_dw3; // ecx
  int v4; // edx

  result = 0;
  p_dw3 = (__int32 *)&this->m_Task[0].SubTask[17].param.dw3;
  v4 = 256;
  do
  {
    if ( *((_BYTE *)p_dw3 + 36) && *p_dw3 == a2 && *(p_dw3 - 648) != 29 )
      ++result;
    p_dw3 += 658;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCDE0
int CCBStage::DoTask(int a2)
{
  int result; // eax

  result = a2;
  if ( a2 == -1 )
    this->m_pShadow = (CCBStageShadow *)-1;
  else
    this->m_pShadow = (CCBStageShadow *)a2;
  return result;
}

// 0x004FCE00
int CCBStage::StartSubTask(int a2)
{
  unsigned int v2; // eax
  float *v3; // esi

  v2 = 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v3 = (float *)&this->m_fDamageNumPosY[658 * this->m_bHideSceneAndRole + 5 + v2 / 4];
  if ( *((_BYTE *)&this->m_nCurSubTask + 2632 * this->m_bHideSceneAndRole + v2 + 1) )
  {
    if ( *((_BYTE *)&this->m_nCurSubTask + 2632 * this->m_bHideSceneAndRole + v2 + 3) == 1
      || this->m_pCBSystem->m_fTimeFund - v3[6] >= v3[8]
      || ((GRPinput *)&g_Input)->SetJoystickAbs() )
    {
      *((_DWORD *)v3 + 4) = 4;
    }
    return 0;
  }
  else
  {
    *((_BYTE *)&this->m_nCurSubTask + 2632 * this->m_bHideSceneAndRole + v2 + 1) = 1;
    return 0;
  }
}

// 0x004FCE70
int CCBStage::IsSubTaskFinished(int a2)
{
  __int32 v3; // ecx
  char *v4; // eax
  double v5; // st7
  int v6; // esi
  double v7; // st7
  unsigned int v8; // eax
  unsigned int v9; // ecx
  float v11; // [esp+1Ch] [ebp-8h]
  float v12; // [esp+1Ch] [ebp-8h]
  float v13; // [esp+20h] [ebp-4h]
  float v14; // [esp+20h] [ebp-4h]

  v3 = 329 * this->m_bHideSceneAndRole;
  v4 = (char *)this + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = *(float *)&v4[8 * v3 + 216] * 0.25;
  v6 = (int)&v4[8 * v3 + 184];
  v11 = v5;
  v13 = v5 * 3.0;
  if ( !v4[8 * v3 + 225] )
  {
    *(_DWORD *)&v4[8 * v3 + 248] = 0;
    v4[8 * v3 + 225] = 1;
  }
  ((CCBStage *)this->m_TempStorageNGH)->EndRound();
  v7 = this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24);
  if ( v7 >= v13 )
  {
    v12 = (1.0 - (v7 - v13) / v11) * 255.0;
    v9 = (int)v12;
    *(_DWORD *)(v6 + 64) = v9;
    v8 = v9 <= 0xFF ? v9 : 0;
  }
  else
  {
    v14 = v7 / v13 * 255.0;
    v8 = (int)v14;
    *(_DWORD *)(v6 + 64) = v8;
    if ( v8 > 0xFF )
      v8 = 255;
  }
  *(_DWORD *)(v6 + 64) = v8;
  if ( *(_BYTE *)(v6 + 43) == 1 || this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24) >= *(float *)(v6 + 32) )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FCFB0
int CCBStage::IsAllSubTaskFinished(int a2)
{
  __int32 v3; // ecx
  unsigned int v4; // edx
  double v5; // st7
  float *v6; // esi
  double v7; // st7
  unsigned int v8; // eax
  unsigned int v9; // ecx
  float v11; // [esp+8h] [ebp-8h]
  float v12; // [esp+8h] [ebp-8h]
  float v13; // [esp+Ch] [ebp-4h]
  float v14; // [esp+Ch] [ebp-4h]

  v3 = 329 * this->m_bHideSceneAndRole;
  v4 = 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = *(float *)((char *)&this->m_nTask + 8 * v3 + v4) * 0.25;
  v6 = (float *)&this->m_fDamageNumPosY[2 * v3 + 5 + v4 / 4];
  v11 = v5;
  v13 = v5 * 3.0;
  if ( !*((_BYTE *)&this->m_nCurSubTask + 8 * v3 + v4 + 1) )
  {
    *(__int32 *)((char *)&this->m_Task[0].SubTask[0].dwID + 8 * v3 + v4) = 0;
    *((_BYTE *)&this->m_nCurSubTask + 8 * v3 + v4 + 1) = 1;
  }
  sub_4DFF90(&this->m_TempStorageNGH->m_actarray, *((_BYTE *)&this->m_Task[0].SubTask[0].dwID + 8 * v3 + v4));
  v7 = this->m_pCBSystem->m_fTimeFund - v6[6];
  if ( v7 >= v13 )
  {
    v12 = (1.0 - (v7 - v13) / v11) * 255.0;
    v9 = (int)v12;
    *((_DWORD *)v6 + 16) = v9;
    v8 = v9 <= 0xFF ? v9 : 0;
  }
  else
  {
    v14 = v7 / v13 * 255.0;
    v8 = (int)v14;
    *((_DWORD *)v6 + 16) = v8;
    if ( v8 > 0xFF )
      v8 = 255;
  }
  *((_DWORD *)v6 + 16) = v8;
  if ( *((_BYTE *)v6 + 43) == 1 || this->m_pCBSystem->m_fTimeFund - v6[6] >= v6[8] )
    *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FD0B0
int CCBStage::IsTaskValid(int a2)
{
  __int32 v3; // ecx
  unsigned int v4; // edx
  float *v5; // esi
  double v6; // st7
  unsigned int v7; // eax
  float v9; // [esp+20h] [ebp-4h]
  float v10; // [esp+20h] [ebp-4h]

  v3 = 329 * this->m_bHideSceneAndRole;
  v4 = 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (float *)&this->m_fDamageNumPosY[2 * v3 + 5 + v4 / 4];
  v9 = *(float *)((char *)&this->m_nTask + 8 * v3 + v4);
  if ( !*((_BYTE *)&this->m_nCurSubTask + 8 * v3 + v4 + 1) )
  {
    *(__int32 *)((char *)&this->m_Task[0].SubTask[0].dwID + 8 * v3 + v4) = 0;
    *((_BYTE *)&this->m_nCurSubTask + 8 * v3 + v4 + 1) = 1;
  }
  ((CCBStage *)this->m_TempStorageNGH)->EndRound();
  v6 = this->m_pCBSystem->m_fTimeFund - v5[6];
  if ( v6 >= v9 )
  {
    *((_DWORD *)v5 + 16) = 255;
    *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    v10 = v6 / v9 * 255.0;
    v7 = (int)v10;
    *((_DWORD *)v5 + 16) = v7;
    if ( v7 > 0xFF )
      v7 = 255;
    *((_DWORD *)v5 + 16) = v7;
  }
  if ( *((_BYTE *)v5 + 43) == 1 )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FD1A0
int CCBStage::IsSubTaskValid(int a2)
{
  __int32 v3; // ecx
  unsigned int v4; // edx
  float *v5; // esi
  double v6; // st7
  unsigned int v7; // ecx
  float v9; // [esp+20h] [ebp-4h]
  float v10; // [esp+20h] [ebp-4h]

  v3 = 329 * this->m_bHideSceneAndRole;
  v4 = 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (float *)&this->m_fDamageNumPosY[2 * v3 + 5 + v4 / 4];
  v9 = *(float *)((char *)&this->m_nTask + 8 * v3 + v4);
  if ( !*((_BYTE *)&this->m_nCurSubTask + 8 * v3 + v4 + 1) )
  {
    *(__int32 *)((char *)&this->m_Task[0].SubTask[0].dwID + 8 * v3 + v4) = 255;
    *((_BYTE *)&this->m_nCurSubTask + 8 * v3 + v4 + 1) = 1;
  }
  ((CCBStage *)this->m_TempStorageNGH)->EndRound();
  v6 = this->m_pCBSystem->m_fTimeFund - v5[6];
  if ( v6 >= v9 )
  {
    v5[16] = 0.0;
    *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    v10 = (1.0 - v6 / v9) * 255.0;
    v7 = (int)v10;
    *((_DWORD *)v5 + 16) = v7;
    *((_DWORD *)v5 + 16) = v7 <= 0xFF ? v7 : 0;
  }
  if ( *((_BYTE *)v5 + 43) == 1 )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FD290
int CCBStage::IsIdle(int a2)
{
  __int32 v3; // ecx
  char *v4; // eax
  int v5; // edi
  CCBUI *m_pUI; // ebp
  char *v8; // eax
  UIStatic *m_pWinPanel; // ecx
  char *v10; // eax
  CCBUI *v11; // ecx

  v3 = 329 * this->m_bHideSceneAndRole;
  v4 = (char *)this + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (int)&v4[8 * v3 + 184];
  if ( !v4[8 * v3 + 225] )
  {
    if ( BYTE1(CEffectSystem::DestroyAllEffect()->m_pVertexBuffer) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    m_pUI = (CCBUI *)this->m_pCBSystem->m_pUI;
    if ( this->m_pRoleState->m_bWeSneakAttackEnemy )
    {
      v8 = ((PalScript *)(&g_PAL3Data + 312))->SetAppName(aWesneakattacke);
      ((UIWnd *)m_pUI->m_pRoleStateImmunity[10])->SetEnable(v8, 1);
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10];
    }
    else
    {
      v10 = ((PalScript *)(&g_PAL3Data + 312))->SetAppName(aEnemysneakatta);
      ((UIWnd *)m_pUI->m_pWinPanel)->SetEnable(v10, 1);
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pWinPanel;
    }
    (*(void (**)(UIStatic *, int))m_pWinPanel->m_fontcolor.ColorQuadFmt)(m_pWinPanel, 1);
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || this->m_pCBSystem->m_fTimeFund - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || BYTE1(CEffectSystem::DestroyAllEffect()->m_pVertexBuffer) )
  {
    v11 = (CCBUI *)this->m_pCBSystem->m_pUI;
    if ( this->m_pRoleState->m_bWeSneakAttackEnemy )
    {
      (*(void (**)(UIStatic *, _DWORD))v11->m_pRoleStateImmunity[10]->m_fontcolor.ColorQuadFmt)(
        v11->m_pRoleStateImmunity[10],
        0);
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    (*(void (**)(UIStatic *, _DWORD))v11->m_pWinPanel->m_fontcolor.ColorQuadFmt)(v11->m_pWinPanel, 0);
    *(_DWORD *)(v5 + 16) = 4;
  }
  return 0;
}

// 0x004FD3D0
int CCBStage::HasNormalAttackRole(int _24)
{
  __int32 v3; // ebp
  __int32 v4; // ecx
  char *v5; // ebx
  int v6; // eax
  int v8; // edi
  signed int i; // edi
  int v10; // edi
  int v11; // ebx
  CCBRoleState *m_pRoleState; // ecx
  int j; // edi
  int v14; // ecx
  int v15; // edx
  CCBStageRole **v16; // eax
  int v17; // eax
  char *v18; // eax
  char v19; // dl
  int k; // eax
  int v21; // ebp
  int v22; // eax
  CCBStageRole **v23; // ecx
  int v24; // eax
  CCBStageRole **v25; // ecx
  unsigned int *a2; // [esp+10h] [ebp-10h]
  CCBStageRole **m_pRole; // [esp+14h] [ebp-Ch]
  CCBStageRole **v28; // [esp+14h] [ebp-Ch]
  char *v29; // [esp+18h] [ebp-8h]
  int v30; // [esp+18h] [ebp-8h]
  int roleIdx; // [esp+1Ch] [ebp-4h]

  if ( (byte_17AAA2C & 1) == 0 )
  {
    dword_17AAA20 = 0;
    byte_17AAA2C |= 1u;
    dword_17AAA24 = 0;
    dword_17AAA28 = 0;
    atexit(nullsub_20);
  }
  v3 = 2632 * this->m_bHideSceneAndRole;
  roleIdx = *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3);
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (char *)&this->m_fDamageNumPosY[5] + v4;
  v29 = v5;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v4 + 1) )
  {
    this->m_pEffect = 0;
    this->m_BFARole = 0;
    LOWORD(this->m_BFARound) = 0;
    BYTE2(this->m_BFARound) = 0;
    v6 = sub_503680(
           (char **)this,
           *(__int32 *)((char *)&this->m_Task[0].eTask + v4),
           (unsigned int *)((char *)&this->m_Task[0].SubTask[17].param.f2 + v3));
    dword_17AAD3C = v6;
    if ( v6 == -1 )
    {
      v5[41] = 1;
      *((_DWORD *)v5 + 9) = -1;
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
    sub_503AE0(
      (void **)&this->m_pCBSystem,
      v6,
      *((_DWORD *)v5 + 11),
      *(int *)((char *)&this->m_Task[0].SubTask[17].param.n3 + v3));
    v5[41] = 1;
  }
  if ( (v5[44] & 1) != 0 )
  {
    v8 = 0;
    a2 = (unsigned int *)((char *)&this->m_Task[0].SubTask[17].param.f2 + v3);
    m_pRole = this->m_pRole;
    do
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->CancelVariance(a2, v8)
        && !((CCBStageRole *)this->m_pRoleState)->IsActive(v8)
        && sub_50A4B0(*m_pRole) )
      {
        dword_17AAD3C = v8;
        sub_503AE0(
          (void **)&this->m_pCBSystem,
          v8,
          *((_DWORD *)v5 + 11),
          *(int *)((char *)&this->m_Task[0].SubTask[17].param.n3 + v3));
      }
      ++v8;
      ++m_pRole;
    }
    while ( v8 < 11 );
    sub_503AE0(
      (void **)&this->m_pCBSystem,
      dword_17AAD3C,
      *((_DWORD *)v5 + 11),
      *(int *)((char *)&this->m_Task[0].SubTask[17].param.n3 + v3));
    for ( i = 0; i < 11; ++i )
    {
      if ( *((_BYTE *)&this->m_pEffect + i) && !((CCBRoleState *)this->m_pRoleState)->CancelVariance(a2, i) )
        *((_BYTE *)&this->m_pEffect + i) = 0;
    }
    if ( (unsigned int)dword_17AAD3C <= 0xA && ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(roleIdx) < 4 )
      ((CCBStageRole *)this->m_pRole[roleIdx])->SetBladeTime(dword_17AAD3C);
  }
  else
  {
    v10 = 0;
    v11 = 0;
    v28 = this->m_pRole;
    do
    {
      m_pRoleState = (CCBRoleState *)this->m_pRoleState;
      if ( m_pRoleState->m_Role[v11].bValid
        && ((CCBStageRole *)m_pRoleState)->IsActive(v10) == 1
        && sub_50A4B0(*v28) )
      {
        dword_17AAD3C = v10;
        sub_503AE0(
          (void **)&this->m_pCBSystem,
          v10,
          *((_DWORD *)v29 + 11),
          *(int *)((char *)&this->m_Task[0].SubTask[17].param.n3 + v3));
      }
      ++v11;
      ++v10;
      ++v28;
    }
    while ( v11 < 11 );
    a2 = (unsigned int *)((char *)&this->m_Task[0].SubTask[17].param.f2 + v3);
    if ( !sub_4F6CD0(a2) )
    {
      for ( j = 0; j < 11; ++j )
      {
        if ( *((_BYTE *)&this->m_pEffect + j) && !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(j) )
          *((_BYTE *)&this->m_pEffect + j) = 0;
      }
    }
    v5 = v29;
  }
  v14 = 0;
  v15 = 0;
  v30 = 0;
  v16 = this->m_pRole;
  do
  {
    if ( this->m_pRoleState->m_Role[v14].bValid )
    {
      if ( *((_BYTE *)&this->m_pEffect + v15) )
      {
        ++v30;
        LOBYTE((*v16)->m_fTimeScale) = 1;
        BYTE2((*v16)->m_bPaused) = 1;
      }
      else
      {
        LOBYTE((*v16)->m_fTimeScale) = 0;
        BYTE2((*v16)->m_bPaused) = 0;
      }
    }
    ++v14;
    ++v15;
    ++v16;
  }
  while ( v14 < 11 );
  if ( v30 <= 0 )
    v5[41] = 0;
  if ( g_Input.m_shiftedKeyStates[207] == 1 && ((v17 = g_Input.m_shiftedKeyStates[204] & 0xF, v17 == 1) || v17 == 2) )
  {
    if ( (v5[44] & 0x10) != 0 )
    {
      *((_BYTE *)&this->m_Task[0].SubTask[17].nEffLinker + v3 + 1) = 0;
      *((_BYTE *)&this->m_Task[0].SubTask[17].nEffLinker + v3) = 0;
      *(_DWORD *)((char *)&this->m_Task[0].SubTask[17].param.f3 + v3) = dword_17AAD3C;
      if ( dword_17AAD3C == -1 )
        return 0;
    }
    else
    {
      *((_BYTE *)&this->m_Task[0].SubTask[17].nEffLinker + v3) = 0;
      *((_BYTE *)&this->m_Task[0].SubTask[17].nEffLinker + v3 + 1) = 1;
      v18 = (char *)&this->m_Task[0].SubTask[17].bEffWorked + v3 + 1;
      *(_DWORD *)v18 = this->m_pEffect;
      *((_DWORD *)v18 + 1) = this->m_BFARole;
      *((_WORD *)v18 + 4) = this->m_BFARound;
      v18[10] = BYTE2(this->m_BFARound);
      v19 = 0;
      for ( k = 0; k < 11; ++k )
      {
        if ( *((_BYTE *)&this->m_pEffect + k) )
          v19 = 1;
      }
      if ( !v19 )
        return 0;
    }
    v21 = roleIdx;
    *((_DWORD *)v5 + 9) = dword_17AAD3C;
    *((_DWORD *)v5 + 4) = 4;
    v22 = 0;
    BYTE2(this->m_pRole[roleIdx]->m_bPaused) = 0;
    v23 = this->m_pRole;
    do
    {
      if ( this->m_pRoleState->m_Role[v22].bValid )
      {
        LOBYTE((*v23)->m_fTimeScale) = 0;
        BYTE2((*v23)->m_bPaused) = 0;
      }
      ++v22;
      ++v23;
    }
    while ( v22 < 11 );
  }
  else
  {
    v21 = roleIdx;
  }
  if ( v5[43] == 1
    || g_Input.m_shiftedKeyStates[211] == 1 && (g_Input.m_shiftedKeyStates[208] & 0xF) == 1
    || g_Input.m_DIKToKEY[5] == 1
    || *a2 == 262 && ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v21, 16)
    || *a2 == 261 && ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v21, 15) )
  {
    *((_DWORD *)v5 + 9) = -1;
    *((_DWORD *)v5 + 4) = 4;
    v24 = 0;
    v25 = this->m_pRole;
    do
    {
      if ( this->m_pRoleState->m_Role[v24].bValid )
      {
        LOBYTE((*v25)->m_fTimeScale) = 0;
        BYTE2((*v25)->m_bPaused) = 0;
      }
      ++v24;
      ++v25;
    }
    while ( v24 < 11 );
  }
  return 0;
}

// 0x004FD880
int CCBStage::ClearRoleAllTask(int a2)
{
  __int32 v3; // edi
  __int32 v4; // eax
  char *v5; // ebp
  const char *ItemNum; // eax
  int RoleNum; // eax
  UIStatic *m_pWinPanel; // ecx
  UIStatic *v10; // ecx
  int v11; // [esp-4h] [ebp-10h]

  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (char *)&this->m_fDamageNumPosY[5] + v4;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v4 + 1) )
  {
    if ( BYTE1(CEffectSystem::DestroyAllEffect()->m_pVertexBuffer) )
    {
      v5[41] = 1;
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
    if ( *(int *)((char *)&this->m_Task[0].SubTask[17].param.n3 + v3) )
    {
      v11 = *(int *)((char *)&this->m_Task[0].SubTask[17].param.n3 + v3);
      if ( *(_DWORD *)((char *)&this->m_Task[0].SubTask[17].param.f2 + v3) == 270 )
      {
        ItemNum = (const char *)((PAL_GDB *)&g_GDB)->GDB_GetItemNum(v11);
        if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
          ((UIWnd *)this->m_pCBSystem->m_pUI->m_pWinPanel)->SetEnable(ItemNum, 1);
        else
          ((UIWnd *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10])->SetEnable(ItemNum, 1);
      }
      else
      {
        RoleNum = ((PAL_GDB *)&g_GDB)->GDB_GetRoleNum(v11);
        if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
          ((UIWnd *)this->m_pCBSystem->m_pUI->m_pWinPanel)->SetEnable((const char *)(RoleNum + 28), 1);
        else
          ((UIWnd *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10])->SetEnable((const char *)(RoleNum + 28), 1);
      }
    }
    if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pWinPanel;
    else
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10];
    (*(void (**)(UIStatic *, int))m_pWinPanel->m_fontcolor.ColorQuadFmt)(m_pWinPanel, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1
    || this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) > *((float *)v5 + 8)
    || BYTE1(CEffectSystem::DestroyAllEffect()->m_pVertexBuffer) )
  {
    if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
      v10 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pWinPanel;
    else
      v10 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10];
    (*(void (**)(UIStatic *, _DWORD))v10->m_fontcolor.ColorQuadFmt)(v10, 0);
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x004FDA10
int CCBStage::EndRoleAllTask(int a2)
{
  __int32 v3; // edi
  __int32 v4; // eax
  char *v5; // ebp
  int SkillNum; // eax
  UIStatic *m_pWinPanel; // ecx
  UIStatic *v8; // ecx

  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (char *)&this->m_fDamageNumPosY[5] + v4;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v4 + 1) )
  {
    SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(*(__int32 *)((char *)&this->m_Task[0].eTask + v4));
    if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
    {
      ((UIWnd *)this->m_pCBSystem->m_pUI->m_pWinPanel)->SetEnable((const char *)(SkillNum + 4), 1);
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pWinPanel;
    }
    else
    {
      ((UIWnd *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10])->SetEnable((const char *)(SkillNum + 4), 1);
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10];
    }
    (*(void (**)(UIStatic *, int))m_pWinPanel->m_fontcolor.ColorQuadFmt)(m_pWinPanel, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) > *((float *)v5 + 8) )
  {
    if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
      v8 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pWinPanel;
    else
      v8 = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10];
    (*(void (**)(UIStatic *, _DWORD))v8->m_fontcolor.ColorQuadFmt)(v8, 0);
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x004FDB10
int CCBStage::GetRoleTaskNum(int a2)
{
  __int32 v3; // eax
  __int32 v4; // ecx
  char *v5; // esi
  _DWORD *v6; // ecx
  CCBStageCam *m_pCam; // ecx
  double v8; // st7
  double HoldTime; // st7
  double Data; // st7
  int v11; // eax
  char v12; // dl
  struct gbVec3D v14; // [esp+8h] [ebp-20h] BYREF
  int v15; // [esp+14h] [ebp-14h]
  int v16; // [esp+18h] [ebp-10h]
  int v17; // [esp+1Ch] [ebp-Ch]
  float v18; // [esp+20h] [ebp-8h] BYREF
  float v19; // [esp+24h] [ebp-4h] BYREF

  v18 = 0.0;
  v19 = 0.0;
  memset(&v14, 0, sizeof(v14));
  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (char *)&this->m_fDamageNumPosY[5] + v4;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v4 + 1) )
  {
    v6 = (__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3);
    *((float *)&this->m_ptMousePos.x + *v6) = *((float *)&this->m_ptMousePos.x + *v6) + 10.0;
    v14 = *(struct gbVec3D *)&this->m_pRole[*v6]->m_Task[35].cmd.bDestRole[7];
    *((_DWORD *)v5 + 16) = LODWORD(v14.x);
    *((_DWORD *)v5 + 17) = LODWORD(v14.z);
    v16 = *(&this->m_ptMousePos.x + *v6);
    v17 = (int)*(float *)&v16;
    *((float *)v5 + 18) = *(float *)&v17;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *((_DWORD *)v5 + 19) = (g_RandSeed >> 16) & 0x1F;
    v5[41] = 1;
  }
  v14.x = *((float *)v5 + 16);
  v14.z = *((float *)v5 + 17);
  m_pCam = (CCBStageCam *)this->m_pCam;
  v14.y = 50.0;
  ((gbCamera *)&m_pCam->OrthoSize)->PointWorldToScr(&v14, &v18, &v19);
  sprintf(byte_17AA920, "%d", *((_DWORD *)v5 + 11));
  v8 = (this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6)) / *((float *)v5 + 8);
  if ( v8 > 1.0 )
    v8 = 1.0;
  *(float *)&v17 = (1.0 - v8) * 255.0;
  v16 = (int)*(float *)&v17;
  *(float *)&v17 = (this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6)) * 30.0;
  v15 = (int)*(float *)&v17;
  HoldTime = (double)g_Input.KeyInfo[120].HoldTime;
  v15 = *((_DWORD *)v5 + 18) - (__int64)((1.0 - v19) * HoldTime * -0.5) - v15;
  v19 = 1.0 - ((double)v15 + (double)v15) / HoldTime;
  Data = (double)g_Input.KeyInfo[120].Data;
  v15 = *((_DWORD *)v5 + 19) - (__int64)((v18 + 1.0) * Data * -0.5) - 16;
  v18 = ((double)v15 + (double)v15) / Data - 1.0;
  v11 = *((_DWORD *)v5 + 13);
  if ( v11 )
  {
    v12 = v5[52];
    BYTE1(v17) = BYTE1(*((_DWORD *)v5 + 13));
    BYTE2(v17) = BYTE2(v11);
    LOBYTE(v17) = v12;
  }
  else
  {
    *(_WORD *)((char *)&v17 + 1) = 12850;
    LOBYTE(v17) = -1;
  }
  HIBYTE(v17) = v16;
  ((CCBStage *)this->m_TempStorageNGH)->InitRound();
  if ( this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) > *((float *)v5 + 8) )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FDD90
int CCBStage::SelectRole(int a2)
{
  __int32 v3; // eax
  __int32 v4; // ecx
  float *v5; // esi
  double v6; // st7
  double HoldTime; // st7
  double Data; // st7
  float v9; // edx
  struct gbVec3D v11; // [esp+8h] [ebp-20h] BYREF
  int v12; // [esp+14h] [ebp-14h]
  int v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+1Ch] [ebp-Ch]
  float v15; // [esp+20h] [ebp-8h] BYREF
  float v16; // [esp+24h] [ebp-4h] BYREF

  v15 = 0.0;
  v16 = 0.0;
  memset(&v11, 0, sizeof(v11));
  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (float *)((char *)&this->m_fDamageNumPosY[5] + v4);
  if ( !*((_BYTE *)&this->m_nCurSubTask + v4 + 1) )
  {
    v11 = *(struct gbVec3D *)&this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3)]->m_Task[35].cmd.bDestRole[10];
    v11.y = v11.y + 80.0;
    *(struct gbVec3D *)((char *)&this->m_Task[0].SubTask[0].dwID + v4) = v11;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *(_DWORD *)((char *)&this->m_Task[0].SubTask[0].fTime + v4) = (g_RandSeed >> 16) & 0x1F;
    *((_BYTE *)&this->m_nCurSubTask + v4 + 1) = 1;
  }
  v11 = *(struct gbVec3D *)((char *)&this->m_Task[0].SubTask[0].dwID + v4);
  ((gbCamera *)&this->m_pCam->OrthoSize)->PointWorldToScr(&v11, &v15, &v16);
  v6 = (this->m_pCBSystem->m_fTimeFund - v5[6]) / v5[8];
  *(float *)&v14 = v6;
  if ( v6 > 1.0 )
    *(float *)&v14 = 1.0;
  *(float *)&v13 = (1.0 - *(float *)&v14) * 255.0;
  v12 = (int)*(float *)&v13;
  *(float *)&v13 = *(float *)&v14 * 32.0;
  v14 = (int)*(float *)&v13;
  HoldTime = (double)g_Input.KeyInfo[120].HoldTime;
  v13 = 16 - (__int64)((1.0 - v16) * HoldTime * -0.5) - v14;
  v16 = 1.0 - ((double)v13 + (double)v13) / HoldTime;
  Data = (double)g_Input.KeyInfo[120].Data;
  LODWORD(v9) = *((_DWORD *)v5 + 19) - (__int64)((v15 + 1.0) * Data * -0.5) - 16;
  *(_WORD *)((char *)&v14 + 1) = 13055;
  *(float *)&v13 = v9;
  LOBYTE(v14) = -1;
  HIBYTE(v14) = v12;
  v15 = ((double)v13 + (double)v13) / Data - 1.0;
  ((CCBStage *)this->m_TempStorageNGH)->InitRound();
  if ( this->m_pCBSystem->m_fTimeFund - v5[6] > v5[8] )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FDFC0
int CCBStage::ProcWait(int a2)
{
  CCBStage *v2; // esi
  __int32 m_bHideSceneAndRole; // eax
  int v4; // ecx
  char *v5; // eax
  int v6; // ebx
  int v7; // eax
  gbCamera *p_OrthoSize; // ecx
  double v9; // st7
  double HoldTime; // st7
  double Data; // st7
  int v12; // edx
  char *v14; // [esp-8h] [ebp-B8h]
  char *v15; // [esp-4h] [ebp-B4h]
  int v16; // [esp-4h] [ebp-B4h]
  char Buffer[128]; // [esp+Ch] [ebp-A4h] BYREF
  int v18; // [esp+8Ch] [ebp-24h]
  CCBStage *v19; // [esp+90h] [ebp-20h]
  struct gbVec3D v20; // [esp+94h] [ebp-1Ch] BYREF
  int v21; // [esp+A0h] [ebp-10h]
  float v22; // [esp+A4h] [ebp-Ch]
  float v23; // [esp+A8h] [ebp-8h] BYREF
  float v24; // [esp+ACh] [ebp-4h] BYREF

  v2 = this;
  v23 = 0.0;
  v24 = 0.0;
  memset(&v20, 0, sizeof(v20));
  m_bHideSceneAndRole = this->m_bHideSceneAndRole;
  v19 = this;
  v4 = 329 * m_bHideSceneAndRole;
  v5 = (char *)v19 + 80 * LODWORD(v19->m_fDamageNumPosY[0]);
  v6 = (int)&v5[8 * v4 + 184];
  if ( !v5[8 * v4 + 225] )
  {
    *((float *)&v2->m_ptMousePos.x + *(_DWORD *)&v5[8 * v4 + 232]) = *((float *)&v2->m_ptMousePos.x
                                                                     + *(_DWORD *)&v5[8 * v4 + 232])
                                                                   + 10.0;
    v20 = *(struct gbVec3D *)&v2->m_pRole[*(_DWORD *)&v5[8 * v4 + 232]]->m_Task[35].cmd.bDestRole[10];
    v7 = *(_DWORD *)&v5[8 * v4 + 232];
    *(float *)(v6 + 64) = v20.x;
    *(float *)(v6 + 68) = v20.z;
    v21 = *(&v2->m_ptMousePos.x + v7);
    LODWORD(v22) = (int)*(float *)&v21;
    *(float *)(v6 + 72) = v22;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *(_DWORD *)(v6 + 76) = (g_RandSeed >> 16) & 0x1F;
    *(_BYTE *)(v6 + 41) = 1;
  }
  v20.x = *(float *)(v6 + 64);
  v20.z = *(float *)(v6 + 68);
  p_OrthoSize = (CCBStageCam *)&v2->m_pCam->OrthoSize;
  v20.y = 50.0;
  p_OrthoSize->PointWorldToScr(&v20, &v23, &v24);
  v9 = (v2->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24)) / *(float *)(v6 + 32);
  if ( v9 > 1.0 )
    v9 = 1.0;
  v22 = (1.0 - v9) * 255.0;
  v18 = (int)v22;
  v22 = (v2->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24)) * 30.0;
  v21 = (int)v22;
  HoldTime = (double)g_Input.KeyInfo[120].HoldTime;
  LODWORD(v22) = *(_DWORD *)(v6 + 72) - (__int64)((1.0 - v24) * HoldTime * -0.5) - v21;
  v24 = 1.0 - ((double)SLODWORD(v22) + (double)SLODWORD(v22)) / HoldTime;
  Data = (double)g_Input.KeyInfo[120].Data;
  v12 = *(_DWORD *)(v6 + 76) - (__int64)((v23 + 1.0) * Data * -0.5);
  *(_WORD *)((char *)&v21 + 1) = 13055;
  LODWORD(v22) = v12 - 32;
  LOBYTE(v21) = -1;
  HIBYTE(v21) = v18;
  v23 = ((double)SLODWORD(v22) + (double)SLODWORD(v22)) / Data - 1.0;
  if ( *(_DWORD *)(v6 + 44) == 1 )
  {
    v16 = *(_DWORD *)(v6 + 52);
    v14 = ((PalScript *)(&g_PAL3Data + 312))->SetAppName(aWitch);
    sprintf(Buffer, "%s -%d", v14, v16);
  }
  else if ( *(_DWORD *)(v6 + 44) == 2 )
  {
    v15 = ((PalScript *)(&g_PAL3Data + 312))->SetAppName(aMoney);
    sprintf(Buffer, "%d%s", *(_DWORD *)(v6 + 52), v15);
  }
  else
  {
    strcpy(Buffer, g_SceneMgr.m_szUIString);
    v2 = v19;
  }
  ((CCBStage *)v2->m_TempStorageNGH)->InitRound();
  if ( v2->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24) > *(float *)(v6 + 32) )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FE290
int CCBStage::ProcShowFiveLineup(int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  float *v6; // edi
  double v7; // st7
  double HoldTime; // st7
  double Data; // st7
  __int64 v10; // rax
  float v11; // ebx
  void (***v12)(_DWORD, _DWORD); // ecx
  int v14; // [esp-4h] [ebp-34h]
  struct gbVec3D v15; // [esp+Ch] [ebp-24h] BYREF
  int v16; // [esp+18h] [ebp-18h]
  float v17; // [esp+1Ch] [ebp-14h]
  int v18; // [esp+20h] [ebp-10h]
  float v19; // [esp+24h] [ebp-Ch] BYREF
  float v20; // [esp+28h] [ebp-8h] BYREF
  int id; // [esp+2Ch] [ebp-4h] BYREF

  v19 = 0.0;
  v20 = 0.0;
  v3 = (int)*((_DWORD *)this + 40);
  memset(&v15, 0, sizeof(v15));
  v4 = 2632 * v3;
  v5 = v4 + 80 * (_DWORD)*((_DWORD *)this + 41);
  v6 = (float *)((char *)this + v5 + 184);
  if ( !*((_BYTE *)this + v5 + 225) )
  {
    v15 = *(struct gbVec3D *)&(*(this + *(_DWORD *)((char *)this + v4 + 2760) + 6))->m_Task[1].SubTask[11].eStats;
    v15.y = v15.y + 80.0;
    *(struct gbVec3D *)((char *)this + v5 + 248) = v15;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *(CCBStage **)((char *)this + v5 + 260) = (CCBStage *)((g_RandSeed >> 16) & 0x1F);
    *((_BYTE *)this + v5 + 225) = 1;
  }
  v15 = *(struct gbVec3D *)((char *)this + v5 + 248);
  ((gbCamera *)&(*((_DWORD *)this + 3))->m_pRoleState)->PointWorldToScr(&v15, &v19, &v20);
  v7 = (*(float *)&(*this)->m_WPXVariance - v6[6]) / v6[8];
  *(float *)&v18 = v7;
  if ( v7 > 1.0 )
    *(float *)&v18 = 1.0;
  v17 = (1.0 - *(float *)&v18) * 255.0;
  v16 = (int)v17;
  v17 = *(float *)&v18 * 32.0;
  HoldTime = (double)g_Input.KeyInfo[120].HoldTime;
  v18 = 16 - (__int64)((1.0 - v20) * HoldTime * -0.5);
  v20 = 1.0 - ((double)v18 + (double)v18) / HoldTime;
  Data = (double)g_Input.KeyInfo[120].Data;
  v10 = (__int64)((v19 + 1.0) * Data * -0.5);
  HIDWORD(v10) = *this;
  LODWORD(v11) = *((_DWORD *)v6 + 19) - v10 - 16;
  v17 = v11;
  HIBYTE(id) = v16;
  *(_WORD *)((char *)&id + 1) = 13055;
  LOBYTE(id) = -1;
  v19 = ((double)SLODWORD(v11) + (double)SLODWORD(v11)) / Data - 1.0;
  (***(void (****)(_DWORD, int))(*(_DWORD *)(HIDWORD(v10) + 4) + 1080))(
    *(_DWORD *)(*(_DWORD *)(HIDWORD(v10) + 4) + 1080),
    1);
  ((UIWnd *)*(UIWnd **)&(*this)->m_pRoleState->m_Role[0].byMagicUseTime[46])->SetEnable((const char *)*((_DWORD *)this + 1), 0);
  v14 = id;
  ((CCBStage *)*this)->ProcShowEnemyFiveLineup();
  v14->UpdateAnim();
  ((UIWnd *)*(UIWnd **)&(*this)->m_pRoleState->m_Role[0].byMagicUseTime[46])->GetChild((int)&id);
  ((UIWnd *)*(UIWnd **)&(*this)->m_pRoleState->m_Role[0].byMagicUseTime[46])->ScreenToClient(LODWORD(v11) - 168, v18 - 128);
  ((UIWnd *)*(UIWnd **)&(*this)->m_pRoleState->m_Role[0].byMagicUseTime[46])->SetShow(0);
  if ( *((_BYTE *)v6 + 43) == 1 || *(float *)&(*this)->m_WPXVariance - v6[6] > v6[8] )
  {
    v12 = *(void (****)(_DWORD, _DWORD))&(*this)->m_pRoleState->m_Role[0].byMagicUseTime[46];
    (**v12)(v12, 0);
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x004FE540
int CCBStage::ProcShowEnemyFiveLineup()
{
  return (int)this->m_pRoleState->m_sCombatDialog;
}

// 0x004FE550
int CCBStage::ProcFiveLienupFadeIn(int a2)
{
  __int32 v3; // eax
  __int32 v4; // ecx
  char *v5; // edi
  _DWORD *v6; // ebp
  CCBStageRole *v7; // ecx

  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (char *)&this->m_fDamageNumPosY[5] + v4;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v4 + 1) )
  {
    v6 = (__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3);
    v7 = (CCBStageRole *)this->m_pRole[*v6];
    if ( !BYTE1(v7->m_vThrowVec.x) || !BYTE2(v7->m_vThrowVec.x) )
    {
      if ( BYTE1(v7->m_vThrowVec.x) == 1 )
        v7->GetCurrentTaskIndex();
      ((CCBStageRole *)this->m_pRole[*v6])->DelAllTask(*(&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), 1);
      v5[41] = 1;
      *((_DWORD *)v5 + 4) = 4;
    }
  }
  return 0;
}

// 0x004FE600
int CCBStage::ProcFiveLienupFadeOut(int a2)
{
  __int32 v2; // eax
  __int32 v3; // edx
  char *v4; // esi

  v2 = 2632 * this->m_bHideSceneAndRole;
  v3 = v2 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v4 = (char *)&this->m_fDamageNumPosY[5] + v3;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v3 + 1) )
  {
    ((CCBStageRole *)this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v2)])->GetCurrentTask(*(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v2));
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  return 0;
}

// 0x004FE660
int CCBStage::ProcShowSneakAttackState(int _74)
{
  unsigned __int32 v3; // eax
  char *v4; // ebp
  float *v5; // edi
  unsigned int v7; // eax
  _DWORD *v8; // ecx
  CCBRoleState *m_pRoleState; // ecx
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  double v13; // st7
  __int32 m_bHideSceneAndRole; // eax
  _DWORD *inited; // eax
  int i; // ebx
  int v17; // eax
  CCBRoleState *v18; // ecx
  int v19; // eax
  int v20; // ebx
  float *v21; // ecx
  float *v22; // eax
  double v23; // st7
  double v24; // st7
  int RoleIndex; // edi
  char v26; // [esp+13h] [ebp-5Dh]
  float *v27; // [esp+14h] [ebp-5Ch]
  int a4; // [esp+18h] [ebp-58h] BYREF
  float a3; // [esp+1Ch] [ebp-54h] BYREF
  float a2[3]; // [esp+20h] [ebp-50h] BYREF
  gbVec3D a7; // [esp+2Ch] [ebp-44h] BYREF
  gbVec3D v32; // [esp+38h] [ebp-38h] BYREF
  _DWORD v33[11]; // [esp+44h] [ebp-2Ch] BYREF

  memset(a2, 0, sizeof(a2));
  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = (char *)&this->m_Task[0].SubTask[17].param.f2 + v3;
  v5 = (float *)&this->m_fDamageNumPosY[20 * LODWORD(this->m_fDamageNumPosY[0]) + 5 + v3 / 4];
  v27 = v5;
  if ( !((CCBStageRole *)this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3)])->IsReady(*(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v3)) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( !*((_BYTE *)v5 + 41) && ((CCBStageRole *)this->m_pRole[*((_DWORD *)v4 + 2)])->ForceDelTaskByPFN() )
  {
    this->ResetAll();
    v7 = *((_DWORD *)v4 + 2);
    if ( v7 <= 4 && *(_BYTE *)(*(_DWORD *)&g_SceneMgr.m_slot0[1408 * v7 + 288] + 613) == 5
      || *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 2)) == 7366 )
    {
      a4 = *((_DWORD *)v4 + 3);
      if ( (unsigned int)a4 <= 0xA )
      {
        v8 = sub_50E160;
        a2[0] = (float)a4;
LABEL_25:
        ((CCBStageRole *)this->m_pRole[*((_DWORD *)v4 + 2)])->GetProperCurAction(v8, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), (int *)a2, v4, (_DWORD *)1);
        goto LABEL_26;
      }
      m_pRoleState = (CCBRoleState *)this->m_pRoleState;
      a3 = NAN;
      a4 = -1;
      if ( (unsigned int)m_pRoleState->WriteBackRoleData((int)v4, &a3, &a4) <= 0xA )
      {
        v8 = sub_50E160;
        a2[0] = (float)*((int *)v4 + 3);
        goto LABEL_25;
      }
    }
    else
    {
      v10 = *((_DWORD *)v4 + 2);
      if ( v10 > 4 )
      {
        if ( *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 2)) == 720 )
        {
          v8 = (_DWORD *)CCBStageRole::ProcMagic;
        }
        else if ( *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 2)) == 738
               || (inited = (_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)v4 + 2)),
                   v8 = CCBStageRole::ProcTurnToRole,
                   *inited == 739) )
        {
          v8 = (_DWORD *)CCBStageRole::ProcBlock;
        }
        goto LABEL_25;
      }
      v11 = v10 - 1;
      if ( v11 )
      {
        v12 = v11 - 1;
        if ( v12 )
        {
          if ( v12 == 1 )
          {
            v13 = ((CCBStageRole *)this->m_pRole[3])->AddTask(a2);
            m_bHideSceneAndRole = this->m_bHideSceneAndRole;
            a3 = v13;
            ((CCBStageRole *)this->m_pRole[*((_DWORD *)v4 + 2)])->GetProperCurAction(sub_50E360, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * m_bHideSceneAndRole), (int *)a2, v4, (_DWORD *)1);
            ((CCBStageRole *)this->m_pRole[*((_DWORD *)v4 + 2)])->GetProperCurAction(CCBStage::CheckAllDone, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), (int *)a2, v4, (_DWORD *)1);
            v8 = (_DWORD *)CCBStage::ProcessCommand;
            a2[0] = a3;
            goto LABEL_25;
          }
        }
        else
        {
          ((CCBStageRole *)this->m_pRole[2])->GetProperCurAction(CCBStageRole::ProcMagic, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), (int *)a2, v4, (_DWORD *)1);
        }
        v8 = (_DWORD *)CCBStageRole::ProcTurnToRole;
        goto LABEL_25;
      }
      ((CCBStageRole *)this->m_pRole[1])->GetProperCurAction(CCBStageRole::ProcUseRecoverItem, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), (int *)a2, v4, (_DWORD *)1);
    }
LABEL_26:
    *((_DWORD *)v5 + 16) = 1;
    *((_BYTE *)v5 + 41) = 1;
  }
  if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(*((_DWORD *)v4 + 2)) )
  {
    v26 = 1;
    if ( v4[17] )
    {
      for ( i = 0; i < 11; ++i )
      {
        if ( v4[i + 29] && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(i) )
          v26 = 0;
      }
      if ( v26 )
        goto LABEL_35;
    }
    else if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(*((_DWORD *)v4 + 3)) )
    {
LABEL_35:
      *((_BYTE *)v5 + 41) = 1;
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
  }
  if ( *((_DWORD *)v5 + 16) == 1 )
  {
    v17 = *((_DWORD *)v4 + 2);
    if ( v17 >= 5 && v17 < 11 )
    {
      v18 = (CCBRoleState *)this->m_pRoleState;
      if ( v18->m_Role[0].bValid )
      {
        if ( *(int *)(v18->InitUI(0) + 84) >= 0
          && *(int *)(((CCBRoleState *)this->m_pRoleState)->InitUI(0) + 84) < 11 )
        {
          v19 = ((CCBRoleState *)this->m_pRoleState)->InitUI(0);
          if ( sub_4F06C0((int)v4, *(_DWORD *)(v19 + 84)) )
          {
            v20 = *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(0) + 84);
            v21 = (float *)&this->m_pRole[v20]->m_Task[35].cmd.bDestRole[7];
            v22 = (float *)&this->m_pRole[*((_DWORD *)v4 + 2)]->m_Task[35].cmd.bDestRole[7];
            a7.x = *v21 - *v22;
            a7.y = v21[1] - v22[1];
            v23 = v21[2] - v22[2];
            v32 = a7;
            a7.z = v23;
            v24 = ((gbVec3D *)&v32)->Length();
            if ( v24 < 120.0 && v24 > 50.0 )
            {
              if ( sub_4EED60((int)this->m_pRoleState->m_sCombatDialog, v20) )
              {
                memset(v33, 0, sizeof(v33));
                v33[2] = 0;
                v33[1] = 0;
                v33[3] = v20;
                RoleIndex = this->GetRoleIndex(18, v33, 1);
                if ( RoleIndex != -1 )
                {
                  a7.x = *((float *)v4 + 2);
                  LODWORD(a7.y) = v33[2];
                  LODWORD(a7.z) = v33[3];
                  this->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeIn, 0, 0, 0, &a7, -1082130432, 0);
                  this->GetRoleName(RoleIndex, (int)sub_500840, 0, 0, 0, &a7, -1082130432, 0);
                  this->GetRoleName(RoleIndex, (int)sub_5009C0, 0, 0, 0, &a7, -1082130432, 0);
                  this->GetRoleName(RoleIndex, (int)sub_500AD0, 0, 0, 0, &a7, -1082130432, 0);
                  this->GetRoleName(RoleIndex, (int)CCBStage::ProcFiveLienupFadeOut, 0, 0, 0, &a7, -1082130432, 0);
                  v27[16] = 0.0;
                  ((CCBSystem *)this)->GetStageRoleByIdx(RoleIndex);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( ((CCBStageRole *)this->m_pRole[*((_DWORD *)v4 + 2)])->ForceDelTaskByPFN() || *((_BYTE *)v27 + 43) == 1 )
    *((_DWORD *)v27 + 4) = 4;
  return 0;
}

// 0x004FECE0
int CCBStage::HandleKeyCtrl(int a2)
{
  unsigned __int32 v3; // edi
  int *v4; // ebp
  float *v5; // ebx

  if ( (byte_17AA91C & 1) == 0 )
  {
    dword_17AA910 = 0;
    byte_17AA91C |= 1u;
    dword_17AA914 = 0;
    dword_17AA918 = 0;
    atexit(nullsub_21);
  }
  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = (__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3);
  v5 = (float *)&this->m_fDamageNumPosY[20 * LODWORD(this->m_fDamageNumPosY[0]) + 5 + v3 / 4];
  if ( ((CCBStageRole *)this->m_pRole[*v4])->IsReady(*(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v3)) )
  {
    if ( !*((_BYTE *)v5 + 41) && ((CCBStageRole *)this->m_pRole[*v4])->ForceDelTaskByPFN() )
    {
      *(float *)&dword_17AA910 = (float)*v4;
      *(float *)&dword_17AA914 = (float)*(int *)((char *)&this->m_Task[0].SubTask[17].param.f3 + v3);
      ((CCBStageRole *)this->m_pRole[*v4])->GetProperCurAction(sub_50E550, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), &dword_17AA910, &this->m_Task[0].SubTask[17].param.f2 + 658 * this->m_bHideSceneAndRole, (_DWORD *)1);
      *((_BYTE *)v5 + 41) = 1;
    }
    if ( ((CCBStageRole *)this->m_pRole[*v4])->ForceDelTaskByPFN() )
      *((_DWORD *)v5 + 4) = 4;
    if ( *((_BYTE *)v5 + 43) == 1 )
      *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  else
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
}

// 0x004FEE60
int CCBStage::HandleKeyFriend(int a2)
{
  __int32 v2; // eax
  __int32 v3; // edx
  char *v4; // esi

  v2 = 2632 * this->m_bHideSceneAndRole;
  v3 = v2 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v4 = (char *)&this->m_fDamageNumPosY[5] + v3;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v3 + 1) )
  {
    ((CCBStageRole *)this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v2)])->ProcTransportRun(COERCE_FLOAT(sub_50EB00), 0.0, 0, 0, 0, 0, 3);
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  if ( v4[43] == 1 )
    *((_DWORD *)v4 + 4) = 4;
  return 0;
}

// 0x004FEFB0
int CCBStage::ProcShowName(int a2)
{
  unsigned __int32 v3; // eax
  int *v4; // edi
  float *v5; // ebx
  int v7; // eax
  CCBStageRole *v8; // ecx
  _DWORD *v9; // edx
  int v10; // ecx
  double x; // st7
  __int32 m_bHideSceneAndRole; // eax
  int v13[3]; // [esp+14h] [ebp-Ch] BYREF

  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = (__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3);
  v5 = (float *)&this->m_fDamageNumPosY[20 * LODWORD(this->m_fDamageNumPosY[0]) + 5 + v3 / 4];
  if ( !((CCBStageRole *)this->m_pRole[*v4])->IsReady(*(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v3)) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( !*((_BYTE *)v5 + 41) && ((CCBStageRole *)this->m_pRole[*v4])->ForceDelTaskByPFN() )
  {
    v7 = *v4;
    if ( *v4 >= 0 && v7 < 5 )
    {
      switch ( v7 )
      {
        case 1:
          v8 = (CCBStageRole *)this->m_pRole[1];
          v9 = (_DWORD *)CCBStageRole::ProcUseRecoverItem;
          break;
        case 2:
          v8 = (CCBStageRole *)this->m_pRole[2];
          v9 = (_DWORD *)CCBStageRole::ProcMagic;
          break;
        case 3:
          v8 = (CCBStageRole *)this->m_pRole[3];
          v9 = (_DWORD *)CCBStage::CheckAllDone;
          break;
        default:
          v8 = (CCBStageRole *)this->m_pRole[v7];
          v9 = (_DWORD *)CCBStageRole::ProcTurnToRole;
          break;
      }
      goto LABEL_22;
    }
    if ( *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*v4) == 720 )
    {
      v9 = (_DWORD *)CCBStageRole::ProcMagic;
    }
    else
    {
      if ( *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*v4) != 738
        && *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*v4) != 739 )
      {
        v9 = (_DWORD *)CCBStageRole::ProcTurnToRole;
        v8 = (CCBStageRole *)this->m_pRole[*v4];
LABEL_22:
        v8->GetProperCurAction(v9, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), &v8->m_Task[35].cmd.bDestRole[10], 0, (_DWORD *)1);
        v10 = *v4;
        x = this->m_pRole[*v4]->m_Task[36].vec1.x;
        v13[1] = 0;
        m_bHideSceneAndRole = this->m_bHideSceneAndRole;
        *(float *)v13 = x;
        v13[2] = 0;
        ((CCBStageRole *)this->m_pRole[v10])->GetProperCurAction(CCBStage::ProcessCommand, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * m_bHideSceneAndRole), v13, 0, (_DWORD *)1);
        *((_BYTE *)v5 + 41) = 1;
        goto LABEL_23;
      }
      v9 = (_DWORD *)CCBStageRole::ProcBlock;
    }
    v8 = (CCBStageRole *)this->m_pRole[*v4];
    goto LABEL_22;
  }
LABEL_23:
  if ( ((CCBStageRole *)this->m_pRole[*v4])->ForceDelTaskByPFN() )
    *((_DWORD *)v5 + 4) = 4;
  if ( *((_BYTE *)v5 + 43) == 1 && !*(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(*v4) + 36) )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF1B0
int CCBStage::ProcShowItemName(int a2)
{
  unsigned __int32 v3; // eax
  int *v4; // ebp
  float *v5; // edi
  _DWORD *v6; // edx
  CCBStageRole *v7; // ecx
  int v8; // ecx
  double x; // st7
  __int32 m_bHideSceneAndRole; // eax
  int v12[3]; // [esp+18h] [ebp-Ch] BYREF

  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = (__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3);
  v5 = (float *)&this->m_fDamageNumPosY[20 * LODWORD(this->m_fDamageNumPosY[0]) + 5 + v3 / 4];
  if ( !((CCBStageRole *)this->m_pRole[*v4])->IsReady(*(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v3)) )
    goto LABEL_13;
  if ( *((_BYTE *)v5 + 41) || !((CCBStageRole *)this->m_pRole[*v4])->ForceDelTaskByPFN() )
    goto LABEL_12;
  if ( *v4 == 1 )
    goto LABEL_9;
  if ( *v4 != 2 )
  {
    if ( *v4 != 3 )
    {
      v6 = (_DWORD *)CCBStageRole::ProcTurnToRole;
LABEL_10:
      v7 = (CCBStageRole *)this->m_pRole[*v4];
      v7->GetProperCurAction(v6, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), &v7->m_Task[35].cmd.bDestRole[10], 0, (_DWORD *)1);
      goto LABEL_11;
    }
LABEL_9:
    v6 = (_DWORD *)CCBStageRole::ProcUseRecoverItem;
    goto LABEL_10;
  }
  ((CCBStageRole *)this->m_pRole[2])->GetProperCurAction(CCBStageRole::ProcMagic, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole), &this->m_pRole[2]->m_Task[35].cmd.bDestRole[10], 0, (_DWORD *)1);
LABEL_11:
  v8 = *v4;
  x = this->m_pRole[*v4]->m_Task[36].vec1.x;
  v12[1] = 0;
  m_bHideSceneAndRole = this->m_bHideSceneAndRole;
  *(float *)v12 = x;
  v12[2] = 0;
  ((CCBStageRole *)this->m_pRole[v8])->GetProperCurAction(CCBStage::ProcessCommand, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * m_bHideSceneAndRole), v12, 0, (_DWORD *)1);
  *((_BYTE *)v5 + 41) = 1;
LABEL_12:
  if ( ((CCBStageRole *)this->m_pRole[*v4])->ForceDelTaskByPFN() )
LABEL_13:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF3D0
int CCBStage::ProcShowDamage(int a2)
{
  __int32 v3; // ebp
  __int32 v4; // eax
  char v5; // cl
  char *v6; // eax
  int v7; // edi
  CCBStageRole **m_pRole; // ebx
  int v9; // ecx
  __int32 *v10; // eax
  gbVec3D *v11; // ecx
  int ItemNum; // eax
  int v13; // eax
  CCBStage *v14; // ebp
  CCBRoleState *m_pRoleState; // ecx
  CCBStageRole *v16; // eax
  __int32 *v17; // eax
  __int32 *v18; // esi
  char *v20; // [esp+8h] [ebp-4h]

  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = *((_BYTE *)&this->m_nCurSubTask + v4 + 1);
  v6 = (char *)&this->m_fDamageNumPosY[5] + v4;
  v20 = v6;
  if ( !v5 )
  {
    v7 = 0;
    m_pRole = this->m_pRole;
    do
    {
      if ( *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v7) + 25)
        && *(_BYTE *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v7) + 26) )
      {
        v9 = *(_DWORD *)(((CCBRoleState *)this->m_pRoleState)->InitUI(v7) + 584);
        v10 = (__int32 *)&(*m_pRole)->m_Task[35].cmd.bDestRole[7];
        v11 = (gbVec3D *)&this->m_pScene->m_vecInitFiveLineup[v9];
        * v10 = (*)LODWORD(v11->x);
        v10[1] = LODWORD(v11->y);
        v10[2] = LODWORD(v11->z);
        (*m_pRole)->m_Task[36].fp = (void *)LODWORD((*m_pRole)->m_Task[36].vec1.x);
      }
      ++v7;
      ++m_pRole;
    }
    while ( v7 < 5 );
    ItemNum = ((PAL_GDB *)&g_GDB)->GDB_GetItemNum(*(int *)((char *)&this->m_Task[0].SubTask[17].param.n3 + v3));
    if ( ItemNum )
    {
      if ( *(_BYTE *)(ItemNum + 592) == 2 )
      {
        v13 = *(_DWORD *)((char *)&this->m_Task[0].SubTask[17].param.f3 + v3);
        v14 = (CCBStage *)((char *)&this->m_Task[0].SubTask[17].param.f3 + v3);
        if ( v13 != -1 && v13 != 10 )
        {
          m_pRoleState = (CCBRoleState *)this->m_pRoleState;
          if ( m_pRoleState->m_Role[10].bValid )
          {
            if ( !*(_BYTE *)(m_pRoleState->InitUI(10) + 880) )
            {
              v16 = (CCBStageRole *)this->m_pRole[10];
              if ( LOBYTE(v16->m_bPaused) )
              {
                v16->m_Task[35].cmd.bDestRole[7] = v16->m_Task[35].cmd.bDestRole[10];
                v16->m_Task[35].cmd.bDestRole[8] = v16->m_Task[35].cmd.bValid;
                v16->m_Task[35].cmd.bDestRole[9] = LODWORD(v16->m_Task[35].fTemp);
                ((CCBStageRole *)this->m_pRole[10])->ForceRelease(0);
              }
            }
          }
          v17 = (__int32 *)&this->m_pRole[10]->m_Task[35].cmd.bDestRole[10];
          v18 = (__int32 *)&this->m_pRole[(int)v14->m_pCBSystem]->m_Task[35].cmd.bDestRole[7];
          * v18 = (*)*v17;
          v18[1] = v17[1];
          v18[2] = v17[2];
        }
      }
    }
    v6 = v20;
    v20[41] = 1;
  }
  *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FF5C0
int CCBStage::ProcShowCost(int a2)
{
  __int32 v3; // eax
  __int32 v4; // ecx
  CCBStage *v5; // ebp
  char *v6; // esi
  CCBStageRole *v7; // eax
  int v8; // edx
  Actor *m_TempStorageWPX; // ecx
  int v10; // ebx

  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = v3 + 80 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (CCBStage *)((char *)&this->m_Task[0].SubTask[17].param.f2 + v3);
  v6 = (char *)&this->m_fDamageNumPosY[5] + v4;
  if ( !*((_BYTE *)&this->m_nCurSubTask + v4 + 1) )
  {
    v7 = (CCBStageRole *)this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3)];
    v7->m_Task[36].fp = (void *)LODWORD(v7->m_Task[36].vec1.x);
    *((_BYTE *)&this->m_nCurSubTask + v4 + 1) = 1;
    *(void **)((char *)&this->m_Task[0].SubTask[0].fp + v4) = (void *)((CCBCamControl *)this->m_TempStorageWPX)->KeepCurCam((int)v5->m_pRoleState->m_sCombatDialog);
    v6[62] = 0;
    v6[61] = 0;
    v6[60] = 0;
    *((_DWORD *)v6 + 17) = 0;
    *((_DWORD *)v6 + 16) = 0;
  }
  v8 = *((_DWORD *)v6 + 14);
  m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
  v10 = (int)&m_TempStorageWPX[4].m_name[60 * v8 + 100];
  if ( !v6[60]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)&m_TempStorageWPX[4].m_name[60 * v8 + 124] )
  {
    *((_DWORD *)v6 + 16) = ((CCBStageRole *)m_TempStorageWPX)->~CCBStageRole(v8, 1, v5);
    v6[60] = 1;
  }
  if ( !v6[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)(v10 + 52) )
  {
    *((_DWORD *)v6 + 17) = ((CCBStageRole *)this->m_TempStorageWPX)->~CCBStageRole(*((_DWORD *)v6 + 14), 2, v5);
    v6[61] = 1;
  }
  if ( !v6[62]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)&this->m_TempStorageWPX[4].m_name[60 * *((_DWORD *)v6 + 14) + 128] )
  {
    ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[0].SubTask[17].param.f2 + 658 * this->m_bHideSceneAndRole);
    v6[62] = 1;
  }
  if ( ((CCBStageRole *)this->m_pRole[(int)v5->m_pEditor])->ForceDelTaskByPFN()
    && v6[62]
    && !((CEffMgr *)this->m_pCBSystem->m_pEffMgr)->Render(*((_DWORD *)v6 + 16))
    && !((CEffMgr *)this->m_pCBSystem->m_pEffMgr)->Render(*((_DWORD *)v6 + 17)) )
  {
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x004FF740
int CCBStage::ProcShowCombatDialog(int a2)
{
  __int32 v3; // ecx
  int v4; // edx
  float *v5; // eax
  int v6; // ebp
  int v7; // esi
  CCBStageRole **m_pRole; // ebx
  CCBRoleState *m_pRoleState; // ecx
  CCBStageRole *v10; // eax
  CCBRoleState *v11; // ecx
  CCBStageRole *v12; // ecx
  float *v14; // [esp+4h] [ebp-4h]

  v3 = 329 * this->m_bHideSceneAndRole;
  v4 = 20 * LODWORD(this->m_fDamageNumPosY[0]);
  v5 = (float *)&this->m_fDamageNumPosY[2 * v3 + 5 + v4];
  v14 = v5;
  if ( !*((_BYTE *)&this->m_nCurSubTask + 8 * v3 + v4 * 4 + 1) )
  {
    v6 = 0;
    v7 = 0;
    m_pRole = this->m_pRole;
    do
    {
      m_pRoleState = (CCBRoleState *)this->m_pRoleState;
      if ( m_pRoleState->m_Role[v7].bValid && !*(_BYTE *)(m_pRoleState->InitUI(v6) + 880) )
      {
        v10 = (CCBStageRole *)*m_pRole;
        v10->m_Task[35].cmd.bDestRole[7] = (*m_pRole)->m_Task[35].cmd.bDestRole[10];
        v10->m_Task[35].cmd.bDestRole[8] = v10->m_Task[35].cmd.bValid;
        v10->m_Task[35].cmd.bDestRole[9] = LODWORD(v10->m_Task[35].fTemp);
        (*m_pRole)->m_Task[36].fp = (void *)LODWORD((*m_pRole)->m_Task[36].vec1.x);
      }
      ++v7;
      ++v6;
      ++m_pRole;
    }
    while ( v7 < 11 );
    v11 = (CCBRoleState *)this->m_pRoleState;
    if ( v11->m_Role[10].bValid )
    {
      if ( !*(_BYTE *)(v11->InitUI(10) + 880) )
      {
        v12 = (CCBStageRole *)this->m_pRole[10];
        if ( LOBYTE(v12->m_bPaused) )
          v12->ForceRelease(1);
      }
    }
    v5 = v14;
    *((_BYTE *)v14 + 41) = 1;
  }
  *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF840
int CCBStage::ProcGrabStageRole(int a2)
{
  unsigned __int32 v3; // eax
  CCBStage *v4; // edi
  float *v5; // ebp
  CCBStageRole *v6; // eax
  unsigned int m_pRoleState; // eax
  unsigned int v8; // eax
  __int32 v9; // eax
  __int32 v10; // eax
  __int32 m_bHideSceneAndRole; // eax
  int v13[6]; // [esp+14h] [ebp-1Ch] BYREF
  int v14; // [esp+2Ch] [ebp-4h]

  memset(v13, 0, 12);
  v3 = 2632 * this->m_bHideSceneAndRole;
  v4 = (CCBStage *)((char *)&this->m_Task[0].SubTask[17].param.f2 + v3);
  v5 = (float *)&this->m_fDamageNumPosY[20 * LODWORD(this->m_fDamageNumPosY[0]) + 5 + v3 / 4];
  if ( !((CCBStageRole *)this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3)])->IsReady(*(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v3)) )
    goto LABEL_17;
  if ( !*((_BYTE *)v5 + 41) )
  {
    if ( !((CCBStageRole *)this->m_pRole[(int)v4->m_pEditor])->ForceDelTaskByPFN() )
      return 0;
    ((CCBStageRole *)this->m_pRole[(int)v4->m_pEditor])->GetState();
    v6 = (CCBStageRole *)this->m_pRole[(int)v4->m_pEditor];
    v6->m_Task[36].fp = (void *)LODWORD(v6->m_Task[36].vec1.x);
    m_pRoleState = (unsigned int)v4->m_pRoleState;
    if ( m_pRoleState > 0x10D0 )
    {
      if ( m_pRoleState == 4505 )
      {
        this->ResetAll();
        m_bHideSceneAndRole = this->m_bHideSceneAndRole;
        v14 = 0;
        ((CCBStageRole *)this->m_pRole[(int)v4->m_pEditor])->GetProperCurAction(CCBStageRole::ProcTurnToRole, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * m_bHideSceneAndRole), v13, v4, (_DWORD *)1);
      }
    }
    else if ( m_pRoleState == 4304 || (v8 = m_pRoleState - 4101) == 0 )
    {
      this->ResetAll();
      v10 = this->m_bHideSceneAndRole;
      v14 = 0;
      ((CCBStageRole *)this->m_pRole[(int)v4->m_pEditor])->GetProperCurAction(CCBStageRole::ProcMagic, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * v10), v13, v4, (_DWORD *)1);
    }
    else if ( v8 == 104 )
    {
      this->ResetAll();
      v9 = this->m_bHideSceneAndRole;
      v14 = 0;
      ((CCBStageRole *)this->m_pRole[(int)v4->m_pEditor])->GetProperCurAction(CCBStageRole::ProcUseRecoverItem, 0, 0, 0, *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * v9), v13, v4, (_DWORD *)1);
    }
    *((_BYTE *)v5 + 41) = 1;
  }
  if ( ((CCBStageRole *)this->m_pRole[(int)v4->m_pEditor])->ForceDelTaskByPFN() || *((_BYTE *)v5 + 43) == 1 )
  {
    ((CCBStageRole *)this->m_pRole[(int)v4->m_pEditor])->TryRelease();
LABEL_17:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00503020
int CCBStage::ResetAll()
{
  int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // edi
  __int32 *v7; // eax
  int v8; // ecx
  __int32 *v9; // eax
  gbVec3D *v10; // eax
  float v11; // eax
  __int32 *v12; // esi
  gbVec3D *v13; // eax
  float v14; // edx
  int result; // eax
  __int32 *v16; // eax
  __int32 *v17; // eax
  gbVec3D *v18; // eax
  float z; // eax
  int v20; // ebx
  gbVec3D *v21; // eax
  float y; // ecx
  float v23; // edx
  __int32 *v25; // eax
  __int32 *v26; // eax
  gbVec3D *v27; // eax
  float v28; // eax
  float v29; // [esp+18h] [ebp-38h]
  float v30; // [esp+18h] [ebp-38h]
  float v31; // [esp+18h] [ebp-38h]
  float v32; // [esp+18h] [ebp-38h]
  float v33; // [esp+18h] [ebp-38h]
  float v34; // [esp+18h] [ebp-38h]
  float v35; // [esp+18h] [ebp-38h]
  float v36; // [esp+1Ch] [ebp-34h]
  float v37; // [esp+1Ch] [ebp-34h]
  float v38; // [esp+1Ch] [ebp-34h]
  float v39; // [esp+1Ch] [ebp-34h]
  float v40; // [esp+1Ch] [ebp-34h]
  float v41; // [esp+1Ch] [ebp-34h]
  float v42; // [esp+1Ch] [ebp-34h]
  float v43; // [esp+20h] [ebp-30h]
  float v44; // [esp+20h] [ebp-30h]
  float v45; // [esp+20h] [ebp-30h]
  float v46; // [esp+20h] [ebp-30h]
  float v47; // [esp+20h] [ebp-30h]
  float v48; // [esp+20h] [ebp-30h]
  float v49; // [esp+20h] [ebp-30h]
  int v50; // [esp+24h] [ebp-2Ch]
  int v51; // [esp+24h] [ebp-2Ch]
  int v52; // [esp+24h] [ebp-2Ch]
  int v53; // [esp+24h] [ebp-2Ch]
  int a3; // [esp+30h] [ebp-20h] BYREF
  int a4; // [esp+34h] [ebp-1Ch] BYREF
  gbVec3D v56; // [esp+38h] [ebp-18h] BYREF
  gbVec3D v57; // [esp+44h] [ebp-Ch] BYREF
  __int32 *v58; // [esp+54h] [ebp+4h]
  int a2; // [esp+58h] [ebp+8h]

  if ( (byte_17AA89C & 1) == 0 )
  {
    dword_17AA890 = 0;
    byte_17AA89C |= 1u;
    dword_17AA894 = 0;
    dword_17AA898 = 0;
    atexit(nullsub_30);
  }
  if ( (byte_17AA89C & 2) == 0 )
  {
    dword_17AA880 = 0;
    byte_17AA89C |= 2u;
    dword_17AA884 = 0;
    dword_17AA888 = 0;
    atexit(nullsub_29);
  }
  if ( (byte_17AA89C & 4) == 0 )
  {
    *(_DWORD *)byte_17AA870 = 0;
    byte_17AA89C |= 4u;
    *(_DWORD *)&byte_17AA870[4] = 0;
    *(_DWORD *)&byte_17AA870[8] = 0;
    atexit(nullsub_28);
  }
  v2 = a2;
  a3 = -1;
  a4 = -1;
  v3 = *(_DWORD *)(a2 + 12);
  if ( v3 == -1 )
  {
    v4 = ((CCBRoleState *)this->m_pRoleState)->WriteBackRoleData(a2, &a3, &a4);
    v5 = v4;
    if ( v4 <= 11 )
    {
      v16 = (__int32 *)&this->m_pRole[v4]->m_Task[35].cmd.bDestRole[10];
      dword_17AA880 = *v16;
      dword_17AA884 = v16[1];
      dword_17AA888 = v16[2];
      v17 = (__int32 *)&this->m_pRole[*(_DWORD *)(a2 + 8)]->m_Task[35].cmd.bDestRole[7];
      dword_17AA890 = *v17;
      dword_17AA894 = v17[1];
      dword_17AA898 = v17[2];
      __asm
      {
        fld     dword_17AA898
        fsub    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA894
        fsub    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA890
        fsub    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v18 = ((gbVec3D *)&v57)->gbVec3D(v32, v39, v46);
      v56.x = v18->x;
      v56.y = v18->y;
      z = v18->z;
      *(float *)byte_17AA870 = v56.x;
      v56.z = z;
      *(float *)&byte_17AA870[4] = v56.y;
      *(float *)&byte_17AA870[8] = z;
      ((gbVec3D *)byte_17AA870)->Normalize();
      v20 = *(_DWORD *)(a2 + 8);
      if ( v20 == 4 && *(_BYTE *)(*(_DWORD *)&g_SceneMgr.m_slot4[288] + 613) == 1 )
      {
        ((CCBStageRole *)this->m_pRole[4])->GetStatus(v50);
        __asm { fstp    [esp+2Ch+a2] }
        ((CCBStageRole *)this->m_pRole[v5])->GetStatus(v51);
        __asm
        {
          fadd    [esp+2Ch+a2]
          fadd    ds:flt_56A77C
        }
      }
      else
      {
        ((CCBStageRole *)this->m_pRole[v20])->GetStatus(v50);
        __asm { fstp    [esp+2Ch+a2] }
        ((CCBStageRole *)this->m_pRole[v5])->GetStatus(v52);
        __asm { fadd    [esp+2Ch+a2] }
      }
      __asm
      {
        fld     dword ptr byte_17AA870
        fmul    st, st(1)
      }
      __asm
      {
        fstp    dword ptr byte_17AA870
        fld     dword ptr byte_17AA870+4
        fmul    st, st(1)
        fstp    dword ptr byte_17AA870+4
        fld     dword ptr byte_17AA870+8
        fmul    st, st(1)
        fstp    dword ptr byte_17AA870+8
        fstp    st
        fld     dword ptr byte_17AA870+8
        fadd    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword ptr byte_17AA870+4
        fadd    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword ptr byte_17AA870
        fadd    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v21 = ((gbVec3D *)&v57)->gbVec3D(v33, v40, v47);
      v56.x = v21->x;
      y = v21->y;
      __asm { fld     [esp+20h+var_18] }
      v23 = v21->z;
      result = (int)v58;
      v56.y = y;
      v56.z = v23;
      __asm { fstp    dword ptr [eax] }
      *(float *)result = _ET1;
      *((float *)v58 + 1) = y;
      *((float *)v58 + 2) = v23;
    }
    else
    {
      _EDI = v58;
      v7 = (__int32 *)&this->m_pRole[a3]->m_Task[35].cmd.bDestRole[10];
      * v58 = (*)*v7;
      v8 = a4;
      v58[1] = v7[1];
      v58[2] = v7[2];
      v9 = (__int32 *)&this->m_pRole[v8]->m_Task[35].cmd.bDestRole[10];
      dword_17AA890 = *v9;
      dword_17AA894 = v9[1];
      dword_17AA898 = v9[2];
      __asm
      {
        fld     dword_17AA898
        fadd    dword ptr [edi+8]
        fstp    [esp+30h+var_30]
        fld     dword_17AA894
        fadd    dword ptr [edi+4]
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA890
        fadd    dword ptr [edi]
      }
      __asm { fstp    [esp+38h+var_38] }
      v10 = ((gbVec3D *)&v57)->gbVec3D(v29, v36, v43);
      v56.x = v10->x;
      __asm
      {
        fld     [esp+2Ch+var_18]
        fmul    ds:flt_56A610
      }
      v56.y = v10->y;
      v11 = v10->z;
      __asm
      {
        fstp    dword_17AA880
        fld     [esp+2Ch+var_14]
        fmul    ds:flt_56A610
      }
      v56.z = v11;
      __asm
      {
        fstp    dword_17AA884
        fld     [esp+2Ch+var_10]
        fmul    ds:flt_56A610
        fstp    dword_17AA888
      }
      v12 = (__int32 *)&this->m_pRole[*(_DWORD *)(a2 + 8)]->m_Task[35].cmd.bDestRole[7];
      dword_17AA890 = *v12;
      dword_17AA894 = v12[1];
      dword_17AA898 = v12[2];
      __asm
      {
        fld     dword_17AA898
        fsub    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA894
        fsub    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA890
        fsub    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v56 = *((gbVec3D *)&v57)->gbVec3D(v30, v37, v44);
      *(gbVec3D *)byte_17AA870 = v56;
      ((gbVec3D *)byte_17AA870)->Normalize();
      __asm
      {
        fld     dword ptr byte_17AA870
        fmul    ds:flt_56A64C
      }
      __asm
      {
        fstp    dword ptr byte_17AA870
        fld     dword ptr byte_17AA870+4
        fmul    ds:flt_56A64C
        fstp    dword ptr byte_17AA870+4
        fld     dword ptr byte_17AA870+8
        fmul    ds:flt_56A64C
        fst     dword ptr byte_17AA870+8
        fadd    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword ptr byte_17AA870+4
        fadd    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword ptr byte_17AA870
        fadd    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v13 = ((gbVec3D *)&v57)->gbVec3D(v31, v38, v45);
      v56.x = v13->x;
      v56.y = v13->y;
      v14 = v56.y;
      result = LODWORD(v13->z);
      * v58 = (*)LODWORD(v56.x);
      *((float *)v58 + 1) = v14;
      v58[2] = result;
      LODWORD(v56.z) = result;
    }
  }
  else
  {
    v25 = (__int32 *)&this->m_pRole[v3]->m_Task[35].cmd.bDestRole[10];
    dword_17AA880 = *v25;
    dword_17AA884 = v25[1];
    dword_17AA888 = v25[2];
    v26 = (__int32 *)&this->m_pRole[*(_DWORD *)(a2 + 8)]->m_Task[35].cmd.bDestRole[7];
    dword_17AA890 = *v26;
    dword_17AA894 = v26[1];
    dword_17AA898 = v26[2];
    __asm
    {
      fld     dword_17AA898
      fsub    dword_17AA888
      fstp    [esp+30h+var_30]
      fld     dword_17AA894
      fsub    dword_17AA884
    }
    __asm
    {
      fstp    [esp+34h+var_34]
      fld     dword_17AA890
      fsub    dword_17AA880
    }
    __asm { fstp    [esp+38h+var_38] }
    v27 = ((gbVec3D *)&v57)->gbVec3D(v34, v41, v48);
    v56.x = v27->x;
    v56.y = v27->y;
    v28 = v27->z;
    *(float *)byte_17AA870 = v56.x;
    v56.z = v28;
    *(float *)&byte_17AA870[4] = v56.y;
    *(float *)&byte_17AA870[8] = v28;
    ((gbVec3D *)byte_17AA870)->Normalize();
    ((CCBStageRole *)this->m_pRole[*(_DWORD *)(a2 + 12)])->GetStatus(v50);
    __asm { fstp    [esp+2Ch+a2] }
    ((CCBStageRole *)this->m_pRole[*(_DWORD *)(v2 + 8)])->GetStatus(v53);
    __asm
    {
      fadd    [esp+2Ch+a2]
      fld     dword ptr byte_17AA870
      fmul    st, st(1)
      fstp    dword ptr byte_17AA870
      fld     dword ptr byte_17AA870+4
      fmul    st, st(1)
      fstp    dword ptr byte_17AA870+4
      fld     dword ptr byte_17AA870+8
      fmul    st, st(1)
      fstp    dword ptr byte_17AA870+8
    }
    __asm { fstp    st }
    if ( *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*(_DWORD *)(v2 + 8)) == 7364
      || *(_DWORD *)((CCBRoleState *)this->m_pRoleState)->InitUI(*(_DWORD *)(v2 + 8)) == 7381 )
    {
      __asm
      {
        fld     dword ptr byte_17AA870
        fadd    st, st
        fstp    dword ptr byte_17AA870
        fld     dword ptr byte_17AA870+4
        fadd    st, st
        fstp    dword ptr byte_17AA870+4
        fld     dword ptr byte_17AA870+8
        fadd    st, st
        fstp    dword ptr byte_17AA870+8
      }
    }
    __asm
    {
      fld     dword ptr byte_17AA870+8
      fadd    dword_17AA888
    }
    __asm
    {
      fstp    [esp+30h+var_30]
      fld     dword ptr byte_17AA870+4
      fadd    dword_17AA884
    }
    __asm
    {
      fstp    [esp+34h+var_34]
      fld     dword ptr byte_17AA870
      fadd    dword_17AA880
    }
    __asm { fstp    [esp+38h+var_38] }
    v56 = *((gbVec3D *)&v57)->gbVec3D(v35, v42, v49);
    return v58->operator=(&v56);
  }
  return result;
}

// 0x00503CF0
int CCBStage::UpdatePhysics()
{
  int result; // eax
  tagPOINT *p_m_ptMousePos; // ecx
  int v3; // edx
  double v4; // st7
  __int16 v5; // fps
  double v6; // st6
  bool v7; // c0
  char v8; // c2
  bool v9; // c3

  result = (int)this->m_pCBSystem;
  p_m_ptMousePos = (tagPOINT *)&this->m_ptMousePos;
  v3 = 11;
  v4 = *(double *)(result + 64) * 30.0;
  do
  {
    if ( *(float *)&p_m_ptMousePos->x > 0.0 )
    {
      if ( *(float *)&p_m_ptMousePos->x <= 160.0 )
        *(float *)&p_m_ptMousePos->x = *(float *)&p_m_ptMousePos->x - v4;
      else
        p_m_ptMousePos->x = 1126170624;
    }
    v6 = *(float *)&p_m_ptMousePos->x;
    v7 = v6 < 0.0;
    v8 = 0;
    v9 = v6 == 0.0;
    LOWORD(result) = v5;
    if ( v6 < 0.0 )
      p_m_ptMousePos->x = 0;
    p_m_ptMousePos = (tagPOINT *)((char *)p_m_ptMousePos + 4);
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x005045B0
char CCBStage::ProcessTurn()
{
  double x; // st7
  double y; // st6
  double v4; // st6
  float fWaitTime; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st6
  double v9; // st6
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  float v15; // [esp+2Ch] [ebp-44h]
  float v16; // [esp+30h] [ebp-40h]
  __int32 v17; // [esp+34h] [ebp-3Ch]
  struct tagPOINT Point; // [esp+38h] [ebp-38h] BYREF
  struct gbVec3D v19; // [esp+40h] [ebp-30h] BYREF
  gbVec3D v20; // [esp+4Ch] [ebp-24h] BYREF
  float v21; // [esp+58h] [ebp-18h]
  float v22; // [esp+60h] [ebp-10h]
  gbVec3D v23; // [esp+64h] [ebp-Ch] BYREF

  this->m_Task[0].SubTask[1].param.f2 = 0.0;
  sub_5049F0(this);
  sub_504A80((char *)this);
  ((GRPinput *)&Point)->GetCursorPos();
  if ( ((GRPinput *)&g_Input)->GetKeyState(0x100u) || ((GRPinput *)&g_Input)->GetKeyState(0x101u) )
  {
    x = (double)Point.x;
    v15 = x - *(float *)&this->m_Task[0].SubTask[2].dwReturn;
    y = (double)Point.y;
    *(float *)&v17 = y;
    v4 = y - *(float *)&this->m_Task[0].SubTask[2].bValid;
    this->m_Task[0].SubTask[2].bValid = v17;
    v16 = v4;
    *(float *)&this->m_Task[0].SubTask[2].dwReturn = x;
  }
  else
  {
    v16 = 0.0;
    v15 = 0.0;
    *(float *)&this->m_Task[0].SubTask[2].dwReturn = (float)Point.x;
    *(float *)&this->m_Task[0].SubTask[2].bValid = (float)Point.y;
  }
  if ( !*(_BYTE *)(*(_DWORD *)LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 134) )
  {
    if ( ((GRPinput *)&g_Input)->GetKeyState(0x100u) )
    {
      fWaitTime = this->m_Task[0].SubTask[2].fWaitTime;
      if ( *(_DWORD *)(LODWORD(fWaitTime) + 88) == -1 && !*(_BYTE *)(*(_DWORD *)(LODWORD(fWaitTime) + 20) + 964) )
      {
        v20 = *(gbVec3D *)&this->m_Task[0].SubTask[1].nTemp3;
        ((gbVec3D *)&v20)->Normalize();
        v23 = *(gbVec3D *)&this->m_Task[0].SubTask[1].nTemp4;
        ((gbVec3D *)&v23)->Normalize();
        memset(&v19, 0, sizeof(v19));
        ((gbVec3D *)&v23)->CrossProduct(&v20, &v19);
        ((gbVec3D *)&v19)->Normalize();
        v6 = v16 + v16;
        if ( (g_Input.m_DIKToKEY[58] & 0xF) == 1 )
        {
          v20.x = 0.0;
          v20.y = v6;
          v7 = (float)0.0;
          v20.z = 0.0;
          v8 = v15 + v15;
          v19.x = v19.x * v8;
        }
        else
        {
          v20.y = 0.0;
          v20.x = v6 * v20.x;
          v7 = v6 * v20.z;
          v20.z = v7;
          v8 = v15 + v15;
          v19.x = v8 * v19.x;
        }
        v19.z = v19.z * v8;
        v9 = v7;
        v10 = v20.y;
        v22 = v9;
        v19.y = 0.0;
        v21 = v19.x + v20.x;
        v22 = v22 + v19.z;
        *(float *)&this->m_Task[0].SubTask[1].nTemp1 = v21 + *(float *)&this->m_Task[0].SubTask[1].nTemp1;
        *(float *)&this->m_Task[0].SubTask[1].dwTemp1 = v10 + *(float *)&this->m_Task[0].SubTask[1].dwTemp1;
        this->m_Task[0].SubTask[1].fTemp1 = v22 + this->m_Task[0].SubTask[1].fTemp1;
        ((InputSystem *)1)->ProcessKeyboard();
        ((InputSystem *)0)->ProcessKeyboard();
      }
    }
    v11 = (double)g_Input.m_keyDragStartPositions[1][202] * 0.25;
    if ( (g_Input.m_DIKToKEY[58] & 0xF) == 1 )
    {
      *(float *)&this->m_Task[0].SubTask[1].nEffLinker = v11 * 0.001 + *(float *)&this->m_Task[0].SubTask[1].nEffLinker;
      ((InputSystem *)0)->ProcessKeyboard();
    }
    else if ( (g_Input.m_DIKToKEY[62] & 0xF) == 1 )
    {
      v12 = v11 * 0.001 + *(float *)&this->m_pRoleState;
      this->m_pEditor = 0;
      *(float *)&this->m_pRoleState = v12;
    }
    else
    {
      *(float *)&this->m_Task[0].SubTask[1].bEff1Started = v11 + *(float *)&this->m_Task[0].SubTask[1].bEff1Started;
      ((InputSystem *)1)->ProcessKeyboard();
    }
    if ( ((GRPinput *)&g_Input)->GetKeyState(0x101u)
      && !*(_BYTE *)(*(_DWORD *)(LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 20) + 964) )
    {
      v13 = v15 * 0.0043633231 + *(float *)&this->m_Task[0].SubTask[1].param.dw3;
      *(float *)&this->m_Task[0].SubTask[1].param.dw3 = v13;
      *(float *)&this->m_Task[0].SubTask[1].param.n3 = *(float *)&this->m_Task[0].SubTask[1].param.n3
                                                     - v16 * 0.0043633231;
      if ( v13 <= 3.1415927 )
      {
        if ( v13 <= -3.1415927 )
          v13 = v13 + 6.2831855;
      }
      else
      {
        v13 = v13 - 6.2831855;
      }
      *(float *)&this->m_Task[0].SubTask[1].param.dw3 = v13;
      ((InputSystem *)0)->ProcessKeyboard();
    }
  }
  this->m_Task[0].SubTask[1].bEff1Started = 1120403456;
  ((InputSystem *)0)->ProcessKeyboard();
  ((CameraCtrl *)this)->SetAsCurrent(3);
  ((Combat *)*(_DWORD *)(LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 68))->LogMessage(5, 135, aCamXFYFZF);
  ((Combat *)*(_DWORD *)(LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 68))->LogMessage(5, 150, aCamYawFPitchFR);
  return ((Combat *)*(_DWORD *)(LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 68))->LogMessage(5, 165, aCamFovF);
}

// 0x0050D440
int CCBStage::CheckAllDone()
{
  char *v2; // eax
  int v3; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st7
  double v8; // st7
  int v9; // edi
  int n1; // eax
  char *Instance; // eax
  double v12; // st7
  double v13; // st6
  double m_DeltaTime; // st7
  double v15; // st7
  int v16; // eax
  char *v17; // eax
  int v18; // eax
  char *v19; // eax
  int v20; // [esp+0h] [ebp-14h]
  float v21; // [esp+8h] [ebp-Ch]
  int v22; // [esp+Ch] [ebp-8h]
  int v23; // [esp+Ch] [ebp-8h]
  float v24; // [esp+Ch] [ebp-8h]
  int v25; // [esp+10h] [ebp-4h]
  int v26; // [esp+10h] [ebp-4h]
  int v27; // [esp+18h] [ebp+4h]
  float v28; // [esp+18h] [ebp+4h]

  if ( (byte_17AB6E4 & 1) == 0 )
  {
    byte_17AB6E4 |= 1u;
    dword_17AB6D8 = 0;
    dword_17AB6DC = 0;
    dword_17AB6E0 = 0;
    atexit(nullsub_57);
  }
  if ( (byte_17AB6E4 & 2) == 0 )
  {
    byte_17AB6E4 |= 2u;
    dword_17AB6C8 = 0;
    dword_17AB6CC = 0;
    dword_17AB6D0 = 1065353216;
    atexit(nullsub_56);
  }
  if ( (byte_17AB6E4 & 4) == 0 )
  {
    byte_17AB6E4 |= 4u;
    dword_17AB6B8 = 0;
    dword_17AB6BC = 0;
    dword_17AB6C0 = 0;
    atexit(nullsub_55);
  }
  v2 = (char *)this + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime);
  if ( v2[506] )
  {
    v9 = v27;
  }
  else
  {
    *((_DWORD *)v2 + 122) = -1054867456;
    v3 = 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime);
    this->m_Task[1].SubTask[11].bValid = *(__int32 *)((char *)&this->m_Task[0].SubTask[1].param.dw1 + v3);
    this->m_Task[1].SubTask[11].bExecuted = *(_DWORD *)((char *)&this->m_Task[0].SubTask[1].param.f1 + v3);
    this->m_Task[1].SubTask[11].bAction = *(int *)((char *)&this->m_Task[0].SubTask[1].param.n2 + v3);
    v4 = *(float *)&this->m_Task[1].SubTask[11].bValid - *(float *)&this->m_Task[1].SubTask[11].eStats;
    *(float *)&v22 = *(float *)&this->m_Task[1].SubTask[11].bExecuted - *(float *)&this->m_Task[1].SubTask[11].dwID;
    v5 = *(float *)&this->m_Task[1].SubTask[11].bAction - this->m_Task[1].SubTask[11].fStartTime;
    dword_17AB6DC = v22;
    *(float *)&v25 = v5;
    *(float *)&dword_17AB6D8 = v4;
    dword_17AB6E0 = v25;
    v6 = ((gbVec3D *)&dword_17AB6D8)->Length();
    if ( v6 < 2.0 )
    {
      this->m_Task[1].SubTask[11].eStats = this->m_Task[1].SubTask[11].bValid;
      this->m_Task[1].SubTask[11].dwID = this->m_Task[1].SubTask[11].bExecuted;
      LODWORD(this->m_Task[1].SubTask[11].fStartTime) = this->m_Task[1].SubTask[11].bAction;
      *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 1) = 1;
      return 0;
    }
    ((gbVec3D *)&dword_17AB6D8)->Normalize();
    flt_17ABCDC = acos(
                    *(float *)&dword_17AB6D0 * *(float *)&dword_17AB6E0
                  + *(float *)&dword_17AB6CC * *(float *)&dword_17AB6DC
                  + *(float *)&dword_17AB6C8 * *(float *)&dword_17AB6D8);
    if ( *(float *)&dword_17AB6D8 < 0.0 )
      flt_17ABCDC = 6.2831855 - flt_17ABCDC;
    *((float *)&this->m_Task[0].SubTask[1].nTemp2 + 24 * LODWORD(this->m_Task[0].SubTask[1].fStartTime)) = flt_17ABCDC * 57.29578;
    this->m_Task[1].SubTask[11].bRequireToEnd = dword_17AB6D8;
    v28 = v6;
    v8 = v28 + v28;
    this->m_Task[1].SubTask[11].param.n1 = dword_17AB6DC;
    this->m_Task[1].SubTask[11].param.dw1 = dword_17AB6E0;
    *(float *)&this->m_Task[1].SubTask[11].bRequireToEnd = v8 * *(float *)&this->m_Task[1].SubTask[11].bRequireToEnd;
    *(float *)&this->m_Task[1].SubTask[11].param.n1 = v8 * *(float *)&this->m_Task[1].SubTask[11].param.n1;
    *(float *)&this->m_Task[1].SubTask[11].param.dw1 = v8 * *(float *)&this->m_Task[1].SubTask[11].param.dw1;
    if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(this->m_Task[0].SubTask[0].param.n1) )
      this->m_Task[1].SubTask[10].nTemp4 = 31;
    else
      this->m_Task[1].SubTask[10].nTemp4 = 52;
    ((CCBStageRole *)this)->IsGrabedBy();
    v9 = 0;
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 2) = 1;
    ((CCBStageRole *)this)->ClearBadPushTask(0.40000001);
    n1 = this->m_Task[0].SubTask[0].param.n1;
    BYTE1(this->m_Task[0].SubTask[0].bExecuted) = 1;
    if ( n1 == 3 )
    {
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(aWe013, 1);
    }
  }
  v12 = *(float *)&this->m_Task[1].SubTask[11].bValid - *(float *)&this->m_Task[1].SubTask[11].eStats;
  *(float *)&v23 = *(float *)&this->m_Task[1].SubTask[11].bExecuted - *(float *)&this->m_Task[1].SubTask[11].dwID;
  v13 = *(float *)&this->m_Task[1].SubTask[11].bAction - this->m_Task[1].SubTask[11].fStartTime;
  dword_17AB6DC = v23;
  *(float *)&v26 = v13;
  *(float *)&dword_17AB6D8 = v12;
  dword_17AB6E0 = v26;
  if ( v9 == this->m_Task[1].SubTask[11].bEff1Started )
    *((_DWORD *)&this->m_Task[0].SubTask[1].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[1].fStartTime)) = 1120403456;
  if ( *(&this->m_Task[0].SubTask[1].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[1].fStartTime)) > 0.0
    && ((gbVec3D *)&dword_17AB6D8)->Length() > 2.0 )
  {
    m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
    v21 = *(float *)&this->m_Task[1].SubTask[11].bRequireToEnd * m_DeltaTime;
    v24 = *(float *)&this->m_Task[1].SubTask[11].param.n1 * m_DeltaTime;
    v15 = m_DeltaTime * *(float *)&this->m_Task[1].SubTask[11].param.dw1;
    *(float *)&this->m_Task[1].SubTask[11].eStats = v21 + *(float *)&this->m_Task[1].SubTask[11].eStats;
    *(float *)&this->m_Task[1].SubTask[11].dwID = v24 + *(float *)&this->m_Task[1].SubTask[11].dwID;
    this->m_Task[1].SubTask[11].fStartTime = v15 + this->m_Task[1].SubTask[11].fStartTime;
    this->m_Task[1].SubTask[11].param.f1 = this->m_pCBSystem->m_pUtil->m_DeltaTime * 720.0
                                         + this->m_Task[1].SubTask[11].param.f1;
  }
  if ( v9 == this->m_Task[1].SubTask[11].bEff2Started && ((gbVec3D *)&dword_17AB6D8)->Length() <= 2.0 )
    *((_DWORD *)&this->m_Task[0].SubTask[1].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[1].fStartTime)) = -1054867456;
  ((gbVec3D *)&dword_17AB6D8)->Normalize();
  flt_17ABCDC = acos(
                  *(float *)&dword_17AB6D0 * *(float *)&dword_17AB6E0
                + *(float *)&dword_17AB6CC * *(float *)&dword_17AB6DC
                + *(float *)&dword_17AB6C8 * *(float *)&dword_17AB6D8);
  if ( *(float *)&dword_17AB6D8 < 0.0 )
    flt_17ABCDC = 6.2831855 - flt_17ABCDC;
  if ( fabs(
         flt_17ABCDC * 57.29578
       - *((float *)&this->m_Task[0].SubTask[1].nTemp2 + 24 * LODWORD(this->m_Task[0].SubTask[1].fStartTime))) >= 1.570796370506287 )
  {
    this->m_Task[1].SubTask[11].eStats = this->m_Task[1].SubTask[11].bValid;
    this->m_Task[1].SubTask[11].dwID = this->m_Task[1].SubTask[11].bExecuted;
    LODWORD(this->m_Task[1].SubTask[11].fStartTime) = this->m_Task[1].SubTask[11].bAction;
    *((_DWORD *)&this->m_Task[0].SubTask[1].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[1].fStartTime)) = -1054867456;
  }
  if ( v9 == LODWORD(this->m_Task[1].SubTask[11].param.f2) )
  {
    this->m_Task[1].SubTask[11].eStats = this->m_Task[1].SubTask[11].bValid;
    this->m_Task[1].SubTask[11].dwID = this->m_Task[1].SubTask[11].bExecuted;
    LODWORD(this->m_Task[1].SubTask[11].fStartTime) = this->m_Task[1].SubTask[11].bAction;
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 1) = 1;
    v16 = this->m_Task[0].SubTask[0].param.n1;
    BYTE1(this->m_Task[0].SubTask[0].bExecuted) = 0;
    if ( v16 == 3 )
    {
      v17 = (char *)CScreenMode::GetInstance();
      ((CCBStageRole *)v17)->PlaySound(aWe013, v20);
    }
  }
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(this->m_Task[0].SubTask[0].param.n1) )
  {
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 1) = 1;
    v18 = this->m_Task[0].SubTask[0].param.n1;
    BYTE1(this->m_Task[0].SubTask[0].bExecuted) = 0;
    if ( v18 == 3 )
    {
      v19 = (char *)CScreenMode::GetInstance();
      ((CCBStageRole *)v19)->PlaySound(aWe013, v20);
    }
  }
  return 0;
}

// 0x0050E0D0
int CCBStage::ProcessCommand()
{
  float *v2; // eax
  int n1; // edx

  v2 = (float *)((char *)this + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime));
  if ( !*((_BYTE *)v2 + 506) )
  {
    n1 = this->m_Task[0].SubTask[0].param.n1;
    this->m_Task[1].SubTask[11].param.f1 = v2[108];
    if ( ((CCBStageRole *)this->m_pRoleState)->IsActive(n1) )
      this->m_Task[1].SubTask[10].nTemp4 = 32;
    else
      this->m_Task[1].SubTask[10].nTemp4 = 50;
    ((CCBStageRole *)this)->IsGrabedBy();
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 2) = 1;
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 1) = 1;
  }
  return 0;
}
