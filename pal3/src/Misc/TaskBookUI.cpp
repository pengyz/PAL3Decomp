#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/TaskBookUI.h"

// Forward declarations for unnamed functions
void * GetSaveDataManager(void); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
void * sub_446010(void *a2); // from annotations
CHAR * sub_458F70(LPCSTR lpString, int a2, LPSTR lpString1); // from annotations

BOOL ReadRegistryString(const char *szSubKey, const char *szValueName, char *szOutBuf); // from annotations

// Unnamed globals (extern)
extern CHAR asc_5B74B4[2];
extern char asc_5B74B8[];
extern char byte_A00701;
extern char byte_A00702;
extern char byte_A00703;
extern CHAR byte_DCEB3C[256];
extern int dword_DC633C;
extern int dword_DC643C;
extern int dword_DD4E3C;
extern int dword_DD4F3C;
extern int dword_DD933C;
extern int dword_DDA93C;
extern int dword_DDAA3C;
extern void * off_5AE380;
extern void * off_5AE388;
extern void * off_5AE38C;
extern void * off_5AE3A8;
extern void *off_5B0950;

// 0x00454830
void TaskBookUI::_TaskBookUI()
{
  sub_4422E0(this->m_OutFrameR.m_text);
  UIScene::GetSys();
  sub_4422E0(&this->m_btnPar2[14][0].m_helix_rx);
  sub_4422E0(&this->m_btnPar2[14][0]._texName[48]);
  UIScene::GetSys();
  UIScene::GetSys();
  ((UIScene *)&this->m_btnPar2[14][1]._element.m_benable)->ctor();
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] = 92;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[20] = 610;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] = 0;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = 0;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[32] = 0;
  ((ARC_PlayerAtt *)&this->m_btnPar2[14][2]._texName[40])->Refresh();
  ((ARC_PlayerAtt *)&this->m_btnPar2[14][4]._texName[240])->Refresh();
  this->m_btnPar2[15][0].view_radiusX = 0;
  this->rc.top = 0;
  this->rc.left = 0;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[36] = 0;
  this->rc.right = 800;
  this->rc.bottom = 600;
  memset(&this->stp_BarL.m_pbk, 0, 0x24u);
}

// 0x00454BA0
void TaskBookUI::_TaskBookUI_4ba0()
{
  ((UIRoleDialog *)&this->m_btnPar2[14][4]._texName[240])->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_btnPar2[14][2]._texName[40])->_UIRoleDialog();
  ((CCBResultWindow *)&this->m_btnPar2[14][1]._element.m_benable)->_CCBResultWindow();
  ((UICaption *)&this->m_btnPar2[14][1].m_sec)->Destroy2();
  ((UICaption *)&this->m_btnPar2[14][0]._texName[200])->Destroy2();
  ((UIFrameWnd *)&this->m_btnPar2[14][0]._texName[48])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_btnPar2[14][0].m_helix_rx)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_OutFrameL.m_texty)->Destroy2();
  ((UIFrameWnd *)this->m_OutFrameR.m_text)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00454CA0
void * TaskBookUI::CreateEntry(int nVal, int nVal2, int nVal3, int nVal4)
{
  tagRECT *p_rc; // ebx
  int v7; // edx
  float m_helix_rx; // edx
  int v9; // edx
  int v10; // eax
  int m_texty; // edx
  int refreshed; // eax
  int v13; // edx
  int v14; // eax
  unsigned int m_sec; // edx
  int m_benable; // edx
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  int sizeY; // ebx
  double v21; // st7
  __int64 v22; // rax
  int v23; // ebp
  __int64 v24; // rax
  int v25; // ecx
  int v26; // ecx
  int v27; // eax
  double v28; // st7
  int v29; // eax
  int sizeX; // eax
  double v31; // st7
  int v32; // eax
  int W; // ecx
  int v34; // ecx
  gbColorQuad *v35; // eax
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
  int v48; // [esp+C4h] [ebp-0x20] BYREF
  int v49; // [esp+C8h] [ebp-0x1C]
  int v50; // [esp+CCh] [ebp-0x18]
  int v51; // [esp+D0h] [ebp-0x14]
  _DWORD v52[4]; // [esp+D4h] [ebp-0x10] BYREF

  p_rc = &this->rc;
  ((UIListBox *)this)->SetSelTexture(0, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom, 0);
  v7 = *(_DWORD *)this->m_OutFrameR.m_text;
  this->m_btnPar2[15][0].view_radiusX = nVal;
  (*(void ( **)(char *, _DWORD, tagRECT *, TaskBookUI *))(v7 + 16))(this->m_OutFrameR.m_text, 0, p_rc, this);
  ((UIStatic *)this->m_OutFrameR.m_text)->CreateFromTemplate();
  m_helix_rx = this->m_btnPar2[14][0].m_helix_rx;
  v41 = 46;
  v40 = 108;
  v42 = 692;
  v43 = 66;
  (*(void ( **)(float *, _DWORD, int *, TaskBookUI *))(LODWORD(m_helix_rx) + 16))(
    &this->m_btnPar2[14][0].m_helix_rx,
    0,
    &v40,
    this);
  ((UIStatic *)&this->m_btnPar2[14][0].m_helix_rx)->CreateFromTemplate();
  v9 = *(_DWORD *)&this->m_btnPar2[14][0]._texName[48];
  v41 = 526;
  v40 = 109;
  v42 = 693;
  v43 = 563;
  (*(void ( **)(char *, _DWORD, int *, TaskBookUI *))(v9 + 16))(
    &this->m_btnPar2[14][0]._texName[48],
    0,
    &v40,
    this);
  ((UIStatic *)&this->m_btnPar2[14][0]._texName[48])->CreateFromTemplate();
  LOBYTE(v10) = g_bEffectEnabled;
  m_texty = this->m_OutFrameL.m_texty;
  v52[1] = 537;
  v52[0] = 745;
  v52[2] = 801;
  v52[3] = 599;
  (*(void ( **)(int *, int, _DWORD *, TaskBookUI *, char *, _DWORD, int))(m_texty + 28))(
    &this->m_OutFrameL.m_texty,
    209,
    v52,
    this,
    off_5B0950[0],
    0,
    v10);
  refreshed = this->RefreshTaskList();
  LOBYTE(refreshed) = g_bEffectEnabled;
  v13 = *(_DWORD *)&this->m_btnPar2[14][0]._texName[200];
  v45 = 62;
  v44 = 702;
  v46 = 727;
  v47 = 90;
  v14 = (*(int ( **)(char *, char *, int *, TaskBookUI *, char *, _DWORD, int))(v13 + 28))(
          &this->m_btnPar2[14][0]._texName[200],
          &byte_A00702,
          &v44,
          this,
          "UI\\GameMainUI\\System\\pgup",
          0,
          refreshed);
  LOBYTE(v14) = g_bEffectEnabled;
  m_sec = this->m_btnPar2[14][1].m_sec;
  v45 = 527;
  v44 = 702;
  v46 = 727;
  v47 = 555;
  (*(void ( **)(unsigned int *, char *, int *, TaskBookUI *, char *, _DWORD, int))(m_sec + 28))(
    &this->m_btnPar2[14][1].m_sec,
    &byte_A00701,
    &v44,
    this,
    "UI\\GameMainUI\\System\\pgdw",
    0,
    v14);
  m_benable = this->m_btnPar2[14][1]._element.m_benable;
  this->m_btnPar2[14][1]._element.m_childs.m_needscriptdel = 90;
  this->m_btnPar2[14][1]._element.m_bcreateok = 722;
  this->m_btnPar2[14][1]._element.m_childs.m_nSize = 708;
  this->m_btnPar2[14][1]._element.m_bvisible = 527;
  LOBYTE(v17) = g_bEffectEnabled;
  (*(void ( **)(int *, ARC_PlayerAtt *, int *, TaskBookUI *, char *, int))(m_benable + 28))(
    &this->m_btnPar2[14][1]._element.m_benable,
    &g_PlayerAttBuffer2,
    &this->m_btnPar2[14][1]._element.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    v17);
  ((UIScene *)&this->m_btnPar2[14][1]._element.m_benable)->SetTexture("UI\\GameMainUI\\System\\hdt.tga", 0);
  ((UIBigMap *)&this->m_btnPar2[14][1]._element.m_benable)->Update(26, 28);
  fill((PlayerItem *)1, v38, v39);
  this->m_btnPar2[14][2]._xg = 14.0;
  this->m_btnPar2[14][2]._yg = -14.0;
  v18 = *(_DWORD *)this->m_btnPar2[14][2]._texName;
  LODWORD(this->m_btnPar2[14][2]._y) = 20;
  if ( !v18 )
  {
    v29 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[4];
    if ( v29 )
    {
      if ( v29 != 1 )
        goto LABEL_13;
      sizeY = this->m_btnPar2[14][1]._sizeY;
      nVal = this->m_btnPar2[14][2]._H - sizeY - 20;
      v23 = (__int64)((double)nVal + this->m_btnPar2[14][2]._xg);
      sizeX = this->m_btnPar2[14][1]._sizeX;
      v31 = (double)*(int *)&this->m_btnPar2[14][2].m_bGetBottom - this->m_btnPar2[14][2]._fade;
      this->m_btnPar2[14][2].view_radiusY = v23;
      nVal = sizeX / 2;
      v28 = v31 - (double)(sizeX / 2) - this->m_btnPar2[14][2]._yi;
    }
    else
    {
      sizeY = this->m_btnPar2[14][1]._sizeY;
      nVal = this->m_btnPar2[14][2]._H - sizeY - 20;
      v23 = (__int64)((double)nVal + this->m_btnPar2[14][2]._xg);
      v32 = this->m_btnPar2[14][1]._sizeX;
      W = this->m_btnPar2[14][2]._W;
      this->m_btnPar2[14][2].view_radiusY = v23;
      nVal = W - v32 / 2;
      v28 = (double)nVal + this->m_btnPar2[14][2]._xi + this->m_btnPar2[14][2]._fade;
    }
LABEL_11:
    v34 = this->m_btnPar2[14][1]._sizeX;
    this->m_btnPar2[14][2].view_radiusX = (__int64)v28;
    this->m_btnPar2[14][2].par_radiusX = v34 + (__int64)v28;
    goto LABEL_12;
  }
  if ( v18 != 1 )
    goto LABEL_13;
  v19 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[4];
  if ( !v19 )
  {
    sizeY = this->m_btnPar2[14][1]._sizeY;
    nVal = this->m_btnPar2[14][2]._H - sizeY / 2;
    v26 = this->m_btnPar2[14][2]._W;
    v23 = (__int64)((double)nVal + this->m_btnPar2[14][2]._xg + this->m_btnPar2[14][2]._fade);
    v27 = this->m_btnPar2[14][1]._sizeX;
    this->m_btnPar2[14][2].view_radiusY = v23;
    nVal = v26 - v27 - 20;
    v28 = (double)nVal + this->m_btnPar2[14][2]._xi;
    goto LABEL_11;
  }
  if ( v19 == 1 )
  {
    sizeY = this->m_btnPar2[14][1]._sizeY;
    v21 = (double)SLODWORD(this->m_btnPar2[14][2].m_HelixAngle) - this->m_btnPar2[14][2]._fade;
    nVal = sizeY / 2;
    v22 = (__int64)(v21 - (double)(sizeY / 2) - this->m_btnPar2[14][2]._yg);
    HIDWORD(v22) = *(_DWORD *)&this->m_btnPar2[14][2].m_bGetBottom;
    v23 = (__int64)(v21 - (double)(sizeY / 2) - this->m_btnPar2[14][2]._yg);
    this->m_btnPar2[14][2].view_radiusY = v22;
    nVal = HIDWORD(v22) + 20;
    v24 = (__int64)((double)(HIDWORD(v22) + 20) - this->m_btnPar2[14][2]._fade - this->m_btnPar2[14][2]._yi);
    v25 = this->m_btnPar2[14][1]._sizeX;
    this->m_btnPar2[14][2].view_radiusX = v24;
    this->m_btnPar2[14][2].par_radiusX = v24 + v25;
LABEL_12:
    this->m_btnPar2[14][2].par_radiusY = sizeY + v23;
  }
LABEL_13:
  // [AUTO-COMMENTED] v35 = ((gbColorQuad *)&nVal)->gbColorQuad(0, 0, 0, 0);
  ((UIScene *)&this->m_btnPar2[14][1]._element.m_benable)->SetParam(v35->Color);
  nVal = 32 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] - 28;
  fVal = (float)nVal;
  ((UIScene *)&this->m_btnPar2[14][1]._element.m_benable)->UpdateLayout(fVal);
  v49 = 200;
  v48 = 250;
  v50 = 450;
  v51 = 300;
  ((ARC_PlayerAtt *)&this->m_btnPar2[14][2]._texName[40])->Create((int)&g_PlayerAttBuffer2.Remark[5], (int)&v48);
  ((UIItem *)&this->m_btnPar2[14][2]._texName[40])->SetData(219);
  v49 = 200;
  v48 = 300;
  v50 = 500;
  v51 = 300;
  ((ARC_PlayerAtt *)&this->m_btnPar2[14][4]._texName[240])->Create((int)&g_PlayerAttBuffer2.Remark[6], (int)&v48);
  return ((UIItem *)&this->m_btnPar2[14][4]._texName[240])->SetData(219);
}

// 0x004551A0
int TaskBookUI::RefreshTaskList()
{
  int v2; // eax
  int v3; // ecx
  int result; // eax
  gbTexture **v5; // esi
  _DWORD *v6; // edi
  int v7; // [esp+ACh] [ebp-0x1C]
  int v8; // [esp+B0h] [ebp-0x18]
  int v9; // [esp+B4h] [ebp-0x14]
  _DWORD v10[4]; // [esp+B8h] [ebp-0x10] BYREF

  v10[1] = 62;
  v2 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[20];
  v3 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[16];
  result = v2 + 80;
  v10[0] = 80;
  v10[2] = result;
  v10[3] = v3 + 62;
  v7 = 0;
  v5 = &this->stp_State.m_texarray.m_ptex[2];
  do
  {
    LOBYTE(result) = g_bEffectEnabled;
    ((void ( *)(gbTexture **, char *, _DWORD *, TaskBookUI *, char *, _DWORD, int))(*(v5 - 86))->Height)(
      v5 - 86,
      &byte_A00703,
      v10,
      this,
      "UI\\GameMainUI\\System\\Note",
      0,
      result);
    ((PalScript *)(v5 - 86))->OpenScript("UI\\GameMainUI\\System\\Note2.tga", g_bEffectEnabled);
    *((_BYTE *)v5 - 4) = 0;
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*(v5 - 86))->0)(v5 - 86, 0);
    // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, char *, _DWORD *, TaskBookUI *))&(*v5)->0 + 4))(v5, &byte_A00703, v10, this);
    ((UIScene *)v5)->SetShow(0);
    v9 = v7 + 1;
    sprintf((char *const)&this->m_OutFrameT, &dir[20], v7 + 1);
    ((UICaption *)v5)->SetEnable((int)&this->m_OutFrameT, 1);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v5)->0)(v5, 0);
    // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, char *, _DWORD *, TaskBookUI *))&v5[38]->0 + 4))(
      // [VTBL_DISPATCH]   v5 + 38,
      // [VTBL_DISPATCH]   &byte_A00703,
      // [VTBL_DISPATCH]   v10,
      // [VTBL_DISPATCH]   this);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v5[38]->0)(v5 + 38, 0);
    v6 = v5 + 76;
    v8 = 5;
    do
    {
      (*(void ( **)(_DWORD *, char *, _DWORD *, TaskBookUI *))(v6[190] + 16))(
        v6 + 190,
        &byte_A00703,
        v10,
        this);
      (*(void ( **)(_DWORD *, _DWORD))v6[190])(v6 + 190, 0);
      (*(void ( **)(_DWORD *, char *, _DWORD *, TaskBookUI *))(*v6 + 16))(v6, &byte_A00703, v10, this);
      (*(void ( **)(_DWORD *, _DWORD))*v6)(v6, 0);
      (*(void ( **)(_DWORD *, char *, _DWORD *, TaskBookUI *))(v6[458] + 16))(
        v6 + 458,
        &byte_A00703,
        v10,
        this);
      sub_446010(v6 + 458);
      (*(void ( **)(_DWORD *, _DWORD))v6[458])(v6 + 458, 0);
      v6 += 38;
      --v8;
    }
    while ( v8 );
    // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, char *, _DWORD *, TaskBookUI *))&v5[458]->0 + 4))(
      // [VTBL_DISPATCH]   v5 + 458,
      // [VTBL_DISPATCH]   &byte_A00703,
      // [VTBL_DISPATCH]   v10,
      // [VTBL_DISPATCH]   this);
    sub_446010(v5 + 458);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v5[458]->0)(v5 + 458, 0);
    // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, char *, _DWORD *, TaskBookUI *))&v5[496]->0 + 4))(
      // [VTBL_DISPATCH]   v5 + 496,
      // [VTBL_DISPATCH]   &byte_A00703,
      // [VTBL_DISPATCH]   v10,
      // [VTBL_DISPATCH]   this);
    sub_446010(v5 + 496);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v5[496]->0)(v5 + 496, 0);
    // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, char *, _DWORD *, TaskBookUI *))&v5[724]->0 + 4))(
      // [VTBL_DISPATCH]   v5 + 724,
      // [VTBL_DISPATCH]   &byte_A00703,
      // [VTBL_DISPATCH]   v10,
      // [VTBL_DISPATCH]   this);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v5[724]->0)(v5 + 724, 0);
    // [VTBL_DISPATCH] (*((void ( **)(gbTexture **, char *, _DWORD *, TaskBookUI *))&v5[762]->0 + 4))(
      // [VTBL_DISPATCH]   v5 + 762,
      // [VTBL_DISPATCH]   &byte_A00703,
      // [VTBL_DISPATCH]   v10,
      // [VTBL_DISPATCH]   this);
    sub_446010(v5 + 762);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v5[762]->0)(v5 + 762, 0);
    v5 += 890;
    this->stp_BarL.m_text[v7 + 16] = 0;
    result = ++v7;
  }
  while ( v9 < 36 );
  return result;
}

// 0x004554D0
int * TaskBookUI::AdvancePage()
{
  int v2; // eax
  int v3; // esi
  int v4; // ebx
  UIStatic *v5; // ebp
  int v7; // [esp+0x18] [ebp-0x8]

  v2 = 64;
  v3 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] + 64;
  v7 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[20] + 80;
  v4 = 0;
  v5 = (UIStatic *)&this->stp_State.m_caption[64];
  do
  {
    ((ChoseCompose *)this)->LayoutItems(v4, 80, v2, v7, v3);
    sub_445E50((int)&v5[-4].m_pbk);
    ((UIStatic *)v5)->CreateFromTemplate();
    v2 = v3;
    v3 += *(_DWORD *)&this->m_btnPar2[14][2]._texName[16];
    ++v4;
    v5 = (UIStatic *)((char *)v5 + 3560);
  }
  while ( v4 < 36 );
  sub_445E50((int)&this->stp_BarM.m_fontcolor);
  return this->RefreshElements();
}

// 0x00455790
int * TaskBookUI::RefreshElements()
{
  int v1; // ebp
  gbTexture **v2; // esi
  void (***v3)(_DWORD, _DWORD); // edi
  int v4; // ebx
  int *result; // eax
  int *v6; // ecx
  gbTexture **v7; // edi
  int v8; // ebp
  void (***v9)(_DWORD, _DWORD); // esi
  void (***v10)(_DWORD, _DWORD); // ecx
  void ( ***v11)(_DWORD, int); // ecx
  int v12; // ebp
  gbTexture **v13; // esi
  void ( **v14)(int); // eax
  int v15; // ebp
  gbTexture **v16; // esi
  gbTexture *v17; // edx
  gbTexture **v18; // ecx
  gbTexture *v19; // eax
  int v20; // [esp+0x48] [ebp-0x18]
  int *v22; // [esp+0x5C] [ebp-0x4]

  v1 = 0;
  v2 = &this->stp_State.m_texarray.m_ptex[2];
  do
  {
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*(v2 - 86))->0)(v2 - 86, 0);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v2)->0)(v2, 0);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v2[38]->0)(v2 + 38, 0);
    v3 = (void ( ***)(_DWORD, _DWORD))(v2 + 76);
    v4 = 5;
    do
    {
      (*v3[190])(v3 + 190, 0);
      (**v3)(v3, 0);
      (*v3[458])(v3 + 458, 0);
      v3 += 38;
      --v4;
    }
    while ( v4 );
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v2[458]->0)(v2 + 458, 0);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v2[496]->0)(v2 + 496, 0);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v2[724]->0)(v2 + 724, 0);
    // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))v2[762]->0)(v2 + 762, 0);
    result = (int *)this;
    ++v1;
    v2 += 890;
    this->stp_BarL.m_text[v1 + 15] = 0;
  }
  while ( v1 < 36 );
  v6 = *(int **)&this->m_btnPar2[14][2]._texName[24];
  v22 = v6;
  if ( !__OFSUB__(v6, (char *)v6 + 5) )
  {
    v7 = &this->stp_State.m_texarray.m_ptex[890 * (_DWORD)v6 + 2];
    do
    {
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*(v7 - 86))->0)(v7 - 86, 1);
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*v7)->0)(v7, 1);
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))v7[38]->0)(v7 + 38, 1);
      v8 = 0;
      v9 = (void ( ***)(_DWORD, _DWORD))(v7 + 76);
      do
      {
        v10 = v9 + 190;
        if ( *((_BYTE *)v7 + v8 + 1824) )
        {
          (**v10)(v10, 0);
          (**v9)(v9, 0);
          (*v9[458])(v9 + 458, 1);
        }
        else
        {
          (**v10)(v10, 0);
          (**v9)(v9, 0);
          (*v9[458])(v9 + 458, 0);
        }
        ++v8;
        v9 += 38;
      }
      while ( v8 < 5 );
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))v7[458]->0)(v7 + 458, 1);
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))v7[496]->0)(v7 + 496, 1);
      v11 = (void ( ***)(_DWORD, int))(v7 + 724);
      if ( *(int **)&this->m_btnPar2[14][2]._texName[28] == v22 )
      {
        (**v11)(v11, 1);
        v12 = 0;
        v13 = v7 + 76;
        do
        {
          v14 = (void ( **)(int))v13[190];
          if ( *((_BYTE *)v7 + v12 + 1824) )
            (*v14)(1);
          else
            (*v14)(0);
          // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v13)->0)(v13, 0);
          ++v12;
          v13 += 38;
        }
        while ( v12 < 5 );
      }
      else
      {
        (**v11)(v11, 0);
        v15 = 0;
        v16 = v7 + 76;
        do
        {
          v17 = v16[190];
          v18 = v16 + 190;
          if ( *((_BYTE *)v7 + v15 + 1824) )
          {
            ((void ( *)(gbTexture **, _DWORD, int))*((_DWORD *)v17))(v18, 0, v20);
            v19 = *v16;
            v20 = 1;
          }
          else
          {
            ((void ( *)(gbTexture **, _DWORD, int))*((_DWORD *)v17))(v18, 0, v20);
            v19 = *v16;
            v20 = 0;
          }
          ((void ( *)(gbTexture **))*((_DWORD *)v19))(v16);
          ++v15;
          v16 += 38;
        }
        while ( v15 < 5 );
      }
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))v7[762]->0)(v7 + 762, 1);
      v7 += 890;
      *((_BYTE *)v22 + (_DWORD)this + 856) = 1;
      result = (int *)((char *)v22 + 1);
      v22 = result;
    }
    while ( (int)result < *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] + 5 );
  }
  return result;
}

// 0x00455A20
char TaskBookUI::ScrollUp(char pData)
{
  int v3; // eax
  CScreenMode *v4; // eax
  int v6; // ebx
  int *v7; // esi
  int v8; // eax
  CScreenMode *Instance; // eax
  const void *v10; // [esp-0x4] [ebp-0x14]
  const void *v11; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]
  int pDataa; // [esp+0x14] [ebp+0x4]

  ++*(_DWORD *)&this->m_btnPar2[14][2]._texName[24];
  if ( pData )
  {
    v3 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] + 1;
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] = v3;
    if ( v3 > 32 )
      *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] = 32;
    pDataa = *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] * *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] - 28;
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[8] = pDataa;
    fProgress = (float)pDataa;
    ((CScreenMode *)&this->m_btnPar2[14][1]._element.m_benable)->SetProgress(fProgress);
  }
  if ( *(int *)&this->m_btnPar2[14][2]._texName[24] <= 31 )
  {

    v6 = 0;
    v7 = (int *)(&this->stp_BarL + 1);
    do
    {
      v8 = *v7 - *(_DWORD *)&this->m_btnPar2[14][2]._texName[16];
      *v7 = v8;
      v7[2] = v8 + *(_DWORD *)&this->m_btnPar2[14][2]._texName[16];
      ((ChoseCompose *)this)->LayoutItems(v6++, *(v7 - 1), *v7, v7[1], v7[2]);
      v7 += 890;
    }
    while ( v6 < 36 );
    v11 = off_5AE3A8;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v11, 1);
    return 1;
  }
  else
  {
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] = 31;
    v10 = off_5AE38C;
    v4 = CScreenMode::GetInstance();
    ((CScreenMode *)v4)->AudioSetPosition(v10, 1);
    return 0;
  }
}

// 0x00455B30
char TaskBookUI::ScrollDown(char pData)
{
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  CScreenMode *v6; // eax
  int *v8; // edi
  int v9; // eax
  CScreenMode *Instance; // eax
  const void *v11; // [esp-0x4] [ebp-0x14]
  const void *v12; // [esp-0x4] [ebp-0x14]
  float fProgress; // [esp+0x0] [ebp-0x10]

  v3 = 0;
  --*(_DWORD *)&this->m_btnPar2[14][2]._texName[24];
  if ( pData )
  {
    v4 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] - 1;
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] = v4;
    if ( v4 <= 0 )
      *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] = 0;
    v5 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] * *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] - 28;
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[8] = v5;
    if ( v5 < 0 )
      *(_DWORD *)&this->m_btnPar2[14][2]._texName[8] = 0;
    fProgress = (float)*(int *)&this->m_btnPar2[14][2]._texName[8];
    ((CScreenMode *)&this->m_btnPar2[14][1]._element.m_benable)->SetProgress(fProgress);
  }
  if ( *(int *)&this->m_btnPar2[14][2]._texName[24] >= 0 )
  {

    v8 = (int *)(&this->stp_BarL + 1);
    do
    {
      v9 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] + *v8;
      *v8 = v9;
      v8[2] = v9 + *(_DWORD *)&this->m_btnPar2[14][2]._texName[16];
      ((ChoseCompose *)this)->LayoutItems(v3++, *(v8 - 1), *v8, v8[1], v8[2]);
      v8 += 890;
    }
    while ( v3 < 36 );
    v12 = off_5AE3A8;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v12, 1);
    return 1;
  }
  else
  {
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] = 0;
    v11 = off_5AE38C;
    v6 = CScreenMode::GetInstance();
    ((CScreenMode *)v6)->AudioSetPosition(v11, 1);
    return 0;
  }
}

// 0x00455C40
void TaskBookUI::HandleInput()
{
  char *v2; // ebp
  const RECT *i; // edi
  int v4; // eax
  int v5; // ebx
  int j; // edi
  int v7; // eax
  MUIDialogMgr *p_refrence_counter; // edi
  int v9; // ebx
  int v10; // ebx
  int k; // edi
  int v12; // eax
  void *v13; // ecx
  Actor *SaveDataManager; // eax
  CScreenMode *Instance; // eax
  CScreenMode *v16; // eax
  const void *v17; // [esp-0x8] [ebp-0x70]
  const void *v18; // [esp-0x8] [ebp-0x70]
  POINT pt; // [esp+0x10] [ebp-0x58]

  if ( !this->m_btnPar2[14][4]._texName[213] && !BYTE1(this->m_btnPar2[14][6]._sizeX) )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    v2 = 0;
    for ( i = (const RECT *)&this->stp_BarL.m_nTextW; ; i = (const RECT *)((char *)i + 3560) )
    {
      if ( v2[(_DWORD)this + 856] && PtInRect(i, pt) && g_Input.KeyInfo[0].PressTime == 1 )
      {
        v4 = g_Input.KeyInfo[0].Data & 0xF;
        if ( v4 == 1 )
        {
          if ( this->stp_BarL.m_text[*(_DWORD *)&this->m_btnPar2[14][2]._texName[28] + 16] )
          {
            v5 = 0;
            for ( j = 0; j < 760; j += 152 )
            {
              v7 = 3560 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28];
              if ( this->stp_TaskBook.m_caption[v7 + 16 + v5] )
              {
                (**(void ( ***)(char *, int))((char *)&this->stp_Magic.m_bfocus + j + v7))(
                  (char *)&this->stp_Magic.m_bfocus + j + v7,
                  1);
                (**(void ( ***)(char *, _DWORD))((char *)&this->stp_Prop.m_texarray.m_ptex[890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] + 10]
                                                         + j))(
                  (char *)&this->stp_Prop.m_texarray.m_ptex[890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] + 10]
                + j,
                  0);
              }
              ++v5;
            }
          }
          *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = v2;
          p_refrence_counter = (MUIDialogMgr *)&this->m_DlgEx.refrence_counter;
          v9 = 36;
          do
          {
            sub_445E50((int)&p_refrence_counter[-810]);
            (*(void ( **)(MUIDialogMgr *, _DWORD))p_refrence_counter->refrence_counter)(p_refrence_counter, 0);
            p_refrence_counter += 890;
            --v9;
          }
          while ( v9 );
          sub_445E50((int)(&this->stp_BarM.m_fontcolor + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]));
          (**((void ( ***)(int *, int))&this->m_DlgEx.refrence_counter
            + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]))(
            &this->m_DlgEx.refrence_counter + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28],
            1);
          v10 = 0;
          for ( k = 0; k < 760; k += 152 )
          {
            v12 = 3560 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28];
            if ( this->stp_TaskBook.m_caption[v12 + 16 + v10] )
            {
              (**(void ( ***)(char *, _DWORD))((char *)&this->stp_Magic.m_bfocus + k + v12))(
                (char *)&this->stp_Magic.m_bfocus + k + v12,
                0);
              (**(void ( ***)(char *, int))((char *)&this->stp_Prop.m_texarray.m_ptex[890
                                                                                              * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]
                                                                                              + 10]
                                                    + k))(
                (char *)&this->stp_Prop.m_texarray.m_ptex[890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] + 10]
              + k,
                1);
            }
            ++v10;
          }
          v13 = off_5AE380;
          goto LABEL_26;
        }
        if ( v4 == 2 )
          break;
      }
      if ( (int)++v2 >= 36 )
        return;
    }
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[32] = v2;
    SaveDataManager = (Actor *)GetSaveDataManager();
    if ( ((Actor *)SaveDataManager)->LoadSaveData(v2) )
    {
      sprintf((char *const)&this->m_OutFrameT, "\\n      %s", (const char *)dword_DD4E3C);
      ((UICaption *)&this->m_btnPar2[14][3].m_posy)->SetEnable((int)&this->m_OutFrameT, 0);
      ((UIRoleSelect *)&this->m_btnPar2[14][2]._texName[40])->SetByte(0);
      ((GRPinput *)&g_Input)->Reset();
      v17 = off_5AE388;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v17, 1);
      return;
    }
    sprintf((char *const)&this->m_OutFrameT, "\\n %s", (const char *)dword_DD4F3C);
    ((UICaption *)&this->m_btnPar2[14][5]._texName[112])->SetEnable((int)&this->m_OutFrameT, 0);
    ((UIRoleSelect *)&this->m_btnPar2[14][4]._texName[240])->SetByte(1);
    ((GRPinput *)&g_Input)->Reset();
    v13 = off_5AE388;
LABEL_26:
    v18 = v13;
    v16 = CScreenMode::GetInstance();
    ((CScreenMode *)v16)->AudioSetPosition(v18, 1);
  }
}

// 0x00455F20
int TaskBookUI::SaveData()
{
  char *v1; // ebp
  char *v2; // edi
  Actor *SaveDataManager; // eax
  char *v4; // esi
  int i; // ebp
  __int64 v6; // rax
  int v7; // esi
  int v8; // ebx
  int v9; // ebp
  char *v10; // esi
  int result; // eax
  int v12; // [esp-0x4] [ebp-0x170]
  int v13; // [esp+0x10] [ebp-0x15C]
  char *v14; // [esp+0x14] [ebp-0x158]
  float v15; // [esp+0x18] [ebp-0x154]
  _BYTE v16[5]; // [esp+0x1C] [ebp-0x150]
  char v17[67]; // [esp+0x21] [ebp-0x14B] BYREF
  int v18; // [esp+0x64] [ebp-0x108]
  char Buffer[257]; // [esp+0x68] [ebp-0x104] BYREF
  __int16 v20; // [esp+0x169] [ebp-0x3]
  char v21; // [esp+0x16B] [ebp-0x1]

  memset(Buffer, 0, sizeof(Buffer));
  v1 = 0;
  v20 = 0;
  v21 = 0;
  v13 = 0;
  v2 = &this->stp_TaskBook.m_caption[24];
  while ( 1 )
  {
    SaveDataManager = (Actor *)GetSaveDataManager();
    if ( ((Actor *)SaveDataManager)->LoadSaveData(v1) )
    {
      v6 = (__int64)v15;
      v7 = (int)v6 / 3600;
      v8 = (int)v6 / 60 % 60;
      v12 = (int)v6 % 60;
      if ( (int)v6 / 3600 < 100 )
        sprintf(Buffer, "%s %02d:%02d:%02d", dword_DC643C, v7, v8, v12);
      else
        sprintf(Buffer, "%s %03d:%02d:%02d", dword_DC643C, v7, v8, v12);
      ((UICaption *)v2)->SetEnable((int)Buffer, 0);
      sprintf(Buffer, "%s %d", (const char *)dword_DC633C, v18);
      ((UICaption *)(v2 + 152))->SetEnable((int)Buffer, 0);
      sprintf(Buffer, "%s %s", (const char *)dword_DD933C, v17);
      ((UICaption *)(v2 + 1216))->SetEnable((int)Buffer, 0);
      sprintf(Buffer, "Save\\PAL3_%04d.JPG", v1);
      ((UIFrameWnd *)(v2 + 1064))->SetTextureByID((int)Buffer);
      (**((void ( ***)(int, int))v2 + 266))((int)(v2 + 1064), 1);
      v9 = 0;
      v10 = v2 - 768;
      do
      {
        if ( v16[v9] )
        {
          v2[v9 - 8] = 1;
          (**(void ( ***)(char *, _DWORD))v10)(v10, 0);
          ((UIStatic *)v10)->CreateFromTemplate();
          (**((void ( ***)(int, int))v10 - 190))((int)(v10 - 760), 1);
          ((UIStatic *)(UIStatic *)v10 - 5)->CreateFromTemplate();
          ((UICaption *)(v10 + 1072))->SetEnable((int)g_szSceneUIText, 1);
        }
        else
        {
          (**(void ( ***)(char *, _DWORD))v10)(v10, 0);
          (**((void ( ***)(int, _DWORD))v10 - 190))((int)(v10 - 760), 0);
          v2[v9 - 8] = 0;
        }
        ++v9;
        v10 += 152;
      }
      while ( v9 < 5 );
    }
    else
    {
      ((UICaption *)v2)->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)(v2 + 152))->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)(v2 + 1216))->SetEnable((int)g_szSceneUIText, 0);
      (**((void ( ***)(int, _DWORD))v2 + 266))((int)(v2 + 1064), 0);
      v4 = v2 - 1528;
      v14 = v2 - 8;
      for ( i = 0; i < 20; i += 4 )
      {
        *v14 = 0;
        (**((void ( ***)(int, _DWORD))v4 + 190))((int)(v4 + 760), 0);
        ((UIStatic *)(UIStatic *)v4 + 5)->CreateFromTemplate();
        (**(void ( ***)(char *, _DWORD))v4)(v4, 0);
        ((UIStatic *)v4)->CreateFromTemplate();
        ((UICaption *)(v4 + 1832))->SetEnable((int)g_szSceneUIText, 1);
        v4 += 152;
        ++v14;
      }
    }
    v2 += 3560;
    result = ++v13;
    if ( v13 >= 36 )
      break;
    v1 = (char *)v13;
  }
  return result;
}

// 0x00456220
int TaskBookUI::_TaskBookUI_6220()
{
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] = 0;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[8] = 0;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] = 1;
  ((CScreenMode *)&this->m_btnPar2[14][1]._element.m_benable)->SetProgress(0.0);
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[32] = 0;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = 0;
  memset(&this->stp_BarL.m_pbk, 0, 0x24u);

  return this->ValidateEntries();
}

// 0x004562C0
void TaskBookUI::HandleNavigation()
{
  int v2; // eax
  MUIDialogMgr *p_refrence_counter; // edi
  int v4; // ebx
  int v5; // eax
  MUIDialogMgr *v6; // edi
  int v7; // ebx
  Actor *SaveDataManager; // eax
  CScreenMode *Instance; // eax
  char *v10; // [esp-0x8] [ebp-0x64]
  const void *v11; // [esp-0x8] [ebp-0x64]

  if ( !this->m_btnPar2[14][4]._texName[213] && !BYTE1(this->m_btnPar2[14][6]._sizeX) )
  {
    if ( g_Input.KeyInfo[5].PressTime == 1 )
    {
      v2 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] + 1;
      *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = v2;
      if ( v2 > 35 )
        *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = 35;
      p_refrence_counter = (MUIDialogMgr *)&this->m_DlgEx.refrence_counter;
      v4 = 36;
      do
      {
        sub_445E50((int)&p_refrence_counter[-810]);
        (*(void ( **)(MUIDialogMgr *, _DWORD))p_refrence_counter->refrence_counter)(p_refrence_counter, 0);
        p_refrence_counter += 890;
        --v4;
      }
      while ( v4 );
      if ( *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] >= *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] + 5 )
        this->ScrollUp(1);
LABEL_10:
      sub_445E50((int)(&this->stp_BarM.m_fontcolor + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]));
      (**((void ( ***)(int *, int))&this->m_DlgEx.refrence_counter
        + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]))(
        &this->m_DlgEx.refrence_counter + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28],
        1);
      return;
    }
    if ( g_Input.KeyInfo[4].PressTime == 1 )
    {
      v5 = *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] - 1;
      *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = v5;
      if ( v5 < 0 )
      {
        ((CScreenMode *)&this->m_btnPar2[14][1]._element.m_benable)->SetProgress(0.0);
        *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = 0;
      }
      v6 = (MUIDialogMgr *)&this->m_DlgEx.refrence_counter;
      v7 = 36;
      do
      {
        sub_445E50((int)&v6[-810]);
        (*(void ( **)(MUIDialogMgr *, _DWORD))v6->refrence_counter)(v6, 0);
        v6 += 890;
        --v7;
      }
      while ( v7 );
      if ( *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] < *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] )
        this->ScrollDown(1);
      goto LABEL_10;
    }
    if ( g_Input.KeyInfo[7].PressTime == 1 )
    {
      v10 = *(char **)&this->m_btnPar2[14][2]._texName[28];
      *(_DWORD *)&this->m_btnPar2[14][2]._texName[32] = v10;
      SaveDataManager = (Actor *)GetSaveDataManager();
      if ( ((Actor *)SaveDataManager)->LoadSaveData(v10) )
      {
        sprintf((char *const)&this->m_OutFrameT, "\\n      %s", (const char *)dword_DD4E3C);
        ((UICaption *)&this->m_btnPar2[14][3].m_posy)->SetEnable((int)&this->m_OutFrameT, 0);
        ((UIRoleSelect *)&this->m_btnPar2[14][2]._texName[40])->SetByte(0);
      }
      else
      {
        sprintf((char *const)&this->m_OutFrameT, "\\n %s", (const char *)dword_DD4F3C);
        ((UICaption *)&this->m_btnPar2[14][5]._texName[112])->SetEnable((int)&this->m_OutFrameT, 0);
        ((UIRoleSelect *)&this->m_btnPar2[14][4]._texName[240])->SetByte(1);
      }
      ((GRPinput *)&g_Input)->Reset();
      v11 = off_5AE388;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v11, 1);
    }
  }
}

// 0x004566C0
int TaskBookUI::ValidateEntries()
{
  int v1; // ebx
  unsigned int v3; // eax
  int v4; // ebp
  unsigned int v5; // ecx
  int *v6; // edi
  int v7; // eax
  MUIDialogMgr *p_refrence_counter; // edi
  int v9; // ebx
  int v10; // ebx
  int i; // edi
  int result; // eax
  float fProgress; // [esp+0x0] [ebp-0x18]
  BYTE Data[4]; // [esp+0x14] [ebp-0x4] BYREF

  v1 = 0;
  *(_DWORD *)Data = 0;
  ReadRegistryString("SOFTWARE\\SOFTSTAR\\PAL3_SAVE", "SEEK", (char *)Data);
  v3 = *(_DWORD *)Data;
  if ( *(_DWORD *)Data >= 0x24u )
  {
    v3 = 35;
    *(_DWORD *)Data = 35;
  }
  v4 = 0;
  v5 = v3;
  if ( v3 <= 4 )
  {
    v3 = 0;
    *(_DWORD *)Data = 0;
  }
  else
  {
    v4 = 4;
  }
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[32] = v5;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[24] = v3 - v4;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] = v5;
  *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] = v5 - v4;
  if ( (int)(v5 - v4) < 31 )
  {
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[8] = (v5 - v4) * *(_DWORD *)&this->m_btnPar2[14][2]._texName[16];
  }
  else
  {
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[12] = 31;
    *(_DWORD *)&this->m_btnPar2[14][2]._texName[8] = (__int64)*(float *)&this->m_btnPar2[14][2].m_color.Color;
  }
  fProgress = (float)*(int *)&this->m_btnPar2[14][2]._texName[8];
  ((CScreenMode *)&this->m_btnPar2[14][1]._element.m_benable)->SetProgress(fProgress);
  v6 = (int *)(&this->stp_BarL + 1);
  do
  {
    v7 = *v6 - *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] * (*(_DWORD *)Data - v4);
    *v6 = v7;
    v6[2] = *(_DWORD *)&this->m_btnPar2[14][2]._texName[16] + v7;
    ((ChoseCompose *)this)->LayoutItems(v1++, *(v6 - 1), *v6, v6[1], v6[2]);
    v6 += 890;
  }
  while ( v1 < 36 );

  p_refrence_counter = (MUIDialogMgr *)&this->m_DlgEx.refrence_counter;
  v9 = 36;
  do
  {
    sub_445E50((int)&p_refrence_counter[-810]);
    (*(void ( **)(MUIDialogMgr *, _DWORD))p_refrence_counter->refrence_counter)(p_refrence_counter, 0);
    p_refrence_counter += 890;
    --v9;
  }
  while ( v9 );
  sub_445E50((int)(&this->stp_BarM.m_fontcolor + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]));
  (**((void ( ***)(int *, int))&this->m_DlgEx.refrence_counter
    + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]))(
    &this->m_DlgEx.refrence_counter + 890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28],
    1);
  v10 = 0;
  for ( i = 0; i < 760; i += 152 )
  {
    result = 3560 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28];
    if ( this->stp_TaskBook.m_caption[result + 16 + v10] )
    {
      (**(void ( ***)(char *, _DWORD))((char *)&this->stp_Magic.m_bfocus + i + result))(
        (char *)&this->stp_Magic.m_bfocus + i + result,
        0);
      result = (**(int ( ***)(char *, int))((char *)&this->stp_Prop.m_texarray.m_ptex[890
                                                                                              * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28]
                                                                                              + 10]
                                                    + i))(
                 (char *)&this->stp_Prop.m_texarray.m_ptex[890 * *(_DWORD *)&this->m_btnPar2[14][2]._texName[28] + 10]
               + i,
                 1);
    }
    ++v10;
  }
  return result;
}

// 0x00477A90
void TaskBookUI::SetEntryCaption(int nVal, int nVal2)
{
  LONG *p_right; // esi
  CHAR *v5; // ebp
  RoleAtt *v6; // ecx
  void (__stdcall *v7)(LPSTR, LPCSTR); // ebp
  LPCSTR v8; // eax

  p_right = &this->rc.right;
  sprintf((char *const)&this->rc.right, g_szSceneUIText);
  v5 = sub_458F70(
         (LPCSTR)(*((_DWORD *)&this->m_btnPar[10][0]._element.m_ratioh + 894 * nVal + 3 * nVal + 3 * nVal2) + 96),
         (int)asc_5B74B8,
         (LPSTR)&this->m_OutFrameR.m_align);
  if ( lstrlenA(v5) <= 0 )
  {
    ((RoleAtt *)v6)->FormatAttributeText();
    v7 = (void ( *)(LPSTR, LPCSTR))lstrcatA;
    lstrcatA((LPSTR)p_right, v8);
  }
  else
  {
    lstrcpyA((LPSTR)p_right, v5);
    v7 = (void ( *)(LPSTR, LPCSTR))lstrcatA;
  }
  switch ( *(_BYTE *)(*((_DWORD *)&this->m_btnPar[10][0]._element.m_ratioh + 894 * nVal + 3 * nVal + 3 * nVal2) + 613) )
  {
    case 1:
    case 3:
      v7((LPSTR)p_right, asc_5B74B4);
      v7((LPSTR)p_right, (LPCSTR)dword_DDAA3C);
      break;
    case 2:
    case 5:
    case 6:
      v7((LPSTR)p_right, asc_5B74B4);
      v7((LPSTR)p_right, byte_DCEB3C);
      break;
    case 4:
    case 7:
      v7((LPSTR)p_right, asc_5B74B4);
      v7((LPSTR)p_right, (LPCSTR)dword_DDA93C);
      break;
    default:
      break;
  }
  ((UICaption *)&this->m_btnPar2[12][5])->SetEnable((int)p_right, 0);
  ((UICaption *)&this->m_btnPar2[12][4]._texName[104])->SetEnable((int)&this->m_OutFrameR.m_align, 0);
}
