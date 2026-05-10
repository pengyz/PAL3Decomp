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
int sub_4AB6B0(...);
int sub_4B0820(...);

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
  *(_DWORD *)&this->buf[8] = 800;
  *(_DWORD *)&this->buf[12] = 600;
  *(_DWORD *)&this->buf[16] = 0;
  *(_DWORD *)&this->buf[20] = 0;
  LOBYTE(this->j) = 0;
  *(_DWORD *)&this->_isCreatable = 0;
  LOBYTE(this->_flashSpeed) = 0;
  BYTE1(this->_flashSpeed) = 0;
  ((UIFrameWnd *)this->m_EquipData)->UIFrameWnd();
  ((UIFrameWnd *)&this->m_EquipData[152])->UIFrameWnd();
  ((UIFrameWnd *)&this->m_EquipData[304])->UIFrameWnd();
  ((UIFrameWnd *)&this->m_EquipData[456])->UIFrameWnd();
  ((UIFrameWnd *)&this->m_EquipData[608])->UIFrameWnd();
  ((UIFrameWnd *)&this->m_EquipData[760])->UIFrameWnd();
  ((UIScene *)&this->m_EquipData[912])->_UIScene();
  ((UIScene *)&this->m_EquipData[1256])->_UIScene();
  ((UIScene *)&this->m_EquipData[1600])->_UIScene();
  ((UIScene *)&this->m_EquipData[1944])->_UIScene();
  ((UIScene *)&this->m_EquipData[2288])->_UIScene();
  ((UIScene *)&this->m_EquipData[2632])->_UIScene();
  ((UIScene *)&this->m_EquipData[2976])->_UIScene();
  ((UIScene *)&this->m_EquipData[3320])->_UIScene();
  ((UIScene *)&this->m_EquipData[3664])->_UIScene();
  ((UIFrameWnd *)&this->m_EquipData[4008])->UIFrameWnd();
  ((UIFrameWnd *)&this->m_EquipData[4176])->UIFrameWnd();
  ((UIFrameWnd *)&this->m_EquipData[4328])->UIFrameWnd();
  `eh vector constructor iterator'(
    &this->m_EquipData[4480],
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    &this->m_ArrowRc[779],
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
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
  *(_DWORD *)this->_base = &off_56F040;
  BYTE1(this->k) = 0;
  LOBYTE(this->k) = 0;
  BYTE2(this->j) = 0;
  BYTE1(this->j) = 0;
  HIBYTE(this->j) = 0;
  *((_DWORD *)this + 38622) = 0;
  *((_DWORD *)this + 38623) = 0;
  *((_DWORD *)this + 38624) = 0;
  *((_DWORD *)this + 44061) = 0;
  return (int)this->_base;
}

// 0x004A4220
void EquipUI::Init()
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  const CHAR *v6; // ebp
  UIWnd **v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // edx
  UIWnd *v11; // eax
  int v12; // eax
  UIWnd *v13; // eax
  int v14; // eax
  UIWnd *v15; // eax
  int v16; // eax
  UIWnd *v17; // eax
  int v18; // eax
  UIWnd *v19; // eax
  int v20; // eax
  UIWnd *v21; // eax
  int v22; // eax
  UIWnd *v23; // eax
  int v24; // eax
  int v25; // ecx
  int id; // [esp+4Ch] [ebp-54h] BYREF
  char v27; // [esp+50h] [ebp-50h] BYREF
  __int16 v28; // [esp+51h] [ebp-4Fh]
  char v29; // [esp+53h] [ebp-4Dh]
  int v30; // [esp+54h] [ebp-4Ch] BYREF
  int v31; // [esp+58h] [ebp-48h]
  int v32; // [esp+5Ch] [ebp-44h]
  int v33; // [esp+60h] [ebp-40h]
  int v34; // [esp+64h] [ebp-3Ch]
  int v35; // [esp+68h] [ebp-38h]
  int v36; // [esp+6Ch] [ebp-34h]
  int v37; // [esp+70h] [ebp-30h]
  int v38; // [esp+74h] [ebp-2Ch] BYREF
  int v39; // [esp+78h] [ebp-28h]
  int v40; // [esp+7Ch] [ebp-24h]
  int v41; // [esp+80h] [ebp-20h]
  _DWORD v42[4]; // [esp+84h] [ebp-1Ch] BYREF
  int v43; // [esp+9Ch] [ebp-4h]

  v2 = *(_DWORD *)&this->buf[8];
  v3 = *(_DWORD *)&this->buf[12];
  *(_DWORD *)this->buf = v2;
  this->bkWndY = 0;
  this->bkWndX = 0;
  *(_DWORD *)&this->buf[4] = v3;
  ((UIListBox *)this)->SetSelTexture(-1, this->bkWndX, this->bkWndY, *(_DWORD *)this->buf, *(_DWORD *)&this->buf[4], 0);
  v4 = this->bkWndY + 18;
  v38 = this->bkWndX + 592;
  v39 = v4;
  v40 = v38 + 192;
  v41 = v4 + 526;
  (*(void (**)(char *, int, int *, EquipUI *))(*(_DWORD *)this->m_EquipData + 16))(
    this->m_EquipData,
    161,
    &v38,
    this);
  ((UIWnd *)this->m_EquipData)->CreateFromTemplate(aUiGamemainuiSt_1, byte_5CEFA8);
  v5 = *(_DWORD *)&this->m_EquipData[152];
  v39 += 26;
  v38 = v40;
  v41 = v39 + 526;
  v40 += 17;
  (*(void (**)(char *, int, int *, EquipUI *))(v5 + 16))(&this->m_EquipData[152], 161, &v38, this);
  ((UIWnd *)&this->m_EquipData[152])->CreateFromTemplate(aUiGamemainuiCo_23, byte_5CEFA8);
  v42[1] = 14;
  v42[0] = 626;
  v42[2] = 674;
  v42[3] = 68;
  v6 = (const CHAR *)"UI\\GameMainUI\\State\\State0.tga";
  v7 = (UIWnd **)((char *)this + 174080);
  do
  {
    (*(void (**)(UIWnd **, int, _DWORD *, EquipUI *))(*v7)->m_rect)(v7, 161, v42, this);
    v7->CreateFromTemplate(v6, byte_5CEFA8);
    (*(void (**)(UIWnd **, _DWORD))(*v7)->_pad_000)(v7, 0);
    v6 += 256;
    v7 += 38;
  }
  while ( (int)v6 < (int)"UI\\GameMainUI\\State\\Portrait0.tga" );
  v8 = *(_DWORD *)&this->m_EquipData[304];
  v30 = v40 - 205;
  v32 = v40 - 205 + 203;
  v31 = 0;
  v33 = 64;
  (*(void (**)(char *, int, int *, EquipUI *))(v8 + 16))(&this->m_EquipData[304], 161, &v30, this);
  ((UIWnd *)&this->m_EquipData[304])->CreateFromTemplate(aUiGamemainuiCo_19, byte_5CEFA8);
  v9 = *(_DWORD *)&this->m_EquipData[4328];
  v31 = -4;
  v30 = 618;
  v32 = 738;
  v33 = 28;
  (*(void (**)(char *, int, int *, EquipUI *))(v9 + 16))(&this->m_EquipData[4328], 161, &v30, this);
  ((UIWnd *)&this->m_EquipData[4328])->SetShow(0);
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
  ((UIWnd *)&this->m_EquipData[4328])->GetChild((int)&id);
  v10 = *(_DWORD *)&this->m_EquipData[4176];
  v31 = 16;
  v30 = 668;
  v32 = 748;
  v33 = 48;
  (*(void (**)(char *, int, int *, EquipUI *))(v10 + 16))(&this->m_EquipData[4176], 161, &v30, this);
  ((UIWnd *)&this->m_EquipData[4176])->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    v28 = -5;
    v27 = 31;
  }
  else
  {
    v28 = 8187;
    v27 = -1;
  }
  v29 = -1;
  ((UIWnd *)&this->m_EquipData[4176])->GetChild((int)&v27);
  sub_4A26D0((int)this);
  v35 = 0;
  v34 = 0;
  v36 = 0;
  v37 = 32;
  UIWnd_GetChild((UIWnd *)this, 0);
  UIWnd_GetChild((UIWnd *)this, 1);
  UIWnd_GetChild((UIWnd *)this, 2);
  UIWnd_GetChild((UIWnd *)this, 3);
  UIWnd_GetChild((UIWnd *)this, 4);
  UIWnd_FindChild((UIWnd *)this, 0);
  UIWnd_FindChild((UIWnd *)this, 1);
  UIWnd_FindChild((UIWnd *)this, 2);
  UIWnd_FindChild((UIWnd *)this, 3);
  UIWnd_FindChild((UIWnd *)this, 4);
  *((_BYTE *)this + 176089) = 0;
  *((_BYTE *)this + 176088) = byte_5CEFA9;
  v11 = (UIWnd *)operator new(0x29CECu);
  id = (int)v11;
  v43 = 0;
  if ( v11 )
    v12 = v11->ctor_2ED0();
  else
    v12 = 0;
  v43 = -1;
  *((_DWORD *)this + 44014) = v12;
  v13 = (UIWnd *)operator new(0x56630u);
  id = (int)v13;
  v43 = 1;
  if ( v13 )
    v14 = v13->ctor_67F0();
  else
    v14 = 0;
  v43 = -1;
  *((_DWORD *)this + 44015) = v14;
  v15 = (UIWnd *)operator new(0x35B50u);
  id = (int)v15;
  v43 = 2;
  if ( v15 )
    v16 = v15->ctor_9F0();
  else
    v16 = 0;
  v43 = -1;
  *((_DWORD *)this + 44016) = v16;
  v17 = (UIWnd *)operator new(0x41014u);
  id = (int)v17;
  v43 = 3;
  if ( v17 )
    v18 = v17->ctor_8820();
  else
    v18 = 0;
  v43 = -1;
  *((_DWORD *)this + 44017) = v18;
  v19 = (UIWnd *)operator new(0x62588u);
  id = (int)v19;
  v43 = 4;
  if ( v19 )
    v20 = v19->ctor_6F10();
  else
    v20 = 0;
  v43 = -1;
  *((_DWORD *)this + 44018) = v20;
  v21 = (UIWnd *)operator new(0x27BD4u);
  id = (int)v21;
  v43 = 5;
  if ( v21 )
    v22 = v21->ctor_E5C0();
  else
    v22 = 0;
  v43 = -1;
  *((_DWORD *)this + 44019) = v22;
  v23 = (UIWnd *)operator new(0x46EB8u);
  id = (int)v23;
  v43 = 6;
  if ( v23 )
    v24 = v23->ctor_1D0();
  else
    v24 = 0;
  v25 = *((_DWORD *)this + 44014);
  v43 = -1;
  *((_DWORD *)this + 44020) = v24;
  sub_483650(v25, (int)this);
  sub_48D5D0(*((_DWORD *)this + 44015), (int)this);
  sub_496190(*((_DWORD *)this + 44016), (int)this);
  sub_49F2E0(*((_DWORD *)this + 44017), (int)v6, (int)this);
  sub_4AB6B0(*((_DWORD *)this + 44018), (int)this);
  sub_47F590(*((_DWORD *)this + 44019), (int)this);
  sub_4B0820(*((_DWORD *)this + 44020), (int)this);
  byte_DE5F92 = 0;
  byte_DE5F93 = 0;
  BYTE1(this->_flashSpeed) = 1;
}

// 0x004A48B0
void EquipUI::InitSlots()
{
  unsigned int data; // [esp+8h] [ebp+4h]

  if ( ((UIBase *)this)->GetSelected() < 5 )
  {
    BYTE1(this->j) = data;
    ((UIBase *)this)->SetItemData(0, data);
    sub_48A2F0(*((char **)this + 44015), data);
    sub_4945C0(*((char **)this + 44016), data);
    sub_49E840(*((char **)this + 44017), data);
    sub_484E70(*((char **)this + 44014), data);
  }
  else
  {
    BYTE1(this->j) = 0;
    ((UIBase *)this)->SetItemData(0, 0);
    sub_48A2F0(*((char **)this + 44015), 0);
    sub_4945C0(*((char **)this + 44016), 0);
    sub_49E840(*((char **)this + 44017), 0);
    sub_484E70(*((char **)this + 44014), 0);
  }
}
