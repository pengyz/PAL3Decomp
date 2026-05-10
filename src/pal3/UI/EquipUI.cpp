#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/EquipUI.h"
#include "pal3/gen/UIBase.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIWnd.h"

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
  ((UIListBox *)this)->UIListBox();
  this->_d058 = 800;
  this->_d05C = 600;
  this->_d060 = 0;
  this->_d064 = 0;
  this->_b168 = 0;
  this->_d170 = 0;
  this->_b174 = 0;
  this->_b175 = 0;
  ((UIFrameWnd *)&this->_d178)->UIFrameWnd();
  ((UIFrameWnd *)&this->_d210)->UIFrameWnd();
  ((UIFrameWnd *)&this->_d2A8)->UIFrameWnd();
  ((UIFrameWnd *)&this->_tail[148])->UIFrameWnd();
  ((UIFrameWnd *)&this->_tail[300])->UIFrameWnd();
  ((UIFrameWnd *)&this->_tail[452])->UIFrameWnd();
  ((UIScene *)&this->_tail[604])->_UIScene();
  ((UIScene *)&this->_tail[948])->_UIScene();
  ((UIScene *)&this->_tail[1292])->_UIScene();
  ((UIScene *)&this->_tail[1636])->_UIScene();
  ((UIScene *)&this->_tail[1980])->_UIScene();
  ((UIScene *)&this->_tail[2324])->_UIScene();
  ((UIScene *)&this->_tail[2668])->_UIScene();
  ((UIScene *)&this->_tail[3012])->_UIScene();
  ((UIScene *)&this->_tail[3356])->_UIScene();
  ((UIFrameWnd *)((char *)this + 4384))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4552))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4704))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 4856,
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 79608,
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  ((UIFrameWnd *)((char *)this + 154516))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154668))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154820))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154972))->UIFrameWnd();
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
  ((UIFrameWnd *)((char *)this + 174688))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 174856,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)((char *)this + 175696))->_UIScene();
  *((_DWORD *)this + 44014) = 0;
  *((_DWORD *)this + 44015) = 0;
  *((_DWORD *)this + 44016) = 0;
  *((_DWORD *)this + 44017) = 0;
  *((_DWORD *)this + 44018) = 0;
  *((_DWORD *)this + 44019) = 0;
  *((_DWORD *)this + 44020) = 0;
  *((_DWORD *)this + 44021) = 0;
  ((UIFrameWnd *)((char *)this + 176092))->UIFrameWnd();
  this->_p000 = &off_56F040;
  this->_b16D = 0;
  this->_b16C = 0;
  this->_b16A = 0;
  this->_b169 = 0;
  this->_b16B = 0;
  *((_DWORD *)this + 38622) = 0;
  *((_DWORD *)this + 38623) = 0;
  *((_DWORD *)this + 38624) = 0;
  *((_DWORD *)this + 44061) = 0;
  return (int)this;
}

// 0x004A4220
void EquipUI::Init()
{
  int d058; // eax
  int d05C; // ecx
  int v4; // eax
  int d210; // edx
  const CHAR *v6; // ebp
  UIWnd **v7; // edi
  int d2A8; // edx
  int v9; // eax
  int v10; // edx
  char *v11; // edi
  UIWnd *v12; // eax
  int v13; // eax
  UIWnd *v14; // eax
  int v15; // eax
  UIWnd *v16; // eax
  int v17; // eax
  UIWnd *v18; // eax
  int v19; // eax
  UIWnd *v20; // eax
  int v21; // eax
  UIWnd *v22; // eax
  int v23; // eax
  UIWnd *v24; // eax
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
  int id; // [esp+4Ch] [ebp-54h] BYREF
  char v43; // [esp+50h] [ebp-50h] BYREF
  __int16 v44; // [esp+51h] [ebp-4Fh]
  char v45; // [esp+53h] [ebp-4Dh]
  int v46; // [esp+54h] [ebp-4Ch] BYREF
  int v47; // [esp+58h] [ebp-48h]
  int v48; // [esp+5Ch] [ebp-44h]
  int v49; // [esp+60h] [ebp-40h]
  int v50[4]; // [esp+64h] [ebp-3Ch] BYREF
  int v51; // [esp+74h] [ebp-2Ch] BYREF
  int v52; // [esp+78h] [ebp-28h]
  int v53; // [esp+7Ch] [ebp-24h]
  int v54; // [esp+80h] [ebp-20h]
  _DWORD v55[4]; // [esp+84h] [ebp-1Ch] BYREF
  int v56; // [esp+9Ch] [ebp-4h]

  d058 = this->_d058;
  d05C = this->_d05C;
  this->_d050 = d058;
  this->_d04C = 0;
  this->_d048 = 0;
  this->_d054 = d05C;
  ((UIListBox *)this)->SetSelTexture(-1, this->_d048, this->_d04C, this->_d050, this->_d054, 0);
  v4 = this->_d04C + 18;
  v51 = this->_d048 + 592;
  v52 = v4;
  v53 = v51 + 192;
  v54 = v4 + 526;
  (*(void (**)(int *, int, int *, EquipUI *))(this->_d178 + 16))(&this->_d178, 161, &v51, this);
  ((UIWnd *)&this->_d178)->CreateFromTemplate(aUiGamemainuiSt_1, byte_5CEFA8);
  d210 = this->_d210;
  v52 += 26;
  v51 = v53;
  v54 = v52 + 526;
  v53 += 17;
  (*(void (**)(int *, int, int *, EquipUI *))(d210 + 16))(&this->_d210, 161, &v51, this);
  ((UIWnd *)&this->_d210)->CreateFromTemplate(aUiGamemainuiCo_23, byte_5CEFA8);
  v55[1] = 14;
  v55[0] = 626;
  v55[2] = 674;
  v55[3] = 68;
  v6 = (const CHAR *)"UI\\GameMainUI\\State\\State0.tga";
  v7 = (UIWnd **)this + 43520;
  do
  {
    ((void (*)(UIWnd **, int, _DWORD *, EquipUI *))(*v7)->m_wndcolor.ColorQuadFmt)(v7, 161, v55, this);
    v7->CreateFromTemplate(v6, byte_5CEFA8);
    (*(void (**)(UIWnd **, _DWORD))(*v7)->_pad_0000)(v7, 0);
    v6 += 256;
    v7 += 38;
  }
  while ( (int)v6 < (int)"UI\\GameMainUI\\State\\Portrait0.tga" );
  d2A8 = this->_d2A8;
  v46 = v53 - 205;
  v48 = v53 - 205 + 203;
  v47 = 0;
  v49 = 64;
  (*(void (**)(int *, int, int *, EquipUI *))(d2A8 + 16))(&this->_d2A8, 161, &v46, this);
  ((UIWnd *)&this->_d2A8)->CreateFromTemplate(aUiGamemainuiCo_19, byte_5CEFA8);
  v9 = *((_DWORD *)this + 1176);
  v47 = -4;
  v46 = 618;
  v48 = 738;
  v49 = 28;
  (*(void (**)(char *, int, int *, EquipUI *))(v9 + 16))((char *)this + 4704, 161, &v46, this);
  ((UIWnd *)(UIWnd *)this + 56)->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&id + 1) = -5;
    LOBYTE(id) = 31;
  }
  else
  {
    *(_WORD *)((char *)&id + 1) = 8187;
    LOBYTE(id) = -1;
  }
  HIBYTE(id) = -1;
  ((UIWnd *)(UIWnd *)this + 56)->GetChild((int)&id);
  v10 = *((_DWORD *)this + 1138);
  v11 = (char *)this + 4552;
  v47 = 16;
  v46 = 668;
  v48 = 748;
  v49 = 48;
  (*(void (**)(char *, int, int *, EquipUI *))(v10 + 16))((char *)this + 4552, 161, &v46, this);
  ((UIWnd *)((char *)this + 4552))->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    v44 = -5;
    v43 = 31;
  }
  else
  {
    v44 = 8187;
    v43 = -1;
  }
  v45 = -1;
  ((UIWnd *)((char *)this + 4552))->GetChild((int)&v43);
  sub_4A26D0((int)this);
  memset(v50, 0, 12);
  v50[3] = 32;
  sub_4A2BD0((int)this, (int)v11, (int)this, 0, v50, v27, v37);
  sub_4A2BD0((int)this, (int)v11, (int)this, 1, v50, v28, v38);
  sub_4A2BD0((int)this, (int)v11, (int)this, 2, v50, v29, v39);
  sub_4A2BD0((int)this, (int)v11, (int)this, 3, v50, v30, v40);
  sub_4A2BD0((int)this, (int)v11, (int)this, 4, v50, v31, v41);
  sub_4A2F90((int)this, 0, (int)v6, 0, (int)v50, v32);
  sub_4A2F90((int)this, 0, (int)v6, 1, (int)v50, v33);
  sub_4A2F90((int)this, 0, (int)v6, 2, (int)v50, v34);
  sub_4A2F90((int)this, 0, (int)v6, 3, (int)v50, v35);
  sub_4A2F90((int)this, 0, (int)v6, 4, (int)v50, v36);
  *((_BYTE *)this + 176089) = 0;
  *((_BYTE *)this + 176088) = byte_5CEFA9;
  v12 = (UIWnd *)operator new(0x29CECu);
  id = (int)v12;
  v56 = 0;
  if ( v12 )
    v13 = v12->ctor_2ED0();
  else
    v13 = 0;
  v56 = -1;
  *((_DWORD *)this + 44014) = v13;
  v14 = (UIWnd *)operator new(0x56630u);
  id = (int)v14;
  v56 = 1;
  if ( v14 )
    v15 = v14->ctor_67F0();
  else
    v15 = 0;
  v56 = -1;
  *((_DWORD *)this + 44015) = v15;
  v16 = (UIWnd *)operator new(0x35B50u);
  id = (int)v16;
  v56 = 2;
  if ( v16 )
    v17 = v16->ctor_9F0();
  else
    v17 = 0;
  v56 = -1;
  *((_DWORD *)this + 44016) = v17;
  v18 = (UIWnd *)operator new(0x41014u);
  id = (int)v18;
  v56 = 3;
  if ( v18 )
    v19 = v18->ctor_8820();
  else
    v19 = 0;
  v56 = -1;
  *((_DWORD *)this + 44017) = v19;
  v20 = (UIWnd *)operator new(0x62588u);
  id = (int)v20;
  v56 = 4;
  if ( v20 )
    v21 = v20->ctor_6F10();
  else
    v21 = 0;
  v56 = -1;
  *((_DWORD *)this + 44018) = v21;
  v22 = (UIWnd *)operator new(0x27BD4u);
  id = (int)v22;
  v56 = 5;
  if ( v22 )
    v23 = v22->ctor_E5C0();
  else
    v23 = 0;
  v56 = -1;
  *((_DWORD *)this + 44019) = v23;
  v24 = (UIWnd *)operator new(0x46EB8u);
  id = (int)v24;
  v56 = 6;
  if ( v24 )
    v25 = v24->ctor_1D0();
  else
    v25 = 0;
  v26 = *((_DWORD *)this + 44014);
  v56 = -1;
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
  this->_b175 = 1;
}

// 0x004A48B0
void EquipUI::InitSlots()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( ((UIBase *)this)->GetSelected() < 5 )
  {
    this->_b169 = data;
    ((UIBase *)this)->SetItemData(0, data);
    sub_48A2F0(*((char **)this + 44015), data);
    sub_4945C0(*((char **)this + 44016), data);
    sub_49E840(*((char **)this + 44017), data);
    sub_484E70(*((char **)this + 44014), data);
  }
  else
  {
    this->_b169 = 0;
    ((UIBase *)this)->SetItemData(0, 0);
    sub_48A2F0(*((char **)this + 44015), 0);
    sub_4945C0(*((char **)this + 44016), 0);
    sub_49E840(*((char **)this + 44017), 0);
    sub_484E70(*((char **)this + 44014), 0);
  }
}
