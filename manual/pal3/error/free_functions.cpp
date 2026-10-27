// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "free_functions.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Role/Actor.h"
#include "Misc/ArcLocaleRole.h"
#include "Misc/ArcSceneMonster.h"
#include "Misc/ArcSceneObject.h"
#include "Misc/Array.h"
#include "Combat/CCBAI.h"
#include "Combat/CCBAIWindow.h"
#include "Combat/CCBAttackSequen.h"
#include "Combat/CCBCamControl.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBParabolaWindow.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBSystem.h"
#include "Combat/CCBUI.h"
#include "Misc/CCBUIPanel.h"
#include "Combat/CCCTData.h"
#include "Misc/CEffCustomShape.h"
#include "Effect/CEffExplosive.h"
#include "Effect/CEffMgr.h"
#include "Effect/CEffect.h"
#include "Effect/CEffectSystem.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/Camera.h"
#include "Scene/CameraCtrl.h"
#include "Misc/ChoseCompose.h"
#include "Combat/Combat.h"
#include "Misc/Comp_DonateUI.h"
#include "UI/EquipUI.h"
#include "Misc/ExternalStatistics.h"
#include "GameBase/GRPinput.h"
#include "GameBase/InputSystem.h"
#include "Misc/JusticeBookUI.h"
#include "Misc/LineupComp.h"
#include "Misc/LineupUI.h"
#include "GameBase/Logger.h"
#include "Misc/MainEquipUI.h"
#include "Misc/MainPropUI.h"
#include "Misc/MiniGame2Scene.h"
#include "Role/NPC.h"
#include "Misc/NameSys.h"
#include "Misc/Object.h"
#include "Role/Object3D.h"
#include "Role/ObjectCamera.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/OpenSceneFile.h"
#include "GameBase/PAL3.h"
#include "Misc/PAL3VisNode.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PalScriptWaitObj.h"
#include "Misc/Parent_Data.h"
#include "Misc/PlayerItem.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Render/RenderTarget3.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleCamera.h"
#include "Misc/RoleCameraCtrl.h"
#include "Role/RoleSystem.h"
#include "Misc/SaleUI.h"
#include "Scene/Scene.h"
#include "Scene/SceneMgr.h"
#include "Scene/SceneObj.h"
#include "Effect/ScreenEffectMgr.h"
#include "Script/ScriptSystem.h"
#include "UI/StateUI.h"
#include "Misc/SystemUI.h"
#include "Misc/TaskBookUI.h"
#include "Render/TextureLib.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UI3DCtrl.h"
#include "Misc/UIBigMap.h"
#include "Misc/UICaption.h"
#include "Misc/UICoverFrm.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "UI/UINote.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "UI/UIQuadManager.h"
#include "UI/UIRenderObj.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "Misc/UITextArea.h"
#include "Misc/UITitle_BBTY.h"
#include "Misc/UITitle_JDHY.h"
#include "Misc/UITitle_XJTM.h"
#include "UI/UIWnd.h"
#include "Misc/VideoPlayer.h"

// Free functions (not belonging to any class)

// Forward declarations for unnamed functions
int FileSysInit(...);
int LocalFree(...);
int sub_41FA90(...);
int sub_420200(...);
int sub_4206F0(...);
int sub_420730(...);
int sub_495CA0(...);
int sub_4B9E50(...);
int sub_4BA150(...);
int sub_4BA270(...);
int sub_4BA3D0(...);
int sub_4BA770(...);
int sub_4BACA0(...);
int sub_4C5940(...);
int sub_4C5FA0(...);
int sub_4CCDA0(...);
int sub_4CD3A0(...);
int sub_53D460(...);
int sub_53DAD0(...);
int todo_00419690(...);
int todo_0044AB40(...);
int todo_004B7560(...);
int todo_004B7650(...);
int todo_004B7D30(...);
int todo_004BA230(...);
int todo_004C5B50(...);
int todo_004C9470(...);
int todo_004CB280(...);
void todo_004D0C90(void); // no-arg compiler stub (does not read ecx)
int todo_004D37A0(...);
int todo_004D4CA0(...);
int todo_0051DFD0(...);
int todo_00530F70(...);
int todo_00537120(...);
int todo_0053A670(...);
int todo_0053BD30(...);

class PtrArray;
class TextureLibDataBase;
class RoleCameraCtrl;

// Unnamed globals (extern)
extern CHAR aSoftwareSoftst_2[];
extern unsigned char byte_A00002;
extern unsigned char byte_A00319;
extern unsigned char byte_A00320;
extern unsigned char byte_A00321;
extern unsigned char byte_A00322;
extern unsigned char byte_A00326;
extern unsigned char byte_A00330;
extern unsigned char byte_A01B00;
extern unsigned char byte_A01B01;
extern unsigned char byte_A01B02;
extern unsigned char byte_A01B03;
extern unsigned char byte_A01B04;
extern unsigned char byte_A01B05;
extern unsigned char byte_A01B08;
extern unsigned char byte_A01B09;
extern unsigned char byte_A01B10;
extern unsigned char byte_A01B11;
extern unsigned char byte_A01B12;
extern unsigned char byte_A01B13;
extern unsigned char byte_A01B14;
extern unsigned char byte_A01B15;
extern unsigned char byte_A01B16;
extern unsigned char byte_A01B17;
extern unsigned char byte_A01B18;
extern unsigned char byte_A01B19;
extern unsigned char byte_A01B20;
extern unsigned char byte_A01B21;
extern unsigned char byte_A01B22;
extern unsigned char byte_A01B23;
extern unsigned char byte_A01B24;
extern unsigned char byte_A01B25;
extern char byte_D8EBBC[];
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DC7D3C[512];
extern CHAR byte_DCAD3C[256];
extern CHAR byte_DD9E3C[256];
extern CHAR byte_DD9F3C[256];
extern CHAR byte_DDA03C[256];
extern CHAR byte_DDA13C[256];
extern CHAR byte_DDA23C[256];
extern CHAR byte_DDA33C[256];
extern CHAR byte_DDA43C[256];
extern CHAR byte_DDA53C[256];
extern CHAR byte_DDA63C[256];
extern CHAR byte_DDA73C[512];
extern CHAR byte_DE54D4[3];
extern CHAR byte_DE54D7[3];
extern CHAR byte_DE54DA[3];
extern CHAR byte_DE54DD[3];
extern CHAR byte_DE54E0[3];
extern CHAR byte_DE54E3[3];
extern CHAR byte_DE54E6[3];
extern CHAR byte_DE54E9[3];
extern CHAR byte_DE54EC[3];
extern int dword_D8EBF0;
extern PalScriptMgr * dword_DBA254;
extern char dword_DCD23C[];
extern char dword_DCD33C[];
extern char dword_DCD53C[];
extern char dword_DCD63C[];
extern char dword_DCD93C[];
extern int dword_DE9384;
void __cdecl nullsub_2(...);
void __cdecl nullsub_28(void);
void __cdecl nullsub_29(void);
void __cdecl nullsub_30(void);
void __cdecl nullsub_69(void);
void __cdecl nullsub_70(void);
extern LPCSTR off_5B087C;
extern LPCSTR off_5F7820;
extern LPCSTR off_5F7824;
extern LPCSTR off_5F7828;
extern PtrArray stru_17B3EB0;
extern TextureLibDataBase stru_1894B78;
extern RoleCameraCtrl stru_DBA134;
extern unsigned short word_A00336;

// 0x00401810
int ArraySort(int base, int count, int elemSize, int compareFunc)
{
  int result; // eax
  int v6; // edi

  result = elemSize - 1;
  if ( elemSize - 1 >= 0 )
  {
    v6 = elemSize;
    do
    {
      result = ((int ( *)(int))compareFunc)(base);
      base += count;
      --v6;
    }
    while ( v6 );
  }
  return result;
}

// 0x00401820
int ArraySort(int base, int count, int elemSize, int compareFunc)
{
  int result; // eax
  int v6; // edi

  result = elemSize - 1;
  if ( elemSize - 1 >= 0 )
  {
    v6 = elemSize;
    do
    {
      result = ((int ( *)(int))compareFunc)(base);
      base += count;
      --v6;
    }
    while ( v6 );
  }
  return result;
}

// 0x004019B0
int PtrArray_ReleasePtrArray(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // edi
  gbRefObject **v4; // ebx
  int result; // eax

  v2 = v1;
  v3 = 0;
  if ( *(int *)(v1 + 64) <= 0 )
  {
    *(_DWORD *)(v1 + 64) = 0;
  }
  else
  {
    v4 = (gbRefObject **)v1;
    do
    {
      (((gbRefObject *)*v4))->gbRefObject::Release();
      result = *(_DWORD *)(v2 + 64);
      ++v3;
      ++v4;
    }
    while ( v3 < result );
    *(_DWORD *)(v2 + 64) = 0;
  }
  return result;
}

// 0x00401C70
// write access to const memory has been detected, the output may be wrong!
int FileSysInit()
{
  int ( *v0)(gbVFileSystem *, char *); // esi
  char v2[324]; // [esp+0x8] [ebp-0x944] BYREF
  char pExceptionObject[1024]; // [esp+0x14C] [ebp-0x800] BYREF
  char ArgList[1024]; // [esp+0x54C] [ebp-0x400] BYREF

  if ( (g_dwGameFlags & 2) != 0 )
  {
    strcpy((char *)v2, "basedata\\");
    strcat((char *)v2, "basedata.cpk");
    v0 = gbVFileSystem::Init;
    if ( !(((gbVFileSystem *)&g_BaseVFileSystem))->gbVFileSystem::Init(v2) )
    {
      qmemcpy(pExceptionObject, (((Logger *)ArgList))->Logger::FormatException(msg, file, 23), sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
  }
  else
  {
    v0 = gbVFileSystem::Init;
    if ( !(((gbVFileSystem *)&g_BaseVFileSystem))->gbVFileSystem::Init("basedata\\") )
    {
      qmemcpy(pExceptionObject, (((Logger *)ArgList))->Logger::FormatException(msg, file, 28), sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
  }
  g_pVFileSys = (gbVFileSystem *)&g_BaseVFileSystem;
  return v0((gbVFileSystem *)&dword_60BDC8, 0);
}

// 0x00401DA0
// write access to const memory has been detected, the output may be wrong!
gbVFileSystem * FileSysDestory()
{
  gbVFileSystem *result; // eax

  if ( g_BaseVFileSystem )
    (((gbVFileSystem *)&g_BaseVFileSystem))->gbVFileSystem::Release();
  result = g_VFileSystem;
  if ( g_VFileSystem )
  {
    (((gbVFileSystem *)&g_VFileSystem))->gbVFileSystem::Release();
    result = g_pVFileSys;
  }
  g_pVFileSys = 0;
  return result;
}

// 0x004023D0
int EnumJoystick()
{
  GRPinput *v0; // ecx
  GRPinput *v1; // esi
  int result; // eax
  IDirectInputDevice8 *m_lpDIDKeyboard; // esi

  v1 = (GRPinput *)v0;
  (((GRPinput *)v0))->GRPinput::Reset();
  v1->m_bKeyboard = 0;
  m_lpDIDKeyboard = (IDirectInputDevice8 *)v1->m_lpDIDKeyboard;
  if ( m_lpDIDKeyboard )
    return (*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)m_lpDIDKeyboard + 32))(m_lpDIDKeyboard);
  return result;
}

// 0x00404310
char * StrCopyRange(char *pStart, char *pEnd, char *pDest)
{
  char *v3; // edx
  char *result; // eax

  v3 = (char *)pStart;
  if ( pStart == pEnd )
    return pDest;
  result = (char *)pDest;
  do
  {
    if ( result )
      qmemcpy(result, v3, 0x24u);
    v3 += 36;
    result += 36;
  }
  while ( v3 != pEnd );
  return result;
}

// 0x00404D60
int WinProc(HWND hWnd, UINT Msg, unsigned int pvParam, LPARAM lParam)
{
  WPARAM v4; // ebx
  UIQuadManager *Instance; // eax
  int result; // eax
  gbGfxManager *v7; // esi
  struct tagPOINT Point; // [esp+0xC] [ebp-0x8] BYREF

  v4 = pvParam;
  if ( Msg > 0x4A )
  {
    if ( Msg == 258 )
    {
      (((Logger *)&g_InputState))->Logger::WinProc_HWND_InputLine(pvParam);
    }
    else
    {
      if ( Msg != 274 )
      {
        if ( Msg == 512 && !UIQuadManager::GetInstance()[7]._tail_000[1] )
        {
          if ( g_bPAL3_BFDA91 )
          {
            v7 = gfxMgr;
            if ( gfxMgr )
            {
              if ( LODWORD(gfxMgr[1].InvViewMatrix.xy) && GetCursorPos(&Point) )
                (*(void ( **)(_DWORD, int, int, int))(*(_DWORD *)LODWORD(v7[1].InvViewMatrix.xy)
                                                                                   + 44))(
                  LODWORD(v7[1].InvViewMatrix.xy),
                  Point.x,
                  Point.y,
                  1);
            }
          }
        }
        return DefWindowProcA(hWnd, Msg, v4, lParam);
      }
      if ( pvParam > 0xF060 )
      {
        if ( pvParam != 61696 && pvParam != 61760 && pvParam != 61808 )
          return DefWindowProcA(hWnd, Msg, v4, lParam);
      }
      else if ( pvParam != 61536 && pvParam != 61440 && pvParam != 61456 && pvParam != 61488 )
      {
        return DefWindowProcA(hWnd, Msg, v4, lParam);
      }
    }
    return 0;
  }
  if ( Msg == 74 )
  {
    (((Logger *)&g_InputState))->Logger::WinProc_HWND_SetAndExec(*(char **)(lParam + 8));
    return DefWindowProcA(hWnd, Msg, v4, lParam);
  }
  switch ( Msg )
  {
    case 1u:
      pvParam = 0;
      SystemParametersInfoA(0x61u, 1u, 0, 0);
      SystemParametersInfoA(0x26u, 1u, 0, 0);
      SystemParametersInfoA(0x24u, 1u, &pvParam, 0);
      SystemParametersInfoA(0x61u, 1u, &pvParam, 0);
      return DefWindowProcA(hWnd, Msg, v4, lParam);
    case 2u:
      pvParam = 0;
      SystemParametersInfoA(0x61u, 0, 0, 0);
      SystemParametersInfoA(0x26u, 0, 0, 0);
      SystemParametersInfoA(0x24u, 1u, &pvParam, 0);
      SystemParametersInfoA(0x61u, 0, &pvParam, 0);
      g_nSceneState = 0;
      PostQuitMessage(0);
      return DefWindowProcA(hWnd, Msg, v4, lParam);
    case 6u:
      if ( (_WORD)pvParam )
      {
        (((GRPinput *)&g_Input))->GRPinput::HandleDeviceInput(1, 1, 0);
        g_nPAL3_5833B8 = 1;
      }
      else
      {
        g_nPAL3_5833B8 = 0;
        (((GRPinput *)&g_Input))->GRPinput::HandleDeviceInput(0, 0, 0);
      }
      result = 0;
      break;
    case 0x20u:
      if ( !gfxMgr )
        return DefWindowProcA(hWnd, Msg, v4, lParam);
      SetCursor(0);
      UIQuadManager::GetInstance();
      crt_sub_00541590();
      if ( g_CCBEditorInst.m_dwTrickID[361] != 9 )
      {
        Instance = (UIQuadManager *)UIQuadManager::GetInstance();
        (((UIRenderObj *)Instance))->UIRenderObj::_sdtor_call_dtor(1);
      }
      result = 1;
      break;
    default:
      return DefWindowProcA(hWnd, Msg, v4, lParam);
  }
  return result;
}

// 0x004074C0
void PAL3::StartCombat(unsigned int *const pdwVal, int monsterid, Role *side, char pMonster)
{
  PAL3 *v4; // ecx
  RoleSystem *v5; // ebx
  RoleSystem *v6; // eax
  int RolePtr; // esi
  int v8; // edi
  __int64 v9; // rax
  int v10; // ecx
  int v11; // esi
  int i; // eax
  Scene *v13; // edi
  Scene *v14; // eax
  char *v15; // esi
  CScreenMode *Instance; // eax
  int v17; // [esp+0x0] [ebp-0x11C] BYREF
  char Buffer[256]; // [esp+0xC] [ebp-0x110] BYREF
  int *v19; // [esp+0x10C] [ebp-0x10]
  int v20; // [esp+0x118] [ebp-0x4]

  v20 = 0;
  v19 = (int *)&v17;
  (((PAL3 *)v4))->PAL3::UIPostProcess();
  v5 = g_pRoleSystem;
  if ( g_pRoleSystem )
  {
    v6 = (RoleSystem *)UISceneUpdate();
    RolePtr = (((RoleSystem *)v6))->RoleSystem::GetRolePtr(v5->m_partyActor.m_nState);
    v8 = (__int64)((*(float *)&v5->m_fontcolor.Color - *(float *)(RolePtr + 128)) / *(float *)&g_nGameTime);
    v9 = (__int64)((*(float *)&v5->m_id - *(float *)(RolePtr + 136)) / *(float *)&g_nGameTime);
    if ( v8 < 0 || (v10 = *(_DWORD *)(RolePtr + 152), v8 >= v10) || (int)v9 < 0 || (int)v9 >= *(_DWORD *)(RolePtr + 156) )
      v11 = 2;
    else
      v11 = *(unsigned __int8 *)(*(_DWORD *)(RolePtr + 160) + 8 * (v8 + v9 * v10) + 5);
    for ( i = 0; i < 6; ++i )
      g_nPartyRoles[i] = pdwVal[i];
    v13 = UISceneUpdate();
    v14 = UISceneUpdate();
    sprintf(Buffer, (const char *)&dir[24], v14, &v13->m_pCapacity[5]);
    (((PalScript *)g_ScriptSlots))->PalScript::SetDirectory(Buffer);
    sprintf(Buffer, (const char *)&dir[20], v11);
    if ( !(((PalScript *)g_ScriptSlots))->PalScript::FindSaveStateString((PalScript *)Buffer, (char *)&unk_C11720, (char *)0x20, v17) )
      (((PalScript *)g_ScriptSlots))->PalScript::FindSaveStateString((PalScript *)&dir[12], (char *)&unk_C11720, (char *)0x20, v17);
    (((PalScript *)g_ScriptSlots))->PalScript::SetDirectory(dir);
    if ( (((PalScript *)g_ScriptSlots))->PalScript::FindSaveStateString(&unk_C11720, Buffer, (char *)0x100, v17) )
      unk_C11720.m_bEnabled = atoi((const char *)Buffer);
    else
      unk_C11720.m_bEnabled = 1;
    if ( monsterid == 1 )
      unk_C11720.m_nTodo_024 = 2;
    else
      unk_C11720.m_nTodo_024 = monsterid == 2;
    unk_C11720.m_nTodo_34 = (int)side;
    byte_C11751 = pMonster;
    if ( (((CCBSystem *)&g_pCBSystem))->CCBSystem::ProcMagicWait((unsigned int)g_nPartyRoles, 0) )
    {
      if ( !pMonster || !CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v15 = (char *)UISceneUpdate();
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::PlayCombatMusic(v15);
      }
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)6);
    }
  }
}

// 0x00408B60
void InitScriptObjArray()
{
  if ( (byte_BFDB78 & 1) == 0 )
  {
    LOBYTE(byte_BFDB78) = byte_BFDB78 | 1;
    (((UIListBox *)&g_pScriptObjArray))->UIListBox::ReleaseVtable();
  }
}

// 0x0040C230
char * ScriptUpdate(int dt)
{
  int *v1; // esi
  float v2; // st7
  float v3; // st7
  int *v4; // ecx
  float v5; // st7
  float v6; // st7
  char *result; // eax
  bool v8; // cl
  scAsmDecoder *v9; // edx
  int v10; // [esp+0x14] [ebp-0x24]
  int v11; // [esp+0x18] [ebp-0x20]
  ScriptSystem *v12; // [esp+0x1C] [ebp-0x1C]
  _BYTE v13[12]; // [esp+0x20] [ebp-0x18]
  gbVec3D v14; // [esp+0x2C] [ebp-0xC] BYREF

  v1 = (int *)(&g_RoleSlotBuf.dword_17AA450 + 150);
  do
  {
    ScriptSystem::UpdateTimers(*(float *)&dt);
    v1 += 2176;
  }
  while ( (int)v1 < (int)&g_RoleSystemArrayEnd );
  if ( g_RoleSystemMain.m_nMoveSubMode == 10 )
  {
    if ( unk_C08160.m_partyActor.m_pRoleObj )
      ScriptSystem::UpdateObjects(*(float *)&dt);
  }
  else if ( g_RoleSystemMain.m_nMoveSubMode == 11 )
  {
    todo_00419690((Actor *)&g_RoleSystemMain, *(float *)&dt);
  }
  else if ( g_RoleSystemMain.m_partyActor.m_pRoleObj )
  {
    ScriptSystem::UpdateTimers(*(float *)&dt);
  }
  if ( g_RoleSystemExtra1.m_partyActor.m_pRoleObj )
  {
    if ( g_RoleSystemExtra1.m_nMoveMode != 4 )
    {
      g_RoleSystemExtra1.m_partyActor.m_pRoleObj = 0;
      (((RoleSystem *)&g_RoleSystemExtra1))->RoleSystem::Notify();
    }
    ScriptSystem::UpdateTimers(*(float *)&dt);
  }
  if ( g_RoleSystemExtra0.m_partyActor.m_pRoleObj )
  {
    if ( g_RoleSystemExtra0.m_nMoveMode != 4 )
    {
      g_RoleSystemExtra0.m_partyActor.m_pRoleObj = 0;
      (((RoleSystem *)&g_RoleSystemExtra0))->RoleSystem::Notify();
    }
    ScriptSystem::UpdateTimers(*(float *)&dt);
    g_RoleSystemExtra0.m_fPosY = g_RoleSystemExtra0.m_fPosY + 80.0;
  }
  if ( g_nCurrentEventId <= 4 )
  {
    if ( g_nScriptEventParam )
    {
      v3 = *(float *)&g_nActor_BFDBAC + *(float *)&dt;
      *(float *)&g_nActor_BFDBAC = v3;
      if ( v3 >= 4.0f )
      {
        g_nActor_BFDBAC = 0;
        switch ( g_nCurrentEventId )
        {
          case 0u:
          case 1u:
            PalScriptMgr::RunScript(1, 0, 1);
            break;
          case 2u:
            ScriptSystem::RunWithDelay(0.5, 0, 1);
            break;
          case 3u:
            PalScriptMgr::RunScript(
              (__int64)((double)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * (_DWORD)dword_C10CC8)
                      * 0.050000001),
              0,
              1);
            break;
          case 4u:
            *(float *)&g_nActor_BFDBA8 = *(float *)&g_nActor_BFDBA8 * 1.5;
            PalScriptMgr::RunScript((__int64)*(float *)&g_nActor_BFDBA8, 0, 1);
            break;
          default:
            break;
        }
      }
    }
    else
    {
      switch ( g_nCurrentEventId )
      {
        case 0u:
          v2 = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * (_DWORD)dword_C10CC8 + 2] * 0.5f;
          if ( v2 < 1.0f )
            v2 = 1.0f;
          PalScriptMgr::RunScript(
            g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * (_DWORD)dword_C10CC8 + 2] - (__int64)v2,
            1,
            1);
          break;
        case 1u:
        case 2u:
          ScriptSystem::RunWithDelay(0.5, 1, 1);
          break;
        case 3u:
          PalScriptMgr::RunScript(
            (__int64)((double)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * (_DWORD)dword_C10CC8)
                    * 0.050000001),
            1,
            1);
          break;
        case 4u:
          *(float *)&g_nActor_BFDBA8 = (double)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame
                                               + 352 * (_DWORD)dword_C10CC8)
                                     * 0.5;
          PalScriptMgr::RunScript((__int64)*(float *)&g_nActor_BFDBA8, 1, 1);
          break;
        default:
          break;
      }
    }
    ++g_nScriptEventParam;
    v4 = (int *)&g_RoleSlotBuf.m_teamData3[2176 * (_DWORD)dword_C10CC8 + 589];
    v10 = (unsigned long)*v4;
    v11 = (unsigned long)v4[1];
    *(float *)v13 = *(float *)v4 - *(float *)&g_nScriptRolePosX;
    v12 = *((ScriptSystem **)v4 + 2);
    *(float *)&v13[4] = *(float *)&v11 - *(float *)&g_nScriptRolePosY;
    *(float *)&v13[8] = *(float *)&v12 - *(float *)&g_nScriptRolePosZ;
    v14 = *(gbVec3D *)v13;
    v5 = (((gbVec3D *)&v14))->gbVec3D::Length() + g_fScriptEventParam2;
    g_nScriptRolePosY = v11;
    g_nScriptRolePosX = v10;
    g_nScriptRolePosZ = (int)v12;
    g_fScriptEventParam2 = v5;
    if ( v5 >= 12.0 * 100.0 )
      (((ScriptSystem *)v12))->ScriptSystem::RunEvent(31, 1);
  }
  v6 = *(float *)&dword_C10CD0 + *(float *)&dt;
  *(float *)&dword_C10CD0 = v6;
  if ( v6 >= 60.0f )
  {
    g_RoleSlotBuf.m_partyActor.m_szTexture[7] = 0;
    g_RoleSlotBuf.m_partyActor.m_szTexture[8] = 0;
    g_RoleSlotBuf.m_partyActor.m_szTexture[9] = 0;
    g_RoleSlotBuf.m_partyActor.m_szTexture[10] = 0;
    byte_C10CC1 = 0;
  }
  NPCAnimUpdate(*(float *)&dt);
  result = (char *)(((PalScript *)&g_palScript))->PalScript::UpdateTimer(dt, 0);
  if ( byte_C10CC0 )
  {
    v8 = 1;
    v9 = 0;
    result = (char *)&unk_C0642C;
    do
    {
      if ( v9 != dword_C10CC8 )
        v8 = v8 && (*((_DWORD *)result + 9) != 4 || *(_DWORD *)result != 10);
      result += 8704;
      v9 = (scAsmDecoder *)((char *)v9 + 1);
    }
    while ( (int)result < (int)byte_C10E2C );
    if ( v8 )
    {
      byte_C10CC0 = 0;
      result = (char *)(((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamDist(g_nPtrArray_586154);
    }
  }
  if ( dword_C10CBC )
    return (char *)(*(int ( **)(int))(*(_DWORD *)dword_C10CBC + 20))(dword_C10CBC);
  return result;
}

// 0x0040DE10
char * MovePartyFollowers(char *bNotifyScript)
{
  RoleSystem *v1; // esi
  int *v2; // edi
  char *result; // eax
  float v4; // st7
  float v5; // st7
  float *v6; // eax
  float v7; // edx
  float v8; // st7
  float v9; // st6
  float *v10; // eax
  float v11; // edx
  float v12; // eax
  const gbVec3D *v13; // eax
  float v14; // st7
  float v15; // [esp+0xC] [ebp-0x78]
  float v16; // [esp+0xC] [ebp-0x78]
  float v17; // [esp+0x10] [ebp-0x74]
  float v18; // [esp+0x10] [ebp-0x74]
  float v19; // [esp+0x14] [ebp-0x70]
  float v20; // [esp+0x14] [ebp-0x70]
  float v21; // [esp+0x18] [ebp-0x6C]
  float *v22; // [esp+0x28] [ebp-0x5C]
  char *v23; // [esp+0x2C] [ebp-0x58]
  gbVec3D nFlags; // [esp+0x30] [ebp-0x54] BYREF
  struct gbVec3D v25; // [esp+0x3C] [ebp-0x48] BYREF
  float v26; // [esp+0x48] [ebp-0x3C]
  float v27; // [esp+0x4C] [ebp-0x38]
  float v28; // [esp+0x50] [ebp-0x34]
  float v29; // [esp+0x54] [ebp-0x30]
  float v30; // [esp+0x58] [ebp-0x2C]
  float v31; // [esp+0x5C] [ebp-0x28]
  gbVec3D v32; // [esp+0x60] [ebp-0x24] BYREF
  gbVec3D v33; // [esp+0x6C] [ebp-0x18] BYREF
  float pOut[3]; // [esp+0x78] [ebp-0xC] BYREF

  v1 = g_pRoleSystem;
  (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
  memset(&nFlags, 0, sizeof(nFlags));
  v23 = 0;
  v22 = (float *)&g_C10Data.m_nEffParamBase[2];
  v2 = (int *)(&g_RoleSlotBuf.dword_17AA450 + 153);
  do
  {
    result = (char *)v23;
    if ( v23[(_DWORD)(&g_RoleSlotBuf.dword_17AA450 + 148)] )
    {
      result = (char *)(v2 - 3);
      if ( v2 - 3 != (int *)v1 )
      {
        (((RoleSystem *)(v2 - 3)))->RoleSystem::SetTransform((int *)v1);
        LODWORD(nFlags.x) = (unsigned long)v1->m_rect.top;
        LODWORD(nFlags.y) = (unsigned long)v1->m_rect.right;
        v4 = *(float *)&v1->m_rect.bottom;
        nFlags.x = nFlags.x * -12.0f;
        nFlags.y = -12.0f * nFlags.y;
        nFlags.z = v4 * -12.0f;
        *((float *)v2 - 2) = nFlags.x + *((float *)v2 - 2);
        *((float *)v2 - 1) = nFlags.y + *((float *)v2 - 1);
        *(float *)v2 = nFlags.z + *(float *)v2;
        (((RoleSystem *)(v2 - 3)))->RoleSystem::NotifySceneChange(v1->m_partyActor.m_nState);
        memset(&v25, 0, sizeof(v25));
        v5 = *(v22 - 2);
        v19 = v5 * *(float *)&v1->m_childs.capacity;
        v17 = v5 * *(float *)&v1->m_childs.m_pData;
        v15 = v5 * *(float *)&v1->m_pfather;
        v26 = *v6;
        v27 = v6[1];
        v7 = v6[2];
        nFlags.x = v26;
        nFlags.y = v27;
        nFlags.z = v7;
        v8 = *(v22 - 1);
        v9 = v8 * *(float *)&v1->m_bcreateok;
        v28 = v7;
        v20 = v9;
        v18 = v8 * *(float *)&v1->m_childs.m_needscriptdel;
        v16 = v8 * *(float *)&v1->m_childs.m_nSize;
        v29 = *v10;
        v11 = v10[1];
        v12 = v10[2];
        v25.x = v29;
        v30 = v11;
        v31 = v12;
        v25.y = v11;
        v25.z = v12;
        (((gbVec3D *)&nFlags))->gbVec3D::operator+=(*(&v25));
        v13 = (const gbVec3D *)Vec3Lerp(pOut, (float *)&v1->m_rect.top, *v22, v21);
        (((gbVec3D *)&v25))->gbVec3D::operator=(*(v13));
        (((gbVec3D *)&nFlags))->gbVec3D::operator+=(*(&v25));
        v22 += 3;
        nFlags.x = nFlags.x + *(float *)&v1->m_fontcolor.Color;
        nFlags.y = nFlags.y + *(float *)&v1->m_wndcolor.Color;
        v14 = nFlags.z + *(float *)&v1->m_id;
        v2[155] = 1;
        nFlags.z = v14;
        (((RoleSystem *)(v2 - 3)))->RoleSystem::InitPathTracking(&nFlags.x);
        result = (char *)bNotifyScript;
        if ( bNotifyScript )
          PalScriptMgr::NotifyEvent();
      }
    }
    v2 += 2176;
    ++v23;
  }
  while ( (int)v2 < (int)flt_C1096C );
  return result;
}

// 0x0040E050
float * Vec3Lerp(float *pOut, float *pSrc, float fLerpFactor, float fMax)
{
  float *result; // eax
  float v5; // [esp+0x0] [ebp-0xC]
  float v6; // [esp+0x4] [ebp-0x8]
  float v7; // [esp+0x8] [ebp-0x4]

  v5 = fLerpFactor * *pSrc;
  v6 = fLerpFactor * pSrc[1];
  result = (float *)pOut;
  v7 = fLerpFactor * pSrc[2];
  *pOut = v5;
  pOut[1] = v6;
  pOut[2] = v7;
  return result;
}

// 0x0040E0A0
void RestorePartyFollowMode(int bNotifyScript)
{
  RoleSystem *v1; // edi
  int v2; // ebx
  RoleSystem *v3; // esi

  v1 = g_pRoleSystem;
  (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
  v2 = 0;
  v3 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
  do
  {
    if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v2) && v3->m_partyActor.m_pRoleObj && v3 != v1 )
    {
      (((RoleSystem *)v3))->RoleSystem::RestoreMoveMode((float *)&v1->m_fontcolor.Color);
      if ( bNotifyScript )
        PalScriptMgr::NotifyEvent();
    }
    v3 = (RoleSystem *)((char *)v3 + 8704);
    ++v2;
  }
  while ( v3 < (RoleSystem *)&g_RoleSystemArrayEnd );
}

// 0x0040E110
char SetupPartyFormation(int bNotifyScript)
{
  RoleSystem *v1; // edi
  RoleSystem *v2; // esi
  int *v3; // esi
  float v4; // st7
  float v5; // st7
  float v6; // edx
  const gbVec3D *v7; // eax
  const gbVec3D *v8; // eax
  const gbVec3D *v9; // eax
  float x; // edx
  float v11; // st7
  char result; // al
  int v13; // [esp+0x4] [ebp-0x60]
  float v14; // [esp+0x4] [ebp-0x60]
  float v15; // [esp+0x4] [ebp-0x60]
  float v16; // [esp+0x4] [ebp-0x60]
  int v17; // [esp+0x4] [ebp-0x60]
  int v18; // [esp+0x8] [ebp-0x5C]
  float *v19; // [esp+0x14] [ebp-0x50]
  int v20; // [esp+0x18] [ebp-0x4C]
  gbVec3D thisa; // [esp+0x1C] [ebp-0x48] BYREF
  float fLerpFactor; // [esp+0x28] [ebp-0x3C]
  float v23; // [esp+0x2C] [ebp-0x38]
  float v24; // [esp+0x30] [ebp-0x34]
  gbVec3D v25; // [esp+0x34] [ebp-0x30] BYREF
  float pOut[3]; // [esp+0x40] [ebp-0x24] BYREF
  float v27[3]; // [esp+0x4C] [ebp-0x18] BYREF
  float v28[3]; // [esp+0x58] [ebp-0xC] BYREF

  v1 = g_pRoleSystem;
  (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
  memset(&thisa, 0, sizeof(thisa));
  if ( byte_C10CC0 )
  {
    v2 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
    do
    {
      (((RoleSystem *)v2))->RoleSystem::Notify();
      v2 = (RoleSystem *)((char *)v2 + 8704);
    }
    while ( (int)v2 < (int)&g_RoleSystemArrayEnd );
  }
  v20 = 0;
  v19 = (float *)&g_C10Data.m_nEffParamBase[2];
  v3 = (int *)(&g_RoleSlotBuf.dword_17AA450 + 152);
  do
  {
    if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v20) && v3 - 2 != (int *)v1 )
    {
      *(v3 - 1) = v1->m_fontcolor.Color;
      *v3 = v1->m_wndcolor.Color;
      v3[1] = (unsigned long)v1->m_id;
      *(_QWORD *)&thisa.x = *(_QWORD *)&v1->m_rect.top;
      v4 = *(float *)&v1->m_rect.bottom;
      thisa.x = -12.0f * thisa.x;
      thisa.y = thisa.y * -12.0f;
      thisa.z = -12.0f * v4;
      *((float *)v3 - 1) = thisa.x + *((float *)v3 - 1);
      *(float *)v3 = thisa.y + *(float *)v3;
      *((float *)v3 + 1) = thisa.z + *((float *)v3 + 1);
      v3[38] = *(v3 - 1);
      v3[39] = (unsigned long)*v3;
      v3[40] = (unsigned long)v3[1];
      (((RoleSystem *)(v3 - 2)))->RoleSystem::NotifySceneChange(v1->m_partyActor.m_nState);
      (((RoleSystem *)(v3 - 2)))->RoleSystem::SetMoveSpeed(0.0, 0, v13);
      memset(&v25, 0, sizeof(v25));
      v5 = *(v19 - 2) * -3.0f;
      v6 = *v19;
      v23 = *(v19 - 1);
      fLerpFactor = v5;
      v23 = v23 * -3.0f;
      v24 = v6 * -3.0f;
      v7 = (const gbVec3D *)Vec3Lerp(pOut, (float *)&v1->m_pfather, fLerpFactor, v14);
      (((gbVec3D *)&thisa))->gbVec3D::operator=(*(v7));
      v8 = (const gbVec3D *)Vec3Lerp(v27, (float *)&v1->m_childs.m_nSize, v23, v15);
      (((gbVec3D *)&v25))->gbVec3D::operator=(*(v8));
      (((gbVec3D *)&thisa))->gbVec3D::operator+=(*(&v25));
      v9 = (const gbVec3D *)Vec3Lerp(v28, (float *)&v1->m_rect.top, v24, v16);
      (((gbVec3D *)&v25))->gbVec3D::operator=(*(v9));
      (((gbVec3D *)&thisa))->gbVec3D::operator+=(*(&v25));
      v19 += 3;
      thisa.x = thisa.x + *(float *)&v1->m_fontcolor.Color;
      x = thisa.x;
      thisa.y = thisa.y + *(float *)&v1->m_wndcolor.Color;
      v11 = thisa.z + *(float *)&v1->m_id;
      v3[156] = 1;
      thisa.z = v11;
      (((RoleSystem *)(v3 - 2)))->RoleSystem::GetActorState(_pal3_coerce_f64(__PAIR64__(LODWORD(thisa.z), LODWORD(x))), 2, v17, v18);
      if ( bNotifyScript )
        PalScriptMgr::NotifyEvent();
      byte_C10CC0 = 1;
    }
    v3 += 2176;
    ++v20;
  }
  while ( (int)v3 < (int)&g_palScript );
  result = byte_C10CC0;
  if ( byte_C10CC0 )
  {
    g_nPtrArray_586154 = SLODWORD(g_pCameraCtrl->m_fCamDist);
    return (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamDist(1142292480);
  }
  return result;
}

// 0x0040E3C0
char SetupPartyFormationWide(int bNotifyScript)
{
  RoleSystem *v1; // edi
  RoleSystem *v2; // esi
  int *v3; // esi
  float *v4; // ebx
  float v5; // edx
  float v6; // st7
  const gbVec3D *v7; // eax
  const gbVec3D *v8; // eax
  const gbVec3D *v9; // eax
  float v10; // st7
  float v11; // st6
  float y; // eax
  float z; // ecx
  char result; // al
  float v15; // [esp+0x10] [ebp-0x5C]
  float v16; // [esp+0x10] [ebp-0x5C]
  float v17; // [esp+0x10] [ebp-0x5C]
  int v18; // [esp+0x10] [ebp-0x5C]
  int v19; // [esp+0x20] [ebp-0x4C]
  gbVec3D v20; // [esp+0x24] [ebp-0x48] BYREF
  float fLerpFactor; // [esp+0x30] [ebp-0x3C]
  float v22; // [esp+0x34] [ebp-0x38]
  float v23; // [esp+0x38] [ebp-0x34]
  gbVec3D v24; // [esp+0x3C] [ebp-0x30] BYREF
  float pOut[3]; // [esp+0x48] [ebp-0x24] BYREF
  float v26[3]; // [esp+0x54] [ebp-0x18] BYREF
  float v27[3]; // [esp+0x60] [ebp-0xC] BYREF

  v1 = g_pRoleSystem;
  (((RoleSystem *)&g_pRoleSystem))->RoleSystem::Notify();
  memset(&v20, 0, sizeof(v20));
  if ( byte_C10CC0 )
  {
    v2 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
    do
    {
      (((RoleSystem *)v2))->RoleSystem::Notify();
      v2 = (RoleSystem *)((char *)v2 + 8704);
    }
    while ( (int)v2 < (int)&g_RoleSystemArrayEnd );
  }
  v19 = 0;
  v3 = (int *)(&g_RoleSlotBuf.dword_17AA450 + 153);
  v4 = (float *)&g_C10Data.m_nEffParamBase[2];
  do
  {
    if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v19) && v3 - 3 != (int *)v1 )
    {
      v5 = *v4;
      v6 = *(v4 - 2) + *(v4 - 2);
      v22 = *(v4 - 1);
      fLerpFactor = v6;
      v22 = v22 + v22;
      v23 = v5 + v5;
      v7 = (const gbVec3D *)Vec3Lerp(pOut, (float *)&v1->m_pfather, fLerpFactor, v15);
      (((gbVec3D *)&v20))->gbVec3D::operator=(*(v7));
      v8 = (const gbVec3D *)Vec3Lerp(v26, (float *)&v1->m_childs.m_nSize, v22, v16);
      (((gbVec3D *)&v24))->gbVec3D::operator=(*(v8));
      (((gbVec3D *)&v20))->gbVec3D::operator+=(*(&v24));
      v9 = (const gbVec3D *)Vec3Lerp(v27, (float *)&v1->m_rect.top, v23, v17);
      (((gbVec3D *)&v24))->gbVec3D::operator=(*(v9));
      (((gbVec3D *)&v20))->gbVec3D::operator+=(*(&v24));
      v10 = v20.x + *(float *)&v1->m_fontcolor.Color;
      v4 += 3;
      v20.x = v10;
      v11 = v20.y + *(float *)&v1->m_wndcolor.Color;
      v20.y = v11;
      y = v20.y;
      v20.z = v20.z + *(float *)&v1->m_id;
      z = v20.z;
      *v3 = LODWORD(v20.z);
      *((float *)v3 - 2) = v10;
      *((float *)v3 - 1) = v11;
      *((float *)v3 + 38) = y;
      *((float *)v3 + 39) = z;
      *((float *)v3 + 37) = v10;
      (((RoleSystem *)(v3 - 3)))->RoleSystem::NotifySceneChange(v1->m_partyActor.m_nState);
      (((RoleSystem *)(v3 - 3)))->RoleSystem::SetMoveSpeed(0.0, 0, v18);
      v3[155] = 1;
      (((RoleSystem *)(v3 - 3)))->RoleSystem::StartLinearMove((int *)&v1->m_fPosX, 2);
      if ( bNotifyScript )
        PalScriptMgr::NotifyEvent();
      byte_C10CC0 = 1;
    }
    v3 += 2176;
    ++v19;
  }
  while ( (int)v3 < (int)flt_C1096C );
  result = byte_C10CC0;
  if ( byte_C10CC0 )
  {
    g_nPtrArray_586154 = SLODWORD(g_pCameraCtrl->m_fCamDist);
    return (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamDist(1142292480);
  }
  return result;
}

// 0x0040E840
int * AddNPCToPartySlot(int nRoleSlot, int nNpcId)
{
  int v2; // ebx
  __int16 v3; // bp
  float *v4; // edx
  int v5; // eax
  float *v6; // ecx
  int v7; // eax
  __int16 v8; // ax
  Array *v9; // esi
  char *m_pData; // ecx
  int *v11; // edi
  int m_nSize; // ebx
  unsigned int v13; // ebp
  int v14; // edx
  unsigned int v15; // eax
  char *v16; // eax
  int *v17; // ebp
  char *j; // ebx
  int v19; // eax
  char *v21; // ecx
  char *i; // eax
  int *v23; // ecx
  int v24; // [esp+0x18] [ebp-0x8]
  int RoleNum; // [esp+0x1C] [ebp-0x4]
  int nRoleSlota; // [esp+0x24] [ebp+0x4]
  int nNpcIda; // [esp+0x28] [ebp+0x8]

  RefreshPartyRoleData();
  v2 = 0;
  v3 = 0;
  v4 = (float *)(&g_RoleSlotBuf.m_partyActor.m_fDirZ + 352 * nRoleSlot);
  while ( 2 )
  {
    v5 = 0;
    v6 = (float *)v4;
    do
    {
      if ( nNpcId == *(_DWORD *)v6 )
      {
        v7 = v5 + 8 * (v2 + 176 * nRoleSlot);
        v3 = *((unsigned __int8 *)&g_RoleSlotBuf.m_FrameA.m_childs.m_pData + v7);
        v8 = *((unsigned __int8 *)&g_RoleSlotBuf.m_fRotAxisZ + v7);
        goto LABEL_9;
      }
      ++v5;
      ++v6;
    }
    while ( v5 < 8 );
    ++v2;
    v4 += 8;
    if ( v2 < 6 )
      continue;
    break;
  }
  v8 = 0;
LABEL_9:
  LOWORD(v24) = v3;
  HIWORD(v24) = v8;
  v9 = (Array *)(&g_SceneMgrPrefix + nRoleSlot);
  RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(nNpcId);
  m_pData = (char *)v9->m_pData;
  v11 = (int *)m_pData;
  if ( (v9->m_nCapacity - (int)m_pData) / 12 )
  {
    (((Array *)v9))->Array::Insert(m_pData, m_pData);
    (((Array *)v9))->Array::Erase((int)v9->m_pData, 1 - (v9->m_pData - (char *)v11) / 12);
    for ( i = v9->m_pData; v11 != (int *)i; v23[2] = RoleNum )
    {
      v23 = (int *)v11;
      v11 += 3;
      *v23 = nNpcId;
      v23[1] = v24;
    }
    v9->m_pData += 12;
    return (int *)NPC::InitAll();
  }
  else
  {
    m_nSize = v9->m_nSize;
    if ( !m_nSize || (v13 = (int)&m_pData[-m_nSize] / 12, v13 <= 1) )
      v13 = 1;
    if ( m_nSize )
      v14 = (int)&m_pData[-m_nSize] / 12;
    else
      v14 = 0;
    v15 = v14 + v13;
    nRoleSlota = v14 + v13;
    if ( (int)(v14 + v13) < 0 )
      v15 = 0;
    v16 = (char *)operator new(12 * v15);
    v17 = (int *)v9->m_nSize;
    nNpcIda = (int)v16;
    for ( j = v16; v17 != v11; j += 12 )
    {
      Array::Copy(j);
      v17 += 3;
    }
    (((Array *)v9))->Array::Erase((int)j, 1);
    (((Array *)v9))->Array::Insert(v11, v9->m_pData);
    nullsub_2(v9->m_nSize, v9->m_pData);
    operator delete((void *)v9->m_nSize);
    v9->m_nCapacity = nNpcIda + 12 * nRoleSlota;
    v19 = v9->m_nSize;
    if ( v19 )
    {
      v21 = (char *)v9->m_pData;
      v9->m_nSize = nNpcIda;
      v9->m_pData = (char *)(nNpcIda + 4 * (3 * ((int)&v21[-v19] / 12) + 3));
    }
    else
    {
      v9->m_nSize = nNpcIda;
      v9->m_pData = (char *)(nNpcIda + 12);
    }
    return (int *)NPC::InitAll();
  }
}

// 0x0040F0C0
void SaveGameState(FILE *fp)
{
  FILE *v1; // esi
  int v2; // eax
  int *p_nState; // edi
  int *p_nCurCount; // edi
  _BYTE Buffer[4]; // [esp+0x4] [ebp-0x64] BYREF
  float m_fPosX; // [esp+0x8] [ebp-0x60]
  float m_fPosY; // [esp+0xC] [ebp-0x5C]
  float m_fPosZ; // [esp+0x10] [ebp-0x58]
  char m_nState; // [esp+0x14] [ebp-0x54]
  float v10; // [esp+0x18] [ebp-0x50]
  _BYTE v11[72]; // [esp+0x20] [ebp-0x48] BYREF

  v1 = (FILE *)fp;
  if ( fp )
  {
    v2 = g_nUpdateInterval;
    if ( g_nUpdateInterval < 35 )
    {
      v2 = 35;
      g_nUpdateInterval = 35;
    }
    g_nFrameRate = v2;
    fwrite(&nVal, 4u, 1u, fp);
    fwrite(&g_nFrameRate, 4u, 1u, v1);
    fwrite(g_nRoleInitLevel, 0x18u, 1u, v1);
    fwrite(&g_RoleSlotBuf, 0x1B80u, 1u, v1);
    fwrite(&g_RoleSlotBuf.dword_17AA450 + 148, 5u, 1u, v1);
    (((NPC *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->NPC::SaveToStream(v1);
    (((NPC *)(&g_RoleSlotBuf.dword_17AA450 + 134)))->NPC::ReadBufferData(v1);
    Buffer[0] = g_RoleSystemMain.m_partyActor.m_pRoleObj;
    m_fPosY = g_RoleSystemMain.m_fPosY;
    m_nState = g_RoleSystemMain.m_partyActor.m_nState;
    m_fPosX = g_RoleSystemMain.m_fPosX;
    m_fPosZ = g_RoleSystemMain.m_fPosZ;
    v10 = g_fScriptTimeAccum;
    fwrite(Buffer, 0x1Cu, 1u, v1);
    p_nState = (int *)&g_ScriptCounters[0].nState;
    do
    {
      LOBYTE(fp) = *(_BYTE *)p_nState;
      fwrite(&fp, 1u, 1u, v1);
      p_nState += 4;
    }
    while ( (int)p_nState < (int)&dword_C020F4 );
    p_nCurCount = (int *)&g_ScriptCounters[0].nCurCount;
    do
    {
      LOBYTE(fp) = *(_BYTE *)p_nCurCount;
      fwrite(&fp, 1u, 1u, v1);
      p_nCurCount += 4;
    }
    while ( (int)p_nCurCount < (int)&g_RoleSystemMain );
    fwrite(&g_nMagicSlotCountA, 8u, 1u, v1);
    memset(v11, 0, sizeof(v11));
    fwrite(v11, 0x48u, 1u, v1);
  }
}

// 0x0040F230
int * LoadGameState(FILE *fp)
{
  ScriptSystem *v1; // ecx
  int *result; // eax
  FILE *v3; // esi
  int *p_nState; // edi
  int *p_nCurCount; // edi
  int *p_m_nModelParamB; // esi
  int v7; // edi
  int v8; // edx
  int Buffer; // [esp+0x4] [ebp-0x64] BYREF
  float v10; // [esp+0x8] [ebp-0x60]
  float v11; // [esp+0xC] [ebp-0x5C]
  float v12; // [esp+0x10] [ebp-0x58]
  int v13; // [esp+0x14] [ebp-0x54]
  float fDeltaTime; // [esp+0x18] [ebp-0x50]
  _BYTE v15[72]; // [esp+0x20] [ebp-0x48] BYREF

  result = (int *)(((ScriptSystem *)v1))->ScriptSystem::Cleanup();
  v3 = (FILE *)fp;
  if ( fp )
  {
    fread(&nVal, 4u, 1u, fp);
    fread(&g_nFrameRate, 4u, 1u, v3);
    g_nUpdateInterval = g_nFrameRate;
    if ( g_nFrameRate < 35 )
      g_nUpdateInterval = 35;
    fread(g_nRoleInitLevel, 0x18u, 1u, v3);
    fread(&g_RoleSlotBuf, 0x1B80u, 1u, v3);
    fread(&g_RoleSlotBuf.dword_17AA450 + 148, 5u, 1u, v3);
    (((NPC *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->NPC::LoadFromStream(v3);
    (((NPC *)(&g_RoleSlotBuf.dword_17AA450 + 134)))->NPC::LoadBufferFromStream(v3);
    v10 = 0.0f;
    v11 = 0.0f;
    v12 = 0.0f;
    fread(&Buffer, 0x1Cu, 1u, v3);
    g_RoleSystemMain.m_partyActor.m_pRoleObj = (unsigned __int8)Buffer;
    g_RoleSystemMain.m_fPosX = v10;
    g_RoleSystemMain.m_partyActor.m_nState = (unsigned __int8)v13;
    g_RoleSystemMain.m_fPosY = v11;
    g_RoleSystemMain.m_fPosZ = v12;
    (((RoleSystem *)&g_RoleSystemMain))->RoleSystem::UpdateMovement(fDeltaTime, 1);
    p_nState = (int *)&g_ScriptCounters[0].nState;
    do
    {
      fread(&fp, 1u, 1u, v3);
      p_nState += 4;
      *(p_nState - 4) = (unsigned __int8)fp;
    }
    while ( (int)p_nState < (int)&dword_C020F4 );
    p_nCurCount = (int *)&g_ScriptCounters[0].nCurCount;
    do
    {
      fread(&fp, 1u, 1u, v3);
      p_nCurCount += 4;
      *(p_nCurCount - 4) = (unsigned __int8)fp;
    }
    while ( (int)p_nCurCount < (int)&g_RoleSystemMain );
    fread(&g_nMagicSlotCountA, 8u, 1u, v3);
    memset(v15, 0, sizeof(v15));
    fread(v15, 0x48u, 1u, v3);
    NPC::SetRoleMode(nVal);
    p_m_nModelParamB = (int *)&g_RoleSlotBuf.m_partyActor.m_nModelParamB;
    do
    {
      if ( *p_m_nModelParamB )
        p_m_nModelParamB[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*p_m_nModelParamB);
      if ( p_m_nModelParamB[3] )
        p_m_nModelParamB[5] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_m_nModelParamB[3]);
      if ( p_m_nModelParamB[6] )
        p_m_nModelParamB[8] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_m_nModelParamB[6]);
      if ( p_m_nModelParamB[9] )
        p_m_nModelParamB[11] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_m_nModelParamB[9]);
      if ( p_m_nModelParamB[12] )
        p_m_nModelParamB[14] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_m_nModelParamB[12]);
      if ( p_m_nModelParamB[15] )
        p_m_nModelParamB[17] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_m_nModelParamB[15]);
      (((RoleSystem *)(p_m_nModelParamB - 213)))->RoleSystem::RecalcAggregatedStats(0);
      result = (int *)(p_m_nModelParamB + 30);
      v7 = 12;
      do
      {
        v8 = *(result - 12);
        if ( *result < v8 )
        {
          if ( *result <= 0 )
            *result = 0;
        }
        else
        {
          *result = v8;
        }
        ++result;
        --v7;
      }
      while ( v7 );
      p_m_nModelParamB += 352;
    }
    while ( (int)p_m_nModelParamB < (int)dword_C06274 );
  }
  return result;
}

// 0x0040F4B0
int RefreshPartyRoleData()
{
  PtrArray *p_m_childs; // edi
  int *p_m_pData; // ebx
  int v2; // esi
  int i; // esi
  int v4; // ebp
  PtrArray *v5; // esi
  int j; // edi
  int *v7; // esi
  int result; // eax
  PtrArray *v9; // [esp+0x10] [ebp-0x24]
  int v10; // [esp+0x14] [ebp-0x20]
  int v11; // [esp+0x18] [ebp-0x1C]

  p_m_childs = (PtrArray *)&g_RoleSlotBuf.m_FrameA.m_childs;
  v11 = 0;
  v10 = 0;
  v9 = (PtrArray *)&g_RoleSlotBuf.m_FrameA.m_childs;
  p_m_pData = (int *)&g_SceneMgrPrefix.m_pData;
  while ( 1 )
  {
    v2 = *(p_m_pData - 1);
    nullsub_2(v2, *p_m_pData);
    *p_m_pData = v2;
    for ( i = 0; i < 6; ++i )
    {
      if ( *((_BYTE *)&p_m_childs[-18] + i - 8) )
        RoleSystem::CheckVisible();
    }
    v4 = 0;
    v5 = (PtrArray *)p_m_childs;
    do
    {
      for ( j = 0; j < 8; ++j )
      {
        if ( LOBYTE(v5[-6].m_pData) )
          RoleSystem::CheckVisible();
        v5 = (PtrArray *)((char *)v5 + 1);
      }
      ++v4;
    }
    while ( v4 < 6 );
    v7 = (int *)*(p_m_pData - 1);
    for ( result = *p_m_pData; v7 != (int *)*p_m_pData; v7 += 3 )
    {
      v7[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v7);
      result = (unsigned long)*p_m_pData;
    }
    p_m_pData += 4;
    v10 += 352;
    v9 += 88;
    v11 += 44;
    if ( (int)p_m_pData >= (int)&g_RoleSlotBuf.m_wndcolor )
      break;
    p_m_childs = (PtrArray *)v9;
  }
  return result;
}

// 0x0040FC90
void AddMoney(int nAmount)
{
  int v1; // ecx
  char *v2; // eax
  char *v3; // eax
  CScreenMode *Instance; // eax
  int v5; // [esp-0x4] [ebp-0x104]
  int v6; // [esp-0x4] [ebp-0x104]
  char Buffer[256]; // [esp+0x0] [ebp-0x100] BYREF

  v1 = *(&g_RoleSlotBuf.dword_17AA450 + 147);
  *(&g_RoleSlotBuf.dword_17AA450 + 147) = *(&g_RoleSlotBuf.dword_17AA450 + 147) + nAmount < 0
                                        ? 0
                                        : *(&g_RoleSlotBuf.dword_17AA450 + 147) + nAmount;
  if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) )
  {
    if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) - v1 >= 0 )
    {
      v6 = *(&g_RoleSlotBuf.dword_17AA450 + 147) - v1;
      v3 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("getmoney");
      _snprintf(Buffer, 0xFFu, v3, v6);
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition("wa006", 1);
    }
    else
    {
      v5 = v1 - *(&g_RoleSlotBuf.dword_17AA450 + 147);
      v2 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("lossmoney");
      _snprintf(Buffer, 0xFFu, v2, v5);
    }
    InputSystem::ProcessFrame(Buffer);
  }
  else
  {
    strcpy((char *)Buffer, (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(name));
    InputSystem::ProcessFrame(Buffer);
  }
}

// 0x0040FF70
char * SetRoleLevelAndRefresh(int nRoleIdx, int nLevel)
{
  int v2; // ebx
  int *v3; // esi
  int v4; // eax
  CCBSystem *v5; // eax
  CCBRoleState *m_pRoleState; // ebx
  char *result; // eax
  int v8; // ecx

  RefreshPartyRoleData();
  v2 = 6;
  v3 = (int *)(&dword_C10BA0 + 12 * nRoleIdx);
  do
  {
    v4 = (unsigned long)v3[1];
    if ( nLevel >= v4 && v4 > 0 && *v3 )
    {
      (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*v3);
      RoleSystem::CheckVisible();
    }
    v3 += 2;
    --v2;
  }
  while ( v2 );
  NPC::InitAll();
  v5 = g_pCBSystem;
  m_pRoleState = g_pCBSystem->m_pRoleState;
  *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * nRoleIdx) = nLevel;
  *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + 352 * nRoleIdx) = (((CCBRoleState *)v5->m_pRoleState))->CCBRoleState::GetRoleCount(nLevel);
  *(&g_RoleSlotBuf.m_partyActor.m_nPathEnabled + 352 * nRoleIdx) = (((CCBRoleState *)m_pRoleState))->CCBRoleState::GetSlotState(nRoleIdx, nLevel);
  *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fScale + 352 * nRoleIdx) = (((CCBRoleState *)m_pRoleState))->CCBRoleState::CalcSpeedByLevel(nRoleIdx, nLevel);
  *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixA + 352 * nRoleIdx) = (((CCBRoleState *)m_pRoleState))->CCBRoleState::GetActionTypeBySlot(nRoleIdx, nLevel);
  *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixB + 352 * nRoleIdx) = (((CCBRoleState *)m_pRoleState))->CCBRoleState::CalcDefenseByLevel(nRoleIdx, nLevel);
  *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixC + 352 * nRoleIdx) = (((CCBRoleState *)m_pRoleState))->CCBRoleState::CalcDamage(nRoleIdx, nLevel);
  (((RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * nRoleIdx)))->RoleSystem::RecalcAggregatedStats(0);
  result = (char *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nRoleIdx + 2];
  v8 = 12;
  do
  {
    *(_DWORD *)result = *((_DWORD *)result - 12);
    result += 4;
    --v8;
  }
  while ( v8 );
  return result;
}

// 0x004105B0
int NPCAnimUpdate(float fVal)
{
  char v1; // bl
  int v2; // edi
  GRPinput *v3; // esi
  float v4; // st7
  float v5; // st6
  float v6; // st6
  float v7; // st7
  int v8; // edx
  int i; // esi
  int v10; // edi
  int v11; // esi
  GRPinput *v12; // ecx
  int result; // eax
  int v14; // eax
  void **v15; // ecx
  int v16; // ecx
  unsigned __int8 v17; // [esp+0x13] [ebp-0x15]
  int m_mouseMinX; // [esp+0x14] [ebp-0x14]
  _DWORD a2[4]; // [esp+0x18] [ebp-0x10] BYREF
  int fVala; // [esp+0x2C] [ebp+0x4]

  v1 = 0;
  v2 = 0;
  m_mouseMinX = -1;
  v17 = 0;
  if ( nIndex <= 0 )
    goto LABEL_37;
  do
  {
    v3 = (GRPinput *)g_pScriptObjArray[v2];
    (((GRPinput *)v3))->GRPinput::SetJoystickFreePos(fVal);
    if ( LOBYTE(v3->m_lpDIDKeyboard) )
    {
      if ( v3->m_mouseMaxY == 1 )
      {
        if ( v3->m_mouseMinX > m_mouseMinX )
          m_mouseMinX = v3->m_mouseMinX;
        v4 = *(float *)&v3->m_mouseMaxX - 1.5f;
        if ( v4 >= 0.0f )
          v5 = v4;
        else
          v5 = 0.0f;
        v6 = 1.0f - v5 * 0.4000000059604645f;
        if ( v6 < 0.0f )
          v6 = 0.0f;
        if ( (unsigned __int8)(__int64)(v6 * 255.0) > v17 )
        {
          if ( v4 < 0.0f )
            v4 = 0.0f;
          v7 = 1.0f - v4 * 0.4000000059604645f;
          if ( v7 < 0.0f )
            v7 = 0.0f;
          v17 = (__int64)(v7 * 255.0);
        }
      }
    }
    else
    {
      if ( v3 )
        (*(void ( **)(GRPinput *, int))v3->m_lpDI)(v3, 1);
      if ( v2 >= 0 && v2 < nIndex )
        g_pScriptObjArray[v2] = 0;
      v1 = 1;
    }
    v8 = nIndex;
    ++v2;
  }
  while ( v2 < nIndex );
  if ( v1 )
  {
    for ( i = 0; i < nIndex; v8 = nIndex )
    {
      if ( i >= 0 && i < v8 && g_pScriptObjArray[i] )
        ++i;
      else
        (((PtrArray *)&g_pScriptObjArray))->PtrArray::RemoveAt(i, 1);
    }
    v10 = 0;
    v11 = 40;
    if ( v8 > 0 )
    {
      do
      {
        v12 = (GRPinput *)g_pScriptObjArray[v10];
        if ( v12->m_mouseMaxY == 1 )
        {
          (((GRPinput *)v12))->GRPinput::GetMouseSensitivity(v11);
          v11 += 24;
        }
        v8 = nIndex;
        ++v10;
      }
      while ( v10 < nIndex );
    }
  }
  if ( m_mouseMinX == -1 )
  {
LABEL_37:
    (((UITextArea *)&dword_BFDAB0))->UITextArea::ShowWindow(0);
  }
  else
  {
    v14 = 0;
    if ( v8 > 0 )
    {
      v15 = g_pScriptObjArray;
      do
      {
        if ( *((_DWORD *)*v15 + 7) == 1 )
          ++v14;
        ++v15;
        --v8;
      }
      while ( v8 );
    }
    a2[1] = 5;
    v16 = 10 * m_mouseMinX + 64;
    a2[3] = 24 * v14 + 30;
    a2[0] = (g_DrvInfo.width - v16) / 2 < 0 ? 0 : (g_DrvInfo.width - v16) / 2;
    a2[2] = v16 + a2[0];
    (((UIWnd *)&dword_BFDAB0))->UIWnd::sub_445FA0(a2);
    (((UITextArea *)&dword_BFDAB0))->UITextArea::ShowWindow(1);
    (((UIScene *)&dword_BFDAB0))->UIScene::SetState(1);
    *(_WORD *)((char *)&fVala + 1) = -1;
    LOBYTE(fVala) = -1;
    HIBYTE(fVala) = v17;
    (((NPC *)&dword_BFDAB0))->NPC::UpdateAnim(fVala);
  }
  return result;
}

// 0x00411220
int * AssignInt(int *pDst, int *pSrc)
{
  int *result; // eax

  result = (int *)pDst;
  if ( pDst )
    *pDst = *pSrc;
  return result;
}

// 0x00411900
int Role_Role(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  char p_BYTE; // [esp+0x57] [ebp-0x15] BYREF
  int v6; // [esp+0x58] [ebp-0x14]
  int v7; // [esp+0x5C] [ebp-0x10]
  int v8; // [esp+0x68] [ebp-0x4]

  v2 = v1;
  *(_DWORD *)(v1 + 4) = 0;
  *(_DWORD *)(v1 + 8) = 0;
  *(_DWORD *)(v1 + 12) = 0;
  v7 = v1;
  *(_DWORD *)(v1 + 16) = 1094713344;
  ((gbVec3D *)(v1 + 20))->gbVec3D::gbVec3D(0.0, 0.0, 1.0);
  ((gbVec3D *)(v2 + 32))->gbVec3D::gbVec3D(1.0, 0.0, 0.0);
  ((gbVec3D *)(v2 + 44))->gbVec3D::gbVec3D(0.0, 1.0, 0.0);
  v8 = 0;
  *(_DWORD *)(v2 + 60) = 0;
  (((RenderTarget3 *)(v2 + 64)))->RenderTarget3::ClearEffects();
  LOBYTE(v8) = 2;
  (((RoleSystem *)(v2 + 96)))->RoleSystem::ClearColors(&p_BYTE);
  *(_DWORD *)(v2 + 148) = 0;
  *(_DWORD *)(v2 + 152) = 0;
  *(_DWORD *)(v2 + 156) = 0;
  LOBYTE(v8) = 3;
  *(_DWORD *)(v2 + 160) = 0;
  *(_DWORD *)(v2 + 164) = 0;
  *(_DWORD *)(v2 + 168) = 0;
  v3 = v2 + 308;
  v6 = 16;
  do
  {
    v3 += 12;
    --v6;
  }
  while ( v6 );
  ((gbVec3D *)(v2 + 644))->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
  ((gbVec3D *)(v2 + 656))->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
  ((gbVec3D *)(v2 + 668))->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
  FastInit((Actor *)(v2 + 680));
  *(_DWORD *)(v2 + 1240) = 0;
  *(_DWORD *)(v2 + 1244) = 0;
  *(_DWORD *)(v2 + 1248) = 0;
  *(_DWORD *)(v2 + 1296) = 0;
  *(_DWORD *)(v2 + 1300) = 0;
  *(_DWORD *)(v2 + 1304) = 0;
  *(_DWORD *)(v2 + 1308) = 0;
  *(_DWORD *)(v2 + 1312) = 0;
  *(_DWORD *)(v2 + 1316) = 0;
  *(_DWORD *)(v2 + 1320) = 0;
  *(_DWORD *)(v2 + 1324) = 0;
  *(_DWORD *)(v2 + 1328) = 0;
  *(_DWORD *)(v2 + 1332) = 0;
  *(_DWORD *)(v2 + 1336) = 0;
  *(_DWORD *)(v2 + 1340) = 0;
  *(_DWORD *)(v2 + 1344) = 0;
  *(_DWORD *)(v2 + 1348) = 0;
  *(_DWORD *)(v2 + 1352) = 0;
  *(_DWORD *)(v2 + 1364) = 0;
  *(_DWORD *)(v2 + 1368) = 0;
  *(_DWORD *)(v2 + 1372) = 0;
  *(_DWORD *)(v2 + 1376) = 0;
  *(_DWORD *)(v2 + 1380) = 0;
  *(_DWORD *)(v2 + 1384) = 0;
  LOBYTE(v8) = 4;
  *(_DWORD *)(v2 + 1468) = 0;
  *(_DWORD *)(v2 + 1472) = 0;
  *(_DWORD *)(v2 + 1476) = 0;
  ((gbVec3D *)(v2 + 8664))->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
  ((gbVec3D *)(v2 + 8676))->gbVec3D::gbVec3D(0.0, 0.0, 0.0);
  *(_DWORD *)(v2 + 4552) = 0;
  *(_DWORD *)(v2 + 8692) = 0;
  *(_DWORD *)(v2 + 8696) = 0;
  *(_DWORD *)(v2 + 8700) = 0;
  g_palScript._todo_764 = gbCrc32Compute(pszOpt1);
  (((RoleSystem *)v2))->RoleSystem::InitDefaultState();
  return v2;
}

// 0x00411CA0
int ScriptObj__ScriptObj(int nVal)
{
  PalScript *v1; // ecx
  PalScript *v2; // esi
  int *p_m_bCreated; // ebx
  int v4; // eax
  int v5; // edi
  int v6; // eax
  void **v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int v11; // edx
  int *v12; // eax
  int v13; // ecx
  void *v15; // [esp-0xC] [ebp-0x38]
  void **v16; // [esp+0x0] [ebp-0x2C]
  _DWORD v17[4]; // [esp+0x10] [ebp-0x1C] BYREF
  int v18; // [esp+0x28] [ebp-0x4]

  v2 = (PalScript *)v1;
  p_m_bCreated = (int *)&v1->m_bCreated;
  v18 = 3;
  (((PalScript *)v1))->PalScript::DestroyScript();
  (((NPC *)((char *)&v2->m_RoleSlotArray.script_state + 284)))->NPC::FreeBuffer();
  v4 = *(_DWORD *)&v2->m_nTodo_04C[64];
  for ( LOBYTE(v18) = 2; v4; v4 = *(_DWORD *)&v2->m_nTodo_04C[64] )
  {
    v5 = *(_DWORD *)&v2->m_nTodo_04C[32] + 16;
    v6 = v4 - 1;
    *(_DWORD *)&v2->m_nTodo_04C[32] = v5;
    *(_DWORD *)&v2->m_nTodo_04C[64] = v6;
    if ( !v6 || v5 == *(_DWORD *)&v2->m_nTodo_04C[28] )
    {
      v7 = (void **)(*(void ***)&v2->m_nTodo_04C[36]);
      *(_DWORD *)&v2->m_nTodo_04C[36] = (unsigned long)(v7 + 1);
      operator delete(*v7);
      if ( *(_DWORD *)&v2->m_nTodo_04C[64] )
      {
        v12 = (int *)(*(int **)&v2->m_nTodo_04C[36]);
        v13 = (unsigned long)*v12;
        *(_DWORD *)&v2->m_nTodo_04C[24] = (unsigned long)*v12;
        *(_DWORD *)&v2->m_nTodo_04C[28] = v13 + 4096;
        *(_DWORD *)&v2->m_nTodo_04C[32] = v13;
        *(_DWORD *)&v2->m_nTodo_04C[36] = (_DWORD)v12;
      }
      else
      {
        (((PalScriptMgr *)v17))->PalScriptMgr::Get_result();
        v8 = v17[0];
        v9 = v17[1];
        v10 = v17[3];
        v11 = v17[2];
        *(_DWORD *)&v2->m_nTodo_04C[24] = v17[0];
        *(_DWORD *)&v2->m_nTodo_04C[28] = v9;
        *(_DWORD *)&v2->m_nTodo_04C[32] = v11;
        *(_DWORD *)&v2->m_nTodo_04C[36] = v10;
        *(_DWORD *)&v2->m_nTodo_04C[40] = v8;
        v15 = (void *)(*(void **)&v2->m_nTodo_04C[56]);
        *(_DWORD *)&v2->m_nTodo_04C[44] = v9;
        *(_DWORD *)&v2->m_nTodo_04C[48] = v11;
        *(_DWORD *)&v2->m_nTodo_04C[52] = v10;
        operator delete(v15);
      }
    }
  }
  LOBYTE(v18) = 1;
  (((RenderTarget3 *)v2 != 0 ? (RenderTarget3 *)&v2->m_pActorData : 0))->RenderTarget3::_nearby_4b6ca0(v16);
  return v2 != 0 ? (unsigned int)p_m_bCreated : 0;
}

// 0x00413800
gbVec3D * Vec3Cross(gbVec3D *pOut, gbVec3D *pA, gbVec3D *pB)
{
  gbVec3D *result; // eax
  _BYTE v4[12]; // [esp+0x0] [ebp-0xC]

  *(float *)v4 = pA->x - pB->x;
  *(float *)&v4[4] = pA->y - pB->y;
  result = (gbVec3D *)pOut;
  *pOut = *(gbVec3D *)v4;
  return result;
}

// 0x00418170
int Role_CheckOBBCollision(int nVal)
{
  int v1; // ecx
  int v2; // esi
  gbOBBox actionId; // [esp+0x4] [ebp-0x4C] BYREF

  v2 = v1;
  (((Actor *)(v2 + 680)))->Actor::PlayAction((int)&actionId);
  actionId.trans.tx = actionId.trans.tx + *(float *)(v2 + 160);
  actionId.trans.ty = actionId.trans.ty + *(float *)(v2 + 164);
  actionId.trans.tz = actionId.trans.tz + *(float *)(v2 + 168);
  actionId.xlen = actionId.xlen * 0.6000000238418579f;
  return (((gbOBBox *)&actionId))->gbOBBox::IsColOBB((gbOBBox *)nVal);
}

// 0x00419690
// positive sp value has been detected, the output may be wrong!
void todo_00419690(Actor *_this, float fFrameDt)
{
  void **p_m_InnerActor; // edi
  double v4; // st7
  char v6; // c0
  long double v7; // st7
  int v8; // [esp-0x4] [ebp-0xC]

  p_m_InnerActor = (void **)&_this->m_InnerActor;
  (((Actor *)&_this->m_InnerActor))->Actor::QueryState(v8);
  v4 = fFrameDt + *(float *)&_this[1].m_pEquipAtt0;
  *(float *)&_this[1].m_pEquipAtt0 = v4;
  if ( v6 )
  {
    v7 = (1.0 - cos(v4 / *(float *)&_this[1].m_nRoleState1 * 3.1415927)) * 0.5;
    _this->m_vecTargetPos.x = *(float *)&_this[1].m_dwMatMsg[1] * (1.0 - v7)
                           + *((float *)&_this[1].m_pParticleData + 3) * v7;
    _this->m_vecTargetPos.y = *(float *)&_this[1].m_dwMatMsg[2] * (1.0 - v7)
                           + *((float *)&_this[1].m_pParticleData + 4) * v7;
    _this->m_vecTargetPos.z = *(float *)&_this[1].m_dwMatMsg[3] * (1.0 - v7)
                           + *((float *)&_this[1].m_pParticleData + 5) * v7;
  }
  else
  {
    _this->m_vecTargetPos.x = *((float *)&_this[1].m_pParticleData + 3);
    _this->m_vecTargetPos.y = *((float *)&_this[1].m_pParticleData + 4);
    _this->m_vecTargetPos.z = *((float *)&_this[1].m_pParticleData + 5);
    _this[1].m_pEquipAtt1[0] = 0;
    (((Actor *)p_m_InnerActor))->Actor::CompareActionName(0, 0);
  }
}

// 0x0041C090
int FlushCommandQueue(RoleSystem *_this)
{
  int result; // eax
  float v3; // edi
  int v4; // eax
  char *m_pPathNodeIter; // eax
  void **v6; // eax
  char *v7; // ecx
  Actor *m_actarray_capacity_end; // [esp-0xC] [ebp-0x10]

  for ( result = *(_DWORD *)_this->m_partyActor.m_name; result; result = *(_DWORD *)_this->m_partyActor.m_name )
  {
    LODWORD(v3) = LODWORD(_this->m_fCmdTimer) + 28;
    v4 = result - 1;
    _this->m_fCmdTimer = v3;
    *(_DWORD *)_this->m_partyActor.m_name = v4;
    if ( !v4 || LODWORD(v3) == LODWORD(_this->m_fCmdInterval) )
    {
      m_pPathNodeIter = _this->m_pPathNodeIter;
      _this->m_pPathNodeIter = m_pPathNodeIter + 4;
      operator delete(*(void **)m_pPathNodeIter);
      if ( *(_DWORD *)_this->m_partyActor.m_name )
      {
        v6 = (void **)_this->m_pPathNodeIter;
        v7 = (char *)*v6;
        _this->m_pCmdQueueEnd = *v6;
        LODWORD(_this->m_fCmdInterval) = (unsigned long)(v7 + 4088);
        LODWORD(_this->m_fCmdTimer) = (unsigned long)v7;
        _this->m_pPathNodeIter = (char *)v6;
      }
      else
      {
        _this->m_pCmdQueueEnd = 0;
        _this->m_fCmdInterval = 0.0;
        _this->m_fCmdTimer = 0.0;
        _this->m_pPathNodeIter = 0;
        _this->m_nCmdQueuePos = 0;
        m_actarray_capacity_end = _this->m_partyActor.m_actarray_capacity_end;
        *(_DWORD *)&_this->m_partyActor.m_actarray_type = 0;
        _this->m_partyActor.m_actarray_begin = 0;
        _this->m_partyActor.m_actarray_end = 0;
        operator delete(m_actarray_capacity_end);
      }
    }
  }
  return result;
}

// 0x0041C1E0
void ScriptPoolPage_Alloc(_Console *_this)
{
  _DWORD *v1; // eax
  int v2; // eax
  _DWORD *v3; // eax

  v1 = (_DWORD *)(*(_DWORD **)&_this->m_cmd[2]._tail_000[104]);
  if ( v1 )
  {
    *(_DWORD *)&_this->m_cmd[2]._tail_000[112] = (unsigned long)v1[40];
    *(_DWORD *)&_this->m_cmd[2]._tail_000[116] = (unsigned long)v1[41];
    v2 = (unsigned long)v1[42];
  }
  else
  {
    v3 = (_DWORD *)(*(_DWORD **)&_this->m_cmd[2]._tail_000[108]);
    if ( !v3 )
      goto LABEL_6;
    *(_DWORD *)&_this->m_cmd[2]._tail_000[112] = (unsigned long)v3[10];
    *(_DWORD *)&_this->m_cmd[2]._tail_000[116] = (unsigned long)v3[11];
    v2 = (unsigned long)v3[12];
  }
  *(_DWORD *)&_this->m_cmd[2]._tail_000[120] = v2;
LABEL_6:
  if ( g_ScriptSystemData.m_nGameMode == 1 )
    *(float *)&_this->m_cmd[2]._tail_000[116] = *(float *)&_this->m_cmd[3]._tail_000[128]
                                             + *(float *)&_this->m_cmd[2]._tail_000[116];
  *(_DWORD *)&_this->m_cmd[3]._tail_000[68] = *(_DWORD *)&_this->m_cmd[2]._tail_000[112];
  *(_DWORD *)&_this->m_cmd[3]._tail_000[72] = *(_DWORD *)&_this->m_cmd[2]._tail_000[116];
  *(_DWORD *)&_this->m_cmd[3]._tail_000[76] = *(_DWORD *)&_this->m_cmd[2]._tail_000[120];
  (((InputSystem *)_this))->InputSystem::ProcessKeyboard(1);
}

// 0x0041C280
int InputUpdate(float fVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  _DWORD *v4; // eax
  int v5; // eax
  _DWORD *v6; // eax
  float v7; // st7
  float v8; // st6
  float v9; // st7
  float v10; // st4
  float v11; // st5
  float v12; // st7
  float v13; // st7
  long double v14; // st7
  float v15; // st7
  float v16; // [esp+0x4] [ebp-0x34]
  gbVec3D v17; // [esp+0x8] [ebp-0x30] BYREF
  gbVec3D v18; // [esp+0x14] [ebp-0x24] BYREF
  float v19; // [esp+0x20] [ebp-0x18]
  float v20; // [esp+0x24] [ebp-0x14]
  float v21; // [esp+0x28] [ebp-0x10]
  float v22; // [esp+0x2C] [ebp-0xC]
  float y; // [esp+0x30] [ebp-0x8]
  float z; // [esp+0x34] [ebp-0x4]

  v2 = v1;
  result = *(_DWORD *)(v1 + 448);
  if ( !result )
    return result;
  v4 = (_DWORD *)*(_DWORD **)(v1 + 380);
  memset(&v17, 0, sizeof(v17));
  if ( v4 )
  {
    *(_DWORD *)(v1 + 388) = (unsigned long)v4[40];
    *(_DWORD *)(v1 + 392) = (unsigned long)v4[41];
    v5 = (unsigned long)v4[42];
LABEL_6:
    *(_DWORD *)(v1 + 396) = v5;
    goto LABEL_7;
  }
  v6 = (_DWORD *)*(_DWORD **)(v1 + 384);
  if ( v6 )
  {
    *(_DWORD *)(v1 + 388) = (unsigned long)v6[10];
    *(_DWORD *)(v1 + 392) = (unsigned long)v6[11];
    v5 = (unsigned long)v6[12];
    goto LABEL_6;
  }
LABEL_7:
  if ( g_ScriptSystemData.m_nGameMode == 1 )
    *(float *)(v1 + 392) = *(float *)(v1 + 540) + *(float *)(v1 + 392);
  v7 = *(float *)(v1 + 480) - *(float *)(v1 + 388);
  y = *(float *)(v1 + 484) - *(float *)(v1 + 392);
  v8 = *(float *)(v1 + 488) - *(float *)(v1 + 396);
  v17.y = y;
  z = v8;
  v17.x = v7;
  v17.z = z;
  v9 = (((gbVec3D *)&v17))->gbVec3D::Length();
  if ( v9 > 0.050000001f )
  {
    v17.y = v17.y / v9;
    v17.z = v17.z / v9;
    v10 = v17.x / v9;
    v22 = v10;
    z = v17.z;
    y = v17.y;
    v11 = (20.0f - v9) * 4.599999904632568f * fVal;
    v16 = v11;
    v17.x = v11 * v10;
    v17.y = v17.y * v16;
    v17.z = v17.z * v16;
    *(float *)(v2 + 480) = v17.x + *(float *)(v2 + 480);
    *(float *)(v2 + 484) = v17.y + *(float *)(v2 + 484);
    *(float *)(v2 + 488) = v17.z + *(float *)(v2 + 488);
    v19 = *(float *)(v2 + 480) - *(float *)(v2 + 388);
    v12 = *(float *)(v2 + 484) - *(float *)(v2 + 392);
    v18.x = v19;
    v20 = v12;
    v13 = *(float *)(v2 + 488) - *(float *)(v2 + 396);
    v18.y = v20;
    v21 = v13;
    v18.z = v21;
    (((gbVec3D *)&v18))->gbVec3D::Normalize();
    if ( z * v18.z + y * v18.y + v18.x * v22 <= 0.0 )
    {
      *(_DWORD *)(v2 + 480) = *(_DWORD *)(v2 + 388);
      *(_DWORD *)(v2 + 484) = *(_DWORD *)(v2 + 392);
      *(_DWORD *)(v2 + 488) = *(_DWORD *)(v2 + 396);
    }
  }
  v14 = fVal * *(float *)(v2 + 460) * 32.0;
  if ( fabs(*(float *)(v2 + 460)) > fabs(v14) )
  {
    *(float *)(v2 + 456) = v14 + *(float *)(v2 + 456);
    *(float *)(v2 + 460) = *(float *)(v2 + 460) - v14;
  }
  else
  {
    v15 = *(float *)(v2 + 460) + *(float *)(v2 + 456);
    *(_DWORD *)(v2 + 460) = 0;
    *(float *)(v2 + 456) = v15;
  }
  if ( g_ScriptSystemData.m_nGameMode == 1 )
    InputSystem::ProcessMouse(SLODWORD(fVal));
  InputSystem::ProcessKeyboard((InputSystem *)v2, 1);
  return result;
}

// 0x0041C710
void InputSystem::ProcessKeyboard(InputSystem *_this, int a1)
{
  long double v2; // st7
  long double v3; // st6
  long double v4; // st5
  float v5; // st5
  float v6; // st4
  float v7; // st3
  float v8; // st4
  float v9; // st5
  float v10; // st4
  float v11; // st7
  float v12; // st6
  float v13; // st5
  float v14; // [esp+0x0] [ebp-0x1C]
  float v15; // [esp+0x4] [ebp-0x18]
  float v16; // [esp+0x8] [ebp-0x14]
  float v17; // [esp+0xC] [ebp-0x10]
  float v18; // [esp+0x10] [ebp-0xC]
  float v19; // [esp+0x14] [ebp-0x8]
  float v20; // [esp+0x14] [ebp-0x8]
  float v21; // [esp+0x14] [ebp-0x8]
  float v22; // [esp+0x14] [ebp-0x8]
  float v23; // [esp+0x18] [ebp-0x4]
  float v24; // [esp+0x18] [ebp-0x4]
  float v25; // [esp+0x18] [ebp-0x4]

  v2 = cos(*(float *)&_this[12]._tail_000[24]);
  v3 = cos(*(float *)&_this[12]._tail_000[20]);
  v16 = cos(*(float *)&_this[12]._tail_000[32]);
  v14 = sin(*(float *)&_this[12]._tail_000[24]);
  v15 = sin(*(float *)&_this[12]._tail_000[20]);
  v4 = sin(*(float *)&_this[12]._tail_000[32]);
  *(float *)&_this[14]._tail_000[4] = v15;
  v17 = v4;
  *(float *)_this[14]._tail_000 = v14 * v3;
  *(float *)&_this[14]._tail_000[8] = -(v3 * v2);
  v5 = *(float *)_this[13]._tail_000;
  v18 = v5 * *(float *)_this[14]._tail_000;
  v19 = v5 * *(float *)&_this[14]._tail_000[4];
  if ( a1 )
  {
    v6 = *(float *)&_this[13]._tail_000[12] - v18;
    v20 = *(float *)&_this[13]._tail_000[16] - v19;
    v7 = *(float *)&_this[13]._tail_000[20] - v5 * *(float *)&_this[14]._tail_000[8];
    *(float *)&_this[13]._tail_000[28] = v20;
    v23 = v7;
    *(float *)&_this[13]._tail_000[24] = v6;
    *(float *)&_this[13]._tail_000[32] = v23;
  }
  else
  {
    v21 = v19 + *(float *)&_this[13]._tail_000[28];
    v8 = v5 * *(float *)&_this[14]._tail_000[8];
    v9 = v18 + *(float *)&_this[13]._tail_000[24];
    v10 = v8 + *(float *)&_this[13]._tail_000[32];
    *(float *)&_this[13]._tail_000[16] = v21;
    v24 = v10;
    *(float *)&_this[13]._tail_000[12] = v9;
    *(float *)&_this[13]._tail_000[20] = v24;
  }
  *(float *)&_this[14]._tail_000[12] = -(v17 * v2) - v15 * v14 * v16;
  *(float *)&_this[14]._tail_000[16] = v16 * v3;
  *(float *)&_this[14]._tail_000[20] = -(v17 * v14) - -(v15 * v16 * v2);
  v11 = *(float *)&_this[14]._tail_000[20] * *(float *)&_this[14]._tail_000[4]
      - *(float *)&_this[14]._tail_000[8] * *(float *)&_this[14]._tail_000[16];
  v22 = *(float *)&_this[14]._tail_000[8] * *(float *)&_this[14]._tail_000[12]
      - *(float *)&_this[14]._tail_000[20] * *(float *)_this[14]._tail_000;
  v12 = *(float *)_this[14]._tail_000 * *(float *)&_this[14]._tail_000[16];
  v13 = *(float *)&_this[14]._tail_000[12] * *(float *)&_this[14]._tail_000[4];
  *(float *)&_this[14]._tail_000[28] = v22;
  v25 = v12 - v13;
  *(float *)&_this[14]._tail_000[24] = v11;
  *(float *)&_this[14]._tail_000[32] = v25;
}

// 0x0041D410
int RoleCamera_PushState(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // ebx
  int v3; // eax
  void **v4; // eax
  void **v5; // eax
  int v6; // eax
  const void *v7; // edx
  int v8; // ecx
  int v9; // edi
  int v10; // edx
  const void *v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  float v15; // st7
  float v16; // ecx
  float v17; // edx
  float v18; // eax
  float v19; // ecx
  float v20; // edx
  float v21; // eax
  int result; // eax
  void *v23; // [esp-0x8] [ebp-0x40]
  int v24; // [esp+0xC] [ebp-0x2C] BYREF
  int v25; // [esp+0x10] [ebp-0x28]
  const void *v26; // [esp+0x14] [ebp-0x24]
  int v27; // [esp+0x18] [ebp-0x20]
  float v28[7]; // [esp+0x1C] [ebp-0x1C] BYREF

  v2 = (_DWORD *)v1;
  v24 = (unsigned long)v1[105];
  v25 = (unsigned long)v1[106];
  v26 = (const void *)v1[107];
  v27 = (unsigned long)v1[108];
  (((CameraCtrl *)&v24))->CameraCtrl::SetupCameraArray(-1);
  v3 = (unsigned long)v2[107];
  qmemcpy(v28, v26, sizeof(v28));
  if ( v3 == v2[105] )
  {
    v4 = (void **)v2[108];
    v2[108] = (unsigned long)(v4 - 1);
    operator delete(*v4);
    if ( v2[111] )
    {
      (((CameraCtrl *)&v24))->CameraCtrl::SetCameraSource(*(_DWORD *)v2[108] + 4088, (int *)v2[108]);
      v10 = v25;
      v11 = v26;
      v2[105] = v24;
      v12 = v27;
      v2[106] = v10;
      v2[107] = (_DWORD)v11;
      v2[108] = v12;
    }
    else
    {
      v5 = (void **)v2[104];
      if ( v5 == (void **)v2[108] )
        operator delete(*v5);
      (((PalScriptMgr *)&v24))->PalScriptMgr::Get_result();
      v6 = v24;
      v7 = v26;
      v8 = v25;
      v9 = v27;
      v2[101] = v24;
      v2[105] = v6;
      v2[106] = v8;
      v2[107] = (_DWORD)v7;
      v2[102] = v8;
      v2[108] = v9;
      v2[103] = (_DWORD)v7;
      v23 = (void *)v2[109];
      v2[104] = v9;
      operator delete(v23);
    }
  }
  v13 = (unsigned long)v2[111];
  if ( v13 )
    v2[107] -= 28;
  v14 = v13 - 1;
  v2[111] = v14;
  if ( !v14 )
    (((CameraCtrl *)(v2 + 100)))->CameraCtrl::PopState();
  v15 = v28[0];
  v16 = v28[3];
  v17 = v28[1];
  v18 = v28[2];
  v2[2] = 0;
  *((float *)v2 + 1) = v15;
  *((float *)v2 + 117) = v16;
  v19 = v28[6];
  *((float *)v2 + 114) = v17;
  v20 = v28[4];
  *((float *)v2 + 113) = v18;
  v21 = v28[5];
  *((float *)v2 + 122) = v19;
  *((float *)v2 + 120) = v20;
  *((float *)v2 + 121) = v21;
  InputSystem::ProcessKeyboard((InputSystem *)v2, 1);
  return result;
}

// 0x00420110
int SystemUI_RenderWithStack(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // esi
  int result; // eax
  RoleSystem *v5; // edi

  v2 = v1;
  v3 = 0;
  result = *(_DWORD *)(v1 + 57568);
  if ( result > 0 )
  {
    v5 = (RoleSystem *)(v1 + 57572);
    do
    {
      (((RoleSystem *)v5))->RoleSystem::RenderRole((gbMatrixStack *)nVal, 0);
      result = *(_DWORD *)(v2 + 57568);
      ++v3;
      v5 = (RoleSystem *)((char *)v5 + 8704);
    }
    while ( v3 < result );
  }
  return result;
}

// 0x00421C00
int SceneMgr_RenderActiveRoles(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  int v3; // edi
  int result; // eax
  int v5; // esi

  v2 = v1;
  v3 = 0;
  result = *(_DWORD *)(v1 + 57568);
  if ( result > 0 )
  {
    v5 = v1 + 57572;
    do
    {
      if ( *(_BYTE *)(v5 + 173) == 4 )
        (((UIScene *)v5))->UIScene::RenderVertexPool();
      result = *(_DWORD *)(v2 + 57568);
      ++v3;
      v5 += 8704;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x00422050
int SceneMgr_FindRoleByState(int nVal)
{
  int v1; // ecx
  int v2; // eax
  int v3; // esi
  _BYTE *i; // edx

  v2 = 0;
  v3 = *(_DWORD *)(v1 + 57568);
  if ( v3 <= 0 )
    return 0;
  for ( i = (_BYTE *)(v1 + 57744); *i != (_BYTE)nVal; i += 8704 )
  {
    if ( ++v2 >= v3 )
      return 0;
  }
  return 8704 * v2 + v1 + 57572;
}

// 0x004226F0
Scene * UISceneUpdate()
{
  return (Scene *)(493156 * (g_ScriptSystemData.m_nGameMode == 1) + 12722152);
}

// 0x00422950
void LoadScene(char *String2, char *desc, char arg8)
{
  PAL3 *v3; // ecx
  const char *v4; // ebx
  int v5; // ebp
  int v6; // esi
  int v7; // edi
  RoleSystem *RoleDataOffset; // eax
  RoleSystem *v9; // eax
  Actor *SaveDataManager; // eax
  int v11; // eax
  CameraCtrl *v12; // ecx
  int v13; // ebx
  PalScript *v14; // eax
  UICursor *v15; // ecx
  void ( ***v16)(_DWORD, int); // ecx
  CScreenMode *Instance; // eax
  int v18; // ebp
  gbSceneGraph *pSceneGraph; // esi
  gbSceneGraph *v20; // ecx
  double v21; // [esp-0x4] [ebp-0x340]
  BOOL v22; // [esp-0x4] [ebp-0x340]
  gbVisNode *v23; // [esp-0x4] [ebp-0x340]
  int *v24; // [esp+0x4] [ebp-0x338]
  CUtil *pUtil; // [esp+0x10] [ebp-0x32C]
  OpenSceneFile v26; // [esp+0x14] [ebp-0x328] BYREF
  int v27; // [esp+0x18] [ebp-0x324]
  int v28; // [esp+0x1C] [ebp-0x320]
  int v29; // [esp+0x20] [ebp-0x31C]
  int v30; // [esp+0x24] [ebp-0x318]
  int v31; // [esp+0x28] [ebp-0x314]
  char String1[260]; // [esp+0x2C] [ebp-0x310] BYREF
  char Buffer[512]; // [esp+0x130] [ebp-0x20C] BYREF
  int v34; // [esp+0x338] [ebp-0x4]

  v30 = g_nSceneState;
  if ( arg8 )
  {
    pUtil = (CUtil *)g_CCBEditorInst.m_dwTrickID[361];
    (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)0xE);
    (((PAL3 *)v3))->PAL3::Render();
  }
  PAL3::ResetForNewScene();
  v4 = (const char *)String2;
  (((VFileSystem *)&g_RoleSystemInstance))->VFileSystem::_auto_4221d0(String2, desc);
  CameraCtrl::AttachToRole(0);
  v31 = g_ScriptSystemData.m_nGameMode;
  g_ScriptSystemData.m_nGameMode = LODWORD(g_RoleSystemInstance.m_fDirZ);
  v5 = 493156 * (LODWORD(g_RoleSystemInstance.m_fDirZ) == 1) + 12722152;
  v22 = !_strcmpi((const char *)v5, String2) && !_strcmpi((const char *)(v5 + 32), desc);
  sub_41FA90((char *)v5, (int)&g_RoleSystemInstance, v22);
  sub_421830((_DWORD *)v5);
  SceneMgr::InitSceneRoles();
  v6 = 0;
  if ( *(int *)(v5 + 492772) > 0 )
  {
    v7 = v5 + 492776;
    do
    {
      RoleDataOffset = (RoleSystem *)GetRoleDataOffset(v6);
      if ( !(((RoleSystem *)RoleDataOffset))->RoleSystem::BuildModelPath((const char *)v5) )
      {
        v9 = (RoleSystem *)GetRoleDataOffset(v6);
        (((RoleSystem *)v9))->RoleSystem::LoadRoleImage(v7, (const char *)v5);
        if ( UIScene::ProcessInput(pszBuf, pszBuf)
          || UIScene::ProcessInput(pszBuf, "q08f")
          || UIScene::ProcessInput(pszBuf, "q08p") )
        {
          *(_DWORD *)(GetRoleDataOffset(v6) + 16) = (v6 + 1) % 2;
          v4 = (const char *)String2;
        }
        else
        {
          *(_DWORD *)(GetRoleDataOffset(v6) + 16) = v6;
        }
        if ( !g_ScriptSystemData.m_nGameMode
          || (SaveDataManager = (Actor *)GetSaveDataManager(),
              (((Actor *)SaveDataManager))->Actor::SearchAnimByIndex((char *)v5, (char *)(v5 + 32))) )
        {
          v11 = GetRoleDataOffset(v6);
          sub_4206F0(v11);
        }
      }
      ++v6;
      v7 += 164;
    }
    while ( v6 < *(_DWORD *)(v5 + 492772) );
  }
  sprintf(Buffer, "%s.sce", v4);
  strcpy((char *)String1, "scene\\");
  strcat((char *)String1, v4);
  v34 = 0;
  PalScriptMgr::Update(Buffer);
  PalScriptMgr::FindScriptByDesc(v4, desc);
  CameraCtrl::AttachToRole(1);
  if ( g_ScriptSystemData.m_nGameMode == 1 )
  {
    g_nRoleSystem_58B234 = 0;
    RoleSystem::SetCameraMode(SLODWORD(g_RoleSystemInstance.m_fDirZ));
  }
  else
  {
    g_nRoleSystem_58B234 = 1;
    RoleSystem::SetCameraMode(SLODWORD(g_RoleSystemInstance.m_fDirZ));
    v12 = g_pCameraCtrl;
    if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
      (((_Console *)g_pCameraCtrl))->_Console::SetActive((int)g_pRoleSystem);
  }
  v13 = v31;
  if ( v31 == 2 && g_ScriptSystemData.m_nGameMode != 2 )
    (((scAsmDecoder *)v12))->scAsmDecoder::Execute(0, 1);
  (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetAsCurrent(3);
  (((RoleCameraCtrl *)&stru_DBA134))->RoleCameraCtrl::ShowWindow(0);
  LODWORD(v21) = v5;
  v14 = (PalScript *)GetSaveDataManager();
  (((PalScript *)v14))->PalScript::DestroyInstances(v21, v24);
  (((GRPinput *)&g_Input))->GRPinput::Reset();
  (((UICursor *)v15))->UICursor::_todo_541CC0();
  if ( arg8 )
  {
    if ( pUtil == (CUtil *)4 )
      pUtil = 0;
    (((CGameData *)&g_gamefrm))->CGameData::Load(pUtil);
  }
  v16 = (void ( ***)(_DWORD, int))((((CGameData *)&g_gamefrm))->CGameData::SetMode(0) + 72);
  if ( g_ScriptSystemData.m_nGameMode == 1 )
    (**v16)((_DWORD)((_DWORD)(v16)), (int)(0));
  else
    (**v16)((_DWORD)((_DWORD)(v16)), (int)(1));
  if ( !CScreenMode::GetInstance()->m_bRenderAlt )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::PlaySceneMusic((char *)v5, (const char *)(v5 + 32), 0);
  }
  v18 = *(_DWORD *)(v5 + 104);
  if ( v18 )
  {
    v27 = 1120403456;
    v28 = 1120403456;
    v29 = 1120403456;
    sub_53DAD0();
    sub_53D460(v18, 1120403456, 1120403456, 1120403456);
    pSceneGraph = gfxMgr->pSceneGraph;
    v23 = (gbVisNode *)sub_53DAD0();
    v20 = (gbSceneGraph *)pSceneGraph;
  }
  else
  {
    v23 = 0;
    v20 = gfxMgr->pSceneGraph;
  }
  (((gbSceneGraph *)v20))->gbSceneGraph::AddSkyBox(v23);
  g_nSceneState = v30;
  CombatEnter();
  g_bRoleSystem_5CEFA9 = g_ScriptSystemData.m_nGameMode != 2;
  if ( UIScene::ProcessInput("m02", 0) )
    g_bRoleSystem_5CEFA9 = 0;
  (((CameraCtrl *)&g_pCameraCtrl))->CameraCtrl::SetCamMode(0);
  if ( v13 != 2 && g_ScriptSystemData.m_nGameMode == 2 )
    byte_C11752 = 1;
  v34 = -1;
  (((OpenSceneFile *)&v26))->OpenSceneFile::~OpenSceneFile();
}

// 0x00422E40
void EffectUpdate(float fVal)
{
  float *v1; // edi
  int v2; // eax
  int v3; // eax
  BOOL v4; // ecx
  int v5; // ebx
  CScreenMode *SoundList; // eax
  int v7; // eax
  int v8; // edi
  _DWORD *v9; // ebp
  int v10; // eax
  _DWORD *v11; // esi
  int v12; // ebx
  RoleSystem *v13; // ebx
  int *v14; // esi
  int v15; // edi
  int v16; // edi
  _DWORD *v17; // esi
  int i; // esi
  float *v19; // [esp-0x8] [ebp-0x18]
  int v20; // [esp+0x8] [ebp-0x8]
  int v21; // [esp+0xC] [ebp-0x4]

  g_fEffectTimer = g_fEffectTimer + fVal;
  if ( g_nunknown_libname_331_C12B3C )
  {
    PalScriptMgr::ClearAllScript();
    if ( !v2 )
    {
      if ( (_BYTE)g_nunknown_libname_331_C12B38 == 6 || (_BYTE)g_nunknown_libname_331_C12B38 == 14 )
      {
        (((RoleSystem *)&g_pRoleSystem))->RoleSystem::GetMoveState(0);
        v3 = g_nunknown_libname_331_C12B40;
        if ( *(_DWORD *)(g_nunknown_libname_331_C12B40 + 88) == 3 )
        {
          (((gbVisNode *)*(gbVisNode **)(g_nunknown_libname_331_C12B40 + 92)))->gbVisNode::SetTimeScale(0.0);
          (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(g_nunknown_libname_331_C12B40 + 92) + 24))(
            *(_DWORD *)(g_nunknown_libname_331_C12B40 + 92),
            0);
          v3 = g_nunknown_libname_331_C12B40;
        }
        *(_BYTE *)(v3 + 80) = 0;
      }
      g_nunknown_libname_331_C12B38 = 0;
      g_nunknown_libname_331_C12B3C = 0;
      g_nunknown_libname_331_C12B40 = 0;
    }
  }
  v4 = g_ScriptSystemData.m_nGameMode == 1;
  v5 = 493156 * v4 + 12722152;
  v21 = v5;
  if ( g_nCameraUpdateCount > 0 )
  {
    SoundList = (CScreenMode *)(((CScreenMode *)v4))->CScreenMode::GetSoundList();
    if ( (((CScreenMode *)SoundList))->CScreenMode::IsAudioReady() )
    {
      v7 = *(_DWORD *)(v5 + 57568);
      v19 = (float *)v1;
      v8 = 0;
      if ( v7 > 0 )
      {
        v9 = (_DWORD *)(v5 + 58204);
        do
        {
          if ( *(v9 - 122) )
          {
            if ( *v9 )
            {
              v10 = v7 - 1;
              if ( v10 > v8 )
              {
                v11 = (_DWORD *)(8704 * v10 + v5 + 57716);
                v12 = v10 - v8;
                do
                {
                  if ( v11[122] && *v11 )
                    (((RoleSystem *)(v9 - 158)))->RoleSystem::CheckMoveCollisionDist((int)(v11 - 36), v19);
                  v11 -= 2176;
                  --v12;
                }
                while ( v12 );
                v5 = v21;
              }
            }
          }
          v7 = *(_DWORD *)(v5 + 57568);
          ++v8;
          v9 += 2176;
        }
        while ( v8 < v7 );
      }
      if ( g_ScriptSystemData.m_nGameMode != 2 )
      {
        v20 = 0;
        v13 = (RoleSystem *)(&g_RoleSlotBuf.dword_17AA450 + 150);
        do
        {
          if ( v13->m_partyActor.m_pRoleObj && v13->m_nMoveMode != 4 )
          {
            if ( (int)v13 < (int)&unk_C0E760 )
            {
              v14 = (int *)&unk_C0EC50;
              v15 = 4 - v20;
              do
              {
                if ( *(v14 - 158) && *v14 != 4 )
                  (((RoleSystem *)v13))->RoleSystem::CheckMoveCollisionDist((int)(v14 - 316), v19);
                v14 -= 2176;
                --v15;
              }
              while ( v15 );
            }
            v16 = 0;
            if ( *(int *)(v21 + 57568) > 0 )
            {
              v17 = (_DWORD *)(v21 + 57716);
              do
              {
                if ( v17[122] && *v17 )
                  (((RoleSystem *)v13))->RoleSystem::CheckMoveCollisionDist((int)(v17 - 36), v19);
                ++v16;
                v17 += 2176;
              }
              while ( v16 < *(_DWORD *)(v21 + 57568) );
            }
          }
          v13 = (RoleSystem *)((char *)v13 + 8704);
          ++v20;
        }
        while ( (int)v13 < (int)&g_RoleSystemArrayEnd );
        v5 = v21;
      }
      if ( g_pRoleSystem && g_pRoleSystem->m_nMoveMode != 4 )
        (((PalScriptMgr *)v5))->PalScriptMgr::CheckTileScript(g_pRoleSystem, fVal, 0);
    }
  }
  if ( g_ScriptSystemData.m_nGameMode != 1 )
  {
    for ( i = 0; i < *(_DWORD *)(v5 + 492772); ++i )
    {
      GetRoleDataOffset(i);
      sub_420730(1);
    }
  }
}

// 0x00423540
gbGfxManager * CombatEnter()
{
  gbGfxManager *result; // eax

  result = (gbGfxManager *)UISceneUpdate();
  if ( *(_DWORD *)&result->DrvInfo.winname[48] != 1
    || (result = (gbGfxManager *)UIScene::ProcessInput("m19", 0), (_BYTE)result)
    || (result = (gbGfxManager *)UIScene::ProcessInput("m20", 0), (_BYTE)result)
    || (result = (gbGfxManager *)UIScene::ProcessInput("m25", 0), (_BYTE)result) )
  {
    gfxMgr->fSelfIllum = 0.69999999;
  }
  else
  {
    result = gfxMgr;
    gfxMgr->fSelfIllum = 0.0;
  }
  return result;
}

// 0x00423600
int GetRoleDataOffset(int nRoleIndex)
{
  if ( g_ScriptSystemData.m_nGameMode == 2 )
    return 392 * nRoleIndex + 14202408;
  else
    return 392 * nRoleIndex + 14201624;
}

// 0x00426E80
BOOL PointInRect(int *pRect, int *pPoint)
{
  int v2; // ecx
  BOOL result; // eax

  result = 0;
  if ( *pPoint >= *pRect && *pPoint <= pRect[2] )
  {
    v2 = (unsigned long)pPoint[1];
    if ( v2 >= pRect[1] && v2 <= pRect[3] )
      return 1;
  }
  return result;
}

// 0x00429CA0
gbActorMgr * GetActorMgr()
{
  int v0; // ecx
  _DWORD *v1; // esi
  gbActorMgr *result; // eax
  int ( ***v3)(_DWORD, int); // ecx
  int ( ***v4)(_DWORD, int); // ecx

  v1 = (_DWORD *)v0;
  result = (gbActorMgr *)(*(_DWORD *)v0 - 1);
  switch ( *(_DWORD *)v0 )
  {
    case 1:
      result = (gbActorMgr *)*(gbActorMgr **)(v0 + 4);
      if ( result )
      {
        (((gbActorMgr *)g_pActorMgr))->gbActorMgr::DestroyActor(*(gbActor **)(v0 + 4));
        v1[1] = 0;
      }
      goto LABEL_4;
    case 2:
    case 3:
LABEL_4:
      v3 = (int ( ***)(_DWORD, int))v1[1];
      if ( v3 )
      {
        result = (gbActorMgr *)(**v3)((_DWORD)((_DWORD)(v3)), (int)(1));
        v1[1] = 0;
      }
      goto LABEL_6;
    case 4:
LABEL_6:
      v4 = (int ( ***)(_DWORD, int))v1[1];
      if ( v4 )
      {
        result = (gbActorMgr *)(**v4)((_DWORD)((_DWORD)(v4)), (int)(1));
        v1[1] = 0;
      }
      break;
    default:
      break;
  }
  *v1 = 0;
  return result;
}

// 0x00430180
_BYTE * InitSceneScriptLoader(_BYTE *_this)
{
  PalScript *v2; // eax
  PalScript *v3; // edi
  _DWORD *v4; // eax
  char v6; // [esp+0xF] [ebp-0xD]

  *_this = v6;
  _this[1] = v6;
  _this[8] = 0;
  if ( !g_ScriptSystemData.m_pCurrentBlock )
  {
    v2 = (PalScript *)operator new(0x30u);
    v2->m_pinst = 0;
    v2->m_nTodo_02C = 1;
    g_ScriptSystemData.m_pCurrentBlock = ((char *)(v2));
    (*(void **)(v2)) = (void *)(0);
    g_ScriptSystemData.m_pCurrentBlock->m_waitobj = 0;
  }
  ++*(_DWORD *)&g_ScriptSystemData.m_String[256];
  v3 = (PalScript *)g_ScriptSystemData.m_pCurrentBlock;
  v4 = (_DWORD *)operator new(0x30u);
  v4[1] = (_DWORD)v3;
  v4[11] = 0;
  *((_DWORD *)_this + 1) = (unsigned long)v4;
  *((_DWORD *)_this + 3) = 0;
  *v4 = (_DWORD)v4;
  *(_DWORD *)(*((_DWORD *)_this + 1) + 8) = *((_DWORD *)_this + 1);
  return _this;
}

// 0x00431E90
void ConditionalCleanup()
{
  if ( (g_ScriptSystemData.m_bScriptFlag & 4) == 0 )
  {
    g_ScriptSystemData.m_bScriptFlag |= 4u;
    (((PtrArray *)&unk_D8C2E8))->PtrArray::Remove();
  }
}

// 0x00431EE0
void FindScript()
{
  if ( (g_ScriptSystemData.m_bScriptFlag & 8) == 0 )
  {
    g_ScriptSystemData.m_bScriptFlag |= 8u;
    (((PtrArray *)&unk_D8C2C8))->PtrArray::Remove();
  }
}

// 0x00431F40
void ClearAllCamObj()
{
  char v0; // al

  if ( (g_ScriptSystemData.m_bScriptFlag & 0x10) == 0 )
  {
    g_ScriptSystemData.m_bScriptFlag |= 0x10u;
    if ( g_ScriptSystemData.m_nScriptState )
    {
      v0 = *(_BYTE *)(g_ScriptSystemData.m_nScriptState - 1);
      if ( !v0 || v0 == -1 )
        operator delete((void *)(g_ScriptSystemData.m_nScriptState - 1));
      else
        *(_BYTE *)(g_ScriptSystemData.m_nScriptState - 1) = v0 - 1;
    }
    g_ScriptSystemData.m_nScriptState = 0;
    g_ScriptSystemData.m_nCmdFA8 = 0;
    g_ScriptSystemData.m_pScriptData = ((char *)0);
  }
}

// 0x004323C0
void StopSceneScripts(const char *pszScene)
{
  int v1; // ebp
  int v2; // ebx
  int v3; // esi
  UIListBox *v4; // edi
  int v5; // eax
  int i; // esi

  v1 = g_ScriptSystemData.m_CmdObjArray0.capacity;
  v2 = 0;
  v3 = 0;
  if ( g_ScriptSystemData.m_CmdObjArray0.capacity > 0 )
  {
    do
    {
      if ( v3 < 0 || v3 >= g_ScriptSystemData.m_CmdObjArray0.capacity )
        v4 = 0;
      else
        v4 = (UIListBox *)(*(UIListBox **)&dword_D8C328.m_pData[4 * v3]);
      if ( (((PalScriptMgr *)v4))->PalScriptMgr::IsScriptRuning((int)pszScene) )
      {
        if ( v4 )
        {
          (((UIListBox *)v4))->UIListBox::RefreshSelection();
          operator delete(v4);
        }
        if ( v3 >= 0 && v3 < g_ScriptSystemData.m_CmdObjArray0.capacity )
          *(_DWORD *)&dword_D8C328.m_pData[4 * v3] = 0;
        v2 = 1;
      }
      ++v3;
    }
    while ( v3 < v1 );
    if ( v2 )
    {
      v5 = g_ScriptSystemData.m_CmdObjArray0.capacity;
      for ( i = 0; i < g_ScriptSystemData.m_CmdObjArray0.capacity; v5 = g_ScriptSystemData.m_CmdObjArray0.capacity )
      {
        if ( i >= 0 && i < v5 && *(_DWORD *)&dword_D8C328.m_pData[4 * i] )
          ++i;
        else
          (((PtrArray *)&dword_D8C328))->PtrArray::RemoveAt(i, 1);
      }
    }
  }
}

// 0x00432600
char FindScriptEventByID(int nEventId)
{
  int v1; // eax
  _DWORD *i; // ecx

  v1 = 0;
  if ( !(_WORD)g_ScriptSystemData.m_nTodo_1004 )
    return 0;
  for ( i = (_DWORD *)g_ScriptSystemData.m_nTodo_1008; *i != nEventId; i += 18 )
  {
    if ( ++v1 >= (unsigned __int16)g_ScriptSystemData.m_nTodo_1004 )
      return 0;
  }
  return 1;
}

// 0x00432870
unsigned __int8 * GetOpcodeParamTypes()
{
  return (unsigned __int8 *)&unk_D8C358;
}

// 0x00432890
void InitOpcodeEntry()
{
  (((PtrArray *)&unk_D8C358))->PtrArray::ResizeOpcodeParams();
}

// 0x004328D0
void InitScriptEventArray()
{
  if ( (g_ScriptSystemData.m_nTodo_1028 & 1) == 0 )
  {
    g_ScriptSystemData.m_nTodo_1028 |= 1u;
    (((UIListBox *)&dword_D8C348))->UIListBox::ReleaseVtable();
  }
}

// 0x00432930
void SetScriptInitFlag()
{
  if ( (g_ScriptSystemData.m_nTodo_1028 & 2) == 0 )
    g_ScriptSystemData.m_nTodo_1028 |= 2u;
}

// 0x00432990
int LoadScriptFile(const char *pszFileName)
{
  InitSceOpcodeTable();
  g_pLoadBuffer = 0;
  return sub_4339F0((char *)pszFileName);
}

// 0x004329B0
int InitSceOpcodeTable()
{
  int result; // eax

  memset(&g_ScriptSystemData.m_CmdTable, 0, 0x2000u);
  result = 1;
  dword_D8C478 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Idle) */;
  byte_D8C47C = 2;
  word_D8C484 = 1;
  dword_D8C488 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_ScriptRunMode) */;
  byte_D8C48C = 1;
  word_D8C494 = 1;
  dword_D8C498 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GoTo) */;
  byte_D8C49C = 4;
  word_D8C4A4 = 1;
  dword_D8C4A8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FCZero) */;
  word_D8C4B4 = 0;
  dword_D8C588 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Rand) */;
  word_D8C594 = 0;
  dword_D8C4B8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FNOT) */;
  byte_D8C4BC = 1;
  word_D8C4C4 = 1;
  dword_D8C4C8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FOP) */;
  byte_D8C4CC = 1;
  byte_D8C4CD = 1;
  word_D8C4D4 = 2;
  dword_D8C4D8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GT) */;
  byte_D8C4DC = 1;
  byte_D8C4DD = 1;
  word_D8C4E4 = 2;
  dword_D8C4E8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_LS) */;
  byte_D8C4EC = 1;
  byte_D8C4ED = 1;
  word_D8C4F4 = 2;
  dword_D8C4F8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_EQ) */;
  byte_D8C4FC = 1;
  byte_D8C4FD = 1;
  word_D8C504 = 2;
  dword_D8C508 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_NEQ) */;
  byte_D8C50C = 1;
  byte_D8C50D = 1;
  word_D8C514 = 2;
  dword_D8C518 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GEQ) */;
  byte_D8C51C = 1;
  byte_D8C51D = 1;
  word_D8C524 = 2;
  dword_D8C528 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_LEQ) */;
  byte_D8C52C = 4;
  word_D8C534 = 1;
  dword_D8C538 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_TestGoto) */;
  byte_D8C53C = 1;
  byte_D8C53D = 1;
  word_D8C544 = 2;
  dword_D8C548 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Let) */;
  byte_D8C54C = 1;
  byte_D8C54D = 1;
  word_D8C554 = 2;
  dword_D8C558 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_AddEx) */;
  byte_D8C55C = 1;
  byte_D8C55D = 1;
  word_D8C564 = 2;
  dword_D8C568 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Sub) */;
  byte_D8C56C = 1;
  word_D8C574 = 1;
  dword_D8C578 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Call) */;
  byte_D8C57C = 1;
  byte_D8C57D = 1;
  word_D8C584 = 2;
  dword_D8C598 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Between) */;
  byte_D8C59C = 1;
  byte_D8C59D = 1;
  byte_D8C59E = 1;
  word_D8C5A4 = 3;
  dword_D8C5A8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RolePathTo) */;
  byte_D8C5AC = 1;
  byte_D8C5AD = 1;
  byte_D8C5AE = 1;
  byte_D8C5AF = 1;
  word_D8C5B4 = 4;
  dword_D8D0F8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RolePathOutToTile) */;
  byte_D8D0FC = 1;
  byte_D8D0FD = 1;
  byte_D8D0FE = 1;
  byte_D8D0FF = 1;
  word_D8D104 = 4;
  dword_D8C5B8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RolePathOut) */;
  byte_D8C5BC = 1;
  byte_D8C5BD = 1;
  byte_D8C5BE = 1;
  word_D8C5C4 = 3;
  dword_D8C5C8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleSetPos) */;
  byte_D8C5CC = 1;
  byte_D8C5CD = 3;
  byte_D8C5CE = 1;
  word_D8C5D4 = 3;
  g_ScriptSystemData.m_nTodo_D8D238 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::CmdGetSceneObject) */;
  g_ScriptSystemData.m_nTodo_D8D23C = 1;
  word_D8D244 = 1;
  dword_D8C5D8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleShowAction) */;
  byte_D8C5DC = 1;
  byte_D8C5DD = 1;
  word_D8C5E4 = 2;
  dword_D8C5E8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleEndAction) */;
  byte_D8C5EC = 1;
  byte_D8C5ED = 1;
  word_D8C5F4 = 2;
  dword_D8C5F8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleSetFace) */;
  word_D8C604 = 0;
  dword_D8C608 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleTurnFace) */;
  word_D8C614 = 0;
  dword_D8C618 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_TeamOpen) */;
  byte_D8C61C = 1;
  word_D8C624 = 1;
  dword_D8C628 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_TeamClose) */;
  byte_D8C62C = 1;
  byte_D8C62D = 1;
  word_D8C634 = 2;
  dword_D8C638 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleInput) */;
  byte_D8C63C = 1;
  byte_D8C63D = 1;
  word_D8C644 = 2;
  dword_D8D108 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleActive) */;
  byte_D8D10C = 1;
  byte_D8D10D = 1;
  word_D8D114 = 2;
  dword_D8D118 = 0 /* TODO: pmf_to_u32((char * (PalScript::*)())PalScript::Op_RoleScript) */;
  byte_D8D11C = 1;
  byte_D8D11D = 1;
  word_D8D124 = 2;
  dword_D8D128 = 0 /* TODO: pmf_to_u32((char * (PalScript::*)())PalScript::Op_InTeamExecScript) */;
  byte_D8D12C = 1;
  word_D8D134 = 1;
  dword_D8D138 = 0 /* TODO: pmf_to_u32((char * (PalScript::*)())PalScript::Op_RoleSetLayerByObj) */;
  byte_D8D13C = 1;
  byte_D8D13D = 1;
  word_D8D144 = 2;
  dword_D8D148 = 0 /* TODO: pmf_to_u32((char * (PalScript::*)())PalScript::Op_RoleCtrl) */;
  byte_D8D14C = 1;
  byte_D8D14D = 2;
  word_D8D154 = 2;
  dword_D8D158 = 0 /* TODO: pmf_to_u32((char * (PalScript::*)())PalScript::Op_RoleOverlap) */;
  byte_D8D15C = 1;
  byte_D8D15D = 1;
  word_D8D164 = 2;
  dword_D8D168 = 0 /* TODO: pmf_to_u32((float * (PalScript::*)())PalScript::Op_RoleScaleEx) */;
  byte_D8D16C = 1;
  byte_D8D16D = 2;
  word_D8D174 = 2;
  dword_D8D178 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_ShowActAutoStandEx) */;
  byte_D8D17C = 1;
  byte_D8D17D = 1;
  word_D8D184 = 2;
  dword_D8D188 = 0 /* TODO: pmf_to_u32((unsigned int (PalScript::*)())PalScript::Op_RoleMoveBackEx) */;
  byte_D8D18C = 1;
  byte_D8D18D = 1;
  word_D8D194 = 2;
  dword_D8D198 = 0 /* TODO: pmf_to_u32((char (PalScript::*)())PalScript::Op_RoleFaceRoleEx) */;
  word_D8D1A4 = 0;
  dword_D8D1A8 = 0 /* TODO: pmf_to_u32((char (PalScript::*)())PalScript::Op_RoleTurnFaceAEx) */;
  word_D8D1B4 = 0;
  g_ScriptSystemData.m_nTodo_D8D1B8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_TeamOpenAStartMove) */;
  g_ScriptSystemData.m_nTodo_D8D1BC = 1;
  g_ScriptSystemData.m_nTodo_D8D1BD = 2;
  g_ScriptSystemData.m_nTodo_D8D1BE = 2;
  g_ScriptSystemData.m_nTodo_D8D1BF = 2;
  word_D8D1C4 = 4;
  g_ScriptSystemData.m_nTodo_D8D1C8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_TeamCloseA) */;
  g_ScriptSystemData.m_nTodo_D8D1CC = 1;
  g_ScriptSystemData.m_nTodo_D8D1CD = 1;
  g_ScriptSystemData.m_nTodo_D8D1CE = 1;
  g_ScriptSystemData.m_nTodo_D8D1CF = 1;
  word_D8D1D4 = 4;
  dword_D8C648 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleActiveShort) */;
  byte_D8C64C = 1;
  word_D8C654 = 1;
  dword_D8C658 = 0 /* TODO: pmf_to_u32((char * (PalScript::*)())PalScript::Op_RoleScriptInitCam) */;
  byte_D8C65C = 2;
  byte_D8C65D = 2;
  byte_D8C65E = 2;
  word_D8C664 = 3;
  dword_D8C668 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_InTeam) */;
  byte_D8C66C = 2;
  byte_D8C66D = 2;
  byte_D8C66E = 1;
  word_D8C674 = 3;
  dword_D8C678 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleSetLayer) */;
  byte_D8C67C = 2;
  byte_D8C67D = 2;
  byte_D8C67E = 2;
  byte_D8C67F = 1;
  word_D8C684 = 4;
  dword_D8C688 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleCtrlEx) */;
  byte_D8C68C = 2;
  byte_D8C68D = 2;
  byte_D8C68E = 2;
  byte_D8C68F = 2;
  byte_D8C690 = 1;
  word_D8C694 = 5;
  dword_D8C698 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleOverlapEx) */;
  byte_D8C69C = 2;
  byte_D8C69D = 2;
  byte_D8C69E = 2;
  byte_D8C69F = 1;
  word_D8C6A4 = 4;
  dword_D8C6A8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleScale) */;
  byte_D8C6AC = 2;
  byte_D8C6AD = 2;
  byte_D8C6AE = 2;
  byte_D8C6AF = 2;
  byte_D8C6B0 = 2;
  byte_D8C6B1 = 2;
  word_D8C6B4 = 6;
  g_ScriptSystemData.m_nTodo_D8DAE8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraPush) */;
  g_ScriptSystemData.m_nTodo_D8DAEC = 2;
  g_ScriptSystemData.m_nTodo_D8DAED = 2;
  g_ScriptSystemData.m_nTodo_D8DAEE = 2;
  g_ScriptSystemData.m_nTodo_D8DAEF = 2;
  g_ScriptSystemData.m_nTodo_D8DAF0 = 2;
  g_ScriptSystemData.m_nTodo_D8DAF1 = 2;
  g_ScriptSystemData.m_nTodo_D8DAF2 = 2;
  word_D8DAF4 = 7;
  dword_D8C6B8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_ShowActAutoStand) */;
  byte_D8C6BC = 1;
  word_D8C6C4 = 1;
  dword_D8C6C8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleMoveBack) */;
  word_D8C6D4 = 0;
  dword_D8C6D8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleFaceRole) */;
  word_D8C6E4 = 0;
  g_ScriptSystemData.m_nTodo_D8D408 = (int)GetCamera4;
  g_ScriptSystemData.m_nTodo_D8D40C = 1;
  word_D8D414 = 1;
  g_ScriptSystemData.m_nTodo_D8D418 = (int)GetCurrentCamera;
  g_ScriptSystemData.m_nTodo_D8D41C = 1;
  word_D8D424 = 1;
  dword_D8C6E8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleTurnFaceA) */;
  byte_D8C6EC = 1;
  byte_D8C6ED = 1;
  byte_D8C6EE = 1;
  word_D8C6F4 = 3;
  dword_D8C6F8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_TeamOpenA) */;
  byte_D8C6FC = 1;
  byte_D8C6FD = 1;
  byte_D8C6FE = 1;
  word_D8C704 = 3;
  dword_D8C708 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_TeamCloseAEx) */;
  byte_D8C70C = 1;
  word_D8C714 = 1;
  dword_D8C718 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleSpaceWalk) */;
  byte_D8C71C = 1;
  byte_D8C71D = 1;
  word_D8C724 = 2;
  dword_D8C728 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleMoveTo) */;
  byte_D8C72C = 1;
  byte_D8C72D = 1;
  word_D8C734 = 2;
  dword_D8C738 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraFocusRole) */;
  byte_D8C73C = 1;
  byte_D8C73D = 1;
  byte_D8C73E = 1;
  word_D8C744 = 3;
  dword_D8C748 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraFocusPoint) */;
  byte_D8C74C = 1;
  byte_D8C74D = 1;
  word_D8C754 = 2;
  dword_D8C758 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_LoseItem) */;
  byte_D8C75C = 1;
  word_D8C764 = 1;
  dword_D8C768 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraRotate) */;
  byte_D8C76C = 1;
  word_D8C774 = 1;
  dword_D8C778 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraMove) */;
  byte_D8C77C = 1;
  word_D8C784 = 1;
  dword_D8C788 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraWag) */;
  byte_D8C78C = 1;
  byte_D8C78D = 1;
  word_D8C794 = 2;
  dword_D8C798 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraSet) */;
  byte_D8C79C = 1;
  byte_D8C79D = 1;
  word_D8C7A4 = 2;
  dword_D8C7A8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraTrans) */;
  byte_D8C7AC = 1;
  word_D8C7B4 = 1;
  dword_D8C7B8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraDefault) */;
  byte_D8C7BC = 1;
  word_D8C7C4 = 1;
  dword_D8C7C8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraPushState) */;
  byte_D8C7CC = 1;
  byte_D8C7CD = 1;
  word_D8C7D4 = 2;
  dword_D8C828 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_LK_Ghost) */;
  byte_D8C82C = 1;
  byte_D8C82D = 1;
  word_D8C834 = 2;
  dword_D8C838 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FavorAdd) */;
  byte_D8C83C = 1;
  word_D8C844 = 1;
  dword_D8C848 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Team) */;
  byte_D8C84C = 3;
  word_D8C854 = 1;
  dword_D8C858 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_AddRoleAtt) */;
  byte_D8C85C = 3;
  byte_D8C85D = 3;
  word_D8C864 = 2;
  dword_D8C868 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_AddItem) */;
  byte_D8C86C = 1;
  byte_D8C86D = 3;
  word_D8C874 = 2;
  dword_D8C878 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RemoveItem) */;
  byte_D8C87C = -6;
  word_D8C884 = 1;
  dword_D8C888 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_AddMoney) */;
  byte_D8C88C = 1;
  word_D8C894 = 1;
  dword_D8C898 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetMoney) */;
  byte_D8C89C = 1;
  byte_D8C89D = 3;
  byte_D8C89E = 1;
  word_D8C8A4 = 3;
  dword_D8C8A8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetFavor) */;
  byte_D8C8AC = 3;
  word_D8C8B4 = 1;
  dword_D8C8B8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_AddSkill) */;
  word_D8C8C4 = 0;
  dword_D8C8C8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetFavorite) */;
  word_D8C8D4 = 0;
  dword_D8C8D8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetDislike) */;
  byte_D8C8DC = 1;
  word_D8C8E4 = 1;
  dword_D8C8E8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FullRoleAtt) */;
  byte_D8C8EC = 1;
  byte_D8C8ED = 1;
  word_D8C8F4 = 2;
  dword_D8C8F8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_DlgPos) */;
  byte_D8C8FC = 1;
  byte_D8C8FD = 1;
  byte_D8C8FE = 1;
  byte_D8C8FF = 1;
  word_D8C904 = 4;
  dword_D8C908 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_DlgFont) */;
  byte_D8C90C = 1;
  byte_D8C90D = 1;
  word_D8C914 = 2;
  dword_D8C928 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_LoadScene) */;
  byte_D8C92C = 3;
  word_D8C934 = 1;
  dword_D8C938 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_DlgHead) */;
  byte_D8C93C = 1;
  word_D8C944 = 1;
  dword_D8C948 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_DlgSel) */;
  byte_D8C94C = 1;
  word_D8C954 = 1;
  dword_D8C958 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetDlgSel) */;
  byte_D8C95C = 3;
  byte_D8C95D = 1;
  word_D8C964 = 2;
  dword_D8C968 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_DlgFace) */;
  byte_D8C96C = 1;
  byte_D8C96D = 1;
  byte_D8C96E = 1;
  byte_D8C96F = 1;
  byte_D8C970 = 1;
  byte_D8C971 = 1;
  word_D8C974 = 6;
  dword_D8C978 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Note) */;
  word_D8C984 = 0;
  dword_D8C988 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FadeOut) */;
  byte_D8C98C = 1;
  word_D8C994 = 1;
  dword_D8C998 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FadeIn) */;
  word_D8C9A4 = 0;
  dword_D8C9A8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleStop) */;
  byte_D8C9AC = 1;
  word_D8C9B4 = 1;
  dword_D8C9B8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleEmote) */;
  byte_D8C9BC = 1;
  byte_D8C9BD = 1;
  word_D8C9C4 = 2;
  dword_D8C9C8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Combat) */;
  byte_D8C9CC = 3;
  byte_D8C9CD = 1;
  word_D8C9D4 = 2;
  dword_D8C9D8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Climb) */;
  byte_D8C9DC = 1;
  word_D8C9E4 = 1;
  dword_D8C9E8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_DlgTime) */;
  byte_D8C9EC = 1;
  word_D8C9F4 = 1;
  dword_D8C9F8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetTimeSel) */;
  byte_D8C9FC = 2;
  byte_D8C9FD = 2;
  byte_D8C9FE = 2;
  word_D8CA04 = 3;
  dword_D8CA08 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_HaveItem) */;
  byte_D8CA0C = 1;
  byte_D8CA0D = 2;
  byte_D8CA0E = 2;
  byte_D8CA0F = 2;
  byte_D8CA10 = 2;
  word_D8CA14 = 5;
  dword_D8CA18 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_PlaySound) */;
  word_D8CA24 = 0;
  dword_D8CAA8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_HY_Mode) */;
  byte_D8CAAC = 3;
  word_D8CAB4 = 1;
  dword_D8CAB8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_HY_FLY) */;
  byte_D8CABC = 1;
  word_D8CAC4 = 1;
  dword_D8CAC8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_ObjectMove) */;
  byte_D8CACC = 1;
  word_D8CAD4 = 1;
  dword_D8CAD8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FadeNormal) */;
  byte_D8CADC = 1;
  word_D8CAE4 = 1;
  dword_D8CAE8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Deal) */;
  word_D8CAF4 = 0;
  dword_D8CAF8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetHSLv) */;
  word_D8CB04 = 0;
  dword_D8CB08 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_SwitchRS) */;
  byte_D8CB0C = 1;
  word_D8CB14 = 1;
  dword_D8CB18 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_SetBigMapElement) */;
  byte_D8CB1C = 1;
  word_D8CB24 = 1;
  dword_D8CB28 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_APPR_Entry) */;
  byte_D8CB2C = 1;
  word_D8CB34 = 1;
  dword_D8CB38 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_KF_Entry) */;
  byte_D8CB3C = 1;
  word_D8CB44 = 1;
  dword_D8CB48 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_ENCAMP_Entry) */;
  byte_D8CB4C = 1;
  word_D8CB54 = 1;
  dword_D8CB58 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_SKEE_Entry) */;
  byte_D8CB5C = 1;
  word_D8CB64 = 1;
  dword_D8CB68 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Get_Appr) */;
  word_D8CB74 = 0;
  dword_D8CB78 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Enable_Sword) */;
  word_D8CB84 = 0;
  dword_D8CB88 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Enable_JusticeBook) */;
  word_D8CB94 = 0;
  dword_D8CB98 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Specify_Compos) */;
  byte_D8CB9C = 3;
  word_D8CBA4 = 1;
  dword_D8CBA8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Start_Wolf) */;
  byte_D8CBAC = 1;
  byte_D8CBAD = 3;
  word_D8CBB4 = 2;
  dword_D8CBB8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Start_HideFight) */;
  byte_D8CBBC = 1;
  byte_D8CBBD = 1;
  byte_D8CBBE = 1;
  word_D8CBC4 = 3;
  dword_D8CBC8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_JT_Exhibit) */;
  byte_D8CBCC = 2;
  byte_D8CBCD = 2;
  word_D8CBD4 = 2;
  dword_D8CBD8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Movie) */;
  byte_D8CBDC = 3;
  byte_D8CBDD = 1;
  byte_D8CBDE = 1;
  byte_D8CBDF = 1;
  word_D8CBE4 = 4;
  dword_D8CBE8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_SetRoleTexture) */;
  byte_D8CBEC = 1;
  word_D8CBF4 = 1;
  dword_D8CBF8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Rotate) */;
  byte_D8CBFC = 1;
  word_D8CC04 = 1;
  dword_D8CC08 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Quake) */;
  byte_D8CC0C = 1;
  word_D8CC14 = 1;
  dword_D8CC18 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_ShowChatRest) */;
  byte_D8CC1C = 1;
  word_D8CC24 = 1;
  dword_D8CC28 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetHS_ManageType) */;
  byte_D8CC2C = 1;
  word_D8CC34 = 1;
  dword_D8CC38 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetHS_Period_type) */;
  byte_D8CC3C = 1;
  byte_D8CC3D = 1;
  word_D8CC44 = 2;
  dword_D8CC48 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetHS_Accrual_type) */;
  byte_D8CC4C = 3;
  byte_D8CC4D = 1;
  byte_D8CC4E = 1;
  word_D8CC54 = 3;
  dword_D8CC58 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetHS_UnHock_type) */;
  byte_D8CC5C = 1;
  byte_D8CC5D = 1;
  word_D8CC64 = 2;
  dword_D8CC68 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Trigger) */;
  byte_D8CC6C = 1;
  byte_D8CC6D = 1;
  byte_D8CC6E = 1;
  word_D8CC74 = 3;
  dword_D8CC78 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_SetBigMapElement) */;
  byte_D8CC7C = 1;
  word_D8CC84 = 1;
  dword_D8CC88 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetSwitch) */;
  byte_D8CC8C = 1;
  byte_D8CC8D = 1;
  word_D8CC94 = 2;
  dword_D8CC98 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_EntryRow) */;
  word_D8CCA4 = 0;
  dword_D8CCA8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RotateInv) */;
  byte_D8CCAC = 1;
  word_D8CCB4 = 1;
  dword_D8CCB8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_EntrySkee) */;
  byte_D8CCBC = 3;
  byte_D8CCBD = 1;
  word_D8CCC4 = 2;
  dword_D8CCC8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Dist) */;
  word_D8CCD4 = 0;
  dword_D8CCD8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CombatNotGameOver) */;
  byte_D8CCDC = 1;
  word_D8CCE4 = 1;
  dword_D8CCE8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GetCombat) */;
  byte_D8CCEC = 1;
  word_D8CCF4 = 1;
  dword_D8CCF8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Music) */;
  byte_D8CCFC = 1;
  word_D8CD04 = 1;
  dword_D8CD08 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_StopMusic) */;
  byte_D8CD0C = 1;
  word_D8CD14 = 1;
  dword_D8CD18 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleFadeOut) */;
  byte_D8CD1C = 2;
  byte_D8CD1D = 1;
  byte_D8CD1E = 1;
  byte_D8CD1F = 1;
  word_D8CD24 = 4;
  dword_D8CD28 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_RoleFadeIn) */;
  byte_D8CD2C = 1;
  word_D8CD34 = 1;
  dword_D8CD38 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_IfInTeam) */;
  byte_D8CD3C = 1;
  word_D8CD44 = 1;
  dword_D8CD48 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Enable_SwordSkill) */;
  byte_D8CD4C = 2;
  byte_D8CD4D = 2;
  byte_D8CD4E = 2;
  word_D8CD54 = 3;
  dword_D8CD58 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FogH) */;
  byte_D8CD5C = 1;
  word_D8CD64 = 1;
  dword_D8CD68 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Snow) */;
  byte_D8CD6C = 1;
  word_D8CD74 = 1;
  dword_D8CD78 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_ScrEft) */;
  byte_D8CD7C = 1;
  byte_D8CD7D = 1;
  word_D8CD84 = 2;
  dword_D8CD88 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CEft_Pos) */;
  byte_D8CD8C = 1;
  word_D8CD94 = 1;
  dword_D8CD98 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CEft) */;
  word_D8CDA4 = 0;
  word_D8CE04 = 0;
  word_D8CE34 = 0;
  word_D8CE64 = 0;
  dword_D8CDA8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CEft_Role) */;
  byte_D8CDAC = 1;
  word_D8CDB4 = 1;
  dword_D8CDB8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_AverageLv) */;
  byte_D8CDBC = 1;
  word_D8CDC4 = 1;
  dword_D8CDC8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_EntrySmeltSys) */;
  byte_D8CDCC = 1;
  byte_D8CDCD = 3;
  word_D8CDD4 = 2;
  dword_D8CDD8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Switch2Menu) */;
  byte_D8CDDC = 1;
  word_D8CDE4 = 1;
  dword_D8CDE8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CEft_Load) */;
  byte_D8CDEC = 1;
  word_D8CDF4 = 1;
  dword_D8CDF8 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_GiveCloth) */;
  dword_D8CE08 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_LoadAct) */;
  byte_D8CE0C = 1;
  byte_D8CE0D = 1;
  byte_D8CE0E = 1;
  word_D8CE14 = 3;
  dword_D8CE18 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_Rain) */;
  byte_D8CE1C = 2;
  word_D8CE24 = 1;
  dword_D8CE28 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_WaterMagic) */;
  dword_D8CE38 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_FullTeamAtt) */;
  byte_D8CE3C = 3;
  word_D8CE44 = 1;
  dword_D8CE48 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_BeeInsertFrame) */;
  byte_D8CE4C = 1;
  word_D8CE54 = 1;
  dword_D8CE58 = 0 /* TODO: pmf_to_u32((void (PalScript::*)())PalScript::Op_CameraYaw) */;
  return result;
}

// 0x00433CD0
void FreeScriptInstance(int *pInstance)
{
  int v1; // esi
  int v2; // eax
  char v3; // cl
  int v4; // eax
  int v5; // esi
  int v6; // edi
  int v7; // eax
  bool v8; // cc
  int v9; // eax

  if ( pInstance )
  {
    if ( *pInstance )
    {
      if ( *(_WORD *)(*pInstance + 76) )
      {
        v1 = 0;
        do
        {
          v2 = (unsigned long)pInstance[19];
          v3 = *(_BYTE *)(v2 + 8 * v1);
          v4 = v2 + 8 * v1;
          if ( v3 == 3 )
          {
            free(*(void **)(v4 + 4));
            *(_DWORD *)(pInstance[19] + 8 * v1 + 4) = 0;
          }
          ++v1;
        }
        while ( v1 < *(unsigned __int16 *)(*pInstance + 76) );
        free((void *)pInstance[19]);
        pInstance[19] = 0;
      }
      v5 = (unsigned long)*pInstance;
      if ( *(_DWORD *)(*pInstance + 72) )
      {
        free(*(void **)(*pInstance + 72));
        *(_DWORD *)(v5 + 72) = 0;
      }
      if ( *(_WORD *)(v5 + 76) )
      {
        v6 = 0;
        do
        {
          v7 = *(_DWORD *)(v5 + 80);
          v8 = *(_WORD *)(v7 + 8 * v6 + 2) == 0;
          v9 = v7 + 8 * v6;
          if ( !v8 )
          {
            free(*(void **)(v9 + 4));
            *(_DWORD *)(*(_DWORD *)(v5 + 80) + 8 * v6 + 4) = 0;
          }
          ++v6;
        }
        while ( v6 < *(unsigned __int16 *)(v5 + 76) );
        free(*(void **)(v5 + 80));
        *(_DWORD *)(v5 + 80) = 0;
      }
      operator delete((void *)*pInstance);
      *pInstance = 0;
    }
    free(pInstance);
    (((PtrArray *)&dword_D8C348))->PtrArray::FindFirst(pInstance);
  }
}

// 0x004343F0
void FindByName(const char *pszName)
{
  int v1; // edi
  const char *v2; // ebp
  const char *v3; // [esp+0x14] [ebp+0x4]

  v1 = 0;
  if ( g_nPtrArray_D8E46C > 0 )
  {
    v2 = (const char *)(Block + 8);
    do
    {
      if ( !strcmp(v3, v2) )
        break;
      ++v1;
      v2 += 24;
    }
    while ( v1 < g_nPtrArray_D8E46C );
  }
}

// 0x00434BD0
void * GetSceneObject(unsigned __int16 nObjID)
{
  if ( nObjID == 0xFFFF )
    return g_pRoleSystem;
  if ( nObjID < 0xAu )
    return ScriptSystem::GetMainRoleSystem(nObjID);
  UISceneUpdate();
  return (void *)sub_420200(nObjID);
}

// 0x00434F60
int ConvertDirection(int nDir)
{
  if ( nDir )
  {
    if ( nDir == 1 )
      return 2;
    if ( nDir == 2 )
      return 3;
  }
  return 1;
}

// 0x00435350
gbCamera * GetCurrentCamera()
{
  PalScript *v0; // ecx
  gbCamera *result; // eax
  PalScript *v2; // eax
  int v3; // eax
  gbCamera *v4; // [esp-0x4] [ebp-0x4]

  result = (gbCamera *)(((PalScript *)v0))->PalScript::GetString();
  if ( result )
  {
    LOWORD(result) = LOWORD(result->OrthoSize);
    v4 = (gbCamera *)result;
    v2 = (PalScript *)UISceneUpdate();
    (((PalScript *)v2))->PalScript::SetAction((int)v4);
    return (gbCamera *)(((RoleSystem *)g_pCameraCtrl))->RoleSystem::SetInactive(v3);
  }
  return result;
}

// 0x00435380
gbCamera * GetCamera4()
{
  PalScript *v0; // ecx
  gbCamera *result; // eax

  result = (gbCamera *)(((PalScript *)v0))->PalScript::GetString();
  if ( result )
  {
    result = (gbCamera *)LODWORD(result->OrthoSize);
    *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = (unsigned long)result;
  }
  return result;
}

// 0x00437D90
int FindOpcodeByName(char *pszCmdName)
{
  int v1; // edi
  const char *i; // esi

  v1 = 0;
  for ( i = "Pal3op"; ; i += 30 )
  {
    if ( !_strcmpi(i, "#End") )
      return -1;
    if ( !_strcmpi(i, pszCmdName) )
      break;
    ++v1;
  }
  return v1;
}

// 0x00437DE0
void SetGameSwitch(int nSwitchIdx)
{
  int v1; // edi
  int v2; // esi
  int i; // ecx
  int v4; // eax
  int v5; // ecx
  char *v6; // eax

  if ( nSwitchIdx < 52 )
  {
    LoadGameSwitches();
    byte_D8EBBC[nSwitchIdx] = 1;
    v1 = 0;
    v2 = 0;
    for ( i = 0; i < 32; ++i )
      v1 |= (unsigned __int8)byte_D8EBBC[i] << i;
    v4 = i;
    v5 = 0;
    v6 = (char *)&byte_D8EBBC[v4];
    do
    {
      v2 |= (unsigned __int8)*v6++ << v5;
      if ( (int)v6 >= (int)dword_D8EBF0 )
        break;
      ++v5;
    }
    while ( v5 < 32 );
    PAL3::WriteRegistryValue(aSoftwareSoftst_2, (DWORD)ValueName, v1);
    PAL3::WriteRegistryValue(aSoftwareSoftst_2, (DWORD)"MOVIE_B", v2);
  }
}

// 0x00437F40
char * LoadGameSwitches()
{
  char *result; // eax
  int v1; // eax
  int i; // ecx
  int v3; // esi
  int v4; // eax
  int v5; // ecx
  BYTE Data[4]; // [esp+0x8] [ebp-0x8] BYREF
  BYTE v7[4]; // [esp+0xC] [ebp-0x4] BYREF

  memset(byte_D8EBBC, 0, 0x34u);
  *(_DWORD *)Data = 0;
  *(_DWORD *)v7 = 0;
  result = (char *)ReadRegistryString(aSoftwareSoftst_2, ValueName, (char *)Data);
  if ( (_BYTE)result )
  {
    result = (char *)ReadRegistryString(aSoftwareSoftst_2, "MOVIE_B", (char *)v7);
    if ( (_BYTE)result )
    {
      v1 = *(_DWORD *)Data;
      for ( i = 0; i < 32; ++i )
        byte_D8EBBC[i] = ((1 << i) & v1) != 0;
      v3 = *(_DWORD *)v7;
      v4 = i;
      v5 = 0;
      result = (char *)&byte_D8EBBC[v4];
      do
      {
        *result++ = ((1 << v5) & v3) != 0;
        if ( (int)result >= (int)dword_D8EBF0 )
          break;
        ++v5;
      }
      while ( v5 < 32 );
    }
  }
  return result;
}

// 0x0043A0E0
int UIPushButton_SetParam(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 248) = nVal;
  return result;
}

// 0x0043A4B0
int UIScene_SetController(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 68) = nVal;
  return result;
}

// 0x0043A5D0
int UIScene_OpenAndLoadResource(int nVal)
{
  int v1; // ecx
  UIScene *v2; // esi
  int result; // eax
  OpenBaseFile v4; // [esp+0x8] [ebp-0x10] BYREF
  int v5; // [esp+0x14] [ebp-0x4]
  unsigned int v6; // [esp+0x20] [ebp+0x8]

  v2 = (UIScene *)v1;
  (((UIWnd *)(v1 + 76)))->UIWnd::MoveWindow();
  v5 = 0;
  LoadUISceneTexture(nVal, 1);
  v2->m_bLoadState = 1;
  v2->m_dwColor = v6;
  (((UIScene *)v2))->UIScene::ResetState();
  v5 = -1;
  ((OpenNULLFile *)&v4)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x0043B3E0
int UIScenePanel__UIScenePanel(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // esi
  int v4; // [esp+0x4] [ebp-0x4]

  v2 = (_DWORD *)v1;
  NameSys::GetSys();
  v2[89] = 32;
  v2[86] = 0;
  v2[87] = 0;
  v2[88] = 0;
  v2[90] = 1;
  if ( gbColorQuad::ColorQuadFmt )
  {
    LOBYTE(v4) = 0x80;
    *(_WORD *)((char *)&v4 + 1) = 17476;
  }
  else
  {
    *(_WORD *)((char *)&v4 + 1) = -32700;
    LOBYTE(v4) = 68;
  }
  HIBYTE(v4) = -1;
  v2[91] = v4;
  v2[92] = -16777216;
  v2[93] = -16119286;
  return (int)v2;
}

// 0x0043BBB0
void UIFrameWnd(UIFrameWnd *_this)
{
  (((UIWnd *)_this))->UIWnd::_UIWnd();
}

// 0x0043C9D0
void fill(PlayerItem *a1, PlayerItem *a2, PlayerItem *a3)
{
  float *v3; // ecx
  int v4; // eax
  float *v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // edi
  __int64 v10; // rax
  int v11; // ecx
  int v12; // ebp
  int v13; // ecx
  int v14; // ebx
  int v15; // ecx
  int v16; // eax
  int v17; // ebp
  int v18; // edi
  __int64 v19; // rax
  int v20; // ecx
  int v21; // edi
  int v22; // ebp
  int v23; // ebx
  int v24; // edi
  __int64 v25; // rax
  PlayerItem *a1a; // [esp+0x18] [ebp+0x4]

  v4 = (int)a1;
  v5 = (float *)v3;
  if ( (int)a1 <= 1 )
  {
    if ( (int)a1 < 0 )
      v4 = 0;
  }
  else
  {
    v4 = 1;
  }
  *((_DWORD *)v3 + 66) = v4;
  if ( !v4 )
  {
    v14 = *((_DWORD *)v3 + 36);
    v15 = *((_DWORD *)v3 + 34);
    v16 = *((_DWORD *)v5 + 67);
    v5[56] = (double)*((int *)v5 + 36) - v5[59] + v5[63] - ((double)v15 + v5[62] + v5[59]);
    if ( v16 )
    {
      if ( v16 != 1 )
        goto LABEL_17;
      v17 = *((_DWORD *)v5 + 24);
      v18 = *((_DWORD *)v5 + 35) + *((_DWORD *)v5 + 61) - v17;
      a1a = (PlayerItem *)(v14 - *((_DWORD *)v5 + 23) / 2);
      *((_DWORD *)v5 + 31) = v18;
      v19 = (__int64)((double)(int)a1a - v5[59] + v5[63]);
      v20 = *((_DWORD *)v5 + 23);
      *((_DWORD *)v5 + 30) = v19;
      v21 = v17 + v18;
      *((_DWORD *)v5 + 32) = v20 + v19;
    }
    else
    {
      v22 = *((_DWORD *)v5 + 23);
      v23 = *((_DWORD *)v5 + 24);
      v24 = *((_DWORD *)v5 + 35) + *((_DWORD *)v5 + 61) - v23;
      *((_DWORD *)v5 + 31) = v24;
      v25 = (__int64)((double)(v15 - v22 / 2) + v5[62] + v5[59]);
      *((_DWORD *)v5 + 30) = v25;
      *((_DWORD *)v5 + 32) = v22 + v25;
      v21 = v23 + v24;
    }
    *((_DWORD *)v5 + 33) = v21;
    goto LABEL_17;
  }
  if ( v4 == 1 )
  {
    v6 = *((_DWORD *)v3 + 37);
    v7 = *((_DWORD *)v5 + 35);
    v8 = *((_DWORD *)v5 + 67);
    v5[56] = (double)*((int *)v5 + 37) - v5[59] + v5[65] - ((double)v7 + v5[64] + v5[59]);
    if ( !v8 )
    {
      v9 = *((_DWORD *)v5 + 24);
      v10 = (__int64)((double)(v7 - v9) + v5[64] + v5[59]);
      *((float *)&v10 + 1) = v5[23];
      v11 = *((_DWORD *)v5 + 61);
      v12 = *((_DWORD *)v5 + 34);
      *((_DWORD *)v5 + 31) = v10;
      goto LABEL_10;
    }
    if ( v8 == 1 )
    {
      v9 = *((_DWORD *)v5 + 24);
      v10 = (__int64)((double)(v6 - v9) - v5[59] + v5[65]);
      *((float *)&v10 + 1) = v5[23];
      v11 = *((_DWORD *)v5 + 61);
      v12 = *((_DWORD *)v5 + 36);
      *((_DWORD *)v5 + 31) = v10;
LABEL_10:
      v13 = v12 + v11 - HIDWORD(v10);
      *((_DWORD *)v5 + 30) = v13;
      *((_DWORD *)v5 + 32) = HIDWORD(v10) + v13;
      *((_DWORD *)v5 + 33) = v9 + v10;
    }
  }
LABEL_17:
  v5[60] = v5[57] / v5[56];
}

// 0x0043D880
void UIFrameWnd__deleting_view(UIFrameWnd *_this)
{
  (((UIWnd *)_this))->UIWnd::_UIWnd();
}

// 0x0043F690
int UIListBox_SetItemData(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 1188) = nVal;
  return result;
}

// 0x0043F6A0
int UIListBox_SetChildParam(int nVal)
{
  int v1; // ecx
  int result; // eax
  int v3; // [esp+0x10] [ebp+0x8]

  *(_DWORD *)(*(_DWORD *)(v1 + 1196) + 4 * nVal) = v3;
  result = (((UIListBox *)v1))->UIListBox::CreateChild();
  if ( nVal == result )
    return UIListBox_SetFirstShow(nVal);
  return result;
}

// 0x0043F6D0
int UIListBox_SetFirstShow(int nVal)
{
  _DWORD *v1; // ecx
  int v2; // edx
  int v3; // eax
  int v4; // esi
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int result; // eax
  _DWORD *v9; // edx

  v2 = (unsigned long)v1[299];
  if ( v2 )
    v3 = (v1[300] - v2) >> 2;
  else
    v3 = 0;
  v4 = nVal;
  if ( nVal >= (unsigned int)(v3 - 1) )
  {
    v5 = (unsigned long)v1[299];
    if ( v5 )
      v6 = (v1[300] - v5) >> 2;
    else
      v6 = 0;
    v4 = v6 - 1;
  }
  v7 = (unsigned long)v1[299];
  for ( result = v4; v7 && result < (unsigned int)((v1[300] - v7) >> 2); ++result )
  {
    if ( *(_DWORD *)(v1[299] + 4 * result) )
      goto LABEL_19;
  }
  result = 0;
  if ( v4 <= 0 )
  {
LABEL_18:
    v1[280] = -1;
    return result;
  }
  v9 = (_DWORD *)v1[299];
  while ( !*v9 )
  {
    ++result;
    ++v9;
    if ( result >= v4 )
      goto LABEL_18;
  }
LABEL_19:
  result -= v1[279];
  v1[280] = result;
  return result;
}

// 0x0043F7F0
// write access to const memory has been detected, the output may be wrong!
void ctor_17(UIButton *_this)
{
  int v2; // ecx

  ClearSubArraySlot();
  *(_DWORD *)&_this->m_hasDBclk = 0;
  _this->m_ratiow = 0.0;
  _this->m_texarray.m_ptex[3] = 0;
  _this->m_texarray.m_ptex[4] = (gbTexture *)1065353216;
  _this->m_texarray.m_ptex[5] = 0;
  _this->m_texarray.m_ptex[7] = 0;
  _this->m_texarray.m_ptex[9] = (gbTexture *)0x40000000;
  _this->m_texarray.m_ptex[10] = 0;
  _this->m_texarray.m_ptex[11] = 0;
  _this->m_texarray.m_ptex[12] = 0;
  _this->m_texarray.m_ptex[13] = 0;
  _this->m_texarray.m_ptex[14] = 0;
  _this->m_texarray.m_ptex[15] = 0;
  LOBYTE(_this->m_texarray.m_num) = 0;
  _this->m_texarrayInfo[2] = 0;
  _this->m_disablepicInfo = 0;
  _this->m_alignmode = 0;
  *(_DWORD *)&_this->m_caption[4] = 0;
  *(_DWORD *)&_this->m_caption[8] = 0;
  *(_DWORD *)&_this->m_caption[12] = 0;
  *(_DWORD *)&_this->m_caption[16] = 0;
  BYTE2(_this->m_texarrayInfo[0]) = -1;
  BYTE1(_this->m_texarrayInfo[0]) = -1;
  LOBYTE(_this->m_texarrayInfo[0]) = -1;
  HIBYTE(_this->m_texarrayInfo[0]) = -1;
  gbColorQuad::ColorQuadFmt = 1;
  BYTE2(_this->m_texarrayInfo[1]) = -1;
  BYTE1(_this->m_texarrayInfo[1]) = 0;
  LOBYTE(_this->m_texarrayInfo[1]) = 0;
  HIBYTE(_this->m_texarrayInfo[1]) = -1;
  *(_DWORD *)&_this->m_caption[20] = 0;
  *(_DWORD *)&_this->m_caption[40] = 1065353216;
  _this->m_caption[44] = 0;
  _this->m_caption[45] = 0;
  _this->m_caption[46] = 0;
  *(_DWORD *)&_this->m_caption[36] = 6;
  *(_DWORD *)&_this->m_caption[24] = -1;
  v2 = (unsigned __int8)_this->m_caption[27];
  _this->m_disablepic = 0;
  *(_DWORD *)&_this->m_mouseoff = 0;
  *(_DWORD *)_this->m_caption = 0;
  *(_DWORD *)&_this->m_caption[32] = v2;
  *(_DWORD *)&_this->m_caption[28] = v2;
  *(_DWORD *)&_this->m_caption[48] = -1;
}

// 0x004413C0
int CCBUI_LoadTextureSequence(int nVal)
{
  int v1; // ecx
  int result; // eax
  int v3; // esi
  int v4; // ebx
  UIWnd *v5; // edi
  Parent_Data **v6; // ebx
  CHAR *v7; // eax
  OpenBaseFile v8; // [esp+0x10] [ebp-0x114] BYREF
  CHAR String1[260]; // [esp+0x14] [ebp-0x110] BYREF
  int v10; // [esp+0x120] [ebp-0x4]
  char v11; // [esp+0x12C] [ebp+0x8]

  result = nVal;
  v3 = 0;
  v4 = v1;
  if ( !nVal )
    return result;
  v5 = (UIWnd *)(v4 + 192);
  v10 = 0;
  (((UIWnd *)(v4 + 192)))->UIWnd::MoveWindow();
  v6 = (Parent_Data **)(v4 + 260);
  while ( 1 )
  {
    sprintf(String1, "%s%d.tga", (const char *)nVal, v3);
    if ( !v11 )
      break;
    *v6 = (((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(String1);
    v7 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(String1);
    lstrcpyA(String1, v7);
    if ( !LoadUISceneTexture((int)String1, 1) )
      goto LABEL_9;
LABEL_7:
    ++v3;
    ++v6;
    if ( v3 >= 10 )
      goto LABEL_10;
  }
  if ( LoadUISceneTexture((int)String1, 1) )
    goto LABEL_7;
LABEL_9:
  (((UIWnd *)v5))->UIWnd::MoveWindow();
LABEL_10:
  v10 = -1;
  ((OpenNULLFile *)&v8)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x00442000
int CalcWeightedOffset()
{
  _DWORD *v0; // ecx
  int v1; // ebx

  v1 = (unsigned long)(v0[42] - v0[41]);
  if ( v1 > 0 )
    return v0[85] + v0[79] + v0[43] * (v0[81] + -2 * v0[85] - v0[87] / 2 - v0[79]) / v1;
  else
    return v0[5] + v0[39];
}

// 0x004427C0
void SetEnable(UICaption *_this)
{
  float *v1; // ebp
  unsigned int v2; // kr04_4
  unsigned int v3; // ebx
  int v4; // ecx
  char v5; // al
  unsigned int v6; // eax
  int v7; // ecx
  const char *v9; // [esp+0x10] [ebp+0x4]
  int v10; // [esp+0x14] [ebp+0x8]

  if ( v9 )
  {
    v1 = (float *)(&_this->m_linetime + 1);
    v2 = strlen(v9) + 1;
    v3 = v2 - 1;
    if ( v2 - 1 > 0xFFFFFFFD )
      std::_Xlen();
    v4 = *((_DWORD *)v1 + 1);
    if ( v4 && (v5 = *(_BYTE *)(v4 - 1)) != 0 && v5 != -1 )
    {
      if ( v2 == 1 )
      {
        *(_BYTE *)(v4 - 1) = v5 - 1;
        v1[1] = 0.0;
        v1[2] = 0.0;
        v1[3] = 0.0;
        goto LABEL_16;
      }
    }
    else
    {
      if ( v2 == 1 )
      {
        (((std::string *)1))->_Tidy();
        goto LABEL_16;
      }
      v6 = *((_DWORD *)v1 + 3);
      if ( v6 <= 0x1F && v6 >= v3 )
      {
LABEL_15:
        qmemcpy(*((void **)v1 + 1), v9, v3);
        v7 = *((_DWORD *)v1 + 1);
        *((_DWORD *)v1 + 2) = v3;
        *(_BYTE *)(v7 + v3) = 0;
LABEL_16:
        if ( v10 )
          _this->m_needscriptdel = (gbImage2D *)1;
        else
          _this->m_needscriptdel = 0;
        return;
      }
      (((std::string *)1))->_Tidy();
    }
    (((GRPinput *)v1))->GRPinput::PollInputState(v3);
    goto LABEL_15;
  }
}

// 0x00443BA0
bool IsHitLeft(CCBFiveNimbusWindow *_this)
{
  float v2; // [esp+0x4] [ebp+0x4]

  return (double)((unsigned int)_this->pMiddle + (unsigned int)_this->pCtrlButton[1] - 256) < *(float *)(80 * _this->m_nimbus[0] + _this->m_nimbus[1] - 44)
                                                                                          - v2
                                                                                          * *(float *)&_this->m_state[4]
                                                                                          * *(float *)&_this->m_nimbus[2];
}

// 0x00445010
void UITextArea_Destroy()
{
  int v0; // ecx
  UIWnd *v1; // esi
  unsigned int Color; // eax
  _BYTE *v3; // ecx
  char v4; // al

  v1 = (UIWnd *)v0;
  (((UIWnd *)(v0 + 104)))->MoveWindow();
  Color = v1[1].m_wndcolor.Color;
  if ( Color )
  {
    v3 = (_BYTE *)(Color - 1);
    v4 = *(_BYTE *)(Color - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      *v3 = v4 - 1;
  }
  v1[1].m_wndcolor.Color = 0;
  v1[1].m_id = 0;
  v1[1].m_rect.left = 0;
  (((UIWnd *)v1))->UIWnd::_UIWnd();
}

// 0x00445AA0
int ClearSubArraySlot()
{
  int v0; // ecx
  _DWORD *v1; // esi
  int v3; // [esp+0x4] [ebp-0x4]

  v1 = (_DWORD *)v0;
  (((PtrArray *)(v0 + 36)))->PtrArray::Clear();
  v1[3] = -1;
  v1[4] = 0;
  v1[5] = 0;
  v1[6] = 0;
  v1[7] = 0;
  v1[8] = 0;
  v1[13] = 0;
  v1[14] = 0;
  v1[15] = 0;
  v1[16] = 0;
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v3) = 0;
    LOWORD(v3) = 1285;
  }
  else
  {
    LOBYTE(v3) = 0;
    *(_WORD *)((char *)&v3 + 1) = 1285;
  }
  HIBYTE(v3) = -1;
  v1[1] = v3;
  v1[2] = -1;
  return (int)v1;
}

// 0x00445D20
int MoveToAbsolute(_DWORD *_this, int a2, int a3)
{
  return sub_445D40(_this, a2 - _this[4], a3 - _this[5]);
}

// 0x00445E10
int * OffsetRect(int *p_DWORD)
{
  int *result; // eax
  LONG bottom; // edx
  LPRECT lprc; // [esp+0x8] [ebp+0x4]

  result = (int *)&lprc->left;
  lprc->left += p_DWORD[4];
  lprc->right += p_DWORD[4];
  bottom = lprc->bottom;
  lprc->top += p_DWORD[5];
  lprc->bottom = p_DWORD[5] + bottom;
  return result;
}

// 0x00445EA0
void * ZeroInitSelf68()
{
  void *v0; // ecx

  memset(v0, 0, 0x44u);
  return v0;
}

// 0x00445ED0
int LoadUISceneTexture(int a2, int a3)
{
  int v2; // ecx
  int result; // eax
  int v4; // edi
  int v5; // esi

  result = a2;
  v4 = v2;
  if ( a2 )
  {
    result = gfxMgr->NewTexture((const char *)a2);
    v5 = result;
    if ( result )
    {
      (((gbTexture *)result))->gbTexture::LoadTexture(a3);
      *(_DWORD *)(v4 + 4 * (*(_DWORD *)(v4 + 64))++) = v5;
      return 1;
    }
  }
  return result;
}

// 0x00445F60
int GetTableEntry16(unsigned int a2)
{
  int v1; // ecx

  if ( a2 >= 0x10 )
    return 0;
  else
    return *(_DWORD *)(v1 + 4 * a2);
}

// 0x00446010
void * AllocObject(void *a2)
{
  void *result; // eax
  _DWORD *v2; // [esp+0x4] [ebp+0x4]

  result = (void *)v2;
  *((_DWORD *)a2 + 1) = (unsigned long)*v2;
  return result;
}

// 0x00449980
int CCBUIPanel_SetUserData(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 364) = nVal;
  return result;
}

// 0x00449AB0
int CCBUIPanel_CenterSlot(int nVal)
{
  int v1; // ecx
  int result; // eax
  int v3; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // edi
  float v7; // st7
  int v8; // edi
  __int64 v9; // rax
  float nVala; // [esp+0x10] [ebp+0x4]

  result = nVal;
  v3 = v1;
  if ( (unsigned int)nVal <= 0x25 )
  {
    v4 = v1 + 476 * nVal + 512;
    v5 = *(_DWORD *)(v3 + 476 * nVal + 520);
    *(_DWORD *)(v4 + 88) = *(_DWORD *)(v3 + 476 * nVal + 524)
                         - (*(_DWORD *)(v3 + 476 * nVal + 524) - *(_DWORD *)(v3 + 476 * nVal + 516)) / 2;
    v6 = *(_DWORD *)(v3 + 476 * nVal + 528) - (*(_DWORD *)(v3 + 476 * nVal + 528) - v5) / 2;
    *(_DWORD *)(v4 + 92) = v6;
    v7 = (float)*(int *)(v3 + 476 * nVal + 600) + *(float *)(v3 + 18780);
    *(float *)(v3 + 18780) = v7;
    nVala = (float)v6 + *(float *)(v3 + 18784);
    *(float *)(v3 + 18784) = nVala;
    v8 = (__int64)v7;
    *(_DWORD *)(v3 + 18788) = v8;
    v9 = (__int64)nVala;
    *(_DWORD *)(v3 + 18792) = v9;
    *(_DWORD *)(v3 + 18604) = v9;
    *(_DWORD *)(v3 + 18600) = v8;
    *(_DWORD *)(v3 + 18608) = v8 + 64;
    *(_DWORD *)(v3 + 18612) = v9 + 64;
    return (((UIWnd *)(v3 + 18616)))->UIWnd::sub_445FA0((void *)(v3 + 18600));
  }
  return result;
}

// 0x00449C50
int CCBUIPanel_UpdateSlotClipping(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // edi
  int v3; // ebp
  _DWORD *v4; // esi
  int v5; // eax
  int v6; // eax
  int v8; // [esp+0xC] [ebp-0x4]

  v2 = (_DWORD *)v1;
  v8 = 0;
  v3 = 38;
  v4 = (_DWORD *)(v1 + 152);
  do
  {
    if ( *((_BYTE *)v4 - 96) )
    {
      v5 = *(v4 - 13);
      if ( v5 >= v2[20] - v2[18] || v5 <= -*(v4 - 5) || (v6 = *(v4 - 11), v6 >= v2[21] - v2[19]) || v6 <= -*(v4 - 4) )
      {
        if ( *((_BYTE *)v4 + 376) )
        {
          (*(void ( **)(_DWORD *, _DWORD))*v4)(v4, 0);
          *((_BYTE *)v4 + 377) = 0;
        }
      }
      else
      {
        if ( *((_BYTE *)v4 + 376) )
        {
          (*(void ( **)(_DWORD *, int))*v4)(v4, 1);
          *((_BYTE *)v4 + 377) = 1;
        }
        ++v8;
      }
    }
    v4 += 119;
    --v3;
  }
  while ( v3 );
  return v8;
}

// 0x00449CF0
int CCBUIPanel_UpdateSlotPositions(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // ebp
  int v4; // esi
  _DWORD *v5; // ebx
  float v6; // st7
  int v7; // esi
  __int64 v8; // rax
  float v9; // st7

  v2 = v1;
  v3 = 38;
  v4 = v1 + 552;
  do
  {
    v5 = (_DWORD *)(v4 - 36);
    *(float *)(v4 - 4) = *(float *)(v2 + 484) + *(float *)(v4 - 4);
    *(float *)v4 = *(float *)(v2 + 488) + *(float *)v4;
    *v5 = (__int64)*(float *)(v4 - 4);
    *(_DWORD *)(v4 - 32) = (__int64)*(float *)v4;
    *(_DWORD *)(v4 - 28) = *(_DWORD *)(v4 - 36) + *(_DWORD *)(v4 + 36);
    *(_DWORD *)(v4 - 24) = *(_DWORD *)(v4 - 32) + *(_DWORD *)(v4 + 40);
    (((UIWnd *)(v4 + 56)))->UIWnd::sub_445FA0((void *)(v4 - 36));
    *(_DWORD *)(v4 + 4) = *(_DWORD *)(v4 - 36) - *(_DWORD *)(v2 + 72);
    v4 += 476;
    *(_DWORD *)(v4 - 468) = (unsigned long)(*v5 - *(_DWORD *)(v2 + 80));
    *(_DWORD *)(v4 - 464) = *(_DWORD *)(v4 - 508) - *(_DWORD *)(v2 + 76);
    --v3;
    *(_DWORD *)(v4 - 460) = *(_DWORD *)(v4 - 508) - *(_DWORD *)(v2 + 84);
  }
  while ( v3 );
  *(float *)(v2 + 18780) = *(float *)(v2 + 484) + *(float *)(v2 + 18780);
  *(float *)(v2 + 18784) = *(float *)(v2 + 488) + *(float *)(v2 + 18784);
  v6 = *(float *)(v2 + 18784);
  v7 = (__int64)*(float *)(v2 + 18780);
  *(_DWORD *)(v2 + 18788) = v7;
  *(_DWORD *)(v2 + 18792) = (__int64)v6;
  *(_DWORD *)(v2 + 18604) = (__int64)v6;
  *(_DWORD *)(v2 + 18600) = v7;
  *(_DWORD *)(v2 + 18608) = v7 + 64;
  *(_DWORD *)(v2 + 18612) = (__int64)v6 + 64;
  LODWORD(v8) = (((UIWnd *)(v2 + 18616)))->UIWnd::sub_445FA0((void *)(v2 + 18600));
  LOBYTE(v8) = *(_BYTE *)(v2 + 18824);
  if ( (_BYTE)v8 )
  {
    *(float *)(v2 + 18804) = *(float *)(v2 + 484) + *(float *)(v2 + 18804);
    *(float *)(v2 + 18808) = *(float *)(v2 + 488) + *(float *)(v2 + 18808);
    v9 = *(float *)(v2 + 18808);
    *(_DWORD *)(v2 + 18796) = (__int64)*(float *)(v2 + 18804);
    v8 = (__int64)v9;
    *(_DWORD *)(v2 + 18800) = (__int64)v9;
  }
  return v8;
}

// 0x00449E60
int CCBUIPanel_EnsureSize(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  int result; // eax
  int v5; // [esp+0x14] [ebp+0x8]

  v2 = v1;
  v3 = *(_DWORD *)(v1 + 18788);
  if ( nVal > v3 && v5 > *(_DWORD *)(v1 + 18792) )
  {
    (((UIScene *)(v1 + 18616)))->UIScene::LoadResource((void *)off_5995A8);
LABEL_7:
    *(_DWORD *)(v2 + 18832) = 1;
    goto LABEL_8;
  }
  if ( nVal > v3 && v5 <= *(_DWORD *)(v1 + 18792) )
  {
    (((UIScene *)(v1 + 18616)))->UIScene::LoadResource((void *)off_5995A0);
    goto LABEL_7;
  }
LABEL_8:
  result = *(_DWORD *)(v2 + 18788);
  if ( nVal >= result )
    return result;
  if ( v5 > *(_DWORD *)(v2 + 18792) )
  {
    (((UIScene *)(v2 + 18616)))->UIScene::LoadResource((void *)off_5995A4);
LABEL_14:
    *(_DWORD *)(v2 + 18832) = 0;
    return result;
  }
  if ( nVal < result && v5 <= *(_DWORD *)(v2 + 18792) )
  {
    (((UIScene *)(v2 + 18616)))->UIScene::LoadResource((void *)off_59959C);
    goto LABEL_14;
  }
  return result;
}

// 0x0044A180
int CCBUIPanel_SetAllSlotsVisible(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int result; // eax

  v2 = v1 + 608;
  v3 = 38;
  do
  {
    result = sub_445E50(v2);
    v2 += 476;
    --v3;
  }
  while ( v3 );
  return result;
}

// 0x0044A7F0
void UIWnd_RenderText()
{
  UIWnd *v0; // ecx

  (((UIWnd *)v0))->UIWnd::_UIWnd();
}

// 0x0044A970
int PalScriptIdleObj_LoadScriptTexture(int nVal)
{
  int v1; // ecx
  int v2; // esi
  gbTexture *v3; // eax
  int v4; // ecx
  int v5; // edx
  void ( **v6)(int, int); // eax
  int result; // eax
  OpenBaseFile v8; // [esp+0xC] [ebp-0x10] BYREF
  int v9; // [esp+0x18] [ebp-0x4]
  int v10; // [esp+0x24] [ebp+0x8]

  v2 = v1;
  (*(void (**)(void))(*(_DWORD *)v1 + 12))();
  *(_DWORD *)(v2 + 84) = 42;
  *(_DWORD *)(v2 + 80) = v10;
  v9 = 0;
  v3 = (gbTexture *)gfxMgr->NewTexture((const char *)nVal);
  *(_DWORD *)(v2 + 76) = (_DWORD)v3;
  (((gbTexture *)v3))->gbTexture::LoadTexture(1);
  v4 = *(_DWORD *)(v2 + 76);
  v5 = *(_DWORD *)(v2 + 20);
  *(_DWORD *)(v2 + 92) = 0;
  *(_DWORD *)(v2 + 88) = 0;
  v6 = *(void ( ***)(int, int))v2;
  *(_DWORD *)(v2 + 28) = *(_DWORD *)(v4 + 28) + v5;
  (*v6)(v2, 1);
  v9 = -1;
  ((OpenNULLFile *)&v8)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x0044AB40
void todo_0044AB40(int a1)
{
  ;
}

// 0x0044AB90
int UITitle_UITitle(int nVal)
{
  int v1; // ecx
  int v2; // esi

  v2 = v1;
  ClearSubArraySlot();
  *(_DWORD *)(v2 + 108) = 360;
  *(_DWORD *)(v2 + 112) = 136;
  (((UIFrameContainer *)(v2 + 124)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 276)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  ((UIRoleDialog *)(v2 + 1916))->UIRoleDialog::UIRoleDialog();
  *(_BYTE *)(v2 + 3300) = 0;
  *(_DWORD *)(v2 + 3296) = 0;
  *(_DWORD *)(v2 + 3292) = 0;
  ((UIRoleDialog *)(v2 + 3308))->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)(v2 + 4676))->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)(v2 + 6044))->UIRoleDialog::UIRoleDialog();
  ((LineupComp *)(v2 + 7420))->LineupComp::LineupComp();
  *(_DWORD *)(v2 + 116) = 90;
  *(_DWORD *)(v2 + 120) = 24;
  return v2;
}

// 0x0044BD80
void SafeDeletePtr(void **pptr)
{
  void **v1; // ecx
  void **v2; // esi

  v2 = (void **)v1;
  if ( *v1 )
  {
    operator delete(*v1);
    *v2 = 0;
  }
}

// 0x0044CB30
int InitParticles(Actor *_this)
{
  int *v2; // ebp
  void **p_m_pParticleData; // esi
  int v4; // eax
  unsigned int v5; // eax
  unsigned int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  _DWORD *v11; // edx
  int v12; // eax
  int v13; // ecx
  int v15; // [esp+0x0] [ebp-0x24]
  int v16; // [esp+0x10] [ebp-0x14]
  int v17; // [esp+0x14] [ebp-0x10] BYREF
  int v18; // [esp+0x18] [ebp-0xC]
  int v19; // [esp+0x1C] [ebp-0x8]
  int v20; // [esp+0x20] [ebp-0x4]

  v17 = 0;
  v18 = 0;
  v19 = 128;
  v20 = 128;
  RoleSystem_InitDefaultPositions(v15);
  v2 = (int *)&off_59DD18;
  p_m_pParticleData = (void **)&_this->m_pParticleData;
  do
  {
    v4 = (*((int ( **)(void **, _DWORD, int *, Actor *))*p_m_pParticleData + 4))(
           p_m_pParticleData,
           0,
           &v17,
           _this);
    if ( (int)v2 < (int)&off_59DD60 )
    {
      LOBYTE(v4) = g_bSceneLoaded;
      (((UIPushButton *)p_m_pParticleData))->UIPushButton::CreateFromTemplate((void *)*v2, v4);
    }
    else
    {
      v5 = rand();
      v6 = v5 % 0x12;
      v7 = v5 % 0x12;
      LOBYTE(v6) = g_bSceneLoaded;
      (((UIPushButton *)p_m_pParticleData))->UIPushButton::CreateFromTemplate((void *)*(&off_59DD18 + v5 % 0x12), v6);
      p_m_pParticleData[43] = (void *)*((_DWORD *)&_this->m_bDirFlag + 52 * v7);
      p_m_pParticleData[44] = (void *)*((_DWORD *)&_this->m_bDirFlag + 52 * v7 + 1);
    }
    *((float *)p_m_pParticleData + 46) = (float)(rand() % 255);
    ++v2;
    v8 = rand() % 10;
    v9 = v17;
    v10 = v18;
    v16 = v8 + 10;
    v11 = (_DWORD *)(p_m_pParticleData + 38);
    p_m_pParticleData += 52;
    *((float *)p_m_pParticleData - 5) = (double)v16 * 0.1;
    *((_BYTE *)p_m_pParticleData - 16) = 1;
    *v11 = v9;
    v12 = v19;
    v11[1] = v10;
    v13 = v20;
    v11[2] = v12;
    v11[3] = v13;
  }
  while ( (int)v2 < (int)&off_59DD70 );
  return (((RoleCamera *)_this))->RoleCamera::InitParticles();
}

// 0x0044CEC0
int RoleSystem_InitDefaultPositions(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // eax
  int v3; // edx
  int result; // eax

  v2 = (_DWORD *)(v1 + 166);
  v3 = 22;
  do
  {
    v2[1] = 298;
    *v2 = 758;
    v2[4] = 1144881152;
    v2 += 52;
    --v3;
  }
  while ( v3 );
  v1[171] = 256;
  v1[172] = 105;
  v1[223] = 256;
  v1[224] = 64;
  result = 128;
  v1[275] = 256;
  v1[276] = 256;
  v1[483] = 256;
  v1[795] = 256;
  v1[899] = 256;
  v1[951] = 256;
  v1[1055] = 256;
  v1[327] = 128;
  v1[328] = 64;
  v1[379] = 128;
  v1[380] = 64;
  v1[431] = 128;
  v1[432] = 64;
  v1[484] = 128;
  v1[535] = 590;
  v1[536] = 128;
  v1[587] = 128;
  v1[588] = 64;
  v1[639] = 64;
  v1[640] = 32;
  v1[691] = 512;
  v1[692] = 128;
  v1[743] = 128;
  v1[744] = 64;
  v1[796] = 64;
  v1[847] = 128;
  v1[848] = 64;
  v1[900] = 128;
  v1[952] = 128;
  v1[1003] = 512;
  v1[1004] = 128;
  v1[1056] = 128;
  return result;
}

// 0x0044D0B0
int UIEmote_InitParticleSlots(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // esi
  int v3; // ebx
  _DWORD *v4; // edi
  int result; // eax

  v2 = (_DWORD *)v1;
  v3 = 10;
  v4 = (_DWORD *)(v1 + 2142);
  do
  {
    v4 += 52;
    --v3;
    *(v4 - 51) = rand() % 100 + 298;
    *(v4 - 52) = 758;
    *(v4 - 48) = 1144881152;
  }
  while ( v3 );
  result = 128;
  v2[2147] = 128;
  v2[2148] = 64;
  v2[2199] = 128;
  v2[2200] = 64;
  v2[2251] = 128;
  v2[2252] = 128;
  v2[2303] = 256;
  v2[2304] = 256;
  v2[2355] = 256;
  v2[2356] = 64;
  v2[2407] = 64;
  v2[2408] = 32;
  v2[2459] = 256;
  v2[2460] = 128;
  v2[2511] = 512;
  v2[2512] = 128;
  return result;
}

// 0x0044E9F0
int ProjectWorldToScreen()
{
  int v0; // ecx
  int v1; // esi
  int result; // eax
  RoleSystem *v3; // ecx
  int v4; // edi
  int v5; // ebx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // kr00_4
  int v9; // eax
  float v10; // [esp+0xC] [ebp-0x34] BYREF
  float v11; // [esp+0x10] [ebp-0x30] BYREF
  struct gbVec3D pOut; // [esp+0x14] [ebp-0x2C] BYREF
  _DWORD v13[4]; // [esp+0x20] [ebp-0x20] BYREF
  _BYTE a2[16]; // [esp+0x30] [ebp-0x10] BYREF

  v1 = v0;
  result = *(_DWORD *)(v0 + 76);
  if ( result )
  {
    v3 = (RoleSystem *)*(RoleSystem **)(v0 + 2212);
    if ( v3 )
    {
      memset(&pOut, 0, sizeof(pOut));
      (((RoleSystem *)v3))->RoleSystem::GetDirection(&pOut.x);
      if ( *(_DWORD *)(v1 + 76) == 7 )
        pOut.y = pOut.y - 20.0;
      (((gbCamera *)&g_pCameraCtrl->m_fMinDist))->gbCamera::PointWorldToScr(&pOut, &v10, &v11);
      v4 = (__int64)((v10 + 1.0) * (double)g_DrvInfo.width * 0.5);
      v5 = (__int64)((1.0 - v11) * (double)g_DrvInfo.height * 0.5);
      v6 = (_DWORD *)sub_445FE0(a2);
      v7 = (unsigned long)(v6[3] - v6[1]);
      v8 = (unsigned long)(v6[2] - *v6);
      v9 = *(_DWORD *)(v1 + 76);
      v13[1] = v5 - v7;
      v13[0] = v4 - v8 / 2;
      v13[2] = v8 + v13[0];
      v13[3] = v5;
      return (((UIWnd *)(v1 + 164 * v9 + 80)))->UIWnd::sub_445FA0(v13);
    }
  }
  return result;
}

// 0x004517A0
void SetVideoRect(BINK *_this)
{
  _DWORD *v1; // [esp+0x4] [ebp+0x4]
  char v2; // [esp+0x8] [ebp+0x8]

  v1[1] = 552;
  v1[3] = 584;
  *v1 = v2 != 0 ? 760 : 18;
  v1[2] = v2 != 0 ? 792 : 50;
}

// 0x004518FE
void SetPitch(float a1)
{
  JUMPOUT(0x451900);
}

// 0x00451E50
int UITitle_BBTY_CreateFromScript(int nVal)
{
  UIWnd *v1; // ecx
  UIWnd *v2; // esi
  int m_benable; // edx
  unsigned int m_id; // edx
  int capacity; // edx
  void *v6; // eax
  int v7; // edx
  void *v8; // eax
  void **v9; // ebx
  UIPushButton *p_m_rect; // edi
  int v11; // ebp
  int result; // eax
  tagRECT pRect; // [esp+0x48] [ebp-0x20] BYREF
  _DWORD a2[4]; // [esp+0x58] [ebp-0x10] BYREF

  pRect.right = g_DrvInfo.width;
  v2 = (UIWnd *)v1;
  pRect.left = g_DrvInfo.width - 71;
  pRect.top = 5;
  pRect.bottom = 95;
  (((UIWnd *)v1))->UIWnd::Create(0, &pRect, nVal);
  m_benable = v2[14].m_benable;
  pRect.top = 0;
  pRect.left = 0;
  pRect.right = 71;
  pRect.bottom = 90;
  (*(void ( **)(int *, int, tagRECT *, UIWnd *))(m_benable + 16))(&v2[14].m_benable, 1, &pRect, v2);
  (((UIPushButton *)&v2[14].m_benable))->UIPushButton::CreateFromTemplate("ui\\scene\\face\\bk.tga", 0);
  m_id = v2[8].m_id;
  pRect.left = 15;
  pRect.right = 79;
  pRect.top = 4;
  pRect.bottom = 68;
  (*(void ( **)(unsigned int *, int, tagRECT *, UIWnd *))(m_id + 16))(&v2[8].m_id, 2, &pRect, v2);
  (*(void ( **)(LONG *, int, tagRECT *, UIWnd *))(v2[10].m_rect.bottom + 16))(
    &v2[10].m_rect.bottom,
    3,
    &pRect,
    v2);
  (*(void ( **)(int *, int, tagRECT *, UIWnd *))(v2[12].m_childs.m_nSize + 16))(
    &v2[12].m_childs.m_nSize,
    3,
    &pRect,
    v2);
  UITitle_BBTY_SetRemarkTextures(0);
  capacity = v2[4].m_childs.capacity;
  pRect.left = 2;
  pRect.top = 1;
  pRect.right = 52;
  pRect.bottom = 44;
  (*(void ( **)(int *, _DWORD, tagRECT *, UIWnd *))(capacity + 16))(
    &v2[4].m_childs.capacity,
    0,
    &pRect,
    v2);
  v6 = (void *)sub_445FE0(a2);
  sub_43FEC0(v6);
  (((UIScene *)&v2[4].m_childs.capacity))->UIScene::GetChildAt();
  v7 = (int)v2[1];
  pRect.left = 4;
  pRect.top = 48;
  pRect.right = 47;
  pRect.bottom = 82;
  (*(void ( **)(UIWnd *, _DWORD, tagRECT *, UIWnd *))(v7 + 16))(v2 + 1, 0, &pRect, v2);
  v8 = (void *)sub_445FE0(a2);
  sub_43FEC0(v8);
  (((UIScene *)&v2[1]))->UIScene::GetChildAt();
  (((UIScrollBar *)&v2[4].m_childs.capacity))->UIScrollBar::SetRange(10.0);
  (((UIProgressBar *)&v2[4].m_childs.capacity))->UIProgressBar::FindChildByName(10.0);
  (((UIScrollBar *)&v2[1]))->UIScrollBar::SetRange(10.0);
  (((UIProgressBar *)&v2[1]))->UIProgressBar::FindChildByName(10.0);
  pRect.left = 47;
  pRect.right = 79;
  pRect.top = 5;
  pRect.bottom = 69;
  a2[0] = (unsigned long)"ui\\scene\\face\\bx.tga";
  a2[1] = (unsigned long)"ui\\scene\\face\\tm.tga";
  a2[2] = (unsigned long)"ui\\scene\\face\\sy.tga";
  a2[3] = (unsigned long)"ui\\scene\\face\\jj.tga";
  v9 = (void **)a2;
  p_m_rect = (UIPushButton *)&v2[17].m_rect;
  v11 = 4;
  do
  {
    (*(void ( **)(UIPushButton *, _DWORD, tagRECT *, UIWnd *))(*(_DWORD *)((UIWnd *)p_m_rect) + 16))(
      p_m_rect,
      0,
      &pRect,
      v2);
    (((UIPushButton *)p_m_rect))->UIPushButton::CreateFromTemplate(*v9, 0);
    result = (**(int ( ***)(UIPushButton *, _DWORD))((UIWnd *)p_m_rect))((UIPushButton *)(p_m_rect), (_DWORD)(0));
    ++v9;
    p_m_rect = (UIPushButton *)((char *)p_m_rect + 152);
    --v11;
  }
  while ( v11 );
  return result;
}

// 0x004524B0
int UITitle_BBTY_SetRemarkTextures(int nVal)
{
  int v1; // ecx
  int v2; // esi
  UIPushButton *v3; // edi
  int result; // eax
  char Buffer[260]; // [esp+0xC] [ebp-0x104] BYREF

  v2 = 0;
  v3 = (UIPushButton *)(v1 + 556);
  do
  {
    sprintf(Buffer, "ui\\scene\\face\\face%d\\face%02d.tga", nVal, v2);
    (((UIPushButton *)v3))->UIPushButton::LoadTextureByName(Buffer, 0);
    ++v2;
    v3 = (UIPushButton *)((char *)v3 + 152);
  }
  while ( v2 < 3 );
  return result;
}

// 0x00452580
int todo_ctor(int _this)
{
  int v3; // [esp+0x0] [ebp-0x14]

  ((UIListBox *)_this)->UIListBox::UIListBox();
  UIAnimateCtrlEX_UIAnimateCtrlEX(v3);
  ((UITitle_BBTY *)(_this + 1084))->UITitle_BBTY::UITitle_BBTY();
  return _this;
}

// 0x00452790
int UIAnimateCtrlEX_UIAnimateCtrlEX(int nVal)
{
  int v1; // ecx
  int v2; // esi

  v2 = v1;
  ClearSubArraySlot();
  NameSys::GetSys();
  (((UIFrameContainer *)(v2 + 412)))->UIFrameContainer::ResetContainerState();
  (((CCBResultWindow *)(v2 + 564)))->CCBResultWindow::ctor();
  (((UITextArea *)(v2 + 748)))->UITextArea::InitAfterClear();
  ZeroInitSelf68();
  *(_DWORD *)(v2 + 1008) = 0;
  return v2;
}

// 0x00452850
int UIAnimateCtrlEX__UIAnimateCtrlEX(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax

  v2 = v1;
  (((UIWnd *)(v1 + 940)))->MoveWindow();
  UITextArea_Destroy();
  (((UIFrameWnd *)(v2 + 564)))->UIFrameWnd::~UIFrameWnd();
  (((UIFrameContainer *)(v2 + 412)))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)(v2 + 68)))->UICaption::Destroy2();
  (((UIWnd *)v2))->UIWnd::_UIWnd();
  return result;
}

// 0x004544F0
int CCBUIPanel_UpdateButtonVisibility(int nVal)
{
  int v1; // ecx
  int v2; // esi

  v2 = v1;
  sub_445E50(v1 + 664);
  sub_445E50(v2 + 1040);
  return sub_445E50(v2 + 1416);
}

// 0x00454980
TaskBookUI * scalar_dtor_0_0(TaskBookUI *Block, char a2)
{
  (((TaskBookUI *)Block))->TaskBookUI::_TaskBookUI_4ba0();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00454CA0
int TaskBookUI_CreateEntry(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int refreshed; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // edx
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  float v21; // st7
  __int64 v22; // rax
  int v23; // ebp
  __int64 v24; // rax
  int v25; // ecx
  int v26; // ecx
  int v27; // eax
  float v28; // st7
  int v29; // eax
  int v30; // eax
  float v31; // st7
  int v32; // eax
  int v33; // ecx
  int v34; // ecx
  int *v35; // eax
  float fVal; // [esp+0x90] [ebp-0x54]
  PlayerItem *v38; // [esp+0x94] [ebp-0x50]
  PlayerItem *v39; // [esp+0x98] [ebp-0x4C]
  int v40; // [esp+A4h] [ebp-0x40] BYREF
  int v41; // [esp+A8h] [ebp-0x3C]
  int v42; // [esp+ACh] [ebp-0x38]
  int v43; // [esp+B0h] [ebp-0x34]
  int v44; // [esp+B4h] [ebp-0x30] BYREF
  int v45; // [esp+B8h] [ebp-0x2C]
  int v46; // [esp+BCh] [ebp-0x28]
  int v47; // [esp+C0h] [ebp-0x24]
  int v48; // [esp+C4h] [ebp-0x20]
  int v49; // [esp+C8h] [ebp-0x1C]
  int v50; // [esp+CCh] [ebp-0x18]
  int v51; // [esp+D0h] [ebp-0x14]
  _DWORD v52[4]; // [esp+D4h] [ebp-0x10] BYREF

  v2 = v1;
  v3 = v1 + 72;
  (((UIListBox *)v1))->UIListBox::SetSelTexture(0, *(_DWORD *)(v1 + 72), *(_DWORD *)(v1 + 76), *(_DWORD *)(v1 + 80), *(_DWORD *)(v1 + 84));
  v4 = *(_DWORD *)(v2 + 360);
  *(_DWORD *)(v2 + 133100) = nVal;
  v5 = (*(int ( **)(int, _DWORD, int, int))(v4 + 16))(v2 + 360, 0, v3, v2);
  LOBYTE(v5) = g_bEffectEnabled;
  (((UIPushButton *)(v2 + 360)))->UIPushButton::CreateFromTemplate((void *)off_5B087C, v5);
  v6 = *(_DWORD *)(v2 + 129052);
  v41 = 46;
  v40 = 108;
  v42 = 692;
  v43 = 66;
  (*(void ( **)(int, _DWORD, int *, int))(v6 + 16))(v2 + 129052, 0, &v40, v2);
  LOBYTE(v7) = g_bEffectEnabled;
  (((UIPushButton *)(v2 + 129052)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\TopBar.tga", v7);
  v8 = *(_DWORD *)(v2 + 129204);
  v41 = 526;
  v40 = 109;
  v42 = 693;
  v43 = 563;
  (*(void ( **)(int, _DWORD, int *, int))(v8 + 16))(v2 + 129204, 0, &v40, v2);
  LOBYTE(v9) = g_bEffectEnabled;
  (((UIPushButton *)(v2 + 129204)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\BottomBar.tga", v9);
  LOBYTE(v10) = g_bEffectEnabled;
  v11 = *(_DWORD *)(v2 + 512);
  v52[1] = 537;
  v52[0] = 745;
  v52[2] = 801;
  v52[3] = 599;
  (*(void ( **)(int, int, _DWORD *, int, char *, _DWORD, int))(v11 + 28))(
    v2 + 512,
    209,
    (_DWORD *)(v52),
    v2,
    off_5B0950[0],
    0,
    v10);
  refreshed = (((TaskBookUI *)v2))->TaskBookUI::RefreshTaskList();
  LOBYTE(refreshed) = g_bEffectEnabled;
  v13 = *(_DWORD *)(v2 + 129356);
  v45 = 62;
  v44 = 702;
  v46 = 727;
  v47 = 90;
  v14 = (*(int ( **)(int, int *, int *, int, char *, _DWORD, int))(v13 + 28))(
          v2 + 129356,
          &byte_A00702,
          &v44,
          v2,
          "UI\\GameMainUI\\System\\pgup",
          0,
          refreshed);
  LOBYTE(v14) = g_bEffectEnabled;
  v15 = *(_DWORD *)(v2 + 129700);
  v45 = 527;
  v44 = 702;
  v46 = 727;
  v47 = 555;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD, int))(v15 + 28))(
    v2 + 129700,
    &byte_A00701,
    &v44,
    v2,
    "UI\\GameMainUI\\System\\pgdw",
    0,
    v14);
  v16 = *(_DWORD *)(v2 + 130060);
  *(_DWORD *)(v2 + 130048) = 90;
  *(_DWORD *)(v2 + 130052) = 722;
  *(_DWORD *)(v2 + 130044) = 708;
  *(_DWORD *)(v2 + 130056) = 527;
  LOBYTE(v17) = g_bEffectEnabled;
  (*(void ( **)(int, ARC_PlayerAtt *, int, int, char *, int))(v16 + 28))(
    v2 + 130060,
    &g_PlayerAttBuffer2,
    v2 + 130044,
    v2,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    v17);
  (((UIScene *)(v2 + 130060)))->UIScene::SetTexture("UI\\GameMainUI\\System\\hdt.tga", 0);
  (((UIBigMap *)(v2 + 130060)))->UIBigMap::UpdateWindowPos(26, 28);
  fill((PlayerItem *)1, v38, v39);
  *(_DWORD *)(v2 + 130316) = 1096810496;
  *(_DWORD *)(v2 + 130320) = -1050673152;
  v18 = *(_DWORD *)(v2 + 130324);
  *(_DWORD *)(v2 + 130304) = 20;
  if ( !v18 )
  {
    v29 = *(_DWORD *)(v2 + 130328);
    if ( v29 )
    {
      if ( v29 != 1 )
        goto LABEL_13;
      v20 = *(_DWORD *)(v2 + 130156);
      nVal = *(_DWORD *)(v2 + 130200) - v20 - 20;
      v23 = (__int64)((double)nVal + *(float *)(v2 + 130316));
      v30 = *(_DWORD *)(v2 + 130152);
      v31 = (float)*(int *)(v2 + 130204) - *(float *)(v2 + 130296);
      *(_DWORD *)(v2 + 130184) = v23;
      nVal = v30 / 2;
      v28 = v31 - (float)(v30 / 2) - *(float *)(v2 + 130312);
    }
    else
    {
      v20 = *(_DWORD *)(v2 + 130156);
      nVal = *(_DWORD *)(v2 + 130200) - v20 - 20;
      v23 = (__int64)((double)nVal + *(float *)(v2 + 130316));
      v32 = *(_DWORD *)(v2 + 130152);
      v33 = *(_DWORD *)(v2 + 130196);
      *(_DWORD *)(v2 + 130184) = v23;
      nVal = v33 - v32 / 2;
      v28 = (float)nVal + *(float *)(v2 + 130308) + *(float *)(v2 + 130296);
    }
LABEL_11:
    v34 = *(_DWORD *)(v2 + 130152);
    *(_DWORD *)(v2 + 130180) = (__int64)v28;
    *(_DWORD *)(v2 + 130188) = v34 + (__int64)v28;
    goto LABEL_12;
  }
  if ( v18 != 1 )
    goto LABEL_13;
  v19 = *(_DWORD *)(v2 + 130328);
  if ( !v19 )
  {
    v20 = *(_DWORD *)(v2 + 130156);
    nVal = *(_DWORD *)(v2 + 130200) - v20 / 2;
    v26 = *(_DWORD *)(v2 + 130196);
    v23 = (__int64)((double)nVal + *(float *)(v2 + 130316) + *(float *)(v2 + 130296));
    v27 = *(_DWORD *)(v2 + 130152);
    *(_DWORD *)(v2 + 130184) = v23;
    nVal = v26 - v27 - 20;
    v28 = (float)nVal + *(float *)(v2 + 130308);
    goto LABEL_11;
  }
  if ( v19 == 1 )
  {
    v20 = *(_DWORD *)(v2 + 130156);
    v21 = (float)*(int *)(v2 + 130208) - *(float *)(v2 + 130296);
    nVal = v20 / 2;
    v22 = (__int64)(v21 - (double)(v20 / 2) - *(float *)(v2 + 130320));
    HIDWORD(v22) = *(_DWORD *)(v2 + 130204);
    v23 = (__int64)(v21 - (double)(v20 / 2) - *(float *)(v2 + 130320));
    *(_DWORD *)(v2 + 130184) = v22;
    nVal = HIDWORD(v22) + 20;
    v24 = (__int64)((double)(HIDWORD(v22) + 20) - *(float *)(v2 + 130296) - *(float *)(v2 + 130312));
    v25 = *(_DWORD *)(v2 + 130152);
    *(_DWORD *)(v2 + 130180) = v24;
    *(_DWORD *)(v2 + 130188) = v24 + v25;
LABEL_12:
    *(_DWORD *)(v2 + 130192) = v20 + v23;
  }
LABEL_13:
  ((gbColorQuad *)&nVal)->gbColorQuad::gbColorQuad(0, 0, 0, 0);
  (((UIScene *)(v2 + 130060)))->UIScene::SetParam(*v35);
  nVal = 32 * *(_DWORD *)(v2 + 130340) - 28;
  fVal = (float)nVal;
  (((UIScene *)(v2 + 130060)))->UIScene::UpdateLayout(fVal);
  v49 = 200;
  v48 = 250;
  v50 = 450;
  v51 = 300;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 130364));
  (((UIItem *)(v2 + 130364)))->UIItem::SetData(219);
  v49 = 200;
  v48 = 300;
  v50 = 500;
  v51 = 300;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 131732));
  return (int)(((UIItem *)(v2 + 131732)))->UIItem::SetData(219);
}

// 0x004554D0
int TaskBookUI_AdvancePage(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // eax
  int v4; // esi
  int v5; // ebx
  UIPushButton *v6; // ebp
  int v7; // ecx
  int v9; // [esp+0x0] [ebp-0x20]
  int v10; // [esp+0x18] [ebp-0x8]

  v2 = v1;
  v3 = 64;
  v4 = *(_DWORD *)(v1 + 130340) + 64;
  v10 = *(_DWORD *)(v1 + 130344) + 80;
  v5 = 0;
  v6 = (UIPushButton *)(v1 + 1404);
  do
  {
    (((ChoseCompose *)v2))->ChoseCompose::LayoutItems(v5, 80, v3, v10, v4);
    sub_445E50((int)&v6[-2]);
    LOBYTE(v7) = g_bEffectEnabled;
    (((UIPushButton *)v6))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\dq.tga", v7);
    v3 = v4;
    v4 += *(_DWORD *)(v2 + 130340);
    ++v5;
    v6 = (UIPushButton *)((char *)v6 + 3560);
  }
  while ( v5 < 36 );
  sub_445E50(v2 + 908);
  return TaskBookUI_RefreshElements(v9);
}

// 0x00455790
int TaskBookUI_RefreshElements(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  void (***v3)(_DWORD, _DWORD); // esi
  void (***v4)(_DWORD, _DWORD); // edi
  int v5; // ebx
  int result; // eax
  int v7; // ecx
  void ( ***v8)(_DWORD, int); // edi
  int v9; // ebp
  void (***v10)(_DWORD, _DWORD); // esi
  void (***v11)(_DWORD, _DWORD); // ecx
  void ( ***v12)(_DWORD, int); // ecx
  int v13; // ebp
  void (***v14)(_DWORD, _DWORD); // esi
  void ( **v15)(int); // eax
  int v16; // ebp
  void (***v17)(_DWORD); // esi
  void (**v18)((_DWORD)(_DWORD)); // edx
  void (***v19)(_DWORD, _DWORD); // ecx
  void (**v20)((_DWORD)(_DWORD)); // eax
  int v21; // [esp+0x48] [ebp-0x18]
  int v22; // [esp+0x58] [ebp-0x8]
  int v23; // [esp+0x5C] [ebp-0x4]

  v22 = v1;
  v2 = 0;
  v3 = (void ( ***)(_DWORD, _DWORD))(v1 + 1252);
  do
  {
    (**(v3 - 86))(v3 - 86, 0);
    (**v3)((_DWORD)(v3), (_DWORD)(0));
    (*v3[38])(v3 + 38, 0);
    v4 = v3 + 76;
    v5 = 5;
    do
    {
      (*v4[190])(v4 + 190, 0);
      (**v4)((_DWORD)(v4), (_DWORD)(0));
      (*v4[458])(v4 + 458, 0);
      v4 += 38;
      --v5;
    }
    while ( v5 );
    (*v3[458])(v3 + 458, 0);
    (*v3[496])(v3 + 496, 0);
    (*v3[724])(v3 + 724, 0);
    (*v3[762])(v3 + 762, 0);
    result = v22;
    ++v2;
    v3 += 890;
    *(_BYTE *)(v22 + v2 + 855) = 0;
  }
  while ( v2 < 36 );
  v7 = *(_DWORD *)(v22 + 130348);
  v23 = v7;
  if ( !__OFSUB__(v7, v7 + 5) )
  {
    v8 = (void ( ***)(_DWORD, int))(v22 + 3560 * v7 + 1252);
    do
    {
      (**(v8 - 86))(v8 - 86, 1);
      (**v8)((_DWORD)((_DWORD)(v8)), (int)(1));
      (*v8[38])(v8 + 38, 1);
      v9 = 0;
      v10 = v8 + 76;
      do
      {
        v11 = v10 + 190;
        if ( *((_BYTE *)v8 + v9 + 1824) )
        {
          (**v11)((_DWORD)(v11), (_DWORD)(0));
          (**v10)((_DWORD)(v10), (_DWORD)(0));
          (*v10[458])(v10 + 458, 1);
        }
        else
        {
          (**v11)((_DWORD)(v11), (_DWORD)(0));
          (**v10)((_DWORD)(v10), (_DWORD)(0));
          (*v10[458])(v10 + 458, 0);
        }
        ++v9;
        v10 += 38;
      }
      while ( v9 < 5 );
      (*v8[458])(v8 + 458, 1);
      (*v8[496])(v8 + 496, 1);
      v12 = v8 + 724;
      if ( *(_DWORD *)(v22 + 130352) == v23 )
      {
        (**v12)((_DWORD)((_DWORD)(v12)), (int)(1));
        v13 = 0;
        v14 = v8 + 76;
        do
        {
          v15 = (void ( **)(int))v14[190];
          if ( *((_BYTE *)v8 + v13 + 1824) )
            (*v15)(1);
          else
            (*v15)(0);
          (**v14)((_DWORD)(v14), (_DWORD)(0));
          ++v13;
          v14 += 38;
        }
        while ( v13 < 5 );
      }
      else
      {
        (**v12)((_DWORD)((_DWORD)(v12)), (int)(0));
        v16 = 0;
        v17 = (void ( ***)(_DWORD))(v8 + 76);
        do
        {
          v18 = v17[190];
          v19 = (void ( ***)(_DWORD, _DWORD))(v17 + 190);
          if ( *((_BYTE *)v8 + v16 + 1824) )
          {
            ((void ( *)(void ( ***)(_DWORD, _DWORD), _DWORD, int))*v18)(v19, 0, v21);
            v20 = *v17;
            v21 = 1;
          }
          else
          {
            ((void ( *)(void ( ***)(_DWORD, _DWORD), _DWORD, int))*v18)(v19, 0, v21);
            v20 = *v17;
            v21 = 0;
          }
          (*v20)(v17);
          ++v16;
          v17 += 38;
        }
        while ( v16 < 5 );
      }
      (*v8[762])(v8 + 762, 1);
      v8 += 890;
      *(_BYTE *)(v22 + v23 + 856) = 1;
      result = v23 + 1;
      v23 = result;
    }
    while ( result < *(_DWORD *)(v22 + 130348) + 5 );
  }
  return result;
}

// 0x00455A20
int TaskBookUI_ScrollUp(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // eax
  CScreenMode *v4; // eax
  int result; // eax
  int v6; // ebx
  int *v7; // esi
  int v8; // eax
  CScreenMode *Instance; // eax
  const void *v10; // [esp-0x4] [ebp-0x14]
  const void *v11; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]
  int v13; // [esp+0x4] [ebp-0xC]
  int nVala; // [esp+0x14] [ebp+0x4]

  v2 = v1;
  ++*(_DWORD *)(v1 + 130348);
  if ( (_BYTE)nVal )
  {
    v3 = *(_DWORD *)(v1 + 130336) + 1;
    *(_DWORD *)(v1 + 130336) = v3;
    if ( v3 > 32 )
      *(_DWORD *)(v1 + 130336) = 32;
    nVala = *(_DWORD *)(v1 + 130336) * *(_DWORD *)(v1 + 130340) - 28;
    *(_DWORD *)(v1 + 130332) = nVala;
    fProgress = (float)nVala;
    (((CScreenMode *)(v1 + 130060)))->CScreenMode::SetProgress(fProgress);
  }
  if ( *(int *)(v2 + 130348) <= 31 )
  {
    TaskBookUI_RefreshElements(v13);
    v6 = 0;
    v7 = (int *)(v2 + 896);
    do
    {
      v8 = (unsigned long)(*v7 - *(_DWORD *)(v2 + 130340));
      *v7 = v8;
      v7[2] = v8 + *(_DWORD *)(v2 + 130340);
      (((ChoseCompose *)v2))->ChoseCompose::LayoutItems(v6++, *(v7 - 1), *v7, v7[1], v7[2]);
      v7 += 890;
    }
    while ( v6 < 36 );
    v11 = off_5AE3A8;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v11, 1);
    LOBYTE(result) = 1;
  }
  else
  {
    *(_DWORD *)(v2 + 130348) = 31;
    v10 = off_5AE38C;
    v4 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v4))->CScreenMode::AudioSetPosition(v10, 1);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x00455B30
int TaskBookUI_ScrollDown(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  CScreenMode *v6; // eax
  int result; // eax
  int *v8; // edi
  int v9; // eax
  CScreenMode *Instance; // eax
  const void *v11; // [esp-0x4] [ebp-0x14]
  const void *v12; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]
  int v14; // [esp+0x4] [ebp-0xC]

  v2 = v1;
  v3 = 0;
  --*(_DWORD *)(v1 + 130348);
  if ( (_BYTE)nVal )
  {
    v4 = *(_DWORD *)(v1 + 130336) - 1;
    *(_DWORD *)(v1 + 130336) = v4;
    if ( v4 <= 0 )
      *(_DWORD *)(v1 + 130336) = 0;
    v5 = *(_DWORD *)(v1 + 130336) * *(_DWORD *)(v1 + 130340) - 28;
    *(_DWORD *)(v1 + 130332) = v5;
    if ( v5 < 0 )
      *(_DWORD *)(v1 + 130332) = 0;
    fProgress = (float)*(int *)(v1 + 130332);
    (((CScreenMode *)(v1 + 130060)))->CScreenMode::SetProgress(fProgress);
  }
  if ( *(int *)(v2 + 130348) >= 0 )
  {
    TaskBookUI_RefreshElements(v14);
    v8 = (int *)(v2 + 896);
    do
    {
      v9 = *(_DWORD *)(v2 + 130340) + *v8;
      *v8 = v9;
      v8[2] = v9 + *(_DWORD *)(v2 + 130340);
      (((ChoseCompose *)v2))->ChoseCompose::LayoutItems(v3++, *(v8 - 1), *v8, v8[1], v8[2]);
      v8 += 890;
    }
    while ( v3 < 36 );
    v12 = off_5AE3A8;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v12, 1);
    LOBYTE(result) = 1;
  }
  else
  {
    *(_DWORD *)(v2 + 130348) = 0;
    v11 = off_5AE38C;
    v6 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v6))->CScreenMode::AudioSetPosition(v11, 1);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x00455C40
int TaskBookUI_HandleInput(int nVal)
{
  int result; // eax
  int v2; // ecx
  int v3; // esi
  char *v4; // ebp
  const RECT *i; // edi
  int v6; // ebx
  int j; // edi
  int v8; // eax
  void (***v9)(_DWORD, _DWORD); // edi
  int v10; // ebx
  int v11; // ebx
  int k; // edi
  int v13; // eax
  void *v14; // ecx
  Actor *SaveDataManager; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v17; // eax
  const void *v18; // [esp-0x8] [ebp-0x70]
  const void *v19; // [esp-0x8] [ebp-0x70]
  POINT pt; // [esp+0x10] [ebp-0x58] BYREF

  v3 = v2;
  LOBYTE(result) = *(_BYTE *)(v2 + 131705);
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = *(_BYTE *)(v2 + 133073);
    if ( !(_BYTE)result )
    {
      result = (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
      v4 = 0;
      for ( i = (const RECT *)(v3 + 892); ; i = (const RECT *)((char *)i + 3560) )
      {
        LOBYTE(result) = (unsigned long)v4[v3 + 856];
        if ( (_BYTE)result )
        {
          result = PtInRect(i, pt);
          if ( result )
          {
            if ( g_Input.KeyInfo[0].PressTime == 1 )
            {
              result = g_Input.KeyInfo[0].Data & 0xF;
              if ( result == 1 )
              {
                if ( *(_BYTE *)(v3 + *(_DWORD *)(v3 + 130352) + 856) )
                {
                  v6 = 0;
                  for ( j = 0; j < 760; j += 152 )
                  {
                    v8 = 3560 * *(_DWORD *)(v3 + 130352);
                    if ( *(_BYTE *)(v8 + v6 + v3 + 3076) )
                    {
                      (**(void ( ***)(int, int))(j + v8 + v3 + 1556))((int)(j + v8 + v3 + 1556), (int)(1));
                      (**(void ( ***)(int, _DWORD))(j + 3560 * *(_DWORD *)(v3 + 130352) + v3 + 2316))((int)(j + 3560 * *(_DWORD *)(v3 + 130352) + v3 + 2316), (_DWORD)(0));
                    }
                    ++v6;
                  }
                }
                *(_DWORD *)(v3 + 130352) = (_DWORD)v4;
                v9 = (void ( ***)(_DWORD, _DWORD))(v3 + 4148);
                v10 = 36;
                do
                {
                  sub_445E50((int)(v9 - 810));
                  (**v9)((_DWORD)(v9), (_DWORD)(0));
                  v9 += 890;
                  --v10;
                }
                while ( v10 );
                sub_445E50(v3 + 3560 * *(_DWORD *)(v3 + 130352) + 908);
                (**(void ( ***)(int, int))(v3 + 3560 * *(_DWORD *)(v3 + 130352) + 4148))((int)(v3 + 3560 * *(_DWORD *)(v3 + 130352) + 4148), (int)(1));
                v11 = 0;
                for ( k = 0; k < 760; k += 152 )
                {
                  v13 = 3560 * *(_DWORD *)(v3 + 130352);
                  if ( *(_BYTE *)(v13 + v11 + v3 + 3076) )
                  {
                    (**(void ( ***)(int, _DWORD))(k + v13 + v3 + 1556))((int)(k + v13 + v3 + 1556), (_DWORD)(0));
                    (**(void ( ***)(int, int))(k + 3560 * *(_DWORD *)(v3 + 130352) + v3 + 2316))((int)(k + 3560 * *(_DWORD *)(v3 + 130352) + v3 + 2316), (int)(1));
                  }
                  ++v11;
                }
                v14 = (void *)off_5AE380;
                goto LABEL_26;
              }
              if ( result == 2 )
                break;
            }
          }
        }
        if ( (int)++v4 >= 36 )
          return result;
      }
      *(_DWORD *)(v3 + 130356) = (_DWORD)v4;
      SaveDataManager = (Actor *)GetSaveDataManager();
      if ( (((Actor *)SaveDataManager))->Actor::LoadSaveData(v4) )
      {
        sprintf((char *const)(v3 + 104), "\\n      %s", (const char *)&dword_DD4E3C);
        SetEnable((UICaption *)(v3 + 130820));
        (((UIRoleSelect *)(v3 + 130364)))->UIRoleSelect::SetByte(0);
        (((GRPinput *)&g_Input))->GRPinput::Reset();
        v18 = (const void *)off_5AE388;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v18, 1);
        return result;
      }
      sprintf((char *const)(v3 + 104), "\\n %s", (const char *)&dword_DD4F3C);
      SetEnable((UICaption *)(v3 + 132188));
      (((UIRoleSelect *)(v3 + 131732)))->UIRoleSelect::SetByte(1);
      (((GRPinput *)&g_Input))->GRPinput::Reset();
      v14 = (void *)off_5AE388;
LABEL_26:
      v19 = v14;
      v17 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v17))->CScreenMode::AudioSetPosition(v19, 1);
    }
  }
  return result;
}

// 0x00455F20
int TaskBookUI_SaveData(int nVal)
{
  int v1; // ecx
  char *v2; // ebp
  int v3; // edi
  Actor *SaveDataManager; // eax
  int v5; // esi
  int i; // ebp
  int v7; // eax
  int v8; // eax
  __int64 v9; // rax
  int v10; // esi
  int v11; // ebx
  int v12; // ebp
  int v13; // esi
  int v14; // ecx
  int v15; // ecx
  int result; // eax
  int v17; // [esp-0x4] [ebp-0x170]
  int v18; // [esp+0x10] [ebp-0x15C]
  _BYTE *v19; // [esp+0x14] [ebp-0x158]
  float v20; // [esp+0x18] [ebp-0x154]
  char v21[5]; // [esp+0x1C] [ebp-0x150]
  char v22[67]; // [esp+0x21] [ebp-0x14B] BYREF
  int v23; // [esp+0x64] [ebp-0x108]
  char Buffer[257]; // [esp+0x68] [ebp-0x104] BYREF
  __int16 v25; // [esp+0x169] [ebp-0x3]
  char v26; // [esp+0x16B] [ebp-0x1]

  memset(Buffer, 0, sizeof(Buffer));
  v2 = 0;
  v25 = 0;
  v26 = 0;
  v18 = 0;
  v3 = v1 + 3084;
  while ( 1 )
  {
    SaveDataManager = (Actor *)GetSaveDataManager();
    if ( (((Actor *)SaveDataManager))->Actor::LoadSaveData(v2) )
    {
      v9 = (__int64)v20;
      v10 = (int)v9 / 3600;
      v11 = (int)v9 / 60 % 60;
      v17 = (int)v9 % 60;
      if ( (int)v9 / 3600 < 100 )
        sprintf(Buffer, "%s %02d:%02d:%02d", &dword_DC643C, v10, v11, v17);
      else
        sprintf(Buffer, "%s %03d:%02d:%02d", &dword_DC643C, v10, v11, v17);
      SetEnable((UICaption *)v3);
      sprintf(Buffer, "%s %d", (const char *)&dword_DC633C, v23);
      SetEnable((UICaption *)(v3 + 152));
      sprintf(Buffer, "%s %s", (const char *)&dword_DD933C, v22);
      SetEnable((UICaption *)(v3 + 1216));
      sprintf(Buffer, "Save\\PAL3_%04d.JPG", v2);
      (((UIFrameWnd *)(v3 + 1064)))->UIFrameWnd::SetTextureByID((int)Buffer);
      (**(void ( ***)(int, int))(v3 + 1064))((int)(v3 + 1064), (int)(1));
      v12 = 0;
      v13 = v3 - 768;
      do
      {
        if ( v21[v12] )
        {
          *(_BYTE *)(v3 + v12 - 8) = 1;
          (**(void ( ***)(int, _DWORD))v13)((int)(v13), (_DWORD)(0));
          LOBYTE(v14) = g_bEffectEnabled;
          (((UIPushButton *)v13))->UIPushButton::CreateFromTemplate((void *)(0x56B24C)[v12], v14);
          (**(void ( ***)(int, int))(v13 - 760))((int)(v13 - 760), (int)(1));
          LOBYTE(v15) = g_bEffectEnabled;
          (((UIPushButton *)(v13 - 760)))->UIPushButton::CreateFromTemplate((void *)(0x56B260)[v12], v15);
          SetEnable((UICaption *)(v13 + 1072));
        }
        else
        {
          (**(void ( ***)(int, _DWORD))v13)((int)(v13), (_DWORD)(0));
          (**(void ( ***)(int, _DWORD))(v13 - 760))((int)(v13 - 760), (_DWORD)(0));
          *(_BYTE *)(v3 + v12 - 8) = 0;
        }
        ++v12;
        v13 += 152;
      }
      while ( v12 < 5 );
    }
    else
    {
      SetEnable((UICaption *)v3);
      SetEnable((UICaption *)(v3 + 152));
      SetEnable((UICaption *)(v3 + 1216));
      (**(void ( ***)(int, _DWORD))(v3 + 1064))((int)(v3 + 1064), (_DWORD)(0));
      v5 = v3 - 1528;
      v19 = (_BYTE *)(v3 - 8);
      for ( i = 0; i < 5; ++i )
      {
        *v19 = 0;
        v7 = (**(int ( ***)(int, _DWORD))(v5 + 760))((int)(v5 + 760), (_DWORD)(0));
        LOBYTE(v7) = g_bEffectEnabled;
        (((UIPushButton *)(v5 + 760)))->UIPushButton::CreateFromTemplate((void *)(0x56B24C)[i], v7);
        v8 = (**(int ( ***)(int, _DWORD))v5)((int)(v5), (_DWORD)(0));
        LOBYTE(v8) = g_bEffectEnabled;
        (((UIPushButton *)v5))->UIPushButton::CreateFromTemplate((void *)(0x56B260)[i], v8);
        SetEnable((UICaption *)(v5 + 1832));
        v5 += 152;
        ++v19;
      }
    }
    v3 += 3560;
    result = ++v18;
    if ( v18 >= 36 )
      break;
    v2 = (char *)v18;
  }
  return result;
}

// 0x00456500
int LineupUI_OnMsgHandleNav(int nVal)
{
  CScreenMode *v1; // ecx
  CScreenMode *v2; // esi
  CScreenMode *Instance; // eax
  const void *v5; // [esp-0x8] [ebp-0xC]
  int v6; // [esp+0x0] [ebp-0x4]
  int v7; // [esp+0x0] [ebp-0x4]
  int a3; // [esp+0xC] [ebp+0x8]

  v2 = (CScreenMode *)v1;
  if ( v1[23].m_RoleDialog.m_needscriptdel )
    return 1;
  (((TaskBookUI *)v1))->TaskBookUI::HandleNavigation();
  (((CScreenMode *)v2))->CScreenMode::GetMouseScroll();
  TaskBookUI_HandleInput(v6);
  if ( UIParabolaCtrl_GetState(v7) )
    return (((SceneObj *)v2))->SceneObj::Update(nVal, a3);
  PAL3::WriteRegistryKey("SOFTWARE\\SOFTSTAR\\PAL3_SAVE", (DWORD)"SEEK", v2[23].m_RoleDialog.m_nTodo_000);
  v2[23].m_RoleDialog.m_needscriptdel = (gbImage2D *)1;
  v5 = off_5AE3C4;
  Instance = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v5, 1);
  return 1;
}

// 0x00456670
BOOL ShowMessageBox(const char *szMessage, const char *szCaption)
{
  BOOL result; // eax

  if ( !szMessage )
    return 1;
  FormatMessageA(0x1300u, 0, (DWORD)szMessage, 0, (LPSTR)&szMessage, 0, 0);
  MessageBoxA(0, szMessage, szCaption, 0);
  result = (BOOL)LocalFree((HLOCAL)szMessage);
  return 0;
}

// 0x004566C0
int TaskBookUI_ValidateEntries(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // esi
  unsigned int v4; // eax
  int v5; // ebp
  unsigned int v6; // ecx
  int *v7; // edi
  int v8; // eax
  void (***v9)(_DWORD, _DWORD); // edi
  int v10; // ebx
  int v11; // ebx
  int i; // edi
  int result; // eax
  float fProgress; // [esp+0x0] [ebp-0x18]
  int v15; // [esp+0x4] [ebp-0x14]
  BYTE Data[4]; // [esp+0x14] [ebp-0x4] BYREF

  v2 = 0;
  v3 = v1;
  *(_DWORD *)Data = 0;
  ReadRegistryString("SOFTWARE\\SOFTSTAR\\PAL3_SAVE", "SEEK", (char *)Data);
  v4 = *(_DWORD *)Data;
  if ( *(_DWORD *)Data >= 0x24u )
  {
    v4 = 35;
    *(_DWORD *)Data = 35;
  }
  v5 = 0;
  v6 = v4;
  if ( v4 <= 4 )
  {
    v4 = 0;
    *(_DWORD *)Data = 0;
  }
  else
  {
    v5 = 4;
  }
  *(_DWORD *)(v3 + 130356) = v6;
  *(_DWORD *)(v3 + 130348) = v4 - v5;
  *(_DWORD *)(v3 + 130352) = v6;
  *(_DWORD *)(v3 + 130336) = v6 - v5;
  if ( (int)(v6 - v5) < 31 )
  {
    *(_DWORD *)(v3 + 130332) = (v6 - v5) * *(_DWORD *)(v3 + 130340);
  }
  else
  {
    *(_DWORD *)(v3 + 130336) = 31;
    *(_DWORD *)(v3 + 130332) = (__int64)*(float *)(v3 + 130288);
  }
  fProgress = (float)*(int *)(v3 + 130332);
  (((CScreenMode *)(v3 + 130060)))->CScreenMode::SetProgress(fProgress);
  v7 = (int *)(v3 + 896);
  do
  {
    v8 = (unsigned long)(*v7 - *(_DWORD *)(v3 + 130340) * (*(_DWORD *)Data - v5));
    *v7 = v8;
    v7[2] = *(_DWORD *)(v3 + 130340) + v8;
    (((ChoseCompose *)v3))->ChoseCompose::LayoutItems(v2++, *(v7 - 1), *v7, v7[1], v7[2]);
    v7 += 890;
  }
  while ( v2 < 36 );
  TaskBookUI_RefreshElements(v15);
  v9 = (void ( ***)(_DWORD, _DWORD))(v3 + 4148);
  v10 = 36;
  do
  {
    sub_445E50((int)(v9 - 810));
    (**v9)((_DWORD)(v9), (_DWORD)(0));
    v9 += 890;
    --v10;
  }
  while ( v10 );
  sub_445E50(v3 + 3560 * *(_DWORD *)(v3 + 130352) + 908);
  (**(void ( ***)(int, int))(v3 + 3560 * *(_DWORD *)(v3 + 130352) + 4148))((int)(v3 + 3560 * *(_DWORD *)(v3 + 130352) + 4148), (int)(1));
  v11 = 0;
  for ( i = 0; i < 760; i += 152 )
  {
    result = 3560 * *(_DWORD *)(v3 + 130352);
    if ( *(_BYTE *)(result + v11 + v3 + 3076) )
    {
      (**(void ( ***)(int, _DWORD))(i + result + v3 + 1556))((int)(i + result + v3 + 1556), (_DWORD)(0));
      result = (**(int ( ***)(int, int))(i + 3560 * *(_DWORD *)(v3 + 130352) + v3 + 2316))((int)(i + 3560 * *(_DWORD *)(v3 + 130352) + v3 + 2316), (int)(1));
    }
    ++v11;
  }
  return result;
}

// 0x004568C0
int UITitle_QCYM_OnMsgSaveData(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // eax
  CScreenMode *Instance; // eax
  const void *v10; // [esp-0x8] [ebp-0xC]
  int v11; // [esp+0x0] [ebp-0x4]
  ARC_PlayerAtt *nMsg; // [esp+0xC] [ebp+0x8]
  int wParam; // [esp+0x10] [ebp+0xC]

  v2 = v1;
  if ( nVal == 1000 )
  {
    if ( nMsg )
    {
      TaskBookUI_SaveData(v11);
      (((TaskBookUI *)v2))->TaskBookUI::_todo_00456220();
      *(_DWORD *)(v2 + 130360) = 0;
    }
    return 1;
  }
  if ( nVal == 1001 )
  {
    if ( nMsg == (ARC_PlayerAtt *)209 )
    {
      v10 = off_5AE380;
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v10, 1);
      (((ChoseCompose *)*(ChoseCompose **)(v2 + 133100)))->ChoseCompose::Init(0);
      return 1;
    }
    v8 = (char *)&nMsg[-1].dwMagicID[5][3] + 3 - (char *)&byte_A00630;
    if ( !v8 )
    {
      TaskBookUI_ScrollUp(1);
      return 1;
    }
    if ( v8 == 1 )
    {
      TaskBookUI_ScrollDown(1);
      return 1;
    }
    return 1;
  }
  if ( nVal != 1019 )
    return (((UIWnd *)v1))->UIWnd::OnMessage(nVal, (int)nMsg, wParam);
  if ( nMsg == &g_PlayerAttBuffer2 )
  {
    v4 = (__int64)*(float *)(v1 + 130292);
    v5 = *(_DWORD *)(v1 + 130332);
    if ( v4 <= v5 )
    {
      if ( v4 < v5 && v4 <= (*(_DWORD *)(v1 + 130336) - 1) * *(_DWORD *)(v1 + 130340) )
      {
        TaskBookUI_ScrollDown(0);
        v7 = *(_DWORD *)(v2 + 130336);
        *(_DWORD *)(v2 + 130332) = v4;
        *(_DWORD *)(v2 + 130336) = v7 - 1;
        if ( v7 - 1 <= 1 )
          *(_DWORD *)(v2 + 130336) = 1;
      }
    }
    else if ( v4 >= *(_DWORD *)(v1 + 130336) * *(_DWORD *)(v1 + 130340) )
    {
      TaskBookUI_ScrollUp(0);
      v6 = *(_DWORD *)(v2 + 130336);
      *(_DWORD *)(v2 + 130332) = v4;
      *(_DWORD *)(v2 + 130336) = v6 + 1;
      if ( v6 + 1 > 36 )
      {
        *(_DWORD *)(v2 + 130336) = 36;
        return 1;
      }
    }
  }
  return 1;
}

// 0x00456FC0
BOOL ReadRegistryString(const char *szSubKey, const char *szValueName, char *szOutBuf)
{
  DWORD v3; // ecx
  BOOL result; // eax
  DWORD cbData; // [esp+0x0] [ebp-0x4] BYREF

  cbData = v3;
  result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, szSubKey, 0, 1u, (PHKEY)&szSubKey);
  if ( result )
  {
    LOBYTE(result) = 0;
  }
  else
  {
    cbData = 32;
    RegQueryValueExA((HKEY)szSubKey, szValueName, 0, 0, (LPBYTE)szOutBuf, &cbData);
    result = RegCloseKey((HKEY)szSubKey);
    LOBYTE(result) = 1;
  }
  return result;
}

// 0x00457340
int UIWnd_CleanupScript(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  void *v4; // [esp+0x0] [ebp-0x14]

  v2 = v1;
  (((PalScript *)(v1 + 805416)))->PalScript::Cleanup();
  NullCallback(v4);
  (((PalScript *)(v2 + 4)))->PalScript::Cleanup();
  return result;
}

// 0x004573A0
int PalScript_FreeScriptBuffers(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax

  v2 = v1;
  (((PalScript *)(v1 + 4)))->PalScript::FreeLoadBuffer();
  (((PalScript *)(v2 + 805416)))->PalScript::FreeLoadBuffer();
  return result;
}

// 0x00459900
int UIScene_RenderUI(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = *(_DWORD *)(v1 + 3272);
  if ( result )
    return crt_sub_00540D20();
  return result;
}

// 0x00459F80
int IsStateFlagSet(_BYTE *_this)
{
  int result; // eax
  int i; // edx

  result = 0;
  for ( i = 0; i < 4; ++i )
  {
    if ( _this[i + 153] )
      ++result;
  }
  return result;
}

// 0x0045A220
int UIFrameWnd_OnPaintUpdate(int nVal)
{
  int result; // eax
  _DWORD *v2; // ecx
  _DWORD *v3; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v18; // edi
  CScreenMode *v19; // eax
  CScreenMode *v20; // eax
  int v21; // ecx
  int v22; // ecx

  v3 = (_DWORD *)v2;
  switch ( nVal )
  {
    case 0:
      result = (*(int ( **)(_DWORD *, int, int, _DWORD))(*v2 + 24))(v2, 1000, 1, 0);
      v4 = (unsigned long)v3[815];
      if ( v4 )
        result = (*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(1000, 0, 0);
      goto LABEL_4;
    case 1:
      result = (*(int ( **)(_DWORD *, int, _DWORD, _DWORD))(*v2 + 24))(v2, 1000, 0, 0);
      v6 = (unsigned long)v3[815];
      if ( v6 )
        result = (*(int ( **)(int, int, _DWORD))(*(_DWORD *)v6 + 24))(1000, 1, 0);
LABEL_4:
      v5 = (unsigned long)v3[816];
      if ( v5 )
        result = (*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v5 + 24))(1000, 0, 0);
      goto LABEL_12;
    case 2:
      result = (*(int ( **)(_DWORD *, int, _DWORD, _DWORD))(*v2 + 24))(v2, 1000, 0, 0);
      v7 = (unsigned long)v3[815];
      if ( v7 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1000, 0, 0);
      v8 = (unsigned long)v3[816];
      if ( v8 )
        result = (*(int ( **)(int, int, _DWORD))(*(_DWORD *)v8 + 24))(1000, 1, 0);
LABEL_12:
      v9 = (unsigned long)v3[817];
      if ( v9 )
        goto LABEL_38;
      goto LABEL_39;
    case 3:
      result = (*(int ( **)(_DWORD *, int, _DWORD, _DWORD))(*v2 + 24))(v2, 1000, 0, 0);
      v10 = (unsigned long)v3[815];
      if ( v10 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1000, 0, 0);
      v11 = (unsigned long)v3[816];
      if ( v11 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 0, 0);
      v12 = (unsigned long)v3[817];
      if ( !v12 )
        goto LABEL_39;
      result = (*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 1, 0);
      v3[814] = nVal;
      return result;
    case 4:
      result = (*(int ( **)(_DWORD *, int, _DWORD, _DWORD))(*v2 + 24))(v2, 1000, 0, 0);
      v13 = (unsigned long)v3[815];
      if ( v13 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v13 + 24))(v13, 1000, 0, 0);
      v14 = (unsigned long)v3[816];
      if ( v14 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v14 + 24))(v14, 1000, 0, 0);
      v15 = (unsigned long)v3[817];
      if ( v15 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v15 + 24))(v15, 1000, 0, 0);
      if ( (g_dwGameFlags & 4) == 0 )
        goto LABEL_39;
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
      v18 = (gbAudioManager *)AudioManager;
      if ( AudioManager )
      {
        (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(1);
        (((gbAudioManager *)v18))->gbAudioManager::StopSoundStream(2);
      }
      if ( CScreenMode::GetInstance()->m_bRenderAlt )
      {
        v19 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v19))->CScreenMode::AudioFadeOut();
      }
      else
      {
        v20 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v20))->CScreenMode::AudioStopAll();
      }
      v3[814] = nVal;
      return result;
    case 5:
      result = (*(int ( **)(_DWORD *, int, _DWORD, _DWORD))(*v2 + 24))(v2, 1000, 0, 0);
      v21 = (unsigned long)v3[815];
      if ( v21 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v21 + 24))(v21, 1000, 0, 0);
      v22 = (unsigned long)v3[816];
      if ( v22 )
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v22 + 24))(v22, 1000, 0, 0);
      v9 = (unsigned long)v3[817];
      if ( v9 )
LABEL_38:
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1000, 0, 0);
      goto LABEL_39;
    default:
LABEL_39:
      v3[814] = nVal;
      return result;
  }
}

// 0x00462120
int SaleUI_SetSelectionFlags(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // edi
  int v4; // edx
  int v5; // eax
  int result; // eax

  v2 = v1;
  v3 = 0;
  v4 = 0;
  *(_DWORD *)(v1 + 356) = 0;
  do
  {
    v5 = *(_DWORD *)(v1 + 356);
    if ( *(_BYTE *)(v5 + v1 + 26348) && *(_BYTE *)(*(_DWORD *)(v1 + 4 * nVal + 15880) + v5 + 614) )
    {
      ++v3;
      v4 = *(_DWORD *)(v1 + 356);
    }
    result = v5 + 1;
    *(_DWORD *)(v1 + 356) = result;
  }
  while ( result < 5 );
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      result = *(unsigned __int8 *)(*(_DWORD *)(v1 + 4 * nVal + 15880) + 612) - 7;
      switch ( *(_BYTE *)(*(_DWORD *)(v1 + 4 * nVal + 15880) + 612) )
      {
        case 7:
          result = (((SaleUI *)v1))->SaleUI::HandleInput(v4, 0, nVal);
          break;
        case 8:
          result = (((SaleUI *)v1))->SaleUI::HandleInput(v4, 3, nVal);
          break;
        case 9:
          result = (((SaleUI *)v1))->SaleUI::HandleInput(v4, 4, nVal);
          break;
        case 0xB:
          result = (((SaleUI *)v1))->SaleUI::HandleInput(v4, 1, nVal);
          break;
        default:
          return result;
      }
    }
  }
  else
  {
    sprintf((char *const)(v1 + 80), "\\n    %s", (const char *)&dword_DD4A3C);
    SetEnable((UICaption *)(v2 + 94380));
    return (((UIRoleSelect *)(v2 + 93924)))->UIRoleSelect::SetByte(1);
  }
  return result;
}

// 0x0046ADF0
char GetCellStateByte(_BYTE *_this)
{
  char result; // al

  result = _this[95265];
  if ( !result )
  {
    result = g_Input.KeyInfo[7].PressTime;
    if ( g_Input.KeyInfo[7].PressTime == 1 )
      result = (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 262, 0);
    if ( g_Input.KeyInfo[10].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 405, 0);
    }
    else if ( g_Input.KeyInfo[9].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 406, 0);
    }
    else if ( g_Input.KeyInfo[6].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, int, int))(*(_DWORD *)_this + 24))(_this, 1009, 265, 30933628);
    }
    else if ( g_Input.KeyInfo[8].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, _DWORD, _DWORD))(*(_DWORD *)_this + 24))(_this, 264, 0, 0);
    }
  }
  return result;
}

// 0x0046D0A0
int UITabCtrl_SetItemParam(int nVal)
{
  int v1; // ecx
  int result; // eax
  int v3; // [esp+0x8] [ebp+0x8]

  if ( nVal < 0 || nVal >= *(_DWORD *)(v1 + 504) )
  {
    result = 0;
    MEMORY[0x44] = v3;
  }
  else
  {
    result = *(_DWORD *)(*(_DWORD *)(v1 + 500) + 4 * nVal);
    *(_DWORD *)(result + 68) = v3;
  }
  return result;
}

// 0x0046F3D0
char GetInputFlag(_BYTE *_this)
{
  char result; // al

  result = _this[21261];
  if ( !result )
  {
    result = g_Input.KeyInfo[7].PressTime;
    if ( g_Input.KeyInfo[7].PressTime == 1 )
      result = (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 518, 0);
    if ( g_Input.KeyInfo[10].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 546, 0);
    }
    else if ( g_Input.KeyInfo[9].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 547, 0);
    }
    else if ( g_Input.KeyInfo[6].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, int, int))(*(_DWORD *)_this + 24))(_this, 1009, 521, 30933628);
    }
    else if ( g_Input.KeyInfo[8].PressTime == 1 )
    {
      return (*(int ( **)(_BYTE *, int, _DWORD, _DWORD))(*(_DWORD *)_this + 24))(_this, 519, 0, 0);
    }
  }
  return result;
}

// 0x00470A60
int UIListBox_InitWithPalScript(int nVal)
{
  UIListBox *v1; // ecx
  int v2; // esi
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *v5; // eax
  int v6; // ecx
  int v7; // eax

  v2 = (int)v1;
  v1->UIListBox::UIListBox();
  *(_DWORD *)(v2 + 72) = 800;
  *(_DWORD *)(v2 + 76) = 600;
  *(_DWORD *)(v2 + 592) = -1;
  *(_WORD *)(v2 + 598) = 0;
  *(_DWORD *)(v2 + 14492) = 0;
  *(_DWORD *)(v2 + 14496) = 0;
  memset((void *)(v2 + 14500), 0, 0x640u);
  memset((void *)(v2 + 17700), 0, 0x190u);
  memset((void *)(v2 + 16100), 0, 0x640u);
  *(_DWORD *)(v2 + 596) = 0;
  v3 = (_DWORD *)(v2 + 46832);
  v4 = 1794;
  do
  {
    *v3 = 0xFFFF;
    v3[1] = 0;
    v3[2] = 0;
    v3 += 3;
    --v4;
  }
  while ( v4 );
  v5 = (_DWORD *)(v2 + 68360);
  v6 = 1794;
  do
  {
    *v5 = 0xFFFF;
    v5[1] = 0;
    v5[2] = 0;
    v5 += 3;
    --v6;
  }
  while ( v6 );
  *(_DWORD *)(v2 + 100652) = 0;
  (((UIFrameContainer *)(v2 + 100672)))->UIFrameContainer::ResetContainerState();
  ((UI3DCtrl *)(v2 + 100824))->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)(v2 + 100908)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  ((PalScript *)(v2 + 101420))->PalScript::PalScript();
  *(_DWORD *)(v2 + 102424) = 250;
  *(_DWORD *)(v2 + 102428) = 150;
  ((UIRoleDialog *)(v2 + 102448))->UIRoleDialog::UIRoleDialog();
  (((UIProgressBar *)(v2 + 103816)))->UIProgressBar::ctor();
  (((UIFrameContainer *)(v2 + 104140)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 104292)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 104444)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 104596)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 107100)))->UIFrameContainer::ResetContainerState();
  ((UI3DCtrl *)(v2 + 111768))->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)(v2 + 111852)))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)(v2 + 113844)))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)(v2 + 115056)))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)(v2 + 116268)))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)(v2 + 117480)))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)(v2 + 118692)))->UIListBox::UpdateKeyCtrl();
  (((UIListBox *)(v2 + 119904)))->UIListBox::UpdateKeyCtrl();
  *(_DWORD *)(v2 + 121116) = 0;
  *(_DWORD *)(v2 + 121120) = 0;
  NameSys::GetSys();
  NameSys::GetSys();
  *(_DWORD *)(v2 + 121844) = 32;
  *(_DWORD *)(v2 + 121848) = 16;
  *(_DWORD *)(v2 + 121852) = 0;
  *(_DWORD *)(v2 + 121856) = 0;
  NameSys::GetSys();
  NameSys::GetSys();
  *(_DWORD *)(v2 + 122560) = -1;
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)(v2 + 123268)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 123420)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 123572)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 123740)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 123908)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 124076)))->UIFrameContainer::ResetContainerState();
  *(_BYTE *)(v2 + 124244) = 0;
  *(_BYTE *)(v2 + 124245) = 0;
  *(_DWORD *)(v2 + 124248) = 0;
  *(_DWORD *)(v2 + 121112) = 0;
  *(_DWORD *)(v2 + 119900) = 0;
  *(_DWORD *)(v2 + 118688) = 0;
  *(_DWORD *)(v2 + 117476) = 0;
  *(_DWORD *)(v2 + 116264) = 0;
  *(_DWORD *)(v2 + 115052) = 0;
  *(_BYTE *)(v2 + 46828) = 0;
  *(_BYTE *)(v2 + 102440) = 1;
  *(_BYTE *)(v2 + 102444) = 0;
  *(_BYTE *)(v2 + 102443) = 0;
  *(_BYTE *)(v2 + 102442) = 0;
  *(_BYTE *)(v2 + 102441) = 0;
  memset((void *)(v2 + 46832), 0, 0x5418u);
  memset((void *)(v2 + 68360), 0, 0x5418u);
  memset((void *)(v2 + 18100), 0, 0x3810u);
  memset((void *)(v2 + 32452), 0, 0x1C08u);
  memset((void *)(v2 + 39628), 0, 0x1C08u);
  memset((void *)(v2 + 89888), 0, 0x1C08u);
  memset((void *)(v2 + 46804), 0, 0x18u);
  lstrcpyA((LPSTR)(v2 + 104764), unk_C10D38);
  v7 = *(_DWORD *)(v2 + 76);
  *(_DWORD *)(v2 + 102424) = 68;
  *(_DWORD *)(v2 + 102432) = 65;
  *(_DWORD *)(v2 + 102428) = v7 / 4;
  *(_DWORD *)(v2 + 102436) = 86;
  *(_BYTE *)(v2 + 124264) = 1;
  return v2;
}

// 0x00470F40
int LineupUI__LineupUI(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax

  v2 = v1;
  *(_BYTE *)(v1 + 46828) = 0;
  *(_DWORD *)(v1 + 124248) = 0;
  Destroy__ovl_03(v1);
  (((UIFrameContainer *)(v2 + 124076)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 123908)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 123740)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 123572)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 123420)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 123268)))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)(v2 + 122924)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 122580)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 122216)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 121872)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 121500)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 121156)))->UICaption::Destroy2();
  (((UIListBox *)(v2 + 119904)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 118692)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 117480)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 116268)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 115056)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 113844)))->UIListBox::DeleteRow();
  (((UIFrameContainer *)(v2 + 111852)))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)(v2 + 111768));
  (((UIFrameContainer *)(v2 + 107100)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 104596)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 104444)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 104292)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 104140)))->UIFrameContainer::~UIFrameContainer();
  (((PalScript *)(v2 + 103816)))->PalScript::Reset();
  (((UIRoleDialog *)(v2 + 102448)))->UIRoleDialog::~UIRoleDialog();
  (((PalScript *)(v2 + 101420)))->PalScript::ctor();
  (((UICaption *)(v2 + 101060)))->UICaption::Destroy2();
  (((UIFrameContainer *)(v2 + 100908)))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)(v2 + 100824));
  (((UIFrameContainer *)(v2 + 100672)))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)v2))->UIListBox::~UIListBox();
  return result;
}

// 0x00471590
int LineupUI_InitListView(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebp
  _DWORD *v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // ecx
  int v10; // edi
  UIPushButton *v11; // ebx
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // edx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // edx
  int v24; // edx
  int v25; // edx
  float v26; // eax
  float v27; // edx
  int v28; // edx
  int v29; // eax
  int v30; // ecx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  int v34; // edi
  UIPushButton *v35; // edi
  int v36; // ebx
  int v37; // edx
  int v38; // ebx
  int v39; // ebp
  int v40; // edx
  int v41; // ecx
  int v42; // eax
  char *v43; // ebp
  int v44; // eax
  int v45; // edx
  int v46; // edx
  int v47; // eax
  int v48; // edx
  int v49; // eax
  int v50; // edx
  int v51; // eax
  int v52; // edx
  int v53; // eax
  int v54; // edx
  int v55; // eax
  int v56; // edx
  int v57; // ecx
  int v58; // eax
  int v59; // edx
  int v60; // edx
  int v61; // ecx
  int v62; // eax
  int v63; // edx
  int v64; // edx
  int v65; // ecx
  int v66; // edx
  int v67; // edx
  int v68; // ecx
  int v69; // edx
  int v70; // edx
  int v71; // edx
  int v72; // edx
  int v73; // eax
  int v74; // edx
  int v75; // eax
  int v76; // ecx
  int v77; // eax
  int v78; // edi
  int result; // eax
  int v80; // [esp+0x244] [ebp-0x10C]
  int v81; // [esp+0x244] [ebp-0x10C]
  _DWORD v82[2]; // [esp+0x258] [ebp-F8h] BYREF
  int v83; // [esp+0x260] [ebp-F0h]
  int v84; // [esp+0x264] [ebp-ECh]
  int v85; // [esp+0x268] [ebp-E8h] BYREF
  int v86; // [esp+0x26C] [ebp-E4h]
  int v87; // [esp+0x270] [ebp-E0h]
  int v88; // [esp+0x274] [ebp-DCh]
  _DWORD v89[2]; // [esp+0x278] [ebp-D8h] BYREF
  int v90; // [esp+0x280] [ebp-D0h]
  int v91; // [esp+0x284] [ebp-CCh]
  gbVec3D pPos; // [esp+0x288] [ebp-C8h] BYREF
  int v93; // [esp+0x294] [ebp-BCh]
  int v94; // [esp+0x298] [ebp-B8h] BYREF
  int v95; // [esp+0x29C] [ebp-B4h]
  int v96; // [esp+0x2A0] [ebp-B0h]
  int v97; // [esp+0x2A4] [ebp-ACh]
  gbVec3D pDir; // [esp+0x2A8] [ebp-A8h] BYREF
  int v99; // [esp+0x2B4] [ebp-0x9C]
  _DWORD v100[4]; // [esp+0x2B8] [ebp-0x98] BYREF
  int v101; // [esp+0x2C8] [ebp-0x88]
  char *v102; // [esp+0x2CC] [ebp-0x84]
  int v103; // [esp+0x2D0] [ebp-0x80] BYREF
  int v104; // [esp+0x2D4] [ebp-0x7C]
  int v105; // [esp+0x2D8] [ebp-0x78]
  int v106; // [esp+0x2DC] [ebp-0x74]
  int v107; // [esp+0x2E0] [ebp-0x70] BYREF
  int v108; // [esp+0x2E4] [ebp-0x6C]
  int v109; // [esp+0x2E8] [ebp-0x68]
  int v110; // [esp+0x2EC] [ebp-0x64]
  _DWORD v111[4]; // [esp+0x2F0] [ebp-0x60] BYREF
  _DWORD v112[4]; // [esp+0x300] [ebp-0x50] BYREF
  _DWORD v113[4]; // [esp+0x310] [ebp-0x40] BYREF
  int v114; // [esp+0x320] [ebp-0x30] BYREF
  int v115; // [esp+0x324] [ebp-0x2C]
  int v116; // [esp+0x328] [ebp-0x28]
  int v117; // [esp+0x32C] [ebp-0x24]
  _DWORD v118[8]; // [esp+0x330] [ebp-0x20] BYREF

  v2 = v1;
  v3 = 0;
  v4 = (_DWORD *)(v1 + 100656);
  *(_DWORD *)(v1 + 100660) = 0;
  *(_DWORD *)(v1 + 100656) = 0;
  *(_DWORD *)(v1 + 100664) = 800;
  *(_DWORD *)(v1 + 100668) = 600;
  (((UIListBox *)v1))->UIListBox::SetSelTexture(-1, *(_DWORD *)(v1 + 100656), *(_DWORD *)(v1 + 100660), *(_DWORD *)(v1 + 100664), *(_DWORD *)(v1 + 100668));
  *(_DWORD *)(v2 + 100660) = 0;
  *v4 = 0;
  *(_DWORD *)(v2 + 100668) = *(_DWORD *)(v2 + 100660) + *(_DWORD *)(v2 + 76);
  *(_DWORD *)(v2 + 100664) = (unsigned long)(*v4 + *(_DWORD *)(v2 + 72));
  v5 = *(_DWORD *)(v2 + 100908);
  v118[1] = 22;
  v118[0] = 266;
  v118[2] = 482;
  v118[3] = 150;
  (*(void ( **)(int, int, _DWORD *, int))(v5 + 16))(v2 + 100908, 769, (_DWORD *)(v118), v2);
  LOBYTE(v6) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 100908)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\SaleFlag.tga", v6);
  v7 = *(_DWORD *)(v2 + 100824);
  v113[1] = 564;
  v113[0] = 0;
  v113[2] = 800;
  v113[3] = 599;
  (*(void ( **)(int, int, _DWORD *, char *, _DWORD, int))(v7 + 28))(
    v2 + 100824,
    769,
    (_DWORD *)(v113),
    "UI\\Flex\\framebar.tga",
    0,
    v2);
  (((CScreenMode *)(v2 + 100824)))->CScreenMode::SetPosition(30,   35);
  v8 = *(_DWORD *)(v2 + 100672);
  v111[1] = 0;
  v111[0] = 0;
  v111[2] = 206;
  v111[3] = 600;
  (*(void ( **)(int, int, _DWORD *, int))(v8 + 16))(v2 + 100672, 769, (_DWORD *)(v111), v2);
  LOBYTE(v9) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 100672)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\Frame.tga", v9);
  v10 = v2 + 107268;
  v11 = (UIPushButton *)(v2 + 101584);
  do
  {
    v12 = *(_DWORD *)(v2 + 102432);
    v13 = *(_DWORD *)(v2 + 102428);
    v100[0] = *(_DWORD *)(v2 + 102424);
    v14 = *(_DWORD *)(v2 + 102436);
    v100[1] = v13;
    v100[3] = v13 + v14;
    v15 = *(int *)((char *)&dword_56B6F0 + v3);
    v100[2] = v100[0] + v12;
    (*(void ( **)(UIPushButton *, int, _DWORD *, int))(*(_DWORD *)((UIWnd *)v11) + 16))(v11, v15, (_DWORD *)(v100), v2);
    LOBYTE(v16) = *(_BYTE *)(v2 + 124264);
    (((UIPushButton *)v11))->UIPushButton::CreateFromTemplate(off_56B754[v3 / 4u], v16);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v11))((UIPushButton *)(v11), (_DWORD)(0));
    v17 = (*(int ( **)(int, _DWORD, _DWORD *, int))(*(_DWORD *)v10 + 16))(
            v10,
            *(int *)((char *)&dword_56B6F0 + v3),
            (_DWORD *)(v100),
            v2);
    LOBYTE(v17) = *(_BYTE *)(v2 + 124264);
    (((UIPushButton *)v10))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Cloth.tga", v17);
    *(_DWORD *)(v10 + 168) = 1090519040;
    *(_DWORD *)(v10 + 176) = 1;
    (**(void ( ***)(int, _DWORD))v10)((int)(v10), (_DWORD)(0));
    v18 = (*(int ( **)(int, _DWORD, _DWORD *, int))(*(_DWORD *)(v10 + 180) + 16))(
            v10 + 180,
            *(int *)((char *)&dword_56B6F0 + v3),
            (_DWORD *)(v100),
            v2);
    LOBYTE(v18) = *(_BYTE *)(v2 + 124264);
    (((UIPushButton *)(v10 + 180)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Weapon.tga", v18);
    *(_DWORD *)(v10 + 348) = 1090519040;
    *(_DWORD *)(v10 + 356) = 1;
    (**(void ( ***)(int, _DWORD))(v10 + 180))((int)(v10 + 180), (_DWORD)(0));
    v19 = (*(int ( **)(int, _DWORD, _DWORD *, int))(*(_DWORD *)(v10 + 360) + 16))(
            v10 + 360,
            *(int *)((char *)&dword_56B6F0 + v3),
            (_DWORD *)(v100),
            v2);
    LOBYTE(v19) = *(_BYTE *)(v2 + 124264);
    (((UIPushButton *)(v10 + 360)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Adorn.tga", v19);
    *(_DWORD *)(v10 + 528) = 1090519040;
    *(_DWORD *)(v10 + 536) = 1;
    (**(void ( ***)(int, _DWORD))(v10 + 360))((int)(v10 + 360), (_DWORD)(0));
    v20 = (*(int ( **)(int, _DWORD, _DWORD *, int))(*(_DWORD *)(v10 + 540) + 16))(
            v10 + 540,
            *(int *)((char *)&dword_56B6F0 + v3),
            (_DWORD *)(v100),
            v2);
    LOBYTE(v20) = *(_BYTE *)(v2 + 124264);
    (((UIPushButton *)(v10 + 540)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Hat.tga", v20);
    *(_DWORD *)(v10 + 708) = 1090519040;
    *(_DWORD *)(v10 + 716) = 1;
    (**(void ( ***)(int, _DWORD))(v10 + 540))((int)(v10 + 540), (_DWORD)(0));
    v21 = (*(int ( **)(int, _DWORD, _DWORD *, int))(*(_DWORD *)(v10 + 720) + 16))(
            v10 + 720,
            *(int *)((char *)&dword_56B6F0 + v3),
            (_DWORD *)(v100),
            v2);
    LOBYTE(v21) = *(_BYTE *)(v2 + 124264);
    (((UIPushButton *)(v10 + 720)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Equip\\Shoes.tga", v21);
    *(_DWORD *)(v10 + 888) = 1090519040;
    *(_DWORD *)(v10 + 896) = 1;
    (**(void ( ***)(int, _DWORD))(v10 + 720))((int)(v10 + 720), (_DWORD)(0));
    v3 += 4;
    v11 = (UIPushButton *)((char *)v11 + 152);
    v10 += 900;
  }
  while ( v3 < 20 );
  v22 = *(_DWORD *)(v2 + 111852);
  v108 = 32;
  v107 = 454;
  v109 = 790;
  v110 = 425;
  (*(void ( **)(int, int, int *, int))(v22 + 16))(v2 + 111852, 769, &v107, v2);
  LOBYTE(v23) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 111852)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ListFrame.tga", v23);
  v24 = *(_DWORD *)(v2 + 111768);
  v95 = v108;
  v94 = v107 + 7;
  v97 = v108 + 32;
  v96 = v107 + 327;
  (*(void ( **)(int, int, int *, char *, _DWORD, int))(v24 + 28))(
    v2 + 111768,
    769,
    &v94,
    "UI\\Flex\\Bar.tga",
    0,
    v2);
  (((CScreenMode *)(v2 + 111768)))->CScreenMode::SetPosition(32,   32);
  v25 = *(_DWORD *)(v2 + 107100);
  v95 = 82;
  v94 = 466;
  v96 = 774;
  v97 = 114;
  (*(void ( **)(int, int, int *, int))(v25 + 16))(v2 + 107100, 769, &v94, v2);
  (((UIScene *)(v2 + 107100)))->UIScene::SetShow(0);
  sprintf(
    (char *const)(v2 + 80),
    "%s            %s   %s %s",
    (const char *)&dword_DC353C,
    (const char *)&dword_DC363C,
    (const char *)&dword_DC373C,
    (const char *)&g_bSaveFlag);
  SetEnable((UICaption *)(v2 + 107100));
  *(_DWORD *)(v2 + 113832) = 106;
  *(_DWORD *)(v2 + 113828) = 472;
  *(_DWORD *)(v2 + 113836) = 770;
  *(_DWORD *)(v2 + 113840) = *(_DWORD *)(v2 + 113832) + 278;
  v26 = *(float *)(v2 + 113836);
  LODWORD(pPos.y) = *(_DWORD *)(v2 + 113832) + 14;
  LODWORD(v26) -= 31;
  pPos.x = v26;
  pDir.x = v26;
  LODWORD(v27) = LODWORD(v26) + 22;
  LOBYTE(v26) = *(_BYTE *)(v2 + 124264);
  v93 = LODWORD(pPos.y) + 26;
  LODWORD(pDir.y) = LODWORD(pPos.y) + 232;
  pPos.z = v27;
  pDir.z = v27;
  v28 = *(_DWORD *)(v2 + 113844);
  v99 = LODWORD(pPos.y) + 258;
  (*(void ( **)(int, int, int, int, _DWORD, int, float))(v28 + 28))(
    v2 + 113844,
    773,
    v2 + 113828,
    v2,
    0,
    1,
    _pal3_coerce_f32(LODWORD(v26)));
  (((UIListBox *)(v2 + 113844)))->UIListBox::SetLockSel(23);
  *(_DWORD *)(v2 + 115004) = -4;
  *(_DWORD *)(v2 + 115008) = -6;
  *(_DWORD *)(v2 + 115012) = 10;
  (((UIListBox *)(v2 + 113844)))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)(v2 + 113844)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)(v2 + 113828), 38, 27, 0);
  (((CCBUI *)(v2 + 113924)))->CCBUI::ShowEffect(*(_DWORD *)(v2 + 113832) + 1, *(_DWORD *)(v2 + 113836) - 38, *(_DWORD *)(v2 + 113836));
  (((CCBUI *)(v2 + 113924)))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)(v2 + 113924)))->CCBUI::SetSelection(27);
  (((CCBUI *)(v2 + 113924)))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)(v2 + 113844)))->UIListBox::SetColumnHead((int)"Name", 131);
  (((UIListBox *)(v2 + 113844)))->UIListBox::SetColumnHead((int)"Price", 52);
  (((UIListBox *)(v2 + 113844)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((UIListBox *)(v2 + 113844)))->UIListBox::SetColumnHead((int)&off_5BC4A4, 36);
  v29 = (((CCBUI *)(v2 + 113924)))->CCBUI::VirtualCall(1);
  LOBYTE(v29) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, int, int, _DWORD, int, int))(*(_DWORD *)(v2 + 115056) + 28))(
    v2 + 115056,
    774,
    v2 + 113828,
    v2,
    0,
    1,
    v29);
  (((UIListBox *)(v2 + 115056)))->UIListBox::SetLockSel(23);
  *(_DWORD *)(v2 + 116216) = -4;
  *(_DWORD *)(v2 + 116220) = -6;
  *(_DWORD *)(v2 + 116224) = 10;
  (((UIListBox *)(v2 + 115056)))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)(v2 + 115056)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)(v2 + 113828), 38, 27, 0);
  (((CCBUI *)(v2 + 115136)))->CCBUI::ShowEffect(*(_DWORD *)(v2 + 113832) + 1, *(_DWORD *)(v2 + 113836) - 38, *(_DWORD *)(v2 + 113836));
  (((CCBUI *)(v2 + 115136)))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)(v2 + 115136)))->CCBUI::SetSelection(27);
  (((CCBUI *)(v2 + 115136)))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)(v2 + 115056)))->UIListBox::SetColumnHead((int)"Name", 131);
  (((UIListBox *)(v2 + 115056)))->UIListBox::SetColumnHead((int)"Price", 52);
  (((UIListBox *)(v2 + 115056)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((UIListBox *)(v2 + 115056)))->UIListBox::SetColumnHead((int)&off_5BC4A4, 36);
  (((CCBUI *)(v2 + 115136)))->CCBUI::VirtualCall(1);
  (**(void ( ***)(int, _DWORD))(v2 + 115056))((int)(v2 + 115056), (_DWORD)(0));
  LOBYTE(v30) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, int, int, _DWORD, int, int))(*(_DWORD *)(v2 + 116268) + 28))(
    v2 + 116268,
    775,
    v2 + 113828,
    v2,
    0,
    1,
    v30);
  (((UIListBox *)(v2 + 116268)))->UIListBox::SetLockSel(23);
  *(_DWORD *)(v2 + 117428) = -4;
  *(_DWORD *)(v2 + 117432) = -6;
  *(_DWORD *)(v2 + 117436) = 10;
  (((UIListBox *)(v2 + 116268)))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)(v2 + 116268)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)(v2 + 113828), 38, 27, 0);
  (((CCBUI *)(v2 + 116348)))->CCBUI::ShowEffect(*(_DWORD *)(v2 + 113832) + 1, *(_DWORD *)(v2 + 113836) - 38, *(_DWORD *)(v2 + 113836));
  (((CCBUI *)(v2 + 116348)))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)(v2 + 116348)))->CCBUI::SetSelection(27);
  (((CCBUI *)(v2 + 116348)))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)(v2 + 116268)))->UIListBox::SetColumnHead((int)"Name", 131);
  (((UIListBox *)(v2 + 116268)))->UIListBox::SetColumnHead((int)"Price", 52);
  (((UIListBox *)(v2 + 116268)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((UIListBox *)(v2 + 116268)))->UIListBox::SetColumnHead((int)&off_5BC4A4, 36);
  (((CCBUI *)(v2 + 116348)))->CCBUI::VirtualCall(1);
  (**(void ( ***)(int, _DWORD))(v2 + 116268))((int)(v2 + 116268), (_DWORD)(0));
  LOBYTE(v31) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, int, int, _DWORD, int, int))(*(_DWORD *)(v2 + 117480) + 28))(
    v2 + 117480,
    776,
    v2 + 113828,
    v2,
    0,
    1,
    v31);
  (((UIListBox *)(v2 + 117480)))->UIListBox::SetLockSel(23);
  *(_DWORD *)(v2 + 118640) = -4;
  *(_DWORD *)(v2 + 118644) = -6;
  *(_DWORD *)(v2 + 118648) = 10;
  (((UIListBox *)(v2 + 117480)))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)(v2 + 117480)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)(v2 + 113828), 38, 27, 0);
  (((CCBUI *)(v2 + 117560)))->CCBUI::ShowEffect(*(_DWORD *)(v2 + 113832) + 1, *(_DWORD *)(v2 + 113836) - 38, *(_DWORD *)(v2 + 113836));
  (((CCBUI *)(v2 + 117560)))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)(v2 + 117560)))->CCBUI::SetSelection(27);
  (((CCBUI *)(v2 + 117560)))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)(v2 + 117480)))->UIListBox::SetColumnHead((int)"Name", 131);
  (((UIListBox *)(v2 + 117480)))->UIListBox::SetColumnHead((int)"Price", 52);
  (((UIListBox *)(v2 + 117480)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((UIListBox *)(v2 + 117480)))->UIListBox::SetColumnHead((int)&off_5BC4A4, 36);
  (((CCBUI *)(v2 + 117560)))->CCBUI::VirtualCall(1);
  (**(void ( ***)(int, _DWORD))(v2 + 117480))((int)(v2 + 117480), (_DWORD)(0));
  LOBYTE(v32) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, int, int, _DWORD, int, int))(*(_DWORD *)(v2 + 118692) + 28))(
    v2 + 118692,
    777,
    v2 + 113828,
    v2,
    0,
    1,
    v32);
  (((UIListBox *)(v2 + 118692)))->UIListBox::SetLockSel(23);
  *(_DWORD *)(v2 + 119852) = -4;
  *(_DWORD *)(v2 + 119856) = -6;
  *(_DWORD *)(v2 + 119860) = 10;
  (((UIListBox *)(v2 + 118692)))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)(v2 + 118692)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)(v2 + 113828), 38, 27, 0);
  (((CCBUI *)(v2 + 118772)))->CCBUI::ShowEffect(*(_DWORD *)(v2 + 113832) + 1, *(_DWORD *)(v2 + 113836) - 38, *(_DWORD *)(v2 + 113836));
  (((CCBUI *)(v2 + 118772)))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)(v2 + 118772)))->CCBUI::SetSelection(27);
  (((CCBUI *)(v2 + 118772)))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)(v2 + 118692)))->UIListBox::SetColumnHead((int)"Name", 131);
  (((UIListBox *)(v2 + 118692)))->UIListBox::SetColumnHead((int)"Price", 52);
  (((UIListBox *)(v2 + 118692)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((UIListBox *)(v2 + 118692)))->UIListBox::SetColumnHead((int)&off_5BC4A4, 36);
  (((CCBUI *)(v2 + 118772)))->CCBUI::VirtualCall(1);
  (**(void ( ***)(int, _DWORD))(v2 + 118692))((int)(v2 + 118692), (_DWORD)(0));
  LOBYTE(v33) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, int, int, _DWORD, int, int))(*(_DWORD *)(v2 + 119904) + 28))(
    v2 + 119904,
    785,
    v2 + 113828,
    v2,
    0,
    1,
    v33);
  (((UIListBox *)(v2 + 119904)))->UIListBox::SetLockSel(23);
  *(_DWORD *)(v2 + 121064) = -4;
  *(_DWORD *)(v2 + 121068) = -6;
  *(_DWORD *)(v2 + 121072) = 10;
  (((UIListBox *)(v2 + 119904)))->UIListBox::GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  (((UIListBox *)(v2 + 119904)))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)(v2 + 113828), 38, 27, 0);
  (((CCBUI *)(v2 + 119984)))->CCBUI::ShowEffect(*(_DWORD *)(v2 + 113832) + 1, *(_DWORD *)(v2 + 113836) - 38, *(_DWORD *)(v2 + 113836));
  (((CCBUI *)(v2 + 119984)))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)(v2 + 119984)))->CCBUI::SetSelection(27);
  (((CCBUI *)(v2 + 119984)))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)(v2 + 119904)))->UIListBox::SetColumnHead((int)"Name", 131);
  (((UIListBox *)(v2 + 119904)))->UIListBox::SetColumnHead((int)"Price", 52);
  (((UIListBox *)(v2 + 119904)))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 36);
  (((UIListBox *)(v2 + 119904)))->UIListBox::SetColumnHead((int)&off_5BC4A4, 36);
  (((CCBUI *)(v2 + 119984)))->CCBUI::VirtualCall(1);
  (**(void ( ***)(int, _DWORD))(v2 + 119904))((int)(v2 + 119904), (_DWORD)(0));
  v34 = *(_DWORD *)(v2 + 113828);
  v104 = *(_DWORD *)(v2 + 113832) + 2;
  v103 = v34;
  v105 = v34 + 256;
  v106 = v104 + 23;
  v35 = (UIPushButton *)(v2 + 112004);
  v36 = 12;
  do
  {
    (*(void ( **)(UIPushButton *, int, int *, int))(*(_DWORD *)((UIWnd *)v35) + 16))(v35, 769, &v103, v2);
    LOBYTE(v37) = *(_BYTE *)(v2 + 124264);
    (((UIPushButton *)v35))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Communal\\Sale_Grid.tga", v37);
    v35 = (UIPushButton *)((char *)v35 + 152);
    v104 = v106;
    --v36;
    v106 += 23;
  }
  while ( v36 );
  LOBYTE(v101) = *(_BYTE *)(v2 + 124264);
  v38 = (unsigned __int8)v101;
  v39 = v101;
  v102 = (char *)"UI\\Assistant\\Communal\\Add";
  v80 = v101;
  v40 = *(_DWORD *)(v2 + 121156);
  *(_DWORD *)(v2 + 121844) = 24;
  *(_DWORD *)(v2 + 121848) = 40;
  *(_DWORD *)(v2 + 121128) = 158;
  *(_DWORD *)(v2 + 121124) = 476;
  *(_DWORD *)(v2 + 121132) = 500;
  *(_DWORD *)(v2 + 121136) = 198;
  (*(void ( **)(int, int, int, int, char *, _DWORD, int))(v40 + 28))(
    v2 + 121156,
    821,
    v2 + 121124,
    v2,
    "UI\\Assistant\\Communal\\Sub",
    0,
    v80);
  v41 = *(_DWORD *)(v2 + 121124);
  v42 = *(_DWORD *)(v2 + 121136);
  *(_DWORD *)(v2 + 121144) = v42;
  v81 = v39;
  v43 = (char *)v102;
  *(_DWORD *)(v2 + 121140) = v41;
  *(_DWORD *)(v2 + 121148) = *(_DWORD *)(v2 + 121132);
  *(_DWORD *)(v2 + 121152) = *(_DWORD *)(v2 + 121848) + v42;
  (*(void ( **)(int, int, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 121500) + 28))(
    822,
    v2 + 121140,
    v2,
    v43,
    0,
    v81);
  *(_BYTE *)(v2 + 121860) = v38;
  *(_DWORD *)(v2 + 121852) = 1;
  (((PalScript *)(v2 + 121156)))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnSub.tga", *(_BYTE *)(v2 + 121860));
  (((PalScript *)(v2 + 121500)))->PalScript::OpenScript("UI\\Assistant\\Communal\\UnAdd.tga", *(_BYTE *)(v2 + 121860));
  *(_DWORD *)(v2 + 121856) = 20;
  (**(void ( ***)(int, _DWORD))(v2 + 121156))((int)(v2 + 121156), (_DWORD)(0));
  v44 = (**(int ( ***)(int, _DWORD))(v2 + 121500))((int)(v2 + 121500), (_DWORD)(0));
  LOBYTE(v44) = *(_BYTE *)(v2 + 124264);
  v45 = *(_DWORD *)(v2 + 105020);
  v82[1] = 30;
  v82[0] = 472;
  v83 = 514;
  v84 = 80;
  (*(void ( **)(int, int, _DWORD *, int, char *, _DWORD, int))(v45 + 28))(
    v2 + 105020,
    808,
    (_DWORD *)(v82),
    v2,
    "UI\\GameMainUI\\Prop\\Resume",
    0,
    v44);
  (((PalScript *)(v2 + 105020)))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Resume2.tga", *(_BYTE *)(v2 + 124264));
  v46 = *(_DWORD *)(v2 + 105364);
  v82[0] = v83 + 11;
  v83 += 53;
  v47 = v83;
  LOBYTE(v47) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, _DWORD *, int, char *, _DWORD, int))(v46 + 28))(
    v2 + 105364,
    809,
    (_DWORD *)(v82),
    v2,
    "UI\\GameMainUI\\Prop\\Treasure",
    0,
    v47);
  (((PalScript *)(v2 + 105364)))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Treasure2.tga", *(_BYTE *)(v2 + 124264));
  v48 = *(_DWORD *)(v2 + 105708);
  v82[0] = v83 + 11;
  v83 += 53;
  v49 = v83;
  LOBYTE(v49) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, _DWORD *, int, char *, _DWORD, int))(v48 + 28))(
    v2 + 105708,
    816,
    (_DWORD *)(v82),
    v2,
    "UI\\GameMainUI\\Prop\\Attack",
    0,
    v49);
  (((PalScript *)(v2 + 105708)))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Attack2.tga", *(_BYTE *)(v2 + 124264));
  v50 = *(_DWORD *)(v2 + 106052);
  v82[0] = v83 + 11;
  v83 += 53;
  v51 = v83;
  LOBYTE(v51) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, _DWORD *, int, char *, _DWORD, int))(v50 + 28))(
    v2 + 106052,
    817,
    (_DWORD *)(v82),
    v2,
    "UI\\GameMainUI\\Prop\\Smelt",
    0,
    v51);
  (((PalScript *)(v2 + 106052)))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Smelt2.tga", *(_BYTE *)(v2 + 124264));
  v52 = *(_DWORD *)(v2 + 106396);
  v82[0] = v83 + 11;
  v83 += 53;
  v53 = v83;
  LOBYTE(v53) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, int, _DWORD *, int, char *, _DWORD, int))(v52 + 28))(
    v2 + 106396,
    818,
    (_DWORD *)(v82),
    v2,
    "UI\\GameMainUI\\Prop\\Ancient",
    0,
    v53);
  (((PalScript *)(v2 + 106396)))->PalScript::OpenScript("UI\\GameMainUI\\Prop\\Ancient2.tga", *(_BYTE *)(v2 + 124264));
  v54 = *(_DWORD *)(v2 + 106740);
  v82[0] = v83 + 11;
  v83 += 53;
  v55 = v83;
  LOBYTE(v55) = *(_BYTE *)(v2 + 124264);
  (*(void ( **)(int, _DWORD, _DWORD *, int, char *, _DWORD, int))(v54 + 28))(
    v2 + 106740,
    0,
    (_DWORD *)(v82),
    v2,
    "UI\\GameMainUI\\Equip\\Cloth",
    0,
    v55);
  (((PalScript *)(v2 + 106740)))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Cloth2.tga", *(_BYTE *)(v2 + 124264));
  v56 = *(_DWORD *)(v2 + 123268);
  v86 = 142;
  v85 = 218;
  v87 = 450;
  v88 = 556;
  (*(void ( **)(int, int, int *, int))(v56 + 16))(v2 + 123268, 790, &v85, v2);
  LOBYTE(v57) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 123268)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Info.tga", v57);
  v58 = *(_DWORD *)(v2 + 123420);
  v86 = 388;
  v85 = 232;
  v87 = 444;
  v88 = 556;
  (*(void ( **)(int, int, int *, int))(v58 + 16))(v2 + 123420, 790, &v85, v2);
  (((UIScene *)(v2 + 123420)))->UIScene::SetShow(0);
  v59 = *(_DWORD *)(v2 + 123740);
  v86 = 520;
  v85 = 232;
  v87 = 444;
  v88 = 552;
  (*(void ( **)(int, int, int *, int))(v59 + 16))(v2 + 123740, 790, &v85, v2);
  (((UIScene *)(v2 + 123740)))->UIScene::SetShow(0);
  v60 = *(_DWORD *)(v2 + 123572);
  v112[1] = 159;
  v112[0] = 403;
  v112[2] = 419;
  v112[3] = 191;
  (*(void ( **)(int, int, _DWORD *, int))(v60 + 16))(v2 + 123572, 769, (_DWORD *)(v112), v2);
  LOBYTE(v61) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 123572)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Prop_word.tga", v61);
  v62 = *(_DWORD *)(v2 + 104140);
  v89[1] = 436;
  v89[0] = 456;
  v90 = 486;
  v91 = 555;
  (*(void ( **)(int, int, _DWORD *, int))(v62 + 16))(v2 + 104140, 801, (_DWORD *)(v89), v2);
  LOBYTE(v63) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 104140)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameLS.tga", v63);
  v64 = *(_DWORD *)(v2 + 104292);
  v89[0] = v90;
  v90 += 256;
  (*(void ( **)(int, int, _DWORD *, int))(v64 + 16))(v2 + 104292, 801, (_DWORD *)(v89), v2);
  LOBYTE(v65) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 104292)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\PropTopFrame\\TopFrameRM.tga", v65);
  v89[0] = v90;
  v90 += 32;
  (*(void ( **)(int, int, _DWORD *, int))(*(_DWORD *)(v2 + 104444) + 16))(v2 + 104444, 801, (_DWORD *)(v89), v2);
  LOBYTE(v66) = *(_BYTE *)(v2 + 124264);
  (((UIPushButton *)(v2 + 104444)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\EquipTopFrame\\TopFrameR.tga", v66);
  v67 = *(_DWORD *)(v2 + 104596);
  *(_DWORD *)(v2 + 104752) = 447;
  *(_DWORD *)(v2 + 104748) = 489;
  *(_DWORD *)(v2 + 104760) = *(_DWORD *)(v2 + 104752) + 100;
  *(_DWORD *)(v2 + 104756) = 745;
  (*(void ( **)(int, int, int, int))(v67 + 16))(v2 + 104596, 801, v2 + 104748, v2);
  (((UIScene *)(v2 + 104596)))->UIScene::SetShow(0);
  (**(void ( ***)(int, _DWORD))(v2 + 104596))((int)(v2 + 104596), (_DWORD)(0));
  v68 = *(_DWORD *)(v2 + 104756);
  v69 = *(_DWORD *)(v2 + 101420);
  v115 = *(_DWORD *)(v2 + 104760) - 36;
  v114 = v68 - 36;
  v117 = v115 + 32;
  v116 = v68 - 36 + 24;
  (*(void ( **)(int, int, int *, int))(v69 + 16))(v2 + 101420, 2, &v114, v2);
  (((UIScene *)(v2 + 101420)))->UIScene::LoadResource("ui\\scene\\page");
  UIScene_SetController(0x40000000);
  (**(void ( ***)(int, _DWORD))(v2 + 101420))((int)(v2 + 101420), (_DWORD)(0));
  v70 = *(_DWORD *)(v2 + 123908);
  *(_DWORD *)(v2 + 124064) = 392;
  *(_DWORD *)(v2 + 124060) = 478;
  *(_DWORD *)(v2 + 124068) = 624;
  *(_DWORD *)(v2 + 124072) = 424;
  (*(void ( **)(int, int, int, int))(v70 + 16))(v2 + 123908, 793, v2 + 124060, v2);
  (((UIScene *)(v2 + 123908)))->UIScene::SetShow(0);
  sprintf((char *const)(v2 + 80), "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)(v2 + 123908));
  v71 = *(_DWORD *)(v2 + 124076);
  *(_DWORD *)(v2 + 124232) = 392;
  *(_DWORD *)(v2 + 124228) = 638;
  *(_DWORD *)(v2 + 124236) = 764;
  *(_DWORD *)(v2 + 124240) = 424;
  (*(void ( **)(int, int, int, int))(v71 + 16))(v2 + 124076, 792, v2 + 124228, v2);
  (((UIScene *)(v2 + 124076)))->UIScene::SetShow(0);
  SetEnable((UICaption *)(v2 + 124076));
  LOBYTE(v72) = *(_BYTE *)(v2 + 124264);
  v73 = *(_DWORD *)(v2 + 122580);
  *(_DWORD *)(v2 + 122568) = 569;
  *(_DWORD *)(v2 + 122564) = 300;
  *(_DWORD *)(v2 + 122572) = 390;
  *(_DWORD *)(v2 + 122576) = 594;
  (*(void ( **)(int, int, int, int, char *, _DWORD, int))(v73 + 28))(
    v2 + 122580,
    788,
    v2 + 122564,
    v2,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v72);
  LOBYTE(v74) = *(_BYTE *)(v2 + 124264);
  v75 = *(_DWORD *)(v2 + 122572) + 132;
  *(_DWORD *)(v2 + 122564) = v75;
  *(_DWORD *)(v2 + 122572) = v75 + 90;
  (*(void ( **)(int, int, int, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 122924) + 28))(
    v2 + 122924,
    789,
    v2 + 122564,
    v2,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v74);
  v76 = *(_DWORD *)(v2 + 100664) - 38;
  v77 = *(_DWORD *)(v2 + 100668) - 50;
  v78 = *(_DWORD *)(v2 + 101060);
  *(_DWORD *)(v2 + 101404) = v76;
  *(_DWORD *)(v2 + 101408) = v77;
  v77 += 48;
  *(_DWORD *)(v2 + 101416) = v77;
  LOBYTE(v77) = *(_BYTE *)(v2 + 124264);
  *(_DWORD *)(v2 + 101412) = v76 + 38;
  (*(void ( **)(int, int, int, int, char *, _DWORD, int))(v78 + 28))(
    v2 + 101060,
    770,
    v2 + 101404,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    0,
    v77);
  (((CCBFiveNimbusWindow *)(v2 + 103816)))->CCBFiveNimbusWindow::CreateScriptAndCamera(807, v2);
  if ( !strcmp("D16", unk_C10D38) )
    sprintf((char *const)(v2 + 80), "%s", "NONE");
  else
    sprintf((char *const)(v2 + 80), "Item\\%s\\%s.pol", "D16", "D16");
  (((PalScript *)(v2 + 103888)))->PalScript::LoadModel((const char *)(v2 + 80), 0);
  *(_DWORD *)(v2 + 103892) = 0;
  *(_DWORD *)(v2 + 103884) = 1;
  (((CCBFiveNimbusWindow *)(v2 + 103816)))->CCBFiveNimbusWindow::SetFloatParam(120.0);
  (((Camera *)(v2 + 103816)))->Camera::UpdateCameraLookAt(330, 258, 600);
  sub_43A090(v2 + 103816, 1, 0.0);
  v118[5] = 200;
  v118[4] = 300;
  v118[6] = 500;
  v118[7] = 300;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 102448));
  (((UIItem *)(v2 + 102448)))->UIItem::SetData(18);
  result = *(_DWORD *)(v2 + 124248);
  if ( result )
  {
    if ( !--result )
    {
      *(_BYTE *)(v2 + 46828) = 1;
      *(_DWORD *)(v2 + 124256) = nVal;
      return result;
    }
  }
  else
  {
    *(_DWORD *)(v2 + 124252) = nVal;
  }
  *(_BYTE *)(v2 + 46828) = 1;
  return result;
}

// 0x00472A80
int LineupUI_SetPageIndex(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  if ( nVal < 2 )
    *(_DWORD *)(v1 + 124248) = nVal;
  return result;
}

// 0x00472AA0
int LineupUI_RefreshListData(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  _DWORD *v3; // ebp
  _DWORD *v4; // eax
  signed int v5; // edi
  int v6; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // edx
  _DWORD *v9; // eax
  _DWORD *v10; // edx
  int v11; // ebp
  signed int v12; // edi
  int v13; // eax
  _DWORD *v14; // eax
  _DWORD *v15; // edx
  _DWORD *v16; // eax
  _DWORD *v17; // edx
  int v18; // ebp
  _DWORD *v19; // ebp
  _DWORD *v20; // eax
  _DWORD *v21; // ebp
  _DWORD *v22; // eax
  signed int v23; // ebp
  int *v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // edi
  _DWORD *v28; // eax
  _DWORD *v29; // eax
  _DWORD *v30; // ecx
  int v31; // ebp
  int result; // eax
  int nIndex; // [esp+0x10] [ebp-0x28]
  unsigned int nIndexa; // [esp+0x10] [ebp-0x28]
  unsigned int nIndexb; // [esp+0x10] [ebp-0x28]
  int nIndexc; // [esp+0x10] [ebp-0x28]
  int nIndexd; // [esp+0x10] [ebp-0x28]
  unsigned int nIndexe; // [esp+0x10] [ebp-0x28]
  _DWORD *v39; // [esp+0x14] [ebp-0x24]
  _DWORD *v40; // [esp+0x14] [ebp-0x24]
  _DWORD *v41; // [esp+0x14] [ebp-0x24]
  int ListItems; // [esp+0x18] [ebp-0x20]
  int v43; // [esp+0x18] [ebp-0x20]
  int v44; // [esp+0x18] [ebp-0x20]
  const void *v45; // [esp+0x1C] [ebp-0x1C]
  _BYTE pOut[12]; // [esp+0x20] [ebp-0x18] BYREF
  _BYTE v47[12]; // [esp+0x2C] [ebp-0xC] BYREF

  v2 = v1;
  v45 = (const void *)(v1 + 97064);
  memset((void *)(v1 + 97064), 0, 0x700u);
  *(_WORD *)(v1 + 98856) = 0;
  memset((void *)(v1 + 32452), 0, 0x1C08u);
  memset((void *)(v1 + 39628), 0, 0x1C08u);
  (((UIListBox *)(v1 + 113844)))->UIListBox::ClearAll();
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(0);
  nIndex = 0;
  if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
  {
    v39 = (_DWORD *)(v2 + 39628);
    v3 = (_DWORD *)(v2 + 46832);
    do
    {
      v4 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, nIndex);
      *v3 = *v4;
      v3[1] = (unsigned long)v4[1];
      v3[2] = (unsigned long)v4[2];
      v3[5382] = (unsigned long)*v3;
      v3[5383] = (unsigned long)v3[1];
      v3[5384] = (unsigned long)v3[2];
      ++*(_DWORD *)(v2 + 115052);
      *v39 = v3[1];
      sprintf((char *const)(v2 + 80), "%s", v3[2] + 4);
      ListItems = (((UIListBox *)(v2 + 113844)))->UIListBox::LoadListItems((char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v3[2] + 608) / 2);
      (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(1, ListItems, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(v39 - 1794));
      (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(2, ListItems, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v39);
      (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(3, ListItems, (char *)(v2 + 80), 0);
      ++nIndex;
      ++v39;
      v3 += 3;
    }
    while ( nIndex < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
  }
  (((UIListBox *)(v2 + 113844)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 113844)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 115056)))->UIListBox::ClearAll();
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(1);
  v5 = 0;
  for ( nIndexa = 0; v5 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize(); nIndexa = v5 )
  {
    v6 = *(_DWORD *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v5);
    if ( v6 != 6409 && v6 != 6410 && v6 != 6411 && v6 != 6412 && v6 != 6413 && v6 != 6408 && v6 != 6427 )
    {
      v7 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v47, v5);
      v8 = (_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 116264) + 50420);
      *v8 = *v7;
      v8[1] = (unsigned long)v7[1];
      v8[2] = (unsigned long)v7[2];
      v9 = (_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 116264));
      v10 = (_DWORD *)(v9 + 12605);
      v9 += 17987;
      *v9 = *v10;
      v9[1] = (unsigned long)v10[1];
      v9[2] = (unsigned long)v10[2];
      *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 116264) + 40824) = *(_DWORD *)(v2
                                                                         + 4 * (3 * *(_DWORD *)(v2 + 116264) + 12606));
      sprintf((char *const)(v2 + 80), "%s", *(_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 116264) + 50428) + 4);
      v11 = (((UIListBox *)(v2 + 115056)))->UIListBox::LoadListItems((char *)(v2 + 80), 0);
      sprintf(
        (char *const)(v2 + 80),
        (const char *)&dir[20],
        *(_DWORD *)(*(_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 116264) + 50428) + 608) / 2);
      (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(1, v11, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 116264) + 33648));
      (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(2, v11, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 116264) + 40824));
      (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(3, v11, (char *)(v2 + 80), 0);
      v5 = nIndexa;
      ++*(_DWORD *)(v2 + 116264);
    }
    ++v5;
  }
  (((UIListBox *)(v2 + 115056)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 115056)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 116268)))->UIListBox::ClearAll();
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(2);
  v12 = 0;
  for ( nIndexb = 0; v12 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize(); nIndexb = v12 )
  {
    v13 = *(_DWORD *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v47, v12);
    if ( v13 != 6119
      && v13 != 6120
      && v13 != 6121
      && v13 != 6122
      && v13 != 6123
      && v13 != 6124
      && v13 != 6125
      && v13 != 6427 )
    {
      v14 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v12);
      v15 = (_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 117476) + 54008);
      *v15 = *v14;
      v15[1] = (unsigned long)v14[1];
      v15[2] = (unsigned long)v14[2];
      v16 = (_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 117476));
      v17 = (_DWORD *)(v16 + 13502);
      v16 += 18884;
      *v16 = *v17;
      v16[1] = (unsigned long)v17[1];
      v16[2] = (unsigned long)v17[2];
      *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 117476) + 42020) = *(_DWORD *)(v2
                                                                         + 4 * (3 * *(_DWORD *)(v2 + 117476) + 13503));
      sprintf((char *const)(v2 + 80), "%s", *(_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 117476) + 54016) + 4);
      v18 = (((UIListBox *)(v2 + 116268)))->UIListBox::LoadListItems((char *)(v2 + 80), 0);
      sprintf(
        (char *const)(v2 + 80),
        (const char *)&dir[20],
        *(_DWORD *)(*(_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 117476) + 54016) + 608) / 2);
      (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(1, v18, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 117476) + 34844));
      (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(2, v18, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 117476) + 42020));
      (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(3, v18, (char *)(v2 + 80), 0);
      v12 = nIndexb;
      ++*(_DWORD *)(v2 + 117476);
    }
    ++v12;
  }
  (((UIListBox *)(v2 + 116268)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 116268)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 117480)))->UIListBox::ClearAll();
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(3);
  nIndexc = 0;
  if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
  {
    v40 = (_DWORD *)(v2 + 43216);
    v19 = (_DWORD *)(v2 + 57596);
    do
    {
      v20 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v47, nIndexc);
      *v19 = *v20;
      v19[1] = (unsigned long)v20[1];
      v19[2] = (unsigned long)v20[2];
      v19[5382] = (unsigned long)*v19;
      v19[5383] = (unsigned long)v19[1];
      v19[5384] = (unsigned long)v19[2];
      ++*(_DWORD *)(v2 + 118688);
      *v40 = v19[1];
      sprintf((char *const)(v2 + 80), "%s", v19[2] + 4);
      v43 = (((UIListBox *)(v2 + 117480)))->UIListBox::LoadListItems((char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v19[2] + 608) / 2);
      (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(1, v43, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(v40 - 1794));
      (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(2, v43, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v40);
      (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(3, v43, (char *)(v2 + 80), 0);
      ++nIndexc;
      ++v40;
      v19 += 3;
    }
    while ( nIndexc < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
  }
  (((UIListBox *)(v2 + 117480)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 117480)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 118692)))->UIListBox::ClearAll();
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(4);
  nIndexd = 0;
  if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
  {
    v41 = (_DWORD *)(v2 + 44412);
    v21 = (_DWORD *)(v2 + 61184);
    do
    {
      v22 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v47, nIndexd);
      *v21 = *v22;
      v21[1] = (unsigned long)v22[1];
      v21[2] = (unsigned long)v22[2];
      v21[5382] = (unsigned long)*v21;
      v21[5383] = (unsigned long)v21[1];
      v21[5384] = (unsigned long)v21[2];
      ++*(_DWORD *)(v2 + 119900);
      *v41 = v21[1];
      sprintf((char *const)(v2 + 80), "%s", v21[2] + 4);
      v44 = (((UIListBox *)(v2 + 118692)))->UIListBox::LoadListItems((char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v21[2] + 608) / 2);
      (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(1, v44, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(v41 - 1794));
      (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(2, v44, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v41);
      (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(3, v44, (char *)(v2 + 80), 0);
      ++nIndexd;
      ++v41;
      v21 += 3;
    }
    while ( nIndexd < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
  }
  (((UIListBox *)(v2 + 118692)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 118692)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 119904)))->UIListBox::ClearAll();
  (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(6);
  v23 = 0;
  for ( nIndexe = 0; v23 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize(); nIndexe = v23 )
  {
    v24 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v47, v23);
    v25 = (unsigned long)*v24;
    v26 = (unsigned long)v24[1];
    v27 = (unsigned long)v24[2];
    if ( *v24 != 8146 && v25 != 8147 && v25 != 8149 && v25 != 8150 && v25 != 8151 && v25 != 8152 )
    {
      v28 = (_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 121112) + 64772);
      *v28 = v25;
      v28[1] = v26;
      v28[2] = v27;
      *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 121112) + 45608) = *(_DWORD *)(v2
                                                                         + 4 * (3 * *(_DWORD *)(v2 + 121112) + 16194));
      v29 = (_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 121112));
      v30 = (_DWORD *)(v29 + 16193);
      v29 += 21575;
      *v29 = *v30;
      v29[1] = (unsigned long)v30[1];
      v29[2] = (unsigned long)v30[2];
      sprintf((char *const)(v2 + 80), "%s", *(_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 121112) + 64780) + 4);
      v31 = (((UIListBox *)(v2 + 119904)))->UIListBox::LoadListItems((char *)(v2 + 80), 0);
      sprintf(
        (char *const)(v2 + 80),
        (const char *)&dir[20],
        *(_DWORD *)(*(_DWORD *)(v2 + 12 * *(_DWORD *)(v2 + 121112) + 64780) + 608) / 2);
      (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(1, v31, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 121112) + 38432));
      (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(2, v31, (char *)(v2 + 80), 0);
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 121112) + 45608));
      (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(3, v31, (char *)(v2 + 80), 0);
      v23 = nIndexe;
      ++*(_DWORD *)(v2 + 121112);
    }
    ++v23;
  }
  (((UIListBox *)(v2 + 119904)))->UIListBox::GetItem();
  result = (((UIListBox *)(v2 + 119904)))->UIListBox::GetItem();
  qmemcpy((void *)(v2 + 98858), v45, 0x702u);
  return result;
}

// 0x00473520
int LineupUI_Render3DModels(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // eax
  _DWORD *v7; // ecx
  int v8; // edx
  UICursor *v9; // ecx
  UIListBox *v10; // edi
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int result; // eax

  v2 = v1;
  v3 = 6;
  v4 = v1 + 105020;
  do
  {
    sub_445E50(v4);
    v4 += 344;
    --v3;
  }
  while ( v3 );
  sub_445E50(v2 + 344 * nVal + 105020);
  LineupUI_InitItemList(nVal);
  *(_DWORD *)(v2 + 121116) = nVal;
  SetEnable((UICaption *)(v2 + 123420));
  SetEnable((UICaption *)(v2 + 123740));
  v5 = *(_DWORD *)(v2 + 121116);
  *(_DWORD *)(v2 + 103892) = 0;
  *(_DWORD *)(v2 + 592) = 0;
  sprintf((char *const)(v2 + 80), "%s %d", g_szCombatFieldName, *(_DWORD *)(v2 + 4 * v5 + 46804));
  SetEnable((UICaption *)(v2 + 124076));
  (**(void ( ***)(int, _DWORD))(v2 + 121156))((int)(v2 + 121156), (_DWORD)(0));
  (**(void ( ***)(int, _DWORD))(v2 + 121500))((int)(v2 + 121500), (_DWORD)(0));
  v6 = 0;
  v7 = (_DWORD *)(v2 + 46804);
  v8 = 6;
  do
  {
    v6 += *v7++;
    --v8;
  }
  while ( v8 );
  sprintf((char *const)(v2 + 80), "%s %d", g_szCombatFieldName, v6);
  SetEnable((UICaption *)(v2 + 124076));
  *(_DWORD *)(v2 + 124260) = nVal;
  switch ( nVal )
  {
    case 0:
      v10 = (UIListBox *)(v2 + 113844);
      (**(void ( ***)(int, int))(v2 + 113844))((int)(v2 + 113844), (int)(1));
      (((UIListBox *)(v2 + 113844)))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))(v2 + 115056))((int)(v2 + 115056), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 116268))((int)(v2 + 116268), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 117480))((int)(v2 + 117480), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 118692))((int)(v2 + 118692), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 119904))((int)(v2 + 119904), (_DWORD)(0));
      LOBYTE(v11) = *(_BYTE *)(v2 + 124264);
      (((UIPushButton *)(v2 + 123572)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Resume_word.tga", v11);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(0);
      goto LABEL_11;
    case 1:
      (**(void ( ***)(int, _DWORD))(v2 + 113844))((int)(v2 + 113844), (_DWORD)(0));
      v10 = (UIListBox *)(v2 + 115056);
      (**(void ( ***)(int, int))(v2 + 115056))((int)(v2 + 115056), (int)(1));
      (((UIListBox *)(v2 + 115056)))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))(v2 + 116268))((int)(v2 + 116268), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 117480))((int)(v2 + 117480), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 118692))((int)(v2 + 118692), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 119904))((int)(v2 + 119904), (_DWORD)(0));
      LOBYTE(v12) = *(_BYTE *)(v2 + 124264);
      (((UIPushButton *)(v2 + 123572)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Treasure_word.tga", v12);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(2);
      goto LABEL_11;
    case 2:
      (**(void ( ***)(int, _DWORD))(v2 + 113844))((int)(v2 + 113844), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 115056))((int)(v2 + 115056), (_DWORD)(0));
      v10 = (UIListBox *)(v2 + 116268);
      (**(void ( ***)(int, int))(v2 + 116268))((int)(v2 + 116268), (int)(1));
      (((UIListBox *)(v2 + 116268)))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))(v2 + 117480))((int)(v2 + 117480), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 118692))((int)(v2 + 118692), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 119904))((int)(v2 + 119904), (_DWORD)(0));
      LOBYTE(v13) = *(_BYTE *)(v2 + 124264);
      (((UIPushButton *)(v2 + 123572)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Attack_word.tga", v13);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(1);
      goto LABEL_11;
    case 3:
      (**(void ( ***)(int, _DWORD))(v2 + 113844))((int)(v2 + 113844), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 115056))((int)(v2 + 115056), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 116268))((int)(v2 + 116268), (_DWORD)(0));
      v10 = (UIListBox *)(v2 + 117480);
      (**(void ( ***)(int, int))(v2 + 117480))((int)(v2 + 117480), (int)(1));
      (((UIListBox *)(v2 + 117480)))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))(v2 + 118692))((int)(v2 + 118692), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 119904))((int)(v2 + 119904), (_DWORD)(0));
      LOBYTE(v14) = *(_BYTE *)(v2 + 124264);
      (((UIPushButton *)(v2 + 123572)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Smelt_word.tga", v14);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(3);
      goto LABEL_11;
    case 4:
      (**(void ( ***)(int, _DWORD))(v2 + 113844))((int)(v2 + 113844), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 115056))((int)(v2 + 115056), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 116268))((int)(v2 + 116268), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 117480))((int)(v2 + 117480), (_DWORD)(0));
      v10 = (UIListBox *)(v2 + 118692);
      (**(void ( ***)(int, int))(v2 + 118692))((int)(v2 + 118692), (int)(1));
      (((UIListBox *)(v2 + 118692)))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))(v2 + 119904))((int)(v2 + 119904), (_DWORD)(0));
      LOBYTE(v15) = *(_BYTE *)(v2 + 124264);
      (((UIPushButton *)(v2 + 123572)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Ancient_word.tga", v15);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(4);
LABEL_11:
      if ( (((UIListBox *)v10))->UIListBox::GetItemData() > 0 )
        goto LABEL_14;
      break;
    case 5:
      (**(void ( ***)(int, _DWORD))(v2 + 113844))((int)(v2 + 113844), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 115056))((int)(v2 + 115056), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 116268))((int)(v2 + 116268), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 117480))((int)(v2 + 117480), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))(v2 + 118692))((int)(v2 + 118692), (_DWORD)(0));
      (**(void ( ***)(int, int))(v2 + 119904))((int)(v2 + 119904), (int)(1));
      (((UIListBox *)(v2 + 119904)))->UIListBox::GetItem();
      LOBYTE(v16) = *(_BYTE *)(v2 + 124264);
      (((UIPushButton *)(v2 + 123572)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Equip_word.tga", v16);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(6);
      if ( (((UIListBox *)(v2 + 119904)))->UIListBox::GetItemData() > 0 )
LABEL_14:
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1007, 0, 0);
      break;
    default:
      break;
  }
  (((UICursor *)v9))->UICursor::_todo_541CC0();
  return result;
}

// 0x004739F0
int LineupUI_BuildEquipList(int nVal)
{
  int result; // eax
  int *v2; // ecx
  int v4; // ebx
  int v5; // esi
  int v6; // eax
  int v7; // edx
  int v8; // ebp
  int *v9; // edx
  int v10; // edx
  int *v11; // ebx
  int v12; // edx
  int v13; // eax
  int v14; // ebp
  int v15; // [esp+0x8] [ebp-0xC]
  int v16; // [esp+0xC] [ebp-0x8]
  int v17; // [esp+0xC] [ebp-0x8]
  int *v18; // [esp+0x10] [ebp-0x4]
  int nVala; // [esp+0x18] [ebp+0x4]

  if ( nVal < 6 )
  {
    result = 0;
    nVala = 0;
    switch ( nVal )
    {
      case 0:
        result = (unsigned long)v2[28763];
        goto LABEL_9;
      case 1:
        result = (unsigned long)v2[29066];
        goto LABEL_9;
      case 2:
        result = (unsigned long)v2[29369];
        goto LABEL_9;
      case 3:
        result = (unsigned long)v2[29672];
        goto LABEL_9;
      case 4:
        result = (unsigned long)v2[29975];
        goto LABEL_9;
      case 5:
        result = (unsigned long)v2[30278];
LABEL_9:
        nVala = result;
        break;
      default:
        break;
    }
    v4 = 0;
    v15 = 0;
    if ( result > 0 )
    {
      do
      {
        v5 = 0;
        v6 = 299 * nVal;
        v7 = 299 * nVal + v4;
        v8 = (unsigned long)v2[2 * v7 + 4525];
        v18 = (int *)&v2[2 * v7 + 4525];
        v9 = (int *)&v2[897 * nVal + 11708];
        while ( v8 != *v9 )
        {
          ++v5;
          v9 += 3;
          if ( v5 >= nVala )
            goto LABEL_16;
        }
        v10 = v6 + v5 + 8113;
        v11 = (int *)&v2[2 * v6 + 4526 + 2 * v4];
        v16 = (unsigned long)v2[v10];
        v2[v10] = (unsigned long)*v11;
        v2[v6 + 8113 + v15] = v16;
        v12 = v6 + v5;
        v13 = v6 + v5 + 2263;
        v14 = (unsigned long)v2[2 * v12 + 4525];
        v17 = (unsigned long)v2[2 * v13];
        v2[2 * v12 + 4525] = (unsigned long)v2[3 * v12 + 11708];
        v2[2 * v13] = (unsigned long)*v11;
        *v18 = v14;
        *v11 = v17;
        v4 = v15;
LABEL_16:
        result = nVala;
        v15 = ++v4;
      }
      while ( v4 < nVala );
    }
  }
  return result;
}

// 0x00473B50
int LineupUI_InitItemList(int nVal)
{
  int v1; // ecx
  int result; // eax
  int v3; // esi
  signed int v4; // ebp
  _DWORD *v5; // edi
  _DWORD *v6; // eax
  _DWORD *v7; // edx
  _DWORD *v8; // ecx
  int v9; // eax
  _DWORD *v10; // ebp
  char *v11; // eax
  int v12; // ecx
  UIListBox *v13; // ebp
  signed int v14; // ebx
  int *v15; // ecx
  int v16; // eax
  int v17; // edx
  int v18; // edi
  _DWORD *v19; // ecx
  _DWORD *v20; // eax
  _DWORD *v21; // ecx
  _DWORD *v22; // ebx
  int v23; // ebp
  int v24; // eax
  bool v25; // cc
  signed int v26; // ebx
  int *v27; // ecx
  int v28; // eax
  int v29; // edx
  int v30; // edi
  _DWORD *v31; // ecx
  _DWORD *v32; // eax
  _DWORD *v33; // ecx
  _DWORD *v34; // ebx
  int v35; // ebp
  int v36; // eax
  signed int v37; // ebp
  _DWORD *v38; // edi
  _DWORD *v39; // eax
  _DWORD *v40; // edx
  _DWORD *v41; // ecx
  int v42; // eax
  _DWORD *v43; // ebp
  char *v44; // eax
  int v45; // ecx
  signed int v46; // ebp
  _DWORD *v47; // edi
  _DWORD *v48; // eax
  _DWORD *v49; // edx
  _DWORD *v50; // ecx
  int v51; // eax
  _DWORD *v52; // ebp
  char *v53; // eax
  int v54; // ecx
  signed int v55; // ebx
  int *v56; // ecx
  int v57; // eax
  int v58; // edx
  int v59; // edi
  _DWORD *v60; // ecx
  _DWORD *v61; // eax
  _DWORD *v62; // ecx
  _DWORD *v63; // ebx
  int v64; // ebp
  int v65; // eax
  int ListItems; // [esp+0x10] [ebp-0x68]
  int v67; // [esp+0x10] [ebp-0x68]
  int v68; // [esp+0x10] [ebp-0x68]
  int v69; // [esp+0x10] [ebp-0x68]
  int v70; // [esp+0x10] [ebp-0x68]
  int v71; // [esp+0x10] [ebp-0x68]
  gbColorQuad v72; // [esp+0x18] [ebp-0x60] BYREF
  gbColorQuad v73; // [esp+0x1C] [ebp-0x5C] BYREF
  gbColorQuad v74; // [esp+0x20] [ebp-0x58] BYREF
  gbColorQuad v75; // [esp+0x24] [ebp-0x54] BYREF
  gbColorQuad v76; // [esp+0x28] [ebp-0x50] BYREF
  gbColorQuad v77; // [esp+0x2C] [ebp-0x4C] BYREF
  char pOut[12]; // [esp+0x30] [ebp-0x48] BYREF
  char v79[12]; // [esp+0x3C] [ebp-0x3C] BYREF
  char v80[12]; // [esp+0x48] [ebp-0x30] BYREF
  char v81[12]; // [esp+0x54] [ebp-0x24] BYREF
  char v82[12]; // [esp+0x60] [ebp-0x18] BYREF
  int v83[3]; // [esp+0x6C] [ebp-0xC] BYREF
  int nVala; // [esp+0x7C] [ebp+0x4]
  UIListBox *nValb; // [esp+0x7C] [ebp+0x4]
  UIListBox *nValc; // [esp+0x7C] [ebp+0x4]
  int nVald; // [esp+0x7C] [ebp+0x4]
  int nVale; // [esp+0x7C] [ebp+0x4]
  UIListBox *nValf; // [esp+0x7C] [ebp+0x4]
  void *pItem; // [esp+0x80] [ebp+0x8]
  char *pItema; // [esp+0x80] [ebp+0x8]
  char *pItemb; // [esp+0x80] [ebp+0x8]
  char *pItemc; // [esp+0x80] [ebp+0x8]
  char *pItemd; // [esp+0x80] [ebp+0x8]
  char *pIteme; // [esp+0x80] [ebp+0x8]
  char *pItemf; // [esp+0x80] [ebp+0x8]

  result = nVal;
  v3 = v1;
  switch ( nVal )
  {
    case 0:
      (((UIListBox *)(v1 + 113844)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(0);
      if ( (int)pItem >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(pItem);
      v4 = 0;
      if ( *(int *)(v3 + 115052) > 0 )
      {
        v5 = (_DWORD *)(v3 + 46832);
        do
        {
          v6 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v4++);
          *v5 = *v6;
          v5[1] = (unsigned long)v6[1];
          v7 = (_DWORD *)v5;
          v5[2] = (unsigned long)v6[2];
          v8 = (_DWORD *)(v5 + 5382);
          v9 = (unsigned long)*v5;
          v5 += 3;
          *v8 = v9;
          v8[1] = (unsigned long)v7[1];
          v8[2] = (unsigned long)v7[2];
        }
        while ( v4 < *(_DWORD *)(v3 + 115052) );
      }
      LineupUI_BuildEquipList(0);
      pItema = 0;
      if ( *(int *)(v3 + 115052) > 0 )
      {
        nVala = v3 + 46840;
        v10 = (_DWORD *)(v3 + 32452);
        do
        {
          v10[1794] = *(_DWORD *)(nVala - 4);
          sprintf((char *const)(v3 + 80), "%s", *(_DWORD *)nVala + 4);
          ListItems = (((UIListBox *)(v3 + 113844)))->UIListBox::LoadListItems((char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)nVala + 608) / 2);
          (((UIListBox *)(v3 + 113844)))->UIListBox::SetMouseMoveSel(1, ListItems, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *v10);
          (((UIListBox *)(v3 + 113844)))->UIListBox::SetMouseMoveSel(2, ListItems, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], v10[1794]);
          (((UIListBox *)(v3 + 113844)))->UIListBox::SetMouseMoveSel(3, ListItems, (char *)(v3 + 80), 0);
          if ( (int)*v10 <= 0 )
          {
            v11 = (char *)pItema;
            if ( (int)pItema < 0 || (int)pItema >= *(_DWORD *)(v3 + 114348) )
              v12 = 0;
            else
              v12 = *(_DWORD *)((char *)v10 + *(_DWORD *)(v3 + 114344) - v3 - 32452);
            *(_DWORD *)(v12 + 68) = *(_DWORD *)(v3 + 113848);
          }
          else
          {
            UITabCtrl_SetItemParam((int)pItema);
            v11 = (char *)pItema;
          }
          ++v10;
          nVala += 12;
          pItema = (char *)(v11 + 1);
        }
        while ( (int)(v11 + 1) < *(_DWORD *)(v3 + 115052) );
      }
      (((UIListBox *)(v3 + 113844)))->UIListBox::GetItem();
      return (((UIListBox *)(v3 + 113844)))->UIListBox::GetItem();
    case 1:
      v13 = (UIListBox *)(v1 + 115056);
      nValc = (UIListBox *)(v1 + 115056);
      (((UIListBox *)(v1 + 115056)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(1);
      v26 = 0;
      if ( (int)pItem >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(pItem);
      *(_DWORD *)(v3 + 116264) = 0;
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        do
        {
          v27 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v80, v26);
          v28 = (unsigned long)*v27;
          v29 = (unsigned long)v27[1];
          v30 = (unsigned long)v27[2];
          if ( *v27 != 6409 && v28 != 6410 && v28 != 6411 && v28 != 6412 && v28 != 6413 && v28 != 6408 && v28 != 6427 )
          {
            v31 = (_DWORD *)(v3 + 12 * *(_DWORD *)(v3 + 116264) + 50420);
            *v31 = v28;
            v31[1] = v29;
            v31[2] = v30;
            v32 = (_DWORD *)(v3 + 12 * *(_DWORD *)(v3 + 116264));
            v33 = (_DWORD *)(v32 + 12605);
            v32 += 17987;
            *v32 = *v33;
            v32[1] = (unsigned long)v33[1];
            v32[2] = (unsigned long)v33[2];
            ++*(_DWORD *)(v3 + 116264);
          }
          ++v26;
        }
        while ( v26 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      LineupUI_BuildEquipList(1);
      pItemc = 0;
      if ( *(int *)(v3 + 116264) > 0 )
      {
        v34 = (_DWORD *)(v3 + 33648);
        v68 = v3 + 50428;
        do
        {
          v34[1794] = *(_DWORD *)(v68 - 4);
          sprintf((char *const)(v3 + 80), "%s", *(_DWORD *)v68 + 4);
          v35 = (((UIListBox *)nValc))->UIListBox::LoadListItems((char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)v68 + 608) / 2);
          (((UIListBox *)nValc))->UIListBox::SetMouseMoveSel(1, v35, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *v34);
          (((UIListBox *)nValc))->UIListBox::SetMouseMoveSel(2, v35, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], v34[1794]);
          (((UIListBox *)nValc))->UIListBox::SetMouseMoveSel(3, v35, (char *)(v3 + 80), 0);
          if ( (int)*v34 <= 0 )
          {
            if ( (int)pItemc < 0 || (int)pItemc >= *(_DWORD *)(v3 + 115560) )
              v36 = 0;
            else
              v36 = *(_DWORD *)((char *)v34 + -33648 - v3 + *(_DWORD *)(v3 + 115556));
            *(_DWORD *)(v36 + 68) = *(_DWORD *)(v3 + 115060);
          }
          else
          {
            UITabCtrl_SetItemParam((int)pItemc);
          }
          ++v34;
          v25 = (int)++pItemc < *(_DWORD *)(v3 + 116264);
          v68 += 12;
        }
        while ( v25 );
        v13 = (UIListBox *)(v3 + 115056);
      }
      goto LABEL_119;
    case 2:
      v13 = (UIListBox *)(v1 + 116268);
      nValb = (UIListBox *)(v1 + 116268);
      (((UIListBox *)(v1 + 116268)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(2);
      v14 = 0;
      if ( (int)pItem >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(pItem);
      *(_DWORD *)(v3 + 117476) = 0;
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        do
        {
          v15 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v79, v14);
          v16 = (unsigned long)*v15;
          v17 = (unsigned long)v15[1];
          v18 = (unsigned long)v15[2];
          if ( *v15 != 6119
            && v16 != 6120
            && v16 != 6121
            && v16 != 6122
            && v16 != 6123
            && v16 != 6124
            && v16 != 6125
            && v16 != 6427 )
          {
            v19 = (_DWORD *)(v3 + 12 * *(_DWORD *)(v3 + 117476) + 54008);
            *v19 = v16;
            v19[1] = v17;
            v19[2] = v18;
            v20 = (_DWORD *)(v3 + 12 * *(_DWORD *)(v3 + 117476));
            v21 = (_DWORD *)(v20 + 13502);
            v20 += 18884;
            *v20 = *v21;
            v20[1] = (unsigned long)v21[1];
            v20[2] = (unsigned long)v21[2];
            ++*(_DWORD *)(v3 + 117476);
          }
          ++v14;
        }
        while ( v14 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      LineupUI_BuildEquipList(2);
      pItemb = 0;
      if ( *(int *)(v3 + 117476) > 0 )
      {
        v22 = (_DWORD *)(v3 + 34844);
        v67 = v3 + 54016;
        do
        {
          v22[1794] = *(_DWORD *)(v67 - 4);
          sprintf((char *const)(v3 + 80), "%s", *(_DWORD *)v67 + 4);
          v23 = (((UIListBox *)nValb))->UIListBox::LoadListItems((char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)v67 + 608) / 2);
          (((UIListBox *)nValb))->UIListBox::SetMouseMoveSel(1, v23, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *v22);
          (((UIListBox *)nValb))->UIListBox::SetMouseMoveSel(2, v23, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], v22[1794]);
          (((UIListBox *)nValb))->UIListBox::SetMouseMoveSel(3, v23, (char *)(v3 + 80), 0);
          if ( (int)*v22 <= 0 )
          {
            if ( (int)pItemb < 0 || (int)pItemb >= *(_DWORD *)(v3 + 116772) )
              v24 = 0;
            else
              v24 = *(_DWORD *)((char *)v22 + -34844 - v3 + *(_DWORD *)(v3 + 116768));
            *(_DWORD *)(v24 + 68) = *(_DWORD *)(v3 + 116272);
          }
          else
          {
            UITabCtrl_SetItemParam((int)pItemb);
          }
          ++v22;
          v25 = (int)++pItemb < *(_DWORD *)(v3 + 117476);
          v67 += 12;
        }
        while ( v25 );
        v13 = (UIListBox *)(v3 + 116268);
      }
      goto LABEL_119;
    case 3:
      (((UIListBox *)(v1 + 117480)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(3);
      if ( (int)pItem >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(pItem);
      v37 = 0;
      if ( *(int *)(v3 + 118688) > 0 )
      {
        v38 = (_DWORD *)(v3 + 57596);
        do
        {
          v39 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v81, v37++);
          *v38 = *v39;
          v38[1] = (unsigned long)v39[1];
          v40 = (_DWORD *)v38;
          v38[2] = (unsigned long)v39[2];
          v41 = (_DWORD *)(v38 + 5382);
          v42 = (unsigned long)*v38;
          v38 += 3;
          *v41 = v42;
          v41[1] = (unsigned long)v40[1];
          v41[2] = (unsigned long)v40[2];
        }
        while ( v37 < *(_DWORD *)(v3 + 118688) );
      }
      LineupUI_BuildEquipList(3);
      pItemd = 0;
      if ( *(int *)(v3 + 118688) > 0 )
      {
        nVald = v3 + 57604;
        v43 = (_DWORD *)(v3 + 36040);
        do
        {
          v43[1794] = *(_DWORD *)(nVald - 4);
          sprintf((char *const)(v3 + 80), "%s", *(_DWORD *)nVald + 4);
          v69 = (((UIListBox *)(v3 + 117480)))->UIListBox::LoadListItems((char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)nVald + 608) / 2);
          (((UIListBox *)(v3 + 117480)))->UIListBox::SetMouseMoveSel(1, v69, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *v43);
          (((UIListBox *)(v3 + 117480)))->UIListBox::SetMouseMoveSel(2, v69, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], v43[1794]);
          (((UIListBox *)(v3 + 117480)))->UIListBox::SetMouseMoveSel(3, v69, (char *)(v3 + 80), 0);
          if ( (int)*v43 <= 0 )
          {
            v44 = (char *)pItemd;
            if ( (int)pItemd < 0 || (int)pItemd >= *(_DWORD *)(v3 + 117984) )
              v45 = 0;
            else
              v45 = *(_DWORD *)((char *)v43 + *(_DWORD *)(v3 + 117980) - v3 - 36040);
            *(_DWORD *)(v45 + 68) = *(_DWORD *)(v3 + 117484);
          }
          else
          {
            UITabCtrl_SetItemParam((int)pItemd);
            v44 = (char *)pItemd;
          }
          ++v43;
          nVald += 12;
          pItemd = (char *)(v44 + 1);
        }
        while ( (int)(v44 + 1) < *(_DWORD *)(v3 + 118688) );
      }
      (((UIListBox *)(v3 + 117480)))->UIListBox::GetItem();
      return (((UIListBox *)(v3 + 117480)))->UIListBox::GetItem();
    case 4:
      (((UIListBox *)(v1 + 118692)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(4);
      if ( (int)pItem >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(pItem);
      v46 = 0;
      if ( *(int *)(v3 + 119900) > 0 )
      {
        v47 = (_DWORD *)(v3 + 61184);
        do
        {
          v48 = (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v82, v46++);
          *v47 = *v48;
          v47[1] = (unsigned long)v48[1];
          v49 = (_DWORD *)v47;
          v47[2] = (unsigned long)v48[2];
          v50 = (_DWORD *)(v47 + 5382);
          v51 = (unsigned long)*v47;
          v47 += 3;
          *v50 = v51;
          v50[1] = (unsigned long)v49[1];
          v50[2] = (unsigned long)v49[2];
        }
        while ( v46 < *(_DWORD *)(v3 + 119900) );
      }
      LineupUI_BuildEquipList(4);
      pIteme = 0;
      if ( *(int *)(v3 + 119900) > 0 )
      {
        nVale = v3 + 61192;
        v52 = (_DWORD *)(v3 + 37236);
        do
        {
          v52[1794] = *(_DWORD *)(nVale - 4);
          sprintf((char *const)(v3 + 80), "%s", *(_DWORD *)nVale + 4);
          v70 = (((UIListBox *)(v3 + 118692)))->UIListBox::LoadListItems((char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)nVale + 608) / 2);
          (((UIListBox *)(v3 + 118692)))->UIListBox::SetMouseMoveSel(1, v70, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *v52);
          (((UIListBox *)(v3 + 118692)))->UIListBox::SetMouseMoveSel(2, v70, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], v52[1794]);
          (((UIListBox *)(v3 + 118692)))->UIListBox::SetMouseMoveSel(3, v70, (char *)(v3 + 80), 0);
          if ( (int)*v52 <= 0 )
          {
            v53 = (char *)pIteme;
            if ( (int)pIteme < 0 || (int)pIteme >= *(_DWORD *)(v3 + 119196) )
              v54 = 0;
            else
              v54 = *(_DWORD *)((char *)v52 + -37236 - v3 + *(_DWORD *)(v3 + 119192));
            *(_DWORD *)(v54 + 68) = *(_DWORD *)(v3 + 118696);
          }
          else
          {
            UITabCtrl_SetItemParam((int)pIteme);
            v53 = (char *)pIteme;
          }
          ++v52;
          nVale += 12;
          pIteme = (char *)(v53 + 1);
        }
        while ( (int)(v53 + 1) < *(_DWORD *)(v3 + 119900) );
      }
      (((UIListBox *)(v3 + 118692)))->UIListBox::GetItem();
      return (((UIListBox *)(v3 + 118692)))->UIListBox::GetItem();
    case 5:
      v13 = (UIListBox *)(v1 + 119904);
      nValf = (UIListBox *)(v1 + 119904);
      (((UIListBox *)(v1 + 119904)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(6);
      v55 = 0;
      if ( (int)pItem >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(pItem);
      *(_DWORD *)(v3 + 121112) = 0;
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        do
        {
          v56 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v83, v55);
          v57 = (unsigned long)*v56;
          v58 = (unsigned long)v56[1];
          v59 = (unsigned long)v56[2];
          if ( *v56 != 8146 && v57 != 8147 && v57 != 8149 && v57 != 8150 && v57 != 8151 && v57 != 8152 )
          {
            v60 = (_DWORD *)(v3 + 12 * *(_DWORD *)(v3 + 121112) + 64772);
            *v60 = v57;
            v60[1] = v58;
            v60[2] = v59;
            v61 = (_DWORD *)(v3 + 12 * *(_DWORD *)(v3 + 121112));
            v62 = (_DWORD *)(v61 + 16193);
            v61 += 21575;
            *v61 = *v62;
            v61[1] = (unsigned long)v62[1];
            v61[2] = (unsigned long)v62[2];
            ++*(_DWORD *)(v3 + 121112);
          }
          ++v55;
        }
        while ( v55 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      LineupUI_BuildEquipList(5);
      pItemf = 0;
      if ( *(int *)(v3 + 121112) > 0 )
      {
        v63 = (_DWORD *)(v3 + 38432);
        v71 = v3 + 64780;
        do
        {
          v63[1794] = *(_DWORD *)(v71 - 4);
          sprintf((char *const)(v3 + 80), "%s", *(_DWORD *)v71 + 4);
          v64 = (((UIListBox *)nValf))->UIListBox::LoadListItems((char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *(_DWORD *)(*(_DWORD *)v71 + 608) / 2);
          (((UIListBox *)nValf))->UIListBox::SetMouseMoveSel(1, v64, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], *v63);
          (((UIListBox *)nValf))->UIListBox::SetMouseMoveSel(2, v64, (char *)(v3 + 80), 0);
          sprintf((char *const)(v3 + 80), (const char *)&dir[20], v63[1794]);
          (((UIListBox *)nValf))->UIListBox::SetMouseMoveSel(3, v64, (char *)(v3 + 80), 0);
          if ( (int)*v63 <= 0 )
          {
            if ( (int)pItemf < 0 || (int)pItemf >= *(_DWORD *)(v3 + 120408) )
              v65 = 0;
            else
              v65 = *(_DWORD *)((char *)v63 + *(_DWORD *)(v3 + 120404) - v3 - 38432);
            *(_DWORD *)(v65 + 68) = *(_DWORD *)(v3 + 119908);
          }
          else
          {
            UITabCtrl_SetItemParam((int)pItemf);
          }
          ++v63;
          v25 = (int)++pItemf < *(_DWORD *)(v3 + 121112);
          v71 += 12;
        }
        while ( v25 );
        v13 = (UIListBox *)(v3 + 119904);
      }
LABEL_119:
      (((UIListBox *)v13))->UIListBox::GetItem();
      result = (((UIListBox *)v13))->UIListBox::GetItem();
      break;
    default:
      return result;
  }
  return result;
}

// 0x00474990
char GetUpdateFlag(_BYTE *_this)
{
  char result; // al
  int v3; // eax
  int v4; // eax

  result = _this[103789];
  if ( !result )
  {
    result = g_Input.KeyInfo[7].PressTime;
    if ( g_Input.KeyInfo[7].PressTime == 1 )
      result = (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 788, 0);
    if ( g_Input.KeyInfo[10].PressTime == 1 )
      return (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 821, 0);
    if ( g_Input.KeyInfo[9].PressTime == 1 )
      return (*(int ( **)(_BYTE *, int, int, _DWORD))(*(_DWORD *)_this + 24))(_this, 1001, 822, 0);
    if ( g_Input.KeyInfo[6].PressTime == 1 )
      return (*(int ( **)(_BYTE *, int, int, int))(*(_DWORD *)_this + 24))(_this, 1009, 801, 30933628);
    if ( g_Input.KeyInfo[2].PressTime == 1 )
    {
      v3 = *((_DWORD *)_this + 31065) - 1;
      *((_DWORD *)_this + 31065) = v3;
      if ( v3 < 0 )
        *((_DWORD *)_this + 31065) = 0;
      return (*(int ( **)(_BYTE *, int, _DWORD, _DWORD))(*(_DWORD *)_this + 24))(
               _this,
               1001,
               *(&dword_56B77C + *((_DWORD *)_this + 31065)),
               0);
    }
    if ( g_Input.KeyInfo[3].PressTime == 1 )
    {
      v4 = *((_DWORD *)_this + 31065) + 1;
      *((_DWORD *)_this + 31065) = v4;
      if ( v4 > 5 )
        *((_DWORD *)_this + 31065) = 5;
      return (*(int ( **)(_BYTE *, int, _DWORD, _DWORD))(*(_DWORD *)_this + 24))(
               _this,
               1001,
               *(&dword_56B77C + *((_DWORD *)_this + 31065)),
               0);
    }
    if ( g_Input.KeyInfo[8].PressTime == 1 )
      return (*(int ( **)(_BYTE *, int, _DWORD, _DWORD))(*(_DWORD *)_this + 24))(_this, 789, 0, 0);
  }
  return result;
}

// 0x00474AB0
int LineupUI_ProcessMouseInput(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  float v4; // st7
  __int16 v5; // fps
  bool v6; // c0
  char v7; // c2
  bool v8; // c3
  float v9; // st7
  __int16 v10; // fps
  bool v11; // c0
  char v12; // c2
  bool v13; // c3
  POINT pt; // [esp+0x10] [ebp-0x8] BYREF

  v2 = v1;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
  if ( PtInRect((const RECT *)(v2 + 121140), pt) && (g_Input.KeyInfo[0].Data & 0xF) != 1
    || ((((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt), PtInRect((const RECT *)(v2 + 121124), pt))
    && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    *(_BYTE *)(v2 + 121868) = 0;
    *(_BYTE *)(v2 + 121869) = 0;
  }
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
  if ( PtInRect((const RECT *)(v2 + 121140), pt) && (result = g_Input.KeyInfo[0].Data & 0xF, (_BYTE)result == 1) )
  {
    if ( !*(_BYTE *)(v2 + 121869) )
    {
      v4 = *(float *)&nVal + *(float *)(v2 + 121864);
      *(_BYTE *)(v2 + 121868) = 1;
      *(_BYTE *)(v2 + 121869) = 0;
      *(float *)(v2 + 121864) = v4;
      v6 = v4 < 0.5f;
      v7 = 0;
      v8 = v4 == 0.5f;
      LOWORD(result) = v5;
      if ( v4 > 0.5f )
        return (*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1001, 822, 0);
    }
  }
  else
  {
    (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
    result = PtInRect((const RECT *)(v2 + 121124), pt);
    if ( result && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      if ( !*(_BYTE *)(v2 + 121868) )
      {
        v9 = *(float *)&nVal + *(float *)(v2 + 121864);
        *(_BYTE *)(v2 + 121868) = 0;
        *(_BYTE *)(v2 + 121869) = 1;
        *(float *)(v2 + 121864) = v9;
        v11 = v9 < 0.5f;
        v12 = 0;
        v13 = v9 == 0.5f;
        LOWORD(result) = v10;
        if ( v9 > 0.5f )
          return (*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1001, 821, 0);
      }
    }
    else
    {
      *(_DWORD *)(v2 + 121864) = 0;
    }
  }
  return result;
}

// 0x00474C80
int LineupUI_BuildListItems(int nVal)
{
  int *v1; // ecx
  int *v2; // esi
  int v3; // ebx
  _DWORD *v4; // edi
  int *v5; // ebp
  int v6; // eax
  int v7; // ecx
  _DWORD *v8; // ebp
  int *v9; // edx
  bool v10; // cc
  int v11; // ebp
  int *v12; // edi
  int v13; // eax
  int v14; // edi
  _DWORD *v15; // ebx
  _DWORD *v16; // ebp
  int v17; // eax
  UIListBox *v18; // edi
  int v19; // ebx
  _DWORD *v20; // edi
  int *v21; // ebp
  int v22; // eax
  int v23; // ecx
  _DWORD *v24; // ebp
  int *v25; // edx
  int v26; // ebp
  int *v27; // edi
  int v28; // eax
  int v29; // edi
  _DWORD *v30; // ebx
  _DWORD *v31; // ebp
  int v32; // eax
  int v33; // ebx
  _DWORD *v34; // edi
  int *v35; // ebp
  int v36; // eax
  int v37; // ecx
  _DWORD *v38; // ebp
  int *v39; // edx
  int v40; // ebp
  int *v41; // edi
  int v42; // eax
  int v43; // edi
  _DWORD *v44; // ebx
  _DWORD *v45; // ebp
  int v46; // eax
  int v47; // ebx
  _DWORD *v48; // edi
  int *v49; // ebp
  int v50; // eax
  int v51; // ecx
  _DWORD *v52; // ebp
  int *v53; // ecx
  int v54; // ebp
  int *v55; // edi
  int v56; // eax
  int v57; // edi
  _DWORD *v58; // ebx
  _DWORD *v59; // ebp
  int v60; // eax
  int v61; // ebx
  _DWORD *v62; // edi
  int *v63; // ebp
  int v64; // eax
  int v65; // ecx
  _DWORD *v66; // ebp
  int *v67; // edx
  int v68; // ebp
  int *v69; // edi
  int v70; // eax
  int v71; // edi
  _DWORD *v72; // ebx
  _DWORD *v73; // ebp
  int v74; // eax
  int v75; // ebp
  int *v76; // ebx
  _DWORD *v77; // edi
  int v78; // eax
  int v79; // ecx
  _DWORD *v80; // ebp
  int *v81; // edx
  int v82; // ebp
  int *v83; // ebx
  int v84; // edi
  int v85; // eax
  _DWORD *v86; // ebx
  int v87; // eax
  int result; // eax
  int v89; // [esp+0x10] [ebp-0x8]
  int v90; // [esp+0x10] [ebp-0x8]
  int v91; // [esp+0x10] [ebp-0x8]
  int v92; // [esp+0x10] [ebp-0x8]
  int v93; // [esp+0x10] [ebp-0x8]
  int v94; // [esp+0x10] [ebp-0x8]
  _DWORD *v95; // [esp+0x10] [ebp-0x8]
  int *v96; // [esp+0x14] [ebp-0x4]
  int *v97; // [esp+0x14] [ebp-0x4]
  int *v98; // [esp+0x14] [ebp-0x4]
  int *v99; // [esp+0x14] [ebp-0x4]
  int *v100; // [esp+0x14] [ebp-0x4]
  int *v101; // [esp+0x14] [ebp-0x4]

  v2 = (int *)v1;
  switch ( nVal )
  {
    case 0:
      v3 = 0;
      if ( v1[28763] > 0 )
      {
        v4 = (_DWORD *)v1 + 17091;
        v5 = (int *)(v1 + 8113);
        do
        {
          if ( *v5 > 0 )
          {
            *(&g_RoleSlotBuf.dword_17AA450 + 147) += v2[11701];
            v2[11701] = 0;
            v6 = (unsigned long)*v5;
            *(v4 - 5382) = *v5;
            v7 = (unsigned long)(*v4 - v6);
            *v4 = v7;
            v5[1794] = v7;
            if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(v4 - 5383) == 2 )
              v5[14359] = 1;
          }
          ++v3;
          ++v5;
          v4 += 3;
        }
        while ( v3 < v2[28763] );
      }
      v89 = 0;
      if ( v2[28763] > 0 )
      {
        v8 = (_DWORD *)v2 + 9907;
        v96 = (int *)(v2 + 17090);
        do
        {
          if ( v8[12565] != 1 )
          {
            v9 = (int *)&v2[3 * v2[25163] + 11708];
            *v9 = *v96;
            v9[1] = (unsigned long)v96[1];
            v9[2] = (unsigned long)v96[2];
            v2[v2[25163] + 8113] = 0;
            v2[v2[25163] + 9907] = *v8;
            sprintf((char *const)v2 + 80, (const char *)&dir[20], v2[v2[25163] + 8113]);
            (((UIListBox *)(v2 + 28461)))->UIListBox::SetMouseMoveSel(2, v2[25163], (char *)v2 + 80, 0);
            sprintf((char *const)v2 + 80, (const char *)&dir[20], *v8);
            (((UIListBox *)(v2 + 28461)))->UIListBox::SetMouseMoveSel(3, v2[25163]++, (char *)v2 + 80, 0);
          }
          ++v8;
          v10 = ++v89 < v2[28763];
          v96 += 3;
        }
        while ( v10 );
      }
      v11 = (unsigned long)(v2[28763] - 1);
      if ( v11 >= 0 )
      {
        v12 = (int *)&v2[v11 + 22472];
        do
        {
          if ( *v12 == 1 )
          {
            *v12 = 0;
            (((UIListBox *)(v2 + 28461)))->UIListBox::AdjustScroll(v11);
            *(v12 - 14359) = 0;
            *(v12 - 12565) = 0;
          }
          --v11;
          --v12;
        }
        while ( v11 >= 0 );
      }
      v13 = (unsigned long)v2[25163];
      v14 = 0;
      v2[28763] = v13;
      if ( v13 > 0 )
      {
        v15 = (_DWORD *)v2 + 9907;
        v16 = (_DWORD *)v2 + 17090;
        do
        {
          *v16 = *(v16 - 5382);
          v16[1] = *(v16 - 5381);
          v16[2] = *(v16 - 5380);
          *v15 = *(v16 - 5381);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *(v15 - 1794));
          (((UIListBox *)(v2 + 28461)))->UIListBox::SetMouseMoveSel(2, v14, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *v15);
          (((UIListBox *)(v2 + 28461)))->UIListBox::SetMouseMoveSel(3, v14, (char *)v2 + 80, 0);
          if ( v14 < 0 || v14 >= v2[28587] )
            v17 = 0;
          else
            v17 = *(_DWORD *)((char *)v15 + -39628 - (_DWORD)v2 + v2[28586]);
          ++v14;
          *(_DWORD *)(v17 + 68) = (unsigned long)v2[28462];
          v16 += 3;
          ++v15;
        }
        while ( v14 < v2[28763] );
      }
      v2[25163] = 0;
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(0);
      sprintf((char *const)v2 + 80, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
      SetEnable((UICaption *)(v2 + 30977));
      v18 = (UIListBox *)(v2 + 28461);
      goto LABEL_151;
    case 1:
      v19 = 0;
      if ( v1[29066] > 0 )
      {
        v20 = (_DWORD *)v1 + 17988;
        v21 = (int *)(v1 + 8412);
        do
        {
          if ( *v21 > 0 )
          {
            *(&g_RoleSlotBuf.dword_17AA450 + 147) += v2[11702];
            v2[11702] = 0;
            v22 = (unsigned long)*v21;
            *(v20 - 5382) = *v21;
            v23 = (unsigned long)(*v20 - v22);
            *v20 = v23;
            v21[1794] = v23;
            if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(v20 - 5383) == 2 )
              v21[14359] = 1;
          }
          ++v19;
          ++v21;
          v20 += 3;
        }
        while ( v19 < v2[29066] );
      }
      v90 = 0;
      if ( v2[29066] > 0 )
      {
        v24 = (_DWORD *)v2 + 10206;
        v97 = (int *)(v2 + 17987);
        do
        {
          if ( !v24[12565] )
          {
            v25 = (int *)&v2[3 * v2[25163] + 12605];
            *v25 = *v97;
            v25[1] = (unsigned long)v97[1];
            v25[2] = (unsigned long)v97[2];
            v2[v2[25163] + 8412] = 0;
            v2[v2[25163] + 10206] = *v24;
            sprintf((char *const)v2 + 80, (const char *)&dir[20], v2[v2[25163] + 8412]);
            (((UIListBox *)(v2 + 28764)))->UIListBox::SetMouseMoveSel(2, v2[25163], (char *)v2 + 80, 0);
            sprintf((char *const)v2 + 80, (const char *)&dir[20], *v24);
            (((UIListBox *)(v2 + 28764)))->UIListBox::SetMouseMoveSel(3, v2[25163]++, (char *)v2 + 80, 0);
          }
          ++v24;
          v10 = ++v90 < v2[29066];
          v97 += 3;
        }
        while ( v10 );
      }
      v26 = (unsigned long)(v2[29066] - 1);
      if ( v26 >= 0 )
      {
        v27 = (int *)&v2[v26 + 22771];
        do
        {
          if ( *v27 == 1 )
          {
            *v27 = 0;
            (((UIListBox *)(v2 + 28764)))->UIListBox::AdjustScroll(v26);
            *(v27 - 14359) = 0;
            *(v27 - 12565) = 0;
          }
          --v26;
          --v27;
        }
        while ( v26 >= 0 );
      }
      v28 = (unsigned long)v2[25163];
      v29 = 0;
      v2[29066] = v28;
      if ( v28 > 0 )
      {
        v30 = (_DWORD *)v2 + 10206;
        v31 = (_DWORD *)v2 + 17987;
        do
        {
          *v31 = *(v31 - 5382);
          v31[1] = *(v31 - 5381);
          v31[2] = *(v31 - 5380);
          *v30 = *(v31 - 5381);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *(v30 - 1794));
          (((UIListBox *)(v2 + 28764)))->UIListBox::SetMouseMoveSel(2, v29, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *v30);
          (((UIListBox *)(v2 + 28764)))->UIListBox::SetMouseMoveSel(3, v29, (char *)v2 + 80, 0);
          if ( v29 < 0 || v29 >= v2[28890] )
            v32 = 0;
          else
            v32 = *(_DWORD *)((char *)v30 + v2[28889] + -40824 - (_DWORD)v2);
          ++v29;
          *(_DWORD *)(v32 + 68) = (unsigned long)v2[28765];
          v31 += 3;
          ++v30;
        }
        while ( v29 < v2[29066] );
      }
      v2[25163] = 0;
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(1);
      sprintf((char *const)v2 + 80, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
      SetEnable((UICaption *)(v2 + 30977));
      v18 = (UIListBox *)(v2 + 28764);
      goto LABEL_151;
    case 2:
      v33 = 0;
      if ( v1[29369] > 0 )
      {
        v34 = (_DWORD *)v1 + 18885;
        v35 = (int *)(v1 + 8711);
        do
        {
          if ( *v35 > 0 )
          {
            *(&g_RoleSlotBuf.dword_17AA450 + 147) += v2[11703];
            v2[11703] = 0;
            v36 = (unsigned long)*v35;
            *(v34 - 5382) = *v35;
            v37 = (unsigned long)(*v34 - v36);
            *v34 = v37;
            v35[1794] = v37;
            if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(v34 - 5383) == 2 )
              v35[14359] = 1;
          }
          ++v33;
          ++v35;
          v34 += 3;
        }
        while ( v33 < v2[29369] );
      }
      v91 = 0;
      if ( v2[29369] > 0 )
      {
        v38 = (_DWORD *)v2 + 10505;
        v98 = (int *)(v2 + 18884);
        do
        {
          if ( !v38[12565] )
          {
            v39 = (int *)&v2[3 * v2[25163] + 13502];
            *v39 = *v98;
            v39[1] = (unsigned long)v98[1];
            v39[2] = (unsigned long)v98[2];
            v2[v2[25163] + 8711] = 0;
            v2[v2[25163] + 10505] = *v38;
            sprintf((char *const)v2 + 80, (const char *)&dir[20], v2[v2[25163] + 8711]);
            (((UIListBox *)(v2 + 29067)))->UIListBox::SetMouseMoveSel(2, v2[25163], (char *)v2 + 80, 0);
            sprintf((char *const)v2 + 80, (const char *)&dir[20], *v38);
            (((UIListBox *)(v2 + 29067)))->UIListBox::SetMouseMoveSel(3, v2[25163]++, (char *)v2 + 80, 0);
          }
          ++v38;
          v10 = ++v91 < v2[29369];
          v98 += 3;
        }
        while ( v10 );
      }
      v40 = (unsigned long)(v2[29369] - 1);
      if ( v40 >= 0 )
      {
        v41 = (int *)&v2[v40 + 23070];
        do
        {
          if ( *v41 == 1 )
          {
            *v41 = 0;
            (((UIListBox *)(v2 + 29067)))->UIListBox::AdjustScroll(v40);
            *(v41 - 14359) = 0;
            *(v41 - 12565) = 0;
          }
          --v40;
          --v41;
        }
        while ( v40 >= 0 );
      }
      v42 = (unsigned long)v2[25163];
      v43 = 0;
      v2[29369] = v42;
      if ( v42 > 0 )
      {
        v44 = (_DWORD *)v2 + 8711;
        v45 = (_DWORD *)v2 + 18884;
        do
        {
          *v45 = *(v45 - 5382);
          v45[1] = *(v45 - 5381);
          v45[2] = *(v45 - 5380);
          v44[1794] = *(v45 - 5381);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *v44);
          (((UIListBox *)(v2 + 29067)))->UIListBox::SetMouseMoveSel(2, v43, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], v44[1794]);
          (((UIListBox *)(v2 + 29067)))->UIListBox::SetMouseMoveSel(3, v43, (char *)v2 + 80, 0);
          if ( v43 < 0 || v43 >= v2[29193] )
            v46 = 0;
          else
            v46 = *(_DWORD *)((char *)v44 + v2[29192] - (_DWORD)v2 - 34844);
          ++v43;
          *(_DWORD *)(v46 + 68) = (unsigned long)v2[29068];
          v45 += 3;
          ++v44;
        }
        while ( v43 < v2[29369] );
      }
      v2[25163] = 0;
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(2);
      sprintf((char *const)v2 + 80, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
      SetEnable((UICaption *)(v2 + 30977));
      v18 = (UIListBox *)(v2 + 29067);
      goto LABEL_151;
    case 3:
      v47 = 0;
      if ( v1[29672] > 0 )
      {
        v48 = (_DWORD *)v1 + 19782;
        v49 = (int *)(v1 + 9010);
        do
        {
          if ( *v49 > 0 )
          {
            *(&g_RoleSlotBuf.dword_17AA450 + 147) += v2[11704];
            v2[11704] = 0;
            v50 = (unsigned long)*v49;
            *(v48 - 5382) = *v49;
            v51 = (unsigned long)(*v48 - v50);
            *v48 = v51;
            v49[1794] = v51;
            if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(v48 - 5383) == 2 )
              v49[14359] = 1;
          }
          ++v47;
          ++v49;
          v48 += 3;
        }
        while ( v47 < v2[29672] );
      }
      v92 = 0;
      if ( v2[29672] > 0 )
      {
        v52 = (_DWORD *)v2 + 10804;
        v99 = (int *)(v2 + 19781);
        do
        {
          if ( !v52[12565] )
          {
            v53 = (int *)&v2[3 * v2[25163] + 14399];
            *v53 = *v99;
            v53[1] = (unsigned long)v99[1];
            v53[2] = (unsigned long)v99[2];
            v2[v2[25163] + 9010] = 0;
            v2[v2[25163] + 10804] = *v52;
            sprintf((char *const)v2 + 80, (const char *)&dir[20], v2[v2[25163] + 9010]);
            (((UIListBox *)(v2 + 29370)))->UIListBox::SetMouseMoveSel(2, v2[25163], (char *)v2 + 80, 0);
            sprintf((char *const)v2 + 80, (const char *)&dir[20], *v52);
            (((UIListBox *)(v2 + 29370)))->UIListBox::SetMouseMoveSel(3, v2[25163]++, (char *)v2 + 80, 0);
          }
          ++v52;
          v10 = ++v92 < v2[29672];
          v99 += 3;
        }
        while ( v10 );
      }
      v54 = (unsigned long)(v2[29672] - 1);
      if ( v54 >= 0 )
      {
        v55 = (int *)&v2[v54 + 23369];
        do
        {
          if ( *v55 == 1 )
          {
            *v55 = 0;
            (((UIListBox *)(v2 + 29370)))->UIListBox::AdjustScroll(v54);
            *(v55 - 14359) = 0;
            *(v55 - 12565) = 0;
          }
          --v54;
          --v55;
        }
        while ( v54 >= 0 );
      }
      v56 = (unsigned long)v2[25163];
      v57 = 0;
      v2[29672] = v56;
      if ( v56 > 0 )
      {
        v58 = (_DWORD *)v2 + 10804;
        v59 = (_DWORD *)v2 + 19781;
        do
        {
          *v59 = *(v59 - 5382);
          v59[1] = *(v59 - 5381);
          v59[2] = *(v59 - 5380);
          *v58 = *(v59 - 5381);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *(v58 - 1794));
          (((UIListBox *)(v2 + 29370)))->UIListBox::SetMouseMoveSel(2, v57, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *v58);
          (((UIListBox *)(v2 + 29370)))->UIListBox::SetMouseMoveSel(3, v57, (char *)v2 + 80, 0);
          if ( v57 < 0 || v57 >= v2[29496] )
            v60 = 0;
          else
            v60 = *(_DWORD *)((char *)v58 + v2[29495] - (_DWORD)v2 - 43216);
          ++v57;
          *(_DWORD *)(v60 + 68) = (unsigned long)v2[29371];
          v59 += 3;
          ++v58;
        }
        while ( v57 < v2[29672] );
      }
      v2[25163] = 0;
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(3);
      sprintf((char *const)v2 + 80, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
      SetEnable((UICaption *)(v2 + 30977));
      v18 = (UIListBox *)(v2 + 29370);
      goto LABEL_151;
    case 4:
      v61 = 0;
      if ( v1[29975] > 0 )
      {
        v62 = (_DWORD *)v1 + 20679;
        v63 = (int *)(v1 + 9309);
        do
        {
          if ( *v63 > 0 )
          {
            *(&g_RoleSlotBuf.dword_17AA450 + 147) += v2[11705];
            v2[11705] = 0;
            v64 = (unsigned long)*v63;
            *(v62 - 5382) = *v63;
            v65 = (unsigned long)(*v62 - v64);
            *v62 = v65;
            v63[1794] = v65;
            if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(v62 - 5383) == 2 )
              v63[14359] = 1;
          }
          ++v61;
          ++v63;
          v62 += 3;
        }
        while ( v61 < v2[29975] );
      }
      v93 = 0;
      if ( v2[29975] > 0 )
      {
        v66 = (_DWORD *)v2 + 11103;
        v100 = (int *)(v2 + 20678);
        do
        {
          if ( !v66[12565] )
          {
            v67 = (int *)&v2[3 * v2[25163] + 15296];
            *v67 = *v100;
            v67[1] = (unsigned long)v100[1];
            v67[2] = (unsigned long)v100[2];
            v2[v2[25163] + 9309] = 0;
            v2[v2[25163] + 11103] = *v66;
            sprintf((char *const)v2 + 80, (const char *)&dir[20], v2[v2[25163] + 9309]);
            (((UIListBox *)(v2 + 29673)))->UIListBox::SetMouseMoveSel(2, v2[25163], (char *)v2 + 80, 0);
            sprintf((char *const)v2 + 80, (const char *)&dir[20], *v66);
            (((UIListBox *)(v2 + 29673)))->UIListBox::SetMouseMoveSel(3, v2[25163]++, (char *)v2 + 80, 0);
          }
          ++v66;
          v10 = ++v93 < v2[29975];
          v100 += 3;
        }
        while ( v10 );
      }
      v68 = (unsigned long)(v2[29975] - 1);
      if ( v68 >= 0 )
      {
        v69 = (int *)&v2[v68 + 23668];
        do
        {
          if ( *v69 == 1 )
          {
            *v69 = 0;
            (((UIListBox *)(v2 + 29673)))->UIListBox::AdjustScroll(v68);
            *(v69 - 14359) = 0;
            *(v69 - 12565) = 0;
          }
          --v68;
          --v69;
        }
        while ( v68 >= 0 );
      }
      v70 = (unsigned long)v2[25163];
      v71 = 0;
      v2[29975] = v70;
      if ( v70 > 0 )
      {
        v72 = (_DWORD *)v2 + 11103;
        v73 = (_DWORD *)v2 + 20678;
        do
        {
          *v73 = *(v73 - 5382);
          v73[1] = *(v73 - 5381);
          v73[2] = *(v73 - 5380);
          *v72 = *(v73 - 5381);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *(v72 - 1794));
          (((UIListBox *)(v2 + 29673)))->UIListBox::SetMouseMoveSel(2, v71, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *v72);
          (((UIListBox *)(v2 + 29673)))->UIListBox::SetMouseMoveSel(3, v71, (char *)v2 + 80, 0);
          if ( v71 < 0 || v71 >= v2[29799] )
            v74 = 0;
          else
            v74 = *(_DWORD *)((char *)v72 + v2[29798] + -44412 - (_DWORD)v2);
          ++v71;
          *(_DWORD *)(v74 + 68) = (unsigned long)v2[29674];
          v73 += 3;
          ++v72;
        }
        while ( v71 < v2[29975] );
      }
      v2[25163] = 0;
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(4);
      sprintf((char *const)v2 + 80, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
      SetEnable((UICaption *)(v2 + 30977));
      v18 = (UIListBox *)(v2 + 29673);
      goto LABEL_151;
    case 5:
      v75 = 0;
      if ( v1[30278] > 0 )
      {
        v76 = (int *)(v1 + 9608);
        v77 = (_DWORD *)v1 + 21576;
        do
        {
          if ( *v76 > 0 )
          {
            *(&g_RoleSlotBuf.dword_17AA450 + 147) += v2[11706];
            v2[11706] = 0;
            v78 = (unsigned long)*v76;
            *(v77 - 5382) = *v76;
            v79 = (unsigned long)(*v77 - v78);
            *v77 = v79;
            v76[1794] = v79;
            if ( (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(v77 - 5383) == 2 )
              v76[14359] = 1;
            if ( *((_BYTE *)v2 + v75 + 98559) && *v76 == *(v77 - 5382) )
            {
              v76[14359] = 1;
              *((_BYTE *)v2 + v75 + 100353) = 0;
              *((_BYTE *)v2 + v75 + 98559) = 0;
            }
          }
          ++v75;
          ++v76;
          v77 += 3;
        }
        while ( v75 < v2[30278] );
      }
      v94 = 0;
      if ( v2[30278] > 0 )
      {
        v80 = (_DWORD *)v2 + 11402;
        v101 = (int *)(v2 + 21575);
        do
        {
          if ( v80[12565] != 1 )
          {
            *((_BYTE *)v2 + v2[25163] + 98559) = *((_BYTE *)v2 + v94 + 100353);
            v81 = (int *)&v2[3 * v2[25163] + 16193];
            *v81 = *v101;
            v81[1] = (unsigned long)v101[1];
            v81[2] = (unsigned long)v101[2];
            v2[v2[25163] + 9608] = 0;
            v2[v2[25163] + 11402] = *v80;
            sprintf((char *const)v2 + 80, (const char *)&dir[20], v2[v2[25163] + 9608]);
            (((UIListBox *)(v2 + 29976)))->UIListBox::SetMouseMoveSel(2, v2[25163], (char *)v2 + 80, 0);
            sprintf((char *const)v2 + 80, (const char *)&dir[20], *v80);
            (((UIListBox *)(v2 + 29976)))->UIListBox::SetMouseMoveSel(3, v2[25163]++, (char *)v2 + 80, 0);
          }
          ++v80;
          v10 = ++v94 < v2[30278];
          v101 += 3;
        }
        while ( v10 );
      }
      v82 = (unsigned long)(v2[30278] - 1);
      if ( v82 < 0 )
      {
        v84 = 0;
      }
      else
      {
        v83 = (int *)&v2[v82 + 23967];
        v84 = 0;
        do
        {
          if ( *v83 == 1 )
          {
            *v83 = 0;
            (((UIListBox *)(v2 + 29976)))->UIListBox::AdjustScroll(v82);
            *(v83 - 14359) = 0;
            *(v83 - 12565) = 0;
          }
          --v82;
          --v83;
        }
        while ( v82 >= 0 );
      }
      v85 = (unsigned long)v2[25163];
      v2[30278] = v85;
      if ( v85 > 0 )
      {
        v95 = (_DWORD *)v2 + 11402;
        v86 = (_DWORD *)v2 + 21575;
        do
        {
          *((_BYTE *)v2 + v84 + 100353) = *((_BYTE *)v2 + v84 + 98559);
          *v86 = *(v86 - 5382);
          v86[1] = *(v86 - 5381);
          v86[2] = *(v86 - 5380);
          *v95 = *(v86 - 5381);
          sprintf((char *const)v2 + 80, "%s", *(v86 - 5380) + 4);
          (((UIListBox *)(v2 + 29976)))->UIListBox::SetMouseMoveSel(0, v84, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *(_DWORD *)(*(v86 - 5380) + 608) / 2);
          (((UIListBox *)(v2 + 29976)))->UIListBox::SetMouseMoveSel(1, v84, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *(v95 - 1794));
          (((UIListBox *)(v2 + 29976)))->UIListBox::SetMouseMoveSel(2, v84, (char *)v2 + 80, 0);
          sprintf((char *const)v2 + 80, (const char *)&dir[20], *v95);
          (((UIListBox *)(v2 + 29976)))->UIListBox::SetMouseMoveSel(3, v84, (char *)v2 + 80, 0);
          if ( v84 < 0 || v84 >= v2[30102] )
            v87 = 0;
          else
            v87 = *(_DWORD *)((char *)v95 + v2[30101] - (_DWORD)v2 - 45608);
          *(_DWORD *)(v87 + 68) = (unsigned long)v2[29977];
          ++v84;
          v86 += 3;
          ++v95;
        }
        while ( v84 < v2[30278] );
      }
      v2[25163] = 0;
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(6);
      sprintf((char *const)v2 + 80, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
      SetEnable((UICaption *)(v2 + 30977));
      v18 = (UIListBox *)(v2 + 29976);
LABEL_151:
      (((UIListBox *)v18))->UIListBox::GetItem();
      (((UIListBox *)v18))->UIListBox::GetItem();
      break;
    default:
      break;
  }
  memset(v2 + 4525, 0, 0x3810u);
  v2[148] = -1;
  SetEnable((UICaption *)(v2 + 30855));
  SetEnable((UICaption *)(v2 + 30935));
  v2[25973] = 0;
  sprintf((char *const)v2 + 80, "%s %d", g_szCombatFieldName, v2[nVal + 11701]);
  SetEnable((UICaption *)(v2 + 31019));
  (*(void ( **)(int *, _DWORD))v2[30289])(v2 + 30289, 0);
  result = (*(int ( **)(int *, _DWORD))v2[30375])(v2 + 30375, 0);
  LOBYTE(result) = g_bListNeedsRefresh;
  if ( g_bListNeedsRefresh )
    g_bListNeedsRefresh = 0;
  return result;
}

// 0x00475FC0
int LineupUI_RefreshDisplay(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int i; // esi
  int v4; // eax
  int result; // eax
  int v6; // [esp+0x0] [ebp-0x8]

  v2 = v1;
  for ( i = 0; i < 6; ++i )
    LineupUI_BuildListItems(i);
  LineupUI_RefreshDisplayEx(v6);
  v4 = *(_DWORD *)(v2 + 124248);
  if ( !v4 )
    return UIFrameWnd_OnPaintUpdate(0);
  result = v4 - 1;
  if ( !result )
    return CUtil_Update(2);
  return result;
}

// 0x00476010
int LineupUI_PopulateList(int nVal)
{
  int *v1; // ecx
  int v2; // ebx
  int *v3; // esi
  int v4; // edi
  int v5; // eax
  UIListBox *v6; // edi
  int v7; // edi
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  _DWORD *v18; // [esp+0x10] [ebp-0x8]
  _DWORD *v19; // [esp+0x10] [ebp-0x8]
  _DWORD *v20; // [esp+0x10] [ebp-0x8]
  _DWORD *v21; // [esp+0x10] [ebp-0x8]
  _DWORD *v22; // [esp+0x10] [ebp-0x8]
  _DWORD *v23; // [esp+0x10] [ebp-0x8]
  int v24; // [esp+0x14] [ebp-0x4]
  int v25; // [esp+0x14] [ebp-0x4]
  int v26; // [esp+0x14] [ebp-0x4]
  int v27; // [esp+0x14] [ebp-0x4]
  int v28; // [esp+0x14] [ebp-0x4]
  int v29; // [esp+0x14] [ebp-0x4]

  v2 = nVal;
  v3 = (int *)v1;
  switch ( nVal )
  {
    case 0:
      v4 = 0;
      if ( v1[28763] > 0 )
      {
        v18 = (_DWORD *)v1 + 9907;
        v24 = -39628 - (_DWORD)v1;
        do
        {
          *(v18 - 1794) = 0;
          sprintf((char *const)v3 + 80, (const char *)&dir[20], 0);
          (((UIListBox *)(v3 + 28461)))->UIListBox::SetMouseMoveSel(2, v4, (char *)v3 + 80, 0);
          sprintf((char *const)v3 + 80, (const char *)&dir[20], *v18);
          (((UIListBox *)(v3 + 28461)))->UIListBox::SetMouseMoveSel(3, v4, (char *)v3 + 80, 0);
          if ( v4 < 0 || v4 >= v3[28587] )
            v5 = 0;
          else
            v5 = *(_DWORD *)((char *)v18 + v24 + v3[28586]);
          ++v4;
          *(_DWORD *)(v5 + 68) = (unsigned long)v3[28462];
          ++v18;
        }
        while ( v4 < v3[28763] );
        v2 = nVal;
      }
      v6 = (UIListBox *)(v3 + 28461);
      goto LABEL_56;
    case 1:
      v7 = 0;
      if ( v1[29066] > 0 )
      {
        v19 = (_DWORD *)v1 + 10206;
        v25 = -40824 - (_DWORD)v1;
        do
        {
          *(v19 - 1794) = 0;
          sprintf((char *const)v3 + 80, (const char *)&dir[20], 0);
          (((UIListBox *)(v3 + 28764)))->UIListBox::SetMouseMoveSel(2, v7, (char *)v3 + 80, 0);
          sprintf((char *const)v3 + 80, (const char *)&dir[20], *v19);
          (((UIListBox *)(v3 + 28764)))->UIListBox::SetMouseMoveSel(3, v7, (char *)v3 + 80, 0);
          if ( v7 < 0 || v7 >= v3[28890] )
            v8 = 0;
          else
            v8 = *(_DWORD *)((char *)v19 + v25 + v3[28889]);
          ++v7;
          *(_DWORD *)(v8 + 68) = (unsigned long)v3[28765];
          ++v19;
        }
        while ( v7 < v3[29066] );
        v2 = nVal;
      }
      v6 = (UIListBox *)(v3 + 28764);
      goto LABEL_56;
    case 2:
      v9 = 0;
      if ( v1[29369] > 0 )
      {
        v20 = (_DWORD *)v1 + 10505;
        v26 = -42020 - (_DWORD)v1;
        do
        {
          *(v20 - 1794) = 0;
          sprintf((char *const)v3 + 80, (const char *)&dir[20], 0);
          (((UIListBox *)(v3 + 29067)))->UIListBox::SetMouseMoveSel(2, v9, (char *)v3 + 80, 0);
          sprintf((char *const)v3 + 80, (const char *)&dir[20], *v20);
          (((UIListBox *)(v3 + 29067)))->UIListBox::SetMouseMoveSel(3, v9, (char *)v3 + 80, 0);
          if ( v9 < 0 || v9 >= v3[29193] )
            v10 = 0;
          else
            v10 = *(_DWORD *)((char *)v20 + v26 + v3[29192]);
          ++v9;
          *(_DWORD *)(v10 + 68) = (unsigned long)v3[29068];
          ++v20;
        }
        while ( v9 < v3[29369] );
        v2 = nVal;
      }
      v6 = (UIListBox *)(v3 + 29067);
      goto LABEL_56;
    case 3:
      v11 = 0;
      if ( v1[29672] > 0 )
      {
        v21 = (_DWORD *)v1 + 10804;
        v27 = -43216 - (_DWORD)v1;
        do
        {
          *(v21 - 1794) = 0;
          sprintf((char *const)v3 + 80, (const char *)&dir[20], 0);
          (((UIListBox *)(v3 + 29370)))->UIListBox::SetMouseMoveSel(2, v11, (char *)v3 + 80, 0);
          sprintf((char *const)v3 + 80, (const char *)&dir[20], *v21);
          (((UIListBox *)(v3 + 29370)))->UIListBox::SetMouseMoveSel(3, v11, (char *)v3 + 80, 0);
          if ( v11 < 0 || v11 >= v3[29496] )
            v12 = 0;
          else
            v12 = *(_DWORD *)((char *)v21 + v27 + v3[29495]);
          *(_DWORD *)(v12 + 68) = (unsigned long)v3[29371];
          ++v11;
          ++v21;
        }
        while ( v11 < v3[29672] );
        v2 = nVal;
      }
      v6 = (UIListBox *)(v3 + 29370);
      goto LABEL_56;
    case 4:
      v13 = 0;
      if ( v1[29975] > 0 )
      {
        v22 = (_DWORD *)v1 + 11103;
        v28 = -44412 - (_DWORD)v1;
        do
        {
          *(v22 - 1794) = 0;
          sprintf((char *const)v3 + 80, (const char *)&dir[20], 0);
          (((UIListBox *)(v3 + 29673)))->UIListBox::SetMouseMoveSel(2, v13, (char *)v3 + 80, 0);
          sprintf((char *const)v3 + 80, (const char *)&dir[20], *v22);
          (((UIListBox *)(v3 + 29673)))->UIListBox::SetMouseMoveSel(3, v13, (char *)v3 + 80, 0);
          if ( v13 < 0 || v13 >= v3[29799] )
            v14 = 0;
          else
            v14 = *(_DWORD *)((char *)v22 + v28 + v3[29798]);
          ++v13;
          *(_DWORD *)(v14 + 68) = (unsigned long)v3[29674];
          ++v22;
        }
        while ( v13 < v3[29975] );
        v2 = nVal;
      }
      v6 = (UIListBox *)(v3 + 29673);
      goto LABEL_56;
    case 5:
      v15 = 0;
      if ( v1[30278] > 0 )
      {
        v23 = (_DWORD *)v1 + 11402;
        v29 = -45608 - (_DWORD)v1;
        do
        {
          *(v23 - 1794) = 0;
          sprintf((char *const)v3 + 80, (const char *)&dir[20], 0);
          (((UIListBox *)(v3 + 29976)))->UIListBox::SetMouseMoveSel(2, v15, (char *)v3 + 80, 0);
          sprintf((char *const)v3 + 80, (const char *)&dir[20], *v23);
          (((UIListBox *)(v3 + 29976)))->UIListBox::SetMouseMoveSel(3, v15, (char *)v3 + 80, 0);
          if ( v15 < 0 || v15 >= v3[30102] )
            v16 = 0;
          else
            v16 = *(_DWORD *)((char *)v23 + v29 + v3[30101]);
          *(_DWORD *)(v16 + 68) = (unsigned long)v3[29977];
          ++v15;
          ++v23;
        }
        while ( v15 < v3[30278] );
        v2 = nVal;
      }
      v6 = (UIListBox *)(v3 + 29976);
LABEL_56:
      (((UIListBox *)v6))->UIListBox::GetItem();
      (((UIListBox *)v6))->UIListBox::GetItem();
      break;
    default:
      break;
  }
  memset(&v3[598 * v2 + 4525], 0, 0x958u);
  v3[148] = -1;
  SetEnable((UICaption *)(v3 + 30855));
  SetEnable((UICaption *)(v3 + 30935));
  v3[25973] = 0;
  v3[v2 + 11701] = 0;
  sprintf((char *const)v3 + 80, "%s %d", g_szCombatFieldName, 0);
  SetEnable((UICaption *)(v3 + 31019));
  (*(void ( **)(int *, _DWORD))v3[30289])(v3 + 30289, 0);
  return (*(int ( **)(int *, _DWORD))v3[30375])(v3 + 30375, 0);
}

// 0x004765F0
int LineupUI_SetItemDisplay(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  CScreenMode *Instance; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int *v14; // edi
  int v15; // ebx
  int v16; // edx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  int *v21; // edi
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // ecx
  int *v28; // edi
  int v29; // ebx
  int v30; // edx
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // ecx
  int *v35; // edi
  int v36; // ebx
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // ecx
  int *v42; // edi
  int v43; // ebx
  int v44; // edx
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // ecx
  int *v49; // edi
  int v50; // ebx
  int v51; // eax
  int v52; // eax
  int *v53; // ecx
  int v54; // edx
  int v55; // edi
  char *v56; // [esp-0x8] [ebp-0x28]
  gbColorQuad v57; // [esp+0xC] [ebp-0x14] BYREF
  gbColorQuad v58; // [esp+0x10] [ebp-0x10] BYREF
  gbColorQuad v59; // [esp+0x14] [ebp-0xC] BYREF
  gbColorQuad v60; // [esp+0x18] [ebp-0x8] BYREF
  gbColorQuad v61; // [esp+0x1C] [ebp-0x4] BYREF

  v2 = v1;
  result = *(_DWORD *)(v1 + 592);
  if ( result >= 0 )
  {
    v4 = nVal;
    v5 = 299 * nVal;
    v6 = 299 * nVal + result;
    *(_DWORD *)(v1 + 121120) = *(_DWORD *)(v1 + 4 * (3 * v6 + 11709));
    ++*(_DWORD *)(v1 + 4 * v6 + 32452);
    v7 = v5 + *(_DWORD *)(v1 + 592);
    v8 = *(_DWORD *)(v1 + 4 * v7 + 39628);
    if ( *(_DWORD *)(v2 + 4 * v7 + 32452) < v8 )
    {
      sub_445E50(v2 + 121156);
      sub_445E50(v2 + 121500);
      v56 = (char *)off_5B9DF4;
    }
    else
    {
      *(_DWORD *)(v2 + 4 * v7 + 32452) = v8;
      sub_445E50(v2 + 121156);
      sub_445E50(v2 + 121500);
      v56 = off_5B9DF0[0];
    }
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v56, 1);
    *(_DWORD *)(v2 + 8 * (v5 + *(_DWORD *)(v2 + 592)) + 18100) = *(_DWORD *)(v2
                                                                           + 12 * (v5 + *(_DWORD *)(v2 + 592))
                                                                           + 46832);
    *(_DWORD *)(v2 + 8 * (*(_DWORD *)(v2 + 592) + v5) + 18104) = *(_DWORD *)(v2
                                                                           + 4 * (*(_DWORD *)(v2 + 592) + v5)
                                                                           + 32452);
    *(_BYTE *)(v2 + 124244) = 1;
    switch ( v4 )
    {
      case 0:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 32452));
        (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 39628));
        (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v10 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v10 + 32452) <= 0 )
        {
          if ( v10 < 0 || v10 >= *(_DWORD *)(v2 + 114348) )
            v11 = 0;
          else
            v11 = *(_DWORD *)(*(_DWORD *)(v2 + 114344) + 4 * v10);
          *(_DWORD *)(v11 + 68) = *(_DWORD *)(v2 + 113848);
        }
        else
        {
          ((gbColorQuad *)&nVal)->gbColorQuad::gbColorQuad(0x1Fu, 0xFBu, 0xFFu, 0xFFu);
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124244) )
        {
          *(_DWORD *)(v2 + 46804) = *(_DWORD *)(v2 + 32452) * (*(_DWORD *)(*(_DWORD *)(v2 + 46840) + 608) / 2);
          v12 = *(_DWORD *)(v2 + 115052);
          if ( v12 > 1 )
          {
            v13 = v2 + 32456;
            v14 = (int *)(v2 + 46852);
            v15 = v12 - 1;
            do
            {
              v16 = (unsigned long)*v14;
              v13 += 4;
              v14 += 3;
              --v15;
              *(_DWORD *)(v2 + 46804) += *(_DWORD *)(v13 - 4) * (*(_DWORD *)(v16 + 608) / 2);
            }
            while ( v15 );
          }
        }
        break;
      case 1:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 33648));
        (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 40824));
        (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v17 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v17 + 33648) <= 0 )
        {
          if ( v17 < 0 || v17 >= *(_DWORD *)(v2 + 115560) )
            v18 = 0;
          else
            v18 = *(_DWORD *)(*(_DWORD *)(v2 + 115556) + 4 * v17);
          *(_DWORD *)(v18 + 68) = *(_DWORD *)(v2 + 115060);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124244) )
        {
          *(_DWORD *)(v2 + 46808) = *(_DWORD *)(v2 + 33648) * (*(_DWORD *)(*(_DWORD *)(v2 + 50428) + 608) / 2);
          v19 = *(_DWORD *)(v2 + 116264);
          if ( v19 > 1 )
          {
            v20 = v2 + 33652;
            v21 = (int *)(v2 + 50440);
            v22 = v19 - 1;
            do
            {
              v23 = (unsigned long)*v21;
              v20 += 4;
              v21 += 3;
              --v22;
              *(_DWORD *)(v2 + 46808) += *(_DWORD *)(v20 - 4) * (*(_DWORD *)(v23 + 608) / 2);
            }
            while ( v22 );
          }
        }
        break;
      case 2:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 34844));
        (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 42020));
        (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v24 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v24 + 34844) <= 0 )
        {
          if ( v24 < 0 || v24 >= *(_DWORD *)(v2 + 116772) )
            v25 = 0;
          else
            v25 = *(_DWORD *)(*(_DWORD *)(v2 + 116768) + 4 * v24);
          *(_DWORD *)(v25 + 68) = *(_DWORD *)(v2 + 116272);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124244) )
        {
          *(_DWORD *)(v2 + 46812) = *(_DWORD *)(v2 + 34844) * (*(_DWORD *)(*(_DWORD *)(v2 + 54016) + 608) / 2);
          v26 = *(_DWORD *)(v2 + 117476);
          if ( v26 > 1 )
          {
            v27 = v2 + 34848;
            v28 = (int *)(v2 + 54028);
            v29 = v26 - 1;
            do
            {
              v30 = (unsigned long)*v28;
              v27 += 4;
              v28 += 3;
              --v29;
              *(_DWORD *)(v2 + 46812) += *(_DWORD *)(v27 - 4) * (*(_DWORD *)(v30 + 608) / 2);
            }
            while ( v29 );
          }
        }
        break;
      case 3:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 36040));
        (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 43216));
        (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v31 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v31 + 36040) <= 0 )
        {
          if ( v31 < 0 || v31 >= *(_DWORD *)(v2 + 117984) )
            v32 = 0;
          else
            v32 = *(_DWORD *)(*(_DWORD *)(v2 + 117980) + 4 * v31);
          *(_DWORD *)(v32 + 68) = *(_DWORD *)(v2 + 117484);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124244) )
        {
          *(_DWORD *)(v2 + 46816) = *(_DWORD *)(v2 + 36040) * (*(_DWORD *)(*(_DWORD *)(v2 + 57604) + 608) / 2);
          v33 = *(_DWORD *)(v2 + 118688);
          if ( v33 > 1 )
          {
            v34 = v2 + 36044;
            v35 = (int *)(v2 + 57616);
            v36 = v33 - 1;
            do
            {
              v37 = (unsigned long)*v35;
              v34 += 4;
              v35 += 3;
              --v36;
              *(_DWORD *)(v2 + 46816) += *(_DWORD *)(v34 - 4) * (*(_DWORD *)(v37 + 608) / 2);
            }
            while ( v36 );
          }
        }
        break;
      case 4:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 37236));
        (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 44412));
        (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v38 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v38 + 37236) <= 0 )
        {
          if ( v38 < 0 || v38 >= *(_DWORD *)(v2 + 119196) )
            v39 = 0;
          else
            v39 = *(_DWORD *)(*(_DWORD *)(v2 + 119192) + 4 * v38);
          *(_DWORD *)(v39 + 68) = *(_DWORD *)(v2 + 118696);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124244) )
        {
          *(_DWORD *)(v2 + 46820) = *(_DWORD *)(v2 + 37236) * (*(_DWORD *)(*(_DWORD *)(v2 + 61192) + 608) / 2);
          v40 = *(_DWORD *)(v2 + 119900);
          if ( v40 > 1 )
          {
            v41 = v2 + 37240;
            v42 = (int *)(v2 + 61204);
            v43 = v40 - 1;
            do
            {
              v44 = (unsigned long)*v42;
              v41 += 4;
              v42 += 3;
              --v43;
              *(_DWORD *)(v2 + 46820) += *(_DWORD *)(v41 - 4) * (*(_DWORD *)(v44 + 608) / 2);
            }
            while ( v43 );
          }
        }
        break;
      case 5:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 38432));
        (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 45608));
        (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v45 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v45 + 38432) <= 0 )
        {
          if ( v45 < 0 || v45 >= *(_DWORD *)(v2 + 120408) )
            v46 = 0;
          else
            v46 = *(_DWORD *)(*(_DWORD *)(v2 + 120404) + 4 * v45);
          *(_DWORD *)(v46 + 68) = *(_DWORD *)(v2 + 119908);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124244) )
        {
          *(_DWORD *)(v2 + 46824) = *(_DWORD *)(v2 + 38432) * (*(_DWORD *)(*(_DWORD *)(v2 + 64780) + 608) / 2);
          v47 = *(_DWORD *)(v2 + 121112);
          if ( v47 > 1 )
          {
            v48 = v2 + 38436;
            v49 = (int *)(v2 + 64792);
            v50 = v47 - 1;
            do
            {
              v51 = (unsigned long)*v49;
              v48 += 4;
              v49 += 3;
              --v50;
              *(_DWORD *)(v2 + 46824) += *(_DWORD *)(v48 - 4) * (*(_DWORD *)(v51 + 608) / 2);
            }
            while ( v50 );
          }
        }
        break;
      default:
        break;
    }
    v52 = 0;
    v53 = (int *)(v2 + 46804);
    v54 = 6;
    do
    {
      v55 = (unsigned long)(*v53++);
      v52 += v55;
      --v54;
    }
    while ( v54 );
    sprintf((char *const)(v2 + 80), "%s %d", g_szCombatFieldName, v52);
    SetEnable((UICaption *)(v2 + 124076));
    *(_BYTE *)(v2 + 124244) = 0;
  }
  return result;
}

// 0x00476ED0
int LineupUI_SetItemColors(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int *v6; // eax
  CScreenMode *Instance; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // ecx
  int *v12; // edi
  int v13; // edx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // ecx
  int *v18; // edi
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // ecx
  int *v25; // edi
  int v26; // ebx
  int v27; // edx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // ecx
  int *v32; // edi
  int v33; // ebx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // ecx
  int *v39; // edi
  int v40; // ebx
  int v41; // edx
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // ecx
  int *v46; // edi
  int v47; // ebx
  int v48; // eax
  int v49; // eax
  int *v50; // ecx
  int v51; // edx
  int v52; // edi
  char *v53; // [esp-0x8] [ebp-0x28]
  gbColorQuad v54; // [esp+0xC] [ebp-0x14] BYREF
  gbColorQuad v55; // [esp+0x10] [ebp-0x10] BYREF
  gbColorQuad v56; // [esp+0x14] [ebp-0xC] BYREF
  gbColorQuad v57; // [esp+0x18] [ebp-0x8] BYREF
  gbColorQuad v58; // [esp+0x1C] [ebp-0x4] BYREF

  v2 = v1;
  result = *(_DWORD *)(v1 + 592);
  if ( result >= 0 )
  {
    v4 = nVal;
    v5 = 299 * nVal;
    --*(_DWORD *)(v1 + 4 * (299 * nVal + result) + 32452);
    v6 = (int *)(v1 + 4 * (*(_DWORD *)(v1 + 592) + v5) + 32452);
    if ( *v6 > 0 )
    {
      sub_445E50(v1 + 121156);
      sub_445E50(v2 + 121500);
      v53 = (char *)off_5B9DF4;
    }
    else
    {
      *v6 = 0;
      sub_445E50(v1 + 121156);
      sub_445E50(v2 + 121500);
      v53 = off_5B9DF0[0];
    }
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v53, 1);
    *(_DWORD *)(v2 + 8 * (v5 + *(_DWORD *)(v2 + 592)) + 18100) = *(_DWORD *)(v2
                                                                           + 12 * (v5 + *(_DWORD *)(v2 + 592))
                                                                           + 46832);
    *(_DWORD *)(v2 + 8 * (*(_DWORD *)(v2 + 592) + v5) + 18104) = *(_DWORD *)(v2
                                                                           + 4 * (*(_DWORD *)(v2 + 592) + v5)
                                                                           + 32452);
    *(_BYTE *)(v2 + 124245) = 1;
    switch ( v4 )
    {
      case 0:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 32452));
        (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 39628));
        (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v8 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v8 + 32452) <= 0 )
        {
          if ( v8 < 0 || v8 >= *(_DWORD *)(v2 + 114348) )
            v9 = 0;
          else
            v9 = *(_DWORD *)(*(_DWORD *)(v2 + 114344) + 4 * v8);
          *(_DWORD *)(v9 + 68) = *(_DWORD *)(v2 + 113848);
        }
        else
        {
          ((gbColorQuad *)&nVal)->gbColorQuad::gbColorQuad(0x1Fu, 0xFBu, 0xFFu, 0xFFu);
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124245) )
        {
          v10 = 1;
          *(_DWORD *)(v2 + 46804) = *(_DWORD *)(v2 + 32452) * (*(_DWORD *)(*(_DWORD *)(v2 + 46840) + 608) / 2);
          if ( *(int *)(v2 + 115052) > 1 )
          {
            v11 = v2 + 32456;
            v12 = (int *)(v2 + 46852);
            do
            {
              v13 = (unsigned long)*v12;
              v11 += 4;
              v12 += 3;
              ++v10;
              *(_DWORD *)(v2 + 46804) += *(_DWORD *)(v11 - 4) * (*(_DWORD *)(v13 + 608) / 2);
            }
            while ( v10 < *(_DWORD *)(v2 + 115052) );
          }
        }
        break;
      case 1:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 33648));
        (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 40824));
        (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v14 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v14 + 33648) <= 0 )
        {
          if ( v14 < 0 || v14 >= *(_DWORD *)(v2 + 115560) )
            v15 = 0;
          else
            v15 = *(_DWORD *)(*(_DWORD *)(v2 + 115556) + 4 * v14);
          *(_DWORD *)(v15 + 68) = *(_DWORD *)(v2 + 115060);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124245) )
        {
          *(_DWORD *)(v2 + 46808) = *(_DWORD *)(v2 + 33648) * (*(_DWORD *)(*(_DWORD *)(v2 + 50428) + 608) / 2);
          v16 = *(_DWORD *)(v2 + 116264);
          if ( v16 > 1 )
          {
            v17 = v2 + 33652;
            v18 = (int *)(v2 + 50440);
            v19 = v16 - 1;
            do
            {
              v20 = (unsigned long)*v18;
              v17 += 4;
              v18 += 3;
              --v19;
              *(_DWORD *)(v2 + 46808) += *(_DWORD *)(v17 - 4) * (*(_DWORD *)(v20 + 608) / 2);
            }
            while ( v19 );
          }
        }
        break;
      case 2:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 34844));
        (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 42020));
        (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v21 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v21 + 34844) <= 0 )
        {
          if ( v21 < 0 || v21 >= *(_DWORD *)(v2 + 116772) )
            v22 = 0;
          else
            v22 = *(_DWORD *)(*(_DWORD *)(v2 + 116768) + 4 * v21);
          *(_DWORD *)(v22 + 68) = *(_DWORD *)(v2 + 116272);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124245) )
        {
          *(_DWORD *)(v2 + 46812) = *(_DWORD *)(v2 + 34844) * (*(_DWORD *)(*(_DWORD *)(v2 + 54016) + 608) / 2);
          v23 = *(_DWORD *)(v2 + 117476);
          if ( v23 > 1 )
          {
            v24 = v2 + 34848;
            v25 = (int *)(v2 + 54028);
            v26 = v23 - 1;
            do
            {
              v27 = (unsigned long)*v25;
              v24 += 4;
              v25 += 3;
              --v26;
              *(_DWORD *)(v2 + 46812) += *(_DWORD *)(v24 - 4) * (*(_DWORD *)(v27 + 608) / 2);
            }
            while ( v26 );
          }
        }
        break;
      case 3:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 36040));
        (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 43216));
        (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v28 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v28 + 36040) <= 0 )
        {
          if ( v28 < 0 || v28 >= *(_DWORD *)(v2 + 117984) )
            v29 = 0;
          else
            v29 = *(_DWORD *)(*(_DWORD *)(v2 + 117980) + 4 * v28);
          *(_DWORD *)(v29 + 68) = *(_DWORD *)(v2 + 117484);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124245) )
        {
          *(_DWORD *)(v2 + 46816) = *(_DWORD *)(v2 + 36040) * (*(_DWORD *)(*(_DWORD *)(v2 + 57604) + 608) / 2);
          v30 = *(_DWORD *)(v2 + 118688);
          if ( v30 > 1 )
          {
            v31 = v2 + 36044;
            v32 = (int *)(v2 + 57616);
            v33 = v30 - 1;
            do
            {
              v34 = (unsigned long)*v32;
              v31 += 4;
              v32 += 3;
              --v33;
              *(_DWORD *)(v2 + 46816) += *(_DWORD *)(v31 - 4) * (*(_DWORD *)(v34 + 608) / 2);
            }
            while ( v33 );
          }
        }
        break;
      case 4:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 37236));
        (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 44412));
        (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v35 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v35 + 37236) <= 0 )
        {
          if ( v35 < 0 || v35 >= *(_DWORD *)(v2 + 119196) )
            v36 = 0;
          else
            v36 = *(_DWORD *)(*(_DWORD *)(v2 + 119192) + 4 * v35);
          *(_DWORD *)(v36 + 68) = *(_DWORD *)(v2 + 118696);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124245) )
        {
          *(_DWORD *)(v2 + 46820) = *(_DWORD *)(v2 + 37236) * (*(_DWORD *)(*(_DWORD *)(v2 + 61192) + 608) / 2);
          v37 = *(_DWORD *)(v2 + 119900);
          if ( v37 > 1 )
          {
            v38 = v2 + 37240;
            v39 = (int *)(v2 + 61204);
            v40 = v37 - 1;
            do
            {
              v41 = (unsigned long)*v39;
              v38 += 4;
              v39 += 3;
              --v40;
              *(_DWORD *)(v2 + 46820) += *(_DWORD *)(v38 - 4) * (*(_DWORD *)(v41 + 608) / 2);
            }
            while ( v40 );
          }
        }
        break;
      case 5:
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 38432));
        (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        sprintf((char *const)(v2 + 80), (const char *)&dir[20], *(_DWORD *)(v2 + 4 * *(_DWORD *)(v2 + 592) + 45608));
        (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 592), (char *)(v2 + 80), 0);
        v42 = *(_DWORD *)(v2 + 592);
        if ( *(int *)(v2 + 4 * v42 + 38432) <= 0 )
        {
          if ( v42 < 0 || v42 >= *(_DWORD *)(v2 + 120408) )
            v43 = 0;
          else
            v43 = *(_DWORD *)(*(_DWORD *)(v2 + 120404) + 4 * v42);
          *(_DWORD *)(v43 + 68) = *(_DWORD *)(v2 + 119908);
        }
        else
        {
          UITabCtrl_SetItemParam(*(_DWORD *)(v2 + 592));
        }
        if ( *(_BYTE *)(v2 + 124245) )
        {
          *(_DWORD *)(v2 + 46824) = *(_DWORD *)(v2 + 38432) * (*(_DWORD *)(*(_DWORD *)(v2 + 64780) + 608) / 2);
          v44 = *(_DWORD *)(v2 + 121112);
          if ( v44 > 1 )
          {
            v45 = v2 + 38436;
            v46 = (int *)(v2 + 64792);
            v47 = v44 - 1;
            do
            {
              v48 = (unsigned long)*v46;
              v45 += 4;
              v46 += 3;
              --v47;
              *(_DWORD *)(v2 + 46824) += *(_DWORD *)(v45 - 4) * (*(_DWORD *)(v48 + 608) / 2);
            }
            while ( v47 );
          }
        }
        break;
      default:
        break;
    }
    v49 = 0;
    v50 = (int *)(v2 + 46804);
    v51 = 6;
    do
    {
      v52 = (unsigned long)(*v50++);
      v49 += v52;
      --v51;
    }
    while ( v51 );
    sprintf((char *const)(v2 + 80), "%s %d", g_szCombatFieldName, v49);
    SetEnable((UICaption *)(v2 + 124076));
    *(_BYTE *)(v2 + 124245) = 0;
  }
  return result;
}

// 0x004777B0
int LineupUI_RefreshDisplayEx(int nVal)
{
  int v1; // ecx
  int v2; // esi
  _DWORD *v3; // ebx
  int v4; // ebp
  int i; // edi
  int v6; // eax
  int v7; // edi
  _DWORD *v8; // ebx
  int v9; // eax
  int v10; // edi
  _DWORD *v11; // ebx
  int v12; // eax
  int v13; // edi
  _DWORD *v14; // ebx
  int v15; // eax
  int v16; // edi
  _DWORD *v17; // ebx
  int result; // eax
  int v19; // edi
  _DWORD *v20; // ebx
  int v21; // [esp+0x10] [ebp-0x4]

  v2 = v1;
  memset((void *)(v1 + 18100), 0, 0x3810u);
  v3 = (_DWORD *)(v1 + 32452);
  memset((void *)(v1 + 32452), 0, 0x1C08u);
  memset((void *)(v1 + 89888), 0, 0x1C08u);
  memset((void *)(v1 + 46832), 0, 0x5418u);
  memset((void *)(v1 + 68360), 0, 0x5418u);
  memset((void *)(v1 + 46804), 0, 0x18u);
  (((UIListBox *)(v1 + 113844)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 115056)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 116268)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 117480)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 118692)))->UIListBox::GetItem();
  (((UIListBox *)(v2 + 119904)))->UIListBox::GetItem();
  SetEnable((UICaption *)(v2 + 123740));
  v21 = 6;
  v4 = v2 + 105020;
  do
  {
    sub_445E50(v4);
    v4 += 344;
    --v21;
  }
  while ( v21 );
  sub_445E50(v2 + 105020);
  (**(void ( ***)(int, _DWORD))(v2 + 121156))((int)(v2 + 121156), (_DWORD)(0));
  (**(void ( ***)(int, _DWORD))(v2 + 121500))((int)(v2 + 121500), (_DWORD)(0));
  for ( i = 0; i < *(_DWORD *)(v2 + 115052); ++v3 )
  {
    sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v3);
    (((UIListBox *)(v2 + 113844)))->UIListBox::SetMouseMoveSel(2, i++, (char *)(v2 + 80), 0);
  }
  v6 = *(_DWORD *)(v2 + 116264);
  v7 = 0;
  *(_DWORD *)(v2 + 115052) = 0;
  if ( v6 > 0 )
  {
    v8 = (_DWORD *)(v2 + 33648);
    do
    {
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v8);
      (((UIListBox *)(v2 + 115056)))->UIListBox::SetMouseMoveSel(2, v7++, (char *)(v2 + 80), 0);
      ++v8;
    }
    while ( v7 < *(_DWORD *)(v2 + 116264) );
  }
  v9 = *(_DWORD *)(v2 + 117476);
  v10 = 0;
  *(_DWORD *)(v2 + 116264) = 0;
  if ( v9 > 0 )
  {
    v11 = (_DWORD *)(v2 + 34844);
    do
    {
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v11);
      (((UIListBox *)(v2 + 116268)))->UIListBox::SetMouseMoveSel(2, v10++, (char *)(v2 + 80), 0);
      ++v11;
    }
    while ( v10 < *(_DWORD *)(v2 + 117476) );
  }
  v12 = *(_DWORD *)(v2 + 118688);
  v13 = 0;
  *(_DWORD *)(v2 + 117476) = 0;
  if ( v12 > 0 )
  {
    v14 = (_DWORD *)(v2 + 36040);
    do
    {
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v14);
      (((UIListBox *)(v2 + 117480)))->UIListBox::SetMouseMoveSel(2, v13++, (char *)(v2 + 80), 0);
      ++v14;
    }
    while ( v13 < *(_DWORD *)(v2 + 118688) );
  }
  v15 = *(_DWORD *)(v2 + 119900);
  v16 = 0;
  *(_DWORD *)(v2 + 118688) = 0;
  if ( v15 > 0 )
  {
    v17 = (_DWORD *)(v2 + 37236);
    do
    {
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v17);
      (((UIListBox *)(v2 + 118692)))->UIListBox::SetMouseMoveSel(2, v16++, (char *)(v2 + 80), 0);
      ++v17;
    }
    while ( v16 < *(_DWORD *)(v2 + 119900) );
  }
  result = *(_DWORD *)(v2 + 121112);
  v19 = 0;
  *(_DWORD *)(v2 + 119900) = 0;
  if ( result <= 0 )
  {
    *(_DWORD *)(v2 + 121112) = 0;
  }
  else
  {
    v20 = (_DWORD *)(v2 + 38432);
    do
    {
      sprintf((char *const)(v2 + 80), (const char *)&dir[20], *v20);
      (((UIListBox *)(v2 + 119904)))->UIListBox::SetMouseMoveSel(2, v19, (char *)(v2 + 80), 0);
      result = *(_DWORD *)(v2 + 121112);
      ++v19;
      ++v20;
    }
    while ( v19 < result );
    *(_DWORD *)(v2 + 121112) = 0;
  }
  return result;
}

// 0x00478C00
int PAL_GDB_ResetAllData(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // ebx
  char *v3; // ebp
  _DWORD *v4; // ebx
  CHAR *v5; // ebp
  _DWORD *v6; // ebx
  CHAR *v7; // ebp
  CHAR *v8; // ebx
  CHAR *v9; // ebp
  _DWORD *v11; // [esp+0x10] [ebp-0x8]
  int v12; // [esp+0x14] [ebp-0x4]
  int v13; // [esp+0x14] [ebp-0x4]
  int v14; // [esp+0x14] [ebp-0x4]
  int v15; // [esp+0x14] [ebp-0x4]

  v2 = (_DWORD *)(v1 + 40);
  v11 = (_DWORD *)v1;
  v3 = (char *)v1 + 166;
  v12 = 200;
  do
  {
    *v2 = 0;
    *((_WORD *)v3 - 1) = 0;
    lstrcpyA(v3, unk_C10D38);
    lstrcpyA(v3 + 512, unk_C10D38);
    lstrcpyA(v3 + 542, unk_C10D38);
    lstrcpyA(v3 + 594, unk_C10D38);
    v2 += 213;
    memset(v3 + 630, 0, 0x30u);
    *(_DWORD *)(v3 + 774) = 0;
    v3 += 852;
    --v12;
  }
  while ( v12 );
  v13 = 300;
  v4 = (_DWORD *)(v11 + 42640);
  v5 = (CHAR *)(v11 + 42655);
  do
  {
    *v4 = 0;
    lstrcpyA((char *)v5 - 32, unk_C10D38);
    lstrcpyA((char *)v5, unk_C10D38);
    v4 += 190;
    memset(v5 + 532, 0, 0x18u);
    v5 += 760;
    --v13;
  }
  while ( v13 );
  v14 = 500;
  v6 = (_DWORD *)(v11 + 99640);
  v7 = (CHAR *)(v11 + 99649);
  do
  {
    *v6 = 0;
    lstrcpyA((char *)v7 - 32, unk_C10D38);
    lstrcpyA((char *)v7, unk_C10D38);
    lstrcpyA((char *)v7 + 30, unk_C10D38);
    lstrcpyA((char *)v7 + 60, unk_C10D38);
    v7[576] = 0;
    memset(v7 + 608, 0, 0x18u);
    v6 += 200;
    v7 += 800;
    --v14;
  }
  while ( v14 );
  v15 = 10;
  v8 = (CHAR *)(v11 + 199640);
  v9 = (CHAR *)(v11 + 199660);
  do
  {
    *((_DWORD *)v9 - 12) = 0;
    lstrcpyA((char *)v8, unk_C10D38);
    lstrcpyA((char *)v9, unk_C10D38);
    v8 += 632;
    memset(v9 + 526, 0, 0x18u);
    v9 += 632;
    --v15;
  }
  while ( v15 );
  v11[201220] = 0;
  memset(v11 + 199640, 0, 0x18B0u);
  memset(v11, 0, 0xA0u);
  memset(v11 + 99640, 0, 0x61A80u);
  memset(v11 + 40, 0, 0x299A0u);
  memset(v11 + 42640, 0, 0x37AA0u);
  return (int)v11;
}

// 0x004790F0
int GDB_GetRoleNum(PAL_GDB *_this)
{
  return _this->m_head.SkillNum;
}

// 0x00479250
int GDB_GetItemNum(PAL_GDB *_this)
{
  return _this->m_head.ComboNum;
}

// 0x0047A400
int RenderTarget_InitParticleRenders(int nVal)
{
  int v1; // ecx
  _DWORD *v2; // ebp
  RenderTarget *v3; // esi
  int v4; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  int fYb; // [esp+0x4] [ebp-0x20]
  int v17; // [esp+0x18] [ebp-0xC]
  int v18; // [esp+0x1C] [ebp-0x8]
  int v19; // [esp+0x20] [ebp-0x4]

  v2 = (_DWORD *)v1;
  v17 = 60;
  v3 = (RenderTarget *)(v1 + 173948);
  do
  {
    v4 = (unsigned long)v2[52247];
    v5 = (unsigned long)(v2[52249] - v4);
    v6 = rand();
    v18 = (unsigned long)v2[52248];
    v19 = v4 + v6 % (v5 / 2);
    v7 = (unsigned long)(v2[52250] - v18);
    (((RenderTarget *)v3))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v3))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 252;
    fX = rand() % 10 + 36;
    v8 = rand();
    (((RenderTarget *)v3))->RenderTarget::SetColor(v8 % 10 - 37, fX, fY);
    v9 = rand();
    (((RenderTarget *)v3))->RenderTarget::SetAlpha(v9 % 135 + 120);
    (((RenderTarget *)v3))->RenderTarget::SetField084(1070386381);
    (((RenderTarget *)v3))->RenderTarget::SetState(1061997773);
    fYa = (float)v18;
    fXa = (float)v19;
    (((RenderTarget *)v3))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v3))->RenderTarget::CalcRenderDimensions(v5, v7);
    (((RenderTarget *)v3))->RenderTarget::SetOffset(10.0, 2.0);
    *(float *)&fYb = (float)(rand() % 8 + 2);
    *(float *)&fXb = (float)(rand() % 8 + 2);
    (((RenderTarget *)v3))->RenderTarget::SetScale(fXb, fYb);
    (((RenderTarget *)v3))->RenderTarget::SetVisible(1);
    v3 = (RenderTarget *)((char *)v3 + 584);
    result = --v17;
  }
  while ( v17 );
  return result;
}

// 0x0047AAB0
int MainEquipUI_UpdateLayout(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  _DWORD *v3; // esi
  int v4; // edx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  _DWORD *v8; // edx
  _DWORD *v9; // ecx
  int result; // eax
  int v11; // [esp-0x4] [ebp-0x2C]
  int v12; // [esp+0x10] [ebp-0x18] BYREF
  int v13; // [esp+0x14] [ebp-0x14]
  int SkillNum; // [esp+0x18] [ebp-0x10]
  _DWORD p_DWORD[3]; // [esp+0x1C] [ebp-0xC] BYREF
  _DWORD *nVala; // [esp+0x2C] [ebp+0x4]

  v2 = v1;
  if ( nVal >= 0 )
  {
    nVala = (_DWORD *)(v1 + 796 * nVal);
    v3 = (_DWORD *)nVala;
    --nVala[1472];
    v4 = (unsigned long)(nVala[1471] - 1);
    nVala[1471] = v4;
    if ( (int)nVala[1472] < 0 || v4 < 0 )
    {
      nVala[1472] = 0;
      nVala[1471] = 0;
      sprintf((char *const)(v1 + 104), "\\n      %s", (const char *)&dword_DD943C);
      SetEnable((UICaption *)(v2 + 171296));
      return (((UIRoleSelect *)(v2 + 170840)))->UIRoleSelect::SetByte(1);
    }
    else
    {
      *(_BYTE *)(v1 + 173940) = 0;
      v11 = (unsigned long)nVala[1473];
      v12 = 0xFFFF;
      v13 = 0;
      SkillNum = 0;
      p_DWORD[0] = v11;
      p_DWORD[1] = 1;
      p_DWORD[2] = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v11);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(p_DWORD);
      v12 = (unsigned long)nVala[1474];
      v13 = 1;
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v12);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&v12);
      v5 = *(_DWORD *)(v2 + 162864);
      ++*(_DWORD *)(v2 + 173944);
      *(_DWORD *)(v2 + 96) = 0;
      if ( v5 > 0 )
      {
        do
        {
          if ( *(_DWORD *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 5896) == v3[1474] )
            *(_DWORD *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 5888) = (unsigned long)v3[1472];
          if ( *(_DWORD *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 5892) == v3[1473] )
            *(_DWORD *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 5884) = (unsigned long)v3[1471];
          sprintf((char *const)(v2 + 104), "%s", v2 + 796 * *(_DWORD *)(v2 + 96) + 5372);
          (((UIListBox *)(v2 + 167232)))->UIListBox::SetMouseMoveSel(0, *(_DWORD *)(v2 + 96), (char *)(v2 + 104), 0);
          sprintf((char *const)(v2 + 104), (const char *)&dir[20], *(_DWORD *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 5884));
          (((UIListBox *)(v2 + 167232)))->UIListBox::SetMouseMoveSel(1, *(_DWORD *)(v2 + 96), (char *)(v2 + 104), 0);
          sprintf((char *const)(v2 + 104), "%s", v2 + 796 * *(_DWORD *)(v2 + 96) + 5628);
          (((UIListBox *)(v2 + 167232)))->UIListBox::SetMouseMoveSel(2, *(_DWORD *)(v2 + 96), (char *)(v2 + 104), 0);
          sprintf((char *const)(v2 + 104), (const char *)&dir[20], *(_DWORD *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 5888));
          (((UIListBox *)(v2 + 167232)))->UIListBox::SetMouseMoveSel(3, *(_DWORD *)(v2 + 96), (char *)(v2 + 104), 0);
          qmemcpy(
            (void *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 83916),
            (const void *)(v2 + 796 * *(_DWORD *)(v2 + 96) + 5112),
            0x31Cu);
          v6 = *(_DWORD *)(v2 + 162864);
          v3 = (_DWORD *)nVala;
          v7 = *(_DWORD *)(v2 + 96) + 1;
          *(_DWORD *)(v2 + 96) = v7;
        }
        while ( v7 < v6 );
      }
      v8 = (_DWORD *)(v2 + 12 * (v3[1475] + 129));
      *(_DWORD *)(v2 + 162820) = (unsigned long)*v8;
      *(_DWORD *)(v2 + 162824) = (unsigned long)v8[1];
      *(_DWORD *)(v2 + 162828) = (unsigned long)v8[2];
      v9 = (_DWORD *)(v2 + 12 * (v3[1476] + 30));
      *(_DWORD *)(v2 + 162832) = (unsigned long)*v9;
      *(_DWORD *)(v2 + 162836) = (unsigned long)v9[1];
      *(_DWORD *)(v2 + 162840) = (unsigned long)v9[2];
      sub_445E50(v2 + 167232);
      sub_445E50(v2 + 168440);
      return sub_445E50(v2 + 169128);
    }
  }
  return result;
}

// 0x0047ADF0
int MainEquipUI_UpdateCompareLayout(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // ebx
  _DWORD *v3; // esi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax
  int v8; // [esp+0x8] [ebp-0x18] BYREF
  int v9; // [esp+0xC] [ebp-0x14]
  int v10; // [esp+0x10] [ebp-0x10]
  int pConfig[2]; // [esp+0x14] [ebp-0xC] BYREF
  int SkillNum; // [esp+0x1C] [ebp-0x4]
  int nVala; // [esp+0x24] [ebp+0x4]

  v2 = (_DWORD *)v1;
  if ( nVal >= 0 )
  {
    if ( v1[40707] && v1[40710] )
    {
      SkillNum = 0;
      v8 = 0xFFFF;
      v9 = 0;
      v10 = 0;
      v3 = (_DWORD *)&v1[199 * nVal];
      ++v3[1472];
      ++v3[1471];
      v1[40707] = 0;
      nVala = (int)v3;
      v1[40708] = 0;
      pConfig[1] = 1;
      v1[40709] = 0;
      v1[40710] = 0;
      v1[40711] = 0;
      v1[40712] = 0;
      pConfig[0] = (unsigned long)v3[1473];
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(pConfig[0]);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(pConfig);
      v8 = (unsigned long)v3[1474];
      v9 = 1;
      v10 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v8);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&v8);
      v4 = (unsigned long)v2[40716];
      ((int *)v2)[24] = 0;
      if ( v4 > 0 )
      {
        while ( 1 )
        {
          if ( v2[199 * v2[24] + 1474] == v3[1474] )
            v2[199 * v2[24] + 1472] = v3[1472];
          if ( v2[199 * v2[24] + 1473] == v3[1473] )
            v2[199 * v2[24] + 1471] = v3[1471];
          sprintf((char *const)v2 + 104, "%s", &v2[199 * v2[24] + 1343]);
          (((UIListBox *)(v2 + 41808)))->UIListBox::SetMouseMoveSel(0, v2[24], (char *)v2 + 104, 0);
          sprintf((char *const)v2 + 104, (const char *)&dir[20], v2[199 * v2[24] + 1471]);
          (((UIListBox *)(v2 + 41808)))->UIListBox::SetMouseMoveSel(1, v2[24], (char *)v2 + 104, 0);
          sprintf((char *const)v2 + 104, "%s", &v2[199 * v2[24] + 1407]);
          (((UIListBox *)(v2 + 41808)))->UIListBox::SetMouseMoveSel(2, v2[24], (char *)v2 + 104, 0);
          sprintf((char *const)v2 + 104, (const char *)&dir[20], v2[199 * v2[24] + 1472]);
          (((UIListBox *)(v2 + 41808)))->UIListBox::SetMouseMoveSel(3, v2[24], (char *)v2 + 104, 0);
          qmemcpy(&v2[199 * v2[24] + 20979], &v2[199 * v2[24] + 1278], 0x31Cu);
          v5 = (unsigned long)v2[40716];
          v6 = (unsigned long)(v2[24] + 1);
          v2[24] = v6;
          if ( v6 >= v5 )
            break;
          v3 = (_DWORD *)nVala;
        }
      }
      (((UIListBox *)(v2 + 41808)))->UIListBox::GetItem();
      sub_445E50((int)(v2 + 41808));
      sub_445E50((int)(v2 + 42110));
      sub_445E50((int)(v2 + 42282));
    }
    SetEnable((UICaption *)(v2 + 41010));
    SetEnable((UICaption *)(v2 + 41048));
    --v2[43486];
  }
  return result;
}

// 0x0047C260
int PAL3_Render_47c260(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = *(_DWORD *)(v1 + 3988);
  if ( result )
    return crt_sub_00540D20();
  return result;
}

// 0x0047C2D0
int PAL3_DispatchModeCommand(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  v2 = v1;
  switch ( nVal )
  {
    case 0:
      result = (*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v1 + 24))(v1, 1000, 1, 0);
      goto LABEL_6;
    case 1:
      result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v1 + 24))(v1, 1000, 0, 0);
      v4 = *(_DWORD *)(v2 + 120);
      if ( !v4 )
        goto LABEL_10;
      result = (*(int ( **)(int, int, int, _DWORD))(*(_DWORD *)v4 + 24))(v4, 1000, 1, 0);
      *(_DWORD *)(v2 + 124) = nVal;
      return result;
    case 2:
      result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v1 + 24))(v1, 1000, 0, 0);
LABEL_6:
      v5 = *(_DWORD *)(v2 + 120);
      if ( v5 )
        goto LABEL_9;
      goto LABEL_10;
    case 3:
      result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v1 + 24))(v1, 1000, 0, 0);
      v5 = *(_DWORD *)(v2 + 120);
      if ( v5 )
LABEL_9:
        result = (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v5 + 24))(v5, 1000, 0, 0);
      goto LABEL_10;
    default:
LABEL_10:
      *(_DWORD *)(v2 + 124) = nVal;
      return result;
  }
}

// 0x0047E190
int ComposeUI_ProcessFrame(int nVal)
{
  int v1; // ecx
  int v2; // eax
  int v3; // esi
  int v4; // edx
  int i; // ecx
  void (***v6)(_DWORD, _DWORD); // edi
  int v7; // ebp
  int v8; // ecx
  int SkillNum; // ebp
  char *v10; // esi
  char *v11; // eax
  int result; // eax
  char *v13; // [esp-0xC] [ebp-0x138]
  const CHAR *v14; // [esp-0x8] [ebp-0x134]
  CHAR String1[29]; // [esp+0xC] [ebp-0x120] BYREF
  __int16 v16; // [esp+0x29] [ebp-0x103]
  char v17; // [esp+0x2B] [ebp-0x101]
  char Buffer[253]; // [esp+0x2C] [ebp-0x100] BYREF
  __int16 v19; // [esp+0x129] [ebp-0x3]
  char v20; // [esp+0x12B] [ebp-0x1]

  v2 = -1;
  v3 = v1;
  switch ( *(_DWORD *)(v1 + 384) )
  {
    case 0x183A:
      v2 = 0;
      break;
    case 0x183C:
      v2 = 1;
      break;
    case 0x183E:
      v2 = 3;
      break;
    case 0x1840:
      v2 = 7;
      break;
    case 0x1842:
      v2 = 2;
      break;
    case 0x184F:
      v2 = 4;
      break;
    case 0x1850:
      v2 = 6;
      break;
    case 0x1856:
      v2 = 5;
      break;
    default:
      break;
  }
  v4 = 0;
  for ( i = 0; i < 8; ++i )
  {
    if ( g_SaveSlotFlags[8 * nVal + i] )
      ++v4;
  }
  if ( v4 >= 6 )
  {
    memset(Buffer, 0, sizeof(Buffer));
    v19 = 0;
    v20 = 0;
    sprintf(Buffer, "\\n  %s", (const char *)&dword_DD203C);
    SetEnable((UICaption *)(v3 + 2912));
    return (((UIRoleSelect *)(v3 + 2456)))->UIRoleSelect::SetByte(1);
  }
  else
  {
    g_SaveSlotFlags[8 * nVal + v2] = 1;
    (**(void ( ***)(int, _DWORD))(v3 + 392))((int)(v3 + 392), (_DWORD)(0));
    (**(void ( ***)(int, _DWORD))(v3 + 584))((int)(v3 + 584), (_DWORD)(0));
    v6 = (void ( ***)(_DWORD, _DWORD))(v3 + 736);
    v7 = 5;
    do
    {
      (**v6)((_DWORD)(v6), (_DWORD)(0));
      v6 += 86;
      --v7;
    }
    while ( v7 );
    v8 = *(_DWORD *)(v3 + 384);
    *(_BYTE *)(v3 + 388) = 1;
    *(_BYTE *)(v3 + 3829) = 0;
    *(_BYTE *)(v3 + 3830) = 0;
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v8);
    memset(String1, 0, sizeof(String1));
    v16 = 0;
    v17 = 0;
    switch ( nVal )
    {
      case 0:
        lstrcpyA(String1, "Jingtian");
        break;
      case 1:
        v14 = "Xuejian";
        goto LABEL_23;
      case 2:
        lstrcpyA(String1, "Longkui");
        break;
      case 3:
        lstrcpyA(String1, "Zixuan");
        break;
      case 4:
        v14 = "Changqing";
LABEL_23:
        lstrcpyA(String1, v14);
        break;
      default:
        break;
    }
    v10 = (char *)(v3 + 112);
    v13 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName(String1);
    v11 = (((PalScript *)g_PAL3_Instance.m_nTodo_140))->PalScript::SetAppName("AddSkill");
    _snprintf(v10, 0xFFu, v11, v13, SkillNum + 4);
    InputSystem::ProcessFrame(v10);
  }
  return result;
}

// 0x0047ECB0
int MainEquipUI_CreateUI(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // edi
  int v10; // ebx
  int v11; // ecx
  int v12; // ecx
  int v13; // edi
  int v14; // eax
  int v15; // edx
  int v16; // edi
  int v17; // ebx
  int v18; // ecx
  int v19; // ecx
  int v20; // edi
  int v21; // eax
  int v22; // edx
  int v23; // edi
  int v24; // ebx
  int v25; // ecx
  int v26; // ecx
  int v27; // eax
  int v28; // edi
  int v29; // edx
  int v30; // edi
  int v31; // ebx
  int v32; // ecx
  int v33; // ecx
  int v34; // eax
  int v35; // edi
  int v36; // edx
  int v37; // edi
  int v38; // ebx
  int v39; // ecx
  int v40; // ecx
  int v41; // edi
  int v42; // eax
  int v43; // edx
  int v44; // edx
  int v45; // edi
  int v46; // ebx
  int v47; // ebp
  int v48; // eax
  int v49; // edx
  int v50; // ecx
  int v51; // eax
  int v52; // eax
  int v53; // edx
  int v54; // eax
  UIScene *v55; // edi
  int v56; // ebx
  int v57; // eax
  UIScene *v58; // edi
  int v59; // ebx
  int v60; // eax
  int v61; // edx
  UIScene *v62; // edi
  int v63; // ecx
  int *v64; // ebx
  int v65; // edx
  bool v66; // zf
  int v67; // ecx
  int v68; // edx
  int v69; // eax
  int v71; // [esp+0x110] [ebp-0x44]
  int v72; // [esp+0x114] [ebp-0x40] BYREF
  int v73; // [esp+0x118] [ebp-0x3C]
  int v74; // [esp+0x11C] [ebp-0x38]
  int v75; // [esp+0x120] [ebp-0x34]
  int v76; // [esp+0x124] [ebp-0x30] BYREF
  int v77; // [esp+0x128] [ebp-0x2C]
  int v78; // [esp+0x12C] [ebp-0x28]
  int v79; // [esp+0x130] [ebp-0x24]
  _DWORD v80[2]; // [esp+0x134] [ebp-0x20] BYREF
  int v81; // [esp+0x13C] [ebp-0x18]
  int v82; // [esp+0x140] [ebp-0x14]
  _DWORD v83[4]; // [esp+0x144] [ebp-0x10] BYREF

  v2 = v1;
  v3 = *(_DWORD *)(v1 + 76) + 368;
  v80[0] = *(_DWORD *)(v1 + 72) + 68;
  v4 = v80[0] + 22;
  v81 = v80[0] + 22;
  LOBYTE(v4) = g_bDebugMode;
  v80[1] = v3;
  v82 = v3 + 36;
  (*(void ( **)(int, int *, _DWORD *, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 157908) + 28))(
    v2 + 157908,
    &byte_A00604,
    (_DWORD *)(v80),
    v2,
    "UI\\GameMainUI\\JusticeBook\\Pgup",
    0,
    v4);
  (((PalScript *)(v2 + 157908)))->PalScript::OpenScript("UI\\GameMainUI\\JusticeBook\\UnUp.tga", g_bDebugMode);
  (**(void ( ***)(int, _DWORD))(v2 + 157908))((int)(v2 + 157908), (_DWORD)(0));
  v5 = *(_DWORD *)(v2 + 158252);
  v80[0] = v81 + 600;
  v81 += 622;
  v6 = v81;
  LOBYTE(v6) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, _DWORD, int))(v5 + 28))(
    v2 + 158252,
    &byte_A00605,
    (_DWORD *)(v80),
    v2,
    "UI\\GameMainUI\\JusticeBook\\Pgdw",
    0,
    v6);
  (((PalScript *)(v2 + 158252)))->PalScript::OpenScript("UI\\GameMainUI\\JusticeBook\\UnDw.tga", g_bDebugMode);
  (**(void ( ***)(int, _DWORD))(v2 + 158252))((int)(v2 + 158252), (_DWORD)(0));
  v7 = *(_DWORD *)(v2 + 76) + 86;
  v72 = *(_DWORD *)(v2 + 72) + 706;
  v73 = v7;
  v7 += 25;
  v8 = *(_DWORD *)(v2 + 158596);
  v75 = v7;
  LOBYTE(v7) = g_bDebugMode;
  v74 = v72 + 82;
  (*(void ( **)(int, int *, int *, int, char *, int))(v8 + 28))(
    v2 + 158596,
    &byte_A00606,
    &v72,
    v2,
    "UI\\GameMainUI\\JusticeBook\\Gods",
    v7);
  v9 = v72;
  v10 = v73;
  v11 = v74;
  *(_DWORD *)(v2 + 162628) = v72;
  *(_DWORD *)(v2 + 162632) = v10;
  *(_DWORD *)(v2 + 162636) = v11;
  v12 = v75;
  *(_DWORD *)(v2 + 162640) = v75;
  *(_DWORD *)(v2 + 162532) = v9;
  v13 = v74;
  *(_DWORD *)(v2 + 162536) = v10;
  *(_DWORD *)(v2 + 162540) = v13;
  *(_DWORD *)(v2 + 162544) = v12;
  v14 = *(_DWORD *)(v2 + 162628) - 708;
  v12 += 25;
  *(_DWORD *)(v2 + 162532) = v14;
  v14 += 82;
  v73 = v12;
  *(_DWORD *)(v2 + 162540) = v14;
  LOBYTE(v14) = g_bDebugMode;
  v15 = *(_DWORD *)(v2 + 158844);
  v75 = v12 + 25;
  (*(void ( **)(int, int *, int *, int, char *, int))(v15 + 28))(
    v2 + 158844,
    &byte_A00607,
    &v72,
    v2,
    "UI\\GameMainUI\\JusticeBook\\Immortal",
    v14);
  v16 = v72;
  v17 = v73;
  v18 = v74;
  *(_DWORD *)(v2 + 162644) = v72;
  *(_DWORD *)(v2 + 162648) = v17;
  *(_DWORD *)(v2 + 162652) = v18;
  v19 = v75;
  *(_DWORD *)(v2 + 162656) = v75;
  *(_DWORD *)(v2 + 162548) = v16;
  v20 = v74;
  *(_DWORD *)(v2 + 162552) = v17;
  *(_DWORD *)(v2 + 162556) = v20;
  *(_DWORD *)(v2 + 162560) = v19;
  v21 = *(_DWORD *)(v2 + 162644) - 708;
  v19 += 25;
  *(_DWORD *)(v2 + 162548) = v21;
  v21 += 82;
  v22 = *(_DWORD *)(v2 + 159092);
  v73 = v19;
  *(_DWORD *)(v2 + 162556) = v21;
  LOBYTE(v21) = g_bDebugMode;
  v75 = v19 + 25;
  (*(void ( **)(int, int *, int *, int, char *, int))(v22 + 28))(
    v2 + 159092,
    &byte_A00608,
    &v72,
    v2,
    "UI\\GameMainUI\\JusticeBook\\Ghost",
    v21);
  v23 = v72;
  v24 = v73;
  v25 = v74;
  *(_DWORD *)(v2 + 162660) = v72;
  *(_DWORD *)(v2 + 162664) = v24;
  *(_DWORD *)(v2 + 162668) = v25;
  v26 = v75;
  *(_DWORD *)(v2 + 162672) = v75;
  v27 = *(_DWORD *)(v2 + 162660) - 708;
  *(_DWORD *)(v2 + 162564) = v23;
  v28 = v74;
  *(_DWORD *)(v2 + 162568) = v24;
  *(_DWORD *)(v2 + 162572) = v28;
  *(_DWORD *)(v2 + 162576) = v26;
  *(_DWORD *)(v2 + 162564) = v27;
  v26 += 25;
  v27 += 82;
  v29 = *(_DWORD *)(v2 + 159340);
  v73 = v26;
  *(_DWORD *)(v2 + 162572) = v27;
  LOBYTE(v27) = g_bDebugMode;
  v75 = v26 + 25;
  (*(void ( **)(int, int *, int *, int, char *, int))(v29 + 28))(
    v2 + 159340,
    &byte_A00609,
    &v72,
    v2,
    "UI\\GameMainUI\\JusticeBook\\Demon",
    v27);
  v30 = v72;
  v31 = v73;
  v32 = v74;
  *(_DWORD *)(v2 + 162676) = v72;
  *(_DWORD *)(v2 + 162680) = v31;
  *(_DWORD *)(v2 + 162684) = v32;
  v33 = v75;
  *(_DWORD *)(v2 + 162688) = v75;
  v34 = *(_DWORD *)(v2 + 162676) - 708;
  *(_DWORD *)(v2 + 162580) = v30;
  v35 = v74;
  *(_DWORD *)(v2 + 162584) = v31;
  *(_DWORD *)(v2 + 162588) = v35;
  *(_DWORD *)(v2 + 162592) = v33;
  *(_DWORD *)(v2 + 162580) = v34;
  v33 += 25;
  v34 += 82;
  v36 = *(_DWORD *)(v2 + 159588);
  v73 = v33;
  *(_DWORD *)(v2 + 162588) = v34;
  LOBYTE(v34) = g_bDebugMode;
  v75 = v33 + 25;
  (*(void ( **)(int, int *, int *, int, char *, int))(v36 + 28))(
    v2 + 159588,
    &byte_A00610,
    &v72,
    v2,
    "UI\\GameMainUI\\JusticeBook\\Human",
    v34);
  v37 = v72;
  v38 = v73;
  v39 = v74;
  *(_DWORD *)(v2 + 162692) = v72;
  *(_DWORD *)(v2 + 162696) = v38;
  *(_DWORD *)(v2 + 162700) = v39;
  v40 = v75;
  *(_DWORD *)(v2 + 162704) = v75;
  *(_DWORD *)(v2 + 162596) = v37;
  v41 = v74;
  *(_DWORD *)(v2 + 162600) = v38;
  *(_DWORD *)(v2 + 162604) = v41;
  *(_DWORD *)(v2 + 162608) = v40;
  v40 += 25;
  v42 = *(_DWORD *)(v2 + 162692) - 708;
  v73 = v40;
  *(_DWORD *)(v2 + 162596) = v42;
  v42 += 82;
  v43 = *(_DWORD *)(v2 + 159836);
  *(_DWORD *)(v2 + 162604) = v42;
  LOBYTE(v42) = g_bDebugMode;
  v75 = v40 + 25;
  (*(void ( **)(int, int *, int *, int, char *, int))(v43 + 28))(
    v2 + 159836,
    &byte_A00611,
    &v72,
    v2,
    "UI\\GameMainUI\\JusticeBook\\Magic",
    v42);
  v44 = v72;
  v45 = v73;
  v46 = v74;
  v47 = v75;
  *(_DWORD *)(v2 + 162708) = v72;
  *(_DWORD *)(v2 + 162712) = v45;
  *(_DWORD *)(v2 + 162716) = v46;
  *(_DWORD *)(v2 + 162720) = v47;
  v48 = *(_DWORD *)(v2 + 162708) - 708;
  *(_DWORD *)(v2 + 162612) = v44;
  v49 = v75;
  *(_DWORD *)(v2 + 162616) = v45;
  *(_DWORD *)(v2 + 162620) = v46;
  *(_DWORD *)(v2 + 162624) = v49;
  *(_DWORD *)(v2 + 162612) = v48;
  v50 = *(_DWORD *)(v2 + 72);
  *(_DWORD *)(v2 + 162620) = v48 + 82;
  v77 = *(_DWORD *)(v2 + 76) + 72;
  v78 = v50 + 32;
  v79 = v77 + 256;
  v51 = *(_DWORD *)(v2 + 154956);
  v76 = v50 + 79;
  (*(void ( **)(int, int *, int *, int))(v51 + 16))(v2 + 154956, &byte_A00602, &v76, v2);
  (((UIScene *)(v2 + 154956)))->UIScene::SetShow(0);
  (**(void ( ***)(int, _DWORD))(v2 + 154956))((int)(v2 + 154956), (_DWORD)(0));
  v52 = *(_DWORD *)(v2 + 76) + 404;
  v76 = *(_DWORD *)(v2 + 72) + 118;
  v77 = v52;
  v78 = v76 + 128;
  v79 = v52 + 32;
  (*(void ( **)(int, int *, int *, int))(*(_DWORD *)(v2 + 155108) + 16))(v2 + 155108, &byte_A00602, &v76, v2);
  (((UIScene *)(v2 + 155108)))->UIScene::SetShow(0);
  (**(void ( ***)(int, _DWORD))(v2 + 155108))((int)(v2 + 155108), (_DWORD)(0));
  v53 = *(_DWORD *)(v2 + 155260);
  v77 = v79 - 2;
  v79 = v79 - 2 + 32;
  (*(void ( **)(int, int *, int *, int))(v53 + 16))(v2 + 155260, &byte_A00602, &v76, v2);
  (((UIScene *)(v2 + 155260)))->UIScene::SetShow(0);
  (**(void ( ***)(int, _DWORD))(v2 + 155260))((int)(v2 + 155260), (_DWORD)(0));
  v54 = *(_DWORD *)(v2 + 76) + 464;
  v76 = *(_DWORD *)(v2 + 72) + 92;
  v77 = v54;
  v78 = v76 + 64;
  v79 = v54 + 32;
  v55 = (UIScene *)(v2 + 155412);
  v56 = 5;
  do
  {
    (*(void ( **)(UIScene *, int *, int *, int))(*(_DWORD *)((UIWnd *)v55) + 16))(v55, &byte_A00602, &v76, v2);
    (((UIScene *)v55))->UIScene::SetShow(0);
    (**(void ( ***)(UIScene *, _DWORD))((UIWnd *)v55))((UIScene *)(v55), (_DWORD)(0));
    v55 = (UIScene *)((char *)v55 + 152);
    v76 = v78 - 3;
    --v56;
    v78 = v78 - 3 + 64;
  }
  while ( v56 );
  v57 = *(_DWORD *)(v2 + 76) + 102;
  v76 = *(_DWORD *)(v2 + 72) + 426;
  v77 = v57;
  v78 = v76 + 100;
  v79 = v57 + 32;
  v58 = (UIScene *)(v2 + 156172);
  v59 = 5;
  do
  {
    (*(void ( **)(UIScene *, int *, int *, int))(*(_DWORD *)((UIWnd *)v58) + 16))(v58, &byte_A00602, &v76, v2);
    (((UIScene *)v58))->UIScene::SetShow(0);
    (**(void ( ***)(UIScene *, _DWORD))((UIWnd *)v58))((UIScene *)(v58), (_DWORD)(0));
    v58 = (UIScene *)((char *)v58 + 152);
    v77 = v79 - 4;
    --v59;
    v79 = v79 - 4 + 32;
  }
  while ( v59 );
  v60 = *(_DWORD *)(v2 + 76) + 128;
  v61 = *(_DWORD *)(v2 + 72) + 542;
  v77 = v60;
  v76 = v61;
  v62 = (UIScene *)(v2 + 156932);
  v78 = v61 + 200;
  v63 = v60 + 32;
  v79 = v60 + 32;
  v64 = (int *)(v2 + 157540);
  v71 = 4;
  while ( 1 )
  {
    *v64 = v61;
    v65 = v78;
    v64[1] = v60;
    v64[2] = v65;
    v64[3] = v63;
    (*(void ( **)(UIScene *, int *, int *, int))(*(_DWORD *)((UIWnd *)v62) + 16))(v62, &byte_A00602, &v76, v2);
    (((UIScene *)v62))->UIScene::SetShow(0);
    (**(void ( ***)(UIScene *, _DWORD))((UIWnd *)v62))((UIScene *)(v62), (_DWORD)(0));
    v60 = v79 - 4;
    v64 += 4;
    v62 = (UIScene *)((char *)v62 + 152);
    v66 = v71 == 1;
    v63 = v79 - 4 + 32;
    v77 = v79 - 4;
    v79 = v63;
    --v71;
    if ( v66 )
      break;
    v61 = v76;
  }
  v67 = *(_DWORD *)(v2 + 72);
  v68 = *(_DWORD *)(v2 + 157604);
  v77 = *(_DWORD *)(v2 + 76) + 255;
  v76 = v67 + 420;
  v79 = v77 + 280;
  v78 = v67 + 676;
  (*(void ( **)(int, int *, int *, int))(v68 + 16))(v2 + 157604, &byte_A00602, &v76, v2);
  (((UIScene *)(v2 + 157604)))->UIScene::SetShow(0);
  (**(void ( ***)(int, _DWORD))(v2 + 157604))((int)(v2 + 157604), (_DWORD)(0));
  v69 = *(_DWORD *)(v2 + 157756);
  v83[1] = 468;
  v83[0] = 670;
  v83[2] = 734;
  v83[3] = 500;
  (*(void ( **)(int, int *, _DWORD *, int))(v69 + 16))(v2 + 157756, &byte_A00602, (_DWORD *)(v83), v2);
  (((UIScene *)(v2 + 157756)))->UIScene::SetShow(0);
  return (**(int ( ***)(int, _DWORD))(v2 + 157756))((int)(v2 + 157756), (_DWORD)(0));
}

// 0x0047FD90
int Object3D_LoadActorModel(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // esi
  CCBParabolaWindow *v4; // ebx
  int result; // eax
  CCBParabolaWindow *v6; // ebx
  CCBParabolaWindow *v7; // ebx
  CCBParabolaWindow *v8; // ebx
  CCBParabolaWindow *v9; // ebx
  CCBParabolaWindow *v10; // ebx
  int v11; // [esp+0x14] [ebp+0x8]

  v2 = v11;
  v3 = v1;
  if ( v11 >= 0 )
  {
    if ( v11 > 1 )
      v2 = 1;
  }
  else
  {
    v2 = 0;
  }
  if ( *(_DWORD *)(v1 + 4 * nVal + 162724) != v2 )
  {
    switch ( nVal )
    {
      case 0:
        v4 = (CCBParabolaWindow *)(v1 + 158596);
        if ( v2 )
        {
          (((UIWnd *)(v1 + 158596)))->UIWnd::sub_445FA0((void *)(v1 + 162628));
          result = (int)(((CCBParabolaWindow *)v4))->CCBParabolaWindow::LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Gods", g_bDebugMode);
          goto LABEL_25;
        }
        (((UIWnd *)(v1 + 158596)))->UIWnd::sub_445FA0((void *)(v1 + 162532));
        (((UIPushButton *)(v3 + 158596)))->UIPushButton::LoadResource("UI\\GameMainUI\\JusticeBook\\PassGods0.tga", g_bDebugMode);
        (((UIPushButton *)(v3 + 158596)))->UIPushButton::LoadTexture("UI\\GameMainUI\\JusticeBook\\Gods1.tga", g_bDebugMode);
        *(_DWORD *)(v3 + 4 * nVal + 162724) = 0;
        break;
      case 1:
        v6 = (CCBParabolaWindow *)(v1 + 158844);
        if ( v2 )
        {
          (((UIWnd *)(v1 + 158844)))->UIWnd::sub_445FA0((void *)(v1 + 162644));
          result = (int)(((CCBParabolaWindow *)v6))->CCBParabolaWindow::LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Immortal", g_bDebugMode);
          goto LABEL_25;
        }
        (((UIWnd *)(v1 + 158844)))->UIWnd::sub_445FA0((void *)(v1 + 162548));
        (((UIPushButton *)(v3 + 158844)))->UIPushButton::LoadResource("UI\\GameMainUI\\JusticeBook\\PassImmortal0.tga", g_bDebugMode);
        (((UIPushButton *)(v3 + 158844)))->UIPushButton::LoadTexture("UI\\GameMainUI\\JusticeBook\\Immortal1.tga", g_bDebugMode);
        *(_DWORD *)(v3 + 4 * nVal + 162724) = 0;
        break;
      case 2:
        v7 = (CCBParabolaWindow *)(v1 + 159092);
        if ( v2 )
        {
          (((UIWnd *)(v1 + 159092)))->UIWnd::sub_445FA0((void *)(v1 + 162660));
          result = (int)(((CCBParabolaWindow *)v7))->CCBParabolaWindow::LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Ghost", g_bDebugMode);
          goto LABEL_25;
        }
        (((UIWnd *)(v1 + 159092)))->UIWnd::sub_445FA0((void *)(v1 + 162564));
        (((UIPushButton *)(v3 + 159092)))->UIPushButton::LoadResource("UI\\GameMainUI\\JusticeBook\\PassGhost0.tga", g_bDebugMode);
        (((UIPushButton *)(v3 + 159092)))->UIPushButton::LoadTexture("UI\\GameMainUI\\JusticeBook\\Ghost1.tga", g_bDebugMode);
        *(_DWORD *)(v3 + 4 * nVal + 162724) = 0;
        break;
      case 3:
        v8 = (CCBParabolaWindow *)(v1 + 159340);
        if ( v2 )
        {
          (((UIWnd *)(v1 + 159340)))->UIWnd::sub_445FA0((void *)(v1 + 162676));
          result = (int)(((CCBParabolaWindow *)v8))->CCBParabolaWindow::LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Demon", g_bDebugMode);
          goto LABEL_25;
        }
        (((UIWnd *)(v1 + 159340)))->UIWnd::sub_445FA0((void *)(v1 + 162580));
        (((UIPushButton *)(v3 + 159340)))->UIPushButton::LoadResource("UI\\GameMainUI\\JusticeBook\\PassDemon0.tga", g_bDebugMode);
        (((UIPushButton *)(v3 + 159340)))->UIPushButton::LoadTexture("UI\\GameMainUI\\JusticeBook\\Demon1.tga", g_bDebugMode);
        *(_DWORD *)(v3 + 4 * nVal + 162724) = 0;
        break;
      case 4:
        v9 = (CCBParabolaWindow *)(v1 + 159588);
        if ( v2 )
        {
          (((UIWnd *)(v1 + 159588)))->UIWnd::sub_445FA0((void *)(v1 + 162692));
          result = (int)(((CCBParabolaWindow *)v9))->CCBParabolaWindow::LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Human", g_bDebugMode);
          goto LABEL_25;
        }
        (((UIWnd *)(v1 + 159588)))->UIWnd::sub_445FA0((void *)(v1 + 162596));
        (((UIPushButton *)(v3 + 159588)))->UIPushButton::LoadResource("UI\\GameMainUI\\JusticeBook\\PassHuman0.tga", g_bDebugMode);
        (((UIPushButton *)(v3 + 159588)))->UIPushButton::LoadTexture("UI\\GameMainUI\\JusticeBook\\Human1.tga", g_bDebugMode);
        *(_DWORD *)(v3 + 4 * nVal + 162724) = 0;
        break;
      case 5:
        v10 = (CCBParabolaWindow *)(v1 + 159836);
        if ( v2 )
        {
          (((UIWnd *)(v1 + 159836)))->UIWnd::sub_445FA0((void *)(v1 + 162708));
          result = (int)(((CCBParabolaWindow *)v10))->CCBParabolaWindow::LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Magic", g_bDebugMode);
          goto LABEL_25;
        }
        (((UIWnd *)(v1 + 159836)))->UIWnd::sub_445FA0((void *)(v1 + 162612));
        (((UIPushButton *)(v3 + 159836)))->UIPushButton::LoadResource("UI\\GameMainUI\\JusticeBook\\PassMagic0.tga", g_bDebugMode);
        (((UIPushButton *)(v3 + 159836)))->UIPushButton::LoadTexture("UI\\GameMainUI\\JusticeBook\\Magic1.tga", g_bDebugMode);
        *(_DWORD *)(v3 + 4 * nVal + 162724) = 0;
        break;
      default:
LABEL_25:
        *(_DWORD *)(v3 + 4 * nVal + 162724) = v2;
        break;
    }
  }
  return result;
}

// 0x004819A0
int MainEquipUI_LoadFromFile(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // esi
  int result; // eax
  int v5; // ebx
  int v6; // [esp+0x10] [ebp+0x8]

  v2 = v6;
  v3 = v1;
  if ( v6 >= 0 )
  {
    if ( v6 > 1 )
      v2 = 1;
  }
  else
  {
    v2 = 0;
  }
  result = nVal;
  switch ( nVal )
  {
    case 0:
      v5 = v2;
      if ( v2 >= 0 )
      {
        if ( v2 > 1 )
          v5 = 1;
      }
      else
      {
        v5 = 0;
      }
      if ( *(_DWORD *)(v1 + 162724) != v5 )
      {
        if ( v5 )
        {
          (((UIWnd *)(v1 + 158596)))->UIWnd::sub_445FA0((void *)(v1 + 162628));
          (((CCBParabolaWindow *)(v3 + 158596)))->CCBParabolaWindow::LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Gods", g_bDebugMode);
        }
        else
        {
          (((UIWnd *)(v1 + 158596)))->UIWnd::sub_445FA0((void *)(v1 + 162532));
          (((UIPushButton *)(v3 + 158596)))->UIPushButton::LoadResource("UI\\GameMainUI\\JusticeBook\\PassGods0.tga", g_bDebugMode);
          (((UIPushButton *)(v3 + 158596)))->UIPushButton::LoadTexture("UI\\GameMainUI\\JusticeBook\\Gods1.tga", g_bDebugMode);
        }
        *(_DWORD *)(v3 + 162724) = v5;
      }
      Object3D_LoadActorModel(1);
      Object3D_LoadActorModel(2);
      Object3D_LoadActorModel(3);
      Object3D_LoadActorModel(4);
      result = Object3D_LoadActorModel(5);
      break;
    case 1:
      if ( v2 )
      {
        Object3D_LoadActorModel(1);
        goto LABEL_19;
      }
      result = Object3D_LoadActorModel(0);
      break;
    case 2:
      if ( v2 )
      {
LABEL_19:
        Object3D_LoadActorModel(2);
        goto LABEL_20;
      }
      Object3D_LoadActorModel(0);
      result = Object3D_LoadActorModel(1);
      break;
    case 3:
      if ( v2 )
      {
LABEL_20:
        Object3D_LoadActorModel(3);
        goto LABEL_21;
      }
      Object3D_LoadActorModel(0);
      Object3D_LoadActorModel(1);
      result = Object3D_LoadActorModel(2);
      break;
    case 4:
      if ( v2 )
      {
LABEL_21:
        Object3D_LoadActorModel(4);
        goto LABEL_22;
      }
      Object3D_LoadActorModel(0);
      Object3D_LoadActorModel(1);
      Object3D_LoadActorModel(2);
      result = Object3D_LoadActorModel(3);
      break;
    case 5:
      if ( v2 )
      {
LABEL_22:
        result = Object3D_LoadActorModel(5);
      }
      else
      {
        Object3D_LoadActorModel(0);
        Object3D_LoadActorModel(1);
        Object3D_LoadActorModel(2);
        Object3D_LoadActorModel(3);
        result = Object3D_LoadActorModel(4);
      }
      break;
    default:
      return result;
  }
  return result;
}

// 0x00484F10
int LoadStateUIRenderTarget(int a2)
{
  int v1; // ecx
  int v4; // edi
  int *v5; // ebx
  int v6; // esi
  int v7; // ebp
  int v8; // eax
  int v9; // eax
  void *v10; // edi
  const void *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  float fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  float fYb; // [esp+0x4] [ebp-0x20]
  int v20; // [esp+0x18] [ebp-0xC]
  int v21; // [esp+0x1C] [ebp-0x8]
  int a2a; // [esp+0x28] [ebp+0x4]

  *(_DWORD *)(v1 + 154632) = 0;
  *(_DWORD *)(v1 + 154636) = 0;
  a2a = 16;
  *(_BYTE *)(a2 + v1 + 154632) = 1;
  v4 = 16 * a2 + v1;
  v5 = (int *)(v4 + 154504);
  v6 = *(_DWORD *)(16 * (a2 + 9657) + v1) - *(_DWORD *)(v4 + 154504);
  v20 = v4;
  v21 = v6;
  v7 = 9344 * a2 + v1 + 5000;
  while ( 1 )
  {
    (((RenderTarget *)v7))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v7))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 252;
    fX = rand() % 10 + 36;
    v8 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetColor(v8 % 10 - 37, fX, fY);
    v9 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetAlpha(v9 % 135 + 120);
    *(_BYTE *)(v7 + 104) = 1;
    (((RenderTarget *)v7))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v7))->RenderTarget::SetState(1067030938);
    fYa = (float)*(int *)(v4 + 154508);
    fXa = (float)(*v5 + rand() % v6);
    (((RenderTarget *)v7))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v7))->RenderTarget::Render(*v5, v5[1], v5[2]);
    fYb = (float)(rand() % 2 + 1);
    fXb = (float)(rand() % 2 + 1);
    (((RenderTarget *)v7))->RenderTarget::SetOffset(fXb, fYb);
    (((RenderTarget *)v7))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v7))->RenderTarget::SetVisible(1);
    v10 = (void *)(v7 + 74752);
    v11 = (const void *)v7;
    v7 += 584;
    result = a2a - 1;
    v12 = a2a == 1;
    qmemcpy(v10, v11, 0x248u);
    --a2a;
    if ( v12 )
      break;
    v4 = v20;
    v6 = v21;
  }
  return result;
}

// 0x004870C0
int RenderTarget_InitNPCPanel(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax

  v2 = v1;
  (((PalScript *)(v1 + 249476)))->PalScript::Reset();
  (((UIListBox *)(v2 + 248268)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 247060)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 245852)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 244644)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 243436)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 242228)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 241020)))->UIListBox::DeleteRow();
  (((UIListBox *)(v2 + 239812)))->UIListBox::DeleteRow();
  (((UIFrameContainer *)(v2 + 212448)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 212296)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 212144)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 211992)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 211840)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 210320)))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)(v2 + 210236));
  (((UIRoleDialog *)(v2 + 208524)))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)(v2 + 207156)))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)(v2 + 205788)))->UIRoleDialog::~UIRoleDialog();
  (((UIFrameContainer *)(v2 + 55988)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 55836)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 55044)))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)(v2 + 54700)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 54356)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 54012)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 53668)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 53324)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 52980)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 52636)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 52292)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 51948)))->UICaption::Destroy2();
  (((UIFrameContainer *)(v2 + 51796)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 51644)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 51492)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 51340)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 51188)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 51036)))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)v2))->UIListBox::~UIListBox();
  return result;
}

// 0x00487480
int CameraCtrl_ResetToDefaults(int nVal)
{
  _DWORD *v1; // ecx
  int result; // eax

  memset(g_SaveSlotFlags, 0, sizeof(g_SaveSlotFlags));
  result = -1;
  v1[230] = -1;
  v1[231] = -1;
  v1[232] = 6202;
  v1[297] = 6201;
  v1[298] = 6201;
  v1[299] = 0;
  v1[305] = -1;
  v1[306] = -1;
  v1[307] = 6204;
  v1[372] = 6203;
  v1[373] = 6203;
  v1[374] = 0;
  v1[380] = -1;
  v1[381] = -1;
  v1[382] = 6210;
  v1[447] = 6204;
  v1[522] = 6205;
  v1[523] = 6205;
  v1[674] = 6224;
  v1[682] = 6224;
  v1[457] = 6206;
  v1[822] = 6206;
  v1[823] = 6206;
  v1[824] = 6206;
  v1[448] = 6208;
  v1[449] = 0;
  v1[455] = -1;
  v1[456] = -1;
  v1[524] = 0;
  v1[530] = -1;
  v1[531] = -1;
  v1[532] = 6223;
  v1[597] = 6214;
  v1[598] = 6215;
  v1[599] = 0;
  v1[605] = -1;
  v1[606] = -1;
  v1[607] = 6230;
  v1[672] = 6216;
  v1[673] = 6219;
  v1[680] = -1;
  v1[681] = -1;
  v1[747] = 6217;
  v1[748] = 6218;
  v1[749] = 0;
  v1[755] = -1;
  v1[756] = -1;
  v1[757] = 6208;
  return result;
}

// 0x00487650
int MainPropUI_CreateCoverTemplate(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  UIPushButton *v4; // edi
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // ecx
  int v33; // edx
  int v34; // eax
  int v35; // edx
  int v36; // edx
  int v37; // eax
  int v38; // ecx
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // ecx
  int v43; // eax
  _DWORD v45[2]; // [esp+0x5C] [ebp-0x20] BYREF
  int v46; // [esp+0x64] [ebp-0x18]
  int v47; // [esp+0x68] [ebp-0x14]
  _DWORD v48[4]; // [esp+0x6C] [ebp-0x10] BYREF

  v2 = v1;
  v3 = *(_DWORD *)(v1 + 51492);
  v4 = (UIPushButton *)(v1 + 51492);
  v45[1] = 543;
  v45[0] = 0;
  v46 = 256;
  v47 = 600;
  (*(void ( **)(int, int, _DWORD *))(v3 + 16))(v1 + 51492, 161, (_DWORD *)(v45));
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)v4))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v5);
  v6 = *(_DWORD *)(v2 + 51644);
  v45[0] = v46;
  v46 += 512;
  (*(void ( **)(int, int, _DWORD *, int))(v6 + 16))(v2 + 51644, 161, (_DWORD *)(v45), v2);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)(v2 + 51644)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v7);
  v45[0] = v46;
  v46 += 32;
  (*(void ( **)(int, int, _DWORD *, int))(*(_DWORD *)(v2 + 51796) + 16))(v2 + 51796, 161, (_DWORD *)(v45), v2);
  LOBYTE(v8) = g_bDebugMode;
  (((UIPushButton *)(v2 + 51796)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v8);
  *(_DWORD *)(v2 + 55200) = 546;
  *(_DWORD *)(v2 + 55196) = 38;
  *(_DWORD *)(v2 + 55204) = 148;
  *(_DWORD *)(v2 + 55208) = *(_DWORD *)(v2 + 55200) + 50;
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 51948) + 28))(
    v2 + 51948,
    &byte_A00102,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v9);
  *(_DWORD *)(v2 + 205648) = *(_DWORD *)(v2 + 55200) + 5;
  *(_DWORD *)(v2 + 205644) = *(_DWORD *)(v2 + 55196) + 35;
  *(_DWORD *)(v2 + 205652) = *(_DWORD *)(v2 + 55204) - 36;
  *(_DWORD *)(v2 + 205656) = *(_DWORD *)(v2 + 55208) - 5;
  v10 = *(_DWORD *)(v2 + 55204) - 22;
  *(_DWORD *)(v2 + 55196) = v10;
  v10 += 110;
  *(_DWORD *)(v2 + 55204) = v10;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 52980) + 28))(
    &byte_A00105,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v10);
  *(_DWORD *)(v2 + 205696) = *(_DWORD *)(v2 + 55200) + 5;
  *(_DWORD *)(v2 + 205692) = *(_DWORD *)(v2 + 55196) + 35;
  *(_DWORD *)(v2 + 205700) = *(_DWORD *)(v2 + 55204) - 36;
  *(_DWORD *)(v2 + 205704) = *(_DWORD *)(v2 + 55208) - 5;
  v11 = *(_DWORD *)(v2 + 55204) - 22;
  *(_DWORD *)(v2 + 55196) = v11;
  v11 += 110;
  *(_DWORD *)(v2 + 55204) = v11;
  LOBYTE(v11) = g_bDebugMode;
  (*(void ( **)(int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 52636) + 28))(
    &byte_A00104,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v11);
  v12 = *(_DWORD *)(v2 + 55200);
  v48[1] = 546;
  *(_DWORD *)(v2 + 205680) = v12 + 5;
  *(_DWORD *)(v2 + 205676) = *(_DWORD *)(v2 + 55196) + 35;
  v13 = *(_DWORD *)(v2 + 55204);
  v14 = *(_DWORD *)(v2 + 55208);
  v48[3] = 610;
  v15 = v13 - 36;
  v13 -= 22;
  *(_DWORD *)(v2 + 55196) = v13;
  *(_DWORD *)(v2 + 55204) = v13 + 110;
  v16 = *(_DWORD *)(v2 + 55196) - 38;
  *(_DWORD *)(v2 + 205684) = v15;
  v48[0] = v16;
  v48[2] = v16 + 256;
  v17 = *(_DWORD *)(v2 + 55044);
  *(_DWORD *)(v2 + 205688) = v14 - 5;
  (*(void ( **)(int, int, _DWORD *, int))(v17 + 16))(v2 + 55044, 161, (_DWORD *)(v48), v2);
  LOBYTE(v18) = g_bDebugMode;
  (((UIPushButton *)(v2 + 55044)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v18);
  LOBYTE(v19) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 52292) + 28))(
    v2 + 52292,
    &byte_A00103,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v19);
  v20 = *(_DWORD *)(v2 + 55196);
  v21 = *(_DWORD *)(v2 + 55204);
  *(_DWORD *)(v2 + 205664) = *(_DWORD *)(v2 + 55200) + 5;
  v22 = v21 - 36;
  *(_DWORD *)(v2 + 205660) = v20 + 35;
  v23 = *(_DWORD *)(v2 + 55208);
  v21 -= 22;
  *(_DWORD *)(v2 + 55196) = v21;
  v23 -= 5;
  *(_DWORD *)(v2 + 205668) = v22;
  *(_DWORD *)(v2 + 205672) = v23;
  *(_DWORD *)(v2 + 55204) = v21 + 110;
  LOBYTE(v23) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 54012) + 28))(
    v2 + 54012,
    &byte_A00108,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v23);
  v24 = *(_DWORD *)(v2 + 55196) + 35;
  *(_DWORD *)(v2 + 205712) = *(_DWORD *)(v2 + 55200) + 5;
  v25 = *(_DWORD *)(v2 + 55204);
  *(_DWORD *)(v2 + 205708) = v24;
  v26 = *(_DWORD *)(v2 + 55208);
  v27 = v25 - 36;
  v25 -= 22;
  *(_DWORD *)(v2 + 55196) = v25;
  v25 += 110;
  *(_DWORD *)(v2 + 205716) = v27;
  *(_DWORD *)(v2 + 205720) = v26 - 5;
  *(_DWORD *)(v2 + 55204) = v25;
  LOBYTE(v25) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 53324) + 28))(
    v2 + 53324,
    &byte_A00106,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v25);
  v28 = *(_DWORD *)(v2 + 55204);
  v29 = *(_DWORD *)(v2 + 55196) + 35;
  *(_DWORD *)(v2 + 205728) = *(_DWORD *)(v2 + 55200) + 5;
  *(_DWORD *)(v2 + 205724) = v29;
  v30 = v28 - 36;
  v31 = *(_DWORD *)(v2 + 55208);
  v28 -= 22;
  *(_DWORD *)(v2 + 55196) = v28;
  v31 -= 5;
  *(_DWORD *)(v2 + 205732) = v30;
  *(_DWORD *)(v2 + 205736) = v31;
  *(_DWORD *)(v2 + 55204) = v28 + 110;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 53668) + 28))(
    v2 + 53668,
    &byte_A00107,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v31);
  v32 = *(_DWORD *)(v2 + 55196);
  v33 = *(_DWORD *)(v2 + 55204);
  *(_DWORD *)(v2 + 205744) = *(_DWORD *)(v2 + 55200) + 5;
  v34 = *(_DWORD *)(v2 + 55208) - 5;
  *(_DWORD *)(v2 + 205740) = v32 + 35;
  *(_DWORD *)(v2 + 205748) = v33 - 36;
  v35 = *(_DWORD *)(v2 + 54700);
  *(_DWORD *)(v2 + 205752) = v34;
  LOBYTE(v34) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(v35 + 28))(
    v2 + 54700,
    &byte_A00110,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v34);
  v36 = *(_DWORD *)(v2 + 54356);
  v37 = *(_DWORD *)(v2 + 55204) - 22;
  *(_DWORD *)(v2 + 55196) = v37;
  v37 += 110;
  *(_DWORD *)(v2 + 55204) = v37;
  LOBYTE(v37) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(v36 + 28))(
    v2 + 54356,
    &byte_A00109,
    v2 + 55196,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v37);
  v38 = *(_DWORD *)(v2 + 55200);
  v39 = *(_DWORD *)(v2 + 55204) - 36;
  *(_DWORD *)(v2 + 205756) = *(_DWORD *)(v2 + 55196) + 35;
  v40 = *(_DWORD *)(v2 + 92);
  *(_DWORD *)(v2 + 205764) = v39;
  v41 = *(_DWORD *)(v2 + 88);
  *(_DWORD *)(v2 + 205760) = v38 + 5;
  v42 = *(_DWORD *)(v2 + 55208);
  v41 -= 38;
  *(_DWORD *)(v2 + 55200) = v40 - 51;
  *(_DWORD *)(v2 + 55196) = v41;
  *(_DWORD *)(v2 + 55204) = v41 + 38;
  v43 = *(_DWORD *)(v2 + 55200);
  *(_DWORD *)(v2 + 205768) = v42 - 5;
  *(_DWORD *)(v2 + 55208) = v43 + 48;
  return (((UIWnd *)(v2 + 54700)))->UIWnd::sub_445FA0((void *)(v2 + 55196));
}

// 0x00487B60
int PalScript_InitMainUIScripts(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ecx

  v2 = v1;
  if ( g_bRoleFlag1 )
  {
    v3 = v1 + 53324;
  }
  else
  {
    (((PalScript *)(v1 + 53324)))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    v3 = v2 + 53324;
  }
  sub_445E50(v3);
  if ( !g_bRoleFlag2 )
    (((PalScript *)(v2 + 53668)))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50(v2 + 53668);
  (((PalScript *)(v2 + 52292)))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnMagic.tga", g_bDebugMode);
  sub_445E50(v2 + 52292);
  sub_445E50(v2 + 51948);
  sub_445E50(v2 + 52636);
  sub_445E50(v2 + 52980);
  sub_445E50(v2 + 54356);
  return sub_445E50(v2 + 54700);
}

// 0x004890A0
int ScriptSystem_ProcessScriptEvent(int nVal)
{
  int result; // eax
  int v2; // ecx
  CameraCtrl *v3; // ebp
  int v4; // ebx
  int v5; // ecx
  int v6; // esi
  char v7; // al
  CScreenMode *Instance; // eax
  unsigned int *v9; // edi
  int v10; // ecx
  int v11; // ebp
  unsigned int *v12; // eax
  int v13; // esi
  char v14; // al
  void (***v15)(_DWORD, _DWORD); // esi
  int v16; // edi
  int v17; // esi
  _BYTE *p_m_bCamEventFlag; // eax
  int v19; // ecx
  __int16 *v20; // edx
  void (***v21)(_DWORD, _DWORD); // esi
  int v22; // edi
  int (***v23)(_DWORD, _DWORD); // esi
  int v24; // edi
  char v25; // al
  int v26; // edi
  int v27; // ebx
  unsigned int *v28; // ebp
  int v29; // esi
  int v30; // eax
  int v31; // esi
  unsigned int v32; // ecx
  unsigned int *v33; // eax
  int v34; // edx
  int v35; // ecx
  int i; // eax
  ScriptSystem *v37; // ecx
  int v38; // edi
  bool v39; // zf
  scAsmDecoder *v40; // eax
  scAsmDecoder *v41; // eax
  scAsmDecoder *v42; // eax
  scAsmDecoder *v43; // eax
  int v44; // esi
  unsigned int *v45; // eax
  int v46; // edx
  int v47; // edx
  int v48; // edi
  ScriptSystem *v49; // esi
  unsigned int *v50; // ebx
  char v51; // al
  unsigned int *v52; // ebp
  int j; // edi
  int v54; // esi
  int v55; // eax
  int v56; // esi
  unsigned int *v57; // eax
  int v58; // edx
  unsigned int *v59; // edi
  ScriptSystem *v60; // esi
  int v61; // ecx
  int k; // eax
  float m_vPos_y; // ecx
  ScriptSystem *v64; // ecx
  ScriptSystem *v65; // ecx
  int v66; // esi
  unsigned int *v67; // eax
  int v68; // edx
  CameraCtrl *v69; // ebx
  float v70; // ebp
  int v71; // esi
  unsigned __int8 *v72; // edi
  int v73; // ecx
  __int16 *v74; // edx
  void (***v75)(_DWORD, _DWORD); // esi
  int v76; // edi
  int (***v77)(_DWORD, _DWORD); // esi
  int v78; // edi
  const char *v79; // [esp-0x8] [ebp-0x30]
  CameraCtrl *v80; // [esp+0x10] [ebp-0x18]
  ScriptSystem *v81; // [esp+0x14] [ebp-0x14]
  int v82; // [esp+0x18] [ebp-0x10]
  unsigned int *v83; // [esp+0x18] [ebp-0x10]
  int v84; // [esp+0x1C] [ebp-0xC]
  int nVala; // [esp+0x2C] [ebp+0x4]
  int nValb; // [esp+0x2C] [ebp+0x4]
  int a1; // [esp+0x30] [ebp+0x8]
  int a1a; // [esp+0x30] [ebp+0x8]
  int a1b; // [esp+0x30] [ebp+0x8]
  ScriptSystem *a1c; // [esp+0x30] [ebp+0x8]
  int nVal2; // [esp+0x34] [ebp+0xC]

  v3 = (CameraCtrl *)v2;
  v4 = 0;
  v80 = (CameraCtrl *)v2;
  if ( nVal2 < 0 )
    goto LABEL_163;
  result = *(_DWORD *)(v2 + 900);
  if ( result < 0 )
    goto LABEL_163;
  if ( *(int *)(v2 + 904) < 0 )
    goto LABEL_163;
  result = 149 * (8 * nVal + result);
  v5 = 12 * nVal2 + 8 * result;
  v6 = (int)&v3->m_CamBlocks + v5 + 4;
  v81 = (ScriptSystem *)v6;
  LOBYTE(result) = *(_BYTE *)(*(int *)((char *)&v3->m_CamBlocks + v5 + 12) + 577);
  if ( (_BYTE)result != 1 && (_BYTE)result != 2 )
    goto LABEL_163;
  (((CameraCtrl *)v3))->CameraCtrl::CalcStatPower(v6);
  if ( !v7 && *(_BYTE *)(*(_DWORD *)(v6 + 8) + 577) == 1 )
  {
    sprintf(v3->m_szCamPath, "\\n        %s", (const char *)&dword_DC9F3C);
    SetEnable((UICaption *)(&v3[50].m_nViewBase + 292));
    (((UIRoleSelect *)(&v3[50].m_nViewBase + 178)))->UIRoleSelect::SetByte(1);
    v79 = g_pCScreenMode_5C7768;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v79, 1);
    return 0;
  }
  result = *(_DWORD *)(v6 + 8);
  v84 = 352 * nVal;
  if ( *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fScale + 352 * nVal) < *(_DWORD *)(result + 688)
    || *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_fMatrixA + 352 * nVal) < *(_DWORD *)(result + 692) )
  {
    goto LABEL_162;
  }
  if ( *(_DWORD *)(result + 696) != 10 )
    goto LABEL_44;
  if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) < *(_DWORD *)(result + 704) )
  {
LABEL_162:
    v3->m_bBlendWeight = 0;
LABEL_163:
    return 0;
  }
  if ( !*(_BYTE *)(result + 700) )
  {
    a1a = 0;
    v9 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
    v82 = 2 * *(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * nVal) + 40;
    while ( 1 )
    {
      if ( *(&v3->m_bCamEventFlag + v4) )
      {
        v10 = *(v9 - 12) - *v9;
        if ( v10 >= v82 )
          v10 = v82;
        v11 = 12;
        *v9 += v10;
        v12 = (unsigned int *)v9;
        do
        {
          v13 = *(v12 - 12);
          if ( (int)*v12 < v13 )
          {
            if ( (int)*v12 <= 0 )
              *v12 = 0;
          }
          else
          {
            *v12 = v13;
          }
          ++v12;
          --v11;
        }
        while ( v11 );
        a1a += v10;
        (((CameraCtrl *)v80))->CameraCtrl::CalcStatPower((int)v81);
        if ( v14 )
          CEffect_UpdateState(v4);
      }
      v9 += 352;
      ++v4;
      if ( (int)v9 >= (int)dword_C062EC )
        break;
      v3 = (CameraCtrl *)v80;
    }
    *(&g_RoleSlotBuf.dword_17AA450 + 147) -= a1a;
    sprintf(v80->m_szCamPath, (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
    SetEnable((UICaption *)(&v80[13].m_nViewBase + 200));
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nVal + 3] -= *(_DWORD *)(LODWORD(v81->m_vPos_y) + 688);
    ++HIWORD(v81->m_vPos_x);
    (((MainPropUI *)v80))->MainPropUI::InitNPCs(nVal, v80->m_nBlendWeight, nVal2);
    v15 = (void ( ***)(_DWORD, _DWORD))(&v80[53].m_wParamB + 18);
    v16 = 5;
    do
    {
      (**v15)((_DWORD)(v15), (_DWORD)(0));
      v15 += 1223;
      --v16;
    }
    while ( v16 );
    v17 = 0;
    p_m_bCamEventFlag = (_BYTE *)&v80->m_bCamEventFlag;
    nVala = 0;
    a1b = (int)&v80->m_bCamEventFlag;
    do
    {
      if ( *p_m_bCamEventFlag )
      {
        v19 = 0;
        v20 = (__int16 *)(LODWORD(v81->m_vPos_y) + 592);
        do
        {
          if ( *v20 > 0 )
            nVala += *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v17 + v19)
                   - g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v17 + 2 + v19];
          ++v19;
          ++v20;
        }
        while ( v19 < 12 );
      }
      v17 += 352;
      p_m_bCamEventFlag = (_BYTE *)++a1b;
    }
    while ( v17 < 1760 );
    if ( nVala <= 0 )
    {
      v21 = (void ( ***)(_DWORD, _DWORD))(&v80[53].m_wParamB + 18);
      *((_BYTE *)&v80->m_nBlendWeight + 9) = 0;
      v22 = 5;
      do
      {
        (**v21)((_DWORD)(v21), (_DWORD)(0));
        v21 += 1223;
        --v22;
      }
      while ( v22 );
    }
    result = CameraCtrl_HandleCameraEvent(nVal2);
    *((_BYTE *)&v80->m_nBlendWeight + 9) = result;
    if ( !(_BYTE)result )
    {
      v80->m_bHandleEvent = 0;
      v80->m_bBlendWeight = 0;
      (((MainPropUI *)v80))->MainPropUI::SetPage(1u);
      v23 = (int ( ***)(_DWORD, _DWORD))(&v80[53].m_wParamB + 18);
      v24 = 5;
      do
      {
        result = (**v23)((_DWORD)(v23), (_DWORD)(0));
        v23 += 1223;
        --v24;
      }
      while ( v24 );
    }
    return 1;
  }
LABEL_44:
  if ( !v3->m_bHandleEvent || !v3->m_bBlendWeight )
    goto LABEL_163;
  v25 = *(_BYTE *)(result + 577);
  if ( v25 == 1 )
  {
    v26 = 592;
    v27 = 352 * a1;
    v28 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * a1 + 2];
    do
    {
      v29 = *(__int16 *)(v26 + LODWORD(v81->m_vPos_y));
      v30 = (((MainPropUI *)v80))->MainPropUI::CalcBarWidth(abs32((__int64)((double)*(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * nVal)
                            * 0.050000001
                            * (double)v29
                            * 1.5)), 0.1);
      if ( v29 <= 0 )
        v30 = -v30;
      v31 = 12;
      v32 = v30 + *v28;
      v33 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v27 + 2];
      *v28 = v32;
      do
      {
        v34 = *(v33 - 12);
        if ( (int)*v33 < v34 )
        {
          if ( (int)*v33 <= 0 )
            *v33 = 0;
        }
        else
        {
          *v33 = v34;
        }
        ++v33;
        --v31;
      }
      while ( v31 );
      v26 += 2;
      ++v28;
    }
    while ( v26 < 616 );
    v35 = 0;
    for ( i = 618; i < 680; i += 2 )
    {
      if ( i < 618 || i > 642 )
        *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + v27 * 4 + v35 + 4) = *(_BYTE *)(i + LODWORD(v81->m_vPos_y));
      ++v35;
    }
    v37 = (ScriptSystem *)v81;
    if ( *(__int16 *)(LODWORD(v81->m_vPos_y) + 622) < 2 )
    {
      v38 = a1;
    }
    else
    {
      v38 = a1;
      v39 = a1 == (_DWORD)dword_C10CC8;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a1 + 6) = 0;
      if ( v39 )
        (((ScriptSystem *)v81))->ScriptSystem::RunEvent(31, 1);
      (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput(a1);
      v37 = (ScriptSystem *)v81;
    }
    if ( *(__int16 *)(LODWORD(v37->m_vPos_y) + 624) >= 2 )
    {
      v40 = dword_C10CC8;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a1 + 7) = 0;
      if ( (scAsmDecoder *)v38 == v40 )
        (((ScriptSystem *)v37))->ScriptSystem::RunEvent(31, 1);
      (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput(v38);
      v37 = (ScriptSystem *)v81;
    }
    if ( *(__int16 *)(LODWORD(v37->m_vPos_y) + 618) >= 2 )
    {
      v41 = dword_C10CC8;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a1 + 4) = 0;
      if ( (scAsmDecoder *)v38 == v41 )
        (((ScriptSystem *)v37))->ScriptSystem::RunEvent(31, 1);
      (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput(v38);
      v37 = (ScriptSystem *)v81;
    }
    if ( *(__int16 *)(LODWORD(v37->m_vPos_y) + 620) >= 2 )
    {
      v42 = dword_C10CC8;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_Actor + 1408 * a1 + 5) = 0;
      if ( (scAsmDecoder *)v38 == v42 )
        (((ScriptSystem *)v37))->ScriptSystem::RunEvent(31, 1);
      (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput(v38);
      v37 = (ScriptSystem *)v81;
    }
    if ( *(__int16 *)(LODWORD(v37->m_vPos_y) + 626) >= 2 )
    {
      v43 = dword_C10CC8;
      *((_BYTE *)&g_RoleSlotBuf.m_partyActor.m_nCmdParam + 1408 * a1) = 0;
      if ( (scAsmDecoder *)v38 == v43 )
        (((ScriptSystem *)v37))->ScriptSystem::RunEvent(31, 1);
      (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput(v38);
      v37 = (ScriptSystem *)v81;
    }
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nVal + 3] -= *(_DWORD *)(LODWORD(v37->m_vPos_y) + 688);
    v44 = 12;
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nVal + 4] -= *(_DWORD *)(LODWORD(v37->m_vPos_y) + 692);
    v45 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v84 + 2];
    do
    {
      v46 = *(v45 - 12);
      if ( (int)*v45 < v46 )
      {
        if ( (int)*v45 <= 0 )
          *v45 = 0;
      }
      else
      {
        *v45 = v46;
      }
      ++v45;
      --v44;
    }
    while ( v44 );
    v47 = 12 * nVal2 + 1192 * (8 * nVal + v80->m_nBlendWeight);
    ++*(_WORD *)((char *)&v80->m_CamBlocks + v47 + 10);
    (((MainPropUI *)v80))->MainPropUI::InitNPCs(nVal, v80->m_nBlendWeight, nVal2);
    CEffect_UpdateState(v38);
  }
  else if ( v25 == 2 )
  {
    v48 = v6;
    v49 = 0;
    v50 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
    a1c = 0;
    v83 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2];
    do
    {
      if ( *(&v3->m_bCamEventFlag + (_DWORD)v49) )
      {
        (((CameraCtrl *)v3))->CameraCtrl::CalcStatPower(v48);
        if ( v51 )
        {
          v52 = (unsigned int *)v50;
          for ( j = 592; j < 616; j += 2 )
          {
            v54 = *(__int16 *)(j + LODWORD(v81->m_vPos_y));
            v55 = (((MainPropUI *)v80))->MainPropUI::CalcBarWidth(abs32((__int64)((double)*(&g_RoleSlotBuf.m_partyActor.m_pRoleObj + 352 * nVal)
                                  * 0.050000001
                                  * (double)v54
                                  * 1.5)), 0.1);
            if ( v54 <= 0 )
              v55 = -v55;
            v56 = 12;
            *v52 += v55;
            v57 = (unsigned int *)v83;
            do
            {
              v58 = *(v57 - 12);
              if ( (int)*v57 < v58 )
              {
                if ( (int)*v57 <= 0 )
                  *v57 = 0;
              }
              else
              {
                *v57 = v58;
              }
              ++v57;
              --v56;
            }
            while ( v56 );
            ++v52;
          }
          v59 = (unsigned int *)v83;
          v60 = (ScriptSystem *)v81;
          v61 = 0;
          for ( k = 618; k < 680; k += 2 )
          {
            if ( k < 618 || k > 642 )
              *((_BYTE *)v83 + v61 - 288) = *(_BYTE *)(k + LODWORD(v81->m_vPos_y));
            ++v61;
          }
          if ( *(__int16 *)(LODWORD(v81->m_vPos_y) + 622) >= 2 )
          {
            v39 = (bool)a1c == (ScriptSystem *)dword_C10CC8;
            *((_BYTE *)v83 - 286) = 0;
            if ( v39 )
              (((ScriptSystem *)a1c))->ScriptSystem::RunEvent(31, 1);
            (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput((int)a1c);
            v59 = (unsigned int *)v83;
            v60 = (ScriptSystem *)v81;
          }
          m_vPos_y = v60->m_vPos_y;
          if ( *(__int16 *)(LODWORD(m_vPos_y) + 624) >= 2 )
          {
            v39 = (bool)a1c == (ScriptSystem *)dword_C10CC8;
            *((_BYTE *)v59 - 285) = 0;
            if ( v39 )
              (((ScriptSystem *)LODWORD(m_vPos_y)))->ScriptSystem::RunEvent(31, 1);
            (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput((int)a1c);
            v59 = (unsigned int *)v83;
            v60 = (ScriptSystem *)v81;
          }
          if ( *(__int16 *)(LODWORD(v60->m_vPos_y) + 618) >= 2 )
          {
            v64 = (ScriptSystem *)dword_C10CC8;
            v39 = (bool)a1c == (ScriptSystem *)dword_C10CC8;
            *((_BYTE *)v59 - 288) = 0;
            if ( v39 )
              (((ScriptSystem *)v64))->ScriptSystem::RunEvent(31, 1);
            (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput((int)a1c);
            v59 = (unsigned int *)v83;
            v60 = (ScriptSystem *)v81;
          }
          if ( *(__int16 *)(LODWORD(v60->m_vPos_y) + 620) >= 2 )
          {
            v39 = (bool)a1c == (ScriptSystem *)dword_C10CC8;
            *((_BYTE *)v59 - 287) = 0;
            if ( v39 )
              (((ScriptSystem *)a1c))->ScriptSystem::RunEvent(31, 1);
            (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput((int)a1c);
            v60 = (ScriptSystem *)v81;
          }
          if ( *(__int16 *)(LODWORD(v60->m_vPos_y) + 626) >= 2 )
          {
            v65 = (ScriptSystem *)dword_C10CC8;
            v39 = (bool)a1c == (ScriptSystem *)dword_C10CC8;
            *((_BYTE *)v83 - 284) = 0;
            if ( v39 )
              (((ScriptSystem *)v65))->ScriptSystem::RunEvent(31, 1);
            (((Comp_DonateUI *)*((Comp_DonateUI **)&v80[12].m_nViewState + 178)))->Comp_DonateUI::ProcessInput((int)a1c);
          }
          CEffect_UpdateState((int)a1c);
          v48 = (int)v81;
          v3 = (CameraCtrl *)v80;
          v50 = (unsigned int *)v83;
          v49 = (ScriptSystem *)a1c;
        }
      }
      v50 += 352;
      v49 = (ScriptSystem *)((char *)v49 + 1);
      a1c = (ScriptSystem *)v49;
      v83 = (unsigned int *)v50;
    }
    while ( (int)v50 < (int)dword_C062EC );
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nVal + 3] -= *(_DWORD *)(*(_DWORD *)(v48 + 8) + 688);
    v66 = 12;
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * nVal + 4] -= *(_DWORD *)(*(_DWORD *)(v48 + 8) + 692);
    v67 = (unsigned int *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v84 + 2];
    do
    {
      v68 = *(v67 - 12);
      if ( (int)*v67 < v68 )
      {
        if ( (int)*v67 <= 0 )
          *v67 = 0;
      }
      else
      {
        *v67 = v68;
      }
      ++v67;
      --v66;
    }
    while ( v66 );
    ++*(_WORD *)(v48 + 6);
    (((MainPropUI *)v3))->MainPropUI::InitNPCs(nVal, v3->m_nBlendWeight, nVal2);
  }
  v69 = (CameraCtrl *)v80;
  (((UIBigMap *)v80))->UIBigMap::UpdateElement((int)v81, nVal);
  v70 = v81->m_vPos_y;
  v71 = 0;
  nValb = 0;
  v72 = (unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 7;
  do
  {
    v73 = 0;
    v74 = (__int16 *)(LODWORD(v70) + 592);
    do
    {
      if ( *v74 > 0 )
      {
        v71 += *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v73 + nValb)
             - g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v73 + 2 + nValb];
        v69 = (CameraCtrl *)v80;
      }
      ++v73;
      ++v74;
    }
    while ( v73 < 12 );
    if ( *(_WORD *)(LODWORD(v70) + 622) )
      v71 += *(v72 - 1);
    if ( *(_WORD *)(LODWORD(v70) + 624) )
      v71 += *v72;
    if ( *(_WORD *)(LODWORD(v70) + 618) )
      v71 += *(v72 - 3);
    if ( *(_WORD *)(LODWORD(v70) + 620) )
      v71 += *(v72 - 2);
    if ( *(_WORD *)(LODWORD(v70) + 626) )
      v71 += v72[1];
    v72 += 1408;
    nValb += 352;
  }
  while ( (int)v72 < (int)byte_C061CF );
  if ( v71 <= 0 )
  {
    *((_BYTE *)&v69->m_nBlendWeight + 9) = 0;
    v75 = (void ( ***)(_DWORD, _DWORD))(&v69[53].m_wParamB + 18);
    v76 = 5;
    do
    {
      (**v75)((_DWORD)(v75), (_DWORD)(0));
      v75 += 1223;
      --v76;
    }
    while ( v76 );
  }
  if ( !*((_BYTE *)&v69->m_nBlendWeight + 9) || (result = CameraCtrl_HandleCameraEvent(nVal2), !(_BYTE)result) )
  {
    *((_BYTE *)&v69->m_nBlendWeight + 9) = 0;
    v69->m_bHandleEvent = 0;
    v69->m_bBlendWeight = 0;
    (((MainPropUI *)v69))->MainPropUI::SetPage(1u);
    v77 = (int ( ***)(_DWORD, _DWORD))(&v69[53].m_wParamB + 18);
    v78 = 5;
    do
    {
      result = (**v77)((_DWORD)(v77), (_DWORD)(0));
      v77 += 1223;
      --v78;
    }
    while ( v78 );
  }
  return 1;
}

// 0x0048A010
int MagicUI_RefreshAndLayout(int nVal)
{
  CCBUIPanel *v1; // ecx
  CCBUIPanel *v2; // esi
  int v3; // edi
  int v4; // ebx
  int v5; // edi
  int v7; // [esp+0xC] [ebp-0x10]
  int v8; // [esp+0x10] [ebp-0xC]
  int v9; // [esp+0x14] [ebp-0x8]
  int v10; // [esp+0x18] [ebp-0x4]

  v2 = (CCBUIPanel *)v1;
  (((CCBUIPanel *)v1))->CCBUIPanel::InitSlots();
  lstrcpyA(byte_DE54D4, byte_DD9E3C);
  lstrcpyA(byte_DE54D7, byte_DD9F3C);
  lstrcpyA(byte_DE54DA, byte_DDA03C);
  lstrcpyA(byte_DE54DD, byte_DDA13C);
  lstrcpyA(byte_DE54E0, byte_DDA23C);
  lstrcpyA(byte_DE54E3, byte_DDA33C);
  lstrcpyA(byte_DE54E6, byte_DDA43C);
  lstrcpyA(byte_DE54E9, byte_DDA53C);
  lstrcpyA(byte_DE54EC, byte_DDA63C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer, byte_DDA73C);
  (((CameraCtrl *)v2))->CameraCtrl::BuildRenderLists();
  v8 = 62;
  v7 = 686;
  v9 = 796;
  v10 = 157;
  v3 = 0;
  v4 = 60;
  do
  {
    if ( *((_BYTE *)((UIWnd *)v2) + v3 + 877) )
    {
      (((UITitle_XJTM *)v2))->UITitle_XJTM::LayoutGetRects();
      (((UITitle_XJTM *)v2))->UITitle_XJTM::SetMonsterState(v3, 1u);
      v4 += 122;
      v8 = v4;
      v10 = v4 + 95;
    }
    else
    {
      (((UITitle_XJTM *)v2))->UITitle_XJTM::SetMonsterState(v3, 0);
    }
    ++v3;
  }
  while ( v3 < 5 );
  LineupUI::LoadRoleData();
  (((CameraCtrl *)v2))->CameraCtrl::LoadRoleParams();
  v5 = 0;
  while ( !*((_BYTE *)((UIWnd *)v2) + v5 + 877) )
  {
    if ( ++v5 >= 5 )
      return MagicUI_InitUILayout(0);
  }
  v2[9].m_Slots[5].m_nPosX = v5;
  MagicUI_UpdateViewListItems(v5);
  (((MainPropUI *)v2))->MainPropUI::DisplayCaption(v5);
  return MagicUI_InitUILayout(0);
}

// 0x0048A390
int MagicUI_InitUILayout(int nVal)
{
  MainPropUI *v1; // ecx
  MainPropUI *v2; // esi
  char *v3; // edi
  int v4; // ebx
  int v5; // edi
  int v6; // ebx
  void ( ***v7)(int, int); // edi
  int v8; // ebp
  char *v9; // ebx
  int v10; // ecx
  UIPushButton *p_m_pbk2; // ebx
  int v12; // ebp
  int v13; // eax
  UIPushButton *v14; // ebx
  int v15; // ebp
  int v16; // eax
  UIPushButton *v17; // ebx
  int v18; // ebp
  int v19; // eax
  UIPushButton *v20; // ebx
  int v21; // ebp
  int v22; // eax
  UIPushButton *v23; // ebx
  int v24; // ebp
  int v25; // eax
  UIPushButton *v26; // ebx
  int v27; // ebp
  int v28; // eax
  UIPushButton *v29; // ebx
  int v30; // ebp
  int Item; // eax
  UIPushButton *v32; // ebx
  int v33; // ebp
  void ( **m_HelixAngle_low)(int, int); // edx
  int result; // eax
  int a2; // [esp+0x34] [ebp-0x10] BYREF
  int v37; // [esp+0x38] [ebp-0xC]
  int v38; // [esp+0x3C] [ebp-0x8]
  int v39; // [esp+0x40] [ebp-0x4]

  v2 = (MainPropUI *)v1;
  (((MainPropUI *)v1))->MainPropUI::SetPage(1u);
  v3 = (char *)&v2->m_parSingle[13][3]._texName[240];
  LODWORD(v2->m_TimeMoney.m_ratiow) = nVal;
  v4 = 5;
  do
  {
    (**(void ( ***)(char *, _DWORD))v3)((char *)(v3), (_DWORD)(0));
    v3 += 4892;
    --v4;
  }
  while ( v4 );
  v5 = (int)&v2->m_parSingle[20][2]._texName[120];
  v6 = 8;
  do
  {
    sub_445E50(v5);
    v5 += 344;
    --v6;
  }
  while ( v6 );
  v7 = (void ( ***)(int, int))&v2->m_btnPar[11][5]._texName[200];
  v8 = 4;
  v9 = (char *)&v2->m_btnPar[11][5]._texName[200];
  do
  {
    (**(void ( ***)(char *, _DWORD))v9)((char *)(v9), (_DWORD)(0));
    v9 += 152;
    --v8;
  }
  while ( v8 );
  switch ( nVal )
  {
    case 0:
      (*(void ( **)(unsigned int *, int))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        1);
      (((UIListBox *)&v2->m_parSingle[21][2].m_time.oldtick))->UIListBox::GetItem();
      (*(void ( **)(int, _DWORD))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 0);
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (_DWORD)(0));
      p_m_pbk2 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v12 = 9;
      do
      {
        LOBYTE(v10) = g_bDebugMode;
        (((UIPushButton *)p_m_pbk2))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Skill_Grid.tga", v10);
        p_m_pbk2 = (UIPushButton *)((char *)p_m_pbk2 + 152);
        --v12;
      }
      while ( v12 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCAF3C, (const char *)&dword_DC423C);
      a2 += 274;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      sub_445E50((int)&v2->m_parSingle[20][2]._texName[120]);
      v2[1].m_OutFrameR.m_pbk = 0;
      break;
    case 1:
      (*(void ( **)(unsigned int *, _DWORD))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        0);
      (*(void ( **)(int, _DWORD))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 0);
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (_DWORD)(0));
      (**(void ( ***)(int, int))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (int)(1));
      (((UIListBox *)&v2->m_parSingle[22][3]._texName[72]))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (_DWORD)(0));
      v19 = (**(int ( ***)(int, _DWORD))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (_DWORD)(0));
      v20 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v21 = 9;
      do
      {
        LOBYTE(v19) = g_bDebugMode;
        (((UIPushButton *)v20))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Magic_Grid.tga", v19);
        v20 = (UIPushButton *)((char *)v20 + 152);
        --v21;
      }
      while ( v21 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      a2 += 146;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCAF3C, (const char *)&dword_DC433C);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      a2 += 72;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6].m_isSubA))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB03C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6].m_isSubA);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6].m_isSubA)((int)((int)&v2->m_btnPar[11][6].m_isSubA), (int)(1));
      a2 += 38;
      v38 = a2 + 128;
      (((UIWnd *)&v2->m_btnPar[11][6]._texName[72]))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCB13C, (const char *)&dword_DC6B3C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6]._texName[72]);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6]._texName[72])((int)((int)&v2->m_btnPar[11][6]._texName[72]), (int)(1));
      sub_445E50((int)&v2->m_parSingle[20][3].m_bGetBottom);
      v2[1].m_OutFrameR.m_pbk = 0;
      break;
    case 2:
      (*(void ( **)(unsigned int *, _DWORD))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        0);
      (*(void ( **)(int, _DWORD))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 0);
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (_DWORD)(0));
      (**(void ( ***)(int, int))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (int)(1));
      (((UIListBox *)&v2->m_parSingle[23][0]._texName[112]))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (_DWORD)(0));
      v22 = (**(int ( ***)(int, _DWORD))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (_DWORD)(0));
      v23 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v24 = 9;
      do
      {
        LOBYTE(v22) = g_bDebugMode;
        (((UIPushButton *)v23))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Magic_Grid.tga", v22);
        v23 = (UIPushButton *)((char *)v23 + 152);
        --v24;
      }
      while ( v24 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      a2 += 146;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCAF3C, (const char *)&dword_DC433C);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      a2 += 72;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6].m_isSubA))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB03C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6].m_isSubA);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6].m_isSubA)((int)((int)&v2->m_btnPar[11][6].m_isSubA), (int)(1));
      a2 += 38;
      v38 = a2 + 128;
      (((UIWnd *)&v2->m_btnPar[11][6]._texName[72]))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCB13C, (const char *)&dword_DC6B3C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6]._texName[72]);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6]._texName[72])((int)((int)&v2->m_btnPar[11][6]._texName[72]), (int)(1));
      sub_445E50((int)&v2->m_parSingle[20][3]._texName[224]);
      v2[1].m_OutFrameR.m_pbk = 0;
      break;
    case 3:
      (*(void ( **)(unsigned int *, _DWORD))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        0);
      (*(void ( **)(int, _DWORD))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 0);
      (**(void ( ***)(int, int))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (int)(1));
      (((UIListBox *)&v2->m_parSingle[22][1]._texName[32]))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (_DWORD)(0));
      v16 = (**(int ( ***)(int, _DWORD))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (_DWORD)(0));
      v17 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v18 = 9;
      do
      {
        LOBYTE(v16) = g_bDebugMode;
        (((UIPushButton *)v17))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Magic_Grid.tga", v16);
        v17 = (UIPushButton *)((char *)v17 + 152);
        --v18;
      }
      while ( v18 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      a2 += 146;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCAF3C, (const char *)&dword_DC433C);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      a2 += 72;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6].m_isSubA))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB03C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6].m_isSubA);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6].m_isSubA)((int)((int)&v2->m_btnPar[11][6].m_isSubA), (int)(1));
      a2 += 38;
      v38 = a2 + 128;
      (((UIWnd *)&v2->m_btnPar[11][6]._texName[72]))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCB13C, (const char *)&dword_DC6B3C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6]._texName[72]);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6]._texName[72])((int)((int)&v2->m_btnPar[11][6]._texName[72]), (int)(1));
      sub_445E50((int)&v2->m_parSingle[20][4]._xi);
      v2[1].m_OutFrameR.m_pbk = 0;
      break;
    case 4:
      (*(void ( **)(unsigned int *, _DWORD))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        0);
      (*(void ( **)(int, int))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 1);
      (((UIListBox *)&v2->m_parSingle[21][4]._xg))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (_DWORD)(0));
      v13 = (**(int ( ***)(int, _DWORD))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (_DWORD)(0));
      v14 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v15 = 9;
      do
      {
        LOBYTE(v13) = g_bDebugMode;
        (((UIPushButton *)v14))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Magic_Grid.tga", v13);
        v14 = (UIPushButton *)((char *)v14 + 152);
        --v15;
      }
      while ( v15 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      a2 += 146;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCAF3C, (const char *)&dword_DC433C);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      a2 += 72;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6].m_isSubA))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB03C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6].m_isSubA);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6].m_isSubA)((int)((int)&v2->m_btnPar[11][6].m_isSubA), (int)(1));
      a2 += 38;
      v38 = a2 + 128;
      (((UIWnd *)&v2->m_btnPar[11][6]._texName[72]))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCB13C, (const char *)&dword_DC6B3C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6]._texName[72]);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6]._texName[72])((int)((int)&v2->m_btnPar[11][6]._texName[72]), (int)(1));
      sub_445E50((int)&v2->m_parSingle[20][4]._element.pDebugTex);
      v2[1].m_OutFrameR.m_pbk = 0;
      break;
    case 5:
      (*(void ( **)(unsigned int *, _DWORD))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        0);
      (*(void ( **)(int, _DWORD))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 0);
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (_DWORD)(0));
      (**(void ( ***)(int, int))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (int)(1));
      (((UIListBox *)&v2->m_parSingle[23][2]._texName[152]))->UIListBox::GetItem();
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (_DWORD)(0));
      v25 = (**(int ( ***)(int, _DWORD))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (_DWORD)(0));
      v26 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v27 = 9;
      do
      {
        LOBYTE(v25) = g_bDebugMode;
        (((UIPushButton *)v26))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Magic_Grid.tga", v25);
        v26 = (UIPushButton *)((char *)v26 + 152);
        --v27;
      }
      while ( v27 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      a2 += 146;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCAF3C, (const char *)&dword_DC433C);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      a2 += 72;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6].m_isSubA))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB03C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6].m_isSubA);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6].m_isSubA)((int)((int)&v2->m_btnPar[11][6].m_isSubA), (int)(1));
      a2 += 38;
      v38 = a2 + 128;
      (((UIWnd *)&v2->m_btnPar[11][6]._texName[72]))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCB13C, (const char *)&dword_DC6B3C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6]._texName[72]);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6]._texName[72])((int)((int)&v2->m_btnPar[11][6]._texName[72]), (int)(1));
      sub_445E50((int)&v2->m_parSingle[21][0]._texName[88]);
      v2[1].m_OutFrameR.m_pbk = 0;
      break;
    case 6:
      (*(void ( **)(unsigned int *, _DWORD))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        0);
      (*(void ( **)(int, _DWORD))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 0);
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (_DWORD)(0));
      (**(void ( ***)(int, int))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (int)(1));
      (((UIListBox *)&v2->m_parSingle[23][4]._texName[192]))->UIListBox::GetItem();
      v28 = (**(int ( ***)(int, _DWORD))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (_DWORD)(0));
      v29 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v30 = 9;
      do
      {
        LOBYTE(v28) = g_bDebugMode;
        (((UIPushButton *)v29))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Magic_Grid.tga", v28);
        v29 = (UIPushButton *)((char *)v29 + 152);
        --v30;
      }
      while ( v30 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      a2 += 146;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCAF3C, (const char *)&dword_DC433C);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      a2 += 72;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6].m_isSubA))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB03C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6].m_isSubA);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6].m_isSubA)((int)((int)&v2->m_btnPar[11][6].m_isSubA), (int)(1));
      a2 += 38;
      v38 = a2 + 128;
      (((UIWnd *)&v2->m_btnPar[11][6]._texName[72]))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s%s", (const char *)&dword_DCB13C, (const char *)&dword_DC6B3C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6]._texName[72]);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6]._texName[72])((int)((int)&v2->m_btnPar[11][6]._texName[72]), (int)(1));
      sub_445E50((int)&v2->m_parSingle[21][1].m_viewRect.right);
      v2[1].m_OutFrameR.m_pbk = 0;
      break;
    case 7:
      (*(void ( **)(unsigned int *, _DWORD))v2->m_parSingle[21][2].m_time.oldtick)(
        &v2->m_parSingle[21][2].m_time.oldtick,
        0);
      (*(void ( **)(int, _DWORD))LODWORD(v2->m_parSingle[21][4]._xg))((int)&v2->m_parSingle[21][4]._xg, 0);
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][1]._texName[32])((int)((int)&v2->m_parSingle[22][1]._texName[32]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[22][3]._texName[72])((int)((int)&v2->m_parSingle[22][3]._texName[72]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][0]._texName[112])((int)((int)&v2->m_parSingle[23][0]._texName[112]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][2]._texName[152])((int)((int)&v2->m_parSingle[23][2]._texName[152]), (_DWORD)(0));
      (**(void ( ***)(int, _DWORD))&v2->m_parSingle[23][4]._texName[192])((int)((int)&v2->m_parSingle[23][4]._texName[192]), (_DWORD)(0));
      (**(void ( ***)(int, int))&v2[1].buf[184])((int)((int)&v2[1].buf[184]), (int)(1));
      Item = (((UIListBox *)&v2[1].buf[184]))->UIListBox::GetItem();
      v32 = (UIPushButton *)&v2->m_parSingle[11][1]._element.m_pbk2;
      v33 = 9;
      do
      {
        LOBYTE(Item) = g_bDebugMode;
        (((UIPushButton *)v32))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Com_Grid.tga", Item);
        v32 = (UIPushButton *)((char *)v32 + 152);
        --v33;
      }
      while ( v33 );
      a2 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[184];
      v37 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[188];
      v38 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[192];
      v39 = *(_DWORD *)&v2->m_btnPar[11][5]._texName[196];
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._texName[200]);
      (**v7)((int)((int)&v2->m_btnPar[11][5]._texName[200]), (int)(1));
      a2 += 94;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][5]._element.m_fonttype))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB33C);
      SetEnable((UICaption *)&v2->m_btnPar[11][5]._element.m_fonttype);
      (*(void ( **)(Parent_Data **, int))v2->m_btnPar[11][5]._element.m_fonttype)(
        &v2->m_btnPar[11][5]._element.m_fonttype,
        1);
      a2 += 98;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6].m_isSubA))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB43C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6].m_isSubA);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6].m_isSubA)((int)((int)&v2->m_btnPar[11][6].m_isSubA), (int)(1));
      a2 += 98;
      v38 = a2 + 64;
      (((UIWnd *)&v2->m_btnPar[11][6]._texName[72]))->UIWnd::sub_445FA0(&a2);
      sprintf((char *const)&v2->s_x, "%s", &dword_DCB53C);
      SetEnable((UICaption *)&v2->m_btnPar[11][6]._texName[72]);
      (**(void ( ***)(int, int))&v2->m_btnPar[11][6]._texName[72])((int)((int)&v2->m_btnPar[11][6]._texName[72]), (int)(1));
      sub_445E50((int)&v2->m_parSingle[21][1]._texName[192]);
      break;
    default:
      break;
  }
  m_HelixAngle_low = (void ( **)(int, int))LODWORD(v2->m_parSingle[12][0].m_HelixAngle);
  v2->m_TimeMoney.pDebugTex = (gbTexture *)nVal;
  (*m_HelixAngle_low)((int)&v2->m_parSingle[12][0].m_HelixAngle, 1);
  SetEnable((UICaption *)&v2->m_parSingle[11][4]._texName[164]);
  SetEnable((UICaption *)&v2->m_parSingle[11][4]._element.m_bvisible);
  SetEnable((UICaption *)&v2->m_parSingle[12][0]._texName[36]);
  return result;
}

// 0x0048B8F0
int MagicUI_UpdateViewListItems(int nVal)
{
  int v1; // ecx
  int v2; // esi
  UIListBox *v3; // edi
  int v4; // ebx
  _DWORD *v5; // ebp
  char *v6; // ebp
  _DWORD *v7; // esi
  int v8; // eax
  int i; // esi
  int v10; // eax
  UIListBox *v11; // edi
  int v12; // eax
  char *m_szCamPath; // esi
  _DWORD *v14; // ebx
  int ListItems; // ebp
  int v16; // eax
  int v17; // edx
  int j; // esi
  int v19; // eax
  UIListBox *v20; // edi
  int v21; // eax
  char *v22; // esi
  _DWORD *v23; // ebx
  int v24; // ebp
  int v25; // eax
  int v26; // edx
  int k; // esi
  int v28; // eax
  UIListBox *v29; // edi
  int v30; // eax
  char *v31; // esi
  _DWORD *v32; // ebx
  int v33; // ebp
  int v34; // eax
  int v35; // edx
  int m; // esi
  int v37; // eax
  UIListBox *v38; // edi
  int v39; // eax
  char *v40; // esi
  _DWORD *v41; // ebx
  int v42; // ebp
  int v43; // eax
  int v44; // edx
  int n; // esi
  int v46; // eax
  UIListBox *p_m_fDefaultPosX; // edi
  int v48; // eax
  char *v49; // esi
  _DWORD *v50; // ebx
  int v51; // ebp
  int v52; // eax
  int v53; // edx
  int ii; // esi
  int v55; // eax
  UIListBox *v56; // edi
  int v57; // eax
  char *v58; // esi
  _DWORD *v59; // ebx
  int v60; // ebp
  int v61; // eax
  int v62; // edx
  int jj; // esi
  int v64; // eax
  CameraCtrl *v65; // edi
  UIListBox *v66; // ebp
  int Color; // eax
  int *p_m_nBlendWeightA; // ebx
  int SkillNum; // eax
  int v70; // esi
  int v71; // eax
  int v72; // eax
  int v73; // eax
  int result; // eax
  CameraCtrl *v75; // [esp+0x10] [ebp-0xC]
  _DWORD *v76; // [esp+0x14] [ebp-0x8]
  float *v77; // [esp+0x14] [ebp-0x8]
  gbColorQuad v78; // [esp+0x18] [ebp-0x4] BYREF
  int v79; // [esp+0x24] [ebp+0x8]

  v2 = v1;
  v75 = (CameraCtrl *)v1;
  v3 = (UIListBox *)(v1 + 239812);
  (((UIListBox *)(v1 + 239812)))->UIListBox::ClearAll();
  v4 = 0;
  v5 = (_DWORD *)(9536 * nVal + v2);
  v76 = (_DWORD *)v5;
  if ( (int)v5[838] > 0 )
  {
    v6 = (char *)(v2 + 104);
    v7 = (_DWORD *)(v76 + 841);
    do
    {
      sprintf(v6, "%s", *v7 + 28);
      v78.Color = (((UIListBox *)v3))->UIListBox::LoadListItems(v6, 0);
      if ( *(int *)(*v7 + 688) < 0 )
      {
        v8 = *(_DWORD *)(*v7 + 692);
        if ( v8 >= 0 )
          sprintf(v6, (const char *)&dir[20], v8);
      }
      else
      {
        sprintf(v6, (const char *)&dir[20], *(_DWORD *)(*v7 + 688));
      }
      (((UIListBox *)v3))->UIListBox::SetMouseMoveSel(1, v78.Color, v6, 0);
      ++v4;
      v7 += 3;
    }
    while ( v4 < v76[838] );
    v5 = (_DWORD *)v76;
  }
  (((UIListBox *)v3))->UIListBox::GetItem();
  (((UIListBox *)v3))->UIListBox::GetItem();
  for ( i = 0; i < v5[838]; ++i )
  {
    if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(i) )
    {
      if ( i < 0 || i >= v3->m_column[0].items.capacity )
        v10 = 0;
      else
        v10 = *(_DWORD *)&v3->m_column[0].items.m_pData[4 * i];
      *(_DWORD *)(v10 + 68) = (unsigned long)v3->m_fontcolor.Color;
    }
    else
    {
      UITabCtrl_SetItemParam(i);
    }
  }
  v11 = (UIListBox *)(&v75[58].m_CamBlocks + 141);
  (((UIListBox *)(&v75[58].m_CamBlocks + 141)))->UIListBox::ClearAll();
  v12 = (unsigned long)v5[2030];
  v78.Color = 0;
  if ( v12 > 0 )
  {
    m_szCamPath = v75->m_szCamPath;
    v14 = (_DWORD *)(v76 + 2033);
    do
    {
      sprintf(m_szCamPath, "%s", *v14 + 28);
      ListItems = (((UIListBox *)v11))->UIListBox::LoadListItems(m_szCamPath, 0);
      if ( *(int *)(*v14 + 688) <= 0 )
      {
        v16 = *(_DWORD *)(*v14 + 692);
        if ( v16 <= 0 )
          sprintf(m_szCamPath, (const char *)&dir[20], 0);
        else
          sprintf(m_szCamPath, (const char *)&dir[20], v16);
      }
      else
      {
        sprintf(m_szCamPath, (const char *)&dir[20], *(_DWORD *)(*v14 + 688));
      }
      (((UIListBox *)v11))->UIListBox::SetMouseMoveSel(1, ListItems, m_szCamPath, 0);
      sprintf(m_szCamPath, (const char *)&dir[20], *((unsigned __int16 *)v14 - 2) + 1);
      (((UIListBox *)v11))->UIListBox::SetMouseMoveSel(2, ListItems, m_szCamPath, 0);
      sprintf(m_szCamPath, (const char *)&dir[20], *((unsigned __int16 *)v14 - 1));
      (((UIListBox *)v11))->UIListBox::SetMouseMoveSel(3, ListItems, m_szCamPath, 0);
      v14 += 3;
      v17 = (unsigned long)v76[2030];
      ++v78.Color;
    }
    while ( (int)v78.Color < v17 );
  }
  (((UIListBox *)v11))->UIListBox::GetItem();
  (((UIListBox *)v11))->UIListBox::GetItem();
  for ( j = 0; j < v76[2030]; ++j )
  {
    if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(j) )
    {
      if ( j < 0 || j >= *(_DWORD *)&v75[59].m_szCamPath[228] )
        v19 = 0;
      else
        v19 = *(_DWORD *)(*(_DWORD *)&v75[59].m_szCamPath[224] + 4 * j);
      *(_DWORD *)(v19 + 68) = *(&v75[58].m_CamBlocks + 142);
    }
    else
    {
      UITabCtrl_SetItemParam(j);
    }
  }
  v20 = (UIListBox *)(&v75[59].m_nSlotParam + 27);
  (((UIListBox *)(&v75[59].m_nSlotParam + 27)))->UIListBox::ClearAll();
  v21 = (unsigned long)v76[1732];
  v78.Color = 0;
  if ( v21 > 0 )
  {
    v22 = v75->m_szCamPath;
    v23 = (_DWORD *)(v76 + 1735);
    do
    {
      sprintf(v22, "%s", *v23 + 28);
      v24 = (((UIListBox *)v20))->UIListBox::LoadListItems(v22, 0);
      if ( *(int *)(*v23 + 688) <= 0 )
      {
        v25 = *(_DWORD *)(*v23 + 692);
        if ( v25 <= 0 )
          sprintf(v22, (const char *)&dir[20], 0);
        else
          sprintf(v22, (const char *)&dir[20], v25);
      }
      else
      {
        sprintf(v22, (const char *)&dir[20], *(_DWORD *)(*v23 + 688));
      }
      (((UIListBox *)v20))->UIListBox::SetMouseMoveSel(1, v24, v22, 0);
      sprintf(v22, (const char *)&dir[20], *((unsigned __int16 *)v23 - 2) + 1);
      (((UIListBox *)v20))->UIListBox::SetMouseMoveSel(2, v24, v22, 0);
      sprintf(v22, (const char *)&dir[20], *((unsigned __int16 *)v23 - 1));
      (((UIListBox *)v20))->UIListBox::SetMouseMoveSel(3, v24, v22, 0);
      v23 += 3;
      v26 = (unsigned long)v76[1732];
      ++v78.Color;
    }
    while ( (int)v78.Color < v26 );
  }
  (((UIListBox *)v20))->UIListBox::GetItem();
  (((UIListBox *)v20))->UIListBox::GetItem();
  for ( k = 0; k < v76[1732]; ++k )
  {
    if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(k) )
    {
      if ( k < 0 || k >= *(&v75[59].m_nViewState + 69) )
        v28 = 0;
      else
        v28 = *(_DWORD *)(*(&v75[59].m_nViewState + 68) + 4 * k);
      *(_DWORD *)(v28 + 68) = *(&v75[59].m_nSlotParam + 28);
    }
    else
    {
      UITabCtrl_SetItemParam(k);
    }
  }
  v29 = (UIListBox *)(&v75[59].m_nViewBase + 50);
  (((UIListBox *)(&v75[59].m_nViewBase + 50)))->UIListBox::ClearAll();
  v30 = (unsigned long)v76[1136];
  v78.Color = 0;
  if ( v30 > 0 )
  {
    v31 = v75->m_szCamPath;
    v32 = (_DWORD *)(v76 + 1139);
    do
    {
      sprintf(v31, "%s", *v32 + 28);
      v33 = (((UIListBox *)v29))->UIListBox::LoadListItems(v31, 0);
      if ( *(int *)(*v32 + 688) <= 0 )
      {
        v34 = *(_DWORD *)(*v32 + 692);
        if ( v34 <= 0 )
          sprintf(v31, (const char *)&dir[20], 0);
        else
          sprintf(v31, (const char *)&dir[20], v34);
      }
      else
      {
        sprintf(v31, (const char *)&dir[20], *(_DWORD *)(*v32 + 688));
      }
      (((UIListBox *)v29))->UIListBox::SetMouseMoveSel(1, v33, v31, 0);
      sprintf(v31, (const char *)&dir[20], *((unsigned __int16 *)v32 - 2) + 1);
      (((UIListBox *)v29))->UIListBox::SetMouseMoveSel(2, v33, v31, 0);
      sprintf(v31, (const char *)&dir[20], *((unsigned __int16 *)v32 - 1));
      (((UIListBox *)v29))->UIListBox::SetMouseMoveSel(3, v33, v31, 0);
      v32 += 3;
      v35 = (unsigned long)v76[1136];
      ++v78.Color;
    }
    while ( (int)v78.Color < v35 );
  }
  (((UIListBox *)v29))->UIListBox::GetItem();
  (((UIListBox *)v29))->UIListBox::GetItem();
  for ( m = 0; m < v76[1136]; ++m )
  {
    if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(m) )
    {
      if ( m < 0 || m >= *((_DWORD *)&v75[59].m_nViewBase + 176) )
        v37 = 0;
      else
        v37 = *(_DWORD *)(*((_DWORD *)&v75[59].m_nViewBase + 175) + 4 * m);
      *(_DWORD *)(v37 + 68) = *((_DWORD *)&v75[59].m_nViewBase + 51);
    }
    else
    {
      UITabCtrl_SetItemParam(m);
    }
  }
  v38 = (UIListBox *)(&v75[59].m_CamBlocks + 25);
  (((UIListBox *)(&v75[59].m_CamBlocks + 25)))->UIListBox::ClearAll();
  v39 = (unsigned long)v76[1434];
  v78.Color = 0;
  if ( v39 > 0 )
  {
    v40 = v75->m_szCamPath;
    v41 = (_DWORD *)(v76 + 1437);
    do
    {
      sprintf(v40, "%s", *v41 + 28);
      v42 = (((UIListBox *)v38))->UIListBox::LoadListItems(v40, 0);
      if ( *(int *)(*v41 + 688) <= 0 )
      {
        v43 = *(_DWORD *)(*v41 + 692);
        if ( v43 <= 0 )
          sprintf(v40, (const char *)&dir[20], 0);
        else
          sprintf(v40, (const char *)&dir[20], v43);
      }
      else
      {
        sprintf(v40, (const char *)&dir[20], *(_DWORD *)(*v41 + 688));
      }
      (((UIListBox *)v38))->UIListBox::SetMouseMoveSel(1, v42, v40, 0);
      sprintf(v40, (const char *)&dir[20], *((unsigned __int16 *)v41 - 2) + 1);
      (((UIListBox *)v38))->UIListBox::SetMouseMoveSel(2, v42, v40, 0);
      sprintf(v40, (const char *)&dir[20], *((unsigned __int16 *)v41 - 1));
      (((UIListBox *)v38))->UIListBox::SetMouseMoveSel(3, v42, v40, 0);
      v41 += 3;
      v44 = (unsigned long)v76[1434];
      ++v78.Color;
    }
    while ( (int)v78.Color < v44 );
  }
  (((UIListBox *)v38))->UIListBox::GetItem();
  (((UIListBox *)v38))->UIListBox::GetItem();
  for ( n = 0; n < v76[1434]; ++n )
  {
    if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(n) )
    {
      if ( n < 0 || n >= *(&v75[59].m_CamBlocks + 151) )
        v46 = 0;
      else
        v46 = *(_DWORD *)(*(&v75[59].m_CamBlocks + 150) + 4 * n);
      *(_DWORD *)(v46 + 68) = *(&v75[59].m_CamBlocks + 26);
    }
    else
    {
      UITabCtrl_SetItemParam(n);
    }
  }
  p_m_fDefaultPosX = (UIListBox *)&v75[60].m_fDefaultPosX;
  (((UIListBox *)&v75[60].m_fDefaultPosX))->UIListBox::ClearAll();
  v48 = (unsigned long)v76[2328];
  v78.Color = 0;
  if ( v48 > 0 )
  {
    v49 = v75->m_szCamPath;
    v50 = (_DWORD *)(v76 + 2331);
    do
    {
      sprintf(v49, "%s", *v50 + 28);
      v51 = (((UIListBox *)p_m_fDefaultPosX))->UIListBox::LoadListItems(v49, 0);
      if ( *(int *)(*v50 + 688) <= 0 )
      {
        v52 = *(_DWORD *)(*v50 + 692);
        if ( v52 <= 0 )
          sprintf(v49, (const char *)&dir[20], 0);
        else
          sprintf(v49, (const char *)&dir[20], v52);
      }
      else
      {
        sprintf(v49, (const char *)&dir[20], *(_DWORD *)(*v50 + 688));
      }
      (((UIListBox *)p_m_fDefaultPosX))->UIListBox::SetMouseMoveSel(1, v51, v49, 0);
      sprintf(v49, (const char *)&dir[20], *((unsigned __int16 *)v50 - 2) + 1);
      (((UIListBox *)p_m_fDefaultPosX))->UIListBox::SetMouseMoveSel(2, v51, v49, 0);
      sprintf(v49, (const char *)&dir[20], *((unsigned __int16 *)v50 - 1));
      (((UIListBox *)p_m_fDefaultPosX))->UIListBox::SetMouseMoveSel(3, v51, v49, 0);
      v50 += 3;
      v53 = (unsigned long)v76[2328];
      ++v78.Color;
    }
    while ( (int)v78.Color < v53 );
  }
  (((UIListBox *)p_m_fDefaultPosX))->UIListBox::GetItem();
  (((UIListBox *)p_m_fDefaultPosX))->UIListBox::GetItem();
  for ( ii = 0; ii < v76[2328]; ++ii )
  {
    if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(ii) )
    {
      if ( ii < 0 || ii >= *(&v75[60].m_nSlotParam + 37) )
        v55 = 0;
      else
        v55 = *(_DWORD *)(*(&v75[60].m_nSlotParam + 36) + 4 * ii);
      *(float *)(v55 + 68) = v75[60].m_fDefaultPosY;
    }
    else
    {
      UITabCtrl_SetItemParam(ii);
    }
  }
  v56 = (UIListBox *)(&v75[60].m_nViewState + 129);
  (((UIListBox *)(&v75[60].m_nViewState + 129)))->UIListBox::ClearAll();
  v57 = (unsigned long)v76[2626];
  v78.Color = 0;
  if ( v57 > 0 )
  {
    v58 = v75->m_szCamPath;
    v59 = (_DWORD *)(v76 + 2629);
    do
    {
      sprintf(v58, "%s", *v59 + 28);
      v60 = (((UIListBox *)v56))->UIListBox::LoadListItems(v58, 0);
      if ( *(int *)(*v59 + 688) <= 0 )
      {
        v61 = *(_DWORD *)(*v59 + 692);
        if ( v61 <= 0 )
          sprintf(v58, (const char *)&dir[20], 0);
        else
          sprintf(v58, (const char *)&dir[20], v61);
      }
      else
      {
        sprintf(v58, (const char *)&dir[20], *(_DWORD *)(*v59 + 688));
      }
      (((UIListBox *)v56))->UIListBox::SetMouseMoveSel(1, v60, v58, 0);
      sprintf(v58, (const char *)&dir[20], *((unsigned __int16 *)v59 - 2) + 1);
      (((UIListBox *)v56))->UIListBox::SetMouseMoveSel(2, v60, v58, 0);
      sprintf(v58, (const char *)&dir[20], *((unsigned __int16 *)v59 - 1));
      (((UIListBox *)v56))->UIListBox::SetMouseMoveSel(3, v60, v58, 0);
      v59 += 3;
      v62 = (unsigned long)v76[2626];
      ++v78.Color;
    }
    while ( (int)v78.Color < v62 );
  }
  (((UIListBox *)v56))->UIListBox::GetItem();
  (((UIListBox *)v56))->UIListBox::GetItem();
  for ( jj = 0; jj < v76[2626]; ++jj )
  {
    if ( (unsigned __int8)CameraCtrl_HandleCameraEvent(jj) )
    {
      if ( jj < 0 || jj >= *((_DWORD *)&v75[60].m_nViewBase + 60) )
        v64 = 0;
      else
        v64 = *(_DWORD *)(*((_DWORD *)&v75[60].m_nViewBase + 59) + 4 * jj);
      *(_DWORD *)(v64 + 68) = *(&v75[60].m_nViewState + 130);
    }
    else
    {
      UITabCtrl_SetItemParam(jj);
    }
  }
  v65 = (CameraCtrl *)v75;
  (((CameraCtrl *)v75))->CameraCtrl::LoadRoleParams();
  v66 = (UIListBox *)(&v75[60].m_nViewBase + 236);
  (((UIListBox *)(&v75[60].m_nViewBase + 236)))->UIListBox::ClearAll();
  Color = 0;
  v78.Color = 0;
  p_m_nBlendWeightA = (int *)&v75->m_nBlendWeightA;
  v77 = (float *)(&v75->m_roleParams + nVal);
  do
  {
    if ( g_SaveSlotFlags[8 * nVal + Color] )
    {
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(p_m_nBlendWeightA - 65));
      if ( !SkillNum )
        break;
      lstrcpyA((LPSTR)p_m_nBlendWeightA - 256, (LPCSTR)(SkillNum + 4));
      v70 = -1;
      if ( *p_m_nBlendWeightA )
      {
        v71 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*p_m_nBlendWeightA);
        if ( v71 )
          v70 = (((UIListBox *)v66))->UIListBox::LoadListItems((char *)(v71 + 4), 0);
      }
      if ( p_m_nBlendWeightA[1] )
      {
        v72 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_m_nBlendWeightA[1]);
        if ( v72 )
        {
          if ( v70 >= 0 )
            (((UIListBox *)v66))->UIListBox::SetMouseMoveSel(1, v70, (char *)(v72 + 4), 0);
        }
      }
      if ( p_m_nBlendWeightA[2] )
      {
        v73 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_m_nBlendWeightA[2]);
        if ( v73 )
        {
          if ( v70 >= 0 )
            (((UIListBox *)v66))->UIListBox::SetMouseMoveSel(2, v70, (char *)(v73 + 4), 0);
        }
      }
      sprintf(v75->m_szCamPath, "%d%%", (unsigned int)(__int64)(*v77 * 100.0));
      (((UIListBox *)v66))->UIListBox::SetMouseMoveSel(3, v70, v75->m_szCamPath, 0);
      v65 = (CameraCtrl *)v75;
      *(p_m_nBlendWeightA - 67) = nVal;
      Color = v78.Color;
      *(p_m_nBlendWeightA - 66) = v70;
    }
    ++Color;
    p_m_nBlendWeightA += 75;
    v78.Color = Color;
    v77 += 75;
  }
  while ( Color < 8 );
  MagicUI_InitUILayout(v79);
  (((UIListBox *)v66))->UIListBox::GetItem();
  (((UIListBox *)v66))->UIListBox::GetItem();
  SetEnable((UICaption *)(&v65[51].m_CamBlocks + 38));
  SetEnable((UICaption *)(&v65[51].m_CamBlocks + 76));
  return result;
}

// 0x0048C610
int CameraCtrl_HandleCameraEvent(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // ebp
  int v4; // eax
  int result; // eax
  int v6; // ebx
  int v7; // esi
  char v8; // al
  CScreenMode *Instance; // eax
  _BYTE *v10; // eax
  unsigned __int8 *v11; // edx
  int v12; // ecx
  _WORD *v13; // eax
  __int16 *v14; // esi
  int v15; // ecx
  char v16; // al
  int v17; // ebp
  _BYTE *v18; // edx
  signed __int16 *p_m_nAnimFrame; // ecx
  int v20; // esi
  int v21; // eax
  const void *v22; // [esp-0x8] [ebp-0x38]
  char v23; // [esp+0x13] [ebp-0x1D]
  int v24; // [esp+0x14] [ebp-0x1C]
  int v25; // [esp+0x18] [ebp-0x18]
  int nVala; // [esp+0x34] [ebp+0x4]
  int v27; // [esp+0x38] [ebp+0x8]
  char v28; // [esp+0x3C] [ebp+0xC]

  v2 = v1;
  v3 = 0;
  v23 = 1;
  v4 = *(_DWORD *)(v1 + 205784);
  *(_BYTE *)(v1 + 911) = 1;
  result = v1 + 12 * nVal + 1192 * (v27 + 8 * v4) + 3356;
  v24 = result;
  if ( !*(_DWORD *)(result + 8) )
    goto LABEL_56;
  if ( v28 )
  {
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
      if ( *(_BYTE *)(v2 + v7 + 877) )
      {
        (((CameraCtrl *)v2))->CameraCtrl::CalcStatPower(result);
        if ( v8 )
          ++v6;
      }
      if ( ++v7 >= 5 )
        break;
      result = v24;
    }
    if ( v6 <= 0 )
    {
      sprintf((char *const)(v2 + 104), "\\n        %s", (const char *)&dword_DC9F3C);
      SetEnable((UICaption *)(v2 + 207612));
      (((UIRoleSelect *)(v2 + 207156)))->UIRoleSelect::SetByte(1);
      v22 = off_5C7764;
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v22, 1);
      *(_BYTE *)(v2 + 911) = 0;
      return 0;
    }
  }
  v10 = (_BYTE *)(v2 + 877);
  nVala = 0;
  v25 = v2 + 877;
  v11 = (unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 7;
  do
  {
    if ( *v10 )
    {
      v12 = 0;
      v13 = (_WORD *)*(_WORD **)(v24 + 8);
      v14 = (__int16 *)(v13 + 296);
      do
      {
        if ( *v14 > 0 )
          v3 += *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + v12 + nVala)
              - g_RoleSlotBuf.m_partyActor.m_dwMatMsg[v12 + 2 + nVala];
        if ( v13[311] )
          v3 += *(v11 - 1);
        if ( v13[312] )
          v3 += *v11;
        if ( v13[309] )
          v3 += *(v11 - 3);
        if ( v13[310] )
          v3 += *(v11 - 2);
        if ( v13[313] )
          v3 += v11[1];
        ++v12;
        ++v14;
      }
      while ( v12 < 12 );
    }
    v11 += 1408;
    v10 = (_BYTE *)++v25;
    nVala += 352;
  }
  while ( (int)v11 < (int)byte_C061CF );
  if ( v3 > 0 )
    v23 = 0;
  v15 = *(_DWORD *)(v24 + 8);
  v16 = *(_BYTE *)(v15 + 577);
  if ( v16 == 1 || v16 == 2 )
  {
    result = 1408 * *(_DWORD *)(v2 + 205784);
    if ( *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[3] + result) < *(_DWORD *)(v15 + 688)
      || *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[4] + result) < *(_DWORD *)(v15 + 692) )
    {
      if ( v27 )
        sprintf((char *const)(v2 + 104), "\\n      %s", (const char *)&dword_DCA03C);
      else
        sprintf((char *const)(v2 + 104), "\\n      %s", (const char *)&dword_DD213C);
      SetEnable((UICaption *)(v2 + 207612));
      if ( !v28 )
        goto LABEL_55;
      goto LABEL_54;
    }
    if ( *(_DWORD *)(v15 + 696) == 10 )
    {
      v17 = 0;
      v18 = (_BYTE *)(v2 + 877);
      p_m_nAnimFrame = (signed __int16 *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame;
      v20 = 2 * *(int *)((char *)&g_RoleSlotBuf.m_partyActor.m_pRoleObj + result) + 40;
      do
      {
        if ( *v18 )
        {
          v21 = *(_DWORD *)p_m_nAnimFrame - *((_DWORD *)p_m_nAnimFrame + 12);
          if ( v21 >= v20 )
            v21 = v20;
          v17 += v21;
        }
        p_m_nAnimFrame += 704;
        ++v18;
      }
      while ( (int)p_m_nAnimFrame < (int)word_C062BC );
      result = *(&g_RoleSlotBuf.dword_17AA450 + 147);
      if ( *(&g_RoleSlotBuf.dword_17AA450 + 147) < v17 || *(&g_RoleSlotBuf.dword_17AA450 + 147) <= 0 || v17 <= 0 )
      {
        sprintf((char *const)(v2 + 104), "\\n      %s", (const char *)&dword_DD273C);
        SetEnable((UICaption *)(v2 + 207612));
        if ( v28 )
        {
          result = (((UIRoleSelect *)(v2 + 207156)))->UIRoleSelect::SetByte(1);
          return 0;
        }
        goto LABEL_56;
      }
    }
    if ( !v23 )
    {
      return 1;
    }
  }
  sprintf((char *const)(v2 + 104), "\\n        %s", (const char *)&dword_DC9F3C);
  SetEnable((UICaption *)(v2 + 207612));
  if ( v28 )
LABEL_54:
    result = (((UIRoleSelect *)(v2 + 207156)))->UIRoleSelect::SetByte(1);
LABEL_55:
  *(_BYTE *)(v2 + 911) = 0;
LABEL_56:
  return 0;
}

// 0x0048C9A0
int CameraCtrl_ProcessCameraTask(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  int v3; // edx
  int v4; // ecx
  void (***v5)(_DWORD, _DWORD); // esi
  int v6; // edi
  int v7; // ecx
  signed __int16 *p_m_nAnimFrame; // esi
  unsigned __int8 *v9; // edx
  int v10; // eax
  _WORD *v11; // edi
  int v12; // ecx
  int v13; // ebx
  void (***v14)(_DWORD, _DWORD); // esi
  int v15; // edi
  int result; // eax
  int v17; // eax
  int v18; // edi
  int v19; // esi
  int v20; // eax
  int *v21; // edx
  char v22; // al
  char v23; // al
  int v24; // esi
  void ( ***v25)(_DWORD, int); // edi
  char v26; // al
  char v27; // [esp+0x13] [ebp-0x41]
  signed __int16 *v28; // [esp+0x14] [ebp-0x40]
  int v29; // [esp+0x18] [ebp-0x3C]
  int v30; // [esp+0x1C] [ebp-0x38]
  int v31; // [esp+0x20] [ebp-0x34]
  _DWORD v32[5]; // [esp+0x2C] [ebp-0x28] BYREF
  _DWORD v33[5]; // [esp+0x40] [ebp-0x14] BYREF
  _BYTE *nVala; // [esp+0x58] [ebp+0x4]
  int v35; // [esp+0x5C] [ebp+0x8]

  v2 = v1;
  memset(&v32[1], 0, 16);
  memset(&v33[1], 0, 16);
  v3 = *(_DWORD *)(v1 + 205784);
  *(_BYTE *)(v1 + 911) = 1;
  v31 = 12 * nVal;
  v32[0] = 0;
  v33[0] = 0;
  v27 = 1;
  v4 = 12 * nVal + 1192 * (v35 + 8 * v3);
  v30 = v4 + v2 + 3356;
  if ( !*(_DWORD *)(v4 + v2 + 3364) )
  {
    v5 = (void ( ***)(_DWORD, _DWORD))(v2 + 217324);
    v6 = 5;
    do
    {
      (**v5)((_DWORD)(v5), (_DWORD)(0));
      v5 += 1223;
      --v6;
    }
    while ( v6 );
  }
  v7 = 592;
  p_m_nAnimFrame = (signed __int16 *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame;
  v29 = 592;
  v28 = (signed __int16 *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame;
  do
  {
    v9 = (unsigned __int8 *)&g_RoleSlotBuf.m_partyActor.m_Actor + 7;
    nVala = (_BYTE *)(v2 + 877);
    v10 = 0;
    do
    {
      if ( *nVala )
      {
        v11 = (_WORD *)*(_WORD **)(v30 + 8);
        if ( *(_WORD *)((char *)v11 + v7) )
        {
          v12 = *(_DWORD *)(v2 + 205784);
          v32[v10] += *(_DWORD *)p_m_nAnimFrame - *((_DWORD *)p_m_nAnimFrame + 12);
          v13 = *(_DWORD *)(v31 + 1192 * (v35 + 8 * v12) + v2 + 3364);
          v7 = v29;
          v33[v10] += *(__int16 *)(v13 + v29);
        }
        if ( v11[311] )
        {
          v32[v10] += *(v9 - 1);
          ++v33[v10];
        }
        if ( v11[312] )
        {
          v32[v10] += *v9;
          ++v33[v10];
        }
        if ( v11[309] )
        {
          v32[v10] += *(v9 - 3);
          ++v33[v10];
        }
        if ( v11[310] )
        {
          v32[v10] += *(v9 - 2);
          ++v33[v10];
        }
        if ( v11[313] )
        {
          v32[v10] += v9[1];
          ++v33[v10];
        }
        if ( (int)v33[v10] > 0 )
          v27 = 0;
      }
      v9 += 1408;
      p_m_nAnimFrame += 704;
      ++v10;
      ++nVala;
    }
    while ( (int)v9 < (int)byte_C061CF );
    v7 += 2;
    p_m_nAnimFrame = (signed __int16 *)(v28 + 2);
    v29 = v7;
    v28 += 2;
  }
  while ( (int)v28 < (int)&g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] );
  if ( v27 )
  {
    v14 = (void ( ***)(_DWORD, _DWORD))(v2 + 217324);
    v15 = 5;
    do
    {
      (**v14)((_DWORD)(v14), (_DWORD)(0));
      v14 += 1223;
      --v15;
    }
    while ( v15 );
    *(_BYTE *)(v2 + 911) = 0;
    return -2;
  }
  else
  {
    v17 = 0;
    while ( !*(_BYTE *)(v17 + v2 + 877) )
    {
      if ( ++v17 >= 5 )
      {
        v18 = 0;
        goto LABEL_32;
      }
    }
    v18 = v32[v17];
LABEL_32:
    v19 = 0;
    v20 = 0;
    v21 = v32;
    do
    {
      if ( *(_BYTE *)(v20 + v2 + 877) && *v21 > v18 )
      {
        v18 = (unsigned long)*v21;
        v19 = v20;
      }
      ++v20;
      ++v21;
    }
    while ( v20 < 5 );
    if ( !v32[v19] )
      v19 = v18;
    v22 = *(_BYTE *)(*(_DWORD *)(v30 + 8) + 577);
    if ( v22 == 1 )
    {
      (((CameraCtrl *)v2))->CameraCtrl::CalcStatPower(v30);
      if ( v23 )
        (**(void ( ***)(int, int))(4892 * v19 + v2 + 217324))((int)(4892 * v19 + v2 + 217324), (int)(1));
      result = v19;
      *(_BYTE *)(v2 + 912) = 0;
    }
    else if ( v22 == 2 )
    {
      v24 = 0;
      v25 = (void ( ***)(_DWORD, int))(v2 + 217324);
      do
      {
        if ( *(_BYTE *)(v24 + v2 + 877) )
        {
          (((CameraCtrl *)v2))->CameraCtrl::CalcStatPower(v30);
          if ( v26 )
            (**v25)((_DWORD)((_DWORD)(v25)), (int)(1));
        }
        else
        {
          (**v25)((_DWORD)((_DWORD)(v25)), (int)(0));
        }
        ++v24;
        v25 += 1223;
      }
      while ( v24 < 5 );
      result = -1;
      *(_BYTE *)(v2 + 912) = 1;
    }
    else
    {
      return -3;
    }
  }
  return result;
}

// 0x0048CCE0
int CameraCtrl_InitBlendState(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // ecx
  int v5; // edi
  _DWORD *v6; // eax
  int result; // eax
  int v8; // ebp
  int v9; // ebx
  int *TargetRole; // edx
  int v11; // eax
  int v12; // ecx
  int *v13; // eax
  int v14; // ecx
  int v15; // ecx
  int *v16; // eax
  int v17; // [esp+0x10] [ebp-0x1C]
  int p_DWORD; // [esp+0x14] [ebp-0x18] BYREF
  int v19; // [esp+0x18] [ebp-0x14]
  int SkillNum; // [esp+0x1C] [ebp-0x10]
  char pOut[12]; // [esp+0x20] [ebp-0xC] BYREF
  int nVala; // [esp+0x30] [ebp+0x4]

  v2 = v1;
  v3 = 0;
  v4 = *(_DWORD *)(v1 + 205784);
  v5 = 0;
  v6 = (_DWORD *)(v2 + 924);
  while ( v4 != *(v6 - 1) || nVal != *v6 )
  {
    ++v5;
    v6 += 75;
    if ( v5 >= 8 )
      goto LABEL_5;
  }
  p_DWORD = 0xFFFF;
  v19 = 0;
  SkillNum = 0;
  v17 = 0;
  nVala = 0;
  v8 = 0;
  if ( ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount() > 0 )
  {
    v9 = v2 + 300 * v5;
    do
    {
      TargetRole = (int *)(((CCBAI *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBAI::GetTargetRole(pOut);
      v11 = (unsigned long)*TargetRole;
      p_DWORD = v11;
      v12 = (unsigned long)TargetRole[1];
      v19 = v12;
      SkillNum = (unsigned long)TargetRole[2];
      if ( v11 == *(_DWORD *)(v9 + 1188) )
        v17 = v12;
      if ( v11 == *(_DWORD *)(v9 + 1192) )
        nVala = v12;
      ++v8;
    }
    while ( v8 < ((Combat *)((Combat *)&g_RoleSlotBuf.dword_17AA450 + 138))->Combat::GetSlotCount() );
    v3 = v17;
  }
  v13 = (int *)(v2 + 300 * v5);
  if ( v13[297] == v13[298] )
    *(_DWORD *)(v2 + 916) = 2;
  else
    *(_DWORD *)(v2 + 916) = 0;
  v14 = (unsigned long)v13[297];
  if ( v14 == v13[298] && v14 == v13[299] )
    *(_DWORD *)(v2 + 916) = 3;
  v15 = *(_DWORD *)(v2 + 916);
  if ( v3 < v15 && nVala < v15 || v3 <= 0 && nVala <= 0 || v3 < 1 || nVala < 1 )
  {
    sprintf((char *const)(v2 + 104), "\\n\\n\\n        %s", &dword_DC8A3C);
  }
  else
  {
    p_DWORD = (unsigned long)v13[232];
    SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(p_DWORD);
    v16 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex(&p_DWORD);
    if ( !v16 || v16[1] < 99 )
    {
LABEL_5:
      result = (((MainPropUI *)v2))->MainPropUI::FindValidSaveSlot();
      return 1;
    }
    sprintf((char *const)(v2 + 104), "\\n\\n\\n         %s", &dword_DCCC3C);
  }
  SetEnable((UICaption *)(v2 + 206244));
  (((UIRoleSelect *)(v2 + 205788)))->UIRoleSelect::SetByte(1);
  result = sub_445E50(v2 + 248268);
  *(_BYTE *)(v2 + 911) = 0;
  *(_DWORD *)(v2 + 916) = 0;
  return 0;
}

// 0x0048D5D0
int CameraCtrl_CreateCameraUI(int nVal)
{
  int v1; // ecx
  int v2; // esi
  _DWORD *v3; // edi
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // ecx
  UIScene *v17; // edi
  int v18; // ecx
  int v19; // eax
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
  int v31; // ecx
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  UIPushButton *v35; // edi
  int v36; // ebx
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // edx
  int v41; // eax
  int v42; // edx
  int v43; // eax
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // edx
  int v48; // eax
  int v49; // edx
  int v50; // eax
  int v51; // eax
  int i; // edi
  int v53; // eax
  int v54; // edx
  int v55; // edx
  int v56; // ecx
  int v57; // eax
  int v58; // edx
  int v59; // eax
  int result; // eax
  int v61; // [esp+0x244] [ebp-B8h]
  int v62; // [esp+0x244] [ebp-B8h]
  int *v63; // [esp+0x248] [ebp-B4h]
  int v64; // [esp+0x24C] [ebp-B0h]
  _DWORD v65[2]; // [esp+0x258] [ebp-A4h] BYREF
  int v66; // [esp+0x260] [ebp-0x9C]
  int v67; // [esp+0x264] [ebp-0x98]
  int v68; // [esp+0x268] [ebp-0x94] BYREF
  int v69; // [esp+0x26C] [ebp-0x90]
  int v70; // [esp+0x270] [ebp-0x8C]
  int v71; // [esp+0x274] [ebp-0x88]
  int pnVal; // [esp+0x278] [ebp-0x84] BYREF
  int v73; // [esp+0x27C] [ebp-0x80]
  int v74; // [esp+0x280] [ebp-0x7C]
  int v75; // [esp+0x284] [ebp-0x78]
  int v76; // [esp+0x288] [ebp-0x74] BYREF
  int v77; // [esp+0x28C] [ebp-0x70]
  int v78; // [esp+0x290] [ebp-0x6C]
  int v79; // [esp+0x294] [ebp-0x68]
  int v80; // [esp+0x298] [ebp-0x64] BYREF
  int v81; // [esp+0x29C] [ebp-0x60]
  int v82; // [esp+0x2A0] [ebp-0x5C]
  int v83; // [esp+0x2A4] [ebp-0x58]
  int v84; // [esp+0x2A8] [ebp-0x54] BYREF
  int v85; // [esp+0x2AC] [ebp-0x50]
  int v86; // [esp+0x2B0] [ebp-0x4C]
  int v87; // [esp+0x2B4] [ebp-0x48]
  int v88; // [esp+0x2B8] [ebp-0x44]
  int v89; // [esp+0x2BC] [ebp-0x40] BYREF
  int v90; // [esp+0x2C0] [ebp-0x3C]
  int v91; // [esp+0x2C4] [ebp-0x38]
  int v92; // [esp+0x2C8] [ebp-0x34]
  int v93; // [esp+0x2CC] [ebp-0x30] BYREF
  int v94; // [esp+0x2D0] [ebp-0x2C]
  int v95; // [esp+0x2D4] [ebp-0x28]
  int v96; // [esp+0x2D8] [ebp-0x24]
  _DWORD v97[4]; // [esp+0x2DC] [ebp-0x20] BYREF
  int nVal2[4]; // [esp+0x2EC] [ebp-0x10] BYREF

  v2 = v1;
  v3 = (_DWORD *)(v1 + 72);
  *(_DWORD *)(v1 + 76) = 0;
  *(_DWORD *)(v1 + 72) = 0;
  *(_DWORD *)(v1 + 80) = *(_DWORD *)(v1 + 88);
  *(_DWORD *)(v1 + 84) = *(_DWORD *)(v1 + 92);
  (((UIListBox *)v1))->UIListBox::SetSelTexture(-1, *(_DWORD *)(v1 + 72), *(_DWORD *)(v1 + 76), *(_DWORD *)(v1 + 80), *(_DWORD *)(v1 + 84));
  v4 = *(_DWORD *)(v2 + 76) + 18;
  v84 = (unsigned long)(*v3 + 592);
  v85 = v4;
  v86 = v84 + 192;
  v87 = v4 + 526;
  (*(void ( **)(int, int, int *, int))(*(_DWORD *)(v2 + 51036) + 16))(v2 + 51036, 161, &v84, v2);
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)(v2 + 51036)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Frame.tga", v5);
  v6 = *(_DWORD *)(v2 + 51188);
  v85 += 26;
  v84 = v86;
  v87 = v85 + 526;
  v86 += 17;
  (*(void ( **)(int, int, int *, int))(v6 + 16))(v2 + 51188, 161, &v84, v2);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)(v2 + 51188)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Frame_Line.tga", v7);
  v77 = 0;
  v76 = v86 - 205;
  v78 = v86 - 205 + 203;
  v8 = *(_DWORD *)(v2 + 51340);
  v79 = 64;
  (*(void ( **)(int, int, int *, int))(v8 + 16))(v2 + 51340, 161, &v76, v2);
  LOBYTE(v9) = g_bDebugMode;
  (((UIPushButton *)(v2 + 51340)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\TimeMoney.tga", v9);
  v10 = *(_DWORD *)(v2 + 55988);
  v77 = -4;
  v76 = 618;
  v78 = 738;
  v79 = 28;
  (*(void ( **)(int, int, int *, int))(v10 + 16))(v2 + 55988, 161, &v76, v2);
  (((UIScene *)(v2 + 55988)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 55988));
  v11 = *(_DWORD *)(v2 + 55836);
  v77 = 16;
  v76 = 668;
  v78 = 748;
  v79 = 48;
  (*(void ( **)(int, int, int *, int))(v11 + 16))(v2 + 55836, 161, &v76, v2);
  (((UIScene *)(v2 + 55836)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 55836));
  MainPropUI_CreateCoverTemplate(v61);
  v12 = *(_DWORD *)(v2 + 210320);
  v90 = 125;
  v89 = 213;
  v91 = 586;
  v92 = 519;
  (*(void ( **)(int, int *, int *, int))(v12 + 16))(v2 + 210320, &byte_A00001, &v89, v2);
  LOBYTE(v13) = g_bDebugMode;
  (((UIPushButton *)(v2 + 210320)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\ListFrame.tga", v13);
  v14 = *(_DWORD *)(v2 + 210236);
  v97[1] = v90;
  v97[0] = v89 + 7;
  v97[3] = v90 + 32;
  v97[2] = v89 + 365;
  (*(void ( **)(int, int *, _DWORD *, char *, _DWORD, int))(v14 + 28))(
    v2 + 210236,
    &byte_A00001,
    (_DWORD *)(v97),
    "UI\\Flex\\Bar.tga",
    0,
    v2);
  (((CScreenMode *)(v2 + 210236)))->CScreenMode::SetPosition(32,   32);
  v15 = v89 + 18;
  *(_DWORD *)(v2 + 55216) = v90 + 52;
  *(_DWORD *)(v2 + 55212) = v15;
  v16 = *(_DWORD *)(v2 + 55216);
  *(_DWORD *)(v2 + 55220) = v15 + 376;
  *(_DWORD *)(v2 + 55224) = v16 + 32;
  v17 = (UIScene *)(v2 + 55228);
  v88 = 4;
  do
  {
    (*(void ( **)(UIScene *, int *, int, int))(*(_DWORD *)((UIWnd *)v17) + 16))(
      v17,
      &byte_A00001,
      v2 + 55212,
      v2);
    (((UIScene *)v17))->UIScene::SetShow(0);
    AllocObject(v17);
    (**(void ( ***)(UIScene *, _DWORD))((UIWnd *)v17))((UIScene *)(v17), (_DWORD)(0));
    v17 = (UIScene *)((char *)v17 + 152);
    --v88;
  }
  while ( v88 );
  LOBYTE(v18) = g_bDebugMode;
  v19 = *(_DWORD *)(v2 + 239812);
  v81 = 207;
  v80 = 232;
  v82 = 566;
  v83 = 485;
  v20 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(v19 + 28))(
          v2 + 239812,
          &byte_A00217,
          &v80,
          v2,
          0,
          0,
          v18);
  LOBYTE(v20) = g_bDebugMode;
  (((UIListBox *)(v2 + 239812)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v20);
  *(_DWORD *)(v2 + 240972) = -8;
  *(_DWORD *)(v2 + 240976) = -8;
  *(_DWORD *)(v2 + 240980) = 14;
  (((UIListBox *)(v2 + 239812)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 239812)))->UIListBox::SetColumnHead((int)"Name", 276);
  (((UIListBox *)(v2 + 239812)))->UIListBox::SetColumnHead((int)&off_5C91C8, 92);
  (**(void ( ***)(int, _DWORD))(v2 + 239812))((int)(v2 + 239812), (_DWORD)(0));
  LOBYTE(v21) = g_bDebugMode;
  v22 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 241020) + 28))(
          v2 + 241020,
          &byte_A00218,
          &v80,
          v2,
          0,
          0,
          v21);
  LOBYTE(v22) = g_bDebugMode;
  (((UIListBox *)(v2 + 241020)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v22);
  *(_DWORD *)(v2 + 242180) = -8;
  *(_DWORD *)(v2 + 242184) = -8;
  *(_DWORD *)(v2 + 242188) = 14;
  (((UIListBox *)(v2 + 241020)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 241020)))->UIListBox::SetColumnHead((int)"Name", 150);
  (((UIListBox *)(v2 + 241020)))->UIListBox::SetColumnHead((int)&off_5C91C8, 72);
  (((UIListBox *)(v2 + 241020)))->UIListBox::SetColumnHead((int)"Lv", 38);
  (((UIListBox *)(v2 + 241020)))->UIListBox::SetColumnHead((int)"UseTimes", 72);
  (**(void ( ***)(int, _DWORD))(v2 + 241020))((int)(v2 + 241020), (_DWORD)(0));
  LOBYTE(v23) = g_bDebugMode;
  v24 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 242228) + 28))(
          v2 + 242228,
          &byte_A00219,
          &v80,
          v2,
          0,
          0,
          v23);
  LOBYTE(v24) = g_bDebugMode;
  (((UIListBox *)(v2 + 242228)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v24);
  *(_DWORD *)(v2 + 243388) = -8;
  *(_DWORD *)(v2 + 243392) = -8;
  *(_DWORD *)(v2 + 243396) = 14;
  (((UIListBox *)(v2 + 242228)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 242228)))->UIListBox::SetColumnHead((int)"Name", 150);
  (((UIListBox *)(v2 + 242228)))->UIListBox::SetColumnHead((int)&off_5C91C8, 72);
  (((UIListBox *)(v2 + 242228)))->UIListBox::SetColumnHead((int)"Lv", 38);
  (((UIListBox *)(v2 + 242228)))->UIListBox::SetColumnHead((int)"UseTimes", 72);
  (**(void ( ***)(int, _DWORD))(v2 + 242228))((int)(v2 + 242228), (_DWORD)(0));
  LOBYTE(v25) = g_bDebugMode;
  v26 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 243436) + 28))(
          v2 + 243436,
          &byte_A00220,
          &v80,
          v2,
          0,
          0,
          v25);
  LOBYTE(v26) = g_bDebugMode;
  (((UIListBox *)(v2 + 243436)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v26);
  *(_DWORD *)(v2 + 244596) = -8;
  *(_DWORD *)(v2 + 244600) = -8;
  *(_DWORD *)(v2 + 244604) = 14;
  (((UIListBox *)(v2 + 243436)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 243436)))->UIListBox::SetColumnHead((int)"Name", 150);
  (((UIListBox *)(v2 + 243436)))->UIListBox::SetColumnHead((int)&off_5C91C8, 72);
  (((UIListBox *)(v2 + 243436)))->UIListBox::SetColumnHead((int)"Lv", 38);
  (((UIListBox *)(v2 + 243436)))->UIListBox::SetColumnHead((int)"UseTimes", 72);
  (**(void ( ***)(int, _DWORD))(v2 + 243436))((int)(v2 + 243436), (_DWORD)(0));
  LOBYTE(v27) = g_bDebugMode;
  v28 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 244644) + 28))(
          v2 + 244644,
          &byte_A00221,
          &v80,
          v2,
          0,
          0,
          v27);
  LOBYTE(v28) = g_bDebugMode;
  (((UIListBox *)(v2 + 244644)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v28);
  *(_DWORD *)(v2 + 245804) = -8;
  *(_DWORD *)(v2 + 245808) = -8;
  *(_DWORD *)(v2 + 245812) = 14;
  (((UIListBox *)(v2 + 244644)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 244644)))->UIListBox::SetColumnHead((int)"Name", 150);
  (((UIListBox *)(v2 + 244644)))->UIListBox::SetColumnHead((int)&off_5C91C8, 72);
  (((UIListBox *)(v2 + 244644)))->UIListBox::SetColumnHead((int)"Lv", 38);
  (((UIListBox *)(v2 + 244644)))->UIListBox::SetColumnHead((int)"UseTimes", 72);
  (**(void ( ***)(int, _DWORD))(v2 + 244644))((int)(v2 + 244644), (_DWORD)(0));
  LOBYTE(v29) = g_bDebugMode;
  v30 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 245852) + 28))(
          v2 + 245852,
          &byte_A00222,
          &v80,
          v2,
          0,
          0,
          v29);
  LOBYTE(v30) = g_bDebugMode;
  (((UIListBox *)(v2 + 245852)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v30);
  *(_DWORD *)(v2 + 247012) = -8;
  *(_DWORD *)(v2 + 247016) = -8;
  *(_DWORD *)(v2 + 247020) = 14;
  (((UIListBox *)(v2 + 245852)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 245852)))->UIListBox::SetColumnHead((int)"Name", 150);
  (((UIListBox *)(v2 + 245852)))->UIListBox::SetColumnHead((int)&off_5C91C8, 72);
  (((UIListBox *)(v2 + 245852)))->UIListBox::SetColumnHead((int)"Lv", 38);
  (((UIListBox *)(v2 + 245852)))->UIListBox::SetColumnHead((int)"UseTimes", 72);
  (**(void ( ***)(int, _DWORD))(v2 + 245852))((int)(v2 + 245852), (_DWORD)(0));
  LOBYTE(v31) = g_bDebugMode;
  v32 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 247060) + 28))(
          v2 + 247060,
          &byte_A00223,
          &v80,
          v2,
          0,
          0,
          v31);
  LOBYTE(v32) = g_bDebugMode;
  (((UIListBox *)(v2 + 247060)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v32);
  *(_DWORD *)(v2 + 248220) = -8;
  *(_DWORD *)(v2 + 248224) = -8;
  *(_DWORD *)(v2 + 248228) = 14;
  (((UIListBox *)(v2 + 247060)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 247060)))->UIListBox::SetColumnHead((int)"Name", 150);
  (((UIListBox *)(v2 + 247060)))->UIListBox::SetColumnHead((int)&off_5C91C8, 72);
  (((UIListBox *)(v2 + 247060)))->UIListBox::SetColumnHead((int)"Lv", 38);
  (((UIListBox *)(v2 + 247060)))->UIListBox::SetColumnHead((int)"UseTimes", 72);
  (**(void ( ***)(int, _DWORD))(v2 + 247060))((int)(v2 + 247060), (_DWORD)(0));
  LOBYTE(v33) = g_bDebugMode;
  v34 = (*(int ( **)(int, int *, int *, int, _DWORD, _DWORD, int))(*(_DWORD *)(v2 + 248268) + 28))(
          v2 + 248268,
          &byte_A00224,
          &v80,
          v2,
          0,
          0,
          v33);
  LOBYTE(v34) = g_bDebugMode;
  (((UIListBox *)(v2 + 248268)))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v34);
  *(_DWORD *)(v2 + 249428) = -8;
  *(_DWORD *)(v2 + 249432) = -8;
  *(_DWORD *)(v2 + 249436) = 14;
  (((UIListBox *)(v2 + 248268)))->UIListBox::SetLockSel(30);
  (((UIListBox *)(v2 + 248268)))->UIListBox::SetColumnHead((int)"Com1", 98);
  (((UIListBox *)(v2 + 248268)))->UIListBox::SetColumnHead((int)"Com2", 98);
  (((UIListBox *)(v2 + 248268)))->UIListBox::SetColumnHead((int)"Com3", 98);
  (((UIListBox *)(v2 + 248268)))->UIListBox::SetColumnHead((int)"Percent", 36);
  (**(void ( ***)(int, _DWORD))(v2 + 248268))((int)(v2 + 248268), (_DWORD)(0));
  v93 = v80;
  v94 = v81;
  v95 = v80 + 333;
  v96 = v81 + 29;
  v35 = (UIPushButton *)(v2 + 210472);
  v36 = 9;
  do
  {
    (*(void ( **)(UIPushButton *, int *, int *, int))(*(_DWORD *)((UIWnd *)v35) + 16))(
      v35,
      &byte_A00001,
      &v93,
      v2);
    LOBYTE(v37) = g_bDebugMode;
    (((UIPushButton *)v35))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Skill_Grid.tga", v37);
    v35 = (UIPushButton *)((char *)v35 + 152);
    v94 = v96;
    v38 = v96 + 29;
    --v36;
    v96 += 29;
  }
  while ( v36 );
  LOBYTE(v38) = g_bDebugMode;
  v39 = *(_DWORD *)(v2 + 237060);
  v65[1] = 124;
  v65[0] = 229;
  v66 = 271;
  v67 = 174;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v39 + 28))(
    v2 + 237060,
    &byte_A00225,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Skill",
    1,
    v38);
  (((PalScript *)(v2 + 237060)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Skill2.tga", g_bDebugMode);
  sub_445E50(v2 + 237060);
  v40 = *(_DWORD *)(v2 + 237404);
  v65[0] = v66 + 1;
  v66 += 43;
  v41 = v66;
  LOBYTE(v41) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v40 + 28))(
    v2 + 237404,
    &byte_A00226,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Shui",
    1,
    v41);
  (((PalScript *)(v2 + 237404)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Shui2.tga", g_bDebugMode);
  v42 = *(_DWORD *)(v2 + 237748);
  v65[0] = v66 + 1;
  v66 += 43;
  v43 = v66;
  LOBYTE(v43) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v42 + 28))(
    v2 + 237748,
    &byte_A00227,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Huo",
    1,
    v43);
  (((PalScript *)(v2 + 237748)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Huo2.tga", g_bDebugMode);
  v65[0] = v66 + 1;
  v66 += 43;
  v44 = v66;
  LOBYTE(v44) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(*(_DWORD *)(v2 + 238092) + 28))(
    v2 + 238092,
    &byte_A00228,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Lei",
    1,
    v44);
  (((PalScript *)(v2 + 238092)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Lei2.tga", g_bDebugMode);
  v45 = *(_DWORD *)(v2 + 238436);
  v65[0] = v66 + 1;
  v66 += 43;
  v46 = v66;
  LOBYTE(v46) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v45 + 28))(
    v2 + 238436,
    &byte_A00229,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Feng",
    1,
    v46);
  (((PalScript *)(v2 + 238436)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Feng2.tga", g_bDebugMode);
  v47 = *(_DWORD *)(v2 + 238780);
  v65[0] = v66 + 1;
  v66 += 43;
  v48 = v66;
  LOBYTE(v48) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v47 + 28))(
    v2 + 238780,
    &byte_A00230,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Tu",
    1,
    v48);
  (((PalScript *)(v2 + 238780)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Tu2.tga", g_bDebugMode);
  v49 = *(_DWORD *)(v2 + 239124);
  v65[0] = v66 + 1;
  v66 += 43;
  v50 = v66;
  LOBYTE(v50) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v49 + 28))(
    v2 + 239124,
    &byte_A00231,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Suang",
    1,
    v50);
  (((PalScript *)(v2 + 239124)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Suang2.tga", g_bDebugMode);
  v65[0] = v66;
  v66 += 42;
  v51 = v66;
  LOBYTE(v51) = g_bDebugMode;
  (*(void ( **)(int, __int16 *, _DWORD *, int, char *, int, int))(*(_DWORD *)(v2 + 239468) + 28))(
    v2 + 239468,
    &word_A00232,
    (_DWORD *)(v65),
    v2,
    "UI\\GameMainUI\\Magic\\Combo",
    1,
    v51);
  (((PalScript *)(v2 + 239468)))->PalScript::OpenScript("UI\\GameMainUI\\Magic\\Combo2.tga", g_bDebugMode);
  v73 = 0;
  pnVal = 0;
  v74 = 0;
  v75 = 32;
  nVal2[1] = 0;
  nVal2[0] = 12;
  nVal2[2] = 590;
  nVal2[3] = 126;
  for ( i = 0; i < 5; ++i )
  {
    (((UITitle_XJTM *)v2))->UITitle_XJTM::UpdateMonsterEntry(i, &pnVal);
    (((ArcSceneMonster *)v2))->ArcSceneMonster::CreateInfoPanel(i, (int)nVal2, v62, v63, v64);
  }
  v53 = *(_DWORD *)(v2 + 211840);
  v69 = 125;
  v68 = 10;
  v70 = 200;
  v71 = 539;
  (*(void ( **)(int, int *, int *, int))(v53 + 16))(v2 + 211840, &byte_A00215, &v68, v2);
  LOBYTE(v54) = g_bDebugMode;
  (((UIPushButton *)(v2 + 211840)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\Info.tga", v54);
  v55 = *(_DWORD *)(v2 + 212296);
  v69 = 128;
  v68 = 18;
  v70 = 194;
  v71 = 370;
  (*(void ( **)(int, int *, int *, int))(v55 + 16))(v2 + 212296, &byte_A00215, &v68, v2);
  LOBYTE(v56) = g_bDebugMode;
  (((UIPushButton *)(v2 + 212296)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Magic\\xs.tga", v56);
  v57 = *(_DWORD *)(v2 + 211992);
  v69 = 386;
  v68 = 22;
  v70 = 194;
  v71 = 492;
  (*(void ( **)(int, int *, int *, int))(v57 + 16))(v2 + 211992, &byte_A00215, &v68, v2);
  (((UIScene *)(v2 + 211992)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 211992));
  v58 = *(_DWORD *)(v2 + 212144);
  v69 = 510;
  v68 = 22;
  v70 = 178;
  v71 = 542;
  (*(void ( **)(int, int *, int *, int))(v58 + 16))(v2 + 212144, &byte_A00215, &v68, v2);
  (((UIScene *)(v2 + 212144)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 212144));
  v59 = *(_DWORD *)(v2 + 212448);
  v69 = 130;
  v68 = 56;
  v70 = 156;
  v71 = 162;
  (*(void ( **)(int, int *, int *, int))(v59 + 16))(v2 + 212448, &byte_A00215, &v68, v2);
  (((UIScene *)(v2 + 212448)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 212448));
  (((CCBFiveNimbusWindow *)(v2 + 249476)))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&dword_A00234, v2);
  if ( !strcmp("D16", unk_C10D38) )
    sprintf((char *const)(v2 + 104), "%s", "NONE");
  else
    sprintf((char *const)(v2 + 104), "Item\\%s\\%s.pol", "D16", "D16");
  (((PalScript *)(v2 + 249548)))->PalScript::LoadModel((const char *)(v2 + 104), 0);
  *(_DWORD *)(v2 + 249552) = 0;
  *(_DWORD *)(v2 + 249544) = 1;
  (((CCBFiveNimbusWindow *)(v2 + 249476)))->CCBFiveNimbusWindow::SetFloatParam(160.0);
  (((Camera *)(v2 + 249476)))->Camera::UpdateCameraLookAt(110, 268, 600);
  sub_43A090(v2 + 249476, 1, 0.0);
  CameraCtrl_ResetToDefaults(v62);
  v73 = 200;
  pnVal = 300;
  v74 = 556;
  v75 = 356;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 205788));
  (((UIItem *)(v2 + 205788)))->UIItem::SetData(31);
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 208524));
  (((UIItem *)(v2 + 208524)))->UIItem::SetData(31);
  v74 = pnVal + 218;
  v75 = v73 + 96;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 207156));
  result = (int)(((UIItem *)(v2 + 207156)))->UIItem::SetData(31);
  *(_DWORD *)(v2 + 307020) = 206;
  *(_DWORD *)(v2 + 307016) = 88;
  *(_DWORD *)(v2 + 307024) = 168;
  *(_DWORD *)(v2 + 307028) = 286;
  *(_DWORD *)(v2 + 51032) = nVal;
  *(_BYTE *)(v2 + 889) = 1;
  return result;
}

// 0x0048E600
int CCBCamControl_ProcessRenderQueue(int nVal)
{
  _DWORD *v1; // ecx
  int v2; // esi
  int v3; // edi
  int v4; // eax
  RenderTarget *v5; // esi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int result; // eax
  int nVal1; // [esp+0x0] [ebp-0x24]
  int nVal1a; // [esp+0x0] [ebp-0x24]
  int nVal2; // [esp+0x4] [ebp-0x20]
  int nVal2a; // [esp+0x4] [ebp-0x20]
  int v15; // [esp+0x18] [ebp-0xC]
  int fXa; // [esp+0x1C] [ebp-0x8]
  float fX; // [esp+0x1C] [ebp-0x8]
  float fY; // [esp+0x20] [ebp-0x4]

  v2 = (unsigned long)v1[76754];
  v3 = (unsigned long)(v1[76756] - v2);
  v4 = v2 + v3 / 2;
  v5 = (RenderTarget *)(v1 + 62446);
  fXa = v4;
  v6 = (unsigned long)v1[76755];
  v7 = (unsigned long)(v1[76757] - v6);
  v15 = 98;
  fY = (float)v6;
  fX = (float)fXa;
  do
  {
    (((RenderTarget *)v5))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v5))->RenderTarget::SetSize(32);
    nVal2 = rand() % 10 + 252;
    nVal1 = rand() % 10 + 36;
    v8 = rand();
    (((RenderTarget *)v5))->RenderTarget::SetColor(v8 % 10 - 37, nVal1, nVal2);
    v9 = rand();
    (((RenderTarget *)v5))->RenderTarget::SetAlpha(v9 % 135 + 120);
    (((RenderTarget *)v5))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v5))->RenderTarget::SetState(1058642330);
    (((RenderTarget *)v5))->RenderTarget::UpdateTransform(fX, fY);
    (((RenderTarget *)v5))->RenderTarget::CalcRenderDimensions(v3, v7);
    (((RenderTarget *)v5))->RenderTarget::SetOffset(10.0, 2.0);
    *(float *)&nVal2a = (float)(rand() % 8 + 2);
    *(float *)&nVal1a = (float)(rand() % 8 + 2);
    (((RenderTarget *)v5))->RenderTarget::SetScale(nVal1a, nVal2a);
    (((RenderTarget *)v5))->RenderTarget::SetVisible(1);
    v5 = (RenderTarget *)((char *)v5 + 584);
    result = --v15;
  }
  while ( v15 );
  return result;
}

// 0x0048E950
int CEffect_UpdateState(int nVal)
{
  int v1; // ecx
  int result; // eax
  _DWORD *v4; // edi
  int v5; // ebx
  int v6; // ebp
  int v7; // eax
  int v8; // ebx
  int v9; // esi
  int v10; // edi
  int v11; // eax
  void *v12; // edi
  const void *v13; // esi
  bool v14; // zf
  float fVal1; // [esp+0x0] [ebp-0x28]
  int fVal1a; // [esp+0x0] [ebp-0x28]
  float fVal2; // [esp+0x4] [ebp-0x24]
  int fVal2a; // [esp+0x4] [ebp-0x24]
  float fX; // [esp+0x18] [ebp-0x10]
  float fY; // [esp+0x1C] [ebp-0xC]
  int nVal2; // [esp+0x20] [ebp-0x8]
  int nVala; // [esp+0x2C] [ebp+0x4]

  LOBYTE(result) = *(_BYTE *)(nVal + v1 + 877);
  if ( (_BYTE)result )
  {
    v4 = (_DWORD *)(16 * nVal + v1);
    v5 = *(_DWORD *)(16 * (nVal + 22110) + v1);
    v6 = (unsigned long)(v4[88442] - v5);
    v7 = (unsigned long)v4[88441];
    nVal2 = (unsigned long)(v4[88443] - v7);
    nVala = 8;
    fY = (float)v7;
    fX = (float)(v5 + v6 / 2);
    v8 = 4672 * nVal + v1 + 330400;
    do
    {
      (((RenderTarget *)v8))->RenderTarget::LoadTexture(szFilename);
      (((RenderTarget *)v8))->RenderTarget::SetSize(32);
      v9 = rand() % 10 + 219;
      v10 = rand() % 10 + 36;
      v11 = rand();
      (((RenderTarget *)v8))->RenderTarget::SetColor(v9, v10, v11 % 10 - 4);
      (((RenderTarget *)v8))->RenderTarget::SetAlpha(0xFFu);
      (((RenderTarget *)v8))->RenderTarget::SetField084(0x40000000);
      (((RenderTarget *)v8))->RenderTarget::SetState(1056964608);
      (((RenderTarget *)v8))->RenderTarget::UpdateTransform(fX, fY);
      (((RenderTarget *)v8))->RenderTarget::CalcRenderDimensions(v6, nVal2);
      fVal2 = (float)(rand() % 2 + 1);
      fVal1 = (float)(rand() % 2 + 1);
      (((RenderTarget *)v8))->RenderTarget::SetOffset(fVal1, fVal2);
      *(float *)&fVal2a = (float)(rand() % 2 + 2);
      *(float *)&fVal1a = (float)(rand() % 2 + 2);
      (((RenderTarget *)v8))->RenderTarget::SetScale(fVal1a, fVal2a);
      *(_DWORD *)(v8 + 76) = 3;
      (((RenderTarget *)v8))->RenderTarget::SetVisible(1);
      v12 = (void *)(v8 - 23360);
      v13 = (const void *)v8;
      v8 += 584;
      result = nVala - 1;
      v14 = nVala == 1;
      qmemcpy(v12, v13, 0x248u);
      --nVala;
    }
    while ( !v14 );
  }
  return result;
}

// 0x0048EE60
int CameraCtrl_ProcessSaveSlotNav(int nVal)
{
  int v1; // ecx
  int *v2; // esi
  int result; // eax
  int PrevValidSlot; // eax
  int v5; // edx
  int NextValidSlot; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax

  v2 = (int *)v1;
  LOBYTE(result) = *(_BYTE *)(v1 + 207129);
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = *(_BYTE *)(v1 + 208497);
    if ( !(_BYTE)result )
    {
      LOBYTE(result) = *(_BYTE *)(v1 + 209865);
      if ( !(_BYTE)result )
      {
        result = 1;
        if ( g_Input.KeyInfo[10].PressTime == 1 )
        {
          PrevValidSlot = (((CameraCtrl *)v1))->CameraCtrl::FindPrevValidSlot((int *)(v1 + 205784));
          v5 = (unsigned long)*v2;
          v2[51446] = PrevValidSlot;
          return (*(int ( **)(int *, int, int, _DWORD))(v5 + 24))(
                   v2,
                   1001,
                   g_MonsterEntryTable[PrevValidSlot],
                   0);
        }
        if ( g_Input.KeyInfo[9].PressTime == 1 )
        {
          NextValidSlot = (((CameraCtrl *)v1))->CameraCtrl::FindNextValidSlot((int *)(v1 + 205784));
          v7 = (unsigned long)*v2;
          v2[51446] = NextValidSlot;
          return (*(int ( **)(int *, int, int, _DWORD))(v7 + 24))(
                   v2,
                   1001,
                   g_MonsterEntryTable[NextValidSlot],
                   0);
        }
        if ( g_Input.KeyInfo[2].PressTime == 1 )
        {
          v8 = *(_DWORD *)(v1 + 900) - 1;
          *(_DWORD *)(v1 + 900) = v8;
          if ( v8 < 0 )
            *(_DWORD *)(v1 + 900) = 0;
          return (*(int ( **)(int, int, const char *, _DWORD))(*(_DWORD *)v1 + 24))(
                   v1,
                   1001,
                   (&off_56C548)[*(_DWORD *)(v1 + 900)],
                   0);
        }
        if ( g_Input.KeyInfo[3].PressTime == 1 )
        {
          v9 = *(_DWORD *)(v1 + 900) + 1;
          *(_DWORD *)(v1 + 900) = v9;
          if ( v9 > 7 )
            *(_DWORD *)(v1 + 900) = 7;
          return (*(int ( **)(int, int, const char *, _DWORD))(*(_DWORD *)v1 + 24))(
                   v1,
                   1001,
                   (&off_56C548)[*(_DWORD *)(v1 + 900)],
                   0);
        }
        if ( g_Input.KeyInfo[8].PressTime == 1 )
          return (*(int ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v1 + 24))(v1, 1010, 0, 0);
      }
    }
  }
  return result;
}

// 0x004909F0
int MainPropUI__MainPropUI(int nVal)
{
  UIListBox *v1; // ecx
  int v2; // esi
  _DWORD *v3; // eax
  int v4; // ebp
  _DWORD *v6; // [esp+0x10] [ebp-0x18]
  int v7; // [esp+0x14] [ebp-0x14]

  v2 = (int)v1;
  v1->UIListBox::UIListBox();
  *(_DWORD *)(v2 + 88) = 800;
  *(_DWORD *)(v2 + 92) = 600;
  *(_BYTE *)(v2 + 360) = 0;
  *(_BYTE *)(v2 + 367) = 0;
  *(_DWORD *)(v2 + 368) = 0;
  *(_DWORD *)(v2 + 372) = 0;
  *(_DWORD *)(v2 + 376) = 7;
  *(_DWORD *)(v2 + 380) = 0;
  (((UIFrameContainer *)(v2 + 384)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 536)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 688)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 840)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 992)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 1144)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)(v2 + 4392)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 4560)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 4712)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 204424)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 204576)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 204728)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 204880)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 205032)))->UIFrameContainer::ResetContainerState();
  v3 = (_DWORD *)(v2 + 205200);
  v6 = (_DWORD *)(v2 + 205200);
  v7 = 5;
  v4 = v2 + 205206;
  while ( 1 )
  {
    *v3 = 0;
    *(_WORD *)(v4 - 2) = 0;
    lstrcpyA((LPSTR)v4, unk_C10D38);
    lstrcpyA((LPSTR)(v4 + 512), unk_C10D38);
    lstrcpyA((LPSTR)(v4 + 542), unk_C10D38);
    lstrcpyA((LPSTR)(v4 + 594), unk_C10D38);
    memset((void *)(v4 + 630), 0, 0x30u);
    *(_DWORD *)(v4 + 774) = 0;
    v4 += 852;
    v6 += 213;
    if ( !--v7 )
      break;
    v3 = (_DWORD *)v6;
  }
  ((UIRoleDialog *)(v2 + 209460))->UIRoleDialog::UIRoleDialog();
  (((UIFrameContainer *)(v2 + 212548)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 212700)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 212852)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 213004)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 213156)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 213308)))->UIFrameContainer::ResetContainerState();
  *(_DWORD *)(v2 + 215196) = -1;
  ((UI3DCtrl *)(v2 + 215200))->UI3DCtrl::UI3DCtrl();
  (((UIFrameContainer *)(v2 + 215284)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 217260)))->UIFrameContainer::ResetContainerState();
  (((UIListBox *)(v2 + 217412)))->UIListBox::UpdateKeyCtrl();
  *(_DWORD *)(v2 + 218620) = -1;
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  *(_DWORD *)(v2 + 219672) = -1;
  (((UIProgressBar *)(v2 + 219676)))->UIProgressBar::ctor();
  *(_BYTE *)(v2 + 365) = 0;
  *(_BYTE *)(v2 + 364) = 0;
  *(_BYTE *)(v2 + 362) = 0;
  *(_BYTE *)(v2 + 361) = 0;
  *(_BYTE *)(v2 + 363) = 0;
  *(_DWORD *)(v2 + 154496) = 0;
  *(_DWORD *)(v2 + 154500) = 0;
  *(_DWORD *)(v2 + 154504) = 0;
  return v2;
}

// 0x00492BB0
int MainPropUI_ShowSubPanels(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  void (***v3)(_DWORD, _DWORD); // esi
  int v4; // ebp
  void (***v5)(_DWORD, _DWORD); // esi
  int v6; // ebp
  int v7; // esi
  int result; // eax
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // [esp+0x38] [ebp+0x8]

  v2 = v1;
  if ( nVal <= 5 )
  {
    v3 = (void ( ***)(_DWORD, _DWORD))(v1 + 162424);
    v4 = 5;
    do
    {
      (**(v3 - 38))(v3 - 38, 0);
      (**v3)((_DWORD)(v3), (_DWORD)(0));
      (*v3[172])(v3 + 172, 0);
      (*v3[86])(v3 + 86, 0);
      (*v3[258])(v3 + 258, 0);
      (*v3[344])(v3 + 344, 0);
      (*v3[430])(v3 + 430, 0);
      v3 += 2495;
      --v4;
    }
    while ( v4 );
    v5 = (void ( ***)(_DWORD, _DWORD))(v2 + 9980 * nVal);
    (*v5[40568])(v5 + 40568, 1);
    (*v5[40606])(v5 + 40606, 1);
    (*v5[40778])(v5 + 40778, 1);
    (*v5[40692])(v5 + 40692, 1);
    (*v5[40864])(v5 + 40864, 1);
    (*v5[40950])(v5 + 40950, 1);
    (*v5[41036])(v5 + 41036, 1);
    v6 = 5;
    v7 = v2 + 210828;
    do
    {
      sub_445E50(v7);
      v7 += 344;
      --v6;
    }
    while ( v6 );
    result = v15;
    switch ( v15 )
    {
      case 0:
        v9 = sub_445E50(v2 + 210828);
        LOBYTE(v9) = g_bDebugMode;
        (((UIPushButton *)(v2 + 205032)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\wq_word.tga", v9);
        break;
      case 1:
        sub_445E50(v2 + 211172);
        LOBYTE(v10) = g_bDebugMode;
        (((UIPushButton *)(v2 + 205032)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Equip_word.tga", v10);
        break;
      case 2:
        sub_445E50(v2 + 211516);
        LOBYTE(v11) = g_bDebugMode;
        (((UIPushButton *)(v2 + 205032)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\tb_word.tga", v11);
        break;
      case 3:
        v12 = sub_445E50(v2 + 211860);
        LOBYTE(v12) = g_bDebugMode;
        (((UIPushButton *)(v2 + 205032)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\jb_word.tga", v12);
        break;
      case 4:
        sub_445E50(v2 + 212204);
        LOBYTE(v13) = g_bDebugMode;
        (((UIPushButton *)(v2 + 205032)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Adorn_word.tga", v13);
        break;
      case 5:
        sub_445E50(v2 + 212204);
        LOBYTE(v14) = g_bDebugMode;
        (((UIPushButton *)(v2 + 205032)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Adorn_word.tga", v14);
        break;
      default:
        return result;
    }
  }
  return result;
}

// 0x004932D0
int UIScene_LoadRoleSkillData(int nVal)
{
  int v1; // ecx
  StateUI *v2; // ebx
  char *v3; // edi
  int *v4; // ecx
  int *v5; // edx
  int *v6; // eax
  int result; // eax
  _BYTE pOut[12]; // [esp+0x18] [ebp-0xC] BYREF

  v2 = (StateUI *)v1;
  v3 = 0;
  if ( (((UIListBox *)(v1 + 217412)))->UIListBox::CreateChild() >= 0 )
  {
    v6 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v2->m_Frame.m_align);
LABEL_12:
    v3 = (char *)v6[2];
  }
  else
  {
    switch ( LODWORD(v2->m_Frame.m_ratiow) )
    {
      case 0:
        v4 = (int *)(&g_RoleSlotBuf.m_partyActor.m_obbox + 352 * nVal);
        goto LABEL_4;
      case 1:
        v5 = (int *)(&g_RoleSlotBuf.m_partyActor.m_nAnimFrames + 352 * nVal);
        goto LABEL_6;
      case 2:
        v6 = (int *)(&g_RoleSlotBuf.m_partyActor.m_nModelParamB + 352 * nVal);
        goto LABEL_12;
      case 3:
        v4 = (int *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * nVal + 1];
LABEL_4:
        v3 = (char *)v4[2];
        break;
      case 4:
        v5 = (int *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nVal + 1];
LABEL_6:
        v3 = (char *)v5[2];
        break;
      case 5:
        v6 = (int *)&g_RoleSlotBuf.m_partyActor.m_pEquipAtt2[352 * nVal + 4];
        goto LABEL_12;
      default:
        break;
    }
  }
  (((RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * nVal)))->RoleSystem::RecalcAggregatedStats(0);
  (((StateUI *)v2))->StateUI::UpdateAttributeDisplay(nVal, v3, v2->m_Frame.m_ratiow);
  return result;
}

// 0x00493E40
int SceneMgr_FormatStatusCaption(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  _DWORD *v3; // edi
  int v4; // esi
  int v5; // edi
  int result; // eax
  char Buffer[600]; // [esp+0xC] [ebp-0x258] BYREF

  v2 = v1;
  memset(Buffer, 0, sizeof(Buffer));
  v3 = (_DWORD *)(v1 + 852 * nVal);
  sprintf(Buffer, "%s %d", (const char *)&g_szRoleName1, v3[51463]);
  sprintf(&Buffer[30], "%s %d", (const char *)&g_szRoleName0, v3[51462]);
  sprintf(&Buffer[60], "%s %d", (const char *)&g_szRoleName2, v3[51464]);
  sprintf(&Buffer[90], "%s %d", (const char *)&g_szRoleName3, v3[51465]);
  sprintf(
    &Buffer[120],
    "%s %d",
    (const char *)&g_szSceneName,
    *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_vecLocalPos.z + 352 * nVal));
  sprintf(&Buffer[150], "%s %d", (const char *)g_bSlotFlag, v3[51466]);
  sprintf(&Buffer[180], "%s %d", (const char *)&g_bSlotFlag[256], v3[51467]);
  sprintf(&Buffer[210], "%s %d", byte_DC3F3C, v3[51469]);
  sprintf(&Buffer[240], "%s %d", (const char *)&g_bSlotFlag[512], v3[51468]);
  sprintf(&Buffer[270], "%s %d", byte_DC403C, v3[51470]);
  v4 = 0;
  v5 = v2 + 9980 * nVal + 159232;
  do
  {
    SetEnable((UICaption *)(v5 - 1520));
    SetEnable((UICaption *)v5);
    SetEnable((UICaption *)(v5 + 1520));
    v4 += 30;
    v5 += 152;
  }
  while ( v4 < 300 );
  SetEnable((UICaption *)(v2 + 204880));
  SetEnable((UICaption *)(v2 + 204728));
  return result;
}

// 0x00494660
int MagicUI_ProcessInput(int nVal)
{
  CScreenMode *v1; // ecx
  CScreenMode *v2; // esi
  int v3; // edi
  int v4; // ebp
  int result; // eax
  int p_DWORD; // [esp+0xC] [ebp-0x10] BYREF
  int v7; // [esp+0x10] [ebp-0xC]
  int v8; // [esp+0x14] [ebp-0x8]
  int v9; // [esp+0x18] [ebp-0x4]

  v2 = (CScreenMode *)v1;
  (((CScreenMode *)v1))->CScreenMode::ResetProgressList();
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 661, byte_DD9E3C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 664, byte_DD9F3C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 667, byte_DDA03C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 670, byte_DDA13C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 673, byte_DDA23C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 676, byte_DDA33C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 679, byte_DDA43C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 682, byte_DDA53C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 685, byte_DDA63C);
  lstrcpyA((LPSTR)&g_ArcSceneObjBuffer + 688, byte_DDA73C);
  v7 = 62;
  p_DWORD = 686;
  v8 = 796;
  v9 = 157;
  v3 = 0;
  v4 = 60;
  do
  {
    if ( *((_BYTE *)&v2->m_FrameB.m_ratioh + v3 + 1) )
    {
      (((CScreenMode *)v2))->CScreenMode::GetPlayerAttByIndex(v3);
      (((UIBigMap *)v2))->UIBigMap::ProcessChildItem(v3, &p_DWORD);
      (((UIBigMap *)v2))->UIBigMap::SetEntryVisible(v3, 1u);
      v4 += 122;
      v7 = v4;
      v9 = v4 + 95;
    }
    else
    {
      (((UIBigMap *)v2))->UIBigMap::SetEntryVisible(v3, 0);
    }
    ++v3;
  }
  while ( v3 < 5 );
  (((StateUI *)v2))->StateUI::UpdateScrollBars();
  v2->m_FrameB.m_texty = 0;
  result = 0;
  while ( !*((_BYTE *)&v2->m_FrameB.m_ratioh + result + 1) )
  {
    if ( ++result >= 5 )
      return result;
  }
  v2[39].m_Static_816.m_childs.m_pData = (char *)result;
  v2->m_FrameB.m_fonttype = 0;
  v2->m_FrameB.m_texty = (void *)-1;
  (((StateUI *)v2))->StateUI::UpdateRoleTooltip(result);
  MainPropUI_ShowSubPanels((int)v2[39].m_Static_816.m_childs.m_pData);
  (((MainEquipUI *)v2))->MainEquipUI::UpdateTooltip((int)v2[39].m_Static_816.m_childs.m_pData);
  (((EquipUI *)v2))->EquipUI::HandleInput((int)v2[39].m_Static_816.m_childs.m_pData, 0);
  return result;
}

// 0x00496190
void CreateSceneEntities(Actor *_this, int nSceneId)
{
  int m_nRoleState0; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  float m_fAnimDelta; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  RoleAtt *v12; // edx
  int v13; // esi
  const char *v14; // ebp
  char *v15; // esi
  int v16; // eax
  void *v17; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // eax
  float m_fMatrixE; // edx
  int v35; // edx
  int v36; // ecx
  int v37; // eax
  int v38; // edx
  float z; // eax
  int v40; // edx
  RoleAtt *v41; // eax
  int v42; // edx
  char *m_pRoleState; // eax
  int v44; // edx
  int v45; // eax
  int v46; // edx
  int m_nCloneParamB; // edx
  int v48; // ecx
  unsigned int v49; // eax
  int v50; // edx
  float m_fMoveRange; // eax
  int v52; // edx
  int m_nTransitionParam; // edx
  int v54; // ecx
  int m_nHandleEvent; // edx
  int v56; // [esp+0x158] [ebp-E8h]
  int *v57; // [esp+0x15C] [ebp-E4h]
  int v58; // [esp+0x160] [ebp-E0h]
  char (**v59)[3]; // [esp+0x168] [ebp-D8h]
  int v60; // [esp+0x16C] [ebp-D4h] BYREF
  int v61; // [esp+0x170] [ebp-D0h]
  int v62; // [esp+0x174] [ebp-CCh]
  int v63; // [esp+0x178] [ebp-C8h]
  int v64; // [esp+0x17C] [ebp-C4h]
  int v65; // [esp+0x180] [ebp-C0h] BYREF
  int v66; // [esp+0x184] [ebp-BCh]
  int v67; // [esp+0x188] [ebp-B8h]
  int v68; // [esp+0x18C] [ebp-B4h]
  int v69; // [esp+0x190] [ebp-B0h] BYREF
  int v70; // [esp+0x194] [ebp-ACh]
  int v71; // [esp+0x198] [ebp-A8h]
  int v72; // [esp+0x19C] [ebp-A4h]
  int v73; // [esp+0x1A0] [ebp-A0h] BYREF
  int v74; // [esp+0x1A4] [ebp-0x9C]
  int v75; // [esp+0x1A8] [ebp-0x98]
  int v76; // [esp+0x1AC] [ebp-0x94]
  char *v77; // [esp+0x1B0] [ebp-0x90] BYREF
  int v78; // [esp+0x1B4] [ebp-0x8C]
  char *v79; // [esp+0x1B8] [ebp-0x88]
  int v80; // [esp+0x1BC] [ebp-0x84]
  int v81; // [esp+0x1C0] [ebp-0x80] BYREF
  int v82; // [esp+0x1C4] [ebp-0x7C]
  int v83; // [esp+0x1C8] [ebp-0x78]
  int v84; // [esp+0x1CC] [ebp-0x74]
  int nVal2[4]; // [esp+0x1D0] [ebp-0x70] BYREF
  _DWORD v86[4]; // [esp+0x1E0] [ebp-0x60] BYREF
  _DWORD v87[4]; // [esp+0x1F0] [ebp-0x50] BYREF
  int v88; // [esp+0x200] [ebp-0x40] BYREF
  int m_nCachedA; // [esp+0x204] [ebp-0x3C]
  int v90; // [esp+0x208] [ebp-0x38]
  int v91; // [esp+0x20C] [ebp-0x34]
  _DWORD v92[4]; // [esp+0x210] [ebp-0x30] BYREF
  int v93[8]; // [esp+0x220] [ebp-0x20] BYREF

  m_nRoleState0 = _this->m_nRoleState0;
  v4 = *(_DWORD *)&_this->m_bUIFlagA;
  _this->m_nCachedA = 0;
  *(_DWORD *)&_this->m_nCachedB = m_nRoleState0;
  _this->m_pRoleParam3 = 0;
  _this->m_nTransform = v4;
  (((UIListBox *)_this))->UIListBox::SetSelTexture(-1, (int)_this->m_pRoleParam3, _this->m_nCachedA, *(_DWORD *)&_this->m_nCachedB, _this->m_nTransform);
  v5 = _this->m_nCachedA + 18;
  v77 = _this->m_pRoleParam3 + 592;
  v78 = v5;
  v79 = (char *)(v77 + 192);
  v80 = v5 + 526;
  (*(void ( **)(float *, int, char **, Actor *))(LODWORD(_this->m_vecRot.z) + 16))(
    &_this->m_vecRot.z,
    161,
    &v77,
    _this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&_this->m_vecRot.z))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\Frame.tga", v6);
  m_fAnimDelta = _this->m_fAnimDelta;
  v78 += 26;
  v77 = (char *)v79;
  v80 = v78 + 526;
  v79 += 17;
  (*(void ( **)(float *, int, char **, Actor *))(LODWORD(m_fAnimDelta) + 16))(
    &_this->m_fAnimDelta,
    161,
    &v77,
    _this);
  LOBYTE(v8) = g_bDebugMode;
  (((UIPushButton *)&_this->m_fAnimDelta))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Frame_Line.tga", v8);
  v74 = 0;
  v73 = (int)(v79 - 205);
  v75 = (int)(v79 - 2);
  v9 = *((_DWORD *)&_this->m_bDirFlag + 1);
  v76 = 64;
  (*(void ( **)(_BYTE *, int, int *, Actor *))(v9 + 16))(&_this->m_bDirFlag + 4, 161, &v73, _this);
  LOBYTE(v10) = g_bDebugMode;
  (((UIPushButton *)(&_this->m_bDirFlag + 4)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\TimeMoney.tga", v10);
  v11 = *(_DWORD *)&_this[5].m_curact[27];
  v74 = -4;
  v73 = 618;
  v75 = 738;
  v76 = 28;
  (*(void ( **)(char *, int, int *, Actor *))(v11 + 16))(&_this[5].m_curact[27], 161, &v73, _this);
  (((UIScene *)&_this[5].m_curact[27]))->UIScene::SetShow(0);
  AllocObject(&_this[5].m_curact[27]);
  v12 = _this[5].m_pEquipAtt2[0];
  v74 = 16;
  v73 = 668;
  v75 = 748;
  v76 = 48;
  (*(void ( **)(RoleAtt **, int, int *, Actor *))((char *)&v12->Remark.skillCount + 10))(
    _this[5].m_pEquipAtt2,
    161,
    &v73,
    _this);
  (((UIScene *)_this[5].m_pEquipAtt2))->UIScene::SetShow(0);
  AllocObject(_this[5].m_pEquipAtt2);
  (((LineupUI *)_this))->LineupUI::RebuildExitPage();
  memset(nVal2, 0, 12);
  nVal2[3] = 32;
  v93[1] = 0;
  v93[0] = 12;
  v93[2] = 590;
  v93[3] = 126;
  v13 = 0;
  v59 = &off_56D5C4;
  v14 = (const char *)"UI\\GameMainUI\\Equip\\SelRole0";
  v64 = (int)(&_this[260].m_pActor + 1);
  do
  {
    (((UIBigMap *)_this))->UIBigMap::GetChildCount(v13, (int)nVal2);
    (((ArcSceneMonster *)_this))->ArcSceneMonster::CreateMonsterUI(v13, (int)v93, v56, v57, v58);
    (*(void ( **)(int, char *, int *, Actor *, const char *, int, _DWORD))(*(_DWORD *)v64 + 28))(
      v64,
      (char *)*v59,
      (int *)(nVal2),
      _this,
      v14,
      1,
      0);
    v14 += 256;
    ++v13;
    ++v59;
    v64 += 344;
  }
  while ( (int)v14 < (int)off_56D5A0 );
  v15 = (char *)(&_this[198].m_pParticleData + 1);
  v64 = 5;
  do
  {
    m_nCachedA = _this->m_nCachedA;
    v91 = m_nCachedA + 64;
    v16 = *((_DWORD *)v15 - 151);
    v88 = 316;
    v90 = 348;
    (*(void ( **)(char *, char *, int *, Actor *))(v16 + 16))(v15 - 604, &byte_A00330, &v88, _this);
    (((UIScene *)(v15 - 604)))->UIScene::SetShow(0);
    v17 = AllocObject(v15 - 604);
    LOBYTE(v17) = g_bDebugMode;
    v18 = *((_DWORD *)v15 - 113);
    v86[1] = 4;
    v86[0] = 368;
    v86[2] = 400;
    v86[3] = 112;
    (*(void ( **)(char *, char *, _DWORD *, Actor *, char *, int, void *))(v18 + 28))(
      v15 - 452,
      byte_A00319,
      (_DWORD *)(v86),
      _this,
      "UI\\GameMainUI\\Equip\\Weapon_Ctrl",
      1,
      v17);
    (((PalScript *)(v15 - 452)))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Weapon_Ctrl2.tga", g_bDebugMode);
    *(v15 - 112) = 0;
    LOBYTE(v19) = g_bDebugMode;
    v20 = *((_DWORD *)v15 - 27);
    v66 = 2;
    v65 = 426;
    v67 = 574;
    v68 = 34;
    (*(void ( **)(char *, char *, int *, Actor *, char *, int, int))(v20 + 28))(
      v15 - 108,
      &byte_A00320,
      &v65,
      _this,
      "UI\\GameMainUI\\Equip\\Equip_Ctrl",
      1,
      v19);
    (((PalScript *)(v15 - 108)))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Equip_Ctrl2.tga", g_bDebugMode);
    v21 = v68;
    *((_DWORD *)v15 - 1) = 0;
    *(_DWORD *)v15 = 5;
    v15[232] = 0;
    v66 = v21 - 12;
    v22 = v21 - 12 + 32;
    v23 = *((_DWORD *)v15 + 59);
    v68 = v22;
    LOBYTE(v22) = g_bDebugMode;
    (*(void ( **)(char *, char *, int *, Actor *, char *, int, int))(v23 + 28))(
      v15 + 236,
      &byte_A00321,
      &v65,
      _this,
      "UI\\GameMainUI\\Equip\\Equip_Ctrl",
      1,
      v22);
    (((PalScript *)(v15 + 236)))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Equip_Ctrl2.tga", g_bDebugMode);
    *((_DWORD *)v15 + 85) = 0;
    *((_DWORD *)v15 + 86) = 5;
    v24 = v68;
    v15[576] = 0;
    v66 = v24 - 12;
    v25 = v24 - 12 + 32;
    v26 = *((_DWORD *)v15 + 145);
    v68 = v25;
    LOBYTE(v25) = g_bDebugMode;
    (*(void ( **)(char *, char *, int *, Actor *, char *, int, int))(v26 + 28))(
      v15 + 580,
      &byte_A00322,
      &v65,
      _this,
      "UI\\GameMainUI\\Equip\\Equip_Ctrl",
      1,
      v25);
    (((PalScript *)(v15 + 580)))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Equip_Ctrl2.tga", g_bDebugMode);
    v27 = v68;
    *((_DWORD *)v15 + 171) = 0;
    *((_DWORD *)v15 + 172) = 5;
    v66 = v27 - 12;
    v28 = v27 - 12 + 32;
    v15[920] = 0;
    v29 = *((_DWORD *)v15 + 231);
    v68 = v28;
    LOBYTE(v28) = g_bDebugMode;
    (*(void ( **)(char *, int *, int *, Actor *, char *, int, int))(v29 + 28))(
      v15 + 924,
      &byte_A00323,
      &v65,
      _this,
      "UI\\GameMainUI\\Equip\\Equip_Ctrl",
      1,
      v28);
    (((PalScript *)(v15 + 924)))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Equip_Ctrl2.tga", g_bDebugMode);
    v30 = v68;
    *((_DWORD *)v15 + 257) = 0;
    *((_DWORD *)v15 + 258) = 5;
    v66 = v30 - 12;
    v31 = v30 - 12 + 32;
    v15[1264] = 0;
    v32 = *((_DWORD *)v15 + 317);
    v68 = v31;
    LOBYTE(v31) = g_bDebugMode;
    (*(void ( **)(char *, int *, int *, Actor *, char *, int, int))(v32 + 28))(
      v15 + 1268,
      &byte_A00324,
      &v65,
      _this,
      "UI\\GameMainUI\\Equip\\Equip_Ctrl",
      1,
      v31);
    (((PalScript *)(v15 + 1268)))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Equip_Ctrl2.tga", g_bDebugMode);
    *((_DWORD *)v15 + 343) = 0;
    *((_DWORD *)v15 + 344) = 5;
    v33 = v64;
    v15[1608] = 0;
    v15 += 9980;
    v64 = v33 - 1;
  }
  while ( v33 != 1 );
  m_fMatrixE = _this[249].m_fMatrixE;
  _this[249].m_nMatrixParam = 16;
  LODWORD(_this[249].m_fMatrixC) = 368;
  LODWORD(_this[249].m_fMatrixParamA) = 400;
  LODWORD(_this[249].m_fMatrixParamB) = 124;
  (*(void ( **)(float *, int, float *, Actor *))(LODWORD(m_fMatrixE) + 16))(
    &_this[249].m_fMatrixE,
    161,
    &_this[249].m_fMatrixC,
    _this);
  (((UIScene *)&_this[249].m_fMatrixE))->UIScene::SetShow(0);
  AllocObject(&_this[249].m_fMatrixE);
  SetEnable((UICaption *)&_this[249].m_fMatrixE);
  v35 = *(_DWORD *)&_this[259].m_curact[39];
  v61 = 40;
  v60 = 336;
  v62 = 356;
  v63 = 72;
  (*(void ( **)(char *, int, int *, Actor *))(v35 + 16))(&_this[259].m_curact[39], 161, &v60, _this);
  LOBYTE(v36) = g_bDebugMode;
  (((UIPushButton *)&_this[259].m_curact[39]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\WeaponIcon.tga", v36);
  v37 = *((_DWORD *)&_this[259].m_vecLocalPos + 3);
  v61 = 8;
  v60 = 438;
  v62 = 456;
  v63 = 28;
  (*(void ( **)(gbVec3D *, int, int *, Actor *))(v37 + 16))(&_this[259].m_vecLocalPos + 1, 161, &v60, _this);
  LOBYTE(v38) = g_bDebugMode;
  (((UIPushButton *)(&_this[259].m_vecLocalPos + 1)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\HatIcon.tga", v38);
  v61 = v63 + 1;
  v63 += 21;
  z = _this[259].m_vecTargetPos.z;
  v62 = v60 + 20;
  (*(void ( **)(float *, int, int *, Actor *))(LODWORD(z) + 16))(&_this[259].m_vecTargetPos.z, 161, &v60, _this);
  LOBYTE(v40) = g_bDebugMode;
  (((UIPushButton *)&_this[259].m_vecTargetPos.z))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ClothIcon.tga", v40);
  v61 = v63 + 1;
  v63 += 19;
  v41 = _this[259].m_pEquipAtt2[3];
  v62 = v60 + 20;
  (*(void ( **)(RoleAtt **, int, int *, Actor *))((char *)&v41->Remark.skillCount + 10))(
    &_this[259].m_pEquipAtt2[3],
    161,
    &v60,
    _this);
  LOBYTE(v42) = g_bDebugMode;
  (((UIPushButton *)&_this[259].m_pEquipAtt2[3]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ShoesIcon.tga", v42);
  v61 = v63 + 1;
  v63 += 22;
  m_pRoleState = _this[259].m_pRoleState;
  v62 = v60 + 22;
  (*((void ( **)(char **, int, int *, Actor *))m_pRoleState + 4))(&_this[259].m_pRoleState, 161, &v60, _this);
  LOBYTE(v44) = g_bDebugMode;
  (((UIPushButton *)&_this[259].m_pRoleState))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\AdornIcon.tga", v44);
  v61 = v63 + 1;
  v63 += 22;
  v45 = *((_DWORD *)&_this[260].m_szText + 2);
  v62 = v60 + 22;
  (*(void ( **)(char *, int, int *, Actor *))(v45 + 16))(&_this[260].m_szText + 8, 161, &v60, _this);
  LOBYTE(v46) = g_bDebugMode;
  (((UIPushButton *)(&_this[260].m_szText + 8)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\AdornIcon.tga", v46);
  m_nCloneParamB = _this[249].m_nCloneParamB;
  v70 = 125;
  v69 = 10;
  v71 = 242;
  v72 = 539;
  (*(void ( **)(int *, char *, int *, Actor *))(m_nCloneParamB + 16))(
    &_this[249].m_nCloneParamB,
    &byte_A00326,
    &v69,
    _this);
  LOBYTE(v48) = g_bDebugMode;
  (((UIPushButton *)&_this[249].m_nCloneParamB))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Info.tga", v48);
  v49 = _this[249].m_dwMatMsg[2];
  v70 = 372;
  v69 = 22;
  v71 = 234;
  v72 = 540;
  (*(void ( **)(unsigned int *, char *, int *, Actor *))(v49 + 16))(
    &_this[249].m_dwMatMsg[2],
    &byte_A00326,
    &v69,
    _this);
  (((UIScene *)&_this[249].m_dwMatMsg[2]))->UIScene::SetShow(0);
  AllocObject(&_this[249].m_dwMatMsg[2]);
  v50 = *((_DWORD *)&_this[249].m_bDirFlag + 4);
  v70 = 504;
  v69 = 22;
  v71 = 234;
  v72 = 536;
  (*(void ( **)(_BYTE *, char *, int *, Actor *))(v50 + 16))(
    &_this[249].m_bDirFlag + 16,
    &byte_A00326,
    &v69,
    _this);
  (((UIScene *)(&_this[249].m_bDirFlag + 16)))->UIScene::SetShow(0);
  AllocObject(&_this[249].m_bDirFlag + 16);
  m_fMoveRange = _this[250].m_fMoveRange;
  v87[1] = 141;
  v87[0] = 195;
  v87[2] = 211;
  v87[3] = 173;
  (*(void ( **)(float *, char *, _DWORD *, Actor *))(LODWORD(m_fMoveRange) + 16))(
    &_this[250].m_fMoveRange,
    &byte_A00326,
    (_DWORD *)(v87),
    _this);
  LOBYTE(v52) = g_bDebugMode;
  (((UIPushButton *)&_this[250].m_fMoveRange))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Attack_word.tga", v52);
  m_nTransitionParam = _this[262].m_nTransitionParam;
  v82 = 125;
  v81 = 251;
  v83 = 587;
  v84 = 518;
  (*(void ( **)(int *, int, int *, Actor *))(m_nTransitionParam + 16))(
    &_this[262].m_nTransitionParam,
    161,
    &v81,
    _this);
  LOBYTE(v54) = g_bDebugMode;
  (((UIPushButton *)&_this[262].m_nTransitionParam))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ListFrame.tga", v54);
  m_nHandleEvent = _this[262].m_nHandleEvent;
  v92[1] = v82;
  v92[0] = v81 + 7;
  v92[3] = v82 + 32;
  v92[2] = v81 + 327;
  (*(void ( **)(int *, char *, _DWORD *, char *, _DWORD, Actor *))(m_nHandleEvent + 28))(
    &_this[262].m_nHandleEvent,
    &byte_A00002,
    (_DWORD *)(v92),
    "UI\\Flex\\Bar.tga",
    0,
    _this);
  (((CScreenMode *)&_this[262].m_nHandleEvent))->CScreenMode::SetPosition(32,   32);
  sub_495CA0(&v81);
  (((CCBFiveNimbusWindow *)(&_this[267].m_nAnimCounter + 3)))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&word_A00336, (int)_this);
  if ( !strcmp("D16", unk_C10D38) )
    sprintf((char *const)&_this->m_szText + 4, "%s", "NONE");
  else
    sprintf((char *const)&_this->m_szText + 4, "Item\\%s\\%s.pol", "D16", "D16");
  (((PalScript *)(&_this[267].m_nUpdateMode + 6)))->PalScript::LoadModel((const char *)&_this->m_szText + 4, 0);
  *(&_this[267].m_nUpdateMode + 7) = 0;
  *(&_this[267].m_nUpdateMode + 5) = 1;
  (((CCBFiveNimbusWindow *)(&_this[267].m_nAnimCounter + 3)))->CCBFiveNimbusWindow::SetFloatParam(160.0);
  (((Camera *)(&_this[267].m_nAnimCounter + 3)))->Camera::UpdateCameraLookAt(126, 258, 600);
  sub_43A090((int)(&_this[267].m_nAnimCounter + 3), 1, 0.0);
  v93[4] = 300;
  v93[7] = 300;
  v93[5] = 200;
  v93[6] = 500;
  Create__ovl_1((ARC_PlayerAtt *)&_this[255].m_nHandleEvent);
  (((UIItem *)&_this[255].m_nHandleEvent))->UIItem::SetData(31);
  HIBYTE(_this->m_vecPos.x) = 1;
  LODWORD(_this->m_vecRot.y) = nSceneId;
}

// 0x00496DD0
int LoadBigMapRenderTarget(int a2)
{
  int v1; // ecx
  int *v3; // ebx
  int v4; // edi
  int v5; // esi
  int v6; // ebp
  int v7; // eax
  int v8; // eax
  void *v9; // edi
  const void *v10; // esi
  bool v11; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  float fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  float fYb; // [esp+0x4] [ebp-0x20]
  int v19; // [esp+0x18] [ebp-0xC]
  int v20; // [esp+0x1C] [ebp-0x8]
  int a2a; // [esp+0x28] [ebp+0x4]

  *(_DWORD *)(v1 + 154496) = 0;
  *(_DWORD *)(v1 + 154500) = 0;
  a2a = 16;
  *(_BYTE *)(a2 + v1 + 154496) = 1;
  v3 = (int *)(16 * (a2 + 9648) + v1);
  v4 = 16 * a2 + v1;
  v5 = *(_DWORD *)(v4 + 154376) - *v3;
  v19 = v4;
  v20 = v5;
  v6 = 9344 * a2 + v1 + 4864;
  while ( 1 )
  {
    (((RenderTarget *)v6))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v6))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 236;
    fX = rand() % 10 + 98;
    v7 = rand();
    (((RenderTarget *)v6))->RenderTarget::SetColor(v7 % 10 + 58, fX, fY);
    v8 = rand();
    (((RenderTarget *)v6))->RenderTarget::SetAlpha(v8 % 55 - 56);
    *(_BYTE *)(v6 + 104) = 1;
    (((RenderTarget *)v6))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v6))->RenderTarget::SetState(1067030938);
    fYa = (float)*(int *)(v4 + 154372);
    fXa = (float)(*v3 + rand() % v5);
    (((RenderTarget *)v6))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v6))->RenderTarget::Render(*v3, v3[1], v3[2]);
    fYb = (float)(rand() % 2 + 1);
    fXb = (float)(rand() % 2 + 1);
    (((RenderTarget *)v6))->RenderTarget::SetOffset(fXb, fYb);
    (((RenderTarget *)v6))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v6))->RenderTarget::SetVisible(1);
    v9 = (void *)(v6 + 74752);
    v10 = (const void *)v6;
    v6 += 584;
    result = a2a - 1;
    v11 = a2a == 1;
    qmemcpy(v9, v10, 0x248u);
    --a2a;
    if ( v11 )
      break;
    v4 = v19;
    v5 = v20;
  }
  return result;
}

// 0x004A13E0
int SyncUIRoleDialogMembers()
{
  int result; // eax

  g_nUILayoutFlags = 0;
  return result;
}

// 0x004A16C0
void Create__ovl_1(ARC_PlayerAtt *_this)
{
  LONG left; // edx
  char *todo_050; // edi
  int todo_054; // edx
  int *p_todo_060; // ebp
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // ebp
  int v13; // ecx
  int v14; // edx
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ebx
  int v22; // kr04_4
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // eax
  char Buffer[253]; // [esp+0x34] [ebp-0x300] BYREF
  __int16 v29; // [esp+0x131] [ebp-0x203]
  char v30; // [esp+0x133] [ebp-0x201]
  char v31[253]; // [esp+0x134] [ebp-0x200] BYREF
  __int16 v32; // [esp+0x231] [ebp-0x103]
  char v33; // [esp+0x233] [ebp-0x101]
  char v34[253]; // [esp+0x234] [ebp-0x100] BYREF
  __int16 v35; // [esp+0x331] [ebp-0x3]
  char v36; // [esp+0x333] [ebp-0x1]
  int id; // [esp+0x338] [ebp+0x4]
  tagRECT *pRect; // [esp+0x33C] [ebp+0x8]
  int parent; // [esp+0x340] [ebp+0xC]
  int v40; // [esp+0x344] [ebp+0x10]
  int v41; // [esp+0x348] [ebp+0x14]

  (((UIWnd *)_this))->UIWnd::Create(id, pRect, parent);
  _this->_todo_048 = parent;
  *(_DWORD *)&_this->byMagicUseTime[2][4] = v40;
  memset(Buffer, 0, sizeof(Buffer));
  memset(v31, 0, sizeof(v31));
  v29 = 0;
  v30 = 0;
  v34[0] = 0;
  v32 = 0;
  v33 = 0;
  _this->_todo_04c = id;
  memset(&v34[1], 0, 0xFCu);
  v35 = 0;
  left = pRect->left;
  v36 = 0;
  todo_050 = _this->_todo_050;
  *(_DWORD *)_this->_todo_050 = left;
  _this->_todo_054 = pRect->top;
  _this->_todo_058 = pRect->right;
  _this->_todo_05c = pRect->bottom;
  sprintf(Buffer, "%s", "UI\\GameMainUI\\MUIDialog\\Normal\\DlgBackground.tga");
  sprintf(v31, "%s", "UI\\GameMainUI\\MUIDialog\\Normal\\Yes");
  sprintf(v34, "%s", "UI\\GameMainUI\\MUIDialog\\Normal\\No");
  todo_054 = _this->_todo_054;
  p_todo_060 = (int *)&_this->_todo_060;
  _this->_todo_064 = todo_054 + 6;
  v6 = *(_DWORD *)_this->_todo_050;
  _this->_todo_060 = v6 + 6;
  v7 = *(_DWORD *)&_this->byMagicUseTime[2][4];
  if ( !v7 )
  {
    _this->_todo_058 = v6 + 308;
    _this->_todo_05c = todo_054 + 109;
    (*(void ( **)(char *, int, char *, ARC_PlayerAtt *))(*(_DWORD *)_this->_todo_130 + 16))(
      _this->_todo_130,
      655360,
      _this->_todo_050,
      _this);
    (((UIPushButton *)_this->_todo_130))->UIPushButton::CreateFromTemplate(Buffer, v41);
    (**(void ( ***)(char *, _DWORD))_this->_todo_130)((char *)(_this->_todo_130), (_DWORD)(0));
    (((UIWnd *)_this->_todo_130))->UIWnd::sub_445FA0(_this->_todo_050);
    v20 = *(_DWORD *)&_this->_todo_224[64];
    v21 = _this->_todo_05c - v20 - 6;
    v22 = *(_DWORD *)&_this->_todo_224[60];
    *(_DWORD *)&_this->_todo_224[72] = v21;
    v23 = *(_DWORD *)todo_050 + 154 - v22 / 2;
    v24 = *(_DWORD *)&_this->_todo_224[60];
    *(_DWORD *)&_this->_todo_224[68] = v23;
    *(_DWORD *)&_this->_todo_224[76] = v24 + v23;
    v25 = *(_DWORD *)&_this->_todo_224[84];
    *(_DWORD *)&_this->_todo_224[80] = v20 + v21;
    (*(void ( **)(char *, int, char *, ARC_PlayerAtt *, char *, _DWORD, int))(v25 + 28))(
      &_this->_todo_224[84],
      655362,
      &_this->_todo_224[68],
      _this,
      (char *)(v31),
      0,
      v41);
    (((UIWnd *)&_this->_todo_224[84]))->UIWnd::sub_445FA0(&_this->_todo_224[68]);
    (**(void ( ***)(char *, _DWORD))&_this->_todo_224[84])((char *)(&_this->_todo_224[84]), (_DWORD)(0));
    _this->_todo_224[184] = 0;
    v26 = _this->_todo_05c - 38;
    _this->_todo_068 = _this->_todo_058 - 6;
    _this->_todo_06c = v26;
    goto LABEL_7;
  }
  v8 = v7 - 2;
  if ( !v8 )
  {
    _this->_todo_05c = todo_054 + 109;
    v10 = *(_DWORD *)_this->_todo_130;
    _this->_todo_058 = v6 + 308;
    (*(void ( **)(char *, int, char *, ARC_PlayerAtt *))(v10 + 16))(
      _this->_todo_130,
      655360,
      _this->_todo_050,
      _this);
    (((UIPushButton *)_this->_todo_130))->UIPushButton::CreateFromTemplate(Buffer, v41);
    (**(void ( ***)(char *, _DWORD))_this->_todo_130)((char *)(_this->_todo_130), (_DWORD)(0));
    (((UIWnd *)_this->_todo_130))->UIWnd::sub_445FA0(_this->_todo_050);
    v11 = *(_DWORD *)&_this->_todo_224[64];
    v12 = *(_DWORD *)&_this->_todo_224[60];
    v13 = _this->_todo_05c - v11 - 6;
    v14 = *(_DWORD *)todo_050 + 26;
    *(_DWORD *)&_this->_todo_224[72] = v13;
    *(_DWORD *)&_this->_todo_224[76] = v14 + v12;
    *(_DWORD *)&_this->_todo_224[68] = v14;
    v15 = *(_DWORD *)&_this->_todo_224[84];
    *(_DWORD *)&_this->_todo_224[80] = v11 + v13;
    (*(void ( **)(char *, int, char *, ARC_PlayerAtt *, char *, _DWORD, int))(v15 + 28))(
      &_this->_todo_224[84],
      655362,
      &_this->_todo_224[68],
      _this,
      (char *)(v31),
      0,
      v41);
    (((UIWnd *)&_this->_todo_224[84]))->UIWnd::sub_445FA0(&_this->_todo_224[68]);
    (**(void ( ***)(char *, _DWORD))&_this->_todo_224[84])((char *)(&_this->_todo_224[84]), (_DWORD)(0));
    _this->_todo_224[184] = 0;
    v16 = *(_DWORD *)&_this->_todo_224[60];
    v17 = _this->currolevalue[0];
    v18 = _this->_todo_058 - v16 - 26;
    *(_DWORD *)&_this->_todo_224[68] = v18;
    *(_DWORD *)&_this->_todo_224[76] = v16 + v18;
    (*(void ( **)(int *, int, char *, ARC_PlayerAtt *, char *, _DWORD, int))(v17 + 28))(
      _this->currolevalue,
      655363,
      &_this->_todo_224[68],
      _this,
      (char *)(v34),
      0,
      v41);
    (((UIWnd *)_this->currolevalue))->UIWnd::sub_445FA0(&_this->_todo_224[68]);
    (*(void ( **)(int *, _DWORD))_this->currolevalue[0])(_this->currolevalue, 0);
    LOBYTE(_this->dwMagicID[0][2]) = 0;
    v19 = _this->_todo_05c - 38;
    _this->_todo_068 = _this->_todo_058 - 6;
    _this->_todo_06c = v19;
LABEL_7:
    p_todo_060 = (int *)&_this->_todo_060;
    goto LABEL_8;
  }
  if ( v8 == 1 )
  {
    (((UINote *)&_this->_todo_070))->UINote::Create(655360, (int)_this->_todo_050, (int)_this, "UI\\Flex\\Note");
    (*(void ( **)(int *, _DWORD))_this->_todo_070)(&_this->_todo_070, 0);
    (((UIWnd *)&_this->_todo_070))->UIWnd::sub_445FA0(_this->_todo_050);
    v9 = _this->_todo_05c - 6;
    _this->_todo_068 = _this->_todo_058 - 6;
    _this->_todo_06c = v9;
  }
LABEL_8:
  v27 = *(_DWORD *)_this->_todo_1c8;
  *(_DWORD *)&_this->byMagicUseTime[6][0] = 0;
  *(_DWORD *)&_this->byMagicUseTime[6][4] = 0;
  _this->byMagicLevel[1][3] = 1;
  (*(void ( **)(char *, int, int *, ARC_PlayerAtt *))(v27 + 16))(
    _this->_todo_1c8,
    655360,
    p_todo_060,
    _this);
  (((UIWnd *)_this->_todo_1c8))->UIWnd::sub_445FA0(p_todo_060);
  (((UIScene *)_this->_todo_1c8))->UIScene::SetShow(0);
  (**(void ( ***)(char *, _DWORD))_this->_todo_1c8)((char *)(_this->_todo_1c8), (_DWORD)(0));
}

// 0x004A1A7C
scGlobalUserVar *GetGlobalUserVar(char *a1)
{
  JUMPOUT(0x4A1A80);
}

// 0x004A1CF0
int UIParabolaCtrl_GetState(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = *(_DWORD *)(v1 + 1328);
  *(_DWORD *)(v1 + 1328) = -1;
  return result;
}

// 0x004A36B0
LPSTR FormatChineseNumber(int nVal, LPSTR lpBuf)
{
  LPSTR result; // eax

  if ( nVal / 10 <= 0 )
    return lstrcpyA(lpBuf, (LPCSTR)&dword_DCA33C + 256 * nVal);
  lstrcpyA(lpBuf, (LPCSTR)&dword_DCA33C + 256 * (nVal / 10));
  result = lstrcatA(lpBuf, byte_DCAD3C);
  if ( nVal % 10 > 0 )
    return lstrcatA(lpBuf, (LPCSTR)&dword_DCA33C + 256 * (nVal % 10));
  return result;
}

// 0x004A4770
unsigned __int8 SetUIWndFlag(unsigned __int8 a1)
{
  unsigned __int8 result; // al

  result = a1;
  g_bUIWnd_DE625A = a1;
  return result;
}

// 0x004A5760
int LoadGameFrmRenderTarget(int a2)
{
  int v1; // ecx
  int v4; // edi
  int *v5; // ebx
  int v6; // esi
  int v7; // ebp
  int v8; // eax
  int v9; // eax
  void *v10; // edi
  const void *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  float fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  float fYb; // [esp+0x4] [ebp-0x20]
  int v20; // [esp+0x18] [ebp-0xC]
  int v21; // [esp+0x1C] [ebp-0x8]
  int a2a; // [esp+0x28] [ebp+0x4]

  *(_DWORD *)(v1 + 154488) = 0;
  *(_DWORD *)(v1 + 154492) = 0;
  a2a = 16;
  *(_BYTE *)(a2 + v1 + 154488) = 1;
  v4 = 16 * a2 + v1;
  v5 = (int *)(v4 + 154360);
  v6 = *(_DWORD *)(16 * (a2 + 9648) + v1) - *(_DWORD *)(v4 + 154360);
  v20 = v4;
  v21 = v6;
  v7 = 9344 * a2 + v1 + 4856;
  while ( 1 )
  {
    (((RenderTarget *)v7))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v7))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 58;
    fX = rand() % 10 + 66;
    v8 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetColor(v8 % 10 - 6, fX, fY);
    v9 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetAlpha(v9 % 55 - 56);
    *(_BYTE *)(v7 + 104) = 1;
    (((RenderTarget *)v7))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v7))->RenderTarget::SetState(1067030938);
    fYa = (float)*(int *)(v4 + 154364);
    fXa = (float)(*v5 + rand() % v6);
    (((RenderTarget *)v7))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v7))->RenderTarget::Render(*v5, v5[1], v5[2]);
    fYb = (float)(rand() % 2 + 1);
    fXb = (float)(rand() % 2 + 1);
    (((RenderTarget *)v7))->RenderTarget::SetOffset(fXb, fYb);
    (((RenderTarget *)v7))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v7))->RenderTarget::SetVisible(1);
    v10 = (void *)(v7 + 74752);
    v11 = (const void *)v7;
    v7 += 584;
    result = a2a - 1;
    v12 = a2a == 1;
    qmemcpy(v10, v11, 0x248u);
    --a2a;
    if ( v12 )
      break;
    v4 = v20;
    v6 = v21;
  }
  return result;
}

// 0x004A6600
int UIGameFrm_Destroy(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx

  v2 = v1;
  Destroy__ovl_03(v1);
  result = (*(int ( **)(_DWORD))(**(_DWORD **)(v2 + 176056) + 12))(*(_DWORD *)(v2 + 176056));
  v4 = *(_DWORD *)(v2 + 176056);
  if ( v4 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
  v5 = *(_DWORD *)(v2 + 176060);
  if ( v5 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
  v6 = *(_DWORD *)(v2 + 176064);
  if ( v6 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v6 + 20))(v6, 1);
  v7 = *(_DWORD *)(v2 + 176068);
  if ( v7 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v7 + 20))(v7, 1);
  v8 = *(_DWORD *)(v2 + 176072);
  if ( v8 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
  v9 = *(_DWORD *)(v2 + 176076);
  if ( v9 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
  v10 = *(_DWORD *)(v2 + 176080);
  if ( v10 )
    result = (*(int ( **)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
  *(_DWORD *)(v2 + 176056) = 0;
  *(_DWORD *)(v2 + 176060) = 0;
  *(_DWORD *)(v2 + 176064) = 0;
  *(_DWORD *)(v2 + 176068) = 0;
  *(_DWORD *)(v2 + 176072) = 0;
  *(_DWORD *)(v2 + 176076) = 0;
  *(_DWORD *)(v2 + 176080) = 0;
  return result;
}

// 0x004A67B0
int CCCTData_DestroyImage(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  gbImage2D *v3; // esi
  gbImage2D *v4; // edi
  int v5; // eax
  int *v6; // eax
  int v7; // ebx
  int v8; // edi
  int *j; // esi
  bool v10; // zf
  int result; // eax
  int *i; // [esp+0x10] [ebp-0x24]
  int v13; // [esp+0x14] [ebp-0x20]
  int v14; // [esp+0x18] [ebp-0x1C]
  gbImage2D *v15; // [esp+0x20] [ebp-0x14]

  v2 = v1;
  v3 = (gbImage2D *)(v1 + 4);
  v15 = (gbImage2D *)(v1 + 4);
  (((gbImage2D *)(v1 + 4)))->gbImage2D::Release();
  v4 = (gbImage2D *)(v2 + 204);
  (((gbImage2D *)(v2 + 204)))->gbImage2D::Release();
  v5 = *(_DWORD *)(v2 + 412);
  v14 = *(_DWORD *)(v2 + 416);
  v13 = v5;
  if ( v5 != v14 )
  {
    v6 = (int *)(v5 + 12);
    for ( i = v6; ; v6 = i )
    {
      v7 = (unsigned long)v6[1];
      v8 = (unsigned long)*v6;
      for ( j = v6 - 1; v8 != v7; v8 += 16 )
        (((Object *)j))->Object::Update(v8);
      operator delete((void *)j[1]);
      j[1] = 0;
      j[2] = 0;
      j[3] = 0;
      v10 = v13 + 24 == v14;
      v13 += 24;
      i += 6;
      if ( v10 )
        break;
    }
    v4 = (gbImage2D *)(v2 + 204);
    v3 = (gbImage2D *)v15;
  }
  operator delete(*(void **)(v2 + 412));
  *(_DWORD *)(v2 + 412) = 0;
  *(_DWORD *)(v2 + 416) = 0;
  *(_DWORD *)(v2 + 420) = 0;
  (((gbImage2D *)v4))->gbImage2D::~gbImage2D();
  (((gbImage2D *)v3))->gbImage2D::~gbImage2D();
  return result;
}

// 0x004A7C40
int SystemUI_LayoutWidgets(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  UIPushButton *v4; // edi
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // eax
  int v28; // edx
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // edx
  int v33; // eax
  int v34; // edx
  int v35; // edx
  int v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // ecx
  int v42; // eax
  _DWORD v44[2]; // [esp+0x8C] [ebp-0x20] BYREF
  int v45; // [esp+0x94] [ebp-0x18]
  int v46; // [esp+0x98] [ebp-0x14]
  _DWORD v47[4]; // [esp+0x9C] [ebp-0x10] BYREF

  v2 = v1;
  v3 = *(_DWORD *)(v1 + 23760);
  v4 = (UIPushButton *)(v1 + 23760);
  v44[1] = 543;
  v44[0] = 0;
  v45 = 256;
  v46 = 600;
  (*(void ( **)(int, int, _DWORD *))(v3 + 16))(v1 + 23760, 161, (_DWORD *)(v44));
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)v4))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v5);
  v6 = *(_DWORD *)(v2 + 23912);
  v44[0] = v45;
  v45 += 512;
  (*(void ( **)(int, int, _DWORD *, int))(v6 + 16))(v2 + 23912, 161, (_DWORD *)(v44), v2);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)(v2 + 23912)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v7);
  v44[0] = v45;
  v45 += 32;
  (*(void ( **)(int, int, _DWORD *, int))(*(_DWORD *)(v2 + 24064) + 16))(v2 + 24064, 161, (_DWORD *)(v44), v2);
  LOBYTE(v8) = g_bDebugMode;
  (((UIPushButton *)(v2 + 24064)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v8);
  *(_DWORD *)(v2 + 27468) = 546;
  *(_DWORD *)(v2 + 27464) = 38;
  *(_DWORD *)(v2 + 27472) = 148;
  *(_DWORD *)(v2 + 27476) = *(_DWORD *)(v2 + 27468) + 50;
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 24216) + 28))(
    v2 + 24216,
    &byte_A00102,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v9);
  *(_DWORD *)(v2 + 177292) = *(_DWORD *)(v2 + 27468) + 5;
  *(_DWORD *)(v2 + 177288) = *(_DWORD *)(v2 + 27464) + 35;
  *(_DWORD *)(v2 + 177296) = *(_DWORD *)(v2 + 27472) - 36;
  *(_DWORD *)(v2 + 177300) = *(_DWORD *)(v2 + 27476) - 5;
  v10 = *(_DWORD *)(v2 + 27472) - 22;
  *(_DWORD *)(v2 + 27464) = v10;
  v10 += 110;
  *(_DWORD *)(v2 + 27472) = v10;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 25248) + 28))(
    &byte_A00105,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v10);
  *(_DWORD *)(v2 + 177340) = *(_DWORD *)(v2 + 27468) + 5;
  *(_DWORD *)(v2 + 177336) = *(_DWORD *)(v2 + 27464) + 35;
  *(_DWORD *)(v2 + 177344) = *(_DWORD *)(v2 + 27472) - 36;
  *(_DWORD *)(v2 + 177348) = *(_DWORD *)(v2 + 27476) - 5;
  v11 = *(_DWORD *)(v2 + 27472) - 22;
  *(_DWORD *)(v2 + 27464) = v11;
  v11 += 110;
  *(_DWORD *)(v2 + 27472) = v11;
  LOBYTE(v11) = g_bDebugMode;
  (*(void ( **)(int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 24904) + 28))(
    &byte_A00104,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v11);
  *(_DWORD *)(v2 + 177324) = *(_DWORD *)(v2 + 27468) + 5;
  *(_DWORD *)(v2 + 177320) = *(_DWORD *)(v2 + 27464) + 35;
  v12 = *(_DWORD *)(v2 + 27472);
  v13 = *(_DWORD *)(v2 + 27476);
  v14 = v12 - 36;
  v12 -= 22;
  *(_DWORD *)(v2 + 27464) = v12;
  v13 -= 5;
  *(_DWORD *)(v2 + 177328) = v14;
  *(_DWORD *)(v2 + 177332) = v13;
  *(_DWORD *)(v2 + 27472) = v12 + 110;
  LOBYTE(v13) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 24560) + 28))(
    v2 + 24560,
    &byte_A00103,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v13);
  v15 = *(_DWORD *)(v2 + 27464);
  *(_DWORD *)(v2 + 177308) = *(_DWORD *)(v2 + 27468) + 5;
  v16 = *(_DWORD *)(v2 + 27472);
  *(_DWORD *)(v2 + 177304) = v15 + 35;
  v17 = *(_DWORD *)(v2 + 27476);
  v18 = v16 - 36;
  v16 -= 22;
  *(_DWORD *)(v2 + 27464) = v16;
  v16 += 110;
  *(_DWORD *)(v2 + 177312) = v18;
  *(_DWORD *)(v2 + 177316) = v17 - 5;
  *(_DWORD *)(v2 + 27472) = v16;
  LOBYTE(v16) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 26280) + 28))(
    v2 + 26280,
    &byte_A00108,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v16);
  v19 = *(_DWORD *)(v2 + 27464);
  v20 = *(_DWORD *)(v2 + 27472);
  *(_DWORD *)(v2 + 177356) = *(_DWORD *)(v2 + 27468) + 5;
  v21 = v20 - 36;
  *(_DWORD *)(v2 + 177352) = v19 + 35;
  v22 = *(_DWORD *)(v2 + 27476);
  v20 -= 22;
  *(_DWORD *)(v2 + 27464) = v20;
  *(_DWORD *)(v2 + 27472) = v20 + 110;
  v23 = *(_DWORD *)(v2 + 27464) - 38;
  v47[1] = 546;
  v47[0] = v23;
  *(_DWORD *)(v2 + 177360) = v21;
  v47[2] = v23 + 256;
  v24 = *(_DWORD *)(v2 + 27312);
  *(_DWORD *)(v2 + 177364) = v22 - 5;
  v47[3] = 610;
  (*(void ( **)(int, int, _DWORD *, int))(v24 + 16))(v2 + 27312, 161, (_DWORD *)(v47), v2);
  LOBYTE(v25) = g_bDebugMode;
  (((UIPushButton *)(v2 + 27312)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v25);
  LOBYTE(v26) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 25592) + 28))(
    v2 + 25592,
    &byte_A00106,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v26);
  v27 = *(_DWORD *)(v2 + 27472);
  v28 = *(_DWORD *)(v2 + 27464) + 35;
  *(_DWORD *)(v2 + 177372) = *(_DWORD *)(v2 + 27468) + 5;
  *(_DWORD *)(v2 + 177368) = v28;
  v29 = v27 - 36;
  v30 = *(_DWORD *)(v2 + 27476);
  v27 -= 22;
  *(_DWORD *)(v2 + 27464) = v27;
  v30 -= 5;
  *(_DWORD *)(v2 + 177376) = v29;
  *(_DWORD *)(v2 + 177380) = v30;
  *(_DWORD *)(v2 + 27472) = v27 + 110;
  LOBYTE(v30) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(*(_DWORD *)(v2 + 25936) + 28))(
    v2 + 25936,
    &byte_A00107,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v30);
  v31 = *(_DWORD *)(v2 + 27464);
  v32 = *(_DWORD *)(v2 + 27472);
  *(_DWORD *)(v2 + 177388) = *(_DWORD *)(v2 + 27468) + 5;
  v33 = *(_DWORD *)(v2 + 27476) - 5;
  *(_DWORD *)(v2 + 177384) = v31 + 35;
  *(_DWORD *)(v2 + 177392) = v32 - 36;
  v34 = *(_DWORD *)(v2 + 26968);
  *(_DWORD *)(v2 + 177396) = v33;
  LOBYTE(v33) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(v34 + 28))(
    v2 + 26968,
    &byte_A00110,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v33);
  v35 = *(_DWORD *)(v2 + 26624);
  v36 = *(_DWORD *)(v2 + 27472) - 22;
  *(_DWORD *)(v2 + 27464) = v36;
  v36 += 110;
  *(_DWORD *)(v2 + 27472) = v36;
  LOBYTE(v36) = g_bDebugMode;
  (*(void ( **)(int, int *, int, int, char *, int, int))(v35 + 28))(
    v2 + 26624,
    &byte_A00109,
    v2 + 27464,
    v2,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v36);
  v37 = *(_DWORD *)(v2 + 27468);
  v38 = *(_DWORD *)(v2 + 27472) - 36;
  *(_DWORD *)(v2 + 177400) = *(_DWORD *)(v2 + 27464) + 35;
  v39 = *(_DWORD *)(v2 + 92);
  *(_DWORD *)(v2 + 177408) = v38;
  v40 = *(_DWORD *)(v2 + 88);
  *(_DWORD *)(v2 + 177404) = v37 + 5;
  v41 = *(_DWORD *)(v2 + 27476);
  v40 -= 38;
  *(_DWORD *)(v2 + 27468) = v39 - 51;
  *(_DWORD *)(v2 + 27464) = v40;
  *(_DWORD *)(v2 + 27472) = v40 + 38;
  v42 = *(_DWORD *)(v2 + 27468);
  *(_DWORD *)(v2 + 177412) = v41 - 5;
  *(_DWORD *)(v2 + 27476) = v42 + 48;
  return (((UIWnd *)(v2 + 26968)))->UIWnd::sub_445FA0((void *)(v2 + 27464));
}

// 0x004A8150
int SystemUI_ShowPage(int nVal)
{
  int v1; // ecx
  int v2; // esi
  PalScript *v3; // ebx

  v2 = v1;
  v3 = (PalScript *)(v1 + 25592);
  if ( g_bRoleFlag1 )
    (((PalScript *)v3))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnSword.tga", g_bDebugMode);
  else
    (((PalScript *)v3))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
  if ( !g_bRoleFlag2 )
    (((PalScript *)(v2 + 25936)))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50(v2 + 25936);
  sub_445E50((int)v3);
  sub_445E50(v2 + 24216);
  sub_445E50(v2 + 24560);
  sub_445E50(v2 + 24904);
  sub_445E50(v2 + 25248);
  sub_445E50(v2 + 26280);
  sub_445E50(v2 + 26624);
  return sub_445E50(v2 + 26968);
}

// 0x004A8230
unsigned int ClampToRange(unsigned int a2, int a3)
{
  int v2; // ecx
  unsigned int result; // eax

  result = *(_DWORD *)(v2 + 8 * a3 + 383216);
  if ( a2 <= result )
  {
    result = *(_DWORD *)(v2 + 8 * a3 + 383212);
    if ( a2 >= result )
      return a2;
  }
  return result;
}

// 0x004A8770
bool Create__ovl_1_0(CCCTData *_this, void *param)
{
  float z; // eax
  float *p_z; // edi
  int v5; // edx
  unsigned int dwID; // eax
  int v7; // ecx
  float fCircleCentreX; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // ecx
  float *p_fSwingFre; // edi
  int v21; // ebp
  int v22; // ecx
  int v23; // eax
  float fCircleEndX; // edx
  int v25; // edx
  int v26; // eax
  float fStartTime; // edx
  int v28; // eax
  float fSwingFre; // edx
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // edx
  float fSwing; // eax
  float fAccelerationTime1; // edx
  int v36; // ecx
  int v37; // ecx
  int v38; // eax
  int v39; // ecx
  int v40; // eax
  float *p_fCircleEndX; // edi
  int v42; // ebp
  int v43; // ecx
  int v44; // eax
  _inline_tagCam_yaw v45; // edx
  float fStartTracePosX; // edx
  int v47; // eax
  float fAccelerationTime2; // edx
  int v49; // eax
  float x; // edx
  int v51; // eax
  float fStartTracePosY; // eax
  _inline_tagCam_yaw v53; // edx
  float y; // eax
  int v55; // edx
  float v56; // edx
  int v57; // ecx
  int v58; // eax
  float fTimeExpiate; // edx
  float v60; // eax
  int v61; // ecx
  float fCircleEndZ; // edx
  int p_DWORD; // [esp+0x2BC] [ebp-D0h] BYREF
  int v65; // [esp+0x2C0] [ebp-CCh]
  int nHeight; // [esp+0x2C4] [ebp-C8h]
  int v67; // [esp+0x2C8] [ebp-C4h]
  _DWORD v68[2]; // [esp+0x2CC] [ebp-C0h] BYREF
  int v69; // [esp+0x2D4] [ebp-B8h]
  int v70; // [esp+0x2D8] [ebp-B4h]
  int v71; // [esp+0x2DC] [ebp-B0h] BYREF
  int v72; // [esp+0x2E0] [ebp-ACh]
  int v73; // [esp+0x2E4] [ebp-A8h]
  int v74; // [esp+0x2E8] [ebp-A4h]
  _DWORD v75[2]; // [esp+0x2EC] [ebp-A0h] BYREF
  int v76; // [esp+0x2F4] [ebp-0x98]
  int v77; // [esp+0x2F8] [ebp-0x94]
  int v78; // [esp+0x2FC] [ebp-0x90] BYREF
  int v79; // [esp+0x300] [ebp-0x8C]
  int v80; // [esp+0x304] [ebp-0x88]
  int v81; // [esp+0x308] [ebp-0x84]
  int v82; // [esp+0x30C] [ebp-0x80] BYREF
  int v83; // [esp+0x310] [ebp-0x7C]
  int v84; // [esp+0x314] [ebp-0x78]
  int v85; // [esp+0x318] [ebp-0x74]
  gbVec3D pDir; // [esp+0x31C] [ebp-0x70] BYREF
  int v87; // [esp+0x328] [ebp-0x64]
  int v88; // [esp+0x32C] [ebp-0x60] BYREF
  int v89; // [esp+0x330] [ebp-0x5C]
  int v90; // [esp+0x334] [ebp-0x58]
  int v91; // [esp+0x338] [ebp-0x54]
  gbVec3D pPos; // [esp+0x33C] [ebp-0x50] BYREF
  int v93; // [esp+0x348] [ebp-0x44]
  int v94; // [esp+0x34C] [ebp-0x40] BYREF
  int v95; // [esp+0x350] [ebp-0x3C]
  int v96; // [esp+0x354] [ebp-0x38]
  int v97; // [esp+0x358] [ebp-0x34]
  _DWORD v98[2]; // [esp+0x35C] [ebp-0x30] BYREF
  int v99; // [esp+0x364] [ebp-0x28]
  int v100; // [esp+0x368] [ebp-0x24]
  _DWORD v101[4]; // [esp+0x36C] [ebp-0x20] BYREF
  _DWORD v102[4]; // [esp+0x37C] [ebp-0x10] BYREF

  z = _this->m_Pool[1892].EndPos.z;
  p_z = (float *)&_this->m_Pool[1892].EndPos.z;
  v72 = 108;
  v71 = 52;
  v73 = 388;
  v74 = 501;
  (*(void ( **)(float *, __int16 *, int *, CCCTData *))(LODWORD(z) + 16))(
    &_this->m_Pool[1892].EndPos.z,
    &word_A00552,
    &v71,
    _this);
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)p_z))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ListFrame.tga", v5);
  (**(void ( ***)(float *, _DWORD))p_z)((float *)(p_z), (_DWORD)(0));
  v83 = v72 + 52;
  v82 = v71 + 10;
  v85 = v72 + 84;
  dwID = _this->m_Pool[1890].dwID;
  v84 = v73;
  (*(void ( **)(unsigned int *, __int16 *, int *, CCCTData *))(dwID + 16))(
    &_this->m_Pool[1890].dwID,
    &word_A00552,
    &v82,
    _this);
  (((UIScene *)&_this->m_Pool[1890].dwID))->UIScene::SetShow(0);
  AllocObject(&_this->m_Pool[1890].dwID);
  sprintf(
    (char *const)&_this->m_Pool[0].nTraceRole,
    " %s            %s %s  %s",
    (const char *)&dword_DC353C,
    (const char *)&dword_DC373C,
    (const char *)&dword_DCF73C,
    (const char *)&dword_DC363C);
  SetEnable((UICaption *)&_this->m_Pool[1890].dwID);
  v101[0] = v71;
  v101[1] = v72 + 2;
  v101[3] = v72 + 34;
  v101[2] = v73;
  (*(void ( **)(float *, __int16 *, _DWORD *, char *, _DWORD, CCCTData *))(LODWORD(_this->m_Pool[1889].fAngleSpeed)
                                                                                   + 28))(
    &_this->m_Pool[1889].fAngleSpeed,
    &word_A00552,
    (_DWORD *)(v101),
    "UI\\Flex\\Bar.tga",
    0,
    _this);
  (((CScreenMode *)&_this->m_Pool[1889].fAngleSpeed))->CScreenMode::SetPosition(32,   32);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1889].fAngleSpeed))(&_this->m_Pool[1889].fAngleSpeed, 0);
  p_DWORD = v71 + 18;
  v65 = v72 + 76;
  v67 = v72 + 364;
  LODWORD(pPos.y) = v72 + 91;
  nHeight = v71 + 316;
  v7 = v71 + 307;
  v93 = v72 + 117;
  LODWORD(pPos.z) = v71 + 307;
  LODWORD(pDir.z) = v71 + 307;
  LOBYTE(v7) = g_bDebugMode;
  LODWORD(pDir.y) = v72 + 323;
  LODWORD(pPos.x) = v71 + 285;
  LODWORD(pDir.x) = v71 + 285;
  fCircleCentreX = _this->m_Pool[1911].fCircleCentreX;
  v87 = v72 + 349;
  v9 = (*(int ( **)(float *, int *, int *, CCCTData *, _DWORD, int, int))(LODWORD(fCircleCentreX) + 28))(
         &_this->m_Pool[1911].fCircleCentreX,
         &byte_A00529,
         &p_DWORD,
         _this,
         0,
         1,
         v7);
  LOBYTE(v9) = g_bDebugMode;
  (((UIListBox *)&_this->m_Pool[1911].fCircleCentreX))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v9);
  _this->m_Pool[1917].EndPos.rol = NAN;
  (((UIListBox *)&_this->m_Pool[1911].fCircleCentreX))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&_this->m_Pool[1912].dwID))->CCBUI::ShowEffect(v65 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&_this->m_Pool[1912].dwID))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&_this->m_Pool[1912].dwID))->CCBUI::SetSelection(27);
  (((CCBUI *)&_this->m_Pool[1912].dwID))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&_this->m_Pool[1911].fCircleCentreX))->UIListBox::SetLockSel(23);
  (((UIListBox *)&_this->m_Pool[1911].fCircleCentreX))->UIListBox::SetColumnHead((int)"Name", 130);
  (((UIListBox *)&_this->m_Pool[1911].fCircleCentreX))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 38);
  (((UIListBox *)&_this->m_Pool[1911].fCircleCentreX))->UIListBox::SetColumnHead((int)"Gu", 38);
  (((UIListBox *)&_this->m_Pool[1911].fCircleCentreX))->UIListBox::SetColumnHead((int)"Price", 50);
  (((CCBUI *)&_this->m_Pool[1912].dwID))->CCBUI::VirtualCall(1);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1911].fCircleCentreX))(
    &_this->m_Pool[1911].fCircleCentreX,
    0);
  LOBYTE(_this->m_Pool[1912].fp[3]) = 0;
  LOBYTE(v10) = g_bDebugMode;
  v11 = (*(int ( **)(float *, int *, int *, CCCTData *, _DWORD, int, int))(LODWORD(_this->m_Pool[1917].fAcceleration1)
                                                                                   + 28))(
          &_this->m_Pool[1917].fAcceleration1,
          &byte_A00530,
          &p_DWORD,
          _this,
          0,
          1,
          v10);
  LOBYTE(v11) = g_bDebugMode;
  (((UIListBox *)&_this->m_Pool[1917].fAcceleration1))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v11);
  _this->m_Pool[1923].EndPos.y = NAN;
  (((UIListBox *)&_this->m_Pool[1917].fAcceleration1))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&_this->m_Pool[1918]))->CCBUI::ShowEffect(v65 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&_this->m_Pool[1918]))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&_this->m_Pool[1918]))->CCBUI::SetSelection(27);
  (((CCBUI *)&_this->m_Pool[1918]))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&_this->m_Pool[1917].fAcceleration1))->UIListBox::SetLockSel(23);
  (((UIListBox *)&_this->m_Pool[1917].fAcceleration1))->UIListBox::SetColumnHead((int)"Name", 130);
  (((UIListBox *)&_this->m_Pool[1917].fAcceleration1))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 38);
  (((UIListBox *)&_this->m_Pool[1917].fAcceleration1))->UIListBox::SetColumnHead((int)"Gu", 38);
  (((UIListBox *)&_this->m_Pool[1917].fAcceleration1))->UIListBox::SetColumnHead((int)"Price", 50);
  (((CCBUI *)&_this->m_Pool[1918]))->CCBUI::VirtualCall(1);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1917].fAcceleration1))(
    &_this->m_Pool[1917].fAcceleration1,
    0);
  LOBYTE(_this->m_Pool[1917].dwReserved[1]) = 0;
  LOBYTE(v12) = g_bDebugMode;
  v13 = (*(int ( **)(float *, int *, int *, CCCTData *, _DWORD, int, int))(LODWORD(_this->m_Pool[1923].fStartSpeed)
                                                                                   + 28))(
          &_this->m_Pool[1923].fStartSpeed,
          &byte_A00531,
          &p_DWORD,
          _this,
          0,
          1,
          v12);
  LOBYTE(v13) = g_bDebugMode;
  (((UIListBox *)&_this->m_Pool[1923].fStartSpeed))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v13);
  _this->m_Pool[1929].StartPos.yaw.p = (CEffMgr *)-4;
  (((UIListBox *)&_this->m_Pool[1923].fStartSpeed))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&_this->m_Pool[1923].fStartTracePosY))->CCBUI::ShowEffect(v65 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&_this->m_Pool[1923].fStartTracePosY))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&_this->m_Pool[1923].fStartTracePosY))->CCBUI::SetSelection(27);
  (((CCBUI *)&_this->m_Pool[1923].fStartTracePosY))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&_this->m_Pool[1923].fStartSpeed))->UIListBox::SetLockSel(23);
  (((UIListBox *)&_this->m_Pool[1923].fStartSpeed))->UIListBox::SetColumnHead((int)"Name", 130);
  (((UIListBox *)&_this->m_Pool[1923].fStartSpeed))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 38);
  (((UIListBox *)&_this->m_Pool[1923].fStartSpeed))->UIListBox::SetColumnHead((int)"Gu", 38);
  (((UIListBox *)&_this->m_Pool[1923].fStartSpeed))->UIListBox::SetColumnHead((int)"Price", 50);
  (((CCBUI *)&_this->m_Pool[1923].fStartTracePosY))->CCBUI::VirtualCall(1);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1923].fStartSpeed))(&_this->m_Pool[1923].fStartSpeed, 0);
  LOBYTE(_this->m_Pool[1923].fStartTracePosX) = 0;
  LOBYTE(v14) = g_bDebugMode;
  v15 = (*(int ( **)(_BYTE *, int *, int *, CCCTData *, _DWORD, int, int))(*(_DWORD *)&_this->m_Pool[1929].bLineMove
                                                                                   + 28))(
          &_this->m_Pool[1929].bLineMove,
          &byte_A00532,
          &p_DWORD,
          _this,
          0,
          1,
          v14);
  LOBYTE(v15) = g_bDebugMode;
  (((UIListBox *)&_this->m_Pool[1929].bLineMove))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v15);
  _this->m_Pool[1935].fExpectTime = NAN;
  (((UIListBox *)&_this->m_Pool[1929].bLineMove))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&_this->m_Pool[1929].fTimeExpiate))->CCBUI::ShowEffect(v65 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&_this->m_Pool[1929].fTimeExpiate))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&_this->m_Pool[1929].fTimeExpiate))->CCBUI::SetSelection(27);
  (((CCBUI *)&_this->m_Pool[1929].fTimeExpiate))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&_this->m_Pool[1929].bLineMove))->UIListBox::SetLockSel(23);
  (((UIListBox *)&_this->m_Pool[1929].bLineMove))->UIListBox::SetColumnHead((int)"Name", 130);
  (((UIListBox *)&_this->m_Pool[1929].bLineMove))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 38);
  (((UIListBox *)&_this->m_Pool[1929].bLineMove))->UIListBox::SetColumnHead((int)"Gu", 38);
  (((UIListBox *)&_this->m_Pool[1929].bLineMove))->UIListBox::SetColumnHead((int)"Price", 50);
  (((CCBUI *)&_this->m_Pool[1929].fTimeExpiate))->CCBUI::VirtualCall(1);
  (**(void ( ***)(_BYTE *, _DWORD))&_this->m_Pool[1929].bLineMove)((_BYTE *)(&_this->m_Pool[1929].bLineMove), (_DWORD)(0));
  LOBYTE(_this->m_Pool[1929].fSwing) = 0;
  LOBYTE(v16) = g_bDebugMode;
  v17 = (*(int ( **)(float *, int *, int *, CCCTData *, _DWORD, int, int))(LODWORD(_this->m_Pool[1935].EndPos.rol)
                                                                                   + 28))(
          &_this->m_Pool[1935].EndPos.rol,
          &byte_A00533,
          &p_DWORD,
          _this,
          0,
          1,
          v16);
  LOBYTE(v17) = g_bDebugMode;
  (((UIListBox *)&_this->m_Pool[1935].EndPos.rol))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v17);
  _this->m_Pool[1941].fp[3] = (char *)-4;
  (((UIListBox *)&_this->m_Pool[1935].EndPos.rol))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&_this->m_Pool[1935].fCircleEndY))->CCBUI::ShowEffect(v65 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&_this->m_Pool[1935].fCircleEndY))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&_this->m_Pool[1935].fCircleEndY))->CCBUI::SetSelection(27);
  (((CCBUI *)&_this->m_Pool[1935].fCircleEndY))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&_this->m_Pool[1935].EndPos.rol))->UIListBox::SetLockSel(23);
  (((UIListBox *)&_this->m_Pool[1935].EndPos.rol))->UIListBox::SetColumnHead((int)"Name", 130);
  (((UIListBox *)&_this->m_Pool[1935].EndPos.rol))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 38);
  (((UIListBox *)&_this->m_Pool[1935].EndPos.rol))->UIListBox::SetColumnHead((int)"Gu", 38);
  (((UIListBox *)&_this->m_Pool[1935].EndPos.rol))->UIListBox::SetColumnHead((int)"Price", 50);
  (((CCBUI *)&_this->m_Pool[1935].fCircleEndY))->CCBUI::VirtualCall(1);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1935].EndPos.rol))(&_this->m_Pool[1935].EndPos.rol, 0);
  v18 = v65 + 2;
  v78 = p_DWORD;
  v19 = p_DWORD + 256;
  v79 = v65 + 2;
  LOBYTE(_this->m_Pool[1935].fCircleEndX) = 0;
  v80 = v19;
  v81 = v18 + 23;
  p_fSwingFre = (float *)&_this->m_Pool[1893].fSwingFre;
  v21 = 12;
  do
  {
    (*(void ( **)(float *, __int16 *, int *, CCCTData *))(*(_DWORD *)p_fSwingFre + 16))(
      p_fSwingFre,
      &word_A00552,
      &v78,
      _this);
    LOBYTE(v22) = g_bDebugMode;
    (((UIPushButton *)p_fSwingFre))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\List_Grid.tga", v22);
    (**(void ( ***)(float *, _DWORD))p_fSwingFre)((float *)(p_fSwingFre), (_DWORD)(0));
    p_fSwingFre += 38;
    v79 = v81;
    --v21;
    v81 += 23;
  }
  while ( v21 );
  v68[1] = v72;
  v23 = v72 + 50;
  v68[0] = v71 + 16;
  v70 = v72 + 50;
  LOBYTE(v23) = g_bDebugMode;
  fCircleEndX = _this->m_Pool[1879].fCircleEndX;
  v69 = v71 + 56;
  (*(void ( **)(float *, int *, _DWORD *, CCCTData *, char *, _DWORD, int))(LODWORD(fCircleEndX) + 28))(
    &_this->m_Pool[1879].fCircleEndX,
    &byte_A00559,
    (_DWORD *)(v68),
    _this,
    "UI\\GameMainUI\\Equip\\Weapon",
    0,
    v23);
  (((PalScript *)&_this->m_Pool[1879].fCircleEndX))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Weapon2.tga", g_bDebugMode);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1879].fCircleEndX))(&_this->m_Pool[1879].fCircleEndX, 0);
  v25 = *(_DWORD *)&_this->m_Pool[1881].bStartCamValid;
  v68[0] = v69 + 26;
  v69 += 66;
  v26 = v69;
  LOBYTE(v26) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, _DWORD *, CCCTData *, char *, _DWORD, int))(v25 + 28))(
    &_this->m_Pool[1881].bStartCamValid,
    &byte_A00560,
    (_DWORD *)(v68),
    _this,
    "UI\\GameMainUI\\Equip\\Cloth",
    0,
    v26);
  (((PalScript *)&_this->m_Pool[1881].bStartCamValid))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Cloth2.tga", g_bDebugMode);
  (**(void ( ***)(_BYTE *, _DWORD))&_this->m_Pool[1881].bStartCamValid)((_BYTE *)(&_this->m_Pool[1881].bStartCamValid), (_DWORD)(0));
  fStartTime = _this->m_Pool[1883].fStartTime;
  v68[0] = v69 + 26;
  v69 += 66;
  v28 = v69;
  LOBYTE(v28) = g_bDebugMode;
  (*(void ( **)(float *, int *, _DWORD *, CCCTData *, char *, _DWORD, int))(LODWORD(fStartTime) + 28))(
    &_this->m_Pool[1883].fStartTime,
    &byte_A00561,
    (_DWORD *)(v68),
    _this,
    "UI\\GameMainUI\\Equip\\Hat",
    0,
    v28);
  (((PalScript *)&_this->m_Pool[1883].fStartTime))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Hat2.tga", g_bDebugMode);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1883].fStartTime))(&_this->m_Pool[1883].fStartTime, 0);
  fSwingFre = _this->m_Pool[1884].fSwingFre;
  v68[0] = v69 + 26;
  v69 += 66;
  v30 = v69;
  LOBYTE(v30) = g_bDebugMode;
  (*(void ( **)(float *, int *, _DWORD *, CCCTData *, char *, _DWORD, int))(LODWORD(fSwingFre) + 28))(
    &_this->m_Pool[1884].fSwingFre,
    &byte_A00562,
    (_DWORD *)(v68),
    _this,
    "UI\\GameMainUI\\Equip\\Shoes",
    0,
    v30);
  (((PalScript *)&_this->m_Pool[1884].fSwingFre))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Shoes2.tga", g_bDebugMode);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1884].fSwingFre))(&_this->m_Pool[1884].fSwingFre, 0);
  v31 = *(_DWORD *)&_this->m_Pool[1886].bRandSwing;
  v68[0] = v69 + 26;
  v69 += 66;
  v32 = v69;
  LOBYTE(v32) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, _DWORD *, CCCTData *, char *, _DWORD, int))(v31 + 28))(
    &_this->m_Pool[1886].bRandSwing,
    &byte_A00563,
    (_DWORD *)(v68),
    _this,
    "UI\\GameMainUI\\Equip\\Adorn",
    0,
    v32);
  (((PalScript *)&_this->m_Pool[1886].bRandSwing))->PalScript::OpenScript("UI\\GameMainUI\\Equip\\Adorn2.tga", g_bDebugMode);
  (**(void ( ***)(_BYTE *, _DWORD))&_this->m_Pool[1886].bRandSwing)((_BYTE *)(&_this->m_Pool[1886].bRandSwing), (_DWORD)(0));
  v89 = v72;
  v88 = v73 + 6;
  v91 = v74;
  v90 = v73 + 342;
  (*((void ( **)(char **, __int16 *, int *, CCCTData *))_this->m_Pool[1893].fp[3] + 4))(
    &_this->m_Pool[1893].fp[3],
    &word_A00552,
    &v88,
    _this);
  LOBYTE(v33) = g_bDebugMode;
  (((UIPushButton *)&_this->m_Pool[1893].fp[3]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Equip\\ListFrame.tga", v33);
  (*(void ( **)(char **, _DWORD))_this->m_Pool[1893].fp[3])(&_this->m_Pool[1893].fp[3], 0);
  v83 = v89 + 52;
  v82 = v88 + 10;
  v85 = v89 + 84;
  fSwing = _this->m_Pool[1890].fSwing;
  v84 = v90;
  (*(void ( **)(float *, __int16 *, int *, CCCTData *))(LODWORD(fSwing) + 16))(
    &_this->m_Pool[1890].fSwing,
    &word_A00552,
    &v82,
    _this);
  (((UIScene *)&_this->m_Pool[1890].fSwing))->UIScene::SetShow(0);
  AllocObject(&_this->m_Pool[1890].fSwing);
  sprintf(
    (char *const)&_this->m_Pool[0].nTraceRole,
    " %s            %s %s  %s",
    (const char *)&dword_DC353C,
    (const char *)&dword_DC373C,
    (const char *)&dword_DCF73C,
    (const char *)&dword_DC363C);
  SetEnable((UICaption *)&_this->m_Pool[1890].fSwing);
  fAccelerationTime1 = _this->m_Pool[1891].fAccelerationTime1;
  v83 = v89;
  v82 = v88 + 7;
  v85 = v89 + 49;
  v84 = v88 + 327;
  (*(void ( **)(float *, __int16 *, int *, CCCTData *))(LODWORD(fAccelerationTime1) + 16))(
    &_this->m_Pool[1891].fAccelerationTime1,
    &word_A00552,
    &v82,
    _this);
  LOBYTE(v36) = g_bDebugMode;
  (((UIPushButton *)&_this->m_Pool[1891].fAccelerationTime1))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\PurgeTitle.tga", v36);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1891].fAccelerationTime1))(
    &_this->m_Pool[1891].fAccelerationTime1,
    0);
  p_DWORD = v88 + 18;
  v65 = v89 + 76;
  v67 = v89 + 364;
  LODWORD(pPos.y) = v89 + 91;
  nHeight = v88 + 316;
  v37 = v88 + 307;
  v93 = v89 + 117;
  LODWORD(pPos.z) = v88 + 307;
  LODWORD(pDir.z) = v88 + 307;
  LOBYTE(v37) = g_bDebugMode;
  LODWORD(pDir.y) = v89 + 323;
  v87 = v89 + 349;
  LODWORD(pPos.x) = v88 + 285;
  LODWORD(pDir.x) = v88 + 285;
  v38 = (*(int ( **)(float *, int *, int *, CCCTData *, _DWORD, int, int))(LODWORD(_this->m_Pool[1941].EndPos.y)
                                                                                   + 28))(
          &_this->m_Pool[1941].EndPos.y,
          &byte_A00534,
          &p_DWORD,
          _this,
          0,
          1,
          v37);
  LOBYTE(v38) = g_bDebugMode;
  (((UIListBox *)&_this->m_Pool[1941].EndPos.y))->UIListBox::GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v38);
  _this->m_Pool[1946].dwReserved[1] = -4;
  (((UIListBox *)&_this->m_Pool[1941].EndPos.y))->UIListBox::GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  (((CCBUI *)&_this->m_Pool[1941].fCircleCentreX))->CCBUI::ShowEffect(v65 + 1, nHeight - 38, nHeight);
  (((CCBUI *)&_this->m_Pool[1941].fCircleCentreX))->CCBUI::SetTargetPos(&pPos, &pDir);
  (((CCBUI *)&_this->m_Pool[1941].fCircleCentreX))->CCBUI::SetSelection(27);
  (((CCBUI *)&_this->m_Pool[1941].fCircleCentreX))->CCBUI::SetCurPlayer(5);
  (((UIListBox *)&_this->m_Pool[1941].EndPos.y))->UIListBox::SetLockSel(23);
  (((UIListBox *)&_this->m_Pool[1941].EndPos.y))->UIListBox::SetColumnHead((int)"Name", 130);
  (((UIListBox *)&_this->m_Pool[1941].EndPos.y))->UIListBox::SetColumnHead((int)&g_pCombatUIData, 38);
  (((UIListBox *)&_this->m_Pool[1941].EndPos.y))->UIListBox::SetColumnHead((int)"Gu", 38);
  (((UIListBox *)&_this->m_Pool[1941].EndPos.y))->UIListBox::SetColumnHead((int)"Price", 50);
  (((CCBUI *)&_this->m_Pool[1941].fCircleCentreX))->CCBUI::VirtualCall(1);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1941].EndPos.y))(&_this->m_Pool[1941].EndPos.y, 0);
  v78 = p_DWORD;
  v79 = v65 + 2;
  v39 = p_DWORD + 256;
  v40 = v65 + 25;
  LOBYTE(_this->m_Pool[1941].fAngleSpeed) = 0;
  v80 = v39;
  v81 = v40;
  p_fCircleEndX = (float *)&_this->m_Pool[1902].fCircleEndX;
  v42 = 12;
  do
  {
    (*(void ( **)(float *, __int16 *, int *, CCCTData *))(*(_DWORD *)p_fCircleEndX + 16))(
      p_fCircleEndX,
      &word_A00552,
      &v78,
      _this);
    LOBYTE(v43) = g_bDebugMode;
    (((UIPushButton *)p_fCircleEndX))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\List_Grid.tga", v43);
    (**(void ( ***)(float *, _DWORD))p_fCircleEndX)((float *)(p_fCircleEndX), (_DWORD)(0));
    p_fCircleEndX += 38;
    v79 = v81;
    v44 = v81 + 23;
    --v42;
    v81 += 23;
  }
  while ( v42 );
  LOBYTE(v44) = g_bDebugMode;
  LODWORD(v45.f) = _this->m_Pool[1954].StartPos.yaw;
  v75[1] = 474;
  v75[0] = 124;
  v76 = 220;
  v77 = 500;
  (*(void ( **)(_inline_tagCam_yaw *, int *, _DWORD *, CCCTData *, char *, int, int))&v45.p->_tail_000[28])(
    &_this->m_Pool[1954].StartPos.yaw,
    &byte_A00555,
    (_DWORD *)(v75),
    _this,
    "UI\\GameMainUI\\Communal\\SortPrice",
    1,
    v44);
  ((void ( *)(_inline_tagCam_yaw *, _DWORD))_this->m_Pool[1954].StartPos.yaw.p->_tail_000[0])(
    &_this->m_Pool[1954].StartPos.yaw,
    0);
  fStartTracePosX = _this->m_Pool[1955].fStartTracePosX;
  v75[0] = v76 + 6;
  v76 += 102;
  v47 = v76;
  LOBYTE(v47) = g_bDebugMode;
  (*(void ( **)(float *, int *, _DWORD *, CCCTData *, char *, int, int))(LODWORD(fStartTracePosX) + 28))(
    &_this->m_Pool[1955].fStartTracePosX,
    &byte_A00556,
    (_DWORD *)(v75),
    _this,
    "UI\\GameMainUI\\Sword\\SortGu",
    1,
    v47);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1955].fStartTracePosX))(
    &_this->m_Pool[1955].fStartTracePosX,
    0);
  fAccelerationTime2 = _this->m_Pool[1957].fAccelerationTime2;
  v75[0] = v76 + 145;
  v76 += 241;
  v49 = v76;
  LOBYTE(v49) = g_bDebugMode;
  (*(void ( **)(float *, int *, _DWORD *, CCCTData *, char *, int, int))(LODWORD(fAccelerationTime2) + 28))(
    &_this->m_Pool[1957].fAccelerationTime2,
    &byte_A00557,
    (_DWORD *)(v75),
    _this,
    "UI\\GameMainUI\\Communal\\SortPrice",
    1,
    v49);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1957].fAccelerationTime2))(
    &_this->m_Pool[1957].fAccelerationTime2,
    0);
  x = _this->m_Pool[1959].EndPos.x;
  v75[0] = v76 + 6;
  v76 += 102;
  v51 = v76;
  LOBYTE(v51) = g_bDebugMode;
  (*(void ( **)(tagCam *, int *, _DWORD *, CCCTData *, char *, int, int))(LODWORD(x) + 28))(
    &_this->m_Pool[1959].EndPos,
    &byte_A00558,
    (_DWORD *)(v75),
    _this,
    "UI\\GameMainUI\\Sword\\SortGu",
    1,
    v51);
  (*(void ( **)(tagCam *, _DWORD))LODWORD(_this->m_Pool[1959].EndPos.x))(&_this->m_Pool[1959].EndPos, 0);
  fStartTracePosY = _this->m_Pool[1878].fStartTracePosY;
  v95 = 93;
  v94 = 43;
  v96 = 731;
  v97 = 111;
  (*(void ( **)(float *, __int16 *, int *, char *, _DWORD, CCCTData *))(LODWORD(fStartTracePosY) + 28))(
    &_this->m_Pool[1878].fStartTracePosY,
    &word_A00552,
    &v94,
    "UI\\Flex\\SmallBar.tga",
    0,
    _this);
  (((CScreenMode *)&_this->m_Pool[1878].fStartTracePosY))->CScreenMode::SetPosition(40,   18);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1878].fStartTracePosY))(
    &_this->m_Pool[1878].fStartTracePosY,
    0);
  LODWORD(v53.f) = _this->m_Pool[1879].EndPos.yaw;
  v95 = 496;
  v94 = 42;
  v96 = 742;
  v97 = 531;
  (*(void ( **)(_inline_tagCam_yaw *, __int16 *, int *, char *, _DWORD, CCCTData *))&v53.p->_tail_000[28])(
    &_this->m_Pool[1879].EndPos.yaw,
    &word_A00552,
    &v94,
    "UI\\Flex\\BigBar.tga",
    0,
    _this);
  (((CScreenMode *)&_this->m_Pool[1879].EndPos.yaw))->CScreenMode::SetPosition(40,   35);
  ((void ( *)(_inline_tagCam_yaw *, _DWORD))_this->m_Pool[1879].EndPos.yaw.p->_tail_000[0])(
    &_this->m_Pool[1879].EndPos.yaw,
    0);
  y = _this->m_Pool[1888].StartPos.y;
  v98[1] = 76;
  v98[0] = 162;
  v99 = 282;
  v100 = 107;
  (*(void ( **)(float *, __int16 *, _DWORD *, CCCTData *))(LODWORD(y) + 16))(
    &_this->m_Pool[1888].StartPos.y,
    &word_A00552,
    (_DWORD *)(v98),
    _this);
  LOBYTE(v55) = g_bDebugMode;
  (((UIPushButton *)&_this->m_Pool[1888].StartPos.y))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\EquipFlag.tga", v55);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1888].StartPos.y))(&_this->m_Pool[1888].StartPos.y, 0);
  v56 = _this->m_Pool[1888].fStartTracePosY;
  v98[0] = v99 + 220;
  v99 += 340;
  (*(void ( **)(float *, __int16 *, _DWORD *, CCCTData *))(LODWORD(v56) + 16))(
    &_this->m_Pool[1888].fStartTracePosY,
    &word_A00552,
    (_DWORD *)(v98),
    _this);
  LOBYTE(v57) = g_bDebugMode;
  (((UIPushButton *)&_this->m_Pool[1888].fStartTracePosY))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\PurgeFlag.tga", v57);
  v58 = (*(int ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1888].fStartTracePosY))(
          &_this->m_Pool[1888].fStartTracePosY,
          0);
  fTimeExpiate = _this->m_Pool[1950].fTimeExpiate;
  LODWORD(_this->m_Pool[1950].fCircleEndZ) = 502;
  LODWORD(_this->m_Pool[1950].fSwingFre) = 322;
  LODWORD(_this->m_Pool[1950].fCircleEndY) = 226;
  LODWORD(_this->m_Pool[1950].fSwing) = 528;
  LOBYTE(v58) = g_bDebugMode;
  (*(void ( **)(float *, int *, float *, CCCTData *, char *, int, int))(LODWORD(fTimeExpiate) + 28))(
    &_this->m_Pool[1950].fTimeExpiate,
    &byte_A00536,
    &_this->m_Pool[1950].fCircleEndY,
    _this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    1,
    v58);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1950].fTimeExpiate))(
    &_this->m_Pool[1950].fTimeExpiate,
    0);
  LODWORD(v60) = LODWORD(_this->m_Pool[1950].fSwingFre) + 150;
  _this->m_Pool[1950].fCircleEndY = v60;
  LODWORD(_this->m_Pool[1950].fSwingFre) = LODWORD(v60) + 96;
  LOBYTE(v61) = g_bDebugMode;
  (*(void ( **)(float *, int *, float *, CCCTData *, char *, int, int))(LODWORD(_this->m_Pool[1952].fStartSpeed)
                                                                                + 28))(
    &_this->m_Pool[1952].fStartSpeed,
    &byte_A00537,
    &_this->m_Pool[1950].fCircleEndY,
    _this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    1,
    v61);
  (*(void ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1952].fStartSpeed))(&_this->m_Pool[1952].fStartSpeed, 0);
  fCircleEndZ = _this->m_Pool[1948].fCircleEndZ;
  v102[1] = 116;
  v102[0] = 552;
  v102[2] = 680;
  v102[3] = 148;
  (*(void ( **)(float *, int *, _DWORD *, CCCTData *))(LODWORD(fCircleEndZ) + 16))(
    &_this->m_Pool[1948].fCircleEndZ,
    &byte_A00527,
    (_DWORD *)(v102),
    _this);
  (((UIScene *)&_this->m_Pool[1948].fCircleEndZ))->UIScene::SetShow(0);
  AllocObject(&_this->m_Pool[1948].fCircleEndZ);
  sprintf(
    (char *const)&_this->m_Pool[0].nTraceRole,
    "%d/%d",
    _this->m_Pool[114].fStartTracePosZ,
    _this->m_Pool[114].fStartTracePosY);
  SetEnable((UICaption *)&_this->m_Pool[1948].fCircleEndZ);
  return (*(int ( **)(float *, _DWORD))LODWORD(_this->m_Pool[1948].fCircleEndZ))(
           &_this->m_Pool[1948].fCircleEndZ,
           0);
}

// 0x004A9870
int UIListBox__todo(int nVal)
{
  int v1; // ecx
  int result; // eax
  signed int v3; // ebp
  int v4; // esi
  UIListBox *v5; // edi
  char *v6; // esi
  int *v7; // eax
  int ListItems; // ebx
  char *v9; // esi
  int *v10; // eax
  int v11; // ebx
  char *v12; // esi
  int *v13; // eax
  int v14; // ebx
  char *v15; // esi
  int *v16; // eax
  int v17; // ebx
  char *v18; // esi
  int *v19; // eax
  int v20; // ebx
  int sel; // [esp+0x10] [ebp-0x4C]
  int pConfig; // [esp+0x14] [ebp-0x48] BYREF
  int v23; // [esp+0x18] [ebp-0x44]
  int v24; // [esp+0x1C] [ebp-0x40]
  _BYTE pOut[12]; // [esp+0x20] [ebp-0x3C] BYREF
  _BYTE v26[12]; // [esp+0x2C] [ebp-0x30] BYREF
  _BYTE v27[12]; // [esp+0x38] [ebp-0x24] BYREF
  _BYTE v28[12]; // [esp+0x44] [ebp-0x18] BYREF
  _BYTE v29[12]; // [esp+0x50] [ebp-0xC] BYREF
  CCBStage *nVala; // [esp+0x60] [ebp+0x4]
  CCBStage *nValb; // [esp+0x60] [ebp+0x4]
  CCBStage *nValc; // [esp+0x60] [ebp+0x4]
  CCBStage *nVald; // [esp+0x60] [ebp+0x4]
  CCBStage *nVale; // [esp+0x60] [ebp+0x4]

  result = nVal;
  v3 = 0;
  v4 = v1;
  pConfig = 0xFFFF;
  v23 = 0;
  v24 = 0;
  switch ( nVal )
  {
    case 0:
      v5 = (UIListBox *)(v1 + 389984);
      sel = *(_DWORD *)(v1 + 390236);
      (((UIListBox *)(v1 + 389984)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(7);
      if ( *(int *)(v4 + 400036) >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(*(void **)(v4 + 400036));
      nVala = (CCBStage *)(v4 + 400040);
      (((CCBStage *)(v4 + 400040)))->CCBStage::Reset();
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v6 = (char *)(v4 + 104);
        do
        {
          v7 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(pOut, v3);
          pConfig = (unsigned long)*v7;
          v23 = (unsigned long)v7[1];
          v24 = (unsigned long)v7[2];
          ListItems = (((UIListBox *)v5))->UIListBox::LoadListItems((char *)(v24 + 4), 0);
          sprintf(v6, (const char *)&dir[20], v23);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(1, ListItems, v6, 0);
          sprintf(v6, (const char *)&dir[20], *(_DWORD *)(v24 + 624));
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(2, ListItems, v6, 0);
          sprintf(v6, (const char *)&dir[20], *(_DWORD *)(v24 + 608) / 2);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(3, ListItems, v6, 0);
          (((CCBStage *)nVala))->CCBStage::GetAlive(&pConfig);
          ++v3;
        }
        while ( v3 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      goto LABEL_31;
    case 1:
      v5 = (UIListBox *)(v1 + 391192);
      sel = *(_DWORD *)(v1 + 391444);
      (((UIListBox *)(v1 + 391192)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(11);
      if ( *(int *)(v4 + 400036) >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(*(void **)(v4 + 400036));
      nValb = (CCBStage *)(v4 + 400040);
      (((CCBStage *)(v4 + 400040)))->CCBStage::Reset();
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v9 = (char *)(v4 + 104);
        do
        {
          v10 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v26, v3);
          pConfig = (unsigned long)*v10;
          v23 = (unsigned long)v10[1];
          v24 = (unsigned long)v10[2];
          v11 = (((UIListBox *)v5))->UIListBox::LoadListItems((char *)(v24 + 4), 0);
          sprintf(v9, (const char *)&dir[20], v23);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(1, v11, v9, 0);
          sprintf(v9, (const char *)&dir[20], *(_DWORD *)(v24 + 624));
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(2, v11, v9, 0);
          sprintf(v9, (const char *)&dir[20], *(_DWORD *)(v24 + 608) / 2);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(3, v11, v9, 0);
          (((CCBStage *)nValb))->CCBStage::GetAlive(&pConfig);
          ++v3;
        }
        while ( v3 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      goto LABEL_31;
    case 2:
      v5 = (UIListBox *)(v1 + 392400);
      sel = *(_DWORD *)(v1 + 392652);
      (((UIListBox *)(v1 + 392400)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(12);
      if ( *(int *)(v4 + 400036) >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(*(void **)(v4 + 400036));
      nValc = (CCBStage *)(v4 + 400040);
      (((CCBStage *)(v4 + 400040)))->CCBStage::Reset();
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v12 = (char *)(v4 + 104);
        do
        {
          v13 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v27, v3);
          pConfig = (unsigned long)*v13;
          v23 = (unsigned long)v13[1];
          v24 = (unsigned long)v13[2];
          v14 = (((UIListBox *)v5))->UIListBox::LoadListItems((char *)(v24 + 4), 0);
          sprintf(v12, (const char *)&dir[20], v23);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(1, v14, v12, 0);
          sprintf(v12, (const char *)&dir[20], *(_DWORD *)(v24 + 624));
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(2, v14, v12, 0);
          sprintf(v12, (const char *)&dir[20], *(_DWORD *)(v24 + 608) / 2);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(3, v14, v12, 0);
          (((CCBStage *)nValc))->CCBStage::GetAlive(&pConfig);
          ++v3;
        }
        while ( v3 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      goto LABEL_31;
    case 3:
      v5 = (UIListBox *)(v1 + 393608);
      sel = *(_DWORD *)(v1 + 393860);
      (((UIListBox *)(v1 + 393608)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(13);
      if ( *(int *)(v4 + 400036) >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(*(void **)(v4 + 400036));
      nVald = (CCBStage *)(v4 + 400040);
      (((CCBStage *)(v4 + 400040)))->CCBStage::Reset();
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v15 = (char *)(v4 + 104);
        do
        {
          v16 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v28, v3);
          pConfig = (unsigned long)*v16;
          v23 = (unsigned long)v16[1];
          v24 = (unsigned long)v16[2];
          v17 = (((UIListBox *)v5))->UIListBox::LoadListItems((char *)(v24 + 4), 0);
          sprintf(v15, (const char *)&dir[20], v23);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(1, v17, v15, 0);
          sprintf(v15, (const char *)&dir[20], *(_DWORD *)(v24 + 624));
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(2, v17, v15, 0);
          sprintf(v15, (const char *)&dir[20], *(_DWORD *)(v24 + 608) / 2);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(3, v17, v15, 0);
          (((CCBStage *)nVald))->CCBStage::GetAlive(&pConfig);
          ++v3;
        }
        while ( v3 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
      goto LABEL_31;
    case 4:
      v5 = (UIListBox *)(v1 + 394816);
      sel = *(_DWORD *)(v1 + 395068);
      (((UIListBox *)(v1 + 394816)))->UIListBox::ClearAll();
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::CheckValid(9);
      if ( *(int *)(v4 + 400036) >= 0 )
        (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(*(void **)(v4 + 400036));
      nVale = (CCBStage *)(v4 + 400040);
      (((CCBStage *)(v4 + 400040)))->CCBStage::Reset();
      if ( (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() > 0 )
      {
        v18 = (char *)(v4 + 104);
        do
        {
          v19 = (int *)(((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetAt(v29, v3);
          pConfig = (unsigned long)*v19;
          v23 = (unsigned long)v19[1];
          v24 = (unsigned long)v19[2];
          v20 = (((UIListBox *)v5))->UIListBox::LoadListItems((char *)(v24 + 4), 0);
          sprintf(v18, (const char *)&dir[20], v23);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(1, v20, v18, 0);
          sprintf(v18, (const char *)&dir[20], *(_DWORD *)(v24 + 624));
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(2, v20, v18, 0);
          sprintf(v18, (const char *)&dir[20], *(_DWORD *)(v24 + 608) / 2);
          (((UIListBox *)v5))->UIListBox::SetMouseMoveSel(3, v20, v18, 0);
          (((CCBStage *)nVale))->CCBStage::GetAlive(&pConfig);
          ++v3;
        }
        while ( v3 < (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::GetSize() );
      }
LABEL_31:
      (((UIListBox *)v5))->UIListBox::SetSel(sel);
      break;
    default:
      return result;
  }
  return result;
}

// 0x004A9ED0
int CCBCamControl_ShowAllSlots(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // edi
  int result; // eax

  v2 = v1;
  v3 = 5;
  v4 = v1 + 383468;
  do
  {
    sub_445E50(v4);
    v4 += 344;
    --v3;
  }
  while ( v3 );
  result = sub_445E50(v2 + 344 * nVal + 383468);
  switch ( nVal )
  {
    case 0:
      UIListBox__todo(0);
      (**(void ( ***)(int, int))(v2 + 389984))((int)(v2 + 389984), (int)(1));
      (((UIListBox *)(v2 + 389984)))->UIListBox::GetItem();
      (((UIListBox *)(v2 + 389984)))->UIListBox::GetItem();
      (((UIListBox *)(v2 + 391192)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 391192))((int)(v2 + 391192), (_DWORD)(0));
      (((UIListBox *)(v2 + 392400)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 392400))((int)(v2 + 392400), (_DWORD)(0));
      goto LABEL_7;
    case 1:
      (((UIListBox *)(v2 + 389984)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 389984))((int)(v2 + 389984), (_DWORD)(0));
      UIListBox__todo(1);
      (**(void ( ***)(int, int))(v2 + 391192))((int)(v2 + 391192), (int)(1));
      (((UIListBox *)(v2 + 391192)))->UIListBox::GetItem();
      (((UIListBox *)(v2 + 391192)))->UIListBox::GetItem();
      (((UIListBox *)(v2 + 392400)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 392400))((int)(v2 + 392400), (_DWORD)(0));
      (((UIListBox *)(v2 + 393608)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 393608))((int)(v2 + 393608), (_DWORD)(0));
      goto LABEL_9;
    case 2:
      (((UIListBox *)(v2 + 389984)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 389984))((int)(v2 + 389984), (_DWORD)(0));
      (((UIListBox *)(v2 + 391192)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 391192))((int)(v2 + 391192), (_DWORD)(0));
      UIListBox__todo(2);
      (**(void ( ***)(int, int))(v2 + 392400))((int)(v2 + 392400), (int)(1));
      (((UIListBox *)(v2 + 392400)))->UIListBox::GetItem();
      (((UIListBox *)(v2 + 392400)))->UIListBox::GetItem();
LABEL_7:
      (((UIListBox *)(v2 + 393608)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 393608))((int)(v2 + 393608), (_DWORD)(0));
      (((UIListBox *)(v2 + 394816)))->UIListBox::ClearAll();
      result = (**(int ( ***)(int, _DWORD))(v2 + 394816))((int)(v2 + 394816), (_DWORD)(0));
      *(_DWORD *)(v2 + 21848) = nVal;
      return result;
    case 3:
      (((UIListBox *)(v2 + 389984)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 389984))((int)(v2 + 389984), (_DWORD)(0));
      (((UIListBox *)(v2 + 391192)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 391192))((int)(v2 + 391192), (_DWORD)(0));
      (((UIListBox *)(v2 + 392400)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 392400))((int)(v2 + 392400), (_DWORD)(0));
      UIListBox__todo(3);
      (**(void ( ***)(int, int))(v2 + 393608))((int)(v2 + 393608), (int)(1));
      (((UIListBox *)(v2 + 393608)))->UIListBox::GetItem();
      (((UIListBox *)(v2 + 393608)))->UIListBox::GetItem();
LABEL_9:
      (((UIListBox *)(v2 + 394816)))->UIListBox::ClearAll();
      result = (**(int ( ***)(int, _DWORD))(v2 + 394816))((int)(v2 + 394816), (_DWORD)(0));
      *(_DWORD *)(v2 + 21848) = nVal;
      return result;
    case 4:
      (((UIListBox *)(v2 + 389984)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 389984))((int)(v2 + 389984), (_DWORD)(0));
      (((UIListBox *)(v2 + 391192)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 391192))((int)(v2 + 391192), (_DWORD)(0));
      (((UIListBox *)(v2 + 392400)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 392400))((int)(v2 + 392400), (_DWORD)(0));
      (((UIListBox *)(v2 + 393608)))->UIListBox::ClearAll();
      (**(void ( ***)(int, _DWORD))(v2 + 393608))((int)(v2 + 393608), (_DWORD)(0));
      UIListBox__todo(4);
      (**(void ( ***)(int, int))(v2 + 394816))((int)(v2 + 394816), (int)(1));
      (((UIListBox *)(v2 + 394816)))->UIListBox::GetItem();
      result = (((UIListBox *)(v2 + 394816)))->UIListBox::GetItem();
      goto LABEL_11;
    default:
LABEL_11:
      *(_DWORD *)(v2 + 21848) = nVal;
      return result;
  }
}

// 0x004AA1B0
int UIListBox_ResetAllListBoxes(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v4; // [esp+0x0] [ebp-0x4]

  v2 = v1;
  UIListBox_ShowSlotUI(v4);
  *(_DWORD *)(v2 + 520) = 0;
  *(_DWORD *)(v2 + 516) = 0;
  *(_DWORD *)(v2 + 536) = 0;
  *(_DWORD *)(v2 + 532) = 0;
  *(_DWORD *)(v2 + 528) = 0;
  *(_DWORD *)(v2 + 524) = 0;
  *(_DWORD *)(v2 + 544) = 0;
  *(_DWORD *)(v2 + 540) = 0;
  *(_DWORD *)(v2 + 23448) = 0;
  (((UIListBox *)(v2 + 389984)))->UIListBox::ClearAll();
  (((UIListBox *)(v2 + 391192)))->UIListBox::ClearAll();
  (((UIListBox *)(v2 + 392400)))->UIListBox::ClearAll();
  (((UIListBox *)(v2 + 393608)))->UIListBox::ClearAll();
  return (((UIListBox *)(v2 + 394816)))->UIListBox::ClearAll();
}

// 0x004AA230
int UIListBox_ShowSlotUI(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // ebx
  int v4; // ebp
  int v5; // esi
  int result; // eax
  int *v7; // esi
  int v8; // ebp
  int v9; // eax
  int v10; // ecx
  int pConfig; // [esp+0x10] [ebp-0xC] BYREF
  int v12; // [esp+0x14] [ebp-0x8]
  int SkillNum; // [esp+0x18] [ebp-0x4]

  v2 = v1;
  v3 = 5;
  v4 = v1 + 383468;
  v5 = v1 + 383468;
  do
  {
    sub_445E50(v5);
    v5 += 344;
    --v3;
  }
  while ( v3 );
  sub_445E50(v4);
  result = (((UIListBox *)(v2 + 396024)))->UIListBox::GetItemData();
  if ( result > 0 )
  {
    v12 = 0;
    SkillNum = 0;
    pConfig = 0xFFFF;
    v7 = (int *)(v2 + 21864);
    v8 = result;
    do
    {
      v9 = *(v7 - 1);
      v12 = (unsigned long)*v7;
      pConfig = v9;
      SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v9);
      (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&pConfig);
      UIListBox__todo(v7[1]);
      v10 = *(_DWORD *)(v2 + 23444);
      *(_DWORD *)(v2 + 23448) = 0;
      sprintf((char *const)(v2 + 104), "%d/%d", 0, v10);
      SetEnable((UICaption *)(v2 + 397552));
      v7 += 4;
      --v8;
    }
    while ( v8 );
    (((UIListBox *)(v2 + 396024)))->UIListBox::ClearAll();
    result = 0;
    memset((void *)(v2 + 21860), 0, 0x630u);
  }
  return result;
}

// 0x004AA320
int UIListBox_InsertUIListBox(int nVal)
{
  int result; // eax
  int v2; // ecx
  int v3; // esi
  int ListItems; // ebp
  void *v5; // eax
  int *TargetRole; // eax
  int v7; // eax
  CScreenMode *v8; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  CScreenMode *Instance; // eax
  int v13; // eax
  int v14; // edx
  char v15; // cl
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  _DWORD *i; // eax
  _DWORD *v22; // eax
  int v23; // eax
  int v24; // ecx
  const void *v25; // [esp-0x8] [ebp-0x30]
  const void *v26; // [esp-0x8] [ebp-0x30]
  _DWORD *v27; // [esp+0xC] [ebp-0x1C]
  int p_DWORD; // [esp+0x10] [ebp-0x18] BYREF
  int v29; // [esp+0x14] [ebp-0x14]
  int v30; // [esp+0x18] [ebp-0x10]
  char pOut[12]; // [esp+0x1C] [ebp-0xC] BYREF

  v3 = v2;
  ListItems = 0;
  if ( *(int *)(v2 + 21844) >= 0 )
  {
    v5 = (void *)*(void **)(v2 + 400036);
    p_DWORD = 0xFFFF;
    v29 = 0;
    v30 = 0;
    if ( (int)v5 >= 0 )
      (((PtrArray *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->PtrArray::Insert(v5);
    TargetRole = (int *)(((CCBAI *)(v3 + 400040)))->CCBAI::GetTargetRole(pOut);
    p_DWORD = (unsigned long)*TargetRole;
    v29 = (unsigned long)TargetRole[1];
    v30 = (unsigned long)TargetRole[2];
    v7 = *(_DWORD *)(v30 + 624);
    if ( v7 > 0 )
    {
      v9 = *(_DWORD *)(v3 + 23448);
      v10 = *(_DWORD *)(v3 + 23444);
      v11 = v9 + v7;
      *(_DWORD *)(v3 + 23448) = v11;
      if ( v11 <= v10 )
      {
        sprintf((char *const)(v3 + 104), "%d/%d", v11, v10);
        SetEnable((UICaption *)(v3 + 397552));
        v13 = v30;
        if ( *(_BYTE *)(v30 + 612) == 11 )
        {
          v14 = *(_DWORD *)(v3 + 524);
          ++*(_DWORD *)(v3 + 520);
          *(_DWORD *)(v3 + 524) = *(__int16 *)(v13 + 650) + v14;
        }
        v15 = *(_BYTE *)(v13 + 612);
        if ( v15 == 7 || v15 == 8 || v15 == 9 || v15 == 10 )
        {
          ++*(_DWORD *)(v3 + 516);
          if ( *(_BYTE *)(v13 + 612) == 10 )
          {
            v16 = *(_DWORD *)(v3 + 532);
            *(_DWORD *)(v3 + 528) += *(__int16 *)(v13 + 650);
            v17 = *(__int16 *)(v13 + 652) + v16;
            v18 = *(_DWORD *)(v3 + 540) + 1;
            *(_DWORD *)(v3 + 532) = v17;
            *(_DWORD *)(v3 + 540) = v18;
          }
          else
          {
            v19 = *(__int16 *)(v13 + 652);
            v20 = *(_DWORD *)(v3 + 544) + 1;
            *(_DWORD *)(v3 + 536) += v19;
            *(_DWORD *)(v3 + 544) = v20;
          }
        }
        if ( (((UIListBox *)(v3 + 396024)))->UIListBox::GetItemData() <= 0 )
        {
LABEL_22:
          ListItems = (((UIListBox *)(v3 + 396024)))->UIListBox::LoadListItems((char *)(v30 + 4), 0);
          v22 = (_DWORD *)(16 * ListItems + v3);
          v22[5465] = p_DWORD;
          ++v22[5466];
          v22[5467] = nVal;
          *(_DWORD *)(16 * (ListItems + 1367) + v3) = *(_DWORD *)(v3 + 21844);
          v23 = (unsigned long)v22[5466];
        }
        else
        {
          for ( i = (_DWORD *)(v3 + 21860); *i != p_DWORD; i = v27 )
          {
            ++ListItems;
            v27 = (_DWORD *)(i + 4);
            if ( ListItems >= (((UIListBox *)(v3 + 396024)))->UIListBox::GetItemData() )
              goto LABEL_22;
          }
          v24 = *(_DWORD *)(16 * ListItems + v3 + 21864) + 1;
          *(_DWORD *)(16 * ListItems + v3 + 21864) = v24;
          v23 = v24;
        }
        sprintf((char *const)(v3 + 104), (const char *)&dir[20], v23);
        (((UIListBox *)(v3 + 396024)))->UIListBox::SetMouseMoveSel(1, ListItems, (char *)(v3 + 104), 0);
        sprintf((char *const)(v3 + 104), (const char *)&dir[20], *(_DWORD *)(v30 + 624));
        (((UIListBox *)(v3 + 396024)))->UIListBox::SetMouseMoveSel(2, ListItems, (char *)(v3 + 104), 0);
        sprintf((char *const)(v3 + 104), (const char *)&dir[20], *(_DWORD *)(v30 + 608) / 2);
        (((UIListBox *)(v3 + 396024)))->UIListBox::SetMouseMoveSel(3, ListItems, (char *)(v3 + 104), 0);
        v29 = 1;
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(&p_DWORD);
        return UIListBox__todo(nVal);
      }
      else
      {
        *(_DWORD *)(v3 + 23448) = v9;
        sprintf((char *const)(v3 + 104), "\\n\\n       %s", (const char *)&dword_DC913C);
        SetEnable((UICaption *)(v3 + 400536));
        (((UIRoleSelect *)(v3 + 400080)))->UIRoleSelect::SetByte(1);
        v26 = (const void *)off_5CF1F0;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v26, 1);
      }
    }
    else
    {
      sprintf((char *const)(v3 + 104), "\\n   %s\\n   %s", (const char *)&dword_DCEA3C, (const char *)&dword_DD423C);
      SetEnable((UICaption *)(v3 + 400536));
      (((UIRoleSelect *)(v3 + 400080)))->UIRoleSelect::SetByte(1);
      v25 = (const void *)off_5CF1F0;
      v8 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v8))->CScreenMode::AudioSetPosition(v25, 1);
    }
  }
  return result;
}

// 0x004AA680
int UIListBox_ProcessListInput(int nVal)
{
  int result; // eax
  int v2; // ecx
  int v3; // ebx
  UIListBox *v4; // edi
  int *v5; // ebp
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  char *v10; // esi
  int v11; // eax
  char v12; // cl
  int ItemData; // ebp
  _DWORD *v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // ebx
  int ListItems; // ebp
  bool v19; // zf
  _DWORD *v20; // [esp+0x10] [ebp-0x14]
  int v21; // [esp+0x10] [ebp-0x14]
  void *v22; // [esp+0x14] [ebp-0x10]
  int pConfig; // [esp+0x18] [ebp-0xC] BYREF
  int v24; // [esp+0x1C] [ebp-0x8]
  int SkillNum; // [esp+0x20] [ebp-0x4]
  int nVala; // [esp+0x28] [ebp+0x4]
  _DWORD *nValb; // [esp+0x28] [ebp+0x4]

  v3 = v2;
  if ( nVal >= 0 )
  {
    v4 = (UIListBox *)(v2 + 396024);
    result = (((UIListBox *)(v2 + 396024)))->UIListBox::GetItemData();
    if ( nVal < result )
    {
      pConfig = 0xFFFF;
      v24 = 0;
      SkillNum = 0;
      result = (((UIListBox *)(v3 + 396024)))->UIListBox::GetItemData();
      if ( result > 0 )
      {
        v5 = (int *)(v3 + 16 * nVal);
        v24 = 1;
        pConfig = (unsigned long)v5[5465];
        SkillNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(pConfig);
        (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetAlive(&pConfig);
        UIListBox__todo(v5[5467]);
        CCBCamControl_ShowAllSlots(*(_DWORD *)(v3 + 21848));
        v6 = SkillNum;
        switch ( *(_BYTE *)(SkillNum + 612) )
        {
          case 7:
          case 8:
          case 9:
            v7 = *(_DWORD *)(v3 + 544) - 1;
            --*(_DWORD *)(v3 + 516);
            *(_DWORD *)(v3 + 544) = v7;
            break;
          case 0xA:
            v8 = *(_DWORD *)(v3 + 540) - 1;
            --*(_DWORD *)(v3 + 516);
            *(_DWORD *)(v3 + 540) = v8;
            break;
          case 0xB:
            --*(_DWORD *)(v3 + 520);
            break;
          default:
            break;
        }
        v9 = *(_DWORD *)(v3 + 23448) - *(_DWORD *)(v6 + 624);
        *(_DWORD *)(v3 + 23448) = v9;
        if ( v9 <= 0 )
          *(_DWORD *)(v3 + 23448) = 0;
        v10 = (char *)(v3 + 104);
        sprintf((char *const)(v3 + 104), "%d/%d", *(_DWORD *)(v3 + 23448), *(_DWORD *)(v3 + 23444));
        SetEnable((UICaption *)(v3 + 397552));
        v11 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(v5[5465]);
        if ( *(_BYTE *)(v11 + 612) == 11 )
          *(_DWORD *)(v3 + 524) -= *(__int16 *)(v11 + 650);
        v12 = *(_BYTE *)(v11 + 612);
        if ( v12 == 7 || v12 == 8 || v12 == 9 || v12 == 10 )
        {
          if ( v12 == 10 )
          {
            *(_DWORD *)(v3 + 528) -= *(__int16 *)(v11 + 650);
            *(_DWORD *)(v3 + 532) -= *(__int16 *)(v11 + 652);
          }
          else
          {
            *(_DWORD *)(v3 + 536) -= *(__int16 *)(v11 + 652);
          }
        }
        --v5[5466];
        ItemData = (((UIListBox *)(v3 + 396024)))->UIListBox::GetItemData();
        nVala = ItemData;
        (((UIListBox *)(v3 + 396024)))->UIListBox::ClearAll();
        v14 = (_DWORD *)(v3 + 21860);
        v15 = 0;
        v22 = (void *)(v3 + 21860);
        v20 = (_DWORD *)(v3 + 21860);
        do
        {
          if ( (int)v14[1] <= 0 && *v14 )
          {
            if ( v15 < ItemData )
            {
              v16 = ItemData - v15;
              do
              {
                *v14 = v14[4];
                v14[1] = (unsigned long)v14[5];
                v14[2] = (unsigned long)v14[6];
                v14 += 4;
                --v16;
              }
              while ( v16 );
              ItemData = nVala;
              v14 = (_DWORD *)v20;
            }
            nVala = --ItemData;
          }
          ++v15;
          v14 += 4;
          v20 = (_DWORD *)v14;
        }
        while ( v15 < 99 );
        if ( ItemData > 0 )
        {
          v21 = ItemData;
          nValb = (_DWORD *)(v3 + 21864);
          do
          {
            v17 = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*(nValb - 1));
            ListItems = (((UIListBox *)v4))->UIListBox::LoadListItems((char *)(v17 + 4), 0);
            sprintf(v10, (const char *)&dir[20], *nValb);
            (((UIListBox *)v4))->UIListBox::SetMouseMoveSel(1, ListItems, v10, 0);
            sprintf(v10, (const char *)&dir[20], *(_DWORD *)(v17 + 624));
            (((UIListBox *)v4))->UIListBox::SetMouseMoveSel(2, ListItems, v10, 0);
            sprintf(v10, (const char *)&dir[20], *(_DWORD *)(v17 + 608) / 2);
            (((UIListBox *)v4))->UIListBox::SetMouseMoveSel(3, ListItems, v10, 0);
            v19 = v21 == 1;
            nValb += 4;
            --v21;
          }
          while ( !v19 );
        }
        result = (((UIListBox *)v4))->UIListBox::GetItemData();
        if ( result <= 0 )
        {
          (((UIListBox *)v4))->UIListBox::ClearAll();
          result = 0;
          memset(v22, 0, 0x630u);
        }
      }
    }
  }
  return result;
}

// 0x004AB5E0
int SaleUI_InitColumnWidths(int nVal)
{
  _DWORD *v1; // ecx
  int result; // eax

  result = 90;
  v1[95804] = 70;
  v1[95807] = 70;
  v1[95803] = 40;
  v1[95805] = 60;
  v1[95806] = 90;
  v1[95808] = 110;
  v1[95809] = 90;
  v1[95810] = 120;
  v1[95811] = 90;
  v1[95812] = 130;
  v1[95813] = 95;
  v1[95814] = 145;
  v1[95815] = 110;
  v1[95816] = 160;
  v1[95817] = 120;
  v1[95818] = 185;
  v1[95819] = 140;
  v1[95820] = 200;
  v1[95821] = 150;
  v1[95822] = 220;
  v1[95823] = 205;
  v1[95824] = 265;
  return result;
}

// 0x004AB6B0
int EquipUI_InitEquipUI(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  int *v3; // edi
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edx
  int v18; // edi
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // edx
  int v28; // edx
  int v29; // edx
  int v30; // eax
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // edx
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int v38; // edx
  int v39; // edx
  int v40; // edx
  int v41; // eax
  int v42; // edx
  int v43; // edx
  int v44; // eax
  int v45; // edx
  int v46; // edx
  int v47; // eax
  int v48; // edx
  int v49; // edx
  int v50; // eax
  int v51; // edx
  int v52; // edx
  int v53; // eax
  int v54; // edx
  int v55; // eax
  int v56; // eax
  int v57; // edx
  int v58; // edx
  int v59; // edx
  int v60; // edx
  int v61; // edx
  int v62; // edx
  int v63; // edx
  int v64; // edx
  int v65; // ecx
  int v66; // eax
  int v67; // ecx
  int RoleNum; // edi
  signed int v69; // esi
  int PropertyByIndex; // eax
  _BYTE *v71; // eax
  int v72; // eax
  int result; // eax
  int v74; // [esp+0x2B4] [ebp-E8h]
  int v75; // [esp+0x2B4] [ebp-E8h]
  void *v76; // [esp+0x2B4] [ebp-E8h]
  int v77; // [esp+0x2B4] [ebp-E8h]
  int v78; // [esp+0x2B8] [ebp-E4h]
  char v79; // [esp+0x2BC] [ebp-E0h]
  int v80; // [esp+0x2C0] [ebp-DCh]
  int nVal5; // [esp+0x2C4] [ebp-D8h]
  int nVal5a; // [esp+0x2C4] [ebp-D8h]
  unsigned __int8 a8[4]; // [esp+0x2C8] [ebp-D4h] BYREF
  int v84; // [esp+0x2CC] [ebp-D0h]
  int v85; // [esp+0x2D0] [ebp-CCh]
  int v86; // [esp+0x2D4] [ebp-C8h]
  int v87; // [esp+0x2D8] [ebp-C4h] BYREF
  int v88; // [esp+0x2DC] [ebp-C0h]
  int v89; // [esp+0x2E0] [ebp-BCh]
  int v90; // [esp+0x2E4] [ebp-B8h]
  int v91; // [esp+0x2E8] [ebp-B4h] BYREF
  int v92; // [esp+0x2EC] [ebp-B0h]
  int v93; // [esp+0x2F0] [ebp-ACh]
  int v94; // [esp+0x2F4] [ebp-A8h]
  int v95; // [esp+0x2F8] [ebp-A4h] BYREF
  int v96; // [esp+0x2FC] [ebp-A0h]
  int v97; // [esp+0x300] [ebp-0x9C]
  int v98; // [esp+0x304] [ebp-0x98]
  int v99; // [esp+0x308] [ebp-0x94]
  int v100; // [esp+0x30C] [ebp-0x90]
  int v101; // [esp+0x310] [ebp-0x8C]
  int v102; // [esp+0x314] [ebp-0x88]
  int v103; // [esp+0x318] [ebp-0x84] BYREF
  int v104; // [esp+0x31C] [ebp-0x80]
  int v105; // [esp+0x320] [ebp-0x7C]
  int v106; // [esp+0x324] [ebp-0x78]
  int v107; // [esp+0x328] [ebp-0x74]
  _DWORD v108[2]; // [esp+0x32C] [ebp-0x70] BYREF
  int v109; // [esp+0x334] [ebp-0x68]
  int v110; // [esp+0x338] [ebp-0x64]
  _DWORD v111[4]; // [esp+0x33C] [ebp-0x60] BYREF
  _DWORD v112[4]; // [esp+0x34C] [ebp-0x50] BYREF
  int v113; // [esp+0x35C] [ebp-0x40] BYREF
  int v114; // [esp+0x360] [ebp-0x3C]
  int v115; // [esp+0x364] [ebp-0x38]
  int v116; // [esp+0x368] [ebp-0x34]
  _DWORD v117[4]; // [esp+0x36C] [ebp-0x30] BYREF
  _DWORD v118[4]; // [esp+0x37C] [ebp-0x20] BYREF
  _DWORD v119[4]; // [esp+0x38C] [ebp-0x10] BYREF

  v2 = v1;
  v3 = (int *)(v1 + 72);
  *(_DWORD *)(v1 + 76) = 0;
  *(_DWORD *)(v1 + 72) = 0;
  *(_DWORD *)(v1 + 80) = *(_DWORD *)(v1 + 88);
  *(_DWORD *)(v1 + 84) = *(_DWORD *)(v1 + 92);
  (((UIListBox *)v1))->UIListBox::SetSelTexture(-1, *(_DWORD *)(v1 + 72), *(_DWORD *)(v1 + 76), *(_DWORD *)(v1 + 80), *(_DWORD *)(v1 + 84));
  v4 = *(_DWORD *)(v2 + 76) + 44;
  v108[0] = (unsigned long)(*v3 + 784);
  v108[1] = v4;
  v109 = v108[0] + 17;
  v110 = v4 + 526;
  (*(void ( **)(int, int, _DWORD *, int))(*(_DWORD *)(v2 + 23456) + 16))(v2 + 23456, 161, (_DWORD *)(v108), v2);
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)(v2 + 23456)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Frame_Line.tga", v5);
  v6 = *(_DWORD *)(v2 + 23608);
  v95 = v109 - 205;
  v97 = v109 - 205 + 203;
  v96 = 0;
  v98 = 64;
  (*(void ( **)(int, int, int *, int))(v6 + 16))(v2 + 23608, 161, &v95, v2);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)(v2 + 23608)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\TimeMoney.tga", v7);
  v8 = *(_DWORD *)(v2 + 27632);
  v96 = -4;
  v95 = 618;
  v97 = 738;
  v98 = 28;
  (*(void ( **)(int, int, int *, int))(v8 + 16))(v2 + 27632, 161, &v95, v2);
  (((UIScene *)(v2 + 27632)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 27632));
  v9 = *(_DWORD *)(v2 + 27480);
  v96 = 16;
  v95 = 668;
  v97 = 748;
  v98 = 48;
  (*(void ( **)(int, int, int *, int))(v9 + 16))(v2 + 27480, 161, &v95, v2);
  (((UIScene *)(v2 + 27480)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 27480));
  SystemUI_LayoutWidgets(v74);
  v11 = *(_DWORD *)(v2 + 76) + 2;
  v112[0] = (unsigned long)(*v3 + 260);
  v10 = v112[0];
  *(_WORD *)(v2 + 179500) = 58;
  v112[2] = v10 + 256;
  v10 += 4;
  v112[1] = v11;
  *(_DWORD *)(v2 + 179472) = v11;
  *(_DWORD *)(v2 + 179468) = v10;
  *(_WORD *)(v2 + 179502) = v10;
  v12 = *(_DWORD *)(v2 + 179468);
  v112[3] = v11 + 534;
  *(_DWORD *)(v2 + 179476) = v12 + 218;
  *(_DWORD *)(v2 + 179480) = *(_DWORD *)(v2 + 179472) + 356;
  *(_DWORD *)(v2 + 179484) = *(_DWORD *)(v2 + 179468);
  *(_DWORD *)(v2 + 179488) = *(_DWORD *)(v2 + 179472);
  *(_DWORD *)(v2 + 179492) = *(_DWORD *)(v2 + 179476);
  *(_DWORD *)(v2 + 179496) = *(_DWORD *)(v2 + 179480);
  v13 = (*(int ( **)(int, int *, int, int))(*(_DWORD *)(v2 + 178804) + 16))(
          v2 + 178804,
          &dword_A00500,
          v2 + 179468,
          v2);
  LOBYTE(v13) = g_bDebugMode;
  (((UIPushButton *)(v2 + 178804)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\SwordRemark.tga", v13);
  *(_DWORD *)(v2 + 179456) = *(_DWORD *)(v2 + 179472) + 36;
  v14 = *(_DWORD *)(v2 + 179468) + 16;
  *(_DWORD *)(v2 + 179452) = v14;
  *(_DWORD *)(v2 + 179460) = v14 + 196;
  *(_DWORD *)(v2 + 179464) = *(_DWORD *)(v2 + 179456) + 326;
  (*(void ( **)(int, int *, int, int))(*(_DWORD *)(v2 + 178956) + 16))(
    v2 + 178956,
    &dword_A00500,
    v2 + 179452,
    v2);
  (((UIScene *)(v2 + 178956)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 178956));
  SetEnable((UICaption *)(v2 + 178956));
  (*(void ( **)(int, int *, _DWORD *, int))(*(_DWORD *)(v2 + 178652) + 16))(
    v2 + 178652,
    &dword_A00500,
    (_DWORD *)(v112),
    v2);
  LOBYTE(v15) = g_bDebugMode;
  (((UIPushButton *)(v2 + 178652)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\SwordFrame.tga", v15);
  v16 = *(_DWORD *)(v2 + 177580);
  v118[1] = 10;
  v118[0] = 470;
  v118[2] = 502;
  v118[3] = 42;
  (*(void ( **)(int, int *, _DWORD *, int))(v16 + 16))(v2 + 177580, &dword_A00510, (_DWORD *)(v118), v2);
  LOBYTE(v17) = g_bDebugMode;
  (((UIPushButton *)(v2 + 177580)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\Sword_Feng.tga", v17);
  v18 = (unsigned long)*v3;
  v19 = *(_DWORD *)(v2 + 177428);
  v114 = *(_DWORD *)(v2 + 76) + 16;
  v116 = v114 + 32;
  v113 = v18 + 342;
  v115 = v18 + 470;
  (*(void ( **)(int, __int16 *, int *, int))(v19 + 16))(v2 + 177428, &word_A00572, &v113, v2);
  (((UIScene *)(v2 + 177428)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 177428));
  v20 = *(_DWORD *)(v2 + 177732);
  v104 = 48;
  v103 = 672;
  v105 = 784;
  v106 = 160;
  (*(void ( **)(int, int *, int *, int))(v20 + 16))(v2 + 177732, &byte_A00541, &v103, v2);
  (((UIScene *)(v2 + 177732)))->UIScene::SetShow(0);
  LOBYTE(v21) = g_bDebugMode;
  (((UIPushButton *)(v2 + 177732)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\Longjingshi.tga", v21);
  LOBYTE(v22) = g_bDebugMode;
  v23 = *(_DWORD *)(v2 + 179108);
  v117[1] = 28;
  v117[0] = 506;
  v117[2] = 619;
  v117[3] = 100;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v23 + 28))(
    v2 + 179108,
    &byte_A00571,
    (_DWORD *)(v117),
    v2,
    "UI\\GameMainUI\\Sword\\yjfx",
    1,
    v22);
  g_bUIWnd_DE625A = 0;
  (**(void ( ***)(int, _DWORD))(v2 + 179108))((int)(v2 + 179108), (_DWORD)(0));
  SaleUI_InitColumnWidths(v75);
  v24 = *(_DWORD *)(v2 + 177884);
  v119[1] = 131;
  v119[0] = 690;
  v119[2] = 795;
  v119[3] = 519;
  (*(void ( **)(int, int *, _DWORD *, int))(v24 + 16))(v2 + 177884, &dword_A00500, (_DWORD *)(v119), v2);
  (((UIScene *)(v2 + 177884)))->UIScene::SetShow(0);
  LOBYTE(v25) = g_bDebugMode;
  (((UIPushButton *)(v2 + 177884)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\wulingControl.tga", v25);
  LOBYTE(v26) = g_bDebugMode;
  v27 = *(_DWORD *)(v2 + 181988);
  v84 = 146;
  *(_DWORD *)a8 = 694;
  v85 = 737;
  v86 = 197;
  (*(void ( **)(int, int *, unsigned __int8 *, int, char *, _DWORD, int))(v27 + 28))(
    v2 + 181988,
    &byte_A00542,
    a8,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\shui_lunar",
    0,
    v26);
  (*(void ( **)(int, int *, unsigned __int8 *, int))(*(_DWORD *)(v2 + 183708) + 16))(
    v2 + 183708,
    &byte_A00517,
    a8,
    v2);
  LOBYTE(v28) = g_bDebugMode;
  (((UIPushButton *)(v2 + 183708)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\shui_lunar_over.tga", v28);
  (**(void ( ***)(int, _DWORD))(v2 + 183708))((int)(v2 + 183708), (_DWORD)(0));
  v29 = *(_DWORD *)(v2 + 179508);
  *(_DWORD *)a8 = v85 - 7;
  v87 = v85 - 7;
  v85 = v85 - 7 + 43;
  v89 = v85;
  v88 = v84 + 1;
  v30 = v84 + 52;
  v90 = v84 + 52;
  LOBYTE(v30) = g_bDebugMode;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD, int))(v29 + 28))(
    v2 + 179508,
    &byte_A00547,
    &v87,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\shui_Positive",
    0,
    v30);
  (*(void ( **)(int, int *, int *, int))(*(_DWORD *)(v2 + 181228) + 16))(v2 + 181228, &byte_A00522, &v87, v2);
  LOBYTE(v31) = g_bDebugMode;
  (((UIPushButton *)(v2 + 181228)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\shui_Positive_over.tga", v31);
  (**(void ( ***)(int, _DWORD))(v2 + 181228))((int)(v2 + 181228), (_DWORD)(0));
  *(_DWORD *)a8 = 694;
  v85 = 737;
  v84 = v86 + 22;
  v86 += 73;
  v32 = v86;
  LOBYTE(v32) = g_bDebugMode;
  (*(void ( **)(int, int *, unsigned __int8 *, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 182332) + 28))(
    v2 + 182332,
    &byte_A00543,
    a8,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\huo_lunar",
    0,
    v32);
  (*(void ( **)(int, int *, unsigned __int8 *, int))(*(_DWORD *)(v2 + 183860) + 16))(
    v2 + 183860,
    &byte_A00518,
    a8,
    v2);
  LOBYTE(v33) = g_bDebugMode;
  (((UIPushButton *)(v2 + 183860)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\huo_lunar_over.tga", v33);
  (**(void ( ***)(int, _DWORD))(v2 + 183860))((int)(v2 + 183860), (_DWORD)(0));
  v34 = *(_DWORD *)(v2 + 179852);
  *(_DWORD *)a8 = v85 - 7;
  v87 = v85 - 7;
  v85 = v85 - 7 + 43;
  v89 = v85;
  v88 = v84 + 1;
  v35 = v84 + 52;
  v90 = v84 + 52;
  LOBYTE(v35) = g_bDebugMode;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD, int))(v34 + 28))(
    v2 + 179852,
    &byte_A00548,
    &v87,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\huo_Positive",
    0,
    v35);
  (*(void ( **)(int, int *, int *, int))(*(_DWORD *)(v2 + 181380) + 16))(v2 + 181380, &byte_A00523, &v87, v2);
  LOBYTE(v36) = g_bDebugMode;
  (((UIPushButton *)(v2 + 181380)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\huo_Positive_over.tga", v36);
  (**(void ( ***)(int, _DWORD))(v2 + 181380))((int)(v2 + 181380), (_DWORD)(0));
  v84 = v86 + 23;
  v86 += 74;
  v37 = v86;
  LOBYTE(v37) = g_bDebugMode;
  v38 = *(_DWORD *)(v2 + 182676);
  *(_DWORD *)a8 = 694;
  v85 = 737;
  (*(void ( **)(int, int *, unsigned __int8 *, int, char *, _DWORD, int))(v38 + 28))(
    v2 + 182676,
    &byte_A00544,
    a8,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\lei_lunar",
    0,
    v37);
  (*(void ( **)(int, int *, unsigned __int8 *, int))(*(_DWORD *)(v2 + 184012) + 16))(
    v2 + 184012,
    &byte_A00519,
    a8,
    v2);
  LOBYTE(v39) = g_bDebugMode;
  (((UIPushButton *)(v2 + 184012)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\lei_lunar_over.tga", v39);
  (**(void ( ***)(int, _DWORD))(v2 + 184012))((int)(v2 + 184012), (_DWORD)(0));
  v40 = *(_DWORD *)(v2 + 180196);
  *(_DWORD *)a8 = v85 - 7;
  v87 = v85 - 7;
  v85 = v85 - 7 + 43;
  v89 = v85;
  v88 = v84 + 1;
  v41 = v84 + 52;
  v90 = v84 + 52;
  LOBYTE(v41) = g_bDebugMode;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD, int))(v40 + 28))(
    v2 + 180196,
    &byte_A00549,
    &v87,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\lei_Positive",
    0,
    v41);
  (*(void ( **)(int, int *, int *, int))(*(_DWORD *)(v2 + 181532) + 16))(v2 + 181532, &byte_A00524, &v87, v2);
  LOBYTE(v42) = g_bDebugMode;
  (((UIPushButton *)(v2 + 181532)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\lei_Positive_over.tga", v42);
  (**(void ( ***)(int, _DWORD))(v2 + 181532))((int)(v2 + 181532), (_DWORD)(0));
  v43 = *(_DWORD *)(v2 + 183020);
  v84 = v86 + 23;
  v86 += 74;
  v44 = v86;
  LOBYTE(v44) = g_bDebugMode;
  *(_DWORD *)a8 = 694;
  v85 = 737;
  (*(void ( **)(int, int *, unsigned __int8 *, int, char *, _DWORD, int))(v43 + 28))(
    v2 + 183020,
    &byte_A00545,
    a8,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\feng_lunar",
    0,
    v44);
  (*(void ( **)(int, int *, unsigned __int8 *, int))(*(_DWORD *)(v2 + 184164) + 16))(
    v2 + 184164,
    &byte_A00520,
    a8,
    v2);
  LOBYTE(v45) = g_bDebugMode;
  (((UIPushButton *)(v2 + 184164)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\feng_lunar_over.tga", v45);
  (**(void ( ***)(int, _DWORD))(v2 + 184164))((int)(v2 + 184164), (_DWORD)(0));
  v46 = *(_DWORD *)(v2 + 180540);
  *(_DWORD *)a8 = v85 - 7;
  v87 = v85 - 7;
  v85 = v85 - 7 + 43;
  v89 = v85;
  v88 = v84 + 1;
  v47 = v84 + 52;
  v90 = v84 + 52;
  LOBYTE(v47) = g_bDebugMode;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD, int))(v46 + 28))(
    v2 + 180540,
    &byte_A00550,
    &v87,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\feng_Positive",
    0,
    v47);
  (*(void ( **)(int, int *, int *, int))(*(_DWORD *)(v2 + 181684) + 16))(v2 + 181684, &byte_A00525, &v87, v2);
  LOBYTE(v48) = g_bDebugMode;
  (((UIPushButton *)(v2 + 181684)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\feng_Positive_over.tga", v48);
  (**(void ( ***)(int, _DWORD))(v2 + 181684))((int)(v2 + 181684), (_DWORD)(0));
  v49 = *(_DWORD *)(v2 + 183364);
  v84 = v86 + 24;
  v86 += 75;
  v50 = v86;
  LOBYTE(v50) = g_bDebugMode;
  *(_DWORD *)a8 = 694;
  v85 = 737;
  (*(void ( **)(int, int *, unsigned __int8 *, int, char *, _DWORD, int))(v49 + 28))(
    v2 + 183364,
    &byte_A00546,
    a8,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\tu_lunar",
    0,
    v50);
  (*(void ( **)(int, int *, unsigned __int8 *, int))(*(_DWORD *)(v2 + 184316) + 16))(
    v2 + 184316,
    &byte_A00521,
    a8,
    v2);
  LOBYTE(v51) = g_bDebugMode;
  (((UIPushButton *)(v2 + 184316)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\tu_lunar_over.tga", v51);
  (**(void ( ***)(int, _DWORD))(v2 + 184316))((int)(v2 + 184316), (_DWORD)(0));
  v52 = *(_DWORD *)(v2 + 180884);
  *(_DWORD *)a8 = v85 - 7;
  v87 = v85 - 7;
  v85 = v85 - 7 + 43;
  v89 = v85;
  v88 = v84 + 1;
  v53 = v84 + 52;
  v90 = v84 + 52;
  LOBYTE(v53) = g_bDebugMode;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD, int))(v52 + 28))(
    v2 + 180884,
    &byte_A00551,
    &v87,
    v2,
    "UI\\GameMainUI\\Sword\\WuLingBtn\\tu_Positive",
    0,
    v53);
  (*(void ( **)(int, int *, int *, int))(*(_DWORD *)(v2 + 181836) + 16))(v2 + 181836, &byte_A00526, &v87, v2);
  LOBYTE(v54) = g_bDebugMode;
  (((UIPushButton *)(v2 + 181836)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\tu_Positive_over.tga", v54);
  (**(void ( ***)(int, _DWORD))(v2 + 181836))((int)(v2 + 181836), (_DWORD)(0));
  v55 = *(_DWORD *)(v2 + 184468);
  v92 = 132;
  v91 = 691;
  v93 = 779;
  v94 = 196;
  v56 = (*(int ( **)(int, int *, int *, int))(v55 + 16))(v2 + 184468, &byte_A00566, &v91, v2);
  LOBYTE(v56) = g_bDebugMode;
  (((UIPushButton *)(v2 + 184468)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\shui_perfect.tga", v56);
  (**(void ( ***)(int, _DWORD))(v2 + 184468))((int)(v2 + 184468), (_DWORD)(0));
  v57 = *(_DWORD *)(v2 + 184620);
  v92 = v94 + 10;
  v94 += 74;
  (*(void ( **)(int, int *, int *, int))(v57 + 16))(v2 + 184620, &byte_A00567, &v91, v2);
  LOBYTE(v58) = g_bDebugMode;
  (((UIPushButton *)(v2 + 184620)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\huo_perfect.tga", v58);
  (**(void ( ***)(int, _DWORD))(v2 + 184620))((int)(v2 + 184620), (_DWORD)(0));
  v59 = *(_DWORD *)(v2 + 184772);
  v92 = v94 + 9;
  v94 += 73;
  (*(void ( **)(int, int *, int *, int))(v59 + 16))(v2 + 184772, &byte_A00568, &v91, v2);
  LOBYTE(v60) = g_bDebugMode;
  (((UIPushButton *)(v2 + 184772)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\lei_perfect.tga", v60);
  (**(void ( ***)(int, _DWORD))(v2 + 184772))((int)(v2 + 184772), (_DWORD)(0));
  v61 = *(_DWORD *)(v2 + 184924);
  v92 = v94 + 10;
  --v91;
  v94 += 74;
  v93 = v91 + 88;
  (*(void ( **)(int, int *, int *, int))(v61 + 16))(v2 + 184924, &byte_A00569, &v91, v2);
  LOBYTE(v62) = g_bDebugMode;
  (((UIPushButton *)(v2 + 184924)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\feng_perfect.tga", v62);
  (**(void ( ***)(int, _DWORD))(v2 + 184924))((int)(v2 + 184924), (_DWORD)(0));
  v63 = *(_DWORD *)(v2 + 185076);
  v92 = v94 + 11;
  v94 += 75;
  (*(void ( **)(int, int *, int *, int))(v63 + 16))(v2 + 185076, &byte_A00570, &v91, v2);
  LOBYTE(v64) = g_bDebugMode;
  (((UIPushButton *)(v2 + 185076)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\WuLingBtn\\tu_perfect.tga", v64);
  (**(void ( ***)(int, _DWORD))(v2 + 185076))((int)(v2 + 185076), (_DWORD)(0));
  LOBYTE(v65) = g_bDebugMode;
  v66 = *(_DWORD *)(v2 + 381816);
  v111[1] = 466;
  v111[0] = 291;
  v111[2] = 491;
  v111[3] = 526;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(v66 + 28))(
    v2 + 381816,
    &byte_A00564,
    (_DWORD *)(v111),
    v2,
    "UI\\GameMainUI\\Sword\\Positive",
    1,
    v65);
  (**(void ( ***)(int, _DWORD))(v2 + 381816))((int)(v2 + 381816), (_DWORD)(0));
  LOBYTE(v67) = g_bDebugMode;
  (*(void ( **)(int, int *, _DWORD *, int, char *, int, int))(*(_DWORD *)(v2 + 382160) + 28))(
    v2 + 382160,
    &byte_A00565,
    (_DWORD *)(v111),
    v2,
    "UI\\GameMainUI\\Sword\\Lunar",
    1,
    v67);
  (**(void ( ***)(int, int))(v2 + 382160))((int)(v2 + 382160), (int)(1));
  (((CCBFiveNimbusWindow *)(v2 + 178036)))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&byte_A00539, v2);
  (((PalScript *)(v2 + 178108)))->PalScript::LoadModel("UI\\GameMainUI\\SWORD\\Data\\Sword.pol", 0);
  *(_DWORD *)(v2 + 178112) = 1;
  *(_DWORD *)(v2 + 178104) = 1;
  (((CCBFiveNimbusWindow *)(v2 + 178036)))->CCBFiveNimbusWindow::SetFloatParam(100.0);
  (((Camera *)(v2 + 178036)))->Camera::UpdateCameraLookAt(392, 400);
  sub_43A090(v2 + 178036, 2, *(float *)(v2 + 21852));
  *(_DWORD *)(v2 + 283692) = 62;
  *(_DWORD *)(v2 + 283688) = 370;
  *(_DWORD *)(v2 + 283696) = 450;
  *(_DWORD *)(v2 + 283700) = 430;
  (((CCBFiveNimbusWindow *)(v2 + 178344)))->CCBFiveNimbusWindow::CreateScriptAndCamera((int)&byte_A00540, v2);
  (((PalScript *)(v2 + 178416)))->PalScript::LoadModel("UI\\GameMainUI\\SWORD\\Data\\ljs.pol", 0);
  *(_DWORD *)(v2 + 178420) = 1;
  *(_DWORD *)(v2 + 178412) = 1;
  (((CCBFiveNimbusWindow *)(v2 + 178344)))->CCBFiveNimbusWindow::SetFloatParam(460.0);
  (((Camera *)(v2 + 178344)))->Camera::UpdateCameraLookAt(730, 152);
  sub_43A090(v2 + 178344, 1, 0.0);
  (((PalScriptWaitObj *)(v2 + 382744)))->PalScriptWaitObj::ReleaseObject("UI\\GameMainUI\\Sword\\Data\\J131Src.tga");
  (((TextureLib *)(v2 + 382744)))->TextureLib::LoadTexture(pszPath);
  *(_DWORD *)(v2 + 382504) = 69;
  *(_DWORD *)(v2 + 382508) = 102;
  *(_DWORD *)(v2 + 382512) = 179;
  *(_DWORD *)(v2 + 382516) = 137;
  *(_DWORD *)(v2 + 382520) = 69;
  *(_DWORD *)(v2 + 382524) = 137;
  *(_DWORD *)(v2 + 382528) = 179;
  *(_DWORD *)(v2 + 382532) = 162;
  *(_DWORD *)(v2 + 382536) = 69;
  *(_DWORD *)(v2 + 382540) = 162;
  *(_DWORD *)(v2 + 382544) = 179;
  *(_DWORD *)(v2 + 382548) = 188;
  *(_DWORD *)(v2 + 382552) = 69;
  *(_DWORD *)(v2 + 382556) = 188;
  *(_DWORD *)(v2 + 382560) = 179;
  *(_DWORD *)(v2 + 382564) = 213;
  *(_DWORD *)(v2 + 382568) = 69;
  *(_DWORD *)(v2 + 382576) = 179;
  *(_DWORD *)(v2 + 382572) = 213;
  *(_DWORD *)(v2 + 382580) = 237;
  *(_DWORD *)(v2 + 382584) = 326;
  *(_DWORD *)(v2 + 382588) = 102;
  *(_DWORD *)(v2 + 382592) = 436;
  *(_DWORD *)(v2 + 382596) = 137;
  *(_DWORD *)(v2 + 382600) = 326;
  *(_DWORD *)(v2 + 382604) = 137;
  *(_DWORD *)(v2 + 382608) = 436;
  *(_DWORD *)(v2 + 382612) = 162;
  *(_DWORD *)(v2 + 382616) = 326;
  *(_DWORD *)(v2 + 382620) = 162;
  *(_DWORD *)(v2 + 382624) = 436;
  *(_DWORD *)(v2 + 382628) = 188;
  *(_DWORD *)(v2 + 382632) = 326;
  *(_DWORD *)(v2 + 382636) = 188;
  *(_DWORD *)(v2 + 382640) = 436;
  *(_DWORD *)(v2 + 382644) = 213;
  *(_DWORD *)(v2 + 382648) = 326;
  *(_DWORD *)(v2 + 382656) = 436;
  *(_DWORD *)(v2 + 382652) = 213;
  *(_DWORD *)(v2 + 382660) = 237;
  *(_DWORD *)(v2 + 382664) = 0;
  *(_DWORD *)(v2 + 382668) = 0;
  *(_DWORD *)(v2 + 382672) = 110;
  *(_DWORD *)(v2 + 382676) = 35;
  *(_DWORD *)(v2 + 382684) = 35;
  *(_DWORD *)(v2 + 382680) = 0;
  *(_DWORD *)(v2 + 382688) = 110;
  *(_DWORD *)(v2 + 382692) = 60;
  *(_DWORD *)(v2 + 382700) = 60;
  *(_DWORD *)(v2 + 382696) = 0;
  *(_DWORD *)(v2 + 382704) = 110;
  *(_DWORD *)(v2 + 382708) = 86;
  *(_DWORD *)(v2 + 382716) = 86;
  *(_DWORD *)(v2 + 382712) = 0;
  *(_DWORD *)(v2 + 382720) = 110;
  *(_DWORD *)(v2 + 382724) = 111;
  *(_DWORD *)(v2 + 382732) = 111;
  *(_DWORD *)(v2 + 382728) = 0;
  *(_DWORD *)(v2 + 382736) = 110;
  *(_DWORD *)(v2 + 382740) = 135;
  *(_DWORD *)(v2 + 21828) = 0;
  RoleNum = GDB_GetRoleNum((PAL_GDB *)&g_pGDB);
  v69 = 0;
  v107 = RoleNum;
  for ( nVal5 = 0; v69 < RoleNum; nVal5 = v69 )
  {
    PropertyByIndex = (((NPC *)&g_pGDB))->NPC::GetPropertyByIndex(v69);
    v71 = (_BYTE *)(((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(PropertyByIndex);
    if ( v71[4] == 4 )
    {
      qmemcpy((void *)(v2 + 760 * *(_DWORD *)(v2 + 21828) + 548), v71, 0x2F8u);
      RoleNum = v107;
      v69 = nVal5;
      ++*(_DWORD *)(v2 + 21828);
    }
    ++v69;
  }
  v72 = *(_DWORD *)(v2 + 364);
  v104 = 48;
  v103 = 688;
  v105 = 784;
  v106 = 80;
  (*(void ( **)(int, int *, int *, int))(v72 + 16))(v2 + 364, &byte_A00541, &v103, v2);
  (((UIScene *)(v2 + 364)))->UIScene::SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&nVal5a + 1) = -5;
    LOBYTE(nVal5a) = 31;
  }
  else
  {
    *(_WORD *)((char *)&nVal5a + 1) = 8187;
    LOBYTE(nVal5a) = -1;
  }
  HIBYTE(nVal5a) = -1;
  AllocObject((void *)(v2 + 364));
  Create__ovl_1_0((CCCTData *)v2, v76);
  memset((void *)(v2 + 21860), 0, 0x630u);
  v100 = 200;
  v99 = 288;
  v101 = 488;
  v102 = 312;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 400080));
  (((UIItem *)(v2 + 400080)))->UIItem::SetData(31);
  v100 = 200;
  v99 = 241;
  v101 = 421;
  v102 = 460;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 401448));
  (((UIItem *)(v2 + 401448)))->UIItem::SetData(31);
  LOBYTE(result) = (((SystemUI *)v2))->SystemUI::CreateNoteEntry(0, v77, v78, v79, v80, nVal5a, a8[0]);
  *(_DWORD *)(v2 + 23452) = nVal;
  *(_BYTE *)(v2 + 21841) = 1;
  return result;
}

// 0x004AC8B0
int SystemUI_ReplaceTextures(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  int v3; // esi
  int *v4; // edi
  int v5; // esi
  int *v6; // edi
  gbTexture *v7; // eax
  int result; // eax
  char pData; // [esp+0x13] [ebp-0x15] BYREF
  char v10; // [esp+0x14] [ebp-0x14]
  char v11; // [esp+0x15] [ebp-0x13]
  char v12; // [esp+0x16] [ebp-0x12]
  char v13; // [esp+0x17] [ebp-0x11]
  char v14; // [esp+0x18] [ebp-0x10]
  char v15; // [esp+0x19] [ebp-0xF]
  char v16; // [esp+0x1A] [ebp-0xE]
  char v17; // [esp+0x1B] [ebp-0xD]
  char v18; // [esp+0x1C] [ebp-0xC]
  char v19; // [esp+0x1D] [ebp-0xB]
  char v20; // [esp+0x1E] [ebp-0xA]
  char v21; // [esp+0x1F] [ebp-0x9]
  char v22; // [esp+0x20] [ebp-0x8]
  char v23; // [esp+0x21] [ebp-0x7]
  char v24; // [esp+0x22] [ebp-0x6]
  char v25; // [esp+0x23] [ebp-0x5]
  char v26; // [esp+0x24] [ebp-0x4]
  char v27; // [esp+0x25] [ebp-0x3]
  char v28; // [esp+0x26] [ebp-0x2]
  char v29; // [esp+0x27] [ebp-0x1]

  v2 = v1;
  switch ( g_nFiveNimbusCount )
  {
    case 0:
      (((UIPushButton *)(v1 + 177580)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\Sword_Shui.tga", g_bDebugMode);
      if ( gbColorQuad::ColorQuadFmt )
      {
        v12 = -7;
        v11 = -34;
        v10 = -102;
      }
      else
      {
        v12 = -102;
        v11 = -34;
        v10 = -7;
      }
      v13 = -1;
      goto LABEL_21;
    case 1:
      (((UIPushButton *)(v1 + 177580)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\Sword_Huo.tga", g_bDebugMode);
      if ( gbColorQuad::ColorQuadFmt )
      {
        v16 = -72;
        v15 = -71;
        v14 = -1;
      }
      else
      {
        v15 = -71;
        v16 = -1;
        v14 = -72;
      }
      v17 = -1;
      goto LABEL_21;
    case 2:
      (((UIPushButton *)(v1 + 177580)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\Sword_Lei.tga", g_bDebugMode);
      if ( gbColorQuad::ColorQuadFmt )
      {
        v20 = -1;
        v19 = -73;
        v18 = -54;
      }
      else
      {
        v20 = -54;
        v19 = -73;
        v18 = -1;
      }
      v21 = -1;
      goto LABEL_21;
    case 3:
      (((UIPushButton *)(v1 + 177580)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\Sword_Feng.tga", g_bDebugMode);
      if ( gbColorQuad::ColorQuadFmt )
      {
        v24 = -48;
        v23 = -1;
        v25 = -1;
        v22 = -73;
      }
      else
      {
        v24 = -73;
        v23 = -1;
        v25 = -1;
        v22 = -48;
      }
      goto LABEL_21;
    case 4:
      (((UIPushButton *)(v1 + 177580)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Sword\\Sword_Tu.tga", g_bDebugMode);
      if ( gbColorQuad::ColorQuadFmt )
      {
        v28 = -73;
        v27 = -20;
        v26 = -1;
      }
      else
      {
        v27 = -20;
        v28 = -1;
        v26 = -73;
      }
      v29 = -1;
LABEL_21:
      AllocObject((void *)(v2 + 177428));
      break;
    default:
      break;
  }
  (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(int *)&g_RoleSlotBuf.m_partyActor.m_curact[11]);
  SetEnable((UICaption *)(v2 + 177428));
  (**(void ( ***)(int, int))(v2 + 177428))((int)(v2 + 177428), (int)(1));
  (((PalScriptWaitObj *)(v2 + 382744)))->PalScriptWaitObj::ReleaseObject("UI\\GameMainUI\\Sword\\Data\\J131Src.tga");
  (((TextureLib *)(v2 + 382744)))->TextureLib::LoadTexture(pszPath);
  v3 = 0;
  v4 = (int *)(v2 + 382584);
  do
  {
    (((TextureLib *)(v2 + 382744)))->TextureLib::CreateFromFile(*v4);
    ++v3;
    v4 += 4;
  }
  while ( v3 < 5 );
  v5 = 0;
  v6 = (int *)(v2 + 382504);
  do
  {
    (((TextureLib *)(v2 + 382744)))->TextureLib::CreateFromFile(*v6);
    ++v5;
    v6 += 4;
  }
  while ( v5 < 5 );
  pData = 0;
  v7 = (((TextureLib *)(v2 + 382744)))->TextureLib::CreateFromMemory(&pData, 1, 1);
  (((gbGeomNode *)*(gbGeomNode **)(v2 + 178124)))->gbGeomNode::ReplaceTexture(v7);
  return result;
}

// 0x004ACC10
int SystemUI_InitSlotEffects(int nVal)
{
  int v1; // ecx
  int v4; // edi
  int *v5; // ebx
  int v6; // esi
  int v7; // ebp
  int v8; // eax
  int v9; // eax
  void *v10; // edi
  const void *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  float fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  float fYb; // [esp+0x4] [ebp-0x20]
  int v20; // [esp+0x18] [ebp-0xC]
  int v21; // [esp+0x1C] [ebp-0x8]
  int nVala; // [esp+0x28] [ebp+0x4]

  *(_DWORD *)(v1 + 177416) = 0;
  *(_DWORD *)(v1 + 177420) = 0;
  nVala = 16;
  *(_BYTE *)(nVal + v1 + 177416) = 1;
  v4 = 16 * nVal + v1;
  v5 = (int *)(v4 + 177288);
  v6 = *(_DWORD *)(16 * (nVal + 11081) + v1) - *(_DWORD *)(v4 + 177288);
  v20 = v4;
  v21 = v6;
  v7 = 9344 * nVal + v1 + 27784;
  while ( 1 )
  {
    (((RenderTarget *)v7))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v7))->RenderTarget::SetSize(32);
    fY = rand() % 10 + 238;
    fX = rand() % 10 + 68;
    v8 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetColor(v8 % 10 - 88, fX, fY);
    v9 = rand();
    (((RenderTarget *)v7))->RenderTarget::SetAlpha(v9 % 55 - 56);
    *(_BYTE *)(v7 + 104) = 1;
    (((RenderTarget *)v7))->RenderTarget::SetField084(1065353216);
    (((RenderTarget *)v7))->RenderTarget::SetState(1067030938);
    fYa = (float)*(int *)(v4 + 177292);
    fXa = (float)(*v5 + rand() % v6);
    (((RenderTarget *)v7))->RenderTarget::UpdateTransform(fXa, fYa);
    (((RenderTarget *)v7))->RenderTarget::Render(*v5, v5[1], v5[2]);
    fYb = (float)(rand() % 2 + 1);
    fXb = (float)(rand() % 2 + 1);
    (((RenderTarget *)v7))->RenderTarget::SetOffset(fXb, fYb);
    (((RenderTarget *)v7))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v7))->RenderTarget::SetVisible(1);
    v10 = (void *)(v7 + 74752);
    v11 = (const void *)v7;
    v7 += 584;
    result = nVala - 1;
    v12 = nVala == 1;
    qmemcpy(v10, v11, 0x248u);
    --nVala;
    if ( v12 )
      break;
    v4 = v20;
    v6 = v21;
  }
  return result;
}

// 0x004ACDE0
int SystemUI_UpdateNoteScroll(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // edi
  int v3; // ebx
  int v4; // ebp
  RenderTarget *v5; // esi
  int v6; // eax
  int v7; // eax
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x28]
  float fXa; // [esp+0x0] [ebp-0x28]
  float fXb; // [esp+0x0] [ebp-0x28]
  int fXc; // [esp+0x0] [ebp-0x28]
  int fVal2; // [esp+0x4] [ebp-0x24]
  float fVal2a; // [esp+0x4] [ebp-0x24]
  int fVal2b; // [esp+0x4] [ebp-0x24]
  int v16; // [esp+0x18] [ebp-0x10]
  int v17; // [esp+0x18] [ebp-0x10]
  float fY; // [esp+0x20] [ebp-0x8]
  int v19; // [esp+0x24] [ebp-0x4]

  v2 = (_DWORD *)v1;
  v3 = (unsigned long)(v1[70924] - v1[70922]);
  v16 = (unsigned long)v1[70923];
  v4 = (unsigned long)(v1[70925] - v16);
  fY = (float)v16;
  v5 = (RenderTarget *)(v1 + 46394);
  v17 = 168;
  do
  {
    v19 = (unsigned long)(v2[70922] + rand() % (v3 / 2));
    (((RenderTarget *)v5))->RenderTarget::LoadTexture("UI\\GameMainUI\\Par_Effect\\star.tga");
    (((RenderTarget *)v5))->RenderTarget::SetSize(32);
    fVal2 = rand() % 10 + 38;
    fX = rand() % 10 + 98;
    v6 = rand();
    (((RenderTarget *)v5))->RenderTarget::SetColor(v6 % 10 - 34, fX, fVal2);
    v7 = rand();
    (((RenderTarget *)v5))->RenderTarget::SetAlpha(v7 % 46 - 58);
    (((RenderTarget *)v5))->RenderTarget::SetField084(0x40000000);
    (((RenderTarget *)v5))->RenderTarget::SetState(1058642330);
    fXa = (float)v19;
    (((RenderTarget *)v5))->RenderTarget::UpdateTransform(fXa, fY);
    (((RenderTarget *)v5))->RenderTarget::CalcRenderDimensions(v3, v4);
    fVal2a = (float)(rand() % 6 + 3);
    fXb = (float)(rand() % 6 + 5);
    (((RenderTarget *)v5))->RenderTarget::SetOffset(fXb, fVal2a);
    *(float *)&fVal2b = (float)(rand() % 6 + 4);
    *(float *)&fXc = (float)(rand() % 6 + 6);
    (((RenderTarget *)v5))->RenderTarget::SetScale(fXc, fVal2b);
    (((RenderTarget *)v5))->RenderTarget::SetVisible(1);
    v5 = (RenderTarget *)((char *)v5 + 584);
    result = --v17;
  }
  while ( v17 );
  return result;
}

// 0x004ACF90
int SystemUI_UpdateNoteScrollAlt(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // edi
  int v3; // ebx
  int v4; // ebp
  RenderTarget *v5; // esi
  int v6; // eax
  int v7; // eax
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x28]
  float fXa; // [esp+0x0] [ebp-0x28]
  float fXb; // [esp+0x0] [ebp-0x28]
  int fXc; // [esp+0x0] [ebp-0x28]
  int fVal2; // [esp+0x4] [ebp-0x24]
  float fVal2a; // [esp+0x4] [ebp-0x24]
  int fVal2b; // [esp+0x4] [ebp-0x24]
  int v16; // [esp+0x18] [ebp-0x10]
  int v17; // [esp+0x18] [ebp-0x10]
  float fY; // [esp+0x20] [ebp-0x8]
  int v19; // [esp+0x24] [ebp-0x4]

  v2 = (_DWORD *)v1;
  v3 = (unsigned long)(v1[70924] - v1[70922]);
  v16 = (unsigned long)v1[70923];
  v4 = (unsigned long)(v1[70925] - v16);
  fY = (float)v16;
  v5 = (RenderTarget *)(v1 + 70926);
  v17 = 168;
  do
  {
    v19 = (unsigned long)(v2[70922] + rand() % (v3 / 2));
    (((RenderTarget *)v5))->RenderTarget::LoadTexture(szFilename);
    (((RenderTarget *)v5))->RenderTarget::SetSize(32);
    fVal2 = rand() % 10 + 98;
    fX = rand() % 10 + 188;
    v6 = rand();
    (((RenderTarget *)v5))->RenderTarget::SetColor(v6 % 10 + 68, fX, fVal2);
    v7 = rand();
    (((RenderTarget *)v5))->RenderTarget::SetAlpha(v7 % 10 - 28);
    (((RenderTarget *)v5))->RenderTarget::SetField084(0x40000000);
    (((RenderTarget *)v5))->RenderTarget::SetState(1058642330);
    fXa = (float)v19;
    (((RenderTarget *)v5))->RenderTarget::UpdateTransform(fXa, fY);
    (((RenderTarget *)v5))->RenderTarget::CalcRenderDimensions(v3, v4);
    fVal2a = (float)(rand() % 8 + 1);
    fXb = (float)(rand() % 5 + 1);
    (((RenderTarget *)v5))->RenderTarget::SetOffset(fXb, fVal2a);
    *(float *)&fVal2b = (float)(rand() % 12 + 1);
    *(float *)&fXc = (float)(rand() % 6 + 1);
    (((RenderTarget *)v5))->RenderTarget::SetScale(fXc, fVal2b);
    (((RenderTarget *)v5))->RenderTarget::SetVisible(1);
    v5 = (RenderTarget *)((char *)v5 + 584);
    result = --v17;
  }
  while ( v17 );
  return result;
}

// 0x004AFAA0
void CopyRoleData(int pDst, int pSrc)
{
  int v2; // ecx
  int v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // edx
  _DWORD *v6; // ecx
  _DWORD *i; // eax

  if ( pDst )
  {
    *(_DWORD *)pDst = *(_DWORD *)pSrc;
    *(_BYTE *)(pDst + 4) = *(_BYTE *)(pSrc + 4);
    *(_BYTE *)(pDst + 8) = *(_BYTE *)(pSrc + 8);
    v2 = *(_DWORD *)(pSrc + 12);
    if ( v2 )
      v3 = (*(_DWORD *)(pSrc + 16) - v2) >> 4;
    else
      v3 = 0;
    if ( v3 < 0 )
      v3 = 0;
    v4 = (_DWORD *)operator new(16 * v3);
    *(_DWORD *)(pDst + 12) = (_DWORD)v4;
    v5 = (_DWORD *)*(_DWORD **)(pSrc + 16);
    v6 = (_DWORD *)v4;
    for ( i = *(_DWORD **)(pSrc + 12); i != v5; v6 += 4 )
    {
      if ( v6 )
      {
        *v6 = *i;
        v6[1] = (unsigned long)i[1];
        v6[2] = (unsigned long)i[2];
        v6[3] = (unsigned long)i[3];
      }
      i += 4;
    }
    *(_DWORD *)(pDst + 16) = (_DWORD)v6;
    *(_DWORD *)(pDst + 20) = (_DWORD)v6;
  }
}

// 0x004B0040
int * SortTripletsByField(int *p_DWORD, int *p_DWORD2, int nVal)
{
  int *result; // eax
  int *v4; // esi
  int *v5; // edi
  int v6; // edx
  int v7; // ecx
  BOOL v8; // eax
  int v9; // ebx
  int v10; // ebp
  int *v11; // eax
  int *v12; // edx
  int v13; // ebx
  int v14; // esi
  BOOL v15; // ecx
  int v16; // ebp
  bool v17; // sf
  bool v18; // of
  int v19; // ebp
  int *v20; // eax
  int v21; // [esp+0x8] [ebp-0x18]
  int v22; // [esp+0xC] [ebp-0x14]
  int v23; // [esp+0x14] [ebp-0xC]

  result = (int *)p_DWORD2;
  v4 = (int *)p_DWORD;
  if ( p_DWORD != p_DWORD2 )
  {
    v5 = (int *)(p_DWORD + 3);
    if ( p_DWORD + 3 != p_DWORD2 )
    {
      while ( 1 )
      {
        v23 = (unsigned long)*v5;
        v6 = (unsigned long)v5[1];
        v7 = (unsigned long)v5[2];
        if ( !nVal )
          break;
        if ( nVal == 1 )
        {
          v9 = *(_DWORD *)(v7 + 624);
          v10 = *(_DWORD *)(v4[2] + 624);
LABEL_9:
          LOBYTE(v8) = v9 < v10;
          goto LABEL_10;
        }
        if ( nVal != 2 )
          goto LABEL_11;
        v8 = v6 > v4[1];
LABEL_10:
        if ( !v8 )
        {
LABEL_11:
          v11 = (int *)(v5 + 2);
          v21 = (unsigned long)*v5;
          v12 = (int *)v5;
          v13 = (unsigned long)v5[1];
          v22 = v13;
          v14 = (unsigned long)v5[2];
          while ( 1 )
          {
            v11 -= 3;
            if ( !nVal )
              break;
            if ( nVal == 1 )
            {
              v16 = *(_DWORD *)(v14 + 624);
              v18 = __OFSUB__(v16, *(_DWORD *)(*v11 + 624));
              v17 = v16 - *(_DWORD *)(*v11 + 624) < 0;
LABEL_18:
              LOBYTE(v15) = v17 ^ v18;
              goto LABEL_19;
            }
            if ( nVal != 2 )
              goto LABEL_21;
            v15 = v13 > *(v11 - 1);
LABEL_19:
            if ( !v15 )
            {
LABEL_21:
              *v12 = v21;
              v12[1] = v13;
              v12[2] = v14;
              v4 = (int *)p_DWORD;
              goto LABEL_25;
            }
            *v12 = *(v11 - 2);
            v12[1] = *(v11 - 1);
            v12[2] = (unsigned long)*v11;
            v13 = v22;
            v12 = (int *)(v11 - 2);
          }
          v19 = *(_DWORD *)(v14 + 608);
          v18 = __OFSUB__(v19, *(_DWORD *)(*v11 + 608));
          v17 = v19 - *(_DWORD *)(*v11 + 608) < 0;
          goto LABEL_18;
        }
        v20 = (int *)v5;
        if ( v4 != v5 )
        {
          do
          {
            v20 -= 3;
            v20[3] = (unsigned long)*v20;
            v20[4] = (unsigned long)v20[1];
            v20[5] = (unsigned long)v20[2];
            v4 = (int *)p_DWORD;
          }
          while ( v20 != p_DWORD );
        }
        *v4 = v23;
        v4[1] = v6;
        v4[2] = v7;
LABEL_25:
        result = (int *)p_DWORD2;
        v5 += 3;
        if ( v5 == p_DWORD2 )
          return result;
      }
      v9 = *(_DWORD *)(v7 + 608);
      v10 = *(_DWORD *)(v4[2] + 608);
      goto LABEL_9;
    }
  }
  return result;
}

// 0x004B01D0
int UITitle_JDHY_DestroyPages(int nVal)
{
  UIListBox *v1; // ecx
  int v2; // esi

  v2 = (int)v1;
  v1->UIListBox::UIListBox();
  *(_DWORD *)(v2 + 88) = 800;
  *(_DWORD *)(v2 + 92) = 600;
  *(_BYTE *)(v2 + 360) = 0;
  *(_DWORD *)(v2 + 364) = 0;
  (((UIFrameContainer *)(v2 + 368)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 520)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 672)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 824)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 976)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 1128)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)(v2 + 4376)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 4544)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 4696)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 154492)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 154644)))->UIFrameContainer::ResetContainerState();
  ((UIPushButton *)(v2 + 154796))->UIPushButton::UIPushButton();
  ((UIPushButton *)(v2 + 155044))->UIPushButton::UIPushButton();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIScene *)(v2 + 285224)))->UIScene::ctor();
  (((UIScene *)(v2 + 285504)))->UIScene::ctor();
  (((UIScene *)(v2 + 285776)))->UIScene::ctor();
  (((UIFrameContainer *)(v2 + 286048)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(v2 + 286200)))->UIFrameContainer::ResetContainerState();
  *(_DWORD *)(v2 + 286352) = 92;
  *(_DWORD *)(v2 + 286356) = 610;
  *(_DWORD *)(v2 + 286360) = 0;
  *(_DWORD *)(v2 + 286364) = 0;
  *(_DWORD *)(v2 + 286368) = 0;
  *(_DWORD *)(v2 + 286372) = 0;
  ((UIRoleDialog *)(v2 + 286384))->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)(v2 + 287752))->UIRoleDialog::UIRoleDialog();
  ((UIRoleDialog *)(v2 + 289120))->UIRoleDialog::UIRoleDialog();
  *(_DWORD *)(v2 + 154480) = 0;
  *(_DWORD *)(v2 + 154484) = 0;
  *(_DWORD *)(v2 + 154488) = 0;
  *(_DWORD *)(v2 + 286376) = 0;
  memset((void *)(v2 + 156324), 0, 0x24u);
  return v2;
}

// 0x004B0540
int UITitle_JDHY__UITitle_JDHY(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax

  v2 = v1;
  (((UIRoleDialog *)(v1 + 289120)))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)(v2 + 287752)))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)(v2 + 286384)))->UIRoleDialog::~UIRoleDialog();
  (((UIFrameContainer *)(v2 + 286200)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 286048)))->UIFrameContainer::~UIFrameContainer();
  (((CCBResultWindow *)(v2 + 285776)))->CCBResultWindow::~CCBResultWindow();
  (((CCBResultWindow *)(v2 + 285504)))->CCBResultWindow::~CCBResultWindow();
  (((CCBResultWindow *)(v2 + 285224)))->CCBResultWindow::~CCBResultWindow();
  (((UICaption *)(v2 + 284864)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 284520)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 155980)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 155636)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 155292)))->UICaption::Destroy2();
  (((UIPushButton *)(v2 + 155044)))->UIPushButton::~UIPushButton();
  (((UIPushButton *)(v2 + 154796)))->UIPushButton::~UIPushButton();
  (((UIFrameContainer *)(v2 + 154644)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 154492)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 4696)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 4544)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 4376)))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)(v2 + 4032)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 3688)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 3344)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 3000)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 2656)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 2312)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 1968)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 1624)))->UICaption::Destroy2();
  (((UICaption *)(v2 + 1280)))->UICaption::Destroy2();
  (((UIFrameContainer *)(v2 + 1128)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 976)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 824)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 672)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 520)))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)(v2 + 368)))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)v2))->UIListBox::~UIListBox();
  return result;
}

// 0x004B0820
int UITitle_JDHY_PopulateContent(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  int v10; // edx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // eax
  int v17; // edx
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // edx
  int v26; // edx
  int v27; // ecx
  int v28; // eax
  int v29; // eax
  int v30; // ebx
  float v31; // st7
  __int64 v32; // rax
  int v33; // ebp
  __int64 v34; // rax
  int v35; // ecx
  int v36; // ebx
  int v37; // ecx
  int v38; // ebp
  int v39; // eax
  float v40; // st7
  int v41; // ecx
  int v42; // eax
  int v43; // eax
  float v44; // st7
  int v45; // ebp
  int v46; // ebx
  int v47; // eax
  int v48; // ecx
  __int64 v49; // rax
  int v50; // ecx
  int *v51; // eax
  int v52; // edx
  int v53; // ecx
  int v54; // edx
  int v55; // ecx
  int v56; // edx
  int v57; // eax
  int v58; // eax
  int v59; // ebx
  float v60; // st7
  int v61; // ebp
  int v62; // eax
  __int64 v63; // rax
  int v64; // ecx
  int v65; // ebp
  int v66; // ecx
  int v67; // ebx
  int v68; // eax
  float v69; // st7
  int v70; // eax
  int v71; // eax
  float v72; // st7
  int v73; // eax
  int v74; // ecx
  int v75; // ecx
  int v76; // edx
  int v77; // eax
  int v78; // eax
  int v79; // ebx
  float v80; // st7
  __int64 v81; // rax
  int v82; // ecx
  int v83; // ebx
  __int64 v84; // rax
  __int64 v85; // rax
  int v86; // ecx
  int v87; // eax
  int v88; // ebx
  float v89; // st7
  float v90; // st7
  float v91; // st7
  int v92; // ecx
  float fVal; // [esp+0x108] [ebp-0x8C]
  PlayerItem *v95; // [esp+0x10C] [ebp-0x88]
  PlayerItem *v96; // [esp+0x10C] [ebp-0x88]
  PlayerItem *v97; // [esp+0x10C] [ebp-0x88]
  PlayerItem *v98; // [esp+0x110] [ebp-0x84]
  PlayerItem *v99; // [esp+0x110] [ebp-0x84]
  PlayerItem *v100; // [esp+0x110] [ebp-0x84]
  int v101; // [esp+0x11C] [ebp-0x78]
  int v102; // [esp+0x11C] [ebp-0x78]
  int v103; // [esp+0x11C] [ebp-0x78]
  gbColorQuad v104; // [esp+0x120] [ebp-0x74] BYREF
  int v105; // [esp+0x124] [ebp-0x70] BYREF
  int v106; // [esp+0x128] [ebp-0x6C]
  int v107; // [esp+0x12C] [ebp-0x68]
  int v108; // [esp+0x130] [ebp-0x64]
  int v109; // [esp+0x134] [ebp-0x60] BYREF
  int v110; // [esp+0x138] [ebp-0x5C]
  int v111; // [esp+0x13C] [ebp-0x58]
  int v112; // [esp+0x140] [ebp-0x54]
  int v113; // [esp+0x144] [ebp-0x50] BYREF
  int v114; // [esp+0x148] [ebp-0x4C]
  int v115; // [esp+0x14C] [ebp-0x48]
  int v116; // [esp+0x150] [ebp-0x44]
  int v117; // [esp+0x154] [ebp-0x40] BYREF
  int v118; // [esp+0x158] [ebp-0x3C]
  int v119; // [esp+0x15C] [ebp-0x38]
  int v120; // [esp+0x160] [ebp-0x34]
  int v121; // [esp+0x164] [ebp-0x30] BYREF
  int v122; // [esp+0x168] [ebp-0x2C]
  int v123; // [esp+0x16C] [ebp-0x28]
  int v124; // [esp+0x170] [ebp-0x24]
  int v125; // [esp+0x174] [ebp-0x20] BYREF
  int v126; // [esp+0x178] [ebp-0x1C]
  int v127; // [esp+0x17C] [ebp-0x18]
  int v128; // [esp+0x180] [ebp-0x14]
  int v129; // [esp+0x184] [ebp-0x10]
  int v130; // [esp+0x188] [ebp-0xC]
  int v131; // [esp+0x18C] [ebp-0x8]
  int v132; // [esp+0x190] [ebp-0x4]

  v2 = v1;
  v3 = *(_DWORD *)(v1 + 88);
  v4 = *(_DWORD *)(v1 + 92);
  *(_DWORD *)(v2 + 80) = v3;
  *(_DWORD *)(v2 + 76) = 0;
  *(_DWORD *)(v2 + 72) = 0;
  *(_DWORD *)(v2 + 84) = v4;
  (((UIListBox *)v2))->UIListBox::SetSelTexture(-1, *(_DWORD *)(v2 + 72), *(_DWORD *)(v2 + 76), *(_DWORD *)(v2 + 80), *(_DWORD *)(v2 + 84));
  v5 = *(_DWORD *)(v2 + 72);
  *(_DWORD *)(v2 + 364) = nVal;
  v6 = *(_DWORD *)(v2 + 368);
  v118 = *(_DWORD *)(v2 + 76) + 38;
  v117 = v5 + 670;
  v120 = v118 + 505;
  v119 = v5 + 784;
  (*(void ( **)(int, int, int *, int))(v6 + 16))(v2 + 368, 161, &v117, v2);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)(v2 + 368)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\Frame.tga", v7);
  v117 = v119;
  v119 += 17;
  v118 += 26;
  v109 = v119 - 205;
  v120 = v118 + 526;
  v111 = v119 - 205 + 203;
  v8 = *(_DWORD *)(v2 + 672);
  v110 = 0;
  v112 = 64;
  (*(void ( **)(int, int, int *, int))(v8 + 16))(v2 + 672, 161, &v109, v2);
  LOBYTE(v9) = g_bDebugMode;
  (((UIPushButton *)(v2 + 672)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\TimeMoney.tga", v9);
  v10 = *(_DWORD *)(v2 + 4696);
  v110 = -4;
  v109 = 618;
  v111 = 738;
  v112 = 28;
  (*(void ( **)(int, int, int *, int))(v10 + 16))(v2 + 4696, 161, &v109, v2);
  (((UIScene *)(v2 + 4696)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 4696));
  v11 = *(_DWORD *)(v2 + 4544);
  v110 = 16;
  v109 = 668;
  v111 = 748;
  v112 = 48;
  (*(void ( **)(int, int, int *, int))(v11 + 16))(v2 + 4544, 161, &v109, v2);
  (((UIScene *)(v2 + 4544)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 4544));
  (((LineupUI *)v2))->LineupUI::RebuildMainPage();
  v12 = *(_DWORD *)(v2 + 154492);
  v106 = 23;
  v105 = 40;
  v107 = 624;
  v108 = 43;
  (*(void ( **)(int, int *, int *, int))(v12 + 16))(v2 + 154492, &byte_A00700, &v105, v2);
  LOBYTE(v13) = g_bDebugMode;
  (((UIPushButton *)(v2 + 154492)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\TopBar.tga", v13);
  v14 = *(_DWORD *)(v2 + 154644);
  v106 = 500;
  v105 = 41;
  v107 = 625;
  v108 = 537;
  (*(void ( **)(int, int *, int *, int))(v14 + 16))(v2 + 154644, &byte_A00700, &v105, v2);
  LOBYTE(v15) = g_bDebugMode;
  (((UIPushButton *)(v2 + 154644)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\BottomBar.tga", v15);
  LOBYTE(v16) = g_bDebugMode;
  v17 = *(_DWORD *)(v2 + 154796);
  v114 = 5;
  v113 = 146;
  v115 = 264;
  v116 = 37;
  (*(void ( **)(int, int *, int *, int, char *, int))(v17 + 28))(
    v2 + 154796,
    &byte_A00704,
    &v113,
    v2,
    "UI\\GameMainUI\\System\\Save",
    v16);
  (((UIPushButton *)(v2 + 154796)))->UIPushButton::FormatText("UI\\GameMainUI\\System\\Saveon.tga", g_bDebugMode);
  v18 = *(_DWORD *)(v2 + 155044);
  v113 = v115 + 134;
  v115 += 252;
  v19 = v115;
  LOBYTE(v19) = g_bDebugMode;
  (*(void ( **)(int, int *, int *, int, char *, int))(v18 + 28))(
    v2 + 155044,
    &byte_A00705,
    &v113,
    v2,
    "UI\\GameMainUI\\System\\Load",
    v19);
  (((UIPushButton *)(v2 + 155044)))->UIPushButton::FormatText("UI\\GameMainUI\\System\\Loadon.tga", g_bDebugMode);
  LOBYTE(v20) = g_bDebugMode;
  v21 = *(_DWORD *)(v2 + 155980);
  v114 = 456;
  v113 = 696;
  v115 = 769;
  v116 = 531;
  (*(void ( **)(int, int *, int *, int, char *, int, int))(v21 + 28))(
    v2 + 155980,
    &byte_A00708,
    &v113,
    v2,
    "UI\\GameMainUI\\System\\ExitGame",
    1,
    v20);
  (((UITitle_JDHY *)v2))->UITitle_JDHY::InitNoteItems();
  v22 = *(_DWORD *)(v2 + 76);
  LOBYTE(v23) = g_bDebugMode;
  v121 = *(_DWORD *)(v2 + 72) + 634;
  v122 = v22 + 38;
  v123 = v121 + 25;
  v124 = v22 + 66;
  (*(void ( **)(int *, int *, int, char *, int, int))(*(_DWORD *)(v2 + 284520) + 28))(
    &byte_A00702,
    &v121,
    v2,
    "UI\\GameMainUI\\System\\pgup",
    1,
    v23);
  v24 = *(_DWORD *)(v2 + 76);
  LOBYTE(v25) = g_bDebugMode;
  v121 = *(_DWORD *)(v2 + 72) + 634;
  v122 = v24 + 503;
  v123 = v121 + 25;
  v124 = v24 + 531;
  (*(void ( **)(int *, int *, int, char *, int, int))(*(_DWORD *)(v2 + 284864) + 28))(
    &byte_A00701,
    &v121,
    v2,
    "UI\\GameMainUI\\System\\pgdw",
    1,
    v25);
  v26 = *(_DWORD *)(v2 + 285224);
  *(_DWORD *)(v2 + 285212) = 66;
  *(_DWORD *)(v2 + 285216) = 654;
  *(_DWORD *)(v2 + 285208) = 640;
  *(_DWORD *)(v2 + 285220) = 503;
  LOBYTE(v27) = g_bDebugMode;
  (*(void ( **)(int, ARC_PlayerAtt *, int, int, char *, int))(v26 + 28))(
    v2 + 285224,
    &g_PlayerAttBuffer2,
    v2 + 285208,
    v2,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    v27);
  (((UIScene *)(v2 + 285224)))->UIScene::SetTexture("UI\\GameMainUI\\System\\hdt.tga", 0);
  (((UIBigMap *)(v2 + 285224)))->UIBigMap::UpdateWindowPos(26, 28);
  fill((PlayerItem *)1, v95, v98);
  *(_DWORD *)(v2 + 285480) = 1096810496;
  *(_DWORD *)(v2 + 285484) = -1050673152;
  v28 = *(_DWORD *)(v2 + 285488);
  *(_DWORD *)(v2 + 285468) = 20;
  if ( !v28 )
  {
    v42 = *(_DWORD *)(v2 + 285492);
    if ( !v42 )
    {
      v45 = *(_DWORD *)(v2 + 285320);
      v46 = (__int64)((double)(*(_DWORD *)(v2 + 285364) - v45 - 20) + *(float *)(v2 + 285480));
      v47 = *(_DWORD *)(v2 + 285316);
      v48 = *(_DWORD *)(v2 + 285360);
      *(_DWORD *)(v2 + 285348) = v46;
      v49 = (__int64)((double)(v48 - v47 / 2) + *(float *)(v2 + 285472) + *(float *)(v2 + 285460));
      v50 = *(_DWORD *)(v2 + 285316);
      *(_DWORD *)(v2 + 285344) = v49;
      *(_DWORD *)(v2 + 285352) = v50 + v49;
      *(_DWORD *)(v2 + 285356) = v45 + v46;
      goto LABEL_12;
    }
    if ( v42 != 1 )
      goto LABEL_12;
    v36 = *(_DWORD *)(v2 + 285320);
    v38 = (__int64)((double)(*(_DWORD *)(v2 + 285364) - v36 - 20) + *(float *)(v2 + 285480));
    v43 = *(_DWORD *)(v2 + 285316);
    v44 = (float)*(int *)(v2 + 285368) - *(float *)(v2 + 285460);
    *(_DWORD *)(v2 + 285348) = v38;
    v40 = v44 - (float)(v43 / 2) - *(float *)(v2 + 285476);
LABEL_7:
    v41 = *(_DWORD *)(v2 + 285316);
    *(_DWORD *)(v2 + 285344) = (__int64)v40;
    *(_DWORD *)(v2 + 285352) = v41 + (__int64)v40;
    *(_DWORD *)(v2 + 285356) = v36 + v38;
    goto LABEL_12;
  }
  if ( v28 != 1 )
    goto LABEL_12;
  v29 = *(_DWORD *)(v2 + 285492);
  if ( !v29 )
  {
    v36 = *(_DWORD *)(v2 + 285320);
    v37 = *(_DWORD *)(v2 + 285360);
    v38 = (__int64)((double)(*(_DWORD *)(v2 + 285364) - v36 / 2) + *(float *)(v2 + 285480) + *(float *)(v2 + 285460));
    v39 = *(_DWORD *)(v2 + 285316);
    *(_DWORD *)(v2 + 285348) = v38;
    v40 = (float)(v37 - v39 - 20) + *(float *)(v2 + 285472);
    goto LABEL_7;
  }
  if ( v29 == 1 )
  {
    v30 = *(_DWORD *)(v2 + 285320);
    v31 = (float)*(int *)(v2 + 285372) - *(float *)(v2 + 285460);
    v32 = (__int64)(v31 - (double)(v30 / 2) - *(float *)(v2 + 285484));
    HIDWORD(v32) = *(_DWORD *)(v2 + 285368);
    v33 = (__int64)(v31 - (double)(v30 / 2) - *(float *)(v2 + 285484));
    *(_DWORD *)(v2 + 285348) = v32;
    v34 = (__int64)((double)(HIDWORD(v32) + 20) - *(float *)(v2 + 285460) - *(float *)(v2 + 285476));
    v35 = *(_DWORD *)(v2 + 285316);
    *(_DWORD *)(v2 + 285344) = v34;
    *(_DWORD *)(v2 + 285352) = v34 + v35;
    *(_DWORD *)(v2 + 285356) = v30 + v33;
  }
LABEL_12:
  (((UIScene *)(v2 + 285224)))->UIScene::SetParam(*v51);
  fVal = (float)(32 * *(_DWORD *)(v2 + 286352) - 28);
  (((UIScene *)(v2 + 285224)))->UIScene::UpdateLayout(fVal);
  v52 = *(_DWORD *)(v2 + 286048);
  v126 = 368;
  v125 = 684;
  v127 = 740;
  v128 = 392;
  (*(void ( **)(int, int *, int *, int))(v52 + 16))(v2 + 286048, &byte_A00700, &v125, v2);
  LOBYTE(v53) = g_bDebugMode;
  (((UIPushButton *)(v2 + 286048)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\MusicText.tga", v53);
  v54 = *(_DWORD *)(v2 + 286200);
  v126 = 105;
  v125 = 726;
  v127 = 782;
  v128 = 129;
  (*(void ( **)(int, int *, int *, int))(v54 + 16))(v2 + 286200, &byte_A00700, &v125, v2);
  LOBYTE(v55) = g_bDebugMode;
  (((UIPushButton *)(v2 + 286200)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\MusicEffectText.tga", v55);
  v56 = *(_DWORD *)(v2 + 285504);
  v106 = 56;
  v105 = 698;
  v107 = 718;
  v108 = 364;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD))(v56 + 28))(
    v2 + 285504,
    &byte_A00709,
    &v105,
    v2,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    0);
  (((UIScene *)(v2 + 285504)))->UIScene::SetTexture("UI\\GameMainUI\\System\\MusicBar.tga", g_bDebugMode);
  fill((PlayerItem *)1, v96, v99);
  (((UIBigMap *)(v2 + 285504)))->UIBigMap::UpdateWindowPos(26, 30);
  (((UIScene *)(v2 + 285504)))->UIScene::SetParam(0);
  *(_DWORD *)(v2 + 285760) = 1101004800;
  *(_DWORD *)(v2 + 285764) = -1049624576;
  v57 = *(_DWORD *)(v2 + 285768);
  *(_DWORD *)(v2 + 285748) = 23;
  if ( !v57 )
  {
    v70 = *(_DWORD *)(v2 + 285772);
    if ( v70 )
    {
      if ( v70 != 1 )
        goto LABEL_23;
      v65 = *(_DWORD *)(v2 + 285600);
      v104.Color = *(_DWORD *)(v2 + 285644) - v65 - 23;
      v67 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 285760));
      v71 = *(_DWORD *)(v2 + 285596);
      v72 = (float)*(int *)(v2 + 285648) - *(float *)(v2 + 285740);
      *(_DWORD *)(v2 + 285628) = v67;
      v104.Color = v71 / 2;
      v69 = v72 - (float)(v71 / 2) - *(float *)(v2 + 285756);
    }
    else
    {
      v65 = *(_DWORD *)(v2 + 285600);
      v104.Color = *(_DWORD *)(v2 + 285644) - v65 - 23;
      v67 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 285760));
      v73 = *(_DWORD *)(v2 + 285596);
      v74 = *(_DWORD *)(v2 + 285640);
      *(_DWORD *)(v2 + 285628) = v67;
      v104.Color = v74 - v73 / 2;
      v69 = (float)(int)v104.Color + *(float *)(v2 + 285752) + *(float *)(v2 + 285740);
    }
    goto LABEL_22;
  }
  if ( v57 != 1 )
    goto LABEL_23;
  v58 = *(_DWORD *)(v2 + 285772);
  if ( !v58 )
  {
    v65 = *(_DWORD *)(v2 + 285600);
    v104.Color = *(_DWORD *)(v2 + 285644) - v65 / 2;
    v66 = *(_DWORD *)(v2 + 285640);
    v67 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 285760) + *(float *)(v2 + 285740));
    v68 = *(_DWORD *)(v2 + 285596);
    *(_DWORD *)(v2 + 285628) = v67;
    v104.Color = v66 - v68 - 23;
    v69 = (float)(int)v104.Color + *(float *)(v2 + 285752);
LABEL_22:
    v75 = *(_DWORD *)(v2 + 285596);
    *(_DWORD *)(v2 + 285624) = (__int64)v69;
    *(_DWORD *)(v2 + 285632) = v75 + (__int64)v69;
    *(_DWORD *)(v2 + 285636) = v65 + v67;
    goto LABEL_23;
  }
  if ( v58 == 1 )
  {
    v59 = *(_DWORD *)(v2 + 285600);
    v60 = (float)*(int *)(v2 + 285652) - *(float *)(v2 + 285740);
    v104.Color = v59 / 2;
    v61 = (__int64)(v60 - (double)(v59 / 2) - *(float *)(v2 + 285764));
    v62 = *(_DWORD *)(v2 + 285648);
    *(_DWORD *)(v2 + 285628) = v61;
    v104.Color = v62 + 23;
    v63 = (__int64)((double)(v62 + 23) - *(float *)(v2 + 285740) - *(float *)(v2 + 285756));
    v64 = *(_DWORD *)(v2 + 285596);
    *(_DWORD *)(v2 + 285624) = v63;
    *(_DWORD *)(v2 + 285632) = v63 + v64;
    *(_DWORD *)(v2 + 285636) = v59 + v61;
  }
LABEL_23:
  (((UIScene *)(v2 + 285504)))->UIScene::UpdateLayout(100.0);
  v76 = *(_DWORD *)(v2 + 285776);
  v106 = 136;
  v105 = 744;
  v107 = 764;
  v108 = 444;
  (*(void ( **)(int, int *, int *, int, char *, _DWORD))(v76 + 28))(
    v2 + 285776,
    &dword_A00710,
    &v105,
    v2,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    0);
  (((UIScene *)(v2 + 285776)))->UIScene::SetTexture("UI\\GameMainUI\\System\\MusicEffect.tga", g_bDebugMode);
  fill((PlayerItem *)1, v97, v100);
  (((UIScene *)(v2 + 285776)))->UIScene::ResizeContentAlt(1);
  (((UIBigMap *)(v2 + 285776)))->UIBigMap::UpdateWindowPos(26, 30);
  (((UIScene *)(v2 + 285776)))->UIScene::SetParam(0);
  *(_DWORD *)(v2 + 286032) = 1097859072;
  *(_DWORD *)(v2 + 286036) = -1046478848;
  v77 = *(_DWORD *)(v2 + 286040);
  *(_DWORD *)(v2 + 286020) = 2;
  if ( !v77 )
  {
    v87 = *(_DWORD *)(v2 + 286044);
    if ( v87 )
    {
      if ( v87 != 1 )
        goto LABEL_34;
      v88 = *(_DWORD *)(v2 + 285872);
      v104.Color = *(_DWORD *)(v2 + 285916) - v88 - 2;
      v89 = (float)*(int *)(v2 + 285920);
      v103 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 286032));
      *(_DWORD *)(v2 + 285900) = v103;
      v90 = v89 - *(float *)(v2 + 286012);
      v104.Color = *(_DWORD *)(v2 + 285868) / 2;
      v91 = v90 - (float)(int)v104.Color - *(float *)(v2 + 286028);
    }
    else
    {
      v88 = *(_DWORD *)(v2 + 285872);
      v104.Color = *(_DWORD *)(v2 + 285916) - v88 - 2;
      v103 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 286032));
      *(_DWORD *)(v2 + 285900) = v103;
      v104.Color = *(_DWORD *)(v2 + 285912) - *(_DWORD *)(v2 + 285868) / 2;
      v91 = (float)(int)v104.Color + *(float *)(v2 + 286024) + *(float *)(v2 + 286012);
    }
    v92 = *(_DWORD *)(v2 + 285868);
    *(_DWORD *)(v2 + 285896) = (__int64)v91;
    *(_DWORD *)(v2 + 285904) = v92 + (__int64)v91;
    *(_DWORD *)(v2 + 285908) = v103 + v88;
    goto LABEL_34;
  }
  if ( v77 == 1 )
  {
    v78 = *(_DWORD *)(v2 + 286044);
    if ( v78 )
    {
      if ( v78 == 1 )
      {
        v79 = *(_DWORD *)(v2 + 285872);
        v80 = (float)*(int *)(v2 + 285924) - *(float *)(v2 + 286012);
        v104.Color = v79 / 2;
        v101 = (__int64)(v80 - (double)(v79 / 2) - *(float *)(v2 + 286036));
        *(_DWORD *)(v2 + 285900) = v101;
        v104.Color = *(_DWORD *)(v2 + 285920) + 2;
        v81 = (__int64)((double)(int)v104.Color - *(float *)(v2 + 286012) - *(float *)(v2 + 286028));
        v82 = v81 + *(_DWORD *)(v2 + 285868);
        *(_DWORD *)(v2 + 285896) = v81;
        *(_DWORD *)(v2 + 285904) = v82;
        *(_DWORD *)(v2 + 285908) = v79 + v101;
      }
    }
    else
    {
      v83 = *(_DWORD *)(v2 + 285872);
      v104.Color = *(_DWORD *)(v2 + 285916) - v83 / 2;
      v84 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 286032) + *(float *)(v2 + 286012));
      HIDWORD(v84) = *(_DWORD *)(v2 + 285912);
      v102 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 286032) + *(float *)(v2 + 286012));
      *(_DWORD *)(v2 + 285900) = v84;
      v104.Color = HIDWORD(v84) - *(_DWORD *)(v2 + 285868) - 2;
      v85 = (__int64)((double)(int)v104.Color + *(float *)(v2 + 286024));
      v86 = *(_DWORD *)(v2 + 285868);
      *(_DWORD *)(v2 + 285896) = v85;
      *(_DWORD *)(v2 + 285904) = v86 + v85;
      *(_DWORD *)(v2 + 285908) = v83 + v102;
    }
  }
LABEL_34:
  (((UIScene *)(v2 + 285776)))->UIScene::UpdateLayout(100.0);
  (((CScreenMode *)(v2 + 285504)))->CScreenMode::SetProgress(0.0);
  (((CScreenMode *)(v2 + 285776)))->CScreenMode::SetProgress(0.0);
  (((CScreenMode *)(v2 + 285776)))->CScreenMode::SetProgress(0.0);
  v130 = 200;
  v129 = 250;
  v131 = 550;
  v132 = 300;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 289120));
  (((UIItem *)(v2 + 289120)))->UIItem::SetData(219);
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 286384));
  (((UIItem *)(v2 + 286384)))->UIItem::SetData(219);
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 287752));
  return (int)(((UIItem *)(v2 + 287752)))->UIItem::SetData(219);
}

// 0x004B1580
int UITitle_JDHY_ResetAndRefresh(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v4; // [esp+0x0] [ebp-0x8]

  v2 = v1;
  *(_DWORD *)(v1 + 286360) = 0;
  *(_DWORD *)(v1 + 285496) = 0;
  *(_DWORD *)(v1 + 285500) = 1;
  (((CScreenMode *)(v1 + 285224)))->CScreenMode::SetProgress(0.0);
  *(_DWORD *)(v2 + 286368) = 0;
  *(_DWORD *)(v2 + 286364) = 0;
  memset((void *)(v2 + 156324), 0, 0x24u);
  (((LineupUI *)v2))->LineupUI::UpdateProtectPanel(nVal);
  (((UITitle_JDHY *)v2))->UITitle_JDHY::ResetNoteState();
  return UITitle_JDHY_UpdateTextPosition(v4);
}

// 0x004B1C50
int UITitle_JDHY_UpdateButtonStates(int nVal)
{
  int v1; // ecx
  int v2; // ebp
  void (***v3)(_DWORD, _DWORD); // esi
  void (***v4)(_DWORD, _DWORD); // edi
  int v5; // ebx
  int result; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // ebp
  void ( ***v10)(_DWORD, int); // esi
  void ( ***v11)(_DWORD, int); // ecx
  int v12; // ebp
  int v13; // esi
  void ( ***v14)(_DWORD, int); // ecx
  int v15; // ebp
  int v16; // esi
  int v17; // [esp+0x54] [ebp-0x8]
  int v18; // [esp+0x58] [ebp-0x4]

  v17 = v1;
  v2 = 0;
  v3 = (void ( ***)(_DWORD, _DWORD))(v1 + 156720);
  do
  {
    (**(v3 - 86))(v3 - 86, 0);
    (**v3)((_DWORD)(v3), (_DWORD)(0));
    (*v3[38])(v3 + 38, 0);
    v4 = v3 + 76;
    v5 = 5;
    do
    {
      (*v4[190])(v4 + 190, 0);
      (**v4)((_DWORD)(v4), (_DWORD)(0));
      (*v4[458])(v4 + 458, 0);
      v4 += 38;
      --v5;
    }
    while ( v5 );
    (*v3[458])(v3 + 458, 0);
    (*v3[496])(v3 + 496, 0);
    (*v3[724])(v3 + 724, 0);
    (*v3[762])(v3 + 762, 0);
    result = v17;
    ++v2;
    v3 += 890;
    *(_BYTE *)(v17 + v2 + 156323) = 0;
  }
  while ( v2 < 36 );
  v7 = *(_DWORD *)(v17 + 286360);
  v18 = v7;
  if ( !__OFSUB__(v7, v7 + 5) )
  {
    v8 = v17 + 3560 * v7 + 156720;
    do
    {
      (**(void ( ***)(int, int))(v8 - 344))((int)(v8 - 344), (int)(1));
      (**(void ( ***)(int, int))v8)((int)(v8), (int)(1));
      (**(void ( ***)(int, int))(v8 + 152))((int)(v8 + 152), (int)(1));
      v9 = 0;
      v10 = (void ( ***)(_DWORD, int))(v8 + 304);
      do
      {
        v11 = v10 + 190;
        if ( *(_BYTE *)(v8 + v9 + 1824) )
        {
          (**v11)((_DWORD)((_DWORD)(v11)), (int)(1));
          (**v10)((_DWORD)((_DWORD)(v10)), (int)(1));
          (*v10[458])(v10 + 458, 1);
        }
        else
        {
          (**v11)((_DWORD)((_DWORD)(v11)), (int)(0));
          (**v10)((_DWORD)((_DWORD)(v10)), (int)(0));
          (*v10[458])(v10 + 458, 0);
        }
        ++v9;
        v10 += 38;
      }
      while ( v9 < 5 );
      (**(void ( ***)(int, int))(v8 + 1832))((int)(v8 + 1832), (int)(1));
      (**(void ( ***)(int, int))(v8 + 1984))((int)(v8 + 1984), (int)(1));
      v12 = v17;
      v13 = v18;
      v14 = (void ( ***)(_DWORD, int))(v8 + 2896);
      if ( *(_DWORD *)(v17 + 286364) == v18 )
      {
        (**v14)((_DWORD)((_DWORD)(v14)), (int)(1));
        v15 = 0;
        v16 = v8 + 304;
        do
        {
          (**(void ( ***)(bool))(v16 + 760))((bool)(*(_BYTE *)(v8 + v15 + 1824) != 0));
          (**(void ( ***)(int, _DWORD))v16)((int)(v16), (_DWORD)(0));
          ++v15;
          v16 += 152;
        }
        while ( v15 < 5 );
        v13 = v18;
        v12 = v17;
      }
      else
      {
        (**v14)((_DWORD)((_DWORD)(v14)), (int)(0));
      }
      result = (**(int ( ***)(int, int))(v8 + 3048))((int)(v8 + 3048), (int)(1));
      *(_BYTE *)(v13 + v12 + 156324) = 1;
      v8 += 3560;
      v18 = v13 + 1;
    }
    while ( v13 + 1 < *(_DWORD *)(v12 + 286360) + 5 );
  }
  return result;
}

// 0x004B1EA0
int UITitle_JDHY_ScrollDown(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // eax
  CScreenMode *v4; // eax
  int result; // eax
  int v6; // ebx
  int *v7; // esi
  int v8; // eax
  CScreenMode *Instance; // eax
  const void *v10; // [esp-0x4] [ebp-0x14]
  const void *v11; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]
  int v13; // [esp+0x4] [ebp-0xC]
  int nVala; // [esp+0x14] [ebp+0x4]

  v2 = v1;
  ++*(_DWORD *)(v1 + 286360);
  if ( (_BYTE)nVal )
  {
    v3 = *(_DWORD *)(v1 + 285500) + 1;
    *(_DWORD *)(v1 + 285500) = v3;
    if ( v3 > 32 )
      *(_DWORD *)(v1 + 285500) = 32;
    nVala = *(_DWORD *)(v1 + 285500) * *(_DWORD *)(v1 + 286352) - 28;
    *(_DWORD *)(v1 + 285496) = nVala;
    fProgress = (float)nVala;
    (((CScreenMode *)(v1 + 285224)))->CScreenMode::SetProgress(fProgress);
  }
  if ( *(int *)(v2 + 286360) <= 31 )
  {
    UITitle_JDHY_UpdateButtonStates(v13);
    v6 = 0;
    v7 = (int *)(v2 + 156364);
    do
    {
      v8 = (unsigned long)(*v7 - *(_DWORD *)(v2 + 286352));
      *v7 = v8;
      v7[2] = v8 + *(_DWORD *)(v2 + 286352);
      (((ChoseCompose *)v2))->ChoseCompose::LayoutItem(v6++, *(v7 - 1), *v7, v7[1], v7[2]);
      v7 += 890;
    }
    while ( v6 < 36 );
    v11 = (const void *)off_5D11E0;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v11, 1);
    LOBYTE(result) = 1;
  }
  else
  {
    *(_DWORD *)(v2 + 286360) = 31;
    v10 = off_5D11C4;
    v4 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v4))->CScreenMode::AudioSetPosition(v10, 1);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004B1FB0
int UITitle_JDHY_ScrollUp(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  CScreenMode *v6; // eax
  int result; // eax
  int *v8; // edi
  int v9; // eax
  CScreenMode *Instance; // eax
  const void *v11; // [esp-0x4] [ebp-0x14]
  const void *v12; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]
  int v14; // [esp+0x4] [ebp-0xC]

  v2 = v1;
  v3 = 0;
  --*(_DWORD *)(v1 + 286360);
  if ( (_BYTE)nVal )
  {
    v4 = *(_DWORD *)(v1 + 285500) - 1;
    *(_DWORD *)(v1 + 285500) = v4;
    if ( v4 <= 0 )
      *(_DWORD *)(v1 + 285500) = 0;
    v5 = *(_DWORD *)(v1 + 285500) * *(_DWORD *)(v1 + 286352) - 28;
    *(_DWORD *)(v1 + 285496) = v5;
    if ( v5 < 0 )
      *(_DWORD *)(v1 + 285496) = 0;
    fProgress = (float)*(int *)(v1 + 285496);
    (((CScreenMode *)(v1 + 285224)))->CScreenMode::SetProgress(fProgress);
  }
  if ( *(int *)(v2 + 286360) >= 0 )
  {
    UITitle_JDHY_UpdateButtonStates(v14);
    v8 = (int *)(v2 + 156364);
    do
    {
      v9 = *(_DWORD *)(v2 + 286352) + *v8;
      *v8 = v9;
      v8[2] = v9 + *(_DWORD *)(v2 + 286352);
      (((ChoseCompose *)v2))->ChoseCompose::LayoutItem(v3++, *(v8 - 1), *v8, v8[1], v8[2]);
      v8 += 890;
    }
    while ( v3 < 36 );
    v12 = (const void *)off_5D11E0;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v12, 1);
    LOBYTE(result) = 1;
  }
  else
  {
    *(_DWORD *)(v2 + 286360) = 0;
    v11 = off_5D11C4;
    v6 = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)v6))->CScreenMode::AudioSetPosition(v11, 1);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004B20C0
int UITitle_JDHY_HandleInput(int nVal)
{
  int result; // eax
  _BYTE *v2; // ecx
  _BYTE *v3; // esi
  char *v4; // ebp
  const RECT *i; // edi
  int v6; // ebx
  int j; // edi
  int v8; // eax
  void (***v9)(_DWORD, _DWORD); // edi
  int v10; // ebx
  int v11; // ebx
  int k; // edi
  int v13; // eax
  int v14; // ecx
  Actor *SaveDataManager; // eax
  int SaveData; // edi
  int v17; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v19; // eax
  CScreenMode *v20; // eax
  const void *v21; // [esp-0x8] [ebp-0x70]
  const void *v22; // [esp-0x8] [ebp-0x70]
  const void *v23; // [esp-0x8] [ebp-0x70]
  POINT pt; // [esp+0x10] [ebp-0x58] BYREF

  v3 = (_BYTE *)v2;
  LOBYTE(result) = (unsigned long)v2[287725];
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = (unsigned long)v2[289093];
    if ( !(_BYTE)result )
    {
      LOBYTE(result) = (unsigned long)v2[290461];
      if ( !(_BYTE)result )
      {
        result = (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
        v4 = 0;
        for ( i = (const RECT *)(v3 + 156360); ; i = (const RECT *)((char *)i + 3560) )
        {
          LOBYTE(result) = (unsigned long)v4[(_DWORD)v3 + 156324];
          if ( (_BYTE)result )
          {
            result = PtInRect(i, pt);
            if ( result )
            {
              if ( g_Input.KeyInfo[0].PressTime == 1 )
              {
                result = g_Input.KeyInfo[0].Data & 0xF;
                if ( result == 1 )
                {
                  if ( v3[*((_DWORD *)v3 + 71591) + 156324] )
                  {
                    v6 = 0;
                    for ( j = 0; j < 760; j += 152 )
                    {
                      v8 = 3560 * *((_DWORD *)v3 + 71591);
                      if ( v3[v8 + 158544 + v6] )
                      {
                        (**(void ( ***)(int, int))&v3[j + 157024 + v8])((int)((int)&v3[j + 157024 + v8]), (int)(1));
                        (**(void ( ***)(int, _DWORD))&v3[3560 * *((_DWORD *)v3 + 71591) + 157784 + j])((int)((int)&v3[3560 * *((_DWORD *)v3 + 71591) + 157784 + j]), (_DWORD)(0));
                      }
                      ++v6;
                    }
                  }
                  *((_DWORD *)v3 + 71591) = (unsigned long)v4;
                  v9 = (void ( ***)(_DWORD, _DWORD))(v3 + 159616);
                  v10 = 36;
                  do
                  {
                    sub_445E50((int)(v9 - 810));
                    (**v9)((_DWORD)(v9), (_DWORD)(0));
                    v9 += 890;
                    --v10;
                  }
                  while ( v10 );
                  sub_445E50((int)&v3[3560 * *((_DWORD *)v3 + 71591) + 156376]);
                  (**(void ( ***)(int, int))&v3[3560 * *((_DWORD *)v3 + 71591) + 159616])((int)((int)&v3[3560 * *((_DWORD *)v3 + 71591) + 159616]), (int)(1));
                  v11 = 0;
                  for ( k = 0; k < 760; k += 152 )
                  {
                    v13 = 3560 * *((_DWORD *)v3 + 71591);
                    if ( v3[v13 + 158544 + v11] )
                    {
                      (**(void ( ***)(int, _DWORD))&v3[k + 157024 + v13])((int)((int)&v3[k + 157024 + v13]), (_DWORD)(0));
                      (**(void ( ***)(int, int))&v3[3560 * *((_DWORD *)v3 + 71591) + 157784 + k])((int)((int)&v3[3560 * *((_DWORD *)v3 + 71591) + 157784 + k]), (int)(1));
                    }
                    ++v11;
                  }
                  v14 = (unsigned long)off_5D11B8;
                  goto LABEL_37;
                }
                if ( result == 2 )
                  break;
              }
            }
          }
          if ( (int)++v4 >= 36 )
            return result;
        }
        *((_DWORD *)v3 + 71592) = (unsigned long)v4;
        SaveDataManager = (Actor *)GetSaveDataManager();
        SaveData = (((Actor *)SaveDataManager))->Actor::LoadSaveData(v4);
        v17 = *((_DWORD *)v3 + 71593);
        if ( v17 )
        {
          result = v17 - 1;
          if ( result )
            return result;
          if ( UIScene::ProcessInput("m04", 0) || UIScene::ProcessInput("m05", 0) )
          {
            sprintf(v3 + 104, "\\n        %s", (const char *)&dword_DDC13C);
            SetEnable((UICaption *)(v3 + 288208));
            (((UIRoleSelect *)(v3 + 287752)))->UIRoleSelect::SetByte(1);
            v21 = (const void *)off_5D11C0;
            Instance = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v21, 1);
            return result;
          }
          if ( SaveData )
          {
            sprintf(v3 + 104, "\\n      %s", (const char *)&dword_DD4E3C);
LABEL_34:
            SetEnable((UICaption *)(v3 + 286840));
            (((UIRoleSelect *)(v3 + 286384)))->UIRoleSelect::SetByte(0);
            (((GRPinput *)&g_Input))->GRPinput::Reset();
            v22 = (const void *)off_5D11C0;
            v19 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v19))->CScreenMode::AudioSetPosition(v22, 1);
            return result;
          }
          sprintf(v3 + 104, "\\n %s", (const char *)&dword_DD4F3C);
          SetEnable((UICaption *)(v3 + 288208));
          (((UIRoleSelect *)(v3 + 287752)))->UIRoleSelect::SetByte(1);
        }
        else
        {
          if ( SaveData )
          {
            sprintf(v3 + 104, "\\n      %s", (const char *)&dword_DD513C);
            goto LABEL_34;
          }
          sprintf(v3 + 104, "\\n %s", (const char *)&dword_DD523C);
          SetEnable((UICaption *)(v3 + 286840));
          (((UIRoleSelect *)(v3 + 286384)))->UIRoleSelect::SetByte(0);
        }
        (((GRPinput *)&g_Input))->GRPinput::Reset();
        v14 = (unsigned long)off_5D11C0;
LABEL_37:
        v23 = (const void *)v14;
        v20 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v20))->CScreenMode::AudioSetPosition(v23, 1);
      }
    }
  }
  return result;
}

// 0x004B2D20
int UITitle_JDHY_HandleNavigation(int nVal)
{
  int result; // eax
  int v2; // ecx
  int v3; // esi
  int v4; // eax
  void (***v5)(_DWORD, _DWORD); // edi
  int v6; // ebx
  int v7; // eax
  void (***v8)(_DWORD, _DWORD); // edi
  int v9; // ebx
  Actor *SaveDataManager; // eax
  int SaveData; // edi
  int v12; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  char *v16; // [esp-0x8] [ebp-0x68]
  const void *v17; // [esp-0x8] [ebp-0x68]
  const void *v18; // [esp-0x8] [ebp-0x68]
  const void *v19; // [esp-0x8] [ebp-0x68]

  v3 = v2;
  LOBYTE(result) = *(_BYTE *)(v2 + 287725);
  if ( !(_BYTE)result )
  {
    LOBYTE(result) = *(_BYTE *)(v2 + 289093);
    if ( !(_BYTE)result )
    {
      LOBYTE(result) = *(_BYTE *)(v2 + 290461);
      if ( !(_BYTE)result )
      {
        result = g_Input.KeyInfo[5].PressTime;
        if ( g_Input.KeyInfo[5].PressTime == 1 )
        {
          v4 = *(_DWORD *)(v2 + 286364) + 1;
          *(_DWORD *)(v2 + 286364) = v4;
          if ( v4 > 35 )
            *(_DWORD *)(v2 + 286364) = 35;
          v5 = (void ( ***)(_DWORD, _DWORD))(v2 + 159616);
          v6 = 36;
          do
          {
            sub_445E50((int)(v5 - 810));
            (**v5)((_DWORD)(v5), (_DWORD)(0));
            v5 += 890;
            --v6;
          }
          while ( v6 );
          if ( *(_DWORD *)(v3 + 286364) >= *(_DWORD *)(v3 + 286360) + 5 )
            UITitle_JDHY_ScrollDown(1);
LABEL_11:
          sub_445E50(v3 + 3560 * *(_DWORD *)(v3 + 286364) + 156376);
          return (**(int ( ***)(int, int))(v3 + 3560 * *(_DWORD *)(v3 + 286364) + 159616))((int)(v3 + 3560 * *(_DWORD *)(v3 + 286364) + 159616), (int)(1));
        }
        if ( g_Input.KeyInfo[4].PressTime == 1 )
        {
          v7 = *(_DWORD *)(v2 + 286364) - 1;
          *(_DWORD *)(v2 + 286364) = v7;
          if ( v7 < 0 )
          {
            (((CScreenMode *)(v2 + 285224)))->CScreenMode::SetProgress(0.0);
            *(_DWORD *)(v3 + 286364) = 0;
          }
          v8 = (void ( ***)(_DWORD, _DWORD))(v3 + 159616);
          v9 = 36;
          do
          {
            sub_445E50((int)(v8 - 810));
            (**v8)((_DWORD)(v8), (_DWORD)(0));
            v8 += 890;
            --v9;
          }
          while ( v9 );
          if ( *(_DWORD *)(v3 + 286364) < *(_DWORD *)(v3 + 286360) )
            UITitle_JDHY_ScrollUp(1);
          goto LABEL_11;
        }
        if ( g_Input.KeyInfo[10].PressTime == 1 )
        {
          if ( g_ScriptSystemData.m_nGameMode != 2 || g_bRoleSystem_5CEFA9 )
            return (*(int ( **)(int, int, int *, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1001, &byte_A00704, 0);
          sprintf((char *const)(v2 + 104), "\\n        %s", (const char *)&dword_DD8A3C);
          SetEnable((UICaption *)(v3 + 288208));
          (((UIRoleSelect *)(v3 + 287752)))->UIRoleSelect::SetByte(1);
          goto LABEL_40;
        }
        if ( g_Input.KeyInfo[9].PressTime == 1 )
          return (*(int ( **)(int, int, int *, _DWORD))(*(_DWORD *)v2 + 24))(v2, 1001, &byte_A00705, 0);
        if ( g_Input.KeyInfo[7].PressTime == 1 )
        {
          v16 = (char *)*(char **)(v2 + 286364);
          *(_DWORD *)(v2 + 286368) = (_DWORD)v16;
          SaveDataManager = (Actor *)GetSaveDataManager();
          SaveData = (((Actor *)SaveDataManager))->Actor::LoadSaveData(v16);
          v12 = *(_DWORD *)(v3 + 286372);
          if ( v12 )
          {
            result = v12 - 1;
            if ( result )
              return result;
            if ( UIScene::ProcessInput("m04", 0) || UIScene::ProcessInput("m05", 0) )
            {
              sprintf((char *const)(v3 + 104), "\\n        %s", (const char *)&dword_DDC13C);
              SetEnable((UICaption *)(v3 + 288208));
              (((UIRoleSelect *)(v3 + 287752)))->UIRoleSelect::SetByte(1);
              v17 = (const void *)off_5D11C0;
              Instance = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v17, 1);
              return result;
            }
            if ( SaveData )
            {
              sprintf((char *const)(v3 + 104), "\\n      %s", (const char *)&dword_DD4E3C);
LABEL_37:
              SetEnable((UICaption *)(v3 + 286840));
              (((UIRoleSelect *)(v3 + 286384)))->UIRoleSelect::SetByte(0);
              (((GRPinput *)&g_Input))->GRPinput::Reset();
              v18 = (const void *)off_5D11C0;
              v14 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(v18, 1);
              return result;
            }
            sprintf((char *const)(v3 + 104), "\\n %s", (const char *)&dword_DD4F3C);
            SetEnable((UICaption *)(v3 + 288208));
            (((UIRoleSelect *)(v3 + 287752)))->UIRoleSelect::SetByte(1);
          }
          else
          {
            if ( SaveData )
            {
              sprintf((char *const)(v3 + 104), "\\n      %s", (const char *)&dword_DD513C);
              goto LABEL_37;
            }
            sprintf((char *const)(v3 + 104), "\\n %s", (const char *)&dword_DD523C);
            SetEnable((UICaption *)(v3 + 286840));
            (((UIRoleSelect *)(v3 + 286384)))->UIRoleSelect::SetByte(0);
          }
          (((GRPinput *)&g_Input))->GRPinput::Reset();
LABEL_40:
          v19 = (const void *)off_5D11C0;
          v15 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(v19, 1);
        }
      }
    }
  }
  return result;
}

// 0x004B3270
int UITitle_JDHY_UpdateTextPosition(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // esi
  unsigned int v4; // eax
  int v5; // ebp
  unsigned int v6; // ecx
  int *v7; // edi
  int v8; // eax
  void (***v9)(_DWORD, _DWORD); // edi
  int v10; // ebx
  int v11; // ebx
  int i; // edi
  int result; // eax
  float fProgress; // [esp+0x0] [ebp-0x18]
  int v15; // [esp+0x4] [ebp-0x14]
  BYTE Data[4]; // [esp+0x14] [ebp-0x4] BYREF

  v2 = 0;
  v3 = v1;
  *(_DWORD *)Data = 0;
  ReadRegistryString("SOFTWARE\\SOFTSTAR\\PAL3_SAVE", "SEEK", (char *)Data);
  v4 = *(_DWORD *)Data;
  if ( *(_DWORD *)Data >= 0x24u )
  {
    v4 = 35;
    *(_DWORD *)Data = 35;
  }
  v5 = 0;
  v6 = v4;
  if ( v4 <= 4 )
  {
    v4 = 0;
    *(_DWORD *)Data = 0;
  }
  else
  {
    v5 = 4;
  }
  *(_DWORD *)(v3 + 286368) = v6;
  *(_DWORD *)(v3 + 286360) = v4 - v5;
  *(_DWORD *)(v3 + 286364) = v6;
  *(_DWORD *)(v3 + 285500) = v6 - v5;
  if ( (int)(v6 - v5) < 31 )
  {
    *(_DWORD *)(v3 + 285496) = (v6 - v5) * *(_DWORD *)(v3 + 286352);
  }
  else
  {
    *(_DWORD *)(v3 + 285500) = 31;
    *(_DWORD *)(v3 + 285496) = (__int64)*(float *)(v3 + 285452);
  }
  fProgress = (float)*(int *)(v3 + 285496);
  (((CScreenMode *)(v3 + 285224)))->CScreenMode::SetProgress(fProgress);
  v7 = (int *)(v3 + 156364);
  do
  {
    v8 = (unsigned long)(*v7 - *(_DWORD *)(v3 + 286352) * (*(_DWORD *)Data - v5));
    *v7 = v8;
    v7[2] = *(_DWORD *)(v3 + 286352) + v8;
    (((ChoseCompose *)v3))->ChoseCompose::LayoutItem(v2++, *(v7 - 1), *v7, v7[1], v7[2]);
    v7 += 890;
  }
  while ( v2 < 36 );
  UITitle_JDHY_UpdateButtonStates(v15);
  v9 = (void ( ***)(_DWORD, _DWORD))(v3 + 159616);
  v10 = 36;
  do
  {
    sub_445E50((int)(v9 - 810));
    (**v9)((_DWORD)(v9), (_DWORD)(0));
    v9 += 890;
    --v10;
  }
  while ( v10 );
  sub_445E50(v3 + 3560 * *(_DWORD *)(v3 + 286364) + 156376);
  (**(void ( ***)(int, int))(v3 + 3560 * *(_DWORD *)(v3 + 286364) + 159616))((int)(v3 + 3560 * *(_DWORD *)(v3 + 286364) + 159616), (int)(1));
  v11 = 0;
  for ( i = 0; i < 760; i += 152 )
  {
    result = 3560 * *(_DWORD *)(v3 + 286364);
    if ( *(_BYTE *)(result + v11 + v3 + 158544) )
    {
      (**(void ( ***)(int, _DWORD))(i + result + v3 + 157024))((int)(i + result + v3 + 157024), (_DWORD)(0));
      result = (**(int ( ***)(int, int))(i + 3560 * *(_DWORD *)(v3 + 286364) + v3 + 157784))((int)(i + 3560 * *(_DWORD *)(v3 + 286364) + v3 + 157784), (int)(1));
    }
    ++v11;
  }
  return result;
}

// 0x004B4830
char IsVisible(RenderTarget *_this)
{
  return _this->m_bVisible;
}

// 0x004B65E0
// Microsoft VisualC 2-14/net runtime
void InitRenderTarget3Singleton()
{
  operator delete((void *)*(&dword_DE6A30 + 4));
  *(&dword_DE6A30 + 4) = 0;
  *(&dword_DE6A30 + 5) = 0;
  *(&dword_DE6A30 + 6) = 0;
}

// 0x004B73D0
int CEffMgr_SetComponent(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 92) = nVal;
  return result;
}

// 0x004B74A0
int UI3DModelNode_UI3DModelNode(int nVal)
{
  PAL3VisNode *v1; // ecx
  PAL3VisNode *v2; // esi

  v2 = (PAL3VisNode *)v1;
  v1->PAL3VisNode::PAL3VisNode();
  v2[2].TimeScale = 0.0;
  v2[1].children.m_Head = 0;
  memset(&v2[1].children.m_Tail, 0, 0x40u);
  v2[1].next = 0;
  v2[1].pFather = 0;
  v2[2].bDoShadow = 0;
  v2[2].bShow = 0;
  v2[2].pCullObj = 0;
  return (int)v2;
}

// 0x004B7560
int todo_004B7560(Actor *_this, int nArg)
{
  float m_fMatrixParamB; // ecx

  m_fMatrixParamB = _this->m_fMatrixParamB;
  if ( m_fMatrixParamB != 0.0f )
    (*(void ( **)(float, _DWORD))(*(_DWORD *)LODWORD(m_fMatrixParamB) + 16))(
      _pal3_coerce_f32(LODWORD(m_fMatrixParamB)),
      0);
  (*(void ( **)(Actor *, _DWORD))(*(_DWORD *)&_this->m_actarray_type + 12))(_this, 0);
  return 1;
}

// 0x004B7590
void RenderActorTransform2(Actor *_this, int nFlag)
{
  int v3; // eax
  float *p_z; // ebx
  gbRenderInfoObj *v5; // edi
  gbRenderEffect *v6; // eax
  gbMatrix4 *Top; // eax
  const gbVec3D *v8; // [esp+0x0] [ebp-0x24]
  gbVec3D *v9; // [esp+0x4] [ebp-0x20]

  v3 = *(_DWORD *)&_this->m_bUIFlagA;
  _this->m_nMatrixParam = 1;
  p_z = (float *)&_this->m_vecTargetPos.z;
  _this->m_vecTargetPos.z = *((float *)&_this->m_szText + v3 + 1);
  v5 = (((gbSceneGraph *)gfxMgr->pSceneGraph))->gbSceneGraph::NewOneRenderObj((gbVisNode *)_this);
  v5->Flags = 0;
  v5->Param = 0;
  v6 = (gbRenderEffect *)(*(gbRenderEffect **)&_this->m_szText);
  v5->pTexArray = (gbTextureArray *)p_z;
  v5->pEffect = v6;
  Top = (((gbMatrixStack *)gfxMgr->pMatrixStack[1]))->gbMatrixStack::GetTop();
  (((gbMatrix4 *)Top))->gbMatrix4::Transform(v8, v9);
  v5->Priority = 1;
  v5->Z = 0.0f;
}

// 0x004B7650
void todo_004B7650(Actor *_this, int nFlag)
{
  gbMatrixStack *v2; // edi
  gbGeomQuad *v4; // ebx
  int v5; // ebp
  gbMatrix4 *Top; // eax
  float m_fMatrixE; // ecx
  double v8; // st7
  gbDynVertBuf *DynVertBuf; // ebx
  float v10; // eax
  double v11; // st7
  double v12; // st6
  int v13; // eax
  gbRenderEffect *v14; // [esp+0x8] [ebp-C0h]
  float v15; // [esp+0x20] [ebp-A8h]
  float v16; // [esp+0x20] [ebp-A8h]
  float v17; // [esp+0x20] [ebp-A8h]
  struct gbVec3D v18; // [esp+0x24] [ebp-A4h] BYREF
  float v19; // [esp+0x30] [ebp-0x98]
  struct gbVec3D v20; // [esp+0x34] [ebp-0x94] BYREF
  struct gbGeomQuad v21; // [esp+0x40] [ebp-0x88] BYREF
  struct gbTextureArray v22; // [esp+0x84] [ebp-0x44] BYREF

  v2 = gfxMgr->pMatrixStack[1];
  (((gbMatrixStack *)v2))->gbMatrixStack::Push();
  (((gbMatrixStack *)v2))->gbMatrixStack::LoadMatrix((gbMatrix4 *)(nFlag + 32));
  v4 = (gbGeomQuad *)&v21;
  v5 = 4;
  do
  {
    v4 = (gbGeomQuad *)((char *)v4 + 12);
    --v5;
  }
  while ( v5 );
  Top = (((gbMatrixStack *)v2))->gbMatrixStack::GetTop();
  m_fMatrixE = _this->m_fMatrixE;
  memset(&v18, 0, sizeof(v18));
  memset(&v20, 0, sizeof(v20));
  v19 = 40.0f;
  v15 = 50.0f;
  switch ( LODWORD(m_fMatrixE) )
  {
    case 1:
      v19 = 12.0f;
      v15 = 14.0f;
      break;
    case 2:
      v19 = 12.0f;
      v15 = 20.0f;
      v20.y = 30.0;
      break;
    case 3:
      v19 = 70.0f;
      v15 = 80.0f;
      break;
    case 4:
      v20.y = 10.0;
      v20.x = -3.4000001;
      v20.z = -3.4000001;
      v19 = 8.0f;
      v15 = 8.0f;
      break;
    default:
      break;
  }
  (((gbMatrix4 *)Top))->gbMatrix4::Transform(&v20, &v18);
  v8 = v19 * 0.5;
  v21.color = -1;
  v21.vec[3].z = v18.z;
  v21.vec[3].x = v18.x - v8;
  v21.vec[0].y = v18.y;
  v21.vec[0].z = v18.z;
  v21.vec[1].y = v18.y;
  v16 = v18.y + v15;
  v21.vec[3].y = v16;
  v21.vec[0].x = v21.vec[3].x;
  v21.vec[2].y = v16;
  v21.su = 0.0;
  v21.sv = 0.0;
  v21.eu = 1.0;
  v21.ev = 1.0;
  v21.vec[1].z = v18.z;
  v21.vec[2].z = v18.z;
  v21.vec[1].x = v8 + v18.x;
  v21.vec[2].x = v21.vec[1].x;
  (((gbMatrixStack *)v2))->gbMatrixStack::LoadIdentity();
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v21, 1, *(gbRenderEffect **)&_this->m_szText, (gbTextureArray *)&_this->m_vecTargetPos.z);
  if ( LODWORD(_this->m_fMatrixParamA) )
  {
    v10 = _this->m_fMatrixE;
    if ( v10 == 0.0f )
    {
      v18.y = v18.y - 32.0;
      v11 = 50.0;
      v12 = 85.0;
    }
    else if ( LODWORD(v10) == 4 )
    {
      v11 = 15.0;
      v12 = 25.0;
      v18.y = v18.y - 10.0;
    }
    else
    {
      v18.y = v18.y - 22.0;
      v11 = 30.0;
      v12 = 50.0;
    }
    v21.vec[0].y = v18.y;
    v21.vec[3].z = v18.z;
    v21.vec[0].z = v18.z;
    v19 = v18.x - v11;
    v21.vec[3].x = v19;
    v21.vec[0].x = v19;
    v21.vec[1].y = v18.y;
    v21.vec[1].z = v18.z;
    v17 = v12 + v18.y;
    v21.vec[3].y = v17;
    v21.vec[2].z = v18.z;
    v21.vec[2].y = v17;
    v21.vec[1].x = v11 + v18.x;
    v21.vec[2].x = v21.vec[1].x;
    v13 = rand();
    v22.nTex = 1;
    v14 = (gbRenderEffect *)(*(gbRenderEffect **)&_this->m_szText);
    LOBYTE(v21.color) = v13 % 55 - 56;
    BYTE1(v21.color) = v21.color;
    BYTE2(v21.color) = v21.color;
    v22.pTexPt[0] = (gbTexture *)LODWORD(_this->m_fMatrixParamA);
    (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v21, 1, v14, &v22);
  }
  (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
}

// 0x004B7980
void LoadActorVisual(Actor *_this, int nVisualId)
{
  const char *v3; // ebp
  int v4; // eax
  char *v5; // edi
  int v6; // esi
  gbTexture *v7; // eax
  char *v8; // eax
  char *v9; // edi
  gbGeomNode *v10; // ecx
  gbTexture *v11; // eax
  char *Format[6]; // [esp+0x10] [ebp-0x128]
  char Buffer[260]; // [esp+0x28] [ebp-0x110] BYREF
  int v14; // [esp+0x134] [ebp-0x4]

  *(_DWORD *)&_this->m_szText = (((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0);
  Format[0] = "EffectScn\\Fire1\\torch%02d.tga";
  Format[1] = "EffectScn\\Fire2\\%02d.tga";
  Format[2] = "EffectScn\\Candle\\%03d.tga";
  Format[3] = "EffectScn\\Fire4\\%02d.tga";
  Format[4] = "EffectScn\\Candle\\%03d.tga";
  v3 = Format[nVisualId];
  v4 = 0;
  v5 = (char *)(&_this->m_szText + 4);
  do
  {
    v6 = v4 + 1;
    sprintf(Buffer, v3, v4 + 1);
    v7 = (gbTexture *)gfxMgr->NewTexture((const char *)Buffer);
    *(_DWORD *)v5 = (_DWORD)v7;
    (((gbTexture *)v7))->gbTexture::LoadTexture(1);
    v4 = v6;
    v5 += 4;
  }
  while ( v6 < 16 );
  *(_DWORD *)&_this->m_bUIFlagA = 0;
  if ( nVisualId == 2 || nVisualId == 4 || !nVisualId )
  {
    v8 = (char *)operator new(0x118u);
    v9 = (char *)v8;
    Format[5] = (char)v8;
    v14 = 0;
    if ( v8 )
    {
      v8->gbGeomNode::gbGeomNode();
      v10 = (gbGeomNode *)v9;
    }
    else
    {
      v10 = 0;
    }
    v14 = -1;
    LODWORD(_this->m_fMatrixParamB) = (unsigned long)v10;
    if ( nVisualId == 2 )
    {
      (((gbGeomNode *)v10))->gbGeomNode::LoadFromFile("EffectScn\\Candle\\Candle.pol", 0, 0);
    }
    else if ( nVisualId == 4 )
    {
      (((gbGeomNode *)v10))->gbGeomNode::LoadFromFile("EffectScn\\Lamp\\Lamp.pol", 0, 0);
    }
    v11 = (gbTexture *)gfxMgr->NewTexture("effect\\Flare4.bmp");
    LODWORD(_this->m_fMatrixParamA) = (unsigned long)v11;
    (((gbTexture *)v11))->gbTexture::LoadTexture(1);
  }
  LODWORD(_this->m_fMatrixE) = nVisualId;
}

// 0x004B7AF0
void ReleaseAllTextures(UI3DModelNode *_this)
{
  gbRefObject *m_nTodo_064; // ecx
  gbRefObject *m_nTodo_0EC; // ecx
  int *m_nTodo_068; // esi
  int v5; // ebp
  void ( ***m_nTodo_0F0)(_DWORD, int); // ecx

  m_nTodo_064 = (gbRefObject *)_this->m_nTodo_064;
  if ( m_nTodo_064 )
  {
    (((gbRefObject *)m_nTodo_064))->gbRefObject::Release();
    _this->m_nTodo_064 = 0;
  }
  m_nTodo_0EC = (gbRefObject *)_this->m_nTodo_0EC;
  if ( m_nTodo_0EC )
  {
    (((gbRefObject *)m_nTodo_0EC))->gbRefObject::Release();
    _this->m_nTodo_0EC = 0;
  }
  m_nTodo_068 = _this->m_nTodo_068;
  v5 = 16;
  do
  {
    if ( *m_nTodo_068 )
    {
      (((gbRefObject *)*m_nTodo_068))->gbRefObject::Release();
      *m_nTodo_068 = 0;
    }
    ++m_nTodo_068;
    --v5;
  }
  while ( v5 );
  m_nTodo_0F0 = (void ( ***)(_DWORD, int))_this->m_nTodo_0F0;
  if ( m_nTodo_0F0 )
  {
    (**m_nTodo_0F0)((_DWORD)((_DWORD)(m_nTodo_0F0)), (int)(1));
    _this->m_nTodo_0F0 = 0;
  }
}

// 0x004B7C30
int ScreenEffectNode_ScreenEffectNode(int nVal)
{
  PAL3VisNode *v1; // ecx
  int v2; // edi
  int v3; // esi
  int v4; // ebx
  int v5; // esi
  int v6; // ebx

  v2 = (int)v1;
  v1->PAL3VisNode::PAL3VisNode();
  v3 = v2 + 172;
  *(_DWORD *)(v2 + 160) = 0;
  v4 = 4;
  do
  {
    v3 += 12;
    --v4;
  }
  while ( v4 );
  v5 = v2 + 240;
  v6 = 12;
  do
  {
    v5 += 68;
    --v6;
  }
  while ( v6 );
  return v2;
}

// 0x004B7D30
void todo_004B7D30(Actor *_this, int nParam)
{
  gbTexture *v3; // eax
  gbTexture *v4; // eax
  gbGeomNode *v5; // eax
  gbGeomNode *v6; // edi
  gbGeomNode *v7; // ecx
  char *v8; // eax
  int v9; // ecx
  OpenBaseFile v10; // [esp+0x24] [ebp-0x14] BYREF
  gbGeomNode *v11; // [esp+0x28] [ebp-0x10]
  int v12; // [esp+0x34] [ebp-0x4]

  v12 = 0;
  v3 = (gbTexture *)gfxMgr->NewTexture("Effect\\save.tga");
  LODWORD(_this->m_fAnimParam) = (unsigned long)v3;
  (((gbTexture *)v3))->gbTexture::LoadTexture(1);
  LODWORD(_this->m_vecTargetPos.x) = 1;
  v4 = (gbTexture *)gfxMgr->NewTexture("Effect\\ray.tga");
  LODWORD(_this->m_vecTargetPos.y) = (unsigned long)v4;
  (((gbTexture *)v4))->gbTexture::LoadTexture(1);
  LODWORD(_this->m_vecTargetPos.z) = (((gbEffectMgr *)gfxMgr->pEffectMgr))->gbEffectMgr::NewRenderEffect("gfxscript\\AdditiveBlend.gbf", 0);
  _this->m_fInterpStart = -30.0;
  _this->m_fInterpEnd = 2.0;
  _this->m_nInterpFrames = -1041235968;
  _this->m_fActionSpeed = -30.0;
  _this->m_nInterpCurrent = 0x40000000;
  _this->m_nInterpState = 1106247680;
  _this->m_fInterpSpeed = 30.0;
  _this->m_nModelLoadState = 0x40000000;
  _this->m_nState = 1106247680;
  _this->m_pRoleObj = 1106247680;
  _this->m_nPathEnabled = 0x40000000;
  *(_DWORD *)&_this->m_fScale = -1041235968;
  *(_DWORD *)&_this->m_fMatrixB = 0;
  _this->m_fMatrixA = 0.0;
  _this->m_nMatrixParam = 1065353216;
  _this->m_fMatrixC = 1.0;
  _this->m_fMatrixParamA = NAN;
  v5 = (gbGeomNode *)operator new(0x118u);
  v6 = (gbGeomNode *)v5;
  v11 = (gbGeomNode *)v5;
  LOBYTE(v12) = 1;
  if ( v5 )
  {
    v5->gbGeomNode::gbGeomNode();
    v7 = (gbGeomNode *)v6;
  }
  else
  {
    v7 = 0;
  }
  LOBYTE(v12) = 0;
  LODWORD(_this[1].m_fMatrixParamA) = (unsigned long)v7;
  (((gbGeomNode *)v7))->gbGeomNode::LoadFromFile("effect\\stone.pol", 0, 0);
  *(_DWORD *)&_this->m_bUIFlagA = 0;
  RenderTarget3::GenerateRingMesh(40.0, 24.0, 1112014848, 12, (int)&_this->m_fMatrixParamB, 12, 3.0);
  v8 = (char *)&_this->m_szTexture[25];
  v9 = 12;
  do
  {
    v8[1] = -11;
    *v8 = -68;
    *(v8 - 1) = 28;
    v8[2] = -1;
    *(_DWORD *)(v8 - 5) = 1064346583;
    v8 += 68;
    --v9;
  }
  while ( v9 );
  v12 = -1;
  ((OpenNULLFile *)&v10)->OpenNULLFile::OpenNULLFile();
}

// 0x004B7F00
int UINote_ReleaseResources(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // esi
  int ( ***v3)(_DWORD, int); // ecx
  int result; // eax
  gbRefObject *v5; // ecx
  gbRefObject *v6; // ecx
  gbRefObject *v7; // ecx

  v2 = (_DWORD *)v1;
  v3 = (int ( ***)(_DWORD, int))v1[264];
  if ( v3 )
  {
    result = (**v3)((_DWORD)((_DWORD)(v3)), (int)(1));
    v2[264] = 0;
  }
  v5 = (gbRefObject *)v2[42];
  if ( v5 )
  {
    (((gbRefObject *)v5))->gbRefObject::Release();
    ((int *)v2)[42] = 0;
  }
  v6 = (gbRefObject *)v2[41];
  if ( v6 )
  {
    (((gbRefObject *)v6))->gbRefObject::Release();
    ((int *)v2)[41] = 0;
  }
  v7 = (gbRefObject *)v2[24];
  if ( v7 )
  {
    (((gbRefObject *)v7))->gbRefObject::Release();
    ((int *)v2)[24] = 0;
  }
  v2[40] = 0;
  return result;
}

// 0x004B7F80
int Object3D_RenderTransformed(int nVal)
{
  int v1; // ecx
  int v2; // edi
  gbMatrixStack *v3; // esi
  float v4; // st7
  float v6; // [esp+0xC] [ebp-0x1C]
  float v7; // [esp+0xC] [ebp-0x1C]
  struct gbVec3D v8; // [esp+0x1C] [ebp-0xC] BYREF

  v2 = v1;
  if ( *(_DWORD *)(v1 + 1056) )
  {
    v3 = gfxMgr->pMatrixStack[1];
    (((gbMatrixStack *)v3))->gbMatrixStack::Push();
    v6 = sin(*(float *)(v2 + 92) * 3.0f) * 8.0f + 25.0f;
    (((gbMatrixStack *)v3))->gbMatrixStack::Translate(0.0,   v6,   0.0);
    v4 = *(float *)(v2 + 92) * 3.0f;
    v8.x = 0.0;
    v8.y = 1.0;
    v7 = v4;
    v8.z = 0.0;
    (((gbMatrixStack *)v3))->gbMatrixStack::Rotate(v7,  v8);
    (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(v2 + 1056) + 16))(*(_DWORD *)(v2 + 1056), 0);
    (((gbMatrixStack *)v3))->gbMatrixStack::Pop();
  }
  (*(void ( **)(int, _DWORD))(*(_DWORD *)v2 + 12))(v2, 0);
  return 1;
}

// 0x004B80C0
void RenderActorTransform(Actor *_this, int nRenderFlag)
{
  gbMatrixStack *v2; // edi
  double v4; // st7
  gbDynVertBuf *DynVertBuf; // ebx
  float z; // eax
  float v7; // [esp+0x10] [ebp-0x68]
  struct gbVec3D v8; // [esp+0x28] [ebp-0x50] BYREF
  struct gbTextureArray v9; // [esp+0x34] [ebp-0x44] BYREF

  v2 = gfxMgr->pMatrixStack[1];
  (((gbMatrixStack *)v2))->gbMatrixStack::Push();
  (((gbMatrixStack *)v2))->gbMatrixStack::LoadMatrix((gbMatrix4 *)(nRenderFlag + 32));
  (((gbMatrixStack *)v2))->gbMatrixStack::Translate(0.0,   1.0,   0.0);
  v4 = *(float *)&_this->m_bUIFlagA * -57.29578;
  v8.x = 0.0;
  v8.y = 1.0;
  v7 = v4;
  v8.z = 0.0;
  (((gbMatrixStack *)v2))->gbMatrixStack::Rotate(v7,  v8);
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&_this->m_fInterpStart, 1, (gbRenderEffect *)LODWORD(_this->m_vecTargetPos.z), (gbTextureArray *)&_this->m_fAnimParam);
  z = _this->m_vecTargetPos.z;
  v9.pTexPt[0] = (gbTexture *)LODWORD(_this->m_vecTargetPos.y);
  v9.nTex = 1;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad((gbGeomQuad *)&_this->m_fMatrixParamB, 12, (gbRenderEffect *)LODWORD(z), &v9);
  (((gbMatrixStack *)v2))->gbMatrixStack::Pop();
}

// 0x004B8200
void j_D3DXVec3TransformCoord(void *pOut, void *pV, void *pM)
{
  if ( *(float *)&pOut != *(float *)&pV )
    rand();
}

// 0x004BA230
void todo_004BA230(Actor *_this)
{
  float m_fTransitionPos; // edx
  double v2; // st7

  m_fTransitionPos = _this[45].m_fTransitionPos;
  v2 = *(float *)(LODWORD(m_fTransitionPos) + 156) - *(float *)(LODWORD(m_fTransitionPos) + 160);
  *(float *)&_this->m_nRoleState0 = v2;
  if ( v2 < *(float *)&_this->m_nCachedA )
  {
    if ( *(_DWORD *)(LODWORD(m_fTransitionPos) + 164) )
      sub_4B9E50();
    else
      *(&_this[44].m_nUpdateMode + 8) = 0;
  }
}

// 0x004BA510
int ParticleEffect_LoadSceneFile(int nVal)
{
  CEffect *v1; // ecx
  CEffect *v2; // ebp
  gbVFile *v3; // ebx
  int result; // eax
  int v5; // edi
  int v6; // esi
  char *p_ev; // edi
  int v8; // esi
  RenderTarget *p_byMaxFrame; // edi
  char v10[8]; // [esp+0x6C] [ebp-0x8] BYREF
  unsigned int *nVala; // [esp+0x78] [ebp+0x4]

  v2 = (CEffect *)v1;
  v3 = (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::OpenFile((const char *)nVal, 0x201u);
  if ( v3 )
  {
    sub_4BA3D0(v2);
    strcpy((char *)v2, (const char *)nVal);
    (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v10, 6u, v3);
    if ( strcmp(v10, "sgpar") )
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::CloseFile(v3);
    (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&g_nFileVersion, 4u, v3);
    if ( g_nFileVersion == dword_5D41AC )
    {
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&v2[1].m_QuadBuffer[273].su, 4u, v3);
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&v2[1].m_QuadBuffer[273].sv, 4u, v3);
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&v2[1].m_QuadBuffer[273].eu, 4u, v3);
      if ( g_nFileVersion > 0x10000 )
        (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&v2[1].m_QuadBuffer[274].ev, 4u, v3);
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&v2->m_Partical[4].fSize, 4u, v3);
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&v2->m_Partical[4].byAlpha, 4u, v3);
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(&v2->m_Partical[4].fZ, 4u, v3);
      v5 = 0;
      if ( SLODWORD(v2->m_Partical[4].fSize) > 0 )
      {
        nVala = (unsigned int *)&v2->m_QuadBuffer[731].color;
        do
        {
          sub_4BACA0(nVala, v3);
          ++v5;
          nVala += 5393;
        }
        while ( v5 < SLODWORD(v2->m_Partical[4].fSize) );
      }
      v6 = 0;
      if ( *(int *)&v2->m_Partical[4].byAlpha > 0 )
      {
        p_ev = (char *)&v2->m_QuadBuffer[2000].ev;
        do
        {
          sub_4BAE60(p_ev, v3);
          ++v6;
          p_ev += 32088;
        }
        while ( v6 < *(_DWORD *)&v2->m_Partical[4].byAlpha );
      }
      v8 = 0;
      if ( SLODWORD(v2->m_Partical[4].fZ) > 0 )
      {
        p_byMaxFrame = (RenderTarget *)&v2->m_Partical[5].byMaxFrame;
        do
        {
          (((RenderTarget *)p_byMaxFrame))->RenderTarget::ReadVFile(v3);
          ++v8;
          p_byMaxFrame = (RenderTarget *)((char *)p_byMaxFrame + 36952);
        }
        while ( v8 < SLODWORD(v2->m_Partical[4].fZ) );
      }
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::CloseFile(v3);
      result = (((CEffect *)v2))->CEffect::SetRenderParam(LODWORD(v2[1].m_QuadBuffer[274].ev));
      LOBYTE(result) = 1;
    }
    else
    {
      (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::CloseFile(v3);
      result = MessageBoxA(0, "Not supported file version", "Info", 0);
      LOBYTE(result) = 0;
    }
  }
  else
  {
    result = MessageBoxA((HWND)g_todo_BFDA4C, Text, Caption, 0);
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004BB260
int RenderTarget_LoadFromFile(int nVal)
{
  char *v1; // ecx
  char *v2; // esi
  int result; // eax

  v2 = (char *)v1;
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v1, 4u, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 4, 4u, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 8, 0x40u, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 72, 0x80u, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 212, 0xCu, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 200, 0xCu, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 224, 0x2D0u, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 944, 0x2D0u, (gbVFile *)nVal);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read(v2 + 1664, 0xE34u, (gbVFile *)nVal);
  return result;
}

// 0x004BC760
int ParticleEffect_Reset(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // esi

  v2 = (_DWORD *)v1;
  sub_4BA270(v1 + 1);
  v2[90710] = 0;
  v2[90711] = 0;
  v2[90712] = 0;
  v2[90713] = 0;
  v2[90714] = 0;
  return (int)v2;
}

// 0x004BC7E0
int ParticleEffect_SetDeltaTime(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 362856) = nVal;
  return result;
}

// 0x004BC7F0
int ParticleEffect_UpdateParticles(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // eax
  int result; // eax
  int v5; // esi
  int v6; // edi
  int v7; // [esp+0x8] [ebp-0xC] BYREF
  int v8; // [esp+0xC] [ebp-0x8]
  int v9; // [esp+0x10] [ebp-0x4]
  int nVala; // [esp+0x18] [ebp+0x4]
  int v11; // [esp+0x1C] [ebp+0x8]
  int v12; // [esp+0x20] [ebp+0xC]
  int v13; // [esp+0x24] [ebp+0x10]

  v2 = v1;
  v7 = v11;
  v3 = *(_DWORD *)(v1 + 362756);
  v8 = v12;
  v9 = v13;
  if ( v3 == 1 )
  {
    v7 = 0;
    v8 = 0;
    v9 = 0;
  }
  result = *(_DWORD *)(v1 + 260);
  v5 = 0;
  *(float *)&nVala = *(float *)&nVal * *(float *)(v1 + 362768);
  if ( result > 0 )
  {
    v6 = v1 + 284;
    do
    {
      sub_4BA150(*(float *)&nVala, (int)&v7);
      result = *(_DWORD *)(v2 + 260);
      ++v5;
      v6 += 36952;
    }
    while ( v5 < result );
  }
  return result;
}

// 0x004BD520
int ParticleEffect_LoadTextures(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // ebp
  int result; // eax
  int v5; // edi
  _DWORD *v6; // esi
  gbTexture **v7; // esi
  const char *v8; // edi
  gbTexture *v9; // eax
  OpenBaseFile v10; // [esp+0x10] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x14] [ebp-0x110] BYREF
  int v12; // [esp+0x120] [ebp-0x4]
  const char *v13; // [esp+0x12C] [ebp+0x8]

  v2 = v1;
  v3 = 0;
  v12 = 0;
  strcpy(g_szParticleTexName, (const char *)nVal);
  sprintf(Buffer, "%s\\%s", g_szParticleTexName, v13);
  if ( (unsigned __int8)ParticleEffect_LoadSceneFile((int)Buffer) )
  {
    v5 = 0;
    if ( *(int *)(v2 + 260) > 0 )
    {
      v6 = (_DWORD *)(v2 + 352);
      do
      {
        sub_4BA770(v2 + 21572 * *(v6 - 1) + 148112, v2 + 32088 * *v6 + 234400);
        ++v5;
        v6 += 9238;
      }
      while ( v5 < *(_DWORD *)(v2 + 260) );
    }
    if ( *(int *)(v2 + 264) > 0 )
    {
      v7 = (gbTexture **)(v2 + 362840);
      v8 = (const char *)(v2 + 148168);
      do
      {
        if ( v3 < 4 )
        {
          sprintf(Buffer, "%s\\%s", g_szParticleTexName, v8);
          v9 = (gbTexture *)gfxMgr->NewTexture((const char *)Buffer);
          *v7 = v9;
          (((gbTexture *)v9))->gbTexture::LoadTexture(1);
        }
        ++v3;
        ++v7;
        v8 += 21572;
      }
      while ( v3 < *(_DWORD *)(v2 + 264) );
    }
    v12 = -1;
    ((OpenNULLFile *)&v10)->OpenNULLFile::OpenNULLFile();
    LOBYTE(result) = 1;
  }
  else
  {
    v12 = -1;
    ((OpenNULLFile *)&v10)->OpenNULLFile::OpenNULLFile();
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x004BD7C0
int ParticleEffect_SetTimeParam(int nVal)
{
  int v1; // ecx
  int v2; // esi
  CEffect *v3; // edi
  int result; // eax
  int v5; // [esp+0x0] [ebp-0xC]

  v2 = v1;
  v3 = (CEffect *)(v1 + 4);
  *(float *)&v5 = 1.0 / *(float *)(v1 + 362832);
  (((CEffect *)(v1 + 4)))->CEffect::SetRenderParam(v5);
  result = (((CEffect *)v3))->CEffect::SetRenderParam(nVal);
  *(_DWORD *)(v2 + 362832) = nVal;
  return result;
}

// 0x004BDB50
// Microsoft VisualC 2-14/net runtime
void InitPal3Singleton()
{
  (((RenderTarget *)&g_PAL3))->RenderTarget::~RenderTarget();
}

// 0x004BE5D0
// Microsoft VisualC 2-14/net runtime
void InitScreenEffectSingleton()
{
  (((ScreenEffectMgr *)(&g_PAL3.m_gametime + 51)))->ScreenEffectMgr::ClearAllEffects();
}

// 0x004BEE60
int ScreenEffectMgr_ScreenEffectMgr(int nVal)
{
  PAL3VisNode *v1; // ecx
  int v2; // edi
  int v3; // esi
  int v4; // ebx
  int v5; // esi
  int v6; // ebx
  int v7; // esi
  int v8; // ebx
  int v10; // [esp+0x0] [ebp-0x1C]

  v2 = (int)v1;
  v1->PAL3VisNode::PAL3VisNode();
  *(_DWORD *)(v2 + 164) = 0;
  v3 = v2 + 176;
  v4 = 6;
  do
  {
    v3 += 68;
    --v4;
  }
  while ( v4 );
  v5 = v2 + 584;
  v6 = 6;
  do
  {
    v5 += 68;
    --v6;
  }
  while ( v6 );
  v7 = v2 + 992;
  v8 = 4;
  do
  {
    v7 += 12;
    --v8;
  }
  while ( v8 );
  ParticleEffect_Reset(v10);
  *(_DWORD *)(v2 + 168) = 0;
  return v2;
}

// 0x004BEF50
void UIWnd(ScreenEffectMgr *_this)
{
  (((ScreenEffectMgr *)_this))->ScreenEffectMgr::CleanupTextures();
  (((RenderTarget *)&_this[7].m_fadeOut.m_life))->RenderTarget::UpdateTimeStep();
  (((gbChain1DNode *)_this))->gbChain1DNode::Process();
}

// 0x004C5B50
bool todo_004C5B50(Actor *_this, int nKey)
{
  int v2; // edx
  int v3; // eax
  char *i; // ecx

  v2 = *((_DWORD *)&_this->m_pActor + 1);
  if ( !v2 )
    return 0;
  v3 = 0;
  if ( v2 <= 0 )
    return 0;
  for ( i = _this->m_szTexture; *(_DWORD *)(*(_DWORD *)i + 8) != nKey; i += 4 )
  {
    if ( ++v3 >= v2 )
      return 0;
  }
  return 1;
}

// 0x004C5B90
_Texture_uv operator_(_Texture_uv *_this, _Texture_uv *a2)
{
  _Texture_uv result; // rax
  char v4; // [esp+0xC] [ebp+0x8]

  LODWORD(result.u) = sub_4C5940(a2);
  LOBYTE(result.v) = v4;
  *(_BYTE *)(*((_DWORD *)&_this[35].u + LODWORD(result.u)) + 13) = v4;
  return result;
}

// 0x004C5BB0
int CombatEffectUpdate(double pData)
{
  int v1; // ecx
  int *v2; // esi
  int v3; // edi
  double v4; // st7
  int result; // eax
  double v6; // st7
  _DWORD *v7; // ebx

  v2 = (int *)v1;
  v3 = 0;
  v4 = *(float *)(v1 + 332) * pData;
  result = *(_DWORD *)(v1 + 276);
  *(double *)(v1 + 312) = v4;
  v6 = v4 + *(double *)(v1 + 320);
  *(double *)(v1 + 320) = v6;
  *(float *)(v1 + 328) = v6;
  if ( result > 0 )
  {
    v7 = (_DWORD *)(v1 + 280);
    do
    {
      (*(void ( **)(_DWORD, int, int))(*(_DWORD *)*v7 + 20))(*v7, v2[78], v2[79]);
      result = (unsigned long)v2[69];
      ++v3;
      ++v7;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x004C61A0
int CEffectSystem_CEffectSystem(int nVal)
{
  int v1; // ecx
  int v2; // esi
  gbTexture *v3; // eax
  int result; // eax
  int v5; // ecx
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x800] BYREF
  char ArgList; // [esp+0x408] [ebp-0x400] BYREF

  v2 = v1;
  v3 = (gbTexture *)(*(int ( **)(_DWORD, int))(**(_DWORD **)dword_DE9384 + 8))(*(_DWORD *)dword_DE9384, nVal);
  *(_DWORD *)(v2 + 245792) = (_DWORD)v3;
  (((gbTexture *)v3))->gbTexture::LoadTexture(1);
  result = (int)operator new(0x44u);
  if ( result )
  {
    v5 = *(_DWORD *)(v2 + 245792);
    *(_DWORD *)(result + 64) = 1;
    *(_DWORD *)result = v5;
  }
  else
  {
    result = 0;
  }
  *(_DWORD *)(v2 + 245796) = result;
  if ( !result )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&g_EffMgrData._tail_000[840], &g_EffMgrData._tail_000[856], 761),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  return result;
}

// 0x004C6290
int Destroy__ovl_02(int nMode)
{
  int result; // eax
  _BYTE v2[16]; // [esp+0x4] [ebp-0x30] BYREF
  int v3; // [esp+0x14] [ebp-0x20]
  int v4; // [esp+0x18] [ebp-0x1C]
  int v5; // [esp+0x1C] [ebp-0x18]
  int v6; // [esp+0x20] [ebp-0x14]
  int v7; // [esp+0x24] [ebp-0x10]
  int v8; // [esp+0x28] [ebp-0xC]
  int v9; // [esp+0x2C] [ebp-0x8]
  int v10; // [esp+0x38] [ebp+0x4]
  int v11; // [esp+0x3C] [ebp+0x8]
  int v12; // [esp+0x40] [ebp+0xC]
  int v13; // [esp+0x44] [ebp+0x10]
  int v14; // [esp+0x48] [ebp+0x14]

  v2[13] = 0;
  v2[14] = 0;
  v6 = v10;
  v9 = v13;
  v8 = v12;
  v7 = v11;
  v2[10] = 1;
  v2[8] = 1;
  v2[9] = 1;
  v2[12] = 16;
  v2[15] = 1;
  v5 = -1;
  v3 = v14;
  v4 = 0;
  result = sub_4C5FA0(v2);
  return 1;
}

// 0x004C6370
CEffectSystem * CEffectSystem_DestroyEffect()
{
  int v0; // ecx

  *(_DWORD *)(v0 + 48) = -1;
  *(_DWORD *)(v0 + 44) = 0;
  *(_DWORD *)(v0 + 832) = 0;
  *(_DWORD *)(v0 + 52) = 0;
  *(_DWORD *)(v0 + 56) = 0;
  *(_BYTE *)(v0 + 4) = 0;
  *(_BYTE *)(v0 + 5) = 0;
  *(_DWORD *)(v0 + 8) = 0;
  *(_DWORD *)(v0 + 828) = 0;
  *(_DWORD *)(v0 + 28) = 0;
  *(_DWORD *)(v0 + 32) = 1061158912;
  *(_DWORD *)(v0 + 36) = 1065353216;
  *(_DWORD *)(v0 + 40) = 0;
  *(_DWORD *)(v0 + 12) = 0;
  *(_DWORD *)(v0 + 24) = 0;
  *(_DWORD *)(v0 + 20) = 1145569280;
  *(_DWORD *)(v0 + 16) = 1142292480;
  return (CEffectSystem *)v0;
}

// 0x004C6450
// Microsoft VisualC 2-14/net runtime
void PostDestroyAllEffects()
{
  ;
}

// 0x004C6831
void SetRadiusWidth(int a1)
{
  JUMPOUT(0x4C6840);
}

// 0x004C7680
int ProcCommonTask__ovl(CEffExplosive *_this, int a2)
{
  float v3; // st7
  int v4; // edi
  int v5; // ecx
  float v6; // st7
  int v7; // ebp
  float m_fAlpha; // st7
  unsigned __int16 v9; // cx
  float fTime; // [esp+0x10] [ebp-0x80]
  int fTimea; // [esp+0x10] [ebp-0x80]
  float fDeltaTime; // [esp+0x24] [ebp-0x6C]
  float v14; // [esp+0x28] [ebp-0x68]
  float v15; // [esp+0x2C] [ebp-0x64]
  float v16; // [esp+0x30] [ebp-0x60]
  float v17; // [esp+0x34] [ebp-0x5C]
  gbVec3D v18; // [esp+0x38] [ebp-0x58] BYREF
  struct gbVec3D v19; // [esp+0x44] [ebp-0x4C] BYREF
  gbMatrix4 v20; // [esp+0x50] [ebp-0x40] BYREF

  v3 = *(float *)&_this->_tail_000[4];
  v4 = *(_DWORD *)&_this->_tail_000[12] + 152 * *(_DWORD *)&_this->_tail_000[16];
  v5 = 9 * *(_DWORD *)&_this->_tail_000[20];
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  fDeltaTime = *(float *)&_this->_tail_000[8];
  if ( v6 > *(float *)(v7 + 24) )
    fDeltaTime = fDeltaTime - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    *(_DWORD *)(v7 + 44) = 0;
    _this->m_bVisible = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  if ( *(float *)&_this->_tail_000[4] - *(float *)(v7 + 16) > *(float *)(v4 + 84) && !*(_DWORD *)(v7 + 44) )
  {
    (((CEffMgr *)_this))->CEffMgr::EmitParticles();
    *(_DWORD *)(v7 + 44) = 1;
  }
  _this->m_vecRot.x = fDeltaTime * *(float *)(v4 + 64) + _this->m_vecRot.x;
  _this->m_vecRot.y = fDeltaTime * *(float *)(v4 + 68) + _this->m_vecRot.y;
  _this->m_vecRot.z = fDeltaTime * *(float *)(v4 + 72) + _this->m_vecRot.z;
  _this->m_vecPos.x = fDeltaTime * *(float *)(v4 + 28) + _this->m_vecPos.x;
  _this->m_vecPos.y = fDeltaTime * *(float *)(v4 + 32) + _this->m_vecPos.y;
  _this->m_vecPos.z = fDeltaTime * *(float *)(v4 + 36) + _this->m_vecPos.z;
  memset(&v18, 0, sizeof(v18));
  memset(&v19, 0, sizeof(v19));
  (((gbMatrix4 *)&v20))->gbMatrix4::LoadIdentity();
  v18 = *(gbVec3D *)(v4 + 44);
  (((gbVec3D *)&v18))->gbVec3D::Normalize();
  fTime = (*(float *)&_this->_tail_000[4] - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  (((gbMatrix4 *)&v20))->gbMatrix4::SetAxisAngle(&v18, fTime);
  v19.z = *(float *)(v4 + 56);
  v19.x = 0.0;
  v19.y = 0.0;
  (((gbMatrix4 *)&v20))->gbMatrix4::Rotate(&v19, &_this->m_vecOffsetPos);
  if ( *(float *)(v4 + 80) != 0.0f
    || *(float *)(v4 + 84) != 0.0f
    || *(float *)(v4 + 92) != 0.0f
    || *(float *)(v4 + 88) != 0.0f )
  {
    _this->m_fAlpha = fDeltaTime * *(float *)(v4 + 80) + _this->m_fAlpha;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( _this->m_fAlpha <= 255.0f )
    {
      if ( _this->m_fAlpha >= 0.0f )
        m_fAlpha = _this->m_fAlpha;
      else
        m_fAlpha = 0.0f;
    }
    else
    {
      m_fAlpha = 255.0f;
    }
    _this->m_fAlpha = m_fAlpha;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v14 = _this->m_fAlpha + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v15 = _this->m_fRed + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v16 = _this->m_fGreen + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v17 = _this->m_fBlue + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    HIBYTE(v9) = LOBYTE(v14);
    LOBYTE(v9) = LOBYTE(v15);
    _this->m_dwStartColor = LOBYTE(v17) | ((LOBYTE(v16) | (v9 << 8)) << 8);
  }
  _this->m_fXSize = fDeltaTime * *(float *)(v4 + 24) + _this->m_fXSize;
  _this->m_fZSize = fDeltaTime * *(float *)(v4 + 108) + _this->m_fZSize;
  if ( *(_DWORD *)(v7 + 44) == 1 )
  {
    *(float *)&fTimea = *(float *)&_this->_tail_000[4] - *(float *)(v7 + 16);
    (((CEffExplosive *)_this))->CEffExplosive::UpdateExplosive(fDeltaTime, fTimea);
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *(float *)&_this->_tail_000[4] - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
    *(_DWORD *)(v7 + 8) = 4;
  return 0;
}

// 0x004C9470
void todo_004C9470(Actor *_this, int nFlags)
{
  float m_fMoveSpeed; // eax
  int v4; // ebx
  int v5; // edi

  m_fMoveSpeed = _this->m_fMoveSpeed;
  if ( m_fMoveSpeed != 0.0f || LODWORD(_this->m_fMoveRange) )
  {
    v4 = 0;
    if ( SLODWORD(m_fMoveSpeed) > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(&_this->m_actarray_capacity_end->m_actarray_type + v5));
        ++v4;
        *(_DWORD *)(&_this->m_actarray_capacity_end->m_actarray_type + v5) = 0;
        v5 += 152;
      }
      while ( v4 < SLODWORD(_this->m_fMoveSpeed) );
    }
    operator delete(_this->m_actarray_capacity_end);
    _this->m_actarray_capacity_end = 0;
    _this->m_fMoveSpeed = 0.0;
    _this->m_fMoveRange = 0.0;
  }
  if ( (nFlags & 1) != 0 )
    operator delete(_this);
}

// 0x004CB280
void todo_004CB280(Actor *_this, int nFlags)
{
  float m_fMoveSpeed; // eax
  int v4; // ebx
  int v5; // edi

  m_fMoveSpeed = _this->m_fMoveSpeed;
  if ( m_fMoveSpeed != 0.0f || LODWORD(_this->m_fMoveRange) )
  {
    v4 = 0;
    if ( SLODWORD(m_fMoveSpeed) > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(&_this->m_actarray_capacity_end->m_actarray_type + v5));
        ++v4;
        *(_DWORD *)(&_this->m_actarray_capacity_end->m_actarray_type + v5) = 0;
        v5 += 152;
      }
      while ( v4 < SLODWORD(_this->m_fMoveSpeed) );
    }
    operator delete(_this->m_actarray_capacity_end);
    _this->m_actarray_capacity_end = 0;
    _this->m_fMoveSpeed = 0.0;
    _this->m_fMoveRange = 0.0;
  }
  if ( (nFlags & 1) != 0 )
    operator delete(_this);
}

// 0x004CC4C0
int CEffCylinder_Update(int nVal)
{
  int v1; // ecx
  int v2; // esi
  float v3; // st7
  int v4; // edi
  int v5; // ecx
  float v6; // st7
  int v7; // ebp
  float v8; // st7
  float v9; // st7
  float v10; // st7
  float v11; // st7
  float v12; // st7
  unsigned __int16 v13; // cx
  int v14; // edi
  int v15; // ebx
  float v17; // [esp+0x10] [ebp-0x80]
  int v18; // [esp+0x10] [ebp-0x80]
  float fVal; // [esp+0x24] [ebp-0x6C]
  float v20; // [esp+0x28] [ebp-0x68]
  float v21; // [esp+0x2C] [ebp-0x64]
  float v22; // [esp+0x30] [ebp-0x60]
  float v23; // [esp+0x34] [ebp-0x5C]
  gbVec3D v24; // [esp+0x38] [ebp-0x58] BYREF
  struct gbVec3D v25; // [esp+0x44] [ebp-0x4C] BYREF
  gbMatrix4 v26; // [esp+0x50] [ebp-0x40] BYREF

  v2 = v1;
  v3 = *(float *)(v1 + 16);
  v4 = *(_DWORD *)(v1 + 24) + 152 * *(_DWORD *)(v1 + 28);
  v5 = 9 * *(_DWORD *)(v1 + 32);
  v6 = v3 - *(float *)(*(_DWORD *)v4 + 8 * v5 + 16);
  v7 = *(_DWORD *)v4 + 8 * v5;
  fVal = *(float *)(v2 + 20);
  if ( v6 > *(float *)(v7 + 24) )
    fVal = fVal - (v6 - *(float *)(v7 + 24));
  if ( !*(_BYTE *)(v7 + 65) )
  {
    *(_DWORD *)(v7 + 44) = 0;
    *(_BYTE *)(v2 + 68) = 1;
    *(_BYTE *)(v7 + 65) = 1;
  }
  if ( *(float *)(v2 + 16) - *(float *)(v7 + 16) >= *(float *)(v4 + 84) && !*(_DWORD *)(v7 + 44) )
  {
    sub_4CCDA0(v2);
    *(_DWORD *)(v7 + 44) = 1;
  }
  *(float *)(v2 + 148) = fVal * *(float *)(v4 + 64) + *(float *)(v2 + 148);
  *(float *)(v2 + 152) = fVal * *(float *)(v4 + 68) + *(float *)(v2 + 152);
  *(float *)(v2 + 156) = fVal * *(float *)(v4 + 72) + *(float *)(v2 + 156);
  *(float *)(v2 + 160) = fVal * *(float *)(v4 + 28) + *(float *)(v2 + 160);
  *(float *)(v2 + 164) = fVal * *(float *)(v4 + 32) + *(float *)(v2 + 164);
  *(float *)(v2 + 168) = fVal * *(float *)(v4 + 36) + *(float *)(v2 + 168);
  memset(&v24, 0, sizeof(v24));
  memset(&v25, 0, sizeof(v25));
  (((gbMatrix4 *)&v26))->gbMatrix4::LoadIdentity();
  v24 = *(gbVec3D *)(v4 + 44);
  (((gbVec3D *)&v24))->gbVec3D::Normalize();
  v17 = (*(float *)(v2 + 16) - *(float *)(v7 + 16)) * *(float *)(v4 + 60);
  (((gbMatrix4 *)&v26))->gbMatrix4::SetAxisAngle(&v24, v17);
  v25.z = *(float *)(v4 + 56);
  v25.x = 0.0;
  v25.y = 0.0;
  (((gbMatrix4 *)&v26))->gbMatrix4::Rotate(&v25, (gbVec3D *)(v2 + 172));
  if ( *(float *)(v4 + 80) != 0.0f
    || *(float *)(v4 + 84) != 0.0f
    || *(float *)(v4 + 92) != 0.0f
    || *(float *)(v4 + 88) != 0.0f )
  {
    *(float *)(v2 + 92) = fVal * *(float *)(v4 + 80) + *(float *)(v2 + 92);
    *(float *)(v2 + 136) = fVal * *(float *)(v4 + 80) + *(float *)(v2 + 136);
    *(float *)(v2 + 96) = fVal * *(float *)(v4 + 84) + *(float *)(v2 + 96);
    *(float *)(v2 + 100) = fVal * *(float *)(v4 + 88) + *(float *)(v2 + 100);
    *(float *)(v2 + 104) = fVal * *(float *)(v4 + 92) + *(float *)(v2 + 104);
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( *(float *)(v2 + 136) <= 255.0f )
    {
      if ( *(float *)(v2 + 136) >= 0.0f )
        v8 = *(float *)(v2 + 136);
      else
        v8 = 0.0f;
    }
    else
    {
      v8 = 255.0f;
    }
    *(float *)(v2 + 136) = v8;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( *(float *)(v2 + 92) <= 255.0f )
    {
      if ( *(float *)(v2 + 92) >= 0.0f )
        v9 = *(float *)(v2 + 92);
      else
        v9 = 0.0f;
    }
    else
    {
      v9 = 255.0f;
    }
    *(float *)(v2 + 92) = v9;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( *(float *)(v2 + 96) <= 255.0f )
    {
      if ( *(float *)(v2 + 96) >= 0.0f )
        v10 = *(float *)(v2 + 96);
      else
        v10 = 0.0f;
    }
    else
    {
      v10 = 255.0f;
    }
    *(float *)(v2 + 96) = v10;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( *(float *)(v2 + 100) <= 255.0f )
    {
      if ( *(float *)(v2 + 100) >= 0.0f )
        v11 = *(float *)(v2 + 100);
      else
        v11 = 0.0f;
    }
    else
    {
      v11 = 255.0f;
    }
    *(float *)(v2 + 100) = v11;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    if ( *(float *)(v2 + 104) <= 255.0f )
    {
      if ( *(float *)(v2 + 104) >= 0.0f )
        v12 = *(float *)(v2 + 104);
      else
        v12 = 0.0f;
    }
    else
    {
      v12 = 255.0f;
    }
    *(float *)(v2 + 104) = v12;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v20 = *(float *)(v2 + 92) + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v21 = *(float *)(v2 + 96) + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v22 = *(float *)(v2 + 100) + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    v23 = *(float *)(v2 + 104) + 12582912.0f;
    if ( (g_bEffSystemFlags & 1) == 0 )
    {
      g_bEffSystemFlags |= 1u;
      (((CEffMgr *)&g_pCEffMgrBackup))->CEffMgr::Reset();
      atexit(j_j_codecvt_base);
    }
    HIBYTE(v13) = LOBYTE(v20);
    LOBYTE(v13) = LOBYTE(v21);
    *(_DWORD *)(v2 + 88) = LOBYTE(v23) | ((LOBYTE(v22) | (v13 << 8)) << 8);
  }
  *(float *)(v2 + 108) = fVal * *(float *)(v4 + 24) + *(float *)(v2 + 108);
  *(float *)(v2 + 112) = fVal * *(float *)(v4 + 108) + *(float *)(v2 + 112);
  if ( *(_DWORD *)(v7 + 44) == 1 )
  {
    *(float *)&v18 = *(float *)(v2 + 16) - *(float *)(v7 + 16);
    (((CEffMgr *)v2))->CEffMgr::UpdateEffect(fVal, v18);
  }
  if ( *(_BYTE *)(v7 + 66) == 1 || *(float *)(v2 + 16) - *(float *)(v7 + 16) >= *(float *)(v7 + 24) )
  {
    v14 = 0;
    if ( *(int *)(v2 + 116) > 0 )
    {
      v15 = 0;
      do
      {
        sub_4CD3A0(*(_DWORD *)(v2 + 52) + v15);
        ++v14;
        v15 += 56;
      }
      while ( v14 < *(_DWORD *)(v2 + 116) );
    }
    *(_DWORD *)(v7 + 8) = 4;
  }
  return 0;
}

// 0x004CD0D0
void LogCreateFailureReport(int pEM, int nMaxTrail, int bNoHead, int pTextureArray)
{
  int v4; // ecx
  _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v6; // esp
  _DWORD *v7; // esi
  _DWORD *v8; // eax
  int v9; // ebp
  void *v10; // edi
  _DWORD *v11; // ecx
  _DWORD *v12; // ebx
  _DWORD *v13; // eax
  _DWORD *v14; // edx
  int v15; // ebx
  void *v16; // eax
  void *v17; // ebp
  int v18; // ebx
  int v19; // edi
  int v20; // ebx
  int v21; // ecx
  int v22; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x100C] BYREF
  char ArgList[1024]; // [esp+0x408] [ebp-C0Ch] BYREF
  char v25[1024]; // [esp+0x808] [ebp-0x80C] BYREF
  char v26; // [esp+C08h] [ebp-0x40C] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v27; // [esp+0x1008] [ebp-0xC]
  void *v28; // [esp+0x100C] [ebp-0x8]
  int v29; // [esp+0x1010] [ebp-0x4]

  v29 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v28 = ((void*)0);
  v27 = (_EXCEPTION_REGISTRATION_RECORD *)ExceptionList;
  v6 = alloca(4104);
  v7 = (_DWORD *)v4;
  *(_DWORD *)v4 = pEM;
  *(_BYTE *)(v4 + 8) = bNoHead;
  *(_DWORD *)(v4 + 12) = pTextureArray;
  if ( nMaxTrail <= 1 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException("few of node in meteor chain", &g_EffMgrData._tail_000[1348], 684),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v8 = (_DWORD *)operator new(0x24u);
  v9 = 0;
  if ( v8 )
  {
    *v8 = 0;
    v8[1] = 0;
    v8[2] = 0;
    v10 = (void *)v8;
  }
  else
  {
    v10 = 0;
  }
  v7[5] = (_DWORD)v10;
  if ( !v10 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)ArgList))->Logger::FormatException("could not malloc in CMeteror create.", &g_EffMgrData._tail_000[1348], 688),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  memset(v10, 0, 0x24u);
  v11 = 0;
  v7[4] = 1;
  v12 = (_DWORD *)v7[5];
  if ( nMaxTrail - 1 > 0 )
  {
    do
    {
      v13 = (_DWORD *)operator new(0x24u);
      if ( v13 )
      {
        *v13 = 0;
        v13[1] = 0;
        v13[2] = 0;
        v14 = (_DWORD *)v13;
      }
      else
      {
        v14 = 0;
      }
      if ( !v14 )
      {
        qmemcpy(
          pExceptionObject,
          (((Logger *)ArgList))->Logger::FormatException("could not malloc in cmeteror create.", &g_EffMgrData._tail_000[1348], 700),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      ++v9;
      memset(v14, 0, 0x24u);
      v12[8] = (_DWORD)v14;
      v14[7] = (_DWORD)v12;
      v12 = (_DWORD *)v14;
      ++v7[4];
    }
    while ( v9 < nMaxTrail - 1 );
    v11 = (_DWORD *)v14;
  }
  v15 = (unsigned long)v7[4];
  v7[6] = (_DWORD)v11;
  v16 = (void *)operator new(68 * v15);
  v17 = (void *)v16;
  v29 = 0;
  if ( v16 )
  {
    v18 = v15 - 1;
    v19 = (int)v16;
    if ( v18 >= 0 )
    {
      v20 = v18 + 1;
      do
      {
        v19 += 68;
        --v20;
      }
      while ( v20 );
    }
  }
  else
  {
    v17 = 0;
  }
  v29 = -1;
  v7[1] = (_DWORD)v17;
  if ( !v17 )
  {
    qmemcpy(
      v25,
      (((Logger *)&v26))->Logger::FormatException("could not malloc in CMeteror construction", &g_EffMgrData._tail_000[1348], 714),
      sizeof(v25));
    _CxxThrowException(v25, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v21 = 0;
  if ( (int)v7[4] > 0 )
  {
    v22 = 0;
    do
    {
      ++v21;
      *(_DWORD *)(v7[1] + v22 + 52) = 0;
      *(_DWORD *)(v7[1] + v22 + 60) = 1065353216;
      v22 += 68;
    }
    while ( v21 < v7[4] );
  }
}

// 0x004CDB70
int SceneMgrUpdate(float fVal)
{
  float *v1; // ecx
  float v2; // st7
  int result; // eax
  int *v4; // esi
  int v5; // edi

  v2 = fVal - v1[10824];
  result = LODWORD(fVal);
  v1[10824] = fVal;
  v4 = (int *)(v1 + 587);
  v1[10825] = v2;
  v5 = 2048;
  v1[10826] = v1[10826] + v1[10825];
  do
  {
    LOBYTE(result) = *((_BYTE *)v4 - 4);
    if ( (_BYTE)result )
    {
      if ( !*((_BYTE *)v4 - 3) )
        result = (*(int ( **)(int, _DWORD))(*(_DWORD *)*v4 + 20))(*v4, LODWORD(fVal));
      LOBYTE(result) = *((_BYTE *)v4 - 4);
      if ( (_BYTE)result )
      {
        result = (unsigned long)*v4;
        if ( *(_BYTE *)(*v4 + 8) )
          *((_BYTE *)v4 - 3) = 1;
      }
    }
    v4 += 5;
    --v5;
  }
  while ( v5 );
  return result;
}

// 0x004D0C90
void todo_004D0C90(int a1@<ecx>, CEffect *a2, float a3)
{
  (((CEffCustomShape *)(a1 - 12)))->CEffCustomShape::_nearby_4cffb0(a2, a3);
}

// 0x004D0CE0
int CEffModel_Reset(int nVal)
{
  int v1; // ecx

  *(_DWORD *)(v1 + 4) = 0;
  *(_BYTE *)(v1 + 8) = 0;
  *(_DWORD *)(v1 + 16) = 0;
  *(_DWORD *)(v1 + 20) = 0;
  *(_DWORD *)(v1 + 24) = 0;
  *(_DWORD *)(v1 + 28) = -1;
  *(_DWORD *)(v1 + 32) = -1;
  *(_DWORD *)(v1 + 36) = 0;
  *(_DWORD *)(v1 + 40) = 0;
  *(_DWORD *)(v1 + 44) = 0;
  *(_DWORD *)(v1 + 72) = -1;
  *(_BYTE *)(v1 + 48) = 0;
  *(_BYTE *)(v1 + 49) = 0;
  *(_BYTE *)(v1 + 50) = 0;
  *(_BYTE *)(v1 + 51) = 0;
  *(_BYTE *)(v1 + 54) = 0;
  *(_BYTE *)(v1 + 52) = 0;
  *(_BYTE *)(v1 + 53) = 0;
  *(_DWORD *)(v1 + 56) = 0;
  *(_DWORD *)(v1 + 60) = 0;
  *(_DWORD *)(v1 + 64) = 0;
  *(_DWORD *)(v1 + 68) = 0;
  *(_DWORD *)(v1 + 156) = 0;
  *(_DWORD *)(v1 + 160) = 0;
  *(_DWORD *)(v1 + 164) = 0;
  *(_DWORD *)(v1 + 4264) = 0;
  *(_DWORD *)(v1 + 4268) = 0;
  memset((void *)(v1 + 168), 0, 0x1000u);
  return v1;
}

// 0x004D37A0
void todo_004D37A0(Actor *_this, unsigned int nDelFlags)
{
  float m_fMoveSpeed; // eax
  int v4; // ebx
  int v5; // edi

  m_fMoveSpeed = _this->m_fMoveSpeed;
  if ( m_fMoveSpeed != 0.0f || LODWORD(_this->m_fMoveRange) )
  {
    v4 = 0;
    if ( SLODWORD(m_fMoveSpeed) > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(&_this->m_actarray_capacity_end->m_actarray_type + v5));
        ++v4;
        *(_DWORD *)(&_this->m_actarray_capacity_end->m_actarray_type + v5) = 0;
        v5 += 152;
      }
      while ( v4 < SLODWORD(_this->m_fMoveSpeed) );
    }
    operator delete(_this->m_actarray_capacity_end);
    _this->m_actarray_capacity_end = 0;
    _this->m_fMoveSpeed = 0.0;
    _this->m_fMoveRange = 0.0;
  }
  if ( (nDelFlags & 1) != 0 )
    operator delete(_this);
}

// 0x004D4CA0
void todo_004D4CA0(Actor *_this, unsigned int nDelFlags)
{
  float m_fMoveSpeed; // eax
  int v4; // ebx
  int v5; // edi

  m_fMoveSpeed = _this->m_fMoveSpeed;
  if ( m_fMoveSpeed != 0.0f || LODWORD(_this->m_fMoveRange) )
  {
    v4 = 0;
    if ( SLODWORD(m_fMoveSpeed) > 0 )
    {
      v5 = 0;
      do
      {
        operator delete(*(void **)(&_this->m_actarray_capacity_end->m_actarray_type + v5));
        ++v4;
        *(_DWORD *)(&_this->m_actarray_capacity_end->m_actarray_type + v5) = 0;
        v5 += 152;
      }
      while ( v4 < SLODWORD(_this->m_fMoveSpeed) );
    }
    operator delete(_this->m_actarray_capacity_end);
    _this->m_actarray_capacity_end = 0;
    _this->m_fMoveSpeed = 0.0;
    _this->m_fMoveRange = 0.0;
  }
  if ( (nDelFlags & 1) != 0 )
    operator delete(_this);
}

// 0x004D589C
void SetRect0(tagRECT *a1)
{
  JUMPOUT(0x4D58A0);
}

// 0x004D6D30
void Update(C3DSpark *_this)
{
  int v1; // esi
  float *v2; // edx
  int v3; // eax
  float v4; // [esp+0x4] [ebp-0x4]
  float deltaTime; // [esp+0xC] [ebp+0x4]

  v1 = 0;
  if ( _this->m_nCurrentSpark > 0 )
  {
    v2 = (float *)&_this->m_Spark[0]._tail_000[12];
    do
    {
      if ( *((_BYTE *)v2 + 41) )
      {
        *v2 = deltaTime * v2[3] + *v2;
        v2[1] = deltaTime * v2[4] + v2[1];
        v2[2] = deltaTime * v2[5] + v2[2];
        *(v2 - 3) = deltaTime * *v2 + *(v2 - 3);
        *(v2 - 2) = deltaTime * v2[1] + *(v2 - 2);
        *(v2 - 1) = deltaTime * v2[2] + *(v2 - 1);
        v2[6] = deltaTime * v2[7] + v2[6];
        v4 = deltaTime * v2[9] + v2[8];
        v2[8] = v4;
        if ( -v4 >= *(v2 - 2) || v2[6] <= 1.0f || v2[6] > 255.0f || v4 < 0.0099999998f )
        {
          *((_BYTE *)v2 + 41) = 0;
          v3 = _this->m_nCurrentSpark - 1;
          if ( v1 == v3 )
            _this->m_nCurrentSpark = v3;
        }
      }
      ++v1;
      v2 += 14;
    }
    while ( v1 < _this->m_nCurrentSpark );
  }
}

// 0x004DB940
int StoreThreadFlag(_BYTE *_this, char a2)
{
  int v3; // ebx
  int i; // esi
  int j; // esi

  _this[454] = a2;
  if ( a2 )
  {
    v3 = 0;
    for ( i = 76; i < 120; i += 4 )
    {
      if ( *(_BYTE *)(*(_DWORD *)(*(_DWORD *)_this + 16) + v3 + 577) )
        (***(void ( ****)(_DWORD, int))(*((_DWORD *)_this + 1) + i))((_DWORD)(*(_DWORD *)(*((_DWORD *)_this + 1) + i)), (int)(1));
      v3 += 892;
    }
    return (***(int ( ****)(_DWORD, int))(*((_DWORD *)_this + 1) + 72))((_DWORD)(*(_DWORD *)(*((_DWORD *)_this + 1) + 72)), (int)(1));
  }
  else
  {
    for ( j = 76; j < 120; j += 4 )
      (***(void ( ****)(_DWORD, _DWORD))(j + *((_DWORD *)_this + 1)))((_DWORD)(*(_DWORD *)(j + *((_DWORD *)_this + 1))), (_DWORD)(0));
    return (***(int ( ****)(_DWORD, _DWORD))(*((_DWORD *)_this + 1) + 72))((_DWORD)(*(_DWORD *)(*((_DWORD *)_this + 1) + 72)), (_DWORD)(0));
  }
}

// 0x004DC610
char CountAttackSequences(CCBUI *_this)
{
  int v2; // edi
  UIStatic **v3; // esi
  char result; // al

  v2 = 0;
  v3 = (UIStatic **)&_this->m_pAttackSequenFace[2];
  do
  {
    result = *((_BYTE *)v3 + 60);
    if ( result )
    {
      _this->m_pAttackSequenFace[0] = (UIStatic *)v2;
      result = ((int ( *)(char *, _DWORD))*v3)((char *)v3[1] + (_DWORD)_this, 0);
    }
    ++v2;
    v3 += 16;
  }
  while ( v2 < 20 );
  _this->m_pAttackSequenFace[0] = (UIStatic *)-1;
  return result;
}

// 0x004DC650
int FindFreeThread(CCBSystem *_this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
  int v11; // edi
  int *i; // eax
  char *v14; // esi
  CCBSystem **v15; // edx
  int v16; // [esp+0x30] [ebp+0x28]

  v11 = 0;
  for ( i = &_this->m_Thread[0].nTaskIndex; *(_BYTE *)i; i += 16 )
  {
    if ( ++v11 >= 20 )
      return -1;
  }
  v14 = (char *)_this + 64 * v11;
  *((_DWORD *)v14 + 28) = a2;
  *((_DWORD *)v14 + 29) = a3;
  *((_DWORD *)v14 + 30) = a4;
  *((_DWORD *)v14 + 31) = a5;
  v15 = (CCBSystem **)(&_this->m_pUtil + 16 * v11 + 32);
  *v15 = (CCBSystem *)a6;
  v15[1] = (CCBSystem *)a7;
  v15[2] = (CCBSystem *)a8;
  v15[3] = (CCBSystem *)a9;
  v14[172] = 1;
  v14[173] = 0;
  *((_DWORD *)v14 + 37) = 0;
  *((_DWORD *)v14 + 38) = a10;
  *((_DWORD *)v14 + 39) = v16;
  *((_DWORD *)v14 + 40) = 0;
  *((_DWORD *)v14 + 36) = (((CCBSystem *)_this->m_pUtil))->CCBSystem::ProcProtect();
  *((_DWORD *)v14 + 41) = -1;
  ++LODWORD(_this->m_fTimeScale);
  return v11;
}

// 0x004DFAA0
int InitRound(CCBStage *_this, float fVal1, int nVal2, float fVal3, int nVal4)
{
  int result; // eax

  strcpy((char *)&_this->m_pRole[70 * (int)_this->m_pCamControl], (const char *)LODWORD(fVal1));
  _this->m_TaskArrC[(int)_this->m_pCamControl].m_fSlot0 = *(float *)&nVal2;
  _this->m_TaskArrC[(int)_this->m_pCamControl].m_fSlot1 = fVal3;
  *((_DWORD *)&_this->m_pScene + 70 * (int)_this->m_pCamControl) = 1;
  _this->m_TaskArrC[(int)_this->m_pCamControl].m_fSlot3 = 24.0;
  *((_DWORD *)&_this->m_pCBSystem + 70 * ((int)_this->m_pCamControl + 1)) = nVal4;
  result = (int)_this->m_pCamControl + 1;
  _this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFE00
int CCBStage_AddTextLabel(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  int v4; // [esp+0xC] [ebp+0x8]
  int v5; // [esp+0x10] [ebp+0xC]
  int v6; // [esp+0x14] [ebp+0x10]

  v2 = v1;
  sprintf((char *const)(v1 + 280 * *(_DWORD *)(v1 + 16) + 24), (const char *)&dir[20], v5);
  *(float *)(v2 + 280 * *(_DWORD *)(v2 + 16) + 284) = ((double)nVal + (double)nVal) / (double)g_DrvInfo.width - 1.0;
  *(float *)(v2 + 280 * *(_DWORD *)(v2 + 16) + 288) = 1.0 - ((double)v4 + (double)v4) / (double)g_DrvInfo.height;
  *(_DWORD *)(v2 + 280 * *(_DWORD *)(v2 + 16) + 20) = 2;
  *(_DWORD *)(v2 + 280 * *(_DWORD *)(v2 + 16) + 296) = 1094713344;
  *(_DWORD *)(v2 + 280 * (*(_DWORD *)(v2 + 16) + 1)) = v6;
  result = *(_DWORD *)(v2 + 16) + 1;
  *(_DWORD *)(v2 + 16) = result;
  return result;
}

// 0x004DFED0
int EndTurnAndAdvance(int nVal1, int nVal2, int nVal3, int nVal4, int nVal5)
{
  int result; // eax
  char v6; // [esp+0x14] [ebp+0x14]

  *(float *)(nVal1 + 280 * *(_DWORD *)(nVal1 + 16) + 284) = *(float *)&nVal2;
  *(float *)(nVal1 + 280 * *(_DWORD *)(nVal1 + 16) + 288) = *(float *)&nVal3;
  *(float *)(nVal1 + 280 * *(_DWORD *)(nVal1 + 16) + 292) = *(float *)&nVal4;
  *(float *)(nVal1 + 280 * *(_DWORD *)(nVal1 + 16) + 296) = *(float *)&nVal5;
  *(_DWORD *)(nVal1 + 280 * *(_DWORD *)(nVal1 + 16) + 20) = 5;
  *(_DWORD *)(nVal1 + 280 * (*(_DWORD *)(nVal1 + 16) + 1)) = *(_DWORD *)(nVal1 + 8);
  *(_BYTE *)(nVal1 + 280 * *(_DWORD *)(nVal1 + 16) + 283) = v6;
  result = *(_DWORD *)(nVal1 + 16) + 1;
  *(_DWORD *)(nVal1 + 16) = result;
  return result;
}

// 0x004E0A30
int DialogFunc(HWND hDlg, UINT uMsg, WPARAM a3, LPARAM lParam)
{
  return (((CCBUI *)pfVal))->CCBUI::DlgProcEditorMain(hDlg, uMsg, a3, lParam);
}

// 0x004E5300
LRESULT EditBoxSetReadOnly(HWND hWnd, BOOL bReadOnly)
{
  if ( bReadOnly )
    return SendMessageA(hWnd, 0xF1u, 1u, 0);
  else
    return SendMessageA(hWnd, 0xF1u, 0, 0);
}

// 0x004E5330
BOOL EditBoxIsModified(HWND hWnd)
{
  BOOL result; // eax

  result = SendMessageA(hWnd, 0xF0u, 0, 0);
  return result;
}

// 0x004E5350
LRESULT EditBoxSetFloat(HWND hWnd, float fValue)
{
  sprintf((char *const)&g_CCBStageCamBuffer, "%1.5f", fValue);
  return SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
}

// 0x004E5390
LRESULT EditBoxSetInt(HWND hWnd, int nValue)
{
  sprintf((char *const)&g_CCBStageCamBuffer, (const char *)&dir[20], nValue);
  return SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_CCBStageCamBuffer);
}

// 0x004E5410
char * GetEditBoxText(HWND hWnd)
{
  SendMessageA(hWnd, 0xDu, 0xFAu, (LPARAM)&g_CCBStageCamBuffer);
  return (char *)&g_CCBStageCamBuffer;
}

// 0x004E5430
double EditBoxGetFloat(HWND hWnd)
{
  SendMessageA(hWnd, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
  return atof((const char *)&g_CCBStageCamBuffer);
}

// 0x004E5460
int EditBoxGetInt(HWND hWnd)
{
  SendMessageA(hWnd, 0xDu, 0x14u, (LPARAM)&g_CCBStageCamBuffer);
  return atoi((const char *)&g_CCBStageCamBuffer);
}

// 0x004EC480
// attributes: thunk
int nearby_4ec480()
{
  int result; // eax

  nearby_4ec490();
  return result;
}

// 0x004EC490
void nearby_4ec490()
{
  flt_17AA800 = 12.0 + 12.0;
}

// 0x004F2750
int CCBRoleState_CheckBoss(int *arg0, int roleIdx)
{
  CCBRoleState *v2; // ecx
  CCBRoleState *v3; // esi

  v3 = (CCBRoleState *)v2;
  if ( arg0[1] != 6230 || (((CCBRoleState *)v2))->CCBRoleState::IsRoleInForce(roleIdx) )
  {
    (((CCBRoleState *)v3))->CCBRoleState::CheckRoleNimbus((int)arg0, roleIdx);
    (((CCBRoleState *)v3))->CCBRoleState::IsBoss(arg0, roleIdx);
    return (((CCBRoleState *)v3))->CCBRoleState::CalcCombatDamage(roleIdx);
  }
  else
  {
    (((CCBRoleState *)v3))->CCBRoleState::AddCommand(roleIdx, -99999999, 1);
    return 0;
  }
}

// 0x005020D0
int CCBRoleState_CalcTurnDelay(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ecx
  int v4; // edx
  int v5; // edi
  float v7; // st7
  char v8; // al
  float fVal; // [esp+0x8] [ebp-0x4]

  v2 = v1;
  v3 = 329 * *(_DWORD *)(v1 + 160);
  v4 = 80 * *(_DWORD *)(v2 + 164);
  v5 = v4 + v2 + 8 * v3 + 184;
  if ( *(_BYTE *)(v4 + v2 + 8 * v3 + 225) )
  {
    v7 = (1.0f
        - (*(float *)(*(_DWORD *)v2 + 80) - *(float *)(v4 + v2 + 8 * v3 + 208)) / *(float *)(v4 + v2 + 8 * v3 + 216))
       * 255.0;
    fVal = v7;
    if ( v7 <= 255.0f )
    {
      if ( fVal < 0.0f )
        fVal = 0.0f;
    }
    else
    {
      fVal = 255.0f;
    }
    (((CCBStage *)*(CCBStage **)(v2 + 68)))->CCBStage::CalculateTurnOrder(fVal, *(_DWORD *)(v4 + v2 + 8 * v3 + 228));
    if ( *(_BYTE *)(v5 + 43) == 1
      || *(float *)(*(_DWORD *)v2 + 80) - *(float *)(v5 + 24) > *(float *)(v5 + 32)
      || ((((GRPinput *)&g_Input))->GRPinput::SetJoystickAbs(), v8) )
    {
      (((CCBStage *)*(CCBStage **)(v2 + 68)))->CCBStage::CalculateTurnOrder(0.0, *(_DWORD *)(v5 + 44));
      *(_DWORD *)(v5 + 16) = 4;
    }
    return 0;
  }
  else
  {
    *(_BYTE *)(v4 + v2 + 8 * v3 + 225) = 1;
    return 0;
  }
}

// 0x00503020
void ResetAll(CCBStage *_this)
{
    unsigned long reg_EDI = 0;

  int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // edi
  ECBRoleTaskMode *v7; // eax
  int v8; // ecx
  int *v9; // eax
  float *v10; // eax
  float v11; // eax
  int *v12; // esi
  gbVec3D *v13; // eax
  float *v14; // eax
  float y; // edx
  float v16; // eax
  int *p_eMode; // eax
  int *p_fTemp; // eax
  float *v19; // eax
  float v20; // eax
  int v21; // ebx
  float *v22; // eax
  float v23; // ecx
  float v24; // edx
  float *p_x; // eax
  int *v27; // eax
  int *v28; // eax
  float *v29; // eax
  float v30; // eax
  gbVec3D *v31; // eax
  float v32; // [esp+0x18] [ebp-0x38]
  float v33; // [esp+0x18] [ebp-0x38]
  float v34; // [esp+0x18] [ebp-0x38]
  float v35; // [esp+0x18] [ebp-0x38]
  float v36; // [esp+0x18] [ebp-0x38]
  float v37; // [esp+0x18] [ebp-0x38]
  float v38; // [esp+0x18] [ebp-0x38]
  float v39; // [esp+0x1C] [ebp-0x34]
  float v40; // [esp+0x1C] [ebp-0x34]
  float v41; // [esp+0x1C] [ebp-0x34]
  float v42; // [esp+0x1C] [ebp-0x34]
  float v43; // [esp+0x1C] [ebp-0x34]
  float v44; // [esp+0x1C] [ebp-0x34]
  float v45; // [esp+0x1C] [ebp-0x34]
  float v46; // [esp+0x20] [ebp-0x30]
  float v47; // [esp+0x20] [ebp-0x30]
  float v48; // [esp+0x20] [ebp-0x30]
  float v49; // [esp+0x20] [ebp-0x30]
  float v50; // [esp+0x20] [ebp-0x30]
  float v51; // [esp+0x20] [ebp-0x30]
  float v52; // [esp+0x20] [ebp-0x30]
  int v53; // [esp+0x24] [ebp-0x2C]
  int v54; // [esp+0x24] [ebp-0x2C]
  int v55; // [esp+0x24] [ebp-0x2C]
  int v56; // [esp+0x24] [ebp-0x2C]
  int p_DWORD; // [esp+0x30] [ebp-0x20] BYREF
  int pnVal; // [esp+0x34] [ebp-0x1C] BYREF
  struct gbVec3D v59; // [esp+0x38] [ebp-0x18] BYREF
  gbVec3D v60; // [esp+0x44] [ebp-0xC] BYREF
  gbVec3D *v61; // [esp+0x54] [ebp+0x4]
  int nVal; // [esp+0x58] [ebp+0x8]

  if ( (g_nCBStageFlags[7] & 1) == 0 )
  {
    g_nCBStageFlags[4] = 0;
    LOBYTE(g_nCBStageFlags[7]) |= 1u;
    g_nCBStageFlags[5] = 0;
    g_nCBStageFlags[6] = 0;
    atexit(nullsub_30);
  }
  if ( (g_nCBStageFlags[7] & 2) == 0 )
  {
    g_nCBStageFlags[0] = 0;
    LOBYTE(g_nCBStageFlags[7]) |= 2u;
    g_nCBStageFlags[1] = 0;
    g_nCBStageFlags[2] = 0;
    atexit(nullsub_29);
  }
  if ( (g_nCBStageFlags[7] & 4) == 0 )
  {
    *(_DWORD *)&g_CCBStageState = 0;
    LOBYTE(g_nCBStageFlags[7]) |= 4u;
    *((_DWORD *)&g_CCBStageState + 1) = 0;
    *((_DWORD *)&g_CCBStageState + 2) = 0;
    atexit(nullsub_28);
  }
  v2 = nVal;
  p_DWORD = -1;
  pnVal = -1;
  v3 = *(_DWORD *)(nVal + 12);
  if ( v3 == -1 )
  {
    (((CCBRoleState *)_this->m_pRoleState))->CCBRoleState::WriteBackRoleData(nVal, &p_DWORD, &pnVal);
    v5 = v4;
    if ( v4 <= 11 )
    {
      p_eMode = (int *)&_this->m_pRole[v4]->m_Task[62].eMode;
      g_nCBStageFlags[0] = *p_eMode;
      g_nCBStageFlags[1] = p_eMode[1];
      g_nCBStageFlags[2] = p_eMode[2];
      p_fTemp = (int *)&_this->m_pRole[*(_DWORD *)(nVal + 8)]->m_Task[62].fTemp;
      g_nCBStageFlags[4] = *p_fTemp;
      g_nCBStageFlags[5] = p_fTemp[1];
      g_nCBStageFlags[6] = p_fTemp[2];
      __asm
      {
        fld     g_nCBStageFlags+0x18
        fsub    g_nCBStageFlags+8
        fstp    [esp+0x30+var_30]; float
        fld     g_nCBStageFlags+0x14
        fsub    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]; float
        fld     g_nCBStageFlags+0x10
        fsub    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38]; float }
      gbVec3D::gbVec3D(&v60, v35, v42, v49);
      v59.x = *v19;
      v59.y = v19[1];
      v20 = v19[2];
      *(float *)&g_CCBStageState = v59.x;
      v59.z = v20;
      *((_DWORD *)&g_CCBStageState + 1) = LODWORD(v59.y);
      *((float *)&g_CCBStageState + 2) = v20;
      (((gbVec3D *)&g_CCBStageState))->gbVec3D::Normalize();
      v21 = *(_DWORD *)(nVal + 8);
      if ( v21 == 4 && *(_BYTE *)(*(&g_RoleSlotBuf.dword_17AA450 + 12) + 613) == 1 )
      {
        (((CCBStage *)_this->m_pRole[4]))->CCBStage::GetStatus(v53);
        // __asm { fstp    [esp+0x2C+nVal] }
        (((CCBStage *)_this->m_pRole[v5]))->CCBStage::GetStatus(v54);
        __asm
        {
          fadd    [esp+0x2C+nVal]
          fadd    _flt_80_0
        }
      }
      else
      {
        (((CCBStage *)_this->m_pRole[v21]))->CCBStage::GetStatus(v53);
        // __asm { fstp    [esp+0x2C+nVal] }
        (((CCBStage *)_this->m_pRole[v5]))->CCBStage::GetStatus(v55);
        // __asm { fadd    [esp+0x2C+nVal] }
      }
      __asm
      {
        fld     dword ptr g_CCBStageState
        fmul    st, st(1)
      }
      __asm
      {
        fstp    dword ptr g_CCBStageState
        fld     dword ptr g_CCBStageState+4
        fmul    st, st(1)
        fstp    dword ptr g_CCBStageState+4
        fld     dword ptr g_CCBStageState+8
        fmul    st, st(1)
        fstp    dword ptr g_CCBStageState+8
        fstp    st
        fld     dword ptr g_CCBStageState+8
        fadd    g_nCBStageFlags+8
        fstp    [esp+0x30+var_30]; float
        fld     dword ptr g_CCBStageState+4
        fadd    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]; float
        fld     dword ptr g_CCBStageState
        fadd    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38]; float }
      gbVec3D::gbVec3D(&v60, v36, v43, v50);
      v59.x = *v22;
      v23 = v22[1];
      // __asm { fld     [esp+0x20+var_18] }
      v24 = v22[2];
      p_x = (float *)&v61->x;
      v59.y = v23;
      v59.z = v24;
      __asm { fstp    dword ptr [eax] }
      *p_x = _ET1;
      v61->y = v23;
      v61->z = v24;
    }
    else
    {
      reg_EDI = (unsigned long)v61;
      v7 = (ECBRoleTaskMode *)&_this->m_pRole[p_DWORD]->m_Task[62].eMode;
      v61->x = *(float *)v7;
      v8 = pnVal;
      v61->y = *(float *)&v7[4];
      v61->z = *(float *)&v7[8];
      v9 = (int *)&_this->m_pRole[v8]->m_Task[62].eMode;
      g_nCBStageFlags[4] = *v9;
      g_nCBStageFlags[5] = v9[1];
      g_nCBStageFlags[6] = v9[2];
      __asm
      {
        fld     g_nCBStageFlags+0x18
        fadd    dword ptr [edi+8]
        fstp    [esp+0x30+var_30]; float
        fld     g_nCBStageFlags+0x14
        fadd    dword ptr [edi+4]
      }
      __asm
      {
        fstp    [esp+0x34+var_34]; float
        fld     g_nCBStageFlags+0x10
        fadd    dword ptr [edi]
      }
      // __asm { fstp    [esp+0x38+var_38]; float }
      gbVec3D::gbVec3D(&v60, v32, v39, v46);
      v59.x = *v10;
      __asm
      {
        fld     [esp+0x2C+var_18]
        fmul    dword ptr [flt_56A610]
      }
      v59.y = v10[1];
      v11 = v10[2];
      __asm
      {
        fstp    g_nCBStageFlags
        fld     [esp+0x2C+var_18+4]
        fmul    dword ptr [flt_56A610]
      }
      v59.z = v11;
      __asm
      {
        fstp    g_nCBStageFlags+4
        fld     [esp+0x2C+var_18+8]
        fmul    dword ptr [flt_56A610]
        fstp    g_nCBStageFlags+8
      }
      v12 = (int *)&_this->m_pRole[*(_DWORD *)(nVal + 8)]->m_Task[62].fTemp;
      g_nCBStageFlags[4] = *v12;
      g_nCBStageFlags[5] = v12[1];
      g_nCBStageFlags[6] = v12[2];
      __asm
      {
        fld     g_nCBStageFlags+0x18
        fsub    g_nCBStageFlags+8
        fstp    [esp+0x30+var_30]; float
        fld     g_nCBStageFlags+0x14
        fsub    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]; float
        fld     g_nCBStageFlags+0x10
        fsub    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38]; float }
      gbVec3D::gbVec3D(&v60, v33, v40, v47);
      v59 = *v13;
      *(gbVec3D *)&g_CCBStageState = v59;
      (((gbVec3D *)&g_CCBStageState))->gbVec3D::Normalize();
      __asm
      {
        fld     dword ptr g_CCBStageState
        fmul    _flt_40_0
      }
      __asm
      {
        fstp    dword ptr g_CCBStageState
        fld     dword ptr g_CCBStageState+4
        fmul    _flt_40_0
        fstp    dword ptr g_CCBStageState+4
        fld     dword ptr g_CCBStageState+8
        fmul    _flt_40_0
        fst     dword ptr g_CCBStageState+8
        fadd    g_nCBStageFlags+8
        fstp    [esp+0x30+var_30]; float
        fld     dword ptr g_CCBStageState+4
        fadd    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]; float
        fld     dword ptr g_CCBStageState
        fadd    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38]; float }
      gbVec3D::gbVec3D(&v60, v34, v41, v48);
      v59.x = *v14;
      v59.y = v14[1];
      y = v59.y;
      v16 = v14[2];
      v61->x = v59.x;
      v61->y = y;
      v61->z = v16;
      v59.z = v16;
    }
  }
  else
  {
    v27 = (int *)&_this->m_pRole[v3]->m_Task[62].eMode;
    g_nCBStageFlags[0] = *v27;
    g_nCBStageFlags[1] = v27[1];
    g_nCBStageFlags[2] = v27[2];
    v28 = (int *)&_this->m_pRole[*(_DWORD *)(nVal + 8)]->m_Task[62].fTemp;
    g_nCBStageFlags[4] = *v28;
    g_nCBStageFlags[5] = v28[1];
    g_nCBStageFlags[6] = v28[2];
    __asm
    {
      fld     g_nCBStageFlags+0x18
      fsub    g_nCBStageFlags+8
      fstp    [esp+0x30+var_30]; float
      fld     g_nCBStageFlags+0x14
      fsub    g_nCBStageFlags+4
    }
    __asm
    {
      fstp    [esp+0x34+var_34]; float
      fld     g_nCBStageFlags+0x10
      fsub    g_nCBStageFlags
    }
    // __asm { fstp    [esp+0x38+var_38]; float }
    gbVec3D::gbVec3D(&v60, v37, v44, v51);
    v59.x = *v29;
    v59.y = v29[1];
    v30 = v29[2];
    *(float *)&g_CCBStageState = v59.x;
    v59.z = v30;
    *((_DWORD *)&g_CCBStageState + 1) = LODWORD(v59.y);
    *((float *)&g_CCBStageState + 2) = v30;
    (((gbVec3D *)&g_CCBStageState))->gbVec3D::Normalize();
    (((CCBStage *)_this->m_pRole[*(_DWORD *)(nVal + 12)]))->CCBStage::GetStatus(v53);
    // __asm { fstp    [esp+0x2C+nVal] }
    (((CCBStage *)_this->m_pRole[*(_DWORD *)(v2 + 8)]))->CCBStage::GetStatus(v56);
    __asm
    {
      fadd    [esp+0x2C+nVal]
      fld     dword ptr g_CCBStageState
      fmul    st, st(1)
      fstp    dword ptr g_CCBStageState
      fld     dword ptr g_CCBStageState+4
      fmul    st, st(1)
      fstp    dword ptr g_CCBStageState+4
      fld     dword ptr g_CCBStageState+8
      fmul    st, st(1)
      fstp    dword ptr g_CCBStageState+8
    }
    __asm { fstp    st }
    if ( (((CCBRoleState *)_this->m_pRoleState))->CCBRoleState::InitUI(*(_DWORD *)(v2 + 8))->dwID == 7364
      || (((CCBRoleState *)_this->m_pRoleState))->CCBRoleState::InitUI(*(_DWORD *)(v2 + 8))->dwID == 7381 )
    {
      __asm
      {
        fld     dword ptr g_CCBStageState
        fadd    st, st
        fstp    dword ptr g_CCBStageState
        fld     dword ptr g_CCBStageState+4
        fadd    st, st
        fstp    dword ptr g_CCBStageState+4
        fld     dword ptr g_CCBStageState+8
        fadd    st, st
        fstp    dword ptr g_CCBStageState+8
      }
    }
    __asm
    {
      fld     dword ptr g_CCBStageState+8
      fadd    g_nCBStageFlags+8
    }
    __asm
    {
      fstp    [esp+0x30+var_30]; float
      fld     dword ptr g_CCBStageState+4
      fadd    g_nCBStageFlags+4
    }
    __asm
    {
      fstp    [esp+0x34+var_34]; float
      fld     dword ptr g_CCBStageState
      fadd    g_nCBStageFlags
    }
    // __asm { fstp    [esp+0x38+var_38]; float }
    gbVec3D::gbVec3D(&v60, v38, v45, v52);
    v59 = *v31;
    (((gbVec3D *)v61))->gbVec3D::operator=(*(&v59));
  }
}

// 0x00504F40
char ReadStageCamConfig()
{
  int v0; // ecx
  int v1; // edi
  gbVFile *v2; // esi
  OpenBaseFile v4; // [esp+0x3C] [ebp-0x810] BYREF
  char pExceptionObject[1024]; // [esp+0x40] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x440] [ebp-0x40C] BYREF
  int v7; // [esp+0x848] [ebp-0x4]

  v1 = v0;
  v7 = 0;
  v2 = (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::OpenFile("cbdata\\flexcam.dat", 0x201u);
  if ( !v2 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(aCouldnTOpenCbC, aDProjectPal3Co_9, 734),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Seek(v2, 0, 1);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read((void *)v1, 0x639C0u, v2);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read((void *)(v1 + 408000), 0x7D0u, v2);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::Read((void *)(v1 + 410000), 0x4E20u, v2);
  (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::CloseFile(v2);
  v7 = -1;
  ((OpenNULLFile *)&v4)->OpenNULLFile::OpenNULLFile();
  return 1;
}

// 0x00508280
int CCBCamControl_Init()
{
  int result; // eax

  *((_QWORD *)&g_CCBCamControlData + 188) = 0x14300000080i64;
  result = 716;
  *((_QWORD *)&g_CCBCamControlData + 189) = 0x2CC00000207i64;
  return result;
}

// 0x00511690
char CCBStageScene_Update()
{
  _DWORD *v0; // ecx
  _DWORD *v1; // ebp
  int v3; // edi
  int i; // esi
  CIniFile v5; // [esp+0x18] [ebp-0x14] BYREF
  int v6; // [esp+0x28] [ebp-0x4]

  v1 = (_DWORD *)v0;
  if ( (g_dwGameFlags & 2) != 0 )
    return 1;
  v3 = 0;
  v6 = 0;
  (((CIniFile *)&v5))->CIniFile::OpenFileWrite("datascript\\combat.ini");
  (((CIniFile *)&v5))->CIniFile::WriteSection(aRolepos);
  for ( i = 24; i < 68; i += 4 )
  {
    sprintf(byte_17ABE00, "Role%d-x", v3);
    (((CIniFile *)&v5))->CIniFile::WriteLine(byte_17ABE00, *(float *)(*(_DWORD *)(i + *v1) + 6584));
    sprintf(byte_17ABE00, "Role%d-z", v3);
    (((CIniFile *)&v5))->CIniFile::WriteLine(byte_17ABE00, *(float *)(*(_DWORD *)(i + *v1) + 6592));
    ++v3;
  }
  v6 = -1;
  (((CIniFile *)&v5))->CIniFile::~CIniFile();
  return 1;
}

// 0x00516940
int CCBUI_InitResultPanels(int nVal)
{
  int v1; // ecx
  int v2; // esi
  UIPushButton **v3; // edi
  int result; // eax
  UIPushButton *v5; // ecx
  UIPushButton **v6; // edi
  UIPushButton *v7; // ecx
  int v8; // [esp+0x10] [ebp-0x10] BYREF
  int v9; // [esp+0x14] [ebp-0xC]
  int v10; // [esp+0x18] [ebp-0x8]
  int v11; // [esp+0x1C] [ebp-0x4]

  v2 = v1;
  v9 = 0;
  v3 = (UIPushButton **)(v1 + 1012);
  v10 = 0;
  v8 = 0;
  v11 = 0;
  (((CCBAIWindow *)v1))->CCBAIWindow::Reset((int *)(v1 + 1012));
  if ( (_BYTE)result )
  {
    v5 = (UIPushButton *)*v3;
    v8 = 150;
    v10 = 406;
    v9 = -50;
    v11 = 462;
    (*(void ( **)(UIPushButton *, int, int *, int))(*(_DWORD *)((UIWnd *)v5) + 16))(v5, 800, &v8, v2);
    (((UIPushButton *)*v3))->UIPushButton::CreateFromTemplate(&unk_5DEA20, 0);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*v3)))((UIPushButton *)(*v3), (_DWORD)(0));
    v6 = (UIPushButton **)(v2 + 1016);
    (((CCBAIWindow *)v2))->CCBAIWindow::Reset((int *)(v2 + 1016));
    if ( (_BYTE)result )
    {
      v7 = (UIPushButton *)*v6;
      v8 = 150;
      v10 = 406;
      v9 = -50;
      v11 = 462;
      (*(void ( **)(UIPushButton *, int, int *, int))(*(_DWORD *)((UIWnd *)v7) + 16))(v7, 816, &v8, v2);
      (((UIPushButton *)*v6))->UIPushButton::CreateFromTemplate(&unk_5DEA00, 0);
      result = (**(int ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*v6)))((UIPushButton *)(*v6), (_DWORD)(0));
      LOBYTE(result) = 1;
    }
  }
  return result;
}

// 0x00516A30
int CCBUI_SetupAIWindow(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // edi
  int *v4; // ebx
  int result; // eax
  int v6; // ecx
  int *v7; // ebx
  int v8; // edi
  UIPushButton **v9; // ebp
  int v10; // ecx
  UIPushButton *v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // edi
  UIProgressBar **v17; // ebp
  UIProgressBar **v18; // ebx
  int v19; // ecx
  int v20; // ecx
  UIProgressBar *v21; // ecx
  UIProgressBar *v22; // ecx
  int *v23; // ebx
  int v24; // edi
  UIPushButton **v25; // ebp
  int v26; // eax
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // ecx
  int v40; // eax
  int v41; // ecx
  int v42; // eax
  int v43; // ecx
  int v44; // eax
  int v45; // ecx
  int v46; // [esp+0x138] [ebp-0x20]
  int v47; // [esp+0x148] [ebp-0x10] BYREF
  int v48; // [esp+0x14C] [ebp-0xC]
  int v49; // [esp+0x150] [ebp-0x8]
  int v50; // [esp+0x154] [ebp-0x4]

  v48 = 0;
  v49 = 0;
  v2 = v1;
  v47 = 0;
  v50 = 0;
  v3 = 0;
  while ( 1 )
  {
    v4 = (int *)(v2 + 4 * v3 + 120);
    (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v4);
    if ( !(_BYTE)result )
      break;
    v6 = (unsigned long)*v4;
    v47 = g_nStatePanelL_dup[v3];
    v49 = v47 + 157;
    v48 = g_nStatePanelT_dup[v3];
    v50 = v48 + 106;
    (*(void ( **)(int, int, int *, int, int))(*(_DWORD *)v6 + 16))(v6, g_nItemTypeBase[v3], &v47, v2, v46);
    if ( v3 )
      (((UIPushButton *)*v4))->UIPushButton::CreateFromTemplate(&unk_5DF2E0, 0);
    else
      (((UIPushButton *)*(UIPushButton **)(v2 + 120)))->UIPushButton::CreateFromTemplate(&unk_5DF300, 0);
    (((NPC *)*v4))->NPC::UpdateAnim(-1);
    v46 = 0;
    (**(void ( ***)(int))*v4)((int)(*v4));
    if ( ++v3 >= 4 )
    {
      v7 = (int *)(v2 + 156);
      v8 = 0;
      while ( 1 )
      {
        v9 = (UIPushButton **)(v7 - 5);
        (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v7 - 5);
        if ( !(_BYTE)result )
          goto LABEL_61;
        (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v7);
        if ( !(_BYTE)result )
          goto LABEL_61;
        v10 = g_nSpriteSize_64[v8];
        v50 = g_nSpriteSize_82[v8] + 12;
        v49 = v10 + 6;
        v11 = (UIPushButton *)*v9;
        v12 = g_nItemIDs_69[v8];
        v47 = 6;
        v48 = 12;
        (*(void ( **)(UIPushButton *, int, int *, int))(*(_DWORD *)((UIWnd *)v11) + 16))(v11, v12, &v47, v2);
        (((UIPushButton *)*v9))->UIPushButton::CreateFromTemplate(*(_UNKNOWN **)((char *)&off_57042C + v8 * 4), 0);
        (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)(*v9)))((UIPushButton *)(*v9), (_DWORD)(0));
        v13 = g_nSpriteSize_20[v8];
        v50 = g_nUnkDataTable[v8] + 10;
        v49 = v13 + 10;
        v14 = (unsigned long)*v7;
        v15 = g_nSkillItemIDTable[v8];
        v47 = 10;
        v48 = 10;
        (*(void ( **)(int, int, int *, int))(*(_DWORD *)v14 + 16))(v14, v15, &v47, v2);
        (((UIPushButton *)*v7))->UIPushButton::CreateFromTemplate(*(_UNKNOWN **)((char *)&off_570440 + v8 * 4), 0);
        (**(void ( ***)(int, _DWORD))*v7)((int)(*v7), (_DWORD)(0));
        ++v8;
        ++v7;
        if ( v8 >= 5 )
        {
          v16 = 0;
          while ( sub_51CC20((_DWORD *)(v2 + 4 * v16 + 1020)) )
          {
            v17 = (UIProgressBar **)(v2 + 4 * v16 + 1036);
            if ( !sub_51CC20(v17) )
              break;
            v18 = (UIProgressBar **)(v2 + 4 * v16 + 1052);
            if ( !sub_51CC20(v18) )
              break;
            if ( !v16 )
            {
              if ( !sub_51CC20((_DWORD *)(v2 + 1068)) )
                goto LABEL_61;
              v19 = *(_DWORD *)(v2 + 1068);
              v47 = g_nCCBAIWindow_17ACB8C;
              v49 = g_nCCBAIWindow_17ACB8C + 30;
              v48 = g_nAIWindowBase;
              v50 = g_nAIWindowBase + 86;
              (*(void ( **)(int, int, int *, int))(*(_DWORD *)v19 + 16))(v19, 20, &v47, v2);
              (((UIScene *)*(UIScene **)(v2 + 1068)))->UIScene::GetChildCount();
              (((UIScene *)*(UIScene **)(v2 + 1068)))->UIScene::GetChildAt();
              sub_43FDB0(*(float **)(v2 + 1068), 2);
              (((UIProgressBar *)*(UIProgressBar **)(v2 + 1068)))->UIProgressBar::GetHeight(5);
              (((UIProgressBar *)*(UIProgressBar **)(v2 + 1068)))->UIProgressBar::GetPosition(2);
              (((CCBFiveNimbusWindow *)*(CCBFiveNimbusWindow **)(v2 + 1068)))->CCBFiveNimbusWindow::CalcHitAngle(1);
              *(_DWORD *)(*(_DWORD *)(v2 + 1068) + 72) = 0;
              (((UIScrollBar *)*(UIScrollBar **)(v2 + 1068)))->UIScrollBar::SetRange(50.0);
              (((UIProgressBar *)*(UIProgressBar **)(v2 + 1068)))->UIProgressBar::FindChildByName(0.0);
              (***(void ( ****)(_DWORD, _DWORD))(v2 + 1068))((_DWORD)(*(_DWORD *)(v2 + 1068)), (_DWORD)(0));
            }
            v20 = *(_DWORD *)(v2 + 4 * v16 + 1020);
            v47 = g_nCBCamState[v16 + 2];
            v49 = v47 + 85;
            v48 = g_nCBCamState[v16 + 6];
            v50 = v48 + 12;
            (*(void ( **)(int, int, int *, int))(*(_DWORD *)v20 + 16))(v20, g_nSkillTabIDs[v16], &v47, v2);
            (((UIScene *)*(UIScene **)(v2 + 4 * v16 + 1020)))->UIScene::GetChildCount();
            (((UIScene *)*(UIScene **)(v2 + 4 * v16 + 1020)))->UIScene::GetChildAt();
            sub_43FDB0(*(float **)(v2 + 4 * v16 + 1020), -2);
            (((UIProgressBar *)*(UIProgressBar **)(v2 + 4 * v16 + 1020)))->UIProgressBar::GetWidth(7);
            (((UIProgressBar *)*(UIProgressBar **)(v2 + 4 * v16 + 1020)))->UIProgressBar::GetHeight(1);
            (((UIProgressBar *)*(UIProgressBar **)(v2 + 4 * v16 + 1020)))->UIProgressBar::GetPosition(1);
            (***(void ( ****)(_DWORD, _DWORD))(v2 + 4 * v16 + 1020))((_DWORD)(*(_DWORD *)(v2 + 4 * v16 + 1020)), (_DWORD)(0));
            *(_DWORD *)(*(_DWORD *)(v2 + 4 * v16 + 1020) + 112) = 1077936128;
            v47 = g_nCBCamState[v16 + 10];
            v49 = v47 + 85;
            v21 = (UIProgressBar *)*v17;
            v48 = g_nCBCamState[v16 + 14];
            v50 = v48 + 12;
            (*(void ( **)(UIProgressBar *, int, int *, int))(*(_DWORD *)((UIWnd *)v21) + 16))(
              v21,
              g_nMagicTabIDs[v16],
              &v47,
              v2);
            (((UIScene *)*v17))->UIScene::GetChildCount();
            (((UIScene *)*v17))->UIScene::GetChildAt();
            sub_43FDB0((float *)*v17, -2);
            (((UIProgressBar *)*v17))->UIProgressBar::GetWidth(7);
            (((UIProgressBar *)*v17))->UIProgressBar::GetHeight(1);
            (((UIProgressBar *)*v17))->UIProgressBar::GetPosition(1);
            (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)(*v17)))((UIProgressBar *)(*v17), (_DWORD)(0));
            (*v17)->m_radius = 1077936128;
            v47 = g_nCBCamState[v16 + 18];
            v49 = v47 + 85;
            v22 = (UIProgressBar *)*v18;
            v48 = g_nCBCamState[v16 + 22];
            v50 = v48 + 12;
            (*(void ( **)(UIProgressBar *, int, int *, int))(*(_DWORD *)((UIWnd *)v22) + 16))(
              v22,
              g_nItemTabIDs[v16],
              &v47,
              v2);
            (((UIScene *)*v18))->UIScene::GetChildCount();
            (((UIScene *)*v18))->UIScene::GetChildAt();
            sub_43FDB0((float *)*v18, -2);
            (((UIProgressBar *)*v18))->UIProgressBar::GetWidth(7);
            (((UIProgressBar *)*v18))->UIProgressBar::GetHeight(1);
            (((UIProgressBar *)*v18))->UIProgressBar::GetPosition(1);
            (**(void ( ***)(UIProgressBar *, _DWORD))((UIWnd *)(*v18)))((UIProgressBar *)(*v18), (_DWORD)(0));
            ++v16;
            (*v18)->m_radius = 1077936128;
            if ( v16 >= 4 )
            {
              v23 = (int *)(v2 + 220);
              v24 = 0;
              while ( 1 )
              {
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 - 11);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 11);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 22);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 55);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 66);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 33);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 44);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 77);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 88);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 99);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 110);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 121);
                if ( !(_BYTE)result )
                  break;
                v25 = (UIPushButton **)(v23 + 132);
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 132);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 143);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 154);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 165);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 176);
                if ( !(_BYTE)result )
                  break;
                (((CCBAIWindow *)v2))->CCBAIWindow::Reset(v23 + 187);
                if ( !(_BYTE)result )
                  break;
                v47 = 15;
                v49 = 37;
                v48 = 85;
                v50 = 108;
                if ( v24 < 4 )
                {
                  v26 = g_nStatePanelL_dup[v24];
                  v27 = g_nStatePanelT_dup[v24];
                  v47 = v26 + 15;
                  v48 = v27 + 85;
                  v49 = v26 + 37;
                  v50 = v27 + 108;
                }
                (*(void ( **)(_DWORD, int, int *, int))(*(_DWORD *)*(v23 - 11) + 16))(
                  *(v23 - 11),
                  79,
                  &v47,
                  v2);
                (((UIPushButton *)*(v23 - 11)))->UIPushButton::CreateFromTemplate(&unk_5DECFC, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)*v23 + 16))(*v23, 79, &v47, v2);
                (((UIPushButton *)*v23))->UIPushButton::CreateFromTemplate(&unk_5DECD4, 0);
                v47 = 39;
                v49 = 61;
                v48 = 85;
                v50 = 108;
                if ( v24 < 4 )
                {
                  v28 = g_nStatePanelL_dup[v24];
                  v29 = g_nStatePanelT_dup[v24];
                  v47 = v28 + 39;
                  v48 = v29 + 85;
                  v49 = v28 + 61;
                  v50 = v29 + 108;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[11] + 16))(v23[11], 79, &v47, v2);
                (((UIPushButton *)v23[11]))->UIPushButton::CreateFromTemplate(&unk_5DECA8, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[22] + 16))(v23[22], 79, &v47, v2);
                (((UIPushButton *)v23[22]))->UIPushButton::CreateFromTemplate(&unk_5DEC7C, 0);
                v47 = 63;
                v49 = 85;
                v48 = 85;
                v50 = 108;
                if ( v24 < 4 )
                {
                  v30 = g_nStatePanelL_dup[v24];
                  v31 = g_nStatePanelT_dup[v24];
                  v47 = v30 + 63;
                  v48 = v31 + 85;
                  v49 = v30 + 85;
                  v50 = v31 + 108;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[55] + 16))(v23[55], 79, &v47, v2);
                (((UIPushButton *)v23[55]))->UIPushButton::CreateFromTemplate(&unk_5DEC54, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[66] + 16))(v23[66], 79, &v47, v2);
                (((UIPushButton *)v23[66]))->UIPushButton::CreateFromTemplate(&unk_5DEC2C, 0);
                v47 = 87;
                v49 = 109;
                v48 = 85;
                v50 = 108;
                if ( v24 < 4 )
                {
                  v32 = g_nStatePanelL_dup[v24];
                  v33 = g_nStatePanelT_dup[v24];
                  v47 = v32 + 87;
                  v48 = v33 + 85;
                  v49 = v32 + 109;
                  v50 = v33 + 108;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[33] + 16))(v23[33], 79, &v47, v2);
                (((UIPushButton *)v23[33]))->UIPushButton::CreateFromTemplate(&unk_5DEC04, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[44] + 16))(v23[44], 79, &v47, v2);
                (((UIPushButton *)v23[44]))->UIPushButton::CreateFromTemplate(&unk_5DEBDC, 0);
                v47 = 111;
                v49 = 127;
                v48 = 88;
                v50 = 104;
                if ( v24 < 4 )
                {
                  v34 = g_nStatePanelL_dup[v24];
                  v35 = g_nStatePanelT_dup[v24];
                  v47 = v34 + 111;
                  v48 = v35 + 88;
                  v49 = v34 + 127;
                  v50 = v35 + 104;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[77] + 16))(v23[77], 79, &v47, v2);
                (((UIPushButton *)v23[77]))->UIPushButton::CreateFromTemplate(&unk_5DEBB4, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[88] + 16))(v23[88], 79, &v47, v2);
                (((UIPushButton *)v23[88]))->UIPushButton::CreateFromTemplate(&unk_5DEB90, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[99] + 16))(v23[99], 79, &v47, v2);
                (((UIPushButton *)v23[99]))->UIPushButton::CreateFromTemplate(&unk_5DEB68, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[110] + 16))(v23[110], 79, &v47, v2);
                (((UIPushButton *)v23[110]))->UIPushButton::CreateFromTemplate(&unk_5DEB44, 0);
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[121] + 16))(v23[121], 79, &v47, v2);
                (((UIPushButton *)v23[121]))->UIPushButton::CreateFromTemplate(&unk_5DEB20, 0);
                (*(void ( **)(UIPushButton *, int, int *, int))(*(_DWORD *)((UIWnd *)(*v25)) + 16))(
                  *v25,
                  79,
                  &v47,
                  v2);
                (((UIPushButton *)*v25))->UIPushButton::CreateFromTemplate(&unk_5DEAFC, 0);
                v47 = 111;
                v49 = 131;
                v48 = 88;
                v50 = 105;
                if ( v24 < 4 )
                {
                  v36 = g_nStatePanelL_dup[v24];
                  v37 = g_nStatePanelT_dup[v24];
                  v47 = v36 + 111;
                  v48 = v37 + 88;
                  v49 = v36 + 131;
                  v50 = v37 + 105;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[143] + 16))(v23[143], 79, &v47, v2);
                (((UIPushButton *)v23[143]))->UIPushButton::CreateFromTemplate(&unk_5DEAD4, 0);
                v47 = 111;
                v49 = 129;
                v48 = 88;
                v50 = 106;
                if ( v24 < 4 )
                {
                  v38 = g_nStatePanelL_dup[v24];
                  v47 = v38 + 111;
                  v39 = g_nStatePanelT_dup[v24];
                  v49 = v38 + 129;
                  v48 = v39 + 88;
                  v50 = v39 + 106;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[154] + 16))(v23[154], 79, &v47, v2);
                (((UIPushButton *)v23[154]))->UIPushButton::CreateFromTemplate(&unk_5DEAB0, 0);
                v47 = 111;
                v49 = 130;
                v48 = 88;
                v50 = 105;
                if ( v24 < 4 )
                {
                  v40 = g_nStatePanelL_dup[v24];
                  v47 = v40 + 111;
                  v41 = g_nStatePanelT_dup[v24];
                  v49 = v40 + 130;
                  v48 = v41 + 88;
                  v50 = v41 + 105;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[165] + 16))(v23[165], 79, &v47, v2);
                (((UIPushButton *)v23[165]))->UIPushButton::CreateFromTemplate(&unk_5DEA8C, 0);
                v47 = 111;
                v49 = 129;
                v48 = 88;
                v50 = 105;
                if ( v24 < 4 )
                {
                  v42 = g_nStatePanelL_dup[v24];
                  v47 = v42 + 111;
                  v43 = g_nStatePanelT_dup[v24];
                  v49 = v42 + 129;
                  v48 = v43 + 88;
                  v50 = v43 + 105;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[176] + 16))(v23[176], 79, &v47, v2);
                (((UIPushButton *)v23[176]))->UIPushButton::CreateFromTemplate(&unk_5DEA64, 0);
                v47 = 131;
                v49 = 168;
                v48 = 88;
                v50 = 105;
                if ( v24 < 4 )
                {
                  v44 = g_nStatePanelL_dup[v24];
                  v47 = v44 + 131;
                  v45 = g_nStatePanelT_dup[v24];
                  v49 = v44 + 168;
                  v48 = v45 + 88;
                  v50 = v45 + 105;
                }
                (*(void ( **)(int, int, int *, int))(*(_DWORD *)v23[187] + 16))(v23[187], 79, &v47, v2);
                (((UIPushButton *)v23[187]))->UIPushButton::CreateFromTemplate(&unk_5DEA3C, 0);
                ++v24;
                ++v23;
                if ( v24 >= 11 )
                {
                  return 1;
                }
              }
              goto LABEL_61;
            }
          }
          goto LABEL_61;
        }
      }
    }
  }
LABEL_61:
  return 0;
}

// 0x0051B9A0
int CCBParabolaWindow_Update(int deltatime, int haveinput)
{
  CCBParabolaWindow *v2; // ecx
  CCBParabolaWindow *v3; // ebx
  int v4; // esi
  unsigned int *i; // edi

  v3 = (CCBParabolaWindow *)v2;
  v4 = 0;
  for ( i = &v2[1].m_id; *(_DWORD *)(*i + 56) != 1 || !(((CCBParabolaWindow *)v3))->CCBParabolaWindow::OnMessage(v4, deltatime, haveinput); ++i )
  {
    if ( ++v4 >= 5 )
      return -1;
  }
  return v4;
}

// 0x0051DFD0
void todo_0051DFD0(Actor *_this, int nPanelId)
{
  char **p_m_pRoleParam3; // edi
  char *v4; // edi
  int m_nCachedA; // eax
  void ( **m_pParticleData)(void **, char *, _DWORD *, Actor *); // edx
  int v7; // edx
  char *v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int m_nPathBuffer; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int m_nRoleState0; // ebp
  int v20; // ecx
  int v21; // edx
  int v22; // eax
  RoleAtt *v23; // edx
  int v24; // edx
  int v25; // ecx
  int v26; // eax
  int v27; // ecx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // ecx
  int v38; // edx
  int v39; // edx
  int v40; // edx
  float v41; // eax
  int v42; // edx
  int v43; // ecx
  int v44; // edx
  int v45; // edx
  int v46; // ecx
  int v47; // eax
  RoleAtt *m_pEquipAtt0; // eax
  int v49; // ecx
  RoleAtt *v50; // eax
  int v51; // ecx
  RoleAtt *v52; // eax
  int overlap_RoleSystem_m_partyActor_m_nState; // eax
  int v54; // edx
  RoleAtt *v55; // eax
  int m_nAnimFrames; // ecx
  RoleAtt *v57; // eax
  int v58; // eax
  int v59; // edx
  RoleAtt *v60; // eax
  int v61; // ecx
  RoleAtt *v62; // eax
  int v63; // eax
  float z; // edx
  RoleAtt *v65; // eax
  RoleAtt *v66; // ecx
  int v67; // eax
  float m_fDirY; // edx
  float m_fRoleParam3; // edx
  int v70; // eax
  int v71; // ecx
  float y; // edx
  int v73; // eax
  int v74; // eax
  int v75; // ecx
  unsigned int v76; // edx
  int v77; // ecx
  Actor *m_actarray_begin; // edx
  unsigned int v79; // eax
  int v80; // ecx
  float m_fMatrixParamC; // edx
  unsigned int v82; // eax
  int v83; // eax
  int v84; // ecx
  int v85; // edx
  int v86; // ecx
  int v87; // edx
  char *v88; // eax
  int v89; // ecx
  int m_nInterpState; // edx
  char *v91; // eax
  int v92; // eax
  int v93; // eax
  RoleAtt *v94; // edx
  int v95; // edx
  char *v96; // eax
  int v97; // eax
  char *v98; // eax
  int v99; // eax
  float v100; // edx
  char *v101; // eax
  int v102; // eax
  LONG top; // eax
  RECT pRect; // [esp+0x288] [ebp-0x80] BYREF
  UIPushButton *v105; // [esp+0x298] [ebp-0x70]
  UIPushButton *p_m_nAnimParam1; // [esp+0x29C] [ebp-0x6C]
  UIItem *v107; // [esp+0x2A0] [ebp-0x68]
  char *m_pEquipAtt1; // [esp+0x2A4] [ebp-0x64]
  char *v109; // [esp+0x2A8] [ebp-0x60]
  char *v110; // [esp+0x2AC] [ebp-0x5C]
  char *p_z; // [esp+0x2B0] [ebp-0x58]
  char *p_m_fDirY; // [esp+0x2B4] [ebp-0x54]
  char *p_y; // [esp+0x2B8] [ebp-0x50]
  char *v114; // [esp+0x2BC] [ebp-0x4C]
  char *p_m_fMatrixParamC; // [esp+0x2C0] [ebp-0x48]
  char *v116; // [esp+0x2C4] [ebp-0x44]
  int v117; // [esp+0x2C8] [ebp-0x40] BYREF
  int v118; // [esp+0x2CC] [ebp-0x3C]
  int v119; // [esp+0x2D0] [ebp-0x38]
  int v120; // [esp+0x2D4] [ebp-0x34]
  char *v121; // [esp+0x2D8] [ebp-0x30] BYREF
  int v122; // [esp+0x2DC] [ebp-0x2C]
  char *v123; // [esp+0x2E0] [ebp-0x28]
  int v124; // [esp+0x2E4] [ebp-0x24]
  int v125; // [esp+0x2E8] [ebp-0x20]
  int v126; // [esp+0x2EC] [ebp-0x1C]
  int v127; // [esp+0x2F0] [ebp-0x18]
  int v128; // [esp+0x2F4] [ebp-0x14]
  int v129; // [esp+0x2FC] [ebp-0xC]
  float m_fAnimParam; // [esp+0x300] [ebp-0x8]
  int v131; // [esp+0x304] [ebp-0x4]

  p_m_pRoleParam3 = (char **)&_this->m_pRoleParam3;
  _this->m_nCachedA = 78;
  _this->m_pRoleParam3 = (char *)182;
  *(_DWORD *)&_this->m_nCachedB = _this->m_nRoleState0 + 182;
  _this->m_nTransform = _this->m_nCachedA + *(_DWORD *)&_this->m_bUIFlagA;
  (((UIListBox *)_this))->UIListBox::SetSelTexture(-1, (int)_this->m_pRoleParam3, _this->m_nCachedA, *(_DWORD *)&_this->m_nCachedB, _this->m_nTransform);
  (*(void ( **)(int *, char *, char **, Actor *))(_this->m_nHandleEvent + 16))(
    &_this->m_nHandleEvent,
    &byte_A01B00,
    p_m_pRoleParam3,
    _this);
  _this[9]._overlap_RoleSystem_m_partyActor_m_nState = nPanelId;
  v4 = (char *)*p_m_pRoleParam3;
  pRect.left = -60910;
  m_nCachedA = _this->m_nCachedA;
  m_pParticleData = (void ( **)(void **, char *, _DWORD *, Actor *))_this->m_pParticleData;
  v121 = (char *)v4;
  v122 = m_nCachedA;
  v123 = (char *)(v4 + 68);
  v124 = m_nCachedA + 32;
  ((void ( **)(void **, char *, char **, Actor *))m_pParticleData)[4](
    &_this->m_pParticleData,
    &byte_A01B00,
    &v121,
    _this);
  LOBYTE(v7) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (((UIPushButton *)&_this->m_pParticleData))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagT.tga", v7);
  v8 = (char *)v121;
  *(_DWORD *)&_this[2].m_bUIFlagA = v124;
  _this[2].m_nRoleState0 = (int)(v8 - 10);
  LODWORD(_this[2].m_fAnimParam) = (unsigned long)(v8 + 80);
  v9 = *(_DWORD *)&_this[2].m_bUIFlagA + 26;
  *(_DWORD *)&_this[2].m_szText = v9;
  v118 = *(_DWORD *)&_this[2].m_bUIFlagA + 1;
  v10 = *(&_this->m_nUpdateMode + 8);
  v117 = _this[2].m_nRoleState0 + 1;
  v119 = v117 + 86;
  v120 = v9 - 1;
  (*(void ( **)(int *, char *, int *, Actor *))(v10 + 16))(
    &_this->m_nUpdateMode + 8,
    &byte_A01B00,
    &v117,
    _this);
  (((UIPushButton *)(&_this->m_nUpdateMode + 8)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", 0);
  LOBYTE(v11) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(char *, char *, int *, Actor *, char *, _DWORD, int))(*((_DWORD *)&_this[2].m_szText
                                                                                           + 1)
                                                                                         + 28))(
    &_this[2].m_szText + 4,
    &byte_A01B01,
    &_this[2].m_nRoleState0,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v11);
  (((PalScript *)(&_this[2].m_szText + 4)))->PalScript::OpenScript("SubGame\\HockShop\\Control\\unrawbtn.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  AllocObject(&_this[2].m_szText + 4);
  (((CScreenMode *)(&_this[2].m_szText + 4)))->CScreenMode::SetTooltipText((int)dword_DCD23C);
  v12 = *(_DWORD *)&_this[2].m_szText;
  *(_DWORD *)&_this[2].m_bUIFlagA = v12;
  v13 = v12 + 26;
  *(_DWORD *)&_this[2].m_szText = v12 + 26;
  v14 = _this[2].m_nRoleState0 + 1;
  v118 = *(_DWORD *)&_this[2].m_bUIFlagA + 1;
  v117 = v14;
  v119 = v14 + 86;
  m_nPathBuffer = _this[1].m_nPathBuffer;
  v120 = v13 - 1;
  v16 = (*(int ( **)(int *, char *, int *, Actor *))(m_nPathBuffer + 16))(
          &_this[1].m_nPathBuffer,
          &byte_A01B00,
          &v117,
          _this);
  LOBYTE(v16) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (((UIPushButton *)&_this[1].m_nPathBuffer))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", v16);
  LOBYTE(v17) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(RoleAtt **, char *, int *, Actor *, char *, _DWORD, int))((char *)&_this[2].m_pEquipAtt1[0]->Remark.skillCount
                                                                                             + 22))(
    _this[2].m_pEquipAtt1,
    &byte_A01B02,
    &_this[2].m_nRoleState0,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v17);
  (((PalScript *)_this[2].m_pEquipAtt1))->PalScript::OpenScript("SubGame\\HockShop\\Control\\unrawbtn.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  AllocObject(_this[2].m_pEquipAtt1);
  (((CScreenMode *)_this[2].m_pEquipAtt1))->CScreenMode::SetTooltipText((int)dword_DCD33C);
  v18 = *(_DWORD *)&_this[2].m_szText;
  *(_DWORD *)&_this[2].m_bUIFlagA = v18;
  v18 += 26;
  *(_DWORD *)&_this[2].m_szText = v18;
  m_nRoleState0 = _this[2].m_nRoleState0;
  v129 = *(_DWORD *)&_this[2].m_bUIFlagA;
  m_fAnimParam = _this[2].m_fAnimParam;
  v20 = v18 + 26;
  v21 = *(_DWORD *)&_this[2].m_szText;
  *(_DWORD *)&_this[2].m_bUIFlagA = v18;
  *(_DWORD *)&_this[2].m_szText = v18 + 26;
  v22 = *(_DWORD *)&_this[2].m_bUIFlagA + 1;
  v131 = v21;
  v118 = v22;
  v23 = _this[1].m_pEquipAtt1[1];
  v117 = _this[2].m_nRoleState0 + 1;
  v119 = v117 + 86;
  v120 = v20 - 1;
  (*(void ( **)(RoleAtt **, char *, int *, Actor *))((char *)&v23->Remark.skillCount + 10))(
    &_this[1].m_pEquipAtt1[1],
    &byte_A01B00,
    &v117,
    _this);
  LOBYTE(v24) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (((UIPushButton *)&_this[1].m_pEquipAtt1[1]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", v24);
  LOBYTE(v25) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(float *, char *, int *, Actor *, char *, _DWORD, int))(LODWORD(_this[3].m_fMatrixA)
                                                                                          + 28))(
    &_this[3].m_fMatrixA,
    &byte_A01B04,
    &_this[2].m_nRoleState0,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v25);
  (((PalScript *)&_this[3].m_fMatrixA))->PalScript::OpenScript("SubGame\\HockShop\\Control\\unrawbtn.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  AllocObject(&_this[3].m_fMatrixA);
  (((CScreenMode *)&_this[3].m_fMatrixA))->CScreenMode::SetTooltipText((int)dword_DCD53C);
  v26 = *(_DWORD *)&_this[2].m_szText;
  *(_DWORD *)&_this[2].m_bUIFlagA = v26;
  v27 = v26 + 26;
  *(_DWORD *)&_this[2].m_szText = v26 + 26;
  v28 = _this[2].m_nRoleState0 + 1;
  v118 = *(_DWORD *)&_this[2].m_bUIFlagA + 1;
  v117 = v28;
  v119 = v28 + 86;
  v29 = *(_DWORD *)&_this[1].m_curact[19];
  v120 = v27 - 1;
  v30 = (*(int ( **)(char *, char *, int *, Actor *))(v29 + 16))(
          &_this[1].m_curact[19],
          &byte_A01B00,
          &v117,
          _this);
  LOBYTE(v30) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (((UIPushButton *)&_this[1].m_curact[19]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", v30);
  LOBYTE(v31) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(unsigned int *, char *, int *, Actor *, char *, _DWORD, int))(_this[3].m_dwMatMsg[6] + 28))(
    &_this[3].m_dwMatMsg[6],
    byte_A01B05,
    &_this[2].m_nRoleState0,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v31);
  (((PalScript *)&_this[3].m_dwMatMsg[6]))->PalScript::OpenScript("SubGame\\HockShop\\Control\\unrawbtn.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  AllocObject(&_this[3].m_dwMatMsg[6]);
  (((CScreenMode *)&_this[3].m_dwMatMsg[6]))->CScreenMode::SetTooltipText((int)dword_DCD63C);
  v32 = *(_DWORD *)&_this[2].m_szText;
  *(_DWORD *)&_this[2].m_bUIFlagA = v32;
  v33 = v32 + 26;
  *(_DWORD *)&_this[2].m_szText = v32 + 26;
  v34 = _this[2].m_nRoleState0 + 1;
  v118 = *(_DWORD *)&_this[2].m_bUIFlagA + 1;
  v117 = v34;
  v119 = v34 + 86;
  v35 = *(&_this[1].m_nAnimCounter + 8);
  v120 = v33 - 1;
  v36 = (*(int ( **)(int *, char *, int *, Actor *))(v35 + 16))(
          &_this[1].m_nAnimCounter + 8,
          &byte_A01B00,
          &v117,
          _this);
  LOBYTE(v36) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (((UIPushButton *)(&_this[1].m_nAnimCounter + 8)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", v36);
  LOBYTE(v37) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(int *, char *, int *, Actor *, char *, _DWORD, int))(_this[4].m_nRoleState0 + 28))(
    &_this[4].m_nRoleState0,
    &byte_A01B08,
    &_this[2].m_nRoleState0,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    0,
    v37);
  (((PalScript *)&_this[4].m_nRoleState0))->PalScript::OpenScript("SubGame\\HockShop\\Control\\unrawbtn.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  AllocObject(&_this[4].m_nRoleState0);
  (((CScreenMode *)&_this[4].m_nRoleState0))->CScreenMode::SetTooltipText((int)dword_DCD93C);
  v38 = *((_DWORD *)&_this->m_fSpeed + 1);
  v122 = *(_DWORD *)&_this[2].m_szText;
  v124 = v122 + 11;
  (*(void ( **)(float *, char *, char **, Actor *))(v38 + 16))(&_this->m_fSpeed + 1, &byte_A01B00, &v121, _this);
  LOBYTE(v39) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (((UIPushButton *)(&_this->m_fSpeed + 1)))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagB.tga", v39);
  v40 = v129;
  v41 = m_fAnimParam;
  _this[2].m_nRoleState0 = m_nRoleState0;
  *(_DWORD *)&_this[2].m_bUIFlagA = v40;
  v42 = v131;
  _this[2].m_fAnimParam = v41;
  *(_DWORD *)&_this[2].m_szText = v42;
  v43 = *(_DWORD *)&_this[2].m_szText;
  v118 = *(_DWORD *)&_this[2].m_bUIFlagA + 1;
  v44 = *(_DWORD *)&_this[1].m_szTexture[20];
  v117 = _this[2].m_nRoleState0 + 1;
  v119 = v117 + 86;
  v120 = v43 - 1;
  (*(void ( **)(char *, char *, int *, Actor *))(v44 + 16))(
    &_this[1].m_szTexture[20],
    &byte_A01B00,
    &v117,
    _this);
  LOBYTE(v45) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (((UIPushButton *)&_this[1].m_szTexture[20]))->UIPushButton::CreateFromTemplate("UI\\Assistant\\Deal\\FlagM.tga", v45);
  LOBYTE(v46) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(int *, char *, int *, Actor *, char *, int))(*(&_this[2].m_nUpdateMode + 2)
                                                                                           + 28))(
    &_this[2].m_nUpdateMode + 2,
    &byte_A01B03,
    &_this[2].m_nRoleState0,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v46);
  (((UIPushButton *)(&_this[2].m_nUpdateMode + 2)))->UIPushButton::FormatText("SubGame\\HockShop\\Control\\rawbtn1.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((UIPushButton *)(&_this[2].m_nUpdateMode + 2)))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((UIPushButton *)(&_this[2].m_nUpdateMode + 2)))->UIPushButton::SetText();
  (((CCBUI *)(&_this[2].m_nUpdateMode + 2)))->CCBUI::SetRect(&pRect);
  (((CCBUI *)(&_this[2].m_nUpdateMode + 2)))->CCBUI::SetTooltip(szText);
  _this[4].m_pEquipAtt0 = *(RoleAtt **)&_this[2].m_bUIFlagA;
  v47 = LODWORD(_this[2].m_fAnimParam) + 2;
  _this[4].m_nRoleState1 = v47;
  _this[4].m_nAnimFrames = v47 + 90;
  m_pEquipAtt0 = _this[4].m_pEquipAtt0;
  m_pEquipAtt1 = (char *)_this[4].m_pEquipAtt1;
  _this[4].m_nTransitionParam = (int)&m_pEquipAtt0->Remark.skillCount + 20;
  LOBYTE(v49) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(RoleAtt **, char *, int *, Actor *, char *, int))((char *)&_this[4].m_pEquipAtt1[0]->Remark.skillCount
                                                                                     + 22))(
    _this[4].m_pEquipAtt1,
    byte_A01B09,
    &_this[4].m_nRoleState1,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v49);
  (((UIPushButton *)_this[4].m_pEquipAtt1))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)_this[4].m_pEquipAtt1))->CCBUI::SetRect(&pRect);
  (((CCBUI *)_this[4].m_pEquipAtt1))->CCBUI::SetTooltip((const char *)&dword_DCDA3C);
  v50 = _this[4].m_pEquipAtt0;
  *(_DWORD *)&_this[5].m_curact[39] = (_DWORD)v50;
  v51 = _this[4].m_nAnimFrames + 2;
  LODWORD(_this[5].m_fDirX) = (unsigned long)((char *)&v50->Remark.skillCount + 20);
  v52 = (RoleAtt *)(_this[4].m_nTransitionParam + 2);
  *(_DWORD *)&_this[5].m_curact[35] = v51;
  _this[4].m_pEquipAtt0 = v52;
  _this[4].m_nTransitionParam = (int)&v52->Remark.skillCount + 20;
  overlap_RoleSystem_m_partyActor_m_nState = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  v51 += 90;
  v54 = *((_DWORD *)&_this[4].m_bDirFlag + 3);
  _this[5]._overlap_RoleSystem_m_partyActor_m_nState = v51;
  LOBYTE(v51) = *(_BYTE *)(overlap_RoleSystem_m_partyActor_m_nState + 1768);
  v109 = (char *)(&_this[4].m_bDirFlag + 12);
  (*(void ( **)(_BYTE *, char *, int *, Actor *, char *, int))(v54 + 28))(
    &_this[4].m_bDirFlag + 12,
    &byte_A01B10,
    &_this[4].m_nRoleState1,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v51);
  (((UIPushButton *)(&_this[4].m_bDirFlag + 12)))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)(&_this[4].m_bDirFlag + 12)))->CCBUI::SetRect(&pRect);
  (((CCBUI *)(&_this[4].m_bDirFlag + 12)))->CCBUI::SetTooltip((const char *)&dword_DCDB3C);
  v55 = _this[4].m_pEquipAtt0;
  m_nAnimFrames = _this[4].m_nAnimFrames;
  _this[6].m_dwMatMsg[6] = (unsigned int)v55;
  _this[6].m_dwMatMsg[8] = (unsigned int)&v55->Remark.skillCount + 20;
  v57 = (RoleAtt *)(_this[4].m_nTransitionParam + 2);
  m_nAnimFrames += 2;
  _this[4].m_pEquipAtt0 = v57;
  _this[6].m_dwMatMsg[5] = m_nAnimFrames;
  _this[4].m_nTransitionParam = (int)&v57->Remark.skillCount + 20;
  v58 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  m_nAnimFrames += 90;
  v59 = *(&_this[5].m_nModelId + 2);
  _this[6].m_dwMatMsg[7] = m_nAnimFrames;
  LOBYTE(m_nAnimFrames) = *(_BYTE *)(v58 + 1768);
  v110 = (char *)(&_this[5].m_nModelId + 2);
  (*(void ( **)(int *, char *, int *, Actor *, char *, int))(v59 + 28))(
    &_this[5].m_nModelId + 2,
    &byte_A01B11,
    &_this[4].m_nRoleState1,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    m_nAnimFrames);
  (((UIPushButton *)(&_this[5].m_nModelId + 2)))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)(&_this[5].m_nModelId + 2)))->CCBUI::SetRect(&pRect);
  (((CCBUI *)(&_this[5].m_nModelId + 2)))->CCBUI::SetTooltip((const char *)&dword_DCDC3C);
  v60 = _this[4].m_pEquipAtt0;
  v61 = _this[4].m_nAnimFrames;
  *((_DWORD *)&_this[7].m_nAnimFrame + 1) = (unsigned long)v60;
  _this[7].m_pParticleData = (char *)&v60->Remark.skillCount + 20;
  v62 = (RoleAtt *)(_this[4].m_nTransitionParam + 2);
  v61 += 2;
  _this[4].m_pEquipAtt0 = v62;
  *(_DWORD *)&_this[7].m_nAnimFrame = v61;
  _this[4].m_nTransitionParam = (int)&v62->Remark.skillCount + 20;
  v63 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  v61 += 90;
  z = _this[5].m_vecPos.z;
  *((_DWORD *)&_this[7].m_nAnimFrame + 2) = v61;
  LOBYTE(v61) = *(_BYTE *)(v63 + 1768);
  p_z = (char *)&_this[5].m_vecPos.z;
  (*(void ( **)(float *, char *, int *, Actor *, char *, int))(LODWORD(z) + 28))(
    &_this[5].m_vecPos.z,
    &byte_A01B12,
    &_this[4].m_nRoleState1,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v61);
  (((UIPushButton *)&_this[5].m_vecPos.z))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)&_this[5].m_vecPos.z))->CCBUI::SetRect(&pRect);
  (((CCBUI *)&_this[5].m_vecPos.z))->CCBUI::SetTooltip((const char *)&dword_DCDD3C);
  v65 = _this[4].m_pEquipAtt0;
  v66 = (RoleAtt *)_this[4].m_nAnimFrames;
  _this[8].m_nTransitionParam = (int)v65;
  v66 = (RoleAtt *)((char *)v66 + 2);
  _this[8].m_nAnimFrames = (int)v66;
  _this[8].m_pEquipAtt1[1] = (RoleAtt *)((char *)&v65->Remark.skillCount + 20);
  v67 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  v66 = (RoleAtt *)((char *)v66 + 90);
  m_fDirY = _this[5].m_fDirY;
  _this[8].m_pEquipAtt1[0] = v66;
  LOBYTE(v66) = *(_BYTE *)(v67 + 1768);
  p_m_fDirY = (char *)&_this[5].m_fDirY;
  (*(void ( **)(float *, char *, char *, Actor *, char *, RoleAtt *))(LODWORD(m_fDirY) + 28))(
    &_this[5].m_fDirY,
    &byte_A01B13,
    &_this[5].m_curact[35],
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v66);
  (((UIPushButton *)&_this[5].m_fDirY))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)&_this[5].m_fDirY))->CCBUI::SetRect(&pRect);
  (((CCBUI *)&_this[5].m_fDirY))->CCBUI::SetTooltip((const char *)&dword_DCDE3C);
  m_fRoleParam3 = _this[6].m_fRoleParam3;
  v70 = LODWORD(_this[5].m_fDirX) + 2;
  *(_DWORD *)&_this[5].m_curact[39] = v70;
  LODWORD(_this[5].m_fDirX) = v70 + 26;
  LOBYTE(v71) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(float *, char *, char *, Actor *, char *, int))(LODWORD(m_fRoleParam3) + 28))(
    &_this[6].m_fRoleParam3,
    &byte_A01B14,
    &_this[5].m_curact[35],
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v71);
  (((UIPushButton *)&_this[6].m_fRoleParam3))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)&_this[6].m_fRoleParam3))->CCBUI::SetRect(&pRect);
  (((CCBUI *)&_this[6].m_fRoleParam3))->CCBUI::SetTooltip((const char *)&dword_DCDF3C);
  LODWORD(_this[6].m_vecBonePos.z) = 1;
  LOBYTE(_this[6].m_nAnimParam1) = 1;
  y = _this[6].m_vecLocalPos.y;
  v73 = LODWORD(_this[5].m_fDirX) + 2;
  *(_DWORD *)&_this[5].m_curact[39] = v73;
  LODWORD(_this[5].m_fDirX) = v73 + 26;
  v74 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  p_y = (char *)&_this[6].m_vecLocalPos.y;
  LOBYTE(v75) = *(_BYTE *)(v74 + 1768);
  (*(void ( **)(float *, char *, char *, Actor *, char *, int))(LODWORD(y) + 28))(
    &_this[6].m_vecLocalPos.y,
    &byte_A01B15,
    &_this[5].m_curact[35],
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v75);
  (((UIPushButton *)&_this[6].m_vecLocalPos.y))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)&_this[6].m_vecLocalPos.y))->CCBUI::SetRect(&pRect);
  (((CCBUI *)&_this[6].m_vecLocalPos.y))->CCBUI::SetTooltip((const char *)&dword_DCE03C);
  v76 = _this[6].m_dwMatMsg[9];
  LOBYTE(v77) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  v114 = (char *)&_this[6].m_dwMatMsg[9];
  (*(void ( **)(unsigned int *, char *, unsigned int *, Actor *, char *, int))(v76 + 28))(
    &_this[6].m_dwMatMsg[9],
    &byte_A01B16,
    &_this[6].m_dwMatMsg[5],
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v77);
  (((UIPushButton *)&_this[6].m_dwMatMsg[9]))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)&_this[6].m_dwMatMsg[9]))->CCBUI::SetRect(&pRect);
  (((CCBUI *)&_this[6].m_dwMatMsg[9]))->CCBUI::SetTooltip((const char *)&dword_DCE13C);
  m_actarray_begin = _this[7].m_actarray_begin;
  v79 = _this[6].m_dwMatMsg[8] + 2;
  _this[6].m_dwMatMsg[6] = v79;
  _this[6].m_dwMatMsg[8] = v79 + 26;
  LOBYTE(v80) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  ((void ( *)(Actor **, char *, unsigned int *, Actor *, char *, int))LODWORD(m_actarray_begin->m_fMoveSpeed))(
    &_this[7].m_actarray_begin,
    &byte_A01B17,
    &_this[6].m_dwMatMsg[5],
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v80);
  (((UIPushButton *)&_this[7].m_actarray_begin))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)&_this[7].m_actarray_begin))->CCBUI::SetRect(&pRect);
  (((CCBUI *)&_this[7].m_actarray_begin))->CCBUI::SetTooltip((const char *)&dword_DCE23C);
  _this[7].m_nTransform = 1;
  LOBYTE(_this[7].m_pRoleParam3) = 1;
  m_fMatrixParamC = _this[7].m_fMatrixParamC;
  v82 = _this[6].m_dwMatMsg[8] + 2;
  _this[6].m_dwMatMsg[6] = v82;
  _this[6].m_dwMatMsg[8] = v82 + 26;
  v83 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  p_m_fMatrixParamC = (char *)&_this[7].m_fMatrixParamC;
  LOBYTE(v84) = *(_BYTE *)(v83 + 1768);
  (*(void ( **)(float *, char *, unsigned int *, Actor *, char *, int))(LODWORD(m_fMatrixParamC) + 28))(
    &_this[7].m_fMatrixParamC,
    &byte_A01B18,
    &_this[6].m_dwMatMsg[5],
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v84);
  (((UIPushButton *)&_this[7].m_fMatrixParamC))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)&_this[7].m_fMatrixParamC))->CCBUI::SetRect(&pRect);
  (((CCBUI *)&_this[7].m_fMatrixParamC))->CCBUI::SetTooltip((const char *)&dword_DCE33C);
  v85 = *((_DWORD *)&_this[7].m_pParticleData + 1);
  LOBYTE(v86) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  v116 = (char *)(&_this[7].m_pParticleData + 1);
  (*(void ( **)(void **, char *, signed __int16 *, Actor *, char *, int))(v85 + 28))(
    &_this[7].m_pParticleData + 1,
    byte_A01B19,
    &_this[7].m_nAnimFrame,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v86);
  (((UIPushButton *)(&_this[7].m_pParticleData + 1)))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)(&_this[7].m_pParticleData + 1)))->CCBUI::SetRect(&pRect);
  (((CCBUI *)(&_this[7].m_pParticleData + 1)))->CCBUI::SetTooltip((const char *)&dword_DCE13C);
  v87 = *(&_this[7].m_nAnimCounter + 10);
  v88 = (char *)_this[7].m_pParticleData + 2;
  *((_DWORD *)&_this[7].m_nAnimFrame + 1) = (unsigned long)v88;
  _this[7].m_pParticleData = v88 + 26;
  LOBYTE(v89) = *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768);
  (*(void ( **)(int *, char *, signed __int16 *, Actor *, char *, int))(v87 + 28))(
    &_this[7].m_nAnimCounter + 10,
    &byte_A01B20,
    &_this[7].m_nAnimFrame,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v89);
  (((UIPushButton *)(&_this[7].m_nAnimCounter + 10)))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)(&_this[7].m_nAnimCounter + 10)))->CCBUI::SetRect(&pRect);
  (((CCBUI *)(&_this[7].m_nAnimCounter + 10)))->CCBUI::SetTooltip((const char *)&dword_DCE23C);
  *(_DWORD *)&_this[8].m_name[4] = 1;
  LOBYTE(_this[8].m_actarray_capacity_end) = 1;
  m_nInterpState = _this[8].m_nInterpState;
  v91 = (char *)_this[7].m_pParticleData + 2;
  *((_DWORD *)&_this[7].m_nAnimFrame + 1) = (unsigned long)v91;
  _this[7].m_pParticleData = v91 + 26;
  v92 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  pRect.right = (LONG)&_this[8].m_nInterpState;
  LOBYTE(v92) = *(_BYTE *)(v92 + 1768);
  (*(void ( **)(char *, signed __int16 *, Actor *, char *, int))(m_nInterpState + 28))(
    &byte_A01B21,
    &_this[7].m_nAnimFrame,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v92);
  (((UIPushButton *)pRect.right))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)pRect.right))->CCBUI::SetRect(&pRect);
  (((CCBUI *)pRect.right))->CCBUI::SetTooltip((const char *)&dword_DCE33C);
  v93 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  v94 = _this[8].m_pEquipAtt1[2];
  LOBYTE(v93) = *(_BYTE *)(v93 + 1768);
  pRect.bottom = (LONG)&_this[8].m_pEquipAtt1[2];
  (*(void ( **)(char *, int *, Actor *, char *, int))((char *)&v94->Remark.skillCount + 22))(
    &byte_A01B22,
    &_this[8].m_nAnimFrames,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v93);
  (((UIPushButton *)pRect.bottom))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)pRect.bottom))->CCBUI::SetRect(&pRect);
  (((CCBUI *)pRect.bottom))->CCBUI::SetTooltip((const char *)&dword_DCE43C);
  v95 = *((_DWORD *)&_this[8].m_bDirFlag + 5);
  v96 = (char *)&_this[8].m_pEquipAtt1[1]->id + 2;
  _this[8].m_nTransitionParam = (int)v96;
  _this[8].m_pEquipAtt1[1] = (RoleAtt *)(v96 + 26);
  v97 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  v105 = (UIPushButton *)(&_this[8].m_bDirFlag + 20);
  LOBYTE(v97) = *(_BYTE *)(v97 + 1768);
  (*(void ( **)(char *, int *, Actor *, char *, int))(v95 + 28))(
    &byte_A01B23,
    &_this[8].m_nAnimFrames,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v97);
  (((UIPushButton *)v105))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)v105))->CCBUI::SetRect(&pRect);
  (((CCBUI *)v105))->CCBUI::SetTooltip((const char *)&dword_DCE53C);
  v98 = (char *)&_this[8].m_pEquipAtt1[1]->id + 2;
  p_m_nAnimParam1 = (UIPushButton *)&_this[9].m_nAnimParam1;
  _this[8].m_nTransitionParam = (int)v98;
  _this[8].m_pEquipAtt1[1] = (RoleAtt *)(v98 + 26);
  v99 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  LOBYTE(v99) = *(_BYTE *)(v99 + 1768);
  (*(void ( **)(char *, int *, Actor *, char *, int))(_this[9].m_nAnimParam1 + 28))(
    &byte_A01B24,
    &_this[8].m_nAnimFrames,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v99);
  (((UIPushButton *)p_m_nAnimParam1))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)p_m_nAnimParam1))->CCBUI::SetRect(&pRect);
  (((CCBUI *)p_m_nAnimParam1))->CCBUI::SetTooltip((const char *)&dword_DCE63C);
  v100 = _this[9].m_vecRot.y;
  v101 = (char *)&_this[8].m_pEquipAtt1[1]->id + 2;
  _this[8].m_nTransitionParam = (int)v101;
  _this[8].m_pEquipAtt1[1] = (RoleAtt *)(v101 + 26);
  v102 = _this[9]._overlap_RoleSystem_m_partyActor_m_nState;
  pRect.top = (LONG)&_this[9].m_vecRot.y;
  LOBYTE(v102) = *(_BYTE *)(v102 + 1768);
  (*(void ( **)(char *, int *, Actor *, char *, int))(LODWORD(v100) + 28))(
    byte_A01B25,
    &_this[8].m_nAnimFrames,
    _this,
    "SubGame\\HockShop\\Control\\rawbtn",
    v102);
  (((UIPushButton *)pRect.top))->UIPushButton::LoadTexture("SubGame\\HockShop\\Control\\rawbtn2.tga", *(_BYTE *)(_this[9]._overlap_RoleSystem_m_partyActor_m_nState + 1768));
  (((CCBUI *)pRect.top))->CCBUI::SetRect(&pRect);
  (((CCBUI *)pRect.top))->CCBUI::SetTooltip((const char *)&dword_DCE73C);
  top = pRect.top;
  *(_DWORD *)(pRect.top + 80) = 1;
  *(_BYTE *)(top + 68) = 1;
  v126 = 200;
  v125 = 300;
  v127 = 500;
  v128 = 300;
  Create__ovl_1((ARC_PlayerAtt *)&_this[816].m_fActionSpeed);
  (((UIItem *)&_this[816].m_fActionSpeed))->UIItem::SetData(31);
  v126 = 200;
  v125 = 246;
  v107 = (UIItem *)(&_this[817].m_nAnimCounter + 2);
  Create__ovl_1((ARC_PlayerAtt *)(&_this[817].m_nAnimCounter + 2));
  (((UIItem *)v107))->UIItem::SetData(31);
  (**(void ( ***)(char *, _DWORD))m_pEquipAtt1)((char *)(m_pEquipAtt1), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))v109)((char *)(v109), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))v110)((char *)(v110), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))p_z)((char *)(p_z), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))p_m_fDirY)((char *)(p_m_fDirY), (_DWORD)(0));
  (*(void ( **)(float *, _DWORD))LODWORD(_this[6].m_fRoleParam3))(&_this[6].m_fRoleParam3, 0);
  (**(void ( ***)(char *, _DWORD))p_y)((char *)(p_y), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))v114)((char *)(v114), (_DWORD)(0));
  ((void ( *)(Actor **, _DWORD))_this[7].m_actarray_begin->m_actarray_type)(&_this[7].m_actarray_begin, 0);
  (**(void ( ***)(char *, _DWORD))p_m_fMatrixParamC)((char *)(p_m_fMatrixParamC), (_DWORD)(0));
  (**(void ( ***)(char *, _DWORD))v116)((char *)(v116), (_DWORD)(0));
  (**((void ( ***)(int *, _DWORD))&_this[7].m_nAnimCounter + 10))((int *)(&_this[7].m_nAnimCounter + 10), (_DWORD)(0));
  (**(void ( ***)(LONG, _DWORD))pRect.right)((LONG)(pRect.right), (_DWORD)(0));
  (**(void ( ***)(LONG, _DWORD))pRect.bottom)((LONG)(pRect.bottom), (_DWORD)(0));
  (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v105))((UIPushButton *)(v105), (_DWORD)(0));
  (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)p_m_nAnimParam1))((UIPushButton *)(p_m_nAnimParam1), (_DWORD)(0));
  (**(void ( ***)(LONG, _DWORD))pRect.top)((LONG)(pRect.top), (_DWORD)(0));
}

// 0x00521B00
int CCBStageRole_LoadSaveData(int nVal)
{
  int v1; // ecx
  int result; // eax
  int v4; // ebp
  const void *v5; // esi
  bool v6; // cc
  bool v7; // zf
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  char *v14; // [esp+0x10] [ebp-0x18]
  int v15; // [esp+0x14] [ebp-0x14]
  _DWORD *v16; // [esp+0x18] [ebp-0x10]
  _DWORD *v17; // [esp+0x1C] [ebp-0xC]
  int v18; // [esp+0x20] [ebp-0x8]
  int v19; // [esp+0x24] [ebp-0x4]
  char *nVala; // [esp+0x2C] [ebp+0x4]

  result = v1;
  v4 = nVal + 232;
  *(_DWORD *)(v1 + 328032) = *(_DWORD *)(nVal + 161848);
  *(_DWORD *)(v1 + 328036) = *(_DWORD *)(nVal + 161852);
  *(_DWORD *)(v1 + 328040) = *(_DWORD *)(nVal + 161856);
  *(_DWORD *)(v1 + 328044) = *(_DWORD *)(nVal + 161860);
  *(_DWORD *)(v1 + 328028) = *(_DWORD *)(nVal + 4);
  v17 = (_DWORD *)(v1 + 8028);
  v16 = (_DWORD *)(nVal + 161832);
  v18 = nVal + 232;
  v14 = (char *)(v1 + 8052);
  v19 = 4;
  do
  {
    v15 = 0;
    if ( *(int *)(nVal + 24) > 0 )
    {
      nVala = (char *)v14;
      do
      {
        v5 = (const void *)v4;
        v4 += 808;
        qmemcpy(nVala, v5, 0x328u);
        v6 = ++v15 < *(_DWORD *)(nVal + 24);
        nVala += 808;
      }
      while ( v6 );
    }
    *v17 = *v16++;
    v4 = v18 + 40400;
    v7 = v19 == 1;
    ++v17;
    v14 += 79992;
    v18 += 40400;
    --v19;
  }
  while ( !v7 );
  v8 = *(_DWORD *)(v1 + 328032);
  if ( !v8 )
  {
    *(_DWORD *)(v1 + 4816) = 1;
    *(_BYTE *)(v1 + 4804) = 1;
    *(_DWORD *)(v1 + 5064) = 0;
    *(_BYTE *)(v1 + 5052) = 0;
    goto LABEL_12;
  }
  v9 = v8 - 1;
  if ( !v9 )
  {
    *(_DWORD *)(v1 + 4816) = 0;
    *(_BYTE *)(v1 + 4804) = 0;
    *(_DWORD *)(v1 + 5064) = 1;
    *(_BYTE *)(v1 + 5052) = 1;
LABEL_12:
    *(_DWORD *)(v1 + 5312) = 0;
    *(_BYTE *)(v1 + 5300) = 0;
    goto LABEL_13;
  }
  if ( v9 == 1 )
  {
    *(_DWORD *)(v1 + 4816) = 0;
    *(_BYTE *)(v1 + 4804) = 0;
    *(_DWORD *)(v1 + 5064) = 0;
    *(_BYTE *)(v1 + 5052) = 0;
    *(_DWORD *)(v1 + 5312) = 1;
    *(_BYTE *)(v1 + 5300) = 1;
  }
LABEL_13:
  v10 = *(_DWORD *)(v1 + 328036);
  if ( !v10 )
  {
    *(_DWORD *)(v1 + 5576) = 1;
    *(_BYTE *)(v1 + 5564) = 1;
    *(_DWORD *)(v1 + 5824) = 0;
    *(_BYTE *)(v1 + 5812) = 0;
    goto LABEL_19;
  }
  v11 = v10 - 1;
  if ( !v11 )
  {
    *(_DWORD *)(v1 + 5576) = 0;
    *(_BYTE *)(v1 + 5564) = 0;
    *(_DWORD *)(v1 + 5824) = 1;
    *(_BYTE *)(v1 + 5812) = 1;
LABEL_19:
    *(_DWORD *)(v1 + 6072) = 0;
    *(_BYTE *)(v1 + 6060) = 0;
    goto LABEL_20;
  }
  if ( v11 == 1 )
  {
    *(_DWORD *)(v1 + 5576) = 0;
    *(_BYTE *)(v1 + 5564) = 0;
    *(_DWORD *)(v1 + 5824) = 0;
    *(_BYTE *)(v1 + 5812) = 0;
    *(_DWORD *)(v1 + 6072) = 1;
    *(_BYTE *)(v1 + 6060) = 1;
  }
LABEL_20:
  v12 = *(_DWORD *)(v1 + 328040);
  if ( !v12 )
  {
    *(_DWORD *)(v1 + 6336) = 1;
    *(_BYTE *)(v1 + 6324) = 1;
    *(_DWORD *)(v1 + 6584) = 0;
    *(_BYTE *)(v1 + 6572) = 0;
    goto LABEL_26;
  }
  v13 = v12 - 1;
  if ( !v13 )
  {
    *(_DWORD *)(v1 + 6336) = 0;
    *(_BYTE *)(v1 + 6324) = 0;
    *(_DWORD *)(v1 + 6584) = 1;
    *(_BYTE *)(v1 + 6572) = 1;
LABEL_26:
    *(_DWORD *)(v1 + 6832) = 0;
    *(_BYTE *)(v1 + 6820) = 0;
    goto LABEL_27;
  }
  if ( v13 == 1 )
  {
    *(_DWORD *)(v1 + 6336) = 0;
    *(_BYTE *)(v1 + 6324) = 0;
    *(_DWORD *)(v1 + 6584) = 0;
    *(_BYTE *)(v1 + 6572) = 0;
    *(_DWORD *)(v1 + 6832) = 1;
    *(_BYTE *)(v1 + 6820) = 1;
  }
LABEL_27:
  switch ( *(_DWORD *)(v1 + 328044) )
  {
    case 0:
      *(_DWORD *)(v1 + 7096) = 0;
      *(_BYTE *)(v1 + 7084) = 0;
      *(_DWORD *)(v1 + 7344) = 0;
      *(_BYTE *)(v1 + 7332) = 0;
      *(_DWORD *)(v1 + 7592) = 0;
      *(_BYTE *)(v1 + 7580) = 0;
      *(_DWORD *)(v1 + 7840) = 1;
      *(_BYTE *)(v1 + 7828) = 1;
      break;
    case 1:
      *(_DWORD *)(v1 + 7096) = 1;
      *(_BYTE *)(v1 + 7084) = 1;
      *(_DWORD *)(v1 + 7344) = 0;
      *(_BYTE *)(v1 + 7332) = 0;
      goto LABEL_30;
    case 2:
      *(_DWORD *)(v1 + 7096) = 0;
      *(_BYTE *)(v1 + 7084) = 0;
      *(_DWORD *)(v1 + 7344) = 1;
      *(_BYTE *)(v1 + 7332) = 1;
LABEL_30:
      *(_DWORD *)(v1 + 7592) = 0;
      *(_BYTE *)(v1 + 7580) = 0;
      *(_DWORD *)(v1 + 7840) = 0;
      *(_BYTE *)(v1 + 7828) = 0;
      break;
    case 3:
      *(_DWORD *)(v1 + 7096) = 0;
      *(_BYTE *)(v1 + 7084) = 0;
      *(_DWORD *)(v1 + 7344) = 0;
      *(_BYTE *)(v1 + 7332) = 0;
      *(_DWORD *)(v1 + 7592) = 1;
      *(_BYTE *)(v1 + 7580) = 1;
      *(_DWORD *)(v1 + 7840) = 0;
      *(_BYTE *)(v1 + 7828) = 0;
      break;
    default:
      return result;
  }
  return result;
}

// 0x00521EB0
int CCBStageRole_DispatchUpdate_1eb0(unsigned __int8 nFlag)
{
  int v1; // ecx
  int v2; // edi

  v2 = v1;
  (**(void ( ***)(int, _DWORD))(v1 + 4736))((int)(v1 + 4736), (_DWORD)(nFlag));
  (**(void ( ***)(int, _DWORD))(v2 + 4984))((int)(v2 + 4984), (_DWORD)(nFlag));
  return (**(int ( ***)(int, _DWORD))(v2 + 5232))((int)(v2 + 5232), (_DWORD)(nFlag));
}

// 0x00521EF0
int CCBStageRole_DispatchUpdate_1ef0(unsigned __int8 nFlag)
{
  int v1; // ecx
  int v2; // edi

  v2 = v1;
  (**(void ( ***)(int, _DWORD))(v1 + 5496))((int)(v1 + 5496), (_DWORD)(nFlag));
  (**(void ( ***)(int, _DWORD))(v2 + 5744))((int)(v2 + 5744), (_DWORD)(nFlag));
  return (**(int ( ***)(int, _DWORD))(v2 + 5992))((int)(v2 + 5992), (_DWORD)(nFlag));
}

// 0x00521F70
int CCBStageRole_DispatchUpdate_1f70(unsigned __int8 nFlag)
{
  int v1; // ecx
  int v2; // edi

  v2 = v1;
  (**(void ( ***)(int, _DWORD))(v1 + 7016))((int)(v1 + 7016), (_DWORD)(nFlag));
  (**(void ( ***)(int, _DWORD))(v2 + 7264))((int)(v2 + 7264), (_DWORD)(nFlag));
  (**(void ( ***)(int, _DWORD))(v2 + 7512))((int)(v2 + 7512), (_DWORD)(nFlag));
  return (**(int ( ***)(int, _DWORD))(v2 + 7760))((int)(v2 + 7760), (_DWORD)(nFlag));
}

// 0x00523600
int CUtil_CalulateParabola(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = *(_DWORD *)(v1 + 1756);
  if ( result )
    return crt_sub_00540D20();
  return result;
}

// 0x00523820
int CUtil_Update(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // esi
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v26; // edi
  CScreenMode *v27; // eax
  CScreenMode *v28; // eax
  int result; // eax

  v2 = (_DWORD *)v1;
  v1[438] = nVal;
  switch ( nVal )
  {
    case 0:
      if ( v1 )
        (*(void ( **)(_DWORD *, int, int, _DWORD))(*v1 + 24))(v1, 1000, 1, 0);
      v3 = (unsigned long)v2[434];
      if ( v3 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v3 + 24))(v3, 1000, 0, 0);
      v4 = (unsigned long)v2[435];
      if ( v4 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(v4, 1000, 0, 0);
      v5 = (unsigned long)v2[436];
      if ( v5 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v5 + 24))(v5, 1000, 0, 0);
      v6 = (unsigned long)v2[437];
      if ( v6 )
        goto LABEL_39;
      break;
    case 1:
      if ( v1 )
        (*(void ( **)(_DWORD *, int, _DWORD, _DWORD))(*v1 + 24))(v1, 1000, 0, 0);
      v7 = (unsigned long)v2[434];
      if ( v7 )
        (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v7 + 24))(v7, 1000, 1, 0);
      v8 = (unsigned long)v2[435];
      if ( v8 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1000, 0, 0);
      v9 = (unsigned long)v2[436];
      if ( v9 )
        (*(void ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(1000, 0, 0);
      goto LABEL_38;
    case 2:
      if ( v1 )
        (*(void ( **)(_DWORD *, int, _DWORD, _DWORD))(*v1 + 24))(v1, 1000, 0, 0);
      v10 = (unsigned long)v2[434];
      if ( v10 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1000, 0, 0);
      v11 = (unsigned long)v2[435];
      if ( v11 )
        (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 1, 0);
      v12 = (unsigned long)v2[436];
      if ( v12 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 0, 0);
      v6 = (unsigned long)v2[437];
      if ( v6 )
        goto LABEL_39;
      break;
    case 3:
      if ( v1 )
        (*(void ( **)(_DWORD *, int, _DWORD, _DWORD))(*v1 + 24))(v1, 1000, 0, 0);
      v13 = (unsigned long)v2[434];
      if ( v13 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v13 + 24))(v13, 1000, 0, 0);
      v14 = (unsigned long)v2[435];
      if ( v14 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v14 + 24))(v14, 1000, 0, 0);
      v15 = (unsigned long)v2[436];
      if ( v15 )
        (*(void ( **)(int, int, _DWORD))(*(_DWORD *)v15 + 24))(1000, 1, 0);
LABEL_38:
      v6 = (unsigned long)v2[437];
      if ( v6 )
LABEL_39:
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v6 + 24))(v6, 1000, 0, 0);
      break;
    case 4:
      if ( v1 )
        (*(void ( **)(_DWORD *, int, _DWORD, _DWORD))(*v1 + 24))(v1, 1000, 0, 0);
      v16 = (unsigned long)v2[434];
      if ( v16 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v16 + 24))(v16, 1000, 0, 0);
      v17 = (unsigned long)v2[435];
      if ( v17 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v17 + 24))(v17, 1000, 0, 0);
      v18 = (unsigned long)v2[436];
      if ( v18 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v18 + 24))(v18, 1000, 0, 0);
      v19 = (unsigned long)v2[437];
      if ( v19 )
        (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v19 + 24))(v19, 1000, 1, 0);
      break;
    case 5:
      if ( v1 )
        (*(void ( **)(_DWORD *, int, _DWORD, _DWORD))(*v1 + 24))(v1, 1000, 0, 0);
      v20 = (unsigned long)v2[434];
      if ( v20 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v20 + 24))(v20, 1000, 0, 0);
      v21 = (unsigned long)v2[435];
      if ( v21 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v21 + 24))(v21, 1000, 0, 0);
      v22 = (unsigned long)v2[436];
      if ( v22 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v22 + 24))(v22, 1000, 0, 0);
      v23 = (unsigned long)v2[437];
      if ( v23 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v23 + 24))(v23, 1000, 0, 0);
      if ( (g_dwGameFlags & 4) != 0 )
      {
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
        v26 = (gbAudioManager *)AudioManager;
        if ( AudioManager )
        {
          (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(1);
          (((gbAudioManager *)v26))->gbAudioManager::StopSoundStream(2);
        }
        if ( CScreenMode::GetInstance()->m_bRenderAlt )
        {
          v27 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v27))->CScreenMode::AudioFadeOut();
        }
        else
        {
          v28 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v28))->CScreenMode::AudioStopAll();
        }
      }
      break;
    default:
      break;
  }
  result = (v2[438] == 5) + 1;
  g_nSceneState = result;
  return result;
}

// 0x00523E70
int GetScriptBufferAddr(_DWORD *_this)
{
  return _this[435] + 345572;
}

// 0x00524230
int UIScene_InitScriptScene(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // ebx
  int v16; // ebp
  int v17; // eax
  float v18; // st7
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // ebx
  int v24; // ebp
  int v25; // eax
  float v26; // st7
  __int64 v27; // rax
  int v28; // ecx
  int v29; // eax
  int v30; // ecx
  __int64 v31; // rax
  int v32; // ecx
  int v33; // eax
  int v34; // ecx
  int v35; // edx
  int v36; // edx
  int v37; // ecx
  int result; // eax
  float fVal; // [esp+0x5C] [ebp-0x88]
  int v40; // [esp+0x74] [ebp-0x70] BYREF
  int v41; // [esp+0x78] [ebp-0x6C]
  int v42; // [esp+0x7C] [ebp-0x68]
  int v43; // [esp+0x80] [ebp-0x64]
  _DWORD v44[2]; // [esp+0x84] [ebp-0x60] BYREF
  int v45; // [esp+0x8C] [ebp-0x58]
  int v46; // [esp+0x90] [ebp-0x54]
  _DWORD v47[2]; // [esp+0x94] [ebp-0x50] BYREF
  int v48; // [esp+0x9C] [ebp-0x48]
  int v49; // [esp+A0h] [ebp-0x44]
  _DWORD v50[2]; // [esp+A4h] [ebp-0x40] BYREF
  int v51; // [esp+ACh] [ebp-0x38]
  int v52; // [esp+B0h] [ebp-0x34]
  _DWORD v53[4]; // [esp+B4h] [ebp-0x30] BYREF
  _DWORD v54[8]; // [esp+C4h] [ebp-0x20] BYREF

  v2 = v1;
  v3 = *(_DWORD *)(v1 + 88);
  v4 = *(_DWORD *)(v1 + 92);
  *(_DWORD *)(v2 + 80) = v3;
  *(_DWORD *)(v2 + 84) = v4;
  *(_DWORD *)(v2 + 76) = 0;
  *(_DWORD *)(v2 + 72) = 0;
  (((UIListBox *)v2))->UIListBox::SetSelTexture(-1, 0, 0, *(_DWORD *)(v2 + 80), *(_DWORD *)(v2 + 84));
  v5 = *(_DWORD *)(v2 + 360);
  *(_DWORD *)(v2 + 5248) = nVal;
  v41 = 84;
  v40 = 112;
  v42 = 655;
  v43 = 318;
  v6 = (*(int ( **)(int, int *, int *, int))(v5 + 16))(v2 + 360, &byte_A00B00, &v40, v2);
  LOBYTE(v6) = *(_BYTE *)(*(_DWORD *)(v2 + 5248) + 1768);
  (((UIPushButton *)(v2 + 360)))->UIPushButton::CreateFromTemplate("SubGame\\HockShop\\Invest\\Invest_Frame.tga", v6);
  v53[1] = v41;
  v53[0] = v40 + 288;
  v53[2] = v40 + 416;
  v53[3] = v41 + 32;
  (*(void ( **)(int, int *, _DWORD *, int))(*(_DWORD *)(v2 + 1120) + 16))(v2 + 1120, &byte_A00B05, (_DWORD *)(v53), v2);
  (((UIScene *)(v2 + 1120)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 1120));
  v47[0] = v40 + 172;
  v47[1] = v41 + 42;
  v48 = v40 + 300;
  v49 = v41 + 74;
  (*(void ( **)(int, int *, _DWORD *, int))(*(_DWORD *)(v2 + 816) + 16))(v2 + 816, &byte_A00B03, (_DWORD *)(v47), v2);
  (((UIScene *)(v2 + 816)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 816));
  v7 = *(_DWORD *)(v2 + 968);
  v47[0] = 558;
  v48 = 686;
  (*(void ( **)(int, int *, _DWORD *, int))(v7 + 16))(v2 + 968, &byte_A00B04, (_DWORD *)(v47), v2);
  (((UIScene *)(v2 + 968)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 968));
  v8 = *(_DWORD *)(v2 + 512);
  v50[1] = v41 + 82;
  v50[0] = v40 + 172;
  v52 = v41 + 114;
  v51 = v40 + 300;
  (*(void ( **)(int, int *, _DWORD *, int))(v8 + 16))(v2 + 512, &byte_A00B02, (_DWORD *)(v50), v2);
  (((UIScene *)(v2 + 512)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 512));
  sprintf((char *const)(v2 + 104), (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)(v2 + 512));
  v9 = *(_DWORD *)(v2 + 664);
  v50[0] = 558;
  v51 = 686;
  (*(void ( **)(int, int *, _DWORD *, int))(v9 + 16))(v2 + 664, &byte_A00B06, (_DWORD *)(v50), v2);
  (((UIScene *)(v2 + 664)))->UIScene::SetShow(0);
  AllocObject((void *)(v2 + 664));
  sprintf((char *const)(v2 + 104), (const char *)&dir[20], (unsigned int)(__int64)*(float *)(v2 + 1504));
  SetEnable((UICaption *)(v2 + 664));
  v54[1] = v41 + 132;
  v54[0] = v40 + 74;
  v54[3] = v41 + 170;
  v10 = *(_DWORD *)(v2 + 5248);
  v11 = v40 + 477;
  v12 = *(_DWORD *)(v2 + 1272);
  v54[2] = v40 + 477;
  LOBYTE(v11) = *(_BYTE *)(v10 + 1768);
  (*(void ( **)(int, int *, _DWORD *, int, char *, int))(v12 + 28))(
    v2 + 1272,
    &byte_A00B01,
    (_DWORD *)(v54),
    v2,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    v11);
  (((UIScene *)(v2 + 1272)))->UIScene::SetTexture("SubGame\\HockShop\\Invest\\DragBar_bk.tga", *(_BYTE *)(*(_DWORD *)(v2 + 5248) + 1768));
  (((UIScene *)(v2 + 1272)))->UIScene::SetParam(0);
  *(_DWORD *)(v2 + 1520) = 1112014848;
  *(_DWORD *)(v2 + 1524) = -1027866624;
  (((UIBigMap *)(v2 + 1272)))->UIBigMap::UpdateWindowPos(26, 28);
  v13 = *(_DWORD *)(v2 + 1536);
  *(_DWORD *)(v2 + 1516) = 32;
  if ( v13 )
  {
    if ( v13 == 1 )
    {
      v14 = *(_DWORD *)(v2 + 1540);
      if ( !v14 )
      {
        v15 = *(_DWORD *)(v2 + 1368);
        v19 = *(_DWORD *)(v2 + 1408);
        v16 = (__int64)((double)(*(_DWORD *)(v2 + 1412) - v15 / 2) + *(float *)(v2 + 1528) + *(float *)(v2 + 1508));
        v20 = *(_DWORD *)(v2 + 1364);
        *(_DWORD *)(v2 + 1396) = v16;
        v18 = (float)(v19 - v20 - 32) + *(float *)(v2 + 1520);
        goto LABEL_7;
      }
      if ( v14 == 1 )
      {
        v15 = *(_DWORD *)(v2 + 1368);
        v16 = (__int64)((double)*(int *)(v2 + 1420) - *(float *)(v2 + 1508) - (double)(v15 / 2) - *(float *)(v2 + 1532));
        v17 = *(_DWORD *)(v2 + 1416);
        *(_DWORD *)(v2 + 1396) = v16;
        v18 = (float)(v17 + 32) - *(float *)(v2 + 1508) - *(float *)(v2 + 1524);
LABEL_7:
        v21 = *(_DWORD *)(v2 + 1364);
        *(_DWORD *)(v2 + 1392) = (__int64)v18;
        *(_DWORD *)(v2 + 1400) = (__int64)v18 + v21;
LABEL_12:
        *(_DWORD *)(v2 + 1404) = v15 + v16;
      }
    }
  }
  else
  {
    v22 = *(_DWORD *)(v2 + 1540);
    if ( !v22 )
    {
      v16 = *(_DWORD *)(v2 + 1368);
      v15 = (__int64)((double)(*(_DWORD *)(v2 + 1412) - v16 - 32) + *(float *)(v2 + 1528));
      v29 = *(_DWORD *)(v2 + 1364);
      v30 = *(_DWORD *)(v2 + 1408);
      *(_DWORD *)(v2 + 1396) = v15;
      v31 = (__int64)((double)(v30 - v29 / 2) + *(float *)(v2 + 1520) + *(float *)(v2 + 1508));
      v32 = *(_DWORD *)(v2 + 1364);
      *(_DWORD *)(v2 + 1392) = v31;
      *(_DWORD *)(v2 + 1400) = v32 + v31;
      goto LABEL_12;
    }
    if ( v22 == 1 )
    {
      v23 = *(_DWORD *)(v2 + 1368);
      v24 = (__int64)((double)(*(_DWORD *)(v2 + 1412) - v23 - 32) + *(float *)(v2 + 1528));
      v25 = *(_DWORD *)(v2 + 1364);
      v26 = (float)*(int *)(v2 + 1416) - *(float *)(v2 + 1508);
      *(_DWORD *)(v2 + 1396) = v24;
      v27 = (__int64)(v26 - (double)(v25 / 2) - *(float *)(v2 + 1524));
      v28 = *(_DWORD *)(v2 + 1364);
      *(_DWORD *)(v2 + 1392) = v27;
      *(_DWORD *)(v2 + 1400) = v28 + v27;
      *(_DWORD *)(v2 + 1404) = v24 + v23;
    }
  }
  fVal = (float)*(&g_RoleSlotBuf.dword_17AA450 + 147);
  (((UIScene *)(v2 + 1272)))->UIScene::UpdateLayout(fVal);
  v44[0] = v40 + 126;
  v44[1] = v41 + 203;
  v46 = v41 + 229;
  v33 = *(_DWORD *)(v2 + 5248);
  v34 = v40 + 216;
  v35 = *(_DWORD *)(v2 + 1544);
  v45 = v40 + 216;
  LOBYTE(v34) = *(_BYTE *)(v33 + 1768);
  (*(void ( **)(int, int *, _DWORD *, int, char *, _DWORD, int))(v35 + 28))(
    v2 + 1544,
    &byte_A00B07,
    (_DWORD *)(v44),
    v2,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v34);
  (((PalScript *)(v2 + 1544)))->PalScript::OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnYes.tga", *(_BYTE *)(*(_DWORD *)(v2 + 5248) + 1768));
  sub_445E50(v2 + 1544);
  v36 = v45;
  v37 = *(_DWORD *)(v2 + 5248);
  v44[0] = v45 + 100;
  v45 += 190;
  LOBYTE(v36) = *(_BYTE *)(v37 + 1768);
  (*(void ( **)(int, int *, _DWORD *, int, char *, _DWORD, int))(*(_DWORD *)(v2 + 1888) + 28))(
    v2 + 1888,
    &dword_A00B08,
    (_DWORD *)(v44),
    v2,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v36);
  (((PalScript *)(v2 + 1888)))->PalScript::OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnNo.tga", *(_BYTE *)(*(_DWORD *)(v2 + 5248) + 1768));
  v54[5] = 200;
  v54[4] = 300;
  v54[7] = 300;
  v54[6] = 600;
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 3876));
  (((UIItem *)(v2 + 3876)))->UIItem::SetData(18);
  return (((PalScript *)(v2 + 2236)))->PalScript::LoadSceneConfig("SubGame\\HockShop\\Data\\HockShopLevel.hsl");
}

// 0x00524960
int UIRoleSelect_SetFieldLeft(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 5252) = nVal;
  return result;
}

// 0x005269B0
void CreateDigitPair(int nVal, UIWnd **ppTens, UIWnd **ppOnes, const char *pszTexBase, char bFlag)
{
  char Buffer[256]; // [esp+0x10] [ebp-0x100] BYREF

  sprintf(Buffer, "%s%d.tga", pszTexBase, nVal / 10);
  (((UIPushButton *)ppTens))->UIPushButton::CreateFromTemplate(Buffer, bFlag);
  sprintf(Buffer, "%s%d.tga", pszTexBase, nVal % 10);
  (((UIPushButton *)ppOnes))->UIPushButton::CreateFromTemplate(Buffer, bFlag);
}

// 0x00527130
int MUIDialog_SetSlotCaption(int nVal)
{
  int v1; // ecx
  int v2; // esi
  DWORD TickCount; // eax
  int v4; // eax
  _DWORD *v5; // ecx
  _DWORD *v6; // eax
  int v7; // ecx
  _DWORD *v8; // ecx
  int v9; // edx
  int result; // eax

  v2 = v1;
  TickCount = GetTickCount();
  CRT_set_new_handler(TickCount);
  v4 = rand() % 2;
  v5 = (_DWORD *)(v2 + 32 * (nVal + 128));
  *v5 = *(_DWORD *)(v2 + 12 * v4 + 4928);
  v5[1] = *(_DWORD *)(v2 + 12 * v4 + 4932);
  v5[2] = *(_DWORD *)(v2 + 12 * v4 + 4936);
  *(_DWORD *)(v2 + 15032) = v4;
  if ( v4 )
  {
    v6 = (_DWORD *)(32 * nVal + v2);
    v6[1101] = *(_DWORD *)(v2 + 4928);
    v6[1102] = *(_DWORD *)(v2 + 4932);
    v7 = *(_DWORD *)(v2 + 4936);
  }
  else
  {
    v6 = (_DWORD *)(v2 + 32 * nVal);
    v6[1101] = *(_DWORD *)(v2 + 4940);
    v6[1102] = *(_DWORD *)(v2 + 4944);
    v7 = *(_DWORD *)(v2 + 4948);
  }
  v6[1103] = v7;
  v8 = (_DWORD *)(v2 + 4388);
  v9 = 5;
  do
  {
    *(v8 - 77) = 0;
    *v8 = 0;
    v8 += 8;
    --v9;
  }
  while ( v9 );
  v6[1020] = 1;
  v6[1097] = 1;
  SetEnable((UICaption *)(v2 + 5256));
  return result;
}

// 0x005273D0
int CCBUI_PlayResultSound(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  CScreenMode *Instance; // eax
  const void *v5; // [esp-0x8] [ebp-0x14]

  v2 = v1;
  *(_BYTE *)(v1 + 6204) = 1;
  if ( *(_BYTE *)(v1 + 3232) )
  {
    if ( *(_DWORD *)(v1 + 15032) )
      *(_BYTE *)(*(_DWORD *)(v1 + 15008) + v1 + 15024) = 0;
    else
      *(_BYTE *)(*(_DWORD *)(v1 + 15008) + v1 + 15024) = 1;
  }
  else if ( *(_BYTE *)(v1 + 3480) )
  {
    *(_BYTE *)(*(_DWORD *)(v1 + 15008) + v1 + 15024) = *(_DWORD *)(v1 + 15032) == 1;
  }
  if ( *(_BYTE *)(*(_DWORD *)(v1 + 15008) + v1 + 15024) )
  {
    sprintf((char *const)(v1 + 96), "\\n      %s", (const char *)&dword_DC873C);
    SetEnable((UICaption *)(v2 + 101028));
    result = (((UIRoleSelect *)(v2 + 100572)))->UIRoleSelect::SetByte(1);
    *(_BYTE *)(v2 + 15037) = 0;
  }
  else
  {
    sprintf((char *const)(v1 + 96), "\\n      %s", (const char *)&dword_DCF63C);
    SetEnable((UICaption *)(v2 + 99660));
    (((UIRoleSelect *)(v2 + 99204)))->UIRoleSelect::SetByte(1);
    (((UINote *)*(UINote **)(*(_DWORD *)(v2 + 99200) + 1724)))->UINote::GetEntryPtr(*(_DWORD *)(v2 + 15008));
    SetEnable((UICaption *)(v2 + 5104));
    (**(void ( ***)(int, int))(v2 + 5104))((int)(v2 + 5104), (int)(1));
    *(_BYTE *)(v2 + 15038) = 0;
    *(_BYTE *)(v2 + 15037) = 1;
    v5 = off_5E7F20;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v5, 1);
  }
  return result;
}

// 0x00527510
int CCBAttackSequen_AdvanceToNextSlot(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // edx
  int SequenceSlot; // eax
  bool v5; // sf
  bool v6; // cc
  int v7; // eax
  CScreenMode *Instance; // eax
  int result; // eax
  const void *v10; // [esp-0x8] [ebp-0x10]
  int v11; // [esp+0x0] [ebp-0x8]

  v2 = v1;
  sub_445E50(v1 + 248 * *(_DWORD *)(v1 + 15008) + 352);
  *(_BYTE *)(v2 + *(_DWORD *)(v2 + 15008) + 15013) = 1;
  *(_DWORD *)(v2 + 3244) = 0;
  *(_BYTE *)(v2 + 3232) = 0;
  *(_DWORD *)(v2 + 3492) = 0;
  *(_BYTE *)(v2 + 3480) = 0;
  (**(void ( ***)(int, _DWORD))(v2 + 3660))((int)(v2 + 3660), (_DWORD)(0));
  v3 = *(_DWORD *)(v2 + 15008);
  *(_BYTE *)(v2 + 15012) = 0;
  *(_DWORD *)(v2 + 15008) = v3 + 1;
  if ( v3 + 1 >= 5 )
    *(_DWORD *)(v2 + 15008) = 0;
  SequenceSlot = (((CCBAttackSequen *)v2))->CCBAttackSequen::FindSequenceSlot(*(_DWORD *)(v2 + 15008));
  v5 = SequenceSlot < 0;
  v6 = SequenceSlot <= 0;
  if ( !SequenceSlot )
  {
LABEL_10:
    *(_BYTE *)(v2 + 6204) = 1;
    *(_BYTE *)(v2 + 15038) = 1;
    *(_BYTE *)(v2 + 15037) = 1;
    CCBUI_UpdateCaptions(v11);
    v10 = off_5E7F24;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v10, 1);
    return result;
  }
  while ( 1 )
  {
    if ( v5 )
    {
      v7 = *(_DWORD *)(v2 + 15008) + 1;
      *(_DWORD *)(v2 + 15008) = v7;
      if ( v7 >= 5 )
        *(_DWORD *)(v2 + 15008) = 0;
      SequenceSlot = (((CCBAttackSequen *)v2))->CCBAttackSequen::FindSequenceSlot(*(_DWORD *)(v2 + 15008));
      goto LABEL_9;
    }
    if ( !v6 )
      break;
LABEL_9:
    v5 = SequenceSlot < 0;
    v6 = SequenceSlot <= 0;
    if ( !SequenceSlot )
      goto LABEL_10;
  }
  result = MUIDialog_SetSlotCaption(*(_DWORD *)(v2 + 15008));
  *(_BYTE *)(v2 + 6204) = 0;
  return result;
}

// 0x00527610
int CCBUI_UpdateCaptions(int nVal)
{
  int v1; // ecx
  int v2; // esi
  const CHAR *v3; // ecx
  void ( ***v4)(int, _DWORD); // ebp
  void ( ***v5)(int, _DWORD); // ebx
  _DWORD *v6; // edi
  bool v7; // zf
  void (***v8)(_DWORD, _DWORD); // edi
  int v9; // ebx
  UIWnd *v10; // ebp
  int v11; // eax
  int i; // ecx
  int v13; // ebx
  int v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // ebp
  void *v18; // edi
  UICaption *v19; // esi
  int result; // eax
  int v21; // [esp-0x4] [ebp-0x134]
  int v22; // [esp+0xC] [ebp-0x124]
  int v23; // [esp+0x14] [ebp-0x11C]
  LPCSTR lpString2; // [esp+0x28] [ebp-0x108]
  const CHAR *lpString2a; // [esp+0x28] [ebp-0x108]
  int v26; // [esp+0x2C] [ebp-0x104]
  char Buffer[253]; // [esp+0x30] [ebp-0x100] BYREF
  __int16 v28; // [esp+0x12D] [ebp-0x3]
  char v29; // [esp+0x12F] [ebp-0x1]

  v2 = v1;
  v26 = 5;
  v3 = (const CHAR *)(v1 + 352);
  *(_BYTE *)(v2 + 15036) = 1;
  v4 = (void ( ***)(int, _DWORD))(v2 + 1776);
  v5 = (void ( ***)(int, _DWORD))(v2 + 1928);
  v6 = (_DWORD *)(v2 + 4388);
  for ( lpString2 = v3; ; v3 = lpString2 )
  {
    (**(void ( ***)(const CHAR *, _DWORD))v3)((const CHAR *)(v3), (_DWORD)(0));
    (**v4)((int)(v2 + 1776), (_DWORD)(0));
    (**v5)((int)(v2 + 1928), (_DWORD)(0));
    *(v6 - 77) = 0;
    *v6 = 0;
    v6[77] = 0;
    (**v4)((int)(v2 + 1776), (_DWORD)(0));
    (**v5)((int)(v2 + 1928), (_DWORD)(0));
    v6 += 8;
    v7 = v26 == 1;
    lpString2 += 248;
    --v26;
    if ( v7 )
      break;
  }
  v8 = (void ( ***)(_DWORD, _DWORD))(v2 + 2080);
  v9 = 3;
  do
  {
    (**v8)((_DWORD)(v8), (_DWORD)(0));
    v8 += 86;
    --v9;
  }
  while ( v9 );
  (**(void ( ***)(int, _DWORD))(v2 + 3164))((int)(v2 + 3164), (_DWORD)(0));
  (**(void ( ***)(int, _DWORD))(v2 + 3412))((int)(v2 + 3412), (_DWORD)(0));
  (**(void ( ***)(int, _DWORD))(v2 + 3660))((int)(v2 + 3660), (_DWORD)(0));
  v10 = (UIWnd *)(v2 + 6468);
  (**(void ( ***)(int, int))(v2 + 6468))((int)(v2 + 6468), (int)(1));
  v11 = 0;
  *(_DWORD *)(v2 + 15040) = 0;
  *(_DWORD *)(v2 + 15044) = 80;
  for ( i = 0; i < 50; i += 10 )
  {
    if ( *(_BYTE *)(v2 + v11 + 15013) && *(_BYTE *)(v11 + v2 + 15024) )
    {
      v13 = *(_DWORD *)(v2 + 15044);
      ++*(_DWORD *)(v2 + 15040);
      *(_DWORD *)(v2 + 15044) = 2 * (v13 + i);
    }
    ++v11;
  }
  v14 = *(_DWORD *)(v2 + 15020);
  v15 = *(_DWORD *)(v2 + 15044);
  *(_DWORD *)(v2 + 6456) = 150;
  v23 = v15 + 40 * v14;
  v22 = *(_DWORD *)(v2 + 15040);
  v21 = *(_DWORD *)(v2 + 6200);
  *(_DWORD *)(v2 + 15048) = v23;
  *(_DWORD *)(v2 + 6464) = 20 * v22 + 350;
  sprintf(
    (char *const)(v2 + 96),
    "\\n\\n        %s:   %d\\n        %s: %d\\n        %s:   %d\\n        %s:     %d\\n",
    (const char *)&dword_DC853C,
    v21,
    (const char *)&dword_DC863C,
    v14,
    (const char *)&dword_DC873C,
    v22,
    (const char *)&dword_DC883C,
    v23);
  memset(Buffer, 0, sizeof(Buffer));
  v16 = *(_DWORD *)(v2 + 99200);
  v28 = 0;
  v29 = 0;
  if ( *(_BYTE *)(v16 + 1740) )
  {
    if ( *(int *)(v2 + 15040) > 0 )
    {
      sprintf(Buffer, "\\n\\n        %s: \\n\\n", (const char *)&dword_DC893C);
      lstrcatA((LPSTR)(v2 + 96), Buffer);
      v17 = 0;
      lpString2a = (const CHAR *)(v2 + 7776);
      do
      {
        if ( *(_BYTE *)(v2 + v17 + 15024) )
        {
          lstrcatA((LPSTR)(v2 + 96), "        ");
          lstrcatA((LPSTR)(v2 + 96), lpString2a);
          lstrcatA((LPSTR)(v2 + 96), aN);
        }
        ++v17;
        lpString2a += 1608;
      }
      while ( v17 < 5 );
      v10 = (UIWnd *)(v2 + 6468);
    }
    else
    {
      sprintf(Buffer, "\\n\\n        %s:   %s", (const char *)&dword_DC893C, byte_DC7D3C);
      lstrcatA((LPSTR)(v2 + 96), Buffer);
    }
  }
  else
  {
    *(_DWORD *)(v2 + 6456) = 200;
    *(_DWORD *)(v2 + 6464) = 400;
  }
  v18 = (void *)(v2 + 6452);
  v19 = (UICaption *)(v2 + 6660);
  (((UIWnd *)v19))->UIWnd::sub_445FA0(v18);
  (((UIWnd *)v10))->UIWnd::sub_445FA0(v18);
  (**(void ( ***)(UICaption *, _DWORD))((UIWnd *)v19))((UICaption *)(v19), (_DWORD)(0));
  SetEnable(v19);
  return result;
}

// 0x00527A80
int SoundContext_CreateSubPanels(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  int v4; // ecx
  JusticeBookUI *v5; // eax
  PAL_GDB *v6; // eax
  SaleUI *v7; // eax
  CCBUI *inited; // eax
  int result; // eax
  CScreenMode *Instance; // eax
  gbAudioManager *v11; // esi

  v2 = v1;
  v3 = *(_DWORD *)(v1 + 88);
  v4 = *(_DWORD *)(v1 + 92);
  *(_DWORD *)(v2 + 80) = v3;
  *(_DWORD *)(v2 + 84) = v4;
  *(_DWORD *)(v2 + 76) = 0;
  *(_DWORD *)(v2 + 72) = 0;
  (((UIListBox *)v2))->UIListBox::SetSelTexture(-1, 0, 0, *(_DWORD *)(v2 + 80), *(_DWORD *)(v2 + 84));
  Create__ovl_1((ARC_PlayerAtt *)(v2 + 356));
  (((UIItem *)(v2 + 356)))->UIItem::SetData(31);
  v5 = (JusticeBookUI *)operator new(0xDB80u);
  if ( v5 )
    v5->JusticeBookUI::JusticeBookUI();
  else
    v6 = 0;
  *(_DWORD *)(v2 + 1724) = (_DWORD)v6;
  (((PAL_GDB *)v6))->PAL_GDB::InitSkillDisplay();
  v7 = (SaleUI *)operator new(0x18E34u);
  if ( v7 )
    inited = (CCBUI *)(((SaleUI *)v7))->SaleUI::InitUI();
  else
    inited = 0;
  *(_DWORD *)(v2 + 1728) = (_DWORD)inited;
  (((CCBUI *)inited))->CCBUI::InitSkillUI(v2);
  result = nVal;
  *(_DWORD *)(*(_DWORD *)(v2 + 1724) + 12748) = *(_DWORD *)(v2 + 1728);
  *(_BYTE *)(v2 + 1740) = 0;
  *(_DWORD *)(v2 + 1736) = nVal;
  if ( !nVal )
  {
    result = (int)(((PAL3 *)v2))->PAL3::HandleDeviceLost();
    *(_BYTE *)(v2 + 1740) = 1;
  }
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    result = (((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    v11 = (gbAudioManager *)result;
    if ( result )
    {
      (((gbAudioManager *)result))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v11))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v11))->gbAudioManager::StopSoundStream(2);
      (((gbAudioManager *)v11))->gbAudioManager::StopSoundStream(1);
    }
  }
  return result;
}

// 0x00528D50
int SceneMgr_LoadMainUITexture(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int *v3; // ebx
  int v4; // edi
  int v5; // ebp
  int v6; // eax
  void *v7; // edi
  const void *v8; // esi
  bool v9; // zf
  int result; // eax
  float fX; // [esp+0x0] [ebp-0x28]
  float fXa; // [esp+0x0] [ebp-0x28]
  float fY; // [esp+0x4] [ebp-0x24]
  float fYa; // [esp+0x4] [ebp-0x24]
  int v15; // [esp+0x18] [ebp-0x10]
  int v16; // [esp+0x1C] [ebp-0xC]
  int v17; // [esp+0x20] [ebp-0x8]

  v2 = v1;
  v16 = v1;
  v3 = (int *)(v1 + 56172);
  v4 = *(_DWORD *)(v1 + 56180) - *(_DWORD *)(v1 + 56172);
  v17 = v4;
  v5 = v1 + 14124;
  v15 = 36;
  while ( 1 )
  {
    (((RenderTarget *)v5))->RenderTarget::LoadTexture("UI\\GameMainUI\\Par_Effect\\spark_16.tga");
    (((RenderTarget *)v5))->RenderTarget::SetSize(16);
    (((RenderTarget *)v5))->RenderTarget::SetColor(0x19u, 0x75u, 0xFCu);
    v6 = rand();
    (((RenderTarget *)v5))->RenderTarget::SetAlpha(v6 % 100 - 101);
    *(_BYTE *)(v5 + 104) = 1;
    (((RenderTarget *)v5))->RenderTarget::SetField084(0x40000000);
    (((RenderTarget *)v5))->RenderTarget::SetState(1061997773);
    fY = (float)*(int *)(v2 + 56176);
    fX = (float)(*v3 + rand() % v4);
    (((RenderTarget *)v5))->RenderTarget::UpdateTransform(fX, fY);
    (((RenderTarget *)v5))->RenderTarget::Render(*v3, v3[1], v3[2]);
    fYa = (float)(rand() % 2 + 1);
    fXa = (float)(rand() % 2 + 1);
    (((RenderTarget *)v5))->RenderTarget::SetOffset(fXa, fYa);
    (((RenderTarget *)v5))->RenderTarget::SetScale(0, 0);
    (((RenderTarget *)v5))->RenderTarget::SetVisible(1);
    v7 = (void *)(v5 + 21024);
    v8 = (const void *)v5;
    v5 += 584;
    v9 = v15 == 1;
    qmemcpy(v7, v8, 0x248u);
    --v15;
    if ( v9 )
      break;
    v4 = v17;
    v2 = v16;
  }
  result = v16;
  *(_BYTE *)(v16 + 56189) = 0;
  return result;
}

// 0x00529400
int * CountActiveParticles(UIParticle *_this, int *a2)
{
  int *result; // eax
  int v3; // esi
  int *v4; // edx

  result = (int *)(*(int **)&_this[3]._texName[68]);
  v3 = 0;
  if ( (int)result > 0 )
  {
    v4 = (int *)&_this[3]._texName[100];
    result = (int *)&_this[3]._element.m_bvisible;
    do
    {
      ++v3;
      *(v4 - 2) = *(result - 2);
      *(v4 - 1) = *(result - 1);
      *v4 = *result;
      result += 3;
      v4 += 8;
    }
    while ( v3 < *(_DWORD *)&_this[3]._texName[68] );
  }
  return result;
}

// 0x0052AEF0
int UIDialog_ResetState(int nVal)
{
  _DWORD *v1; // ecx
  int result; // eax

  result = (int)v1;
  v1[67] = 0;
  v1[68] = 0;
  v1[69] = 0;
  v1[66] = 0;
  v1[64] = 0;
  return result;
}

// 0x0052AFC0
int UINote_RenderIfVisible(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax

  v2 = v1;
  result = *(_DWORD *)(v1 + 256);
  if ( result )
  {
    (((UINote *)v1))->UINote::RenderWithStack((gbMatrixStack *)nVal);
    return (*(int ( **)(_DWORD, _DWORD))(**(_DWORD **)(v2 + 256) + 16))(*(_DWORD *)(v2 + 256), 0);
  }
  return result;
}

// 0x0052B1E0
int CCBStageScene_InitCameraPositions(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  int v6; // [esp+0x0] [ebp-0x20]

  v2 = v1;
  v3 = v1 + 776;
  v4 = 5;
  do
  {
    v3 += 12;
    --v4;
  }
  while ( v4 );
  (((ObjectCamera *)(v2 + 856)))->ObjectCamera::Update();
  *(_DWORD *)(v2 + 1008) = 0;
  *(_DWORD *)(v2 + 1012) = 0;
  *(_DWORD *)(v2 + 1016) = 0;
  *(_DWORD *)(v2 + 1020) = 0;
  *(_DWORD *)(v2 + 1024) = 0;
  *(_DWORD *)(v2 + 1028) = 0;
  *(_DWORD *)(v2 + 1032) = 0;
  *(_DWORD *)(v2 + 1036) = 0;
  *(_DWORD *)(v2 + 1040) = 0;
  CCBStageScene_SetCameraDefaults(v6);
  return v2;
}

// 0x0052B350
int CCBStageScene_SetCameraDefaults(int nVal)
{
  _DWORD *v1; // ecx
  int result; // eax

  result = 0;
  v1[253] = 1120403456;
  v1[252] = 0;
  v1[254] = 1133903872;
  v1[255] = 0;
  v1[256] = -1032847360;
  v1[257] = 0;
  v1[258] = 0;
  v1[259] = 1065353216;
  v1[260] = 0;
  v1[2] = 0;
  v1[3] = 0;
  *v1 = 0;
  v1[1] = 0;
  return result;
}

// 0x0052B3B0
int CCBStageScene_CreateCamera(int nVal)
{
  int v1; // ecx
  int v2; // esi
  ObjectCamera *v3; // eax
  int v4; // ebp
  float *v5; // eax
  int v6; // edi
  UI3DCtrl *v7; // eax
  gbVisNode *v8; // eax
  gbVisNode *v9; // edi
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v12; // edi
  UICoverFrm *v13; // eax
  Camera *v14; // eax
  CScreenMode *v15; // eax
  int result; // eax
  gbVec3D v17; // [esp-0x10] [ebp-0x178]
  const char *v18; // [esp-0x8] [ebp-0x170]
  const void *v19; // [esp-0x8] [ebp-0x170]
  int v20; // [esp+0x0] [ebp-0x168]
  float *v21; // [esp+0x10] [ebp-0x158]
  void *v22; // [esp+0x10] [ebp-0x158]
  char *pszName; // [esp+0x20] [ebp-0x148]
  _DWORD *v24; // [esp+0x24] [ebp-0x144]
  _DWORD v25[2]; // [esp+0x28] [ebp-0x140] BYREF
  __int16 v26; // [esp+0x30] [ebp-0x138]
  char *v27; // [esp+0x32] [ebp-0x136]
  int v28; // [esp+0x36] [ebp-0x132]
  __int16 v29; // [esp+0x3A] [ebp-0x12E]
  char *v30; // [esp+0x3C] [ebp-0x12C]
  int v31; // [esp+0x40] [ebp-0x128]
  __int16 v32; // [esp+0x44] [ebp-0x124]
  int v33; // [esp+0x46] [ebp-0x122]
  int v34; // [esp+0x4A] [ebp-0x11E]
  __int16 v35; // [esp+0x4E] [ebp-0x11A]
  void *v36; // [esp+0x50] [ebp-0x118]
  int v37; // [esp+0x54] [ebp-0x114]
  __int16 v38; // [esp+0x58] [ebp-0x110]
  char Buffer[253]; // [esp+0x5C] [ebp-0x10C] BYREF
  __int16 v40; // [esp+0x159] [ebp-0xF]
  char v41; // [esp+0x15B] [ebp-0xD]
  int v42; // [esp+0x164] [ebp-0x4]

  v2 = v1;
  v3 = (ObjectCamera *)operator new(0x7Cu);
  v4 = 0;
  v42 = 0;
  if ( v3 )
    v5 = (((ObjectCamera *)v3))->ObjectCamera::Create();
  else
    v5 = 0;
  *(_DWORD *)(v2 + 12) = (_DWORD)v5;
  v42 = -1;
  (((ObjectCamera *)v5))->ObjectCamera::SetCameraEyePosition(gfxMgr);
  (((ObjectCamera *)*(ObjectCamera **)(v2 + 12)))->ObjectCamera::SetCameraRotate(86.0, 0.0, -200.0);
  v17.x = 0.0f;
  *(_QWORD *)&v17.y = 0xC42F000041A00000ui64;
  (((ObjectCamera *)*(ObjectCamera **)(v2 + 12)))->ObjectCamera::SetCameraAtPosition(v17, 1);
  (((ObjectCamera *)*(ObjectCamera **)(v2 + 12)))->ObjectCamera::SetCameraDist(1142341632, -1052770304, 0);
  *(_DWORD *)(v2 + 776) = 1121189888;
  *(_DWORD *)(v2 + 780) = 0;
  *(_DWORD *)(v2 + 784) = -1018429440;
  *(_DWORD *)(v2 + 788) = 1082130432;
  *(_DWORD *)(v2 + 792) = 0;
  *(_DWORD *)(v2 + 796) = -1020854272;
  *(_DWORD *)(v2 + 800) = -1028521984;
  *(_DWORD *)(v2 + 804) = 0;
  *(_DWORD *)(v2 + 808) = -1018953728;
  *(_DWORD *)(v2 + 812) = -1028915200;
  *(_DWORD *)(v2 + 816) = 0;
  *(_DWORD *)(v2 + 820) = -1014366208;
  *(_DWORD *)(v2 + 824) = 1118961664;
  *(_DWORD *)(v2 + 828) = 0;
  *(_DWORD *)(v2 + 832) = -1014562816;
  *(_DWORD *)(v2 + 836) = 1132462080;
  *(_DWORD *)(v2 + 840) = 1126825984;
  *(_DWORD *)(v2 + 844) = 1122500608;
  *(_DWORD *)(v2 + 848) = 1117782016;
  *(_DWORD *)(v2 + 852) = 1133510656;
  v25[0] = *(_DWORD *)dword_58619C;
  v25[1] = 0;
  v26 = 0;
  v27 = g_pszSceneSlot1;
  v28 = 0;
  v29 = 0;
  v30 = g_pszSceneSlot2;
  v31 = 0;
  v32 = 0;
  v33 = *(_DWORD *)g_szFormat105;
  v34 = 0;
  v35 = 0;
  v36 = g_pfnUpdateFuncs[0];
  v37 = 0;
  v24 = (_DWORD *)(v2 + 836);
  v38 = 0;
  pszName = (char *)v25;
  v21 = (float *)(v2 + 776);
  v6 = v2 + 96;
  do
  {
    (((Object3D *)(v6 - 80)))->Object3D::_todo_0047CB90(pszName, 10);
    (((Object3D *)(v6 - 80)))->Object3D::VecAngle(*v21, v21[1], v21[2]);
    *(_DWORD *)(v6 - 24) = (unsigned long)*v24;
    *(_DWORD *)(v6 + 4) = *(_DWORD *)(v2 + 12);
    if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + v4) )
    {
      *(_BYTE *)v6 = 1;
    }
    else
    {
      *(_BYTE *)v6 = 0;
      *(_BYTE *)(v6 - 59) = 0;
    }
    ++v4;
    v6 += 152;
    ++v24;
    pszName += 10;
    v21 += 3;
  }
  while ( v4 < 5 );
  v22 = (void *)operator new(0x118u);
  v42 = 1;
  if ( v22 )
    v7 = (UI3DCtrl *)UIDialog_ResetState(v20);
  else
    v7 = 0;
  v42 = -1;
  *(_DWORD *)v2 = (_DWORD)v7;
  (((UI3DCtrl *)v7))->UI3DCtrl::LoadModel(pszModelName);
  switch ( nVal )
  {
    case 0:
      v18 = (const char *)"SubGame\\Encampment\\EncampFlag\\WZ07\\WZ07.pol";
      goto LABEL_17;
    case 1:
      v18 = (const char *)"SubGame\\Encampment\\EncampFlag\\WZ08\\WZ08.pol";
      goto LABEL_17;
    case 2:
      v18 = (const char *)"SubGame\\Encampment\\EncampFlag\\WZ09\\WZ09.pol";
      goto LABEL_17;
    case 3:
      v18 = (const char *)"SubGame\\Encampment\\EncampFlag\\WZ10\\WZ10.pol";
LABEL_17:
      (((Object3D *)(v2 + 856)))->Object3D::_todo_0047CB90(v18, 0);
      break;
    default:
      break;
  }
  (((Object3D *)(v2 + 856)))->Object3D::VecAngle(0.0, 0.0, 0.0);
  *(_DWORD *)(v2 + 940) = *(_DWORD *)(v2 + 12);
  memset(Buffer, 0, sizeof(Buffer));
  v40 = 0;
  v41 = 0;
  sprintf(Buffer, "%s", "SubGame\\Encampment\\Encamp_scene\\Encamp_scene.lgt");
  if ( (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) )
  {
    v8 = (gbVisNode *)operator new(0x58u);
    v9 = (gbVisNode *)v8;
    v42 = 2;
    if ( v8 )
      v8->gbVisNode::gbVisNode();
    else
      v9 = 0;
    v42 = -1;
    *(_DWORD *)(v2 + 8) = (_DWORD)v9;
    *(_DWORD *)(v2 + 8) = gbLoadLightFile(Buffer);
  }
  if ( (g_dwGameFlags & 4) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    v12 = (gbAudioManager *)AudioManager;
    if ( AudioManager )
    {
      (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v12))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v12))->gbAudioManager::StopSoundStream(2);
    }
  }
  v13 = (UICoverFrm *)operator new(0x329Cu);
  v42 = 3;
  if ( v13 )
    v13->UICoverFrm::UICoverFrm();
  else
    v14 = 0;
  v42 = -1;
  *(_DWORD *)(v2 + 4) = (_DWORD)v14;
  (((Camera *)v14))->Camera::InitUIElements();
  v19 = off_5EFAB4;
  v15 = (CScreenMode *)CScreenMode::GetInstance();
  (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(v19, 1);
  return 1;
}

// 0x0052B900
int MiniGame1Update(double pData)
{
  int v1; // ecx
  int v2; // ebp
  int v3; // esi
  int v4; // ebx
  float fVal; // [esp+0x0] [ebp-0x4]

  fVal = pData;
  v2 = v1;
  v3 = v1 + 24;
  v4 = 5;
  do
  {
    (((Object3D *)(v3 - 8)))->Object3D::CaculateRelative(fVal);
    if ( (((Object3D *)*(Object3D **)v3))->Object3D::GetVisNode() == (gbVisNode *)1 )
      (((Actor *)*(Actor **)v3))->Actor::CompareActionName(*(_DWORD *)(v3 + 140), 0);
    v3 += 152;
    --v4;
  }
  while ( v4 );
  (((Object3D *)(v2 + 856)))->Object3D::CaculateRelative(fVal);
  (((ObjectCamera *)*(ObjectCamera **)(v2 + 12)))->ObjectCamera::SetStepRotate();
  return (((UINote *)*(UINote **)v2))->UINote::CallVtableMethod(pData);
}

// 0x0052CD40
void LayoutSlot(UIScenePanel *_this)
{
  char *v2; // esi
  int v3; // eax
  int v4; // eax
  int v5; // [esp+0xC] [ebp-0x80] BYREF
  int v6; // [esp+0x10] [ebp-0x7C]
  int v7; // [esp+0x14] [ebp-0x78]
  int v8; // [esp+0x18] [ebp-0x74]
  int v9; // [esp+0x1C] [ebp-0x70] BYREF
  int v10; // [esp+0x20] [ebp-0x6C]
  int v11; // [esp+0x24] [ebp-0x68]
  int v12; // [esp+0x28] [ebp-0x64]
  _DWORD v13[4]; // [esp+0x2C] [ebp-0x60] BYREF
  _DWORD v14[4]; // [esp+0x3C] [ebp-0x50] BYREF
  _DWORD v15[4]; // [esp+0x4C] [ebp-0x40] BYREF
  _DWORD v16[4]; // [esp+0x5C] [ebp-0x30] BYREF
  _DWORD v17[4]; // [esp+0x6C] [ebp-0x20] BYREF
  _DWORD v18[4]; // [esp+0x7C] [ebp-0x10] BYREF
  int v19; // [esp+0x90] [ebp+0x4]
  int a2; // [esp+0x94] [ebp+0x8] BYREF
  int v21; // [esp+0x98] [ebp+0xC]

  v2 = (char *)_this + 1552 * v19;
  (((UIWnd *)(v2 + 2424)))->UIWnd::sub_445FA0(&a2);
  v13[0] = a2 + 42;
  v13[1] = v21 + 2;
  v13[2] = a2 + 152;
  v13[3] = v21 + 34;
  (((UIWnd *)(v2 + 2576)))->UIWnd::sub_445FA0(v13);
  v14[0] = a2 + 58;
  v14[1] = v21 + 33;
  v14[2] = a2 + 123;
  v14[3] = v21 + 119;
  (((UIWnd *)(v2 + 2728)))->UIWnd::sub_445FA0(v14);
  v5 = a2 + 40;
  v6 = v21 + 132;
  v7 = a2 + 62;
  v8 = v21 + 151;
  v3 = (((UIWnd *)(v2 + 2880)))->UIWnd::sub_445FA0(&v5);
  LOBYTE(v3) = *((_BYTE *)&_this->m_SceneD.m_hTexture + 69);
  (((UIPushButton *)(v2 + 2880)))->UIPushButton::CreateFromTemplate("SubGame\\Encampment\\JingText.tga", v3);
  v15[0] = v5 + 16;
  v15[1] = v6 + 6;
  v15[2] = v5 + 92;
  v15[3] = v6 + 18;
  sub_43FEC0(v15);
  (((UIScene *)(v2 + 3032)))->UIScene::GetChildCount();
  (((UIScene *)(v2 + 3032)))->UIScene::GetChildAt();
  sub_43FD90((float *)v2 + 758, 2);
  (((UIProgressBar *)(v2 + 3032)))->UIProgressBar::GetWidth(2);
  (((UIProgressBar *)(v2 + 3032)))->UIProgressBar::GetHeight(2);
  (((UIProgressBar *)(v2 + 3032)))->UIProgressBar::GetPosition(1);
  v16[1] = v6 - 16;
  v16[0] = v5 + 26;
  v16[3] = v6 - 16 + 32;
  v16[2] = v5 + 106;
  (((UIWnd *)(v2 + 3276)))->UIWnd::sub_445FA0(v16);
  v9 = v5;
  v10 = v6 + 26;
  v11 = v5 + 22;
  v12 = v6 + 45;
  v4 = (((UIWnd *)(v2 + 3428)))->UIWnd::sub_445FA0(&v9);
  LOBYTE(v4) = *((_BYTE *)&_this->m_SceneD.m_hTexture + 69);
  (((UIPushButton *)(v2 + 3428)))->UIPushButton::CreateFromTemplate("SubGame\\Encampment\\ShenText.tga", v4);
  v17[0] = v9 + 16;
  v17[1] = v10 + 6;
  v17[2] = v9 + 92;
  v17[3] = v10 + 18;
  sub_43FEC0(v17);
  (((UIScene *)(v2 + 3580)))->UIScene::GetChildCount();
  (((UIScene *)(v2 + 3580)))->UIScene::GetChildAt();
  sub_43FD90((float *)v2 + 895, 2);
  (((UIProgressBar *)(v2 + 3580)))->UIProgressBar::GetWidth(2);
  (((UIProgressBar *)(v2 + 3580)))->UIProgressBar::GetHeight(2);
  (((UIProgressBar *)(v2 + 3580)))->UIProgressBar::GetPosition(1);
  v18[1] = v10 - 16;
  v18[0] = v9 + 26;
  v18[3] = v10 - 16 + 32;
  v18[2] = v9 + 106;
  (((UIWnd *)(v2 + 3824)))->UIWnd::sub_445FA0(v18);
}

// 0x0052D770
// Microsoft VisualC 2-14/net runtime
void MiniGame2_ClearState()
{
  _DWORD *v0; // ecx

  *v0 = 0;
  v0[1] = 0;
  v0[2] = 0;
}

// 0x0052F350
int MiniGame2Update(float fVal)
{
  int v1; // ecx
  int v2; // esi
  int result; // eax
  int v4; // ecx
  ScreenEffectMgr *v5; // ecx
  CScreenMode *v6; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v8; // esi
  CScreenMode *v9; // eax
  CScreenMode *v10; // eax
  ScreenEffect *Instance; // eax
  double v12; // st7
  char v13; // al
  unsigned int v14; // ecx
  unsigned int v15; // edx
  unsigned int v16; // ecx
  float *v17; // eax
  unsigned int v18; // edx
  double v19; // st7
  double v20; // st6
  float fVala; // [esp+0x14] [ebp+0x4]

  v2 = v1;
  StopSceneScripts((const char *)LODWORD(fVal));
  LOBYTE(result) = *(_BYTE *)(v2 + 24);
  if ( (_BYTE)result )
  {
    v4 = *(_DWORD *)(v2 + 20);
    if ( v4 )
    {
      result = (*(int ( **)(int))(*(_DWORD *)v4 + 4))(v4);
      if ( !result )
      {
        PAL3::WriteRegistryDwordEx(szSubKey, (DWORD)"S_GAME_C", 1);
        (((CGameData *)&g_gamefrm))->CGameData::Load(*(CUtil **)(v2 + 300));
        if ( *(_DWORD *)(v2 + 300) )
        {
          Instance = (((ScreenEffectMgr *)v5))->ScreenEffectMgr::GetInstance();
          return (((ScreenEffectMgr *)Instance))->ScreenEffectMgr::ProcessEffect(2);
        }
        else
        {
          (((PalScriptMgr *)dword_DBA254))->PalScriptMgr::Destroy();
          LOBYTE(result) = g_dwGameFlags;
          if ( (g_dwGameFlags & 4) != 0 )
          {
            v6 = (CScreenMode *)CScreenMode::GetInstance();
            AudioManager = (gbAudioManager *)(((CScreenMode *)v6))->CScreenMode::GetAudioManager();
            v8 = (gbAudioManager *)AudioManager;
            if ( AudioManager )
            {
              (((gbAudioManager *)AudioManager))->gbAudioManager::StopSoundStream(1);
              (((gbAudioManager *)v8))->gbAudioManager::StopSoundStream(2);
            }
            if ( CScreenMode::GetInstance()->m_bRenderAlt )
            {
              v9 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v9))->CScreenMode::AudioFadeOut();
            }
            else
            {
              v10 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v10))->CScreenMode::AudioStopAll();
            }
          }
        }
      }
    }
  }
  else
  {
    if ( *(_BYTE *)(v2 + 293) )
    {
      v12 = fVal;
    }
    else
    {
      if ( *(_BYTE *)(v2 + 292) )
        *(_BYTE *)(v2 + 292) = 0;
      *(float *)(*(_DWORD *)(v2 + 276) + 4 * *(_DWORD *)(v2 + 284)) = fVal;
      v13 = *(_BYTE *)(v2 + 294);
      v14 = *(_DWORD *)(v2 + 284) + 1;
      *(_DWORD *)(v2 + 284) = v14;
      v15 = v14;
      if ( !v13 )
        *(_BYTE *)(v2 + 294) = v14 >= *(_DWORD *)(v2 + 272);
      v16 = *(_DWORD *)(v2 + 272);
      *(_DWORD *)(v2 + 280) = 0;
      *(_DWORD *)(v2 + 284) = v15 < v16 ? v15 : 0;
      if ( v16 )
      {
        v17 = (float *)*(float **)(v2 + 276);
        v18 = v16;
        do
        {
          v19 = *v17++ + *(float *)(v2 + 280);
          --v18;
          *(float *)(v2 + 280) = v19;
        }
        while ( v18 );
      }
      v12 = *(float *)(v2 + 280) / (double)v16;
    }
    if ( *(_BYTE *)(v2 + 296) )
    {
      fVala = flt_5F4B9C * v12;
    }
    else if ( *(_BYTE *)(v2 + 294) )
    {
      v20 = flt_5F4B9C * v12;
      *(_BYTE *)(v2 + 296) = 1;
      fVala = v20;
    }
    else
    {
      fVala = 1.0f;
    }
    (((CameraCtrl *)*(CameraCtrl **)(v2 + 4)))->CameraCtrl::SetViewport(SLODWORD(fVala));
    (((Actor *)*(Actor **)v2))->Actor::UpdateFrame(fVala);
    (((ArcLocaleRole *)*(ArcLocaleRole **)(v2 + 12)))->ArcLocaleRole::DispatchActive(SLODWORD(fVala));
    return MiniGame2Scene_UpdateMiniGame2(SLODWORD(fVala));
  }
  return result;
}

// 0x0052F8E0
int RoleAtt_LoadGeomNode(int nVal)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // esi
  int *v3; // ebp
  gbGeomNode *v4; // edi
  int *v5; // ebx
  const char *v6; // ebp
  bool v7; // zf
  int result; // eax
  gbOBBox *v9; // [esp+0x10] [ebp-0x164]
  int v10; // [esp+0x14] [ebp-0x160]
  OpenBaseFile v11; // [esp+0x18] [ebp-0x15C] BYREF
  char Buffer[253]; // [esp+0x1C] [ebp-0x158] BYREF
  __int16 v13; // [esp+0x119] [ebp-0x5B]
  char v14; // [esp+0x11B] [ebp-0x59]
  gbMatrix4 v15; // [esp+0x11C] [ebp-0x58] BYREF
  int v16; // [esp+0x170] [ebp-0x4]

  v2 = (_DWORD *)v1;
  v3 = (int *)v1 + 553;
  v1[554] = 6029;
  v1[555] = 6017;
  v1[553] = 6019;
  v16 = 0;
  memset(Buffer, 0, sizeof(Buffer));
  v13 = 0;
  v14 = 0;
  v4 = (gbGeomNode *)(v2 + 556);
  v9 = (gbOBBox *)(v2 + 775);
  v5 = (int *)v3;
  v10 = 3;
  do
  {
    v6 = (const char *)((((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetSkillNum(*v5) + 36);
    if ( !strcmp(v6, unk_C10D38) )
      sprintf(Buffer, "%s", "NONE");
    else
      sprintf(Buffer, "Item\\%s\\%s.pol", v6, v6);
    (((gbGeomNode *)v4))->gbGeomNode::LoadFromFile(Buffer, 0, 0);
    (((gbGeomNode *)v4))->gbGeomNode::GetOBBox(v9);
    ++v5;
    v4 = (gbGeomNode *)((char *)v4 + 280);
    v7 = v10 == 1;
    ++v9;
    --v10;
  }
  while ( !v7 );
  v16 = -1;
  ((OpenNULLFile *)&v11)->OpenNULLFile::OpenNULLFile();
  return result;
}

// 0x0052FC50
int GetTableEntry(int a2)
{
  int v1; // ecx

  return *(_DWORD *)(v1 + 4 * a2 + 2212);
}

// 0x0052FE30
int MiniGame2Scene_UpdateMiniGame2(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  int result; // eax
  int v6; // edi
  int v7; // ebp
  float v8; // st7
  __int16 v9; // fps
  bool v10; // c0
  char v11; // c2
  bool v12; // c3
  float v13; // st7
  float v14; // st6
  float v15; // edx
  float v16; // st7
  int v17; // ecx
  float v18; // st7
  float v19; // ecx
  float v20; // st7
  float v21; // edx
  float v22; // st7
  float v23; // st7
  long double v24; // st7
  float v25; // st7
  char v27; // c0
  gbVec3D v28; // [esp+0x10] [ebp-0x30] BYREF
  gbVec3D v29; // [esp+0x1C] [ebp-0x24] BYREF
  float v30; // [esp+0x28] [ebp-0x18]
  float v31; // [esp+0x2C] [ebp-0x14]
  float v32; // [esp+0x30] [ebp-0x10]
  float v33; // [esp+0x34] [ebp-0xC]
  float v34; // [esp+0x38] [ebp-0x8]
  float v35; // [esp+0x3C] [ebp-0x4]

  v2 = v1;
  v3 = v1;
  v4 = 6;
  do
  {
    result = (*(int ( **)(int))(*(_DWORD *)v3 + 20))(v3);
    v3 += 280;
    --v4;
  }
  while ( v4 );
  v6 = 0;
  v7 = v2 + 2224;
  do
  {
    if ( *(_BYTE *)(v2 + v6 + 3328) )
      result = (*(int ( **)(int))(*(_DWORD *)v7 + 20))(v7);
    ++v6;
    v7 += 280;
  }
  while ( v6 < 3 );
  v8 = *(float *)&nVal * 6.0f + *(float *)(v2 + 3332);
  *(float *)(v2 + 3332) = v8;
  v10 = v8 < 360.0f;
  v11 = 0;
  v12 = v8 == 360.0f;
  LOWORD(result) = v9;
  if ( v8 >= 360.0f )
    *(_DWORD *)(v2 + 3332) = 0;
  if ( *(_BYTE *)(v2 + 3744) )
  {
    result = (((ArcSceneMonster *)(v2 + 3748)))->ArcSceneMonster::CheckDistance(*(float *)(v2 + 3728));
    if ( result )
    {
      v13 = *(float *)result - *(float *)(v2 + 3628);
      v34 = *(float *)(result + 4) - *(float *)(v2 + 3632);
      v14 = *(float *)(result + 8) - *(float *)(v2 + 3636);
      *(float *)(v2 + 3644) = v34;
      v35 = v14;
      v15 = v35;
      *(float *)(v2 + 3640) = v13;
      *(float *)(v2 + 3648) = v15;
      (((gbVec3D *)(v2 + 3640)))->gbVec3D::Normalize();
      v16 = *(float *)(v2 + 3732) * *(float *)(v2 + 3640);
      v17 = *(_DWORD *)(v2 + 3628);
      *(_DWORD *)(v2 + 3620) = *(_DWORD *)(v2 + 3632);
      *(_DWORD *)(v2 + 3616) = v17;
      *(_DWORD *)(v2 + 3624) = *(_DWORD *)(v2 + 3636);
      v18 = v16 * *(float *)&nVal + *(float *)(v2 + 3628);
      v30 = *(float *)(v2 + 3616);
      v19 = *(float *)(v2 + 3620);
      *(float *)(v2 + 3628) = v18;
      v20 = *(float *)(v2 + 3644) * *(float *)(v2 + 3732);
      v21 = *(float *)(v2 + 3624);
      v31 = v19;
      v32 = v21;
      *(float *)(v2 + 3632) = v20 * *(float *)&nVal + *(float *)(v2 + 3632);
      *(float *)(v2 + 3636) = *(float *)(v2 + 3648) * *(float *)(v2 + 3732) * *(float *)&nVal + *(float *)(v2 + 3636);
      v33 = *(float *)(v2 + 3628);
      v34 = *(float *)(v2 + 3632);
      v35 = *(float *)(v2 + 3636);
      *(float *)(v2 + 3728) = sqrt((v30 - v33) * (v30 - v33) + (v31 - v34) * (v31 - v34) + (v32 - v35) * (v32 - v35))
                            + *(float *)(v2 + 3728);
      v33 = *(float *)(v2 + 3628) - *(float *)(v2 + 3616);
      v22 = *(float *)(v2 + 3632) - *(float *)(v2 + 3620);
      v29.x = v33;
      v34 = v22;
      v23 = *(float *)(v2 + 3636) - *(float *)(v2 + 3624);
      v29.y = v34;
      v35 = v23;
      v29.z = v35;
      (((gbVec3D *)&v29))->gbVec3D::Normalize();
      v28 = v29;
      (((gbVec3D *)&v28))->gbVec3D::Normalize();
      if ( (g_bgbGeomNodeFlag_17AF5C4 & 1) == 0 )
      {
        dword_17AF5B8 = 0;
        g_bgbGeomNodeFlag_17AF5C4 |= 1u;
        dword_17AF5BC = 0;
        dword_17AF5C0 = 1065353216;
        atexit(nullsub_70);
      }
      v24 = acos(v28.z * *(float *)&dword_17AF5C0 + v28.y * *(float *)&dword_17AF5BC + *(float *)&dword_17AF5B8 * v28.x);
      *(float *)(v2 + 3736) = v24;
      if ( v28.x < 0.0f )
        *(float *)(v2 + 3736) = 6.2831855 - v24;
      *(float *)(v2 + 3736) = *(float *)(v2 + 3736) * 57.29578;
      if ( (g_bgbGeomNodeFlag_17AF5C4 & 2) == 0 )
      {
        dword_17AF5A8 = 0;
        g_bgbGeomNodeFlag_17AF5C4 |= 2u;
        dword_17AF5AC = 1065353216;
        dword_17AF5B0 = 0;
        atexit(nullsub_69);
      }
      *(float *)(v2 + 3740) = acos(
                                v28.z * *(float *)&dword_17AF5B0
                              + v28.y * *(float *)&dword_17AF5AC
                              + *(float *)&dword_17AF5A8 * v28.x)
                            * 57.29578;
      (((gbGeomNode *)(v2 + 3336)))->gbGeomNode::GetTotalOBBox((gbOBBox *)(v2 + 3652));
      *(float *)(v2 + 3700) = *(float *)(v2 + 3700) + *(float *)(v2 + 3628);
      *(float *)(v2 + 3704) = *(float *)(v2 + 3704) + *(float *)(v2 + 3632);
      *(float *)(v2 + 3708) = *(float *)(v2 + 3708) + *(float *)(v2 + 3636);
      v25 = *(float *)(v2 + 3760) + 16.0f;
      *(float *)(v2 + 3760) = v25;
      if ( !v27 )
        *(float *)(v2 + 3760) = 360.0 - v25;
      return (*(int ( **)(int))(*(_DWORD *)(v2 + 3336) + 20))(v2 + 3336);
    }
    else
    {
      *(_BYTE *)(v2 + 3744) = 0;
    }
  }
  return result;
}

// 0x00530270
void * ZeroInitPair()
{
  _DWORD *v0; // ecx
  void *result; // eax

  result = (void *)v0;
  v0[1] = 0;
  *v0 = 0;
  return result;
}

// 0x00530570
int UIGameOver_ClearState(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = 0;
  *(_DWORD *)v1 = 0;
  *(_DWORD *)(v1 + 4) = 0;
  *(_DWORD *)(v1 + 576) = 0;
  *(_DWORD *)(v1 + 776) = 0;
  *(_DWORD *)(v1 + 580) = 0;
  *(_DWORD *)(v1 + 780) = 0;
  *(_BYTE *)(v1 + 228) = 0;
  *(_DWORD *)(v1 + 484) = 0;
  return result;
}

// 0x005305A0
int UIGameOver_ResetState(int nVal)
{
  _DWORD *v1; // ecx
  int result; // eax

  result = 0;
  v1[149] = 0;
  v1[150] = 0;
  v1[151] = 0;
  v1[146] = 0;
  v1[147] = (unsigned long)v1[150];
  v1[148] = (unsigned long)v1[151];
  v1[152] = 0;
  v1[153] = 0;
  v1[154] = 0;
  v1[155] = 0;
  v1[156] = (unsigned long)v1[153];
  v1[157] = (unsigned long)v1[154];
  v1[158] = 0;
  v1[159] = 0;
  v1[160] = 0;
  v1[161] = 0;
  v1[162] = 0;
  v1[163] = -1165815185;
  v1[164] = 0;
  v1[165] = 1093517967;
  v1[166] = 1093517967;
  v1[169] = 0;
  v1[181] = 0;
  return result;
}

// 0x00530990
int UIAnimateCtrlEX_SetTextBottom(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 776) = nVal;
  return result;
}

// 0x005309A0
int ResetTransformState(Actor *_this)
{
  int v2; // eax
  int v3; // ecx
  float v4; // edx
  float v5; // st7
  float v6; // st7
  int v7; // eax
  int result; // eax
  int v9; // et2
  int v10; // [esp+0xC] [ebp-0x8]
  float v11; // [esp+0x10] [ebp-0x4]

  v2 = (((ArcSceneMonster *)&_this->m_dwMatMsg[6]))->ArcSceneMonster::CheckDistance(0.0);
  v10 = *(_DWORD *)(v2 + 4);
  v3 = *(_DWORD *)(v2 + 8);
  *(_DWORD *)&_this->m_curact[11] = *(_DWORD *)v2;
  *(_DWORD *)&_this->m_curact[15] = v10;
  *(_DWORD *)&_this->m_curact[19] = v3;
  *(_DWORD *)&_this->m_bChangedMat = *(_DWORD *)&_this->m_curact[11];
  *(_DWORD *)&_this->m_curact[3] = *(_DWORD *)&_this->m_curact[15];
  *(_DWORD *)&_this->m_curact[7] = *(_DWORD *)&_this->m_curact[19];
  *(_DWORD *)&_this->m_curact[23] = 0;
  *(_DWORD *)&_this->m_curact[27] = 0;
  *(_DWORD *)&_this->m_curact[31] = 0;
  *(_DWORD *)&_this->m_curact[35] = 0;
  *(_DWORD *)&_this->m_curact[39] = *(_DWORD *)&_this->m_curact[27];
  _this->_overlap_RoleSystem_m_partyActor_m_nState = *(_DWORD *)&_this->m_curact[31];
  v4 = *(float *)(v2 + 4);
  v11 = *(float *)(v2 + 8);
  _this->m_fDirX = *(float *)v2;
  _this->m_fDirY = v4;
  _this->m_fDirZ = v11;
  _this->m_fNormX = 0.0;
  _this->m_fNormY = 0.0;
  _this->m_fNormZ = -0.001;
  _this->m_fDistAccum = 0.0;
  *((_DWORD *)&_this->m_fSpeed + 2) = 1093517967;
  *((_DWORD *)&_this->m_fSpeed + 3) = 1105649992;
  _this->m_fSpeed = 10.86;
  *((_DWORD *)&_this->m_fSpeed + 1) = 1093517967;
  _this->m_fAngleDeg = 0.0;
  _this->m_InnerActor = 0;
  _this->m_nUpdateMode = 0;
  *(&_this->m_nUpdateMode + 1) = 0;
  SetMaterialName(*(Actor **)&_this->m_actarray_type, (void *)lpString2, 0);
  lstrcpyA((LPSTR)&_this->m_fMatrixC, lpString2);
  v5 = _this->m_fBlendWeight * 0.3333333432674408f;
  *(&_this->m_bDirFlag + 21) = 0;
  *(&_this->m_bDirFlag + 22) = 0;
  _this->m_bDirFlag = 0;
  *((_DWORD *)&_this->m_bDirFlag + 1) = 0;
  *(&_this->m_bDirFlag + 1) = 1;
  *((_BYTE *)&_this->m_nAnimCounter + 46) = 0;
  *((_DWORD *)&_this->m_bDirFlag + 6) = 1145241600;
  *((_DWORD *)&_this->m_bDirFlag + 7) = 1119092736;
  *((_DWORD *)&_this->m_bDirFlag + 8) = -1033895936;
  *((_DWORD *)&_this->m_bDirFlag + 9) = 1104150528;
  v6 = v5 + _this->m_fBlendWeight;
  *(&_this->m_nUpdateMode + 5) = 0;
  *(&_this->m_nUpdateMode + 6) = 1086324736;
  *(&_this->m_nUpdateMode + 7) = 1086324736;
  *(&_this->m_nUpdateMode + 8) = 1022739087;
  *(_DWORD *)&_this[1].m_actarray_type = 0;
  *((float *)&_this->m_nUpdateMode + 4) = v6;
  *((_BYTE *)&_this->m_nUpdateMode + 14) = 1;
  *((_BYTE *)&_this->m_nUpdateMode + 15) = 1;
  *(&_this->m_nUpdateMode + 2) = 1039516303;
  *((_BYTE *)&_this->m_nUpdateMode + 13) = 1;
  *((_BYTE *)&_this->m_nAnimCounter + 44) = 0;
  v7 = rand();
  _this->m_bStateFlag = 0;
  v9 = v7 % 2600;
  result = v7 / 2600;
  *((_BYTE *)&_this->m_nAnimCounter + 45) = 0;
  *(&_this->m_nAnimCounter + 4) = v9;
  return result;
}

// 0x00530BE0
int UIAnimateCtrlEX_SwapBuffer(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = *(_DWORD *)(v1 + 784);
  *(_DWORD *)(v1 + 788) = result;
  *(_DWORD *)(v1 + 784) = nVal;
  return result;
}

// 0x00530C00
bool UpdateAnimState(Actor *_this, char bForce)
{
  unsigned int v3; // ecx
  RoleSystem *v4; // ecx
  bool result; // al

  UIAnimateCtrlEX_SwapBuffer(3);
  SetMaterialName(*(Actor **)&_this->m_actarray_type, (void *)lpString2, 0);
  v3 = _this->m_dwMatMsg[10];
  *((_BYTE *)&_this->m_nAnimCounter + 45) = bForce;
  (((ScreenEffectMgr *)*(ScreenEffectMgr **)(v3 + 1312)))->ScreenEffectMgr::ProcessInstance();
  v4 = (RoleSystem *)_this->m_dwMatMsg[10];
  *(&_this->m_bDirFlag + 21) = 1;
  (((RoleSystem *)v4))->RoleSystem::StopBlinkUI();
  result = bForce == 0;
  *(_BYTE *)(_this->m_dwMatMsg[10] + 4524) = 1;
  *((_BYTE *)&_this->m_nAnimCounter + 46) = bForce == 0;
  return result;
}

// 0x00530C70
int MatrixStack_BeginSceneWithRotation(int nVal)
{
  int v1; // ecx
  gbSceneGraph *pSceneGraph; // ebp
  Actor **v3; // esi
  gbMatrixStack *v4; // edi
  double v5; // st7
  float v6; // ecx
  Actor *v7; // eax
  double v8; // st7
  int result; // eax
  float v10; // [esp+0x34] [ebp-0x94]
  float v11; // [esp+0x34] [ebp-0x94]
  struct gbVec3D v12; // [esp+0x4C] [ebp-0x7C] BYREF
  gbQuaternion v13; // [esp+0x58] [ebp-0x70] BYREF
  gbQuaternion v14; // [esp+0x68] [ebp-0x60] BYREF
  struct gbQuaternion v15; // [esp+0x78] [ebp-0x50] BYREF
  gbMatrix4 v16; // [esp+0x88] [ebp-0x40] BYREF

  pSceneGraph = gfxMgr->pSceneGraph;
  v3 = (Actor **)v1;
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(**(gbCamera ***)(v1 + 576));
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v4 = gfxMgr->pMatrixStack[1];
  (((gbCamera *)*(gbCamera **)&v3[144]->m_actarray_type))->gbCamera::SetAsCurrent(3);
  (((gbMatrixStack *)v4))->gbMatrixStack::Push();
  memset(&v13, 0, 12);
  v13.w = 1.0f;
  memset(&v14, 0, 12);
  v14.w = 1.0f;
  memset(&v15, 0, 12);
  v15.w = 1.0;
  v12.x = 1.0;
  v12.y = 0.0;
  v12.z = 0.0;
  (((gbQuaternion *)&v13))->gbQuaternion::SetAxisAngle(&v12, 45.0);
  v12.x = 0.0;
  v12.y = 1.0;
  v12.z = 0.0;
  (((gbQuaternion *)&v14))->gbQuaternion::SetAxisAngle(&v12, 90.0);
  (((gbQuaternion *)&v14))->gbQuaternion::MultiplyBy(&v13, &v15);
  (((gbQuaternion *)&v15))->gbQuaternion::GetMatrix((gbMatrix4 *)(v3 + 24));
  ((void ( *)(Actor **, _DWORD))v3[2]->m_pact)(v3 + 2, 0);
  if ( v3[196] == (Actor *)2 )
  {
    v12.x = *((float *)v3 + 158);
    v12.y = *((float *)v3 + 205);
    v12.z = *((float *)v3 + 160);
    (((gbMatrixStack *)v4))->gbMatrixStack::Translate(v12);
  }
  else
  {
    (((gbMatrixStack *)v4))->gbMatrixStack::Translate(*(gbVec3D *)(v3 + 158));
  }
  if ( v3[196] == (Actor *)3 )
  {
    v5 = *((float *)v3 + 169) - 90.0;
    v12.x = 0.0;
    v12.y = 1.0;
    v12.z = 0.0;
    v10 = v5;
    (((gbMatrixStack *)v4))->gbMatrixStack::Rotate(v10,  v12);
  }
  else
  {
    v6 = *((float *)v3 + 169);
    v12.x = 0.0;
    v12.y = 1.0;
    v12.z = 0.0;
    (((gbMatrixStack *)v4))->gbMatrixStack::Rotate(v6,  v12);
  }
  v7 = (Actor *)v3[196];
  if ( v7 == (Actor *)1 || v7 == (Actor *)3 )
  {
    v12.x = 0.0;
    v12.y = 0.0;
    v12.z = 1.0;
    (((gbMatrixStack *)v4))->gbMatrixStack::Rotate(0.0,  v12);
  }
  else
  {
    v8 = *((float *)v3 + 170) - 90.0;
    v12.x = 0.0;
    v12.y = 0.0;
    v12.z = 1.0;
    v11 = v8;
    (((gbMatrixStack *)v4))->gbMatrixStack::Rotate(v11,  v12);
  }
  if ( v3[196] != (Actor *)3 )
  {
    (((gbMatrixStack *)v4))->gbMatrixStack::Push();
    (((gbActor *)(*v3)->m_pact))->gbActor::GetTagNodeTM(&v16, "tag_weapon1");
    (((gbMatrixStack *)v4))->gbMatrixStack::MultMatrix(&v16);
    (*(void ( **)(Actor *, _DWORD))(*(_DWORD *)&v3[1]->m_actarray_type + 16))(v3[1], 0);
    (((gbMatrixStack *)v4))->gbMatrixStack::Pop();
  }
  (((Actor *)*v3))->Actor::DispatchAction(0);
  (((gbMatrixStack *)v4))->gbMatrixStack::Pop();
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
  return result;
}

// 0x00530F20
bool IsWithinBoundRadius(Actor *_this)
{
  char *m_pRoleState; // ecx
  gbOBBox *OBBox; // eax
  long double v5; // [esp+0x0] [ebp-0x8]

  m_pRoleState = _this->m_pRoleState;
  v5 = fabs(_this->m_fDistAccum - *((float *)m_pRoleState + 932));
  OBBox = (((MiniGame2Scene *)m_pRoleState))->MiniGame2Scene::GetOBBox();
  return (((gbOBBox *)OBBox))->gbOBBox::GetRadius() > v5;
}

// 0x00530F70
int todo_00530F70(Actor *_this, int a1)
{
  int result; // eax
  float v4; // st7
  double v5; // st7
  float v6; // fps
  bool v7; // c0
  char v8; // c2
  bool v9; // c3
  Actor *v10; // ecx
  double v11; // st7
  __int16 v12; // fps
  bool v13; // c0
  char v14; // c2
  bool v15; // c3
  float v16; // edx

  LOBYTE(result) = *((_BYTE *)&_this->m_nUpdateMode + 13);
  if ( !(_BYTE)result )
  {
    v4 = *(float *)&a1 * *((float *)&_this->m_nUpdateMode + 2);
    if ( *((_BYTE *)&_this->m_nUpdateMode + 12) )
    {
      v5 = _this->m_fSpeed - v4;
      _this->m_fSpeed = v5;
      v7 = v5 < 0.0;
      v8 = 0;
      v9 = v5 == 0.0;
      LOWORD(result) = v6;
      if ( v5 <= 0.0 )
      {
        v10 = (Actor *)(*(Actor **)&_this->m_actarray_type);
        *((_BYTE *)&_this->m_nUpdateMode + 12) = 0;
        SetMaterialName(v10, (void *)off_5F50B4, 0);
        return UIAnimateCtrlEX_SwapBuffer(0);
      }
    }
    else
    {
      v11 = v4 + _this->m_fSpeed;
      _this->m_fSpeed = v11;
      v13 = v11 < *(&_this->m_fSpeed + 2);
      v14 = 0;
      v15 = v11 == *(&_this->m_fSpeed + 2);
      LOWORD(result) = v12;
      if ( v11 >= *(&_this->m_fSpeed + 2) )
      {
        v16 = *(&_this->m_fSpeed + 2);
        *((_BYTE *)&_this->m_nUpdateMode + 12) = 1;
        _this->m_fSpeed = v16;
        *((_BYTE *)&_this->m_nUpdateMode + 13) = 1;
      }
      *((_BYTE *)&_this->m_nUpdateMode + 15) = 1;
    }
  }
  return result;
}

// 0x00531F50
int RoleSystem_InitAllSystems(int nVal)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // esi
  int v4; // eax
  _DWORD *v5; // eax
  _BYTE *v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // edx
  UIPushButton *v10; // edi
  int v11; // eax
  UIPushButton *v12; // edi
  int i; // ebx
  int v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int result; // eax
  int v19; // [esp+0x2C] [ebp-0x60] BYREF
  int v20; // [esp+0x30] [ebp-0x5C]
  int v21; // [esp+0x34] [ebp-0x58]
  int v22; // [esp+0x38] [ebp-0x54]
  int v23; // [esp+0x3C] [ebp-0x50] BYREF
  int v24; // [esp+0x40] [ebp-0x4C]
  int v25; // [esp+0x44] [ebp-0x48]
  int v26; // [esp+0x48] [ebp-0x44]
  _DWORD v27[4]; // [esp+0x4C] [ebp-0x40] BYREF
  _DWORD v28[12]; // [esp+0x5C] [ebp-0x30] BYREF

  v2 = 0;
  v3 = v1;
  *(_DWORD *)(v1 + 76) = 0;
  *(_DWORD *)(v1 + 72) = 0;
  *(_DWORD *)(v1 + 80) = 800;
  *(_DWORD *)(v1 + 84) = 600;
  (((UIListBox *)v1))->UIListBox::SetSelTexture(-1, 0, 0, 800, *(_DWORD *)(v1 + 84));
  v4 = *(_DWORD *)(v3 + 364);
  v28[1] = 200;
  v28[0] = 300;
  v28[2] = 556;
  v28[3] = 328;
  (*(void ( **)(int, int, _DWORD *, int))(v4 + 16))(v3 + 364, 10, (_DWORD *)(v28), v3);
  (((UIScene *)(v3 + 364)))->UIScene::SetShow(1);
  (**(void ( ***)(int, _DWORD))(v3 + 364))((int)(v3 + 364), (_DWORD)(0));
  *(_BYTE *)(v3 + 516) = 0;
  v5 = (_DWORD *)(v3 + 1292);
  v6 = (_BYTE *)(v3 + 524);
  v7 = 3;
  do
  {
    *v6 = 0;
    *v5++ = 0;
    v6 += 256;
    --v7;
  }
  while ( v7 );
  v8 = *(_DWORD *)(v3 + 1316);
  *(_DWORD *)(v3 + 1304) = 0;
  v24 = 0;
  v23 = 681;
  v25 = 800;
  v26 = 92;
  (*(void ( **)(int, int *, int *, int))(v8 + 16))(v3 + 1316, &byte_ABC00B, &v23, v3);
  LOBYTE(v9) = *(_BYTE *)(v3 + 7598);
  (((UIPushButton *)(v3 + 1316)))->UIPushButton::CreateFromTemplate((void *)off_5F7820, v9);
  v10 = (UIPushButton *)(v3 + 1468);
  v19 = v23 + 48;
  v20 = v24 + 16;
  v21 = v23 + 80;
  v22 = v24 + 40;
  do
  {
    (*(void ( **)(UIPushButton *, int *, int *, int))(*(_DWORD *)((UIWnd *)v10) + 16))(
      v10,
      &byte_ABC00C,
      &v19,
      v3);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v10))((UIPushButton *)(v10), (_DWORD)(0));
    v11 = sprintf((char *const)(v3 + 96), "SubGame\\Appraise\\Number\\%d.tga", v2);
    LOBYTE(v11) = *(_BYTE *)(v3 + 7598);
    (((UIPushButton *)v10))->UIPushButton::CreateFromTemplate((void *)(v3 + 96), v11);
    ++v2;
    v10 = (UIPushButton *)((char *)v10 + 152);
  }
  while ( v2 < 10 );
  v12 = (UIPushButton *)(v3 + 2988);
  v20 = v22;
  v22 += 24;
  for ( i = 0; i < 10; ++i )
  {
    (*(void ( **)(UIPushButton *, int *, int *, int))(*(_DWORD *)((UIWnd *)v12) + 16))(
      v12,
      &byte_ABC00D,
      &v19,
      v3);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v12))((UIPushButton *)(v12), (_DWORD)(0));
    v14 = sprintf((char *const)(v3 + 96), "SubGame\\Appraise\\Number\\%d.tga", i);
    LOBYTE(v14) = *(_BYTE *)(v3 + 7598);
    (((UIPushButton *)v12))->UIPushButton::CreateFromTemplate((void *)(v3 + 96), v14);
    v12 = (UIPushButton *)((char *)v12 + 152);
  }
  v15 = *(_DWORD *)(v3 + 7280);
  *(_BYTE *)(v3 + 7277) = 0;
  v27[1] = 200;
  v27[0] = 644;
  v27[2] = 700;
  v27[3] = 264;
  (*(void ( **)(int, int *, _DWORD *, int))(v15 + 16))(v3 + 7280, &byte_AABC03, (_DWORD *)(v27), v3);
  LOBYTE(v16) = *(_BYTE *)(v3 + 7598);
  (((UIPushButton *)(v3 + 7280)))->UIPushButton::CreateFromTemplate((void *)off_5F7824, v16);
  (**(void ( ***)(int, _DWORD))(v3 + 7280))((int)(v3 + 7280), (_DWORD)(0));
  (*(void ( **)(int, int *, _DWORD *, int))(*(_DWORD *)(v3 + 7432) + 16))(v3 + 7432, &dword_AABC04, (_DWORD *)(v27), v3);
  LOBYTE(v17) = *(_BYTE *)(v3 + 7598);
  (((UIPushButton *)(v3 + 7432)))->UIPushButton::CreateFromTemplate((void *)off_5F7828, v17);
  (**(void ( ***)(int, _DWORD))(v3 + 7432))((int)(v3 + 7432), (_DWORD)(0));
  v28[5] = 221;
  v28[4] = 320;
  v28[6] = 480;
  v28[7] = 411;
  Create__ovl_1((ARC_PlayerAtt *)(v3 + 4540));
  (((UIItem *)(v3 + 4540)))->UIItem::SetData(31);
  v28[9] = 260;
  v28[8] = 186;
  v28[10] = 614;
  v28[11] = 388;
  Create__ovl_1((ARC_PlayerAtt *)(v3 + 5908));
  (((UIItem *)(v3 + 5908)))->UIItem::SetData(31);
  sprintf(
    (char *const)(v3 + 96),
    "%s\\n%s\\n%s\\n%s",
    (const char *)&dword_DD313C,
    (const char *)&dword_DD323C,
    (const char *)&dword_DD333C,
    (const char *)&dword_DD343C);
  SetEnable((UICaption *)(v3 + 6364));
  result = (((UIRoleSelect *)(v3 + 5908)))->UIRoleSelect::SetByte(1);
  *(_BYTE *)(v3 + 7276) = 0;
  *(_DWORD *)(v3 + 4512) = 59;
  *(_BYTE *)(v3 + 4524) = 0;
  *(_DWORD *)(v3 + 1308) = 0;
  return result;
}

// 0x005322D0
int RoleAtt_SetPageParam(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 1308) = nVal;
  return result;
}

// 0x005322E0
int RoleAtt_SetPageParam2(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  *(_DWORD *)(v1 + 1312) = nVal;
  return result;
}

// 0x00532B40
int UITabCtrl_Render(int nVal)
{
  UICursor *v1; // ecx
  UICursor *v2; // esi
  int result; // eax
  UIScene *v4; // ecx
  int RolePtr; // edi
  float v6; // st7

  v2 = (UICursor *)v1;
  (((UICursor *)v1))->UICursor::_todo_541CC0();
  LOBYTE(result) = BYTE1(v2[2].m_dwID[1]);
  if ( (_BYTE)result )
  {
    BYTE1(v2[2].m_dwID[1]) = 1;
    *(_DWORD *)&v2[1].m_bShow = 1074832343;
    v2->m_active = 0;
    v2->m_tex[0] = 0;
    v2->m_tex[1] = (gbTexture *)1074832343;
    *(_DWORD *)(&v2[1].m_bSoftMode + 3) = *(_DWORD *)&v2[1].m_bShow;
    *(_DWORD *)(&v2[1].m_bSoftMode + 7) = 1016296636;
    v2->m_tex[2] = 0;
    *(_DWORD *)&v2->m_bShow = 0;
    *(_DWORD *)(&v2->m_bSoftMode + 3) = 1065353216;
    *(_DWORD *)(&v2->m_bSoftMode + 7) = -1027567780;
    *(_DWORD *)(&v2->m_bSoftMode + 11) = 0;
    v2->m_pData = -982398730;
    *(_DWORD *)(&v2->m_bSoftMode + 7) = 1117782016;
    *(_DWORD *)(&v2->m_bSoftMode + 11) = 0;
    v2->m_pData = 1141112832;
    *(&v2->m_pData + 1) = *(_DWORD *)(&v2->m_bSoftMode + 7);
    *(&v2->m_pData + 2) = *(_DWORD *)(&v2->m_bSoftMode + 11);
    *(&v2->m_pData + 3) = v2->m_pData;
    v4 = (UIScene *)v2->m_dwID[0];
    *((_BYTE *)&v2->m_pData + 16) = 0;
    v2[1].m_tex[0] = (gbTexture *)1030590824;
    v2[1].m_dwID[2] = 1114112000;
    v2[1].m_dwID[0] = 1078774989;
    v2[1].m_dwID[1] = 1020591604;
    *(&v2[1].m_bSoftMode + 11) = 1;
    *(&v2[1].m_bSoftMode + 12) = 1;
    *((_BYTE *)&v2[1].m_pData + 4) = 0;
    *((_BYTE *)&v2[1].m_pData + 5) = 0;
    v2[2].m_dwID[0] = 0;
    v2[2].m_dwID[2] = 0;
    (((UIScene *)v4))->UIScene::ResetCameraOffset();
    (((UIScene *)v2->m_dwID[0]))->UIScene::ResetCameraOffset();
    RolePtr = (((RoleSystem *)*(RoleSystem **)v2->m_dwID[1]))->RoleSystem::GetRolePtr(0);
    v2->m_dwID[2] = RolePtr;
    v6 = (((Scene *)*(_DWORD *)v2->m_dwID[1]))->Scene::GetTileHeight(0, (__int64)((*(float *)(&v2->m_bSoftMode + 7) - *(float *)(RolePtr + 128)) / g_fSceneScale), (__int64)((*(float *)&v2->m_pData - *(float *)(RolePtr + 136)) / g_fSceneScale), 0)
       + *(float *)&v2[1].m_dwID[2];
    BYTE2(v2[2].m_dwID[1]) = 0;
    HIBYTE(v2[2].m_dwID[1]) = 0;
    v2[2].m_active = 0;
    *(float *)(&v2->m_bSoftMode + 11) = v6;
    *(float *)&v2[1].m_active = v6;
    *(float *)&v2[1].m_pData = v6;
  }
  return result;
}

// 0x00532CF0
long double CalcAngleBetweenVectors(int nX1, int nY1, int nZ1, int nX2, float fY2, float fZ2)
{
  (((gbVec3D *)&nX1))->gbVec3D::Normalize();
  (((gbVec3D *)&nX2))->gbVec3D::Normalize();
  return acos(fZ2 * *(float *)&nZ1 + fY2 * *(float *)&nY1 + *(float *)&nX2 * *(float *)&nX1) * 57.295776;
}

// 0x00532D30
int GetStateMode(RoleSystem *_this)
{
  int result; // eax

  result = *(_DWORD *)&_this->m_nStateMode;
  _this->m_rect.right = result;
  return result;
}

// 0x00532D50
void ClearStateMode(RoleSystem *_this)
{
  _this->m_rect.right = 0;
}

// 0x00532E10
void ResetPathState(RoleSystem *_this)
{
  float v2; // [esp+0x4] [ebp+0x4]
  float v3; // [esp+0xC] [ebp+0xC]
  float v4; // [esp+0x10] [ebp+0x10]
  float v5; // [esp+0x18] [ebp+0x18]
  float v6; // [esp+0x1C] [ebp+0x1C]
  float v7; // [esp+0x24] [ebp+0x24]
  float v8; // [esp+0x28] [ebp+0x28]
  float v9; // [esp+0x30] [ebp+0x30]

  if ( (((RoleSystem *)*(RoleSystem **)_this->m_fontcolor.Color))->RoleSystem::IsRoleInRange(0, (int *)(__int64)((v2 - *(float *)(_this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v3 - *(float *)(_this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
  {
    if ( (((RoleSystem *)*(RoleSystem **)_this->m_fontcolor.Color))->RoleSystem::IsRoleInRange(0, (int *)(__int64)((v4 - *(float *)(_this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v5 - *(float *)(_this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
    {
      if ( (((RoleSystem *)*(RoleSystem **)_this->m_fontcolor.Color))->RoleSystem::IsRoleInRange(0, (int *)(__int64)((v6 - *(float *)(_this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v7 - *(float *)(_this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
      {
        if ( !(((RoleSystem *)*(RoleSystem **)_this->m_fontcolor.Color))->RoleSystem::IsRoleInRange(0, (int *)(__int64)((v8 - *(float *)(_this->m_wndcolor.Color + 128)) / g_fSceneScale), (__int64)((v9 - *(float *)(_this->m_wndcolor.Color + 136)) / g_fSceneScale)) )
          LOBYTE(_this->m_nPathState) = 0;
      }
      else
      {
        LOBYTE(_this->m_nPathState) = 1;
      }
    }
    else
    {
      LOBYTE(_this->m_nPathState) = 1;
    }
  }
  else
  {
    LOBYTE(_this->m_nPathState) = 0;
  }
}

// 0x00533DB0
void ResetNameField(RoleAtt *_this)
{
  *(_DWORD *)_this->ImageID = 1036831949;
  *(_DWORD *)&_this->ModelID[26] = 1036831949;
  *(_DWORD *)&_this->ImageID[4] = 1036831949;
  *(_DWORD *)&_this->ImageID[8] = 1133903872;
  *(_DWORD *)&_this->ImageID[12] = 1120403456;
  *(_DWORD *)&_this->ImageID[16] = 0;
  *(_DWORD *)&_this->ImageID[20] = 0;
  *(_DWORD *)&_this->ImageID[24] = 0;
  *(_DWORD *)&_this->ImageID[28] = 0;
  _this->att[0] = -1018691584;
  _this->att[1] = 0;
  *(_DWORD *)&_this->fightstate[8] = 1065353216;
  _this->fightstate[16] = 0;
  _this->fightstate[17] = 0;
  _this->RoundNum = 0.0;
  *(_DWORD *)&_this->fightstate[28] = 0;
  *(_DWORD *)&_this->fightstate[24] = 0;
  *(_DWORD *)&_this->fightstate[20] = 0;
  *(&_this->SAID + 3) = 0;
  *(&_this->SAID + 2) = 0;
  *(&_this->SAID + 1) = 0;
  _this->SAID = 0;
  _this->Escape = 1.0;
  _this->exp = 0.0;
  *(_DWORD *)&_this->haogan[4] = 0;
  *(_DWORD *)&_this->haogan[2] = 0;
  *(_DWORD *)_this->haogan = 0;
  _this->name[12] = 0;
  *(_DWORD *)&_this->name[16] = 1101004800;
  _this->lv = 0.5;
  *(_DWORD *)&_this->name[24] = 0;
  *(_DWORD *)&_this->name[20] = 0;
  *(_DWORD *)&_this->name[28] = 0;
}

// 0x005353A0
int MiniGame3Update(float fVal)
{
  ArcSceneObject **v1; // ecx
  ArcSceneObject **v2; // esi
  DWORD TickCount; // eax
  DWORD v4; // eax
  unsigned int v5; // edx
  int result; // eax
  char v7; // al
  unsigned int p_active; // ecx
  unsigned int v9; // edx
  ArcSceneObject *v10; // ecx
  ArcSceneObject *v11; // edx
  double v12; // st7
  gbVec3D v13; // [esp-0x10] [ebp-0x2C]
  double fDelta; // [esp+0x0] [ebp-0x1C]
  float v15; // [esp+0x8] [ebp-0x14]

  v2 = (ArcSceneObject **)v1;
  (((ArcSceneObject *)v1[3]))->ArcSceneObject::UpdateOscillation((*v1)->info.path.pt[4].x);
  (((RoleAtt *)v2[3]))->RoleAtt::SetPositionFromInts(LODWORD((*v2)->info.path.pt[2].x), LODWORD((*v2)->info.path.pt[2].y), LODWORD((*v2)->info.path.pt[2].z));
  v13.x = 0.0f;
  *(_QWORD *)&v13.y = 0xBF80000000000000ui64;
  (((RoleAtt *)v2[3]))->RoleAtt::UpdateDirectionalMotion(v13, 260.0, 168.0);
  if ( LOBYTE((*v2)->info.path.pt[6].x) )
    *((_BYTE *)v2 + 36) = 1;
  else
    *((_BYTE *)v2 + 37) = 1;
  if ( *((_BYTE *)v2 + 36) && *((_BYTE *)v2 + 37) )
  {
    (((RoleAtt *)v2[3]))->RoleAtt::SetFightState(1086324736, 1086324736, 1086324736, 1091567616, 1070386381, 1, 0);
    if ( !*((_BYTE *)v2 + 32) )
    {
      TickCount = GetTickCount();
      v2[6] = (ArcSceneObject *)TickCount;
      v2[7] = (ArcSceneObject *)TickCount;
      *((_BYTE *)v2 + 32) = 1;
    }
    v4 = GetTickCount();
    v5 = v4 - (_DWORD)v2[7];
    v2[6] = (ArcSceneObject *)v4;
    if ( v5 > 0x3E8 )
    {
      v2[7] = (ArcSceneObject *)v4;
      *((_BYTE *)v2 + 32) = 0;
      (((RoleAtt *)v2[3]))->RoleAtt::ResetFightState();
      *((_BYTE *)v2 + 36) = 0;
      *((_BYTE *)v2 + 37) = 0;
    }
  }
  if ( *((_BYTE *)v2 + 61) )
  {
    result = LODWORD(fVal);
  }
  else
  {
    if ( *((_BYTE *)v2 + 60) )
      *((_BYTE *)v2 + 60) = 0;
    *((float *)((ObjectInfoBase *)&v2[11]->info) + (_DWORD)v2[13]) = fVal;
    v7 = *((_BYTE *)v2 + 62);
    p_active = (unsigned int)&v2[13]->info.active;
    v2[13] = (ArcSceneObject *)p_active;
    v9 = p_active;
    if ( !v7 )
      *((_BYTE *)v2 + 62) = p_active >= (unsigned int)v2[10];
    v10 = (ArcSceneObject *)v2[10];
    result = v9 < (unsigned int)v10 ? v9 : 0;
    v2[13] = (ArcSceneObject *)result;
    v2[12] = 0;
    if ( v10 )
    {
      result = (int)v2[11];
      v11 = (ArcSceneObject *)v10;
      do
      {
        v12 = *((float *)v2 + 12) + *(float *)result;
        result += 4;
        v11 = (ArcSceneObject *)((char *)v11 - 1);
        *((float *)v2 + 12) = v12;
      }
      while ( v11 );
    }
    fVal = *((float *)v2 + 12) / (float)(unsigned int)v10;
  }
  LOBYTE(result) = *((_BYTE *)v2 + 62);
  if ( (_BYTE)result )
  {
    *(float *)&fDelta = fVal;
    (((CScreenMode *)v2[4]))->CScreenMode::LoadScreenScene(fDelta, v15);
    (((ExternalStatistics *)v2[2]))->ExternalStatistics::UpdateFromRole(COERCE_UNSIGNED_INT64(fVal), HIDWORD(COERCE_UNSIGNED_INT64(fVal)));
    SetParam((Actor *)*v2, fVal);
    nearby_5359B0(fVal);
    (((RoleCamera *)v2[3]))->RoleCamera::UpdateAudioListener(COERCE_UNSIGNED_INT64(fVal), HIDWORD(COERCE_UNSIGNED_INT64(fVal)));
  }
  return result;
}

// 0x00535630
int UISceneFrm_ShowAndRelease(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int ( ***v3)(_DWORD, int); // ecx
  int result; // eax

  v2 = v1;
  v3 = *(int ( ****)(_DWORD, int))(v1 + 3216);
  if ( v3 )
  {
    result = (**v3)((_DWORD)((_DWORD)(v3)), (int)(1));
    *(_DWORD *)(v2 + 3216) = 0;
  }
  return result;
}

// 0x00535930
void LoadOverlayTexture(UISceneFrm *_this)
{
  char *v2; // eax
  double v3; // [esp-0x8] [ebp-0x10]
  char *v4; // [esp+0x0] [ebp-0x8]
  char *v5; // [esp+0x4] [ebp-0x4]
  int v6; // [esp+0xC] [ebp+0x4]

  if ( v6 < 6 )
  {
    v2 = (char *)_this + 512 * v6;
    HIDWORD(v3) = (unsigned long)(v2 + 268);
    LODWORD(v3) = (unsigned long)(v2 + 12);
    (((PalScript *)_this))->PalScript::LoadVisNode(v3, v4, v5);
    _this->m_wndcolor.Color = v6;
  }
}

// 0x00535E50
int UISceneMap_SetFieldIfValid(int nVal)
{
  int v1; // ecx
  int result; // eax

  result = nVal;
  if ( nVal )
    *(_DWORD *)(v1 + 224) = nVal;
  return result;
}

// 0x00535FD0
int ArcLocaleRole_TransformPoint(int nVal)
{
  float *v1; // ecx
  float v2; // st7
  float v3; // st7
  float v4; // st7
  float v5; // st7
  int result; // eax
  float v7; // [esp+0xC] [ebp-0x14]
  float v8; // [esp+0xC] [ebp-0x14]
  float v9; // [esp+0xC] [ebp-0x14]
  float v10; // [esp+0xC] [ebp-0x14]
  float v11; // [esp+0x10] [ebp-0x10]
  float v12; // [esp+0x10] [ebp-0x10]
  float v13; // [esp+0x10] [ebp-0x10]
  float v14; // [esp+0x10] [ebp-0x10]
  float v15; // [esp+0x18] [ebp-0x8]
  float v16; // [esp+0x18] [ebp-0x8]
  float v17; // [esp+0x18] [ebp-0x8]
  float v18; // [esp+0x18] [ebp-0x8]
  float v19; // [esp+0x1C] [ebp-0x4]
  float v20; // [esp+0x1C] [ebp-0x4]
  float v21; // [esp+0x1C] [ebp-0x4]
  float v22; // [esp+0x1C] [ebp-0x4]
  float v23; // [esp+0x28] [ebp+0x8]
  float v24; // [esp+0x2C] [ebp+0xC]
  float v25; // [esp+0x30] [ebp+0x10]

  v7 = v1[20] * -0.5f;
  v11 = v1[21] * -0.5f;
  v2 = v1[19] * -0.5f + v23;
  v15 = v24 + v7;
  v1[23] = v15;
  v19 = v25 + v11;
  v1[22] = v2;
  v1[24] = v19;
  v16 = v1[20] * -0.5f;
  v20 = v1[21] * -0.5f;
  v3 = v1[19] * 0.5f + v23;
  v8 = v16 + v24;
  v1[26] = v8;
  v12 = v20 + v25;
  v1[25] = v3;
  v1[27] = v12;
  v17 = v1[20] * -0.5f;
  v21 = v1[21] * 0.5f;
  v4 = v1[19] * 0.5f + v23;
  v9 = v17 + v24;
  v1[29] = v9;
  v13 = v21 + v25;
  v1[28] = v4;
  v1[30] = v13;
  v18 = v1[20] * -0.5f;
  v22 = v1[21] * 0.5f;
  v5 = v1[19] * -0.5f + v23;
  v10 = v18 + v24;
  v1[32] = v10;
  v14 = v22 + v25;
  v1[31] = v5;
  v1[33] = v14;
  result = nVal;
  qmemcpy((void *)nVal, v1 + 22, 0x44u);
  return result;
}

// 0x00536160
double SetParam(Actor *_this, double fVal)
{
  int v3; // eax
  Actor *m_actarray_begin; // ecx
  Actor *m_actarray_end; // ecx
  double result; // st7
  int nVal[17]; // [esp+0x4] [ebp-0x44] BYREF

  if ( _this->m_fScale )
  {
    v3 = rand();
    Actor_SetActorAction(-83 - v3 % 34);
    _this->m_bParamFlag = 1;
  }
  (((gbGeomNode *)*(gbGeomNode **)&_this->m_actarray_type))->gbGeomNode::GetTotalOBBox((gbOBBox *)&_this->m_actarray_capacity_end);
  ArcLocaleRole_TransformPoint((int)nVal);
  (*(void ( **)(_DWORD))(**(_DWORD **)&_this->m_actarray_type + 20))(*(_DWORD *)&_this->m_actarray_type);
  m_actarray_begin = _this->m_actarray_begin;
  if ( m_actarray_begin )
    (*(void ( **)(Actor *))(*(_DWORD *)&m_actarray_begin->m_actarray_type + 20))(m_actarray_begin);
  m_actarray_end = _this->m_actarray_end;
  if ( m_actarray_end )
    (*(void ( **)(Actor *))(*(_DWORD *)&m_actarray_end->m_actarray_type + 20))(m_actarray_end);
  return result;
}

// 0x005363A0
int ResetDefaultState(Actor *_this)
{
  int result; // eax

  result = 0;
  _this->m_nActionState = 0;
  _this->m_nActionType = 0;
  _this->m_bActionFlag1 = 0;
  return result;
}

// 0x005363E0
int Actor_SetActorAction(int nVal)
{
  int result; // eax
  int v2; // ecx
  int v3; // esi
  int v4; // eax
  float fValue; // [esp+0x8] [ebp-0xC]
  float fValuea; // [esp+0x8] [ebp-0xC]

  v3 = v2;
  LOBYTE(result) = *(_BYTE *)(v2 + 344);
  if ( (_BYTE)result )
  {
    result = *(_DWORD *)(v2 + 348);
    if ( result )
    {
      v4 = nVal + result;
      *(_BYTE *)(v2 + 344) = 0;
      *(_DWORD *)(v2 + 348) = v4;
      if ( v4 <= 0 )
      {
        (**(void ( ***)(int, _DWORD))(v2 + 3096))((int)(v2 + 3096), (_DWORD)(0));
        (**(void ( ***)(int, _DWORD))(v3 + 3340))((int)(v3 + 3340), (_DWORD)(0));
        sprintf(
          (char *const)(v3 + 72),
          "       %s\\n       %s",
          (const char *)&dword_DD893C,
          (const char *)&dword_DD8B3C);
        SetEnable((UICaption *)(v3 + 816));
        (((UIRoleSelect *)(v3 + 360)))->UIRoleSelect::SetByte(1);
        *(_DWORD *)(v3 + 348) = 0;
      }
      fValue = (float)*(int *)(v3 + 352);
      (((UIScrollBar *)(v3 + 3096)))->UIScrollBar::SetRange(fValue);
      fValuea = (float)*(int *)(v3 + 348);
      (((UIProgressBar *)(v3 + 3096)))->UIProgressBar::FindChildByName(fValuea);
      *(_BYTE *)(v3 + 332) = 1;
    }
  }
  return result;
}

// 0x005364B0
int Actor_InitActorComponents(int nVal)
{
  int v1; // ecx
  int v2; // esi
  int v3; // eax
  void ( **v4)(int, bool); // edx
  float fValue; // [esp+0x0] [ebp-0xC]
  float fValuea; // [esp+0x0] [ebp-0xC]

  v2 = v1;
  *(_BYTE *)(v1 + 345) = 0;
  SetEnable((UICaption *)(v1 + 2184));
  (((UIRoleSelect *)(v2 + 1728)))->UIRoleSelect::SetByte(1);
  *(_DWORD *)(v2 + 348) = 1000;
  *(_DWORD *)(v2 + 352) = 1000;
  (((UIListBox *)(v2 + 3096)))->UIListBox::GetCurSel();
  fValue = (float)*(int *)(v2 + 352);
  (((UIScrollBar *)(v2 + 3096)))->UIScrollBar::SetRange(fValue);
  fValuea = (float)*(int *)(v2 + 348);
  (((UIProgressBar *)(v2 + 3096)))->UIProgressBar::FindChildByName(fValuea);
  v3 = *(_DWORD *)(v2 + 348);
  v4 = *(void ( ***)(int, bool))(v2 + 3096);
  *(_BYTE *)(v2 + 356) = v3 <= 0;
  (*v4)(v2 + 3096, v3 > 0);
  return (**(int ( ***)(int, bool))(v2 + 3340))((int)(v2 + 3340), (bool)(*(_DWORD *)(v2 + 348) > 0));
}

// 0x00536560
int Actor_ProcessActorFrame(int nVal)
{
  UIListBox *v1; // ecx
  UIListBox *v2; // esi
  _PlugInfo *v3; // eax
  int m_needscriptdel; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int width; // ecx
  int v11; // edx
  int v12; // ecx
  int result; // eax
  float fValue; // [esp+0xC] [ebp-0x58]
  float fValuea; // [esp+0xC] [ebp-0x58]
  int v16; // [esp+0x24] [ebp-0x40] BYREF
  int v17; // [esp+0x28] [ebp-0x3C]
  int v18; // [esp+0x2C] [ebp-0x38]
  int v19; // [esp+0x30] [ebp-0x34]
  _DWORD v20[12]; // [esp+0x34] [ebp-0x30] BYREF

  v2 = (UIListBox *)v1;
  (((UIListBox *)v1))->UIListBox::SetSelTexture(-1, 0, 0, 800, 600);
  v3 = (_PlugInfo *)operator new(0xCu);
  if ( v3 )
  {
    v3->name[4] = 0;
    *(_DWORD *)v3->name = 0;
    v3->filepos = 0;
  }
  else
  {
    v3 = 0;
  }
  v2->m_scrollbar.m_texarrayInfo[0] = v3;
  v2->m_scrollbar.m_texarrayInfo[2] = (_PlugInfo *)1000;
  v2->m_scrollbar.m_texarrayInfo[3] = (_PlugInfo *)1000;
  m_needscriptdel = v2[2].m_column[2].items.m_needscriptdel;
  BYTE2(v2->m_scrollbar.m_texarray.m_num) = -58;
  BYTE1(v2->m_scrollbar.m_texarray.m_num) = 116;
  LOBYTE(v2->m_scrollbar.m_texarray.m_num) = 36;
  v17 = 310;
  v16 = 350;
  v18 = 440;
  v19 = 322;
  (*(void ( **)(int *, int, int *, UIListBox *))(m_needscriptdel + 16))(
    &v2[2].m_column[2].items.m_needscriptdel,
    -5570049,
    &v16,
    v2);
  (((UIScene *)&v2[2].m_column[2].items.m_needscriptdel))->UIScene::GetChildCount();
  (((UIScene *)&v2[2].m_column[2].items.m_needscriptdel))->UIScene::GetChildAt();
  sub_43FD90((float *)&v2[2].m_column[2].items.m_needscriptdel, 2);
  (((UIProgressBar *)&v2[2].m_column[2].items.m_needscriptdel))->UIProgressBar::GetWidth(2);
  sub_43FDB0((float *)&v2[2].m_column[2].items.m_needscriptdel, 2);
  (((UIProgressBar *)&v2[2].m_column[2].items.m_needscriptdel))->UIProgressBar::GetHeight(2);
  (((UIProgressBar *)&v2[2].m_column[2].items.m_needscriptdel))->UIProgressBar::GetPosition(1);
  *(_DWORD *)&v2[2].m_column[5].head[36] = 1;
  fValue = (float)(int)v2->m_scrollbar.m_texarrayInfo[3];
  (((UIScrollBar *)&v2[2].m_column[2].items.m_needscriptdel))->UIScrollBar::SetRange(fValue);
  fValuea = (float)(int)v2->m_scrollbar.m_texarrayInfo[2];
  (((UIProgressBar *)&v2[2].m_column[2].items.m_needscriptdel))->UIProgressBar::FindChildByName(fValuea);
  v5 = v18;
  v20[0] = v16;
  v6 = v17;
  v2[2].m_column[5].items.m_pData = (char *)400;
  v20[1] = v6 - 26;
  v20[2] = v5;
  *(_DWORD *)&v2[2].m_column[5].head[56] = 1101004800;
  *(_DWORD *)&v2[2].m_column[5].head[44] = 255;
  v20[3] = v6 - 26 + 32;
  (*(void ( **)(int *, int, _DWORD *, UIListBox *))(v2[2].m_column[5].items.capacity + 16))(
    &v2[2].m_column[5].items.capacity,
    -5570049,
    (_DWORD *)(v20),
    v2);
  (((UIScene *)&v2[2].m_column[5].items.capacity))->UIScene::SetShow(0);
  AllocObject(&v2[2].m_column[5].items.capacity);
  v20[5] = 250;
  v20[4] = 300;
  v20[6] = 500;
  v20[7] = 370;
  Create__ovl_1((ARC_PlayerAtt *)&v2->m_scrollbar.m_texarrayInfo[5]);
  v7 = *(_DWORD *)&v2->m_column[0].head[8] + 22;
  *(_DWORD *)&v2->m_column[0].head[20] = *(_DWORD *)&v2->m_column[0].head[4] + 6;
  v8 = *(_DWORD *)&v2->m_column[0].head[16];
  *(_DWORD *)&v2->m_column[0].head[24] = v7;
  v9 = *(_DWORD *)&v2->m_column[0].head[12] - 6;
  *(_DWORD *)&v2->m_column[0].head[32] = v8 - 38;
  *(_DWORD *)&v2[1].m_column[0].head[60] = 0;
  v2[1].m_column[0].items.m_pData = (char *)16;
  *(_DWORD *)&v2->m_column[0].head[28] = v9;
  (((UIWnd *)&v2->m_column[4].head[44]))->UIWnd::sub_445FA0(&v2->m_column[0].head[20]);
  (((UIItem *)&v2->m_scrollbar.m_texarrayInfo[5]))->UIItem::SetData(31);
  LOBYTE(v2->m_scrollbar.m_texarrayInfo[4]) = 0;
  LOBYTE(v2->m_scrollbar.m_texarrayInfo[1]) = 1;
  BYTE1(v2->m_scrollbar.m_texarrayInfo[1]) = 0;
  v20[9] = 200;
  v20[8] = 250;
  v20[10] = 550;
  v20[11] = 328;
  Create__ovl_1((ARC_PlayerAtt *)&v2[1].m_column[1]);
  (((UIItem *)&v2[1].m_column[1]))->UIItem::SetData(31);
  width = v2[1].m_column[1].width;
  v11 = *(_DWORD *)&v2[1].m_column[2].head[4];
  *(_DWORD *)&v2[1].m_column[2].head[16] = *(_DWORD *)v2[1].m_column[2].head + 26;
  *(_DWORD *)&v2[1].m_column[2].head[12] = width + 6;
  v12 = *(_DWORD *)&v2[1].m_column[2].head[8] - 38;
  *(_DWORD *)&v2[2].m_column[2].head[52] = 0;
  *(_DWORD *)&v2[2].m_column[2].head[56] = 20;
  *(_DWORD *)&v2[1].m_column[2].head[20] = v11 - 6;
  *(_DWORD *)&v2[1].m_column[2].head[24] = v12;
  (((UIWnd *)((char *)v2 + 2184)))->UIWnd::sub_445FA0(&v2[1].m_column[2].head[12]);
  SetEnable((UICaption *)&v2[1].m_column[6].head[36]);
  result = (((UIRoleSelect *)&v2[1].m_column[1]))->UIRoleSelect::SetByte(1);
  return 1;
}

// 0x005368A0
int SceneObj_HandleEvent(int nVal)
{
  int v1; // ecx
  int v2; // edi
  int v3; // esi
  int v5; // edi
  DWORD TickCount; // eax
  DWORD v7; // eax
  unsigned int v8; // edx
  char v9; // al
  char v10; // al
  char v11; // al
  int v12; // [esp-0x8] [ebp-0x14]
  int v13; // [esp+0x0] [ebp-0xC]
  int a3; // [esp+0x18] [ebp+0xC]

  v3 = v1;
  if ( *(_BYTE *)(v1 + 356) )
    return (((SceneObj *)v1))->SceneObj::Update(nVal, a3);
  if ( !*(_BYTE *)(v1 + 345) && UIParabolaCtrl_GetState(v13) == 2 )
    *(_BYTE *)(v3 + 345) = 1;
  v12 = v2;
  sprintf((char *const)(v3 + 72), "%d/%d", (int)*(float *)(v3 + 3252), *(_DWORD *)(v3 + 352));
  SetEnable((UICaption *)(v3 + 3340));
  if ( *(_BYTE *)(v3 + 332) )
  {
    v5 = *(_DWORD *)(v3 + 340);
    if ( !*(_BYTE *)(v5 + 8) )
    {
      TickCount = GetTickCount();
      *(_DWORD *)v5 = TickCount;
      *(_DWORD *)(v5 + 4) = TickCount;
      *(_BYTE *)(v5 + 8) = 1;
    }
    v7 = GetTickCount();
    v8 = v7 - *(_DWORD *)(v5 + 4);
    *(_DWORD *)v5 = v7;
    if ( v8 <= 0x7D0 )
    {
      v9 = *(_BYTE *)(v3 + 333);
      *(_BYTE *)(v3 + 344) = 0;
      if ( v9 )
      {
        v10 = *(_BYTE *)(v3 + 339) + 20;
        *(_BYTE *)(v3 + 339) = v10;
        if ( v10 == -1 )
        {
          *(_BYTE *)(v3 + 339) = -1;
          *(_BYTE *)(v3 + 333) = 0;
        }
      }
      else
      {
        v11 = *(_BYTE *)(v3 + 339);
        *(_BYTE *)(v3 + 339) = v11 - 20;
        if ( v11 == 20 )
        {
          *(_BYTE *)(v3 + 339) = 0;
          *(_BYTE *)(v3 + 333) = 1;
        }
      }
    }
    else
    {
      *(_DWORD *)(v5 + 4) = v7;
      *(_BYTE *)(v5 + 8) = 0;
      *(_BYTE *)(v3 + 332) = 0;
      *(_BYTE *)(v3 + 344) = 1;
      *(_BYTE *)(v3 + 339) = -1;
    }
  }
  *(_BYTE *)(v3 + 356) = UIParabolaCtrl_GetState(v12) == 2;
  return (((SceneObj *)v3))->SceneObj::Update(nVal, a3);
}

// 0x00536A80
void FastInit(Actor *_this)
{
  _this->m_actarray_type = HIBYTE(_this);
  _this->m_actarray_begin = 0;
  _this->m_actarray_end = 0;
  _this->m_actarray_capacity_end = 0;
  _this->m_dwMatMsg[0] = 0;
  _this->m_dwMatMsg[1] = 0;
  memset(_this->m_name, 0, 0x104u);
  memset(_this->m_szTexture, 0, 0x104u);
}

// 0x00536AC0
int SetMaterialName(Actor *_this, void *pszName, int nFlag)
{
  unsigned int *m_dwMatMsg; // ebx
  char *v6; // edi
  unsigned int v7; // kr04_4
  Actor *m_actarray_begin; // eax
  unsigned int v9; // esi
  int v10; // edi
  Actor *v11; // eax
  int v12; // eax
  int v13; // eax
  gbActor *v14; // ecx
  char *m_szTexture; // esi
  gbActor *v16; // ebp
  gbActor *m_pact; // [esp-0x4] [ebp-0x30]
  struct gbNodeMsgObj v18; // [esp+0x10] [ebp-0x1C] BYREF
  int v19; // [esp+0x28] [ebp-0x4]

  m_dwMatMsg = _this->m_dwMatMsg;
  if ( !strcmp((const char *)pszName, (const char *)_this->m_dwMatMsg) )
    return 1;
  v7 = strlen((const char *)pszName) + 1;
  v6 = (char *)pszName + v7;
  qmemcpy(m_dwMatMsg, pszName, 4 * (v7 >> 2));
  qmemcpy(&m_dwMatMsg[v7 >> 2], &v6[4 * (v7 >> 2) - v7], v7 & 3);
  _strlwr((char *)m_dwMatMsg);
  m_actarray_begin = _this->m_actarray_begin;
  v9 = 0;
  if ( m_actarray_begin && (unsigned int)(((char *)_this->m_actarray_end - (char *)m_actarray_begin) >> 2) > 1 )
  {
    _this->m_pact = 0;
    v10 = gbCrc32Compute((const char *)m_dwMatMsg);
    while ( 1 )
    {
      v11 = _this->m_actarray_begin;
      if ( !v11 || v9 >= ((char *)_this->m_actarray_end - (char *)v11) >> 2 )
        break;
      if ( (((Actor *)_this))->Actor::ValidateInput(v10, *((_DWORD *)&v11->m_actarray_type + v9)) )
      {
        _this->m_pact = (gbActor *)*((_DWORD *)&_this->m_actarray_begin->m_actarray_type + v9);
        break;
      }
      ++v9;
    }
  }
  m_pact = _this->m_pact;
  v12 = gbCrc32Compute((const char *)m_dwMatMsg);
  v13 = (((Actor *)_this))->Actor::ValidateInput(v12, (int)m_pact);
  v14 = _this->m_pact;
  if ( !v14 || !v13 )
    return 0;
  (((gbActor *)v14))->gbActor::GotoAction((char *)m_dwMatMsg, 0);
  while ( (((gbVisNode *)_this->m_pact))->gbVisNode::PopMessage(v18) )
    ;
  m_szTexture = _this->m_szTexture;
  if ( _this->m_szTexture[0] )
  {
    ((OpenBaseFile *)&pszName)->OpenBaseFile::OpenBaseFile();
    v16 = _this->m_pact;
    v19 = 0;
    (*(void ( **)(gbActorDef *, char *))(*(_DWORD *)((gbRefObject *)v16->pBody) + 60))(v16->pBody, m_szTexture);
    v19 = -1;
    ((OpenNULLFile *)&pszName)->OpenNULLFile::OpenNULLFile();
  }
  return 1;
}

// 0x00536D20
void LoadActionSequences(Actor *_this, const char *pszRoleDir, int nSeqIdx)
{
  int v4; // esi
  gbActor *ActorFile; // eax
  Actor *m_actarray_end; // eax
  gbVec3D *v7; // esi
  Actor *m_actarray_begin; // edx
  unsigned int v9; // ecx
  int v10; // eax
  int v11; // eax
  gbVec3D *v12; // edi
  gbVec3D *v13; // ebp
  int ArrayCount; // eax
  Actor *v15; // ecx
  gbActor **v16; // eax
  int pVal; // [esp+0x10] [ebp-0x11C] BYREF
  OpenBaseFile v18; // [esp+0x14] [ebp-0x118] BYREF
  Actor *v19; // [esp+0x18] [ebp-0x114]
  char Buffer[260]; // [esp+0x1C] [ebp-0x110] BYREF
  int v21; // [esp+0x128] [ebp-0x4]

  UpdateAllActions(_this);
  strcpy(_this->m_name, pszRoleDir);
  v4 = 0;
  v21 = 0;
  sprintf(Buffer, "role\\%s\\%s.ini", _this->m_name, _this->m_name);
  if ( (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) > 0 )
  {
    ActorFile = (((gbActorMgr *)g_pActorMgr))->gbActorMgr::LoadActorFile(Buffer);
    _this->m_pact = ActorFile;
    if ( ActorFile )
    {
      m_actarray_end = _this->m_actarray_end;
      v7 = (gbVec3D *)m_actarray_end;
      if ( ((char *)_this->m_actarray_capacity_end - (char *)m_actarray_end) >> 2 )
      {
        Vec3CopyStruct(
          (gbVec3D *)m_actarray_end,
          (gbVec3D *)m_actarray_end,
          (gbVec3D *)&m_actarray_end->m_actarray_begin);
        (((Actor *)_this))->Actor::StoreParam((int)_this->m_actarray_end, 1 - (((char *)_this->m_actarray_end - (char *)v7) >> 2));
        v15 = _this->m_actarray_end;
        v16 = (gbActor **)v7;
        if ( v7 != (gbVec3D *)v15 )
        {
          do
            *v16++ = _this->m_pact;
          while ( v16 != (gbActor **)v15 );
        }
        _this->m_actarray_end = (Actor *)((char *)_this->m_actarray_end + 4);
      }
      else
      {
        m_actarray_begin = _this->m_actarray_begin;
        if ( !m_actarray_begin || (v9 = ((char *)m_actarray_end - (char *)m_actarray_begin) >> 2, v9 <= 1) )
          v9 = 1;
        if ( m_actarray_begin )
          v10 = ((char *)m_actarray_end - (char *)m_actarray_begin) >> 2;
        else
          v10 = 0;
        v11 = v9 + v10;
        pVal = v11;
        if ( v11 < 0 )
          v11 = 0;
        v12 = (gbVec3D *)operator new(4 * v11);
        v13 = (gbVec3D *)Vec3CopyStruct((gbVec3D *)_this->m_actarray_begin, v7, v12);
        (((Actor *)_this))->Actor::StoreParam((int)v13, 1);
        Vec3CopyStruct(v7, (gbVec3D *)_this->m_actarray_end, (gbVec3D *)&v13->y);
        v19 = _this->m_actarray_begin;
        operator delete(v19);
        _this->m_actarray_capacity_end = (Actor *)(&v12->x + pVal);
        ArrayCount = (((Actor *)_this))->Actor::GetArrayCount();
        _this->m_actarray_begin = (Actor *)v12;
        _this->m_actarray_end = (Actor *)(&v12->y + ArrayCount);
      }
    }
  }
  else
  {
    do
    {
      sprintf(Buffer, "role\\%s\\%02d.ini", _this->m_name, v4);
      pVal = 0;
      if ( (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) )
      {
        pVal = (int)(((gbActorMgr *)g_pActorMgr))->gbActorMgr::LoadActorFile(Buffer);
        if ( !pVal )
          goto LABEL_21;
        PtrVec_Insert_dword(_this, (int *)_this->m_actarray_end, 1u, &pVal);
      }
      ++v4;
    }
    while ( v4 < 10 );
    _this->m_pact = *(gbActor **)_this->m_actarray_begin;
  }
LABEL_21:
  v21 = -1;
  ((OpenNULLFile *)&v18)->OpenNULLFile::OpenNULLFile();
}

// 0x00536FF0
int UpdateAllActions(Actor *_this)
{
  unsigned int i; // edi
  Actor *m_actarray_begin; // eax
  int result; // eax
  unsigned int *m_dwMatMsg; // esi

  for ( i = 0; ; ++i )
  {
    m_actarray_begin = _this->m_actarray_begin;
    if ( !m_actarray_begin || i >= ((char *)_this->m_actarray_end - (char *)m_actarray_begin) >> 2 )
      break;
    (((gbActorMgr *)g_pActorMgr))->gbActorMgr::DestroyActor(*((gbActor **)&m_actarray_begin->m_actarray_type + i));
  }
  result = (int)_this->m_actarray_end;
  _this->m_actarray_end = _this->m_actarray_begin;
  _this->m_pact = 0;
  m_dwMatMsg = _this->m_dwMatMsg;
  *m_dwMatMsg = 0;
  m_dwMatMsg[1] = 0;
  return result;
}

// 0x00537120
int todo_00537120(Actor *_this, int a1)
{
  int result; // eax

  if ( a1 )
  {
    result = strlen((const char *)a1) + 1;
    qmemcpy(_this->m_szTexture, (const void *)a1, result);
    if ( _this->m_szTexture[0] )
    {
      ((OpenBaseFile *)&a1)->OpenBaseFile::OpenBaseFile();
      (*(void ( **)(gbActorDef *, char *))(*(_DWORD *)((gbRefObject *)_this->m_pact->pBody) + 60))(
        _this->m_pact->pBody,
        _this->m_szTexture);
      ((OpenNULLFile *)&a1)->OpenNULLFile::OpenNULLFile();
    }
  }
  return result;
}

// 0x005371B0
void SetActionByName(Actor *_this, const char *pszAction, const char *pszOpt1, const char *pszOpt2)
{
  int v5; // eax
  int v6; // eax
  gbActor *v7; // ecx
  char *m_szTexture; // esi
  gbActor *v9; // ebx
  gbActor *m_pact; // [esp+0x0] [ebp-0x2C]
  struct gbNodeMsgObj v11; // [esp+0x10] [ebp-0x1C] BYREF
  int v12; // [esp+0x28] [ebp-0x4]

  if ( pszAction )
  {
    strcpy((char *)_this->m_dwMatMsg, pszAction);
    _strlwr((char *)_this->m_dwMatMsg);
  }
  m_pact = _this->m_pact;
  v5 = gbCrc32Compute((const char *)_this->m_dwMatMsg);
  v6 = (((Actor *)_this))->Actor::ValidateInput(v5, (int)m_pact);
  v7 = _this->m_pact;
  if ( v7 && v6 )
  {
    (((gbActor *)v7))->gbActor::GotoAction((char *)_this->m_dwMatMsg, (char *)pszOpt1, (char *)pszOpt2);
    while ( (((gbVisNode *)_this->m_pact))->gbVisNode::PopMessage(v11) )
      ;
    m_szTexture = _this->m_szTexture;
    if ( _this->m_szTexture[0] )
    {
      ((OpenBaseFile *)&pszAction)->OpenBaseFile::OpenBaseFile();
      v9 = _this->m_pact;
      v12 = 0;
      (*(void ( **)(gbActorDef *, char *))(*(_DWORD *)((gbRefObject *)v9->pBody) + 60))(v9->pBody, m_szTexture);
      v12 = -1;
      ((OpenNULLFile *)&pszAction)->OpenNULLFile::OpenNULLFile();
    }
  }
}

// 0x005372D0
int * PtrVec_Insert_dword(Actor *_this, int *pPos, unsigned int nCount, const int *pVal)
{
  Actor *v5; // edi
  int *result; // eax
  Actor *m_actarray_begin; // edx
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
  Actor *v18; // ecx
  Actor *v19; // eax
  unsigned int v20; // ebx
  int *v21; // esi
  int *v22; // ecx
  _DWORD *p_m_actarray_type; // eax
  unsigned int k; // ebp
  int *v25; // ecx
  int *m; // eax
  unsigned int v27; // ebp
  Actor *m_actarray_end; // esi
  int *i; // ecx
  Actor *v30; // ecx
  int *j; // eax
  int v32; // esi
  int v34; // [esp+0x14] [ebp-0x4]
  Actor *nCounta; // [esp+0x20] [ebp+0x8]

  v5 = _this;
  result = (int *)_this->m_actarray_end;
  if ( ((char *)_this->m_actarray_capacity_end - (char *)result) >> 2 >= nCount )
  {
    if ( result - pPos >= nCount )
    {
      if ( nCount )
      {
        v27 = 4 * nCount;
        m_actarray_end = _this->m_actarray_end;
        for ( i = &result[-nCount]; i != result; m_actarray_end = (Actor *)((char *)m_actarray_end + 4) )
        {
          if ( m_actarray_end )
            *(_DWORD *)&m_actarray_end->m_actarray_type = (unsigned long)*i;
          ++i;
        }
        v30 = (Actor *)v5->m_actarray_end;
        for ( j = (int *)((char *)v30 - v27); j != pPos; *(_DWORD *)&v30->m_actarray_type = v32 )
        {
          v32 = *--j;
          v30 = (Actor *)((char *)v30 - 4);
        }
        for ( result = pPos; result != &pPos[v27 / 4]; ++result )
          *result = *pVal;
        v5->m_actarray_end = (Actor *)((char *)v5->m_actarray_end + v27);
      }
    }
    else
    {
      v20 = 4 * nCount;
      v21 = (int *)&pPos[nCount];
      if ( pPos != result )
      {
        v22 = (int *)&v21[v20 / 0xFFFFFFFC];
        do
        {
          if ( v21 )
          {
            *v21 = *v22;
            v5 = _this;
          }
          ++v22;
          ++v21;
        }
        while ( v22 != result );
      }
      p_m_actarray_type = (_DWORD *)&v5->m_actarray_end->m_actarray_type;
      for ( k = nCount - (p_m_actarray_type - pPos); k; --k )
      {
        if ( p_m_actarray_type )
          *p_m_actarray_type = *pVal;
        ++p_m_actarray_type;
      }
      v25 = (int *)v5->m_actarray_end;
      for ( m = pPos; m != v25; ++m )
        *m = *pVal;
      result = (int *)(&v5->m_actarray_end->m_actarray_type + v20);
      v5->m_actarray_end = (Actor *)result;
    }
  }
  else
  {
    m_actarray_begin = _this->m_actarray_begin;
    if ( !m_actarray_begin || (v8 = ((char *)result - (char *)m_actarray_begin) >> 2, nCount >= v8) )
      v8 = nCount;
    if ( m_actarray_begin )
      v9 = ((char *)result - (char *)m_actarray_begin) >> 2;
    else
      v9 = 0;
    v10 = v8 + v9;
    v34 = v10;
    if ( v10 < 0 )
      v10 = 0;
    nCounta = (Actor *)operator new(4 * v10);
    v11 = (int *)nCounta;
    for ( n = (int *)v5->m_actarray_begin; n != pPos; ++v11 )
    {
      if ( v11 )
        *v11 = *n;
      ++n;
    }
    v13 = (int *)v11;
    if ( nCount )
    {
      v14 = nCount;
      do
      {
        if ( v13 )
        {
          *v13 = *pVal;
          v5 = _this;
        }
        ++v13;
        --v14;
      }
      while ( v14 );
    }
    v15 = (int *)v5->m_actarray_end;
    v16 = (int *)&v11[nCount];
    if ( pPos != v15 )
    {
      v17 = (int *)pPos;
      do
      {
        if ( v16 )
          *v16 = *v17;
        ++v17;
        ++v16;
      }
      while ( v17 != v15 );
    }
    operator delete(_this->m_actarray_begin);
    _this->m_actarray_capacity_end = (Actor *)((char *)nCounta + 4 * v34);
    v18 = _this->m_actarray_begin;
    if ( v18 )
    {
      v19 = _this->m_actarray_end;
      _this->m_actarray_begin = nCounta;
      result = (int *)((char *)nCounta + 4 * nCount + 4 * (((char *)v19 - (char *)v18) >> 2));
    }
    else
    {
      _this->m_actarray_begin = nCounta;
      result = (int *)((char *)nCounta + 4 * nCount);
    }
    _this->m_actarray_end = (Actor *)result;
  }
  return result;
}

// 0x005374E0
gbVec3D * Vec3CopyStruct(gbVec3D *pDst, gbVec3D *pSrc, gbVec3D *pEnd)
{
  gbVec3D *v3; // ecx
  gbVec3D *result; // eax

  v3 = (gbVec3D *)pDst;
  if ( pDst == pSrc )
    return pEnd;
  result = (gbVec3D *)pEnd;
  do
  {
    if ( result )
      result->x = v3->x;
    v3 = (gbVec3D *)((char *)v3 + 4);
    result = (gbVec3D *)((char *)result + 4);
  }
  while ( v3 != pSrc );
  return result;
}

// 0x005375F0
void ClearPathBuffer(Actor *_this)
{
  Actor *m_actarray_begin; // edi
  Actor *i; // [esp+0x10] [ebp-0x10]

  operator delete(_this->m_pAllocBuf);
  _this->m_pAllocBuf = 0;
  _this->m_fTransitionSpeed = 0.0;
  _this->m_fTransitionPos = 0.0;
  operator delete(*(void **)_this->m_name);
  *(_DWORD *)_this->m_name = 0;
  *(_DWORD *)&_this->m_name[4] = 0;
  _this->m_fMoveSpeed = 0.0;
  m_actarray_begin = _this->m_actarray_begin;
  for ( i = _this->m_actarray_end; m_actarray_begin != i; m_actarray_begin = (Actor *)((char *)m_actarray_begin + 164) )
  {
    nullsub_2(m_actarray_begin->m_nAnimBuffer, m_actarray_begin->m_nParticleBuffer);
    operator delete((void *)m_actarray_begin->m_nAnimBuffer);
    m_actarray_begin->m_nAnimBuffer = 0;
    m_actarray_begin->m_nParticleBuffer = 0;
    m_actarray_begin->m_vecTargetPos.x = 0.0f;
    (((Array *)&m_actarray_begin->m_nAnimParam1))->Array::Free();
  }
  operator delete(_this->m_actarray_begin);
  _this->m_actarray_begin = 0;
  _this->m_actarray_end = 0;
  _this->m_actarray_capacity_end = 0;
}

// 0x00537770
int LoadActions(Actor *_this, FILE *Stream, int *pnCount)
{
  int v4; // ebx
  char **v5; // ebx
  char *v6; // eax
  Actor *m_actarray_begin; // ebx
  int v8; // edx
  Actor *p_m_pact; // ebx
  int result; // eax
  int v11; // esi
  char **v12; // [esp-0x1C] [ebp-0x130]
  Actor *m_actarray_end; // [esp-0xC] [ebp-0x120]
  FILE *v14; // [esp+0x0] [ebp-0x114]
  int v15; // [esp+0x10] [ebp-0x104]
  int v16; // [esp+0x10] [ebp-0x104]
  int v17; // [esp+0x10] [ebp-0x104]
  char pActionType; // [esp+0x17] [ebp-FDh] BYREF
  int v19; // [esp+0x18] [ebp-FCh] BYREF
  char *a4; // [esp+0x1C] [ebp-F8h] BYREF
  int Buffer; // [esp+0x20] [ebp-F4h] BYREF
  char pEntry[132]; // [esp+0x24] [ebp-F0h] BYREF
  Array v23; // [esp+A8h] [ebp-0x6C] BYREF
  char v24; // [esp+B8h] [ebp-0x5C] BYREF
  void *Block; // [esp+BCh] [ebp-0x58]
  int v26; // [esp+C0h] [ebp-0x54]
  int v27; // [esp+C4h] [ebp-0x50]
  _BYTE pVal[64]; // [esp+C8h] [ebp-0x4C] BYREF
  int v29; // [esp+0x110] [ebp-0x4]

  fseek(Stream, pnCount[40], 0);
  fread(&Buffer, 4u, 1u, Stream);
  v4 = 0;
  if ( Buffer > 0 )
  {
    v15 = 0;
    do
    {
      fread((void *)(::Block + v15), 0x18u, 1u, Stream);
      ++v4;
      v15 += 24;
    }
    while ( v4 < Buffer );
  }
  fseek(Stream, pnCount[41], 0);
  a4 = 0;
  fread(&a4, 4u, 1u, Stream);
  v5 = ActVecUninitCopy(
         (int)_this->m_actarray_end,
         (unsigned int *)_this->m_actarray_end,
         (unsigned int *)_this->m_actarray_begin,
         v12);
  (((Actor *)_this))->Actor::DestroyActionRange((int)v5, (int)_this->m_actarray_end);
  v6 = (char *)a4;
  _this->m_actarray_end = (Actor *)v5;
  v16 = 0;
  if ( (int)v6 > 0 )
  {
    do
    {
      memset(&v23.m_nSize, 0, 12);
      LOBYTE(v23.m_pDataStart) = pActionType;
      v29 = 0;
      InitAction((Actor *)&v24, &pActionType);
      m_actarray_end = _this->m_actarray_end;
      v29 = 1;
      PtrVec_InsertN_elem(_this, &m_actarray_end->m_actarray_type, 1u, pEntry);
      m_actarray_begin = _this->m_actarray_begin;
      if ( m_actarray_begin )
        v8 = ((char *)_this->m_actarray_end - (char *)m_actarray_begin) / 164;
      else
        v8 = 0;
      (((UIBigMap *)((char *)m_actarray_begin + 164 * v8 - 164)))->UIBigMap::SetElementVisible(Stream, v14);
      v29 = 2;
      nullsub_2(Block, v26);
      operator delete(Block);
      Block = 0;
      v26 = 0;
      v27 = 0;
      v29 = -1;
      (((Array *)&v23))->Array::Free();
      ++v16;
    }
    while ( v16 < (int)a4 );
  }
  fseek(Stream, pnCount[46], 0);
  v19 = 0;
  fread(&v19, 4u, 1u, Stream);
  p_m_pact = (Actor *)&_this->m_pact;
  v17 = *(_DWORD *)_this->m_name;
  nullsub_2(v17, *(_DWORD *)&_this->m_name[4]);
  result = v19;
  *(_DWORD *)&_this->m_name[4] = v17;
  v11 = 0;
  if ( result > 0 )
  {
    do
    {
      memset(pVal, 0, sizeof(pVal));
      fread(pVal, 0x40u, 1u, Stream);
      PtrVec_InsertN_64(p_m_pact, &p_m_pact->m_actarray_end->m_actarray_type, 1u, pVal);
      result = v19;
      ++v11;
    }
    while ( v11 < v19 );
  }
  return result;
}

// 0x00537A30
void ClearAllocBuffers(Actor *_this)
{
  operator delete((void *)_this->m_nAnimBuffer);
  _this->m_nAnimBuffer = 0;
  _this->m_nParticleBuffer = 0;
  _this->m_vecTargetPos.x = 0.0;
  operator delete((void *)LODWORD(_this->m_vecBonePos.x));
  _this->m_vecBonePos.x = 0.0;
  _this->m_vecBonePos.y = 0.0;
  _this->m_vecBonePos.z = 0.0;
}

// 0x005381D0
char * InitAnimSequence(Actor *_this)
{
  char *v1; // esi
  int v2; // ebx
  float *p_m_fRoleParam2; // eax
  float *v4; // ebp
  float *v5; // ebp
  float *v6; // ebp

  v1 = (char *)&_this->m_name[4];
  v2 = 4;
  p_m_fRoleParam2 = (float *)&_this->m_fRoleParam2;
  do
  {
    v4 = (float *)(p_m_fRoleParam2 - 6);
    *(_DWORD *)v1 = 0;
    *(p_m_fRoleParam2 - 8) = 0.0;
    *(p_m_fRoleParam2 - 7) = 0.0;
    *v4 = 0.0;
    v1 += 48;
    v4[1] = 0.0;
    v4[2] = 0.0;
    v5 = (float *)(p_m_fRoleParam2 - 3);
    *(p_m_fRoleParam2 - 3) = 0.0;
    v5[1] = 0.0;
    v5[2] = 0.0;
    v6 = (float *)p_m_fRoleParam2;
    p_m_fRoleParam2 += 12;
    --v2;
    *v6 = 0.0;
    v6[1] = 0.0;
    v6[2] = 0.0;
  }
  while ( v2 );
  _this->m_actarray_type = 0;
  *(&_this->m_actarray_type + 1) = 0;
  *(&_this->m_actarray_type + 2) = 0;
  *(&_this->m_actarray_type + 3) = 0;
  LOBYTE(_this->m_actarray_begin) = 0;
  BYTE1(_this->m_actarray_begin) = 0;
  BYTE2(_this->m_actarray_begin) = 0;
  _this->m_actarray_capacity_end = 0;
  _this->m_pact = 0;
  *(_DWORD *)_this->m_name = 0;
  *(_DWORD *)&_this->m_fScale = 0;
  _this->m_actarray_end = (Actor *)1065353216;
  memset(&_this->m_name[4], 0, 0xC0u);
  return &_this->m_actarray_type;
}

// 0x00538260
CHAR * ClearModelFlag(CHAR *_this)
{
  *(_DWORD *)_this = 0;
  lstrcpyA((char *)_this + 4, unk_C10D38);
  lstrcpyA((char *)_this + 36, unk_C10D38);
  lstrcpyA((char *)_this + 66, unk_C10D38);
  lstrcpyA((char *)_this + 96, unk_C10D38);
  _this[612] = 0;
  memset(_this + 644, 0, 0x18u);
  _this[800] = 0;
  _this[801] = 0;
  *((_DWORD *)_this + 201) = -1;
  return _this;
}

// 0x005382D0
BOOL CheckDirectoryExists(LPCSTR lpFileName)
{
  HANDLE FirstFileA; // eax
  BOOL v3; // esi
  struct _WIN32_FIND_DATAA FindFileData; // [esp+0x4] [ebp-0x140] BYREF

  FirstFileA = FindFirstFileA(lpFileName, &FindFileData);
  if ( FirstFileA == (HANDLE)-1 )
    return 0;
  v3 = (FindFileData.dwFileAttributes & 0x10) != 0;
  FindClose(FirstFileA);
  return v3;
}

// 0x00538CE0
int ClearActionFlags(Actor *_this)
{
  int result; // eax

  result = 0;
  _this->m_actarray_type = 0;
  *(&_this->m_actarray_type + 1) = 0;
  *(&_this->m_actarray_type + 2) = 0;
  *(&_this->m_actarray_type + 3) = 0;
  LOBYTE(_this->m_actarray_begin) = 0;
  BYTE1(_this->m_actarray_begin) = 0;
  BYTE2(_this->m_actarray_begin) = 0;
  _this->m_actarray_end = (Actor *)1065353216;
  _this->m_actarray_capacity_end = 0;
  _this->m_pact = 0;
  *(_DWORD *)_this->m_name = 0;
  *(_DWORD *)&_this->m_fScale = 0;
  memset(&_this->m_name[4], 0, 0xC0u);
  return result;
}

// 0x005394D0
int * ClearActionArrays(Actor *_this)
{
  int *result; // eax

  result = (int *)_this;
  _this->m_actarray_begin = 0;
  _this->m_actarray_end = 0;
  _this->m_actarray_capacity_end = 0;
  _this->m_pact = 0;
  *(_DWORD *)_this->m_name = 0;
  *(_DWORD *)&_this->m_name[4] = 0;
  return result;
}

// 0x005394F0
void * GetSaveDataManager()
{
  if ( (g_ActorSaveData.m_nRoleParam0 & 1) == 0 )
  {
    LOBYTE(g_ActorSaveData.m_nRoleParam0) |= 1u;
    (((Actor *)&g_ActorSaveData))->Actor::ClearArrayEntry();
    atexit(SingletonThunk_00539530);
  }
  return &g_ActorSaveData;
}

// 0x00539700
void VecEntry_Write(Actor *_this, FILE *fp)
{
  FILE *v2; // ebx
  float x; // eax
  float i; // edi
  int m_nAnimBuffer; // eax
  char *j; // edi
  int Buffer; // [esp+0xC] [ebp-0x4] BYREF

  v2 = (FILE *)fp;
  if ( fp )
  {
    fwrite(_this, 0x84u, 1u, fp);
    x = _this->m_vecBonePos.x;
    if ( x == 0.0f )
      fp = 0;
    else
      fp = (FILE *)((LODWORD(_this->m_vecBonePos.y) - LODWORD(x)) / 656);
    fwrite(&fp, 4u, 1u, v2);
    if ( (int)fp > 0 )
    {
      for ( i = _this->m_vecBonePos.x; LODWORD(i) != LODWORD(_this->m_vecBonePos.y); LODWORD(i) += 656 )
        fwrite((const void *)LODWORD(i), 0x290u, 1u, v2);
    }
    m_nAnimBuffer = _this->m_nAnimBuffer;
    if ( m_nAnimBuffer )
      Buffer = (_this->m_nParticleBuffer - m_nAnimBuffer) >> 1;
    else
      Buffer = 0;
    fwrite(&Buffer, 4u, 1u, v2);
    if ( Buffer > 0 )
    {
      for ( j = (char *)_this->m_nAnimBuffer; j != (char *)_this->m_nParticleBuffer; j += 2 )
        fwrite(j, 2u, 1u, v2);
    }
  }
}

// 0x00539D60
Actor * ClearAllActions(Actor *_this)
{
  Actor *result; // eax
  Actor *m_actarray_begin; // ebp
  Actor *m_actarray_end; // edi
  Actor *v4; // esi

  result = _this;
  *(_DWORD *)&_this->m_name[4] = *(_DWORD *)_this->m_name;
  m_actarray_begin = _this->m_actarray_begin;
  m_actarray_end = _this->m_actarray_end;
  v4 = (Actor *)m_actarray_begin;
  if ( m_actarray_begin != m_actarray_end )
  {
    do
    {
      ClearAllocBuffers(v4);
      v4 = (Actor *)((char *)v4 + 164);
    }
    while ( v4 != m_actarray_end );
    result = _this;
  }
  result->m_actarray_end = m_actarray_begin;
  LODWORD(result->m_fTransitionSpeed) = (unsigned long)result->m_pAllocBuf;
  return result;
}

// 0x00539E70
char * InsertAnimFrame(Actor *_this, float fTime)
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

  m_fTransitionSpeed = _this->m_fTransitionSpeed;
  p_m_fMoveRange = (float *)&_this->m_fMoveRange;
  v4 = (gbVec3D *)LODWORD(m_fTransitionSpeed);
  if ( (LODWORD(_this->m_fTransitionPos) - LODWORD(m_fTransitionSpeed)) >> 2 )
  {
    Vec3CopyStruct(
      (gbVec3D *)LODWORD(m_fTransitionSpeed),
      (gbVec3D *)LODWORD(m_fTransitionSpeed),
      (gbVec3D *)(LODWORD(m_fTransitionSpeed) + 4));
    (((Actor *)p_m_fMoveRange))->Actor::StoreParam(*((_DWORD *)p_m_fMoveRange + 2), 1 - ((*((_DWORD *)p_m_fMoveRange + 2) - (int)v4) >> 2));
    v15 = (gbVec3D *)*((_DWORD *)p_m_fMoveRange + 2);
    if ( v4 == v15 )
    {
      result = (char *)(*((_DWORD *)p_m_fMoveRange + 2) + 4);
      *((_DWORD *)p_m_fMoveRange + 2) = (unsigned long)result;
    }
    else
    {
      do
      {
        v4->x = fTime;
        v4 = (gbVec3D *)((char *)v4 + 4);
      }
      while ( v4 != v15 );
      result = (char *)(*((_DWORD *)p_m_fMoveRange + 2) + 4);
      *((_DWORD *)p_m_fMoveRange + 2) = (unsigned long)result;
    }
  }
  else
  {
    m_pAllocBuf = _this->m_pAllocBuf;
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
    v16 = (char *)v9;
    for ( i = (int)v9; v10 != (int *)v4; i += 4 )
      AssignInt((int *)i, v10++);
    (((Actor *)p_m_fMoveRange))->Actor::StoreParam(i, 1);
    Vec3CopyStruct(v4, *((gbVec3D **)p_m_fMoveRange + 2), (gbVec3D *)(i + 4));
    nullsub_2(*((_DWORD *)p_m_fMoveRange + 1), *((_DWORD *)p_m_fMoveRange + 2));
    operator delete(*((void **)p_m_fMoveRange + 1));
    v12 = *((_DWORD *)p_m_fMoveRange + 1);
    *((_DWORD *)p_m_fMoveRange + 3) = (unsigned long)&v16[4 * v17];
    if ( v12 )
    {
      v14 = *((_DWORD *)p_m_fMoveRange + 2);
      *((_DWORD *)p_m_fMoveRange + 1) = (unsigned long)v16;
      result = (char *)&v16[4 * ((v14 - v12) >> 2) + 4];
      *((_DWORD *)p_m_fMoveRange + 2) = (unsigned long)result;
    }
    else
    {
      *((_DWORD *)p_m_fMoveRange + 1) = (unsigned long)v16;
      result = (char *)(v16 + 4);
      *((_DWORD *)p_m_fMoveRange + 2) = (unsigned long)(v16 + 4);
    }
  }
  return result;
}

// 0x0053A060
int * InitAction(Actor *_this, _BYTE *pActionType)
{
  int *result; // eax

  result = (int *)_this;
  _this->m_actarray_type = *pActionType;
  _this->m_actarray_begin = 0;
  _this->m_actarray_end = 0;
  _this->m_actarray_capacity_end = 0;
  return result;
}

// 0x0053A0C0
int * Vec_InsertEntry(Actor *_this, int *pPos, const int *pEntry)
{
  Actor *m_actarray_begin; // ebx
  Actor *m_actarray_end; // ecx
  int v7; // ebp
  unsigned int v8; // ebp
  int v9; // edx
  unsigned int v10; // eax
  Actor *v11; // eax
  int *v12; // ebx
  int i; // ebp
  int ActionCount; // eax
  char **v16; // [esp-0xC] [ebp-0x24]
  char **v17; // [esp+0x0] [ebp-0x18]
  unsigned int v18; // [esp+0x10] [ebp-0x8]
  Actor *v19; // [esp+0x14] [ebp-0x4]
  int *pPosa; // [esp+0x1C] [ebp+0x4]

  m_actarray_begin = _this->m_actarray_begin;
  m_actarray_end = _this->m_actarray_end;
  v7 = ((char *)pPos - (char *)m_actarray_begin) / 164;
  pPosa = (int *)v7;
  if ( ((char *)_this->m_actarray_capacity_end - (char *)m_actarray_end) / 164 )
  {
    if ( ((char *)m_actarray_end - (char *)pPos) / 164 )
    {
      (((Actor *)_this))->Actor::FindMatchingEntry((int)&m_actarray_end[-1].m_fDistAccum, (int)m_actarray_end, (int)m_actarray_end);
      ActVecUninitFill((int)pPos, (int)&_this->m_actarray_end[-1].m_fDistAccum, (int)_this->m_actarray_end, v17);
      ActVecUninitCopy2((int)pPos, pPos + 41, (int *)pEntry, v16);
    }
    else
    {
      (((Actor *)_this))->Actor::FindMatchingEntry((int)pPos, (int)m_actarray_end, (int)(pPos + 41));
      (((Actor *)_this))->Actor::SetVideoRegions((int)_this->m_actarray_end, 1 - ((char *)_this->m_actarray_end - (char *)pPos) / 164, (int)pEntry);
      ActVecUninitCopy2((int)pPos, (int *)_this->m_actarray_end, (int *)pEntry, v17);
    }
    _this->m_actarray_end = (Actor *)((char *)_this->m_actarray_end + 164);
  }
  else
  {
    if ( !m_actarray_begin || (v8 = ((char *)m_actarray_end - (char *)m_actarray_begin) / 164, v8 <= 1) )
      v8 = 1;
    if ( m_actarray_begin )
      v9 = ((char *)m_actarray_end - (char *)m_actarray_begin) / 164;
    else
      v9 = 0;
    v10 = v9 + v8;
    v18 = v9 + v8;
    if ( (int)(v9 + v8) < 0 )
      v10 = 0;
    v11 = (Actor *)operator new(164 * v10);
    v12 = (int *)_this->m_actarray_begin;
    v19 = (Actor *)v11;
    for ( i = (int)v11; v12 != pPos; i += 164 )
    {
      VideoPlayer::SetRegion(i, (int)v12);
      v12 += 41;
    }
    VideoPlayer::SetRegion(i, (int)pEntry);
    (((Actor *)_this))->Actor::FindMatchingEntry((int)pPos, (int)_this->m_actarray_end, i + 164);
    (((Actor *)_this))->Actor::DestroyActionRange((int)_this->m_actarray_begin, (int)_this->m_actarray_end);
    operator delete(_this->m_actarray_begin);
    _this->m_actarray_capacity_end = (Actor *)((char *)v19 + 164 * v18);
    ActionCount = (((Actor *)_this))->Actor::GetActionCount();
    v7 = (int)pPosa;
    _this->m_actarray_begin = v19;
    _this->m_actarray_end = (Actor *)(&v19->m_vecTargetPos.y + 41 * ActionCount);
  }
  return (int *)((char *)_this->m_actarray_begin + 164 * v7);
}

// 0x0053A340
char * PtrVec_InsertN(Actor *_this, char *pPos, unsigned int nCount, const char *pVal)
{
  Actor *m_actarray_end; // ebx
  Actor *m_actarray_begin; // esi
  unsigned int v7; // ecx
  int v8; // edx
  unsigned int v9; // eax
  Actor *v10; // esi
  Actor *v11; // edx
  Actor *j; // eax
  Actor *v13; // eax
  unsigned int v14; // ebx
  char *p_m_actarray_type; // edi
  char *v16; // ebx
  char *v17; // eax
  char *result; // eax
  int v19; // edx
  int v20; // ecx
  Actor *v21; // edi
  unsigned int v22; // esi
  char *v23; // eax
  Actor *v24; // edx
  Actor *v25; // eax
  unsigned int i; // edx
  Actor *v27; // ebx
  Actor *v28; // esi
  unsigned int v29; // ebp
  Actor *v30; // esi
  Actor *v31; // ebx
  int v32; // esi
  Actor *v33; // esi
  int v34; // [esp+0x0] [ebp-0x18]
  Actor *v35; // [esp+0x10] [ebp-0x8]
  Actor *v36; // [esp+0x14] [ebp-0x4]
  Actor *pPosa; // [esp+0x1C] [ebp+0x4]
  unsigned int nCounta; // [esp+0x20] [ebp+0x8]
  unsigned int nCountb; // [esp+0x20] [ebp+0x8]
  const char *pVala; // [esp+0x24] [ebp+0xC]

  m_actarray_end = _this->m_actarray_end;
  v35 = _this;
  if ( ((char *)_this->m_actarray_capacity_end - (char *)m_actarray_end) / 656 >= nCount )
  {
    v21 = (Actor *)pPos;
    result = (char *)((unsigned int)((unsigned __int64)(1676084799i64 * ((char *)m_actarray_end - pPos)) >> 32) >> 31);
    if ( ((char *)m_actarray_end - pPos) / 656 >= nCount )
    {
      if ( nCount )
      {
        result = (char *)(5 * nCount);
        pPosa = _this->m_actarray_end;
        v29 = 656 * nCount;
        v30 = (Actor *)((char *)m_actarray_end - 656 * nCount);
        if ( v30 != m_actarray_end )
        {
          do
          {
            Actor::CopyConstruct_290(pPosa, v30, v34);
            v30 = (Actor *)((char *)v30 + 656);
            pPosa = (Actor *)((char *)pPosa + 656);
          }
          while ( v30 != m_actarray_end );
          _this = v35;
        }
        v31 = _this->m_actarray_end;
        v32 = (int)v31 - v29;
        if ( v21 != (Actor *)((char *)v31 - v29) )
        {
          do
          {
            v32 -= 656;
            v31 = (Actor *)((char *)v31 - 656);
            result = SetCurrentAction(v31, v32);
          }
          while ( (Actor *)v32 != v21 );
          _this = v35;
        }
        v33 = (Actor *)((char *)v21 + v29);
        if ( v21 != (Actor *)((char *)v21 + v29) )
        {
          do
          {
            result = SetCurrentAction(v21, (int)pVal);
            v21 = (Actor *)((char *)v21 + 656);
          }
          while ( v21 != v33 );
          _this = v35;
        }
        _this->m_actarray_end = (Actor *)((char *)_this->m_actarray_end + v29);
      }
    }
    else
    {
      v22 = 656 * nCount;
      nCountb = 656 * nCount;
      v23 = (char *)&pPos[656 * nCount];
      if ( pPos != (char *)m_actarray_end )
      {
        v24 = (Actor *)&v23[-v22];
        do
        {
          if ( v23 )
          {
            qmemcpy(v23, v24, 0x290u);
            v21 = (Actor *)pPos;
            _this = v35;
          }
          v24 = (Actor *)((char *)v24 + 656);
          v23 += 656;
        }
        while ( v24 != m_actarray_end );
      }
      v25 = _this->m_actarray_end;
      for ( i = nCount - ((char *)v25 - (char *)v21) / 656; i; --i )
      {
        if ( v25 )
        {
          qmemcpy(v25, pVal, 0x290u);
          v21 = (Actor *)pPos;
          _this = v35;
        }
        v25 = (Actor *)((char *)v25 + 656);
      }
      v27 = _this->m_actarray_end;
      v28 = (Actor *)v21;
      if ( v21 != v27 )
      {
        do
        {
          (((Actor *)v28))->Actor::ActionEntry_Assign((int)pVal);
          todo_0053A670((Actor *)&v28->m_curact[35], (int)(pVal + 620));
          v28 = (Actor *)((char *)v28 + 656);
        }
        while ( v28 != v27 );
        _this = v35;
      }
      result = (char *)(&_this->m_actarray_end->m_actarray_type + nCountb);
      _this->m_actarray_end = (Actor *)result;
    }
  }
  else
  {
    m_actarray_begin = _this->m_actarray_begin;
    if ( !m_actarray_begin || (v7 = ((char *)m_actarray_end - (char *)m_actarray_begin) / 656, nCount >= v7) )
      v7 = nCount;
    if ( m_actarray_begin )
      v8 = ((char *)m_actarray_end - (char *)m_actarray_begin) / 656;
    else
      v8 = 0;
    v9 = v8 + v7;
    nCounta = v8 + v7;
    if ( (int)(v8 + v7) < 0 )
      v9 = 0;
    v10 = (Actor *)v35;
    v36 = (Actor *)operator new(656 * v9);
    v11 = (Actor *)v36;
    for ( j = v35->m_actarray_begin; j != (Actor *)pPos; v11 = (Actor *)((char *)v11 + 656) )
    {
      if ( v11 )
      {
        qmemcpy(v11, j, 0x290u);
        v10 = (Actor *)v35;
      }
      j = (Actor *)((char *)j + 656);
    }
    v13 = (Actor *)v11;
    if ( nCount )
    {
      v14 = nCount;
      do
      {
        if ( v13 )
        {
          qmemcpy(v13, pVal, 0x290u);
          v10 = (Actor *)v35;
        }
        v13 = (Actor *)((char *)v13 + 656);
        --v14;
      }
      while ( v14 );
    }
    p_m_actarray_type = (char *)&v10->m_actarray_end->m_actarray_type;
    pVala = (const char *)p_m_actarray_type;
    v16 = (char *)(&v11->m_actarray_type + 656 * nCount);
    if ( pPos != p_m_actarray_type )
    {
      v17 = (char *)pPos;
      do
      {
        if ( v16 )
        {
          qmemcpy(v16, v17, 0x290u);
          v10 = (Actor *)v35;
          p_m_actarray_type = (char *)pVala;
        }
        v17 += 656;
        v16 += 656;
      }
      while ( v17 != p_m_actarray_type );
    }
    operator delete(v10->m_actarray_begin);
    result = (char *)&v10->m_actarray_begin->m_actarray_type;
    v10->m_actarray_capacity_end = (Actor *)((char *)v36 + 656 * nCounta);
    if ( result )
    {
      v20 = (int)(char *)v10->m_actarray_end - result;
      result = (char *)((unsigned int)((unsigned __int64)(1676084799i64 * v20) >> 32) >> 31);
      v19 = v20 / 656;
    }
    else
    {
      v19 = 0;
    }
    v10->m_actarray_begin = v36;
    v10->m_actarray_end = (Actor *)((char *)v36 + 656 * v19 + 656 * nCount);
  }
  return result;
}

// 0x0053A670
int todo_0053A670(Actor *_this, int a1)
{
  int result; // eax

  result = (int)_this;
  *(_DWORD *)&_this->m_actarray_type = *(_DWORD *)a1;
  _this->m_actarray_begin = *(Actor **)(a1 + 4);
  _this->m_actarray_end = *(Actor **)(a1 + 8);
  _this->m_actarray_capacity_end = *(Actor **)(a1 + 12);
  _this->m_pact = *(gbActor **)(a1 + 16);
  *(_QWORD *)_this->m_name = *(_QWORD *)(a1 + 20);
  LOBYTE(_this->m_fMoveSpeed) = *(_BYTE *)(a1 + 28);
  BYTE1(_this->m_fMoveSpeed) = *(_BYTE *)(a1 + 29);
  _this->m_fMoveRange = *(float *)(a1 + 32);
  return result;
}

// 0x0053A6C0
_WORD * PtrVec_Insert_word(Actor *_this, _WORD *pPos, unsigned int nCount, const _WORD *pVal)
{
  Actor *v5; // edi
  _WORD *result; // eax
  Actor *m_actarray_begin; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  Actor *v11; // ecx
  Actor *k; // eax
  _WORD *v13; // eax
  unsigned int v14; // edx
  Actor *v15; // edi
  _WORD *v16; // edx
  Actor *v17; // eax
  Actor *v18; // ecx
  Actor *v19; // eax
  unsigned int v20; // ebx
  _WORD *v21; // esi
  _WORD *v22; // ecx
  _WORD *p_m_actarray_type; // eax
  unsigned int j; // ebp
  Actor *v25; // ecx
  Actor *v26; // eax
  unsigned int v27; // ebp
  _WORD *v28; // ecx
  _WORD *i; // esi
  Actor *m_actarray_end; // ecx
  _WORD *v31; // eax
  __int16 v32; // si
  int v34; // [esp+0x14] [ebp-0x4]
  Actor *nCounta; // [esp+0x20] [ebp+0x8]

  v5 = _this;
  result = (_WORD *)&_this->m_actarray_end->m_actarray_type;
  if ( ((char *)_this->m_actarray_capacity_end - (char *)result) >> 1 >= nCount )
  {
    if ( result - pPos >= nCount )
    {
      if ( nCount )
      {
        v27 = 2 * nCount;
        v28 = (_WORD *)&result[-nCount];
        for ( i = result; v28 != result; ++i )
        {
          if ( i )
            *i = *v28;
          ++v28;
        }
        m_actarray_end = (Actor *)v5->m_actarray_end;
        v31 = (_WORD *)(&m_actarray_end->m_actarray_type - v27);
        if ( pPos != (_WORD *)((char *)m_actarray_end - v27) )
        {
          do
          {
            v32 = *--v31;
            m_actarray_end = (Actor *)((char *)m_actarray_end - 2);
            *(_WORD *)&m_actarray_end->m_actarray_type = v32;
          }
          while ( v31 != pPos );
        }
        for ( result = pPos; result != &pPos[v27 / 2]; ++result )
          *result = *pVal;
        v5->m_actarray_end = (Actor *)((char *)v5->m_actarray_end + v27);
      }
    }
    else
    {
      v20 = 2 * nCount;
      v21 = (_WORD *)&pPos[nCount];
      if ( pPos != result )
      {
        v22 = (_WORD *)&v21[v20 / 0xFFFFFFFE];
        do
        {
          if ( v21 )
          {
            *v21 = *v22;
            v5 = _this;
          }
          ++v22;
          ++v21;
        }
        while ( v22 != result );
      }
      p_m_actarray_type = (_WORD *)&v5->m_actarray_end->m_actarray_type;
      for ( j = nCount - (p_m_actarray_type - pPos); j; --j )
      {
        if ( p_m_actarray_type )
          *p_m_actarray_type = *pVal;
        ++p_m_actarray_type;
      }
      v25 = (Actor *)v5->m_actarray_end;
      v26 = (Actor *)pPos;
      if ( pPos != (_WORD *)v25 )
      {
        do
        {
          *(_WORD *)&v26->m_actarray_type = *pVal;
          v26 = (Actor *)((char *)v26 + 2);
        }
        while ( v26 != v25 );
      }
      result = (_WORD *)(&v5->m_actarray_end->m_actarray_type + v20);
      v5->m_actarray_end = (Actor *)result;
    }
  }
  else
  {
    m_actarray_begin = _this->m_actarray_begin;
    if ( !m_actarray_begin || (v8 = ((char *)result - (char *)m_actarray_begin) >> 1, nCount >= v8) )
      v8 = nCount;
    if ( m_actarray_begin )
      v9 = ((char *)result - (char *)m_actarray_begin) >> 1;
    else
      v9 = 0;
    v10 = v8 + v9;
    v34 = v10;
    if ( v10 < 0 )
      v10 = 0;
    nCounta = (Actor *)operator new(2 * v10);
    v11 = (Actor *)nCounta;
    for ( k = v5->m_actarray_begin; k != (Actor *)pPos; v11 = (Actor *)((char *)v11 + 2) )
    {
      if ( v11 )
        *(_WORD *)&v11->m_actarray_type = *(_WORD *)&k->m_actarray_type;
      k = (Actor *)((char *)k + 2);
    }
    v13 = (_WORD *)&v11->m_actarray_type;
    if ( nCount )
    {
      v14 = nCount;
      do
      {
        if ( v13 )
        {
          *v13 = *pVal;
          v5 = _this;
        }
        ++v13;
        --v14;
      }
      while ( v14 );
    }
    v15 = (Actor *)v5->m_actarray_end;
    v16 = (_WORD *)(&v11->m_actarray_type + 2 * nCount);
    if ( pPos != (_WORD *)v15 )
    {
      v17 = (Actor *)pPos;
      do
      {
        if ( v16 )
          *v16 = *(_WORD *)&v17->m_actarray_type;
        v17 = (Actor *)((char *)v17 + 2);
        ++v16;
      }
      while ( v17 != v15 );
    }
    operator delete(_this->m_actarray_begin);
    _this->m_actarray_capacity_end = (Actor *)((char *)nCounta + 2 * v34);
    v18 = _this->m_actarray_begin;
    if ( v18 )
    {
      v19 = _this->m_actarray_end;
      _this->m_actarray_begin = nCounta;
      result = (_WORD *)(&nCounta->m_actarray_type + 2 * nCount + 2 * (((char *)v19 - (char *)v18) >> 1));
    }
    else
    {
      _this->m_actarray_begin = nCounta;
      result = (_WORD *)(&nCounta->m_actarray_type + 2 * nCount);
    }
    _this->m_actarray_end = (Actor *)result;
  }
  return result;
}

// 0x0053A8D0
char * PtrVec_InsertN_elem(Actor *_this, char *pPos, unsigned int nCount, const char *pEntry)
{
  Actor *m_actarray_end; // edi
  unsigned int v5; // esi
  Actor *m_actarray_begin; // ecx
  unsigned int v7; // ebx
  int v8; // edx
  unsigned int v9; // eax
  int v10; // ebp
  char *i; // edi
  int j; // edi
  char *v13; // edi
  const char *v14; // eax
  char *p_m_actarray_type; // ebp
  Actor *v16; // ebp
  Actor *k; // edi
  Actor *v18; // eax
  int v19; // edx
  unsigned int v20; // esi
  char *result; // eax
  char *v23; // ebx
  Actor *v24; // edi
  unsigned int v25; // esi
  char *v26; // ebx
  Actor *v27; // ebx
  int v28; // esi
  Actor *v29; // edi
  char *v30; // ebx
  char *p_m_nPathBuffer; // edx
  int *v32; // eax
  char *v33; // ebx
  Actor *v34; // [esp+0x10] [ebp-0xC]
  Actor *v35; // [esp+0x14] [ebp-0x8]
  Actor *v36; // [esp+0x14] [ebp-0x8]
  Actor *v37; // [esp+0x18] [ebp-0x4]
  char *pPosa; // [esp+0x20] [ebp+0x4]
  char *pPosb; // [esp+0x20] [ebp+0x4]
  char *nCounta; // [esp+0x24] [ebp+0x8]
  Actor *nCountb; // [esp+0x24] [ebp+0x8]
  unsigned int nCountc; // [esp+0x24] [ebp+0x8]
  char *nCountd; // [esp+0x24] [ebp+0x8]
  const char *pEntrya; // [esp+0x28] [ebp+0xC]

  m_actarray_end = _this->m_actarray_end;
  v5 = nCount;
  v34 = _this;
  if ( ((char *)_this->m_actarray_capacity_end - (char *)m_actarray_end) / 164 >= nCount )
  {
    result = (char *)((unsigned int)((unsigned __int64)(1676084799i64 * ((char *)m_actarray_end - pPos)) >> 32) >> 31);
    if ( ((char *)m_actarray_end - pPos) / 164 >= nCount )
    {
      if ( nCount )
      {
        v27 = _this->m_actarray_end;
        result = (char *)(164 * nCount);
        v28 = (int)m_actarray_end - 164 * nCount;
        pPosb = (char *)(164 * nCount);
        if ( (Actor *)v28 != m_actarray_end )
        {
          do
          {
            VideoPlayer::SetRegion((int)v27, v28);
            v28 += 164;
            v27 = (Actor *)((char *)v27 + 164);
          }
          while ( (Actor *)v28 != m_actarray_end );
          _this = v34;
          result = (char *)(164 * nCount);
        }
        v29 = _this->m_actarray_end;
        v30 = (char *)((char *)v29 - result);
        if ( pPos != (char *)((char *)v29 - result) )
        {
          p_m_nPathBuffer = (char *)&v29->m_nPathBuffer;
          v32 = (int *)(v30 + 148);
          while ( 1 )
          {
            v30 -= 164;
            nCountc = (unsigned int)(v32 - 41);
            qmemcpy(&v29[-1].m_fDistAccum, v30, 0x84u);
            v36 = (Actor *)(p_m_nPathBuffer - 164);
            (((Actor *)(p_m_nPathBuffer - 180)))->Actor::ActArray_Assign(v32 - 45);
            todo_0053BD30(v36, nCountc);
            if ( v30 == pPos )
              break;
            v32 = (int *)nCountc;
            p_m_nPathBuffer = (char *)&v36->m_actarray_type;
            v29 = (Actor *)((char *)v29 - 164);
          }
          _this = v34;
          result = (char *)pPosb;
        }
        v33 = (char *)pPos;
        nCountd = (char *)&pPos[(_DWORD)result];
        if ( pPos != &pPos[(_DWORD)result] )
        {
          do
          {
            qmemcpy(v33, pEntry, 0x84u);
            (((Actor *)(v33 + 132)))->Actor::ActArray_Assign((int *)pEntry + 33);
            todo_0053BD30((Actor *)(v33 + 148), (int)(pEntry + 148));
            v33 += 164;
          }
          while ( v33 != nCountd );
          _this = v34;
          result = (char *)pPosb;
        }
        _this->m_actarray_end = (Actor *)((char *)_this->m_actarray_end + (unsigned int)result);
      }
    }
    else
    {
      v23 = (char *)pPos;
      pPosa = (char *)(164 * nCount);
      if ( pPos != (char *)m_actarray_end )
      {
        nCounta = (char *)&pPos[164 * nCount];
        do
        {
          VideoPlayer::SetRegion((int)nCounta, (int)v23);
          v23 += 164;
          nCounta += 164;
        }
        while ( v23 != (char *)m_actarray_end );
        _this = v34;
      }
      v24 = _this->m_actarray_end;
      v25 = v5 - ((char *)v24 - pPos) / 164;
      if ( v25 )
      {
        do
        {
          VideoPlayer::SetRegion((int)v24, (int)pEntry);
          v24 = (Actor *)((char *)v24 + 164);
          --v25;
        }
        while ( v25 );
        _this = v34;
      }
      v26 = (char *)pPos;
      nCountb = _this->m_actarray_end;
      if ( pPos != (char *)nCountb )
      {
        do
        {
          qmemcpy(v26, pEntry, 0x84u);
          (((Actor *)(v26 + 132)))->Actor::ActArray_Assign((int *)pEntry + 33);
          todo_0053BD30((Actor *)(v26 + 148), (int)(pEntry + 148));
          v26 += 164;
        }
        while ( v26 != (char *)nCountb );
        _this = v34;
      }
      result = (char *)&pPosa[(unsigned int)_this->m_actarray_end];
      _this->m_actarray_end = (Actor *)result;
    }
  }
  else
  {
    m_actarray_begin = _this->m_actarray_begin;
    if ( !m_actarray_begin || (v7 = ((char *)m_actarray_end - (char *)m_actarray_begin) / 164, nCount >= v7) )
      v7 = nCount;
    if ( m_actarray_begin )
      v8 = ((char *)m_actarray_end - (char *)m_actarray_begin) / 164;
    else
      v8 = 0;
    v9 = v8 + v7;
    v35 = (Actor *)(v8 + v7);
    if ( (int)(v8 + v7) < 0 )
      v9 = 0;
    v37 = (Actor *)operator new(164 * v9);
    v10 = (int)v37;
    for ( i = (char *)&v34->m_actarray_begin->m_actarray_type; i != pPos; v10 += 164 )
    {
      VideoPlayer::SetRegion(v10, (int)i);
      i += 164;
    }
    for ( j = v10; nCount; --nCount )
    {
      VideoPlayer::SetRegion(j, (int)pEntry);
      j += 164;
    }
    v13 = (char *)pPos;
    v14 = (const char *)(v10 + 164 * v5);
    p_m_actarray_type = (char *)&v34->m_actarray_end->m_actarray_type;
    if ( pPos != p_m_actarray_type )
    {
      pEntrya = (const char *)v14;
      do
      {
        VideoPlayer::SetRegion((int)pEntrya, (int)v13);
        v13 += 164;
        pEntrya += 164;
      }
      while ( v13 != p_m_actarray_type );
    }
    v16 = (Actor *)v34->m_actarray_end;
    for ( k = v34->m_actarray_begin; k != v16; k = (Actor *)((char *)k + 164) )
      ClearAllocBuffers(k);
    operator delete(v34->m_actarray_begin);
    v34->m_actarray_capacity_end = (Actor *)((char *)v37 + 164 * (_DWORD)v35);
    v18 = (Actor *)v34->m_actarray_begin;
    if ( v18 )
      v19 = ((char *)v34->m_actarray_end - (char *)v18) / 164;
    else
      v19 = 0;
    v20 = v19 + v5;
    v34->m_actarray_begin = v37;
    result = (char *)(41 * v20);
    v34->m_actarray_end = (Actor *)((char *)v37 + 164 * v20);
  }
  return result;
}

// 0x0053ACA0
char * PtrVec_InsertN_64(Actor *_this, char *pPos, unsigned int nCount, const void *pVal)
{
  unsigned int v4; // esi
  Actor *v5; // edi
  char *result; // eax
  Actor *m_actarray_begin; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  Actor *v11; // edx
  Actor *i; // eax
  Actor *v13; // eax
  unsigned int v14; // ebx
  char *v15; // ebp
  char *v16; // ebx
  char *v17; // eax
  Actor *v18; // ecx
  Actor *v19; // eax
  char *v21; // edx
  char *v22; // ebx
  Actor *v23; // eax
  unsigned int v24; // esi
  unsigned int v25; // edx
  char *p_m_actarray_type; // edx
  char *v27; // eax
  char *v28; // edi
  unsigned int v29; // esi
  Actor *m_actarray_end; // ebx
  char *v31; // edx
  Actor *v32; // edx
  char *v33; // eax
  char *v34; // eax
  char *v35; // edi
  int v37; // [esp+0x14] [ebp-0x8]
  Actor *v38; // [esp+0x18] [ebp-0x4]
  char *pPosa; // [esp+0x20] [ebp+0x4]

  v4 = nCount;
  v5 = _this;
  result = (char *)&_this->m_actarray_end->m_actarray_type;
  if ( ((char *)_this->m_actarray_capacity_end - result) >> 6 >= nCount )
  {
    if ( (result - pPos) >> 6 >= nCount )
    {
      if ( !nCount )
        return result;
      v29 = nCount << 6;
      m_actarray_end = _this->m_actarray_end;
      v31 = (char *)&result[-64 * nCount];
      pPosa = (char *)(nCount << 6);
      if ( v31 != result )
      {
        do
        {
          if ( m_actarray_end )
          {
            qmemcpy(m_actarray_end, v31, 0x40u);
            v5 = _this;
          }
          v31 += 64;
          m_actarray_end = (Actor *)((char *)m_actarray_end + 64);
        }
        while ( v31 != result );
        v29 = nCount << 6;
      }
      v32 = (Actor *)v5->m_actarray_end;
      v33 = (char *)(&v32->m_actarray_type - v29);
      if ( pPos != (char *)v32 - v29 )
      {
        do
        {
          v33 -= 64;
          v32 = (Actor *)((char *)v32 - 64);
          qmemcpy(v32, v33, 0x40u);
        }
        while ( v33 != pPos );
        v5 = _this;
      }
      v34 = (char *)pPos;
      if ( pPos == &pPos[(_DWORD)pPosa] )
        goto LABEL_54;
      do
      {
        v35 = (char *)v34;
        v34 += 64;
        qmemcpy(v35, pVal, 0x40u);
      }
      while ( v34 != &pPos[(_DWORD)pPosa] );
    }
    else
    {
      pPosa = (char *)(nCount << 6);
      v21 = (char *)&pPos[64 * nCount];
      if ( pPos != result )
      {
        v22 = (char *)pPos;
        do
        {
          if ( v21 )
          {
            qmemcpy(v21, v22, 0x40u);
            v5 = _this;
            v4 = nCount;
          }
          v22 += 64;
          v21 += 64;
        }
        while ( v22 != result );
      }
      v23 = (Actor *)v5->m_actarray_end;
      v24 = v4 - (((char *)v23 - pPos) >> 6);
      if ( v24 )
      {
        v25 = v24;
        do
        {
          if ( v23 )
          {
            qmemcpy(v23, pVal, 0x40u);
            v5 = _this;
          }
          v23 = (Actor *)((char *)v23 + 64);
          --v25;
        }
        while ( v25 );
      }
      p_m_actarray_type = (char *)&v5->m_actarray_end->m_actarray_type;
      v27 = (char *)pPos;
      if ( pPos == p_m_actarray_type )
        goto LABEL_54;
      do
      {
        v28 = (char *)v27;
        v27 += 64;
        qmemcpy(v28, pVal, 0x40u);
      }
      while ( v27 != p_m_actarray_type );
    }
    v5 = _this;
LABEL_54:
    result = (char *)&pPosa[(unsigned int)v5->m_actarray_end];
    v5->m_actarray_end = (Actor *)result;
    return result;
  }
  m_actarray_begin = _this->m_actarray_begin;
  if ( !m_actarray_begin || (v8 = (result - (char *)m_actarray_begin) >> 6, nCount >= v8) )
    v8 = nCount;
  if ( m_actarray_begin )
    v9 = (result - (char *)m_actarray_begin) >> 6;
  else
    v9 = 0;
  v10 = v8 + v9;
  v37 = v10;
  if ( v10 < 0 )
    v10 = 0;
  v38 = (Actor *)operator new(v10 << 6);
  v11 = (Actor *)v38;
  for ( i = v5->m_actarray_begin; i != (Actor *)pPos; v11 = (Actor *)((char *)v11 + 64) )
  {
    if ( v11 )
    {
      qmemcpy(v11, i, 0x40u);
      v5 = _this;
      v4 = nCount;
    }
    i = (Actor *)((char *)i + 64);
  }
  v13 = (Actor *)v11;
  if ( v4 )
  {
    v14 = v4;
    do
    {
      if ( v13 )
      {
        qmemcpy(v13, pVal, 0x40u);
        v5 = _this;
        v4 = nCount;
      }
      v13 = (Actor *)((char *)v13 + 64);
      --v14;
    }
    while ( v14 );
  }
  v15 = (char *)&v5->m_actarray_end->m_actarray_type;
  v16 = (char *)(&v11->m_actarray_type + 64 * v4);
  if ( pPos != v15 )
  {
    v17 = (char *)pPos;
    do
    {
      if ( v16 )
      {
        qmemcpy(v16, v17, 0x40u);
        v5 = _this;
        v4 = nCount;
      }
      v17 += 64;
      v16 += 64;
    }
    while ( v17 != v15 );
  }
  operator delete(v5->m_actarray_begin);
  v18 = (Actor *)v5->m_actarray_begin;
  v5->m_actarray_capacity_end = (Actor *)((char *)v38 + 64 * v37);
  if ( v18 )
  {
    v19 = (Actor *)v5->m_actarray_end;
    v5->m_actarray_begin = v38;
    result = (char *)(&v38->m_actarray_type + 64 * (v4 + (((char *)v19 - (char *)v18) >> 6)));
  }
  else
  {
    v5->m_actarray_begin = v38;
    result = (char *)(&v38->m_actarray_type + 64 * v4);
  }
  v5->m_actarray_end = (Actor *)result;
  return result;
}

// 0x0053B010
char ** ActVecUninitCopy(int nVal, unsigned int *pdwVal, unsigned int *pdwVal2, char **a4)
{
  int v4; // ebp
  char *v5; // edi
  const void *v6; // esi
  char **v7; // ebp
  unsigned int *v8; // ebx
  unsigned int v9; // esi
  unsigned int v10; // edx
  Actor *v11; // edi
  int v12; // edx
  char *v13; // esi
  int Count; // eax
  char *v15; // eax
  char *v16; // eax
  char *v18; // [esp-0xC] [ebp-0x14]
  int v19; // [esp-0x8] [ebp-0x10]
  unsigned int v20; // [esp+0x4] [ebp-0x4]
  char *i; // [esp+0x4] [ebp-0x4]
  char *v22; // [esp+0x4] [ebp-0x4]

  v6 = (const void *)nVal;
  if ( (unsigned int *)nVal == pdwVal )
    return (char **)pdwVal2;
  v19 = v4;
  v18 = (char *)v5;
  v7 = (char **)(nVal + 136);
  v8 = (unsigned int *)(pdwVal2 + 34);
  while ( 1 )
  {
    qmemcpy(pdwVal2, v6, 0x84u);
    if ( v8 - 1 != (unsigned int *)(v7 - 1) )
    {
      v9 = (unsigned int)*v7;
      if ( *v7 )
        v20 = (int)&v7[1][-v9] / 656;
      else
        v20 = 0;
      if ( *v8 )
        v10 = (int)(v8[1] - *v8) / 656;
      else
        v10 = 0;
      if ( v20 > v10 )
      {
        if ( v9 )
          v9 = (int)&v7[1][-v9] / 656;
        if ( v9 > (((Actor *)(v8 - 1)))->Actor::GetActionCountEx() )
        {
          nullsub_2(*v8, v8[1]);
          operator delete((void *)*v8);
          Count = (((Actor *)(v7 - 1)))->Actor::GetCount();
          if ( Count < 0 )
            Count = 0;
          v15 = (char *)operator new(656 * Count);
          *v8 = (unsigned int)v15;
          v16 = (((Actor *)(v8 - 1)))->Actor::CompareBuffers(*v7, v7[1], v15);
          v8[1] = (unsigned int)v16;
          v8[2] = (unsigned int)v16;
        }
        else
        {
          v22 = (char *)*v7;
          v13 = (char *)&v22[656 * (((Actor *)(v8 - 1)))->Actor::GetCount()];
          ActVecReallocate((int)*v7, v13, (char *)*v8, v18, v19);
          (((Actor *)(v8 - 1)))->Actor::CompareBuffers(v13, v7[1], (char *)v8[1]);
          v8[1] = (unsigned long)(*v8 + 656 * (((Actor *)(v7 - 1)))->Actor::GetCount());
        }
      }
      else
      {
        v11 = (Actor *)*v8;
        for ( i = v7[1]; (char *)v9 != i; v11 = (Actor *)((char *)v11 + 656) )
        {
          SetCurrentAction(v11, v9);
          v9 += 656;
        }
        if ( *v7 )
          v12 = (v7[1] - *v7) / 656;
        else
          v12 = 0;
        v8[1] = (unsigned long)(*v8 + 656 * v12);
      }
    }
    todo_0053BD30((Actor *)(v8 + 3), (int)(v7 + 3));
    v8 += 41;
    pdwVal2 += 41;
    v7 += 41;
    nVal += 164;
    if ( (unsigned int *)nVal == pdwVal )
      break;
    v6 = (const void *)nVal;
  }
  return (char **)pdwVal2;
}

// 0x0053B2D0
int * ActVecUninitCopy2(int nVal, int *p_DWORD, int *p_DWORD2, char **a4)
{
  int v4; // ebp
  char *v5; // esi
  int *result; // eax
  int *v7; // edi
  Actor *v8; // ebp
  char **v9; // ebx
  unsigned int v10; // esi
  unsigned int v11; // edx
  Actor *v12; // edi
  int v13; // eax
  int v14; // edx
  char *v15; // esi
  int Count; // eax
  char *v17; // eax
  char *v18; // eax
  char *v19; // [esp-0xC] [ebp-0x14]
  int v20; // [esp-0x8] [ebp-0x10]
  unsigned int v21; // [esp+0x4] [ebp-0x4]
  int i; // [esp+0x4] [ebp-0x4]
  int v23; // [esp+0x4] [ebp-0x4]

  result = (int *)p_DWORD;
  v7 = (int *)nVal;
  if ( (int *)nVal != p_DWORD )
  {
    v20 = v4;
    v19 = (char *)v5;
    v8 = (Actor *)(p_DWORD2 + 33);
    v9 = (char **)(nVal + 136);
    while ( 1 )
    {
      qmemcpy(v7, p_DWORD2, 0x84u);
      if ( v9 - 1 != (char **)v8 )
      {
        v10 = (unsigned long)p_DWORD2[34];
        if ( v10 )
          v21 = (int)(p_DWORD2[35] - v10) / 656;
        else
          v21 = 0;
        if ( *v9 )
          v11 = (v9[1] - *v9) / 656;
        else
          v11 = 0;
        if ( v21 > v11 )
        {
          if ( v10 )
            v10 = (int)(p_DWORD2[35] - v10) / 656;
          if ( v10 > (((Actor *)(v9 - 1)))->Actor::GetActionCountEx() )
          {
            nullsub_2(*v9, v9[1]);
            operator delete(*v9);
            Count = (((Actor *)v8))->Actor::GetCount();
            if ( Count < 0 )
              Count = 0;
            v17 = (char *)operator new(656 * Count);
            *v9 = v17;
            v18 = (((Actor *)(v9 - 1)))->Actor::CompareBuffers((char *)p_DWORD2[34], (char *)p_DWORD2[35], v17);
            v9[1] = v18;
            v9[2] = v18;
          }
          else
          {
            v23 = (unsigned long)p_DWORD2[34];
            v15 = (char *)(v23 + 656 * (((Actor *)(v9 - 1)))->Actor::GetCount());
            ActVecReallocate(p_DWORD2[34], v15, *v9, v19, v20);
            (((Actor *)(v9 - 1)))->Actor::CompareBuffers(v15, (char *)p_DWORD2[35], v9[1]);
            v9[1] = &(*v9)[656 * (((Actor *)v8))->Actor::GetCount()];
          }
        }
        else
        {
          v12 = (Actor *)*v9;
          for ( i = p_DWORD2[35]; v10 != i; v12 = (Actor *)((char *)v12 + 656) )
          {
            SetCurrentAction(v12, v10);
            v10 += 656;
          }
          v13 = (unsigned long)p_DWORD2[34];
          if ( v13 )
            v14 = (p_DWORD2[35] - v13) / 656;
          else
            v14 = 0;
          v9[1] = &(*v9)[656 * v14];
        }
      }
      todo_0053BD30((Actor *)(v9 + 3), (int)(p_DWORD2 + 37));
      result = (int *)(nVal + 164);
      v9 += 41;
      nVal += 164;
      if ( (int *)nVal == p_DWORD )
        break;
      v7 = (int *)nVal;
    }
  }
  return result;
}

// 0x0053B4D0
char ** ActVecUninitFill(int nVal, int nVal2, int nVal3, char **a4)
{
  int v4; // ebp
  char *v5; // edi
  int v6; // esi
  char **v7; // ebp
  char **v8; // ebx
  unsigned int v9; // esi
  unsigned int v10; // edx
  Actor *v11; // edi
  int v12; // edx
  char *v13; // esi
  int Count; // eax
  char *v15; // eax
  char *v16; // eax
  char *v18; // [esp-0xC] [ebp-0x14]
  int v19; // [esp-0x8] [ebp-0x10]
  unsigned int v20; // [esp+0x4] [ebp-0x4]
  char *i; // [esp+0x4] [ebp-0x4]
  char *v22; // [esp+0x4] [ebp-0x4]
  int nVal2a; // [esp+0x10] [ebp+0x8]

  v6 = nVal2;
  if ( nVal == nVal2 )
    return (char **)nVal3;
  v19 = v4;
  v18 = (char *)v5;
  v7 = (char **)(nVal2 + 136);
  v8 = (char **)(nVal3 + 136);
  while ( 1 )
  {
    nVal2a = v6 - 164;
    v7 -= 41;
    nVal3 -= 164;
    v8 -= 41;
    qmemcpy((void *)nVal3, (const void *)(v6 - 164), 0x84u);
    if ( v8 - 1 != v7 - 1 )
    {
      v9 = (unsigned int)*v7;
      if ( *v7 )
        v20 = (int)&v7[1][-v9] / 656;
      else
        v20 = 0;
      if ( *v8 )
        v10 = (v8[1] - *v8) / 656;
      else
        v10 = 0;
      if ( v20 > v10 )
      {
        if ( v9 )
          v9 = (int)&v7[1][-v9] / 656;
        if ( v9 > (((Actor *)(v8 - 1)))->Actor::GetActionCountEx() )
        {
          nullsub_2(*v8, v8[1]);
          operator delete(*v8);
          Count = (((Actor *)(v7 - 1)))->Actor::GetCount();
          if ( Count < 0 )
            Count = 0;
          v15 = (char *)operator new(656 * Count);
          *v8 = v15;
          v16 = (((Actor *)(v8 - 1)))->Actor::CompareBuffers(*v7, v7[1], v15);
          v8[1] = v16;
          v8[2] = v16;
        }
        else
        {
          v22 = (char *)*v7;
          v13 = (char *)&v22[656 * (((Actor *)(v8 - 1)))->Actor::GetCount()];
          ActVecReallocate((int)*v7, v13, *v8, v18, v19);
          (((Actor *)(v8 - 1)))->Actor::CompareBuffers(v13, v7[1], v8[1]);
          v8[1] = &(*v8)[656 * (((Actor *)(v7 - 1)))->Actor::GetCount()];
        }
      }
      else
      {
        v11 = (Actor *)*v8;
        for ( i = v7[1]; (char *)v9 != i; v11 = (Actor *)((char *)v11 + 656) )
        {
          SetCurrentAction(v11, v9);
          v9 += 656;
        }
        if ( *v7 )
          v12 = (v7[1] - *v7) / 656;
        else
          v12 = 0;
        v8[1] = &(*v8)[656 * v12];
      }
    }
    todo_0053BD30((Actor *)(v8 + 3), (int)(v7 + 3));
    if ( nVal2a == nVal )
      break;
    v6 = nVal2a;
  }
  return (char **)nVal3;
}

// 0x0053B890
char * SetCurrentAction(Actor *_this, int nActionId)
{
  int v4; // ebx
  Actor **p_m_actarray_begin; // eax
  int *p_m_nCachedA; // eax
  int v7; // ecx
  char *v8; // eax
  int v9; // ecx
  gbVec3D *p_m_vecBonePos; // ebp
  signed __int16 *v11; // eax
  float *p_m_fActionAssignParam; // eax
  float *p_m_fFacingAngle; // eax
  int v14; // ecx
  int v16; // [esp+0x10] [ebp-0x4]
  int nActionIda; // [esp+0x18] [ebp+0x4]

  v4 = nActionId - (_DWORD)_this;
  *(_DWORD *)&_this->m_actarray_type = *(_DWORD *)nActionId;
  p_m_actarray_begin = (Actor **)&_this->m_actarray_begin;
  do
  {
    *(_BYTE *)p_m_actarray_begin = *((_BYTE *)p_m_actarray_begin + v4);
    p_m_actarray_begin = (Actor **)((char *)p_m_actarray_begin + 1);
  }
  while ( (unsigned int)p_m_actarray_begin - 4 - (unsigned int)_this < 0x20 );
  LOBYTE(_this->m_pAllocBuf) = *(_BYTE *)(nActionId + 36);
  BYTE1(_this->m_pAllocBuf) = *(_BYTE *)(nActionId + 37);
  _this->m_fTransitionSpeed = *(float *)(nActionId + 40);
  _this->m_fTransitionPos = *(float *)(nActionId + 44);
  _this->m_nRoleParam0 = *(_DWORD *)(nActionId + 48);
  _this->m_fRoleParam1 = *(float *)(nActionId + 52);
  _this->m_fRoleParam = *(float *)(nActionId + 56);
  _this->m_fRoleParam2 = *(float *)(nActionId + 60);
  _this->m_fRoleParam3 = *(float *)(nActionId + 64);
  _this->m_nRoleParam2 = *(_DWORD *)(nActionId + 68);
  _this->m_pRoleParam3 = *(char **)(nActionId + 72);
  p_m_nCachedA = (int *)&_this->m_nCachedA;
  v7 = 6;
  do
  {
    *p_m_nCachedA = *(int *)((char *)p_m_nCachedA + v4);
    ++p_m_nCachedA;
    --v7;
  }
  while ( v7 );
  _this->m_szText = *(_BYTE *)(nActionId + 100);
  *((_WORD *)&_this->m_szText + 1) = *(_WORD *)(nActionId + 102);
  *((_WORD *)&_this->m_szText + 2) = *(_WORD *)(nActionId + 104);
  *((_WORD *)&_this->m_szText + 3) = *(_WORD *)(nActionId + 106);
  *((_WORD *)&_this->m_szText + 4) = *(_WORD *)(nActionId + 108);
  *(&_this->m_szText + 10) = *(_BYTE *)(nActionId + 110);
  v8 = (char *)(&_this->m_szText + 11);
  do
  {
    *v8 = v8[v4];
    ++v8;
  }
  while ( (unsigned int)&v8[-111 - (_DWORD)_this] < 0x10 );
  _this->m_nAnimParam0 = *(_DWORD *)(nActionId + 128);
  v9 = nActionId - (_DWORD)_this;
  _this->m_nAnimParam1 = *(_DWORD *)(nActionId + 132);
  p_m_vecBonePos = (gbVec3D *)&_this->m_vecBonePos;
  v16 = nActionId - (_DWORD)_this;
  nActionIda = 16;
  while ( 1 )
  {
    (((gbVec3D *)p_m_vecBonePos))->gbVec3D::operator=(*((gbVec3D *)((char *)p_m_vecBonePos + v9)));
    ++p_m_vecBonePos;
    if ( !--nActionIda )
      break;
    v9 = v16;
  }
  _this->m_nAnimState = *(_WORD *)(nActionId + 328);
  v11 = (signed __int16 *)(&_this->m_nAnimState + 1);
  do
  {
    *(_BYTE *)v11 = *((_BYTE *)v11 + v4);
    v11 = (signed __int16 *)((char *)v11 + 1);
  }
  while ( (unsigned int)v11 - 330 - (unsigned int)_this < 0x20 );
  BYTE2(_this->m_nHandleEvent) = *(_BYTE *)(nActionId + 362);
  (((gbVec3D *)&_this->m_vecPos))->gbVec3D::operator=(*((const gbVec3D *)(nActionId + 364)));
  (((gbVec3D *)&_this->m_vecRot))->gbVec3D::operator=(*((const gbVec3D *)(nActionId + 376)));
  _this->m_nCloneParam = *(_DWORD *)(nActionId + 388);
  p_m_fActionAssignParam = (float *)&_this->m_fActionAssignParam;
  do
  {
    *(_BYTE *)p_m_fActionAssignParam = *((_BYTE *)p_m_fActionAssignParam + v4);
    p_m_fActionAssignParam = (float *)((char *)p_m_fActionAssignParam + 1);
  }
  while ( (unsigned int)p_m_fActionAssignParam - 392 - (unsigned int)_this < 8 );
  _this->m_nCloneState = *(_DWORD *)(nActionId + 400);
  _this->m_nCloneFlag1 = *(_DWORD *)(nActionId + 404);
  _this->m_nCloneFlag2 = *(_DWORD *)(nActionId + 408);
  p_m_fFacingAngle = (float *)&_this->m_fFacingAngle;
  v14 = 52;
  do
  {
    *p_m_fFacingAngle = *(float *)((char *)p_m_fFacingAngle + v4);
    ++p_m_fFacingAngle;
    --v14;
  }
  while ( v14 );
  *(_DWORD *)&_this->m_curact[35] = *(_DWORD *)(nActionId + 620);
  *(_DWORD *)&_this->m_curact[39] = *(_DWORD *)(nActionId + 624);
  _this->_overlap_RoleSystem_m_partyActor_m_nState = *(_DWORD *)(nActionId + 628);
  _this->m_fDirX = *(float *)(nActionId + 632);
  (((gbVec3D *)&_this->m_fDirY))->gbVec3D::operator=(*((const gbVec3D *)(nActionId + 636)));
  LOBYTE(_this->m_fNormY) = *(_BYTE *)(nActionId + 648);
  BYTE1(_this->m_fNormY) = *(_BYTE *)(nActionId + 649);
  _this->m_fNormZ = *(float *)(nActionId + 652);
  return &_this->m_actarray_type;
}

// 0x0053BD30
int todo_0053BD30(Actor *_this, int a1)
{
  __int16 *v3; // eax
  unsigned int v4; // edi
  Actor *m_actarray_begin; // edx
  unsigned int v6; // ecx
  __int16 *i; // ecx
  __int16 v8; // di
  int v9; // eax
  Actor *v10; // ecx
  int result; // eax
  unsigned int v12; // edi
  unsigned int v13; // ecx
  int v14; // ecx
  __int16 *k; // ecx
  __int16 v16; // di
  __int16 *v17; // edi
  Actor *m_actarray_end; // edx
  __int16 *m; // eax
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  Actor *v23; // eax
  _WORD *v24; // edx
  Actor *v25; // ecx
  _WORD *j; // eax

  if ( _this == (Actor *)a1 )
    return (int)_this;
  v3 = (__int16 *)*(__int16 **)(a1 + 4);
  if ( v3 )
    v4 = (*(_DWORD *)(a1 + 8) - (int)v3) >> 1;
  else
    v4 = 0;
  m_actarray_begin = _this->m_actarray_begin;
  if ( m_actarray_begin )
    v6 = ((char *)_this->m_actarray_end - (char *)m_actarray_begin) >> 1;
  else
    v6 = 0;
  if ( v4 <= v6 )
  {
    for ( i = *(__int16 **)(a1 + 8); v3 != i; m_actarray_begin = (Actor *)((char *)m_actarray_begin + 2) )
    {
      v8 = *v3++;
      *(_WORD *)&m_actarray_begin->m_actarray_type = v8;
    }
    v9 = *(_DWORD *)(a1 + 4);
    if ( v9 )
      v10 = (Actor *)((char *)_this->m_actarray_begin + 2 * ((*(_DWORD *)(a1 + 8) - v9) >> 1));
    else
      v10 = _this->m_actarray_begin;
    result = (int)_this;
    _this->m_actarray_end = v10;
    return result;
  }
  if ( v3 )
    v12 = (*(_DWORD *)(a1 + 8) - (int)v3) >> 1;
  else
    v12 = 0;
  if ( m_actarray_begin )
    v13 = ((char *)_this->m_actarray_capacity_end - (char *)m_actarray_begin) >> 1;
  else
    v13 = 0;
  if ( v12 > v13 )
  {
    operator delete(_this->m_actarray_begin);
    v21 = *(_DWORD *)(a1 + 4);
    if ( v21 )
      v22 = (*(_DWORD *)(a1 + 8) - v21) >> 1;
    else
      v22 = 0;
    if ( v22 < 0 )
      v22 = 0;
    v23 = (Actor *)operator new(2 * v22);
    _this->m_actarray_begin = v23;
    v24 = (_WORD *)*(_WORD **)(a1 + 8);
    v25 = (Actor *)v23;
    for ( j = *(_WORD **)(a1 + 4); j != v24; v25 = (Actor *)((char *)v25 + 2) )
    {
      if ( v25 )
        *(_WORD *)&v25->m_actarray_type = *j;
      ++j;
    }
    _this->m_actarray_end = v25;
    _this->m_actarray_capacity_end = v25;
    return (int)_this;
  }
  if ( m_actarray_begin )
    v14 = ((char *)_this->m_actarray_end - (char *)m_actarray_begin) >> 1;
  else
    v14 = 0;
  for ( k = &v3[v14]; v3 != k; m_actarray_begin = (Actor *)((char *)m_actarray_begin + 2) )
  {
    v16 = *v3++;
    *(_WORD *)&m_actarray_begin->m_actarray_type = v16;
  }
  v17 = (__int16 *)*(__int16 **)(a1 + 8);
  m_actarray_end = _this->m_actarray_end;
  for ( m = k; m != v17; m_actarray_end = (Actor *)((char *)m_actarray_end + 2) )
  {
    if ( m_actarray_end )
      *(_WORD *)&m_actarray_end->m_actarray_type = *m;
    ++m;
  }
  v20 = *(_DWORD *)(a1 + 4);
  if ( v20 )
    _this->m_actarray_end = (Actor *)((char *)_this->m_actarray_begin + 2 * ((*(_DWORD *)(a1 + 8) - v20) >> 1));
  else
    _this->m_actarray_end = _this->m_actarray_begin;
  return (int)_this;
}

// 0x0053BEE0
char * ActVecReallocate(int nVal, char *pszBuf, char *pszBuf2, char *pszBuf3, int nVal2)
{
  char *v5; // ebx
  char *v6; // ecx
  char *v7; // esi
  int v8; // edi
  int v9; // ebx
  char *v10; // eax
  char *v11; // edx
  char *v12; // eax
  int v13; // edx
  char *v14; // eax
  int v15; // eax
  gbVec3D *v16; // ebp
  char *v17; // eax
  char *v18; // eax
  char *v19; // eax
  int v20; // ecx
  char v21; // dl
  int v23; // [esp+0x4] [ebp-0x8]

  v5 = (char *)nVal;
  if ( (char *)nVal == pszBuf )
    return pszBuf2;
  v6 = (char *)pszBuf2;
  v7 = (char *)(pszBuf2 + 632);
  v8 = nVal + 632;
  while ( 1 )
  {
    *(_DWORD *)v6 = *(_DWORD *)v5;
    v9 = (int)v5 - v6;
    v10 = (char *)(v7 - 628);
    do
    {
      *v10 = v10[v9];
      ++v10;
    }
    while ( (unsigned int)&v10[-4 - (_DWORD)v6] < 0x20 );
    *(v7 - 596) = *(_BYTE *)(v8 - 596);
    *(v7 - 595) = *(_BYTE *)(v8 - 595);
    *((_DWORD *)v7 - 148) = *(_DWORD *)(v8 - 592);
    *((_DWORD *)v7 - 147) = *(_DWORD *)(v8 - 588);
    *((_DWORD *)v7 - 146) = *(_DWORD *)(v8 - 584);
    *((_DWORD *)v7 - 145) = *(_DWORD *)(v8 - 580);
    v11 = (char *)(v7 - 576);
    *(_DWORD *)v11 = *(_DWORD *)(v8 - 576);
    *((_DWORD *)v11 + 1) = *(_DWORD *)(v8 - 576 + 4);
    *((_DWORD *)v11 + 2) = *(_DWORD *)(v8 - 576 + 8);
    *((_DWORD *)v11 + 3) = *(_DWORD *)(v8 - 576 + 12);
    *(v7 - 560) = *(_BYTE *)(v8 - 560);
    *(v7 - 559) = *(_BYTE *)(v8 - 559);
    *(v7 - 558) = *(_BYTE *)(v8 - 558);
    *(v7 - 557) = *(_BYTE *)(v8 - 557);
    v12 = (char *)(v7 - 556);
    v13 = 6;
    do
    {
      *(_DWORD *)v12 = *(_DWORD *)&v12[v9];
      v12 += 4;
      --v13;
    }
    while ( v13 );
    *(v7 - 532) = *(_BYTE *)(v8 - 532);
    *((_WORD *)v7 - 265) = *(_WORD *)(v8 - 530);
    *((_WORD *)v7 - 264) = *(_WORD *)(v8 - 528);
    *((_WORD *)v7 - 263) = *(_WORD *)(v8 - 526);
    *((_WORD *)v7 - 262) = *(_WORD *)(v8 - 524);
    *(v7 - 522) = *(_BYTE *)(v8 - 522);
    v14 = (char *)(v7 - 521);
    do
    {
      *v14 = v14[v9];
      ++v14;
    }
    while ( (unsigned int)&v14[-111 - (_DWORD)v6] < 0x10 );
    *((_DWORD *)v7 - 126) = *(_DWORD *)(v8 - 504);
    *((_DWORD *)v7 - 125) = *(_DWORD *)(v8 - 500);
    v15 = v8 - (_DWORD)v7;
    v16 = (gbVec3D *)(v7 - 496);
    v23 = 16;
    while ( 1 )
    {
      (((gbVec3D *)v16))->gbVec3D::operator=(*((gbVec3D *)((char *)v16 + v15)));
      ++v16;
      if ( !--v23 )
        break;
      v15 = v8 - (_DWORD)v7;
    }
    *((_WORD *)v7 - 152) = *(_WORD *)(v8 - 304);
    v17 = (char *)(v7 - 302);
    do
    {
      *v17 = v17[v9];
      ++v17;
    }
    while ( (unsigned int)&v17[-330 - (_DWORD)pszBuf2] < 0x20 );
    *(v7 - 270) = *(_BYTE *)(v8 - 270);
    (((gbAABBox *)(v7 - 268)))->gbAABBox::operator=(*((const gbAABBox *)(v8 - 268)));
    *((_DWORD *)v7 - 61) = *(_DWORD *)(v8 - 244);
    v18 = (char *)(v7 - 240);
    do
    {
      *v18 = v18[v9];
      ++v18;
    }
    while ( (unsigned int)&v18[-392 - (_DWORD)pszBuf3] < 8 );
    *((_DWORD *)v7 - 58) = *(_DWORD *)(v8 - 232);
    *((_DWORD *)v7 - 57) = *(_DWORD *)(v8 - 228);
    *((_DWORD *)v7 - 56) = *(_DWORD *)(v8 - 224);
    v19 = (char *)(v7 - 220);
    v20 = 52;
    do
    {
      *(_DWORD *)v19 = *(_DWORD *)&v19[v9];
      v19 += 4;
      --v20;
    }
    while ( v20 );
    *((_DWORD *)v7 - 3) = *(_DWORD *)(v8 - 12);
    *((_DWORD *)v7 - 2) = *(_DWORD *)(v8 - 8);
    *((_DWORD *)v7 - 1) = *(_DWORD *)(v8 - 4);
    *(_DWORD *)v7 = *(_DWORD *)v8;
    (((gbVec3D *)(v7 + 4)))->gbVec3D::operator=(*((const gbVec3D *)(v8 + 4)));
    v21 = *(_BYTE *)(v8 + 16);
    v8 += 656;
    v7[16] = v21;
    v7[17] = *(_BYTE *)(v8 - 639);
    pszBuf2 += 656;
    *((_DWORD *)v7 + 5) = *(_DWORD *)(v8 - 636);
    v7 += 656;
    nVal += 656;
    if ( (char *)nVal == pszBuf )
      break;
    v5 = (char *)nVal;
    v6 = (char *)pszBuf2;
  }
  return pszBuf2;
}

// 0x0053CF30
char * TextureInfoFormatException(
        char *ArgList,
        const char *pszName,
        const char *pszName2,
        const char *pszName3,
        int nVal)
{
  char *v5; // ecx
  const char *v6; // esi

  v6 = (const char *)v5;
  v5[1023] = 0;
  _snprintf(v5, 0x400u, "%s(%d):%s,%s", pszName2, pszName3, ArgList, pszName);
  LogMessage("_Exception: %s\r\n", v6);
  return (char *)v6;
}

// 0x0053CF80
FILE * InitLogFiles()
{
  FILE *v0; // esi
  FILE *result; // eax
  FILE *v2; // edi
  CHAR Filename[512]; // [esp+0x8] [ebp-0x200] BYREF

  v0 = fopen("Pal3Log.txt", "wt");
  result = fopen("EngineLog.txt", "wt");
  v2 = (FILE *)result;
  if ( v0 )
  {
    if ( result )
    {
      GetModuleFileNameA(0, Filename, 0x200u);
      fprintf(v0, "[%s Log at ", Filename);
      _strdate(Filename);
      fprintf(v0, Filename);
      _strtime(Filename);
      fprintf(v0, " %s]\r\n\r\n", Filename);
      fclose(v0);
      fprintf(v2, "Log At:%s\r\n", Filename);
      return (FILE *)fclose(v2);
    }
  }
  return result;
}

// 0x0053D030
FILE *LogMessage(char *Format, ...)
{
  FILE *result; // eax
  FILE *v2; // esi
  va_list ArgList; // [esp+0xC] [ebp+0x8] BYREF

  va_start(ArgList, Format);
  vsprintf(byte_17B3AAC, Format, ArgList);
  result = fopen("Pal3Log.txt", "at");
  v2 = (FILE *)result;
  if ( result )
  {
    fprintf(result, byte_17B3AAC);
    return (FILE *)fclose(v2);
  }
  return result;
}

// 0x0053D190
// Microsoft VisualC 2-14/net runtime
void RefreshSoundListBox()
{
  (((UIListBox *)&stru_17B3EB0))->UIListBox::RefreshList();
}

// 0x0053D5D0
void RenderActorGeometry(Actor *_this, int nRenderFlag)
{
  gbGeomQuad *v3; // edi
  int v4; // ebx
  gbDynVertBuf *DynVertBuf; // edi
  gbMatrixStack *v6; // ebp
  gbMatrix4 *Top; // eax
  float v8; // ecx
  gbTexture *m_nRoleState0; // edx
  double v10; // st6
  float v11; // eax
  double v12; // st6
  gbRenderEffect *v13; // edx
  gbTexture *v14; // ecx
  double v15; // st7
  double v16; // st5
  float v17; // eax
  double v18; // st7
  double v19; // st6
  float v20; // ecx
  float v21; // edx
  double v22; // st6
  gbRenderEffect *v23; // eax
  float m_fAnimParam; // edx
  double v25; // st7
  double v26; // st7
  double v27; // st6
  float v28; // ecx
  float v29; // edx
  double v30; // st7
  double v31; // st6
  gbRenderEffect *v32; // edx
  double v33; // st7
  double v34; // st6
  double v35; // st6
  double v36; // st5
  float v37; // eax
  gbRenderEffect *v38; // eax
  float v39; // eax
  gbTexture *v40; // edx
  double v41; // st6
  double v42; // st6
  double v43; // st5
  float v44; // eax
  float v45; // edx
  double v46; // st6
  double v47; // st6
  gbRenderEffect *v48; // ecx
  float v49; // edx
  gbTexture *v50; // eax
  double v51; // st6
  double v52; // st6
  double v53; // st5
  gbRenderEffect *v54; // edx
  int m_nModelId; // [esp+0x58] [ebp-0x98]
  float v56; // [esp+0x58] [ebp-0x98]
  int v57; // [esp+0x58] [ebp-0x98]
  float v58; // [esp+0x58] [ebp-0x98]
  float v59; // [esp+0x58] [ebp-0x98]
  float v60; // [esp+0x58] [ebp-0x98]
  float v61; // [esp+0x58] [ebp-0x98]
  float v62; // [esp+0x58] [ebp-0x98]
  int v63; // [esp+0x58] [ebp-0x98]
  float v64; // [esp+0x58] [ebp-0x98]
  float v65; // [esp+0x58] [ebp-0x98]
  float v66; // [esp+0x5C] [ebp-0x94]
  float v67; // [esp+0x5C] [ebp-0x94]
  float v68; // [esp+0x5C] [ebp-0x94]
  float v69; // [esp+0x5C] [ebp-0x94]
  float v70; // [esp+0x5C] [ebp-0x94]
  float v71; // [esp+0x5C] [ebp-0x94]
  float v72; // [esp+0x5C] [ebp-0x94]
  float v73; // [esp+0x5C] [ebp-0x94]
  float v74; // [esp+0x5C] [ebp-0x94]
  float v75; // [esp+0x5C] [ebp-0x94]
  float v76; // [esp+0x60] [ebp-0x90]
  float v77; // [esp+0x60] [ebp-0x90]
  float v78; // [esp+0x60] [ebp-0x90]
  float v79; // [esp+0x60] [ebp-0x90]
  float v80; // [esp+0x60] [ebp-0x90]
  float v81; // [esp+0x64] [ebp-0x8C]
  float v82; // [esp+0x64] [ebp-0x8C]
  float v83; // [esp+0x64] [ebp-0x8C]
  float v84; // [esp+0x64] [ebp-0x8C]
  float v85; // [esp+0x64] [ebp-0x8C]
  struct gbGeomQuad v86; // [esp+0x68] [ebp-0x88] BYREF
  struct gbTextureArray v87; // [esp+ACh] [ebp-0x44] BYREF

  v87.nTex = 1;
  v3 = (gbGeomQuad *)&v86;
  v4 = 4;
  do
  {
    v3 = (gbGeomQuad *)((char *)v3 + 12);
    --v4;
  }
  while ( v4 );
  v86.sv = 0.001953125;
  v86.su = 0.001953125;
  v86.ev = 0.99804688;
  v86.eu = 0.99804688;
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x15u);
  v6 = gfxMgr->pMatrixStack[1];
  (((gbMatrixStack *)v6))->gbMatrixStack::Push();
  (((gbGfxManager *)gfxMgr))->gbGfxManager::IdentityWorldMatrix();
  Top = (((gbMatrixStack *)v6))->gbMatrixStack::GetTop();
  Top->tz = 0.0f;
  Top->ty = 0.0f;
  Top->tx = 0.0f;
  Top->tw = 1.0f;
  (((gbMatrixStack *)v6))->gbMatrixStack::LoadMatrix(Top);
  v76 = -*(float *)&_this->m_nModelId;
  v8 = *((float *)&_this->m_nModelId + 1);
  m_nRoleState0 = (gbTexture *)_this->m_nRoleState0;
  v86.vec[0].x = -*(float *)&_this->m_pResource;
  v87.pTexPt[0] = m_nRoleState0;
  v81 = -*((float *)&_this->m_nModelId + 1);
  v86.vec[0].y = v76;
  v86.vec[1].x = v86.vec[0].x;
  m_nModelId = _this->m_nModelId;
  v86.vec[0].z = v8;
  v86.vec[2].x = v86.vec[0].x;
  v10 = *(float *)&_this->m_nModelId;
  v86.vec[1].y = v76;
  v11 = *(float *)&m_nModelId;
  v86.vec[1].z = v81;
  v56 = v10;
  v12 = *((float *)&_this->m_nModelId + 1);
  v86.vec[2].z = v81;
  v66 = v12;
  v86.vec[3].y = v56;
  v13 = (gbRenderEffect *)*(&_this->m_nModelId + 2);
  v86.vec[3].x = v86.vec[0].x;
  v86.vec[2].y = v11;
  v86.vec[3].z = v66;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v86, 1, v13, &v87);
  v77 = -*(float *)&_this->m_nModelId;
  v67 = *((float *)&_this->m_nModelId + 1);
  v14 = (gbTexture *)(*(gbTexture **)&_this->m_bUIFlagA);
  v86.vec[0].x = *(float *)&_this->m_pResource;
  v15 = -*(float *)&_this->m_pResource;
  v16 = *((float *)&_this->m_nModelId + 1);
  v87.pTexPt[0] = v14;
  v86.vec[0].z = v67;
  v68 = v16;
  v17 = v68;
  v86.vec[1].x = v15;
  v57 = _this->m_nModelId;
  v69 = *((float *)&_this->m_nModelId + 1);
  v86.vec[0].y = v77;
  v86.vec[2].x = v15;
  v18 = *(float *)&_this->m_pResource;
  v19 = *(float *)&_this->m_nModelId;
  v20 = *(float *)&v57;
  v86.vec[1].y = v77;
  v21 = v69;
  v86.vec[1].z = v17;
  v58 = v19;
  v22 = *((float *)&_this->m_nModelId + 1);
  v86.vec[2].y = v20;
  v70 = v22;
  v86.vec[2].z = v21;
  v86.vec[3].x = v18;
  v86.vec[3].y = v58;
  v23 = (gbRenderEffect *)*(&_this->m_nModelId + 2);
  v86.vec[3].z = v70;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v86, 1, v23, &v87);
  v78 = -*(float *)&_this->m_nModelId;
  m_fAnimParam = _this->m_fAnimParam;
  v82 = -*((float *)&_this->m_nModelId + 1);
  v86.vec[0].x = *(float *)&_this->m_pResource;
  *(float *)v87.pTexPt = m_fAnimParam;
  v25 = *(float *)&_this->m_pResource;
  v71 = *((float *)&_this->m_nModelId + 1);
  v86.vec[0].z = v82;
  v86.vec[1].x = v25;
  v26 = *(float *)&_this->m_pResource;
  v27 = *(float *)&_this->m_nModelId;
  v28 = v71;
  v86.vec[0].y = v78;
  v59 = v27;
  v72 = *((float *)&_this->m_nModelId + 1);
  v29 = v59;
  v86.vec[2].x = v26;
  v30 = *(float *)&_this->m_pResource;
  v31 = *(float *)&_this->m_nModelId;
  v86.vec[1].y = v78;
  v86.vec[1].z = v28;
  v60 = v31;
  v86.vec[2].y = v29;
  v86.vec[2].z = v72;
  v86.vec[3].x = v30;
  v86.vec[3].y = v60;
  v32 = (gbRenderEffect *)*(&_this->m_nModelId + 2);
  v86.vec[3].z = v82;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v86, 1, v32, &v87);
  v33 = -*(float *)&_this->m_pResource;
  v79 = -*(float *)&_this->m_nModelId;
  v83 = -*((float *)&_this->m_nModelId + 1);
  v87.pTexPt[0] = *(gbTexture **)&_this->m_szText;
  v86.vec[0].x = v33;
  v34 = *(float *)&_this->m_pResource;
  v86.vec[0].y = v79;
  v86.vec[0].z = v83;
  v86.vec[1].x = v34;
  v35 = *(float *)&_this->m_pResource;
  v36 = *(float *)&_this->m_nModelId;
  v86.vec[1].y = v79;
  v86.vec[1].z = v83;
  v61 = v36;
  v37 = v61;
  v86.vec[2].x = v35;
  v62 = *(float *)&_this->m_nModelId;
  v86.vec[2].y = v37;
  v86.vec[3].y = v62;
  v38 = (gbRenderEffect *)*(&_this->m_nModelId + 2);
  v86.vec[3].x = v33;
  v86.vec[2].z = v83;
  v86.vec[3].z = v83;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v86, 1, v38, &v87);
  v84 = -*((float *)&_this->m_nModelId + 1);
  v39 = *(float *)&_this->m_nModelId;
  v40 = (gbTexture *)*((_DWORD *)&_this->m_szText + 1);
  v86.vec[0].x = -*(float *)&_this->m_pResource;
  v41 = *(float *)&_this->m_pResource;
  v63 = _this->m_nModelId;
  v86.vec[0].y = v39;
  v86.vec[1].x = v41;
  v42 = *(float *)&_this->m_pResource;
  v43 = *(float *)&_this->m_nModelId;
  v44 = *(float *)&v63;
  v87.pTexPt[0] = v40;
  v86.vec[0].z = v84;
  v64 = v43;
  v73 = *((float *)&_this->m_nModelId + 1);
  v45 = v64;
  v86.vec[1].y = v44;
  v86.vec[2].x = v42;
  v46 = *(float *)&_this->m_nModelId;
  v86.vec[1].z = v84;
  v65 = v46;
  v47 = *((float *)&_this->m_nModelId + 1);
  v86.vec[2].z = v73;
  v74 = v47;
  v86.vec[2].y = v45;
  v86.vec[3].x = v86.vec[0].x;
  v86.vec[3].y = v65;
  v48 = (gbRenderEffect *)*(&_this->m_nModelId + 2);
  v86.vec[3].z = v74;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v86, 1, v48, &v87);
  v80 = -*(float *)&_this->m_nModelId;
  v49 = *((float *)&_this->m_nModelId + 1);
  v50 = (gbTexture *)*((_DWORD *)&_this->m_szText + 2);
  v86.vec[0].x = -*(float *)&_this->m_pResource;
  v51 = *(float *)&_this->m_pResource;
  v75 = *((float *)&_this->m_nModelId + 1);
  v87.pTexPt[0] = v50;
  v86.vec[1].x = v51;
  v52 = *(float *)&_this->m_pResource;
  v53 = *((float *)&_this->m_nModelId + 1);
  v86.vec[0].z = v49;
  v86.vec[0].y = v80;
  v85 = -v53;
  v86.vec[1].z = v75;
  v86.vec[2].x = v52;
  v86.vec[1].y = v80;
  v86.vec[2].y = v80;
  v86.vec[2].z = v85;
  v86.vec[3].x = v86.vec[0].x;
  v86.vec[3].y = v80;
  v54 = (gbRenderEffect *)*(&_this->m_nModelId + 2);
  v86.vec[3].z = v85;
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderGeomQuad(&v86, 1, v54, &v87);
  (((gbMatrixStack *)v6))->gbMatrixStack::Pop();
}

// 0x0053EDD0
int nearby_53edd0(int a1)
{
  return a1 - 1;
}

// 0x00540070
int crt_sub_00540070()
{
  gbDynVertBuf *DynVertBuf; // eax
  int result; // eax
  struct gbUIQuad v2; // [esp+0x4] [ebp-0x28] BYREF
  int v3; // [esp+0x30] [ebp+0x4]
  int v4; // [esp+0x34] [ebp+0x8]
  int v5; // [esp+0x38] [ebp+0xC]
  int v6; // [esp+0x3C] [ebp+0x10]
  unsigned int *v7; // [esp+0x40] [ebp+0x14]

  v2.z = 0.0;
  v2.sx = (float)v3;
  v2.color = *v7;
  v2.ey = (float)v4;
  v2.ex = (float)v5;
  v2.sy = (float)v6;
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad(&v2, 1, g_pRenderEffect_1895050, 0);
  return result;
}

// 0x00540D20
int crt_sub_00540D20()
{
  gbDynVertBuf *DynVertBuf; // eax
  int result; // eax
  struct gbUIQuad v2; // [esp+0x4] [ebp-0x28] BYREF
  int v3; // [esp+0x30] [ebp+0x4]
  int v4; // [esp+0x34] [ebp+0x8]
  int v5; // [esp+0x38] [ebp+0xC]
  int v6; // [esp+0x3C] [ebp+0x10]
  float v7; // [esp+0x40] [ebp+0x14]
  unsigned int *v8; // [esp+0x48] [ebp+0x1C]
  gbTextureArray *v9; // [esp+0x4C] [ebp+0x20]

  v2.z = 0.0;
  v2.su = 0.0;
  v2.ey = (float)v4;
  v2.color = *v8;
  v2.sv = v7;
  v2.ex = (float)v5;
  v2.eu = 1.0;
  v2.ev = 0.0;
  v2.sy = (float)v6;
  v2.sx = (double)v3 - -0.5;
  v2.ex = v2.ex - -0.5;
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad(&v2, 1, (gbRenderEffect *)g_pTexColorEffect, v9);
  return result;
}

// 0x00540DC0
int crt_sub_00540DC0()
{
  unsigned int v0; // ecx
  gbTexture *v1; // ecx
  long double v2; // st7
  gbTexture *v3; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  gbDynVertBuf *DynVertBuf; // eax
  int result; // eax
  struct gbUIQuad v9; // [esp+0x14] [ebp-0x28] BYREF
  int v10; // [esp+0x40] [ebp+0x4]
  int v11; // [esp+0x44] [ebp+0x8]
  int v12; // [esp+0x48] [ebp+0xC]
  int v13; // [esp+0x4C] [ebp+0x10]
  unsigned int *v14; // [esp+0x50] [ebp+0x14]
  gbTextureArray *v15; // [esp+0x54] [ebp+0x18]
  int v16; // [esp+0x58] [ebp+0x1C]
  char v17; // [esp+0x5C] [ebp+0x20]

  v0 = (unsigned long)*v14;
  v9.z = 0.0;
  v9.color = v0;
  if ( !v16 )
  {
    v3 = (gbTexture *)v15->pTexPt[0];
    v9.sv = 0.0;
    v9.su = 0.0;
    v9.eu = (fabs((double)(v12 - v10)) + -0.5) / (double)v3->Width;
    v2 = (fabs((double)(v13 - v11)) + -0.5) / (double)v3->Height;
    goto LABEL_6;
  }
  v9.su = *(float *)(v16 + 1048);
  v9.sv = *(float *)(v16 + 1052);
  if ( !v17 )
  {
    v1 = (gbTexture *)v15->pTexPt[0];
    v9.eu = (fabs((double)(v12 - v10)) + -0.5) / (double)v15->pTexPt[0]->Width + v9.su;
    v2 = (fabs((double)(v13 - v11)) + -0.5) / (double)v1->Height + v9.sv;
LABEL_6:
    v9.ev = v2;
    goto LABEL_7;
  }
  v9.eu = *(float *)(v16 + 1064);
  v9.ev = *(float *)(v16 + 1068);
LABEL_7:
  v4 = (double)v10;
  v9.ey = (float)v11;
  if ( v16 && v17 )
  {
    v5 = (double)*(unsigned int *)(v16 + 1040) + v4;
    v6 = (double)*(unsigned int *)(v16 + 1044) + v9.ey;
  }
  else
  {
    v5 = (double)v12;
    v6 = (double)v13;
  }
  v9.sy = v6;
  v9.sx = v4 - -0.5;
  v9.ex = v5 - -0.5;
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(0x114u);
  (((gbDynVertBuf *)DynVertBuf))->gbDynVertBuf::RenderUIQuad(&v9, 1, g_pRenderEffect_1895060, v15);
  return result;
}

// 0x00540FD0
int crt_sub_00540FD0()
{
  int result; // eax
  int v1; // eax
  gbPrintFont *v2; // esi
  bool v3; // cc
  bool v4; // cc
  float v5; // st7
  float v6; // st6
  float v7; // [esp+0x0] [ebp-0x20]
  float v8; // [esp+0x4] [ebp-0x1C]
  int v9; // [esp+0x24] [ebp+0x4]
  int v10; // [esp+0x28] [ebp+0x8]
  int v11; // [esp+0x28] [ebp+0x8]
  int v12; // [esp+0x2C] [ebp+0xC]
  _BYTE *v13; // [esp+0x30] [ebp+0x10]
  int v14; // [esp+0x34] [ebp+0x14]
  unsigned int v15; // [esp+0x34] [ebp+0x14]

  if ( !v12 )
    return result;
  v1 = v14;
  v2 = 0;
  v11 = v14 + v10;
  if ( v14 > 24 )
    goto LABEL_15;
  if ( v14 >= 12 )
  {
    if ( v14 <= 12 )
    {
      v3 = v14 <= 16;
    }
    else
    {
      v3 = v14 <= 16;
      if ( v14 < 16 )
      {
        v1 = 16;
        goto LABEL_16;
      }
    }
    if ( v3 )
    {
      v4 = v14 <= 20;
    }
    else
    {
      v4 = v14 <= 20;
      if ( v14 < 20 )
      {
        v1 = 20;
        goto LABEL_16;
      }
    }
    if ( v4 || v14 >= 24 )
      goto LABEL_17;
LABEL_15:
    v1 = 24;
    goto LABEL_16;
  }
  v1 = 12;
LABEL_16:
  v14 = v1;
LABEL_17:
  switch ( v1 )
  {
    case 12:
      v2 = gfxMgr->pFontMgr->pAllFont[0];
      break;
    case 16:
      v2 = gfxMgr->pFontMgr->pAllFont[1];
      break;
    case 20:
      v2 = gfxMgr->pFontMgr->pAllFont[2];
      break;
    case 24:
      v2 = gfxMgr->pFontMgr->pAllFont[3];
      break;
    default:
      break;
  }
  v5 = (float)v14 + (float)v14;
  v6 = v5 / (float)g_DrvInfo.height;
  v2->ScaleX = v5 / (float)g_DrvInfo.width;
  v2->ScaleY = v6;
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v15) = (unsigned long)*v13;
    BYTE1(v15) = (unsigned long)v13[1];
    LOBYTE(v15) = (unsigned long)v13[2];
  }
  else
  {
    *(_WORD *)((char *)&v15 + 1) = *(_WORD *)(v13 + 1);
    LOBYTE(v15) = (unsigned long)*v13;
  }
  HIBYTE(v15) = (unsigned long)v13[3];
  v2->curColor.Color = v15;
  v8 = 1.0f - ((float)v11 + (float)v11) / (float)g_DrvInfo.height;
  v7 = ((float)v9 + (float)v9) / (float)g_DrvInfo.width - 1.0f;
  ((void ( *)(gbPrintFont *, int, _DWORD, _DWORD, int, int))v2->pGfxMgr->DrvInfo.subtype)(
    v2,
    v12,
    LODWORD(v7),
    LODWORD(v8),
    1176256512,
    1176256512);
  return ((int ( *)(gbPrintFont *))v2->pGfxMgr->hGfxWnd)(v2);
}

// 0x00541160
int UIRenderPar(int nX, int nY, int nW, int nH, gbColorQuad *pColor, gbTextureArray *pTex, _PlugInfo *pInfo)
{
  gbPrintFont *v7; // edi
  int nHa; // [esp+0x20] [ebp+0x10]

  v7 = gfxMgr->pFontMgr->pAllFont[nH];
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(nHa) = *(_BYTE *)nW;
    BYTE1(nHa) = *(_BYTE *)(nW + 1);
    LOBYTE(nHa) = *(_BYTE *)(nW + 2);
  }
  else
  {
    *(_WORD *)((char *)&nHa + 1) = *(_WORD *)(nW + 1);
    LOBYTE(nHa) = *(_BYTE *)nW;
  }
  HIBYTE(nHa) = *(_BYTE *)(nW + 3);
  v7->curColor.Color = nHa;
  return crt_sub_00541210();
}

// 0x00541210
int crt_sub_00541210()
{
  int result; // eax
  int v1; // ebp
  unsigned int v2; // kr10_4
  int v3; // ecx
  int v4; // edi
  bool v5; // zf
  float v6; // st7
  float v7; // st6
  int v8; // esi
  int *v9; // ebx
  char v10; // al
  int v11; // edi
  char v12; // al
  char v13; // cl
  int v14; // ebx
  unsigned int v15; // kr18_4
  float v16; // [esp+0x0] [ebp-0x40]
  float v17; // [esp+0x4] [ebp-0x3C]
  int v18; // [esp+0x20] [ebp-0x20]
  int v19; // [esp+0x24] [ebp-0x1C]
  int v20; // [esp+0x28] [ebp-0x18]
  int v21; // [esp+0x2C] [ebp-0x14]
  int v22; // [esp+0x30] [ebp-0x10]
  int v23; // [esp+0x34] [ebp-0xC]
  const char *v24; // [esp+0x44] [ebp+0x4]
  int *v25; // [esp+0x48] [ebp+0x8]
  float *v26; // [esp+0x4C] [ebp+0xC]
  int v27; // [esp+0x50] [ebp+0x10]
  int v28; // [esp+0x54] [ebp+0x14] BYREF

  v1 = 0;
  if ( v24 )
  {
    if ( v26 )
    {
      result = 0;
      v2 = strlen(v24) + 1;
      v3 = v2 - 1;
      if ( (int)(v2 - 1) > 0 )
      {
        v4 = 1;
        v5 = v28 == 1;
        v6 = (float)v27 + (float)v27;
        v18 = 0;
        v21 = 0;
        v22 = 0;
        v7 = v6 / (float)g_DrvInfo.height;
        v26[12] = v6 / (double)g_DrvInfo.width;
        v26[13] = v7;
        v8 = v27;
        v9 = (int *)v25;
        if ( v5 )
        {
          v21 = (v25[2] - v27 * v3 / 2 - *v25) / 2;
          v22 = (v25[3] - v25[1] - v27) / 2;
        }
        v20 = 1;
        v19 = v27;
        while ( 1 )
        {
          v10 = v24[v1];
          if ( v10 == 92 )
          {
            ++v1;
            v11 = v4 + 1;
            if ( v1 >= v3 )
              return (*(int ( **)(float *))(*(_DWORD *)v26 + 8))(v26);
            v12 = v24[v1];
            if ( v12 == 110 )
            {
              v18 = 0;
              v19 += v8;
            }
            else if ( v12 == 116 )
            {
              v18 = 8 * ((v18 + 8) / 8);
            }
          }
          else
          {
            LOWORD(v28) = 0;
            BYTE2(v28) = 0;
            if ( v10 <= 0 || v10 == 127 )
            {
              if ( v4 >= v3 )
                return (*(int ( **)(float *))(*(_DWORD *)v26 + 8))(v26);
              LOBYTE(v28) = v10;
              v13 = v24[++v1];
              BYTE1(v28) = v13;
              v20 = v4 + 1;
            }
            else
            {
              LOBYTE(v28) = v10;
            }
            v14 = (unsigned long)*v9;
            v23 = v21 + v14 + v8 * v18 / 2;
            if ( (int)(v23 + v27 / 2 * strlen((const char *)&v28)) > v25[2] )
            {
              v18 = 0;
              v23 = v14;
              v19 += v27;
            }
            if ( v22 + v19 + v25[1] > v25[3] )
              return (*(int ( **)(float *))(*(_DWORD *)v26 + 8))(v26);
            v17 = 1.0f - ((float)(v22 + v19 + v25[1]) + (float)(v22 + v19 + v25[1])) / (float)g_DrvInfo.height;
            v16 = ((float)v23 + (float)v23) / (float)g_DrvInfo.width - 1.0f;
            (*(void ( **)(int *, _DWORD, _DWORD, int, int))(*(_DWORD *)v26 + 16))(
              &v28,
              LODWORD(v16),
              LODWORD(v17),
              1176256512,
              1176256512);
            v8 = v27;
            v15 = strlen((const char *)&v28) + 1;
            v9 = (int *)v25;
            v11 = v20;
            v3 = v2 - 1;
            v18 += v15 - 1;
          }
          ++v1;
          v4 = v11 + 1;
          v20 = v4;
          if ( v1 >= v3 )
            return (*(int ( **)(float *))(*(_DWORD *)v26 + 8))(v26);
        }
      }
    }
  }
  return result;
}

// 0x00541590
int crt_sub_00541590()
{
  int v0; // ecx
  int result; // eax
  char v2; // cl
  int v3; // [esp+0x4] [ebp+0x4]

  result = v0;
  if ( v3 != *(_DWORD *)(v0 + 12) )
  {
    v2 = *(_BYTE *)(v0 + 29);
    *(_DWORD *)(result + 12) = v3;
    if ( !v2 )
      return (*(int ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)*(void**)(gfxMgr) + 100))(
               gfxMgr,
               *(_DWORD *)(result + 4 * v3));
  }
  return result;
}

// 0x00541630
// Microsoft VisualC 2-14/net runtime
void InitUIQuadManagerSingleton()
{
  crt_sub_00541490(&((TextureLibDataBase *)&stru_1894B78)->_isLoadTLI + 4);
}

// 0x00541900
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  HWND WindowA; // esi
  BOOL i; // eax
  char *v7; // eax
  void *v8; // esi
  double v9; // st7
  PAL3 *v10; // ecx
  int v11; // edx
  CCBSystem *v12; // edi
  HWND ActiveWindow; // eax
  PAL3 *v14; // ecx
  PAL3 *v15; // ecx
  int v16; // [esp+0x0] [ebp-0x698] BYREF
  CHAR Text[256]; // [esp+0x40C] [ebp-0x28C] BYREF
  char Buffer[324]; // [esp+0x50C] [ebp-0x18C] BYREF
  struct tagMSG Msg; // [esp+0x650] [ebp-0x48] BYREF
  int v20; // [esp+0x66C] [ebp-0x2C]
  void *v21; // [esp+0x670] [ebp-0x28]
  int v22; // [esp+0x678] [ebp-0x20]
  char v23; // [esp+0x680] [ebp-0x18]
  char v24; // [esp+0x681] [ebp-0x17]
  char v25; // [esp+0x682] [ebp-0x16]
  HHOOK hhk; // [esp+0x684] [ebp-0x14]
  int *v27; // [esp+0x688] [ebp-0x10]
  int v28; // [esp+0x694] [ebp-0x4]
  float hInstancea; // [esp+0x6A0] [ebp+0x8]

  v27 = (int *)&v16;
  WindowA = FindWindowA(WindowName, WindowName);
  if ( IsWindow(WindowA) )
  {
    ::ShowWindow(WindowA, 1);
    return 0;
  }
  ::hInstance = hInstance;
  hhk = SetWindowsHookExA(13, fn, hInstance, 0);
  memset(&Data, 0, 0x104u);
  v28 = 0;
  if ( !(unsigned __int8)crt_sub_00541C40("software\\softstar\\pal3", "CDriver", &Data) )
    crt_sub_00541860();
  if ( !strrchr((const char *)&Data, 92) )
    strcat((char *)&Data, "\\");
  sprintf(Buffer, "%sMovie", (const char *)&Data);
  for ( i = CheckDirectoryExists(Buffer); !i; i = CheckDirectoryExists(Buffer) )
  {
    sprintf(Text, "Please Insert Disc4 to Dirver %c:", (char)Data);
    if ( MessageBoxA(0, Text, "Pal3", 0x41u) == 2 )
      return 0;
  }
  memset(Filename, 0, sizeof(Filename));
  GetModuleFileNameA(0, Filename, 0x104u);
  v7 = strrchr(Filename, 92);
  if ( v7 )
    *v7 = 0;
  sub_404800(hInstance);
  gbUpdateCurTime();
  v20 = 20;
  *(_QWORD *)&dbl_1895070 = __PAIR64__(HIDWORD(g_CurrentTime), LODWORD(g_CurrentTime));
  v8 = (void *)operator new(0x50u);
  v21 = (void *)v8;
  memset(v8, 0, 0x50u);
  v22 = 0;
  v23 = 1;
  v24 = 0;
  v25 = 0;
  LOBYTE(v28) = 1;
  while ( 1 )
  {
    if ( !PeekMessageA(&Msg, 0, 0, 0, 0) )
      goto LABEL_20;
    if ( !GetMessageA(&Msg, 0, 0, 0) )
      break;
    TranslateMessage(&Msg);
    DispatchMessageA(&Msg);
LABEL_20:
    gbUpdateCurTime();
    v9 = g_CurrentTime - dbl_1895070;
    v10 = (PAL3 *)LODWORD(g_CurrentTime);
    v11 = HIDWORD(g_CurrentTime);
    LODWORD(dbl_1895070) = LODWORD(g_CurrentTime);
    HIDWORD(dbl_1895070) = v11;
    if ( g_nPAL3_5833B8
      || (v12 = g_pCBSystem, ActiveWindow = GetActiveWindow(), (((CCBSystem *)v12))->CCBSystem::ProcUseItem(ActiveWindow)) )
    {
      hInstancea = v9;
      (((PAL3 *)v10))->PAL3::Update(hInstancea);
      (((PAL3 *)v14))->PAL3::Render();
    }
    else
    {
      Sleep(0x64u);
    }
  }
  if ( v8 )
    operator delete(v8);
  v28 = -1;
  UnhookWindowsHookEx(hhk);
  (((PAL3 *)v15))->PAL3::Destroy();
  return Msg.wParam;
}

// 0x0055CCE4
// positive sp value has been detected, the output may be wrong!
int NextRole(int *a1)
{
  int v2; // [esp-0x4] [ebp-0x4]

  return v2;
}


// Nullsub stubs (compiler-generated empty bodies)

void __cdecl nullsub_10(...) {}
void __cdecl nullsub_12(...) {}
void __cdecl nullsub_13(...) {}
void __cdecl nullsub_14(...) {}
void __cdecl nullsub_15(...) {}
void __cdecl nullsub_16(...) {}
void __cdecl nullsub_17(...) {}
void __cdecl nullsub_18(...) {}
void __cdecl nullsub_19(...) {}
void __cdecl nullsub_2(...) {}
void __cdecl nullsub_20(...) {}
void __cdecl nullsub_21(...) {}
void __cdecl nullsub_22(...) {}
void __cdecl nullsub_23(...) {}
void __cdecl nullsub_24(...) {}
void __cdecl nullsub_25(...) {}
void __cdecl nullsub_26(...) {}
void __cdecl nullsub_27(...) {}
void __cdecl nullsub_28(...) {}
void __cdecl nullsub_29(...) {}
void __cdecl nullsub_30(...) {}
void __cdecl nullsub_31(...) {}
void __cdecl nullsub_32(...) {}
void __cdecl nullsub_33(...) {}
void __cdecl nullsub_34(...) {}
void __cdecl nullsub_35(...) {}
void __cdecl nullsub_36(...) {}
void __cdecl nullsub_37(...) {}
void __cdecl nullsub_38(...) {}
void __cdecl nullsub_39(...) {}
void __cdecl nullsub_4(...) {}
void __cdecl nullsub_40(...) {}
void __cdecl nullsub_41(...) {}
void __cdecl nullsub_42(...) {}
void __cdecl nullsub_43(...) {}
void __cdecl nullsub_44(...) {}
void __cdecl nullsub_45(...) {}
void __cdecl nullsub_46(...) {}
void __cdecl nullsub_47(...) {}
void __cdecl nullsub_48(...) {}
void __cdecl nullsub_49(...) {}
void __cdecl nullsub_5(...) {}
void __cdecl nullsub_50(...) {}
void __cdecl nullsub_51(...) {}
void __cdecl nullsub_52(...) {}
void __cdecl nullsub_53(...) {}
void __cdecl nullsub_54(...) {}
void __cdecl nullsub_55(...) {}
void __cdecl nullsub_56(...) {}
void __cdecl nullsub_57(...) {}
void __cdecl nullsub_58(...) {}
void __cdecl nullsub_59(...) {}
void __cdecl nullsub_6(...) {}
void __cdecl nullsub_60(...) {}
void __cdecl nullsub_61(...) {}
void __cdecl nullsub_62(...) {}
void __cdecl nullsub_63(...) {}
void __cdecl nullsub_64(...) {}
void __cdecl nullsub_65(...) {}
void __cdecl nullsub_66(...) {}
void __cdecl nullsub_67(...) {}
void __cdecl nullsub_68(...) {}
void __cdecl nullsub_69(...) {}
void __cdecl nullsub_7(...) {}
void __cdecl nullsub_70(...) {}
void __cdecl nullsub_71(...) {}
void __cdecl nullsub_72(...) {}
void __cdecl nullsub_74(...) {}
void __cdecl nullsub_76(...) {}
void __cdecl nullsub_77(...) {}
void __cdecl nullsub_78(...) {}
void __cdecl nullsub_8(...) {}
void __cdecl nullsub_80(...) {}
void __cdecl nullsub_81(...) {}
void __cdecl nullsub_82(...) {}
void __cdecl nullsub_83(...) {}
void __cdecl nullsub_84(...) {}
void __cdecl nullsub_85(...) {}
void __cdecl nullsub_86(...) {}
void __cdecl nullsub_87(...) {}
void __cdecl nullsub_88(...) {}
void __cdecl nullsub_89(...) {}
void __cdecl nullsub_9(...) {}
void __cdecl nullsub_90(...) {}
void __cdecl nullsub_91(...) {}
void __cdecl nullsub_92(...) {}
void __cdecl nullsub_93(...) {}
void __cdecl nullsub_94(...) {}
