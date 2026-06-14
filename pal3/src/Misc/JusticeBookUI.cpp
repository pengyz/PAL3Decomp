#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/JusticeBookUI.h"

// Forward declarations for unnamed functions
int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc); // from annotations
void sub_4422E0(void *_this); // from annotations

int * ctor_0x431870(int *_this); // from annotations

// Unnamed globals (extern)
extern int dword_DDAE3C;
extern void * off_5EB920;

// 0x0044DA30
char JusticeBookUI::UpdateFadeAnim(float fDelta)
{
  char result; // al
  double v3; // st7

  result = this->m_tpID[88][5];
  if ( result )
  {
    v3 = fDelta * 80.0 + *(float *)&this->m_tpID[89][0];
    *(float *)&this->m_tpID[89][0] = v3;
    if ( v3 >= 255.0 )
    {
      this->m_tpID[89][0] = 1132396544;
      LOBYTE(this->m_tpID[88][5]) = 0;
    }
    ((NPC *)&this->m_tpID[82][3])->NPC::UpdateAnim();
  }
  return result;
}

// 0x005282E0
int JusticeBookUI::ctor()
{
  char *m_text; // edi
  int v3; // ebp
  int *p_m_bcreateok; // edi
  int v5; // ebp

  this->bkWndX = 800;
  this->bkWndY = 600;
  UIScene::GetSys();
  sub_4422E0(&this->m_Exit.m_texarrayInfo[2]);
  sub_4422E0(&this->m_Exit.m_benable_snd + 4);
  sub_4422E0(&this->m_OutFrameT.m_disablepicInfo);
  sub_4422E0(&this->m_OutFrameR.m_ppicInfo);
  sub_4422E0(&this->m_OutFrameL.m_pbkInfo);
  sub_4422E0(&this->m_OutFrameB.m_text[12]);
  sub_4422E0(&this->m_JusticeBook.m_obj[0].m_pos.z);
  sub_4422E0(&this->m_JusticeBook.m_rotatetarget);
  ((UIProgressBar *)&this->m_Monster.m_obj[0].m_pos.y)->ctor();
  m_text = this->m_Name.m_text;
  v3 = 5;
  do
  {
    m_text += 12;
    --v3;
  }
  while ( v3 );
  ((UIProgressBar *)((char *)&this->m_Name + 156))->ctor();
  sub_4422E0(&this->m_S.m_FVF);
  sub_4422E0(&this->m_Wuling[0].m_pbk2);
  ctor_0x431870(&this->m_Wuling[1].m_FVF);
  p_m_bcreateok = &this->m_Sorcery[3].m_bcreateok;
  v5 = 5;
  do
  {
    ArraySort((int)p_m_bcreateok, 800, 2, 0 /* TODO: (int)ArcSceneObject::InitFromConfig */);
    p_m_bcreateok += 402;
    --v5;
  }
  while ( v5 );
  *((_DWORD *)this + 3186) = 0;
  ((ARC_PlayerAtt *)((char *)this + 12752))->Refresh();
  *((_BYTE *)this + 56188) = 0;
  *((_BYTE *)this + 56189) = 0;
  *(_DWORD *)&this->m_Wuling[1].m_mouseoff = 0;
  return (int)this;
}

// 0x005284E0
void JusticeBookUI::ctor_84E0()
{
  ((UIRoleDialog *)((char *)this + 12752))->_UIRoleDialog();
  ((PalScript *)&this->m_Wuling[1].m_FVF)->Cleanup();
  ((UIFrameWnd *)&this->m_Wuling[0].m_pbk2)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_S.m_FVF)->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)((char *)&this->m_Name + 156))->PalScript_Init();
  ((PalScript *)&this->m_Monster.m_obj[0].m_pos.y)->PalScript_Init();
  ((UIFrameWnd *)&this->m_JusticeBook.m_rotatetarget)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_JusticeBook.m_obj[0].m_pos.z)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameB.m_text[12])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameL.m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameR.m_ppicInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_OutFrameT.m_disablepicInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)(&this->m_Exit.m_benable_snd + 4))->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_Exit.m_texarrayInfo[2])->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->buf[248])->Destroy2();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00528ED0
void JusticeBookUI::Render()
{
  ScreenEffect *v2; // esi
  int v3; // ebp
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v4);
  if ( *((_BYTE *)this + 56188) )
  {
    v2 = (ScreenEffect *)((char *)this + 35148);
    v3 = 36;
    do
    {
// [IDA_MISID]       if ( ((Concurrency *)&v2[-876])->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)v2 - 876)->Apply();
// [IDA_MISID]       if ( ((Concurrency *)v2)->details::VirtualProcessor::IsThrottled() )
        ((ScreenEffect *)v2)->Apply();
      v2 = (ScreenEffect *)((char *)v2 + 584);
      --v3;
    }
    while ( v3 );
    *((_BYTE *)this + 56188) = 0;
    *((_BYTE *)this + 56189) = 1;
  }
  else if ( *((_BYTE *)this + 56189) )
  {
    ((SceneMgr *)this)->LoadMainUITexture();
  }
}

// 0x00528F50
int JusticeBookUI::ProcessInput(int nVal, int nVal2)
{
  int *p_i; // edi
  const char *v5; // ecx
  const char *v7; // [esp-0x4] [ebp-0x64]
  POINT pt; // [esp+0x8] [ebp-0x58]
  RECT rc; // [esp+0x10] [ebp-0x50] BYREF
  RECT v10; // [esp+0x20] [ebp-0x40] BYREF
  RECT v11; // [esp+0x30] [ebp-0x30] BYREF
  RECT v12; // [esp+0x40] [ebp-0x20] BYREF
  RECT v13; // [esp+0x50] [ebp-0x10] BYREF

  if ( !LOBYTE(this->m_Wuling[1].m_pbk2) )
  {
    ((GRPinput *)&g_Input)->GetCursorPos();
    rc.top = 179;
    v10.top = 179;
    rc.bottom = 348;
    v10.bottom = 348;
    v11.top = 406;
    v12.top = 406;
    v13.top = 406;
    v11.bottom = 575;
    v12.bottom = 575;
    v13.bottom = 575;
    rc.left = 199;
    rc.right = 337;
    v10.left = 464;
    v10.right = 602;
    v11.left = 128;
    v11.right = 266;
    v12.left = 334;
    v12.right = 472;
    v13.left = 540;
    v13.right = 678;
    if ( PtInRect(&rc, pt) )
    {
      p_i = &this->i;
      sprintf(
        (char *const)&this->i,
        "%s\\n%s\\n",
        (const char *)&this->m_Sorcery[3].m_bvisible,
        (const char *)&this->m_Sorcery[3].m_nTextW);
LABEL_13:
      ((UICaption *)&this->m_OutFrameB.m_text[12])->SetEnable((int)p_i, 0);
      goto LABEL_15;
    }
    if ( PtInRect(&v10, pt) )
    {
      p_i = &this->i;
      v7 = (const char *)(&this->m_tpImmortal._todo_0EC + 3);
      v5 = &this->m_tpImmortal.m_caption[56];
    }
    else
    {
      if ( PtInRect(&v11, pt) )
      {
        p_i = &this->i;
        sprintf(
          (char *const)&this->i,
          "%s\\n%s\\n",
          (const char *)&this->m_tpGhost_unopen,
          (const char *)&this->m_tpGhost_unopen.m_disablepic);
        goto LABEL_13;
      }
      if ( PtInRect(&v12, pt) )
      {
        p_i = &this->i;
        sprintf(
          (char *const)&this->i,
          "%s\\n%s\\n",
          (const char *)&this->m_tpID[23][4],
          (const char *)&this->m_tpID[27][3]);
        goto LABEL_13;
      }
      if ( !PtInRect(&v13, pt) )
      {
        ((UICaption *)&this->m_OutFrameB.m_text[12])->SetEnable((int)g_szSceneUIText, 0);
        goto LABEL_15;
      }
      p_i = &this->i;
      v7 = (const char *)&this->m_tpID[94][3];
      v5 = (const char *)&this->m_tpID[90][4];
    }
    sprintf((char *const)p_i, "%s\\n%s\\n", v5, v7);
    goto LABEL_13;
  }
LABEL_15:
  ((UIListBox *)this)->Update(nVal, nVal2);
  return 1;
}

// 0x00529120
int JusticeBookUI::OnMessage(int nVal, char *pszBuf, int nVal2)
{
  DWORD TickCount; // eax
  int result; // eax
  int v7; // ecx
  int v8; // eax
  int *p_m_enable; // eax
  int v10; // ecx
  int *v11; // ebx
  int v12; // eax
  CScreenMode *Instance; // eax
  const void *v14; // [esp-0x8] [ebp-0x1C]
  int v15; // [esp-0x4] [ebp-0x18]
  int pOut; // [esp+0xC] [ebp-0x8] BYREF
  int pOut2; // [esp+0x10] [ebp-0x4] BYREF

  switch ( nVal )
  {
    case 1000:
      if ( !pszBuf )
        goto LABEL_16;
      TickCount = GetTickCount();
      CRT_set_new_handler(TickCount);
      ((SceneMgr *)this)->LoadMainUITexture();
      ((UICaption *)((char *)this + 13208))->SetEnable((int)dword_DDAE3C, 0);
      ((UIRoleSelect *)((char *)this + 12752))->SetByte(1);
      ((UIParticle *)this)->CountActiveParticles();
      return 1;
    case 1001:
      if ( pszBuf != (char *)&g_PlayerAttBuffer.id + 1 )
        goto LABEL_16;
      v7 = *((_DWORD *)this + 3187);
      v15 = *(_DWORD *)&this->m_Wuling[1].m_mouseoff;
      *(_DWORD *)(v7 + 15008) = v15;
      ((CCBAttackSequen *)v7)->FindSequenceSlot(v15);
      v8 = *((_DWORD *)this + 3187);
      qmemcpy((void *)(v8 + 6964), &this->m_Sorcery[3].m_childs.m_nSize, 0x1F68u);
      *(_BYTE *)(v8 + 15004) = 1;
      ((CScreenMode *)*((CScreenMode **)this + 3186))->InitSceneAudio(2);
      goto LABEL_14;
    case 1002:
      if ( pszBuf != (char *)&g_PlayerAttBuffer.id + 1 )
        goto LABEL_16;
      *((_BYTE *)this + 56188) = 1;
      result = 1;
      break;
    case 1010:
      ((UISceneFrm *)this)->CallFaceMethod(*(_DWORD *)&this->m_Wuling[1].m_mouseoff, 0);
      *(_DWORD *)&this->m_S.m_text[12] = 0;
      *(_DWORD *)&this->m_S.m_text[8] = 0;
      *(_DWORD *)&this->m_S.m_text[4] = 0;
      ((UICaption *)&this->m_OutFrameB.m_text[12])->SetEnable((int)g_szSceneUIText, 0);
      ((UICaption *)&this->m_JusticeBook.m_rotatetarget)->SetEnable((int)g_szSceneUIText, 0);
      *(_DWORD *)&this->m_Wuling[1].m_mouseoff = 0;
      p_m_enable = &this->m_Monster.m_obj[3].m_enable;
      v10 = 5;
      do
      {
        *p_m_enable = 1;
        p_m_enable += 8;
        --v10;
      }
      while ( v10 );
      v14 = off_5EB920;
      goto LABEL_15;
    case 1013:
      if ( pszBuf != &g_PlayerAttBuffer.Remark[2] )
        goto LABEL_16;
      *(&this->m_H.m_align + 8 * *(_DWORD *)&this->m_Wuling[1].m_mouseoff) = 0;
      *(_DWORD *)&this->m_S.m_text[12] = 0;
      *(_DWORD *)&this->m_S.m_text[8] = 0;
      *(_DWORD *)&this->m_S.m_text[4] = 0;
      *(_DWORD *)&this->m_Wuling[1].m_mouseoff = nVal2;
      ((UISceneFrm *)this)->CallFaceMethod(nVal2, 1u);
      sprintf(
        (char *const)&this->i,
        "%s\\n%s\\n",
        (const char *)&this->m_Sorcery[3].m_bvisible + 1608 * *(_DWORD *)&this->m_Wuling[1].m_mouseoff,
        (const char *)&this->m_Sorcery[3].m_nTextW + 1608 * *(_DWORD *)&this->m_Wuling[1].m_mouseoff);
      ((UICaption *)&this->m_OutFrameB.m_text[12])->SetEnable((int)&this->i, 0);
      ((UICaption *)&this->m_JusticeBook.m_rotatetarget)->SetEnable((int)(&this->m_Sorcery[3].m_bvisible + 402 * *(_DWORD *)&this->m_Wuling[1].m_mouseoff), 1);
      v11 = &this->m_Monster.m_obj[3].m_enable;
      v12 = 5;
      do
      {
        *v11 = 0;
        v11 += 8;
        --v12;
      }
      while ( v12 );
LABEL_14:
      v14 = off_5EB920;
LABEL_15:
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v14, 1);
LABEL_16:
      result = 1;
      break;
    case 1016:
      if ( pszBuf == &g_PlayerAttBuffer.Remark[3] )
      {
        ((GRPinput *)&g_Input)->GetMousePos(&pOut, &pOut2);
        *(float *)&this->m_S.m_text[4] = (double)pOut2 + *(float *)&this->m_S.m_text[4];
        *(float *)&this->m_S.m_text[8] = (double)pOut + *(float *)&this->m_S.m_text[8];
      }
      return 1;
    default:
      return ((PalScript *)this)->OnMessage(nVal, (int)pszBuf, nVal2);
  }
  return result;
}
