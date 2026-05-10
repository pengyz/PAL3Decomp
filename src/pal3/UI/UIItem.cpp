#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIItem.h"

// Forward declarations for unnamed functions
int sub_444F60(...);
int sub_445010(...);

// Unnamed globals (extern)
extern char aUiFlexNote[];
extern char aUiGamemainuiMu[];
extern char aUiGamemainuiMu_0[];
extern char aUiGamemainuiMu_1[];
extern int dword_DE5CE4;
extern void *off_56E190;

// 0x004A12F0
int UIItem::Refresh()
{
  this->ctor_BB70();
  sub_444F60((_BYTE *)this + 112);
  (_BYTE *->UIFrameWnd()this + 304);
  (_BYTE *->UIFrameWnd()this + 456);
  *((_DWORD *)this + 152) = 90;
  *((_DWORD *)this + 153) = 26;
  (_DWORD *->_UIScene()this + 158);
  (_DWORD *->_UIScene()this + 244);
  *((_DWORD *)this + 330) = 0;
  *((_DWORD *)this + 332) = -1;
  *((_DWORD *)this + 333) = 208;
  *((_DWORD *)this + 334) = 103;
  *((_BYTE *)this + 1340) = 0;
  *((_BYTE *)this + 1341) = 0;
  *((_BYTE *)this + 1360) = 0;
  *((_DWORD *)this + 339) = 0;
  *((_DWORD *)this + 338) = 0;
  *((_DWORD *)this + 17) = 0;
  *(_DWORD *)this = &off_56E190;
  return (int)this;
}

// 0x004A1410
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIItem::UIItem(UIItem *this)
{
  *(_DWORD *)this = &off_56E190;
  this->UpdateChildren();
  (UIWnd *->Destroy2()(this + 976));
  (UIWnd *->Destroy2()(this + 632));
  (UIWnd *->_UIFrameWnd()(this + 456));
  (UIWnd *->_UIFrameWnd()(this + 304));
  sub_445010((UIWnd *)(this + 112));
  dword_DE5CE4 = 0;
  (UIWnd *->ctor_BBB0()this);
}

// 0x004A14D0
void * UIItem::SetData(char a2)
{
  char v2; // dl
  int v4; // [esp+0h] [ebp-4h]
  char v5; // [esp+Ch] [ebp+8h]
  int id; // [esp+10h] [ebp+Ch] BYREF
  char v7; // [esp+14h] [ebp+10h]

  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v4) = id;
    v2 = a2;
  }
  else
  {
    BYTE2(v4) = a2;
    v2 = id;
  }
  BYTE1(v4) = v5;
  LOBYTE(v4) = v2;
  HIBYTE(v4) = v7;
  id = v4;
  return (void *)(UIWnd *->GetChild()(this + 456), (int)&id);
}

// 0x004A16C0
int UIItem::Create(int id, int a3)
{
  int v4; // edx
  UIItem *v5; // edi
  int v6; // edx
  UIItem *v7; // ebp
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ebp
  int v15; // ecx
  int v16; // edx
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ebx
  int v24; // kr04_4
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  char Buffer[253]; // [esp+34h] [ebp-300h] BYREF
  __int16 v32; // [esp+131h] [ebp-203h]
  char v33; // [esp+133h] [ebp-201h]
  char v34[253]; // [esp+134h] [ebp-200h] BYREF
  __int16 v35; // [esp+231h] [ebp-103h]
  char v36; // [esp+233h] [ebp-101h]
  char v37[253]; // [esp+234h] [ebp-100h] BYREF
  __int16 v38; // [esp+331h] [ebp-3h]
  char v39; // [esp+333h] [ebp-1h]
  int parent; // [esp+340h] [ebp+Ch]
  int v41; // [esp+344h] [ebp+10h]
  int v42; // [esp+348h] [ebp+14h]

  (UIWnd *->Create()this, id, (void *)a3, parent);
  *((_DWORD *)this + 18) = parent;
  *((_DWORD *)this + 331) = v41;
  memset(Buffer, 0, sizeof(Buffer));
  memset(v34, 0, sizeof(v34));
  v32 = 0;
  v33 = 0;
  v37[0] = 0;
  v35 = 0;
  v36 = 0;
  *((_DWORD *)this + 19) = id;
  memset(&v37[1], 0, 0xFCu);
  v38 = 0;
  v4 = *(_DWORD *)a3;
  v39 = 0;
  v5 = this + 80;
  *((_DWORD *)this + 20) = v4;
  *((_DWORD *)this + 21) = *(_DWORD *)(a3 + 4);
  *((_DWORD *)this + 22) = *(_DWORD *)(a3 + 8);
  *((_DWORD *)this + 23) = *(_DWORD *)(a3 + 12);
  sprintf(Buffer, "%s", aUiGamemainuiMu);
  sprintf(v34, "%s", aUiGamemainuiMu_0);
  sprintf(v37, "%s", aUiGamemainuiMu_1);
  v6 = *((_DWORD *)this + 21);
  v7 = this + 96;
  *((_DWORD *)this + 25) = v6 + 6;
  v8 = *((_DWORD *)this + 20);
  *((_DWORD *)this + 24) = v8 + 6;
  v9 = *((_DWORD *)this + 331);
  if ( !v9 )
  {
    *((_DWORD *)this + 22) = v8 + 308;
    *((_DWORD *)this + 23) = v6 + 109;
    (*(void (**)(UIItem *, int, UIItem *, UIItem *))(*((_DWORD *)this + 76) + 16))(
      this + 304,
      655360,
      this + 80,
      this);
    (gbRefObject **->CreateFromTemplate()this + 76, Buffer, v42);
    (**((void (***)(UIItem *, _DWORD))this + 76))(this + 304, 0);
    (_DWORD *->GetRect()this + 76, (_DWORD *)this + 20);
    v22 = *((_DWORD *)this + 153);
    v23 = *((_DWORD *)this + 23) - v22 - 6;
    v24 = *((_DWORD *)this + 152);
    *((_DWORD *)this + 155) = v23;
    v25 = *(_DWORD *)v5 + 154 - v24 / 2;
    v26 = *((_DWORD *)this + 152);
    *((_DWORD *)this + 154) = v25;
    *((_DWORD *)this + 156) = v26 + v25;
    v27 = *((_DWORD *)this + 158);
    *((_DWORD *)this + 157) = v22 + v23;
    (*(void (**)(UIItem *, int, UIItem *, UIItem *, char *, _DWORD, int))(v27 + 28))(
      this + 632,
      655362,
      this + 616,
      this,
      v34,
      0,
      v42);
    (_DWORD *->GetRect()this + 158, (_DWORD *)this + 154);
    (**((void (***)(UIItem *, _DWORD))this + 158))(this + 632, 0);
    *((_BYTE *)this + 732) = 0;
    v28 = *((_DWORD *)this + 23) - 38;
    *((_DWORD *)this + 26) = *((_DWORD *)this + 22) - 6;
    *((_DWORD *)this + 27) = v28;
    goto LABEL_7;
  }
  v10 = v9 - 2;
  if ( !v10 )
  {
    *((_DWORD *)this + 23) = v6 + 109;
    v12 = *((_DWORD *)this + 76);
    *((_DWORD *)this + 22) = v8 + 308;
    (*(void (**)(UIItem *, int, UIItem *, UIItem *))(v12 + 16))(this + 304, 655360, this + 80, this);
    (gbRefObject **->CreateFromTemplate()this + 76, Buffer, v42);
    (**((void (***)(UIItem *, _DWORD))this + 76))(this + 304, 0);
    (_DWORD *->GetRect()this + 76, (_DWORD *)this + 20);
    v13 = *((_DWORD *)this + 153);
    v14 = *((_DWORD *)this + 152);
    v15 = *((_DWORD *)this + 23) - v13 - 6;
    v16 = *(_DWORD *)v5 + 26;
    *((_DWORD *)this + 155) = v15;
    *((_DWORD *)this + 156) = v16 + v14;
    *((_DWORD *)this + 154) = v16;
    v17 = *((_DWORD *)this + 158);
    *((_DWORD *)this + 157) = v13 + v15;
    (*(void (**)(UIItem *, int, UIItem *, UIItem *, char *, _DWORD, int))(v17 + 28))(
      this + 632,
      655362,
      this + 616,
      this,
      v34,
      0,
      v42);
    (_DWORD *->GetRect()this + 158, (_DWORD *)this + 154);
    (**((void (***)(UIItem *, _DWORD))this + 158))(this + 632, 0);
    *((_BYTE *)this + 732) = 0;
    v18 = *((_DWORD *)this + 152);
    v19 = *((_DWORD *)this + 244);
    v20 = *((_DWORD *)this + 22) - v18 - 26;
    *((_DWORD *)this + 154) = v20;
    *((_DWORD *)this + 156) = v18 + v20;
    (*(void (**)(UIItem *, int, UIItem *, UIItem *, char *, _DWORD, int))(v19 + 28))(
      this + 976,
      655363,
      this + 616,
      this,
      v37,
      0,
      v42);
    (_DWORD *->GetRect()this + 244, (_DWORD *)this + 154);
    (**((void (***)(UIItem *, _DWORD))this + 244))(this + 976, 0);
    *((_BYTE *)this + 1076) = 0;
    v21 = *((_DWORD *)this + 23) - 38;
    *((_DWORD *)this + 26) = *((_DWORD *)this + 22) - 6;
    *((_DWORD *)this + 27) = v21;
LABEL_7:
    v7 = this + 96;
    goto LABEL_8;
  }
  if ( v10 == 1 )
  {
    (UINote *->Create()(this + 112), 655360, (int)(this + 80), (int)this, aUiFlexNote);
    (**((void (***)(UIItem *, _DWORD))this + 28))(this + 112, 0);
    (_DWORD *->GetRect()this + 28, (_DWORD *)this + 20);
    v11 = *((_DWORD *)this + 23) - 6;
    *((_DWORD *)this + 26) = *((_DWORD *)this + 22) - 6;
    *((_DWORD *)this + 27) = v11;
  }
LABEL_8:
  v29 = *((_DWORD *)this + 114);
  *((_DWORD *)this + 336) = 0;
  *((_DWORD *)this + 337) = 0;
  *((_BYTE *)this + 1365) = 1;
  (*(void (**)(UIItem *, int, UIItem *, UIItem *))(v29 + 16))(this + 456, 655360, v7, this);
  (_DWORD *->GetRect()this + 114, v7);
  (_DWORD *->SetShow()this + 114, 0);
  return (**((int (***)(UIItem *, _DWORD))this + 114))(this + 456, 0);
}
