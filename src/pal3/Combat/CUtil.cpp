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
UIWnd * CUtil::WriteLog(CUtil *Block, char a2)
{
  Block->GetFileSize();
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return (UIWnd *)Block;
}

// 0x005231F0
void CUtil::GetFileSize()
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  this->m_bCanWarp = (__int32)&off_5705F4;
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
  (UIItem *->UIItem()&this->m_INIBuffer[84]);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x005232B0
int CUtil::GetFileSize()
{
  int v2; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  char *Instance; // eax
  gbAudioManager *AudioManager; // eax
  gbAudioManager *v17; // esi
  char *v18; // eax
  char *v20; // [esp-8h] [ebp-38h]
  int a3[4]; // [esp+14h] [ebp-1Ch] BYREF
  int v22; // [esp+2Ch] [ebp-4h]

  v2 = *(_DWORD *)&this->m_INIFileName[68];
  v3 = *(_DWORD *)&this->m_INIFileName[72];
  *(_DWORD *)&this->m_INIFileName[60] = v2;
  *(_DWORD *)&this->m_INIFileName[64] = v3;
  *(_DWORD *)&this->m_INIFileName[56] = 0;
  *(_DWORD *)&this->m_INIFileName[52] = 0;
  (UIListBox *->SetSelTexture()this,
    -1,
    0,
    0,
    *(_DWORD *)&this->m_INIFileName[60],
    *(_DWORD *)&this->m_INIFileName[64],
    0);
  a3[1] = 200;
  a3[0] = 250;
  a3[2] = 550;
  a3[3] = 300;
  (UIItem *->Create()&this->m_INIBuffer[84], (int)&unk_ABCD00, (int)a3);
  (UIItem *->SetData()&this->m_INIBuffer[84], 18);
  v4 = *(_DWORD *)&this->m_INIBuffer[164];
  v5 = *(_DWORD *)&this->m_INIBuffer[172];
  *(_DWORD *)&this->m_INIBuffer[184] = *(_DWORD *)&this->m_INIBuffer[168] + 12;
  *(_DWORD *)&this->m_INIBuffer[180] = v4 + 6;
  *(_DWORD *)&this->m_INIBuffer[192] = *(_DWORD *)&this->m_INIBuffer[176] - 38;
  *((_DWORD *)this + 428) = 0;
  *((_DWORD *)this + 429) = 6;
  *(_DWORD *)&this->m_INIBuffer[188] = v5 - 6;
  (UIWnd *->GetRect()((char *)this + 824), &this->m_INIBuffer[180]);
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
    v9 = v8->Create();
  else
    v9 = 0;
  v22 = -1;
  *((_DWORD *)this + 435) = v9;
  v10 = operator new(0x1E56Cu);
  v22 = 2;
  if ( v10 )
    v11 = v10->ctor_A60();
  else
    v11 = 0;
  v22 = -1;
  *((_DWORD *)this + 436) = v11;
  v12 = operator new(0x70DCu);
  v22 = 3;
  if ( v12 )
    v13 = v12->ctor_D140();
  else
    v13 = 0;
  v14 = *((_DWORD *)this + 434);
  v22 = -1;
  *((_DWORD *)this + 437) = v13;
  sub_524230(v14, (int)this);
  sub_51DFD0(*((_DWORD *)this + 435), (int)this);
  sub_472A80(*((_DWORD **)this + 436), 1);
  sub_471590(*((_DWORD *)this + 436), (int)this);
  sub_46EC30(*((_DWORD **)this + 437), 1);
  sub_46DF40(*((_DWORD *)this + 437), (int)this);
  sub_524960(*((_DWORD **)this + 434), *((_DWORD *)this + 435));
  CCBResultWindow::~CCBResultWindow(*((CCBResultWindow **)this + 435), *((_DWORD *)this + 437));
  CCBResultWindow::CCBResultWindow(*((CCBResultWindow **)this + 435), *((_DWORD *)this + 436));
  CCBProtectWindow::Update(*((CCBProtectWindow **)this + 435), *((_DWORD *)this + 434));
  this->RectIntersection();
  if ( (g_nGameFlags & 4) != 0 )
  {
    Instance = (char *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(CScreenMode *->GetAudioManager()Instance);
    v17 = AudioManager;
    if ( AudioManager )
    {
      AudioManager->DetachAll3D();
      v17->StopSoundStream(0);
      v17->StopSoundStream(2);
      v20 = (char *)off_5E2C34[0];
      v18 = (char *)CScreenMode::GetInstance();
      sub_53EA80((int)v18, 1, v20, 0);
    }
  }
  return UICursor::IRender();
}

// 0x00523560
char CUtil::RectIntersection()
{
  RenderTarget *Instance; // eax
  int v3; // ecx
  int v4; // eax
  RenderTarget *v5; // eax
  _DWORD *v6; // eax
  char v7; // bl
  int *v8; // eax
  _DWORD *v9; // eax

  Instance = (RenderTarget *)CRenderTarget::GetInstance();
  Instance->OnDeviceLost(1);
  v3 = *CRenderTarget::GetInstance();
  v4 = 1061158912;
  if ( v3 )
    v4 = 1065353216;
  *((_DWORD *)this + 441) = v4;
  *((_DWORD *)this + 440) = v4;
  v5 = (RenderTarget *)CRenderTarget::GetInstance();
  LOBYTE(v6) = v5->OnResetDevice(1);
  if ( (_BYTE)v6 )
  {
    v7 = g_bRenderUI;
    g_bRenderUI = 0;
    PAL3::Render();
    g_bRenderUI = v7;
    v8 = (int *)CRenderTarget::GetInstance();
    sub_4BDD90(v8);
    *((_DWORD *)this + 439) = 0;
    v9 = (_DWORD *)CRenderTarget::GetInstance();
    v6 = (_DWORD *)sub_4BDEB0(v9);
    if ( v6 && v6[21] )
      *((_DWORD *)this + 439) = v6;
  }
  else
  {
    *((_DWORD *)this + 439) = 0;
  }
  return (char)v6;
}
