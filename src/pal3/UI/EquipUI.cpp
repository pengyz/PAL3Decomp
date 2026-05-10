#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/EquipUI.h"

// Forward declarations for unnamed functions
int sub_47F590(...);
int sub_483650(...);
int sub_484E70(...);
int sub_48A2F0(...);
int sub_48D5D0(...);
int sub_4945C0(...);
int sub_496190(...);
int sub_49E840(...);
int sub_49F2E0(...);
int sub_4A2170(...);
int sub_4A22E0(...);
int sub_4A26D0(...);
int sub_4A2BD0(...);
int sub_4A2F90(...);
int sub_4AB6B0(...);
int sub_4B0820(...);
int sub_4B4690(...);
int sub_4B47E0(...);

// Unnamed globals (extern)
extern char aUiGamemainuiCo_19[];
extern char aUiGamemainuiCo_23[];
extern char aUiGamemainuiSt_1[];
extern unsigned char byte_5CEFA8;
extern unsigned char byte_5CEFA9;
extern unsigned char byte_DE5F92;
extern unsigned char byte_DE5F93;
extern void *off_56F040;

// 0x004A1E40
int EquipUI::Create()
{
  this->UIListBox();
  *(_DWORD *)&this->UIFrameWnd[88] = 800;
  *(_DWORD *)&this->UIFrameWnd[92] = 600;
  *(_DWORD *)&this->UIFrameWnd[96] = 0;
  *(_DWORD *)&this->UIFrameWnd[100] = 0;
  this->UIFrameWnd[360] = 0;
  *(_DWORD *)&this->UIFrameWnd[368] = 0;
  this->UIFrameWnd[372] = 0;
  this->UIFrameWnd[373] = 0;
  &this->UIFrameWnd[376]->UIFrameWnd();
  &this->UIFrameWnd[528]->UIFrameWnd();
  &this->UIFrameWnd[680]->UIFrameWnd();
  &this->UIFrameWnd[832]->UIFrameWnd();
  &this->UIFrameWnd[984]->UIFrameWnd();
  &this->UIFrameWnd[1136]->UIFrameWnd();
  &this->UIFrameWnd[1288]->_UIScene();
  &this->UIFrameWnd[1632]->_UIScene();
  &this->UIFrameWnd[1976]->_UIScene();
  &this->UIFrameWnd[2320]->_UIScene();
  &this->UIFrameWnd[2664]->_UIScene();
  &this->UIFrameWnd[3008]->_UIScene();
  &this->UIFrameWnd[3352]->_UIScene();
  &this->UIFrameWnd[3696]->_UIScene();
  &this->UIFrameWnd[4040]->_UIScene();
  &this->UIFrameWnd[4384]->UIFrameWnd();
  &this->UIFrameWnd[4552]->UIFrameWnd();
  &this->UIFrameWnd[4704]->UIFrameWnd();
  `eh vector constructor iterator'(
    &this->UIFrameWnd[4856],
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    &this->UIFrameWnd[79608],
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  (_BYTE *->UIFrameWnd()this + 154516);
  (_BYTE *->UIFrameWnd()this + 154668);
  (_BYTE *->UIFrameWnd()this + 154820);
  (_BYTE *->UIFrameWnd()this + 154972);
  `eh vector constructor iterator'(
    (char *)this + 155140,
    0xECCu,
    5,
    (void (*)(void *))sub_4A2170,
    (void (*)(void *))sub_4A22E0);
  `eh vector constructor iterator'(
    (char *)this + 174080,
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()this + 174688);
  `eh vector constructor iterator'(
    (char *)this + 174856,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_DWORD *->_UIScene()this + 43924);
  *((_DWORD *)this + 44014) = 0;
  *((_DWORD *)this + 44015) = 0;
  *((_DWORD *)this + 44016) = 0;
  *((_DWORD *)this + 44017) = 0;
  *((_DWORD *)this + 44018) = 0;
  *((_DWORD *)this + 44019) = 0;
  *((_DWORD *)this + 44020) = 0;
  *((_DWORD *)this + 44021) = 0;
  (_BYTE *->UIFrameWnd()this + 176092);
  *(_DWORD *)this->UIFrameWnd = &off_56F040;
  this->UIFrameWnd[365] = 0;
  this->UIFrameWnd[364] = 0;
  this->UIFrameWnd[362] = 0;
  this->UIFrameWnd[361] = 0;
  this->UIFrameWnd[363] = 0;
  *((_DWORD *)this + 38622) = 0;
  *((_DWORD *)this + 38623) = 0;
  *((_DWORD *)this + 38624) = 0;
  *((_DWORD *)this + 44061) = 0;
  return (int)this->UIFrameWnd;
}

// 0x004A4220
void EquipUI::Init()
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  const CHAR *v6; // ebp
  gbRefObject **v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // edx
  char *v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // ecx
  int v27; // [esp+3Ch] [ebp-64h]
  int v28; // [esp+3Ch] [ebp-64h]
  int v29; // [esp+3Ch] [ebp-64h]
  int v30; // [esp+3Ch] [ebp-64h]
  int v31; // [esp+3Ch] [ebp-64h]
  int v32; // [esp+3Ch] [ebp-64h]
  int v33; // [esp+3Ch] [ebp-64h]
  int v34; // [esp+3Ch] [ebp-64h]
  int v35; // [esp+3Ch] [ebp-64h]
  int v36; // [esp+3Ch] [ebp-64h]
  int v37; // [esp+40h] [ebp-60h]
  int v38; // [esp+40h] [ebp-60h]
  int v39; // [esp+40h] [ebp-60h]
  int v40; // [esp+40h] [ebp-60h]
  int v41; // [esp+40h] [ebp-60h]
  int v42; // [esp+4Ch] [ebp-54h] BYREF
  int v43; // [esp+50h] [ebp-50h] BYREF
  int v44; // [esp+54h] [ebp-4Ch] BYREF
  int v45; // [esp+58h] [ebp-48h]
  int v46; // [esp+5Ch] [ebp-44h]
  int v47; // [esp+60h] [ebp-40h]
  int v48[4]; // [esp+64h] [ebp-3Ch] BYREF
  int v49; // [esp+74h] [ebp-2Ch] BYREF
  int v50; // [esp+78h] [ebp-28h]
  int v51; // [esp+7Ch] [ebp-24h]
  int v52; // [esp+80h] [ebp-20h]
  _DWORD v53[4]; // [esp+84h] [ebp-1Ch] BYREF
  int v54; // [esp+9Ch] [ebp-4h]

  v2 = *(_DWORD *)&this->UIFrameWnd[88];
  v3 = *(_DWORD *)&this->UIFrameWnd[92];
  *(_DWORD *)&this->UIFrameWnd[80] = v2;
  *(_DWORD *)&this->UIFrameWnd[76] = 0;
  *(_DWORD *)&this->UIFrameWnd[72] = 0;
  *(_DWORD *)&this->UIFrameWnd[84] = v3;
  (UIWnd *->SetSelTexture()this,
    -1,
    *(_DWORD *)&this->UIFrameWnd[72],
    *(_DWORD *)&this->UIFrameWnd[76],
    *(_DWORD *)&this->UIFrameWnd[80],
    *(_DWORD *)&this->UIFrameWnd[84],
    0);
  v4 = *(_DWORD *)&this->UIFrameWnd[76] + 18;
  v49 = *(_DWORD *)&this->UIFrameWnd[72] + 592;
  v50 = v4;
  v51 = v49 + 192;
  v52 = v4 + 526;
  (*(void (**)(char *, int, int *, EquipUI *))(*(_DWORD *)&this->UIFrameWnd[376] + 16))(
    &this->UIFrameWnd[376],
    161,
    &v49,
    this);
  (gbRefObject **->CreateFromTemplate()&this->UIFrameWnd[376], aUiGamemainuiSt_1, byte_5CEFA8);
  v5 = *(_DWORD *)&this->UIFrameWnd[528];
  v50 += 26;
  v49 = v51;
  v52 = v50 + 526;
  v51 += 17;
  (*(void (**)(char *, int, int *, EquipUI *))(v5 + 16))(&this->UIFrameWnd[528], 161, &v49, this);
  (gbRefObject **->CreateFromTemplate()&this->UIFrameWnd[528], aUiGamemainuiCo_23, byte_5CEFA8);
  v53[1] = 14;
  v53[0] = 626;
  v53[2] = 674;
  v53[3] = 68;
  v6 = "UI\\GameMainUI\\State\\State0.tga";
  v7 = (gbRefObject **)((char *)this + 174080);
  do
  {
    ((void (*)(gbRefObject **, int, _DWORD *, EquipUI *))(*v7)[4].RefCount)(v7, 161, v53, this);
    v7->CreateFromTemplate(v6, byte_5CEFA8);
    ((void (*)(gbRefObject **, _DWORD))(*v7)->RefCount)(v7, 0);
    v6 += 256;
    v7 += 38;
  }
  while ( (int)v6 < (int)"UI\\GameMainUI\\State\\Portrait0.tga" );
  v8 = *(_DWORD *)&this->UIFrameWnd[680];
  v44 = v51 - 205;
  v46 = v51 - 205 + 203;
  v45 = 0;
  v47 = 64;
  (*(void (**)(char *, int, int *, EquipUI *))(v8 + 16))(&this->UIFrameWnd[680], 161, &v44, this);
  (gbRefObject **->CreateFromTemplate()&this->UIFrameWnd[680], aUiGamemainuiCo_19, byte_5CEFA8);
  v9 = *(_DWORD *)&this->UIFrameWnd[4704];
  v45 = -4;
  v44 = 618;
  v46 = 738;
  v47 = 28;
  (*(void (**)(char *, int, int *, EquipUI *))(v9 + 16))(&this->UIFrameWnd[4704], 161, &v44, this);
  &this->UIFrameWnd[4704]->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v42 + 1) = -5;
    LOBYTE(v42) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v42 + 1) = 8187;
    LOBYTE(v42) = -1;
  }
  HIBYTE(v42) = -1;
  &this->UIFrameWnd[4704]->GetChild(&v42);
  v10 = *(_DWORD *)&this->UIFrameWnd[4552];
  v11 = &this->UIFrameWnd[4552];
  v45 = 16;
  v44 = 668;
  v46 = 748;
  v47 = 48;
  (*(void (**)(char *, int, int *, EquipUI *))(v10 + 16))(&this->UIFrameWnd[4552], 161, &v44, this);
  &this->UIFrameWnd[4552]->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v43 + 1) = -5;
    LOBYTE(v43) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v43 + 1) = 8187;
    LOBYTE(v43) = -1;
  }
  HIBYTE(v43) = -1;
  &this->UIFrameWnd[4552]->GetChild(&v43);
  sub_4A26D0((int)this);
  memset(v48, 0, 12);
  v48[3] = 32;
  sub_4A2BD0((int)this, (int)v11, (int)this, 0, v48, v27, v37);
  sub_4A2BD0((int)this, (int)v11, (int)this, 1, v48, v28, v38);
  sub_4A2BD0((int)this, (int)v11, (int)this, 2, v48, v29, v39);
  sub_4A2BD0((int)this, (int)v11, (int)this, 3, v48, v30, v40);
  sub_4A2BD0((int)this, (int)v11, (int)this, 4, v48, v31, v41);
  sub_4A2F90((int)this, 0, (int)v6, 0, (int)v48, v32);
  sub_4A2F90((int)this, 0, (int)v6, 1, (int)v48, v33);
  sub_4A2F90((int)this, 0, (int)v6, 2, (int)v48, v34);
  sub_4A2F90((int)this, 0, (int)v6, 3, (int)v48, v35);
  sub_4A2F90((int)this, 0, (int)v6, 4, (int)v48, v36);
  *((_BYTE *)this + 176089) = 0;
  *((_BYTE *)this + 176088) = byte_5CEFA9;
  v12 = operator new(0x29CECu);
  v42 = v12;
  v54 = 0;
  if ( v12 )
    v13 = v12->ctor_2ED0();
  else
    v13 = 0;
  v54 = -1;
  *((_DWORD *)this + 44014) = v13;
  v14 = operator new(0x56630u);
  v42 = v14;
  v54 = 1;
  if ( v14 )
    v15 = v14->ctor_67F0();
  else
    v15 = 0;
  v54 = -1;
  *((_DWORD *)this + 44015) = v15;
  v16 = operator new(0x35B50u);
  v42 = v16;
  v54 = 2;
  if ( v16 )
    v17 = v16->ctor_9F0();
  else
    v17 = 0;
  v54 = -1;
  *((_DWORD *)this + 44016) = v17;
  v18 = operator new(0x41014u);
  v42 = v18;
  v54 = 3;
  if ( v18 )
    v19 = v18->ctor_8820();
  else
    v19 = 0;
  v54 = -1;
  *((_DWORD *)this + 44017) = v19;
  v20 = operator new(0x62588u);
  v42 = v20;
  v54 = 4;
  if ( v20 )
    v21 = v20->ctor_6F10();
  else
    v21 = 0;
  v54 = -1;
  *((_DWORD *)this + 44018) = v21;
  v22 = operator new(0x27BD4u);
  v42 = v22;
  v54 = 5;
  if ( v22 )
    v23 = v22->ctor_E5C0();
  else
    v23 = 0;
  v54 = -1;
  *((_DWORD *)this + 44019) = v23;
  v24 = operator new(0x46EB8u);
  v42 = v24;
  v54 = 6;
  if ( v24 )
    v25 = v24->ctor_1D0();
  else
    v25 = 0;
  v26 = *((_DWORD *)this + 44014);
  v54 = -1;
  *((_DWORD *)this + 44020) = v25;
  sub_483650(v26, (int)this);
  sub_48D5D0(*((_DWORD *)this + 44015), (int)this);
  sub_496190(*((_DWORD *)this + 44016), (int)this);
  sub_49F2E0(*((_DWORD *)this + 44017), (int)v6, (int)this);
  sub_4AB6B0(*((_DWORD *)this + 44018), (int)this);
  sub_47F590(*((_DWORD *)this + 44019), (int)this);
  sub_4B0820(*((_DWORD *)this + 44020), (int)this);
  byte_DE5F92 = 0;
  byte_DE5F93 = 0;
  this->UIFrameWnd[373] = 1;
}

// 0x004A48B0
void EquipUI::InitSlots()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( (UIBase *->GetSelected()this) < 5 )
  {
    this->UIFrameWnd[361] = data;
    (UIBase *->SetItemData()this, 0, data);
    sub_48A2F0(*((char **)this + 44015), data);
    sub_4945C0(*((char **)this + 44016), data);
    sub_49E840(*((char **)this + 44017), data);
    sub_484E70(*((char **)this + 44014), data);
  }
  else
  {
    this->UIFrameWnd[361] = 0;
    (UIBase *->SetItemData()this, 0, 0);
    sub_48A2F0(*((char **)this + 44015), 0);
    sub_4945C0(*((char **)this + 44016), 0);
    sub_49E840(*((char **)this + 44017), 0);
    sub_484E70(*((char **)this + 44014), 0);
  }
}
