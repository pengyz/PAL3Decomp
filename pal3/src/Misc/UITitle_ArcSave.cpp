#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_ArcSave.h"

// Forward declarations for unnamed functions
int PalScript_Cleanup(...);
void sub_4422E0(void *_this); // from annotations

// Unnamed globals (extern)
extern int dword_DBA240;
extern void * off_5BF000;

// 0x0047BBF0
int UITitle_ArcSave::ctor()
{
  int v3; // [esp+0x0] [ebp-0x14]

  sub_4422E0(&this->m_YesNo.m_bvisible);
  sub_4422E0((char *)&this->m_YesNo.76 + 132);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  this->m_YesNo.m_rect.left = 88;
  this->m_YesNo.m_rect.top = 138;
  this->m_YesNo.m_pfather = (UIWnd *)90;
  this->m_YesNo.m_childs.m_pData = (char *)26;
  this->m_YesNo.m_rect.right = 800;
  this->m_YesNo.m_rect.bottom = 64;
  this->m_YesNo.m_bcreateok = 0;
  *((_DWORD *)&this->m_YesNo + 979) = 0;
  *((_BYTE *)&this->m_YesNo + 3928) = 1;
  return (int)this;
}

// 0x0047BD20
void UITitle_ArcSave::ctor_BD20()
{

  PalScript_Cleanup((PalScript *)((char *)&this->m_YesNo + 1848));
  ((UICaption *)((char *)&this->m_YesNo + 1504))->Destroy2();
  ((UICaption *)(&this->m_YesNo.m_btRc + 33))->Destroy2();
  ((UICaption *)((char *)&this->m_YesNo.m_btRc + 184))->Destroy2();
  ((UIFrameWnd *)((char *)&this->m_YesNo.76 + 132))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_YesNo.m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x0047C370
void UITitle_ArcSave::Render()
{
  int m_bcreateok; // eax
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  ((PAL3 *)this)->Render_47c260();
  m_bcreateok = this->m_YesNo.m_bcreateok;
  if ( m_bcreateok )
  {
    if ( m_bcreateok == 1 )
      (*(void ( **)(int))(*(_DWORD *)this->m_YesNo.m_childs.m_needscriptdel + 4))(this->m_YesNo.m_childs.m_needscriptdel);
  }
  else
  {
    ((CCBControlWindow *)this)->Render(v3);
  }
}

// 0x0047C3A0
int UITitle_ArcSave::ProcessPageAction(PalScript *p, int nVal)
{
  int result; // eax

  switch ( this->m_YesNo.m_bcreateok )
  {
    case 0:
      ((PalScriptMgr *)this)->RunSceneScript((const char *)p);
      ((UIListBox *)this)->Update((int)p, nVal);
      result = 1;
      break;
    case 1:
      (*(void ( **)(int, PalScript *, int))(*(_DWORD *)this->m_YesNo.m_childs.m_needscriptdel
                                                                      + 8))(
        this->m_YesNo.m_childs.m_needscriptdel,
        p,
        nVal);
      result = 1;
      break;
    case 2:
      ((CGameData *)&g_gamefrm)->Load(0);
      result = 1;
      break;
    case 3:
      ((CGameData *)&g_gamefrm)->Load((CUtil *)4);
      goto LABEL_6;
    default:
LABEL_6:
      result = 1;
      break;
  }
  return result;
}

// 0x0047C430
int UITitle_ArcSave::OnMessage(int nVal, int nVal2, int nVal3)
{
  CScreenMode *v6; // eax
  CScreenMode *v7; // eax
  CScreenMode *Instance; // eax
  PalScriptMgr *v9; // ecx
  const void *v10; // [esp-0x8] [ebp-0xC]
  const void *v11; // [esp-0x8] [ebp-0xC]
  const void *v12; // [esp-0x8] [ebp-0xC]

  if ( nVal == 1000 )
  {
    if ( nVal2 )
      g_nSceneState = 1;
  }
  else
  {
    if ( nVal != 1001 )
      return ((PalScript *)this)->OnMessage(nVal, nVal2, nVal3);
    switch ( nVal2 )
    {
      case 1027:
        if ( dword_DBA240 )
        {
          v12 = off_5BF000;
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v12, 1);
          ((PAL3 *)this)->DispatchModeCommand(2);
          ((PalScriptMgr *)v9)->Destroy();
          return 1;
        }
        break;
      case 1028:
        ((PAL3 *)this)->DispatchModeCommand(1);
        v11 = off_5BF000;
        v7 = CScreenMode::GetInstance();
        ((CScreenMode *)v7)->AudioSetPosition(v11, 1);
        return 1;
      case 1029:
        ((PAL3 *)this)->DispatchModeCommand(2);
        v10 = off_5BF000;
        v6 = CScreenMode::GetInstance();
        ((CScreenMode *)v6)->AudioSetPosition(v10, 1);
        return 1;
    }
  }
  return 1;
}
