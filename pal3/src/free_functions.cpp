#include "pal3/ida_defs.h"
#include "globals.h"
#include "free_functions.h"
#include "Role/Actor.h"
#include "Misc/ArcLocaleRole.h"
#include "Misc/ArcPastScene.h"
#include "Misc/ArcSceneObject.h"
#include "Misc/Array.h"
#include "Combat/CCBCamControl.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBRoleState.h"
#include "Combat/CCBStageScene.h"
#include "Combat/CCBUI.h"
#include "Misc/CCBUIPanel.h"
#include "Effect/CEffGrid.h"
#include "Effect/CEffMeteor.h"
#include "Effect/CEffect.h"
#include "Effect/CEffgbParticle.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Scene/CameraCtrl.h"
#include "Misc/ExternalStatistics.h"
#include "GameBase/GRPinput.h"
#include "GameBase/InputSystem.h"
#include "GameBase/Logger.h"
#include "Misc/MainEquipUI.h"
#include "Misc/MiniGame2Scene.h"
#include "Role/NPC.h"
#include "Role/Object3D.h"
#include "Role/ObjectCamera.h"
#include "Misc/OpenSceneFile.h"
#include "GameBase/PAL3.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/PtrArray.h"
#include "Misc/RoleAtt.h"
#include "Misc/RoleCamera.h"
#include "Misc/RoleCameraCtrl.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneMgr.h"
#include "Effect/ScreenEffectMgr.h"
#include "Script/ScriptSystem.h"
#include "Misc/ScriptVM.h"
#include "GameBase/SoundContext.h"
#include "UI/UICursor.h"
#include "Misc/UIEmote.h"
#include "Misc/UIGameOver.h"
#include "UI/UIListBox.h"
#include "Misc/UILoadingFrm.h"
#include "UI/UINote.h"
#include "UI/UIQuadManager.h"
#include "UI/UIRenderObj.h"
#include "Misc/UIRoleSelectDialog.h"
#include "UI/UIScene.h"
#include "Misc/UISceneFrm.h"
#include "Misc/UISceneMap.h"
#include "Misc/UIScenePanel.h"
#include "Misc/UIStatic.h"
#include "Misc/UITextArea.h"
#include "Misc/UITitle_ArcSave.h"
#include "Misc/UITitle_BBTY.h"
#include "Misc/UITitle_YXXX.h"
#include "UI/UIWnd.h"
#include "Misc/VideoPlayer.h"

// Free functions (not belonging to any class)

// Forward declarations for unnamed functions
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc); // from annotations
int CombatEffectUpdate(int _this, double pData); // from annotations
void EffectUpdate(float fVal); // from annotations
void FightInfo(void); // from annotations
int FileSysInit(...);
void * GetSaveDataManager(void); // from annotations
int InputUpdate(int _this, int nVal); // from annotations
int LocalFree(...);
int MiniGame1Update(int ***_this, double pData); // from annotations
void MiniGame2Update(int **_this, int nVal); // from annotations
void MiniGame3Update(int *_this, float fVal); // from annotations
int NPCAnimUpdate(float fVal); // from annotations
char SceneMgrUpdate(float *_this, float fVal); // from annotations
char * ScriptUpdate(int dt); // from annotations
char * Texture_Info_FormatException(char *ArgList, const char *pszName, const char *pszName2, const char *pszName3, int nVal); // from annotations
int UINotifyUpdate(int *_this); // from annotations
void UIPostUpdate(gbSound2DNode *_this); // from annotations
int UISceneUpdate(void); // from annotations
int sub_41FA90(...);
int sub_420200(...);
int sub_420450(...);
int sub_4206F0(...);
int sub_420730(...);
void sub_421830(struct gbVisNode **_this); // from annotations
int sub_4339F0(const char *a1); // from annotations
int sub_438530(...);
int sub_445FA0(void *a2); // from annotations
int sub_4531F0(...);
int sub_459F80(...);
char sub_459FA0(int _this, unsigned __int8 pData); // from annotations
char sub_45A020(int _this, unsigned __int8 pData); // from annotations
char sub_45A0A0(int _this, unsigned __int8 pData); // from annotations
char sub_45A120(int _this, unsigned __int8 pData); // from annotations
char sub_45A1A0(int _this, unsigned __int8 pData); // from annotations
int sub_4A13E0(...);
int sub_4C5940(...);
int sub_523CD0(...);
int sub_523D20(...);
int sub_523D70(...);
int sub_523DC0(...);
int sub_523E10(...);
int sub_538260(...);
int sub_53D460(...);
int sub_53DAD0(...);
void __cdecl todo_401800(void);
int todo_451730(...);

void Actor_CopyConstruct_1C(void *pDst, const void *pSrc); // from annotations
void Actor_CopyConstruct_290(void *pDst, const void *pSrc); // from annotations
void Actor_CopyConstruct_40(void *pDst, const void *pSrc); // from annotations
void ActVec_Insert_char(Actor *_this, char *pszBuf, unsigned int dwVal, char *pszBuf2); // from annotations
_WORD * ActVec_Insert_word(Actor *_this, _WORD *p_WORD, unsigned int dwVal, _WORD *p_WORD2); // from annotations
unsigned int ActVec_InsertN(Actor *_this, char *pszBuf, unsigned int nX, char *nY); // from annotations
char * ActVec_InsertRange(Actor *_this, char *pszBuf, unsigned int dwVal, const void *pData); // from annotations
void AddMoney(int nAmount); // from annotations
int * AddNPCToPartySlot(int nRoleSlot, int nNpcId); // from annotations
int * AssignInt(int *pDst, int *pSrc); // from annotations
long double CalcAngleBetweenVectors(int nX1, int nY1, int nZ1, int nX2, float fY2, float fZ2); // from annotations
BOOL __stdcall CCBStageCam_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // from annotations
BOOL CheckDirectoryExists(LPCSTR lpFileName); // from annotations
gbGfxManager * CombatEnter(void); // from annotations
int ConvertDirection(int nDir); // from annotations
void CopyRoleData(int pDst, int pSrc); // from annotations
void CreateDigitPair(int nVal, UIWnd **ppTens, UIWnd **ppOnes, const char *pszTexBase, char bFlag); // from annotations
int crt_sub_00540070(void); // from annotations
int crt_sub_00540D20(void); // from annotations
int crt_sub_00540DC0(void); // from annotations
int crt_sub_00540FD0(void); // from annotations
int crt_sub_00541210(void); // from annotations
int crt_sub_00541590(void); // from annotations
int * ctor_0x431870(int *_this); // from annotations
int __stdcall DialogFunc(HWND hDlg, UINT uMsg, WPARAM a3, LPARAM lParam); // from annotations
double EditBox_GetFloat(HWND hWnd); // from annotations
int EditBox_GetInt(HWND hWnd); // from annotations
BOOL EditBox_IsModified(HWND hWnd); // from annotations
LRESULT EditBox_SetFloat(HWND hWnd, float fValue); // from annotations
LRESULT EditBox_SetInt(HWND hWnd, int nValue); // from annotations
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations
int FindOpcodeByName(char *pszCmdName); // from annotations
char FindScriptEventByID(int nEventId); // from annotations
LPSTR FormatChineseNumber(int nVal, LPSTR lpBuf); // from annotations
void FreeScriptInstance(int *pInstance); // from annotations
gbActorMgr * GetActorMgr(void); // from annotations
gbCamera * GetCamera_4(void); // from annotations
gbCamera * GetCurrentCamera(void); // from annotations
char * GetEditBoxText(HWND hWnd); // from annotations
void GetGridOffset(void *_this, int *pOut, int index); // from annotations
unsigned __int8 * GetOpcodeParamTypes(void); // from annotations
int GetRoleDataOffset(int nRoleIndex); // from annotations
void * GetSceneObject(unsigned __int16 nObjID); // from annotations
FILE * InitLogFiles(void); // from annotations
void InitOpcodeEntry(void); // from annotations
int InitSceOpcodeTable(void); // from annotations
void InitScriptEventArray(void); // from annotations
void InitScriptObjArray(void); // from annotations
int * LoadGameState(FILE *fp); // from annotations
char * LoadGameSwitches(void); // from annotations
struct gbVFileSystem * LoadScene(double sceneNames, char *arg8, char *pszBuf, char pData, char pData2); // from annotations
int LoadScriptFile(const char *pszFileName); // from annotations
char * MovePartyFollowers(char *bNotifyScript); // from annotations
BOOL __stdcall MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint); // from annotations
int operator_(_DWORD *_this, int a2, char a3); // from annotations
int PAL3_RandomPickValues(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int *p_DWORD); // from annotations
BOOL PointInRect(int *pRect, int *pPoint); // from annotations
BOOL ReadRegistryString(const char *szSubKey, const char *szValueName, char *szOutBuf); // from annotations
int RefreshPartyRoleData(void); // from annotations
int RenderPost(int _this, int nVal); // from annotations
void ResizeOpcodeParams(PtrArray *_this); // from annotations
void RestorePartyFollowMode(int bNotifyScript); // from annotations
void SafeDeletePtr(void **pptr); // from annotations
void SaveGameState(FILE *fp); // from annotations
void SetGameSwitch(int nSwitchIdx); // from annotations
char * SetRoleLevelAndRefresh(int nRoleIdx, int nLevel); // from annotations
void SetScriptInitFlag(void); // from annotations
char SetupPartyFormation(int bNotifyScript); // from annotations
char SetupPartyFormationWide(int bNotifyScript); // from annotations
BOOL ShowMessageBox(const char *szMessage, const char *szCaption); // from annotations
int * SortTripletsByField(int *p_DWORD, int *p_DWORD2, int nVal); // from annotations
char * __stdcall StrCopyRange(char *pStart, char *pEnd, char *pDest); // from annotations
gbVec3D * __stdcall Vec3D_CopyStruct(gbVec3D *pDst, gbVec3D *pSrc, gbVec3D *pExtra); // from annotations
gbVec3D * Vec3D_Cross(gbVec3D *pOut, gbVec3D *pA, gbVec3D *pB); // from annotations
float * Vec3D_Lerp(float *pOut, float *pSrc, float fLerpFactor); // from annotations
char * WinProc_HWND_ExecCommand(char *_this); // from annotations
int WinProc_HWND_InputLine(void *_this, char pData); // from annotations
int WinProc_HWND_SetAndExec(char *_this, char *Source); // from annotations

// Unnamed globals (extern)
extern char byte_17B3AAC[1028];
extern char byte_BFDB78;
extern CHAR byte_DCAD3C[256];
extern int dword_60BDC8;
extern std::ios_base dword_BFDAB0;
extern int dword_C020F4;
extern int dword_C0E760;
extern int dword_C0EC50;
extern int dword_C10BA0[];
extern int dword_D8BBEC;
extern PalScriptMgr * dword_DBA254;
extern int dword_DCA33C[];
extern float flt_17AA800;
extern float flt_5F4B9C;
void __cdecl nullsub_2(...);
extern char off_6088D8[];
extern RoleSystem stru_C059A0;
extern RoleSystem stru_C08160;
extern PalScript stru_C11720;
extern GRPinput stru_D8C2B8;
extern RoleCameraCtrl stru_DBA134;
extern int unk_D8F624;
void __cdecl unknown_libname_507(void);

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

// 0x00401C70
// write access to const memory has been detected, the output may be wrong!
int FileSysInit()
{
  _DWORD ( *v0)(gbVFileSystem *__hidden, char *); // esi
  char v2[324]; // [esp+0x8] [ebp-0x944] BYREF
  char pExceptionObject[1024]; // [esp+0x14C] [ebp-0x800] BYREF
  char ArgList[1024]; // [esp+0x54C] [ebp-0x400] BYREF

  if ( (g_dwGameFlags & 2) != 0 )
  {
    strcpy(v2, "basedata\\");
    strcat(v2, "basedata.cpk");
    v0 = gbVFileSystem::Init;
    if ( !((gbVFileSystem *)&g_BaseVFileSystem)->Init(v2) )
    {
      qmemcpy(pExceptionObject, ((Logger *)ArgList)->FormatException(msg, file, 23), sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
  }
  else
  {
    v0 = gbVFileSystem::Init;
    if ( !((gbVFileSystem *)&g_BaseVFileSystem)->Init("basedata\\") )
    {
      qmemcpy(pExceptionObject, ((Logger *)ArgList)->FormatException(msg, file, 28), sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
  }
  g_pVFileSys = (gbVFileSystem *)&g_BaseVFileSystem;
  return v0((gbVFileSystem *)dword_60BDC8, 0);
}

// 0x00401DA0
// write access to const memory has been detected, the output may be wrong!
gbVFileSystem *FileSysDestory()
{
  gbVFileSystem *result; // eax

  if ( g_BaseVFileSystem )
    ((gbVFileSystem *)&g_BaseVFileSystem)->Release();
  result = g_VFileSystem;
  if ( g_VFileSystem )
  {
    ((gbVFileSystem *)&g_VFileSystem)->Release();
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

  v1 = v0;
  ((GRPinput *)v0)->Reset();
  v1->m_bKeyboard = 0;
  m_lpDIDKeyboard = v1->m_lpDIDKeyboard;
  if ( m_lpDIDKeyboard )
    return (*(int ( **)(IDirectInputDevice8 *))(*(_DWORD *)m_lpDIDKeyboard + 32))(m_lpDIDKeyboard);
  return result;
}

// 0x00404310
char * StrCopyRange(char *pStart, char *pEnd, char *pDest)
{
  char *v3; // edx
  char *result; // eax

  v3 = pStart;
  if ( pStart == g_SceneMgr.m_pAddEffect2 )
    return pDest;
  result = pDest;
  do
  {
    if ( result )
      qmemcpy(result, v3, 0x24u);
    v3 += 36;
    result += 36;
  }
  while ( v3 != g_SceneMgr.m_pAddEffect2 );
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
      WinProc_HWND_InputLine(&g_InputState, pvParam);
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
                (*(void ( **)(_DWORD, LONG, LONG, int))(*(_DWORD *)LODWORD(v7[1].InvViewMatrix.xy) + 44))(
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
    WinProc_HWND_SetAndExec((char *)&g_InputState, *(char **)(lParam + 8));
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
        ((GRPinput *)&g_Input)->HandleDeviceInput(1, 1, 0);
        g_nPAL3_5833B8 = 1;
      }
      else
      {
        g_nPAL3_5833B8 = 0;
        ((GRPinput *)&g_Input)->HandleDeviceInput(0, 0, 0);
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
        Instance = UIQuadManager::GetInstance();
        ((UIRenderObj *)Instance)->_UIRenderObj();
      }
      result = 1;
      break;
    default:
      return DefWindowProcA(hWnd, Msg, v4, lParam);
  }
  return result;
}

// 0x00408B60
void InitScriptObjArray()
{
  if ( (byte_BFDB78 & 1) == 0 )
  {
    byte_BFDB78 |= 1u;
    ((UIListBox *)&g_pScriptObjArray)->ReleaseVtable();
  }
}

// 0x0040C230
char * ScriptUpdate(int dt)
{
  int *p_capacity; // esi
  double v2; // st7
  double v3; // st7
  int *v4; // ecx
  double v5; // st7
  double v6; // st7
  char *result; // eax
  bool v8; // cl
  int v9; // edx
  int v10; // [esp+0x14] [ebp-0x24]
  int v11; // [esp+0x18] [ebp-0x20]
  ScriptSystem *v12; // [esp+0x1C] [ebp-0x1C]
  _BYTE v13[12]; // [esp+0x20] [ebp-0x18]
  gbVec3D v14; // [esp+0x2C] [ebp-0xC] BYREF

  p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
  do
  {
    ((ScriptSystem *)*(float *)&dt)->UpdateTimers();
    p_capacity += 2176;
  }
  while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
  if ( g_RoleSystemMain.m_FrameA.m_rect.bottom == 10 )
  {
    if ( *(_DWORD *)&((RoleSystem *)&stru_C08160)->m_partyActor.m_szTexture[4] )
      ((ScriptSystem *)*(float *)&dt)->UpdateObjects();
  }
  else if ( g_RoleSystemMain.m_FrameA.m_rect.bottom == 11 )
  {
    ((Actor *)&g_RoleSystemMain)->UpdatePhysics(*(float *)&dt);
  }
  else if ( *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] )
  {
    ((ScriptSystem *)*(float *)&dt)->UpdateTimers();
  }
  if ( *(_DWORD *)&g_RoleSystemExtra1.m_partyActor.m_szTexture[4] )
  {
    if ( g_RoleSystemExtra1.m_FrameA.m_rect.right != 4 )
    {
      *(_DWORD *)&g_RoleSystemExtra1.m_partyActor.m_szTexture[4] = 0;
      ((RoleSystem *)&g_RoleSystemExtra1)->Notify();
    }
    ((ScriptSystem *)*(float *)&dt)->UpdateTimers();
  }
  if ( *(_DWORD *)&g_RoleSystemExtra0.m_partyActor.m_szTexture[4] )
  {
    if ( g_RoleSystemExtra0.m_FrameA.m_rect.right != 4 )
    {
      *(_DWORD *)&g_RoleSystemExtra0.m_partyActor.m_szTexture[4] = 0;
      ((RoleSystem *)&g_RoleSystemExtra0)->Notify();
    }
    ((ScriptSystem *)*(float *)&dt)->UpdateTimers();
    g_RoleSystemExtra0.m_fPosY = g_RoleSystemExtra0.m_fPosY + 80.0;
  }
  if ( g_nCurrentEventId <= 4 )
  {
    if ( g_nScriptEventParam )
    {
      v3 = *(float *)&g_nActor_BFDBAC + *(float *)&dt;
      *(float *)&g_nActor_BFDBAC = v3;
      if ( v3 >= 4.0 )
      {
        g_nActor_BFDBAC = 0;
        switch ( g_nCurrentEventId )
        {
          case 0u:
          case 1u:
            ((PalScriptMgr *)1)->RunScript(0, 1);
            break;
          case 2u:
            ((ScriptSystem *)0.5)->RunWithDelay(0, 1);
            break;
          case 3u:
            ((PalScriptMgr *)(__int64)((double)(int)Buffer.m_partyActor.m_dwMatMsg[352 * g_nCurrentRoleSlot + 9] * 0.050000001))->RunScript(0, 1);
            break;
          case 4u:
            *(float *)&g_nActor_BFDBA8 = *(float *)&g_nActor_BFDBA8 * 1.5;
            ((PalScriptMgr *)(__int64)*(float *)&g_nActor_BFDBA8)->RunScript(0, 1);
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
          v2 = (double)*(int *)&Buffer.m_partyActor.m_curact[1408 * g_nCurrentRoleSlot + 39] * 0.5;
          if ( v2 < 1.0 )
            v2 = 1.0;
          ((PalScriptMgr *)*(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * g_nCurrentRoleSlot + 39] - (__int64)v2)->RunScript(1, 1);
          break;
        case 1u:
        case 2u:
          ((ScriptSystem *)0.5)->RunWithDelay(1, 1);
          break;
        case 3u:
          ((PalScriptMgr *)(__int64)((double)(int)Buffer.m_partyActor.m_dwMatMsg[352 * g_nCurrentRoleSlot + 9] * 0.050000001))->RunScript(1, 1);
          break;
        case 4u:
          *(float *)&g_nActor_BFDBA8 = (double)(int)Buffer.m_partyActor.m_dwMatMsg[352 * g_nCurrentRoleSlot + 9] * 0.5;
          ((PalScriptMgr *)(__int64)*(float *)&g_nActor_BFDBA8)->RunScript(1, 1);
          break;
        default:
          break;
      }
    }
    ++g_nScriptEventParam;
    v4 = &((RoleSystem *)&stru_C059A0)->m_teamSlots[2176 * g_nCurrentRoleSlot - 6];
    v10 = *v4;
    v11 = v4[1];
    *(float *)v13 = *(float *)v4 - *(float *)&g_nScriptRolePosX;
    v12 = *((ScriptSystem **)v4 + 2);
    *(float *)&v13[4] = *(float *)&v11 - *(float *)&g_nScriptRolePosY;
    *(float *)&v13[8] = *(float *)&v12 - *(float *)&g_nScriptRolePosZ;
    v14 = *(gbVec3D *)v13;
    v5 = ((gbVec3D *)&v14)->Length() + g_fScriptEventParam2;
    g_nScriptRolePosY = v11;
    g_nScriptRolePosX = v10;
    g_nScriptRolePosZ = (int)v12;
    g_fScriptEventParam2 = v5;
    if ( v5 >= 12.0 * 100.0 )
      ((ScriptSystem *)v12)->RunEvent(31, 1);
  }
  v6 = g_fFadeTimer + *(float *)&dt;
  g_fFadeTimer = v6;
  if ( v6 >= 60.0 )
  {
    HIBYTE(Buffer.m_partyActor.m_nHandleEvent) = 0;
    LOWORD(Buffer.m_partyActor.m_vecPos.x) = 0;
    BYTE2(Buffer.m_partyActor.m_vecPos.x) = 0;
    g_nSceneTransitionParam2 = 0;
  }
  NPCAnimUpdate(*(float *)&dt);
  result = (char *)((PalScript *)&g_UIScript)->UpdateTimer(dt, 0);
  if ( g_bFormationReady )
  {
    v8 = 1;
    v9 = 0;
    result = (char *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[300];
    do
    {
      if ( v9 != g_nCurrentRoleSlot )
        v8 = v8 && (*((_DWORD *)result + 9) != 4 || *(_DWORD *)result != 10);
      result += 8704;
      ++v9;
    }
    while ( (int)result < (int)&g_szSceneUIText[244] );
    if ( v8 )
    {
      g_bFormationReady = 0;
      result = (char *)((CameraCtrl *)&g_pCameraCtrl)->SetCamDist(g_nPtrArray_586154);
    }
  }
  if ( g_pCurrentScript )
    return (*(char *( **)(PalScript *))(g_pCurrentScript->m_bLoadSceneScript + 20))(g_pCurrentScript);
  return result;
}

// 0x0040DE10
char * MovePartyFollowers(char *bNotifyScript)
{
  RoleSystem *v1; // esi
  int *p_m_bcreateok; // edi
  char *result; // eax
  double v4; // st7
  double v5; // st7
  double v6; // st6
  gbVec3D *v7; // eax
  float z; // edx
  double v9; // st7
  double v10; // st6
  gbVec3D *v11; // eax
  float v12; // edx
  float v13; // eax
  float *v14; // eax
  double v15; // st7
  int v16; // eax
  float v17; // [esp+0xC] [ebp-0x78]
  float v18; // [esp+0xC] [ebp-0x78]
  float v19; // [esp+0x10] [ebp-0x74]
  float v20; // [esp+0x10] [ebp-0x74]
  float v21; // [esp+0x14] [ebp-0x70]
  float v22; // [esp+0x14] [ebp-0x70]
  int *v23; // [esp+0x28] [ebp-0x5C]
  char *v24; // [esp+0x2C] [ebp-0x58]
  float nFlags; // [esp+0x30] [ebp-0x54] BYREF
  float v26; // [esp+0x34] [ebp-0x50]
  float v27; // [esp+0x38] [ebp-0x4C]
  float v28; // [esp+0x3C] [ebp-0x48] BYREF
  float v29; // [esp+0x40] [ebp-0x44]
  float v30; // [esp+0x44] [ebp-0x40]
  float x; // [esp+0x48] [ebp-0x3C]
  float y; // [esp+0x4C] [ebp-0x38]
  float v33; // [esp+0x50] [ebp-0x34]
  float v34; // [esp+0x54] [ebp-0x30]
  float v35; // [esp+0x58] [ebp-0x2C]
  float v36; // [esp+0x5C] [ebp-0x28]
  gbVec3D v37; // [esp+0x60] [ebp-0x24] BYREF
  gbVec3D v38; // [esp+0x6C] [ebp-0x18] BYREF
  float pOut[3]; // [esp+0x78] [ebp-0xC] BYREF

  v1 = g_pRoleSystem;
  ((RoleSystem *)&g_pRoleSystem)->Notify();
  nFlags = 0.0;
  v26 = 0.0;
  v27 = 0.0;
  v24 = 0;
  v23 = &g_nPtrArray_C04300;
  p_m_bcreateok = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_bcreateok;
  do
  {
    result = v24;
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + (_DWORD)v24) )
    {
      result = (char *)(p_m_bcreateok - 3);
      if ( p_m_bcreateok - 3 != (int *)v1 )
      {
        ((RoleSystem *)(p_m_bcreateok - 3))->SetTransform((int *)v1);
        nFlags = *(float *)&v1->m_rect.top;
        v26 = *(float *)&v1->m_rect.right;
        v4 = *(float *)&v1->m_rect.bottom;
        nFlags = nFlags * -12.0;
        v26 = -12.0 * v26;
        v27 = v4 * -12.0;
        *((float *)p_m_bcreateok - 2) = nFlags + *((float *)p_m_bcreateok - 2);
        *((float *)p_m_bcreateok - 1) = v26 + *((float *)p_m_bcreateok - 1);
        *(float *)p_m_bcreateok = v27 + *(float *)p_m_bcreateok;
        ((RoleSystem *)(p_m_bcreateok - 3))->NotifySceneChange();
        v28 = 0.0;
        v29 = 0.0;
        v5 = *((float *)v23 - 2);
        v6 = v5 * *(float *)&v1->m_childs.capacity;
        v30 = 0.0;
        v21 = v6;
        v19 = v5 * *(float *)&v1->m_childs.m_pData;
        v17 = v5 * *(float *)&v1->m_pfather;
        v7 = ((gbVec3D *)&v37)->gbVec3D(v17, v19, v21);
        x = v7->x;
        y = v7->y;
        z = v7->z;
        nFlags = x;
        v26 = y;
        v27 = z;
        v9 = *((float *)v23 - 1);
        v10 = v9 * *(float *)&v1->m_bcreateok;
        v33 = z;
        v22 = v10;
        v20 = v9 * *(float *)&v1->m_childs.m_needscriptdel;
        v18 = v9 * *(float *)&v1->m_childs.m_nSize;
        v11 = ((gbVec3D *)&v38)->gbVec3D(v18, v20, v22);
        v34 = v11->x;
        v12 = v11->y;
        v13 = v11->z;
        v28 = v34;
        v35 = v12;
        v36 = v13;
        v29 = v12;
        v30 = v13;
        ((gbVec3D *)&nFlags)->operator+=(&v28);
        v14 = Vec3D_Lerp(pOut, (float *)&v1->m_rect.top, *(float *)v23);
        ((gbVec3D *)&v28)->operator=(v14);
        ((gbVec3D *)&nFlags)->operator+=(&v28);
        v23 += 3;
        nFlags = nFlags + *(float *)&v1->m_fontcolor.Color;
        v26 = v26 + *(float *)&v1->m_wndcolor.Color;
        v15 = v27 + *(float *)&v1->m_id;
        p_m_bcreateok[155] = 1;
        v27 = v15;
        ((RoleSystem *)(p_m_bcreateok - 3))->InitPathTracking(&nFlags);
        result = bNotifyScript;
        if ( bNotifyScript )
        {
          if ( p_m_bcreateok == (int *)12 )
            v16 = 0;
          else
            v16 = (int)(p_m_bcreateok + 11);
          ((PalScriptMgr *)v16)->NotifyEvent();
        }
      }
    }
    p_m_bcreateok += 2176;
    ++v24;
  }
  while ( (int)p_m_bcreateok < (int)&g_pScriptArrayEnd2 );
  return result;
}

// 0x0040E050
float * Vec3D_Lerp(float *pOut, float *pSrc, float fLerpFactor)
{
  float v4; // [esp+0x0] [ebp-0xC]
  float v5; // [esp+0x4] [ebp-0x8]
  float v6; // [esp+0x8] [ebp-0x4]

  v4 = fLerpFactor * *pSrc;
  v5 = fLerpFactor * pSrc[1];
  v6 = fLerpFactor * pSrc[2];
  *pOut = v4;
  pOut[1] = v5;
  pOut[2] = v6;
  return pOut;
}

// 0x0040E0A0
void RestorePartyFollowMode(int bNotifyScript)
{
  RoleSystem *v1; // edi
  int v2; // ebx
  int *p_capacity; // esi
  int v4; // eax

  v1 = g_pRoleSystem;
  ((RoleSystem *)&g_pRoleSystem)->Notify();
  v2 = 0;
  p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v2) )
    {
      if ( p_capacity[158] )
      {
        if ( p_capacity != (int *)v1 )
        {
          ((RoleSystem *)p_capacity)->RestoreMoveMode((float *)&v1->m_fontcolor.Color);
          if ( bNotifyScript )
          {
            if ( p_capacity )
              v4 = (int)(p_capacity + 14);
            else
              v4 = 0;
            ((PalScriptMgr *)v4)->NotifyEvent();
          }
        }
      }
    }
    p_capacity += 2176;
    ++v2;
  }
  while ( p_capacity < (int *)&g_pScriptArrayEnd );
}

// 0x0040E110
char SetupPartyFormation(int bNotifyScript)
{
  RoleSystem *v1; // edi
  int *p_capacity; // esi
  int *p_m_needscriptdel; // esi
  double v4; // st7
  double v5; // st7
  float v6; // edx
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  unsigned int v10; // edx
  double v11; // st7
  int v12; // eax
  char result; // al
  int v14; // [esp+0x4] [ebp-0x60]
  int v15; // [esp+0x4] [ebp-0x60]
  int v16; // [esp+0x8] [ebp-0x5C]
  int *v17; // [esp+0x14] [ebp-0x50]
  int v18; // [esp+0x18] [ebp-0x4C]
  double thisa; // [esp+0x1C] [ebp-0x48] BYREF
  float v20; // [esp+0x24] [ebp-0x40]
  float fLerpFactor; // [esp+0x28] [ebp-0x3C]
  float v22; // [esp+0x2C] [ebp-0x38]
  float v23; // [esp+0x30] [ebp-0x34]
  _DWORD v24[3]; // [esp+0x34] [ebp-0x30] BYREF
  float pOut[3]; // [esp+0x40] [ebp-0x24] BYREF
  float v26[3]; // [esp+0x4C] [ebp-0x18] BYREF
  float v27[3]; // [esp+0x58] [ebp-0xC] BYREF

  v1 = g_pRoleSystem;
  ((RoleSystem *)&g_pRoleSystem)->Notify();
  thisa = 0.0;
  v20 = 0.0;
  if ( g_bFormationReady )
  {
    p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
    do
    {
      ((RoleSystem *)p_capacity)->Notify();
      p_capacity += 2176;
    }
    while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
  }
  v18 = 0;
  v17 = &g_nPtrArray_C04300;
  p_m_needscriptdel = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_needscriptdel;
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v18) && p_m_needscriptdel - 2 != (int *)v1 )
    {
      *(p_m_needscriptdel - 1) = v1->m_fontcolor.Color;
      *p_m_needscriptdel = v1->m_wndcolor.Color;
      p_m_needscriptdel[1] = (int)v1->m_id;
      thisa = *(double *)&v1->m_rect.top;
      v4 = *(float *)&v1->m_rect.bottom;
      *(float *)&thisa = -12.0 * *(float *)&thisa;
      *((float *)&thisa + 1) = *((float *)&thisa + 1) * -12.0;
      v20 = -12.0 * v4;
      *((float *)p_m_needscriptdel - 1) = *(float *)&thisa + *((float *)p_m_needscriptdel - 1);
      *(float *)p_m_needscriptdel = *((float *)&thisa + 1) + *(float *)p_m_needscriptdel;
      *((float *)p_m_needscriptdel + 1) = v20 + *((float *)p_m_needscriptdel + 1);
      p_m_needscriptdel[38] = *(p_m_needscriptdel - 1);
      p_m_needscriptdel[39] = *p_m_needscriptdel;
      p_m_needscriptdel[40] = p_m_needscriptdel[1];
      ((RoleSystem *)(p_m_needscriptdel - 2))->NotifySceneChange();
      ((RoleSystem *)(p_m_needscriptdel - 2))->SetMoveSpeed(0.0, 0, v14);
      memset(v24, 0, sizeof(v24));
      v5 = *((float *)v17 - 2) * -3.0;
      v6 = *(float *)v17;
      v22 = *((float *)v17 - 1);
      fLerpFactor = v5;
      v22 = v22 * -3.0;
      v23 = v6 * -3.0;
      v7 = Vec3D_Lerp(pOut, (float *)&v1->m_pfather, fLerpFactor);
      ((gbVec3D *)&thisa)->operator=(v7);
      v8 = Vec3D_Lerp(v26, (float *)&v1->m_childs.m_nSize, v22);
      ((gbVec3D *)v24)->operator=(v8);
      ((gbVec3D *)&thisa)->operator+=(v24);
      v9 = Vec3D_Lerp(v27, (float *)&v1->m_rect.top, v23);
      ((gbVec3D *)v24)->operator=(v9);
      ((gbVec3D *)&thisa)->operator+=(v24);
      v17 += 3;
      *(float *)&thisa = *(float *)&thisa + *(float *)&v1->m_fontcolor.Color;
      v10 = LODWORD(thisa);
      *((float *)&thisa + 1) = *((float *)&thisa + 1) + *(float *)&v1->m_wndcolor.Color;
      v11 = v20 + *(float *)&v1->m_id;
      p_m_needscriptdel[156] = 1;
      v20 = v11;
      ((RoleSystem *)(p_m_needscriptdel - 2))->GetActorState(COERCE_DOUBLE(__PAIR64__(LODWORD(v20), v10)), 2, v15, v16);
      if ( bNotifyScript )
      {
        if ( p_m_needscriptdel == (int *)8 )
          v12 = 0;
        else
          v12 = (int)(p_m_needscriptdel + 12);
        ((PalScriptMgr *)v12)->NotifyEvent();
      }
      g_bFormationReady = 1;
    }
    p_m_needscriptdel += 2176;
    ++v18;
  }
  while ( (int)p_m_needscriptdel < (int)&g_UIScript );
  result = g_bFormationReady;
  if ( g_bFormationReady )
  {
    g_nPtrArray_586154 = SLODWORD(g_pCameraCtrl->m_fCamDist);
    return ((CameraCtrl *)&g_pCameraCtrl)->SetCamDist(1142292480);
  }
  return result;
}

// 0x0040E3C0
char SetupPartyFormationWide(int bNotifyScript)
{
  RoleSystem *v1; // edi
  int *p_capacity; // esi
  int *p_m_bcreateok; // esi
  int *v4; // ebx
  float v5; // edx
  double v6; // st7
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  double v10; // st7
  double v11; // st6
  float v12; // eax
  float v13; // ecx
  int v14; // eax
  char result; // al
  int v16; // [esp+0x10] [ebp-0x5C]
  int v17; // [esp+0x20] [ebp-0x4C]
  float v18; // [esp+0x24] [ebp-0x48] BYREF
  float v19; // [esp+0x28] [ebp-0x44]
  float v20; // [esp+0x2C] [ebp-0x40]
  float fLerpFactor; // [esp+0x30] [ebp-0x3C]
  float v22; // [esp+0x34] [ebp-0x38]
  float v23; // [esp+0x38] [ebp-0x34]
  gbVec3D v24; // [esp+0x3C] [ebp-0x30] BYREF
  float pOut[3]; // [esp+0x48] [ebp-0x24] BYREF
  float v26[3]; // [esp+0x54] [ebp-0x18] BYREF
  float v27[3]; // [esp+0x60] [ebp-0xC] BYREF

  v1 = g_pRoleSystem;
  ((RoleSystem *)&g_pRoleSystem)->Notify();
  v18 = 0.0;
  v19 = 0.0;
  v20 = 0.0;
  if ( g_bFormationReady )
  {
    p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
    do
    {
      ((RoleSystem *)p_capacity)->Notify();
      p_capacity += 2176;
    }
    while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
  }
  v17 = 0;
  p_m_bcreateok = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_bcreateok;
  v4 = &g_nPtrArray_C04300;
  do
  {
    if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v17) && p_m_bcreateok - 3 != (int *)v1 )
    {
      v5 = *(float *)v4;
      v6 = *((float *)v4 - 2) + *((float *)v4 - 2);
      v22 = *((float *)v4 - 1);
      fLerpFactor = v6;
      v22 = v22 + v22;
      v23 = v5 + v5;
      v7 = Vec3D_Lerp(pOut, (float *)&v1->m_pfather, fLerpFactor);
      ((gbVec3D *)&v18)->operator=(v7);
      v8 = Vec3D_Lerp(v26, (float *)&v1->m_childs.m_nSize, v22);
      ((gbVec3D *)&v24)->operator=(v8);
      ((gbVec3D *)&v18)->operator+=(&v24);
      v9 = Vec3D_Lerp(v27, (float *)&v1->m_rect.top, v23);
      ((gbVec3D *)&v24)->operator=(v9);
      ((gbVec3D *)&v18)->operator+=(&v24);
      v10 = v18 + *(float *)&v1->m_fontcolor.Color;
      v4 += 3;
      v18 = v10;
      v11 = v19 + *(float *)&v1->m_wndcolor.Color;
      v19 = v11;
      v12 = v19;
      v20 = v20 + *(float *)&v1->m_id;
      v13 = v20;
      *(float *)p_m_bcreateok = v20;
      *((float *)p_m_bcreateok - 2) = v10;
      *((float *)p_m_bcreateok - 1) = v11;
      *((float *)p_m_bcreateok + 38) = v12;
      *((float *)p_m_bcreateok + 39) = v13;
      *((float *)p_m_bcreateok + 37) = v10;
      ((RoleSystem *)(p_m_bcreateok - 3))->NotifySceneChange();
      ((RoleSystem *)(p_m_bcreateok - 3))->SetMoveSpeed(0.0, 0, v16);
      p_m_bcreateok[155] = 1;
      ((RoleSystem *)(p_m_bcreateok - 3))->StartLinearMove((int *)&v1->m_fPosX, 2);
      if ( bNotifyScript )
      {
        if ( p_m_bcreateok == (int *)12 )
          v14 = 0;
        else
          v14 = (int)(p_m_bcreateok + 11);
        ((PalScriptMgr *)v14)->NotifyEvent();
      }
      g_bFormationReady = 1;
    }
    p_m_bcreateok += 2176;
    ++v17;
  }
  while ( (int)p_m_bcreateok < (int)&g_pScriptArrayEnd2 );
  result = g_bFormationReady;
  if ( g_bFormationReady )
  {
    g_nPtrArray_586154 = SLODWORD(g_pCameraCtrl->m_fCamDist);
    return ((CameraCtrl *)&g_pCameraCtrl)->SetCamDist(1142292480);
  }
  return result;
}

// 0x0040E840
int * AddNPCToPartySlot(int nRoleSlot, int nNpcId)
{
  int v2; // ebx
  __int16 v3; // bp
  _BYTE *v4; // edx
  int v5; // eax
  _DWORD *v6; // ecx
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
  char *v17; // ebp
  char *j; // ebx
  int v19; // eax
  char *v21; // ecx
  char *i; // eax
  int *v23; // ecx
  int v24; // [esp+0x0] [ebp-0x20]
  int v25; // [esp+0x18] [ebp-0x8]
  int RoleNum; // [esp+0x1C] [ebp-0x4]
  int nRoleSlota; // [esp+0x24] [ebp+0x4]
  int nNpcIda; // [esp+0x28] [ebp+0x8]

  RefreshPartyRoleData();
  v2 = 0;
  v3 = 0;
  v4 = &Buffer.m_partyActor.m_bDirFlag + 1408 * nRoleSlot + 32;
  while ( 2 )
  {
    v5 = 0;
    v6 = v4;
    do
    {
      if ( nNpcId == *v6 )
      {
        v7 = v5 + 8 * (v2 + 176 * nRoleSlot);
        v3 = *((unsigned __int8 *)&Buffer.m_fMoveRadius + v7);
        v8 = *((unsigned __int8 *)&Buffer.m_FrameA.m_bfocus + v7);
        goto LABEL_9;
      }
      ++v5;
      ++v6;
    }
    while ( v5 < 8 );
    ++v2;
    v4 += 32;
    if ( v2 < 6 )
      continue;
    break;
  }
  v8 = 0;
LABEL_9:
  LOWORD(v25) = v3;
  HIWORD(v25) = v8;
  v9 = &g_SceneMgrPrefix + nRoleSlot;
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nNpcId);
  m_pData = v9->m_pData;
  v11 = (int *)m_pData;
  if ( (v9->m_nCapacity - (int)m_pData) / 12 )
  {
    ((Array *)v9)->Insert(m_pData, m_pData);
    ((Array *)v9)->Erase((int)v9->m_pData, 1 - (v9->m_pData - (char *)v11) / 12);
    for ( i = v9->m_pData; v11 != (int *)i; v23[2] = RoleNum )
    {
      v23 = v11;
      v11 += 3;
      *v23 = nNpcId;
      v23[1] = v25;
    }
    v9->m_pData += 12;
    return (int *)((NPC *)v24)->InitAll();
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
    v17 = (char *)v9->m_nSize;
    nNpcIda = (int)v16;
    for ( j = v16; v17 != (char *)v11; j += 12 )
    {
      ((Array *)j)->Copy(v17);
      v17 += 12;
    }
    ((Array *)v9)->Erase((int)j, 1);
    ((Array *)v9)->Insert(v11, v9->m_pData);
    nullsub_2(v9->m_nSize, v9->m_pData);
    operator delete((void *)v9->m_nSize);
    v9->m_nCapacity = nNpcIda + 12 * nRoleSlota;
    v19 = v9->m_nSize;
    if ( v19 )
    {
      v21 = v9->m_pData;
      v9->m_nSize = nNpcIda;
      v9->m_pData = (char *)(nNpcIda + 4 * (3 * ((int)&v21[-v19] / 12) + 3));
    }
    else
    {
      v9->m_nSize = nNpcIda;
      v9->m_pData = (char *)(nNpcIda + 12);
    }
    return (int *)((NPC *)v24)->InitAll();
  }
}

// 0x0040F0C0
void SaveGameState(FILE *fp)
{
  FILE *v1; // esi
  int v2; // eax
  int *p_nState; // edi
  int *p_nCurCount; // edi
  char Buffer[4]; // [esp+0x4] [ebp-0x64] BYREF
  float m_fPosX; // [esp+0x8] [ebp-0x60]
  float m_fPosY; // [esp+0xC] [ebp-0x5C]
  float m_fPosZ; // [esp+0x10] [ebp-0x58]
  char v9; // [esp+0x14] [ebp-0x54]
  float v10; // [esp+0x18] [ebp-0x50]
  _BYTE v11[72]; // [esp+0x20] [ebp-0x48] BYREF

  v1 = fp;
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
    fwrite(&::Buffer, 0x1B80u, 1u, v1);
    fwrite(&((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather, 5u, 1u, v1);
    ((NPC *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->SaveToStream(v1);
    ((NPC *)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY)->ReadBufferData(v1);
    Buffer[0] = g_RoleSystemMain.m_partyActor.m_szTexture[4];
    m_fPosY = g_RoleSystemMain.m_fPosY;
    v9 = g_RoleSystemMain.m_partyActor.m_szTexture[0];
    m_fPosX = g_RoleSystemMain.m_fPosX;
    m_fPosZ = g_RoleSystemMain.m_fPosZ;
    v10 = g_fScriptTimeAccum;
    fwrite(Buffer, 0x1Cu, 1u, v1);
    p_nState = &g_ScriptCounters[0].nState;
    do
    {
      LOBYTE(fp) = *(_BYTE *)p_nState;
      fwrite(&fp, 1u, 1u, v1);
      p_nState += 4;
    }
    while ( (int)p_nState < (int)&dword_C020F4 );
    p_nCurCount = &g_ScriptCounters[0].nCurCount;
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
  int *v6; // esi
  int v7; // edi
  int v8; // edx
  int Buffer; // [esp+0x4] [ebp-0x64] BYREF
  float v10; // [esp+0x8] [ebp-0x60]
  float v11; // [esp+0xC] [ebp-0x5C]
  float v12; // [esp+0x10] [ebp-0x58]
  int v13; // [esp+0x14] [ebp-0x54]
  float fDeltaTime; // [esp+0x18] [ebp-0x50]
  _BYTE v15[72]; // [esp+0x20] [ebp-0x48] BYREF

  result = (int *)((ScriptSystem *)v1)->Cleanup();
  v3 = fp;
  if ( fp )
  {
    fread(&nVal, 4u, 1u, fp);
    fread(&g_nFrameRate, 4u, 1u, v3);
    g_nUpdateInterval = g_nFrameRate;
    if ( g_nFrameRate < 35 )
      g_nUpdateInterval = 35;
    fread(g_nRoleInitLevel, 0x18u, 1u, v3);
    fread(&::Buffer, 0x1B80u, 1u, v3);
    fread(&((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather, 5u, 1u, v3);
    ((NPC *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->LoadFromStream(v3);
    ((NPC *)&((RoleSystem *)&stru_C059A0)->m_fMoveTargetY)->LoadBufferFromStream(v3);
    v10 = 0.0;
    v11 = 0.0;
    v12 = 0.0;
    fread(&Buffer, 0x1Cu, 1u, v3);
    *(_DWORD *)&g_RoleSystemMain.m_partyActor.m_szTexture[4] = (unsigned __int8)Buffer;
    g_RoleSystemMain.m_fPosX = v10;
    *(_DWORD *)g_RoleSystemMain.m_partyActor.m_szTexture = (unsigned __int8)v13;
    g_RoleSystemMain.m_fPosY = v11;
    g_RoleSystemMain.m_fPosZ = v12;
    ((RoleSystem *)&g_RoleSystemMain)->UpdateMovement(fDeltaTime, 1);
    p_nState = &g_ScriptCounters[0].nState;
    do
    {
      fread(&fp, 1u, 1u, v3);
      p_nState += 4;
      *(p_nState - 4) = (unsigned __int8)fp;
    }
    while ( (int)p_nState < (int)&dword_C020F4 );
    p_nCurCount = &g_ScriptCounters[0].nCurCount;
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
    ((NPC *)nVal)->SetRoleMode();
    v6 = (int *)(&::Buffer.m_partyActor.m_nAnimFrame + 2);
    do
    {
      if ( *v6 )
        v6[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*v6);
      if ( v6[3] )
        v6[5] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v6[3]);
      if ( v6[6] )
        v6[8] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v6[6]);
      if ( v6[9] )
        v6[11] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v6[9]);
      if ( v6[12] )
        v6[14] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v6[12]);
      if ( v6[15] )
        v6[17] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v6[15]);
      ((RoleSystem *)(v6 - 213))->RecalcAggregatedStats(0);
      result = v6 + 30;
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
      v6 += 352;
    }
    while ( (int)v6 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[190] );
  }
  return result;
}

// 0x0040F4B0
int RefreshPartyRoleData()
{
  float *p_m_fMoveRadius; // edi
  int *p_m_pData; // ebx
  int v2; // esi
  int i; // esi
  int v4; // ebp
  float *v5; // esi
  int j; // edi
  int *v7; // esi
  int result; // eax
  float *v9; // [esp+0x10] [ebp-0x24]
  int v10; // [esp+0x14] [ebp-0x20]
  int v11; // [esp+0x18] [ebp-0x1C]

  p_m_fMoveRadius = &Buffer.m_fMoveRadius;
  v11 = 0;
  v10 = 0;
  v9 = &Buffer.m_fMoveRadius;
  p_m_pData = (int *)&g_SceneMgrPrefix.m_pData;
  while ( 1 )
  {
    v2 = *(p_m_pData - 1);
    nullsub_2(v2, *p_m_pData);
    *p_m_pData = v2;
    for ( i = 0; i < 6; ++i )
    {
      if ( *((_BYTE *)p_m_fMoveRadius + i - 296) )
        ((RoleSystem *)*p_m_pData)->CheckVisible();
    }
    v4 = 0;
    v5 = p_m_fMoveRadius;
    do
    {
      for ( j = 0; j < 8; ++j )
      {
        if ( *((_BYTE *)v5 - 96) )
          ((RoleSystem *)*p_m_pData)->CheckVisible();
        v5 = (float *)((char *)v5 + 1);
      }
      ++v4;
    }
    while ( v4 < 6 );
    v7 = (int *)*(p_m_pData - 1);
    for ( result = *p_m_pData; v7 != (int *)*p_m_pData; v7 += 3 )
    {
      v7[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v7);
      result = *p_m_pData;
    }
    p_m_pData += 4;
    v10 += 352;
    v9 += 352;
    v11 += 44;
    if ( (int)p_m_pData >= (int)&Buffer.m_wndcolor )
      break;
    p_m_fMoveRadius = v9;
  }
  return result;
}

// 0x0040FC90
void AddMoney(int nAmount)
{
  LONG bottom; // ecx
  char *v2; // eax
  char *v3; // eax
  CScreenMode *Instance; // eax
  int v5; // [esp-0x4] [ebp-0x104]
  int v6; // [esp-0x4] [ebp-0x104]
  char Buffer[256]; // [esp+0x0] [ebp-0x100] BYREF

  bottom = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
  ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom + nAmount < 0
                                             ? 0
                                             : ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom + nAmount;
  if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom )
  {
    if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom - bottom >= 0 )
    {
      v6 = ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom - bottom;
      v3 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("getmoney");
      _snprintf(Buffer, 0xFFu, v3, v6);
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition("wa006", 1);
    }
    else
    {
      v5 = bottom - ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
      v2 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("lossmoney");
      _snprintf(Buffer, 0xFFu, v2, v5);
    }
    ((InputSystem *)Buffer)->ProcessFrame();
  }
  else
  {
    strcpy(Buffer, ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(name));
    ((InputSystem *)Buffer)->ProcessFrame();
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
  int v9; // [esp+0x0] [ebp-0x1C]

  RefreshPartyRoleData();
  v2 = 6;
  v3 = &dword_C10BA0[12 * nRoleIdx];
  do
  {
    v4 = v3[1];
    if ( nLevel >= v4 && v4 > 0 && *v3 )
    {
      ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v3);
      ((RoleSystem *)*((_DWORD *)&g_SceneMgrPrefix.m_pData + 4 * nRoleIdx))->CheckVisible();
    }
    v3 += 2;
    --v2;
  }
  while ( v2 );
  ((NPC *)v9)->InitAll();
  v5 = g_pCBSystem;
  m_pRoleState = g_pCBSystem->m_pRoleState;
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nRoleIdx + 4] = nLevel;
  *((_DWORD *)&Buffer.m_partyActor.m_fActionAssignParam + 352 * nRoleIdx) = ((CCBRoleState *)v5->m_pRoleState)->GetRoleCount(nLevel);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nRoleIdx + 8] = ((CCBRoleState *)m_pRoleState)->GetSlotState(nRoleIdx, nLevel);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nRoleIdx + 12] = ((CCBRoleState *)m_pRoleState)->CalcSpeedByLevel(nRoleIdx, nLevel);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nRoleIdx + 16] = ((CCBRoleState *)m_pRoleState)->GetActionTypeBySlot(nRoleIdx, nLevel);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nRoleIdx + 20] = ((CCBRoleState *)m_pRoleState)->CalcDefenseByLevel(nRoleIdx, nLevel);
  *(_DWORD *)&Buffer.m_partyActor.m_szTexture[1408 * nRoleIdx + 24] = ((CCBRoleState *)m_pRoleState)->CalcDamage(nRoleIdx, nLevel);
  ((RoleSystem *)((char *)&Buffer + 1408 * nRoleIdx))->RecalcAggregatedStats(0);
  result = &Buffer.m_partyActor.m_curact[1408 * nRoleIdx + 39];
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
  double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st7
  char *v8; // edx
  int i; // esi
  int v10; // edi
  int v11; // esi
  GRPinput *v12; // ecx
  int result; // eax
  int v14; // eax
  void **v15; // ecx
  unsigned __int8 v16; // [esp+0x13] [ebp-0x15]
  int m_mouseMinX; // [esp+0x14] [ebp-0x14]

  v1 = 0;
  v2 = 0;
  m_mouseMinX = -1;
  v16 = 0;
  if ( (int)g_pScriptEventObj <= 0 )
    goto LABEL_37;
  do
  {
    v3 = (GRPinput *)g_pScriptObjArray[v2];
    ((GRPinput *)v3)->SetJoystickFreePos(fVal);
    if ( LOBYTE(v3->m_lpDIDKeyboard) )
    {
      if ( v3->m_mouseMaxY == 1 )
      {
        if ( v3->m_mouseMinX > m_mouseMinX )
          m_mouseMinX = v3->m_mouseMinX;
        v4 = *(float *)&v3->m_mouseMaxX - 1.5;
        if ( v4 >= 0.0 )
          v5 = v4;
        else
          v5 = 0.0;
        v6 = 1.0 - v5 * 0.40000001;
        if ( v6 < 0.0 )
          v6 = 0.0;
        if ( (unsigned __int8)(__int64)(v6 * 255.0) > v16 )
        {
          if ( v4 < 0.0 )
            v4 = 0.0;
          v7 = 1.0 - v4 * 0.40000001;
          if ( v7 < 0.0 )
            v7 = 0.0;
          v16 = (__int64)(v7 * 255.0);
        }
      }
    }
    else
    {
      if ( v3 )
        (*(void ( **)(GRPinput *, int))v3->m_lpDI)(v3, 1);
      if ( v2 >= 0 && v2 < (int)g_pScriptEventObj )
        g_pScriptObjArray[v2] = 0;
      v1 = 1;
    }
    v8 = (char *)g_pScriptEventObj;
    ++v2;
  }
  while ( v2 < (int)g_pScriptEventObj );
  if ( v1 )
  {
    for ( i = 0; i < (int)g_pScriptEventObj; v8 = (char *)g_pScriptEventObj )
    {
      if ( i >= 0 && i < (int)v8 && g_pScriptObjArray[i] )
        ++i;
      else
        ((PtrArray *)&g_pScriptObjArray)->RemoveAt(i, 1);
    }
    v10 = 0;
    v11 = 40;
    if ( (int)v8 > 0 )
    {
      do
      {
        v12 = (GRPinput *)g_pScriptObjArray[v10];
        if ( v12->m_mouseMaxY == 1 )
        {
          ((GRPinput *)v12)->GetMouseSensitivity(v11);
          v11 += 24;
        }
        v8 = (char *)g_pScriptEventObj;
        ++v10;
      }
      while ( v10 < (int)g_pScriptEventObj );
    }
  }
  if ( m_mouseMinX == -1 )
  {
LABEL_37:
    ((UITextArea *)dword_BFDAB0)->ShowWindow();
  }
  else
  {
    v14 = 0;
    if ( (int)v8 > 0 )
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
    sub_445FA0(dword_BFDAB0);
    ((UITextArea *)dword_BFDAB0)->ShowWindow();
    ((UIScene *)dword_BFDAB0)->SetState();
    ((NPC *)dword_BFDAB0)->NPC::UpdateAnim();
  }
  return result;
}

// 0x00411220
int * AssignInt(int *pDst, int *pSrc)
{
  int *result; // eax

  result = pDst;
  if ( pDst )
    *pDst = *pSrc;
  return result;
}

// 0x00413800
gbVec3D * Vec3D_Cross(gbVec3D *pOut, gbVec3D *pA, gbVec3D *pB)
{
  _BYTE v4[12]; // [esp+0x0] [ebp-0xC]

  *(float *)v4 = pA->x - pB->x;
  *(float *)&v4[4] = pA->y - pB->y;
  *pOut = *(gbVec3D *)v4;
  return pOut;
}

// 0x0041C1E0
int old_sbh_page_alloc(__old_sbh_page_struct *_this)
{
  _DWORD *v1; // eax
  int v2; // eax
  _DWORD *v3; // eax
  int result; // eax

  v1 = *(_DWORD **)&_this->alloc_blocks[124];
  if ( v1 )
  {
    *(_DWORD *)&_this->alloc_blocks[132] = v1[40];
    *(_DWORD *)&_this->alloc_blocks[136] = v1[41];
    v2 = v1[42];
  }
  else
  {
    v3 = *(_DWORD **)&_this->alloc_blocks[128];
    if ( !v3 )
      goto LABEL_6;
    *(_DWORD *)&_this->alloc_blocks[132] = v3[10];
    *(_DWORD *)&_this->alloc_blocks[136] = v3[11];
    v2 = v3[12];
  }
  *(_DWORD *)&_this->alloc_blocks[140] = v2;
LABEL_6:
  if ( dword_D8BBEC == 1 )
    *(float *)&_this->alloc_blocks[136] = *((float *)_this + 135) + *(float *)&_this->alloc_blocks[136];
  *(_DWORD *)&_this->alloc_blocks[224] = *(_DWORD *)&_this->alloc_blocks[132];
  *(_DWORD *)&_this->alloc_blocks[228] = *(_DWORD *)&_this->alloc_blocks[136];
  *(_DWORD *)&_this->alloc_blocks[232] = *(_DWORD *)&_this->alloc_blocks[140];
  ((InputSystem *)_this)->InputSystem::ProcessKeyboard();
  return result;
}

// 0x0041C280
int InputUpdate(int _this, int nVal)
{
  int result; // eax
  _DWORD *v4; // eax
  int v5; // eax
  _DWORD *v6; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st4
  double v11; // st5
  double v12; // st7
  double v13; // st7
  long double v14; // st7
  double v15; // st7
  float v16; // [esp+0x4] [ebp-0x34]
  gbVec3D v17; // [esp+0x8] [ebp-0x30] BYREF
  gbVec3D v18; // [esp+0x14] [ebp-0x24] BYREF
  float v19; // [esp+0x20] [ebp-0x18]
  float v20; // [esp+0x24] [ebp-0x14]
  float v21; // [esp+0x28] [ebp-0x10]
  float v22; // [esp+0x2C] [ebp-0xC]
  float y; // [esp+0x30] [ebp-0x8]
  float z; // [esp+0x34] [ebp-0x4]

  result = *(_DWORD *)(_this + 448);
  if ( !result )
    return result;
  v4 = *(_DWORD **)(_this + 380);
  memset(&v17, 0, sizeof(v17));
  if ( v4 )
  {
    *(_DWORD *)(_this + 388) = v4[40];
    *(_DWORD *)(_this + 392) = v4[41];
    v5 = v4[42];
LABEL_6:
    *(_DWORD *)(_this + 396) = v5;
    goto LABEL_7;
  }
  v6 = *(_DWORD **)(_this + 384);
  if ( v6 )
  {
    *(_DWORD *)(_this + 388) = v6[10];
    *(_DWORD *)(_this + 392) = v6[11];
    v5 = v6[12];
    goto LABEL_6;
  }
LABEL_7:
  if ( dword_D8BBEC == 1 )
    *(float *)(_this + 392) = *(float *)(_this + 540) + *(float *)(_this + 392);
  v7 = *(float *)(_this + 480) - *(float *)(_this + 388);
  y = *(float *)(_this + 484) - *(float *)(_this + 392);
  v8 = *(float *)(_this + 488) - *(float *)(_this + 396);
  v17.y = y;
  z = v8;
  v17.x = v7;
  v17.z = z;
  v9 = ((gbVec3D *)&v17)->Length();
  if ( v9 > 0.050000001 )
  {
    v17.y = v17.y / v9;
    v17.z = v17.z / v9;
    v10 = v17.x / v9;
    v22 = v10;
    z = v17.z;
    y = v17.y;
    v11 = (20.0 - v9) * 4.5999999 * *(float *)&nVal;
    v16 = v11;
    v17.x = v11 * v10;
    v17.y = v17.y * v16;
    v17.z = v17.z * v16;
    *(float *)(_this + 480) = v17.x + *(float *)(_this + 480);
    *(float *)(_this + 484) = v17.y + *(float *)(_this + 484);
    *(float *)(_this + 488) = v17.z + *(float *)(_this + 488);
    v19 = *(float *)(_this + 480) - *(float *)(_this + 388);
    v12 = *(float *)(_this + 484) - *(float *)(_this + 392);
    v18.x = v19;
    v20 = v12;
    v13 = *(float *)(_this + 488) - *(float *)(_this + 396);
    v18.y = v20;
    v21 = v13;
    v18.z = v21;
    ((gbVec3D *)&v18)->Normalize();
    if ( z * v18.z + y * v18.y + v18.x * v22 <= 0.0 )
    {
      *(_DWORD *)(_this + 480) = *(_DWORD *)(_this + 388);
      *(_DWORD *)(_this + 484) = *(_DWORD *)(_this + 392);
      *(_DWORD *)(_this + 488) = *(_DWORD *)(_this + 396);
    }
  }
  v14 = *(float *)&nVal * *(float *)(_this + 460) * 32.0;
  if ( fabs(*(float *)(_this + 460)) > fabs(v14) )
  {
    *(float *)(_this + 456) = v14 + *(float *)(_this + 456);
    *(float *)(_this + 460) = *(float *)(_this + 460) - v14;
  }
  else
  {
    v15 = *(float *)(_this + 460) + *(float *)(_this + 456);
    *(_DWORD *)(_this + 460) = 0;
    *(float *)(_this + 456) = v15;
  }
  if ( dword_D8BBEC == 1 )
    ((InputSystem *)nVal)->ProcessMouse();
  ((InputSystem *)_this)->InputSystem::ProcessKeyboard();
  return result;
}

// 0x0041D100
int old_sbh_page_manage(__old_sbh_page_struct *_this, int nVal)
{
  int result; // eax

  switch ( nVal )
  {
    case 0:
      *(_DWORD *)_this->alloc_map = 0;
      _this->free_paras_at_start = 1104150528;
      *(_DWORD *)&_this->alloc_blocks[224] = 0;
      *(_DWORD *)&_this->alloc_blocks[228] = 0;
      *(_DWORD *)&_this->alloc_blocks[232] = 0;
      *(_DWORD *)&_this->alloc_blocks[212] = 1150222336;
      *(_DWORD *)&_this->alloc_blocks[200] = -1083490798;
      *(_DWORD *)&_this->alloc_blocks[196] = -1090015724;
      break;
    case 1:
      *(_DWORD *)&_this->alloc_blocks[224] = 0;
      *(_DWORD *)&_this->alloc_blocks[228] = 0;
      *(_DWORD *)&_this->alloc_blocks[232] = 0;
      *(_DWORD *)_this->alloc_map = 0;
      _this->free_paras_at_start = 1103128166;
      *(_DWORD *)&_this->alloc_blocks[212] = 1143734272;
      *(_DWORD *)&_this->alloc_blocks[200] = 1058309259;
      goto LABEL_6;
    case 2:
      *(_DWORD *)&_this->alloc_blocks[224] = 0;
      *(_DWORD *)&_this->alloc_blocks[228] = 0;
      *(_DWORD *)&_this->alloc_blocks[232] = 0;
      *(_DWORD *)_this->alloc_map = 0;
      _this->free_paras_at_start = 1103128166;
      *(_DWORD *)&_this->alloc_blocks[212] = 1143734272;
      *(_DWORD *)&_this->alloc_blocks[200] = -1089174389;
      goto LABEL_6;
    case 3:
      *(_DWORD *)&_this->alloc_blocks[224] = 0;
      *(_DWORD *)&_this->alloc_blocks[228] = 0;
      *(_DWORD *)&_this->alloc_blocks[232] = 0;
      *(_DWORD *)_this->alloc_map = 0;
      _this->free_paras_at_start = 1103128166;
      *(_DWORD *)&_this->alloc_blocks[212] = 1143734272;
      *(_DWORD *)&_this->alloc_blocks[200] = 0;
LABEL_6:
      *(_DWORD *)&_this->alloc_blocks[196] = -1095887749;
      break;
    default:
      break;
  }
  *(_DWORD *)&_this->alloc_blocks[204] = 0;
  old_sbh_page_alloc(_this);
  ((InputSystem *)_this)->InputSystem::ProcessKeyboard();
  return result;
}

// 0x0041EB80
void UIPostUpdate(gbSound2DNode *_this)
{
  RoleSystem *v1; // eax
  int RolePtr; // esi
  int v3; // edi
  __int64 v4; // rax
  int v5; // ecx
  ScriptSystem *v6; // ecx
  int v7; // edi
  gbSound2DNode *v8; // esi
  int v9; // [esp-0x8] [ebp-0x10]

  if ( g_pRoleSystem )
  {
    v9 = *(_DWORD *)g_pRoleSystem->m_partyActor.m_szTexture;
    v1 = (RoleSystem *)UISceneUpdate();
    RolePtr = ((RoleSystem *)v1)->GetRolePtr(v9);
    v3 = (__int64)((*(float *)&g_pRoleSystem->m_fontcolor.Color - *(float *)(RolePtr + 128)) / g_fTileSize);
    v4 = (__int64)((*(float *)&g_pRoleSystem->m_id - *(float *)(RolePtr + 136)) / g_fTileSize);
    if ( v3 < 0 || (v5 = *(_DWORD *)(RolePtr + 152), v3 >= v5) || (int)v4 < 0 || (int)v4 >= *(_DWORD *)(RolePtr + 156) )
    {
      v7 = 2;
    }
    else
    {
      v6 = (ScriptSystem *)(v3 + v4 * v5);
      v7 = *(unsigned __int8 *)(*(_DWORD *)(RolePtr + 160) + 8 * (_DWORD)v6 + 5);
      if ( v7 == 6 )
      {
        if ( g_nCurrentEventId != 2 )
          ((ScriptSystem *)v6)->RunEvent(2, 1);
      }
      else if ( v7 == 10 )
      {
        if ( g_nCurrentEventId )
          ((ScriptSystem *)v6)->RunEvent(0, 1);
      }
      else if ( v7 == 13 && g_nCurrentEventId != 3 )
      {
        ((ScriptSystem *)v6)->RunEvent(3, 1);
      }
    }
    if ( (g_dwGameFlags & 1) != 0 )
    {
      v8 = 0;
      if ( g_pRoleSystem->m_FrameA.m_childs.m_nSize )
      {
        if ( g_pRoleSystem->m_FrameA.m_childs.m_nSize == 1 )
        {
          v8 = g_pAmbientTable[((CameraCtrl *)v7)->GetModeByIndex()];
        }
        else if ( g_pRoleSystem->m_FrameA.m_childs.m_nSize == 2 )
        {
          v8 = g_pBGMTable[((CameraCtrl *)v7)->GetModeByIndex()];
        }
      }
      else
      {
        v8 = 0;
      }
      if ( g_pCurrentBGM )
      {
        if ( v8 )
        {
          if ( g_pCurrentBGM != v8 )
          {
            ((gbSound2DNode *)g_pCurrentBGM)->Stop();
            g_pCurrentBGM = v8;
            ((gbSound2DNode *)v8)->Play();
          }
        }
        else
        {
          ((gbSound2DNode *)g_pCurrentBGM)->Stop();
          g_pCurrentBGM = 0;
        }
      }
      else if ( v8 )
      {
        g_pCurrentBGM = v8;
        ((gbSound2DNode *)v8)->Play();
      }
    }
  }
}

// 0x00420430
void * sdtor_2(void *Block, char a2)
{
  sub_420450(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00421C40
int UINotifyUpdate(int *_this)
{
  RoleSystem *v1; // ebx
  int v3; // edi
  RoleSystem *i; // esi

  v1 = g_pRoleSystem;
  v3 = 0;
  if ( *(_this + 14392) <= 0 )
    return 0;
  for ( i = (RoleSystem *)(_this + 14393);
        i->m_nActionState != 4 || !((RoleSystem *)i)->AdvancePathStep((float *)&v1->m_fontcolor.Color);
        i = (RoleSystem *)((char *)i + 8704) )
  {
    if ( ++v3 >= *(_this + 14392) )
      return 0;
  }
  return 1;
}

// 0x004226F0
int UISceneUpdate()
{
  return 493156 * (dword_D8BBEC == 1) + 12722152;
}

// 0x00422950
gbVFileSystem * LoadScene(double sceneNames, char *arg8, char *pszBuf, char pData, char pData2)
{
  PAL3 *v5; // ecx
  const char *v6; // ebx
  int v7; // ebp
  int v8; // esi
  int v9; // edi
  RoleSystem *RoleDataOffset; // eax
  RoleSystem *v11; // eax
  Actor *SaveDataManager; // eax
  int v13; // eax
  CameraCtrl *v14; // ecx
  int v15; // ebx
  PalScript *v16; // eax
  UICursor *v17; // ecx
  void ( ***v18)(_DWORD, int); // ecx
  CScreenMode *Instance; // eax
  int v20; // ebp
  gbSceneGraph *pSceneGraph; // esi
  gbSceneGraph *v22; // ecx
  gbVFileSystem *result; // eax
  double v24; // [esp-0x4] [ebp-0x340]
  BOOL v25; // [esp-0x4] [ebp-0x340]
  gbVisNode *v26; // [esp-0x4] [ebp-0x340]
  int *v27; // [esp+0x4] [ebp-0x338]
  CUtil *pUtil; // [esp+0x10] [ebp-0x32C]
  OpenSceneFile v29; // [esp+0x14] [ebp-0x328] BYREF
  int v30; // [esp+0x18] [ebp-0x324]
  int v31; // [esp+0x1C] [ebp-0x320]
  int v32; // [esp+0x20] [ebp-0x31C]
  int v33; // [esp+0x24] [ebp-0x318]
  int v34; // [esp+0x28] [ebp-0x314]
  char String1[260]; // [esp+0x2C] [ebp-0x310] BYREF
  char Buffer[512]; // [esp+0x130] [ebp-0x20C] BYREF
  int v37; // [esp+0x338] [ebp-0x4]

  v33 = g_nSceneState;
  if ( (_BYTE)arg8 )
  {
    pUtil = (CUtil *)g_CCBEditorInst.m_dwTrickID[361];
    ((CGameData *)&g_gamefrm)->Load((CUtil *)0xE);
    ((PAL3 *)v5)->Render();
  }
  ((PAL3 *)pszBuf)->ResetForNewScene();
  v6 = (const char *)LODWORD(sceneNames);
  ((VFileSystem *)&g_RoleSystemInstance)->_auto_4221d0((char *)LODWORD(sceneNames), (char *)HIDWORD(sceneNames));
  CameraCtrl::AttachToRole();
  v34 = dword_D8BBEC;
  dword_D8BBEC = LODWORD(g_RoleSystemInstance.m_fDirZ);
  v7 = 493156 * (LODWORD(g_RoleSystemInstance.m_fDirZ) == 1) + 12722152;
  v25 = !_strcmpi((const char *)v7, (const char *)LODWORD(sceneNames))
     && !_strcmpi((const char *)(v7 + 32), (const char *)HIDWORD(sceneNames));
  sub_41FA90((char *)v7, (int)&g_RoleSystemInstance, v25);
  sub_421830((gbVisNode **)v7);
  SceneMgr::InitSceneRoles();
  v8 = 0;
  if ( *(int *)(v7 + 492772) > 0 )
  {
    v9 = v7 + 492776;
    do
    {
      RoleDataOffset = (RoleSystem *)GetRoleDataOffset(v8);
      if ( !((RoleSystem *)RoleDataOffset)->BuildModelPath((const char *)v7) )
      {
        v11 = (RoleSystem *)GetRoleDataOffset(v8);
        ((RoleSystem *)v11)->LoadRoleImage(v9, (const char *)v7);
        if ( ((UIScene *)pszBuf)->ProcessInput(::pszBuf)
          || ((UIScene *)pszBuf)->ProcessInput("q08f")
          || ((UIScene *)pszBuf)->ProcessInput("q08p") )
        {
          *(_DWORD *)(GetRoleDataOffset(v8) + 16) = (v8 + 1) % 2;
          v6 = (const char *)LODWORD(sceneNames);
        }
        else
        {
          *(_DWORD *)(GetRoleDataOffset(v8) + 16) = v8;
        }
        if ( !dword_D8BBEC
          || (SaveDataManager = (Actor *)GetSaveDataManager(),
              ((Actor *)SaveDataManager)->SearchAnimByIndex((char *)v7, (char *)(v7 + 32))) )
        {
          v13 = GetRoleDataOffset(v8);
          sub_4206F0(v13);
        }
      }
      ++v8;
      v9 += 164;
    }
    while ( v8 < *(_DWORD *)(v7 + 492772) );
  }
  sprintf(Buffer, "%s.sce", v6);
  strcpy(String1, "scene\\");
  strcat(String1, v6);
  v37 = 0;
  ((PalScriptMgr *)Buffer)->Update();
  ((PalScriptMgr *)v6)->FindScriptByDesc((const char *)HIDWORD(sceneNames));
  ((CameraCtrl *)1)->AttachToRole();
  if ( dword_D8BBEC == 1 )
  {
    g_nRoleSystem_58B234 = 0;
    ((RoleSystem *)SLODWORD(g_RoleSystemInstance.m_fDirZ))->SetCameraMode();
  }
  else
  {
    g_nRoleSystem_58B234 = 1;
    ((RoleSystem *)SLODWORD(g_RoleSystemInstance.m_fDirZ))->SetCameraMode();
    v14 = g_pCameraCtrl;
    if ( *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) )
      ((_Console *)g_pCameraCtrl)->SetActive((int)g_pRoleSystem);
  }
  v15 = v34;
  if ( v34 == 2 && dword_D8BBEC != 2 )
    ((scAsmDecoder *)v14)->Execute(0, 1);
  ((CameraCtrl *)&g_pCameraCtrl)->SetAsCurrent(3);
  ((RoleCameraCtrl *)&stru_DBA134)->ShowWindow();
  LODWORD(v24) = v7;
  v16 = (PalScript *)GetSaveDataManager();
  ((PalScript *)v16)->DestroyInstances(v24, v27);
  ((GRPinput *)&g_Input)->Reset();
  ((UICursor *)v17)->IRender();
  if ( (_BYTE)arg8 )
  {
    if ( pUtil == (CUtil *)4 )
      pUtil = 0;
    ((CGameData *)&g_gamefrm)->Load(pUtil);
  }
  v18 = (void ( ***)(_DWORD, int))(((CGameData *)&g_gamefrm)->SetMode(0) + 72);
  if ( dword_D8BBEC == 1 )
    (**v18)(v18, 0);
  else
    (**v18)(v18, 1);
  if ( !CScreenMode::GetInstance()->m_bRenderAlt )
  {
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->PlaySceneMusic((char *)v7, (const char *)(v7 + 32), 0);
  }
  v20 = *(_DWORD *)(v7 + 104);
  if ( v20 )
  {
    v30 = 1120403456;
    v31 = 1120403456;
    v32 = 1120403456;
    sub_53DAD0();
    sub_53D460(v20, 1120403456, 1120403456, 1120403456);
    pSceneGraph = gfxMgr->pSceneGraph;
    v26 = (gbVisNode *)sub_53DAD0();
    v22 = pSceneGraph;
  }
  else
  {
    v26 = 0;
    v22 = gfxMgr->pSceneGraph;
  }
  ((gbSceneGraph *)v22)->AddSkyBox(v26);
  g_nSceneState = v33;
  CombatEnter();
  g_bRoleSystem_5CEFA9 = dword_D8BBEC != 2;
  if ( ((UIScene *)"m02")->ProcessInput(0) )
    g_bRoleSystem_5CEFA9 = 0;
  ((CameraCtrl *)&g_pCameraCtrl)->SetCamMode(0);
  if ( v15 != 2 && dword_D8BBEC == 2 )
    BYTE2(((PalScript *)&stru_C11720)->_todo_48) = 1;
  v37 = -1;
  ((OpenSceneFile *)&v29)->_OpenSceneFile();
  return result;
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
  int *p_capacity; // ebx
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
    ((PalScriptMgr *)g_nunknown_libname_331_C12B3C)->ClearAllScript();
    if ( !v2 )
    {
      if ( (_BYTE)g_nunknown_libname_331_C12B38 == 6 || (_BYTE)g_nunknown_libname_331_C12B38 == 14 )
      {
        ((RoleSystem *)&g_pRoleSystem)->GetMoveState();
        v3 = g_nunknown_libname_331_C12B40;
        if ( *(_DWORD *)(g_nunknown_libname_331_C12B40 + 88) == 3 )
        {
          ((gbVisNode *)*(gbVisNode **)(g_nunknown_libname_331_C12B40 + 92))->SetTimeScale(0.0);
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
  v4 = dword_D8BBEC == 1;
  v5 = 493156 * v4 + 12722152;
  v21 = v5;
  if ( g_nCameraUpdateCount > 0 )
  {
    SoundList = (CScreenMode *)((CScreenMode *)v4)->GetSoundList();
    if ( ((CScreenMode *)SoundList)->IsAudioReady() )
    {
      v7 = *(_DWORD *)(v5 + 57568);
      v19 = v1;
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
                    ((RoleSystem *)(v9 - 158))->CheckMoveCollisionDist((int)(v11 - 36), v19);
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
      if ( dword_D8BBEC != 2 )
      {
        v20 = 0;
        p_capacity = &((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.capacity;
        do
        {
          if ( p_capacity[158] && p_capacity[316] != 4 )
          {
            if ( (int)p_capacity < (int)dword_C0E760 )
            {
              v14 = dword_C0EC50;
              v15 = 4 - v20;
              do
              {
                if ( *(v14 - 158) && *v14 != 4 )
                  ((RoleSystem *)p_capacity)->CheckMoveCollisionDist((int)(v14 - 316), v19);
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
                  ((RoleSystem *)p_capacity)->CheckMoveCollisionDist((int)(v17 - 36), v19);
                ++v16;
                v17 += 2176;
              }
              while ( v16 < *(_DWORD *)(v21 + 57568) );
            }
          }
          p_capacity += 2176;
          ++v20;
        }
        while ( (int)p_capacity < (int)&g_pScriptArrayEnd );
        v5 = v21;
      }
      if ( g_pRoleSystem && g_pRoleSystem->m_FrameA.m_rect.right != 4 )
        ((PalScriptMgr *)v5)->CheckTileScript(g_pRoleSystem, fVal, 0);
    }
  }
  if ( dword_D8BBEC != 1 )
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
    || (result = (gbGfxManager *)((UIScene *)"m19")->ProcessInput(0), (_BYTE)result)
    || (result = (gbGfxManager *)((UIScene *)"m20")->ProcessInput(0), (_BYTE)result)
    || (result = (gbGfxManager *)((UIScene *)"m25")->ProcessInput(0), (_BYTE)result) )
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
  if ( dword_D8BBEC == 2 )
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
    v2 = pPoint[1];
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
      result = *(gbActorMgr **)(v0 + 4);
      if ( result )
      {
        ((gbActorMgr *)g_pActorMgr)->DestroyActor(*(gbActor **)(v0 + 4));
        v1[1] = 0;
      }
      goto LABEL_4;
    case 2:
    case 3:
LABEL_4:
      v3 = (int ( ***)(_DWORD, int))v1[1];
      if ( v3 )
      {
        result = (gbActorMgr *)(**v3)(v3, 1);
        v1[1] = 0;
      }
      goto LABEL_6;
    case 4:
LABEL_6:
      v4 = (int ( ***)(_DWORD, int))v1[1];
      if ( v4 )
      {
        result = (gbActorMgr *)(**v4)(v4, 1);
        v1[1] = 0;
      }
      break;
    default:
      break;
  }
  *v1 = 0;
  return result;
}

// 0x0042CB70
void FightInfo()
{
  _DWORD *v0; // ecx
  _DWORD *v1; // esi
  RoleSystem *v2; // ebp
  int v3; // edx
  int v4; // eax
  int v5; // eax
  char *bottom; // edi
  char *v7; // ecx
  void *v8; // esi
  char *v9; // eax
  float x; // eax
  float v11; // edx
  float v12; // ecx
  UIWnd *v13; // esi
  unsigned int m_pfather; // eax
  UIWnd *v15; // eax
  float v16; // eax
  float v17; // edx
  UIWnd *v18; // eax
  int v19; // edi
  gbVec3D *RoleName; // eax
  gbVec3D *v21; // edi
  float y; // edx
  float z; // ecx
  LONG v24; // edx
  float v25; // edx
  float v26; // ecx
  UIWnd *v27; // edx
  gbVec3D v28; // [esp+0xC] [ebp-0x5C] BYREF
  UIWnd *v29; // [esp+0x18] [ebp-0x50]
  _DWORD v30[19]; // [esp+0x1C] [ebp-0x4C] BYREF
  _DWORD *v31; // [esp+0x6C] [ebp+0x4]
  unsigned __int8 v32; // [esp+0x70] [ebp+0x8]
  unsigned __int8 v33; // [esp+0x74] [ebp+0xC]

  v1 = v0;
  GetCGEntry((char *)v30);
  LOBYTE(v30[0]) = 2;
  v30[2] = 0;
  v2 = (RoleSystem *)(v1 + 207);
  v30[3] = LODWORD(g_pRoleSystem->m_fPosX);
  v30[4] = LODWORD(g_pRoleSystem->m_fPosY);
  v30[5] = LODWORD(g_pRoleSystem->m_fPosZ);
  v3 = v31[1];
  v4 = v31[2];
  v30[6] = *v31;
  v30[7] = v3;
  v30[8] = v4;
  v5 = v1[218];
  v30[15] = v32;
  v30[16] = v33;
  if ( !v5 || (bottom = (char *)v1[214], v7 = (char *)v1[213], bottom == v7) )
  {
    v8 = (void *)operator new(0xFBCu);
    if ( v2->m_childs.m_nSize )
    {
      m_pfather = (unsigned int)v2->m_pfather;
      if ( (char *)m_pfather >= &v2->m_childs.m_pData[4 * v2->m_childs.capacity - 4] )
      {
        v19 = ((int)(m_pfather - v2->m_rect.left) >> 2) + 1;
        RoleName = (gbVec3D *)((RoleSystem *)v2)->GetRoleName(2 * v19);
        v21 = (gbVec3D *)((char *)RoleName + 4 * v19);
        LODWORD(v21->x) = v8;
        ((gbVec3D *)&v28)->Copy((int)v2->m_id, RoleName);
        y = v28.y;
        v2->m_fontcolor.Color = LODWORD(v28.x);
        z = v28.z;
        *(float *)&v2->m_wndcolor.Color = y;
        v24 = (LONG)v29;
        *(float *)&v2->m_id = z;
        v2->m_rect.left = v24;
        ((gbVec3D *)&v28)->Copy((int)v8, v21);
        v25 = v28.y;
        v2->m_rect.top = LODWORD(v28.x);
        v26 = v28.z;
        *(float *)&v2->m_rect.right = v25;
        v27 = v29;
        *(float *)&v2->m_rect.bottom = v26;
        v2->m_pfather = v27;
      }
      else
      {
        v15 = (UIWnd *)(m_pfather + 4);
        v2->m_pfather = v15;
// [VFTABLE] v15->__vftable = v8;
        ((gbVec3D *)&v28)->Copy((int)v8, (gbVec3D *)v2->m_pfather);
        v16 = v28.y;
        v2->m_rect.top = LODWORD(v28.x);
        v17 = v28.z;
        *(float *)&v2->m_rect.right = v16;
        v18 = v29;
        *(float *)&v2->m_rect.bottom = v17;
        v2->m_pfather = v18;
      }
    }
    else
    {
      v2->m_childs.capacity = 2;
      v9 = (char *)operator new(8u);
      v2->m_childs.m_pData = v9;
      *((_DWORD *)v9 + 1) = v8;
      ((gbVec3D *)&v28)->Copy((int)&v8[70].Create, (gbVec3D *)(v2->m_childs.m_pData + 4));
      x = v28.x;
      v11 = v28.z;
      v12 = v28.y;
      v13 = v29;
      v2->m_fontcolor.Color = LODWORD(v28.x);
      *(float *)&v2->m_wndcolor.Color = v12;
      *(float *)&v2->m_id = v11;
      v2->m_rect.left = (LONG)v13;
      *(float *)&v2->m_rect.top = x;
      *(float *)&v2->m_rect.right = v12;
      *(float *)&v2->m_rect.bottom = v11;
      v2->m_pfather = v13;
    }
    bottom = (char *)v2->m_rect.bottom;
    v2->m_rect.bottom = (LONG)(bottom + 76);
    if ( !bottom )
      goto LABEL_16;
    goto LABEL_15;
  }
  v1[214] = bottom + 76;
  if ( bottom + 76 != v7 )
  {
    if ( !bottom )
    {
LABEL_16:
      ++v2->m_childs.m_nSize;
      return;
    }
LABEL_15:
    qmemcpy(bottom, v30, 0x4Cu);
    goto LABEL_16;
  }
  if ( bottom )
    qmemcpy(bottom, v30, 0x4Cu);
  ((ScriptVM *)v2)->GetString();
  ++v1[218];
}

// 0x00431760
PalScript * sdtor_23(PalScript *Block, char a2)
{
  ((PalScript *)Block)->ReleaseFrame();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00431870
int * ctor_0x431870(int *_this)
{
  *(_this + 128) = 0;
  *(_this + 129) = 0;
  *(_this + 130) = 0;
  memset(_this, 0, 0x200u);
  return _this;
}

// 0x00432600
char FindScriptEventByID(int nEventId)
{
  int v1; // eax
  _DWORD *i; // ecx

  v1 = 0;
  if ( !LOWORD(((GRPinput *)&stru_D8C2B8)->m_joystickDeltaY) )
    return 0;
  for ( i = *(_DWORD **)((GRPinput *)&stru_D8C2B8)->m_keyStates; *i != nEventId; i += 18 )
  {
    if ( ++v1 >= LOWORD(((GRPinput *)&stru_D8C2B8)->m_joystickDeltaY) )
      return 0;
  }
  return 1;
}

// 0x00432870
unsigned __int8 * GetOpcodeParamTypes()
{
  return &((GRPinput *)&stru_D8C2B8)->m_keyStates[56];
}

// 0x00432890
void InitOpcodeEntry()
{
  ResizeOpcodeParams((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[56]);
}

// 0x004328D0
void InitScriptEventArray()
{
  if ( (((GRPinput *)&stru_D8C2B8)->m_keyStates[32] & 1) == 0 )
  {
    ((GRPinput *)&stru_D8C2B8)->m_keyStates[32] |= 1u;
    ((UIListBox *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[40])->ReleaseVtable();
  }
}

// 0x00432930
void SetScriptInitFlag()
{
  if ( (((GRPinput *)&stru_D8C2B8)->m_keyStates[32] & 2) == 0 )
    ((GRPinput *)&stru_D8C2B8)->m_keyStates[32] |= 2u;
}

// 0x00432980
void ResizeOpcodeParams(PtrArray *_this)
{
  ((PtrArray *)_this)->SetSize();
}

// 0x00432990
int LoadScriptFile(const char *pszFileName)
{
  InitSceOpcodeTable();
  ((GRPinput *)&stru_D8C2B8)->KeyInfo[147].CountMode = 0;
  return sub_4339F0(pszFileName);
}

// 0x004329B0
int InitSceOpcodeTable()
{
  memset(&((GRPinput *)&stru_D8C2B8)->m_keyRaw[56], 0, 0x2000u);
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[72] = PalScript::Op_Idle;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[76] = 2;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[84] = 1;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[88] = PalScript::Op_ScriptRunMode;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[92] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[100] = 1;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[104] = PalScript::Op_GoTo;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[108] = 4;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[116] = 1;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[120] = PalScript::Op_FCZero;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[132] = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[22] = (ULONG)PalScript::Op_Rand;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[25]) = 0;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[136] = PalScript::Op_FNOT;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[140] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[148] = 1;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[152] = PalScript::Op_FOP;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[156] = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[157] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[164] = 2;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[168] = PalScript::Op_GT;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[172] = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[173] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[180] = 2;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[184] = PalScript::Op_LS;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[188] = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[189] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[196] = 2;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[200] = PalScript::Op_EQ;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[204] = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[205] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[212] = 2;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[216] = PalScript::Op_NEQ;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[220] = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[221] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[228] = 2;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[232] = PalScript::Op_GEQ;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[236] = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[237] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[244] = 2;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_keyRaw[248] = PalScript::Op_LEQ;
  ((GRPinput *)&stru_D8C2B8)->m_keyRaw[252] = 4;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[2] = (ULONG)PalScript::Op_TestGoto;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[3]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[5]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[6] = (ULONG)PalScript::Op_Let;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[7]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[9]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[10] = (ULONG)PalScript::Op_AddEx;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[11]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[13]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[14] = (ULONG)PalScript::Op_Sub;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[15]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[17]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[18] = (ULONG)PalScript::Op_Call;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[19]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[21]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[26] = (ULONG)PalScript::Op_Between;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[27]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[27]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[29]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[30] = (ULONG)PalScript::Op_RolePathTo;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[31] = 16843009;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[33]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[242][0] = (ULONG)PalScript::Op_RolePathOutToTile;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[242][1] = 16843009;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[243][1]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[34] = (ULONG)PalScript::Op_RolePathOut;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[35]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[35]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[37]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[38] = (ULONG)PalScript::Op_RoleSetPos;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[39]) = 769;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[39]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[41]) = 3;
  *(_DWORD *)&((GRPinput *)&stru_D8C2B8)->m_shiftedKeyStates[96] = PalScript::CmdGetSceneObject;
  ((GRPinput *)&stru_D8C2B8)->m_shiftedKeyStates[100] = 1;
  *(_WORD *)&((GRPinput *)&stru_D8C2B8)->m_shiftedKeyStates[108] = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[42] = (ULONG)PalScript::Op_RoleShowAction;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[43]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[45]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[46] = (ULONG)PalScript::Op_RoleEndAction;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[47]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[49]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[50] = (ULONG)PalScript::Op_RoleSetFace;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[53]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[54] = (ULONG)PalScript::Op_RoleTurnFace;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[57]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[58] = (ULONG)PalScript::Op_TeamOpen;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[59]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[61]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[62] = (ULONG)PalScript::Op_TeamClose;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[63]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[65]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[66] = (ULONG)PalScript::Op_RoleInput;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[67]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[69]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[244][0] = (ULONG)PalScript::Op_RoleActive;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[244][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[245][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[246][0] = (ULONG)PalScript::Op_RoleScript;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[246][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[247][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[248][0] = (ULONG)PalScript::Op_InTeamExecScript;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[248][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[249][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[250][0] = (ULONG)PalScript::Op_RoleSetLayerByObj;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[250][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[251][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[252][0] = (ULONG)PalScript::Op_RoleCtrl;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[252][1]) = 513;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[253][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[254][0] = (ULONG)PalScript::Op_RoleOverlap;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[254][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[255][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[256][0] = (ULONG)PalScript::Op_RoleScaleEx;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[256][1]) = 513;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[257][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[258][0] = (ULONG)PalScript::Op_ShowActAutoStandEx;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[258][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[259][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[260][0] = (ULONG)PalScript::Op_RoleMoveBackEx;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[260][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[261][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[262][0] = (ULONG)PalScript::Op_RoleFaceRoleEx;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[263][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[264][0] = (ULONG)PalScript::Op_RoleTurnFaceAEx;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[265][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[266][0] = (ULONG)PalScript::Op_TeamOpenAStartMove;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[266][1] = 33686017;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[267][1]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[268][0] = (ULONG)PalScript::Op_TeamCloseA;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[268][1] = 16843009;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[269][1]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[70] = (ULONG)PalScript::Op_RoleActiveShort;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[71]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[73]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[74] = (ULONG)PalScript::Op_RoleScriptInitCam;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[75]) = 514;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[75]) = 2;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[77]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[78] = (ULONG)PalScript::Op_InTeam;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[79]) = 514;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[79]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[81]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[82] = (ULONG)PalScript::Op_RoleSetLayer;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[83] = 16908802;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[85]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[86] = (ULONG)PalScript::Op_RoleCtrlEx;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[87] = 33686018;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[88]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[89]) = 5;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[90] = (ULONG)PalScript::Op_RoleOverlapEx;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[91] = 16908802;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[93]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[94] = (ULONG)PalScript::Op_RoleScale;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[95] = 33686018;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[96]) = 514;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[97]) = 6;
  ((GRPinput *)&stru_D8C2B8)->charTOscan[251] = (ULONG)PalScript::Op_CameraPush;
  ((GRPinput *)&stru_D8C2B8)->charTOscan[252] = 33686018;
  LOWORD(((GRPinput *)&stru_D8C2B8)->charTOscan[253]) = 514;
  BYTE2(((GRPinput *)&stru_D8C2B8)->charTOscan[253]) = 2;
  LOWORD(((GRPinput *)&stru_D8C2B8)->charTOscan[254]) = 7;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[98] = (ULONG)PalScript::Op_ShowActAutoStand;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[99]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[101]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[102] = (ULONG)PalScript::Op_RoleMoveBack;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[105]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[106] = (ULONG)PalScript::Op_RoleFaceRole;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[109]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_DIKToKEY[72] = (ULONG)GetCamera_4;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_DIKToKEY[73]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_DIKToKEY[75]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_DIKToKEY[76] = (ULONG)GetCurrentCamera;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_DIKToKEY[77]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_DIKToKEY[79]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[110] = (ULONG)PalScript::Op_RoleTurnFaceA;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[111]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[111]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[113]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[114] = (ULONG)PalScript::Op_TeamOpenA;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[115]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[115]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[117]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[118] = (ULONG)PalScript::Op_TeamCloseAEx;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[119]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[121]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[122] = (ULONG)PalScript::Op_RoleSpaceWalk;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[123]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[125]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[126] = (ULONG)PalScript::Op_RoleMoveTo;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[127]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[129]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[130] = (ULONG)PalScript::Op_CameraFocusRole;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[131]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[131]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[133]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[134] = (ULONG)PalScript::Op_CameraFocusPoint;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[135]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[137]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[138] = (ULONG)PalScript::Op_LoseItem;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[139]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[141]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[142] = (ULONG)PalScript::Op_CameraRotate;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[143]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[145]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[146] = (ULONG)PalScript::Op_CameraMove;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[147]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[149]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[150] = (ULONG)PalScript::Op_CameraWag;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[151]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[153]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[154] = (ULONG)PalScript::Op_CameraSet;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[155]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[157]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[158] = (ULONG)PalScript::Op_CameraTrans;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[159]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[161]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[162] = (ULONG)PalScript::Op_CameraDefault;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[163]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[165]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[166] = (ULONG)PalScript::Op_CameraPushState;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[167]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[169]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[190] = (ULONG)PalScript::Op_LK_Ghost;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[191]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[193]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[194] = (ULONG)PalScript::Op_FavorAdd;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[195]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[197]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[198] = (ULONG)PalScript::Op_Team;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[199]) = 3;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[201]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[202] = (ULONG)PalScript::Op_AddRoleAtt;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[203]) = 771;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[205]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[206] = (ULONG)PalScript::Op_AddItem;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[207]) = 769;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[209]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[210] = (ULONG)PalScript::Op_RemoveItem;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[211]) = -6;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[213]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[214] = (ULONG)PalScript::Op_AddMoney;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[215]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[217]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[218] = (ULONG)PalScript::Op_GetMoney;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[219]) = 769;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[219]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[221]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[222] = (ULONG)PalScript::Op_GetFavor;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[223]) = 3;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[225]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[226] = (ULONG)PalScript::Op_AddSkill;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[229]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[230] = (ULONG)PalScript::Op_GetFavorite;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[233]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[234] = (ULONG)PalScript::Op_GetDislike;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[235]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[237]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[238] = (ULONG)PalScript::Op_FullRoleAtt;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[239]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[241]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[242] = (ULONG)PalScript::Op_DlgPos;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[243] = 16843009;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[245]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[246] = (ULONG)PalScript::Op_DlgFont;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[247]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[249]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[254] = (ULONG)PalScript::Op_LoadScene;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[255]) = 3;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[257]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[258] = (ULONG)PalScript::Op_DlgHead;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[259]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[261]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[262] = (ULONG)PalScript::Op_DlgSel;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[263]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[265]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[266] = (ULONG)PalScript::Op_GetDlgSel;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[267]) = 259;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyPressTimes[269]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[0][0] = (ULONG)PalScript::Op_DlgFace;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[0][1] = 16843009;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[1][0]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[1][1]) = 6;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[2][0] = (ULONG)PalScript::Op_Note;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[3][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[4][0] = (ULONG)PalScript::Op_FadeOut;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[4][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[5][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[6][0] = (ULONG)PalScript::Op_FadeIn;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[7][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[8][0] = (ULONG)PalScript::Op_RoleStop;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[8][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[9][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[10][0] = (ULONG)PalScript::Op_RoleEmote;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[10][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[11][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[12][0] = (ULONG)PalScript::Op_Combat;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[12][1]) = 259;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[13][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[14][0] = (ULONG)PalScript::Op_Climb;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[14][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[15][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[16][0] = (ULONG)PalScript::Op_DlgTime;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[16][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[17][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[18][0] = (ULONG)PalScript::Op_GetTimeSel;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[18][1]) = 514;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[18][1]) = 2;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[19][1]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[20][0] = (ULONG)PalScript::Op_HaveItem;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[20][1] = 33686017;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[21][0]) = 2;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[21][1]) = 5;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[22][0] = (ULONG)PalScript::Op_PlaySound;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[23][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[40][0] = (ULONG)PalScript::Op_HY_Mode;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[40][1]) = 3;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[41][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[42][0] = (ULONG)PalScript::Op_HY_FLY;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[42][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[43][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[44][0] = (ULONG)PalScript::Op_ObjectMove;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[44][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[45][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[46][0] = (ULONG)PalScript::Op_FadeNormal;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[46][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[47][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[48][0] = (ULONG)PalScript::Op_Deal;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[49][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[50][0] = (ULONG)PalScript::Op_GetHSLv;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[51][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[52][0] = (ULONG)PalScript::Op_SwitchRS;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[52][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[53][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[54][0] = (ULONG)PalScript::Op_SetBigMapElement;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[54][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[55][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[56][0] = (ULONG)PalScript::Op_APPR_Entry;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[56][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[57][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[58][0] = (ULONG)PalScript::Op_KF_Entry;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[58][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[59][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[60][0] = (ULONG)PalScript::Op_ENCAMP_Entry;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[60][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[61][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[62][0] = (ULONG)PalScript::Op_SKEE_Entry;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[62][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[63][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[64][0] = (ULONG)PalScript::Op_Get_Appr;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[65][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[66][0] = (ULONG)PalScript::Op_Enable_Sword;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[67][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[68][0] = (ULONG)PalScript::Op_Enable_JusticeBook;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[69][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[70][0] = (ULONG)PalScript::Op_Specify_Compos;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[70][1]) = 3;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[71][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[72][0] = (ULONG)PalScript::Op_Start_Wolf;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[72][1]) = 769;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[73][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[74][0] = (ULONG)PalScript::Op_Start_HideFight;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[74][1]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[74][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[75][1]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[76][0] = (ULONG)PalScript::Op_JT_Exhibit;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[76][1]) = 514;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[77][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[78][0] = (ULONG)PalScript::Op_Movie;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[78][1] = 16843011;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[79][1]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[80][0] = (ULONG)PalScript::Op_SetRoleTexture;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[80][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[81][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[82][0] = (ULONG)PalScript::Op_Rotate;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[82][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[83][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[84][0] = (ULONG)PalScript::Op_Quake;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[84][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[85][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[86][0] = (ULONG)PalScript::Op_ShowChatRest;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[86][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[87][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[88][0] = (ULONG)PalScript::Op_GetHS_ManageType;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[88][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[89][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[90][0] = (ULONG)PalScript::Op_GetHS_Period_type;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[90][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[91][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[92][0] = (ULONG)PalScript::Op_GetHS_Accrual_type;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[92][1]) = 259;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[92][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[93][1]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[94][0] = (ULONG)PalScript::Op_GetHS_UnHock_type;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[94][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[95][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[96][0] = (ULONG)PalScript::Op_Trigger;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[96][1]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[96][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[97][1]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[98][0] = (ULONG)PalScript::Op_SetBigMapElement;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[98][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[99][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[100][0] = (ULONG)PalScript::Op_GetSwitch;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[100][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[101][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[102][0] = (ULONG)PalScript::Op_EntryRow;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[103][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[104][0] = (ULONG)PalScript::Op_RotateInv;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[104][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[105][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[106][0] = (ULONG)PalScript::Op_EntrySkee;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[106][1]) = 259;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[107][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[108][0] = (ULONG)PalScript::Op_Dist;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[109][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[110][0] = (ULONG)PalScript::Op_CombatNotGameOver;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[110][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[111][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[112][0] = (ULONG)PalScript::Op_GetCombat;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[112][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[113][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[114][0] = (ULONG)PalScript::Op_Music;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[114][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[115][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[116][0] = (ULONG)PalScript::Op_StopMusic;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[116][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[117][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[118][0] = (ULONG)PalScript::Op_RoleFadeOut;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[118][1] = 16843010;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[119][1]) = 4;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[120][0] = (ULONG)PalScript::Op_RoleFadeIn;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[120][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[121][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[122][0] = (ULONG)PalScript::Op_IfInTeam;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[122][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[123][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[124][0] = (ULONG)PalScript::Op_Enable_SwordSkill;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[124][1]) = 514;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[124][1]) = 2;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[125][1]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[126][0] = (ULONG)PalScript::Op_FogH;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[126][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[127][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[128][0] = (ULONG)PalScript::Op_Snow;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[128][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[129][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[130][0] = (ULONG)PalScript::Op_ScrEft;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[130][1]) = 257;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[131][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[132][0] = (ULONG)PalScript::Op_CEft_Pos;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[132][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[133][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[134][0] = (ULONG)PalScript::Op_CEft;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[135][1]) = 0;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[147][1]) = 0;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[153][1]) = 0;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[159][1]) = 0;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[136][0] = (ULONG)PalScript::Op_CEft_Role;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[136][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[137][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[138][0] = (ULONG)PalScript::Op_AverageLv;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[138][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[139][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[140][0] = (ULONG)PalScript::Op_EntrySmeltSys;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[140][1]) = 769;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[141][1]) = 2;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[142][0] = (ULONG)PalScript::Op_Switch2Menu;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[142][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[143][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[144][0] = (ULONG)PalScript::Op_CEft_Load;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[144][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[145][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[146][0] = (ULONG)PalScript::Op_GiveCloth;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[148][0] = (ULONG)PalScript::Op_LoadAct;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[148][1]) = 257;
  BYTE2(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[148][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[149][1]) = 3;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[150][0] = (ULONG)PalScript::Op_Rain;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[150][1]) = 2;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[151][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[152][0] = (ULONG)PalScript::Op_WaterMagic;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[154][0] = (ULONG)PalScript::Op_FullTeamAtt;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[154][1]) = 3;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[155][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[156][0] = (ULONG)PalScript::Op_BeeInsertFrame;
  LOBYTE(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[156][1]) = 1;
  LOWORD(((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[157][1]) = 1;
  ((GRPinput *)&stru_D8C2B8)->m_keyDragStartPositions[158][0] = (ULONG)PalScript::Op_CameraYaw;
  return 1;
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
          v2 = pInstance[19];
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
      v5 = *pInstance;
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
    ((PtrArray *)&((GRPinput *)&stru_D8C2B8)->m_keyStates[40])->FindFirst(pInstance);
  }
}

// 0x00434BD0
void * GetSceneObject(unsigned __int16 nObjID)
{
  if ( nObjID == 0xFFFF )
    return g_pRoleSystem;
  if ( nObjID < 0xAu )
    return ((ScriptSystem *)nObjID)->GetMainRoleSystem();
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

  result = (gbCamera *)((PalScript *)v0)->GetString();
  if ( result )
  {
    LOWORD(result) = LOWORD(result->OrthoSize);
    v4 = result;
    v2 = (PalScript *)UISceneUpdate();
    ((PalScript *)v2)->SetAction((int)v4);
    return (gbCamera *)((RoleSystem *)g_pCameraCtrl)->SetInactive(v3);
  }
  return result;
}

// 0x00435380
gbCamera * GetCamera_4()
{
  PalScript *v0; // ecx
  gbCamera *result; // eax

  result = (gbCamera *)((PalScript *)v0)->GetString();
  if ( result )
  {
    result = (gbCamera *)LODWORD(result->OrthoSize);
    *((_DWORD *)&g_pCameraCtrl->m_nextYAW + 1) = result;
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
  unsigned __int8 *v6; // eax

  if ( nSwitchIdx < 52 )
  {
    LoadGameSwitches();
    *((_BYTE *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[264].PressTime + nSwitchIdx) = 1;
    v1 = 0;
    v2 = 0;
    for ( i = 0; i < 32; ++i )
      v1 |= *((unsigned __int8 *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[264].PressTime + i) << i;
    v4 = i;
    v5 = 0;
    v6 = (unsigned __int8 *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[264].PressTime + v4;
    do
    {
      v2 |= *v6++ << v5;
      if ( (int)v6 >= (int)&((GRPinput *)&stru_D8C2B8)->KeyInfo[268] )
        break;
      ++v5;
    }
    while ( v5 < 32 );
    ((PAL3 *)szSubKey)->WriteRegistryValue((DWORD)szValueName, v1);
    ((PAL3 *)szSubKey)->WriteRegistryValue((DWORD)"MOVIE_B", v2);
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

  memset(&((GRPinput *)&stru_D8C2B8)->KeyInfo[264].PressTime, 0, 0x34u);
  *(_DWORD *)Data = 0;
  *(_DWORD *)v7 = 0;
  result = (char *)ReadRegistryString(szSubKey, szValueName, (char *)Data);
  if ( (_BYTE)result )
  {
    result = (char *)ReadRegistryString(szSubKey, "MOVIE_B", (char *)v7);
    if ( (_BYTE)result )
    {
      v1 = *(_DWORD *)Data;
      for ( i = 0; i < 32; ++i )
        *((_BYTE *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[264].PressTime + i) = ((1 << i) & v1) != 0;
      v3 = *(_DWORD *)v7;
      v4 = i;
      v5 = 0;
      result = (char *)&((GRPinput *)&stru_D8C2B8)->KeyInfo[264].PressTime + v4;
      do
      {
        *result++ = ((1 << v5) & v3) != 0;
        if ( (int)result >= (int)&((GRPinput *)&stru_D8C2B8)->KeyInfo[268] )
          break;
        ++v5;
      }
      while ( v5 < 32 );
    }
  }
  return result;
}

// 0x00438530
BOOL sub_438530(_BYTE *_this)
{
  return *(_this + 16) == 0;
}

// 0x0043A690
// Microsoft VisualC 2-14/net runtime
void CheckCurRV()
{
  if ( (g_bStaticInitFlags & 1) == 0 )
    g_bStaticInitFlags |= 1u;
  atexit(todo_401800);
}

// 0x0043A740
void Reset()
{
  unk_D8F624 = 1094713344;
}

// 0x0043EBB0
void GetGridOffset(void *_this, int *pOut, int index)
{
  int v3; // eax
  int v4; // edx

  v3 = *((_DWORD *)_this + 5);
  v4 = *((_DWORD *)_this + 277) * (index - *((_DWORD *)_this + 279));
  *pOut = *((_DWORD *)_this + 4);
  pOut[1] = v3 + v4;
}

// 0x00445F20
BOOL MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
  _DWORD *v6; // ecx
  _DWORD *v7; // edi
  int v8; // esi
  gbRefObject **v9; // ebx

  v7 = v6;
  v8 = 0;
  if ( (int)v6[16] > 0 )
  {
    v9 = (gbRefObject **)v6;
    do
    {
      ((gbRefObject *)*v9)->Release();
      ++v8;
      ++v9;
    }
    while ( v8 < v7[16] );
  }
  memset(v7, 0, 0x44u);
  return 0;
}

// 0x0044A7D0
void * sdtor_14(void *Block, char a2)
{
  ((UIWnd *)Block)->RenderText();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0044BD80
void SafeDeletePtr(void **pptr)
{
  void **v1; // ecx
  void **v2; // esi

  v2 = v1;
  if ( *v1 )
  {
    operator delete(*v1);
    *v2 = 0;
  }
}

// 0x0044F8D0
CCBUI * init_44f8d0(int _this, int a2)
{
  UILoadingFrm *v3; // eax
  int *v4; // esi
  CCBUI *result; // eax
  UISceneMap *v6; // eax
  UIGameOver *v7; // esi
  UIScenePanel *v8; // eax
  int *m_pUtil; // esi
  UISceneFrm *v10; // eax
  UITitle_ArcSave *v11; // eax
  CScreenMode *v12; // esi
  CUtil *v13; // eax
  CUtil *v14; // eax
  CUtil *v15; // esi
  UIListBox *v16; // eax
  SoundContext *v17; // esi
  UIRoleSelectDialog *v18; // eax
  CCBStageScene *v19; // eax
  CCBStageScene *inited; // esi
  SceneMgr *v21; // eax
  int *CurrentNode; // esi
  void *v23; // ecx
  ArcPastScene *v24; // eax
  UICursor *v25; // eax
  int v26; // ecx
  CCBUIPanel *v27; // eax
  double v28; // [esp+0x4] [ebp-0x14]

  switch ( a2 )
  {
    case 0:
      return *(CCBUI **)(_this + 28176);
    case 2:
      v10 = (UISceneFrm *)operator new(0xCD8u);
      if ( v10 )
        m_pUtil = (int *)((UISceneFrm *)v10)->ctor();
      else
        m_pUtil = 0;
      ((CScreenMode *)m_pUtil)->InitGameUI();
      ((UITitle_YXXX *)m_pUtil)->LayoutWidgets();
      ((CCBUI *)m_pUtil)->ForwardToPlayerMgr(&p_WORD);
      sub_459FA0((int)m_pUtil, (unsigned __int8)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather);
      sub_45A020((int)m_pUtil, BYTE1(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather));
      sub_45A0A0((int)m_pUtil, BYTE2(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather));
      sub_45A1A0((int)m_pUtil, (unsigned __int8)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_pData);
      sub_45A120((int)m_pUtil, HIBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather));
      goto LABEL_60;
    case 3:
      v11 = (UITitle_ArcSave *)operator new(0xFA4u);
      if ( v11 )
        v12 = (CScreenMode *)((UITitle_ArcSave *)v11)->ctor();
      else
        v12 = 0;
      ((CScreenMode *)v12)->InitEquipScreen();
      ((PAL3 *)v12)->DispatchModeCommand(0);
      return (CCBUI *)v12;
    case 4:
      v8 = (UIScenePanel *)operator new(0x379Cu);
      if ( v8 )
        m_pUtil = (int *)((UIScenePanel *)v8)->ctor_BA60();
      else
        m_pUtil = 0;
      ((UIScenePanel *)m_pUtil)->CreateSettingsUI();
      goto LABEL_12;
    case 5:
      ((MainEquipUI *)*(MainEquipUI **)(_this + 28180))->HandleDeviceLostB();
      ((MainEquipUI *)*(MainEquipUI **)(_this + 28180))->HandleMessage();
      return *(CCBUI **)(_this + 28180);
    case 6:
      return g_pCBSystem->m_pUI;
    case 7:
      v13 = (CUtil *)operator new(0x6ECu);
      if ( v13 )
      {
        v15 = v14;
      }
      else
      {
        v15 = 0;
      }
      ((CUtil *)v15)->InitGameSystems();
      sub_523CD0((unsigned __int8)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather);
      sub_523D20(BYTE1(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather));
      sub_523D70(BYTE2(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather));
      sub_523E10((unsigned __int8)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_childs.m_pData);
      sub_523DC0(HIBYTE(((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_pfather));
      ((CUtil *)v15)->DispatchCommand((int *)pCmd);
      ((CUtil *)v15)->Update(0.0);
      return (CCBUI *)v15;
    case 8:
      v16 = (UIListBox *)operator new(0x6E0u);
      if ( v16 )
        v17 = (SoundContext *)((UIListBox *)v16)->ctor();
      else
        v17 = 0;
      ((SoundContext *)v17)->CreateSubPanels(*(_DWORD *)(_this + 14536));
      ((CScreenMode *)v17)->InitSceneAudio(0);
      return (CCBUI *)v17;
    case 9:
      v18 = (UIRoleSelectDialog *)operator new(0x89Cu);
      if ( v18 )
      {
        m_pUtil = (int *)((UIRoleSelectDialog *)v18)->ctor_95F0();
        ((UIEmote *)m_pUtil)->Render();
      }
      else
      {
        m_pUtil = 0;
        UIEmote::Render();
      }
LABEL_12:
      if ( !m_pUtil )
        goto LABEL_62;
      (*(void ( **)(int *, int, int, _DWORD))(*m_pUtil + 24))(m_pUtil, 1000, 1, 0);
      result = (CCBUI *)m_pUtil;
      break;
    case 10:
      v19 = (CCBStageScene *)operator new(0x414u);
      if ( v19 )
        inited = (CCBStageScene *)((CCBStageScene *)v19)->InitCameraPositions();
      else
        inited = 0;
      ((CCBStageScene *)inited)->CreateCamera();
      g_pMiniGame1 = inited;
      m_pUtil = (int *)inited->m_pUtil;
      goto LABEL_60;
    case 11:
      v21 = (SceneMgr *)operator new(0x130u);
      if ( v21 )
        CurrentNode = ((SceneMgr *)v21)->GetCurrentNode();
      else
        CurrentNode = 0;
      ((CCBFiveNimbusWindow *)CurrentNode)->fn_52F300(*(_DWORD *)(_this + 14536));
      ((CScreenMode *)CurrentNode)->InitEndScreen();
      g_pMiniGame2 = CurrentNode;
      return (CCBUI *)CurrentNode[2];
    case 12:
      v23 = g_pMiniGame3;
      if ( g_pMiniGame3 )
      {
        if ( !g_nMiniGameState && LODWORD(thisa) == g_nMiniGameParam && *(_DWORD *)(_this + 14536) != 5 )
        {
          ((ArcLocaleRole *)g_pMiniGame3)->GetScreenLeft(v28);
          v23 = g_pMiniGame3;
        }
        return (CCBUI *)*((_DWORD *)v23 + 5);
      }
      else
      {
        v24 = (ArcPastScene *)operator new(0x40u);
        if ( v24 )
          v25 = (UICursor *)((ArcPastScene *)v24)->ResetCityName();
        else
          v25 = 0;
        g_pMiniGame3 = v25;
        ((UICursor *)v25)->Update(v28);
        g_bSceneLoaded_0 = 0;
        v26 = *((_DWORD *)g_pMiniGame3 + 5);
        if ( v26 )
          (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v26 + 24))(v26, 1000, 1, 0);
        return (CCBUI *)*((_DWORD *)g_pMiniGame3 + 5);
      }
    case 13:
      v27 = (CCBUIPanel *)operator new(0x5660u);
      if ( v27 )
        m_pUtil = ((CCBUIPanel *)v27)->ctor_60D0();
      else
        m_pUtil = 0;
      ((CCBUIPanel *)m_pUtil)->InitPanel();
LABEL_60:
      if ( m_pUtil )
        (*(void ( **)(int *, int, int, _DWORD))(*m_pUtil + 24))(m_pUtil, 1000, 1, 0);
LABEL_62:
      result = (CCBUI *)m_pUtil;
      break;
    case 14:
      v3 = (UILoadingFrm *)operator new(0x14Cu);
      if ( v3 )
      {
        v4 = ((UILoadingFrm *)v3)->ctor();
        ((UILoadingFrm *)v4)->InitFullScreen();
        result = (CCBUI *)v4;
      }
      else
      {
        UILoadingFrm::InitFullScreen();
        result = 0;
      }
      break;
    case 15:
      v6 = (UISceneMap *)operator new(0xE8u);
      if ( v6 )
      {
        v7 = (UIGameOver *)((UISceneMap *)v6)->ctor();
        ((UIGameOver *)v7)->Create();
        result = (CCBUI *)v7;
      }
      else
      {
        UIGameOver::Create();
        result = 0;
      }
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// 0x00450370
void * sdtor_15(void *Block, char a2)
{
  ((UIWnd *)Block)->DelegateRender();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x00450A25
void RoleCameraCtrl()
{
  accessor_00450A30();
}

// 0x00451730
int todo_451730(UIWnd *_this)
{
  return *((_DWORD *)_this + 276);
}

// 0x004518FE
void SetPitch(float a1)
{
  JUMPOUT(0x451900);
}

// 0x00452540
// attributes: thunk
int GetVertexNum()
{
  return accessor_00452550();
}

// 0x00452560
// attributes: thunk
gbVec3D *GetVertexBuf()
{
  return UITitle_BBTY::_nearby_452570();
}

// 0x004531F0
void sub_4531F0(_BYTE *_this)
{
  *(_this + 100) = 1;
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
  LOBYTE(result) = 0;
  return result;
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

// 0x00459F80
int sub_459F80(_BYTE *_this)
{
  int result; // eax
  int i; // edx

  result = 0;
  for ( i = 0; i < 4; ++i )
  {
    if ( *(_this + i + 153) )
      ++result;
  }
  return result;
}

// 0x004A13E0
int sub_4A13E0()
{
  int result; // eax

  g_nUILayoutFlags = 0;
  return result;
}

// 0x004A1A7C
scGlobalUserVar *GetGlobalUserVar(char *a1)
{
  JUMPOUT(0x4A1A80);
}

// 0x004A36B0
LPSTR FormatChineseNumber(int nVal, LPSTR lpBuf)
{
  LPSTR result; // eax

  if ( nVal / 10 <= 0 )
    return lstrcpyA(lpBuf, (LPCSTR)&dword_DCA33C[64 * nVal]);
  lstrcpyA(lpBuf, (LPCSTR)&dword_DCA33C[64 * (nVal / 10)]);
  result = lstrcatA(lpBuf, byte_DCAD3C);
  if ( nVal % 10 > 0 )
    return lstrcatA(lpBuf, (LPCSTR)&dword_DCA33C[64 * (nVal % 10)]);
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
    v4 = operator new(16 * v3);
    *(_DWORD *)(pDst + 12) = v4;
    v5 = *(_DWORD **)(pSrc + 16);
    v6 = v4;
    for ( i = *(_DWORD **)(pSrc + 12); i != v5; v6 += 4 )
    {
      if ( v6 )
      {
        *v6 = *i;
        v6[1] = i[1];
        v6[2] = i[2];
        v6[3] = i[3];
      }
      i += 4;
    }
    *(_DWORD *)(pDst + 16) = v6;
    *(_DWORD *)(pDst + 20) = v6;
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

  result = p_DWORD2;
  v4 = p_DWORD;
  if ( p_DWORD != p_DWORD2 )
  {
    v5 = p_DWORD + 3;
    if ( p_DWORD + 3 != p_DWORD2 )
    {
      while ( 1 )
      {
        v23 = *v5;
        v6 = v5[1];
        v7 = v5[2];
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
          v11 = v5 + 2;
          v21 = *v5;
          v12 = v5;
          v13 = v5[1];
          v22 = v13;
          v14 = v5[2];
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
              v4 = p_DWORD;
              goto LABEL_25;
            }
            *v12 = *(v11 - 2);
            v12[1] = *(v11 - 1);
            v12[2] = *v11;
            v13 = v22;
            v12 = v11 - 2;
          }
          v19 = *(_DWORD *)(v14 + 608);
          v18 = __OFSUB__(v19, *(_DWORD *)(*v11 + 608));
          v17 = v19 - *(_DWORD *)(*v11 + 608) < 0;
          goto LABEL_18;
        }
        v20 = v5;
        if ( v4 != v5 )
        {
          do
          {
            v20 -= 3;
            v20[3] = *v20;
            v20[4] = v20[1];
            v20[5] = v20[2];
            v4 = p_DWORD;
          }
          while ( v20 != p_DWORD );
        }
        *v4 = v23;
        v4[1] = v6;
        v4[2] = v7;
LABEL_25:
        result = p_DWORD2;
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

// 0x004B6CA0
void nearby_4b6ca0(void **_this)
{
  ;
}

// 0x004BE460
int RenderPost(int _this, int nVal)
{
  int result; // eax

  result = *(_DWORD *)(_this + 148);
  if ( result )
    return (*(int ( **)(_DWORD, int))(***(_DWORD ***)(_this + 116) + 20))(**(_DWORD **)(_this + 116), nVal);
  return result;
}

// 0x004C5B90
int operator_(_DWORD *_this, int a2, char a3)
{
  int result; // eax

  result = sub_4C5940(a2);
  *(_BYTE *)(*(_this + result + 70) + 13) = a3;
  return result;
}

// 0x004C5BB0
int CombatEffectUpdate(int _this, double pData)
{
  int v3; // edi
  double v4; // st7
  int result; // eax
  double v6; // st7
  _DWORD *v7; // ebx

  v3 = 0;
  v4 = *(float *)(_this + 332) * pData;
  result = *(_DWORD *)(_this + 276);
  *(double *)(_this + 312) = v4;
  v6 = v4 + *(double *)(_this + 320);
  *(double *)(_this + 320) = v6;
  *(float *)(_this + 328) = v6;
  if ( result > 0 )
  {
    v7 = (_DWORD *)(_this + 280);
    do
    {
      (*(void ( **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)*v7 + 20))(
        *v7,
        *(_DWORD *)(_this + 312),
        *(_DWORD *)(_this + 316));
      result = *(_DWORD *)(_this + 276);
      ++v3;
      ++v7;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x004C6831
void SetRadiusWidth(int a1)
{
  JUMPOUT(0x4C6840);
}

// 0x004CB350
char * sdtor_36(char *_this, char a2)
{
  char *v2; // esi

  v2 = _this - 12;
  ((CEffGrid *)(_this - 12))->_CEffGrid();
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004CDA00
char * sdtor_37(char *_this, char a2)
{
  char *v2; // esi

  v2 = _this - 12;
  ((CEffMeteor *)(_this - 12))->_CEffMeteor();
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004CDB70
char SceneMgrUpdate(float *_this, float fVal)
{
  double v2; // st7
  float *v3; // esi
  int v4; // edi
  int v5; // eax

  v2 = fVal - *(_this + 10824);
  *(_this + 10824) = fVal;
  v3 = _this + 587;
  *(_this + 10825) = v2;
  v4 = 2048;
  *(_this + 10826) = *(_this + 10826) + *(_this + 10825);
  do
  {
    LOBYTE(v5) = *((_BYTE *)v3 - 4);
    if ( (_BYTE)v5 )
    {
      if ( !*((_BYTE *)v3 - 3) )
        (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)v3 + 20))(*(_DWORD *)v3, LODWORD(fVal));
      LOBYTE(v5) = *((_BYTE *)v3 - 4);
      if ( (_BYTE)v5 )
      {
        v5 = *(_DWORD *)v3;
        if ( *(_BYTE *)(*(_DWORD *)v3 + 8) )
          *((_BYTE *)v3 - 3) = 1;
      }
    }
    v3 += 5;
    --v4;
  }
  while ( v4 );
  return v5;
}

// 0x004D0CA0
char * sdtor_38(char *_this, char a2)
{
  char *v2; // esi

  v2 = _this - 12;
  ((CEffgbParticle *)(_this - 12))->_nearby_4cfd40();
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004D3230
char * sdtor_39(char *_this, char a2)
{
  char *v2; // esi

  v2 = _this - 12;
  ((CEffect *)(_this - 12))->UpdateCallback();
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004D4DF0
char * sdtor_40(char *_this, char a2)
{
  char *v2; // esi

  v2 = _this - 12;
  ((CEffect *)(_this - 12))->DestroyCallback();
  if ( (a2 & 1) != 0 )
    operator delete(v2);
  return v2;
}

// 0x004D589C
void SetRect_0(tagRECT *a1)
{
  JUMPOUT(0x4D58A0);
}

// 0x004D5950
void BringWindowToTop()
{
  int v0; // ebx
  char *v1; // esi
  int v2; // eax
  char *Buffer; // [esp+0x10] [ebp+0x4]
  const char *v4; // [esp+0x14] [ebp+0x8]

  if ( Buffer != v4 )
    strcpy(Buffer, v4);
  v0 = 0;
  v1 = Buffer;
  if ( strlen(Buffer) )
  {
    while ( *v1 < 48 || *v1 > 57 )
    {
      ++v1;
      if ( ++v0 >= strlen(Buffer) )
        goto LABEL_7;
    }
    v2 = atoi(v1);
    sprintf(v1, &dir[20], v2 + 1);
  }
  else
  {
LABEL_7:
    strcat(Buffer, (const char *)&pTarget.m_nTargetType + 224);
  }
}

// 0x004E0A30
int DialogFunc(HWND hDlg, UINT uMsg, WPARAM a3, LPARAM lParam)
{
  return ((CCBUI *)g_RoleSystemCombat.m_teamSlots[263])->DlgProcEditorMain(hDlg, uMsg, a3, lParam);
}

// 0x004E5300
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly)
{
  if ( bReadOnly )
    return SendMessageA(hWnd, 0xF1u, 1u, 0);
  else
    return SendMessageA(hWnd, 0xF1u, 0, 0);
}

// 0x004E5330
BOOL EditBox_IsModified(HWND hWnd)
{
  BOOL result; // eax

  result = SendMessageA(hWnd, 0xF0u, 0, 0);
  LOBYTE(result) = result;
  return result;
}

// 0x004E5350
LRESULT EditBox_SetFloat(HWND hWnd, float fValue)
{
  sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%1.5f", fValue);
  return SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
}

// 0x004E5390
LRESULT EditBox_SetInt(HWND hWnd, int nValue)
{
  sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], nValue);
  return SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
}

// 0x004E5410
char * GetEditBoxText(HWND hWnd)
{
  SendMessageA(hWnd, 0xDu, 0xFAu, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  return (char *)&g_RoleSystemCombat.m_teamSlots[264];
}

// 0x004E5430
double EditBox_GetFloat(HWND hWnd)
{
  SendMessageA(hWnd, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  return atof((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
}

// 0x004E5460
int EditBox_GetInt(HWND hWnd)
{
  SendMessageA(hWnd, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  return atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
}

// 0x004EA590
BOOL CCBStageCam_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return ((CCBUI *)g_RoleSystemCombat.m_teamSlots[263])->DlgProcCameraEdit(hDlg, uMsg, wParam, lParam);
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

// 0x005269B0
void CreateDigitPair(int nVal, UIWnd **ppTens, UIWnd **ppOnes, const char *pszTexBase, char bFlag)
{
  char Buffer[256]; // [esp+0x10] [ebp-0x100] BYREF

  sprintf(Buffer, "%s%d.tga", pszTexBase, nVal / 10);
  ((UIStatic *)ppTens)->CreateFromTemplate();
  sprintf(Buffer, "%s%d.tga", pszTexBase, nVal % 10);
  ((UIStatic *)ppOnes)->CreateFromTemplate();
}

// 0x0052B900
int MiniGame1Update(int ***_this, double pData)
{
  int ***v3; // esi
  int v4; // ebx
  float fVal; // [esp+0x0] [ebp-0x4]

  fVal = pData;
  v3 = _this + 6;
  v4 = 5;
  do
  {
    ((Object3D *)(v3 - 2))->CaculateRelative(fVal);
    if ( ((Object3D *)*v3)->GetVisNode() == (gbVisNode *)1 )
      ((Actor *)*v3)->CompareActionName((int)v3[35], 0);
    v3 += 38;
    --v4;
  }
  while ( v4 );
  ((Object3D *)(_this + 214))->CaculateRelative(fVal);
  ((ObjectCamera *)*(_this + 3))->SetStepRotate();
  return ((UINote *)*_this)->CallVtableMethod(pData);
}

// 0x0052F350
void MiniGame2Update(int **_this, int nVal)
{
  int v3; // ecx
  ScreenEffectMgr *v4; // ecx
  CScreenMode *v5; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v7; // esi
  CScreenMode *v8; // eax
  CScreenMode *v9; // eax
  ScreenEffect *Instance; // eax
  double v11; // st7
  char v12; // al
  int *v13; // ecx
  int *v14; // edx
  unsigned int v15; // ecx
  float *v16; // eax
  unsigned int v17; // edx
  double v18; // st7
  double v19; // st6
  float nVala; // [esp+0x14] [ebp+0x4]

  ((PalScriptMgr *)_this)->RunSceneScript((const char *)nVal);
  if ( *((_BYTE *)_this + 24) )
  {
    v3 = (int)*(_this + 5);
    if ( v3 && !(*(int ( **)(int))(*(_DWORD *)v3 + 4))(v3) )
    {
      ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_S_GAME")->WriteRegistryDwordEx((DWORD)"S_GAME_C", 1);
      ((CGameData *)&g_gamefrm)->Load((CUtil *)*(_this + 75));
      if ( *(_this + 75) )
      {
        Instance = ((ScreenEffectMgr *)v4)->GetInstance();
        ((ScreenEffectMgr *)Instance)->ProcessEffect();
      }
      else
      {
        ((PalScriptMgr *)dword_DBA254)->Destroy();
        if ( (g_dwGameFlags & 4) != 0 )
        {
          v5 = CScreenMode::GetInstance();
          AudioManager = (gbAudioManager *)((CScreenMode *)v5)->GetAudioManager();
          v7 = AudioManager;
          if ( AudioManager )
          {
            ((gbAudioManager *)AudioManager)->StopSoundStream(1);
            ((gbAudioManager *)v7)->StopSoundStream(2);
          }
          if ( CScreenMode::GetInstance()->m_bRenderAlt )
          {
            v8 = CScreenMode::GetInstance();
            ((CScreenMode *)v8)->AudioFadeOut();
          }
          else
          {
            v9 = CScreenMode::GetInstance();
            ((CScreenMode *)v9)->AudioStopAll();
          }
        }
      }
    }
  }
  else
  {
    if ( *((_BYTE *)_this + 293) )
    {
      v11 = *(float *)&nVal;
    }
    else
    {
      if ( *((_BYTE *)_this + 292) )
        *((_BYTE *)_this + 292) = 0;
      (*(_this + 69))[(_DWORD)*(_this + 71)] = nVal;
      v12 = *((_BYTE *)_this + 294);
      v13 = (int *)((char *)*(_this + 71) + 1);
      *(_this + 71) = v13;
      v14 = v13;
      if ( !v12 )
        *((_BYTE *)_this + 294) = v13 >= *(_this + 68);
      v15 = (unsigned int)*(_this + 68);
      *(_this + 70) = 0;
      *(_this + 71) = (unsigned int)v14 < v15 ? v14 : 0;
      if ( v15 )
      {
        v16 = (float *)*(_this + 69);
        v17 = v15;
        do
        {
          v18 = *v16++ + *((float *)_this + 70);
          --v17;
          *((float *)_this + 70) = v18;
        }
        while ( v17 );
      }
      v11 = *((float *)_this + 70) / (double)v15;
    }
    if ( *((_BYTE *)_this + 296) )
    {
      nVala = flt_5F4B9C * v11;
    }
    else if ( *((_BYTE *)_this + 294) )
    {
      v19 = flt_5F4B9C * v11;
      *((_BYTE *)_this + 296) = 1;
      nVala = v19;
    }
    else
    {
      nVala = 1.0;
    }
    ((CameraCtrl *)*(_this + 1))->SetViewport(SLODWORD(nVala));
    ((Actor *)*_this)->UpdateFrame(nVala);
    ((ArcLocaleRole *)*(_this + 3))->DispatchActive(SLODWORD(nVala));
    ((MiniGame2Scene *)*(_this + 4))->UpdateMiniGame2(nVala);
  }
}

// 0x00532CF0
long double CalcAngleBetweenVectors(int nX1, int nY1, int nZ1, int nX2, float fY2, float fZ2)
{
  ((gbVec3D *)&nX1)->Normalize();
  ((gbVec3D *)&nX2)->Normalize();
  return acos(fZ2 * *(float *)&nZ1 + fY2 * *(float *)&nY1 + *(float *)&nX2 * *(float *)&nX1) * 57.295776;
}

// 0x005353A0
void MiniGame3Update(int *_this, float fVal)
{
  DWORD TickCount; // eax
  DWORD v4; // eax
  unsigned int v5; // edx
  char v6; // al
  unsigned int v7; // ecx
  unsigned int v8; // edx
  unsigned int v9; // ecx
  float *v10; // eax
  unsigned int v11; // edx
  double v12; // st7
  gbVec3D v13; // [esp-0x10] [ebp-0x2C]
  double fDelta; // [esp+0x0] [ebp-0x1C]
  float v15; // [esp+0x8] [ebp-0x14]

  ((ArcSceneObject *)*(_this + 3))->UpdateOscillation(*(float *)(*_this + 192));
  ((RoleAtt *)*(_this + 3))->SetPositionFromInts(*(_DWORD *)(*_this + 168), *(_DWORD *)(*_this + 172), *(_DWORD *)(*_this + 176));
  v13.x = 0.0;
  *(_QWORD *)&v13.y = 0xBF80000000000000uLL;
  ((RoleAtt *)*(_this + 3))->UpdateDirectionalMotion(v13, 260.0, 168.0);
  if ( *(_BYTE *)(*_this + 216) )
    *((_BYTE *)_this + 36) = 1;
  else
    *((_BYTE *)_this + 37) = 1;
  if ( *((_BYTE *)_this + 36) && *((_BYTE *)_this + 37) )
  {
    ((RoleAtt *)*(_this + 3))->SetFightState(1086324736, 1086324736, 1086324736, 1091567616, 1070386381, 1, 0);
    if ( !*((_BYTE *)_this + 32) )
    {
      TickCount = GetTickCount();
      *(_this + 6) = TickCount;
      *(_this + 7) = TickCount;
      *((_BYTE *)_this + 32) = 1;
    }
    v4 = GetTickCount();
    v5 = v4 - *(_this + 7);
    *(_this + 6) = v4;
    if ( v5 > 0x3E8 )
    {
      *(_this + 7) = v4;
      *((_BYTE *)_this + 32) = 0;
      ((RoleAtt *)*(_this + 3))->ResetFightState();
      *((_BYTE *)_this + 36) = 0;
      *((_BYTE *)_this + 37) = 0;
    }
  }
  if ( !*((_BYTE *)_this + 61) )
  {
    if ( *((_BYTE *)_this + 60) )
      *((_BYTE *)_this + 60) = 0;
    *(float *)(*(_this + 11) + 4 * *(_this + 13)) = fVal;
    v6 = *((_BYTE *)_this + 62);
    v7 = *(_this + 13) + 1;
    *(_this + 13) = v7;
    v8 = v7;
    if ( !v6 )
      *((_BYTE *)_this + 62) = v7 >= *(_this + 10);
    v9 = *(_this + 10);
    *(_this + 13) = v8 < v9 ? v8 : 0;
    *(_this + 12) = 0;
    if ( v9 )
    {
      v10 = (float *)*(_this + 11);
      v11 = v9;
      do
      {
        v12 = *((float *)_this + 12) + *v10++;
        --v11;
        *((float *)_this + 12) = v12;
      }
      while ( v11 );
    }
    fVal = *((float *)_this + 12) / (double)v9;
  }
  if ( *((_BYTE *)_this + 62) )
  {
    *(float *)&fDelta = fVal;
    ((CScreenMode *)*(_this + 4))->LoadScreenScene(fDelta, v15);
    ((ExternalStatistics *)*(_this + 2))->UpdateFromRole(COERCE_UNSIGNED_INT64(fVal), HIDWORD(COERCE_UNSIGNED_INT64(fVal)));
    ((Actor *)*_this)->SetParam(COERCE_UNSIGNED_INT64(fVal));
    nearby_5359B0(fVal);
    ((RoleCamera *)*(_this + 3))->UpdateAudioListener(COERCE_UNSIGNED_INT64(fVal), HIDWORD(COERCE_UNSIGNED_INT64(fVal)));
  }
}

// 0x005374E0
gbVec3D * Vec3D_CopyStruct(gbVec3D *pDst, gbVec3D *pSrc, gbVec3D *pExtra)
{
  gbVec3D *v3; // ecx
  gbVec3D *result; // eax

  v3 = pDst;
  if ( pDst == pSrc )
    return pExtra;
  result = pExtra;
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

// 0x00538260
CHAR * sub_538260(CHAR *_this)
{
  *(_DWORD *)_this = 0;
  lstrcpyA(_this + 4, g_szSceneUIText);
  lstrcpyA(_this + 36, g_szSceneUIText);
  lstrcpyA(_this + 66, g_szSceneUIText);
  lstrcpyA(_this + 96, g_szSceneUIText);
  *(_this + 612) = 0;
  memset(_this + 644, 0, 0x18u);
  *(_this + 800) = 0;
  *(_this + 801) = 0;
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

// 0x005394F0
void * GetSaveDataManager()
{
  if ( (g_ActorSaveData.m_nRoleParam0 & 1) == 0 )
  {
    LOBYTE(g_ActorSaveData.m_nRoleParam0) |= 1u;
    ((Actor *)&g_ActorSaveData)->ClearArrayEntry();
    atexit(unknown_libname_507);
  }
  return &g_ActorSaveData;
}

// 0x0053A340
void ActVec_Insert_char(Actor *_this, char *pszBuf, unsigned int dwVal, char *pszBuf2)
{
  char *v4; // ebx
  int v6; // esi
  unsigned int v7; // ecx
  int v8; // edx
  unsigned int v9; // eax
  Actor *v10; // esi
  char *v11; // edx
  char *j; // eax
  char *v13; // eax
  unsigned int v14; // ebx
  char *v15; // edi
  char *v16; // ebx
  char *v17; // eax
  int v18; // eax
  int v19; // edx
  Actor *v20; // edi
  unsigned int v21; // esi
  char *v22; // eax
  char *v23; // edx
  char *v24; // eax
  unsigned int i; // edx
  Actor *v26; // ebx
  Actor *v27; // esi
  unsigned int v28; // ebp
  char *v29; // esi
  Actor *v30; // ebx
  int v31; // esi
  Actor *v32; // esi
  Actor *v33; // [esp+0x10] [ebp-0x8]
  char *v34; // [esp+0x14] [ebp-0x4]
  char *pszBufa; // [esp+0x1C] [ebp+0x4]
  unsigned int dwVala; // [esp+0x20] [ebp+0x8]
  unsigned int dwValb; // [esp+0x20] [ebp+0x8]
  char *pszBuf2a; // [esp+0x24] [ebp+0xC]

  v4 = *(char **)&_this->m_actarray[8];
  v33 = _this;
  if ( (*(_DWORD *)&_this->m_actarray[12] - (int)v4) / 656 >= dwVal )
  {
    v20 = (Actor *)pszBuf;
    if ( (v4 - pszBuf) / 656 >= dwVal )
    {
      if ( dwVal )
      {
        pszBufa = *(char **)&_this->m_actarray[8];
        v28 = 656 * dwVal;
        v29 = &v4[-656 * dwVal];
        if ( v29 != v4 )
        {
          do
          {
            Actor_CopyConstruct_290(pszBufa, v29);
            v29 += 656;
            pszBufa += 656;
          }
          while ( v29 != v4 );
          _this = v33;
        }
        v30 = *(Actor **)&_this->m_actarray[8];
        v31 = (int)&v30->m_actarray[-v28];
        if ( v20 != (Actor *)((char *)v30 - v28) )
        {
          do
          {
            v31 -= 656;
            v30 = (Actor *)((char *)v30 - 656);
            ((Actor *)v30)->SetCurrentAction(v31);
          }
          while ( (Actor *)v31 != v20 );
          _this = v33;
        }
        v32 = (Actor *)((char *)v20 + v28);
        if ( v20 != (Actor *)&v20->m_actarray[v28] )
        {
          do
          {
            ((Actor *)v20)->SetCurrentAction((int)pszBuf2);
            v20 = (Actor *)((char *)v20 + 656);
          }
          while ( v20 != v32 );
          _this = v33;
        }
        *(_DWORD *)&_this->m_actarray[8] += v28;
      }
    }
    else
    {
      v21 = 656 * dwVal;
      dwValb = 656 * dwVal;
      v22 = &pszBuf[656 * dwVal];
      if ( pszBuf != v4 )
      {
        v23 = &v22[-v21];
        do
        {
          if ( v22 )
          {
            qmemcpy(v22, v23, 0x290u);
            v20 = (Actor *)pszBuf;
            _this = v33;
          }
          v23 += 656;
          v22 += 656;
        }
        while ( v23 != v4 );
      }
      v24 = *(char **)&_this->m_actarray[8];
      for ( i = dwVal - (v24 - (char *)v20) / 656; i; --i )
      {
        if ( v24 )
        {
          qmemcpy(v24, pszBuf2, 0x290u);
          v20 = (Actor *)pszBuf;
          _this = v33;
        }
        v24 += 656;
      }
      v26 = *(Actor **)&_this->m_actarray[8];
      v27 = v20;
      if ( v20 != v26 )
      {
        do
        {
          ((Actor *)v27)->ActionEntry_Assign((int)pszBuf2);
          ((Actor *)&v27->m_curact[35])->CopyActionData((int)(pszBuf2 + 620));
          v27 = (Actor *)((char *)v27 + 656);
        }
        while ( v27 != v26 );
        _this = v33;
      }
      *(_DWORD *)&_this->m_actarray[8] += dwValb;
    }
  }
  else
  {
    v6 = *(_DWORD *)&_this->m_actarray[4];
    if ( !v6 || (v7 = (int)&v4[-v6] / 656, dwVal >= v7) )
      v7 = dwVal;
    if ( v6 )
      v8 = (int)&v4[-v6] / 656;
    else
      v8 = 0;
    v9 = v8 + v7;
    dwVala = v8 + v7;
    if ( (int)(v8 + v7) < 0 )
      v9 = 0;
    v10 = v33;
    v34 = (char *)operator new(656 * v9);
    v11 = v34;
    for ( j = *(char **)&v33->m_actarray[4]; j != pszBuf; v11 += 656 )
    {
      if ( v11 )
      {
        qmemcpy(v11, j, 0x290u);
        v10 = v33;
      }
      j += 656;
    }
    v13 = v11;
    if ( dwVal )
    {
      v14 = dwVal;
      do
      {
        if ( v13 )
        {
          qmemcpy(v13, pszBuf2, 0x290u);
          v10 = v33;
        }
        v13 += 656;
        --v14;
      }
      while ( v14 );
    }
    v15 = *(char **)&v10->m_actarray[8];
    pszBuf2a = v15;
    v16 = &v11[656 * dwVal];
    if ( pszBuf != v15 )
    {
      v17 = pszBuf;
      do
      {
        if ( v16 )
        {
          qmemcpy(v16, v17, 0x290u);
          v10 = v33;
          v15 = pszBuf2a;
        }
        v17 += 656;
        v16 += 656;
      }
      while ( v17 != v15 );
    }
    operator delete(*(void **)&v10->m_actarray[4]);
    v18 = *(_DWORD *)&v10->m_actarray[4];
    *(_DWORD *)&v10->m_actarray[12] = &v34[656 * dwVala];
    if ( v18 )
      v19 = (*(_DWORD *)&v10->m_actarray[8] - v18) / 656;
    else
      v19 = 0;
    *(_DWORD *)&v10->m_actarray[4] = v34;
    *(_DWORD *)&v10->m_actarray[8] = &v34[656 * v19 + 656 * dwVal];
  }
}

// 0x0053A6C0
_WORD * ActVec_Insert_word(Actor *_this, _WORD *p_WORD, unsigned int dwVal, _WORD *p_WORD2)
{
  Actor *v5; // edi
  _WORD *result; // eax
  int v7; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  _WORD *v11; // ecx
  _WORD *n; // eax
  _WORD *v13; // eax
  unsigned int v14; // edx
  _WORD *v15; // edi
  _WORD *v16; // edx
  _WORD *v17; // eax
  int v18; // ecx
  int v19; // eax
  unsigned int v20; // ebx
  _WORD *v21; // esi
  _WORD *v22; // ecx
  _WORD *v23; // eax
  unsigned int k; // ebp
  _WORD *v25; // ecx
  _WORD *m; // eax
  unsigned int v27; // ebp
  _WORD *v28; // ecx
  _WORD *i; // esi
  _WORD *v30; // ecx
  _WORD *j; // eax
  __int16 v32; // si
  int v34; // [esp+0x14] [ebp-0x4]
  _WORD *dwVala; // [esp+0x20] [ebp+0x8]

  v5 = _this;
  result = *(_WORD **)&_this->m_actarray[8];
  if ( (*(_DWORD *)&_this->m_actarray[12] - (int)result) >> 1 >= dwVal )
  {
    if ( result - p_WORD >= dwVal )
    {
      if ( dwVal )
      {
        v27 = 2 * dwVal;
        v28 = &result[-dwVal];
        for ( i = result; v28 != result; ++i )
        {
          if ( i )
            *i = *v28;
          ++v28;
        }
        v30 = *(_WORD **)&v5->m_actarray[8];
        for ( j = &v30[v27 / 0xFFFFFFFE]; j != p_WORD; *v30 = v32 )
        {
          v32 = *--j;
          --v30;
        }
        for ( result = p_WORD; result != &p_WORD[v27 / 2]; ++result )
          *result = *p_WORD2;
        *(_DWORD *)&v5->m_actarray[8] += v27;
      }
    }
    else
    {
      v20 = 2 * dwVal;
      v21 = &p_WORD[dwVal];
      if ( p_WORD != result )
      {
        v22 = &v21[v20 / 0xFFFFFFFE];
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
      v23 = *(_WORD **)&v5->m_actarray[8];
      for ( k = dwVal - (v23 - p_WORD); k; --k )
      {
        if ( v23 )
          *v23 = *p_WORD2;
        ++v23;
      }
      v25 = *(_WORD **)&v5->m_actarray[8];
      for ( m = p_WORD; m != v25; ++m )
        *m = *p_WORD2;
      result = (_WORD *)(v20 + *(_DWORD *)&v5->m_actarray[8]);
      *(_DWORD *)&v5->m_actarray[8] = result;
    }
  }
  else
  {
    v7 = *(_DWORD *)&_this->m_actarray[4];
    if ( !v7 || (v8 = ((int)result - v7) >> 1, dwVal >= v8) )
      v8 = dwVal;
    if ( v7 )
      v9 = ((int)result - v7) >> 1;
    else
      v9 = 0;
    v10 = v8 + v9;
    v34 = v10;
    if ( v10 < 0 )
      v10 = 0;
    dwVala = operator new(2 * v10);
    v11 = dwVala;
    for ( n = *(_WORD **)&v5->m_actarray[4]; n != p_WORD; ++v11 )
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
          *v13 = *p_WORD2;
          v5 = _this;
        }
        ++v13;
        --v14;
      }
      while ( v14 );
    }
    v15 = *(_WORD **)&v5->m_actarray[8];
    v16 = &v11[dwVal];
    if ( p_WORD != v15 )
    {
      v17 = p_WORD;
      do
      {
        if ( v16 )
          *v16 = *v17;
        ++v17;
        ++v16;
      }
      while ( v17 != v15 );
    }
    operator delete(*(void **)&_this->m_actarray[4]);
    *(_DWORD *)&_this->m_actarray[12] = &dwVala[v34];
    v18 = *(_DWORD *)&_this->m_actarray[4];
    if ( v18 )
    {
      v19 = *(_DWORD *)&_this->m_actarray[8];
      *(_DWORD *)&_this->m_actarray[4] = dwVala;
      result = &dwVala[dwVal + ((v19 - v18) >> 1)];
    }
    else
    {
      *(_DWORD *)&_this->m_actarray[4] = dwVala;
      result = &dwVala[dwVal];
    }
    *(_DWORD *)&_this->m_actarray[8] = result;
  }
  return result;
}

// 0x0053A8D0
unsigned int ActVec_InsertN(Actor *_this, char *pszBuf, unsigned int nX, char *nY)
{
  char *v4; // edi
  unsigned int v5; // esi
  int v6; // ecx
  unsigned int v7; // ebx
  int v8; // edx
  unsigned int v9; // eax
  int v10; // ebp
  char *i; // edi
  int j; // edi
  char *v13; // edi
  char *v14; // eax
  char *v15; // ebp
  Actor *v16; // ebp
  Actor *k; // edi
  int v18; // eax
  int v19; // edx
  unsigned int v20; // esi
  unsigned int result; // eax
  char *v23; // ebx
  int v24; // edi
  unsigned int v25; // esi
  char *v26; // ebx
  int v27; // ebx
  int v28; // esi
  int v29; // edi
  int *v30; // ebx
  Actor *v31; // edx
  int *v32; // eax
  char *v33; // ebx
  Actor *v34; // [esp+0x10] [ebp-0xC]
  Actor *v35; // [esp+0x14] [ebp-0x8]
  Actor *v36; // [esp+0x14] [ebp-0x8]
  char *v37; // [esp+0x18] [ebp-0x4]
  char *pszBufa; // [esp+0x20] [ebp+0x4]
  unsigned int pszBufb; // [esp+0x20] [ebp+0x4]
  char *nXa; // [esp+0x24] [ebp+0x8]
  char *nXb; // [esp+0x24] [ebp+0x8]
  int *nXc; // [esp+0x24] [ebp+0x8]
  char *nXd; // [esp+0x24] [ebp+0x8]
  char *nYa; // [esp+0x28] [ebp+0xC]

  v4 = *(char **)&_this->m_actarray[8];
  v5 = nX;
  v34 = _this;
  if ( (*(_DWORD *)&_this->m_actarray[12] - (int)v4) / 164 >= nX )
  {
    result = (unsigned int)((unsigned __int64)(1676084799LL * (v4 - pszBuf)) >> 32) >> 31;
    if ( (v4 - pszBuf) / 164 >= nX )
    {
      if ( nX )
      {
        v27 = *(_DWORD *)&_this->m_actarray[8];
        result = 164 * nX;
        v28 = (int)&v4[-164 * nX];
        pszBufb = 164 * nX;
        if ( (char *)v28 != v4 )
        {
          do
          {
            ((VideoPlayer *)v27)->SetRegion(v28);
            v28 += 164;
            v27 += 164;
          }
          while ( (char *)v28 != v4 );
          _this = v34;
          result = 164 * nX;
        }
        v29 = *(_DWORD *)&_this->m_actarray[8];
        v30 = (int *)(v29 - result);
        if ( pszBuf != (char *)(v29 - result) )
        {
          v31 = (Actor *)(v29 + 148);
          v32 = v30 + 37;
          while ( 1 )
          {
            v30 -= 41;
            nXc = v32 - 41;
            qmemcpy((void *)(v29 - 164), v30, 0x84u);
            v36 = (Actor *)((char *)v31 - 164);
            ((Actor *)((char *)v31 - 180))->ActArray_Assign(v32 - 45);
            ((Actor *)v36)->BoneIndexVec_Assign(nXc);
            if ( v30 == (int *)pszBuf )
              break;
            v32 = nXc;
            v31 = v36;
            v29 -= 164;
          }
          _this = v34;
          result = pszBufb;
        }
        v33 = pszBuf;
        nXd = &pszBuf[result];
        if ( pszBuf != &pszBuf[result] )
        {
          do
          {
            qmemcpy(v33, nY, 0x84u);
            ((Actor *)(v33 + 132))->ActArray_Assign((int *)nY + 33);
            ((Actor *)(v33 + 148))->BoneIndexVec_Assign((int *)nY + 37);
            v33 += 164;
          }
          while ( v33 != nXd );
          _this = v34;
          result = pszBufb;
        }
        *(_DWORD *)&_this->m_actarray[8] += result;
      }
    }
    else
    {
      v23 = pszBuf;
      pszBufa = (char *)(164 * nX);
      if ( pszBuf != v4 )
      {
        nXa = &pszBuf[164 * nX];
        do
        {
          ((VideoPlayer *)nXa)->SetRegion((int)v23);
          v23 += 164;
          nXa += 164;
        }
        while ( v23 != v4 );
        _this = v34;
      }
      v24 = *(_DWORD *)&_this->m_actarray[8];
      v25 = v5 - (v24 - (int)pszBuf) / 164;
      if ( v25 )
      {
        do
        {
          ((VideoPlayer *)v24)->SetRegion((int)nY);
          v24 += 164;
          --v25;
        }
        while ( v25 );
        _this = v34;
      }
      v26 = pszBuf;
      nXb = *(char **)&_this->m_actarray[8];
      if ( pszBuf != nXb )
      {
        do
        {
          qmemcpy(v26, nY, 0x84u);
          ((Actor *)(v26 + 132))->ActArray_Assign((int *)nY + 33);
          ((Actor *)(v26 + 148))->BoneIndexVec_Assign((int *)nY + 37);
          v26 += 164;
        }
        while ( v26 != nXb );
        _this = v34;
      }
      result = (unsigned int)&pszBufa[*(_DWORD *)&_this->m_actarray[8]];
      *(_DWORD *)&_this->m_actarray[8] = result;
    }
  }
  else
  {
    v6 = *(_DWORD *)&_this->m_actarray[4];
    if ( !v6 || (v7 = (int)&v4[-v6] / 164, nX >= v7) )
      v7 = nX;
    if ( v6 )
      v8 = (int)&v4[-v6] / 164;
    else
      v8 = 0;
    v9 = v8 + v7;
    v35 = (Actor *)(v8 + v7);
    if ( (int)(v8 + v7) < 0 )
      v9 = 0;
    v37 = (char *)operator new(164 * v9);
    v10 = (int)v37;
    for ( i = *(char **)&v34->m_actarray[4]; i != pszBuf; v10 += 164 )
    {
      ((VideoPlayer *)v10)->SetRegion((int)i);
      i += 164;
    }
    for ( j = v10; nX; --nX )
    {
      ((VideoPlayer *)j)->SetRegion((int)nY);
      j += 164;
    }
    v13 = pszBuf;
    v14 = (char *)(v10 + 164 * v5);
    v15 = *(char **)&v34->m_actarray[8];
    if ( pszBuf != v15 )
    {
      nYa = v14;
      do
      {
        ((VideoPlayer *)nYa)->SetRegion((int)v13);
        v13 += 164;
        nYa += 164;
      }
      while ( v13 != v15 );
    }
    v16 = *(Actor **)&v34->m_actarray[8];
    for ( k = *(Actor **)&v34->m_actarray[4]; k != v16; k = (Actor *)((char *)k + 164) )
      ((Actor *)k)->ClearAllocBuffers();
    operator delete(*(void **)&v34->m_actarray[4]);
    *(_DWORD *)&v34->m_actarray[12] = &v37[164 * (_DWORD)v35];
    v18 = *(_DWORD *)&v34->m_actarray[4];
    if ( v18 )
      v19 = (*(_DWORD *)&v34->m_actarray[8] - v18) / 164;
    else
      v19 = 0;
    v20 = v19 + v5;
    *(_DWORD *)&v34->m_actarray[4] = v37;
    *(_DWORD *)&v34->m_actarray[8] = &v37[164 * v20];
    return 41 * v20;
  }
  return result;
}

// 0x0053ACA0
char * ActVec_InsertRange(Actor *_this, char *pszBuf, unsigned int dwVal, const void *pData)
{
  unsigned int v4; // esi
  Actor *v5; // edi
  char *result; // eax
  int v7; // edx
  unsigned int v8; // ecx
  int v9; // eax
  int v10; // eax
  char *v11; // edx
  char *i; // eax
  char *v13; // eax
  unsigned int v14; // ebx
  char *v15; // ebp
  char *v16; // ebx
  char *v17; // eax
  int v18; // ecx
  int v19; // eax
  char *v21; // edx
  char *v22; // ebx
  char *v23; // eax
  unsigned int v24; // esi
  unsigned int v25; // edx
  char *v26; // edx
  char *v27; // eax
  char *v28; // edi
  unsigned int v29; // esi
  char *v30; // ebx
  char *v31; // edx
  char *v32; // edx
  char *v33; // eax
  char *v34; // eax
  char *v35; // edi
  int v37; // [esp+0x14] [ebp-0x8]
  char *v38; // [esp+0x18] [ebp-0x4]
  char *pszBufa; // [esp+0x20] [ebp+0x4]

  v4 = dwVal;
  v5 = _this;
  result = *(char **)&_this->m_actarray[8];
  if ( (*(_DWORD *)&_this->m_actarray[12] - (int)result) >> 6 >= dwVal )
  {
    if ( (result - pszBuf) >> 6 >= dwVal )
    {
      if ( !dwVal )
        return result;
      v29 = dwVal << 6;
      v30 = *(char **)&_this->m_actarray[8];
      v31 = &result[-64 * dwVal];
      pszBufa = (char *)(dwVal << 6);
      if ( v31 != result )
      {
        do
        {
          if ( v30 )
          {
            qmemcpy(v30, v31, 0x40u);
            v5 = _this;
          }
          v31 += 64;
          v30 += 64;
        }
        while ( v31 != result );
        v29 = dwVal << 6;
      }
      v32 = *(char **)&v5->m_actarray[8];
      v33 = &v32[-v29];
      if ( pszBuf != &v32[-v29] )
      {
        do
        {
          v33 -= 64;
          v32 -= 64;
          qmemcpy(v32, v33, 0x40u);
        }
        while ( v33 != pszBuf );
        v5 = _this;
      }
      v34 = pszBuf;
      if ( pszBuf == &pszBuf[(_DWORD)pszBufa] )
        goto LABEL_54;
      do
      {
        v35 = v34;
        v34 += 64;
        qmemcpy(v35, pData, 0x40u);
      }
      while ( v34 != &pszBuf[(_DWORD)pszBufa] );
    }
    else
    {
      pszBufa = (char *)(dwVal << 6);
      v21 = &pszBuf[64 * dwVal];
      if ( pszBuf != result )
      {
        v22 = pszBuf;
        do
        {
          if ( v21 )
          {
            qmemcpy(v21, v22, 0x40u);
            v5 = _this;
            v4 = dwVal;
          }
          v22 += 64;
          v21 += 64;
        }
        while ( v22 != result );
      }
      v23 = *(char **)&v5->m_actarray[8];
      v24 = v4 - ((v23 - pszBuf) >> 6);
      if ( v24 )
      {
        v25 = v24;
        do
        {
          if ( v23 )
          {
            qmemcpy(v23, pData, 0x40u);
            v5 = _this;
          }
          v23 += 64;
          --v25;
        }
        while ( v25 );
      }
      v26 = *(char **)&v5->m_actarray[8];
      v27 = pszBuf;
      if ( pszBuf == v26 )
        goto LABEL_54;
      do
      {
        v28 = v27;
        v27 += 64;
        qmemcpy(v28, pData, 0x40u);
      }
      while ( v27 != v26 );
    }
    v5 = _this;
LABEL_54:
    result = &pszBufa[*(_DWORD *)&v5->m_actarray[8]];
    *(_DWORD *)&v5->m_actarray[8] = result;
    return result;
  }
  v7 = *(_DWORD *)&_this->m_actarray[4];
  if ( !v7 || (v8 = (int)&result[-v7] >> 6, dwVal >= v8) )
    v8 = dwVal;
  if ( v7 )
    v9 = (int)&result[-v7] >> 6;
  else
    v9 = 0;
  v10 = v8 + v9;
  v37 = v10;
  if ( v10 < 0 )
    v10 = 0;
  v38 = (char *)operator new(v10 << 6);
  v11 = v38;
  for ( i = *(char **)&v5->m_actarray[4]; i != pszBuf; v11 += 64 )
  {
    if ( v11 )
    {
      qmemcpy(v11, i, 0x40u);
      v5 = _this;
      v4 = dwVal;
    }
    i += 64;
  }
  v13 = v11;
  if ( v4 )
  {
    v14 = v4;
    do
    {
      if ( v13 )
      {
        qmemcpy(v13, pData, 0x40u);
        v5 = _this;
        v4 = dwVal;
      }
      v13 += 64;
      --v14;
    }
    while ( v14 );
  }
  v15 = *(char **)&v5->m_actarray[8];
  v16 = &v11[64 * v4];
  if ( pszBuf != v15 )
  {
    v17 = pszBuf;
    do
    {
      if ( v16 )
      {
        qmemcpy(v16, v17, 0x40u);
        v5 = _this;
        v4 = dwVal;
      }
      v17 += 64;
      v16 += 64;
    }
    while ( v17 != v15 );
  }
  operator delete(*(void **)&v5->m_actarray[4]);
  v18 = *(_DWORD *)&v5->m_actarray[4];
  *(_DWORD *)&v5->m_actarray[12] = &v38[64 * v37];
  if ( v18 )
  {
    v19 = *(_DWORD *)&v5->m_actarray[8];
    *(_DWORD *)&v5->m_actarray[4] = v38;
    result = &v38[64 * (v4 + ((v19 - v18) >> 6))];
  }
  else
  {
    *(_DWORD *)&v5->m_actarray[4] = v38;
    result = &v38[64 * v4];
  }
  *(_DWORD *)&v5->m_actarray[8] = result;
  return result;
}

// 0x0053B010
char **ActVec_UninitCopy(int nVal, unsigned int *pdwVal, unsigned int *pdwVal2, char **a4)
{
  int v4; // ebp
  char *v5; // edi
  const void *v6; // esi
  int v7; // ebp
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
  int i; // [esp+0x4] [ebp-0x4]
  char *v22; // [esp+0x4] [ebp-0x4]

  v6 = (const void *)nVal;
  if ( (unsigned int *)nVal == pdwVal )
    return (char **)pdwVal2;
  v19 = v4;
  v18 = v5;
  v7 = nVal + 136;
  v8 = pdwVal2 + 34;
  while ( 1 )
  {
    qmemcpy(pdwVal2, v6, 0x84u);
    if ( v8 - 1 != (unsigned int *)(v7 - 4) )
    {
      v9 = *(_DWORD *)v7;
      if ( *(_DWORD *)v7 )
        v20 = (int)(*(_DWORD *)(v7 + 4) - v9) / 656;
      else
        v20 = 0;
      if ( *v8 )
        v10 = (int)(v8[1] - *v8) / 656;
      else
        v10 = 0;
      if ( v20 > v10 )
      {
        if ( v9 )
          v9 = (int)(*(_DWORD *)(v7 + 4) - v9) / 656;
        if ( v9 > ((Actor *)(v8 - 1))->GetActionCountEx() )
        {
          nullsub_2(*v8, v8[1]);
          operator delete((void *)*v8);
          Count = ((Actor *)(v7 - 4))->GetCount();
          if ( Count < 0 )
            Count = 0;
          v15 = (char *)operator new(656 * Count);
          *v8 = (unsigned int)v15;
          v16 = ((Actor *)(v8 - 1))->CompareBuffers(*(char **)v7, *(char **)(v7 + 4), v15);
          v8[1] = (unsigned int)v16;
          v8[2] = (unsigned int)v16;
        }
        else
        {
          v22 = *(char **)v7;
          v13 = &v22[656 * ((Actor *)(v8 - 1))->GetCount()];
          ActVec_Reallocate(*(_DWORD *)v7, v13, (char *)*v8, v18, v19);
          ((Actor *)(v8 - 1))->CompareBuffers(v13, *(char **)(v7 + 4), (char *)v8[1]);
          v8[1] = *v8 + 656 * ((Actor *)(v7 - 4))->GetCount();
        }
      }
      else
      {
        v11 = (Actor *)*v8;
        for ( i = *(_DWORD *)(v7 + 4); v9 != i; v11 = (Actor *)((char *)v11 + 656) )
        {
          ((Actor *)v11)->SetCurrentAction(v9);
          v9 += 656;
        }
        if ( *(_DWORD *)v7 )
          v12 = (*(_DWORD *)(v7 + 4) - *(_DWORD *)v7) / 656;
        else
          v12 = 0;
        v8[1] = *v8 + 656 * v12;
      }
    }
    ((Actor *)(v8 + 3))->BoneIndexVec_Assign((int *)(v7 + 12));
    v8 += 41;
    pdwVal2 += 41;
    v7 += 164;
    nVal += 164;
    if ( (unsigned int *)nVal == pdwVal )
      break;
    v6 = (const void *)nVal;
  }
  return (char **)pdwVal2;
}

// 0x0053B2D0
int *ActVec_UninitCopy2(int nVal, int *p_DWORD, int *p_DWORD2, char **a4)
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

  result = p_DWORD;
  v7 = (int *)nVal;
  if ( (int *)nVal != p_DWORD )
  {
    v20 = v4;
    v19 = v5;
    v8 = (Actor *)(p_DWORD2 + 33);
    v9 = (char **)(nVal + 136);
    while ( 1 )
    {
      qmemcpy(v7, p_DWORD2, 0x84u);
      if ( v9 - 1 != (char **)v8 )
      {
        v10 = p_DWORD2[34];
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
          if ( v10 > ((Actor *)(v9 - 1))->GetActionCountEx() )
          {
            nullsub_2(*v9, v9[1]);
            operator delete(*v9);
            Count = ((Actor *)v8)->GetCount();
            if ( Count < 0 )
              Count = 0;
            v17 = (char *)operator new(656 * Count);
            *v9 = v17;
            v18 = ((Actor *)(v9 - 1))->CompareBuffers((char *)p_DWORD2[34], (char *)p_DWORD2[35], v17);
            v9[1] = v18;
            v9[2] = v18;
          }
          else
          {
            v23 = p_DWORD2[34];
            v15 = (char *)(v23 + 656 * ((Actor *)(v9 - 1))->GetCount());
            ActVec_Reallocate(p_DWORD2[34], v15, *v9, v19, v20);
            ((Actor *)(v9 - 1))->CompareBuffers(v15, (char *)p_DWORD2[35], v9[1]);
            v9[1] = &(*v9)[656 * ((Actor *)v8)->GetCount()];
          }
        }
        else
        {
          v12 = (Actor *)*v9;
          for ( i = p_DWORD2[35]; v10 != i; v12 = (Actor *)((char *)v12 + 656) )
          {
            ((Actor *)v12)->SetCurrentAction(v10);
            v10 += 656;
          }
          v13 = p_DWORD2[34];
          if ( v13 )
            v14 = (p_DWORD2[35] - v13) / 656;
          else
            v14 = 0;
          v9[1] = &(*v9)[656 * v14];
        }
      }
      ((Actor *)(v9 + 3))->BoneIndexVec_Assign(p_DWORD2 + 37);
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
char **ActVec_UninitFill(int nVal, int nVal2, int nVal3, char **a4)
{
  int v4; // ebp
  char *v5; // edi
  int v6; // esi
  int v7; // ebp
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
  int i; // [esp+0x4] [ebp-0x4]
  char *v22; // [esp+0x4] [ebp-0x4]
  int nVal2a; // [esp+0x10] [ebp+0x8]

  v6 = nVal2;
  if ( nVal == nVal2 )
    return (char **)nVal3;
  v19 = v4;
  v18 = v5;
  v7 = nVal2 + 136;
  v8 = (char **)(nVal3 + 136);
  while ( 1 )
  {
    nVal2a = v6 - 164;
    v7 -= 164;
    nVal3 -= 164;
    v8 -= 41;
    qmemcpy((void *)nVal3, (const void *)(v6 - 164), 0x84u);
    if ( v8 - 1 != (char **)(v7 - 4) )
    {
      v9 = *(_DWORD *)v7;
      if ( *(_DWORD *)v7 )
        v20 = (int)(*(_DWORD *)(v7 + 4) - v9) / 656;
      else
        v20 = 0;
      if ( *v8 )
        v10 = (v8[1] - *v8) / 656;
      else
        v10 = 0;
      if ( v20 > v10 )
      {
        if ( v9 )
          v9 = (int)(*(_DWORD *)(v7 + 4) - v9) / 656;
        if ( v9 > ((Actor *)(v8 - 1))->GetActionCountEx() )
        {
          nullsub_2(*v8, v8[1]);
          operator delete(*v8);
          Count = ((Actor *)(v7 - 4))->GetCount();
          if ( Count < 0 )
            Count = 0;
          v15 = (char *)operator new(656 * Count);
          *v8 = v15;
          v16 = ((Actor *)(v8 - 1))->CompareBuffers(*(char **)v7, *(char **)(v7 + 4), v15);
          v8[1] = v16;
          v8[2] = v16;
        }
        else
        {
          v22 = *(char **)v7;
          v13 = &v22[656 * ((Actor *)(v8 - 1))->GetCount()];
          ActVec_Reallocate(*(_DWORD *)v7, v13, *v8, v18, v19);
          ((Actor *)(v8 - 1))->CompareBuffers(v13, *(char **)(v7 + 4), v8[1]);
          v8[1] = &(*v8)[656 * ((Actor *)(v7 - 4))->GetCount()];
        }
      }
      else
      {
        v11 = (Actor *)*v8;
        for ( i = *(_DWORD *)(v7 + 4); v9 != i; v11 = (Actor *)((char *)v11 + 656) )
        {
          ((Actor *)v11)->SetCurrentAction(v9);
          v9 += 656;
        }
        if ( *(_DWORD *)v7 )
          v12 = (*(_DWORD *)(v7 + 4) - *(_DWORD *)v7) / 656;
        else
          v12 = 0;
        v8[1] = &(*v8)[656 * v12];
      }
    }
    ((Actor *)(v8 + 3))->BoneIndexVec_Assign((int *)(v7 + 12));
    if ( nVal2a == nVal )
      break;
    v6 = nVal2a;
  }
  return (char **)nVal3;
}

// 0x0053B6E0
void Actor_CopyConstruct_1C(void *pDst, const void *pSrc)
{
  if ( pDst )
    qmemcpy(pDst, pSrc, 0x1Cu);
}

// 0x0053B700
void Actor_CopyConstruct_290(void *pDst, const void *pSrc)
{
  if ( pDst )
    qmemcpy(pDst, pSrc, 0x290u);
}

// 0x0053B870
void Actor_CopyConstruct_40(void *pDst, const void *pSrc)
{
  if ( pDst )
    qmemcpy(pDst, pSrc, 0x40u);
}

// 0x0053BEE0
char *ActVec_Reallocate(int nVal, char *pszBuf, char *pszBuf2, char *pszBuf3, int nVal2)
{
  int v5; // edi
  char *v6; // ebx
  char *v7; // ecx
  char *v8; // esi
  int v9; // edi
  int v10; // ebx
  char *v11; // eax
  char *v12; // edx
  char *v13; // eax
  int v14; // edx
  char *v15; // eax
  int v16; // eax
  char *v17; // ebp
  char *v18; // eax
  char *v19; // eax
  char *v20; // eax
  int v21; // ecx
  char v22; // dl
  int v24; // [esp-0xC] [ebp-0x18]
  int v25; // [esp+0x4] [ebp-0x8]

  v6 = (char *)nVal;
  if ( (char *)nVal == pszBuf )
    return pszBuf2;
  v7 = pszBuf2;
  v24 = v5;
  v8 = pszBuf2 + 632;
  v9 = nVal + 632;
  while ( 1 )
  {
    *(_DWORD *)v7 = *(_DWORD *)v6;
    v10 = v6 - v7;
    v11 = v8 - 628;
    do
    {
      *v11 = v11[v10];
      ++v11;
    }
    while ( (unsigned int)&v11[-4 - (_DWORD)v7] < 0x20 );
    *(v8 - 596) = *(_BYTE *)(v9 - 596);
    *(v8 - 595) = *(_BYTE *)(v9 - 595);
    *((_DWORD *)v8 - 148) = *(_DWORD *)(v9 - 592);
    *((_DWORD *)v8 - 147) = *(_DWORD *)(v9 - 588);
    *((_DWORD *)v8 - 146) = *(_DWORD *)(v9 - 584);
    *((_DWORD *)v8 - 145) = *(_DWORD *)(v9 - 580);
    v12 = v8 - 576;
    *(_DWORD *)v12 = *(_DWORD *)(v9 - 576);
    *((_DWORD *)v12 + 1) = *(_DWORD *)(v9 - 576 + 4);
    *((_DWORD *)v12 + 2) = *(_DWORD *)(v9 - 576 + 8);
    *((_DWORD *)v12 + 3) = *(_DWORD *)(v9 - 576 + 12);
    *(v8 - 560) = *(_BYTE *)(v9 - 560);
    *(v8 - 559) = *(_BYTE *)(v9 - 559);
    *(v8 - 558) = *(_BYTE *)(v9 - 558);
    *(v8 - 557) = *(_BYTE *)(v9 - 557);
    v13 = v8 - 556;
    v14 = 6;
    do
    {
      *(_DWORD *)v13 = *(_DWORD *)&v13[v10];
      v13 += 4;
      --v14;
    }
    while ( v14 );
    *(v8 - 532) = *(_BYTE *)(v9 - 532);
    *((_WORD *)v8 - 265) = *(_WORD *)(v9 - 530);
    *((_WORD *)v8 - 264) = *(_WORD *)(v9 - 528);
    *((_WORD *)v8 - 263) = *(_WORD *)(v9 - 526);
    *((_WORD *)v8 - 262) = *(_WORD *)(v9 - 524);
    *(v8 - 522) = *(_BYTE *)(v9 - 522);
    v15 = v8 - 521;
    do
    {
      *v15 = v15[v10];
      ++v15;
    }
    while ( (unsigned int)&v15[-111 - (_DWORD)v7] < 0x10 );
    *((_DWORD *)v8 - 126) = *(_DWORD *)(v9 - 504);
    *((_DWORD *)v8 - 125) = *(_DWORD *)(v9 - 500);
    v16 = v9 - (_DWORD)v8;
    v17 = v8 - 496;
    v25 = 16;
    while ( 1 )
    {
      ((gbVec3D *)v17)->operator=(&v17[v16]);
      v17 += 12;
      if ( !--v25 )
        break;
      v16 = v9 - (_DWORD)v8;
    }
    *((_WORD *)v8 - 152) = *(_WORD *)(v9 - 304);
    v18 = v8 - 302;
    do
    {
      *v18 = v18[v10];
      ++v18;
    }
    while ( (unsigned int)&v18[-330 - (_DWORD)pszBuf2] < 0x20 );
    *(v8 - 270) = *(_BYTE *)(v9 - 270);
    ((gbAABBox *)v8 - 268)->operator=(v9 - 268, v24);
    *((_DWORD *)v8 - 61) = *(_DWORD *)(v9 - 244);
    v19 = v8 - 240;
    do
    {
      *v19 = v19[v10];
      ++v19;
    }
    while ( (unsigned int)&v19[-392 - (_DWORD)pszBuf3] < 8 );
    *((_DWORD *)v8 - 58) = *(_DWORD *)(v9 - 232);
    *((_DWORD *)v8 - 57) = *(_DWORD *)(v9 - 228);
    *((_DWORD *)v8 - 56) = *(_DWORD *)(v9 - 224);
    v20 = v8 - 220;
    v21 = 52;
    do
    {
      *(_DWORD *)v20 = *(_DWORD *)&v20[v10];
      v20 += 4;
      --v21;
    }
    while ( v21 );
    *((_DWORD *)v8 - 3) = *(_DWORD *)(v9 - 12);
    *((_DWORD *)v8 - 2) = *(_DWORD *)(v9 - 8);
    *((_DWORD *)v8 - 1) = *(_DWORD *)(v9 - 4);
    *(_DWORD *)v8 = *(_DWORD *)v9;
    ((gbVec3D *)v8 + 4)->operator=(v9 + 4);
    v22 = *(_BYTE *)(v9 + 16);
    v9 += 656;
    v8[16] = v22;
    v8[17] = *(_BYTE *)(v9 - 639);
    pszBuf2 += 656;
    *((_DWORD *)v8 + 5) = *(_DWORD *)(v9 - 636);
    v8 += 656;
    nVal += 656;
    if ( (char *)nVal == pszBuf )
      break;
    v6 = (char *)nVal;
    v7 = pszBuf2;
  }
  return pszBuf2;
}

// 0x0053CB10
int WinProc_HWND_InputLine(void *_this, char pData)
{
  int result; // eax
  unsigned int v4; // ecx
  _BYTE *v5; // ebx
  int v6; // ecx

  if ( pData == 96 )
  {
    result = *((_DWORD *)_this + 1161) == 0;
    *((_DWORD *)_this + 1161) = result;
  }
  else
  {
    result = *((_DWORD *)_this + 1161);
    if ( result )
    {
      switch ( pData )
      {
        case 8:
          result = 0;
          v6 = strlen((const char *)_this + 4656);
          if ( v6 >= 2 )
          {
            *((_BYTE *)_this + v6 + 4655) = 0;
            *((_BYTE *)_this + v6 + 4654) = 95;
          }
          break;
        case 13:
          v5 = (char *)_this + 4656;
          *((_BYTE *)_this + strlen((const char *)_this + 4656) + 4655) = 0;
          ((Logger *)_this)->Write(off_6088D8, (_BYTE)_this + 48);
          WinProc_HWND_ExecCommand((char *)_this);
          memset(v5, 0, 0x64u);
          *v5 = 95;
          return 0;
        case 27:
          memset((char *)_this + 4656, 0, 0x64u);
          *((_BYTE *)_this + 4656) = 95;
          return 0;
        default:
          result = 0;
          v4 = strlen((const char *)_this + 4656);
          if ( v4 < 0x63 )
          {
            *((_BYTE *)_this + v4 + 4655) = pData;
            *((_BYTE *)_this + v4 + 4656) = 95;
          }
          break;
      }
    }
  }
  return result;
}

// 0x0053CCF0
char * WinProc_HWND_ExecCommand(char *_this)
{
  char *result; // eax
  char *v3; // eax
  char *v4; // ebp
  int v5; // esi
  const char *i; // edi
  char Str[100]; // [esp+0x10] [ebp-0x64] BYREF

  if ( *((_DWORD *)_this + 1162) )
  {
    strcpy(Str, _this + 4656);
    v3 = strchr(Str, 32);
    v4 = v3;
    if ( v3 )
    {
      *v3 = 0;
      v4 = v3 + 1;
    }
    v5 = 0;
    if ( *(int *)_this <= 0 )
    {
      return ((Logger *)_this)->Write("Bad command or file name.");
    }
    else
    {
      for ( i = _this + 4; _strcmpi(i, Str); i += 136 )
      {
        if ( ++v5 >= *(_DWORD *)_this )
          return ((Logger *)_this)->Write("Bad command or file name.");
      }
      return (*((char *( **)(char *))_this + 34 * v5 + 34))(v4);
    }
  }
  else
  {
    result = (char *)gbCrc32Compute(_this + 4656);
    *((_DWORD *)_this + 1162) = result + 706426632 == 0;
  }
  return result;
}

// 0x0053CDE0
int WinProc_HWND_SetAndExec(char *_this, char *Source)
{
  char *v3; // esi

  v3 = _this + 4656;
  strncpy(_this + 4656, Source, 0x64u);
  WinProc_HWND_ExecCommand(_this);
  memset(v3, 0, 0x64u);
  *v3 = 95;
  return 0;
}

// 0x0053CF30
char * Texture_Info_FormatException(
        char *ArgList,
        const char *pszName,
        const char *pszName2,
        const char *pszName3,
        int nVal)
{
  char *v5; // ecx
  const char *v6; // esi

  v6 = v5;
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
  v2 = result;
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
  v2 = result;
  if ( result )
  {
    fprintf(result, byte_17B3AAC);
    return (FILE *)fclose(v2);
  }
  return result;
}

// 0x0053EDD0
int nearby_53edd0(int a1)
{
  return a1 - 1;
}

// 0x0053F4C0
_DWORD * nearby_53f4c0(_DWORD *_this)
{
  return _this;
}

// 0x0053F4D0
void * sdtor_20(void *Block, char a2)
{
  nearby_53f4f0(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0053F4F0
void nearby_53f4f0(_DWORD *_this)
{
  ;
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
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v2, 1, g_pRenderEffect_1895050, 0);
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
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v2, 1, (gbRenderEffect *)g_pTexColorEffect, v9);
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

  v0 = *v14;
  v9.z = 0.0;
  v9.color = v0;
  if ( !v16 )
  {
    v3 = v15->pTexPt[0];
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
    v1 = v15->pTexPt[0];
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
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v9, 1, g_pRenderEffect_1895060, v15);
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
  double v5; // st7
  double v6; // st6
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
  v5 = (double)v14 + (double)v14;
  v6 = v5 / (double)g_DrvInfo.height;
  v2->ScaleX = v5 / (double)g_DrvInfo.width;
  v2->ScaleY = v6;
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v15) = *v13;
    BYTE1(v15) = v13[1];
    LOBYTE(v15) = v13[2];
  }
  else
  {
    *(_WORD *)((char *)&v15 + 1) = *(_WORD *)(v13 + 1);
    LOBYTE(v15) = *v13;
  }
  HIBYTE(v15) = v13[3];
  v2->curColor.Color = v15;
  v8 = 1.0 - ((double)v11 + (double)v11) / (double)g_DrvInfo.height;
  v7 = ((double)v9 + (double)v9) / (double)g_DrvInfo.width - 1.0;
  ((void ( *)(gbPrintFont *, int, _DWORD, _DWORD, int, int))v2->pGfxMgr->DrvInfo.subtype)(
    v2,
    v12,
    LODWORD(v7),
    LODWORD(v8),
    1176256512,
    1176256512);
  return ((int ( *)(gbPrintFont *))v2->pGfxMgr->hGfxWnd)(v2);
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
  double v6; // st7
  double v7; // st6
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
        v6 = (double)v27 + (double)v27;
        v18 = 0;
        v21 = 0;
        v22 = 0;
        v7 = v6 / (double)g_DrvInfo.height;
        v26[12] = v6 / (double)g_DrvInfo.width;
        v26[13] = v7;
        v8 = v27;
        v9 = v25;
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
            v14 = *v9;
            v23 = v21 + v14 + v8 * v18 / 2;
            if ( (int)(v23 + v27 / 2 * strlen((const char *)&v28)) > v25[2] )
            {
              v18 = 0;
              v23 = v14;
              v19 += v27;
            }
            if ( v22 + v19 + v25[1] > v25[3] )
              return (*(int ( **)(float *))(*(_DWORD *)v26 + 8))(v26);
            v17 = 1.0 - ((double)(v22 + v19 + v25[1]) + (double)(v22 + v19 + v25[1])) / (double)g_DrvInfo.height;
            v16 = ((double)v23 + (double)v23) / (double)g_DrvInfo.width - 1.0;
            (*(void ( **)(int *, _DWORD, _DWORD, int, int))(*(_DWORD *)v26 + 16))(
              &v28,
              LODWORD(v16),
              LODWORD(v17),
              1176256512,
              1176256512);
            v8 = v27;
            v15 = strlen((const char *)&v28) + 1;
            v9 = v25;
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
      return (*(int ( **)(gbGfxManager *, _DWORD))(*(_DWORD *)gfxMgr + 100))(
               gfxMgr,
               *(_DWORD *)(result + 4 * v3));
  }
  return result;
}

// 0x00551C66
void InitComItem()
{
  __m64 v0; // mm1
  __m64 v1; // mm2
  __m64 v2; // mm2
  __m64 *v3; // [esp+0x4] [ebp+0x4]
  __m64 *v4; // [esp+0x8] [ebp+0x8]
  __m64 *v5; // [esp+0xC] [ebp+0xC]

  _m_femms();
  v0 = _mm_cvtsi32_si64(v5[1].m64_i64);
  v1 = _m_pfmul((__m64)v4->m64_i64, (__m64)v5->m64_i64);
  v2 = _m_pfadd(_m_pfacc(v1, v1), _m_pfmul(_mm_cvtsi32_si64(v4[1].m64_i64), v0));
  v3->m64_i64 = v5->m64_i64;
  LODWORD(v3[1].m64_i64) = _mm_cvtsi64_si32(v0);
  HIDWORD(v3[1].m64_i64) = _mm_cvtsi64_si32(_m_pxor(v2, (__m64)0x80000000LL));
  _m_femms();
}

// 0x0055CCE4
// positive sp value has been detected, the output may be wrong!
int NextRole(int *a1)
{
  int v2; // [esp-0x4] [ebp-0x4]

  return v2;
}

// 0x00569020
int PAL3_RandomPickValues(int nVal, int nVal2, int nVal3, int nVal4, int nVal5, int *p_DWORD)
{
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  int result; // eax
  int *v10; // esi
  int v11; // edi
  int v12; // eax
  int v13; // edx
  int v14; // et2
  int v15; // edx
  int v16; // [esp+0x10] [ebp-0x4]

  memset(p_DWORD, 0, 0x18u);
  v6 = nVal3;
  v16 = 0;
  p_DWORD[6] = 0;
  if ( !nVal2 )
  {
    if ( !nVal3 )
    {
      v6 = nVal4;
      nVal4 = 0;
    }
    nVal2 = v6;
    goto LABEL_5;
  }
  if ( !nVal3 )
  {
LABEL_5:
    v7 = nVal4;
    nVal4 = 0;
    nVal3 = v7;
  }
  if ( nVal2 )
    v16 = 1;
  if ( nVal3 )
    ++v16;
  if ( nVal4 )
    ++v16;
  v8 = nVal;
  if ( nVal5 )
  {
    v8 = nVal + 1;
    *p_DWORD = nVal5;
  }
  result = nVal5 != 0;
  if ( result < v8 )
  {
    v10 = &p_DWORD[result];
    v11 = v8 - result;
    do
    {
      v12 = rand();
      v14 = v12 % v16;
      result = v12 / v16;
      v13 = v14;
      if ( v14 )
      {
        v15 = v13 - 1;
        if ( v15 )
        {
          if ( v15 == 1 )
          {
            result = nVal4;
            *v10 = nVal4;
          }
        }
        else
        {
          *v10 = nVal3;
        }
      }
      else
      {
        *v10 = nVal2;
      }
      ++v10;
      --v11;
    }
    while ( v11 );
  }
  p_DWORD[6] = v8;
  return result;
}
