#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBSkillWindow.h"

// Forward declarations for unnamed functions
int sub_43FD90(float *_this, int a2); // from annotations
void sub_43FDB0(float *_this, int a2); // from annotations
int sub_43FEC0(void *a2); // from annotations
int sub_4431B0(...);
void * sub_445FE0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

// Unnamed globals (extern)
extern int dword_570324;
extern const char * off_570310;

// 0x0051BBE0
void CCBSkillWindow::Destroy()
{
  char v2; // [esp+0x8] [ebp+0x4]

  if ( (v2 & 1) != 0 )
    operator delete(this);
}

// 0x0051BC00
void CCBSkillWindow::_CCBSkillWindow()
{
  ((CCBMagicWindow *)this)->ClearMagicData();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0051C2D0
void CCBSkillWindow::Reset()
{
  *((_DWORD *)this + 42) = 0;
  *((_DWORD *)this + 43) = -1;
  this->m_pBack = 0;
  this->m_pDescription = 0;
  this->m_pSkillList[0] = 0;
  *((_DWORD *)this + 21) = 0;
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 23) = 0;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 26) = 0;
  memset((char *)this + 108, 0, 0x2Cu);
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 41) = 0;
}

// 0x0051C330
bool CCBSkillWindow::Create(int *pRect, int parent)
{
  UIStatic **p_m_pBack; // ebx
  CCBLineupWindow *v5; // ecx
  CCBLineupWindow *v6; // ecx
  const char **v7; // ebp
  UIStatic **v8; // ebx
  CCBSkillWindow *v9; // ebx
  CCBLineupWindow *v10; // ecx
  void *v11; // eax
  CCBSkillWindow *v12; // ebx
  CCBLineupWindow *v13; // ecx
  void *v14; // eax
  CCBSkillWindow *v15; // ebx
  CCBLineupWindow *v16; // ecx
  void *v17; // eax
  CCBSkillWindow *v18; // ebx
  CCBLineupWindow *v19; // ecx
  UIStatic **p_m_pDescription; // ebx
  CCBLineupWindow *v21; // ecx
  UIListBox **m_pSkillList; // ebx
  CCBLineupWindow *v23; // ecx
  CCBSkillWindow *v24; // ebx
  CCBLineupWindow *v25; // ecx
  CCBSkillWindow *v26; // ebx
  CCBLineupWindow *v27; // ecx
  CCBSkillWindow *v28; // ebx
  CCBLineupWindow *v29; // ecx
  CCBSkillWindow *v30; // ebx
  CCBLineupWindow *v31; // ecx
  CCBSkillWindow *v32; // ebx
  CCBLineupWindow *v33; // ecx
  CCBSkillWindow *v34; // ebx
  CCBLineupWindow *v35; // ecx
  _BYTE a2[16]; // [esp+C8h] [ebp-0x10] BYREF

  ((PalScript *)this)->Create(512, (tagRECT *)pRect, parent);
  *((_DWORD *)this + 42) = parent;
  p_m_pBack = &this->m_pBack;
  ((CCBLineupWindow *)v5)->Destroy();
  *pRect = 0;
  pRect[2] = 256;
  pRect[1] = 0;
  pRect[3] = 256;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBSkillWindow *))(*p_m_pBack)->__vftable->Create)(
// [VFTABLE]   *p_m_pBack,
// [VFTABLE]   513,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
  ((UIStatic *)this->m_pBack)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))(*p_m_pBack)->__vftable->ShowWindow)(*p_m_pBack, 1);
  v7 = &off_570310;
  v8 = (UIStatic **)((char *)this + 108);
  do
  {
    ((CCBLineupWindow *)v6)->Destroy();
    *pRect = 15;
    pRect[2] = 79;
    pRect[1] = -15;
    pRect[3] = 113;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBSkillWindow *))(*v8)->__vftable->Create)(*v8, 528, pRect, this);
    ((UIStatic *)*v8)->CreateFromTemplate();
    ++v7;
    ++v8;
  }
  while ( (int)v7 < (int)dword_570324 );
  (***((void ( ****)(_DWORD, int))this + 27))(*((_DWORD *)this + 27), 1);
  v9 = (CCBSkillWindow *)((char *)this + 156);
  ((CCBLineupWindow *)v10)->Render((int *)this + 39);
  *pRect = 83;
  pRect[2] = 168;
  pRect[1] = 46;
  pRect[3] = 58;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v9->__vftable->ShowWindow + 4))(
// [VFTABLE]   v9->__vftable,
// [VFTABLE]   545,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
  v11 = sub_445FE0(a2);
  sub_43FEC0(v11);
  ((UIScene *)*((UIScene **)this + 39))->GetChildCount();
  ((UIScene *)*((UIScene **)this + 39))->GetChildAt();
  sub_43FD90(*((float **)this + 39), 3);
  sub_43FDB0(*((float **)this + 39), -2);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v9->__vftable->ShowWindow)(v9->__vftable, 1);
  v12 = (CCBSkillWindow *)((char *)this + 160);
  ((CCBLineupWindow *)v13)->Render((int *)this + 40);
  *pRect = 86;
  pRect[2] = 171;
  pRect[1] = 71;
  pRect[3] = 83;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v12->__vftable->ShowWindow + 4))(
// [VFTABLE]   v12->__vftable,
// [VFTABLE]   546,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
  v14 = sub_445FE0(a2);
  sub_43FEC0(v14);
  ((UIScene *)*((UIScene **)this + 40))->GetChildCount();
  ((UIScene *)*((UIScene **)this + 40))->GetChildAt();
  sub_43FD90(*((float **)this + 40), 3);
  sub_43FDB0(*((float **)this + 40), -2);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v12->__vftable->ShowWindow)(v12->__vftable, 1);
  v15 = (CCBSkillWindow *)((char *)this + 164);
  ((CCBLineupWindow *)v16)->Render((int *)this + 41);
  *pRect = 84;
  pRect[2] = 169;
  pRect[1] = 97;
  pRect[3] = 109;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v15->__vftable->ShowWindow + 4))(
// [VFTABLE]   v15->__vftable,
// [VFTABLE]   547,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
  v17 = sub_445FE0(a2);
  sub_43FEC0(v17);
  ((UIScene *)*((UIScene **)this + 41))->GetChildCount();
  ((UIScene *)*((UIScene **)this + 41))->GetChildAt();
  sub_43FD90(*((float **)this + 41), 3);
  sub_43FDB0(*((float **)this + 41), -2);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v15->__vftable->ShowWindow)(v15->__vftable, 1);
  v18 = (CCBSkillWindow *)((char *)this + 152);
  ((CCBLineupWindow *)v19)->Destroy();
  *pRect = 66;
  pRect[2] = 130;
  pRect[1] = 42;
  pRect[3] = 109;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v18->__vftable->ShowWindow + 4))(
// [VFTABLE]   v18->__vftable,
// [VFTABLE]   544,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
  ((UIStatic *)*((UIStatic **)this + 38))->CreateFromTemplate();
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v18->__vftable->ShowWindow)(v18->__vftable, 1);
  p_m_pDescription = &this->m_pDescription;
  ((CCBLineupWindow *)v21)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 134;
  pRect[3] = 166;
// [VFTABLE] ((void ( *)(UIStatic *, int, int *, CCBSkillWindow *))(*p_m_pDescription)->__vftable->Create)(
// [VFTABLE]   *p_m_pDescription,
// [VFTABLE]   514,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] ((void ( *)(UIStatic *, int))(*p_m_pDescription)->__vftable->ShowWindow)(*p_m_pDescription, 1);
  ((UIScene *)this->m_pDescription)->SetShow(0);
  sub_446010(this->m_pDescription);
  m_pSkillList = this->m_pSkillList;
  ((CCBLineupWindow *)v23)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 134;
  pRect[3] = 166;
// [VFTABLE] ((void ( *)(UIListBox *, int, int *, CCBSkillWindow *))(*m_pSkillList)->__vftable->Create)(
// [VFTABLE]   *m_pSkillList,
// [VFTABLE]   515,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] ((void ( *)(UIListBox *, int))(*m_pSkillList)->__vftable->ShowWindow)(*m_pSkillList, 1);
  ((UIScene *)this->m_pSkillList[0])->SetShow(0);
  sub_446010(this->m_pSkillList[0]);
  v24 = this + 1;
  ((CCBLineupWindow *)v25)->Destroy();
  *pRect = 51;
  pRect[2] = 115;
  pRect[1] = 108;
  pRect[3] = 140;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v24->__vftable->ShowWindow + 4))(
// [VFTABLE]   v24->__vftable,
// [VFTABLE]   516,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v24->__vftable->ShowWindow)(v24->__vftable, 1);
  ((UIScene *)*((UIScene **)this + 21))->SetShow(0);
  sub_446010(*((void **)this + 21));
  v26 = (CCBSkillWindow *)((char *)this + 88);
  ((CCBLineupWindow *)v27)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 108;
  pRect[3] = 140;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v26->__vftable->ShowWindow + 4))(
// [VFTABLE]   v26->__vftable,
// [VFTABLE]   517,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v26->__vftable->ShowWindow)(v26->__vftable, 1);
  ((UIScene *)*((UIScene **)this + 22))->SetShow(0);
  sub_446010(*((void **)this + 22));
  v28 = (CCBSkillWindow *)((char *)this + 92);
  ((CCBLineupWindow *)v29)->Destroy();
  pRect[2] = 115;
  *pRect = 51;
  pRect[1] = 160;
  pRect[3] = 192;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v28->__vftable->ShowWindow + 4))(
// [VFTABLE]   v28->__vftable,
// [VFTABLE]   518,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v28->__vftable->ShowWindow)(v28->__vftable, 1);
  ((UIScene *)*((UIScene **)this + 23))->SetShow(0);
  sub_446010(*((void **)this + 23));
  v30 = (CCBSkillWindow *)((char *)this + 96);
  ((CCBLineupWindow *)v31)->Destroy();
  *pRect = 136;
  pRect[2] = 200;
  pRect[1] = 160;
  pRect[3] = 192;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v30->__vftable->ShowWindow + 4))(
// [VFTABLE]   v30->__vftable,
// [VFTABLE]   519,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v30->__vftable->ShowWindow)(v30->__vftable, 1);
  ((UIScene *)*((UIScene **)this + 24))->SetShow(0);
  sub_446010(*((void **)this + 24));
  v32 = (CCBSkillWindow *)((char *)this + 100);
  ((CCBLineupWindow *)v33)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 211;
  pRect[3] = 243;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v32->__vftable->ShowWindow + 4))(
// [VFTABLE]   v32->__vftable,
// [VFTABLE]   529,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v32->__vftable->ShowWindow)(v32->__vftable, 1);
  ((UIScene *)*((UIScene **)this + 25))->SetShow(0);
  sub_446010(*((void **)this + 25));
  v34 = (CCBSkillWindow *)((char *)this + 104);
  ((CCBLineupWindow *)v35)->Destroy();
  *pRect = 0;
  pRect[2] = 187;
  pRect[1] = 0;
  pRect[3] = 32;
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int, int *, CCBSkillWindow *))v34->__vftable->ShowWindow + 4))(
// [VFTABLE]   v34->__vftable,
// [VFTABLE]   530,
// [VFTABLE]   pRect,
// [VFTABLE]   this);
// [VFTABLE] (*(void ( **)(vtbl_0056AE2C *, int))v34->__vftable->ShowWindow)(v34->__vftable, 1);
  ((UIScene *)*((UIScene **)this + 26))->SetShow(0);
  sub_446010(*((void **)this + 26));
  return 1;
}

// 0x0051C880
int CCBSkillWindow::Destroy_c880()
{
  int result; // eax
  CCBSkillWindow *v3; // edi
  int v4; // ebx
  UIStatic *m_pBack; // ecx
  UIStatic *m_pDescription; // ecx
  UIListBox *v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  UIListBox *v18; // [esp+0x0] [ebp-0x10]
  int v19; // [esp+0x4] [ebp-0xC]

  ((CCBRoleState *)this)->Destroy(v18, v19);
  v3 = (CCBSkillWindow *)((char *)this + 108);
  v4 = 11;
  do
  {
// [VFTABLE] if ( v3->__vftable )
    {
// [VFTABLE] result = (*((int ( **)(vtbl_0056AE2C *, int))v3->__vftable->ShowWindow + 5))(v3->__vftable, 1);
// [VFTABLE] v3->__vftable = 0;
    }
    v3 = (CCBSkillWindow *)((char *)v3 + 4);
    --v4;
  }
  while ( v4 );
  m_pBack = this->m_pBack;
  if ( m_pBack )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))m_pBack->__vftable->sub_4431B0)(m_pBack, 1);
    this->m_pBack = 0;
  }
  m_pDescription = this->m_pDescription;
  if ( m_pDescription )
  {
// [VFTABLE] result = ((int ( *)(UIStatic *, int))m_pDescription->__vftable->sub_4431B0)(m_pDescription, 1);
    this->m_pDescription = 0;
  }
  v7 = this->m_pSkillList[0];
  if ( v7 )
  {
// [VFTABLE] result = ((int ( *)(UIListBox *, int))v7->__vftable->sub_4431B0)(v7, 1);
    this->m_pSkillList[0] = 0;
  }
  v8 = *((_DWORD *)this + 21);
  if ( v8 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
    *((_DWORD *)this + 21) = 0;
  }
  v9 = *((_DWORD *)this + 22);
  if ( v9 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v9 + 20))(v9, 1);
    *((_DWORD *)this + 22) = 0;
  }
  v10 = *((_DWORD *)this + 23);
  if ( v10 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v10 + 20))(v10, 1);
    *((_DWORD *)this + 23) = 0;
  }
  v11 = *((_DWORD *)this + 24);
  if ( v11 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
    *((_DWORD *)this + 24) = 0;
  }
  v12 = *((_DWORD *)this + 25);
  if ( v12 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
    *((_DWORD *)this + 25) = 0;
  }
  v13 = *((_DWORD *)this + 26);
  if ( v13 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
    *((_DWORD *)this + 26) = 0;
  }
  v14 = *((_DWORD *)this + 38);
  if ( v14 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v14 + 20))(v14, 1);
    *((_DWORD *)this + 38) = 0;
  }
  v15 = *((_DWORD *)this + 39);
  if ( v15 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v15 + 20))(v15, 1);
    *((_DWORD *)this + 39) = 0;
  }
  v16 = *((_DWORD *)this + 40);
  if ( v16 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v16 + 20))(v16, 1);
    *((_DWORD *)this + 40) = 0;
  }
  v17 = *((_DWORD *)this + 41);
  if ( v17 )
  {
    result = (*(int ( **)(int, int))(*(_DWORD *)v17 + 20))(v17, 1);
    *((_DWORD *)this + 41) = 0;
  }
  return result;
}

// 0x0051C9F0
BOOL CCBSkillWindow::Update(int deltatime, int haveinput)
{
  if ( this->m_bvisible == 1 && g_Input.KeyInfo[16].PressTime == 1 && (g_Input.KeyInfo[16].Data & 0xF) == 1 )
    ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))->SetParam(513, -1);
  return ((UIListBox *)this)->Update(deltatime, haveinput);
}

// 0x0051CA50
CCBAIWindow * CCBSkillWindow::ToggleSlots(int nVal)
{
  int v3; // edi
  char *v4; // esi
  void ( ***v5)(_DWORD, int); // ecx

  if ( nVal == 1 )
  {
    *((_BYTE *)this + 176) = 0;
    v3 = 0;
    v4 = (char *)this + 108;
    do
    {
      v5 = *(void ( ****)(_DWORD, int))v4;
      if ( *((_DWORD *)this + 43) == v3 )
        (**v5)(v5, 1);
      else
        (**v5)(v5, 0);
      ++v3;
      v4 += 4;
    }
    while ( v3 < 5 );
  }
  return (CCBAIWindow *)((PalScript *)this)->ShowWindow(nVal);
}

// 0x0051CAA0
void CCBSkillWindow::Render()
{
  LONG left; // ebx
  CCBStage *v3; // edi
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0x18]
  LONG top; // [esp+0xC] [ebp-0xC]

  ((CCBControlWindow *)this)->Render(v4);
  left = this->m_rect.left;
  top = this->m_rect.top;
  v3 = *(CCBStage **)(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 42) + 1160) + 20) + 68);
  ((CCBStage *)v3)->AddTextLabel(left + 105, top + 51);
  ((CCBStage *)v3)->AddTextLabel(left + 117, top + 76);
  ((CCBStage *)v3)->AddTextLabel(left + 107, top + 102);
}
