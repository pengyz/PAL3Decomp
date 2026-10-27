#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIEmote.h"
#include "Combat/CCBResultWindow.h"
#include "Role/Role.h"
#include "Misc/RoleAtt.h"
#include "Role/RoleSystem.h"
#include "Misc/UIAnimateCtrl.h"
#include "Misc/UICaption.h"
#include "UI/UIListBox.h"
#include "UI/UINote.h"
#include "Misc/UIPushButton.h"
#include "UI/UIQuadManager.h"
#include "UI/UIRenderObj.h"
#include "UI/UIScene.h"
#include "Misc/UITitle_QCYM.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x0044AB00
int UIEmote::_todo_0044AB00()
{
  // [overlay-fix 2026-10-27] C2440: *(this-3) 得 UIEmote& 无法转 int（Hex-Rays 垃圾形）——待语义修复
  // return *(this - 3);
  return 0;
}

// 0x0044E530
UIEmote::UIEmote()
{
  ClearSubArraySlot();
  this->m_needscriptdel = ((gbImage2D *)0);
  this->m_role = ((Role *)0);
  this->m_cur = 0;
  this->m_loopcount = 2;
}

// 0x0044EB40
void UIEmote::_todo_44EB40()
{
  ;
}

// 0x00529870
void UIEmote::Render()
{
  unsigned int m_id; // edx
  UIPushButton *v3; // edi
  float *v4; // ebx
  int capacity; // ebp
  __int64 v6; // rax
  int v7; // ecx
  __int64 v8; // rax
  int v9; // edx
  UIAnimateCtrl *v10; // edi
  LONG top; // eax
  char *m_pData; // edx
  int m_bvisible; // eax
  int v14; // edx
  int v15; // edx
  UIQuadManager *Instance; // eax
  int *v17; // [esp+0x30] [ebp-0x38]
  int nVal[4]; // [esp+0x38] [ebp-0x30] BYREF
  _DWORD v19[4]; // [esp+0x48] [ebp-0x20] BYREF
  _DWORD v20[4]; // [esp+0x58] [ebp-0x10] BYREF

  m_id = this->m_ani[0].m_id;
  *(_DWORD *)((UIWnd *)&this->m_ani[0]) = this->m_ani[0].m_wndcolor.Color;
  this->m_cur = 0;
  this->m_needscriptdel = ((gbImage2D *)0);
  this->m_ani[0].m_fontcolor.Color = m_id;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, (int)this->m_needscriptdel, this->m_cur, *(_DWORD *)((UIWnd *)&this->m_ani[0]), this->m_ani[0].m_fontcolor.Color) /* [ROWTABLE] */;
  v17 = (int *)&off_570748;
  v3 = (UIPushButton *)&this->m_ani[2].m_texarray.m_ptex[7];
  v4 = (float *)&this->m_ani[9].m_texarray.m_ptex[2];
  do
  {
    capacity = this->m_ani[7].m_childs.capacity;
    this->m_cur = (__int64)(v4[1] - (double)(capacity / 2));
    v6 = (__int64)(*v4 - (double)((int)this->m_ani[7].m_childs.m_pData / 2));
    HIDWORD(v6) = (unsigned long)(this->m_ani[7].m_childs.m_pData);
    this->m_needscriptdel = ((gbImage2D *)((gbImage2D *)v6));
    LODWORD(v6) = HIDWORD(v6) + v6;
    HIDWORD(v6) = this->m_cur;
    *(_DWORD *)((UIWnd *)&this->m_ani[0]) = v6;
    this->m_ani[0].m_fontcolor.Color = HIDWORD(v6) + capacity;
    (*(void ( **)(UIPushButton *, int, gbImage2D **, UIEmote *))(*(_DWORD *)((UIWnd *)v3) + 16))(
      v3,
      *v17,
      &this->m_needscriptdel,
      this);
    LOBYTE(v7) = this->m_ani[12].m_looppassed;
    (((UIPushButton *)v3))->UIPushButton::CreateFromTemplate("SubGame\\KillFlyer\\Flyer_gold.tga", v7);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v3))((UIPushButton *)(v3), (_DWORD)(0));
    v4 += 2;
    v3 = (UIPushButton *)((char *)v3 + 184);
    ++v17;
  }
  while ( (int)v17 < (int)&off_570754 );
  if ( (int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] > 0 )
  {
    v8 = (__int64)((double)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] * 0.0099999998);
    this->m_ani[7].m_rect.top = v8;
    if ( (int)v8 <= 0 )
      this->m_ani[7].m_rect.top = 1;
  }
  else
  {
    this->m_ani[7].m_rect.top = 0;
  }
  v9 = (int)((UIWnd *)&this->m_ani[6]);
  v10 = (UIAnimateCtrl *)&this->m_ani[6];
  v20[1] = 158;
  v20[0] = 300;
  v20[2] = 468;
  v20[3] = 190;
  (*(void ( **)(UIAnimateCtrl *, int *, _DWORD *, UIEmote *))(v9 + 16))(
    &this->m_ani[6],
    &byte_80AB21,
    (_DWORD *)(v20),
    this);
  (((UIScene *)&this->m_ani[6]))->UIScene::SetShow(0);
  sprintf((char *const)&this->m_ani[0].m_rect, "%s%d%", &dword_DD263C, this->m_ani[7].m_rect.top);
  (((UICaption *)&this->m_ani[6]))->UICaption::SetEnable();
  AllocObject(&this->m_ani[6]);
  this->m_ani[7].m_fontcolor.Color = 1087583027;
  (((CCBResultWindow *)&this->m_ani[6]))->CCBResultWindow::StartAnim();
  top = this->m_ani[7].m_rect.top;
  LOBYTE(this->m_ani[7].m_rect.left) = 0;
  if ( top > 0 )
    (**(void ( ***)(UIAnimateCtrl *, int))((UIWnd *)v10))((UIAnimateCtrl *)(&this->m_ani[6]), (int)(1));
  else
    (**(void ( ***)(UIAnimateCtrl *, _DWORD))((UIWnd *)v10))((UIAnimateCtrl *)(&this->m_ani[6]), (_DWORD)(0));
  nVal[1] = 158;
  nVal[0] = 300;
  nVal[2] = 432;
  nVal[3] = 290;
  (((UINote *)&this->m_ani[11].m_texarray.m_ptex[8]))->UINote::Create((int)&byte_80AB20, (int)nVal, (int)this, "UI\\Flex\\Note");
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_ani[11].m_texarray.m_ptex[8]))(
    &this->m_ani[11].m_texarray.m_ptex[8],
    0);
  ((void ( *)(gbTexture **, int *, int *, UIEmote *))this->m_ani[10].m_texarray.m_ptex[11]->IsLoaded)(
    &this->m_ani[10].m_texarray.m_ptex[11],
    &byte_80AB20,
    nVal,
    this);
  (((UIScene *)&this->m_ani[10].m_texarray.m_ptex[11]))->UIScene::SetShow(0);
  AllocObject(&this->m_ani[10].m_texarray.m_ptex[11]);
  ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_ani[10].m_texarray.m_ptex[11]))(
    &this->m_ani[10].m_texarray.m_ptex[11],
    0);
  m_pData = this->m_ani[9].m_childs.m_pData;
  m_bvisible = this->m_ani[7].m_bvisible;
  v19[2] = (unsigned long)(this->m_ani[9].m_pfather);
  v19[1] = 0;
  v19[0] = 0;
  v19[3] = (unsigned long)m_pData;
  (*(void ( **)(int *, int *, _DWORD *, UIEmote *))(m_bvisible + 16))(
    &this->m_ani[7].m_bvisible,
    &byte_80AB19,
    (_DWORD *)(v19),
    this);
  LOBYTE(v14) = this->m_ani[12].m_looppassed;
  (((UIPushButton *)&this->m_ani[7].m_bvisible))->UIPushButton::CreateFromTemplate("SubGame\\KillFlyer\\Kill.tga", v14);
  (*(void ( **)(int *, _DWORD))this->m_ani[7].m_bvisible)(&this->m_ani[7].m_bvisible, 0);
  (*(void ( **)(int *, int *, _DWORD *, UIEmote *))(this->m_ani[8].m_childs.m_nSize + 16))(
    &this->m_ani[8].m_childs.m_nSize,
    &byte_80AB19,
    (_DWORD *)(v19),
    this);
  LOBYTE(v15) = this->m_ani[12].m_looppassed;
  (((UIPushButton *)&this->m_ani[8].m_childs.m_nSize))->UIPushButton::CreateFromTemplate("SubGame\\KillFlyer\\Kill_pa.tga", v15);
  (*(void ( **)(int *, _DWORD))this->m_ani[8].m_childs.m_nSize)(
    &this->m_ani[8].m_childs.m_nSize,
    0);
  LOBYTE(this->m_ani[12].m_texarray.m_ptex[15]) = 1;
  Instance = (UIQuadManager *)UIQuadManager::GetInstance();
  (((UIRenderObj *)Instance))->UIRenderObj::_sdtor_call_dtor(0);
  (((UITitle_QCYM *)this))->UITitle_QCYM::HandleDeviceLostC();
}
