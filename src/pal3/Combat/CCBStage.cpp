#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CCBStage.h"
#include "pal3/gen/C3DSpark.h"
#include "pal3/gen/CCBRoleState.h"
#include "pal3/gen/CCBStageCam.h"
#include "pal3/gen/CCBStageRole.h"
#include "pal3/gen/CCBStageScene.h"
#include "pal3/gen/CCBStageShadow.h"
#include "pal3/gen/CCCTData.h"
#include "pal3/gen/CEffectSystem.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/CameraCtrl.h"
#include "pal3/gen/Combat.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/InputSystem.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/SceneMgr.h"

// Forward declarations for unnamed functions
int sub_4C5C20(...);
int sub_4DF710(...);
int sub_4DFA10(...);
int sub_5049F0(...);
int sub_504A80(...);

// Unnamed globals (extern)
extern char aCamFovF[];
extern char aCamXFYFZF[];
extern char aCamYawFPitchFR[];
extern char aWe013[];
extern unsigned char byte_17A9927;
extern unsigned char byte_17AA870;
extern unsigned char byte_17AA89C;
extern unsigned char byte_17AA920;
extern unsigned char byte_17AB6E4;
extern int dword_17A990C;
extern int dword_17AA880;
extern int dword_17AA884;
extern int dword_17AA888;
extern int dword_17AA890;
extern int dword_17AA894;
extern int dword_17AA898;
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
    ((int)this->m_pCamControl)->DoTask();
    nullsub_3(this->m_TempStorageNGH);
    nullsub_3(this->m_NGHVariance);
    this->UpdatePhysics();
    a2 = this->m_pCBSystem->m_DeltaTime;
    v4 = (CEffectSystem *)CEffectSystem::DestroyAllEffect();
    v4->SetVisible(a2);
  }
  return result;
}

// 0x004FC3A0
int CCBStage::EditorUpdate()
{
  int v2; // ebp
  CCBStageCam *m_pCam; // eax
  float *p_OrthoSize; // eax
  void *v5; // eax
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
  void *v19; // eax
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
  v5 = (void *)CEffectSystem::DestroyAllEffect();
  ((int)v5)->HandleViewMove(v21);
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
        ((void (*)(gbGeomNode *, _DWORD))this->m_pScene->m_pPointer->next[4].next)(
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
  ((void (*)(gbVisNode *, _DWORD))this->m_pScene->m_pLights->next[4].next)(this->m_pScene->m_pLights, 0);
  ((SceneMgr *)this->m_pCBSystem->m_pEffMgr)->RenderAll();
  ((SceneMgr *)this->m_pCBSystem->m_pATSEffMgr)->RenderAll();
  ((int)this->m_pCBSystem->m_p3DSpark->m_Spark)->Render((struct gbVec3D *)gbSceneGraph::End);
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
      ((int)m_pScene)->LoadPointer(60);
    }
    if ( dword_17A990C == 4 )
    {
      v18 = (CCBStageScene *)this->m_pScene;
      if ( HIBYTE(v18->m_EnemyFiveLineupQuad.color.Blue) )
        ((int)v18)->LoadPointer(60);
      ((int)this->m_pCamControl)->~CCCTData();
    }
  }
LABEL_31:
  sub_4DFA10(&this->m_TempStorageNGH->m_actarray);
  v19 = (void *)CEffectSystem::DestroyAllEffect();
  ((int)v19)->Update();
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

// 0x004FCBD0
char CCBStage::GetTaskID(int a2, int a3)
{
  char *v3; // eax

  v3 = (char *)this + 2632 * a2 + 80 * a3;
  *((_DWORD *)v3 + 50) = 3;
  *((float *)v3 + 52) = this->m_pCBSystem->m_fTimeFund;
  return 1;
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
  ((CCBStageCam *)&m_pCam->OrthoSize)->PointWorldToScr(&v14, &v18, &v19);
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
    ((int)this)->IsGrabedBy();
    v9 = 0;
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 2) = 1;
    ((int)this)->ClearBadPushTask(0.40000001);
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
    ((int)this)->IsGrabedBy();
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 2) = 1;
    *((_BYTE *)&this->m_Task[0].SubTask[1].nTemp3 + 96 * LODWORD(this->m_Task[0].SubTask[1].fStartTime) + 1) = 1;
  }
  return 0;
}
