#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_YXXX.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

void CopyRoleData(int pDst, int pSrc); // from annotations

// Unnamed globals (extern)
extern char byte_ABE000;
extern int dword_56B884;
extern const char * off_56B898;

// 0x00459970
int UITitle_YXXX::LayoutWidgets()
{
  char *v2; // ebx
  int result; // eax
  void ( ***p_m_childs)(void *, int); // ebx
  unsigned int m_needscriptdel; // eax
  char *v6; // [esp+0x30] [ebp-0x14]
  char *v7; // [esp+0x30] [ebp-0x14]
  char *v8; // [esp+0x30] [ebp-0x14]
  char *v9; // [esp+0x30] [ebp-0x14]
  char *v10; // [esp+0x30] [ebp-0x14]
  char *v11; // [esp+0x30] [ebp-0x14]
  char *v12; // [esp+0x30] [ebp-0x14]
  char *v13; // [esp+0x30] [ebp-0x14]
  unsigned __int16 v14; // [esp+0x48] [ebp+0x4]

  v2 = (char *)this->m_OutFrameT.m_id + this->m_OutFrameT.m_childs.m_nSize + 32;
  HIWORD(this->m_OutFrameT.pDebugTex) = v14;
  result = v14;
  switch ( v14 )
  {
    case 0u:
      sub_445FA0(&this->m_ZZRY.m_disablepicInfo);
      ((void ( *)(_PlugInfo **, int))this->m_ZZRY.m_disablepicInfo->filepos)(
        &this->m_ZZRY.m_disablepicInfo,
        1);
      sub_445FA0(&this->m_OutFrameL.m_benable);
      (*(void ( **)(int *, int))this->m_OutFrameL.m_benable)(&this->m_OutFrameL.m_benable, 1);
      v6 = &v2[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0(&this->m_XGWZ.m_disablepicInfo);
      ((void ( *)(_PlugInfo **, int))this->m_XGWZ.m_disablepicInfo->filepos)(
        &this->m_XGWZ.m_disablepicInfo,
        1);
      sub_445FA0(&this->m_OutFrameB.m_bcreateok);
      (*(void ( **)(int *, int))this->m_OutFrameB.m_bcreateok)(&this->m_OutFrameB.m_bcreateok, 1);
      v7 = &v6[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0((char *)&this->m_WordBk + 180);
      (**((void ( ***)(char *, int))&this->m_WordBk + 45))((char *)&this->m_WordBk + 180, 1);
      sub_445FA0(&this->m_background.m_childs.m_nSize);
      (*(void ( **)(int *, int))this->m_background.m_childs.m_nSize)(
        &this->m_background.m_childs.m_nSize,
        1);
      v8 = &v7[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0((char *)this + 2608);
      (**((void ( ***)(char *, int))this + 652))((char *)this + 2608, 1);
      p_m_childs = (void ( ***)(void *, int))&this->m_title.m_childs;
      goto LABEL_5;
    case 1u:
    case 3u:
      sub_445FA0(&this->m_exit.m_disablepicInfo);
      ((void ( *)(_PlugInfo **, int))this->m_exit.m_disablepicInfo->filepos)(
        &this->m_exit.m_disablepicInfo,
        1);
      sub_445FA0(&this->m_OutFrameL.m_benable);
      (*(void ( **)(int *, int))this->m_OutFrameL.m_benable)(&this->m_OutFrameL.m_benable, 1);
      v11 = &v2[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0(&this->m_ZZRY.m_disablepicInfo);
      ((void ( *)(_PlugInfo **, int))this->m_ZZRY.m_disablepicInfo->filepos)(
        &this->m_ZZRY.m_disablepicInfo,
        1);
      sub_445FA0(&this->m_OutFrameB.m_bcreateok);
      (*(void ( **)(int *, int))this->m_OutFrameB.m_bcreateok)(&this->m_OutFrameB.m_bcreateok, 1);
      v12 = &v11[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0(&this->m_XGWZ.m_disablepicInfo);
      ((void ( *)(_PlugInfo **, int))this->m_XGWZ.m_disablepicInfo->filepos)(
        &this->m_XGWZ.m_disablepicInfo,
        1);
      sub_445FA0(&this->m_background.m_childs.m_nSize);
      (*(void ( **)(int *, int))this->m_background.m_childs.m_nSize)(
        &this->m_background.m_childs.m_nSize,
        1);
      v13 = &v12[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0((char *)&this->m_WordBk + 180);
      (**((void ( ***)(char *, int))&this->m_WordBk + 45))((char *)&this->m_WordBk + 180, 1);
      sub_445FA0(&this->m_title.m_childs);
      (*(void ( **)(PtrArray *, int))this->m_title.m_childs.m_pData)(&this->m_title.m_childs, 1);
      v8 = &v13[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0((char *)this + 2608);
      (**((void ( ***)(char *, int))this + 652))((char *)this + 2608, 1);
      p_m_childs = (void ( ***)(void *, int))&this->m_exit.m_rect.bottom;
      goto LABEL_5;
    case 2u:
      sub_445FA0(&this->m_exit.m_disablepicInfo);
      ((void ( *)(_PlugInfo **, int))this->m_exit.m_disablepicInfo->filepos)(
        &this->m_exit.m_disablepicInfo,
        1);
      sub_445FA0(&this->m_OutFrameL.m_benable);
      (*(void ( **)(int *, int))this->m_OutFrameL.m_benable)(&this->m_OutFrameL.m_benable, 1);
      v9 = &v2[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0(&this->m_XGWZ.m_disablepicInfo);
      ((void ( *)(_PlugInfo **, int))this->m_XGWZ.m_disablepicInfo->filepos)(
        &this->m_XGWZ.m_disablepicInfo,
        1);
      sub_445FA0(&this->m_OutFrameB.m_bcreateok);
      (*(void ( **)(int *, int))this->m_OutFrameB.m_bcreateok)(&this->m_OutFrameB.m_bcreateok, 1);
      v10 = &v9[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0((char *)&this->m_WordBk + 180);
      (**((void ( ***)(char *, int))&this->m_WordBk + 45))((char *)&this->m_WordBk + 180, 1);
      sub_445FA0(&this->m_background.m_childs.m_nSize);
      (*(void ( **)(int *, int))this->m_background.m_childs.m_nSize)(
        &this->m_background.m_childs.m_nSize,
        1);
      v8 = &v10[this->m_OutFrameT.m_childs.m_nSize];
      sub_445FA0((char *)this + 2608);
      (**((void ( ***)(char *, int))this + 652))((char *)this + 2608, 1);
      p_m_childs = (void ( ***)(void *, int))&this->m_title.m_childs;
LABEL_5:
      sub_445FA0(p_m_childs);
      (**p_m_childs)(p_m_childs, 1);
      m_needscriptdel = this->m_OutFrameT.m_childs.m_needscriptdel;
      this->m_OutFrameT.m_id = v8;
      this->m_OutFrameT.m_wndcolor.Color = m_needscriptdel;
      this->m_OutFrameT.m_rect.top = (LONG)(v8 + 11);
      this->m_OutFrameT.m_rect.left = m_needscriptdel + 68;
      result = sub_445FA0(&this->m_OutFrameR.pDebugTex);
      break;
    default:
      return result;
  }
  return result;
}

// 0x0047DCA0
void UITitle_YXXX::Create()
{
  this->rc.top = 0;
  this->m_OutFrameT.m_wndcolor.Color = 800;
  this->m_OutFrameT.m_id = (void *)600;
  this->m_OutFrameR.m_pbk2 = 0;
  this->m_OutFrameR.m_mouseoff = 0;
  ((UITextArea *)&this->m_OutFrameR.m_FVF)->InitAfterClear();
  sub_4422E0(&this->m_OutFrameB.m_rect);
  ((ARC_PlayerAtt *)((char *)&this->m_WordBk + 376))->Refresh();
}

// 0x0047DD90
void UITitle_YXXX::_UITitle_YXXX()
{
  ((UIRoleDialog *)((char *)&this->m_WordBk + 376))->_UIRoleDialog();
  ((UIFrameWnd *)&this->m_OutFrameB.m_rect)->UIFrameWnd::_UIFrameWnd();
  ((UITextArea *)&this->m_OutFrameR.m_FVF)->Destroy();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0047DE40
void UITitle_YXXX::Init()
{
  void *Color; // eax
  void *m_id; // ecx
  char *v4; // eax
  char *v5; // ebx
  int *v6; // ebp
  gbColorQuad *p_m_wndcolor; // esi
  _DWORD v8[4]; // [esp+0x20] [ebp-0x20] BYREF
  int nVal[4]; // [esp+0x30] [ebp-0x10] BYREF

  Color = (void *)this->m_OutFrameT.m_wndcolor.Color;
  m_id = this->m_OutFrameT.m_id;
// [VFTABLE] this->m_OutFrameT.__vftable = Color;
  this->m_OutFrameT.m_fontcolor.Color = (unsigned int)m_id;
  this->rc.bottom = 0;
  this->rc.right = 0;
// [VFTABLE] ((UIListBox *)this)->SetSelTexture(-1, 0, 0, (int)this->m_OutFrameT.__vftable, this->m_OutFrameT.m_fontcolor.Color, 0);
  this->m_OutFrameR.m_ppicInfo = (_PlugInfo *)170;
  this->m_OutFrameR.m_ppic = (gbTexture *)310;
  this->m_OutFrameR.m_disablepic = (gbTexture *)468;
  this->m_OutFrameR.m_disablepicInfo = (_PlugInfo *)430;
  ((UINote *)&this->m_OutFrameR.m_FVF)->Create(-1430519792, (int)&this->m_OutFrameR.m_ppic, (int)this, "UI\\Flex\\Note");
  (*(void ( **)(int *, _DWORD))this->m_OutFrameR.m_FVF)(&this->m_OutFrameR.m_FVF, 0);
  v4 = &this->m_OutFrameR.m_ppicInfo->name[6];
  v8[0] = (char *)&this->m_OutFrameR.*((_DWORD *)m_ppic) + 10;
  v8[1] = v4;
  v8[2] = v8[0] + 136;
  v8[3] = v4 + 128;
  (*(void ( **)(tagRECT *, int, _DWORD *, UITitle_YXXX *))(this->m_OutFrameB.m_rect.left + 16))(
    &this->m_OutFrameB.m_rect,
    -1430519792,
    v8,
    this);
  ((UIScene *)&this->m_OutFrameB.m_rect)->SetShow(0);
  sub_446010(&this->m_OutFrameB.m_rect);
  (*(void ( **)(tagRECT *, _DWORD))this->m_OutFrameB.m_rect.left)(&this->m_OutFrameB.m_rect, 0);
  v5 = g_szRoleNameTable;
  v6 = dword_56B884;
  p_m_wndcolor = &this->m_background.m_wndcolor;
  do
  {
    (*(void ( **)(gbColorQuad *, int, _DWORD *, UITitle_YXXX *, char *, _DWORD, int))(p_m_wndcolor->Color + 28))(
      p_m_wndcolor,
      *v6,
      v8,
      this,
      "SubGame\\HockShop\\Control\\rawbtn",
      0,
      1);
    ((PalScript *)p_m_wndcolor)->OpenScript("SubGame\\HockShop\\Control\\unrawbtn.tga", 1);
    ((CScreenMode *)p_m_wndcolor)->SetTooltipText();
    p_m_wndcolor[27].Color = 3;
    p_m_wndcolor[26].Color = 1;
    p_m_wndcolor[52].Color = 1;
    (*(void ( **)(gbColorQuad *, _DWORD))p_m_wndcolor->Color)(p_m_wndcolor, 0);
    ++v6;
    v5 += 256;
    p_m_wndcolor += 86;
  }
  while ( (int)v6 < (int)&off_56B898 );
  nVal[1] = 200;
  nVal[0] = 300;
  nVal[2] = 500;
  nVal[3] = 300;
  ((ARC_PlayerAtt *)((char *)&this->m_WordBk + 376))->Create((int)&byte_ABE000, (int)nVal);
  ((UIItem *)((char *)&this->m_WordBk + 376))->SetData(18);
  *((_BYTE *)this + 3829) = 0;
  *((_BYTE *)this + 3830) = 0;
}

// 0x0047E3E0
int UITitle_YXXX::Update(int nVal, int nVal2)
{
  int v4; // ebp
  gbColorQuad *p_m_wndcolor; // edi
  gbColorQuad *v6; // edi
  int v7; // ebp

  if ( !*((_BYTE *)this + 3830) && *((_DWORD *)&this->m_OutFrameL + 39) == 2 )
  {
    (*(void ( **)(tagRECT *, int))this->m_OutFrameB.m_rect.left)(&this->m_OutFrameB.m_rect, 1);
    v4 = 0;
    p_m_wndcolor = &this->m_background.m_wndcolor;
    do
    {
      if ( *((_BYTE *)this + v4 + 3824) )
        (*(void ( **)(gbColorQuad *, int))p_m_wndcolor->Color)(p_m_wndcolor, 1);
      else
        (*(void ( **)(gbColorQuad *, _DWORD))p_m_wndcolor->Color)(p_m_wndcolor, 0);
      ++v4;
      p_m_wndcolor += 86;
    }
    while ( v4 < 5 );
    *((_BYTE *)this + 3830) = 1;
  }
  if ( ((UIParabolaCtrl *)(UIParabolaCtrl *)&this->m_WordBk + 94)->GetState() == 2 )
  {
    (*(void ( **)(int *, _DWORD))this->m_OutFrameR.m_FVF)(&this->m_OutFrameR.m_FVF, 0);
    (*(void ( **)(tagRECT *, _DWORD))this->m_OutFrameB.m_rect.left)(&this->m_OutFrameB.m_rect, 0);
    v6 = &this->m_background.m_wndcolor;
    v7 = 5;
    do
    {
      (*(void ( **)(gbColorQuad *, _DWORD))v6->Color)(v6, 0);
      v6 += 86;
      --v7;
    }
    while ( v7 );
    this->m_OutFrameR.m_mouseoff = 1;
    *((_BYTE *)this + 3829) = 0;
    *((_BYTE *)this + 3830) = 0;
  }
  if ( this->m_OutFrameR.m_mouseoff )
    ((CGameData *)&g_gamefrm)->Load(0);
  else
    ((UIListBox *)this)->Update(nVal, nVal2);
  return 1;
}

// 0x0047E4E0
int UITitle_YXXX::HandleMsgDLL(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  int v5; // edx
  int *v6; // eax

  if ( hinstDLL == (HINSTANCE)1000 )
    return DllMain((HINSTANCE)0x3E8, fdwReason, lpvReserved);
  if ( hinstDLL != (HINSTANCE)1001 )
    return ((PalScript *)this)->OnMessage((int)hinstDLL, fdwReason, (int)lpvReserved);
  v5 = 0;
  v6 = dword_56B884;
  while ( fdwReason != *v6 )
  {
    ++v6;
    ++v5;
    if ( (int)v6 >= (int)&off_56B898 )
      return 1;
  }
  ((ComposeUI *)this)->ProcessFrame(v5);
  return 1;
}

// 0x004AF770
int * UITitle_YXXX::CreateTitle(char *pszBuf, unsigned int dwVal, int nVal)
{
  char *Color; // esi
  unsigned int v5; // edi
  unsigned int v6; // ebx
  unsigned int v7; // ecx
  int v8; // edx
  unsigned int v9; // eax
  int v10; // ebp
  char *i; // esi
  int j; // esi
  char *v13; // esi
  char *v14; // eax
  char *v15; // ebp
  ArcLocaleRole *v16; // ebp
  ArcLocaleRole *k; // esi
  int *result; // eax
  unsigned int v19; // ecx
  int v20; // kr00_4
  char *v22; // ebp
  unsigned int v23; // esi
  unsigned int v24; // ebp
  char *v25; // esi
  char *v26; // ebp
  unsigned int v27; // edx
  int v28; // edi
  unsigned int v29; // ebp
  char *v30; // esi
  ArcLocaleRole *v31; // ebp
  int *v32; // edi
  int v33; // edx
  char *v34; // ebp
  char *v35; // esi
  UITitle_YXXX *v36; // [esp+0x10] [ebp-0xC]
  unsigned int v37; // [esp+0x14] [ebp-0x8]
  char *v38; // [esp+0x18] [ebp-0x4]
  char *pszBufa; // [esp+0x20] [ebp+0x4]
  char *pszBufb; // [esp+0x20] [ebp+0x4]
  unsigned int pszBufc; // [esp+0x20] [ebp+0x4]
  char *dwVala; // [esp+0x24] [ebp+0x8]
  int *dwValb; // [esp+0x24] [ebp+0x8]

  Color = (char *)this->m_wndcolor.Color;
  v5 = dwVal;
if ( ((char *)this->m_id - (char *)Color) / 24 >= dwVal )
  {
    result = (int *)((unsigned int)((unsigned __int64)(715827883LL * (Color - pszBuf)) >> 32) >> 31);
    if ( (Color - pszBuf) / 24 >= dwVal )
    {
      if ( dwVal )
      {
        v27 = 24 * dwVal;
        v28 = (int)&Color[-24 * dwVal];
        v29 = this->m_wndcolor.Color;
        pszBufc = 24 * dwVal;
        if ( (char *)v28 != Color )
        {
          do
          {
            CopyRoleData(v29, v28);
            v28 += 24;
            v29 += 24;
          }
          while ( (char *)v28 != Color );
          this = v36;
          v27 = 24 * dwVal;
        }
        result = (int *)this->m_wndcolor.Color;
        v30 = (char *)result - v27;
        if ( pszBuf != (char *)result - v27 )
        {
          v31 = (ArcLocaleRole *)(result + 2);
          v32 = (int *)(v30 + 8);
          while ( 1 )
          {
            v33 = *((_DWORD *)v30 - 6);
            v30 -= 24;
            v32 -= 6;
            dwValb = result - 6;
            v31 = (ArcLocaleRole *)((char *)v31 - 24);
            *(result - 6) = v33;
            LOBYTE(v31[-1].script) = *((_BYTE *)v32 - 4);
            result = ((ArcLocaleRole *)v31)->CalcPosition(v32);
            if ( v30 == pszBuf )
              break;
            result = dwValb;
          }
          this = v36;
          v27 = pszBufc;
        }
        v34 = &pszBuf[v27];
        v35 = pszBuf;
        if ( pszBuf != &pszBuf[v27] )
        {
          do
          {
            *(_DWORD *)v35 = *(_DWORD *)nVal;
            v35[4] = *(_BYTE *)(nVal + 4);
            result = ((ArcLocaleRole *)(v35 + 8))->CalcPosition((int *)(nVal + 8));
            v35 += 24;
          }
          while ( v35 != v34 );
          this = v36;
          v27 = pszBufc;
        }
        this->m_wndcolor.Color += v27;
      }
    }
    else
    {
      v22 = pszBuf;
      pszBufb = (char *)(24 * dwVal);
      if ( pszBuf != Color )
      {
        dwVala = &pszBuf[24 * dwVal];
        do
        {
          CopyRoleData((int)dwVala, (int)v22);
          v22 += 24;
          dwVala += 24;
        }
        while ( v22 != Color );
        this = v36;
      }
      v23 = this->m_wndcolor.Color;
      if ( v5 != (int)(v23 - (_DWORD)pszBuf) / 24 )
      {
        v24 = v5 - (int)(this->m_wndcolor.Color - (int)pszBuf) / 24;
        do
        {
          CopyRoleData(v23, nVal);
          v23 += 24;
          --v24;
        }
        while ( v24 );
      }
      result = (int *)v36;
      v25 = pszBuf;
      v26 = (char *)this->m_wndcolor.Color;
      if ( pszBuf != v26 )
      {
        do
        {
          *(_DWORD *)v25 = *(_DWORD *)nVal;
          v25[4] = *(_BYTE *)(nVal + 4);
          ((ArcLocaleRole *)(v25 + 8))->CalcPosition((int *)(nVal + 8));
          v25 += 24;
        }
        while ( v25 != v26 );
        result = (int *)v36;
      }
      result[2] += (int)pszBufb;
    }
  }
  else
  {
    v6 = this->m_fontcolor.Color;
    if ( !v6 || (v7 = (int)&Color[-v6] / 24, dwVal >= v7) )
      v7 = dwVal;
    if ( v6 )
      v8 = (int)&Color[-v6] / 24;
    else
      v8 = 0;
    v9 = v8 + v7;
    v37 = v8 + v7;
    if ( (int)(v8 + v7) < 0 )
      v9 = 0;
    v38 = (char *)operator new(24 * v9);
    v10 = (int)v38;
    for ( i = (char *)this->m_fontcolor.Color; i != pszBuf; v10 += 24 )
    {
      CopyRoleData(v10, (int)i);
      i += 24;
    }
    for ( j = v10; dwVal; --dwVal )
    {
      CopyRoleData(j, nVal);
      j += 24;
    }
    v13 = pszBuf;
    v14 = (char *)(v10 + 24 * v5);
    v15 = (char *)this->m_wndcolor.Color;
    if ( pszBuf != v15 )
    {
      pszBufa = v14;
      do
      {
        CopyRoleData((int)pszBufa, (int)v13);
        v13 += 24;
        pszBufa += 24;
      }
      while ( v13 != v15 );
    }
    v16 = (ArcLocaleRole *)this->m_wndcolor.Color;
    for ( k = (ArcLocaleRole *)this->m_fontcolor.Color; k != v16; k = (ArcLocaleRole *)((char *)k + 24) )
      ((ArcLocaleRole *)k)->Release();
    operator delete((void *)this->m_fontcolor.Color);
    result = (int *)this->m_fontcolor.Color;
    this->m_id = &v38[24 * v37];
    if ( result )
    {
      v19 = this->m_wndcolor.Color;
      this->m_fontcolor.Color = (unsigned int)v38;
      v20 = v19 - (_DWORD)result;
      result = (int *)((unsigned int)((unsigned __int64)(715827883LL * (int)(v19 - (_DWORD)result)) >> 32) >> 31);
      v5 += v20 / 24;
    }
    else
    {
      this->m_fontcolor.Color = (unsigned int)v38;
    }
    this->m_wndcolor.Color = (unsigned int)&v38[24 * v5];
  }
  return result;
}
