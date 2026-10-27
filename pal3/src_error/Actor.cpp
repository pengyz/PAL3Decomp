#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Role/Actor.h"
#include "Misc/AStarPathFinder.h"
#include "Misc/ArcSceneMonster.h"
#include "Misc/Array.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBSystem.h"
#include "Effect/CEffgbParticle.h"
#include "Render/CScreenMode.h"
#include "Misc/CScreenModeNode.h"
#include "Scene/CameraCtrl.h"
#include "Misc/ECBStageTaskState.h"
#include "GameBase/GRPinput.h"
#include "Misc/Object.h"
#include "Role/Object3D.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget2.h"
#include "Render/RenderTarget3.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleCameraCtrl.h"
#include "Role/RoleSystem.h"
#include "Scene/Scene.h"
#include "Scene/SceneObj.h"
#include "Effect/ScreenEffect.h"
#include "Effect/ScreenEffectMgr.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/TxtFile.h"
#include "Misc/UIBigMap.h"
#include "Misc/UIButton.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIListBox.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIScene.h"
#include "UI/UIWnd.h"
#include "Misc/VideoPlayer.h"
#include "Misc/s_RoleState.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/tagActionCommand.h"
#include "Misc/tagCmdData.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_407790(...);
int sub_4B70B0(...);
int sub_53D3F0(...);
int todo_00530F70(...);
void todo_00532A30(void); // no-arg compiler stub (does not read ecx)

class CScreenModeNode;

// Unnamed globals (extern)
extern CHAR aSoftwareSoftst_2[];
extern int dword_DE6F70;
extern float flt_17B41E0;
extern float flt_DE71F8;
extern float flt_DE7480;
void __cdecl nullsub_2(...);
void __cdecl nullsub_71(void);
void __cdecl nullsub_72(void);
extern CScreenModeNode stru_17B3ED8;

// 0x004083D0
void Actor::_todo_004083D0(int a2)
{
  (((AStarPathFinder *)this))->AStarPathFinder::ReleaseAll();
}

// 0x0041B9F0
unsigned int Actor::GetInnerAnimDuration(int animId)
{
  return (((Actor *)&this->m_InnerActor))->Actor::GetAnimDuration(animId);
}

// 0x0041BCA0
int Actor::ExecuteAction(tagActionCommand *pCmd)
{
  int result; // eax
  Actor *pTargetActor; // edx

  LODWORD(this->m_fDirX) = (unsigned long)pCmd->cmdType;
  result = (int)this[1].m_pEquipAtt1[0];
  if ( result != 3 )
  {
    (((RoleSystem *)this))->RoleSystem::NotifySceneChange(*((unsigned __int8 *)&pCmd->targetZ + 4)) /* [ROWTABLE] */;
    if ( this[1].m_pEquipAtt1[0] == (RoleAtt *)3 )
    {
      pTargetActor = (Actor *)pCmd->pTargetActor;
      LODWORD(this->m_vecTargetPos.x) = (unsigned long)pTargetActor;
      this->m_vecTargetPos.y = pCmd->targetY;
      this->m_vecTargetPos.z = pCmd->targetZ;
      this->m_actarray_begin = ((Actor *)(pTargetActor));
      this->m_actarray_end = ((Actor *)((Actor *)LODWORD(this->m_vecTargetPos.y)));
      this->m_actarray_capacity_end = ((Actor *)((Actor *)LODWORD(this->m_vecTargetPos.z)));
      this->m_actarray_end = ((Actor *)0);
    }
    else
    {
      (((RoleSystem *)this))->RoleSystem::SetTargetRotation((gbVec3D *)&pCmd->pTargetActor) /* [ROWTABLE] */;
    }
    result = (((RoleSystem *)this))->RoleSystem::UpdateMovement(pCmd->fSpeed, 1) /* [ROWTABLE] */;
    this->m_nCmdParam = pCmd->nCmdParam;
  }
  return result;
}

// 0x0041F2D0
void Actor::_todo_0041F2D0(int a2)
{
  char *v2; // esi
  int v3; // edi

  v2 = (char *)&unk_C11720.m_fTimerAccum;
  v3 = 55;
  do
  {
    v2 += 68;
    --v3;
  }
  while ( v3 );
  unk_C11720.m_pActorData = 0;
  unk_C11720.m_fTimerLimit = 0;
  unk_C11720.m_bInitialized = 0;
}

// 0x0041F360
void Actor::_todo_0041F360(int a2, int a3)
{
  ;
}

// 0x004503C0
void Actor::_todo_004503C0(int a2)
{
  ;
}

// 0x00456EE0
int Actor::ApplyStateArray()
{
  int v2; // esi
  void **p_m_pParticleData; // edi
  int result; // eax

  this->Actor::SaveState();
  v2 = 0;
  p_m_pParticleData = (void **)&this->m_pParticleData;
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
  result = (char *)ReadRegistryString(aSoftwareSoftst_2, ValueName, (char *)Data);
  if ( (_BYTE)result )
  {
    result = (char *)ReadRegistryString(aSoftwareSoftst_2, "MOVIE_B", (char *)v8);
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

// 0x004B7260
// Microsoft VisualC 2-14/net runtime
void Actor::_todo_004B7260(int a2)
{
  sub_4B70B0((Actor *)&dword_DE6F70);
}

// 0x004B72C0
// attributes: thunk
void Actor::_todo_004B72C0()
{
  int v1; // [esp+0x4] [ebp+0x4]

  this->Actor::_todo_004B72D0(v1);
}

// 0x004B72D0
void Actor::_todo_004B72D0(int a2)
{
  flt_DE71F8 = 12.0 + 12.0;
}

// 0x004B7330
void Actor::_todo_004B7330(int a2)
{
  (((gbChain1DNode *)this))->gbChain1DNode::Process();
}

// 0x004B73E0
void Actor::_todo_004B73E0(int a2)
{
  ;
}

// 0x004B7490
void Actor::_todo_004B7490(int a2)
{
  flt_DE7480 = 12.0 + 12.0;
}

// 0x004B8030
void Actor::_todo_004B8030(int a2)
{
  Actor *v2; // edi
  gbRenderInfoObj *v3; // esi
  char *m_pRoleParam3; // ecx
  gbMatrix4 *Top; // eax
  const gbVec3D *v6; // [esp+0x0] [ebp-0x20]
  gbVec3D *v7; // [esp+0x4] [ebp-0x1C]
v3 = (((gbSceneGraph *)gfxMgr->pSceneGraph))->gbSceneGraph::NewOneRenderObj((gbVisNode *)this);
  v2 = (Actor *)((char *)this + 96);
  v3->Flags = 0;
  v3->Param = 0;
  m_pRoleParam3 = (char *)this->m_pRoleParam3;
  v3->pTexArray = (gbTextureArray *)this;
  v3->pEffect = (gbRenderEffect *)m_pRoleParam3;
  Top = (((gbMatrixStack *)gfxMgr->pMatrixStack[1]))->gbMatrixStack::GetTop();
  (((gbMatrix4 *)Top))->gbMatrix4::Transform(v6, v7);
  v3->Priority = 1;
  v3->Z = 0.0f;
}

// 0x004D3160
void Actor::_todo_004D3160(int a2)
{
  float m_fMoveSpeed; // eax
  int v4; // ebx
  int v5; // edi

  m_fMoveSpeed = this->m_fMoveSpeed;
  if ( m_fMoveSpeed != 0.0f || LODWORD(this->m_fMoveRange) )
  {
    v4 = 0;
    if ( SLODWORD(m_fMoveSpeed) > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(&this->m_actarray_capacity_end->m_actarray_type + v5));
        ++v4;
        *(_DWORD *)(&this->m_actarray_capacity_end->m_actarray_type + v5) = 0;
        v5 += 152;
      }
      while ( v4 < SLODWORD(this->m_fMoveSpeed) );
    }
    operator delete(this->m_actarray_capacity_end);
    this->m_actarray_capacity_end = ((Actor *)0);
    this->m_fMoveSpeed = 0.0f;
    this->m_fMoveRange = 0.0f;
  }
  if ( (a2 & 1) != 0 )
    operator delete(this);
}

// 0x0050ACF0
unsigned int Actor::GetAnimDurationByIndex(int nVal)
{
  unsigned int result; // eax

  result = nVal;
  if ( nVal > 0 )
  {
    sprintf(byte_17AB808, "z%02d", nVal);
    return (((Actor *)*(Actor **)&this->m_szTexture[12]))->Actor::GetAnimDuration((int)byte_17AB808);
  }
  return result;
}

// 0x00531260
// positive sp value has been detected, the output may be wrong!
void Actor::UpdateFrame(float arg0)
{
  unsigned int m_nAnimCounter; // eax
  float *v4; // eax
  float v5; // st7
  float *p_m_fDirX; // ebx
  float v7; // st6
  float v8; // ecx
  float v9; // st7
  float v10; // st7
  float m_fDirZ; // ecx
  float v12; // st7
  float v13; // ecx
  float v14; // st7
  float v15; // edx
  float v16; // ecx
  float v17; // st7
  float v18; // st7
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
  float v30; // st7
  gbOBBox *SlotA; // eax
  float v32; // st7
  int v33; // ecx
  bool v34; // zf
  float v35; // st7
  gbOBBox *v36; // eax
  Actor *v37; // ecx
  int v38; // esi
  gbOBBox *SlotB; // eax
  int TableEntry; // eax
  unsigned int v41; // eax
  DWORD v42; // eax
  DWORD v43; // eax
  unsigned int v44; // ecx
  float v45; // edx
  int v46; // eax
  int v47; // [esp-0x4] [ebp-A0h]
  int v48; // [esp-0x4] [ebp-A0h]
  int v49; // [esp+0x8] [ebp-0x94]
  int v50; // [esp+0x14] [ebp-0x88]
  float z; // [esp+0x1C] [ebp-0x80] BYREF
  gbVec3D v52; // [esp+0x20] [ebp-0x7C] BYREF
  int p_DWORD; // [esp+0x2C] [ebp-0x70]
  float v54; // [esp+0x30] [ebp-0x6C]
  float v55; // [esp+0x34] [ebp-0x68]
  float v56; // [esp+0x38] [ebp-0x64]
  float v57; // [esp+0x3C] [ebp-0x60]
  float m_fDirX; // [esp+0x40] [ebp-0x5C]
  float m_fDirY; // [esp+0x44] [ebp-0x58]
  float v60[19]; // [esp+0x48] [ebp-0x54] BYREF
  float retaddr; // [esp+0x9C] [ebp+0x0]

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
      todo_00530F70(this, SLODWORD(retaddr));
      break;
    case 2:
      (((RoleAtt *)this))->RoleAtt::ApplySpeedFactor(retaddr) /* [ROWTABLE] */;
      break;
    case 3:
      (((RoleAtt *)this))->RoleAtt::UpdateTimedBuff(retaddr) /* [ROWTABLE] */;
      break;
  }
  if ( this->m_bStateFlag )
  {
    (((Actor *)*(Actor **)&this->m_actarray_type))->Actor::QueryState(v49);
    return;
  }
  v4 = (float *)(((ArcSceneMonster *)&this->m_dwMatMsg[6]))->ArcSceneMonster::CheckDistance(this->m_fDistAccum);
  if ( !v4 )
  {
    this->m_bDirFlag = 0;
    (((s_RoleState *)this->m_pRoleState))->s_RoleState::CopyRoleData(0, 0);
    this->m_bStateFlag = 1;
    this->Actor::UpdateAnimState(0);
    return;
  }
  v5 = *v4 - this->m_fDirX;
  p_m_fDirX = (float *)&this->m_fDirX;
  m_fDirY = v4[1] - this->m_fDirY;
  v7 = v4[2] - this->m_fDirZ;
  this->m_fNormY = m_fDirY;
  v60[0] = v7;
  v8 = v60[0];
  this->m_fNormX = v5;
  this->m_fNormZ = v8;
  (((gbVec3D *)&this->m_fNormX))->gbVec3D::Normalize();
  v9 = retaddr * this->m_fSpeed;
  *(_DWORD *)&this->m_bChangedMat = *(_DWORD *)&this->m_curact[11];
  *(_DWORD *)&this->m_curact[3] = *(_DWORD *)&this->m_curact[15];
  v10 = v9 * this->m_fNormX;
  *(_DWORD *)&this->m_curact[7] = *(_DWORD *)&this->m_curact[19];
  *(float *)&this->m_curact[11] = this->m_fDirX;
  m_fDirZ = this->m_fDirZ;
  *(float *)&this->m_curact[15] = this->m_fDirY;
  *(float *)&this->m_curact[19] = m_fDirZ;
  v12 = v10 + this->m_fDirX;
  v55 = *(float *)&this->m_curact[11];
  v13 = *(float *)&this->m_curact[15];
  this->m_fDirX = v12;
  v14 = this->m_fNormY * this->m_fSpeed;
  v15 = *(float *)&this->m_curact[19];
  v56 = v13;
  v57 = v15;
  this->m_fDirY = v14 * retaddr + this->m_fDirY;
  this->m_fDirZ = this->m_fNormZ * this->m_fSpeed * retaddr + this->m_fDirZ;
  m_fDirX = this->m_fDirX;
  v16 = this->m_fDirZ;
  m_fDirY = this->m_fDirY;
  v60[0] = v16;
  this->m_fDistAccum = sqrt(
                         (v56 - m_fDirY) * (v56 - m_fDirY)
                       + (v57 - v16) * (v57 - v16)
                       + (v55 - m_fDirX) * (v55 - m_fDirX))
                     + this->m_fDistAccum;
  m_fDirX = this->m_fDirX - *(float *)&this->m_curact[11];
  v17 = this->m_fDirY - *(float *)&this->m_curact[15];
  v52.z = m_fDirX;
  m_fDirY = v17;
  v18 = this->m_fDirZ - *(float *)&this->m_curact[19];
  p_DWORD = LODWORD(m_fDirY);
  v60[0] = v18;
  v54 = v60[0];
  (((gbVec3D *)&v52.z))->gbVec3D::Normalize();
  v52.y = v54;
  z = v52.z;
  LODWORD(v52.x) = p_DWORD;
  (((gbVec3D *)&z))->gbVec3D::Normalize();
  if ( (byte_17AFB04 & 1) == 0 )
  {
    dword_17AFAF8 = 0;
    LOBYTE(byte_17AFB04) = byte_17AFB04 | 1;
    dword_17AFAFC = 0;
    dword_17AFB00 = 1065353216;
    atexit(nullsub_72);
  }
  v19 = acos(v52.y * *(float *)&dword_17AFB00 + v52.x * *(float *)&dword_17AFAFC + *(float *)&dword_17AFAF8 * z);
  this->m_fAngleDeg = v19;
  if ( z < 0.0f )
    this->m_fAngleDeg = 6.2831854820251465f - v19;
  this->m_fAngleDeg = this->m_fAngleDeg * 57.295780181884766f;
  if ( (byte_17AFB04 & 2) == 0 )
  {
    dword_17AFAE8 = 0;
    LOBYTE(byte_17AFB04) = byte_17AFB04 | 2;
    dword_17AFAEC = 1065353216;
    dword_17AFAF0 = 0;
    atexit(nullsub_71);
  }
  *(float *)&this->m_InnerActor = acos(
                                    v52.y * *(float *)&dword_17AFAF0
                                  + v52.x * *(float *)&dword_17AFAEC
                                  + *(float *)&dword_17AFAE8 * z)
                                * 57.29578;
  m_fDirX = *p_m_fDirX;
  m_fDirY = this->m_fDirY + 200.0f;
  v60[0] = this->m_fDirZ;
  (((RoleCameraCtrl *)this->m_dwMatMsg[9]))->RoleCameraCtrl::ComputeViewVector(SLODWORD(m_fDirX), SLODWORD(m_fDirY), SLODWORD(v60[0]));
  m_fDirX = *p_m_fDirX;
  v20 = 0;
  m_fDirY = this->m_fDirY + 200.0f;
  v60[0] = this->m_fDirZ;
  (((RoleCameraCtrl *)this->m_dwMatMsg[9]))->RoleCameraCtrl::SetViewPosition(SLODWORD(m_fDirX), SLODWORD(m_fDirY), SLODWORD(v60[0]), 0);
  (((UIScene *)this->m_dwMatMsg[9]))->UIScene::LoadMapData(*((_DWORD *)&this->m_bDirFlag + 6));
  *(float *)&v47 = *((float *)&this->m_bDirFlag + 7) - (this->m_fAngleDeg - 90.0);
  (((UIBigMap *)this->m_dwMatMsg[9]))->UIBigMap::SetBounds(v47, *((_DWORD *)&this->m_bDirFlag + 8), 0);
  m_nUpdateMode = this->m_nUpdateMode;
  if ( m_nUpdateMode != 1 && m_nUpdateMode != 3 && m_nUpdateMode != 2 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
  {
    v22 = this->m_fDirY;
    *(&this->m_nUpdateMode + 6) = *(&this->m_nUpdateMode + 7);
    *((_BYTE *)&this->m_nUpdateMode + 15) = 0;
    *(float *)&this[1].m_actarray_type = v22;
    *((_BYTE *)&this->m_nUpdateMode + 14) = 1;
    *(&this->m_nUpdateMode + 5) = 0;
    UIAnimateCtrlEX_SwapBuffer(2);
    ::SetMaterialName(*(Actor **)&this->m_actarray_type, (void *)off_5F50C0, 0);
  }
  if ( *(&this->m_nUpdateMode + 1) == 2 )
  {
    if ( (((Object3D *)*(Object3D **)&this->m_actarray_type))->Object3D::GetVisNode() )
    {
      ::SetMaterialName(*(Actor **)&this->m_actarray_type, (void *)off_5F50C4, 0);
      *(&this->m_nUpdateMode + 1) = 0;
    }
    if ( *(&this->m_nUpdateMode + 1) == 2 && (((Object3D *)*(Object3D **)&this->m_actarray_type))->Object3D::GetVisNode() )
    {
      *(&this->m_nUpdateMode + 1) = 0;
      ::SetMaterialName(*(Actor **)&this->m_actarray_type, (void *)lpString2, 0);
    }
  }
  if ( !*(&this->m_nUpdateMode + 1) && (((Object3D *)*(Object3D **)&this->m_actarray_type))->Object3D::GetVisNode() )
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
        ::SetMaterialName(*(Actor **)&this->m_actarray_type, (void *)lpString2, 0);
        goto LABEL_45;
      }
      v28 = v27 - 1;
      if ( !v28 )
      {
        ::SetMaterialName(*(Actor **)&this->m_actarray_type, (void *)off_5F50BC, 0);
        goto LABEL_45;
      }
      if ( v28 != 1 )
        goto LABEL_45;
      v29 = (CHAR *)off_5F50C4;
    }
    ::SetMaterialName(*(Actor **)&this->m_actarray_type, v29, 0);
  }
LABEL_45:
  if ( !this->m_nUpdateMode )
  {
    if ( this->m_bDirFlag )
    {
      if ( g_Input.KeyInfo[0].PressTime == 1 )
      {
        v30 = this->m_fSpeed + 0.20000000298023224f;
        this->m_fSpeed = v30;
        if ( v30 >= *(&this->m_fSpeed + 3) )
          this->m_fSpeed = *(&this->m_fSpeed + 3);
      }
    }
  }
  if ( *(&this->m_nUpdateMode + 1) == 1 )
  {
    if ( (((Object3D *)*(Object3D **)&this->m_actarray_type))->Object3D::GetVisNode() )
    {
      *(&this->m_nUpdateMode + 1) = 0;
      ::SetMaterialName(*(Actor **)&this->m_actarray_type, (void *)lpString2, 0);
    }
    (((Actor *)*(Actor **)&this->m_actarray_type))->Actor::PlayAction((int)&this->m_obbox);
    this->m_fAnimDelta = this->m_fAnimDelta + *p_m_fDirX;
    *(float *)this->m_dwMatMsg = this->m_fDirY + *(float *)this->m_dwMatMsg;
    *(float *)&this->m_dwMatMsg[1] = this->m_fDirZ + *(float *)&this->m_dwMatMsg[1];
    while ( 1 )
    {
      SlotA = (gbOBBox *)(((CCBFiveNimbusWindow *)this->m_pRoleState))->CCBFiveNimbusWindow::GetSlotA(v20);
      if ( (((gbOBBox *)&this->m_obbox))->gbOBBox::IsColOBB(SlotA) )
        break;
      if ( ++v20 >= 6 )
        goto LABEL_62;
    }
    qmemcpy(
      v60,
      (const void *)(((CCBFiveNimbusWindow *)this->m_pRoleState))->CCBFiveNimbusWindow::GetSlotA(v20),
      sizeof(v60));
    v32 = v60[16];
    if ( v60[17] > (double)v60[16] )
      v32 = v60[17];
    if ( v60[18] > v32 )
      v32 = v60[18];
    *(float *)&v50 = v32 + v32 + this->m_fDistAccum;
    this->m_fDistAccum = *(float *)&v50;
    (((RoleAtt *)this))->RoleAtt::InterpolateStats(v50) /* [ROWTABLE] */;
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
      (((Actor *)*(Actor **)&this->m_actarray_type))->Actor::PlayAction((int)&this->m_obbox);
      v34 = this->m_nUpdateMode == 2;
      this->m_fAnimDelta = this->m_fAnimDelta + *p_m_fDirX;
      if ( v34 )
        v35 = *(float *)&this[1].m_actarray_type;
      else
        v35 = this->m_fDirY;
      *(float *)this->m_dwMatMsg = v35 + *(float *)this->m_dwMatMsg;
      *(float *)&this->m_dwMatMsg[1] = this->m_fDirZ + *(float *)&this->m_dwMatMsg[1];
      while ( 1 )
      {
        v36 = (gbOBBox *)(((CCBFiveNimbusWindow *)this->m_pRoleState))->CCBFiveNimbusWindow::GetSlotA(v20);
        if ( (((gbOBBox *)&this->m_obbox))->gbOBBox::IsColOBB(v36) )
          break;
        if ( ++v20 >= 6 )
          goto LABEL_76;
      }
      UIAnimateCtrlEX_SwapBuffer(1);
      v37 = (Actor *)(*(Actor **)&this->m_actarray_type);
      *((_BYTE *)&this->m_nUpdateMode + 13) = 0;
      *((_BYTE *)&this->m_nUpdateMode + 12) = 1;
      ::SetMaterialName(v37, (void *)off_5F50C8, 1);
LABEL_76:
      v38 = 0;
      while ( 1 )
      {
        SlotB = (gbOBBox *)(((CCBFiveNimbusWindow *)this->m_pRoleState))->CCBFiveNimbusWindow::GetSlotB(v38);
        if ( (((gbOBBox *)&this->m_obbox))->gbOBBox::IsColOBB(SlotB) )
          break;
        if ( ++v38 >= 3 )
          goto LABEL_82;
      }
      LODWORD(v52.z) = 0xFFFF;
      p_DWORD = 0;
      v54 = 0.0f;
      LODWORD(v52.z) = GetTableEntry(v38);
      v54 = _pal3_coerce_f32((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(SLODWORD(v52.z)));
      p_DWORD = 1;
      if ( !(((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex((int *)&v52.z) )
      {
        this->m_pRoleState[v38 + 3328] = 0;
        TableEntry = GetTableEntry(v38);
        (((CCBFiveNimbusWindow *)this))->CCBFiveNimbusWindow::ApplySelection(TableEntry) /* [ROWTABLE] */;
      }
    }
  }
LABEL_82:
  if ( IsWithinBoundRadius(this) && this->m_bDirFlag )
  {
    this->m_bStateFlag = 1;
    this->Actor::UpdateAnimState(1);
  }
  (((Actor *)*(Actor **)&this->m_actarray_type))->Actor::QueryState(v48);
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
        v45 = *((float *)&this->m_bDirFlag + 1);
        *(&this->m_bDirFlag + 1) = 0;
        v46 = (((ArcSceneMonster *)&this->m_dwMatMsg[6]))->ArcSceneMonster::ValidateRange(v45);
        (((s_RoleState *)this->m_pRoleState))->s_RoleState::CopyRoleData(v46, 1);
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
    (((RoleSystem *)this->m_dwMatMsg[10]))->RoleSystem::StartBlinkUI();
  }
}

// 0x00532A20
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
void Actor::_todo_00532A20()
{
  todo_00532A30();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00536220
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
int Actor::GetDefaultFOV_thunk()
{
  return this->Actor::SetDefaultFOV();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00536230
int Actor::SetDefaultFOV()
{
  int result; // eax

  result = 1094713344;
  dword_17B129C = 1094713344;
  return result;
}

// 0x00536240
// attributes: thunk
int Actor::GetDefaultDist_thunk()
{
  int result; // eax

  this->Actor::SetDefaultDist();
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
  (((UIFrameContainer *)&this[4].m_fRoleParam2))->UIFrameContainer::~UIFrameContainer();
  (((UIButton *)&this[3].m_fDirY))->UIButton::~UIButton();
  (((UIRoleDialog *)&this[2].m_nRoleState0))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)&this->m_nHandleEvent))->UIRoleDialog::~UIRoleDialog();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x00536A40
#pragma inline_depth(0)
#pragma auto_inline(off)
// attributes: thunk
int Actor::GetDefaultFOV2_thunk()
{
  return this->Actor::SetDefaultFOV2();
}
#pragma auto_inline(on)
#pragma inline_depth()

// 0x00536A50
int Actor::SetDefaultFOV2()
{
  int result; // eax

  result = 1094713344;
  dword_17B154C = 1094713344;
  return result;
}

// 0x00536A60
// attributes: thunk
int Actor::GetDefaultDist2_thunk()
{
  int result; // eax

  this->Actor::SetDefaultDist2();
  return result;
}

// 0x00536A70
void Actor::SetDefaultDist2()
{
  flt_17B1548 = 12.0 + 12.0;
}

// 0x00536C50
int Actor::CompareActionName(int actionIdx, int nVal)
{
  if ( !strcmp((&off_570904)[actionIdx], (const char *)this->m_dwMatMsg) )
    return 1;
  else
    return this->Actor::SetMaterialName((void *)(&off_570904)[actionIdx], nVal);
}

// 0x00536CC0
unsigned int Actor::GetAnimDuration(int animId)
{
  return (((gbActor *)this->m_pact))->gbActor::GetActionDuration((char *)animId);
}

// 0x00536CE0
void Actor::EnableTransition(int nVal, int nVal2)
{
  (((gbActor *)this->m_pact))->gbActor::EnableActionTransMtl((char *)nVal, nVal2);
}

// 0x00536D00
void Actor::SetTimeScale(float scale)
{
  (((gbVisNode *)this->m_pact))->gbVisNode::SetTimeScale(scale);
}

// 0x00536FB0
int Actor::QueryState(int nVal1)
{
  return (*(int ( **)(gbActor *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pact) + 20))(this->m_pact, nVal1);
}

// 0x00536FC0
int Actor::DispatchAction(int actionId)
{
  return (*(int ( **)(gbActor *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pact) + 16))(this->m_pact, actionId);
}

// 0x00536FD0
int Actor::PlayAction(int actionId)
{
  return (*(int ( **)(gbActorDef *, int, gbActor *))(*(_DWORD *)((gbRefObject *)this->m_pact->pBody) + 28))(
           this->m_pact->pBody,
           actionId,
           this->m_pact);
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

// 0x005372B0
int Actor::GetArrayCount()
{
  Actor *m_actarray_begin; // edx

  m_actarray_begin = (Actor *)this->m_actarray_begin;
  if ( m_actarray_begin )
    return ((char *)this->m_actarray_end - (char *)m_actarray_begin) >> 2;
  else
    return 0;
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
        *(_DWORD *)result = (unsigned long)*v5;
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
  int result; // eax

  result = nVal;
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
  return result;
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
  result = (int)fopen(Buffer, aRb);
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

// 0x00537A90
FILE * Actor::DoSceneTransition(double pData, int nVal)
{
  int v3; // edi
  FILE *result; // eax
  FILE *v5; // ebp
  Actor **p_pTargetActor; // esi
  int v7; // edi
  _BYTE *v8; // edx
  int v9; // esi
  void *v10; // edi
  int v11; // ecx
  unsigned __int8 **v12; // eax
  unsigned __int8 *v13; // edx
  int v14; // esi
  int *p_m_nScreenFlags; // ebx
  Actor *v16; // esi
  int v17; // ecx
  CScreenMode *Instance; // eax
  gbVec3D *p_m_lastFrom; // ebx
  float m_fCtrlYaw; // edi
  float m_yaw; // ecx
  float y; // eax
  Actor *v23; // esi
  tagActionCommand *p_pCmd; // edi
  scAsmDecoder *v25; // ecx
  PAL3 *v26; // ecx
  RenderTarget3 *v27; // eax
  PAL3 *v28; // ecx
  ScreenEffectMgr *Instance_fd20; // eax
  CScreenMode *v30; // eax
  gbAudioManager *AudioManager; // eax
  Role *v32; // edi
  int v33; // esi
  int *v34; // ebx
  RoleSystem *RoleDataOffset; // eax
  int v36; // esi
  Scene *v37; // eax
  Actor *m_roles; // edi
  int v39; // [esp+0x0] [ebp-0x280A0]
  Actor *v40; // [esp+0x10] [ebp-0x28090] BYREF
  float v41; // [esp+0x14] [ebp-0x2808C] BYREF
  float v42; // [esp+0x18] [ebp-0x28088]
  float v43; // [esp+0x1C] [ebp-0x28084]
  tagActionCommand v44; // [esp+0x20] [ebp-0x28080] BYREF
  char sceneNames[32]; // [esp+0x3C] [ebp-0x28064] BYREF
  char pszBuf[100]; // [esp+0x5C] [ebp-0x28044] BYREF
  _DWORD pSrc[7]; // [esp+C0h] [ebp-0x27FE0] BYREF
  tagActionCommand pCmd; // [esp+DCh] [ebp-0x27FC4] BYREF
  unsigned __int8 String2[36]; // [esp+0x168] [ebp-0x27F38] BYREF
  int v50; // [esp+0x18C] [ebp-0x27F14]
  float v51; // [esp+0x190] [ebp-0x27F10]
  int v52; // [esp+0x194] [ebp-0x27F0C]
  int v53; // [esp+0x198] [ebp-0x27F08]
  int v54; // [esp+0x19C] [ebp-0x27F04]
  unsigned int v55; // [esp+0x1A0] [ebp-0x27F00]
  int v56; // [esp+0x1A4] [ebp-0x27EFC]
  int v57; // [esp+0x1A8] [ebp-0x27EF8]
  char v58; // [esp+0x1AC] [ebp-0x27EF4]
  int v59; // [esp+0x1B0] [ebp-0x27EF0]
  char v60; // [esp+0x1B4] [ebp-0x27EEC]
  unsigned __int8 v61; // [esp+0x1B5] [ebp-0x27EEB]
  char v62[20]; // [esp+0x1B6] [ebp-0x27EEA] BYREF
  int v63; // [esp+0x1CA] [ebp-0x27ED6]
  int pnCount[44]; // [esp+0x20C] [ebp-0x27E94] BYREF
  char v65; // [esp+0x2BC] [ebp-0x27DE4] BYREF
  int v66; // [esp+0x2C8] [ebp-0x27DD8]
  char Buffer[260]; // [esp+0x2E8] [ebp-0x27DB8] BYREF
  int v68; // [esp+0x3EC] [ebp-0x27CB4] BYREF
  int v69; // [esp+0x3F0] [ebp-0x27CB0]
  _DWORD v70[3]; // [esp+0x3F4] [ebp-0x27CAC]
  __int16 v71; // [esp+0x400] [ebp-0x27CA0]
  int v72; // [esp+0x402] [ebp-0x27C9E]
  char v73; // [esp+0x406] [ebp-0x27C9A]
  int v74; // [esp+0x408] [ebp-0x27C98]
  unsigned __int8 v75; // [esp+0x40C] [ebp-0x27C94]
  _BYTE v76[41]; // [esp+0x40D] [ebp-0x27C93] BYREF
  __int16 v77; // [esp+0x436] [ebp-0x27C6A]
  int v78; // [esp+0x438] [ebp-0x27C68]
  int v79; // [esp+0x43C] [ebp-0x27C64]
  int v80; // [esp+0x440] [ebp-0x27C60]
  _BYTE v81[40]; // [esp+0x444] [ebp-0x27C5C]
  int v82; // [esp+0x46C] [ebp-0x27C34]
  _BYTE v83[160]; // [esp+0x470] [ebp-0x27C30] BYREF
  int v84; // [esp+0x510] [ebp-0x27B90]
  _DWORD v85[40466]; // [esp+0x514] [ebp-0x27B8C] BYREF
  char v86; // [esp+0x27D5C] [ebp-0x344]
  int v87; // [esp+0x27D60] [ebp-0x340]
  _BYTE v88[828]; // [esp+0x27D64] [ebp-0x33C] BYREF
sub_407790();
  sprintf(Buffer, "save\\pal%02d.arc", LODWORD(pData));
  result = fopen(Buffer, aRb);
  v5 = (FILE *)result;
  if ( result )
  {
    v39 = v3;
    fread(pnCount, 0xDCu, 1u, result);
    memset(&pSrc[4], 0, 12);
    p_pTargetActor = (Actor **)&pCmd.pTargetActor;
    v7 = 5;
    do
    {
      ((gbVec3D *)p_pTargetActor)->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
      p_pTargetActor += 7;
      --v7;
    }
    while ( v7 );
    v52 = 0;
    v53 = 0;
    v54 = 0;
    fseek(v5, pnCount[38], 0);
    fread(sceneNames, 0x1D0u, 1u, v5);
    fseek(v5, pnCount[39], 0);
    LoadGameState(v5);
    ::LoadActions(v40, v5, pnCount);
    fseek(v5, pnCount[42], 0);
    v41 = 1.0f;
    v42 = 1.0f;
    v43 = 1.0f;
    fread(&v41, 0xCu, 1u, v5);
    fseek(v5, pnCount[43], 0);
    v68 = 0;
    v69 = 0;
    memset(v85, 0, 12);
    v70[0] = 1;
    ::InitAnimSequence((Actor *)&v85[3]);
    ArraySort((int)&v85[58], 808, 200, (int)ClearModelFlag);
    v85[40465] = 0;
    v85[40462] = 1;
    v85[40463] = 1;
    v85[40464] = 1;
    v8 = v88;
    v9 = 11;
    do
    {
      v10 = (void *)v8;
      v8 += 52;
      --v9;
      memset(v10, 0, 0x2Cu);
    }
    while ( v9 );
    fread(&v68, 0x27CB4u, 1u, v5);
    g_ScriptSystemData.m_nScriptFlag = v70[0];
    g_ScriptSystemData.m_nScriptCounter1 = v69;
    g_nRoleParam = v70[1];
    LOBYTE(g_nActor_DE5F9C) = v73;
    dword_C10CC4 = v74;
    g_ScriptSystemData.m_nScriptCounter0 = v68;
    LOWORD(g_nActor_DE5FA8) = v71;
    g_nActorState = v72;
    LOBYTE(g_dwUISettings) = v76[40];
    g_nRoleState = v70[2];
    qmemcpy(g_SaveSlotFlags, v76, sizeof(g_SaveSlotFlags));
    g_bUIWnd_DE625A = v75;
    *(_WORD *)((char *)&g_dwUISettings + 1) = v77;
    g_nUpdateInterval = v80;
    g_bRoleFlag1 = v78 == 1;
    g_bRoleFlag2 = v79 == 1;
    v11 = 0;
    v12 = (unsigned __int8 **)&g_pSceneTransitionBegin;
    do
    {
      ++v12;
      v13 = (unsigned __int8 *)(unsigned __int8)v81[v11++];
      *(v12 - 1) = v13;
    }
    while ( (int)v12 < (int)&g_pSceneTransitionEnd );
    qmemcpy(g_fCamRoleParams, v83, sizeof(g_fCamRoleParams));
    g_nFiveNimbusCount = v84;
    qmemcpy(&g_SceneTransitionBuffer, v85, 0x27848u);
    g_nWolfIndex = v82;
    LOBYTE(byte_D92785) = v86;
    dword_C10CD4 = v87;
    qmemcpy(g_pCBSystem->m_Player, v88, sizeof(g_pCBSystem->m_Player));
    g_fGameTimer = *(float *)&pnCount[18];
    CScreenMode::GetInstance()->m_bRenderAlt = v60;
    v14 = v61;
    CScreenMode::GetInstance()->m_nFadeState = v14;
    p_m_nScreenFlags = (int *)&CScreenMode::GetInstance()->m_nScreenFlags;
    v16 = (Actor *)strlen((const char *)v62);
    v40 = (Actor *)v16;
    if ( (((SceneObj *)p_m_nScreenFlags))->SceneObj::UpdateAutoDelete((unsigned int)v16) )
    {
      qmemcpy((void *)p_m_nScreenFlags[1], v62, (unsigned int)v16);
      v17 = (unsigned long)p_m_nScreenFlags[1];
      p_m_nScreenFlags[2] = (int)v16;
      *(&v16->m_actarray_type + v17) = 0;
    }
    if ( CScreenMode::GetInstance()->m_bRenderAlt )
    {
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioFadeOut();
    }
    LoadScene(sceneNames, pszBuf, 1);
    p_m_lastFrom = (gbVec3D *)&g_pCameraCtrl->m_lastFrom;
    if ( !LODWORD(g_pCameraCtrl->m_nextYAW)
      || (m_fCtrlYaw = g_pCameraCtrl->m_fCtrlYaw, m_yaw = g_pCameraCtrl->m_yaw, LODWORD(m_fCtrlYaw) == LODWORD(m_yaw)) )
    {
      (((CameraCtrl *)&g_pCameraCtrl->m_lastFrom))->CameraCtrl::UpdateFOVLerp();
      y = p_m_lastFrom[2].y;
      LODWORD(p_m_lastFrom[2].y) = LODWORD(y) + 28;
      Actor::CopyConstruct_1C((void *)LODWORD(y), pSrc);
    }
    else
    {
      LODWORD(g_pCameraCtrl->m_fCtrlYaw) = LODWORD(m_fCtrlYaw) + 28;
      if ( LODWORD(m_fCtrlYaw) + 28 == LODWORD(m_yaw) )
      {
        Actor::CopyConstruct_1C((void *)LODWORD(m_fCtrlYaw), pSrc);
        (((CameraCtrl *)p_m_lastFrom))->CameraCtrl::UpdateFOVLerp();
      }
      else if ( m_fCtrlYaw != 0.0f )
      {
        qmemcpy((void *)LODWORD(m_fCtrlYaw), pSrc, 0x1Cu);
      }
    }
    ++LODWORD(p_m_lastFrom[3].z);
    RoleCamera_PushState(v39);
    v23 = (Actor *)(&g_RoleSlotBuf.dword_17AA450 + 150);
    p_pCmd = (tagActionCommand *)&pCmd;
    do
    {
      (((Actor *)v23))->Actor::ExecuteAction(p_pCmd);
      v23 = (Actor *)((char *)v23 + 8704);
      ++p_pCmd;
    }
    while ( (int)v23 < (int)&g_RoleSystemArrayEnd );
    if ( _strcmpi(unk_C0A360.m_nAnimState, (const char *)&String2[1]) )
    {
      LoadActionSequences(&unk_C0A608, (const char *)&String2[1], 0);
      strcpy(unk_C0A360.m_nAnimState, (const char *)&String2[1]);
      (((RoleSystem *)&unk_C0A360))->RoleSystem::UpdateTransform();
    }
    (((scAsmDecoder *)v25))->scAsmDecoder::Execute(String2[0], 0);
    g_nScriptEventParam = v50;
    g_fScriptEventParam2 = v51;
    g_nScriptRolePosX = v52;
    g_nScriptRolePosY = v53;
    v26 = (PAL3 *)v56;
    g_nScriptRolePosZ = v54;
    g_nCurrentEventId = v55;
    g_nActor_BFDBA8 = v56;
    LOBYTE(v26) = v58;
    g_nActor_BFDBAC = v57;
    dword_C10CD0 = v59;
    byte_C10CC1 = v58;
    v27 = (((PAL3 *)v26))->PAL3::GetInstance();
    *(_BYTE *)v27 = v62[16];
    Instance_fd20 = (((PAL3 *)v28))->PAL3::GetInstance_fd20();
    LOBYTE(Instance_fd20->m_pVtable) = v62[17];
    LOBYTE(byte_BFDA40) = v62[19];
    LOBYTE(byte_BFDA41) = v62[18];
    (((PalScript *)(unsigned __int8)v63))->PalScript::InitParticleSlht((PalScript *)(unsigned __int8)v63);
    v30 = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)v30))->CScreenMode::GetAudioManager();
    if ( AudioManager )
    {
      AudioManager->S_2DMasterVol = v41;
      AudioManager->S_3DMasterVol = v42;
      (((gbAudioManager *)AudioManager))->gbAudioManager::SetMusicMasterVolume(v43);
    }
    v32 = (Role *)&UISceneUpdate()->m_roles[50];
    v33 = 0;
    if ( *(_DWORD *)((Object *)v32) > 0 )
    {
      v34 = (int *)&v65;
      do
      {
        if ( *v34 )
        {
          fseek(v5, *v34, 0);
          RoleDataOffset = (RoleSystem *)GetRoleDataOffset(v33);
          (((RoleSystem *)RoleDataOffset))->RoleSystem::ClearPathData(v5);
        }
        ++v33;
        ++v34;
      }
      while ( v33 < *(_DWORD *)((Object *)v32) );
    }
    v36 = 0;
    if ( v66 )
    {
      fseek(v5, v66, 0);
      v40 = 0;
      fread(&v40, 4u, 1u, v5);
      v37 = UISceneUpdate();
      memset(&v44.pTargetActor, 0, 12);
      if ( (int)v40 > 0 )
      {
        m_roles = (Actor *)v37->m_roles;
        do
        {
          fread(&v44, 0x1Cu, 1u, v5);
          (((Actor *)m_roles))->Actor::ExecuteAction(&v44);
          ++v36;
          m_roles = (Actor *)((char *)m_roles + 8704);
        }
        while ( v36 < (int)v40 );
      }
    }
    fclose(v5);
    return (FILE *)1;
  }
  return result;
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
  _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  BOOL result; // eax
  Scene *v6; // ebx
  FILE *v7; // ebp
  _DWORD *v8; // eax
  int v9; // ecx
  RoleSystem *v10; // esi
  float *v11; // edi
  float v12; // edx
  gbVec3D *p_m_lastFrom; // esi
  float z; // eax
  float v15; // eax
  const char *m_nTodo_0C; // eax
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
  RoleSystem *m_roles; // edi
  int v33; // [esp-0x10] [ebp-0x282C0]
  int m_nTodo_e0e0; // [esp+0x0] [ebp-0x282B0] BYREF
  Actor *v35; // [esp+0x4] [ebp-0x282AC]
  _DWORD Buffer[2]; // [esp+0x8] [ebp-0x282A8] BYREF
  float Buffer_8; // [esp+0x10] [ebp-0x282A0]
  int Buffer_12; // [esp+0x14] [ebp-0x2829C]
  float Buffer_16[7]; // [esp+0x18] [ebp-0x28298] BYREF
  _DWORD Buffer_44[116]; // [esp+0x34] [ebp-0x2827C] BYREF
  int Buffer_508[55]; // [esp+0x204] [ebp-0x280AC] BYREF
  TxtFile Buffer_728; // [esp+0x2E0] [ebp-0x27FD0] BYREF
  char Buffer_1252[260]; // [esp+0x4EC] [ebp-0x27DC4] BYREF
  int Buffer_1512; // [esp+0x5F0] [ebp-0x27CC0] BYREF
  int Buffer_1516; // [esp+0x5F4] [ebp-0x27CBC]
  int Buffer_1520; // [esp+0x5F8] [ebp-0x27CB8]
  int Buffer_1524; // [esp+0x5FC] [ebp-0x27CB4]
  int Buffer_1528; // [esp+0x600] [ebp-0x27CB0]
  __int16 Buffer_1532; // [esp+0x604] [ebp-0x27CAC]
  int Buffer_1534; // [esp+0x606] [ebp-0x27CAA]
  char Buffer_1538; // [esp+0x60A] [ebp-0x27CA6]
  int Buffer_1540; // [esp+0x60C] [ebp-0x27CA4]
  unsigned __int8 Buffer_1544; // [esp+0x610] [ebp-0x27CA0]
  _BYTE Buffer_1545[41]; // [esp+0x611] [ebp-0x27C9F] BYREF
  __int16 Buffer_1586; // [esp+0x63A] [ebp-0x27C76]
  int Buffer_1588; // [esp+0x63C] [ebp-0x27C74]
  int Buffer_1592; // [esp+0x640] [ebp-0x27C70]
  int Buffer_1596; // [esp+0x644] [ebp-0x27C6C]
  _BYTE Buffer_1600[40]; // [esp+0x648] [ebp-0x27C68]
  int Buffer_1640; // [esp+0x670] [ebp-0x27C40]
  _BYTE Buffer_1644[160]; // [esp+0x674] [ebp-0x27C3C] BYREF
  int Buffer_1804; // [esp+0x714] [ebp-0x27B9C]
  _DWORD Buffer_1808[40466]; // [esp+0x718] [ebp-0x27B98] BYREF
  char v64; // [esp+0x27F60] [ebp-0x350]
  int v65; // [esp+0x27F64] [ebp-0x34C]
  _BYTE v66[828]; // [esp+0x27F68] [ebp-0x348] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v67; // [esp+0x282A4] [ebp-0xC]
  void *v68; // [esp+0x282A8] [ebp-0x8]
  int v69; // [esp+0x282AC] [ebp-0x4]

  v69 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v68 = ((void*)0);
  v67 = (_EXCEPTION_REGISTRATION_RECORD *)ExceptionList;
  v4 = alloca(164516);
result = this->Actor::EnsureDirectory();
  if ( result )
  {
    v6 = UISceneUpdate();
    memset(Buffer_508, 0, sizeof(Buffer_508));
    *(float *)&Buffer_508[18] = g_fGameTimer;
    Buffer_508[19] = *(&g_RoleSlotBuf.dword_17AA450 + 148);
    LOBYTE(Buffer_508[20]) = *((_BYTE *)&g_RoleSlotBuf.dword_17AA450 + 596);
    Buffer_508[37] = *(&g_RoleSlotBuf.dword_17AA450 + 147);
    v69 = 0;
    (((PalScript *)&Buffer_728))->PalScript::LoadFromFile("datascript\\SceneName.txt");
    (((PalScript *)&Buffer_728))->PalScript::SetDirectory((char *)v6);
    if ( !(((PalScript *)&Buffer_728))->PalScript::FindSaveStateString((PalScript *)&v6->m_pCapacity[5], (char *)&Buffer_508[20] + 1, (char *)0x40, v2) )
      (((PalScript *)&Buffer_728))->PalScript::FindSaveStateString((PalScript *)&dir[12], (char *)&Buffer_508[20] + 1, (char *)0x40, v33);
    sprintf(Buffer_1252, "save\\pal%02d.arc", nVal);
    v7 = fopen(Buffer_1252, Mode);
    if ( v7 )
    {
      memset(&Buffer_44[37], 0, 12);
      v8 = (_DWORD *)&Buffer_44[43];
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
      memset(Buffer_44, 0, sizeof(Buffer_44));
      qmemcpy(Buffer_44, v6, 0x84u);
      v10 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
      v11 = (float *)&Buffer_44[40];
      do
      {
        (((RoleSystem *)v10))->RoleSystem::ExportRoleData(v11);
        v10 = (RoleSystem *)((char *)v10 + 8704);
        v11 += 7;
      }
      while ( (int)v10 < (int)&g_RoleSystemArrayEnd );
      LOBYTE(Buffer_44[75]) = (_BYTE)dword_C10CC8;
      v12 = g_fScriptEventParam2;
      strcpy((char *)&Buffer_44[75] + 1, unk_C0A360.m_nAnimState);
      *(float *)&Buffer_44[85] = v12;
      Buffer_44[84] = g_nScriptEventParam;
      Buffer_44[86] = g_nScriptRolePosX;
      Buffer_44[87] = g_nScriptRolePosY;
      Buffer_44[88] = g_nScriptRolePosZ;
      Buffer_44[90] = g_nActor_BFDBA8;
      Buffer_44[89] = g_nCurrentEventId;
      LOBYTE(Buffer_44[92]) = (unsigned long)byte_C10CC1;
      Buffer_44[91] = g_nActor_BFDBAC;
      Buffer_44[93] = dword_C10CD0;
      (((RoleSystem *)g_pCameraCtrl))->RoleSystem::AddCameraKeyframe();
      Buffer[0] = LODWORD(g_pCameraCtrl->m_fromVec.z);
      Buffer[1] = LODWORD(g_pCameraCtrl->m_yaw);
      Buffer_8 = g_pCameraCtrl->m_fCtrlYaw;
      Buffer_12 = g_pCameraCtrl->m_dist;
      (((CameraCtrl *)Buffer))->CameraCtrl::SetupCameraArray(-1);
      Buffer_44[33] = *(_DWORD *)LODWORD(Buffer_8);
      Buffer_44[34] = *(_DWORD *)(LODWORD(Buffer_8) + 4);
      Buffer_44[35] = *(_DWORD *)(LODWORD(Buffer_8) + 8);
      Buffer_44[36] = *(_DWORD *)(LODWORD(Buffer_8) + 12);
      Buffer_44[37] = *(_DWORD *)(LODWORD(Buffer_8) + 16);
      Buffer_44[38] = *(_DWORD *)(LODWORD(Buffer_8) + 20);
      Buffer_44[39] = *(_DWORD *)(LODWORD(Buffer_8) + 24);
      p_m_lastFrom = (gbVec3D *)&g_pCameraCtrl->m_lastFrom;
      if ( LODWORD(g_pCameraCtrl->m_fCtrlYaw) == LODWORD(g_pCameraCtrl->m_fromVec.z) )
        (((CameraCtrl *)&g_pCameraCtrl->m_lastFrom))->CameraCtrl::PopState();
      z = p_m_lastFrom[3].z;
      if ( z != 0.0f )
        LODWORD(p_m_lastFrom[2].y) -= 28;
      LODWORD(v15) = LODWORD(z) - 1;
      p_m_lastFrom[3].z = v15;
      if ( v15 == 0.0f )
        (((CameraCtrl *)p_m_lastFrom))->CameraCtrl::PopState();
      LOBYTE(Buffer_44[94]) = (unsigned long)CScreenMode::GetInstance()->m_bRenderAlt;
      BYTE1(Buffer_44[94]) = (unsigned long)CScreenMode::GetInstance()->m_nFadeState;
      m_nTodo_0C = (const char *)CScreenMode::GetInstance()->m_nTodo_0C;
      if ( !m_nTodo_0C )
        m_nTodo_0C = (const char *)&g_bActorFlag;
      strncpy((char *)&Buffer_44[94] + 2, m_nTodo_0C, 0x10u);
      BYTE2(Buffer_44[98]) = *(_BYTE *)(((PAL3 *)v17))->PAL3::GetInstance();
      HIBYTE(Buffer_44[98]) = (unsigned long)(((PAL3 *)v18))->PAL3::GetInstance_fd20()->m_pVtable;
      BYTE1(Buffer_44[99]) = (unsigned long)byte_BFDA40;
      LOBYTE(Buffer_44[99]) = (unsigned long)byte_BFDA41;
      BYTE2(Buffer_44[99]) = dword_C10CBC != 0;
      (((Actor *)this))->Actor::BuildCollisionMesh((int *)v6);
      fwrite(Buffer_508, 0xDCu, 1u, v7);
      Buffer_508[38] = ftell(v7);
      fwrite(Buffer_44, 0x1D0u, 1u, v7);
      Buffer_508[39] = ftell(v7);
      SaveGameState(v7);
      CScreenMode::LoadAudioFromFile((int *)this, v7, Buffer_508);
      v19 = ftell(v7);
      Buffer_1512 = 0;
      Buffer_1516 = 0;
      Buffer_1520 = 1;
      Buffer_508[43] = v19;
      memset(Buffer_1808, 0, 12);
      ArraySort((int)&Buffer_1808[9], 48, 4, 0 /* TODO: pmf_to_u32((int * (CCBStage::*)())CCBStage::ClearRoleState) */);
      ::ClearActionFlags((Actor *)&Buffer_1808[3]);
      v20 = (CHAR *)&Buffer_1808[58];
      v21 = 200;
      do
      {
        ::ClearModelFlag(v20);
        v20 += 808;
        --v21;
      }
      while ( v21 );
      Buffer_1808[40465] = 0;
      Buffer_1808[40462] = 1;
      Buffer_1808[40463] = 1;
      Buffer_1808[40464] = 1;
      v22 = v66;
      v23 = 11;
      do
      {
        v24 = (void *)v22;
        v22 += 52;
        --v23;
        memset(v24, 0, 0x2Cu);
      }
      while ( v23 );
      Buffer_1512 = g_ScriptSystemData.m_nScriptCounter0;
      Buffer_1516 = g_ScriptSystemData.m_nScriptCounter1;
      Buffer_1520 = g_ScriptSystemData.m_nScriptFlag;
      Buffer_1534 = g_nActorState;
      Buffer_1538 = g_nActor_DE5F9C;
      Buffer_1524 = g_nRoleParam;
      Buffer_1528 = g_nRoleState;
      Buffer_1532 = g_nActor_DE5FA8;
      Buffer_1540 = dword_C10CC4;
      Buffer_1596 = g_nUpdateInterval;
      qmemcpy(Buffer_1545, g_SaveSlotFlags, 0x28u);
      Buffer_1586 = *(_WORD *)((char *)&g_dwUISettings + 1);
      Buffer_1545[40] = g_dwUISettings;
      Buffer_1544 = g_bUIWnd_DE625A;
      Buffer_1592 = g_bRoleFlag2;
      Buffer_1588 = g_bRoleFlag1;
      v25 = 0;
      v26 = (unsigned __int8 **)&g_pSceneTransitionBegin;
      do
      {
        v27 = *(_BYTE *)v26++;
        Buffer_1600[v25++] = v27;
      }
      while ( (int)v26 < (int)&g_pSceneTransitionEnd );
      Buffer_1640 = g_nWolfIndex;
      qmemcpy(Buffer_1644, g_fCamRoleParams, sizeof(Buffer_1644));
      Buffer_1804 = g_nFiveNimbusCount;
      qmemcpy(Buffer_1808, &g_SceneTransitionBuffer, sizeof(Buffer_1808));
      v64 = byte_D92785;
      v65 = dword_C10CD4;
      qmemcpy(v66, g_pCBSystem->m_Player, 0x23Cu);
      fwrite(&Buffer_1512, 0x27CB4u, 1u, v7);
      if ( v6->m_pCapacity[21] == (char *)2 )
      {
        v28 = 0;
        if ( *(_DWORD *)((Object *)&v6->m_roles[50]) > 0 )
        {
          v29 = (int *)&Buffer_508[44];
          do
          {
            *v29 = ftell(v7);
            RoleDataOffset = (RoleSystem *)GetRoleDataOffset(v28);
            (((RoleSystem *)RoleDataOffset))->RoleSystem::GetFontColor(v7);
            ++v28;
            ++v29;
          }
          while ( v28 < *(_DWORD *)((Object *)&v6->m_roles[50]) );
        }
      }
      Buffer_508[47] = ftell(v7);
      m_nTodo_e0e0 = v6->m_nTodo_e0e0;
      fwrite(&m_nTodo_e0e0, 4u, 1u, v7);
      v31 = 0;
      memset(&Buffer_16[1], 0, 12);
      if ( m_nTodo_e0e0 > 0 )
      {
        m_roles = (RoleSystem *)v6->m_roles;
        do
        {
          (((RoleSystem *)m_roles))->RoleSystem::ExportRoleData(Buffer_16);
          fwrite(Buffer_16, 0x1Cu, 1u, v7);
          ++v31;
          m_roles = (RoleSystem *)((char *)m_roles + 8704);
        }
        while ( v31 < m_nTodo_e0e0 );
      }
      fseek(v7, 0, 0);
      strcpy((char *)Buffer_508, "PAL");
      LOBYTE(Buffer_508[1]) = 1;
      fwrite(Buffer_508, 0xDCu, 1u, v7);
      fclose(v7);
      v69 = -1;
      (((PalScript *)&Buffer_728))->PalScript::Cleanup();
      return 1;
    }
    else
    {
      v69 = -1;
      (((PalScript *)&Buffer_728))->PalScript::Cleanup();
      return 0;
    }
  }
  return result;
}

// 0x00538D20
BOOL Actor::CompareModelName(char *String1, char *String2)
{
  return !_strcmpi(String1, String2) && !_strcmpi(String1 + 32, String2 + 32);
}

// 0x00538FA0
void Actor::BuildCollisionMesh(int *pOut)
{
  Actor *m_actarray_end; // esi
  Actor *m_actarray_begin; // edi
  int *v5; // eax
  Actor *v6; // ecx
  int v7; // edx
  Actor *p_m_nAnimParam1; // ebp
  char *v9; // esi
  int *p_m_nPathBuffer; // ebx
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
  __int16 pVal; // [esp+0x14] [ebp-0x3E8] BYREF
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
  ::InitAction(&v30, &pActionType);
  qmemcpy(String2, pOut, sizeof(String2));
  v34 = 1;
  ::InitAction((Actor *)&v30.m_nPathBuffer, &v27);
  LOBYTE(v34) = 2;
  ::InitAction((Actor *)&v30.m_vecTargetPos.y, &v26);
  m_actarray_end = (Actor *)this->m_actarray_end;
  m_actarray_begin = (Actor *)this->m_actarray_begin;
  for ( LOBYTE(v34) = 3; m_actarray_begin != m_actarray_end; m_actarray_begin = (Actor *)((char *)m_actarray_begin + 164) )
  {
    if ( Actor::CompareModelName(&m_actarray_begin->m_actarray_type, String2) )
      break;
  }
  v5 = (int *)this->m_actarray_end;
  if ( m_actarray_begin == (Actor *)v5 )
  {
    Vec_InsertEntry(this, v5, (const int *)&v30.m_pact);
    v6 = (Actor *)this->m_actarray_begin;
    if ( v6 )
      v7 = ((char *)this->m_actarray_end - (char *)v6) / 164;
    else
      v7 = 0;
    m_actarray_begin = (Actor *)((char *)v6 + 164 * v7 - 164);
  }
  p_m_nAnimParam1 = (Actor *)&m_actarray_begin->m_nAnimParam1;
  v9 = ActVecReallocate(
         LODWORD(m_actarray_begin->m_vecBonePos.y),
         (char *)LODWORD(m_actarray_begin->m_vecBonePos.y),
         (char *)LODWORD(m_actarray_begin->m_vecBonePos.x),
         v22,
         v23);
  nullsub_2(v9, LODWORD(m_actarray_begin->m_vecBonePos.y));
  p_m_nPathBuffer = (int *)&m_actarray_begin->m_nPathBuffer;
  LODWORD(m_actarray_begin->m_vecBonePos.y) = (unsigned long)v9;
  (((Actor *)&m_actarray_begin->m_nPathBuffer))->Actor::GetActionArrayEnd((_WORD *)m_actarray_begin->m_nAnimBuffer, (__int16 *)m_actarray_begin->m_nParticleBuffer);
  qmemcpy(m_actarray_begin, pOut, 0x84u);
  ((gbVec3D *)&v30.m_fMatrixA)->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
  ((gbAABBox *)&v30.m_dwMatMsg[1])->gbAABBox::gbAABBox();
  ::ClearActionArrays((Actor *)(&v30.m_nUpdateMode + 4));
  v11 = (int *)pOut;
  v12 = 0;
  if ( pOut[55] > 0 )
  {
    v13 = (int *)(pOut + 72);
    do
    {
      if ( (((PalScriptMgr *)(v13 - 16)))->PalScriptMgr::IsInputBlocked() )
      {
        (((Actor *)&v30.m_nInterpFrames))->Actor::ActionEntry_Assign((int)(v13 + 27));
        v14 = *(v13 - 3);
        v15 = *(v13 - 1);
        *(&v30.m_nUpdateMode + 5) = *(v13 - 2);
        *(&v30.m_nUpdateMode + 4) = v14;
        v16 = (unsigned long)*v13;
        *(&v30.m_nUpdateMode + 6) = v15;
        *(&v30.m_nUpdateMode + 7) = v16;
        (((gbVec3D *)(&v30.m_nUpdateMode + 8)))->gbVec3D::operator=(*((const gbVec3D *)(v13 + 1)));
        v17 = *((_BYTE *)v13 + 17);
        v18 = (unsigned long)v13[5];
        v31 = *((_BYTE *)v13 + 16);
        v32 = v17;
        v33 = v18;
        PtrVec_InsertN(
          p_m_nAnimParam1,
          &p_m_nAnimParam1->m_actarray_end->m_actarray_type,
          1u,
          (const char *)&v30.m_nInterpFrames);
      }
      v11 = (int *)pOut;
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
        LOBYTE(pVal) = *(v20 - 129);
        HIBYTE(pVal) = v21;
        PtrVec_Insert_word((Actor *)p_m_nPathBuffer, (_WORD *)p_m_nPathBuffer[2], 1u, &pVal);
        v11 = (int *)pOut;
      }
      ++v19;
      v20 += 8704;
    }
    while ( v19 < v11[14392] );
  }
  LOBYTE(v34) = 1;
  (((Array *)&v30.m_vecTargetPos.y))->Array::Free();
  (((Array *)&v30.m_nPathBuffer))->Array::Free();
  v34 = -1;
  (((Array *)&v30))->Array::Free();
  (((Array *)&v29))->Array::Free();
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

  result = (char *)&this->m_actarray_type;
  v4 = nVal - (_DWORD)result;
  *(_DWORD *)result = *(_DWORD *)nVal;
  v5 = (char *)(result + 4);
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
  v6 = (char *)(result + 76);
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
  v8 = (char *)(result + 111);
  do
  {
    *v8 = v8[v4];
    ++v8;
  }
  while ( (unsigned int)&v8[-111 - (_DWORD)result] < 0x10 );
  *((_DWORD *)result + 32) = *(_DWORD *)(nVal + 128);
  v9 = (int *)(nVal + 136);
  *((_DWORD *)result + 33) = *(_DWORD *)(nVal + 132);
  v10 = (char *)(result + 140);
  nVala = 16;
  do
  {
    v11 = (unsigned long)*v9;
    v9 += 3;
    *((_DWORD *)v10 - 1) = v11;
    *(_DWORD *)v10 = *(_DWORD *)&v10[nVal - (_DWORD)result];
    *((_DWORD *)v10 + 1) = *(v9 - 1);
    v10 += 12;
    --nVala;
  }
  while ( nVala );
  *((_WORD *)result + 164) = *(_WORD *)(nVal + 328);
  v12 = (char *)(result + 330);
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
  v13 = (char *)(result + 392);
  do
  {
    *v13 = v13[v4];
    ++v13;
  }
  while ( (unsigned int)&v13[-392 - (_DWORD)result] < 8 );
  *((_DWORD *)result + 100) = *(_DWORD *)(nVal + 400);
  *((_DWORD *)result + 101) = *(_DWORD *)(nVal + 404);
  *((_DWORD *)result + 102) = *(_DWORD *)(nVal + 408);
  v14 = (char *)(result + 412);
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

// 0x00539540
int Actor::AddActionByName(const char *pszName, const char *pszName2, int nVal)
{
  int v4; // ebp
  Actor *m_actarray_end; // edi
  Actor *i; // esi
  float x; // ebx
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
  ::InitAction((Actor *)&v18, &pActionType);
  strcpy((char *)String2, pszName);
  strcpy((char *)v14, pszName2);
  m_actarray_end = (Actor *)this->m_actarray_end;
  for ( i = this->m_actarray_begin; i != m_actarray_end; i = (Actor *)((char *)i + 164) )
  {
    if ( Actor::CompareModelName(&i->m_actarray_type, String2) )
      break;
  }
  if ( i != this->m_actarray_end )
  {
    x = i->m_vecBonePos.x;
    for ( j = 0; x != 0.0f && j < (LODWORD(i->m_vecBonePos.y) - LODWORD(x)) / 656; ++j )
    {
      if ( *(unsigned __int8 *)(LODWORD(i->m_vecBonePos.x) + v4) == nVal )
      {
        v10 = LODWORD(i->m_vecBonePos.x) + 656 * j;
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

// 0x005399E0
void Actor::IterateActiveActors()
{
  Actor *m_actarray_begin; // ebp
  Actor *m_actarray_end; // ebx
  Actor *i; // esi

  m_actarray_begin = (Actor *)this->m_actarray_begin;
  m_actarray_end = (Actor *)this->m_actarray_end;
  for ( i = m_actarray_begin; i != m_actarray_end; i = (Actor *)((char *)i + 164) )
    ::ClearAllocBuffers(i);
  this->m_actarray_end = ((Actor *)(m_actarray_begin));
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
  Actor *p_m_pact; // ebx
  char *p_m_actarray_type; // eax
  char *v6; // ebp
  Actor *m_actarray_begin; // edx
  unsigned int v8; // ecx
  int v9; // eax
  unsigned int v10; // esi
  int v11; // eax
  char *v12; // edi
  Actor *v13; // eax
  Actor *v14; // eax
  int v15; // ecx
  Actor *m_actarray_end; // eax
  char *v17; // edi
  int v18; // [esp+0x0] [ebp-0x50]
  char pData[64]; // [esp+0x10] [ebp-0x40] BYREF
  char *String1; // [esp+0x54] [ebp+0x4]
  char *pszBufa; // [esp+0x58] [ebp+0x8]

  if ( pszName && pszBuf && strlen(pszName) && strlen(pszBuf) && !this->Actor::SearchAnimByIndex(pszName, pszBuf) )
  {
    memset(pData, 0, sizeof(pData));
    p_m_pact = (Actor *)&this->m_pact;
    strcpy((char *)pData, pszName);
    strcpy((char *)&pData[32], pszBuf);
    p_m_actarray_type = (char *)&p_m_pact->m_actarray_end->m_actarray_type;
    v6 = (char *)p_m_actarray_type;
    if ( ((char *)p_m_pact->m_actarray_capacity_end - p_m_actarray_type) >> 6 )
    {
      (((Actor *)p_m_pact))->Actor::CopyBufferBlocks(p_m_actarray_type, p_m_actarray_type, p_m_actarray_type + 64);
      (((Actor *)p_m_pact))->Actor::CopyIfValid(&p_m_pact->m_actarray_end->m_actarray_type, (char *)(1 - (((char *)p_m_pact->m_actarray_end - v6) >> 6)), pData);
      m_actarray_end = (Actor *)p_m_pact->m_actarray_end;
      if ( v6 == (char *)m_actarray_end )
      {
        p_m_pact->m_actarray_end = (Actor *)((char *)p_m_pact->m_actarray_end + 64);
      }
      else
      {
        do
        {
          v17 = (char *)v6;
          v6 += 64;
          qmemcpy(v17, pData, 0x40u);
        }
        while ( v6 != (char *)m_actarray_end );
        p_m_pact->m_actarray_end = (Actor *)((char *)p_m_pact->m_actarray_end + 64);
      }
    }
    else
    {
      m_actarray_begin = (Actor *)p_m_pact->m_actarray_begin;
      if ( !m_actarray_begin || (v8 = (p_m_actarray_type - (char *)m_actarray_begin) >> 6, v8 <= 1) )
        v8 = 1;
      if ( m_actarray_begin )
        v9 = (p_m_actarray_type - (char *)m_actarray_begin) >> 6;
      else
        v9 = 0;
      v10 = v9 + v8;
      v11 = v9 + v8;
      if ( v11 < 0 )
        v11 = 0;
      pszBufa = (char *)operator new(v11 << 6);
      v12 = (char *)pszBufa;
      v13 = (Actor *)p_m_pact->m_actarray_begin;
      String1 = (char *)&v13->m_actarray_type;
      if ( v13 != (Actor *)v6 )
      {
        while ( 1 )
        {
          Actor::CopyConstruct_40(v12, v13, v18);
          v12 += 64;
          String1 += 64;
          if ( String1 == v6 )
            break;
          v13 = (Actor *)String1;
        }
      }
      (((Actor *)p_m_pact))->Actor::CopyIfValid(v12, (char *)1, pData);
      (((Actor *)p_m_pact))->Actor::CopyBufferBlocks(v6, &p_m_pact->m_actarray_end->m_actarray_type, v12 + 64);
      nullsub_2(p_m_pact->m_actarray_begin, p_m_pact->m_actarray_end);
      operator delete(p_m_pact->m_actarray_begin);
      v14 = (Actor *)p_m_pact->m_actarray_begin;
      p_m_pact->m_actarray_capacity_end = (Actor *)&pszBufa[64 * v10];
      if ( v14 )
      {
        v15 = (((char *)p_m_pact->m_actarray_end - (char *)v14) >> 6) + 1;
        p_m_pact->m_actarray_begin = (Actor *)pszBufa;
        p_m_pact->m_actarray_end = (Actor *)&pszBufa[64 * v15];
      }
      else
      {
        p_m_pact->m_actarray_begin = (Actor *)pszBufa;
        p_m_pact->m_actarray_end = (Actor *)(pszBufa + 64);
      }
    }
  }
}

// 0x0053A020
char Actor::IterateAllocBuffer(int nVal)
{
  char *m_pAllocBuf; // edx
  unsigned int i; // eax

  m_pAllocBuf = (char *)this->m_pAllocBuf;
  for ( i = 0; m_pAllocBuf && i < (LODWORD(this->m_fTransitionSpeed) - (int)m_pAllocBuf) >> 2; ++i )
  {
    if ( *(_DWORD *)&this->m_pAllocBuf[4 * i] == nVal )
      return 1;
  }
  return 0;
}

// 0x0053A080
_WORD * Actor::GetActionArrayEnd(_WORD *p_WORD, __int16 *pnVal)
{
  __int16 *v3; // edx
  _WORD *result; // eax
  __int16 *m_actarray_end; // edi
  Actor *v6; // esi
  __int16 v7; // bx

  v3 = (__int16 *)pnVal;
  result = (_WORD *)p_WORD;
  m_actarray_end = (__int16 *)this->m_actarray_end;
  v6 = (Actor *)p_WORD;
  if ( pnVal != m_actarray_end )
  {
    do
    {
      v7 = *v3++;
      *(_WORD *)&v6->m_actarray_type = v7;
      v6 = (Actor *)((char *)v6 + 2);
    }
    while ( v3 != m_actarray_end );
  }
  this->m_actarray_end = ((Actor *)(v6));
  return result;
}

// 0x0053A2E0
int Actor::GetActionCount()
{
  int result; // eax

  result = (int)this->m_actarray_begin;
  if ( result )
    return ((int)this->m_actarray_end - result) / 164;
  return result;
}

// 0x0053A310
void Actor::DestroyActionRange(int nVal, int nVal2)
{
  Actor *i; // esi

  for ( i = (Actor *)nVal; i != (Actor *)nVal2; i = (Actor *)((char *)i + 164) )
    ::ClearAllocBuffers(i);
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
    VideoPlayer::SetRegion(v5, v4);
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
    VideoPlayer::SetRegion(nX, nY);
    nX += 164;
  }
}

// 0x0053AFA0
char * Actor::CopyBufferBlocks(char *pszDst, char *pszSrc, char *pszBuf3)
{
  char *v4; // edx
  char *result; // eax

  v4 = (char *)pszDst;
  if ( pszDst == pszSrc )
    return pszBuf3;
  result = (char *)pszBuf3;
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

  result = (char *)pszBuf2;
  if ( pszBuf2 )
  {
    v5 = (char *)pszBuf2;
    result = (char *)pszBuf;
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

  result = (int)this->m_actarray_begin;
  if ( result )
    return ((int)this->m_actarray_end - result) / 656;
  return result;
}

// 0x0053B260
char * Actor::CompareBuffers(char *pszBuf, char *pszBuf2, char *pszBuf3)
{
  char *v4; // edx
  char *result; // eax

  v4 = (char *)pszBuf;
  if ( pszBuf == pszBuf2 )
    return pszBuf3;
  result = (char *)pszBuf3;
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
int * Actor::SelectPointer(int *pnVal, int *pnVal2, int *pnVal3)
{
  int *v3; // ecx
  int *result; // eax
  int v5; // esi

  v3 = (int *)pnVal;
  if ( pnVal == pnVal2 )
    return pnVal3;
  result = (int *)pnVal3;
  do
  {
    v5 = (unsigned long)(*v3++);
    *result++ = v5;
  }
  while ( v3 != pnVal2 );
  return result;
}

// 0x0053B6E0
void Actor::CopyConstruct_1C(void *pDst, const void *pSrc)
{
  if ( pDst )
    qmemcpy(pDst, pSrc, 0x1Cu);
}

// 0x0053B700
void Actor::CopyConstruct_290(void *pDst, const void *pSrc, int nVal)
{
  if ( pDst )
    qmemcpy(pDst, pSrc, 0x290u);
}

// 0x0053B870
void Actor::CopyConstruct_40(void *pDst, const void *pSrc, int nVal)
{
  if ( pDst )
    qmemcpy(pDst, pSrc, 0x40u);
}

// 0x0053BAE0
int * Actor::ActArray_Assign(int *p_DWORD)
{
  Actor *v3; // esi
  int v4; // edi
  unsigned int v5; // ebp
  Actor *m_actarray_begin; // ecx
  unsigned int v7; // edx
  int v8; // esi
  Actor *v9; // ebp
  int v10; // eax
  int v11; // edx
  int *result; // eax
  unsigned int v13; // ebp
  unsigned int v14; // edx
  int v15; // edx
  Actor *v16; // ebp
  char *j; // esi
  int v18; // ebp
  int *v19; // ecx
  char *v20; // eax
  Actor *k; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  Actor *v27; // eax
  int v28; // ebp
  Actor *v29; // edx
  char *i; // eax
  int *p_DWORDa; // [esp+0x18] [ebp+0x4]
if ( this == (Actor *)p_DWORD )
    return (int *)this;
  v4 = (unsigned long)p_DWORD[1];
  if ( v4 )
    v5 = (p_DWORD[2] - v4) / 656;
  else
    v5 = 0;
  m_actarray_begin = (Actor *)this->m_actarray_begin;
  if ( m_actarray_begin )
    v7 = ((char *)this->m_actarray_end - (char *)m_actarray_begin) / 656;
  else
    v7 = 0;
  if ( v5 <= v7 )
  {
    v8 = (unsigned long)p_DWORD[1];
    p_DWORDa = (int *)p_DWORD[2];
    v9 = (Actor *)m_actarray_begin;
    if ( (int *)v4 != p_DWORDa )
    {
      do
      {
        ::SetCurrentAction(v9, v8);
        v8 += 656;
        v9 = (Actor *)((char *)v9 + 656);
      }
      while ( (int *)v8 != p_DWORDa );
    }
    v10 = (unsigned long)p_DWORD[1];
    if ( v10 )
      v11 = (p_DWORD[2] - v10) / 656;
    else
      v11 = 0;
    result = (int *)this;
    this->m_actarray_end = ((Actor *)((Actor *)((char *)this->m_actarray_begin + 656 * v11)));
    return result;
  }
  if ( v4 )
    v13 = (p_DWORD[2] - v4) / 656;
  else
    v13 = 0;
  if ( m_actarray_begin )
    v14 = ((char *)this->m_actarray_capacity_end - (char *)m_actarray_begin) / 656;
  else
    v14 = 0;
  if ( v13 > v14 )
  {
    operator delete(this->m_actarray_begin);
    v24 = (unsigned long)p_DWORD[1];
    if ( v24 )
      v25 = (p_DWORD[2] - v24) / 656;
    else
      v25 = 0;
    v26 = v25;
    if ( v25 < 0 )
      v26 = 0;
    v27 = (Actor *)operator new(656 * v26);
    this->m_actarray_begin = v27;
    v28 = (unsigned long)p_DWORD[2];
    v29 = (Actor *)v27;
    for ( i = (char *)p_DWORD[1]; i != (char *)v28; v29 = (Actor *)((char *)v29 + 656) )
    {
      if ( v29 )
      {
        qmemcpy(v29, i, 0x290u);
}
      i += 656;
    }
    this->m_actarray_end = v29;
    this->m_actarray_capacity_end = v29;
    return (int *)this;
  }
  if ( m_actarray_begin )
    v15 = ((char *)this->m_actarray_end - (char *)m_actarray_begin) / 656;
  else
    v15 = 0;
  v16 = (Actor *)this->m_actarray_begin;
  for ( j = (char *)(v4 + 656 * v15); (char *)v4 != j; v16 = (Actor *)((char *)v16 + 656) )
  {
    ::SetCurrentAction(v16, v4);
    v4 += 656;
  }
  v18 = (unsigned long)p_DWORD[2];
  v19 = (int *)this;
  v20 = (char *)j;
  for ( k = this->m_actarray_end; v20 != (char *)v18; k = (Actor *)((char *)k + 656) )
  {
    if ( k )
    {
      qmemcpy(k, v20, 0x290u);
      v19 = (int *)this;
    }
    v20 += 656;
  }
  v22 = (unsigned long)p_DWORD[1];
  if ( v22 )
    v23 = (p_DWORD[2] - v22) / 656;
  else
    v23 = 0;
  result = (int *)v19;
  v19[2] = (unsigned long)(v19[1] + 656 * v23);
  return result;
}

// 0x0053BEB0
int Actor::GetActionCountEx()
{
  int result; // eax

  result = (int)this->m_actarray_begin;
  if ( result )
    return ((int)this->m_actarray_capacity_end - result) / 656;
  return result;
}

// 0x0053D390
void Actor::_todo_0053D390(int a2)
{
  flt_17B41E0 = 12.0 + 12.0;
}

// 0x0053DB10
// Microsoft VisualC 2-14/net runtime
void Actor::_todo_0053DB10(int a2)
{
  sub_53D3F0((Actor *)&stru_17B3ED8);
}
