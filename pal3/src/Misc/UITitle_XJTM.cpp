#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_XJTM.h"

// Forward declarations for unnamed functions
int sub_43FD90(float *_this, int a2); // from annotations
void sub_43FDB0(float *_this, int a2); // from annotations
int sub_43FEC0(void *a2); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations

// Unnamed globals (extern)
extern int dword_56E148[];
extern int off_59DD60;
extern LPCSTR off_59DD80;
extern int off_59DDA0;

// 0x0044CC60
int UITitle_XJTM::CreateSubWidgets()
{
  int *v2; // ebp
  UIStatic *v3; // esi
  int v4; // edi
  int v5; // edx
  void *v6; // eax
  unsigned int v7; // ecx
  UIStatic *v8; // edx
  int v9; // eax
  int v10; // ecx
  int v12; // [esp+0x10] [ebp-0x14]
  void *v13; // [esp+0x14] [ebp-0x10] BYREF
  unsigned int v14; // [esp+0x18] [ebp-0xC]
  int v15; // [esp+0x1C] [ebp-0x8]
  int v16; // [esp+0x20] [ebp-0x4]

  v13 = 0;
  v14 = 0;
  v15 = 128;
  v16 = 128;
  ((CCBStageRole *)this)->RandomizePositions();
  v2 = &off_59DD60;
  v3 = (UIStatic *)((char *)this + 5088);
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD, vtbl_0056AE2C **, UITitle_XJTM *))v3->__vftable->Create)(
// [VFTABLE]   v3,
// [VFTABLE]   0,
// [VFTABLE]   &v13,
// [VFTABLE]   this);
    if ( (int)v2 < (int)&off_59DD80 )
    {
      ((UIStatic *)v3)->CreateFromTemplate();
    }
    else
    {
      v4 = rand() & 7;
      ((UIStatic *)v3)->CreateFromTemplate();
      v3[1].m_rect.top = *((_DWORD *)this + 52 * v4 + 1315);
      v3[1].m_rect.right = *((_DWORD *)this + 52 * v4 + 1316);
    }
    *(float *)&v3[1].m_pfather = (float)(rand() % 255);
    ++v2;
    v5 = rand() % 10;
    v6 = v13;
    v7 = v14;
    v12 = v5 + 10;
    v8 = v3 + 1;
    v3 = (UIStatic *)((char *)v3 + 208);
    *(float *)&v3[-1].m_disablepicInfo = (double)v12 * 0.1;
    LOBYTE(v3[-1].m_pbk2) = 1;
// [VFTABLE] v8->__vftable = v6;
    v9 = v15;
    v8->m_fontcolor.Color = v7;
    v10 = v16;
    v8->m_wndcolor.Color = v9;
    v8->m_id = (void *)v10;
  }
  while ( (int)v2 < (int)&off_59DDA0 );
  return ((RoleShadow *)this)->InitParticles();
}

// 0x00486D20
void UITitle_XJTM::DestroyStatics()
{
  sub_4422E0(this);
  UIScene::GetSys();
  sub_4422E0(&this->m_OutFrameL.m_ratioh);
  sub_4422E0(&this->m_OutFrameB.m_align);
  ((UIButton *)&this->m_background.m_bfocus)->ctor_17();
  sub_4422E0(&this->m_title.m_nTextW);
  sub_4422E0(&this->m_exit.m_texarray.m_ptex[11]);
  ((UIButton *)&this->m_exit.m_caption[100])->ctor_17();
  sub_4422E0(&this->m_WordBk.m_ppicInfo);
  sub_4422E0(&this->m_BtnBk.m_pbkInfo);
  ((UIButton *)&this->m_BtnFirstRow[0].m_texarray.m_ptex[3])->ctor_17();
  sub_4422E0(&this->m_BtnFirstRow[1].m_wndcolor);
  sub_4422E0(&this->m_BtnFirstRow[1].m_texarray.m_num);
  sub_4422E0(&this->m_BtnFirstRow[1].m_caption[120]);
  sub_4422E0(&this->m_BtnFirstRow[2].m_texarray.m_ptex[6]);
  sub_4422E0(&this->m_BtnFirstRow[2].m_caption[80]);
  sub_4422E0(&this->m_BtnFirstRow[3].m_canctrl);
  sub_4422E0(&this->m_BtnFirstRow[3].m_caption[40]);
  sub_4422E0(&this->m_BtnSecondRow[0].m_childs.capacity);
  sub_4422E0(this->m_BtnSecondRow[0].m_caption);
  sub_4422E0(&this->m_BtnSecondRow[1]);
  sub_4422E0(&this->m_BtnSecondRow[1].m_texarray.m_ptex[14]);
  sub_4422E0(&this->m_BtnSecondRow[1].m_caption[112]);
  sub_4422E0(&this->m_BtnSecondRow[4].m_mouseoff);
}

// 0x00486EF0
void UITitle_XJTM::DestroyFrames()
{
  ((UIFrameWnd *)&this->m_BtnSecondRow[4].m_mouseoff)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[1].m_caption[112])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[1].m_texarray.m_ptex[14])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[1])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)this->m_BtnSecondRow[0].m_caption)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[0].m_childs.capacity)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[3].m_caption[40])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[3].m_canctrl)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[2].m_caption[80])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[2].m_texarray.m_ptex[6])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[1].m_caption[120])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[1].m_texarray.m_num)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[1].m_wndcolor)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_BtnFirstRow[0].m_texarray.m_ptex[3])->_UIButton();
  ((UIFrameWnd *)&this->m_BtnBk.m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_WordBk.m_ppicInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_exit.m_caption[100])->_UIButton();
  ((UIFrameWnd *)&this->m_exit.m_texarray.m_ptex[11])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_title.m_nTextW)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_background.m_bfocus)->_UIButton();
  ((UIFrameWnd *)&this->m_OutFrameB.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameL.m_ratioh)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_OutFrameT.m_bvisible)->Destroy2();
// [VFTABLE] ((UIFrameWnd *)&this->__vftable)->_UIFrameWnd();
}

// 0x00487C40
int UITitle_XJTM::UpdateMonsterEntry(int nVal, int *pnVal)
{
  int v4; // ecx
  int v5; // edx
  char *v6; // esi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int result; // eax
  int v11; // [esp+0x18] [ebp-0x10] BYREF
  int v12; // [esp+0x1C] [ebp-0xC]
  int v13; // [esp+0x20] [ebp-0x8]
  int v14; // [esp+0x24] [ebp-0x4]

  if ( nVal <= 5 )
  {
    v4 = *pnVal;
    v12 = pnVal[1];
    v14 = v12 + 12;
    v5 = (int)*(&g_ArcSceneMonsterTable + nVal);
    v11 = v4;
    v6 = (char *)this + 4892 * nVal;
    v7 = *((_DWORD *)v6 + 53350);
    v13 = v4 + 85;
    (*(void ( **)(char *, int, int *, UITitle_XJTM *))(v7 + 16))(v6 + 213400, v5, &v11, this);
    ((UIScene *)(v6 + 213400))->GetChildCount();
    ((UIScene *)(v6 + 213400))->GetChildAt();
    *((_DWORD *)v6 + 53368) = 1;
    v6[213570] = -30;
    v6[213569] = -51;
    v6[213568] = 58;
    v6[213571] = -1;
    sub_43FD90((float *)v6 + 53350, 4);
    ((UIWnd *)(v6 + 213400))->GetWidth(-4);
    sub_43FDB0((float *)v6 + 53350, 1);
    ((UIWnd *)(v6 + 213400))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 53624) + 16))(
      v6 + 214496,
      *(&g_ArcSceneMonsterTable + nVal),
      &v11,
      this);
    ((UIScene *)(v6 + 214496))->GetChildCount();
    ((UIScene *)(v6 + 214496))->GetChildAt();
    *((_DWORD *)v6 + 53642) = 1;
    v6[214666] = -30;
    v6[214665] = -51;
    v6[214664] = 58;
    v6[214667] = -1;
    sub_43FD90((float *)v6 + 53624, 4);
    ((UIWnd *)(v6 + 214496))->GetWidth(-4);
    sub_43FDB0((float *)v6 + 53624, 1);
    ((UIWnd *)(v6 + 214496))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 53487) + 16))(
      v6 + 213948,
      *(&g_ArcSceneMonsterTable + nVal),
      &v11,
      this);
    ((UIScene *)(v6 + 213948))->GetChildCount();
    ((UIScene *)(v6 + 213948))->GetChildAt();
    *((_DWORD *)v6 + 53505) = 1;
    v6[214118] = -30;
    v6[214117] = -51;
    v6[214116] = 58;
    v6[214119] = -1;
    sub_43FD90((float *)v6 + 53487, 4);
    ((UIWnd *)(v6 + 213948))->GetWidth(-4);
    sub_43FDB0((float *)v6 + 53487, 1);
    ((UIWnd *)(v6 + 213948))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 53411) + 16))(
      v6 + 213644,
      *(&g_ArcSceneMonsterTable + nVal),
      pnVal,
      this);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 53685) + 16))(
      v6 + 214740,
      *(&g_ArcSceneMonsterTable + nVal),
      pnVal,
      this);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 53548) + 16))(
      v6 + 214192,
      *(&g_ArcSceneMonsterTable + nVal),
      pnVal,
      this);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 53150) + 16))(
      v6 + 212600,
      *(&g_ArcSceneMonsterTable + nVal),
      pnVal,
      this);
    ((UIStatic *)(v6 + 212600))->CreateFromTemplate();
    LOBYTE(v8) = g_bDebugMode;
    (*(void ( **)(char *, int, int *, UITitle_XJTM *, char *, int, int))(*((_DWORD *)v6 + 53188) + 28))(
      v6 + 212752,
      g_MonsterEntryTable[nVal],
      pnVal,
      this,
      &"UI\\GameMainUI\\Communal\\RoleHead0"[256 * nVal],
      1,
      v8);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 54331) + 16))(
      v6 + 217324,
      *(&g_ArcSceneMonsterTable + nVal),
      pnVal,
      this);
    ((UIStatic *)(v6 + 217324))->CreateFromTemplate();
    (**((void ( ***)(int, _DWORD))v6 + 54331))((int)(v6 + 217324), 0);
    v9 = *((_DWORD *)v6 + 53274);
    v6 += 213096;
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(v9 + 16))(
      v6,
      *(&g_ArcSceneMonsterTable + nVal),
      pnVal,
      this);
    ((UIStatic *)v6)->CreateFromTemplate();
    return ((UIScene *)v6)->SetShow(0);
  }
  return result;
}

// 0x004889E0
void UITitle_XJTM::LayoutGetRects()
{
  char *v2; // edi
  int v3; // eax
  int v4; // ecx
  int *v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // esi
  unsigned int v17; // ecx
  LONG v18; // edi
  void *v19; // esi
  unsigned int v20; // edx
  void **v21; // eax
  UITitle_XJTM *v22; // eax
  LONG v23; // ecx
  UITitle_XJTM *v24; // edx
  int a2; // [esp+0x8] [ebp-0x50] BYREF
  int v26; // [esp+0xC] [ebp-0x4C]
  int v27; // [esp+0x10] [ebp-0x48]
  int v28; // [esp+0x14] [ebp-0x44]
  int v29; // [esp+0x18] [ebp-0x40]
  int v30; // [esp+0x1C] [ebp-0x3C]
  int v31; // [esp+0x20] [ebp-0x38]
  int v32; // [esp+0x24] [ebp-0x34]
  int v33; // [esp+0x28] [ebp-0x30]
  unsigned int v34; // [esp+0x2C] [ebp-0x2C]
  int v35; // [esp+0x30] [ebp-0x28]
  LONG v36; // [esp+0x34] [ebp-0x24]
  int v37; // [esp+0x38] [ebp-0x20]
  int v38; // [esp+0x3C] [ebp-0x1C]
  int v39; // [esp+0x40] [ebp-0x18]
  int v40; // [esp+0x44] [ebp-0x14]
  int v41; // [esp+0x48] [ebp-0x10]
  int v42; // [esp+0x4C] [ebp-0xC]
  int v43; // [esp+0x50] [ebp-0x8]
  int v44; // [esp+0x54] [ebp-0x4]
  int v45; // [esp+0x5C] [ebp+0x4]
  int *v46; // [esp+0x60] [ebp+0x8]

  if ( v45 <= 5 )
  {
    v2 = (char *)this + 4892 * v45;
    sub_445FA0(v2 + 212600);
    v3 = v46[1] + 10;
    v37 = *v46 + 25;
    v39 = v37 + 65;
    v38 = v3;
    v40 = v3 + 86;
    sub_445FA0(v2 + 212752);
    v4 = v38;
    v5 = (int *)((char *)this + 16 * v45 + 353760);
    *v5 = v37;
    v6 = v39;
    v5[1] = v4;
    v7 = v40;
    v5[2] = v6;
    v5[3] = v7;
    v8 = v46[1] + 36;
    v41 = v46[2] - 27;
    v42 = v8;
    v43 = v41 + 32;
    v44 = v8 + 128;
    sub_445FA0(v2 + 213096);
    v9 = *v46 - 72;
    v26 = v46[1] + 21;
    a2 = v9;
    v28 = v26 + 12;
    v27 = v9 + 85;
    sub_43FEC0(&a2);
    v10 = *v46 - 80;
    v26 = v28 + 16;
    a2 = v10;
    v28 += 28;
    v27 = v10 + 85;
    sub_43FEC0(&a2);
    v11 = *v46;
    v26 = v28 + 16;
    a2 = v11 - 70;
    v28 += 28;
    v27 = v11 - 70 + 85;
    sub_43FEC0(&a2);
    v12 = v46[1];
    v29 = a2;
    v30 = v12;
    v31 = a2 + 100;
    v32 = v12 + 32;
    sub_445FA0(v2 + 213644);
    v13 = v46[1] + 28;
    v29 = a2;
    v30 = v13;
    v32 = v13 + 32;
    v31 = a2 + 100;
    sub_445FA0(v2 + 214740);
    v14 = v46[1];
    v29 = a2;
    v31 = a2 + 100;
    v30 = v14 + 56;
    v32 = v14 + 88;
    sub_445FA0(v2 + 214192);
    v15 = v46[3];
    v16 = *v46 + 30;
    v34 = v15 + 6;
    v33 = v16;
    v35 = v16 + 25;
    v36 = v15 + 34;
    sub_445FA0(v2 + 217324);
    v17 = v34;
    v18 = v36;
    v19 = (void *)v35;
    *((_DWORD *)this + 4 * v45 + 52540) = v34 - 6;
    v20 = v33;
// [VFTABLE] v21 = &this->__vftable + 4 * v45;
    v21[52539] = (void *)v33;
    v21[52541] = v19;
    v21[52542] = (void *)(v18 - 6);
    v22 = (UITitle_XJTM *)((char *)this + 52 * v45 + 209896);
    v22->m_wndcolor.Color = v17;
    v22->m_fontcolor.Color = v20;
    v23 = v36;
    v22->m_id = v19;
    v22->m_rect.left = v23;
    v24 = (UITitle_XJTM *)((char *)this + 52 * v45 + 209916);
// [VFTABLE] v24->__vftable = (vtbl_0056AE2C *)*((_DWORD *)this + 13 * v45 + 52475);
    v24->m_fontcolor.Color = *((_DWORD *)this + 13 * v45 + 52476);
    v24->m_wndcolor.Color = (unsigned int)v19;
    v24->m_id = (void *)*((_DWORD *)this + 13 * v45 + 52478);
// [VFTABLE] v22->__vftable = (vtbl_0056AE2C *)36;
  }
}

// 0x00488C70
int UITitle_XJTM::SetMonsterState(int nIndex, unsigned int dwParam)
{
  int result; // eax
  char *v4; // edi
  int (***v5)(_DWORD, _DWORD); // edi
  int v6; // ebx

  result = nIndex;
  if ( nIndex <= 5 )
  {
    v4 = (char *)this + 4892 * nIndex;
    (**((void ( ***)(int, _DWORD))v4 + 53150))((int)(v4 + 212600), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53188))((int)(v4 + 212752), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53274))((int)(v4 + 213096), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53350))((int)(v4 + 213400), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53411))((int)(v4 + 213644), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53624))((int)(v4 + 214496), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53685))((int)(v4 + 214740), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53487))((int)(v4 + 213948), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53548))((int)(v4 + 214192), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53723))((int)(v4 + 214892), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53761))((int)(v4 + 215044), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53799))((int)(v4 + 215196), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53837))((int)(v4 + 215348), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53875))((int)(v4 + 215500), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53913))((int)(v4 + 215652), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53951))((int)(v4 + 215804), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 53989))((int)(v4 + 215956), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 54027))((int)(v4 + 216108), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 54065))((int)(v4 + 216260), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 54103))((int)(v4 + 216412), (unsigned __int8)dwParam);
    v5 = (int ( ***)(_DWORD, _DWORD))(v4 + 216564);
    v6 = 5;
    do
    {
      result = (**v5)(v5, (unsigned __int8)dwParam);
      v5 += 38;
      --v6;
    }
    while ( v6 );
  }
  return result;
}

// 0x0048F360
int UITitle_XJTM::UpdateNPCAnims2(int nVal, int nVal2)
{
  char *v3; // esi
  int result; // eax

  v3 = (char *)this + 4892 * nVal;
  ((NPC *)(v3 + 212752))->NPC::UpdateAnim();
  ((NPC *)(v3 + 215652))->NPC::UpdateAnim();
  return result;
}

// 0x00498C90
void UITitle_XJTM::DestroyStaticsEx()
{
  sub_4422E0(this);
  UIScene::GetSys();
  sub_4422E0(&this->m_OutFrameL.m_ratioh);
  sub_4422E0(&this->m_OutFrameB.m_align);
  ((UIButton *)&this->m_background.m_bfocus)->ctor_17();
  sub_4422E0(&this->m_title.m_nTextW);
  sub_4422E0(&this->m_exit.m_texarray.m_ptex[11]);
  ((UIButton *)&this->m_exit.m_caption[100])->ctor_17();
  sub_4422E0(&this->m_WordBk.m_ppicInfo);
  sub_4422E0(&this->m_BtnBk.m_pbkInfo);
  ((UIButton *)&this->m_BtnFirstRow[0].m_texarray.m_ptex[3])->ctor_17();
  sub_4422E0(&this->m_BtnFirstRow[1].m_wndcolor);
  sub_4422E0(&this->m_BtnFirstRow[1].m_texarray.m_num);
  sub_4422E0(&this->m_BtnFirstRow[1].m_caption[120]);
  sub_4422E0(&this->m_BtnFirstRow[2].m_texarray.m_ptex[6]);
  sub_4422E0(&this->m_BtnFirstRow[2].m_caption[80]);
  sub_4422E0(&this->m_BtnFirstRow[3].m_canctrl);
  sub_4422E0(&this->m_BtnFirstRow[3].m_caption[40]);
  sub_4422E0(&this->m_BtnSecondRow[0].m_childs.capacity);
  sub_4422E0(this->m_BtnSecondRow[0].m_caption);
  sub_4422E0(&this->m_BtnSecondRow[1]);
  sub_4422E0(&this->m_BtnSecondRow[1].m_texarray.m_ptex[14]);
  sub_4422E0(&this->m_BtnSecondRow[1].m_caption[112]);
  sub_4422E0(&this->m_BtnSecondRow[4].m_mouseoff);
}

// 0x00498E60
void UITitle_XJTM::DestroyFramesEx()
{
  ((UIFrameWnd *)&this->m_BtnSecondRow[4].m_mouseoff)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[1].m_caption[112])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[1].m_texarray.m_ptex[14])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[1])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)this->m_BtnSecondRow[0].m_caption)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnSecondRow[0].m_childs.capacity)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[3].m_caption[40])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[3].m_canctrl)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[2].m_caption[80])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[2].m_texarray.m_ptex[6])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[1].m_caption[120])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[1].m_texarray.m_num)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_BtnFirstRow[1].m_wndcolor)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_BtnFirstRow[0].m_texarray.m_ptex[3])->_UIButton();
  ((UIFrameWnd *)&this->m_BtnBk.m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_WordBk.m_ppicInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_exit.m_caption[100])->_UIButton();
  ((UIFrameWnd *)&this->m_exit.m_texarray.m_ptex[11])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_title.m_nTextW)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_background.m_bfocus)->_UIButton();
  ((UIFrameWnd *)&this->m_OutFrameB.m_align)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameL.m_ratioh)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_OutFrameT.m_bvisible)->Destroy2();
// [VFTABLE] ((UIFrameWnd *)&this->__vftable)->_UIFrameWnd();
}

// 0x004999D0
int UITitle_XJTM::UpdateMonsterEntry2(int nVal, int *pnVal)
{
  int v4; // ecx
  int v5; // edx
  char *v6; // esi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int result; // eax
  int v11; // [esp+0x18] [ebp-0x10] BYREF
  int v12; // [esp+0x1C] [ebp-0xC]
  int v13; // [esp+0x20] [ebp-0x8]
  int v14; // [esp+0x24] [ebp-0x4]

  if ( nVal <= 5 )
  {
    v4 = *pnVal;
    v12 = pnVal[1];
    v14 = v12 + 12;
    v5 = (int)*(&g_ArcSceneMonsterTable2 + nVal);
    v11 = v4;
    v6 = (char *)this + 4892 * nVal;
    v7 = *((_DWORD *)v6 + 39238);
    v13 = v4 + 85;
    (*(void ( **)(char *, int, int *, UITitle_XJTM *))(v7 + 16))(v6 + 156952, v5, &v11, this);
    ((UIScene *)(v6 + 156952))->GetChildCount();
    ((UIScene *)(v6 + 156952))->GetChildAt();
    *((_DWORD *)v6 + 39256) = 1;
    v6[157122] = -30;
    v6[157121] = -51;
    v6[157120] = 58;
    v6[157123] = -1;
    sub_43FD90((float *)v6 + 39238, 4);
    ((UIWnd *)(v6 + 156952))->GetWidth(-4);
    sub_43FDB0((float *)v6 + 39238, 1);
    ((UIWnd *)(v6 + 156952))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 39512) + 16))(
      v6 + 158048,
      *(&g_ArcSceneMonsterTable2 + nVal),
      &v11,
      this);
    ((UIScene *)(v6 + 158048))->GetChildCount();
    ((UIScene *)(v6 + 158048))->GetChildAt();
    *((_DWORD *)v6 + 39530) = 1;
    v6[158218] = -30;
    v6[158217] = -51;
    v6[158216] = 58;
    v6[158219] = -1;
    sub_43FD90((float *)v6 + 39512, 4);
    ((UIWnd *)(v6 + 158048))->GetWidth(-4);
    sub_43FDB0((float *)v6 + 39512, 1);
    ((UIWnd *)(v6 + 158048))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 39375) + 16))(
      v6 + 157500,
      *(&g_ArcSceneMonsterTable2 + nVal),
      &v11,
      this);
    ((UIScene *)(v6 + 157500))->GetChildCount();
    ((UIScene *)(v6 + 157500))->GetChildAt();
    *((_DWORD *)v6 + 39393) = 1;
    v6[157670] = -30;
    v6[157669] = -51;
    v6[157668] = 58;
    v6[157671] = -1;
    sub_43FD90((float *)v6 + 39375, 4);
    ((UIWnd *)(v6 + 157500))->GetWidth(-4);
    sub_43FDB0((float *)v6 + 39375, 1);
    ((UIWnd *)(v6 + 157500))->GetPosition(-3);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 39299) + 16))(
      v6 + 157196,
      *(&g_ArcSceneMonsterTable2 + nVal),
      pnVal,
      this);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 39573) + 16))(
      v6 + 158292,
      *(&g_ArcSceneMonsterTable2 + nVal),
      pnVal,
      this);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 39436) + 16))(
      v6 + 157744,
      *(&g_ArcSceneMonsterTable2 + nVal),
      pnVal,
      this);
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(*((_DWORD *)v6 + 39038) + 16))(
      v6 + 156152,
      *(&g_ArcSceneMonsterTable2 + nVal),
      pnVal,
      this);
    ((UIStatic *)(v6 + 156152))->CreateFromTemplate();
    LOBYTE(v8) = g_bDebugMode;
    (*(void ( **)(char *, int, int *, UITitle_XJTM *, char *, int, int))(*((_DWORD *)v6 + 39076) + 28))(
      v6 + 156304,
      dword_56E148[nVal],
      pnVal,
      this,
      &"UI\\GameMainUI\\Communal\\RoleHead0"[256 * nVal],
      1,
      v8);
    v9 = *((_DWORD *)v6 + 39162);
    v6 += 156648;
    (*(void ( **)(char *, _DWORD, int *, UITitle_XJTM *))(v9 + 16))(
      v6,
      *(&g_ArcSceneMonsterTable2 + nVal),
      pnVal,
      this);
    ((UIStatic *)v6)->CreateFromTemplate();
    return ((UIScene *)v6)->SetShow(0);
  }
  return result;
}

// 0x0049A6E0
int * UITitle_XJTM::Layout_49a6e0(int arg0, int *pnVal)
{
  char *v4; // edi
  int v5; // eax
  void **v6; // ebp
  void *v7; // edx
  void *v8; // ecx
  void *v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // esi
  int v17; // ecx
  int v18; // esi
  int v19; // eax
  int v20; // edx
  int *result; // eax
  int a2; // [esp+0xC] [ebp-0x50] BYREF
  int v24; // [esp+0x10] [ebp-0x4C]
  int v25; // [esp+0x14] [ebp-0x48]
  int v26; // [esp+0x18] [ebp-0x44]
  int v27; // [esp+0x1C] [ebp-0x40]
  int v28; // [esp+0x20] [ebp-0x3C]
  int v29; // [esp+0x24] [ebp-0x38]
  int v30; // [esp+0x28] [ebp-0x34]
  int v31; // [esp+0x2C] [ebp-0x30]
  int v32; // [esp+0x30] [ebp-0x2C]
  int v33; // [esp+0x34] [ebp-0x28]
  int v34; // [esp+0x38] [ebp-0x24]
  int v35; // [esp+0x3C] [ebp-0x20]
  int v36; // [esp+0x40] [ebp-0x1C]
  int v37; // [esp+0x44] [ebp-0x18]
  int v38; // [esp+0x48] [ebp-0x14]
  int v39; // [esp+0x4C] [ebp-0x10]
  int v40; // [esp+0x50] [ebp-0xC]
  int v41; // [esp+0x54] [ebp-0x8]
  int v42; // [esp+0x58] [ebp-0x4]

  if ( arg0 <= 5 )
  {
    v4 = (char *)this + 4892 * arg0;
    sub_445FA0(v4 + 156152);
    v5 = pnVal[1] + 10;
    v35 = *pnVal + 25;
    v37 = v35 + 65;
    v36 = v5;
    v38 = v5 + 86;
    sub_445FA0(v4 + 156304);
// [VFTABLE] v6 = &this->__vftable + 4 * arg0;
    v7 = (void *)v36;
    v6[66545] = (void *)v35;
    v8 = (void *)v37;
    v6[66546] = v7;
    v9 = (void *)v38;
    v6[66547] = v8;
    v6[66548] = v9;
    v10 = pnVal[2];
    v40 = pnVal[1] + 36;
    v39 = v10 - 27;
    v42 = v40 + 128;
    v41 = v10 - 27 + 32;
    sub_445FA0(v4 + 156648);
    v11 = pnVal[1] + 21;
    a2 = *pnVal - 72;
    v25 = a2 + 85;
    v24 = v11;
    v26 = v11 + 12;
    sub_43FEC0(&a2);
    a2 = *pnVal - 80;
    v24 = v26 + 16;
    v25 = a2 + 85;
    v26 += 28;
    sub_43FEC0(&a2);
    v12 = *pnVal;
    v24 = v26 + 16;
    a2 = v12 - 70;
    v26 += 28;
    v25 = v12 - 70 + 85;
    sub_43FEC0(&a2);
    v28 = pnVal[1];
    v27 = a2;
    v30 = v28 + 32;
    v29 = a2 + 100;
    sub_445FA0(v4 + 157196);
    v13 = pnVal[1];
    v27 = a2;
    v29 = a2 + 100;
    v28 = v13 + 28;
    v30 = v13 + 60;
    sub_445FA0(v4 + 158292);
    v14 = pnVal[1] + 56;
    v27 = a2;
    v28 = v14;
    v29 = a2 + 100;
    v30 = v14 + 32;
    sub_445FA0(v4 + 157744);
    v15 = pnVal[3];
    v16 = *pnVal + 30;
    v32 = v15 + 6;
    v34 = v15 + 34;
    v31 = v16;
    v33 = v16 + 25;
    sub_445FA0(v4 + 160876);
    v17 = v32;
    v18 = v33;
    v19 = v34;
    v6[48666] = (void *)(v32 - 6);
    v20 = v31;
    v6[48665] = (void *)v31;
    v6[48667] = (void *)v18;
    *((_DWORD *)this + 4 * arg0 + 48668) = v19 - 6;
    result = (int *)((char *)this + 52 * arg0 + 194400);
    result[2] = v17;
    result[1] = v20;
    result[3] = v18;
    result[4] = v34;
    result[5] = result[1];
    result[6] = result[2];
    result[7] = v18;
    result[8] = *((_DWORD *)this + 13 * arg0 + 48604);
    *result = 36;
  }
  return result;
}

// 0x0049A980
int UITitle_XJTM::SetMonsterState2(int nIndex, unsigned int dwParam)
{
  int result; // eax
  char *v4; // edi
  int (***v5)(_DWORD, _DWORD); // edi
  int v6; // ebx

  result = nIndex;
  if ( nIndex <= 5 )
  {
    v4 = (char *)this + 4892 * nIndex;
    (**((void ( ***)(int, _DWORD))v4 + 39038))((int)(v4 + 156152), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39076))((int)(v4 + 156304), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39162))((int)(v4 + 156648), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39238))((int)(v4 + 156952), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39299))((int)(v4 + 157196), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39512))((int)(v4 + 158048), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39573))((int)(v4 + 158292), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39375))((int)(v4 + 157500), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39436))((int)(v4 + 157744), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39611))((int)(v4 + 158444), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39649))((int)(v4 + 158596), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39687))((int)(v4 + 158748), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39725))((int)(v4 + 158900), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39763))((int)(v4 + 159052), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39801))((int)(v4 + 159204), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39839))((int)(v4 + 159356), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39877))((int)(v4 + 159508), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39915))((int)(v4 + 159660), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39953))((int)(v4 + 159812), (unsigned __int8)dwParam);
    (**((void ( ***)(int, _DWORD))v4 + 39991))((int)(v4 + 159964), (unsigned __int8)dwParam);
    v5 = (int ( ***)(_DWORD, _DWORD))(v4 + 160116);
    v6 = 5;
    do
    {
      result = (**v5)(v5, (unsigned __int8)dwParam);
      v5 += 38;
      --v6;
    }
    while ( v6 );
  }
  return result;
}

// 0x004A0330
int UITitle_XJTM::UpdateNPCAnims(int nVal, int nVal2)
{
  char *v3; // esi
  int result; // eax

  v3 = (char *)this + 4892 * nVal;
  ((NPC *)(v3 + 156304))->NPC::UpdateAnim();
  ((NPC *)(v3 + 159204))->NPC::UpdateAnim();
  return result;
}
