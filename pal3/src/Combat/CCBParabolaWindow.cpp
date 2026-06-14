#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBParabolaWindow.h"

// Forward declarations for unnamed functions
void * sub_445FE0(void *a2); // from annotations

// Unnamed globals (extern)
extern const char * off_570298;
extern TextureLibDataBase stru_1894B78;

// 0x00440BE0
gbVFileSystem * CCBParabolaWindow::LoadResourceEx(const char *pszName, char pData)
{
  int v4; // edi
  CCBParabolaWindow *v5; // esi
  int v6; // ebp
  CHAR *v7; // eax
  gbVFileSystem *result; // eax
  OpenBaseFile v9; // [esp+0x10] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x14] [ebp-0x110] BYREF
  int v11; // [esp+0x120] [ebp-0x4]

  v4 = 0;
  v11 = 0;
  v5 = this + 1;
  do
  {
// [VFTABLE] if ( v5->__vftable )
// [VFTABLE] ((gbRefObject *)v5->__vftable)->Release();
    sprintf(Buffer, "%s%d.tga", pszName, v4);
    if ( pData )
    {
      v6 = *(_DWORD *)gfxMgr;
      v7 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(Buffer);
// [VFTABLE] v5->__vftable = (vtbl_0056AE2C *)(*(int ( **)(gbGfxManager *, CHAR *))(v6 + 8))(gfxMgr, v7);
      v5->m_wndcolor.Color = (unsigned int)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(Buffer);
    }
    else
    {
// [VFTABLE] v5->__vftable = (vtbl_0056AE2C *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(
// [VFTABLE]   gfxMgr,
// [VFTABLE]   Buffer);
    }
// [VFTABLE] if ( v5->__vftable )
// [VFTABLE] ((gbTexture *)v5->__vftable)->LoadTexture(1);
    ++v4;
    v5 = (CCBParabolaWindow *)((char *)v5 + 4);
  }
  while ( v4 < 2 );
  v11 = -1;
  return result;
}

// 0x0051B710
CCBParabolaWindow::CCBParabolaWindow(
        
        CCBParabolaWindow **thisa,
        int *pnVal,
        int nVal)
{
  UIStatic **v5; // edi
  CCBLineupWindow *v6; // ecx
  CCBLineupWindow *v7; // ecx
  char v8; // al
  UIStatic **v9; // ebx
  int i; // edi
  char v11; // al
  int v12; // eax
  int v13; // ecx

  ((PalScript *)this)->Create(1879048197, (tagRECT *)thisa, (int)pnVal);
  *((_DWORD *)this + 30) = pnVal;
  v5 = (UIStatic **)((char *)this + 92);
  ((CCBLineupWindow *)v6)->Destroy();
  if ( v8 == 1 )
  {
    *thisa = 0;
    thisa[2] = (CCBParabolaWindow *)230;
    thisa[1] = 0;
    thisa[3] = (CCBParabolaWindow *)250;
// [VFTABLE] ((void (*)(UIStatic *, int, CCBParabolaWindow **, CCBParabolaWindow *))(*v5)->__vftable->Create)(
// [VFTABLE]   *v5,
// [VFTABLE]   240,
// [VFTABLE]   thisa,
// [VFTABLE]   this);
    ((UIStatic *)*v5)->CreateFromTemplate();
// [VFTABLE] ((void (*)(UIStatic *, int))(*v5)->__vftable->ShowWindow)(*v5, 1);
  }
  v9 = (UIStatic **)((char *)this + 96);
  for ( i = 0; i < 5; ++i )
  {
    ((CCBLineupWindow *)v7)->Destroy();
    if ( v11 )
    {
      v12 = g_nUnkTable_268[i + 1];
      v13 = g_nUnkTable_24C[i + 1];
      *thisa = (CCBParabolaWindow *)v13;
      thisa[1] = (CCBParabolaWindow *)v12;
      thisa[2] = (CCBParabolaWindow *)(v13 + 40);
      thisa[3] = (CCBParabolaWindow *)(v12 + 38);
// [VFTABLE] ((void (*)(UIStatic *, int, CCBParabolaWindow **, CCBParabolaWindow *))(*v9)->__vftable->Create)(
// [VFTABLE]   *v9,
// [VFTABLE]   g_nPropIDs_241[i],
// [VFTABLE]   thisa,
// [VFTABLE]   this);
      ((UIStatic *)*v9)->CreateFromTemplate();
      ((UIFrameWnd *)*v9)->SetTextureByName((&off_570298)[i], 0);
// [VFTABLE] ((void (*)(UIStatic *, int))(*v9)->__vftable->ShowWindow)(*v9, 1);
    }
    ++v9;
  }
}

// 0x0051B810
void CCBParabolaWindow::_CCBParabolaWindow()
{
  int v2; // ecx
  CCBParabolaWindow *v3; // esi
  int v4; // edi
  UIListBox *v5; // [esp+0x0] [ebp-0x8]
  int v6; // [esp+0x4] [ebp-0x4]

  ((CCBRoleState *)this)->Destroy(v5, v6);
  v2 = *((_DWORD *)this + 23);
  if ( v2 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v2 + 20))(v2, 1);
    *((_DWORD *)this + 23) = 0;
  }
  v3 = (CCBParabolaWindow *)((char *)this + 96);
  v4 = 5;
  do
  {
// [VFTABLE] if ( v3->__vftable )
    {
// [VFTABLE] (*((void ( **)(vtbl_0056AE2C *, int))v3->__vftable->ShowWindow + 5))(v3->__vftable, 1);
// [VFTABLE] v3->__vftable = 0;
    }
    v3 = (CCBParabolaWindow *)((char *)v3 + 4);
    --v4;
  }
  while ( v4 );
}

// 0x0051B920
void CCBParabolaWindow::Destroy()
{
  int v2; // ecx
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v3);
  v2 = *((_DWORD *)this + *((_DWORD *)this + 29) + 24);
  (*(void ( **)(int))(*(_DWORD *)v2 + 4))(v2);
}

// 0x0051B950
bool CCBParabolaWindow::OnMessage(int msg, int wparam, int lparam)
{
  int *v4; // eax
  _BYTE a2[16]; // [esp+0x8] [ebp-0x10] BYREF

  v4 = (int *)sub_445FE0(a2);
  return wparam >= *v4 && wparam < v4[2] && lparam >= v4[1] && lparam < v4[3];
}

// 0x0051B9A0
int CCBParabolaWindow::Update(int deltatime, int haveinput)
{
  int v4; // esi
  char *i; // edi

  v4 = 0;
  for ( i = (char *)this + 96;
        *(_DWORD *)(*(_DWORD *)i + 56) != 1 || !this->OnMessage(v4, deltatime, haveinput);
        i += 4 )
  {
    if ( ++v4 >= 5 )
      return -1;
  }
  return v4;
}
