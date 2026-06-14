#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/MainPropUI.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
CHAR * sub_458F70(LPCSTR lpString, int a2, LPSTR lpString1); // from annotations

// Unnamed globals (extern)
extern char asc_5B74B8[];
extern char byte_A00102;
extern char byte_A00103;
extern char byte_A00104;
extern char byte_A00105;
extern char byte_A00106;
extern char byte_A00107;
extern char byte_A00108;
extern char byte_A00109;
extern char byte_A00110;
extern char byte_A00323;
extern char byte_A00324;
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern int dword_56D5F0[];
extern const char * off_56D5D8;

// 0x00487650
int MainPropUI::CreateCoverTemplate()
{
  int v2; // eax
  UIStatic *p_isActive; // edi
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  LONG v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // eax
  unsigned int v17; // ecx
  unsigned int v18; // edx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // edx
  gbTexture *v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // edx
  int v29; // eax
  gbTexture *ptex; // edx
  float m_posy; // edx
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v37; // ecx
  int v38; // eax
  _DWORD v40[2]; // [esp+0x5C] [ebp-0x20] BYREF
  int v41; // [esp+0x64] [ebp-0x18]
  int v42; // [esp+0x68] [ebp-0x14]
  _DWORD v43[4]; // [esp+0x6C] [ebp-0x10] BYREF

  v2 = *(_DWORD *)&this->m_btnPar[10][6]._isActive;
  p_isActive = (UIStatic *)&this->m_btnPar[10][6]._isActive;
  v40[1] = 543;
  v40[0] = 0;
  v41 = 256;
  v42 = 600;
  (*(void ( **)(_BYTE *, int, _DWORD *, MainPropUI *))(v2 + 16))(
    &this->m_btnPar[10][6]._isActive,
    161,
    v40,
    this);
  ((UIStatic *)p_isActive)->CreateFromTemplate();
  v4 = *(_DWORD *)&this->m_btnPar[10][6]._texName[120];
  v40[0] = v41;
  v41 += 512;
  (*(void ( **)(char *, int, _DWORD *, MainPropUI *))(v4 + 16))(
    &this->m_btnPar[10][6]._texName[120],
    161,
    v40,
    this);
  ((UIStatic *)&this->m_btnPar[10][6]._texName[120])->CreateFromTemplate();
  v40[0] = v41;
  v41 += 32;
  (*((void ( **)(void **, int, _DWORD *, MainPropUI *))this->m_btnPar[10][6]._element.m_id + 4))(
    &this->m_btnPar[10][6]._element.m_id,
    161,
    v40,
    this);
  ((UIStatic *)&this->m_btnPar[10][6]._element.m_id)->CreateFromTemplate();
  *(_DWORD *)&this->m_btnPar[11][5]._texName[172] = 546;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = 38;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = 148;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[180] = *(_DWORD *)&this->m_btnPar[11][5]._texName[172] + 50;
  LOBYTE(v5) = g_bDebugMode;
  (*(void ( **)(UIParticle *, char *, char *, MainPropUI *, char *, int, int))(this->m_btnPar[11][0].m_viewRect.left
                                                                                       + 28))(
    this->m_btnPar[11],
    &byte_A00102,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v5);
  *(_DWORD *)&this->m_parSingle[9][3]._texName[244] = *(_DWORD *)&this->m_btnPar[11][5]._texName[172] + 5;
  *(_DWORD *)&this->m_parSingle[9][3]._texName[240] = *(_DWORD *)&this->m_btnPar[11][5]._texName[168] + 35;
  *(_DWORD *)&this->m_parSingle[9][3]._texName[248] = *(_DWORD *)&this->m_btnPar[11][5]._texName[176] - 36;
  *(_DWORD *)&this->m_parSingle[9][3]._texName[252] = *(_DWORD *)&this->m_btnPar[11][5]._texName[180] - 5;
  v6 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176] - 22;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = v6;
  v6 += 110;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = v6;
  LOBYTE(v6) = g_bDebugMode;
  (*(void ( **)(char *, char *, MainPropUI *, char *, int, int))(this->m_btnPar[11][1]._element.m_rect.bottom
                                                                        + 28))(
    &byte_A00105,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v6);
  this->m_parSingle[9][3]._element.m_pfather = (UIWnd *)(*(_DWORD *)&this->m_btnPar[11][5]._texName[172] + 5);
  this->m_parSingle[9][3]._element.m_rect.bottom = *(_DWORD *)&this->m_btnPar[11][5]._texName[168] + 35;
  this->m_parSingle[9][3]._element.m_childs.m_pData = (char *)(*(_DWORD *)&this->m_btnPar[11][5]._texName[176] - 36);
  this->m_parSingle[9][3]._element.m_childs.capacity = *(_DWORD *)&this->m_btnPar[11][5]._texName[180] - 5;
  v7 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176] - 22;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = v7;
  v7 += 110;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = v7;
  LOBYTE(v7) = g_bDebugMode;
  (*(void ( **)(char *, char *, MainPropUI *, char *, int, int))(*(_DWORD *)&this->m_btnPar[11][1].m_iscolorfade
                                                                        + 28))(
    &byte_A00104,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v7);
  v8 = *(_DWORD *)&this->m_btnPar[11][5]._texName[172];
  v43[1] = 546;
  this->m_parSingle[9][3]._element.m_rect.left = v8 + 5;
  this->m_parSingle[9][3]._element.m_id = (void *)(*(_DWORD *)&this->m_btnPar[11][5]._texName[168] + 35);
  v9 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176];
  v10 = *(_DWORD *)&this->m_btnPar[11][5]._texName[180];
  v43[3] = 610;
  v11 = v9 - 36;
  v9 -= 22;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = v9;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = v9 + 110;
  v12 = *(_DWORD *)&this->m_btnPar[11][5]._texName[168] - 38;
  this->m_parSingle[9][3]._element.m_rect.top = v11;
  v43[0] = v12;
  v43[2] = v12 + 256;
  v13 = *(_DWORD *)&this->m_btnPar[11][5]._texName[16];
  this->m_parSingle[9][3]._element.m_rect.right = v10 - 5;
  (*(void ( **)(char *, int, _DWORD *, MainPropUI *))(v13 + 16))(
    &this->m_btnPar[11][5]._texName[16],
    161,
    v43,
    this);
  ((UIStatic *)&this->m_btnPar[11][5]._texName[16])->CreateFromTemplate();
  LOBYTE(v14) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, MainPropUI *, char *, int, int))(*(_DWORD *)&this->m_btnPar[11][0]._texName[184]
                                                                                 + 28))(
    &this->m_btnPar[11][0]._texName[184],
    &byte_A00103,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v14);
  v15 = *(_DWORD *)&this->m_btnPar[11][5]._texName[168];
  v16 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176];
// [VFTABLE] this->m_parSingle[9][3]._element.__vftable = (vtbl_0056AE2C *)(*(_DWORD *)&this->m_btnPar[11][5]._texName[172] + 5);
  v17 = v16 - 36;
  this->m_parSingle[9][3]._ptex = (gbTexture *)(v15 + 35);
  v18 = *(_DWORD *)&this->m_btnPar[11][5]._texName[180];
  v16 -= 22;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = v16;
  v18 -= 5;
  this->m_parSingle[9][3]._element.m_fontcolor.Color = v17;
  this->m_parSingle[9][3]._element.m_wndcolor.Color = v18;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = v16 + 110;
  LOBYTE(v18) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, MainPropUI *, char *, int, unsigned int))(*(_DWORD *)&this->m_btnPar[11][3]._texName[152]
                                                                                              + 28))(
    &this->m_btnPar[11][3]._texName[152],
    &byte_A00108,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v18);
  v19 = *(_DWORD *)&this->m_btnPar[11][5]._texName[168] + 35;
  this->m_parSingle[9][3]._element.m_childs.m_needscriptdel = *(_DWORD *)&this->m_btnPar[11][5]._texName[172] + 5;
  v20 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176];
  this->m_parSingle[9][3]._element.m_childs.m_nSize = v19;
  v21 = *(_DWORD *)&this->m_btnPar[11][5]._texName[180];
  v22 = v20 - 36;
  v20 -= 22;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = v20;
  v20 += 110;
  this->m_parSingle[9][3]._element.m_bcreateok = v22;
  this->m_parSingle[9][3]._element.m_bvisible = v21 - 5;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = v20;
  LOBYTE(v20) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, MainPropUI *, char *, int, int))(*(_DWORD *)&this->m_btnPar[11][2]._texName[48]
                                                                                 + 28))(
    &this->m_btnPar[11][2]._texName[48],
    &byte_A00106,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v20);
  v23 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176];
  v24 = *(_DWORD *)&this->m_btnPar[11][5]._texName[168] + 35;
  this->m_parSingle[9][3]._element.m_bfocus = *(_DWORD *)&this->m_btnPar[11][5]._texName[172] + 5;
  this->m_parSingle[9][3]._element.m_benable = v24;
  v25 = (gbTexture *)(v23 - 36);
  v26 = *(_DWORD *)&this->m_btnPar[11][5]._texName[180];
  v23 -= 22;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = v23;
  v26 -= 5;
  this->m_parSingle[9][3]._element.pDebugTex = v25;
  this->m_parSingle[9][3]._element.m_align = v26;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = v23 + 110;
  LOBYTE(v26) = g_bDebugMode;
  (*(void ( **)(_PlugInfo **, char *, char *, MainPropUI *, char *, int, int))&this->m_btnPar[11][2]._element.m_disablepicInfo->name[24])(
    &this->m_btnPar[11][2]._element.m_disablepicInfo,
    &byte_A00107,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v26);
  v27 = *(_DWORD *)&this->m_btnPar[11][5]._texName[168];
  v28 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176];
  LODWORD(this->m_parSingle[9][3]._element.m_ratioh) = *(_DWORD *)&this->m_btnPar[11][5]._texName[172] + 5;
  v29 = *(_DWORD *)&this->m_btnPar[11][5]._texName[180] - 5;
  LODWORD(this->m_parSingle[9][3]._element.m_ratiow) = v27 + 35;
  this->m_parSingle[9][3]._element.m_textx = v28 - 36;
  ptex = this->m_btnPar[11][4]._ptex;
  this->m_parSingle[9][3]._element.m_texty = v29;
  LOBYTE(v29) = g_bDebugMode;
  ((void ( *)(gbTexture **, char *, char *, MainPropUI *, char *, int, int))ptex->Height)(
    &this->m_btnPar[11][4]._ptex,
    byte_A00110,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v29);
  m_posy = this->m_btnPar[11][4].m_posy;
  v32 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176] - 22;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = v32;
  v32 += 110;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = v32;
  LOBYTE(v32) = g_bDebugMode;
  (*(void ( **)(float *, char *, char *, MainPropUI *, char *, int, int))(LODWORD(m_posy) + 28))(
    &this->m_btnPar[11][4].m_posy,
    byte_A00109,
    &this->m_btnPar[11][5]._texName[168],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v32);
  v33 = *(_DWORD *)&this->m_btnPar[11][5]._texName[172];
  v34 = *(_DWORD *)&this->m_btnPar[11][5]._texName[176] - 36;
  this->m_parSingle[9][3]._element.m_fonttype = (Parent_Data *)(*(_DWORD *)&this->m_btnPar[11][5]._texName[168] + 35);
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_parSingle[9][3]._element.m_text[4] = v34;
  bkWndX = this->bkWndX;
  *(_DWORD *)this->m_parSingle[9][3]._element.m_text = v33 + 5;
  v37 = *(_DWORD *)&this->m_btnPar[11][5]._texName[180];
  bkWndX -= 38;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[172] = bkWndY - 51;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[168] = bkWndX;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[176] = bkWndX + 38;
  v38 = *(_DWORD *)&this->m_btnPar[11][5]._texName[172];
  *(_DWORD *)&this->m_parSingle[9][3]._element.m_text[8] = v37 - 5;
  *(_DWORD *)&this->m_btnPar[11][5]._texName[180] = v38 + 48;
  return sub_445FA0(&this->m_btnPar[11][4]._ptex);
}

// 0x00488660
void MainPropUI::DisplayCaption(int nVal)
{
  PtrArray *p_m_childs; // esi
  PtrArray *v4; // edi
  int v5; // ebx
  char *v6; // edi
  int v7; // ebp
  void ( ***v8)(_DWORD, int); // esi
  int v9; // [esp+0x5C] [ebp-0x8]

  p_m_childs = &this->m_parSingle[12][4]._element.m_childs;
  v9 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))p_m_childs[-10].m_nSize)(&p_m_childs[-10].m_nSize, 0);
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs->m_pData)(p_m_childs, 0);
    (*(void ( **)(int *, _DWORD))p_m_childs[9].m_nSize)(&p_m_childs[9].m_nSize, 0);
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs[19].m_pData)(p_m_childs + 19, 0);
    (*(void ( **)(int *, _DWORD))p_m_childs[28].m_nSize)(&p_m_childs[28].m_nSize, 0);
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs[38].m_pData)(p_m_childs + 38, 0);
    (*(void ( **)(int *, _DWORD))p_m_childs[47].m_nSize)(&p_m_childs[47].m_nSize, 0);
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs[57].m_pData)(p_m_childs + 57, 0);
    (*(void ( **)(int *, _DWORD))p_m_childs[66].m_nSize)(&p_m_childs[66].m_nSize, 0);
    (*(void ( **)(PtrArray *, _DWORD))p_m_childs[76].m_pData)(p_m_childs + 76, 0);
    (*(void ( **)(int *, _DWORD))p_m_childs[85].m_nSize)(&p_m_childs[85].m_nSize, 0);
    v4 = p_m_childs + 95;
    v5 = 5;
    do
    {
      (*(void ( **)(PtrArray *, _DWORD))v4->m_pData)(v4, 0);
      v4 = (PtrArray *)((char *)v4 + 152);
      --v5;
    }
    while ( v5 );
    p_m_childs = (PtrArray *)((char *)p_m_childs + 4892);
    --v9;
  }
  while ( v9 );
  v6 = (char *)this + 4892 * nVal;
  v7 = 5;
  v8 = (void ( ***)(_DWORD, int))(v6 + 216564);
  do
  {
    (**v8)(v8, 1);
    v8 += 38;
    --v7;
  }
  while ( v7 );
  (**((void ( ***)(int, int))v6 + 53723))((int)(v6 + 214892), 1);
  (**((void ( ***)(int, int))v6 + 53761))((int)(v6 + 215044), 1);
  (**((void ( ***)(int, int))v6 + 53799))((int)(v6 + 215196), 1);
  (**((void ( ***)(int, int))v6 + 53837))((int)(v6 + 215348), 1);
  (**((void ( ***)(int, int))v6 + 53875))((int)(v6 + 215500), 1);
  (**((void ( ***)(int, int))v6 + 53913))((int)(v6 + 215652), 1);
  (**((void ( ***)(int, int))v6 + 53951))((int)(v6 + 215804), 1);
  (**((void ( ***)(int, int))v6 + 53989))((int)(v6 + 215956), 1);
  (**((void ( ***)(int, int))v6 + 54027))((int)(v6 + 216108), 1);
  (**((void ( ***)(int, int))v6 + 54065))((int)(v6 + 216260), 1);
  (**((void ( ***)(int, int))v6 + 54103))((int)(v6 + 216412), 1);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)&g_szRoleName1,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 7]);
  ((UICaption *)(v6 + 215804))->SetEnable((int)&this->s_x, 0);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)&g_szRoleName0,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 3]);
  ((UICaption *)(v6 + 215956))->SetEnable((int)&this->s_x, 0);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)&g_szRoleName2,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 11]);
  ((UICaption *)(v6 + 216108))->SetEnable((int)&this->s_x, 0);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)&g_szRoleName3,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 15]);
  ((UICaption *)(v6 + 216260))->SetEnable((int)&this->s_x, 0);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)&g_szSceneName,
    *((_DWORD *)&Buffer.m_partyActor.m_fActionAssignParam + 352 * nVal));
  ((UICaption *)(v6 + 216412))->SetEnable((int)&this->s_x, 0);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)g_bSlotFlag,
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 19]);
  ((UICaption *)(v6 + 216564))->SetEnable((int)&this->s_x, 0);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)&g_bSlotFlag[256],
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 23]);
  ((UICaption *)(v6 + 216716))->SetEnable((int)&this->s_x, 0);
  sprintf((char *const)&this->s_x, "%s %d", byte_DC3F3C, *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 31]);
  ((UICaption *)(v6 + 216868))->SetEnable((int)&this->s_x, 0);
  sprintf(
    (char *const)&this->s_x,
    "%s %d",
    (const char *)&g_bSlotFlag[512],
    *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 27]);
  ((UICaption *)(v6 + 217020))->SetEnable((int)&this->s_x, 0);
  sprintf((char *const)&this->s_x, "%s %d", byte_DC403C, *(_DWORD *)&Buffer.m_partyActor.m_curact[1408 * nVal + 35]);
  ((UICaption *)(v6 + 217172))->SetEnable((int)&this->s_x, 0);
}

// 0x00489030
int MainPropUI::CalcBarWidth(int nVal, float fVal)
{
  signed int v3; // esi
  int v5; // esi
  float fVala; // [esp+0x10] [ebp+0xC]

  fVala = (double)nVal * fVal;
  v3 = abs32((int)fVala);
  if ( !v3 )
    return 0;
  v5 = rand() % v3;
  if ( rand() % 1024 < 512 )
    return nVal - v5;
  else
    return v5 + nVal;
}

// 0x00489ED0
int * MainPropUI::InitNPCs(int nVal, int arg4, int nVal2)
{
  int *p_s_x; // ebx
  char *v7; // edx
  unsigned int v8; // edi
  int v9; // ebp
  int v10; // ebx
  int v12; // [esp-0x4] [ebp-0x14]
  int v13; // [esp+0x0] [ebp-0x10]
  int arg4a; // [esp+0x18] [ebp+0x8]

  p_s_x = &this->s_x;
  v7 = (char *)this + 12 * nVal2;
  v12 = *(unsigned __int16 *)&v7[9536 * nVal + 3362 + 1192 * arg4];
  arg4a = (int)&v7[9536 * nVal + 1192 * arg4];
  sprintf((char *const)&this->s_x, &dir[20], v12);
  switch ( arg4 )
  {
    case 1:
      ((UIListBox *)&this->m_parSingle[22][3]._texName[72])->SetMouseMoveSel(3, nVal2, (char *)p_s_x, 0);
      break;
    case 2:
      ((UIListBox *)&this->m_parSingle[23][0]._texName[112])->SetMouseMoveSel(3, nVal2, (char *)p_s_x, 0);
      break;
    case 3:
      ((UIListBox *)&this->m_parSingle[22][1]._texName[32])->SetMouseMoveSel(3, nVal2, (char *)p_s_x, 0);
      break;
    case 4:
      ((UIListBox *)&this->m_parSingle[21][4]._xg)->SetMouseMoveSel(3, nVal2, (char *)p_s_x, 0);
      break;
    case 5:
      ((UIListBox *)&this->m_parSingle[23][2]._texName[152])->SetMouseMoveSel(3, nVal2, (char *)p_s_x, 0);
      break;
    case 6:
      ((UIListBox *)&this->m_parSingle[23][4]._texName[192])->SetMouseMoveSel(3, nVal2, (char *)p_s_x, 0);
      break;
    default:
      break;
  }
  v8 = 0;
  v9 = 0;
  v10 = *(&g_SceneMgrPrefix.m_nSize + 4 * nVal);
  while ( v10 && v8 < (*((_DWORD *)&g_SceneMgrPrefix.m_pData + 4 * nVal) - v10) / 12 )
  {
    if ( *(_DWORD *)(*(&g_SceneMgrPrefix.m_nSize + 4 * nVal) + v9) == *(_DWORD *)(arg4a + 3356) )
    {
      *(_WORD *)(*(&g_SceneMgrPrefix.m_nSize + 4 * nVal) + 12 * v8 + 6) = *(_WORD *)(arg4a + 3362);
      return (int *)((NPC *)v13)->InitAll();
    }
    ++v8;
    v9 += 12;
  }
  return (int *)((NPC *)v13)->InitAll();
}

// 0x0048C4A0
int MainPropUI::SetPage(unsigned __int8 nPageIdx)
{
  sub_445E50((int)&this->m_parSingle[21][2].m_time.oldtick);
  sub_445E50((int)&this->m_parSingle[21][4]._xg);
  sub_445E50((int)&this->m_parSingle[22][1]._texName[32]);
  sub_445E50((int)&this->m_parSingle[22][3]._texName[72]);
  sub_445E50((int)&this->m_parSingle[23][0]._texName[112]);
  sub_445E50((int)&this->m_parSingle[23][2]._texName[152]);
  sub_445E50((int)&this->m_parSingle[23][4]._texName[192]);
  return sub_445E50((int)this + 248268);
}

// 0x0048CEE0
int MainPropUI::FindValidSaveSlot()
{
  int v1; // edx
  int result; // eax

  v1 = 0;
  for ( result = 0; result < 8; ++result )
  {
    if ( g_SaveSlotFlags[8 * (int)this->m_parSingle[9][3]._element.m_ppic + result] )
    {
      *((_BYTE *)this + v1 + 307032) = result;
      ++v1;
    }
  }
  return result;
}

// 0x0048CF10
void MainPropUI::SetCaption(int nVal, int nVal2, int nVal3)
{
  int *p_s_x; // esi
  CHAR *v6; // edi
  CHAR *v7; // [esp-0x4] [ebp-0x114]
  CHAR String1[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v9; // [esp+0x10D] [ebp-0x3]
  char v10; // [esp+0x10F] [ebp-0x1]

  p_s_x = &this->s_x;
  sprintf((char *const)&this->s_x, g_szSceneUIText);
  memset(String1, 0, sizeof(String1));
  v9 = 0;
  v10 = 0;
  v6 = sub_458F70((LPCSTR)(nVal3 + 60), (int)asc_5B74B8, String1);
  if ( lstrlenA(v6) <= 0 )
  {
    v7 = ((ArcSceneObject *)nVal3)->FormatDescription();
    lstrcpyA((LPSTR)p_s_x, v7);
  }
  else
  {
    lstrcpyA((LPSTR)p_s_x, v6);
  }
  ((UICaption *)&this->m_parSingle[11][4]._texName[164])->SetEnable((int)String1, 0);
  ((UICaption *)&this->m_parSingle[11][4]._element.m_bvisible)->SetEnable((int)p_s_x, 0);
}

// 0x0048EB40
char MainPropUI::RenderWithEffects()
{
  int v2; // eax
  char *v3; // esi
  int v4; // ebp
  int i; // esi
  char result; // al
  ScreenEffect *v7; // esi
  int v8; // ebp
  int v9; // ebx
  int v10; // eax
  int v11; // ebp
  int v12; // eax
  int v13; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  CCBMagicWindow *v19; // [esp+0x8] [ebp-0x1C]
  int v20; // [esp+0x18] [ebp-0xC]
  int v21; // [esp+0x18] [ebp-0xC]
  char *v22; // [esp+0x1C] [ebp-0x8]
  int v23; // [esp+0x1C] [ebp-0x8]
  int v24; // [esp+0x20] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v19);
  v2 = 0;
  v3 = (char *)this + 307040;
  v20 = 0;
  v22 = (char *)this + 307040;
  do
  {
    if ( *((_BYTE *)&this->m_TimeMoney.m_bcreateok + v2 + 1) )
    {
      v4 = 8;
      do
      {
// [IDA_MISID]         if ( ((Concurrency *)(v3 + 23360))->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)(v3 + 23360))->Apply();
// [IDA_MISID]         if ( ((Concurrency *)v3)->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)v3)->Apply();
        v3 += 584;
        --v4;
      }
      while ( v4 );
      v2 = v20;
    }
    ++v2;
    v3 = v22 + 4672;
    v20 = v2;
    v22 += 4672;
  }
  while ( v2 < 5 );
  if ( this->m_parSingle[9][3]._element.m_pbkInfo[352].name[(unsigned int)this + 200] )
  {
    for ( i = 0; i < 16; ++i )
    {
// [IDA_MISID]       if ( ((Concurrency *)&this->m_btnPar[12][16 * (int)this->m_parSingle[9][3]._element.m_pbkInfo + i].m_iscolorfade)->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)&this->m_btnPar[12][16 * (int)this->m_parSingle[9][3]._element.m_pbkInfo + i].m_iscolorfade)->Apply();
// [IDA_MISID]       if ( ((Concurrency *)&this->m_btnPar2[14][16 * (int)this->m_parSingle[9][3]._element.m_pbkInfo + i]._texName[216])->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)&this->m_btnPar2[14][16 * (int)this->m_parSingle[9][3]._element.m_pbkInfo
                                                               + i]._texName[216])->Apply();
    }
  }
  result = this->stp_Equip.m_caption[108];
  if ( result )
  {
    v7 = (ScreenEffect *)((char *)this + 249784);
    v23 = 98;
    do
    {
// [IDA_MISID]       if ( ((Concurrency *)v7)->details::VirtualProcessor::IsThrottled() )
      {
        ((ScreenEffect *)v7)->Apply();
      }
      else
      {
        v8 = *((_DWORD *)this + 76754);
        v9 = *((_DWORD *)this + 76756) - v8;
        v10 = rand();
        v21 = *((_DWORD *)this + 76755);
        v24 = v8 + v10 % (v9 / 2);
        v11 = *((_DWORD *)this + 76757) - v21;
        ((RenderTarget *)v7)->LoadTexture(szFilename);
        ((RenderTarget *)v7)->SetSize(32);
        fY = rand() % 10 + 252;
        fX = rand() % 10 + 36;
        v12 = rand();
        ((RenderTarget *)v7)->SetColor(v12 % 10 - 37, fX, fY);
        v13 = rand();
        ((RenderTarget *)v7)->SetAlpha(v13 % 135 + 120);
        ((RenderTarget *)v7)->SetField084();
        ((RenderTarget *)v7)->SetState();
        fYa = (float)v21;
        fXa = (float)v24;
        ((RenderTarget *)v7)->UpdateTransform(fXa, fYa);
        ((RenderTarget *)v7)->CalcRenderDimensions(v9, v11);
        ((RenderTarget *)v7)->SetOffset(1092616192);
        rand();
        *(float *)&fXb = (float)(rand() % 8 + 2);
        ((RenderTarget *)v7)->SetScale(fXb);
        ((RenderTarget *)v7)->SetVisible(1);
      }
      v7 = (ScreenEffect *)((char *)v7 + 584);
      result = --v23;
    }
    while ( v23 );
  }
  return result;
}

// 0x004909F0
int MainPropUI::_MainPropUI()
{
  gbTexture **p_m_ppic; // eax
  char *v3; // ebp
  gbTexture **v5; // [esp+0x10] [ebp-0x18]
  int v6; // [esp+0x14] [ebp-0x14]

  this->bkWndX = 800;
  this->bkWndY = 600;
  this->buf[252] = 0;
  this->remarkbuf[3] = 0;
  *(_DWORD *)&this->remarkbuf[4] = 0;
  *(_DWORD *)&this->remarkbuf[8] = 0;
  *(_DWORD *)&this->remarkbuf[12] = 7;
  *(_DWORD *)&this->remarkbuf[16] = 0;
  sub_4422E0(&this->remarkbuf[20]);
  sub_4422E0(&this->remarkbuf[172]);
  sub_4422E0(&this->m_Frame.m_rect.right);
  sub_4422E0(&this->m_TimeMoney.m_rect);
  sub_4422E0(&this->m_TopFrame.m_wndcolor);
  sub_4422E0(&this->m_TopFrameWP);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->stp_TaskBook.m_benable_snd + 4);
  sub_4422E0(&this->stp_System.m_texarray.m_ptex[13]);
  sub_4422E0(&this->stp_System.m_caption[108]);
  sub_4422E0(&this->m_parSingle[9][1]._texName[188]);
  sub_4422E0(&this->m_parSingle[9][1]._element.m_ratioh);
  sub_4422E0(&this->m_parSingle[9][2].m_posx);
  sub_4422E0(&this->m_parSingle[9][2]._texName[60]);
  sub_4422E0(&this->m_parSingle[9][2]._texName[212]);
  p_m_ppic = &this->m_parSingle[9][2]._element.m_ppic;
  v5 = &this->m_parSingle[9][2]._element.m_ppic;
  v6 = 5;
  v3 = (char *)&this->m_parSingle[9][2]._element.m_ppicInfo + 2;
  while ( 1 )
  {
    *p_m_ppic = 0;
    *((_WORD *)v3 - 1) = 0;
    lstrcpyA(v3, g_szSceneUIText);
    lstrcpyA(v3 + 512, g_szSceneUIText);
    lstrcpyA(v3 + 542, g_szSceneUIText);
    lstrcpyA(v3 + 594, g_szSceneUIText);
    memset(v3 + 630, 0, 0x30u);
    *(_DWORD *)(v3 + 774) = 0;
    v3 += 852;
    v5 += 213;
    if ( !--v6 )
      break;
    p_m_ppic = v5;
  }
  ((ARC_PlayerAtt *)&this->m_parSingle[11][0]._isActive)->Refresh();
  sub_4422E0(&this->m_parSingle[12][0]._texName[136]);
  sub_4422E0(&this->m_parSingle[12][0]._element.m_rect.bottom);
  sub_4422E0(&this->m_parSingle[12][1].view_radiusX);
  sub_4422E0(&this->m_parSingle[12][1]._texName[8]);
  sub_4422E0(&this->m_parSingle[12][1]._texName[160]);
  sub_4422E0(&this->m_parSingle[12][1]._element.m_bcreateok);
  this->m_parSingle[13][0].par_radiusX = -1;
  ((UI3DCtrl *)&this->m_parSingle[13][0].par_radiusY)->ctor_D830();
  sub_4422E0(&this->m_parSingle[13][0].m_time.oldtick);
  sub_4422E0(&this->m_parSingle[13][3]._texName[176]);
  ((UIListBox *)&this->m_parSingle[13][3]._element.pDebugTex)->UpdateKeyCtrl();
  *(_DWORD *)&this->m_parSingle[14][0]._element.m_text[12] = -1;
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  *(_DWORD *)&this->m_parSingle[14][2]._texName[252] = -1;
  ((UIProgressBar *)&this->m_parSingle[14][2]._ptex)->ctor();
  this->remarkbuf[1] = 0;
  this->remarkbuf[0] = 0;
  this->buf[254] = 0;
  this->buf[253] = 0;
  this->buf[255] = 0;
  this->m_Role[3].m_JingBar.m_alpha = 0;
  this->m_Role[3].m_JingBar.m_minAlpha = 0;
  this->m_Role[3].m_JingBar.m_fadespeed = 0.0;
  return (int)this;
}

// 0x00491B40
int MainPropUI::ShowPage()
{
  _BYTE *v2; // ecx

  if ( g_bRoleFlag1 )
  {
    v2 = &this->stp_State.m_benable_snd + 4;
  }
  else
  {
    ((PalScript *)(&this->stp_State.m_benable_snd + 4))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    v2 = &this->stp_State.m_benable_snd + 4;
  }
  sub_445E50((int)v2);
  if ( !g_bRoleFlag2 )
    ((PalScript *)(&this->stp_Magic.m_benable_snd + 4))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)(&this->stp_Magic.m_benable_snd + 4));
  ((PalScript *)&this->stp_BarL.m_childs.capacity)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnEquip.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_BarL.m_childs.capacity);
  sub_445E50((int)(&this->m_TopFrameWP + 1));
  sub_445E50((int)&this->m_OutFrameL.m_rect);
  sub_445E50((int)&this->stp_BarR.m_mouseoff);
  sub_445E50((int)(&this->stp_Equip.m_benable_snd + 4));
  sub_445E50((int)(&this->stp_Prop.m_benable_snd + 4));
  return sub_445E50((int)(&this->stp_BattleArray.m_benable_snd + 4));
}

// 0x00492BB0
void MainPropUI::ShowSubPanels(int nVal)
{
  LONG *p_top; // esi
  int v4; // ebp
  void ( ***v5)(int, int); // esi
  int v6; // ebp
  char *v7; // esi
  int v8; // [esp+0x38] [ebp+0x8]

  if ( nVal <= 5 )
  {
    p_top = &this->m_Role[5].m_Jing.m_rect.top;
    v4 = 5;
    do
    {
      (*(void ( **)(LONG *, _DWORD))*(p_top - 38))(p_top - 38, 0);
      (*(void ( **)(LONG *, _DWORD))*p_top)(p_top, 0);
      (*(void ( **)(LONG *, _DWORD))p_top[172])(p_top + 172, 0);
      (*(void ( **)(LONG *, _DWORD))p_top[86])(p_top + 86, 0);
      (*(void ( **)(LONG *, _DWORD))p_top[258])(p_top + 258, 0);
      (*(void ( **)(LONG *, _DWORD))p_top[344])(p_top + 344, 0);
      (*(void ( **)(LONG *, _DWORD))p_top[430])(p_top + 430, 0);
      p_top += 2495;
      --v4;
    }
    while ( v4 );
    v5 = (void ( ***)(int, int))((char *)this + 9980 * nVal);
    (*v5[40568])((int)(v5 + 40568), 1);
    (*v5[40606])((int)(v5 + 40606), 1);
    (*v5[40778])((int)(v5 + 40778), 1);
    (*v5[40692])((int)(v5 + 40692), 1);
    (*v5[40864])((int)(v5 + 40864), 1);
    (*v5[40950])((int)(v5 + 40950), 1);
    (*v5[41036])((int)(v5 + 41036), 1);
    v6 = 5;
    v7 = &this->m_parSingle[11][2]._texName[168];
    do
    {
      sub_445E50((int)v7);
      v7 += 344;
      --v6;
    }
    while ( v6 );
    switch ( v8 )
    {
      case 0:
        sub_445E50((int)&this->m_parSingle[11][2]._texName[168]);
        ((UIStatic *)&this->m_parSingle[9][2]._texName[212])->CreateFromTemplate();
        break;
      case 1:
        sub_445E50((int)&this->m_parSingle[11][3].m_bGetTop);
        ((UIStatic *)&this->m_parSingle[9][2]._texName[212])->CreateFromTemplate();
        break;
      case 2:
        sub_445E50((int)&this->m_parSingle[11][3]._element.m_id);
        ((UIStatic *)&this->m_parSingle[9][2]._texName[212])->CreateFromTemplate();
        break;
      case 3:
        sub_445E50((int)&this->m_parSingle[11][4]._texName[32]);
        ((UIStatic *)&this->m_parSingle[9][2]._texName[212])->CreateFromTemplate();
        break;
      case 4:
      case 5:
        sub_445E50((int)&this->m_parSingle[11][4]._element.m_pbkInfo);
        ((UIStatic *)&this->m_parSingle[9][2]._texName[212])->CreateFromTemplate();
        break;
      default:
        return;
    }
  }
}

// 0x00497050
int MainPropUI::ProcessSlotCounter(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  ++*pCounter;
  while ( 1 )
  {
    v2 = *pCounter;
    if ( this->buf[*pCounter + 253] )
    {
      if ( v2 <= 4 )
        break;
    }
    v3 = v2 + 1;
    *pCounter = v3;
    if ( v3 > 4 )
      *pCounter = 0;
  }
  return *pCounter;
}

// 0x00497080
int MainPropUI::FindNextValid(int *pCounter)
{
  int v2; // eax
  int v3; // eax

  --*pCounter;
  while ( 1 )
  {
    v2 = *pCounter;
    if ( this->buf[*pCounter + 253] )
    {
      if ( v2 >= 0 )
        break;
    }
    v3 = v2 - 1;
    *pCounter = v3;
    if ( v3 < 0 )
      *pCounter = 4;
  }
  return *pCounter;
}

// 0x004970B0
char MainPropUI::HandleKeyInput()
{
  char result; // al
  int NextValid; // eax
  void *vftable; // edx
  int v5; // eax
  void *v6; // edx
  int v7; // eax
  int v8; // edx

  result = this->m_parSingle[11][2]._texName[141];
  if ( !result )
  {
    result = 1;
    if ( g_Input.KeyInfo[10].PressTime == 1 )
    {
      NextValid = this->FindNextValid(&this->m_parSingle[13][0].par_radiusX);
// [VFTABLE] vftable = this->__vftable;
      this->m_parSingle[13][0].par_radiusX = NextValid;
      return ((char ( *)(MainPropUI *, int, int, _DWORD))vftable->OnMessage)(
               this,
               1001,
               dword_56D5F0[NextValid],
               0);
    }
    else if ( g_Input.KeyInfo[9].PressTime == 1 )
    {
      v5 = this->ProcessSlotCounter(&this->m_parSingle[13][0].par_radiusX);
// [VFTABLE] v6 = this->__vftable;
      this->m_parSingle[13][0].par_radiusX = v5;
      return ((char ( *)(MainPropUI *, int, int, _DWORD))v6->OnMessage)(this, 1001, dword_56D5F0[v5], 0);
    }
    else if ( g_Input.KeyInfo[2].PressTime == 1 )
    {
      v7 = *(_DWORD *)&this->remarkbuf[8] - 1;
      *(_DWORD *)&this->remarkbuf[8] = v7;
      if ( v7 >= 0 )
      {
        if ( v7 >= 4 )
          this->OnMessage(1001,
            &byte_A00323,
            0);
      }
      else
      {
        *(_DWORD *)&this->remarkbuf[8] = 0;
      }
      return this->OnMessage(1001,
               (&off_56D5D8)[*(_DWORD *)&this->remarkbuf[8]],
               0);
    }
    else if ( g_Input.KeyInfo[3].PressTime == 1 )
    {
      v8 = *(_DWORD *)&this->remarkbuf[8] + 1;
      *(_DWORD *)&this->remarkbuf[8] = v8;
      if ( v8 < 5 )
      {
        return this->OnMessage(1001,
                 (&off_56D5D8)[v8],
                 0);
      }
      else
      {
        result = this->OnMessage(1001,
                   &byte_A00324,
                   0);
        *(_DWORD *)&this->remarkbuf[8] = 5;
      }
    }
  }
  return result;
}
