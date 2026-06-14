#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SaleUI.h"

// Forward declarations for unnamed functions
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
char sub_46ADF0(_BYTE *_this); // from annotations

// Unnamed globals (extern)
extern char byte_1010101;
extern CHAR byte_DC343C[256];
extern const char * off_5706AC;
extern const char * off_5706C0;
extern const char * off_5706CC;
extern void * off_5E7ECC;
extern _SPropValue * off_5E7ED8;
extern RoleSystem stru_C059A0;

// 0x0045A7B0
SaleUI::SaleUI()
{
  _DWORD *v2; // eax
  SaleUI_SortData *v3; // ebp
  bool v4; // zf
  int bkHeight; // kr00_4
  char *v7; // [esp+0x10] [ebp-0x18]
  int v8; // [esp+0x14] [ebp-0x14]

  this->bkWidth = 800;
  this->bkHeight = 600;
  *(_DWORD *)this->remarkbuf = 0;
  *(_DWORD *)&this->remarkbuf[4] = 0;
  *(_DWORD *)&this->remarkbuf[16] = 0;
  *(_DWORD *)&this->remarkbuf[20] = 0;
  *(_DWORD *)&this->remarkbuf[24] = 0;
  *(_DWORD *)&this->remarkbuf[28] = 0;
  this->remarkbuf[32] = 0;
  *(_DWORD *)&this->remarkbuf[36] = 1090519040;
  *(_WORD *)&this->remarkbuf[42] = 0;
  *((_DWORD *)&this->m_data + 3419) = 0;
  v8 = 5;
  *((_DWORD *)&this->m_data + 3420) = 0;
  memset((char *)&this->m_data + 13684, 0, 0x640u);
  memset((char *)&this->m_data + 16884, 0, 0x190u);
  memset((char *)&this->m_data + 15284, 0, 0x640u);
  v2 = (_DWORD *)((char *)&this->m_data + 17288);
  *(_DWORD *)&this->remarkbuf[40] = 0;
  *((_DWORD *)&this->m_data + 4321) = 0;
  v7 = (char *)&this->m_data + 17288;
  v3 = &this->m_sort[32][1];
  while ( 1 )
  {
    *v2 = 0;
    *(_WORD *)v3[-214]._tail_000 = 0;
    lstrcpyA((LPSTR)&v3[-214] + 2, g_szSceneUIText);
    lstrcpyA((LPSTR)&v3[-86] + 2, g_szSceneUIText);
    lstrcpyA((LPSTR)&v3[-78], g_szSceneUIText);
    lstrcpyA((LPSTR)&v3[-65], g_szSceneUIText);
    memset(&v3[-56], 0, 0x30u);
    v3[-20] = 0;
    v3[-2] = (SaleUI_SortData)0xFFFF;
    v3[-1] = 0;
    *v3 = 0;
    v3[1] = (SaleUI_SortData)0xFFFF;
    v3[2] = 0;
    v3[3] = 0;
    v3[4] = (SaleUI_SortData)0xFFFF;
    v3[5] = 0;
    v3[6] = 0;
    ArraySort((int)&v3[7], 12, 2, 0 /* TODO: (int)exception::exception */);
    v3[13] = (SaleUI_SortData)0xFFFF;
    v3[14] = 0;
    v3[15] = 0;
    memset(v7, 0, 0x580u);
    v3 += 352;
    v4 = v8 == 1;
    v7 += 1408;
    --v8;
    if ( v4 )
      break;
    v2 = v7;
  }
  sub_4422E0(this->m_sort[342]);
  ((UI3DCtrl *)&this->m_sort[349][3])->ctor_D830();
  sub_4422E0(&this->m_sort[353][4]);
  this->m_TempData[115][2].item = 0;
  LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
  HIBYTE(this->m_ListSaleTitle.m_childs.m_nSize) = 0;
  this->m_ListSaleTitle.m_childs.m_needscriptdel = 0;
  this->m_ListEquipTitleRc.bottom = 0;
// [VFTABLE] this->m_Icon[0][0].__vftable = 0;
  ((UIProgressBar *)&this->m_Icon[0][0].m_rect)->ctor();
  ((ARC_PlayerAtt *)&this->m_Icon[0][1].m_FVF)->Refresh();
  sub_4422E0(&this->m_Icon[1][4].m_align);
  sub_4422E0(&this->m_Icon[2][0].m_childs.m_nSize);
  sub_4422E0(&this->m_Icon[2][1].m_rect);
  sub_4422E0(&this->m_Icon[2][1].m_fadespeed);
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->m_Icon[3][1].m_ppicInfo);
  sub_4422E0(&this->m_Icon[3][2].m_pbk);
  sub_4422E0(&this->m_ListGrid[1].m_disablepic);
  sub_4422E0(&this->m_ListGrid[2].m_disablepic);
  ((UIListBox *)&this->m_ListGrid[3].m_disablepic)->UpdateKeyCtrl();
  UIScene::GetSys();
  UIScene::GetSys();
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[0] = (gbTexture *)32;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[1] = (gbTexture *)16;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[2] = 0;
  this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[3] = 0;
  sub_4422E0(&this->ml_ResumeList.m_scrollbar.m_texarray.m_ptex[7]);
  sub_4422E0(&this->ml_ResumeList.m_column[0].head[16]);
  sub_4422E0(&this->ml_ResumeList.m_column[2].head[16]);
  sub_4422E0(&this->ml_ResumeList.m_column[4].head[16]);
  sub_4422E0(&this->ml_ResumeList.m_column[6].head[16]);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  sub_4422E0(&this->ml_SmeltList.m_column[0].head[8]);
  LOBYTE(this->ml_SmeltList.m_column[1].items.m_needscriptdel) = 0;
  BYTE1(this->ml_SmeltList.m_column[1].items.m_needscriptdel) = 0;
  BYTE2(this->ml_SmeltList.m_itemheight) = 0;
  this->ml_SmeltList.m_fontsize = 0;
  this->ml_SmeltList.m_firstshow = -1;
  this->ml_SmeltList.m_onsel = -1;
  LOBYTE(this->ml_SmeltList.m_locksel) = 0;
  this->ml_SmeltList.m_scrollRc.left = 0;
  this->ml_SmeltList.m_scrollRc.top = 0;
  this->ml_SmeltList.m_scrollRc.bottom = 0;
  this->ml_SmeltList.m_pbkpic = 0;
  LOBYTE(this->ml_SmeltList.m_pbkpicInfo) = 0;
  LOBYTE(this->ml_SmeltList.m_selpicInfo) = 0;
  lstrcpyA((LPSTR)&this->ml_SmeltList.m_column[1].items.m_needscriptdel + 2, Destination);
  lstrcpyA((LPSTR)&this->ml_SmeltList.m_column[4].width + 2, byte_DC343C);
  memset(&this->remarkbuf[40], 0, 0x4460u);
  memset((char *)&this->m_data + 17288, 0, 0x580u);
  this->m_sort[412][2]._tail_000[0] = 1;
  this->m_sort[412][3]._tail_000[0] = 0;
  this->m_sort[412][2]._tail_000[3] = 0;
  this->m_sort[412][2]._tail_000[2] = 0;
  this->m_sort[412][2]._tail_000[1] = 0;
  memset((char *)&this->m_ListSaleTitle.m_rect.left + 1, 0, 0x1Cu);
  *(_WORD *)((char *)&this->m_ListSaleTitle.m_childs.m_nSize + 1) = 0;
  memset(&this->m_ListSaleTitle.m_bcreateok, 0xFFu, 0x78u);
  memset(&this->m_TempData[111][2].item, 0, 0xF0u);
  memset(&this->m_TempData[115][3], 0, 0xF0u);
  this->m_Icon[0][0].m_fontcolor.Color = 0;
  this->m_Icon[0][0].m_wndcolor.Color = 0;
  LOWORD(this->m_Icon[0][0].m_id) = 0;
  bkHeight = this->bkHeight;
  this->m_sort[411][3] = (SaleUI_SortData)68;
  this->m_sort[411][4] = (SaleUI_SortData)(bkHeight / 4);
  this->m_sort[412][0] = (SaleUI_SortData)65;
  this->m_sort[412][1] = (SaleUI_SortData)86;
  this->ml_SmeltList.m_scrollRc.right = 0;
  (int)this;
}

// 0x004615F0
int SaleUI::DestroySubFrames()
{
  int v2; // ecx
  SaleUI_SortData *v3; // eax
  SaleUI_SortData *v4; // edi
  int v5; // eax
  LONG v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // eax

  if ( !BYTE1(this->ml_SmeltList.m_column[1].items.m_needscriptdel) )
  {

    v2 = 0;
    v3 = &this->m_sort[32][2];
    do
    {
      if ( this->m_sort[412][2]._tail_000[v2] )
      {
        if ( v3[2] )
        {
          *v3 = 0;
          v3[1] = 0;
          v3[2] = 0;
        }
        if ( v3[-1] )
        {
          v4 = v3 - 3;
          *v4 = 0;
          v4[1] = 0;
          v4[2] = 0;
        }
        if ( v3[5] )
        {
          v3[3] = 0;
          v3[4] = 0;
          v3[5] = 0;
        }
        if ( v3[8] )
        {
          v3[6] = 0;
          v3[7] = 0;
          v3[8] = 0;
        }
        if ( v3[11] )
        {
          v3[9] = 0;
          v3[10] = 0;
          v3[11] = 0;
        }
        if ( v3[14] )
        {
          v3[12] = 0;
          v3[13] = 0;
          v3[14] = 0;
        }
      }
      ++v2;
      v3 += 352;
    }
    while ( v2 < 5 );
    v5 = *((_DWORD *)&this->m_data + 3419);
    *(_DWORD *)&this->remarkbuf[20] = 0;
    if ( v5 > 0 )
    {
      do
      {
        *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]) = 0;
        sprintf(this->buf, &dir[20], *(_DWORD *)(*(_DWORD *)&this->remarkbuf[4] + 4 * *(_DWORD *)&this->remarkbuf[20]));
        ((UIListBox *)&this->m_ListGrid[3].m_disablepic)->SetMouseMoveSel(2, *(_DWORD *)&this->remarkbuf[20], this->buf, 0);
        v6 = *(_DWORD *)&this->remarkbuf[20];
        if ( v6 < 0 || v6 >= this->m_ListGrid[7].m_rect.right )
          v7 = 0;
        else
          v7 = *(_DWORD *)(this->m_ListGrid[7].m_rect.top + 4 * v6);
        *(_DWORD *)(v7 + 68) = this->m_ListGrid[3].m_disablepicInfo;
        v8 = *((_DWORD *)&this->m_data + 3419);
        v9 = *(_DWORD *)&this->remarkbuf[20] + 1;
        *(_DWORD *)&this->remarkbuf[20] = v9;
      }
      while ( v9 < v8 );
    }
    ((UIListBox *)&this->m_ListGrid[3].m_disablepic)->GetItem();
    this->ml_SmeltList.m_scrollRc.bottom = 0;
    *(_DWORD *)&this->remarkbuf[16] = 0;
    sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
    ((UICaption *)&this->ml_ResumeList.m_column[6].head[16])->SetEnable((int)this->buf, 0);
    *(_DWORD *)&this->remarkbuf[20] = 0;
    do
    {
      if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
      {
        *(_DWORD *)&this->remarkbuf[24] = 0;
        do
        {
          (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4])(
            &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
            0);
          *(_DWORD *)&this->remarkbuf[28] = 0;
          do
          {
            (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824
                                                                                  * *(_DWORD *)&this->remarkbuf[20]
                                                                                  + 4
                                                                                  + 304
                                                                                  * *(_DWORD *)&this->remarkbuf[24]
                                                                                  + 38 * *(_DWORD *)&this->remarkbuf[28]])(
              &this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                               + 4
                               + 304 * *(_DWORD *)&this->remarkbuf[24]
                               + 38 * *(_DWORD *)&this->remarkbuf[28]],
              0);
            v10 = *(_DWORD *)&this->remarkbuf[28] + 1;
            *(_DWORD *)&this->remarkbuf[28] = v10;
          }
          while ( v10 < 8 );
          v11 = *(_DWORD *)&this->remarkbuf[24] + 1;
          *(_DWORD *)&this->remarkbuf[24] = v11;
        }
        while ( v11 < 6 );
      }
      v12 = *(_DWORD *)&this->remarkbuf[20] + 1;
      *(_DWORD *)&this->remarkbuf[20] = v12;
    }
    while ( v12 < 5 );
    ((UICaption *)&this->ml_ResumeList.m_column[2].head[16])->SetEnable((int)g_szSceneUIText, 0);
    ((UICaption *)&this->ml_ResumeList.m_column[0].head[16])->SetEnable((int)g_szSceneUIText, 0);
    this->m_Icon[0][0].m_fonttype = 0;
    ((PAL3 *)this)->GetValue(0);
    LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
  }
  memset((char *)&this->m_ListSaleTitle.m_rect.left + 1, 0, 0x1Cu);
  *(_WORD *)((char *)&this->m_ListSaleTitle.m_childs.m_nSize + 1) = 0;
  memset(&this->m_ListSaleTitle.m_bcreateok, 0xFFu, 0x78u);
  this->m_Icon[0][0].m_fontcolor.Color = 0;
  this->m_Icon[0][0].m_wndcolor.Color = 0;
  LOWORD(this->m_Icon[0][0].m_id) = 0;
  memset(*(void **)&this->remarkbuf[4], 0, 4 * *((_DWORD *)&this->m_data + 3419));
  memset((void *)this->m_ListSaleTitle.m_childs.m_needscriptdel, 0, 4 * *((_DWORD *)&this->m_data + 3419));
  memset((void *)this->m_ListEquipTitleRc.bottom, 0, 4 * *((_DWORD *)&this->m_data + 3419));
  *(_DWORD *)&this->remarkbuf[20] = 0;
  do
  {
    if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
    {
      *(_DWORD *)&this->remarkbuf[24] = 0;
      do
      {
        (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4])(
          &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
          0);
        (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20]
                                                                   + 2
                                                                   + *(_DWORD *)&this->remarkbuf[24]].m_fonttype)(
          &this->m_Role[6 * *(_DWORD *)&this->remarkbuf[20] + 2 + *(_DWORD *)&this->remarkbuf[24]].m_fonttype,
          0);
        (*(void ( **)(int *, _DWORD))this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4])(
          &this->m_NotesNull[54 * *(_DWORD *)&this->remarkbuf[20] + 277][45 * *(_DWORD *)&this->remarkbuf[24] + 4],
          0);
        *(_DWORD *)&this->remarkbuf[28] = 0;
        do
        {
          (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                                                                                + 4
                                                                                + 304 * *(_DWORD *)&this->remarkbuf[24]
                                                                                + 38 * *(_DWORD *)&this->remarkbuf[28]])(
            &this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                             + 4
                             + 304 * *(_DWORD *)&this->remarkbuf[24]
                             + 38 * *(_DWORD *)&this->remarkbuf[28]],
            0);
          sub_445FA0(&this->m_sort[412][1824 * *(_DWORD *)&this->remarkbuf[20]
                                      + 4
                                      + 304 * *(_DWORD *)&this->remarkbuf[24]
                                      + 38 * *(_DWORD *)&this->remarkbuf[28]]);
          v13 = *(_DWORD *)&this->remarkbuf[28] + 1;
          *(_DWORD *)&this->remarkbuf[28] = v13;
        }
        while ( v13 < 8 );
        v14 = *(_DWORD *)&this->remarkbuf[24] + 1;
        *(_DWORD *)&this->remarkbuf[24] = v14;
      }
      while ( v14 < 6 );
    }
    v15 = *(_DWORD *)&this->remarkbuf[20] + 1;
    *(_DWORD *)&this->remarkbuf[20] = v15;
  }
  while ( v15 < 5 );
  ((UICaption *)&this->ml_ResumeList.m_column[0].head[16])->SetEnable((int)g_szSceneUIText, 0);
  ((UICaption *)&this->m_Icon[2][1].m_fadespeed)->SetEnable((int)g_szSceneUIText, 0);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_Icon[2][1].m_fadespeed))(&this->m_Icon[2][1].m_fadespeed, 0);
  (**(void ( ***)(SaleUI_SortData *, _DWORD))&this->m_sort[361][2])(&this->m_sort[361][2], 0);
  this->m_Icon[0][0].m_fonttype = 0;
  ((PAL3 *)this)->SetPanelStates(1u);
  ((PAL3 *)this)->GetValue(0);
  sub_445E50((int)&this->m_ListGrid[3].m_disablepic);
  ((PAL3 *)this)->SetRange(1u);
  ((PAL3 *)this)->SetValue(0);
  ((PlayerMgr *)this)->SendInputToRole(0);
  *(_DWORD *)this->remarkbuf = 0;
  this->ml_SmeltList.m_scrollRc.left = 0;
  *(_DWORD *)&this->remarkbuf[16] = 0;
  this->ml_SmeltList.m_scrollRc.bottom = 0;
  this->ml_SmeltList.m_pbkpic = 0;
  this->ml_SmeltList.m_fontsize = 0;
  this->ml_SmeltList.m_onsel = -1;
  BYTE2(this->ml_SmeltList.m_itemheight) = 0;
  BYTE1(this->ml_SmeltList.m_column[1].items.m_needscriptdel) = 0;
  LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
  sprintf(this->buf, "%s %d", g_szCombatFieldName, 0);
  ((UICaption *)&this->ml_ResumeList.m_column[6].head[16])->SetEnable((int)this->buf, 0);
  v16 = *((_DWORD *)&this->m_data + 3419);
  *(_DWORD *)&this->remarkbuf[20] = 0;
  if ( v16 > 0 )
  {
    do
    {
      sprintf(this->buf, &dir[20], 0);
      ((UIListBox *)&this->m_ListGrid[3].m_disablepic)->SetMouseMoveSel(2, *(_DWORD *)&this->remarkbuf[20], this->buf, 0);
      v17 = *((_DWORD *)&this->m_data + 3419);
      v18 = *(_DWORD *)&this->remarkbuf[20] + 1;
      *(_DWORD *)&this->remarkbuf[20] = v18;
    }
    while ( v18 < v17 );
  }
  ((UIListBox *)&this->m_ListGrid[3].m_disablepic)->GetItem();
  ((UIListBox *)&this->m_ListGrid[3].m_disablepic)->GetItem();
  ((UICaption *)&this->ml_ResumeList.m_column[2].head[16])->SetEnable((int)g_szSceneUIText, 0);
  (*(void ( **)(tagRECT *, _DWORD))this->m_ListGrid[12].m_rect.left)(&this->m_ListGrid[12].m_rect, 0);
  (*(void ( **)(int *, _DWORD))this->m_ListGrid[14].m_bvisible)(
    &this->m_ListGrid[14].m_bvisible,
    0);
  return (**(int ( ***)(char *, _DWORD))&this->ml_SmeltList.m_column[0].head[8])(
           &this->ml_SmeltList.m_column[0].head[8],
           0);
}

// 0x0046A8B0
int SaleUI::Update(int deltatime, int haveinput)
{
  int result; // eax
  _BYTE *v5; // edx
  SaleUI_SortData *v6; // ecx
  SaleUI_SortData *v7; // eax
  int *v8; // eax
  _BYTE *v9; // edx
  SaleUI_SortData *v10; // ecx
  SaleUI_SortData *v11; // eax
  _BYTE *v12; // edx
  SaleUI_SortData *v13; // ecx
  SaleUI_SortData *v14; // eax
  _BYTE *v15; // edx
  SaleUI_SortData *v16; // ecx
  SaleUI_SortData *v17; // eax
  _BYTE *v18; // edx
  SaleUI_SortData *v19; // ecx
  SaleUI_SortData *v20; // eax
  _BYTE *v21; // edx
  SaleUI_SortData *v22; // ecx
  SaleUI_SortData *v23; // eax
  _DWORD *v24; // ecx
  char *v25; // eax
  int v26; // ebx
  int v27; // edx
  int v28; // esi

  result = haveinput;
  if ( haveinput < 6 )
  {
    switch ( haveinput )
    {
      case 0:
        v5 = (char *)&this->m_ListSaleTitle.m_rect.left + 6 * deltatime + 1;
        if ( *v5 )
        {
          v6 = &this->m_sort[32][352 * deltatime + 2];
          v7 = (SaleUI_SortData *)(&Buffer.m_partyActor.m_pParticleData + 352 * deltatime + 1);
          *v7 = this->m_sort[32][352 * deltatime + 2];
          v7[1] = this->m_sort[32][352 * deltatime + 3];
          v7[2] = this->m_sort[32][352 * deltatime + 4];
          *v6 = 0;
          v6[1] = 0;
          v6[2] = 0;
          *v5 = 0;
          (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * deltatime + 2].m_fonttype)(
            &this->m_Role[6 * deltatime + 2].m_fonttype,
            0);
          v8 = &this->m_ListSaleTitle.m_bcreateok + 6 * deltatime;
          goto LABEL_15;
        }
        break;
      case 1:
        v21 = (char *)&this->m_ListSaleTitle.m_rect.left + 6 * deltatime + 2;
        if ( *v21 )
        {
          v22 = &this->m_sort[34][352 * deltatime + 4];
          v23 = (SaleUI_SortData *)&Buffer.m_partyActor.m_dwMatMsg[352 * deltatime + 6];
          *v23 = this->m_sort[34][352 * deltatime + 4];
          v23[1] = this->m_sort[35][352 * deltatime];
          v23[2] = this->m_sort[35][352 * deltatime + 1];
          *v22 = 0;
          v22[1] = 0;
          v22[2] = 0;
          *v21 = 0;
          (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * deltatime + 3].m_fonttype)(
            &this->m_Role[6 * deltatime + 3].m_fonttype,
            0);
          v8 = &this->m_ListSaleTitle.m_bvisible + 6 * deltatime;
          goto LABEL_15;
        }
        break;
      case 2:
        v15 = (char *)&this->m_ListSaleTitle.m_rect.left + 6 * deltatime + 3;
        if ( *v15 )
        {
          v16 = &this->m_sort[33][352 * deltatime + 3];
          v17 = (SaleUI_SortData *)&Buffer.m_partyActor.m_dwMatMsg[352 * deltatime];
          *v17 = this->m_sort[33][352 * deltatime + 3];
          v17[1] = this->m_sort[33][352 * deltatime + 4];
          v17[2] = this->m_sort[34][352 * deltatime];
          *v16 = 0;
          v16[1] = 0;
          v16[2] = 0;
          *v15 = 0;
          (*(void ( **)(Parent_Data **, _DWORD))this->m_Role[6 * deltatime + 4].m_fonttype)(
            &this->m_Role[6 * deltatime + 4].m_fonttype,
            0);
          *((_BYTE *)&this->m_Icon[0][0].m_fontcolor.Color + 2 * deltatime) = 0;
          v8 = &this->m_ListSaleTitle.m_benable + 6 * deltatime;
          goto LABEL_15;
        }
        break;
      case 3:
        v9 = (char *)&this->m_ListSaleTitle.m_rect.top + 6 * deltatime;
        if ( *v9 )
        {
          v10 = &this->m_sort[31][352 * deltatime + 4];
          v11 = (SaleUI_SortData *)(&Buffer.m_partyActor.m_nAnimFrame + 704 * deltatime + 2);
          *v11 = this->m_sort[31][352 * deltatime + 4];
          v11[1] = this->m_sort[32][352 * deltatime];
          v11[2] = this->m_sort[32][352 * deltatime + 1];
          *v10 = 0;
          v10[1] = 0;
          v10[2] = 0;
          *v9 = 0;
          (*(void ( **)(LONG *, _DWORD))this->m_RoleRc[57 * deltatime + 3].top)(
            &this->m_RoleRc[57 * deltatime + 3].top,
            0);
          v8 = &this->m_ListSaleTitle.m_bfocus + 6 * deltatime;
          goto LABEL_15;
        }
        break;
      case 4:
        v12 = (char *)&this->m_ListSaleTitle.m_rect.top + 6 * deltatime + 1;
        if ( *v12 )
        {
          v13 = &this->m_sort[33][352 * deltatime];
          v14 = (SaleUI_SortData *)(&Buffer.m_partyActor.m_pParticleData + 352 * deltatime + 4);
          *v14 = this->m_sort[33][352 * deltatime];
          v14[1] = this->m_sort[33][352 * deltatime + 1];
          v14[2] = this->m_sort[33][352 * deltatime + 2];
          *v13 = 0;
          v13[1] = 0;
          v13[2] = 0;
          *v12 = 0;
          (**((void ( ***)(LONG *, _DWORD))&this->m_Msg.m_rect.right + 228 * deltatime))(
            &this->m_Msg.m_rect.right + 228 * deltatime,
            0);
          v8 = (int *)(&this->m_ListSaleTitle.pDebugTex + 6 * deltatime);
          goto LABEL_15;
        }
        break;
      case 5:
        v18 = (char *)&this->m_ListSaleTitle.m_rect.top + 6 * deltatime + 2;
        if ( *v18 )
        {
          v19 = &this->m_sort[34][352 * deltatime + 1];
          v20 = (SaleUI_SortData *)&Buffer.m_partyActor.m_dwMatMsg[352 * deltatime + 3];
          *v20 = this->m_sort[34][352 * deltatime + 1];
          v20[1] = this->m_sort[34][352 * deltatime + 2];
          v20[2] = this->m_sort[34][352 * deltatime + 3];
          *v19 = 0;
          v19[1] = 0;
          v19[2] = 0;
          *v18 = 0;
          (**((void ( ***)(char *, _DWORD))&this->m_Msg.76 + 228 * deltatime + 44))(
            (char *)&this->m_Msg.76 + 912 * deltatime + 176,
            0);
          *((_BYTE *)&this->m_Icon[0][0].m_fontcolor.Color + 2 * deltatime + 1) = 0;
          v8 = &this->m_ListSaleTitle.m_align + 6 * deltatime;
LABEL_15:
          ++*(_DWORD *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *v8);
          v24 = (_DWORD *)(this->m_ListEquipTitleRc.bottom + 4 * *v8);
          --*v24;
          *(_DWORD *)this->remarkbuf = *v8;
        }
        break;
      default:
        break;
    }
    ((RoleSystem *)((char *)&Buffer + 1408 * deltatime))->RecalcAggregatedStats(0);
    v25 = &Buffer.m_partyActor.m_curact[1408 * deltatime + 39];
    v26 = 12;
    do
    {
      v27 = *((_DWORD *)v25 - 12);
      if ( *(_DWORD *)v25 < v27 )
      {
        if ( *(int *)v25 <= 0 )
          *(_DWORD *)v25 = 0;
      }
      else
      {
        *(_DWORD *)v25 = v27;
      }
      v25 += 4;
      --v26;
    }
    while ( v26 );
    v28 = haveinput + 6 * deltatime;
    if ( *(int *)(this->m_ListSaleTitle.m_childs.m_needscriptdel + 4 * *(&this->m_ListSaleTitle.m_bcreateok + v28)) <= 0 )
      ((CCBResultWindow *)&this->m_NotesNull[9 * v28 + 277][4])->SetDirty();
    else
      ((CCBResultWindow *)&this->m_NotesNull[9 * v28 + 277][4])->StartAnim();
    *(&this->m_ListSaleTitle.m_bcreateok + v28) = -1;
    ((UIListBox *)&this->m_ListGrid[3].m_disablepic)->GetItem();
    ((PlayerMgr *)this)->CreatePanelElements(*(CCBUIPanel **)this->remarkbuf);
    ((PlayerMgr *)this)->SetupPlayerDisplay(*(_DWORD *)this->remarkbuf);
    LOBYTE(this->m_ListSaleTitle.m_rect.left) = 1;
    return ((PAL3 *)this)->GetValue(0);
  }
  return result;
}

// 0x0046ACD0
int SaleUI::ConsumeItems()
{
  int i; // edi
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // eax

  for ( i = 0; i < *((_DWORD *)&this->m_data + 3419); ++i )
  {
    while ( *(int *)(this->m_ListEquipTitleRc.bottom + 4 * i) > 0 )
    {
      *(_DWORD *)&this->remarkbuf[24] = 0;
      while ( 1 )
      {
        v3 = *(_DWORD *)&this->remarkbuf[24];
        if ( this->m_sort[412][2]._tail_000[v3] )
        {
          *(_DWORD *)&this->remarkbuf[28] = 0;
          while ( 1 )
          {
            v4 = *(_DWORD *)&this->remarkbuf[28];
            if ( *(&this->m_ListSaleTitle.m_bcreateok + 6 * v3 + v4) == i )
              break;
            v5 = v4 + 1;
            *(_DWORD *)&this->remarkbuf[28] = v5;
            if ( v5 >= 6 )
              goto LABEL_10;
          }
          this->Update(v3, *(_DWORD *)&this->remarkbuf[28]);
          ((PAL3 *)this)->GetValue(0);
          LOBYTE(this->m_ListSaleTitle.m_rect.left) = 0;
          *(_DWORD *)&this->remarkbuf[28] = 1;
LABEL_10:
          if ( *(_DWORD *)&this->remarkbuf[28] == 1 )
            break;
        }
        v6 = *(_DWORD *)&this->remarkbuf[24] + 1;
        *(_DWORD *)&this->remarkbuf[24] = v6;
        if ( v6 >= 5 )
          goto LABEL_14;
      }
      *(_DWORD *)&this->remarkbuf[28] = 0;
LABEL_14:
      ;
    }
  }
  memset((void *)this->m_ListEquipTitleRc.bottom, 0, 4 * *((_DWORD *)&this->m_data + 3419));
  memset((void *)this->m_ListSaleTitle.m_childs.m_needscriptdel, 0, 4 * *((_DWORD *)&this->m_data + 3419));
  return 0;
}

// 0x0046B040
int SaleUI::ProcessCellAnimations(int deltatime, int haveinput)
{
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int *v7; // edx
  int v8; // eax
  int v9; // ecx
  int *v10; // edx
  int v11; // ebp
  int v12; // edx
  int *v13; // ecx
  int *v14; // edx
  int v15; // edi
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int *v19; // edx
  int v20; // eax
  int v21; // ecx
  int *v22; // edx
  int v23; // ebp
  int v24; // edx
  int *v25; // ecx
  int *v26; // edx
  int v27; // edi
  int v28; // ecx
  int v29; // eax
  int v30; // eax
  int v32; // [esp-0x14] [ebp-0x24] BYREF
  int v33; // [esp-0x10] [ebp-0x20]
  int v34; // [esp-0xC] [ebp-0x1C]
  int v35; // [esp-0x8] [ebp-0x18]
  SaleUI_SortData *v36; // [esp-0x4] [ebp-0x14]

  sub_46ADF0(this);
  ((GRPinput *)this)->ProcessButtonHold(*(float *)&deltatime);
  *(_DWORD *)&this->remarkbuf[20] = 0;
  do
  {
    if ( this->m_sort[412][2]._tail_000[*(_DWORD *)&this->remarkbuf[20]] )
    {
      *(_DWORD *)&this->remarkbuf[24] = 0;
      do
      {
        *(_DWORD *)&this->remarkbuf[28] = 0;
        do
        {
          *(&this->m_TempData[183][208 * *(_DWORD *)&this->remarkbuf[20] + 3].id
          + 104 * *(_DWORD *)&this->remarkbuf[24]
          + 13 * *(_DWORD *)&this->remarkbuf[28]) = 36;
          v4 = *(_DWORD *)&this->remarkbuf[28] + 1;
          *(_DWORD *)&this->remarkbuf[28] = v4;
        }
        while ( v4 < 8 );
        v6 = *(_DWORD *)&this->remarkbuf[24];
        v5 = v6 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v6) = *((_BYTE *)&this->m_TempData[115][3].id + 8 * v5);
        if ( (_BYTE)v6 )
        {
          v36 = &this->m_sort[412][304 * v5 + 4];
          v32 = *(&this->m_TempData[119][3].id + 32 * v5);
          v33 = *(&this->m_TempData[119][3].num + 32 * v5);
          v34 = *((_DWORD *)&this->m_TempData[119][3].item + 32 * v5);
          v35 = *(&this->m_TempData[119][4].id + 32 * v5);
          ((UIFrameWnd *)((char *)&this->m_TempData[183][3] + 416 * v5))->ProcessTimer(v6, 1, 1, v32);
        }
        else
        {
          v36 = &this->m_sort[443][304 * v5 + 1];
          v7 = &v32;
          v32 = *(&this->m_TempData[120][3].num + 32 * v5);
          v33 = *((_DWORD *)&this->m_TempData[120][3].item + 32 * v5);
          v34 = *(&this->m_TempData[120][4].id + 32 * v5);
          v35 = *(&this->m_TempData[120][4].num + 32 * v5);
          LOBYTE(v7) = *((_BYTE *)&this->m_TempData[115][3].num + 8 * v5);
          ((UIFrameWnd *)(&this->m_TempData[187][0].num + 104 * v5))->ProcessTimer((BOOL)v7, 1, 1, v32);
        }
        v9 = *(_DWORD *)&this->remarkbuf[24];
        v8 = v9 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v9) = *((_BYTE *)&this->m_TempData[115][3].id + 8 * v8 + 1);
        if ( (_BYTE)v9 )
        {
          if ( *((_BYTE *)&this->m_TempData[115][3].id + 8 * v8) )
          {
            v36 = &this->m_sort[420][304 * v8 + 2];
            v10 = (int *)(&this->m_TempData[120][0].item + 32 * v8);
          }
          else
          {
            v36 = &this->m_sort[420][304 * v8 + 2];
            v10 = (int *)((char *)&this->m_TempData[119][3] + 128 * v8);
          }
          v32 = *v10;
          v33 = v10[1];
          v11 = v10[2];
          v12 = v10[3];
          v34 = v11;
          v35 = v12;
          ((UIFrameWnd *)(&this->m_TempData[184][2].num + 104 * v8))->ProcessTimer(v9, 1, 1, v32);
        }
        else
        {
          if ( *((_BYTE *)&this->m_TempData[115][3].num + 8 * v8) )
          {
            v36 = &this->m_sort[450][304 * v8 + 4];
            v13 = (int *)((char *)&this->m_TempData[121][1] + 128 * v8);
          }
          else
          {
            v36 = &this->m_sort[450][304 * v8 + 4];
            v13 = &this->m_TempData[120][3].num + 32 * v8;
          }
          v14 = &v32;
          v32 = *v13;
          v33 = v13[1];
          v15 = v13[2];
          v16 = v13[3];
          v34 = v15;
          v35 = v16;
          LOBYTE(v14) = *((_BYTE *)&this->m_TempData[115][3].num + 8 * v8 + 1);
          ((UIFrameWnd *)(&this->m_TempData[187][4].item + 104 * v8))->ProcessTimer((BOOL)v14, 1, 1, v32);
        }
        v18 = *(_DWORD *)&this->remarkbuf[24];
        v17 = v18 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v18) = *((_BYTE *)&this->m_TempData[115][3].id + 8 * v17 + 2);
        if ( (_BYTE)v18 )
        {
          v36 = &this->m_sort[428][304 * v17];
          v32 = *((_DWORD *)&this->m_TempData[120][0].item + 32 * v17);
          v33 = *(&this->m_TempData[120][1].id + 32 * v17);
          v34 = *(&this->m_TempData[120][1].num + 32 * v17);
          v35 = *((_DWORD *)&this->m_TempData[120][1].item + 32 * v17);
          ((UIFrameWnd *)(&this->m_TempData[185][1].item + 104 * v17))->ProcessTimer(v18, 1, 1, v32);
        }
        else
        {
          v36 = &this->m_sort[458][304 * v17 + 2];
          v19 = &v32;
          v32 = *(&this->m_TempData[121][1].id + 32 * v17);
          v33 = *(&this->m_TempData[121][1].num + 32 * v17);
          v34 = *((_DWORD *)&this->m_TempData[121][1].item + 32 * v17);
          v35 = *(&this->m_TempData[121][2].id + 32 * v17);
          LOBYTE(v19) = *((_BYTE *)&this->m_TempData[115][3].num + 8 * v17 + 2);
          ((UIFrameWnd *)((char *)&this->m_TempData[188][4] + 416 * v17))->ProcessTimer((BOOL)v19, 1, 1, v32);
        }
        v21 = *(_DWORD *)&this->remarkbuf[24];
        v20 = v21 + 6 * *(_DWORD *)&this->remarkbuf[20];
        LOBYTE(v21) = *((_BYTE *)&this->m_TempData[115][3].id + 8 * v20 + 3);
        if ( (_BYTE)v21 )
        {
          if ( *((_BYTE *)&this->m_TempData[115][3].id + 8 * v20 + 2) )
          {
            v36 = &this->m_sort[435][304 * v20 + 3];
            v22 = (int *)((char *)&this->m_TempData[119][3] + 128 * v20);
          }
          else
          {
            v36 = &this->m_sort[435][304 * v20 + 3];
            v22 = (int *)(&this->m_TempData[120][0].item + 32 * v20);
          }
          v32 = *v22;
          v33 = v22[1];
          v23 = v22[2];
          v24 = v22[3];
          v34 = v23;
          v35 = v24;
          ((UIFrameWnd *)((char *)&this->m_TempData[186][1] + 416 * v20))->ProcessTimer(v21, 1, 1, v32);
        }
        else
        {
          if ( *((_BYTE *)&this->m_TempData[115][3].num + 8 * v20 + 2) )
          {
            v36 = &this->m_sort[466][304 * v20];
            v25 = &this->m_TempData[120][3].num + 32 * v20;
          }
          else
          {
            v36 = &this->m_sort[466][304 * v20];
            v25 = (int *)((char *)&this->m_TempData[121][1] + 128 * v20);
          }
          v26 = &v32;
          v32 = *v25;
          v33 = v25[1];
          v27 = v25[2];
          v28 = v25[3];
          v34 = v27;
          v35 = v28;
          LOBYTE(v26) = *((_BYTE *)&this->m_TempData[115][3].num + 8 * v20 + 3);
          ((UIFrameWnd *)(&this->m_TempData[189][3].num + 104 * v20))->ProcessTimer((BOOL)v26, 1, 1, v32);
        }
        v29 = *(_DWORD *)&this->remarkbuf[24] + 1;
        *(_DWORD *)&this->remarkbuf[24] = v29;
      }
      while ( v29 < 6 );
    }
    v30 = *(_DWORD *)&this->remarkbuf[20] + 1;
    *(_DWORD *)&this->remarkbuf[20] = v30;
  }
  while ( v30 < 5 );
  ((UIListBox *)this)->Update(deltatime, haveinput);
  return 1;
}

// 0x004AB5E0
int SaleUI::InitColumnWidths()
{
  *((_DWORD *)this + 95804) = 70;
  *((_DWORD *)this + 95807) = 70;
  *((_DWORD *)this + 95803) = 40;
  *((_DWORD *)this + 95805) = 60;
  *((_DWORD *)this + 95806) = 90;
  *((_DWORD *)this + 95808) = 110;
  *((_DWORD *)this + 95809) = 90;
  *((_DWORD *)this + 95810) = 120;
  *((_DWORD *)this + 95811) = 90;
  *((_DWORD *)this + 95812) = 130;
  *((_DWORD *)this + 95813) = 95;
  *((_DWORD *)this + 95814) = 145;
  *((_DWORD *)this + 95815) = 110;
  *((_DWORD *)this + 95816) = 160;
  *((_DWORD *)this + 95817) = 120;
  *((_DWORD *)this + 95818) = 185;
  *((_DWORD *)this + 95819) = 140;
  *((_DWORD *)this + 95820) = 200;
  *((_DWORD *)this + 95821) = 150;
  *((_DWORD *)this + 95822) = 220;
  *((_DWORD *)this + 95823) = 205;
  *((_DWORD *)this + 95824) = 265;
  return 90;
}

// 0x00525120
int SaleUI::InitUI()
{
  char *v2; // edi
  int v3; // ebp
  char *v4; // edi
  int v5; // ebp

  *(_DWORD *)&this->buf[8] = 800;
  *(_DWORD *)&this->buf[12] = 600;
  sub_4422E0((char *)&this->m_data + 1028);
  sub_4422E0((char *)&this->m_data + 1180);
  sub_4422E0((char *)&this->m_data + 1332);
  UIScene::GetSys();
  ((UIProgressBar *)((char *)&this->m_data + 3408))->ctor();
  ((UIProgressBar *)((char *)&this->m_data + 3716))->ctor();
  ((UIProgressBar *)((char *)&this->m_data + 4024))->ctor();
  v2 = (char *)&this->m_data + 4332;
  v3 = 2;
  do
  {
    v2 += 12;
    --v3;
  }
  while ( v3 );
  sub_4422E0((char *)&this->m_data + 4356);
  sub_4422E0((char *)&this->m_data + 4508);
  sub_4422E0((char *)&this->m_data + 4660);
  sub_4422E0((char *)&this->m_data + 4812);
  sub_4422E0((char *)&this->m_data + 4964);
  sub_4422E0((char *)&this->m_data + 5116);
  sub_4422E0((char *)&this->m_data + 5268);
  sub_4422E0((char *)&this->m_data + 5420);
  *((_BYTE *)&this->m_data + 5596) = 0;
  *((_DWORD *)&this->m_data + 1398) = 0;
  *((_DWORD *)&this->m_data + 1397) = 0;
  *((_BYTE *)&this->m_data + 5608) = 0;
  ((UIButton *)(&this->m_data + 23))->ctor_17();
  ((UITextArea *)((char *)&this->m_data + 5872))->InitAfterClear();
  sub_4422E0((char *)&this->m_data + 6064);
  sub_4422E0((char *)&this->m_data + 6216);
  v4 = (char *)&this->m_data + 6376;
  v5 = 5;
  do
  {
    ArraySort((int)v4, 800, 2, 0 /* TODO: (int)ArcSceneObject::InitFromConfig */);
    v4 += 1608;
    --v5;
  }
  while ( v5 );
  *((_BYTE *)&this->m_data + 14408) = 0;
  *((_DWORD *)&this->m_data + 3603) = 0;
  *((_BYTE *)&this->m_data + 14416) = 0;
  *((_BYTE *)&this->m_data + 14422) = 0;
  *((_DWORD *)&this->m_data + 3606) = 3;
  *((_DWORD *)&this->m_data + 3609) = 0;
  *((_BYTE *)&this->m_data + 14440) = 0;
  *((_BYTE *)&this->m_data + 14441) = 0;
  *((_BYTE *)&this->m_data + 14442) = 0;
  LOBYTE(this->m_ListGrid[3].m_ppic) = 0;
  BYTE1(this->m_ListGrid[3].m_ppic) = 0;
  this->m_ListGrid[3].m_ppicInfo = 0;
  ((ARC_PlayerAtt *)&this->m_ListGrid[3].m_disablepic)->Refresh();
  ((ARC_PlayerAtt *)&this->m_ListGrid[12].m_disablepic)->Refresh();
  *(_DWORD *)((char *)&this->m_data + 14417) = 0;
  *((_BYTE *)&this->m_data + 14421) = 0;
  *((_DWORD *)&this->m_data + 3607) = 0;
  *((_BYTE *)&this->m_data + 14432) = 0;
  *((_DWORD *)&this->m_data + 3613) = 0;
  *((_DWORD *)&this->m_data + 3612) = 0;
  *((_DWORD *)&this->m_data + 3611) = 0;
  *((_DWORD *)&this->m_data + 3617) = 0;
  *((_DWORD *)&this->m_data + 3616) = 0;
  *((_DWORD *)&this->m_data + 3615) = 0;
  *((_DWORD *)&this->m_data + 3614) = 0;
  *((_DWORD *)&this->m_data + 1401) = 0;
  *((_DWORD *)&this->m_data + 1400) = 1;
  *((_BYTE *)&this->m_data + 5580) = 0;
  *((_DWORD *)&this->m_data + 1396) = 0;
  *((_WORD *)&this->m_data + 1282) = (unsigned __int16)byte_1010101;
  *((_BYTE *)&this->m_data + 2566) = (unsigned __int8)byte_1010101;
  return (int)this;
}

// 0x005263C0
int SaleUI::ResetGridState()
{
  int v2; // esi
  char *v3; // ebx
  int v4; // eax
  const void *v5; // esi
  int v6; // eax
  void *v7; // edi
  bool v8; // zf
  int result; // eax
  float fX; // [esp+0x0] [ebp-0x28]
  int fXa; // [esp+0x0] [ebp-0x28]
  float fXb; // [esp+0x0] [ebp-0x28]
  int fXc; // [esp+0x0] [ebp-0x28]
  float fY; // [esp+0x4] [ebp-0x24]
  float fYa; // [esp+0x4] [ebp-0x24]
  int v16; // [esp+0x18] [ebp-0x10]
  int v17; // [esp+0x1C] [ebp-0xC]
  int v18; // [esp+0x24] [ebp-0x4]

  v16 = 36;
  v2 = *(_DWORD *)this->m_ListGrid[3].m_text - this->m_ListGrid[3].m_texty;
  v17 = v2;
  v18 = (int)this->m_ListGrid[3].m_pbk - *(_DWORD *)&this->m_ListGrid[3].m_text[8];
  v3 = (char *)&this->m_data + 14472;
  while ( 1 )
  {
    ((RenderTarget *)v3)->LoadTexture("UI\\GameMainUI\\Par_Effect\\spark_16.tga");
    ((RenderTarget *)v3)->SetSize(16);
    ((RenderTarget *)v3)->SetColor(0x64u, 0x64u, 0xD2u);
    v4 = rand();
    ((RenderTarget *)v3)->SetAlpha(v4 % 100 - 101);
    ((RenderTarget *)v3)->SetField084();
    ((RenderTarget *)v3)->SetState();
    fY = (float)(int)this->m_ListGrid[3].m_fonttype;
    fX = (float)(this->m_ListGrid[3].m_texty + rand() % v2);
    ((RenderTarget *)v3)->UpdateTransform(fX, fY);
    ((RenderTarget *)v3)->Render(this->m_ListGrid[3].m_texty, (int)this->m_ListGrid[3].m_fonttype, *(_DWORD *)this->m_ListGrid[3].m_text);
    rand();
    *(float *)&fXa = (float)(rand() % 2 + 1);
    ((RenderTarget *)v3)->SetOffset(fXa);
    ((RenderTarget *)v3)->SetScale(0);
    ((RenderTarget *)v3)->SetVisible(1);
    qmemcpy(v3 + 21024, v3, 0x248u);
    v5 = v3 + 42048;
    ((RenderTarget *)(v3 + 42048))->LoadTexture("UI\\GameMainUI\\Par_Effect\\spark_16.tga");
    ((RenderTarget *)(v3 + 42048))->SetSize(16);
    ((RenderTarget *)(v3 + 42048))->SetColor(0x64u, 0x64u, 0xD2u);
    v6 = rand();
    ((RenderTarget *)(v3 + 42048))->SetAlpha(v6 % 100 - 101);
    ((RenderTarget *)(v3 + 42048))->SetField084();
    ((RenderTarget *)(v3 + 42048))->SetState();
    fYa = (float)*(int *)&this->m_ListGrid[3].m_text[12];
    fXb = (float)(*(_DWORD *)&this->m_ListGrid[3].m_text[8] + rand() % v18);
    ((RenderTarget *)(v3 + 42048))->UpdateTransform(fXb, fYa);
    ((RenderTarget *)(v3 + 42048))->Render(*(_DWORD *)&this->m_ListGrid[3].m_text[8], *(_DWORD *)&this->m_ListGrid[3].m_text[12], (int)this->m_ListGrid[3].m_pbk);
    rand();
    *(float *)&fXc = (float)(rand() % 2 + 1);
    ((RenderTarget *)(v3 + 42048))->SetOffset(fXc);
    ((RenderTarget *)(v3 + 42048))->SetScale(0);
    ((RenderTarget *)(v3 + 42048))->SetVisible(1);
    v7 = v3 + 63072;
    v3 += 584;
    result = v16 - 1;
    v8 = v16 == 1;
    qmemcpy(v7, v5, 0x248u);
    --v16;
    if ( v8 )
      break;
    v2 = v17;
  }
  BYTE2(this->m_ListGrid[3].m_ppic) = 0;
  return result;
}

// 0x00526A40
int SaleUI::OnMessage(int thisa, UIWnd *a2, char *nMsg, int wParam)
{
  ARC_PlayerAtt *v7; // edx
  int v8; // eax
  const char **v9; // ecx
  int v10; // edi
  const char **v11; // ebp
  void ( **v12)(char *, int); // edx
  CScreenMode *Instance; // eax
  CScreenMode *v14; // eax
  char *v15; // eax
  char *v16; // ecx
  char *v17; // esi
  void ( **v18)(char *, _DWORD); // edx
  void ( **v19)(char *, _DWORD); // eax
  int v20; // ebp
  int *v21; // edi
  int v22; // edi
  char *v23; // ebp
  int v24; // ecx
  char *v25; // esi
  int v26; // edi
  int v27; // eax
  char *v28; // esi
  int v29; // edi
  const void *v30; // [esp-0x8] [ebp-0x24]
  _SPropValue *v31; // [esp-0x8] [ebp-0x24]
  int v32; // [esp-0x4] [ebp-0x20]
  int *v33; // [esp+0x0] [ebp-0x1C]
  int pOut; // [esp+0x10] [ebp-0xC] BYREF
  int pOut2; // [esp+0x14] [ebp-0x8] BYREF
  int SkillNum; // [esp+0x18] [ebp-0x4]
  char *thisb; // [esp+0x20] [ebp+0x4]

  switch ( thisa )
  {
    case 1000:
      if ( !a2 )
        return 1;
      ((PAL_GDB *)this)->RefreshPartyStats();
      ((MUIDialog *)this)->SetSlotCaption(*((_DWORD *)&this->m_data + 3603));

      return 1;
    case 1001:
      v7 = (ARC_PlayerAtt *)a2;
      v8 = 0;
      v9 = &off_5706AC;
      while ( a2 != (UIWnd *)*v9 )
      {
        ++v9;
        ++v8;
        if ( (int)v9 >= (int)&off_5706C0 )
        {
          v10 = 0;
          v11 = &off_5706C0;
          thisb = (char *)&this->m_data + 1484;
          do
          {
            if ( !*((_BYTE *)&this->m_data + 5580) && v7 == (ARC_PlayerAtt *)*v11 )
            {
              if ( !*((_BYTE *)&this->m_data + 14422) )
              {
                v12 = (void ( **)(char *, int))*((_DWORD *)&this->m_data + 1279);
                *((_BYTE *)&this->m_data + 5580) = 1;
                (*v12)((char *)&this->m_data + 5116, 1);
                *((_DWORD *)&this->m_data + 1396) = v10;
                sub_445E50((int)thisb);
                *((_DWORD *)&this->m_data + 1074) = 0;
                *((_DWORD *)&this->m_data + 1073) = 0;
                *((_DWORD *)&this->m_data + 1072) = 0;
              }
              v30 = off_5E7ECC;
              Instance = CScreenMode::GetInstance();
              ((CScreenMode *)Instance)->AudioSetPosition(v30, 1);
              v7 = (ARC_PlayerAtt *)a2;
            }
            ++v11;
            ++v10;
            thisb += 344;
          }
          while ( (int)v11 < (int)&off_5706CC );
          if ( v7 == (ARC_PlayerAtt *)&g_PlayerAttBuffer.Remark[272] )
          {
            if ( *((_BYTE *)&this->m_data + 14422) )
              return 1;
            if ( *((_BYTE *)&this->m_data + 5580) )
            {
              *((_DWORD *)&this->m_data + 662) = 0;
              *((_BYTE *)&this->m_data + 2636) = 0;
            }
            *((_BYTE *)&this->m_data + 14416) = 1;
            *((_DWORD *)&this->m_data + 724) = 0;
            *((_BYTE *)&this->m_data + 2884) = 0;
            (**((void ( ***)(char *, int))&this->m_data + 766))((char *)&this->m_data + 3064, 1);
            if ( *((_DWORD *)&this->m_data + 3609) )
              *((_BYTE *)&this->m_data + *((_DWORD *)&this->m_data + 3603) + 14428) = 0;
            else
              *((_BYTE *)&this->m_data + *((_DWORD *)&this->m_data + 3603) + 14428) = 1;
            if ( !*((_BYTE *)&this->m_data + 2636) && !*((_BYTE *)&this->m_data + 2884) )
            {
              v19 = (void ( **)(char *, _DWORD))*((_DWORD *)&this->m_data + 766);
              *((_BYTE *)&this->m_data + 14416) = 0;
              (*v19)((char *)&this->m_data + 3064, 0);
              *((_BYTE *)&this->m_data + *((_DWORD *)&this->m_data + 3603) + 14428) = 0;
            }
          }
          else
          {
            if ( (char *)v7 - &g_PlayerAttBuffer.Remark[272] != 1 )
            {
              if ( (char *)v7 - &g_PlayerAttBuffer.Remark[272] == 2
                && !*((_BYTE *)&this->m_data + 14422)
                && !*((_BYTE *)&this->m_data + 5580) )
              {
                ((CCBUI *)this)->PlayResultSound();
                goto LABEL_20;
              }
              return 1;
            }
            if ( *((_BYTE *)&this->m_data + 14422) )
              return 1;
            if ( *((_BYTE *)&this->m_data + 5580) )
            {
              *((_DWORD *)&this->m_data + 724) = 0;
              *((_BYTE *)&this->m_data + 2884) = 0;
            }
            *((_BYTE *)&this->m_data + 14416) = 1;
            *((_DWORD *)&this->m_data + 662) = 0;
            *((_BYTE *)&this->m_data + 2636) = 0;
            (**((void ( ***)(char *, int))&this->m_data + 766))((char *)&this->m_data + 3064, 1);
            if ( *((_DWORD *)&this->m_data + 3609) )
              *((_BYTE *)&this->m_data + *((_DWORD *)&this->m_data + 3603) + 14428) = 0;
            else
              *((_BYTE *)&this->m_data + *((_DWORD *)&this->m_data + 3603) + 14428) = 1;
            if ( !*((_BYTE *)&this->m_data + 2636) && !*((_BYTE *)&this->m_data + 2884) )
            {
              v18 = (void ( **)(char *, _DWORD))*((_DWORD *)&this->m_data + 766);
              *((_BYTE *)&this->m_data + 14416) = 0;
              (*v18)((char *)&this->m_data + 3064, 0);
              *((_BYTE *)&this->m_data + *((_DWORD *)&this->m_data + 3603) + 14428) = 0;
            }
          }
          ((UICoverFrm *)this)->ResetStarFrames(*((_DWORD *)&this->m_data + 3603));
          v31 = (_SPropValue *)off_5E7ECC;
          goto LABEL_21;
        }
      }
      if ( *((_BYTE *)&this->m_data + 5580) )
      {
        v15 = (char *)this + 248 * v8;
        if ( v15[420] )
        {
          *((_DWORD *)v15 + 108) = 0;
          v15[420] = 0;
        }
        else
        {
          *((_DWORD *)v15 + 108) = 1;
          v15[420] = 1;
        }
        return 1;
      }
      if ( *((_BYTE *)&this->m_data + 14416) || *((_BYTE *)&this->m_data + 14422) )
      {
        if ( !*((_BYTE *)&this->m_data + v8 + 14417) )
        {
          v16 = &this->remarkbuf[248 * v8 + 16];
          *((_DWORD *)v16 + 20) = 0;
          v16[68] = 0;
        }
        if ( *((_DWORD *)&this->m_data + 3603) == v8 )
        {
          v17 = &this->remarkbuf[248 * v8 + 16];
          *((_DWORD *)v17 + 20) = 1;
          v17[68] = 1;
        }
        v31 = off_5E7ED8;
      }
      else if ( *((_BYTE *)&this->m_data + v8 + 14417) )
      {
        v31 = off_5E7ED8;
      }
      else
      {
        *((_DWORD *)&this->m_data + 3603) = v8;
        if ( ((CCBAttackSequen *)this)->FindSequenceSlot(v8) > 0 )
          ((MUIDialog *)this)->SetSlotCaption(*((_DWORD *)&this->m_data + 3603));
LABEL_20:
        v31 = (_SPropValue *)off_5E7ECC;
      }
LABEL_21:
      v14 = CScreenMode::GetInstance();
      ((CScreenMode *)v14)->AudioSetPosition(v31, 1);
      return 1;
    case 1002:
      if ( a2 == (UIWnd *)&g_PlayerAttBuffer.Remark[272] )
      {
        if ( !*((_BYTE *)&this->m_data + 14422) && !*((_BYTE *)&this->m_data + 5580) )
          LOBYTE(this->m_ListGrid[3].m_ppic) = 1;
      }
      else if ( (char *)a2 - &g_PlayerAttBuffer.Remark[272] == 1
             && !*((_BYTE *)&this->m_data + 14422)
             && !*((_BYTE *)&this->m_data + 5580) )
      {
        BYTE1(this->m_ListGrid[3].m_ppic) = 1;
        return 1;
      }
      return 1;
    case 1009:
      if ( a2 != (UIWnd *)&g_PlayerAttBuffer.Remark[284] )
        return 1;
      if ( LOBYTE(this->m_ListGrid[3].m_ppicInfo[2]._tex_uvRB.v) )
      {
        v20 = 0;
        v21 = (int *)((char *)&this->m_data + 6372);
        do
        {
          if ( *((_BYTE *)&this->m_data + v20 + 14428) )
          {
            v32 = *v21;
            pOut2 = 0;
            SkillNum = 0;
            pOut = v32;
            SkillNum = ((PAL_GDB *)&g_pGDB)->GDB_GetSkillNum(v32);
            pOut2 = 1;
            ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAlive((int)&pOut, v33);
          }
          ++v20;
          v21 += 402;
        }
        while ( v20 < 5 );
      }
      ((CScreenMode *)this->m_ListGrid[3].m_ppicInfo)->InitSceneAudio(3);
      return 1;
    case 1010:
      if ( *((_BYTE *)&this->m_data + 14422) )
      {
        ((UICoverFrm *)this)->ResetStarFrames(*((_DWORD *)&this->m_data + 3603));
        *((_DWORD *)&this->m_data + 1074) = 0;
        *((_DWORD *)&this->m_data + 1073) = 0;
        *((_DWORD *)&this->m_data + 1072) = 0;
        v22 = 0;
        v23 = (char *)&this->m_data + 1484;
        do
        {
          if ( *((_BYTE *)&this->m_data + v22 + 2564) )
            sub_445E50((int)v23);
          ++v22;
          v23 += 344;
        }
        while ( v22 < 3 );
      }
      return 1;
    case 1013:
      if ( a2 == (UIWnd *)&g_PlayerAttBuffer.Remark[287] )
      {
        if ( *((_BYTE *)&this->m_data + 5580) )
        {
          ((UICoverFrm *)this)->UpdateClouds(0, *((_DWORD *)&this->m_data + 3603));
          v27 = *((_DWORD *)&this->m_data + 1396);
          v28 = (char *)&this->m_data + 1484;
          v29 = 3;
          v28[v27 + 1080] = 0;
          do
          {
            sub_445E50((int)v28);
            v28 += 344;
            --v29;
          }
          while ( v29 );
        }
        return 1;
      }
      if ( (char *)a2 - &g_PlayerAttBuffer.Remark[287] != 1 || !*((_BYTE *)&this->m_data + 5580) )
        return 1;
      ((UICoverFrm *)this)->UpdateClouds(1, *((_DWORD *)&this->m_data + 3603));
      v24 = *((_DWORD *)&this->m_data + 1396);
      v25 = (char *)&this->m_data + 1484;
      v26 = 3;
      v25[v24 + 1080] = 0;
      do
      {
        sub_445E50((int)v25);
        v25 += 344;
        --v26;
      }
      while ( v26 );
      return 1;
    case 1016:
      if ( a2 == (UIWnd *)&g_PlayerAttBuffer.Remark[289] )
      {
        ((GRPinput *)&g_Input)->GetMousePos(&pOut, &pOut2);
        *((float *)&this->m_data + 1072) = (double)pOut2 + *((float *)&this->m_data + 1072);
        *((float *)&this->m_data + 1073) = (double)pOut + *((float *)&this->m_data + 1073);
      }
      return 1;
    default:
      return ((PalScript *)this)->OnMessage(thisa, (int)a2, (int)nMsg);
  }
}
