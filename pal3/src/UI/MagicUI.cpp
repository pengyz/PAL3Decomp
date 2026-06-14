#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/MagicUI.h"

// Forward declarations for unnamed functions
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
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
extern int dword_DC423C;
extern int dword_DC433C;
extern int dword_DC6B3C;
extern int dword_DCAF3C;
extern int dword_DCB03C;
extern int dword_DCB13C;
extern int dword_DCB23C;
extern int dword_DCB33C;
extern int dword_DCB43C;
extern int dword_DCB53C;
extern int dword_DDBA3C;
extern int dword_DDBB3C;
extern int dword_DDBC3C;
extern int dword_DDBD3C;
extern int dword_DDBE3C;
extern int dword_DDBF3C;
extern int dword_DDC03C;

// 0x00484ED0
int MagicUI::SelectTab3(unsigned __int8 nTab)
{
  this->remarkbuf[84] = nTab;
  return ((LineupComp *)this)->DispatchSlotMethod(3, nTab);
}

// 0x00484EF0
int MagicUI::SelectTab4(unsigned __int8 nTab)
{
  this->remarkbuf[85] = nTab;
  return ((LineupComp *)this)->DispatchSlotMethod(4, nTab);
}

// 0x0048A010
int MagicUI::RefreshAndLayout()
{
  int v2; // edi
  int v3; // ebx
  int v4; // edi

  ((CCBUIPanel *)this)->InitSlots();
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
  ((CameraCtrl *)this)->BuildRenderLists();
  v2 = 0;
  v3 = 60;
  do
  {
    if ( this->m_RoleSkill[0][1].m_Data[v2 + 25] )
    {
      ((UITitle_XJTM *)this)->LayoutGetRects();
      ((UITitle_XJTM *)this)->SetMonsterState(v2, 1u);
      v3 += 122;
    }
    else
    {
      ((UITitle_XJTM *)this)->SetMonsterState(v2, 0);
    }
    ++v2;
  }
  while ( v2 < 5 );
  LineupUI::LoadRoleData();
  ((CameraCtrl *)this)->LoadRoleParams();
  v4 = 0;
  while ( !this->m_RoleSkill[0][1].m_Data[v4 + 25] )
  {
    if ( ++v4 >= 5 )
      return this->InitUILayout();
  }
  *(_DWORD *)&this->m_Role[4].m_F.m_mouseoff = v4;

  ((MainPropUI *)this)->DisplayCaption(v4);
  return this->InitUILayout();
}

// 0x0048A350
int MagicUI::SelectSubTab3(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][1].m_Data[28] = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState(3, nTab);
}

// 0x0048A370
int MagicUI::SelectSubTab4(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][1].m_Data[29] = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState(4, nTab);
}

// 0x0048A390
int MagicUI::InitUILayout()
{
  _PlugInfo **v2; // edi
  int v3; // ebx
  char *v4; // edi
  int v5; // ebx
  _PlugInfo **p_m_ppicInfo; // edi
  int v7; // ebp
  _PlugInfo **v8; // ebx
  UIStatic *v9; // ebx
  int v10; // ebp
  UIStatic *v11; // ebx
  int v12; // ebp
  UIStatic *v13; // ebx
  int v14; // ebp
  UIStatic *v15; // ebx
  int v16; // ebp
  UIStatic *v17; // ebx
  int v18; // ebp
  UIStatic *v19; // ebx
  int v20; // ebp
  UIStatic *v21; // ebx
  int v22; // ebp
  UIStatic *v23; // ebx
  int v24; // ebp
  void ( **v25)(char *, int); // edx
  int result; // eax
  int v27; // [esp+0x48] [ebp+0x4]

  ((MainPropUI *)this)->SetPage(1u);
  v2 = &this->ml_TuList.m_scrollbar.m_texarrayInfo[1];
  *(_DWORD *)&this->m_RoleSkill[0][1].m_Data[48] = v27;
  v3 = 5;
  do
  {
    ((void ( *)(_PlugInfo **, _DWORD))(*v2)->filepos)(v2, 0);
    v2 += 1223;
    --v3;
  }
  while ( v3 );
  v4 = &this->m_parRainbow[5][4]._texName[104];
  v5 = 8;
  do
  {
    sub_445E50((int)v4);
    v4 += 344;
    --v5;
  }
  while ( v5 );
  p_m_ppicInfo = &this->m_btnPar[1][3]._element.m_ppicInfo;
  v7 = 4;
  v8 = &this->m_btnPar[1][3]._element.m_ppicInfo;
  do
  {
    ((void ( *)(_PlugInfo **, _DWORD))(*v8)->filepos)(v8, 0);
    v8 += 38;
    --v7;
  }
  while ( v7 );
  switch ( v27 )
  {
    case 0:
      (*(void ( **)(int *, int))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        1);
      ((UIListBox *)&this->m_parRainbow[6][4].m_xflag)->GetItem();
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        0);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        0);
      (*(void ( **)(int *, _DWORD))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        0);
      v9 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v10 = 9;
      do
      {
        ((UIStatic *)v9++)->CreateFromTemplate();
        --v10;
      }
      while ( v10 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DDBA3C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCAF3C, (const char *)dword_DC423C);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445E50((int)&this->m_parRainbow[5][4]._texName[104]);
      *(_DWORD *)&this->m_parRise[2][0]._texName[12] = 0;
      break;
    case 1:
      (*(void ( **)(int *, _DWORD))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        0);
      (**(void ( ***)(char *, int))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        1);
      ((UIListBox *)&this->m_parRainbow[8][0]._texName[56])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        0);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        0);
      (*(void ( **)(int *, _DWORD))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        0);
      v15 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v16 = 9;
      do
      {
        ((UIStatic *)v15++)->CreateFromTemplate();
        --v16;
      }
      while ( v16 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DDBB3C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCAF3C, (const char *)dword_DC433C);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445FA0(&this->m_btnPar[1][4]._texName[104]);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB03C);
      ((UICaption *)&this->m_btnPar[1][4]._texName[104])->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (**(void ( ***)(char *, int))&this->m_btnPar[1][4]._texName[104])(
        &this->m_btnPar[1][4]._texName[104],
        1);
      sub_445FA0(&this->m_btnPar[1][4]._ptex);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCB13C, (const char *)dword_DC6B3C);
      ((UICaption *)&this->m_btnPar[1][4]._ptex)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      ((void ( *)(gbTexture **, int))this->m_btnPar[1][4].*((_DWORD *)_ptex))(&this->m_btnPar[1][4]._ptex, 1);
      sub_445E50((int)&this->m_parRainbow[6][0].par_radiusX);
      *(_DWORD *)&this->m_parRise[2][0]._texName[12] = 0;
      break;
    case 2:
      (*(void ( **)(int *, _DWORD))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        0);
      (**(void ( ***)(char *, int))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        1);
      ((UIListBox *)&this->m_parRise[0][1]._element.m_text[4])->GetItem();
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        0);
      (*(void ( **)(int *, _DWORD))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        0);
      v17 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v18 = 9;
      do
      {
        ((UIStatic *)v17++)->CreateFromTemplate();
        --v18;
      }
      while ( v18 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DDBC3C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCAF3C, (const char *)dword_DC433C);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445FA0(&this->m_btnPar[1][4]._texName[104]);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB03C);
      ((UICaption *)&this->m_btnPar[1][4]._texName[104])->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (**(void ( ***)(char *, int))&this->m_btnPar[1][4]._texName[104])(
        &this->m_btnPar[1][4]._texName[104],
        1);
      sub_445FA0(&this->m_btnPar[1][4]._ptex);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCB13C, (const char *)dword_DC6B3C);
      ((UICaption *)&this->m_btnPar[1][4]._ptex)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      ((void ( *)(gbTexture **, int))this->m_btnPar[1][4].*((_DWORD *)_ptex))(&this->m_btnPar[1][4]._ptex, 1);
      sub_445E50((int)&this->m_parRainbow[6][0]._texName[208]);
      *(_DWORD *)&this->m_parRise[2][0]._texName[12] = 0;
      break;
    case 3:
      (*(void ( **)(int *, _DWORD))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 0);
      (**(void ( ***)(char *, int))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        1);
      ((UIListBox *)&this->m_parRainbow[7][3]._texName[16])->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        0);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        0);
      (*(void ( **)(int *, _DWORD))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        0);
      v13 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v14 = 9;
      do
      {
        ((UIStatic *)v13++)->CreateFromTemplate();
        --v14;
      }
      while ( v14 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DDBD3C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCAF3C, (const char *)dword_DC433C);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445FA0(&this->m_btnPar[1][4]._texName[104]);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB03C);
      ((UICaption *)&this->m_btnPar[1][4]._texName[104])->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (**(void ( ***)(char *, int))&this->m_btnPar[1][4]._texName[104])(
        &this->m_btnPar[1][4]._texName[104],
        1);
      sub_445FA0(&this->m_btnPar[1][4]._ptex);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCB13C, (const char *)dword_DC6B3C);
      ((UICaption *)&this->m_btnPar[1][4]._ptex)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      ((void ( *)(gbTexture **, int))this->m_btnPar[1][4].*((_DWORD *)_ptex))(&this->m_btnPar[1][4]._ptex, 1);
      sub_445E50((int)&this->m_parRainbow[6][1]._isActive);
      *(_DWORD *)&this->m_parRise[2][0]._texName[12] = 0;
      break;
    case 4:
      (*(void ( **)(int *, _DWORD))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        0);
      (*(void ( **)(float *, int))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 1);
      ((UIListBox *)&this->m_parRainbow[7][1]._x)->GetItem();
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        0);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        0);
      (*(void ( **)(int *, _DWORD))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        0);
      v11 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v12 = 9;
      do
      {
        ((UIStatic *)v11++)->CreateFromTemplate();
        --v12;
      }
      while ( v12 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DDBE3C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCAF3C, (const char *)dword_DC433C);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445FA0(&this->m_btnPar[1][4]._texName[104]);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB03C);
      ((UICaption *)&this->m_btnPar[1][4]._texName[104])->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (**(void ( ***)(char *, int))&this->m_btnPar[1][4]._texName[104])(
        &this->m_btnPar[1][4]._texName[104],
        1);
      sub_445FA0(&this->m_btnPar[1][4]._ptex);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCB13C, (const char *)dword_DC6B3C);
      ((UICaption *)&this->m_btnPar[1][4]._ptex)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      ((void ( *)(gbTexture **, int))this->m_btnPar[1][4].*((_DWORD *)_ptex))(&this->m_btnPar[1][4]._ptex, 1);
      sub_445E50((int)&this->m_parRainbow[6][1]._element.m_bcreateok);
      *(_DWORD *)&this->m_parRise[2][0]._texName[12] = 0;
      break;
    case 5:
      (*(void ( **)(int *, _DWORD))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        0);
      (**(void ( ***)(_BYTE *, int))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        1);
      ((UIListBox *)&this->m_parRise[0][3]._element.m_mouseoff)->GetItem();
      (*(void ( **)(int *, _DWORD))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        0);
      v19 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v20 = 9;
      do
      {
        ((UIStatic *)v19++)->CreateFromTemplate();
        --v20;
      }
      while ( v20 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DDBF3C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCAF3C, (const char *)dword_DC433C);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445FA0(&this->m_btnPar[1][4]._texName[104]);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB03C);
      ((UICaption *)&this->m_btnPar[1][4]._texName[104])->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (**(void ( ***)(char *, int))&this->m_btnPar[1][4]._texName[104])(
        &this->m_btnPar[1][4]._texName[104],
        1);
      sub_445FA0(&this->m_btnPar[1][4]._ptex);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCB13C, (const char *)dword_DC6B3C);
      ((UICaption *)&this->m_btnPar[1][4]._ptex)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      ((void ( *)(gbTexture **, int))this->m_btnPar[1][4].*((_DWORD *)_ptex))(&this->m_btnPar[1][4]._ptex, 1);
      sub_445E50((int)&this->m_parRainbow[6][2]._texName[72]);
      *(_DWORD *)&this->m_parRise[2][0]._texName[12] = 0;
      break;
    case 6:
      (*(void ( **)(int *, _DWORD))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        0);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        0);
      (*(void ( **)(int *, int))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        1);
      ((UIListBox *)&this->m_parRise[1][1].view_radiusX)->GetItem();
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        0);
      v21 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v22 = 9;
      do
      {
        ((UIStatic *)v21++)->CreateFromTemplate();
        --v22;
      }
      while ( v22 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DDC03C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCAF3C, (const char *)dword_DC433C);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445FA0(&this->m_btnPar[1][4]._texName[104]);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB03C);
      ((UICaption *)&this->m_btnPar[1][4]._texName[104])->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (**(void ( ***)(char *, int))&this->m_btnPar[1][4]._texName[104])(
        &this->m_btnPar[1][4]._texName[104],
        1);
      sub_445FA0(&this->m_btnPar[1][4]._ptex);
      sprintf(&this->m_ComSkill[6][2], "%s%s", (const char *)dword_DCB13C, (const char *)dword_DC6B3C);
      ((UICaption *)&this->m_btnPar[1][4]._ptex)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      ((void ( *)(gbTexture **, int))this->m_btnPar[1][4].*((_DWORD *)_ptex))(&this->m_btnPar[1][4]._ptex, 1);
      sub_445E50((int)&this->m_parRainbow[6][2]._sizeY);
      *(_DWORD *)&this->m_parRise[2][0]._texName[12] = 0;
      break;
    case 7:
      (*(void ( **)(int *, _DWORD))this->m_parRainbow[6][4].m_xflag)(
        &this->m_parRainbow[6][4].m_xflag,
        0);
      (*(void ( **)(float *, _DWORD))LODWORD(this->m_parRainbow[7][1]._x))(&this->m_parRainbow[7][1]._x, 0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[7][3]._texName[16])(
        &this->m_parRainbow[7][3]._texName[16],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRainbow[8][0]._texName[56])(
        &this->m_parRainbow[8][0]._texName[56],
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_parRise[0][1]._element.m_text[4])(
        &this->m_parRise[0][1]._element.m_text[4],
        0);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_parRise[0][3]._element.m_mouseoff)(
        &this->m_parRise[0][3]._element.m_mouseoff,
        0);
      (*(void ( **)(int *, _DWORD))this->m_parRise[1][1].view_radiusX)(
        &this->m_parRise[1][1].view_radiusX,
        0);
      (*(void ( **)(float *, int))LODWORD(this->m_parRise[1][3].m_helix_rx))(
        &this->m_parRise[1][3].m_helix_rx,
        1);
      ((UIListBox *)&this->m_parRise[1][3].m_helix_rx)->GetItem();
      v23 = (UIStatic *)&this->m_Ctrlbtn[6].m_caption[84];
      v24 = 9;
      do
      {
        ((UIStatic *)v23++)->CreateFromTemplate();
        --v24;
      }
      while ( v24 );
      ((UICaption *)&this->m_btnPar[1][3]._element.m_ppicInfo)->SetEnable((int)dword_DCB23C, 0);
      ((void ( *)(_PlugInfo **, int))(*p_m_ppicInfo)->filepos)(&this->m_btnPar[1][3]._element.m_ppicInfo, 1);
      sub_445FA0(&this->m_btnPar[1][4].m_time.oldtick);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB33C);
      ((UICaption *)&this->m_btnPar[1][4].m_time.oldtick)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (*(void ( **)(unsigned int *, int))this->m_btnPar[1][4].m_time.oldtick)(
        &this->m_btnPar[1][4].m_time.oldtick,
        1);
      sub_445FA0(&this->m_btnPar[1][4]._texName[104]);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB43C);
      ((UICaption *)&this->m_btnPar[1][4]._texName[104])->SetEnable((int)&this->m_ComSkill[6][2], 0);
      (**(void ( ***)(char *, int))&this->m_btnPar[1][4]._texName[104])(
        &this->m_btnPar[1][4]._texName[104],
        1);
      sub_445FA0(&this->m_btnPar[1][4]._ptex);
      sprintf(&this->m_ComSkill[6][2], byte_5967B0, dword_DCB53C);
      ((UICaption *)&this->m_btnPar[1][4]._ptex)->SetEnable((int)&this->m_ComSkill[6][2], 0);
      ((void ( *)(gbTexture **, int))this->m_btnPar[1][4].*((_DWORD *)_ptex))(&this->m_btnPar[1][4]._ptex, 1);
      sub_445E50((int)&this->m_parRainbow[6][3]._texName[176]);
      break;
    default:
      break;
  }
  v25 = *(void ( ***)(char *, int))&this->ml_FengList.m_column[0].head[32];
  *(_DWORD *)&this->m_RoleSkill[0][1].m_Data[40] = v27;
  (*v25)(&this->ml_FengList.m_column[0].head[32], 1);
  ((UICaption *)&this->ml_FengList.m_scrollbar.m_bk.m_id)->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->ml_FengList.m_scrollbar.m_texarray.m_ptex[11])->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->ml_FengList.m_column[2].head[16])->SetEnable((int)g_szSceneUIText, 0);
  return result;
}

// 0x0048B8F0
int MagicUI::UpdateViewListItems()
{
  UIListBox *p_m_xflag; // edi
  int v3; // ebx
  char *v4; // ebp
  char *v5; // ebp
  _DWORD *v6; // esi
  int v7; // eax
  int i; // esi
  int v9; // eax
  float *p_x; // edi
  int v11; // eax
  char *v12; // esi
  _DWORD *v13; // ebx
  int v14; // ebp
  int v15; // eax
  int v16; // edx
  int j; // esi
  int v18; // eax
  UIListBox *v19; // edi
  int v20; // eax
  char *v21; // esi
  _DWORD *v22; // ebx
  int v23; // ebp
  int v24; // eax
  int v25; // edx
  int k; // esi
  int v27; // eax
  UIListBox *v28; // edi
  int v29; // eax
  char *v30; // esi
  _DWORD *v31; // ebx
  int v32; // ebp
  int v33; // eax
  int v34; // edx
  int m; // esi
  int v36; // eax
  UIListBox *v37; // edi
  int v38; // eax
  char *v39; // esi
  _DWORD *v40; // ebx
  int v41; // ebp
  int v42; // eax
  int v43; // edx
  LONG n; // esi
  int v45; // eax
  UIListBox *p_m_mouseoff; // edi
  int v47; // eax
  char *v48; // esi
  _DWORD *v49; // ebx
  int v50; // ebp
  int v51; // eax
  int v52; // edx
  int ii; // esi
  int v54; // eax
  int *p_view_radiusX; // edi
  int v56; // eax
  char *v57; // esi
  _DWORD *v58; // ebx
  int v59; // ebp
  int v60; // eax
  int v61; // edx
  int jj; // esi
  int v63; // eax
  MagicUI *v64; // edi
  float *p_m_helix_rx; // ebp
  int v66; // eax
  int *v67; // ebx
  int SkillNum; // eax
  int v69; // esi
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int result; // eax
  _DWORD *v75; // [esp+0x14] [ebp-0x8]
  float *v76; // [esp+0x14] [ebp-0x8]
  int nVal; // [esp+0x18] [ebp-0x4] BYREF
  int v78; // [esp+0x20] [ebp+0x4]

  p_m_xflag = (UIListBox *)&this->m_parRainbow[6][4].m_xflag;
  ((UIListBox *)&this->m_parRainbow[6][4].m_xflag)->ClearAll();
  v3 = 0;
  v4 = (char *)this + 9536 * v78;
  v75 = v4;
  if ( *((int *)v4 + 838) > 0 )
  {
    v5 = &this->m_ComSkill[6][2];
    v6 = v75 + 841;
    do
    {
      sprintf(v5, byte_5967B0, *v6 + 28);
      nVal = ((UIListBox *)p_m_xflag)->SetItemOffset(v5, 0);
      if ( *(int *)(*v6 + 688) < 0 )
      {
        v7 = *(_DWORD *)(*v6 + 692);
        if ( v7 >= 0 )
          sprintf(v5, &dir[20], v7);
      }
      else
      {
        sprintf(v5, &dir[20], *(_DWORD *)(*v6 + 688));
      }
      ((UIListBox *)p_m_xflag)->SetMouseMoveSel(1, nVal, v5, 0);
      ++v3;
      v6 += 3;
    }
    while ( v3 < v75[838] );
    v4 = (char *)v75;
  }
  ((UIListBox *)p_m_xflag)->GetItem();
  ((UIListBox *)p_m_xflag)->GetItem();
  for ( i = 0; i < *((_DWORD *)v4 + 838); ++i )
  {
    if ( ((CameraCtrl *)this)->HandleCameraEvent(i, 0) )
    {
      if ( i < 0 || i >= p_m_xflag->m_column[0].items.capacity )
        v9 = 0;
      else
        v9 = *(_DWORD *)&p_m_xflag->m_column[0].items.m_pData[4 * i];
      *(_DWORD *)(v9 + 68) = p_m_xflag->m_fontcolor.Color;
    }
    else
    {
      ((UITabCtrl *)p_m_xflag)->SetItemParam(i);
    }
  }
  p_x = &this->m_parRainbow[7][1]._x;
  ((UIListBox *)&this->m_parRainbow[7][1]._x)->ClearAll();
  v11 = *((_DWORD *)v4 + 2030);
  nVal = 0;
  if ( v11 > 0 )
  {
    v12 = &this->m_ComSkill[6][2];
    v13 = v75 + 2033;
    do
    {
      sprintf(v12, byte_5967B0, *v13 + 28);
      v14 = ((UIListBox *)p_x)->SetItemOffset(v12, 0);
      if ( *(int *)(*v13 + 688) <= 0 )
      {
        v15 = *(_DWORD *)(*v13 + 692);
        if ( v15 <= 0 )
          sprintf(v12, &dir[20], 0);
        else
          sprintf(v12, &dir[20], v15);
      }
      else
      {
        sprintf(v12, &dir[20], *(_DWORD *)(*v13 + 688));
      }
      ((UIListBox *)p_x)->SetMouseMoveSel(1, v14, v12, 0);
      sprintf(v12, &dir[20], *((unsigned __int16 *)v13 - 2) + 1);
      ((UIListBox *)p_x)->SetMouseMoveSel(2, v14, v12, 0);
      sprintf(v12, &dir[20], *((unsigned __int16 *)v13 - 1));
      ((UIListBox *)p_x)->SetMouseMoveSel(3, v14, v12, 0);
      v13 += 3;
      v16 = v75[2030];
      ++nVal;
    }
    while ( nVal < v16 );
  }
  ((UIListBox *)p_x)->GetItem();
  ((UIListBox *)p_x)->GetItem();
  for ( j = 0; j < v75[2030]; ++j )
  {
    if ( ((CameraCtrl *)this)->HandleCameraEvent(j, 4) )
    {
      if ( j < 0 || j >= SLODWORD(this->m_parRainbow[7][2].m_helix_rx) )
        v18 = 0;
      else
        v18 = *(_DWORD *)(LODWORD(this->m_parRainbow[7][2].m_tempy) + 4 * j);
      *(float *)(v18 + 68) = this->m_parRainbow[7][1]._y;
    }
    else
    {
      ((UITabCtrl *)p_x)->SetItemParam(j);
    }
  }
  v19 = (UIListBox *)&this->m_parRainbow[7][3]._texName[16];
  ((UIListBox *)&this->m_parRainbow[7][3]._texName[16])->ClearAll();
  v20 = v75[1732];
  nVal = 0;
  if ( v20 > 0 )
  {
    v21 = &this->m_ComSkill[6][2];
    v22 = v75 + 1735;
    do
    {
      sprintf(v21, byte_5967B0, *v22 + 28);
      v23 = ((UIListBox *)v19)->SetItemOffset(v21, 0);
      if ( *(int *)(*v22 + 688) <= 0 )
      {
        v24 = *(_DWORD *)(*v22 + 692);
        if ( v24 <= 0 )
          sprintf(v21, &dir[20], 0);
        else
          sprintf(v21, &dir[20], v24);
      }
      else
      {
        sprintf(v21, &dir[20], *(_DWORD *)(*v22 + 688));
      }
      ((UIListBox *)v19)->SetMouseMoveSel(1, v23, v21, 0);
      sprintf(v21, &dir[20], *((unsigned __int16 *)v22 - 2) + 1);
      ((UIListBox *)v19)->SetMouseMoveSel(2, v23, v21, 0);
      sprintf(v21, &dir[20], *((unsigned __int16 *)v22 - 1));
      ((UIListBox *)v19)->SetMouseMoveSel(3, v23, v21, 0);
      v22 += 3;
      v25 = v75[1732];
      ++nVal;
    }
    while ( nVal < v25 );
  }
  ((UIListBox *)v19)->GetItem();
  ((UIListBox *)v19)->GetItem();
  for ( k = 0; k < v75[1732]; ++k )
  {
    if ( ((CameraCtrl *)this)->HandleCameraEvent(k, 3) )
    {
      if ( k < 0 || k >= this->m_parRainbow[7][4].m_xflag )
        v27 = 0;
      else
        v27 = *(_DWORD *)(LODWORD(this->m_parRainbow[7][4].m_riseY) + 4 * k);
      *(_DWORD *)(v27 + 68) = *(_DWORD *)&this->m_parRainbow[7][3]._texName[20];
    }
    else
    {
      ((UITabCtrl *)v19)->SetItemParam(k);
    }
  }
  v28 = (UIListBox *)&this->m_parRainbow[8][0]._texName[56];
  ((UIListBox *)&this->m_parRainbow[8][0]._texName[56])->ClearAll();
  v29 = v75[1136];
  nVal = 0;
  if ( v29 > 0 )
  {
    v30 = &this->m_ComSkill[6][2];
    v31 = v75 + 1139;
    do
    {
      sprintf(v30, byte_5967B0, *v31 + 28);
      v32 = ((UIListBox *)v28)->SetItemOffset(v30, 0);
      if ( *(int *)(*v31 + 688) <= 0 )
      {
        v33 = *(_DWORD *)(*v31 + 692);
        if ( v33 <= 0 )
          sprintf(v30, &dir[20], 0);
        else
          sprintf(v30, &dir[20], v33);
      }
      else
      {
        sprintf(v30, &dir[20], *(_DWORD *)(*v31 + 688));
      }
      ((UIListBox *)v28)->SetMouseMoveSel(1, v32, v30, 0);
      sprintf(v30, &dir[20], *((unsigned __int16 *)v31 - 2) + 1);
      ((UIListBox *)v28)->SetMouseMoveSel(2, v32, v30, 0);
      sprintf(v30, &dir[20], *((unsigned __int16 *)v31 - 1));
      ((UIListBox *)v28)->SetMouseMoveSel(3, v32, v30, 0);
      v31 += 3;
      v34 = v75[1136];
      ++nVal;
    }
    while ( nVal < v34 );
  }
  ((UIListBox *)v28)->GetItem();
  ((UIListBox *)v28)->GetItem();
  for ( m = 0; m < v75[1136]; ++m )
  {
    if ( ((CameraCtrl *)this)->HandleCameraEvent(m, 1) )
    {
      if ( m < 0 || m >= *(_DWORD *)&this->m_parRise[0][0]._texName[240] )
        v36 = 0;
      else
        v36 = *(_DWORD *)(*(_DWORD *)&this->m_parRise[0][0]._texName[236] + 4 * m);
      *(_DWORD *)(v36 + 68) = *(_DWORD *)&this->m_parRainbow[8][0]._texName[60];
    }
    else
    {
      ((UITabCtrl *)v28)->SetItemParam(m);
    }
  }
  v37 = (UIListBox *)&this->m_parRise[0][1]._element.m_text[4];
  ((UIListBox *)&this->m_parRise[0][1]._element.m_text[4])->ClearAll();
  v38 = v75[1434];
  nVal = 0;
  if ( v38 > 0 )
  {
    v39 = &this->m_ComSkill[6][2];
    v40 = v75 + 1437;
    do
    {
      sprintf(v39, byte_5967B0, *v40 + 28);
      v41 = ((UIListBox *)v37)->SetItemOffset(v39, 0);
      if ( *(int *)(*v40 + 688) <= 0 )
      {
        v42 = *(_DWORD *)(*v40 + 692);
        if ( v42 <= 0 )
          sprintf(v39, &dir[20], 0);
        else
          sprintf(v39, &dir[20], v42);
      }
      else
      {
        sprintf(v39, &dir[20], *(_DWORD *)(*v40 + 688));
      }
      ((UIListBox *)v37)->SetMouseMoveSel(1, v41, v39, 0);
      sprintf(v39, &dir[20], *((unsigned __int16 *)v40 - 2) + 1);
      ((UIListBox *)v37)->SetMouseMoveSel(2, v41, v39, 0);
      sprintf(v39, &dir[20], *((unsigned __int16 *)v40 - 1));
      ((UIListBox *)v37)->SetMouseMoveSel(3, v41, v39, 0);
      v40 += 3;
      v43 = v75[1434];
      ++nVal;
    }
    while ( nVal < v43 );
  }
  ((UIListBox *)v37)->GetItem();
  ((UIListBox *)v37)->GetItem();
  for ( n = 0; n < v75[1434]; ++n )
  {
    if ( ((CameraCtrl *)this)->HandleCameraEvent(n, 2) )
    {
      if ( n < 0 || n >= this->m_parRise[0][2]._element.m_rect.top )
        v45 = 0;
      else
        v45 = *(_DWORD *)(this->m_parRise[0][2]._element.m_rect.left + 4 * n);
      *(_DWORD *)(v45 + 68) = *(_DWORD *)&this->m_parRise[0][1]._element.m_text[8];
    }
    else
    {
      ((UITabCtrl *)v37)->SetItemParam(n);
    }
  }
  p_m_mouseoff = (UIListBox *)&this->m_parRise[0][3]._element.m_mouseoff;
  ((UIListBox *)&this->m_parRise[0][3]._element.m_mouseoff)->ClearAll();
  v47 = v75[2328];
  nVal = 0;
  if ( v47 > 0 )
  {
    v48 = &this->m_ComSkill[6][2];
    v49 = v75 + 2331;
    do
    {
      sprintf(v48, byte_5967B0, *v49 + 28);
      v50 = ((UIListBox *)p_m_mouseoff)->SetItemOffset(v48, 0);
      if ( *(int *)(*v49 + 688) <= 0 )
      {
        v51 = *(_DWORD *)(*v49 + 692);
        if ( v51 <= 0 )
          sprintf(v48, &dir[20], 0);
        else
          sprintf(v48, &dir[20], v51);
      }
      else
      {
        sprintf(v48, &dir[20], *(_DWORD *)(*v49 + 688));
      }
      ((UIListBox *)p_m_mouseoff)->SetMouseMoveSel(1, v50, v48, 0);
      sprintf(v48, &dir[20], *((unsigned __int16 *)v49 - 2) + 1);
      ((UIListBox *)p_m_mouseoff)->SetMouseMoveSel(2, v50, v48, 0);
      sprintf(v48, &dir[20], *((unsigned __int16 *)v49 - 1));
      ((UIListBox *)p_m_mouseoff)->SetMouseMoveSel(3, v50, v48, 0);
      v49 += 3;
      v52 = v75[2328];
      ++nVal;
    }
    while ( nVal < v52 );
  }
  ((UIListBox *)p_m_mouseoff)->GetItem();
  ((UIListBox *)p_m_mouseoff)->GetItem();
  for ( ii = 0; ii < v75[2328]; ++ii )
  {
    if ( ((CameraCtrl *)this)->HandleCameraEvent(ii, 5) )
    {
      if ( ii < 0 || ii >= this->m_parRise[0][4]._element.m_benable )
        v54 = 0;
      else
        v54 = *(_DWORD *)(this->m_parRise[0][4]._element.m_bvisible + 4 * ii);
      *(_DWORD *)(v54 + 68) = this->m_parRise[0][3]._element.m_FVF;
    }
    else
    {
      ((UITabCtrl *)p_m_mouseoff)->SetItemParam(ii);
    }
  }
  p_view_radiusX = &this->m_parRise[1][1].view_radiusX;
  ((UIListBox *)&this->m_parRise[1][1].view_radiusX)->ClearAll();
  v56 = v75[2626];
  nVal = 0;
  if ( v56 > 0 )
  {
    v57 = &this->m_ComSkill[6][2];
    v58 = v75 + 2629;
    do
    {
      sprintf(v57, byte_5967B0, *v58 + 28);
      v59 = ((UIListBox *)p_view_radiusX)->SetItemOffset(v57, 0);
      if ( *(int *)(*v58 + 688) <= 0 )
      {
        v60 = *(_DWORD *)(*v58 + 692);
        if ( v60 <= 0 )
          sprintf(v57, &dir[20], 0);
        else
          sprintf(v57, &dir[20], v60);
      }
      else
      {
        sprintf(v57, &dir[20], *(_DWORD *)(*v58 + 688));
      }
      ((UIListBox *)p_view_radiusX)->SetMouseMoveSel(1, v59, v57, 0);
      sprintf(v57, &dir[20], *((unsigned __int16 *)v58 - 2) + 1);
      ((UIListBox *)p_view_radiusX)->SetMouseMoveSel(2, v59, v57, 0);
      sprintf(v57, &dir[20], *((unsigned __int16 *)v58 - 1));
      ((UIListBox *)p_view_radiusX)->SetMouseMoveSel(3, v59, v57, 0);
      v58 += 3;
      v61 = v75[2626];
      ++nVal;
    }
    while ( nVal < v61 );
  }
  ((UIListBox *)p_view_radiusX)->GetItem();
  ((UIListBox *)p_view_radiusX)->GetItem();
  for ( jj = 0; jj < v75[2626]; ++jj )
  {
    if ( ((CameraCtrl *)this)->HandleCameraEvent(jj, 6) )
    {
      if ( jj < 0 || jj >= *(_DWORD *)&this->m_parRise[1][1]._element.m_text[4] )
        v63 = 0;
      else
        v63 = *(_DWORD *)(*(_DWORD *)this->m_parRise[1][1]._element.m_text + 4 * jj);
      *(_DWORD *)(v63 + 68) = this->m_parRise[1][1].view_radiusY;
    }
    else
    {
      ((UITabCtrl *)p_view_radiusX)->SetItemParam(jj);
    }
  }
((CameraCtrl *)this)->LoadRoleParams();
  p_m_helix_rx = &this->m_parRise[1][3].m_helix_rx;
  ((UIListBox *)&this->m_parRise[1][3].m_helix_rx)->ClearAll();
  v66 = 0;
  nVal = 0;
  v67 = (int *)&this->m_RoleSkill[0][2].m_Data[76];
  v76 = (float *)&this->m_RoleSkill[0][2].m_Data[4 * v78 + 88];
  do
  {
    if ( g_SaveSlotFlags[8 * v78 + v66] )
    {
      SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*(v67 - 65));
      if ( !SkillNum )
        break;
      lstrcpyA((LPSTR)v67 - 256, (LPCSTR)(SkillNum + 4));
      v69 = -1;
      if ( *v67 )
      {
        v70 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(*v67);
        if ( v70 )
          v69 = ((UIListBox *)p_m_helix_rx)->SetItemOffset((char *)(v70 + 4), 0);
      }
      if ( v67[1] )
      {
        v71 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v67[1]);
        if ( v71 )
        {
          if ( v69 >= 0 )
            ((UIListBox *)p_m_helix_rx)->SetMouseMoveSel(1, v69, (char *)(v71 + 4), 0);
        }
      }
      if ( v67[2] )
      {
        v72 = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v67[2]);
        if ( v72 )
        {
          if ( v69 >= 0 )
            ((UIListBox *)p_m_helix_rx)->SetMouseMoveSel(2, v69, (char *)(v72 + 4), 0);
        }
      }
      sprintf(&this->m_ComSkill[6][2], "%d%%", (unsigned int)(__int64)(*v76 * 100.0));
      ((UIListBox *)p_m_helix_rx)->SetMouseMoveSel(3, v69, &this->m_ComSkill[6][2], 0);
*(v67 - 67) = v78;
      v66 = nVal;
      *(v67 - 66) = v69;
    }
    ++v66;
    v67 += 75;
    nVal = v66;
    v76 += 75;
  }
  while ( v66 < 8 );
  ((MagicUI *)v64)->InitUILayout();
  ((UIListBox *)p_m_helix_rx)->GetItem();
  ((UIListBox *)p_m_helix_rx)->GetItem();
  ((UICaption *)&this->ml_FengList.m_scrollbar.m_bk.m_id)->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->ml_FengList.m_scrollbar.m_texarray.m_ptex[11])->SetEnable((int)g_szSceneUIText, 0);
  return result;
}

// 0x00494620
int MagicUI::SelectBigMapTab3(char nTab)
{
  this->remarkbuf[84] = nTab;
  return ((UIBigMap *)this)->SetEntryVisible(3, nTab);
}

// 0x00494640
int MagicUI::SelectBigMapTab4(char nTab)
{
  this->remarkbuf[85] = nTab;
  return ((UIBigMap *)this)->SetEntryVisible(4, nTab);
}

// 0x00494660
void MagicUI::ProcessInput()
{
  int v2; // edi
  int v3; // ebp
  int v4; // eax
  int p_DWORD; // [esp+0xC] [ebp-0x10] BYREF
  int v6; // [esp+0x10] [ebp-0xC]
  int v7; // [esp+0x14] [ebp-0x8]
  int v8; // [esp+0x18] [ebp-0x4]

  ((CScreenMode *)this)->ResetProgressList();
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
  v6 = 62;
  p_DWORD = 686;
  v7 = 796;
  v8 = 157;
  v2 = 0;
  v3 = 60;
  do
  {
    if ( this->remarkbuf[v2 + 81] )
    {
      ((CScreenMode *)this)->GetPlayerAttByIndex(v2);
      ((UIBigMap *)this)->ProcessChildItem(v2, &p_DWORD);
      ((UIBigMap *)this)->SetEntryVisible(v2, 1u);
      v3 += 122;
      v6 = v3;
      v8 = v3 + 95;
    }
    else
    {
      ((UIBigMap *)this)->SetEntryVisible(v2, 0);
    }
    ++v2;
  }
  while ( v2 < 5 );
  ((StateUI *)this)->UpdateScrollBars();
  *(_DWORD *)&this->remarkbuf[88] = 0;
  v4 = 0;
  while ( !this->remarkbuf[v4 + 81] )
  {
    if ( ++v4 >= 5 )
      return;
  }
  *(_DWORD *)&this->ml_ShuiList.m_column[4].head[20] = v4;
  *(_DWORD *)&this->remarkbuf[92] = 0;
  *(_DWORD *)&this->remarkbuf[88] = -1;
  ((StateUI *)this)->UpdateRoleTooltip(v4);
  ((MainPropUI *)this)->ShowSubPanels(*(_DWORD *)&this->ml_ShuiList.m_column[4].head[20]);
  ((MainEquipUI *)this)->UpdateTooltip(*(_DWORD *)&this->ml_ShuiList.m_column[4].head[20]);
  ((EquipUI *)this)->HandleInput(*(_DWORD *)&this->ml_ShuiList.m_column[4].head[20], 0);
}

// 0x0049E8A0
int MagicUI::SelectXJTMTab3(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][0].m_Data[32] = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState2(3, nTab);
}

// 0x0049E8C0
int MagicUI::SelectXJTMTab4(unsigned __int8 nTab)
{
  this->m_RoleSkill[0][0].m_Data[33] = nTab;
  return ((UITitle_XJTM *)this)->SetMonsterState2(4, nTab);
}

// 0x004A4AC0
int MagicUI::SetSelectedData()
{
  unsigned int data; // [esp+0x8] [ebp+0x4]

  if ( ((EquipUI *)this)->GetSelected() < 5 )
  {
    this->remarkbuf[84] = data;
    ((UIBase *)this)->SetItemData(3, data);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[16])->SelectSubTab3(data);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[20])->SelectBigMapTab3(data);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[24])->SelectXJTMTab3(data);
    return ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[12])->SelectTab3(data);
  }
  else
  {
    this->remarkbuf[84] = 0;
    ((UIBase *)this)->SetItemData(3, 0);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[16])->SelectSubTab3(0);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[20])->SelectBigMapTab3(0);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[24])->SelectXJTMTab3(0);
    return ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[12])->SelectTab3(0);
  }
}

// 0x004A4B70
void MagicUI::Init()
{
  unsigned int data; // [esp+0x8] [ebp+0x4]

  if ( ((EquipUI *)this)->GetSelected() < 5 )
  {
    this->remarkbuf[85] = data;
    ((UIBase *)this)->SetItemData(4, data);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[16])->SelectSubTab4(data);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[20])->SelectBigMapTab4(data);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[24])->SelectXJTMTab4(data);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[12])->SelectTab4(data);
  }
  else
  {
    this->remarkbuf[85] = 0;
    ((UIBase *)this)->SetItemData(4, 0);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[16])->SelectSubTab4(0);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[20])->SelectBigMapTab4(0);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[24])->SelectXJTMTab4(0);
    ((MagicUI *)*(MagicUI **)&this->m_btnPar2[14][6]._texName[12])->SelectTab4(0);
  }
}
