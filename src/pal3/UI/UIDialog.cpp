#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIDialog.h"

// 0x004503D0
void UIDialog::Create(int id, int x, int y, int parent, char *tex)
{
  gbTexture *v7; // eax
  _DWORD pRect[4]; // [esp+4h] [ebp-10h] BYREF

  pRect[2] = x;
  this->m_childs.m_nGrowBy = x;
  this->m_bcreateok = y;
  pRect[3] = y;
  pRect[1] = 0;
  pRect[0] = 0;
  this->Create(id, pRect, parent);
  v7 = (gbTexture *)(*(int (__thiscall **)(gbGfxManager *, char *))(*(_DWORD *)g_pGfxManager + 8))(
                      g_pGfxManager,
                      tex);
  this->m_bvisible = (int)v7;
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

  pRect[0] = (MEMORY[0xBFD6D0] - 274) / 2;
  pRect[1] = 10;
  pRect[3] = 87;
  pRect[2] = pRect[0] + 274;
  (UIWnd *->Create()this, 0, pRect, parent);
  (UINote *->Create()(this + 18), 1, (int)pRect, (int)this, aUiFlexNote_0);
  (_DWORD *->GetRect()this + 18, pRect);
  sub_445910((_DWORD *)this + 18, 2);
  return (*(int (__thiscall **)(UIDialog *, _DWORD))this->UIWnd)(this, 0);
}
