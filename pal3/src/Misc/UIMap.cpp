#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIMap.h"

// Forward declarations for unnamed functions
int sub_442000(void); // from annotations
int sub_442100(void); // from annotations
int sub_445AA0(void); // from annotations
void * sub_445EA0(void); // from annotations
int sub_445F60(unsigned int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_445FE0(void *a2); // from annotations

// 0x004410F0
int * UIMap::ctor()
{
  sub_445AA0();
  ((UI3DCtrl *)&this->m_screenWidth)->ctor_D830();
  sub_445EA0();
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 42) = 100;
  *((_DWORD *)this + 43) = 0;
  *((_DWORD *)this + 40) = 5;
  LOBYTE(this->m_mapwidth) = 0;
  BYTE1(this->m_mapwidth) = 0;
  *((_DWORD *)this + 47) = 10;
  *((_DWORD *)this + 39) = 16;
  *((_DWORD *)this + 44) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 75) = 0;
  *((_DWORD *)this + 84) = 0;
  memset((char *)this + 260, 0, 0x28u);
  return (int *)this;
}

// 0x004412C0
char * UIMap::Create(int id, void *pRect, int parent, char *pszTexPath, int nVal, char bAtlas)
{
  char *result; // eax
  LONG right; // ecx
  int v10; // eax

  if ( parent )
  {
    result = pszTexPath;
    if ( pszTexPath )
    {
      ((CCBUI *)this)->LoadTextureSequence((gbVFileSystem *)pszTexPath, bAtlas);
      ((PalScript *)this)->Create(id, (tagRECT *)pRect, parent);
      (*(void ( **)(int *, _DWORD, tagRECT *, char *, int, UIMap *))(this->m_screenWidth + 28))(
        &this->m_screenWidth,
        0,
        &this->m_rect,
        "ui\\flex\\scroll.tga",
        1,
        this);
      sub_445FA0(&this->m_screenWidth);
      ((CScreenMode *)&this->m_screenWidth)->SetPosition(39,   32);
      (*(void ( **)(int *, _DWORD))this->m_screenWidth)(&this->m_screenWidth, 0);
      sub_442100();
      right = this->m_rect.right;
      v10 = *((_DWORD *)this + 79) + 16;
      *((_DWORD *)this + 87) = 32;
      *((_DWORD *)this + 45) = v10;
      *((_DWORD *)this + 44) = v10;
      result = (char *)this->m_rect.left;
      *((_DWORD *)this + 85) = 0;
      *((_DWORD *)this + 86) = right - (_DWORD)result;
    }
  }
  return result;
}

// 0x004414F0
void UIMap::Render()
{
  int v2; // eax
  unsigned int v3; // edi
  int v4; // eax
  unsigned int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  LONG left; // eax
  int v12; // edx
  LONG v13; // eax
  LONG v14; // ecx
  int v15; // eax
  int v16; // eax
  char pszFolder[4]; // [esp+0x10] [ebp-0x54] BYREF
  LONG top; // [esp+0x14] [ebp-0x50]
  LONG right; // [esp+0x18] [ebp-0x4C]
  LONG bottom; // [esp+0x1C] [ebp-0x48]
  int v21; // [esp+0x20] [ebp-0x44] BYREF
  int v22; // [esp+0x60] [ebp-0x4]

  if ( this->m_bvisible )
  {
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
    sub_445F60(3u);
    *(_DWORD *)pszFolder = *((_DWORD *)this + 76);
    top = *((_DWORD *)this + 77);
    right = *((_DWORD *)this + 78);
    v2 = *((_DWORD *)this + 40);
    bottom = *((_DWORD *)this + 79);
    if ( v2 )
    {
      v3 = 4;
    }
    else
    {
      v3 = 5;
      if ( BYTE1(this->m_mapwidth) )
        v3 = 6;
    }
    v4 = sub_445F60(v3);
    if ( v4 )
    {
      v21 = v4;
      v22 = 1;
      ((TextureLibDataBase *)&v21)->SetLibFolder(pszFolder);
    }
    *(_DWORD *)pszFolder = *((_DWORD *)this + 80);
    top = *((_DWORD *)this + 81);
    right = *((_DWORD *)this + 82);
    bottom = *((_DWORD *)this + 83);
    if ( *((_DWORD *)this + 40) == 1 )
    {
      v5 = 8;
      if ( BYTE1(this->m_mapwidth) )
        v5 = 9;
    }
    else
    {
      v5 = 7;
    }
    v6 = sub_445F60(v5);
    if ( v6 )
    {
      v21 = v6;
      v22 = 1;
      ((TextureLibDataBase *)pszFolder)->SetLibFolder(pszFolder);
    }
    if ( *((_DWORD *)this + 42) - *((_DWORD *)this + 41) > 0 )
    {
      v7 = *((_DWORD *)this + 85);
      v8 = v7 + *((_DWORD *)this + 79);
      if ( *((_DWORD *)this + 45) <= v8 )
      {
        *((_DWORD *)this + 45) = v8;
        *((_DWORD *)this + 43) = 0;
      }
      v9 = *((_DWORD *)this + 87);
      v10 = *((_DWORD *)this + 81) - v9 - v7;
      if ( *((_DWORD *)this + 45) >= v10 )
        *((_DWORD *)this + 45) = v10;
      left = this->m_rect.left;
      top = this->m_rect.top;
      right = this->m_rect.right;
      bottom = this->m_rect.bottom;
      v12 = *((_DWORD *)this + 86);
      *(_DWORD *)pszFolder = *((_DWORD *)this + 84) + left;
      v13 = *((_DWORD *)this + 45);
      right = *(_DWORD *)pszFolder + v12;
      top = v13;
      v14 = v13 + v9;
      v15 = *((_DWORD *)this + 40);
      bottom = v14;
      if ( v15 == 2 )
      {
        v16 = sub_445F60(1u);
        if ( LOBYTE(this->m_mapwidth) )
          v16 = sub_445F60(2u);
      }
      else
      {
        v16 = sub_445F60(0);
      }
      if ( v16 )
      {
        v21 = v16;
        v22 = 1;
        ((TextureLibDataBase *)pszFolder)->SetLibFolder(pszFolder);
      }
    }
  }
}

// 0x00441730
BOOL UIMap::ProcessHitTest(int nVal, int nVal2)
{
  int v5; // eax
  int v6; // ecx
  int v7; // ebp
  int v8; // kr00_4
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  LONG y; // ecx
  LONG v14; // eax
  bool v15; // cc
  int v16; // ebx
  int v17; // ecx
  double v18; // st7
  int v19; // ecx
  double v20; // st7
  int v21; // eax
  int v22; // eax
  int v23; // eax
  double v24; // st7
  int v25; // eax
  int v26; // edi
  int v27; // eax
  double v28; // st7
  double v29; // st7
  int v30; // eax
  int v31; // edi
  int v32; // eax
  const RECT *v33; // eax
  int v34; // ecx
  int v35; // edx
  int v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  UIWnd *m_pfather; // ecx
  POINT v42; // [esp-0x10] [ebp-0x40]
  int v43; // [esp+0xC] [ebp-0x24]
  int v44; // [esp+0xC] [ebp-0x24]
  int v45; // [esp+0xC] [ebp-0x24]
  struct tagPOINT Point; // [esp+0x14] [ebp-0x1C] BYREF
  BOOL v47; // [esp+0x24] [ebp-0xC]
  POINT pt; // [esp+0x28] [ebp-0x8] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  if ( !nVal2 )
    return ((UIListBox *)this)->Update(nVal, 0);
  ((GRPinput *)&g_Input)->GetCursorPos();
  v5 = ((ArcSceneMonster *)this)->HitTest((unsigned int *)&pt);
  v6 = *((_DWORD *)this + 81);
  v47 = v5 != 5;
  v7 = *((_DWORD *)this + 41);
  v8 = *((_DWORD *)this + 87);
  v9 = *((_DWORD *)this + 79);
  *((_DWORD *)this + 40) = v5;
  v10 = v6 - v9;
  v43 = *((_DWORD *)this + 42);
  v11 = v43 - v7;
  v12 = v10 - v8 / 2;
  LOBYTE(this->m_mapwidth) = 0;
  Point.x = v43 - v7;
  if ( v43 - v7 <= 0 || v12 <= 0 )
    *((_DWORD *)this + 46) = 0;
  else
    *((float *)this + 46) = (double)v12 / (double)Point.x;
  switch ( v5 )
  {
    case 0:
      if ( g_Input.KeyInfo[0].PressTime != 1 )
        goto LABEL_57;
      v19 = *((_DWORD *)this + 43);
      BYTE1(this->m_mapwidth) = 1;
      *((_DWORD *)this + 43) = v19 - 1;
      if ( v19 - 1 <= v7 )
        *((_DWORD *)this + 43) = v7;
      if ( *((_DWORD *)this + 43) >= v43 )
        *((_DWORD *)this + 43) = v43;
      v20 = (double)*((int *)this + 45) - *((float *)this + 46);
      goto LABEL_56;
    case 1:
      if ( g_Input.KeyInfo[0].PressTime != 1 )
        goto LABEL_57;
      v17 = *((_DWORD *)this + 43);
      BYTE1(this->m_mapwidth) = 1;
      *((_DWORD *)this + 43) = v17 + 1;
      if ( v17 + 1 <= v7 )
        *((_DWORD *)this + 43) = v7;
      if ( *((_DWORD *)this + 43) >= v43 )
        *((_DWORD *)this + 43) = v43;
      v18 = (double)*((int *)this + 45);
      goto LABEL_55;
    case 2:
      if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 )
        goto LABEL_57;
      LOBYTE(this->m_mapwidth) = 1;
      if ( v11 <= 0 )
        goto LABEL_57;
      y = pt.y;
      v14 = *((_DWORD *)this + 44);
      v15 = pt.y < v14;
      *((_DWORD *)this + 45) = pt.y - v8 / 2;
      if ( v15 )
      {
        Point.x = v14 - y;
        if ( (double)(v14 - y) / *((float *)this + 46) >= 1.0 )
        {
          v16 = 1;
          --*((_DWORD *)this + 43);
          goto LABEL_20;
        }
      }
      else
      {
        Point.x = y - v14;
        if ( (double)(y - v14) / *((float *)this + 46) >= 1.0 )
        {
          v16 = 1;
          ++*((_DWORD *)this + 43);
          goto LABEL_20;
        }
      }
      v16 = 0;
LABEL_20:
      if ( *((_DWORD *)this + 43) <= v7 )
        *((_DWORD *)this + 43) = v7;
      if ( *((_DWORD *)this + 43) >= v43 )
        *((_DWORD *)this + 43) = v43;
      *((_DWORD *)this + 44) = sub_442000();
      goto LABEL_58;
    case 3:
      if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 || v11 <= 0 )
        goto LABEL_57;
      v21 = *((_DWORD *)this + 43) - 1;
      *((_DWORD *)this + 43) = v21;
      if ( v21 <= v7 )
        *((_DWORD *)this + 43) = v7;
      if ( *((_DWORD *)this + 43) >= v43 )
        *((_DWORD *)this + 43) = v43;
      ((GRPinput *)&g_Input)->GetCursorPos();
      v44 = *((_DWORD *)this + 45);
      Point.x = v44 - Point.y;
      if ( (double)(v44 - Point.y) < *((float *)this + 46) )
      {
        v16 = 1;
        *((_DWORD *)this + 45) = Point.y;
        goto LABEL_58;
      }
      v20 = (double)v44 - *((float *)this + 46);
      goto LABEL_56;
    case 4:
      if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 || v11 <= 0 )
        goto LABEL_57;
      v22 = *((_DWORD *)this + 43) + 1;
      *((_DWORD *)this + 43) = v22;
      if ( v22 <= v7 )
        *((_DWORD *)this + 43) = v7;
      if ( *((_DWORD *)this + 43) >= v43 )
        *((_DWORD *)this + 43) = v43;
      ((GRPinput *)&g_Input)->GetCursorPos();
      v45 = *((_DWORD *)this + 45);
      Point.x = Point.y - v45;
      if ( (double)(Point.y - v45) >= *((float *)this + 46) )
      {
        v18 = (double)v45;
LABEL_55:
        v20 = v18 + *((float *)this + 46);
LABEL_56:
        *((_DWORD *)this + 45) = (__int64)v20;
        v16 = 1;
      }
      else
      {
        v16 = 1;
        *((_DWORD *)this + 45) = Point.y;
      }
LABEL_58:
      v23 = *((_DWORD *)this + 40);
      if ( !v23 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
      {
        v24 = *(float *)&nVal + *((float *)this + 75);
        *((float *)this + 75) = v24;
        if ( v24 <= 0.5 )
          goto LABEL_78;
        v25 = *((_DWORD *)this + 41);
        v26 = *((_DWORD *)this + 43) - 1;
        BYTE1(this->m_mapwidth) = 1;
        *((_DWORD *)this + 43) = v26;
        if ( v26 <= v25 )
          *((_DWORD *)this + 43) = v25;
        v27 = *((_DWORD *)this + 42);
        if ( *((_DWORD *)this + 43) >= v27 )
          *((_DWORD *)this + 43) = v27;
        v28 = (double)*((int *)this + 45) - *((float *)this + 46);
        goto LABEL_66;
      }
      if ( v23 == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1 )
      {
        v29 = *(float *)&nVal + *((float *)this + 75);
        *((float *)this + 75) = v29;
        if ( v29 > 0.5 )
        {
          v30 = *((_DWORD *)this + 41);
          v31 = *((_DWORD *)this + 43) + 1;
          BYTE1(this->m_mapwidth) = 1;
          *((_DWORD *)this + 43) = v31;
          if ( v31 <= v30 )
            *((_DWORD *)this + 43) = v30;
          v32 = *((_DWORD *)this + 42);
          if ( *((_DWORD *)this + 43) >= v32 )
            *((_DWORD *)this + 43) = v32;
          v28 = (double)*((int *)this + 45) + *((float *)this + 46);
LABEL_66:
          *((_DWORD *)this + 45) = (__int64)v28;
          v16 = 1;
        }
      }
      else
      {
        if ( (g_Input.KeyInfo[0].Data & 0xF) != 1 )
          BYTE1(this->m_mapwidth) = 0;
        *((_DWORD *)this + 75) = 0;
      }
LABEL_78:
      if ( this->m_pfather && (v42 = pt, v33 = (const RECT *)sub_445FE0(&Point), PtInRect(v33, v42))
        || PtInRect(&this->m_rect, pt) )
      {
        v34 = *((_DWORD *)this + 42);
        v35 = *(_DWORD *)&g_Input.MouseState[8] / 120;
        v36 = *((_DWORD *)this + 41);
        if ( v34 - v36 > 0 )
        {
          if ( v35 )
          {
            v16 = 1;
            v37 = *((_DWORD *)this + 43) - v35;
            *((_DWORD *)this + 43) = v37;
            if ( v37 <= v36 )
              *((_DWORD *)this + 43) = v36;
            if ( *((_DWORD *)this + 43) >= v34 )
              *((_DWORD *)this + 43) = v34;
            v38 = sub_442000();
            *((_DWORD *)this + 45) = v38;
            *((_DWORD *)this + 44) = v38;
          }
        }
      }
      v39 = *((_DWORD *)this + 41);
      if ( *((_DWORD *)this + 43) <= v39 )
        *((_DWORD *)this + 43) = v39;
      v40 = *((_DWORD *)this + 42);
      if ( *((_DWORD *)this + 43) >= v40 )
        *((_DWORD *)this + 43) = v40;
      if ( v16 )
      {
        m_pfather = this->m_pfather;
        if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1005,
// [VFTABLE]   this->m_id,
// [VFTABLE]   *((_DWORD *)this + 43));
      }
      return ((UIListBox *)this)->Update(nVal, nVal2) || v47;
    default:
LABEL_57:
      v16 = 0;
      goto LABEL_58;
  }
}

// 0x004420C0
int UIMap::OnMessage(int nVal, int nVal2, int nVal3)
{
  if ( nVal == 1022 )
    sub_445FA0(&this->m_screenWidth);
  return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
}
