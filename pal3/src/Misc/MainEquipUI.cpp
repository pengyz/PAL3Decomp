#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/MainEquipUI.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations
CHAR * sub_458F70(LPCSTR lpString, int a2, LPSTR lpString1); // from annotations
int sub_4A13E0(...);

int crt_sub_00540D20(void); // from annotations

// Unnamed globals (extern)
extern char asc_5B74B8[];
extern char byte_1010101;
extern char byte_189598C;
extern char byte_5967B0[3];
extern char byte_A00400;
extern char byte_A00401;
extern char byte_A00403;
extern char byte_A00404;
extern char byte_A00405;
extern char byte_A00406;
extern char byte_A00407;
extern char byte_A00416;
extern char byte_A00417;
extern char byte_A00418;
extern char byte_A00419;
extern char byte_A00420;
extern char byte_A00421;
extern char byte_A00427;
extern char byte_A00428;
extern char byte_A00429;
extern char byte_A00602;
extern char byte_A00604;
extern char byte_A00605;
extern char byte_A00606;
extern char byte_A00607;
extern char byte_A00608;
extern char byte_A00609;
extern char byte_A00610;
extern char byte_A00611;
extern char byte_ABAB09;
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DCD03C[256];
extern CHAR byte_DCD13C[256];
extern CHAR byte_DCFC3C[512];
extern int dword_A00408;
extern int dword_A00430;
extern int dword_DC353C;
extern int dword_DC373C;
extern int dword_DC433C;
extern int dword_DC673C;
extern int dword_DC683C;
extern int dword_DCF83C;
extern int dword_DCF93C;
extern int dword_DCFA3C;
extern int dword_DCFB3C;
extern int dword_DD943C;
extern int dword_DD973C;
extern int dword_DD983C;
extern int dword_DD993C;
extern int dword_DD9A3C;
extern int dword_DD9C3C;
extern int dword_DD9D3C;
extern const char * off_5BC90C;
extern void * off_5BC914;
extern void * off_5BC940;
extern void * off_5C3ED4;
extern RoleSystem stru_C059A0;

// 0x00479300
int MainEquipUI::ctor_9300()
{
  _DWORD *p_m_IsMsg; // eax
  int v3; // ecx
  int *p_m_nSize; // eax
  int v5; // ecx
  _PlugInfo **m_texarrayInfo; // eax
  int v7; // ecx
  _DWORD *p_m_benable_snd; // eax
  int v9; // ecx

  p_m_IsMsg = &this->m_IsMsg;
  v3 = 99;
  do
  {
    *p_m_IsMsg = 0xFFFF;
    p_m_IsMsg[1] = 0;
    p_m_IsMsg[2] = 0;
    p_m_IsMsg += 3;
    --v3;
  }
  while ( v3 );
  p_m_nSize = &this->m_OutFrameL.m_childs.m_nSize;
  v5 = 99;
  do
  {
    *p_m_nSize = 0xFFFF;
    p_m_nSize[1] = 0;
    p_m_nSize[2] = 0;
    p_m_nSize += 3;
    --v5;
  }
  while ( v5 );
  m_texarrayInfo = this->stp_Magic.m_texarrayInfo;
  v7 = 99;
  do
  {
    *m_texarrayInfo = (_PlugInfo *)0xFFFF;
    m_texarrayInfo[1] = 0;
    m_texarrayInfo[2] = 0;
    m_texarrayInfo += 3;
    --v7;
  }
  while ( v7 );
  p_m_benable_snd = &this->stp_BattleArray.m_benable_snd;
  v9 = 99;
  do
  {
    *p_m_benable_snd = 0xFFFF;
    p_m_benable_snd[1] = 0;
    p_m_benable_snd[2] = 0;
    p_m_benable_snd += 3;
    --v9;
  }
  while ( v9 );
  this->me_Role[2].m_RoleAttCng[2].m_bfocus = 0xFFFF;
  this->me_Role[2].m_RoleAttCng[2].pDebugTex = 0;
  this->me_Role[2].m_RoleAttCng[2].m_align = 0;
  LODWORD(this->me_Role[2].m_RoleAttCng[2].m_ratiow) = 0xFFFF;
  this->me_Role[2].m_RoleAttCng[2].m_ratioh = 0.0;
  this->me_Role[2].m_RoleAttCng[2].m_textx = 0;
  this->me_Role[2].m_RoleAttCng[2].m_texty = 0xFFFF;
  this->me_Role[2].m_RoleAttCng[2].m_fonttype = 0;
  *(_DWORD *)this->me_Role[2].m_RoleAttCng[2].m_text = 0;
  ((UI3DCtrl *)&this->me_Role[2].m_RoleAttCng[2].m_ppicInfo)->ctor_D830();
  sub_4422E0(&this->me_Role[2].m_RoleAttCng[3].m_bvisible);
  sub_4422E0(&this->me_Role[2].m_RoleAttCng[4].m_bvisible);
  sub_4422E0(&this->me_Role[2].m_RoleAttCng[5].m_bvisible);
  sub_4422E0(&this->me_Role[2].m_RoleAttCng[6].m_bvisible);
  sub_4422E0(&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
  sub_4422E0(&this->me_Role[2].m_RoleAttCng[9].pDebugTex);
  sub_4422E0(&this->me_Role[2].m_RoleAttEqual[0].pDebugTex);
  sub_4422E0(&this->me_Role[2].m_RoleAttEqual[1].pDebugTex);
  sub_4422E0(&this->me_Role[2].m_RoleAttEqual[2].pDebugTex);
  sub_4422E0(&this->me_Role[2].m_RoleAttEqual[3].pDebugTex);
  sub_4422E0(&this->me_Role[2].m_RoleAttEqual[4].pDebugTex);
  sub_4422E0(&this->me_Role[2].m_RoleAttEqual[5].pDebugTex);
  sub_4422E0(&this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11]);
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->UpdateKeyCtrl();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  ((ARC_PlayerAtt *)&this->me_Role[3].m_Qi.m_rect.top)->Refresh();
  ((ARC_PlayerAtt *)&this->me_Role[3].m_RoleAtt[3].m_ratioh)->Refresh();
  ((ARC_PlayerAtt *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh)->Refresh();
  ((UIProgressBar *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh)->ctor();
  LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) = 0;
  this->me_Role[3].m_RoleAttEqual[3].m_texty = 0;
  this->me_Role[3].m_RoleAttEqual[3].m_textx = 0;
  this->me_Role[3].m_RoleAttEqual[3].m_text[8] = 0;
  *(_DWORD *)&this->me_Role[3].m_RoleAttEqual[3].m_text[4] = 0;
  *(_DWORD *)this->me_Role[3].m_RoleAttEqual[3].m_text = 0;
  this->bkWndX = 800;
  this->bkWndY = 600;
  this->j = 0;
  this->i = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] = 0;
  this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)-1;
  this->me_Role[2].m_RoleAttCng[2].m_pbkInfo = 0;
  memset(&this->me_Role[2].m_RoleAttCng[1].m_pbkInfo, 0, 0x60u);
  LOWORD(this->me_Role[2].m_RoleAttCng[2].m_benable) = 0;
  BYTE2(this->me_Role[2].m_RoleAttCng[2].m_benable) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_align = 0;
  this->me_Role[2].m_RoleAttCng[2].m_ratiow = 0.0;
  this->me_Role[2].m_RoleAttCng[2].m_ratioh = 0.0;
  this->me_Role[2].m_RoleAttCng[2].m_textx = 0;
  this->me_Role[2].m_RoleAttCng[2].m_texty = 0;
  this->me_Role[2].m_RoleAttCng[2].m_fonttype = 0;
  this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 0;
  *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) = 1;
  return (int)this;
}

// 0x00479680
void MainEquipUI::ctor()
{
  ((PalScript *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh)->PalScript_Init();
  ((UIRoleDialog *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh)->_UIRoleDialog();
  ((UIRoleDialog *)&this->me_Role[3].m_RoleAtt[3].m_ratioh)->_UIRoleDialog();
  ((UIRoleDialog *)&this->me_Role[3].m_Qi.m_rect.top)->_UIRoleDialog();
  ((UICaption *)&this->me_Role[3].m_ShenBar.m_decorateRc)->Destroy2();
  ((UICaption *)&this->me_Role[3].m_JingVal.m_pfather)->Destroy2();
  ((UICaption *)&this->me_Role[3].m_Jing.m_textx)->Destroy2();
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->DeleteRow();
  ((UIFrameWnd *)&this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttEqual[5].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttEqual[4].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttEqual[3].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttEqual[2].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttCng[9].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)&this->me_Role[2].m_RoleAttCng[8].m_bvisible)->ctor();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttCng[6].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttCng[5].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttCng[4].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[2].m_RoleAttCng[3].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)&this->me_Role[2].m_RoleAttCng[2].m_ppicInfo)->ctor();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00479890
int MainEquipUI::InitMainEquipUI(int arg0)
{
  LONG bkWndY; // ecx
  gbTexture *pDebugTex; // edx
  gbTexture *v5; // edx
  _PlugInfo *m_ppicInfo; // edx
  int v7; // edx
  LONG v8; // edx
  int m_bvisible; // edx
  gbTexture *v10; // edx
  gbTexture *v11; // edx
  gbTexture *v12; // edx
  gbTexture *v13; // edx
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  gbTexture *v19; // eax
  UIScene *v20; // edi
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  gbTexture **p_pDebugTex; // edi
  int v25; // ebp
  int v26; // ecx
  int v27; // eax
  int m_textx; // edx
  int v29; // edx
  int v30; // ecx
  int v31; // ecx
  LONG left; // eax
  int v33; // edx
  int v34; // edx
  int v35; // ecx
  gbTexture *v36; // edx
  unsigned int Color; // edx
  UIWnd *v38; // ecx
  LONG top; // edx
  int result; // eax
  float v41; // [esp+D0h] [ebp-F4h]
  int v42; // [esp+E0h] [ebp-E4h]
  int v43; // [esp+E4h] [ebp-E0h] BYREF
  int v44; // [esp+E8h] [ebp-DCh]
  int v45; // [esp+ECh] [ebp-D8h]
  int v46; // [esp+F0h] [ebp-D4h]
  int v47; // [esp+F4h] [ebp-D0h] BYREF
  int v48; // [esp+F8h] [ebp-CCh]
  int v49; // [esp+FCh] [ebp-C8h]
  int v50; // [esp+0x100] [ebp-C4h]
  _DWORD v51[2]; // [esp+0x104] [ebp-C0h] BYREF
  int v52; // [esp+0x10C] [ebp-B8h]
  int v53; // [esp+0x110] [ebp-B4h]
  int v54; // [esp+0x114] [ebp-B0h] BYREF
  int v55; // [esp+0x118] [ebp-ACh]
  int v56; // [esp+0x11C] [ebp-A8h]
  int v57; // [esp+0x120] [ebp-A4h]
  int p_DWORD; // [esp+0x124] [ebp-A0h] BYREF
  int v59; // [esp+0x128] [ebp-0x9C]
  int nHeight; // [esp+0x12C] [ebp-0x98]
  int v61; // [esp+0x130] [ebp-0x94]
  int nVal[2]; // [esp+0x134] [ebp-0x90] BYREF
  int v63; // [esp+0x13C] [ebp-0x88]
  int v64; // [esp+0x140] [ebp-0x84]
  _DWORD v65[2]; // [esp+0x144] [ebp-0x80] BYREF
  int v66; // [esp+0x14C] [ebp-0x78]
  int v67; // [esp+0x150] [ebp-0x74]
  int v68; // [esp+0x154] [ebp-0x70] BYREF
  int v69; // [esp+0x158] [ebp-0x6C]
  int v70; // [esp+0x15C] [ebp-0x68]
  int v71; // [esp+0x160] [ebp-0x64]
  int v72; // [esp+0x164] [ebp-0x60] BYREF
  int v73; // [esp+0x168] [ebp-0x5C]
  int v74; // [esp+0x16C] [ebp-0x58]
  int v75; // [esp+0x170] [ebp-0x54]
  _DWORD v76[4]; // [esp+0x174] [ebp-0x50] BYREF
  _DWORD v77[4]; // [esp+0x184] [ebp-0x40] BYREF
  gbVec3D pDir; // [esp+0x194] [ebp-0x30] BYREF
  int v79; // [esp+0x1A0] [ebp-0x24]
  _DWORD v80[4]; // [esp+0x1A4] [ebp-0x20] BYREF
  gbVec3D pPos; // [esp+0x1B4] [ebp-0x10] BYREF
  int v82; // [esp+0x1C0] [ebp-0x4]

  bkWndY = this->bkWndY;
  this->rc.top = 0;
  this->rc.left = 0;
  this->rc.right = this->bkWndX;
  this->rc.bottom = bkWndY;
  ((UIListBox *)this)->SetSelTexture(-1, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom, 0);
  pDebugTex = this->me_Role[2].m_RoleAttEqual[3].pDebugTex;
  *((_DWORD *)this + 52251) = arg0;
  v65[1] = 0;
  v65[0] = 0;
  v66 = 14;
  v67 = 600;
  (*((void ( **)(gbTexture **, int, _DWORD *, MainEquipUI *))pDebugTex + 4))(
    &this->me_Role[2].m_RoleAttEqual[3].pDebugTex,
    4353,
    v65,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttEqual[3].pDebugTex)->CreateFromTemplate();
  v5 = this->me_Role[2].m_RoleAttEqual[4].pDebugTex;
  v65[0] = 786;
  v66 = 800;
  (*((void ( **)(gbTexture **, int, _DWORD *, MainEquipUI *))v5 + 4))(
    &this->me_Role[2].m_RoleAttEqual[4].pDebugTex,
    4353,
    v65,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttEqual[4].pDebugTex)->CreateFromTemplate();
  m_ppicInfo = this->me_Role[2].m_RoleAttCng[2].m_ppicInfo;
  v80[1] = 565;
  v80[0] = 0;
  v80[2] = 800;
  v80[3] = 600;
  (*(void ( **)(_PlugInfo **, int, _DWORD *, char *, _DWORD, MainEquipUI *))&m_ppicInfo->name[24])(
    &this->me_Role[2].m_RoleAttCng[2].m_ppicInfo,
    4353,
    v80,
    "UI\\Flex\\framebar.tga",
    0,
    this);
  ((CScreenMode *)&this->me_Role[2].m_RoleAttCng[2].m_ppicInfo)->SetPosition(30,   35);
  v7 = this->bkWndY;
  this->rc.top = 0;
  this->rc.left = 0;
  v8 = this->rc.top + v7;
  this->rc.right = this->bkWndX;
  this->rc.bottom = v8;
  m_bvisible = this->me_Role[2].m_RoleAttCng[3].m_bvisible;
  v76[1] = 6;
  v76[0] = 220;
  v76[2] = 348;
  v76[3] = 134;
  (*(void ( **)(int *, int, _DWORD *, MainEquipUI *))(m_bvisible + 16))(
    &this->me_Role[2].m_RoleAttCng[3].m_bvisible,
    4353,
    v76,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttCng[3].m_bvisible)->CreateFromTemplate();
  v10 = this->me_Role[2].m_RoleAttCng[9].pDebugTex;
  v44 = 132;
  v43 = 80;
  v45 = 312;
  v46 = 546;
  (*((void ( **)(gbTexture **, int, int *, MainEquipUI *))v10 + 4))(
    &this->me_Role[2].m_RoleAttCng[9].pDebugTex,
    4353,
    &v43,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttCng[9].pDebugTex)->CreateFromTemplate();
  v11 = this->me_Role[2].m_RoleAttEqual[0].pDebugTex;
  v44 = 380;
  v43 = 92;
  v45 = 312;
  v46 = 508;
  (*((void ( **)(gbTexture **, int, int *, MainEquipUI *))v11 + 4))(
    &this->me_Role[2].m_RoleAttEqual[0].pDebugTex,
    4353,
    &v43,
    this);
  ((UIScene *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex)->SetShow(0);
  v12 = this->me_Role[2].m_RoleAttEqual[1].pDebugTex;
  v44 = 510;
  v43 = 92;
  v45 = 312;
  v46 = 542;
  (*((void ( **)(gbTexture **, int, int *, MainEquipUI *))v12 + 4))(
    &this->me_Role[2].m_RoleAttEqual[1].pDebugTex,
    4353,
    &v43,
    this);
  ((UIScene *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex)->SetShow(0);
  v13 = this->me_Role[2].m_RoleAttEqual[2].pDebugTex;
  v44 = 150;
  v43 = 265;
  v45 = 281;
  v46 = 182;
  (*((void ( **)(gbTexture **, int, int *, MainEquipUI *))v13 + 4))(
    &this->me_Role[2].m_RoleAttEqual[2].pDebugTex,
    4353,
    &v43,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttEqual[2].pDebugTex)->CreateFromTemplate();
  v14 = this->me_Role[2].m_RoleAttCng[4].m_bvisible;
  *((_DWORD *)this + 52248) = 168;
  *((_DWORD *)this + 52247) = 168;
  *((_DWORD *)this + 52249) = 268;
  *((_DWORD *)this + 52250) = 328;
  v48 = 426;
  v47 = 368;
  v49 = 398;
  v50 = 545;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v14 + 16))(
    &this->me_Role[2].m_RoleAttCng[4].m_bvisible,
    4353,
    &v47,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttCng[4].m_bvisible)->CreateFromTemplate();
  v15 = this->me_Role[2].m_RoleAttCng[5].m_bvisible;
  v47 = v49;
  v49 += 256;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v15 + 16))(
    &this->me_Role[2].m_RoleAttCng[5].m_bvisible,
    4353,
    &v47,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttCng[5].m_bvisible)->CreateFromTemplate();
  v16 = this->me_Role[2].m_RoleAttCng[6].m_bvisible;
  v47 = v49;
  v49 += 32;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v16 + 16))(
    &this->me_Role[2].m_RoleAttCng[6].m_bvisible,
    4353,
    &v47,
    this);
  ((UIStatic *)&this->me_Role[2].m_RoleAttCng[6].m_bvisible)->CreateFromTemplate();
  v17 = this->me_Role[2].m_RoleAttCng[7].m_bvisible;
  v48 = 428;
  v47 = 395;
  v49 = 677;
  v50 = 556;
  (*(void ( **)(int *, int, int *, MainEquipUI *))(v17 + 16))(
    &this->me_Role[2].m_RoleAttCng[7].m_bvisible,
    4374,
    &v47,
    this);
  ((UIScene *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetShow(0);
  sub_446010(&this->me_Role[2].m_RoleAttCng[7].m_bvisible);
  v18 = this->me_Role[2].m_RoleAttCng[8].m_bvisible;
  v77[1] = v50 - 46;
  v77[0] = v49 - 40;
  v77[3] = v50 - 46 + 32;
  v77[2] = v49 - 40 + 24;
  this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
  (*(void ( **)(int *, int, _DWORD *, MainEquipUI *))(v18 + 16))(
    &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
    2,
    v77,
    this);
  ((UIScene *)&this->me_Role[2].m_RoleAttCng[8].m_bvisible)->LoadResource("ui\\scene\\page");
  ((UIScene *)&this->me_Role[2].m_RoleAttCng[8].m_bvisible)->SetController(0x40000000);
  (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
    &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
    0);
  v19 = this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11];
  v73 = 20;
  v72 = 342;
  v74 = 715;
  v75 = 414;
  (*((void ( **)(gbTexture **, int, int *, MainEquipUI *))v19 + 4))(
    &this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11],
    4371,
    &v72,
    this);
  ((UIStatic *)&this->me_Role[2].m_EquipCloth.m_texarray.m_ptex[11])->CreateFromTemplate();
  v51[0] = v72 + 18;
  v51[1] = v73 + 16;
  v52 = v72 + 126;
  v53 = v73 + 48;
  v20 = (UIScene *)&this->me_Role[2].m_EquipCloth.m_caption[100];
  v42 = 4;
  do
  {
// [VFTABLE] ((void ( *)(UIScene *, int, _DWORD *, MainEquipUI *))v20->__vftable->Create)(v20, 4371, v51, this);
    ((UIScene *)v20)->SetShow(0);
    v20 = (UIScene *)((char *)v20 + 152);
    --v42;
  }
  while ( v42 );
  ((UICaption *)&this->me_Role[2].m_EquipCloth.m_caption[100])->SetEnable((int)dword_DC673C, 0);
  v51[0] = v52;
  v52 += 64;
  sub_445FA0(&this->me_Role[2].m_EquipShoes.m_texarray.m_ptex[1]);
  ((UICaption *)&this->me_Role[2].m_EquipShoes.m_texarray.m_ptex[1])->SetEnable((int)dword_DC373C, 0);
  v51[0] = v52 - 26;
  v52 = v52 - 26 + 108;
  sub_445FA0(&this->me_Role[2].m_EquipShoes.m_caption[60]);
  ((UICaption *)&this->me_Role[2].m_EquipShoes.m_caption[60])->SetEnable((int)dword_DC683C, 0);
  v51[0] = v52;
  v52 += 64;
  sub_445FA0(&this->me_Role[2].m_EquipAdorn1.m_benable);
  ((UICaption *)&this->me_Role[2].m_EquipAdorn1.m_benable)->SetEnable((int)dword_DC373C, 0);
  v21 = 667;
  LODWORD(pPos.z) = 689;
  LODWORD(pDir.z) = 689;
  v22 = *((_DWORD *)this + 52251);
  v23 = *(_DWORD *)&this->me_Role[2].m_EquipAdorn1.m_caption[20];
  v59 = 68;
  p_DWORD = 362;
  nHeight = 698;
  v61 = 368;
  LODWORD(pPos.y) = 83;
  LODWORD(pPos.x) = 667;
  v82 = 109;
  LODWORD(pDir.y) = 326;
  LODWORD(pDir.x) = 667;
  v79 = 352;
  LOBYTE(v21) = *(_BYTE *)(v22 + 4000);
  (*(void ( **)(char *, int, int *, MainEquipUI *, _DWORD, int, int))(v23 + 28))(
    &this->me_Role[2].m_EquipAdorn1.m_caption[20],
    4359,
    &p_DWORD,
    this,
    0,
    1,
    v21);
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", 0);
  this->me_Role[3].m_Jing.m_childs.m_pData = (char *)-8;
  this->me_Role[3].m_Jing.m_childs.capacity = -8;
  this->me_Role[3].m_Jing.m_childs.m_nSize = 14;
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100])->ShowEffect(v59 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100])->SetSelection(27);
  ((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100])->SetCurPlayer(5);
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetLockSel();
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetFirstShow((int)"Bone", 111);
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetFirstShow((int)"Smelt", 111);
  ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((CCBUI *)&this->me_Role[2].m_EquipAdorn1.m_caption[100])->VirtualCall();
  v68 = p_DWORD;
  v70 = p_DWORD + 333;
  v69 = v59 + 2;
  v71 = v59 + 31;
  p_pDebugTex = &this->me_Role[2].m_RoleAttEqual[6].pDebugTex;
  v25 = 10;
  do
  {
    // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, int, int *, MainEquipUI *))&(*p_pDebugTex)->0 + 4))(
      // [VTBL_DISPATCH]   p_pDebugTex,
      // [VTBL_DISPATCH]   4371,
      // [VTBL_DISPATCH]   &v68,
      // [VTBL_DISPATCH]   this);
    ((UIStatic *)p_pDebugTex)->CreateFromTemplate();
    p_pDebugTex += 38;
    v69 = v71;
    --v25;
    v71 += 29;
  }
  while ( v25 );
  v27 = *((_DWORD *)this + 52251);
  m_textx = this->me_Role[3].m_Jing.m_textx;
  v55 = 570;
  v54 = 206;
  v56 = 298;
  v57 = 596;
  LOBYTE(v26) = *(_BYTE *)(v27 + 4000);
  (*(void ( **)(int *, int, int *, MainEquipUI *, char *, _DWORD, int))(m_textx + 28))(
    &this->me_Role[3].m_Jing.m_textx,
    4372,
    &v54,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v26);
  ((PalScript *)&this->me_Role[3].m_Jing.m_textx)->OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnYes.tga", *(_BYTE *)(*((_DWORD *)this + 52251) + 4000));
  v29 = v56;
  v30 = *((_DWORD *)this + 52251);
  v54 = v56 + 204;
  v56 += 296;
  LOBYTE(v29) = *(_BYTE *)(v30 + 4000);
  ((void ( *)(UIWnd **, int, int *, MainEquipUI *, char *, _DWORD, int))this->me_Role[3].m_JingVal.m_pfather->m_rect.bottom)(
    &this->me_Role[3].m_JingVal.m_pfather,
    4373,
    &v54,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v29);
  ((PalScript *)&this->me_Role[3].m_JingVal.m_pfather)->OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnNo.tga", *(_BYTE *)(*((_DWORD *)this + 52251) + 4000));
  v31 = *((_DWORD *)this + 52251);
  left = this->me_Role[3].m_ShenBar.m_decorateRc.left;
  v55 = 549;
  v54 = 762;
  v56 = 800;
  v57 = 597;
  LOBYTE(v33) = *(_BYTE *)(v31 + 4000);
  (*(void ( **)(tagRECT *, int, int *, MainEquipUI *, char *, _DWORD, int))(left + 28))(
    &this->me_Role[3].m_ShenBar.m_decorateRc,
    4354,
    &v54,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    0,
    v33);
  ((PalScript *)&this->me_Role[3].m_ShenBar.m_decorateRc)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnExit.tga", *(_BYTE *)(*((_DWORD *)this + 52251) + 4000));
  ((CCBFiveNimbusWindow *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh)->CreateScriptAndCamera((int)&g_PlayerAttBuffer2.Remark[228], (int)this);
  this->me_Role[3].m_RoleAttEqual[2].m_fontcolor.Color = 0;
  this->me_Role[3].m_RoleAttEqual[1].m_nTextW = 1;
  ((CCBFiveNimbusWindow *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh)->SetFloatParam(210.0);
  ((Camera *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh)->UpdateCameraLookAt(198, 264, 600);
  ((UIPushButton *)&this->me_Role[3].m_RoleAttEqual[1].m_ratioh)->SetAnimOffset(1, 0, v41);
  nVal[0] = 300;
  v64 = 300;
  nVal[1] = 200;
  v63 = 500;
  ((ARC_PlayerAtt *)&this->me_Role[3].m_Qi.m_rect.top)->Create((int)&g_PlayerAttBuffer2.Remark[4], (int)nVal);
  ((UIItem *)&this->me_Role[3].m_Qi.m_rect.top)->SetData(31);
  v34 = *(_DWORD *)&this->me_Role[3].m_Qi.m_text[4];
  this->me_Role[3].m_Qi.m_ppic = (gbTexture *)(*(_DWORD *)&this->me_Role[3].m_Qi.m_text[8] + 14);
  v35 = *(_DWORD *)&this->me_Role[3].m_Qi.m_text[12];
  this->me_Role[3].m_Qi.m_pbkInfo = (_PlugInfo *)(v34 + 8);
  v36 = (gbTexture *)((char *)this->me_Role[3].m_Qi.m_pbk - 38);
  this->me_Role[3].m_Qi.m_ppicInfo = (_PlugInfo *)(v35 - 6);
  this->me_Role[3].m_RoleAtt[3].m_bvisible = 2;
  this->me_Role[3].m_RoleAtt[3].m_benable = 8;
  this->me_Role[3].m_Qi.m_disablepic = v36;
  sub_445FA0(&this->me_Role[3].m_QiVal.m_ratioh);
  ((ARC_PlayerAtt *)&this->me_Role[3].m_RoleAtt[3].m_ratioh)->Create((int)&g_PlayerAttBuffer2.Remark[228], (int)nVal);
  ((UIItem *)&this->me_Role[3].m_RoleAtt[3].m_ratioh)->SetData(31);
  Color = this->me_Role[3].m_RoleAtt[4].m_wndcolor.Color;
  this->me_Role[3].m_RoleAtt[4].m_rect.bottom = (LONG)this->me_Role[3].m_RoleAtt[4].m_id + 14;
  v38 = (UIWnd *)(this->me_Role[3].m_RoleAtt[4].m_rect.left - 6);
  this->me_Role[3].m_RoleAtt[4].m_rect.right = Color + 8;
  top = this->me_Role[3].m_RoleAtt[4].m_rect.top;
  this->me_Role[3].m_RoleAttCng[2].m_bvisible = 2;
  this->me_Role[3].m_RoleAttCng[2].m_benable = 8;
  this->me_Role[3].m_RoleAtt[4].m_pfather = v38;
  this->me_Role[3].m_RoleAtt[4].m_childs.m_pData = (char *)(top - 38);
  sub_445FA0(&this->me_Role[3].m_RoleAtt[6].m_ratioh);
  v63 += 100;
  v64 += 100;
  ((ARC_PlayerAtt *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh)->Create((int)&g_PlayerAttBuffer2.Remark[228], (int)nVal);
  ((UIItem *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh)->SetData(31);

  this->me_Role[3].m_RoleAttEqual[3].m_FVF = 0;
  this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)-1;
  return result;
}

// 0x0047A580
void MainEquipUI::ValidateRoles()
{
  unsigned int v2; // esi
  _DWORD *v3; // eax
  char *v4; // edx
  int v5; // edx
  unsigned int v6; // esi
  int *v7; // eax
  int *v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  _PlugInfo **v14; // edx
  char *v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int v21; // edi
  int v22; // ecx
  int v23; // eax
  UIListBox *v24; // ebx
  _BYTE pOut[12]; // [esp+0x10] [ebp-0xC] BYREF

  memset(&this->m_IsMsg, 0, 0x4A4u);
  memset(&this->m_OutFrameL.m_childs.m_nSize, 0, 0x4A4u);
  memset(this->stp_Magic.m_texarrayInfo, 0, 0x4A4u);
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8] = 0;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] = 0;
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(3);
  this->i = 0;
  v2 = 0;
  if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
  {
    do
    {
      v3 = ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v2);
      v4 = &this->buf[12 * this->i + 256];
      *(_DWORD *)v4 = *v3;
      *((_DWORD *)v4 + 1) = v3[1];
      *((_DWORD *)v4 + 2) = v3[2];
      v5 = this->i + 1;
      ++*(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4];
      this->i = v5;
      v2 = v5;
    }
    while ( v5 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
  }
  ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(10);
  this->i = 0;
  v6 = 0;
  if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
  {
    do
    {
      v7 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, v6);
      v8 = &this->m_OutFrameL.m_childs.m_nSize + 3 * this->i;
      *v8 = *v7;
      v8[1] = v7[1];
      v8[2] = v7[2];
      v9 = this->i + 1;
      ++*(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8];
      this->i = v9;
      v6 = v9;
    }
    while ( v9 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
  }
  v10 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8];
  this->i = 0;
  if ( v10 > 0 )
  {
    do
    {
      v11 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4];
      this->j = 0;
      if ( v11 > 0 )
      {
        do
        {
          v12 = *(&this->m_OutFrameL.m_bcreateok + 3 * this->i);
          if ( *(_DWORD *)(v12 + 776) == *(_DWORD *)&this->buf[12 * this->j + 256] )
          {
            this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]] = *(_PlugInfo **)(v12 + 780);
            this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 2] = (_PlugInfo *)((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum((int)this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]]);
            this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 1] = (_PlugInfo *)1;
            *(&this->m_GameMoney.m_bcreateok + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = (int)this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]];
            lstrcpyA(
              (LPSTR)&this->stp_Effect.m_disablepicInfo + 796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12],
              this->stp_Magic.m_texarrayInfo[3 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 2]->name);
            *((_DWORD *)&this->m_DlgEx.m_static.m_pbkInfo + 199
                                                          * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = *(_DWORD *)&this->buf[12 * this->j + 256];
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 12] = *(_DWORD *)&this->m_Is[12 * this->j + 3];
            lstrcpyA(
              (LPSTR)&this->m_DlgEx.76 + 796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 76,
              (LPCSTR)(*(&this->m_SelNum + 3 * this->j) + 4));
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 16] = *(&this->m_OutFrameL.m_childs.m_nSize + 3 * this->i);
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 8] = *(&this->m_OutFrameL.m_childs.m_needscriptdel + 3 * this->i);
            lstrcpyA(
              (LPSTR)&this->m_GameMoney.m_bvisible + 796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12],
              (LPCSTR)(*(&this->m_OutFrameL.m_bcreateok + 3 * this->i) + 4));
            *((_DWORD *)&this->m_DlgEx.m_static.m_ppic + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = this->i;
            *((_DWORD *)&this->m_DlgEx.m_static.m_ppicInfo
            + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12]) = this->j;
            qmemcpy(
              &this->m_btnPar2[2][4]._texName[796 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] + 80],
              &this->stp_Effect.m_disablepicInfo + 199 * *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12],
              0x31Cu);
            v13 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
            v14 = &this->stp_Magic.m_texarrayInfo[3 * v13];
            v15 = &this->stp_BattleArray.m_caption[12 * v13 + 128];
            *(_DWORD *)v15 = *v14;
            *((_DWORD *)v15 + 1) = v14[1];
            *((_DWORD *)v15 + 2) = v14[2];
            ++*(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
          }
          v16 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[4];
          v17 = this->j + 1;
          this->j = v17;
        }
        while ( v17 < v16 );
      }
      v18 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[8];
      v19 = this->i + 1;
      this->i = v19;
    }
    while ( v19 < v18 );
  }
  if ( *(int *)&this->me_Role[2].m_RoleAttCng[2].m_text[12] <= 0 )
  {
    this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)5;
    ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)dword_DD9D3C, 0);
    (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
      &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
      1);
  }
  v20 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
  this->i = 0;
  if ( v20 > 0 )
  {
    do
    {
      v21 = ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetItemOffset((char *)&this->m_GameMoney.m_bvisible + 796 * this->i, 0);
      sprintf(this->buf, &dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 8]);
      ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(1, v21, this->buf, 0);
      sprintf(this->buf, byte_5967B0, (char *)&this->m_DlgEx.76 + 796 * this->i + 76);
      ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(2, v21, this->buf, 0);
      sprintf(this->buf, &dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 12]);
      ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(3, v21, this->buf, 0);
      v22 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
      v23 = this->i + 1;
      this->i = v23;
    }
    while ( v23 < v22 );
  }
  ((LineupUI *)this)->CountVisibleItems(0);
  v24 = (UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20];
  ((UIListBox *)v24)->GetItem();
  ((UIListBox *)v24)->GetItem();
}

// 0x0047AAB0
int MainEquipUI::UpdateLayout()
{
  void **v2; // esi
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int *v7; // edx
  char *v8; // ecx
  int result; // eax
  int v10; // [esp-0x4] [ebp-0x2C]
  int v11; // [esp+0x10] [ebp-0x18] BYREF
  int v12; // [esp+0x14] [ebp-0x14]
  int SkillNum; // [esp+0x18] [ebp-0x10]
  _DWORD p_DWORD[3]; // [esp+0x1C] [ebp-0xC] BYREF
  int v15; // [esp+0x2C] [ebp+0x4]
  void **v16; // [esp+0x2C] [ebp+0x4]

  if ( v15 >= 0 )
  {
// [VFTABLE] v16 = &this->__vftable + 199 * v15;
    v2 = v16;
    v16[1472] = (void *)((char *)v16[1472] - 1);
    v3 = (int)&v16[1471][-1].OnMessage + 3;
    v16[1471] = (void *)v3;
    if ( (int)v16[1472] < 0 || v3 < 0 )
    {
      v16[1472] = 0;
      v16[1471] = 0;
      sprintf(this->buf, "\\n      %s", (const char *)dword_DD943C);
      ((UICaption *)&this->me_Role[3].m_RoleAtt[6].m_ratioh)->SetEnable((int)this->buf, 0);
      return ((UIRoleSelect *)&this->me_Role[3].m_RoleAtt[3].m_ratioh)->SetByte(1);
    }
    else
    {
      this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 0;
      v10 = (int)v16[1473];
      v11 = 0xFFFF;
      v12 = 0;
      SkillNum = 0;
      p_DWORD[0] = v10;
      p_DWORD[1] = 1;
      p_DWORD[2] = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v10);
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(p_DWORD);
      v11 = (int)v16[1474];
      v12 = 1;
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v11);
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&v11);
      v4 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
      ++this->me_Role[3].m_RoleAttEqual[3].m_FVF;
      this->i = 0;
      if ( v4 > 0 )
      {
        do
        {
          if ( *((void **)&this->m_DlgEx.m_static.m_pbkInfo + 199 * this->i) == v2[1474] )
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 12] = v2[1472];
          if ( *(void **)&this->m_DlgEx.m_static.m_text[796 * this->i + 16] == v2[1473] )
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 8] = v2[1471];
          sprintf(this->buf, byte_5967B0, &this->m_GameMoney.m_bvisible + 199 * this->i);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(0, this->i, this->buf, 0);
          sprintf(this->buf, &dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 8]);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(1, this->i, this->buf, 0);
          sprintf(this->buf, byte_5967B0, (char *)&this->m_DlgEx.76 + 796 * this->i + 76);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(2, this->i, this->buf, 0);
          sprintf(this->buf, &dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 12]);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(3, this->i, this->buf, 0);
          qmemcpy(
            &this->m_btnPar2[2][4]._texName[796 * this->i + 80],
            &this->stp_Effect.m_disablepicInfo + 199 * this->i,
            0x31Cu);
          v5 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
          v2 = v16;
          v6 = this->i + 1;
          this->i = v6;
        }
        while ( v6 < v5 );
      }
      v7 = (int *)((char *)this + 12 * ((_DWORD)v2[1475] + 129));
      this->me_Role[2].m_RoleAttCng[2].m_bfocus = *v7;
      this->me_Role[2].m_RoleAttCng[2].pDebugTex = (gbTexture *)v7[1];
      this->me_Role[2].m_RoleAttCng[2].m_align = v7[2];
      v8 = (char *)this + 12 * ((_DWORD)v2[1476] + 30);
      this->me_Role[2].m_RoleAttCng[2].m_ratiow = *(float *)v8;
      this->me_Role[2].m_RoleAttCng[2].m_ratioh = *((float *)v8 + 1);
      this->me_Role[2].m_RoleAttCng[2].m_textx = *((_DWORD *)v8 + 2);
      sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
      sub_445E50((int)&this->me_Role[3].m_Jing.m_textx);
      return sub_445E50((int)&this->me_Role[3].m_ShenBar.m_decorateRc);
    }
  }
  return result;
}

// 0x0047ADF0
int MainEquipUI::UpdateCompareLayout()
{
  int *v1; // esi
  void **v3; // esi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax
  int *v8; // [esp-0x8] [ebp-0x28]
  int *v9; // [esp-0x8] [ebp-0x28]
  int v10; // [esp+0x8] [ebp-0x18] BYREF
  int v11; // [esp+0xC] [ebp-0x14]
  int v12; // [esp+0x10] [ebp-0x10]
  int v13[2]; // [esp+0x14] [ebp-0xC] BYREF
  int SkillNum; // [esp+0x1C] [ebp-0x4]
  int v15; // [esp+0x24] [ebp+0x4]
  void **v16; // [esp+0x24] [ebp+0x4]

  if ( v15 >= 0 )
  {
    if ( this->me_Role[2].m_RoleAttCng[2].m_align && this->me_Role[2].m_RoleAttCng[2].m_textx )
    {
      v8 = v1;
      SkillNum = 0;
      v10 = 0xFFFF;
      v11 = 0;
      v12 = 0;
// [VFTABLE] v3 = &this->__vftable + 199 * v15;
      v3[1472] = (void *)((char *)v3[1472] + 1);
      v3[1471] = (void *)((char *)v3[1471] + 1);
      this->me_Role[2].m_RoleAttCng[2].m_align = 0;
      v16 = v3;
      this->me_Role[2].m_RoleAttCng[2].m_ratiow = 0.0;
      v13[1] = 1;
      this->me_Role[2].m_RoleAttCng[2].m_ratioh = 0.0;
      this->me_Role[2].m_RoleAttCng[2].m_textx = 0;
      this->me_Role[2].m_RoleAttCng[2].m_texty = 0;
      this->me_Role[2].m_RoleAttCng[2].m_fonttype = 0;
      v13[0] = (int)v3[1473];
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v13[0]);
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)v13, v8);
      v10 = (int)v3[1474];
      v11 = 1;
      v12 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v10);
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&v10, v9);
      v4 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
      this->i = 0;
      if ( v4 > 0 )
      {
        while ( 1 )
        {
          if ( *((void **)&this->m_DlgEx.m_static.m_pbkInfo + 199 * this->i) == v3[1474] )
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 12] = v3[1472];
          if ( *(void **)&this->m_DlgEx.m_static.m_text[796 * this->i + 16] == v3[1473] )
            *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 8] = v3[1471];
          sprintf(this->buf, byte_5967B0, &this->m_GameMoney.m_bvisible + 199 * this->i);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(0, this->i, this->buf, 0);
          sprintf(this->buf, &dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 8]);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(1, this->i, this->buf, 0);
          sprintf(this->buf, byte_5967B0, (char *)&this->m_DlgEx.76 + 796 * this->i + 76);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(2, this->i, this->buf, 0);
          sprintf(this->buf, &dir[20], *(_DWORD *)&this->m_DlgEx.m_static.m_text[796 * this->i + 12]);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->SetMouseMoveSel(3, this->i, this->buf, 0);
          qmemcpy(
            &this->m_btnPar2[2][4]._texName[796 * this->i + 80],
            &this->stp_Effect.m_disablepicInfo + 199 * this->i,
            0x31Cu);
          v5 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[2].m_text[12];
          v6 = this->i + 1;
          this->i = v6;
          if ( v6 >= v5 )
            break;
          v3 = v16;
        }
      }
      ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetItem();
      sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
      sub_445E50((int)&this->me_Role[3].m_Jing.m_textx);
      sub_445E50((int)&this->me_Role[3].m_ShenBar.m_decorateRc);
    }
    ((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
    ((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
    --this->me_Role[3].m_RoleAttEqual[3].m_FVF;
  }
  return result;
}

// 0x0047B140
void MainEquipUI::FormatItemPath(int nVal)
{
  char *buf; // ebx
  CHAR *v4; // ebp
  RoleAtt *v5; // ecx
  LPCSTR v6; // eax
  CHAR String1[253]; // [esp+0x10] [ebp-0x100] BYREF
  __int16 v8; // [esp+0x10D] [ebp-0x3]
  char v9; // [esp+0x10F] [ebp-0x1]

  buf = this->buf;
  sprintf(this->buf, g_szSceneUIText);
  memset(String1, 0, sizeof(String1));
  v8 = 0;
  v9 = 0;
  v4 = sub_458F70(&this->stp_Magic.m_texarrayInfo[3 * nVal + 2]->name[92], (int)asc_5B74B8, String1);
  if ( lstrlenA(v4) <= 0 )
  {
    ((RoleAtt *)v5)->FormatAttributeText();
    lstrcatA(buf, v6);
  }
  else
  {
    lstrcpyA(buf, v4);
  }
  ((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex)->SetEnable((int)buf, 0);
  ((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex)->SetEnable((int)String1, 0);
}

// 0x0047B200
void MainEquipUI::Render()
{
  int *p_m_nTextW; // esi
  int v3; // ebx
  int v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  CCBMagicWindow *v14; // [esp+0x14] [ebp-0x10]
  int v15; // [esp+0x18] [ebp-0xC]
  int v16; // [esp+0x1C] [ebp-0x8]
  int v17; // [esp+0x20] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v14);
  if ( this->me_Role[3].m_RoleAttEqual[3].m_mouseoff )
  {
    p_m_nTextW = &this->me_Role[3].m_RoleAttEqual[3].m_nTextW;
    v15 = 60;
    do
    {
// [IDA_MISID]       if ( ((Concurrency *)p_m_nTextW)->details::VirtualProcessor::IsThrottled() )
      {
        ((ScreenEffect *)p_m_nTextW)->Apply();
      }
      else
      {
        v3 = *((_DWORD *)this + 52247);
        v4 = *((_DWORD *)this + 52249) - v3;
        v5 = rand();
        v16 = *((_DWORD *)this + 52248);
        v17 = v3 + v5 % (v4 / 2);
        v6 = *((_DWORD *)this + 52250) - v16;
        ((RenderTarget *)p_m_nTextW)->LoadTexture(szFilename);
        ((RenderTarget *)p_m_nTextW)->SetSize(32);
        fY = rand() % 10 + 252;
        fX = rand() % 10 + 36;
        v7 = rand();
        ((RenderTarget *)p_m_nTextW)->SetColor(v7 % 10 - 37, fX, fY);
        v8 = rand();
        ((RenderTarget *)p_m_nTextW)->SetAlpha(v8 % 135 + 120);
        ((RenderTarget *)p_m_nTextW)->SetField084();
        ((RenderTarget *)p_m_nTextW)->SetState();
        fYa = (float)v16;
        fXa = (float)v17;
        ((RenderTarget *)p_m_nTextW)->UpdateTransform(fXa, fYa);
        ((RenderTarget *)p_m_nTextW)->CalcRenderDimensions(v4, v6);
        ((RenderTarget *)p_m_nTextW)->SetOffset(1092616192);
        rand();
        *(float *)&fXb = (float)(rand() % 8 + 2);
        ((RenderTarget *)p_m_nTextW)->SetScale(fXb);
        ((RenderTarget *)p_m_nTextW)->SetVisible(1);
      }
      p_m_nTextW += 146;
      --v15;
    }
    while ( v15 );
  }
}

// 0x0047B3B0
BOOL MainEquipUI::Render3DModel()
{
  int *v1; // ebp
  DWORD TickCount; // eax
  DWORD v4; // eax
  unsigned int v5; // ecx
  const char *v6; // ebp
  _PlugInfo *v7; // eax
  const char *v8; // ebp
  int m_align; // ecx
  int v10; // eax
  UICursor *v11; // ecx
  const char *v13; // [esp+0x8] [ebp-0x104]
  char Buffer[253]; // [esp+0xC] [ebp-0x100] BYREF
  __int16 v15; // [esp+0x109] [ebp-0x3]
  char v16; // [esp+0x10B] [ebp-0x1]
  int a2; // [esp+0x110] [ebp+0x4]
  int a3; // [esp+0x114] [ebp+0x8]

  if ( this->me_Role[3].m_RoleAttEqual[3].m_mouseoff )
  {
    if ( !LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) )
    {
      TickCount = GetTickCount();
      this->me_Role[3].m_RoleAttEqual[3].m_textx = TickCount;
      this->me_Role[3].m_RoleAttEqual[3].m_texty = TickCount;
      LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) = 1;
    }
    v4 = GetTickCount();
    v5 = v4 - this->me_Role[3].m_RoleAttEqual[3].m_texty;
    this->me_Role[3].m_RoleAttEqual[3].m_textx = v4;
    if ( v5 > 0x1388 )
    {
      this->me_Role[3].m_RoleAttEqual[3].m_texty = v4;
      LOBYTE(this->me_Role[3].m_RoleAttEqual[3].m_fonttype) = 0;
      this->FormatItemPath((int)this->me_Role[2].m_RoleAttCng[2].m_pbk);
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)this + 12 * (int)&this->me_Role[2].m_RoleAttCng[2].m_pbk[2].InFmt.a_mask, v1);
      if ( !strcmp(
              &this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2]->name[32],
              g_szSceneUIText) )
      {
        sprintf(this->buf, byte_5967B0, "NONE");
      }
      else
      {
        v6 = &this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2]->name[32];
        sprintf(this->buf, "Item\\%s\\%s.pol", v6, v6);
      }
      ((PalScript *)&this->me_Role[3].m_RoleAttEqual[2])->LoadModel(this->buf, 0);
      v7 = this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2];
      v8 = &v7->name[32];
      v13 = &v7->name[62];
      if ( !strcmp(&v7->name[32], g_szSceneUIText) )
      {
        sprintf(this->buf, byte_5967B0, "NONE");
      }
      else
      {
        memset(Buffer, 0, sizeof(Buffer));
        v15 = 0;
        v16 = 0;
        sprintf(Buffer, "%s%s", v8, v13);
        sprintf(this->buf, "Item\\%s\\%s.tga", v8, Buffer);
      }
      ((gbGeomNode *)this->me_Role[3].m_RoleAttEqual[2].m_rect.left)->ReplaceTexture(this->buf);
      m_align = this->me_Role[2].m_RoleAttCng[2].m_align;
      v10 = this->me_Role[2].m_RoleAttCng[2].m_textx + 4;
      this->me_Role[3].m_RoleAttEqual[2].m_fontcolor.Color = 1;
      sprintf(
        this->buf,
        &szFilename[36],
        byte_DCD03C,
        this->stp_Magic.m_texarrayInfo[3 * (int)this->me_Role[2].m_RoleAttCng[2].m_pbk + 2]->name,
        byte_DCD13C,
        m_align + 4,
        v10);
      ((UICaption *)&this->me_Role[3].m_RoleAttCng[5].m_ratioh)->SetEnable((int)this->buf, 0);
      ((UIRoleSelect *)&this->me_Role[3].m_RoleAttCng[2].m_ratioh)->SetByte(1);
      ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)dword_DD9A3C, 0);
      (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
        &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
        1);
      this->me_Role[2].m_RoleAttCng[2].m_ppic = 0;
      this->me_Role[2].m_RoleAttCng[2].m_bfocus = 0;
      this->me_Role[2].m_RoleAttCng[2].pDebugTex = 0;
      this->me_Role[2].m_RoleAttCng[2].m_align = 0;
      this->me_Role[2].m_RoleAttCng[2].m_ratiow = 0.0;
      this->me_Role[2].m_RoleAttCng[2].m_ratioh = 0.0;
      this->me_Role[2].m_RoleAttCng[2].m_textx = 0;
      ((LineupUI *)this)->CountVisibleItems((int)this->me_Role[2].m_RoleAttCng[2].m_pbk);
      sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
      sub_445E50((int)&this->me_Role[3].m_Jing.m_textx);
      sub_445E50((int)&this->me_Role[3].m_JingVal.m_pfather);
      sub_445E50((int)&this->me_Role[3].m_ShenBar.m_decorateRc);
      ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetItem();
      *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) = 1;
      this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 0;
      this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)-1;
      ((UICursor *)v11)->IRender();
    }
  }
  return ((UIListBox *)this)->Update(a2, a3);
}

// 0x0047B6C0
int MainEquipUI::OnMessage(int nVal, int nVal2, int nVal3)
{
  int result; // eax
  CScreenMode *Instance; // eax
  gbTexture *LockedSel; // eax
  gbTexture *v8; // eax
  CScreenMode *v9; // eax
  CScreenMode *v10; // eax
  CScreenMode *v11; // eax
  const char *v12; // [esp-0x8] [ebp-0x10]
  const char *v13; // [esp-0x8] [ebp-0x10]
  const void *v14; // [esp-0x8] [ebp-0x10]
  const void *v15; // [esp-0x8] [ebp-0x10]

  switch ( nVal )
  {
    case 1000:
      if ( !nVal2 || this->me_Role[2].m_RoleAttCng[2].m_ppic == (gbTexture *)5 )
        return 1;
      this->me_Role[2].m_RoleAttCng[2].m_ppic = 0;
      ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)dword_DD973C, 0);
      (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
        &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
        1);
      return 1;
    case 1001:
      if ( nVal2 == 4354 )
      {
        if ( this->me_Role[2].m_RoleAttCng[2].m_ppic == (gbTexture *)3 )
        {
          ((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
          ((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
          sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetItem();
          ((PAL3 *)*((PAL3 **)this + 52251))->DispatchModeCommand(0);
        }
        else
        {
          this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)3;
          ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)dword_DD9C3C, 0);
          (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
            &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
            1);
        }
        v13 = off_5BC90C;
        goto LABEL_24;
      }
      if ( nVal2 == 4372 )
      {
        if ( *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) )
        {
          LockedSel = (gbTexture *)((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetLockedSel();
          this->me_Role[2].m_RoleAttCng[2].m_pbk = LockedSel;
          if ( (int)LockedSel >= 0 )
          {

            ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)dword_DD983C, 0);
            (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
              &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
              1);
            this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)1;
            v13 = off_5BC90C;
          }
          else
          {
            v13 = g_pCScreenMode_5BC918;
          }
        }
        else
        {
          v13 = g_pCScreenMode_5BC918;
        }
        goto LABEL_24;
      }
      if ( nVal2 != 4373 )
        return 1;
      if ( !*(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) )
        goto LABEL_23;

      v12 = off_5BC90C;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v12, 1);
      ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)dword_DD993C, 0);
      (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
        &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
        1);
      this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)2;
      return 1;
    case 1008:
      if ( nVal2 == 4359 )
      {
        if ( *(&this->me_Role[3].m_RoleAttEqual[3].m_mouseoff + 1) )
        {
          v8 = (gbTexture *)((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetLockedSel();
          this->me_Role[2].m_RoleAttCng[2].m_pbk = v8;
          if ( (int)v8 >= 0 )
          {

            v14 = off_5BC914;
            v9 = CScreenMode::GetInstance();
            ((CScreenMode *)v9)->AudioSetPosition(v14, 1);
            ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)dword_DD983C, 0);
            (*(void ( **)(int *, int))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
              &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
              1);
            this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)1;
            return 1;
          }
        }
LABEL_23:
        v13 = g_pCScreenMode_5BC918;
LABEL_24:
        v10 = CScreenMode::GetInstance();
        ((CScreenMode *)v10)->AudioSetPosition(v13, 1);
      }
      return 1;
    case 1009:
      if ( nVal2 == 4359 )
      {
        this->me_Role[3].m_RoleAttEqual[2].m_fontcolor.Color = 0;
        this->me_Role[2].m_RoleAttCng[2].m_pbk = (gbTexture *)((NPC *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->CreateChild();
        ((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
        ((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
        ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)g_szSceneUIText, 0);
        (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
          &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
          0);
        if ( (int)this->me_Role[2].m_RoleAttCng[2].m_pbk >= 0 )
          this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 0;
        this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
        return 1;
      }
      if ( nVal2 != 4374 )
        return 1;
      switch ( (unsigned int)this->me_Role[2].m_RoleAttCng[2].m_ppic )
      {
        case 0u:
        case 2u:
          this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
          ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)g_szSceneUIText, 0);
          (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
            &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
            0);
          result = 1;
          break;
        case 1u:
          this->me_Role[2].m_RoleAttCng[2].m_ppic = (gbTexture *)-1;
          ((UICaption *)&this->me_Role[2].m_RoleAttCng[7].m_bvisible)->SetEnable((int)g_szSceneUIText, 0);
          (*(void ( **)(int *, _DWORD))this->me_Role[2].m_RoleAttCng[8].m_bvisible)(
            &this->me_Role[2].m_RoleAttCng[8].m_bvisible,
            0);
          ((RenderTarget *)this)->InitParticleRenders();
          sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
          sub_445E50((int)&this->me_Role[3].m_Jing.m_textx);
          sub_445E50((int)&this->me_Role[3].m_JingVal.m_pfather);
          sub_445E50((int)&this->me_Role[3].m_ShenBar.m_decorateRc);
          this->me_Role[3].m_RoleAttEqual[3].m_mouseoff = 1;
          v15 = off_5BC940;
          v11 = CScreenMode::GetInstance();
          ((CScreenMode *)v11)->AudioSetPosition(v15, 1);
          result = 1;
          break;
        case 3u:
          ((UICaption *)&this->me_Role[2].m_RoleAttEqual[0].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
          ((UICaption *)&this->me_Role[2].m_RoleAttEqual[1].pDebugTex)->SetEnable((int)g_szSceneUIText, 0);
          sub_445E50((int)&this->me_Role[2].m_EquipAdorn1.m_caption[20]);
          ((UIListBox *)&this->me_Role[2].m_EquipAdorn1.m_caption[20])->GetItem();
          ((PAL3 *)*((PAL3 **)this + 52251))->DispatchModeCommand(0);
          result = 1;
          break;
        default:
          return 1;
      }
      return result;
    default:
      return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
  }
}

// 0x0047EC00
// write access to const memory has been detected, the output may be wrong!
int MainEquipUI::ClearState()
{
  this->me_Role[2].m_Qi.m_fontcolor.Color = 0;
  this->me_Role[2].m_Qi.m_wndcolor.Color = 0;
  memset(&this->me_Role[2].m_Qi.m_id, 0, 0x18u);
  memset(&this->me_Role[2].m_Qi.m_childs, 0, 0x960u);
  this->me_Role[2].m_RoleAttCng[0].m_ratiow = 0.0;
  this->me_Role[2].m_RoleAttCng[0].m_align = 0;
  this->me_Role[2].m_RoleAttCng[0].m_bfocus = 0;
  this->me_Role[2].m_RoleAttCng[0].pDebugTex = 0;
  LOBYTE(this->me_Role[2].m_RoleAttCng[1].m_FVF) = 0;
  BYTE1(this->me_Role[2].m_RoleAttCng[1].m_FVF) = 0;
  this->me_Role[2].m_RoleAttCng[1].m_nTextW = -1;
// [VFTABLE] this->me_Role[2].m_RoleAttCng[2].__vftable = 0;
  memset32(&this->me_Role[2].m_RoleAttCng[1].m_ppic, (int)byte_1010101, 6u);
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  gbColorQuad::ColorQuadFmt = 1;
  BYTE2(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  BYTE1(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  HIBYTE(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = 0;
  return gbColorQuad::ColorQuadFmt;
}

// 0x0047ECB0
int MainEquipUI::CreateUI()
{
  int v2; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // eax
  gbTexture *v7; // edx
  float v8; // edi
  LONG v9; // ebx
  UIWnd *v10; // ecx
  Parent_Data *v11; // ecx
  int v12; // edi
  float v13; // eax
  void ( **m_id)(void **, char *, LONG *, MainEquipUI *, char *, float); // edx
  LONG v15; // edi
  int v16; // ebx
  int v17; // ecx
  char *v18; // ecx
  UIWnd *v19; // edi
  int v20; // eax
  int v21; // edx
  gbTexture *v22; // edi
  _PlugInfo *v23; // ebx
  int v24; // ecx
  _PlugInfo *v25; // ecx
  gbTexture *v26; // eax
  gbTexture *v27; // edi
  int m_alpha; // edx
  gbTexture *v29; // edi
  _PlugInfo *v30; // ebx
  float v31; // ecx
  char *v32; // ecx
  gbTexture *v33; // eax
  gbTexture *v34; // edi
  int m_bvisible; // edx
  int v36; // edi
  Parent_Data *v37; // ebx
  UIWnd *v38; // ecx
  unsigned int v39; // ecx
  void *v40; // edi
  void *v41; // eax
  gbTexture *m_pbk; // edx
  unsigned int v43; // edx
  _PlugInfo *v44; // edi
  gbTexture *v45; // ebx
  _PlugInfo *v46; // ebp
  unsigned int v47; // eax
  LONG v48; // edx
  LONG left; // ecx
  int m_bcreateok; // eax
  int v51; // eax
  int v52; // edx
  int v53; // eax
  int *p_m_bcreateok; // edi
  int v55; // ebx
  int v56; // eax
  int *v57; // edi
  int v58; // ebx
  int v59; // eax
  int v60; // edx
  UIScene *v61; // edi
  int v62; // ecx
  char *v63; // ebx
  int v64; // edx
  bool v65; // zf
  LONG v66; // ecx
  int v67; // edx
  gbTexture *v68; // eax
  int v70; // [esp+0x110] [ebp-0x44]
  LONG v71; // [esp+0x114] [ebp-0x40] BYREF
  _PlugInfo *v72; // [esp+0x118] [ebp-0x3C]
  UIWnd *v73; // [esp+0x11C] [ebp-0x38]
  char *v74; // [esp+0x120] [ebp-0x34]
  int v75; // [esp+0x124] [ebp-0x30] BYREF
  int v76; // [esp+0x128] [ebp-0x2C]
  int v77; // [esp+0x12C] [ebp-0x28]
  int v78; // [esp+0x130] [ebp-0x24]
  _DWORD v79[2]; // [esp+0x134] [ebp-0x20] BYREF
  int v80; // [esp+0x13C] [ebp-0x18]
  int v81; // [esp+0x140] [ebp-0x14]
  _DWORD v82[4]; // [esp+0x144] [ebp-0x10] BYREF

  v2 = this->rc.top + 368;
  v79[0] = this->rc.left + 68;
  v3 = v79[0] + 22;
  v80 = v79[0] + 22;
  LOBYTE(v3) = g_bDebugMode;
  v79[1] = v2;
  v81 = v2 + 36;
  (*(void ( **)(char *, char *, _DWORD *, MainEquipUI *, char *, _DWORD, int))(*(_DWORD *)&this->me_Role[1].m_EquipAdorn1.m_caption[68]
                                                                                       + 28))(
    &this->me_Role[1].m_EquipAdorn1.m_caption[68],
    &byte_A00604,
    v79,
    this,
    "UI\\GameMainUI\\JusticeBook\\Pgup",
    0,
    v3);
  ((PalScript *)&this->me_Role[1].m_EquipAdorn1.m_caption[68])->OpenScript("UI\\GameMainUI\\JusticeBook\\UnUp.tga", g_bDebugMode);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn1.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn1.m_caption[68],
    0);
  v4 = *(_DWORD *)&this->me_Role[1].m_EquipAdorn2.m_caption[68];
  v79[0] = v80 + 600;
  v80 += 622;
  v5 = v80;
  LOBYTE(v5) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, MainEquipUI *, char *, _DWORD, int))(v4 + 28))(
    &this->me_Role[1].m_EquipAdorn2.m_caption[68],
    &byte_A00605,
    v79,
    this,
    "UI\\GameMainUI\\JusticeBook\\Pgdw",
    0,
    v5);
  ((PalScript *)&this->me_Role[1].m_EquipAdorn2.m_caption[68])->OpenScript("UI\\GameMainUI\\JusticeBook\\UnDw.tga", g_bDebugMode);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn2.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn2.m_caption[68],
    0);
  v6 = this->rc.top + 86;
  v71 = this->rc.left + 706;
  v72 = (_PlugInfo *)v6;
  v6 += 25;
  v7 = this->me_Role[2].m_Head.m_texarray.m_ptex[3];
  v74 = (char *)v6;
  LOBYTE(v6) = g_bDebugMode;
  v73 = (UIWnd *)(v71 + 82);
  ((void ( *)(gbTexture **, char *, LONG *, MainEquipUI *, char *, int))v7->Height)(
    &this->me_Role[2].m_Head.m_texarray.m_ptex[3],
    &byte_A00606,
    &v71,
    this,
    "UI\\GameMainUI\\JusticeBook\\Gods",
    v6);
  v8 = *(float *)&v71;
  v9 = (LONG)v72;
  v10 = v73;
  this->me_Role[2].m_RoleAttCng[1].m_rect.right = v71;
  this->me_Role[2].m_RoleAttCng[1].m_rect.bottom = v9;
  this->me_Role[2].m_RoleAttCng[1].m_pfather = v10;
  v11 = (Parent_Data *)v74;
  this->me_Role[2].m_RoleAttCng[1].m_childs.m_pData = v74;
  this->me_Role[2].m_RoleAttCng[0].m_ratioh = v8;
  v12 = (int)v73;
  this->me_Role[2].m_RoleAttCng[0].m_textx = v9;
  this->me_Role[2].m_RoleAttCng[0].m_texty = v12;
  this->me_Role[2].m_RoleAttCng[0].m_fonttype = v11;
  LODWORD(v13) = this->me_Role[2].m_RoleAttCng[1].m_rect.right - 708;
  v11 = (Parent_Data *)((char *)v11 + 25);
  this->me_Role[2].m_RoleAttCng[0].m_ratioh = v13;
  LODWORD(v13) += 82;
  v72 = (_PlugInfo *)v11;
  *(float *)&this->me_Role[2].m_RoleAttCng[0].m_texty = v13;
  LOBYTE(v13) = g_bDebugMode;
  m_id = (void ( **)(void **, char *, LONG *, MainEquipUI *, char *, float))this->me_Role[2].m_Name.m_id;
  v74 = (char *)&v11[6] + 1;
  m_id[7](&this->me_Role[2].m_Name.m_id, &byte_A00607, &v71, this, "UI\\GameMainUI\\JusticeBook\\Immortal", COERCE_FLOAT(LODWORD(v13)));
  v15 = v71;
  v16 = (int)v72;
  v17 = (int)v73;
  this->me_Role[2].m_RoleAttCng[1].m_childs.capacity = v71;
  this->me_Role[2].m_RoleAttCng[1].m_childs.m_nSize = v16;
  this->me_Role[2].m_RoleAttCng[1].m_childs.m_needscriptdel = v17;
  v18 = v74;
  this->me_Role[2].m_RoleAttCng[1].m_bcreateok = (int)v74;
  *(_DWORD *)this->me_Role[2].m_RoleAttCng[0].m_text = v15;
  v19 = v73;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[0].m_text[4] = v16;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[0].m_text[8] = v19;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[0].m_text[12] = v18;
  v20 = this->me_Role[2].m_RoleAttCng[1].m_childs.capacity - 708;
  v18 += 25;
  *(_DWORD *)this->me_Role[2].m_RoleAttCng[0].m_text = v20;
  v20 += 82;
  v21 = *(_DWORD *)&this->me_Role[2].m_Jing.m_text[12];
  v72 = (_PlugInfo *)v18;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[0].m_text[8] = v20;
  LOBYTE(v20) = g_bDebugMode;
  v74 = v18 + 25;
  (*(void ( **)(char *, char *, LONG *, MainEquipUI *, char *, int))(v21 + 28))(
    &this->me_Role[2].m_Jing.m_text[12],
    &byte_A00608,
    &v71,
    this,
    "UI\\GameMainUI\\JusticeBook\\Ghost",
    v20);
  v22 = (gbTexture *)v71;
  v23 = v72;
  v24 = (int)v73;
  this->me_Role[2].m_RoleAttCng[1].m_bvisible = v71;
  this->me_Role[2].m_RoleAttCng[1].m_benable = (int)v23;
  this->me_Role[2].m_RoleAttCng[1].m_bfocus = v24;
  v25 = (_PlugInfo *)v74;
  this->me_Role[2].m_RoleAttCng[1].pDebugTex = (gbTexture *)v74;
  v26 = (gbTexture *)(this->me_Role[2].m_RoleAttCng[1].m_bvisible - 708);
  this->me_Role[2].m_RoleAttCng[0].m_pbk = v22;
  v27 = (gbTexture *)v73;
  this->me_Role[2].m_RoleAttCng[0].m_pbkInfo = v23;
  this->me_Role[2].m_RoleAttCng[0].m_ppic = v27;
  this->me_Role[2].m_RoleAttCng[0].m_ppicInfo = v25;
  this->me_Role[2].m_RoleAttCng[0].m_pbk = v26;
  v25 = (_PlugInfo *)((char *)v25 + 25);
  v26 = (gbTexture *)((char *)v26 + 82);
  m_alpha = this->me_Role[2].m_JingBar.m_alpha;
  v72 = v25;
  this->me_Role[2].m_RoleAttCng[0].m_ppic = v26;
  LOBYTE(v26) = g_bDebugMode;
  v74 = &v25->name[21];
  (*(void ( **)(int *, char *, LONG *, MainEquipUI *, char *, gbTexture *))(m_alpha + 28))(
    &this->me_Role[2].m_JingBar.m_alpha,
    byte_A00609,
    &v71,
    this,
    "UI\\GameMainUI\\JusticeBook\\Demon",
    v26);
  v29 = (gbTexture *)v71;
  v30 = v72;
  v31 = *(float *)&v73;
  this->me_Role[2].m_RoleAttCng[1].m_align = v71;
  LODWORD(this->me_Role[2].m_RoleAttCng[1].m_ratiow) = v30;
  this->me_Role[2].m_RoleAttCng[1].m_ratioh = v31;
  v32 = v74;
  this->me_Role[2].m_RoleAttCng[1].m_textx = (int)v74;
  v33 = (gbTexture *)(this->me_Role[2].m_RoleAttCng[1].m_align - 708);
  this->me_Role[2].m_RoleAttCng[0].m_disablepic = v29;
  v34 = (gbTexture *)v73;
  this->me_Role[2].m_RoleAttCng[0].m_disablepicInfo = v30;
  this->me_Role[2].m_RoleAttCng[0].m_pbk2 = v34;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[0].m_mouseoff = v32;
  this->me_Role[2].m_RoleAttCng[0].m_disablepic = v33;
  v32 += 25;
  v33 = (gbTexture *)((char *)v33 + 82);
  m_bvisible = this->me_Role[2].m_Shen.m_bvisible;
  v72 = (_PlugInfo *)v32;
  this->me_Role[2].m_RoleAttCng[0].m_pbk2 = v33;
  LOBYTE(v33) = g_bDebugMode;
  v74 = v32 + 25;
  (*(void ( **)(int *, char *, LONG *, MainEquipUI *, char *, gbTexture *))(m_bvisible + 28))(
    &this->me_Role[2].m_Shen.m_bvisible,
    &byte_A00610,
    &v71,
    this,
    "UI\\GameMainUI\\JusticeBook\\Human",
    v33);
  v36 = v71;
  v37 = (Parent_Data *)v72;
  v38 = v73;
  this->me_Role[2].m_RoleAttCng[1].m_texty = v71;
  this->me_Role[2].m_RoleAttCng[1].m_fonttype = v37;
  *(_DWORD *)this->me_Role[2].m_RoleAttCng[1].m_text = v38;
  v39 = (unsigned int)v74;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[1].m_text[4] = v74;
  this->me_Role[2].m_RoleAttCng[0].m_FVF = v36;
  v40 = (void *)v73;
  this->me_Role[2].m_RoleAttCng[0].m_nTextW = (int)v37;
// [VFTABLE] this->me_Role[2].m_RoleAttCng[1].__vftable = v40;
  this->me_Role[2].m_RoleAttCng[1].m_fontcolor.Color = v39;
  v39 += 25;
  v41 = (void *)(this->me_Role[2].m_RoleAttCng[1].m_texty - 708);
  v72 = (_PlugInfo *)v39;
  this->me_Role[2].m_RoleAttCng[0].m_FVF = (int)v41;
  v41 = (void *)((char *)v41 + 82);
  m_pbk = this->me_Role[2].m_ShenBar.m_pbk;
// [VFTABLE] this->me_Role[2].m_RoleAttCng[1].__vftable = v41;
  LOBYTE(v41) = g_bDebugMode;
  v74 = (char *)(v39 + 25);
  ((void ( *)(gbTexture **, char *, LONG *, MainEquipUI *, char *, void *))m_pbk->Height)(
    &this->me_Role[2].m_ShenBar.m_pbk,
    &byte_A00611,
    &v71,
    this,
    "UI\\GameMainUI\\JusticeBook\\Magic",
    v41);
  v43 = v71;
  v44 = v72;
  v45 = (gbTexture *)v73;
  v46 = (_PlugInfo *)v74;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[1].m_text[8] = v71;
  *(_DWORD *)&this->me_Role[2].m_RoleAttCng[1].m_text[12] = v44;
  this->me_Role[2].m_RoleAttCng[1].m_pbk = v45;
  this->me_Role[2].m_RoleAttCng[1].m_pbkInfo = v46;
  v47 = *(_DWORD *)&this->me_Role[2].m_RoleAttCng[1].m_text[8] - 708;
  this->me_Role[2].m_RoleAttCng[1].m_wndcolor.Color = v43;
  v48 = (LONG)v74;
  this->me_Role[2].m_RoleAttCng[1].m_id = v44;
  this->me_Role[2].m_RoleAttCng[1].m_rect.left = (LONG)v45;
  this->me_Role[2].m_RoleAttCng[1].m_rect.top = v48;
  this->me_Role[2].m_RoleAttCng[1].m_wndcolor.Color = v47;
  left = this->rc.left;
  this->me_Role[2].m_RoleAttCng[1].m_rect.left = v47 + 82;
  v76 = this->rc.top + 72;
  v77 = left + 32;
  v78 = v76 + 256;
  m_bcreateok = this->me_Role[1].m_RoleAttEqual[2].m_bcreateok;
  v75 = left + 79;
  (*(void ( **)(int *, char *, int *, MainEquipUI *))(m_bcreateok + 16))(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    &byte_A00602,
    &v75,
    this);
  ((UIScene *)&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)->SetShow(0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    0);
  v51 = this->rc.top + 404;
  v75 = this->rc.left + 118;
  v76 = v51;
  v77 = v75 + 128;
  v78 = v51 + 32;
  (*(void ( **)(int *, char *, int *, MainEquipUI *))(this->me_Role[1].m_RoleAttEqual[3].m_bcreateok
                                                                         + 16))(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    &byte_A00602,
    &v75,
    this);
  ((UIScene *)&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)->SetShow(0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    0);
  v52 = this->me_Role[1].m_RoleAttEqual[4].m_bcreateok;
  v76 = v78 - 2;
  v78 = v78 - 2 + 32;
  (*(void ( **)(int *, char *, int *, MainEquipUI *))(v52 + 16))(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    &byte_A00602,
    &v75,
    this);
  ((UIScene *)&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)->SetShow(0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    0);
  v53 = this->rc.top + 464;
  v75 = this->rc.left + 92;
  v76 = v53;
  v77 = v75 + 64;
  v78 = v53 + 32;
  p_m_bcreateok = &this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v55 = 5;
  do
  {
    (*(void ( **)(int *, char *, int *, MainEquipUI *))(*p_m_bcreateok + 16))(
      p_m_bcreateok,
      &byte_A00602,
      &v75,
      this);
    ((UIScene *)p_m_bcreateok)->SetShow(0);
    (*(void ( **)(int *, _DWORD))*p_m_bcreateok)(p_m_bcreateok, 0);
    p_m_bcreateok += 38;
    v75 = v77 - 3;
    --v55;
    v77 = v77 - 3 + 64;
  }
  while ( v55 );
  v56 = this->rc.top + 102;
  v75 = this->rc.left + 426;
  v76 = v56;
  v77 = v75 + 100;
  v78 = v56 + 32;
  v57 = &this->me_Role[1].m_EquipPic.m_bcreateok;
  v58 = 5;
  do
  {
    (*(void ( **)(int *, char *, int *, MainEquipUI *))(*v57 + 16))(v57, &byte_A00602, &v75, this);
    ((UIScene *)v57)->SetShow(0);
    (*(void ( **)(int *, _DWORD))*v57)(v57, 0);
    v57 += 38;
    v76 = v78 - 4;
    --v58;
    v78 = v78 - 4 + 32;
  }
  while ( v58 );
  v59 = this->rc.top + 128;
  v60 = this->rc.left + 542;
  v76 = v59;
  v75 = v60;
  v61 = (UIScene *)&this->me_Role[1].m_EquipHat.m_caption[124];
  v77 = v60 + 200;
  v62 = v59 + 32;
  v78 = v59 + 32;
  v63 = &this->me_Role[1].m_EquipShoes.m_caption[44];
  v70 = 4;
  while ( 1 )
  {
    *(_DWORD *)v63 = v60;
    v64 = v77;
    *((_DWORD *)v63 + 1) = v59;
    *((_DWORD *)v63 + 2) = v64;
    *((_DWORD *)v63 + 3) = v62;
// [VFTABLE] ((void ( *)(UIScene *, char *, int *, MainEquipUI *))v61->__vftable->Create)(
// [VFTABLE]   v61,
// [VFTABLE]   &byte_A00602,
// [VFTABLE]   &v75,
// [VFTABLE]   this);
    ((UIScene *)v61)->SetShow(0);
// [VFTABLE] ((void ( *)(UIScene *, _DWORD))v61->__vftable->ShowWindow)(v61, 0);
    v59 = v78 - 4;
    v63 += 16;
    v61 = (UIScene *)((char *)v61 + 152);
    v65 = v70 == 1;
    v62 = v78 - 4 + 32;
    v76 = v78 - 4;
    v78 = v62;
    --v70;
    if ( v65 )
      break;
    v60 = v75;
  }
  v66 = this->rc.left;
  v67 = *(_DWORD *)&this->me_Role[1].m_EquipShoes.m_caption[108];
  v76 = this->rc.top + 255;
  v75 = v66 + 420;
  v78 = v76 + 280;
  v77 = v66 + 676;
  (*(void ( **)(char *, char *, int *, MainEquipUI *))(v67 + 16))(
    &this->me_Role[1].m_EquipShoes.m_caption[108],
    &byte_A00602,
    &v75,
    this);
  ((UIScene *)&this->me_Role[1].m_EquipShoes.m_caption[108])->SetShow(0);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipShoes.m_caption[108])(
    &this->me_Role[1].m_EquipShoes.m_caption[108],
    0);
  v68 = this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3];
  v82[1] = 468;
  v82[0] = 670;
  v82[2] = 734;
  v82[3] = 500;
  (*((void ( **)(gbTexture **, char *, _DWORD *, MainEquipUI *))v68 + 4))(
    &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
    &byte_A00602,
    v82,
    this);
  ((UIScene *)&this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3])->SetShow(0);
  // [VTBL_DISPATCH] return ((int ( *)(gbTexture **, _DWORD))this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]->0)(
           // [VTBL_DISPATCH]   &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
           // [VTBL_DISPATCH]   0);
}

// 0x00480530
int * MainEquipUI::UpdateFadeAlpha(float fVal)
{
  double v3; // st7
  int *p_m_bcreateok; // ebx
  int v5; // ebp
  char *v6; // ebx
  int v7; // ebp

  v3 = fVal * 120.0 + *(float *)&this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color;
  *(float *)&this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = v3;
  if ( v3 >= 255.0 )
  {
    this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 1132396544;
    LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  }
  HIBYTE(this->me_Role[2].m_RoleAttCng[2].m_fontcolor.Color) = (__int64)*(float *)&this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color;
  sub_446010(&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok);
  sub_446010(&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok);
  sub_446010(&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok);
  p_m_bcreateok = &this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v5 = 5;
  do
  {
    sub_446010(p_m_bcreateok + 190);
    sub_446010(p_m_bcreateok);
    p_m_bcreateok += 38;
    --v5;
  }
  while ( v5 );
  v6 = &this->me_Role[1].m_EquipHat.m_caption[124];
  v7 = 4;
  do
  {
    sub_446010(v6);
    v6 += 152;
    --v7;
  }
  while ( v7 );
  return (int *)sub_446010(&this->me_Role[1].m_EquipShoes.m_caption[108]);
}

// 0x004819A0
OpenNULLFile * MainEquipUI::LoadFromFile(OpenNULLFile *pFile, int nVal)
{
  int v3; // edi
  OpenNULLFile *result; // eax
  int v6; // ebx

  v3 = nVal;
  if ( nVal >= 0 )
  {
    if ( nVal > 1 )
      v3 = 1;
  }
  else
  {
    v3 = 0;
  }
  result = pFile;
  switch ( (unsigned int)pFile )
  {
    case 0u:
      v6 = v3;
      if ( v3 >= 0 )
      {
        if ( v3 > 1 )
          v6 = 1;
      }
      else
      {
        v6 = 0;
      }
      if ( this->me_Role[2].m_RoleAttCng[1].m_ppic != (gbTexture *)v6 )
      {
        sub_445FA0(&this->me_Role[2].m_Head.m_texarray.m_ptex[3]);
        if ( v6 )
        {
          ((CCBParabolaWindow *)&this->me_Role[2].m_Head.m_texarray.m_ptex[3])->LoadResourceEx("UI\\GameMainUI\\JusticeBook\\Gods", g_bDebugMode);
        }
        else
        {
          ((UIStatic *)&this->me_Role[2].m_Head.m_texarray.m_ptex[3])->LoadResource("UI\\GameMainUI\\JusticeBook\\PassGods0.tga", g_bDebugMode);
          ((UIStatic *)&this->me_Role[2].m_Head.m_texarray.m_ptex[3])->LoadTexture();
        }
        this->me_Role[2].m_RoleAttCng[1].m_ppic = (gbTexture *)v6;
      }
      ((Object3D *)this)->LoadActorModel(1);
      ((Object3D *)this)->LoadActorModel(2);
      ((Object3D *)this)->LoadActorModel(3);
      ((Object3D *)this)->LoadActorModel(4);
      result = (OpenNULLFile *)((Object3D *)this)->LoadActorModel(5);
      break;
    case 1u:
      if ( v3 )
      {
        ((Object3D *)this)->LoadActorModel(1);
        goto LABEL_19;
      }
      result = (OpenNULLFile *)((Object3D *)this)->LoadActorModel(0);
      break;
    case 2u:
      if ( v3 )
      {
LABEL_19:
        ((Object3D *)this)->LoadActorModel(2);
        goto LABEL_20;
      }
      ((Object3D *)this)->LoadActorModel(0);
      result = (OpenNULLFile *)((Object3D *)this)->LoadActorModel(1);
      break;
    case 3u:
      if ( v3 )
      {
LABEL_20:
        ((Object3D *)this)->LoadActorModel(3);
        goto LABEL_21;
      }
      ((Object3D *)this)->LoadActorModel(0);
      ((Object3D *)this)->LoadActorModel(1);
      result = (OpenNULLFile *)((Object3D *)this)->LoadActorModel(2);
      break;
    case 4u:
      if ( v3 )
      {
LABEL_21:
        ((Object3D *)this)->LoadActorModel(4);
        goto LABEL_22;
      }
      ((Object3D *)this)->LoadActorModel(0);
      ((Object3D *)this)->LoadActorModel(1);
      ((Object3D *)this)->LoadActorModel(2);
      result = (OpenNULLFile *)((Object3D *)this)->LoadActorModel(3);
      break;
    case 5u:
      if ( v3 )
      {
LABEL_22:
        result = (OpenNULLFile *)((Object3D *)this)->LoadActorModel(5);
      }
      else
      {
        ((Object3D *)this)->LoadActorModel(0);
        ((Object3D *)this)->LoadActorModel(1);
        ((Object3D *)this)->LoadActorModel(2);
        ((Object3D *)this)->LoadActorModel(3);
        result = (OpenNULLFile *)((Object3D *)this)->LoadActorModel(4);
      }
      break;
    default:
      return result;
  }
  return result;
}

// 0x00481BA0
unsigned __int8 MainEquipUI::SetAdornVisible(unsigned __int8 pData)
{
  int *p_m_bcreateok; // ebp
  int v4; // ebx
  int *v5; // ebp
  int v6; // ebx
  char *v7; // ebp
  int v8; // ebx
  unsigned __int8 result; // al

  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn1.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn1.m_caption[68],
    pData);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn2.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn2.m_caption[68],
    pData);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    pData);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    pData);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    pData);
  p_m_bcreateok = &this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v4 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_bcreateok)(p_m_bcreateok, pData);
    p_m_bcreateok += 38;
    --v4;
  }
  while ( v4 );
  v5 = &this->me_Role[1].m_EquipPic.m_bcreateok;
  v6 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*v5)(v5, pData);
    v5 += 38;
    --v6;
  }
  while ( v6 );
  v7 = &this->me_Role[1].m_EquipHat.m_caption[124];
  v8 = 4;
  do
  {
    (**(void ( ***)(char *, _DWORD))v7)(v7, pData);
    v7 += 152;
    --v8;
  }
  while ( v8 );
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipShoes.m_caption[108])(
    &this->me_Role[1].m_EquipShoes.m_caption[108],
    pData);
  // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]->0)(
    // [VTBL_DISPATCH]   &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
    // [VTBL_DISPATCH]   pData);
  if ( *((int *)&this->me_Role[2].m_Qi.m_id + (int)this->me_Role[2].m_RoleAttCng[0].pDebugTex) > 0 )
    this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = (_PlugInfo *)pData;
  else
    this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = 0;
  result = pData;
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = pData;
  if ( !pData )
    this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  return result;
}

// 0x00481CB0
void MainEquipUI::SelectWithSound(int nVal)
{
  int *p_m_bcreateok; // edi
  int v4; // ebp
  int *v5; // edi
  int v6; // ebp
  char *v7; // edi
  int v8; // ebp
  CScreenMode *Instance; // eax
  const void *v10; // [esp+0x18] [ebp-0x10]

  this->me_Role[2].m_Head.m_alignmode = 0;
  LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 0;
  this->me_Role[2].m_Name.m_fonttype = 0;
  LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 0;
  this->me_Role[2].m_JingBar.m_childs.m_pData = 0;
  LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 0;
  this->me_Role[2].m_JingVal.m_childs.capacity = 0;
  LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 0;
  this->me_Role[2].m_Shen.m_pbk2 = 0;
  LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 0;
  *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 0;
  LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 0;
  switch ( nVal )
  {
    case 0:
      this->me_Role[2].m_Head.m_alignmode = 1;
      LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 1;
      break;
    case 1:
      this->me_Role[2].m_Name.m_fonttype = (Parent_Data *)1;
      LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 1;
      break;
    case 2:
      this->me_Role[2].m_JingBar.m_childs.m_pData = (char *)1;
      LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 1;
      break;
    case 3:
      this->me_Role[2].m_JingVal.m_childs.capacity = 1;
      LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 1;
      break;
    case 4:
      this->me_Role[2].m_Shen.m_pbk2 = (gbTexture *)1;
      LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 1;
      break;
    case 5:
      *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 1;
      LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 1;
      break;
    default:
      break;
  }
  ((gbVisNode *)this->me_Role[1].m_RoleAttCng[8].m_disablepicInfo)->SetTimeScale(2.0);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn1.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn1.m_caption[68],
    0);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn2.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn2.m_caption[68],
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    0);
  p_m_bcreateok = &this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v4 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_bcreateok)(p_m_bcreateok, 0);
    p_m_bcreateok += 38;
    --v4;
  }
  while ( v4 );
  v5 = &this->me_Role[1].m_EquipPic.m_bcreateok;
  v6 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*v5)(v5, 0);
    v5 += 38;
    --v6;
  }
  while ( v6 );
  v7 = &this->me_Role[1].m_EquipHat.m_caption[124];
  v8 = 4;
  do
  {
    (**(void ( ***)(char *, _DWORD))v7)(v7, 0);
    v7 += 152;
    --v8;
  }
  while ( v8 );
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipShoes.m_caption[108])(
    &this->me_Role[1].m_EquipShoes.m_caption[108],
    0);
  // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]->0)(
    // [VTBL_DISPATCH]   &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
    // [VTBL_DISPATCH]   0);
  this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = 0;
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  this->RenderEquipDetails(nVal);
  v10 = off_5C3ED4;
  Instance = CScreenMode::GetInstance();
  ((CScreenMode *)Instance)->AudioSetPosition(v10, 1);
}

// 0x00481EB0
void MainEquipUI::ShowPanelsWithSound(int nVal, int nVal2)
{
  int *p_m_bcreateok; // edi
  int v5; // ebp
  int *v6; // edi
  int v7; // ebp
  char *v8; // edi
  int v9; // ebp
  CScreenMode *Instance; // eax
  const void *v11; // [esp-0x8] [ebp-0x10]
  int m_bfocus; // [esp-0x4] [ebp-0xC]

  this->me_Role[2].m_RoleAttCng[0].m_bfocus = nVal;
  this->me_Role[2].m_RoleAttCng[0].pDebugTex = (gbTexture *)nVal;
  this->me_Role[2].m_Head.m_alignmode = 0;
  LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 0;
  this->me_Role[2].m_Name.m_fonttype = 0;
  LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 0;
  this->me_Role[2].m_JingBar.m_childs.m_pData = 0;
  LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 0;
  this->me_Role[2].m_JingVal.m_childs.capacity = 0;
  LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 0;
  this->me_Role[2].m_Shen.m_pbk2 = 0;
  LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 0;
  *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 0;
  LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 0;
  switch ( this->me_Role[2].m_RoleAttCng[0].m_bfocus )
  {
    case 0:
      this->me_Role[2].m_Head.m_alignmode = 1;
      LOBYTE(this->me_Role[2].m_Head.m_disablepic) = 1;
      break;
    case 1:
      this->me_Role[2].m_Name.m_fonttype = (Parent_Data *)1;
      LOBYTE(this->me_Role[2].m_Name.m_ratioh) = 1;
      break;
    case 2:
      this->me_Role[2].m_JingBar.m_childs.m_pData = (char *)1;
      LOBYTE(this->me_Role[2].m_JingBar.m_rect.right) = 1;
      break;
    case 3:
      this->me_Role[2].m_JingVal.m_childs.capacity = 1;
      LOBYTE(this->me_Role[2].m_JingVal.m_rect.bottom) = 1;
      break;
    case 4:
      this->me_Role[2].m_Shen.m_pbk2 = (gbTexture *)1;
      LOBYTE(this->me_Role[2].m_Shen.m_ppicInfo) = 1;
      break;
    case 5:
      *(&this->me_Role[2].m_ShenBar.m_warningval + 3) = 1;
      LOBYTE(this->me_Role[2].m_ShenBar.m_warningval) = 1;
      break;
    default:
      break;
  }
  if ( nVal2 == 2 )
  {
    ((PalScript *)&this->me_Role[1].m_RoleAttCng[8].m_pbkInfo)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
// [VFTABLE] this->me_Role[2].m_RoleAttCng[2].__vftable = (vtbl_0056AE2C *)2;
    this->me_Role[2].m_RoleAttCng[1].m_nTextW = 1;
  }
  else if ( nVal2 == 1 )
  {
    ((PalScript *)&this->me_Role[1].m_RoleAttCng[8].m_pbkInfo)->LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
// [VFTABLE] this->me_Role[2].m_RoleAttCng[2].__vftable = (vtbl_0056AE2C *)1;
    this->me_Role[2].m_RoleAttCng[1].m_nTextW = 0;
  }
  ((StateUI *)this)->ShowPanels(this->me_Role[2].m_RoleAttCng[0].m_bfocus, 0, (UIWnd *)this->me_Role[2].m_RoleAttCng[1].m_nTextW);
  ((gbVisNode *)this->me_Role[1].m_RoleAttCng[8].m_disablepicInfo)->SetTimeScale(2.0);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn1.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn1.m_caption[68],
    0);
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipAdorn2.m_caption[68])(
    &this->me_Role[1].m_EquipAdorn2.m_caption[68],
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[2].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[3].m_bcreateok,
    0);
  (*(void ( **)(int *, _DWORD))this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)(
    &this->me_Role[1].m_RoleAttEqual[4].m_bcreateok,
    0);
  p_m_bcreateok = &this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
  v5 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*p_m_bcreateok)(p_m_bcreateok, 0);
    p_m_bcreateok += 38;
    --v5;
  }
  while ( v5 );
  v6 = &this->me_Role[1].m_EquipPic.m_bcreateok;
  v7 = 5;
  do
  {
    (*(void ( **)(int *, _DWORD))*v6)(v6, 0);
    v6 += 38;
    --v7;
  }
  while ( v7 );
  v8 = &this->me_Role[1].m_EquipHat.m_caption[124];
  v9 = 4;
  do
  {
    (**(void ( ***)(char *, _DWORD))v8)(v8, 0);
    v8 += 152;
    --v9;
  }
  while ( v9 );
  (**(void ( ***)(char *, _DWORD))&this->me_Role[1].m_EquipShoes.m_caption[108])(
    &this->me_Role[1].m_EquipShoes.m_caption[108],
    0);
  // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3]->0)(
    // [VTBL_DISPATCH]   &this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3],
    // [VTBL_DISPATCH]   0);
  m_bfocus = this->me_Role[2].m_RoleAttCng[0].m_bfocus;
  this->me_Role[1].m_RoleAttEqual[0].m_ppicInfo = 0;
  LOBYTE(this->me_Role[2].m_RoleAttCng[2].m_id) = 0;
  this->me_Role[2].m_RoleAttCng[2].m_wndcolor.Color = 0;
  this->RenderEquipDetails(m_bfocus);
  BYTE1(this->me_Role[2].m_RoleAttCng[1].m_FVF) = 1;
  v11 = off_5C3ED4;
  Instance = CScreenMode::GetInstance();
  ((CScreenMode *)Instance)->AudioSetPosition(v11, 1);
}

// 0x00482140
void MainEquipUI::RenderEquipDetails(int arg0)
{
  int v3; // ebx
  int *v4; // esi
  int v5; // ebx
  UICaption *v6; // esi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  UICaption *v14; // esi
  int RoleNum; // ebp
  bool v16; // zf
  int *p_m_bcreateok; // esi
  int v18; // ebx
  UICaption *v19; // esi
  int v20; // ebx
  const CHAR *v21; // [esp-0x4] [ebp-A0h]
  int *v22; // [esp+0x10] [ebp-0x8C]
  char *v23; // [esp+0x14] [ebp-0x88]
  int v24; // [esp+0x18] [ebp-0x84]
  char Buffer[128]; // [esp+0x1C] [ebp-0x80] BYREF

  v3 = 0;
  if ( *((int *)&this->me_Role[2].m_Qi.m_id + arg0) > 0 )
  {
    switch ( arg0 )
    {
      case 0:
        ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)&this->me_Role[2].m_Qi.m_childs.m_pData + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v8;
        lstrcpyA(this->buf, (LPCSTR)dword_DC433C);
        break;
      case 1:
        ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(&this->me_Role[2].m_QiVal.m_childs.capacity + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v9;
        lstrcpyA(this->buf, (LPCSTR)dword_DCF83C);
        break;
      case 2:
        ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)&this->me_Role[2].m_AttFramePose.m_pbk2 + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v10;
        v21 = (const CHAR *)dword_DCF93C;
        goto LABEL_14;
      case 3:
        ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)&this->me_Role[2].m_RoleAtt[2].m_ratioh + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v11;
        lstrcpyA(this->buf, (LPCSTR)dword_DCFA3C);
        break;
      case 4:
        ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*(&this->me_Role[2].m_RoleAtt[5].m_rect.right + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v12;
        lstrcpyA(this->buf, (LPCSTR)dword_DCFB3C);
        break;
      case 5:
        ((PAL_GDB *)&g_pGDB)->_PAL_GDB(*((_DWORD *)&this->me_Role[2].m_RoleAtt[7].m_ppic + LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow)));
        v3 = v13;
        v21 = byte_DCFC3C;
LABEL_14:
        lstrcpyA(this->buf, v21);
        break;
      default:
        break;
    }
    sprintf(Buffer, &dir[20], LODWORD(this->me_Role[2].m_RoleAttCng[0].m_ratiow) + 1);
    lstrcatA(this->buf, Buffer);
    ((UICaption *)&this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3])->SetEnable((int)this->buf, 0);
    if ( *((int *)&this->me_Role[2].m_Qi.m_id + arg0) <= 0 )
    {
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)->SetEnable((int)g_szSceneUIText, 0);
      p_m_bcreateok = &this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
      v18 = 5;
      do
      {
        ((UICaption *)(p_m_bcreateok + 190))->SetEnable((int)g_szSceneUIText, 0);
        ((UICaption *)p_m_bcreateok)->SetEnable((int)g_szSceneUIText, 0);
        p_m_bcreateok += 38;
        --v18;
      }
      while ( v18 );
      v19 = (UICaption *)&this->me_Role[1].m_EquipHat.m_caption[124];
      v20 = 4;
      do
      {
        ((UICaption *)v19)->SetEnable((int)g_szSceneUIText, 0);
        v19 = (UICaption *)((char *)v19 + 152);
        --v20;
      }
      while ( v20 );
      ((UICaption *)&this->me_Role[1].m_EquipShoes.m_caption[108])->SetEnable((int)g_szSceneUIText, 0);
    }
    else
    {
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)->SetEnable(v3 + 600, 0);
      sprintf(this->buf, &dir[20], *(_DWORD *)(v3 + 636));
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, &dir[20], *(_DWORD *)(v3 + 644));
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "%s%d", (const char *)g_bSlotFlag, *(_DWORD *)(v3 + 664));
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[5].m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "%s%d", (const char *)&g_bSlotFlag[256], *(_DWORD *)(v3 + 668));
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[6].m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "%s%d", (const char *)&g_bSlotFlag[512], *(_DWORD *)(v3 + 676));
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[8].m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "%s%d", byte_DC3F3C, *(_DWORD *)(v3 + 672));
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[7].m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "%s%d", byte_DC403C, *(_DWORD *)(v3 + 680));
      ((UICaption *)&this->me_Role[1].m_RoleAttEqual[9].m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 648));
      ((UICaption *)&this->me_Role[1].m_EquipPic.m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 652));
      ((UICaption *)&this->me_Role[1].m_EquipWeapon.m_bcreateok)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 656));
      ((UICaption *)&this->me_Role[1].m_EquipWeapon.m_caption[12])->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 660));
      ((UICaption *)&this->me_Role[1].m_EquipHat.m_id)->SetEnable((int)this->buf, 0);
      sprintf(this->buf, "    %d", *(_DWORD *)(v3 + 740));
      ((UICaption *)this->me_Role[1].m_EquipHat.m_texarrayInfo)->SetEnable((int)this->buf, 0);
      v14 = (UICaption *)&this->me_Role[1].m_EquipHat.m_caption[124];
      v23 = &this->me_Role[1].m_EquipShoes.m_caption[44];
      v22 = (int *)(v3 + 760);
      v24 = 4;
      do
      {
        if ( *v22 )
        {
          RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*v22);
          sub_445FA0(v14);
          ((UICaption *)v14)->SetEnable(RoleNum + 28, 0);
          v23 += 16;
        }
        else
        {
          ((UICaption *)v14)->SetEnable((int)g_szSceneUIText, 0);
        }
        v14 = (UICaption *)((char *)v14 + 152);
        v16 = v24 == 1;
        ++v22;
        --v24;
      }
      while ( !v16 );
      ((UICaption *)&this->me_Role[1].m_EquipShoes.m_caption[108])->SetEnable(v3 + 6, 0);
      ((PalScript *)&this->me_Role[1].m_RoleAttEqual[0].m_ppic)->LoadModel((const char *)(v3 + 518), 50);
    }
  }
  else
  {
    ((UICaption *)&this->me_Role[1].m_RoleAttEqual[2].m_bcreateok)->SetEnable((int)g_szSceneUIText, 0);
    ((UICaption *)&this->me_Role[1].m_RoleAttEqual[3].m_bcreateok)->SetEnable((int)g_szSceneUIText, 0);
    ((UICaption *)&this->me_Role[1].m_RoleAttEqual[4].m_bcreateok)->SetEnable((int)g_szSceneUIText, 0);
    v4 = &this->me_Role[1].m_RoleAttEqual[5].m_bcreateok;
    v5 = 5;
    do
    {
      ((UICaption *)(v4 + 190))->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)v4)->SetEnable((int)g_szSceneUIText, 0);
      v4 += 38;
      --v5;
    }
    while ( v5 );
    v6 = (UICaption *)&this->me_Role[1].m_EquipHat.m_caption[124];
    v7 = 4;
    do
    {
      ((UICaption *)v6)->SetEnable((int)g_szSceneUIText, 0);
      v6 = (UICaption *)((char *)v6 + 152);
      --v7;
    }
    while ( v7 );
    ((UICaption *)&this->me_Role[1].m_EquipShoes.m_caption[108])->SetEnable((int)g_szSceneUIText, 0);
    ((UICaption *)&this->me_Role[1].m_EquipAdorn1.m_texarray.m_ptex[3])->SetEnable((int)g_szSceneUIText, 0);
  }
}

// 0x004844A0
int MainEquipUI::CountVisibleStats()
{
  int result; // eax
  int *p_m_nSize; // ecx
  int *p_m_align; // ebp
  int v5; // edi
  int *v6; // eax
  int v7; // ecx
  bool v8; // cc
  int *v9; // [esp+0x10] [ebp-0xC]
  int v10; // [esp+0x14] [ebp-0x8]
  int v11; // [esp+0x18] [ebp-0x4]

  result = 0;
  p_m_nSize = &this->me_Role[1].m_RoleAttEqual[0].m_childs.m_nSize;
  v10 = 0;
  v11 = 0;
  v9 = p_m_nSize;
  p_m_align = &this->me_Role[2].m_RoleAttCng[5].m_align;
  do
  {
    if ( this->m_Is[result] )
    {
      v5 = 0;
      while ( 1 )
      {
        if ( v5 == 5 )
        {
          if ( *((_BYTE *)p_m_nSize + 5) == 2 )
          {
            ((LineupComp *)this)->GetSlotWidget(result, 1u);
            p_m_align[3] = 1;
            *(_BYTE *)p_m_align = 1;
          }
          else
          {
            *p_m_nSize = 0;
            *((_WORD *)p_m_nSize + 2) = 0;
            ((LineupComp *)this)->GetSlotWidget(result, 0);
            sub_445E50((int)(p_m_align - 17));
            v6 = p_m_align - 310;
            v7 = 6;
            do
            {
              v6[3] = 0;
              *(_BYTE *)v6 = 0;
              v6 += 62;
              --v7;
            }
            while ( v7 );
          }
        }
        else
        {
          sub_445E50((int)&this->me_Role[2].m_RoleAtt[6].m_disablepicInfo + 248 * v5 + v11);
          if ( *((_BYTE *)v9 + v5) )
          {
            if ( *((_BYTE *)v9 + v5) == 1 )
            {
              *(int *)((char *)&this->me_Role[2].m_RoleAtt[7].m_benable + 248 * v5 + v11) = 0;
              *((_BYTE *)&this->me_Role[2].m_RoleAtt[7].m_childs.m_needscriptdel + 248 * v5 + v11) = 0;
            }
            else if ( *((_BYTE *)v9 + v5) == 2 )
            {
              *(int *)((char *)&this->me_Role[2].m_RoleAtt[7].m_benable + 248 * v5 + v11) = 1;
              *((_BYTE *)&this->me_Role[2].m_RoleAtt[7].m_childs.m_needscriptdel + 248 * v5 + v11) = 1;
            }
          }
          else
          {
            *(int *)((char *)&this->me_Role[2].m_RoleAtt[7].m_benable + 248 * v5 + v11) = 0;
            *((_BYTE *)&this->me_Role[2].m_RoleAtt[7].m_childs.m_needscriptdel + 248 * v5 + v11) = 0;
            sub_445E50((int)&this->me_Role[2].m_RoleAtt[6].m_disablepicInfo + 248 * v5 + v11);
          }
        }
        if ( ++v5 >= 6 )
          break;
        result = v10;
        p_m_nSize = v9;
      }
      sub_445E50((int)(p_m_align - 17));
      result = v10;
      p_m_nSize = v9;
    }
    ++result;
    p_m_nSize = (int *)((char *)p_m_nSize + 6);
    p_m_align += 486;
    v8 = v11 + 1944 < 9720;
    v10 = result;
    v9 = p_m_nSize;
    v11 += 1944;
  }
  while ( v8 );
  return result;
}

// 0x004930E0
void MainEquipUI::UpdateTooltip(int nVal)
{
  unsigned int v3; // eax
  char *v4; // esi

  v3 = Buffer.m_partyActor.m_dwMatMsg[352 * nVal + 8];
  if ( v3 )
  {
    switch ( lstrlenA((LPCSTR)(v3 + 4)) )
    {
      case 4:
        *((_DWORD *)&this->mb_SortDefault + 172) = 32;
        break;
      case 6:
        *((_DWORD *)&this->mb_SortDefault + 172) = 26;
        break;
      case 8:
        *((_DWORD *)&this->mb_SortDefault + 172) = 20;
        break;
      case 10:
        *((_DWORD *)&this->mb_SortDefault + 172) = 14;
        break;
      default:
        break;
    }
    *((_DWORD *)&this->mb_SortDefault + 174) = *((_DWORD *)&this->mb_SortDefault + 172) + 108;
    sub_445FA0((char *)&this->mb_SortDefault + 700);
    ((UICaption *)((char *)&this->mb_SortDefault + 700))->SetEnable(Buffer.m_partyActor.m_dwMatMsg[352 * nVal + 8] + 4, 0);
  }
  else
  {
    ((UICaption *)((char *)&this->mb_SortDefault + 700))->SetEnable((int)g_szSceneUIText, 0);
  }
  v4 = (char *)this + 9980 * nVal;
  ((CScreenMode *)(v4 + 162768))->SetTooltipText();
  ((CScreenMode *)(v4 + 163112))->SetTooltipText();
  ((CScreenMode *)(v4 + 163456))->SetTooltipText();
  ((CScreenMode *)(v4 + 163800))->SetTooltipText();
  ((CScreenMode *)(v4 + 164144))->SetTooltipText();
}

// 0x0049AEA0
void MainEquipUI::ShowWithCursor(int nVal)
{
  int *p_capacity; // edi
  int v4; // ebp
  char *m_text; // edi
  int v6; // ebp
  UICursor *v7; // ecx
  char *p_m_bcreateok; // edi

  this->m_TimeMoney.m_text[13] = 0;
  ((EquipUI *)this)->SetGroupVisible(1u);
  p_capacity = &this->me_Role[4].m_RoleAttCng[1].m_childs.capacity;
  v4 = 6;
  do
  {
    sub_445E50((int)p_capacity);
    p_capacity += 86;
    --v4;
  }
  while ( v4 );
  this->SetupRoleList(nVal, 0);
  m_text = this->me_Role[2].m_AttFramePose.m_text;
  v6 = 5;
  do
  {
    (**(void ( ***)(char *, _DWORD))m_text)(m_text, 0);
    m_text += 4892;
    --v6;
  }
  while ( v6 );
  ((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right)->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->me_Role[4].m_RoleAtt[8].m_rect.right)->SetEnable((int)g_szSceneUIText, 0);
  this->m_Ctrlbtn[1].m_texarrayInfo[2] = 0;
  switch ( nVal )
  {
    case 0:
      p_m_bcreateok = (char *)&this->me_Role[5].m_Jing.m_bcreateok;
      (*(void ( **)(int *, int))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        1);
      ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])(&this->m_ClothName.m_text[12], 0);
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[1].Remark[210])(&this->m_role[1].Remark[210], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])(&this->m_role[2].ImageID[24], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[4].Remark[70])(&this->m_role[4].Remark[70], 0);
      this->m_TimeMoney.m_fonttype = 0;
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[1].m_childs.capacity);
      goto LABEL_11;
    case 1:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      p_m_bcreateok = &this->m_ClothName.m_text[12];
      (**(void ( ***)(char *, int))&this->m_ClothName.m_text[12])(&this->m_ClothName.m_text[12], 1);
      ((UIListBox *)&this->m_ClothName.m_text[12])->GetItem();
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[1].Remark[210])(&this->m_role[1].Remark[210], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])(&this->m_role[2].ImageID[24], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[4].Remark[70])(&this->m_role[4].Remark[70], 0);
      this->m_TimeMoney.m_fonttype = (Parent_Data *)1;
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[3].m_ratioh);
      goto LABEL_11;
    case 2:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])(&this->m_ClothName.m_text[12], 0);
      p_m_bcreateok = (char *)&this->m_typeWord.m_childs;
      (*(void ( **)(PtrArray *, int))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 1);
      ((UIListBox *)&this->m_typeWord.m_childs)->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_role[1].Remark[210])(&this->m_role[1].Remark[210], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])(&this->m_role[2].ImageID[24], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[4].Remark[70])(&this->m_role[4].Remark[70], 0);
      this->m_TimeMoney.m_fonttype = (Parent_Data *)2;
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[5].m_ppic);
      goto LABEL_11;
    case 3:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])(&this->m_ClothName.m_text[12], 0);
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      p_m_bcreateok = &this->m_role[1].Remark[210];
      (**(void ( ***)(char *, int))&this->m_role[1].Remark[210])(&this->m_role[1].Remark[210], 1);
      ((UIListBox *)&this->m_role[1].Remark[210])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])(&this->m_role[2].ImageID[24], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[4].Remark[70])(&this->m_role[4].Remark[70], 0);
      this->m_TimeMoney.m_fonttype = (Parent_Data *)3;
      sub_445E50((int)&this->me_Role[4].m_RoleAttCng[8].m_wndcolor);
      goto LABEL_11;
    case 4:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])(&this->m_ClothName.m_text[12], 0);
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[1].Remark[210])(&this->m_role[1].Remark[210], 0);
      p_m_bcreateok = &this->m_role[2].ImageID[24];
      (**(void ( ***)(char *, int))&this->m_role[2].ImageID[24])(&this->m_role[2].ImageID[24], 1);
      ((UIListBox *)&this->m_role[2].ImageID[24])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_role[4].Remark[70])(&this->m_role[4].Remark[70], 0);
      this->m_TimeMoney.m_fonttype = (Parent_Data *)4;
      sub_445E50((int)&this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel);
LABEL_11:
      ((UIStatic *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity)->CreateFromTemplate();
      if ( ((UIListBox *)p_m_bcreateok)->GetItemData() > 0 )
        goto LABEL_14;
      break;
    case 5:
      (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
        &this->me_Role[5].m_Jing.m_bcreateok,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])(&this->m_ClothName.m_text[12], 0);
      (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[1].Remark[210])(&this->m_role[1].Remark[210], 0);
      (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])(&this->m_role[2].ImageID[24], 0);
      (**(void ( ***)(char *, int))&this->m_role[4].Remark[70])(&this->m_role[4].Remark[70], 1);
      ((UIListBox *)&this->m_role[4].Remark[70])->GetItem();
      this->m_TimeMoney.m_fonttype = (Parent_Data *)5;
      sub_445E50((int)&this->me_Role[4].m_RoleAttEqual[2].m_texty);
      ((UIStatic *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity)->CreateFromTemplate();
      if ( ((UIListBox *)&this->m_role[4].Remark[70])->GetItemData() > 0 )
LABEL_14:
        this->OnMessage(1007, 0, 0);
      break;
    default:
      break;
  }
  ((UICursor *)v7)->IRender();
}

// 0x0049B2E0
void MainEquipUI::SetupRoleList(int arg0, char arg4)
{
  MainEquipUI *v3; // ebx
  signed int i; // ebp
  int *v5; // eax
  int j; // ebp
  int v7; // eax
  int ItemData; // eax
  signed int v9; // esi
  int *v10; // eax
  const char *v11; // esi
  signed int k; // ebp
  int *v13; // eax
  int m; // ebp
  int v15; // eax
  int v16; // eax
  signed int v17; // esi
  int *v18; // eax
  UIListBox *p_m_childs; // edi
  void *v20; // ebx
  signed int v21; // ebp
  char *v22; // esi
  int *v23; // eax
  int v24; // ebx
  int v25; // eax
  signed int v26; // esi
  int *v27; // eax
  char *v28; // ebx
  const char *v29; // ebp
  UIListBox *v30; // edi
  void *v31; // ebx
  signed int v32; // ebp
  char *v33; // esi
  int *v34; // eax
  int v35; // ebx
  int v36; // eax
  signed int v37; // esi
  int *v38; // eax
  UIListBox *v39; // edi
  void *v40; // ebx
  signed int v41; // ebx
  char *v42; // esi
  int *v43; // eax
  int v44; // ebp
  int v45; // eax
  signed int v46; // esi
  int *v47; // eax
  UIListBox *v48; // edi
  void *v49; // ebx
  signed int v50; // ebp
  char *v51; // esi
  int *v52; // eax
  int v53; // ebx
  int v54; // eax
  signed int v55; // esi
  int *v56; // eax
  int *v57; // eax
  int nVala; // [esp+0x10] [ebp-0x1C0]
  int nValb; // [esp+0x10] [ebp-0x1C0]
  int nIndex; // [esp+0x14] [ebp-0x1BC]
  int sel; // [esp+0x18] [ebp-0x1B8]
  int sela; // [esp+0x18] [ebp-0x1B8]
  int selb; // [esp+0x18] [ebp-0x1B8]
  int selc; // [esp+0x18] [ebp-0x1B8]
  int seld; // [esp+0x18] [ebp-0x1B8]
  int sele; // [esp+0x18] [ebp-0x1B8]
  int p_DWORD; // [esp+0x1C] [ebp-0x1B4] BYREF
  int v69; // [esp+0x20] [ebp-0x1B0]
  int v70; // [esp+0x24] [ebp-0x1AC]
  gbColorQuad v71; // [esp+0x28] [ebp-0x1A8] BYREF
  gbColorQuad v72; // [esp+0x2C] [ebp-0x1A4] BYREF
  gbColorQuad v73; // [esp+0x30] [ebp-0x1A0] BYREF
  gbColorQuad v74; // [esp+0x34] [ebp-0x19C] BYREF
  gbColorQuad v75; // [esp+0x38] [ebp-0x198] BYREF
  gbColorQuad v76; // [esp+0x3C] [ebp-0x194] BYREF
  int nVal2[3]; // [esp+0x40] [ebp-0x190] BYREF
  char Buffer; // [esp+0x4C] [ebp-0x184] BYREF
  _BYTE v79[252]; // [esp+0x4D] [ebp-0x183] BYREF
  __int16 v80; // [esp+0x149] [ebp-0x87]
  char v81; // [esp+0x14B] [ebp-0x85]
  _BYTE v82[12]; // [esp+0x14C] [ebp-0x84] BYREF
  _BYTE v83[12]; // [esp+0x158] [ebp-0x78] BYREF
  _BYTE v84[12]; // [esp+0x164] [ebp-0x6C] BYREF
  _BYTE v85[12]; // [esp+0x170] [ebp-0x60] BYREF
  _BYTE v86[12]; // [esp+0x17C] [ebp-0x54] BYREF
  _BYTE v87[12]; // [esp+0x188] [ebp-0x48] BYREF
  _BYTE v88[12]; // [esp+0x194] [ebp-0x3C] BYREF
  _BYTE v89[12]; // [esp+0x1A0] [ebp-0x30] BYREF
  _BYTE pOut[12]; // [esp+0x1AC] [ebp-0x24] BYREF
  _BYTE v91[12]; // [esp+0x1B8] [ebp-0x18] BYREF
  _BYTE v92[12]; // [esp+0x1C4] [ebp-0xC] BYREF
p_DWORD = 0xFFFF;
  v69 = 0;
  v70 = 0;
  nIndex = 0;
  *(_DWORD *)this->m_TimeMoney.m_text = arg0;
  if ( arg0 == 5 )
  {
    ((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray)->SetFloatParam(228.0);
    ((Camera *)&this->m_Ctrlbtn[1].m_texarray)->UpdateCameraLookAt(128, 262, 600);
  }
  else
  {
    ((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray)->SetFloatParam(160.0);
    ((Camera *)&this->m_Ctrlbtn[1].m_texarray)->UpdateCameraLookAt(128, 258, 600);
  }
  switch ( arg0 )
  {
    case 0:
      sel = (int)this->me_Role[5].m_JingBar.m_pbk;
      nIndex = ((NPC *)&this->me_Role[5].m_Jing.m_bcreateok)->CreateChild();
      if ( !arg4 )
        ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(0);
      if ( *(int *)&this->m_Ctrlbtn[1].m_bBigFont >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( !arg4 )
      {
        for ( i = 0; i < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize(); ++i )
        {
          v5 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, i);
          p_DWORD = *v5;
          v69 = v5[1];
          v70 = v5[2];
          sprintf(&this->buf[4], byte_5967B0, v70 + 4);
          nVala = ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->SetItemOffset(&this->buf[4], 0);
          sprintf(&this->buf[4], &dir[20], v69);
          ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->SetMouseMoveSel(1, nVala, &this->buf[4], 0);
        }
      }
      for ( j = 0; j < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize(); ++j )
      {
        if ( ((PAL_GDB *)v3)->LoadByType(j, 0) )
        {
          if ( j < 0 || j >= (int)this->me_Role[5].m_Shen.m_wndcolor.Color )
            v7 = 0;
          else
            v7 = *(_DWORD *)(this->me_Role[5].m_Shen.m_fontcolor.Color + 4 * j);
          *(_DWORD *)(v7 + 68) = this->me_Role[5].m_Jing.m_bvisible;
        }
        else
        {
          ((UITabCtrl *)&this->me_Role[5].m_Jing.m_bcreateok)->SetItemParam(j);
        }
      }
      ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->SetSel(sel);
      ItemData = ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->GetItemData();
      v9 = nIndex;
      if ( ItemData <= nIndex )
      {
        v9 = ItemData - 1;
        nIndex = ItemData - 1;
      }
      ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->GetItem();
      if ( v9 >= 0 )
      {
        v10 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v82, v9);
        p_DWORD = *v10;
        v69 = v10[1];
        v70 = v10[2];
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
          sprintf(&this->buf[4], byte_5967B0, "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        ((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1])->LoadModel(&this->buf[4], 0);
        v11 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), g_szSceneUIText) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v11, (const char *)(v70 + 66));
          goto LABEL_54;
        }
        goto LABEL_52;
      }
      break;
    case 1:
      sela = this->m_HatName.m_childs.capacity;
      nIndex = ((NPC *)&this->m_ClothName.m_text[12])->CreateChild();
      if ( !arg4 )
        ((UIListBox *)&this->m_ClothName.m_text[12])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(1);
      if ( *(int *)&this->m_Ctrlbtn[1].m_bBigFont >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(*(void **)&this->m_Ctrlbtn[1].m_bBigFont);
      if ( !arg4 )
      {
        for ( k = 0; k < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize(); ++k )
        {
          v13 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v92, k);
          p_DWORD = *v13;
          v69 = v13[1];
          v70 = v13[2];
          sprintf(&this->buf[4], byte_5967B0, v70 + 4);
          nValb = ((UIListBox *)&this->m_ClothName.m_text[12])->SetItemOffset(&this->buf[4], 0);
          sprintf(&this->buf[4], &dir[20], v69);
          ((UIListBox *)&this->m_ClothName.m_text[12])->SetMouseMoveSel(1, nValb, &this->buf[4], 0);
        }
      }
      for ( m = 0; m < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize(); ++m )
      {
        if ( ((PAL_GDB *)v3)->LoadByType(m, 0) )
        {
          if ( m < 0 || m >= (int)this->m_Adorn1Name.m_disablepicInfo )
            v15 = 0;
          else
            v15 = *((_DWORD *)&this->m_Adorn1Name.*((_DWORD *)m_disablepic) + m);
          *(_DWORD *)(v15 + 68) = this->m_ClothName.m_pbk;
        }
        else
        {
          ((UITabCtrl *)&this->m_ClothName.m_text[12])->SetItemParam(m);
        }
      }
      ((UIListBox *)&this->m_ClothName.m_text[12])->SetSel(sela);
      v16 = ((UIListBox *)&this->m_ClothName.m_text[12])->GetItemData();
      v17 = nIndex;
      if ( v16 <= nIndex )
      {
        v17 = v16 - 1;
        nIndex = v16 - 1;
      }
      ((UIListBox *)&this->m_ClothName.m_text[12])->GetItem();
      if ( v17 >= 0 )
      {
        v18 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v91, v17);
        p_DWORD = *v18;
        v69 = v18[1];
        v70 = v18[2];
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
          sprintf(&this->buf[4], byte_5967B0, "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        ((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1])->LoadModel(&this->buf[4], 0);
        v11 = (const char *)(v70 + 36);
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
        {
LABEL_52:
          sprintf(&this->buf[4], byte_5967B0, "NONE");
        }
        else
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v11, (const char *)(v70 + 66));
LABEL_54:
          sprintf(&this->buf[4], "Item\\%s\\%s.tga", v11, &Buffer);
        }
        ((gbGeomNode *)*(gbGeomNode **)&this->m_Ctrlbtn[1].m_mouseoff)->ReplaceTexture(&this->buf[4]);
        this->m_Ctrlbtn[1].m_texarrayInfo[2] = (_PlugInfo *)1;
        goto LABEL_114;
      }
      break;
    case 2:
      p_m_childs = (UIListBox *)&this->m_typeWord.m_childs;
      selb = *(_DWORD *)&this->m_role[0].Remark[106];
      nIndex = ((NPC *)&this->m_typeWord.m_childs)->CreateChild();
      ((UIListBox *)&this->m_typeWord.m_childs)->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(2);
      v20 = *(void **)&this->m_Ctrlbtn[1].m_bBigFont;
      if ( (int)v20 >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(v20);
      v21 = 0;
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v22 = &this->buf[4];
        do
        {
          v23 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v85, v21);
          p_DWORD = *v23;
          v69 = v23[1];
          v70 = v23[2];
          sprintf(v22, byte_5967B0, v70 + 4);
          v24 = ((UIListBox *)p_m_childs)->SetItemOffset(v22, 0);
          sprintf(v22, &dir[20], v69);
          ((UIListBox *)p_m_childs)->SetMouseMoveSel(1, v24, v22, 0);
          ((UITabCtrl *)p_m_childs)->SetItemParam(v24);
          ++v21;
        }
        while ( v21 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      ((UIListBox *)p_m_childs)->SetSel(selb);
      v25 = ((UIListBox *)p_m_childs)->GetItemData();
      v26 = nIndex;
      if ( v25 <= nIndex )
      {
        v26 = v25 - 1;
        nIndex = v25 - 1;
      }
      ((UIListBox *)p_m_childs)->GetItem();
      if ( v26 >= 0 )
      {
        v27 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v89, v26);
        p_DWORD = *v27;
        v69 = v27[1];
        v28 = &this->buf[4];
        v70 = v27[2];
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
          sprintf(&this->buf[4], byte_5967B0, "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        ((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1])->LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), g_szSceneUIText) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
          goto LABEL_112;
        }
        goto LABEL_110;
      }
      break;
    case 3:
      v30 = (UIListBox *)&this->m_role[1].Remark[210];
      selc = *(_DWORD *)&this->m_role[1].Remark[462];
      nIndex = ((NPC *)&this->m_role[1].Remark[210])->CreateChild();
      ((UIListBox *)&this->m_role[1].Remark[210])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(3);
      v31 = *(void **)&this->m_Ctrlbtn[1].m_bBigFont;
      if ( (int)v31 >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(v31);
      v32 = 0;
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v33 = &this->buf[4];
        do
        {
          v34 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v87, v32);
          p_DWORD = *v34;
          v69 = v34[1];
          v70 = v34[2];
          sprintf(v33, byte_5967B0, v70 + 4);
          v35 = ((UIListBox *)v30)->SetItemOffset(v33, 0);
          sprintf(v33, &dir[20], v69);
          ((UIListBox *)v30)->SetMouseMoveSel(1, v35, v33, 0);
          ((UITabCtrl *)v30)->SetItemParam(v35);
          ++v32;
        }
        while ( v32 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      ((UIListBox *)v30)->SetSel(selc);
      v36 = ((UIListBox *)v30)->GetItemData();
      v37 = nIndex;
      if ( v36 <= nIndex )
      {
        v37 = v36 - 1;
        nIndex = v36 - 1;
      }
      ((UIListBox *)v30)->GetItem();
      if ( v37 >= 0 )
      {
        v38 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v83, v37);
        p_DWORD = *v38;
        v69 = v38[1];
        v28 = &this->buf[4];
        v70 = v38[2];
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
          sprintf(&this->buf[4], byte_5967B0, "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        ((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1])->LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), g_szSceneUIText) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
          goto LABEL_112;
        }
        goto LABEL_110;
      }
      break;
    case 4:
      v39 = (UIListBox *)&this->m_role[2].ImageID[24];
      seld = this->m_role[2].normalplunder;
      nIndex = ((NPC *)&this->m_role[2].ImageID[24])->CreateChild();
      ((UIListBox *)&this->m_role[2].ImageID[24])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(4);
      v40 = *(void **)&this->m_Ctrlbtn[1].m_bBigFont;
      if ( (int)v40 >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(v40);
      v41 = 0;
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v42 = &this->buf[4];
        do
        {
          v43 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v84, v41);
          p_DWORD = *v43;
          v69 = v43[1];
          v70 = v43[2];
          if ( ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex(&p_DWORD) && v69 > 1 )
          {
            --v69;
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(&p_DWORD);
          }
          sprintf(v42, byte_5967B0, v70 + 4);
          v44 = ((UIListBox *)v39)->SetItemOffset(v42, 0);
          sprintf(v42, &dir[20], v69);
          ((UIListBox *)v39)->SetMouseMoveSel(1, v44, v42, 0);
          ((UITabCtrl *)v39)->SetItemParam(v44);
          ++v41;
        }
        while ( v41 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      ((UIListBox *)v39)->SetSel(seld);
      v45 = ((UIListBox *)v39)->GetItemData();
      v46 = nIndex;
      if ( v45 <= nIndex )
      {
        v46 = v45 - 1;
        nIndex = v45 - 1;
      }
      ((UIListBox *)v39)->GetItem();
      if ( v46 >= 0 )
      {
        v47 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v86, v46);
        p_DWORD = *v47;
        v69 = v47[1];
        v28 = &this->buf[4];
        v70 = v47[2];
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
          sprintf(&this->buf[4], byte_5967B0, "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        ((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1])->LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( strcmp((const char *)(v70 + 36), g_szSceneUIText) )
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
          goto LABEL_112;
        }
        goto LABEL_110;
      }
      break;
    case 5:
      v48 = (UIListBox *)&this->m_role[4].Remark[70];
      sele = *(_DWORD *)&this->m_role[4].Remark[322];
      nIndex = ((NPC *)&this->m_role[4].Remark[70])->CreateChild();
      ((UIListBox *)&this->m_role[4].Remark[70])->ClearAll();
      ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->CheckValid(5);
      v49 = *(void **)&this->m_Ctrlbtn[1].m_bBigFont;
      if ( (int)v49 >= 0 )
        ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->Insert(v49);
      v50 = 0;
      if ( ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() > 0 )
      {
        v51 = &this->buf[4];
        do
        {
          v52 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(v88, v50);
          p_DWORD = *v52;
          v69 = v52[1];
          v70 = v52[2];
          sprintf(v51, byte_5967B0, v70 + 4);
          v53 = ((UIListBox *)v48)->SetItemOffset(v51, 0);
          sprintf(v51, &dir[20], v69);
          ((UIListBox *)v48)->SetMouseMoveSel(1, v53, v51, 0);
          ((UITabCtrl *)v48)->SetItemParam(v53);
          ++v50;
        }
        while ( v50 < ((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetSize() );
      }
      ((UIListBox *)v48)->SetSel(sele);
      v54 = ((UIListBox *)v48)->GetItemData();
      v55 = nIndex;
      if ( v54 <= nIndex )
      {
        v55 = v54 - 1;
        nIndex = v54 - 1;
      }
      ((UIListBox *)v48)->GetItem();
      if ( v55 >= 0 )
      {
        v56 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(nVal2, v55);
        p_DWORD = *v56;
        v69 = v56[1];
        v28 = &this->buf[4];
        v70 = v56[2];
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
          sprintf(&this->buf[4], byte_5967B0, "NONE");
        else
          sprintf(&this->buf[4], "Item\\%s\\%s.pol", (const char *)(v70 + 36), (const char *)(v70 + 36));
        ((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1])->LoadModel(v28, 0);
        v29 = (const char *)(v70 + 36);
        if ( !strcmp((const char *)(v70 + 36), g_szSceneUIText) )
        {
LABEL_110:
          sprintf(v28, byte_5967B0, "NONE");
        }
        else
        {
          Buffer = 0;
          memset(v79, 0, sizeof(v79));
          v80 = 0;
          v81 = 0;
          sprintf(&Buffer, "%s%s", v29, (const char *)(v70 + 66));
LABEL_112:
          sprintf(v28, "Item\\%s\\%s.tga", v29, &Buffer);
        }
        ((gbGeomNode *)*(gbGeomNode **)&this->m_Ctrlbtn[1].m_mouseoff)->ReplaceTexture(v28);
        this->m_Ctrlbtn[1].m_texarrayInfo[2] = (_PlugInfo *)1;
goto LABEL_114;
      }
      break;
    default:
LABEL_114:
      v57 = (int *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(nVal2, nIndex);
      ((MainEquipUI *)v3)->SetSlotLabel(*v57, v57[1], v57[2]);
      break;
  }
}

// 0x0049C9F0
void MainEquipUI::SetSlotLabel(int nVal, int nVal2, int nVal3)
{
  CHAR *v5; // edi
  CHAR *v6; // ebp
  LPCSTR v7; // eax

  v5 = &this->buf[4];
  sprintf(&this->buf[4], g_szSceneUIText);
  v6 = sub_458F70((LPCSTR)(nVal3 + 96), (int)asc_5B74B8, &this->m_Is[3]);
  if ( lstrlenA(v6) <= 0 )
  {
    ((RoleAtt *)nVal3)->FormatAttributeText();
    lstrcpyA(v5, v7);
  }
  else
  {
    lstrcpyA(v5, v6);
  }
  ((UICaption *)&this->me_Role[4].m_RoleAtt[8].m_rect.right)->SetEnable((int)v5, 0);
  ((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right)->SetEnable((int)&this->m_Is[3], 0);
}

// 0x0049E670
void MainEquipUI::ResetControls()
{
  int i; // eax
  int v3; // eax

  this->i = 0;
  do
  {
    i = this->i;
    if ( *((_BYTE *)&this->m_TimeMoney.m_ratiow + i + 1) )
    {
      ((UIListBox *)&this->me_Role[1].m_EquipHat.m_caption[4892 * i + 144])->GetCurSel();
      ((UIListBox *)(&this->me_Role[1].m_EquipAdorn2.m_bvisible + 1223 * this->i))->GetCurSel();
      ((UIListBox *)&this->me_Role[1].m_EquipShoes.m_caption[4892 * this->i + 4])->GetCurSel();
      sprintf(
        &this->buf[4],
        "%d/%d",
        (int)*(float *)&this->me_Role[1].m_EquipCloth.m_texarray.m_ptex[1223 * this->i + 13],
        Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 9]);
      ((UICaption *)&this->me_Role[1].m_EquipCloth.m_caption[4892 * this->i + 44])->SetEnable((int)&this->buf[4], 0);
      sprintf(
        &this->buf[4],
        "%d/%d",
        (int)*(float *)&this->me_Role[1].m_EquipAdorn2.m_caption[4892 * this->i + 20],
        Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 10]);
      ((UICaption *)&this->me_Role[1].m_EquipAdorn2.m_caption[4892 * this->i + 108])->SetEnable((int)&this->buf[4], 0);
      sprintf(
        &this->buf[4],
        "%d/%d",
        (int)*((float *)&this->me_Role[1].m_EquipAdorn1.m_wndcolor.Color + 1223 * this->i),
        Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 11]);
      ((UICaption *)((char *)&this->me_Role[1].m_EquipAdorn1.m_texarray + 4892 * this->i))->SetEnable((int)&this->buf[4], 0);
      (**(void ( ***)(char *, _DWORD))&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i])(
        &this->me_Role[2].m_AttFramePose.m_text[4892 * this->i],
        0);
    }
    v3 = this->i + 1;
    this->i = v3;
  }
  while ( v3 < 5 );
  ((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right)->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->me_Role[4].m_RoleAtt[7].m_rect.right)->SetEnable((int)g_szSceneUIText, 0);
  this->m_Ctrlbtn[1].m_texarrayInfo[2] = 0;
}

// 0x0049E8E0
int MainEquipUI::CreateFromData(int *pBuffer)
{
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int v24; // eax
  UIStatic *v25; // edi
  int v26; // ebp
  int v27; // ebx
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int p_DWORD; // [esp+0x160] [ebp-0x70] BYREF
  int v36; // [esp+0x164] [ebp-0x6C]
  int nHeight; // [esp+0x168] [ebp-0x68]
  int v38; // [esp+0x16C] [ebp-0x64]
  _DWORD v39[2]; // [esp+0x170] [ebp-0x60] BYREF
  int v40; // [esp+0x178] [ebp-0x58]
  int v41; // [esp+0x17C] [ebp-0x54]
  _DWORD v42[2]; // [esp+0x180] [ebp-0x50] BYREF
  int v43; // [esp+0x188] [ebp-0x48]
  int v44; // [esp+0x18C] [ebp-0x44]
  gbVec3D pDir; // [esp+0x190] [ebp-0x40] BYREF
  int v46; // [esp+0x19C] [ebp-0x34]
  gbVec3D pPos; // [esp+0x1A0] [ebp-0x30] BYREF
  int v48; // [esp+0x1AC] [ebp-0x24]
  int v49; // [esp+0x1B0] [ebp-0x20] BYREF
  int v50; // [esp+0x1B4] [ebp-0x1C]
  int v51; // [esp+0x1B8] [ebp-0x18]
  int v52; // [esp+0x1BC] [ebp-0x14]
  int v53; // [esp+0x1C0] [ebp-0x10] BYREF
  int v54; // [esp+0x1C4] [ebp-0xC]
  int v55; // [esp+0x1C8] [ebp-0x8]
  int v56; // [esp+0x1CC] [ebp-0x4]

  v3 = pBuffer[1] - 2;
  v39[0] = *pBuffer + 15;
  v4 = v39[0] + 42;
  v40 = v39[0] + 42;
  LOBYTE(v4) = g_bDebugMode;
  v39[1] = v3;
  v41 = v3 + 50;
  (*(void ( **)(int *, char *, _DWORD *, MainEquipUI *, char *, int, int))(this->me_Role[4].m_RoleAttCng[1].m_childs.capacity
                                                                                              + 28))(
    &this->me_Role[4].m_RoleAttCng[1].m_childs.capacity,
    &byte_A00403,
    v39,
    this,
    "UI\\GameMainUI\\Prop\\Resume",
    1,
    v4);
  ((PalScript *)&this->me_Role[4].m_RoleAttCng[1].m_childs.capacity)->OpenScript("UI\\GameMainUI\\Prop\\Resume2.tga", g_bDebugMode);
  sub_445E50((int)&this->me_Role[4].m_RoleAttCng[1].m_childs.capacity);
  LOBYTE(v5) = g_bDebugMode;
  v39[0] = v40 + 11;
  v40 += 53;
  (*(void ( **)(float *, char *, _DWORD *, MainEquipUI *, char *, int, int))(LODWORD(this->me_Role[4].m_RoleAttCng[3].m_ratioh)
                                                                                     + 28))(
    &this->me_Role[4].m_RoleAttCng[3].m_ratioh,
    &byte_A00404,
    v39,
    this,
    "UI\\GameMainUI\\Prop\\Treasure",
    1,
    v5);
  ((PalScript *)&this->me_Role[4].m_RoleAttCng[3].m_ratioh)->OpenScript("UI\\GameMainUI\\Prop\\Treasure2.tga", g_bDebugMode);
  LOBYTE(v6) = g_bDebugMode;
  v39[0] = v40 + 11;
  v40 += 53;
  ((void ( *)(gbTexture **, char *, _DWORD *, MainEquipUI *, char *, int, int))this->me_Role[4].m_RoleAttCng[5].m_ppic->Height)(
    &this->me_Role[4].m_RoleAttCng[5].m_ppic,
    &byte_A00405,
    v39,
    this,
    "UI\\GameMainUI\\Prop\\Attack",
    1,
    v6);
  ((PalScript *)&this->me_Role[4].m_RoleAttCng[5].m_ppic)->OpenScript("UI\\GameMainUI\\Prop\\Attack2.tga", g_bDebugMode);
  LOBYTE(v7) = g_bDebugMode;
  v39[0] = v40 + 11;
  v40 += 53;
  (*(void ( **)(gbColorQuad *, char *, _DWORD *, MainEquipUI *, char *, int, int))(this->me_Role[4].m_RoleAttCng[8].m_wndcolor.Color
                                                                                           + 28))(
    &this->me_Role[4].m_RoleAttCng[8].m_wndcolor,
    &byte_A00406,
    v39,
    this,
    "UI\\GameMainUI\\Prop\\Smelt",
    1,
    v7);
  ((PalScript *)&this->me_Role[4].m_RoleAttCng[8].m_wndcolor)->OpenScript("UI\\GameMainUI\\Prop\\Smelt2.tga", g_bDebugMode);
  LOBYTE(v8) = g_bDebugMode;
  v39[0] = v40 + 11;
  v40 += 53;
  (*(void ( **)(int *, char *, _DWORD *, MainEquipUI *, char *, int, int))(this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel
                                                                                              + 28))(
    &this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel,
    &byte_A00407,
    v39,
    this,
    "UI\\GameMainUI\\Prop\\Ancient",
    1,
    v8);
  ((PalScript *)&this->me_Role[4].m_RoleAttEqual[0].m_childs.m_needscriptdel)->OpenScript("UI\\GameMainUI\\Prop\\Ancient2.tga", g_bDebugMode);
  LOBYTE(v9) = g_bDebugMode;
  v39[0] = v40 + 9;
  v40 += 51;
  (*(void ( **)(int *, int *, _DWORD *, MainEquipUI *, char *, int, int))(this->me_Role[4].m_RoleAttEqual[2].m_texty
                                                                                             + 28))(
    &this->me_Role[4].m_RoleAttEqual[2].m_texty,
    dword_A00408,
    v39,
    this,
    "UI\\GameMainUI\\Prop\\Special",
    1,
    v9);
  ((PalScript *)&this->me_Role[4].m_RoleAttEqual[2].m_texty)->OpenScript("UI\\GameMainUI\\Prop\\Special2.tga", g_bDebugMode);
  v10 = *pBuffer;
  v11 = *(_DWORD *)&this->me_Role[4].m_EquipHat.m_caption[16];
  v54 = pBuffer[1] + 52;
  v53 = v10 + 18;
  v56 = v54 + 32;
  v55 = v10 + 394;
  (*(void ( **)(char *, char *, int *, MainEquipUI *))(v11 + 16))(
    &this->me_Role[4].m_EquipHat.m_caption[16],
    byte_ABAB09,
    &v53,
    this);
  ((UIScene *)&this->me_Role[4].m_EquipHat.m_caption[16])->SetShow(0);
  sub_446010(&this->me_Role[4].m_EquipHat.m_caption[16]);
  sprintf(&this->buf[4], "%s                       %s", (const char *)dword_DC353C, (const char *)dword_DC373C);
  ((UICaption *)&this->me_Role[4].m_EquipHat.m_caption[16])->SetEnable((int)&this->buf[4], 0);
  v12 = pBuffer[1] + 76;
  p_DWORD = *pBuffer + 18;
  v36 = v12;
  nHeight = p_DWORD + 298;
  LODWORD(pPos.y) = v12 + 15;
  v13 = p_DWORD + 267;
  v38 = v12 + 288;
  LODWORD(pPos.x) = p_DWORD + 267;
  v48 = v12 + 41;
  LODWORD(pDir.x) = p_DWORD + 267;
  LOBYTE(v13) = g_bDebugMode;
  LODWORD(pDir.y) = v12 + 247;
  LODWORD(pPos.z) = p_DWORD + 289;
  LODWORD(pDir.z) = p_DWORD + 289;
  v46 = v12 + 273;
  v14 = (*(int ( **)(int *, char *, int *, MainEquipUI *, _DWORD, int, int))(this->me_Role[5].m_Jing.m_bcreateok
                                                                                                + 28))(
          &this->me_Role[5].m_Jing.m_bcreateok,
          &byte_A00416,
          &p_DWORD,
          this,
          0,
          1,
          v13);
  LOBYTE(v14) = g_bDebugMode;
  ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v14);
  this->m_ClothName.m_benable = -4;
  this->m_ClothName.m_bfocus = -6;
  this->m_ClothName.pDebugTex = (gbTexture *)10;
  ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo)->ShowEffect(v36 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo)->SetSelection(27);
  ((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo)->SetCurPlayer(5);
  ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->SetLockSel();
  ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->SetFirstShow((int)"Name", 220);
  ((UIListBox *)&this->me_Role[5].m_Jing.m_bcreateok)->SetFirstShow((int)&g_pCombatUIData, 36);
  ((CCBUI *)&this->me_Role[5].m_Jing.m_disablepicInfo)->VirtualCall();
  (*(void ( **)(int *, _DWORD))this->me_Role[5].m_Jing.m_bcreateok)(
    &this->me_Role[5].m_Jing.m_bcreateok,
    0);
  LOBYTE(v15) = g_bDebugMode;
  v16 = (*(int ( **)(char *, char *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)&this->m_ClothName.m_text[12]
                                                                                      + 28))(
          &this->m_ClothName.m_text[12],
          &byte_A00417,
          &p_DWORD,
          this,
          0,
          1,
          v15);
  LOBYTE(v16) = g_bDebugMode;
  ((UIListBox *)&this->m_ClothName.m_text[12])->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v16);
  this->m_RemarkVal.m_nTextW = -4;
  *((_DWORD *)&this->m_RemarkVal + 38) = -6;
  *((_DWORD *)&this->m_RemarkVal + 39) = 10;
  ((UIListBox *)&this->m_ClothName.m_text[12])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_ShoesName.m_rect.bottom)->ShowEffect(v36 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_ShoesName.m_rect.bottom)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_ShoesName.m_rect.bottom)->SetSelection(27);
  ((CCBUI *)&this->m_ShoesName.m_rect.bottom)->SetCurPlayer(5);
  ((UIListBox *)&this->m_ClothName.m_text[12])->SetLockSel();
  ((UIListBox *)&this->m_ClothName.m_text[12])->SetFirstShow((int)"Name", 220);
  ((UIListBox *)&this->m_ClothName.m_text[12])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((CCBUI *)&this->m_ShoesName.m_rect.bottom)->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_ClothName.m_text[12])(&this->m_ClothName.m_text[12], 0);
  LOBYTE(v17) = g_bDebugMode;
  v18 = (*((int ( **)(PtrArray *, char *, int *, MainEquipUI *, _DWORD, int, int))this->m_typeWord.m_childs.m_pData
         + 7))(
          &this->m_typeWord.m_childs,
          &byte_A00418,
          &p_DWORD,
          this,
          0,
          1,
          v17);
  LOBYTE(v18) = g_bDebugMode;
  ((UIListBox *)&this->m_typeWord.m_childs)->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v18);
  *(_DWORD *)&this->m_role[1].Remark[162] = -4;
  *(_DWORD *)&this->m_role[1].Remark[166] = -6;
  *(_DWORD *)&this->m_role[1].Remark[170] = 10;
  ((UIListBox *)&this->m_typeWord.m_childs)->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_typeWord.m_pbkInfo)->ShowEffect(v36 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_typeWord.m_pbkInfo)->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_typeWord.m_pbkInfo)->SetSelection(27);
  ((CCBUI *)&this->m_typeWord.m_pbkInfo)->SetCurPlayer(5);
  ((UIListBox *)&this->m_typeWord.m_childs)->SetLockSel();
  ((UIListBox *)&this->m_typeWord.m_childs)->SetFirstShow((int)"Name", 220);
  ((UIListBox *)&this->m_typeWord.m_childs)->SetFirstShow((int)&g_pCombatUIData, 36);
  ((CCBUI *)&this->m_typeWord.m_pbkInfo)->VirtualCall();
  (*(void ( **)(PtrArray *, _DWORD))this->m_typeWord.m_childs.m_pData)(&this->m_typeWord.m_childs, 0);
  LOBYTE(v19) = g_bDebugMode;
  v20 = (*(int ( **)(char *, char *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)&this->m_role[1].Remark[210]
                                                                                      + 28))(
          &this->m_role[1].Remark[210],
          byte_A00419,
          &p_DWORD,
          this,
          0,
          1,
          v19);
  LOBYTE(v20) = g_bDebugMode;
  ((UIListBox *)&this->m_role[1].Remark[210])->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v20);
  *(_DWORD *)&this->m_role[2].ModelID[6] = -4;
  *(_DWORD *)&this->m_role[2].ModelID[10] = -6;
  *(_DWORD *)&this->m_role[2].ModelID[14] = 10;
  ((UIListBox *)&this->m_role[1].Remark[210])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_role[1].Remark[290])->ShowEffect(v36 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_role[1].Remark[290])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_role[1].Remark[290])->SetSelection(27);
  ((CCBUI *)&this->m_role[1].Remark[290])->SetCurPlayer(5);
  ((UIListBox *)&this->m_role[1].Remark[210])->SetLockSel();
  ((UIListBox *)&this->m_role[1].Remark[210])->SetFirstShow((int)"Name", 220);
  ((UIListBox *)&this->m_role[1].Remark[210])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((CCBUI *)&this->m_role[1].Remark[290])->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_role[1].Remark[210])(&this->m_role[1].Remark[210], 0);
  LOBYTE(v21) = g_bDebugMode;
  v22 = (*(int ( **)(char *, char *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)&this->m_role[2].ImageID[24]
                                                                                      + 28))(
          &this->m_role[2].ImageID[24],
          &byte_A00420,
          &p_DWORD,
          this,
          0,
          1,
          v21);
  LOBYTE(v22) = g_bDebugMode;
  ((UIListBox *)&this->m_role[2].ImageID[24])->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v22);
  *(_DWORD *)&this->m_role[4].Remark[22] = -4;
  *(_DWORD *)&this->m_role[4].Remark[26] = -6;
  *(_DWORD *)&this->m_role[4].Remark[30] = 10;
  ((UIListBox *)&this->m_role[2].ImageID[24])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_role[2].rolevalue[4])->ShowEffect(v36 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_role[2].rolevalue[4])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_role[2].rolevalue[4])->SetSelection(27);
  ((CCBUI *)&this->m_role[2].rolevalue[4])->SetCurPlayer(5);
  ((UIListBox *)&this->m_role[2].ImageID[24])->SetLockSel();
  ((UIListBox *)&this->m_role[2].ImageID[24])->SetFirstShow((int)"Name", 220);
  ((UIListBox *)&this->m_role[2].ImageID[24])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((CCBUI *)&this->m_role[2].rolevalue[4])->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_role[2].ImageID[24])(&this->m_role[2].ImageID[24], 0);
  LOBYTE(v23) = g_bDebugMode;
  v24 = (*(int ( **)(char *, char *, int *, MainEquipUI *, _DWORD, int, int))(*(_DWORD *)&this->m_role[4].Remark[70]
                                                                                      + 28))(
          &this->m_role[4].Remark[70],
          byte_A00421,
          &p_DWORD,
          this,
          0,
          1,
          v23);
  LOBYTE(v24) = g_bDebugMode;
  ((UIListBox *)&this->m_role[4].Remark[70])->GetSel((int)"UI\\assistant\\Communal\\ListBoxSelPic.tga", v24);
  this->m_Dlg.m_static.m_ratioh = NAN;
  this->m_Dlg.m_static.m_textx = -6;
  this->m_Dlg.m_static.m_texty = 10;
  ((UIListBox *)&this->m_role[4].Remark[70])->GetLockSel((int)"UI\\GameMainUI\\Communal\\Scroll\\scrollbar", &p_DWORD, 38, 27, 0);
  ((CCBUI *)&this->m_role[4].Remark[150])->ShowEffect(v36 + 1, nHeight - 38, nHeight);
  ((CCBUI *)&this->m_role[4].Remark[150])->SetTargetPos(&pPos, &pDir);
  ((CCBUI *)&this->m_role[4].Remark[150])->SetSelection(27);
  ((CCBUI *)&this->m_role[4].Remark[150])->SetCurPlayer(5);
  ((UIListBox *)&this->m_role[4].Remark[70])->SetLockSel();
  ((UIListBox *)&this->m_role[4].Remark[70])->SetFirstShow((int)"Name", 220);
  ((UIListBox *)&this->m_role[4].Remark[70])->SetFirstShow((int)&g_pCombatUIData, 36);
  ((CCBUI *)&this->m_role[4].Remark[150])->VirtualCall();
  (**(void ( ***)(char *, _DWORD))&this->m_role[4].Remark[70])(&this->m_role[4].Remark[70], 0);
  v50 = v36 + 2;
  v49 = p_DWORD;
  v51 = p_DWORD + 256;
  v52 = v36 + 25;
  v25 = (UIStatic *)&this->me_Role[4].m_EquipCloth.m_caption[60];
  v26 = 12;
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, MainEquipUI *))v25->__vftable->Create)(v25, 161, &v49, this);
    ((UIStatic *)v25++)->CreateFromTemplate();
    v50 = v52;
    --v26;
    v52 += 23;
  }
  while ( v26 );
  v27 = *pBuffer;
  v28 = *((_DWORD *)&this->m_Dlg.m_btRc + 39);
  v42[1] = v38 + 3;
  v29 = v38 + 23;
  v44 = v38 + 23;
  LOBYTE(v29) = g_bDebugMode;
  v42[0] = v27 + 20;
  v43 = v27 + 114;
  (*(void ( **)(char *, char *, _DWORD *, MainEquipUI *, char *, int, int))(v28 + 28))(
    (char *)&this->m_Dlg.m_btRc + 156,
    &byte_A00427,
    v42,
    this,
    "UI\\GameMainUI\\Communal\\SortUse",
    1,
    v29);
  v30 = *((_DWORD *)&this->m_Dlg.m_btRc + 125);
  v42[0] = v43 + 8;
  v43 += 102;
  v31 = v43;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(char *, char *, _DWORD *, MainEquipUI *, char *, int, int))(v30 + 28))(
    (char *)&this->m_Dlg.m_btRc + 500,
    &byte_A00428,
    v42,
    this,
    "UI\\GameMainUI\\Communal\\SortPrice",
    1,
    v31);
  v32 = *(_DWORD *)&this->m_Ctrlbtn[0].m_bBigFont;
  v42[0] = v43 + 8;
  v43 += 102;
  v33 = v43;
  LOBYTE(v33) = g_bDebugMode;
  return (*(int ( **)(_BYTE *, char *, _DWORD *, MainEquipUI *, char *, int, int))(v32 + 28))(
           &this->m_Ctrlbtn[0].m_bBigFont,
           byte_A00429,
           v42,
           this,
           "UI\\GameMainUI\\Communal\\SortFunc",
           1,
           v33);
}

// 0x0049F2E0
void * MainEquipUI::CreateListPanel(int nVal, int FC)
{
  LONG bkWndX; // eax
  LONG bkWndY; // ecx
  int v6; // eax
  int v7; // edx
  int v8; // edx
  unsigned int Color; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax
  LONG right; // eax
  LONG v14; // edx
  LONG v15; // eax
  int capacity; // edx
  gbTexture *v17; // eax
  LONG left; // edx
  void *result; // eax
  int v20; // [esp+0x60] [ebp-0x94]
  int *v21; // [esp+0x64] [ebp-0x90]
  int v22; // [esp+0x68] [ebp-0x8C]
  int v23; // [esp+0x74] [ebp-0x80] BYREF
  int v24; // [esp+0x78] [ebp-0x7C]
  int v25; // [esp+0x7C] [ebp-0x78]
  int v26; // [esp+0x80] [ebp-0x74]
  int v27; // [esp+0x84] [ebp-0x70] BYREF
  int v28; // [esp+0x88] [ebp-0x6C]
  int v29; // [esp+0x8C] [ebp-0x68]
  int v30; // [esp+0x90] [ebp-0x64]
  int v31; // [esp+0x94] [ebp-0x60] BYREF
  int v32; // [esp+0x98] [ebp-0x5C]
  int v33; // [esp+0x9C] [ebp-0x58]
  int v34; // [esp+A0h] [ebp-0x54]
  int pnVal; // [esp+A4h] [ebp-0x50] BYREF
  int v36; // [esp+A8h] [ebp-0x4C]
  int v37; // [esp+ACh] [ebp-0x48]
  int v38; // [esp+B0h] [ebp-0x44]
  int pBuffer; // [esp+B4h] [ebp-0x40] BYREF
  int v40; // [esp+B8h] [ebp-0x3C]
  int v41; // [esp+BCh] [ebp-0x38]
  int v42; // [esp+C0h] [ebp-0x34]
  int nVal2[4]; // [esp+C4h] [ebp-0x30] BYREF
  _DWORD v44[4]; // [esp+D4h] [ebp-0x20] BYREF
  _DWORD v45[4]; // [esp+E4h] [ebp-0x10] BYREF

  bkWndX = this->bkWndX;
  bkWndY = this->bkWndY;
  this->rc.right = bkWndX;
  this->rc.top = 0;
  this->rc.left = 0;
  this->rc.bottom = bkWndY;
  ((UIListBox *)this)->SetSelTexture(-1, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom, 0);
  v6 = this->rc.top + 18;
  v31 = this->rc.left + 592;
  v32 = v6;
  v33 = v31 + 192;
  v34 = v6 + 526;
  (*(void ( **)(_PlugInfo **, int, int *, MainEquipUI *))&this->m_TimeMoney.m_pbkInfo->name[12])(
    &this->m_TimeMoney.m_pbkInfo,
    161,
    &v31,
    this);
  ((UIStatic *)&this->m_TimeMoney.m_pbkInfo)->CreateFromTemplate();
  v7 = *(_DWORD *)&this->m_TopFrame.m_text[12];
  v32 += 26;
  v31 = v33;
  v34 = v32 + 526;
  v33 += 17;
  (*(void ( **)(char *, int, int *, MainEquipUI *))(v7 + 16))(&this->m_TopFrame.m_text[12], 161, &v31, this);
  ((UIStatic *)&this->m_TopFrame.m_text[12])->CreateFromTemplate();
  v24 = 0;
  v23 = v33 - 205;
  v25 = v33 - 205 + 203;
  v8 = *(_DWORD *)&this->m_TopFrameZB.m_text[4];
  v26 = 64;
  (*(void ( **)(char *, int, int *, MainEquipUI *))(v8 + 16))(&this->m_TopFrameZB.m_text[4], 161, &v23, this);
  ((UIStatic *)&this->m_TopFrameZB.m_text[4])->CreateFromTemplate();
  Color = this->stp_Effect.m_wndcolor.Color;
  v24 = -4;
  v23 = 618;
  v25 = 738;
  v26 = 28;
  (*(void ( **)(gbColorQuad *, int, int *, MainEquipUI *))(Color + 16))(
    &this->stp_Effect.m_wndcolor,
    161,
    &v23,
    this);
  ((UIScene *)&this->stp_Effect.m_wndcolor)->SetShow(0);
  sub_446010(&this->stp_Effect.m_wndcolor);
  v10 = *(_DWORD *)&this->stp_Exit.m_caption[8];
  v24 = 16;
  v23 = 668;
  v25 = 748;
  v26 = 48;
  (*(void ( **)(char *, int, int *, MainEquipUI *))(v10 + 16))(&this->stp_Exit.m_caption[8], 161, &v23, this);
  ((UIScene *)&this->stp_Exit.m_caption[8])->SetShow(0);
  sub_446010(&this->stp_Exit.m_caption[8]);
  ((LineupUI *)this)->RebuildCaptionPage();
  v36 = 0;
  pnVal = 0;
  v37 = 0;
  v38 = 32;
  nVal2[1] = 0;
  nVal2[0] = 12;
  nVal2[2] = 590;
  nVal2[3] = 126;
  this->i = 0;
  do
  {
    ((UITitle_XJTM *)this)->UpdateMonsterEntry2(this->i, &pnVal);
    ((ArcSceneMonster *)this)->CreateStatusPanel(this->i, (int)nVal2, v20, v21, v22);
    v11 = this->i + 1;
    this->i = v11;
  }
  while ( v11 < 5 );
  this->i = 0;
  do
  {
    (*(void ( **)(char *, _DWORD, int *, MainEquipUI *))(*(_DWORD *)&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i]
                                                                 + 16))(
      &this->me_Role[2].m_AttFramePose.m_text[4892 * this->i],
      *(&g_ArcSceneMonsterTable2 + this->i),
      nVal2,
      this);
    ((UIStatic *)&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i])->CreateFromTemplate();
    (**(void ( ***)(char *, _DWORD))&this->me_Role[2].m_AttFramePose.m_text[4892 * this->i])(
      &this->me_Role[2].m_AttFramePose.m_text[4892 * this->i],
      0);
    v12 = this->i + 1;
    this->i = v12;
  }
  while ( v12 < 5 );
  right = this->me_Role[4].m_RoleAtt[6].m_rect.right;
  v28 = 125;
  v27 = 10;
  v29 = 242;
  v30 = 539;
  (*(void ( **)(LONG *, char *, int *, MainEquipUI *))(right + 16))(
    &this->me_Role[4].m_RoleAtt[6].m_rect.right,
    byte_A00401,
    &v27,
    this);
  ((UIStatic *)&this->me_Role[4].m_RoleAtt[6].m_rect.right)->CreateFromTemplate();
  v14 = this->me_Role[4].m_RoleAtt[7].m_rect.right;
  v28 = 372;
  v27 = 22;
  v29 = 234;
  v30 = 540;
  (*(void ( **)(LONG *, char *, int *, MainEquipUI *))(v14 + 16))(
    &this->me_Role[4].m_RoleAtt[7].m_rect.right,
    byte_A00401,
    &v27,
    this);
  ((UIScene *)&this->me_Role[4].m_RoleAtt[7].m_rect.right)->SetShow(0);
  sub_446010(&this->me_Role[4].m_RoleAtt[7].m_rect.right);
  v15 = this->me_Role[4].m_RoleAtt[8].m_rect.right;
  v28 = 504;
  v27 = 22;
  v29 = 234;
  v30 = 536;
  (*(void ( **)(LONG *, char *, int *, MainEquipUI *))(v15 + 16))(
    &this->me_Role[4].m_RoleAtt[8].m_rect.right,
    byte_A00401,
    &v27,
    this);
  ((UIScene *)&this->me_Role[4].m_RoleAtt[8].m_rect.right)->SetShow(0);
  sub_446010(&this->me_Role[4].m_RoleAtt[8].m_rect.right);
  capacity = this->me_Role[4].m_RoleAtt[9].m_childs.capacity;
  v44[1] = 142;
  v44[0] = 195;
  v44[2] = 211;
  v44[3] = 174;
  (*(void ( **)(int *, char *, _DWORD *, MainEquipUI *))(capacity + 16))(
    &this->me_Role[4].m_RoleAtt[9].m_childs.capacity,
    byte_A00401,
    v44,
    this);
  ((UIStatic *)&this->me_Role[4].m_RoleAtt[9].m_childs.capacity)->CreateFromTemplate();
  v17 = this->me_Role[4].m_EquipCloth.m_texarray.m_ptex[1];
  v40 = 125;
  pBuffer = 251;
  v41 = 587;
  v42 = 518;
  (*((void ( **)(gbTexture **, int, int *, MainEquipUI *))v17 + 4))(
    &this->me_Role[4].m_EquipCloth.m_texarray.m_ptex[1],
    161,
    &pBuffer,
    this);
  ((UIStatic *)&this->me_Role[4].m_EquipCloth.m_texarray.m_ptex[1])->CreateFromTemplate();
  left = this->me_Role[4].m_EquipCloth.m_rect.left;
  v45[1] = v40;
  v45[0] = pBuffer + 7;
  v45[3] = v40 + 32;
  v45[2] = pBuffer + 327;
  (*(void ( **)(tagRECT *, char *, _DWORD *, char *, _DWORD, MainEquipUI *))(left + 28))(
    &this->me_Role[4].m_EquipCloth.m_rect,
    &byte_A00400,
    v45,
    "UI\\Flex\\Bar.tga",
    0,
    this);
  ((CScreenMode *)&this->me_Role[4].m_EquipCloth.m_rect)->SetPosition(32,   32);
  this->CreateFromData(&pBuffer);
  ((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray)->CreateScriptAndCamera((int)dword_A00430, (int)this);
  if ( !strcmp("D16", g_szSceneUIText) )
    sprintf(&this->buf[4], byte_5967B0, "NONE");
  else
    sprintf(&this->buf[4], "Item\\%s\\%s.pol", "D16", "D16");
  ((PalScript *)&this->m_Ctrlbtn[1].m_texarrayInfo[1])->LoadModel(&this->buf[4], 0);
  this->m_Ctrlbtn[1].m_texarrayInfo[2] = 0;
  this->m_Ctrlbtn[1].m_texarrayInfo[0] = (_PlugInfo *)1;
  ((CCBFiveNimbusWindow *)&this->m_Ctrlbtn[1].m_texarray)->SetFloatParam(160.0);
  ((Camera *)&this->m_Ctrlbtn[1].m_texarray)->UpdateCameraLookAt(128, 258, 600);
  ((UIPushButton *)&this->m_Ctrlbtn[1].m_texarray)->SetAnimOffset(1, 0, *(float *)&v20);
  pnVal = 300;
  v38 = 300;
  v36 = 200;
  v37 = 500;
  ((ARC_PlayerAtt *)&this->me_Role[1].m_RoleAttEqual[1].m_pfather)->Create((int)&g_PlayerAttBuffer2.skill[2], (int)&pnVal);
  result = ((UIItem *)&this->me_Role[1].m_RoleAttEqual[1].m_pfather)->SetData(31);
  BYTE1(this->m_TimeMoney.m_texty) = 1;
  this->m_TimeMoney.m_pbk = (gbTexture *)nVal;
  return result;
}

// 0x004A2450
int MainEquipUI::_MainEquipUI()
{
  int result; // eax

  ((UIGameFrm *)this)->Destroy();
  ((UIFrameWnd *)&this->me_Role[3].m_EquipShoes.m_childs.m_nSize)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)(&this->me_Role[3].m_EquipHat.m_benable_snd + 16))->Destroy2();
  ((UIFrameWnd *)&this->me_Role[3].m_RoleAttEqual[8].m_disablepic)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[1].m_RoleAttEqual[2].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[1].m_RoleAttEqual[1].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[1].m_RoleAttEqual[0].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->me_Role[1].m_RoleAttCng[9].pDebugTex)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->stp_Exit.m_hasDBclk)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->stp_System.m_caption[68])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->stp_System.m_bBigFont)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->stp_TaskBook.m_bBigFont)->Destroy2();
  ((UICaption *)&this->stp_BattleArray.m_bBigFont)->Destroy2();
  ((UICaption *)&this->stp_Prop.m_bBigFont)->Destroy2();
  ((UICaption *)&this->stp_Equip.m_bBigFont)->Destroy2();
  ((UICaption *)&this->stp_Magic.m_bBigFont)->Destroy2();
  ((UICaption *)&this->stp_State.m_bBigFont)->Destroy2();
  ((UICaption *)(&this->stp_BarL + 1))->Destroy2();
  ((UICaption *)&this->m_OutFrameL.m_disablepic)->Destroy2();
  ((UICaption *)&this->m_OutFrameT.m_text[8])->Destroy2();
  ((UIFrameWnd *)&this->m_ScrollHB.m_pbk)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_TopFrameZB.m_ppic)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_TopFrame.m_disablepic)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_TimeMoney.m_pbk2)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Frame.m_FVF)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_CurType)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
  return result;
}

// 0x004A4780
int MainEquipUI::HandleDeviceLostB()
{
  PAL3 *Instance_db10; // eax
  PAL3 *v3; // ecx
  float m_snaph; // ecx
  int v5; // eax
  PAL3 *v6; // eax
  int result; // eax
  PAL3 *v8; // ecx
  unsigned __int8 v9; // bl
  PAL3 *v10; // ecx
  PAL3 *v11; // eax
  PAL3 *v12; // ecx
  PAL3 *v13; // eax

  Instance_db10 = ((PAL3 *)this)->GetInstance_db10();
  ((RenderTarget *)Instance_db10)->OnDeviceLost(1);
  m_snaph = ((PAL3 *)v3)->GetInstance_db10()->m_snaph;
  v5 = 1061158912;
  if ( m_snaph != 0.0 )
    v5 = 1065353216;
  *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[12] = v5;
  *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[8] = v5;
  v6 = ((PAL3 *)LODWORD(m_snaph))->GetInstance_db10();
  LOBYTE(result) = ((RenderTarget *)v6)->OnResetDevice(1);
  if ( (_BYTE)result )
  {
    v9 = g_bGameFlag2;
    g_bGameFlag2 = 0;
    ((PAL3 *)v8)->Render();
    g_bGameFlag2 = v9;
    v11 = ((PAL3 *)v10)->GetInstance_db10();
    ((RenderTarget *)v11)->RenderToScreen();
    *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4] = 0;
    v13 = ((PAL3 *)v12)->GetInstance_db10();
    result = (int)((RenderTarget *)v13)->GetActiveTexture();
    if ( result )
    {
      if ( *(_DWORD *)(result + 84) )
        *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4] = result;
    }
  }
  else
  {
    *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4] = 0;
  }
  return result;
}

// 0x004A4820
int MainEquipUI::Render_4a4820()
{
  int result; // eax

  result = *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4];
  if ( result )
    return crt_sub_00540D20();
  return result;
}

// 0x004A4ED0
int MainEquipUI::ShowPage()
{
  char *v2; // ebx

  v2 = &this->m_OutFrameT.m_text[8];
  ((PalScript *)&this->m_OutFrameT.m_text[8])->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnState.tga", g_bDebugMode);
  if ( !g_bRoleFlag1 )
    ((PalScript *)&this->stp_Magic.m_bBigFont)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_Magic.m_bBigFont);
  if ( !g_bRoleFlag2 )
    ((PalScript *)&this->stp_Equip.m_bBigFont)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_Equip.m_bBigFont);
  sub_445E50((int)v2);
  sub_445E50((int)&this->m_OutFrameL.m_disablepic);
  sub_445E50((int)(&this->stp_BarL + 1));
  sub_445E50((int)&this->stp_State.m_bBigFont);
  sub_445E50((int)&this->stp_Prop.m_bBigFont);
  sub_445E50((int)&this->stp_BattleArray.m_bBigFont);
  return sub_445E50((int)&this->stp_TaskBook.m_bBigFont);
}

// 0x004A4FC0
BOOL MainEquipUI::SetEquipSlotData()
{
  BOOL result; // eax

  this->me_Role[3].m_EquipShoes.m_childs.m_pData = (char *)7;
  LOBYTE(gfxMgr->pSceneGraph->pnodebuf[713]) = 0;
  LOBYTE(this->me_Role[3].m_EquipShoes.m_childs.capacity) = g_bRoleSystem_5CEFA9;
  g_bRoleSystem_5CEFA9 = 1;
  result = this->HandleMessage();
  BYTE1(this->me_Role[3].m_EquipShoes.m_childs.capacity) = 1;
  return result;
}

// 0x004A5010
BOOL MainEquipUI::HandleMessage()
{
  BOOL result; // eax
  void *m_id; // ecx
  LONG left; // ecx
  LONG top; // ecx
  LONG right; // ecx
  unsigned int Color; // ecx
  LONG bottom; // ecx
  void *v9; // ecx
  LONG v10; // ecx
  LONG v11; // ecx
  LONG v12; // ecx
  unsigned int v13; // ecx
  void *v14; // ecx
  LONG v15; // ecx
  LONG v16; // ecx
  LONG v17; // ecx
  unsigned int v18; // ecx
  void *v19; // ecx
  LONG v20; // ecx
  LONG v21; // ecx
  LONG v22; // ecx
  unsigned int v23; // ecx
  void *v24; // ecx
  LONG v25; // ecx
  LONG v26; // ecx
  LONG v27; // ecx
  unsigned int v28; // ecx
  void *v29; // ecx
  LONG v30; // ecx
  LONG v31; // ecx
  LONG v32; // ecx
  unsigned int v33; // ecx
  LONG v34; // ecx
  void *v35; // ecx
  LONG v36; // ecx
  LONG v37; // ecx
  LONG v38; // ecx
  unsigned int v39; // ecx
  LONG v40; // ecx
  UIWnd *m_pfather; // ecx
  void *v42; // ecx
  LONG v43; // ecx
  LONG v44; // ecx
  LONG v45; // ecx
  unsigned int v46; // ecx
  LONG v47; // ecx
  UIWnd *v48; // ecx
  void *v49; // ecx
  LONG v50; // ecx
  LONG v51; // ecx
  LONG v52; // ecx
  unsigned int v53; // ecx
  void *v54; // ecx
  LONG v55; // ecx
  LONG v56; // ecx
  LONG v57; // ecx
  unsigned int v58; // ecx
  LONG v59; // ecx
  UIWnd *v60; // ecx
  char *v61; // [esp+0x8] [ebp+0x4]

  result = (BOOL)v61;
  this->me_Role[3].m_EquipShoes.m_childs.m_pData = v61;
  switch ( (unsigned int)v61 )
  {
    case 0u:
      LOBYTE(gfxMgr->pSceneGraph->pnodebuf[713]) = 0;
      result = this->OnMessage(1000, 1, 0);
      m_id = this->me_Role[3].m_EquipShoes.m_id;
      if ( m_id )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)m_id + 24))(m_id, 1000, 0, 0);
      left = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( left )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)left + 24))(left, 1000, 0, 0);
      top = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( top )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)top + 24))(top, 1000, 0, 0);
      right = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( right )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)right + 24))(right, 1000, 0, 0);
      Color = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( Color )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)Color + 24))(
                   Color,
                   1000,
                   0,
                   0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( !bottom )
        break;
      goto LABEL_115;
    case 1u:
      result = this->OnMessage(1000, 0, 0);
      v19 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v19 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v19 + 24))(v19, 1000, 0, 0);
      v20 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v20 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v20 + 24))(v20, 1000, 0, 0);
      v21 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v21 )
        result = (*(int ( **)(LONG, int, int, _DWORD))(*(_DWORD *)v21 + 24))(v21, 1000, 1, 0);
      v22 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v22 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v22 + 24))(v22, 1000, 0, 0);
      v23 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v23 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v23 + 24))(v23, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 2u:
      result = this->OnMessage(1000, 0, 0);
      v14 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v14 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v14 + 24))(v14, 1000, 0, 0);
      v15 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v15 )
        result = (*(int ( **)(LONG, int, int, _DWORD))(*(_DWORD *)v15 + 24))(v15, 1000, 1, 0);
      v16 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v16 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v16 + 24))(v16, 1000, 0, 0);
      v17 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v17 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v17 + 24))(v17, 1000, 0, 0);
      v18 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v18 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v18 + 24))(v18, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 3u:
      result = this->OnMessage(1000, 0, 0);
      v9 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v9 )
        result = (*(int ( **)(void *, int, int, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1000, 1, 0);
      v10 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v10 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1000, 0, 0);
      v11 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v11 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 0, 0);
      v12 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v12 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 0, 0);
      v13 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v13 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v13 + 24))(v13, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 4u:
      result = this->OnMessage(1000, 0, 0);
      v35 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v35 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v35 + 24))(v35, 1000, 0, 0);
      v36 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v36 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v36 + 24))(v36, 1000, 0, 0);
      v37 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v37 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v37 + 24))(v37, 1000, 0, 0);
      v38 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v38 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v38 + 24))(v38, 1000, 0, 0);
      v39 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v39 )
        result = (*(int ( **)(unsigned int, int, int, _DWORD))(*(_DWORD *)v39 + 24))(v39, 1000, 1, 0);
      v40 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v40 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v40 + 24))(v40, 1000, 0, 0);
      m_pfather = this->me_Role[3].m_EquipShoes.m_pfather;
      if ( m_pfather )
// [VFTABLE] return ((BOOL ( *)(UIWnd *, int, _DWORD, _DWORD))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1000,
// [VFTABLE]   0,
// [VFTABLE]   0);
      return result;
    case 5u:
      LOBYTE(result) = g_bRoleFlag1;
      if ( !g_bRoleFlag1 )
        return result;
      result = this->OnMessage(1000, 0, 0);
      v24 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v24 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v24 + 24))(v24, 1000, 0, 0);
      v25 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v25 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v25 + 24))(v25, 1000, 0, 0);
      v26 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v26 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v26 + 24))(v26, 1000, 0, 0);
      v27 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v27 )
        result = (*(int ( **)(LONG, int, int, _DWORD))(*(_DWORD *)v27 + 24))(v27, 1000, 1, 0);
      v28 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v28 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v28 + 24))(v28, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
LABEL_115:
        result = (*(int ( **)(int, _DWORD, _DWORD))(*(_DWORD *)bottom + 24))(1000, 0, 0);
      break;
    case 6u:
      LOBYTE(result) = g_bRoleFlag2;
      if ( !g_bRoleFlag2 )
        return result;
      result = this->OnMessage(1000, 0, 0);
      v29 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v29 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v29 + 24))(v29, 1000, 0, 0);
      v30 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v30 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v30 + 24))(v30, 1000, 0, 0);
      v31 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v31 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v31 + 24))(v31, 1000, 0, 0);
      v32 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v32 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v32 + 24))(v32, 1000, 0, 0);
      v33 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v33 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v33 + 24))(v33, 1000, 0, 0);
      v34 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v34 )
        result = (*(int ( **)(int, int, _DWORD))(*(_DWORD *)v34 + 24))(1000, 1, 0);
      break;
    case 7u:
      result = this->OnMessage(1000, 0, 0);
      v42 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v42 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v42 + 24))(v42, 1000, 0, 0);
      v43 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v43 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v43 + 24))(v43, 1000, 0, 0);
      v44 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v44 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v44 + 24))(v44, 1000, 0, 0);
      v45 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v45 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v45 + 24))(v45, 1000, 0, 0);
      v46 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v46 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v46 + 24))(v46, 1000, 0, 0);
      v47 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v47 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v47 + 24))(v47, 1000, 0, 0);
      v48 = this->me_Role[3].m_EquipShoes.m_pfather;
      if ( v48 )
// [VFTABLE] return ((BOOL ( *)(UIWnd *, int, int, _DWORD))v48->__vftable->OnMessage)(v48, 1000, 1, 0);
      return result;
    case 8u:
      result = this->OnMessage(1000, 0, 0);
      v49 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v49 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v49 + 24))(v49, 1000, 0, 0);
      v50 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v50 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v50 + 24))(v50, 1000, 0, 0);
      v51 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v51 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v51 + 24))(v51, 1000, 0, 0);
      v52 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v52 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v52 + 24))(v52, 1000, 0, 0);
      v53 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v53 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v53 + 24))(v53, 1000, 0, 0);
      bottom = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( bottom )
        goto LABEL_115;
      break;
    case 9u:
      result = this->OnMessage(1000, 0, 0);
      v54 = this->me_Role[3].m_EquipShoes.m_id;
      if ( v54 )
        result = (*(int ( **)(void *, int, _DWORD, _DWORD))(*(_DWORD *)v54 + 24))(v54, 1000, 0, 0);
      v55 = this->me_Role[3].m_EquipShoes.m_rect.left;
      if ( v55 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v55 + 24))(v55, 1000, 0, 0);
      v56 = this->me_Role[3].m_EquipShoes.m_rect.top;
      if ( v56 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v56 + 24))(v56, 1000, 0, 0);
      v57 = this->me_Role[3].m_EquipShoes.m_rect.right;
      if ( v57 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v57 + 24))(v57, 1000, 0, 0);
      v58 = this->me_Role[3].m_EquipShoes.m_wndcolor.Color;
      if ( v58 )
        result = (*(int ( **)(unsigned int, int, _DWORD, _DWORD))(*(_DWORD *)v58 + 24))(v58, 1000, 0, 0);
      v59 = this->me_Role[3].m_EquipShoes.m_rect.bottom;
      if ( v59 )
        result = (*(int ( **)(LONG, int, _DWORD, _DWORD))(*(_DWORD *)v59 + 24))(v59, 1000, 0, 0);
      v60 = this->me_Role[3].m_EquipShoes.m_pfather;
      if ( v60 )
// [VFTABLE] result = ((int ( *)(UIWnd *, int, _DWORD, _DWORD))v60->__vftable->OnMessage)(v60, 1000, 0, 0);
      LOBYTE(result) = BYTE1(this->me_Role[3].m_EquipShoes.m_childs.capacity);
      *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4] = 0;
      if ( result )
      {
        g_bRoleSystem_5CEFA9 = this->me_Role[3].m_EquipShoes.m_childs.capacity;
        BYTE1(this->me_Role[3].m_EquipShoes.m_childs.capacity) = 0;
      }
      return result;
    case 0xAu:
      *(_DWORD *)&this->me_Role[3].m_EquipShoes.m_caption[4] = 0;
      return result;
    default:
      return result;
  }
  m_pfather = this->me_Role[3].m_EquipShoes.m_pfather;
  if ( m_pfather )
// [VFTABLE] return ((BOOL ( *)(UIWnd *, int, _DWORD, _DWORD))m_pfather->__vftable->OnMessage)(m_pfather, 1000, 0, 0);
  return result;
}

// 0x004A5930
int MainEquipUI::RenderThrottled()
{
  int result; // eax
  int i; // edi
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0x4]

  result = (int)this->me_Role[3].m_EquipShoes.m_childs.m_pData;
  switch ( result )
  {
    case 0:
      ((CCBControlWindow *)this)->Render(v4);
      result = this->me_Role[1].m_RoleAttCng[9].m_childs.m_needscriptdel;
      if ( *((_BYTE *)&this->me_Role[1].m_RoleAttCng[9].m_childs.capacity + result) )
      {
        for ( i = 0; i < 16; ++i )
        {
// [IDA_MISID]           if ( ((Concurrency *)&this->stp_Exit.m_caption[9344 * this->me_Role[1].m_RoleAttCng[9].m_childs.m_needscriptdel + 28 + 584 * i])->details::VirtualProcessor::IsThrottled() )
            ((ScreenEffect *)&this->stp_Exit.m_caption[9344
                                                                        * this->me_Role[1].m_RoleAttCng[9].m_childs.m_needscriptdel
                                                                        + 28
                                                                        + 584 * i])->Apply();
// [IDA_MISID]           LOBYTE(result) = ((Concurrency *)&this->m_btnPar2[1][16 * this->me_Role[1].m_RoleAttCng[9].m_childs.m_needscriptdel + 4 + i].view_radiusY)->details::VirtualProcessor::IsThrottled();
          if ( (_BYTE)result )
            ((ScreenEffect *)&this->m_btnPar2[1][16
                                                                  * this->me_Role[1].m_RoleAttCng[9].m_childs.m_needscriptdel
                                                                  + 4
                                                                  + i].view_radiusY)->Apply();
        }
      }
      break;
    case 1:
      result = (*(int ( **)(LONG))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.top + 4))(this->me_Role[3].m_EquipShoes.m_rect.top);
      break;
    case 2:
      result = (*(int ( **)(LONG))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.left + 4))(this->me_Role[3].m_EquipShoes.m_rect.left);
      break;
    case 3:
      result = (*(int ( **)(void *))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_id + 4))(this->me_Role[3].m_EquipShoes.m_id);
      break;
    case 4:
      result = (*(int ( **)(unsigned int))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_wndcolor.Color + 4))(this->me_Role[3].m_EquipShoes.m_wndcolor.Color);
      break;
    case 5:
      result = (*(int ( **)(LONG))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.right + 4))(this->me_Role[3].m_EquipShoes.m_rect.right);
      break;
    case 6:
      result = (*(int ( **)(LONG))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.bottom + 4))(this->me_Role[3].m_EquipShoes.m_rect.bottom);
      break;
    case 7:
// [VFTABLE] result = ((int ( *)(UIWnd *))this->me_Role[3].m_EquipShoes.m_pfather->__vftable->Render)(this->me_Role[3].m_EquipShoes.m_pfather);
      break;
    default:
      return result;
  }
  return result;
}

// 0x004A5A80
int MainEquipUI::LayoutHandleNav()
{
  int result; // eax
  char *v3; // eax

  if ( (byte_189598C & 1) == 0 )
  {
    byte_189598C |= 1u;
    atexit((void ( *)())sub_4A13E0);
  }
  result = g_nUILayoutFlags;
  if ( g_nUILayoutFlags <= 0 )
  {
    result = this->me_Role[3].m_EquipShoes.m_rect.right;
    if ( *(_BYTE *)(result + 185228) )
    {
      if ( g_Input.KeyInfo[11].PressTime == 1 )
      {
        v3 = this->me_Role[3].m_EquipShoes.m_childs.m_pData + 1;
        this->me_Role[3].m_EquipShoes.m_childs.m_pData = v3;
        if ( v3 == (char *)5 && !g_bRoleFlag1 )
          this->me_Role[3].m_EquipShoes.m_childs.m_pData = (char *)6;
        if ( this->me_Role[3].m_EquipShoes.m_childs.m_pData == (char *)6 && !g_bRoleFlag2 )
          this->me_Role[3].m_EquipShoes.m_childs.m_pData = (char *)7;
        if ( (int)this->me_Role[3].m_EquipShoes.m_childs.m_pData >= 8 )
          this->me_Role[3].m_EquipShoes.m_childs.m_pData = 0;
        return this->HandleMessage();
      }
    }
  }
  return result;
}

// 0x004A5B30
int MainEquipUI::UpdateCaptions()
{
  int i; // eax
  int v3; // eax
  char v4; // cl
  float *v5; // eax
  int v6; // eax
  __int64 v7; // rax
  int v8; // ebx
  gbTexture **p_m_disablepic; // ecx
  gbTexture **v10; // ecx
  gbTexture **v11; // ecx
  gbTexture **v12; // ecx
  int result; // eax
  UIWnd *m_pfather; // esi
  CUtil *Mode; // eax
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v18; // esi
  int v19; // [esp-0x8] [ebp-0x28]
  double v20; // [esp-0x4] [ebp-0x24]
  int v21; // [esp+0x4] [ebp-0x1C]
  int v22; // [esp+0x1C] [ebp-0x4]
  int a2; // [esp+0x28] [ebp+0x8]
  int a3; // [esp+0x2C] [ebp+0xC]

  if ( LOBYTE(this->m_PutOnType) )
  {
    this->i = 0;
    do
    {
      i = this->i;
      if ( this->m_Is[i] )
      {
        v3 = 947 * i;
        v4 = (char)(&this->me_Role[1].m_RoleAttEqual[8].m_fonttype)[v3];
// [VFTABLE] v5 = (float *)(&this->__vftable + v3);
        if ( !v4 )
        {
          sprintf(this->buf, "%d/%d", (int)v5[38976], Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 9]);
          ((UICaption *)(&this->me_Role[1].m_RoleAttEqual[9].m_rect.right + 947 * this->i))->SetEnable((int)this->buf, 0);
        }
        if ( !*((_BYTE *)&this->me_Role[1].m_EquipCloth.m_childs.m_nSize + 3788 * this->i) )
        {
          sprintf(
            this->buf,
            "%d/%d",
            (int)*((float *)&this->me_Role[1].m_EquipCloth.m_childs.capacity + 947 * this->i),
            Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 10]);
          ((UICaption *)&this->me_Role[1].m_EquipCloth.m_texarray.m_ptex[947 * this->i + 8])->SetEnable((int)this->buf, 0);
        }
        if ( !*(&this->me_Role[1].m_EquipWeapon.m_mouseoff + 3788 * this->i) )
        {
          sprintf(
            this->buf,
            "%d/%d",
            (int)*((float *)&this->me_Role[1].m_EquipWeapon.m_disablepicInfo + 947 * this->i),
            Buffer.m_partyActor.m_dwMatMsg[352 * this->i + 11]);
          ((UICaption *)&this->me_Role[1].m_EquipWeapon.m_caption[3788 * this->i + 76])->SetEnable((int)this->buf, 0);
        }
      }
      v6 = this->i + 1;
      this->i = v6;
    }
    while ( v6 < 5 );
    v7 = (__int64)g_fGameTimer;
    v8 = (int)v7 / 3600;
    v22 = (int)v7 / 60 % 60;
    v19 = (int)v7 % 60;
    if ( (int)v7 / 3600 < 100 )
      sprintf(this->buf, "%02d:%02d:%02d", v8, v22, v19);
    else
      sprintf(this->buf, "%03d:%02d:%02d", v8, v22, v19);
    ((UICaption *)&this->stp_System.m_caption[68])->SetEnable((int)this->buf, 0);
    sprintf(this->buf, &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
    ((UICaption *)&this->stp_Exit.m_hasDBclk)->SetEnable((int)this->buf, 0);
  }

  switch ( (unsigned int)this->me_Role[3].m_EquipShoes.m_childs.m_pData )
  {
    case 0u:
      ((UIListBox *)this)->Update(a2, a3);
      p_m_disablepic = &this->me_Role[3].m_RoleAttEqual[4].m_disablepic;
      if ( HIBYTE(Buffer.m_partyActor.m_nHandleEvent) )
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*p_m_disablepic)->0)(p_m_disablepic, 1);
      else
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*p_m_disablepic)->0)(p_m_disablepic, 0);
      v10 = &this->me_Role[3].m_RoleAttEqual[7].m_disablepic;
      if ( LOBYTE(Buffer.m_partyActor.m_vecPos.x) )
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*v10)->0)(v10, 1);
      else
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v10)->0)(v10, 0);
      v11 = &this->me_Role[3].m_RoleAttEqual[6].m_disablepic;
      if ( BYTE1(Buffer.m_partyActor.m_vecPos.x) )
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*v11)->0)(v11, 1);
      else
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v11)->0)(v11, 0);
      v12 = &this->me_Role[3].m_RoleAttEqual[5].m_disablepic;
      if ( BYTE2(Buffer.m_partyActor.m_vecPos.x) )
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*v12)->0)(v12, 1);
      else
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v12)->0)(v12, 0);
      result = 1;
      break;
    case 1u:
      (*(void ( **)(LONG, int, int))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.top + 8))(
        this->me_Role[3].m_EquipShoes.m_rect.top,
        a2,
        a3);
      result = 1;
      break;
    case 2u:
      (*(void ( **)(LONG, int, int))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.left + 8))(
        this->me_Role[3].m_EquipShoes.m_rect.left,
        a2,
        a3);
      result = 1;
      break;
    case 3u:
      (*(void ( **)(void *, int, int))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_id + 8))(
        this->me_Role[3].m_EquipShoes.m_id,
        a2,
        a3);
      result = 1;
      break;
    case 4u:
      (*(void ( **)(unsigned int, int, int))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_wndcolor.Color + 8))(
        this->me_Role[3].m_EquipShoes.m_wndcolor.Color,
        a2,
        a3);
      result = 1;
      break;
    case 5u:
      (*(void ( **)(LONG, int, int))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.right + 8))(
        this->me_Role[3].m_EquipShoes.m_rect.right,
        a2,
        a3);
      result = 1;
      break;
    case 6u:
      (*(void ( **)(LONG, int, int))(*(_DWORD *)this->me_Role[3].m_EquipShoes.m_rect.bottom + 8))(
        this->me_Role[3].m_EquipShoes.m_rect.bottom,
        a2,
        a3);
      result = 1;
      break;
    case 7u:
// [VFTABLE] ((void ( *)(UIWnd *, int, int))this->me_Role[3].m_EquipShoes.m_pfather->__vftable->Update_2ff0)(
// [VFTABLE]   this->me_Role[3].m_EquipShoes.m_pfather,
// [VFTABLE]   a2,
// [VFTABLE]   a3);
      m_pfather = this->me_Role[3].m_EquipShoes.m_pfather;
      if ( !m_pfather[4211].m_rect.bottom )
        goto LABEL_43;
      LODWORD(v20) = m_pfather[4211].m_rect.left;
      ((UITitle_JDHY *)m_pfather)->SaveData(v20, v21);
      result = 1;
      break;
    case 8u:
      ((CGameData *)&g_gamefrm)->Load((CUtil *)0xD);
      result = 1;
      break;
    case 9u:
      Mode = (CUtil *)((CGameData *)&g_gamefrm)->GetMode();
      ((CGameData *)&g_gamefrm)->Load(Mode);
      result = 1;
      break;
    case 0xAu:
      if ( (g_dwGameFlags & 4) != 0 )
      {
        Instance = CScreenMode::GetInstance();
        AudioManager = (gbAudioManager *)((CScreenMode *)Instance)->GetAudioManager();
        v18 = AudioManager;
        if ( AudioManager )
        {
          ((gbAudioManager *)AudioManager)->DetachAll3D();
          ((gbAudioManager *)v18)->StopSoundStream(0);
          ((gbAudioManager *)v18)->StopSoundStream(2);
          ((gbAudioManager *)v18)->StopSoundStream(1);
        }
      }
      ((CGameData *)&g_gamefrm)->Load((CUtil *)4);
      LOBYTE(gfxMgr->pSceneGraph->pnodebuf[713]) = 0;
      g_nMiniGameParam = 0;
      g_nMiniGameState = 0;
      g_bSceneLoaded_0 = 1;
      goto LABEL_43;
    default:
LABEL_43:
      result = 1;
      break;
  }
  return result;
}
