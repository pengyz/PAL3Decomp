#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIDialog.h"

// Forward declarations for unnamed functions
int sub_445FA0(void *a2); // from annotations

// 0x004503D0
void UIDialog::Create(int id, int x, int y, int parent, char *tex)
{
  gbTexture *v7; // eax
  tagRECT pRect; // [esp+0x4] [ebp-0x10] BYREF

  pRect.right = x;
  *((_DWORD *)this + 21) = x;
  *((_DWORD *)this + 22) = y;
  pRect.bottom = y;
  pRect.top = 0;
  pRect.left = 0;
  ((PalScript *)this)->Create(id, &pRect, parent);
  v7 = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, tex);
  *((_DWORD *)this + 23) = v7;
  if ( v7 )
    ((gbTexture *)v7)->LoadTexture(1);
}

// 0x00450550
void UIDialog::Show()
{
  int v1; // [esp+0x4] [ebp+0x4]

  *((_DWORD *)this + 20) = v1;
}

// 0x00450B30
int UIDialog::Init()
{
  tagRECT pRect; // [esp+0x8] [ebp-0x10] BYREF
  int parent; // [esp+0x1C] [ebp+0x4]

  pRect.left = (g_DrvInfo.width - 274) / 2;
  pRect.top = 10;
  pRect.bottom = 87;
  pRect.right = pRect.left + 274;
  ((PalScript *)this)->Create(0, &pRect, parent);
  ((UINote *)(this + 1))->Create(1, (int)&pRect, (int)this, "ui\\flex\\note");
  sub_445FA0(this + 1);
  ((RoleCameraCtrl *)(this + 1))->SetTargetDistance(2);
  return this->ShowWindow(0);
}

// 0x0052AEF0
int * UIDialog::ResetState()
{
  *((_DWORD *)this + 67) = 0;
  *((_DWORD *)this + 68) = 0;
  *((_DWORD *)this + 69) = 0;
  *((_DWORD *)this + 66) = 0;
  *((_DWORD *)this + 64) = 0;
  return (int *)this;
}
