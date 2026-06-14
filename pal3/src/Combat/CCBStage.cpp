#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBStage.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations
void * sub_446010(void *a2); // from annotations
int sub_508460(...);
int sub_5110B0(...);
int todo_408BD0(...);

int crt_sub_00540070(void); // from annotations

// Unnamed globals (extern)
extern char aFleesuccess[];
extern char byte_17AA91C;
extern char byte_17AA920[256];
extern char byte_17AAA2C;
extern int dword_17AA914;
extern int dword_17AA918;
extern int dword_17AAA20;
extern int dword_17AAA24;
extern int dword_17AAA28;
extern int dword_17ABCE8;
extern int dword_17ABCEC;
extern CCBUI * dword_5DB6C4;
extern float flt_17ABCE4;
extern float flt_17ABCFC;
void __cdecl nullsub_20(void);
void __cdecl nullsub_21(void);
void __cdecl nullsub_28(void);
void __cdecl nullsub_29(void);
void __cdecl nullsub_30(void);
void __cdecl nullsub_55(void);
void __cdecl nullsub_56(void);
void __cdecl nullsub_57(void);
void __cdecl nullsub_58(void);
void __cdecl nullsub_59(void);
void __cdecl nullsub_60(void);
void __cdecl nullsub_61(void);
void __cdecl nullsub_62(void);
void __cdecl nullsub_63(void);
void __cdecl nullsub_64(void);
void __cdecl nullsub_65(void);
void __cdecl nullsub_66(void);
void __cdecl nullsub_67(void);
extern RoleSystem stru_C059A0;
extern unsigned int unk_5DFDEC;

// 0x004C5C20
int CCBStage::GetReadyCount()
{
  int v2; // edi
  int result; // eax
  float *p_fTemp3; // esi

  v2 = 0;
  result = LODWORD(this->m_Task[0].SubTask[0].fTemp2);
  if ( result > 0 )
  {
    p_fTemp3 = &this->m_Task[0].SubTask[0].fTemp3;
    do
    {
      if ( *(_BYTE *)(*(_DWORD *)p_fTemp3 + 13) )
        (*(void ( **)(_DWORD))(**(_DWORD **)p_fTemp3 + 24))(*(_DWORD *)p_fTemp3);
      result = LODWORD(this->m_Task[0].SubTask[0].fTemp2);
      ++v2;
      ++p_fTemp3;
    }
    while ( v2 < result );
  }
  return result;
}

// 0x004D1EF0
int CCBStage::GetActiveTaskCount()
{
  int result; // eax
  int v2; // edx

  result = 0;
  if ( (int)this->m_TempStorageNGH > 0 )
  {
    v2 = 0;
    do
    {
      ++result;
      *(_BYTE *)(v2 + this->m_nTaskCount + 4) = 0;
      v2 += 80;
    }
    while ( result < (int)this->m_TempStorageNGH->m_actarray );
  }
  this->m_pRole[9] = 0;
  this->m_pRole[10] = 0;
  this->m_NGHVariance = (Actor *)-1;
  return result;
}

// 0x004D4D30
int CCBStage::GetTaskParam(int nVal, int nVal2)
{
  int v3; // edx
  int result; // eax

  v3 = 72 * nVal2;
  *(_DWORD *)(*((_DWORD *)&this->m_pCam->fov + 38 * nVal) + v3 + 8) = 3;
  result = *((_DWORD *)&this->m_pCam->fov + 38 * nVal);
  *(_DWORD *)(result + v3 + 16) = this->m_pRoleState;
  return result;
}

// 0x004D4D70
char CCBStage::SetTaskState(int nVal)
{
  int v2; // edx
  _DWORD *v3; // eax
  int v4; // ecx
  _DWORD *i; // eax

  v2 = 0;
  v3 = (_DWORD *)(&this->m_pCam->fov + 38 * nVal);
  v4 = v3[1];
  if ( v4 <= 0 )
    return 1;
  for ( i = (_DWORD *)(*v3 + 8); *i == 4; i += 18 )
  {
    if ( ++v2 >= v4 )
      return 1;
  }
  return 0;
}

// 0x004DF6B0
int * CCBStage::InitStage(int nVal)
{
  memset(this, 0, 0x4618u);
  this->m_pCBSystem = (CCBSystem *)nVal;
  this->m_pRoleState = *(CCBRoleState **)(nVal + 20);
  return (int *)this;
}

// 0x004DF700
char CCBStage::IsInitialized()
{
  ((CCBRoleState *)this)->ResetDialogSlots();
  return 1;
}

// 0x004DF710
void CCBStage::ResetRoundState()
{
  float *v2; // esi
  gbPrintFont *v3; // edi
  gbColorQuad *v4; // eax
  gbGfxManager *pGfxMgr; // edx
  double v6; // st7
  gbPrintFont *v7; // edi
  double v8; // st7
  unsigned int Color; // edx
  gbGfxManager *v10; // eax
  double v11; // st7
  double v12; // st6
  gbPrintFont *v13; // ecx
  unsigned int v14; // eax
  double v15; // st7
  double v16; // st6
  unsigned __int8 m_pCam_high; // al
  unsigned int v18; // [esp+0xC] [ebp-0x34]
  unsigned int v19; // [esp+0x10] [ebp-0x30]
  int v20; // [esp+0x14] [ebp-0x2C]
  gbColorQuad v21; // [esp+0x38] [ebp-0x8] BYREF
  gbColorQuad v22; // [esp+0x3C] [ebp-0x4] BYREF

  v20 = 0;
  if ( (int)this->m_pCamControl > 0 )
  {
    v2 = (float *)&this->m_Task[0].SubTask[1].fp[2];
    do
    {
      switch ( *((_DWORD *)v2 - 69) )
      {
        case 1:
          v3 = gfxMgr->pFontMgr->pAllFont[2];
          // [AUTO-COMMENTED] v4 = ((gbColorQuad *)&v21)->gbColorQuad(*((_BYTE *)v2 - 14), *((_BYTE *)v2 - 15), *((_BYTE *)v2 - 16), *((_BYTE *)v2 - 13));
          pGfxMgr = v3->pGfxMgr;
          v3->curColor = (gbColorQuad)v4->Color;
          v6 = 40.0 / (double)g_DrvInfo.height;
          v3->ScaleX = 40.0 / (double)g_DrvInfo.width;
          v3->ScaleY = v6;
          ((void ( *)(float *, _DWORD, _DWORD, int, int))pGfxMgr->DrvInfo.subtype)(
            v2 - 68,
            *((_DWORD *)v2 - 3),
            *((_DWORD *)v2 - 2),
            1176256512,
            1176256512);
          break;
        case 2:
          v7 = gfxMgr->pFontMgr->pAllFont[3];
          v8 = *v2 / (double)g_DrvInfo.height * 2.5999999;
          v7->ScaleX = *v2 / (double)g_DrvInfo.width + *v2 / (double)g_DrvInfo.width;
          v7->ScaleY = v8;
          // [AUTO-COMMENTED] Color = ((gbColorQuad *)&v22)->gbColorQuad(*((_BYTE *)v2 - 14), *((_BYTE *)v2 - 15), *((_BYTE *)v2 - 16), *((_BYTE *)v2 - 13))->Color;
          v10 = v7->pGfxMgr;
          v7->curColor.Color = Color;
          ((void ( *)(gbPrintFont *, float *, _DWORD, _DWORD, int, int))v10->DrvInfo.subtype)(
            v7,
            v2 - 68,
            *((_DWORD *)v2 - 3),
            *((_DWORD *)v2 - 2),
            1176256512,
            1176256512);
          break;
        case 3:
          v11 = *v2 + *v2;
          v12 = v11 / (double)g_DrvInfo.height;
          v13 = gfxMgr->pFontMgr->pAllFont[1];
          v13->ScaleX = v11 / (double)g_DrvInfo.width;
          v13->ScaleY = v12;
          if ( gbColorQuad::ColorQuadFmt )
          {
            BYTE2(v18) = *((_BYTE *)v2 - 16);
            BYTE1(v18) = *((_BYTE *)v2 - 15);
            LOBYTE(v18) = *((_BYTE *)v2 - 14);
          }
          else
          {
            BYTE2(v18) = *((_BYTE *)v2 - 14);
            LOWORD(v18) = *((_WORD *)v2 - 8);
          }
          HIBYTE(v18) = *((_BYTE *)v2 - 13);
          v14 = v18;
          goto LABEL_14;
        case 7:
          v15 = *v2 * 3.0;
          v16 = v15 / (double)g_DrvInfo.height;
          v13 = gfxMgr->pFontMgr->pAllFont[1];
          v13->ScaleX = v15 / (double)g_DrvInfo.width;
          v13->ScaleY = v16;
          if ( gbColorQuad::ColorQuadFmt )
          {
            BYTE2(v19) = *((_BYTE *)v2 - 16);
            BYTE1(v19) = *((_BYTE *)v2 - 15);
            LOBYTE(v19) = *((_BYTE *)v2 - 14);
          }
          else
          {
            BYTE2(v19) = *((_BYTE *)v2 - 14);
            LOWORD(v19) = *((_WORD *)v2 - 8);
          }
          HIBYTE(v19) = *((_BYTE *)v2 - 13);
          v14 = v19;
LABEL_14:
          v13->curColor.Color = v14;
          ((void ( *)(float *, _DWORD, _DWORD, int, int))v13->pGfxMgr->DrvInfo.subtype)(
            v2 - 68,
            *((_DWORD *)v2 - 3),
            *((_DWORD *)v2 - 2),
            1176256512,
            1176256512);
          break;
        default:
          break;
      }
      v2 += 70;
      ++v20;
    }
    while ( v20 < (int)this->m_pCamControl );
  }
  ((void ( *)(gbPrintFont *))gfxMgr->pFontMgr->pAllFont[1]->pGfxMgr->hGfxWnd)(gfxMgr->pFontMgr->pAllFont[1]);
  ((void ( *)(gbPrintFont *))gfxMgr->pFontMgr->pAllFont[2]->pGfxMgr->hGfxWnd)(gfxMgr->pFontMgr->pAllFont[2]);
  ((void ( *)(gbPrintFont *))gfxMgr->pFontMgr->pAllFont[3]->pGfxMgr->hGfxWnd)(gfxMgr->pFontMgr->pAllFont[3]);
  m_pCam_high = HIBYTE(this->m_pCam);
  this->m_pCamControl = 0;
  if ( m_pCam_high > 1u )

}

// 0x004DFA10
int CCBStage::CountActiveActions()
{
  int v2; // ebx
  int result; // eax
  float *p_fTemp4; // esi
  void *v5; // edx
  CCBRoleState *m_pRoleState; // eax
  unsigned int v7; // [esp+0x10] [ebp-0x4]

  v2 = 0;
  result = (int)this->m_pCamControl;
  if ( result > 0 )
  {
    p_fTemp4 = &this->m_Task[0].SubTask[0].fTemp4;
    do
    {
      if ( *((_DWORD *)p_fTemp4 - 66) == 5 )
      {
        *(unsigned int *)((char *)&this->m_pRoleState->m_Role[1].dwSkillID[8] + 1) = (unsigned int)p_fTemp4[3];
        v5 = (void *)*((_DWORD *)p_fTemp4 + 1);
        v7 = *((_DWORD *)p_fTemp4 + 2);
        m_pRoleState = this->m_pRoleState;
        *(unsigned int *)((char *)&m_pRoleState->m_Role[1].dwSkillID[2] + 1) = *(unsigned int *)p_fTemp4;
        m_pRoleState = (CCBRoleState *)((char *)m_pRoleState + 888);
// [VFTABLE] m_pRoleState->_embed_UIFrameWnd_168.__vftable = v5;
        m_pRoleState->_embed_UIFrameWnd_168.m_fontcolor.Color = v7;
        ((CCBStageScene *)this->m_pRoleState)->LoadPointer(*((_BYTE *)p_fTemp4 - 1));
      }
      else if ( *((_DWORD *)p_fTemp4 - 66) == 6 )
      {
        sub_5110B0(*((_BYTE *)p_fTemp4 - 1));
      }
      result = (int)this->m_pCamControl;
      ++v2;
      p_fTemp4 += 70;
    }
    while ( v2 < result );
  }
  return result;
}

// 0x004DFAA0
int CCBStage::InitRound()
{
  int result; // eax
  const char *v2; // [esp+0x10] [ebp+0x4]
  float v3; // [esp+0x14] [ebp+0x8]
  char *v4; // [esp+0x18] [ebp+0xC]
  int v5; // [esp+0x1C] [ebp+0x10]

  strcpy((char *)&this->m_pRole[70 * (int)this->m_pCamControl], v2);
  *(&this->m_Task[0].SubTask[0].fTemp4 + 70 * (int)this->m_pCamControl) = v3;
  this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl] = v4;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 1;
  this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl + 2] = (char *)1103101952;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT + 1)) = v5;
  result = (int)&this->m_pCamControl->m_CCT + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFB70
int CCBStage::UpdateTurnFlags(const char *pszName, float fVal, float fVal2, float fVal3)
{
  int result; // eax

  strcpy((char *)&this->m_pRole[70 * (int)this->m_pCamControl], pszName);
  *(&this->m_Task[0].SubTask[0].fTemp4 + 70 * (int)this->m_pCamControl) = fVal;
  *(float *)&this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl] = fVal2;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 1;
  *(float *)&this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl + 2] = fVal3;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT + 1)) = this->m_pEditor;
  result = (int)&this->m_pCamControl->m_CCT + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFC40
int CCBStage::InitSlotFlags(const char *pszName, int nVal, int nVal2, int nVal3)
{
  int result; // eax

  strcpy((char *)&this->m_pRole[70 * (int)this->m_pCamControl], pszName);
  *(&this->m_Task[0].SubTask[0].fTemp4 + 70 * (int)this->m_pCamControl) = ((double)nVal + (double)nVal)
                                                                        / (double)g_DrvInfo.width
                                                                        - 1.0;
  *(float *)&this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl] = 1.0
                                                                          - ((double)nVal2 + (double)nVal2)
                                                                          / (double)g_DrvInfo.height;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 1;
  this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl + 2] = (char *)1098907648;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT + 1)) = nVal3;
  result = (int)&this->m_pCamControl->m_CCT + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFE00
int CCBStage::AddTextLabel(int nVal, int nVal2)
{
  int result; // eax
  int v5; // [esp+0x10] [ebp+0xC]
  int v6; // [esp+0x14] [ebp+0x10]

  sprintf((char *const)&this->m_pRole[70 * (int)this->m_pCamControl], &dir[20], v5);
  *(&this->m_Task[0].SubTask[0].fTemp4 + 70 * (int)this->m_pCamControl) = ((double)nVal + (double)nVal)
                                                                        / (double)g_DrvInfo.width
                                                                        - 1.0;
  *(float *)&this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl] = 1.0
                                                                          - ((double)nVal2 + (double)nVal2)
                                                                          / (double)g_DrvInfo.height;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 2;
  this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl + 2] = (char *)1094713344;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT + 1)) = v6;
  result = (int)&this->m_pCamControl->m_CCT + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFED0
int CCBStage::EndTurnAndAdvance()
{
  int result; // eax
  float v2; // [esp+0x4] [ebp+0x4]
  char *v3; // [esp+0x8] [ebp+0x8]
  char *v4; // [esp+0xC] [ebp+0xC]
  char *v5; // [esp+0x10] [ebp+0x10]
  char v6; // [esp+0x14] [ebp+0x14]

  *(&this->m_Task[0].SubTask[0].fTemp4 + 70 * (int)this->m_pCamControl) = v2;
  this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl] = v3;
  this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl + 1] = v4;
  this->m_Task[0].SubTask[1].fp[70 * (int)this->m_pCamControl + 2] = v5;
  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 5;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT + 1)) = this->m_pEditor;
  *((_BYTE *)&this->m_Task[0].SubTask[0].fTemp3 + 280 * (int)this->m_pCamControl + 3) = v6;
  result = (int)&this->m_pCamControl->m_CCT + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFF90
int CCBStage::AssignSlotData(char pData)
{
  int result; // eax

  *((_DWORD *)&this->m_pScene + 70 * (int)this->m_pCamControl) = 6;
  *((_DWORD *)&this->m_pCBSystem + 70 * ((int)&this->m_pCamControl->m_CCT + 1)) = this->m_pEditor;
  *((_BYTE *)&this->m_Task[0].SubTask[0].fTemp3 + 280 * (int)this->m_pCamControl + 3) = pData;
  result = (int)&this->m_pCamControl->m_CCT + 1;
  this->m_pCamControl = (CCBCamControl *)result;
  return result;
}

// 0x004DFFF0
__int64 CCBStage::CalculateTurnOrder(float fVal, int nVal)
{
  __int64 result; // rax

  this->m_pCam = (CCBStageCam *)nVal;
  result = (__int64)fVal;
  HIBYTE(this->m_pCam) = result;
  return result;
}

// 0x004E0010
void CCBStage::SetupCamControl()
{
  _BYTE v1[4]; // [esp+0x4] [ebp-0x10] BYREF
  int v2; // [esp+0x10] [ebp-0x4]

  PushMatrixStacks(v1);
  v2 = 0;
  crt_sub_00540070();
  v2 = -1;
  PopMatrixStacks(v1);
}

// 0x004E02F0
int * CCBStage::ResetAndSetSystem(int nVal)
{
  memset(this, 0, 0x2598u);

  this->m_pCBSystem = (CCBSystem *)nVal;
  this->m_pRoleState = 0;
  g_RoleSystemCombat.dwInitParam = 0;
  hDlg = 0;
  g_hMainWnd = 0;
  g_RoleSystemCombat.m_teamSlots[263] = (int)this;
  return (int *)this;
}

// 0x004E0330
int CCBStage::Reset()
{
  memset(this, 0, 0x2598u);
  return 0;
}

// 0x004E0340
int CCBStage::ResetTurnSlots()
{
  this->m_Task[2].cmd.nDestRole = -1;
  *(_DWORD *)&this->m_Task[2].cmd.bMultiSrcRole = -1;
  *(_DWORD *)&this->m_Task[2].cmd.bSrcRole[2] = -1;
  *(_DWORD *)&this->m_Task[2].cmd.bSrcRole[6] = -1;
  *(_DWORD *)&this->m_Task[2].cmd.bSrcRole[10] = -1;
  *(_DWORD *)&this->m_Task[2].cmd.bDestRole[3] = -1;
  *(_DWORD *)&this->m_Task[2].cmd.bDestRole[7] = -1;
  this->m_Task[3].SubTask[18].fTemp3 = NAN;
  this->m_Task[3].SubTask[18].fTemp4 = NAN;
  return -1;
}

// 0x004E0380
char CCBStage::SyncTimeScale()
{

  *(float *)&g_RoleSystemCombat.m_teamSlotsB[4] = this->m_pCBSystem->m_fTimeScale;
  if ( g_bTestCombat )
  {
    hDlg = CreateDialogParamA(hInstance, (LPCSTR)0x66, hWnd, DialogFunc, 0);
    g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x6A, hWnd, (DLGPROC)CCBUI::CloseDialog, 0);
  }
  return 1;
}

// 0x004E03F0
char CCBStage::DestroyDialog()
{
  if ( hDlg )
  {
    DestroyWindow(hDlg);
    hDlg = 0;
  }
  if ( g_hMainWnd )
  {
    DestroyWindow(g_hMainWnd);
    g_hMainWnd = 0;
  }
  return 1;
}

// 0x004E0430
char CCBStage::CreatePreviewDialog()
{
  CCBSystem *m_pCBSystem; // eax
  HWND DlgItem; // eax

  m_pCBSystem = this->m_pCBSystem;
  this->m_pRoleState = this->m_pCBSystem->m_pRoleState;
  if ( BYTE1(m_pCBSystem->m_nTimesOfCombat) )
  {
    ShowWindow(hDlg, 4);
    ShowWindow(g_hMainWnd, 4);
  }
  BYTE2(g_RoleSystemCombat.m_nCCBUISelectedRole) = 0;
  ((PAL_GDB *)this)->LoadConfigFromINI();
  DlgItem = GetDlgItem(hDlg, 1006);
  SendMessageA(DlgItem, 0xF5u, 0, 0);
  ((CCBRoleState *)this)->UpdateDebugTreeView();
  ((CCBRoleState *)this)->HandleDlgMessage();
  SetActiveWindow(hWnd);
  return 1;
}

// 0x004E0530
bool CCBStage::ProcessAction(HWND pData)
{
  if ( !pData )
    return 0;
  if ( pData == hWnd )
    return 1;
  if ( pData == hDlg )
    return 1;
  if ( pData == g_hMainWnd )
    return 1;
  if ( pData == g_RoleSystemCombat.g_hCombatDlg1 )
    return 1;
  if ( pData == g_RoleSystemCombat.g_hCombatDlg2 )
    return 1;
  if ( pData == (HWND)g_RoleSystemCombat.m_nActorRenderCount )
    return 1;
  if ( pData == g_RoleSystemCombat.g_hCBStageCamDlg )
    return 1;
  return pData == *(HWND *)&g_RoleSystemCombat.m_bWPARAM_17A9926;
}

// 0x004E05B0
void CCBStage::CreatePreview(float fVal)
{
  HWND DlgItem; // edi
  HWND v2; // esi

  if ( *(float *)&g_RoleSystemCombat.m_teamSlotsB[4] != fVal )
  {
    *(float *)&g_RoleSystemCombat.m_teamSlotsB[4] = fVal;
    DlgItem = GetDlgItem(hDlg, 1001);
    v2 = GetDlgItem(hDlg, 1003);
    SendMessageA(DlgItem, 0x405u, 1u, (__int64)(100.0 * *(float *)&g_RoleSystemCombat.m_teamSlotsB[4]));
    sprintf(
      (char *const)&g_RoleSystemCombat.m_StaticSlotArray.m_bfocus,
      "Speed%1.2f",
      *(float *)&g_RoleSystemCombat.m_teamSlotsB[4]);
    SendMessageA(v2, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_StaticSlotArray.m_bfocus);
  }
}

// 0x004E0650
BOOL CCBStage::DestroyPreviewWindow()
{
  if ( g_RoleSystemCombat.g_hCBStageCamDlg )
    DestroyWindow(g_RoleSystemCombat.g_hCBStageCamDlg);
  g_RoleSystemCombat.g_hCBStageCamDlg = CreateDialogParamA(
                                          hInstance,
                                          (LPCSTR)0x6F,
                                          hWnd,
                                          (DLGPROC)PAL_GDB::PartySetupDialogProc,
                                          0);
  return ShowWindow(g_RoleSystemCombat.g_hCBStageCamDlg, 5);
}

// 0x004F06C0
bool CCBStage::FindThreadByParam(int nVal, unsigned int dwVal)
{
  if ( !nVal )
    return 0;
  if ( *(_DWORD *)(nVal + 12) == dwVal )
    return 1;
  return dwVal <= 0xA && *(_BYTE *)(nVal + dwVal + 29);
}

// 0x004F4AA0
CCBStageRole * CCBStage::GetRole(int index)
{
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int *i; // eax
  int RoleNum; // eax
  int pCmd[11]; // [esp+0xC] [ebp-0x2C] BYREF
  int nVal; // [esp+0x40] [ebp+0x8]

  memset(pCmd, 0, sizeof(pCmd));
  v3 = ((CCBRoleState *)this)->GetRoleHP(index) - 1;
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)&this->m_Task[0].SubTask[4].fStartTime + 223 * index));
      v4 = 0;
      for ( i = (int *)(v5 + 760); nVal != *i; ++i )
      {
        if ( ++v4 >= 4 )
          return 0;
      }
      RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*i);
      return (CCBStageRole *)*(__int16 *)(RoleNum + 592);
    }
    return 0;
  }
  pCmd[2] = index;
  pCmd[0] = 261;
  pCmd[1] = nVal;
  LOBYTE(pCmd[10]) = 1;
  if ( !((CCBRoleState *)this)->ValidateCommandTarget(pCmd) )
  {
    pCmd[0] = 260;
    if ( !((CCBRoleState *)this)->ValidateCommandTarget(pCmd) )
      return 0;
  }
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nVal);
  return (CCBStageRole *)*(__int16 *)(RoleNum + 592);
}

// 0x004F6CD0
char CCBStage::CheckGDBTypeCompat(unsigned int *pdwVal)
{
  unsigned int v2; // eax

  v2 = *pdwVal;
  if ( *pdwVal >= 0x104 )
  {
    if ( v2 <= 0x105 )
    {
      if ( *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(pdwVal[1]) + 666) == 2 )
        return 1;
    }
    else if ( v2 == 262 && *(_WORD *)(((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(pdwVal[1]) + 748) == 2 )
    {
      return 1;
    }
  }
  return 0;
}

// 0x004FB9A0
CCBStage::CCBStage(int pCBSystem)
{
  float *p_fTemp1; // edx
  int v3; // esi
  float *v4; // edi

  p_fTemp1 = &this->m_Task[0].SubTask[31].fTemp1;
  v3 = 256;
  do
  {
    v4 = p_fTemp1;
    p_fTemp1 += 658;
    --v3;
    memset(v4, 0, 0x2Cu);
  }
  while ( v3 );
  memset(this, 0, 0xA48B0u);
  this->m_pCBSystem = (CCBSystem *)pCBSystem;
  this->m_pRoleState = *(CCBRoleState **)(pCBSystem + 16);
  (int *)this;
}

// 0x004FB9F0
unsigned int CCBStage::_CCBStage()
{
  Actor **p_m_WPXVariance; // ecx
  unsigned int result; // eax

  p_m_WPXVariance = &this->m_WPXVariance;
  *p_m_WPXVariance = 0;
  p_m_WPXVariance[1] = 0;
  this->m_nStageStatus = 0;
  this->m_nTaskCount = 0;
  memset(&this->m_nForceDelTask, 0, 0xA4800u);
  this->m_nClearRoleAllTask = -1;
  this->m_nRoleSlot = -1;
  this->m_pShadow = (CCBStageShadow *)-1;
  this->m_pEffect = 0;
  this->m_BFARole = 0;
  LOWORD(this->m_BFARound) = 0;
  BYTE2(this->m_BFARound) = 0;
  memset(&this->m_ptMousePos, 0, 0x2Cu);
  this->_todo_094 = 0;
  result = gbCrc32Compute("over");
  *(_DWORD *)&this->m_Task[255].cmd.bSrcRole[6] = result;
  return result;
}

// 0x004FBE50
bool CCBStage::Create()
{
  int v2; // ebp
  CCBStageScene *m_pScene; // ecx
  CCBStageScene *v4; // edi
  CCBStageRole **i; // edi
  CCBStageRole *v6; // ebx
  std::codecvt_base *m_pCam; // ecx
  CCBStageCam *v8; // ecx
  CCBCamControl *m_pCamControl; // ecx
  CCBCamControl *v10; // edi
  std::codecvt_base *m_TempStorageNGH; // ecx
  Actor *v12; // edi
  Actor *m_NGHVariance; // ecx
  Actor *v14; // edi
  Actor *m_TempStorageWPX; // ecx
  Actor *v16; // edi
  void *v18; // [esp+0x0] [ebp-0x10]

  v2 = 0;
  m_pScene = this->m_pScene;
  if ( m_pScene )
  {
    ((CCBStageScene *)m_pScene)->_CCBStageScene();
    v4 = this->m_pScene;
    if ( v4 )
    {
      todo_408BD0(v18);
      operator delete(v4);
    }
    this->m_pScene = 0;
    for ( i = this->m_pRole; *i; ++i )
    {
      ((CCBStageRole *)*i)->IsAtInitPos();
      v6 = *i;
      if ( *i )
      {
        todo_408BD0(v18);
        operator delete(v6);
      }
      *i = 0;
      if ( ++v2 >= 11 )
      {
        m_pCam = (std::codecvt_base *)this->m_pCam;
        if ( m_pCam )
        {
          ((std *)m_pCam)->codecvt_base::do_always_noconv();
          v8 = this->m_pCam;
          if ( v8 )
            (*(void ( **)(CCBStageCam *, int))LODWORD(v8->fov))(v8, 1);
          this->m_pCam = 0;
          m_pCamControl = this->m_pCamControl;
          if ( m_pCamControl )
          {
            ((CCBCamControl *)m_pCamControl)->Init();
            v10 = this->m_pCamControl;
            if ( v10 )
            {
              ((j_j_codecvt_base *)this->m_pCamControl)->do_always_noconv();
              operator delete(v10);
            }
            this->m_pCamControl = 0;
            m_TempStorageNGH = (std::codecvt_base *)this->m_TempStorageNGH;
            if ( m_TempStorageNGH )
            {
              ((std *)m_TempStorageNGH)->codecvt_base::do_always_noconv();
              v12 = this->m_TempStorageNGH;
              if ( v12 )
              {
                todo_408BD0(v18);
                operator delete(v12);
              }
              this->m_TempStorageNGH = 0;
              m_NGHVariance = this->m_NGHVariance;
              if ( m_NGHVariance )
              {
                ((CCBStageShadow *)m_NGHVariance)->_CCBStageShadow();
                v14 = this->m_NGHVariance;
                if ( v14 )
                {
                  todo_408BD0(v18);
                  operator delete(v14);
                }
                this->m_NGHVariance = 0;
                m_TempStorageWPX = this->m_TempStorageWPX;
                if ( m_TempStorageWPX )
                {
                  ((CCBCamControl *)m_TempStorageWPX)->DoList();
                  v16 = this->m_TempStorageWPX;
                  if ( v16 )
                  {
                    sub_508460(this->m_TempStorageWPX);
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
bool CCBStage::Destroy()
{
  CCBStageScene *m_pScene; // ecx
  char v3; // al
  int v5; // ebx
  int v6; // edi
  CCBStageRole **m_pRole; // esi
  CCBStageRole *v8; // ecx
  CCBStageCam *m_pCam; // ecx
  CCBCamControl *m_pCamControl; // ecx
  char v11; // al
  Actor *m_NGHVariance; // ecx
  char v13; // al
  Actor *m_TempStorageWPX; // ecx
  char v15; // al
  Actor *m_TempStorageNGH; // ecx

  this->m_pEditor = this->m_pCBSystem->m_pEditor;
  m_pScene = this->m_pScene;
  if ( !m_pScene )
    return 0;
  ((CCBStageScene *)m_pScene)->Reset();
  if ( !v3 )
    return 0;
  v5 = 0;
  v6 = 0;
  m_pRole = this->m_pRole;
  do
  {
    if ( !*m_pRole )
      return 0;
    ((CCBStageRole *)*m_pRole)->GetRotAngle();
    v8 = *m_pRole;
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v6 + 4] )
    {
      if ( !((CCBStageRole *)v8)->IsAtProtectPos(v5, 0, 0) )
        return 0;
    }
    else if ( !((CCBStageRole *)v8)->IsAtProtectPos(v5, 0, 0) )
    {
      return 0;
    }
    v6 += 892;
    ++v5;
    ++m_pRole;
  }
  while ( v6 < 9812 );
  m_pCam = this->m_pCam;
  if ( !m_pCam || !((CameraCtrl *)m_pCam)->InitFromScreen() )
    return 0;
  m_pCamControl = this->m_pCamControl;
  if ( !m_pCamControl )
    return 0;
  ((CCBStageCam *)m_pCamControl)->Update();
  if ( !v11 )
    return 0;
  m_NGHVariance = this->m_NGHVariance;
  if ( !m_NGHVariance )
    return 0;
  ((CCBStageShadow *)m_NGHVariance)->Reset();
  if ( !v13 )
    return 0;
  m_TempStorageWPX = this->m_TempStorageWPX;
  if ( !m_TempStorageWPX )
    return 0;
  ((CCBCamControl *)m_TempStorageWPX)->ResetListFlag();
  if ( !v15 )
    return 0;
  m_TempStorageNGH = this->m_TempStorageNGH;
  if ( !m_TempStorageNGH || !((CCBStage *)m_TempStorageNGH)->IsInitialized() )
    return 0;
  ((CCBStage *)this->m_TempStorageNGH)->CalculateTurnOrder(0.0, 0);
  return 1;
}

// 0x004FC0A0
void CCBStage::Update()
{
  void *v1; // esi
  CCBStageRole **m_pRole; // esi
  int v4; // ebx
  int *v5; // eax
  float effect; // [esp+0x0] [ebp-0x10]
  void *v7; // [esp+0x4] [ebp-0xC]
  void *v8; // [esp+0x4] [ebp-0xC]
  BOOL v9; // [esp+0x8] [ebp-0x8]

  if ( this->m_nStageStatus != 1 )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    ((CCBStageScene *)this->m_pScene)->SetBattleFieldAttr();
    if ( g_RoleSystemCombat.dwInitParam == (HWND)1 )
    {
    }
    else

    v7 = v1;
    m_pRole = this->m_pRole;
    v4 = 11;
    do
    {
      if ( (*m_pRole)->m_bValid )
        ((CCBStageRole *)*m_pRole)->IsTaskFinished((int)v7, v9);
      ++m_pRole;
      --v4;
    }
    while ( v4 );
    ((CCBStage *)this->m_pCam)->ProcessTurn();
    ((CCBCamControl *)this->m_pCamControl)->DoTask();
    todo_408BD0(v7);
    todo_408BD0(v8);

    effect = this->m_pCBSystem->m_DeltaTime;
    v5 = ((CEffectSystem *)this->m_pCBSystem)->DestroyAllEffect();
    ((CEffectSystem *)v5)->SetVisible(effect);
  }
}

// 0x004FC150
int CCBStage::Update_c150()
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
  float v13; // [esp+0x1C] [ebp-0x7C]
  float v14; // [esp+0x20] [ebp-0x78]
  float v15; // [esp+0x24] [ebp-0x74]
  int pOut; // [esp+0x30] [ebp-0x68] BYREF
  int pOut2; // [esp+0x34] [ebp-0x64] BYREF
  float pPos; // [esp+0x38] [ebp-0x60] BYREF
  float y; // [esp+0x3C] [ebp-0x5C]
  int v20; // [esp+0x40] [ebp-0x58]
  float v21; // [esp+0x44] [ebp-0x54] BYREF
  float v22; // [esp+0x48] [ebp-0x50]
  int v23; // [esp+0x4C] [ebp-0x4C]
  struct gbVec3D v24; // [esp+0x50] [ebp-0x48] BYREF
  struct gbVec3D v25; // [esp+0x5C] [ebp-0x3C] BYREF
  gbVec3D pTarget[2]; // [esp+0x68] [ebp-0x30] BYREF
  gbRay v27; // [esp+0x80] [ebp-0x18] BYREF

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
  m_pDisplayChain = this->m_pDisplayChain;
  pPos = *(float *)&this->m_WPXVariance;
  y = *(float *)&m_pDisplayChain;
  m_pCam = this->m_pCam;
  pOut = 0;
  pOut2 = 0;
  ViewTarget = (char *)((CameraCtrl *)m_pCam)->GetViewTarget(pTarget, &pPos);
  ((gbVec3D *)&v27)->operator=(ViewTarget);
  ((gbVec3D *)&v27.Direction)->operator=(ViewTarget + 12);
  v5 = ((gbRay *)&v27)->IntersectPlane(v25, v24);
  pPos = v27.Direction.x * v5;
  y = v27.Direction.y * v5;
  v15 = v27.Origin.z + v5 * v27.Direction.z;
  v14 = v27.Origin.y + y;
  v13 = pPos + v27.Origin.x;
  // [AUTO-COMMENTED] v6 = ((gbVec3D *)pTarget)->gbVec3D(v13, v14, v15);
  pPos = v6->x;
  y = v6->y;
  z_low = LODWORD(v6->z);
  v21 = pPos;
  v20 = z_low;
  v23 = z_low;
  m_pShadow = this->m_pShadow;
  v22 = y;
  if ( m_pShadow != (CCBStageShadow *)-1 )
  {
    ((gbVec3D *)&this->m_pRole[(_DWORD)m_pShadow]->m_Task[62].eMode)->operator=(&v21);
    v9 = this->m_pRole[(int)this->m_pShadow];
    v9->m_Task[62].fTemp = v21;
    v9 = (CCBStageRole *)((char *)v9 + 6584);
    *(float *)&v9->m_pRoleState = v22;
    *(_DWORD *)v9->m_sLastRole = v23;
  }
  result = (int)this->m_pScene;
  if ( *(_BYTE *)(result + 964) )
  {
    if ( (g_Input.KeyInfo[15].Data & 0xF) == 1 )
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
      this->m_pScene->m_vecFiveLineupPos.x = (double)pOut2 * 0.016666668 + this->m_pScene->m_vecFiveLineupPos.x;
    }
  }
  return result;
}

// 0x004FC3A0
int CCBStage::EditorUpdate(int a2)
{
  int v3; // ebp
  CCBStageCam *m_pCam; // eax
  float *p_OrthoSize; // eax
  int *v6; // eax
  CCBStageCam *v7; // eax
  gbSceneGraph *pSceneGraph; // ebx
  gbCamera *v9; // eax
  gbMatrixStack *v10; // edi
  char *v11; // eax
  CCBStageRole **v12; // eax
  CCBStageRole *v13; // ecx
  long double v14; // st7
  bool v15; // cc
  CCBStageCam *v16; // eax
  gbCamera *v17; // eax
  CCBStageScene *m_pScene; // ecx
  CCBStageScene *v19; // ecx
  CEffectSystem *v20; // ecx
  int *v21; // eax
  gbRenderEffect *v23; // [esp+0x18] [ebp-0x3C]
  float v24; // [esp+0x20] [ebp-0x34]
  CCBStageRole **m_pRole; // [esp+0x38] [ebp-0x1C] BYREF
  float v26; // [esp+0x3C] [ebp-0x18]
  CCBStageRole **v27; // [esp+0x40] [ebp-0x14]
  gbVec3D dwMsg; // [esp+0x48] [ebp-0xC] BYREF

  v3 = 0;
  gfxMgr->fSelfIllum = 0.0;
  m_pCam = this->m_pCam;
  if ( m_pCam )
    p_OrthoSize = &m_pCam->OrthoSize;
  else
    p_OrthoSize = 0;
  v23 = (gbRenderEffect *)p_OrthoSize;
  v6 = ((CEffectSystem *)this)->DestroyAllEffect();
  ((CEffectSystem *)v6)->HandleViewMove(v23, a2);
  v7 = this->m_pCam;
  pSceneGraph = gfxMgr->pSceneGraph;
  if ( v7 )
    v9 = (gbCamera *)&v7->OrthoSize;
  else
    v9 = 0;
  ((gbSceneGraph *)pSceneGraph)->Begin(v9);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v10 = gfxMgr->pMatrixStack[1];
  ((CameraCtrl *)this->m_pCam)->SetAsCurrent(3);
  ((gbMatrixStack *)v10)->Push();
  ((void (*)(gbActor **, _DWORD))this->m_TempStorageWPX->m_pact->children.m_Tail)(
    &this->m_TempStorageWPX->m_pact,
    0);
  if ( !HIBYTE(this->m_BFARound) )
  {
    ((CCBStageScene *)this->m_pScene)->GetBattleFieldSubdueAttr(v10);
    m_pRole = this->m_pRole;
    do
    {
      if ( g_RoleSystemCombat.dwInitParam == (HWND)1
        || (v11 = &this->m_pRoleState->m_sCombatDialog[v3], v11[577]) && !v11[1432] )
      {
        ((CCBStageRole *)*m_pRole)->IsDoTask(v10);
      }
      v3 += 892;
      ++m_pRole;
    }
    while ( v3 < 9812 );
    v12 = this->m_pRole;
    m_pRole = 0;
    v27 = this->m_pRole;
    do
    {
      v13 = *v12;
      if ( (*v12)->m_bShowWeapon )
      {
        memset(&dwMsg, 0, sizeof(dwMsg));
        ((CCBStageRole *)v13)->DoTask(&dwMsg);
        v14 = sin(this->m_pCBSystem->m_fTimeFund * 10.0 + (double)(int)m_pRole);
        v26 = v14;
        dwMsg.y = v14 * 5.0 + dwMsg.y + 6.0;
        ((gbMatrixStack *)v10)->Push();
        ((gbMatrixStack *)v10)->Translate(dwMsg.x,   dwMsg.y,   dwMsg.z);
        v24 = v26 * 0.2 + 1.0;
        ((gbMatrixStack *)v10)->Scale(1.0,   v24,   1.0);
        (*(void (**)(gbGeomNode *, _DWORD))(*(_DWORD *)this->m_pScene->m_pPointer + 16))(
          this->m_pScene->m_pPointer,
          0);
        ((gbMatrixStack *)v10)->Pop();
      }
      v12 = v27 + 1;
      v15 = (int)m_pRole + 1 < 5;
      m_pRole = (CCBStageRole **)((char *)m_pRole + 1);
      ++v27;
    }
    while ( v15 );
  }
  ((SceneMgr *)this->m_pCBSystem->m_pEffMgr)->RenderUpdate();
  ((SceneMgr *)this->m_pCBSystem->m_pATSEffMgr)->RenderUpdate();
  ((gbMatrixStack *)v10)->Pop();
  ((gbSceneGraph *)pSceneGraph)->End();
  ((CCBStageShadow *)this->m_NGHVariance)->Create();
  v16 = this->m_pCam;
  if ( v16 )
    v17 = (gbCamera *)&v16->OrthoSize;
  else
    v17 = 0;
  ((gbSceneGraph *)pSceneGraph)->Begin(v17);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  ((void (*)(gbActor **, _DWORD))this->m_TempStorageWPX->m_pact->children.m_Tail)(
    &this->m_TempStorageWPX->m_pact,
    0);
  (*(void (**)(gbVisNode *, _DWORD))(*(_DWORD *)this->m_pScene->m_pLights + 16))(
    this->m_pScene->m_pLights,
    0);
  ((SceneMgr *)this->m_pCBSystem->m_pEffMgr)->RenderAll();
  ((SceneMgr *)this->m_pCBSystem->m_pATSEffMgr)->RenderAll();
  ((C3DSpark *)this->m_pCBSystem->m_p3DSpark)->Render((gbVec3D *)gbSceneGraph::End);
  ((gbSceneGraph *)pSceneGraph)->End();
  if ( HIBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) )
  {
    ((CCBStageScene *)this->m_pScene)->IsSameBattleFieldAttr();
    ((CCBStageScene *)this->m_pScene)->GetBFASubdueFM();
  }
  if ( BYTE1(this->m_pCBSystem->m_nTimesOfCombat) )
  {
    if ( g_RoleSystemCombat.dwInitParam == (HWND)1 )
    {
      m_pScene = this->m_pScene;
      if ( !HIBYTE(m_pScene->m_vecEnemyFiveLineupPos.x) )
        goto LABEL_31;
      ((CCBStageScene *)m_pScene)->LoadPointer(60);
    }
    if ( g_RoleSystemCombat.dwInitParam == (HWND)4 )
    {
      v19 = this->m_pScene;
      if ( HIBYTE(v19->m_vecEnemyFiveLineupPos.x) )
        ((CCBStageScene *)v19)->LoadPointer(60);
      ((CCCTData *)this->m_pCamControl)->_CCCTData();
    }
  }
LABEL_31:
  ((CCBStage *)this->m_TempStorageNGH)->CountActiveActions();
  v21 = ((CEffectSystem *)v20)->DestroyAllEffect();
  ((CEffectSystem *)v21)->Update();
  ((CCBStage *)g_pEffectSystem)->GetReadyCount();
  PushMatrixStacks(&m_pRole);
  dwMsg.z = 0.0;
  ((CGameData *)&g_gamefrm)->ProcessDialog();
  ((CCBStage *)this->m_TempStorageNGH)->ResetRoundState();
  if ( !g_bEditorMode )
    ((Logger *)&g_InputState)->Render();
  dwMsg.z = NAN;
  return PopMatrixStacks(&m_pRole);
}

// 0x004FC6F0
// attributes: thunk
void CCBStage::Render()
{

}

// 0x004FC700
int CCBStage::GetRoleIndex(int nameCrc, const void *pData, char a4)
{
  int v5; // ebp
  _BYTE *i; // eax
  char *v8; // edi

  if ( this->m_nTaskCount >= 246 )
    ((CCBSystem *)this->m_pCBSystem)->CreateObj(&dword_5DB6C4, 0, 0x30u);
  v5 = 0;
  for ( i = &this->m_Task[0].cmd.bSrcRole[2]; *i; i += 2632 )
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
  *((_DWORD *)v8 + 42) = nameCrc;
  *((_DWORD *)v8 + 687) = 0;
  if ( pData )
    qmemcpy(v8 + 2752, pData, 0x2Cu);
  else
    *((_DWORD *)v8 + 690) = -1;
  ++this->m_nTaskCount;
  return v5;
}

// 0x004FC7D0
int CCBStage::GetRoleName(
        
        int nameCrc,
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int *p_DWORD,
        int nVal5,
        int nVal6)
{
  int v9; // ebp
  int v10; // ebx
  ECBStageTaskState *i; // eax
  int *v13; // esi
  int *v14; // esi

  v9 = 0;
  v10 = 2632 * nameCrc;
  for ( i = &this->m_Task[nameCrc].SubTask[0].eStats; *i; i += 80 )
  {
    if ( ++v9 >= 32 )
      return -1;
  }
  v13 = (int *)((char *)&this->m_nCurTask + 80 * v9 + v10);
  memset(v13, 0, 0x50u);
  *((_BYTE *)&this->m_Task[0].SubTask[v9].eStats + v10 + 1) = 0;
  *((_BYTE *)&this->m_Task[0].SubTask[v9].eStats + v10) = 1;
  *(int *)((char *)&this->m_Task[0].nSubTask + 80 * v9 + v10) = 2;
  *v13 = nVal;
  *(int *)((char *)&this->m_nCurSubTask + 80 * v9 + v10) = nVal2;
  *(_DWORD *)(&this->m_Task[0].eTask + 80 * v9 + v10) = nVal3;
  *(_DWORD *)(&this->m_Task[0].eStats + 80 * v9 + v10) = nVal4;
  v13[5] = ((CCBSystem *)this->m_pCBSystem)->ProcProtect();
  v13[7] = nVal5;
  v13[6] = 0;
  v13[8] = nVal6;
  if ( p_DWORD )
  {
    v14 = v13 + 11;
    *v14 = *p_DWORD;
    v14[1] = p_DWORD[1];
    v14[2] = p_DWORD[2];
  }
  ++*(_DWORD *)(&this->m_bPaused + v10);
  return v9;
}

// 0x004FC8B0
void CCBStage::Procced(int nVal)
{
  char *v2; // edx
  int v3; // ecx
  _BYTE *v4; // eax

  v2 = (char *)this + 2632 * nVal;
  v3 = 32;
  v4 = v2 + 227;
  do
  {
    if ( *(v4 - 3) )
      *v4 = 1;
    v4 += 80;
    --v3;
  }
  while ( v3 );
  v2[2797] = 1;
}

// 0x004FC8F0
char CCBStage::GetStageRole(int idx)
{
  char *v2; // esi

  v2 = (char *)this + 2632 * idx;
  v2[2796] = 0;
  memset(v2 + 184, 0, 0xA00u);
  *((_DWORD *)v2 + 44) = 0;
  --this->m_nTaskCount;
  return 1;
}

// 0x004FC940
char CCBStage::GetStageRoleByIdx(int idx)
{
  char *v2; // eax

  v2 = (char *)this + 2632 * idx;
  *((_DWORD *)v2 + 43) = 3;
  *((_DWORD *)v2 + 50) = 3;
  *((float *)v2 + 52) = this->m_pCBSystem->m_fTimeFund;
  return 1;
}

// 0x004FC980
bool CCBStage::IsDoTask(int eTask)
{
  return (_BYTE)this + 72 * eTask - 88;
}

// 0x004FC9A0
bool CCBStage::EndTask(int nIndex)
{
  return this->m_Task[nIndex].SubTask[31].nEffLinker;
}

// 0x004FC9C0
char * CCBStage::DelTask(int nIndex, _BYTE *p_BYTE, int *p_DWORD)
{
  char *result; // eax

  *p_BYTE = 0;
  *p_DWORD = 0;
  result = (char *)this + 2632 * nIndex;
  if ( *((_DWORD *)result + 43) == 4 )
  {
    *p_BYTE = 1;
    *p_DWORD = *((_DWORD *)result + 687);
  }
  return result;
}

// 0x004FCA00
bool CCBStage::ForceDelTask(int nIndex)
{
  _BYTE *p_m_nForceDelTask; // eax
  int v3; // edx

  p_m_nForceDelTask = &this->m_nForceDelTask;
  v3 = 0;
  while ( !p_m_nForceDelTask[2628] || nIndex != *(_DWORD *)p_m_nForceDelTask || *((_DWORD *)p_m_nForceDelTask + 1) == 4 )
  {
    ++v3;
    p_m_nForceDelTask += 2632;
    if ( v3 >= 256 )
      return 0;
  }
  return 1;
}

// 0x004FCA80
void CCBStage::GetTask()
{
  int v2; // ebx
  _BYTE *v3; // edi
  int v4; // ebp
  _BYTE *v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  unsigned int ( *v9)(CCBStage *, int); // ecx
  bool *v10; // [esp+0x0] [ebp-0x14]
  int v11; // [esp+0x4] [ebp-0x10]
  _BYTE *v12; // [esp+0x10] [ebp-0x4]

  v2 = 0;
  v3 = &this->m_Task[0].cmd.bSrcRole[2];
  v12 = &this->m_Task[0].cmd.bSrcRole[2];
  do
  {
    if ( *v3 == 1 && *((_DWORD *)v3 - 656) == 3 )
    {
      v4 = 0;
      v5 = v3 - 2676;
      do
      {
        if ( !v5[104] || v4 > 0 && *(_DWORD *)v5 == 2 )
          break;
        if ( *((_DWORD *)v5 + 20) == 2 )
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
                this->m_nClearRoleAllTask = v2;
                this->m_nRoleSlot = v4;
                (*((void ( **)(char *, _DWORD))v5 + 16))((char *)this + *((_DWORD *)v5 + 17), 0);
              }
            }
            else if ( *(_DWORD *)v5 == 4 )
            {
              goto LABEL_25;
            }
          }
        }
        else
        {
          if ( *((_DWORD *)v5 + 20) == 3 )
            goto LABEL_26;
          if ( *((_DWORD *)v5 + 20) == 4 && this->GetTaskState(v2, v10, v11) == 1 )
          {
            v6 = *((_DWORD *)v12 - 655);
            *((_DWORD *)v12 - 656) = 4;
            v6 *= 80;
            v7 = *(_DWORD *)&v12[v6 - 2656];
            v8 = (int)&v12[v6 - 2628];
            *((_DWORD *)v12 - 12) = v7;
            v9 = *(unsigned int ( **)(CCBStage *, int))(v8 - 64);
            if ( v9 == CCBStage::ProcFiveLienupFadeOut
              && (!v9 || !*(_DWORD *)(v8 - 60) && !*(_DWORD *)(v8 - 56) && !*(_DWORD *)(v8 - 52)) )
            {
              *((_DWORD *)v12 - 12) = *(_DWORD *)(v8 - 108);
            }
            if ( v12[1] == 1 )
            {
              this->GetStageRole(v2);
              break;
            }
          }
        }
        ++v4;
        v5 += 80;
      }
      while ( v4 < 32 );
    }
    ++v2;
    v3 = v12 + 2632;
    v12 += 2632;
  }
  while ( v2 < 256 );
}

// 0x004FCBD0
char CCBStage::GetTaskID(int nIndex, int nVal)
{
  char *v3; // eax

  v3 = (char *)this + 2632 * nIndex + 80 * nVal;
  *((_DWORD *)v3 + 50) = 3;
  *((float *)v3 + 52) = this->m_pCBSystem->m_fTimeFund;
  return 1;
}

// 0x004FCC10
char CCBStage::GetTaskState(int a2, bool *a3, int a4)
{
  int v4; // edx
  char *v5; // ecx
  int v6; // eax
  _DWORD *i; // ecx

  v4 = 0;
  v5 = (char *)this + 2632 * a2;
  v6 = *((_DWORD *)v5 + 44);
  if ( v6 <= 0 )
    return 1;
  for ( i = v5 + 200; *i == 4; i += 20 )
  {
    if ( ++v4 >= v6 )
      return 1;
  }
  return 0;
}

// 0x004FCC50
char CCBStage::GetTaskState(int a2, int a3)
{
  int v3; // ebx
  _BYTE *i; // edx
  int v5; // eax
  int v6; // esi
  _BYTE *v7; // eax
  int v8; // ecx

  v3 = 0;
  for ( i = &this->m_Task[0].cmd.bSrcRole[2]; ; i += 2632 )
  {
    if ( *i )
    {
      if ( *((_DWORD *)i - 656) != 4 && *((_DWORD *)i - 657) == 11 )
      {
        v5 = *((_DWORD *)i - 9);
        if ( v5 >= 5 && v5 < 11 )
          break;
      }
    }
LABEL_18:
    if ( ++v3 >= 256 )
      return 0;
  }
  v6 = 0;
  v7 = i - 2612;
  while ( 1 )
  {
    if ( *(void (**)(CCBStage *, int))v7 == CCBStage::HandleKeyCtrl
      && (!*(_DWORD *)v7 || !*((_DWORD *)v7 + 1) && !*((_DWORD *)v7 + 2) && !*((_DWORD *)v7 + 3)) )
    {
      if ( *((_DWORD *)v7 + 4) == 4 )
        goto LABEL_18;
      v8 = *((_DWORD *)i - 8);
      if ( v8 == a2 || v8 == -1 && i[a2 - 15] )
        return 1;
    }
    ++v6;
    v7 += 80;
    if ( v6 >= 32 )
      goto LABEL_18;
  }
}

// 0x004FCD00
bool CCBStage::IsTaskFinished(int nIndex)
{
  float *p_fTemp3; // edx
  int v4; // ebx
  bool result; // al

  ((CCBStageRole *)this->m_pRole[nIndex])->GetCurrentState();
  p_fTemp3 = &this->m_Task[0].SubTask[31].fTemp3;
  v4 = 256;
  do
  {
    result = *((_BYTE *)p_fTemp3 + 36);
    if ( result && *(_DWORD *)p_fTemp3 == nIndex )
    {
      result = 0;
      memset(p_fTemp3 - 648, 0, 0xA48u);
      --this->m_nTaskCount;
    }
    p_fTemp3 += 658;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCD50
unsigned __int8 * CCBStage::IsTaskValidButNotFinish(int eTask, int nVal)
{
  unsigned __int8 *v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // esi
  int v7; // ecx

  v5 = v4 + 2760;
  v6 = 256;
  do
  {
    LOBYTE(v3) = *(_BYTE *)(v5 + 36);
    if ( (_BYTE)v3 && *(unsigned __int8 **)v5 == result )
    {
      v3 = (unsigned __int8 *)(v5 - 2533);
      v7 = 32;
      do
      {
        if ( *(v3 - 3) )
          *v3 = 1;
        v3 += 80;
        --v7;
      }
      while ( v7 );
    }
    v5 += 2632;
    --v6;
  }
  while ( v6 );
  return v3;
}

// 0x004FCDA0
bool CCBStage::IsTaskExist(unsigned int dwTaskID)
{
  bool result; // al
  float *p_fTemp3; // ecx
  int v4; // edx

  result = 0;
  p_fTemp3 = &this->m_Task[0].SubTask[31].fTemp3;
  v4 = 256;
  do
  {
    if ( *((_BYTE *)p_fTemp3 + 36) && *(_DWORD *)p_fTemp3 == dwTaskID && *((_DWORD *)p_fTemp3 - 648) != 29 )
      ++result;
    p_fTemp3 += 658;
    --v4;
  }
  while ( v4 );
  return result;
}

// 0x004FCDE0
void CCBStage::DoTask(int nVal)
{
  if ( nVal == -1 )
    this->m_pShadow = (CCBStageShadow *)-1;
  else
    this->m_pShadow = (CCBStageShadow *)nVal;
}

// 0x004FCE00
bool CCBStage::StartSubTask(int n)
{
  int m_nRoleSlot; // eax
  char *v3; // esi
  char v5; // al

  m_nRoleSlot = this->m_nRoleSlot;
  v3 = (char *)&this->m_nCurTask + 2632 * this->m_nClearRoleAllTask + m_nRoleSlot * 80;
  if ( *((_BYTE *)&this->m_Task[this->m_nClearRoleAllTask].SubTask[m_nRoleSlot].eStats + 1) )
  {
    if ( *((_BYTE *)&this->m_Task[this->m_nClearRoleAllTask].SubTask[m_nRoleSlot].eStats + 3) == 1
      || this->m_pCBSystem->m_fTimeFund - *((float *)v3 + 6) >= *((float *)v3 + 8)
      || (((GRPinput *)&g_Input)->SetJoystickAbs(), v5) )
    {
      *((_DWORD *)v3 + 4) = 4;
    }
    return 0;
  }
  else
  {
    *((_BYTE *)&this->m_Task[this->m_nClearRoleAllTask].SubTask[m_nRoleSlot].eStats + 1) = 1;
    return 0;
  }
}

// 0x004FCE70
int CCBStage::IsSubTaskFinished(int a2, int a3)
{
  int v4; // ecx
  char *v5; // eax
  double v6; // st7
  int v7; // esi
  double v8; // st7
  unsigned int v9; // eax
  unsigned int v10; // ecx
  float v12; // [esp+0x1C] [ebp-0x8]
  float v13; // [esp+0x1C] [ebp-0x8]
  float v14; // [esp+0x20] [ebp-0x4]
  float v15; // [esp+0x20] [ebp-0x4]

  v4 = 329 * this->m_nClearRoleAllTask;
  v5 = (char *)this + 80 * this->m_nRoleSlot;
  v6 = *(float *)&v5[8 * v4 + 216] * 0.25;
  v7 = (int)&v5[8 * v4 + 184];
  v12 = v6;
  v14 = v6 * 3.0;
  if ( !v5[8 * v4 + 225] )
  {
    *(_DWORD *)&v5[8 * v4 + 248] = 0;
    v5[8 * v4 + 225] = 1;
  }
  ((CCBStage *)this->m_TempStorageNGH)->EndTurnAndAdvance();
  v8 = this->m_pCBSystem->m_fTimeFund - *(float *)(v7 + 24);
  if ( v8 >= v14 )
  {
    v13 = (1.0 - (v8 - v14) / v12) * 255.0;
    v10 = (int)v13;
    *(_DWORD *)(v7 + 64) = v10;
    v9 = v10 <= 0xFF ? v10 : 0;
  }
  else
  {
    v15 = v8 / v14 * 255.0;
    v9 = (int)v15;
    *(_DWORD *)(v7 + 64) = v9;
    if ( v9 > 0xFF )
      v9 = 255;
  }
  *(_DWORD *)(v7 + 64) = v9;
  if ( *(_BYTE *)(v7 + 43) == 1 || this->m_pCBSystem->m_fTimeFund - *(float *)(v7 + 24) >= *(float *)(v7 + 32) )
    *(_DWORD *)(v7 + 16) = 4;
  return 0;
}

// 0x004FCFB0
bool CCBStage::IsAllSubTaskFinished(int n)
{
  unsigned int v3; // ecx
  int m_nRoleSlot; // edx
  double v5; // st7
  float *v6; // esi
  double v7; // st7
  unsigned int v8; // eax
  unsigned int v9; // ecx
  float v11; // [esp+0x8] [ebp-0x8]
  float v12; // [esp+0x8] [ebp-0x8]
  float v13; // [esp+0xC] [ebp-0x4]
  float v14; // [esp+0xC] [ebp-0x4]

  v3 = 329 * this->m_nClearRoleAllTask;
  m_nRoleSlot = this->m_nRoleSlot;
  v5 = *(float *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].fp[2] * 0.25;
  v6 = (float *)((char *)&this->m_nCurTask + 8 * v3 + m_nRoleSlot * 80);
  v11 = v5;
  v13 = v5 * 3.0;
  if ( !*((_BYTE *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].eStats + 1) )
  {
    *(_DWORD *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].bValid = 0;
    *((_BYTE *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].eStats + 1) = 1;
  }
  ((CCBStage *)this->m_TempStorageNGH)->AssignSlotData(this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].bValid);
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
bool CCBStage::IsTaskValid(int n)
{
  unsigned int v3; // ecx
  int m_nRoleSlot; // edx
  float *v5; // esi
  double v6; // st7
  unsigned int v7; // eax
  char *v9; // [esp+0x20] [ebp-0x4]
  float v10; // [esp+0x20] [ebp-0x4]

  v3 = 329 * this->m_nClearRoleAllTask;
  m_nRoleSlot = this->m_nRoleSlot;
  v5 = (float *)((char *)&this->m_nCurTask + 8 * v3 + m_nRoleSlot * 80);
  v9 = this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].fp[2];
  if ( !*((_BYTE *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].eStats + 1) )
  {
    *(_DWORD *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].bValid = 0;
    *((_BYTE *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].eStats + 1) = 1;
  }
  ((CCBStage *)this->m_TempStorageNGH)->EndTurnAndAdvance();
  v6 = this->m_pCBSystem->m_fTimeFund - v5[6];
  if ( v6 >= *(float *)&v9 )
  {
    *((_DWORD *)v5 + 16) = 255;
    *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    v10 = v6 / *(float *)&v9 * 255.0;
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
int CCBStage::IsSubTaskValid(int a2, int a3)
{
  unsigned int v4; // ecx
  int m_nRoleSlot; // edx
  float *v6; // esi
  double v7; // st7
  unsigned int v8; // ecx
  char *v10; // [esp+0x20] [ebp-0x4]
  float v11; // [esp+0x20] [ebp-0x4]

  v4 = 329 * this->m_nClearRoleAllTask;
  m_nRoleSlot = this->m_nRoleSlot;
  v6 = (float *)((char *)&this->m_nCurTask + 8 * v4 + m_nRoleSlot * 80);
  v10 = this->m_Task[v4 / 0x149].SubTask[m_nRoleSlot].fp[2];
  if ( !*((_BYTE *)&this->m_Task[v4 / 0x149].SubTask[m_nRoleSlot].eStats + 1) )
  {
    *(_DWORD *)&this->m_Task[v4 / 0x149].SubTask[m_nRoleSlot].bValid = 255;
    *((_BYTE *)&this->m_Task[v4 / 0x149].SubTask[m_nRoleSlot].eStats + 1) = 1;
  }
  ((CCBStage *)this->m_TempStorageNGH)->EndTurnAndAdvance();
  v7 = this->m_pCBSystem->m_fTimeFund - v6[6];
  if ( v7 >= *(float *)&v10 )
  {
    v6[16] = 0.0;
    *((_DWORD *)v6 + 4) = 4;
  }
  else
  {
    v11 = (1.0 - v7 / *(float *)&v10) * 255.0;
    v8 = (int)v11;
    *((_DWORD *)v6 + 16) = v8;
    *((_DWORD *)v6 + 16) = v8 <= 0xFF ? v8 : 0;
  }
  if ( *((_BYTE *)v6 + 43) == 1 )
    *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FD290
bool CCBStage::IsIdle(int nVal)
{
  CEffectSystem *v3; // ecx
  char *v4; // eax
  int v5; // edi
  CCBUI *m_pUI; // ebp
  char *v8; // eax
  UIProgressBar *v9; // ecx
  char *v10; // eax
  CCBUI *v11; // ecx

  v3 = (CEffectSystem *)(329 * this->m_nClearRoleAllTask);
  v4 = (char *)this + 80 * this->m_nRoleSlot;
  v5 = (int)&v4[8 * (_DWORD)v3 + 184];
  if ( !v4[8 * (_DWORD)v3 + 225] )
  {
    if ( *((_BYTE *)((CEffectSystem *)v3)->DestroyAllEffect() + 5) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    m_pUI = this->m_pCBSystem->m_pUI;
    if ( BYTE1(this->m_pRoleState->m_Role[0].dwMagicID[8][4]) )
    {
      v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aWesneakattacke);
      ((UICaption *)m_pUI->m_pRoleStateGP[2])->SetEnable((int)v8, 1);
      v9 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    }
    else
    {
      v10 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aEnemysneakatta);
      ((UICaption *)m_pUI->m_pRoleStateGP[3])->SetEnable((int)v10, 1);
      v9 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    }
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v9->__vftable->ShowWindow)(v9, 1);
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || this->m_pCBSystem->m_fTimeFund - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || *((_BYTE *)((CEffectSystem *)this->m_pCBSystem)->DestroyAllEffect() + 5) )
  {
    v11 = this->m_pCBSystem->m_pUI;
    if ( BYTE1(this->m_pRoleState->m_Role[0].dwMagicID[8][4]) )
    {
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v11->m_pRoleStateGP[2]->__vftable->ShowWindow)(
// [VFTABLE]   v11->m_pRoleStateGP[2],
// [VFTABLE]   0);
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v11->m_pRoleStateGP[3]->__vftable->ShowWindow)(
// [VFTABLE]   v11->m_pRoleStateGP[3],
// [VFTABLE]   0);
    *(_DWORD *)(v5 + 16) = 4;
  }
  return 0;
}

// 0x004FD3D0
bool CCBStage::HasNormalAttackRole(int nRoleIndex)
{
  int m_nClearRoleAllTask; // ebp
  int v4; // ecx
  char *v5; // ebx
  int v6; // eax
  int v8; // edi
  char v9; // al
  signed int i; // edi
  char v11; // al
  int v12; // edi
  int v13; // ebx
  CCBRoleState *m_pRoleState; // ecx
  int j; // edi
  int v16; // ecx
  int v17; // edx
  CCBStageRole **v18; // eax
  int v19; // eax
  char *v20; // eax
  char v21; // dl
  int k; // eax
  int v23; // ebp
  int v24; // eax
  CCBStageRole **v25; // ecx
  int v26; // eax
  CCBStageRole **v27; // ecx
  int *p_fTemp1; // [esp+0x10] [ebp-0x10]
  CCBStageRole **m_pRole; // [esp+0x14] [ebp-0xC]
  CCBStageRole **v30; // [esp+0x14] [ebp-0xC]
  char *v31; // [esp+0x18] [ebp-0x8]
  int v32; // [esp+0x18] [ebp-0x8]
  int roleIdx; // [esp+0x1C] [ebp-0x4]

  if ( (byte_17AAA2C & 1) == 0 )
  {
    dword_17AAA20 = 0;
    byte_17AAA2C |= 1u;
    dword_17AAA24 = 0;
    dword_17AAA28 = 0;
    atexit(nullsub_20);
  }
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  roleIdx = LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3);
  v4 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v5 = (char *)&this->m_nCurTask + v4;
  v31 = v5;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) )
  {
    this->m_pEffect = 0;
    this->m_BFARole = 0;
    LOWORD(this->m_BFARound) = 0;
    BYTE2(this->m_BFARound) = 0;
    v6 = this->CalcSneakAttackVariance();
    fBladeTime = v6;
    if ( v6 == -1 )
    {
      v5[41] = 1;
      *((_DWORD *)v5 + 9) = -1;
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
    ((CCBRoleState *)this)->GetRoleMPValue(v6, *((_DWORD *)v5 + 11), LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp2));
    v5[41] = 1;
  }
  if ( (v5[44] & 1) != 0 )
  {
    v8 = 0;
    p_fTemp1 = (int *)&this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp1;
    m_pRole = this->m_pRole;
    do
    {
      ((CCBRoleState *)this->m_pRoleState)->CancelVariance(p_fTemp1, v8);
      if ( v9 && !((CCBRoleState *)this->m_pRoleState)->IsActive(v8) && ((CCBStageRole *)*m_pRole)->CheckViewTarget() )
      {
        fBladeTime = v8;
        ((CCBRoleState *)this)->GetRoleMPValue(v8, *((_DWORD *)v5 + 11), LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp2));
      }
      ++v8;
      ++m_pRole;
    }
    while ( v8 < 11 );
    ((CCBRoleState *)this)->GetRoleMPValue(fBladeTime, *((_DWORD *)v5 + 11), LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp2));
    for ( i = 0; i < 11; ++i )
    {
      if ( *((_BYTE *)&this->m_pEffect + i) )
      {
        ((CCBRoleState *)this->m_pRoleState)->CancelVariance(p_fTemp1, i);
        if ( !v11 )
          *((_BYTE *)&this->m_pEffect + i) = 0;
      }
    }
    if ( (unsigned int)fBladeTime <= 0xA && ((CCBRoleState *)this->m_pRoleState)->GetRoleAttr(roleIdx) < 4 )
      ((CCBStageRole *)this->m_pRole[roleIdx])->SetBladeTime(fBladeTime);
  }
  else
  {
    v12 = 0;
    v13 = 0;
    v30 = this->m_pRole;
    do
    {
      m_pRoleState = this->m_pRoleState;
      if ( m_pRoleState->m_Role[0].bMagicMastered[5][v13 + 4]
        && ((CCBRoleState *)m_pRoleState)->IsActive(v12) == 1
        && ((CCBStageRole *)*v30)->CheckViewTarget() )
      {
        fBladeTime = v12;
        ((CCBRoleState *)this)->GetRoleMPValue(v12, *((_DWORD *)v31 + 11), LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp2));
      }
      v13 += 892;
      ++v12;
      ++v30;
    }
    while ( v13 < 9812 );
    p_fTemp1 = (int *)&this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp1;
    if ( !((CCBStage *)this->m_pRoleState)->CheckGDBTypeCompat((unsigned int *)p_fTemp1) )
    {
      for ( j = 0; j < 11; ++j )
      {
        if ( *((_BYTE *)&this->m_pEffect + j) && !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(j) )
          *((_BYTE *)&this->m_pEffect + j) = 0;
      }
    }
    v5 = v31;
  }
  v16 = 0;
  v17 = 0;
  v32 = 0;
  v18 = this->m_pRole;
  do
  {
    if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v16 + 4] )
    {
      if ( *((_BYTE *)&this->m_pEffect + v17) )
      {
        ++v32;
        (*v18)->m_bShowWeapon = 1;
        (*v18)->m_bFlash = 1;
      }
      else
      {
        (*v18)->m_bShowWeapon = 0;
        (*v18)->m_bFlash = 0;
      }
    }
    v16 += 892;
    ++v17;
    ++v18;
  }
  while ( v16 < 9812 );
  if ( v32 <= 0 )
    v5[41] = 0;
  if ( g_Input.KeyInfo[0].PressTime == 1 && ((v19 = g_Input.KeyInfo[0].Data & 0xF, v19 == 1) || v19 == 2) )
  {
    if ( (v5[44] & 0x10) != 0 )
    {
      BYTE1(this->m_Task[m_nClearRoleAllTask].dwID) = 0;
      LOBYTE(this->m_Task[m_nClearRoleAllTask].dwID) = 0;
      LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp4) = fBladeTime;
      if ( fBladeTime == -1 )
        return 0;
    }
    else
    {
      LOBYTE(this->m_Task[m_nClearRoleAllTask].dwID) = 0;
      BYTE1(this->m_Task[m_nClearRoleAllTask].dwID) = 1;
      v20 = (char *)&this->m_Task[m_nClearRoleAllTask].cmd.dwItemID + 1;
      *(_DWORD *)v20 = this->m_pEffect;
      *((_DWORD *)v20 + 1) = this->m_BFARole;
      *((_WORD *)v20 + 4) = this->m_BFARound;
      v20[10] = BYTE2(this->m_BFARound);
      v21 = 0;
      for ( k = 0; k < 11; ++k )
      {
        if ( *((_BYTE *)&this->m_pEffect + k) )
          v21 = 1;
      }
      if ( !v21 )
        return 0;
    }
    v23 = roleIdx;
    *((_DWORD *)v5 + 9) = fBladeTime;
    *((_DWORD *)v5 + 4) = 4;
    v24 = 0;
    this->m_pRole[roleIdx]->m_bFlash = 0;
    v25 = this->m_pRole;
    do
    {
      if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v24 + 4] )
      {
        (*v25)->m_bShowWeapon = 0;
        (*v25)->m_bFlash = 0;
      }
      v24 += 892;
      ++v25;
    }
    while ( v24 < 9812 );
  }
  else
  {
    v23 = roleIdx;
  }
  if ( v5[43] == 1
    || g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1
    || g_Input.KeyInfo[17].PressTime == 1
    || *p_fTemp1 == 262 && ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v23, 16)
    || *p_fTemp1 == 261 && ((CCBRoleState *)this->m_pRoleState)->GetRoleField(v23, 15) )
  {
    *((_DWORD *)v5 + 9) = -1;
    *((_DWORD *)v5 + 4) = 4;
    v26 = 0;
    v27 = this->m_pRole;
    do
    {
      if ( this->m_pRoleState->m_Role[0].bMagicMastered[5][v26 + 4] )
      {
        (*v27)->m_bShowWeapon = 0;
        (*v27)->m_bFlash = 0;
      }
      v26 += 892;
      ++v27;
    }
    while ( v26 < 9812 );
  }
  return 0;
}

// 0x004FD880
void CCBStage::ClearRoleAllTask(int nRoleIndex)
{
  int m_nClearRoleAllTask; // eax
  CEffectSystem *v4; // ecx
  int v5; // edi
  int v6; // eax
  char *v7; // ebp
  int ItemNum; // eax
  int RoleNum; // eax
  UIProgressBar *v10; // ecx
  UIProgressBar *v11; // ecx
  int fTemp2_low; // [esp-0x4] [ebp-0x10]

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = (CEffectSystem *)(5 * m_nClearRoleAllTask);
  v5 = m_nClearRoleAllTask;
  v6 = 2632 * m_nClearRoleAllTask + 80 * this->m_nRoleSlot;
  v7 = (char *)&this->m_nCurTask + v6;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v6 + 1) )
  {
    if ( *((_BYTE *)((CEffectSystem *)v4)->DestroyAllEffect() + 5) )
    {
      v7[41] = 1;
      *((_DWORD *)v7 + 4) = 4;
      return;
    }
    if ( LODWORD(this->m_Task[v5].SubTask[31].fTemp2) )
    {
      fTemp2_low = LODWORD(this->m_Task[v5].SubTask[31].fTemp2);
      if ( LODWORD(this->m_Task[v5].SubTask[31].fTemp1) == 270 )
      {
        ItemNum = ((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(fTemp2_low);
        if ( LODWORD(this->m_Task[v5].SubTask[31].fTemp3) > 4 )
          ((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3])->SetEnable(ItemNum, 1);
        else
          ((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2])->SetEnable(ItemNum, 1);
      }
      else
      {
        RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(fTemp2_low);
        if ( LODWORD(this->m_Task[v5].SubTask[31].fTemp3) > 4 )
          ((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3])->SetEnable(RoleNum + 28, 1);
        else
          ((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2])->SetEnable(RoleNum + 28, 1);
      }
    }
    if ( LODWORD(this->m_Task[v5].SubTask[31].fTemp3) > 4 )
      v10 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    else
      v10 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v10->__vftable->ShowWindow)(v10, 1);
    v7[41] = 1;
  }
  if ( v7[43] == 1
    || this->m_pCBSystem->m_fTimeFund - *((float *)v7 + 6) > *((float *)v7 + 8)
    || *((_BYTE *)((CEffectSystem *)v4)->DestroyAllEffect() + 5) )
  {
    if ( LODWORD(this->m_Task[v5].SubTask[31].fTemp3) > 4 )
      v11 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    else
      v11 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v11->__vftable->ShowWindow)(v11, 0);
    *((_DWORD *)v7 + 4) = 4;
  }
}

// 0x004FDA10
void CCBStage::EndRoleAllTask(int nRoleIndex)
{
  int m_nClearRoleAllTask; // edi
  int v4; // eax
  char *v5; // ebp
  int SkillNum; // eax
  UIProgressBar *v7; // ecx
  UIProgressBar *v8; // ecx

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v5 = (char *)&this->m_nCurTask + v4;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) )
  {
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(unsigned int *)((char *)&this->m_Task[0].SubTask[0].dwID + v4));
    if ( LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3) > 4 )
    {
      ((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[3])->SetEnable(SkillNum + 4, 1);
      v7 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    }
    else
    {
      ((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateGP[2])->SetEnable(SkillNum + 4, 1);
      v7 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
    }
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v7->__vftable->ShowWindow)(v7, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6) > *((float *)v5 + 8) )
  {
    if ( LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3) > 4 )
      v8 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[3];
    else
      v8 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v8->__vftable->ShowWindow)(v8, 0);
    *((_DWORD *)v5 + 4) = 4;
  }
}

// 0x004FDB10
int CCBStage::GetRoleTaskNum(int nRoleIndex)
{
  int m_nClearRoleAllTask; // eax
  int v4; // ecx
  char *v5; // esi
  float *p_fTemp3; // ecx
  CCBStageCam *m_pCam; // ecx
  double v8; // st7
  double height; // st7
  double width; // st7
  int v11; // eax
  char v12; // dl
  struct gbVec3D v14; // [esp+0x8] [ebp-0x20] BYREF
  int v15; // [esp+0x14] [ebp-0x14]
  int v16; // [esp+0x18] [ebp-0x10]
  int v17; // [esp+0x1C] [ebp-0xC]
  float v18; // [esp+0x20] [ebp-0x8] BYREF
  float v19; // [esp+0x24] [ebp-0x4] BYREF

  v18 = 0.0;
  v19 = 0.0;
  memset(&v14, 0, sizeof(v14));
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v5 = (char *)&this->m_nCurTask + v4;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) )
  {
    p_fTemp3 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
    *((float *)&this->m_ptMousePos.x + *(_DWORD *)p_fTemp3) = *((float *)&this->m_ptMousePos.x + *(_DWORD *)p_fTemp3)
                                                            + 10.0;
    v14 = *(gbVec3D *)&this->m_pRole[*(_DWORD *)p_fTemp3]->m_Task[62].fTemp;
    *((_DWORD *)v5 + 16) = LODWORD(v14.x);
    *((_DWORD *)v5 + 17) = LODWORD(v14.z);
    v16 = *(&this->m_ptMousePos.x + *(_DWORD *)p_fTemp3);
    v17 = (int)*(float *)&v16;
    *((float *)v5 + 18) = *(float *)&v17;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    *((_DWORD *)v5 + 19) = ((int)unk_5DFDEC >> 16) & 0x1F;
    v5[41] = 1;
  }
  v14.x = *((float *)v5 + 16);
  v14.z = *((float *)v5 + 17);
  m_pCam = this->m_pCam;
  v14.y = 50.0;
  ((gbCamera *)&m_pCam->OrthoSize)->PointWorldToScr(&v14, &v18, &v19);
  sprintf(byte_17AA920, &dir[20], *((_DWORD *)v5 + 11));
  v8 = (this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6)) / *((float *)v5 + 8);
  if ( v8 > 1.0 )
    v8 = 1.0;
  *(float *)&v17 = (1.0 - v8) * 255.0;
  v16 = (int)*(float *)&v17;
  *(float *)&v17 = (this->m_pCBSystem->m_fTimeFund - *((float *)v5 + 6)) * 30.0;
  v15 = (int)*(float *)&v17;
  height = (double)g_DrvInfo.height;
  v15 = *((_DWORD *)v5 + 18) - (__int64)((1.0 - v19) * height * -0.5) - v15;
  v19 = 1.0 - ((double)v15 + (double)v15) / height;
  width = (double)g_DrvInfo.width;
  v15 = *((_DWORD *)v5 + 19) - (__int64)((v18 + 1.0) * width * -0.5) - 16;
  v18 = ((double)v15 + (double)v15) / width - 1.0;
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
void CCBStage::SelectRole(int nRoleIndex)
{
  int m_nClearRoleAllTask; // eax
  int v4; // ecx
  float *v5; // esi
  double v6; // st7
  double height; // st7
  double width; // st7
  float v9; // edx
  struct gbVec3D v10; // [esp+0x8] [ebp-0x20] BYREF
  int v11; // [esp+0x14] [ebp-0x14]
  int v12; // [esp+0x18] [ebp-0x10]
  int v13; // [esp+0x1C] [ebp-0xC]
  float v14; // [esp+0x20] [ebp-0x8] BYREF
  float v15; // [esp+0x24] [ebp-0x4] BYREF

  v14 = 0.0;
  v15 = 0.0;
  memset(&v10, 0, sizeof(v10));
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v5 = (float *)((char *)&this->m_nCurTask + v4);
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) )
  {
    v10 = *(gbVec3D *)&this->m_pRole[LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3)]->m_Task[62].eMode;
    v10.y = v10.y + 80.0;
    *(gbVec3D *)(&this->m_Task[0].SubTask[0].bValid + v4) = v10;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    *(_DWORD *)((char *)&this->m_Task[0].SubTask[0].param.f3 + v4) = ((int)unk_5DFDEC >> 16) & 0x1F;
    *((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) = 1;
  }
  v10 = *(gbVec3D *)(&this->m_Task[0].SubTask[0].bValid + v4);
  ((gbCamera *)&this->m_pCam->OrthoSize)->PointWorldToScr(&v10, &v14, &v15);
  v6 = (this->m_pCBSystem->m_fTimeFund - v5[6]) / v5[8];
  *(float *)&v13 = v6;
  if ( v6 > 1.0 )
    *(float *)&v13 = 1.0;
  *(float *)&v12 = (1.0 - *(float *)&v13) * 255.0;
  v11 = (int)*(float *)&v12;
  *(float *)&v12 = *(float *)&v13 * 32.0;
  v13 = (int)*(float *)&v12;
  height = (double)g_DrvInfo.height;
  v12 = 16 - (__int64)((1.0 - v15) * height * -0.5) - v13;
  v15 = 1.0 - ((double)v12 + (double)v12) / height;
  width = (double)g_DrvInfo.width;
  LODWORD(v9) = *((_DWORD *)v5 + 19) - (__int64)((v14 + 1.0) * width * -0.5) - 16;
  *(_WORD *)((char *)&v13 + 1) = 13055;
  *(float *)&v12 = v9;
  LOBYTE(v13) = -1;
  HIBYTE(v13) = v11;
  v14 = ((double)v12 + (double)v12) / width - 1.0;
  ((CCBStage *)this->m_TempStorageNGH)->InitRound();
  if ( this->m_pCBSystem->m_fTimeFund - v5[6] > v5[8] )
    *((_DWORD *)v5 + 4) = 4;
}

// 0x004FDFC0
unsigned int CCBStage::ProcWait(int formal)
{
  CCBStage *v2; // esi
  int m_nClearRoleAllTask; // eax
  int v4; // ecx
  char *v5; // eax
  int v6; // ebx
  int v7; // eax
  gbCamera *p_OrthoSize; // ecx
  double v9; // st7
  double height; // st7
  double width; // st7
  int v12; // edx
  char *v14; // [esp-0x8] [ebp-B8h]
  char *v15; // [esp-0x4] [ebp-B4h]
  int v16; // [esp-0x4] [ebp-B4h]
  char Buffer[128]; // [esp+0xC] [ebp-A4h] BYREF
  int v18; // [esp+0x8C] [ebp-0x24]
  CCBStage *v19; // [esp+0x90] [ebp-0x20]
  struct gbVec3D v20; // [esp+0x94] [ebp-0x1C] BYREF
  int v21; // [esp+A0h] [ebp-0x10]
  float v22; // [esp+A4h] [ebp-0xC]
  float v23; // [esp+A8h] [ebp-0x8] BYREF
  float v24; // [esp+ACh] [ebp-0x4] BYREF
v23 = 0.0;
  v24 = 0.0;
  memset(&v20, 0, sizeof(v20));
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v19 = this;
  v4 = 329 * m_nClearRoleAllTask;
  v5 = (char *)v19 + 80 * v19->m_nRoleSlot;
  v6 = (int)&v5[8 * v4 + 184];
  if ( !v5[8 * v4 + 225] )
  {
    *((float *)&this->m_ptMousePos.x + *(_DWORD *)&v5[8 * v4 + 232]) = *((float *)&this->m_ptMousePos.x
                                                                     + *(_DWORD *)&v5[8 * v4 + 232])
                                                                   + 10.0;
    v20 = *(gbVec3D *)&this->m_pRole[*(_DWORD *)&v5[8 * v4 + 232]]->m_Task[62].eMode;
    v7 = *(_DWORD *)&v5[8 * v4 + 232];
    *(float *)(v6 + 64) = v20.x;
    *(float *)(v6 + 68) = v20.z;
    v21 = *(&this->m_ptMousePos.x + v7);
    LODWORD(v22) = (int)*(float *)&v21;
    *(float *)(v6 + 72) = v22;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    *(_DWORD *)(v6 + 76) = ((int)unk_5DFDEC >> 16) & 0x1F;
    *(_BYTE *)(v6 + 41) = 1;
  }
  v20.x = *(float *)(v6 + 64);
  v20.z = *(float *)(v6 + 68);
  p_OrthoSize = (gbCamera *)&this->m_pCam->OrthoSize;
  v20.y = 50.0;
  ((gbCamera *)p_OrthoSize)->PointWorldToScr(&v20, &v23, &v24);
  v9 = (this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24)) / *(float *)(v6 + 32);
  if ( v9 > 1.0 )
    v9 = 1.0;
  v22 = (1.0 - v9) * 255.0;
  v18 = (int)v22;
  v22 = (this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24)) * 30.0;
  v21 = (int)v22;
  height = (double)g_DrvInfo.height;
  LODWORD(v22) = *(_DWORD *)(v6 + 72) - (__int64)((1.0 - v24) * height * -0.5) - v21;
  v24 = 1.0 - ((double)SLODWORD(v22) + (double)SLODWORD(v22)) / height;
  width = (double)g_DrvInfo.width;
  v12 = *(_DWORD *)(v6 + 76) - (__int64)((v23 + 1.0) * width * -0.5);
  *(_WORD *)((char *)&v21 + 1) = 13055;
  LODWORD(v22) = v12 - 32;
  LOBYTE(v21) = -1;
  HIBYTE(v21) = v18;
  v23 = ((double)SLODWORD(v22) + (double)SLODWORD(v22)) / width - 1.0;
  if ( *(_DWORD *)(v6 + 44) == 1 )
  {
    v16 = *(_DWORD *)(v6 + 52);
    v14 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aWitch);
    sprintf(Buffer, "%s -%d", v14, v16);
  }
  else if ( *(_DWORD *)(v6 + 44) == 2 )
  {
    v15 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aMoney);
    sprintf(Buffer, "%d%s", *(_DWORD *)(v6 + 52), v15);
  }
  else
  {
    strcpy(Buffer, g_szSceneUIText);
    v2 = v19;
  }
  ((CCBStage *)this->m_TempStorageNGH)->InitRound();
  if ( this->m_pCBSystem->m_fTimeFund - *(float *)(v6 + 24) > *(float *)(v6 + 32) )
    *(_DWORD *)(v6 + 16) = 4;
  return 0;
}

// 0x004FE290
unsigned int CCBStage::ProcShowFiveLineup(int formal)
{
  int m_nClearRoleAllTask; // eax
  int v4; // eax
  int v5; // ecx
  float *v6; // edi
  double v7; // st7
  double height; // st7
  double width; // st7
  __int64 v10; // rax
  float v11; // ebx
  unsigned int v12; // eax
  UIProgressBar *v13; // ecx
  struct gbVec3D v15; // [esp+0xC] [ebp-0x24] BYREF
  int v16; // [esp+0x18] [ebp-0x18]
  float v17; // [esp+0x1C] [ebp-0x14]
  int v18; // [esp+0x20] [ebp-0x10]
  float v19; // [esp+0x24] [ebp-0xC] BYREF
  float v20; // [esp+0x28] [ebp-0x8] BYREF
  char v21; // [esp+0x2C] [ebp-0x4]
  __int16 v22; // [esp+0x2D] [ebp-0x3]
  char v23; // [esp+0x2F] [ebp-0x1]

  v19 = 0.0;
  v20 = 0.0;
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  memset(&v15, 0, sizeof(v15));
  v4 = m_nClearRoleAllTask;
  v5 = v4 * 2632 + 80 * this->m_nRoleSlot;
  v6 = (float *)((char *)&this->m_nCurTask + v5);
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v5 + 1) )
  {
    v15 = *(gbVec3D *)&this->m_pRole[LODWORD(this->m_Task[v4].SubTask[31].fTemp3)]->m_Task[62].fTemp;
    v15.y = v15.y + 80.0;
    *(gbVec3D *)(&this->m_Task[0].SubTask[0].bValid + v5) = v15;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    *(_DWORD *)((char *)&this->m_Task[0].SubTask[0].param.f3 + v5) = ((int)unk_5DFDEC >> 16) & 0x1F;
    *((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v5 + 1) = 1;
  }
  v15 = *(gbVec3D *)(&this->m_Task[0].SubTask[0].bValid + v5);
  ((gbCamera *)&this->m_pCam->OrthoSize)->PointWorldToScr(&v15, &v19, &v20);
  v7 = (this->m_pCBSystem->m_fTimeFund - v6[6]) / v6[8];
  *(float *)&v18 = v7;
  if ( v7 > 1.0 )
    *(float *)&v18 = 1.0;
  v17 = (1.0 - *(float *)&v18) * 255.0;
  v16 = (int)v17;
  v17 = *(float *)&v18 * 32.0;
  height = (double)g_DrvInfo.height;
  v18 = 16 - (__int64)((1.0 - v20) * height * -0.5);
  v20 = 1.0 - ((double)v18 + (double)v18) / height;
  width = (double)g_DrvInfo.width;
  v10 = (__int64)((v19 + 1.0) * width * -0.5);
  HIDWORD(v10) = this->m_pCBSystem;
  LODWORD(v11) = *((_DWORD *)v6 + 19) - v10 - 16;
  v17 = v11;
  v23 = v16;
  v22 = 13055;
  v21 = -1;
  v19 = ((double)SLODWORD(v11) + (double)SLODWORD(v11)) / width - 1.0;
  (***(void ( ****)(_DWORD, int))(*(_DWORD *)(HIDWORD(v10) + 4) + 1080))(
    *(_DWORD *)(*(_DWORD *)(HIDWORD(v10) + 4) + 1080),
    1);
  ((UICaption *)this->m_pCBSystem->m_pUI->m_pRoleStateMP[0])->SetEnable((int)this->m_pRoleState->m_sCombatDialog, 0);
  v12 = ((CCBStage *)this->m_pCBSystem)->ProcShowEnemyFiveLineup();
  ((NPC *)*(NPC **)(v12 + 1080))->NPC::UpdateAnim();
  sub_446010(this->m_pCBSystem->m_pUI->m_pRoleStateMP[0]);
// [VFTABLE] sub_445D20(&this->m_pCBSystem->m_pUI->m_pRoleStateMP[0]->__vftable, LODWORD(v11) - 168, v18 - 128);
  ((UIScene *)this->m_pCBSystem->m_pUI->m_pRoleStateMP[0])->SetShow(0);
  if ( *((_BYTE *)v6 + 43) == 1 || this->m_pCBSystem->m_fTimeFund - v6[6] > v6[8] )
  {
    v13 = this->m_pCBSystem->m_pUI->m_pRoleStateMP[0];
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v13->__vftable->ShowWindow)(v13, 0);
    *((_DWORD *)v6 + 4) = 4;
  }
  return 0;
}

// 0x004FE540
unsigned int CCBStage::ProcShowEnemyFiveLineup()
{
  return (unsigned int)this->m_pRoleState;
}

// 0x004FE550
unsigned int CCBStage::ProcFiveLienupFadeIn(int formal)
{
  int m_nClearRoleAllTask; // eax
  int v4; // ecx
  char *v5; // edi
  float *p_fTemp3; // ebp
  CCBStageRole *v7; // ecx

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v5 = (char *)&this->m_nCurTask + v4;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) )
  {
    p_fTemp3 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
    v7 = this->m_pRole[*(_DWORD *)p_fTemp3];
    if ( !v7->m_bCatching || !v7->m_bDelAllTask )
    {
      if ( v7->m_bCatching == 1 )
        ((CCBStageRole *)v7)->GetCurrentTaskIndex();
      ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->DelAllTask(this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, 1);
      v5[41] = 1;
      *((_DWORD *)v5 + 4) = 4;
    }
  }
  return 0;
}

// 0x004FE600
unsigned int CCBStage::ProcFiveLienupFadeOut(int formal)
{
  int m_nClearRoleAllTask; // eax
  int v3; // edx
  char *v4; // esi

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v3 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v4 = (char *)&this->m_nCurTask + v3;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v3 + 1) )
  {
    ((CCBStageRole *)this->m_pRole[LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3)])->GetCurrentTask(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker);
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  return 0;
}

// 0x004FE660
unsigned int CCBStage::ProcShowSneakAttackState(unsigned int a_74)
{
  int m_nClearRoleAllTask; // eax
  float *p_fTemp1; // ebp
  char *v5; // edi
  unsigned int v7; // eax
  void *v8; // ecx
  CCBRoleState *m_pRoleState; // ecx
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  unsigned int v13; // eax
  double v14; // st7
  int v15; // eax
  tagRoleState *inited; // eax
  int i; // ebx
  int v18; // eax
  CCBRoleState *v19; // ecx
  tagRoleState *v20; // eax
  int nProtectRole; // ebx
  float *p_fTemp; // ecx
  float *v23; // eax
  double v24; // st7
  double v25; // st7
  int RoleIndex; // edi
  char v27; // [esp+0x13] [ebp-0x5D]
  char *v28; // [esp+0x14] [ebp-0x5C]
  int pnVal; // [esp+0x18] [ebp-0x58] BYREF
  int p_DWORD; // [esp+0x1C] [ebp-0x54] BYREF
  float fp[3]; // [esp+0x20] [ebp-0x50] BYREF
  gbVec3D v32; // [esp+0x2C] [ebp-0x44] BYREF
  gbVec3D v33; // [esp+0x38] [ebp-0x38] BYREF
  _DWORD pData[11]; // [esp+0x44] [ebp-0x2C] BYREF

  memset(fp, 0, sizeof(fp));
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  p_fTemp1 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp1;
  v5 = (char *)&this->m_nCurTask + 80 * this->m_nRoleSlot + m_nClearRoleAllTask * 2632;
  v28 = v5;
  if ( !((CCBStageRole *)this->m_pRole[LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3)])->IsReady(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( !v5[41] && ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->ForceDelTaskByPFN() )
  {

    v7 = *((_DWORD *)p_fTemp1 + 2);
    if ( v7 <= 4 && *(_BYTE *)(Buffer.m_partyActor.m_dwMatMsg[352 * v7 + 8] + 613) == 5
      || ((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)p_fTemp1 + 2))->dwID == 7366 )
    {
      pnVal = *((_DWORD *)p_fTemp1 + 3);
      if ( (unsigned int)pnVal <= 0xA )
      {
        v8 = CCBStage::Method_50E160;
        fp[0] = (float)pnVal;
LABEL_25:
        ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->GetProperCurAction((int)v8, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)fp, p_fTemp1, 1);
        goto LABEL_26;
      }
      m_pRoleState = this->m_pRoleState;
      *(float *)&p_DWORD = NAN;
      pnVal = -1;
      ((CCBRoleState *)m_pRoleState)->WriteBackRoleData((int)p_fTemp1, &p_DWORD, &pnVal);
      if ( v10 <= 0xA )
      {
        v8 = CCBStage::Method_50E160;
        fp[0] = (float)*((int *)p_fTemp1 + 3);
        goto LABEL_25;
      }
    }
    else
    {
      v11 = *((_DWORD *)p_fTemp1 + 2);
      if ( v11 > 4 )
      {
        if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)p_fTemp1 + 2))->dwID == 720 )
        {
          v8 = CCBStageRole::ProcMagic;
        }
        else if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)p_fTemp1 + 2))->dwID == 738
               || (inited = ((CCBRoleState *)this->m_pRoleState)->InitUI(*((_DWORD *)p_fTemp1 + 2)),
                   v8 = CCBStageRole::ProcTurnToRole,
                   inited->dwID == 739) )
        {
          v8 = CCBStageRole::ProcBlock;
        }
        goto LABEL_25;
      }
      v12 = v11 - 1;
      if ( v12 )
      {
        v13 = v12 - 1;
        if ( v13 )
        {
          if ( v13 == 1 )
          {
            v14 = ((CCBStageRole *)this->m_pRole[3])->AddTask(fp);
            v15 = this->m_nClearRoleAllTask;
            *(float *)&p_DWORD = v14;
            ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->GetProperCurAction(0 /* TODO: (int)CCBStage::CalcFacingAngle */, 0, 0, 0, this->m_Task[v15].SubTask[31].nEffLinker, (int *)fp, p_fTemp1, 1);
            ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->GetProperCurAction(0 /* TODO: (int)CCBStage::CheckAllDone */, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)fp, p_fTemp1, 1);
            v8 = CCBStage::ProcessCommand;
            LODWORD(fp[0]) = p_DWORD;
            goto LABEL_25;
          }
        }
        else
        {
          ((CCBStageRole *)this->m_pRole[2])->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcMagic */, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)fp, p_fTemp1, 1);
        }
        v8 = CCBStageRole::ProcTurnToRole;
        goto LABEL_25;
      }
      ((CCBStageRole *)this->m_pRole[1])->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcUseRecoverItem */, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)fp, p_fTemp1, 1);
    }
LABEL_26:
    *((_DWORD *)v5 + 16) = 1;
    v5[41] = 1;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(*((_DWORD *)p_fTemp1 + 2)) )
  {
    v27 = 1;
    if ( *((_BYTE *)p_fTemp1 + 17) )
    {
      for ( i = 0; i < 11; ++i )
      {
        if ( *((_BYTE *)p_fTemp1 + i + 29) && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(i) )
          v27 = 0;
      }
      if ( v27 )
        goto LABEL_35;
    }
    else if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(*((_DWORD *)p_fTemp1 + 3)) )
    {
LABEL_35:
      v5[41] = 1;
      *((_DWORD *)v5 + 4) = 4;
      return 0;
    }
  }
  if ( *((_DWORD *)v5 + 16) == 1 )
  {
    v18 = *((_DWORD *)p_fTemp1 + 2);
    if ( v18 >= 5 && v18 < 11 )
    {
      v19 = this->m_pRoleState;
      if ( v19->m_Role[0].bMagicMastered[5][4] )
      {
        if ( ((CCBRoleState *)v19)->InitUI(0)->nProtectRole >= 0
          && ((CCBRoleState *)this->m_pRoleState)->InitUI(0)->nProtectRole < 11 )
        {
          v20 = ((CCBRoleState *)this->m_pRoleState)->InitUI(0);
          if ( ((CCBStage *)this->m_pRoleState)->FindThreadByParam((int)p_fTemp1, v20->nProtectRole) )
          {
            nProtectRole = ((CCBRoleState *)this->m_pRoleState)->InitUI(0)->nProtectRole;
            p_fTemp = &this->m_pRole[nProtectRole]->m_Task[62].fTemp;
            v23 = &this->m_pRole[*((_DWORD *)p_fTemp1 + 2)]->m_Task[62].fTemp;
            v32.x = *p_fTemp - *v23;
            v32.y = p_fTemp[1] - v23[1];
            v24 = p_fTemp[2] - v23[2];
            v33 = v32;
            v32.z = v24;
            v25 = ((gbVec3D *)&v33)->Length();
            if ( v25 < 120.0 && v25 > 50.0 )
            {
              if ( ((CCBRoleState *)this->m_pRoleState)->ForceRoleTaskByCond(nProtectRole) )
              {
                memset(pData, 0, sizeof(pData));
                pData[2] = 0;
                pData[1] = 0;
                pData[3] = nProtectRole;
                RoleIndex = this->GetRoleIndex(18, pData, 1);
                if ( RoleIndex != -1 )
                {
                  v32.x = p_fTemp1[2];
                  LODWORD(v32.y) = pData[2];
                  LODWORD(v32.z) = pData[3];
                  this->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeIn */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ExecuteRoleTask */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->GetRoleName(RoleIndex, 0x5009C0, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->GetRoleName(RoleIndex, 0x500AD0, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  this->GetRoleName(RoleIndex, 0 /* TODO: (int)CCBStage::ProcFiveLienupFadeOut */, 0, 0, 0, (int *)&v32, -1082130432, 0);
                  *((_DWORD *)v28 + 16) = 0;
                  this->GetStageRoleByIdx(RoleIndex);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->ForceDelTaskByPFN() || v28[43] == 1 )
    *((_DWORD *)v28 + 4) = 4;
  return 0;
}

// 0x004FECE0
void CCBStage::HandleKeyCtrl(int n)
{
  int m_nClearRoleAllTask; // edi
  float *p_fTemp3; // ebp
  char *v5; // ebx

  if ( (byte_17AA91C & 1) == 0 )
  {
    pnVal = 0;
    byte_17AA91C |= 1u;
    dword_17AA914 = 0;
    dword_17AA918 = 0;
    atexit(nullsub_21);
  }
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  p_fTemp3 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
  v5 = (char *)&this->m_nCurTask + 80 * this->m_nRoleSlot + m_nClearRoleAllTask * 2632;
  if ( ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->IsReady(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker) )
  {
    if ( !v5[41] && ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
    {
      *(float *)&pnVal = (float)*(int *)p_fTemp3;
      *(float *)&dword_17AA914 = (float)SLODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp4);
      ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->GetProperCurAction(0 /* TODO: (int)CCBStage::ResolveActionEffect */, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, &pnVal, &this->m_Task[this->m_nClearRoleAllTask].SubTask[31].fTemp1, 1);
      v5[41] = 1;
    }
    if ( ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
      *((_DWORD *)v5 + 4) = 4;
    if ( v5[43] == 1 )
      *((_DWORD *)v5 + 4) = 4;
  }
  else
  {
    *((_DWORD *)v5 + 4) = 4;
  }
}

// 0x004FEE60
bool CCBStage::HandleKeyFriend(int Selected)
{
  int m_nClearRoleAllTask; // eax
  int v3; // edx
  char *v4; // esi

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v3 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v4 = (char *)&this->m_nCurTask + v3;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v3 + 1) )
  {
    ((CCBStageRole *)this->m_pRole[LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3)])->ProcTransportRun((unsigned int)CCBStage::ProcessSlotAction, 0, 0, 0, 0, 0, 3);
    v4[41] = 1;
    *((_DWORD *)v4 + 4) = 4;
  }
  if ( v4[43] == 1 )
    *((_DWORD *)v4 + 4) = 4;
  return 0;
}

// 0x004FEFB0
unsigned int CCBStage::ProcShowName(unsigned int formal)
{
  int m_nClearRoleAllTask; // eax
  int *p_fTemp3; // edi
  char *v5; // ebx
  int v7; // eax
  CCBStageRole *v8; // ecx
  void *v9; // edx
  int v10; // ecx
  double v11; // st7
  int v12; // eax
  int pnVal[3]; // [esp+0x14] [ebp-0xC] BYREF

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  p_fTemp3 = (int *)&this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
  v5 = (char *)&this->m_nCurTask + 80 * this->m_nRoleSlot + m_nClearRoleAllTask * 2632;
  if ( !((CCBStageRole *)this->m_pRole[*p_fTemp3])->IsReady(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker) )
  {
    *((_DWORD *)v5 + 4) = 4;
    return 0;
  }
  if ( !v5[41] && ((CCBStageRole *)this->m_pRole[*p_fTemp3])->ForceDelTaskByPFN() )
  {
    v7 = *p_fTemp3;
    if ( *p_fTemp3 >= 0 && v7 < 5 )
    {
      switch ( v7 )
      {
        case 1:
          v8 = this->m_pRole[1];
          v9 = CCBStageRole::ProcUseRecoverItem;
          break;
        case 2:
          v8 = this->m_pRole[2];
          v9 = CCBStageRole::ProcMagic;
          break;
        case 3:
          v8 = this->m_pRole[3];
          v9 = CCBStage::CheckAllDone;
          break;
        default:
          v8 = this->m_pRole[v7];
          v9 = CCBStageRole::ProcTurnToRole;
          break;
      }
      goto LABEL_22;
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(*p_fTemp3)->dwID == 720 )
    {
      v9 = CCBStageRole::ProcMagic;
    }
    else
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(*p_fTemp3)->dwID != 738
        && ((CCBRoleState *)this->m_pRoleState)->InitUI(*p_fTemp3)->dwID != 739 )
      {
        v9 = CCBStageRole::ProcTurnToRole;
        v8 = this->m_pRole[*p_fTemp3];
LABEL_22:
        ((CCBStageRole *)v8)->GetProperCurAction((int)v9, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)&v8->m_Task[62].eMode, 0, 1);
        v10 = *p_fTemp3;
        v11 = *(float *)&this->m_pRole[*p_fTemp3]->m_Task[63].cmd.dwCmdKind;
        pnVal[1] = 0;
        v12 = this->m_nClearRoleAllTask;
        *(float *)pnVal = v11;
        pnVal[2] = 0;
        ((CCBStageRole *)this->m_pRole[v10])->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, this->m_Task[v12].SubTask[31].nEffLinker, pnVal, 0, 1);
        v5[41] = 1;
        goto LABEL_23;
      }
      v9 = CCBStageRole::ProcBlock;
    }
    v8 = this->m_pRole[*p_fTemp3];
    goto LABEL_22;
  }
LABEL_23:
  if ( ((CCBStageRole *)this->m_pRole[*p_fTemp3])->ForceDelTaskByPFN() )
    *((_DWORD *)v5 + 4) = 4;
  if ( v5[43] == 1 && !((CCBRoleState *)this->m_pRoleState)->InitUI(*p_fTemp3)->nHP )
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF1B0
unsigned int CCBStage::ProcShowItemName(int formal)
{
  int m_nClearRoleAllTask; // eax
  float *p_fTemp3; // ebp
  char *v5; // edi
  void *v6; // edx
  CCBStageRole *v7; // ecx
  int v8; // ecx
  double v9; // st7
  int v10; // eax
  int pnVal[3]; // [esp+0x18] [ebp-0xC] BYREF

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  p_fTemp3 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
  v5 = (char *)&this->m_nCurTask + 80 * this->m_nRoleSlot + m_nClearRoleAllTask * 2632;
  if ( !((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->IsReady(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker) )
    goto LABEL_13;
  if ( v5[41] || !((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
    goto LABEL_12;
  if ( *(_DWORD *)p_fTemp3 == 1 )
    goto LABEL_9;
  if ( *(_DWORD *)p_fTemp3 != 2 )
  {
    if ( *(_DWORD *)p_fTemp3 != 3 )
    {
      v6 = CCBStageRole::ProcTurnToRole;
LABEL_10:
      v7 = this->m_pRole[*(_DWORD *)p_fTemp3];
      ((CCBStageRole *)v7)->GetProperCurAction((int)v6, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)&v7->m_Task[62].eMode, 0, 1);
      goto LABEL_11;
    }
LABEL_9:
    v6 = CCBStageRole::ProcUseRecoverItem;
    goto LABEL_10;
  }
  ((CCBStageRole *)this->m_pRole[2])->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcMagic */, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)&this->m_pRole[2]->m_Task[62].eMode, 0, 1);
LABEL_11:
  v8 = *(_DWORD *)p_fTemp3;
  v9 = *(float *)&this->m_pRole[*(_DWORD *)p_fTemp3]->m_Task[63].cmd.dwCmdKind;
  pnVal[1] = 0;
  v10 = this->m_nClearRoleAllTask;
  *(float *)pnVal = v9;
  pnVal[2] = 0;
  ((CCBStageRole *)this->m_pRole[v8])->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, this->m_Task[v10].SubTask[31].nEffLinker, pnVal, 0, 1);
  v5[41] = 1;
LABEL_12:
  if ( ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
LABEL_13:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF3D0
unsigned int CCBStage::ProcShowDamage(unsigned int formal)
{
  int m_nClearRoleAllTask; // ebp
  int v4; // eax
  char v5; // cl
  char *v6; // eax
  int v7; // edi
  CCBStageRole **m_pRole; // ebx
  int v9; // ecx
  CCBStageRole *p_fTemp; // eax
  gbVec3D *v11; // ecx
  int ItemNum; // eax
  float fTemp4; // eax
  float *p_fTemp4; // ebp
  CCBRoleState *m_pRoleState; // ecx
  CCBStageRole *v16; // eax
  ECBRoleTaskMode *p_eMode; // eax
  float *v18; // esi
  char *v20; // [esp+0x8] [ebp-0x4]

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v5 = *((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1);
  v6 = (char *)&this->m_nCurTask + v4;
  v20 = v6;
  if ( !v5 )
  {
    v7 = 0;
    m_pRole = this->m_pRole;
    do
    {
      if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(v7)->bValid && ((CCBRoleState *)this->m_pRoleState)->InitUI(v7)->bAlive )
      {
        v9 = *(_DWORD *)&((CCBRoleState *)this->m_pRoleState)->InitUI(v7)->byMagicUseTime[8][3];
        p_fTemp = (CCBStageRole *)&(*m_pRole)->m_Task[62].fTemp;
        v11 = &this->m_pScene->m_vecInitFiveLineup[v9];
        p_fTemp->m_pStage = (CCBStage *)LODWORD(v11->x);
        p_fTemp->m_pRoleState = (CCBRoleState *)LODWORD(v11->y);
        *(float *)p_fTemp->m_sLastRole = v11->z;
        LODWORD((*m_pRole)->m_Task[63].vec1.z) = (*m_pRole)->m_Task[63].cmd.dwCmdKind;
      }
      ++v7;
      ++m_pRole;
    }
    while ( v7 < 5 );
    ItemNum = ((PAL_GDB *)&g_pGDB)->GDB_GetItemNum(LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp2));
    if ( ItemNum )
    {
      if ( *(_BYTE *)(ItemNum + 592) == 2 )
      {
        fTemp4 = this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp4;
        p_fTemp4 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp4;
        if ( fTemp4 != NAN && LODWORD(fTemp4) != 10 )
        {
          m_pRoleState = this->m_pRoleState;
          if ( m_pRoleState->m_BufferData[2780] )
          {
            if ( !LOBYTE(((CCBRoleState *)m_pRoleState)->InitUI(10)[1].dwMagicID[2][5]) )
            {
              v16 = this->m_pRole[10];
              if ( v16->m_bAlive )
              {
                v16->m_Task[62].fTemp = *(float *)&v16->m_Task[62].eMode;
                v16->m_Task[62].fTemp2 = *(float *)&v16->m_Task[62].bValid;
                v16->m_Task[62].dwID = *(_DWORD *)(&v16->m_Task[62].bExecuted + 2);
                ((CCBStageRole *)this->m_pRole[10])->ForceRelease(0);
              }
            }
          }
          p_eMode = &this->m_pRole[10]->m_Task[62].eMode;
          v18 = &this->m_pRole[*(_DWORD *)p_fTemp4]->m_Task[62].fTemp;
          *v18 = *(float *)p_eMode;
          v18[1] = *(float *)&p_eMode[4];
          v18[2] = *(float *)&p_eMode[8];
        }
      }
    }
    v6 = v20;
    v20[41] = 1;
  }
  *((_DWORD *)v6 + 4) = 4;
  return 0;
}

// 0x004FF560
int CCBStage::ProcTaskSlot(int nVal)
{
  int m_nClearRoleAllTask; // eax
  int v3; // edx
  char *v4; // esi

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v3 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  v4 = (char *)&this->m_nCurTask + v3;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v3 + 1) )
    *((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v3 + 1) = 1;
  if ( *((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v3 + 3) == 1
    || ((CCBStageRole *)this->m_pRole[LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3)])->ForceDelTaskByPFN() )
  {
    *((_DWORD *)v4 + 4) = 4;
  }
  return 0;
}

// 0x004FF5C0
unsigned int CCBStage::ProcShowCost(int formal)
{
  int m_nClearRoleAllTask; // eax
  int v4; // ecx
  int *p_fTemp1; // ebp
  char *v6; // esi
  CCBStageRole *v7; // eax
  int v8; // eax
  int v9; // edx
  Actor *m_TempStorageWPX; // ecx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  char v14; // al
  char v15; // al

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v4 = m_nClearRoleAllTask * 2632 + 80 * this->m_nRoleSlot;
  p_fTemp1 = (int *)&this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp1;
  v6 = (char *)&this->m_nCurTask + v4;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) )
  {
    v7 = this->m_pRole[LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3)];
    LODWORD(v7->m_Task[63].vec1.z) = v7->m_Task[63].cmd.dwCmdKind;
    *((_BYTE *)&this->m_Task[0].SubTask[0].eStats + v4 + 1) = 1;
    ((CCBCamControl *)this->m_TempStorageWPX)->KeepCurCam(p_fTemp1[1]);
    *((_DWORD *)v6 + 14) = v8;
    v6[62] = 0;
    v6[61] = 0;
    v6[60] = 0;
    *((_DWORD *)v6 + 17) = 0;
    *((_DWORD *)v6 + 16) = 0;
  }
  v9 = *((_DWORD *)v6 + 14);
  m_TempStorageWPX = this->m_TempStorageWPX;
  v11 = (int)(&m_TempStorageWPX[2].m_nUpdateMode + 15 * v9 + 5);
  if ( !v6[60]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)&m_TempStorageWPX[3].m_actarray[60 * v9 + 8] )
  {
    ((CCBStageRole *)m_TempStorageWPX)->_CCBStageRole(v9, 1, p_fTemp1);
    *((_DWORD *)v6 + 16) = v12;
    v6[60] = 1;
  }
  if ( !v6[61] && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)(v11 + 52) )
  {
    ((CCBStageRole *)this->m_TempStorageWPX)->_CCBStageRole(*((_DWORD *)v6 + 14), 2, p_fTemp1);
    *((_DWORD *)v6 + 17) = v13;
    v6[61] = 1;
  }
  if ( !v6[62]
    && this->m_pCBSystem->m_fTimeFund - *((float *)v6 + 6) >= *(float *)&this->m_TempStorageWPX[3].m_actarray[60 * *((_DWORD *)v6 + 14) + 12] )
  {
    ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[this->m_nClearRoleAllTask].SubTask[31].fTemp1);
    v6[62] = 1;
  }
  if ( ((CCBStageRole *)this->m_pRole[p_fTemp1[2]])->ForceDelTaskByPFN() )
  {
    if ( v6[62] )
    {
      ((CEffMgr *)this->m_pCBSystem->m_pEffMgr)->Render(*((_DWORD *)v6 + 16));
      if ( !v14 )
      {
        ((CEffMgr *)this->m_pCBSystem->m_pEffMgr)->Render(*((_DWORD *)v6 + 17));
        if ( !v15 )
          *((_DWORD *)v6 + 4) = 4;
      }
    }
  }
  return 0;
}

// 0x004FF740
unsigned int CCBStage::ProcShowCombatDialog(int formal)
{
  unsigned int v3; // ecx
  int m_nRoleSlot; // edx
  char *v5; // eax
  int v6; // ebp
  int v7; // esi
  CCBStageRole **m_pRole; // ebx
  CCBRoleState *m_pRoleState; // ecx
  CCBStageRole *v10; // eax
  CCBRoleState *v11; // ecx
  CCBStageRole *v12; // ecx
  char *v14; // [esp+0x4] [ebp-0x4]

  v3 = 329 * this->m_nClearRoleAllTask;
  m_nRoleSlot = this->m_nRoleSlot;
  v5 = (char *)&this->m_nCurTask + 8 * v3 + m_nRoleSlot * 80;
  v14 = v5;
  if ( !*((_BYTE *)&this->m_Task[v3 / 0x149].SubTask[m_nRoleSlot].eStats + 1) )
  {
    v6 = 0;
    v7 = 0;
    m_pRole = this->m_pRole;
    do
    {
      m_pRoleState = this->m_pRoleState;
      if ( m_pRoleState->m_Role[0].bMagicMastered[5][v7 + 4]
        && !LOBYTE(((CCBRoleState *)m_pRoleState)->InitUI(v6)[1].dwMagicID[2][5]) )
      {
        v10 = *m_pRole;
        v10->m_Task[62].fTemp = *(float *)&(*m_pRole)->m_Task[62].eMode;
        v10->m_Task[62].fTemp2 = *(float *)&v10->m_Task[62].bValid;
        v10->m_Task[62].dwID = *(_DWORD *)(&v10->m_Task[62].bExecuted + 2);
        LODWORD((*m_pRole)->m_Task[63].vec1.z) = (*m_pRole)->m_Task[63].cmd.dwCmdKind;
      }
      v7 += 892;
      ++v6;
      ++m_pRole;
    }
    while ( v7 < 9812 );
    v11 = this->m_pRoleState;
    if ( v11->m_BufferData[2780] )
    {
      if ( !LOBYTE(((CCBRoleState *)v11)->InitUI(10)[1].dwMagicID[2][5]) )
      {
        v12 = this->m_pRole[10];
        if ( v12->m_bAlive )
          ((CCBStageRole *)v12)->ForceRelease(1);
      }
    }
    v5 = v14;
    v14[41] = 1;
  }
  *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x004FF840
unsigned int CCBStage::ProcGrabStageRole(unsigned int formal)
{
  int m_nClearRoleAllTask; // eax
  float *p_fTemp1; // edi
  char *v5; // ebp
  CCBStageRole *v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int pnVal[6]; // [esp+0x14] [ebp-0x1C] BYREF
  int v14; // [esp+0x2C] [ebp-0x4]

  memset(pnVal, 0, 12);
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  p_fTemp1 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp1;
  v5 = (char *)&this->m_nCurTask + 80 * this->m_nRoleSlot + m_nClearRoleAllTask * 2632;
  if ( !((CCBStageRole *)this->m_pRole[LODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3)])->IsReady(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker) )
    goto LABEL_17;
  if ( !v5[41] )
  {
    if ( !((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->ForceDelTaskByPFN() )
      return 0;
    ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->GetCurrentState();
    v6 = this->m_pRole[*((_DWORD *)p_fTemp1 + 2)];
    LODWORD(v6->m_Task[63].vec1.z) = v6->m_Task[63].cmd.dwCmdKind;
    v7 = *((_DWORD *)p_fTemp1 + 1);
    if ( v7 > 0x10D0 )
    {
      if ( v7 == 4505 )
      {

        v11 = this->m_nClearRoleAllTask;
        v14 = 0;
        ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcTurnToRole */, 0, 0, 0, this->m_Task[v11].SubTask[31].nEffLinker, pnVal, p_fTemp1, 1);
      }
    }
    else if ( v7 == 4304 || (v8 = v7 - 4101) == 0 )
    {

      v10 = this->m_nClearRoleAllTask;
      v14 = 0;
      ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcMagic */, 0, 0, 0, this->m_Task[v10].SubTask[31].nEffLinker, pnVal, p_fTemp1, 1);
    }
    else if ( v8 == 104 )
    {

      v9 = this->m_nClearRoleAllTask;
      v14 = 0;
      ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcUseRecoverItem */, 0, 0, 0, this->m_Task[v9].SubTask[31].nEffLinker, pnVal, p_fTemp1, 1);
    }
    v5[41] = 1;
  }
  if ( ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->ForceDelTaskByPFN() || v5[43] == 1 )
  {
    ((CCBStageRole *)this->m_pRole[*((_DWORD *)p_fTemp1 + 2)])->TryRelease();
LABEL_17:
    *((_DWORD *)v5 + 4) = 4;
  }
  return 0;
}

// 0x00500840
int CCBStage::ExecuteRoleTask(int nVal)
{
  int m_nClearRoleAllTask; // eax
  int v4; // ebp
  float *p_fTemp3; // ebx
  int *v6; // edi
  int v7; // eax
  CCBStageRole **v8; // ecx
  double v9; // st7
  int v10; // eax
  int pnVal; // [esp+0x10] [ebp-0x18] BYREF
  float v13; // [esp+0x14] [ebp-0x14]
  int v14; // [esp+0x18] [ebp-0x10]
  int v15[3]; // [esp+0x1C] [ebp-0xC] BYREF

  *(float *)&pnVal = 0.0;
  v13 = 0.0;
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  v14 = 0;
  v4 = m_nClearRoleAllTask;
  p_fTemp3 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
  v6 = &this->m_nCurTask + 658 * m_nClearRoleAllTask + 20 * this->m_nRoleSlot;
  if ( !((CCBStageRole *)this->m_pRole[LODWORD(this->m_Task[v4].SubTask[31].fTemp3)])->IsReady(this->m_Task[v4].SubTask[31].nEffLinker) )
    goto LABEL_8;
  if ( !*((_BYTE *)v6 + 41) )
  {
    if ( ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
    {
      *(float *)&pnVal = (float)SLODWORD(this->m_Task[v4].SubTask[31].fTemp4);
      v7 = this->m_nClearRoleAllTask;
      v13 = (float)v6[11];
      ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->GetProperCurAction(0 /* TODO: (int)CCBStage::UpdateSlotTimer */, 0, 0, 0, this->m_Task[v7].SubTask[31].nEffLinker, &pnVal, 0, 1);
      v8 = &this->m_pRole[*(_DWORD *)p_fTemp3];
      v9 = *(float *)&(*v8)->m_Task[63].cmd.dwCmdKind;
      v15[1] = 0;
      v10 = this->m_nClearRoleAllTask;
      *(float *)v15 = v9;
      v15[2] = 0;
      ((CCBStageRole *)*v8)->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, this->m_Task[v10].SubTask[31].nEffLinker, v15, 0, 1);
      *((_BYTE *)v6 + 41) = 1;
    }
    else
    {
      *((_BYTE *)v6 + 41) = 1;
      v6[4] = 4;
    }
  }
  if ( *((_BYTE *)v6 + 43) == 1 || ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
LABEL_8:
    v6[4] = 4;
  return 0;
}

// 0x005009C0
int CCBStage::Method_5009C0(int nVal)
{
  int m_nClearRoleAllTask; // edi
  float *p_fTemp3; // ebp
  char *v5; // ebx
  int v6; // eax
  int pnVal[3]; // [esp+0x14] [ebp-0xC] BYREF

  memset(pnVal, 0, sizeof(pnVal));
  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  p_fTemp3 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
  v5 = (char *)&this->m_nCurTask + 80 * this->m_nRoleSlot + m_nClearRoleAllTask * 2632;
  if ( !((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->IsReady(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker) )
    goto LABEL_7;
  if ( !v5[41] && ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
  {
    v6 = this->m_nClearRoleAllTask;
    *(float *)pnVal = (float)SLODWORD(this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp4);
    ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->GetProperCurAction(0 /* TODO: (int)CCBStage::AnimCallback_Throw */, 0, 0, 0, this->m_Task[v6].SubTask[31].nEffLinker, pnVal, 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x00500AD0
int CCBStage::Method_500AD0(int nVal)
{
  int m_nClearRoleAllTask; // eax
  float *p_fTemp3; // edi
  char *v5; // ebx
  int v6; // ecx
  double v7; // st7
  int v8; // eax
  int pnVal[3]; // [esp+0x14] [ebp-0xC] BYREF

  m_nClearRoleAllTask = this->m_nClearRoleAllTask;
  p_fTemp3 = &this->m_Task[m_nClearRoleAllTask].SubTask[31].fTemp3;
  v5 = (char *)&this->m_nCurTask + 80 * this->m_nRoleSlot + m_nClearRoleAllTask * 2632;
  if ( !((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->IsReady(this->m_Task[m_nClearRoleAllTask].SubTask[31].nEffLinker) )
    goto LABEL_7;
  if ( !v5[41] && ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
  {
    ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->GetProperCurAction(0 /* TODO: (int)CCBStageRole::ProcTurnToRole */, 0, 0, 0, this->m_Task[this->m_nClearRoleAllTask].SubTask[31].nEffLinker, (int *)&this->m_pRole[*(_DWORD *)p_fTemp3]->m_Task[62].eMode, 0, 1);
    v6 = *(_DWORD *)p_fTemp3;
    v7 = *(float *)&this->m_pRole[*(_DWORD *)p_fTemp3]->m_Task[63].cmd.dwCmdKind;
    pnVal[1] = 0;
    v8 = this->m_nClearRoleAllTask;
    *(float *)pnVal = v7;
    pnVal[2] = 0;
    ((CCBStageRole *)this->m_pRole[v6])->GetProperCurAction(0 /* TODO: (int)CCBStage::ProcessCommand */, 0, 0, 0, this->m_Task[v8].SubTask[31].nEffLinker, pnVal, 0, 1);
    v5[41] = 1;
  }
  if ( v5[43] == 1 || ((CCBStageRole *)this->m_pRole[*(_DWORD *)p_fTemp3])->ForceDelTaskByPFN() )
LABEL_7:
    *((_DWORD *)v5 + 4) = 4;
  return 0;
}

// 0x005024D0
int CCBStage::ProcessRoleEffect(int nVal)
{
  CEffectSystem *v3; // ecx
  char *v4; // eax
  int v5; // edi
  CCBUI *m_pUI; // ebp
  char *v8; // eax
  UIProgressBar *v9; // ecx
  UIProgressBar *v10; // ecx

  v3 = (CEffectSystem *)(329 * this->m_nClearRoleAllTask);
  v4 = (char *)this + 80 * this->m_nRoleSlot;
  v5 = (int)&v4[8 * (_DWORD)v3 + 184];
  if ( !v4[8 * (_DWORD)v3 + 225] )
  {
    if ( *((_BYTE *)((CEffectSystem *)v3)->DestroyAllEffect() + 5) )
    {
      *(_BYTE *)(v5 + 41) = 1;
      *(_DWORD *)(v5 + 16) = 4;
      return 0;
    }
    m_pUI = this->m_pCBSystem->m_pUI;
    if ( *(_DWORD *)(v5 + 44) == 1 )
      v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aFleesuccess);
    else
      v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aFleefail);
    ((UICaption *)m_pUI->m_pRoleStateGP[2])->SetEnable((int)v8, 1);
    v9 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v9->__vftable->ShowWindow)(v9, 1);
    *(_BYTE *)(v5 + 41) = 1;
  }
  if ( *(_BYTE *)(v5 + 43) == 1
    || this->m_pCBSystem->m_fTimeFund - *(float *)(v5 + 24) > *(float *)(v5 + 32)
    || *((_BYTE *)((CEffectSystem *)v3)->DestroyAllEffect() + 5) )
  {
    v10 = this->m_pCBSystem->m_pUI->m_pRoleStateGP[2];
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v10->__vftable->ShowWindow)(v10, 0);
    *(_DWORD *)(v5 + 16) = 4;
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
  ECBRoleTaskMode *v7; // eax
  int v8; // ecx
  int *v9; // eax
  gbVec3D *v10; // eax
  float v11; // eax
  int *v12; // esi
  gbVec3D *v13; // eax
  float v14; // edx
  int result; // eax
  int *p_eMode; // eax
  int *p_fTemp; // eax
  gbVec3D *v18; // eax
  float z; // eax
  int v20; // ebx
  gbVec3D *v21; // eax
  float y; // ecx
  float v23; // edx
  int *v25; // eax
  int *v26; // eax
  gbVec3D *v27; // eax
  float v28; // eax
  float v29; // [esp+0x18] [ebp-0x38]
  float v30; // [esp+0x18] [ebp-0x38]
  float v31; // [esp+0x18] [ebp-0x38]
  float v32; // [esp+0x18] [ebp-0x38]
  float v33; // [esp+0x18] [ebp-0x38]
  float v34; // [esp+0x18] [ebp-0x38]
  float v35; // [esp+0x18] [ebp-0x38]
  float v36; // [esp+0x1C] [ebp-0x34]
  float v37; // [esp+0x1C] [ebp-0x34]
  float v38; // [esp+0x1C] [ebp-0x34]
  float v39; // [esp+0x1C] [ebp-0x34]
  float v40; // [esp+0x1C] [ebp-0x34]
  float v41; // [esp+0x1C] [ebp-0x34]
  float v42; // [esp+0x1C] [ebp-0x34]
  float v43; // [esp+0x20] [ebp-0x30]
  float v44; // [esp+0x20] [ebp-0x30]
  float v45; // [esp+0x20] [ebp-0x30]
  float v46; // [esp+0x20] [ebp-0x30]
  float v47; // [esp+0x20] [ebp-0x30]
  float v48; // [esp+0x20] [ebp-0x30]
  float v49; // [esp+0x20] [ebp-0x30]
  int v50; // [esp+0x24] [ebp-0x2C]
  int v51; // [esp+0x24] [ebp-0x2C]
  int v52; // [esp+0x24] [ebp-0x2C]
  int v53; // [esp+0x24] [ebp-0x2C]
  int p_DWORD; // [esp+0x30] [ebp-0x20] BYREF
  int pnVal; // [esp+0x34] [ebp-0x1C] BYREF
  gbVec3D v56; // [esp+0x38] [ebp-0x18] BYREF
  gbVec3D v57; // [esp+0x44] [ebp-0xC] BYREF
  float *v58; // [esp+0x54] [ebp+0x4]
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
    ((CCBRoleState *)this->m_pRoleState)->WriteBackRoleData(nVal, &p_DWORD, &pnVal);
    v5 = v4;
    if ( v4 <= 11 )
    {
      p_eMode = (int *)&this->m_pRole[v4]->m_Task[62].eMode;
      g_nCBStageFlags[0] = *p_eMode;
      g_nCBStageFlags[1] = p_eMode[1];
      g_nCBStageFlags[2] = p_eMode[2];
      p_fTemp = (int *)&this->m_pRole[*(_DWORD *)(nVal + 8)]->m_Task[62].fTemp;
      g_nCBStageFlags[4] = *p_fTemp;
      g_nCBStageFlags[5] = p_fTemp[1];
      g_nCBStageFlags[6] = p_fTemp[2];
      __asm
      {
        fld     g_nCBStageFlags+0x18
        fsub    g_nCBStageFlags+8
        fstp    [esp+0x30+var_30]
        fld     g_nCBStageFlags+0x14
        fsub    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]
        fld     g_nCBStageFlags+0x10
        fsub    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38] }
      // [AUTO-COMMENTED] v18 = ((gbVec3D *)&v57)->gbVec3D(v32, v39, v46);
      v56.x = v18->x;
      v56.y = v18->y;
      z = v18->z;
      *(float *)&g_CCBStageState = v56.x;
      v56.z = z;
      *((_DWORD *)&g_CCBStageState + 1) = LODWORD(v56.y);
      *((float *)&g_CCBStageState + 2) = z;
      ((gbVec3D *)&g_CCBStageState)->Normalize();
      v20 = *(_DWORD *)(nVal + 8);
      if ( v20 == 4 && *(_BYTE *)(((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[8] + 613) == 1 )
      {
        ((CCBStageRole *)this->m_pRole[4])->GetStatus(v50);
        // __asm { fstp    [esp+0x2C+nVal] }
        ((CCBStageRole *)this->m_pRole[v5])->GetStatus(v51);
        __asm
        {
          fadd    [esp+0x2C+nVal]
          fadd    _flt_80_0
        }
      }
      else
      {
        ((CCBStageRole *)this->m_pRole[v20])->GetStatus(v50);
        // __asm { fstp    [esp+0x2C+nVal] }
        ((CCBStageRole *)this->m_pRole[v5])->GetStatus(v52);
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
        fstp    [esp+0x30+var_30]
        fld     dword ptr g_CCBStageState+4
        fadd    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]
        fld     dword ptr g_CCBStageState
        fadd    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38] }
      // [AUTO-COMMENTED] v21 = ((gbVec3D *)&v57)->gbVec3D(v33, v40, v47);
      v56.x = v21->x;
      y = v21->y;
      // __asm { fld     [esp+0x20+var_18] }
      v23 = v21->z;
      result = (int)v58;
      v56.y = y;
      v56.z = v23;
      __asm { fstp    dword ptr [eax] }
      *(float *)result = _ET1;
      v58[1] = y;
      v58[2] = v23;
    }
    else
    {
      _EDI = v58;
      v7 = &this->m_pRole[p_DWORD]->m_Task[62].eMode;
      *v58 = *(float *)v7;
      v8 = pnVal;
      v58[1] = *(float *)&v7[4];
      v58[2] = *(float *)&v7[8];
      v9 = (int *)&this->m_pRole[v8]->m_Task[62].eMode;
      g_nCBStageFlags[4] = *v9;
      g_nCBStageFlags[5] = v9[1];
      g_nCBStageFlags[6] = v9[2];
      __asm
      {
        fld     g_nCBStageFlags+0x18
        fadd    dword ptr [edi+8]
        fstp    [esp+0x30+var_30]
        fld     g_nCBStageFlags+0x14
        fadd    dword ptr [edi+4]
      }
      __asm
      {
        fstp    [esp+0x34+var_34]
        fld     g_nCBStageFlags+0x10
        fadd    dword ptr [edi]
      }
      // __asm { fstp    [esp+0x38+var_38] }
      // [AUTO-COMMENTED] v10 = ((gbVec3D *)&v57)->gbVec3D(v29, v36, v43);
      v56.x = v10->x;
      __asm
      {
        fld     [esp+0x2C+var_18]
        fmul    _flt_0_5
      }
      v56.y = v10->y;
      v11 = v10->z;
      __asm
      {
        fstp    g_nCBStageFlags
        fld     [esp+0x2C+var_14]
        fmul    _flt_0_5
      }
      v56.z = v11;
      __asm
      {
        fstp    g_nCBStageFlags+4
        fld     [esp+0x2C+var_10]
        fmul    _flt_0_5
        fstp    g_nCBStageFlags+8
      }
      v12 = (int *)&this->m_pRole[*(_DWORD *)(nVal + 8)]->m_Task[62].fTemp;
      g_nCBStageFlags[4] = *v12;
      g_nCBStageFlags[5] = v12[1];
      g_nCBStageFlags[6] = v12[2];
      __asm
      {
        fld     g_nCBStageFlags+0x18
        fsub    g_nCBStageFlags+8
        fstp    [esp+0x30+var_30]
        fld     g_nCBStageFlags+0x14
        fsub    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]
        fld     g_nCBStageFlags+0x10
        fsub    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38] }
      // [AUTO-COMMENTED] v56 = *((gbVec3D *)&v57)->gbVec3D(v30, v37, v44);
      *(gbVec3D *)&g_CCBStageState = v56;
      ((gbVec3D *)&g_CCBStageState)->Normalize();
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
        fstp    [esp+0x30+var_30]
        fld     dword ptr g_CCBStageState+4
        fadd    g_nCBStageFlags+4
      }
      __asm
      {
        fstp    [esp+0x34+var_34]
        fld     dword ptr g_CCBStageState
        fadd    g_nCBStageFlags
      }
      // __asm { fstp    [esp+0x38+var_38] }
      // [AUTO-COMMENTED] v13 = ((gbVec3D *)&v57)->gbVec3D(v31, v38, v45);
      v56.x = v13->x;
      v56.y = v13->y;
      v14 = v56.y;
      result = LODWORD(v13->z);
      *v58 = v56.x;
      v58[1] = v14;
      *((_DWORD *)v58 + 2) = result;
      LODWORD(v56.z) = result;
    }
  }
  else
  {
    v25 = (int *)&this->m_pRole[v3]->m_Task[62].eMode;
    g_nCBStageFlags[0] = *v25;
    g_nCBStageFlags[1] = v25[1];
    g_nCBStageFlags[2] = v25[2];
    v26 = (int *)&this->m_pRole[*(_DWORD *)(nVal + 8)]->m_Task[62].fTemp;
    g_nCBStageFlags[4] = *v26;
    g_nCBStageFlags[5] = v26[1];
    g_nCBStageFlags[6] = v26[2];
    __asm
    {
      fld     g_nCBStageFlags+0x18
      fsub    g_nCBStageFlags+8
      fstp    [esp+0x30+var_30]
      fld     g_nCBStageFlags+0x14
      fsub    g_nCBStageFlags+4
    }
    __asm
    {
      fstp    [esp+0x34+var_34]
      fld     g_nCBStageFlags+0x10
      fsub    g_nCBStageFlags
    }
    // __asm { fstp    [esp+0x38+var_38] }
    // [AUTO-COMMENTED] v27 = ((gbVec3D *)&v57)->gbVec3D(v34, v41, v48);
    v56.x = v27->x;
    v56.y = v27->y;
    v28 = v27->z;
    *(float *)&g_CCBStageState = v56.x;
    v56.z = v28;
    *((_DWORD *)&g_CCBStageState + 1) = LODWORD(v56.y);
    *((float *)&g_CCBStageState + 2) = v28;
    ((gbVec3D *)&g_CCBStageState)->Normalize();
    ((CCBStageRole *)this->m_pRole[*(_DWORD *)(nVal + 12)])->GetStatus(v50);
    // __asm { fstp    [esp+0x2C+nVal] }
    ((CCBStageRole *)this->m_pRole[*(_DWORD *)(v2 + 8)])->GetStatus(v53);
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
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(*(_DWORD *)(v2 + 8))->dwID == 7364
      || ((CCBRoleState *)this->m_pRoleState)->InitUI(*(_DWORD *)(v2 + 8))->dwID == 7381 )
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
      fstp    [esp+0x30+var_30]
      fld     dword ptr g_CCBStageState+4
      fadd    g_nCBStageFlags+4
    }
    __asm
    {
      fstp    [esp+0x34+var_34]
      fld     dword ptr g_CCBStageState
      fadd    g_nCBStageFlags
    }
    // __asm { fstp    [esp+0x38+var_38] }
    v56 = *((gbVec3D *)&v57)->gbVec3D(v35, v42, v49);
    return ((gbVec3D *)v58)->operator=(&v56);
  }
  return result;
}

// 0x00503680
int CCBStage::CalcSneakAttackVariance()
{
  char v2; // bl
  CCBStageEffect **p_m_pEffect; // ecx
  int *v4; // ebp
  unsigned int v5; // edi
  char v6; // al
  unsigned int v7; // eax
  int v8; // edi
  int i; // ebp
  CCBRoleState *m_pRoleState; // ecx
  int *v12; // ecx
  int v13; // eax
  int v14; // ebp
  int v15; // ebx
  int v16; // edi
  int v17; // edi
  int j; // ebp
  CCBRoleState *v19; // ecx
  int v20; // edi
  int k; // ebp
  CCBRoleState *v22; // ecx
  unsigned int v23; // [esp+0x10] [ebp-0xC]
  float v24; // [esp+0x14] [ebp-0x8]
  float v25; // [esp+0x18] [ebp-0x4]
  float v26; // [esp+0x18] [ebp-0x4]
  float v27; // [esp+0x18] [ebp-0x4]
  char v28; // [esp+0x20] [ebp+0x4]
  int v29; // [esp+0x20] [ebp+0x4]
  float Role; // [esp+0x20] [ebp+0x4]
  float v31; // [esp+0x20] [ebp+0x4]
  float v32; // [esp+0x20] [ebp+0x4]
  float v33; // [esp+0x20] [ebp+0x4]
  int *nRoleIndex; // [esp+0x24] [ebp+0x8]
  char nRoleIndexa; // [esp+0x24] [ebp+0x8]

  v2 = v28;
  p_m_pEffect = &this->m_pEffect;
  *p_m_pEffect = 0;
  v23 = -1;
  v24 = 1.0;
  v25 = 1.0;
  p_m_pEffect[1] = 0;
  *((_WORD *)p_m_pEffect + 4) = 0;
  *((_BYTE *)p_m_pEffect + 10) = 0;
  if ( (v28 & 1) != 0 )
  {
    v4 = nRoleIndex;
    v29 = v28 & 0x10;
    if ( (v2 & 0x10) != 0 )
    {
      v5 = ((CCBSystem *)this->m_pCBSystem->m_pAttackSequen)->ProcessAllCmds();
      v23 = v5;
      ((CCBRoleState *)this->m_pRoleState)->CancelVariance(nRoleIndex, v5);
      if ( !v6 )
      {
        v23 = -1;
        goto LABEL_18;
      }
      if ( v5 != 6 )
      {
        if ( v5 == -1 )
          goto LABEL_18;
        goto LABEL_63;
      }
      if ( *nRoleIndex != 259 )
        goto LABEL_63;
    }
    else
    {
      if ( (v2 & 4) == 0 && (v2 & 8) == 0 )
      {
LABEL_18:
        nRoleIndexa = 1;
        if ( *v4 == 259 && (v29 || (v2 & 4) != 0) && !((CCBRoleState *)this->m_pRoleState)->CalSneakAttack(v4[2], 6u) )
          nRoleIndexa = 0;
        v8 = 0;
        for ( i = 0; i < 9812; i += 892 )
        {
          m_pRoleState = this->m_pRoleState;
          if ( m_pRoleState->m_Role[0].bMagicMastered[5][i + 4]
            && !*((_BYTE *)&m_pRoleState->m_Role[2].fSkillCentInc + i + 1)
            && !HIBYTE(((CCBRoleState *)m_pRoleState)->InitUI(v8)[1].dwMagicID[2][4])
            && i >= 4460
            && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v8)
            && (nRoleIndexa || i != 5352) )
          {
            v26 = (float)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v8, 0);
            if ( v26 / (double)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v8, 1) <= v24 )
            {
              v27 = (float)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v8, 0);
              v23 = v8;
              v24 = v27 / (double)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v8, 1);
            }
          }
          ++v8;
        }
        *((_BYTE *)&this->m_pEffect + v23) = 1;
        return v23;
      }
      ((CCBRoleState *)this->m_pRoleState)->SetEnemyBeImbibeNimbus((v2 & 4) != 0, 1);
      v23 = v7;
      if ( (v2 & 4) == 0 || v7 != 6 )
      {
        if ( v7 == -1 )
          goto LABEL_18;
        goto LABEL_63;
      }
      if ( *nRoleIndex != 259 )
        goto LABEL_63;
    }
    if ( !((CCBRoleState *)this->m_pRoleState)->CalSneakAttack(nRoleIndex[2], 6u) )
    {
      v23 = -1;
      goto LABEL_18;
    }
LABEL_63:
    *((_BYTE *)&this->m_pEffect + v23) = 1;
    return v23;
  }
  v12 = nRoleIndex;
  v13 = *nRoleIndex;
  if ( *nRoleIndex != 262 && v13 != 260 && v13 != 261 )
  {
LABEL_47:
    if ( *v12 != 262
      || !((PAL_GDB *)this->m_pRoleState)->GetSkillType(v12[1])
      || ((PAL_GDB *)this->m_pRoleState)->GetSkillLevel(nRoleIndex[1]) )
    {
      goto LABEL_57;
    }
    v17 = 0;
    for ( j = 0; j < 4460; j += 892 )
    {
      v19 = this->m_pRoleState;
      if ( v19->m_Role[0].bMagicMastered[5][j + 4] )
      {
        if ( ((CCBRoleState *)v19)->IsRoleAlive(v17) )
        {
          Role = (float)(int)((CCBRoleState *)this->m_pRoleState)->GetRole(v17);
          if ( Role / (double)(int)((CCBRoleState *)this->m_pRoleState)->GetRole(v17) < v25 )
          {
            v31 = (float)(int)((CCBRoleState *)this->m_pRoleState)->GetRole(v17);
            v23 = v17;
            v25 = v31 / (double)(int)((CCBRoleState *)this->m_pRoleState)->GetRole(v17);
          }
        }
      }
      ++v17;
    }
    if ( v23 > 0xA )
    {
LABEL_57:
      v20 = 0;
      for ( k = 0; k < 4460; k += 892 )
      {
        v22 = this->m_pRoleState;
        if ( v22->m_Role[0].bMagicMastered[5][k + 4] )
        {
          if ( ((CCBRoleState *)v22)->IsRoleAlive(v20) )
          {
            v32 = (float)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v20, 0);
            if ( v32 / (double)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v20, 1) <= v24 )
            {
              v33 = (float)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v20, 0);
              v23 = v20;
              v24 = v33 / (double)((CCBRoleState *)this->m_pRoleState)->SetRoleField(v20, 1);
            }
          }
        }
        ++v20;
      }
    }
    goto LABEL_63;
  }
  v14 = 0;
  v15 = 0;
  while ( !this->m_pRoleState->m_Role[0].bMagicMastered[5][v15 + 4] )
  {
LABEL_45:
    v15 += 892;
    ++v14;
    if ( v15 >= 4460 )
    {
      v12 = nRoleIndex;
      goto LABEL_47;
    }
  }
  v16 = 1;
  while ( !((CCBRoleState *)this->m_pRoleState)->GetRoleField(v14, v16)
       || ((CCBRoleState *)this->m_pRoleState)->IsPlayerTeam(v16)
       || !((PAL_GDB *)this->m_pRoleState)->IsRoleSkillValid((unsigned int *)nRoleIndex, v16) )
  {
    if ( ++v16 >= 27 )
      goto LABEL_45;
  }
  *((_BYTE *)&this->m_pEffect + v14) = 1;
  return v14;
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
  p_m_ptMousePos = &this->m_ptMousePos;
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

// 0x00503FA0
int CCBStage::ResetTurnData(int **a2, gbGfxManager *p)
{
  ECBStageTaskState *p_eStats; // eax
  int v5; // edx
  float *p_fTemp1; // eax
  int v7; // edx

  p_eStats = &this->m_Task[0].SubTask[5].eStats;
  v5 = 50;
  do
  {
    *(_DWORD *)&p_eStats[-8] = 0;
    *(_DWORD *)&p_eStats[-4] = 0;
    *(_DWORD *)p_eStats = 0;
    *(_DWORD *)&p_eStats[4] = 0;
    *(_DWORD *)&p_eStats[8] = 0;
    *(_DWORD *)&p_eStats[12] = 0;
    *(_DWORD *)&p_eStats[16] = 0;
    *(_DWORD *)&p_eStats[20] = 0;
    *(_DWORD *)&p_eStats[24] = 0;
    *(_DWORD *)&p_eStats[28] = 0;
    *(_DWORD *)&p_eStats[32] = 0;
    *(_DWORD *)&p_eStats[36] = 0;
    p_eStats += 80;
    --v5;
  }
  while ( v5 );
  p_fTemp1 = &this->m_Task[1].SubTask[21].fTemp1;
  v7 = 64;
  do
  {
    *p_fTemp1 = 0.0;
    p_fTemp1[1] = 0.0;
    p_fTemp1[2] = 0.0;
    p_fTemp1[3] = 0.0;
    p_fTemp1[4] = 0.0;
    p_fTemp1[5] = 0.0;
    p_fTemp1 += 6;
    --v7;
  }
  while ( v7 );

  *(_DWORD *)&this->m_Task[0].SubTask[4].eStats = a2;
  this->m_Task[0].SubTask[4].dwID = **a2;
  return (int)this;
}

// 0x005040D0
int CCBStage::ResetTurnSystem()
{
  *(_DWORD *)&this->m_Task[0].SubTask[4].eStats = 0;
  this->m_Task[0].SubTask[4].dwID = 0;
  memset(&this->m_Task[1].SubTask[21].fTemp1, 0, 0x600u);
  this->m_Task[0].SubTask[4].fTime = 0.0;
  this->m_Task[0].SubTask[4].param.f3 = NAN;
  this->m_Task[0].SubTask[4].dwReturn = 0;
  this->m_Task[0].SubTask[4].param.f2 = 0.0;
  *(_DWORD *)&this->m_Task[0].SubTask[4].bValid = 0;
  this->m_Task[0].SubTask[4].param.f1 = NAN;
  memset(&this->m_Task[0].SubTask[4].nEffLinker, 0, 0xFA0u);
  return 0;
}

// 0x00504420
int CCBStage::ClearTurnSlot(int nVal)
{
  memset(&this->m_Task[1].SubTask[21].fTemp1 + 6 * nVal, 0, 0x18u);
  return 0;
}

// 0x00504440
bool CCBStage::GetTurnSlotData(int nVal)
{
  return this->HasTurnChanged(&this->m_Task[1].SubTask[21].fTemp1 + 6 * nVal);
}

// 0x00504460
bool CCBStage::HasTurnChanged(float *pfVal)
{
  return *pfVal != pfVal[1]
      || *pfVal != pfVal[2]
      || *pfVal != pfVal[3]
      || *pfVal != pfVal[4]
      || *pfVal != pfVal[5]
      || *pfVal != 0.0;
}

// 0x005045B0
char CCBStage::ProcessTurn()
{
  double v2; // st7
  double v3; // st6
  double v4; // st6
  int v5; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st6
  double v9; // st6
  double y; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  float v15; // [esp+0x2C] [ebp-0x44]
  char *v16; // [esp+0x2C] [ebp-0x44]
  float v17; // [esp+0x30] [ebp-0x40]
  char *v18; // [esp+0x30] [ebp-0x40]
  float v19; // [esp+0x34] [ebp-0x3C]
  float v20; // [esp+0x34] [ebp-0x3C]
  int Point; // [esp+0x38] [ebp-0x38]
  int Point_4; // [esp+0x3C] [ebp-0x34]
  struct gbVec3D v23; // [esp+0x40] [ebp-0x30] BYREF
  gbVec3D v24; // [esp+0x4C] [ebp-0x24] BYREF
  float v25; // [esp+0x58] [ebp-0x18]
  float v26; // [esp+0x60] [ebp-0x10]
  gbVec3D v27; // [esp+0x64] [ebp-0xC] BYREF

  this->m_Task[0].SubTask[3].fp[0] = 0;


  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( ((GRPinput *)&g_Input)->GetKeyState(0x100u) || ((GRPinput *)&g_Input)->GetKeyState(0x101u) )
  {
    v2 = (double)Point;
    v15 = v2 - this->m_Task[0].SubTask[4].fStartTime;
    v3 = (double)Point_4;
    v19 = v3;
    v4 = v3 - this->m_Task[0].SubTask[4].fWaitTime;
    this->m_Task[0].SubTask[4].fWaitTime = v19;
    v17 = v4;
    this->m_Task[0].SubTask[4].fStartTime = v2;
  }
  else
  {
    v17 = 0.0;
    v15 = 0.0;
    this->m_Task[0].SubTask[4].fStartTime = (float)Point;
    this->m_Task[0].SubTask[4].fWaitTime = (float)Point_4;
  }
  if ( *(_BYTE *)(**(_DWORD **)&this->m_Task[0].SubTask[4].eStats + 134) )
    goto LABEL_26;
  if ( ((GRPinput *)&g_Input)->GetKeyState(0x100u) )
  {
    v5 = *(_DWORD *)&this->m_Task[0].SubTask[4].eStats;
    if ( *(_DWORD *)(v5 + 88) == -1 && !*(_BYTE *)(*(_DWORD *)(v5 + 20) + 964) )
    {
      v24 = *(gbVec3D *)&this->m_Task[0].SubTask[3].nEffLinker;
      ((gbVec3D *)&v24)->Normalize();
      v27 = *(gbVec3D *)&this->m_Task[0].SubTask[3].fTemp2;
      ((gbVec3D *)&v27)->Normalize();
      memset(&v23, 0, sizeof(v23));
      ((gbVec3D *)&v27)->CrossProduct(&v24, &v23);
      ((gbVec3D *)&v23)->Normalize();
      v6 = v17 + v17;
      if ( (g_Input.KeyInfo[31].Data & 0xF) == 1 )
      {
        v24.x = 0.0;
        v24.y = v6;
        v7 = (float)0.0;
        v24.z = 0.0;
        v8 = v15 + v15;
        v23.x = v23.x * v8;
      }
      else
      {
        v24.y = 0.0;
        v24.x = v6 * v24.x;
        v7 = v6 * v24.z;
        v24.z = v7;
        v8 = v15 + v15;
        v23.x = v8 * v23.x;
      }
      v23.z = v23.z * v8;
      v9 = v7;
      y = v24.y;
      v26 = v9;
      v23.y = 0.0;
      v25 = v23.x + v24.x;
      v26 = v26 + v23.z;
      this->m_Task[0].SubTask[3].fTime = v25 + this->m_Task[0].SubTask[3].fTime;
      *(float *)&this->m_Task[0].SubTask[3].dwReturn = y + *(float *)&this->m_Task[0].SubTask[3].dwReturn;
      *(float *)&this->m_Task[0].SubTask[3].bValid = v26 + *(float *)&this->m_Task[0].SubTask[3].bValid;
      ((InputSystem *)this)->InputSystem::ProcessKeyboard();
      ((InputSystem *)this)->InputSystem::ProcessKeyboard();
    }
  }
  v11 = (double)*(int *)&g_Input.MouseState[8] * 0.25;
  if ( (g_Input.KeyInfo[31].Data & 0xF) == 1 )
  {
    *(float *)&this->m_Task[0].SubTask[3].eStats = v11 * 0.001 + *(float *)&this->m_Task[0].SubTask[3].eStats;
LABEL_18:
    ((InputSystem *)this)->InputSystem::ProcessKeyboard();
    goto LABEL_19;
  }
  if ( (g_Input.KeyInfo[32].Data & 0xF) != 1 )
  {
    *(float *)&this->m_Task[0].SubTask[3].dwID = v11 + *(float *)&this->m_Task[0].SubTask[3].dwID;
    goto LABEL_18;
  }
  v12 = v11 * 0.001 + *(float *)&this->m_pRoleState;
  this->m_pEditor = 0;
  *(float *)&this->m_pRoleState = v12;
LABEL_19:
  if ( ((GRPinput *)&g_Input)->GetKeyState(0x101u)
    && !*(_BYTE *)(*(_DWORD *)(*(_DWORD *)&this->m_Task[0].SubTask[4].eStats + 20) + 964) )
  {
    v13 = v15 * 0.0043633231 + *(float *)&this->m_Task[0].SubTask[3].fp[2];
    *(float *)&this->m_Task[0].SubTask[3].fp[2] = v13;
    *(float *)&this->m_Task[0].SubTask[3].fp[1] = *(float *)&this->m_Task[0].SubTask[3].fp[1] - v17 * 0.0043633231;
    if ( v13 <= 3.1415927 )
    {
      if ( v13 <= -3.1415927 )
        v13 = v13 + 6.2831855;
    }
    else
    {
      v13 = v13 - 6.2831855;
    }
    *(float *)&this->m_Task[0].SubTask[3].fp[2] = v13;
    ((InputSystem *)this)->InputSystem::ProcessKeyboard();
  }
LABEL_26:
  this->m_Task[0].SubTask[3].dwID = 1120403456;
  ((InputSystem *)this)->InputSystem::ProcessKeyboard();
  ((CameraCtrl *)this)->SetAsCurrent(3);
  v16 = this->m_Task[0].SubTask[3].fp[2];
  v18 = this->m_Task[0].SubTask[3].fp[1];
  v20 = *(float *)&this->m_Task[0].SubTask[3].eStats;
  ((Combat *)*(Combat **)(*(_DWORD *)&this->m_Task[0].SubTask[4].eStats + 68))->LogMessage((char *)5, 135, aCamXFYFZF, this->m_Task[0].SubTask[3].param.f1, this->m_Task[0].SubTask[3].param.f2, this->m_Task[0].SubTask[3].param.f3);
  ((Combat *)*(Combat **)(*(_DWORD *)&this->m_Task[0].SubTask[4].eStats + 68))->LogMessage((char *)5, 150, aCamYawFPitchFR, *(float *)&v16, *(float *)&v18, v20);
  return ((Combat *)*(Combat **)(*(_DWORD *)&this->m_Task[0].SubTask[4].eStats + 68))->LogMessage((char *)5, 165, aCamFovF, *(float *)&this->m_pRoleState);
}

// 0x005049F0
int * CCBStage::GetNextActiveTask()
{
  int *result; // eax
  int v2; // ecx
  int *v3; // ebx
  _BYTE *v4; // edx

  result = (int *)this;
  v2 = 0;
  v3 = result + 140;
  result[140] = 0;
  result[145] = -1;
  result[141] = 0;
  v4 = (char *)result + 606;
  result[142] = 0;
  result[143] = -1;
  while ( *(v4 - 2) )
  {
    if ( !*v4 )
    {
      result[145] = v2;
      *v3 = result[20 * v2 + 146];
      result[141] = result[20 * v2 + 147];
      result[142] = result[20 * v2 + 148];
      result[143] = result[20 * v2 + 149];
      return ((int *( *)(char *, _DWORD))*v3)((char *)result + result[141], 0);
    }
    ++v2;
    v4 += 80;
    if ( v2 >= 50 )
      return result;
  }
  return result;
}

// 0x00504A80
char CCBStage::ScanTurnSlots()
{
  int v1; // edx
  _BYTE *v2; // eax

  v1 = 0;
  v2 = (char *)&this->m_Task[0].SubTask[4].fTemp4 + 2;
  while ( *(v2 - 2) != 1 || *v2 != 1 )
  {
    ++v1;
    v2 += 80;
    if ( v1 >= 50 )
      return (char)v2;
  }
  LOBYTE(v2) = this->ClearActionSlot(v1);
  return (char)v2;
}

// 0x00504AB0
char CCBStage::ClearActionSlot(int nVal)
{
  int v2; // ebx
  int *p_nEffLinker; // eax

  v2 = nVal;
  if ( nVal == 49 )
  {
    memset(&this->m_Task[1].SubTask[20].fTemp1, 0, 0x50u);
    --LODWORD(this->m_Task[0].SubTask[4].param.f2);
    return 1;
  }
  else
  {
    if ( nVal < SLODWORD(this->m_Task[0].SubTask[4].param.f2) )
    {
      p_nEffLinker = &this->m_Task[0].SubTask[nVal + 4].nEffLinker;
      do
      {
        ++v2;
        qmemcpy(p_nEffLinker, p_nEffLinker + 20, 0x50u);
        p_nEffLinker += 20;
      }
      while ( v2 < SLODWORD(this->m_Task[0].SubTask[4].param.f2) );
    }
    memset(&this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2)-- + 4].nEffLinker, 0, 0x50u);
    return 1;
  }
}

// 0x00504B50
char CCBStage::EnqueueCommand(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        float fVal,
        const void *pData,
        const void *pData2)
{
  float f2; // ecx
  int *p_nEffLinker; // edx

  f2 = this->m_Task[0].SubTask[4].param.f2;
  if ( SLODWORD(f2) >= 49 )
    return 0;
  BYTE1(this->m_Task[0].SubTask[LODWORD(f2) + 4].fTemp4) = 0;
  BYTE2(this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2) + 4].fTemp4) = 0;
  LOBYTE(this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2) + 4].fTemp4) = 1;
  *(float *)&this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2) + 5].fp[1] = fVal;
  LODWORD(this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2) + 4].fTemp3) = nVal5;
  qmemcpy(&this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2) + 5].fp[2], pData, 0x18u);
  qmemcpy(&this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2) + 5].fTime, pData2, 0x18u);
  p_nEffLinker = &this->m_Task[0].SubTask[LODWORD(this->m_Task[0].SubTask[4].param.f2) + 4].nEffLinker;
  *p_nEffLinker = nVal;
  p_nEffLinker[1] = nVal2;
  p_nEffLinker[2] = nVal3;
  p_nEffLinker[3] = nVal4;
  ++LODWORD(this->m_Task[0].SubTask[4].param.f2);
  return 1;
}

// 0x00504C50
int CCBStage::ProcessQueuedCommand(int nVal)
{
  float v3; // eax
  int *v4; // esi
  float v6; // [esp+0x0] [ebp-0x28]
  float v7; // [esp+0x4] [ebp-0x24]
  float v8; // [esp+0x8] [ebp-0x20]
  float v9; // [esp+0xC] [ebp-0x1C]
  float v10; // [esp+0x10] [ebp-0x18]
  float v11; // [esp+0x14] [ebp-0x14]
  float v12; // [esp+0x24] [ebp-0x4]

  LODWORD(v3) = 80 * LODWORD(this->m_Task[0].SubTask[4].param.f3);
  v4 = (int *)((char *)&this->m_Task[0].SubTask[4].nEffLinker + LODWORD(v3));
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[4].fTemp4 + LODWORD(v3) + 1) )
  {
    *(char **)((char *)this->m_Task[0].SubTask[5].fp + LODWORD(v3)) = *(char **)(**(_DWORD **)&this->m_Task[0].SubTask[4].eStats
                                                                               + 80);
    *((_BYTE *)&this->m_Task[0].SubTask[4].fTemp4 + LODWORD(v3) + 1) = 1;
  }
  if ( *(float *)((char *)&this->m_Task[0].SubTask[5].fp[1] + LODWORD(v3)) == 0.0 )
    v12 = 1.0;
  else
    v12 = (*(float *)(**(_DWORD **)&this->m_Task[0].SubTask[4].eStats + 80)
         - *(float *)((char *)this->m_Task[0].SubTask[5].fp + LODWORD(v3)))
        / *(float *)((char *)&this->m_Task[0].SubTask[5].fp[1] + LODWORD(v3));
  v11 = (*(float *)(&this->m_Task[0].SubTask[5].bValid + LODWORD(v3))
       - *(float *)(&this->m_Task[0].SubTask[5].eStats + LODWORD(v3)))
      * v12
      + *(float *)(&this->m_Task[0].SubTask[5].eStats + LODWORD(v3));
  v10 = (*(float *)((char *)&this->m_Task[0].SubTask[5].dwReturn + LODWORD(v3))
       - *(float *)((char *)&this->m_Task[0].SubTask[5].fp[3] + LODWORD(v3)))
      * v12
      + *(float *)((char *)&this->m_Task[0].SubTask[5].fp[3] + LODWORD(v3));
  v9 = (*(float *)((char *)&this->m_Task[0].SubTask[5].fTime + LODWORD(v3))
      - *(float *)((char *)&this->m_Task[0].SubTask[5].fp[2] + LODWORD(v3)))
     * v12
     + *(float *)((char *)&this->m_Task[0].SubTask[5].fp[2] + LODWORD(v3));
  v8 = (*(float *)((char *)&this->m_Task[0].SubTask[5].param.f3 + LODWORD(v3))
      - *(float *)((char *)&this->m_Task[0].SubTask[5].fWaitTime + LODWORD(v3)))
     * v12
     + *(float *)((char *)&this->m_Task[0].SubTask[5].fWaitTime + LODWORD(v3));
  v7 = (*(float *)((char *)&this->m_Task[0].SubTask[5].param.f2 + LODWORD(v3))
      - *(float *)((char *)&this->m_Task[0].SubTask[5].fStartTime + LODWORD(v3)))
     * v12
     + *(float *)((char *)&this->m_Task[0].SubTask[5].fStartTime + LODWORD(v3));
  v6 = (*(float *)((char *)&this->m_Task[0].SubTask[5].param.f1 + LODWORD(v3))
      - *(float *)((char *)&this->m_Task[0].SubTask[5].dwID + LODWORD(v3)))
     * v12
     + *(float *)((char *)&this->m_Task[0].SubTask[5].dwID + LODWORD(v3));
  ((j_InputSystem *)LODWORD(v6))->InputSystem::ProcessKeyboard(LODWORD(v7), LODWORD(v8), LODWORD(v9), LODWORD(v10), LODWORD(v11));
  ((CameraCtrl *)this)->SetAsCurrent(3);
  if ( v12 >= 1.0 )
  {
    ((CCCTData *)this)->CCCTData::UpdateCamera((int)(v4 + 14));
    *((_BYTE *)v4 + 22) = 1;
  }
  return 0;
}

// 0x00504E30
int CCBStage::ClearAll()
{
  memset(this, 0, 0x639C0u);
  memset(&this->m_Task[154].SubTask[30].fTemp1, 0, 0x7D0u);
  memset(&this->m_Task[155].SubTask[22].fTemp3, 0xFFu, 0x4E20u);
  return -1;
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
  float fTemp4; // eax
  CScreenMode *Instance; // eax
  double v12; // st7
  double v13; // st6
  double m_DeltaTime; // st7
  double v15; // st7
  float v16; // eax
  CCBStageRole *v17; // eax
  float v18; // eax
  CCBStageRole *v19; // eax
  int v20; // [esp+0x0] [ebp-0x14]
  float v21; // [esp+0x8] [ebp-0xC]
  int v22; // [esp+0xC] [ebp-0x8]
  int v23; // [esp+0xC] [ebp-0x8]
  float v24; // [esp+0xC] [ebp-0x8]
  int v25; // [esp+0x10] [ebp-0x4]
  int v26; // [esp+0x10] [ebp-0x4]
  int v27; // [esp+0x18] [ebp+0x4]
  float v28; // [esp+0x18] [ebp+0x4]

  if ( (g_nCBFormation4[11] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation4[11]) |= 1u;
    g_nCBFormation4[8] = 0;
    g_nCBFormation4[9] = 0;
    g_nCBFormation4[10] = 0;
    atexit(nullsub_57);
  }
  if ( (g_nCBFormation4[11] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation4[11]) |= 2u;
    g_nCBFormation4[4] = 0;
    g_nCBFormation4[5] = 0;
    g_nCBFormation4[6] = 1065353216;
    atexit(nullsub_56);
  }
  if ( (g_nCBFormation4[11] & 4) == 0 )
  {
    LOBYTE(g_nCBFormation4[11]) |= 4u;
    g_nCBFormation4[0] = 0;
    g_nCBFormation4[1] = 0;
    g_nCBFormation4[2] = 0;
    atexit(nullsub_55);
  }
  v2 = (char *)this + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
  if ( v2[506] )
  {
    v9 = v27;
  }
  else
  {
    *((_DWORD *)v2 + 122) = -1054867456;
    v3 = 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
    *(float *)&this->m_Task[2].SubTask[14].eStats = *(float *)((char *)&this->m_Task[0].SubTask[2].fTemp1 + v3);
    this->m_Task[2].SubTask[14].dwID = *(_DWORD *)((char *)&this->m_Task[0].SubTask[2].fTemp2 + v3);
    this->m_Task[2].SubTask[14].fStartTime = *(float *)((char *)&this->m_Task[0].SubTask[2].fTemp3 + v3);
    v4 = *(float *)&this->m_Task[2].SubTask[14].eStats - this->m_Task[2].SubTask[13].fTemp3;
    *(float *)&v22 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
    v5 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
    g_nCBFormation4[9] = v22;
    *(float *)&v25 = v5;
    *(float *)&g_nCBFormation4[8] = v4;
    g_nCBFormation4[10] = v25;
    v6 = ((gbVec3D *)&g_nCBFormation4[8])->Length();
    if ( v6 < 2.0 )
    {
      this->m_Task[2].SubTask[13].fTemp3 = *(float *)&this->m_Task[2].SubTask[14].eStats;
      LODWORD(this->m_Task[2].SubTask[13].fTemp4) = this->m_Task[2].SubTask[14].dwID;
      this->m_Task[2].SubTask[14].fp[0] = (char *)LODWORD(this->m_Task[2].SubTask[14].fStartTime);
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
      return 0;
    }
    ((gbVec3D *)&g_nCBFormation4[8])->Normalize();
    g_fCombatTimer = acos(
                       *(float *)&g_nCBFormation4[6] * *(float *)&g_nCBFormation4[10]
                     + *(float *)&g_nCBFormation4[5] * *(float *)&g_nCBFormation4[9]
                     + *(float *)&g_nCBFormation4[4] * *(float *)&g_nCBFormation4[8]);
    if ( *(float *)&g_nCBFormation4[8] < 0.0 )
      g_fCombatTimer = 6.2831855 - g_fCombatTimer;
    *(&this->m_Task[0].SubTask[3].param.f1 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) = g_fCombatTimer
                                                                                                 * 57.29578;
    LODWORD(this->m_Task[2].SubTask[14].fWaitTime) = g_nCBFormation4[8];
    v28 = v6;
    v8 = v28 + v28;
    LODWORD(this->m_Task[2].SubTask[14].fTime) = g_nCBFormation4[9];
    this->m_Task[2].SubTask[14].dwReturn = g_nCBFormation4[10];
    this->m_Task[2].SubTask[14].fWaitTime = v8 * this->m_Task[2].SubTask[14].fWaitTime;
    this->m_Task[2].SubTask[14].fTime = v8 * this->m_Task[2].SubTask[14].fTime;
    *(float *)&this->m_Task[2].SubTask[14].dwReturn = v8 * *(float *)&this->m_Task[2].SubTask[14].dwReturn;
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
      this->m_Task[2].SubTask[13].nEffLinker = 31;
    else
      this->m_Task[2].SubTask[13].nEffLinker = 52;
    ((CCBStageRole *)this)->IsGrabedBy();
    v9 = 0;
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    ((CCBStageRole *)this)->ClearBadPushTask(0.40000001);
    fTemp4 = this->m_Task[0].SubTask[0].fTemp4;
    BYTE1(this->m_Task[0].SubTask[0].fTemp1) = 1;
    if ( LODWORD(fTemp4) == 3 )
    {
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(aWe013, 1);
    }
  }
  v12 = *(float *)&this->m_Task[2].SubTask[14].eStats - this->m_Task[2].SubTask[13].fTemp3;
  *(float *)&v23 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
  v13 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
  g_nCBFormation4[9] = v23;
  *(float *)&v26 = v13;
  *(float *)&g_nCBFormation4[8] = v12;
  g_nCBFormation4[10] = v26;
  if ( v9 == LODWORD(this->m_Task[2].SubTask[14].fTemp3) )
    *((_DWORD *)&this->m_Task[0].SubTask[3].bValid + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) = 1120403456;
  if ( *((float *)&this->m_Task[0].SubTask[3].bValid + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) > 0.0
    && ((gbVec3D *)&g_nCBFormation4[8])->Length() > 2.0 )
  {
    m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
    v21 = this->m_Task[2].SubTask[14].fWaitTime * m_DeltaTime;
    v24 = this->m_Task[2].SubTask[14].fTime * m_DeltaTime;
    v15 = m_DeltaTime * *(float *)&this->m_Task[2].SubTask[14].dwReturn;
    this->m_Task[2].SubTask[13].fTemp3 = v21 + this->m_Task[2].SubTask[13].fTemp3;
    this->m_Task[2].SubTask[13].fTemp4 = v24 + this->m_Task[2].SubTask[13].fTemp4;
    *(float *)this->m_Task[2].SubTask[14].fp = v15 + *(float *)this->m_Task[2].SubTask[14].fp;
    *(float *)&this->m_Task[2].SubTask[14].bValid = this->m_pCBSystem->m_pUtil->m_DeltaTime * 720.0
                                                  + *(float *)&this->m_Task[2].SubTask[14].bValid;
  }
  if ( v9 == LODWORD(this->m_Task[2].SubTask[14].fTemp4) && ((gbVec3D *)&g_nCBFormation4[8])->Length() <= 2.0 )
    *((_DWORD *)&this->m_Task[0].SubTask[3].bValid + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) = -1054867456;
  ((gbVec3D *)&g_nCBFormation4[8])->Normalize();
  g_fCombatTimer = acos(
                     *(float *)&g_nCBFormation4[6] * *(float *)&g_nCBFormation4[10]
                   + *(float *)&g_nCBFormation4[5] * *(float *)&g_nCBFormation4[9]
                   + *(float *)&g_nCBFormation4[4] * *(float *)&g_nCBFormation4[8]);
  if ( *(float *)&g_nCBFormation4[8] < 0.0 )
    g_fCombatTimer = 6.2831855 - g_fCombatTimer;
  if ( fabs(
         g_fCombatTimer * 57.29578
       - *(&this->m_Task[0].SubTask[3].param.f1 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime))) >= 1.570796370506287 )
  {
    this->m_Task[2].SubTask[13].fTemp3 = *(float *)&this->m_Task[2].SubTask[14].eStats;
    LODWORD(this->m_Task[2].SubTask[13].fTemp4) = this->m_Task[2].SubTask[14].dwID;
    this->m_Task[2].SubTask[14].fp[0] = (char *)LODWORD(this->m_Task[2].SubTask[14].fStartTime);
    *((_DWORD *)&this->m_Task[0].SubTask[3].bValid + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) = -1054867456;
  }
  if ( v9 == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
  {
    this->m_Task[2].SubTask[13].fTemp3 = *(float *)&this->m_Task[2].SubTask[14].eStats;
    LODWORD(this->m_Task[2].SubTask[13].fTemp4) = this->m_Task[2].SubTask[14].dwID;
    this->m_Task[2].SubTask[14].fp[0] = (char *)LODWORD(this->m_Task[2].SubTask[14].fStartTime);
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    v16 = this->m_Task[0].SubTask[0].fTemp4;
    BYTE1(this->m_Task[0].SubTask[0].fTemp1) = 0;
    if ( LODWORD(v16) == 3 )
    {
      v17 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v17)->PlaySound(aWe013, v20);
    }
  }
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
  {
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    v18 = this->m_Task[0].SubTask[0].fTemp4;
    BYTE1(this->m_Task[0].SubTask[0].fTemp1) = 0;
    if ( LODWORD(v18) == 3 )
    {
      v19 = (CCBStageRole *)CScreenMode::GetInstance();
      ((CCBStageRole *)v19)->PlaySound(aWe013, v20);
    }
  }
  return 0;
}

// 0x0050DA90
int CCBStage::UpdateSlotTimer(int nVal)
{
  double v3; // st7
  float *p_eStats; // edi
  double v5; // st6
  double v6; // st7
  double v7; // st6
  double v8; // st7
  double v9; // st6
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st6
  long double v15; // st7
  float *p_fTemp3; // edi
  double m_DeltaTime; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st7
  float v24; // [esp+0xC] [ebp-0x2C]
  unsigned int v25; // [esp+0x10] [ebp-0x28]
  unsigned int v26; // [esp+0x10] [ebp-0x28]
  int v27; // [esp+0x10] [ebp-0x28]
  unsigned int v28; // [esp+0x10] [ebp-0x28]
  int v29; // [esp+0x10] [ebp-0x28]
  float v30; // [esp+0x10] [ebp-0x28]
  int v31; // [esp+0x10] [ebp-0x28]
  float v32; // [esp+0x14] [ebp-0x24]
  float v33; // [esp+0x14] [ebp-0x24]
  int v34; // [esp+0x14] [ebp-0x24]
  float v35; // [esp+0x14] [ebp-0x24]
  int v36; // [esp+0x14] [ebp-0x24]
  int v37; // [esp+0x14] [ebp-0x24]
  float v38; // [esp+0x24] [ebp-0x14]
  float v39; // [esp+0x28] [ebp-0x10]
  float v40; // [esp+0x28] [ebp-0x10]
  float v41; // [esp+0x2C] [ebp-0xC]
  float v42; // [esp+0x2C] [ebp-0xC]
  float v43; // [esp+0x30] [ebp-0x8]

  if ( (g_nCBFormation3[11] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation3[11]) |= 1u;
    g_nCBFormation3[8] = 0;
    g_nCBFormation3[9] = 0;
    g_nCBFormation3[10] = 0;
    atexit(nullsub_60);
  }
  if ( (g_nCBFormation3[11] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation3[11]) |= 2u;
    g_nCBFormation3[4] = 0;
    g_nCBFormation3[5] = 0;
    g_nCBFormation3[6] = 1065353216;
    atexit(nullsub_59);
  }
  if ( (g_nCBFormation3[11] & 4) == 0 )
  {
    LOBYTE(g_nCBFormation3[11]) |= 4u;
    g_nCBFormation3[0] = 0;
    g_nCBFormation3[1] = 0;
    g_nCBFormation3[2] = 0;
    atexit(nullsub_58);
  }
  dword_17ABCE8 = (int)*(&this->m_Task[0].SubTask[2].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime));
  v43 = *(&this->m_Task[0].SubTask[2].fTemp2 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime));
  dword_17ABCEC = (int)v43;
  if ( !*((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    v38 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + dword_17ABCE8) + 6596);
    v39 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + dword_17ABCE8) + 6600);
    v3 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + (int)v43) + 6596) - v38;
    v41 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + dword_17ABCE8) + 6604);
    p_eStats = (float *)&this->m_Task[2].SubTask[14].eStats;
    *(float *)&v25 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + (int)v43) + 6600) - v39;
    v5 = *(float *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + (int)v43) + 6604) - v41;
    this->m_Task[2].SubTask[14].dwID = v25;
    v32 = v5;
    *(float *)&this->m_Task[2].SubTask[14].eStats = v3;
    this->m_Task[2].SubTask[14].fStartTime = v32;
    ((gbVec3D *)&this->m_Task[2].SubTask[14].eStats)->Normalize();
    *(float *)&this->m_Task[2].SubTask[14].eStats = *(float *)&this->m_Task[2].SubTask[14].eStats * 32.0;
    *(float *)&this->m_Task[2].SubTask[14].dwID = *(float *)&this->m_Task[2].SubTask[14].dwID * 32.0;
    this->m_Task[2].SubTask[14].fStartTime = this->m_Task[2].SubTask[14].fStartTime * 32.0;
    v6 = v38 + *(float *)&this->m_Task[2].SubTask[14].eStats;
    *(float *)&v26 = v39 + *(float *)&this->m_Task[2].SubTask[14].dwID;
    v7 = v41 + this->m_Task[2].SubTask[14].fStartTime;
    this->m_Task[2].SubTask[14].dwID = v26;
    v33 = v7;
    *(float *)&this->m_Task[2].SubTask[14].eStats = v6;
    this->m_Task[2].SubTask[14].fStartTime = v33;
    v8 = this->m_Task[2].SubTask[13].fTemp3 - *(float *)&this->m_Task[2].SubTask[14].eStats;
    *(float *)&v27 = this->m_Task[2].SubTask[13].fTemp4 - *(float *)&this->m_Task[2].SubTask[14].dwID;
    v9 = *(float *)this->m_Task[2].SubTask[14].fp - this->m_Task[2].SubTask[14].fStartTime;
    g_nCBFormation3[9] = v27;
    *(float *)&v34 = v9;
    *(float *)&g_nCBFormation3[8] = v8;
    g_nCBFormation3[10] = v34;
    if ( ((gbVec3D *)&g_nCBFormation3[8])->Length() < 4.0 )
    {
      this->m_Task[2].SubTask[13].fTemp3 = *p_eStats;
      LODWORD(this->m_Task[2].SubTask[13].fTemp4) = this->m_Task[2].SubTask[14].dwID;
      this->m_Task[2].SubTask[14].fp[0] = (char *)LODWORD(this->m_Task[2].SubTask[14].fStartTime);
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
      return 0;
    }
    ((gbVec3D *)&g_nCBFormation3[8])->Normalize();
    *(float *)&g_nCBFormation3[8] = *(float *)&g_nCBFormation3[8] * 10.0;
    *(float *)&g_nCBFormation3[9] = *(float *)&g_nCBFormation3[9] * 10.0;
    *(float *)&g_nCBFormation3[10] = *(float *)&g_nCBFormation3[10] * 10.0;
    v11 = *(float *)&g_nCBFormation3[8] + *p_eStats;
    *(float *)&v28 = *(float *)&g_nCBFormation3[9] + *(float *)&this->m_Task[2].SubTask[14].dwID;
    v12 = *(float *)&g_nCBFormation3[10] + this->m_Task[2].SubTask[14].fStartTime;
    this->m_Task[2].SubTask[14].dwID = v28;
    v35 = v12;
    *p_eStats = v11;
    this->m_Task[2].SubTask[14].fStartTime = v35;
    v13 = *p_eStats - this->m_Task[2].SubTask[13].fTemp3;
    *(float *)&v29 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
    v14 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
    g_nCBFormation3[9] = v29;
    *(float *)&v36 = v14;
    *(float *)&g_nCBFormation3[8] = v13;
    g_nCBFormation3[10] = v36;
    ((gbVec3D *)&g_nCBFormation3[8])->Normalize();
    v15 = acos(
            *(float *)&g_nCBFormation3[5] * *(float *)&g_nCBFormation3[9]
          + *(float *)&g_nCBFormation3[6] * *(float *)&g_nCBFormation3[10]
          + *(float *)&g_nCBFormation3[4] * *(float *)&g_nCBFormation3[8]);
    *(float *)&this->m_Task[2].SubTask[14].bValid = v15;
    if ( *(float *)&g_nCBFormation3[8] < 0.0 )
      *(float *)&this->m_Task[2].SubTask[14].bValid = 6.2831855 - v15;
    *(float *)&this->m_Task[2].SubTask[14].bValid = *(float *)&this->m_Task[2].SubTask[14].bValid * 57.29578;
    LODWORD(this->m_Task[2].SubTask[14].fWaitTime) = g_nCBFormation3[8];
    LODWORD(this->m_Task[2].SubTask[14].fTime) = g_nCBFormation3[9];
    this->m_Task[2].SubTask[14].dwReturn = g_nCBFormation3[10];
    this->m_Task[2].SubTask[14].fWaitTime = this->m_Task[2].SubTask[14].fWaitTime * 480.0;
    this->m_Task[2].SubTask[14].fTime = this->m_Task[2].SubTask[14].fTime * 480.0;
    *(float *)&this->m_Task[2].SubTask[14].dwReturn = *(float *)&this->m_Task[2].SubTask[14].dwReturn * 480.0;
    this->m_Task[2].SubTask[13].nEffLinker = 31;
    ((CCBStageRole *)this)->IsGrabedBy();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    BYTE1(this->m_Task[0].SubTask[0].fTemp1) = 1;
  }
  p_fTemp3 = &this->m_Task[2].SubTask[13].fTemp3;
  m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
  v24 = this->m_Task[2].SubTask[14].fWaitTime * m_DeltaTime;
  v30 = this->m_Task[2].SubTask[14].fTime * m_DeltaTime;
  v18 = v24 + this->m_Task[2].SubTask[13].fTemp3;
  v40 = this->m_Task[2].SubTask[13].fTemp4 + v30;
  v19 = *(float *)this->m_Task[2].SubTask[14].fp + m_DeltaTime * *(float *)&this->m_Task[2].SubTask[14].dwReturn;
  this->m_Task[2].SubTask[13].fTemp4 = v40;
  v42 = v19;
  this->m_Task[2].SubTask[13].fTemp3 = v18;
  *(float *)this->m_Task[2].SubTask[14].fp = v42;
  v20 = *(float *)&this->m_Task[2].SubTask[14].eStats - this->m_Task[2].SubTask[13].fTemp3;
  *(float *)&v31 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
  v21 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
  g_nCBFormation3[9] = v31;
  *(float *)&v37 = v21;
  *(float *)&g_nCBFormation3[8] = v20;
  g_nCBFormation3[10] = v37;
  if ( ((gbVec3D *)&g_nCBFormation3[8])->Length() >= 4.0 )
  {
    ((gbVec3D *)&g_nCBFormation3[8])->Normalize();
    v22 = acos(
            *(float *)&g_nCBFormation3[5] * *(float *)&g_nCBFormation3[9]
          + *(float *)&g_nCBFormation3[6] * *(float *)&g_nCBFormation3[10]
          + *(float *)&g_nCBFormation3[4] * *(float *)&g_nCBFormation3[8]);
    if ( *(float *)&g_nCBFormation3[8] < 0.0 )
      v22 = 6.2831855 - v22;
    v23 = v22 * 57.29578;
    flt_17ABCE4 = v23;
    if ( fabs(v23 - *(float *)&this->m_Task[2].SubTask[14].bValid) >= 1.570796370506287 )
    {
      *p_fTemp3 = *(float *)&this->m_Task[2].SubTask[14].eStats;
      LODWORD(this->m_Task[2].SubTask[13].fTemp4) = this->m_Task[2].SubTask[14].dwID;
      this->m_Task[2].SubTask[14].fp[0] = (char *)LODWORD(this->m_Task[2].SubTask[14].fStartTime);
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
      BYTE1(this->m_Task[0].SubTask[0].fTemp1) = 0;
    }
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
    {
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
      BYTE1(this->m_Task[0].SubTask[0].fTemp1) = 0;
    }
    return 0;
  }
  else
  {
    *p_fTemp3 = *(float *)&this->m_Task[2].SubTask[14].eStats;
    LODWORD(this->m_Task[2].SubTask[13].fTemp4) = this->m_Task[2].SubTask[14].dwID;
    this->m_Task[2].SubTask[14].fp[0] = (char *)LODWORD(this->m_Task[2].SubTask[14].fStartTime);
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    return 0;
  }
}

// 0x0050E0D0
int CCBStage::ProcessCommand()
{
  char *v2; // eax
  int fTemp4_low; // edx

  v2 = (char *)this + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
  if ( !v2[506] )
  {
    fTemp4_low = LODWORD(this->m_Task[0].SubTask[0].fTemp4);
    *(_DWORD *)&this->m_Task[2].SubTask[14].bValid = *((_DWORD *)v2 + 108);
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(fTemp4_low) )
      this->m_Task[2].SubTask[13].nEffLinker = 32;
    else
      this->m_Task[2].SubTask[13].nEffLinker = 50;
    ((CCBStageRole *)this)->IsGrabedBy();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
  }
  return 0;
}

// 0x0050E160
int CCBStage::Method_50E160(int nVal)
{
  float *v3; // eax
  int v4; // eax
  double v5; // st7
  double v6; // st6
  long double v7; // st7
  int v8; // edx
  int v10; // [esp+0x8] [ebp-0x8]
  int v11; // [esp+0xC] [ebp-0x4]

  if ( (g_nCBFormation2[15] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation2[15]) |= 1u;
    g_nCBFormation2[12] = 0;
    g_nCBFormation2[13] = 0;
    g_nCBFormation2[14] = 0;
    atexit(nullsub_62);
  }
  if ( (g_nCBFormation2[15] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation2[15]) |= 2u;
    g_nCBFormation2[8] = 0;
    g_nCBFormation2[9] = 0;
    g_nCBFormation2[10] = 1065353216;
    atexit(nullsub_61);
  }
  v3 = (float *)((char *)this + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime));
  if ( !*((_BYTE *)v3 + 506) )
  {
    v4 = *((_DWORD *)&this->m_pCBSystem->m_pAI + (__int64)v3[108]) + 6584;
    *(_DWORD *)&this->m_Task[2].SubTask[14].eStats = *(_DWORD *)v4;
    this->m_Task[2].SubTask[14].dwID = *(_DWORD *)(v4 + 4);
    this->m_Task[2].SubTask[14].fStartTime = *(float *)(v4 + 8);
    v5 = *(float *)&this->m_Task[2].SubTask[14].eStats - this->m_Task[2].SubTask[13].fTemp3;
    *(float *)&v10 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
    v6 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
    g_nCBFormation2[13] = v10;
    *(float *)&v11 = v6;
    *(float *)&g_nCBFormation2[12] = v5;
    g_nCBFormation2[14] = v11;
    ((gbVec3D *)&g_nCBFormation2[12])->Normalize();
    v7 = acos(
           *(float *)&g_nCBFormation2[10] * *(float *)&g_nCBFormation2[14]
         + *(float *)&g_nCBFormation2[9] * *(float *)&g_nCBFormation2[13]
         + *(float *)&g_nCBFormation2[8] * *(float *)&g_nCBFormation2[12]);
    *(float *)&this->m_Task[2].SubTask[14].bValid = v7;
    if ( *(float *)&g_nCBFormation2[12] < 0.0 )
      *(float *)&this->m_Task[2].SubTask[14].bValid = 6.2831855 - v7;
  }
  v8 = 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
  *(float *)&this->m_Task[2].SubTask[14].bValid = *(float *)&this->m_Task[2].SubTask[14].bValid * 57.29578;
  *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + v8 + 1) = 1;
  return 0;
}

// 0x0050E360
int CCBStage::CalcFacingAngle(int nVal)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v6; // st7
  int v7; // eax
  int v9; // [esp+0x8] [ebp-0x8]
  int v10; // [esp+0xC] [ebp-0x4]

  if ( (g_nCBFormation2[7] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation2[7]) |= 1u;
    g_nCBFormation2[4] = 0;
    g_nCBFormation2[5] = 0;
    g_nCBFormation2[6] = 0;
    atexit(nullsub_64);
  }
  if ( (g_nCBFormation2[7] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation2[7]) |= 2u;
    g_nCBFormation2[0] = 0;
    g_nCBFormation2[1] = 0;
    g_nCBFormation2[2] = 1065353216;
    atexit(nullsub_63);
  }
  v3 = (char *)this + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
  if ( !v3[506] )
  {
    *(_DWORD *)&this->m_Task[2].SubTask[14].eStats = *((_DWORD *)v3 + 108);
    this->m_Task[2].SubTask[14].dwID = *((_DWORD *)v3 + 109);
    this->m_Task[2].SubTask[14].fStartTime = *((float *)v3 + 110);
    v4 = *(float *)&this->m_Task[2].SubTask[14].eStats - this->m_Task[2].SubTask[13].fTemp3;
    *(float *)&v9 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
    v5 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
    g_nCBFormation2[5] = v9;
    *(float *)&v10 = v5;
    *(float *)&g_nCBFormation2[4] = v4;
    g_nCBFormation2[6] = v10;
    ((gbVec3D *)&g_nCBFormation2[4])->Normalize();
    v6 = acos(
           *(float *)&g_nCBFormation2[2] * *(float *)&g_nCBFormation2[6]
         + *(float *)&g_nCBFormation2[1] * *(float *)&g_nCBFormation2[5]
         + *(float *)g_nCBFormation2 * *(float *)&g_nCBFormation2[4]);
    *(float *)&this->m_Task[2].SubTask[14].bValid = v6;
    if ( *(float *)&g_nCBFormation2[4] < 0.0 )
      *(float *)&this->m_Task[2].SubTask[14].bValid = 6.2831855 - v6;
  }
  v7 = 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
  *(float *)&this->m_Task[2].SubTask[14].bValid = *(float *)&this->m_Task[2].SubTask[14].bValid * 57.29578;
  *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + v7 + 1) = 1;
  return 0;
}

// 0x0050E550
int CCBStage::ResolveActionEffect(int nVal)
{
  char v3; // bl
  char *v4; // ebp
  int i; // edi
  float fTemp4; // eax
  unsigned int v7; // ebp
  float v8; // eax
  int v10; // edi
  CScreenMode *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  tagRoleState *inited; // eax
  int v18; // eax
  int v19; // edi
  unsigned int v20; // ecx
  int *v21; // ecx
  int v22; // eax
  CScreenMode *Instance; // eax
  int nEffLinker; // ecx
  float v25; // eax
  int v26; // edi
  float *v27; // edi
  const void *v28; // [esp-0x8] [ebp-0x44]
  const void *v29; // [esp-0x8] [ebp-0x44]
  const void *v30; // [esp-0x8] [ebp-0x44]
  void *v31; // [esp+0x0] [ebp-0x3C]
  char Buffer[32]; // [esp+0x1C] [ebp-0x20] BYREF

  v3 = 1;
  v4 = (char *)this + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
  if ( !v4[506] )
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.25);
    if ( v4[461] )
    {
      for ( i = 0; i < 11; ++i )
      {
        if ( v4[i + 473] && ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(i) )
          v3 = 0;
      }
      if ( !v3 )
        goto LABEL_10;
    }
    else if ( ((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(*((_DWORD *)v4 + 114)) )
    {
      goto LABEL_10;
    }
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
LABEL_10:
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
    {
      fTemp4 = this->m_Task[0].SubTask[0].fTemp4;
      this->m_Task[2].SubTask[13].nEffLinker = 29;
      if ( LODWORD(fTemp4) == 2 )
      {
        if ( *(_BYTE *)(::Buffer.m_configData[17] + 613) == 7 )
        {
          this->m_Task[2].SubTask[13].nEffLinker = 30;
        }
        else
        {
          v7 = *((_DWORD *)v4 + 114);
          if ( v7 <= 0xA )
            ((CCBStageRole *)this)->SetBladeTime(v7);
        }
      }
      v8 = this->m_Task[0].SubTask[0].fTemp4;
      if ( LODWORD(v8) == 3 && *(_BYTE *)(g_SceneMgr.m_partyInitData[27] + 613) == 4 )
        this->m_Task[2].SubTask[13].nEffLinker = 30;
      if ( LODWORD(v8) == 4 && *(_BYTE *)(((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[8] + 613) == 2 )
        this->m_Task[2].SubTask[13].nEffLinker = 30;
    }
    else
    {
      this->m_Task[2].SubTask[13].nEffLinker = 53;
    }
    ((CCBStageRole *)this)->GetPointerPos();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    todo_408BD0(v31);
    return 0;
  }
  v10 = nVal;
  if ( nVal != this->m_Task[2].SubTask[14].nEffLinker && nVal != *(_DWORD *)&this->m_Task[2].SubTask[14].bEff1Started )
    goto LABEL_68;
  if ( !((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
  {
    inited = ((CCBRoleState *)this->m_pCBSystem->m_pUtil->m_pRoleState)->InitUI(LODWORD(this->m_Task[0].SubTask[0].fTemp4));
    ((PAL_GDB *)&g_pGDB)->_PAL_GDB(inited->dwID);
    v19 = (__int64)*(float *)(v18 + 784);
    if ( v19 )
    {
      v20 = *((_DWORD *)v4 + 114);
      if ( v20 <= 0xA )
      {
        v21 = (int *)(*((_DWORD *)&this->m_pCBSystem->m_pAI + v20) + 6596);
        switch ( v19 )
        {
          case 121:
            v22 = 324;
            goto LABEL_66;
          case 123:
            v22 = 325;
            goto LABEL_66;
          case 124:
            v22 = 326;
            goto LABEL_66;
          case 125:
            v22 = 327;
            goto LABEL_66;
          case 127:
            v22 = 328;
            goto LABEL_66;
          case 128:
            v22 = 329;
            goto LABEL_66;
          case 129:
            v22 = 330;
            goto LABEL_66;
          case 130:
            v22 = 331;
            goto LABEL_66;
          case 131:
            v22 = 332;
            goto LABEL_66;
          case 132:
            v22 = 333;
            goto LABEL_66;
          case 133:
            v22 = 334;
            goto LABEL_66;
          case 134:
            v22 = 335;
LABEL_66:
            ((CEffMgr *)this->m_pCBSystem->m_pUtil->m_pEffMgr)->Init(v22, *v21, 0, v21[2], 0);
            break;
          default:
            break;
        }
      }
      sprintf(Buffer, "%s%03d", "wd", v19);
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(Buffer, 1);
    }
LABEL_68:
    v10 = nVal;
    goto LABEL_69;
  }
  if ( !LODWORD(this->m_Task[0].SubTask[0].fTemp4) )
  {
    if ( ((CCBRoleState *)this->m_pRoleState)->InitUI(0)->bMagicSword )
      v28 = &g_EffMgr;
    else
      v28 = &g_EffMgr;
    v11 = CScreenMode::GetInstance();
    ((CScreenMode *)v11)->AudioSetPosition(v28, 1);
  }
  if ( LODWORD(this->m_Task[0].SubTask[0].fTemp4) == 1 )
  {
    v12 = CScreenMode::GetInstance();
    ((CScreenMode *)v12)->AudioSetPosition(&g_EffMgr, 1);
  }
  if ( LODWORD(this->m_Task[0].SubTask[0].fTemp4) != 2 )
    goto LABEL_42;
  if ( *(_BYTE *)(::Buffer.m_configData[17] + 613) == 7 )
  {
    v29 = &g_EffMgr;
LABEL_41:
    v13 = CScreenMode::GetInstance();
    ((CScreenMode *)v13)->AudioSetPosition(v29, 1);
    goto LABEL_42;
  }
  if ( nVal == *(_DWORD *)&this->m_Task[2].SubTask[14].bEff1Started )
  {
    v29 = &g_EffMgr;
    goto LABEL_41;
  }
LABEL_42:
  if ( LODWORD(this->m_Task[0].SubTask[0].fTemp4) == 3 )
  {
    if ( *(_BYTE *)(g_SceneMgr.m_partyInitData[27] + 613) == 4 )
      v30 = &g_EffMgr;
    else
      v30 = &g_EffMgr;
    v14 = CScreenMode::GetInstance();
    ((CScreenMode *)v14)->AudioSetPosition(v30, 1);
  }
  if ( LODWORD(this->m_Task[0].SubTask[0].fTemp4) == 4 )
  {
    if ( *(_BYTE *)(((RoleSystem *)&stru_C059A0)->m_partyActor.m_dwMatMsg[8] + 613) == 2 )
    {
      v15 = CScreenMode::GetInstance();
      ((CScreenMode *)v15)->AudioSetPosition(&g_EffMgr, 1);
    }
    else
    {
      v16 = CScreenMode::GetInstance();
      ((CScreenMode *)v16)->AudioSetPosition(&g_EffMgr, 1);
    }
  }
LABEL_69:
  nEffLinker = this->m_Task[2].SubTask[14].nEffLinker;
  if ( v10 != nEffLinker && v10 != *(_DWORD *)&this->m_Task[2].SubTask[14].bEff1Started )
    goto LABEL_92;
  v25 = this->m_Task[0].SubTask[0].fTemp4;
  if ( SLODWORD(v25) < 5 || SLODWORD(v25) >= 11 )
  {
    if ( LODWORD(v25) == 2 )
    {
      if ( v10 == nEffLinker && *(_BYTE *)(::Buffer.m_configData[17] + 613) == 5 )
        goto LABEL_91;
      if ( *(int *)(::Buffer.m_configData[17] + 764) <= 1 )
        goto LABEL_74;
      v26 = *(_DWORD *)(::Buffer.m_configData[17] + 764);
      do
      {
        ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[0].SubTask[2].fTemp4 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime));
        --v26;
      }
      while ( v26 );
    }
    else
    {
      if ( v25 == 0.0
        && ((CCBRoleState *)this->m_pRoleState)->InitUI(0)->bMagicSword
        && *(_DWORD *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[3][5] )
      {
        if ( !*(_DWORD *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[4][1] )
          *(_DWORD *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[4][1] = 1;
        v27 = (float *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[4][3];
        *v27 = (double)*(unsigned int *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[4][1] + *v27;
        if ( *(float *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[4][3] > 200.0 )
          *(_DWORD *)&((CCBRoleState *)this->m_pRoleState)->InitUI(0)->byMagicUseTime[4][3] = 1128792064;
      }
      ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[0].SubTask[2].fTemp4 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime));
    }
    v10 = nVal;
    goto LABEL_91;
  }
  if ( v10 == nEffLinker )
LABEL_74:
    ((CCBRoleState *)this->m_pRoleState)->RandSetEnemyPos(&this->m_Task[0].SubTask[2].fTemp4 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime));
LABEL_91:
  LODWORD(this->m_Task[0].SubTask[3].param.f3) = 3;
LABEL_92:
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
    || v10 == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
  {
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
  }
  return 0;
}

// 0x0050EB00
int CCBStage::ProcessSlotAction(int nVal)
{
  int nEffLinker; // eax
  tagRoleState *inited; // eax
  int v5; // eax
  double v6; // st7
  CScreenMode *Instance; // eax
  char *v9; // [esp-0x8] [ebp-0x38]
  void *v10; // [esp+0x0] [ebp-0x30]
  char Buffer[32]; // [esp+0x10] [ebp-0x20] BYREF

  if ( !*((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.25);
    if ( !((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_Task[0].SubTask[0].fTemp4), 14) )
    {
      nEffLinker = this->m_Task[2].SubTask[13].nEffLinker;
      if ( nEffLinker == 33 || nEffLinker == 43 || nEffLinker == 54 )
      {
        (*(void ( **)(_DWORD, _DWORD))(**((_DWORD **)this->m_Task[0].SubTask[1].fp[1] + 4) + 24))(
          *((_DWORD *)this->m_Task[0].SubTask[1].fp[1] + 4),
          0);
      }
      else
      {
        if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
          this->m_Task[2].SubTask[13].nEffLinker = LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_Task[0].SubTask[0].fTemp4))->byMagicUseTime[8][5]) != 0
                                                 ? 43
                                                 : 33;
        else
          this->m_Task[2].SubTask[13].nEffLinker = 54;
        ((CCBStageRole *)this)->GetPointerPos();
      }
    }
    if ( ((CCBRoleState *)this->m_pRoleState)->IsActive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
    {
      if ( !LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_Task[0].SubTask[0].fTemp4))->byMagicUseTime[8][5]) )
      {
        switch ( LODWORD(this->m_Task[0].SubTask[0].fTemp4) )
        {
          case 0:
            v9 = "we015";
            goto LABEL_22;
          case 1:
            v9 = "we016";
            goto LABEL_22;
          case 2:
            v9 = "we017";
            goto LABEL_22;
          case 3:
            v9 = "we018";
            goto LABEL_22;
          case 4:
            v9 = "we019";
            goto LABEL_22;
          default:
            goto LABEL_23;
        }
        goto LABEL_23;
      }
      v9 = (char *)&g_EffMgr;
    }
    else
    {
      ((CEffectSystem *)this->m_pCBSystem->m_pUtil->m_pEffectSimple)->Destroy();
      inited = ((CCBRoleState *)this->m_pCBSystem->m_pUtil->m_pRoleState)->InitUI(LODWORD(this->m_Task[0].SubTask[0].fTemp4));
      ((PAL_GDB *)&g_pGDB)->_PAL_GDB(inited->dwID);
      v6 = *(float *)(v5 + 788);
      if ( !(unsigned int)(__int64)v6 )
      {
LABEL_23:
        *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
        todo_408BD0(v10);
        return 0;
      }
      sprintf(Buffer, "%s%03d", "we", (unsigned int)(__int64)v6);
      v9 = Buffer;
    }
LABEL_22:
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v9, 1);
    goto LABEL_23;
  }
  if ( ((CCBRoleState *)this->m_pRoleState)->GetRoleField(LODWORD(this->m_Task[0].SubTask[0].fTemp4), 14) )
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
      LOBYTE(this->m_Task[0].SubTask[0].fTemp1) = 0;
  }
  if ( nVal == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
      LOBYTE(this->m_Task[0].SubTask[0].fTemp1) = 0;
  }
  return 0;
}

// 0x0050EF60
int CCBStage::UpdateActionTimers(float fVal)
{
  void *v4; // [esp+0x0] [ebp-0x8]

  if ( *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || LODWORD(fVal) == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
    {
      ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    }
    return 0;
  }
  else
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
    if ( LODWORD(this->m_Task[0].SubTask[0].fTemp4) > 4 )
    {
      if ( (int)*(&this->m_Task[0].SubTask[2].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) == 1 )
      {
        this->m_Task[2].SubTask[13].nEffLinker = 56;
      }
      else if ( (int)*(&this->m_Task[0].SubTask[2].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) == 2 )
      {
        this->m_Task[2].SubTask[13].nEffLinker = 57;
      }
      else
      {
        this->m_Task[2].SubTask[13].nEffLinker = 55;
      }
    }
    else
    {
      this->m_Task[2].SubTask[13].nEffLinker = 35;
    }
    ((CCBStageRole *)this)->GetPointerPos();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    todo_408BD0(v4);
    *((_DWORD *)&this->m_Task[0].SubTask[3].param.f3 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)) = 3;
    return 0;
  }
}

// 0x0050F080
int CCBStage::AnimCallback_Attack(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || nVal == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
    {
      ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    }
    return 0;
  }
  else
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.25);
    if ( this->m_Task[0].SubTask[3].fp[24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime)] == (char *)4101 )
      this->m_Task[2].SubTask[13].nEffLinker = 37;
    else
      this->m_Task[2].SubTask[13].nEffLinker = 36;
    *(float *)&this->m_Task[2].SubTask[14].bValid = this->m_Task[2].SubTask[14].param.f1;
    ((CCBStageRole *)this)->GetPointerPos();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    todo_408BD0(v4);
    return 0;
  }
}

// 0x0050F150
int CCBStage::AnimCallback_UseItem(int nVal)
{
  float f1; // ecx
  void *v5; // [esp+0x0] [ebp-0x4]

  if ( *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || nVal == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
    {
      ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    }
    return 0;
  }
  else
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.25);
    f1 = this->m_Task[2].SubTask[14].param.f1;
    this->m_Task[2].SubTask[13].nEffLinker = 38;
    *(float *)&this->m_Task[2].SubTask[14].bValid = f1;
    ((CCBStageRole *)this)->GetPointerPos();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    todo_408BD0(v5);
    return 0;
  }
}

// 0x0050F310
int CCBStage::AnimCallback_Throw(int nVal, int nVal2)
{
  int v3; // edi
  int v6; // edi
  bool v7; // bl
  int v8; // [esp-0x8] [ebp-0x10]
  void *v9; // [esp+0x0] [ebp-0x8]

  if ( *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    v8 = v3;
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || nVal == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
    {
      v6 = (int)*(&this->m_Task[0].SubTask[2].fTemp1 + 24 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime));
      v7 = ((CCBStageRole *)*((CCBStageRole **)&this->m_pCBSystem->m_pAI + v6))->ForceEndTaskByPFN();
      if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(v6)
        || !v7
        || !((CCBStage *)this->m_pCBSystem)->GetTaskState(v6, v8) )
      {
        ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
        *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
      }
    }
    return 0;
  }
  else
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.25);
    this->m_Task[2].SubTask[13].nEffLinker = 42;
    ((CCBStageRole *)this)->IsGrabedBy();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    todo_408BD0(v9);
    return 0;
  }
}

// 0x0050F410
int CCBStage::AnimCallback_CastMagic(int nVal)
{
  float f1; // ecx
  void *v5; // [esp+0x0] [ebp-0x4]

  if ( *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || nVal == LODWORD(this->m_Task[2].SubTask[14].param.f3) )
    {
      ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    }
    return 0;
  }
  else
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.25);
    f1 = this->m_Task[2].SubTask[14].param.f1;
    this->m_Task[2].SubTask[13].nEffLinker = 40;
    *(float *)&this->m_Task[2].SubTask[14].bValid = f1;
    ((CCBStageRole *)this)->GetPointerPos();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    todo_408BD0(v5);
    return 0;
  }
}

// 0x0050F4C0
int CCBStage::AnimCallback_WaitCmd(int nVal)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) )
  {
    if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || ((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen)->IsCmdReady(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || ((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen)->IsCmdEmpty(LODWORD(this->m_Task[0].SubTask[0].fTemp4))
      || (unsigned __int8)((CCBRoleState *)this->m_pRoleState)->GetForce(0) )
    {
      *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
    }
    return 0;
  }
  else
  {
    ((CCBStageRole *)this)->ClearBadPushTask(0.0099999998);
    this->m_Task[2].SubTask[13].nEffLinker = 48;
    ((CCBStageRole *)this)->IsGrabedBy();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
    todo_408BD0(v4);
    return 0;
  }
}

// 0x0050F590
int CCBStage::AnimCallback_MoveTo(int nVal)
{
  char *v3; // eax
  double v4; // st7
  double v5; // st6
  long double v6; // st7
  double m_DeltaTime; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st7
  double v11; // st6
  double v12; // st7
  double v13; // st7
  int v15; // [esp+0xC] [ebp-0x14]
  float v16; // [esp+0xC] [ebp-0x14]
  int v17; // [esp+0x10] [ebp-0x10]
  float v18; // [esp+0x10] [ebp-0x10]
  float v19; // [esp+0x14] [ebp-0xC]
  float v20; // [esp+0x18] [ebp-0x8]
  int v21; // [esp+0x18] [ebp-0x8]
  int v22; // [esp+0x1C] [ebp-0x4]

  if ( (g_nCBFormation1[11] & 1) == 0 )
  {
    LOBYTE(g_nCBFormation1[11]) |= 1u;
    g_nCBFormation1[8] = 0;
    g_nCBFormation1[9] = 0;
    g_nCBFormation1[10] = 0;
    atexit(nullsub_67);
  }
  if ( (g_nCBFormation1[11] & 2) == 0 )
  {
    LOBYTE(g_nCBFormation1[11]) |= 2u;
    g_nCBFormation1[4] = 0;
    g_nCBFormation1[5] = 0;
    g_nCBFormation1[6] = 1065353216;
    atexit(nullsub_66);
  }
  if ( (g_nCBFormation1[11] & 4) == 0 )
  {
    LOBYTE(g_nCBFormation1[11]) |= 4u;
    g_nCBFormation1[0] = 0;
    g_nCBFormation1[1] = 0;
    g_nCBFormation1[2] = 0;
    atexit(nullsub_65);
  }
  v3 = (char *)this + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime);
  if ( !v3[506] )
  {
    *(_DWORD *)&this->m_Task[2].SubTask[14].eStats = *((_DWORD *)v3 + 108);
    this->m_Task[2].SubTask[14].dwID = *((_DWORD *)v3 + 109);
    this->m_Task[2].SubTask[14].fStartTime = *((float *)v3 + 110);
    v4 = *(float *)&this->m_Task[2].SubTask[14].eStats - this->m_Task[2].SubTask[13].fTemp3;
    *(float *)&v15 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
    v5 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
    g_nCBFormation1[9] = v15;
    *(float *)&v17 = v5;
    *(float *)&g_nCBFormation1[8] = v4;
    g_nCBFormation1[10] = v17;
    ((gbVec3D *)&g_nCBFormation1[8])->Normalize();
    v6 = acos(
           *(float *)&g_nCBFormation1[6] * *(float *)&g_nCBFormation1[10]
         + *(float *)&g_nCBFormation1[5] * *(float *)&g_nCBFormation1[9]
         + *(float *)&g_nCBFormation1[4] * *(float *)&g_nCBFormation1[8]);
    *(float *)&this->m_Task[2].SubTask[14].bValid = v6;
    if ( *(float *)&g_nCBFormation1[8] < 0.0 )
      *(float *)&this->m_Task[2].SubTask[14].bValid = 6.2831855 - v6;
    *(float *)&this->m_Task[2].SubTask[14].bValid = *(float *)&this->m_Task[2].SubTask[14].bValid * 57.29578;
    LODWORD(this->m_Task[2].SubTask[14].fWaitTime) = g_nCBFormation1[8];
    LODWORD(this->m_Task[2].SubTask[14].fTime) = g_nCBFormation1[9];
    this->m_Task[2].SubTask[14].dwReturn = g_nCBFormation1[10];
    this->m_Task[2].SubTask[14].fWaitTime = this->m_Task[2].SubTask[14].fWaitTime * 380.0;
    this->m_Task[2].SubTask[14].fTime = this->m_Task[2].SubTask[14].fTime * 380.0;
    *(float *)&this->m_Task[2].SubTask[14].dwReturn = *(float *)&this->m_Task[2].SubTask[14].dwReturn * 380.0;
    this->m_Task[2].SubTask[13].nEffLinker = 52;
    ((CCBStageRole *)this)->IsGrabedBy();
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 2) = 1;
  }
  m_DeltaTime = this->m_pCBSystem->m_pUtil->m_DeltaTime;
  v19 = this->m_Task[2].SubTask[14].fWaitTime * m_DeltaTime;
  v20 = this->m_Task[2].SubTask[14].fTime * m_DeltaTime;
  v8 = v19 + this->m_Task[2].SubTask[13].fTemp3;
  v16 = this->m_Task[2].SubTask[13].fTemp4 + v20;
  v9 = *(float *)this->m_Task[2].SubTask[14].fp + m_DeltaTime * *(float *)&this->m_Task[2].SubTask[14].dwReturn;
  this->m_Task[2].SubTask[13].fTemp4 = v16;
  v18 = v9;
  this->m_Task[2].SubTask[13].fTemp3 = v8;
  *(float *)this->m_Task[2].SubTask[14].fp = v18;
  v10 = *(float *)&this->m_Task[2].SubTask[14].eStats - this->m_Task[2].SubTask[13].fTemp3;
  *(float *)&v21 = *(float *)&this->m_Task[2].SubTask[14].dwID - this->m_Task[2].SubTask[13].fTemp4;
  v11 = this->m_Task[2].SubTask[14].fStartTime - *(float *)this->m_Task[2].SubTask[14].fp;
  g_nCBFormation1[9] = v21;
  *(float *)&v22 = v11;
  *(float *)&g_nCBFormation1[8] = v10;
  g_nCBFormation1[10] = v22;
  ((gbVec3D *)&g_nCBFormation1[8])->Normalize();
  v12 = acos(
          *(float *)&g_nCBFormation1[6] * *(float *)&g_nCBFormation1[10]
        + *(float *)&g_nCBFormation1[5] * *(float *)&g_nCBFormation1[9]
        + *(float *)&g_nCBFormation1[4] * *(float *)&g_nCBFormation1[8]);
  if ( *(float *)&g_nCBFormation1[8] < 0.0 )
    v12 = 6.2831855 - v12;
  v13 = v12 * 57.29578;
  flt_17ABCFC = v13;
  if ( fabs(v13 - *(float *)&this->m_Task[2].SubTask[14].bValid) >= 1.570796370506287 )
  {
    LOBYTE(((CCBRoleState *)this->m_pRoleState)->InitUI(LODWORD(this->m_Task[0].SubTask[0].fTemp4))[1].dwMagicID[2][5]) = 1;
    ((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen)->GetCmdPtr(LODWORD(this->m_Task[0].SubTask[0].fTemp4));
    ((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen)->InvokeThreadMethod(LODWORD(this->m_Task[0].SubTask[0].fTemp4), 0);
    ((CCBSystem *)this->m_pCBSystem->m_pUtil->m_pAttackSequen)->SetCmdParam(LODWORD(this->m_Task[0].SubTask[0].fTemp4), 1);
    this->m_Task[2].SubTask[13].fTemp3 = *(float *)&this->m_Task[2].SubTask[14].eStats;
    LODWORD(this->m_Task[2].SubTask[13].fTemp4) = this->m_Task[2].SubTask[14].dwID;
    this->m_Task[2].SubTask[14].fp[0] = (char *)LODWORD(this->m_Task[2].SubTask[14].fStartTime);
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
  }
  if ( !((CCBRoleState *)this->m_pRoleState)->IsRoleAlive(LODWORD(this->m_Task[0].SubTask[0].fTemp4)) )
    *((_BYTE *)&this->m_Task[0].SubTask[3].nEffLinker + 96 * LODWORD(this->m_Task[0].SubTask[2].fWaitTime) + 1) = 1;
  return 0;
}

// 0x0051D710
CCBProtectWindow * CCBStage::Create_d710()
{
  int *p_nDestRole; // eax
  tagStageTask *v3; // ebp
  float *p_f2; // ecx
  char **v5; // eax
  char **v6; // ebp
  char **v7; // ebp
  char **v8; // ebp
  char **v9; // eax
  CHAR *p_bValid; // ebp
  tagStageSubTask *v11; // ecx
  unsigned int *p_dwReturn; // eax
  unsigned int *v13; // ebp
  unsigned int *v14; // ebp
  unsigned int *v15; // ebp
  unsigned int *v16; // eax
  float *p_fTemp3; // ebp
  float *p_fTemp4; // eax
  int v19; // ecx
  int *v21; // [esp+0x10] [ebp-0x18]
  char **v22; // [esp+0x10] [ebp-0x18]
  unsigned int *v23; // [esp+0x10] [ebp-0x18]
  int v24; // [esp+0x14] [ebp-0x14]
  int v25; // [esp+0x14] [ebp-0x14]
  int v26; // [esp+0x14] [ebp-0x14]
  int v27; // [esp+0x14] [ebp-0x14]
  int v28; // [esp+0x14] [ebp-0x14]

  this->m_pShadow = (CCBStageShadow *)128;
  this->m_pEffect = (CCBStageEffect *)512;
  this->m_BFARole = 0;
  this->m_BFARound = 0;
  sub_4422E0(&this->m_Task[0].SubTask[1].fTemp3);
  sub_4422E0(&this->m_Task[0].SubTask[3].fTemp1);
  sub_4422E0(&this->m_Task[0].SubTask[5].nEffLinker);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  p_nDestRole = &this->m_Task[2].cmd.nDestRole;
  this->m_Task[2].SubTask[31].nEffLinker = 0;
  *(_DWORD *)&this->m_Task[2].SubTask[31].bEff1Started = 0;
  this->m_Task[2].SubTask[31].fTemp1 = 0.0;
  this->m_Task[2].SubTask[31].fTemp2 = 0.0;
  BYTE1(this->m_Task[2].SubTask[31].fTemp3) = 1;
  BYTE2(this->m_Task[2].SubTask[31].fTemp3) = 0;
  this->m_Task[2].cmd.nSrcRole = 0;
  v21 = &this->m_Task[2].cmd.nDestRole;
  v3 = &this->m_Task[3];
  v24 = 396;
  while ( 1 )
  {
    *p_nDestRole = 0;
    lstrcpyA(&v3[-1].cmd.bMultiSrcRole, g_szSceneUIText);
    lstrcpyA((LPSTR)v3, g_szSceneUIText);
    lstrcpyA((LPSTR)&v3->SubTask[0].fp[3] + 2, g_szSceneUIText);
    lstrcpyA((LPSTR)&v3->SubTask[0].param, g_szSceneUIText);
    LOBYTE(v3->SubTask[7].fp[0]) = 0;
    memset(&v3->SubTask[7].fTime, 0, 0x18u);
    LOBYTE(v3->SubTask[9].fWaitTime) = 0;
    BYTE1(v3->SubTask[9].fWaitTime) = 0;
    v3->SubTask[9].fTime = NAN;
    v3 = (tagStageTask *)((char *)v3 + 808);
    v21 += 202;
    if ( !--v24 )
      break;
    p_nDestRole = v21;
  }
  this->m_Task[124].SubTask[18].fp[1] = 0;
  this->m_Task[124].SubTask[18].fp[2] = 0;
  this->m_Task[124].SubTask[18].fp[3] = 0;
  *(_DWORD *)&this->m_Task[124].SubTask[18].eStats = 1;
  this->m_Task[124].SubTask[18].dwID = 1;
  LODWORD(this->m_Task[124].SubTask[18].fStartTime) = 1;
  this->m_Task[124].SubTask[18].fWaitTime = 0.0;
  this->m_Task[124].SubTask[18].fTime = 0.0;
  HIWORD(this->m_Task[124].SubTask[18].dwReturn) = 0;
  this->m_Task[129].SubTask[27].param.f3 = 0.0;
  v25 = 4;
  this->m_Task[129].SubTask[27].nEffLinker = 0;
  memset(&this->m_Task[129].SubTask[27].bEff1Started, 0, 0x640u);
  memset(&this->m_Task[131].SubTask[1].fTemp4, 0, 0x190u);
  memset(&this->m_Task[130].SubTask[14].fTemp2, 0, 0x640u);
  this->m_Task[124].SubTask[18].dwReturn = 0;
  p_f2 = &this->m_Task[131].SubTask[7].param.f2;
  this->m_Task[131].SubTask[7].fp[3] = 0;
  *(_DWORD *)&this->m_Task[131].SubTask[7].eStats = 0;
  this->m_Task[131].SubTask[7].dwID = 0;
  v5 = &this->m_Task[131].SubTask[8].fp[1];
  do
  {
    v6 = v5 - 6;
    *p_f2 = 0.0;
    *(v5 - 8) = 0;
    *(v5 - 7) = 0;
    *v6 = 0;
    p_f2 += 12;
    v6[1] = 0;
    v6[2] = 0;
    v7 = v5 - 3;
    *(v5 - 3) = 0;
    v7[1] = 0;
    v7[2] = 0;
    v8 = v5;
    v5 += 12;
    *v8 = 0;
    v8[1] = 0;
    v8[2] = 0;
    --v25;
  }
  while ( v25 );
  LOBYTE(this->m_Task[131].SubTask[7].fStartTime) = 0;
  BYTE1(this->m_Task[131].SubTask[7].fStartTime) = 0;
  BYTE2(this->m_Task[131].SubTask[7].fStartTime) = 0;
  HIBYTE(this->m_Task[131].SubTask[7].fStartTime) = 0;
  LOBYTE(this->m_Task[131].SubTask[7].fWaitTime) = 0;
  BYTE1(this->m_Task[131].SubTask[7].fWaitTime) = 0;
  BYTE2(this->m_Task[131].SubTask[7].fWaitTime) = 0;
  this->m_Task[131].SubTask[7].fTime = 1.0;
  this->m_Task[131].SubTask[7].dwReturn = 0;
  *(_DWORD *)&this->m_Task[131].SubTask[7].bValid = 0;
  this->m_Task[131].SubTask[7].param.f1 = 0.0;
  this->m_Task[131].SubTask[10].fp[0] = 0;
  memset(&this->m_Task[131].SubTask[7].param.f2, 0, 0xC0u);
  v9 = &this->m_Task[131].SubTask[10].fp[1];
  v26 = 200;
  v22 = &this->m_Task[131].SubTask[10].fp[1];
  p_bValid = &this->m_Task[131].SubTask[10].bValid;
  while ( 1 )
  {
    *v9 = 0;
    lstrcpyA(p_bValid - 32, g_szSceneUIText);
    lstrcpyA(p_bValid, g_szSceneUIText);
    lstrcpyA(p_bValid + 30, g_szSceneUIText);
    lstrcpyA(p_bValid + 60, g_szSceneUIText);
    p_bValid[576] = 0;
    memset(p_bValid + 608, 0, 0x18u);
    p_bValid[764] = 0;
    p_bValid[765] = 0;
    *((_DWORD *)p_bValid + 192) = -1;
    p_bValid += 808;
    v22 += 202;
    if ( !--v26 )
      break;
    v9 = v22;
  }
  v11 = &this->m_Task[192].SubTask[24];
  LODWORD(this->m_Task[192].SubTask[23].fWaitTime) = 1;
  LODWORD(this->m_Task[192].SubTask[23].fTime) = 1;
  this->m_Task[192].SubTask[23].dwReturn = 1;
  *(_DWORD *)&this->m_Task[192].SubTask[23].bValid = 0;
  this->m_Task[192].SubTask[23].param.f1 = 0.0;
  this->m_Task[192].SubTask[23].param.f2 = 0.0;
  this->m_Task[192].SubTask[23].param.f3 = 0.0;
  p_dwReturn = &this->m_Task[192].SubTask[24].dwReturn;
  v27 = 4;
  do
  {
    v13 = p_dwReturn - 6;
    v11->fp[0] = 0;
    *(p_dwReturn - 8) = 0;
    *(p_dwReturn - 7) = 0;
    *v13 = 0;
    v11 = (tagStageSubTask *)((char *)v11 + 48);
    v13[1] = 0;
    v13[2] = 0;
    v14 = p_dwReturn - 3;
    *(p_dwReturn - 3) = 0;
    v14[1] = 0;
    v14[2] = 0;
    v15 = p_dwReturn;
    p_dwReturn += 12;
    *v15 = 0;
    v15[1] = 0;
    v15[2] = 0;
    --v27;
  }
  while ( v27 );
  LOBYTE(this->m_Task[192].SubTask[23].nEffLinker) = 0;
  BYTE1(this->m_Task[192].SubTask[23].nEffLinker) = 0;
  BYTE2(this->m_Task[192].SubTask[23].nEffLinker) = 0;
  HIBYTE(this->m_Task[192].SubTask[23].nEffLinker) = 0;
  this->m_Task[192].SubTask[23].bEff1Started = 0;
  this->m_Task[192].SubTask[23].bEff2Started = 0;
  this->m_Task[192].SubTask[23].bEffWorked = 0;
  this->m_Task[192].SubTask[23].fTemp1 = 1.0;
  this->m_Task[192].SubTask[23].fTemp2 = 0.0;
  this->m_Task[192].SubTask[23].fTemp3 = 0.0;
  this->m_Task[192].SubTask[23].fTemp4 = 0.0;
  this->m_Task[192].SubTask[26].fTime = 0.0;
  memset(&this->m_Task[192].SubTask[24], 0, 0xC0u);
  v16 = &this->m_Task[192].SubTask[26].dwReturn;
  v28 = 200;
  v23 = &this->m_Task[192].SubTask[26].dwReturn;
  p_fTemp3 = &this->m_Task[192].SubTask[26].fTemp3;
  while ( 1 )
  {
    *v16 = 0;
    lstrcpyA((LPSTR)p_fTemp3 - 32, g_szSceneUIText);
    lstrcpyA((LPSTR)p_fTemp3, g_szSceneUIText);
    lstrcpyA((LPSTR)p_fTemp3 + 30, g_szSceneUIText);
    lstrcpyA((LPSTR)p_fTemp3 + 60, g_szSceneUIText);
    *((_BYTE *)p_fTemp3 + 576) = 0;
    memset(p_fTemp3 + 152, 0, 0x18u);
    *((_BYTE *)p_fTemp3 + 764) = 0;
    *((_BYTE *)p_fTemp3 + 765) = 0;
    p_fTemp3[192] = NAN;
    p_fTemp3 += 202;
    v23 += 202;
    if ( !--v28 )
      break;
    v16 = v23;
  }
  this->m_Task[254].SubTask[7].fp[0] = 0;
  LODWORD(this->m_Task[254].SubTask[6].fTemp2) = 1;
  LODWORD(this->m_Task[254].SubTask[6].fTemp3) = 1;
  LODWORD(this->m_Task[254].SubTask[6].fTemp4) = 1;
  LOBYTE(this->m_Task[254].SubTask[7].fp[1]) = 0;
  ((ARC_PlayerAtt *)&this->m_Task[254].SubTask[7].fp[2])->Refresh();
  ((ARC_PlayerAtt *)&this->m_Task[254].SubTask[24].eStats)->Refresh();
  p_fTemp4 = &this->m_Task[2].SubTask[31].fTemp4;
  v19 = 4;
  do
  {
    p_fTemp4[84382] = 0.0;
    *p_fTemp4++ = 0.0;
    --v19;
  }
  while ( v19 );
  return (CCBProtectWindow *)this;
}

// 0x0051DDA0
void CCBStage::ShowWindow()
{
  BYTE1(this->m_Task[2].SubTask[31].fTemp3) = 1;
  ((UIRoleDialog *)&this->m_Task[254].SubTask[24].eStats)->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_Task[254].SubTask[7].fp[2])->_UIRoleDialog();
  ((UIStatic *)&this->m_Task[2].SubTask[28].param.f2)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[25].bValid)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[22].fTime)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[19].fStartTime)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[16])->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[12].fTemp3)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[9].fTemp1)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[6].bValid)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[3].fTime)->_UIStatic();
  ((UIStatic *)&this->m_Task[2].SubTask[0].fStartTime)->_UIStatic();
  ((UIStatic *)&this->m_Task[1].SubTask[29].fTemp3)->_UIStatic();
  ((UIStatic *)&this->m_Task[1].SubTask[26].fTemp1)->_UIStatic();
  ((UIStatic *)&this->m_Task[1].SubTask[23].nEffLinker)->_UIStatic();
  ((UIStatic *)&this->m_Task[1].SubTask[20].fTime)->_UIStatic();
  ((UIStatic *)&this->m_Task[1].SubTask[17].fStartTime)->_UIStatic();
  ((UIStatic *)&this->m_Task[1].SubTask[14].eStats)->_UIStatic();
  ((UIStatic *)&this->m_Task[1].SubTask[11].fp[2])->_UIStatic();
  ((UICaption *)&this->m_Task[1].SubTask[6].param.f2)->Destroy2();
  ((UICaption *)&this->m_Task[1].SubTask[2].fStartTime)->Destroy2();
  ((UICaption *)&this->m_Task[0].SubTask[30].fTemp3)->Destroy2();
  ((UIStatic *)&this->m_Task[0].SubTask[27].fTemp1)->_UIStatic();
  ((UICaption *)&this->m_Task[0].SubTask[23].bValid)->Destroy2();
  ((UICaption *)&this->m_Task[0].SubTask[19].eStats)->Destroy2();
  ((UIFrameWnd *)&this->m_Task[0].SubTask[5].nEffLinker)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Task[0].SubTask[3].fTemp1)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Task[0].SubTask[1].fTemp3)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}
