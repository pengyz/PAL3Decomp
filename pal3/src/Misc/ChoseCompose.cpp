#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ChoseCompose.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations

// 0x0044C970
void ChoseCompose::Init(int nVal)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  switch ( nVal )
  {
    case 0:
      if ( this )
        this->OnMessage(1000, 1, 0);
      v3 = *((_DWORD *)this + 3464);
      if ( v3 )
        (*(void ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v3 + 24))(1000, 0, 0);
      goto LABEL_6;
    case 1:
      if ( this )
        this->OnMessage(1000, 0, 0);
      v5 = *((_DWORD *)this + 3464);
      if ( v5 )
        (*(void ( **)(int, int, _DWORD))(*(_DWORD *)v5 + 24))(1000, 1, 0);
LABEL_6:
      v4 = *((_DWORD *)this + 3465);
      if ( v4 )
        (*(void ( **)(int, _DWORD, _DWORD))(*(_DWORD *)v4 + 24))(1000, 0, 0);
      goto LABEL_18;
    case 3:
      if ( this )
        this->OnMessage(1000, 0, 0);
      v6 = *((_DWORD *)this + 3464);
      if ( v6 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v6 + 24))(v6, 1000, 0, 0);
      v7 = *((_DWORD *)this + 3465);
      if ( v7 )
        (*(void ( **)(int, int, _DWORD))(*(_DWORD *)v7 + 24))(1000, 1, 0);
LABEL_18:
      v8 = *((_DWORD *)this + 3466);
      if ( v8 )
        goto LABEL_35;
      goto LABEL_36;
    case 4:
      if ( this )
        this->OnMessage(1000, 0, 0);
      v9 = *((_DWORD *)this + 3464);
      if ( v9 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v9 + 24))(v9, 1000, 0, 0);
      v10 = *((_DWORD *)this + 3465);
      if ( v10 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v10 + 24))(v10, 1000, 0, 0);
      v11 = *((_DWORD *)this + 3466);
      if ( !v11 )
        goto LABEL_36;
      (*(void ( **)(int, int, int, _DWORD))(*(_DWORD *)v11 + 24))(v11, 1000, 1, 0);
      *((_DWORD *)this + 3467) = nVal;
      break;
    case 5:
      if ( this )
        this->OnMessage(1000, 0, 0);
      v12 = *((_DWORD *)this + 3464);
      if ( v12 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v12 + 24))(v12, 1000, 0, 0);
      v13 = *((_DWORD *)this + 3465);
      if ( v13 )
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v13 + 24))(v13, 1000, 0, 0);
      v8 = *((_DWORD *)this + 3466);
      if ( v8 )
LABEL_35:
        (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)v8 + 24))(v8, 1000, 0, 0);
LABEL_36:
      *((_DWORD *)this + 3467) = nVal;
      break;
    default:
      return;
  }
}

// 0x004549A0
void ChoseCompose::DestroyScene()
{
  UIScene::GetSys();
  sub_4422E0(&this->buf[248]);
  sub_4422E0(&this->m_bk.m_texs.m_ptex[9]);
  sub_4422E0(&this->m_RoleName[4].m_ratiow);
  sub_4422E0(&this->m_RoleName[4].m_caption[32]);
  sub_4422E0(&this->m_RoleName[7].m_texarray.m_ptex[2]);
  sub_4422E0(&this->m_RoleName[7].m_caption[64]);
}

// 0x00454AA0
void ChoseCompose::_ChoseCompose()
{
  ((UIFrameWnd *)&this->m_RoleName[7].m_caption[64])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[7].m_texarray.m_ptex[2])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[4].m_caption[32])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[4].m_ratiow)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_bk.m_texs.m_ptex[9])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->buf[248])->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_rect)->Destroy2();
}

// 0x00455570
int ChoseCompose::LayoutItems(int arg0, int nVal, int nVal2, int nVal3, int nVal4)
{
  void **v6; // esi
  int v7; // ebx
  _DWORD *v8; // edi
  int v10; // [esp+0x24] [ebp-0x48]

// [VFTABLE] v6 = &this->__vftable + 890 * arg0;
  sub_445FA0(v6 + 227);
  v6[223] = (void *)nVal;
  v6[224] = (void *)nVal2;
  v6[225] = (void *)nVal3;
  v6[226] = (void *)nVal4;
  sub_445FA0(v6 + 313);
  sub_445FA0(v6 + 351);
  v10 = nVal + 154;
  v7 = 0;
  v8 = v6 + 389;
  do
  {
    if ( *((_BYTE *)v6 + v7 + 3076) )
    {
      sub_445FA0(v8 + 190);
      sub_445FA0(v8);
      sub_445FA0(v8 + 458);
      v10 += 58;
    }
    ++v7;
    v8 += 38;
  }
  while ( v7 < 5 );
  sub_445FA0(v6 + 771);
  sub_445FA0(v6 + 809);
  sub_445FA0(v6 + 1075);
  return sub_445FA0(v6 + 1037);
}

// 0x004A2170
void ChoseCompose::Method_4A2170()
{
  sub_4422E0(this);
  sub_4422E0(&this->buf[40]);
  sub_4422E0(&this->buf[192]);
  sub_4422E0(&this->m_bk.m_bfocus);
  ((UIButton *)&this->m_ComposeInfo.m_rect.right)->ctor_17();
  sub_4422E0(&this->m_RoleName[0].m_texarray.m_ptex[3]);
  sub_4422E0(&this->m_RoleName[0].m_caption[68]);
  ((UIButton *)&this->m_RoleName[1].m_hasDBclk)->ctor_17();
  sub_4422E0(&this->m_RoleName[1].m_caption[120]);
  sub_4422E0(&this->m_RoleName[2].m_texarray.m_ptex[6]);
  ((UIButton *)&this->m_RoleName[2].m_caption[80])->ctor_17();
  sub_4422E0(&this->m_RoleName[3].m_texarrayInfo[2]);
  sub_4422E0(&this->m_RoleName[3].m_benable_snd + 4);
  sub_4422E0(&this->m_RoleName[4].m_texarray.m_ptex[9]);
  sub_4422E0(&this->m_RoleName[4].m_caption[92]);
  sub_4422E0(&this->m_RoleName[5].m_bBigFont);
  sub_4422E0(&this->m_RoleName[5].m_caption[52]);
  sub_4422E0(&this->m_RoleName[8].m_texarray.m_ptex[7]);
}

// 0x004A22E0
void ChoseCompose::DestroySubWindows()
{
  ((UIFrameWnd *)&this->m_RoleName[8].m_texarray.m_ptex[7])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[5].m_caption[52])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[5].m_bBigFont)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[4].m_caption[92])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[4].m_texarray.m_ptex[9])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->m_RoleName[3].m_benable_snd + 4))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[3].m_texarrayInfo[2])->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_RoleName[2].m_caption[80])->_UIButton();
  ((UIFrameWnd *)&this->m_RoleName[2].m_texarray.m_ptex[6])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[1].m_caption[120])->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_RoleName[1].m_hasDBclk)->_UIButton();
  ((UIFrameWnd *)&this->m_RoleName[0].m_caption[68])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_RoleName[0].m_texarray.m_ptex[3])->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_ComposeInfo.m_rect.right)->_UIButton();
  ((UIFrameWnd *)&this->m_bk.m_bfocus)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->buf[192])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->buf[40])->UIFrameWnd::_UIFrameWnd();
// [VFTABLE] ((UIFrameWnd *)&this->__vftable)->_UIFrameWnd();
}

// 0x004B19E0
int ChoseCompose::LayoutItem(int arg0, int nVal, int nVal2, int nVal3, int nVal4)
{
  void **v6; // esi
  int v7; // ebx
  _DWORD *v8; // edi
  int v10; // [esp+0x24] [ebp-0x48]

// [VFTABLE] v6 = &this->__vftable + 890 * arg0;
  sub_445FA0(v6 + 39094);
  v6[39090] = (void *)nVal;
  v6[39091] = (void *)nVal2;
  v6[39092] = (void *)nVal3;
  v6[39093] = (void *)nVal4;
  sub_445FA0(v6 + 39180);
  sub_445FA0(v6 + 39218);
  v10 = nVal + 154;
  v7 = 0;
  v8 = v6 + 39256;
  do
  {
    if ( *((_BYTE *)v6 + v7 + 158544) )
    {
      sub_445FA0(v8 + 190);
      sub_445FA0(v8);
      sub_445FA0(v8 + 458);
      v10 += 58;
    }
    ++v7;
    v8 += 38;
  }
  while ( v7 < 5 );
  sub_445FA0(v6 + 39638);
  sub_445FA0(v6 + 39676);
  sub_445FA0(v6 + 39942);
  return sub_445FA0(v6 + 39904);
}
