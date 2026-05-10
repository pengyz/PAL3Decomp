#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/Logger.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/Parent_Data.h"
#include "pal3/gen/PtrArray.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_432680(...);
int sub_43DF70(...);
int sub_43E120(...);
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
UIListBox::UIListBox()
{
  this->UIWnd();
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AD20;
  this->m_pfather = 0;
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0043DCF0
UIListBox::~UIListBox(UIListBox *Block, char a2)
{
  UIWnd::~UIWnd((UIWnd *)Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x0043DD60
int UIListBox::SetSelTexture(int id, int pRect, int a4, int a5, int a6, int a7)
{
  int v7; // edi
  UIWnd *v9; // eax

  v7 = a7;
  if ( a7 )
  {
    OpenBaseFile::OpenBaseFile((OpenBaseFile *)&a7);
    v9 = (UIWnd *)(*(int (**)(int, int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                    g_Input.KeyInfo[177].Data,
                    v7);
    this->m_pfather = v9;
    if ( v9 )
      gbTexture::LoadTexture((gbTexture *)v9, 1);
    OpenNULLFile::OpenNULLFile((OpenNULLFile **)&a7);
  }
  return this->Create(id, &pRect, 0);
}

// 0x0043DDF0
int UIListBox::SetScroll()
{
  int result; // eax
  struct gbTextureArray v3; // [esp+4h] [ebp-44h] BYREF

  result = this->m_rect.top;
  if ( result )
  {
    if ( this->m_pfather )
    {
      v3.pTexPt[0] = (gbTexture *)this->m_pfather;
      v3.nTex = 1;
      _TextureLib_Data::SetLibFolder(
        &this->m_fontcolor.Alpha,
        (unsigned int *)&this->m_fontcolor.Green,
        &v3,
        0x114u,
        0,
        COERCE_FLOAT(1));
    }
    return this->GetID();
  }
  return result;
}

// 0x0043DE40
int UIListBox::SetScrollPos(UIListBox **this)
{
  gbRefObject *v2; // ecx
  int result; // eax

  v2 = (gbRefObject *)*((_DWORD *)this + 17);
  if ( v2 )
  {
    v2->Release();
    *((_DWORD *)this + 17) = 0;
  }
  UIWnd::UpdateChildren((UIWnd *)this);
  return result;
}

// 0x0043DE90
// attributes: thunk
int UIListBox::Destroy()
{
  return UIListBox::AddColumn();
}

// 0x0043DEA0
int UIListBox::AddColumn()
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
void UIListBox::SetSubItem()
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
int UIListBox::Render(UIListBox **this)
{
  UIListBox *v2; // ecx

  v2 = (UIListBox *)*this;
  if ( v2 )
    gbRefObject::Release((gbRefObject *)v2);
  memset(this, 0, 0x48u);
  return 0;
}

// 0x0043DF10
void UIListBox::CalHeightCount()
{
  PtrArray::Clear((PtrArray *)&this->m_rect.bottom);
}

// 0x0043DF20
void UIListBox::GetItemPos(UIListBox **this)
{
  sub_43DF70(this);
  sub_432680((void **)this + 16);
}

// 0x0043DFC0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char *UIListBox::UpdateKeyCtrl(UIListBox *this)
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
  UIWnd::ctor_10F0(&this->UIWnd[80]);
  `eh vector constructor iterator'(
    &this->UIWnd[436],
    0x54u,
    8,
    (void (*)(void *))UIListBox::CalHeightCount,
    (void (*)(void *))UIListBox::GetItemPos);
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
UIWnd * UIListBox::DeleteAllItems(UIWnd *Block, char a2)
{
  Block->DeleteRow();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0043E120
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_43E120(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD40;
  UIListBox::GetItemCount();
  operator delete(*((void **)this + 299));
  *((_DWORD *)this + 299) = 0;
  *((_DWORD *)this + 300) = 0;
  *((_DWORD *)this + 301) = 0;
  `eh vector destructor iterator'((char *)this + 436, 0x54u, 8, (void (*)(void *))UIListBox::GetItemPos);
  UIWnd::ctor_11D0(this + 2);
  this->_UIWnd();
}

// 0x0043E1C0
int UIListBox::CalScrollBarRange(int _this, int id, _DWORD *a3, int parent, LPCSTR lpString, int a6, char a7)
{
  const CHAR *v7; // edi
  int (**vtable)(gbGfxManager *, CHAR *); // ebp
  CHAR *v10; // eax
  gbTexture *v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  _DWORD *v15; // eax
  int (**v16)(int, int); // edx
  _DWORD v18[4]; // [esp+20h] [ebp-1Ch] BYREF
  int v19; // [esp+38h] [ebp-4h]

  v7 = lpString;
  if ( lpString )
  {
    OpenBaseFile::OpenBaseFile(&lpString);
    v19 = 0;
    if ( a7 )
    {
      vtable = *(int (***)(gbGfxManager *, CHAR *))g_pGfxManager;
      v10 = (CHAR *)_Texture_Info::_CalculateUV((int)dword_1894B78, v7);
      *(_DWORD *)(this + 1144) = vtable[2](g_pGfxManager, v10);
      *(_DWORD *)(this + 1148) = Parent_Data::Parent_Data((int)dword_1894B78, v7);
    }
    else
    {
      *(_DWORD *)(this + 1144) = (*(int (**)(gbGfxManager *, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                   g_pGfxManager,
                                   v7);
    }
    v11 = (gbTexture *)*(gbTexture **)(this + 1144);
    if ( v11 )
      v11->LoadTexture(1);
    v19 = -1;
    OpenNULLFile::OpenNULLFile((struct gbVFileSystem **)&lpString);
  }
  UIWnd::Create((UIWnd *)this, id, a3, parent);
  v12 = *(_DWORD *)(this + 1172);
  *(_BYTE *)(this + 76) = 1;
  v13 = a3[2] - *a3;
  *(_DWORD *)(this + 1136) = v13;
  *(_DWORD *)(this + 1128) = v13 - v12;
  *(_DWORD *)(this + 1132) = 0;
  v14 = *(_DWORD *)(this + 80);
  *(_DWORD *)(this + 1140) = a3[3] - a3[1];
  (*(void (**)(int, int, int, int, char *, int, _DWORD))(v14 + 28))(
    this + 80,
    1,
    this + 1128,
    this,
    aUiCommonScroll,
    1,
    0);
  sub_442060((_DWORD *)(this + 80), 0);
  sub_43F520((_DWORD *)this);
  v15 = (_DWORD *)UIWnd::SetRect((_DWORD *)(this + 80), v18);
  *(_DWORD *)(this + 1128) = *v15;
  *(_DWORD *)(this + 1132) = v15[1];
  *(_DWORD *)(this + 1136) = v15[2];
  v16 = *(int (***)(int, int))(this + 80);
  *(_DWORD *)(this + 1140) = v15[3];
  return (*v16)(this + 80, a6);
}

// 0x0043E330
void UIListBox::GetSel(int a2, int a3)
{
  int v3; // edi
  gbTexture *v5; // eax

  v3 = a2;
  if ( a2 )
  {
    OpenBaseFile::OpenBaseFile((OpenBaseFile *)&a2);
    v5 = (gbTexture *)(*(int (**)(int, int))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                        g_Input.KeyInfo[177].Data,
                        v3);
    *(_DWORD *)&this->m_column[6].head[16] = v5;
    if ( v5 )
      v5->LoadTexture(1);
    OpenNULLFile::OpenNULLFile((OpenNULLFile **)&a2);
  }
}

// 0x0043E3B0
int UIListBox::GetLockSel(int a2, _DWORD *a3, int a4, int a5, char a6)
{
  float m_lastpos; // ecx
  int v9; // edx

  if ( a2 )
    sub_4413C0(&this->m_childs.m_nMaxSize, (const char *)a2, a6);
  this->m_column[5].rightalign = *a3;
  this->m_column[5].rightoffset = a3[1];
  *(_DWORD *)this->m_column[6].head = a3[2];
  *(_DWORD *)&this->m_column[6].head[4] = a3[3];
  this->m_column[5].rightalign = *(_DWORD *)this->m_column[6].head - a4;
  UIWnd::GetRect((UIWnd *)&this->m_childs.m_nMaxSize, &this->m_column[5].rightalign);
  m_lastpos = this->m_scrollbar.m_lastpos;
  v9 = a5 + this->m_scrollbar.m_mouseat;
  this->m_scrollbar.m_bfocus = a5;
  this->m_scrollbar.m_max = v9;
  LODWORD(this->m_scrollbar.m_step) = a5 + LODWORD(m_lastpos);
  *(_DWORD *)&this->m_column[6].head[36] = a4;
  return a5;
}

// 0x0043E440
int UIListBox::SetSel(int a2)
{
  __int32 ColorQuadFmt; // eax

  sub_43F520(this);
  ColorQuadFmt = a2;
  if ( a2 >= this->m_scrollbar.m_bk.m_fontcolor.ColorQuadFmt )
    ColorQuadFmt = this->m_scrollbar.m_bk.m_fontcolor.ColorQuadFmt;
  if ( ColorQuadFmt <= this->m_scrollbar.m_bPressed )
    ColorQuadFmt = this->m_scrollbar.m_bPressed;
  this->m_column[5].items.m_nMaxSize = ColorQuadFmt;
  return sub_442060(&this->m_childs.m_nMaxSize, ColorQuadFmt);
}

// 0x0043E480
int UIListBox::SetItemHeight(int a2, int a3, int a4)
{
  int m_nMaxSize; // edi
  int Child; // eax
  __int32 Green; // ecx
  __int32 v9; // ecx

  if ( a2 != 1005 )
    return a2->SendMessage(a3, a4);
  if ( *(_DWORD *)&this->m_column[6].head[52] )
  {
    m_nMaxSize = this->m_column[5].items.m_nMaxSize;
    this->m_column[5].items.m_nMaxSize = a4;
    Child = this->CreateChild();
    if ( Child == -1 )
    {
      this->m_column[5].items.m_nMaxSize = m_nMaxSize;
    }
    else if ( *(_DWORD *)(*(_DWORD *)&this->m_column[6].head[60] + 4 * Child) )
    {
      Green = this->m_wndcolor.Green;
      if ( Green )
        (*(void (**)(__int32, int, __int32, int))(*(_DWORD *)Green + 24))(
          Green,
          1006,
          this->m_fontcolor.Red,
          Child);
    }
  }
  else
  {
    this->m_column[5].items.m_nMaxSize = a4;
  }
  v9 = this->m_wndcolor.Green;
  if ( v9 )
    (*(void (**)(__int32, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1005, 0, 0);
  return 1;
}

// 0x0043E520
int UIListBox::GetItemCount(UIListBox **this)
{
  gbRefObject *v2; // ecx
  int result; // eax

  sub_43F360(this);
  v2 = (gbRefObject *)*((_DWORD *)this + 286);
  *((_DWORD *)this + 108) = 0;
  if ( v2 )
  {
    v2->Release();
    *((_DWORD *)this + 286) = 0;
  }
  UIWnd::UpdateChildren((UIWnd *)this);
  return result;
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
int UIListBox::SetItemOffset(char *Source, int a3)
{
  UIListBox *v4; // eax
  char *SubItemInfo; // edi
  gbTexture *v6; // eax
  _PlugInfo *v7; // ebp
  int v8; // ebx
  PtrArray *m_column; // edi
  UIListBox *v10; // eax
  void *v11; // eax
  _DWORD *m_pData; // ecx
  int v13; // eax
  int Child; // eax
  __int32 Green; // ecx
  int v17; // [esp+10h] [ebp-814h] BYREF
  OpenBaseFile v18; // [esp+14h] [ebp-810h] BYREF
  char pExceptionObject[1024]; // [esp+18h] [ebp-80Ch] BYREF
  char ArgList[1024]; // [esp+418h] [ebp-40Ch] BYREF
  int v21; // [esp+820h] [ebp-4h]

  v4 = (UIListBox *)operator new(0x48u);
  if ( !v4 || (SubItemInfo = (char *)v4->GetSubItemInfo()) == 0 )
  {
    qmemcpy(
      pExceptionObject,
      Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Ui, 260),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  if ( a3 )
  {
    OpenBaseFile::OpenBaseFile(&v18);
    v21 = 0;
    v6 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                        g_Input.KeyInfo[177].Data,
                        Source);
    *(_DWORD *)SubItemInfo = v6;
    if ( v6 )
      v6->LoadTexture(1);
    v21 = -1;
    OpenNULLFile::OpenNULLFile((OpenNULLFile **)&v18);
  }
  else
  {
    strncpy(SubItemInfo + 4, Source, 0x40u);
    *((_DWORD *)SubItemInfo + 17) = this->m_fontcolor.Blue;
  }
  v7 = (_PlugInfo *)this->m_scrollbar.m_texarrayInfo[4];
  PtrArray::SetAt((PtrArray *)&this->m_scrollbar.m_texarrayInfo[3], (int)v7, (int)SubItemInfo);
  v8 = 1;
  if ( (int)this->m_scrollbar.m_texarray.m_ptex[3] > 1 )
  {
    m_column = (PtrArray *)this->m_column;
    do
    {
      v10 = (UIListBox *)operator new(0x48u);
      if ( !v10 || (v11 = v10->GetSubItemInfo()) == 0 )
      {
        qmemcpy(
          pExceptionObject,
          Logger::FormatException((Logger *)ArgList, aCNewFailed, aDProjectPal3Ui, 282),
          sizeof(pExceptionObject));
        _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
      }
      m_column->SetAt(m_column->m_nSize, (int)v11);
      ++v8;
      m_column = (PtrArray *)((char *)m_column + 84);
    }
    while ( v8 < (int)this->m_scrollbar.m_texarray.m_ptex[3] );
  }
  sub_43F520(this);
  m_pData = (_DWORD *)this->m_column[6].items.m_pData;
  v17 = 1;
  sub_5372D0((int)&this->m_column[6].head[56], m_pData, 1u, &v17);
  v13 = *(_DWORD *)&this->m_column[6].head[60];
  if ( v13 )
  {
    if ( ((int)this->m_column[6].items.m_pData - v13) >> 2 )
    {
      if ( this->m_column[5].items.m_nGrowBy == -1 )
      {
        sub_43F6D0(this, 0);
        if ( this->m_column[5].items.m_nGrowBy != -1 )
        {
          Child = this->CreateChild();
          Green = this->m_wndcolor.Green;
          if ( Green )
            (*(void (**)(__int32, int, __int32, int))(*(_DWORD *)Green + 24))(
              Green,
              1006,
              this->m_fontcolor.Red,
              Child);
        }
      }
    }
  }
  return (int)v7;
}

// 0x0043E7D0
struct gbVFileSystem * UIListBox::SetMouseMoveSel(int a2, int a3, char *Source, int a5)
{
  int v5; // esi
  gbTexture *v6; // eax

  if ( a3 < 0 || a3 >= (int)this->m_scrollbar.m_texarrayInfo[21 * a2 + 4] )
    v5 = 0;
  else
    v5 = *(&this->m_scrollbar.m_texarrayInfo[21 * a2 + 3]->filepos + a3);
  if ( !a5 )
    return (struct gbVFileSystem *)strncpy((char *)(v5 + 4), Source, 0x40u);
  OpenBaseFile::OpenBaseFile((OpenBaseFile *)&a2);
  v6 = (gbTexture *)(*(int (**)(int, char *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                      g_Input.KeyInfo[177].Data,
                      Source);
  *(_DWORD *)v5 = v6;
  if ( v6 )
    v6->LoadTexture(1);
  return OpenNULLFile::OpenNULLFile((OpenNULLFile **)&a2);
}

// 0x0043E8A0
int UIListBox::EnableRow()
{
  int result; // eax
  unsigned int *v3; // eax
  int v4; // ebp
  _PlugInfo **v5; // eax
  int m_nMaxSize; // ebx
  int v7; // edi
  gbTexture **v8; // ecx
  int v9; // eax
  bool v10; // cc
  int Child; // eax
  int v12; // edx
  bool v13; // cl
  __int32 Alpha; // eax
  __int32 Color; // ecx
  int v16; // ebp
  int ColorQuadFmt; // ebx
  int v18; // ecx
  int v19; // eax
  int v20; // ebx
  void *m_pData; // edi
  int v22; // edx
  int v23; // edx
  int v24; // ecx
  __int32 v25; // edi
  int v26; // edi
  int v27; // [esp-24h] [ebp-88h]
  int v28; // [esp-1Ch] [ebp-80h]
  _PlugInfo **v29; // [esp+4h] [ebp-60h]
  int v30; // [esp+8h] [ebp-5Ch]
  int v31; // [esp+Ch] [ebp-58h]
  int v32[3]; // [esp+10h] [ebp-54h] BYREF
  __int32 Blue; // [esp+1Ch] [ebp-48h]
  struct gbTextureArray v34; // [esp+20h] [ebp-44h] BYREF

  result = this->m_rect.top;
  if ( result )
  {
    if ( *(_DWORD *)&this->m_column[6].head[8] )
    {
      v34.pTexPt[0] = *(gbTexture **)&this->m_column[6].head[8];
      v3 = (unsigned int *)*(unsigned int **)&this->m_column[6].head[12];
      v34.nTex = 1;
      _TextureLib_Data::SetLibFolder(
        &this->m_fontcolor.Alpha,
        (unsigned int *)&this->m_fontcolor.Green,
        &v34,
        0x114u,
        v3,
        COERCE_FLOAT(1));
    }
    else if ( this->m_childs.m_pData )
    {
      _TextureLib_Data::~_TextureLib_Data(
        this->m_fontcolor.Alpha,
        this->m_fontcolor.Color,
        this->m_wndcolor.ColorQuadFmt,
        this->m_wndcolor.Blue,
        (float *)&g_GameData_0._data[12992]);
    }
    v4 = *(_DWORD *)&this->m_column[6].head[44] + this->m_fontcolor.Alpha + 8;
    v30 = this->SetDefaultSel();
    v31 = 0;
    if ( (int)this->m_scrollbar.m_texarray.m_ptex[3] > 0 )
    {
      v5 = &this->m_scrollbar.m_texarrayInfo[4];
      v29 = &this->m_scrollbar.m_texarrayInfo[4];
      do
      {
        m_nMaxSize = this->m_column[5].items.m_nMaxSize;
        v7 = this->m_fontcolor.Color + *(_DWORD *)&this->m_column[6].head[48] + 8;
        if ( m_nMaxSize < m_nMaxSize + v30 )
        {
          do
          {
            if ( m_nMaxSize >= (int)*v5 )
              break;
            v8 = m_nMaxSize < 0 ? 0 : (gbTexture **)*(&(*(v5 - 1))->filepos + m_nMaxSize);
            if ( *v8 )
            {
              v34.pTexPt[0] = *v8;
              v32[2] = v4 + 32;
              Blue = v7 + 32;
              v32[0] = v4;
              v32[1] = v7;
              v34.nTex = 1;
              v32->SetLibFolder((unsigned int *)&this->m_fontcolor.Green, &v34, 0x114u, 0, COERCE_FLOAT(1));
            }
            else if ( *(_DWORD *)(*(_DWORD *)&this->m_column[6].head[60] + 4 * m_nMaxSize) )
            {
              v9 = m_nMaxSize < 0 || m_nMaxSize >= (int)this->m_scrollbar.m_texarrayInfo[4]
                 ? 0
                 : *(&this->m_scrollbar.m_texarrayInfo[3]->filepos + m_nMaxSize);
              UIRenderQuad(v4, v7, (int)(v8 + 1), (_BYTE *)(v9 + 68), this->m_column[5].items.m_nSize);
            }
            else
            {
              UIRenderQuad(v4, v7, (int)(v8 + 1), &g_GameData_0._data[12992], this->m_column[5].items.m_nSize);
            }
            v7 += (int)this->m_column[5].items.m_pData;
            ++m_nMaxSize;
            v5 = v29;
          }
          while ( m_nMaxSize < v30 + this->m_column[5].items.m_nMaxSize );
        }
        v4 += (int)v5[3];
        v5 += 21;
        v10 = ++v31 < (int)this->m_scrollbar.m_texarray.m_ptex[3];
        v29 = v5;
      }
      while ( v10 );
    }
    Child = this->CreateChild();
    v12 = *(_DWORD *)&this->m_column[6].head[52];
    if ( v12 )
    {
      v13 = this->m_column[5].items.m_nGrowBy != -1;
      if ( this->m_column[5].items.m_nGrowBy == -1 || !*(_DWORD *)(*(_DWORD *)&this->m_column[6].head[60] + 4 * Child) )
        return this->GetID();
    }
    else
    {
      v13 = this->m_column[5].width != -1;
    }
    if ( v13 )
    {
      Alpha = this->m_fontcolor.Alpha;
      Color = this->m_fontcolor.Color;
      v16 = *(_DWORD *)&this->m_column[6].head[48];
      ColorQuadFmt = this->m_wndcolor.ColorQuadFmt;
      Blue = this->m_wndcolor.Blue;
      v18 = v16 + Color;
      v19 = *(_DWORD *)&this->m_column[6].head[44] + Alpha + 4;
      v20 = -2 - *(_DWORD *)&this->m_column[6].head[36] + ColorQuadFmt;
      m_pData = (void *)this->m_column[5].items.m_pData;
      v22 = v12 ? this->m_column[5].items.m_nGrowBy : this->m_column[5].width - this->m_column[5].items.m_nMaxSize;
      v23 = v18 + (_DWORD)m_pData * v22 + 8;
      v24 = (int)m_pData + v23 - 2;
      v25 = this->m_wndcolor.Blue;
      if ( v24 > v25 )
        v24 = this->m_wndcolor.Blue;
      if ( v23 >= this->m_fontcolor.Color && v24 <= v25 )
      {
        if ( *(_DWORD *)&this->m_column[6].head[16] )
        {
          v34.pTexPt[0] = *(gbTexture **)&this->m_column[6].head[16];
          v26 = *(_DWORD *)&this->m_column[6].head[24];
          v28 = v20 + *(_DWORD *)&this->m_column[6].head[32];
          v27 = v19 + *(_DWORD *)&this->m_column[6].head[28];
          v34.nTex = 1;
          UIDestorySystem(v27, v23 + v26, v28, v26 + v24, (int *)&this->m_column[6].head[40], &v34);
          return this->GetID();
        }
        v19->~_TextureLib_Data(v23, v20, v24, (float *)&this->m_pfather);
      }
    }
    return this->GetID();
  }
  return result;
}

// 0x0043EBA0
int UIListBox::SetDefaultSel()
{
  return (this->m_wndcolor.Blue - this->m_fontcolor.Color) / (__int32)this->m_column[5].items.m_pData;
}
