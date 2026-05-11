#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/EquipUI.h"
#include "pal3/gen/MagicUI.h"
#include "pal3/gen/MvcViewport.h"
#include "pal3/gen/Object3D.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/PropUI.h"
#include "pal3/gen/StateUI.h"
#include "pal3/gen/TextureLib.h"
#include "pal3/gen/UIBigDialog.h"
#include "pal3/gen/UIDialog.h"
#include "pal3/gen/UIItem.h"
#include "pal3/gen/UISelectDialog.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_43A5D0(...);
int sub_43AFA0(...);
int sub_4573A0(...);

// Unnamed globals (extern)
extern char aUiDlgHeadbkTga[];
extern char aUiDlgSelbkTga[];
extern char aUiUilib[];
extern char aUiUilibUiOptTl[];
extern unsigned char byte_DD8F3C;
extern unsigned char byte_DD903C;
extern unsigned char byte_DD913C;
extern int dword_8ACD40;
extern void *off_59BA88;
extern void *off_59BA8C;
extern void *off_59BA90;
extern void *off_59BA94;
extern int unk_AABEF6;
extern int unk_AABEF7;
extern int unk_AABEF8;
extern int unk_AABEF9;
extern int unk_ABCD01;
extern int unk_ABCD02;
extern int unk_ABCD03;
extern int unk_ABD000;

// 0x0044ADE0
int CGameData::InitRoles(int a2)
{
  int d06C; // ecx
  int d070; // eax
  int d07C; // edx
  UIWnd **v6; // edi
  int result; // eax
  int a3; // [esp+84h] [ebp-10h] BYREF
  int v9; // [esp+88h] [ebp-Ch]
  int v10; // [esp+8Ch] [ebp-8h]
  int v11; // [esp+90h] [ebp-4h]
  int a2a; // [esp+98h] [ebp+4h]

  this->_d050 = 0;
  this->_d04C = 0;
  this->_d054 = 800;
  this->_d058 = 600;
  ((UIWnd *)this)->Create((int)&unk_AABEF6, &this->_d04C, a2);
  d06C = this->_d06C;
  d070 = this->_d070;
  d07C = this->_d07C;
  this->_d060 = d070;
  this->_d05C = d06C;
  this->_d064 = d06C + 68;
  this->_d068 = d070 + 32;
  (*(void (**)(int *, void *, int *, CGameData *))(d07C + 16))(&this->_d07C, &unk_AABEF6, &this->_d05C, this);
  ((UIWnd *)&this->_d07C)->CreateFromTemplate(off_59BA88, 1);
  (*(void (**)(int *, _DWORD))this->_d07C)(&this->_d07C, 0);
  v6 = (UIWnd **)&this->_pad_118[148];
  a2a = 3;
  do
  {
    ((void (*)(UIWnd **, void *, int *, CGameData *))(*v6)->m_rect_left)(v6, &unk_AABEF6, &this->_d05C, this);
    v6->CreateFromTemplate(off_59BA90, 1);
    ((void (*)(UIWnd **, _DWORD))(*v6)->_vftable)(v6, 0);
    v6 += 38;
    --a2a;
  }
  while ( a2a );
  (*(void (**)(int *, void *, int *, CGameData *))(this->_d114 + 16))(
    &this->_d114,
    &unk_AABEF6,
    &this->_d05C,
    this);
  ((UIWnd *)&this->_d114)->CreateFromTemplate(off_59BA8C, 1);
  (*(void (**)(int *, _DWORD))this->_d114)(&this->_d114, 0);
  (*(void (**)(int *, void *, int *, CGameData *, char *, _DWORD, int))(this->_d374 + 28))(
    &this->_d374,
    &unk_AABEF7,
    &this->_d05C,
    this,
    off_59BA94,
    0,
    1);
  sub_43AFA0((char *)&this->_d374, byte_DD8F3C);
  this->_d3DC = 0;
  this->_d3E0 = 2;
  (*(void (**)(int *, _DWORD))this->_d374)(&this->_d374, 0);
  (*(void (**)(int *, void *, int *, CGameData *, char *, _DWORD, int))(this->_d4CC + 28))(
    &this->_d4CC,
    &unk_AABEF8,
    &this->_d05C,
    this,
    off_59BA94,
    0,
    1);
  sub_43AFA0((char *)&this->_d4CC, byte_DD903C);
  this->_d534 = 0;
  this->_d538 = 2;
  (*(void (**)(int *, _DWORD))this->_d4CC)(&this->_d4CC, 0);
  (*(void (**)(int *, void *, int *, CGameData *, char *, _DWORD, int))(this->_d624 + 28))(
    &this->_d624,
    &unk_AABEF9,
    &this->_d05C,
    this,
    off_59BA94,
    0,
    1);
  sub_43AFA0((char *)&this->_d624, byte_DD913C);
  this->_d68C = 0;
  this->_d690 = 2;
  (*(void (**)(int *, _DWORD))this->_d624)(&this->_d624, 0);
  v9 = 200;
  a3 = 300;
  v10 = 600;
  v11 = 456;
  ((UIItem *)&this->_pad_694[232])->Create((int)&unk_ABD000, (int)&a3);
  ((UIItem *)&this->_pad_694[232])->SetData(31);
  v10 = a3 + 256;
  v11 = v9 + 128;
  ((UIItem *)&this->_pad_CDC[16])->Create((int)&unk_ABCD01, (int)&a3);
  ((UIItem *)&this->_pad_CDC[16])->SetData(31);
  ((UIItem *)(UIItem *)this + 4676)->Create((int)&unk_ABCD02, (int)&a3);
  ((UIItem *)(UIItem *)this + 4676)->SetData(18);
  ((UIItem *)(UIItem *)this + 6044)->Create((int)&unk_ABCD03, (int)&a3);
  result = (int)((UIItem *)(UIItem *)this + 6044)->SetData(31);
  *((_DWORD *)this + 2373) = 0;
  *((_DWORD *)this + 2372) = 0;
  *((_DWORD *)this + 2374) = 0;
  *((_DWORD *)this + 2375) = 0;
  *((_DWORD *)this + 2376) = 0;
  *((_DWORD *)this + 2377) = 0;
  this->_pad_8D8[1020] = 0;
  *((_BYTE *)this + 7416) = 0;
  *((_DWORD *)this + 1853) = 0;
  this->_pad_CDC[12] = 0;
  this->_pad_CDC[13] = 0;
  this->_dCD8 = 0;
  *((_BYTE *)this + 9512) = 0;
  return result;
}

// 0x0044E660
int CGameData::InitItems(int a2)
{
  int v3; // edi
  int *v4; // ebp
  UIWnd *v5; // esi
  int v6; // eax
  UIWnd **v8; // [esp+10h] [ebp-1B4h]
  _DWORD pRect[2]; // [esp+14h] [ebp-1B0h] BYREF
  int v10; // [esp+1Ch] [ebp-1A8h]
  int v11; // [esp+20h] [ebp-1A4h]
  int v12; // [esp+24h] [ebp-1A0h]
  _DWORD v13[15]; // [esp+28h] [ebp-19Ch] BYREF
  _DWORD v14[23]; // [esp+64h] [ebp-160h] BYREF
  char Buffer[260]; // [esp+C0h] [ebp-104h] BYREF

  pRect[1] = 0;
  pRect[0] = 0;
  v11 = 600;
  v10 = 800;
  ((UIWnd *)this)->Create(0, pRect, a2);
  memset32(&this->_pad_694[536], 3, 0xDu);
  v14[8] = 32;
  v14[0] = 54;
  v14[7] = 54;
  v14[15] = 54;
  v14[16] = 32;
  v13[0] = 6;
  v13[1] = 10;
  v13[2] = 10;
  v13[10] = 6;
  v3 = 1;
  v14[3] = 31;
  v14[9] = 31;
  v14[21] = 0;
  v14[22] = 0;
  v12 = 0;
  memset(&v13[11], 0, 12);
  this->_d8B4 = 1;
  this->_d8B8 = 1;
  this->_d8C8 = 1;
  this->_d8D4 = 1;
  v13[14] = 38;
  v14[1] = 25;
  v14[2] = 57;
  v14[4] = 43;
  v14[5] = 82;
  v14[6] = 51;
  v14[10] = 41;
  v14[11] = 16;
  v14[12] = 111;
  v14[13] = 64;
  v14[14] = 46;
  v14[17] = 49;
  v14[18] = 40;
  v14[19] = 70;
  v14[20] = 42;
  v13[3] = 3;
  v13[4] = 2;
  v13[5] = 4;
  v13[6] = 7;
  v13[7] = 3;
  v13[8] = 2;
  v13[9] = 8;
  v8 = (UIWnd **)v13;
  v4 = v14;
  v5 = (UIWnd *)&this->_pad_080[116];
  do
  {
    (*((void (**)(UIWnd *, _DWORD, _DWORD *, CGameData *))v5->_vftable + 4))(v5, 0, pRect, this);
    ((void (*)(UIWnd *, _DWORD))*v5->_vftable)(v5, 0);
    v6 = *(v4 - 1);
    v11 = *v4;
    v10 = v6;
    v5->GetRect(pRect);
    sprintf(Buffer, "ui\\EMOTE\\EM_%02d.tga", v3);
    sub_43A5D0((UIWnd **)v5, (int)Buffer, *v8);
    v5->SetController(1084227584);
    ++v3;
    v4 += 2;
    v5 = (UIWnd *)((char *)v5 + 164);
    ++v8;
  }
  while ( v3 < 13 );
  return (**(int (***)(CGameData *, _DWORD))this->_pad_000)(this, 0);
}

// 0x0044F130
void * CGameData::Init()
{
  PropUI *v2; // eax
  PropUI *v3; // eax
  EquipUI *v4; // eax
  EquipUI *v5; // eax
  Object3D *v6; // eax
  Object3D *v7; // eax
  CGameData *v8; // edi
  int v9; // ebp
  char *v10; // ebp
  UIDialog *v11; // edi
  int d104; // edx
  OpenBaseFile v14; // [esp+18h] [ebp-24h] BYREF
  void *v15; // [esp+1Ch] [ebp-20h]
  int pRect; // [esp+20h] [ebp-1Ch] BYREF
  int v17; // [esp+24h] [ebp-18h]
  int v18; // [esp+28h] [ebp-14h]
  int v19; // [esp+2Ch] [ebp-10h]
  int v20; // [esp+38h] [ebp-4h]

  v17 = 0;
  pRect = 0;
  v18 = 800;
  v19 = 600;
  ((UIWnd *)this)->Create(0, &pRect, 0);
  ((OpenBaseFile *)&v14)->OpenBaseFile();
  v20 = 0;
  ((TextureLib *)&g_PlayerBase)->SetPath(aUiUilib);
  ((TextureLib *)&g_PlayerBase)->LoadFromFile(aUiUilibUiOptTl);
  v2 = (PropUI *)operator new(0xB30u);
  v15 = v2;
  LOBYTE(v20) = 1;
  if ( v2 )
    v3 = (PropUI *)v2->Create();
  else
    v3 = 0;
  LOBYTE(v20) = 0;
  *((_DWORD *)this + 7044) = v3;
  v3->Init();
  v4 = (EquipUI *)operator new(0x2B080u);
  v15 = v4;
  LOBYTE(v20) = 2;
  if ( v4 )
    v5 = (EquipUI *)v4->Create();
  else
    v5 = 0;
  LOBYTE(v20) = 0;
  *((_DWORD *)this + 7045) = v5;
  v5->Init();
  ((EquipUI *)*((EquipUI **)this + 7045))->InitSlots();
  ((StateUI *)*((StateUI **)this + 7045))->Create();
  ((StateUI *)*((StateUI **)this + 7045))->Init();
  ((MagicUI *)*((MagicUI **)this + 7045))->Init();
  ((MagicUI *)*((MagicUI **)this + 7045))->Create();
  v6 = (Object3D *)operator new(0xEF8u);
  v15 = v6;
  LOBYTE(v20) = 3;
  if ( v6 )
    v7 = (Object3D *)v6->Create();
  else
    v7 = 0;
  LOBYTE(v20) = 0;
  *((_DWORD *)this + 7046) = v7;
  v7->Init();
  v8 = (CGameData *)((char *)this + 14544);
  v9 = 6;
  do
  {
    v8->InitItems((int)this);
    v8 = (CGameData *)((char *)v8 + 2272);
    --v9;
  }
  while ( v9 );
  v17 = v19 - 150;
  v18 = pRect + 800;
  ((UIBigDialog *)&this->_dF40)->Create(1001, &pRect, 0, tex);
  (*(void (**)(int *, _DWORD))this->_dF40)(&this->_dF40, 0);
  v10 = (char *)&g_SceneMgr._gap_1888[808];
  v11 = (UIDialog *)&this->_pad_694[460];
  do
  {
    v11->Create(1002, 180, 50, (int)this, aUiDlgHeadbkTga);
    v11->Show();
    ((void (*)(UIDialog *, _DWORD))*v11->_base._vftable)(v11, 0);
    v10 += 8704;
    v11 = (UIDialog *)((char *)v11 + 352);
  }
  while ( (int)v10 < (int)&g_SceneMgr.m_RoleSystem[4]._pad_11CC[4116] );
  pRect = 0;
  v18 = 414;
  v17 = 0;
  v19 = 125;
  ((UISelectDialog *)&this->_pad_118[376])->Create(1011, &pRect, (int)this, aUiDlgSelbkTga);
  ((UIWnd *)&this->_pad_118[376])->SetVisible(0);
  ((UIDialog *)&this->_pad_118[76])->Init();
  ((CGameData *)((char *)this + 5012))->InitRoles((int)this);
  *((_DWORD *)this + 3632) = 3;
  memset(&this->_pad_000[68], 0, 0x24u);
  LOWORD(this->_d068) = 0;
  memset(&this->_pad_080[92], 0, 0x24u);
  *(_WORD *)&this->_pad_080[128] = 0;
  d104 = this->_d104;
  this->_pad_118[360] = 0;
  this->_pad_118[361] = 0;
  this->_pad_118[362] = 0;
  pRect = 0;
  v18 = 760;
  v17 = 50;
  v19 = 600;
  (*(void (**)(int *, _DWORD, int *, CGameData *))(d104 + 16))(&this->_d104, 0, &pRect, this);
  (*(void (**)(int *, _DWORD))this->_d104)(&this->_d104, 0);
  v20 = -1;
  return ((OpenNULLFile *)&v14)->OpenNULLFile();
}

// 0x0044F430
void CGameData::Destroy()
{
  int v2; // ecx
  int v3; // ecx
  int v4; // eax
  int v5; // ecx

  ((UIWnd *)this)->UpdateChildren();
  sub_4573A0(dword_8ACD40);
  (*(void (**)(int *))(this->_dF40 + 12))(&this->_dF40);
  v2 = *((_DWORD *)this + 7044);
  if ( v2 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v2 + 20))(v2, 1);
    *((_DWORD *)this + 7044) = 0;
  }
  v3 = *((_DWORD *)this + 7045);
  if ( v3 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *((_DWORD *)this + 7045) = 0;
  }
  v4 = *((_DWORD *)this + 3634);
  if ( v4 != 6 && v4 && v4 != 5 )
  {
    v5 = *((_DWORD *)this + 3633);
    if ( v5 )
      (*(void (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *((_DWORD *)this + 3633) = 0;
  }
}

// 0x0044F5B0
int CGameData::Render()
{
  _BYTE *v2; // ecx
  int result; // eax

  (*(void (**)(_DWORD))(**((_DWORD **)this + 3633) + 4))(*((_DWORD *)this + 3633));
  if ( *((_DWORD *)this + 3634) == 12 )
    (*(void (**)(_DWORD))(**((_DWORD **)this + 7044) + 4))(*((_DWORD *)this + 7044));
  v2 = (_BYTE *)*((_DWORD *)this + 7046);
  if ( v2 && v2[3829] )
    (*(void (**)(_BYTE *))(*(_DWORD *)v2 + 4))(v2);
  ((UIWnd *)this)->GetID();
  result = *((_DWORD *)this + 3634);
  if ( !result )
    return (*(int (**)(int *))(this->_dF40 + 4))(&this->_dF40);
  return result;
}

// 0x0044F8A0
int CGameData::SetMode(int mode)
{
  if ( !mode )
    return *((_DWORD *)this + 7044);
  if ( mode == 5 )
    return *((_DWORD *)this + 7045);
  return *((_DWORD *)this + 3633);
}

// 0x0044FF60
int CGameData::GetMode()
{
  return *((_DWORD *)this + 3635);
}
