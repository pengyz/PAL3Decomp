#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIListBox.h"

// Forward declarations for unnamed functions
int sub_432680(...);
int sub_43DCD0(...);
int sub_43DCF0(...);
int sub_43DDF0(...);
int sub_43DE40(...);
int sub_43DEA0(...);
int sub_43DEC0(...);
int sub_43DEF0(...);
int sub_43DF10(...);
int sub_43DF20(...);
int sub_43DF70(...);
int sub_43E100(...);
int sub_43E120(...);
int sub_43E330(...);
int sub_43E3B0(...);
int sub_43E440(...);
int sub_43E480(...);
int sub_43E520(...);
int sub_43E5C0(...);
int sub_43E7D0(...);
int sub_43E8A0(...);
int sub_43EBA0(...);
int sub_43F360(...);
int sub_43F520(...);
int sub_43F6D0(...);
int sub_4413C0(...);
int sub_442060(...);
int sub_5372D0(...);

// Unnamed globals (extern)
extern char aCNewFailed[];
extern char aDProjectPal3Ui[];
extern char aUiCommonScroll[];
extern int dword_1894B78;
extern void *off_56AD20;
extern void *off_56AD40;

// 0x0043DCD0
_DWORD * sub_43DCD0()
{
  UIWnd::UIWnd();
  *this = &off_56AD20;
  *((_DWORD *)this + 17) = 0;
  return this;
}

// 0x0043DCF0
UIWnd * sub_43DCF0(UIWnd *Block, char a2)
{
  UIWnd::~UIWnd(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0043DD60
int UIListBox::SetSelTexture(int id, int pRect, int a4, int a5, int a6, int a7)
{
  int v7; // edi
  gbTexture *v9; // eax

  v7 = a7;
  if ( a7 )
  {
    OpenBaseFile::OpenBaseFile(&a7);
    v9 = (gbTexture *)(*(int (__thiscall **)(gbGfxManager *, int))(*(_DWORD *)g_pGfxManager + 8))(
                        g_pGfxManager,
                        v7);
    this->m_pfather = (UIWnd *)v9;
    if ( v9 )
      v9->LoadTexture(1);
    (struct gbVFileSystem **->OpenNULLFile()&a7);
  }
  return this->Create(id, &pRect, 0);
}

// 0x0043DDF0
int sub_43DDF0()
{
  int result; // eax
  int v3[17]; // [esp+4h] [ebp-44h] BYREF

  result = *((_DWORD *)this + 14);
  if ( result )
  {
    if ( *((_DWORD *)this + 17) )
    {
      v3[0] = *((_DWORD *)this + 17);
      v3[16] = 1;
      _TextureLib_Data::SetLibFolder((int)(this + 4), (int)(this + 2), (int)v3, 276, 0, COERCE_FLOAT(1));
    }
    return this->GetID();
  }
  return result;
}

// 0x0043DE40
int sub_43DE40(gbRefObject **this)
{
  gbRefObject *v2; // ecx

  v2 = *((_DWORD *)this + 17);
  if ( v2 )
  {
    v2->Release();
    *((_DWORD *)this + 17) = 0;
  }
  return this->UpdateChildren();
}

// 0x0043DE90
// attributes: thunk
int UIListBox::Destroy()
{
  return UIListBox::AddColumn();
}

// 0x0043DEA0
int sub_43DEA0()
{
  MEMORY[0xD902F4] = 1094713344;
  return 1094713344;
}

// 0x0043DEB0
// attributes: thunk
void UIListBox::AddRow()
{
  UIListBox::SetSubItem();
}

// 0x0043DEC0
void sub_43DEC0()
{
  MEMORY[0xD902F0] = 12.0 + 12.0;
}

// 0x0043DED0
void * UIListBox::GetSubItemInfo()
{
  memset(this, 0, 0x48u);
  return this;
}

// 0x0043DEF0
int sub_43DEF0(gbRefObject **this)
{
  gbRefObject *v2; // ecx

  v2 = *this;
  if ( v2 )
    v2->Release();
  memset(this, 0, 0x48u);
  return 0;
}

// 0x0043DF10
void sub_43DF10()
{
  PtrArray::Clear(this + 16);
}

// 0x0043DF20
void sub_43DF20(void **this)
{
  sub_43DF70();
  sub_432680(this + 16);
}

// 0x0043DFC0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char *__thiscall UIListBox::UpdateKeyCtrl(UIListBox *this)
{
  char v3; // [esp+Bh] [ebp-11h]

  this->UIWnd();
  if ( gbColorQuad::ColorQuadFmt )
  {
    this->UIWnd[70] = -6;
    this->UIWnd[69] = 55;
    this->UIWnd[68] = 55;
  }
  else
  {
    this->UIWnd[68] = -6;
    this->UIWnd[70] = 55;
    this->UIWnd[69] = 55;
  }
  this->UIWnd[71] = -56;
  &this->UIWnd[80]->ctor_10F0();
  `eh vector constructor iterator'(
    &this->UIWnd[436],
    0x54u,
    8,
    (void (__thiscall *)(void *))UIListBox::CalHeightCount,
    (void (__thiscall *)(void *))UIListBox::GetItemPos);
  this->UIWnd[1179] = -56;
  this->UIWnd[1178] = -88;
  this->UIWnd[1177] = -88;
  this->UIWnd[1176] = -88;
  this->UIWnd[1192] = v3;
  *(_DWORD *)&this->UIWnd[1196] = 0;
  *(_DWORD *)&this->UIWnd[1200] = 0;
  *(_DWORD *)&this->UIWnd[1204] = 0;
  *(_DWORD *)&this->UIWnd[432] = 0;
  *(_DWORD *)&this->UIWnd[1116] = 0;
  *(_DWORD *)&this->UIWnd[1144] = 0;
  *(_DWORD *)&this->UIWnd[1152] = 0;
  *(_DWORD *)&this->UIWnd[1160] = 0;
  *(_DWORD *)&this->UIWnd[1168] = 0;
  *(_DWORD *)&this->UIWnd[1164] = 0;
  *(_DWORD *)&this->UIWnd[1108] = 16;
  *(_DWORD *)&this->UIWnd[1172] = 16;
  *(_DWORD *)&this->UIWnd[1112] = 16;
  *(_DWORD *)&this->UIWnd[1180] = 0;
  *(_DWORD *)&this->UIWnd[1184] = 0;
  *(_DWORD *)&this->UIWnd[1188] = 0;
  *(_DWORD *)&this->UIWnd[72] = 0;
  *(_DWORD *)&this->UIWnd[1148] = 0;
  *(_DWORD *)&this->UIWnd[1156] = 0;
  *(_DWORD *)this->UIWnd = &off_56AD40;
  *(_DWORD *)&this->UIWnd[1120] = -1;
  return this->UIWnd;
}

// 0x0043E100
UIWnd * sub_43E100(UIWnd *Block, char a2)
{
  Block->DeleteRow();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0043E120
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void __thiscall sub_43E120(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD40;
  UIListBox::GetItemCount();
  operator delete(*((void **)this + 299));
  *((_DWORD *)this + 299) = 0;
  *((_DWORD *)this + 300) = 0;
  *((_DWORD *)this + 301) = 0;
  `eh vector destructor iterator'((char *)this + 436, 0x54u, 8, (void (__thiscall *)(void *))UIListBox::GetItemPos);
  UIWnd::ctor_11D0(this + 2);
  this->_UIWnd();
}

// 0x0043E1C0
int UIListBox::CalScrollBarRange(int this, int id, _DWORD *a3, int parent, LPCSTR lpString, int a6, char a7)
{
  const CHAR *v7; // edi
  int (__thiscall **vtable)(gbGfxManager *, CHAR *); // ebp
  CHAR *v10; // eax
  gbTexture *v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  _DWORD *v15; // eax
  int (__thiscall **v16)(int, int); // edx
  _DWORD v18[4]; // [esp+20h] [ebp-1Ch] BYREF
  int v19; // [esp+38h] [ebp-4h]

  v7 = lpString;
  if ( lpString )
  {
    OpenBaseFile::OpenBaseFile(&lpString);
    v19 = 0;
    if ( a7 )
    {
      vtable = *(int (__thiscall ***)(gbGfxManager *, CHAR *))g_pGfxManager;
      v10 = _Texture_Info::_CalculateUV((int)dword_1894B78, v7);
      *(_DWORD *)(this + 1144) = vtable[2](g_pGfxManager, v10);
      *(_DWORD *)(this + 1148) = Parent_Data::Parent_Data((int)dword_1894B78, v7);
    }
    else
    {
      *(_DWORD *)(this + 1144) = (*(int (__thiscall **)(gbGfxManager *, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                   g_pGfxManager,
                                   v7);
    }
    v11 = *(gbTexture **)(this + 1144);
    if ( v11 )
      v11->LoadTexture(1);
    v19 = -1;
    (struct gbVFileSystem **->OpenNULLFile()&lpString);
  }
  (UIWnd *->Create()this, id, a3, parent);
  v12 = *(_DWORD *)(this + 1172);
  *(_BYTE *)(this + 76) = 1;
  v13 = a3[2] - *a3;
  *(_DWORD *)(this + 1136) = v13;
  *(_DWORD *)(this + 1128) = v13 - v12;
  *(_DWORD *)(this + 1132) = 0;
  v14 = *(_DWORD *)(this + 80);
  *(_DWORD *)(this + 1140) = a3[3] - a3[1];
  (*(void (__thiscall **)(int, int, int, int, char *, int, _DWORD))(v14 + 28))(
    this + 80,
    1,
    this + 1128,
    this,
    aUiCommonScroll,
    1,
    0);
  sub_442060((_DWORD *)(this + 80), 0);
  sub_43F520((_DWORD *)this);
  v15 = (_DWORD *->SetRect()(this + 80), v18);
  *(_DWORD *)(this + 1128) = *v15;
  *(_DWORD *)(this + 1132) = v15[1];
  *(_DWORD *)(this + 1136) = v15[2];
  v16 = *(int (__thiscall ***)(int, int))(this + 80);
  *(_DWORD *)(this + 1140) = v15[3];
  return (*v16)(this + 80, a6);
}

// 0x0043E330
void sub_43E330(int a2, int a3)
{
  int v3; // edi
  gbTexture *v5; // eax

  v3 = a2;
  if ( a2 )
  {
    OpenBaseFile::OpenBaseFile(&a2);
    v5 = (gbTexture *)(*(int (__thiscall **)(int, int))(*(_DWORD *)g_pGfxManager + 8))(g_pGfxManager, v3);
    *((_DWORD *)this + 288) = v5;
    if ( v5 )
      v5->LoadTexture(1);
    (struct gbVFileSystem **->OpenNULLFile()&a2);
  }
}

// 0x0043E3B0
int sub_43E3B0(int a2, _DWORD *a3, int a4, int a5, char a6)
{
  int v8; // ecx
  int v9; // edx

  if ( a2 )
    sub_4413C0(a2, a6);
  *((_DWORD *)this + 282) = *a3;
  *((_DWORD *)this + 283) = a3[1];
  *((_DWORD *)this + 284) = a3[2];
  *((_DWORD *)this + 285) = a3[3];
  *((_DWORD *)this + 282) = *((_DWORD *)this + 284) - a4;
  UIWnd::GetRect(this + 282);
  v8 = *((_DWORD *)this + 101);
  v9 = a5 + *((_DWORD *)this + 97);
  *((_DWORD *)this + 59) = a5;
  *((_DWORD *)this + 99) = v9;
  *((_DWORD *)this + 103) = a5 + v8;
  *((_DWORD *)this + 293) = a4;
  return a5;
}

// 0x0043E440
int sub_43E440(int a2)
{
  int v3; // eax

  sub_43F520(this);
  v3 = a2;
  if ( a2 >= *((_DWORD *)this + 62) )
    v3 = *((_DWORD *)this + 62);
  if ( v3 <= *((_DWORD *)this + 61) )
    v3 = *((_DWORD *)this + 61);
  *((_DWORD *)this + 279) = v3;
  return sub_442060(v3);
}

// 0x0043E480
int sub_43E480(int a2, int a3, int a4)
{
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // ecx

  if ( a2 != 1005 )
    return a2->SendMessage(a3, a4);
  if ( *((_DWORD *)this + 297) )
  {
    v6 = *((_DWORD *)this + 279);
    *((_DWORD *)this + 279) = a4;
    v7 = this->CreateChild();
    if ( v7 == -1 )
    {
      *((_DWORD *)this + 279) = v6;
    }
    else if ( *(_DWORD *)(*((_DWORD *)this + 299) + 4 * v7) )
    {
      v8 = *((_DWORD *)this + 8);
      if ( v8 )
        (*(void (__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v8 + 24))(v8, 1006, *((_DWORD *)this + 3), v7);
    }
  }
  else
  {
    *((_DWORD *)this + 279) = a4;
  }
  v9 = *((_DWORD *)this + 8);
  if ( v9 )
    (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1005, 0, 0);
  return 1;
}

// 0x0043E520
int sub_43E520(gbRefObject **this)
{
  gbRefObject *v2; // ecx

  sub_43F360();
  v2 = *((_DWORD *)this + 286);
  *((_DWORD *)this + 108) = 0;
  if ( v2 )
  {
    v2->Release();
    *((_DWORD *)this + 286) = 0;
  }
  return this->UpdateChildren();
}

// 0x0043E560
int UIListBox::SetFirstShow(char *Source, int a3)
{
  int result; // eax

  strncpy(&this->UIWnd[84 * *(_DWORD *)&this->UIWnd[432] + 436], Source, 0x40u);
  *(_DWORD *)&this->UIWnd[84 * *(_DWORD *)&this->UIWnd[432] + 516] = a3;
  result = *(_DWORD *)&this->UIWnd[432] + 1;
  *(_DWORD *)&this->UIWnd[432] = result;
  return result;
}

// 0x0043E5C0
int sub_43E5C0(char *Source, int a3)
{
  void *v4; // eax
  char *v5; // edi
  gbTexture *v6; // eax
  int v7; // ebp
  int v8; // ebx
  _DWORD *v9; // edi
  void *v10; // eax
  void *v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v17; // [esp+10h] [ebp-814h] BYREF
  struct gbVFileSystem *v18; // [esp+14h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+18h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+418h] [ebp-40Ch] BYREF
  int v21; // [esp+820h] [ebp-4h]

  v4 = operator new(0x48u);
  if ( !v4 || (v5 = (char *)v4->GetSubItemInfo()) == 0 )
  {
    qmemcpy(
      pExceptionObject,
      (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Ui, 260),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( a3 )
  {
    OpenBaseFile::OpenBaseFile(&v18);
    v21 = 0;
    v6 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(g_pGfxManager, Source);
    *(_DWORD *)v5 = v6;
    if ( v6 )
      v6->LoadTexture(1);
    v21 = -1;
    OpenNULLFile::OpenNULLFile(&v18);
  }
  else
  {
    strncpy(v5 + 4, Source, 0x40u);
    *((_DWORD *)v5 + 17) = *((_DWORD *)this + 1);
  }
  v7 = *((_DWORD *)this + 126);
  PtrArray::SetAt(this + 125, v7, (int)v5);
  v8 = 1;
  if ( *((_DWORD *)this + 108) > 1 )
  {
    v9 = this + 146;
    do
    {
      v10 = operator new(0x48u);
      if ( !v10 || (v11 = v10->GetSubItemInfo()) == 0 )
      {
        qmemcpy(
          pExceptionObject,
          (const void *)Logger::FormatException((char)ArgList, (int)aCNewFailed, (int)aDProjectPal3Ui, 282),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      v9->SetAt(v9[1], (int)v11);
      ++v8;
      v9 += 21;
    }
    while ( v8 < *((_DWORD *)this + 108) );
  }
  sub_43F520(this);
  v12 = *((_DWORD *)this + 300);
  v17 = 1;
  sub_5372D0(v12, 1, &v17);
  v13 = *((_DWORD *)this + 299);
  if ( v13 )
  {
    if ( (*((_DWORD *)this + 300) - v13) >> 2 )
    {
      if ( *((_DWORD *)this + 280) == -1 )
      {
        sub_43F6D0(0);
        if ( *((_DWORD *)this + 280) != -1 )
        {
          v14 = this->CreateChild();
          v15 = *((_DWORD *)this + 8);
          if ( v15 )
            (*(void (__thiscall **)(int, int, _DWORD, int))(*(_DWORD *)v15 + 24))(v15, 1006, *((_DWORD *)this + 3), v14);
        }
      }
    }
  }
  return v7;
}

// 0x0043E7D0
struct gbVFileSystem * sub_43E7D0(int a2, int a3, char *Source, int a5)
{
  int v5; // esi
  gbTexture *v6; // eax

  if ( a3 < 0 || a3 >= *(this + 21 * a2 + 126) )
    v5 = 0;
  else
    v5 = *(_DWORD *)(*(this + 21 * a2 + 125) + 4 * a3);
  if ( !a5 )
    return (struct gbVFileSystem *)strncpy((char *)(v5 + 4), Source, 0x40u);
  OpenBaseFile::OpenBaseFile(&a2);
  v6 = (gbTexture *)(*(int (__thiscall **)(int, char *))(*(_DWORD *)g_pGfxManager + 8))(g_pGfxManager, Source);
  *(_DWORD *)v5 = v6;
  if ( v6 )
    v6->LoadTexture(1);
  return (struct gbVFileSystem **->OpenNULLFile()&a2);
}

// 0x0043E8A0
int sub_43E8A0()
{
  int result; // eax
  int v3; // eax
  int v4; // ebp
  int *v5; // eax
  int v6; // ebx
  int v7; // edi
  int *v8; // ecx
  int v9; // eax
  bool v10; // cc
  int v11; // eax
  int v12; // edx
  bool v13; // cl
  int v14; // eax
  int v15; // ecx
  int v16; // ebp
  int v17; // ebx
  int v18; // ecx
  int v19; // eax
  int v20; // ebx
  int v21; // edi
  int v22; // edx
  int v23; // edx
  int v24; // ecx
  int v25; // edi
  int v26; // edi
  int v27; // [esp-24h] [ebp-88h]
  int v28; // [esp-1Ch] [ebp-80h]
  int *v29; // [esp+4h] [ebp-60h]
  int v30; // [esp+8h] [ebp-5Ch]
  int v31; // [esp+Ch] [ebp-58h]
  int v32[3]; // [esp+10h] [ebp-54h] BYREF
  int v33; // [esp+1Ch] [ebp-48h]
  int v34[16]; // [esp+20h] [ebp-44h] BYREF
  int v35; // [esp+60h] [ebp-4h]

  result = *((_DWORD *)this + 14);
  if ( result )
  {
    if ( *((_DWORD *)this + 286) )
    {
      v34[0] = *((_DWORD *)this + 286);
      v3 = *((_DWORD *)this + 287);
      v35 = 1;
      _TextureLib_Data::SetLibFolder((int)(this + 4), (int)(this + 2), (int)v34, 276, v3, COERCE_FLOAT(1));
    }
    else if ( *((_DWORD *)this + 18) )
    {
      _TextureLib_Data::~_TextureLib_Data(*((_DWORD *)this + 4), *((_DWORD *)this + 5), *((_DWORD *)this + 6), *((_DWORD *)this + 7), &MEMORY[0xD91780]);
    }
    v4 = *((_DWORD *)this + 295) + *((_DWORD *)this + 4) + 8;
    v30 = this->SetDefaultSel();
    v31 = 0;
    if ( *((_DWORD *)this + 108) > 0 )
    {
      v5 = this + 126;
      v29 = this + 126;
      do
      {
        v6 = *((_DWORD *)this + 279);
        v7 = *((_DWORD *)this + 5) + *((_DWORD *)this + 296) + 8;
        if ( v6 < v6 + v30 )
        {
          do
          {
            if ( v6 >= *v5 )
              break;
            v8 = v6 < 0 ? 0 : *(int **)(*(v5 - 1) + 4 * v6);
            if ( *v8 )
            {
              v34[0] = *v8;
              v32[2] = v4 + 32;
              v33 = v7 + 32;
              v32[0] = v4;
              v32[1] = v7;
              v35 = 1;
              _TextureLib_Data::SetLibFolder((int)v32, (int)(this + 2), (int)v34, 276, 0, COERCE_FLOAT(1));
            }
            else if ( *(_DWORD *)(*((_DWORD *)this + 299) + 4 * v6) )
            {
              v9 = v6 < 0 || v6 >= *((_DWORD *)this + 126) ? 0 : *(_DWORD *)(*((_DWORD *)this + 125) + 4 * v6);
              UIRenderQuad(v4, v7, v8 + 1, v9 + 68, *((_DWORD *)this + 278));
            }
            else
            {
              UIRenderQuad(v4, v7, v8 + 1, &MEMORY[0xD91780], *((_DWORD *)this + 278));
            }
            v7 += *((_DWORD *)this + 277);
            ++v6;
            v5 = v29;
          }
          while ( v6 < v30 + *((_DWORD *)this + 279) );
        }
        v4 += v5[3];
        v5 += 21;
        v10 = ++v31 < *((_DWORD *)this + 108);
        v29 = v5;
      }
      while ( v10 );
    }
    v11 = this->CreateChild();
    v12 = *((_DWORD *)this + 297);
    if ( v12 )
    {
      v13 = *((_DWORD *)this + 280) != -1;
      if ( *((_DWORD *)this + 280) == -1 || !*(_DWORD *)(*((_DWORD *)this + 299) + 4 * v11) )
        return this->GetID();
    }
    else
    {
      v13 = *((_DWORD *)this + 281) != -1;
    }
    if ( v13 )
    {
      v14 = *((_DWORD *)this + 4);
      v15 = *((_DWORD *)this + 5);
      v16 = *((_DWORD *)this + 296);
      v17 = *((_DWORD *)this + 6);
      v33 = *((_DWORD *)this + 7);
      v18 = v16 + v15;
      v19 = *((_DWORD *)this + 295) + v14 + 4;
      v20 = -2 - *((_DWORD *)this + 293) + v17;
      v21 = *((_DWORD *)this + 277);
      v22 = v12 ? *((_DWORD *)this + 280) : *((_DWORD *)this + 281) - *((_DWORD *)this + 279);
      v23 = v18 + v21 * v22 + 8;
      v24 = v21 + v23 - 2;
      v25 = *((_DWORD *)this + 7);
      if ( v24 > v25 )
        v24 = *((_DWORD *)this + 7);
      if ( v23 >= *((_DWORD *)this + 5) && v24 <= v25 )
      {
        if ( *((_DWORD *)this + 288) )
        {
          v34[0] = *((_DWORD *)this + 288);
          v26 = *((_DWORD *)this + 290);
          v28 = v20 + *((_DWORD *)this + 292);
          v27 = v19 + *((_DWORD *)this + 291);
          v35 = 1;
          UIDestorySystem(v27, v23 + v26, v28, v26 + v24, this + 294, v34);
          return this->GetID();
        }
        _TextureLib_Data::~_TextureLib_Data(v19, v23, v20, v24, this + 17);
      }
    }
    return this->GetID();
  }
  return result;
}

// 0x0043EBA0
int sub_43EBA0()
{
  return (*((_DWORD *)this + 7) - *((_DWORD *)this + 5)) / *((_DWORD *)this + 277);
}
