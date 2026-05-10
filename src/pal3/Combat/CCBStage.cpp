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
int sub_4FBE50(...);
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
extern unsigned char byte_17AA89C;
extern unsigned char byte_17AA91C;
extern unsigned char byte_17AA920;
extern unsigned char byte_17AAA2C;
extern unsigned char byte_17AB6E4;
extern unsigned char byte_5DB6C4;
extern int dword_17A990C;
extern int dword_17AA870;
extern int dword_17AA874;
extern int dword_17AA878;
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

  strcpy(&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 24], v2);
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 284] = v3;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 288] = v4;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 20] = 1;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 296] = 1103101952;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 280] = v5;
  result = *(_DWORD *)&this->m_pCBSystem[16] + 1;
  *(_DWORD *)&this->m_pCBSystem[16] = result;
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

  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 284] = v2;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 288] = v3;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 292] = v4;
  *(float *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 296] = v5;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 20] = 5;
  *(_DWORD *)&this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 280] = *(_DWORD *)&this->m_pCBSystem[8];
  this->m_pCBSystem[280 * *(_DWORD *)&this->m_pCBSystem[16] + 283] = v6;
  result = *(_DWORD *)&this->m_pCBSystem[16] + 1;
  *(_DWORD *)&this->m_pCBSystem[16] = result;
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
  return &this->m_pCBSystem;
}

// 0x004FB9F0
CCBStage::~CCBStage(int _this)
{
  _DWORD *v2; // ecx
  unsigned int result; // eax

  v2 = (_DWORD *)(this + 80);
  *v2 = 0;
  v2[1] = 0;
  *(_BYTE *)(this + 152) = 0;
  *(_DWORD *)(this + 156) = 0;
  memset((void *)(this + 168), 0, 0xA4800u);
  *(_DWORD *)(this + 160) = -1;
  *(_DWORD *)(this + 164) = -1;
  *(_DWORD *)(this + 88) = -1;
  *(_DWORD *)(this + 92) = 0;
  *(_DWORD *)(this + 96) = 0;
  *(_WORD *)(this + 100) = 0;
  *(_BYTE *)(this + 102) = 0;
  memset((void *)(this + 104), 0, 0x2Cu);
  *(_DWORD *)(this + 148) = 0;
  result = gbCrc32Compute(aOver);
  *(_DWORD *)(this + 673960) = result;
  return result;
}

// 0x004FBA70
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char CCBStage::Reset(CCBStage *this)
{
  char *v2; // eax
  unsigned int v3; // edi
  char *v4; // eax
  char result; // al
  CCBStageRole **i; // ebx
  CCBStageRole *v7; // eax
  char *OBBox; // eax
  int v9; // eax
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
      Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_5, 6003),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( CCBStageScene::CCBStageScene((CCBStageScene *)v4) )
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
          Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_5, 109),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      if ( !CCBStageRole::IsIdle((int)OBBox, v3) )
        break;
      if ( (int)++v3 >= 11 )
      {
        v9 = operator new(0x17E8u);
        v23 = 2;
        if ( v9 )
          v10 = (CCBStageCam *)sub_503FA0(v9, this, (struct gbGfxManager *)g_Input.KeyInfo[177].Data);
        else
          v10 = 0;
        this->m_pCam = v10;
        v23 = -1;
        if ( !v10 )
        {
          qmemcpy(
            pExceptionObject,
            Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_5, 124),
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
              Logger::FormatException((Logger *)ArgList, aNewFailedAtCre, aDProjectPal3Co_5, 135),
              sizeof(pExceptionObject));
            _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
          }
          result = CCBStageCam::Destroy((CCBStageCam *)v12);
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
                Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_5, 6003),
                sizeof(pExceptionObject));
              _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
            }
            result = std::codecvt_base::do_always_noconv((std::codecvt_base *)v14);
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
                  Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Co_5, 6003),
                  sizeof(pExceptionObject));
                _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
              }
              result = CCBStageShadow::CCBStageShadow((CCBStageShadow *)v16);
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
                    Logger::FormatException((Logger *)v22, aCNewFailed, aDProjectPal3Co_5, 6003),
                    sizeof(v21));
                  _CxxThrowException(v21, (_ThrowInfo *)&_TI1_AV_Exception__);
                }
                return CCBCamControl::IsPointerUnderMouse((int)v18) != 0;
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
char sub_4FBE50(int _this)
{
  int v2; // ebp
  void *v3; // edi
  void **i; // edi
  void *v5; // ebx
  std::codecvt_base *v6; // ecx
  void (***v7)(_DWORD, int); // ecx
  void *v8; // edi
  std::codecvt_base *v9; // ecx
  void *v10; // edi
  void *v11; // edi
  void *v12; // edi

  v2 = 0;
  if ( *(_DWORD *)(this + 20) )
  {
    CCBStageScene::~CCBStageScene();
    v3 = (void *)*(void **)(this + 20);
    if ( v3 )
    {
      nullsub_3(*(void **)(this + 20));
      operator delete(v3);
    }
    *(_DWORD *)(this + 20) = 0;
    for ( i = (void **)(this + 24); *i; ++i )
    {
      CCBStageRole::IsAtInitPos();
      v5 = (void *)*i;
      if ( *i )
      {
        nullsub_3(*i);
        operator delete(v5);
      }
      *i = 0;
      if ( ++v2 >= 11 )
      {
        v6 = *(std::codecvt_base **)(this + 12);
        if ( v6 )
        {
          v6->codecvt_base::do_always_noconv();
          v7 = *(void (****)(_DWORD, int))(this + 12);
          if ( v7 )
            (**v7)(v7, 1);
          *(_DWORD *)(this + 12) = 0;
          if ( *(_DWORD *)(this + 16) )
          {
            CCBStageCam::Init();
            v8 = (void *)*(void **)(this + 16);
            if ( v8 )
            {
              j_std::codecvt_base::do_always_noconv(*(std::codecvt_base **)(this + 16));
              operator delete(v8);
            }
            *(_DWORD *)(this + 16) = 0;
            v9 = *(std::codecvt_base **)(this + 68);
            if ( v9 )
            {
              v9->codecvt_base::do_always_noconv();
              v10 = (void *)*(void **)(this + 68);
              if ( v10 )
              {
                nullsub_3(*(void **)(this + 68));
                operator delete(v10);
              }
              *(_DWORD *)(this + 68) = 0;
              if ( *(_DWORD *)(this + 72) )
              {
                CCBStageShadow::~CCBStageShadow();
                v11 = (void *)*(void **)(this + 72);
                if ( v11 )
                {
                  nullsub_3(*(void **)(this + 72));
                  operator delete(v11);
                }
                *(_DWORD *)(this + 72) = 0;
                if ( *(_DWORD *)(this + 76) )
                {
                  CCBCamControl::DoList();
                  v12 = (void *)*(void **)(this + 76);
                  if ( v12 )
                  {
                    sub_508460(*(_DWORD *)(this + 76));
                    operator delete(v12);
                  }
                  *(_DWORD *)(this + 76) = 0;
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
  int *m_pRole; // esi
  CCBStageRole *v7; // ecx
  CCBStageCam *m_pCam; // ecx
  CCBStageCam *m_pCamControl; // ecx
  Actor *m_NGHVariance; // ecx
  Actor *m_TempStorageWPX; // ecx
  Actor *m_TempStorageNGH; // ecx

  CCBStage::~CCBStage((int)this);
  this->m_pEditor = this->m_pCBSystem->m_pEditor;
  m_pScene = (CCBStageScene *)this->m_pScene;
  if ( !m_pScene || !m_pScene->Reset() )
    return 0;
  v4 = 0;
  v5 = 0;
  m_pRole = (int *)this->m_pRole;
  do
  {
    if ( !*m_pRole )
      return 0;
    CCBStageRole::GetRotAngle(*m_pRole);
    v7 = (CCBStageRole *)*m_pRole;
    if ( this->m_pRoleState->m_Role[0].sModel[v5 + 5] )
    {
      if ( !v7->IsAtProtectPos(v4, 0, 0) )
        return 0;
    }
    else if ( !v7->IsAtProtectPos(v4, 0, 0) )
    {
      return 0;
    }
    v5 += 892;
    ++v4;
    ++m_pRole;
  }
  while ( v5 < 9812 );
  m_pCam = (CCBStageCam *)this->m_pCam;
  if ( !m_pCam || !sub_504540((CameraCtrl *)m_pCam) )
    return 0;
  m_pCamControl = (CCBStageCam *)this->m_pCamControl;
  if ( !m_pCamControl || !m_pCamControl->Update() )
    return 0;
  m_NGHVariance = (Actor *)this->m_NGHVariance;
  if ( !m_NGHVariance || !CCBStageShadow::Reset((CCBStageShadow *)m_NGHVariance) )
    return 0;
  m_TempStorageWPX = (Actor *)this->m_TempStorageWPX;
  if ( !m_TempStorageWPX || !(unsigned __int8)CCBCamControl::ResetListFlag((int)m_TempStorageWPX) )
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
    GRPinput::GetCursorPos(&this->m_WPXVariance);
    CCBStageScene::SetBattleFieldAttr(this->m_pScene);
    if ( dword_17A990C == 1 )
      this->Update();
    else
      this->Render();
    m_pRole = this->m_pRole;
    v3 = 11;
    do
    {
      if ( LOBYTE((*m_pRole)->m_bValid) )
        CCBStageRole::IsTaskFinished(*m_pRole, (int)this);
      ++m_pRole;
      --v3;
    }
    while ( v3 );
    CCBStage::ProcessTurn((CCBStage *)this->m_pCam);
    CCBStageCam::DoTask((int)this->m_pCamControl);
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
  gbVec3D::gbVec3D(&v27.Direction, 0.0, 0.0, 0.0);
  m_pDisplayChain = (CCBDisplayChain *)this->m_pDisplayChain;
  pPos = *(float *)&this->m_WPXVariance;
  y = *(float *)&m_pDisplayChain;
  m_pCam = (CCBStageCam *)this->m_pCam;
  pOut = 0;
  pOut2 = 0;
  ViewTarget = (char *)CameraCtrl::GetViewTarget((CameraCtrl *)m_pCam, pTarget, &pPos);
  gbVec3D::operator=(&v27, ViewTarget);
  gbVec3D::operator=(&v27.Direction, ViewTarget + 12);
  v5 = gbRay::IntersectPlane(&v27, &v25, &v24);
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
    gbVec3D::operator=(&this->m_pRole[(_DWORD)m_pShadow]->m_Task[35].cmd.bDestRole[10], &v21);
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
      GRPinput::GetMousePos(&g_Input, &pOut, &pOut2);
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
  CCBStageCam *v3; // eax
  int v4; // eax
  void *v5; // eax
  CCBStageCam *v6; // eax
  gbSceneGraph *pSceneGraph; // ebx
  struct gbCamera *v8; // eax
  gbMatrixStack *v9; // edi
  int v10; // eax
  char *v11; // eax
  int v12; // ecx
  long double v13; // st7
  bool v14; // cc
  CCBStageCam *v15; // eax
  struct gbCamera *v16; // eax
  int v17; // ecx
  int v18; // ecx
  void *v19; // eax
  int v21; // [esp+18h] [ebp-3Ch]
  float v22; // [esp+20h] [ebp-34h]
  CCBStageRole **v23; // [esp+38h] [ebp-1Ch]
  int v24; // [esp+38h] [ebp-1Ch]
  float v25; // [esp+3Ch] [ebp-18h]
  char *v26; // [esp+40h] [ebp-14h]
  float v27; // [esp+48h] [ebp-Ch] BYREF
  float v28; // [esp+4Ch] [ebp-8h]
  float v29; // [esp+50h] [ebp-4h]

  v2 = 0;
  *(_DWORD *)&g_pGfxManager[444] = 0;
  v3 = (CCBStageCam *)this->m_pCam;
  if ( v3 )
    v4 = (int)&v3->OrthoSize;
  else
    v4 = 0;
  v21 = v4;
  v5 = (void *)CEffectSystem::DestroyAllEffect();
  CEffectSystem::HandleViewMove((int)v5, v21);
  v6 = (CCBStageCam *)this->m_pCam;
  pSceneGraph = (gbSceneGraph *)*(gbSceneGraph **)&g_pGfxManager[448];
  if ( v6 )
    v8 = (CCBStageCam *)&v6->OrthoSize;
  else
    v8 = 0;
  pSceneGraph->Begin(v8);
  LOBYTE(pSceneGraph->?[9].m[0]) = 0;
  v9 = (gbMatrixStack *)*(gbMatrixStack **)&g_pGfxManager[216];
  CameraCtrl::SetAsCurrent((CameraCtrl *)this->m_pCam, 3);
  v9->Push();
  (*(void (**)(int, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_TempStorageWPX + 16) + 16))(
    *(_DWORD *)this->m_TempStorageWPX + 16,
    0);
  if ( !HIBYTE(this->m_pShadow[3]) )
  {
    CCBStageScene::GetBattleFieldSubdueAttr(this->m_pScene, v9);
    v23 = (CCBStageRole **)&this->m_pRole;
    do
    {
      if ( dword_17A990C == 1
        || (v10 = (int)&this->m_pRoleState->m_sCombatDialog[v2], *(_BYTE *)(v10 + 577)) && !*(_BYTE *)(v10 + 1432) )
      {
        CCBStageRole::IsDoTask(*v23, v9);
      }
      v2 += 892;
      ++v23;
    }
    while ( v2 < 9812 );
    v11 = (char *)&this->m_pRole;
    v24 = 0;
    v26 = (char *)&this->m_pRole;
    do
    {
      v12 = *(_DWORD *)v11;
      if ( *(_BYTE *)(*(_DWORD *)v11 + 280) )
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
        ((void (*)(gbGeomNode *, _DWORD))this->m_pScene->m_pPointer->next[4].next)(
          this->m_pScene->m_pPointer,
          0);
        v9->Pop();
      }
      v11 = (char *)v26 + 4;
      v14 = ++v24 < 5;
      v26 += 4;
    }
    while ( v14 );
  }
  SceneMgr::RenderUpdate((SceneMgr *)this->m_pCBSystem->m_pEffMgr);
  SceneMgr::RenderUpdate((SceneMgr *)this->m_pCBSystem->m_pATSEffMgr);
  v9->Pop();
  pSceneGraph->End();
  CCBStageShadow::Create((CCBStageShadow *)this->m_NGHVariance);
  v15 = (CCBStageCam *)this->m_pCam;
  if ( v15 )
    v16 = (CCBStageCam *)&v15->OrthoSize;
  else
    v16 = 0;
  pSceneGraph->Begin(v16);
  LOBYTE(pSceneGraph->?[9].m[0]) = 0;
  (*(void (**)(int, _DWORD))(*(_DWORD *)(*(_DWORD *)this->m_TempStorageWPX + 16) + 16))(
    *(_DWORD *)this->m_TempStorageWPX + 16,
    0);
  ((void (*)(gbVisNode *, _DWORD))this->m_pScene->m_pLights->next[4].next)(this->m_pScene->m_pLights, 0);
  SceneMgr::RenderAll((SceneMgr *)this->m_pCBSystem->m_pEffMgr);
  SceneMgr::RenderAll((SceneMgr *)this->m_pCBSystem->m_pATSEffMgr);
  C3DSpark::Render((int)this->m_pCBSystem->m_p3DSpark->m_Spark, (struct gbVec3D *)gbSceneGraph::End);
  pSceneGraph->End();
  if ( byte_17A9927 )
  {
    CCBStageScene::IsSameBattleFieldAttr(this->m_pScene);
    CCBStageScene::GetBFASubdueFM(this->m_pScene);
  }
  if ( BYTE1(this->m_pCBSystem->m_bFiveNimbus) )
  {
    if ( dword_17A990C == 1 )
    {
      v17 = (int)this->m_pScene;
      if ( !*(_BYTE *)(v17 + 963) )
        goto LABEL_31;
      v17->LoadPointer(60);
    }
    if ( dword_17A990C == 4 )
    {
      v18 = (int)this->m_pScene;
      if ( *(_BYTE *)(v18 + 963) )
        v18->LoadPointer(60);
      CCCTData::~CCCTData((int)this->m_pCamControl);
    }
  }
LABEL_31:
  sub_4DFA10((int *)this->?.y);
  v19 = (void *)CEffectSystem::DestroyAllEffect();
  CEffectSystem::Update((int)v19);
  sub_4C5C20((int *)g_pSceneMgr);
  PushMatrixStacks();
  v29 = 0.0;
  CGameData::Render((CGameData *)&g_GameData);
  sub_4DF710(this->?.y);
  if ( !g_pPalScript )
    Logger::Render((Logger *)g_Logger);
  v29 = NAN;
  return (int)PopMatrixStacks();
}

// 0x004FC6F0
// attributes: thunk
void CCBStage::Render(CCBStage *this)
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
    byte_5DB6C4->CreateObj(0, 0x30u);
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
  *((_DWORD *)v8 + 686) = CCBSystem::ProcProtect(this->m_pCBSystem);
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
  *((_DWORD *)v13 + 5) = CCBSystem::ProcProtect(this->m_pCBSystem);
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

  v2 = (char *)&this->m_pCBSystem[2632 * a2];
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
  return (int)&this->m_pCBSystem[2632 * a2 + 168];
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
  result = (char *)&this->m_pCBSystem[2632 * a2];
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
  char *v2; // eax
  int v3; // edx

  v2 = (char *)&this->m_pCBSystem[168];
  v3 = 0;
  while ( !v2[2628] || a2 != *(_DWORD *)v2 || *((_DWORD *)v2 + 1) == 4 )
  {
    ++v3;
    v2 += 2632;
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
              CCBSystem::GetStageRole((CCBSystem *)this, v2);
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

  v3 = (char *)&this->m_pCBSystem[2632 * a2 + 80 * a3];
  *((_DWORD *)v3 + 50) = 3;
  *((float *)v3 + 52) = *(float *)(*(_DWORD *)this->m_pCBSystem + 80);
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
  v3 = (char *)&this->m_pCBSystem[2632 * a2];
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
  char *i; // edx
  int v4; // eax
  int v5; // esi
  char *v6; // eax
  int v7; // ecx

  v2 = 0;
  for ( i = &this->m_pCBSystem[2796]; ; i += 2632 )
  {
    if ( *i )
    {
      if ( *((_DWORD *)i - 656) != 4 && *((_DWORD *)i - 657) == 11 )
      {
        v4 = *((_DWORD *)i - 9);
        if ( v4 >= 5 && v4 < 11 )
          break;
      }
    }
LABEL_18:
    if ( ++v2 >= 256 )
      return 0;
  }
  v5 = 0;
  v6 = (char *)i - 2612;
  while ( 1 )
  {
    if ( *(int (**)(_DWORD *, int))v6 == CCBStage::HandleKeyCtrl
      && (!*(_DWORD *)v6 || !*((_DWORD *)v6 + 1) && !*((_DWORD *)v6 + 2) && !*((_DWORD *)v6 + 3)) )
    {
      if ( *((_DWORD *)v6 + 4) == 4 )
        goto LABEL_18;
      v7 = *((_DWORD *)i - 8);
      if ( v7 == a2 || v7 == -1 && i[a2 - 15] )
        return 1;
    }
    ++v5;
    v6 += 80;
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

  CCBStageRole::GetState(this->m_pRole[a2]);
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
_BYTE * CCBStage::IsTaskValidButNotFinish@<eax>(_BYTE *result@<eax>, int a2@<ecx>, int a3)
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
  char *v3; // ecx
  int v4; // edx

  result = 0;
  v3 = (char *)&this->m_pCBSystem[2760];
  v4 = 256;
  do
  {
    if ( v3[36] && *(_DWORD *)v3 == a2 && *((_DWORD *)v3 - 648) != 29 )
      ++result;
    v3 += 2632;
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
      || GRPinput::SetJoystickAbs(&g_Input) )
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
  int v3; // ecx
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

  v3 = 329 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = (char *)&this->m_pCBSystem[80 * *(_DWORD *)&this->m_pCBSystem[164]];
  v5 = *(float *)&v4[8 * v3 + 216] * 0.25;
  v6 = (int)&v4[8 * v3 + 184];
  v11 = v5;
  v13 = v5 * 3.0;
  if ( !v4[8 * v3 + 225] )
  {
    *(_DWORD *)&v4[8 * v3 + 248] = 0;
    v4[8 * v3 + 225] = 1;
  }
  CCBStage::EndRound(*(CCBStage **)&this->m_pCBSystem[68]);
  v7 = *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *(float *)(v6 + 24);
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
  if ( *(_BYTE *)(v6 + 43) == 1
    || *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *(float *)(v6 + 24) >= *(float *)(v6 + 32) )
  {
    *(_DWORD *)(v6 + 16) = 4;
  }
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
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  double v6; // st7
  unsigned int v7; // eax
  float v9; // [esp+20h] [ebp-4h]
  float v10; // [esp+20h] [ebp-4h]

  v3 = 329 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v5 = (char *)&this->m_pCBSystem[8 * v3 + 184 + v4];
  v9 = *(float *)&this->m_pCBSystem[8 * v3 + 216 + v4];
  if ( !this->m_pCBSystem[8 * v3 + 225 + v4] )
  {
    *(_DWORD *)&this->m_pCBSystem[8 * v3 + 248 + v4] = 0;
    this->m_pCBSystem[8 * v3 + 225 + v4] = 1;
  }
  CCBStage::EndRound(*(CCBStage **)&this->m_pCBSystem[68]);
  v6 = *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v5 + 6);
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
  if ( v5[43] == 1 )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FD1A0
int CCBStage::IsSubTaskValid(int a2)
{
  int v3; // ecx
  int v4; // edx
  char *v5; // esi
  double v6; // st7
  unsigned int v7; // ecx
  float v9; // [esp+20h] [ebp-4h]
  float v10; // [esp+20h] [ebp-4h]

  v3 = 329 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v5 = (char *)&this->m_pCBSystem[8 * v3 + 184 + v4];
  v9 = *(float *)&this->m_pCBSystem[8 * v3 + 216 + v4];
  if ( !this->m_pCBSystem[8 * v3 + 225 + v4] )
  {
    *(_DWORD *)&this->m_pCBSystem[8 * v3 + 248 + v4] = 255;
    this->m_pCBSystem[8 * v3 + 225 + v4] = 1;
  }
  CCBStage::EndRound(*(CCBStage **)&this->m_pCBSystem[68]);
  v6 = *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v5 + 6);
  if ( v6 >= v9 )
  {
    *((_DWORD *)v5 + 16) = 0;
    *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    v10 = (1.0 - v6 / v9) * 255.0;
    v7 = (int)v10;
    *((_DWORD *)v5 + 16) = v7;
    *((_DWORD *)v5 + 16) = v7 <= 0xFF ? v7 : 0;
  }
  if ( v5[43] == 1 )
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
    if ( *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    m_pUI = (CCBUI *)this->m_pCBSystem->m_pUI;
    if ( LOBYTE(this->m_pRoleState->m_bWeSneakAttackEnemy) )
    {
      v8 = (char *)PalScript::SetAppName((PalScript *)(&g_PAL3Data + 312), aWesneakattacke);
      UIWnd::SetEnable(m_pUI->m_pRoleStateImmunity[10], v8, 1);
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10];
    }
    else
    {
      v10 = (char *)PalScript::SetAppName((PalScript *)(&g_PAL3Data + 312), aEnemysneakatta);
      UIWnd::SetEnable(m_pUI->m_pWinPanel, v10, 1);
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pWinPanel;
    }
    (*(void (**)(UIStatic *, int))m_pWinPanel->m_fontcolor.ColorQuadFmt)(m_pWinPanel, 1);
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || this->m_pCBSystem->m_fTimeFund - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
  {
    v11 = (CCBUI *)this->m_pCBSystem->m_pUI;
    if ( LOBYTE(this->m_pRoleState->m_bWeSneakAttackEnemy) )
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
int CCBStage::HasNormalAttackRole(int _this, int a2)
{
  int v3; // ebp
  int v4; // ecx
  int v5; // ebx
  int v6; // eax
  int v8; // edi
  signed int i; // edi
  int v10; // edi
  int v11; // ebx
  _BYTE *v12; // ecx
  int j; // edi
  int v14; // ecx
  int v15; // edx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  char v19; // dl
  int k; // eax
  int v21; // ebp
  int v22; // eax
  int v23; // ecx
  int v24; // eax
  int v25; // ecx
  unsigned int *v26; // [esp+10h] [ebp-10h]
  _DWORD *v27; // [esp+14h] [ebp-Ch]
  _DWORD *v28; // [esp+14h] [ebp-Ch]
  int v29; // [esp+18h] [ebp-8h]
  int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+1Ch] [ebp-4h]

  if ( (byte_17AAA2C & 1) == 0 )
  {
    dword_17AAA20 = 0;
    byte_17AAA2C |= 1u;
    dword_17AAA24 = 0;
    dword_17AAA28 = 0;
    atexit(nullsub_20);
  }
  v3 = 2632 * *(_DWORD *)(this + 160);
  v31 = *(_DWORD *)(this + v3 + 2760);
  v4 = v3 + 80 * *(_DWORD *)(this + 164);
  v5 = v4 + this + 184;
  v29 = v5;
  if ( !*(_BYTE *)(v4 + this + 225) )
  {
    *(_DWORD *)(this + 92) = 0;
    *(_DWORD *)(this + 96) = 0;
    *(_WORD *)(this + 100) = 0;
    *(_BYTE *)(this + 102) = 0;
    v6 = sub_503680(*(_DWORD *)(v4 + this + 228), this + v3 + 2752);
    dword_17AAD3C = v6;
    if ( v6 == -1 )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 36) = -1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    sub_503AE0(v6, *(_DWORD *)(v5 + 44), *(_DWORD *)(this + v3 + 2756));
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( (*(_BYTE *)(v5 + 44) & 1) != 0 )
  {
    v8 = 0;
    v26 = (unsigned int *)(this + v3 + 2752);
    v27 = (_DWORD *)(this + 24);
    do
    {
      if ( CCBRoleState::CancelVariance(*(char **)(this + 4), v26, v8)
        && !CCBStageRole::IsActive(*(_BYTE **)(this + 4), v8)
        && (unsigned __int8)sub_50A4B0(*v27) == 1 )
      {
        dword_17AAD3C = v8;
        sub_503AE0(v8, *(_DWORD *)(v5 + 44), *(_DWORD *)(this + v3 + 2756));
      }
      ++v8;
      ++v27;
    }
    while ( v8 < 11 );
    sub_503AE0(dword_17AAD3C, *(_DWORD *)(v5 + 44), *(_DWORD *)(this + v3 + 2756));
    for ( i = 0; i < 11; ++i )
    {
      if ( *(_BYTE *)(this + i + 92) && !CCBRoleState::CancelVariance(*(char **)(this + 4), v26, i) )
        *(_BYTE *)(this + i + 92) = 0;
    }
    if ( (unsigned int)dword_17AAD3C <= 0xA && CCBRoleState::GetRoleAttr(*(_DWORD **)(this + 4), v31) < 4 )
      dword_17AAD3C->SetBladeTime();
  }
  else
  {
    v10 = 0;
    v11 = 0;
    v28 = (_DWORD *)(this + 24);
    do
    {
      v12 = (_BYTE *)*(_BYTE **)(this + 4);
      if ( v12[v11 + 577] && v12->IsActive(v10) == 1 && (unsigned __int8)sub_50A4B0(*v28) == 1 )
      {
        dword_17AAD3C = v10;
        sub_503AE0(v10, *(_DWORD *)(v29 + 44), *(_DWORD *)(this + v3 + 2756));
      }
      v11 += 892;
      ++v10;
      ++v28;
    }
    while ( v11 < 9812 );
    v26 = (unsigned int *)(this + v3 + 2752);
    if ( !sub_4F6CD0(v26) )
    {
      for ( j = 0; j < 11; ++j )
      {
        if ( *(_BYTE *)(this + j + 92) && !CCBRoleState::IsRoleAlive(*(_BYTE **)(this + 4), j) )
          *(_BYTE *)(this + j + 92) = 0;
      }
    }
    v5 = v29;
  }
  v14 = 0;
  v15 = 0;
  v30 = 0;
  v16 = this + 24;
  do
  {
    if ( *(_BYTE *)(v14 + *(_DWORD *)(this + 4) + 577) )
    {
      if ( *(_BYTE *)(v15 + this + 92) )
      {
        ++v30;
        *(_BYTE *)(*(_DWORD *)v16 + 280) = 1;
        *(_BYTE *)(*(_DWORD *)v16 + 274) = 1;
      }
      else
      {
        *(_BYTE *)(*(_DWORD *)v16 + 280) = 0;
        *(_BYTE *)(*(_DWORD *)v16 + 274) = 0;
      }
    }
    v14 += 892;
    ++v15;
    v16 += 4;
  }
  while ( v14 < 9812 );
  if ( v30 <= 0 )
    *(_BYTE *)(v5 + 41) = 0;
  if ( MEMORY[0xBFC5F4] == 1 && ((v17 = MEMORY[0xBFC5E8][0] & 0xF, v17 == 1) || v17 == 2) )
  {
    if ( (*(_BYTE *)(v5 + 44) & 0x10) != 0 )
    {
      *(_BYTE *)(this + v3 + 2769) = 0;
      *(_BYTE *)(this + v3 + 2768) = 0;
      *(_DWORD *)(this + v3 + 2764) = dword_17AAD3C;
      if ( dword_17AAD3C == -1 )
        return 0;
    }
    else
    {
      *(_BYTE *)(this + v3 + 2768) = 0;
      *(_BYTE *)(this + v3 + 2769) = 1;
      v18 = this + v3 + 2781;
      *(_DWORD *)v18 = *(_DWORD *)(this + 92);
      *(_DWORD *)(v18 + 4) = *(_DWORD *)(this + 96);
      *(_WORD *)(v18 + 8) = *(_WORD *)(this + 100);
      *(_BYTE *)(v18 + 10) = *(_BYTE *)(this + 102);
      v19 = 0;
      for ( k = 0; k < 11; ++k )
      {
        if ( *(_BYTE *)(this + 92 + k) )
          v19 = 1;
      }
      if ( !v19 )
        return 0;
    }
    v21 = v31;
    *(_DWORD *)(v5 + 36) = dword_17AAD3C;
    *(_DWORD *)(v5 + 16) = 4;
    v22 = 0;
    *(_BYTE *)(*(_DWORD *)(this + 4 * v31 + 24) + 274) = 0;
    v23 = this + 24;
    do
    {
      if ( *(_BYTE *)(v22 + *(_DWORD *)(this + 4) + 577) )
      {
        *(_BYTE *)(*(_DWORD *)v23 + 280) = 0;
        *(_BYTE *)(*(_DWORD *)v23 + 274) = 0;
      }
      v22 += 892;
      v23 += 4;
    }
    while ( v22 < 9812 );
  }
  else
  {
    v21 = v31;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || MEMORY[0xBFC604] == 1 && (MEMORY[0xBFC5F8] & 0xF) == 1
    || MEMORY[0xBFC704] == 1
    || *v26 == 262 && CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), v21, 16)
    || *v26 == 261 && CCBRoleState::GetRoleField(*(_BYTE **)(this + 4), v21, 15) )
  {
    *(_DWORD *)(v5 + 36) = -1;
    *(_DWORD *)(v5 + 16) = 4;
    v24 = 0;
    v25 = this + 24;
    do
    {
      if ( *(_BYTE *)(v24 + *(_DWORD *)(this + 4) + 577) )
      {
        *(_BYTE *)(*(_DWORD *)v25 + 280) = 0;
        *(_BYTE *)(*(_DWORD *)v25 + 274) = 0;
      }
      v24 += 892;
      v25 += 4;
    }
    while ( v24 < 9812 );
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
    if ( *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
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
        ItemNum = (const char *)PAL_GDB::GDB_GetItemNum(&g_GDB, v11);
        if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
          UIWnd::SetEnable(this->m_pCBSystem->m_pUI->m_pWinPanel, ItemNum, 1);
        else
          UIWnd::SetEnable(this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10], ItemNum, 1);
      }
      else
      {
        RoleNum = PAL_GDB::GDB_GetRoleNum(&g_GDB, v11);
        if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
          UIWnd::SetEnable(this->m_pCBSystem->m_pUI->m_pWinPanel, (const char *)(RoleNum + 28), 1);
        else
          UIWnd::SetEnable(this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10], (const char *)(RoleNum + 28), 1);
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
    || *((_BYTE *)CEffectSystem::DestroyAllEffect() + 5) )
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
    SkillNum = PAL_GDB::GDB_GetSkillNum(&g_GDB, *(__int32 *)((char *)&this->m_Task[0].eTask + v4));
    if ( *(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v3) > 4u )
    {
      UIWnd::SetEnable(this->m_pCBSystem->m_pUI->m_pWinPanel, (const char *)(SkillNum + 4), 1);
      m_pWinPanel = (UIStatic *)this->m_pCBSystem->m_pUI->m_pWinPanel;
    }
    else
    {
      UIWnd::SetEnable(this->m_pCBSystem->m_pUI->m_pRoleStateImmunity[10], (const char *)(SkillNum + 4), 1);
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
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  char *v6; // esi
  char *v7; // ecx
  int *v8; // eax
  int v9; // ecx
  double v10; // st7
  double v11; // st7
  double v12; // st7
  int v13; // eax
  char v14; // dl
  int v16; // [esp+8h] [ebp-20h] BYREF
  int v17; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  int v19; // [esp+14h] [ebp-14h]
  int v20; // [esp+18h] [ebp-10h]
  int v21; // [esp+1Ch] [ebp-Ch]
  float v22; // [esp+20h] [ebp-8h] BYREF
  float v23; // [esp+24h] [ebp-4h] BYREF

  v22 = 0.0;
  v23 = 0.0;
  v16 = 0;
  v3 = *(_DWORD *)&this->m_pCBSystem[160];
  v17 = 0;
  v18 = 0;
  v4 = 2632 * v3;
  v5 = v4 + 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v6 = (char *)&this->m_pCBSystem[v5 + 184];
  if ( !this->m_pCBSystem[v5 + 225] )
  {
    v7 = (char *)&this->m_pCBSystem[v4 + 2760];
    *(float *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 104] = *(float *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 104] + 10.0;
    v8 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 24] + 6584);
    v16 = *v8;
    v17 = v8[1];
    v18 = v8[2];
    *((_DWORD *)v6 + 16) = v16;
    *((_DWORD *)v6 + 17) = v18;
    v20 = *(int *)&this->m_pCBSystem[4 * *(_DWORD *)v7 + 104];
    v21 = (int)*(float *)&v20;
    *((float *)v6 + 18) = *(float *)&v21;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *((_DWORD *)v6 + 19) = (g_RandSeed >> 16) & 0x1F;
    v6[41] = 1;
  }
  v16 = *((_DWORD *)v6 + 16);
  v18 = *((_DWORD *)v6 + 17);
  v9 = *(_DWORD *)&this->m_pCBSystem[12];
  v17 = 1112014848;
  gbCamera::PointWorldToScr((gbCamera *)(v9 + 4), (struct gbVec3D *)&v16, &v22, &v23);
  sprintf(byte_17AA920, "%d", *((_DWORD *)v6 + 11));
  v10 = (*(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6)) / *((float *)v6 + 8);
  if ( v10 > 1.0 )
    v10 = 1.0;
  *(float *)&v21 = (1.0 - v10) * 255.0;
  v20 = (int)*(float *)&v21;
  *(float *)&v21 = (*(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6)) * 30.0;
  v19 = (int)*(float *)&v21;
  v11 = (double)MEMORY[0xBFD6D4];
  v19 = *((_DWORD *)v6 + 18) - (__int64)((1.0 - v23) * v11 * -0.5) - v19;
  v23 = 1.0 - ((double)v19 + (double)v19) / v11;
  v12 = (double)MEMORY[0xBFD6D0];
  v19 = *((_DWORD *)v6 + 19) - (__int64)((v22 + 1.0) * v12 * -0.5) - 16;
  v22 = ((double)v19 + (double)v19) / v12 - 1.0;
  v13 = *((_DWORD *)v6 + 13);
  if ( v13 )
  {
    v14 = v6[52];
    BYTE1(v21) = BYTE1(*((_DWORD *)v6 + 13));
    BYTE2(v21) = BYTE2(v13);
    LOBYTE(v21) = v14;
  }
  else
  {
    *(_WORD *)((char *)&v21 + 1) = 12850;
    LOBYTE(v21) = -1;
  }
  HIBYTE(v21) = v20;
  CCBStage::InitRound(*(CCBStage **)&this->m_pCBSystem[68]);
  if ( *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6) > *((float *)v6 + 8) )
    *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FDD90
int CCBStage::SelectRole(int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  char *v6; // esi
  int v7; // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  float v11; // edx
  int v13; // [esp+8h] [ebp-20h] BYREF
  float v14; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  int v17; // [esp+18h] [ebp-10h]
  int v18; // [esp+1Ch] [ebp-Ch]
  float v19; // [esp+20h] [ebp-8h] BYREF
  float v20; // [esp+24h] [ebp-4h] BYREF

  v19 = 0.0;
  v20 = 0.0;
  v13 = 0;
  v3 = *(_DWORD *)&this->m_pCBSystem[160];
  v14 = 0.0;
  v15 = 0;
  v4 = 2632 * v3;
  v5 = v4 + 80 * *(_DWORD *)&this->m_pCBSystem[164];
  v6 = (char *)&this->m_pCBSystem[v5 + 184];
  if ( !this->m_pCBSystem[v5 + 225] )
  {
    v7 = *(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)&this->m_pCBSystem[v4 + 2760] + 24] + 6596;
    v13 = *(_DWORD *)v7;
    v14 = *(float *)(v7 + 4);
    v15 = *(_DWORD *)(v7 + 8);
    v14 = v14 + 80.0;
    *(_DWORD *)&this->m_pCBSystem[v5 + 248] = v13;
    *(float *)&this->m_pCBSystem[v5 + 252] = v14;
    *(_DWORD *)&this->m_pCBSystem[v5 + 256] = v15;
    ++g_nRandCallCount;
    g_RandSeed = 214013 * g_RandSeed + 2531011;
    *(_DWORD *)&this->m_pCBSystem[v5 + 260] = (g_RandSeed >> 16) & 0x1F;
    this->m_pCBSystem[v5 + 225] = 1;
  }
  v13 = *(_DWORD *)&this->m_pCBSystem[v5 + 248];
  v14 = *(float *)&this->m_pCBSystem[v5 + 252];
  v15 = *(_DWORD *)&this->m_pCBSystem[v5 + 256];
  gbCamera::PointWorldToScr((gbCamera *)(*(_DWORD *)&this->m_pCBSystem[12] + 4), (struct gbVec3D *)&v13, &v19, &v20);
  v8 = (*(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6)) / *((float *)v6 + 8);
  *(float *)&v18 = v8;
  if ( v8 > 1.0 )
    *(float *)&v18 = 1.0;
  *(float *)&v17 = (1.0 - *(float *)&v18) * 255.0;
  v16 = (int)*(float *)&v17;
  *(float *)&v17 = *(float *)&v18 * 32.0;
  v18 = (int)*(float *)&v17;
  v9 = (double)MEMORY[0xBFD6D4];
  v17 = 16 - (__int64)((1.0 - v20) * v9 * -0.5) - v18;
  v20 = 1.0 - ((double)v17 + (double)v17) / v9;
  v10 = (double)MEMORY[0xBFD6D0];
  LODWORD(v11) = *((_DWORD *)v6 + 19) - (__int64)((v19 + 1.0) * v10 * -0.5) - 16;
  *(_WORD *)((char *)&v18 + 1) = 13055;
  *(float *)&v17 = v11;
  LOBYTE(v18) = -1;
  HIBYTE(v18) = v16;
  v19 = ((double)v17 + (double)v17) / v10 - 1.0;
  CCBStage::InitRound(*(CCBStage **)&this->m_pCBSystem[68]);
  if ( *(float *)(*(_DWORD *)this->m_pCBSystem + 80) - *((float *)v6 + 6) > *((float *)v6 + 8) )
    *((_DWORD *)v6 + 4) = 4;
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
    v14 = (char *)PalScript::SetAppName((PalScript *)(&g_PAL3Data + 312), aWitch);
    sprintf(Buffer, "%s -%d", v14, v16);
  }
  else if ( *(_DWORD *)(v6 + 44) == 2 )
  {
    v15 = (char *)PalScript::SetAppName((PalScript *)(&g_PAL3Data + 312), aMoney);
    sprintf(Buffer, "%d%s", *(_DWORD *)(v6 + 52), v15);
  }
  else
  {
    strcpy(Buffer, (const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    v2 = v19;
  }
  CCBStage::InitRound((CCBStage *)v2->m_TempStorageNGH);
  if ( v2->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24) > *(float *)(v6 + 32) )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FE290
int CCBStage::ProcShowFiveLineup(CCBStage **this, int a2)
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
  gbCamera::PointWorldToScr((gbCamera *)&(*((_DWORD *)this + 3))->m_pRoleState, &v15, &v19, &v20);
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
  UIWnd::SetEnable((UIWnd *)(*this)->m_pRoleState->m_Role[0].bMagicMastered[1][0], (const char *)*((_DWORD *)this + 1), 0);
  v14 = id;
  CCBStage::ProcShowEnemyFiveLineup(*this);
  v14->UpdateAnim();
  UIWnd::GetChild((UIWnd *)(*this)->m_pRoleState->m_Role[0].bMagicMastered[1][0], (int)&id);
  UIWnd::ScreenToClient((UIWnd *)(*this)->m_pRoleState->m_Role[0].bMagicMastered[1][0], LODWORD(v11) - 168, v18 - 128);
  UIWnd::SetShow((UIWnd *)(*this)->m_pRoleState->m_Role[0].bMagicMastered[1][0], 0);
  if ( *((_BYTE *)v6 + 43) == 1 || *(float *)&(*this)->m_WPXVariance - v6[6] > v6[8] )
  {
    v12 = (void (***)(_DWORD, _DWORD))(*this)->m_pRoleState->m_Role[0].bMagicMastered[1][0];
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
        CCBStageRole::GetCurrentTaskIndex((int)v7);
      CCBStageRole::DelAllTask(
        (int)this->m_pRole[*v6],
        *(&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole),
        1);
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
    CCBStageRole::GetCurrentTask(
      (int)this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v2)],
      *(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v2));
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  return 0;
}

// 0x004FE660
int CCBStage::ProcShowSneakAttackState(int _this, int _74)
{
  int v3; // eax
  int v4; // ebp
  int v5; // edi
  unsigned int v7; // eax
  _DWORD *v8; // ecx
  CCBRoleState *v9; // ecx
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  double v13; // st7
  int v14; // eax
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
  int v27; // [esp+14h] [ebp-5Ch]
  int a4; // [esp+18h] [ebp-58h] BYREF
  float a3; // [esp+1Ch] [ebp-54h] BYREF
  float a2[3]; // [esp+20h] [ebp-50h] BYREF
  gbVec3D a7; // [esp+2Ch] [ebp-44h] BYREF
  gbVec3D v32; // [esp+38h] [ebp-38h] BYREF
  _DWORD v33[11]; // [esp+44h] [ebp-2Ch] BYREF

  memset(a2, 0, sizeof(a2));
  v3 = 2632 * *(_DWORD *)(this + 160);
  v4 = v3 + this + 2752;
  v5 = v3 + 80 * *(_DWORD *)(this + 164) + this + 184;
  v27 = v5;
  if ( !CCBStageRole::IsReady(
          *(CCBStageRole **)(this + 4 * *(_DWORD *)(v3 + this + 2760) + 24),
          *(_DWORD *)(v3 + this + 2744)) )
  {
    *(_DWORD *)(v5 + 16) = 4;
    return 0;
  }
  if ( !*(_BYTE *)(v5 + 41) && CCBStageRole::ForceDelTaskByPFN(*(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24)) )
  {
    CCBStage::ResetAll((CCBStage *)this);
    v7 = *(_DWORD *)(v4 + 8);
    if ( v7 <= 4 && *(_BYTE *)(*(&g_SceneMgr.m_npc[0].m_npcinfo.speed + 352 * v7) + 613) == 5
      || *(_DWORD *)CCBRoleState::InitUI(*(CCBRoleState **)(this + 4), *(_DWORD *)(v4 + 8)) == 7366 )
    {
      a4 = *(_DWORD *)(v4 + 12);
      if ( (unsigned int)a4 <= 0xA )
      {
        v8 = sub_50E160;
        a2[0] = (float)a4;
LABEL_25:
        CCBStageRole::GetProperCurAction(
          *(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24),
          v8,
          0,
          0,
          0,
          *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
          (int *)a2,
          (const void *)v4,
          (_DWORD *)1);
        goto LABEL_26;
      }
      v9 = (CCBRoleState *)*(CCBRoleState **)(this + 4);
      a3 = NAN;
      a4 = -1;
      if ( (unsigned int)v9->WriteBackRoleData(v4, &a3, &a4) <= 0xA )
      {
        v8 = sub_50E160;
        a2[0] = (float)*(int *)(v4 + 12);
        goto LABEL_25;
      }
    }
    else
    {
      v10 = *(_DWORD *)(v4 + 8);
      if ( v10 > 4 )
      {
        if ( *(_DWORD *)CCBRoleState::InitUI(*(CCBRoleState **)(this + 4), *(_DWORD *)(v4 + 8)) == 720 )
        {
          v8 = (_DWORD *)CCBStageRole::ProcMagic;
        }
        else if ( *(_DWORD *)CCBRoleState::InitUI(*(CCBRoleState **)(this + 4), *(_DWORD *)(v4 + 8)) == 738
               || (inited = (_DWORD *)CCBRoleState::InitUI(*(CCBRoleState **)(this + 4), *(_DWORD *)(v4 + 8)),
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
            v13 = CCBStageRole::AddTask((CCBStageRole *)*(_DWORD *)(this + 36), a2);
            v14 = *(_DWORD *)(this + 160);
            a3 = v13;
            CCBStageRole::GetProperCurAction(
              *(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24),
              sub_50E360,
              0,
              0,
              0,
              *(_DWORD **)(this + 2632 * v14 + 2744),
              (int *)a2,
              (const void *)v4,
              (_DWORD *)1);
            CCBStageRole::GetProperCurAction(
              *(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24),
              CCBStage::CheckAllDone,
              0,
              0,
              0,
              *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
              (int *)a2,
              (const void *)v4,
              (_DWORD *)1);
            v8 = (_DWORD *)CCBStage::ProcessCommand;
            a2[0] = a3;
            goto LABEL_25;
          }
        }
        else
        {
          CCBStageRole::GetProperCurAction(
            *(CCBStageRole **)(this + 32),
            CCBStageRole::ProcMagic,
            0,
            0,
            0,
            *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
            (int *)a2,
            (const void *)v4,
            (_DWORD *)1);
        }
        v8 = (_DWORD *)CCBStageRole::ProcTurnToRole;
        goto LABEL_25;
      }
      CCBStageRole::GetProperCurAction(
        *(CCBStageRole **)(this + 28),
        CCBStageRole::ProcUseRecoverItem,
        0,
        0,
        0,
        *(_DWORD **)(this + 2632 * *(_DWORD *)(this + 160) + 2744),
        (int *)a2,
        (const void *)v4,
        (_DWORD *)1);
    }
LABEL_26:
    *(_DWORD *)(v5 + 64) = 1;
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( CCBStageRole::IsActive(*(CCBStageRole **)(this + 4), *(_DWORD *)(v4 + 8)) )
  {
    v26 = 1;
    if ( *(_BYTE *)(v4 + 17) )
    {
      for ( i = 0; i < 11; ++i )
      {
        if ( *(_BYTE *)(i + v4 + 29) && CCBRoleState::IsRoleAlive(*(CCBRoleState **)(this + 4), i) )
          v26 = 0;
      }
      if ( v26 )
        goto LABEL_35;
    }
    else if ( !CCBRoleState::IsRoleAlive(*(CCBRoleState **)(this + 4), *(_DWORD *)(v4 + 12)) )
    {
LABEL_35:
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
  }
  if ( *(_DWORD *)(v5 + 64) == 1 )
  {
    v17 = *(_DWORD *)(v4 + 8);
    if ( v17 >= 5 && v17 < 11 )
    {
      v18 = (CCBRoleState *)*(CCBRoleState **)(this + 4);
      if ( v18->m_Role[0].sModel[5] )
      {
        if ( *(int *)(v18->InitUI(0) + 84) >= 0
          && *(int *)(CCBRoleState::InitUI(*(CCBRoleState **)(this + 4), 0) + 84) < 11 )
        {
          v19 = CCBRoleState::InitUI(*(CCBRoleState **)(this + 4), 0);
          if ( sub_4F06C0(v4, *(_DWORD *)(v19 + 84)) )
          {
            v20 = *(_DWORD *)(CCBRoleState::InitUI(*(CCBRoleState **)(this + 4), 0) + 84);
            v21 = (float *)(*(_DWORD *)(this + 4 * v20 + 24) + 6584);
            v22 = (float *)(*(_DWORD *)(this + 4 * *(_DWORD *)(v4 + 8) + 24) + 6584);
            a7.x = *v21 - *v22;
            a7.y = v21[1] - v22[1];
            v23 = v21[2] - v22[2];
            v32 = a7;
            a7.z = v23;
            v24 = gbVec3D::Length(&v32);
            if ( v24 < 120.0 && v24 > 50.0 )
            {
              if ( sub_4EED60(*(_DWORD *)(this + 4), v20) )
              {
                memset(v33, 0, sizeof(v33));
                v33[2] = 0;
                v33[1] = 0;
                v33[3] = v20;
                RoleIndex = CCBStage::GetRoleIndex((CCBStage *)this, 18, v33, 1);
                if ( RoleIndex != -1 )
                {
                  a7.x = *(float *)(v4 + 8);
                  LODWORD(a7.y) = v33[2];
                  LODWORD(a7.z) = v33[3];
                  CCBStage::GetRoleName(
                    (CCBStage *)this,
                    RoleIndex,
                    (int)CCBStage::ProcFiveLienupFadeIn,
                    0,
                    0,
                    0,
                    &a7,
                    -1082130432,
                    0);
                  CCBStage::GetRoleName((CCBStage *)this, RoleIndex, (int)sub_500840, 0, 0, 0, &a7, -1082130432, 0);
                  CCBStage::GetRoleName((CCBStage *)this, RoleIndex, (int)sub_5009C0, 0, 0, 0, &a7, -1082130432, 0);
                  CCBStage::GetRoleName((CCBStage *)this, RoleIndex, (int)sub_500AD0, 0, 0, 0, &a7, -1082130432, 0);
                  CCBStage::GetRoleName(
                    (CCBStage *)this,
                    RoleIndex,
                    (int)CCBStage::ProcFiveLienupFadeOut,
                    0,
                    0,
                    0,
                    &a7,
                    -1082130432,
                    0);
                  *(_DWORD *)(v27 + 64) = 0;
                  CCBSystem::GetStageRoleByIdx((CCBSystem *)this, RoleIndex);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( CCBStageRole::ForceDelTaskByPFN(*(CCBStageRole **)(this + 4 * *(_DWORD *)(v4 + 8) + 24))
    || *(_BYTE *)(v27 + 43) == 1 )
  {
    *(_DWORD *)(v27 + 16) = 4;
  }
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
  if ( CCBStageRole::IsReady(this->m_pRole[*v4], *(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v3)) )
  {
    if ( !*((_BYTE *)v5 + 41) && CCBStageRole::ForceDelTaskByPFN(this->m_pRole[*v4]) )
    {
      *(float *)&dword_17AA910 = (float)*v4;
      *(float *)&dword_17AA914 = (float)*(int *)((char *)&this->m_Task[0].SubTask[17].param.f3 + v3);
      CCBStageRole::GetProperCurAction(
        this->m_pRole[*v4],
        sub_50E550,
        0,
        0,
        0,
        *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole),
        &dword_17AA910,
        &this->m_Task[0].SubTask[17].param.f2 + 658 * this->m_bHideSceneAndRole,
        (_DWORD *)1);
      *((_BYTE *)v5 + 41) = 1;
    }
    if ( CCBStageRole::ForceDelTaskByPFN(this->m_pRole[*v4]) )
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
    CCBStageRole::ProcTransportRun(
      this->m_pRole[*(__int32 *)((char *)&this->m_Task[0].SubTask[17].param.dw3 + v2)],
      (int)sub_50EB00,
      0,
      0,
      0,
      0,
      0,
      3);
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  if ( v4[43] == 1 )
    *((_DWORD *)v4 + 4) = 4;
  return 0;
}

// 0x004FEFB0
int CCBStage::ProcShowName(int _this, int a2)
{
  int v3; // eax
  int *v4; // edi
  int v5; // ebx
  int v7; // eax
  int v8; // ecx
  int (__stdcall *v9)(int); // edx
  double v10; // st7
  int v11; // eax
  float v12[3]; // [esp+14h] [ebp-Ch] BYREF

  v3 = 2632 * *(_DWORD *)(this + 160);
  v4 = (int *)(v3 + this + 2760);
  v5 = v3 + 80 * *(_DWORD *)(this + 164) + this + 184;
  if ( !(unsigned __int8)CCBStageRole::IsReady(*(_DWORD *)(v3 + this + 2744)) )
  {
    *(_DWORD *)(v5 + 16) = 4;
    return 0;
  }
  if ( !*(_BYTE *)(v5 + 41) && (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(_DWORD *)(this + 4 * *v4 + 24)) == 1 )
  {
    v7 = *v4;
    if ( *v4 >= 0 && v7 < 5 )
    {
      switch ( v7 )
      {
        case 1:
          v8 = *(_DWORD *)(this + 28);
          v9 = (int (__stdcall *)(int))CCBStageRole::ProcUseRecoverItem;
          break;
        case 2:
          v8 = *(_DWORD *)(this + 32);
          v9 = CCBStageRole::ProcMagic;
          break;
        case 3:
          v8 = *(_DWORD *)(this + 36);
          v9 = (int (__stdcall *)(int))CCBStage::CheckAllDone;
          break;
        default:
          v8 = *(_DWORD *)(this + 4 * v7 + 24);
          v9 = CCBStageRole::ProcTurnToRole;
          break;
      }
      goto LABEL_22;
    }
    if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *v4) == 720 )
    {
      v9 = CCBStageRole::ProcMagic;
    }
    else
    {
      if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *v4) != 738
        && *(_DWORD *)CCBRoleState::InitUI(*(void **)(this + 4), *v4) != 739 )
      {
        v9 = CCBStageRole::ProcTurnToRole;
        v8 = *(_DWORD *)(this + 4 * *v4 + 24);
LABEL_22:
        v9->GetProperCurAction(0, 0, 0, *(_DWORD *)(this + 2632 * *(_DWORD *)(this + 160) + 2744), v8 + 6596, 0, 1);
        v10 = *(float *)(*(_DWORD *)(this + 4 * *v4 + 24) + 6636);
        v12[1] = 0.0;
        v11 = *(_DWORD *)(this + 160);
        v12[0] = v10;
        v12[2] = 0.0;
        CCBStageRole::GetProperCurAction(
          CCBStage::ProcessCommand,
          0,
          0,
          0,
          *(_DWORD *)(this + 2632 * v11 + 2744),
          v12,
          0,
          1);
        *(_BYTE *)(v5 + 41) = 1;
        goto LABEL_23;
      }
      v9 = CCBStageRole::ProcBlock;
    }
    v8 = *(_DWORD *)(this + 4 * *v4 + 24);
    goto LABEL_22;
  }
LABEL_23:
  if ( (unsigned __int8)CCBStageRole::ForceDelTaskByPFN(*(_DWORD *)(this + 4 * *v4 + 24)) == 1 )
    *(_DWORD *)(v5 + 16) = 4;
  if ( *(_BYTE *)(v5 + 43) == 1 && !*(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), *v4) + 36) )
    *(_DWORD *)(v5 + 16) = 4;
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
  if ( !CCBStageRole::IsReady(this->m_pRole[*v4], *(int *)((char *)&this->m_Task[0].SubTask[17].param.n2 + v3)) )
    goto LABEL_13;
  if ( *((_BYTE *)v5 + 41) || !CCBStageRole::ForceDelTaskByPFN(this->m_pRole[*v4]) )
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
  CCBStageRole::GetProperCurAction(
    this->m_pRole[2],
    CCBStageRole::ProcMagic,
    0,
    0,
    0,
    *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * this->m_bHideSceneAndRole),
    &this->m_pRole[2]->m_Task[35].cmd.bDestRole[10],
    0,
    (_DWORD *)1);
LABEL_11:
  v8 = *v4;
  x = this->m_pRole[*v4]->m_Task[36].vec1.x;
  v12[1] = 0;
  m_bHideSceneAndRole = this->m_bHideSceneAndRole;
  *(float *)v12 = x;
  v12[2] = 0;
  CCBStageRole::GetProperCurAction(
    this->m_pRole[v8],
    CCBStage::ProcessCommand,
    0,
    0,
    0,
    *((_DWORD **)&this->m_Task[0].SubTask[17].param.n2 + 658 * m_bHideSceneAndRole),
    v12,
    0,
    (_DWORD *)1);
  *((_BYTE *)v5 + 41) = 1;
LABEL_12:
  if ( CCBStageRole::ForceDelTaskByPFN(this->m_pRole[*v4]) )
LABEL_13:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF3D0
int CCBStage::ProcShowDamage(int _this, int a2)
{
  int v3; // ebp
  int v4; // eax
  char v5; // cl
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // ecx
  _DWORD *v10; // eax
  _DWORD *v11; // ecx
  int v12; // eax
  int v13; // eax
  _DWORD *v14; // ebp
  _BYTE *v15; // ecx
  int v16; // eax
  _DWORD *v17; // eax
  _DWORD *v18; // esi
  int v20; // [esp+8h] [ebp-4h]

  v3 = 2632 * *(_DWORD *)(this + 160);
  v4 = v3 + 80 * *(_DWORD *)(this + 164);
  v5 = *(_BYTE *)(v4 + this + 225);
  v6 = v4 + this + 184;
  v20 = v6;
  if ( !v5 )
  {
    v7 = 0;
    v8 = this + 24;
    do
    {
      if ( *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 4), v7) + 25)
        && *(_BYTE *)(CCBRoleState::InitUI(*(void **)(this + 4), v7) + 26) )
      {
        v9 = 3 * *(_DWORD *)(CCBRoleState::InitUI(*(void **)(this + 4), v7) + 584);
        v10 = (_DWORD *)(*(_DWORD *)v8 + 6584);
        v11 = (_DWORD *)(*(_DWORD *)(this + 20) + 4 * v9 + 92);
        * v10 = (*)*v11;
        v10[1] = v11[1];
        v10[2] = v11[2];
        *(_DWORD *)(*(_DWORD *)v8 + 6632) = *(_DWORD *)(*(_DWORD *)v8 + 6636);
      }
      ++v7;
      v8 += 4;
    }
    while ( v7 < 5 );
    v12 = g_GDB->GDB_GetItemNum(*(_DWORD *)(this + v3 + 2756));
    if ( v12 )
    {
      if ( *(_BYTE *)(v12 + 592) == 2 )
      {
        v13 = *(_DWORD *)(this + v3 + 2764);
        v14 = (_DWORD *)(this + v3 + 2764);
        if ( v13 != -1 && v13 != 10 )
        {
          v15 = (_BYTE *)*(_BYTE **)(this + 4);
          if ( v15[9497] )
          {
            if ( !*(_BYTE *)(v15->InitUI(10) + 880) )
            {
              v16 = *(_DWORD *)(this + 64);
              if ( *(_BYTE *)(v16 + 272) )
              {
                *(_DWORD *)(v16 + 6584) = *(_DWORD *)(v16 + 6596);
                *(_DWORD *)(v16 + 6588) = *(_DWORD *)(v16 + 6600);
                *(_DWORD *)(v16 + 6592) = *(_DWORD *)(v16 + 6604);
                CCBStageRole::ForceRelease(0);
              }
            }
          }
          v17 = (_DWORD *)(*(_DWORD *)(this + 64) + 6596);
          v18 = (_DWORD *)(*(_DWORD *)(this + 4 * *v14 + 24) + 6584);
          * v18 = (*)*v17;
          v18[1] = v17[1];
          v18[2] = v17[2];
        }
      }
    }
    v6 = v20;
    *(_BYTE *)(v20 + 41) = 1;
  }
  *(_DWORD *)(v6 + 16) = 4;
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
    *(void **)((char *)&this->m_Task[0].SubTask[0].fp + v4) = (void *)CCBCamControl::KeepCurCam(
                                                                        (CCBCamControl *)this->m_TempStorageWPX,
                                                                        (int)v5->m_pRoleState->m_sCombatDialog);
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
    *((_DWORD *)v6 + 16) = CCBStageRole::~CCBStageRole((CCBStageRole *)m_TempStorageWPX, v8, 1, v5);
    v6[60] = 1;
  }
  if ( !v6[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)(v10 + 52) )
  {
    *((_DWORD *)v6 + 17) = CCBStageRole::~CCBStageRole(
                             (CCBStageRole *)this->m_TempStorageWPX,
                             *((_DWORD *)v6 + 14),
                             2,
                             v5);
    v6[61] = 1;
  }
  if ( !v6[62]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)&this->m_TempStorageWPX[4].m_name[60 * *((_DWORD *)v6 + 14) + 128] )
  {
    CCBRoleState::RandSetEnemyPos(
      this->m_pRoleState,
      &this->m_Task[0].SubTask[17].param.f2 + 658 * this->m_bHideSceneAndRole);
    v6[62] = 1;
  }
  if ( CCBStageRole::ForceDelTaskByPFN(this->m_pRole[(int)v5->m_pEditor])
    && v6[62]
    && !CEffMgr::Render(this->m_pCBSystem->m_pEffMgr, *((_DWORD *)v6 + 16))
    && !CEffMgr::Render(this->m_pCBSystem->m_pEffMgr, *((_DWORD *)v6 + 17)) )
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
      if ( m_pRoleState->m_Role[0].sModel[v7 + 5] && !*(_BYTE *)(m_pRoleState->InitUI(v6) + 880) )
      {
        v10 = (CCBStageRole *)*m_pRole;
        v10->m_Task[35].cmd.bDestRole[7] = (*m_pRole)->m_Task[35].cmd.bDestRole[10];
        v10->m_Task[35].cmd.bDestRole[8] = v10->m_Task[35].cmd.bValid;
        v10->m_Task[35].cmd.bDestRole[9] = LODWORD(v10->m_Task[35].fTemp);
        (*m_pRole)->m_Task[36].fp = (void *)LODWORD((*m_pRole)->m_Task[36].vec1.x);
      }
      v7 += 892;
      ++v6;
      ++m_pRole;
    }
    while ( v7 < 9812 );
    v11 = (CCBRoleState *)this->m_pRoleState;
    if ( BYTE1(v11->m_Role[5].bMagicMastered[4][1]) )
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
  int v3; // eax
  char *v4; // edi
  char *v5; // ebp
  int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v13[6]; // [esp+14h] [ebp-1Ch] BYREF
  int v14; // [esp+2Ch] [ebp-4h]

  memset(v13, 0, 12);
  v3 = 2632 * *(_DWORD *)&this->m_pCBSystem[160];
  v4 = (char *)&this->m_pCBSystem[v3 + 2752];
  v5 = (char *)&this->m_pCBSystem[80 * *(_DWORD *)&this->m_pCBSystem[164] + 184 + v3];
  if ( !CCBStageRole::IsReady(
          *(CCBStageRole **)&this->m_pCBSystem[4 * *(_DWORD *)&this->m_pCBSystem[v3 + 2760] + 24],
          *(_DWORD *)&this->m_pCBSystem[v3 + 2744]) )
    goto LABEL_17;
  if ( !v5[41] )
  {
    if ( !CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]) )
      return 0;
    CCBStageRole::GetState(*(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]);
    v6 = *(_DWORD *)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24];
    *(_DWORD *)(v6 + 6632) = *(_DWORD *)(v6 + 6636);
    v7 = *((_DWORD *)v4 + 1);
    if ( v7 > 0x10D0 )
    {
      if ( v7 == 4505 )
      {
        this->ResetAll();
        v11 = *(_DWORD *)&this->m_pCBSystem[160];
        v14 = 0;
        CCBStageRole::GetProperCurAction(
          *(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24],
          CCBStageRole::ProcTurnToRole,
          0,
          0,
          0,
          *(_DWORD **)&this->m_pCBSystem[2632 * v11 + 2744],
          v13,
          v4,
          (_DWORD *)1);
      }
    }
    else if ( v7 == 4304 || (v8 = v7 - 4101) == 0 )
    {
      this->ResetAll();
      v10 = *(_DWORD *)&this->m_pCBSystem[160];
      v14 = 0;
      CCBStageRole::GetProperCurAction(
        *(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24],
        CCBStageRole::ProcMagic,
        0,
        0,
        0,
        *(_DWORD **)&this->m_pCBSystem[2632 * v10 + 2744],
        v13,
        v4,
        (_DWORD *)1);
    }
    else if ( v8 == 104 )
    {
      this->ResetAll();
      v9 = *(_DWORD *)&this->m_pCBSystem[160];
      v14 = 0;
      CCBStageRole::GetProperCurAction(
        *(CCBStageRole **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24],
        CCBStageRole::ProcUseRecoverItem,
        0,
        0,
        0,
        *(_DWORD **)&this->m_pCBSystem[2632 * v9 + 2744],
        v13,
        v4,
        (_DWORD *)1);
    }
    v5[41] = 1;
  }
  if ( CCBStageRole::ForceDelTaskByPFN(*(_DWORD **)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]) || v5[43] == 1 )
  {
    CCBStageRole::TryRelease(*(_DWORD *)&this->m_pCBSystem[4 * *((_DWORD *)v4 + 2) + 24]);
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
  int *v7; // eax
  int v8; // ecx
  int *v9; // eax
  gbVec3D *v10; // eax
  int v11; // eax
  int *v12; // esi
  gbVec3D *v13; // eax
  gbVec3D *v14; // eax
  int v15; // edx
  int result; // eax
  int *v17; // eax
  int *v18; // eax
  gbVec3D *v19; // eax
  int v20; // eax
  int v21; // ebx
  gbVec3D *v22; // eax
  int v23; // ecx
  int v24; // edx
  int *v26; // eax
  int *v27; // eax
  gbVec3D *v28; // eax
  int v29; // eax
  gbVec3D *v30; // eax
  float v31; // [esp+18h] [ebp-38h]
  float v32; // [esp+18h] [ebp-38h]
  float v33; // [esp+18h] [ebp-38h]
  float v34; // [esp+18h] [ebp-38h]
  float v35; // [esp+18h] [ebp-38h]
  float v36; // [esp+18h] [ebp-38h]
  float v37; // [esp+18h] [ebp-38h]
  float v38; // [esp+1Ch] [ebp-34h]
  float v39; // [esp+1Ch] [ebp-34h]
  float v40; // [esp+1Ch] [ebp-34h]
  float v41; // [esp+1Ch] [ebp-34h]
  float v42; // [esp+1Ch] [ebp-34h]
  float v43; // [esp+1Ch] [ebp-34h]
  float v44; // [esp+1Ch] [ebp-34h]
  float v45; // [esp+20h] [ebp-30h]
  float v46; // [esp+20h] [ebp-30h]
  float v47; // [esp+20h] [ebp-30h]
  float v48; // [esp+20h] [ebp-30h]
  float v49; // [esp+20h] [ebp-30h]
  float v50; // [esp+20h] [ebp-30h]
  float v51; // [esp+20h] [ebp-30h]
  int v52; // [esp+24h] [ebp-2Ch]
  int v53; // [esp+24h] [ebp-2Ch]
  int v54; // [esp+24h] [ebp-2Ch]
  int v55; // [esp+24h] [ebp-2Ch]
  int v56; // [esp+30h] [ebp-20h] BYREF
  int v57; // [esp+34h] [ebp-1Ch] BYREF
  int v58; // [esp+38h] [ebp-18h] BYREF
  int v59; // [esp+3Ch] [ebp-14h]
  int v60; // [esp+40h] [ebp-10h]
  _BYTE v61[12]; // [esp+44h] [ebp-Ch] BYREF
  int *v62; // [esp+54h] [ebp+4h]
  int v63; // [esp+58h] [ebp+8h]

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
    dword_17AA870 = 0;
    byte_17AA89C |= 4u;
    dword_17AA874 = 0;
    dword_17AA878 = 0;
    atexit(nullsub_28);
  }
  v2 = v63;
  v56 = -1;
  v57 = -1;
  v3 = *(_DWORD *)(v63 + 12);
  if ( v3 == -1 )
  {
    v4 = CCBRoleState::WriteBackRoleData(*(_DWORD **)&this->m_pCBSystem[4], v63, &v56, &v57);
    v5 = v4;
    if ( v4 <= 11 )
    {
      v17 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v4 + 24] + 6596);
      dword_17AA880 = *v17;
      dword_17AA884 = v17[1];
      dword_17AA888 = v17[2];
      v18 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 8) + 24] + 6584);
      dword_17AA890 = *v18;
      dword_17AA894 = v18[1];
      dword_17AA898 = v18[2];
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
      v19 = (gbVec3D *)gbVec3D::gbVec3D((gbVec3D *)v61, v34, v41, v48);
      v58 = *(_DWORD *)v19;
      v59 = *((_DWORD *)v19 + 1);
      v20 = *((_DWORD *)v19 + 2);
      dword_17AA870 = v58;
      v60 = v20;
      dword_17AA874 = v59;
      dword_17AA878 = v20;
      gbVec3D::Normalize((gbVec3D *)&dword_17AA870);
      v21 = *(_DWORD *)(v63 + 8);
      if ( v21 == 4 && *(_BYTE *)(*(_DWORD *)&g_SceneMgr.m_info[6568] + 613) == 1 )
      {
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[40], v52);
        __asm { fstp    [esp+2Ch+a2] }
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * v5 + 24], v53);
        __asm
        {
          fadd    [esp+2Ch+a2]
          fadd    ds:flt_56A77C
        }
      }
      else
      {
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * v21 + 24], v52);
        __asm { fstp    [esp+2Ch+a2] }
        CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * v5 + 24], v54);
        __asm { fadd    [esp+2Ch+a2] }
      }
      __asm
      {
        fld     dword_17AA870
        fmul    st, st(1)
      }
      __asm
      {
        fstp    dword_17AA870
        fld     dword_17AA874
        fmul    st, st(1)
        fstp    dword_17AA874
        fld     dword_17AA878
        fmul    st, st(1)
        fstp    dword_17AA878
        fstp    st
        fld     dword_17AA878
        fadd    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA874
        fadd    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA870
        fadd    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v22 = (gbVec3D *)gbVec3D::gbVec3D((gbVec3D *)v61, v35, v42, v49);
      v58 = *(_DWORD *)v22;
      v23 = *((_DWORD *)v22 + 1);
      __asm { fld     [esp+20h+var_18] }
      v24 = *((_DWORD *)v22 + 2);
      result = (int)v62;
      v59 = v23;
      v60 = v24;
      __asm { fstp    dword ptr [eax] }
      *(float *)result = _ET1;
      v62[1] = v23;
      v62[2] = v24;
    }
    else
    {
      _EDI = v62;
      v7 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v56 + 24] + 6596);
      * v62 = (*)*v7;
      v8 = v57;
      v62[1] = v7[1];
      v62[2] = v7[2];
      v9 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v8 + 24] + 6596);
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
      v10 = (gbVec3D *)gbVec3D::gbVec3D((gbVec3D *)v61, v31, v38, v45);
      v58 = *(_DWORD *)v10;
      __asm
      {
        fld     [esp+2Ch+var_18]
        fmul    ds:flt_56A610
      }
      v59 = *((_DWORD *)v10 + 1);
      v11 = *((_DWORD *)v10 + 2);
      __asm
      {
        fstp    dword_17AA880
        fld     [esp+2Ch+var_14]
        fmul    ds:flt_56A610
      }
      v60 = v11;
      __asm
      {
        fstp    dword_17AA884
        fld     [esp+2Ch+var_10]
        fmul    ds:flt_56A610
        fstp    dword_17AA888
      }
      v12 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 8) + 24] + 6584);
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
      v13 = (gbVec3D *)gbVec3D::gbVec3D((gbVec3D *)v61, v32, v39, v46);
      v58 = *(_DWORD *)v13;
      v59 = *((_DWORD *)v13 + 1);
      v60 = *((_DWORD *)v13 + 2);
      dword_17AA870 = v58;
      dword_17AA874 = v59;
      dword_17AA878 = v60;
      gbVec3D::Normalize((gbVec3D *)&dword_17AA870);
      __asm
      {
        fld     dword_17AA870
        fmul    ds:flt_56A64C
      }
      __asm
      {
        fstp    dword_17AA870
        fld     dword_17AA874
        fmul    ds:flt_56A64C
        fstp    dword_17AA874
        fld     dword_17AA878
        fmul    ds:flt_56A64C
        fst     dword_17AA878
        fadd    dword_17AA888
        fstp    [esp+30h+var_30]
        fld     dword_17AA874
        fadd    dword_17AA884
      }
      __asm
      {
        fstp    [esp+34h+var_34]
        fld     dword_17AA870
        fadd    dword_17AA880
      }
      __asm { fstp    [esp+38h+var_38] }
      v14 = (gbVec3D *)gbVec3D::gbVec3D((gbVec3D *)v61, v33, v40, v47);
      v58 = *(_DWORD *)v14;
      v59 = *((_DWORD *)v14 + 1);
      v15 = v59;
      result = *((_DWORD *)v14 + 2);
      *v62 = v58;
      v62[1] = v15;
      v62[2] = result;
      v60 = result;
    }
  }
  else
  {
    v26 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * v3 + 24] + 6596);
    dword_17AA880 = *v26;
    dword_17AA884 = v26[1];
    dword_17AA888 = v26[2];
    v27 = (int *)(*(_DWORD *)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 8) + 24] + 6584);
    dword_17AA890 = *v27;
    dword_17AA894 = v27[1];
    dword_17AA898 = v27[2];
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
    v28 = (gbVec3D *)gbVec3D::gbVec3D((gbVec3D *)v61, v36, v43, v50);
    v58 = *(_DWORD *)v28;
    v59 = *((_DWORD *)v28 + 1);
    v29 = *((_DWORD *)v28 + 2);
    dword_17AA870 = v58;
    v60 = v29;
    dword_17AA874 = v59;
    dword_17AA878 = v29;
    gbVec3D::Normalize((gbVec3D *)&dword_17AA870);
    CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * *(_DWORD *)(v63 + 12) + 24], v52);
    __asm { fstp    [esp+2Ch+a2] }
    CCBStageRole::GetStatus(*(CCBStageRole **)&this->m_pCBSystem[4 * *(_DWORD *)(v2 + 8) + 24], v55);
    __asm
    {
      fadd    [esp+2Ch+a2]
      fld     dword_17AA870
      fmul    st, st(1)
      fstp    dword_17AA870
      fld     dword_17AA874
      fmul    st, st(1)
      fstp    dword_17AA874
      fld     dword_17AA878
      fmul    st, st(1)
      fstp    dword_17AA878
    }
    __asm { fstp    st }
    if ( *(_DWORD *)CCBRoleState::InitUI(*(void **)&this->m_pCBSystem[4], *(_DWORD *)(v2 + 8)) == 7364
      || *(_DWORD *)CCBRoleState::InitUI(*(void **)&this->m_pCBSystem[4], *(_DWORD *)(v2 + 8)) == 7381 )
    {
      __asm
      {
        fld     dword_17AA870
        fadd    st, st
        fstp    dword_17AA870
        fld     dword_17AA874
        fadd    st, st
        fstp    dword_17AA874
        fld     dword_17AA878
        fadd    st, st
        fstp    dword_17AA878
      }
    }
    __asm
    {
      fld     dword_17AA878
      fadd    dword_17AA888
    }
    __asm
    {
      fstp    [esp+30h+var_30]
      fld     dword_17AA874
      fadd    dword_17AA884
    }
    __asm
    {
      fstp    [esp+34h+var_34]
      fld     dword_17AA870
      fadd    dword_17AA880
    }
    __asm { fstp    [esp+38h+var_38] }
    v30 = (gbVec3D *)gbVec3D::gbVec3D((gbVec3D *)v61, v37, v44, v51);
    v58 = *(_DWORD *)v30;
    v59 = *((_DWORD *)v30 + 1);
    v60 = *((_DWORD *)v30 + 2);
    return v62->operator=(&v58);
  }
  return result;
}

// 0x00503CF0
int CCBStage::UpdatePhysics()
{
  int result; // eax
  float *v2; // ecx
  int v3; // edx
  double v4; // st7
  __int16 v5; // fps
  double v6; // st6
  bool v7; // c0
  char v8; // c2
  bool v9; // c3

  result = *(_DWORD *)this->m_pCBSystem;
  v2 = (float *)&this->m_pCBSystem[104];
  v3 = 11;
  v4 = *(double *)(result + 64) * 30.0;
  do
  {
    if ( *v2 > 0.0 )
    {
      if ( *v2 <= 160.0 )
        * v2 = (*)*v2 - v4;
      else
        *v2 = 160.0;
    }
    v6 = *v2;
    v7 = v6 < 0.0;
    v8 = 0;
    v9 = v6 == 0.0;
    LOWORD(result) = v5;
    if ( v6 < 0.0 )
      *v2 = 0.0;
    ++v2;
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
  int v5; // eax
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
  float v17; // [esp+34h] [ebp-3Ch]
  struct tagPOINT Point; // [esp+38h] [ebp-38h] BYREF
  float v19; // [esp+40h] [ebp-30h] BYREF
  int v20; // [esp+44h] [ebp-2Ch]
  float v21; // [esp+48h] [ebp-28h]
  float v22; // [esp+4Ch] [ebp-24h] BYREF
  float v23; // [esp+50h] [ebp-20h]
  float v24; // [esp+54h] [ebp-1Ch]
  float v25; // [esp+58h] [ebp-18h]
  float v26; // [esp+60h] [ebp-10h]
  _DWORD v27[3]; // [esp+64h] [ebp-Ch] BYREF

  *(_DWORD *)&this->m_pCBSystem[448] = 0;
  sub_5049F0(this);
  sub_504A80(this->m_pCBSystem);
  GRPinput::GetCursorPos(&Point);
  if ( GRPinput::GetKeyState(&g_Input, 0x100u) || GRPinput::GetKeyState(&g_Input, 0x101u) )
  {
    x = (double)Point.x;
    v15 = x - *(float *)&this->m_pCBSystem[552];
    y = (double)Point.y;
    v17 = y;
    v4 = y - *(float *)&this->m_pCBSystem[556];
    *(float *)&this->m_pCBSystem[556] = v17;
    v16 = v4;
    *(float *)&this->m_pCBSystem[552] = x;
  }
  else
  {
    v16 = 0.0;
    v15 = 0.0;
    *(float *)&this->m_pCBSystem[552] = (float)Point.x;
    *(float *)&this->m_pCBSystem[556] = (float)Point.y;
  }
  if ( !*(_BYTE *)(**(_DWORD **)&this->m_pCBSystem[544] + 134) )
  {
    if ( GRPinput::GetKeyState(&g_Input, 0x100u) )
    {
      v5 = *(_DWORD *)&this->m_pCBSystem[544];
      if ( *(_DWORD *)(v5 + 88) == -1 && !*(_BYTE *)(*(_DWORD *)(v5 + 20) + 964) )
      {
        v22 = *(float *)&this->m_pCBSystem[504];
        v23 = *(float *)&this->m_pCBSystem[508];
        v24 = *(float *)&this->m_pCBSystem[512];
        gbVec3D::Normalize((gbVec3D *)&v22);
        v27[0] = *(_DWORD *)&this->m_pCBSystem[516];
        v27[1] = *(_DWORD *)&this->m_pCBSystem[520];
        v27[2] = *(_DWORD *)&this->m_pCBSystem[524];
        gbVec3D::Normalize((gbVec3D *)v27);
        v19 = 0.0;
        v20 = 0;
        v21 = 0.0;
        gbVec3D::CrossProduct((gbVec3D *)v27, (const struct gbVec3D *)&v22, (struct gbVec3D *)&v19);
        gbVec3D::Normalize((gbVec3D *)&v19);
        v6 = v16 + v16;
        if ( (g_Input.m_mousept[6712] & 0xF) == 1 )
        {
          v22 = 0.0;
          v23 = v6;
          v7 = (float)0.0;
          v24 = 0.0;
          v8 = v15 + v15;
          v19 = v19 * v8;
        }
        else
        {
          v23 = 0.0;
          v22 = v6 * v22;
          v7 = v6 * v24;
          v24 = v7;
          v8 = v15 + v15;
          v19 = v8 * v19;
        }
        v21 = v21 * v8;
        v9 = v7;
        v10 = v23;
        v26 = v9;
        v20 = 0;
        v25 = v19 + v22;
        v26 = v26 + v21;
        *(float *)&this->m_pCBSystem[480] = v25 + *(float *)&this->m_pCBSystem[480];
        *(float *)&this->m_pCBSystem[484] = v10 + *(float *)&this->m_pCBSystem[484];
        *(float *)&this->m_pCBSystem[488] = v26 + *(float *)&this->m_pCBSystem[488];
        InputSystem::ProcessKeyboard(1);
        InputSystem::ProcessKeyboard(0);
      }
    }
    v11 = (double)*(int *)&g_Input.m_mousept[5128] * 0.25;
    if ( (g_Input.m_mousept[6712] & 0xF) == 1 )
    {
      *(float *)&this->m_pCBSystem[464] = v11 * 0.001 + *(float *)&this->m_pCBSystem[464];
      InputSystem::ProcessKeyboard(0);
    }
    else if ( (g_Input.m_mousept[6728] & 0xF) == 1 )
    {
      v12 = v11 * 0.001 + *(float *)&this->m_pCBSystem[4];
      *(_DWORD *)&this->m_pCBSystem[8] = 0;
      *(float *)&this->m_pCBSystem[4] = v12;
    }
    else
    {
      *(float *)&this->m_pCBSystem[468] = v11 + *(float *)&this->m_pCBSystem[468];
      InputSystem::ProcessKeyboard(1);
    }
    if ( GRPinput::GetKeyState(&g_Input, 0x101u)
      && !*(_BYTE *)(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 20) + 964) )
    {
      v13 = v15 * 0.0043633231 + *(float *)&this->m_pCBSystem[456];
      *(float *)&this->m_pCBSystem[456] = v13;
      *(float *)&this->m_pCBSystem[452] = *(float *)&this->m_pCBSystem[452] - v16 * 0.0043633231;
      if ( v13 <= 3.1415927 )
      {
        if ( v13 <= -3.1415927 )
          v13 = v13 + 6.2831855;
      }
      else
      {
        v13 = v13 - 6.2831855;
      }
      *(float *)&this->m_pCBSystem[456] = v13;
      InputSystem::ProcessKeyboard(0);
    }
  }
  *(_DWORD *)&this->m_pCBSystem[468] = 1120403456;
  InputSystem::ProcessKeyboard(0);
  CameraCtrl::SetAsCurrent((CameraCtrl *)this, 3);
  Combat::LogMessage(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 68), 5, 135, aCamXFYFZF);
  Combat::LogMessage(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 68), 5, 150, aCamYawFPitchFR);
  return Combat::LogMessage(*(_DWORD *)(*(_DWORD *)&this->m_pCBSystem[544] + 68), 5, 165, aCamFovF);
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
  int v10; // eax
  char *Instance; // eax
  double v12; // st7
  double v13; // st6
  double v14; // st7
  double v15; // st7
  int v16; // eax
  CCBStageRole *v17; // eax
  int v18; // eax
  CCBStageRole *v19; // eax
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
  v2 = (char *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396]];
  if ( v2[506] )
  {
    v9 = v27;
  }
  else
  {
    *((_DWORD *)v2 + 122) = -1054867456;
    v3 = 96 * *(_DWORD *)&this->m_pCBSystem[396];
    *(_DWORD *)&this->m_pCBSystem[6608] = *(_DWORD *)&this->m_pCBSystem[v3 + 432];
    *(_DWORD *)&this->m_pCBSystem[6612] = *(_DWORD *)&this->m_pCBSystem[v3 + 436];
    *(_DWORD *)&this->m_pCBSystem[6616] = *(_DWORD *)&this->m_pCBSystem[v3 + 440];
    v4 = *(float *)&this->m_pCBSystem[6608] - *(float *)&this->m_pCBSystem[6584];
    *(float *)&v22 = *(float *)&this->m_pCBSystem[6612] - *(float *)&this->m_pCBSystem[6588];
    v5 = *(float *)&this->m_pCBSystem[6616] - *(float *)&this->m_pCBSystem[6592];
    dword_17AB6DC = v22;
    *(float *)&v25 = v5;
    *(float *)&dword_17AB6D8 = v4;
    dword_17AB6E0 = v25;
    v6 = gbVec3D::Length((gbVec3D *)&dword_17AB6D8);
    if ( v6 < 2.0 )
    {
      *(_DWORD *)&this->m_pCBSystem[6584] = *(_DWORD *)&this->m_pCBSystem[6608];
      *(_DWORD *)&this->m_pCBSystem[6588] = *(_DWORD *)&this->m_pCBSystem[6612];
      *(_DWORD *)&this->m_pCBSystem[6592] = *(_DWORD *)&this->m_pCBSystem[6616];
      this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
      return 0;
    }
    gbVec3D::Normalize((gbVec3D *)&dword_17AB6D8);
    flt_17ABCDC = acos(
                    *(float *)&dword_17AB6D0 * *(float *)&dword_17AB6E0
                  + *(float *)&dword_17AB6CC * *(float *)&dword_17AB6DC
                  + *(float *)&dword_17AB6C8 * *(float *)&dword_17AB6D8);
    if ( *(float *)&dword_17AB6D8 < 0.0 )
      flt_17ABCDC = 6.2831855 - flt_17ABCDC;
    *(float *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 492] = flt_17ABCDC * 57.29578;
    *(_DWORD *)&this->m_pCBSystem[6620] = dword_17AB6D8;
    v28 = v6;
    v8 = v28 + v28;
    *(_DWORD *)&this->m_pCBSystem[6624] = dword_17AB6DC;
    *(_DWORD *)&this->m_pCBSystem[6628] = dword_17AB6E0;
    *(float *)&this->m_pCBSystem[6620] = v8 * *(float *)&this->m_pCBSystem[6620];
    *(float *)&this->m_pCBSystem[6624] = v8 * *(float *)&this->m_pCBSystem[6624];
    *(float *)&this->m_pCBSystem[6628] = v8 * *(float *)&this->m_pCBSystem[6628];
    if ( CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pCBSystem[4], *(_DWORD *)&this->m_pCBSystem[284]) )
      *(_DWORD *)&this->m_pCBSystem[6568] = 31;
    else
      *(_DWORD *)&this->m_pCBSystem[6568] = 52;
    CCBStageRole::IsGrabedBy((int)this);
    v9 = 0;
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 506] = 1;
    CCBStageRole::ClearBadPushTask((int)this, 0.40000001);
    v10 = *(_DWORD *)&this->m_pCBSystem[284];
    this->m_pCBSystem[273] = 1;
    if ( v10 == 3 )
    {
      Instance = (char *)CScreenMode::GetInstance();
      CScreenMode::AudioSetPosition((CScreenMode *)Instance, aWe013, 1);
    }
  }
  v12 = *(float *)&this->m_pCBSystem[6608] - *(float *)&this->m_pCBSystem[6584];
  *(float *)&v23 = *(float *)&this->m_pCBSystem[6612] - *(float *)&this->m_pCBSystem[6588];
  v13 = *(float *)&this->m_pCBSystem[6616] - *(float *)&this->m_pCBSystem[6592];
  dword_17AB6DC = v23;
  *(float *)&v26 = v13;
  *(float *)&dword_17AB6D8 = v12;
  dword_17AB6E0 = v26;
  if ( v9 == *(_DWORD *)&this->m_pCBSystem[6664] )
    *(_DWORD *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] = 1120403456;
  if ( *(float *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] > 0.0
    && gbVec3D::Length((gbVec3D *)&dword_17AB6D8) > 2.0 )
  {
    v14 = *(double *)(**(_DWORD **)this->m_pCBSystem + 64);
    v21 = *(float *)&this->m_pCBSystem[6620] * v14;
    v24 = *(float *)&this->m_pCBSystem[6624] * v14;
    v15 = v14 * *(float *)&this->m_pCBSystem[6628];
    *(float *)&this->m_pCBSystem[6584] = v21 + *(float *)&this->m_pCBSystem[6584];
    *(float *)&this->m_pCBSystem[6588] = v24 + *(float *)&this->m_pCBSystem[6588];
    *(float *)&this->m_pCBSystem[6592] = v15 + *(float *)&this->m_pCBSystem[6592];
    *(float *)&this->m_pCBSystem[6632] = *(double *)(**(_DWORD **)this->m_pCBSystem + 64) * 720.0
                                       + *(float *)&this->m_pCBSystem[6632];
  }
  if ( v9 == *(_DWORD *)&this->m_pCBSystem[6668] && gbVec3D::Length((gbVec3D *)&dword_17AB6D8) <= 2.0 )
    *(_DWORD *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] = -1054867456;
  gbVec3D::Normalize((gbVec3D *)&dword_17AB6D8);
  flt_17ABCDC = acos(
                  *(float *)&dword_17AB6D0 * *(float *)&dword_17AB6E0
                + *(float *)&dword_17AB6CC * *(float *)&dword_17AB6DC
                + *(float *)&dword_17AB6C8 * *(float *)&dword_17AB6D8);
  if ( *(float *)&dword_17AB6D8 < 0.0 )
    flt_17ABCDC = 6.2831855 - flt_17ABCDC;
  if ( fabs(flt_17ABCDC * 57.29578 - *(float *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 492]) >= 1.570796370506287 )
  {
    *(_DWORD *)&this->m_pCBSystem[6584] = *(_DWORD *)&this->m_pCBSystem[6608];
    *(_DWORD *)&this->m_pCBSystem[6588] = *(_DWORD *)&this->m_pCBSystem[6612];
    *(_DWORD *)&this->m_pCBSystem[6592] = *(_DWORD *)&this->m_pCBSystem[6616];
    *(_DWORD *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 488] = -1054867456;
  }
  if ( v9 == *(_DWORD *)&this->m_pCBSystem[6644] )
  {
    *(_DWORD *)&this->m_pCBSystem[6584] = *(_DWORD *)&this->m_pCBSystem[6608];
    *(_DWORD *)&this->m_pCBSystem[6588] = *(_DWORD *)&this->m_pCBSystem[6612];
    *(_DWORD *)&this->m_pCBSystem[6592] = *(_DWORD *)&this->m_pCBSystem[6616];
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
    v16 = *(_DWORD *)&this->m_pCBSystem[284];
    this->m_pCBSystem[273] = 0;
    if ( v16 == 3 )
    {
      v17 = (CCBStageRole *)CScreenMode::GetInstance();
      v17->PlaySound(aWe013, v20);
    }
  }
  if ( !CCBRoleState::IsRoleAlive(*(CCBRoleState **)&this->m_pCBSystem[4], *(_DWORD *)&this->m_pCBSystem[284]) )
  {
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
    v18 = *(_DWORD *)&this->m_pCBSystem[284];
    this->m_pCBSystem[273] = 0;
    if ( v18 == 3 )
    {
      v19 = (CCBStageRole *)CScreenMode::GetInstance();
      v19->PlaySound(aWe013, v20);
    }
  }
  return 0;
}

// 0x0050E0D0
int CCBStage::ProcessCommand()
{
  char *v2; // eax
  int v3; // edx

  v2 = (char *)&this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396]];
  if ( !v2[506] )
  {
    v3 = *(_DWORD *)&this->m_pCBSystem[284];
    *(_DWORD *)&this->m_pCBSystem[6632] = *((_DWORD *)v2 + 108);
    if ( CCBStageRole::IsActive(*(CCBStageRole **)&this->m_pCBSystem[4], v3) )
      *(_DWORD *)&this->m_pCBSystem[6568] = 32;
    else
      *(_DWORD *)&this->m_pCBSystem[6568] = 50;
    CCBStageRole::IsGrabedBy((int)this);
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 506] = 1;
    this->m_pCBSystem[96 * *(_DWORD *)&this->m_pCBSystem[396] + 505] = 1;
  }
  return 0;
}
