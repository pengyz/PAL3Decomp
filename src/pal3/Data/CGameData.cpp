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
extern int dword_1894B78;
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
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  UIWnd **v6; // edi
  int result; // eax
  int a3; // [esp+84h] [ebp-10h] BYREF
  int v9; // [esp+88h] [ebp-Ch]
  int v10; // [esp+8Ch] [ebp-8h]
  int v11; // [esp+90h] [ebp-4h]
  int a2a; // [esp+98h] [ebp+4h]

  *(_DWORD *)&this->_data[80] = 0;
  *(_DWORD *)&this->_data[76] = 0;
  *(_DWORD *)&this->_data[84] = 800;
  *(_DWORD *)&this->_data[88] = 600;
  ((UIWnd *)this)->Create((int)&unk_AABEF6, &this->_data[76], a2);
  v3 = *(_DWORD *)&this->_data[108];
  v4 = *(_DWORD *)&this->_data[112];
  v5 = *(_DWORD *)&this->_data[124];
  *(_DWORD *)&this->_data[96] = v4;
  *(_DWORD *)&this->_data[92] = v3;
  *(_DWORD *)&this->_data[100] = v3 + 68;
  *(_DWORD *)&this->_data[104] = v4 + 32;
  (*(void (**)(char *, void *, char *, CGameData *))(v5 + 16))(
    &this->_data[124],
    &unk_AABEF6,
    &this->_data[92],
    this);
  ((UIWnd **)&this->_data[124])->CreateFromTemplate(off_59BA88, 1);
  (**(void (***)(char *, _DWORD))&this->_data[124])(&this->_data[124], 0);
  v6 = (UIWnd **)&this->_data[428];
  a2a = 3;
  do
  {
    ((void (*)(UIWnd **, void *, char *, CGameData *))(*v6)->m_fontcolor.Alpha)(
      v6,
      &unk_AABEF6,
      &this->_data[92],
      this);
    v6->CreateFromTemplate(off_59BA90, 1);
    ((void (*)(UIWnd **, _DWORD))(*v6)->m_fontcolor.ColorQuadFmt)(v6, 0);
    v6 += 38;
    --a2a;
  }
  while ( a2a );
  (*(void (**)(char *, void *, char *, CGameData *))(*(_DWORD *)&this->_data[276] + 16))(
    &this->_data[276],
    &unk_AABEF6,
    &this->_data[92],
    this);
  ((UIWnd **)&this->_data[276])->CreateFromTemplate(off_59BA8C, 1);
  (**(void (***)(char *, _DWORD))&this->_data[276])(&this->_data[276], 0);
  (*(void (**)(char *, void *, char *, CGameData *, char *, _DWORD, int))(*(_DWORD *)&this->_data[884] + 28))(
    &this->_data[884],
    &unk_AABEF7,
    &this->_data[92],
    this,
    off_59BA94,
    0,
    1);
  sub_43AFA0(&this->_data[884], byte_DD8F3C);
  *(_DWORD *)&this->_data[988] = 0;
  *(_DWORD *)&this->_data[992] = 2;
  (**(void (***)(char *, _DWORD))&this->_data[884])(&this->_data[884], 0);
  (*(void (**)(char *, void *, char *, CGameData *, char *, _DWORD, int))(*(_DWORD *)&this->_data[1228] + 28))(
    &this->_data[1228],
    &unk_AABEF8,
    &this->_data[92],
    this,
    off_59BA94,
    0,
    1);
  sub_43AFA0(&this->_data[1228], byte_DD903C);
  *(_DWORD *)&this->_data[1332] = 0;
  *(_DWORD *)&this->_data[1336] = 2;
  (**(void (***)(char *, _DWORD))&this->_data[1228])(&this->_data[1228], 0);
  (*(void (**)(char *, void *, char *, CGameData *, char *, _DWORD, int))(*(_DWORD *)&this->_data[1572] + 28))(
    &this->_data[1572],
    &unk_AABEF9,
    &this->_data[92],
    this,
    off_59BA94,
    0,
    1);
  sub_43AFA0(&this->_data[1572], byte_DD913C);
  *(_DWORD *)&this->_data[1676] = 0;
  *(_DWORD *)&this->_data[1680] = 2;
  (**(void (***)(char *, _DWORD))&this->_data[1572])(&this->_data[1572], 0);
  v9 = 200;
  a3 = 300;
  v10 = 600;
  v11 = 456;
  ((UIItem *)&this->_data[1916])->Create((int)&unk_ABD000, (int)&a3);
  ((UIItem *)&this->_data[1916])->SetData(31);
  v10 = a3 + 256;
  v11 = v9 + 128;
  ((UIItem *)&this->_data[3308])->Create((int)&unk_ABCD01, (int)&a3);
  ((UIItem *)&this->_data[3308])->SetData(31);
  ((UIItem *)&this->_data[4676])->Create((int)&unk_ABCD02, (int)&a3);
  ((UIItem *)&this->_data[4676])->SetData(18);
  ((UIItem *)&this->_data[6044])->Create((int)&unk_ABCD03, (int)&a3);
  result = (int)((UIItem *)&this->_data[6044])->SetData(31);
  *(_DWORD *)&this->_data[9492] = 0;
  *(_DWORD *)&this->_data[9488] = 0;
  *(_DWORD *)&this->_data[9496] = 0;
  *(_DWORD *)&this->_data[9500] = 0;
  *(_DWORD *)&this->_data[9504] = 0;
  *(_DWORD *)&this->_data[9508] = 0;
  this->_data[3284] = 0;
  this->_data[7416] = 0;
  *(_DWORD *)&this->_data[7412] = 0;
  this->_data[3304] = 0;
  this->_data[3305] = 0;
  *(_DWORD *)&this->_data[3288] = 0;
  this->_data[9512] = 0;
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
  memset32(&this->_data[2220], 3, 0xDu);
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
  *(_DWORD *)&this->_data[2228] = 1;
  *(_DWORD *)&this->_data[2232] = 1;
  *(_DWORD *)&this->_data[2248] = 1;
  *(_DWORD *)&this->_data[2260] = 1;
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
  v5 = (UIWnd *)&this->_data[244];
  do
  {
    (*(void (**)(UIWnd *, _DWORD, _DWORD *, CGameData *))(v5->m_fontcolor.ColorQuadFmt + 16))(
      v5,
      0,
      pRect,
      this);
    (*(void (**)(UIWnd *, _DWORD))v5->m_fontcolor.ColorQuadFmt)(v5, 0);
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
  return (**(int (***)(CGameData *, _DWORD))this->_data)(this, 0);
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
  float *p_y; // ebp
  UIDialog *v11; // edi
  int v12; // edx
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
  ((TextureLib *)dword_1894B78)->SetPath(aUiUilib);
  ((TextureLib *)dword_1894B78)->LoadFromFile(aUiUilibUiOptTl);
  v2 = (PropUI *)((operator *)0xB30u)->new();
  v15 = v2;
  LOBYTE(v20) = 1;
  if ( v2 )
    v3 = (PropUI *)v2->Create();
  else
    v3 = 0;
  LOBYTE(v20) = 0;
  *((_DWORD *)this + 7044) = v3;
  v3->Init();
  v4 = (EquipUI *)((operator *)0x2B080u)->new();
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
  v6 = (Object3D *)((operator *)0xEF8u)->new();
  v15 = v6;
  LOBYTE(v20) = 3;
  if ( v6 )
    v7 = (Object3D *)v6->Create();
  else
    v7 = 0;
  LOBYTE(v20) = 0;
  *((_DWORD *)this + 7046) = v7;
  v7->Init();
  v8 = (CGameData *)this + 1;
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
  ((UIBigDialog *)&this->_data[3904])->Create(1001, &pRect, 0, tex);
  (**(void (***)(char *, _DWORD))&this->_data[3904])(&this->_data[3904], 0);
  p_y = (float *)&g_SceneMgr.m_npc[0].m_path.normal[83].y;
  v11 = (UIDialog *)&this->_data[2144];
  do
  {
    v11->Create(1002, 180, 50, (int)this, aUiDlgHeadbkTga);
    v11->Show();
    (*(void (**)(UIDialog *, _DWORD))v11->m_fontcolor.ColorQuadFmt)(v11, 0);
    p_y += 2176;
    v11 = (UIDialog *)((char *)v11 + 352);
  }
  while ( (int)p_y < (int)&g_SceneMgr.m_npc[5].m_path.normal[58].y );
  pRect = 0;
  v18 = 414;
  v17 = 0;
  v19 = 125;
  ((UISelectDialog *)&this->_data[656])->Create(1011, &pRect, (int)this, aUiDlgSelbkTga);
  ((UIWnd *)&this->_data[656])->SetVisible(0);
  ((UIDialog *)&this->_data[356])->Init();
  ((CGameData *)&this->_data[5012])->InitRoles((int)this);
  *(_DWORD *)&this->_data[14528] = 3;
  memset(&this->_data[68], 0, 0x24u);
  *(_WORD *)&this->_data[104] = 0;
  memset(&this->_data[220], 0, 0x24u);
  *(_WORD *)&this->_data[256] = 0;
  v12 = *(_DWORD *)&this->_data[260];
  this->_data[640] = 0;
  this->_data[641] = 0;
  this->_data[642] = 0;
  pRect = 0;
  v18 = 760;
  v17 = 50;
  v19 = 600;
  (*(void (**)(char *, _DWORD, int *, CGameData *))(v12 + 16))(&this->_data[260], 0, &pRect, this);
  (**(void (***)(char *, _DWORD))&this->_data[260])(&this->_data[260], 0);
  v20 = -1;
  return ((OpenNULLFile **)&v14)->OpenNULLFile();
}

// 0x0044F430
void CGameData::Destroy()
{
  int v2; // ecx
  int v3; // ecx
  int v4; // eax
  int v5; // ecx

  ((UIWnd *)this)->UpdateChildren();
  sub_4573A0(&g_PAL3Data + 328);
  (*(void (**)(char *))(*(_DWORD *)&this->_data[3904] + 12))(&this->_data[3904]);
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
  v4 = *(_DWORD *)&this->_data[14536];
  if ( v4 != 6 && v4 && v4 != 5 )
  {
    v5 = *(_DWORD *)&this->_data[14532];
    if ( v5 )
      (*(void (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *(_DWORD *)&this->_data[14532] = 0;
  }
}

// 0x0044F5B0
int CGameData::Render()
{
  _BYTE *v2; // ecx
  int result; // eax

  (*(void (**)(_DWORD))(**(_DWORD **)&this->_data[14532] + 4))(*(_DWORD *)&this->_data[14532]);
  if ( *(_DWORD *)&this->_data[14536] == 12 )
    (*(void (**)(_DWORD))(**((_DWORD **)this + 7044) + 4))(*((_DWORD *)this + 7044));
  v2 = (_BYTE *)*((_DWORD *)this + 7046);
  if ( v2 && v2[3829] )
    (*(void (**)(_BYTE *))(*(_DWORD *)v2 + 4))(v2);
  ((UIWnd *)this)->GetID();
  result = *(_DWORD *)&this->_data[14536];
  if ( !result )
    return (*(int (**)(char *))(*(_DWORD *)&this->_data[3904] + 4))(&this->_data[3904]);
  return result;
}

// 0x0044F8A0
int CGameData::SetMode(int mode)
{
  if ( !mode )
    return *((_DWORD *)this + 7044);
  if ( mode == 5 )
    return *((_DWORD *)this + 7045);
  return *(_DWORD *)&this->_data[14532];
}

// 0x0044FF60
int CGameData::GetMode()
{
  return *(_DWORD *)&this->_data[14540];
}
