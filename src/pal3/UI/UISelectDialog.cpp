#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UISelectDialog.h"

// Forward declarations for unnamed functions
int sub_43F640(...);
int sub_43F690(...);

// Unnamed globals (extern)
extern char aSeldlg[];
extern char aUiFlexNote_0[];
extern char aUiSceneSelpicT[];

// 0x00451980
int UISelectDialog::Create(int id, void *pRect, int parent, char *tex)
{
  int v6; // eax
  int v7; // edx
  _DWORD v9[2]; // [esp+18h] [ebp-10h] BYREF
  int v10; // [esp+20h] [ebp-8h]
  int v11; // [esp+24h] [ebp-4h]

  (UIWnd *->Create()this, id, pRect, parent);
  (UINote *->Create()((char *)this + 1296), 0, (int)pRect, (int)this, aUiFlexNote_0);
  (_DWORD *->GetRect()this + 324, pRect);
  v6 = *((_DWORD *)pRect + 3);
  v10 = *((_DWORD *)pRect + 2) - *(_DWORD *)pRect - 16;
  v7 = *((_DWORD *)this + 22);
  v11 = v6 - *((_DWORD *)pRect + 1) - 16;
  v9[0] = 8;
  v9[1] = 0;
  (*(void (**)(char *, _DWORD, _DWORD *, UISelectDialog *, _DWORD, _DWORD, _DWORD))(v7 + 28))(
    (char *)this + 88,
    0,
    v9,
    this,
    0,
    0,
    0);
  (char *->SetFirstShow()this + 88, aSeldlg, v10 - v9[0]);
  sub_43F690((_DWORD *)this + 22, 1);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&parent + 1) = -6;
    LOBYTE(parent) = -6;
  }
  else
  {
    *(_WORD *)((char *)&parent + 1) = -1286;
    LOBYTE(parent) = -1;
  }
  HIBYTE(parent) = -1;
  (_DWORD *->GetChild()this + 22, &parent);
  (_DWORD *->GetSel()this + 22, (int)aUiSceneSelpicT, 0);
  (**(void (***)(UISelectDialog *, _DWORD))this)(this, 0);
  *((_DWORD *)this + 300) = 20;
  return sub_43F640((_DWORD *)this + 22, 20);
}
