#include "pal3/gen/UIBigDialog.h"

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
  int v18; // [esp+3Ch] [ebp-10h] BYREF
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
  (UIWnd *->Create()this, id, v16, v17);
  (UINote *->Create()((char *)this + 80), 0, (int)v5, 0, aUiFlexDlg);
  *((_DWORD *)this + 37) = 1048576000;
  v21 = MEMORY[0xBFD6D4] - 8;
  v19 = MEMORY[0xBFD6D4] - 520;
  v7 = *((_DWORD *)this + 109);
  v18 = 8;
  v20 = 264;
  (*(void (__thiscall **)(char *, int, int *, UIBigDialog *))(v7 + 16))((char *)this + 436, 2, &v18, this);
  v8 = *((_DWORD *)this + 6);
  v9 = *((_DWORD *)this + 4);
  v10 = *((_DWORD *)this + 148);
  v19 = 8;
  v11 = v8 - v9;
  v18 = 256;
  v20 = 600;
  v21 = 144;
  (*(void (__thiscall **)(char *, int, int *, UIBigDialog *))(v10 + 16))((char *)this + 592, 1, &v18, this);
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
  (_DWORD *->GetChild()this + 148, &pRect);
  (*(void (__thiscall **)(char *, int, int *, UIBigDialog *))(*((_DWORD *)this + 68) + 16))(
    (char *)this + 272,
    2,
    &v18,
    this);
  (UIBigDialog *->LoadResource()((char *)this + 272), aUiScenePage);
  (_DWORD *->SetController()this + 68, 0x40000000);
  sub_4517A0(&v18, 1);
  (_DWORD *->GetRect()this + 68, &v18);
  v12 = (v11 - 134) / 2;
  v18 = v12;
  v20 = v12 + 134;
  v13 = *((_DWORD *)this + 174);
  v21 = 600;
  v19 = 580;
  (*(void (__thiscall **)(char *, _DWORD, int *, UIBigDialog *))(v13 + 16))((char *)this + 696, 0, &v18, this);
  (_DWORD *->GetRect()this + 174, &v18);
  (gbRefObject **->CreateFromTemplate()this + 174, aUiSceneTimeclo, 0);
  v14 = *((_DWORD *)this + 212);
  v18 = v12;
  v20 = v12 + 134;
  v21 = 600;
  v19 = 568;
  (*(void (__thiscall **)(char *, _DWORD, int *, UIBigDialog *))(v14 + 16))((char *)this + 848, 0, &v18, this);
  sub_43FEC0((_DWORD *)this + 212, &v18);
  (gbRefObject **->GetChildCount()this + 212, aUiSceneTimebkT, 0);
  (gbRefObject **->GetChildAt()this + 212, aUiSceneTimepTg, 0);
  UIWnd::FindChild((int)this + 848, 4.0);
  UIWnd::FindChildByName((int)this + 848, 0.0);
  *((_DWORD *)this + 240) = 1120403456;
  sub_43FDB0((float *)this + 212, 4);
  sub_43FDD0((float *)this + 212, 9);
  sub_43FDC0((float *)this + 212, 4);
  sub_43FDE0((float *)this + 212, 9);
  return (**((int (__thiscall ***)(char *, _DWORD))this + 212))((char *)this + 848, 0);
}
