#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_YXXX.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Misc/ArcLocaleRole.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Misc/ComposeUI.h"
#include "Script/PalScript.h"
#include "Misc/PtrArray.h"
#include "Scene/SceneObj.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "UI/UINote.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIScene.h"
#include "Misc/UITextArea.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x00459970
int UITitle_YXXX::LayoutWidgets()
{
  unsigned int Color; // ecx
  int m_nSize; // ebx
  unsigned int v4; // ebx
  unsigned int v5; // eax
  int result; // eax
  int v7; // edx
  int v8; // edx
  int v9; // edx
  UIWnd *p_m_childs; // ebx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // edx
  unsigned int v18; // ecx
  unsigned int m_needscriptdel; // eax
  unsigned int a2; // [esp+0x24] [ebp-0x20] BYREF
  unsigned int v21; // [esp+0x28] [ebp-0x1C]
  unsigned int v22; // [esp+0x2C] [ebp-0x18]
  unsigned int v23; // [esp+0x30] [ebp-0x14]
  unsigned int v24; // [esp+0x34] [ebp-0x10] BYREF
  unsigned int v25; // [esp+0x38] [ebp-0xC]
  unsigned int v26; // [esp+0x3C] [ebp-0x8]
  unsigned int v27; // [esp+0x40] [ebp-0x4]
  unsigned __int16 v28; // [esp+0x48] [ebp+0x4]

  Color = this->m_OutFrameT.m_wndcolor.Color;
  m_nSize = this->m_OutFrameT.m_childs.m_nSize;
  v21 = this->m_OutFrameT.m_id + 32;
  v4 = v21 + m_nSize;
  Color -= 10;
  v5 = Color + this->m_OutFrameT.m_childs.capacity;
  HIWORD(this->m_OutFrameT.pDebugTex) = v28;
  v22 = v5;
  result = v28;
  a2 = Color;
  v23 = v4;
  switch ( v28 )
  {
    case 0u:
      (((UIWnd *)&this->m_ZZRY.m_disablepicInfo))->UIWnd::sub_445FA0(&a2);
      ((void ( *)(_PlugInfo **, int))this->m_ZZRY.m_disablepicInfo->filepos)(
        &this->m_ZZRY.m_disablepicInfo,
        1);
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_OutFrameL.m_benable))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_OutFrameL.m_benable)(&this->m_OutFrameL.m_benable, 1);
      v7 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v7;
      (((UIWnd *)&this->m_XGWZ.m_disablepicInfo))->UIWnd::sub_445FA0(&a2);
      ((void ( *)(_PlugInfo **, int))this->m_XGWZ.m_disablepicInfo->filepos)(
        &this->m_XGWZ.m_disablepicInfo,
        1);
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_OutFrameB.m_bcreateok))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_OutFrameB.m_bcreateok)(&this->m_OutFrameB.m_bcreateok, 1);
      v8 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v8;
      (((UIWnd *)((char *)&this->m_WordBk + 180)))->UIWnd::sub_445FA0(&a2);
      (**((void ( ***)(char *, int))&this->m_WordBk + 45))((char *)((char *)&this->m_WordBk + 180), (int)(1));
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_background.m_childs.m_nSize))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_background.m_childs.m_nSize)(
        &this->m_background.m_childs.m_nSize,
        1);
      v9 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v9;
      (((UIWnd *)((char *)&this->m_WordBk + 528)))->UIWnd::sub_445FA0(&a2);
      (**((void ( ***)(char *, int))&this->m_WordBk + 132))((char *)((char *)&this->m_WordBk + 528), (int)(1));
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      p_m_childs = (UIWnd *)&this->m_title.m_childs;
      goto LABEL_5;
    case 1u:
    case 3u:
      (((UIWnd *)&this->m_exit.m_disablepicInfo))->UIWnd::sub_445FA0(&a2);
      ((void ( *)(_PlugInfo **, int))this->m_exit.m_disablepicInfo->filepos)(
        &this->m_exit.m_disablepicInfo,
        1);
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_OutFrameL.m_benable))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_OutFrameL.m_benable)(&this->m_OutFrameL.m_benable, 1);
      v14 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v14;
      (((UIWnd *)&this->m_ZZRY.m_disablepicInfo))->UIWnd::sub_445FA0(&a2);
      ((void ( *)(_PlugInfo **, int))this->m_ZZRY.m_disablepicInfo->filepos)(
        &this->m_ZZRY.m_disablepicInfo,
        1);
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_OutFrameB.m_bcreateok))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_OutFrameB.m_bcreateok)(&this->m_OutFrameB.m_bcreateok, 1);
      v15 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v15;
      (((UIWnd *)&this->m_XGWZ.m_disablepicInfo))->UIWnd::sub_445FA0(&a2);
      ((void ( *)(_PlugInfo **, int))this->m_XGWZ.m_disablepicInfo->filepos)(
        &this->m_XGWZ.m_disablepicInfo,
        1);
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_background.m_childs.m_nSize))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_background.m_childs.m_nSize)(
        &this->m_background.m_childs.m_nSize,
        1);
      v16 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v16;
      (((UIWnd *)((char *)&this->m_WordBk + 180)))->UIWnd::sub_445FA0(&a2);
      (**((void ( ***)(char *, int))&this->m_WordBk + 45))((char *)((char *)&this->m_WordBk + 180), (int)(1));
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_title.m_childs))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(PtrArray *, int))this->m_title.m_childs.m_pData)(&this->m_title.m_childs, 1);
      v17 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v17;
      (((UIWnd *)((char *)&this->m_WordBk + 528)))->UIWnd::sub_445FA0(&a2);
      (**((void ( ***)(char *, int))&this->m_WordBk + 132))((char *)((char *)&this->m_WordBk + 528), (int)(1));
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      p_m_childs = (UIWnd *)&this->m_exit.m_rect.bottom;
      goto LABEL_5;
    case 2u:
      (((UIWnd *)&this->m_exit.m_disablepicInfo))->UIWnd::sub_445FA0(&a2);
      ((void ( *)(_PlugInfo **, int))this->m_exit.m_disablepicInfo->filepos)(
        &this->m_exit.m_disablepicInfo,
        1);
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_OutFrameL.m_benable))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_OutFrameL.m_benable)(&this->m_OutFrameL.m_benable, 1);
      v11 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v11;
      (((UIWnd *)&this->m_XGWZ.m_disablepicInfo))->UIWnd::sub_445FA0(&a2);
      ((void ( *)(_PlugInfo **, int))this->m_XGWZ.m_disablepicInfo->filepos)(
        &this->m_XGWZ.m_disablepicInfo,
        1);
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_OutFrameB.m_bcreateok))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_OutFrameB.m_bcreateok)(&this->m_OutFrameB.m_bcreateok, 1);
      v12 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v12;
      (((UIWnd *)((char *)&this->m_WordBk + 180)))->UIWnd::sub_445FA0(&a2);
      (**((void ( ***)(char *, int))&this->m_WordBk + 45))((char *)((char *)&this->m_WordBk + 180), (int)(1));
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      (((UIWnd *)&this->m_background.m_childs.m_nSize))->UIWnd::sub_445FA0(&v24);
      (*(void ( **)(int *, int))this->m_background.m_childs.m_nSize)(
        &this->m_background.m_childs.m_nSize,
        1);
      v13 = this->m_OutFrameT.m_childs.m_nSize;
      v21 = v23;
      v23 += v13;
      (((UIWnd *)((char *)&this->m_WordBk + 528)))->UIWnd::sub_445FA0(&a2);
      (**((void ( ***)(char *, int))&this->m_WordBk + 132))((char *)((char *)&this->m_WordBk + 528), (int)(1));
      v25 = v21 + 1;
      v24 = a2 + 1;
      v26 = a2 + 87;
      v27 = v23 - 1;
      p_m_childs = (UIWnd *)&this->m_title.m_childs;
LABEL_5:
      (((UIWnd *)p_m_childs))->UIWnd::sub_445FA0(&v24);
      (**(void ( ***)(UIWnd *, int))p_m_childs)((UIWnd *)(p_m_childs), (int)(1));
      v18 = v23;
      m_needscriptdel = this->m_OutFrameT.m_childs.m_needscriptdel;
      this->m_OutFrameT.m_id = v23;
      this->m_OutFrameT.m_wndcolor.Color = m_needscriptdel;
      this->m_OutFrameT.m_rect.top = v18 + 11;
      this->m_OutFrameT.m_rect.left = m_needscriptdel + 68;
      result = (((UIWnd *)&this->m_OutFrameR.pDebugTex))->UIWnd::sub_445FA0(&this->m_OutFrameT.m_wndcolor);
      break;
    default:
      return result;
  }
  return result;
}

// 0x0047DCA0
void UITitle_YXXX::Create()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->rc.top = 0;
  this->m_OutFrameT.m_wndcolor.Color = 800;
  this->m_OutFrameT.m_id = 600;
  this->m_OutFrameR.m_pbk2 = ((gbTexture *)0);
  this->m_OutFrameR.m_mouseoff = 0;
  (((UITextArea *)&this->m_OutFrameR.m_FVF))->UITextArea::InitAfterClear();
  (((UIFrameContainer *)&this->m_OutFrameB.m_rect))->UIFrameContainer::ResetContainerState();
  ((UIRoleDialog *)((char *)&this->m_WordBk + 376))->UIRoleDialog::UIRoleDialog();
}

// 0x0047DD90
UITitle_YXXX::~UITitle_YXXX()
{
  (((UIRoleDialog *)((char *)&this->m_WordBk + 376)))->UIRoleDialog::~UIRoleDialog();
  (((UIFrameContainer *)&this->m_OutFrameB.m_rect))->UIFrameContainer::~UIFrameContainer();
  UITextArea_Destroy();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x0047DE40
void UITitle_YXXX::Init()
{
  unsigned int Color; // eax
  unsigned int m_id; // ecx
  char *v4; // eax
  char *v5; // ebx
  int *v6; // ebp
  gbColorQuad *p_m_wndcolor; // esi
  _DWORD v8[8]; // [esp+0x20] [ebp-0x20] BYREF

  Color = this->m_OutFrameT.m_wndcolor.Color;
  m_id = this->m_OutFrameT.m_id;
  *(_DWORD *)((UIWnd *)&this->m_OutFrameT) = Color;
  this->m_OutFrameT.m_fontcolor.Color = m_id;
  this->rc.bottom = 0;
  this->rc.right = 0;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, 0, 0, *(_DWORD *)((UIWnd *)&this->m_OutFrameT), this->m_OutFrameT.m_fontcolor.Color) /* [ROWTABLE] */;
  this->m_OutFrameR.m_ppicInfo = ((_PlugInfo *)((_PlugInfo *)170));
  this->m_OutFrameR.m_ppic = ((gbTexture *)((gbTexture *)310));
  this->m_OutFrameR.m_disablepic = ((gbTexture *)((gbTexture *)468));
  this->m_OutFrameR.m_disablepicInfo = ((_PlugInfo *)((_PlugInfo *)430));
  (((UINote *)&this->m_OutFrameR.m_FVF))->UINote::Create(-1430519792, (int)&this->m_OutFrameR.m_ppic, (int)this, "UI\\Flex\\Note");
  (*(void ( **)(int *, _DWORD))this->m_OutFrameR.m_FVF)(&this->m_OutFrameR.m_FVF, 0);
  v4 = (char *)&this->m_OutFrameR.m_ppicInfo->name[6];
  v8[0] = (unsigned long)((char *)&this->m_OutFrameR.m_ppic->pName + 2);
  v8[1] = (unsigned long)v4;
  v8[2] = v8[0] + 136;
  v8[3] = (unsigned long)(v4 + 128);
  (*(void ( **)(tagRECT *, int, _DWORD *, UITitle_YXXX *))(this->m_OutFrameB.m_rect.left + 16))(
    &this->m_OutFrameB.m_rect,
    -1430519792,
    (_DWORD *)(v8),
    this);
  (((UIScene *)&this->m_OutFrameB.m_rect))->UIScene::SetShow(0);
  AllocObject(&this->m_OutFrameB.m_rect);
  (*(void ( **)(tagRECT *, _DWORD))this->m_OutFrameB.m_rect.left)(&this->m_OutFrameB.m_rect, 0);
  v5 = g_szRoleNameTable;
  v6 = (int *)&dword_56B884;
  p_m_wndcolor = (gbColorQuad *)&this->m_background.m_wndcolor;
  do
  {
    (*(void ( **)(gbColorQuad *, int, _DWORD *, UITitle_YXXX *, char *, _DWORD, int))(p_m_wndcolor->Color + 28))(
      p_m_wndcolor,
      *v6,
      (_DWORD *)(v8),
      this,
      "SubGame\\HockShop\\Control\\rawbtn",
      0,
      1);
    (((PalScript *)p_m_wndcolor))->PalScript::OpenScript("SubGame\\HockShop\\Control\\unrawbtn.tga", 1);
    (((CScreenMode *)p_m_wndcolor))->CScreenMode::SetTooltipText((int)v5);
    p_m_wndcolor[27].Color = 3;
    p_m_wndcolor[26].Color = 1;
    p_m_wndcolor[52].Color = 1;
    (*(void ( **)(gbColorQuad *, _DWORD))p_m_wndcolor->Color)(p_m_wndcolor, 0);
    ++v6;
    v5 += 256;
    p_m_wndcolor += 86;
  }
  while ( (int)v6 < (int)&off_56B898 );
  v8[5] = 200;
  v8[4] = 300;
  v8[6] = 500;
  v8[7] = 300;
  Create__ovl_1((ARC_PlayerAtt *)((char *)&this->m_WordBk + 376));
  (((UIItem *)((char *)&this->m_WordBk + 376)))->UIItem::SetData(18);
  *((_BYTE *)&this->m_WordBk + 1749) = 0;
  *((_BYTE *)&this->m_WordBk + 1750) = 0;
}

// 0x0047E3E0
int UITitle_YXXX::Update(int nVal, int nVal2)
{
  int v4; // ebp
  gbColorQuad *p_m_wndcolor; // edi
  gbColorQuad *v6; // edi
  int v7; // ebp
  int v9; // [esp+0x4] [ebp-0xC]

  if ( !*((_BYTE *)&this->m_WordBk + 1750) && *((_DWORD *)&this->m_OutFrameL + 39) == 2 )
  {
    (*(void ( **)(tagRECT *, int))this->m_OutFrameB.m_rect.left)(&this->m_OutFrameB.m_rect, 1);
    v4 = 0;
    p_m_wndcolor = (gbColorQuad *)&this->m_background.m_wndcolor;
    do
    {
      if ( *((_BYTE *)&this->m_WordBk + v4 + 1744) )
        (*(void ( **)(gbColorQuad *, int))p_m_wndcolor->Color)(p_m_wndcolor, 1);
      else
        (*(void ( **)(gbColorQuad *, _DWORD))p_m_wndcolor->Color)(p_m_wndcolor, 0);
      ++v4;
      p_m_wndcolor += 86;
    }
    while ( v4 < 5 );
    *((_BYTE *)&this->m_WordBk + 1750) = 1;
  }
  if ( UIParabolaCtrl_GetState(v9) == 2 )
  {
    (*(void ( **)(int *, _DWORD))this->m_OutFrameR.m_FVF)(&this->m_OutFrameR.m_FVF, 0);
    (*(void ( **)(tagRECT *, _DWORD))this->m_OutFrameB.m_rect.left)(&this->m_OutFrameB.m_rect, 0);
    v6 = (gbColorQuad *)&this->m_background.m_wndcolor;
    v7 = 5;
    do
    {
      (*(void ( **)(gbColorQuad *, _DWORD))v6->Color)(v6, 0);
      v6 += 86;
      --v7;
    }
    while ( v7 );
    this->m_OutFrameR.m_mouseoff = 1;
    *((_BYTE *)&this->m_WordBk + 1749) = 0;
    *((_BYTE *)&this->m_WordBk + 1750) = 0;
  }
  if ( this->m_OutFrameR.m_mouseoff )
    (((CGameData *)&g_gamefrm))->CGameData::Load(0);
  else
    (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return 1;
}

// 0x0047E4E0
int UITitle_YXXX::HandleMsgDLL(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  int v5; // edx
  int *v6; // eax

  if ( hinstDLL == (HINSTANCE)1000 )
    return HandleDllEntryUITitle((HINSTANCE)0x3E8, fdwReason, lpvReserved);
  if ( hinstDLL != (HINSTANCE)1001 )
    return this->UIWnd::OnMessage((int)hinstDLL, fdwReason, (int)lpvReserved);
  v5 = 0;
  v6 = (int *)&dword_56B884;
  while ( fdwReason != *v6 )
  {
    ++v6;
    ++v5;
    if ( (int)v6 >= (int)&off_56B898 )
      return 1;
  }
  ComposeUI_ProcessFrame(v5);
  return 1;
}

// 0x004AF770
int * UITitle_YXXX::CreateTitle(char *pszBuf, unsigned int dwVal, int nVal)
{
    UITitle_YXXX *_this = this;
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
  void *v38; // [esp+0x18] [ebp-0x4]
  char *pszBufa; // [esp+0x20] [ebp+0x4]
  char *pszBufb; // [esp+0x20] [ebp+0x4]
  unsigned int pszBufc; // [esp+0x20] [ebp+0x4]
  char *dwVala; // [esp+0x24] [ebp+0x8]
  int *dwValb; // [esp+0x24] [ebp+0x8]

  Color = (char *)_this->m_wndcolor.Color;
  v5 = dwVal;
  v36 = _this;
  if ( (int)(_this->m_id - (int)Color) / 24 >= dwVal )
  {
    result = (int *)((unsigned int)((unsigned __int64)(715827883i64 * (Color - pszBuf)) >> 32) >> 31);
    if ( (Color - pszBuf) / 24 >= dwVal )
    {
      if ( dwVal )
      {
        v27 = 24 * dwVal;
        v28 = (int)&Color[-24 * dwVal];
        v29 = _this->m_wndcolor.Color;
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
          _this = v36;
          v27 = 24 * dwVal;
        }
        result = (int *)_this->m_wndcolor.Color;
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
            dwValb = (int *)(result - 6);
            v31 = (ArcLocaleRole *)((char *)v31 - 24);
            *(result - 6) = v33;
            LOBYTE(v31[-1].script) = *((_BYTE *)v32 - 4);
            result = (((ArcLocaleRole *)v31))->ArcLocaleRole::CalcPosition(v32);
            if ( v30 == pszBuf )
              break;
            result = (int *)dwValb;
          }
          _this = v36;
          v27 = pszBufc;
        }
        v34 = (char *)&pszBuf[v27];
        v35 = (char *)pszBuf;
        if ( pszBuf != &pszBuf[v27] )
        {
          do
          {
            *(_DWORD *)v35 = *(_DWORD *)nVal;
            v35[4] = *(_BYTE *)(nVal + 4);
            result = (((ArcLocaleRole *)(v35 + 8)))->ArcLocaleRole::CalcPosition((int *)(nVal + 8));
            v35 += 24;
          }
          while ( v35 != v34 );
          _this = v36;
          v27 = pszBufc;
        }
        _this->m_wndcolor.Color += v27;
      }
    }
    else
    {
      v22 = (char *)pszBuf;
      pszBufb = (char *)(24 * dwVal);
      if ( pszBuf != Color )
      {
        dwVala = (char *)&pszBuf[24 * dwVal];
        do
        {
          CopyRoleData((int)dwVala, (int)v22);
          v22 += 24;
          dwVala += 24;
        }
        while ( v22 != Color );
        _this = v36;
      }
      v23 = _this->m_wndcolor.Color;
      if ( v5 != (int)(v23 - (_DWORD)pszBuf) / 24 )
      {
        v24 = v5 - (int)(_this->m_wndcolor.Color - (int)pszBuf) / 24;
        do
        {
          CopyRoleData(v23, nVal);
          v23 += 24;
          --v24;
        }
        while ( v24 );
      }
      result = (int *)v36;
      v25 = (char *)pszBuf;
      v26 = (char *)v36->m_wndcolor.Color;
      if ( pszBuf != v26 )
      {
        do
        {
          *(_DWORD *)v25 = *(_DWORD *)nVal;
          v25[4] = *(_BYTE *)(nVal + 4);
          (((ArcLocaleRole *)(v25 + 8)))->ArcLocaleRole::CalcPosition((int *)(nVal + 8));
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
    v6 = _this->m_fontcolor.Color;
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
    v38 = (void *)operator new(24 * v9);
    v10 = (int)v38;
    for ( i = (char *)v36->m_fontcolor.Color; i != pszBuf; v10 += 24 )
    {
      CopyRoleData(v10, (int)i);
      i += 24;
    }
    for ( j = v10; dwVal; --dwVal )
    {
      CopyRoleData(j, nVal);
      j += 24;
    }
    v13 = (char *)pszBuf;
    v14 = (char *)(v10 + 24 * v5);
    v15 = (char *)v36->m_wndcolor.Color;
    if ( pszBuf != v15 )
    {
      pszBufa = (char *)v14;
      do
      {
        CopyRoleData((int)pszBufa, (int)v13);
        v13 += 24;
        pszBufa += 24;
      }
      while ( v13 != v15 );
    }
    v16 = (ArcLocaleRole *)v36->m_wndcolor.Color;
    for ( k = (ArcLocaleRole *)v36->m_fontcolor.Color; k != v16; k = (ArcLocaleRole *)((char *)k + 24) )
      (((ArcLocaleRole *)k))->ArcLocaleRole::Release();
    operator delete((void *)v36->m_fontcolor.Color);
    result = (int *)v36->m_fontcolor.Color;
    v36->m_id = (unsigned int)v38 + 24 * v37;
    if ( result )
    {
      v19 = (unsigned long)v36->m_wndcolor.Color;
      v36->m_fontcolor.Color = (unsigned int)v38;
      v20 = v19 - (_DWORD)result;
      result = (int *)((unsigned int)((unsigned __int64)(715827883i64 * (int)(v19 - (_DWORD)result)) >> 32) >> 31);
      v5 += v20 / 24;
    }
    else
    {
      v36->m_fontcolor.Color = (unsigned int)v38;
    }
    v36->m_wndcolor.Color = (unsigned int)v38 + 24 * v5;
  }
  return result;
}
