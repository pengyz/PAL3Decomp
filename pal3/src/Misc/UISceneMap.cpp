#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UISceneMap.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_443CA0(...);
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_445FE0(void *a2); // from annotations

int crt_sub_00540070(void); // from annotations
int crt_sub_00540D20(void); // from annotations

// 0x00443CA0
char UISceneMap::sub_443CA0(int thisa, float fVal)
{
  struct tagPOINT Point; // [esp+0x4] [ebp-0x8]

  LOBYTE(this->m_probe.m_bcreateok) = 0;
  ((GRPinput *)&g_Input)->GetCursorPos();
  return ((SceneInfo *)this)->ProcessSceneChange(*(float *)&thisa, Point.x, Point.y);
}

// 0x00449F70
unsigned int UISceneMap::ValidateInput(unsigned int dwVal)
{
  unsigned int result; // eax
  char *v3; // esi
  int v4; // edx
  int v5; // edi

  result = dwVal;
  if ( dwVal <= 0x25 )
  {
    v3 = &this->m_base.m_text[476 * dwVal + 4];
    v4 = *(_DWORD *)&this->m_base.m_text[476 * dwVal + 12];
    *((_DWORD *)v3 + 22) = *(_DWORD *)&this->m_base.m_text[476 * dwVal + 16]
                         - (*(_DWORD *)&this->m_base.m_text[476 * dwVal + 16]
                          - *(_DWORD *)&this->m_base.m_text[476 * dwVal + 8])
                         / 2;
    v5 = *((_DWORD *)&this->m_base.m_pbkInfo + 119 * dwVal)
       - (*((_DWORD *)&this->m_base.m_pbkInfo + 119 * dwVal) - v4) / 2;
    *((_DWORD *)v3 + 23) = v5;
    return ((CCBRoleState *)this)->CalcSpringForce(*((_DWORD *)&this->m_compass.m_childs.m_pData + 119 * dwVal), v5);
  }
  return result;
}

// 0x0044FFE0
int UISceneMap::ctor()
{
  sub_4422E0(&this->m_probe.m_wndcolor);
  this->m_probe.m_fontcolor.Color = 0;
  this->m_wndcolor.Color = -1;
  return (int)this;
}

// 0x00450090
void UISceneMap::ctor_90()
{
  ((UIFrameWnd *)&this->m_probe.m_wndcolor)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x004501A0
double UISceneMap::Update(float fVal, int nVal)
{
  double result; // st7

  if ( (g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 1
     || g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2
     || g_Input.KeyInfo[6].PressTime == 1 && (g_Input.KeyInfo[6].Data & 0xF) == 1
     || g_Input.KeyInfo[6].PressTime == 1 && (g_Input.KeyInfo[6].Data & 0xF) == 2)
    && *(float *)&this->m_probe.m_texarray.m_num >= 4.5 )
  {
    ((CGameData *)&g_gamefrm)->Load((CUtil *)4);
  }
  result = fVal + *(float *)&this->m_probe.m_texarray.m_num;
  *(float *)&this->m_probe.m_texarray.m_num = result;
  return result;
}

// 0x00450230
void UISceneMap::Render()
{
  double v2; // st7
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x8]

  v2 = *(float *)&this->m_probe.m_texarray.m_num * 0.2;
  if ( v2 >= 1.0 )
    v2 = 1.0;
  HIBYTE(this->m_wndcolor.Color) = (__int64)(v2 * 255.0);
  crt_sub_00540070();
  BYTE2(this->m_wndcolor.Color) = -3;
  BYTE1(this->m_wndcolor.Color) = -11;
  LOBYTE(this->m_wndcolor.Color) = -13;
  ((NPC *)&this->m_probe.m_wndcolor)->NPC::UpdateAnim();
  ((CCBControlWindow *)this)->Render(v3);
}

// 0x00450DC0
UISceneMap::UISceneMap()
{
  this->m_probe.m_wndcolor.Color = 0;
  ((UITextArea *)&this->m_probe.m_id)->InitAfterClear();
  ((UIStatic *)&this->m_base.m_rect.right)->UIStatic_Base();
  ((SceneObj *)&this->m_compass.m_rect.bottom)->ctor();
  sub_4422E0(&this->m_compass.m_disablepicInfo);
  ((UIButton *)&this->m_mapbk.m_texs.m_ptex[4])->ctor_17();
// [VFTABLE] this->m_probe.__vftable = (vtbl_0056AE2C *)1;
  *((_DWORD *)this + 274) = 0;
  (int)this;
}

// 0x00451200
int UISceneMap::LoadCompass(const char *arg0, int nVal)
{
  LONG *p_bottom; // ebx
  gbTexture **v5; // edi
  int v6; // eax
  int result; // eax
  _BYTE a2[16]; // [esp+0x1C] [ebp-0x10] BYREF

  p_bottom = &this->m_compass.m_rect.bottom;
  ((SceneObj *)&this->m_compass.m_rect.bottom)->LoadData();
  ((string *)arg0)->_init_4530c0();
  v5 = &this->m_mapbk.m_texs.m_ptex[4];
  *((_DWORD *)this + 274) = nVal;
  *((_DWORD *)this + 275) = 0;
  *((_DWORD *)this + 276) = 0;
  ((UIProgressBar *)&this->m_mapbk.m_texs.m_ptex[4])->FindChildByName(0.0);
  ((UIListBox *)&this->m_mapbk.m_texs.m_ptex[4])->GetCurSel();
  v6 = *((_DWORD *)this + 274);
  if ( v6 )
  {
    result = v6 - 1;
    if ( !result )
    {
      ((void ( *)(_PlugInfo **, _DWORD))this->m_compass.m_disablepicInfo->filepos)(
        &this->m_compass.m_disablepicInfo,
        0);
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, int))(*v5)->0)(&this->m_mapbk.m_texs.m_ptex[4], 1);
      sub_445FE0(a2);
      return sub_445FA0(p_bottom);
    }
  }
  else
  {
    ((void ( *)(_PlugInfo **, int))this->m_compass.m_disablepicInfo->filepos)(
      &this->m_compass.m_disablepicInfo,
      1);
    // [VTBL_DISPATCH] return ((int ( *)(gbTexture **, _DWORD))(*v5)->0)(&this->m_mapbk.m_texs.m_ptex[4], 0);
  }
  return result;
}

// 0x0046F2C0
int UISceneMap::RenderWithUpdate()
{
  int v2; // eax
  int result; // eax

  ((PropUI *)this)->UpdateCaptions();
  v2 = *((_DWORD *)this + 7219);
  if ( !v2 )
    return ((UIFrameWnd *)*((UIFrameWnd **)this + 7220))->OnPaintUpdate();
  result = v2 - 1;
  if ( !result )
    return ((CUtil *)*((CUtil **)this + 7221))->Update(2.0f);
  return result;
}

// 0x004B42F0
int UISceneMap::ShowPage()
{
  char *v2; // ecx

  if ( g_bRoleFlag1 )
  {
    v2 = (char *)this + 2656;
  }
  else
  {
    ((PalScript *)((char *)this + 2656))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    v2 = (char *)this + 2656;
  }
  sub_445E50((int)v2);
  if ( !g_bRoleFlag2 )
    ((PalScript *)((char *)this + 3000))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)this + 3000);
  ((PalScript *)((char *)this + 3688))->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnSystem.tga", g_bDebugMode);
  sub_445E50((int)this + 3688);
  sub_445E50((int)this + 1280);
  sub_445E50((int)this + 1624);
  sub_445E50((int)this + 1968);
  sub_445E50((int)this + 2312);
  sub_445E50((int)this + 3344);
  return sub_445E50((int)this + 4032);
}

// 0x004B47E0
void UISceneMap::Destructor()
{
  ((UIFrameWnd *)&this->m_base.m_wndcolor)->UIFrameWnd::_UIFrameWnd();
}

// 0x00523E60
int UISceneMap::fn_523E60()
{
  return *((_DWORD *)this + 435) + 507436;
}

// 0x00527CD0
void UISceneMap::Render_527cd0()
{
  if ( *((_DWORD *)this + 436) )
    crt_sub_00540D20();
}

// 0x00529C80
void UISceneMap::Render_529c80()
{
  if ( *((_DWORD *)this + 547) )
    crt_sub_00540D20();
}

// 0x0052FBA0
int UISceneMap::SetCurrentMapID(int nVal)
{
  *((_DWORD *)this + 552) = nVal;
  return nVal;
}

// 0x00535930
gbVFileSystem * UISceneMap::LoadOverlayTexture(double thisa, int nVal)
{
  char *v4; // eax
  gbVFileSystem *result; // eax
  double v6; // [esp-0x8] [ebp-0x10]
  char *v7; // [esp+0x0] [ebp-0x8]
  char *v8; // [esp+0x4] [ebp-0x4]

  if ( SLODWORD(thisa) < 6 )
  {
    v4 = (char *)this + 512 * LODWORD(thisa);
    HIDWORD(v6) = v4 + 268;
    LODWORD(v6) = v4 + 12;
    result = ((PalScript *)this)->LoadVisNode(v6, v7, v8);
    this->m_wndcolor.Color = LODWORD(thisa);
  }
  return result;
}

// 0x00535960
int UISceneMap::SetColorIfValid(int nVal)
{
  int result; // eax

  result = nVal;
  if ( nVal )
    this->m_fontcolor.Color = nVal;
  return result;
}

// 0x00535E50
int UISceneMap::SetFieldIfValid(int nVal)
{
  int result; // eax

  result = nVal;
  if ( nVal )
    this->m_probe.m_texarray.m_ptex[15] = (gbTexture *)nVal;
  return result;
}
