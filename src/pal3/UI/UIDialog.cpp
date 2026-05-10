#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIDialog.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_445910(...);

// Unnamed globals (extern)
extern char aUiFlexNote_0[];
extern int dword_BFD6D0;
extern int dword_BFDA60;

// 0x004503D0
void UIDialog::Create(int id, int x, int y, int parent, char *tex)
{
  gbTexture *v7; // eax
  _DWORD pRect[4]; // [esp+4h] [ebp-10h] BYREF

  pRect[2] = x;
  this->_d054 = x;
  this->_d058 = y;
  pRect[3] = y;
  pRect[1] = 0;
  pRect[0] = 0;
  ((UIWnd *)this)->Create(id, pRect, parent);
  v7 = (gbTexture *)(*(int (**)(gbGfxManager *, char *))(*(_DWORD *)dword_BFDA60->_pad_0000 + 8))(
                      dword_BFDA60,
                      tex);
  this->_d05C = (int)v7;
  if ( v7 )
    v7->LoadTexture(1);
}

// 0x00450550
void UIDialog::Show()
{
  int v1; // [esp+4h] [ebp+4h]

  this->_d050 = v1;
}

// 0x00450B30
int UIDialog::Init()
{
  _DWORD pRect[4]; // [esp+8h] [ebp-10h] BYREF
  int parent; // [esp+1Ch] [ebp+4h]

  pRect[0] = (dword_BFD6D0 - 274) / 2;
  pRect[1] = 10;
  pRect[3] = 87;
  pRect[2] = pRect[0] + 274;
  ((UIWnd *)this)->Create(0, pRect, parent);
  ((UINote *)&this->_pad_000[72])->Create(1, (int)pRect, (int)this, aUiFlexNote_0);
  ((UIWnd *)&this->_pad_000[72])->GetRect(pRect);
  sub_445910(&this->_pad_000[72], 2);
  return (**(int (***)(UIDialog *, _DWORD))this->_pad_000)(this, 0);
}
