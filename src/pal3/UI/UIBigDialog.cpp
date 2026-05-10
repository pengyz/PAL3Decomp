#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIBigDialog.h"
#include "pal3/gen/MvcViewport.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_4517A0(...);

// Unnamed globals (extern)
extern char aUiFlexDlg[];
extern char aUiScenePage[];
extern char aUiSceneTimebkT[];
extern char aUiSceneTimeclo[];
extern char aUiSceneTimepTg[];
extern int dword_BFD6D4;

// 0x00450F90
int UIBigDialog::Create(int id, void *pRect, int parent, char *tex)
{
  _DWORD *v5; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // edx
  int v10; // eax
  int v11; // ebx
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  void *v16; // [esp+28h] [ebp-24h]
  int v17; // [esp+2Ch] [ebp-20h]
  int a2; // [esp+3Ch] [ebp-10h] BYREF
  int v19; // [esp+40h] [ebp-Ch]
  int v20; // [esp+44h] [ebp-8h]
  int v21; // [esp+48h] [ebp-4h]

  v5 = pRect;
  v17 = parent;
  v16 = pRect;
  *(_DWORD *)pRect = 0;
  *((_DWORD *)this + 5) = 458;
  v5[2] = 800;
  v5[3] = 594;
  ((UIWnd *)this)->Create(id, v16, v17);
  ((UINote *)((char *)this + 80))->Create(0, (int)v5, 0, aUiFlexDlg);
  *((_DWORD *)this + 37) = 1048576000;
  v21 = dword_BFD6D4 - 8;
  v19 = dword_BFD6D4 - 520;
  v7 = *((_DWORD *)this + 109);
  a2 = 8;
  v20 = 264;
  (*(void (**)(char *, int, int *, UIBigDialog *))(v7 + 16))((char *)this + 436, 2, &a2, this);
  v8 = *((_DWORD *)this + 6);
  v9 = *((_DWORD *)this + 4);
  v10 = *((_DWORD *)this + 148);
  v19 = 8;
  v11 = v8 - v9;
  a2 = 256;
  v20 = 600;
  v21 = 144;
  (*(void (**)(char *, int, int *, UIBigDialog *))(v10 + 16))((char *)this + 592, 1, &a2, this);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&pRect + 1) = -1286;
    LOBYTE(pRect) = -1;
  }
  else
  {
    *(_WORD *)((char *)&pRect + 1) = -6;
    LOBYTE(pRect) = -6;
  }
  HIBYTE(pRect) = -1;
  ((UIWnd *)((char *)this + 592))->GetChild((int)&pRect);
  (*(void (**)(char *, int, int *, UIBigDialog *))(*((_DWORD *)this + 68) + 16))(
    (char *)this + 272,
    2,
    &a2,
    this);
  ((UIScene *)((char *)this + 272))->LoadResource(aUiScenePage);
  ((MvcViewport *)(_DWORD *)this + 68)->SetController(0x40000000);
  sub_4517A0(&a2, 1);
  ((UIWnd *)((char *)this + 272))->GetRect(&a2);
  v12 = (v11 - 134) / 2;
  a2 = v12;
  v20 = v12 + 134;
  v13 = *((_DWORD *)this + 174);
  v21 = 600;
  v19 = 580;
  (*(void (**)(char *, _DWORD, int *, UIBigDialog *))(v13 + 16))((char *)this + 696, 0, &a2, this);
  ((UIWnd *)((char *)this + 696))->GetRect(&a2);
  ((UIWnd *)(UIWnd **)this + 174)->CreateFromTemplate(aUiSceneTimeclo, 0);
  v14 = *((_DWORD *)this + 212);
  a2 = v12;
  v20 = v12 + 134;
  v21 = 600;
  v19 = 568;
  (*(void (**)(char *, _DWORD, int *, UIBigDialog *))(v14 + 16))((char *)this + 848, 0, &a2, this);
  ((UIWnd *)((char *)this + 848))->AddChild(&a2);
  ((UIWnd *)(UIWnd **)this + 212)->GetChildCount(aUiSceneTimebkT, 0);
  ((UIWnd *)(UIWnd **)this + 212)->GetChildAt(aUiSceneTimepTg, 0);
  ((UIWnd *)((char *)this + 848))->FindChild(4.0);
  ((UIWnd *)((char *)this + 848))->FindChildByName(0.0);
  *((_DWORD *)this + 240) = 1120403456;
  ((UIWnd *)((char *)this + 848))->SetFrameRate(4);
  ((UIWnd *)((char *)this + 848))->GetHeight(9);
  ((UIWnd *)((char *)this + 848))->GetWidth(4);
  ((UIWnd *)((char *)this + 848))->GetPosition(9);
  return (**((int (***)(char *, _DWORD))this + 212))((char *)this + 848, 0);
}
