#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle.h"

// Forward declarations for unnamed functions
int PalScript_Cleanup(...);
void sub_4422E0(void *_this); // from annotations
int sub_445AA0(void); // from annotations

// Unnamed globals (extern)
extern char byte_AABEF7;
extern int dword_DD8D3C;
extern int dword_DD8E3C;
extern RoleSystem stru_C059A0;

// 0x0044AB90
UITitle::UITitle()
{
  int v2; // [esp+0x0] [ebp-0x18]

  sub_445AA0();
  *((_DWORD *)this + 27) = 360;
  *((_DWORD *)this + 28) = 136;
  sub_4422E0((char *)this + 124);
  sub_4422E0((char *)this + 276);
  UIScene::GetSys();
  UIScene::GetSys();
  UIScene::GetSys();
  ((ARC_PlayerAtt *)((char *)this + 1916))->Refresh();
  this->m_bTimerActive = 0;
  this->m_dwTimerTick = 0;
  this->m_dwEffectTick = 0;
  ((ARC_PlayerAtt *)(&this->m_bTimerProcessed + 3))->Refresh();
  ((ARC_PlayerAtt *)(&this->m_bTimerProcessed + 1371))->Refresh();
  ((ARC_PlayerAtt *)(&this->m_bTimerProcessed + 2739))->Refresh();
  *((_DWORD *)this + 29) = 90;
  *((_DWORD *)this + 30) = 24;
}

// 0x0044ACE0
void UITitle::_UITitle()
{
  PalScript_Cleanup((PalScript *)(&this->m_nTitleStage + 2));
  ((UIRoleDialog *)(&this->m_bTimerProcessed + 2739))->_UIRoleDialog();
  ((UIRoleDialog *)(&this->m_bTimerProcessed + 1371))->_UIRoleDialog();
  ((UIRoleDialog *)(&this->m_bTimerProcessed + 3))->_UIRoleDialog();
  ((UIRoleDialog *)((char *)this + 1916))->_UIRoleDialog();
  ((UICaption *)((char *)this + 1572))->Destroy2();
  ((UICaption *)((char *)this + 1228))->Destroy2();
  ((UICaption *)((char *)this + 884))->Destroy2();
  ((UIFrameWnd *)((char *)this + 276))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 124))->UIFrameWnd::_UIFrameWnd();
// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x0044B0F0
int UITitle::RunFrame(PalScript *p, int nVal)
{
  PalScriptMgr *v5; // ecx
  int m_nTitleScript; // ecx
  int State; // eax
  PalScriptMgr *v8; // ecx
  int v9; // eax
  int v10; // eax
  ScreenEffectMgr *v11; // ecx
  int v12; // eax
  ScreenEffect *v13; // eax
  int m_hEffect; // ecx
  DWORD TickCount; // eax
  DWORD v16; // eax
  int m_dwTimerTick; // edi
  int v18; // ecx
  char *v19; // eax
  int v20; // eax
  ScreenEffectMgr *v21; // ecx
  ScreenEffect *Instance; // eax
  PalScriptMgr *v23; // ecx
  int v24; // eax
  char Buffer[253]; // [esp+0x8] [ebp-0x100] BYREF
  __int16 v26; // [esp+0x105] [ebp-0x3]
  char v27; // [esp+0x107] [ebp-0x1]

  if ( !*((_BYTE *)this + 9512) )
    return 0;
  if ( !(*(int ( **)(gbColorQuad *))(g_UISceneMapDlg.m_probe.m_fontcolor.Color + 4))(&g_UISceneMapDlg.m_probe.m_fontcolor)
    && *((_BYTE *)this + 3284) )
  {
    memset(Buffer, 0, sizeof(Buffer));
    m_nTitleScript = this->m_nTitleScript;
    v26 = 0;
    v27 = 0;
    sprintf(Buffer, "\\n          %s%d%s", (const char *)dword_DD8D3C, m_nTitleScript, (const char *)dword_DD8E3C);
    ((UICaption *)((char *)this + 2372))->SetEnable((int)Buffer, 0);
    ((UIRoleSelect *)((char *)this + 1916))->SetByte(1);
    *((_BYTE *)this + 3284) = 0;
  }
  ((PalScriptMgr *)v5)->RunSceneScript((const char *)p);
  State = ((UIParabolaCtrl *)(UIParabolaCtrl *)this + 479)->GetState();
  if ( State )
  {
    if ( State == 1 )
    {
      ((CCBEditor *)this)->InvokeItemMethod();
      this->ShowWindow(0);
    }
  }
  else
  {
    ((CCBEditor *)this)->InvokeItemMethod();
    this->ShowWindow(0);
    v8 = (PalScriptMgr *)this->m_nTitleScript;
    if ( ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom >= (int)v8 )
    {
      ((PalScriptMgr *)v8)->Destroy();
      *((_DWORD *)this + 2375) = v10;
      *((_BYTE *)this + 9512) = 1;
      this->m_bTimerDone = 0;
    }
    else
    {
      ((PalScriptMgr *)*((PalScriptMgr **)this + 2373))->Destroy();
      *((_DWORD *)this + 2376) = v9;
    }
  }
  if ( *((_DWORD *)this + 2375) )
  {
    ((PalScriptMgr *)*((void **)this + 2375))->ClearAllScript();
    if ( !v12 )
    {
      if ( this->m_bTimerDone )
      {
LABEL_18:
        m_hEffect = this->m_hEffect;
        if ( m_hEffect && !(*(int ( **)(int))(*(_DWORD *)m_hEffect + 4))(m_hEffect) )
        {
          if ( !this->m_bTimerActive )
          {
            TickCount = GetTickCount();
            this->m_dwEffectTick = TickCount;
            this->m_dwTimerTick = TickCount;
            this->m_bTimerActive = 1;
          }
          v16 = GetTickCount();
          m_dwTimerTick = this->m_dwTimerTick;
          this->m_dwEffectTick = v16;
          if ( v16 - m_dwTimerTick > 0x3E8 )
          {
            this->m_dwTimerTick = v16;
            this->m_bTimerActive = 0;
            this->m_bTimerDone = 0;
            this->m_bTimerProcessed = 1;
            v18 = 0;
            v19 = &::Buffer.m_partyActor.m_curact[39];
            do
            {
              if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + v18) )
              {
                *(_DWORD *)v19 = *((_DWORD *)v19 - 12);
                *((_DWORD *)v19 + 2) = *((_DWORD *)v19 - 10);
              }
              v19 += 1408;
              ++v18;
            }
            while ( (int)v19 < (int)&((RoleSystem *)&stru_C059A0)->m_teamSlots[220] );
            ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom -= this->m_nTitleScript;
            ((PtrArray *)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom)->RemoveAt("g_story");
            if ( v20 )
            {
              v21 = *(ScreenEffectMgr **)(v20 + 4);
              if ( v21 == (ScreenEffectMgr *)11101 )
              {
                *(_DWORD *)(v20 + 4) = 11200;
              }
              else if ( v21 == (ScreenEffectMgr *)120301 )
              {
                *(_DWORD *)(v20 + 4) = 120302;
              }
            }
            Instance = ((ScreenEffectMgr *)v21)->GetInstance();
            this->m_hEffect = ((ScreenEffectMgr *)Instance)->ProcessEffect();
          }
        }
        if ( this->m_bTimerDone )
          goto LABEL_37;
        goto LABEL_34;
      }
      if ( !this->m_bTimerProcessed )
      {
        this->m_bTimerDone = 1;
        v13 = ((ScreenEffectMgr *)v11)->GetInstance();
        this->m_hEffect = ((ScreenEffectMgr *)v13)->ProcessEffect();
      }
    }
  }
  if ( this->m_bTimerDone )
    goto LABEL_18;
LABEL_34:
  if ( this->m_bTimerProcessed
    && !(*(int ( **)(int))(*(_DWORD *)this->m_hEffect + 4))(this->m_hEffect) )
  {
    ((PalScriptMgr *)v23)->Destroy();
    *((_DWORD *)this + 2373) = 0;
    *((_DWORD *)this + 2372) = 0;
    *((_DWORD *)this + 2374) = 0;
    *((_DWORD *)this + 2375) = 0;
    *((_DWORD *)this + 2376) = 0;
    *((_DWORD *)this + 2377) = 0;
    this->m_bTimerDone = 0;
    this->m_bTimerProcessed = 0;
    *((_BYTE *)this + 3284) = 0;
    *((_BYTE *)this + 9512) = 0;
    ((CCBEditor *)this)->InvokeItemMethod();
    this->ShowWindow(0);
  }
LABEL_37:
  if ( *((_DWORD *)this + 2377) )
  {
    ((PalScriptMgr *)*((void **)this + 2377))->ClearAllScript();
    if ( !v24 && !*((_BYTE *)this + 9512) )
    {
      *((_DWORD *)this + 2373) = 0;
      *((_DWORD *)this + 2372) = 0;
      *((_DWORD *)this + 2374) = 0;
      *((_DWORD *)this + 2375) = 0;
      *((_DWORD *)this + 2376) = 0;
      *((_DWORD *)this + 2377) = 0;
      this->m_bTimerDone = 0;
      this->m_bTimerProcessed = 0;
      *((_BYTE *)this + 3284) = 0;
      *((_BYTE *)this + 9512) = 0;
      ((CCBEditor *)this)->InvokeItemMethod();
      this->ShowWindow(0);
    }
  }
  ((UIListBox *)this)->Update((int)p, nVal);
  return 1;
}

// 0x0044B460
// attributes: thunk
int UITitle::Render()
{
  int result; // eax

// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  return result;
}

// 0x0044B710
int UITitle::OnCommand(int nVal, char *pszBuf, int nVal2)
{
  CScreenMode *Instance; // eax
  PalScriptMgr *v7; // ecx
  const char *v8; // [esp-0x8] [ebp-0xC]

  if ( nVal == 1000 )
  {
    if ( pszBuf )
    {
      this->m_hEffect = 0;
      this->m_bTimerDone = 0;
      this->m_bTimerProcessed = 0;
    }
    return 1;
  }
  if ( nVal != 1001 )
    return ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
  if ( pszBuf != &byte_AABEF7 )
  {
    if ( pszBuf - &byte_AABEF7 == 1 )
    {
      *((_BYTE *)this + 3284) = 1;
      ((UISceneMap *)&g_UISceneMapDlg)->LoadCompass((const char *)&this->m_nTitleScript + 4, 0);
// [VFTABLE] ((void ( *)(UISceneMap *, int))g_UISceneMapDlg.__vftable->ShowWindow)(&g_UISceneMapDlg, 1);
// [VFTABLE] ((void ( *)(UISceneMap *, _DWORD, _DWORD))g_UISceneMapDlg.__vftable->Update_2ff0)(
// [VFTABLE]   &g_UISceneMapDlg,
// [VFTABLE]   0,
// [VFTABLE]   0);
      this->m_nTitleStage = 2;
      ((CCBEditor *)this)->InvokeItemMethod();
      *((_BYTE *)this + 9512) = 1;
      return 1;
    }
    if ( pszBuf - &byte_AABEF7 == 2 )
    {
      this->m_nTitleStage = 3;
      ((CCBEditor *)this)->InvokeItemMethod();
      this->ShowWindow(0);
      return 1;
    }
    return 1;
  }
  v8 = g_pCScreenMode;
  Instance = CScreenMode::GetInstance();
  ((CScreenMode *)Instance)->AudioSetPosition(v8, 1);
  this->m_nTitleStage = 1;
  ((CCBEditor *)this)->InvokeItemMethod();
  if ( *((_WORD *)&this->m_nTitleStage + 394) )
    ((PalScriptMgr *)v7)->Destroy();
  this->ShowWindow(0);
  return 1;
}
