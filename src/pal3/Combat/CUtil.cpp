#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CUtil.h"

// Forward declarations for unnamed functions
int sub_46DF40(...);
int sub_46EC30(...);
int sub_471590(...);
int sub_472A80(...);
int sub_4BDD90(...);
int sub_4BDEB0(...);
int sub_51DFD0(...);
int sub_524230(...);
int sub_524960(...);
int sub_53EA80(...);

// Unnamed globals (extern)
extern int dword_17ADB04;
extern float flt_17ADB00;
extern void *off_5705F4;
extern void *off_5E2C34;
extern int unk_ABCD00;

// 0x005230F0
// attributes: thunk
int CUtil::~CUtil()
{
  return CUtil::Create();
}

// 0x00523100
int CUtil::Create()
{
  dword_17ADB04 = 1094713344;
  return 1094713344;
}

// 0x00523110
// attributes: thunk
void CUtil::Destroy()
{
  CUtil::Init();
}

// 0x00523120
void CUtil::Init()
{
  flt_17ADB00 = 12.0 + 12.0;
}

// 0x00523130
int CUtil::CreateLog(int _this)
{
  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 360) = 0;
  *(_DWORD *)(this + 364) = 0;
  UIItem::Refresh(this + 368);
  *(_DWORD *)(this + 1736) = 0;
  *(_DWORD *)(this + 1740) = 0;
  *(_DWORD *)(this + 1744) = 0;
  *(_DWORD *)(this + 1748) = 0;
  *(_DWORD *)(this + 1752) = 0;
  *(_DWORD *)this = &off_5705F4;
  *(_DWORD *)(this + 352) = 0;
  *(_BYTE *)(this + 356) = 0;
  *(_DWORD *)(this + 1756) = 0;
  *(_BYTE *)(this + 1768) = 1;
  return this;
}

// 0x005231D0
UIWnd * CUtil::WriteLog(UIWnd *Block, char a2)
{
  Block->GetFileSize();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x005231F0
void CUtil::GetFileSize()
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  *(_DWORD *)this = &off_5705F4;
  v2 = *((_DWORD *)this + 434);
  if ( v2 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v2 + 20))(v2, 1);
    *((_DWORD *)this + 434) = 0;
  }
  v3 = *((_DWORD *)this + 435);
  if ( v3 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *((_DWORD *)this + 435) = 0;
  }
  v4 = *((_DWORD *)this + 436);
  if ( v4 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v4 + 20))(v4, 1);
    *((_DWORD *)this + 436) = 0;
  }
  v5 = *((_DWORD *)this + 437);
  if ( v5 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *((_DWORD *)this + 437) = 0;
  }
  UIItem::UIItem((int)this + 368);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x005232B0
int CUtil::GetFileSize()
{
  int v2; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  void *v6; // eax
  int v7; // eax
  void *v8; // eax
  int v9; // eax
  void *v10; // eax
  int v11; // eax
  void *v12; // eax
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  gbAudioManager *v16; // eax
  gbAudioManager *v17; // esi
  int v18; // ecx
  char *v20; // [esp-8h] [ebp-38h]
  int v21[4]; // [esp+14h] [ebp-1Ch] BYREF
  int v22; // [esp+2Ch] [ebp-4h]

  v2 = *((_DWORD *)this + 22);
  v3 = *((_DWORD *)this + 23);
  *((_DWORD *)this + 20) = v2;
  *((_DWORD *)this + 21) = v3;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  this->SetSelTexture(-1, 0, 0, *((_DWORD *)this + 20), *((_DWORD *)this + 21), 0);
  v21[1] = 200;
  v21[0] = 250;
  v21[2] = 550;
  v21[3] = 300;
  UIItem::Create((int)(this + 92), (int)&unk_ABCD00, v21, (int)this, 0, 1);
  UIItem::SetData(this + 92, 18, 255, 28, 200);
  v4 = *((_DWORD *)this + 112);
  v5 = *((_DWORD *)this + 114);
  *((_DWORD *)this + 117) = *((_DWORD *)this + 113) + 12;
  *((_DWORD *)this + 116) = v4 + 6;
  *((_DWORD *)this + 119) = *((_DWORD *)this + 115) - 38;
  *((_DWORD *)this + 428) = 0;
  *((_DWORD *)this + 429) = 6;
  *((_DWORD *)this + 118) = v5 - 6;
  UIWnd::GetRect(this + 206, this + 116);
  v6 = operator new(0x1578u);
  v22 = 0;
  if ( v6 )
    v7 = v6->ctor_3F30();
  else
    v7 = 0;
  v22 = -1;
  *((_DWORD *)this + 434) = v7;
  v8 = operator new(0xA4128u);
  v22 = 1;
  if ( v8 )
    v9 = CCBProtectWindow::Create((int)v8);
  else
    v9 = 0;
  v22 = -1;
  *((_DWORD *)this + 435) = v9;
  v10 = operator new(0x1E56Cu);
  v22 = 2;
  if ( v10 )
    v11 = UIWnd::ctor_A60((int)v10);
  else
    v11 = 0;
  v22 = -1;
  *((_DWORD *)this + 436) = v11;
  v12 = operator new(0x70DCu);
  v22 = 3;
  if ( v12 )
    v13 = UIWnd::ctor_D140((int)v12);
  else
    v13 = 0;
  v22 = -1;
  *((_DWORD *)this + 437) = v13;
  sub_524230(this);
  sub_51DFD0(*((_DWORD *)this + 435), (int)this);
  sub_472A80((_DWORD *)*((_DWORD *)this + 436), 1);
  sub_471590(*((_DWORD *)this + 436), (int)this);
  sub_46EC30((_DWORD *)*((_DWORD *)this + 437), 1);
  sub_46DF40(*((_DWORD *)this + 437), (int)this);
  sub_524960(*((_DWORD *)this + 435));
  CCBResultWindow::~CCBResultWindow((_DWORD *)*((_DWORD *)this + 435), *((_DWORD *)this + 437));
  (_DWORD *->CCBResultWindow()*((_DWORD *)this + 435), *((_DWORD *)this + 436));
  (_DWORD *->Update()*((_DWORD *)this + 435), *((_DWORD *)this + 434));
  this->RectIntersection();
  if ( (g_nGameFlags & 4) != 0 )
  {
    v15 = v14->GetInstance();
    v16 = (gbAudioManager *)v15->GetAudioManager();
    v17 = v16;
    if ( v16 )
    {
      v16->DetachAll3D();
      v17->StopSoundStream(0);
      v17->StopSoundStream(2);
      v20 = off_5E2C34[0];
      v18->GetInstance();
      sub_53EA80(1, v20, 0);
    }
  }
  return UICursor::IRender();
}

// 0x00523560
char CUtil::RectIntersection()
{
  _DWORD *v2; // eax
  int v3; // ecx
  int v4; // eax
  int *v5; // eax
  _DWORD *v6; // eax
  char v7; // bl
  int *v8; // eax
  _DWORD *v9; // eax

  v2 = CRenderTarget::GetInstance();
  v2->OnDeviceLost(1);
  v3 = *CRenderTarget::GetInstance();
  v4 = 1061158912;
  if ( v3 )
    v4 = 1065353216;
  *((_DWORD *)this + 441) = v4;
  *((_DWORD *)this + 440) = v4;
  v5 = CRenderTarget::GetInstance();
  LOBYTE(v6) = v5->OnResetDevice(1);
  if ( (_BYTE)v6 )
  {
    v7 = g_bRenderUI;
    g_bRenderUI = 0;
    PAL3::Render();
    g_bRenderUI = v7;
    v8 = CRenderTarget::GetInstance();
    sub_4BDD90(v8);
    *((_DWORD *)this + 439) = 0;
    v9 = CRenderTarget::GetInstance();
    v6 = sub_4BDEB0(v9);
    if ( v6 && v6[21] )
      *((_DWORD *)this + 439) = v6;
  }
  else
  {
    *((_DWORD *)this + 439) = 0;
  }
  return (char)v6;
}
