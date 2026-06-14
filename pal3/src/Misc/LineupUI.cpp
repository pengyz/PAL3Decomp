#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/LineupUI.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_4431B0(...);
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
char sub_474990(_BYTE *_this); // from annotations

void GetGridOffset(void *_this, int *pOut, int index); // from annotations

// Unnamed globals (extern)
extern char byte_1234567;
extern char byte_5967B0[3];
extern char byte_A00001;
extern char byte_A00102;
extern char byte_A00103;
extern char byte_A00104;
extern char byte_A00105;
extern char byte_A00106;
extern char byte_A00107;
extern char byte_A00108;
extern char byte_A00109;
extern char byte_A00110;
extern char byte_A00606;
extern int dword_56B6F0[];
extern int dword_56B77C[];
extern int dword_DC353C;
extern int dword_DC363C;
extern int dword_DC373C;
extern const char * off_56B794;
extern const char * off_56B97C;
extern const char * off_56BA08;
extern void * off_5AE3C4;
extern void * off_5B9DE4;
extern _SPropValue * off_5B9DF0;
extern void * off_5B9DF4;
extern int off_5BC4A4;
extern void * off_5C3EAC;
extern void * off_5C3ED4;
extern RoleSystem stru_C059A0;

// 0x00456500
int LineupUI::OnMsgHandleNav(unsigned int uMsg, unsigned int wParam, int lParam)
{
  CScreenMode *Instance; // eax
  const void *v7; // [esp-0x8] [ebp-0xC]

  if ( *(_DWORD *)&this->m_btnPar2[14][0]._texName[140] )
    return 1;
  ((TaskBookUI *)this)->HandleNavigation();
  ((CScreenMode *)this)->GetMouseScroll();
  ((TaskBookUI *)this)->HandleInput();
  if ( ((UIParabolaCtrl *)&this->m_btnPar2[14][0]._texName[144])->GetState() )
    return ((UIListBox *)this)->Update(uMsg, wParam);
  ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_SAVE")->WriteRegistryKey((DWORD)"SEEK", *(_DWORD *)&this->m_btnPar2[14][0]._texName[136]);
  *(_DWORD *)&this->m_btnPar2[14][0]._texName[140] = 1;
  v7 = off_5AE3C4;
  Instance = CScreenMode::GetInstance();
  ((CScreenMode *)Instance)->AudioSetPosition(v7, 1);
  return 1;
}

// 0x00470F40
void LineupUI::_LineupUI()
{
  UIListBox *v2; // [esp+0x0] [ebp-0x1C]
  int v3; // [esp+0x4] [ebp-0x18]

  LOBYTE(this->m_btnPar[9][6].m_viewRect.right) = 0;
  this->m_btnPar2[12][4].par_radiusY = 0;
  ((CCBRoleState *)this)->Destroy(v2, v3);
  ((UIFrameWnd *)&this->m_btnPar2[12][3]._element.m_rect.top)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[12][3]._texName[112])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[12][3].m_iscolorfade)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[12][2]._element.m_text[4])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[12][2]._texName[208])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[12][2]._texName[56])->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_btnPar2[12][1]._element.m_childs)->Destroy2();
  ((UICaption *)&this->m_btnPar2[12][1].m_time.oldtick)->Destroy2();
  ((UICaption *)&this->m_btnPar2[12][0]._texName[172])->Destroy2();
  ((UICaption *)&this->m_btnPar2[11][6]._sizeX)->Destroy2();
  ((UICaption *)&this->m_btnPar2[11][6]._texName[40])->Destroy2();
  ((UICaption *)&this->m_btnPar2[11][5]._element.m_rect.top)->Destroy2();
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->DeleteRow();
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->DeleteRow();
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->DeleteRow();
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->DeleteRow();
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->DeleteRow();
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->DeleteRow();
  ((UIFrameWnd *)&this->m_btnPar2[9][3]._element.m_benable)->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)&this->m_btnPar2[9][3]._texName[236])->ctor();
  ((UIFrameWnd *)&this->m_btnPar2[8][2]._texName[240])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[7][5]._texName[72])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[7][5].m_isSubA)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[7][4]._element.m_fonttype)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[7][4]._texName[200])->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)&this->m_btnPar2[7][4]._H)->PalScript_Init();
  ((UIRoleDialog *)&this->m_btnPar2[7][1]._element)->_UIRoleDialog();
  ((PalScript *)&this->m_btnPar2[6][6]._element.m_mouseoff)->ctor();
  ((UICaption *)&this->m_btnPar2[6][6]._texName[40])->Destroy2();
  ((UIFrameWnd *)&this->m_btnPar2[6][6].m_tempx)->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)&this->m_btnPar2[6][5]._element.m_disablepic)->ctor();
  ((UIFrameWnd *)&this->m_btnPar2[6][5]._texName[236])->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00471590
int LineupUI::InitListView()
{
  int v2; // ebp
  char *v3; // edi
  float m_tempx; // eax
  gbTexture *m_disablepic; // edx
  int v6; // edx
  int *p_m_nTextW; // edi
  float *p_y; // ebx
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int m_benable; // eax
  int v14; // edx
  int v15; // edx
  float v16; // eax
  float v17; // edx
  float x; // edx
  int v19; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  unsigned int m_sec; // edi
  float *p_m_tempx; // edi
  int v26; // ebx
  int v27; // ebx
  int v28; // ebp
  LONG top; // edx
  unsigned int v30; // ecx
  void *vftable; // eax
  char *v32; // ebp
  int v33; // eax
  float m_posy; // edx
  gbTexture *ptex; // edx
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // edx
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // edx
  int v48; // edx
  int v49; // eax
  Parent_Data *m_fonttype; // edx
  int v51; // edx
  int v52; // ecx
  int v53; // edx
  int v54; // edx
  LONG v55; // edx
  int v56; // edx
  unsigned int oldtick; // eax
  int v58; // edx
  int v59; // eax
  int v60; // ecx
  gbTexture *v61; // eax
  int v62; // edi
  int result; // eax
  int v64; // [esp+0x244] [ebp-0x10C]
  int v65; // [esp+0x244] [ebp-0x10C]
  float v66; // [esp+0x248] [ebp-0x108]
  _DWORD v67[2]; // [esp+0x258] [ebp-F8h] BYREF
  int v68; // [esp+0x260] [ebp-F0h]
  int v69; // [esp+0x264] [ebp-ECh]
  int v70; // [esp+0x268] [ebp-E8h] BYREF
  int v71; // [esp+0x26C] [ebp-E4h]
  int v72; // [esp+0x270] [ebp-E0h]
  int v73; // [esp+0x274] [ebp-DCh]
  _DWORD v74[2]; // [esp+0x278] [ebp-D8h] BYREF
  int v75; // [esp+0x280] [ebp-D0h]
  int v76; // [esp+0x284] [ebp-CCh]
  gbVec3D pPos; // [esp+0x288] [ebp-C8h] BYREF
  int v78; // [esp+0x294] [ebp-BCh]
  int v79; // [esp+0x298] [ebp-B8h] BYREF
  int v80; // [esp+0x29C] [ebp-B4h]
  int v81; // [esp+0x2A0] [ebp-B0h]
  int v82; // [esp+0x2A4] [ebp-ACh]
  gbVec3D pDir; // [esp+0x2A8] [ebp-A8h] BYREF
  int v84; // [esp+0x2B4] [ebp-0x9C]
  _DWORD v85[4]; // [esp+0x2B8] [ebp-0x98] BYREF
  int v86; // [esp+0x2C8] [ebp-0x88]
  char *v87; // [esp+0x2CC] [ebp-0x84]
  unsigned int v88; // [esp+0x2D0] [ebp-0x80] BYREF
  unsigned int v89; // [esp+0x2D4] [ebp-0x7C]
  unsigned int v90; // [esp+0x2D8] [ebp-0x78]
  unsigned int v91; // [esp+0x2DC] [ebp-0x74]
  int v92; // [esp+0x2E0] [ebp-0x70] BYREF
  int v93; // [esp+0x2E4] [ebp-0x6C]
  int v94; // [esp+0x2E8] [ebp-0x68]
  int v95; // [esp+0x2EC] [ebp-0x64]
  _DWORD v96[4]; // [esp+0x2F0] [ebp-0x60] BYREF
  _DWORD v97[4]; // [esp+0x300] [ebp-0x50] BYREF
  _DWORD v98[4]; // [esp+0x310] [ebp-0x40] BYREF
  int v99; // [esp+0x320] [ebp-0x30] BYREF
  int v100; // [esp+0x324] [ebp-0x2C]
  int v101; // [esp+0x328] [ebp-0x28]
  int v102; // [esp+0x32C] [ebp-0x24]
  _DWORD v103[4]; // [esp+0x330] [ebp-0x20] BYREF
  int nVal[4]; // [esp+0x340] [ebp-0x10] BYREF
  int v105; // [esp+0x354] [ebp+0x4]

  v2 = 0;
  v3 = &this->m_btnPar2[6][5]._texName[220];
  *(_QWORD *)&this->m_btnPar2[6][5]._texName[220] = 0;
  *(_DWORD *)&this->m_btnPar2[6][5]._texName[228] = 800;
  *(_DWORD *)&this->m_btnPar2[6][5]._texName[232] = 600;
  ((UIListBox *)this)->SetSelTexture(-1, *(_DWORD *)&this->m_btnPar2[6][5]._texName[220], *(_DWORD *)&this->m_btnPar2[6][5]._texName[224], *(_DWORD *)&this->m_btnPar2[6][5]._texName[228], *(_DWORD *)&this->m_btnPar2[6][5]._texName[232], 0);
  *(_DWORD *)&this->m_btnPar2[6][5]._texName[224] = 0;
  *(_DWORD *)v3 = 0;
  *(_DWORD *)&this->m_btnPar2[6][5]._texName[232] = *(_DWORD *)&this->m_btnPar2[6][5]._texName[224] + this->rc.top;
  *(_DWORD *)&this->m_btnPar2[6][5]._texName[228] = *(_DWORD *)v3 + this->rc.left;
  m_tempx = this->m_btnPar2[6][6].m_tempx;
  v103[1] = 22;
  v103[0] = 266;
  v103[2] = 482;
  v103[3] = 150;
  (*(void ( **)(float *, int, _DWORD *, LineupUI *))(LODWORD(m_tempx) + 16))(
    &this->m_btnPar2[6][6].m_tempx,
    769,
    v103,
    this);
  ((UIStatic *)&this->m_btnPar2[6][6].m_tempx)->CreateFromTemplate();
  m_disablepic = this->m_btnPar2[6][5]._element.m_disablepic;
  v98[1] = 564;
  v98[0] = 0;
  v98[2] = 800;
  v98[3] = 599;
  ((void ( *)(gbTexture **, int, _DWORD *, char *, _DWORD, LineupUI *))m_disablepic->Height)(
    &this->m_btnPar2[6][5]._element.m_disablepic,
    769,
    v98,
    "UI\\Flex\\framebar.tga",
    0,
    this);
  ((CScreenMode *)&this->m_btnPar2[6][5]._element.m_disablepic)->SetPosition(30,   35);
  v6 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[236];
  v96[1] = 0;
  v96[0] = 0;
  v96[2] = 206;
  v96[3] = 600;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v6 + 16))(
    &this->m_btnPar2[6][5]._texName[236],
    769,
    v96,
    this);
  ((UIStatic *)&this->m_btnPar2[6][5]._texName[236])->CreateFromTemplate();
  p_m_nTextW = &this->m_btnPar2[8][2]._element.m_nTextW;
  p_y = &this->m_btnPar2[7][0]._y;
  do
  {
    v9 = *(_DWORD *)&this->m_btnPar2[7][1]._texName[244];
    v10 = *(_DWORD *)&this->m_btnPar2[7][1]._texName[240];
    v85[0] = *(_DWORD *)&this->m_btnPar2[7][1]._texName[236];
    v11 = *(_DWORD *)&this->m_btnPar2[7][1]._texName[248];
    v85[1] = v10;
    v85[3] = v10 + v11;
    v12 = dword_56B6F0[v2];
    v85[2] = v85[0] + v9;
    (*(void ( **)(float *, int, _DWORD *, LineupUI *))(*(_DWORD *)p_y + 16))(p_y, v12, v85, this);
    ((UIStatic *)p_y)->CreateFromTemplate();
    (**(void ( ***)(float *, _DWORD))p_y)(p_y, 0);
    (*(void ( **)(int *, int, _DWORD *, LineupUI *))(*p_m_nTextW + 16))(
      p_m_nTextW,
      dword_56B6F0[v2],
      v85,
      this);
    ((UIStatic *)p_m_nTextW)->CreateFromTemplate();
    p_m_nTextW[42] = 1090519040;
    p_m_nTextW[44] = 1;
    (*(void ( **)(int *, _DWORD))*p_m_nTextW)(p_m_nTextW, 0);
    (*(void ( **)(int *, int, _DWORD *, LineupUI *))(p_m_nTextW[45] + 16))(
      p_m_nTextW + 45,
      dword_56B6F0[v2],
      v85,
      this);
    ((UIStatic *)(p_m_nTextW + 45))->CreateFromTemplate();
    p_m_nTextW[87] = 1090519040;
    p_m_nTextW[89] = 1;
    (*(void ( **)(int *, _DWORD))p_m_nTextW[45])(p_m_nTextW + 45, 0);
    (*(void ( **)(int *, int, _DWORD *, LineupUI *))(p_m_nTextW[90] + 16))(
      p_m_nTextW + 90,
      dword_56B6F0[v2],
      v85,
      this);
    ((UIStatic *)(p_m_nTextW + 90))->CreateFromTemplate();
    p_m_nTextW[132] = 1090519040;
    p_m_nTextW[134] = 1;
    (*(void ( **)(int *, _DWORD))p_m_nTextW[90])(p_m_nTextW + 90, 0);
    (*(void ( **)(int *, int, _DWORD *, LineupUI *))(p_m_nTextW[135] + 16))(
      p_m_nTextW + 135,
      dword_56B6F0[v2],
      v85,
      this);
    ((UIStatic *)(p_m_nTextW + 135))->CreateFromTemplate();
    p_m_nTextW[177] = 1090519040;
    p_m_nTextW[179] = 1;
    (*(void ( **)(int *, _DWORD))p_m_nTextW[135])(p_m_nTextW + 135, 0);
    (*(void ( **)(int *, int, _DWORD *, LineupUI *))(p_m_nTextW[180] + 16))(
      p_m_nTextW + 180,
      dword_56B6F0[v2],
      v85,
      this);
    ((UIStatic *)(p_m_nTextW + 180))->CreateFromTemplate();
    p_m_nTextW[222] = 1090519040;
    p_m_nTextW[224] = 1;
    (*(void ( **)(int *, _DWORD))p_m_nTextW[180])(p_m_nTextW + 180, 0);
    ++v2;
    p_y += 38;
    p_m_nTextW += 225;
  }
  while ( v2 < 5 );
  m_benable = this->m_btnPar2[9][3]._element.m_benable;
  v93 = 32;
  v92 = 454;
  v94 = 790;
  v95 = 425;
  (*(void ( **)(int *, int, int *, LineupUI *))(m_benable + 16))(
    &this->m_btnPar2[9][3]._element.m_benable,
    769,
    &v92,
    this);
  ((UIStatic *)&this->m_btnPar2[9][3]._element.m_benable)->CreateFromTemplate();
  v14 = *(_DWORD *)&this->m_btnPar2[9][3]._texName[236];
  v80 = v93;
  v79 = v92 + 7;
  v82 = v93 + 32;
  v81 = v92 + 327;
  (*(void ( **)(char *, int, int *, char *, _DWORD, LineupUI *))(v14 + 28))(
    &this->m_btnPar2[9][3]._texName[236],
    769,
    &v79,
    "UI\\Flex\\Bar.tga",
    0,
    this);
  ((CScreenMode *)&this->m_btnPar2[9][3]._texName[236])->SetPosition(32,   32);
  v15 = *(_DWORD *)&this->m_btnPar2[8][2]._texName[240];
  v80 = 82;
  v79 = 466;
  v81 = 774;
  v82 = 114;
  (*(void ( **)(char *, int, int *, LineupUI *))(v15 + 16))(
    &this->m_btnPar2[8][2]._texName[240],
    769,
    &v79,
    this);
  ((UIScene *)&this->m_btnPar2[8][2]._texName[240])->SetShow(0);
  sprintf(
    (char *const)&this->rc.right,
    "%s            %s   %s %s",
    (const char *)dword_DC353C,
    (const char *)dword_DC363C,
    (const char *)dword_DC373C,
    (const char *)&g_bSaveFlag);
  ((UICaption *)&this->m_btnPar2[8][2]._texName[240])->SetEnable((int)&this->rc.right, 0);
  this->m_btnPar2[10][0].m_color.Color = 106;
  this->m_btnPar2[10][0].m_sec = 472;
  *(_DWORD *)&this->m_btnPar2[10][0]._isActive = 770;
  LODWORD(this->m_btnPar2[10][0]._fade) = this->m_btnPar2[10][0].m_color.Color + 278;
  v16 = *(float *)&this->m_btnPar2[10][0]._isActive;
  LODWORD(pPos.y) = this->m_btnPar2[10][0].m_color.Color + 14;
  LODWORD(v16) -= 31;
  pPos.x = v16;
  pDir.x = v16;
  LODWORD(v17) = LODWORD(v16) + 22;
  LOBYTE(v16) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  v78 = LODWORD(pPos.y) + 26;
  LODWORD(pDir.y) = LODWORD(pPos.y) + 232;
  pPos.z = v17;
  pDir.z = v17;
  x = this->m_btnPar2[10][0]._x;
  v84 = LODWORD(pPos.y) + 258;
  (*(void ( **)(float *, int, unsigned int *, LineupUI *, _DWORD, int, float))(LODWORD(x) + 28))(
    &this->m_btnPar2[10][0]._x,
    773,
    &this->m_btnPar2[10][0].m_sec,
    this,
    0,
    1,
    COERCE_FLOAT(LODWORD(v16)));
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetLockSel();
  *(_DWORD *)&this->m_btnPar2[10][2]._isActive = -4;
  this->m_btnPar2[10][2]._fade = NAN;
  LODWORD(this->m_btnPar2[10][2]._x) = 10;
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->m_btnPar2[10][0].m_sec, 38, 27, 0);
  ((CCBUI *)&this->m_btnPar2[10][0]._texName[56])->ShowEffect(this->m_btnPar2[10][0].m_color.Color + 1, *(_DWORD *)&this->m_btnPar2[10][0]._isActive - 38, *(_DWORD *)&this->m_btnPar2[10][0]._isActive);
  ((CCBUI *)&this->m_btnPar2[10][0]._texName[56])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_btnPar2[10][0]._texName[56])->SetSelection(27);
  ((CCBUI *)&this->m_btnPar2[10][0]._texName[56])->SetCurPlayer(5);
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetFirstShow((int)"Name", 131);
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetFirstShow((int)"Price", 52);
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetFirstShow((int)&g_pCombatUIData, 36);
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetFirstShow((int)&off_5BC4A4, 36);
  v19 = ((CCBUI *)&this->m_btnPar2[10][0]._texName[56])->VirtualCall();
  LOBYTE(v19) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, unsigned int *, LineupUI *, _DWORD, int, int))(*(_DWORD *)&this->m_btnPar2[10][2]._texName[20]
                                                                                        + 28))(
    &this->m_btnPar2[10][2]._texName[20],
    774,
    &this->m_btnPar2[10][0].m_sec,
    this,
    0,
    1,
    v19);
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetLockSel();
  *(_DWORD *)&this->m_btnPar2[10][4]._texName[12] = -4;
  *(_DWORD *)&this->m_btnPar2[10][4]._texName[16] = -6;
  *(_DWORD *)&this->m_btnPar2[10][4]._texName[20] = 10;
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->m_btnPar2[10][0].m_sec, 38, 27, 0);
  ((CCBUI *)&this->m_btnPar2[10][2]._texName[100])->ShowEffect(this->m_btnPar2[10][0].m_color.Color + 1, *(_DWORD *)&this->m_btnPar2[10][0]._isActive - 38, *(_DWORD *)&this->m_btnPar2[10][0]._isActive);
  ((CCBUI *)&this->m_btnPar2[10][2]._texName[100])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_btnPar2[10][2]._texName[100])->SetSelection(27);
  ((CCBUI *)&this->m_btnPar2[10][2]._texName[100])->SetCurPlayer(5);
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetFirstShow((int)"Name", 131);
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetFirstShow((int)"Price", 52);
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetFirstShow((int)&off_5BC4A4, 36);
  ((CCBUI *)&this->m_btnPar2[10][2]._texName[100])->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][2]._texName[20])(
    &this->m_btnPar2[10][2]._texName[20],
    0);
  LOBYTE(v20) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, unsigned int *, LineupUI *, _DWORD, int, int))(*(_DWORD *)&this->m_btnPar2[10][4]._texName[64]
                                                                                        + 28))(
    &this->m_btnPar2[10][4]._texName[64],
    775,
    &this->m_btnPar2[10][0].m_sec,
    this,
    0,
    1,
    v20);
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetLockSel();
  *(_DWORD *)&this->m_btnPar2[10][6]._texName[56] = -4;
  *(_DWORD *)&this->m_btnPar2[10][6]._texName[60] = -6;
  *(_DWORD *)&this->m_btnPar2[10][6]._texName[64] = 10;
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->m_btnPar2[10][0].m_sec, 38, 27, 0);
  ((CCBUI *)&this->m_btnPar2[10][4]._texName[144])->ShowEffect(this->m_btnPar2[10][0].m_color.Color + 1, *(_DWORD *)&this->m_btnPar2[10][0]._isActive - 38, *(_DWORD *)&this->m_btnPar2[10][0]._isActive);
  ((CCBUI *)&this->m_btnPar2[10][4]._texName[144])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_btnPar2[10][4]._texName[144])->SetSelection(27);
  ((CCBUI *)&this->m_btnPar2[10][4]._texName[144])->SetCurPlayer(5);
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetFirstShow((int)"Name", 131);
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetFirstShow((int)"Price", 52);
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetFirstShow((int)&off_5BC4A4, 36);
  ((CCBUI *)&this->m_btnPar2[10][4]._texName[144])->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][4]._texName[64])(
    &this->m_btnPar2[10][4]._texName[64],
    0);
  LOBYTE(v21) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, unsigned int *, LineupUI *, _DWORD, int, int))(*(_DWORD *)&this->m_btnPar2[10][6]._texName[108]
                                                                                        + 28))(
    &this->m_btnPar2[10][6]._texName[108],
    776,
    &this->m_btnPar2[10][0].m_sec,
    this,
    0,
    1,
    v21);
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetLockSel();
  *(_DWORD *)&this->m_btnPar2[11][1]._texName[100] = -4;
  *(_DWORD *)&this->m_btnPar2[11][1]._texName[104] = -6;
  *(_DWORD *)&this->m_btnPar2[11][1]._texName[108] = 10;
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->m_btnPar2[10][0].m_sec, 38, 27, 0);
  ((CCBUI *)&this->m_btnPar2[10][6]._texName[188])->ShowEffect(this->m_btnPar2[10][0].m_color.Color + 1, *(_DWORD *)&this->m_btnPar2[10][0]._isActive - 38, *(_DWORD *)&this->m_btnPar2[10][0]._isActive);
  ((CCBUI *)&this->m_btnPar2[10][6]._texName[188])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_btnPar2[10][6]._texName[188])->SetSelection(27);
  ((CCBUI *)&this->m_btnPar2[10][6]._texName[188])->SetCurPlayer(5);
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetFirstShow((int)"Name", 131);
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetFirstShow((int)"Price", 52);
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetFirstShow((int)&off_5BC4A4, 36);
  ((CCBUI *)&this->m_btnPar2[10][6]._texName[188])->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][6]._texName[108])(
    &this->m_btnPar2[10][6]._texName[108],
    0);
  LOBYTE(v22) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, unsigned int *, LineupUI *, _DWORD, int, int))(*(_DWORD *)&this->m_btnPar2[11][1]._texName[152]
                                                                                        + 28))(
    &this->m_btnPar2[11][1]._texName[152],
    777,
    &this->m_btnPar2[10][0].m_sec,
    this,
    0,
    1,
    v22);
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetLockSel();
  *(_DWORD *)&this->m_btnPar2[11][3]._texName[144] = -4;
  *(_DWORD *)&this->m_btnPar2[11][3]._texName[148] = -6;
  *(_DWORD *)&this->m_btnPar2[11][3]._texName[152] = 10;
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->m_btnPar2[10][0].m_sec, 38, 27, 0);
  ((CCBUI *)&this->m_btnPar2[11][1]._texName[232])->ShowEffect(this->m_btnPar2[10][0].m_color.Color + 1, *(_DWORD *)&this->m_btnPar2[10][0]._isActive - 38, *(_DWORD *)&this->m_btnPar2[10][0]._isActive);
  ((CCBUI *)&this->m_btnPar2[11][1]._texName[232])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_btnPar2[11][1]._texName[232])->SetSelection(27);
  ((CCBUI *)&this->m_btnPar2[11][1]._texName[232])->SetCurPlayer(5);
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetFirstShow((int)"Name", 131);
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetFirstShow((int)"Price", 52);
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetFirstShow((int)&off_5BC4A4, 36);
  ((CCBUI *)&this->m_btnPar2[11][1]._texName[232])->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][1]._texName[152])(
    &this->m_btnPar2[11][1]._texName[152],
    0);
  LOBYTE(v23) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, unsigned int *, LineupUI *, _DWORD, int, int))(*(_DWORD *)&this->m_btnPar2[11][3]._texName[196]
                                                                                        + 28))(
    &this->m_btnPar2[11][3]._texName[196],
    785,
    &this->m_btnPar2[10][0].m_sec,
    this,
    0,
    1,
    v23);
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetLockSel();
  *(_DWORD *)&this->m_btnPar2[11][5]._texName[188] = -4;
  *(_DWORD *)&this->m_btnPar2[11][5]._texName[192] = -6;
  *(_DWORD *)&this->m_btnPar2[11][5]._texName[196] = 10;
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->GetSel((int)"UI\\Assistant\\Communal\\ListBoxSelPic.tga", 0);
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", (int *)&this->m_btnPar2[10][0].m_sec, 38, 27, 0);
  ((CCBUI *)&this->m_btnPar2[11][3]._element.m_rect)->ShowEffect(this->m_btnPar2[10][0].m_color.Color + 1, *(_DWORD *)&this->m_btnPar2[10][0]._isActive - 38, *(_DWORD *)&this->m_btnPar2[10][0]._isActive);
  ((CCBUI *)&this->m_btnPar2[11][3]._element.m_rect)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_btnPar2[11][3]._element.m_rect)->SetSelection(27);
  ((CCBUI *)&this->m_btnPar2[11][3]._element.m_rect)->SetCurPlayer(5);
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetFirstShow((int)"Name", 131);
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetFirstShow((int)"Price", 52);
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetFirstShow((int)&off_5BC4A4, 36);
  ((CCBUI *)&this->m_btnPar2[11][3]._element.m_rect)->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][3]._texName[196])(
    &this->m_btnPar2[11][3]._texName[196],
    0);
  m_sec = this->m_btnPar2[10][0].m_sec;
  v89 = this->m_btnPar2[10][0].m_color.Color + 2;
  v88 = m_sec;
  v90 = m_sec + 256;
  v91 = v89 + 23;
  p_m_tempx = &this->m_btnPar2[9][4].m_tempx;
  v26 = 12;
  do
  {
    (*(void ( **)(float *, int, unsigned int *, LineupUI *))(*(_DWORD *)p_m_tempx + 16))(
      p_m_tempx,
      769,
      &v88,
      this);
    ((UIStatic *)p_m_tempx)->CreateFromTemplate();
    p_m_tempx += 38;
    v89 = v91;
    --v26;
    v91 += 23;
  }
  while ( v26 );
  LOBYTE(v86) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  v27 = (unsigned __int8)v86;
  v28 = v86;
  v87 = "UI\\Assistant\\Communal\\Add";
  v64 = v86;
  top = this->m_btnPar2[11][5]._element.m_rect.top;
  this->m_btnPar2[11][6]._element.m_ppicInfo = (_PlugInfo *)24;
  this->m_btnPar2[11][6]._element.m_disablepic = (gbTexture *)40;
  *(_DWORD *)&this->m_btnPar2[11][5]._texName[252] = 158;
  *(_DWORD *)&this->m_btnPar2[11][5]._texName[248] = 476;
  this->m_btnPar2[11][5]._ptex = (gbTexture *)500;
// [VFTABLE] this->m_btnPar2[11][5]._element.__vftable = (vtbl_0056AE2C *)198;
  (*(void ( **)(LONG *, int, char *, LineupUI *, char *, _DWORD, int))(top + 28))(
    &this->m_btnPar2[11][5]._element.m_rect.top,
    821,
    &this->m_btnPar2[11][5]._texName[248],
    this,
    "UI\\Assistant\\Communal\\Sub",
    0,
    v64);
  v30 = *(_DWORD *)&this->m_btnPar2[11][5]._texName[248];
// [VFTABLE] vftable = this->m_btnPar2[11][5]._element.__vftable;
  this->m_btnPar2[11][5]._element.m_wndcolor.Color = (unsigned int)vftable;
  v65 = v28;
  v32 = v87;
  this->m_btnPar2[11][5]._element.m_fontcolor.Color = v30;
  this->m_btnPar2[11][5]._element.m_id = this->m_btnPar2[11][5]._ptex;
  this->m_btnPar2[11][5]._element.m_rect.left = (LONG)this->m_btnPar2[11][6]._element.m_disablepic
                                              + (unsigned int)vftable;
  (*(void ( **)(int, gbColorQuad *, LineupUI *, char *, _DWORD, int))(*(_DWORD *)&this->m_btnPar2[11][6]._texName[40]
                                                                             + 28))(
    822,
    &this->m_btnPar2[11][5]._element.m_fontcolor,
    this,
    v32,
    0,
    v65);
  this->m_btnPar2[11][6]._element.m_mouseoff = v27;
  this->m_btnPar2[11][6]._element.m_disablepicInfo = (_PlugInfo *)1;
  ((PalScript *)&this->m_btnPar2[11][5]._element.m_rect.top)->OpenScript("UI\\Assistant\\Communal\\UnSub.tga", this->m_btnPar2[11][6]._element.m_mouseoff);
  ((PalScript *)&this->m_btnPar2[11][6]._texName[40])->OpenScript("UI\\Assistant\\Communal\\UnAdd.tga", this->m_btnPar2[11][6]._element.m_mouseoff);
  this->m_btnPar2[11][6]._element.m_pbk2 = (gbTexture *)20;
  (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
    &this->m_btnPar2[11][5]._element.m_rect.top,
    0);
  v33 = (**(int ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])(
          &this->m_btnPar2[11][6]._texName[40],
          0);
  LOBYTE(v33) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  m_posy = this->m_btnPar2[7][6].m_posy;
  v67[1] = 30;
  v67[0] = 472;
  v68 = 514;
  v69 = 80;
  (*(void ( **)(float *, int, _DWORD *, LineupUI *, char *, _DWORD, int))(LODWORD(m_posy) + 28))(
    &this->m_btnPar2[7][6].m_posy,
    808,
    v67,
    this,
    "UI\\GameMainUI\\Prop\\Resume",
    0,
    v33);
  ((PalScript *)&this->m_btnPar2[7][6].m_posy)->OpenScript("UI\\GameMainUI\\Prop\\Resume2.tga", LOBYTE(this->m_btnPar2[12][4].m_HelixAngle));
  ptex = this->m_btnPar2[7][6]._ptex;
  v67[0] = v68 + 11;
  v68 += 53;
  v36 = v68;
  LOBYTE(v36) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *, char *, _DWORD, int))ptex->Height)(
    &this->m_btnPar2[7][6]._ptex,
    809,
    v67,
    this,
    "UI\\GameMainUI\\Prop\\Treasure",
    0,
    v36);
  ((PalScript *)&this->m_btnPar2[7][6]._ptex)->OpenScript("UI\\GameMainUI\\Prop\\Treasure2.tga", LOBYTE(this->m_btnPar2[12][4].m_HelixAngle));
  v37 = *(_DWORD *)&this->m_btnPar2[8][0]._texName[16];
  v67[0] = v68 + 11;
  v68 += 53;
  v38 = v68;
  LOBYTE(v38) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, _DWORD *, LineupUI *, char *, _DWORD, int))(v37 + 28))(
    &this->m_btnPar2[8][0]._texName[16],
    816,
    v67,
    this,
    "UI\\GameMainUI\\Prop\\Attack",
    0,
    v38);
  ((PalScript *)&this->m_btnPar2[8][0]._texName[16])->OpenScript("UI\\GameMainUI\\Prop\\Attack2.tga", LOBYTE(this->m_btnPar2[12][4].m_HelixAngle));
  v39 = *(_DWORD *)&this->m_btnPar2[8][0]._element.m_text[4];
  v67[0] = v68 + 11;
  v68 += 53;
  v40 = v68;
  LOBYTE(v40) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, _DWORD *, LineupUI *, char *, _DWORD, int))(v39 + 28))(
    &this->m_btnPar2[8][0]._element.m_text[4],
    817,
    v67,
    this,
    "UI\\GameMainUI\\Prop\\Smelt",
    0,
    v40);
  ((PalScript *)&this->m_btnPar2[8][0]._element.m_text[4])->OpenScript("UI\\GameMainUI\\Prop\\Smelt2.tga", LOBYTE(this->m_btnPar2[12][4].m_HelixAngle));
  v41 = *(_DWORD *)&this->m_btnPar2[8][1]._texName[120];
  v67[0] = v68 + 11;
  v68 += 53;
  v42 = v68;
  LOBYTE(v42) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(char *, int, _DWORD *, LineupUI *, char *, _DWORD, int))(v41 + 28))(
    &this->m_btnPar2[8][1]._texName[120],
    818,
    v67,
    this,
    "UI\\GameMainUI\\Prop\\Ancient",
    0,
    v42);
  ((PalScript *)&this->m_btnPar2[8][1]._texName[120])->OpenScript("UI\\GameMainUI\\Prop\\Ancient2.tga", LOBYTE(this->m_btnPar2[12][4].m_HelixAngle));
  v43 = *(_DWORD *)&this->m_btnPar2[8][2].m_bGetBottom;
  v67[0] = v68 + 11;
  v68 += 53;
  v44 = v68;
  LOBYTE(v44) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  (*(void ( **)(_BYTE *, _DWORD, _DWORD *, LineupUI *, char *, _DWORD, int))(v43 + 28))(
    &this->m_btnPar2[8][2].m_bGetBottom,
    0,
    v67,
    this,
    "UI\\GameMainUI\\Equip\\Cloth",
    0,
    v44);
  ((PalScript *)&this->m_btnPar2[8][2].m_bGetBottom)->OpenScript("UI\\GameMainUI\\Equip\\Cloth2.tga", LOBYTE(this->m_btnPar2[12][4].m_HelixAngle));
  v45 = *(_DWORD *)&this->m_btnPar2[12][2]._texName[56];
  v71 = 142;
  v70 = 218;
  v72 = 450;
  v73 = 556;
  (*(void ( **)(char *, int, int *, LineupUI *))(v45 + 16))(
    &this->m_btnPar2[12][2]._texName[56],
    790,
    &v70,
    this);
  ((UIStatic *)&this->m_btnPar2[12][2]._texName[56])->CreateFromTemplate();
  v46 = *(_DWORD *)&this->m_btnPar2[12][2]._texName[208];
  v71 = 388;
  v70 = 232;
  v72 = 444;
  v73 = 556;
  (*(void ( **)(char *, int, int *, LineupUI *))(v46 + 16))(
    &this->m_btnPar2[12][2]._texName[208],
    790,
    &v70,
    this);
  ((UIScene *)&this->m_btnPar2[12][2]._texName[208])->SetShow(0);
  v47 = *(_DWORD *)&this->m_btnPar2[12][3].m_iscolorfade;
  v71 = 520;
  v70 = 232;
  v72 = 444;
  v73 = 552;
  (*(void ( **)(_BYTE *, int, int *, LineupUI *))(v47 + 16))(
    &this->m_btnPar2[12][3].m_iscolorfade,
    790,
    &v70,
    this);
  ((UIScene *)&this->m_btnPar2[12][3].m_iscolorfade)->SetShow(0);
  v48 = *(_DWORD *)&this->m_btnPar2[12][2]._element.m_text[4];
  v97[1] = 159;
  v97[0] = 403;
  v97[2] = 419;
  v97[3] = 191;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v48 + 16))(
    &this->m_btnPar2[12][2]._element.m_text[4],
    769,
    v97,
    this);
  ((UIStatic *)&this->m_btnPar2[12][2]._element.m_text[4])->CreateFromTemplate();
  v49 = *(_DWORD *)&this->m_btnPar2[7][4]._texName[200];
  v74[1] = 436;
  v74[0] = 456;
  v75 = 486;
  v76 = 555;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v49 + 16))(
    &this->m_btnPar2[7][4]._texName[200],
    801,
    v74,
    this);
  ((UIStatic *)&this->m_btnPar2[7][4]._texName[200])->CreateFromTemplate();
  m_fonttype = this->m_btnPar2[7][4]._element.m_fonttype;
  v74[0] = v75;
  v75 += 256;
  ((void ( *)(Parent_Data **, int, _DWORD *, LineupUI *))m_fonttype[4])(
    &this->m_btnPar2[7][4]._element.m_fonttype,
    801,
    v74,
    this);
  ((UIStatic *)&this->m_btnPar2[7][4]._element.m_fonttype)->CreateFromTemplate();
  v74[0] = v75;
  v75 += 32;
  (*(void ( **)(_BYTE *, int, _DWORD *, LineupUI *))(*(_DWORD *)&this->m_btnPar2[7][5].m_isSubA + 16))(
    &this->m_btnPar2[7][5].m_isSubA,
    801,
    v74,
    this);
  ((UIStatic *)&this->m_btnPar2[7][5].m_isSubA)->CreateFromTemplate();
  v51 = *(_DWORD *)&this->m_btnPar2[7][5]._texName[72];
  *(_DWORD *)&this->m_btnPar2[7][5]._texName[228] = 447;
  *(_DWORD *)&this->m_btnPar2[7][5]._texName[224] = 489;
  *(_DWORD *)&this->m_btnPar2[7][5]._texName[236] = *(_DWORD *)&this->m_btnPar2[7][5]._texName[228] + 100;
  *(_DWORD *)&this->m_btnPar2[7][5]._texName[232] = 745;
  (*(void ( **)(char *, int, char *, LineupUI *))(v51 + 16))(
    &this->m_btnPar2[7][5]._texName[72],
    801,
    &this->m_btnPar2[7][5]._texName[224],
    this);
  ((UIScene *)&this->m_btnPar2[7][5]._texName[72])->SetShow(0);
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[7][5]._texName[72])(&this->m_btnPar2[7][5]._texName[72], 0);
  v52 = *(_DWORD *)&this->m_btnPar2[7][5]._texName[232];
  v53 = *(_DWORD *)&this->m_btnPar2[6][6]._element.m_mouseoff;
  v100 = *(_DWORD *)&this->m_btnPar2[7][5]._texName[236] - 36;
  v99 = v52 - 36;
  v102 = v100 + 32;
  v101 = v52 - 36 + 24;
  (*(void ( **)(_BYTE *, int, int *, LineupUI *))(v53 + 16))(
    &this->m_btnPar2[6][6]._element.m_mouseoff,
    2,
    &v99,
    this);
  ((UIScene *)&this->m_btnPar2[6][6]._element.m_mouseoff)->LoadResource("ui\\scene\\page");
  ((UIScene *)&this->m_btnPar2[6][6]._element.m_mouseoff)->SetController(0x40000000);
  (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)(
    &this->m_btnPar2[6][6]._element.m_mouseoff,
    0);
  v54 = *(_DWORD *)&this->m_btnPar2[12][3]._texName[112];
  this->m_btnPar2[12][3]._element.m_wndcolor.Color = 392;
  this->m_btnPar2[12][3]._element.m_fontcolor.Color = 478;
  this->m_btnPar2[12][3]._element.m_id = (void *)624;
  this->m_btnPar2[12][3]._element.m_rect.left = 424;
  (*(void ( **)(char *, int, gbColorQuad *, LineupUI *))(v54 + 16))(
    &this->m_btnPar2[12][3]._texName[112],
    793,
    &this->m_btnPar2[12][3]._element.m_fontcolor,
    this);
  ((UIScene *)&this->m_btnPar2[12][3]._texName[112])->SetShow(0);
  sprintf((char *const)&this->rc.right, "%s %d", (const char *)&g_bSaveFlag, ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
  v55 = this->m_btnPar2[12][3]._element.m_rect.top;
  this->m_btnPar2[12][4].m_viewRect.bottom = 392;
  this->m_btnPar2[12][4].m_viewRect.right = 638;
  this->m_btnPar2[12][4].view_radiusX = 764;
  this->m_btnPar2[12][4].view_radiusY = 424;
  (*(void ( **)(LONG *, int, LONG *, LineupUI *))(v55 + 16))(
    &this->m_btnPar2[12][3]._element.m_rect.top,
    792,
    &this->m_btnPar2[12][4].m_viewRect.right,
    this);
  ((UIScene *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetShow(0);
  ((UICaption *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetEnable((int)g_szSceneUIText, 0);
  LOBYTE(v56) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  oldtick = this->m_btnPar2[12][1].m_time.oldtick;
  this->m_btnPar2[12][1].m_state = 569;
  this->m_btnPar2[12][1].m_xflag = 300;
  *(_DWORD *)&this->m_btnPar2[12][1].m_iscolorfade = 390;
  this->m_btnPar2[12][1].m_time.newtick = 594;
  (*(void ( **)(unsigned int *, int, int *, LineupUI *, char *, _DWORD, int))(oldtick + 28))(
    &this->m_btnPar2[12][1].m_time.oldtick,
    788,
    &this->m_btnPar2[12][1].m_xflag,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v56);
  LOBYTE(v58) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  v59 = *(_DWORD *)&this->m_btnPar2[12][1].m_iscolorfade + 132;
  this->m_btnPar2[12][1].m_xflag = v59;
  *(_DWORD *)&this->m_btnPar2[12][1].m_iscolorfade = v59 + 90;
  (*((void ( **)(PtrArray *, int, int *, LineupUI *, char *, _DWORD, int))this->m_btnPar2[12][1]._element.m_childs.m_pData
   + 7))(
    &this->m_btnPar2[12][1]._element.m_childs,
    789,
    &this->m_btnPar2[12][1].m_xflag,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v58);
  v60 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[228] - 38;
  v61 = (gbTexture *)(*(_DWORD *)&this->m_btnPar2[6][5]._texName[232] - 50);
  v62 = *(_DWORD *)&this->m_btnPar2[6][6]._texName[40];
  this->m_btnPar2[6][6]._element.m_ppicInfo = (_PlugInfo *)v60;
  this->m_btnPar2[6][6]._element.m_disablepic = v61;
  v61 = (gbTexture *)((char *)v61 + 48);
  this->m_btnPar2[6][6]._element.m_pbk2 = v61;
  LOBYTE(v61) = LOBYTE(this->m_btnPar2[12][4].m_HelixAngle);
  this->m_btnPar2[6][6]._element.m_disablepicInfo = (_PlugInfo *)(v60 + 38);
  (*(void ( **)(char *, int, _PlugInfo **, LineupUI *, char *, _DWORD, gbTexture *))(v62 + 28))(
    &this->m_btnPar2[6][6]._texName[40],
    770,
    &this->m_btnPar2[6][6]._element.m_ppicInfo,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    0,
    v61);
  ((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H)->CreateScriptAndCamera(807, (int)this);
  if ( !strcmp("D16", g_szSceneUIText) )
    sprintf((char *const)&this->rc.right, byte_5967B0, "NONE");
  else
    sprintf((char *const)&this->rc.right, "Item\\%s\\%s.pol", "D16", "D16");
  ((PalScript *)&this->m_btnPar2[7][4].m_time)->LoadModel((const char *)&this->rc.right, 0);
  this->m_btnPar2[7][4].m_time.oldtick = 0;
  *(_DWORD *)&this->m_btnPar2[7][4].m_iscolorfade = 1;
  ((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H)->SetFloatParam(120.0);
  ((Camera *)&this->m_btnPar2[7][4]._H)->UpdateCameraLookAt(330, 258, 600);
  ((UIPushButton *)&this->m_btnPar2[7][4]._H)->SetAnimOffset(1, 0, v66);
  nVal[1] = 200;
  nVal[0] = 300;
  nVal[2] = 500;
  nVal[3] = 300;
  ((ARC_PlayerAtt *)&this->m_btnPar2[7][1]._element)->Create((int)&g_PlayerAttBuffer2.skill[2] + 1, (int)nVal);
  ((UIItem *)&this->m_btnPar2[7][1]._element)->SetData(18);
  result = this->m_btnPar2[12][4].par_radiusY;
  if ( result )
  {
    if ( !--result )
    {
      LOBYTE(this->m_btnPar[9][6].m_viewRect.right) = 1;
      this->m_btnPar2[12][4]._H = v105;
      return result;
    }
  }
  else
  {
    this->m_btnPar2[12][4]._W = v105;
  }
  LOBYTE(this->m_btnPar[9][6].m_viewRect.right) = 1;
  return result;
}

// 0x00472A80
int LineupUI::SetPageIndex(int nPage)
{
  int result; // eax

  result = nPage;
  if ( nPage < 2 )
    this->m_btnPar2[12][4].par_radiusY = nPage;
  return result;
}

// 0x00472AA0
void LineupUI::RefreshListData()
{
  LONG *p_bottom; // ebp
  LONG *v3; // eax
  signed int v4; // edi
  int v5; // eax
  int *v6; // eax
  int *v7; // edx
  void **v8; // eax
  void **v9; // edx
  int v10; // ebp
  signed int v11; // edi
  int v12; // eax
  _DWORD *v13; // eax
  char *v14; // edx
  void **v15; // eax
  void **v16; // edx
  int v17; // ebp
  char *v18; // ebp
  _DWORD *v19; // eax
  char *v20; // ebp
  _DWORD *v21; // eax
  signed int v22; // ebp
  void **v23; // eax
  void *v24; // ecx
  void *v25; // edx
  void *v26; // edi
  void **v27; // eax
  void **v28; // eax
  void **v29; // ecx
  int v30; // ebp
  int nIndex; // [esp+0x10] [ebp-0x28]
  unsigned int nIndexa; // [esp+0x10] [ebp-0x28]
  unsigned int nIndexb; // [esp+0x10] [ebp-0x28]
  int nIndexc; // [esp+0x10] [ebp-0x28]
  int nIndexd; // [esp+0x10] [ebp-0x28]
  unsigned int nIndexe; // [esp+0x10] [ebp-0x28]
  char *v37; // [esp+0x14] [ebp-0x24]
  int *p_m_bfocus; // [esp+0x14] [ebp-0x24]
  Parent_Data **p_m_fonttype; // [esp+0x14] [ebp-0x24]
  int nVal; // [esp+0x18] [ebp-0x20]
  int nVala; // [esp+0x18] [ebp-0x20]
  int nValb; // [esp+0x18] [ebp-0x20]
  char *v43; // [esp+0x1C] [ebp-0x1C]
  _BYTE pOut[12]; // [esp+0x20] [ebp-0x18] BYREF
  _BYTE v45[12]; // [esp+0x2C] [ebp-0xC] BYREF

  v43 = &this->m_btnPar2[5][6]._texName[132];
  memset(&this->m_btnPar2[5][6]._texName[132], 0, 0x700u);
  *(_WORD *)&this->m_btnPar2[6][2]._texName[172] = 0;
  memset(&this->m_btnPar[6][2]._texName[72], 0, 0x1C08u);
  memset(&this->m_btnPar[8][0]._texName[240], 0, 0x1C08u);
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->ClearAll();
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(0);
  nIndex = 0;
  if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
  {
    v37 = &this->m_btnPar[8][0]._texName[240];
    p_bottom = &this->m_btnPar[9][6].m_viewRect.bottom;
    do
    {
      v3 = (LONG *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, nIndex);
      *p_bottom = *v3;
      p_bottom[1] = v3[1];
      p_bottom[2] = v3[2];
      p_bottom[5382] = *p_bottom;
      p_bottom[5383] = p_bottom[1];
      p_bottom[5384] = p_bottom[2];
      ++*(_DWORD *)&this->m_btnPar2[10][2]._texName[16];
      *(_DWORD *)v37 = p_bottom[1];
      sprintf((char *const)&this->rc.right, byte_5967B0, p_bottom[2] + 4);
      nVal = ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetItemOffset((char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(p_bottom[2] + 608) / 2);
      ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(1, nVal, (char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v37 - 1794));
      ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, nVal, (char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v37);
      ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(3, nVal, (char *)&this->rc.right, 0);
      ++nIndex;
      v37 += 4;
      p_bottom += 3;
    }
    while ( nIndex < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
  }
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->ClearAll();
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(1);
  v4 = 0;
  for ( nIndexa = 0; v4 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize(); nIndexa = v4 )
  {
    v5 = *(_DWORD *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v4);
    if ( v5 != 6409 && v5 != 6410 && v5 != 6411 && v5 != 6412 && v5 != 6413 && v5 != 6408 && v5 != 6427 )
    {
      v6 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v45, v4);
      v7 = &this->m_btnPar[10][5].m_xflag + 3 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
      *v7 = *v6;
      v7[1] = v6[1];
      v7[2] = v6[2];
// [VFTABLE] v8 = &this->__vftable + 3 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
      v9 = v8 + 12605;
      v8 += 17987;
      *v8 = *v9;
      v8[1] = v9[1];
      v8[2] = v9[2];
      *(&this->m_btnPar[8][2]._element.m_wndcolor.Color + *(_DWORD *)&this->m_btnPar2[10][4]._texName[60]) = *(&this->m_btnPar[10][5].m_state + 3 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60]);
      sprintf(
        (char *const)&this->rc.right,
        byte_5967B0,
        *((_DWORD *)&this->m_btnPar[10][5].m_iscolorfade + 3 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60]) + 4);
      v10 = ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetItemOffset((char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *(_DWORD *)(*((_DWORD *)&this->m_btnPar[10][5].m_iscolorfade
                    + 3 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60])
                  + 608)
      / 2);
      ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(1, v10, (char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *(_DWORD *)&this->m_btnPar[6][4]._texName[4 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] + 100]);
      ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(2, v10, (char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *(&this->m_btnPar[8][2]._element.m_wndcolor.Color + *(_DWORD *)&this->m_btnPar2[10][4]._texName[60]));
      ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(3, v10, (char *)&this->rc.right, 0);
      v4 = nIndexa;
      ++*(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
    }
    ++v4;
  }
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->ClearAll();
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(2);
  v11 = 0;
  for ( nIndexb = 0; v11 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize(); nIndexb = v11 )
  {
    v12 = *(_DWORD *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v45, v11);
    if ( v12 != 6119
      && v12 != 6120
      && v12 != 6121
      && v12 != 6122
      && v12 != 6123
      && v12 != 6124
      && v12 != 6125
      && v12 != 6427 )
    {
      v13 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v11);
      v14 = &this->m_btnPar[11][4]._texName[12 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] + 20];
      *(_DWORD *)v14 = *v13;
      *((_DWORD *)v14 + 1) = v13[1];
      *((_DWORD *)v14 + 2) = v13[2];
// [VFTABLE] v15 = &this->__vftable + 3 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
      v16 = v15 + 13502;
      v15 += 18884;
      *v15 = *v16;
      v15[1] = v16[1];
      v15[2] = v16[2];
      *((_DWORD *)&this->m_btnPar[8][4]._element.m_childs.m_pData + *(_DWORD *)&this->m_btnPar2[10][6]._texName[104]) = *(_DWORD *)&this->m_btnPar[11][4]._texName[12 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] + 24];
      sprintf(
        (char *const)&this->rc.right,
        byte_5967B0,
        *(_DWORD *)&this->m_btnPar[11][4]._texName[12 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] + 28] + 4);
      v17 = ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetItemOffset((char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *(_DWORD *)(*(_DWORD *)&this->m_btnPar[11][4]._texName[12 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104]
                                                             + 28]
                  + 608)
      / 2);
      ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(1, v17, (char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *(_DWORD *)&this->m_btnPar[6][6]._texName[4 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] + 128]);
      ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(2, v17, (char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *((_DWORD *)&this->m_btnPar[8][4]._element.m_childs.m_pData + *(_DWORD *)&this->m_btnPar2[10][6]._texName[104]));
      ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(3, v17, (char *)&this->rc.right, 0);
      v11 = nIndexb;
      ++*(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
    }
    ++v11;
  }
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->ClearAll();
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(3);
  nIndexc = 0;
  if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
  {
    p_m_bfocus = &this->m_btnPar[8][6]._element.m_bfocus;
    v18 = &this->m_btnPar[12][3]._texName[104];
    do
    {
      v19 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v45, nIndexc);
      *(_DWORD *)v18 = *v19;
      *((_DWORD *)v18 + 1) = v19[1];
      *((_DWORD *)v18 + 2) = v19[2];
      *((_DWORD *)v18 + 5382) = *(_DWORD *)v18;
      *((_DWORD *)v18 + 5383) = *((_DWORD *)v18 + 1);
      *((_DWORD *)v18 + 5384) = *((_DWORD *)v18 + 2);
      ++*(_DWORD *)&this->m_btnPar2[11][1]._texName[148];
      *p_m_bfocus = *((_DWORD *)v18 + 1);
      sprintf((char *const)&this->rc.right, byte_5967B0, *((_DWORD *)v18 + 2) + 4);
      nVala = ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetItemOffset((char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(*((_DWORD *)v18 + 2) + 608) / 2);
      ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(1, nVala, (char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *(p_m_bfocus - 1794));
      ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, nVala, (char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *p_m_bfocus);
      ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(3, nVala, (char *)&this->rc.right, 0);
      ++nIndexc;
      ++p_m_bfocus;
      v18 += 12;
    }
    while ( nIndexc < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
  }
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetItem();
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->ClearAll();
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(4);
  nIndexd = 0;
  if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
  {
    p_m_fonttype = &this->m_btnPar[9][1]._element.m_fonttype;
    v20 = &this->m_btnPar[13][2]._texName[188];
    do
    {
      v21 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v45, nIndexd);
      *(_DWORD *)v20 = *v21;
      *((_DWORD *)v20 + 1) = v21[1];
      *((_DWORD *)v20 + 2) = v21[2];
      *((_DWORD *)v20 + 5382) = *(_DWORD *)v20;
      *((_DWORD *)v20 + 5383) = *((_DWORD *)v20 + 1);
      *((_DWORD *)v20 + 5384) = *((_DWORD *)v20 + 2);
      ++*(_DWORD *)&this->m_btnPar2[11][3]._texName[192];
      *p_m_fonttype = (Parent_Data *)*((_DWORD *)v20 + 1);
      sprintf((char *const)&this->rc.right, byte_5967B0, *((_DWORD *)v20 + 2) + 4);
      nValb = ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetItemOffset((char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(*((_DWORD *)v20 + 2) + 608) / 2);
      ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(1, nValb, (char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *(p_m_fonttype - 1794));
      ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, nValb, (char *)&this->rc.right, 0);
      sprintf((char *const)&this->rc.right, &dir[20], *p_m_fonttype);
      ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(3, nValb, (char *)&this->rc.right, 0);
      ++nIndexd;
      ++p_m_fonttype;
      v20 += 12;
    }
    while ( nIndexd < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
  }
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetItem();
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetItem();
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->ClearAll();
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(6);
  v22 = 0;
  for ( nIndexe = 0; v22 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize(); nIndexe = v22 )
  {
    v23 = (void **)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v45, v22);
    v24 = *v23;
    v25 = v23[1];
    v26 = v23[2];
    if ( *v23 != (void *)8146
      && v24 != (void *)8147
      && v24 != (void *)8149
      && v24 != (void *)8150
      && v24 != (void *)8151
      && v24 != (void *)8152 )
    {
      v27 = &this->m_btnPar[14][1]._element.m_id + 3 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
      *v27 = v24;
      v27[1] = v25;
      v27[2] = v26;
      *((_DWORD *)&this->m_btnPar[9][3]._element.m_ppic + *(_DWORD *)&this->m_btnPar2[11][5]._texName[236]) = *(&this->m_btnPar[14][1]._element.m_rect.left + 3 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236]);
// [VFTABLE] v28 = &this->__vftable + 3 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
      v29 = v28 + 16193;
      v28 += 21575;
      *v28 = *v29;
      v28[1] = v29[1];
      v28[2] = v29[2];
      sprintf(
        (char *const)&this->rc.right,
        byte_5967B0,
        *(&this->m_btnPar[14][1]._element.m_rect.top + 3 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236]) + 4);
      v30 = ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetItemOffset((char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *(_DWORD *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236])
                  + 608)
      / 2);
      ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(1, v30, (char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *(_DWORD *)&this->m_btnPar[7][5]._texName[4 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] + 212]);
      ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(2, v30, (char *)&this->rc.right, 0);
      sprintf(
        (char *const)&this->rc.right,
        &dir[20],
        *((_DWORD *)&this->m_btnPar[9][3]._element.m_ppic + *(_DWORD *)&this->m_btnPar2[11][5]._texName[236]));
      ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(3, v30, (char *)&this->rc.right, 0);
      v22 = nIndexe;
      ++*(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
    }
    ++v22;
  }
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->GetItem();
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->GetItem();
  qmemcpy(&this->m_btnPar2[6][2]._texName[174], v43, 0x702u);
}

// 0x00473520
int LineupUI::Render3DModels()
{
  int v2; // ebx
  float *p_m_posy; // edi
  int v4; // eax
  int v5; // eax
  int *p_m_nTextW; // ecx
  int v7; // edx
  UICursor *v8; // ecx
  char *p_x; // edi
  int result; // eax
  int v11; // [esp+0x14] [ebp+0x4]

  v2 = 6;
  p_m_posy = &this->m_btnPar2[7][6].m_posy;
  do
  {
    sub_445E50((int)p_m_posy);
    p_m_posy += 86;
    --v2;
  }
  while ( v2 );
  sub_445E50((int)(&this->m_btnPar2[7][6].m_posy + 86 * v11));

  *(_DWORD *)&this->m_btnPar2[11][5]._texName[240] = v11;
  ((UICaption *)&this->m_btnPar2[12][2]._texName[208])->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->m_btnPar2[12][3].m_iscolorfade)->SetEnable((int)g_szSceneUIText, 0);
  v4 = *(_DWORD *)&this->m_btnPar2[11][5]._texName[240];
  this->m_btnPar2[7][4].m_time.oldtick = 0;
  this->m_TimeMoney.m_bfocus = 0;
  sprintf((char *const)&this->rc.right, "%s %d", g_szCombatFieldName, *(&this->m_btnPar[9][5]._element.m_nTextW + v4));
  ((UICaption *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetEnable((int)&this->rc.right, 0);
  (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
    &this->m_btnPar2[11][5]._element.m_rect.top,
    0);
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])(
    &this->m_btnPar2[11][6]._texName[40],
    0);
  v5 = 0;
  p_m_nTextW = &this->m_btnPar[9][5]._element.m_nTextW;
  v7 = 6;
  do
  {
    v5 += *p_m_nTextW++;
    --v7;
  }
  while ( v7 );
  sprintf((char *const)&this->rc.right, "%s %d", g_szCombatFieldName, v5);
  ((UICaption *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetEnable((int)&this->rc.right, 0);
  *(_DWORD *)&this->m_btnPar2[12][4].m_bGetBottom = v11;
  switch ( v11 )
  {
    case 0:
      p_x = (char *)&this->m_btnPar2[10][0]._x;
      (*(void ( **)(float *, int))LODWORD(this->m_btnPar2[10][0]._x))(&this->m_btnPar2[10][0]._x, 1);
      ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][2]._texName[20])(
        &this->m_btnPar2[10][2]._texName[20],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][4]._texName[64])(
        &this->m_btnPar2[10][4]._texName[64],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][6]._texName[108])(
        &this->m_btnPar2[10][6]._texName[108],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][1]._texName[152])(
        &this->m_btnPar2[11][1]._texName[152],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][3]._texName[196])(
        &this->m_btnPar2[11][3]._texName[196],
        0);
      ((UIStatic *)&this->m_btnPar2[12][2]._element.m_text[4])->CreateFromTemplate();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(0);
      goto LABEL_11;
    case 1:
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_btnPar2[10][0]._x))(&this->m_btnPar2[10][0]._x, 0);
      p_x = &this->m_btnPar2[10][2]._texName[20];
      (**(void ( ***)(char *, int))&this->m_btnPar2[10][2]._texName[20])(
        &this->m_btnPar2[10][2]._texName[20],
        1);
      ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][4]._texName[64])(
        &this->m_btnPar2[10][4]._texName[64],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][6]._texName[108])(
        &this->m_btnPar2[10][6]._texName[108],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][1]._texName[152])(
        &this->m_btnPar2[11][1]._texName[152],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][3]._texName[196])(
        &this->m_btnPar2[11][3]._texName[196],
        0);
      ((UIStatic *)&this->m_btnPar2[12][2]._element.m_text[4])->CreateFromTemplate();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(2);
      goto LABEL_11;
    case 2:
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_btnPar2[10][0]._x))(&this->m_btnPar2[10][0]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][2]._texName[20])(
        &this->m_btnPar2[10][2]._texName[20],
        0);
      p_x = &this->m_btnPar2[10][4]._texName[64];
      (**(void ( ***)(char *, int))&this->m_btnPar2[10][4]._texName[64])(
        &this->m_btnPar2[10][4]._texName[64],
        1);
      ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][6]._texName[108])(
        &this->m_btnPar2[10][6]._texName[108],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][1]._texName[152])(
        &this->m_btnPar2[11][1]._texName[152],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][3]._texName[196])(
        &this->m_btnPar2[11][3]._texName[196],
        0);
      ((UIStatic *)&this->m_btnPar2[12][2]._element.m_text[4])->CreateFromTemplate();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(1);
      goto LABEL_11;
    case 3:
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_btnPar2[10][0]._x))(&this->m_btnPar2[10][0]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][2]._texName[20])(
        &this->m_btnPar2[10][2]._texName[20],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][4]._texName[64])(
        &this->m_btnPar2[10][4]._texName[64],
        0);
      p_x = &this->m_btnPar2[10][6]._texName[108];
      (**(void ( ***)(char *, int))&this->m_btnPar2[10][6]._texName[108])(
        &this->m_btnPar2[10][6]._texName[108],
        1);
      ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][1]._texName[152])(
        &this->m_btnPar2[11][1]._texName[152],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][3]._texName[196])(
        &this->m_btnPar2[11][3]._texName[196],
        0);
      ((UIStatic *)&this->m_btnPar2[12][2]._element.m_text[4])->CreateFromTemplate();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(3);
      goto LABEL_11;
    case 4:
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_btnPar2[10][0]._x))(&this->m_btnPar2[10][0]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][2]._texName[20])(
        &this->m_btnPar2[10][2]._texName[20],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][4]._texName[64])(
        &this->m_btnPar2[10][4]._texName[64],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][6]._texName[108])(
        &this->m_btnPar2[10][6]._texName[108],
        0);
      p_x = &this->m_btnPar2[11][1]._texName[152];
      (**(void ( ***)(char *, int))&this->m_btnPar2[11][1]._texName[152])(
        &this->m_btnPar2[11][1]._texName[152],
        1);
      ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][3]._texName[196])(
        &this->m_btnPar2[11][3]._texName[196],
        0);
      ((UIStatic *)&this->m_btnPar2[12][2]._element.m_text[4])->CreateFromTemplate();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(4);
LABEL_11:
      if ( ((UIListBox *)p_x)->GetItemData() > 0 )
        goto LABEL_14;
      break;
    case 5:
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_btnPar2[10][0]._x))(&this->m_btnPar2[10][0]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][2]._texName[20])(
        &this->m_btnPar2[10][2]._texName[20],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][4]._texName[64])(
        &this->m_btnPar2[10][4]._texName[64],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[10][6]._texName[108])(
        &this->m_btnPar2[10][6]._texName[108],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][1]._texName[152])(
        &this->m_btnPar2[11][1]._texName[152],
        0);
      (**(void ( ***)(char *, int))&this->m_btnPar2[11][3]._texName[196])(
        &this->m_btnPar2[11][3]._texName[196],
        1);
      ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->GetItem();
      ((UIStatic *)&this->m_btnPar2[12][2]._element.m_text[4])->CreateFromTemplate();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(6);
      if ( ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->GetItemData() > 0 )
LABEL_14:
        this->OnMessage(1007, 0, 0);
      break;
    default:
      break;
  }
  ((UICursor *)v8)->IRender();
  return result;
}

// 0x004739F0
int LineupUI::BuildEquipList()
{
  int result; // eax
  int v2; // edi
  int v3; // ebx
  int v4; // esi
  int v5; // eax
  int v6; // edx
  int v7; // ebp
  LONG *v8; // edx
  int v9; // edx
  int *v10; // ebx
  int v11; // edx
  int v12; // eax
  int v13; // ebp
  int v14; // [esp+0x8] [ebp-0xC]
  int v15; // [esp+0xC] [ebp-0x8]
  int v16; // [esp+0xC] [ebp-0x8]
  int *v17; // [esp+0x10] [ebp-0x4]
  int v18; // [esp+0x18] [ebp+0x4]
  int v19; // [esp+0x18] [ebp+0x4]

  v2 = v18;
  if ( v18 < 6 )
  {
    result = 0;
    v19 = 0;
    switch ( v2 )
    {
      case 0:
        result = *(_DWORD *)&this->m_btnPar2[10][2]._texName[16];
        goto LABEL_9;
      case 1:
        result = *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
        goto LABEL_9;
      case 2:
        result = *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
        goto LABEL_9;
      case 3:
        result = *(_DWORD *)&this->m_btnPar2[11][1]._texName[148];
        goto LABEL_9;
      case 4:
        result = *(_DWORD *)&this->m_btnPar2[11][3]._texName[192];
        goto LABEL_9;
      case 5:
        result = *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
LABEL_9:
        v19 = result;
        break;
      default:
        break;
    }
    v3 = 0;
    v14 = 0;
    if ( result > 0 )
    {
      do
      {
        v4 = 0;
        v5 = 299 * v2;
        v6 = 299 * v2 + v3;
        v7 = *(&this->m_btnPar[2][5]._element.m_benable + 2 * v6);
        v17 = &this->m_btnPar[2][5]._element.m_benable + 2 * v6;
        v8 = &this->m_btnPar[9][6].m_viewRect.bottom + 897 * v2;
        while ( v7 != *v8 )
        {
          ++v4;
          v8 += 3;
          if ( v4 >= v19 )
            goto LABEL_16;
        }
        v9 = v5 + v4 + 8113;
        v10 = &this->m_btnPar[2][5]._element.m_bfocus + 2 * v5 + 2 * v3;
// [VFTABLE] v15 = *((_DWORD *)&this->__vftable + v9);
// [VFTABLE] *((_DWORD *)&this->__vftable + v9) = *v10;
        *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * v5 + 72 + 4 * v14] = v15;
        v11 = v5 + v4;
        v12 = v5 + v4 + 2263;
        v13 = *(&this->m_btnPar[2][5]._element.m_benable + 2 * v11);
// [VFTABLE] v16 = *((_DWORD *)&this->__vftable + 2 * v12);
        *(&this->m_btnPar[2][5]._element.m_benable + 2 * v11) = *(&this->m_btnPar[9][6].m_viewRect.bottom + 3 * v11);
// [VFTABLE] *((_DWORD *)&this->__vftable + 2 * v12) = *v10;
        *v17 = v13;
        *v10 = v16;
        v3 = v14;
LABEL_16:
        result = v19;
        v14 = ++v3;
      }
      while ( v3 < v19 );
    }
  }
  return result;
}

// 0x00473B50
int LineupUI::InitItemList()
{
  int result; // eax
  signed int v3; // ebp
  LONG *p_bottom; // edi
  LONG *v5; // eax
  LONG *v6; // edx
  LONG *v7; // ecx
  LONG v8; // eax
  char *v9; // ebp
  char *v10; // eax
  int v11; // ecx
  char *v12; // ebp
  signed int v13; // ebx
  int *v14; // ecx
  int v15; // eax
  int v16; // edx
  int v17; // edi
  char *v18; // ecx
  void **v19; // eax
  void **v20; // ecx
  char *v21; // ebx
  int v22; // ebp
  int v23; // eax
  bool v24; // cc
  signed int v25; // ebx
  int *v26; // ecx
  int v27; // eax
  int v28; // edx
  int v29; // edi
  int *v30; // ecx
  void **v31; // eax
  void **v32; // ecx
  char *v33; // ebx
  int v34; // ebp
  int v35; // eax
  signed int v36; // ebp
  char *v37; // edi
  _DWORD *v38; // eax
  char *v39; // edx
  _DWORD *v40; // ecx
  int v41; // eax
  char *v42; // ebp
  char *v43; // eax
  int v44; // ecx
  signed int v45; // ebp
  char *v46; // edi
  _DWORD *v47; // eax
  char *v48; // edx
  _DWORD *v49; // ecx
  int v50; // eax
  char *v51; // ebp
  char *v52; // eax
  int v53; // ecx
  signed int v54; // ebx
  void **v55; // ecx
  void *v56; // eax
  void *v57; // edx
  void *v58; // edi
  void **v59; // ecx
  void **v60; // eax
  void **v61; // ecx
  char *v62; // ebx
  int v63; // ebp
  int v64; // eax
  int nValc; // [esp+0x10] [ebp-0x68]
  char *nVal; // [esp+0x10] [ebp-0x68]
  _BYTE *nVala; // [esp+0x10] [ebp-0x68]
  int nVald; // [esp+0x10] [ebp-0x68]
  int nVale; // [esp+0x10] [ebp-0x68]
  LONG *nValb; // [esp+0x10] [ebp-0x68]
  gbColorQuad v71; // [esp+0x18] [ebp-0x60] BYREF
  gbColorQuad v72; // [esp+0x1C] [ebp-0x5C] BYREF
  gbColorQuad v73; // [esp+0x20] [ebp-0x58] BYREF
  gbColorQuad v74; // [esp+0x24] [ebp-0x54] BYREF
  gbColorQuad v75; // [esp+0x28] [ebp-0x50] BYREF
  gbColorQuad v76; // [esp+0x2C] [ebp-0x4C] BYREF
  char pOut[12]; // [esp+0x30] [ebp-0x48] BYREF
  char v78[12]; // [esp+0x3C] [ebp-0x3C] BYREF
  char v79[12]; // [esp+0x48] [ebp-0x30] BYREF
  char v80[12]; // [esp+0x54] [ebp-0x24] BYREF
  char v81[12]; // [esp+0x60] [ebp-0x18] BYREF
  int v82[3]; // [esp+0x6C] [ebp-0xC] BYREF
  UIListBox *v83; // [esp+0x7C] [ebp+0x4]
  int *p_view_radiusY; // [esp+0x7C] [ebp+0x4]
  UIListBox *v85; // [esp+0x7C] [ebp+0x4]
  UIListBox *v86; // [esp+0x7C] [ebp+0x4]
  UIListBox *v87; // [esp+0x7C] [ebp+0x4]
  UIListBox *v88; // [esp+0x7C] [ebp+0x4]
  UIListBox *v89; // [esp+0x7C] [ebp+0x4]
  void *pItem; // [esp+0x80] [ebp+0x8]
  char *pItema; // [esp+0x80] [ebp+0x8]
  char *pItemb; // [esp+0x80] [ebp+0x8]
  char *pItemc; // [esp+0x80] [ebp+0x8]
  char *pItemd; // [esp+0x80] [ebp+0x8]
  char *pIteme; // [esp+0x80] [ebp+0x8]
  char *pItemf; // [esp+0x80] [ebp+0x8]

  result = (int)v83;
  switch ( (unsigned int)v83 )
  {
    case 0u:
      ((UIListBox *)&this->m_btnPar2[10][0]._x)->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(0);
      if ( (int)pItem >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(pItem);
      v3 = 0;
      if ( *(int *)&this->m_btnPar2[10][2]._texName[16] > 0 )
      {
        p_bottom = &this->m_btnPar[9][6].m_viewRect.bottom;
        do
        {
          v5 = (LONG *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v3++);
          *p_bottom = *v5;
          p_bottom[1] = v5[1];
          v6 = p_bottom;
          p_bottom[2] = v5[2];
          v7 = p_bottom + 5382;
          v8 = *p_bottom;
          p_bottom += 3;
          *v7 = v8;
          v7[1] = v6[1];
          v7[2] = v6[2];
        }
        while ( v3 < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] );
      }

      pItema = 0;
      if ( *(int *)&this->m_btnPar2[10][2]._texName[16] > 0 )
      {
        p_view_radiusY = &this->m_btnPar[9][6].view_radiusY;
        v9 = &this->m_btnPar[6][2]._texName[72];
        do
        {
          *((_DWORD *)v9 + 1794) = *(p_view_radiusY - 1);
          sprintf((char *const)&this->rc.right, byte_5967B0, *p_view_radiusY + 4);
          nValc = ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetItemOffset((char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(*p_view_radiusY + 608) / 2);
          ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(1, nValc, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v9);
          ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, nValc, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v9 + 1794));
          ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(3, nValc, (char *)&this->rc.right, 0);
          if ( *(int *)v9 <= 0 )
          {
            v10 = pItema;
            if ( (int)pItema < 0 || (int)pItema >= SLODWORD(this->m_btnPar2[10][1].m_helix_rx) )
              v11 = 0;
            else
              v11 = *(_DWORD *)&v9[-32452 - (_DWORD)this + LODWORD(this->m_btnPar2[10][1].m_tempy)];
            *(float *)(v11 + 68) = this->m_btnPar2[10][0]._y;
          }
          else
          {
            ((UITabCtrl *)&this->m_btnPar2[10][0]._x)->SetItemParam((int)pItema);
            v10 = pItema;
          }
          v9 += 4;
          p_view_radiusY += 3;
          pItema = v10 + 1;
        }
        while ( (int)(v10 + 1) < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] );
      }
      ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetItem();
      return ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetItem();
    case 1u:
      v12 = &this->m_btnPar2[10][2]._texName[20];
      v86 = (UIListBox *)&this->m_btnPar2[10][2]._texName[20];
      ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(1);
      v25 = 0;
      if ( (int)pItem >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(pItem);
      *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] = 0;
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        do
        {
          v26 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v79, v25);
          v27 = *v26;
          v28 = v26[1];
          v29 = v26[2];
          if ( *v26 != 6409 && v27 != 6410 && v27 != 6411 && v27 != 6412 && v27 != 6413 && v27 != 6408 && v27 != 6427 )
          {
            v30 = &this->m_btnPar[10][5].m_xflag + 3 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
            *v30 = v27;
            v30[1] = v28;
            v30[2] = v29;
// [VFTABLE] v31 = &this->__vftable + 3 * *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
            v32 = v31 + 12605;
            v31 += 17987;
            *v31 = *v32;
            v31[1] = v32[1];
            v31[2] = v32[2];
            ++*(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
          }
          ++v25;
        }
        while ( v25 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }

      pItemc = 0;
      if ( *(int *)&this->m_btnPar2[10][4]._texName[60] > 0 )
      {
        v33 = &this->m_btnPar[6][4]._texName[100];
        nVala = &this->m_btnPar[10][5].m_iscolorfade;
        do
        {
          *((_DWORD *)v33 + 1794) = *((_DWORD *)nVala - 1);
          sprintf((char *const)&this->rc.right, byte_5967B0, *(_DWORD *)nVala + 4);
          v34 = ((UIListBox *)v86)->SetItemOffset((char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(*(_DWORD *)nVala + 608) / 2);
          ((UIListBox *)v86)->SetMouseMoveSel(1, v34, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v33);
          ((UIListBox *)v86)->SetMouseMoveSel(2, v34, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v33 + 1794));
          ((UIListBox *)v86)->SetMouseMoveSel(3, v34, (char *)&this->rc.right, 0);
          if ( *(int *)v33 <= 0 )
          {
            if ( (int)pItemc < 0 || (int)pItemc >= this->m_btnPar2[10][3].m_state )
              v35 = 0;
            else
              v35 = *(_DWORD *)&v33[-33648 - (_DWORD)this + this->m_btnPar2[10][3].m_xflag];
            *(_DWORD *)(v35 + 68) = *(_DWORD *)&this->m_btnPar2[10][2]._texName[24];
          }
          else
          {
            ((UITabCtrl *)v86)->SetItemParam((int)pItemc);
          }
          v33 += 4;
          v24 = (int)++pItemc < *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
          nVala += 12;
        }
        while ( v24 );
        v12 = &this->m_btnPar2[10][2]._texName[20];
      }
      goto LABEL_119;
    case 2u:
      v12 = &this->m_btnPar2[10][4]._texName[64];
      v85 = (UIListBox *)&this->m_btnPar2[10][4]._texName[64];
      ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(2);
      v13 = 0;
      if ( (int)pItem >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(pItem);
      *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] = 0;
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        do
        {
          v14 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v78, v13);
          v15 = *v14;
          v16 = v14[1];
          v17 = v14[2];
          if ( *v14 != 6119
            && v15 != 6120
            && v15 != 6121
            && v15 != 6122
            && v15 != 6123
            && v15 != 6124
            && v15 != 6125
            && v15 != 6427 )
          {
            v18 = &this->m_btnPar[11][4]._texName[12 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] + 20];
            *(_DWORD *)v18 = v15;
            *((_DWORD *)v18 + 1) = v16;
            *((_DWORD *)v18 + 2) = v17;
// [VFTABLE] v19 = &this->__vftable + 3 * *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
            v20 = v19 + 13502;
            v19 += 18884;
            *v19 = *v20;
            v19[1] = v20[1];
            v19[2] = v20[2];
            ++*(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
          }
          ++v13;
        }
        while ( v13 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }

      pItemb = 0;
      if ( *(int *)&this->m_btnPar2[10][6]._texName[104] > 0 )
      {
        v21 = &this->m_btnPar[6][6]._texName[128];
        nVal = &this->m_btnPar[11][4]._texName[28];
        do
        {
          *((_DWORD *)v21 + 1794) = *((_DWORD *)nVal - 1);
          sprintf((char *const)&this->rc.right, byte_5967B0, *(_DWORD *)nVal + 4);
          v22 = ((UIListBox *)v85)->SetItemOffset((char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(*(_DWORD *)nVal + 608) / 2);
          ((UIListBox *)v85)->SetMouseMoveSel(1, v22, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v21);
          ((UIListBox *)v85)->SetMouseMoveSel(2, v22, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v21 + 1794));
          ((UIListBox *)v85)->SetMouseMoveSel(3, v22, (char *)&this->rc.right, 0);
          if ( *(int *)v21 <= 0 )
          {
            if ( (int)pItemb < 0 || (int)pItemb >= SLODWORD(this->m_btnPar2[10][5]._xi) )
              v23 = 0;
            else
              v23 = *(_DWORD *)&v21[-34844 - (_DWORD)this + LODWORD(this->m_btnPar2[10][5]._y)];
            *(_DWORD *)(v23 + 68) = *(_DWORD *)&this->m_btnPar2[10][4]._texName[68];
          }
          else
          {
            ((UITabCtrl *)v85)->SetItemParam((int)pItemb);
          }
          v21 += 4;
          v24 = (int)++pItemb < *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
          nVal += 12;
        }
        while ( v24 );
        v12 = &this->m_btnPar2[10][4]._texName[64];
      }
      goto LABEL_119;
    case 3u:
      ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(3);
      if ( (int)pItem >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(pItem);
      v36 = 0;
      if ( *(int *)&this->m_btnPar2[11][1]._texName[148] > 0 )
      {
        v37 = &this->m_btnPar[12][3]._texName[104];
        do
        {
          v38 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v80, v36++);
          *(_DWORD *)v37 = *v38;
          *((_DWORD *)v37 + 1) = v38[1];
          v39 = v37;
          *((_DWORD *)v37 + 2) = v38[2];
          v40 = v37 + 21528;
          v41 = *(_DWORD *)v37;
          v37 += 12;
          *v40 = v41;
          v40[1] = *((_DWORD *)v39 + 1);
          v40[2] = *((_DWORD *)v39 + 2);
        }
        while ( v36 < *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] );
      }

      pItemd = 0;
      if ( *(int *)&this->m_btnPar2[11][1]._texName[148] > 0 )
      {
        v87 = (UIListBox *)&this->m_btnPar[12][3]._texName[112];
        v42 = &this->m_btnPar[7][1]._texName[156];
        do
        {
          *((_DWORD *)v42 + 1794) = *(_DWORD *)&v87[-1].m_rowenable[12];
// [VFTABLE] sprintf((char *const)&this->rc.right, byte_5967B0, &v87->__vftable->Render);
          nVald = ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetItemOffset((char *)&this->rc.right, 0);
// [VFTABLE] sprintf((char *const)&this->rc.right, &dir[20], (int)v87->__vftable[21].sub_4431B0 / 2);
          ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(1, nVald, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v42);
          ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, nVald, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v42 + 1794));
          ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(3, nVald, (char *)&this->rc.right, 0);
          if ( *(int *)v42 <= 0 )
          {
            v43 = pItemd;
            if ( (int)pItemd < 0 || (int)pItemd >= *(_DWORD *)&this->m_btnPar2[11][0]._texName[28] )
              v44 = 0;
            else
              v44 = *(_DWORD *)&v42[-36040 - (_DWORD)this + *(_DWORD *)&this->m_btnPar2[11][0]._texName[24]];
            *(_DWORD *)(v44 + 68) = *(_DWORD *)&this->m_btnPar2[10][6]._texName[112];
          }
          else
          {
            ((UITabCtrl *)&this->m_btnPar2[10][6]._texName[108])->SetItemParam((int)pItemd);
            v43 = pItemd;
          }
          v42 += 4;
          v87 = (UIListBox *)((char *)v87 + 12);
          pItemd = v43 + 1;
        }
        while ( (int)(v43 + 1) < *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] );
      }
      ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetItem();
      return ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetItem();
    case 4u:
      ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(4);
      if ( (int)pItem >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(pItem);
      v45 = 0;
      if ( *(int *)&this->m_btnPar2[11][3]._texName[192] > 0 )
      {
        v46 = &this->m_btnPar[13][2]._texName[188];
        do
        {
          v47 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v81, v45++);
          *(_DWORD *)v46 = *v47;
          *((_DWORD *)v46 + 1) = v47[1];
          v48 = v46;
          *((_DWORD *)v46 + 2) = v47[2];
          v49 = v46 + 21528;
          v50 = *(_DWORD *)v46;
          v46 += 12;
          *v49 = v50;
          v49[1] = *((_DWORD *)v48 + 1);
          v49[2] = *((_DWORD *)v48 + 2);
        }
        while ( v45 < *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] );
      }

      pIteme = 0;
      if ( *(int *)&this->m_btnPar2[11][3]._texName[192] > 0 )
      {
        v88 = (UIListBox *)&this->m_btnPar[13][2]._texName[196];
        v51 = &this->m_btnPar[7][3]._texName[184];
        do
        {
          *((_DWORD *)v51 + 1794) = *(_DWORD *)&v88[-1].m_rowenable[12];
// [VFTABLE] sprintf((char *const)&this->rc.right, byte_5967B0, &v88->__vftable->Render);
          nVale = ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetItemOffset((char *)&this->rc.right, 0);
// [VFTABLE] sprintf((char *const)&this->rc.right, &dir[20], (int)v88->__vftable[21].sub_4431B0 / 2);
          ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(1, nVale, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v51);
          ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, nVale, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v51 + 1794));
          ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(3, nVale, (char *)&this->rc.right, 0);
          if ( *(int *)v51 <= 0 )
          {
            v52 = pIteme;
            if ( (int)pIteme < 0 || (int)pIteme >= *(_DWORD *)&this->m_btnPar2[11][2]._texName[72] )
              v53 = 0;
            else
              v53 = *(_DWORD *)&v51[-37236 - (_DWORD)this + *(_DWORD *)&this->m_btnPar2[11][2]._texName[68]];
            *(_DWORD *)(v53 + 68) = *(_DWORD *)&this->m_btnPar2[11][1]._texName[156];
          }
          else
          {
            ((UITabCtrl *)&this->m_btnPar2[11][1]._texName[152])->SetItemParam((int)pIteme);
            v52 = pIteme;
          }
          v51 += 4;
          v88 = (UIListBox *)((char *)v88 + 12);
          pIteme = v52 + 1;
        }
        while ( (int)(v52 + 1) < *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] );
      }
      ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetItem();
      return ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetItem();
    case 5u:
      v12 = &this->m_btnPar2[11][3]._texName[196];
      v89 = (UIListBox *)&this->m_btnPar2[11][3]._texName[196];
      ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(6);
      v54 = 0;
      if ( (int)pItem >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(pItem);
      *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] = 0;
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        do
        {
          v55 = (void **)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v82, v54);
          v56 = *v55;
          v57 = v55[1];
          v58 = v55[2];
          if ( *v55 != (void *)8146
            && v56 != (void *)8147
            && v56 != (void *)8149
            && v56 != (void *)8150
            && v56 != (void *)8151
            && v56 != (void *)8152 )
          {
            v59 = &this->m_btnPar[14][1]._element.m_id + 3 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
            *v59 = v56;
            v59[1] = v57;
            v59[2] = v58;
// [VFTABLE] v60 = &this->__vftable + 3 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
            v61 = v60 + 16193;
            v60 += 21575;
            *v60 = *v61;
            v60[1] = v61[1];
            v60[2] = v61[2];
            ++*(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
          }
          ++v54;
        }
        while ( v54 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }

      pItemf = 0;
      if ( *(int *)&this->m_btnPar2[11][5]._texName[236] > 0 )
      {
        v62 = &this->m_btnPar[7][5]._texName[212];
        nValb = &this->m_btnPar[14][1]._element.m_rect.top;
        do
        {
          *((_DWORD *)v62 + 1794) = *(nValb - 1);
          sprintf((char *const)&this->rc.right, byte_5967B0, *nValb + 4);
          v63 = ((UIListBox *)v89)->SetItemOffset((char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(*nValb + 608) / 2);
          ((UIListBox *)v89)->SetMouseMoveSel(1, v63, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v62);
          ((UIListBox *)v89)->SetMouseMoveSel(2, v63, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v62 + 1794));
          ((UIListBox *)v89)->SetMouseMoveSel(3, v63, (char *)&this->rc.right, 0);
          if ( *(int *)v62 <= 0 )
          {
            if ( (int)pItemf < 0 || (int)pItemf >= *(_DWORD *)&this->m_btnPar2[11][4]._texName[116] )
              v64 = 0;
            else
              v64 = *(_DWORD *)&v62[-38432 - (_DWORD)this + *(_DWORD *)&this->m_btnPar2[11][4]._texName[112]];
            *(_DWORD *)(v64 + 68) = *(_DWORD *)&this->m_btnPar2[11][3]._texName[200];
          }
          else
          {
            ((UITabCtrl *)v89)->SetItemParam((int)pItemf);
          }
          v62 += 4;
          v24 = (int)++pItemf < *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
          nValb += 3;
        }
        while ( v24 );
        v12 = &this->m_btnPar2[11][3]._texName[196];
      }
LABEL_119:
      ((UIListBox *)v12)->GetItem();
      result = ((UIListBox *)v12)->GetItem();
      break;
    default:
      return result;
  }
  return result;
}

// 0x00474AB0
void LineupUI::ProcessMouseInput(float fVal)
{
  double v3; // st7
  double v4; // st7
  POINT pt; // [esp+0x10] [ebp-0x8]

  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( PtInRect((const RECT *)&this->m_btnPar2[11][5]._element.m_fontcolor, pt) && (g_Input.KeyInfo[0].Data & 0xF) != 1
    || (((GRPinput *)&g_Input)->GetCursorPos(), PtInRect((const RECT *)&this->m_btnPar2[11][5]._texName[248], pt))
    && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    LOBYTE(this->m_btnPar2[11][6]._element.m_nTextW) = 0;
    BYTE1(this->m_btnPar2[11][6]._element.m_nTextW) = 0;
  }
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( PtInRect((const RECT *)&this->m_btnPar2[11][5]._element.m_fontcolor, pt) && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
  {
    if ( !BYTE1(this->m_btnPar2[11][6]._element.m_nTextW) )
    {
      v3 = fVal + *(float *)&this->m_btnPar2[11][6]._element.m_FVF;
      LOBYTE(this->m_btnPar2[11][6]._element.m_nTextW) = 1;
      BYTE1(this->m_btnPar2[11][6]._element.m_nTextW) = 0;
      *(float *)&this->m_btnPar2[11][6]._element.m_FVF = v3;
      if ( v3 > 0.5 )
        this->OnMessage(1001, 822, 0);
    }
  }
  else
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    if ( PtInRect((const RECT *)&this->m_btnPar2[11][5]._texName[248], pt) && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
    {
      if ( !LOBYTE(this->m_btnPar2[11][6]._element.m_nTextW) )
      {
        v4 = fVal + *(float *)&this->m_btnPar2[11][6]._element.m_FVF;
        LOBYTE(this->m_btnPar2[11][6]._element.m_nTextW) = 0;
        BYTE1(this->m_btnPar2[11][6]._element.m_nTextW) = 1;
        *(float *)&this->m_btnPar2[11][6]._element.m_FVF = v4;
        if ( v4 > 0.5 )
          this->OnMessage(1001, 821, 0);
      }
    }
    else
    {
      this->m_btnPar2[11][6]._element.m_FVF = 0;
    }
  }
}

// 0x00474C50
int LineupUI::UpdateAndForward(int nVal, int nVal2)
{
  sub_474990(this);
  this->ProcessMouseInput(*(float *)&nVal);
  ((UIListBox *)this)->Update(nVal, nVal2);
  return 1;
}

// 0x00474C80
int LineupUI::BuildListItems()
{
  int v2; // ebx
  char *v3; // edi
  char *v4; // ebp
  int v5; // eax
  int v6; // ecx
  char *v7; // ebp
  LONG *v8; // edx
  bool v9; // cc
  int v10; // ebp
  gbColorQuad *v11; // edi
  int v12; // eax
  int v13; // edi
  char *v14; // ebx
  char *v15; // ebp
  int v16; // eax
  char *p_x; // edi
  int v18; // ebx
  int *p_view_radiusY; // edi
  char *v20; // ebp
  int v21; // eax
  int v22; // ecx
  gbColorQuad *p_m_wndcolor; // ebp
  int *v24; // edx
  int v25; // ebp
  float *v26; // edi
  int v27; // eax
  int v28; // edi
  gbColorQuad *v29; // ebx
  int *v30; // ebp
  int v31; // eax
  int v32; // ebx
  char *v33; // edi
  char *v34; // ebp
  int v35; // eax
  int v36; // ecx
  PtrArray *p_m_childs; // ebp
  char *v38; // edx
  int v39; // ebp
  char *v40; // edi
  int v41; // eax
  int v42; // edi
  char *v43; // ebx
  char *v44; // ebp
  int v45; // eax
  int v46; // ebx
  int *p_capacity; // edi
  char *v48; // ebp
  int v49; // eax
  int v50; // ecx
  int *p_m_bfocus; // ebp
  char *v52; // ecx
  int v53; // ebp
  char *v54; // edi
  int v55; // eax
  int v56; // edi
  int *v57; // ebx
  PtrArray *v58; // ebp
  int v59; // eax
  int v60; // ebx
  _PlugInfo **p_m_ppicInfo; // edi
  char *v62; // ebp
  int v63; // eax
  _PlugInfo *v64; // ecx
  Parent_Data **p_m_fonttype; // ebp
  char *v66; // edx
  int v67; // ebp
  char *v68; // edi
  int v69; // eax
  int v70; // edi
  Parent_Data **v71; // ebx
  gbTexture **v72; // ebp
  int v73; // eax
  int v74; // ebp
  char *v75; // ebx
  float *p_m_HelixAngle; // edi
  int v77; // eax
  int v78; // ecx
  gbTexture **v79; // ebp
  void **v80; // edx
  int v81; // ebp
  char *v82; // ebx
  int v83; // edi
  int v84; // eax
  _DWORD *v85; // ebx
  int v86; // eax
  int result; // eax
  int v88; // [esp+0x10] [ebp-0x8]
  int v89; // [esp+0x10] [ebp-0x8]
  int v90; // [esp+0x10] [ebp-0x8]
  int v91; // [esp+0x10] [ebp-0x8]
  int v92; // [esp+0x10] [ebp-0x8]
  int v93; // [esp+0x10] [ebp-0x8]
  gbTexture **v94; // [esp+0x10] [ebp-0x8]
  char *m_text; // [esp+0x14] [ebp-0x4]
  int *p_view_radiusX; // [esp+0x14] [ebp-0x4]
  char *v97; // [esp+0x14] [ebp-0x4]
  PtrArray *v98; // [esp+0x14] [ebp-0x4]
  gbTexture **p_m_ppic; // [esp+0x14] [ebp-0x4]
  void **p_m_bGetBottom; // [esp+0x14] [ebp-0x4]
  int v101; // [esp+0x1C] [ebp+0x4]

  switch ( v101 )
  {
    case 0:
      v2 = 0;
      if ( *(int *)&this->m_btnPar2[10][2]._texName[16] > 0 )
      {
        v3 = &this->m_btnPar[15][0]._element.m_text[4];
        v4 = &this->m_btnPar[6][2]._texName[72];
        do
        {
          if ( *(int *)v4 > 0 )
          {
            ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += this->m_btnPar[9][5]._element.m_nTextW;
            this->m_btnPar[9][5]._element.m_nTextW = 0;
            v5 = *(_DWORD *)v4;
            *((_DWORD *)v3 - 5382) = *(_DWORD *)v4;
            v6 = *(_DWORD *)v3 - v5;
            *(_DWORD *)v3 = v6;
            *((_DWORD *)v4 + 1794) = v6;
            if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(v3 - 21532) == 2 )
              *((_DWORD *)v4 + 14359) = 1;
          }
          ++v2;
          v4 += 4;
          v3 += 12;
        }
        while ( v2 < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] );
      }
      v88 = 0;
      if ( *(int *)&this->m_btnPar2[10][2]._texName[16] > 0 )
      {
        v7 = &this->m_btnPar[8][0]._texName[240];
        m_text = this->m_btnPar[15][0]._element.m_text;
        do
        {
          if ( *((_DWORD *)v7 + 12565) != 1 )
          {
            v8 = &this->m_btnPar[9][6].m_viewRect.bottom + 3 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
            *v8 = *(_DWORD *)m_text;
            v8[1] = *((_DWORD *)m_text + 1);
            v8[2] = *((_DWORD *)m_text + 2);
            *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 72] = 0;
            *(_DWORD *)&this->m_btnPar[8][0]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 240] = *(_DWORD *)v7;
            sprintf(
              (char *const)&this->rc.right,
              &dir[20],
              *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 72]);
            ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v7);
            ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(3, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            ++*(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
          }
          v7 += 4;
          v9 = ++v88 < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16];
          m_text += 12;
        }
        while ( v9 );
      }
      v10 = *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] - 1;
      if ( v10 >= 0 )
      {
        v11 = &this->m_btnPar2[4][1].m_color + v10;
        do
        {
          if ( v11->Color == 1 )
          {
            v11->Color = 0;
            ((UIListBox *)&this->m_btnPar2[10][0]._x)->AdjustScroll(v10);
            v11[-14359].Color = 0;
            v11[-12565].Color = 0;
          }
          --v10;
          --v11;
        }
        while ( v10 >= 0 );
      }
      v12 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
      v13 = 0;
      *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] = v12;
      if ( v12 > 0 )
      {
        v14 = &this->m_btnPar[8][0]._texName[240];
        v15 = this->m_btnPar[15][0]._element.m_text;
        do
        {
          *(_DWORD *)v15 = *((_DWORD *)v15 - 5382);
          *((_DWORD *)v15 + 1) = *((_DWORD *)v15 - 5381);
          *((_DWORD *)v15 + 2) = *((_DWORD *)v15 - 5380);
          *(_DWORD *)v14 = *((_DWORD *)v15 - 5381);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v14 - 1794));
          ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, v13, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v14);
          ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(3, v13, (char *)&this->rc.right, 0);
          if ( v13 < 0 || v13 >= SLODWORD(this->m_btnPar2[10][1].m_helix_rx) )
            v16 = 0;
          else
            v16 = *(_DWORD *)&v14[-39628 - (_DWORD)this + LODWORD(this->m_btnPar2[10][1].m_tempy)];
          ++v13;
          *(float *)(v16 + 68) = this->m_btnPar2[10][0]._y;
          v15 += 12;
          v14 += 4;
        }
        while ( v13 < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] );
      }
      *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] = 0;
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(0);
      sprintf(
        (char *const)&this->rc.right,
        "%s %d",
        (const char *)&g_bSaveFlag,
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
      ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
      p_x = (char *)&this->m_btnPar2[10][0]._x;
      goto LABEL_151;
    case 1:
      v18 = 0;
      if ( *(int *)&this->m_btnPar2[10][4]._texName[60] > 0 )
      {
        p_view_radiusY = &this->m_btnPar[16][0].view_radiusY;
        v20 = &this->m_btnPar[6][4]._texName[100];
        do
        {
          if ( *(int *)v20 > 0 )
          {
            ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += this->m_btnPar[9][5]._sizeX;
            this->m_btnPar[9][5]._sizeX = 0;
            v21 = *(_DWORD *)v20;
            *(p_view_radiusY - 5382) = *(_DWORD *)v20;
            v22 = *p_view_radiusY - v21;
            *p_view_radiusY = v22;
            *((_DWORD *)v20 + 1794) = v22;
            if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(p_view_radiusY - 5383) == 2 )
              *((_DWORD *)v20 + 14359) = 1;
          }
          ++v18;
          v20 += 4;
          p_view_radiusY += 3;
        }
        while ( v18 < *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] );
      }
      v89 = 0;
      if ( *(int *)&this->m_btnPar2[10][4]._texName[60] > 0 )
      {
        p_m_wndcolor = &this->m_btnPar[8][2]._element.m_wndcolor;
        p_view_radiusX = &this->m_btnPar[16][0].view_radiusX;
        do
        {
          if ( !p_m_wndcolor[12565].Color )
          {
            v24 = &this->m_btnPar[10][5].m_xflag + 3 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
            *v24 = *p_view_radiusX;
            v24[1] = p_view_radiusX[1];
            v24[2] = p_view_radiusX[2];
            *(_DWORD *)&this->m_btnPar[6][4]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 100] = 0;
            *(&this->m_btnPar[8][2]._element.m_wndcolor + *(_DWORD *)&this->m_btnPar2[6][5]._texName[216]) = (gbColorQuad)p_m_wndcolor->Color;
            sprintf(
              (char *const)&this->rc.right,
              &dir[20],
              *(_DWORD *)&this->m_btnPar[6][4]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 100]);
            ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(2, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            sprintf((char *const)&this->rc.right, &dir[20], p_m_wndcolor->Color);
            ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(3, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            ++*(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
          }
          ++p_m_wndcolor;
          v9 = ++v89 < *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
          p_view_radiusX += 3;
        }
        while ( v9 );
      }
      v25 = *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] - 1;
      if ( v25 >= 0 )
      {
        v26 = &this->m_btnPar2[4][3]._xg + v25;
        do
        {
          if ( *(_DWORD *)v26 == 1 )
          {
            *v26 = 0.0;
            ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->AdjustScroll(v25);
            *(v26 - 14359) = 0.0;
            *(v26 - 12565) = 0.0;
          }
          --v25;
          --v26;
        }
        while ( v25 >= 0 );
      }
      v27 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
      v28 = 0;
      *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] = v27;
      if ( v27 > 0 )
      {
        v29 = &this->m_btnPar[8][2]._element.m_wndcolor;
        v30 = &this->m_btnPar[16][0].view_radiusX;
        do
        {
          *v30 = *(v30 - 5382);
          v30[1] = *(v30 - 5381);
          v30[2] = *(v30 - 5380);
          v29->Color = *(v30 - 5381);
          sprintf((char *const)&this->rc.right, &dir[20], v29[-1794].Color);
          ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(2, v28, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], v29->Color);
          ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(3, v28, (char *)&this->rc.right, 0);
          if ( v28 < 0 || v28 >= this->m_btnPar2[10][3].m_state )
            v31 = 0;
          else
            v31 = *(unsigned int *)((char *)&v29->Color + this->m_btnPar2[10][3].m_xflag + -40824 - (_DWORD)this);
          ++v28;
          *(_DWORD *)(v31 + 68) = *(_DWORD *)&this->m_btnPar2[10][2]._texName[24];
          v30 += 3;
          ++v29;
        }
        while ( v28 < *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] );
      }
      *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] = 0;
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(1);
      sprintf(
        (char *const)&this->rc.right,
        "%s %d",
        (const char *)&g_bSaveFlag,
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
      ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
      p_x = &this->m_btnPar2[10][2]._texName[20];
      goto LABEL_151;
    case 2:
      v32 = 0;
      if ( *(int *)&this->m_btnPar2[10][6]._texName[104] > 0 )
      {
        v33 = &this->m_btnPar2[0][4]._texName[216];
        v34 = &this->m_btnPar[6][6]._texName[128];
        do
        {
          if ( *(int *)v34 > 0 )
          {
            ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += this->m_btnPar[9][5]._sizeY;
            this->m_btnPar[9][5]._sizeY = 0;
            v35 = *(_DWORD *)v34;
            *((_DWORD *)v33 - 5382) = *(_DWORD *)v34;
            v36 = *(_DWORD *)v33 - v35;
            *(_DWORD *)v33 = v36;
            *((_DWORD *)v34 + 1794) = v36;
            if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(v33 - 21532) == 2 )
              *((_DWORD *)v34 + 14359) = 1;
          }
          ++v32;
          v34 += 4;
          v33 += 12;
        }
        while ( v32 < *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] );
      }
      v90 = 0;
      if ( *(int *)&this->m_btnPar2[10][6]._texName[104] > 0 )
      {
        p_m_childs = &this->m_btnPar[8][4]._element.m_childs;
        v97 = &this->m_btnPar2[0][4]._texName[212];
        do
        {
          if ( !p_m_childs[3141].capacity )
          {
            v38 = &this->m_btnPar[11][4]._texName[12 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 20];
            *(_DWORD *)v38 = *(_DWORD *)v97;
            *((_DWORD *)v38 + 1) = *((_DWORD *)v97 + 1);
            *((_DWORD *)v38 + 2) = *((_DWORD *)v97 + 2);
            *(_DWORD *)&this->m_btnPar[6][6]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 128] = 0;
            *((_DWORD *)&this->m_btnPar[8][4]._element.m_childs.m_pData + *(_DWORD *)&this->m_btnPar2[6][5]._texName[216]) = p_m_childs->m_pData;
            sprintf(
              (char *const)&this->rc.right,
              &dir[20],
              *(_DWORD *)&this->m_btnPar[6][6]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 128]);
            ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(2, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            sprintf((char *const)&this->rc.right, &dir[20], p_m_childs->m_pData);
            ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(3, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            ++*(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
          }
          p_m_childs = (PtrArray *)((char *)p_m_childs + 4);
          v9 = ++v90 < *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
          v97 += 12;
        }
        while ( v9 );
      }
      v39 = *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] - 1;
      if ( v39 >= 0 )
      {
        v40 = &this->m_btnPar2[4][5]._texName[4 * v39 + 20];
        do
        {
          if ( *(_DWORD *)v40 == 1 )
          {
            *(_DWORD *)v40 = 0;
            ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->AdjustScroll(v39);
            *((_DWORD *)v40 - 14359) = 0;
            *((_DWORD *)v40 - 12565) = 0;
          }
          --v39;
          v40 -= 4;
        }
        while ( v39 >= 0 );
      }
      v41 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
      v42 = 0;
      *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] = v41;
      if ( v41 > 0 )
      {
        v43 = &this->m_btnPar[6][6]._texName[128];
        v44 = &this->m_btnPar2[0][4]._texName[212];
        do
        {
          *(_DWORD *)v44 = *((_DWORD *)v44 - 5382);
          *((_DWORD *)v44 + 1) = *((_DWORD *)v44 - 5381);
          *((_DWORD *)v44 + 2) = *((_DWORD *)v44 - 5380);
          *((_DWORD *)v43 + 1794) = *((_DWORD *)v44 - 5381);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v43);
          ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(2, v42, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *((_DWORD *)v43 + 1794));
          ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(3, v42, (char *)&this->rc.right, 0);
          if ( v42 < 0 || v42 >= SLODWORD(this->m_btnPar2[10][5]._xi) )
            v45 = 0;
          else
            v45 = *(_DWORD *)&v43[-34844 - (_DWORD)this + LODWORD(this->m_btnPar2[10][5]._y)];
          ++v42;
          *(_DWORD *)(v45 + 68) = *(_DWORD *)&this->m_btnPar2[10][4]._texName[68];
          v44 += 12;
          v43 += 4;
        }
        while ( v42 < *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] );
      }
      *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] = 0;
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(2);
      sprintf(
        (char *const)&this->rc.right,
        "%s %d",
        (const char *)&g_bSaveFlag,
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
      ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
      p_x = &this->m_btnPar2[10][4]._texName[64];
      goto LABEL_151;
    case 3:
      v46 = 0;
      if ( *(int *)&this->m_btnPar2[11][1]._texName[148] > 0 )
      {
        p_capacity = &this->m_btnPar2[1][3]._element.m_childs.capacity;
        v48 = &this->m_btnPar[7][1]._texName[156];
        do
        {
          if ( *(int *)v48 > 0 )
          {
            ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += LODWORD(this->m_btnPar[9][5]._speed);
            this->m_btnPar[9][5]._speed = 0.0;
            v49 = *(_DWORD *)v48;
            *(p_capacity - 5382) = *(_DWORD *)v48;
            v50 = *p_capacity - v49;
            *p_capacity = v50;
            *((_DWORD *)v48 + 1794) = v50;
            if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(p_capacity - 5383) == 2 )
              *((_DWORD *)v48 + 14359) = 1;
          }
          ++v46;
          v48 += 4;
          p_capacity += 3;
        }
        while ( v46 < *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] );
      }
      v91 = 0;
      if ( *(int *)&this->m_btnPar2[11][1]._texName[148] > 0 )
      {
        p_m_bfocus = &this->m_btnPar[8][6]._element.m_bfocus;
        v98 = &this->m_btnPar2[1][3]._element.m_childs;
        do
        {
          if ( !p_m_bfocus[12565] )
          {
            v52 = &this->m_btnPar[12][3]._texName[12 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 104];
            *(_DWORD *)v52 = v98->m_pData;
            *((_DWORD *)v52 + 1) = v98->capacity;
            *((_DWORD *)v52 + 2) = v98->m_nSize;
            *(_DWORD *)&this->m_btnPar[7][1]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 156] = 0;
            *(&this->m_btnPar[8][6]._element.m_bfocus + *(_DWORD *)&this->m_btnPar2[6][5]._texName[216]) = *p_m_bfocus;
            sprintf(
              (char *const)&this->rc.right,
              &dir[20],
              *(_DWORD *)&this->m_btnPar[7][1]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 156]);
            ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            sprintf((char *const)&this->rc.right, &dir[20], *p_m_bfocus);
            ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(3, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            ++*(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
          }
          ++p_m_bfocus;
          v9 = ++v91 < *(_DWORD *)&this->m_btnPar2[11][1]._texName[148];
          v98 = (PtrArray *)((char *)v98 + 12);
        }
        while ( v9 );
      }
      v53 = *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] - 1;
      if ( v53 >= 0 )
      {
        v54 = &this->m_btnPar2[5][0]._texName[4 * v53 + 48];
        do
        {
          if ( *(_DWORD *)v54 == 1 )
          {
            *(_DWORD *)v54 = 0;
            ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->AdjustScroll(v53);
            *((_DWORD *)v54 - 14359) = 0;
            *((_DWORD *)v54 - 12565) = 0;
          }
          --v53;
          v54 -= 4;
        }
        while ( v53 >= 0 );
      }
      v55 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
      v56 = 0;
      *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] = v55;
      if ( v55 > 0 )
      {
        v57 = &this->m_btnPar[8][6]._element.m_bfocus;
        v58 = &this->m_btnPar2[1][3]._element.m_childs;
        do
        {
          v58->m_pData = (char *)v58[-1346].m_nSize;
          v58->capacity = v58[-1346].m_needscriptdel;
          v58->m_nSize = (int)v58[-1345].m_pData;
          *v57 = v58[-1346].m_needscriptdel;
          sprintf((char *const)&this->rc.right, &dir[20], *(v57 - 1794));
          ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, v56, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *v57);
          ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(3, v56, (char *)&this->rc.right, 0);
          if ( v56 < 0 || v56 >= *(_DWORD *)&this->m_btnPar2[11][0]._texName[28] )
            v59 = 0;
          else
            v59 = *(int *)((char *)v57
                                    + *(_DWORD *)&this->m_btnPar2[11][0]._texName[24]
                                    - (_DWORD)this
                                    - 43216);
          ++v56;
          *(_DWORD *)(v59 + 68) = *(_DWORD *)&this->m_btnPar2[10][6]._texName[112];
          v58 = (PtrArray *)((char *)v58 + 12);
          ++v57;
        }
        while ( v56 < *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] );
      }
      *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] = 0;
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(3);
      sprintf(
        (char *const)&this->rc.right,
        "%s %d",
        (const char *)&g_bSaveFlag,
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
      ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
      p_x = &this->m_btnPar2[10][6]._texName[108];
      goto LABEL_151;
    case 4:
      v60 = 0;
      if ( *(int *)&this->m_btnPar2[11][3]._texName[192] > 0 )
      {
        p_m_ppicInfo = &this->m_btnPar2[2][2]._element.m_ppicInfo;
        v62 = &this->m_btnPar[7][3]._texName[184];
        do
        {
          if ( *(int *)v62 > 0 )
          {
            ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += this->m_btnPar[9][6].m_viewRect.left;
            this->m_btnPar[9][6].m_viewRect.left = 0;
            v63 = *(_DWORD *)v62;
            *(p_m_ppicInfo - 5382) = *(_PlugInfo **)v62;
            v64 = (_PlugInfo *)((char *)*p_m_ppicInfo - v63);
            *p_m_ppicInfo = v64;
            *((_DWORD *)v62 + 1794) = v64;
            if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(p_m_ppicInfo - 5383) == 2 )
              *((_DWORD *)v62 + 14359) = 1;
          }
          ++v60;
          v62 += 4;
          p_m_ppicInfo += 3;
        }
        while ( v60 < *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] );
      }
      v92 = 0;
      if ( *(int *)&this->m_btnPar2[11][3]._texName[192] > 0 )
      {
        p_m_fonttype = &this->m_btnPar[9][1]._element.m_fonttype;
        p_m_ppic = &this->m_btnPar2[2][2]._element.m_ppic;
        do
        {
          if ( !p_m_fonttype[12565] )
          {
            v66 = &this->m_btnPar[13][2]._texName[12 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 188];
            *(_DWORD *)v66 = *p_m_ppic;
            *((_DWORD *)v66 + 1) = p_m_ppic[1];
            *((_DWORD *)v66 + 2) = p_m_ppic[2];
            *(_DWORD *)&this->m_btnPar[7][3]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 184] = 0;
            (&this->m_btnPar[9][1]._element.m_fonttype)[*(_DWORD *)&this->m_btnPar2[6][5]._texName[216]] = *p_m_fonttype;
            sprintf(
              (char *const)&this->rc.right,
              &dir[20],
              *(_DWORD *)&this->m_btnPar[7][3]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 184]);
            ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            sprintf((char *const)&this->rc.right, &dir[20], *p_m_fonttype);
            ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(3, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            ++*(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
          }
          ++p_m_fonttype;
          v9 = ++v92 < *(_DWORD *)&this->m_btnPar2[11][3]._texName[192];
          p_m_ppic += 3;
        }
        while ( v9 );
      }
      v67 = *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] - 1;
      if ( v67 >= 0 )
      {
        v68 = &this->m_btnPar2[5][2]._texName[4 * v67 + 76];
        do
        {
          if ( *(_DWORD *)v68 == 1 )
          {
            *(_DWORD *)v68 = 0;
            ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->AdjustScroll(v67);
            *((_DWORD *)v68 - 14359) = 0;
            *((_DWORD *)v68 - 12565) = 0;
          }
          --v67;
          v68 -= 4;
        }
        while ( v67 >= 0 );
      }
      v69 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
      v70 = 0;
      *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] = v69;
      if ( v69 > 0 )
      {
        v71 = &this->m_btnPar[9][1]._element.m_fonttype;
        v72 = &this->m_btnPar2[2][2]._element.m_ppic;
        do
        {
          *v72 = *(v72 - 5382);
          v72[1] = *(v72 - 5381);
          v72[2] = *(v72 - 5380);
          *v71 = (Parent_Data *)*(v72 - 5381);
          sprintf((char *const)&this->rc.right, &dir[20], *(v71 - 1794));
          ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, v70, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *v71);
          ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(3, v70, (char *)&this->rc.right, 0);
          if ( v70 < 0 || v70 >= *(_DWORD *)&this->m_btnPar2[11][2]._texName[72] )
            v73 = 0;
          else
            v73 = *(int *)((char *)v71 + *(_DWORD *)&this->m_btnPar2[11][2]._texName[68] + -44412 - (_DWORD)this);
          ++v70;
          *(_DWORD *)(v73 + 68) = *(_DWORD *)&this->m_btnPar2[11][1]._texName[156];
          v72 += 3;
          ++v71;
        }
        while ( v70 < *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] );
      }
      *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] = 0;
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(4);
      sprintf(
        (char *const)&this->rc.right,
        "%s %d",
        (const char *)&g_bSaveFlag,
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
      ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
      p_x = &this->m_btnPar2[11][1]._texName[152];
      goto LABEL_151;
    case 5:
      v74 = 0;
      if ( *(int *)&this->m_btnPar2[11][5]._texName[236] > 0 )
      {
        v75 = &this->m_btnPar[7][5]._texName[212];
        p_m_HelixAngle = &this->m_btnPar2[3][2].m_HelixAngle;
        do
        {
          if ( *(int *)v75 > 0 )
          {
            ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += this->m_btnPar[9][6].m_viewRect.top;
            this->m_btnPar[9][6].m_viewRect.top = 0;
            v77 = *(_DWORD *)v75;
            *(p_m_HelixAngle - 5382) = *(float *)v75;
            v78 = *(_DWORD *)p_m_HelixAngle - v77;
            *(_DWORD *)p_m_HelixAngle = v78;
            *((_DWORD *)v75 + 1794) = v78;
            if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(p_m_HelixAngle - 5383) == 2 )
              *((_DWORD *)v75 + 14359) = 1;
            if ( *((_BYTE *)&this->m_btnPar2[6][2]._W + v74 + 3) && *(_DWORD *)v75 == *((_DWORD *)p_m_HelixAngle - 5382) )
            {
              *((_DWORD *)v75 + 14359) = 1;
              *((_BYTE *)&this->m_btnPar2[6][5].m_FlareTime + v74 + 1) = 0;
              *((_BYTE *)&this->m_btnPar2[6][2]._W + v74 + 3) = 0;
            }
          }
          ++v74;
          v75 += 4;
          p_m_HelixAngle += 3;
        }
        while ( v74 < *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] );
      }
      v93 = 0;
      if ( *(int *)&this->m_btnPar2[11][5]._texName[236] > 0 )
      {
        v79 = &this->m_btnPar[9][3]._element.m_ppic;
        p_m_bGetBottom = (void **)&this->m_btnPar2[3][2].m_bGetBottom;
        do
        {
          if ( v79[12565] != (gbTexture *)1 )
          {
            *((_BYTE *)&this->m_btnPar2[6][2]._W + *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 3) = *((_BYTE *)&this->m_btnPar2[6][5].m_FlareTime + v93 + 1);
            v80 = &this->m_btnPar[14][1]._element.m_id + 3 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
            *v80 = *p_m_bGetBottom;
            v80[1] = p_m_bGetBottom[1];
            v80[2] = p_m_bGetBottom[2];
            *(_DWORD *)&this->m_btnPar[7][5]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 212] = 0;
            *((_DWORD *)&this->m_btnPar[9][3]._element.m_ppic + *(_DWORD *)&this->m_btnPar2[6][5]._texName[216]) = *v79;
            sprintf(
              (char *const)&this->rc.right,
              &dir[20],
              *(_DWORD *)&this->m_btnPar[7][5]._texName[4 * *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] + 212]);
            ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(2, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            sprintf((char *const)&this->rc.right, &dir[20], *v79);
            ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(3, *(_DWORD *)&this->m_btnPar2[6][5]._texName[216], (char *)&this->rc.right, 0);
            ++*(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
          }
          ++v79;
          v9 = ++v93 < *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
          p_m_bGetBottom += 3;
        }
        while ( v9 );
      }
      v81 = *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] - 1;
      if ( v81 < 0 )
      {
        v83 = 0;
      }
      else
      {
        v82 = &this->m_btnPar2[5][4]._texName[4 * v81 + 104];
        v83 = 0;
        do
        {
          if ( *(_DWORD *)v82 == 1 )
          {
            *(_DWORD *)v82 = 0;
            ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->AdjustScroll(v81);
            *((_DWORD *)v82 - 14359) = 0;
            *((_DWORD *)v82 - 12565) = 0;
          }
          --v81;
          v82 -= 4;
        }
        while ( v81 >= 0 );
      }
      v84 = *(_DWORD *)&this->m_btnPar2[6][5]._texName[216];
      *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] = v84;
      if ( v84 > 0 )
      {
        v94 = &this->m_btnPar[9][3]._element.m_ppic;
        v85 = &this->m_btnPar2[3][2].m_bGetBottom;
        do
        {
          *((_BYTE *)&this->m_btnPar2[6][5].m_FlareTime + v83 + 1) = *((_BYTE *)&this->m_btnPar2[6][2]._W + v83 + 3);
          *v85 = *(v85 - 5382);
          v85[1] = *(v85 - 5381);
          v85[2] = *(v85 - 5380);
          *v94 = (gbTexture *)*(v85 - 5381);
          sprintf((char *const)&this->rc.right, byte_5967B0, *(v85 - 5380) + 4);
          ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(0, v83, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)(*(v85 - 5380) + 608) / 2);
          ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(1, v83, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(v94 - 1794));
          ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(2, v83, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *v94);
          ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(3, v83, (char *)&this->rc.right, 0);
          if ( v83 < 0 || v83 >= *(_DWORD *)&this->m_btnPar2[11][4]._texName[116] )
            v86 = 0;
          else
            v86 = *(int *)((char *)v94 + *(_DWORD *)&this->m_btnPar2[11][4]._texName[112] - (_DWORD)this - 45608);
          *(_DWORD *)(v86 + 68) = *(_DWORD *)&this->m_btnPar2[11][3]._texName[200];
          ++v83;
          v85 += 3;
          ++v94;
        }
        while ( v83 < *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] );
      }
      *(_DWORD *)&this->m_btnPar2[6][5]._texName[216] = 0;
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(6);
      sprintf(
        (char *const)&this->rc.right,
        "%s %d",
        (const char *)&g_bSaveFlag,
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
      ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
      p_x = &this->m_btnPar2[11][3]._texName[196];
LABEL_151:
      ((UIListBox *)p_x)->GetItem();
      ((UIListBox *)p_x)->GetItem();
      break;
    default:
      break;
  }
  memset(&this->m_btnPar[2][5]._element.m_benable, 0, 0x3810u);
  this->m_TimeMoney.m_bfocus = -1;
  ((UICaption *)&this->m_btnPar2[12][2]._texName[208])->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->m_btnPar2[12][3].m_iscolorfade)->SetEnable((int)g_szSceneUIText, 0);
  this->m_btnPar2[7][4].m_time.oldtick = 0;
  sprintf((char *const)&this->rc.right, "%s %d", g_szCombatFieldName, *(&this->m_btnPar[9][5]._element.m_nTextW + v101));
  ((UICaption *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetEnable((int)&this->rc.right, 0);
  (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
    &this->m_btnPar2[11][5]._element.m_rect.top,
    0);
  result = (**(int ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])(
             &this->m_btnPar2[11][6]._texName[40],
             0);
  LOBYTE(result) = g_bListNeedsRefresh;
  if ( g_bListNeedsRefresh )
    g_bListNeedsRefresh = 0;
  return result;
}

// 0x00475FC0
int LineupUI::RefreshDisplay()
{
  int i; // esi
  int par_radiusY; // eax
  int result; // eax

  for ( i = 0; i < 6; ++i )


  par_radiusY = this->m_btnPar2[12][4].par_radiusY;
  if ( !par_radiusY )
    return ((UIFrameWnd *)this->m_btnPar2[12][4]._W)->OnPaintUpdate();
  result = par_radiusY - 1;
  if ( !result )
    return ((CUtil *)this->m_btnPar2[12][4]._H)->Update(2.0f);
  return result;
}

// 0x00476010
int LineupUI::PopulateList()
{
  int v1; // ebx
  int v3; // edi
  int v4; // eax
  char *p_x; // edi
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // edi
  int v15; // eax
  char *v17; // [esp+0x10] [ebp-0x8]
  gbColorQuad *p_m_wndcolor; // [esp+0x10] [ebp-0x8]
  PtrArray *p_m_childs; // [esp+0x10] [ebp-0x8]
  int *p_m_bfocus; // [esp+0x10] [ebp-0x8]
  Parent_Data **p_m_fonttype; // [esp+0x10] [ebp-0x8]
  gbTexture **p_m_ppic; // [esp+0x10] [ebp-0x8]
  int v23; // [esp+0x14] [ebp-0x4]
  int v24; // [esp+0x14] [ebp-0x4]
  int v25; // [esp+0x14] [ebp-0x4]
  int v26; // [esp+0x14] [ebp-0x4]
  int v27; // [esp+0x14] [ebp-0x4]
  int v28; // [esp+0x14] [ebp-0x4]
  int v29; // [esp+0x1C] [ebp+0x4]

  v1 = v29;
  switch ( v29 )
  {
    case 0:
      v3 = 0;
      if ( *(int *)&this->m_btnPar2[10][2]._texName[16] > 0 )
      {
        v17 = &this->m_btnPar[8][0]._texName[240];
        v23 = -39628 - (_DWORD)this;
        do
        {
          *((_DWORD *)v17 - 1794) = 0;
          sprintf((char *const)&this->rc.right, &dir[20], 0);
          ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, v3, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v17);
          ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(3, v3, (char *)&this->rc.right, 0);
          if ( v3 < 0 || v3 >= SLODWORD(this->m_btnPar2[10][1].m_helix_rx) )
            v4 = 0;
          else
            v4 = *(_DWORD *)&v17[v23 + LODWORD(this->m_btnPar2[10][1].m_tempy)];
          ++v3;
          *(float *)(v4 + 68) = this->m_btnPar2[10][0]._y;
          v17 += 4;
        }
        while ( v3 < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] );
        v1 = v29;
      }
      p_x = (char *)&this->m_btnPar2[10][0]._x;
      goto LABEL_56;
    case 1:
      v6 = 0;
      if ( *(int *)&this->m_btnPar2[10][4]._texName[60] > 0 )
      {
        p_m_wndcolor = &this->m_btnPar[8][2]._element.m_wndcolor;
        v24 = -40824 - (_DWORD)this;
        do
        {
          p_m_wndcolor[-1794].Color = 0;
          sprintf((char *const)&this->rc.right, &dir[20], 0);
          ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(2, v6, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], p_m_wndcolor->Color);
          ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(3, v6, (char *)&this->rc.right, 0);
          if ( v6 < 0 || v6 >= this->m_btnPar2[10][3].m_state )
            v7 = 0;
          else
            v7 = *(unsigned int *)((char *)&p_m_wndcolor->Color + v24 + this->m_btnPar2[10][3].m_xflag);
          ++v6;
          *(_DWORD *)(v7 + 68) = *(_DWORD *)&this->m_btnPar2[10][2]._texName[24];
          ++p_m_wndcolor;
        }
        while ( v6 < *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] );
        v1 = v29;
      }
      p_x = &this->m_btnPar2[10][2]._texName[20];
      goto LABEL_56;
    case 2:
      v8 = 0;
      if ( *(int *)&this->m_btnPar2[10][6]._texName[104] > 0 )
      {
        p_m_childs = &this->m_btnPar[8][4]._element.m_childs;
        v25 = -42020 - (_DWORD)this;
        do
        {
          p_m_childs[-449].m_nSize = 0;
          sprintf((char *const)&this->rc.right, &dir[20], 0);
          ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(2, v8, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], p_m_childs->m_pData);
          ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(3, v8, (char *)&this->rc.right, 0);
          if ( v8 < 0 || v8 >= SLODWORD(this->m_btnPar2[10][5]._xi) )
            v9 = 0;
          else
            v9 = *(int *)((char *)&p_m_childs->m_pData + v25 + LODWORD(this->m_btnPar2[10][5]._y));
          ++v8;
          *(_DWORD *)(v9 + 68) = *(_DWORD *)&this->m_btnPar2[10][4]._texName[68];
          p_m_childs = (PtrArray *)((char *)p_m_childs + 4);
        }
        while ( v8 < *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] );
        v1 = v29;
      }
      p_x = &this->m_btnPar2[10][4]._texName[64];
      goto LABEL_56;
    case 3:
      v10 = 0;
      if ( *(int *)&this->m_btnPar2[11][1]._texName[148] > 0 )
      {
        p_m_bfocus = &this->m_btnPar[8][6]._element.m_bfocus;
        v26 = -43216 - (_DWORD)this;
        do
        {
          *(p_m_bfocus - 1794) = 0;
          sprintf((char *const)&this->rc.right, &dir[20], 0);
          ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, v10, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *p_m_bfocus);
          ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(3, v10, (char *)&this->rc.right, 0);
          if ( v10 < 0 || v10 >= *(_DWORD *)&this->m_btnPar2[11][0]._texName[28] )
            v11 = 0;
          else
            v11 = *(int *)((char *)p_m_bfocus + v26 + *(_DWORD *)&this->m_btnPar2[11][0]._texName[24]);
          *(_DWORD *)(v11 + 68) = *(_DWORD *)&this->m_btnPar2[10][6]._texName[112];
          ++v10;
          ++p_m_bfocus;
        }
        while ( v10 < *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] );
        v1 = v29;
      }
      p_x = &this->m_btnPar2[10][6]._texName[108];
      goto LABEL_56;
    case 4:
      v12 = 0;
      if ( *(int *)&this->m_btnPar2[11][3]._texName[192] > 0 )
      {
        p_m_fonttype = &this->m_btnPar[9][1]._element.m_fonttype;
        v27 = -44412 - (_DWORD)this;
        do
        {
          *(p_m_fonttype - 1794) = 0;
          sprintf((char *const)&this->rc.right, &dir[20], 0);
          ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, v12, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *p_m_fonttype);
          ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(3, v12, (char *)&this->rc.right, 0);
          if ( v12 < 0 || v12 >= *(_DWORD *)&this->m_btnPar2[11][2]._texName[72] )
            v13 = 0;
          else
            v13 = *(int *)((char *)p_m_fonttype + v27 + *(_DWORD *)&this->m_btnPar2[11][2]._texName[68]);
          ++v12;
          *(_DWORD *)(v13 + 68) = *(_DWORD *)&this->m_btnPar2[11][1]._texName[156];
          ++p_m_fonttype;
        }
        while ( v12 < *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] );
        v1 = v29;
      }
      p_x = &this->m_btnPar2[11][1]._texName[152];
      goto LABEL_56;
    case 5:
      v14 = 0;
      if ( *(int *)&this->m_btnPar2[11][5]._texName[236] > 0 )
      {
        p_m_ppic = &this->m_btnPar[9][3]._element.m_ppic;
        v28 = -45608 - (_DWORD)this;
        do
        {
          *(p_m_ppic - 1794) = 0;
          sprintf((char *const)&this->rc.right, &dir[20], 0);
          ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(2, v14, (char *)&this->rc.right, 0);
          sprintf((char *const)&this->rc.right, &dir[20], *p_m_ppic);
          ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(3, v14, (char *)&this->rc.right, 0);
          if ( v14 < 0 || v14 >= *(_DWORD *)&this->m_btnPar2[11][4]._texName[116] )
            v15 = 0;
          else
            v15 = *(int *)((char *)p_m_ppic + v28 + *(_DWORD *)&this->m_btnPar2[11][4]._texName[112]);
          *(_DWORD *)(v15 + 68) = *(_DWORD *)&this->m_btnPar2[11][3]._texName[200];
          ++v14;
          ++p_m_ppic;
        }
        while ( v14 < *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] );
        v1 = v29;
      }
      p_x = &this->m_btnPar2[11][3]._texName[196];
LABEL_56:
      ((UIListBox *)p_x)->GetItem();
      ((UIListBox *)p_x)->GetItem();
      break;
    default:
      break;
  }
  memset(&this->m_btnPar[2][5]._element.m_benable + 598 * v1, 0, 0x958u);
  this->m_TimeMoney.m_bfocus = -1;
  ((UICaption *)&this->m_btnPar2[12][2]._texName[208])->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->m_btnPar2[12][3].m_iscolorfade)->SetEnable((int)g_szSceneUIText, 0);
  this->m_btnPar2[7][4].m_time.oldtick = 0;
  *(&this->m_btnPar[9][5]._element.m_nTextW + v1) = 0;
  sprintf((char *const)&this->rc.right, "%s %d", g_szCombatFieldName, 0);
  ((UICaption *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetEnable((int)&this->rc.right, 0);
  (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
    &this->m_btnPar2[11][5]._element.m_rect.top,
    0);
  return (**(int ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])(
           &this->m_btnPar2[11][6]._texName[40],
           0);
}

// 0x004765D0
int LineupUI::UpdateAllSlots()
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 6; ++i )
    result = this->PopulateList();
  return result;
}

// 0x004765F0
int LineupUI::SetItemDisplay()
{
  int result; // eax
  unsigned int Color; // edi
  unsigned int v4; // ebx
  int v5; // eax
  unsigned int v6; // eax
  int v7; // ecx
  CScreenMode *Instance; // eax
  int m_bfocus; // eax
  int v10; // eax
  int v11; // eax
  char *v12; // ecx
  int *p_W; // edi
  int v14; // ebx
  int v15; // edx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  char *v19; // ecx
  int *p_bNote; // edi
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  char *v26; // ecx
  char *v27; // edi
  int v28; // ebx
  int v29; // edx
  int v30; // eax
  int v31; // eax
  int v32; // eax
  char *v33; // ecx
  char *v34; // edi
  int v35; // ebx
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  char *v40; // ecx
  char *v41; // edi
  int v42; // ebx
  int v43; // edx
  int v44; // eax
  int v45; // eax
  int v46; // eax
  char *v47; // ecx
  UIWnd **p_m_pfather; // edi
  int v49; // ebx
  UIWnd *v50; // eax
  int v51; // eax
  int *p_m_nTextW; // ecx
  int v53; // edx
  int v54; // edi
  _SPropValue *v55; // [esp-0x8] [ebp-0x28]
  gbColorQuad v56; // [esp+0xC] [ebp-0x14] BYREF
  gbColorQuad v57; // [esp+0x10] [ebp-0x10] BYREF
  gbColorQuad v58; // [esp+0x14] [ebp-0xC] BYREF
  gbColorQuad v59; // [esp+0x18] [ebp-0x8] BYREF
  gbColorQuad v60; // [esp+0x1C] [ebp-0x4] BYREF
  gbColorQuad v61; // [esp+0x24] [ebp+0x4] BYREF

  result = this->m_TimeMoney.m_bfocus;
  if ( result >= 0 )
  {
    Color = v61.Color;
    v4 = 299 * v61.Color;
    v5 = 299 * v61.Color + result;
    *(_DWORD *)&this->m_btnPar2[11][5]._texName[244] = *(&this->m_btnPar[9][6].view_radiusX + 3 * v5);
    ++*(_DWORD *)&this->m_btnPar[6][2]._texName[4 * v5 + 72];
    v6 = v4 + this->m_TimeMoney.m_bfocus;
    v7 = *(_DWORD *)&this->m_btnPar[8][0]._texName[4 * v6 + 240];
    if ( *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * v6 + 72] < v7 )
    {
      sub_445E50((int)&this->m_btnPar2[11][5]._element.m_rect.top);
      sub_445E50((int)&this->m_btnPar2[11][6]._texName[40]);
      v55 = (_SPropValue *)off_5B9DF4;
    }
    else
    {
      *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * v6 + 72] = v7;
      sub_445E50((int)&this->m_btnPar2[11][5]._element.m_rect.top);
      sub_445E50((int)&this->m_btnPar2[11][6]._texName[40]);
      v55 = off_5B9DF0;
    }
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v55, 1);
    *(&this->m_btnPar[2][5]._element.m_benable + 2 * v4 + 2 * this->m_TimeMoney.m_bfocus) = *(&this->m_btnPar[9][6].m_viewRect.bottom
                                                                                            + 3 * v4
                                                                                            + 3
                                                                                            * this->m_TimeMoney.m_bfocus);
    *(&this->m_btnPar[2][5]._element.m_bfocus + 2 * this->m_TimeMoney.m_bfocus + 2 * v4) = *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * this->m_TimeMoney.m_bfocus + 72 + 4 * v4];
    LOBYTE(this->m_btnPar2[12][4].par_radiusX) = 1;
    switch ( Color )
    {
      case 0u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * this->m_TimeMoney.m_bfocus + 72]);
        ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[8][0]._texName[4 * this->m_TimeMoney.m_bfocus + 240]);
        ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        m_bfocus = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[6][2]._texName[4 * m_bfocus + 72] <= 0 )
        {
          if ( m_bfocus < 0 || m_bfocus >= SLODWORD(this->m_btnPar2[10][1].m_helix_rx) )
            v10 = 0;
          else
            v10 = *(_DWORD *)(LODWORD(this->m_btnPar2[10][1].m_tempy) + 4 * m_bfocus);
          *(float *)(v10 + 68) = this->m_btnPar2[10][0]._y;
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][0]._x)->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( LOBYTE(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][5]._element.m_nTextW = *(_DWORD *)&this->m_btnPar[6][2]._texName[72]
                                                 * (*(_DWORD *)(this->m_btnPar[9][6].view_radiusY + 608)
                                                  / 2);
          v11 = *(_DWORD *)&this->m_btnPar2[10][2]._texName[16];
          if ( v11 > 1 )
          {
            v12 = &this->m_btnPar[6][2]._texName[76];
            p_W = &this->m_btnPar[9][6]._W;
            v14 = v11 - 1;
            do
            {
              v15 = *p_W;
              v12 += 4;
              p_W += 3;
              --v14;
              this->m_btnPar[9][5]._element.m_nTextW += *((_DWORD *)v12 - 1) * (*(_DWORD *)(v15 + 608) / 2);
            }
            while ( v14 );
          }
        }
        break;
      case 1u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[6][4]._texName[4 * this->m_TimeMoney.m_bfocus + 100]);
        ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(&this->m_btnPar[8][2]._element.m_wndcolor.Color + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v16 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[6][4]._texName[4 * v16 + 100] <= 0 )
        {
          if ( v16 < 0 || v16 >= this->m_btnPar2[10][3].m_state )
            v17 = 0;
          else
            v17 = *(_DWORD *)(this->m_btnPar2[10][3].m_xflag + 4 * v16);
          *(_DWORD *)(v17 + 68) = *(_DWORD *)&this->m_btnPar2[10][2]._texName[24];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][2]._texName[20])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( LOBYTE(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][5]._sizeX = *(_DWORD *)&this->m_btnPar[6][4]._texName[100]
                                      * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[10][5].m_iscolorfade + 608)
                                       / 2);
          v18 = *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
          if ( v18 > 1 )
          {
            v19 = &this->m_btnPar[6][4]._texName[104];
            p_bNote = (int *)&this->m_btnPar[10][5].m_time.bNote;
            v21 = v18 - 1;
            do
            {
              v22 = *p_bNote;
              v19 += 4;
              p_bNote += 3;
              --v21;
              this->m_btnPar[9][5]._sizeX += *((_DWORD *)v19 - 1) * (*(_DWORD *)(v22 + 608) / 2);
            }
            while ( v21 );
          }
        }
        break;
      case 2u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[6][6]._texName[4 * this->m_TimeMoney.m_bfocus + 128]);
        ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *((_DWORD *)&this->m_btnPar[8][4]._element.m_childs.m_pData + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v23 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[6][6]._texName[4 * v23 + 128] <= 0 )
        {
          if ( v23 < 0 || v23 >= SLODWORD(this->m_btnPar2[10][5]._xi) )
            v24 = 0;
          else
            v24 = *(_DWORD *)(LODWORD(this->m_btnPar2[10][5]._y) + 4 * v23);
          *(_DWORD *)(v24 + 68) = *(_DWORD *)&this->m_btnPar2[10][4]._texName[68];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][4]._texName[64])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( LOBYTE(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][5]._sizeY = *(_DWORD *)&this->m_btnPar[6][6]._texName[128]
                                      * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[11][4]._texName[28] + 608)
                                       / 2);
          v25 = *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
          if ( v25 > 1 )
          {
            v26 = &this->m_btnPar[6][6]._texName[132];
            v27 = &this->m_btnPar[11][4]._texName[40];
            v28 = v25 - 1;
            do
            {
              v29 = *(_DWORD *)v27;
              v26 += 4;
              v27 += 12;
              --v28;
              this->m_btnPar[9][5]._sizeY += *((_DWORD *)v26 - 1) * (*(_DWORD *)(v29 + 608) / 2);
            }
            while ( v28 );
          }
        }
        break;
      case 3u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[7][1]._texName[4 * this->m_TimeMoney.m_bfocus + 156]);
        ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(&this->m_btnPar[8][6]._element.m_bfocus + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v30 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[7][1]._texName[4 * v30 + 156] <= 0 )
        {
          if ( v30 < 0 || v30 >= *(_DWORD *)&this->m_btnPar2[11][0]._texName[28] )
            v31 = 0;
          else
            v31 = *(_DWORD *)(*(_DWORD *)&this->m_btnPar2[11][0]._texName[24] + 4 * v30);
          *(_DWORD *)(v31 + 68) = *(_DWORD *)&this->m_btnPar2[10][6]._texName[112];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][6]._texName[108])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( LOBYTE(this->m_btnPar2[12][4].par_radiusX) )
        {
          LODWORD(this->m_btnPar[9][5]._speed) = *(_DWORD *)&this->m_btnPar[7][1]._texName[156]
                                               * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[12][3]._texName[112] + 608)
                                                / 2);
          v32 = *(_DWORD *)&this->m_btnPar2[11][1]._texName[148];
          if ( v32 > 1 )
          {
            v33 = &this->m_btnPar[7][1]._texName[160];
            v34 = &this->m_btnPar[12][3]._texName[124];
            v35 = v32 - 1;
            do
            {
              v36 = *(_DWORD *)v34;
              v33 += 4;
              v34 += 12;
              --v35;
              LODWORD(this->m_btnPar[9][5]._speed) += *((_DWORD *)v33 - 1) * (*(_DWORD *)(v36 + 608) / 2);
            }
            while ( v35 );
          }
        }
        break;
      case 4u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[7][3]._texName[4 * this->m_TimeMoney.m_bfocus + 184]);
        ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          (&this->m_btnPar[9][1]._element.m_fonttype)[this->m_TimeMoney.m_bfocus]);
        ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v37 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[7][3]._texName[4 * v37 + 184] <= 0 )
        {
          if ( v37 < 0 || v37 >= *(_DWORD *)&this->m_btnPar2[11][2]._texName[72] )
            v38 = 0;
          else
            v38 = *(_DWORD *)(*(_DWORD *)&this->m_btnPar2[11][2]._texName[68] + 4 * v37);
          *(_DWORD *)(v38 + 68) = *(_DWORD *)&this->m_btnPar2[11][1]._texName[156];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[11][1]._texName[152])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( LOBYTE(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][6].m_viewRect.left = *(_DWORD *)&this->m_btnPar[7][3]._texName[184]
                                               * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[13][2]._texName[196] + 608)
                                                / 2);
          v39 = *(_DWORD *)&this->m_btnPar2[11][3]._texName[192];
          if ( v39 > 1 )
          {
            v40 = &this->m_btnPar[7][3]._texName[188];
            v41 = &this->m_btnPar[13][2]._texName[208];
            v42 = v39 - 1;
            do
            {
              v43 = *(_DWORD *)v41;
              v40 += 4;
              v41 += 12;
              --v42;
              this->m_btnPar[9][6].m_viewRect.left += *((_DWORD *)v40 - 1) * (*(_DWORD *)(v43 + 608) / 2);
            }
            while ( v42 );
          }
        }
        break;
      case 5u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[7][5]._texName[4 * this->m_TimeMoney.m_bfocus + 212]);
        ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *((_DWORD *)&this->m_btnPar[9][3]._element.m_ppic + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v44 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[7][5]._texName[4 * v44 + 212] <= 0 )
        {
          if ( v44 < 0 || v44 >= *(_DWORD *)&this->m_btnPar2[11][4]._texName[116] )
            v45 = 0;
          else
            v45 = *(_DWORD *)(*(_DWORD *)&this->m_btnPar2[11][4]._texName[112] + 4 * v44);
          *(_DWORD *)(v45 + 68) = *(_DWORD *)&this->m_btnPar2[11][3]._texName[200];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[11][3]._texName[196])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( LOBYTE(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][6].m_viewRect.top = *(_DWORD *)&this->m_btnPar[7][5]._texName[212]
                                              * (*(_DWORD *)(this->m_btnPar[14][1]._element.m_rect.top + 608)
                                               / 2);
          v46 = *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
          if ( v46 > 1 )
          {
            v47 = &this->m_btnPar[7][5]._texName[216];
            p_m_pfather = &this->m_btnPar[14][1]._element.m_pfather;
            v49 = v46 - 1;
            do
            {
              v50 = *p_m_pfather;
              v47 += 4;
              p_m_pfather += 3;
              --v49;
              this->m_btnPar[9][6].m_viewRect.top += *((_DWORD *)v47 - 1) * (v50[8].m_bfocus / 2);
            }
            while ( v49 );
          }
        }
        break;
      default:
        break;
    }
    v51 = 0;
    p_m_nTextW = &this->m_btnPar[9][5]._element.m_nTextW;
    v53 = 6;
    do
    {
      v54 = *p_m_nTextW++;
      v51 += v54;
      --v53;
    }
    while ( v53 );
    sprintf((char *const)&this->rc.right, "%s %d", g_szCombatFieldName, v51);
    ((UICaption *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetEnable((int)&this->rc.right, 0);
    LOBYTE(this->m_btnPar2[12][4].par_radiusX) = 0;
  }
  return result;
}

// 0x00476ED0
int LineupUI::SetItemColors()
{
  int result; // eax
  unsigned int Color; // edi
  unsigned int v4; // ebx
  char *v5; // eax
  CScreenMode *Instance; // eax
  int m_bfocus; // eax
  int v8; // eax
  int v9; // ebx
  char *v10; // ecx
  int *p_W; // edi
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  char *v16; // ecx
  int *p_bNote; // edi
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  char *v23; // ecx
  char *v24; // edi
  int v25; // ebx
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  char *v30; // ecx
  char *v31; // edi
  int v32; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  char *v37; // ecx
  char *v38; // edi
  int v39; // ebx
  int v40; // edx
  int v41; // eax
  int v42; // eax
  int v43; // eax
  char *v44; // ecx
  UIWnd **p_m_pfather; // edi
  int v46; // ebx
  UIWnd *v47; // eax
  int v48; // eax
  int *p_m_nTextW; // ecx
  int v50; // edx
  int v51; // edi
  _SPropValue *v52; // [esp-0x8] [ebp-0x28]
  gbColorQuad v53; // [esp+0xC] [ebp-0x14] BYREF
  gbColorQuad v54; // [esp+0x10] [ebp-0x10] BYREF
  gbColorQuad v55; // [esp+0x14] [ebp-0xC] BYREF
  gbColorQuad v56; // [esp+0x18] [ebp-0x8] BYREF
  gbColorQuad v57; // [esp+0x1C] [ebp-0x4] BYREF
  gbColorQuad v58; // [esp+0x24] [ebp+0x4] BYREF

  result = this->m_TimeMoney.m_bfocus;
  if ( result >= 0 )
  {
    Color = v58.Color;
    v4 = 299 * v58.Color;
    --*(_DWORD *)&this->m_btnPar[6][2]._texName[1196 * v58.Color + 72 + 4 * result];
    v5 = &this->m_btnPar[6][2]._texName[4 * this->m_TimeMoney.m_bfocus + 72 + 4 * v4];
    if ( *(int *)v5 > 0 )
    {
      sub_445E50((int)&this->m_btnPar2[11][5]._element.m_rect.top);
      sub_445E50((int)&this->m_btnPar2[11][6]._texName[40]);
      v52 = (_SPropValue *)off_5B9DF4;
    }
    else
    {
      *(_DWORD *)v5 = 0;
      sub_445E50((int)&this->m_btnPar2[11][5]._element.m_rect.top);
      sub_445E50((int)&this->m_btnPar2[11][6]._texName[40]);
      v52 = off_5B9DF0;
    }
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v52, 1);
    *(&this->m_btnPar[2][5]._element.m_benable + 2 * v4 + 2 * this->m_TimeMoney.m_bfocus) = *(&this->m_btnPar[9][6].m_viewRect.bottom
                                                                                            + 3 * v4
                                                                                            + 3
                                                                                            * this->m_TimeMoney.m_bfocus);
    *(&this->m_btnPar[2][5]._element.m_bfocus + 2 * this->m_TimeMoney.m_bfocus + 2 * v4) = *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * this->m_TimeMoney.m_bfocus + 72 + 4 * v4];
    BYTE1(this->m_btnPar2[12][4].par_radiusX) = 1;
    switch ( Color )
    {
      case 0u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[6][2]._texName[4 * this->m_TimeMoney.m_bfocus + 72]);
        ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[8][0]._texName[4 * this->m_TimeMoney.m_bfocus + 240]);
        ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        m_bfocus = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[6][2]._texName[4 * m_bfocus + 72] <= 0 )
        {
          if ( m_bfocus < 0 || m_bfocus >= SLODWORD(this->m_btnPar2[10][1].m_helix_rx) )
            v8 = 0;
          else
            v8 = *(_DWORD *)(LODWORD(this->m_btnPar2[10][1].m_tempy) + 4 * m_bfocus);
          *(float *)(v8 + 68) = this->m_btnPar2[10][0]._y;
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][0]._x)->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( BYTE1(this->m_btnPar2[12][4].par_radiusX) )
        {
          v9 = 1;
          this->m_btnPar[9][5]._element.m_nTextW = *(_DWORD *)&this->m_btnPar[6][2]._texName[72]
                                                 * (*(_DWORD *)(this->m_btnPar[9][6].view_radiusY + 608)
                                                  / 2);
          if ( *(int *)&this->m_btnPar2[10][2]._texName[16] > 1 )
          {
            v10 = &this->m_btnPar[6][2]._texName[76];
            p_W = &this->m_btnPar[9][6]._W;
            do
            {
              v12 = *p_W;
              v10 += 4;
              p_W += 3;
              ++v9;
              this->m_btnPar[9][5]._element.m_nTextW += *((_DWORD *)v10 - 1) * (*(_DWORD *)(v12 + 608) / 2);
            }
            while ( v9 < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] );
          }
        }
        break;
      case 1u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[6][4]._texName[4 * this->m_TimeMoney.m_bfocus + 100]);
        ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(&this->m_btnPar[8][2]._element.m_wndcolor.Color + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v13 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[6][4]._texName[4 * v13 + 100] <= 0 )
        {
          if ( v13 < 0 || v13 >= this->m_btnPar2[10][3].m_state )
            v14 = 0;
          else
            v14 = *(_DWORD *)(this->m_btnPar2[10][3].m_xflag + 4 * v13);
          *(_DWORD *)(v14 + 68) = *(_DWORD *)&this->m_btnPar2[10][2]._texName[24];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][2]._texName[20])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( BYTE1(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][5]._sizeX = *(_DWORD *)&this->m_btnPar[6][4]._texName[100]
                                      * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[10][5].m_iscolorfade + 608)
                                       / 2);
          v15 = *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
          if ( v15 > 1 )
          {
            v16 = &this->m_btnPar[6][4]._texName[104];
            p_bNote = (int *)&this->m_btnPar[10][5].m_time.bNote;
            v18 = v15 - 1;
            do
            {
              v19 = *p_bNote;
              v16 += 4;
              p_bNote += 3;
              --v18;
              this->m_btnPar[9][5]._sizeX += *((_DWORD *)v16 - 1) * (*(_DWORD *)(v19 + 608) / 2);
            }
            while ( v18 );
          }
        }
        break;
      case 2u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[6][6]._texName[4 * this->m_TimeMoney.m_bfocus + 128]);
        ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *((_DWORD *)&this->m_btnPar[8][4]._element.m_childs.m_pData + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v20 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[6][6]._texName[4 * v20 + 128] <= 0 )
        {
          if ( v20 < 0 || v20 >= SLODWORD(this->m_btnPar2[10][5]._xi) )
            v21 = 0;
          else
            v21 = *(_DWORD *)(LODWORD(this->m_btnPar2[10][5]._y) + 4 * v20);
          *(_DWORD *)(v21 + 68) = *(_DWORD *)&this->m_btnPar2[10][4]._texName[68];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][4]._texName[64])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( BYTE1(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][5]._sizeY = *(_DWORD *)&this->m_btnPar[6][6]._texName[128]
                                      * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[11][4]._texName[28] + 608)
                                       / 2);
          v22 = *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
          if ( v22 > 1 )
          {
            v23 = &this->m_btnPar[6][6]._texName[132];
            v24 = &this->m_btnPar[11][4]._texName[40];
            v25 = v22 - 1;
            do
            {
              v26 = *(_DWORD *)v24;
              v23 += 4;
              v24 += 12;
              --v25;
              this->m_btnPar[9][5]._sizeY += *((_DWORD *)v23 - 1) * (*(_DWORD *)(v26 + 608) / 2);
            }
            while ( v25 );
          }
        }
        break;
      case 3u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[7][1]._texName[4 * this->m_TimeMoney.m_bfocus + 156]);
        ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(&this->m_btnPar[8][6]._element.m_bfocus + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v27 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[7][1]._texName[4 * v27 + 156] <= 0 )
        {
          if ( v27 < 0 || v27 >= *(_DWORD *)&this->m_btnPar2[11][0]._texName[28] )
            v28 = 0;
          else
            v28 = *(_DWORD *)(*(_DWORD *)&this->m_btnPar2[11][0]._texName[24] + 4 * v27);
          *(_DWORD *)(v28 + 68) = *(_DWORD *)&this->m_btnPar2[10][6]._texName[112];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[10][6]._texName[108])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( BYTE1(this->m_btnPar2[12][4].par_radiusX) )
        {
          LODWORD(this->m_btnPar[9][5]._speed) = *(_DWORD *)&this->m_btnPar[7][1]._texName[156]
                                               * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[12][3]._texName[112] + 608)
                                                / 2);
          v29 = *(_DWORD *)&this->m_btnPar2[11][1]._texName[148];
          if ( v29 > 1 )
          {
            v30 = &this->m_btnPar[7][1]._texName[160];
            v31 = &this->m_btnPar[12][3]._texName[124];
            v32 = v29 - 1;
            do
            {
              v33 = *(_DWORD *)v31;
              v30 += 4;
              v31 += 12;
              --v32;
              LODWORD(this->m_btnPar[9][5]._speed) += *((_DWORD *)v30 - 1) * (*(_DWORD *)(v33 + 608) / 2);
            }
            while ( v32 );
          }
        }
        break;
      case 4u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[7][3]._texName[4 * this->m_TimeMoney.m_bfocus + 184]);
        ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          (&this->m_btnPar[9][1]._element.m_fonttype)[this->m_TimeMoney.m_bfocus]);
        ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v34 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[7][3]._texName[4 * v34 + 184] <= 0 )
        {
          if ( v34 < 0 || v34 >= *(_DWORD *)&this->m_btnPar2[11][2]._texName[72] )
            v35 = 0;
          else
            v35 = *(_DWORD *)(*(_DWORD *)&this->m_btnPar2[11][2]._texName[68] + 4 * v34);
          *(_DWORD *)(v35 + 68) = *(_DWORD *)&this->m_btnPar2[11][1]._texName[156];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[11][1]._texName[152])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( BYTE1(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][6].m_viewRect.left = *(_DWORD *)&this->m_btnPar[7][3]._texName[184]
                                               * (*(_DWORD *)(*(_DWORD *)&this->m_btnPar[13][2]._texName[196] + 608)
                                                / 2);
          v36 = *(_DWORD *)&this->m_btnPar2[11][3]._texName[192];
          if ( v36 > 1 )
          {
            v37 = &this->m_btnPar[7][3]._texName[188];
            v38 = &this->m_btnPar[13][2]._texName[208];
            v39 = v36 - 1;
            do
            {
              v40 = *(_DWORD *)v38;
              v37 += 4;
              v38 += 12;
              --v39;
              this->m_btnPar[9][6].m_viewRect.left += *((_DWORD *)v37 - 1) * (*(_DWORD *)(v40 + 608) / 2);
            }
            while ( v39 );
          }
        }
        break;
      case 5u:
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *(_DWORD *)&this->m_btnPar[7][5]._texName[4 * this->m_TimeMoney.m_bfocus + 212]);
        ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(2, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        sprintf(
          (char *const)&this->rc.right,
          &dir[20],
          *((_DWORD *)&this->m_btnPar[9][3]._element.m_ppic + this->m_TimeMoney.m_bfocus));
        ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(3, this->m_TimeMoney.m_bfocus, (char *)&this->rc.right, 0);
        v41 = this->m_TimeMoney.m_bfocus;
        if ( *(int *)&this->m_btnPar[7][5]._texName[4 * v41 + 212] <= 0 )
        {
          if ( v41 < 0 || v41 >= *(_DWORD *)&this->m_btnPar2[11][4]._texName[116] )
            v42 = 0;
          else
            v42 = *(_DWORD *)(*(_DWORD *)&this->m_btnPar2[11][4]._texName[112] + 4 * v41);
          *(_DWORD *)(v42 + 68) = *(_DWORD *)&this->m_btnPar2[11][3]._texName[200];
        }
        else
        {
          ((UITabCtrl *)&this->m_btnPar2[11][3]._texName[196])->SetItemParam(this->m_TimeMoney.m_bfocus);
        }
        if ( BYTE1(this->m_btnPar2[12][4].par_radiusX) )
        {
          this->m_btnPar[9][6].m_viewRect.top = *(_DWORD *)&this->m_btnPar[7][5]._texName[212]
                                              * (*(_DWORD *)(this->m_btnPar[14][1]._element.m_rect.top + 608)
                                               / 2);
          v43 = *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
          if ( v43 > 1 )
          {
            v44 = &this->m_btnPar[7][5]._texName[216];
            p_m_pfather = &this->m_btnPar[14][1]._element.m_pfather;
            v46 = v43 - 1;
            do
            {
              v47 = *p_m_pfather;
              v44 += 4;
              p_m_pfather += 3;
              --v46;
              this->m_btnPar[9][6].m_viewRect.top += *((_DWORD *)v44 - 1) * (v47[8].m_bfocus / 2);
            }
            while ( v46 );
          }
        }
        break;
      default:
        break;
    }
    v48 = 0;
    p_m_nTextW = &this->m_btnPar[9][5]._element.m_nTextW;
    v50 = 6;
    do
    {
      v51 = *p_m_nTextW++;
      v48 += v51;
      --v50;
    }
    while ( v50 );
    sprintf((char *const)&this->rc.right, "%s %d", g_szCombatFieldName, v48);
    ((UICaption *)&this->m_btnPar2[12][3]._element.m_rect.top)->SetEnable((int)&this->rc.right, 0);
    BYTE1(this->m_btnPar2[12][4].par_radiusX) = 0;
  }
  return result;
}

// 0x004777B0
int LineupUI::RefreshDisplayEx()
{
  char *v2; // ebx
  float *p_m_posy; // ebp
  int i; // edi
  int v5; // eax
  int v6; // edi
  char *v7; // ebx
  int v8; // eax
  int v9; // edi
  char *v10; // ebx
  int v11; // eax
  int v12; // edi
  char *v13; // ebx
  int v14; // eax
  int v15; // edi
  char *v16; // ebx
  int result; // eax
  int v18; // edi
  char *v19; // ebx
  int v20; // [esp+0x10] [ebp-0x4]

  memset(&this->m_btnPar[2][5]._element.m_benable, 0, 0x3810u);
  v2 = &this->m_btnPar[6][2]._texName[72];
  memset(&this->m_btnPar[6][2]._texName[72], 0, 0x1C08u);
  memset(&this->m_btnPar2[4][1].m_color, 0, 0x1C08u);
  memset(&this->m_btnPar[9][6].m_viewRect.bottom, 0, 0x5418u);
  memset(this->m_btnPar[15][0]._element.m_text, 0, 0x5418u);
  memset(&this->m_btnPar[9][5]._element.m_nTextW, 0, 0x18u);
  ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->GetItem();
  ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->GetItem();
  ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->GetItem();
  ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->GetItem();
  ((UICaption *)&this->m_btnPar2[12][3].m_iscolorfade)->SetEnable((int)g_szSceneUIText, 0);
  v20 = 6;
  p_m_posy = &this->m_btnPar2[7][6].m_posy;
  do
  {
    sub_445E50((int)p_m_posy);
    p_m_posy += 86;
    --v20;
  }
  while ( v20 );
  sub_445E50((int)&this->m_btnPar2[7][6].m_posy);
  (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
    &this->m_btnPar2[11][5]._element.m_rect.top,
    0);
  (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])(
    &this->m_btnPar2[11][6]._texName[40],
    0);
  for ( i = 0; i < *(_DWORD *)&this->m_btnPar2[10][2]._texName[16]; v2 += 4 )
  {
    sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v2);
    ((UIListBox *)&this->m_btnPar2[10][0]._x)->SetMouseMoveSel(2, i++, (char *)&this->rc.right, 0);
  }
  v5 = *(_DWORD *)&this->m_btnPar2[10][4]._texName[60];
  v6 = 0;
  *(_DWORD *)&this->m_btnPar2[10][2]._texName[16] = 0;
  if ( v5 > 0 )
  {
    v7 = &this->m_btnPar[6][4]._texName[100];
    do
    {
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v7);
      ((UIListBox *)&this->m_btnPar2[10][2]._texName[20])->SetMouseMoveSel(2, v6++, (char *)&this->rc.right, 0);
      v7 += 4;
    }
    while ( v6 < *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] );
  }
  v8 = *(_DWORD *)&this->m_btnPar2[10][6]._texName[104];
  v9 = 0;
  *(_DWORD *)&this->m_btnPar2[10][4]._texName[60] = 0;
  if ( v8 > 0 )
  {
    v10 = &this->m_btnPar[6][6]._texName[128];
    do
    {
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v10);
      ((UIListBox *)&this->m_btnPar2[10][4]._texName[64])->SetMouseMoveSel(2, v9++, (char *)&this->rc.right, 0);
      v10 += 4;
    }
    while ( v9 < *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] );
  }
  v11 = *(_DWORD *)&this->m_btnPar2[11][1]._texName[148];
  v12 = 0;
  *(_DWORD *)&this->m_btnPar2[10][6]._texName[104] = 0;
  if ( v11 > 0 )
  {
    v13 = &this->m_btnPar[7][1]._texName[156];
    do
    {
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v13);
      ((UIListBox *)&this->m_btnPar2[10][6]._texName[108])->SetMouseMoveSel(2, v12++, (char *)&this->rc.right, 0);
      v13 += 4;
    }
    while ( v12 < *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] );
  }
  v14 = *(_DWORD *)&this->m_btnPar2[11][3]._texName[192];
  v15 = 0;
  *(_DWORD *)&this->m_btnPar2[11][1]._texName[148] = 0;
  if ( v14 > 0 )
  {
    v16 = &this->m_btnPar[7][3]._texName[184];
    do
    {
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v16);
      ((UIListBox *)&this->m_btnPar2[11][1]._texName[152])->SetMouseMoveSel(2, v15++, (char *)&this->rc.right, 0);
      v16 += 4;
    }
    while ( v15 < *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] );
  }
  result = *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
  v18 = 0;
  *(_DWORD *)&this->m_btnPar2[11][3]._texName[192] = 0;
  if ( result <= 0 )
  {
    *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] = 0;
  }
  else
  {
    v19 = &this->m_btnPar[7][5]._texName[212];
    do
    {
      sprintf((char *const)&this->rc.right, &dir[20], *(_DWORD *)v19);
      ((UIListBox *)&this->m_btnPar2[11][3]._texName[196])->SetMouseMoveSel(2, v18, (char *)&this->rc.right, 0);
      result = *(_DWORD *)&this->m_btnPar2[11][5]._texName[236];
      ++v18;
      v19 += 4;
    }
    while ( v18 < result );
    *(_DWORD *)&this->m_btnPar2[11][5]._texName[236] = 0;
  }
  return result;
}

// 0x00477BB0
int LineupUI::OnMessage(int msg, int wparam, int lparam)
{
  int v5; // eax
  char *v6; // ebx
  char *v7; // edi
  int v8; // eax
  _BYTE *p_m_mouseoff; // ecx
  UICursor *v10; // ecx
  int result; // eax
  int v12; // edi
  int *v13; // eax
  int par_radiusY; // eax
  int v15; // eax
  CScreenMode *Instance; // eax
  int *v17; // eax
  int v18; // eax
  const char *v19; // ebp
  int v20; // eax
  const char *v21; // ebp
  int *p_m_nTextW; // edi
  int v23; // ebp
  int v24; // ebx
  const char **v25; // eax
  const char *v26; // ebp
  const char **v27; // eax
  const char **v28; // eax
  const char **v29; // eax
  const char **v30; // eax
  const char **v31; // eax
  int v32; // edi
  int *v33; // ebx
  int v34; // edi
  char *v35; // ebx
  int v36; // edi
  unsigned int *p_m_sec; // ebx
  int v38; // edi
  char *v39; // ebx
  int v40; // edi
  char *v41; // ebx
  _PlugInfo *m_disablepicInfo; // edx
  char *v43; // edi
  unsigned int v44; // eax
  unsigned int v45; // ecx
  _PlugInfo *m_ppicInfo; // ebx
  char *v47; // eax
  _PlugInfo *v48; // ecx
  void *left; // edx
  LONG *p_top; // ecx
  _PlugInfo *v51; // edx
  gbTexture *m_disablepic; // ebp
  unsigned int v53; // edx
  char *v54; // eax
  signed int v55; // ecx
  const void *v56; // [esp-0x8] [ebp-0x160]
  int v57; // [esp+0x10] [ebp-0x148]
  const char *v58; // [esp+0x10] [ebp-0x148]
  const char *v59; // [esp+0x14] [ebp-0x144]
  int v60; // [esp+0x28] [ebp-0x130] BYREF
  int v61; // [esp+0x30] [ebp-0x128] BYREF
  int v62; // [esp+0x38] [ebp-0x120] BYREF
  int pOut; // [esp+0x40] [ebp-0x118] BYREF
  int v64; // [esp+0x48] [ebp-0x110] BYREF
  int v65; // [esp+0x50] [ebp-0x108] BYREF
  char Buffer[253]; // [esp+0x58] [ebp-0x100] BYREF
  __int16 v67; // [esp+0x155] [ebp-0x3]
  char v68; // [esp+0x157] [ebp-0x1]

  switch ( msg )
  {
    case 1000:
      if ( !wparam )
        return 1;


      v5 = 0;
      v6 = &this->m_btnPar2[7][1]._texName[160];
      v57 = 0;
      v7 = &this->m_btnPar2[8][3]._texName[4];
      do
      {
        if ( this->m_btnPar2[7][1]._texName[v5 + 252] )
        {
          sub_445FA0(v7 - 180);
          (**((void ( ***)(int, _DWORD))v7 - 45))((int)(v7 - 180), 0);
          sub_445FA0(v7);
          (**(void ( ***)(char *, _DWORD))v7)(v7, 0);
          sub_445FA0(v7 + 180);
          sub_445FA0(v7 + 360);
          (**((void ( ***)(int, _DWORD))v7 + 90))((int)(v7 + 360), 0);
          sub_445FA0(v7 + 540);
          (**((void ( ***)(int, _DWORD))v7 + 135))((int)(v7 + 540), 0);
          v5 = v57;
        }
        ++v5;
        v6 += 16;
        v7 += 900;
        v57 = v5;
      }
      while ( v5 < 5 );
      this->m_TimeMoney.m_bfocus = 0;
      if ( ((UIListBox *)&this->m_btnPar2[10][0]._x)->GetItemData() > 0 )
        this->OnMessage(1007,
          773,
          this->m_TimeMoney.m_bfocus);
      else
        this->m_TimeMoney.m_bfocus = -1;
      if ( !this->m_btnPar2[12][4].par_radiusY )
      {
        (**(void ( ***)(char *, int))&this->m_btnPar2[7][5]._texName[72])(
          &this->m_btnPar2[7][5]._texName[72],
          1);
        ((UICaption *)&this->m_btnPar2[7][5]._texName[72])->SetEnable((int)&this->stp_BarL.m_childs.m_needscriptdel, 0);
        v8 = lstrlenA((LPCSTR)&this->stp_BarL.m_childs.m_needscriptdel);
        p_m_mouseoff = &this->m_btnPar2[6][6]._element.m_mouseoff;
        if ( v8 > 0 )
          (**(void ( ***)(_BYTE *, int))p_m_mouseoff)(p_m_mouseoff, 1);
        else
          (**(void ( ***)(_BYTE *, _DWORD))p_m_mouseoff)(p_m_mouseoff, 0);
      }
      sprintf(
        (char *const)&this->rc.right,
        "%s %d",
        (const char *)&g_bSaveFlag,
        ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
      ((UICaption *)&this->m_btnPar2[12][3]._texName[112])->SetEnable((int)&this->rc.right, 0);
      BYTE1(this->m_btnPar2[11][6]._element.m_nTextW) = 1;
      LOBYTE(this->m_btnPar2[11][6]._element.m_nTextW) = 1;
      ((UICursor *)v10)->IRender();
      return 1;
    case 1001:
      v12 = 0;
      v13 = dword_56B77C;
      while ( wparam != *v13 )
      {
        ++v13;
        ++v12;
        if ( (int)v13 >= (int)&off_56B794 )
        {
          switch ( wparam )
          {
            case 770:

              par_radiusY = this->m_btnPar2[12][4].par_radiusY;
              if ( par_radiusY )
              {
                if ( par_radiusY == 1 )
                  ((CUtil *)this->m_btnPar2[12][4]._H)->Update(2.0f);
              }
              else
              {
                ((UIFrameWnd *)this->m_btnPar2[12][4]._W)->OnPaintUpdate();
              }
              goto LABEL_34;
            case 788:

              v56 = off_5B9DE4;
              goto LABEL_35;
            case 789:

              v15 = this->m_btnPar2[12][4].par_radiusY;
              if ( v15 )
              {
                if ( v15 == 1 )
                {
                  ((UICaption *)&this->m_btnPar2[7][5]._texName[72])->SetEnable((int)g_szSceneUIText, 0);
                  (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)(
                    &this->m_btnPar2[6][6]._element.m_mouseoff,
                    0);
                }
              }
              else
              {
                (**(void ( ***)(char *, int))&this->m_btnPar2[7][5]._texName[72])(
                  &this->m_btnPar2[7][5]._texName[72],
                  1);
                ((UICaption *)&this->m_btnPar2[7][5]._texName[72])->SetEnable((int)&this->stp_State.m_texarray.m_ptex[15], 0);
                (**(void ( ***)(_BYTE *, int))&this->m_btnPar2[6][6]._element.m_mouseoff)(
                  &this->m_btnPar2[6][6]._element.m_mouseoff,
                  1);
              }
              goto LABEL_34;
            case 819:
              LODWORD(this->m_btnPar2[12][1].m_riseY) = 3;

              v56 = off_5B9DE4;
              goto LABEL_35;
            case 820:
              this->m_btnPar2[12][1].m_riseY = 0.0;

LABEL_34:
              v56 = off_5B9DE4;
              goto LABEL_35;
            case 821:

              goto LABEL_31;
            case 822:

LABEL_31:
              ((UICaption *)&this->m_btnPar2[7][5]._texName[72])->SetEnable((int)g_szSceneUIText, 0);
              (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)(
                &this->m_btnPar2[6][6]._element.m_mouseoff,
                0);
              result = 1;
              break;
            default:
              return 1;
          }
          return result;
        }
      }
      sub_445E50((int)(&this->m_btnPar2[7][6].m_posy + 86 * v12));

      ((UICaption *)&this->m_btnPar2[7][5]._texName[72])->SetEnable((int)g_szSceneUIText, 0);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)(
        &this->m_btnPar2[6][6]._element.m_mouseoff,
        0);
      v56 = off_5B9DE4;
LABEL_35:
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v56, 1);
      return 1;
    case 1005:
      (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
        &this->m_btnPar2[11][5]._element.m_rect.top,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])(
        &this->m_btnPar2[11][6]._texName[40],
        0);
      return 1;
    case 1007:
      this->m_TimeMoney.m_bfocus = lparam;
      if ( lparam > -1 )
      {
        ((UICaption *)&this->m_btnPar2[7][5]._texName[72])->SetEnable((int)g_szSceneUIText, 0);
        (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)(
          &this->m_btnPar2[6][6]._element.m_mouseoff,
          0);
        ((TaskBookUI *)this)->SetEntryCaption(*(_DWORD *)&this->m_btnPar2[11][5]._texName[240], this->m_TimeMoney.m_bfocus);
        v17 = (int *)*(&this->m_btnPar[9][6].view_radiusY
                     + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
                     + 3 * this->m_TimeMoney.m_bfocus);
        if ( *((_BYTE *)v17 + 613) == 5 )
        {
          ((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H)->SetFloatParam(228.0);
          ((Camera *)&this->m_btnPar2[7][4]._H)->UpdateCameraLookAt(330, 280, 600);
        }
        else if ( *((_BYTE *)v17 + 612) == 11 )
        {
          ((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H)->SetFloatParam(228.0);
          ((Camera *)&this->m_btnPar2[7][4]._H)->UpdateCameraLookAt(330, 272, 600);
        }
        else
        {
          v18 = *v17;
          if ( v18 == 8114 || v18 == 8132 )
          {
            ((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H)->SetFloatParam(180.0);
            ((Camera *)&this->m_btnPar2[7][4]._H)->UpdateCameraLookAt(330, 252, 600);
          }
          else
          {
            ((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H)->SetFloatParam(180.0);
            ((Camera *)&this->m_btnPar2[7][4]._H)->UpdateCameraLookAt(330, 268, 600);
          }
        }
        if ( !strcmp(
                (const char *)(*(&this->m_btnPar[9][6].view_radiusY
                               + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
                               + 3 * this->m_TimeMoney.m_bfocus)
                             + 36),
                g_szSceneUIText) )
        {
          sprintf((char *const)&this->rc.right, byte_5967B0, "NONE");
        }
        else
        {
          v19 = (const char *)(*(&this->m_btnPar[9][6].view_radiusY
                               + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
                               + 3 * this->m_TimeMoney.m_bfocus)
                             + 36);
          sprintf((char *const)&this->rc.right, "Item\\%s\\%s.pol", v19, v19);
        }
        ((PalScript *)&this->m_btnPar2[7][4].m_time)->LoadModel((const char *)&this->rc.right, 0);
        v20 = *(&this->m_btnPar[9][6].view_radiusY
              + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
              + 3 * this->m_TimeMoney.m_bfocus);
        v21 = (const char *)(v20 + 36);
        v58 = (const char *)(v20 + 66);
        if ( !strcmp((const char *)(v20 + 36), g_szSceneUIText) )
        {
          sprintf((char *const)&this->rc.right, byte_5967B0, "NONE");
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v67 = 0;
          v68 = 0;
          sprintf(Buffer, "%s%s", v21, v58);
          sprintf((char *const)&this->rc.right, "Item\\%s\\%s.tga", v21, Buffer);
        }
        ((gbGeomNode *)this->m_btnPar2[7][4].m_color.Color)->ReplaceTexture((const char *)&this->rc.right);
        this->m_btnPar2[7][4].m_time.oldtick = 1;
        p_m_nTextW = &this->m_btnPar2[8][2]._element.m_nTextW;
        v23 = 5;
        do
        {
          v24 = 5;
          do
          {
            (*(void ( **)(int *, _DWORD))*p_m_nTextW)(p_m_nTextW, 0);
            p_m_nTextW += 45;
            --v24;
          }
          while ( v24 );
          --v23;
        }
        while ( v23 );
        switch ( *(_DWORD *)&this->m_btnPar2[11][5]._texName[240] )
        {
          case 0:
            GetGridOffset(&this->m_btnPar2[10][0]._x, &pOut, this->m_TimeMoney.m_bfocus);
            v26 = *v25;
            v59 = v25[1];
            break;
          case 1:
            GetGridOffset(&this->m_btnPar2[10][2]._texName[20], &v64, this->m_TimeMoney.m_bfocus);
            v26 = *v27;
            v59 = v27[1];
            break;
          case 2:
            GetGridOffset(&this->m_btnPar2[10][4]._texName[64], &v65, this->m_TimeMoney.m_bfocus);
            v26 = *v28;
            v59 = v28[1];
            break;
          case 3:
            GetGridOffset(&this->m_btnPar2[10][6]._texName[108], &v60, this->m_TimeMoney.m_bfocus);
            v26 = *v29;
            v59 = v29[1];
            break;
          case 4:
            GetGridOffset(&this->m_btnPar2[11][1]._texName[152], &v61, this->m_TimeMoney.m_bfocus);
            v26 = *v30;
            v59 = v30[1];
            break;
          case 5:
            GetGridOffset(&this->m_btnPar2[11][3]._texName[196], &v62, this->m_TimeMoney.m_bfocus);
            v26 = *v31;
            v59 = v31[1];
            switch ( *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus) + 612) )
            {
              case 7:
                v32 = 0;
                v33 = &this->m_btnPar2[8][2]._element.m_nTextW;
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v32 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v32
                                + 614) )
                  {
                    (*(void ( **)(int *, int))*v33)(v33, 1);
                  }
                  ++v32;
                  v33 += 225;
                }
                while ( v32 < 5 );
                break;
              case 8:
                v34 = 0;
                v35 = &this->m_btnPar2[8][3]._element.m_text[8];
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v34 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v34
                                + 614) )
                  {
                    (**(void ( ***)(char *, int))v35)(v35, 1);
                  }
                  ++v34;
                  v35 += 900;
                }
                while ( v34 < 5 );
                break;
              case 9:
                v36 = 0;
                p_m_sec = &this->m_btnPar2[8][4].m_sec;
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v36 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v36
                                + 614) )
                  {
                    (*(void ( **)(unsigned int *, int))*p_m_sec)(p_m_sec, 1);
                  }
                  ++v36;
                  p_m_sec += 225;
                }
                while ( v36 < 5 );
                break;
              case 0xA:
                v38 = 0;
                v39 = &this->m_btnPar2[8][3]._texName[184];
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v38 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v38
                                + 614) )
                  {
                    (**(void ( ***)(char *, int))v39)(v39, 1);
                  }
                  ++v38;
                  v39 += 900;
                }
                while ( v38 < 5 );
                break;
              case 0xB:
                v40 = 0;
                v41 = &this->m_btnPar2[8][3]._texName[4];
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v40 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v40
                                + 614) )
                  {
                    (**(void ( ***)(char *, int))v41)(v41, 1);
                  }
                  ++v40;
                  v41 += 900;
                }
                while ( v40 < 5 );
                break;
              default:
                goto LABEL_95;
            }
            break;
          default:
            v26 = v58;
            break;
        }
LABEL_95:
        m_disablepicInfo = this->m_btnPar2[11][6]._element.m_disablepicInfo;
        v43 = &this->m_btnPar2[11][5]._texName[248];
        v44 = (unsigned int)(v59 - 4);
        v45 = (unsigned int)(v26 + 162);
        if ( m_disablepicInfo )
        {
          if ( m_disablepicInfo != (_PlugInfo *)1 )
          {
LABEL_100:
            (*(void ( **)(LONG *, int))this->m_btnPar2[11][5]._element.m_rect.top)(
              &this->m_btnPar2[11][5]._element.m_rect.top,
              1);
            (**(void ( ***)(char *, int))&this->m_btnPar2[11][6]._texName[40])(
              &this->m_btnPar2[11][6]._texName[40],
              1);
            sub_445E50((int)&this->m_btnPar2[11][5]._element.m_rect.top);
            sub_445E50((int)&this->m_btnPar2[11][6]._texName[40]);
            return 1;
          }
          m_ppicInfo = this->m_btnPar2[11][6]._element.m_ppicInfo;
          this->m_btnPar2[11][5]._element.m_wndcolor.Color = v44;
          this->m_btnPar2[11][5]._element.m_fontcolor.Color = v45;
          this->m_btnPar2[11][5]._element.m_id = (char *)m_ppicInfo + v45;
          this->m_btnPar2[11][5]._element.m_rect.left = (LONG)this->m_btnPar2[11][6]._element.m_disablepic + v44;
          sub_445FA0(&this->m_btnPar2[11][6]._texName[40]);
          v47 = (char *)this->m_btnPar2[11][5]._element.m_id + (unsigned int)this->m_btnPar2[11][6]._element.m_pbk2;
          v48 = this->m_btnPar2[11][6]._element.m_ppicInfo;
          *(_DWORD *)&this->m_btnPar2[11][5]._texName[252] = this->m_btnPar2[11][5]._element.m_wndcolor.Color;
          left = (void *)this->m_btnPar2[11][5]._element.m_rect.left;
          *(_DWORD *)v43 = v47;
// [VFTABLE] this->m_btnPar2[11][5]._element.__vftable = left;
          this->m_btnPar2[11][5]._ptex = (gbTexture *)&v47[(_DWORD)v48];
          p_top = &this->m_btnPar2[11][5]._element.m_rect.top;
        }
        else
        {
          v51 = this->m_btnPar2[11][6]._element.m_ppicInfo;
          m_disablepic = this->m_btnPar2[11][6]._element.m_disablepic;
          *(_DWORD *)&this->m_btnPar2[11][5]._texName[252] = v44;
          *(_DWORD *)v43 = v45;
          this->m_btnPar2[11][5]._ptex = (gbTexture *)((char *)v51 + v45);
// [VFTABLE] this->m_btnPar2[11][5]._element.__vftable = (vtbl_0056AE2C *)((char *)m_disablepic + v44);
          sub_445FA0(&this->m_btnPar2[11][5]._element.m_rect.top);
          v53 = *(_DWORD *)v43;
// [VFTABLE] v54 = (char *)this->m_btnPar2[11][5]._element.__vftable + (unsigned int)this->m_btnPar2[11][6]._element.m_pbk2;
          this->m_btnPar2[11][5]._element.m_wndcolor.Color = (unsigned int)v54;
          this->m_btnPar2[11][5]._element.m_fontcolor.Color = v53;
          this->m_btnPar2[11][5]._element.m_id = this->m_btnPar2[11][5]._ptex;
          p_top = (LONG *)&this->m_btnPar2[11][6]._texName[40];
          this->m_btnPar2[11][5]._element.m_rect.left = (LONG)this->m_btnPar2[11][6]._element.m_disablepic
                                                      + (unsigned int)v54;
        }
        sub_445FA0(p_top);
        goto LABEL_100;
      }
      ((UICaption *)&this->m_btnPar2[12][2]._texName[208])->SetEnable((int)g_szSceneUIText, 0);
      this->m_btnPar2[7][4].m_time.oldtick = 0;
      (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
        &this->m_btnPar2[11][5]._element.m_rect.top,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])(
        &this->m_btnPar2[11][6]._texName[40],
        0);
      return 1;
    case 1009:
      if ( wparam == 801 )
      {
        v55 = HIWORD(lparam);
        if ( (unsigned __int16)lparam > *(int *)&this->m_btnPar2[7][5]._texName[224]
          && (unsigned __int16)lparam < *(int *)&this->m_btnPar2[7][5]._texName[232]
          && v55 > *(_DWORD *)&this->m_btnPar2[7][5]._texName[228]
          && v55 < *(_DWORD *)&this->m_btnPar2[7][5]._texName[236] )
        {
          ((UICaption *)&this->m_btnPar2[7][5]._texName[72])->SetEnable((int)g_szSceneUIText, 0);
          (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)(
            &this->m_btnPar2[6][6]._element.m_mouseoff,
            0);
        }
      }
      return 1;
    default:
      return ((PalScript *)this)->OnMessage(msg, wparam, lparam);
  }
}

// 0x0047B0E0
char LineupUI::CountVisibleItems(int nVal)
{
  signed int v3; // esi
  tagRECT *v4; // ebx

  v3 = 0;
  if ( *((int *)&this->pStateUI + 1344) <= 0 )
    return 1;
  v4 = &this->m_DlgEx.m_btRc + 17;
  do
  {
    if ( v4->top <= 0 || v4->left <= 0 )
      ((UIListBox *)(&this->pStateUI + 2436))->SetChildParam(v3, 0);
    else
      ((UIListBox *)(&this->pStateUI + 2436))->SetChildParam(v3, 1);
    ++v3;
    v4 = (tagRECT *)((char *)v4 + 796);
  }
  while ( v3 < *((_DWORD *)&this->pStateUI + 1344) );
  return 1;
}

// 0x0047E5C0
int LineupUI::ctor_E5C0()
{
  this->bkWndX = 800;
  this->bkWndY = 600;
  this->m_IsMsg = 0;
  this->m_Is[0] = 0;
  *(_DWORD *)&this->m_Is[3] = 0;
  sub_4422E0(&this->m_Frame);
  sub_4422E0(&this->m_Frame + 1);
  sub_4422E0(&this->m_TimeMoney.m_FVF);
  sub_4422E0(&this->m_OutFrameT.m_pbk2);
  sub_4422E0(&this->m_OutFrameR.m_disablepic);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->stp_Exit.m_offsetx);
  sub_4422E0(&this->stp_Exit.m_caption[60]);
  sub_4422E0(&this->stp_Effect.m_benable);
  ((UIProgressBar *)&this->m_CtrlPlank[11].m_Name.m_ppic)->ctor();
  ((UIProgressBar *)&this->m_CtrlPlank[11].m_Btn[124])->ctor();
  sub_4422E0(&this->m_CtrlPlank[12].m_Name.m_rect.right);
  sub_4422E0(&this->m_CtrlPlank[12].m_Dw.m_rect.right);
  sub_4422E0(&this->m_CtrlPlank[12].m_Btn[24]);
  sub_4422E0(&this->pStateUI + 29);
  sub_4422E0(&this->pStateUI + 67);
  UIScene::GetSys();
  UIScene::GetSys();
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_text[12] = 0;
  this->m_CtrlPlank[11].m_Name.m_pbk = 0;
  this->m_CtrlPlank[11].m_Name.m_pbkInfo = 0;
  ((MainEquipUI *)this)->ClearState();
  return (int)this;
}

// 0x0047E910
void LineupUI::ctor()
{
  ((StateUI *)this)->ReleaseResource();
  ((UIStatic *)(&this->pStateUI + 587))->_UIStatic();
  ((UIStatic *)(&this->pStateUI + 525))->_UIStatic();
  ((UIStatic *)(&this->pStateUI + 463))->_UIStatic();
  ((UIStatic *)(&this->pStateUI + 401))->_UIStatic();
  ((UIStatic *)(&this->pStateUI + 339))->_UIStatic();
  ((UIStatic *)(&this->pStateUI + 277))->_UIStatic();
  ((UICaption *)(&this->pStateUI + 191))->Destroy2();
  ((UICaption *)(&this->pStateUI + 105))->Destroy2();
  ((UIFrameWnd *)(&this->pStateUI + 67))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->pStateUI + 29))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_CtrlPlank[12].m_Btn[24])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_CtrlPlank[12].m_Dw.m_rect.right)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_CtrlPlank[12].m_Name.m_rect.right)->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)&this->m_CtrlPlank[11].m_Btn[124])->PalScript_Init();
  ((PalScript *)&this->m_CtrlPlank[11].m_Name.m_ppic)->PalScript_Init();
  ((UIFrameWnd *)&this->stp_Effect.m_benable)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->stp_Exit.m_caption[60])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->stp_Exit.m_offsetx)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->stp_System.m_offsetx)->Destroy2();
  ((UICaption *)&this->stp_TaskBook.m_offsetx)->Destroy2();
  ((UICaption *)&this->stp_BattleArray.m_offsetx)->Destroy2();
  ((UICaption *)&this->stp_Prop.m_offsetx)->Destroy2();
  ((UICaption *)&this->stp_Equip.m_offsetx)->Destroy2();
  ((UICaption *)&this->stp_Magic.m_offsetx)->Destroy2();
  ((UICaption *)&this->stp_State.m_offsetx)->Destroy2();
  ((UICaption *)&this->stp_BarL.m_FVF)->Destroy2();
  ((UICaption *)&this->m_OutFrameL.m_ppic)->Destroy2();
  ((UIFrameWnd *)&this->m_OutFrameR.m_disablepic)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameT.m_pbk2)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_TimeMoney.m_FVF)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->m_Frame + 1))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Frame)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0047F880
void LineupUI::RenderEffects()
{
  int i; // edi
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v3);
  if ( this->m_CtrlPlank[11].m_Name.m_text[(unsigned int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + 12] )
  {
    for ( i = 0; i < 16; ++i )
    {
// [IDA_MISID]       if ( ((Concurrency *)((char *)&this->m_GameTime.m_childs + 9344 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + 584 * i))->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)((char *)&this->m_GameTime.m_childs
                                           + 9344 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo
                                           + 584 * i))->Apply();
// [IDA_MISID]       if ( ((Concurrency *)&this->m_btnPar2[1][16 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + 4 + i]._texName[36])->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)&this->m_btnPar2[1][16 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + 4 + i]._texName[36])->Apply();
    }
  }
}

// 0x0047F970
int LineupUI::CleanupAndForwardInput()
{
  __int64 v2; // rax
  int v3; // ebx
  int v4; // ebp
  char *v5; // edi
  int v6; // ebp
  char *v7; // edi
  int v8; // ebp
  UIPushButton *v9; // edi
  int v10; // ebp
  int v11; // edi
  StateUI **v12; // ecx
  int v14; // [esp+0x1C] [ebp-0x14]
  int fVal; // [esp+0x34] [ebp+0x4]
  int a3; // [esp+0x38] [ebp+0x8]

  v2 = (__int64)g_fGameTimer;
  v3 = (int)v2 / 3600;
  v4 = (int)v2 / 60 % 60;
  v14 = (int)v2 % 60;
  if ( (int)v2 / 3600 < 100 )
    sprintf(this->buf, "%02d:%02d:%02d", v3, v4, v14);
  else
    sprintf(this->buf, "%03d:%02d:%02d", v3, v4, v14);
  ((UICaption *)&this->stp_Exit.m_caption[60])->SetEnable((int)this->buf, 0);
  sprintf(this->buf, &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)&this->stp_Effect.m_benable)->SetEnable((int)this->buf, 0);
  ((ArcLocaleRole *)this)->HandleKeyInput();
  ((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetAnimLoop(1);
  if ( ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->CheckAnimOver() )
  {
    ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(0.0);
    *((_BYTE *)&this->pStateUI + 5260) = 1;
  }
  if ( *((_BYTE *)&this->pStateUI + 5260) )
  {
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 105))(&this->pStateUI + 105, 1);
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 191))(&this->pStateUI + 191, 1);
    (*(void ( **)(LONG *, int))this->m_CtrlPlank[12].m_Name.m_rect.right)(
      &this->m_CtrlPlank[12].m_Name.m_rect.right,
      1);
    (*(void ( **)(LONG *, int))this->m_CtrlPlank[12].m_Dw.m_rect.right)(
      &this->m_CtrlPlank[12].m_Dw.m_rect.right,
      1);
    (**(void ( ***)(char *, int))&this->m_CtrlPlank[12].m_Btn[24])(&this->m_CtrlPlank[12].m_Btn[24], 1);
    v5 = &this->m_CtrlPlank[12].m_Btn[176];
    v6 = 5;
    do
    {
      (**(void ( ***)(char *, int))v5)(v5, 1);
      v5 += 152;
      --v6;
    }
    while ( v6 );
    v7 = &this->m_CtrlPlank[13].m_Btn[224];
    v8 = 5;
    do
    {
      (**(void ( ***)(char *, int))v7)(v7, 1);
      v7 += 152;
      --v8;
    }
    while ( v8 );
    v9 = &this->m_ProtectPanel.m_WPXFace + 1;
    v10 = 4;
    do
    {
// [VFTABLE] ((void ( *)(UIPushButton *, int))v9->__vftable->ShowWindow)(v9, 1);
      v9 = (UIPushButton *)((char *)v9 + 152);
      --v10;
    }
    while ( v10 );
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 29))(&this->pStateUI + 29, 1);
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 67))(&this->pStateUI + 67, 1);
    *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[200] = *((int *)&this->pStateUI + *((_DWORD *)&this->pStateUI + 1258) + 651) > 0;
    v11 = *((_DWORD *)&this->pStateUI + 1316);
    *((_BYTE *)&this->pStateUI + 5280) = 1;
    if ( v11 >= 0 )
    {
      if ( *((_BYTE *)&this->pStateUI + 5261) )
      {
        if ( v11 > 1 )
          v11 = 1;
        switch ( *((_DWORD *)&this->pStateUI + 1257) )
        {
          case 0:
            ((Object3D *)this)->LoadActorModel(0);
            goto LABEL_22;
          case 1:
            if ( v11 )
            {
LABEL_22:
              ((Object3D *)this)->LoadActorModel(1);
LABEL_23:
              ((Object3D *)this)->LoadActorModel(2);
LABEL_24:
              ((Object3D *)this)->LoadActorModel(3);
LABEL_25:
              ((Object3D *)this)->LoadActorModel(4);
LABEL_26:
              ((Object3D *)this)->LoadActorModel(5);
            }
            else
            {
              ((Object3D *)this)->LoadActorModel(0);
            }
            break;
          case 2:
            if ( v11 )
              goto LABEL_23;
            ((Object3D *)this)->LoadActorModel(0);
            ((Object3D *)this)->LoadActorModel(1);
            break;
          case 3:
            if ( v11 )
              goto LABEL_24;
            ((Object3D *)this)->LoadActorModel(0);
            ((Object3D *)this)->LoadActorModel(1);
            ((Object3D *)this)->LoadActorModel(2);
            break;
          case 4:
            if ( v11 )
              goto LABEL_25;
            ((Object3D *)this)->LoadActorModel(0);
            ((Object3D *)this)->LoadActorModel(1);
            ((Object3D *)this)->LoadActorModel(2);
            ((Object3D *)this)->LoadActorModel(3);
            break;
          case 5:
            if ( v11 )
              goto LABEL_26;
            ((Object3D *)this)->LoadActorModel(0);
            ((Object3D *)this)->LoadActorModel(1);
            ((Object3D *)this)->LoadActorModel(2);
            ((Object3D *)this)->LoadActorModel(3);
            ((Object3D *)this)->LoadActorModel(4);
            break;
          default:
            break;
        }
        ((StateUI *)this)->ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 1u, *((UIWnd **)&this->pStateUI + 1316));
        *((_BYTE *)&this->pStateUI + 5261) = 0;
      }
      else
      {
        ((Object3D *)this)->LoadActorModel(*((_DWORD *)&this->pStateUI + 1257));
        switch ( *((_DWORD *)&this->pStateUI + 1257) )
        {
          case 0:
            (**((void ( ***)(StateUI **, int))&this->pStateUI + 277))(&this->pStateUI + 277, 1);
            break;
          case 1:
            v12 = &this->pStateUI + 339;
            goto LABEL_45;
          case 2:
            (**((void ( ***)(StateUI **, int))&this->pStateUI + 401))(&this->pStateUI + 401, 1);
            break;
          case 3:
            v12 = &this->pStateUI + 463;
            goto LABEL_45;
          case 4:
            (**((void ( ***)(StateUI **, int))&this->pStateUI + 525))(&this->pStateUI + 525, 1);
            break;
          case 5:
            v12 = &this->pStateUI + 587;
LABEL_45:(*v12)->ShowWindow(1);
break;
          default:
            break;
        }
      }
      *((_DWORD *)&this->pStateUI + 1316) = -1;
    }
    *((_BYTE *)&this->pStateUI + 5260) = 0;
  }
  sub_445E50((int)(&this->pStateUI + 105));
  sub_445E50((int)(&this->pStateUI + 191));
  if ( *((_BYTE *)&this->pStateUI + 5280) )
    ((MainEquipUI *)this)->UpdateFadeAlpha(*(float *)&fVal);
  return ((UIListBox *)this)->Update(fVal, a3);
}

// 0x00480600
int LineupUI::OnMessage(int nVal, char *pszBuf, int nVal2)
{
  int v5; // edi
  int i; // edi
  CScreenMode *Instance; // eax
  char *v8; // esi
  UICursor *v9; // ecx
  int result; // eax
  CScreenMode *v11; // eax
  int v12; // eax
  int v13; // ecx
  bool v14; // sf
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // ecx
  StateUI **v19; // ecx
  int v20; // ecx
  CScreenMode *v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // ecx
  int v25; // eax
  int v26; // eax
  CScreenMode *v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // ecx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // ecx
  int v37; // ecx
  CScreenMode *v38; // eax
  int v39; // eax
  CScreenMode *v40; // eax
  int v41; // eax
  CScreenMode *v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // eax
  char v46; // al
  int v47; // [esp-0xC] [ebp-0x18]
  const void *v48; // [esp-0x8] [ebp-0x14]
  const void *v49; // [esp-0x8] [ebp-0x14]
  int v50; // [esp-0x8] [ebp-0x14]
  int v51; // [esp-0x8] [ebp-0x14]
  const void *v52; // [esp-0x8] [ebp-0x14]
  int v53; // [esp-0x8] [ebp-0x14]
  const void *v54; // [esp-0x8] [ebp-0x14]
  int v55; // [esp-0x8] [ebp-0x14]
  int v56; // [esp-0x8] [ebp-0x14]
  const void *v57; // [esp-0x8] [ebp-0x14]
  const void *v58; // [esp-0x8] [ebp-0x14]
  const void *v59; // [esp-0x8] [ebp-0x14]
  int v60; // [esp-0x4] [ebp-0x10]
  int v61; // [esp-0x4] [ebp-0x10]
  int v62; // [esp-0x4] [ebp-0x10]

  v5 = 3;
  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        this->m_Is[0] = 1;
        for ( i = 0; i < 8; ++i )
          ((StateUI *)this)->AutoScrollParticles(i);

        gfxMgr->fSelfIllum = 1.0;
        ((StateUI *)this)->CategorizeRoles();
        ((MainEquipUI *)this)->SelectWithSound(0);
        v48 = off_5C3ED4;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v48, 1);
        v8 = &this->m_CtrlPlank[11].m_Name.m_text[12];
        g_nSceneState = 1;
        *(_DWORD *)v8 = 0;
        *((_DWORD *)v8 + 1) = 0;
        ((UICursor *)v9)->IRender();
        result = 1;
      }
      else
      {
        ((StateUI *)this)->ReleaseResource();
        *((_DWORD *)&this->pStateUI + 297) = 0;
        *((_BYTE *)&this->pStateUI + 1176) = 0;
        *((_DWORD *)&this->pStateUI + 359) = 0;
        *((_BYTE *)&this->pStateUI + 1424) = 0;
        *((_DWORD *)&this->pStateUI + 421) = 0;
        *((_BYTE *)&this->pStateUI + 1672) = 0;
        *((_DWORD *)&this->pStateUI + 483) = 0;
        *((_BYTE *)&this->pStateUI + 1920) = 0;
        *((_DWORD *)&this->pStateUI + 545) = 0;
        *((_BYTE *)&this->pStateUI + 2168) = 0;
        *((_DWORD *)&this->pStateUI + 607) = 0;
        *((_BYTE *)&this->pStateUI + 2416) = 0;
        ((MainEquipUI *)this)->LoadFromFile(0, 1);
        ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\close.CVD", 0);
        ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(0.0);
        this->m_Is[0] = 0;
        result = 1;
      }
      break;
    case 1001:
      if ( pszBuf > byte_A00110 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00604u:
            if ( *((_DWORD *)&this->pStateUI + 1317) != 2 )
            {
              ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
            }
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_bvisible + 24))(
              this->m_CtrlPlank[11].m_Dw.m_bvisible,
              0);
            ((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetAnimLoop(1);
            v12 = *((_DWORD *)&this->pStateUI + 1260) - 1;
            *((_DWORD *)&this->pStateUI + 1260) = v12;
            if ( v12 )
            {
              v13 = *((_DWORD *)&this->pStateUI + 1257);
              v14 = v12 < 0;
              v15 = *((_DWORD *)&this->pStateUI + 1258);
              if ( v14 )
              {
                if ( v13 != v15 )
                  *((_DWORD *)&this->pStateUI + 1257) = v15;
                v16 = v15 - 1;
                *((_DWORD *)&this->pStateUI + 1258) = v16;
                *((_DWORD *)&this->pStateUI + 1257) = v16;
                if ( v16 < 0 )
                {
                  v17 = v16 + 1;
                  *((_DWORD *)&this->pStateUI + 1260) = 0;
                  *((_DWORD *)&this->pStateUI + 1257) = v17;
                  *((_DWORD *)&this->pStateUI + 1258) = v17;
                  return 1;
                }
                v18 = *((_DWORD *)&this->pStateUI + v16 + 651);
                if ( v18 <= 0 )
                {
                  v19 = &this->pStateUI + 105;
                  goto LABEL_24;
                }
                v20 = v18 - 1;
                *((_DWORD *)&this->pStateUI + 1260) = v20;
                if ( !v20 )
                {
                  *((_DWORD *)&this->pStateUI + 1316) = 1;
                  ((StateUI *)this)->DispatchCmd(v16);
                  *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
                }
                v15 = *((_DWORD *)&this->pStateUI + 1258);
              }
              else if ( v13 != v15 )
              {
                *((_DWORD *)&this->pStateUI + 1257) = v15;
              }
              ((MainEquipUI *)this)->SelectWithSound(v15);
            }
            else
            {
              v50 = *((_DWORD *)&this->pStateUI + 1258);
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              ((StateUI *)this)->DispatchCmd(v50);
              ((MainEquipUI *)this)->SelectWithSound(*((_DWORD *)&this->pStateUI + 1258));
              *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
            }
            ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(2.0);
            ((MainEquipUI *)this)->SetAdornVisible(0);
            v52 = off_5C3ED4;
            v21 = CScreenMode::GetInstance();
            ((CScreenMode *)v21)->AudioSetPosition(v52, 1);
            return 1;
          case 0xA00605u:
            if ( *((_DWORD *)&this->pStateUI + 1317) != 1 )
            {
              ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 1;
            }
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_bvisible + 24))(
              this->m_CtrlPlank[11].m_Dw.m_bvisible,
              0);
            ((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetAnimLoop(1);
            v22 = *((_DWORD *)&this->pStateUI + 1258);
            ++*((_DWORD *)&this->pStateUI + 1260);
            if ( *((int *)&this->pStateUI + v22 + 651) <= 0 )
            {
              v28 = v22 + 1;
              *((_DWORD *)&this->pStateUI + 1258) = v28;
              *((_DWORD *)&this->pStateUI + 1257) = v28;
              if ( v28 < 6 )
              {
                v19 = &this->pStateUI + 191;
LABEL_24:
                sub_445E50((int)v19);
                v60 = *((_DWORD *)&this->pStateUI + 1317);
                v51 = *((_DWORD *)&this->pStateUI + 1258);
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                ((MainEquipUI *)this)->ShowPanelsWithSound(v51, v60);
                return 1;
              }
              else
              {
                v29 = v28 - 1;
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                *((_DWORD *)&this->pStateUI + 1258) = v29;
                *((_DWORD *)&this->pStateUI + 1257) = v29;
                return 1;
              }
            }
            else
            {
              if ( *((_DWORD *)&this->pStateUI + 1257) != v22 )
                *((_DWORD *)&this->pStateUI + 1257) = v22;
              v23 = *((_DWORD *)&this->pStateUI + 1257);
              v24 = *((_DWORD *)&this->pStateUI + 1260);
              if ( v24 < *((_DWORD *)&this->pStateUI + v23 + 651) )
              {
                sub_445E50((int)(&this->pStateUI + 105));
                if ( *((_DWORD *)&this->pStateUI + 1260) == 1 )
                {
                  v53 = *((_DWORD *)&this->pStateUI + 1257);
                  *((_DWORD *)&this->pStateUI + 1316) = 0;
                  ((StateUI *)this)->DispatchCmd(v53);
                }
                else
                {
                  *((_DWORD *)&this->pStateUI + 1316) = -1;
                }
                ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(2.0);
                ((MainEquipUI *)this)->SetAdornVisible(0);
                ((MainEquipUI *)this)->RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257));
                v54 = off_5C3ED4;
                v27 = CScreenMode::GetInstance();
                ((CScreenMode *)v27)->AudioSetPosition(v54, 1);
                return 1;
              }
              else
              {
                v25 = v23 + 1;
                *((_DWORD *)&this->pStateUI + 1257) = v25;
                *((_DWORD *)&this->pStateUI + 1258) = v25;
                if ( v25 < 6 )
                {
                  v61 = *((_DWORD *)&this->pStateUI + 1317);
                  *((_DWORD *)&this->pStateUI + 1260) = 0;
                  ((MainEquipUI *)this)->ShowPanelsWithSound(v25, v61);
                }
                else
                {
                  v26 = v25 - 1;
                  *((_DWORD *)&this->pStateUI + 1257) = v26;
                  *((_DWORD *)&this->pStateUI + 1258) = v26;
                  *((_DWORD *)&this->pStateUI + 1260) = v24 - 1;
                }
                return 1;
              }
            }
          case 0xA00606u:
            v30 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v30 <= 0 )
            {
              if ( v30 )
                goto LABEL_78;
              if ( *((_DWORD *)&this->pStateUI + 1317) != 2 )
              {
                ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
                *((_DWORD *)&this->pStateUI + 1317) = 2;
              }
              (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_bvisible + 24))(
                this->m_CtrlPlank[11].m_Dw.m_bvisible,
                0);
              ((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetAnimLoop(1);
              v31 = *((_DWORD *)&this->pStateUI + 1260) - 1;
              *((_DWORD *)&this->pStateUI + 1260) = v31;
              if ( v31 )
              {
                v32 = *((_DWORD *)&this->pStateUI + 1257);
                v14 = v31 < 0;
                v33 = *((_DWORD *)&this->pStateUI + 1258);
                if ( v14 )
                {
                  if ( v32 != v33 )
                    *((_DWORD *)&this->pStateUI + 1257) = v33;
                  v34 = v33 - 1;
                  *((_DWORD *)&this->pStateUI + 1258) = v34;
                  *((_DWORD *)&this->pStateUI + 1257) = v34;
                  if ( v34 < 0 )
                  {
                    v35 = v34 + 1;
                    *((_DWORD *)&this->pStateUI + 1260) = 0;
                    *((_DWORD *)&this->pStateUI + 1257) = v35;
                    *((_DWORD *)&this->pStateUI + 1258) = v35;
                    goto LABEL_78;
                  }
                  v36 = *((_DWORD *)&this->pStateUI + v34 + 651);
                  if ( v36 <= 0 )
                  {
                    sub_445E50((int)(&this->pStateUI + 105));
                    v62 = *((_DWORD *)&this->pStateUI + 1317);
                    v56 = *((_DWORD *)&this->pStateUI + 1258);
                    *((_DWORD *)&this->pStateUI + 1260) = 0;
                    ((MainEquipUI *)this)->ShowPanelsWithSound(v56, v62);
                    goto LABEL_78;
                  }
                  v37 = v36 - 1;
                  *((_DWORD *)&this->pStateUI + 1260) = v37;
                  if ( !v37 )
                  {
                    *((_DWORD *)&this->pStateUI + 1316) = 1;
                    ((StateUI *)this)->DispatchCmd(v34);
                    *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
                  }
                  v33 = *((_DWORD *)&this->pStateUI + 1258);
                }
                else if ( v32 != v33 )
                {
                  *((_DWORD *)&this->pStateUI + 1257) = v33;
                }
                ((MainEquipUI *)this)->SelectWithSound(v33);
              }
              else
              {
                v55 = *((_DWORD *)&this->pStateUI + 1258);
                *((_DWORD *)&this->pStateUI + 1316) = 1;
                ((StateUI *)this)->DispatchCmd(v55);
                ((MainEquipUI *)this)->SelectWithSound(*((_DWORD *)&this->pStateUI + 1258));
                *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
              }
              ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(2.0);
              ((MainEquipUI *)this)->SetAdornVisible(0);
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1257) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 0;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              v47 = *((_DWORD *)&this->pStateUI + 1257);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              ((StateUI *)this)->ShowPanels(v47, 0, (UIWnd *)1);
              ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(2.0);
              ((MainEquipUI *)this)->SetAdornVisible(0);
              ((MainEquipUI *)this)->RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257));
              *((_BYTE *)&this->pStateUI + 5261) = 1;
            }
            v57 = off_5C3ED4;
            v38 = CScreenMode::GetInstance();
            ((CScreenMode *)v38)->AudioSetPosition(v57, 1);
            goto LABEL_78;
          case 0xA00607u:
            v39 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v39 <= 1 )
            {
              if ( v39 >= 1 )
                goto LABEL_98;
              *((_DWORD *)&this->pStateUI + 1257) = 1;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 1;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 1;
              *((_DWORD *)&this->pStateUI + 1316) = 0;
              ((StateUI *)this)->ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, 0);
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1257) = 1;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 1;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              ((StateUI *)this)->ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, (UIWnd *)1);
            }
            ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(2.0);
            ((MainEquipUI *)this)->SetAdornVisible(0);
            ((MainEquipUI *)this)->RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257));
            *((_BYTE *)&this->pStateUI + 5261) = 1;
            v58 = off_5C3ED4;
            v40 = CScreenMode::GetInstance();
            ((CScreenMode *)v40)->AudioSetPosition(v58, 1);
LABEL_98:
            *((_DWORD *)&this->pStateUI + 359) = 1;
            *((_BYTE *)&this->pStateUI + 1424) = 1;
            return 1;
          case 0xA00608u:
            v41 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v41 <= 2 )
            {
              if ( v41 >= 2 )
                break;
              *((_DWORD *)&this->pStateUI + 1257) = 2;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 2;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 1;
              *((_DWORD *)&this->pStateUI + 1316) = 0;
              ((StateUI *)this)->ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, 0);
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1257) = 2;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 2;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              ((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              ((StateUI *)this)->ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, (UIWnd *)1);
            }
            ((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible)->SetTimeScale(2.0);
            ((MainEquipUI *)this)->SetAdornVisible(0);
            ((MainEquipUI *)this)->RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257));
            *((_BYTE *)&this->pStateUI + 5261) = 1;
            v59 = off_5C3ED4;
            v42 = CScreenMode::GetInstance();
            ((CScreenMode *)v42)->AudioSetPosition(v59, 1);
            break;
          case 0xA00609u:
            v43 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v43 <= 3 )
            {
              if ( v43 < 3 )
              {
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                ((MainEquipUI *)this)->ShowPanelsWithSound(3, 1);
              }
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              ((MainEquipUI *)this)->ShowPanelsWithSound(3, 2);
            }
            goto LABEL_123;
          case 0xA00610u:
            v44 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v44 <= 4 )
            {
              if ( v44 < 4 )
              {
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                ((MainEquipUI *)this)->ShowPanelsWithSound(4, 1);
              }
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              ((MainEquipUI *)this)->ShowPanelsWithSound(4, 2);
            }
            goto LABEL_128;
          case 0xA00611u:
            v45 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v45 >= 5 )
            {
              if ( v45 == 5 )
              {
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                ((MainEquipUI *)this)->ShowPanelsWithSound(5, 2);
              }
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              ((MainEquipUI *)this)->ShowPanelsWithSound(5, 1);
            }
            goto LABEL_133;
          default:
            goto LABEL_134;
        }
LABEL_118:
        *((_DWORD *)&this->pStateUI + 421) = 1;
        *((_BYTE *)&this->pStateUI + 1672) = 1;
        result = 1;
      }
      else
      {
        if ( pszBuf != byte_A00110 )
        {
          switch ( (unsigned int)pszBuf )
          {
            case 0xA00102u:
            case 0xA00103u:
            case 0xA00104u:
            case 0xA00105u:
            case 0xA00106u:
            case 0xA00108u:
            case 0xA00109u:
              break;
            default:
              goto LABEL_134;
          }
        }
        v49 = off_5C3EAC;
        v11 = CScreenMode::GetInstance();
        ((CScreenMode *)v11)->AudioSetPosition(v49, 1);
        ((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3])->HandleMessage();
        result = 1;
      }
      break;
    case 1002:
      if ( pszBuf > &byte_A00606 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00607u:
            *((_DWORD *)&this->pStateUI + 359) = 1;
            *((_BYTE *)&this->pStateUI + 1424) = 1;
            return 1;
          case 0xA00608u:
            goto LABEL_118;
          case 0xA00609u:
LABEL_123:
            *((_DWORD *)&this->pStateUI + 483) = 1;
            *((_BYTE *)&this->pStateUI + 1920) = 1;
            return 1;
          case 0xA00610u:
LABEL_128:
            *((_DWORD *)&this->pStateUI + 545) = 1;
            *((_BYTE *)&this->pStateUI + 2168) = 1;
            return 1;
          case 0xA00611u:
LABEL_133:
            *((_DWORD *)&this->pStateUI + 607) = 1;
            *((_BYTE *)&this->pStateUI + 2416) = 1;
            goto LABEL_134;
          default:
LABEL_134:
            result = 1;
            break;
        }
      }
      else if ( pszBuf == &byte_A00606 )
      {
LABEL_78:
        *((_DWORD *)&this->pStateUI + 297) = 1;
        *((_BYTE *)&this->pStateUI + 1176) = 1;
        result = 1;
      }
      else
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00102u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = 0;
            if ( this->m_CtrlPlank[11].m_Name.m_text[12] )
              goto LABEL_134;
            ((StateUI *)this)->AutoScrollParticles(0);
            return 1;
          case 0xA00103u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)1;
            if ( this->m_CtrlPlank[11].m_Name.m_text[13] )
              goto LABEL_134;
            ((StateUI *)this)->AutoScrollParticles(1);
            return 1;
          case 0xA00104u:
            v5 = 2;
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)2;
            v46 = this->m_CtrlPlank[11].m_Name.m_text[14];
            goto LABEL_144;
          case 0xA00105u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)3;
            v46 = this->m_CtrlPlank[11].m_Name.m_text[15];
LABEL_144:
            if ( v46 )
              goto LABEL_134;
            ((StateUI *)this)->AutoScrollParticles(v5);
            result = 1;
            break;
          case 0xA00106u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)5;
            if ( BYTE1(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_134;
            ((StateUI *)this)->AutoScrollParticles(5);
            return 1;
          case 0xA00107u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)6;
            if ( BYTE2(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_134;
            ((StateUI *)this)->AutoScrollParticles(6);
            return 1;
          case 0xA00108u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)4;
            if ( LOBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_134;
            ((StateUI *)this)->AutoScrollParticles(4);
            return 1;
          case 0xA00109u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)7;
            if ( HIBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_134;
            ((StateUI *)this)->AutoScrollParticles(7);
            return 1;
          default:
            goto LABEL_134;
        }
      }
      break;
    case 1003:
      if ( pszBuf > &byte_A00606 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00607u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 1 )
              goto LABEL_180;
            *((_DWORD *)&this->pStateUI + 359) = 0;
            *((_BYTE *)&this->pStateUI + 1424) = 0;
            result = 1;
            break;
          case 0xA00608u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 2 )
              goto LABEL_180;
            *((_DWORD *)&this->pStateUI + 421) = 0;
            *((_BYTE *)&this->pStateUI + 1672) = 0;
            result = 1;
            break;
          case 0xA00609u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 3 )
              goto LABEL_180;
            *((_DWORD *)&this->pStateUI + 483) = 0;
            *((_BYTE *)&this->pStateUI + 1920) = 0;
            result = 1;
            break;
          case 0xA00610u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 4 )
              goto LABEL_180;
            *((_DWORD *)&this->pStateUI + 545) = 0;
            *((_BYTE *)&this->pStateUI + 2168) = 0;
            result = 1;
            break;
          case 0xA00611u:
            if ( *((_DWORD *)&this->pStateUI + 1258) != 5 )
            {
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
            }
            goto LABEL_180;
          default:
            goto LABEL_180;
        }
      }
      else if ( pszBuf == &byte_A00606 )
      {
        if ( *((_DWORD *)&this->pStateUI + 1258) )
        {
          *((_DWORD *)&this->pStateUI + 297) = 0;
          *((_BYTE *)&this->pStateUI + 1176) = 0;
          result = 1;
        }
        else
        {
LABEL_180:
          result = 1;
        }
      }
      else
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00102u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = 0;
            this->m_CtrlPlank[11].m_Name.m_text[12] = 0;
            result = 1;
            break;
          case 0xA00103u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)1;
            this->m_CtrlPlank[11].m_Name.m_text[13] = 0;
            result = 1;
            break;
          case 0xA00104u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)2;
            this->m_CtrlPlank[11].m_Name.m_text[14] = 0;
            result = 1;
            break;
          case 0xA00105u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)3;
            this->m_CtrlPlank[11].m_Name.m_text[15] = 0;
            result = 1;
            break;
          case 0xA00106u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)5;
            BYTE1(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          case 0xA00107u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)6;
            BYTE2(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          case 0xA00108u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)4;
            LOBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          case 0xA00109u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)7;
            HIBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          default:
            goto LABEL_180;
        }
      }
      break;
    default:
      result = ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
      break;
  }
  return result;
}

// 0x004826A0
int LineupUI::RebuildSystemPage()
{
  int m_FVF; // eax
  int *p_m_FVF; // edi
  gbTexture *m_pbk2; // edx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  LONG v9; // edx
  LONG v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  unsigned int v14; // edx
  int v15; // edx
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  gbTexture *v22; // edx
  int m_offsetx; // edx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int v29; // edx
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v35; // ecx
  int v36; // eax
  _DWORD v38[2]; // [esp+A4h] [ebp-0x20] BYREF
  int v39; // [esp+ACh] [ebp-0x18]
  int v40; // [esp+B0h] [ebp-0x14]
  _DWORD v41[4]; // [esp+B4h] [ebp-0x10] BYREF

  m_FVF = this->m_TimeMoney.m_FVF;
  p_m_FVF = &this->m_TimeMoney.m_FVF;
  v38[1] = 543;
  v38[0] = 0;
  v39 = 256;
  v40 = 600;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_FVF + 16))(
    &this->m_TimeMoney.m_FVF,
    161,
    v38,
    this);
  ((UIStatic *)p_m_FVF)->CreateFromTemplate();
  m_pbk2 = this->m_OutFrameT.m_pbk2;
  v38[0] = v39;
  v39 += 512;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2 + 4))(
    &this->m_OutFrameT.m_pbk2,
    161,
    v38,
    this);
  ((UIStatic *)&this->m_OutFrameT.m_pbk2)->CreateFromTemplate();
  v38[0] = v39;
  v39 += 32;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))&this->m_OutFrameR.*((_DWORD *)m_disablepic) + 4))(
    &this->m_OutFrameR.m_disablepic,
    161,
    v38,
    this);
  ((UIStatic *)&this->m_OutFrameR.m_disablepic)->CreateFromTemplate();
  *(_DWORD *)&this->stp_Exit.m_caption[48] = 546;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = 38;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = 148;
  *(_DWORD *)&this->stp_Exit.m_caption[56] = *(_DWORD *)&this->stp_Exit.m_caption[48] + 50;
  LOBYTE(v5) = g_bDebugMode;
  ((void ( *)(gbTexture **, char *, char *, LineupUI *, char *, int, int))this->m_OutFrameL.m_ppic->Height)(
    &this->m_OutFrameL.m_ppic,
    &byte_A00102,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v5);
  this->m_CtrlPlank[11].m_Up.m_pbk2 = (gbTexture *)(*(_DWORD *)&this->stp_Exit.m_caption[48] + 5);
  this->m_CtrlPlank[11].m_Up.m_disablepicInfo = (_PlugInfo *)(*(_DWORD *)&this->stp_Exit.m_caption[44] + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Up.m_mouseoff = *(_DWORD *)&this->stp_Exit.m_caption[52] - 36;
  this->m_CtrlPlank[11].m_Up.m_FVF = *(_DWORD *)&this->stp_Exit.m_caption[56] - 5;
  v6 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v6;
  v6 += 110;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v6;
  LOBYTE(v6) = g_bDebugMode;
  (*(void ( **)(char *, char *, LineupUI *, char *, int, int))(this->stp_Magic.m_offsetx + 28))(
    &byte_A00105,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v6);
  this->m_CtrlPlank[11].m_Name.m_pfather = (UIWnd *)(*(_DWORD *)&this->stp_Exit.m_caption[48] + 5);
  this->m_CtrlPlank[11].m_Name.m_rect.bottom = *(_DWORD *)&this->stp_Exit.m_caption[44] + 35;
  this->m_CtrlPlank[11].m_Name.m_childs.m_pData = (char *)(*(_DWORD *)&this->stp_Exit.m_caption[52] - 36);
  this->m_CtrlPlank[11].m_Name.m_childs.capacity = *(_DWORD *)&this->stp_Exit.m_caption[56] - 5;
  v7 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v7;
  v7 += 110;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v7;
  LOBYTE(v7) = g_bDebugMode;
  (*(void ( **)(char *, char *, LineupUI *, char *, int, int))(this->stp_State.m_offsetx + 28))(
    &byte_A00104,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v7);
  this->m_CtrlPlank[11].m_Name.m_rect.left = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  this->m_CtrlPlank[11].m_Name.m_id = (void *)(*(_DWORD *)&this->stp_Exit.m_caption[44] + 35);
  v8 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  v9 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v10 = v8 - 36;
  v8 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v8;
  v9 -= 5;
  this->m_CtrlPlank[11].m_Name.m_rect.top = v10;
  this->m_CtrlPlank[11].m_Name.m_rect.right = v9;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v8 + 110;
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(int *, char *, char *, LineupUI *, char *, int, LONG))(this->stp_BarL.m_FVF + 28))(
    &this->stp_BarL.m_FVF,
    &byte_A00103,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v9);
  v11 = *(_DWORD *)&this->stp_Exit.m_caption[44];
// [VFTABLE] this->m_CtrlPlank[11].m_Name.__vftable = (vtbl_0056AE2C *)(*(_DWORD *)&this->stp_Exit.m_caption[48] + 5);
  v12 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  this->m_CtrlPlank[11].m_Up.m_nTextW = v11 + 35;
  v13 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v14 = v12 - 36;
  v12 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v12;
  v12 += 110;
  this->m_CtrlPlank[11].m_Name.m_fontcolor.Color = v14;
  this->m_CtrlPlank[11].m_Name.m_wndcolor.Color = v13 - 5;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v12;
  LOBYTE(v12) = g_bDebugMode;
  (*(void ( **)(int *, char *, char *, LineupUI *, char *, int, int))(this->stp_BattleArray.m_offsetx
                                                                                         + 28))(
    &this->stp_BattleArray.m_offsetx,
    &byte_A00108,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v12);
  v15 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  v16 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  this->m_CtrlPlank[11].m_Name.m_childs.m_needscriptdel = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  v17 = v16 - 36;
  this->m_CtrlPlank[11].m_Name.m_childs.m_nSize = v15 + 35;
  v18 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v16 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v16;
  v18 -= 5;
  this->m_CtrlPlank[11].m_Name.m_bcreateok = v17;
  this->m_CtrlPlank[11].m_Name.m_bvisible = v18;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v16 + 110;
  LOBYTE(v18) = g_bDebugMode;
  (*(void ( **)(int *, char *, char *, LineupUI *, char *, int, int))(this->stp_Equip.m_offsetx + 28))(
    &this->stp_Equip.m_offsetx,
    &byte_A00106,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v18);
  v19 = *(_DWORD *)&this->stp_Exit.m_caption[44] + 35;
  this->m_CtrlPlank[11].m_Name.m_bfocus = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  v20 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  this->m_CtrlPlank[11].m_Name.m_benable = v19;
  v21 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v22 = (gbTexture *)(v20 - 36);
  v20 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v20;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v20 + 110;
  v41[0] = *(_DWORD *)&this->stp_Exit.m_caption[44] - 38;
  v41[1] = 546;
  v41[2] = v41[0] + 256;
  this->m_CtrlPlank[11].m_Name.pDebugTex = v22;
  m_offsetx = this->stp_Exit.m_offsetx;
  this->m_CtrlPlank[11].m_Name.m_align = v21 - 5;
  v41[3] = 610;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_offsetx + 16))(
    &this->stp_Exit.m_offsetx,
    161,
    v41,
    this);
  ((UIStatic *)&this->stp_Exit.m_offsetx)->CreateFromTemplate();
  LOBYTE(v24) = g_bDebugMode;
  (*(void ( **)(int *, char *, char *, LineupUI *, char *, int, int))(this->stp_Prop.m_offsetx + 28))(
    &this->stp_Prop.m_offsetx,
    &byte_A00107,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v24);
  v25 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  v26 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  LODWORD(this->m_CtrlPlank[11].m_Name.m_ratioh) = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  v27 = *(_DWORD *)&this->stp_Exit.m_caption[56] - 5;
  LODWORD(this->m_CtrlPlank[11].m_Name.m_ratiow) = v25 + 35;
  this->m_CtrlPlank[11].m_Name.m_textx = v26 - 36;
  v28 = this->stp_System.m_offsetx;
  this->m_CtrlPlank[11].m_Name.m_texty = v27;
  LOBYTE(v27) = g_bDebugMode;
  (*(void ( **)(int *, char *, char *, LineupUI *, char *, int, int))(v28 + 28))(
    &this->stp_System.m_offsetx,
    byte_A00110,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v27);
  v29 = this->stp_TaskBook.m_offsetx;
  v30 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v30;
  v30 += 110;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v30;
  LOBYTE(v30) = g_bDebugMode;
  (*(void ( **)(int *, char *, char *, LineupUI *, char *, int, int))(v29 + 28))(
    &this->stp_TaskBook.m_offsetx,
    byte_A00109,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v30);
  v31 = *(_DWORD *)&this->stp_Exit.m_caption[48];
  v32 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 36;
  this->m_CtrlPlank[11].m_Name.m_fonttype = (Parent_Data *)(*(_DWORD *)&this->stp_Exit.m_caption[44] + 35);
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_text[4] = v32;
  bkWndX = this->bkWndX;
  *(_DWORD *)this->m_CtrlPlank[11].m_Name.m_text = v31 + 5;
  v35 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  bkWndX -= 38;
  *(_DWORD *)&this->stp_Exit.m_caption[48] = bkWndY - 51;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = bkWndX;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = bkWndX + 38;
  v36 = *(_DWORD *)&this->stp_Exit.m_caption[48];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_text[8] = v35 - 5;
  *(_DWORD *)&this->stp_Exit.m_caption[56] = v36 + 48;
  return sub_445FA0(&this->stp_System.m_offsetx);
}

// 0x00482BB0
int LineupUI::ShowPage()
{
  int *p_m_offsetx; // ecx

  if ( g_bRoleFlag1 )
  {
    p_m_offsetx = &this->stp_Equip.m_offsetx;
  }
  else
  {
    ((PalScript *)&this->stp_Equip.m_offsetx)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    p_m_offsetx = &this->stp_Equip.m_offsetx;
  }
  sub_445E50((int)p_m_offsetx);
  if ( g_bRoleFlag2 )
    ((PalScript *)&this->stp_Prop.m_offsetx)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnJusticeBook.tga", g_bDebugMode);
  else
    ((PalScript *)&this->stp_Prop.m_offsetx)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_Prop.m_offsetx);
  sub_445E50((int)&this->m_OutFrameL.m_ppic);
  sub_445E50((int)&this->stp_BarL.m_FVF);
  sub_445E50((int)&this->stp_State.m_offsetx);
  sub_445E50((int)&this->stp_Magic.m_offsetx);
  sub_445E50((int)&this->stp_BattleArray.m_offsetx);
  sub_445E50((int)&this->stp_TaskBook.m_offsetx);
  return sub_445E50((int)&this->stp_System.m_offsetx);
}

// 0x00482ED0
int LineupUI::Save()
{
  StateUI **v2; // edi
  int v4; // [esp+0x10] [ebp-0x14]

  this->bkWndX = 800;
  this->bkWndY = 600;
  this->m_IsMsg = 0;
  sub_4422E0(&this->m_Frame);
  sub_4422E0(&this->m_Frame + 1);
  sub_4422E0(&this->m_TimeMoney.m_FVF);
  sub_4422E0(&this->m_OutFrameT.m_pbk2);
  sub_4422E0(&this->m_OutFrameR.m_disablepic);
  sub_4422E0(&this->m_OutFrameL.m_ppic);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->stp_Exit.m_caption[44]);
  sub_4422E0(&this->stp_Effect.m_benable);
  sub_4422E0(&this->m_GameTime.m_childs);
  sub_4422E0(&this->m_GameMoney.m_rect.bottom);
  memset(&this->m_CtrlPlank[11].m_Btn[120], 0, 0x1Cu);
  *(_WORD *)&this->m_CtrlPlank[11].m_Btn[148] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[150] = 117901063;
  this->m_CtrlPlank[11].m_Btn[154] = 7;
  sub_4422E0(&this->m_CtrlPlank[11].m_Btn[172]);
  *((_DWORD *)&this->pStateUI + 175) = 0;
  ((ARC_PlayerAtt *)(&this->pStateUI + 176))->Refresh();
  v2 = &this->pStateUI + 526;
  v4 = 6;
  do
  {
    v2 += 3;
    --v4;
  }
  while ( v4 );
  ((ObjectCamera *)(&this->pStateUI + 544))->Update();
  *((_DWORD *)&this->pStateUI + 3438) = 0;
  this->m_Is[4] = 0;
  this->m_Is[3] = 0;
  this->m_Is[1] = 0;
  this->m_Is[0] = 0;
  this->m_Is[2] = 0;
  memset(&this->m_CtrlPlank[11].m_Btn[120], 0, 0x1Cu);
  *(_WORD *)&this->m_CtrlPlank[11].m_Btn[148] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[150] = 0;
  this->m_CtrlPlank[11].m_Btn[154] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[108] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[112] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[116] = 0;
  *((_DWORD *)&this->pStateUI + 518) = -1038614528;
  *((_DWORD *)&this->pStateUI + 519) = 1072064102;
  *((_DWORD *)&this->pStateUI + 521) = 1094713344;
  *((_DWORD *)&this->pStateUI + 520) = 0;
  return (int)this;
}

// 0x00483650
void * LineupUI::CreatePreviewScene(int nVal)
{
  tagRECT *p_rc; // edi
  int v4; // eax
  int v5; // edx
  int m_FVF; // edx
  char *m_pData; // eax
  int m_benable; // edx
  int v9; // edx
  int v10; // edx
  StateUI **v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  StateUI **v16; // ebp
  UIStatic *v17; // edi
  int v18; // ebx
  int v19; // ecx
  int v20; // ebx
  UIStatic *v21; // edi
  gbTexture **p_pDebugTex; // ebp
  int i; // edi
  LONG bottom; // eax
  ObjectCamera *v25; // eax
  float *v26; // eax
  float *v27; // ebp
  char *v28; // edi
  double v29; // st7
  bool v30; // cc
  Object3D *v31; // edi
  int v32; // ebx
  int v33; // edx
  int v34; // eax
  int v35; // ecx
  int v36; // edx
  gbVec3D v38; // [esp+0x6C] [ebp-A4h]
  int v39; // [esp+0x8C] [ebp-0x84]
  char *pszName; // [esp+0x90] [ebp-0x80]
  char *pszNamea; // [esp+0x90] [ebp-0x80]
  float v42; // [esp+0x98] [ebp-0x78]
  float v43; // [esp+0x98] [ebp-0x78]
  float v44; // [esp+0x98] [ebp-0x78]
  float v45; // [esp+0x98] [ebp-0x78]
  float v46; // [esp+0x98] [ebp-0x78]
  float v47; // [esp+0x98] [ebp-0x78]
  int v48; // [esp+C4h] [ebp-0x4C] BYREF
  int v49; // [esp+C8h] [ebp-0x48]
  int v50; // [esp+CCh] [ebp-0x44]
  int v51; // [esp+D0h] [ebp-0x40]
  int v52; // [esp+D4h] [ebp-0x3C] BYREF
  int v53; // [esp+D8h] [ebp-0x38]
  int v54; // [esp+DCh] [ebp-0x34]
  int v55; // [esp+E0h] [ebp-0x30]
  _DWORD v56[4]; // [esp+E4h] [ebp-0x2C] BYREF
  int v57[4]; // [esp+F4h] [ebp-0x1C] BYREF
  int v58; // [esp+0x10C] [ebp-0x4]

  p_rc = &this->rc;
  this->rc.top = 0;
  this->rc.left = 0;
  this->rc.right = this->bkWndX;
  this->rc.bottom = this->bkWndY;
  ((UIListBox *)this)->SetSelTexture(-1, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom, 0);
  v4 = this->rc.top + 18;
  v52 = p_rc->left + 631;
  v53 = v4;
  v54 = v52 + 153;
  v55 = v4 + 526;
// [VFTABLE] ((void ( *)(UIStatic *, char *, int *, LineupUI *))this->m_Frame.__vftable->Create)(
// [VFTABLE]   &this->m_Frame,
// [VFTABLE]   &byte_1234567,
// [VFTABLE]   &v52,
// [VFTABLE]   this);
  ((UIStatic *)&this->m_Frame)->CreateFromTemplate();
  v5 = *((_DWORD *)&this->m_Frame + 38);
  v53 += 26;
  v52 = v54;
  v55 = v53 + 526;
  v54 += 17;
  (*(void ( **)(UIStatic *, int, int *, LineupUI *))(v5 + 16))(&this->m_Frame + 1, 161, &v52, this);
  ((UIStatic *)&this->m_Frame + 1)->CreateFromTemplate();
  v49 = 0;
  v48 = v54 - 205;
  v50 = v54 - 205 + 203;
  m_FVF = this->m_TimeMoney.m_FVF;
  v51 = 64;
  (*(void ( **)(int *, int, int *, LineupUI *))(m_FVF + 16))(
    &this->m_TimeMoney.m_FVF,
    161,
    &v48,
    this);
  ((UIStatic *)&this->m_TimeMoney.m_FVF)->CreateFromTemplate();
  m_pData = this->m_GameTime.m_childs.m_pData;
  v49 = -4;
  v48 = 618;
  v50 = 738;
  v51 = 28;
  (*((void ( **)(PtrArray *, int, int *, LineupUI *))m_pData + 4))(
    &this->m_GameTime.m_childs,
    161,
    &v48,
    this);
  ((UIScene *)&this->m_GameTime.m_childs)->SetShow(0);
  sub_446010(&this->m_GameTime.m_childs);
  m_benable = this->stp_Effect.m_benable;
  v49 = 16;
  v48 = 668;
  v50 = 748;
  v51 = 48;
  (*(void ( **)(int *, int, int *, LineupUI *))(m_benable + 16))(
    &this->stp_Effect.m_benable,
    161,
    &v48,
    this);
  ((UIScene *)&this->stp_Effect.m_benable)->SetShow(0);
  sub_446010(&this->stp_Effect.m_benable);

  v9 = *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[172];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[160] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[156] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[164] = 488;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[168] = 110;
  (*(void ( **)(char *, char *, char *, LineupUI *))(v9 + 16))(
    &this->m_CtrlPlank[11].m_Btn[172],
    &byte_A00001,
    &this->m_CtrlPlank[11].m_Btn[156],
    this);
  ((UIStatic *)&this->m_CtrlPlank[11].m_Btn[172])->CreateFromTemplate();
  v10 = 5;
  v11 = &this->pStateUI + 156;
  do
  {
    *v11 = (StateUI *)24;
    v11 += 4;
    --v10;
  }
  while ( v10 );
  v12 = *((_DWORD *)&this->pStateUI + 156);
  v13 = *((_DWORD *)&this->pStateUI + 164);
  *((_DWORD *)&this->pStateUI + 162) = *((_DWORD *)&this->pStateUI + 160) + 57;
  *((_DWORD *)&this->pStateUI + 158) = v12 + 57;
  v14 = *((_DWORD *)&this->pStateUI + 168);
  *((_DWORD *)&this->pStateUI + 169) = 351;
  *((_DWORD *)&this->pStateUI + 173) = 351;
  v15 = *((_DWORD *)&this->pStateUI + 172);
  v16 = &this->pStateUI + 155;
  *((_DWORD *)&this->pStateUI + 166) = v13 + 57;
  *((_DWORD *)&this->pStateUI + 155) = 50;
  *((_DWORD *)&this->pStateUI + 157) = 105;
  *((_DWORD *)&this->pStateUI + 159) = 136;
  *((_DWORD *)&this->pStateUI + 161) = 191;
  *((_DWORD *)&this->pStateUI + 163) = 216;
  *((_DWORD *)&this->pStateUI + 165) = 271;
  *((_DWORD *)&this->pStateUI + 167) = 296;
  *((_DWORD *)&this->pStateUI + 170) = v14 + 57;
  *((_DWORD *)&this->pStateUI + 171) = 296;
  *((_DWORD *)&this->pStateUI + 174) = v15 + 57;
  v17 = (UIStatic *)&this->m_ProtectPanel.m_WHFace.m_caption[60];
  v18 = 5;
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, char *, StateUI **, LineupUI *))v17->__vftable->Create)(
// [VFTABLE]   v17,
// [VFTABLE]   &byte_A00001,
// [VFTABLE]   v16,
// [VFTABLE]   this);
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v17->__vftable->ShowWindow)(v17, 0);
    ((UIStatic *)v17)->CreateFromTemplate();
    v16 += 4;
    ++v17;
    --v18;
  }
  while ( v18 );
  v20 = 0;
  v21 = (UIStatic *)((char *)&this->m_ProtectPanel.m_WPXFace + 668);
  p_pDebugTex = &this->m_CtrlPlank[12].m_Up.pDebugTex;
  pszName = (char *)(&this->pStateUI + 155);
  v39 = 0;
  do
  {
    LOBYTE(v19) = g_bDebugMode;
    ((void ( *)(gbTexture **, const char *, char *, LineupUI *, char *, int, int))(*p_pDebugTex)->Height)(
      p_pDebugTex,
      (&off_56B97C)[v20],
      pszName,
      this,
      &"UI\\GameMainUI\\Lineup\\Head0"[v39],
      1,
      v19);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*p_pDebugTex)->0)(p_pDebugTex, 0);
// [VFTABLE] ((void ( *)(UIStatic *, const char *, StateUI **, LineupUI *))v21->__vftable->Create)(
// [VFTABLE]   v21,
// [VFTABLE]   (&off_56BA08)[v20],
// [VFTABLE]   &this->pStateUI + 155,
// [VFTABLE]   this);
    ((UIStatic *)v21)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD))v21->__vftable->ShowWindow)(v21, 0);
    ++v20;
    p_pDebugTex += 86;
    pszName += 16;
    ++v21;
    v39 += 256;
  }
  while ( v20 < 5 );
  for ( i = 0; i < 5; ++i )
    ((LineupComp *)this)->ShowById(i);
  bottom = this->m_GameMoney.m_rect.bottom;
  v56[1] = 95;
  v56[0] = 100;
  v56[2] = 142;
  v56[3] = 318;
  (*(void ( **)(LONG *, char *, _DWORD *, LineupUI *))(bottom + 16))(
    &this->m_GameMoney.m_rect.bottom,
    &byte_A00001,
    v56,
    this);
  ((UIStatic *)&this->m_GameMoney.m_rect.bottom)->CreateFromTemplate();
  *((_DWORD *)&this->pStateUI + 3438) = nVal;
  v25 = (ObjectCamera *)operator new(0x7Cu);
  v58 = 0;
  if ( v25 )
    v26 = ((ObjectCamera *)v25)->Create();
  else
    v26 = 0;
  *((_DWORD *)&this->pStateUI + 520) = v26;
  v58 = -1;
  ((ObjectCamera *)v26)->SetCameraEyePosition(gfxMgr);
  v38.x = 0.0;
  *(_QWORD *)&v38.y = 0x43C8000042480000LL;
  ((ObjectCamera *)*((ObjectCamera **)&this->pStateUI + 520))->SetCameraAtPosition(v38, 1);
  ((ObjectCamera *)*((ObjectCamera **)&this->pStateUI + 520))->SetCameraDist(0, *((_DWORD *)&this->pStateUI + 518), 1078774989);
  ((Object3D *)(&this->pStateUI + 544))->_Object3D("ui\\GameMainUI\\Lineup\\wl.pol", 0);
  ((Object3D *)(&this->pStateUI + 544))->VecAngle(-30.0, 30.0, 0.0);
  v27 = (float *)(&this->pStateUI + 552);
  *((_DWORD *)&this->pStateUI + 565) = *((_DWORD *)&this->pStateUI + 520);
  pszNamea = (char *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[36] + 2;
  *((float *)&this->pStateUI + 578) = *((float *)&this->pStateUI + 519);
  *((_DWORD *)&this->pStateUI + 580) = 1;
  v28 = (char *)&this->pStateUI + 2349;
  do
  {
    ((Object3D *)(v28 - 21))->_Object3D(pszNamea, 16);
    v28[59] = 0;
    *v28 = 0;
    ((Object3D *)(v28 - 21))->VecAngle(*v27, *((float *)&this->pStateUI + 553), *((float *)&this->pStateUI + 554));
    ((Object3D *)(v28 - 21))->SetObjectPosition(*v27, *((float *)&this->pStateUI + 553), *((float *)&this->pStateUI + 554));
    *(_DWORD *)(v28 + 63) = *((_DWORD *)&this->pStateUI + 520);
    *(float *)(v28 + 115) = *((float *)&this->pStateUI + 519);
    v28[99] = 1;
    ((Object3D *)(v28 - 21))->LoadObject("ui\\GameMainUI\\Lineup\\pointer.cvd", 0);
    v29 = *(float *)(v28 + 7);
    v28 += 152;
    v30 = (int)(pszNamea + 8704) < (int)&g_pRoleSystemArrayEnd;
    pszNamea += 8704;
    *(float *)(v28 - 149) = v29 + *((float *)&this->pStateUI + 521);
  }
  while ( v30 );
  v31 = (Object3D *)(&this->pStateUI + 780);
  v32 = 6;
  v42 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 526) = -1041235968;
  *((float *)&this->pStateUI + 527) = v42;
  *((_DWORD *)&this->pStateUI + 528) = -1033895936;
  v43 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 529) = 1103626240;
  *((float *)&this->pStateUI + 530) = v43;
  *((_DWORD *)&this->pStateUI + 531) = -1047527424;
  v44 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 532) = 1082130432;
  *((float *)&this->pStateUI + 533) = v44;
  *((_DWORD *)&this->pStateUI + 534) = 1109917696;
  v45 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 535) = -1031667712;
  *((float *)&this->pStateUI + 536) = v45;
  *((_DWORD *)&this->pStateUI + 537) = 1109917696;
  v46 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 538) = -1029701632;
  *((float *)&this->pStateUI + 539) = v46;
  *((_DWORD *)&this->pStateUI + 540) = -1046478848;
  v33 = *((_DWORD *)&this->pStateUI + 553);
  v34 = *((_DWORD *)&this->pStateUI + 554);
  *((float *)&this->pStateUI + 541) = *v27;
  *((_DWORD *)&this->pStateUI + 542) = v33;
  *((_DWORD *)&this->pStateUI + 543) = v34;
  do
  {
    ((Object3D *)v31)->_Object3D("ui\\GameMainUI\\Lineup\\pointer.cvd", 0);
    v31->m_visible = 0;
    v31->m_showSubObj = 0;
    v47 = *((float *)&this->pStateUI + 553) + *((float *)&this->pStateUI + 521);
    ((Object3D *)v31)->SetObjectPosition(*v27, v47, *((float *)&this->pStateUI + 554));
    v31->m_pCamera = (ObjectCamera *)*((_DWORD *)&this->pStateUI + 520);
    ++v31;
    v31[-1].m_rotDstSpeed = *((float *)&this->pStateUI + 519);
    v31[-1].m_isActionRelativeRot = 1;
    --v32;
  }
  while ( v32 );
  v57[1] = 200;
  v57[0] = 300;
  v57[2] = 500;
  v57[3] = 300;
  ((ARC_PlayerAtt *)(&this->pStateUI + 176))->Create((int)&g_PlayerAttBuffer2.skill[2], (int)v57);
  v35 = *((_DWORD *)&this->pStateUI + 196);
  v36 = *((_DWORD *)&this->pStateUI + 198);
  *((_DWORD *)&this->pStateUI + 201) = *((_DWORD *)&this->pStateUI + 197) + 14;
  *((_DWORD *)&this->pStateUI + 200) = v35 + 6;
  *((_DWORD *)&this->pStateUI + 203) = *((_DWORD *)&this->pStateUI + 199) - 38;
  *((_DWORD *)&this->pStateUI + 512) = 0;
  *((_DWORD *)&this->pStateUI + 513) = 8;
  *((_DWORD *)&this->pStateUI + 202) = v36 - 6;
  sub_445FA0(&this->pStateUI + 290);
  return ((UIItem *)(&this->pStateUI + 176))->SetData(31);
}

// 0x00484360
int LineupUI::GetSlotRect(int nVal, unsigned int dwVal)
{
  int v3; // ebp
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  char *v9; // ebp
  scAsmDecoder *v10; // ecx
  int result; // eax
  int v12; // [esp-0x8] [ebp-0x10]
  gbTexture **nVala; // [esp+0xC] [ebp+0x4]

  if ( (unsigned int)nVal <= 4 )
  {
    v12 = v3;
    sub_445FA0(&this->m_CtrlPlank[12].m_Up.pDebugTex + 86 * nVal);
    sub_445FA0(&this->m_CtrlPlank[12].m_Up.pDebugTex + 86 * *((_DWORD *)&this->pStateUI + 175));
    v6 = *((_DWORD *)&this->pStateUI + 175);
    *((_DWORD *)&this->pStateUI + 175) = nVal;
    v7 = *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * nVal + 40];
    v8 = 0;
    v9 = (char *)&this->m_ProtectPanel.m_WPXFace + 668;
    *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * nVal + 40] = *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * v6 + 40];
    *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * v6 + 40] = v7;
    nVala = &this->m_CtrlPlank[12].m_Up.pDebugTex;
    do
    {
      if ( this->m_Is[v8] )
      {
        (**(void ( ***)(char *, _DWORD))v9)(v9, 0);
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*nVala)->0)(nVala, 1);
      }
      ++v8;
      v9 += 152;
      nVala += 86;
    }
    while ( v8 < 5 );
    (**((void ( ***)(char *, int, int))&this->m_ProtectPanel.m_WPXFace
      + 38 * *((_DWORD *)&this->pStateUI + 175)
      + 167))(
      (char *)&this->m_ProtectPanel.m_WPXFace + 152 * *((_DWORD *)&this->pStateUI + 175) + 668,
      1,
      v12);
    (**((void ( ***)(gbTexture **, _DWORD))&this->m_CtrlPlank[12].m_Up.pDebugTex
      + 86 * *((_DWORD *)&this->pStateUI + 175)))(
      &this->m_CtrlPlank[12].m_Up.pDebugTex + 86 * *((_DWORD *)&this->pStateUI + 175),
      0);
    return ((scAsmDecoder *)v10)->Execute(nVal, 1);
  }
  return result;
}

// 0x00484810
int LineupUI::RebuildNavPage()
{
  gbTexture *m_pbk2; // eax
  gbTexture **p_m_pbk2; // edi
  gbTexture *m_disablepic; // edx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int m_bcreateok; // eax
  int m_bvisible; // edx
  int v10; // ecx
  int m_nSize; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // edx
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // ecx
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // edx
  int v30; // edx
  int v31; // eax
  int m_needscriptdel; // ecx
  int v33; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v36; // ecx
  int v37; // eax
  _DWORD v39[2]; // [esp+0x74] [ebp-0x20] BYREF
  int v40; // [esp+0x7C] [ebp-0x18]
  int v41; // [esp+0x80] [ebp-0x14]
  _DWORD v42[4]; // [esp+0x84] [ebp-0x10] BYREF

  m_pbk2 = this->m_OutFrameT.m_pbk2;
  p_m_pbk2 = &this->m_OutFrameT.m_pbk2;
  v39[1] = 543;
  v39[0] = 0;
  v40 = 256;
  v41 = 600;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2 + 4))(
    &this->m_OutFrameT.m_pbk2,
    161,
    v39,
    this);
  ((UIStatic *)p_m_pbk2)->CreateFromTemplate();
  m_disablepic = this->m_OutFrameR.m_disablepic;
  v39[0] = v40;
  v40 += 512;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))m_disablepic + 4))(
    &this->m_OutFrameR.m_disablepic,
    161,
    v39,
    this);
  ((UIStatic *)&this->m_OutFrameR.m_disablepic)->CreateFromTemplate();
  v39[0] = v40;
  v40 += 32;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))&this->m_OutFrameL.*((_DWORD *)m_ppic) + 4))(
    &this->m_OutFrameL.m_ppic,
    161,
    v39,
    this);
  ((UIStatic *)&this->m_OutFrameL.m_ppic)->CreateFromTemplate();
  this->stp_Effect.m_childs.m_needscriptdel = 546;
  this->stp_Effect.m_childs.m_nSize = 38;
  this->stp_Effect.m_bcreateok = 148;
  this->stp_Effect.m_bvisible = this->stp_Effect.m_childs.m_needscriptdel + 50;
  LOBYTE(v5) = g_bDebugMode;
  ((void ( *)(gbTexture **, char *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_pbk->Height)(
    &this->m_OutFrameB.m_pbk,
    &byte_A00102,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v5);
  this->m_CtrlPlank[11].m_Dw.m_pbk2 = (gbTexture *)(this->stp_Effect.m_childs.m_needscriptdel + 5);
  this->m_CtrlPlank[11].m_Dw.m_disablepicInfo = (_PlugInfo *)(this->stp_Effect.m_childs.m_nSize + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_mouseoff = this->stp_Effect.m_bcreateok - 36;
  this->m_CtrlPlank[11].m_Dw.m_FVF = this->stp_Effect.m_bvisible - 5;
  v6 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v6;
  v6 += 110;
  this->stp_Effect.m_bcreateok = v6;
  LOBYTE(v6) = g_bDebugMode;
  (*(void ( **)(char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[44]
                                                                                           + 28))(
    &byte_A00105,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v6);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[32] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[28] = this->stp_Effect.m_childs.m_nSize + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[36] = this->stp_Effect.m_bcreateok - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[40] = this->stp_Effect.m_bvisible - 5;
  v7 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v7;
  v7 += 110;
  this->stp_Effect.m_bcreateok = v7;
  LOBYTE(v7) = g_bDebugMode;
  (*(void ( **)(char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[44]
                                                                                           + 28))(
    &byte_A00104,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v7);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[16] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[12] = this->stp_Effect.m_childs.m_nSize + 35;
  m_bcreateok = this->stp_Effect.m_bcreateok;
  m_bvisible = this->stp_Effect.m_bvisible;
  v10 = m_bcreateok - 36;
  m_bcreateok -= 22;
  this->stp_Effect.m_childs.m_nSize = m_bcreateok;
  m_bvisible -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[20] = v10;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[24] = m_bvisible;
  this->stp_Effect.m_bcreateok = m_bcreateok + 110;
  LOBYTE(m_bvisible) = g_bDebugMode;
  (*(void ( **)(int *, char *, int *, LineupUI *, char *, int, int))(this->stp_BarR.m_bcreateok + 28))(
    &this->stp_BarR.m_bcreateok,
    &byte_A00103,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    m_bvisible);
  m_nSize = this->stp_Effect.m_childs.m_nSize;
  *(_DWORD *)this->m_CtrlPlank[11].m_Btn = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v12 = this->stp_Effect.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_nTextW = m_nSize + 35;
  v13 = this->stp_Effect.m_bvisible;
  v14 = v12 - 36;
  v12 -= 22;
  this->stp_Effect.m_childs.m_nSize = v12;
  this->stp_Effect.m_bcreateok = v12 + 110;
  v15 = this->stp_Effect.m_childs.m_nSize - 38;
  v42[1] = 546;
  v42[0] = v15;
  v42[2] = v15 + 256;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[4] = v14;
  v16 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[8] = v13 - 5;
  v42[3] = 610;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v16 + 16))(&this->stp_Exit.m_caption[44], 161, v42, this);
  ((UIStatic *)&this->stp_Exit.m_caption[44])->CreateFromTemplate();
  LOBYTE(v17) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_BattleArray.m_caption[44]
                                                                                         + 28))(
    &this->stp_BattleArray.m_caption[44],
    &byte_A00108,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v17);
  v18 = this->stp_Effect.m_childs.m_nSize + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[48] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v19 = this->stp_Effect.m_bcreateok;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[44] = v18;
  v20 = this->stp_Effect.m_bvisible;
  v21 = v19 - 36;
  v19 -= 22;
  this->stp_Effect.m_childs.m_nSize = v19;
  v19 += 110;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[52] = v21;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[56] = v20 - 5;
  this->stp_Effect.m_bcreateok = v19;
  LOBYTE(v19) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_caption[44] + 28))(
    &this->stp_Equip.m_caption[44],
    &byte_A00106,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v19);
  v22 = this->stp_Effect.m_bcreateok;
  v23 = this->stp_Effect.m_childs.m_nSize + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[64] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[60] = v23;
  v24 = v22 - 36;
  v25 = this->stp_Effect.m_bvisible;
  v22 -= 22;
  this->stp_Effect.m_childs.m_nSize = v22;
  v25 -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[68] = v24;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[72] = v25;
  this->stp_Effect.m_bcreateok = v22 + 110;
  LOBYTE(v25) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Prop.m_caption[44] + 28))(
    &this->stp_Prop.m_caption[44],
    &byte_A00107,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v25);
  v26 = this->stp_Effect.m_childs.m_nSize;
  v27 = this->stp_Effect.m_bcreateok;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[80] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v28 = this->stp_Effect.m_bvisible - 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[76] = v26 + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[84] = v27 - 36;
  v29 = *(_DWORD *)&this->stp_System.m_caption[44];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[88] = v28;
  LOBYTE(v28) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(v29 + 28))(
    &this->stp_System.m_caption[44],
    byte_A00110,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v28);
  v30 = *(_DWORD *)&this->stp_TaskBook.m_caption[44];
  v31 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v31;
  v31 += 110;
  this->stp_Effect.m_bcreateok = v31;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(v30 + 28))(
    &this->stp_TaskBook.m_caption[44],
    byte_A00109,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v31);
  m_needscriptdel = this->stp_Effect.m_childs.m_needscriptdel;
  v33 = this->stp_Effect.m_bcreateok - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[92] = this->stp_Effect.m_childs.m_nSize + 35;
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[100] = v33;
  bkWndX = this->bkWndX;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[96] = m_needscriptdel + 5;
  v36 = this->stp_Effect.m_bvisible;
  bkWndX -= 38;
  this->stp_Effect.m_childs.m_needscriptdel = bkWndY - 51;
  this->stp_Effect.m_childs.m_nSize = bkWndX;
  this->stp_Effect.m_bcreateok = bkWndX + 38;
  v37 = this->stp_Effect.m_childs.m_needscriptdel;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[104] = v36 - 5;
  this->stp_Effect.m_bvisible = v37 + 48;
  return sub_445FA0(&this->stp_System.m_caption[44]);
}

// 0x00488DE0
void LineupUI::LoadRoleData()
{
  int v0; // ecx
  int v1; // esi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  float fValue; // [esp+0x0] [ebp-0x1C]
  float fValuea; // [esp+0x0] [ebp-0x1C]
  float fValueb; // [esp+0x0] [ebp-0x1C]
  float fValuec; // [esp+0x0] [ebp-0x1C]
  float fValued; // [esp+0x0] [ebp-0x1C]
  float fValuee; // [esp+0x0] [ebp-0x1C]

  v1 = v0;
  *(_DWORD *)(v0 + 96) = 0;
  do
  {
    v2 = *(_DWORD *)(v1 + 96);
    if ( *(_BYTE *)(v2 + v1 + 877) )
    {
      ((RoleSystem *)((char *)&Buffer + 1408 * v2))->RecalcAggregatedStats(0);
      v3 = *(_DWORD *)(v1 + 96);
      fValue = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v3 + 9];
      ((UIScrollBar *)(4892 * v3 + v1 + 213400))->SetRange(fValue);
      v4 = *(_DWORD *)(v1 + 96);
      fValuea = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v4 + 10];
      ((UIScrollBar *)(4892 * v4 + v1 + 214496))->SetRange(fValuea);
      v5 = *(_DWORD *)(v1 + 96);
      fValueb = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * v5 + 11];
      ((UIScrollBar *)(4892 * v5 + v1 + 213948))->SetRange(fValueb);
      v6 = *(_DWORD *)(v1 + 96);
      fValuec = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v6 + 39];
      ((UIProgressBar *)(4892 * v6 + v1 + 213400))->FindChildByName(fValuec);
      v7 = *(_DWORD *)(v1 + 96);
      fValued = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v7 + 43];
      ((UIProgressBar *)(4892 * v7 + v1 + 214496))->FindChildByName(fValued);
      v8 = *(_DWORD *)(v1 + 96);
      fValuee = (float)*(int *)&Buffer.m_partyActor.m_curact[1408 * v8 + 47];
      ((UIProgressBar *)(4892 * v8 + v1 + 213948))->FindChildByName(fValuee);
      sprintf(
        (char *const)(v1 + 104),
        "%d/%d",
        (int)*(float *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 213556),
        Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)(v1 + 96) + 9]);
      ((UICaption *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 213644))->SetEnable(v1 + 104, 0);
      sprintf(
        (char *const)(v1 + 104),
        "%d/%d",
        (int)*(float *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214652),
        Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)(v1 + 96) + 10]);
      ((UICaption *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214740))->SetEnable(v1 + 104, 0);
      sprintf(
        (char *const)(v1 + 104),
        "%d/%d",
        (int)*(float *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214104),
        Buffer.m_partyActor.m_dwMatMsg[352 * *(_DWORD *)(v1 + 96) + 11]);
      ((UICaption *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214192))->SetEnable(v1 + 104, 0);
    }
    v9 = *(_DWORD *)(v1 + 96) + 1;
    *(_DWORD *)(v1 + 96) = v9;
  }
  while ( v9 < 5 );
}

// 0x00491630
int LineupUI::RebuildExitPage()
{
  int v2; // eax
  UIStatic *v3; // edi
  int m_FVF; // edx
  int v5; // eax
  gbTexture *v6; // eax
  int m_bfocus; // ecx
  unsigned int *p_r_mask; // eax
  char *v9; // eax
  int v10; // edx
  int v11; // edx
  gbTexture *pDebugTex; // eax
  char *v13; // edx
  int m_align; // ecx
  int m_benable; // edx
  gbTexture *v16; // eax
  LONG v17; // ecx
  LONG v18; // edx
  int v19; // ecx
  gbTexture *v20; // eax
  int v21; // ecx
  gbTexture *v22; // edx
  gbTexture *v23; // eax
  float v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  gbTexture *v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // edx
  gbTexture *v32; // eax
  int v33; // ecx
  _PlugInfo *v34; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v37; // ecx
  int v38; // eax
  _DWORD v40[2]; // [esp+0x44] [ebp-0x20] BYREF
  int v41; // [esp+0x4C] [ebp-0x18]
  int v42; // [esp+0x50] [ebp-0x14]
  _DWORD v43[4]; // [esp+0x54] [ebp-0x10] BYREF

  v2 = *((_DWORD *)&this->m_OutFrameT + 38);
  v3 = &this->m_OutFrameT + 1;
  v40[1] = 543;
  v40[0] = 0;
  v41 = 256;
  v42 = 600;
  (*(void ( **)(UIStatic *, int, _DWORD *, LineupUI *))(v2 + 16))(&this->m_OutFrameT + 1, 161, v40, this);
  ((UIStatic *)v3)->CreateFromTemplate();
  m_FVF = this->m_OutFrameR.m_FVF;
  v40[0] = v41;
  v41 += 512;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_FVF + 16))(
    &this->m_OutFrameR.m_FVF,
    161,
    v40,
    this);
  ((UIStatic *)&this->m_OutFrameR.m_FVF)->CreateFromTemplate();
  v40[0] = v41;
  v41 += 32;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))&this->m_OutFrameL.*((_DWORD *)m_pbk2) + 4))(
    &this->m_OutFrameL.m_pbk2,
    161,
    v40,
    this);
  ((UIStatic *)&this->m_OutFrameL.m_pbk2)->CreateFromTemplate();
  this->stp_Effect.m_bfocus = 546;
  this->stp_Effect.m_benable = 38;
  this->stp_Effect.pDebugTex = (gbTexture *)148;
  this->stp_Effect.m_align = this->stp_Effect.m_bfocus + 50;
  LOBYTE(v5) = g_bDebugMode;
  ((void ( *)(gbTexture **, char *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_disablepic->Height)(
    &this->m_OutFrameB.m_disablepic,
    &byte_A00102,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v5);
// [VFTABLE] this->m_CtrlPlank[11].m_Dw.__vftable = (vtbl_0056AE2C *)(this->stp_Effect.m_bfocus + 5);
  this->m_CtrlPlank[11].m_Name.m_nTextW = this->stp_Effect.m_benable + 35;
  this->m_CtrlPlank[11].m_Dw.m_fontcolor.Color = (unsigned int)&this->stp_Effect.pDebugTex[-1].InFmt.r_mask;
  this->m_CtrlPlank[11].m_Dw.m_wndcolor.Color = this->stp_Effect.m_align - 5;
  v6 = (gbTexture *)((char *)this->stp_Effect.pDebugTex - 22);
  this->stp_Effect.m_benable = (int)v6;
  v6 = (gbTexture *)((char *)v6 + 110);
  this->stp_Effect.pDebugTex = v6;
  LOBYTE(v6) = g_bDebugMode;
  (*(void ( **)(char *, int *, LineupUI *, char *, int, gbTexture *))(*(_DWORD *)&this->stp_Magic.m_caption[60]
                                                                                        + 28))(
    &byte_A00105,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v6);
  m_bfocus = this->stp_Effect.m_bfocus;
  v43[1] = 546;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_needscriptdel = m_bfocus + 5;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_nSize = this->stp_Effect.m_benable + 35;
  p_r_mask = &this->stp_Effect.pDebugTex[-1].InFmt.r_mask;
  v43[3] = 610;
  this->m_CtrlPlank[11].m_Dw.m_bcreateok = (int)p_r_mask;
  this->m_CtrlPlank[11].m_Dw.m_bvisible = this->stp_Effect.m_align - 5;
  v9 = (char *)&this->stp_Effect.pDebugTex[-1].InFmt.a_mask + 2;
  this->stp_Effect.m_benable = (int)v9;
  this->stp_Effect.pDebugTex = (gbTexture *)(v9 + 110);
  v10 = *(_DWORD *)&this->stp_Exit.m_caption[60];
  v43[0] = this->stp_Effect.m_benable - 38;
  v43[2] = v43[0] + 256;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v10 + 16))(&this->stp_Exit.m_caption[60], 161, v43, this);
  ((UIStatic *)&this->stp_Exit.m_caption[60])->CreateFromTemplate();
  LOBYTE(v11) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[60]
                                                                                         + 28))(
    &this->stp_State.m_caption[60],
    &byte_A00104,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v11);
  this->m_CtrlPlank[11].m_Dw.m_pfather = (UIWnd *)(this->stp_Effect.m_bfocus + 5);
  pDebugTex = this->stp_Effect.pDebugTex;
  this->m_CtrlPlank[11].m_Dw.m_rect.bottom = this->stp_Effect.m_benable + 35;
  v13 = (char *)&pDebugTex[-1].InFmt.r_mask;
  m_align = this->stp_Effect.m_align;
  pDebugTex = (gbTexture *)((char *)pDebugTex - 22);
  this->stp_Effect.m_benable = (int)pDebugTex;
  pDebugTex = (gbTexture *)((char *)pDebugTex + 110);
  this->m_CtrlPlank[11].m_Dw.m_childs.m_pData = v13;
  this->m_CtrlPlank[11].m_Dw.m_childs.capacity = m_align - 5;
  this->stp_Effect.pDebugTex = pDebugTex;
  LOBYTE(pDebugTex) = g_bDebugMode;
  ((void ( *)(gbTexture **, char *, int *, LineupUI *, char *, int, gbTexture *))this->stp_BarR.pDebugTex->Height)(
    &this->stp_BarR.pDebugTex,
    &byte_A00103,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    pDebugTex);
  m_benable = this->stp_Effect.m_benable;
  v16 = this->stp_Effect.pDebugTex;
  this->m_CtrlPlank[11].m_Dw.m_rect.left = this->stp_Effect.m_bfocus + 5;
  v17 = (LONG)&v16[-1].InFmt.r_mask;
  this->m_CtrlPlank[11].m_Dw.m_id = (void *)(m_benable + 35);
  v18 = this->stp_Effect.m_align;
  v16 = (gbTexture *)((char *)v16 - 22);
  this->stp_Effect.m_benable = (int)v16;
  v18 -= 5;
  this->m_CtrlPlank[11].m_Dw.m_rect.top = v17;
  this->m_CtrlPlank[11].m_Dw.m_rect.right = v18;
  this->stp_Effect.pDebugTex = (gbTexture *)((char *)v16 + 110);
  LOBYTE(v18) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, LONG))(*(_DWORD *)&this->stp_BattleArray.m_caption[60]
                                                                                          + 28))(
    &this->stp_BattleArray.m_caption[60],
    &byte_A00108,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v18);
  v19 = this->stp_Effect.m_benable + 35;
  this->m_CtrlPlank[11].m_Dw.m_bfocus = this->stp_Effect.m_bfocus + 5;
  v20 = this->stp_Effect.pDebugTex;
  this->m_CtrlPlank[11].m_Dw.m_benable = v19;
  v21 = this->stp_Effect.m_align;
  v22 = (gbTexture *)((char *)v20 - 36);
  v20 = (gbTexture *)((char *)v20 - 22);
  this->stp_Effect.m_benable = (int)v20;
  v20 = (gbTexture *)((char *)v20 + 110);
  this->m_CtrlPlank[11].m_Dw.pDebugTex = v22;
  this->m_CtrlPlank[11].m_Dw.m_align = v21 - 5;
  this->stp_Effect.pDebugTex = v20;
  LOBYTE(v20) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, gbTexture *))(*(_DWORD *)&this->stp_Equip.m_caption[60]
                                                                                                 + 28))(
    &this->stp_Equip.m_caption[60],
    &byte_A00106,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v20);
  v23 = this->stp_Effect.pDebugTex;
  LODWORD(v24) = this->stp_Effect.m_benable + 35;
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratioh) = this->stp_Effect.m_bfocus + 5;
  this->m_CtrlPlank[11].m_Dw.m_ratiow = v24;
  v25 = (int)&v23[-1].InFmt.r_mask;
  v26 = this->stp_Effect.m_align;
  v23 = (gbTexture *)((char *)v23 - 22);
  this->stp_Effect.m_benable = (int)v23;
  v26 -= 5;
  this->m_CtrlPlank[11].m_Dw.m_textx = v25;
  this->m_CtrlPlank[11].m_Dw.m_texty = v26;
  this->stp_Effect.pDebugTex = (gbTexture *)((char *)v23 + 110);
  LOBYTE(v26) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Prop.m_caption[60] + 28))(
    &this->stp_Prop.m_caption[60],
    &byte_A00107,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v26);
  v27 = this->stp_Effect.m_benable;
  v28 = this->stp_Effect.pDebugTex;
  *(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_text = this->stp_Effect.m_bfocus + 5;
  v29 = this->stp_Effect.m_align - 5;
  this->m_CtrlPlank[11].m_Dw.m_fonttype = (Parent_Data *)(v27 + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[4] = (char *)v28 - 36;
  v30 = *(_DWORD *)&this->stp_System.m_caption[60];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[8] = v29;
  LOBYTE(v29) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(v30 + 28))(
    &this->stp_System.m_caption[60],
    byte_A00110,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v29);
  v31 = *(_DWORD *)&this->stp_TaskBook.m_caption[60];
  v32 = (gbTexture *)((char *)this->stp_Effect.pDebugTex - 22);
  this->stp_Effect.m_benable = (int)v32;
  v32 = (gbTexture *)((char *)v32 + 110);
  this->stp_Effect.pDebugTex = v32;
  LOBYTE(v32) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, gbTexture *))(v31 + 28))(
    &this->stp_TaskBook.m_caption[60],
    byte_A00109,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v32);
  v33 = this->stp_Effect.m_bfocus;
  v34 = (_PlugInfo *)&this->stp_Effect.pDebugTex[-1].InFmt.r_mask;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[12] = this->stp_Effect.m_benable + 35;
  bkWndY = this->bkWndY;
  this->m_CtrlPlank[11].m_Dw.m_pbkInfo = v34;
  bkWndX = this->bkWndX;
  this->m_CtrlPlank[11].m_Dw.m_pbk = (gbTexture *)(v33 + 5);
  v37 = this->stp_Effect.m_align;
  bkWndX -= 38;
  this->stp_Effect.m_bfocus = bkWndY - 51;
  this->stp_Effect.m_benable = bkWndX;
  this->stp_Effect.pDebugTex = (gbTexture *)(bkWndX + 38);
  v38 = this->stp_Effect.m_bfocus;
  this->m_CtrlPlank[11].m_Dw.m_ppic = (gbTexture *)(v37 - 5);
  this->stp_Effect.m_align = v38 + 48;
  return sub_445FA0(&this->stp_System.m_caption[60]);
}

// 0x004993D0
int LineupUI::RebuildCaptionPage()
{
  int v2; // eax
  UIStatic *v3; // edi
  int v4; // edx
  int v5; // eax
  char *v6; // edx
  void *v7; // eax
  unsigned int Color; // edx
  int v9; // edx
  void *v10; // eax
  void *v11; // eax
  int (**p_sub_4431B0)(char); // ecx
  char *m_id; // edx
  char *v14; // ecx
  void *v15; // eax
  char *v16; // ecx
  int (**v17)(char); // edx
  void *vftable; // edx
  void *v19; // eax
  int (**v20)(char); // ecx
  char *v21; // edx
  char *v22; // ecx
  void *v23; // eax
  int (**v24)(char); // edx
  char *v25; // ecx
  void *v26; // edx
  unsigned int v27; // eax
  char *v28; // ecx
  int v29; // edx
  int v30; // edx
  void *v31; // eax
  unsigned int v32; // ecx
  unsigned int v33; // eax
  int bkWndY; // edx
  void *bkWndX; // eax
  char *v36; // ecx
  unsigned int v37; // eax
  _DWORD v39[2]; // [esp+0x2C] [ebp-0x20] BYREF
  int v40; // [esp+0x34] [ebp-0x18]
  int v41; // [esp+0x38] [ebp-0x14]
  _DWORD v42[4]; // [esp+0x3C] [ebp-0x10] BYREF

  v2 = *(_DWORD *)&this->m_OutFrameL.m_text[12];
  v3 = (UIStatic *)&this->m_OutFrameL.m_text[12];
  v39[1] = 543;
  v39[0] = 0;
  v40 = 256;
  v41 = 600;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v2 + 16))(&this->m_OutFrameL.m_text[12], 161, v39, this);
  ((UIStatic *)v3)->CreateFromTemplate();
  v4 = *(_DWORD *)&this->m_OutFrameB.m_text[4];
  v39[0] = v40;
  v40 += 512;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v4 + 16))(&this->m_OutFrameB.m_text[4], 161, v39, this);
  ((UIStatic *)&this->m_OutFrameB.m_text[4])->CreateFromTemplate();
  v39[0] = v40;
  v40 += 32;
  ((void ( *)(Parent_Data **, int, _DWORD *, LineupUI *))this->stp_BarL.m_fonttype[4])(
    &this->stp_BarL.m_fonttype,
    161,
    v39,
    this);
  ((UIStatic *)&this->stp_BarL.m_fonttype)->CreateFromTemplate();
  this->m_GameMoney.m_fontcolor.Color = 546;
// [VFTABLE] this->m_GameMoney.__vftable = (vtbl_0056AE2C *)38;
  this->m_GameMoney.m_wndcolor.Color = 148;
  this->m_GameMoney.m_id = (void *)(this->m_GameMoney.m_fontcolor.Color + 50);
  LOBYTE(v5) = g_bDebugMode;
// [VFTABLE] ((void ( *)(UIStatic *, char *, UIStatic *, LineupUI *, char *, int, int))this->stp_BarR.__vftable[1].ShowWindow)(
// [VFTABLE]   &this->stp_BarR,
// [VFTABLE]   &byte_A00102,
// [VFTABLE]   &this->m_GameMoney,
// [VFTABLE]   this,
// [VFTABLE]   aUiGamemainuiCo_25,
// [VFTABLE]   1,
// [VFTABLE]   v5);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[124] = this->m_GameMoney.m_fontcolor.Color + 5;
// [VFTABLE] v6 = (char *)&this->m_GameMoney.__vftable[1].Render + 3;
  v42[1] = 546;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[120] = v6;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[128] = this->m_GameMoney.m_wndcolor.Color - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[132] = (char *)this->m_GameMoney.m_id - 5;
  v7 = (void *)(this->m_GameMoney.m_wndcolor.Color - 22);
// [VFTABLE] this->m_GameMoney.__vftable = v7;
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)&v7[3].OnMessage + 2;
  Color = this->m_GameTime.m_wndcolor.Color;
// [VFTABLE] v42[0] = (char *)this->m_GameMoney.__vftable - 38;
  v42[2] = v42[0] + 256;
  v42[3] = 610;
  (*(void ( **)(gbColorQuad *, int, _DWORD *, LineupUI *))(Color + 16))(
    &this->m_GameTime.m_wndcolor,
    161,
    v42,
    this);
  ((UIStatic *)&this->m_GameTime.m_wndcolor)->CreateFromTemplate();
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, UIStatic *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_mouseoff
                                                                                    + 28))(
    &this->stp_Equip.m_mouseoff,
    &byte_A00105,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v9);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[172] = this->m_GameMoney.m_fontcolor.Color + 5;
// [VFTABLE] *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[168] = (char *)this->m_GameMoney.__vftable + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[176] = this->m_GameMoney.m_wndcolor.Color - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[180] = (char *)this->m_GameMoney.m_id - 5;
  v10 = (void *)(this->m_GameMoney.m_wndcolor.Color - 22);
// [VFTABLE] this->m_GameMoney.__vftable = v10;
  v10 = (void *)((char *)v10 + 110);
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)v10;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(char *, UIStatic *, LineupUI *, char *, int, void *))(*(_DWORD *)&this->stp_Magic.m_mouseoff
                                                                                      + 28))(
    &byte_A00104,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v10);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[156] = this->m_GameMoney.m_fontcolor.Color + 5;
  v11 = (void *)this->m_GameMoney.m_wndcolor.Color;
// [VFTABLE] *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[152] = (char *)this->m_GameMoney.__vftable + 35;
  p_sub_4431B0 = &v11[-2].sub_4431B0;
  m_id = (char *)this->m_GameMoney.m_id;
  v11 = (void *)((char *)v11 - 22);
// [VFTABLE] this->m_GameMoney.__vftable = v11;
  m_id -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[160] = p_sub_4431B0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[164] = m_id;
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)&v11[3].OnMessage + 2;
  LOBYTE(m_id) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, UIStatic *, LineupUI *, char *, int, char *))(*(_DWORD *)&this->stp_State.m_mouseoff
                                                                                       + 28))(
    &this->stp_State.m_mouseoff,
    &byte_A00103,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    m_id);
// [VFTABLE] v14 = (char *)&this->m_GameMoney.__vftable[1].Render + 3;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[140] = this->m_GameMoney.m_fontcolor.Color + 5;
  v15 = (void *)this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[136] = v14;
  v16 = (char *)this->m_GameMoney.m_id;
  v17 = &v15[-2].sub_4431B0;
  v15 = (void *)((char *)v15 - 22);
// [VFTABLE] this->m_GameMoney.__vftable = v15;
  v15 = (void *)((char *)v15 + 110);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[144] = v17;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[148] = v16 - 5;
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)v15;
  LOBYTE(v15) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, UIStatic *, LineupUI *, char *, int, void *))(*(_DWORD *)&this->stp_TaskBook.m_mouseoff
                                                                                                + 28))(
    &this->stp_TaskBook.m_mouseoff,
    &byte_A00108,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v15);
// [VFTABLE] vftable = this->m_GameMoney.__vftable;
  v19 = (void *)this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[188] = this->m_GameMoney.m_fontcolor.Color + 5;
  v20 = &v19[-2].sub_4431B0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[184] = (char *)vftable + 35;
  v21 = (char *)this->m_GameMoney.m_id;
  v19 = (void *)((char *)v19 - 22);
// [VFTABLE] this->m_GameMoney.__vftable = v19;
  v21 -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[192] = v20;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[196] = v21;
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)&v19[3].OnMessage + 2;
  LOBYTE(v21) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, UIStatic *, LineupUI *, char *, int, char *))(*(_DWORD *)&this->stp_Prop.m_mouseoff
                                                                                       + 28))(
    &this->stp_Prop.m_mouseoff,
    &byte_A00106,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v21);
// [VFTABLE] v22 = (char *)&this->m_GameMoney.__vftable[1].Render + 3;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[204] = this->m_GameMoney.m_fontcolor.Color + 5;
  v23 = (void *)this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[200] = v22;
  v24 = &v23[-2].sub_4431B0;
  v25 = (char *)this->m_GameMoney.m_id;
  v23 = (void *)((char *)v23 - 22);
// [VFTABLE] this->m_GameMoney.__vftable = v23;
  v23 = (void *)((char *)v23 + 110);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[208] = v24;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[212] = v25 - 5;
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)v23;
  LOBYTE(v23) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, UIStatic *, LineupUI *, char *, int, void *))(*(_DWORD *)&this->stp_BattleArray.m_mouseoff
                                                                                                + 28))(
    &this->stp_BattleArray.m_mouseoff,
    &byte_A00107,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v23);
// [VFTABLE] v26 = this->m_GameMoney.__vftable;
  v27 = this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[220] = this->m_GameMoney.m_fontcolor.Color + 5;
  v27 -= 36;
  v28 = (char *)this->m_GameMoney.m_id - 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[216] = (char *)v26 + 35;
  v29 = *(_DWORD *)&this->stp_Exit.m_mouseoff;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[224] = v27;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[228] = v28;
  LOBYTE(v27) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, UIStatic *, LineupUI *, char *, int, unsigned int))(v29 + 28))(
    &this->stp_Exit.m_mouseoff,
    byte_A00110,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v27);
  v30 = *(_DWORD *)&this->stp_System.m_mouseoff;
  v31 = (void *)(this->m_GameMoney.m_wndcolor.Color - 22);
// [VFTABLE] this->m_GameMoney.__vftable = v31;
  v31 = (void *)((char *)v31 + 110);
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)v31;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(_BYTE *, char *, UIStatic *, LineupUI *, char *, int, void *))(v30 + 28))(
    &this->stp_System.m_mouseoff,
    byte_A00109,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v31);
  v32 = this->m_GameMoney.m_fontcolor.Color;
  v33 = this->m_GameMoney.m_wndcolor.Color - 36;
// [VFTABLE] *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[232] = (char *)this->m_GameMoney.__vftable + 35;
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[240] = v33;
  bkWndX = (void *)this->bkWndX;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[236] = v32 + 5;
  v36 = (char *)this->m_GameMoney.m_id;
  bkWndX = (void *)((char *)bkWndX - 38);
  this->m_GameMoney.m_fontcolor.Color = bkWndY - 51;
// [VFTABLE] this->m_GameMoney.__vftable = bkWndX;
  this->m_GameMoney.m_wndcolor.Color = (unsigned int)&bkWndX[1].Update_2ff0 + 2;
  v37 = this->m_GameMoney.m_fontcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[244] = v36 - 5;
  this->m_GameMoney.m_id = (void *)(v37 + 48);
  return sub_445FA0(&this->stp_Exit.m_mouseoff);
}

// 0x004A26D0
int LineupUI::RebuildFontPage()
{
  int m_FVF; // eax
  int *p_m_FVF; // edi
  gbTexture *m_pbk2; // edx
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int m_benable; // eax
  UIWnd *v10; // edx
  unsigned int v11; // ecx
  int v12; // eax
  int m_bfocus; // ecx
  void *v14; // edx
  int m_bcreateok; // edx
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  gbTexture *v19; // ecx
  int v20; // eax
  float v21; // ecx
  int v22; // edx
  Parent_Data *v23; // eax
  int v24; // ecx
  int v25; // edx
  int v26; // edx
  int v27; // eax
  int m_bvisible; // ecx
  int v29; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v32; // ecx
  int v33; // eax
  _DWORD v35[2]; // [esp+0x18] [ebp-0x20] BYREF
  int v36; // [esp+0x20] [ebp-0x18]
  int v37; // [esp+0x24] [ebp-0x14]
  _DWORD v38[4]; // [esp+0x28] [ebp-0x10] BYREF

  m_FVF = this->m_OutFrameT.m_FVF;
  p_m_FVF = &this->m_OutFrameT.m_FVF;
  v35[1] = 543;
  v35[0] = 0;
  v36 = 256;
  v37 = 600;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_FVF + 16))(
    &this->m_OutFrameT.m_FVF,
    161,
    v35,
    this);
  ((UIStatic *)p_m_FVF)->CreateFromTemplate();
  m_pbk2 = this->m_OutFrameR.m_pbk2;
  v35[0] = v36;
  v36 += 512;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2 + 4))(
    &this->m_OutFrameR.m_pbk2,
    161,
    v35,
    this);
  ((UIStatic *)&this->m_OutFrameR.m_pbk2)->CreateFromTemplate();
  v35[0] = v36;
  v36 += 32;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))&this->m_OutFrameL.*((_DWORD *)m_disablepic) + 4))(
    &this->m_OutFrameL.m_disablepic,
    161,
    v35,
    this);
  ((UIStatic *)&this->m_OutFrameL.m_disablepic)->CreateFromTemplate();
  v5 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  v38[1] = 546;
  v38[0] = 0;
  v38[2] = 256;
  v38[3] = 610;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v5 + 16))(&this->stp_Exit.m_caption[52], 161, v38, this);
  ((UIStatic *)&this->stp_Exit.m_caption[52])->CreateFromTemplate();
  this->stp_Effect.m_bvisible = 546;
  this->stp_Effect.m_bcreateok = 38;
  this->stp_Effect.m_benable = 148;
  v6 = this->stp_Effect.m_bvisible + 50;
  this->stp_Effect.m_bfocus = v6;
  LOBYTE(v6) = g_bDebugMode;
  ((void ( *)(char *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_ppic->Height)(
    &byte_A00102,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v6);
  this->m_CtrlPlank[11].m_Name.m_FVF = this->stp_Effect.m_bvisible + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_mouseoff = this->stp_Effect.m_bcreateok + 35;
  this->m_CtrlPlank[11].m_Name.m_nTextW = this->stp_Effect.m_benable - 36;
// [VFTABLE] this->m_CtrlPlank[11].m_Dw.__vftable = (vtbl_0056AE2C *)(this->stp_Effect.m_bfocus - 5);
  v7 = this->stp_Effect.m_benable - 22;
  this->stp_Effect.m_bcreateok = v7;
  v7 += 110;
  this->stp_Effect.m_benable = v7;
  LOBYTE(v7) = g_bDebugMode;
  (*(void ( **)(char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[52]
                                                                                           + 28))(
    &byte_A00105,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v7);
  this->m_CtrlPlank[11].m_Dw.m_childs.capacity = this->stp_Effect.m_bvisible + 5;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_pData = (char *)(this->stp_Effect.m_bcreateok + 35);
  this->m_CtrlPlank[11].m_Dw.m_childs.m_nSize = this->stp_Effect.m_benable - 36;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_needscriptdel = this->stp_Effect.m_bfocus - 5;
  v8 = this->stp_Effect.m_benable - 22;
  this->stp_Effect.m_bcreateok = v8;
  v8 += 110;
  this->stp_Effect.m_benable = v8;
  LOBYTE(v8) = g_bDebugMode;
  (*(void ( **)(char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[52]
                                                                                           + 28))(
    &byte_A00104,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v8);
  this->m_CtrlPlank[11].m_Dw.m_rect.right = this->stp_Effect.m_bvisible + 5;
  m_benable = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_rect.top = this->stp_Effect.m_bcreateok + 35;
  v10 = (UIWnd *)(this->stp_Effect.m_bfocus - 5);
  this->m_CtrlPlank[11].m_Dw.m_rect.bottom = m_benable - 36;
  m_benable -= 22;
  this->m_CtrlPlank[11].m_Dw.m_pfather = v10;
  this->stp_Effect.m_bcreateok = m_benable;
  this->stp_Effect.m_benable = m_benable + 110;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(int *, char *, int *, LineupUI *, char *, int, UIWnd *))(this->stp_BarR.m_benable + 28))(
    &this->stp_BarR.m_benable,
    &byte_A00103,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v10);
  v11 = this->stp_Effect.m_bcreateok + 35;
  this->m_CtrlPlank[11].m_Dw.m_wndcolor.Color = this->stp_Effect.m_bvisible + 5;
  v12 = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_fontcolor.Color = v11;
  m_bfocus = this->stp_Effect.m_bfocus;
  v14 = (void *)(v12 - 36);
  v12 -= 22;
  this->stp_Effect.m_bcreateok = v12;
  v12 += 110;
  this->m_CtrlPlank[11].m_Dw.m_id = v14;
  this->m_CtrlPlank[11].m_Dw.m_rect.left = m_bfocus - 5;
  this->stp_Effect.m_benable = v12;
  LOBYTE(v12) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_BattleArray.m_caption[52] + 28))(
    &this->stp_BattleArray.m_caption[52],
    &byte_A00108,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v12);
  m_bcreateok = this->stp_Effect.m_bcreateok;
  v16 = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_bvisible = this->stp_Effect.m_bvisible + 5;
  v17 = v16 - 36;
  this->m_CtrlPlank[11].m_Dw.m_bcreateok = m_bcreateok + 35;
  v18 = this->stp_Effect.m_bfocus;
  v16 -= 22;
  this->stp_Effect.m_bcreateok = v16;
  v18 -= 5;
  this->m_CtrlPlank[11].m_Dw.m_benable = v17;
  this->m_CtrlPlank[11].m_Dw.m_bfocus = v18;
  this->stp_Effect.m_benable = v16 + 110;
  LOBYTE(v18) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_caption[52] + 28))(
    &this->stp_Equip.m_caption[52],
    &byte_A00106,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v18);
  v19 = (gbTexture *)(this->stp_Effect.m_bcreateok + 35);
  this->m_CtrlPlank[11].m_Dw.m_align = this->stp_Effect.m_bvisible + 5;
  v20 = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.pDebugTex = v19;
  LODWORD(v21) = this->stp_Effect.m_bfocus - 5;
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratiow) = v20 - 36;
  v20 -= 22;
  this->m_CtrlPlank[11].m_Dw.m_ratioh = v21;
  this->stp_Effect.m_bcreateok = v20;
  v20 += 110;
  this->stp_Effect.m_benable = v20;
  LOBYTE(v20) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Prop.m_caption[52] + 28))(
    &this->stp_Prop.m_caption[52],
    &byte_A00107,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v20);
  v22 = this->stp_Effect.m_bcreateok;
  v23 = (Parent_Data *)this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_texty = this->stp_Effect.m_bvisible + 5;
  v23 -= 9;
  v24 = this->stp_Effect.m_bfocus - 5;
  this->m_CtrlPlank[11].m_Dw.m_textx = v22 + 35;
  v25 = *(_DWORD *)&this->stp_System.m_caption[52];
  this->m_CtrlPlank[11].m_Dw.m_fonttype = v23;
  *(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_text = v24;
  LOBYTE(v23) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, Parent_Data *))(v25 + 28))(
    &this->stp_System.m_caption[52],
    byte_A00110,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v23);
  v26 = *(_DWORD *)&this->stp_TaskBook.m_caption[52];
  v27 = this->stp_Effect.m_benable - 22;
  this->stp_Effect.m_bcreateok = v27;
  v27 += 110;
  this->stp_Effect.m_benable = v27;
  LOBYTE(v27) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(v26 + 28))(
    &this->stp_TaskBook.m_caption[52],
    byte_A00109,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v27);
  m_bvisible = this->stp_Effect.m_bvisible;
  v29 = this->stp_Effect.m_benable - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[4] = this->stp_Effect.m_bcreateok + 35;
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[12] = v29;
  bkWndX = this->bkWndX;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[8] = m_bvisible + 5;
  v32 = this->stp_Effect.m_bfocus;
  bkWndX -= 38;
  this->stp_Effect.m_bvisible = bkWndY - 51;
  this->stp_Effect.m_bcreateok = bkWndX;
  this->stp_Effect.m_benable = bkWndX + 38;
  v33 = this->stp_Effect.m_bvisible + 48;
  this->m_CtrlPlank[11].m_Dw.m_pbk = (gbTexture *)(v32 - 5);
  this->stp_Effect.m_bfocus = v33;
  return sub_445FA0(&this->stp_System.m_caption[52]);
}

// 0x004B1920
int * LineupUI::UpdateProtectPanel(int nVal)
{
  int v3; // eax
  int v4; // esi
  int v5; // ebx
  UIStatic *v6; // ebp
  int v8; // [esp+0x18] [ebp-0x8]

  v3 = 40;
  v4 = *((_DWORD *)this + 71588) + 40;
  v8 = *((_DWORD *)this + 71589) + 12;
  v5 = 0;
  v6 = (UIStatic *)&this->m_ProtectPanel.m_WPXFace.m_caption[92];
  do
  {
    ((ChoseCompose *)this)->LayoutItem(v5, 12, v3, v8, v4);
    sub_445E50((int)&v6[-4].m_pbk);
    if ( (unsigned int)nVal <= 1 )
      ((UIStatic *)v6)->CreateFromTemplate();
    v3 = v4;
    v4 += *((_DWORD *)this + 71588);
    ++v5;
    v6 = (UIStatic *)((char *)v6 + 3560);
  }
  while ( v5 < 36 );
  sub_445E50((int)&this->m_ProtectPanel.m_BK.m_text[12]);
  return (int *)((UITitle_JDHY *)this)->UpdateButtonStates();
}

// 0x004B3DA0
int LineupUI::RebuildMainPage()
{
  gbTexture *m_pbk2; // eax
  gbTexture **p_m_pbk2; // edi
  gbTexture *m_disablepic; // edx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int m_bcreateok; // edx
  int m_bvisible; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  unsigned int v13; // ecx
  unsigned int v14; // edx
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int m_nSize; // edx
  int v20; // eax
  gbTexture *v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // eax
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // edx
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // eax
  int v33; // edx
  _DWORD v35[2]; // [esp+D0h] [ebp-0x30] BYREF
  int v36; // [esp+D8h] [ebp-0x28]
  int v37; // [esp+DCh] [ebp-0x24]
  _DWORD v38[4]; // [esp+E0h] [ebp-0x20] BYREF
  _DWORD v39[4]; // [esp+F0h] [ebp-0x10] BYREF

  m_pbk2 = this->m_OutFrameT.m_pbk2;
  p_m_pbk2 = &this->m_OutFrameT.m_pbk2;
  v35[1] = 543;
  v35[0] = 0;
  v36 = 256;
  v37 = 600;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2 + 4))(
    &this->m_OutFrameT.m_pbk2,
    161,
    v35,
    this);
  ((UIStatic *)p_m_pbk2)->CreateFromTemplate();
  m_disablepic = this->m_OutFrameR.m_disablepic;
  v35[0] = v36;
  v36 += 512;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))m_disablepic + 4))(
    &this->m_OutFrameR.m_disablepic,
    161,
    v35,
    this);
  ((UIStatic *)&this->m_OutFrameR.m_disablepic)->CreateFromTemplate();
  v35[0] = v36;
  v36 += 32;
  (*((void ( **)(gbTexture **, int, _DWORD *, LineupUI *))&this->m_OutFrameL.*((_DWORD *)m_ppic) + 4))(
    &this->m_OutFrameL.m_ppic,
    161,
    v35,
    this);
  ((UIStatic *)&this->m_OutFrameL.m_ppic)->CreateFromTemplate();
  this->stp_Effect.m_childs.m_needscriptdel = 546;
  this->stp_Effect.m_childs.m_nSize = 38;
  this->stp_Effect.m_bcreateok = 148;
  this->stp_Effect.m_bvisible = this->stp_Effect.m_childs.m_needscriptdel + 50;
  LOBYTE(v5) = g_bDebugMode;
  ((void ( *)(gbTexture **, char *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_pbk->Height)(
    &this->m_OutFrameB.m_pbk,
    &byte_A00102,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v5);
  this->m_CtrlPlank[11].m_Name.m_pbk2 = (gbTexture *)(this->stp_Effect.m_childs.m_needscriptdel + 5);
  this->m_CtrlPlank[11].m_Name.m_disablepicInfo = (_PlugInfo *)(this->stp_Effect.m_childs.m_nSize + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_mouseoff = this->stp_Effect.m_bcreateok - 36;
  this->m_CtrlPlank[11].m_Name.m_FVF = this->stp_Effect.m_bvisible - 5;
  v6 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v6;
  v6 += 110;
  this->stp_Effect.m_bcreateok = v6;
  LOBYTE(v6) = g_bDebugMode;
  (*(void ( **)(char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[44]
                                                                                           + 28))(
    &byte_A00105,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v6);
  this->m_CtrlPlank[11].m_Dw.m_pfather = (UIWnd *)(this->stp_Effect.m_childs.m_needscriptdel + 5);
  this->m_CtrlPlank[11].m_Dw.m_rect.bottom = this->stp_Effect.m_childs.m_nSize + 35;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_pData = (char *)(this->stp_Effect.m_bcreateok - 36);
  this->m_CtrlPlank[11].m_Dw.m_childs.capacity = this->stp_Effect.m_bvisible - 5;
  v7 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v7;
  v7 += 110;
  this->stp_Effect.m_bcreateok = v7;
  LOBYTE(v7) = g_bDebugMode;
  (*(void ( **)(char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[44]
                                                                                           + 28))(
    &byte_A00104,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v7);
  this->m_CtrlPlank[11].m_Dw.m_rect.left = this->stp_Effect.m_childs.m_needscriptdel + 5;
  this->m_CtrlPlank[11].m_Dw.m_id = (void *)(this->stp_Effect.m_childs.m_nSize + 35);
  m_bcreateok = this->stp_BarR.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_rect.top = this->stp_Effect.m_bcreateok - 36;
  m_bvisible = this->stp_Effect.m_bvisible;
  v10 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v10;
  v10 += 110;
  this->m_CtrlPlank[11].m_Dw.m_rect.right = m_bvisible - 5;
  this->stp_Effect.m_bcreateok = v10;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(int *, char *, int *, LineupUI *, char *, int, int))(m_bcreateok + 28))(
    &this->stp_BarR.m_bcreateok,
    &byte_A00103,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v10);
  v11 = this->stp_Effect.m_bcreateok;
  v12 = this->stp_Effect.m_childs.m_nSize + 35;
// [VFTABLE] this->m_CtrlPlank[11].m_Dw.__vftable = (vtbl_0056AE2C *)(this->stp_Effect.m_childs.m_needscriptdel + 5);
  v13 = v11 - 36;
  this->m_CtrlPlank[11].m_Name.m_nTextW = v12;
  v11 -= 22;
  v14 = this->stp_Effect.m_bvisible - 5;
  this->stp_Effect.m_childs.m_nSize = v11;
  this->m_CtrlPlank[11].m_Dw.m_fontcolor.Color = v13;
  this->m_CtrlPlank[11].m_Dw.m_wndcolor.Color = v14;
  this->stp_Effect.m_bcreateok = v11 + 110;
  LOBYTE(v14) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_BattleArray.m_caption[44] + 28))(
    &this->stp_BattleArray.m_caption[44],
    &byte_A00108,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v14);
  v15 = this->stp_Effect.m_childs.m_nSize + 35;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_needscriptdel = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v16 = this->stp_Effect.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_nSize = v15;
  v17 = this->stp_Effect.m_bvisible;
  v18 = v16 - 36;
  v16 -= 22;
  this->stp_Effect.m_childs.m_nSize = v16;
  v16 += 110;
  this->m_CtrlPlank[11].m_Dw.m_bcreateok = v18;
  this->m_CtrlPlank[11].m_Dw.m_bvisible = v17 - 5;
  this->stp_Effect.m_bcreateok = v16;
  LOBYTE(v16) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_caption[44] + 28))(
    &this->stp_Equip.m_caption[44],
    &byte_A00106,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v16);
  m_nSize = this->stp_Effect.m_childs.m_nSize;
  v20 = this->stp_Effect.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_bfocus = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v21 = (gbTexture *)(v20 - 36);
  this->m_CtrlPlank[11].m_Dw.m_benable = m_nSize + 35;
  v22 = this->stp_Effect.m_bvisible;
  v20 -= 22;
  this->stp_Effect.m_childs.m_nSize = v20;
  v22 -= 5;
  this->m_CtrlPlank[11].m_Dw.pDebugTex = v21;
  this->m_CtrlPlank[11].m_Dw.m_align = v22;
  this->stp_Effect.m_bcreateok = v20 + 110;
  LOBYTE(v22) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Prop.m_caption[44] + 28))(
    &this->stp_Prop.m_caption[44],
    &byte_A00107,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v22);
  v23 = this->stp_Effect.m_childs.m_nSize;
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratioh) = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v24 = this->stp_Effect.m_bcreateok;
  v38[1] = 546;
  v25 = v24 - 36;
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratiow) = v23 + 35;
  v26 = this->stp_Effect.m_bvisible;
  v24 -= 22;
  this->stp_Effect.m_childs.m_nSize = v24;
  this->stp_Effect.m_bcreateok = v24 + 110;
  v38[0] = this->stp_Effect.m_childs.m_nSize - 38;
  v38[2] = v38[0] + 256;
  this->m_CtrlPlank[11].m_Dw.m_textx = v25;
  v27 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  this->m_CtrlPlank[11].m_Dw.m_texty = v26 - 5;
  v38[3] = 610;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v27 + 16))(&this->stp_Exit.m_caption[44], 161, v38, this);
  ((UIStatic *)&this->stp_Exit.m_caption[44])->CreateFromTemplate();
  LOBYTE(v28) = g_bDebugMode;
  (*(void ( **)(char *, char *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_TaskBook.m_caption[44]
                                                                                         + 28))(
    &this->stp_TaskBook.m_caption[44],
    byte_A00109,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v28);
  v29 = this->stp_Effect.m_bcreateok;
  v30 = this->stp_Effect.m_childs.m_nSize;
  *(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_text = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[8] = this->stp_Effect.m_bvisible - 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[4] = v29 - 36;
  v31 = *((_DWORD *)&this->m_Frame + 38);
  this->m_CtrlPlank[11].m_Dw.m_fonttype = (Parent_Data *)(v30 + 35);
  v39[1] = 64;
  v39[0] = 784;
  v39[2] = 800;
  v39[3] = 590;
  (*(void ( **)(UIStatic *, int, _DWORD *, LineupUI *))(v31 + 16))(&this->m_Frame + 1, 161, v39, this);
  ((UIStatic *)&this->m_Frame + 1)->CreateFromTemplate();
  this->stp_Effect.m_childs.m_needscriptdel = this->bkWndY - 51;
  v32 = this->bkWndX - 38;
  v33 = *(_DWORD *)&this->stp_System.m_caption[44];
  this->stp_Effect.m_childs.m_nSize = v32;
  v32 += 38;
  this->stp_Effect.m_bcreateok = v32;
  this->stp_Effect.m_bvisible = this->stp_Effect.m_childs.m_needscriptdel + 48;
  LOBYTE(v32) = g_bDebugMode;
  return (*(int ( **)(char *, char *, int *, LineupUI *, char *, int, int))(v33 + 28))(
           &this->stp_System.m_caption[44],
           byte_A00110,
           &this->stp_Effect.m_childs.m_nSize,
           this,
           "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
           1,
           v32);
}
