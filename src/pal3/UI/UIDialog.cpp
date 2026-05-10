#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIDialog.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_445910(...);

// Unnamed globals (extern)
extern char aUiFlexNote_0[];

// 0x004503D0
void UIDialog::Create(int id, int x, int y, int parent, char *tex)
{
  gbTexture *v7; // eax
  _DWORD pRect[4]; // [esp+4h] [ebp-10h] BYREF

  pRect[2] = x;
  *((_DWORD *)this + 21) = x;
  *((_DWORD *)this + 22) = y;
  pRect[3] = y;
  pRect[1] = 0;
  pRect[0] = 0;
  ((UIWnd *)&this->_base)->Create(id, pRect, parent);
  v7 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxMgr->_pad_0000 + 8))(
                      g_pGfxMgr,
                      tex);
  *((_DWORD *)this + 23) = v7;
  if ( v7 )
    v7->LoadTexture(1);
}

// 0x00450550
void UIDialog::Show()
{
  int v1; // [esp+4h] [ebp+4h]

  *((_DWORD *)this + 20) = v1;
}

// 0x00450B30
int UIDialog::Init()
{
  _DWORD pRect[4]; // [esp+8h] [ebp-10h] BYREF
  int parent; // [esp+1Ch] [ebp+4h]

  pRect[0] = ((int)g_pGameTime - 274) / 2;
  pRect[1] = 10;
  pRect[3] = 87;
  pRect[2] = pRect[0] + 274;
  ((UIWnd *)&this->_base)->Create(0, pRect, parent);
  ((UINote *)(this + 1))->Create(1, (int)pRect, (int)this, aUiFlexNote_0);
  ((UIWnd *)(this + 1))->GetRect(pRect);
  sub_445910((_DWORD *)this + 18, 2);
  return (**(int (***)(UIDialog *, _DWORD))this->_base._pad_000)(this, 0);
}
