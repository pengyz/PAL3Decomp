#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBUI.h"

// Forward declarations for unnamed functions
int sub_43FD90(float *_this, int a2); // from annotations
void sub_43FDB0(float *_this, int a2); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_4431B0(...);
int sub_445D20(_DWORD *_this, int a2, int a3); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445ED0(int a2, int a3); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_445FE0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
unsigned int sub_4A8230(unsigned int a2, int a3); // from annotations
bool sub_4AB560(_DWORD *_this, int a2, int a3); // from annotations
int sub_4CE030(...);
int sub_4CE5C0(...);
int sub_4E95A0(...);
int sub_4EB6F0(...);
int sub_4EB8D0(...);
int sub_511630(...);
int sub_516170(...);
int sub_51A400(...);
char __stdcall sub_51CC20(int **a1); // from annotations
void __cdecl todo_401800(void);

void CreateDigitPair(int nVal, UIWnd **ppTens, UIWnd **ppOnes, const char *pszTexBase, char bFlag); // from annotations
double EditBox_GetFloat(HWND hWnd); // from annotations
int EditBox_GetInt(HWND hWnd); // from annotations
BOOL EditBox_IsModified(HWND hWnd); // from annotations
LRESULT EditBox_SetFloat(HWND hWnd, float fValue); // from annotations
LRESULT EditBox_SetInt(HWND hWnd, int nValue); // from annotations
LRESULT EditBox_SetReadOnly(HWND hWnd, BOOL bReadOnly); // from annotations
char * GetEditBoxText(HWND hWnd); // from annotations
BOOL __stdcall MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint); // from annotations
int * SortTripletsByField(int *p_DWORD, int *p_DWORD2, int nVal); // from annotations

// Unnamed globals (extern)
extern CHAR asc_5B74B4[2];
extern CHAR asc_5E9090[];
extern char byte_17ACB08[128];
extern char byte_1895559;
extern char byte_5967B0[3];
extern char byte_ABC00C;
extern char byte_ABE00B;
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DC7D3C[512];
extern CHAR byte_DCF43C[256];
extern int dword_5D87F8;
extern int dword_5D87FC;
extern int dword_C10CC4;
extern int dword_DC853C;
extern int dword_DC863C;
extern int dword_DC873C;
extern int dword_DC883C;
extern int dword_DC893C;
extern int dword_DC923C;
extern int dword_DC933C;
extern int dword_DCE93C;
extern int dword_DCF63C;
extern int dword_DCFE3C;
extern const char * off_5706AC;
extern const char * off_5706C0;
extern const char * off_5706CC;
extern void * off_5CF1F0;
extern void * off_5E7F20;
extern TextureLibDataBase stru_1894B78;
extern RoleSystem stru_C059A0;
extern PalScript stru_C11720;
extern int unk_5D87F0;
extern char unk_5D8848;
extern CHAR unk_5D88FC;
extern char unk_5D89B0;
extern CHAR unk_5D8B14;
extern CHAR unk_5D8B3C;
extern CHAR unk_5D8BE4;
extern CHAR unk_5D8C20;
extern char unk_5DFDB4[];
extern char unk_5DFDC0[];
extern char unk_5DFDCC[];
extern unsigned int unk_5DFDEC;

// 0x00441040
void CCBUI::SetTooltip(const char *szText)
{
  if ( szText )
    strncpy((char *)&this->m_pAttackSequenFace[4], szText, 0x7Fu);
  else
    memset(&this->m_pAttackSequenFace[4], 0, 0x80u);
}

// 0x00441070
void CCBUI::SetRect(RECT *pRect)
{
  this->m_pAttackSequenBack = (UIStatic *)pRect->left;
}

// 0x00441380
int CCBUI::ShowEffect(int nY, int nWidth, int nHeight)
{
  return sub_445FA0(&this->m_pAttackSequenBack);
}

// 0x004413C0
gbVFileSystem * CCBUI::LoadTextureSequence(gbVFileSystem *pPath, char bUseAtlas)
{
  gbVFileSystem *result; // eax
  int v4; // esi
  UIStatic **v6; // ebx
  CHAR *v7; // eax
  HWND v8; // [esp+0x0] [ebp-0x124]
  HWND v9; // [esp+0x0] [ebp-0x124]
  int v10; // [esp+0x4] [ebp-0x120]
  int v11; // [esp+0x4] [ebp-0x120]
  int v12; // [esp+0x8] [ebp-0x11C]
  int v13; // [esp+0x8] [ebp-0x11C]
  int v14; // [esp+0xC] [ebp-0x118]
  int v15; // [esp+0xC] [ebp-0x118]
  OpenBaseFile v16; // [esp+0x10] [ebp-0x114] BYREF
  BOOL String1[65]; // [esp+0x14] [ebp-0x110] BYREF
  int v18; // [esp+0x120] [ebp-0x4]

  result = pPath;
  v4 = 0;
  if ( !pPath )
    return result;
  v18 = 0;
  MoveWindow(v8, v10, v12, v14, (int)v16.m_plastsys, String1[0]);
  v6 = &this->m_pRoleStateAttackDec[3];
  while ( 1 )
  {
    sprintf((char *const)String1, "%s%d.tga", (const char *)pPath, v4);
    if ( !bUseAtlas )
      break;
    *v6 = (UIStatic *)((TextureLibDataBase *)&stru_1894B78)->CreateParentData((LPCSTR)String1);
    v7 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV((LPCSTR)String1);
    lstrcpyA((LPSTR)String1, v7);
    if ( !sub_445ED0((int)String1, 1) )
      goto LABEL_9;
LABEL_7:
    ++v4;
    ++v6;
    if ( v4 >= 10 )
      goto LABEL_10;
  }
  if ( sub_445ED0((int)String1, 1) )
    goto LABEL_7;
LABEL_9:
  MoveWindow(v9, v11, v13, v15, (int)v16.m_plastsys, String1[0]);
LABEL_10:
  v18 = -1;
  return result;
}

// 0x004420B0
int CCBUI::VirtualCall()
{
  int v2; // [esp+0x4] [ebp+0x4]

  returnthis->m_pAttackSequenBack->ShowWindow(v2);
}

// 0x00442170
void CCBUI::SetTargetPos(gbVec3D *pPos, gbVec3D *pDir)
{
  float y; // ebx
  UIStatic *v4; // eax
  LONG left; // edx

  *(gbVec3D *)&this->m_pRoleStateDefenceInc[3] = *pPos;
  this->m_pRoleStateDefenceInc[6] = (UIStatic *)LODWORD(pPos[1].x);
  *(gbVec3D *)&this->m_pRoleStateDefenceInc[7] = *pDir;
  this->m_pRoleStateDefenceInc[10] = (UIStatic *)LODWORD(pDir[1].x);
  y = pDir->y;
  v4 = (UIStatic *)(LODWORD(pPos[1].x) - LODWORD(pPos->y));
  if ( (int)v4 <= LODWORD(pDir[1].x) - LODWORD(y) )
    v4 = (UIStatic *)(LODWORD(pDir[1].x) - LODWORD(y));
  left = this->m_rect.left;
  this->m_pRoleStatePanel[2] = v4;
  this->m_pRoleStateDefenceDec[0] = (UIStatic *)(LODWORD(pPos->x) - left);
}

// 0x004421F0
void CCBUI::SetCurPlayer(int nPlayer)
{
  this->m_pRoleStateDefenceDec[0] = (UIStatic *)nPlayer;
}

// 0x00442200
int CCBUI::SetRoleStatePointers(int nVal)
{
  int v2; // edx

  v2 = this->m_rect.top - (int)this->m_pRoleStateDefenceDec[3] / 2;
  this->m_pRoleStateDefenceDec[1] = (UIStatic *)nVal;
  this->m_pRoleStateFace[4] = (UIStatic *)(v2 + nVal);
  this->m_pRoleStateFace[3] = (UIStatic *)(v2 + nVal);
  return v2 + nVal;
}

// 0x00442230
int CCBUI::SetSelection(int nItemIndex)
{
  UIStatic *v2; // edx
  UIStatic *v3; // esi
  int result; // eax
  UIStatic *v5; // [esp+0xC] [ebp+0x8]

  v2 = this->m_pRoleStateDefenceInc[6];
  v3 = this->m_pRoleStateDefenceDec[1];
  this->m_pRoleStateDefenceDec[2] = (UIStatic *)nItemIndex;
  this->m_pRoleStateDefenceDec[3] = v5;
  result = (int)v3 + (_DWORD)v2 + (int)v5 / 2;
  this->m_pRoleStateFace[4] = (UIStatic *)result;
  this->m_pRoleStateFace[3] = (UIStatic *)result;
  return result;
}

// 0x00459F30
__int16 CCBUI::ForwardToPlayerMgr(_WORD *p_WORD)
{
  __int16 result; // ax

  ((PlayerMgr *)*((PlayerMgr **)this + 815))->LoadState(p_WORD);
  ((PropUI *)*((PropUI **)this + 816))->UpdateItemList(p_WORD);
  qmemcpy((void *)(*((_DWORD *)this + 817) + 596), p_WORD, 0x4460u);
  result = p_WORD[1];
  LOWORD(this->m_pRoleStatePanel[3]) = result;
  return result;
}

// 0x00460A00
bool CCBUI::RollProbability(float fProb)
{
  int fProba; // [esp+0xC] [ebp+0x8]
  float fProbb; // [esp+0xC] [ebp+0x8]

  fProba = (__int64)(fProb * 100.0);
  if ( fProba <= 0 )
    return 0;
  fProbb = (double)fProba * 10.24;
  ++*(_DWORD *)&g_TempBuffer1024[912];
  unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
  return (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)fProbb;
}

// 0x00469D00
int CCBUI::SetItemData(int nCol, int nRow, int nData, int nFlags)
{
  gbColorQuad *p_m_fontcolor; // eax
  LONG *p_top; // ecx
  unsigned int Color; // edx
  int result; // eax

  this->m_wndcolor.Color = nRow;
  p_m_fontcolor = &this->m_fontcolor;
  p_top = &this->m_rect.top;
  p_m_fontcolor->Color = nCol;
  *(p_top - 2) = nData;
  *(p_top - 1) = nFlags;
  *p_top = p_m_fontcolor->Color;
  p_top[1] = p_m_fontcolor[1].Color;
  Color = p_m_fontcolor[2].Color;
  result = p_m_fontcolor[3].Color;
  p_top[2] = Color;
  p_top[3] = result;
  return result;
}

// 0x00469D40
unsigned __int8 CCBUI::fn_469D40()
{
  return *((_BYTE *)this + 3284);
}

// 0x00469D50
void CCBUI::AddItem(void *pData, int nCol, int nRow, int nFlags)
{
  CCBUI *v5; // ecx

  v5 = (CCBUI *)((char *)this + 768 * nCol + 128 * nRow + 16 * nFlags + 62836);
// [VFTABLE] *(_DWORD *)pData = v5->__vftable;
  *((_DWORD *)pData + 1) = v5->m_fontcolor.Color;
  *((_DWORD *)pData + 2) = v5->m_wndcolor.Color;
  *((_DWORD *)pData + 3) = v5->m_id;
}

// 0x004AA9C0
void CCBUI::CreatePanelUI()
{
  int v2; // eax
  int v3; // eax
  int v4; // esi
  UIStatic **v5; // edi
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // edi
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // edx
  CScreenMode *Instance; // eax
  const void *v19; // [esp-0x10] [ebp-0x1E4]
  const CHAR *v20; // [esp-0x4] [ebp-0x1D8]
  CHAR v21[128]; // [esp+0x4] [ebp-0x1D0] BYREF
  char Buffer[253]; // [esp+0x84] [ebp-0x150] BYREF
  __int16 v23; // [esp+0x181] [ebp-0x53]
  char v24; // [esp+0x183] [ebp-0x51]
  CHAR String1[64]; // [esp+0x184] [ebp-0x50] BYREF
  float v26; // [esp+0x1C4] [ebp-0x10]
  unsigned int a2; // [esp+0x1C8] [ebp-0xC]
  int v28; // [esp+0x1CC] [ebp-0x8]
  float v29; // [esp+0x1D0] [ebp-0x4]

  if ( *((int *)this + 5862) > 0 )
  {
    switch ( g_nFiveNimbusCount )
    {
      case 0:
        lstrcpyA(String1, (LPCSTR)g_bSlotFlag);
        break;
      case 1:
        v20 = (const CHAR *)&g_bSlotFlag[256];
        goto LABEL_8;
      case 2:
        lstrcpyA(String1, byte_DC3F3C);
        break;
      case 3:
        lstrcpyA(String1, (LPCSTR)&g_bSlotFlag[512]);
        break;
      case 4:
        v20 = byte_DC403C;
LABEL_8:
        lstrcpyA(String1, v20);
        break;
      default:
        break;
    }
    v2 = dword_C10CC4;
    if ( dword_C10CC4 < 0 )
      v2 = 0;
    dword_C10CC4 = v2 + 1;
    if ( v2 + 1 >= 9 )
      dword_C10CC4 = 9;
    memset(this->m_pAttackSequenFace, 0, 0x100u);
    if ( *((_BYTE *)&g_nRoleParam + g_nFiveNimbusCount) || *((_BYTE *)&g_nRoleState + g_nFiveNimbusCount + 1) )
      *((_BYTE *)&g_nActorState + g_nFiveNimbusCount) = 1;
    lstrcpyA(v21, byte_DCF43C);
    v3 = *((_DWORD *)this + 5457);
    v4 = 0;
    if ( v3 > 0 )
    {
      v5 = &this->m_pRoleStateStable[1];
      v6 = (unsigned __int8)g_nActorState;
      a2 = (unsigned __int8)g_nActorState;
      while ( *(_QWORD *)(v5 - 1) != __PAIR64__(BYTE1(g_nActorState), v6)
           || *(_QWORD *)(v5 + 1) != __PAIR64__(BYTE2(g_nActorState), HIBYTE(g_nActorState))
           || v5[3] != (UIStatic *)(unsigned __int8)g_nActor_DE5F9C )
      {
        ++v4;
        v5 += 190;
        if ( v4 >= v3 )
          goto LABEL_25;
        v6 = a2;
      }
      lstrcpyA(v21, (LPCSTR)&this->m_pRoleStateStable[190 * v4 + 5]);
    }
LABEL_25:
    v7 = (int)this->m_pRoleStateSpeedDec[3];
    v8 = 0;
    v9 = 0;
    a2 = 0;
    v26 = 0.0;
    if ( v7 > 0 )
    {
      v10 = (int)this->m_pRoleStateSpeedDec[2];
      if ( v10 > 0 )
        a2 = v7 / v10;
    }
    v11 = (int)this->m_pRoleStateSpeedDec[4];
    if ( v11 > 0 )
    {
      v12 = (int)this->m_pRoleStateSpeedDec[7];
      if ( v12 > 0 )
        v9 = v11 / v12;
    }
    v13 = (int)this->m_pRoleStateSpeedDec[6];
    if ( v13 > 0 )
    {
      v28 = (int)this->m_pRoleStateSpeedDec[8];
      if ( v28 > 0 )
        v26 = ((double)v28 * 0.0099999998 + 0.89999998) * (double)(v13 / v28) * 0.2;
    }
    v14 = (int)this->m_pRoleStateSpeedDec[5];
    if ( v14 > 0 )
    {
      v15 = (int)this->m_pRoleStateSpeedDec[7];
      if ( v15 > 0 )
        v8 = v14 / v15;
    }
    v16 = (int)this->m_pRoleStateSpeedDec[1];
    v28 = (int)this->m_pRoleStateSpeedDec[2] / 2;
    v17 = LODWORD(::Buffer.m_partyActor.m_fAngleDeg) + v16 / 5 - v28;
    v28 = v17;
    if ( v17 > 0 )
    {
      if ( v17 > 20 )
        v28 = 20;
    }
    else
    {
      v28 = 1;
    }
    v29 = ((double)dword_C10CC4 * 0.02 + 1.0) * (double)(int)(a2 + v9 + v8 + (int)v26);
    a2 = (int)v29;
    v29 = COERCE_FLOAT(sub_4A8230(a2, dword_C10CC4));
    memset(Buffer, 0, sizeof(Buffer));
    v23 = 0;
    v24 = 0;
    LOBYTE(this->m_pAttackSequenFace[0]) = 0;
    sprintf(Buffer, "      %s   %s", (const char *)dword_DC933C, String1);
    while ( lstrlenA(Buffer) < 22 )
      lstrcatA(Buffer, asc_5B74B4);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    sprintf(Buffer, "%s %d", (const char *)dword_DCE93C, v28);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, aN);
    sprintf(Buffer, "      %s     %d", (const char *)dword_DCFE3C, v29);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, aN);
    sprintf(Buffer, "      %s %s", (const char *)dword_DC923C, v21);
    lstrcatA((LPSTR)this->m_pAttackSequenFace, Buffer);
    ((UICaption *)((char *)this + 401904))->SetEnable((int)this->m_pAttackSequenFace, 0);
    ((UIRoleSelect *)((char *)this + 401448))->SetByte(1);
    v19 = off_5CF1F0;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v19, 1);
  }
}

// 0x004AB2B0
void CCBUI::DestroyDynamic(int nVal)
{
  UIListBox *v3; // ebx
  int v4; // ebp
  int *v5; // edi
  int *v6; // ebp
  int *v7; // edi
  int *v8; // esi
  int v9; // edx
  int v10; // eax
  int v11; // ebp
  int v12; // edi
  char *i; // [esp+0x10] [ebp-0x44]
  int *v14; // [esp+0x18] [ebp-0x3C]
  int v16; // [esp+0x24] [ebp-0x30]
  int v17; // [esp+0x28] [ebp-0x2C]
  int v18; // [esp+0x2C] [ebp-0x28] BYREF
  int v19; // [esp+0x30] [ebp-0x24]
  int j; // [esp+0x34] [ebp-0x20]
  char v21; // [esp+0x38] [ebp-0x1C]
  void *Block; // [esp+0x3C] [ebp-0x18]
  int *p_DWORD2; // [esp+0x40] [ebp-0x14]
  int v24; // [esp+0x44] [ebp-0x10]
  int v25; // [esp+0x50] [ebp-0x4]
  unsigned int nVala; // [esp+0x58] [ebp+0x4]

  v21 = nVal;
  Block = 0;
  p_DWORD2 = 0;
  v24 = 0;
  v3 = (UIListBox *)((char *)this + 396024);
  v25 = 0;
  v4 = 0;
  if ( ((UIListBox *)((char *)this + 396024))->GetItemData() > 0 )
  {
    v5 = (int *)((char *)this + 21860);
    do
    {
      ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*v5);
      ((RoleSystem *)p_DWORD2)->CheckVisible();
      ++v4;
      v5 += 4;
    }
    while ( v4 < ((UIListBox *)v3)->GetItemData() );
  }
  v14 = p_DWORD2;
  if ( ((char *)p_DWORD2 - (_BYTE *)Block) / 12 > 16 )
  {
    ((ArcLocaleRole *)Block)->ParseLocaleData((char *)p_DWORD2, nVal);
    v6 = (int *)((char *)Block + 192);
    SortTripletsByField((int *)Block, (int *)Block + 48, nVal);
    if ( (char *)Block + 192 != (char *)p_DWORD2 )
    {
      v7 = (int *)((char *)Block + 180);
      for ( i = (char *)Block + 180; ; v7 = (int *)i )
      {
        v8 = v6;
        v18 = *v6;
        v19 = v6[1];
        for ( j = v6[2]; (unsigned __int8)sub_4AB560(&v18, v7); v7 -= 3 )
        {
          *v8 = *v7;
          v8[1] = v7[1];
          v8[2] = v7[2];
          v8 = v7;
        }
        v9 = v19;
        v10 = j;
        *v8 = v18;
        v8[1] = v9;
        v8[2] = v10;
        v6 += 3;
        i += 12;
        if ( v6 == v14 )
          break;
      }
    }
  }
  else
  {
    SortTripletsByField((int *)Block, p_DWORD2, nVal);
  }
  ((UIListBox *)v3)->ClearAll();
  nVala = 0;
  v11 = 0;
  while ( Block && nVala < ((char *)p_DWORD2 - (_BYTE *)Block) / 12 )
  {
    v16 = *(_DWORD *)((char *)Block + v11 + 4);
    v17 = *(_DWORD *)((char *)Block + v11 + 8);
    v12 = ((UIListBox *)v3)->SetItemOffset((char *)(v17 + 4), 0);
    sprintf((char *const)this->m_pAttackSequenFace, &dir[20], v16);
    ((UIListBox *)v3)->SetMouseMoveSel(1, v12, (char *)this->m_pAttackSequenFace, 0);
    sprintf((char *const)this->m_pAttackSequenFace, &dir[20], *(_DWORD *)(v17 + 624));
    ((UIListBox *)v3)->SetMouseMoveSel(2, v12, (char *)this->m_pAttackSequenFace, 0);
    sprintf((char *const)this->m_pAttackSequenFace, &dir[20], *(_DWORD *)(v17 + 608) / 2);
    ((UIListBox *)v3)->SetMouseMoveSel(3, v12, (char *)this->m_pAttackSequenFace, 0);
    v11 += 12;
    ++nVala;
  }
  operator delete(Block);
}

// 0x004DC220
char CCBUI::IsActive()
{
  ((CCBSystem *)this)->ClearAllPointers();
  this->UpdatePanel(0);
  return 1;
}

// 0x004DC250
int CCBUI::UpdatePanel(BOOL bRefresh)
{
  int result; // eax

  if ( bRefresh )
  {
    if ( this->m_pfather
      || !*(_DWORD *)&((CCBRoleState *)this->m_id)->InitUI(0)->byMagicUseTime[3][5]
      || *(float *)&((CCBRoleState *)this->m_id)->InitUI(0)->byMagicUseTime[4][3] <= 199.89999 )
    {
      (***(void ( ****)(_DWORD))(*(_DWORD *)(this->m_rect.left + 1116) + 112))(0);
    }
    else
    {
      (***(void ( ****)(int))(*(_DWORD *)(this->m_rect.left + 1116) + 112))(1);
    }
    ((CCBRoleState *)this->m_id)->GetRoleField((int)this->m_pfather, 15);
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 84));
    ((CCBRoleState *)this->m_id)->GetRoleField((int)this->m_pfather, 16);
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 88));
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 104));
    ((CCBRoleState *)this)->CheckMP();
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 96));
    if ( !this->m_pfather )
      ((CCBRoleState *)this->m_id)->InitUI(0);
    sub_445E50(*(_DWORD *)(*(_DWORD *)(this->m_rect.left + 1116) + 108));
    LOBYTE(result) = ((CCBUI *)this->m_rect.left)->CreateSkillWindow(1);
  }
  else
  {
    LOBYTE(result) = ((CCBUI *)this->m_rect.left)->CreateSkillWindow(0);
  }
  return result;
}

// 0x004DC610
char CCBUI::CountAttackSequences()
{
  int v2; // edi
  UIStatic **v3; // esi
  char result; // al

  v2 = 0;
  v3 = &this->m_pAttackSequenFace[2];
  do
  {
    result = *((_BYTE *)v3 + 60);
    if ( result )
    {
      this->m_pAttackSequenFace[0] = (UIStatic *)v2;
      result = ((int ( *)(char *, _DWORD))*v3)((char *)v3[1] + (_DWORD)this, 0);
    }
    ++v2;
    v3 += 16;
  }
  while ( v2 < 20 );
  this->m_pAttackSequenFace[0] = (UIStatic *)-1;
  return result;
}

// 0x004E04C0
int CCBUI::StepFrame()
{
  int result; // eax

// [VFTABLE] ((CCBSystem *)this->__vftable)->ProcAI(*(float *)&g_RoleSystemCombat.m_teamSlotsB[4]);
// [VFTABLE] if ( LOBYTE(this->__vftable[4].sub_4431B0) != LOBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) )
// [VFTABLE] ((CCBSystem *)this->__vftable)->SetRenderFlag(g_RoleSystemCombat.m_nCCBUISelectedRole);
// [VFTABLE] BYTE2(this->__vftable[4].sub_4431B0) = unk_5D87F0;
  if ( BYTE2(g_RoleSystemCombat.m_nCCBUISelectedRole) )
  {
// [VFTABLE] ((CCBSystem *)this->__vftable)->GetRenderFlag();
    BYTE2(g_RoleSystemCombat.m_nCCBUISelectedRole) = 0;
  }



  LOBYTE(result) = this->UpdateState();
  return result;
}

// 0x004E0690
char CCBUI::ResetAllSlots()
{
  char result; // al
  int FullConfig; // eax
  char Buffer[128]; // [esp+0x8] [ebp-0x80] BYREF

  result = g_RoleSystemCombat.m_pScriptBuf;
  if ( LOBYTE(g_RoleSystemCombat.m_pScriptBuf) )
  {
// [VFTABLE] ((CCBStageScene *)*((CCBStageScene **)this->__vftable->sub_4431B0 + 5))->Update();
// [VFTABLE] ((CCBStageScene *)*((CCBStageScene **)this->__vftable->sub_4431B0 + 5))->ShowRoleIndex();
// [VFTABLE] result = ((CCBSystem *)this->__vftable)->CreateObj(&ppUI, 0, 0x40u);
    LOBYTE(g_RoleSystemCombat.m_pScriptBuf) = 0;
  }
  if ( BYTE2(g_RoleSystemCombat.m_pScriptBuf) )
    BYTE2(g_RoleSystemCombat.m_pScriptBuf) = 0;
  if ( BYTE1(g_RoleSystemCombat.m_pScriptBuf) )
    BYTE1(g_RoleSystemCombat.m_pScriptBuf) = 0;
  if ( HIBYTE(g_RoleSystemCombat.m_pScriptBuf) )
  {
// [VFTABLE] FullConfig = ((CIniFile *)*((CIniFile **)this->__vftable->sub_4431B0 + 3))->LoadFullConfig();
    sprintf(Buffer, &unk_5D8848, FullConfig);
// [VFTABLE] result = ((CCBSystem *)this->__vftable)->CreateObj((CCBUI **)Buffer, 0, 0x40u);
    HIBYTE(g_RoleSystemCombat.m_pScriptBuf) = 0;
  }
  return result;
}

// 0x004E0740
char CCBUI::UpdateDisplay()
{
  _BYTE *vftable; // eax
  int v3; // edi
  int i; // esi
  int (*Create)(int, int); // ecx
  int v6; // edi
  int v7; // esi
  int (*v8)(int, int); // ecx
  HWND DlgItem; // eax

  LOBYTE(vftable) = BYTE1(g_RoleSystemCombat.m_nCCBUISelectedRole);
  if ( BYTE1(g_RoleSystemCombat.m_nCCBUISelectedRole) )
  {
    v3 = 0;
    for ( i = 0; i < 4460; i += 892 )
    {
// [VFTABLE] vftable = this->__vftable;
// [VFTABLE] Create = this->__vftable->Create;
      if ( *((_BYTE *)Create + i + 577) )
      {
        vftable = ((CCBRoleState *)Create)->InitUI(v3);
        vftable[837] = 0;
      }
      ++v3;
    }
    LOWORD(g_RoleSystemCombat.m_nCCBUISelectedRole) = 0;
  }
  else
  {
    v6 = 0;
    v7 = 0;
    while ( 1 )
    {
// [VFTABLE] v8 = this->__vftable->Create;
      if ( *((_BYTE *)v8 + v7 + 577) )
      {
        vftable = ((CCBRoleState *)v8)->InitUI(v6);
        if ( !vftable[837] )
          break;
      }
      v7 += 892;
      ++v6;
      if ( v7 >= 4460 )
      {
        if ( !LOBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) )
        {
          LOBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) = 1;
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
          DlgItem = GetDlgItem(hDlg, 1004);
          SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
// [VFTABLE] LOBYTE(vftable) = ((CCBSystem *)this->__vftable)->ProcFlee(g_RoleSystemCombat.m_nCCBUISelectedRole);
        }
        return (char)vftable;
      }
    }
  }
  return (char)vftable;
}

// 0x004E0820
char CCBUI::UpdateAnimation()
{
  char result; // al

  result = g_RoleSystemCombat._field_FE4;
  if ( LOBYTE(g_RoleSystemCombat._field_FE4) )
  {
    LOBYTE(g_RoleSystemCombat._field_FE4) = 0;
    ((CCBStageRole *)this)->InitUIByName();
  }
  if ( BYTE1(g_RoleSystemCombat._field_FE4) )
  {
    BYTE1(g_RoleSystemCombat._field_FE4) = 0;
    result = ((CCBRoleState *)this)->SyncRoleUIData();
  }
  if ( BYTE2(g_RoleSystemCombat._field_FE4) )
  {
    BYTE2(g_RoleSystemCombat._field_FE4) = 0;
    result = this->UpdateDebugStatus();
  }
  if ( LOBYTE(g_RoleSystemCombat._todo_FF8) )
  {
    LOBYTE(g_RoleSystemCombat._todo_FF8) = 0;

  }
  if ( HIBYTE(g_RoleSystemCombat._field_FE4) )
  {
    HIBYTE(g_RoleSystemCombat._field_FE4) = 0;
    result = this->InitUI_4E3A20();
  }
  if ( LOBYTE(g_RoleSystemCombat.m_configData[2]) )
  {
    LOBYTE(g_RoleSystemCombat.m_configData[2]) = 0;
    result = ((CCBRoleState *)this)->UpdateDebugDialog();
  }
  if ( BYTE1(g_RoleSystemCombat.m_configData[2]) )
  {
    BYTE1(g_RoleSystemCombat.m_configData[2]) = 0;
    result = ((CCBRoleState *)this)->ApplyDebugEdits();
  }
  if ( BYTE2(g_RoleSystemCombat.m_configData[2]) )
  {
    BYTE2(g_RoleSystemCombat.m_configData[2]) = 0;
    result = this->PopulateCommandList();
  }
  if ( LOBYTE(g_RoleSystemCombat.m_configData[3]) )
  {
    LOBYTE(g_RoleSystemCombat.m_configData[3]) = 0;
    result = this->ShowCommandDetails();
  }
  if ( HIBYTE(g_RoleSystemCombat.m_configData[2]) )
  {
    HIBYTE(g_RoleSystemCombat.m_configData[2]) = 0;
    result = this->CloseCommandDialog();
  }
  if ( BYTE2(g_RoleSystemCombat.m_configData[3]) )
  {
    BYTE2(g_RoleSystemCombat.m_configData[3]) = 0;
    result = (unsigned __int8)((PAL_GDB *)this)->SetupSkillConfig();
  }
  if ( BYTE1(g_RoleSystemCombat.m_configData[3]) )
  {
    BYTE1(g_RoleSystemCombat.m_configData[3]) = 0;
    result = this->ApplyCommandEdit();
  }
  if ( HIBYTE(g_RoleSystemCombat.m_configData[3]) )
  {
    HIBYTE(g_RoleSystemCombat.m_configData[3]) = 0;
    result = this->ShowSkillDetails();
  }
  if ( LOBYTE(g_RoleSystemCombat.m_configData[4]) )
  {
    LOBYTE(g_RoleSystemCombat.m_configData[4]) = 0;
    result = CCBRoleState::GetTargetCommand();
  }
  if ( BYTE1(g_RoleSystemCombat.m_configData[4]) )
  {
    BYTE1(g_RoleSystemCombat.m_configData[4]) = 0;
    result = ((PAL_GDB *)this)->RefreshPartyDialog();
  }
  if ( BYTE2(g_RoleSystemCombat.m_configData[4]) )
  {
    BYTE2(g_RoleSystemCombat.m_configData[4]) = 0;
    return ((PAL_GDB *)this)->PopulateAvailableRoles();
  }
  return result;
}

// 0x004E0980
char CCBUI::UpdateState()
{
  char result; // al
  int v2; // esi
  HWND DlgItem; // edi

  result = (char)g_RoleSystemCombat.dwInitParam;
// [VFTABLE] v2 = *((_DWORD *)this->__vftable->sub_4431B0 + 4);
  if ( g_RoleSystemCombat.dwInitParam == (HWND)4 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1201);
    result = *(_BYTE *)(v2 + 430012);
    if ( result )
    {
      g_EffMgr = 1;
      sprintf(
        (char *const)&g_RoleSystemCombat.m_teamSlots[264],
        "%03d-%03d",
        *(_DWORD *)(v2 + 430032),
        *(_DWORD *)(v2 + 430036));
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    }
    else if ( g_EffMgr == 1 )
    {
      g_EffMgr = 0;
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "Stopped");
      return SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    }
  }
  return result;
}

// 0x004E0A60
int CCBUI::DlgProcEditorMain(HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam)
{
  HWND DlgItem; // ebx
  HWND v7; // ebp
  HWND v8; // edi
  int result; // eax
  void (__stdcall *v10)(HWND, UINT, WPARAM, LPARAM); // esi
  double v11; // st7
  bool v12; // zf
  LPARAM v13; // [esp+0x4] [ebp-0x18]
  HWND hWnd; // [esp+0x18] [ebp-0x4]
  HWND hDlga; // [esp+0x24] [ebp+0x8]

  DlgItem = GetDlgItem(hDlg, 1001);
  v7 = GetDlgItem(hDlg, 1003);
  hDlga = GetDlgItem(hDlg, 1004);
  hWnd = GetDlgItem(hDlg, 1005);
  v8 = GetDlgItem(hDlg, 1010);
  if ( uMsg > 0x110 )
  {
    if ( uMsg == 273 )
    {
      if ( wParam > 0x3F1u )
      {
        switch ( wParam )
        {
          case 0x3F3u:
            if ( !g_RoleSystemCombat.dwInitParam )
              return 0;
// [VFTABLE] ((CCBSystem *)a1->__vftable->Destroy)->SetThreadFlag(1);
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_RoleSystemCombat.dwInitParam = 0;
            g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x69, ::hWnd, (DLGPROC)CCBUI::CloseDialog, 0);
            ShowWindow(g_hMainWnd, 4);
            result = 0;
            break;
          case 0x3F4u:
            BYTE2(g_RoleSystemCombat.m_nCCBUISelectedRole) = 1;
            result = 0;
            break;
          case 0x3F5u:
            HIBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) = HIBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) == 0;
            return 0;
          case 0x3F6u:
            if ( g_RoleSystemCombat.dwInitParam == (HWND)5 )
              return 0;
            ((CCBUI *)a1)->StartMagicThread();
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_RoleSystemCombat.dwInitParam = (HWND)5;
            g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x71, ::hWnd, (DLGPROC)CCBStageCam::StoreCurrentView, 0);
            ShowWindow(g_hMainWnd, 4);
            ((CCBStageCam *)a1)->sub_4E95A0(g_hMainWnd);
            result = 0;
            break;
          case 0x3F7u:
            g_RoleSystemCombat.m_teamSlotsB[4] = 0;
            v13 = 0;
            goto LABEL_25;
          case 0x3F8u:
            if ( g_RoleSystemCombat.dwInitParam == (HWND)6 )
              return 0;
            ((CCBUI *)a1)->StartMagicThread();
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_RoleSystemCombat.dwInitParam = (HWND)6;
            g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x72, ::hWnd, CCBUI::_nearby_4eb230, 0);
            ShowWindow(g_hMainWnd, 4);
            ((CCBCamControl *)a1)->sub_4EB6F0(g_hMainWnd);
            result = 0;
            break;
          default:
            return 0;
        }
        return result;
      }
      if ( wParam == 1009 )
      {
        if ( g_RoleSystemCombat.dwInitParam != (HWND)1 )
        {
          ((CCBUI *)a1)->StartMagicThread();
          if ( g_hMainWnd )
            DestroyWindow(g_hMainWnd);
          g_RoleSystemCombat.dwInitParam = (HWND)1;
          g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x68, ::hWnd, (DLGPROC)CCBUI::DlgProcEffect, 0);
          ShowWindow(g_hMainWnd, 4);
          return 0;
        }
      }
      else
      {
        if ( wParam <= 0x3ECu )
        {
          switch ( wParam )
          {
            case 0x3ECu:
              v12 = LOBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) != 0;
              LOBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) = LOBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) == 0;
              if ( v12 )
              {
                BYTE1(g_RoleSystemCombat.m_nCCBUISelectedRole) = 1;
                sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
              }
              else
              {
                sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
              }
              SendMessageA(hDlga, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
              return 0;
            case 1u:
              EndDialog(hDlg, 1);
              DestroyWindow(::hWnd);
              return 0;
            case 2u:
              return 1;
          }
          if ( wParam != 1003 )
            return 0;
          g_RoleSystemCombat.m_teamSlotsB[4] = 1065353216;
          v13 = (__int64)(1.0 * 100.0);
LABEL_25:
          v10 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
          SendMessageA(DlgItem, 0x405u, 1u, v13);
          v11 = *(float *)&g_RoleSystemCombat.m_teamSlotsB[4];
LABEL_16:
          sprintf((char *const)&g_RoleSystemCombat.m_StaticSlotArray.m_bfocus, "Speed%1.2f", v11);
          v10(v7, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_StaticSlotArray.m_bfocus);
          return 0;
        }
        if ( wParam == 1005 )
        {
          v12 = g_EffMgr != 0;
          g_EffMgr = g_EffMgr == 0;
          if ( v12 )
            sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
          else
            sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
          SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
          return 0;
        }
        if ( wParam == 1006 )
        {
          if ( g_RoleSystemCombat.dwInitParam != (HWND)2 )
          {
// [VFTABLE] ((CCBSystem *)a1->__vftable->Destroy)->SetThreadFlag(1);
// [VFTABLE] ((CCBUI *)a1->__vftable->Render)->CreateResultWindow(1);
            if ( g_hMainWnd )
              DestroyWindow(g_hMainWnd);
            g_RoleSystemCombat.dwInitParam = (HWND)2;
            g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x6A, ::hWnd, CCBUI::CombatDlgProcThunk, 0);
            ShowWindow(g_hMainWnd, 4);
            ((CCBRoleState *)a1)->UpdateDebugTreeView();
            return 0;
          }
        }
        else if ( wParam == 1007 && g_RoleSystemCombat.dwInitParam != (HWND)4 )
        {
          ((CCBUI *)a1)->StartMagicThread();
          if ( g_hMainWnd )
            DestroyWindow(g_hMainWnd);
          g_RoleSystemCombat.dwInitParam = (HWND)4;
          g_hMainWnd = CreateDialogParamA(hInstance, (LPCSTR)0x6E, ::hWnd, (DLGPROC)PAL_GDB::DlgProcCamera, 0);
          ShowWindow(g_hMainWnd, 4);
          HIBYTE(g_RoleSystemCombat.m_configData[4]) = 1;
          return 0;
        }
      }
    }
    else if ( uMsg == 276 )
    {
      v10 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
      v11 = (double)SendMessageA(DlgItem, 0x400u, 0, 0) / 100.0;
      *(float *)&g_RoleSystemCombat.m_teamSlotsB[4] = v11;
      goto LABEL_16;
    }
    return 0;
  }
  if ( uMsg != 272 )
  {
    if ( uMsg == 16 )
    {
      EndDialog(hDlg, wParam);
      DestroyWindow(::hWnd);
      return 1;
    }
    return 0;
  }
  SetWindowPos(hDlg, 0, 0, 600, 801, 130, 0x80u);
  SendMessageA(DlgItem, 0x407u, 0, 0);
  SendMessageA(DlgItem, 0x408u, 0, 2000);
  SendMessageA(DlgItem, 0x405u, 1u, (__int64)(*(float *)&g_RoleSystemCombat.m_teamSlotsB[4] * 100.0));
  sprintf(
    (char *const)&g_RoleSystemCombat.m_StaticSlotArray.m_bfocus,
    "Speed%1.2f",
    *(float *)&g_RoleSystemCombat.m_teamSlotsB[4]);
  SendMessageA(v7, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_StaticSlotArray.m_bfocus);
  if ( LOBYTE(g_RoleSystemCombat.m_nCCBUISelectedRole) )
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
  else
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
  SendMessageA(hDlga, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  if ( g_EffMgr )
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
  else
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], byte_5967B0, &g_EffMgr);
  SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  sprintf(
    (char *const)&g_RoleSystemCombat.m_teamSlots[264],
    "%s Build %s %s Release",
    "PAL3 COMBAT SYSTEM 1.03",
    "Jan  5 2004",
    "16:42:29");
  SendMessageA(v8, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  return 0;
}

// 0x004E10E0
int CCBUI::CloseDialog(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if ( uMsg == 16 )
  {
    EndDialog(hDlg, (unsigned __int16)wParam);
    return 1;
  }
  else
  {
    if ( uMsg == 272 )
    {
      SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
    }
    else if ( uMsg == 273 && (unsigned __int16)wParam == 1 )
    {
      EndDialog(hDlg, 1);
      return 0;
    }
    return 0;
  }
}

// 0x004E1160
int CCBUI::DlgProcEffect(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return ((CEffectSystem *)g_RoleSystemCombat.m_teamSlots[263])->CreateEffectChain((CCBUI *)g_RoleSystemCombat.m_teamSlots[263], hDlg, msg, wParam, lParam);
}

// 0x004E16F0
unsigned __int8 * CCBUI::PopulateSceneList(HWND hDlg)
{
  LPARAM v2; // esi
  HWND DlgItem; // ebp
  unsigned __int8 *result; // eax
  HANDLE FirstFileA; // eax
  HANDLE hFindFile; // [esp+0x10] [ebp-0x270]
  LPARAM lParam[10]; // [esp+0x14] [ebp-0x26C] BYREF
  CHAR Filename[260]; // [esp+0x3C] [ebp-0x244] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+0x140] [ebp-0x140] BYREF

  v2 = 0;
  DlgItem = GetDlgItem(hDlg, 1203);
  memset(lParam, 0, sizeof(lParam));
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  memset(Filename, 0, sizeof(Filename));
  GetModuleFileNameA(0, Filename, 0x104u);
  result = _mbsrchr((const unsigned __int8 *)Filename, 0x5Cu);
  if ( result )
  {
    _mbsrchr((const unsigned __int8 *)Filename, 0x5Cu)[1] = 0;
    lstrcatA(Filename, "basedata\\cbscene\\*.");
    FirstFileA = FindFirstFileA(Filename, &FindFileData);
    hFindFile = FirstFileA;
    if ( FirstFileA == (HANDLE)-1 )
    {
      return (unsigned __int8 *)MessageBoxA(hWnd, &unk_5D88FC, 0, 0);
    }
    else
    {
      for ( result = (unsigned __int8 *)FindNextFileA(FirstFileA, &FindFileData);
            result;
            result = (unsigned __int8 *)FindNextFileA(hFindFile, &FindFileData) )
      {
        if ( !_mbsrchr((const unsigned __int8 *)FindFileData.cFileName, 0x2Eu) )
        {
          lParam[0] = 1;
          lParam[5] = (LPARAM)&g_RoleSystemCombat.m_teamSlots[264];
          lParam[1] = v2;
          lParam[2] = 0;
          sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%03d", v2);
          SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
          lParam[5] = (LPARAM)FindFileData.cFileName;
          lParam[2] = 1;
          SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
          ++v2;
        }
      }
    }
  }
  return result;
}

// 0x004E1870
unsigned __int8 * CCBUI::LoadSceneByIndex(int nVal)
{
  unsigned __int8 *result; // eax
  HANDLE FirstFileA; // eax
  void *v5; // ebx
  int v6; // edi
  int v7; // [esp+0xC] [ebp-0x248]
  CHAR Filename[260]; // [esp+0x10] [ebp-0x244] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+0x114] [ebp-0x140] BYREF

  memset(Filename, 0, sizeof(Filename));
  v7 = 0;
  GetModuleFileNameA(0, Filename, 0x104u);
  result = _mbsrchr((const unsigned __int8 *)Filename, 0x5Cu);
  if ( result )
  {
    _mbsrchr((const unsigned __int8 *)Filename, 0x5Cu)[1] = 0;
    lstrcatA(Filename, "basedata\\cbscene\\*.");
    FirstFileA = FindFirstFileA(Filename, &FindFileData);
    v5 = FirstFileA;
    if ( FirstFileA == (HANDLE)-1 )
    {
      return (unsigned __int8 *)MessageBoxA(hWnd, &unk_5D88FC, 0, 0);
    }
    else
    {
      for ( result = (unsigned __int8 *)FindNextFileA(FirstFileA, &FindFileData);
            result;
            result = (unsigned __int8 *)FindNextFileA(v5, &FindFileData) )
      {
        if ( !_mbsrchr((const unsigned __int8 *)FindFileData.cFileName, 0x2Eu) )
        {
          if ( v7 == nVal )
          {
// [VFTABLE] v6 = *((_DWORD *)this->__vftable->sub_4431B0 + 5);
            if ( strcmp(FindFileData.cFileName, (const char *)(v6 + 345)) )
            {
              sub_511630(v6);
// [VFTABLE] ((CCBStageScene *)*((CCBStageScene **)this->__vftable->sub_4431B0 + 5))->LoadModel(FindFileData.cFileName);
              strcpy((char *)&stru_C11720, FindFileData.cFileName);
            }
          }
          ++v7;
        }
      }
    }
  }
  return result;
}

// 0x004E1A10
int CCBUI::CombatDlgProcThunk(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return ((CCBRoleState *)g_RoleSystemCombat.m_teamSlots[263])->CombatDialogProc(g_RoleSystemCombat.m_teamSlots[263], hDlg, uMsg, wParam, lParam);
}

// 0x004E1F70
int CCBUI::SettingsDialogProc(HWND hDlg, unsigned int dwVal, WPARAM pData, LPARAM a5)
{
  HWND v5; // eax
  HWND DlgItem; // eax
  HWND v7; // ebx
  HWND v8; // eax
  HWND v9; // ebx
  HWND v10; // eax
  HWND v11; // ebx
  HWND v12; // eax
  HWND v13; // ebx
  HWND v14; // eax
  HWND v15; // ebx
  HWND v16; // eax
  HWND v17; // ebx
  HWND v18; // eax
  HWND v19; // ebx
  HWND v20; // eax
  HWND v21; // ebx
  HWND v22; // eax
  HWND v23; // edi
  unsigned int v25; // [esp+0x8] [ebp-0x28]
  LPARAM lParam[2]; // [esp+0xC] [ebp-0x24] BYREF
  LPARAM v27[3]; // [esp+0x14] [ebp-0x1C] BYREF
  void *v28; // [esp+0x20] [ebp-0x10]
  int v29; // [esp+0x28] [ebp-0x8]
  int v30; // [esp+0x2C] [ebp-0x4]

  v5 = 0;
  v25 = 0;
  lParam[1] = 1;
  lParam[0] = 1;
  if ( dwVal > 0x110 )
  {
    if ( dwVal == 273 )
    {
      if ( (unsigned __int16)pData > 0x428u )
      {
        if ( (unsigned __int16)pData == 1065 )
        {
          dword_5D87F8 = 3;
          goto LABEL_32;
        }
        if ( (unsigned __int16)pData == 1066 )
        {
          dword_5D87F8 = 4;
          goto LABEL_32;
        }
      }
      else
      {
        switch ( (unsigned __int16)pData )
        {
          case 0x428u:
            dword_5D87F8 = 2;
            goto LABEL_32;
          case 1u:
            LOBYTE(g_RoleSystemCombat._todo_FF8) = 1;
            EndDialog(hDlg, 1);
            return 1;
          case 0x426u:
            dword_5D87F8 = 0;
            goto LABEL_32;
          case 0x427u:
            dword_5D87F8 = 1;
LABEL_32:
            HIBYTE(g_RoleSystemCombat._field_FE4) = 1;
            LOBYTE(g_RoleSystemCombat._todo_FF8) = 1;
            break;
        }
      }
    }
    return 0;
  }
  if ( dwVal != 272 )
  {
    if ( dwVal != 2 )
    {
      if ( dwVal != 78 || pData != 1114 || *(_DWORD *)(a5 + 8) != -551 )
        return 0;
      DlgItem = GetDlgItem(hDlg, 1114);
      g_RoleSystemCombat.m_configData[0] = SendMessageA(DlgItem, 0x130Bu, 0, 0);
      goto LABEL_32;
    }
    return 1;
  }
  if ( ::dwVal <= 4 )
    v25 = ::dwVal;
  switch ( ::dwVal )
  {
    case 0u:
      v5 = GetDlgItem(hDlg, 1062);
      break;
    case 1u:
      v5 = GetDlgItem(hDlg, 1063);
      break;
    case 2u:
      v5 = GetDlgItem(hDlg, 1064);
      break;
    case 3u:
      v5 = GetDlgItem(hDlg, 1065);
      break;
    case 4u:
      v5 = GetDlgItem(hDlg, 1066);
      break;
    default:
      break;
  }
  SendMessageA(v5, 0xF1u, 1u, 0);
  v7 = GetDlgItem(hDlg, 1087);
  v8 = GetDlgItem(hDlg, 1102);
  SendMessageA(v7, 0x469u, (WPARAM)v8, 0);
  SendMessageA(v7, 0x465u, 0, 65540);
  SendMessageA(v7, 0x46Du, 0xAu, 0);
  SendMessageA(v7, 0x46Bu, 1u, (LPARAM)lParam);
  v9 = GetDlgItem(hDlg, 1088);
  v10 = GetDlgItem(hDlg, 1103);
  SendMessageA(v9, 0x469u, (WPARAM)v10, 0);
  SendMessageA(v9, 0x465u, 0, 65540);
  SendMessageA(v9, 0x46Du, 0xAu, 0);
  SendMessageA(v9, 0x46Bu, 1u, (LPARAM)lParam);
  v11 = GetDlgItem(hDlg, 1089);
  v12 = GetDlgItem(hDlg, 1105);
  SendMessageA(v11, 0x469u, (WPARAM)v12, 0);
  SendMessageA(v11, 0x465u, 0, 65540);
  SendMessageA(v11, 0x46Du, 0xAu, 0);
  SendMessageA(v11, 0x46Bu, 1u, (LPARAM)lParam);
  v13 = GetDlgItem(hDlg, 1090);
  v14 = GetDlgItem(hDlg, 1106);
  SendMessageA(v13, 0x469u, (WPARAM)v14, 0);
  SendMessageA(v13, 0x465u, 0, 65540);
  SendMessageA(v13, 0x46Du, 0xAu, 0);
  SendMessageA(v13, 0x46Bu, 1u, (LPARAM)lParam);
  v15 = GetDlgItem(hDlg, 1091);
  v16 = GetDlgItem(hDlg, 1107);
  SendMessageA(v15, 0x469u, (WPARAM)v16, 0);
  SendMessageA(v15, 0x465u, 0, 65540);
  SendMessageA(v15, 0x46Du, 0xAu, 0);
  SendMessageA(v15, 0x46Bu, 1u, (LPARAM)lParam);
  v17 = GetDlgItem(hDlg, 1092);
  v18 = GetDlgItem(hDlg, 1109);
  SendMessageA(v17, 0x469u, (WPARAM)v18, 0);
  SendMessageA(v17, 0x465u, 0, 65540);
  SendMessageA(v17, 0x46Du, 0xAu, 0);
  SendMessageA(v17, 0x46Bu, 1u, (LPARAM)lParam);
  v19 = GetDlgItem(hDlg, 1093);
  v20 = GetDlgItem(hDlg, 1110);
  SendMessageA(v19, 0x469u, (WPARAM)v20, 0);
  SendMessageA(v19, 0x465u, 0, 65540);
  SendMessageA(v19, 0x46Du, 0xAu, 0);
  SendMessageA(v19, 0x46Bu, 1u, (LPARAM)lParam);
  v21 = GetDlgItem(hDlg, 1094);
  v22 = GetDlgItem(hDlg, 1112);
  SendMessageA(v21, 0x469u, (WPARAM)v22, 0);
  SendMessageA(v21, 0x465u, 0, 65540);
  SendMessageA(v21, 0x46Du, 0xAu, 0);
  SendMessageA(v21, 0x46Bu, 1u, (LPARAM)lParam);
  v23 = GetDlgItem(hDlg, 1114);
  SendMessageA(v23, 0x1331u, 0, 10);
  SendMessageA(v23, 0x1329u, 0, 1310730);
  v27[0] = 1;
  v29 = 0;
  v30 = 0;
  v28 = &g_EffMgr;
  SendMessageA(v23, 0x1307u, 0, (LPARAM)v27);
  v28 = &g_EffMgr;
  SendMessageA(v23, 0x1307u, 1u, (LPARAM)v27);
  v28 = &g_EffMgr;
  SendMessageA(v23, 0x1307u, 2u, (LPARAM)v27);
  v28 = &g_EffMgr;
  SendMessageA(v23, 0x1307u, 3u, (LPARAM)v27);
  v28 = &g_EffMgr;
  SendMessageA(v23, 0x1307u, 4u, (LPARAM)v27);
  v28 = &g_EffMgr;
  SendMessageA(v23, 0x1307u, 5u, (LPARAM)v27);
  LOBYTE(g_RoleSystemCombat._todo_FF8) = 0;
  dword_5D87F8 = v25;
  HIBYTE(g_RoleSystemCombat._field_FE4) = 1;
  return 1;
}

// 0x004E2430
int CCBUI::HandleWindowMessage(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if ( uMsg == 272 )
  {
    LOBYTE(g_RoleSystemCombat.m_configData[2]) = 1;
  }
  else if ( uMsg == 273 )
  {
    if ( (unsigned __int16)wParam == 1 )
    {
      EndDialog(g_RoleSystemCombat.g_hCombatDlg2, 0);
      g_RoleSystemCombat.g_hCombatDlg2 = 0;
      return 0;
    }
    if ( (unsigned __int16)wParam == 2 )
    {
      BYTE1(g_RoleSystemCombat.m_configData[2]) = 1;
      return 0;
    }
  }
  return 0;
}

// 0x004E2490
int CCBUI::DlgProcMain(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  return ((CCBUI *)g_RoleSystemCombat.m_teamSlots[263])->CommandEditDialogProc((int *)g_RoleSystemCombat.m_teamSlots[263], hDlg, msg, wParam, lParam);
}

// 0x004E24C0
int CCBUI::CommandEditDialogProc(int *p_DWORD, HWND hDlg, int nVal, int nVal2, int nVal3)
{
  HWND DlgItem; // ebp
  HWND v7; // ebx
  HWND v8; // edi
  int v10; // edi
  int j; // esi
  int *v12; // eax
  int SlotCount; // edi
  int i; // esi
  int *TargetRole; // eax
  LRESULT v16; // eax
  LRESULT v17; // eax
  signed int SkillID; // ebp
  signed int v19; // edi
  int ItemID; // eax
  int SkillNum; // eax
  int v22; // [esp+0x10] [ebp-0x174] BYREF
  int v23; // [esp+0x14] [ebp-0x170]
  int v24; // [esp+0x18] [ebp-0x16C]
  LPARAM lParam[8]; // [esp+0x1C] [ebp-0x168] BYREF
  HWND v26; // [esp+0x3C] [ebp-0x148]
  HWND hWnd; // [esp+0x40] [ebp-0x144]
  LPARAM v28[10]; // [esp+0x44] [ebp-0x140] BYREF
  char pOut[12]; // [esp+0x6C] [ebp-0x118] BYREF
  char v30[12]; // [esp+0x78] [ebp-0x10C] BYREF
  char Buffer[256]; // [esp+0x84] [ebp-0x100] BYREF

  DlgItem = GetDlgItem(hDlg, 1142);
  v7 = GetDlgItem(hDlg, 1146);
  hWnd = GetDlgItem(hDlg, 1040);
  v26 = GetDlgItem(hDlg, 1149);
  v8 = GetDlgItem(hDlg, 1086);
  if ( nVal == 78 )
  {
    if ( nVal2 == 1142 )
    {
      if ( *(_DWORD *)(nVal3 + 8) == -2 && *(_DWORD *)(nVal3 + 12) != -1 )
      {
        g_EffMgr = *(_DWORD *)(nVal3 + 12);
        LOBYTE(g_RoleSystemCombat.m_configData[3]) = 1;
        EnableWindow(hWnd, 1);
        EnableWindow(v26, 1);
        EnableWindow(v8, 1);
      }
    }
    else if ( nVal2 == 1146 && *(_DWORD *)(nVal3 + 8) == -3 && *(_DWORD *)(nVal3 + 12) != -1 )
    {
      index = *(_DWORD *)(nVal3 + 12);
      BYTE2(g_RoleSystemCombat.m_configData[3]) = 1;
      return 0;
    }
    return 0;
  }
  if ( nVal != 272 )
  {
    if ( nVal == 273 )
    {
      if ( (unsigned __int16)nVal2 > 0x412u )
      {
        switch ( (unsigned __int16)nVal2 )
        {
          case 0x413u:
            v22 = 0xFFFF;
            v23 = 0;
            v24 = 0;
LABEL_25:
            SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
            for ( i = 0; i < SlotCount; ++i )
            {
              TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(v30);
              v22 = *TargetRole;
              v23 = TargetRole[1];
              v24 = TargetRole[2];
              if ( *(_BYTE *)(v24 + 612) == 1 )
              {
                ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v22);
                goto LABEL_25;
              }
            }
            goto LABEL_10;
          case 0x43Eu:
            BYTE1(g_RoleSystemCombat.m_configData[3]) = 1;
            return 0;
          case 0x47Du:
            HIBYTE(g_RoleSystemCombat.m_configData[3]) = 1;
            return 0;
        }
      }
      else
      {
        switch ( (unsigned __int16)nVal2 )
        {
          case 0x412u:
            v22 = 0xFFFF;
            v23 = 0;
            v24 = 0;
LABEL_14:
            v10 = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
            for ( j = 0; j < v10; ++j )
            {
              v12 = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
              v22 = *v12;
              v23 = v12[1];
              v24 = v12[2];
              if ( *(_BYTE *)(v24 + 612) == 2 )
              {
                ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v22);
                goto LABEL_14;
              }
            }
            goto LABEL_10;
          case 1u:
            HIBYTE(g_RoleSystemCombat.m_configData[2]) = 1;
            return 0;
          case 0x410u:
            LOBYTE(g_RoleSystemCombat.m_configData[4]) = 1;
            return 0;
          case 0x411u:
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Reset();
LABEL_10:
            ((CCBUI *)p_DWORD)->PopulateCommandList();
            return 0;
        }
      }
    }
    return 0;
  }
  memset(lParam, 0, sizeof(lParam));
  BYTE2(g_RoleSystemCombat.m_configData[2]) = 1;
  v16 = SendMessageA(DlgItem, 0x1037u, 0, 0);
  LOBYTE(v16) = v16 | 0x21;
  SendMessageA(DlgItem, 0x1036u, 0, v16);
  v17 = SendMessageA(v7, 0x1037u, 0, 0);
  LOBYTE(v17) = v17 | 0x21;
  SendMessageA(v7, 0x1036u, 0, v17);
  lParam[0] = 7;
  lParam[1] = 0;
  lParam[2] = 120;
  lParam[3] = (LPARAM)"Name";
  SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParam);
  lParam[1] = 1;
  lParam[2] = 50;
  lParam[3] = (LPARAM)&g_pCombatUIData;
  SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParam);
  lParam[2] = 50;
  lParam[3] = (LPARAM)&g_EffMgr;
  SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParam);
  lParam[2] = 50;
  lParam[3] = (LPARAM)&g_EffMgr;
  SendMessageA(DlgItem, 0x101Bu, 3u, (LPARAM)lParam);
  lParam[2] = 50;
  lParam[3] = (LPARAM)&g_EffMgr;
  SendMessageA(DlgItem, 0x101Bu, 4u, (LPARAM)lParam);
  lParam[2] = 145;
  lParam[3] = (LPARAM)"Name";
  SendMessageA(v7, 0x101Bu, 0, (LPARAM)lParam);
  SkillID = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillID();
  memset(v28, 0, sizeof(v28));
  v19 = 0;
  v28[0] = 1;
  v28[2] = 0;
  v28[5] = (LPARAM)Buffer;
  if ( SkillID <= 0 )
    return 0;
  do
  {
    ItemID = ((PAL_GDB *)&g_pGDB)->GetItemID(v19);
    SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(ItemID);
    sprintf(Buffer, "%03d%s", v19, (const char *)(SkillNum + 4));
    v28[1] = v19;
    v28[2] = 0;
    SendMessageA(v7, 0x1007u, 0, (LPARAM)v28);
    ++v19;
  }
  while ( v19 < SkillID );
  return 0;
}

// 0x004E2AE0
LRESULT CCBUI::HandleRoleStateDialog(int nVal)
{
  LRESULT result; // eax
  HWND DlgItem; // ebx
  void *vftable; // edx
  tagRoleState *inited; // eax
  void *v7; // eax
  tagRoleState *v8; // eax
  void *v9; // ecx
  tagRoleState *v10; // eax
  LPARAM lParam[10]; // [esp+0xC] [ebp-A8h] BYREF
  char Buffer[128]; // [esp+0x34] [ebp-0x80] BYREF

  result = (LRESULT)g_RoleSystemCombat.dwInitParam;
  if ( g_RoleSystemCombat.dwInitParam == (HWND)2 )
  {
    DlgItem = GetDlgItem(g_hMainWnd, 1000);
    result = (LRESULT)g_RoleSystemCombat.dwInitParam;
    if ( g_RoleSystemCombat.dwInitParam == (HWND)2 )
    {
// [VFTABLE] vftable = this->__vftable;
      memset(lParam, 0, sizeof(lParam));
      lParam[0] = 1;
      lParam[1] = nVal;
      lParam[5] = (LPARAM)Buffer;
      lParam[2] = 2;
      inited = ((CCBRoleState *)vftable->Create)->InitUI(nVal);
      sprintf(Buffer, &dir[20], inited->nHP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
// [VFTABLE] v7 = this->__vftable;
      lParam[2] = 3;
      v8 = ((CCBRoleState *)v7->Create)->InitUI(nVal);
      sprintf(Buffer, &dir[20], v8->nGP);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
// [VFTABLE] v9 = this->__vftable;
      lParam[2] = 4;
      v10 = ((CCBRoleState *)v9->Create)->InitUI(nVal);
      sprintf(Buffer, &dir[20], v10->nMP);
      return SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
    }
  }
  return result;
}

// 0x004E3780
char CCBUI::UpdateDebugStatus()
{
  HWND DlgItem; // ebp
  HWND v3; // edi
  char result; // al
  int v5; // edi
  int SlotState; // eax
  int v7; // eax
  int ActionTypeBySlot; // eax
  int v9; // eax
  int v10; // eax
  int RoleCount; // eax
  HWND hWnd; // [esp+0x10] [ebp-0x20]
  HWND v13; // [esp+0x14] [ebp-0x1C]
  HWND v14; // [esp+0x18] [ebp-0x18]
  HWND v15; // [esp+0x1C] [ebp-0x14]
  HWND v16; // [esp+0x20] [ebp-0x10]
  HWND v17; // [esp+0x24] [ebp-0xC]
  HWND v18; // [esp+0x28] [ebp-0x8]
  HWND v19; // [esp+0x2C] [ebp-0x4]

  GetDlgItem(g_hMainWnd, 1024);
  DlgItem = GetDlgItem(g_hMainWnd, 1026);
  hWnd = GetDlgItem(g_hMainWnd, 1032);
  v13 = GetDlgItem(g_hMainWnd, 1025);
  v14 = GetDlgItem(g_hMainWnd, 1033);
  v15 = GetDlgItem(g_hMainWnd, 1027);
  v16 = GetDlgItem(g_hMainWnd, 1034);
  v3 = GetDlgItem(g_hMainWnd, 1028);
  GetDlgItem(g_hMainWnd, 1029);
  v17 = GetDlgItem(g_hMainWnd, 1030);
  v18 = GetDlgItem(g_hMainWnd, 1031);
  GetDlgItem(g_hMainWnd, 1035);
  v19 = GetDlgItem(g_hMainWnd, 1036);
  result = dwVal;
  if ( dwVal <= 0xA )
  {
    result = *(_BYTE *)(this->m_fontcolor.Color + 892 * dwVal + 577);
    if ( result )
    {
      SendMessageA(v3, 0xDu, 0x14u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v5 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]);
      SlotState = ((CCBRoleState *)this->m_fontcolor.Color)->GetSlotState(dwVal, v5);
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], SlotState);
      SendMessageA(DlgItem, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v7 = ((CCBRoleState *)this->m_fontcolor.Color)->CalcSpeedByLevel(dwVal, v5);
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v7);
      SendMessageA(v13, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      SendMessageA(v14, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      ActionTypeBySlot = ((CCBRoleState *)this->m_fontcolor.Color)->GetActionTypeBySlot(dwVal, v5);
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], ActionTypeBySlot);
      SendMessageA(v15, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      SendMessageA(v16, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v9 = ((CCBRoleState *)this->m_fontcolor.Color)->CalcDefenseByLevel(dwVal, v5);
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v9);
      SendMessageA(v17, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v10 = ((CCBRoleState *)this->m_fontcolor.Color)->CalcDamage(dwVal, v5);
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v10);
      SendMessageA(v18, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      RoleCount = ((CCBRoleState *)this->m_fontcolor.Color)->GetRoleCount(v5);
      sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], RoleCount);
      return SendMessageA(v19, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
    }
  }
  return result;
}

// 0x004E3A20
LRESULT CCBUI::InitUI_4E3A20()
{
  HWND v1; // ebp
  HWND DlgItem; // edi
  int v3; // ebx
  char v4; // bl
  int RoleNum; // eax
  HWND v6; // eax
  void (__stdcall *v7)(HWND, UINT, WPARAM, LPARAM); // ebx
  int j; // ebp
  int v9; // edi
  char v10; // bl
  char *v11; // edi
  HWND v12; // eax
  LRESULT result; // eax
  int v14; // [esp-0x4] [ebp-0x2C]
  int v15; // [esp-0x4] [ebp-0x2C]
  char v16; // [esp+0x13] [ebp-0x15]
  HWND hWnd; // [esp+0x14] [ebp-0x14]
  int i; // [esp+0x18] [ebp-0x10]
  char *lParam; // [esp+0x20] [ebp-0x8]
  int v21; // [esp+0x24] [ebp-0x4]

  v1 = 0;
  DlgItem = 0;
  hWnd = 0;
  dword_5D87FC = dword_5D87F8;
  g_RoleSystemCombat.m_configData[1] = g_RoleSystemCombat.m_configData[0];
  for ( i = 0; i < 8; ++i )
  {
    v3 = ((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87F8)->dwSkillID[8
                                                                                              * g_RoleSystemCombat.m_configData[0]
                                                                                              + 7
                                                                                              + i];
    v16 = *((_BYTE *)&((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87F8)->dwMagicID[7][2 * g_RoleSystemCombat.m_configData[0] + 1]
          + i);
    v21 = (unsigned __int8)((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87F8)->bMagicMastered[8][8 * g_RoleSystemCombat.m_configData[0] + 4 + i]
        + 1;
    if ( v3 )
    {
      RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v3);
      v4 = v16;
      lParam = (char *)(RoleNum + 28);
    }
    else
    {
      lParam = &unk_5D89B0;
      v4 = 0;
      v21 = 0;
    }
    switch ( i )
    {
      case 0:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1052);
        v6 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1102);
        goto LABEL_15;
      case 1:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1054);
        v14 = 1103;
        goto LABEL_14;
      case 2:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1055);
        v6 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1105);
        goto LABEL_15;
      case 3:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1056);
        v6 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1106);
        goto LABEL_15;
      case 4:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1057);
        v14 = 1107;
        goto LABEL_14;
      case 5:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1058);
        v6 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1109);
        goto LABEL_15;
      case 6:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1060);
        v6 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1110);
        goto LABEL_15;
      case 7:
        DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1061);
        v14 = 1112;
LABEL_14:
        v6 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, v14);
LABEL_15:
        v1 = v6;
        break;
      default:
        break;
    }
    if ( v4 )
    {
      v7 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
      SendMessageA(DlgItem, 0xF1u, 1u, 0);
    }
    else
    {
      SendMessageA(DlgItem, 0xF1u, 0, 0);
      v7 = (void ( *)(HWND, UINT, WPARAM, LPARAM))SendMessageA;
    }
    v7(DlgItem, 0xCu, 0, (LPARAM)lParam);
    sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], &dir[20], v21);
    v7(v1, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
  }
  for ( j = 0; j < 6; ++j )
  {
    v9 = *(&((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87F8)->nCombatEXP + j);
    v10 = *((_BYTE *)&((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87F8)->dwSkillID[5] + j);
    if ( v9 )
    {
      v11 = (char *)(((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(v9) + 28);
    }
    else
    {
      v11 = &unk_5D89B0;
      v10 = 0;
    }
    switch ( j )
    {
      case 0:
        v12 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1075);
        goto LABEL_32;
      case 1:
        v12 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1047);
        goto LABEL_32;
      case 2:
        v15 = 1048;
        goto LABEL_31;
      case 3:
        v12 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1049);
        goto LABEL_32;
      case 4:
        v12 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1050);
        goto LABEL_32;
      case 5:
        v15 = 1051;
LABEL_31:
        v12 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, v15);
LABEL_32:
        hWnd = v12;
        break;
      default:
        break;
    }
    SendMessageA(hWnd, 0xCu, 0, (LPARAM)v11);
    if ( v10 )
      result = SendMessageA(hWnd, 0xF1u, 1u, 0);
    else
      result = SendMessageA(hWnd, 0xF1u, 0, 0);
  }
  return result;
}

// 0x004E3D90
void CCBUI::InitUI_4E3D90()
{
  CCBUI *v1; // ebx
  HWND DlgItem; // edi
  HWND v3; // ebp
  HWND v4; // eax
  bool v5; // bl
  char v6; // bl
  int j; // edi
  int v8; // ebp
  HWND v9; // eax
  int v10; // [esp-0x4] [ebp-0x28]
  int v11; // [esp-0x4] [ebp-0x28]
  bool v12; // [esp+0x13] [ebp-0x11]
  HWND hWnd; // [esp+0x14] [ebp-0x10]
  int i; // [esp+0x18] [ebp-0xC]
  unsigned int nVal; // [esp+0x20] [ebp-0x4]
DlgItem = 0;
  v3 = 0;
  hWnd = 0;
  for ( i = 0; i < 8; ++i )
  {
    nVal = ((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC)->dwSkillID[8
                                                                                              * g_RoleSystemCombat.m_configData[1]
                                                                                              + 7
                                                                                              + i];
    ((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC);
    ((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC);
    if ( nVal )
    {
      ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(nVal);
      switch ( i )
      {
        case 0:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1052);
          v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1102);
          goto LABEL_13;
        case 1:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1054);
          v10 = 1103;
          goto LABEL_12;
        case 2:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1055);
          v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1105);
          goto LABEL_13;
        case 3:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1056);
          v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1106);
          goto LABEL_13;
        case 4:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1057);
          v10 = 1107;
          goto LABEL_12;
        case 5:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1058);
          v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1109);
          goto LABEL_13;
        case 6:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1060);
          v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1110);
          goto LABEL_13;
        case 7:
          DlgItem = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1061);
          v10 = 1112;
LABEL_12:
          v4 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, v10);
LABEL_13:
          v3 = v4;
          break;
        default:
          break;
      }
      v5 = SendMessageA(DlgItem, 0xF0u, 0, 0) == 1;
      *((_BYTE *)&((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC)->dwMagicID[7][2 * g_RoleSystemCombat.m_configData[1] + 1]
      + i) = v5;
      SendMessageA(v3, 0xDu, 2u, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
      v6 = atoi((const char *)&g_RoleSystemCombat.m_teamSlots[264]) - 1;
      ((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC)->bMagicMastered[8][8 * g_RoleSystemCombat.m_configData[1] + 4 + i] = v6;
}
  }
  for ( j = 0; j < 6; ++j )
  {
    v8 = *(&((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC)->nCombatEXP + j);
    ((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC);
    if ( v8 )
    {
      switch ( j )
      {
        case 0:
          v9 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1075);
          goto LABEL_26;
        case 1:
          v9 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1047);
          goto LABEL_26;
        case 2:
          v11 = 1048;
          goto LABEL_25;
        case 3:
          v9 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1049);
          goto LABEL_26;
        case 4:
          v9 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, 1050);
          goto LABEL_26;
        case 5:
          v11 = 1051;
LABEL_25:
          v9 = GetDlgItem(g_RoleSystemCombat.g_hCombatDlg1, v11);
LABEL_26:
          hWnd = v9;
          break;
        default:
          break;
      }
      v12 = SendMessageA(hWnd, 0xF0u, 0, 0) == 1;
      *((_BYTE *)&((CCBRoleState *)this->m_fontcolor.Color)->InitUI(dword_5D87FC)->dwSkillID[5] + j) = v12;
    }
  }
}

// 0x004E4A80
LRESULT CCBUI::PopulateCommandList()
{
  HWND DlgItem; // ebx
  LPARAM v2; // ebp
  int *TargetRole; // eax
  int v4; // edi
  int SkillNum; // eax
  int ItemPrice; // eax
  int ItemWeight; // eax
  int ItemData; // eax
  int v10; // [esp-0x4] [ebp-0x17C]
  int SlotCount; // [esp+0x14] [ebp-0x164]
  HWND v13; // [esp+0x18] [ebp-0x160]
  HWND v14; // [esp+0x1C] [ebp-0x15C]
  HWND v15; // [esp+0x20] [ebp-0x158]
  HWND v16; // [esp+0x24] [ebp-0x154]
  HWND v17; // [esp+0x28] [ebp-0x150]
  HWND v18; // [esp+0x2C] [ebp-0x14C]
  HWND hWnd; // [esp+0x30] [ebp-0x148]
  HWND v20; // [esp+0x34] [ebp-0x144]
  LPARAM lParam[11]; // [esp+0x38] [ebp-0x140] BYREF
  int v22; // [esp+0x64] [ebp-0x114]
  int v23; // [esp+0x68] [ebp-0x110]
  _BYTE pOut[12]; // [esp+0x6C] [ebp-0x10C] BYREF
  char Buffer[256]; // [esp+0x78] [ebp-0x100] BYREF

  DlgItem = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1142);
  GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1146);
  hWnd = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1040);
  v15 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1149);
  v18 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1086);
  v17 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1145);
  v13 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1143);
  v20 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1144);
  v14 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1147);
  v16 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1148);
  SlotCount = ((Combat *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSlotCount();
  ((PAL_GDB *)&g_pGDB)->GDB_GetSkillID();
  v2 = 0;
  memset(lParam, 0, 0x28u);
  SendMessageA(DlgItem, 0x1009u, 0, 0);
  lParam[0] = 1;
  lParam[2] = 0;
  lParam[5] = (LPARAM)Buffer;
  if ( SlotCount > 0 )
  {
    do
    {
      TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
      v4 = *TargetRole;
      v10 = *TargetRole;
      v22 = TargetRole[1];
      v23 = TargetRole[2];
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v10);
      sprintf(Buffer, byte_5967B0, SkillNum + 4);
      lParam[1] = v2;
      lParam[2] = 0;
      SendMessageA(DlgItem, 0x1007u, 0, (LPARAM)lParam);
      lParam[2] = 1;
      sprintf(Buffer, &dir[20], v22);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 2;
      ItemPrice = ((PAL_GDB *)this)->GetItemPrice(v4);
      sprintf(Buffer, &dir[20], ItemPrice);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 3;
      ItemWeight = ((PAL_GDB *)this)->GetItemWeight(v4);
      sprintf(Buffer, &dir[20], ItemWeight);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      lParam[2] = 4;
      ItemData = ((PAL_GDB *)this)->GetItemData(v4);
      sprintf(Buffer, &dir[20], ItemData);
      SendMessageA(DlgItem, 0x1006u, 0, (LPARAM)lParam);
      ++v2;
    }
    while ( v2 < SlotCount );
  }
  EnableWindow(hWnd, 0);
  EnableWindow(v15, 0);
  EnableWindow(v18, 0);
  SendMessageA(v17, 0xCu, 0, (LPARAM)g_szSceneUIText);
  SendMessageA(v13, 0xCu, 0, (LPARAM)g_szSceneUIText);
  SendMessageA(v20, 0xCu, 0, (LPARAM)g_szSceneUIText);
  SendMessageA(v14, 0xCu, 0, (LPARAM)g_szSceneUIText);
  return SendMessageA(v16, 0xCu, 0, (LPARAM)g_szSceneUIText);
}

// 0x004E4D70
LRESULT CCBUI::ShowCommandDetails()
{
  HWND DlgItem; // edi
  HWND v3; // ebp
  int *TargetRole; // eax
  int v5; // esi
  int SkillNum; // eax
  int ItemPrice; // eax
  int ItemWeight; // eax
  int ItemData; // eax
  HWND v11; // [esp+0x10] [ebp-0x124]
  HWND v12; // [esp+0x14] [ebp-0x120]
  HWND hWnd; // [esp+0x18] [ebp-0x11C]
  int v14; // [esp+0x20] [ebp-0x114]
  _BYTE pOut[12]; // [esp+0x28] [ebp-0x10C] BYREF
  char lParam[256]; // [esp+0x34] [ebp-0x100] BYREF

  GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1142);
  GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1146);
  DlgItem = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1145);
  v3 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1143);
  hWnd = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1144);
  v12 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1147);
  v11 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1148);
  TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
  v5 = *TargetRole;
  v14 = TargetRole[1];
  SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*TargetRole);
  sprintf(lParam, byte_5967B0, SkillNum + 4);
  SendMessageA(DlgItem, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, &dir[20], v14);
  SendMessageA(v3, 0xCu, 0, (LPARAM)lParam);
  ItemPrice = ((PAL_GDB *)this)->GetItemPrice(v5);
  sprintf(lParam, &dir[20], ItemPrice);
  SendMessageA(hWnd, 0xCu, 0, (LPARAM)lParam);
  ItemWeight = ((PAL_GDB *)this)->GetItemWeight(v5);
  sprintf(lParam, &dir[20], ItemWeight);
  SendMessageA(v12, 0xCu, 0, (LPARAM)lParam);
  ItemData = ((PAL_GDB *)this)->GetItemData(v5);
  sprintf(lParam, &dir[20], ItemData);
  return SendMessageA(v11, 0xCu, 0, (LPARAM)lParam);
}

// 0x004E4F00
int CCBUI::ApplyCommandEdit()
{
  HWND DlgItem; // ebx
  HWND v3; // ebp
  int *TargetRole; // eax
  int v5; // ebx
  int v6; // ebp
  int v7; // esi
  int result; // eax
  gbColorQuad *i; // edx
  void **v10; // ecx
  int *v11; // [esp+0x0] [ebp-0x130]
  HWND hWnda; // [esp+0x10] [ebp-0x120]
  void *hWnd; // [esp+0x10] [ebp-0x120]
  int p_DWORD; // [esp+0x14] [ebp-0x11C] BYREF
  int v15; // [esp+0x18] [ebp-0x118]
  int v16; // [esp+0x1C] [ebp-0x114]
  HWND v17; // [esp+0x20] [ebp-0x110]
  _BYTE pOut[12]; // [esp+0x24] [ebp-0x10C] BYREF
  char lParam[256]; // [esp+0x30] [ebp-0x100] BYREF

  v15 = 0;
  v16 = 0;
  p_DWORD = 0xFFFF;
  DlgItem = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1143);
  v3 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1144);
  hWnda = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1147);
  v17 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1148);
  TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
  p_DWORD = *TargetRole;
  v15 = TargetRole[1];
  v16 = TargetRole[2];
  ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(p_DWORD);
  SendMessageA(DlgItem, 0xDu, 0x14u, (LPARAM)lParam);
  v5 = atoi(lParam);
  SendMessageA(v3, 0xDu, 0x14u, (LPARAM)lParam);
  v6 = atoi(lParam);
  SendMessageA(hWnda, 0xDu, 0x14u, (LPARAM)lParam);
  hWnd = (void *)atoi(lParam);
  SendMessageA(v17, 0xDu, 0x14u, (LPARAM)lParam);
  v7 = atoi(lParam);
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
  if ( v5 > 0 )
  {
    v15 = v5;
    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&p_DWORD, v11);
  }
  result = 0;
  for ( i = &this->m_wndcolor; ; i += 4 )
  {
    if ( i->Color == p_DWORD )
    {
// [VFTABLE] v10 = &this->__vftable + 4 * result;
      goto LABEL_10;
    }
    if ( !i->Color )
      break;
    if ( ++result >= 500 )
    {
      BYTE2(g_RoleSystemCombat.m_configData[2]) = 1;
      return result;
    }
  }
// [VFTABLE] v10 = &this->__vftable + 4 * result;
  v10[2] = (void *)p_DWORD;
LABEL_10:
  result = 16 * (result + 1);
  v10[3] = (void *)v6;
// [VFTABLE] *(vtbl_0056AE2C **)((char *)&this->__vftable + result) = hWnd;
  v10[5] = (void *)v7;
  BYTE2(g_RoleSystemCombat.m_configData[2]) = 1;
  return result;
}

// 0x004E5170
int CCBUI::ShowSkillDetails()
{
  HWND DlgItem; // edi
  HWND v2; // ebx
  HWND v3; // ebp
  int *TargetRole; // eax
  __int16 *SkillNum; // esi
  HWND hWnd; // [esp+0x10] [ebp-0x120]
  HWND v8; // [esp+0x14] [ebp-0x11C]
  int v9; // [esp+0x1C] [ebp-0x114]
  _BYTE pOut[12]; // [esp+0x24] [ebp-0x10C] BYREF
  char lParam[256]; // [esp+0x30] [ebp-0x100] BYREF

  GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1142);
  GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1146);
  DlgItem = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1145);
  v2 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1143);
  v3 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1144);
  hWnd = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1147);
  v8 = GetDlgItem((HWND)g_RoleSystemCombat.m_nActorRenderCount, 1148);
  TargetRole = (int *)((CCBAI *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetTargetRole(pOut);
  v9 = TargetRole[1];
  SkillNum = (__int16 *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*TargetRole);
  sprintf(lParam, byte_5967B0, SkillNum + 2);
  SendMessageA(DlgItem, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, &dir[20], v9);
  SendMessageA(v2, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, &dir[20], SkillNum[322]);
  SendMessageA(v3, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, &dir[20], SkillNum[323]);
  SendMessageA(hWnd, 0xCu, 0, (LPARAM)lParam);
  sprintf(lParam, &dir[20], SkillNum[324]);
  return SendMessageA(v8, 0xCu, 0, (LPARAM)lParam);
}

// 0x004E53C0
LRESULT CCBUI::SendWindowMessage(HWND hWnd, LPARAM lParam)
{
  return SendMessageA(hWnd, 0xCu, 0, lParam);
}

// 0x004E53E0
LRESULT CCBUI::FormatCombatBuffer(HWND hWnd, int nVal)
{
  sprintf((char *const)&g_RoleSystemCombat.m_teamSlots[264], "%lu", nVal);
  return SendMessageA(hWnd, 0xCu, 0, (LPARAM)&g_RoleSystemCombat.m_teamSlots[264]);
}

// 0x004E5490
int CCBUI::StartMagicThread()
{
  CCBControl *Update_2ff0; // ecx
  int v3; // edx
  int result; // eax

// [VFTABLE] ((CCBSystem *)this->__vftable->Destroy)->SetThreadFlag(0);
// [VFTABLE] ((CCBUI *)this->__vftable->Render)->CreateMagicWindow();
// [VFTABLE] Update_2ff0 = (CCBControl *)this->__vftable->Update_2ff0;
  if ( Update_2ff0->m_bActive )
    ((CCBControl *)Update_2ff0)->GetState();
  v3 = 0;
  for ( result = 24; result < 68; result += 4 )
  {
// [VFTABLE] if ( *((_BYTE *)this->__vftable->Create + v3 + 577) )
    {
// [VFTABLE] *(_BYTE *)(*(_DWORD *)((char *)this->__vftable->sub_4431B0 + result) + 280) = 0;
// [VFTABLE] *(_BYTE *)(*(_DWORD *)((char *)this->__vftable->sub_4431B0 + result) + 274) = 0;
    }
    v3 += 892;
  }
  return result;
}

// 0x004EA4A0
LRESULT CCBUI::_nearby_4ea4a0(void *hDlg, HWND arg4, int a3)
{
  int v5; // esi
  HWND *v6; // edi
  int v7; // ecx
  LPARAM v8; // eax
  LRESULT result; // eax
  _DWORD v10[13]; // [esp+0x10] [ebp-0x34] BYREF

  v10[0] = GetDlgItem((HWND)hDlg, 1264);
  v10[1] = GetDlgItem((HWND)hDlg, 1263);
  v10[2] = GetDlgItem((HWND)hDlg, 1265);
  v10[3] = GetDlgItem((HWND)hDlg, 1266);
  v10[4] = GetDlgItem((HWND)hDlg, 1267);
  v10[5] = GetDlgItem((HWND)hDlg, 1268);
  v10[6] = GetDlgItem((HWND)hDlg, 1269);
  v10[7] = GetDlgItem((HWND)hDlg, 1270);
  v10[8] = GetDlgItem((HWND)hDlg, 1271);
  v10[9] = GetDlgItem((HWND)hDlg, 1272);
  v10[10] = GetDlgItem((HWND)hDlg, 1273);
  v10[11] = GetDlgItem((HWND)hDlg, 1274);
  v10[12] = GetDlgItem((HWND)hDlg, 1275);
  v5 = 0;
  v6 = (HWND *)v10;
  do
  {
// [VFTABLE] v7 = *((_DWORD *)this->__vftable[1].Create + 18 * (_DWORD)arg4 + 24);
    v8 = (*(int ( **)(int, int))(*(_DWORD *)v7 + 40))(v7, v5);
    result = ((CCBUI *)*v6)->SendWindowMessage(v8);
    ++v5;
    ++v6;
  }
  while ( v5 < 13 );
  return result;
}

// 0x004EA5C0
int CCBUI::DlgProcCameraEdit(HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam)
{
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  _BYTE *v10; // edi
  bool v11; // zf
  HWND hWnd; // [esp+0x8] [ebp-0x4]
  HWND hDlga; // [esp+0x14] [ebp+0x8]

  hDlga = GetDlgItem(hDlg, 1225);
  hWnd = GetDlgItem(hDlg, 1226);
  if ( uMsg == 272 )
  {
    v7 = -1;
    if ( a1->m_CamEntries[1405] == -1 )
    {
      v8 = a1->m_CamEntries[1404];
      if ( v8 != -1 )
      {
        v9 = LODWORD(a1->m_CCT->m_Pool[0].StartPos.yaw) + 72 * v8;
        v10 = (_BYTE *)(v9 + 58);
        do
        {
          if ( !v7 )
            break;
          v11 = *v10++ == 0;
          --v7;
        }
        while ( !v11 );
        if ( -v7 == 2 )
          ((CCBUI *)hDlga)->SendWindowMessage(v9 + 28);
        else
          ((CCBUI *)hDlga)->SendWindowMessage(v9 + 58);
        EditBox_SetInt(hWnd, a1->m_CamEntries[1404]);
      }
    }
    ((CCBUI *)a1)->_nearby_4ea6d0(hDlg, a1->m_CamEntries[1405]);
  }
  else if ( uMsg == 273 )
  {
    if ( wParam == 1 )
    {
      if ( ((CCBUI *)a1)->_nearby_4eac10(hDlg, a1->m_CamEntries[1405]) )
      {
        ((CCBStageCam *)a1)->sub_4E95A0(g_hMainWnd);
        EndDialog(hDlg, 1);
        goto LABEL_8;
      }
    }
    else if ( wParam == 2 )
    {
      EndDialog(hDlg, 2);
LABEL_8:
      *(_DWORD *)&g_RoleSystemCombat.m_bWPARAM_17A9926 = 0;
      return 0;
    }
  }
  return 0;
}

// 0x004EA6D0
char CCBUI::_nearby_4ea6d0(HWND hDlg, int a3)
{
  _DWORD *v4; // ebx
  int EffSlot; // eax
  int v6; // edx
  int v7; // edi
  LRESULT v8; // eax
  BOOL v9; // edx
  BOOL v10; // ecx
  int v12; // [esp+0x0] [ebp-0x1B4]
  HWND v13; // [esp+0x10] [ebp-0x1A4]
  HWND v14; // [esp+0x14] [ebp-0x1A0]
  HWND v15; // [esp+0x18] [ebp-0x19C]
  HWND v16; // [esp+0x1C] [ebp-0x198]
  HWND v17; // [esp+0x20] [ebp-0x194]
  HWND v18; // [esp+0x24] [ebp-0x190]
  HWND v19; // [esp+0x28] [ebp-0x18C]
  HWND v20; // [esp+0x2C] [ebp-0x188]
  HWND v21; // [esp+0x30] [ebp-0x184]
  HWND v22; // [esp+0x34] [ebp-0x180]
  HWND v23; // [esp+0x38] [ebp-0x17C]
  HWND v24; // [esp+0x3C] [ebp-0x178]
  HWND v25; // [esp+0x40] [ebp-0x174]
  HWND v26; // [esp+0x44] [ebp-0x170]
  HWND v27; // [esp+0x48] [ebp-0x16C]
  HWND v28; // [esp+0x4C] [ebp-0x168]
  HWND v29; // [esp+0x50] [ebp-0x164]
  HWND v30; // [esp+0x54] [ebp-0x160]
  HWND DlgItem; // [esp+0x58] [ebp-0x15C]
  HWND v32; // [esp+0x5C] [ebp-0x158]
  HWND hWnd; // [esp+0x60] [ebp-0x154]
  HWND v34; // [esp+0x64] [ebp-0x150]
  HWND v35; // [esp+0x68] [ebp-0x14C]
  HWND v36; // [esp+0x6C] [ebp-0x148]
  HWND v37; // [esp+0x70] [ebp-0x144]
  HWND v38; // [esp+0x74] [ebp-0x140]
  HWND v39; // [esp+0x78] [ebp-0x13C]
  HWND v40; // [esp+0x7C] [ebp-0x138]
  HWND v41; // [esp+0x80] [ebp-0x134]
  HWND v42; // [esp+0x84] [ebp-0x130]
  HWND v43; // [esp+0x88] [ebp-0x12C]
  HWND v44; // [esp+0x8C] [ebp-0x128]
  HWND v45; // [esp+0x90] [ebp-0x124]
  HWND v46; // [esp+0x94] [ebp-0x120]
  HWND v47; // [esp+0x98] [ebp-0x11C]
  _DWORD v48[70]; // [esp+0x9C] [ebp-0x118] BYREF

  DlgItem = GetDlgItem(hDlg, 1225);
  v15 = GetDlgItem(hDlg, 1226);
  v17 = GetDlgItem(hDlg, 1207);
  v47 = GetDlgItem(hDlg, 1206);
  v19 = GetDlgItem(hDlg, 1227);
  hWnd = GetDlgItem(hDlg, 1228);
  v41 = GetDlgItem(hDlg, 1248);
  v21 = GetDlgItem(hDlg, 1229);
  v22 = GetDlgItem(hDlg, 1216);
  v20 = GetDlgItem(hDlg, 1217);
  v18 = GetDlgItem(hDlg, 1221);
  v43 = GetDlgItem(hDlg, 1218);
  v29 = GetDlgItem(hDlg, 1219);
  v39 = GetDlgItem(hDlg, 1220);
  v13 = GetDlgItem(hDlg, 1244);
  v14 = GetDlgItem(hDlg, 1245);
  v16 = GetDlgItem(hDlg, 1230);
  v27 = GetDlgItem(hDlg, 1222);
  v35 = GetDlgItem(hDlg, 1232);
  v23 = GetDlgItem(hDlg, 1231);
  v45 = GetDlgItem(hDlg, 1233);
  v25 = GetDlgItem(hDlg, 1234);
  v37 = GetDlgItem(hDlg, 1224);
  v24 = GetDlgItem(hDlg, 1223);
  v26 = GetDlgItem(hDlg, 1235);
  v28 = GetDlgItem(hDlg, 1236);
  v30 = GetDlgItem(hDlg, 1237);
  v32 = GetDlgItem(hDlg, 1247);
  v34 = GetDlgItem(hDlg, 1238);
  v36 = GetDlgItem(hDlg, 1239);
  v38 = GetDlgItem(hDlg, 1240);
  v40 = GetDlgItem(hDlg, 1241);
  v42 = GetDlgItem(hDlg, 1242);
  v44 = GetDlgItem(hDlg, 1243);
  v46 = GetDlgItem(hDlg, 1246);
  v4 = v48;
  if ( a3 == -1 )
  {
    EffSlot = *((_DWORD *)this + 2015);
    if ( EffSlot == -1 )
      return EffSlot;
// [VFTABLE] v6 = *((_DWORD *)this->__vftable[1].Create + 18 * EffSlot + 23);
    memset(v48, 0, sizeof(v48));
    v48[51] = -1;
    v48[42] = 1;
    v48[43] = 1;
    v48[44] = 1;
    v48[50] = 1065353216;
  }
  else
  {
    v4 = (_DWORD *)(280 * a3 + 24433456);
    LOBYTE(EffSlot) = g_EffTable[280 * a3 + 212];
    if ( !(_BYTE)EffSlot )
      return EffSlot;
    v6 = *(_DWORD *)&g_EffTable[280 * a3];
  }
// [VFTABLE] EffSlot = ((CEffMgr *)this->__vftable[1].Create)->FindEffSlot(v6);
  v7 = EffSlot;
  if ( EffSlot != -1 )
  {
    this->_nearby_4ea4a0(hDlg, (HWND)EffSlot, v12);
// [VFTABLE] ((CCBUI *)DlgItem)->SendWindowMessage((LPARAM)this->__vftable[1].Create + 72 * v7 + 28);
    EditBox_SetInt(v15, v7);
    ((CCBUI *)v47)->SendWindowMessage((LPARAM)(v4 + 10));
    v8 = ((CCBUI *)v17)->SendWindowMessage((LPARAM)(v4 + 1));
    LOBYTE(v8) = *((_BYTE *)v4 + 213);
    EditBox_SetReadOnly(hWnd, v8);
    LOBYTE(v9) = *((_BYTE *)v4 + 214);
    EditBox_SetReadOnly(v19, v9);
    LOBYTE(v10) = *((_BYTE *)v4 + 215);
    EditBox_SetReadOnly(v41, v10);
    EditBox_SetInt(v21, v4[52]);
    ((CCBUI *)v35)->FormatCombatBuffer(HIBYTE(v4[51]));
    ((CCBUI *)v23)->FormatCombatBuffer(*((unsigned __int8 *)v4 + 206));
    ((CCBUI *)v45)->FormatCombatBuffer(*((unsigned __int8 *)v4 + 205));
    ((CCBUI *)v25)->FormatCombatBuffer((unsigned __int8)v4[51]);
    EditBox_SetFloat(v37, *((float *)v4 + 45));
    EditBox_SetFloat(v27, *((float *)v4 + 50));
    EditBox_SetFloat(v43, *((float *)v4 + 46));
    EditBox_SetFloat(v29, *((float *)v4 + 47));
    EditBox_SetFloat(v39, *((float *)v4 + 48));
    EditBox_SetFloat(v13, *((float *)v4 + 54));
    EditBox_SetFloat(v14, *((float *)v4 + 49));
    EditBox_SetFloat(v16, *((float *)v4 + 55));
    EditBox_SetInt(v18, v4[44]);
    EditBox_SetInt(v20, v4[43]);
    EditBox_SetInt(v22, v4[42]);
    EditBox_SetFloat(v24, *((float *)v4 + 56));
    EditBox_SetFloat(v26, *((float *)v4 + 57));
    EditBox_SetFloat(v28, *((float *)v4 + 58));
    EditBox_SetFloat(v30, *((float *)v4 + 59));
    EditBox_SetFloat(v32, *((float *)v4 + 60));
    EditBox_SetFloat(v34, *((float *)v4 + 61));
    EditBox_SetFloat(v36, *((float *)v4 + 62));
    EditBox_SetFloat(v38, *((float *)v4 + 63));
    EditBox_SetFloat(v40, *((float *)v4 + 64));
    EditBox_SetFloat(v42, *((float *)v4 + 65));
    EditBox_SetFloat(v44, *((float *)v4 + 66));
    LOBYTE(EffSlot) = EditBox_SetFloat(v46, *((float *)v4 + 67));
  }
  return EffSlot;
}

// 0x004EAC10
char CCBUI::_nearby_4eac10(HWND hDlg, int a3)
{
  HWND v3; // ebx
  HWND v4; // ebp
  char *EditBoxText; // eax
  int v6; // esi
  int v7; // edi
  int v8; // ebx
  const char *v9; // eax
  int v10; // edi
  char *v11; // ecx
  int v12; // ecx
  char *v13; // eax
  const char *v15; // ebx
  const char *v16; // eax
  int *v17; // esi
  int v18; // edx
  const char **v19; // ecx
  HWND v21; // [esp+0x14] [ebp-0x198]
  HWND v22; // [esp+0x18] [ebp-0x194]
  HWND v23; // [esp+0x1C] [ebp-0x190]
  HWND DlgItem; // [esp+0x20] [ebp-0x18C]
  HWND v25; // [esp+0x24] [ebp-0x188]
  HWND v26; // [esp+0x28] [ebp-0x184]
  HWND v27; // [esp+0x2C] [ebp-0x180]
  HWND v28; // [esp+0x30] [ebp-0x17C]
  HWND v29; // [esp+0x34] [ebp-0x178]
  HWND v30; // [esp+0x38] [ebp-0x174]
  HWND v31; // [esp+0x3C] [ebp-0x170]
  HWND v32; // [esp+0x40] [ebp-0x16C]
  HWND v33; // [esp+0x44] [ebp-0x168]
  HWND v34; // [esp+0x48] [ebp-0x164]
  HWND v35; // [esp+0x4C] [ebp-0x160]
  HWND v36; // [esp+0x50] [ebp-0x15C]
  HWND v37; // [esp+0x54] [ebp-0x158]
  HWND v38; // [esp+0x58] [ebp-0x154]
  HWND v39; // [esp+0x5C] [ebp-0x150]
  HWND v40; // [esp+0x60] [ebp-0x14C]
  HWND v41; // [esp+0x64] [ebp-0x148]
  HWND v42; // [esp+0x68] [ebp-0x144]
  HWND v43; // [esp+0x6C] [ebp-0x140]
  HWND v44; // [esp+0x70] [ebp-0x13C]
  HWND v45; // [esp+0x74] [ebp-0x138]
  HWND v46; // [esp+0x78] [ebp-0x134]
  HWND v47; // [esp+0x7C] [ebp-0x130]
  HWND v48; // [esp+0x80] [ebp-0x12C]
  HWND v49; // [esp+0x84] [ebp-0x128]
  HWND v50; // [esp+0x88] [ebp-0x124]
  HWND v51; // [esp+0x8C] [ebp-0x120]
  HWND hWnd; // [esp+0x90] [ebp-0x11C]
  const char *EditorTaskDescription; // [esp+0x94] [ebp-0x118] BYREF
  char nIndex[36]; // [esp+0x98] [ebp-0x114] BYREF
  char v55[128]; // [esp+BCh] [ebp-F0h] BYREF
  int v56; // [esp+0x13C] [ebp-0x70]
  int v57; // [esp+0x140] [ebp-0x6C]
  int v58; // [esp+0x144] [ebp-0x68]
  float Float; // [esp+0x148] [ebp-0x64]
  float v60; // [esp+0x14C] [ebp-0x60]
  float v61; // [esp+0x150] [ebp-0x5C]
  float v62; // [esp+0x154] [ebp-0x58]
  float v63; // [esp+0x158] [ebp-0x54]
  float v64; // [esp+0x15C] [ebp-0x50]
  int v65; // [esp+0x160] [ebp-0x4C]
  int Int; // [esp+0x164] [ebp-0x48]
  char v67; // [esp+0x168] [ebp-0x44]
  bool IsModified; // [esp+0x169] [ebp-0x43]
  bool v69; // [esp+0x16A] [ebp-0x42]
  bool v70; // [esp+0x16B] [ebp-0x41]
  float v71; // [esp+0x16C] [ebp-0x40]
  float v72; // [esp+0x170] [ebp-0x3C]
  float v73; // [esp+0x174] [ebp-0x38]
  float v74; // [esp+0x178] [ebp-0x34]
  float v75; // [esp+0x17C] [ebp-0x30]
  float v76; // [esp+0x180] [ebp-0x2C]
  float v77; // [esp+0x184] [ebp-0x28]
  float v78; // [esp+0x188] [ebp-0x24]
  float v79; // [esp+0x18C] [ebp-0x20]
  float v80; // [esp+0x190] [ebp-0x1C]
  float v81; // [esp+0x194] [ebp-0x18]
  float v82; // [esp+0x198] [ebp-0x14]
  float v83; // [esp+0x19C] [ebp-0x10]
  float v84; // [esp+0x1A0] [ebp-0xC]

  DlgItem = GetDlgItem(hDlg, 1225);
  v51 = GetDlgItem(hDlg, 1207);
  v49 = GetDlgItem(hDlg, 1206);
  v3 = GetDlgItem(hDlg, 1227);
  v4 = GetDlgItem(hDlg, 1228);
  hWnd = GetDlgItem(hDlg, 1248);
  v38 = GetDlgItem(hDlg, 1229);
  v23 = GetDlgItem(hDlg, 1216);
  v22 = GetDlgItem(hDlg, 1217);
  v21 = GetDlgItem(hDlg, 1221);
  v42 = GetDlgItem(hDlg, 1218);
  v32 = GetDlgItem(hDlg, 1219);
  v48 = GetDlgItem(hDlg, 1220);
  v34 = GetDlgItem(hDlg, 1244);
  v44 = GetDlgItem(hDlg, 1245);
  v36 = GetDlgItem(hDlg, 1230);
  v30 = GetDlgItem(hDlg, 1222);
  v46 = GetDlgItem(hDlg, 1232);
  v26 = GetDlgItem(hDlg, 1231);
  v40 = GetDlgItem(hDlg, 1233);
  v28 = GetDlgItem(hDlg, 1234);
  v50 = GetDlgItem(hDlg, 1224);
  v25 = GetDlgItem(hDlg, 1223);
  v27 = GetDlgItem(hDlg, 1235);
  v29 = GetDlgItem(hDlg, 1236);
  v31 = GetDlgItem(hDlg, 1237);
  v33 = GetDlgItem(hDlg, 1247);
  v35 = GetDlgItem(hDlg, 1238);
  v37 = GetDlgItem(hDlg, 1239);
  v39 = GetDlgItem(hDlg, 1240);
  v41 = GetDlgItem(hDlg, 1241);
  v43 = GetDlgItem(hDlg, 1242);
  v45 = GetDlgItem(hDlg, 1243);
  v47 = GetDlgItem(hDlg, 1246);
  IsModified = EditBox_IsModified(v4);
  v69 = EditBox_IsModified(v3);
  v70 = EditBox_IsModified(hWnd);
  Int = EditBox_GetInt(v38);
  v67 = 1;
  if ( (byte_1895559 & 1) == 0 )
  {
    byte_1895559 |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  EditBoxText = GetEditBoxText(DlgItem);
  EditorTaskDescription = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)EditBoxText);
  v6 = EditBox_GetInt(v46) << 24;
  v7 = EditBox_GetInt(v26) << 16;
  v8 = EditBox_GetInt(v40) << 8;
  v65 = v6 | v7 | v8 | EditBox_GetInt(v28);
  Float = EditBox_GetFloat(v50);
  v64 = EditBox_GetFloat(v30);
  v60 = EditBox_GetFloat(v42);
  v61 = EditBox_GetFloat(v32);
  v62 = EditBox_GetFloat(v48);
  v71 = EditBox_GetFloat(v34);
  v63 = EditBox_GetFloat(v44);
  v72 = EditBox_GetFloat(v36);
  v58 = EditBox_GetInt(v21);
  v57 = EditBox_GetInt(v22);
  v56 = EditBox_GetInt(v23);
  v73 = EditBox_GetFloat(v25);
  v74 = EditBox_GetFloat(v27);
  v75 = EditBox_GetFloat(v29);
  v76 = EditBox_GetFloat(v31);
  v77 = EditBox_GetFloat(v33);
  v78 = EditBox_GetFloat(v35);
  v79 = EditBox_GetFloat(v37);
  v80 = EditBox_GetFloat(v39);
  v81 = EditBox_GetFloat(v41);
  v82 = EditBox_GetFloat(v43);
  v83 = EditBox_GetFloat(v45);
  v84 = EditBox_GetFloat(v47);
  strcpy(v55, GetEditBoxText(v49));
  strcpy(nIndex, GetEditBoxText(v51));
  if ( (byte_1895559 & 1) == 0 )
  {
    byte_1895559 |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  v9 = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)nIndex);
  v10 = a3;
  if ( a3 == -1 )
  {
    v11 = &g_EffTable[36];
    do
    {
      if ( v11[176] && *(const char **)v11 == v9 )
      {
        MessageBoxA(::hWnd, &unk_5D8BE4, Caption, 0);
        return 0;
      }
      v11 += 280;
    }
    while ( (int)v11 < (int)&g_EffTableEnd );
    v12 = 0;
    v13 = &g_EffTable[212];
    while ( *v13 )
    {
      v13 += 280;
      ++v12;
      if ( (int)v13 >= (int)&g_EffTaskEnd )
        return 0;
    }
    v10 = v12;
    *((_DWORD *)this + 2016) = v12;
  }
  else
  {
    v15 = *(const char **)&g_EffTable[280 * a3 + 36];
    if ( (byte_1895559 & 1) == 0 )
    {
      byte_1895559 |= 1u;
      ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
      atexit(todo_401800);
    }
    v16 = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)nIndex);
    if ( v16 != v15 )
    {
      v17 = &g_nSaveSlot1;
      do
      {
        v18 = *(v17 - 1);
        if ( v18 > 0 )
        {
          v19 = (const char **)v17;
          do
          {
            if ( *v19 == v15 )
              *v19 = v16;
            ++v19;
            --v18;
          }
          while ( v18 );
        }
        v17 += 3985;
      }
      while ( (int)v17 < (int)&g_EffTable[4] );
    }
  }
  if ( v10 == -1 )
    return 0;
  sub_4CE030(&EditorTaskDescription, v10);
  return 1;
}

// 0x004EB230
INT_PTR CCBUI::_nearby_4eb230(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  return ((CCBUI *)g_RoleSystemCombat.m_teamSlots[263])->DlgProcCameraConfig(hDlg, a2, a3, a4);
}

// 0x004EB260
int CCBUI::DlgProcCameraConfig(HWND hDlg, UINT uMsg, WORD wParam, LPARAM lParam)
{
  HWND v5; // edi
  HWND DlgItem; // ebp
  HWND v7; // ebx
  int v8; // eax
  int v9; // eax
  LRESULT v11; // eax
  LRESULT v12; // eax
  int v13; // eax
  int v14; // eax
  LPARAM lParama[8]; // [esp+0x10] [ebp-0x20] BYREF

  v5 = hDlg;
  DlgItem = GetDlgItem(hDlg, 1276);
  v7 = GetDlgItem(hDlg, 1278);
  if ( uMsg != 78 )
  {
    if ( uMsg == 272 )
    {
      SetWindowPos(hDlg, 0, 800, 0, 224, 730, 0x80u);
      v11 = SendMessageA(DlgItem, 0x1037u, 0, 0);
      LOBYTE(v11) = v11 | 0x21;
      SendMessageA(DlgItem, 0x1036u, 0, v11);
      memset(lParama, 0, sizeof(lParama));
      lParama[0] = 7;
      lParama[1] = 0;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 0, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 42;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 1u, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 86;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(DlgItem, 0x101Bu, 2u, (LPARAM)lParama);
      v12 = SendMessageA(v7, 0x1037u, 0, 0);
      LOBYTE(v12) = v12 | 0x21;
      SendMessageA(v7, 0x1036u, 0, v12);
      lParama[0] = 7;
      lParama[1] = 0;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v7, 0x101Bu, 0, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 108;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v7, 0x101Bu, 1u, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v7, 0x101Bu, 2u, (LPARAM)lParama);
      lParama[1] = 1;
      lParama[2] = 30;
      lParama[3] = (LPARAM)&g_EffMgr;
      SendMessageA(v7, 0x101Bu, 3u, (LPARAM)lParama);
      return 0;
    }
    if ( uMsg != 273 )
      return 0;
    switch ( wParam )
    {
      case 0x41Fu:
        sub_4CE5C0(LODWORD(a1->m_CCT->m_Pool[0].StartPos.yaw));
        break;
      case 0x421u:
        if ( a1->m_CamEntries[1793] != -1 )
        {
          ((CEffect *)LODWORD(a1->m_CCT->m_Pool[0].StartPos.yaw))->Render(a1->m_CamEntries[1793]);
          ((CEffMgr *)LODWORD(a1->m_CCT->m_Pool[0].StartPos.yaw))->Init(a1->m_CamEntries[1793], 0, 0, 0, 0);
          *(_DWORD *)(LODWORD(a1->m_CCT->m_Pool[0].StartPos.yaw) + 43304) = 0;
        }
        break;
      case 0x4BAu:
        ((CCBStageEffect *)*(CCBStageEffect **)(*(_DWORD *)&a1->m_CCT->m_Pool[0].bValid + 76))->_CCBStageEffect();
        break;
      case 0x4BBu:
        if ( MessageBoxA(hWnd, &unk_5D8B14, &unk_5D8B3C, 1u) == 1 )
        {
          ((CCBCamControl *)a1)->sub_4EB6F0(hDlg);
        }
        v5 = hDlg;
        break;
      case 0x4D0u:
        if ( a1->m_nCurCamIdx == -1 )
        {
          MessageBoxA(hWnd, &unk_5D8C20, "Warning", 0);
        }
        else
        {
          ((CCBCamControl *)a1)->ReadCameraDialog(hDlg);
          ((CCBCamControl *)a1)->sub_4EB8D0(hDlg);
        }
        break;
      case 0x4D5u:
        ((CEffMgr *)LODWORD(a1->m_CCT->m_Pool[0].StartPos.yaw))->ReleaseCompletedEffects();
        break;
      case 0x508u:
        ((PAL_GDB *)a1)->ShowDetailPanel(hDlg);
        break;
      default:
        break;
    }
  }
  if ( wParam == 1276 )
  {
    v13 = *(_DWORD *)(lParam + 8);
    if ( v13 == -3 || v13 == -2 )
    {
      v14 = *(_DWORD *)(lParam + 12);
      if ( v14 != -1 )
      {
        a1->m_CamEntries[1793] = v14;
        return 0;
      }
      a1->m_CamEntries[1793] = -1;
    }
    return 0;
  }
  if ( wParam != 1278 )
    return 0;
  v8 = *(_DWORD *)(lParam + 8);
  if ( v8 != -3 && v8 != -2 )
    return 0;
  v9 = *(_DWORD *)(lParam + 12);
  if ( v9 == -1 )
  {
    a1->m_nCurCamIdx = -1;
  }
  else
  {
    a1->m_nCurCamIdx = v9;
    ((CCBCamControl *)a1)->ShowCameraDialog(v5);
  }
  return 0;
}

// 0x005160A0
int * CCBUI::ctor(int nVal)
{
  sub_516170(this);
  this->m_pSkillWindow = (CCBSkillWindow *)nVal;
  return (int *)this;
}

// 0x005164D0
void CCBUI::Destroy()
{
  UIStatic *m_pAttackSequenBack; // ecx
  UIStatic **p_pPanel; // esi
  int v4; // edi
  UIProgressBar *v5; // ecx
  UIStatic **v6; // esi
  int v7; // edi
  int v8; // ecx
  UIStatic *v9; // ecx
  UIStatic *v10; // ecx
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
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  UIProgressBar *v30; // ecx
  UIProgressBar *v31; // ecx
  UIStatic *v32; // ecx
  UIStatic *v33; // ecx
  UIProgressBar *v34; // ecx
  UIProgressBar *v35; // ecx
  UIProgressBar *v36; // ecx
  UIProgressBar *m_pRoleStateSword; // ecx
  UIStaticCB *m_pTrickName; // ecx
  UIStaticCB *m_pTrickName2; // ecx
  UIStatic *m_pDialogBack; // ecx
  UIStatic *m_pResultLevelup; // ecx
  UIStatic **v42; // esi
  int v43; // edi
  int v44; // ecx
  UIStatic *m_pResultWindLvup; // ecx
  UIStatic *m_pResultThunderLvup; // ecx
  UIStatic *m_pResultWaterLvup; // ecx
  UIStatic *m_pResultFireLvup; // ecx
  UIStatic *m_pResultEarthLvup; // ecx
  UIStatic *m_pResultDoubleLvup; // ecx
  UIStatic *m_pResultGetItem; // ecx
  CCBControlWindow **p_m_pMain; // esi
  int v53; // edi
  UIListBox *v54; // [esp+0x0] [ebp-0x10]
  int v55; // [esp+0x4] [ebp-0xC]

  ((CCBRoleState *)this)->Destroy(v54, v55);
  m_pAttackSequenBack = this->m_pAttackSequenBack;
  if ( m_pAttackSequenBack )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pAttackSequenBack->__vftable->sub_4431B0)(m_pAttackSequenBack, 1);
    this->m_pAttackSequenBack = 0;
  }
  p_pPanel = &this->pPanel;
  v4 = 11;
  do
  {
    if ( *p_pPanel )
    {
// [VFTABLE] ((void ( *)(UIStatic *, int))(*p_pPanel)->__vftable->sub_4431B0)(*p_pPanel, 1);
      *p_pPanel = 0;
    }
    ++p_pPanel;
    --v4;
  }
  while ( v4 );
  v5 = this->m_pRoleStateGP[1];
  if ( v5 )
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v5->__vftable->sub_4431B0)(v5, 1);
    this->m_pRoleStateGP[1] = 0;
  }
  v6 = &this->m_pRoleStateImmunity[6];
  v7 = 4;
  do
  {
    v8 = (int)*(v6 - 225);
    if ( v8 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
      *(v6 - 225) = 0;
    }
    if ( *v6 )
    {
// [VFTABLE] ((void ( *)(UIStatic *, int))(*v6)->__vftable->sub_4431B0)(*v6, 1);
      *v6 = 0;
    }
    v9 = v6[4];
    if ( v9 )
    {
// [VFTABLE] ((void ( *)(UIStatic *, int))v9->__vftable->sub_4431B0)(v9, 1);
      v6[4] = 0;
    }
    v10 = v6[8];
    if ( v10 )
    {
// [VFTABLE] ((void ( *)(UIStatic *, int))v10->__vftable->sub_4431B0)(v10, 1);
      v6[8] = 0;
    }
    v11 = (int)*(v6 - 211);
    if ( v11 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
      *(v6 - 211) = 0;
    }
    v12 = (int)*(v6 - 200);
    if ( v12 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
      *(v6 - 200) = 0;
    }
    v13 = (int)*(v6 - 189);
    if ( v13 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
      *(v6 - 189) = 0;
    }
    v14 = (int)*(v6 - 178);
    if ( v14 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v14 + 20))(v14, 1);
      *(v6 - 178) = 0;
    }
    v15 = (int)*(v6 - 145);
    if ( v15 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v15 + 20))(v15, 1);
      *(v6 - 145) = 0;
    }
    v16 = (int)*(v6 - 134);
    if ( v16 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v16 + 20))(v16, 1);
      *(v6 - 134) = 0;
    }
    v17 = (int)*(v6 - 167);
    if ( v17 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v17 + 20))(v17, 1);
      *(v6 - 167) = 0;
    }
    v18 = (int)*(v6 - 156);
    if ( v18 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v18 + 20))(v18, 1);
      *(v6 - 156) = 0;
    }
    v19 = (int)*(v6 - 123);
    if ( v19 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v19 + 20))(v19, 1);
      *(v6 - 123) = 0;
    }
    v20 = (int)*(v6 - 112);
    if ( v20 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v20 + 20))(v20, 1);
      *(v6 - 112) = 0;
    }
    v21 = (int)*(v6 - 101);
    if ( v21 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v21 + 20))(v21, 1);
      *(v6 - 101) = 0;
    }
    v22 = (int)*(v6 - 90);
    if ( v22 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v22 + 20))(v22, 1);
      *(v6 - 90) = 0;
    }
    v23 = (int)*(v6 - 79);
    if ( v23 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v23 + 20))(v23, 1);
      *(v6 - 79) = 0;
    }
    v24 = (int)*(v6 - 68);
    if ( v24 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v24 + 20))(v24, 1);
      *(v6 - 68) = 0;
    }
    v25 = (int)*(v6 - 57);
    if ( v25 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v25 + 20))(v25, 1);
      *(v6 - 57) = 0;
    }
    v26 = (int)*(v6 - 46);
    if ( v26 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v26 + 20))(v26, 1);
      *(v6 - 46) = 0;
    }
    v27 = (int)*(v6 - 35);
    if ( v27 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v27 + 20))(v27, 1);
      *(v6 - 35) = 0;
    }
    v28 = (int)*(v6 - 24);
    if ( v28 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v28 + 20))(v28, 1);
      *(v6 - 24) = 0;
    }
    v29 = (int)*(v6 - 13);
    if ( v29 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v29 + 20))(v29, 1);
      *(v6 - 13) = 0;
    }
    ++v6;
    --v7;
  }
  while ( v7 );
  v30 = this->m_pRoleStateGP[2];
  if ( v30 )
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v30->__vftable->sub_4431B0)(v30, 1);
    this->m_pRoleStateGP[2] = 0;
  }
  v31 = this->m_pRoleStateGP[3];
  if ( v31 )
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v31->__vftable->sub_4431B0)(v31, 1);
    this->m_pRoleStateGP[3] = 0;
  }
  v32 = this->m_pRoleStateImmunity[4];
  if ( v32 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v32->__vftable->sub_4431B0)(v32, 1);
    this->m_pRoleStateImmunity[4] = 0;
  }
  v33 = this->m_pRoleStateImmunity[5];
  if ( v33 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v33->__vftable->sub_4431B0)(v33, 1);
    this->m_pRoleStateImmunity[5] = 0;
  }
  v34 = this->m_pRoleStateMP[1];
  if ( v34 )
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v34->__vftable->sub_4431B0)(v34, 1);
    this->m_pRoleStateMP[1] = 0;
  }
  v35 = this->m_pRoleStateMP[2];
  if ( v35 )
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v35->__vftable->sub_4431B0)(v35, 1);
    this->m_pRoleStateMP[2] = 0;
  }
  v36 = this->m_pRoleStateMP[3];
  if ( v36 )
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, int))v36->__vftable->sub_4431B0)(v36, 1);
    this->m_pRoleStateMP[3] = 0;
  }
  m_pRoleStateSword = this->m_pRoleStateSword;
  if ( m_pRoleStateSword )
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, int))m_pRoleStateSword->__vftable->sub_4431B0)(m_pRoleStateSword, 1);
    this->m_pRoleStateSword = 0;
  }
  m_pTrickName = this->m_pTrickName;
  if ( m_pTrickName )
  {
// [VFTABLE] ((void ( *)(UIStaticCB *, int))m_pTrickName->__vftable->sub_4431B0)(m_pTrickName, 1);
    this->m_pTrickName = 0;
  }
  m_pTrickName2 = this->m_pTrickName2;
  if ( m_pTrickName2 )
  {
// [VFTABLE] ((void ( *)(UIStaticCB *, int))m_pTrickName2->__vftable->sub_4431B0)(m_pTrickName2, 1);
    this->m_pTrickName2 = 0;
  }
  m_pDialogBack = this->m_pDialogBack;
  if ( m_pDialogBack )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pDialogBack->__vftable->sub_4431B0)(m_pDialogBack, 1);
    this->m_pDialogBack = 0;
  }
  m_pResultLevelup = this->m_pResultLevelup;
  if ( m_pResultLevelup )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultLevelup->__vftable->sub_4431B0)(m_pResultLevelup, 1);
    this->m_pResultLevelup = 0;
  }
  v42 = &this->m_pRoleStatePanel[2];
  v43 = 5;
  do
  {
    v44 = (int)*(v42 - 5);
    if ( v44 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v44 + 20))(v44, 1);
      *(v42 - 5) = 0;
    }
    if ( *v42 )
    {
// [VFTABLE] ((void ( *)(UIStatic *, int))(*v42)->__vftable->sub_4431B0)(*v42, 1);
      *v42 = 0;
    }
    ++v42;
    --v43;
  }
  while ( v43 );
  m_pResultWindLvup = this->m_pResultWindLvup;
  if ( m_pResultWindLvup )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultWindLvup->__vftable->sub_4431B0)(m_pResultWindLvup, 1);
    this->m_pResultWindLvup = 0;
  }
  m_pResultThunderLvup = this->m_pResultThunderLvup;
  if ( m_pResultThunderLvup )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultThunderLvup->__vftable->sub_4431B0)(m_pResultThunderLvup, 1);
    this->m_pResultThunderLvup = 0;
  }
  m_pResultWaterLvup = this->m_pResultWaterLvup;
  if ( m_pResultWaterLvup )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultWaterLvup->__vftable->sub_4431B0)(m_pResultWaterLvup, 1);
    this->m_pResultWaterLvup = 0;
  }
  m_pResultFireLvup = this->m_pResultFireLvup;
  if ( m_pResultFireLvup )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultFireLvup->__vftable->sub_4431B0)(m_pResultFireLvup, 1);
    this->m_pResultFireLvup = 0;
  }
  m_pResultEarthLvup = this->m_pResultEarthLvup;
  if ( m_pResultEarthLvup )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultEarthLvup->__vftable->sub_4431B0)(m_pResultEarthLvup, 1);
    this->m_pResultEarthLvup = 0;
  }
  m_pResultDoubleLvup = this->m_pResultDoubleLvup;
  if ( m_pResultDoubleLvup )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultDoubleLvup->__vftable->sub_4431B0)(m_pResultDoubleLvup, 1);
    this->m_pResultDoubleLvup = 0;
  }
  m_pResultGetItem = this->m_pResultGetItem;
  if ( m_pResultGetItem )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pResultGetItem->__vftable->sub_4431B0)(m_pResultGetItem, 1);
    this->m_pResultGetItem = 0;
  }
  p_m_pMain = &this->m_pMain;
  v53 = 4;
  do
  {
    if ( *p_m_pMain )
    {
// [VFTABLE] ((void ( *)(CCBControlWindow *, int))(*p_m_pMain)->__vftable->sub_4431B0)(*p_m_pMain, 1);
      *p_m_pMain = 0;
    }
    ++p_m_pMain;
    --v53;
  }
  while ( v53 );
}

// 0x00516940
void CCBUI::InitResultPanels()
{
  UIStatic **v2; // edi
  char v3; // al
  UIStatic *v4; // ecx
  UIStatic **v5; // edi
  char v6; // al
  UIStatic *v7; // ecx
  int v8; // [esp+0x10] [ebp-0x10] BYREF
  int v9; // [esp+0x14] [ebp-0xC]
  int v10; // [esp+0x18] [ebp-0x8]
  int v11; // [esp+0x1C] [ebp-0x4]

  v9 = 0;
  v2 = &this->m_pRoleStateImmunity[4];
  v10 = 0;
  v8 = 0;
  v11 = 0;
  ((CCBAIWindow *)this)->Reset((int *)&this->m_pRoleStateImmunity[4]);
  if ( v3 )
  {
    v4 = *v2;
    v8 = 150;
    v10 = 406;
    v9 = -50;
    v11 = 462;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v4->__vftable->Create)(v4, 800, &v8, this);
    ((UIStatic *)*v2)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v2)->__vftable->ShowWindow)(*v2, 0);
    v5 = &this->m_pRoleStateImmunity[5];
    ((CCBAIWindow *)this)->Reset((int *)&this->m_pRoleStateImmunity[5]);
    if ( v6 )
    {
      v7 = *v5;
      v8 = 150;
      v10 = 406;
      v9 = -50;
      v11 = 462;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v7->__vftable->Create)(v7, 816, &v8, this);
      ((UIStatic *)*v5)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v5)->__vftable->ShowWindow)(*v5, 0);
    }
  }
}

// 0x00516A30
char CCBUI::SetupAIWindow()
{
  int v2; // edi
  int *v3; // ebx
  char v4; // al
  int v5; // ecx
  UIStatic *v6; // ecx
  int *v7; // ebx
  int v8; // edi
  UIStatic **v9; // ebp
  char v10; // al
  char v11; // al
  int v12; // ecx
  UIStatic *v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // edx
  int v18; // edi
  UIScene **v19; // ebp
  UIScene **v20; // ebx
  UIProgressBar *v21; // ecx
  UIStatic *v22; // ecx
  UIScene *v23; // ecx
  UIScene *v24; // ecx
  int *v25; // ebx
  int v26; // edi
  char v27; // al
  char v28; // al
  char v29; // al
  char v30; // al
  char v31; // al
  char v32; // al
  char v33; // al
  char v34; // al
  char v35; // al
  char v36; // al
  char v37; // al
  char v38; // al
  char v39; // al
  UIStatic **v40; // ebp
  char v41; // al
  char v42; // al
  char v43; // al
  char v44; // al
  char v45; // al
  char v46; // al
  int v47; // eax
  int v48; // ecx
  int v49; // eax
  int v50; // ecx
  int v51; // eax
  int v52; // ecx
  int v53; // eax
  int v54; // ecx
  int v55; // eax
  int v56; // ecx
  int v57; // eax
  int v58; // ecx
  int v59; // eax
  int v60; // ecx
  int v61; // eax
  int v62; // ecx
  int v63; // eax
  int v64; // ecx
  int v65; // eax
  int v66; // ecx
  int v68; // [esp+0x138] [ebp-0x20]
  int v69; // [esp+0x148] [ebp-0x10] BYREF
  int v70; // [esp+0x14C] [ebp-0xC]
  int v71; // [esp+0x150] [ebp-0x8]
  int v72; // [esp+0x154] [ebp-0x4]

  v70 = 0;
  v71 = 0;
  v69 = 0;
  v72 = 0;
  v2 = 0;
  while ( 1 )
  {
    v3 = (int *)&this->m_pAttackSequenFace[v2 + 4];
    ((CCBAIWindow *)this)->Reset(v3);
    if ( !v4 )
      break;
    v5 = *v3;
    v69 = g_nStatePanelL_dup[v2];
    v71 = v69 + 157;
    v70 = g_nStatePanelT_dup[v2];
    v72 = v70 + 106;
    (*(void ( **)(int, int, int *, CCBUI *, int))(*(_DWORD *)v5 + 16))(
      v5,
      g_nItemTypeBase[v2],
      &v69,
      this,
      v68);
    if ( v2 )
      v6 = (UIStatic *)*v3;
    else
      v6 = this->m_pAttackSequenFace[4];
    ((UIStatic *)v6)->CreateFromTemplate();
    ((NPC *)*v3)->NPC::UpdateAnim();
    v68 = 0;
    (**(void ( ***)(int))*v3)(*v3);
    if ( ++v2 >= 4 )
    {
      v7 = (int *)&this->m_pRoleStatePanel[2];
      v8 = 0;
      while ( 1 )
      {
        v9 = (UIStatic **)(v7 - 5);
        ((CCBAIWindow *)this)->Reset(v7 - 5);
        if ( !v10 )
          break;
        ((CCBAIWindow *)this)->Reset(v7);
        if ( !v11 )
          break;
        v12 = g_nSpriteSize_64[v8];
        v72 = g_nSpriteSize_82[v8] + 12;
        v71 = v12 + 6;
        v13 = *v9;
        v14 = g_nItemIDs_69[v8];
        v69 = 6;
        v70 = 12;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v13->__vftable->Create)(v13, v14, &v69, this);
        ((UIStatic *)*v9)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v9)->__vftable->ShowWindow)(*v9, 0);
        v15 = g_nSpriteSize_20[v8];
        v72 = g_nUnkDataTable[v8] + 10;
        v71 = v15 + 10;
        v16 = *v7;
        v17 = g_nSkillItemIDTable[v8];
        v69 = 10;
        v70 = 10;
        (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v16 + 16))(v16, v17, &v69, this);
        ((UIStatic *)*v7)->CreateFromTemplate();
        (**(void ( ***)(int, _DWORD))*v7)(*v7, 0);
        ++v8;
        ++v7;
        if ( v8 >= 5 )
        {
          v18 = 0;
          while ( (unsigned __int8)sub_51CC20(&this->m_pRoleStateImmunity[v18 + 6]) )
          {
            v19 = (UIScene **)&this->m_pRoleStateImmunity[v18 + 10];
            if ( !(unsigned __int8)sub_51CC20(v19) )
              break;
            v20 = (UIScene **)&this->m_pRoleStateHP[v18 + 1];
            if ( !(unsigned __int8)sub_51CC20(v20) )
              break;
            if ( !v18 )
            {
              if ( !(unsigned __int8)sub_51CC20(&this->m_pRoleStateGP[1]) )
                return 0;
              v21 = this->m_pRoleStateGP[1];
              v69 = g_nCCBAIWindow_17ACB8C;
              v71 = g_nCCBAIWindow_17ACB8C + 30;
              v70 = g_nAIWindowBase;
              v72 = g_nAIWindowBase + 86;
// [VFTABLE] ((void ( *)(UIProgressBar *, int, int *, CCBUI *))v21->__vftable->Create)(v21, 20, &v69, this);
              ((UIScene *)this->m_pRoleStateGP[1])->GetChildCount();
              ((UIScene *)this->m_pRoleStateGP[1])->GetChildAt();
              sub_43FDB0((float *)this->m_pRoleStateGP[1], 2);
// [VFTABLE] ((UIWnd *)&this->m_pRoleStateGP[1]->__vftable)->GetHeight(5);
// [VFTABLE] ((UIWnd *)&this->m_pRoleStateGP[1]->__vftable)->GetPosition(2);
              ((CCBFiveNimbusWindow *)this->m_pRoleStateGP[1])->CalcHitAngle(1);
              this->m_pRoleStateGP[1]->m_decorateRc.left = 0;
              ((UIScrollBar *)this->m_pRoleStateGP[1])->SetRange(50.0);
              ((UIProgressBar *)this->m_pRoleStateGP[1])->FindChildByName(0.0);
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateGP[1]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateGP[1],
// [VFTABLE]   0);
            }
            v22 = this->m_pRoleStateImmunity[v18 + 6];
            v69 = g_nCBCamState[v18 + 2];
            v71 = v69 + 85;
            v70 = g_nCBCamState[v18 + 6];
            v72 = v70 + 12;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v22->__vftable->Create)(
// [VFTABLE]   v22,
// [VFTABLE]   g_nSkillTabIDs[v18],
// [VFTABLE]   &v69,
// [VFTABLE]   this);
            ((UIScene *)this->m_pRoleStateImmunity[v18 + 6])->GetChildCount();
            ((UIScene *)this->m_pRoleStateImmunity[v18 + 6])->GetChildAt();
            sub_43FDB0((float *)this->m_pRoleStateImmunity[v18 + 6], -2);
// [VFTABLE] ((UIWnd *)&this->m_pRoleStateImmunity[v18 + 6]->__vftable)->GetWidth(7);
// [VFTABLE] ((UIWnd *)&this->m_pRoleStateImmunity[v18 + 6]->__vftable)->GetHeight(1);
// [VFTABLE] ((UIWnd *)&this->m_pRoleStateImmunity[v18 + 6]->__vftable)->GetPosition(1);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_pRoleStateImmunity[v18 + 6]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateImmunity[v18 + 6],
// [VFTABLE]   0);
            this->m_pRoleStateImmunity[v18 + 6]->m_pbk = (gbTexture *)1077936128;
            v69 = g_nCBCamState[v18 + 10];
            v71 = v69 + 85;
            v23 = *v19;
            v70 = g_nCBCamState[v18 + 14];
            v72 = v70 + 12;
// [VFTABLE] ((void ( *)(UIScene *, int, int *, CCBUI *))v23->__vftable->Create)(
// [VFTABLE]   v23,
// [VFTABLE]   g_nMagicTabIDs[v18],
// [VFTABLE]   &v69,
// [VFTABLE]   this);
            ((UIScene *)*v19)->GetChildCount();
            ((UIScene *)*v19)->GetChildAt();
            sub_43FDB0((float *)*v19, -2);
// [VFTABLE] ((UIWnd *)&(*v19)->__vftable)->GetWidth(7);
// [VFTABLE] ((UIWnd *)&(*v19)->__vftable)->GetHeight(1);
// [VFTABLE] ((UIWnd *)&(*v19)->__vftable)->GetPosition(1);
// [VFTABLE] ((void ( *)(UIScene *, _DWORD))(*v19)->__vftable->ShowWindow)(*v19, 0);
            (*v19)->m_nRectY = 1077936128;
            v69 = g_nCBCamState[v18 + 18];
            v71 = v69 + 85;
            v24 = *v20;
            v70 = g_nCBCamState[v18 + 22];
            v72 = v70 + 12;
// [VFTABLE] ((void ( *)(UIScene *, int, int *, CCBUI *))v24->__vftable->Create)(
// [VFTABLE]   v24,
// [VFTABLE]   g_nItemTabIDs[v18],
// [VFTABLE]   &v69,
// [VFTABLE]   this);
            ((UIScene *)*v20)->GetChildCount();
            ((UIScene *)*v20)->GetChildAt();
            sub_43FDB0((float *)*v20, -2);
// [VFTABLE] ((UIWnd *)&(*v20)->__vftable)->GetWidth(7);
// [VFTABLE] ((UIWnd *)&(*v20)->__vftable)->GetHeight(1);
// [VFTABLE] ((UIWnd *)&(*v20)->__vftable)->GetPosition(1);
// [VFTABLE] ((void ( *)(UIScene *, _DWORD))(*v20)->__vftable->ShowWindow)(*v20, 0);
            ++v18;
            (*v20)->m_nRectY = 1077936128;
            if ( v18 >= 4 )
            {
              v25 = (int *)&this->m_pRoleStateAttackInc[4];
              v26 = 0;
              while ( 1 )
              {
                ((CCBAIWindow *)this)->Reset(v25 - 11);
                if ( !v27 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25);
                if ( !v28 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 11);
                if ( !v29 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 22);
                if ( !v30 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 55);
                if ( !v31 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 66);
                if ( !v32 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 33);
                if ( !v33 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 44);
                if ( !v34 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 77);
                if ( !v35 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 88);
                if ( !v36 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 99);
                if ( !v37 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 110);
                if ( !v38 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 121);
                if ( !v39 )
                  break;
                v40 = (UIStatic **)(v25 + 132);
                ((CCBAIWindow *)this)->Reset(v25 + 132);
                if ( !v41 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 143);
                if ( !v42 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 154);
                if ( !v43 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 165);
                if ( !v44 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 176);
                if ( !v45 )
                  break;
                ((CCBAIWindow *)this)->Reset(v25 + 187);
                if ( !v46 )
                  break;
                v69 = 15;
                v71 = 37;
                v70 = 85;
                v72 = 108;
                if ( v26 < 4 )
                {
                  v47 = g_nStatePanelL_dup[v26];
                  v48 = g_nStatePanelT_dup[v26];
                  v69 = v47 + 15;
                  v70 = v48 + 85;
                  v71 = v47 + 37;
                  v72 = v48 + 108;
                }
                (*(void ( **)(_DWORD, int, int *, CCBUI *))(*(_DWORD *)*(v25 - 11) + 16))(
                  *(v25 - 11),
                  79,
                  &v69,
                  this);
                ((UIStatic *)*(v25 - 11))->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)*v25 + 16))(*v25, 79, &v69, this);
                ((UIStatic *)*v25)->CreateFromTemplate();
                v69 = 39;
                v71 = 61;
                v70 = 85;
                v72 = 108;
                if ( v26 < 4 )
                {
                  v49 = g_nStatePanelL_dup[v26];
                  v50 = g_nStatePanelT_dup[v26];
                  v69 = v49 + 39;
                  v70 = v50 + 85;
                  v71 = v49 + 61;
                  v72 = v50 + 108;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[11] + 16))(v25[11], 79, &v69, this);
                ((UIStatic *)v25[11])->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[22] + 16))(v25[22], 79, &v69, this);
                ((UIStatic *)v25[22])->CreateFromTemplate();
                v69 = 63;
                v71 = 85;
                v70 = 85;
                v72 = 108;
                if ( v26 < 4 )
                {
                  v51 = g_nStatePanelL_dup[v26];
                  v52 = g_nStatePanelT_dup[v26];
                  v69 = v51 + 63;
                  v70 = v52 + 85;
                  v71 = v51 + 85;
                  v72 = v52 + 108;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[55] + 16))(v25[55], 79, &v69, this);
                ((UIStatic *)v25[55])->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[66] + 16))(v25[66], 79, &v69, this);
                ((UIStatic *)v25[66])->CreateFromTemplate();
                v69 = 87;
                v71 = 109;
                v70 = 85;
                v72 = 108;
                if ( v26 < 4 )
                {
                  v53 = g_nStatePanelL_dup[v26];
                  v54 = g_nStatePanelT_dup[v26];
                  v69 = v53 + 87;
                  v70 = v54 + 85;
                  v71 = v53 + 109;
                  v72 = v54 + 108;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[33] + 16))(v25[33], 79, &v69, this);
                ((UIStatic *)v25[33])->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[44] + 16))(v25[44], 79, &v69, this);
                ((UIStatic *)v25[44])->CreateFromTemplate();
                v69 = 111;
                v71 = 127;
                v70 = 88;
                v72 = 104;
                if ( v26 < 4 )
                {
                  v55 = g_nStatePanelL_dup[v26];
                  v56 = g_nStatePanelT_dup[v26];
                  v69 = v55 + 111;
                  v70 = v56 + 88;
                  v71 = v55 + 127;
                  v72 = v56 + 104;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[77] + 16))(v25[77], 79, &v69, this);
                ((UIStatic *)v25[77])->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[88] + 16))(v25[88], 79, &v69, this);
                ((UIStatic *)v25[88])->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[99] + 16))(v25[99], 79, &v69, this);
                ((UIStatic *)v25[99])->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[110] + 16))(v25[110], 79, &v69, this);
                ((UIStatic *)v25[110])->CreateFromTemplate();
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[121] + 16))(v25[121], 79, &v69, this);
                ((UIStatic *)v25[121])->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))(*v40)->__vftable->Create)(*v40, 79, &v69, this);
                ((UIStatic *)*v40)->CreateFromTemplate();
                v69 = 111;
                v71 = 131;
                v70 = 88;
                v72 = 105;
                if ( v26 < 4 )
                {
                  v57 = g_nStatePanelL_dup[v26];
                  v58 = g_nStatePanelT_dup[v26];
                  v69 = v57 + 111;
                  v70 = v58 + 88;
                  v71 = v57 + 131;
                  v72 = v58 + 105;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[143] + 16))(v25[143], 79, &v69, this);
                ((UIStatic *)v25[143])->CreateFromTemplate();
                v69 = 111;
                v71 = 129;
                v70 = 88;
                v72 = 106;
                if ( v26 < 4 )
                {
                  v59 = g_nStatePanelL_dup[v26];
                  v69 = v59 + 111;
                  v60 = g_nStatePanelT_dup[v26];
                  v71 = v59 + 129;
                  v70 = v60 + 88;
                  v72 = v60 + 106;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[154] + 16))(v25[154], 79, &v69, this);
                ((UIStatic *)v25[154])->CreateFromTemplate();
                v69 = 111;
                v71 = 130;
                v70 = 88;
                v72 = 105;
                if ( v26 < 4 )
                {
                  v61 = g_nStatePanelL_dup[v26];
                  v69 = v61 + 111;
                  v62 = g_nStatePanelT_dup[v26];
                  v71 = v61 + 130;
                  v70 = v62 + 88;
                  v72 = v62 + 105;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[165] + 16))(v25[165], 79, &v69, this);
                ((UIStatic *)v25[165])->CreateFromTemplate();
                v69 = 111;
                v71 = 129;
                v70 = 88;
                v72 = 105;
                if ( v26 < 4 )
                {
                  v63 = g_nStatePanelL_dup[v26];
                  v69 = v63 + 111;
                  v64 = g_nStatePanelT_dup[v26];
                  v71 = v63 + 129;
                  v70 = v64 + 88;
                  v72 = v64 + 105;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[176] + 16))(v25[176], 79, &v69, this);
                ((UIStatic *)v25[176])->CreateFromTemplate();
                v69 = 131;
                v71 = 168;
                v70 = 88;
                v72 = 105;
                if ( v26 < 4 )
                {
                  v65 = g_nStatePanelL_dup[v26];
                  v69 = v65 + 131;
                  v66 = g_nStatePanelT_dup[v26];
                  v71 = v65 + 168;
                  v70 = v66 + 88;
                  v72 = v66 + 105;
                }
                (*(void ( **)(int, int, int *, CCBUI *))(*(_DWORD *)v25[187] + 16))(v25[187], 79, &v69, this);
                ((UIStatic *)v25[187])->CreateFromTemplate();
                ++v26;
                ++v25;
                if ( v26 >= 11 )
                  return 1;
              }
              return 0;
            }
          }
          return 0;
        }
      }
      return 0;
    }
  }
  return 0;
}

// 0x00517650
void CCBUI::_CCBUI()
{
  void *v2; // eax
  UIStatic *v3; // eax
  int *v4; // esi
  UIStatic **p_pPanel; // edi
  void *v6; // eax
  UIStatic *v7; // eax
  int v8; // [esp+0x10] [ebp-0x1C] BYREF
  int v9; // [esp+0x14] [ebp-0x18]
  int v10; // [esp+0x18] [ebp-0x14]
  int v11; // [esp+0x1C] [ebp-0x10]
  int v12; // [esp+0x28] [ebp-0x4]

  v2 = operator new(0x98u);
  v12 = 0;
  if ( v2 )
    sub_4422E0(v2);
  else
    v3 = 0;
  v12 = -1;
  this->m_pAttackSequenBack = v3;
  if ( v3 )
  {
    v8 = 483;
    v9 = 10;
    v10 = 803;
    v11 = 42;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v3->__vftable->Create)(v3, 1, &v8, this);
    ((UIStatic *)this->m_pAttackSequenBack)->CreateFromTemplate();
    v8 = 480;
    v10 = 544;
    v9 = 8;
    v11 = 72;
    v4 = &g_nSkillItemIDTable[5];
    p_pPanel = &this->pPanel;
    do
    {
      v6 = operator new(0x98u);
      v12 = 1;
      if ( v6 )
        sub_4422E0(v6);
      else
        v7 = 0;
      v12 = -1;
      *p_pPanel = v7;
      if ( !v7 )
        break;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v7->__vftable->Create)(v7, *v4, &v8, this);
      ((UIStatic *)*p_pPanel)->CreateFromTemplate();
      ++v4;
      ++p_pPanel;
    }
    while ( (int)v4 < (int)&g_nSkillItemIDTable[16] );
  }
}

// 0x005177B0
void CCBUI::Reset()
{
  UIStatic *v2; // eax
  UIProgressBar *v3; // eax
  UIStatic *v4; // eax
  UIProgressBar *v5; // eax
  UIStatic *v6; // eax
  UIProgressBar *v7; // eax
  UIProgressBar *v8; // ecx
  UIProgressBar *v9; // ecx
  int v10; // [esp+0x30] [ebp-0x820] BYREF
  int v11; // [esp+0x34] [ebp-0x81C]
  int v12; // [esp+0x38] [ebp-0x818]
  int v13; // [esp+0x3C] [ebp-0x814]
  UIStatic *v14; // [esp+0x40] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x44] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x444] [ebp-0x40C] BYREF
  int v17; // [esp+0x84C] [ebp-0x4]

  v2 = (UIStatic *)operator new(0x9Cu);
  v14 = v2;
  v17 = 0;
  if ( v2 )
    v3 = (UIProgressBar *)((UIStatic *)v2)->CtorWithFlag();
  else
    v3 = 0;
  this->m_pRoleStateGP[2] = v3;
  v4 = (UIStatic *)operator new(0x9Cu);
  v14 = v4;
  v17 = 1;
  if ( v4 )
    v5 = (UIProgressBar *)((UIStatic *)v4)->CtorWithFlag();
  else
    v5 = 0;
  this->m_pRoleStateGP[3] = v5;
  v6 = (UIStatic *)operator new(0x98u);
  v14 = v6;
  v17 = 2;
  if ( v6 )
    sub_4422E0(v6);
  else
    v7 = 0;
  v8 = this->m_pRoleStateGP[2];
  v17 = -1;
  this->m_pRoleStateMP[0] = v7;
  if ( !v8 || !this->m_pRoleStateGP[3] || !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 719),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v10 = 300;
  v11 = 30;
  v12 = 461;
  v13 = 87;
// [VFTABLE] ((void ( *)(UIProgressBar *, int, int *, CCBUI *))v8->__vftable->Create)(v8, 784, &v10, this);
  ((UIStatic *)this->m_pRoleStateGP[2])->CreateFromTemplate();
  ((UIScene *)this->m_pRoleStateGP[2])->SetShow(1);
  sub_446010(this->m_pRoleStateGP[2]);
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateGP[2]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateGP[2],
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIProgressBar *, int, int *, CCBUI *))this->m_pRoleStateGP[3]->__vftable->Create)(
// [VFTABLE]   this->m_pRoleStateGP[3],
// [VFTABLE]   784,
// [VFTABLE]   &v10,
// [VFTABLE]   this);
  ((UIStatic *)this->m_pRoleStateGP[3])->CreateFromTemplate();
  ((UIScene *)this->m_pRoleStateGP[3])->SetShow(1);
  sub_446010(this->m_pRoleStateGP[3]);
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateGP[3]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateGP[3],
// [VFTABLE]   0);
  v9 = this->m_pRoleStateMP[0];
  v10 = 100;
  v11 = 100;
  v12 = 356;
  v13 = 228;
// [VFTABLE] ((void ( *)(UIProgressBar *, int, int *, CCBUI *))v9->__vftable->Create)(v9, 1024, &v10, this);
  ((UIStatic *)this->m_pRoleStateMP[0])->CreateFromTemplate();
  ((UIScene *)this->m_pRoleStateMP[0])->SetShow(1);
  sub_446010(this->m_pRoleStateMP[0]);
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateMP[0]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateMP[0],
// [VFTABLE]   0);
  ((UIFrameWnd *)this->m_pRoleStateMP[0])->SetPosition(5,   63);
  ((UIFrameWnd *)this->m_pRoleStateMP[0])->SetFrameParam(190);
}

// 0x00517B30
bool CCBUI::CreateCombatPanel()
{
  UIStatic **p_m_pResultWaterLvup; // esi
  bool result; // al
  CCBUI *v4; // ecx
  int v5; // [esp+0x8] [ebp-0x10] BYREF
  int v6; // [esp+0xC] [ebp-0xC]
  int v7; // [esp+0x10] [ebp-0x8]
  int v8; // [esp+0x14] [ebp-0x4]

  p_m_pResultWaterLvup = &this->m_pResultWaterLvup;
  result = ((CCBAIWindow *)this)->Update((CCBUI **)&this->m_pResultWaterLvup);
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (CCBUI *)*p_m_pResultWaterLvup;
    v5 = 2;
    v7 = 251;
    v6 = 278;
    v8 = 484;
    ((CCBUI *)v4)->AddTask((tagUITask *)&v5, (int)this);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*p_m_pResultWaterLvup)->__vftable->ShowWindow)(*p_m_pResultWaterLvup, 0);
    return 1;
  }
  return result;
}

// 0x00517C10
bool CCBUI::CreateAttackSequen()
{
  UIStatic **p_m_pResultEarthLvup; // esi
  bool result; // al
  CCBItemWindow *v4; // ecx
  int pRect; // [esp+0x8] [ebp-0x10] BYREF
  int v6; // [esp+0xC] [ebp-0xC]
  int v7; // [esp+0x10] [ebp-0x8]
  int v8; // [esp+0x14] [ebp-0x4]

  p_m_pResultEarthLvup = &this->m_pResultEarthLvup;
  if ( result )
  {
    v6 = 0;
    v7 = 0;
    v4 = (CCBItemWindow *)*p_m_pResultEarthLvup;
    pRect = 14;
    v7 = 172;
    v6 = 316;
    v8 = 474;
    ((CCBItemWindow *)v4)->Create(&pRect, (int)this);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*p_m_pResultEarthLvup)->__vftable->ShowWindow)(*p_m_pResultEarthLvup, 0);
    return 1;
  }
  return result;
}

// 0x00517C80
bool CCBUI::CreateBattleFieldAttr()
{
  UIStatic **p_m_pResultDoubleLvup; // esi
  bool result; // al
  CCBParabolaWindow *v4; // ecx
  int v5; // [esp+0x0] [ebp-0x18]
  CCBParabolaWindow *v6; // [esp+0x8] [ebp-0x10] BYREF
  int v7; // [esp+0xC] [ebp-0xC]
  int v8; // [esp+0x10] [ebp-0x8]
  int v9; // [esp+0x14] [ebp-0x4]

  p_m_pResultDoubleLvup = &this->m_pResultDoubleLvup;
  ((CCBLineupWindow *)this)->_CCBLineupWindow((CCBItemWindow **)&this->m_pResultDoubleLvup);
  if ( result )
  {
    v7 = 0;
    v8 = 0;
    v4 = (CCBParabolaWindow *)*p_m_pResultDoubleLvup;
    v6 = (CCBParabolaWindow *)9;
    v8 = 239;
    v7 = 232;
    v9 = 482;
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*p_m_pResultDoubleLvup)->__vftable->ShowWindow)(
// [VFTABLE]   *p_m_pResultDoubleLvup,
// [VFTABLE]   0);
    return 1;
  }
  return result;
}

// 0x00517D60
bool CCBUI::CreateControlWindow()
{
  int v1; // esi
  CCBControlWindow **i; // edi
  CCBSkillWindow *v4; // ecx
  int v6; // [esp+0x0] [ebp-0x1C]
  int pRect; // [esp+0xC] [ebp-0x10] BYREF
  int v8; // [esp+0x10] [ebp-0xC]
  int v9; // [esp+0x14] [ebp-0x8]
  int v10; // [esp+0x18] [ebp-0x4]

  v1 = 0;
  v8 = 0;
  v9 = 0;
  pRect = 0;
  v10 = 0;
  for ( i = &this->m_pMain; ((CCBLineupWindow *)this)->Create((tagRECT *)i, v6); ++i )
  {
    v9 = v1 + 256;
    v4 = (CCBSkillWindow *)*i;
    pRect = v1;
    v8 = 0;
    v10 = 256;
    ((CCBSkillWindow *)v4)->Create(&pRect, (int)this);
// [VFTABLE] ((void ( *)(CCBControlWindow *, _DWORD))(*i)->__vftable->ShowWindow)(*i, 0);
    v1 += 200;
    if ( v1 >= 800 )
      return 1;
  }
  return 0;
}

// 0x00517DF0
BOOL CCBUI::CreateItemWindow()
{
  UIStatic **v2; // edi
  BOOL result; // eax
  UIStatic *v4; // ecx
  UIStatic **v5; // edi
  UIStatic *v6; // ecx
  UIStatic **v7; // edi
  UIStatic *v8; // ecx
  UIStatic **p_m_pRoleStateSword; // edi
  UIStatic *v10; // ecx
  UIStatic **p_m_pTrickName; // edi
  UIStatic *v12; // ecx
  UIStatic **p_m_pTrickName2; // edi
  UIStatic *v14; // ecx
  UIStatic **p_m_pDialogBack; // edi
  UIStatic *v16; // ecx
  UIStatic **p_m_pResultLevelup; // edi
  UIStatic *v18; // ecx
  int v19; // [esp+0x80] [ebp-0x10] BYREF
  int v20; // [esp+0x84] [ebp-0xC]
  int v21; // [esp+0x88] [ebp-0x8]
  int v22; // [esp+0x8C] [ebp-0x4]

  v20 = 0;
  v2 = (UIStatic **)&this->m_pRoleStateMP[1];
  v21 = 0;
  v19 = 0;
  v22 = 0;
  ((CCBAIWindow *)this)->Reset((int *)&this->m_pRoleStateMP[1]);
  if ( result )
  {
    v4 = *v2;
    v19 = 284;
    v21 = 516;
    v20 = 268;
    v22 = 332;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v4->__vftable->Create)(v4, 531, &v19, this);
    ((UIStatic *)*v2)->CreateFromTemplate();
    ((UIScene *)*v2)->SetShow(1);
    sub_446010(*v2);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v2)->__vftable->ShowWindow)(*v2, 0);
    v5 = (UIStatic **)&this->m_pRoleStateMP[2];
    ((CCBAIWindow *)this)->Reset((int *)&this->m_pRoleStateMP[2]);
    if ( result )
    {
      v6 = *v5;
      v19 = 249;
      v21 = 551;
      v20 = 263;
      v22 = 337;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v6->__vftable->Create)(v6, 533, &v19, this);
      ((UIStatic *)*v5)->CreateFromTemplate();
      ((UIScene *)*v5)->SetShow(1);
      sub_446010(*v5);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v5)->__vftable->ShowWindow)(*v5, 0);
      v7 = (UIStatic **)&this->m_pRoleStateMP[3];
      ((CCBAIWindow *)this)->Reset((int *)&this->m_pRoleStateMP[3]);
      if ( result )
      {
        v8 = *v7;
        v19 = 249;
        v21 = 551;
        v20 = 263;
        v22 = 337;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v8->__vftable->Create)(v8, 534, &v19, this);
        ((UIStatic *)*v7)->CreateFromTemplate();
        ((UIScene *)*v7)->SetShow(1);
        sub_446010(*v7);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v7)->__vftable->ShowWindow)(*v7, 0);
        p_m_pRoleStateSword = (UIStatic **)&this->m_pRoleStateSword;
        ((CCBAIWindow *)this)->Reset((int *)&this->m_pRoleStateSword);
        if ( result )
        {
          v10 = *p_m_pRoleStateSword;
          v19 = 249;
          v21 = 551;
          v20 = 263;
          v22 = 337;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v10->__vftable->Create)(v10, 535, &v19, this);
          ((UIStatic *)*p_m_pRoleStateSword)->CreateFromTemplate();
          ((UIScene *)*p_m_pRoleStateSword)->SetShow(1);
          sub_446010(*p_m_pRoleStateSword);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*p_m_pRoleStateSword)->__vftable->ShowWindow)(
// [VFTABLE]   *p_m_pRoleStateSword,
// [VFTABLE]   0);
          p_m_pTrickName = (UIStatic **)&this->m_pTrickName;
          ((CCBAIWindow *)this)->Reset((int *)&this->m_pTrickName);
          if ( result )
          {
            v12 = *p_m_pTrickName;
            v19 = 249;
            v21 = 551;
            v20 = 263;
            v22 = 337;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v12->__vftable->Create)(v12, 536, &v19, this);
            ((UIStatic *)*p_m_pTrickName)->CreateFromTemplate();
            ((UIScene *)*p_m_pTrickName)->SetShow(1);
            sub_446010(*p_m_pTrickName);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*p_m_pTrickName)->__vftable->ShowWindow)(*p_m_pTrickName, 0);
            p_m_pTrickName2 = (UIStatic **)&this->m_pTrickName2;
            ((CCBAIWindow *)this)->Reset((int *)&this->m_pTrickName2);
            if ( result )
            {
              v14 = *p_m_pTrickName2;
              v19 = 249;
              v21 = 551;
              v20 = 263;
              v22 = 337;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v14->__vftable->Create)(v14, 538, &v19, this);
              ((UIStatic *)*p_m_pTrickName2)->CreateFromTemplate();
              ((UIScene *)*p_m_pTrickName2)->SetShow(1);
              sub_446010(*p_m_pTrickName2);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*p_m_pTrickName2)->__vftable->ShowWindow)(*p_m_pTrickName2, 0);
              p_m_pDialogBack = &this->m_pDialogBack;
              ((CCBAIWindow *)this)->Reset((int *)&this->m_pDialogBack);
              if ( result )
              {
                v16 = *p_m_pDialogBack;
                v19 = 249;
                v21 = 551;
                v20 = 263;
                v22 = 337;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v16->__vftable->Create)(v16, 539, &v19, this);
                ((UIStatic *)*p_m_pDialogBack)->CreateFromTemplate();
                ((UIScene *)*p_m_pDialogBack)->SetShow(1);
                sub_446010(*p_m_pDialogBack);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*p_m_pDialogBack)->__vftable->ShowWindow)(
// [VFTABLE]   *p_m_pDialogBack,
// [VFTABLE]   0);
                p_m_pResultLevelup = &this->m_pResultLevelup;
                ((CCBAIWindow *)this)->Reset((int *)&this->m_pResultLevelup);
                if ( result )
                {
                  v18 = *p_m_pResultLevelup;
                  v19 = 221;
                  v21 = 579;
                  v20 = 255;
                  v22 = 345;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBUI *))v18->__vftable->Create)(v18, 532, &v19, this);
                  ((UIStatic *)*p_m_pResultLevelup)->CreateFromTemplate();
                  ((UIScene *)*p_m_pResultLevelup)->SetShow(1);
                  sub_446010(*p_m_pResultLevelup);
// [VFTABLE] result = ((int ( *)(UIStatic *, _DWORD))(*p_m_pResultLevelup)->__vftable->ShowWindow)(
// [VFTABLE]   *p_m_pResultLevelup,
// [VFTABLE]   0);
                  LOBYTE(result) = 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

// 0x005181E0
bool CCBUI::CreateParaWindow()
{
  UIStatic *v2; // ecx
  UIStatic *v3; // ecx
  UIProgressBar *v4; // ecx
  UIProgressBar *v5; // ecx
  UIProgressBar *v6; // ecx
  UIProgressBar *m_pRoleStateSword; // ecx
  UIStaticCB *m_pTrickName; // ecx
  UIStaticCB *m_pTrickName2; // ecx
  UIStatic *m_pDialogBack; // ecx
  UIStatic *m_pResultLevelup; // ecx
  UIListBox *v12; // ecx
  int v13; // edi
  CCBControlWindow **p_m_pMain; // ebx

// [VFTABLE] this->m_pAIWindow = (CCBAIWindow *)this->m_pSkillWindow->__vftable;
  v2 = this->m_pRoleStateImmunity[4];
  if ( v2 )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v2->__vftable->ShowWindow)(v2, 0);
  v3 = this->m_pRoleStateImmunity[5];
  if ( v3 )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v3->__vftable->ShowWindow)(v3, 0);
  v4 = this->m_pRoleStateMP[1];
  if ( v4 )
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v4->__vftable->ShowWindow)(v4, 0);
  v5 = this->m_pRoleStateMP[2];
  if ( v5 )
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v5->__vftable->ShowWindow)(v5, 0);
  v6 = this->m_pRoleStateMP[3];
  if ( v6 )
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v6->__vftable->ShowWindow)(v6, 0);
  m_pRoleStateSword = this->m_pRoleStateSword;
  if ( m_pRoleStateSword )
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))m_pRoleStateSword->__vftable->ShowWindow)(m_pRoleStateSword, 0);
  m_pTrickName = this->m_pTrickName;
  if ( m_pTrickName )
// [VFTABLE] ((void ( *)(UIStaticCB *, _DWORD))m_pTrickName->__vftable->ShowWindow)(m_pTrickName, 0);
  m_pTrickName2 = this->m_pTrickName2;
  if ( m_pTrickName2 )
// [VFTABLE] ((void ( *)(UIStaticCB *, _DWORD))m_pTrickName2->__vftable->ShowWindow)(m_pTrickName2, 0);
  m_pDialogBack = this->m_pDialogBack;
  if ( m_pDialogBack )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pDialogBack->__vftable->ShowWindow)(m_pDialogBack, 0);
  m_pResultLevelup = this->m_pResultLevelup;
  if ( m_pResultLevelup )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultLevelup->__vftable->ShowWindow)(m_pResultLevelup, 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_pResultThunderLvup->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pResultThunderLvup,
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_pResultWaterLvup->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pResultWaterLvup,
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_pResultFireLvup->__vftable->ShowWindow)(this->m_pResultFireLvup, 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_pResultEarthLvup->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pResultEarthLvup,
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_pResultDoubleLvup->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pResultDoubleLvup,
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))this->m_pResultGetItem->__vftable->ShowWindow)(this->m_pResultGetItem, 0);
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateMP[0]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateMP[0],
// [VFTABLE]   0);
  this->m_pRoleStateGP[2]->m_pbk = 0;
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateGP[2]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateGP[2],
// [VFTABLE]   0);
  this->m_pRoleStateGP[3]->m_pbk = 0;
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateGP[3]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateGP[3],
// [VFTABLE]   0);
  this->CreateResultWindow(0);
  v12 = (UIListBox *)this->m_pRoleStateGP[1];
  if ( v12 )
  {
    ((UIListBox *)v12)->GetCurSel();
    ((UIScrollBar *)this->m_pRoleStateGP[1])->SetRange(50.0);
    ((UIProgressBar *)this->m_pRoleStateGP[1])->FindChildByName(0.0);
  }
  v13 = 0;
  p_m_pMain = &this->m_pMain;
  do
  {
    *(&(*p_m_pMain)->m_CurCtrl + 15) = v13;
// [VFTABLE] ((void ( *)(CCBControlWindow *, _DWORD))(*p_m_pMain)->__vftable->ShowWindow)(*p_m_pMain, 0);
    ++v13;
    ++p_m_pMain;
  }
  while ( v13 < 4 );
  memset(&this->m_pLineupWindow, 0, 0x5A0u);
  this->fp.fp = 0;
  this->fp.fp_data[0] = 0;
  *((_DWORD *)&this->fp + 4) = 0;
  *((_DWORD *)&this->fp + 5) = -1;
  this->fp.fp_data[1] = 0;
  this->fp.fp_data[2] = -1;
  return 1;
}

// 0x005183C0
BOOL CCBUI::CreateMagicWindow()
{
  UIStatic *v2; // ecx
  UIStatic *v3; // ecx
  UIProgressBar *v4; // ecx
  UIStatic *m_pResultWindLvup; // ecx
  UIStatic *m_pResultThunderLvup; // ecx
  UIStatic *m_pResultWaterLvup; // ecx
  UIStatic *m_pResultFireLvup; // ecx
  UIStatic *m_pResultEarthLvup; // ecx
  UIStatic *m_pResultDoubleLvup; // ecx
  UIStatic *m_pResultGetItem; // ecx
  UIProgressBar *v12; // ecx
  UIProgressBar *v13; // ecx
  int v14; // edi
  CCBControlWindow **p_m_pMain; // esi
  BOOL result; // eax

  v2 = this->m_pRoleStateImmunity[4];
  if ( v2 )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v2->__vftable->ShowWindow)(v2, 0);
  v3 = this->m_pRoleStateImmunity[5];
  if ( v3 )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v3->__vftable->ShowWindow)(v3, 0);
  v4 = this->m_pRoleStateMP[0];
  if ( v4 )
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v4->__vftable->ShowWindow)(v4, 0);
  m_pResultWindLvup = this->m_pResultWindLvup;
  if ( m_pResultWindLvup )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultWindLvup->__vftable->ShowWindow)(m_pResultWindLvup, 0);
  m_pResultThunderLvup = this->m_pResultThunderLvup;
  if ( m_pResultThunderLvup )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultThunderLvup->__vftable->ShowWindow)(m_pResultThunderLvup, 0);
  m_pResultWaterLvup = this->m_pResultWaterLvup;
  if ( m_pResultWaterLvup )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultWaterLvup->__vftable->ShowWindow)(m_pResultWaterLvup, 0);
  m_pResultFireLvup = this->m_pResultFireLvup;
  if ( m_pResultFireLvup )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultFireLvup->__vftable->ShowWindow)(m_pResultFireLvup, 0);
  m_pResultEarthLvup = this->m_pResultEarthLvup;
  if ( m_pResultEarthLvup )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultEarthLvup->__vftable->ShowWindow)(m_pResultEarthLvup, 0);
  m_pResultDoubleLvup = this->m_pResultDoubleLvup;
  if ( m_pResultDoubleLvup )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultDoubleLvup->__vftable->ShowWindow)(m_pResultDoubleLvup, 0);
  m_pResultGetItem = this->m_pResultGetItem;
  if ( m_pResultGetItem )
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))m_pResultGetItem->__vftable->ShowWindow)(m_pResultGetItem, 0);
  v12 = this->m_pRoleStateGP[2];
  if ( v12 )
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v12->__vftable->ShowWindow)(v12, 0);
  v13 = this->m_pRoleStateGP[3];
  if ( v13 )
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))v13->__vftable->ShowWindow)(v13, 0);
  this->CreateResultWindow(0);
  v14 = 0;
  p_m_pMain = &this->m_pMain;
  do
  {
    result = (BOOL)*p_m_pMain;
    if ( *p_m_pMain )
    {
      *(_DWORD *)(result + 172) = v14;
// [VFTABLE] result = ((int ( *)(CCBControlWindow *, _DWORD))(*p_m_pMain)->__vftable->ShowWindow)(*p_m_pMain, 0);
    }
    ++v14;
    ++p_m_pMain;
  }
  while ( v14 < 4 );
  return result;
}

// 0x005184C0
bool CCBUI::CreateSkillWindow(char pData)
{
  UIStatic *m_pResultWindLvup; // ecx

  m_pResultWindLvup = this->m_pResultWindLvup;
  if ( pData )
// [VFTABLE] return ((bool ( *)(UIStatic *, int))m_pResultWindLvup->__vftable->ShowWindow)(m_pResultWindLvup, 1);
  else
// [VFTABLE] return ((bool ( *)(UIStatic *, _DWORD))m_pResultWindLvup->__vftable->ShowWindow)(m_pResultWindLvup, 0);
}

// 0x005184E0
int CCBUI::InitRoleDisplay(int a_128)
{
  int v3; // ebx
  CCBControlWindow **p_m_pMain; // esi
  CCBRoleState *left; // ebp
  NPC *v6; // ecx
  CCBRoleState *v7; // ebp
  char *v8; // eax
  CCBRoleState *v9; // ebp
  CCBRoleState *v10; // ebp
  CCBRoleState *v11; // ebp
  CCBRoleState *v12; // ebp
  CCBSkillWindow *m_pSkillWindow; // edx
  double nEXP; // st7
  CCBControlWindow *v15; // eax
  unsigned int v16; // eax
  int RoleExp; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int *v23; // eax
  CCBControlWindow *v24; // ebp
  int v25; // ecx
  int v26; // eax
  CCBSkillWindow *v27; // ecx
  unsigned int v28; // eax
  int result; // eax
  bool v30; // cc
  int nVal6; // [esp+0x4] [ebp-0x120]
  int nLevel; // [esp+0x8] [ebp-0x11C]
  char *fValue; // [esp+0xC] [ebp-0x118]
  float fValuea; // [esp+0xC] [ebp-0x118]
  float fValueb; // [esp+0xC] [ebp-0x118]
  float fValuec; // [esp+0xC] [ebp-0x118]
  float fValued; // [esp+0xC] [ebp-0x118]
  float fValuee; // [esp+0xC] [ebp-0x118]
  float fValuef; // [esp+0xC] [ebp-0x118]
  int v40; // [esp+0x20] [ebp-0x104]
  _BYTE *v41; // [esp+0x24] [ebp-0x100]
  unsigned int dwID; // [esp+0x28] [ebp-FCh]
  int v43; // [esp+0x2C] [ebp-F8h]
  CCBRoleState *v44; // [esp+0x30] [ebp-F4h]
  CCBControlWindow *v45; // [esp+0x34] [ebp-F0h] BYREF
  float v46; // [esp+0x38] [ebp-ECh]
  float v47; // [esp+0x3C] [ebp-E8h]
  float v48; // [esp+0x40] [ebp-E4h]
  int v49; // [esp+0x44] [ebp-E0h]
  int v50; // [esp+0x54] [ebp-D0h]
  int v51; // [esp+0x5C] [ebp-C8h]
  char Buffer[140]; // [esp+0x64] [ebp-C0h] BYREF
  int v53; // [esp+F0h] [ebp-0x34]
  UICaption *pData[8]; // [esp+F4h] [ebp-0x30] BYREF
  char a2[16]; // [esp+0x114] [ebp-0x10] BYREF

  v3 = 0;
  v43 = 0;
  v40 = 108;
  p_m_pMain = &this->m_pMain;
  left = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
  v44 = left;
  v41 = &left->m_Role[0].bMagicMastered[5][4];
  do
  {
    if ( !*v41 )
      goto LABEL_21;
    dwID = ((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->dwID;
    *(&(*p_m_pMain)->m_CurCtrl + 15) = v3;
    if ( ((CCBRoleState *)left)->GetRoleField(v3, 3) )
    {
// [VFTABLE] v6 = *(NPC **)((char *)&(*p_m_pMain)->__vftable + v40);
    }
    else if ( ((CCBRoleState *)left)->GetRoleField(v3, 4) )
    {
// [VFTABLE] v6 = *(NPC **)((char *)&(*p_m_pMain)->__vftable + v40);
    }
    else
    {
      if ( ((CCBRoleState *)left)->GetRoleField(v3, 2) )
        goto LABEL_12;
      if ( ((CCBRoleState *)left)->GetRoleField(v3, 1) )
      {
// [VFTABLE] v6 = *(NPC **)((char *)&(*p_m_pMain)->__vftable + v40);
      }
      else
      {
        if ( !((CCBRoleState *)left)->GetRoleField(v3, 5) )
        {
LABEL_12:
// [VFTABLE] v6 = *(NPC **)((char *)&(*p_m_pMain)->__vftable + v40);
          goto LABEL_13;
        }
// [VFTABLE] v6 = *(NPC **)((char *)&(*p_m_pMain)->__vftable + v40);
      }
    }
LABEL_13:
    ((NPC *)v6)->NPC::UpdateAnim();
    switch ( dwID )
    {
      case 'e':
        v7 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValue = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        nLevel = ((CCBRoleState *)v7)->InitUI(v3)->nLevel;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Jingtian");
        goto LABEL_19;
      case 'f':
        v12 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValue = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        nLevel = ((CCBRoleState *)v12)->InitUI(v3)->nLevel;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Changqing");
        goto LABEL_19;
      case 'h':
        v9 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValue = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        nLevel = ((CCBRoleState *)v9)->InitUI(v3)->nLevel;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Xuejian");
        goto LABEL_19;
      case 'i':
      case 'j':
        v10 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValue = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        nLevel = ((CCBRoleState *)v10)->InitUI(v3)->nLevel;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Longkui");
        goto LABEL_19;
      case 'k':
        v11 = (CCBRoleState *)this->m_pSkillWindow->m_rect.left;
        fValue = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName(aLevel);
        nLevel = ((CCBRoleState *)v11)->InitUI(v3)->nLevel;
        v8 = ((PalScript *)&g_PAL3_Instance.s_drvinfo.winname[52])->SetAppName("Zixuan");
LABEL_19:
        sprintf(Buffer, "%s %d %s", v8, nLevel, fValue);
        break;
      default:
        break;
    }
    ((UICaption *)(*p_m_pMain)->m_pButtonFlee)->SetEnable((int)Buffer, 1);
    ((UICaption *)(*p_m_pMain)->m_pButtonLineup)->SetEnable((int)Buffer, 0);
    ((UIListBox *)*((UIListBox **)&(*p_m_pMain)->m_CurCtrl + 11))->GetCurSel();
    fValuea = (float)((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->nFullHP;
    ((UIScrollBar *)*((UIScrollBar **)&(*p_m_pMain)->m_CurCtrl + 11))->SetRange(fValuea);
    fValueb = (float)((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->nHP;
    ((UIProgressBar *)*((UIProgressBar **)&(*p_m_pMain)->m_CurCtrl + 11))->FindChildByName(fValueb);
    ((UIListBox *)*((UIListBox **)&(*p_m_pMain)->m_CurCtrl + 12))->GetCurSel();
    fValuec = (float)(int)((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->pCCBSystem;
    ((UIScrollBar *)*((UIScrollBar **)&(*p_m_pMain)->m_CurCtrl + 12))->SetRange(fValuec);
    fValued = (float)((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->nGP;
    ((UIProgressBar *)*((UIProgressBar **)&(*p_m_pMain)->m_CurCtrl + 12))->FindChildByName(fValued);
    ((UIListBox *)*((UIListBox **)&(*p_m_pMain)->m_CurCtrl + 13))->GetCurSel();
    fValuee = (float)((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->nFullMP;
    ((UIScrollBar *)*((UIScrollBar **)&(*p_m_pMain)->m_CurCtrl + 13))->SetRange(fValuee);
    fValuef = (float)(int)((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->nMP;
    ((UIProgressBar *)*((UIProgressBar **)&(*p_m_pMain)->m_CurCtrl + 13))->FindChildByName(fValuef);
    m_pSkillWindow = this->m_pSkillWindow;
    pData[1] = 0;
    nEXP = (double)((CCBRoleState *)m_pSkillWindow->m_rect.left)->InitUI(v3)->nEXP;
    v15 = *p_m_pMain;
    *(float *)&pData[3] = nEXP;
    pData[0] = (UICaption *)v15->m_pButtonAI;
    ((UICaption *)pData[0])->SetEnable((int)Default, 0);
    v16 = ((CCBSystem *)this->m_pSkillWindow)->ProcProtect();
    this->IsResultWindowClosed(0 /* TODO: (int)CCBUI::ShowControlWindow */, 0, 0, 0, v16, 0, 0x40000000, pData);
    RoleExp = ((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->GetRoleExp(v3);
    sprintf(Buffer, &dir[20], RoleExp);
    ((UICaption *)(*p_m_pMain)->m_pButtonAttack)->SetEnable((int)Buffer, 0);
    v18 = ((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->GetRoleExp(v3);
    sprintf(Buffer, &dir[20], v18);
    ((UICaption *)(*p_m_pMain)->m_pButtonSkill)->SetEnable((int)Buffer, 0);
    v19 = ((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->GetRoleExp(v3);
    sprintf(Buffer, &dir[20], v19);
    ((UICaption *)(*p_m_pMain)->m_pButtonMagic)->SetEnable((int)Buffer, 0);
    v20 = ((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->GetRoleExp(v3);
    sprintf(Buffer, &dir[20], v20);
    ((UICaption *)(*p_m_pMain)->m_pButtonItem)->SetEnable((int)Buffer, 0);
    v21 = ((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->GetRoleExp(v3);
    sprintf(Buffer, &dir[20], v21);
    ((UICaption *)(*p_m_pMain)->m_pButtonDefence)->SetEnable((int)Buffer, 0);
    v22 = ((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->GetRoleExp(v3);
    sprintf(Buffer, &dir[20], v22);
    ((UICaption *)(*p_m_pMain)->m_pButtonLineup)->SetEnable((int)Buffer, 0);
    v23 = (int *)sub_445FE0(a2);
    v24 = *p_m_pMain;
    v50 = *v23;
    v25 = v23[1];
    v51 = v23[2];
    v26 = v23[3];
    v49 = 0;
    v46 = (float)v50;
    v45 = v24;
    v47 = -(double)(v26 - v25);
    v48 = v46;
    sub_445D20(v24, (__int64)v46, (__int64)v47);
// [VFTABLE] ((void ( *)(CCBControlWindow *, int))v45->__vftable->ShowWindow)(v45, 1);
    v27 = this->m_pSkillWindow;
    v53 = 0;
    *(float *)&nVal6 = (double)v43 * 0.079999998;
    v28 = ((CCBSystem *)v27)->ProcProtect();
    this->IsResultWindowClosed(0 /* TODO: (int)CCBUI::ShowBattleFieldAttr */, 0, 0, v53, v28, nVal6, 1161527296, &v45);
    left = v44;
    ++p_m_pMain;
    ++v43;
LABEL_21:
    result = v40 + 4;
    ++v3;
    v30 = v40 + 4 < 128;
    v40 += 4;
    v41 += 892;
  }
  while ( v30 );
  return result;
}

// 0x00518AF0
bool CCBUI::CreateLineupWindow(int nVal, char pData)
{
  UIStatic *m_pResultEarthLvup; // ecx

  this->m_pResultEarthLvup->m_ppicInfo = (_PlugInfo *)nVal;
  m_pResultEarthLvup = this->m_pResultEarthLvup;
  if ( pData )
// [VFTABLE] return ((bool ( *)(UIStatic *, int))m_pResultEarthLvup->__vftable->ShowWindow)(m_pResultEarthLvup, 1);
  else
// [VFTABLE] return ((bool ( *)(UIStatic *, _DWORD))m_pResultEarthLvup->__vftable->ShowWindow)(m_pResultEarthLvup, 0);
}

// 0x00518B20
bool CCBUI::CreateProtectWindow()
{
  return *((_BYTE *)&this->m_pMain->m_CurCtrl + 64);
}

// 0x00518B30
bool CCBUI::CreateResultWindow(char pData)
{
  int i; // edi
  bool result; // al
  int byUIIndex; // ebx
  UIStatic **v6; // edi
  int v7; // ebx
  UIStatic **v8; // edi
  int v9; // ebx
  UIStatic **v10; // esi
  int v11; // edi

  if ( pData )
  {
    for ( i = 0; i < 5; ++i )
    {
      result = *(_BYTE *)(this->m_pSkillWindow->m_rect.left + 892 * i + 577);
      if ( result )
      {
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pAttackSequenFace[i + 8]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pAttackSequenFace[i + 8],
// [VFTABLE]   1);
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pRoleStatePanel[i + 2]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStatePanel[i + 2],
// [VFTABLE]   1);
        byUIIndex = (unsigned __int8)((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(i)->byUIIndex;
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pRoleStateImmunity[byUIIndex + 6]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateImmunity[byUIIndex + 6],
// [VFTABLE]   1);
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pRoleStateImmunity[byUIIndex + 10]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateImmunity[byUIIndex + 10],
// [VFTABLE]   1);
// [VFTABLE] ((void ( *)(UIProgressBar *, int))this->m_pRoleStateHP[byUIIndex + 1]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateHP[byUIIndex + 1],
// [VFTABLE]   1);
// [VFTABLE] result = ((int ( *)(UIStatic *, int))this->m_pAttackSequenFace[byUIIndex + 4]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pAttackSequenFace[byUIIndex + 4],
// [VFTABLE]   1);
        if ( !i )
// [VFTABLE] result = ((int ( *)(UIProgressBar *, int))this->m_pRoleStateGP[1]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateGP[1],
// [VFTABLE]   1);
      }
    }
  }
  else
  {
// [VFTABLE] ((void ( *)(UIProgressBar *, _DWORD))this->m_pRoleStateGP[1]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pRoleStateGP[1],
// [VFTABLE]   0);
    v6 = &this->m_pRoleStateImmunity[10];
    v7 = 4;
    do
    {
// [VFTABLE] ((void ( *)(_DWORD, _DWORD))(*(v6 - 4))->__vftable->ShowWindow)(*(v6 - 4), 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v6)->__vftable->ShowWindow)(*v6, 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v6[4]->__vftable->ShowWindow)(v6[4], 0);
// [VFTABLE] ((void ( *)(_DWORD, _DWORD))(*(v6 - 229))->__vftable->ShowWindow)(*(v6 - 229), 0);
      ++v6;
      --v7;
    }
    while ( v7 );
    v8 = &this->m_pRoleStatePanel[2];
    v9 = 5;
    do
    {
// [VFTABLE] ((void ( *)(_DWORD, _DWORD))(*(v8 - 5))->__vftable->ShowWindow)(*(v8 - 5), 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v8)->__vftable->ShowWindow)(*v8, 0);
      ++v8;
      --v9;
    }
    while ( v9 );
    v10 = &this->m_pRoleStateAttackInc[4];
    v11 = 11;
    do
    {
// [VFTABLE] ((void ( *)(_DWORD, _DWORD))(*(v10 - 11))->__vftable->ShowWindow)(*(v10 - 11), 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v10)->__vftable->ShowWindow)(*v10, 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[11]->__vftable->ShowWindow)(v10[11], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[22]->__vftable->ShowWindow)(v10[22], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[55]->__vftable->ShowWindow)(v10[55], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[66]->__vftable->ShowWindow)(v10[66], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[33]->__vftable->ShowWindow)(v10[33], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[44]->__vftable->ShowWindow)(v10[44], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[77]->__vftable->ShowWindow)(v10[77], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[88]->__vftable->ShowWindow)(v10[88], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[99]->__vftable->ShowWindow)(v10[99], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[110]->__vftable->ShowWindow)(v10[110], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[121]->__vftable->ShowWindow)(v10[121], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[132]->__vftable->ShowWindow)(v10[132], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[143]->__vftable->ShowWindow)(v10[143], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[154]->__vftable->ShowWindow)(v10[154], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[165]->__vftable->ShowWindow)(v10[165], 0);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v10[176]->__vftable->ShowWindow)(v10[176], 0);
// [VFTABLE] result = ((int ( *)(UIStatic *, _DWORD))v10[187]->__vftable->ShowWindow)(v10[187], 0);
      ++v10;
      --v11;
    }
    while ( v11 );
  }
  return result;
}

// 0x00518D40
bool CCBUI::CreateFiveNimbus(char pData)
{
  int v3; // ebx
  int v4; // ebp
  int i; // esi

  if ( !pData )
// [VFTABLE] return ((bool ( *)(UIStatic *, _DWORD))this->m_pResultDoubleLvup->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pResultDoubleLvup,
// [VFTABLE]   0);
  v3 = 0;
  v4 = 0;
  for ( i = 96; i < 116; i += 4 )
  {
    if ( *(_BYTE *)(this->m_pSkillWindow->m_rect.left + v4 + 577) )
    {
// [VFTABLE] (***(void ( ****)(_DWORD, int))((char *)&this->m_pResultDoubleLvup->__vftable + i))(
// [VFTABLE]   *(vtbl_0056AE2C **)((char *)&this->m_pResultDoubleLvup->__vftable + i),
// [VFTABLE]   1);
      *(_DWORD *)((char *)this->m_pResultDoubleLvup + i - 24) = *(_DWORD *)&((CCBRoleState *)this->m_pSkillWindow->m_rect.left)->InitUI(v3)->byMagicUseTime[8][3];
      sub_445D20(
// [VFTABLE] *(_DWORD **)((char *)&this->m_pResultDoubleLvup->__vftable + i),
        g_nUnkTable_24C[*(_DWORD *)((char *)this->m_pResultDoubleLvup + i - 24)] + 9,
        g_nUnkTable_268[*(_DWORD *)((char *)this->m_pResultDoubleLvup + i - 24)] + 232);
    }
    else
    {
// [VFTABLE] (***(void ( ****)(_DWORD, _DWORD))((char *)&this->m_pResultDoubleLvup->__vftable + i))(
// [VFTABLE]   *(vtbl_0056AE2C **)((char *)&this->m_pResultDoubleLvup->__vftable + i),
// [VFTABLE]   0);
    }
    ++v3;
    v4 += 892;
  }
// [VFTABLE] return ((int ( *)(UIStatic *, int))this->m_pResultDoubleLvup->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pResultDoubleLvup,
// [VFTABLE]   1);
}

// 0x00518E60
void CCBUI::HideAll()
{
  NPC **v1; // esi
  int v2; // ebx

  v1 = (NPC **)&this->m_pRoleStateAttackInc[4];
  v2 = 4;
  do
  {
    ((NPC *)*(v1 - 11))->NPC::UpdateAnim();
    ((NPC *)*v1)->NPC::UpdateAnim();
    ((NPC *)v1[11])->NPC::UpdateAnim();
    ((NPC *)v1[22])->NPC::UpdateAnim();
    ((NPC *)v1[33])->NPC::UpdateAnim();
    ((NPC *)v1[44])->NPC::UpdateAnim();
    ((NPC *)v1[55])->NPC::UpdateAnim();
    ((NPC *)v1[66])->NPC::UpdateAnim();
    ((NPC *)v1[77])->NPC::UpdateAnim();
    ((NPC *)v1[88])->NPC::UpdateAnim();
    ((NPC *)v1[99])->NPC::UpdateAnim();
    ((NPC *)v1[110])->NPC::UpdateAnim();
    ((NPC *)v1[121])->NPC::UpdateAnim();
    ((NPC *)v1[132])->NPC::UpdateAnim();
    ((NPC *)v1[143])->NPC::UpdateAnim();
    ((NPC *)v1[154])->NPC::UpdateAnim();
    ((NPC *)v1[165])->NPC::UpdateAnim();
    ((NPC *)v1[176])->NPC::UpdateAnim();
    ((NPC *)v1[187])->NPC::UpdateAnim();
    ++v1;
    --v2;
  }
  while ( v2 );
}

// 0x00518FE0
void CCBUI::ShowBattleFieldAttr(int attr)
{
  CCBLineupWindow **v2; // esi
  CCBSkillWindow *m_pSkillWindow; // ecx
  double v4; // st6
  double v5; // st7
  double v6; // st7

  v2 = &this->m_pLineupWindow + 18 * *((_DWORD *)&this->fp + 5);
  if ( !BYTE1(this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 2]) )
  {
    this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 4] = (CCBResultWindow *)this->m_pSkillWindow->m_pSkillList[0];
    *((_BYTE *)v2 + 17) = 1;
  }
  m_pSkillWindow = this->m_pSkillWindow;
  v4 = *((float *)v2 + 7) + *((float *)v2 + 6);
  if ( *(float *)m_pSkillWindow->m_pSkillList > v4 )
  {
    v5 = *(float *)m_pSkillWindow->m_pSkillList - v4;
    v6 = v5 * (v5 * *((float *)v2 + 8)) * 0.5 + *((float *)v2 + 11);
    if ( v6 > *((float *)v2 + 13) )
    {
      v6 = *((float *)v2 + 13);
      *((_BYTE *)v2 + 18) = 1;
    }
    sub_445D20(v2[9], (__int64)*((float *)v2 + 10), (__int64)v6);
  }
}

// 0x00519080
void CCBUI::ShowControlWindow(int bShow)
{
  CCBLineupWindow **v2; // esi
  double v3; // st6
  float v4; // [esp+0x8] [ebp-0x8]
  float v5; // [esp+0xC] [ebp-0x4]

  v2 = &this->m_pLineupWindow + 18 * *((_DWORD *)&this->fp + 5);
  if ( !BYTE1(this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 2]) )
  {
    this->m_pResultWindow[18 * *((_DWORD *)&this->fp + 5) + 4] = (CCBResultWindow *)this->m_pSkillWindow->m_pSkillList[0];
    *((_BYTE *)v2 + 17) = 1;
  }
  v3 = *((float *)v2 + 7) + *((float *)v2 + 6);
  if ( *(float *)this->m_pSkillWindow->m_pSkillList > v3 )
  {
    v5 = (*(float *)this->m_pSkillWindow->m_pSkillList - v3) / *((float *)v2 + 8);
    v4 = (*((float *)v2 + 12) - *((float *)v2 + 10)) * v5 + *((float *)v2 + 10);
    sprintf(byte_17ACB08, &dir[20], (int)v4);
    ((UICaption *)v2[9])->SetEnable((int)byte_17ACB08, 1);
    if ( v5 >= 1.0 )
    {
      sprintf(byte_17ACB08, &dir[20], (int)*((float *)v2 + 12));
      ((UICaption *)v2[9])->SetEnable((int)byte_17ACB08, 1);
      *((_BYTE *)v2 + 18) = 1;
    }
  }
}

// 0x00519200
void CCBUI::ShowDialogWindow()
{
  int v2; // esi
  _BYTE *v3; // edi

  v2 = 0;
  v3 = (char *)&this->m_pResultWindow[2] + 2;
  do
  {
    if ( *(v3 - 2) == 1 && *v3 == 1 )
      this->ShowAIWindow(v2);
    ++v2;
    v3 += 72;
  }
  while ( v2 < 20 );
}

// 0x00519230
void CCBUI::ShowAIWindow(int nRoleIndex)
{
  LOBYTE(this->m_pResultWindow[18 * nRoleIndex + 2]) = 0;
  --*((_DWORD *)&this->fp + 4);
}

// 0x00519260
bool CCBUI::IsResultWindowClosed(
        
        int nVal,
        int nVal2,
        int nVal3,
        int nVal4,
        int nVal5,
        int nVal6,
        int nVal7,
        const void *pData)
{
  int v10; // eax
  CCBResultWindow **i; // ecx
  void **v13; // eax

  if ( *((int *)&this->fp + 4) >= 19 )
    return 0;
  v10 = 0;
  for ( i = &this->m_pResultWindow[2]; *(_BYTE *)i; i += 18 )
  {
    if ( ++v10 >= 20 )
      return 0;
  }
// [VFTABLE] v13 = &this->__vftable + 18 * v10;
  *((_BYTE *)v13 + 1184) = 1;
  *((_BYTE *)v13 + 1185) = 0;
  *((_BYTE *)v13 + 1186) = 0;
  v13[299] = (void *)nVal6;
  v13[300] = (void *)nVal7;
  v13[297] = (void *)nVal5;
  qmemcpy(v13 + 301, pData, 0x20u);
  v13 += 292;
  *v13 = (void *)nVal;
  v13[1] = (void *)nVal2;
  v13[2] = (void *)nVal3;
  v13[3] = (void *)nVal4;
  ++*((_DWORD *)&this->fp + 4);
  return 1;
}

// 0x00519310
int * CCBUI::ctor()
{

  return (int *)this;
}

// 0x00519380
void CCBUI::Release()
{

  ((UIListBox *)this)->_UIListBox();
}

// 0x005193D0
void CCBUI::ClearAttackSequence()
{
  this->m_pAttackSequenBack = 0;
  this->pPanel = 0;
  this->m_pBattleFieldAttr[0] = 0;
  this->m_pBattleFieldAttr[1] = 0;
  this->m_pBattleFieldAttr[2] = 0;
  this->m_pBattleFieldAttr[3] = 0;
  this->m_pBattleFieldAttr[4] = 0;
  this->m_pBattleFieldAttr[5] = 0;
  this->m_pAttackSequenFace[0] = 0;
  this->m_pAttackSequenFace[1] = 0;
  this->m_pAttackSequenFace[2] = 0;
}

// 0x00519400
void CCBUI::CreateImbibeNimbus(int nCount)
{
  void *v3; // eax
  UIStatic *v4; // eax
  char pExceptionObject[1024]; // [esp+0xC] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x40C] [ebp-0x40C] BYREF
  int v7; // [esp+0x814] [ebp-0x4]
  int parent; // [esp+0x820] [ebp+0x8]

  ((PalScript *)this)->Create(1879048193, (tagRECT *)nCount, parent);
  v3 = operator new(0x98u);
  v7 = 0;
  if ( v3 )
    sub_4422E0(v3);
  else
    v4 = 0;
  v7 = -1;
  this->m_pAttackSequenBack = v4;
  if ( !v4 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 2090),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  *(_DWORD *)nCount = 0;
  *(_DWORD *)(nCount + 8) = 256;
  *(_DWORD *)(nCount + 4) = 0;
  *(_DWORD *)(nCount + 12) = 256;
// [VFTABLE] ((void ( *)(UIStatic *, int, int, CCBUI *))this->m_pAttackSequenBack->__vftable->Create)(
// [VFTABLE]   this->m_pAttackSequenBack,
// [VFTABLE]   256,
// [VFTABLE]   nCount,
// [VFTABLE]   this);
  ((UIStatic *)this->m_pAttackSequenBack)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pAttackSequenBack->__vftable->ShowWindow)(this->m_pAttackSequenBack, 1);

}

// 0x00519510
void CCBUI::Destroy()
{
  UIStatic *m_pAttackSequenBack; // ecx
  UIStatic *pPanel; // ecx
  UIStatic *v4; // ecx
  UIStatic *v5; // ecx
  UIStatic *v6; // ecx
  UIStatic *v7; // ecx
  UIStatic *v8; // ecx
  UIStatic *v9; // ecx
  UIStatic *v10; // ecx
  UIStatic *v11; // ecx
  UIStatic *v12; // ecx
  UIListBox *v13; // [esp+0x0] [ebp-0x8]
  int v14; // [esp+0x4] [ebp-0x4]

  ((CCBRoleState *)this)->Destroy(v13, v14);
  m_pAttackSequenBack = this->m_pAttackSequenBack;
  if ( m_pAttackSequenBack )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pAttackSequenBack->__vftable->sub_4431B0)(m_pAttackSequenBack, 1);
    this->m_pAttackSequenBack = 0;
  }
  pPanel = this->pPanel;
  if ( pPanel )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))pPanel->__vftable->sub_4431B0)(pPanel, 1);
    this->pPanel = 0;
  }
  v4 = this->m_pBattleFieldAttr[0];
  if ( v4 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v4->__vftable->sub_4431B0)(v4, 1);
    this->m_pBattleFieldAttr[0] = 0;
  }
  v5 = this->m_pBattleFieldAttr[1];
  if ( v5 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v5->__vftable->sub_4431B0)(v5, 1);
    this->m_pBattleFieldAttr[1] = 0;
  }
  v6 = this->m_pBattleFieldAttr[2];
  if ( v6 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v6->__vftable->sub_4431B0)(v6, 1);
    this->m_pBattleFieldAttr[2] = 0;
  }
  v7 = this->m_pBattleFieldAttr[3];
  if ( v7 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v7->__vftable->sub_4431B0)(v7, 1);
    this->m_pBattleFieldAttr[3] = 0;
  }
  v8 = this->m_pBattleFieldAttr[4];
  if ( v8 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v8->__vftable->sub_4431B0)(v8, 1);
    this->m_pBattleFieldAttr[4] = 0;
  }
  v9 = this->m_pBattleFieldAttr[5];
  if ( v9 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v9->__vftable->sub_4431B0)(v9, 1);
    this->m_pBattleFieldAttr[5] = 0;
  }
  v10 = this->m_pAttackSequenFace[0];
  if ( v10 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v10->__vftable->sub_4431B0)(v10, 1);
    this->m_pAttackSequenFace[0] = 0;
  }
  v11 = this->m_pAttackSequenFace[1];
  if ( v11 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v11->__vftable->sub_4431B0)(v11, 1);
    this->m_pAttackSequenFace[1] = 0;
  }
  v12 = this->m_pAttackSequenFace[2];
  if ( v12 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v12->__vftable->sub_4431B0)(v12, 1);
    this->m_pAttackSequenFace[2] = 0;
  }
}

// 0x005195E0
int CCBUI::OnMessage(int pt, unsigned int area, int nVal)
{
  CScreenMode *Instance; // eax

  if ( pt == 1001 )
  {
    if ( area >= 0x103 && area <= 0x10C )
    {
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition("wa001", 1);
    }
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(area, nVal);
  }
  else if ( pt == 1007 && nVal != -1 )
  {
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(area, nVal);
  }
  return ((PalScript *)this)->OnMessage(pt, area, nVal);
}

// 0x005196C0
void CCBUI::SetNimbusToNimbusControl()
{
  UIStatic **v2; // edi

  v2 = &this->m_pAttackSequenFace[2];

// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*v2)->__vftable->ShowWindow)(*v2, 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->pPanel->__vftable->ShowWindow)(this->pPanel, 1);
  ((PalScript *)this->pPanel)->OpenScript("ui\\combat\\control\\attack3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[0]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[0],
// [VFTABLE]   1);
  ((PalScript *)this->m_pBattleFieldAttr[0])->OpenScript("ui\\combat\\control\\skill3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[1]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[1],
// [VFTABLE]   1);
  ((PalScript *)this->m_pBattleFieldAttr[1])->OpenScript("ui\\combat\\control\\magic3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[2]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[2],
// [VFTABLE]   1);
  ((PalScript *)this->m_pBattleFieldAttr[2])->OpenScript("ui\\combat\\control\\item3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[4]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[4],
// [VFTABLE]   1);
  ((PalScript *)this->m_pBattleFieldAttr[4])->OpenScript("ui\\combat\\control\\lineup3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[5]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[5],
// [VFTABLE]   1);
  ((PalScript *)this->m_pBattleFieldAttr[5])->OpenScript("ui\\combat\\control\\ai3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pAttackSequenFace[0]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pAttackSequenFace[0],
// [VFTABLE]   1);
  ((PalScript *)this->m_pAttackSequenFace[0])->OpenScript("ui\\combat\\control\\flee3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pAttackSequenFace[1]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pAttackSequenFace[1],
// [VFTABLE]   1);
  ((PalScript *)this->m_pAttackSequenFace[1])->OpenScript("ui\\combat\\control\\protect3.tga", 0);

// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[3]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[3],
// [VFTABLE]   1);
  ((PalScript *)this->m_pBattleFieldAttr[3])->OpenScript("ui\\combat\\control\\defence3.tga", 0);
}

// 0x00519A10
void CCBUI::WriteNimbusToPlayerMgr()
{
  NameSys *Sys; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v5; // [esp+0x810] [ebp-0x4]
  NameSys **v6; // [esp+0x818] [ebp+0x4]
  int v7; // [esp+0x81C] [ebp+0x8]
  int v8; // [esp+0x820] [ebp+0xC]
  int v9; // [esp+0x824] [ebp+0x10]

  v5 = 0;
  if ( operator new(0x158u) )
    Sys = UIScene::GetSys();
  else
    Sys = 0;
  v5 = -1;
  *v6 = Sys;
  if ( !Sys )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 2306),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  (*(void ( **)(NameSys *, int, int, CCBUI *, int, int, _DWORD))(*(_DWORD *)Sys->m_Flag + 28))(
    Sys,
    v7,
    v8,
    this,
    v9,
    1,
    0);
}

// 0x00519B40
CCBUI * CCBUI::GetNimbusColor(int nNimbusType)
{
  ((CCBFiveNimbusWindow *)this)->_CCBFiveNimbusWindow();
  if ( (nNimbusType & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00519BB0
void CCBUI::Render()
{
  this->m_pBattleFieldAttr[0] = 0;
  this->m_pBattleFieldAttr[1] = 0;
  this->m_pBattleFieldAttr[2] = 0;
  this->m_pAttackSequenBack = 0;
  this->pPanel = 0;
  this->m_pBattleFieldAttr[3] = 0;
  this->m_pBattleFieldAttr[4] = 0;
  this->m_pBattleFieldAttr[5] = 0;
}

// 0x00519BD0
char CCBUI::CreateButton(
        CCBUI *this@<ecx>,
        int a2@<ebx>,
        int a3@<ebp>,
        int a4@<edi>,
        int a5@<esi>,
        tagRECT *pRect,
        int parent)
{
// [IDA_MISID]   _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v8; // esp
  void *v10; // eax
  UIStatic *v11; // eax
  int *v12; // ebx
  UIListBox **m_pBattleFieldAttr; // esi
  UIListBox *v14; // eax
  UIListBox *updated; // eax
  void *v16; // eax
  UIStatic *v17; // eax
  _BYTE pExceptionObject[1040]; // [esp+0x40] [ebp-0x100C] BYREF
  char v21; // [esp+0x450] [ebp-BFCh] BYREF
  char v22[1024]; // [esp+0x850] [ebp-0x7FC] BYREF
  char v23; // [esp+C50h] [ebp-0x3FC] BYREF
  _EXCEPTION_REGISTRATION_RECORD *v24; // [esp+0x1040] [ebp-0xC]
  void *v25; // [esp+0x1044] [ebp-0x8]
  int v26; // [esp+0x1048] [ebp-0x4]

  v26 = -1;
// [IDA_MISID]   ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v25 = ((void*)0);
// [IDA_MISID]   v24 = ExceptionList;
  v8 = alloca(4120);
  ((PalScript *)this)->Create(1879048193, pRect, parent);
  v10 = operator new(0x98u);
  v26 = 0;
  if ( v10 )
    sub_4422E0(v10);
  else
    v11 = 0;
  v26 = -1;
  this->m_pAttackSequenBack = v11;
  if ( !v11 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&pExceptionObject[1024])->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 2366),
      0x400u);
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  pRect->left = 0;
  pRect->right = 249;
  pRect->top = 0;
  pRect->bottom = 206;
// [VFTABLE] ((void (*)(UIStatic *, int, tagRECT *, CCBUI *, int, int, int, int))this->m_pAttackSequenBack->__vftable->Create)(
// [VFTABLE]   this->m_pAttackSequenBack,
// [VFTABLE]   131,
// [VFTABLE]   pRect,
// [VFTABLE]   this,
// [VFTABLE]   a4,
// [VFTABLE]   a5,
// [VFTABLE]   a3,
// [VFTABLE]   a2);
  ((UIStatic *)this->m_pAttackSequenBack)->CreateFromTemplate();
  ((UIScene *)this->m_pAttackSequenBack)->SetShow(0);
  sub_446010(this->m_pAttackSequenBack);
  ((UIFrameWnd *)this->m_pAttackSequenBack)->SetPosition(40,   150);
  ((UIFrameWnd *)this->m_pAttackSequenBack)->SetPosition(0,   0);
// [VFTABLE] ((void (*)(UIStatic *, int))this->m_pAttackSequenBack->__vftable->ShowWindow)(this->m_pAttackSequenBack, 1);
  v12 = &g_nSkillItemIDTable[15];
  m_pBattleFieldAttr = (UIListBox **)this->m_pBattleFieldAttr;
  do
  {
    v14 = (UIListBox *)operator new(0x4B8u);
    if ( v14 )
      updated = ((UIListBox *)v14)->UpdateKeyCtrl();
    else
      updated = 0;
    *m_pBattleFieldAttr = updated;
    if ( !updated )
    {
      qmemcpy(
        &pExceptionObject[16],
        ((Logger *)&v21)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 2390),
        0x400u);
      _CxxThrowException(&pExceptionObject[16], (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    pRect->left = 39;
    pRect->right = 241;
    pRect->top = 78;
    pRect->bottom = 175;
// [VFTABLE] ((void (*)(UIListBox *, int, tagRECT *, CCBUI *, _DWORD, int, _DWORD))(*m_pBattleFieldAttr)->__vftable[1].ShowWindow)(
// [VFTABLE]   *m_pBattleFieldAttr,
// [VFTABLE]   *v12,
// [VFTABLE]   pRect,
// [VFTABLE]   this,
// [VFTABLE]   0,
// [VFTABLE]   1,
// [VFTABLE]   0);
// [VFTABLE] ((void (*)(UIListBox *, int))(*m_pBattleFieldAttr)->__vftable->ShowWindow)(*m_pBattleFieldAttr, 1);
    ((UIListBox *)*m_pBattleFieldAttr)->SetItemOffset(2, -4);
    ((UIListBox *)*m_pBattleFieldAttr)->SetFirstShow((int)"Name", 150);
    ((UIListBox *)*m_pBattleFieldAttr)->SetFirstShow((int)unk_5DFDB4, 43);
    ((UIListBox *)*m_pBattleFieldAttr)->SetLockSel();
    ((UIListBox *)*m_pBattleFieldAttr)->GetSel(g_nUnkDataTable[5], 0);
    ((UIListBox *)*m_pBattleFieldAttr)->SetItemData(1);
    *pRect = *(tagRECT *)sub_445FE0(pExceptionObject);
    ((UIListBox *)*m_pBattleFieldAttr)->GetLockSel((int)&g_EffMgr.m_sz5D8C3C[1812], &pRect->left, 16, 16, 0);
    ((CCBUI *)&(*m_pBattleFieldAttr)->m_scrollbar)->SetSelection(26);
    ((CCBUI *)&(*m_pBattleFieldAttr)->m_scrollbar)->SetCurPlayer(-5);
    ((CCBUI *)&(*m_pBattleFieldAttr)->m_scrollbar)->SetRoleStatePointers(-2);
    ++v12;
    ++m_pBattleFieldAttr;
  }
  while ( (int)v12 < (int)&g_nSkillItemIDTable[18] );

  v16 = operator new(0x98u);
  if ( v16 )
    sub_4422E0(v16);
  else
    v17 = 0;
  this->pPanel = v17;
  if ( !v17 )
  {
    qmemcpy(v22, ((Logger *)&v23)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 4346), sizeof(v22));
    _CxxThrowException(v22, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  pRect->left = 37;
  pRect->right = 237;
  pRect->top = 170;
  pRect->bottom = 210;
// [VFTABLE] ((void (*)(UIStatic *, int, tagRECT *, CCBUI *))this->pPanel->__vftable->Create)(
// [VFTABLE]   this->pPanel,
// [VFTABLE]   131,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] ((void (*)(UIStatic *, int))this->pPanel->__vftable->ShowWindow)(this->pPanel, 1);
  this->GravityDown(0);
  return 1;
}

// 0x00519F50
void CCBUI::Destroy_9f50()
{
  UIStatic **m_pBattleFieldAttr; // esi
  int v3; // ebx
  UIStatic *m_pAttackSequenBack; // ecx
  UIStatic *pPanel; // ecx
  UIStatic *v6; // ecx
  UIStatic *v7; // ecx
  UIStatic *v8; // ecx
  UIListBox *v9; // [esp+0x0] [ebp-0x10]
  int v10; // [esp+0x4] [ebp-0xC]

  ((CCBRoleState *)this)->Destroy(v9, v10);
  m_pBattleFieldAttr = this->m_pBattleFieldAttr;
  v3 = 3;
  do
  {
    if ( *m_pBattleFieldAttr )
    {
// [VFTABLE] ((void ( *)(UIStatic *, int))(*m_pBattleFieldAttr)->__vftable->sub_4431B0)(*m_pBattleFieldAttr, 1);
      *m_pBattleFieldAttr = 0;
    }
    ++m_pBattleFieldAttr;
    --v3;
  }
  while ( v3 );
  m_pAttackSequenBack = this->m_pAttackSequenBack;
  if ( m_pAttackSequenBack )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))m_pAttackSequenBack->__vftable->sub_4431B0)(m_pAttackSequenBack, 1);
    this->m_pAttackSequenBack = 0;
  }
  pPanel = this->pPanel;
  if ( pPanel )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))pPanel->__vftable->sub_4431B0)(pPanel, 1);
    this->pPanel = 0;
  }
  v6 = this->m_pBattleFieldAttr[3];
  if ( v6 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v6->__vftable->sub_4431B0)(v6, 1);
    this->m_pBattleFieldAttr[3] = 0;
  }
  v7 = this->m_pBattleFieldAttr[4];
  if ( v7 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v7->__vftable->sub_4431B0)(v7, 1);
    this->m_pBattleFieldAttr[4] = 0;
  }
  v8 = this->m_pBattleFieldAttr[5];
  if ( v8 )
  {
// [VFTABLE] ((void ( *)(UIStatic *, int))v8->__vftable->sub_4431B0)(v8, 1);
    this->m_pBattleFieldAttr[5] = 0;
  }
}

// 0x0051A090
BOOL CCBUI::AddResultWindowAni(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(g_nSkillItemIDTable[15], -1);
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x0051A0F0
void CCBUI::ChangeSpecStateLum()
{
  UIStatic **v2; // edi

  v2 = &this->m_pBattleFieldAttr[3];
  this->LineMove((POINT *)&this->m_pBattleFieldAttr[3], (POINT *)0xB5);
// [VFTABLE] ((void ( *)(UIStatic *, int))(*v2)->__vftable->ShowWindow)(*v2, 1);
  this->LineMove((POINT *)&this->m_pBattleFieldAttr[4], (POINT *)0xB6);
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[4]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[4],
// [VFTABLE]   1);
  this->LineMove((POINT *)&this->m_pBattleFieldAttr[5], (POINT *)0xB7);
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pBattleFieldAttr[5]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[5],
// [VFTABLE]   1);
}

// 0x0051A1D0
BOOL CCBUI::LineMove(POINT *pStart, POINT *pEnd)
{
  UIStatic *v4; // eax
  LONG v5; // eax
  BOOL result; // eax
  char pExceptionObject[1024]; // [esp+0x8] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x408] [ebp-0x40C] BYREF
  int v9; // [esp+0x810] [ebp-0x4]
  int v10; // [esp+0x820] [ebp+0xC]
  int v11; // [esp+0x824] [ebp+0x10]

  v4 = (UIStatic *)operator new(0xF8u);
  v9 = 0;
  if ( v4 )
  {
  }
  else
    v5 = 0;
  v9 = -1;
  pStart->x = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], g_EffMgr.m_sz5D8C3C[1780], 2575),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  result = (*(int ( **)(LONG, POINT *, int, CCBUI *, int, _DWORD))(*(_DWORD *)v5 + 28))(
             v5,
             g_SceneMgr.m_pAddEffect2,
             v10,
             this,
             v11,
             0);
  LOBYTE(result) = 1;
  return result;
}

// 0x0051A2B0
unsigned int CCBUI::GravityDown(unsigned int formal)
{
  int v3; // ebp
  UIStatic **m_pBattleFieldAttr; // edi
  UIStatic *v5; // eax
  UIStatic *v6; // eax
  UIStatic *v7; // eax
  UIStatic *v8; // eax
  unsigned int result; // eax

  v3 = 3;
  m_pBattleFieldAttr = this->m_pBattleFieldAttr;
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))(*m_pBattleFieldAttr)->__vftable->ShowWindow)(*m_pBattleFieldAttr, 0);
    v5 = this->m_pBattleFieldAttr[3];
    ++m_pBattleFieldAttr;
    --v3;
    v5->m_ratioh = 0.0;
    LOBYTE(v5->pDebugTex) = 0;
    v6 = this->m_pBattleFieldAttr[4];
    v6->m_ratioh = 0.0;
    LOBYTE(v6->pDebugTex) = 0;
    v7 = this->m_pBattleFieldAttr[5];
    v7->m_ratioh = 0.0;
    LOBYTE(v7->pDebugTex) = 0;
  }
  while ( v3 );
  switch ( formal )
  {
    case 0u:
      v8 = this->m_pBattleFieldAttr[3];
      goto LABEL_9;
    case 1u:
      v8 = this->m_pBattleFieldAttr[4];
      goto LABEL_9;
    case 2u:
      v8 = this->m_pBattleFieldAttr[5];
LABEL_9:
      LODWORD(v8->m_ratioh) = 1;
      LOBYTE(v8->pDebugTex) = 1;
      break;
  }
  ((UICaption *)this->m_pAttackSequenBack)->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)this->pPanel)->SetEnable((int)g_szSceneUIText, 0);
// [VFTABLE] result = ((int ( *)(UIStatic *, int))this->m_pBattleFieldAttr[formal]->__vftable->ShowWindow)(
// [VFTABLE]   this->m_pBattleFieldAttr[formal],
// [VFTABLE]   1);
  this->m_pAttackSequenFace[0] = (UIStatic *)formal;
  return result;
}

// 0x0051A340
unsigned int CCBUI::ChangeNumTxt()
{
  sub_51A400(this);
  return (unsigned int)this;
}

// 0x0051A390
void CCBUI::DoTask()
{
  char v2; // [esp+0x8] [ebp+0x4]

  ((CCBItemWindow *)this)->_CCBItemWindow();
  if ( (v2 & 1) != 0 )
    operator delete(this);
}

// 0x0051A430
BOOL CCBUI::AddTask(tagUITask *pTask, int nParam)
{
  void *v4; // eax
  UIStatic *v5; // eax
  int *v6; // ebp
  UIListBox **p_pPanel; // esi
  UIListBox *v8; // eax
  UIListBox *updated; // eax
  char **v10; // eax
  BOOL result; // eax
  char a2[16]; // [esp+0x2C] [ebp-0x81C] BYREF
  char pExceptionObject[1024]; // [esp+0x3C] [ebp-0x80C] BYREF
  char ArgList[1024]; // [esp+0x43C] [ebp-0x40C] BYREF
  int v15; // [esp+0x844] [ebp-0x4]

  ((PalScript *)this)->Create(1879048194, (tagRECT *)pTask, nParam);
  v4 = operator new(0x98u);
  v15 = 0;
  if ( v4 )
    sub_4422E0(v4);
  else
    v5 = 0;
  v15 = -1;
  this->m_pAttackSequenBack = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)ArgList)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 2678),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  pTask->fp[0] = 0;
  pTask->fp[2] = (char *)249;
  pTask->fp[1] = 0;
  pTask->fp[3] = (char *)206;
// [VFTABLE] ((void ( *)(UIStatic *, int, tagUITask *, CCBUI *))this->m_pAttackSequenBack->__vftable->Create)(
// [VFTABLE]   this->m_pAttackSequenBack,
// [VFTABLE]   150,
// [VFTABLE]   pTask,
// [VFTABLE]   this);
  ((UIStatic *)this->m_pAttackSequenBack)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))this->m_pAttackSequenBack->__vftable->ShowWindow)(this->m_pAttackSequenBack, 1);
  ((UIScene *)this->m_pAttackSequenBack)->SetShow(0);
  sub_446010(this->m_pAttackSequenBack);
  ((UIFrameWnd *)this->m_pAttackSequenBack)->SetPosition(40,   170);
  v6 = &g_nSkillItemIDTable[18];
  p_pPanel = (UIListBox **)&this->pPanel;
  do
  {
    v8 = (UIListBox *)operator new(0x4B8u);
    v15 = 1;
    if ( v8 )
      updated = ((UIListBox *)v8)->UpdateKeyCtrl();
    else
      updated = 0;
    v15 = -1;
    *p_pPanel = updated;
    if ( !updated )
    {
      qmemcpy(
        pExceptionObject,
        ((Logger *)ArgList)->FormatException("C++ new failed!", g_EffMgr.m_sz5D8C3C[1780], 2700),
        sizeof(pExceptionObject));
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
    }
    pTask->fp[0] = (char *)39;
    pTask->fp[2] = (char *)241;
    pTask->fp[1] = (char *)78;
    pTask->fp[3] = (char *)175;
// [VFTABLE] ((void ( *)(UIListBox *, int, tagUITask *, CCBUI *, _DWORD, int, _DWORD))(*p_pPanel)->__vftable[1].ShowWindow)(
// [VFTABLE]   *p_pPanel,
// [VFTABLE]   *v6,
// [VFTABLE]   pTask,
// [VFTABLE]   this,
// [VFTABLE]   0,
// [VFTABLE]   1,
// [VFTABLE]   0);
// [VFTABLE] ((void ( *)(UIListBox *, _DWORD))(*p_pPanel)->__vftable->ShowWindow)(*p_pPanel, 0);
    ((UIListBox *)*p_pPanel)->SetItemOffset(2, -4);
    ((UIListBox *)*p_pPanel)->SetFirstShow((int)"Name", 96);
    ((UIListBox *)*p_pPanel)->SetFirstShow((int)unk_5DFDCC, 37);
    ((UIListBox *)*p_pPanel)->SetFirstShow((int)unk_5DFDC0, 50);
    ((UIListBox *)*p_pPanel)->SetLockSel();
    ((UIListBox *)*p_pPanel)->GetSel(g_nUnkDataTable[9], 0);
    ((UIListBox *)*p_pPanel)->SetItemData(1);
    v10 = (char **)sub_445FE0(a2);
    pTask->fp[0] = *v10;
    pTask->fp[1] = v10[1];
    pTask->fp[2] = v10[2];
    pTask->fp[3] = v10[3];
    ((UIListBox *)*p_pPanel)->GetLockSel((int)&g_EffMgr.m_sz5D8C3C[1812], (int *)pTask, 16, 16, 0);
    ((CCBUI *)&(*p_pPanel)->m_scrollbar)->SetSelection(26);
    ((CCBUI *)&(*p_pPanel)->m_scrollbar)->SetCurPlayer(-5);
    ((CCBUI *)&(*p_pPanel)->m_scrollbar)->SetRoleStatePointers(-2);
    ++v6;
    ++p_pPanel;
  }
  while ( (int)v6 < (int)&g_nSkillItemIDTable[24] );
  result = (BOOL)((CCBControlWindow *)this)->HandleInput(0);
  LOBYTE(result) = 1;
  return result;
}

// 0x0051A880
int CCBUI::Destroy_a880()
{
  int result; // eax
  UIStatic **p_pPanel; // edi
  int v4; // ebx
  UIStatic *v5; // ecx
  UIStatic *v6; // ecx
  UIStatic *v7; // ecx
  UIStatic *v8; // ecx
  UIStatic *v9; // ecx
  UIStatic *v10; // ecx
  UIStatic *m_pAttackSequenBack; // ecx
  UIListBox *v12; // [esp+0x0] [ebp-0x10]
  int v13; // [esp+0x4] [ebp-0xC]

  ((CCBRoleState *)this)->Destroy(v12, v13);
  p_pPanel = &this->pPanel;
  v4 = 6;
  do
  {
    if ( *p_pPanel )
    {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))(*p_pPanel)->__vftable->sub_4431B0)(*p_pPanel, 1);
      *p_pPanel = 0;
    }
    ++p_pPanel;
    --v4;
  }
  while ( v4 );
  v5 = this->m_pBattleFieldAttr[5];
  if ( v5 )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))v5->__vftable->sub_4431B0)(v5, 1);
    this->m_pBattleFieldAttr[5] = 0;
  }
  v6 = this->m_pAttackSequenFace[0];
  if ( v6 )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))v6->__vftable->sub_4431B0)(v6, 1);
    this->m_pAttackSequenFace[0] = 0;
  }
  v7 = this->m_pAttackSequenFace[1];
  if ( v7 )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))v7->__vftable->sub_4431B0)(v7, 1);
    this->m_pAttackSequenFace[1] = 0;
  }
  v8 = this->m_pAttackSequenFace[2];
  if ( v8 )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))v8->__vftable->sub_4431B0)(v8, 1);
    this->m_pAttackSequenFace[2] = 0;
  }
  v9 = this->m_pAttackSequenFace[3];
  if ( v9 )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))v9->__vftable->sub_4431B0)(v9, 1);
    this->m_pAttackSequenFace[3] = 0;
  }
  v10 = this->m_pAttackSequenFace[4];
  if ( v10 )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))v10->__vftable->sub_4431B0)(v10, 1);
    this->m_pAttackSequenFace[4] = 0;
  }
  m_pAttackSequenBack = this->m_pAttackSequenBack;
  if ( m_pAttackSequenBack )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))m_pAttackSequenBack->__vftable->sub_4431B0)(m_pAttackSequenBack, 1);
    this->m_pAttackSequenBack = 0;
  }
  return result;
}

// 0x0051AB00
BOOL CCBUI::CheckMagicKeyPress(int nVal, int nVal2)
{
  if ( this->m_bvisible == 1
    && (g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 || g_Input.KeyInfo[17].PressTime == 1) )
  {
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(g_nSkillItemIDTable[18], -1);
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x00525540
void CCBUI::InitShopUI()
{
  ((UIRoleDialog *)((char *)this + 100572))->_UIRoleDialog();
  ((UIRoleDialog *)((char *)this + 99204))->_UIRoleDialog();
  ((UIFrameWnd *)((char *)this + 6812))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 6660))->UIFrameWnd::_UIFrameWnd();
  ((UITextArea *)((char *)this + 6468))->Destroy();
  ((UIButton *)((char *)this + 6208))->_UIButton();
  ((UIFrameWnd *)((char *)this + 6016))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5864))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5712))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5560))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5408))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 73)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5104))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4952))->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)((char *)this + 4620))->PalScript_Init();
  ((PalScript *)((char *)this + 4312))->PalScript_Init();
  ((PalScript *)((char *)this + 4004))->PalScript_Init();
  ((UICaption *)((char *)this + 3660))->Destroy2();
  ((UIStatic *)((char *)this + 3412))->_UIStatic();
  ((UIStatic *)((char *)this + 3164))->_UIStatic();
  ((UIFrameWnd *)&this->m_Task[10])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Task[7].param.nTimes)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Task[5].param.fSpeed)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x005257B0
int * CCBUI::InitSkillUI(int nVal)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  float fSpeed; // edx
  int v11; // ecx
  const char **v12; // ebp
  UIStatic *v13; // edi
  int v14; // edx
  int v15; // edx
  const char **v16; // ebp
  PalScript *v17; // edi
  int *v18; // ebx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // edx
  int v28; // ecx
  int v29; // edx
  int v30; // ecx
  CCBUI *v31; // ebp
  int v32; // ebx
  CCBUI *v33; // ebp
  int v34; // ebx
  int nTimes; // edx
  CCBUI *v36; // eax
  int v37; // ecx
  char *v38; // eax
  int v39; // eax
  float v41; // [esp+0x120] [ebp-E4h]
  int v42; // [esp+0x134] [ebp-D0h] BYREF
  int v43; // [esp+0x138] [ebp-CCh]
  int v44; // [esp+0x13C] [ebp-C8h]
  int v45; // [esp+0x140] [ebp-C4h]
  int v46; // [esp+0x144] [ebp-C0h] BYREF
  int v47; // [esp+0x148] [ebp-BCh]
  int v48; // [esp+0x14C] [ebp-B8h]
  int v49; // [esp+0x150] [ebp-B4h]
  int v50; // [esp+0x154] [ebp-B0h] BYREF
  int v51; // [esp+0x158] [ebp-ACh]
  int v52; // [esp+0x15C] [ebp-A8h]
  int v53; // [esp+0x160] [ebp-A4h]
  int v54; // [esp+0x164] [ebp-A0h] BYREF
  int v55; // [esp+0x168] [ebp-0x9C]
  int v56; // [esp+0x16C] [ebp-0x98]
  int v57; // [esp+0x170] [ebp-0x94]
  int v58; // [esp+0x174] [ebp-0x90] BYREF
  int v59; // [esp+0x178] [ebp-0x8C]
  int v60; // [esp+0x17C] [ebp-0x88]
  int v61; // [esp+0x180] [ebp-0x84]
  _DWORD v62[2]; // [esp+0x184] [ebp-0x80] BYREF
  int v63; // [esp+0x18C] [ebp-0x78]
  int v64; // [esp+0x190] [ebp-0x74]
  _DWORD v65[2]; // [esp+0x194] [ebp-0x70] BYREF
  int v66; // [esp+0x19C] [ebp-0x68]
  int v67; // [esp+0x1A0] [ebp-0x64]
  int v68[4]; // [esp+0x1A4] [ebp-0x60] BYREF
  _DWORD v69[4]; // [esp+0x1B4] [ebp-0x50] BYREF
  _DWORD v70[4]; // [esp+0x1C4] [ebp-0x40] BYREF
  _DWORD v71[4]; // [esp+0x1D4] [ebp-0x30] BYREF
  _DWORD v72[4]; // [esp+0x1E4] [ebp-0x20] BYREF
  _DWORD v73[4]; // [esp+0x1F4] [ebp-0x10] BYREF

  this->pPanel = 0;
  this->m_pAttackSequenBack = 0;
  this->m_pBattleFieldAttr[0] = this->m_pBattleFieldAttr[2];
  this->m_pBattleFieldAttr[1] = (UIStatic *)((char *)this->pPanel + (unsigned int)this->m_pBattleFieldAttr[3]);
  ((UIListBox *)this)->SetSelTexture(-1, (int)this->m_pAttackSequenBack, (int)this->pPanel, (int)this->m_pBattleFieldAttr[0], (int)this->m_pBattleFieldAttr[1], 0);
  *((_DWORD *)this + 24800) = nVal;
  v3 = *((_DWORD *)this + 1238);
  v47 = 32;
  v46 = 168;
  v48 = 636;
  v49 = 136;
  (*(void ( **)(char *, char *, int *, CCBUI *))(v3 + 16))(
    (char *)this + 4952,
    &g_PlayerAttBuffer.Remark[250],
    &v46,
    this);
  ((UIStatic *)((char *)this + 4952))->CreateFromTemplate();
  v4 = *((_DWORD *)this + 1276);
  v47 += 6;
  v46 += 24;
  v49 = v47 + 158;
  v48 = v46 + 428;
  (*(void ( **)(char *, char *, int *, CCBUI *))(v4 + 16))(
    (char *)this + 5104,
    &g_PlayerAttBuffer.Remark[250],
    &v46,
    this);
  ((UIScene *)((char *)this + 5104))->SetShow(0);
  sub_446010((char *)this + 5104);
  v5 = *((_DWORD *)this + 1466);
  v62[1] = 0;
  v62[0] = 0;
  v63 = 14;
  v64 = 600;
  (*(void ( **)(char *, ARC_PlayerAtt *, _DWORD *, CCBUI *))(v5 + 16))(
    (char *)this + 5864,
    &g_PlayerAttBuffer,
    v62,
    this);
  ((UIStatic *)((char *)this + 5864))->CreateFromTemplate();
  v6 = *((_DWORD *)this + 1504);
  v62[0] = 786;
  v63 = 800;
  (*(void ( **)(char *, ARC_PlayerAtt *, _DWORD *, CCBUI *))(v6 + 16))(
    (char *)this + 6016,
    &g_PlayerAttBuffer,
    v62,
    this);
  ((UIStatic *)((char *)this + 6016))->CreateFromTemplate();
  v7 = *((_DWORD *)this + 1552);
  v72[1] = 0;
  v72[0] = 16;
  v72[2] = 788;
  v72[3] = 92;
  (*(void ( **)(char *, char *, _DWORD *, CCBUI *))(v7 + 16))(
    (char *)this + 6208,
    &g_PlayerAttBuffer.Remark[250],
    v72,
    this);
  ((UIScene *)((char *)this + 6208))->GetChildCount();
  ((UIScene *)((char *)this + 6208))->GetChildAt();
  sub_43FD90((float *)this + 1552, 0);
  ((UIScrollBar *)((char *)this + 6208))->SetRange(620.0);
  *((_DWORD *)this + 1605) = 1;
  *((_DWORD *)this + 1612) = 300;
  *((_DWORD *)this + 1610) = 1092616192;
  *((_DWORD *)this + 1607) = 255;
  ((UIProgressBar *)((char *)this + 6208))->FindChildByName(620.0);
  *((_DWORD *)this + 1580) = 1142620160;
  v8 = *((_DWORD *)this + 1352);
  v59 = 18;
  v58 = 64;
  v60 = 96;
  v61 = 42;
  (*(void ( **)(char *, char *, int *, CCBUI *))(v8 + 16))(
    (char *)this + 5408,
    &g_PlayerAttBuffer.Remark[250],
    &v58,
    this);
  v9 = *((_DWORD *)this + 1390);
  v59 = v61;
  v61 += 24;
  (*(void ( **)(char *, char *, int *, CCBUI *))(v9 + 16))(
    (char *)this + 5560,
    &g_PlayerAttBuffer.Remark[250],
    &v58,
    this);
  fSpeed = this->m_Task[5].param.fSpeed;
  v69[1] = 136;
  v69[0] = 90;
  v69[2] = 714;
  v69[3] = 598;
  (*(void ( **)(float *, char *, _DWORD *, CCBUI *))(LODWORD(fSpeed) + 16))(
    &this->m_Task[5].param.fSpeed,
    &g_PlayerAttBuffer.Remark[250],
    v69,
    this);
  ((UIStatic *)&this->m_Task[5].param.fSpeed)->CreateFromTemplate();
  v65[1] = 162;
  v65[0] = 120;
  v66 = 160;
  v67 = 208;
  v12 = &off_5706AC;
  v13 = (UIStatic *)&this->m_pRoleStateDefenceDec[4];
  do
  {
    LOBYTE(v11) = *(_BYTE *)(*((_DWORD *)this + 24800) + 1756);
// [VFTABLE] ((void ( *)(UIStatic *, const char *, _DWORD *, CCBUI *, char *, int))v13->__vftable[1].ShowWindow)(
// [VFTABLE]   v13,
// [VFTABLE]   *v12,
// [VFTABLE]   v65,
// [VFTABLE]   this,
// [VFTABLE]   aSubgameApprais_3,
// [VFTABLE]   v11);
    ((UIStatic *)v13)->SetText();
    ++v12;
    v65[0] = v66;
    v13 = (UIStatic *)((char *)v13 + 248);
    v66 += 40;
  }
  while ( (int)v12 < (int)&off_5706C0 );
  v14 = *((_DWORD *)this + 1314);
  v70[1] = 170;
  v70[0] = 326;
  v70[2] = 482;
  v70[3] = 202;
  (*(void ( **)(char *, char *, _DWORD *, CCBUI *))(v14 + 16))(
    (char *)this + 5256,
    &g_PlayerAttBuffer.Remark[283],
    v70,
    this);
  ((UIScene *)((char *)this + 5256))->SetShow(0);
  sub_446010((char *)this + 5256);
  v51 = 146;
  v50 = 552;
  v52 = 597;
  v53 = 210;
  v16 = &off_5706C0;
  v17 = (PalScript *)&this->m_Task[12].fp[2];
  v18 = (int *)((char *)this + 3112);
  do
  {
    LOBYTE(v15) = *(_BYTE *)(*((_DWORD *)this + 24800) + 1756);
    (*(void ( **)(PalScript *, const char *, int *, CCBUI *, char *, _DWORD, int))(v17->m_bLoadSceneScript + 28))(
      v17,
      *v16,
      &v50,
      this,
      "SubGame\\Appraise\\Do\\Magnifier",
      0,
      v15);
    v19 = v51;
    *v18 = v50;
    v20 = v52;
    v18[1] = v19;
    v21 = v53;
    v18[2] = v20;
    v18[3] = v21;
    ((PalScript *)v17)->OpenScript("SubGame\\Appraise\\Do\\unMagnifier.tga", *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
    v15 = v52;
    ++v16;
    v18 += 4;
    v17 = (PalScript *)((char *)v17 + 344);
    v50 = v52 + 2;
    v52 += 47;
  }
  while ( (int)v16 < (int)&off_5706CC );
  v22 = *((_DWORD *)this + 24800);
  v43 = 548;
  v42 = 213;
  v44 = 307;
  v45 = 568;
  LOBYTE(v22) = *(_BYTE *)(v22 + 1756);
  (*(void ( **)(char *, char *, int *, CCBUI *, char *, int))(*((_DWORD *)this + 791) + 28))(
    (char *)this + 3164,
    &g_PlayerAttBuffer.Remark[272],
    &v42,
    this,
    "SubGame\\Appraise\\Do\\Result",
    v22);
  v23 = v43;
  *((_DWORD *)this + 24791) = v42;
  v24 = v45;
  *((_DWORD *)this + 24792) = v23;
  v25 = v44;
  *((_DWORD *)this + 24793) = v44;
  v42 = v25 + 200;
  *((_DWORD *)this + 24794) = v24;
  v26 = *((_DWORD *)this + 24800);
  v44 = v25 + 294;
  LOBYTE(v26) = *(_BYTE *)(v26 + 1756);
  (*(void ( **)(char *, char *, int *, CCBUI *, char *, int))(*((_DWORD *)this + 853) + 28))(
    (char *)this + 3412,
    &g_PlayerAttBuffer.Remark[273],
    &v42,
    this,
    "SubGame\\Appraise\\Do\\Result",
    v26);
  v27 = v43;
  v71[1] = 573;
  v71[0] = 358;
  v71[2] = 448;
  *((_DWORD *)this + 24795) = v42;
  v28 = v44;
  v71[3] = 598;
  *((_DWORD *)this + 24796) = v27;
  v29 = v45;
  *((_DWORD *)this + 24797) = v28;
  v30 = *((_DWORD *)this + 24800);
  *((_DWORD *)this + 24798) = v29;
  LOBYTE(v29) = *(_BYTE *)(v30 + 1756);
  (*(void ( **)(char *, char *, _DWORD *, CCBUI *, char *, _DWORD, int))(*((_DWORD *)this + 915) + 28))(
    (char *)this + 3660,
    &g_PlayerAttBuffer.Remark[274],
    v71,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v29);
  (**((void ( ***)(char *, _DWORD))this + 915))((char *)this + 3660, 0);
  ((CCBFiveNimbusWindow *)((char *)this + 4004))->CreateScriptAndCamera((int)&g_PlayerAttBuffer.Remark[287], (int)this);
  ((CCBFiveNimbusWindow *)((char *)this + 4004))->SetFloatParam(600.0);
  ((Camera *)((char *)this + 4004))->UpdateCameraLookAt(400, 320);
  v31 = (CCBUI *)((char *)this + 4080);
  v32 = 5;
  do
  {
// [VFTABLE] v31->__vftable = 0;
    ((UIPushButton *)((char *)this + 4004))->SetAnimOffset(1, 1127481344, v41);
    *((_DWORD *)this + 1062) = 58;
    v31 = (CCBUI *)((char *)v31 + 32);
    --v32;
    ++*((_DWORD *)this + 1018);
  }
  while ( v32 );
  ((CCBFiveNimbusWindow *)((char *)this + 4312))->CreateScriptAndCamera((int)&g_PlayerAttBuffer.Remark[288], (int)this);
  ((CCBFiveNimbusWindow *)((char *)this + 4312))->SetFloatParam(600.0);
  ((Camera *)((char *)this + 4312))->UpdateCameraLookAt(400, 320);
  v33 = (CCBUI *)((char *)this + 4388);
  v34 = 5;
  do
  {
// [VFTABLE] v33->__vftable = 0;
    ((UIPushButton *)((char *)this + 4312))->SetAnimOffset(1, 1127481344, v41);
    *((_DWORD *)this + 1139) = 58;
    v33 = (CCBUI *)((char *)v33 + 32);
    --v34;
    ++*((_DWORD *)this + 1095);
  }
  while ( v34 );
  nTimes = this->m_Task[7].param.nTimes;
  *((_DWORD *)this + 1233) = -1029701632;
  *((_DWORD *)this + 1236) = -1029701632;
  *((_DWORD *)this + 1232) = -1017380864;
  *((_DWORD *)this + 1234) = 0;
  *((_DWORD *)this + 1235) = 1130102784;
  *((_DWORD *)this + 1237) = 0;
  v55 = 136;
  v54 = 90;
  v56 = 716;
  v57 = 603;
  (*(void ( **)(int *, char *, int *, CCBUI *))(nTimes + 16))(
    &this->m_Task[7].param.nTimes,
    &g_PlayerAttBuffer.Remark[275],
    &v54,
    this);
  ((UIStatic *)&this->m_Task[7].param.nTimes)->CreateFromTemplate();
  (*(void ( **)(int *, _DWORD))this->m_Task[7].param.nTimes)(&this->m_Task[7].param.nTimes, 0);
  ((CCBFiveNimbusWindow *)((char *)this + 4620))->CreateScriptAndCamera((int)&g_PlayerAttBuffer.Remark[289], (int)this);
  ((CCBFiveNimbusWindow *)((char *)this + 4620))->SetFloatParam(580.0);
  ((Camera *)((char *)this + 4620))->UpdateCameraLookAt(400, 346);
  v36 = (CCBUI *)((char *)this + 4696);
  v37 = 5;
  do
  {
// [VFTABLE] v36->__vftable = 0;
    v36 = (CCBUI *)((char *)v36 + 32);
    --v37;
    ++*((_DWORD *)this + 1172);
  }
  while ( v37 );
  v38 = this->m_Task[10].fp[0];
  v55 = 164;
  v54 = 326;
  v56 = 482;
  v57 = 196;
  (*((void ( **)(tagUITask *, char *, int *, CCBUI *))v38 + 4))(
    &this->m_Task[10],
    &g_PlayerAttBuffer.Remark[275],
    &v54,
    this);
  ((UIScene *)&this->m_Task[10])->SetShow(0);
  sub_446010(&this->m_Task[10]);
  (*(void ( **)(tagUITask *, _DWORD))this->m_Task[10].fp[0])(&this->m_Task[10], 0);
  v39 = *((_DWORD *)this + 1428);
  v73[1] = 158;
  v73[0] = 536;
  v73[2] = 581;
  v73[3] = 208;
  (*(void ( **)(char *, char *, _DWORD *, CCBUI *))(v39 + 16))(
    (char *)this + 5712,
    &g_PlayerAttBuffer.Remark[250],
    v73,
    this);
  ((UIStatic *)((char *)this + 5712))->CreateFromTemplate();
  (**((void ( ***)(char *, _DWORD))this + 1428))((char *)this + 5712, 0);
  v68[0] = 300;
  v68[3] = 300;
  *((_DWORD *)this + 1542) = 45;
  *((_DWORD *)this + 1543) = 50;
  v68[1] = 200;
  v68[2] = 500;
  ((ARC_PlayerAtt *)((char *)this + 99204))->Create((int)&byte_ABE00B, (int)v68);
  ((UIItem *)((char *)this + 99204))->SetData(31);
  sub_446010((char *)this + 99204);
  ((ARC_PlayerAtt *)((char *)this + 100572))->Create((int)&byte_ABC00C, (int)v68);
  ((UIItem *)((char *)this + 100572))->SetData(31);
  sub_446010((char *)this + 100572);
  *((_DWORD *)this + 1614) = 120;
  *((_DWORD *)this + 1615) = 534;
  *((_DWORD *)this + 1616) = 420;
  *((_DWORD *)this + 1613) = 278;
  ((UINote *)((char *)this + 6468))->Create((int)&g_PlayerAttBuffer.Remark[284], (int)this + 6452, (int)this, "UI\\Flex\\Note");
  (**((void ( ***)(char *, _DWORD))this + 1617))((char *)this + 6468, 0);
  (*(void ( **)(char *, char *, char *, CCBUI *))(*((_DWORD *)this + 1665) + 16))(
    (char *)this + 6660,
    &g_PlayerAttBuffer.Remark[284],
    (char *)this + 6452,
    this);
  ((UIScene *)((char *)this + 6660))->SetShow(0);
  sub_446010((char *)this + 6660);
  (**((void ( ***)(char *, _DWORD))this + 1665))((char *)this + 6660, 0);
  (*(void ( **)(char *, char *, char *, CCBUI *))(*((_DWORD *)this + 1703) + 16))(
    (char *)this + 6812,
    &g_PlayerAttBuffer.Remark[285],
    (char *)this + 6452,
    this);
  ((UIScene *)((char *)this + 6812))->SetShow(0);
  (**((void ( ***)(char *, _DWORD))this + 1703))((char *)this + 6812, 0);
  return (int *)sub_446010((char *)this + 6812);
}

// 0x00526660
void CCBUI::Render()
{
  ScreenEffect *v2; // esi
  int v3; // ebx
  ScreenEffect *v4; // esi
  int v5; // ebx
  CCBMagicWindow *v6; // [esp+0x0] [ebp-0x10]

  ((CCBControlWindow *)this)->Render(v6);
  if ( *((_BYTE *)this + 99196) )
  {
    v2 = (ScreenEffect *)((char *)this + 36092);
    v3 = 36;
    do
    {
// [IDA_MISID]       if ( ((Concurrency *)&v2[-876])->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)v2 - 876)->Apply();
// [IDA_MISID]       if ( ((Concurrency *)v2)->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)v2)->Apply();
      v2 = (ScreenEffect *)((char *)v2 + 584);
      --v3;
    }
    while ( v3 );
    *((_BYTE *)this + 99196) = 0;
    *((_BYTE *)this + 99198) = 1;
  }
  else if ( *((_BYTE *)this + 99197) )
  {
    v4 = (ScreenEffect *)((char *)this + 78140);
    v5 = 36;
    do
    {
// [IDA_MISID]       if ( ((Concurrency *)&v4[-876])->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)v4 - 876)->Apply();
// [IDA_MISID]       if ( ((Concurrency *)v4)->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)v4)->Apply();
      v4 = (ScreenEffect *)((char *)v4 + 584);
      --v5;
    }
    while ( v5 );
    *((_BYTE *)this + 99197) = 0;
    *((_BYTE *)this + 99198) = 1;
  }
  else if ( *((_BYTE *)this + 99198) )
  {
    ((SaleUI *)this)->ResetGridState();
  }
}

// 0x00526740
int CCBUI::Update(int deltatime, int haveinput)
{
  DWORD TickCount; // eax
  DWORD v5; // eax
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // eax
  void ( **v9)(char *, _DWORD); // edx
  float fValue; // [esp+0x4] [ebp-0x28]

  if ( ((UIParabolaCtrl *)(UIParabolaCtrl *)this + 25143)->GetState() == 2 )
    ((CCBAttackSequen *)this)->AdvanceToNextSlot();
  if ( ((UIParabolaCtrl *)(UIParabolaCtrl *)this + 24801)->GetState() == 2 )
  {
    if ( *((_BYTE *)this + 15037) )
    {
    }
    else
      *((_BYTE *)this + 6204) = 0;
  }
  if ( *((_DWORD *)this + 1660) == 2 )
    (**((void ( ***)(char *, int))this + 1665))((char *)this + 6660, 1);
  if ( !*((_BYTE *)this + 6204) && !*((_BYTE *)this + 15018) && !*((_BYTE *)this + 15037) )
  {
    if ( !*((_BYTE *)this + 6192) )
    {
      TickCount = GetTickCount();
      *((_DWORD *)this + 1546) = TickCount;
      *((_DWORD *)this + 1547) = TickCount;
      *((_BYTE *)this + 6192) = 1;
    }
    v5 = GetTickCount();
    v6 = v5 - *((_DWORD *)this + 1547);
    *((_DWORD *)this + 1546) = v5;
    if ( v6 > 0x3E8 )
    {
      *((_DWORD *)this + 1547) = v5;
      *((_BYTE *)this + 6192) = 0;
      v7 = *((_DWORD *)this + 1550) - 1;
      *((_DWORD *)this + 1550) = v7;
      if ( v7 < 0 )
      {
        v8 = *((_DWORD *)this + 1549);
        *((_DWORD *)this + 1550) = 59;
        *((_DWORD *)this + 1549) = --v8;
        if ( v8 < 0 )
        {
          *((_DWORD *)this + 1549) = 0;
          *((_DWORD *)this + 1550) = 0;
          *((_BYTE *)this + 6204) = 1;

        }
      }
      if ( *((_BYTE *)this + 6368) )
        *((_DWORD *)this + 1580) = 1065353216;
      fValue = (float)(10 * (*((_DWORD *)this + 1550) + 2));
      ((UIProgressBar *)((char *)this + 6208))->FindChildByName(fValue);
    }
  }
  CreateDigitPair(
    *((_DWORD *)this + 1550),
    (UIWnd **)this + 1352,
    (UIWnd **)this + 1390,
    pszTexBase,
    *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  if ( *((_BYTE *)this + 6176) )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    sub_445FA0((char *)this + 5712);
    if ( (g_Input.KeyInfo[1].Data & 0xF) == 1 )
    {
      v9 = (void ( **)(char *, _DWORD))*((_DWORD *)this + 1428);
      *((_BYTE *)this + 6176) = 0;
      (*v9)((char *)this + 5712, 0);
      sub_445FA0((char *)this + 5712);
      sub_445E50((int)&this->m_Task[12].fp[86 * *((_DWORD *)this + 1545) + 2]);
    }
  }
  ((UIListBox *)this)->Update(deltatime, haveinput);
  return 1;
}

// 0x005273D0
void CCBUI::PlayResultSound()
{
  int EntryPtr; // eax
  CScreenMode *Instance; // eax
  const void *v4; // [esp-0x8] [ebp-0x14]

  *((_BYTE *)this + 6204) = 1;
  if ( *((_BYTE *)this + 3232) )
  {
    if ( *((_DWORD *)this + 3758) )
      *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 0;
    else
      *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 1;
  }
  else if ( *((_BYTE *)this + 3480) )
  {
    *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = *((_DWORD *)this + 3758) == 1;
  }
  if ( *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) )
  {
    sprintf((char *const)&this->m_pBattleFieldAttr[4], "\\n      %s", (const char *)dword_DC873C);
    ((UICaption *)((char *)this + 101028))->SetEnable((int)&this->m_pBattleFieldAttr[4], 0);
    ((UIRoleSelect *)((char *)this + 100572))->SetByte(1);
    *((_BYTE *)this + 15037) = 0;
  }
  else
  {
    sprintf((char *const)&this->m_pBattleFieldAttr[4], "\\n      %s", (const char *)dword_DCF63C);
    ((UICaption *)((char *)this + 99660))->SetEnable((int)&this->m_pBattleFieldAttr[4], 0);
    ((UIRoleSelect *)((char *)this + 99204))->SetByte(1);
    EntryPtr = ((UINote *)*(UINote **)(*((_DWORD *)this + 24800) + 1724))->GetEntryPtr(*((_DWORD *)this + 3752));
    ((UICaption *)((char *)this + 5104))->SetEnable(EntryPtr, 0);
    (**((void ( ***)(char *, int))this + 1276))((char *)this + 5104, 1);
    *((_BYTE *)this + 15038) = 0;
    *((_BYTE *)this + 15037) = 1;
    v4 = off_5E7F20;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v4, 1);
  }
}

// 0x00527610
void CCBUI::UpdateCaptions()
{
  UIStatic **v2; // ecx
  int *p_nTimes; // ebp
  tagUITask *v4; // ebx
  CCBUI *v5; // edi
  bool v6; // zf
  char **v7; // edi
  int v8; // ebx
  char *v9; // ebp
  int v10; // eax
  int i; // ecx
  int v12; // ebx
  int v13; // eax
  int v14; // edx
  UIStatic **v15; // ebx
  int v16; // ecx
  int v17; // ebp
  UICaption *v18; // esi
  int v19; // [esp-0x4] [ebp-0x134]
  int v20; // [esp+0xC] [ebp-0x124]
  int v21; // [esp+0x14] [ebp-0x11C]
  LPCSTR lpString2; // [esp+0x28] [ebp-0x108]
  const CHAR *lpString2a; // [esp+0x28] [ebp-0x108]
  int v24; // [esp+0x2C] [ebp-0x104]
  char Buffer[253]; // [esp+0x30] [ebp-0x100] BYREF
  __int16 v26; // [esp+0x12D] [ebp-0x3]
  char v27; // [esp+0x12F] [ebp-0x1]

  v24 = 5;
  v2 = &this->m_pRoleStateDefenceDec[4];
  *((_BYTE *)this + 15036) = 1;
  p_nTimes = &this->m_Task[7].param.nTimes;
  v4 = &this->m_Task[10];
  v5 = (CCBUI *)((char *)this + 4388);
  for ( lpString2 = (LPCSTR)v2; ; v2 = (UIStatic **)lpString2 )
  {(*v2)->ShowWindow(0);
(*(void ( **)(int *, _DWORD))*p_nTimes)(&this->m_Task[7].param.nTimes, 0);
    (*(void ( **)(tagUITask *, _DWORD))v4->fp[0])(&this->m_Task[10], 0);
    v5[-1].m_Task[15].param.fEndY = 0.0;
// [VFTABLE] v5->__vftable = 0;
    v5->m_pRoleStateDefenceInc[4] = 0;
    (*(void ( **)(int *, _DWORD))*p_nTimes)(&this->m_Task[7].param.nTimes, 0);
    (*(void ( **)(tagUITask *, _DWORD))v4->fp[0])(&this->m_Task[10], 0);
    v5 = (CCBUI *)((char *)v5 + 32);
    v6 = v24 == 1;
    lpString2 += 248;
    --v24;
    if ( v6 )
      break;
  }
  v7 = &this->m_Task[12].fp[2];
  v8 = 3;
  do
  {
    (*(void ( **)(char **, _DWORD))*v7)(v7, 0);
    v7 += 86;
    --v8;
  }
  while ( v8 );
  (**((void ( ***)(char *, _DWORD))this + 791))((char *)this + 3164, 0);
  (**((void ( ***)(char *, _DWORD))this + 853))((char *)this + 3412, 0);
  (**((void ( ***)(char *, _DWORD))this + 915))((char *)this + 3660, 0);
  v9 = (char *)this + 6468;
  (**((void ( ***)(char *, int))this + 1617))((char *)this + 6468, 1);
  v10 = 0;
  *((_DWORD *)this + 3760) = 0;
  *((_DWORD *)this + 3761) = 80;
  for ( i = 0; i < 50; i += 10 )
  {
    if ( *((_BYTE *)this + v10 + 15013) && *((_BYTE *)this + v10 + 15024) )
    {
      v12 = *((_DWORD *)this + 3761);
      ++*((_DWORD *)this + 3760);
      *((_DWORD *)this + 3761) = 2 * (v12 + i);
    }
    ++v10;
  }
  v13 = *((_DWORD *)this + 3755);
  v14 = *((_DWORD *)this + 3761);
  v15 = &this->m_pBattleFieldAttr[4];
  *((_DWORD *)this + 1614) = 150;
  v21 = v14 + 40 * v13;
  v20 = *((_DWORD *)this + 3760);
  v19 = *((_DWORD *)this + 1550);
  *((_DWORD *)this + 3762) = v21;
  *((_DWORD *)this + 1616) = 20 * v20 + 350;
  sprintf(
    (char *const)&this->m_pBattleFieldAttr[4],
    "\\n\\n        %s:   %d\\n        %s: %d\\n        %s:   %d\\n        %s:     %d\\n",
    (const char *)dword_DC853C,
    v19,
    (const char *)dword_DC863C,
    v13,
    (const char *)dword_DC873C,
    v20,
    (const char *)dword_DC883C,
    v21);
  memset(Buffer, 0, sizeof(Buffer));
  v16 = *((_DWORD *)this + 24800);
  v26 = 0;
  v27 = 0;
  if ( *(_BYTE *)(v16 + 1740) )
  {
    if ( *((int *)this + 3760) > 0 )
    {
      sprintf(Buffer, "\\n\\n        %s: \\n\\n", (const char *)dword_DC893C);
      lstrcatA((LPSTR)&this->m_pBattleFieldAttr[4], Buffer);
      v17 = 0;
      lpString2a = (char *)this + 7776;
      do
      {
        if ( *((_BYTE *)this + v17 + 15024) )
        {
          lstrcatA((LPSTR)&this->m_pBattleFieldAttr[4], asc_5E9090);
          lstrcatA((LPSTR)&this->m_pBattleFieldAttr[4], lpString2a);
          lstrcatA((LPSTR)&this->m_pBattleFieldAttr[4], aN);
        }
        ++v17;
        lpString2a += 1608;
      }
      while ( v17 < 5 );
      v9 = (char *)this + 6468;
    }
    else
    {
      sprintf(Buffer, "\\n\\n        %s:   %s", (const char *)dword_DC893C, byte_DC7D3C);
      lstrcatA((LPSTR)&this->m_pBattleFieldAttr[4], Buffer);
    }
  }
  else
  {
    *((_DWORD *)this + 1614) = 200;
    *((_DWORD *)this + 1616) = 400;
  }
  v18 = (UICaption *)((char *)this + 6660);
  sub_445FA0(v18);
  sub_445FA0(v9);
// [VFTABLE] ((void ( *)(UICaption *, _DWORD))v18->__vftable->ShowWindow)(v18, 0);
  ((UICaption *)v18)->SetEnable((int)v15, 0);
}
