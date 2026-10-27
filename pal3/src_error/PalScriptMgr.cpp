// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Script/PalScriptMgr.h"
#include "Role/Actor.h"
#include "Misc/CCBEditor.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBStageRole.h"
#include "Combat/CCBStageScene.h"
#include "Misc/CG_Entry.h"
#include "Misc/CG_Scene.h"
#include "Render/CScreenMode.h"
#include "Scene/CameraCtrl.h"
#include "GameBase/GRPinput.h"
#include "Misc/GeomNode.h"
#include "GameBase/InputSystem.h"
#include "Role/Object3D.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/OpenSceneFile.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Misc/PathObj.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Misc/RoleCameraCtrl.h"
#include "Role/RoleSystem.h"
#include "Scene/Scene.h"
#include "Misc/ScriptSystemData.h"
#include "Misc/ScriptVM.h"
#include "Misc/String.h"
#include "UI/UIListBox.h"
#include "UI/UIScene.h"
#include "UI/UIWnd.h"
#include "Misc/_Console.h"
#include "Misc/scAsmDecoder.h"
#include "Misc/scSCEFile.h"
#include "Misc/scVarStack.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

class RoleCameraCtrl;

// Unnamed globals (extern)
extern RoleCameraCtrl stru_DBA134;

// 0x004100A0
int PalScriptMgr::RunScript(int nVal, int nVal2, int nVal3)
{
  int result; // eax
  unsigned int *v4; // edx
  scAsmDecoder *v5; // edi
  int v6; // ebx
  scAsmDecoder *v7; // esi
  unsigned int v8; // ecx
  int v9; // eax
  GRPinput *v10; // eax
  GRPinput *v11; // esi
  CScreenMode *Instance; // eax
  const void *v13; // [esp-0x8] [ebp-0x13C]
  void *pData[6]; // [esp+0x10] [ebp-0x124]
  char Buffer[256]; // [esp+0x28] [ebp-0x10C] BYREF
  int v16; // [esp+0x130] [ebp-0x4]

  v4 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
  v5 = dword_C10CC8;
  v6 = 0;
  v7 = 0;
  do
  {
    LOBYTE(result) = *((_BYTE *)&v7->m_stack + (_DWORD)(&g_RoleSlotBuf.dword_17AA450 + 148));
    if ( (_BYTE)result )
    {
      LOBYTE(result) = nVal3;
      if ( !(_BYTE)nVal3 || v7 == v5 )
      {
        v8 = (unsigned long)*v4;
        v9 = (unsigned long)(*v4 - nVal);
        if ( v9 < 1 )
          v9 = 1;
        *v4 = v9;
        result = v9 - v8;
        if ( v7 == v5 )
          v6 = result;
      }
    }
    v4 += 352;
    v7 = (scAsmDecoder *)((char *)v7 + 1);
  }
  while ( (int)v4 < (int)dword_C062EC );
  if ( v6 < 0 )
  {
    sprintf(Buffer, (const char *)&dir[20], v6);
    v10 = (GRPinput *)operator new(0x24u);
    pData[5] = v10;
    v16 = 0;
    if ( v10 )
      v11 = (((GRPinput *)v10))->GRPinput::SetMousePos();
    else
      v11 = 0;
    v16 = -1;
    (((GRPinput *)v11))->GRPinput::SetJoystickPos(Buffer, 0);
    (((PtrArray *)&g_pScriptObjArray))->PtrArray::SetAt(nIndex, (int)v11);
    LOBYTE(result) = nVal2;
    if ( (_BYTE)nVal2 )
    {
      pData[0] = "we015";
      pData[1] = "we016";
      pData[2] = "we017";
      pData[3] = "we018";
      pData[4] = "we019";
      v13 = pData[(_DWORD)dword_C10CC8];
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v13, 1);
    }
  }
  return result;
}

// 0x00410920
int * PalScriptMgr::LoadYlfScript()
{
  const char *v1; // eax

  int *result; // eax
  char Buffer[128]; // [esp+0x0] [ebp-0x80] BYREF

  v1 = (const char *)UISceneUpdate();
  sprintf(Buffer, "_ylf_%s_%s", v1, v1 + 32);
  PtrArray::IsArrayReady();
  this->PalScriptMgr::Destroy();
  return result;
}

// 0x0041BDE0
int * PalScriptMgr::Get_result()
{
    PalScriptMgr *_this = this;
  int *result; // eax

  result = (int *)_this;
  *(_DWORD *)_this = 0;
  *(_DWORD *)&_this->m_bGetSceneScript = 0;
  _this->m_scriptMain.m_pData = ((char *)0);
  _this->m_scriptMain.capacity = 0;
  return result;
}

// 0x00420B40
void PalScriptMgr::CheckTileScript(RoleSystem *pRole, float fVal, char bExecute)
{
  int m_nState; // esi
  __int64 v6; // rax
  unsigned __int8 Tile; // bl
  char *v8; // eax
  char *v9; // eax
  char v10; // al
  int nX; // [esp+0xC] [ebp-0x8]

  if ( pRole )
  {
    m_nState = pRole->m_partyActor.m_nState;
    nX = (__int64)((*(&pRole[1].m_partyActor.m_fSpeed + 2) - *((float *)&this[51].m_nField_1D94 + 41 * m_nState + 3))
                 / g_fTileScale);
    v6 = (__int64)((pRole[1].m_partyActor.m_fAngleDeg - *((float *)&this[51].m_nField_1D94 + 41 * m_nState + 5))
                 / g_fTileScale);
    if ( nX < 0
      || nX >= *(&this[51].m_nField_1D94 + 41 * m_nState + 9)
      || (int)v6 < 0
      || (int)v6 >= *(&this[51].m_nField_1D94 + 41 * m_nState + 10) )
    {
      Tile = -1;
    }
    else
    {
      Tile = (((RoleSystem *)(&this->m_RoleAnimData + 5 * m_nState)))->RoleSystem::GetTile(nX, v6);
    }
    if ( bExecute )
    {
      if ( Tile != 0xFF )
      {
        v8 = (char *)this + 896 * Tile;
        if ( v8[397] )
        {
          if ( v8[468] == 38 )
            (((ScriptVM *)(v8 + 224)))->ScriptVM::ExecuteBlock();
        }
      }
    }
    else
    {
      if ( Tile != 0xFF )
      {
        v9 = (char *)this + 896 * Tile;
        if ( v9[397] )
        {
          (((ScriptVM *)(v9 + 224)))->ScriptVM::ExecuteBlock();
          (((RoleSystem *)pRole))->RoleSystem::GetActiveRole();
        }
      }
      v10 = *((_BYTE *)&this[51].m_nField_1D94 + 256);
      if ( v10 != Tile && v10 != -1 )
        (((PalScriptMgr *)(&this->m_nSavedDataB
                                                    + 224 * *((unsigned __int8 *)&this[51].m_nField_1D94 + 256))))->PalScriptMgr::GetScriptState();
      *((_BYTE *)&this[51].m_nField_1D94 + 256) = Tile;
    }
  }
}

// 0x00429D80
int PalScriptMgr::InitControlBlock()
{
  ((gbMatrix4 *)&this->m_scriptMain)->gbMatrix4::gbMatrix4();
  memset(this, 0, 0x54u);
  return (int)this;
}

// 0x00429DB0
void PalScriptMgr::BuildCmdTransform(gbMatrix4 *pMatrix)
{
  char m_nExecRangeD; // al
  int m_scriptAux; // eax
  char **p_m_pExecSystem; // esi
  float v5; // st6
  float v6; // [esp+0x4] [ebp-0x18]
  float v7; // [esp+0x8] [ebp-0x14]
  float v8; // [esp+0x8] [ebp-0x14]
  float v9; // [esp+0xC] [ebp-0x10]
  float v10; // [esp+0xC] [ebp-0x10]
  struct gbVec3D v11; // [esp+0x10] [ebp-0xC] BYREF

  m_nExecRangeD = this->m_nExecRangeD;
  if ( m_nExecRangeD == 20 || m_nExecRangeD == 27 )
  {
    v6 = this->m_fPosAZ - *(&this->m_nTodo_214 + 1);
    v7 = this->m_fPosBX - this->m_fPosAX;
    v5 = this->m_fPosBY - this->m_fPosAY;
    v11.x = v6;
    v11.y = v7;
    v9 = v5;
    *(float *)&pMatrix[1] = v6;
    v11.z = v9;
    pMatrix[1].xy = v7;
    pMatrix[1].xz = v9;
    v8 = this->m_fPosBX + this->m_fPosAX;
    v10 = this->m_fPosBY + this->m_fPosAY;
    v11.x = (*(&this->m_nTodo_214 + 1) + this->m_fPosAZ) * 0.5;
    v11.y = v8 * 0.5;
    v11.z = v10 * 0.5;
    (((gbMatrix4 *)pMatrix))->gbMatrix4::LoadIdentity();
    (((gbMatrix4 *)pMatrix))->gbMatrix4::RightTranslate(v11);
  }
  else
  {
    m_scriptAux = this->m_scriptAux;
    if ( m_scriptAux )
    {
      if ( m_scriptAux == 2 || m_scriptAux == 3 )
      {
        p_m_pExecSystem = (char **)&this->m_pExecSystem;
        (((gbMatrix4 *)pMatrix))->gbMatrix4::operator=(*((const gbMatrix4 *)&this->m_pExecSystem));
        *(_DWORD *)&pMatrix[1] = (unsigned long)p_m_pExecSystem[16];
        LODWORD(pMatrix[1].xy) = (unsigned long)p_m_pExecSystem[17];
        LODWORD(pMatrix[1].xz) = (unsigned long)p_m_pExecSystem[18];
      }
      else
      {
        (*(void ( **)(gbVisNode *, gbMatrix4 *))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 56))(
          this->m_pScriptObjMain,
          pMatrix);
      }
    }
  }
}

// 0x00429F90
void PalScriptMgr::BuildFullTransform(gbMatrix4 *pMatrix, gbVec3D *pPos)
{
  gbMatrix4 v4; // [esp+0x14] [ebp-0x40] BYREF

  this->PalScriptMgr::BuildCmdTransform(pMatrix);
  (((gbMatrix4 *)&v4))->gbMatrix4::LoadIdentity();
  (((gbMatrix4 *)&v4))->gbMatrix4::SetAxisAngle(GB_AXIS_X, this->m_fPosBZ);
  (((gbMatrix4 *)pMatrix))->gbMatrix4::RightMultiply(&v4);
  (((gbMatrix4 *)&v4))->gbMatrix4::SetAxisAngle(GB_AXIS_Y, *(float *)&this->m_nSavedDataB);
  (((gbMatrix4 *)pMatrix))->gbMatrix4::RightMultiply(&v4);
  (((gbMatrix4 *)pMatrix))->gbMatrix4::RightTranslate(*pPos);
}

// 0x0042AAE0
BOOL PalScriptMgr::CheckTileCollision(int *pnVal, int nVal, gbVec3D *p)
{
  GRPinput *RolePtr; // eax
  BOOL result; // eax
  int v7; // edx
  int v8; // ecx
  Object3D *v9; // ebx
  int v10; // edi
  int v11; // eax
  int i; // ebx
  unsigned __int8 Tile; // [esp+0x10] [ebp-0x9C]
  struct gbOBBox v14; // [esp+0x14] [ebp-0x98] BYREF
  gbOBBox pMatrix; // [esp+0x60] [ebp-0x4C] BYREF

  RolePtr = (GRPinput *)(((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::GetRolePtr(BYTE2(this->m_nExecRangeD));
  result = (((GRPinput *)RolePtr))->GRPinput::GetJoystickFreePos((int)pnVal, nVal);
  if ( result )
  {
    Tile = (((RoleSystem *)this->m_nBlockHandle))->RoleSystem::GetTile((int)pnVal, nVal);
    if ( Tile != 0xFF )
    {
      v7 = 896 * Tile;
      v8 = *(_DWORD *)(this->m_nBlockHandle + 16);
      v9 = (Object3D *)(v7 + v8 + 224);
      if ( !*(_BYTE *)(v7 + v8 + 433) && (*(_BYTE *)(v7 + v8 + 432) & 2) != 0 )
      {
        this->PalScriptMgr::BuildFullTransform(&pMatrix.trans, p);
        (((Object3D *)v9))->Object3D::SetTransform(&v14.trans);
        if ( (((gbOBBox *)&pMatrix))->gbOBBox::IsColOBB(&v14) )
          return 0;
      }
    }
    if ( LOBYTE(this->m_nExecRangeD) == 11 )
    {
      this->PalScriptMgr::BuildFullTransform(&v14.trans, p);
      v10 = 0;
      v11 = *(_DWORD *)(this->m_nBlockHandle + 16);
      if ( *(int *)(v11 + 220) > 0 )
      {
        for ( i = 0; ; i += 896 )
        {
          if ( v10 != LOBYTE(this->m_pSceneMgr) && *(_BYTE *)(i + v11 + 468) == 11 )
          {
            (((Object3D *)(i + v11 + 224)))->Object3D::SetTransform(&pMatrix.trans);
            if ( (((gbOBBox *)&v14))->gbOBBox::IsColOBB(&pMatrix) )
              break;
          }
          ++v10;
          v11 = *(_DWORD *)(this->m_nBlockHandle + 16);
          if ( v10 >= *(_DWORD *)(v11 + 220) )
            return 1;
        }
        return 0;
      }
    }
    return 1;
  }
  return result;
}

// 0x0042AC80
int PalScriptMgr::CmdUpdateRolePath(float *pfVal, float *pfVal2)
{
  int result; // eax
  int RolePtr; // esi

  result = this->m_nBlockHandle;
  if ( result )
  {
    RolePtr = (((RoleSystem *)*(RoleSystem **)(result + 16)))->RoleSystem::GetRolePtr(BYTE2(this->m_nExecRangeD));
    return (((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::UpdatePathProgress((char)this->m_pSceneMgr, BYTE2(this->m_nExecRangeD), (char *)(__int64)((*pfVal - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta), (__int64)((pfVal[2] - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta), (char *)(__int64)((*pfVal2 - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta), (__int64)((pfVal2[2] - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta));
  }
  return result;
}

// 0x0042AF80
char PalScriptMgr::GetScriptState()
{
  char result; // al

  result = this->m_nExecRangeD;
  if ( result == 9 )
  {
    LOBYTE(this->m_scepath) = 0;
  }
  else if ( result == 38 )
  {
    *(_DWORD *)&this->m_bBigMapState = 0;
  }
  return result;
}

// 0x0042AFA0
int PalScriptMgr::SaveExecutionState()
{
  RoleSystem *v1; // edi
  int RolePtr; // ebp
  __int64 v4; // rax
  int v5; // ecx
  int v6; // eax
  float v7; // st7
  int v8; // edx
  float v9; // ecx
  float v10; // edx
  int v11; // ecx
  int v12; // eax
  char *v13; // edx
  int m_nCmdValue_low; // ecx
  int m_nBlockHandle; // edx
  int v16; // eax
  PalScriptMgr *v17; // edi
  PalScriptMgr *v18; // eax
  PalScriptMgr *v19; // ebx
  int result; // eax
  int v21; // [esp-0x4] [ebp-0x28]
  int v22; // [esp+0x0] [ebp-0x24]
  float v23; // [esp+0x10] [ebp-0x14] BYREF
  char v24; // [esp+0x14] [ebp-0x10]
  char v25; // [esp+0x15] [ebp-0xF]
  float v26; // [esp+0x18] [ebp-0xC]
  int pPoint; // [esp+0x1C] [ebp-0x8] BYREF
  int v28; // [esp+0x20] [ebp-0x4]

  v1 = g_pRoleSystem;
  (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
  RolePtr = (((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::GetRolePtr(v1->m_partyActor.m_nState);
  v4 = (__int64)((*(float *)&v1->m_id - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta);
  pPoint = (__int64)((*(float *)&v1->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta);
  v28 = v4;
  if ( PointInRect(&this->m_nExecState, &pPoint) )
  {
    switch ( *(_DWORD *)&this->m_bRoleCmd )
    {
      case 0:
        v5 = v28;
        v6 = this->m_nExecState - 1;
        pPoint = v6;
        goto LABEL_9;
      case 1:
        v5 = v28;
        v6 = this->m_nLoopCountA + 1;
        pPoint = v6;
        goto LABEL_9;
      case 2:
        v5 = (int)(this->m_pCmdBuffer - 1);
        v28 = v5;
        goto LABEL_8;
      case 3:
        v5 = this->m_nLoopCountB + 1;
        v28 = v5;
        goto LABEL_8;
      default:
        v5 = v28;
LABEL_8:
        v6 = pPoint;
LABEL_9:
        v7 = 0.0f;
        v23 = ((float)pPoint + 0.5f) * g_ScriptSystemData.m_g_fTimeDelta + *(float *)(RolePtr + 128);
        v26 = ((float)v28 + 0.5f) * g_ScriptSystemData.m_g_fTimeDelta + *(float *)(RolePtr + 136);
        if ( v6 >= 0 )
        {
          v8 = *(_DWORD *)(RolePtr + 152);
          if ( v6 < v8 && v5 >= 0 && v5 < *(_DWORD *)(RolePtr + 156) )
            v7 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (v6 + v5 * v8));
        }
        v9 = v23;
        v10 = v26;
        *(float *)&v1->m_wndcolor.Color = v7;
        *(float *)&v1->m_fontcolor.Color = v9;
        *(float *)&v1->m_id = v10;
        v1->m_wndcolor.Color = 0;
        (((RoleSystem *)v1))->RoleSystem::SetMoveSpeed(0.0, 0, v22);
        break;
    }
  }
  LOBYTE(this->m_scepath) = 0;
  (((RoleSystem *)v1))->RoleSystem::Notify();
  if ( *(_DWORD *)&this->m_nCmdType == 2 && this->PalScriptMgr::IsScriptReady() )
  {
    v11 = BYTE1(this->m_scepath);
    v24 = -1;
    v12 = *(_DWORD *)&this->m_bRoleCmd - 2;
    v13 = (char *)&v23 + v11;
    m_nCmdValue_low = LOWORD(this->m_nCmdValue);
    v23 = 9.367221729153875e-38f;
    v25 = 0;
    LOBYTE(v12) = (unsigned long)v13[3 * v12];
    m_nBlockHandle = this->m_nBlockHandle;
    BYTE1(this->m_scepath) = v12;
    (((PalScript *)*(PalScript **)(m_nBlockHandle + 16)))->PalScript::SetAction(m_nCmdValue_low);
    v17 = (PalScriptMgr *)v16;
    LOWORD(v16) = this->m_nCmdParam0;
    (((PalScript *)*(PalScript **)(this->m_nBlockHandle + 16)))->PalScript::SetAction(v16);
    v19 = (PalScriptMgr *)v18;
    switch ( BYTE1(this->m_scepath) )
    {
      case 0:
        (((PalScriptMgr *)v17))->PalScriptMgr::SetPauseState(0);
        v21 = 0;
        goto LABEL_23;
      case 1:
        (((PalScriptMgr *)v17))->PalScriptMgr::SetPauseState(1);
        break;
      case 2:
        v21 = 1;
LABEL_23:
        (((PalScriptMgr *)v19))->PalScriptMgr::SetPauseState(v21);
        break;
    }
  }
  *(_DWORD *)&this->m_pTodo_84 = this->m_nTodo_024;
  result = LODWORD(this->m_fCamX);
  this->m_nExecuteBlock = result;
  this->m_nSavedDataA = LODWORD(this->m_fCamY);
  return result;
}

// 0x0042B350
void PalScriptMgr::ProcessRoleLoading()
{
  Actor *SaveDataManager; // eax
  int v3; // eax
  float v4; // st7
  int m_nCmdValue; // eax
  int v6; // eax
  int v7; // edi
  char v8; // cl
  RoleSystem *v9; // eax
  Scene *v10; // [esp-0xC] [ebp-0x14]
  int v11; // [esp-0x4] [ebp-0xC]
  int v12; // [esp-0x4] [ebp-0xC]

  if ( LOBYTE(this->m_nExecRangeD) == 22 )
  {
    if ( BYTE2(this->m_fSpeed2) )
    {
      if ( BYTE2(this->m_nTodo_214) != 0xFF )
      {
        v11 = BYTE2(this->m_nTodo_214);
        v10 = UISceneUpdate();
        SaveDataManager = (Actor *)GetSaveDataManager();
        v3 = (((Actor *)SaveDataManager))->Actor::AddActionByName((const char *)v10, (const char *)&this->m_fSpeed2 + 2, v11);
        if ( v3 )
        {
          if ( *(_BYTE *)(v3 + 3) )
          {
            v4 = (float)*(int *)&this->m_nCmdType;
            m_nCmdValue = this->m_nCmdValue;
            BYTE1(this->m_nSavedBlockNum) = 1;
            this->m_fCamX = v4;
            LOBYTE(this->m_scepath) = 2;
            if ( m_nCmdValue )
              (((RoleSystem *)this))->RoleSystem::UpdateStateMode() /* [ROWTABLE] */;
          }
        }
      }
    }
    (((PalScript *)*(PalScript **)(this->m_nBlockHandle + 16)))->PalScript::SetAction(this->m_nCmdParam0);
    v7 = v6;
    if ( v6 )
    {
      v8 = *(_BYTE *)(v6 + 246);
      *(float *)(v6 + 44) = this->m_fCamX;
      if ( BYTE2(this->m_nExecRangeD) != v8 )
      {
        (((RoleSystem *)v6))->RoleSystem::ProcessAction();
        v12 = BYTE2(this->m_nExecRangeD);
        v9 = (RoleSystem *)UISceneUpdate();
        *(_DWORD *)(v7 + 796) = (unsigned long)(((RoleSystem *)v9))->RoleSystem::NotifyPathEnd(v12);
        (((RoleSystem *)v7))->RoleSystem::ProcessAction();
        *(_BYTE *)(v7 + 246) = BYTE2(this->m_nExecRangeD);
      }
      if ( this->m_nLoopCountC )
        g_pRoleSystem->m_fPosY = this->m_fCamX;
    }
  }
}

// 0x0042B450
BOOL PalScriptMgr::IsPosInBounds(float *pfPos)
{
  int RolePtr; // esi
  int v5; // ebx
  float v6; // st7
  __int64 v7; // rax

  if ( !pfPos )
    return 0;
  if ( BYTE2(this->m_nExecRangeD) != *((_DWORD *)pfPos + 157) )
    return 0;
  RolePtr = (((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::GetRolePtr(BYTE2(this->m_nExecRangeD));
  v5 = (__int64)((pfPos[1] - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_g_fTimeDelta);
  v6 = (pfPos[3] - *(float *)(RolePtr + 136)) / g_ScriptSystemData.m_g_fTimeDelta;
  v7 = (__int64)v6;
  return v5 >= 0
      && v5 < *(_DWORD *)(RolePtr + 152)
      && (int)v7 >= 0
      && (int)v7 < *(_DWORD *)(RolePtr + 156)
      && (((RoleSystem *)this->m_nBlockHandle))->RoleSystem::GetTile(v5, (__int64)v6) == LOBYTE(this->m_pSceneMgr);
}

// 0x0042B5B0
double PalScriptMgr::UpdateScriptRoles(double thisa, int nVal, int nVal2)
{
  char m_nExecRangeD; // al
  Scene *v6; // eax
  char v7; // al
  char *v8; // eax
  int v9; // eax
  int v10; // ecx
  int m_nCmdValue; // edx
  float result; // st7
  float v13; // eax
  char *m_szScriptFile; // edi
  int v15; // ebx
  char *v16; // eax
  _DWORD *p_m_nCmdType; // eax
  int v18; // ecx
  _BYTE *v19; // eax
  float *v20; // ecx
  float *p_m_fPrevPosX; // eax
  float v22; // edx
  _BYTE *v23; // eax
  int *p_m_nMatrixData; // eax
  int *p_m_bRoleLock; // eax
  int v26; // ecx
  float m_fCamZ; // eax
  PalScriptMgr *m_pScriptObjAux; // eax
  int v29; // ecx
  char **v30; // eax
  char *m_pClearResult; // eax
  int v32; // eax
  int v33; // edx
  int v34; // edi
  int v35; // ebx
  int v36; // ebp
  RoleSystem *m_nBlockHandle; // ecx
  int v38; // [esp+0x8] [ebp-0x1BC]
  OpenBaseFile v39; // [esp+0xC] [ebp-0x1B8] BYREF
  int nY; // [esp+0x10] [ebp-0x1B4]
  int p_DWORD; // [esp+0x14] [ebp-0x1B0] BYREF
  float m_fCamX; // [esp+0x18] [ebp-0x1AC]
  float m_fCamY; // [esp+0x1C] [ebp-0x1A8]
  gbMatrix4 v44; // [esp+0x20] [ebp-0x1A4] BYREF
  float v45; // [esp+0x64] [ebp-0x160]
  gbMatrix4 pMatrix; // [esp+0x6C] [ebp-0x158] BYREF
  float v47; // [esp+B0h] [ebp-0x114]
  char Buffer[256]; // [esp+B8h] [ebp-0x10C] BYREF
  int v49; // [esp+0x1C0] [ebp-0x4]

  m_nExecRangeD = this->m_nExecRangeD;
  if ( m_nExecRangeD != 23 || *(_DWORD *)&this->m_nCmdParam0 != 2 )
  {
    if ( m_nExecRangeD != 11 || !this->m_nScriptCount && (v6 = UISceneUpdate(), _strcmpi((const char *)v6, "m02")) )
    {
      v7 = this->m_nExecRangeD;
      if ( v7 != 11 || *(int *)&this->m_nCmdType > 0 )
      {
        if ( v7 == 40 && *(_BYTE *)(LODWORD(thisa) + 74) != BYTE2(this->m_nExecRangeD) )
        {
          (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
          v8 = (((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::NotifyPathEnd(*(unsigned __int8 *)(LODWORD(thisa) + 74));
          this->m_nBlockHandle = (int)v8;
          (((RoleSystem *)*((RoleSystem **)v8 + 4)))->RoleSystem::GetRolePtr(*(unsigned __int8 *)(LODWORD(thisa) + 74));
          v9 = *(unsigned __int8 *)(LODWORD(thisa) + 74);
          if ( *(_BYTE *)(LODWORD(thisa) + 74) )
          {
            v10 = *(_DWORD *)&this->m_nCmdParam0;
            m_nCmdValue = *(_DWORD *)&this->m_nCmdParam1;
          }
          else
          {
            v10 = *(_DWORD *)&this->m_nCmdType;
            m_nCmdValue = this->m_nCmdValue;
          }
          nY = m_nCmdValue;
          p_DWORD = this->m_nTodo_024;
          m_fCamX = this->m_fCamX;
          m_fCamY = this->m_fCamY;
          m_fCamX = (((Scene *)*(_DWORD *)(this->m_nBlockHandle + 16)))->Scene::GetTileHeight(v9, v10, m_nCmdValue, 0);
          this->PalScriptMgr::BuildCmdTransform(&pMatrix);
          result = v47 + m_fCamX;
          v13 = m_fCamY;
          this->m_nTodo_024 = p_DWORD;
          this->m_fCamY = v13;
          this->m_fCamX = result;
          BYTE2(this->m_nExecRangeD) = *(_BYTE *)(LODWORD(thisa) + 74);
          (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
        }
        m_szScriptFile = this->m_szScriptFile;
        v15 = LODWORD(thisa) - (_DWORD)this->m_szScriptFile;
        *(_DWORD *)this->m_szScriptFile = *(_DWORD *)LODWORD(thisa);
        v16 = (char *)&this->m_szScriptFile[4];
        do
        {
          *v16 = v16[v15];
          ++v16;
        }
        while ( (unsigned int)&v16[-4 - (_DWORD)this->m_szScriptFile] < 0x20 );
        LOBYTE(this->m_nSavedBlockNum) = *(_BYTE *)(LODWORD(thisa) + 36);
        BYTE1(this->m_nSavedBlockNum) = *(_BYTE *)(LODWORD(thisa) + 37);
        *(_DWORD *)&this->m_pTodo_84 = *(_DWORD *)(LODWORD(thisa) + 40);
        this->m_nExecuteBlock = *(_DWORD *)(LODWORD(thisa) + 44);
        this->m_nSavedDataA = *(_DWORD *)(LODWORD(thisa) + 48);
        this->m_nSavedDataB = *(_DWORD *)(LODWORD(thisa) + 52);
        this->m_fAngle = *(float *)(LODWORD(thisa) + 56);
        this->m_nExecRangeA = *(_DWORD *)(LODWORD(thisa) + 60);
        this->m_nExecRangeB = *(_DWORD *)(LODWORD(thisa) + 64);
        this->m_nExecRangeC = *(_DWORD *)(LODWORD(thisa) + 68);
        LOBYTE(this->m_nExecRangeD) = *(_BYTE *)(LODWORD(thisa) + 72);
        BYTE1(this->m_nExecRangeD) = *(_BYTE *)(LODWORD(thisa) + 73);
        BYTE2(this->m_nExecRangeD) = *(_BYTE *)(LODWORD(thisa) + 74);
        HIBYTE(this->m_nExecRangeD) = *(_BYTE *)(LODWORD(thisa) + 75);
        p_m_nCmdType = (_DWORD *)&this->m_nCmdType;
        v18 = 6;
        do
        {
          *p_m_nCmdType = *(_DWORD *)((char *)p_m_nCmdType + v15);
          ++p_m_nCmdType;
          --v18;
        }
        while ( v18 );
        LOBYTE(this->m_pRoleSystemCache) = *(_BYTE *)(LODWORD(thisa) + 100);
        HIWORD(this->m_pRoleSystemCache) = *(_WORD *)(LODWORD(thisa) + 102);
        *(_WORD *)&this->m_nTodo_110 = *(_WORD *)(LODWORD(thisa) + 104);
        this->m_nTodo_112 = *(_WORD *)(LODWORD(thisa) + 106);
        this->m_Actor = *(_WORD *)(LODWORD(thisa) + 108);
        LOBYTE(this->m_nTodo_116) = *(_BYTE *)(LODWORD(thisa) + 110);
        v19 = (char *)&this->m_nTodo_116 + 1;
        do
        {
          *v19 = v19[v15];
          ++v19;
        }
        while ( (unsigned int)&v19[-111 - (_DWORD)m_szScriptFile] < 0x10 );
        this->m_nScriptCount = *(_DWORD *)(LODWORD(thisa) + 128);
        this->m_pScriptObjAux = ((PalScriptMgr *)(*(PalScriptMgr **)(LODWORD(thisa) + 132)));
        v20 = (float *)(LODWORD(thisa) + 136);
        p_m_fPrevPosX = (float *)&this->m_fPrevPosX;
        v38 = 16;
        v39.m_plastsys = (gbVFileSystem *)(LODWORD(thisa) + 132 - (_DWORD)&this->m_pScriptObjAux);
        do
        {
          v22 = *v20;
          v20 += 3;
          *(p_m_fPrevPosX - 1) = v22;
          *p_m_fPrevPosX = *(float *)((char *)&v39.m_plastsys->IsInit + (unsigned int)p_m_fPrevPosX);
          p_m_fPrevPosX[1] = *(v20 - 1);
          p_m_fPrevPosX += 3;
          --v38;
        }
        while ( v38 );
        LOWORD(this->m_fSpeed2) = *(_WORD *)(LODWORD(thisa) + 328);
        v23 = (char *)&this->m_fSpeed2 + 2;
        do
        {
          *v23 = v23[v15];
          ++v23;
        }
        while ( (unsigned int)&v23[-330 - (_DWORD)m_szScriptFile] < 0x20 );
        BYTE2(this->m_nTodo_214) = *(_BYTE *)(LODWORD(thisa) + 362);
        (((gbVec3D *)(&this->m_nTodo_214 + 1)))->gbVec3D::operator=(*((const gbVec3D *)(LODWORD(thisa) + 364)));
        (((gbVec3D *)&this->m_fPosAZ))->gbVec3D::operator=(*((const gbVec3D *)(LODWORD(thisa) + 376)));
        this->m_fPosBZ = *(float *)(LODWORD(thisa) + 388);
        p_m_nMatrixData = (int *)&this->m_nMatrixData;
        do
        {
          *(_BYTE *)p_m_nMatrixData = *((_BYTE *)p_m_nMatrixData + v15);
          p_m_nMatrixData = (int *)((char *)p_m_nMatrixData + 1);
        }
        while ( (unsigned int)p_m_nMatrixData - 392 - (unsigned int)m_szScriptFile < 8 );
        this->m_nTodo_238 = *(_DWORD *)(LODWORD(thisa) + 400);
        this->m_bScriptInputBlock = *(_DWORD *)(LODWORD(thisa) + 404);
        this->m_bInputBlock = *(_DWORD *)(LODWORD(thisa) + 408);
        p_m_bRoleLock = (int *)&this->m_bRoleLock;
        v26 = 52;
        do
        {
          *p_m_bRoleLock = *(int *)((char *)p_m_bRoleLock + v15);
          ++p_m_bRoleLock;
          --v26;
        }
        while ( v26 );
        m_fCamZ = this->m_fCamZ;
        *(_QWORD *)&this->m_fCamZ = *(_QWORD *)HIDWORD(thisa);
        *(_QWORD *)&this->m_nFrameCounter = *(_QWORD *)(HIDWORD(thisa) + 8);
        *(_QWORD *)&this->m_pBigMapSce = *(_QWORD *)(HIDWORD(thisa) + 16);
        this->m_fPosZ = *(float *)(HIDWORD(thisa) + 24);
        LOWORD(this->m_scepath) = *(_WORD *)(HIDWORD(thisa) + 28);
        *(_DWORD *)&this->m_bBigMapState = *(_DWORD *)(HIDWORD(thisa) + 32);
        this->m_fCamZ = m_fCamZ;
        switch ( LOBYTE(this->m_nExecRangeD) )
        {
          case 5:
            if ( *(_DWORD *)&this->m_nCmdType == 1 || *(_BYTE *)(HIDWORD(thisa) + 28) != 3 )
              goto LABEL_31;
            (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
            m_pScriptObjAux = (PalScriptMgr *)this->m_pScriptObjAux;
            v29 = *((_DWORD *)&this->m_pTodo_128 + 3 * (_DWORD)m_pScriptObjAux);
            v30 = (char **)(&this->m_pTodo_128 + 3 * (_DWORD)m_pScriptObjAux);
            this->m_nTodo_024 = v29;
            LODWORD(this->m_fCamX) = (unsigned long)v30[1];
            LODWORD(this->m_fCamY) = (unsigned long)v30[2];
            (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
            LOBYTE(this->m_scepath) = *(_BYTE *)(HIDWORD(thisa) + 28);
            goto LABEL_78;
          case 7:
            m_pClearResult = (char *)this->m_pClearResult;
            v39.m_plastsys = (gbVFileSystem *)this->m_nSavedDataB;
            this->m_nSavedDataB = (int)m_pClearResult;
            (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
            this->m_nSavedDataB = (int)v39.m_plastsys;
            break;
          case 0xB:
          case 0x22:
LABEL_31:
            (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
            this->m_nTodo_024 = *(_DWORD *)&this->m_pTodo_84;
            LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
            LODWORD(this->m_fCamY) = this->m_nSavedDataA;
            break;
          case 0xC:
            if ( !this->m_szScriptFile[1] )
              break;
            goto LABEL_78;
          case 0x11:
            if ( this->m_nCmdValue && LOBYTE(this->m_scepath) == 1 && this->m_scriptAux == 3 )
              goto LABEL_39;
            goto LABEL_78;
          case 0x13:
            if ( LOBYTE(this->m_scepath) == 1 )
            {
LABEL_39:
              (*(void ( **)(gbVisNode *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
                this->m_pScriptObjMain,
                -1082130432);
              (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(0.0);
            }
            goto LABEL_78;
          case 0x16:
            if ( *(_BYTE *)(HIDWORD(thisa) + 28) == 2 )
            {
              result = (float)*(int *)&this->m_nCmdType;
              v32 = this->m_nCmdValue;
              BYTE1(this->m_nSavedBlockNum) = 1;
              this->m_fCamX = result;
              if ( v32 )
                (((RoleSystem *)this))->RoleSystem::UpdateStateMode() /* [ROWTABLE] */;
              LOBYTE(this->m_scepath) = *(_BYTE *)(HIDWORD(thisa) + 28);
              this->PalScriptMgr::ProcessRoleLoading();
            }
            goto LABEL_78;
          case 0x17:
            if ( !this->m_szScriptFile[2] )
            {
              (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(0.0);
              (*(void ( **)(gbVisNode *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
                this->m_pScriptObjMain,
                -1082130432);
              (((PalScript *)&this->m_scriptAux))->PalScript::GetCount(0);
            }
            if ( *(_DWORD *)&this->m_nCmdType && this->m_szScriptFile[3] )
            {
              (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(0.0);
              (*(void ( **)(gbVisNode *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
                this->m_pScriptObjMain,
                -1082130432);
              (((PalScript *)&this->m_scriptAux))->PalScript::GetCount(0);
            }
            if ( *(_DWORD *)&this->m_nCmdParam0 == 1 )
            {
              LOBYTE(g_ScriptSystemData.m_nScriptFlag) = this->m_szScriptFile[3] == 0;
              (((ScriptVM *)this))->ScriptVM::OpenSceneScript();
              v34 = 0;
              v35 = *(_DWORD *)(this->m_nBlockHandle + 16);
              if ( *(int *)(v35 + 220) > 0 )
              {
                v36 = v35 + 224;
                do
                {
                  if ( *(_BYTE *)(v36 + 244) == 37 )
                    (((PalScriptMgr *)v36))->PalScriptMgr::LoadSceneGeometry(g_ScriptSystemData.m_nScriptFlag);
                  ++v34;
                  v36 += 896;
                }
                while ( v34 < *(_DWORD *)(v35 + 220) );
              }
            }
            goto LABEL_78;
          case 0x18:
            if ( this->m_nCmdValue == 1 )
            {
              v33 = *(_DWORD *)&this->m_nCmdType;
              m_fCamX = 0.0f;
              m_fCamY = 0.0f;
              p_DWORD = v33;
              if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD) )
                this->m_szScriptFile[1] = 0;
            }
            goto LABEL_78;
          case 0x1A:
            if ( *(_BYTE *)(HIDWORD(thisa) + 28) != 1 )
              goto LABEL_78;
            if ( BYTE1(this->m_scepath) >= 3u )
            {
              sprintf(
                Buffer,
                "object\\wz20_%d.cvd",
                *((char *)&this->m_pVarContext + strlen((const char *)&this->m_szScriptFile[4]) + 3) - 48);
              v49 = 0;
              (((GeomNode *)&this->m_scriptAux))->GeomNode::InitFromFile((const gbGeomNode *)Buffer, 0);
              v49 = -1;
              ((OpenNULLFile *)&v39)->OpenNULLFile::OpenNULLFile();
            }
            (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(0.0);
            (*(void ( **)(gbVisNode *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
              this->m_pScriptObjMain,
              -1082130432);
            (((PalScript *)&this->m_scriptAux))->PalScript::GetCount(0);
            break;
          case 0x1E:
            if ( LOBYTE(this->m_scepath) == 3 )
            {
              this->PalScriptMgr::BuildCmdTransform(&v44);
              result = this->m_fCamX - v45;
              this->m_fCamX = result;
            }
            BYTE1(this->m_nSavedBlockNum) = this->m_szScriptFile[3];
            goto LABEL_78;
          case 0x1F:
            if ( (!this->m_szScriptFile[1] || LOBYTE(this->m_scepath) == 2)
              && !_strcmpi(*(const char **)(this->m_nBlockHandle + 16), "m09") )
            {
              (((RoleSystem *)this))->RoleSystem::SetTileTypeVisible(2, 1) /* [ROWTABLE] */;
            }
            goto LABEL_78;
          case 0x21:
            this->m_nTodo_024 = *(_DWORD *)&this->m_pTodo_84;
            LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
            LODWORD(this->m_fCamY) = this->m_nSavedDataA;
            goto LABEL_78;
          case 0x24:
            if ( LOBYTE(this->m_scepath) != 2 )
              goto LABEL_78;
            this->m_nTodo_024 = *(_DWORD *)&this->m_pTodo_84;
            LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
            LODWORD(this->m_fCamY) = this->m_nSavedDataA;
            m_nBlockHandle = (RoleSystem *)this->m_nBlockHandle;
            BYTE1(this->m_nSavedBlockNum) = 0;
            (((RoleSystem *)m_nBlockHandle))->RoleSystem::GetCurrentID((int *)&this->m_fAngle, 255);
            break;
          case 0x29:
            if ( *(_BYTE *)(HIDWORD(thisa) + 28) != 2 )
              goto LABEL_78;
            (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(0.0);
            (*(void ( **)(gbVisNode *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
              this->m_pScriptObjMain,
              -1082130432);
            (((PalScript *)&this->m_scriptAux))->PalScript::GetCount(0);
            break;
          default:
            goto LABEL_78;
        }
        (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
LABEL_78:
        if ( this->m_bInputBlock )
        {
          this->m_nTodo_024 = *(_DWORD *)&this->m_pTodo_84;
          LODWORD(this->m_fCamX) = this->m_nExecuteBlock;
          LODWORD(this->m_fCamY) = this->m_nSavedDataA;
        }
      }
    }
  }
  return result;
}

// 0x0042BEA0
void PalScriptMgr::OnAnimFinish()
{
  if ( this->m_scriptAux == 3 )
  {
    (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(2.0);
    (*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
      this->m_pScriptObjMain,
      0);
    LOBYTE(this->m_scepath) = 2;
    this->PalScriptMgr::RunCommand(0);
  }
}

// 0x0042BEF0
void PalScriptMgr::HandleGetItem(int nSkillGDBID)
{
  char *v1; // eax
  CScreenMode *Instance; // eax
  int v3; // [esp-0x4] [ebp-0x110]
  int pConfig; // [esp+0x0] [ebp-0x10C] BYREF
  int v5; // [esp+0x4] [ebp-0x108]
  int SkillNum; // [esp+0x8] [ebp-0x104]
  char Buffer[256]; // [esp+0xC] [ebp-0x100] BYREF

  pConfig = nSkillGDBID;
  v5 = 1;
  SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(nSkillGDBID);
  if ( SkillNum )
  {
    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&pConfig);
    v3 = SkillNum + 4;
    v1 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getitem");
    _snprintf(Buffer, 0xFFu, v1, v3, pConfig, v5);
    InputSystem::ProcessFrame(Buffer);
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa006", 1);
  }
}

// 0x0042BF90
PalScriptMgr * PalScriptMgr::ExecuteScriptByID()
{
  __int16 m_fSpeed2_low; // ax
  ScriptVM *v2; // eax
  PalScriptMgr *v3; // esi

  m_fSpeed2_low = LOWORD(this->m_fSpeed2);
  if ( m_fSpeed2_low == -1 )
    return 0;
  (((PalScript *)*(PalScript **)(this->m_nBlockHandle + 16)))->PalScript::SetAction(m_fSpeed2_low);
  v3 = (PalScriptMgr *)v2;
  if ( !v2 )
    return 0;
  (((ScriptVM *)v2))->ScriptVM::ExecuteBlock();
  return v3;
}

// 0x0042BFE0
bool PalScriptMgr::IsScriptReady()
{
  int v2; // ecx

  if ( BYTE1(this->m_scepath) )
  {
    if ( BYTE1(this->m_scepath) == 1 )
      return *(_DWORD *)&this->m_bRoleCmd == 2;
    else
      return BYTE1(this->m_scepath) != 2 || *(_DWORD *)&this->m_bRoleCmd == 3;
  }
  else
  {
    v2 = *(_DWORD *)&this->m_bRoleCmd;
    return v2 == 2 || v2 == 3;
  }
}

// 0x0042C030
void PalScriptMgr::SetPauseState(int bPause)
{
  float v3; // st7
  gbMatrix4 pMatrix; // [esp+0x4] [ebp-0x4C] BYREF
  float v5; // [esp+0x48] [ebp-0x8]

  if ( bPause != (unsigned __int8)this->m_szScriptFile[3] )
  {
    this->m_szScriptFile[3] = bPause;
    if ( (_BYTE)bPause )
      LOBYTE(this->m_scepath) = 1;
    else
      LOBYTE(this->m_scepath) = 2;
    *(_DWORD *)&this->m_bBigMapState = 0;
    this->m_nTodo_0034 = this->m_nTodo_024;
    this->m_nFrameCounter = LODWORD(this->m_fCamX);
    this->m_fPauseCamY = this->m_fCamY;
    this->PalScriptMgr::BuildCmdTransform(&pMatrix);
    v3 = v5 - 2.0f;
    BYTE1(this->m_nSavedBlockNum) = this->m_szScriptFile[3];
    *(float *)&this->m_pBigMapSce = v3;
    this->PalScriptMgr::RunCommand(0);
  }
}

// 0x0042C280
gbVFileSystem * PalScriptMgr::LoadSceneGeometry(char bNoPol)
{
  int v3; // ecx
  gbVFileSystem *result; // eax
  char v5; // [esp+0x7] [ebp-0x115] BYREF
  OpenSceneFile v6; // [esp+0x8] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0xC] [ebp-0x110] BYREF
  int v8; // [esp+0x118] [ebp-0x4]

  if ( this->m_scriptAux )
    (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
  sprintf(Buffer, "%s%s", "scene\\", *(const char **)(this->m_nBlockHandle + 16));
  v3 = *(_DWORD *)(this->m_nBlockHandle + 16);
  v8 = 0;
  sprintf(Buffer, "%s\\%s", (const char *)(v3 + 64), &this->m_szScriptFile[4]);
  if ( !bNoPol )
    strcpy(&v5 + strlen((const char *)Buffer), a2Pol);
  (((GeomNode *)&this->m_scriptAux))->GeomNode::InitFromFile((const gbGeomNode *)Buffer, 0);
  (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
  BYTE1(this->m_nSavedBlockNum) = bNoPol;
  v8 = -1;
  (((OpenSceneFile *)&v6))->OpenSceneFile::~OpenSceneFile();
  return result;
}

// 0x0042C3A0
bool PalScriptMgr::IsInputBlocked()
{
  bool result; // al

  if ( this->m_bScriptInputBlock || this->m_bInputBlock )
    return 1;
  switch ( LOBYTE(this->m_nExecRangeD) )
  {
    case 0:
      result = UIScene::ProcessInput("m22", pszName2);
      break;
    case 1:
    case 2:
    case 3:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x12:
    case 0x15:
    case 0x19:
    case 0x1B:
    case 0x2A:
    case 0x2B:
      result = 0;
      break;
    case 0x11:
      result = this->m_nCmdValue == 1;
      break;
    default:
      return 1;
  }
  return result;
}

// 0x0042C440
void PalScriptMgr::RunCommand(int a1)
{
  const char *p_m_nMatrixData; // edi
  int m_scriptAux; // ecx
  CScreenMode *Instance; // eax
  _DWORD pData[4]; // [esp+0x8] [ebp-0x10] BYREF

  memset(pData, 0, sizeof(pData));
  p_m_nMatrixData = (const char *)&this->m_nMatrixData;
  if ( !LOBYTE(this->m_nMatrixData) )
  {
    switch ( LOBYTE(this->m_nExecRangeD) )
    {
      case 3:
        goto LABEL_4;
      case 4:
        m_scriptAux = this->m_scriptAux;
        if ( m_scriptAux != 3 )
          goto LABEL_20;
LABEL_4:
        p_m_nMatrixData = (const char *)"wg006";
        break;
      case 6:
        p_m_nMatrixData = (const char *)"wg007";
        break;
      case 7:
        p_m_nMatrixData = (const char *)"wg004";
        break;
      case 0xB:
        p_m_nMatrixData = (const char *)"We025";
        break;
      case 0xC:
        switch ( *(_DWORD *)&this->m_nCmdType )
        {
          case 0:
            p_m_nMatrixData = (const char *)"We026";
            goto LABEL_30;
          case 1:
            p_m_nMatrixData = (const char *)"We027";
            goto LABEL_30;
          case 2:
            p_m_nMatrixData = (const char *)"We028";
            goto LABEL_30;
          case 3:
            p_m_nMatrixData = (const char *)"We029";
            goto LABEL_30;
          case 4:
            p_m_nMatrixData = (const char *)"We030";
            goto LABEL_30;
          default:
            goto LABEL_31;
        }
        goto LABEL_31;
      case 0xD:
        p_m_nMatrixData = (const char *)"Wb002";
        break;
      case 0x13:
        p_m_nMatrixData = (const char *)"Wg001";
        break;
      case 0x16:
      case 0x1E:
        goto LABEL_24;
      case 0x1A:
        if ( a1 )
          goto LABEL_29;
        p_m_nMatrixData = (const char *)"wa004";
        break;
      case 0x1C:
        m_scriptAux = this->m_scriptAux;
        if ( m_scriptAux == 3 )
        {
          p_m_nMatrixData = (const char *)"wg010";
          break;
        }
LABEL_20:
        if ( m_scriptAux != 2 )
          goto LABEL_31;
LABEL_21:
        p_m_nMatrixData = (const char *)"wg009";
        break;
      case 0x1D:
        if ( a1 )
          p_m_nMatrixData = (const char *)"We026";
        else
LABEL_24:
          p_m_nMatrixData = (const char *)"Wg005";
        break;
      case 0x1F:
        p_m_nMatrixData = (const char *)"Wc007";
        break;
      case 0x20:
        p_m_nMatrixData = (const char *)"WG008";
        break;
      case 0x22:
        p_m_nMatrixData = (const char *)"wg005";
        break;
      case 0x24:
        goto LABEL_21;
      case 0x27:
        p_m_nMatrixData = (const char *)"wc014";
        break;
      case 0x29:
LABEL_29:
        p_m_nMatrixData = (const char *)"wg011";
        break;
      default:
        goto LABEL_31;
    }
  }
LABEL_30:
  strcpy((char *)pData, p_m_nMatrixData);
LABEL_31:
  if ( LOBYTE(pData[0]) )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(pData, 1);
  }
}

// 0x0042CF60
int PalScriptMgr::CmdPushCmd04(int nVal, unsigned __int8 pData)
{
  int *p_m_nSavedPosX; // ebx
  int v5; // eax
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v9; // esi
  _DWORD *v10; // eax
  float v11; // ecx
  float v12; // edx
  float x; // eax
  int v14; // esi
  unsigned int v15; // eax
  _DWORD *v16; // eax
  float v17; // edx
  float v18; // ecx
  int v19; // edx
  int v20; // edi
  gbVec3D *RoleName; // eax
  int *v22; // edi
  float y; // ecx
  float z; // eax
  int v25; // ecx
  int v26; // ecx
  gbVec3D v27; // [esp+0xC] [ebp-0x5C] BYREF
  int v28; // [esp+0x18] [ebp-0x50]
  _DWORD v29[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v29))->CG_Entry::GetCGEntry();
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  v29[15] = pData;
  LOBYTE(v29[0]) = 4;
  v5 = *((_DWORD *)&this->m_pWaitObj + 1);
  v29[16] = nVal;
  if ( !v5
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v9 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v15 = (unsigned long)p_m_nSavedPosX[8];
      if ( v15 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v20 = ((int)(v15 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v20);
        v22 = (int *)(&RoleName->x + v20);
        *v22 = (int)v9;
        (((gbVec3D *)&v27))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v27.y;
        p_m_nSavedPosX[1] = LODWORD(v27.x);
        z = v27.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v25 = v28;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v25;
        v26 = (unsigned long)(*v22 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v22;
        p_m_nSavedPosX[6] = v26;
        p_m_nSavedPosX[7] = (int)v9;
        p_m_nSavedPosX[8] = (int)v22;
      }
      else
      {
        v16 = (_DWORD *)(v15 + 4);
        p_m_nSavedPosX[8] = (int)v16;
        *v16 = (_DWORD)v9;
        (((gbVec3D *)&v27))->gbVec3D::Copy((int)v9, (gbVec3D *)p_m_nSavedPosX[8]);
        v17 = v27.y;
        p_m_nSavedPosX[5] = LODWORD(v27.x);
        v18 = v27.z;
        *((float *)p_m_nSavedPosX + 6) = v17;
        v19 = v28;
        *((float *)p_m_nSavedPosX + 7) = v18;
        p_m_nSavedPosX[8] = v19;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v10 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v10;
      v10[1] = (_DWORD)v9;
      (((gbVec3D *)&v27))->gbVec3D::Copy((int)v9 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      v11 = v27.y;
      v12 = v27.z;
      x = v27.x;
      v14 = v28;
      p_m_nSavedPosX[1] = LODWORD(v27.x);
      *((float *)p_m_nSavedPosX + 2) = v11;
      *((float *)p_m_nSavedPosX + 3) = v12;
      p_m_nSavedPosX[4] = v14;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v11;
      *((float *)p_m_nSavedPosX + 7) = v12;
      p_m_nSavedPosX[8] = v14;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v29, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v29, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042D130
int PalScriptMgr::CmdPushCmd05(unsigned __int8 pData)
{
  int *p_m_nSavedPosX; // ebx
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // ecx
  int v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // edx
  float v16; // ecx
  int v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // ecx
  float z; // eax
  int v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  LOBYTE(v27[0]) = 5;
  v27[15] = pData;
  if ( !*((_DWORD *)&this->m_pWaitObj + 1)
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v13 = (unsigned long)p_m_nSavedPosX[8];
      if ( v13 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v25.y;
        p_m_nSavedPosX[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v23 = v26;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v20;
        p_m_nSavedPosX[6] = v24;
        p_m_nSavedPosX[7] = (int)v7;
        p_m_nSavedPosX[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nSavedPosX[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nSavedPosX[8]);
        v15 = v25.y;
        p_m_nSavedPosX[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nSavedPosX + 6) = v15;
        v17 = v26;
        *((float *)p_m_nSavedPosX + 7) = v16;
        p_m_nSavedPosX[8] = v17;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_nSavedPosX[1] = LODWORD(v25.x);
      *((float *)p_m_nSavedPosX + 2) = v10;
      *((float *)p_m_nSavedPosX + 3) = v12;
      p_m_nSavedPosX[4] = v11;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v10;
      *((float *)p_m_nSavedPosX + 7) = v12;
      p_m_nSavedPosX[8] = v11;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042D2F0
int PalScriptMgr::CmdPushCmd07(unsigned __int8 pData)
{
  int *p_m_nSavedPosX; // ebx
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // ecx
  int v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // edx
  float v16; // ecx
  int v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // ecx
  float z; // eax
  int v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  LOBYTE(v27[0]) = 7;
  v27[15] = pData;
  if ( !*((_DWORD *)&this->m_pWaitObj + 1)
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v13 = (unsigned long)p_m_nSavedPosX[8];
      if ( v13 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v25.y;
        p_m_nSavedPosX[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v23 = v26;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v20;
        p_m_nSavedPosX[6] = v24;
        p_m_nSavedPosX[7] = (int)v7;
        p_m_nSavedPosX[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nSavedPosX[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nSavedPosX[8]);
        v15 = v25.y;
        p_m_nSavedPosX[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nSavedPosX + 6) = v15;
        v17 = v26;
        *((float *)p_m_nSavedPosX + 7) = v16;
        p_m_nSavedPosX[8] = v17;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_nSavedPosX[1] = LODWORD(v25.x);
      *((float *)p_m_nSavedPosX + 2) = v10;
      *((float *)p_m_nSavedPosX + 3) = v12;
      p_m_nSavedPosX[4] = v11;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v10;
      *((float *)p_m_nSavedPosX + 7) = v12;
      p_m_nSavedPosX[8] = v11;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042D830
int PalScriptMgr::CmdPushCmd10(unsigned __int8 pData)
{
  int *p_m_nSavedPosX; // ebx
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // ecx
  int v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // edx
  float v16; // ecx
  int v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // ecx
  float z; // eax
  int v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  LOBYTE(v27[0]) = 10;
  v27[15] = pData;
  if ( !*((_DWORD *)&this->m_pWaitObj + 1)
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v13 = (unsigned long)p_m_nSavedPosX[8];
      if ( v13 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v25.y;
        p_m_nSavedPosX[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v23 = v26;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v20;
        p_m_nSavedPosX[6] = v24;
        p_m_nSavedPosX[7] = (int)v7;
        p_m_nSavedPosX[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nSavedPosX[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nSavedPosX[8]);
        v15 = v25.y;
        p_m_nSavedPosX[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nSavedPosX + 6) = v15;
        v17 = v26;
        *((float *)p_m_nSavedPosX + 7) = v16;
        p_m_nSavedPosX[8] = v17;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_nSavedPosX[1] = LODWORD(v25.x);
      *((float *)p_m_nSavedPosX + 2) = v10;
      *((float *)p_m_nSavedPosX + 3) = v12;
      p_m_nSavedPosX[4] = v11;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v10;
      *((float *)p_m_nSavedPosX + 7) = v12;
      p_m_nSavedPosX[8] = v11;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042DF30
int PalScriptMgr::CmdPushCmd14(int nVal, unsigned __int8 pData)
{
  int *p_m_nSavedPosX; // ebx
  int v5; // eax
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v9; // esi
  _DWORD *v10; // eax
  float v11; // ecx
  float v12; // edx
  float x; // eax
  int v14; // esi
  unsigned int v15; // eax
  _DWORD *v16; // eax
  float v17; // edx
  float v18; // ecx
  int v19; // edx
  int v20; // edi
  gbVec3D *RoleName; // eax
  int *v22; // edi
  float y; // ecx
  float z; // eax
  int v25; // ecx
  int v26; // ecx
  gbVec3D v27; // [esp+0xC] [ebp-0x5C] BYREF
  int v28; // [esp+0x18] [ebp-0x50]
  _DWORD v29[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v29))->CG_Entry::GetCGEntry();
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  v29[15] = nVal;
  LOBYTE(v29[0]) = 14;
  v5 = *((_DWORD *)&this->m_pWaitObj + 1);
  v29[16] = pData;
  if ( !v5
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v9 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v15 = (unsigned long)p_m_nSavedPosX[8];
      if ( v15 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v20 = ((int)(v15 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v20);
        v22 = (int *)(&RoleName->x + v20);
        *v22 = (int)v9;
        (((gbVec3D *)&v27))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v27.y;
        p_m_nSavedPosX[1] = LODWORD(v27.x);
        z = v27.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v25 = v28;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v25;
        v26 = (unsigned long)(*v22 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v22;
        p_m_nSavedPosX[6] = v26;
        p_m_nSavedPosX[7] = (int)v9;
        p_m_nSavedPosX[8] = (int)v22;
      }
      else
      {
        v16 = (_DWORD *)(v15 + 4);
        p_m_nSavedPosX[8] = (int)v16;
        *v16 = (_DWORD)v9;
        (((gbVec3D *)&v27))->gbVec3D::Copy((int)v9, (gbVec3D *)p_m_nSavedPosX[8]);
        v17 = v27.y;
        p_m_nSavedPosX[5] = LODWORD(v27.x);
        v18 = v27.z;
        *((float *)p_m_nSavedPosX + 6) = v17;
        v19 = v28;
        *((float *)p_m_nSavedPosX + 7) = v18;
        p_m_nSavedPosX[8] = v19;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v10 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v10;
      v10[1] = (_DWORD)v9;
      (((gbVec3D *)&v27))->gbVec3D::Copy((int)v9 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      v11 = v27.y;
      v12 = v27.z;
      x = v27.x;
      v14 = v28;
      p_m_nSavedPosX[1] = LODWORD(v27.x);
      *((float *)p_m_nSavedPosX + 2) = v11;
      *((float *)p_m_nSavedPosX + 3) = v12;
      p_m_nSavedPosX[4] = v14;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v11;
      *((float *)p_m_nSavedPosX + 7) = v12;
      p_m_nSavedPosX[8] = v14;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v29, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v29, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042E100
int PalScriptMgr::CmdPushCmd15(unsigned __int8 pData)
{
  int *p_m_nSavedPosX; // ebx
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v7; // esi
  _DWORD *v8; // eax
  float x; // eax
  float v10; // ecx
  int v11; // esi
  float v12; // edx
  unsigned int v13; // eax
  _DWORD *v14; // eax
  float v15; // edx
  float v16; // ecx
  int v17; // edx
  int v18; // edi
  gbVec3D *RoleName; // eax
  int *v20; // edi
  float y; // ecx
  float z; // eax
  int v23; // ecx
  int v24; // ecx
  gbVec3D v25; // [esp+0xC] [ebp-0x5C] BYREF
  int v26; // [esp+0x18] [ebp-0x50]
  _DWORD v27[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v27))->CG_Entry::GetCGEntry();
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  LOBYTE(v27[0]) = 15;
  v27[15] = pData;
  if ( !*((_DWORD *)&this->m_pWaitObj + 1)
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v7 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v13 = (unsigned long)p_m_nSavedPosX[8];
      if ( v13 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v18 = ((int)(v13 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v18);
        v20 = (int *)(&RoleName->x + v18);
        *v20 = (int)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v25.y;
        p_m_nSavedPosX[1] = LODWORD(v25.x);
        z = v25.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v23 = v26;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v23;
        v24 = (unsigned long)(*v20 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v20;
        p_m_nSavedPosX[6] = v24;
        p_m_nSavedPosX[7] = (int)v7;
        p_m_nSavedPosX[8] = (int)v20;
      }
      else
      {
        v14 = (_DWORD *)(v13 + 4);
        p_m_nSavedPosX[8] = (int)v14;
        *v14 = (_DWORD)v7;
        (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7, (gbVec3D *)p_m_nSavedPosX[8]);
        v15 = v25.y;
        p_m_nSavedPosX[5] = LODWORD(v25.x);
        v16 = v25.z;
        *((float *)p_m_nSavedPosX + 6) = v15;
        v17 = v26;
        *((float *)p_m_nSavedPosX + 7) = v16;
        p_m_nSavedPosX[8] = v17;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v8 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v8;
      v8[1] = (_DWORD)v7;
      (((gbVec3D *)&v25))->gbVec3D::Copy((int)v7 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      x = v25.x;
      v10 = v25.y;
      v11 = v26;
      v12 = v25.z;
      p_m_nSavedPosX[1] = LODWORD(v25.x);
      *((float *)p_m_nSavedPosX + 2) = v10;
      *((float *)p_m_nSavedPosX + 3) = v12;
      p_m_nSavedPosX[4] = v11;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v10;
      *((float *)p_m_nSavedPosX + 7) = v12;
      p_m_nSavedPosX[8] = v11;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v27, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042E2C0
char * PalScriptMgr::CmdCameraOrbitPos(
        
        int nVal,
        float fVal,
        float fVal2,
        unsigned __int8 pData)
{
  float *v6; // eax
  int *p_m_nSavedPosX; // ebx
  int v8; // eax
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  char *result; // eax
  void *v12; // esi
  _DWORD *v13; // eax
  float v14; // ecx
  float v15; // edx
  float x; // eax
  int v17; // esi
  unsigned int v18; // eax
  _DWORD *v19; // eax
  float v20; // edx
  float v21; // ecx
  int v22; // edx
  int v23; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v25; // edi
  float y; // ecx
  float z; // eax
  int v28; // ecx
  float v29; // ecx
  float v30; // eax
  int v31; // ecx
  gbVec3D v32; // [esp+0xC] [ebp-0x5C] BYREF
  int v33; // [esp+0x18] [ebp-0x50]
  _DWORD v34[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v34))->CG_Entry::GetCGEntry();
  LOBYTE(v34[0]) = 16;
  v6 = (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::CalcOrbitalPos((float *)&nVal, *(float *)&nVal, fVal, fVal2);
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  *(float *)&v34[3] = (unsigned long)*v6;
  *(float *)&v34[4] = (unsigned long)v6[1];
  *(float *)&v34[5] = (unsigned long)v6[2];
  v8 = *((_DWORD *)&this->m_pWaitObj + 1);
  v34[15] = pData;
  if ( !v8
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v12 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v18 = (unsigned long)p_m_nSavedPosX[8];
      if ( v18 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v23 = ((int)(v18 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v23);
        v25 = (gbVec3D *)((char *)RoleName + 4 * v23);
        LODWORD(v25->x) = (unsigned long)v12;
        (((gbVec3D *)&v32))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v32.y;
        p_m_nSavedPosX[1] = LODWORD(v32.x);
        z = v32.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v28 = v33;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v28;
        (((gbVec3D *)&v32))->gbVec3D::Copy((int)v12, v25);
        v29 = v32.y;
        p_m_nSavedPosX[5] = LODWORD(v32.x);
        v30 = v32.z;
        *((float *)p_m_nSavedPosX + 6) = v29;
        v31 = v33;
        *((float *)p_m_nSavedPosX + 7) = v30;
        p_m_nSavedPosX[8] = v31;
      }
      else
      {
        v19 = (_DWORD *)(v18 + 4);
        p_m_nSavedPosX[8] = (int)v19;
        *v19 = (_DWORD)v12;
        (((gbVec3D *)&v32))->gbVec3D::Copy((int)v12, (gbVec3D *)p_m_nSavedPosX[8]);
        v20 = v32.y;
        p_m_nSavedPosX[5] = LODWORD(v32.x);
        v21 = v32.z;
        *((float *)p_m_nSavedPosX + 6) = v20;
        v22 = v33;
        *((float *)p_m_nSavedPosX + 7) = v21;
        p_m_nSavedPosX[8] = v22;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v13 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v13;
      v13[1] = (_DWORD)v12;
      (((gbVec3D *)&v32))->gbVec3D::Copy((int)v12 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      v14 = v32.y;
      v15 = v32.z;
      x = v32.x;
      v17 = v33;
      p_m_nSavedPosX[1] = LODWORD(v32.x);
      *((float *)p_m_nSavedPosX + 2) = v14;
      *((float *)p_m_nSavedPosX + 3) = v15;
      p_m_nSavedPosX[4] = v17;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v14;
      *((float *)p_m_nSavedPosX + 7) = v15;
      p_m_nSavedPosX[8] = v17;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (char *)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = (int)result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v34, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v34, 0x4Cu);
  result = (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  ++*((_DWORD *)&this->m_pWaitObj + 1);
  return result;
}

// 0x0042E4D0
int PalScriptMgr::CmdRoleMoveSmooth(int nVal, unsigned __int8 pData)
{
  int *p_m_nSavedPosX; // ebx
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v8; // esi
  _DWORD *v9; // eax
  float x; // eax
  float v11; // ecx
  int v12; // esi
  float v13; // edx
  unsigned int v14; // eax
  _DWORD *v15; // eax
  float v16; // edx
  float v17; // ecx
  int v18; // edx
  int v19; // edi
  gbVec3D *RoleName; // eax
  int *v21; // edi
  float y; // ecx
  float z; // eax
  int v24; // ecx
  int v25; // ecx
  gbVec3D v26; // [esp+0xC] [ebp-0x5C] BYREF
  int v27; // [esp+0x18] [ebp-0x50]
  _DWORD v28[19]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v28))->CG_Entry::GetCGEntry();
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  v28[15] = nVal;
  LOBYTE(v28[0]) = 18;
  if ( !*((_DWORD *)&this->m_pWaitObj + 1)
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v8 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v14 = (unsigned long)p_m_nSavedPosX[8];
      if ( v14 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v19 = ((int)(v14 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v19);
        v21 = (int *)(&RoleName->x + v19);
        *v21 = (int)v8;
        (((gbVec3D *)&v26))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v26.y;
        p_m_nSavedPosX[1] = LODWORD(v26.x);
        z = v26.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v24 = v27;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v24;
        v25 = (unsigned long)(*v21 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v21;
        p_m_nSavedPosX[6] = v25;
        p_m_nSavedPosX[7] = (int)v8;
        p_m_nSavedPosX[8] = (int)v21;
      }
      else
      {
        v15 = (_DWORD *)(v14 + 4);
        p_m_nSavedPosX[8] = (int)v15;
        *v15 = (_DWORD)v8;
        (((gbVec3D *)&v26))->gbVec3D::Copy((int)v8, (gbVec3D *)p_m_nSavedPosX[8]);
        v16 = v26.y;
        p_m_nSavedPosX[5] = LODWORD(v26.x);
        v17 = v26.z;
        *((float *)p_m_nSavedPosX + 6) = v16;
        v18 = v27;
        *((float *)p_m_nSavedPosX + 7) = v17;
        p_m_nSavedPosX[8] = v18;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v9 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v9;
      v9[1] = (_DWORD)v8;
      (((gbVec3D *)&v26))->gbVec3D::Copy((int)v8 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      x = v26.x;
      v11 = v26.y;
      v12 = v27;
      v13 = v26.z;
      p_m_nSavedPosX[1] = LODWORD(v26.x);
      *((float *)p_m_nSavedPosX + 2) = v11;
      *((float *)p_m_nSavedPosX + 3) = v13;
      p_m_nSavedPosX[4] = v12;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v11;
      *((float *)p_m_nSavedPosX + 7) = v13;
      p_m_nSavedPosX[8] = v12;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v28, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v28, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042E6C0
int PalScriptMgr::CmdRoleMoveDirect(unsigned __int8 pData)
{
  int v3; // eax
  int *p_m_nSavedPosX; // ebx
  float m_fExecPosY; // edi
  float m_fExecParam; // ecx
  int result; // eax
  void *v8; // esi
  _DWORD *v9; // eax
  float x; // eax
  float v11; // edx
  float v12; // ecx
  int v13; // esi
  unsigned int v14; // eax
  _DWORD *v15; // eax
  float v16; // eax
  float v17; // edx
  int v18; // eax
  int v19; // edi
  gbVec3D *RoleName; // eax
  int *v21; // edi
  float y; // edx
  float z; // ecx
  int v24; // edx
  int v25; // ecx
  gbVec3D v26; // [esp+0xC] [ebp-0x5C] BYREF
  int v27; // [esp+0x18] [ebp-0x50]
  char v28[76]; // [esp+0x1C] [ebp-0x4C] BYREF

  (((CG_Entry *)v28))->CG_Entry::GetCGEntry();
  v3 = *((_DWORD *)&this->m_pWaitObj + 1);
  p_m_nSavedPosX = (int *)&this->m_nSavedPosX;
  v28[0] = 19;
  if ( !v3
    || (m_fExecPosY = this->m_fExecPosY, m_fExecParam = this->m_fExecParam,
                                         LODWORD(m_fExecPosY) == LODWORD(m_fExecParam)) )
  {
    v8 = (void *)operator new(0xFBCu);
    if ( p_m_nSavedPosX[11] )
    {
      v14 = (unsigned long)p_m_nSavedPosX[8];
      if ( v14 >= p_m_nSavedPosX[9] + 4 * p_m_nSavedPosX[10] - 4 )
      {
        v19 = ((int)(v14 - p_m_nSavedPosX[4]) >> 2) + 1;
        RoleName = (gbVec3D *)(((RoleSystem *)p_m_nSavedPosX))->RoleSystem::GetRoleName(2 * v19);
        v21 = (int *)(&RoleName->x + v19);
        *v21 = (int)v8;
        (((gbVec3D *)&v26))->gbVec3D::Copy(p_m_nSavedPosX[3], RoleName);
        y = v26.y;
        p_m_nSavedPosX[1] = LODWORD(v26.x);
        z = v26.z;
        *((float *)p_m_nSavedPosX + 2) = y;
        v24 = v27;
        *((float *)p_m_nSavedPosX + 3) = z;
        p_m_nSavedPosX[4] = v24;
        v25 = (unsigned long)(*v21 + 4028);
        p_m_nSavedPosX[5] = (unsigned long)*v21;
        p_m_nSavedPosX[6] = v25;
        p_m_nSavedPosX[7] = (int)v8;
        p_m_nSavedPosX[8] = (int)v21;
      }
      else
      {
        v15 = (_DWORD *)(v14 + 4);
        p_m_nSavedPosX[8] = (int)v15;
        *v15 = (_DWORD)v8;
        (((gbVec3D *)&v26))->gbVec3D::Copy((int)v8, (gbVec3D *)p_m_nSavedPosX[8]);
        v16 = v26.y;
        p_m_nSavedPosX[5] = LODWORD(v26.x);
        v17 = v26.z;
        *((float *)p_m_nSavedPosX + 6) = v16;
        v18 = v27;
        *((float *)p_m_nSavedPosX + 7) = v17;
        p_m_nSavedPosX[8] = v18;
      }
    }
    else
    {
      p_m_nSavedPosX[10] = 2;
      v9 = (_DWORD *)operator new(8u);
      p_m_nSavedPosX[9] = (int)v9;
      v9[1] = (_DWORD)v8;
      (((gbVec3D *)&v26))->gbVec3D::Copy((int)v8 + 1976, (gbVec3D *)(p_m_nSavedPosX[9] + 4));
      x = v26.x;
      v11 = v26.z;
      v12 = v26.y;
      v13 = v27;
      p_m_nSavedPosX[1] = LODWORD(v26.x);
      *((float *)p_m_nSavedPosX + 2) = v12;
      *((float *)p_m_nSavedPosX + 3) = v11;
      p_m_nSavedPosX[4] = v13;
      *((float *)p_m_nSavedPosX + 5) = x;
      *((float *)p_m_nSavedPosX + 6) = v12;
      *((float *)p_m_nSavedPosX + 7) = v11;
      p_m_nSavedPosX[8] = v13;
    }
    m_fExecPosY = *((float *)p_m_nSavedPosX + 7);
    p_m_nSavedPosX[7] = LODWORD(m_fExecPosY) + 76;
    if ( m_fExecPosY == 0.0f )
      goto LABEL_16;
    goto LABEL_15;
  }
  LODWORD(this->m_fExecPosY) = LODWORD(m_fExecPosY) + 76;
  if ( LODWORD(m_fExecPosY) + 76 != LODWORD(m_fExecParam) )
  {
    if ( m_fExecPosY == 0.0f )
    {
LABEL_16:
      result = (unsigned long)(p_m_nSavedPosX[11] + 1);
      p_m_nSavedPosX[11] = result;
      return result;
    }
LABEL_15:
    qmemcpy((void *)LODWORD(m_fExecPosY), v28, 0x4Cu);
    goto LABEL_16;
  }
  if ( m_fExecPosY != 0.0f )
    qmemcpy((void *)LODWORD(m_fExecPosY), v28, 0x4Cu);
  (((ScriptVM *)p_m_nSavedPosX))->ScriptVM::GetString();
  result = *((_DWORD *)&this->m_pWaitObj + 1) + 1;
  *((_DWORD *)&this->m_pWaitObj + 1) = result;
  return result;
}

// 0x0042EBE0
int PalScriptMgr::ExecuteOpcode()
{
  int result; // eax
  unsigned __int8 *m_nScriptCamY; // edi
  PalScriptMgr *p_m_nSavedPosX; // ecx
  int v5; // edx
  int v6; // eax
  unsigned __int8 v7; // al
  int m_nBlockHandle; // ecx
  int v9; // edx
  int v10; // edx
  int v11; // ecx
  char *v12; // eax
  PalScriptMgr **v13; // eax
  PalScriptMgr *v14; // ecx
  RoleSystem *v15; // esi
  CScreenMode *v16; // ecx
  float v17; // eax
  int v18; // edi
  int v19; // edx
  PtrArray *SoundList; // eax
  RoleSystem *v21; // esi
  RoleSystem *v22; // ebx
  int v23; // ebp
  _DWORD *p_m_fMoveParamZ; // edx
  float *p_m_fPrevPosY; // eax
  float v26; // st7
  int RolePtr; // ebx
  float v28; // st7
  float v29; // ebp
  __int64 v30; // rax
  float v31; // st7
  int v32; // ecx
  float z; // ecx
  float v34; // st7
  float v35; // st7
  float v36; // st7
  int v37; // edx
  int v38; // ecx
  char *v39; // eax
  float v40; // eax
  float v41; // edx
  float v42; // ecx
  char *v43; // edi
  float v44; // eax
  float v45; // edx
  char *v46; // eax
  char *v47; // eax
  int v48; // edx
  int v49; // ecx
  char *v50; // eax
  float y; // ecx
  float v52; // edx
  float x; // eax
  char *v54; // edi
  float v55; // edx
  float v56; // ecx
  char *v57; // edx
  void *v58; // [esp-0x4] [ebp-0x8C]
  int m_fDirNeg_low; // [esp-0x4] [ebp-0x8C]
  void *v60; // [esp-0x4] [ebp-0x8C]
  void *m_nExecState2; // [esp-0x4] [ebp-0x8C]
  gbVec3D nVal2; // [esp+0x10] [ebp-0x78] BYREF
  char *v63; // [esp+0x1C] [ebp-0x6C]
  gbVec3D v64; // [esp+0x20] [ebp-0x68] BYREF
  gbVec3D v65; // [esp+0x2C] [ebp-0x5C] BYREF
  char *m_pScriptBlock; // [esp+0x38] [ebp-0x50]
  gbMatrix4 pMatrix; // [esp+0x3C] [ebp-0x4C] BYREF
  float v68; // [esp+0x7C] [ebp-0xC]
  float v69; // [esp+0x84] [ebp-0x4]

  result = *((_DWORD *)&this->m_pWaitObj + 1);
  if ( result )
  {
    while ( 2 )
    {
      LODWORD(v65.x) = (unsigned long)this->m_pSubScriptB;
      LODWORD(v65.y) = this->m_nScriptCamX;
      m_nScriptCamY = (unsigned __int8 *)this->m_nScriptCamY;
      m_pScriptBlock = (char *)this->m_pScriptBlock;
      result = (unsigned long)(*m_nScriptCamY - 2);
      switch ( *m_nScriptCamY )
      {
        case 2u:
          v15 = g_pRoleSystem;
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
          (((RoleSystem *)v15))->RoleSystem::GetMoveState(1);
          (((RoleSystem *)v15))->RoleSystem::SetMoveTarget((float *)m_nScriptCamY + 6, 1);
          return result;
        case 3u:
          this->PalScriptMgr::SetBigMapState(m_nScriptCamY[60]);
          result = *((_DWORD *)m_nScriptCamY + 16);
          goto LABEL_4;
        case 4u:
          (((PalScriptMgr *)*((PalScriptMgr **)m_nScriptCamY + 16)))->PalScriptMgr::Destroy();
          this->m_fDirNeg = v17;
          if ( !*((_DWORD *)m_nScriptCamY + 15) )
          {
            v18 = this->m_nScriptCamY + 76;
            v19 = *((_DWORD *)&this->m_pWaitObj + 1) - 1;
            this->m_nScriptCamY = v18;
            *((_DWORD *)&this->m_pWaitObj + 1) = v19;
            if ( !v19 || v18 == this->m_nScriptCamX )
              (((PalScriptMgr *)&this->m_nSavedPosX))->PalScriptMgr::PopScript();
            this->PalScriptMgr::ExecuteOpcode();
          }
          m_fDirNeg_low = LODWORD(this->m_fDirNeg);
          SoundList = (((CScreenMode *)v16))->CScreenMode::GetSoundList();
          (((PtrArray *)SoundList))->PtrArray::SetResolution(0, m_fDirNeg_low);
          return result;
        case 5u:
          this->PalScriptMgr::ExecuteScriptByID();
          result = *((_DWORD *)m_nScriptCamY + 15);
LABEL_4:
          if ( !result )
            goto LABEL_5;
          return result;
        case 6u:
          v21 = g_pRoleSystem;
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
          return (((RoleSystem *)v21))->RoleSystem::GetActionByIndex(*((_DWORD *)m_nScriptCamY + 15));
        case 7u:
          (*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
            this->m_pScriptObjMain,
            0);
          (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(2.0);
          return result;
        case 8u:
          CameraCtrl::AttachToRole(*((_DWORD *)m_nScriptCamY + 15));
          goto LABEL_5;
        case 9u:
          (((RoleSystem *)this))->RoleSystem::ProcessAction() /* [ROWTABLE] */;
          goto LABEL_5;
        case 0xAu:
          BYTE1(this->m_nSavedBlockNum) = (unsigned long)m_nScriptCamY[60];
          goto LABEL_5;
        case 0xBu:
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::IsPathComplete((float *)m_nScriptCamY + 3, 1);
          goto LABEL_5;
        case 0xCu:
          v22 = g_pRoleSystem;
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
          v23 = 0;
          v22->m_partyUI3.m_pfather = (UIWnd *)((char *)this->m_pScriptObjAux + 1);
          v22->m_fMoveTargetX = v22->m_fPosX;
          v22->m_fMoveTargetY = LODWORD(v22->m_fPosY);
          v22->m_fMoveTargetZ = v22->m_fPosZ;
          if ( (int)this->m_pScriptObjAux > 0 )
          {
            p_m_fMoveParamZ = (_DWORD *)&v22->m_fMoveParamZ;
            p_m_fPrevPosY = (float *)&this->m_fPrevPosY;
            do
            {
              ++v23;
              *(p_m_fMoveParamZ - 2) = *((_DWORD *)p_m_fPrevPosY - 2);
              *(p_m_fMoveParamZ - 1) = *((_DWORD *)p_m_fPrevPosY - 1);
              *p_m_fMoveParamZ = *(_DWORD *)p_m_fPrevPosY;
              p_m_fPrevPosY += 3;
              p_m_fMoveParamZ += 3;
            }
            while ( v23 < (int)this->m_pScriptObjAux );
          }
          (((PathObj *)&v22->m_fMoveTargetX))->PathObj::CalcLength();
          v26 = *(float *)&v22->m_partyUI3.m_childs.m_pData * 0.0016666667070239782f;
          *((_DWORD *)m_nScriptCamY + 2) = 0;
          *((float *)m_nScriptCamY + 1) = v26;
          v22->m_nCoreState = 2;
          (((RoleSystem *)v22))->RoleSystem::UpdateTransform();
          return (((RoleSystem *)v22))->RoleSystem::GetMoveState(1);
        case 0xDu:
          RolePtr = (((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::GetRolePtr(BYTE2(this->m_nExecRangeD));
          v28 = this->m_fCamY - *(float *)(RolePtr + 136);
          LODWORD(v29) = (__int64)((*(float *)&this->m_nTodo_024 - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_fScriptTileSize2);
          nVal2.x = v29;
          v30 = (__int64)(v28 / g_ScriptSystemData.m_fScriptTileSize2);
          v31 = 0.0f;
          LODWORD(nVal2.y) = v30;
          v64.x = ((float)SLODWORD(v29) + 0.5f) * g_ScriptSystemData.m_fScriptTileSize2 + *(float *)(RolePtr + 128);
          v64.z = ((float)(int)v30 + 0.5f) * g_ScriptSystemData.m_fScriptTileSize2 + *(float *)(RolePtr + 136);
          if ( v29 >= 0.0f )
          {
            v32 = *(_DWORD *)(RolePtr + 152);
            if ( SLODWORD(v29) < v32 && (int)v30 >= 0 && (int)v30 < *(_DWORD *)(RolePtr + 156) )
              v31 = *(float *)(*(_DWORD *)(RolePtr + 160) + 8 * (LODWORD(v29) + v30 * v32));
          }
          result = LODWORD(v64.x);
          z = v64.z;
          *((float *)m_nScriptCamY + 4) = v31;
          *((_DWORD *)m_nScriptCamY + 3) = result;
          *((float *)m_nScriptCamY + 5) = z;
          *((float *)m_nScriptCamY + 4) = *((float *)m_nScriptCamY + 4) - 4.0;
          return result;
        case 0xEu:
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::NotifySceneChange(*((_DWORD *)m_nScriptCamY + 15));
          if ( *((_DWORD *)m_nScriptCamY + 16) )
          {
            v7 = m_nScriptCamY[60];
            m_nBlockHandle = this->m_nBlockHandle;
            BYTE2(this->m_nExecRangeD) = v7;
            this->m_nBlockHandle = (int)(((RoleSystem *)*(RoleSystem **)(m_nBlockHandle + 16)))->RoleSystem::NotifyPathEnd(v7);
          }
          goto LABEL_5;
        case 0xFu:
          *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = *((_DWORD *)m_nScriptCamY + 15);
          goto LABEL_5;
        case 0x10u:
          if ( *((_DWORD *)m_nScriptCamY + 15) )
          {
            v64.x = g_pCameraCtrl->m_vecLookAt.x - *((float *)m_nScriptCamY + 3);
            v34 = g_pCameraCtrl->m_vecLookAt.y - *((float *)m_nScriptCamY + 4);
            nVal2.x = v64.x;
            v64.y = v34;
            v35 = g_pCameraCtrl->m_vecLookAt.z - *((float *)m_nScriptCamY + 5);
            nVal2.y = v64.y;
            v64.z = v35;
            nVal2.z = v64.z;
            nVal2.x = (((gbVec3D *)&nVal2))->gbVec3D::Length() * 0.019999999552965164f;
            return (((CameraCtrl *)&g_GameData))->CameraCtrl::SetupLerp((int)g_pCameraCtrl, (int *)m_nScriptCamY + 3, SLODWORD(nVal2.x), 1);
          }
          else
          {
            g_pCameraCtrl->m_vecLookAt = *(gbVec3D *)(m_nScriptCamY + 1);
            InputSystem::ProcessKeyboard((InputSystem *)g_pCameraCtrl, 0);
          }
          return result;
        case 0x11u:
          this->m_szScriptFile[1] = m_nScriptCamY[60];
LABEL_5:
          p_m_nSavedPosX = (PalScriptMgr *)&this->m_nSavedPosX;
          v5 = *((_DWORD *)&this->m_pWaitObj + 1) - 1;
          v6 = this->m_nScriptCamY + 76;
          this->m_nScriptCamY = v6;
          *((_DWORD *)&this->m_pWaitObj + 1) = v5;
          if ( v5 )
            goto LABEL_17;
          goto LABEL_18;
        case 0x12u:
          this->PalScriptMgr::RunCommand(*((_DWORD *)m_nScriptCamY + 15));
          p_m_nSavedPosX = (PalScriptMgr *)&this->m_nSavedPosX;
          v9 = *((_DWORD *)&this->m_pWaitObj + 1) - 1;
          v6 = this->m_nScriptCamY + 76;
          this->m_nScriptCamY = v6;
          *((_DWORD *)&this->m_pWaitObj + 1) = v9;
          if ( !v9 )
            goto LABEL_18;
LABEL_17:
          if ( (char *)v6 == p_m_nSavedPosX->m_scriptMain.m_pData )
LABEL_18:
            (((PalScriptMgr *)p_m_nSavedPosX))->PalScriptMgr::PopScript();
LABEL_26:
          result = *((_DWORD *)&this->m_pWaitObj + 1);
          if ( !result )
            return result;
          continue;
        case 0x13u:
          LODWORD(v64.x) = this->m_nTodo_024;
          v64.z = this->m_fCamY;
          v64.y = 0.0f;
          v64.x = v64.x - *(float *)&g_pRoleSystem->m_fontcolor.Color;
          v64.y = -*(float *)&g_pRoleSystem->m_wndcolor.Color;
          v64.z = v64.z - *(float *)&g_pRoleSystem->m_id;
          nVal2.x = (((gbVec3D *)&v64))->gbVec3D::Length();
          (((Object3D *)this))->Object3D::SetTransform(&pMatrix);
          if ( v69 <= (double)v68 )
            v36 = v68;
          else
            v36 = v69;
          if ( nVal2.x - v36 * 0.5 <= g_ScriptSystemData.m_fTimerB )
          {
            v48 = this->m_nScriptCamY + 76;
            v49 = *((_DWORD *)&this->m_pWaitObj + 1) - 1;
            this->m_nScriptCamY = v48;
            *((_DWORD *)&this->m_pWaitObj + 1) = v49;
            if ( !v49 || v48 == this->m_nScriptCamX )
            {
              v50 = (char *)this->m_pScriptBlock;
              this->m_pScriptBlock = ((char *)(v50 + 4));
              operator delete(*(void **)v50);
              if ( !*((_DWORD *)&this->m_pWaitObj + 1) )
              {
                (((PalScriptMgr *)&v65))->PalScriptMgr::Get_result();
                y = v65.y;
                v52 = v65.z;
                x = v65.x;
                v54 = (char *)m_pScriptBlock;
                this->m_pSubScriptB = ((PalScriptMgr *)((PalScriptMgr *)LODWORD(v65.x)));
                *(float *)&this->m_nScriptCamX = y;
                *(float *)&this->m_nScriptCamY = v52;
                this->m_pScriptBlock = ((char *)(v54));
                *(float *)&this->m_pExecObj = x;
                this->m_fExecParam = y;
                m_nExecState2 = (void *)this->m_nExecState2;
                this->m_fExecPosY = v52;
                LODWORD(this->m_fExecPosZ) = (unsigned long)v54;
                operator delete(m_nExecState2);
                return this->PalScriptMgr::ExecuteOpcode();
              }
              (((gbVec3D *)&v65))->gbVec3D::Copy(*(_DWORD *)this->m_pScriptBlock, (gbVec3D *)this->m_pScriptBlock);
              v55 = v65.y;
              this->m_pSubScriptB = ((PalScriptMgr *)((PalScriptMgr *)LODWORD(v65.x)));
              v56 = v65.z;
              *(float *)&this->m_nScriptCamX = v55;
              v57 = (char *)m_pScriptBlock;
              *(float *)&this->m_nScriptCamY = v56;
              this->m_pScriptBlock = ((char *)(v57));
            }
            result = this->PalScriptMgr::ExecuteOpcode();
          }
          else
          {
            while ( *((_DWORD *)&this->m_pWaitObj + 1) )
            {
              v37 = this->m_nScriptCamY + 76;
              v38 = *((_DWORD *)&this->m_pWaitObj + 1) - 1;
              this->m_nScriptCamY = v37;
              *((_DWORD *)&this->m_pWaitObj + 1) = v38;
              if ( !v38 || v37 == this->m_nScriptCamX )
              {
                v39 = (char *)this->m_pScriptBlock;
                this->m_pScriptBlock = ((char *)(v39 + 4));
                operator delete(*(void **)v39);
                if ( *((_DWORD *)&this->m_pWaitObj + 1) )
                {
                  (((gbVec3D *)&v65))->gbVec3D::Copy(*(_DWORD *)this->m_pScriptBlock, (gbVec3D *)this->m_pScriptBlock);
                  v44 = v65.y;
                  this->m_pSubScriptB = ((PalScriptMgr *)((PalScriptMgr *)LODWORD(v65.x)));
                  v45 = v65.z;
                  *(float *)&this->m_nScriptCamX = v44;
                  v46 = (char *)m_pScriptBlock;
                  *(float *)&this->m_nScriptCamY = v45;
                  this->m_pScriptBlock = ((char *)(v46));
                }
                else
                {
                  (((PalScriptMgr *)&nVal2))->PalScriptMgr::Get_result();
                  v40 = nVal2.x;
                  v41 = nVal2.z;
                  v42 = nVal2.y;
                  v43 = (char *)v63;
                  this->m_pSubScriptB = ((PalScriptMgr *)((PalScriptMgr *)LODWORD(nVal2.x)));
                  *(float *)&this->m_nScriptCamX = v42;
                  *(float *)&this->m_nScriptCamY = v41;
                  this->m_pScriptBlock = ((char *)(v43));
                  *(float *)&this->m_pExecObj = v40;
                  this->m_fExecParam = v42;
                  this->m_fExecPosY = v41;
                  v60 = (void *)this->m_nExecState2;
                  LODWORD(this->m_fExecPosZ) = (unsigned long)v43;
                  operator delete(v60);
                }
              }
            }
            v47 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("outdist");
            result = (((PalScriptMgr *)&stru_DBA134))->PalScriptMgr::ShowTextBox(v47);
          }
          break;
        case 0x15u:
          if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
            (((_Console *)g_pCameraCtrl))->_Console::SetActive((int)g_pRoleSystem);
          v10 = this->m_nScriptCamY + 76;
          v11 = *((_DWORD *)&this->m_pWaitObj + 1) - 1;
          this->m_nScriptCamY = v10;
          *((_DWORD *)&this->m_pWaitObj + 1) = v11;
          if ( !v11 || v10 == this->m_nScriptCamX )
          {
            v12 = (char *)this->m_pScriptBlock;
            this->m_pScriptBlock = ((char *)(v12 + 4));
            operator delete(*(void **)v12);
            if ( *((_DWORD *)&this->m_pWaitObj + 1) )
            {
              v13 = (PalScriptMgr **)this->m_pScriptBlock;
              v14 = (PalScriptMgr *)*v13;
              this->m_pSubScriptB = ((PalScriptMgr *)(*v13));
              this->m_nScriptCamX = (int)(&v14->m_nField_0E70 + 82);
              this->m_nScriptCamY = (int)v14;
              this->m_pScriptBlock = ((char *)((char *)v13));
            }
            else
            {
              this->m_pSubScriptB = ((PalScriptMgr *)0);
              this->m_nScriptCamX = 0;
              this->m_nScriptCamY = 0;
              this->m_pScriptBlock = ((char *)0);
              this->m_pExecObj = ((char *)0);
              v58 = (void *)this->m_nExecState2;
              this->m_fExecParam = 0.0f;
              this->m_fExecPosY = 0.0f;
              this->m_fExecPosZ = 0.0f;
              operator delete(v58);
            }
          }
          goto LABEL_26;
        default:
          return result;
      }
      break;
    }
  }
  return result;
}

// 0x0042F460
void PalScriptMgr::ExecuteFrame(float fVal)
{
  bool IsRunning; // bl
  int m_nScriptCamX; // edx
  int m_nScriptCamY; // ebp
  double v6; // st7
  float *p_m_nTodo_024; // esi
  long double v8; // st7
  RoleSystem *v9; // edx
  char m_nExecRangeD; // al
  RoleSystem *v11; // esi
  double v12; // st7
  int RolePtr; // ebx
  float v14; // eax
  float v15; // ecx
  int v16; // ebp
  bool v17; // zf
  BOOL IsAngleBelowTarget; // eax
  PalScript *v19; // eax
  ScriptVM *v20; // eax
  int v21; // eax
  BOOL IsVisible; // eax
  RoleSystem *v23; // esi
  double v24; // st7
  float v25; // eax
  int v26; // edx
  int v27; // ecx
  char *v28; // eax
  PalScriptMgr **v29; // eax
  PalScriptMgr *v30; // ecx
  float pPos; // [esp+0x0] [ebp-0x40]
  int v32; // [esp+0x8] [ebp-0x38]
  void *m_nExecState2; // [esp+0x8] [ebp-0x38]
  int v34; // [esp+0xC] [ebp-0x34]
  int nFlag; // [esp+0x1C] [ebp-0x24]
  float pfVal; // [esp+0x24] [ebp-0x1C] BYREF
  float v37; // [esp+0x28] [ebp-0x18]
  float v38; // [esp+0x2C] [ebp-0x14]
  int p_DWORD; // [esp+0x30] [ebp-0x10] BYREF
  float v40; // [esp+0x34] [ebp-0xC]
  float v41; // [esp+0x38] [ebp-0x8]
  char *m_pScriptBlock; // [esp+0x3C] [ebp-0x4]

  if ( *((_DWORD *)&this->m_pWaitObj + 1) )
  {
    IsRunning = 0;
    p_DWORD = (int)this->m_pSubScriptB;
    m_nScriptCamX = this->m_nScriptCamX;
    v40 = *(float *)&m_nScriptCamX;
    m_nScriptCamY = this->m_nScriptCamY;
    v6 = fVal + *(float *)(m_nScriptCamY + 8);
    m_pScriptBlock = (char *)this->m_pScriptBlock;
    *(float *)(m_nScriptCamY + 8) = v6;
    if ( v6 >= *(float *)(m_nScriptCamY + 4) )
    {
      IsRunning = 1;
      *(_DWORD *)(m_nScriptCamY + 8) = *(_DWORD *)(m_nScriptCamY + 4);
    }
    *(float *)&nFlag = *(float *)(m_nScriptCamY + 8) / *(float *)(m_nScriptCamY + 4);
    switch ( *(_BYTE *)m_nScriptCamY )
    {
      case 1:
        p_m_nTodo_024 = (float *)&this->m_nTodo_024;
        v8 = (1.0 - cos(*(float *)&nFlag * 3.1415927)) * 0.5;
        *(float *)&this->m_nTodo_024 = *(float *)(m_nScriptCamY + 12) * (1.0 - v8) + *(float *)(m_nScriptCamY + 24) * v8;
        this->m_fCamX = *(float *)(m_nScriptCamY + 16) * (1.0f - v8) + *(float *)(m_nScriptCamY + 28) * v8;
        this->m_fCamY = *(float *)(m_nScriptCamY + 20) * (1.0f - v8) + *(float *)(m_nScriptCamY + 32) * v8;
        if ( *(_DWORD *)(m_nScriptCamY + 60) )
        {
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::SetTargetRotation((gbVec3D *)&this->m_nTodo_024);
          v9 = g_pRoleSystem;
          g_pRoleSystem->m_fPosX = *p_m_nTodo_024;
          v9->m_fPosY = this->m_fCamX;
          v9->m_fPosZ = this->m_fCamY;
        }
        if ( *(_DWORD *)(m_nScriptCamY + 64) )
        {
          *(float *)&this->m_pTodo_84 = *p_m_nTodo_024;
          this->m_nExecuteBlock = LODWORD(this->m_fCamX);
          this->m_nSavedDataA = LODWORD(this->m_fCamY);
        }
        m_nExecRangeD = this->m_nExecRangeD;
        if ( m_nExecRangeD == 33 || m_nExecRangeD == 29 )
          (((RoleSystem *)&g_pRoleSystem))->RoleSystem::SetMoveSpeed(0.0, 0, v34);
        goto LABEL_40;
      case 2:
        v11 = g_pRoleSystem;
        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::PathFollowUpdate();
        if ( v11->m_nMoveSubMode == 4 )
        {
          v11->m_fRotAxisX = v11->m_nMovement;
          v11->m_fRotAxisY = v11->m_fSavedRotX;
          LODWORD(v11->m_fRotAxisZ) = (unsigned long)((UIWnd *)&v11->m_FrameA);
          v11->m_fRotAxisY = 0.0f;
          *((_DWORD *)&v11[1].m_partyActor.m_fSpeed + 2) = (unsigned long)v11->m_fontcolor.Color;
          *((_DWORD *)&v11[1].m_partyActor.m_fSpeed + 3) = (unsigned long)v11->m_wndcolor.Color;
          LODWORD(v11[1].m_partyActor.m_fAngleDeg) = (unsigned long)v11->m_id;
          v12 = fVal * v11->m_fRotAxisX;
          v40 = fVal * v11->m_fRotAxisY;
          v41 = fVal * v11->m_fRotAxisZ;
          *(&v11[1].m_partyActor.m_fSpeed + 2) = v12 + *(&v11[1].m_partyActor.m_fSpeed + 2);
          *(&v11[1].m_partyActor.m_fSpeed + 3) = v40 + *(&v11[1].m_partyActor.m_fSpeed + 3);
          v11[1].m_partyActor.m_fAngleDeg = v41 + v11[1].m_partyActor.m_fAngleDeg;
          if ( *(_DWORD *)(m_nScriptCamY + 60) )
          {
            RolePtr = (((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::GetRolePtr(v11->m_partyActor.m_nState);
            if ( !(((RoleSystem *)*(RoleSystem **)(this->m_nBlockHandle + 16)))->RoleSystem::CheckCollision((int *)v11->m_partyActor.m_nState, (__int64)((*(&v11[1].m_partyActor.m_fSpeed + 2) - *(float *)(RolePtr + 128)) / g_ScriptSystemData.m_fScriptTileSize2)) )
            {
              (((RoleSystem *)v11))->RoleSystem::NotifyMoveComplete();
              *((_DWORD *)&v11[1].m_partyActor.m_fSpeed + 2) = (unsigned long)v11->m_fontcolor.Color;
              *((_DWORD *)&v11[1].m_partyActor.m_fSpeed + 3) = (unsigned long)v11->m_wndcolor.Color;
              LODWORD(v11[1].m_partyActor.m_fAngleDeg) = (unsigned long)v11->m_id;
            }
          }
          v11->m_fontcolor.Color = *((_DWORD *)&v11[1].m_partyActor.m_fSpeed + 2);
          v11->m_wndcolor.Color = *((_DWORD *)&v11[1].m_partyActor.m_fSpeed + 3);
          v11->m_id = LODWORD(v11[1].m_partyActor.m_fAngleDeg);
          v11->m_wndcolor.Color = 0;
          (((RoleSystem *)v11))->RoleSystem::UpdatePosition();
          if ( *(_DWORD *)(m_nScriptCamY + 64) )
          {
            (((RoleSystem *)v11))->RoleSystem::SetMoveSpeed(0.0, 0, v34);
          }
          else
          {
            v14 = *(float *)&v11->m_id;
            v15 = *(float *)&v11->m_fontcolor.Color;
            v11->m_fPosX = v15;
            v11->m_fPosZ = v14;
            *(float *)&v11->m_nDispFontColor = v15;
            v11->m_nDispWndColor = LODWORD(v11->m_fPosY);
            v11->m_nTodo_9C = LODWORD(v11->m_fPosZ);
          }
        }
        IsRunning = v11->m_nMoveSubMode != 4;
        if ( v11->m_nMoveSubMode == 4 )
          return;
        (((RoleSystem *)v11))->RoleSystem::GetMoveState(0);
        goto LABEL_40;
      case 3:
        v16 = *(_DWORD *)(m_nScriptCamY + 60) - 1;
        if ( v16 )
        {
          if ( v16 == 1 )
          {
            v17 = LOBYTE(this->m_scepath) == 0;
LABEL_39:
            IsRunning = v17;
          }
        }
        else
        {
          IsRunning = LOBYTE(this->m_scepath) != 1;
        }
LABEL_40:
        if ( !IsRunning )
          return;
LABEL_41:
        v26 = this->m_nScriptCamY + 76;
        v27 = *((_DWORD *)&this->m_pWaitObj + 1) - 1;
        this->m_nScriptCamY = v26;
        *((_DWORD *)&this->m_pWaitObj + 1) = v27;
        if ( v27 && v26 != this->m_nScriptCamX )
          goto LABEL_46;
        v28 = (char *)this->m_pScriptBlock;
        this->m_pScriptBlock = ((char *)(v28 + 4));
        operator delete(*(void **)v28);
        if ( *((_DWORD *)&this->m_pWaitObj + 1) )
        {
          v29 = (PalScriptMgr **)this->m_pScriptBlock;
          v30 = (PalScriptMgr *)*v29;
          this->m_pSubScriptB = ((PalScriptMgr *)(*v29));
          this->m_nScriptCamX = (int)(&v30->m_nField_0E70 + 82);
          this->m_nScriptCamY = (int)v30;
          this->m_pScriptBlock = ((char *)((char *)v29));
LABEL_46:
          this->PalScriptMgr::ExecuteOpcode();
        }
        else
        {
          this->m_pSubScriptB = ((PalScriptMgr *)0);
          this->m_nScriptCamX = 0;
          this->m_nScriptCamY = 0;
          this->m_pScriptBlock = ((char *)0);
          this->m_pExecObj = ((char *)0);
          m_nExecState2 = (void *)this->m_nExecState2;
          this->m_fExecParam = 0.0f;
          this->m_fExecPosY = 0.0f;
          this->m_fExecPosZ = 0.0f;
          operator delete(m_nExecState2);
          this->PalScriptMgr::ExecuteOpcode();
        }
        break;
      case 4:
        PalScriptMgr::ClearAllScript();
        goto LABEL_38;
      case 5:
        LOWORD(m_nScriptCamX) = LOWORD(this->m_fSpeed2);
        v32 = m_nScriptCamX;
        v19 = (PalScript *)UISceneUpdate();
        (((PalScript *)v19))->PalScript::SetAction(v32);
        if ( !v20 )
          goto LABEL_41;
        IsRunning = (((ScriptVM *)v20))->ScriptVM::IsRunning();
        goto LABEL_40;
      case 6:
        v21 = (*(int ( **)(int *))(g_pRoleSystem->m_bvisible + 4))(&g_pRoleSystem->m_bvisible);
        IsRunning = v21 == 1;
        if ( v21 != 1 )
          return;
        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
        goto LABEL_40;
      case 7:
        IsVisible = (((Object3D *)&this->m_scriptAux))->Object3D::IsVisible();
        IsRunning = IsVisible;
        if ( !IsVisible )
          return;
        if ( *(_DWORD *)(m_nScriptCamY + 60) )
        {
          (((gbVisNode *)this->m_pScriptObjMain))->gbVisNode::SetTimeScale(0.0);
          (*(void ( **)(gbVisNode *, int))(*(_DWORD *)((gbChain1DNode *)this->m_pScriptObjMain) + 24))(
            this->m_pScriptObjMain,
            -1082130432);
          (((PalScript *)&this->m_scriptAux))->PalScript::GetCount(0);
        }
        goto LABEL_40;
      case 0xC:
        v23 = g_pRoleSystem;
        v24 = *(float *)&g_pRoleSystem->m_partyUI3.m_childs.m_pData;
        pfVal = 0.0f;
        v37 = 0.0f;
        v38 = 0.0f;
        p_DWORD = 0;
        v40 = 0.0f;
        v41 = 0.0f;
        pPos = (1.0f - cos(*(float *)&nFlag * 3.1415927410125732f)) * 0.5f * v24;
        (((PathObj *)&g_pRoleSystem->m_fMoveTargetX))->PathObj::GetPosition(pPos, &pfVal, &p_DWORD);
        *(float *)&v23->m_fontcolor.Color = pfVal;
        *(float *)&v23->m_wndcolor.Color = v37;
        *(float *)&v23->m_id = v38;
        v23->m_fPosX = pfVal;
        v23->m_fPosY = v37;
        v23->m_fPosZ = v38;
        v23->m_wndcolor.Color = 0;
        LODWORD(v23->m_fRotAxisX) = p_DWORD;
        v23->m_fRotAxisY = v40;
        v23->m_fRotAxisZ = v41;
        (((RoleSystem *)v23))->RoleSystem::SetMoveSpeed(0.0, 0, v34);
        (((RoleSystem *)v23))->RoleSystem::UpdatePosition();
        if ( !IsRunning )
          return;
        (((RoleSystem *)v23))->RoleSystem::GetMoveState(0);
        (((RoleSystem *)v23))->RoleSystem::Notify();
        goto LABEL_40;
      case 0xD:
        *(float *)(m_nScriptCamY + 28) = *(float *)(m_nScriptCamY + 28) - 490.0 * fVal;
        pfVal = *(float *)(m_nScriptCamY + 24);
        v25 = *(float *)(m_nScriptCamY + 32);
        v37 = *(float *)(m_nScriptCamY + 28) * fVal;
        v38 = v25 * fVal;
        *(float *)&this->m_nTodo_024 = pfVal * fVal + *(float *)&this->m_nTodo_024;
        this->m_fCamX = v37 + this->m_fCamX;
        this->m_fCamY = v38 + this->m_fCamY;
        if ( this->m_fCamX > (double)*(float *)(m_nScriptCamY + 16) )
          return;
        this->m_fCamX = *(float *)(m_nScriptCamY + 16);
        *(_DWORD *)&this->m_pTodo_84 = this->m_nTodo_024;
        this->m_nExecuteBlock = LODWORD(this->m_fCamX);
        this->m_nSavedDataA = LODWORD(this->m_fCamY);
        goto LABEL_41;
      case 0x10:
        (((CameraCtrl *)&g_GameData))->CameraCtrl::UpdateTransition(fVal);
        IsAngleBelowTarget = (((CameraCtrl *)&g_GameData))->CameraCtrl::IsAngleBelowTarget();
LABEL_38:
        v17 = !IsAngleBelowTarget;
        goto LABEL_39;
      default:
        goto LABEL_40;
    }
  }
}

// 0x0042FB40
char PalScriptMgr::SetBigMapState(char nState)
{
  char result; // al

  result = nState;
  *(_DWORD *)&this->m_bBigMapState = 0;
  LOBYTE(this->m_scepath) = nState;
  return result;
}

// 0x0042FCC0
void PalScriptMgr::PopScript()
{
  void **m_nSize; // eax
  int *v3; // eax
  int *p_m_bGetSceneScript; // esi
  int v5; // ecx
  float m_nTodo_020; // [esp-0x8] [ebp-0x10]

  m_nSize = (void **)this->m_scriptMain.m_nSize;
  this->m_scriptMain.m_nSize = (int)(m_nSize + 1);
  operator delete(*m_nSize);
  if ( LODWORD(this->m_fCamX) )
  {
    v3 = (int *)this->m_scriptMain.m_nSize;
    p_m_bGetSceneScript = (int *)&this->m_bGetSceneScript;
    v5 = (unsigned long)*v3;
    *p_m_bGetSceneScript = *v3;
    p_m_bGetSceneScript[1] = v5 + 4028;
    p_m_bGetSceneScript[2] = v5;
    p_m_bGetSceneScript[3] = (int)v3;
  }
  else
  {
    *(_DWORD *)&this->m_bGetSceneScript = 0;
    this->m_scriptMain.m_pData = ((char *)0);
    this->m_scriptMain.capacity = 0;
    this->m_scriptMain.m_nSize = 0;
    this->m_scriptMain.m_needscriptdel = 0;
    m_nTodo_020 = this->m_nTodo_020;
    this->m_scefile = ((scSCEFile *)0);
    this->m_nTodo_018 = 0.0f;
    this->m_nTodo_01C = 0.0f;
    operator delete((void *)LODWORD(m_nTodo_020));
  }
}

// 0x00431E60
PalScriptMgr::PalScriptMgr()
{
  SingletonThunk_00431E70(this);
  atexit(ConditionalCleanup);
}

// 0x00431EB0
void PalScriptMgr::OpenSCE()
{
  SingletonThunk_00431EC0(this);
  atexit(FindScript);
}

// 0x004320A0
void PalScriptMgr::Update(const char *pszName)
{
  int v1; // eax
  unsigned int v2; // kr04_4
  unsigned int v3; // ebp
  char *v4; // edi
  char v5; // al

  (((PtrArray *)&p_DWORD))->PtrArray::InsertAt(pszName);
  if ( v1 )
  {
    v2 = strlen(pszName) + 1;
    v3 = v2 - 1;
    if ( v2 - 1 > 0xFFFFFFFD )
      std::_Xlen();
    v4 = (char *)g_ScriptSystemData.m_nScriptState;
    if ( g_ScriptSystemData.m_nScriptState && (v5 = *(_BYTE *)(g_ScriptSystemData.m_nScriptState - 1)) != 0 && v5 != -1 )
    {
      if ( v2 == 1 )
      {
        *(_BYTE *)(g_ScriptSystemData.m_nScriptState - 1) = v5 - 1;
        g_ScriptSystemData.m_nScriptState = 0;
        g_ScriptSystemData.m_nCmdFA8 = 0;
        g_ScriptSystemData.m_pScriptData = ((char *)0);
        return;
      }
    }
    else
    {
      if ( v2 == 1 )
      {
        (((std::string *)1))->_Tidy();
        return;
      }
      if ( (unsigned int)g_ScriptSystemData.m_pScriptData <= 0x1F && g_ScriptSystemData.m_pScriptData >= v2 - 1 )
        goto LABEL_15;
      (((std::string *)1))->_Tidy();
    }
    (((GRPinput *)&g_ScriptSystemData.m_nCmdFA0))->GRPinput::PollInputState(v3);
    v4 = (char *)g_ScriptSystemData.m_nScriptState;
LABEL_15:
    qmemcpy(v4, pszName, v3);
    g_ScriptSystemData.m_nCmdFA8 = v2 - 1;
    *(_BYTE *)(g_ScriptSystemData.m_nScriptState + v3) = 0;
  }
}

// 0x00432170
void PalScriptMgr::Destroy()
{
  int *v1; // eax
  int *v2; // edi
  PtrArray *v3; // eax
  int *v4; // esi
  unsigned int nVal; // [esp+0x18] [ebp+0x4]
  char v6; // [esp+0x1C] [ebp+0x8]

  if ( nVal )
  {
    if ( v6 )
      v1 = (int *)PtrArray::CopyRange((int *)&unk_D8C2C8, nVal, 0);
    else
      v1 = nVal >= 0x64
         ? PtrArray::CopyRange((int *)&p_DWORD, nVal, 0)
         : PtrArray::CopyRange((int *)&unk_D8C2E8, nVal, 0);
    v2 = (int *)v1;
    if ( v1 )
    {
      v3 = (PtrArray *)operator new(0x18u);
      if ( v3 )
        v4 = (((PtrArray *)v3))->PtrArray::Reset();
      else
        v4 = 0;
      if ( v4 )
      {
        v4[1] = (int)v2;
        (((PtrArray *)&dword_D8C328))->PtrArray::SetAt(g_ScriptSystemData.m_CmdObjArray0.capacity, (int)v4);
      }
      else
      {
        FreeScriptInstance(v2);
      }
    }
  }
}

// 0x00432260
const char ** PalScriptMgr::_CON_State(const char *pszName)
{
  int v1; // ecx
  char *i; // edx
  const char **result; // eax

  v1 = 0;
  if ( g_ScriptSystemData.m_CmdObjArray0.capacity <= 0 )
    return 0;
  for ( i = dword_D8C328.m_pData; ; i += 4 )
  {
    if ( v1 >= 0 && v1 < g_ScriptSystemData.m_CmdObjArray0.capacity )
    {
      result = (const char **)*(const char ***)i;
      if ( *(_DWORD *)i )
      {
        if ( result[1] == pszName )
          break;
      }
    }
    if ( ++v1 >= g_ScriptSystemData.m_CmdObjArray0.capacity )
      return 0;
  }
  return result;
}

// 0x004322A0
bool PalScriptMgr::IfAnyScriptRunning(int nVal)
{
  bool result; // al

  (((PtrArray *)&this->m_scriptMain))->PtrArray::SetAt(this->m_scriptMain.capacity, nVal);
  return result;
}

// 0x004322C0
int PalScriptMgr::IsScriptRuning(int pal)
{
    PalScriptMgr *_this = this;
  PalScriptMgr *v2; // ebx
  int capacity; // eax
  int v4; // eax
  int v6; // ebp
  int v7; // edi
  PtrArray *p_m_scriptMain; // ebx
  _DWORD *v9; // esi
  int v10; // esi
  PalScriptMgr *v11; // [esp+0x10] [ebp-0x4]

  v2 = _this;
  capacity = _this->m_scriptMain.capacity;
  v11 = _this;
  if ( capacity )
  {
    v6 = 0;
    v7 = 0;
    if ( capacity > 0 )
    {
      p_m_scriptMain = (PtrArray *)&_this->m_scriptMain;
      do
      {
        if ( v7 < 0 || v7 >= p_m_scriptMain->capacity )
          v9 = 0;
        else
          v9 = (_DWORD *)(*(_DWORD **)&p_m_scriptMain->m_pData[4 * v7]);
        if ( (*(int ( **)(_DWORD *))(*v9 + 4))(v9) )
        {
          (*(void ( **)(_DWORD *, int))(*v9 + 8))(v9, pal);
        }
        else
        {
          if ( v9[1] && v9 )
            (*(void ( **)(_DWORD *, int))*v9)(v9, 1);
          if ( v7 >= 0 && v7 < p_m_scriptMain->capacity )
            *(_DWORD *)&p_m_scriptMain->m_pData[4 * v7] = 0;
          v6 = 1;
        }
        ++v7;
      }
      while ( v7 < v11->m_scriptMain.capacity );
      if ( v6 )
      {
        v10 = 0;
        while ( v10 < v11->m_scriptMain.capacity )
        {
          if ( v10 >= 0 && v10 < p_m_scriptMain->capacity && *(_DWORD *)&p_m_scriptMain->m_pData[4 * v10] )
            ++v10;
          else
            (((PtrArray *)p_m_scriptMain))->PtrArray::RemoveAt(v10, 1);
        }
      }
    }
  }
  else
  {
    while ( 1 )
    {
      (((PtrArray *)_this))->PtrArray::~PtrArray();
      if ( v4 == 2 )
        break;
      _this = (PalScriptMgr *)v2->m_scriptMain.capacity;
      if ( (int)_this > 0 )
        return 0;
    }
    if ( !v2->m_scriptMain.capacity )
      return 1;
  }
  return 0;
}

// 0x00432480
void PalScriptMgr::_CON_ReLoadScript()
{
  PtrArray *v1; // ecx

  this->PalScriptMgr::IfHaveScript();
  (((PtrArray *)v1))->PtrArray::SetSize();
  (((PtrArray *)&p_DWORD))->PtrArray::DestroyAll();
}

// 0x004324A0
BOOL PalScriptMgr::_CON_CloseScript()
{
  return g_ScriptSystemData.m_CmdObjArray0.capacity > 0;
}

// 0x004324B0
void PalScriptMgr::ClearAllScript()
{
  int v0; // eax
  char *m_pData; // esi
  int v2; // ecx
  int v3; // [esp+0xC] [ebp+0x4]

  if ( v3 )
  {
    v0 = 0;
    if ( g_ScriptSystemData.m_CmdObjArray0.capacity > 0 )
    {
      m_pData = (char *)dword_D8C328.m_pData;
      do
      {
        if ( v0 < 0 || v0 >= g_ScriptSystemData.m_CmdObjArray0.capacity )
          v2 = 0;
        else
          v2 = *(_DWORD *)m_pData;
        if ( v2 == v3 )
          break;
        ++v0;
        m_pData += 4;
      }
      while ( v0 < g_ScriptSystemData.m_CmdObjArray0.capacity );
    }
  }
}

// 0x00432500
int * PalScriptMgr::FindScriptByDesc(const char *pszName, const char *desc)
{
  PalScriptMgr *v2; // ecx
  int *result; // eax
  char Buffer[64]; // [esp+0x0] [ebp-0x40] BYREF

  _snprintf(Buffer, 0x3Fu, "_%s_%s", pszName, desc);
  PtrArray::IsArrayReady();
  (((PalScriptMgr *)v2))->PalScriptMgr::Destroy();
  if ( result )
    byte_D8C339 = 1;
  return result;
}

// 0x00432550
void PalScriptMgr::IfHaveScript()
{
  int v1; // eax
  int i; // edi
  void *v3; // esi

  v1 = g_ScriptSystemData.m_CmdObjArray0.capacity;
  for ( i = 0; i < v1; ++i )
  {
    if ( i >= 0 && i < v1 )
    {
      v3 = (void *)(*(void **)&dword_D8C328.m_pData[4 * i]);
      if ( v3 )
      {
        (((UIListBox *)*(UIListBox **)&dword_D8C328.m_pData[4 * i]))->UIListBox::RefreshSelection();
        operator delete(v3);
        v1 = g_ScriptSystemData.m_CmdObjArray0.capacity;
      }
    }
  }
  (((String *)&dword_D8C328))->String::Assign(0, -1);
}

// 0x00434C40
void PalScriptMgr::NotifyEvent()
{
  const char **v0; // eax
  int nVal; // [esp+0x8] [ebp+0x4]

  if ( nVal )
  {
    v0 = (const char **)PalScriptMgr::_CON_State((const char *)g_pLoadBuffer);
    if ( v0 )
    {
      (((PalScriptMgr *)v0))->PalScriptMgr::IfAnyScriptRunning(nVal);
    }
    else if ( *(_DWORD *)(nVal + 4) )
    {
      (**(void ( ***)(int, int))nVal)((int)(nVal), (int)(1));
    }
  }
}

// 0x00434C80
void * PalScriptMgr::UpdateLoadProgress()
{
  void *result; // eax

  result = (void *)g_pLoadBuffer;
  *(_DWORD *)(g_pLoadBuffer + 8) = *(_DWORD *)(*(_DWORD *)g_pLoadBuffer + 68)
                                 + *(_DWORD *)(*(_DWORD *)g_pLoadBuffer + 72);
  return result;
}

// 0x00434CA0
void PalScriptMgr::InitVtable(int nVal1)
{
  this->m_scriptMain.m_pData = ((char *)((char *)nVal1));
  *(_DWORD *)&this->m_bGetSceneScript = 1;
}

// 0x00434CC0
BOOL PalScriptMgr::IsWaitComplete()
{
  return (_BYTE)byte_DBA25C || (char *)g_CCBEditorInst.m_dwTrickID[361] == this->m_scriptMain.m_pData;
}

// 0x00450BC0
int PalScriptMgr::ShowTextBox(const char *pszText)
{
  void ( **v3)(PalScriptMgr *, int); // eax
  int result; // eax
  _DWORD a2[2]; // [esp+0xC] [ebp-0x10] BYREF
  unsigned int v6; // [esp+0x14] [ebp-0x8]
  int v7; // [esp+0x18] [ebp-0x4]

  a2[1] = 0;
  a2[0] = 0;
  v7 = 48;
  if ( 10 * (strlen(pszText) + 6) >= 0x40 )
    v6 = 10 * (strlen(pszText) + 6);
  else
    v6 = 64;
  (((UIWnd *)&this->m_wndTextBox))->UIWnd::sub_445FA0(a2);
  sub_445DB0(this);
  (((RoleCameraCtrl *)&this->m_wndTextBox))->RoleCameraCtrl::SetName(pszText);
  v3 = *(void ( ***)(PalScriptMgr *, int))this;
  this->m_nCmdParam2 = 0;
  (*v3)(this, 1);
  (((UIScene *)&this->m_wndTextBox))->UIScene::SetState(1);
  return result;
}

// 0x00525080
int PalScriptMgr::Get_m_nField_1490()
{
  return *(&this->m_nField_1468 + 9);
}
