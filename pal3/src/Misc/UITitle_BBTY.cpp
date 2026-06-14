#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UITitle_BBTY.h"

// Forward declarations for unnamed functions
int sub_43FEC0(void *a2); // from annotations
void sub_4422E0(void *_this); // from annotations
int sub_445AA0(void); // from annotations
void * sub_445FE0(void *a2); // from annotations

// Unnamed globals (extern)
extern void * off_5A6A3C;

// 0x00451CC0
int UITitle_BBTY::ctor_1CC0()
{
  sub_445AA0();
  ((UIButton *)&this->m_pbktex)->ctor_17();
  ((UIButton *)&this->buf[208])->ctor_17();
  sub_4422E0(&this->m_btn[0].m_benable_snd + 12);
  this->m_btn[1].m_texarray.m_ptex[4] = 0;
  return (int)this;
}

// 0x00451DA0
void UITitle_BBTY::ctor()
{
  ((UIFrameWnd *)(&this->m_btn[0].m_benable_snd + 12))->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->buf[208])->_UIButton();
  ((UIButton *)&this->m_pbktex)->_UIButton();
// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x00451E50
int UITitle_BBTY::CreateFromScript()
{
  int v2; // edx
  char *m_pData; // edx
  int v4; // edx
  void *v5; // eax
  gbTexture *m_pbktex; // edx
  void *v7; // eax
  _DWORD *v8; // ebx
  UIStatic *v9; // edi
  int v10; // ebp
  int result; // eax
  tagRECT pRect; // [esp+0x48] [ebp-0x20] BYREF
  _DWORD a2[4]; // [esp+0x58] [ebp-0x10] BYREF
  int parent; // [esp+0x6C] [ebp+0x4]

  pRect.right = g_DrvInfo.width;
  pRect.left = g_DrvInfo.width - 71;
  pRect.top = 5;
  pRect.bottom = 95;
  ((PalScript *)this)->Create(0, &pRect, parent);
  v2 = *((_DWORD *)&this->m_btn[0].m_benable_snd + 3);
  pRect.top = 0;
  pRect.left = 0;
  pRect.right = 71;
  pRect.bottom = 90;
  (*(void ( **)(_BYTE *, int, tagRECT *, UITitle_BBTY *))(v2 + 16))(
    &this->m_btn[0].m_benable_snd + 12,
    1,
    &pRect,
    this);
  ((UIStatic *)(&this->m_btn[0].m_benable_snd + 12))->CreateFromTemplate();
  m_pData = this->m_remark.m_childs.m_pData;
  pRect.left = 15;
  pRect.right = 79;
  pRect.top = 4;
  pRect.bottom = 68;
  (*((void ( **)(PtrArray *, int, tagRECT *, UITitle_BBTY *))m_pData + 4))(
    &this->m_remark.m_childs,
    2,
    &pRect,
    this);
  (*(void ( **)(LONG *, int, tagRECT *, UITitle_BBTY *))(this->m_btn[0].m_rect.bottom + 16))(
    &this->m_btn[0].m_rect.bottom,
    3,
    &pRect,
    this);
  (*(void ( **)(_PlugInfo **, int, tagRECT *, UITitle_BBTY *))&this->m_btn[0].m_disablepicInfo->name[12])(
    &this->m_btn[0].m_disablepicInfo,
    3,
    &pRect,
    this);
  this->SetRemarkTextures(0);
  v4 = *(_DWORD *)&this->buf[208];
  pRect.left = 2;
  pRect.top = 1;
  pRect.right = 52;
  pRect.bottom = 44;
  (*(void ( **)(char *, _DWORD, tagRECT *, UITitle_BBTY *))(v4 + 16))(&this->buf[208], 0, &pRect, this);
  v5 = sub_445FE0(a2);
  sub_43FEC0(v5);
  ((UIScene *)&this->buf[208])->GetChildAt();
  m_pbktex = this->m_pbktex;
  pRect.left = 4;
  pRect.top = 48;
  pRect.right = 47;
  pRect.bottom = 82;
  (*((void ( **)(gbTexture **, _DWORD, tagRECT *, UITitle_BBTY *))m_pbktex + 4))(
    &this->m_pbktex,
    0,
    &pRect,
    this);
  v7 = sub_445FE0(a2);
  sub_43FEC0(v7);
  ((UIScene *)&this->m_pbktex)->GetChildAt();
  ((UIScrollBar *)&this->buf[208])->SetRange(10.0);
  ((UIProgressBar *)&this->buf[208])->FindChildByName(10.0);
  ((UIScrollBar *)&this->m_pbktex)->SetRange(10.0);
  ((UIProgressBar *)&this->m_pbktex)->FindChildByName(10.0);
  pRect.left = 47;
  pRect.right = 79;
  pRect.top = 5;
  pRect.bottom = 69;
  a2[0] = "ui\\scene\\face\\bx.tga";
  a2[1] = "ui\\scene\\face\\tm.tga";
  a2[2] = "ui\\scene\\face\\sy.tga";
  a2[3] = "ui\\scene\\face\\jj.tga";
  v8 = a2;
  v9 = (UIStatic *)&this->m_btn[1].m_texarray.m_ptex[5];
  v10 = 4;
  do
  {
// [VFTABLE] ((void ( *)(UIStatic *, _DWORD, tagRECT *, UITitle_BBTY *))v9->__vftable->Create)(v9, 0, &pRect, this);
    ((UIStatic *)v9)->CreateFromTemplate();
// [VFTABLE] result = ((int ( *)(UIStatic *, _DWORD))v9->__vftable->ShowWindow)(v9, 0);
    ++v8;
    ++v9;
    --v10;
  }
  while ( v10 );
  return result;
}

// 0x004520A0
double UITitle_BBTY::UpdateFrame(double result, int arg0, int arg0a)
{
  double v4; // st7
  CScreenMode *SoundList; // eax
  unsigned int v7; // edi
  int v8; // ebp
  NPC *v9; // esi
  void ( **vftable)(NPC *, int); // edx
  unsigned int v11; // ebp
  int v12; // eax
  PtrArray *p_m_childs; // esi
  LONG *p_bottom; // edi
  _PlugInfo **p_m_disablepicInfo; // ebp
  CScreenMode *v16; // ecx
  CScreenMode *v17; // eax
  float fValue; // [esp+0x0] [ebp-0x44]
  float fValuea; // [esp+0x0] [ebp-0x44]
  float fValueb; // [esp+0x0] [ebp-0x44]
  float fValuec; // [esp+0x0] [ebp-0x44]
  gbColorQuad v22; // [esp+0x14] [ebp-0x30] BYREF
  POINT pt; // [esp+0x1C] [ebp-0x28]
  RECT rc; // [esp+0x24] [ebp-0x20] BYREF
  _BYTE a2[16]; // [esp+0x34] [ebp-0x10] BYREF

  if ( this->m_bvisible && this->m_benable )
  {
    if ( this->m_btn[1].m_texarray.m_ptex[4] )
    {
      v4 = *(float *)&result + *(float *)&this->m_btn[1].m_texarray.m_ptex[3];
      *(float *)&this->m_btn[1].m_texarray.m_ptex[3] = v4;
      if ( v4 <= 0.80000001 )
        return v4;
      this->m_btn[1].m_texarray.m_ptex[3] = 0;
      this->m_btn[1].m_texarray.m_ptex[4] = 0;
      SoundList = (CScreenMode *)((CScreenMode *)this)->GetSoundList();
      if ( !((CScreenMode *)SoundList)->IsAudioReady()
        || g_pRoleSystem->m_FrameA.m_rect.right == 4
        || g_nCameraUpdateCount <= 0
        || LOBYTE(g_CCBEditorInst.m_dwTrickID[358]) )
      {
        if ( g_CCBEditorInst.m_dwTrickID[361] != 12 )
          return v4;
      }
      else
      {
        ((RoleSystem *)&g_pRoleSystem)->Notify();
      }
      ((CGameData *)&g_gamefrm)->Load((CUtil *)5);
    }
    else
    {
      v7 = 1408 * g_nCurrentRoleSlot;
      fValue = (float)(int)Buffer.m_partyActor.m_dwMatMsg[352 * g_nCurrentRoleSlot + 9];
      ((UIScrollBar *)&this->buf[208])->SetRange(fValue);
      fValuea = (float)*(int *)&Buffer.m_partyActor.m_curact[v7 + 39];
      ((UIProgressBar *)&this->buf[208])->FindChildByName(fValuea);
      fValueb = (float)(int)Buffer.m_partyActor.m_dwMatMsg[v7 / 4 + 11];
      ((UIScrollBar *)&this->m_pbktex)->SetRange(fValueb);
      v4 = (double)*(int *)&Buffer.m_partyActor.m_curact[v7 + 47];
      fValuec = v4;
      ((UIProgressBar *)&this->m_pbktex)->FindChildByName(fValuec);
      v8 = 27;
      v9 = (NPC *)&this->m_btn[1].m_texarray.m_ptex[5];
      do
      {
// [VFTABLE] vftable = (void ( **)(NPC *, int))v9->__vftable;
        if ( *(&Buffer.m_partyActor.m_nActionParam + v8) )
        {
          (*vftable)(v9, 1);
          v4 = (1.0 - g_fFadeTimer / 60.0) * 255.0;
          if ( v4 < 80.0 )
            v4 = 80.0;
          ((NPC *)v9)->NPC::UpdateAnim();
        }
        else
        {
          (*vftable)(v9, 0);
        }
        ++v8;
        v9 = (NPC *)((char *)v9 + 152);
      }
      while ( v8 <= 30 );
      switch ( g_nCurrentEventId )
      {
        case 0u:
          v11 = -11356565;
          break;
        case 1u:
          v11 = -6002966;
          break;
        case 2u:
          v11 = -13002067;
          break;
        case 3u:
          v11 = -2198223;
          break;
        case 4u:
          v11 = -2707878;
          break;
        default:
          v11 = -1;
          break;
      }
      v12 = *(_DWORD *)&Buffer.m_partyActor.m_curact[v7 + 39];
      v22.Color = v11;
      if ( 100 * v12 / (int)Buffer.m_partyActor.m_dwMatMsg[v7 / 4 + 9] < 25 )
      {
        BYTE2(v22.Color) >>= 2;
        BYTE1(v22.Color) = BYTE1(v22.Color) / 5;
        LOBYTE(v22.Color) = LOBYTE(v22.Color) / 5;
      }
      p_m_childs = &this->m_remark.m_childs;
      ((NPC *)&this->m_remark.m_childs)->NPC::UpdateAnim();
      p_bottom = &this->m_btn[0].m_rect.bottom;
      ((NPC *)&this->m_btn[0].m_rect.bottom)->NPC::UpdateAnim();
      p_m_disablepicInfo = &this->m_btn[0].m_disablepicInfo;
      ((NPC *)&this->m_btn[0].m_disablepicInfo)->NPC::UpdateAnim();
      ((GRPinput *)&g_Input)->GetCursorPos();
      rc = *(RECT *)sub_445FE0(a2);
      if ( PtInRect(&rc, pt) && (v17 = (CScreenMode *)((CScreenMode *)v16)->GetSoundList(), ((CScreenMode *)v17)->IsAudioReady()) )
      {
        (*(void ( **)(PtrArray *, _DWORD))p_m_childs->m_pData)(&this->m_remark.m_childs, 0);
        (*(void ( **)(LONG *, int))*p_bottom)(&this->m_btn[0].m_rect.bottom, 1);
        ((void ( *)(_PlugInfo **, _DWORD))(*p_m_disablepicInfo)->filepos)(&this->m_btn[0].m_disablepicInfo, 0);
      }
      else
      {
        (*(void ( **)(PtrArray *, int))p_m_childs->m_pData)(&this->m_remark.m_childs, 1);
        (*(void ( **)(LONG *, _DWORD))*p_bottom)(&this->m_btn[0].m_rect.bottom, 0);
        ((void ( *)(_PlugInfo **, _DWORD))(*p_m_disablepicInfo)->filepos)(&this->m_btn[0].m_disablepicInfo, 0);
      }
      ((UIListBox *)this)->Update(SLODWORD(result), SHIDWORD(result));
    }
  }
  return v4;
}

// 0x00452420
int UITitle_BBTY::OnMessage(int nVal, int nVal2, int nVal3)
{
  CScreenMode *Instance; // eax
  PAL3 *v6; // ecx
  const void *v8; // [esp-0x8] [ebp-0xC]

  if ( nVal == 1009 && (nVal2 == 2 || nVal2 == 3) )
  {
    this->m_btn[1].m_texarray.m_ptex[3] = 0;
    this->m_btn[1].m_texarray.m_ptex[4] = (gbTexture *)1;
    v8 = off_5A6A3C;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v8, 1);
    (*(void ( **)(PtrArray *, _DWORD))this->m_remark.m_childs.m_pData)(&this->m_remark.m_childs, 0);
    (*(void ( **)(LONG *, _DWORD))this->m_btn[0].m_rect.bottom)(&this->m_btn[0].m_rect.bottom, 0);
    ((void ( *)(_PlugInfo **, int))this->m_btn[0].m_disablepicInfo->filepos)(
      &this->m_btn[0].m_disablepicInfo,
      1);
    ((PAL3 *)v6)->DefaultKeyMap(0, 64);
  }
  return 1;
}

// 0x004524B0
void UITitle_BBTY::SetRemarkTextures(int nVal)
{
  int v2; // esi
  PtrArray *p_m_childs; // edi
  char Buffer[260]; // [esp+0xC] [ebp-0x104] BYREF

  v2 = 0;
  p_m_childs = &this->m_remark.m_childs;
  do
  {
    sprintf(Buffer, "ui\\scene\\face\\face%d\\face%02d.tga", nVal, v2);
    ((UIStatic *)p_m_childs)->LoadTextureByName(Buffer, 0);
    ++v2;
    p_m_childs = (PtrArray *)((char *)p_m_childs + 152);
  }
  while ( v2 < 3 );
}
