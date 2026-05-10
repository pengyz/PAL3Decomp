#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIWnd.h"
#include "pal3/gen/CCBControlWindow.h"
#include "pal3/gen/CCBItemWindow.h"
#include "pal3/gen/CCBMagicWindow.h"
#include "pal3/gen/CCBSkillWindow.h"
#include "pal3/gen/CCBUI.h"
#include "pal3/gen/CGameData.h"
#include "pal3/gen/CScreenMode.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/Object3D.h"
#include "pal3/gen/ObjectCamera.h"
#include "pal3/gen/OpenBaseFile.h"
#include "pal3/gen/OpenNULLFile.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/PalScript.h"
#include "pal3/gen/Parent_Data.h"
#include "pal3/gen/PtrArray.h"
#include "pal3/gen/UICursor.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIItem.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UINote.h"
#include "pal3/gen/UIQuadManager.h"
#include "pal3/gen/UIRenderObj.h"
#include "pal3/gen/UIScene.h"
#include "pal3/gen/UIStatic.h"

// Forward declarations for unnamed functions
int ArraySort(...);
int sub_40CC60(...);
int sub_41C090(...);
int sub_432680(...);
int sub_4391A0(...);
int sub_439230(...);
int sub_439740(...);
int sub_439810(...);
int sub_439850(...);
int sub_43A090(...);
int sub_43B3E0(...);
int sub_43B4D0(...);
int sub_43BE80(...);
int sub_43F650(...);
int sub_43F9C0(...);
int sub_440CE0(...);
int sub_4414D0(...);
int sub_443190(...);
int sub_4431D0(...);
int sub_4434C0(...);
int sub_4438F0(...);
int sub_444A20(...);
int sub_445BF0(...);
int sub_445E10(...);
int sub_4461B0(...);
int sub_4461F0(...);
int sub_44A3D0(...);
int sub_44A7F0(...);
int sub_44B850(...);
int sub_44BE60(...);
int sub_44C910(...);
int sub_44C970(...);
int sub_44DB50(...);
int sub_44E5E0(...);
int sub_450390(...);
int sub_450AD0(...);
int sub_450EB0(...);
int sub_451900(...);
int sub_4543C0(...);
int sub_454420(...);
int sub_4544F0(...);
int sub_4549A0(...);
int sub_454AA0(...);
int sub_456E20(...);
int sub_456EE0(...);
int sub_459360(...);
int sub_45A220(...);
int sub_45ADD0(...);
int sub_472AA0(...);
int sub_473520(...);
int sub_473B50(...);
int sub_475FC0(...);
int sub_4765D0(...);
int sub_4765F0(...);
int sub_476ED0(...);
int sub_4777B0(...);
int sub_477A90(...);
int sub_47BDF0(...);
int sub_47EC00(...);
int sub_47F410(...);
int sub_483280(...);
int sub_483300(...);
int sub_486CE0(...);
int sub_486D20(...);
int sub_486EF0(...);
int sub_490E90(...);
int sub_4910B0(...);
int sub_498C90(...);
int sub_498E60(...);
int sub_4A22E0(...);
int sub_4A6600(...);
int sub_4A6730(...);
int sub_4A67B0(...);
int sub_4B6FB0(...);
int sub_4B7AF0(...);
int sub_4B7F00(...);
int sub_4BC7B0(...);
int sub_4BF170(...);
int sub_5040D0(...);
int sub_516170(...);
int sub_51A400(...);
int sub_51B6E0(...);
int sub_522030(...);
int sub_522120(...);
int sub_523820(...);
int sub_5254C0(...);
int sub_526300(...);
int sub_5263C0(...);
int sub_5270C0(...);
int sub_527130(...);
int sub_527230(...);
int sub_527370(...);
int sub_5273D0(...);
int sub_527F50(...);
int sub_52BBD0(...);
int sub_52BC90(...);

// Unnamed globals (extern)
extern char aDefault[];
extern char aNone[];
extern char aSubgameApprais_1[];
extern char aSubgameApprais_10[];
extern char aSubgameApprais_11[];
extern char aSubgameApprais_2[];
extern char aSubgameApprais_3[];
extern char aSubgameApprais_4[];
extern char aSubgameApprais_5[];
extern char aSubgameApprais_6[];
extern char aSubgameApprais_7[];
extern char aSubgameApprais_8[];
extern char aSubgameApprais_9[];
extern char aUiFlexNote[];
extern char aUiGamemainuiCo_17[];
extern char aUiGamemainuiMu_0[];
extern unsigned char byte_DC333C;
extern unsigned char byte_DC343C;
extern unsigned char byte_DC5F3C;
extern unsigned char byte_DD2A3C;
extern unsigned char byte_DD2B3C;
extern unsigned char byte_DD2C3C;
extern unsigned char byte_DD2D3C;
extern unsigned char byte_DD2E3C;
extern unsigned char byte_DD2F3C;
extern unsigned char byte_DD303C;
extern unsigned char byte_DD313C;
extern unsigned char byte_DD323C;
extern unsigned char byte_DD333C;
extern unsigned char byte_DD343C;
extern unsigned char byte_DD553C;
extern unsigned char byte_DD953C;
extern unsigned char byte_DD963C;
extern unsigned char byte_DDB03C;
extern unsigned char byte_DDB13C;
extern int dword_1894B78;
extern int dword_56AEE8;
extern int dword_56B220;
extern int dword_56B294;
extern int dword_56B77C;
extern int dword_BFD6D0;
extern int dword_BFD6D4;
extern int dword_BFDA4C;
extern int dword_BFDA60;
extern int dword_DE5F98;
extern int dword_DE5F9C;
extern int dword_DE5FA0;
extern int nullsub_1;
extern int nullsub_3;
extern void *off_56AC20;
extern void *off_56AC4C;
extern void *off_56ACB8;
extern void *off_56ACD8;
extern void *off_56ACFC;
extern void *off_56AD20;
extern void *off_56AD64;
extern void *off_56AD88;
extern void *off_56ADAC;
extern void *off_56AE10;
extern void *off_56AE64;
extern void *off_56AEC8;
extern void *off_56AF80;
extern void *off_56AFD4;
extern void *off_56AFFC;
extern void *off_56B018;
extern void *off_56B094;
extern void *off_56B0B4;
extern void *off_56B100;
extern void *off_56B19C;
extern void *off_56B1BC;
extern void *off_56B1DC;
extern void *off_56B200;
extern void *off_56B22C;
extern void *off_56B274;
extern void *off_56B364;
extern void *off_56B394;
extern void *off_56B5CC;
extern void *off_56B688;
extern void *off_56B794;
extern void *off_56B820;
extern void *off_56B850;
extern void *off_56B90C;
extern void *off_56BA30;
extern void *off_56C590;
extern void *off_56D618;
extern void *off_56E170;
extern void *off_56F040;
extern void *off_56F29C;
extern void *off_56F33C;
extern void *off_56F404;
extern void *off_56F450;
extern void *off_56F580;
extern void *off_56FD78;
extern void *off_5704A8;
extern void *off_5704C8;
extern void *off_5704E4;
extern void *off_570500;
extern void *off_57051C;
extern void *off_570538;
extern void *off_570554;
extern void *off_570570;
extern void *off_57058C;
extern void *off_570630;
extern void *off_5706AC;
extern void *off_5706C0;
extern void *off_5706CC;
extern void *off_5706EC;
extern void *off_570728;
extern void *off_57076C;
extern void *off_570830;
extern void *off_570890;
extern void *off_5ABBE0;
extern void *off_5B0DA4;
extern void *off_5B9DE4;
extern void *off_5E7ECC;
extern void *off_5E7ED8;
extern int unk_1010101;
extern int unk_A3A7D8;
extern int unk_AA0B00;
extern int unk_AA0C00;
extern int unk_AA0C16;
extern int unk_AA0C17;
extern int unk_AA0C18;
extern int unk_AA0C19;
extern int unk_AA0C21;
extern int unk_AA0C22;
extern int unk_AA0C23;
extern int unk_AA0C25;
extern int unk_AA0C26;
extern int unk_AA0C27;
extern int unk_ABC00C;
extern int unk_ABE00B;
extern int unk_D90D3C;
extern int unk_DE5FA4;
extern int word_DE5FA8;

// 0x00439030
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_DWORD * UIWnd::ctor_9030()
{
  this->UIWnd();
  `eh vector constructor iterator'((char *)this + 72, 0x20u, 5, (void (*)(void *))sub_4391A0, nullsub_3);
  *((_DWORD *)this + 74) = 0;
  *((_DWORD *)this + 75) = 0;
  *((_DWORD *)this + 76) = 0;
  *((_DWORD *)this + 71) = 1065353216;
  *((_DWORD *)this + 70) = 1065353216;
  *((_DWORD *)this + 69) = 1065353216;
  *(_DWORD *)this->_pad_000 = &off_56AC20;
  *((_DWORD *)this + 73) = 0;
  *((_DWORD *)this + 17) = 0;
  *((_DWORD *)this + 59) = 0;
  *((_DWORD *)this + 63) = 0;
  *((_DWORD *)this + 62) = 0;
  *((_DWORD *)this + 65) = 0;
  *((_DWORD *)this + 64) = 0;
  *((_DWORD *)this + 68) = 0;
  *((_DWORD *)this + 67) = 0;
  *((_DWORD *)this + 66) = 0;
  *((_BYTE *)this + 240) = 0;
  *((_DWORD *)this + 61) = 98;
  *((_DWORD *)this + 72) = 0;
  return this->_pad_000;
}

// 0x00439130
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_9130()
{
  *(_DWORD *)this->_pad_000 = &off_56AC20;
  sub_439810((int)this);
  `eh vector destructor iterator'((char *)this + 72, 0x20u, 5, nullsub_3);
  this->_UIWnd();
}

// 0x0043A160
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_A160()
{
  this->UIWnd();
  ((UIWnd *)((char *)this + 76))->DestroyChildren();
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 37) = 0;
  *(_DWORD *)this->_pad_000 = &off_56AC4C;
  *((_DWORD *)this + 17) = 1092616192;
  *((_DWORD *)this + 39) = -1;
}

// 0x0043A1F0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_A1F0()
{
  *(_DWORD *)this->_pad_000 = &off_56AC4C;
  ((PalScript *)this)->Reset();
  ((j_UIWnd *)(UIWnd **)this + 19)->MoveWindow();
  this->_UIWnd();
}

// 0x0043BB70
_DWORD * UIWnd::ctor_BB70()
{
  this->UIWnd();
  *(_DWORD *)this->_pad_000 = &off_56ACB8;
  *((_DWORD *)this + 17) = 0;
  return this->_pad_000;
}

// 0x0043BBB0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_BBB0()
{
  *(_DWORD *)this->_pad_000 = &off_56ACB8;
  this->_UIWnd();
}

// 0x0043BCE0
// write access to const memory has been detected, the output may be wrong!
_DWORD * UIWnd::ctor_BCE0()
{
  this->UIWnd();
  *((_DWORD *)this + 23) = 32;
  *((_DWORD *)this + 24) = 32;
  *((_DWORD *)this + 59) = 0x40000000;
  *((_DWORD *)this + 25) = 0;
  *((_BYTE *)this + 104) = 0;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 51) = 0;
  *((_DWORD *)this + 53) = 0;
  *((_DWORD *)this + 55) = 0;
  *((_DWORD *)this + 56) = 0;
  *((_DWORD *)this + 57) = 0;
  *((_DWORD *)this + 58) = 0;
  *((_DWORD *)this + 60) = 0;
  *((_DWORD *)this + 62) = 0;
  *((_DWORD *)this + 63) = 0;
  *((_DWORD *)this + 64) = 0;
  *((_DWORD *)this + 65) = 0;
  *((_DWORD *)this + 66) = 0;
  *((_DWORD *)this + 67) = 0;
  *(_DWORD *)this->_pad_000 = &off_56ACD8;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 47) = 0;
  *((_BYTE *)this + 170) = 0;
  *((_BYTE *)this + 169) = 0;
  *((_BYTE *)this + 168) = -1;
  *((_BYTE *)this + 171) = -1;
  *((_BYTE *)this + 174) = -1;
  *((_BYTE *)this + 173) = -1;
  *((_BYTE *)this + 172) = -1;
  *((_BYTE *)this + 175) = -1;
  gbColorQuad::ColorQuadFmt = 1;
  *((_BYTE *)this + 178) = -1;
  *((_BYTE *)this + 177) = 0;
  *((_BYTE *)this + 176) = 0;
  *((_BYTE *)this + 179) = -1;
  *((_DWORD *)this + 28) = 0;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 61) = 0;
  *((_DWORD *)this + 52) = 0;
  *((_DWORD *)this + 54) = 0;
  *((_DWORD *)this + 48) = 0;
  *((_DWORD *)this + 49) = 0;
  *((_DWORD *)this + 50) = 0;
  return this->_pad_000;
}

// 0x0043BE30
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56ACD8;
  sub_43BE80((gbRefObject **)this);
  this->_UIWnd();
}

// 0x0043D830
_DWORD * UIWnd::ctor_D830()
{
  this->UIWnd();
  *(_DWORD *)this->_pad_000 = &off_56ACFC;
  *((_DWORD *)this + 20) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 17) = 32;
  *((_DWORD *)this + 18) = 32;
  return this->_pad_000;
}

// 0x0043D880
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_D880()
{
  *(_DWORD *)this->_pad_000 = &off_56ACFC;
  this->_UIWnd();
}

// 0x0043DD10
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56AD20;
  ((UIListBox *)this)->SetScrollPos();
  this->_UIWnd();
}

// 0x0043F560
int UIWnd::CreateChild()
{
  int v1; // edx

  if ( *((int *)this + 108) <= 0 )
    return -1;
  v1 = *((_DWORD *)this + 280);
  if ( v1 == -1 )
    return -1;
  else
    return v1 + *((_DWORD *)this + 279);
}

// 0x0043F7F0
// write access to const memory has been detected, the output may be wrong!
_DWORD * UIWnd::ctor_F7F0()
{
  int v2; // ecx

  this->UIWnd();
  *((_DWORD *)this + 17) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 27) = 0;
  *((_DWORD *)this + 28) = 1065353216;
  *((_DWORD *)this + 29) = 0;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 33) = 0x40000000;
  *((_DWORD *)this + 34) = 0;
  *((_DWORD *)this + 35) = 0;
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 37) = 0;
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_BYTE *)this + 160) = 0;
  *((_DWORD *)this + 43) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 47) = 0;
  *((_DWORD *)this + 49) = 0;
  *((_DWORD *)this + 50) = 0;
  *((_DWORD *)this + 51) = 0;
  *((_DWORD *)this + 52) = 0;
  *(_DWORD *)this->_pad_000 = &off_56AD64;
  *((_BYTE *)this + 166) = -1;
  *((_BYTE *)this + 165) = -1;
  *((_BYTE *)this + 164) = -1;
  *((_BYTE *)this + 167) = -1;
  gbColorQuad::ColorQuadFmt = 1;
  *((_BYTE *)this + 170) = -1;
  *((_BYTE *)this + 169) = 0;
  *((_BYTE *)this + 168) = 0;
  *((_BYTE *)this + 171) = -1;
  *((_DWORD *)this + 53) = 0;
  *((_DWORD *)this + 58) = 1065353216;
  *((_BYTE *)this + 236) = 0;
  *((_BYTE *)this + 237) = 0;
  *((_BYTE *)this + 238) = 0;
  *((_DWORD *)this + 57) = 6;
  *((_DWORD *)this + 54) = -1;
  v2 = *((unsigned __int8 *)this + 219);
  *((_DWORD *)this + 44) = 0;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 48) = 0;
  *((_DWORD *)this + 56) = v2;
  *((_DWORD *)this + 55) = v2;
  *((_DWORD *)this + 60) = -1;
  return this->_pad_000;
}

// 0x0043F970
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56AD64;
  sub_43F9C0((gbRefObject **)this);
  this->_UIWnd();
}

// 0x0043FA00
void UIWnd::GetChildCount(LPCSTR lpString, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  Scene *v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString;
  if ( lpString )
  {
    v5 = (gbRefObject *)*((_DWORD *)this + 43);
    if ( v5 )
      v5->Release();
    ((OpenBaseFile *)&lpString)->OpenBaseFile();
    v6 = a3 == 0;
    *((_DWORD *)this + 44) = 0;
    if ( v6 )
    {
      *((_DWORD *)this + 43) = (UIWnd *)(*(int (**)(gbGfxManager *, const CHAR *))(*(_DWORD *)dword_BFDA60->_pad_0000
                                                                                  + 8))(
                                dword_BFDA60,
                                v3);
    }
    else
    {
      v7 = *(_DWORD *)dword_BFDA60->_pad_0000;
      v8 = ((_Texture_Info *)dword_1894B78)->_CalculateUV(v3);
      *((_DWORD *)this + 43) = (UIWnd *)(*(int (**)(gbGfxManager *, Scene *))(v7 + 8))(dword_BFDA60, v8);
      *((_DWORD *)this + 44) = (UIWnd *)((Parent_Data *)dword_1894B78)->Parent_Data(v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 43);
    if ( v9 )
      v9->LoadTexture(1);
    ((OpenNULLFile *)&lpString)->OpenNULLFile();
  }
}

// 0x0043FAE0
void UIWnd::GetChildAt(LPCSTR lpString, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  Scene *v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString;
  if ( lpString )
  {
    v5 = (gbRefObject *)*((_DWORD *)this + 45);
    if ( v5 )
      v5->Release();
    ((OpenBaseFile *)&lpString)->OpenBaseFile();
    v6 = a3 == 0;
    *((_DWORD *)this + 46) = 0;
    if ( v6 )
    {
      *((_DWORD *)this + 45) = (UIWnd *)(*(int (**)(gbGfxManager *, const CHAR *))(*(_DWORD *)dword_BFDA60->_pad_0000
                                                                                  + 8))(
                                dword_BFDA60,
                                v3);
    }
    else
    {
      v7 = *(_DWORD *)dword_BFDA60->_pad_0000;
      v8 = ((_Texture_Info *)dword_1894B78)->_CalculateUV(v3);
      *((_DWORD *)this + 45) = (UIWnd *)(*(int (**)(gbGfxManager *, Scene *))(v7 + 8))(dword_BFDA60, v8);
      *((_DWORD *)this + 46) = (UIWnd *)((Parent_Data *)dword_1894B78)->Parent_Data(v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 45);
    if ( v9 )
      v9->LoadTexture(1);
    ((OpenNULLFile *)&lpString)->OpenNULLFile();
  }
}

// 0x0043FCA0
void UIWnd::FindChild(float a2)
{
  int v2; // eax
  double v3; // st7
  double v4; // st6

  *((float *)this + 31) = a2;
  if ( a2 >= 0.0 )
  {
    v2 = *((_DWORD *)this + 17);
    if ( v2 )
    {
      if ( v2 != 1 )
      {
LABEL_7:
        *((float *)this + 32) = *((float *)this + 30) / a2;
        *((float *)this + 38) = a2 / *((float *)this + 30);
        return;
      }
      v3 = (double)*(int *)&this->m_rect[12] - *((float *)this + 37) - *((float *)this + 33);
      v4 = (double)*(int *)&this->m_rect[4] + *((float *)this + 36);
    }
    else
    {
      v3 = (double)*(int *)&this->m_rect[8] - *((float *)this + 35) - *((float *)this + 33);
      v4 = (double)*(int *)this->m_rect + *((float *)this + 34);
    }
    *((float *)this + 30) = v3 - (v4 + *((float *)this + 33));
    goto LABEL_7;
  }
}

// 0x0043FDB0
void UIWnd::SetFrameRate(int a2)
{
  *((float *)this + 34) = (float)a2;
}

// 0x0043FDC0
void UIWnd::GetWidth(int a2)
{
  *((float *)this + 35) = (float)a2;
}

// 0x0043FDD0
void UIWnd::GetHeight(int a2)
{
  *((float *)this + 36) = (float)a2;
}

// 0x0043FDE0
void UIWnd::GetPosition(int a2)
{
  *((float *)this + 37) = (float)a2;
}

// 0x0043FDF0
void UIWnd::FindChildByName(float a2)
{
  double v2; // st7
  double v3; // st6

  if ( *((float *)this + 31) > 0.0 )
  {
    v2 = a2;
    if ( a2 < 0.0 )
      v2 = 0.0;
    if ( v2 > *((float *)this + 31) )
      v2 = *((float *)this + 31);
    v3 = v2 * *((float *)this + 32);
    *((float *)this + 29) = v3;
    if ( v3 >= *((float *)this + 30) )
      *((_DWORD *)this + 29) = *((_DWORD *)this + 30);
    *((float *)this + 39) = *((float *)this + 38) * *((float *)this + 27);
    if ( v2 > (double)*((int *)this + 60) )
    {
      *((_BYTE *)this + 238) = 1;
    }
    else
    {
      *((_BYTE *)this + 237) = 1;
      *((_BYTE *)this + 238) = 0;
    }
    *((_BYTE *)this + 160) = 0;
  }
}

// 0x0043FEC0
int UIWnd::AddChild(_DWORD *a2)
{
  UIWnd *v2; // edx
  char *m_rect; // ecx
  int result; // eax

  v2 = (UIWnd *)((char *)this + 76);
  m_rect = (char *)this->m_rect;
  *(_DWORD *)v2->_pad_000 = *a2;
  *(_DWORD *)v2->m_fontcolor = a2[1];
  *(_DWORD *)v2->m_wndcolor = a2[2];
  v2->m_id = a2[3];
  *(_DWORD *)m_rect = *a2;
  *((_DWORD *)m_rect + 1) = a2[1];
  *((_DWORD *)m_rect + 2) = a2[2];
  result = a2[3];
  *((_DWORD *)m_rect + 3) = result;
  return result;
}

// 0x004407C0
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56AD88;
  ((UIStatic *)this)->OnMessage();
  this->_UIWnd();
}

// 0x004410F0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_DWORD * UIWnd::ctor_10F0()
{
  this->UIWnd();
  ((UIWnd *)((char *)this + 72))->ctor_D830();
  ((UIWnd *)((char *)this + 192))->DestroyChildren();
  *(_DWORD *)this->_pad_000 = &off_56ADAC;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 42) = 100;
  *((_DWORD *)this + 43) = 0;
  *((_DWORD *)this + 40) = 5;
  *((_BYTE *)this + 68) = 0;
  *((_BYTE *)this + 69) = 0;
  *((_DWORD *)this + 47) = 10;
  *((_DWORD *)this + 39) = 16;
  *((_DWORD *)this + 44) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 75) = 0;
  *((_DWORD *)this + 84) = 0;
  memset((char *)this + 260, 0, 0x28u);
  return this->_pad_000;
}

// 0x004411D0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_11D0()
{
  *(_DWORD *)this->_pad_000 = &off_56ADAC;
  sub_4414D0((UIWnd **)this);
  ((j_UIWnd *)(UIWnd **)this + 48)->MoveWindow();
  ((UIWnd *)((char *)this + 72))->ctor_D880();
  this->_UIWnd();
}

// 0x004426B0
void UIWnd::CreateFromTemplate(LPCSTR lpString1, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  char v6; // al
  int v7; // ebx
  Scene *v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString1;
  if ( lpString1 )
  {
    v5 = (gbRefObject *)*((_DWORD *)this + 28);
    if ( v5 )
      v5->Release();
    ((OpenBaseFile *)&lpString1)->OpenBaseFile();
    lstrcmpA(v3, String2);
    v6 = a3;
    *((_DWORD *)this + 29) = 0;
    if ( v6 )
    {
      v7 = *(_DWORD *)dword_BFDA60->_pad_0000;
      v8 = ((_Texture_Info *)dword_1894B78)->_CalculateUV(v3);
      *((_DWORD *)this + 28) = (UIWnd *)(*(int (**)(gbGfxManager *, Scene *))(v7 + 8))(dword_BFDA60, v8);
      *((_DWORD *)this + 29) = (UIWnd *)((Parent_Data *)dword_1894B78)->Parent_Data(v3);
    }
    else
    {
      *((_DWORD *)this + 28) = (UIWnd *)(*(int (**)(gbGfxManager *, const CHAR *))(*(_DWORD *)dword_BFDA60->_pad_0000
                                                                                  + 8))(
                                dword_BFDA60,
                                v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 28);
    if ( v9 )
      v9->LoadTexture(1);
    if ( !lstrcmpA(v3, String2) )
      unk_D90D3C = *((_DWORD *)this + 28);
    ((OpenNULLFile *)&lpString1)->OpenNULLFile();
  }
}

// 0x004427A0
int UIWnd::SetShow(int a2)
{
  int result; // eax

  result = a2;
  if ( a2 )
    *((_DWORD *)this + 23) = 2;
  else
    *((_DWORD *)this + 23) = 1;
  return result;
}

// 0x004427C0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::SetEnable(const char *a2, int a3)
{
  char *v3; // ebp
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  int v6; // ecx
  char v7; // al
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // [esp-8h] [ebp-14h]

  if ( a2 )
  {
    v3 = (char *)this + 96;
    v4 = strlen(a2) + 1;
    v5 = v4 - 1;
    if ( v4 - 1 > 0xFFFFFFFD )
      v10->_Xlen();
    v6 = *((_DWORD *)v3 + 1);
    if ( v6 && (v7 = *(_BYTE *)(v6 - 1)) != 0 && v7 != -1 )
    {
      if ( v4 == 1 )
      {
        *(_BYTE *)(v6 - 1) = v7 - 1;
        *((_DWORD *)v3 + 1) = 0;
        *((_DWORD *)v3 + 2) = 0;
        *((_DWORD *)v3 + 3) = 0;
        goto LABEL_16;
      }
    }
    else
    {
      if ( v4 == 1 )
      {
        v3->string::_Tidy(1);
        goto LABEL_16;
      }
      v8 = *((_DWORD *)v3 + 3);
      if ( v8 <= 0x1F && v8 >= v5 )
      {
LABEL_15:
        qmemcpy(*((void **)v3 + 1), a2, v5);
        v9 = *((_DWORD *)v3 + 1);
        *((_DWORD *)v3 + 2) = v5;
        *(_BYTE *)(v9 + v5) = 0;
LABEL_16:
        if ( a3 )
          *((_DWORD *)this + 18) = 1;
        else
          *((_DWORD *)this + 18) = 0;
        return;
      }
      v3->string::_Tidy(1);
    }
    ((GRPinput *)v3)->GetKeyState(v5);
    goto LABEL_15;
  }
}

// 0x00442E10
void UIWnd::ctor_2E10()
{
  ((UIFrameWnd *)this)->UIFrameWnd();
  *((_DWORD *)this + 41) = 1056964608;
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 42) = 0;
  *((_BYTE *)this + 172) = 0;
  *((_DWORD *)this + 44) = 0;
  *(_DWORD *)this->_pad_000 = &off_56AE10;
  *((_DWORD *)this + 36) = 21;
}

// 0x00442E80
void UIWnd::ctor_2E80()
{
  *(_DWORD *)this->_pad_000 = &off_56AE10;
  ((UIFrameWnd *)this)->_UIFrameWnd();
}

// 0x00443550
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56AE64;
  sub_4438F0((int)this);
  this->_UIWnd();
}

// 0x00445920
int UIWnd::Reset()
{
  return ((UIWnd *)(UIWnd **)this + 26)->MoveWindow();
}

// 0x00445930
int UIWnd::SetState(int state)
{
  int result; // eax

  result = state;
  *((_DWORD *)this + 47) = state;
  if ( state )
  {
    *((_DWORD *)this + 43) = 2;
    *((_DWORD *)this + 22) = *(_DWORD *)this->m_rect;
    *((_DWORD *)this + 23) = *(_DWORD *)&this->m_rect[4];
    *((_DWORD *)this + 24) = *(_DWORD *)&this->m_rect[8];
    result = *(_DWORD *)&this->m_rect[12];
    *((_DWORD *)this + 25) = result;
  }
  return result;
}

// 0x00445AA0
UIWnd::UIWnd()
{
  int v3; // [esp+4h] [ebp-4h]

  ((PtrArray *)this->m_childs)->Clear();
  *(_DWORD *)this->_pad_000 = &off_56AEC8;
  this->m_id = -1;
  *(_DWORD *)this->m_rect = 0;
  *(_DWORD *)&this->m_rect[4] = 0;
  *(_DWORD *)&this->m_rect[8] = 0;
  *(_DWORD *)&this->m_rect[12] = 0;
  this->m_pfather = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  this->m_benable = 0;
  this->m_bfocus = 0;
  if ( gbColorQuad::ColorQuadFmt )
  {
    BYTE2(v3) = 0;
    LOWORD(v3) = 1285;
  }
  else
  {
    LOBYTE(v3) = 0;
    *(_WORD *)((char *)&v3 + 1) = 1285;
  }
  HIBYTE(v3) = -1;
  *(_DWORD *)this->m_fontcolor = v3;
  *(_DWORD *)this->m_wndcolor = -1;
  this->_pad_000;
}

// 0x00445B40
void UIWnd::_UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56AEC8;
  this->UpdateChildren();
  sub_432680((void **)this->m_childs);
}

// 0x00445B90
int UIWnd::Create(int id, void *pRect, int parent)
{
  this->m_id = id;
  *(_DWORD *)this->m_rect = *(_DWORD *)pRect;
  *(_DWORD *)&this->m_rect[4] = *((_DWORD *)pRect + 1);
  *(_DWORD *)&this->m_rect[8] = *((_DWORD *)pRect + 2);
  *(_DWORD *)&this->m_rect[12] = *((_DWORD *)pRect + 3);
  this->m_pfather = (UIWnd *)parent;
  if ( parent )
  {
    sub_445BF0((int *)parent, (int)this);
    sub_445E10(this->m_pfather->_pad_000, this->m_rect);
  }
  this->m_bcreateok = 1;
  this->m_bvisible = 1;
  this->m_benable = 1;
  return 1;
}

// 0x00445C10
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::UpdateChildren()
{
  int v2; // edi
  int v3; // ecx

  v2 = 0;
  this->m_bcreateok = 0;
  this->m_bvisible = 0;
  for ( this->m_benable = 0; v2 < *(_DWORD *)&this->m_childs[4]; ++v2 )
  {
    v3 = *(_DWORD *)(*(_DWORD *)this->m_childs + 4 * v2);
    (*(void (**)(int))(*(_DWORD *)v3 + 12))(v3);
  }
  String_Assign_4326A0(this->m_childs, 0, -1);
}

// 0x00445C60
BOOL UIWnd::HitTest(int a2, int a3)
{
  int v5; // edi
  int v6; // esi
  int v7; // ecx

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
    return 0;
  v5 = *(_DWORD *)&this->m_childs[4] - 1;
  if ( v5 < 0 )
    return a3 == 0;
  v6 = a3;
  do
  {
    v7 = *(_DWORD *)(*(_DWORD *)this->m_childs + 4 * v5);
    if ( (*(int (**)(int, int, int))(*(_DWORD *)v7 + 8))(v7, a2, v6) )
      v6 = 0;
    --v5;
  }
  while ( v5 >= 0 );
  return v6 == 0;
}

// 0x00445CD0
int UIWnd::GetID()
{
  int result; // eax
  int i; // esi
  _DWORD *v4; // ecx

  result = this->m_bvisible;
  if ( result )
  {
    result = *(_DWORD *)&this->m_childs[4];
    for ( i = 0; i < result; ++i )
    {
      v4 = (_DWORD *)*(_DWORD **)(*(_DWORD *)this->m_childs + 4 * i);
      if ( v4[14] )
        (*(void (**)(_DWORD *))(*v4 + 4))(v4);
      result = *(_DWORD *)&this->m_childs[4];
    }
  }
  return result;
}

// 0x00445D10
int UIWnd::SendMessage(int a1, int a2, int a3)
{
  return 0;
}

// 0x00445D20
int UIWnd::ScreenToClient(int a2, int a3)
{
  return this->ClientToScreen(a2 - *(_DWORD *)this->m_rect, a3 - *(_DWORD *)&this->m_rect[4]);
}

// 0x00445D40
int UIWnd::ClientToScreen(int a2, int a3)
{
  int v4; // ebp
  int v5; // edi
  int v6; // edx
  int v7; // ecx
  int result; // eax
  int i; // edi

  v4 = *(_DWORD *)this->m_rect;
  v5 = *(_DWORD *)&this->m_rect[8];
  v6 = *(_DWORD *)&this->m_rect[4];
  v7 = *(_DWORD *)&this->m_rect[12];
  *(_DWORD *)this->m_rect = a2 + v4;
  *(_DWORD *)&this->m_rect[8] = a2 + v5;
  *(_DWORD *)&this->m_rect[4] = a3 + v6;
  *(_DWORD *)&this->m_rect[12] = a3 + v7;
  if ( this )
    (*(void (**)(UIWnd *, int, _DWORD, _DWORD))(*(_DWORD *)this->_pad_000 + 24))(this, 1022, 0, 0);
  result = *(_DWORD *)&this->m_childs[4];
  for ( i = 0; i < result; ++i )
  {
    ((UIWnd *)*(UIWnd **)(*(_DWORD *)this->m_childs + 4 * i))->ClientToScreen(a2, a3);
    result = *(_DWORD *)&this->m_childs[4];
  }
  return result;
}

// 0x00445DB0
int UIWnd::SetVisible(int bVisible)
{
  int v2; // ebx
  int v3; // edx
  int v4; // esi
  int v5; // edi

  if ( bVisible )
  {
    v4 = *(_DWORD *)(bVisible + 16);
    v5 = *(_DWORD *)(bVisible + 20);
    v2 = *(_DWORD *)(bVisible + 24);
    v3 = *(_DWORD *)(bVisible + 28);
  }
  else
  {
    v2 = dword_BFD6D0;
    v3 = dword_BFD6D4;
    v4 = 0;
    v5 = 0;
  }
  return this->ScreenToClient(v4 + (v2 + *(_DWORD *)this->m_rect - *(_DWORD *)&this->m_rect[8] - v4) / 2, v5 + (v3 + *(_DWORD *)&this->m_rect[4] - *(_DWORD *)&this->m_rect[12] - v5) / 2);
}

// 0x00445E70
int UIWnd::Destroy(int a2)
{
  int result; // eax
  int v3; // edx

  result = this->m_bcreateok;
  if ( result )
  {
    result = a2;
    if ( this->m_bvisible != a2 )
    {
      v3 = *(_DWORD *)this->_pad_000;
      this->m_bvisible = a2;
      return (*(int (__stdcall **)(int, int, _DWORD))(v3 + 24))(1000, a2, 0);
    }
  }
  return result;
}

// 0x00445EA0
void * UIWnd::DestroyChildren()
{
  memset(this, 0, sizeof(UIWnd));
  return this;
}

// 0x00445F20
int UIWnd::MoveWindow()
{
  int v2; // esi
  UIWnd **v3; // ebx

  v2 = 0;
  if ( (int)*((_DWORD *)this + 16) > 0 )
  {
    v3 = this;
    do
    {
      ((gbRefObject *)*v3)->Release();
      ++v2;
      ++v3;
    }
    while ( v2 < (int)*((_DWORD *)this + 16) );
  }
  memset(this, 0, 0x44u);
  return 0;
}

// 0x00445FA0
int UIWnd::GetRect(_DWORD *a2)
{
  int result; // eax

  result = (int)this->m_rect;
  *(_DWORD *)this->m_rect = *a2;
  *(_DWORD *)&this->m_rect[4] = a2[1];
  *(_DWORD *)&this->m_rect[8] = a2[2];
  *(_DWORD *)&this->m_rect[12] = a2[3];
  if ( this )
    return (*(int (**)(UIWnd *, int, _DWORD, _DWORD))(*(_DWORD *)this->_pad_000 + 24))(this, 1022, 0, 0);
  return result;
}

// 0x00445FE0
_DWORD * UIWnd::SetRect(_DWORD *a2)
{
  char *m_rect; // ecx

  m_rect = (char *)this->m_rect;
  * a2 = (*)*(_DWORD *)m_rect;
  a2[1] = *((_DWORD *)m_rect + 1);
  a2[2] = *((_DWORD *)m_rect + 2);
  a2[3] = *((_DWORD *)m_rect + 3);
  return a2;
}

// 0x00446010
int UIWnd::GetChild(int id)
{
  *(_DWORD *)this->m_fontcolor = *(_DWORD *)id;
  return id;
}

// 0x004460D0
_DWORD * UIWnd::ctor_60D0()
{
  ((UIListBox *)this)->UIListBox();
  sub_4434C0((UIWnd *)((char *)this + 360));
  `eh vector constructor iterator'(
    (char *)this + 512,
    0x1DCu,
    38,
    (void (*)(void *))sub_4461B0,
    (void (*)(void *))sub_4461F0);
  ((UIWnd *)((char *)this + 18616))->ctor_A160();
  *((_DWORD *)this + 4709) = 38;
  ((UIItem *)(UIItem *)this + 18840)->Refresh();
  ((UIItem *)(UIItem *)this + 20208)->Refresh();
  ctor_0x431870((_DWORD *)this + 5394);
  *(_DWORD *)this->_pad_000 = &off_56AF80;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 20) = 800;
  *((_DWORD *)this + 21) = 600;
  return this->_pad_000;
}

// 0x00446200
void UIWnd::ctor_6200()
{
  *(_DWORD *)this->_pad_000 = &off_56AF80;
  ((UIListBox *)this)->SetScrollPos();
  PalScript_Cleanup((PalScript *)((char *)this + 21576));
  ((UIItem *)(UIItem *)this + 20208)->UIItem();
  ((UIItem *)(UIItem *)this + 18840)->UIItem();
  ((UIWnd *)((char *)this + 18616))->ctor_A1F0();
  `eh vector destructor iterator'((char *)this + 512, 0x1DCu, 38, (void (*)(void *))sub_4461F0);
  ((UIWnd *)((char *)this + 360))->~UIWnd();
  this->~UIWnd();
}

// 0x0044A540
int UIWnd::ctor_A540(int a2, int a3, int a4)
{
  int v6; // esi
  int *v7; // eax
  char Destination[253]; // [esp+4h] [ebp-200h] BYREF
  __int16 v9; // [esp+101h] [ebp-103h]
  char v10; // [esp+103h] [ebp-101h]
  char Buffer[253]; // [esp+104h] [ebp-100h] BYREF
  __int16 v12; // [esp+201h] [ebp-3h]
  char v13; // [esp+203h] [ebp-1h]

  if ( a2 == 1000 )
  {
    if ( a3 )
    {
      *((_DWORD *)this + 4709) = -1;
      sub_44A3D0((int)this);
    }
    return 1;
  }
  else
  {
    if ( a2 != 1001 )
      return a2->SendMessage(a3, a4);
    v6 = 0;
    v7 = (int *)&dword_56AEE8;
    while ( a3 != *v7 )
    {
      ++v7;
      ++v6;
      if ( (int)v7 >= (int)&off_56AF80 )
        return 1;
    }
    if ( !*((_BYTE *)this + 18824) )
    {
      memset(Destination, 0, sizeof(Destination));
      v9 = 0;
      v10 = 0;
      ((PalScript *)((char *)this + 21576))->SetDirectory(&aQ07[64 * v6]);
      Script_Method_431C10((PalScript *)((char *)this + 21576), aDefault, Destination, 256);
      if ( !*((_BYTE *)this + 476 * v6 + 596) )
      {
        sprintf((char *const)this + 104, "%s%s%s", byte_DDB03C, Destination, byte_DDB13C);
        ((UIWnd *)((char *)this + 20664))->SetEnable((const char *)this + 104, 1);
        UIWnd_SetByte((UIWnd *)((char *)this + 20208), 1);
        return 1;
      }
      sprintf((char *const)this + 104, "%s%s%s", byte_DD953C, Destination, byte_DD963C);
      memset(Buffer, 0, sizeof(Buffer));
      v12 = 0;
      v13 = 0;
      sprintf(Buffer, "%s", (const char *)this + 104);
      ((UIWnd *)((char *)this + 19296))->SetEnable(Buffer, 1);
      UIWnd_SetByte((UIWnd *)((char *)this + 18840), 1);
      *((_DWORD *)this + 4709) = v6;
    }
    return 1;
  }
}

// 0x0044AB90
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_AB90()
{
  this->UIWnd();
  *((_DWORD *)this + 27) = 360;
  *((_DWORD *)this + 28) = 136;
  ((UIFrameWnd *)((char *)this + 124))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 276))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 428,
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)(this + 13))->_UIScene();
  ((UIScene *)((char *)this + 1228))->_UIScene();
  ((UIScene *)((char *)this + 1572))->_UIScene();
  ((UIItem *)(UIItem *)this + 1916)->Refresh();
  *((_BYTE *)this + 3300) = 0;
  *((_DWORD *)this + 824) = 0;
  *((_DWORD *)this + 823) = 0;
  ((UIItem *)(UIItem *)this + 3308)->Refresh();
  ((UIItem *)(UIItem *)this + 4676)->Refresh();
  ((UIItem *)(UIItem *)this + 6044)->Refresh();
  sub_44B850((int)this + 7420);
  *(_DWORD *)this->_pad_000 = &off_56AFD4;
  *((_DWORD *)this + 29) = 90;
  *((_DWORD *)this + 30) = 24;
  return (int)this->_pad_000;
}

// 0x0044ACE0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_ACE0()
{
  *(_DWORD *)this->_pad_000 = &off_56AFD4;
  j_PalScript_Cleanup((PalScript *)((char *)this + 7420));
  ((UIItem *)(UIItem *)this + 6044)->UIItem();
  ((UIItem *)(UIItem *)this + 4676)->UIItem();
  ((UIItem *)(UIItem *)this + 3308)->UIItem();
  ((UIItem *)(UIItem *)this + 1916)->UIItem();
  ((UIScene *)((char *)this + 1572))->Destroy2();
  ((UIScene *)((char *)this + 1228))->Destroy2();
  ((UIScene *)(this + 13))->Destroy2();
  `eh vector destructor iterator'((char *)this + 428, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 276))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 124))->_UIFrameWnd();
  this->_UIWnd();
}

// 0x0044BA60
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_BA60()
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 512,
    0xD0u,
    22,
    (void (*)(void *))sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 5088,
    0xD0u,
    16,
    (void (*)(void *))sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 8416,
    0xD0u,
    10,
    (void (*)(void *))sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 10496))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 10648))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 150)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 10952))->UIFrameWnd();
  sub_443190((UIWnd *)((char *)this + 11116));
  sub_443190((UIWnd *)((char *)this + 11308));
  ((UIScene *)((char *)this + 11500))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 11844,
    0x10u,
    3,
    PtrArray_Init,
    (void (*)(void *))SafeDelete_44BD80);
  *((_DWORD *)this + 2875) = &off_56B018;
  ((UIScene *)((char *)this + 11892))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 12236,
    0x10u,
    3,
    PtrArray_Init,
    (void (*)(void *))SafeDelete_44BD80);
  *((_DWORD *)this + 2973) = &off_56B018;
  ((UIScene *)((char *)this + 12284))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 12628,
    0x10u,
    3,
    PtrArray_Init,
    (void (*)(void *))SafeDelete_44BD80);
  *((_DWORD *)this + 3071) = &off_56B018;
  ((UIScene *)((char *)this + 12676))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 13020,
    0x10u,
    3,
    PtrArray_Init,
    (void (*)(void *))SafeDelete_44BD80);
  *((_DWORD *)this + 3169) = &off_56B018;
  ((UIScene *)((char *)this + 13068))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 13412,
    0x10u,
    3,
    PtrArray_Init,
    (void (*)(void *))SafeDelete_44BD80);
  *((_DWORD *)this + 3267) = &off_56B018;
  ((UIScene *)((char *)this + 13460))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 13804,
    0x10u,
    3,
    PtrArray_Init,
    (void (*)(void *))SafeDelete_44BD80);
  *((_DWORD *)this + 3365) = &off_56B018;
  *((_DWORD *)this + 3467) = 0;
  *((_DWORD *)this + 3468) = 0;
  *((_DWORD *)this + 3469) = 0;
  *((_DWORD *)this + 3471) = 0;
  *((_BYTE *)this + 13892) = 1;
  *((_BYTE *)this + 13893) = 1;
  *((_BYTE *)this + 13894) = 0;
  ((UIFrameWnd *)((char *)this + 13904))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 14080))->UIFrameWnd();
  *(_DWORD *)this->_pad_000 = &off_56AFFC;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 20) = 800;
  *((_DWORD *)this + 21) = 600;
  *((_BYTE *)this + 13852) = 0;
  *((_BYTE *)this + 13853) = 0;
  *((_DWORD *)this + 3464) = 0;
  *((_DWORD *)this + 3465) = 0;
  *((_DWORD *)this + 3466) = 0;
  return (int)this->_pad_000;
}

// 0x0044BDA0
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56B018;
  `eh vector destructor iterator'((char *)this + 344, 0x10u, 3, (void (*)(void *))SafeDelete_44BD80);
  ((UIScene *)this)->Destroy2();
}

// 0x0044BE80
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_BE80()
{
  *(_DWORD *)this->_pad_000 = &off_56AFFC;
  sub_44C910((int)this);
  ((UIFrameWnd *)((char *)this + 14080))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 13904))->_UIFrameWnd();
  if ( *((_DWORD *)this + 3469) )
  {
    operator delete(*((void **)this + 3469));
    *((_DWORD *)this + 3469) = 0;
  }
  *((_DWORD *)this + 3365) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13804, 0x10u, 3, (void (*)(void *))SafeDelete_44BD80);
  ((UIScene *)((char *)this + 13460))->Destroy2();
  *((_DWORD *)this + 3267) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13412, 0x10u, 3, (void (*)(void *))SafeDelete_44BD80);
  ((UIScene *)((char *)this + 13068))->Destroy2();
  *((_DWORD *)this + 3169) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13020, 0x10u, 3, (void (*)(void *))SafeDelete_44BD80);
  ((UIScene *)((char *)this + 12676))->Destroy2();
  *((_DWORD *)this + 3071) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 12628, 0x10u, 3, (void (*)(void *))SafeDelete_44BD80);
  ((UIScene *)((char *)this + 12284))->Destroy2();
  *((_DWORD *)this + 2973) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 12236, 0x10u, 3, (void (*)(void *))SafeDelete_44BD80);
  ((UIScene *)((char *)this + 11892))->Destroy2();
  *((_DWORD *)this + 2875) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 11844, 0x10u, 3, (void (*)(void *))SafeDelete_44BD80);
  ((UIScene *)((char *)this + 11500))->Destroy2();
  sub_4431D0((UIWnd *)((char *)this + 11308));
  sub_4431D0((UIWnd *)((char *)this + 11116));
  ((UIFrameWnd *)((char *)this + 10952))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 150)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 10648))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 10496))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 8416,
    0xD0u,
    10,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'(
    (char *)this + 5088,
    0xD0u,
    16,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 512, 0xD0u, 22, (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->_UIFrameWnd();
  this->~UIWnd();
}

// 0x0044F050
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_F050()
{
  *(_DWORD *)this->_pad_000 = &off_56B094;
  ((CGameData *)this)->Destroy();
  `eh vector destructor iterator'((char *)this + 14544, 0x8E0u, 6, (void (*)(void *))sub_44E5E0);
  ((UIWnd *)((char *)this + 5012))->ctor_ACE0();
  sub_450EB0((int)this + 3904);
  `eh vector destructor iterator'((char *)this + 2144, 0x160u, 5, (void (*)(void *))sub_450390);
  sub_451900((int)this + 656);
  sub_450AD0((int)this + 356);
  sub_44A7F0((int)this + 260);
  this->_UIWnd();
}

// 0x0044FFE0
int UIWnd::ctor_FFE0()
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)((char *)this + 76))->UIFrameWnd();
  *(_DWORD *)this->_pad_000 = &off_56B0B4;
  *((_DWORD *)this + 18) = 0;
  *(_DWORD *)this->m_wndcolor = -1;
  return (int)this->_pad_000;
}

// 0x00450090
void UIWnd::ctor_90()
{
  *(_DWORD *)this->_pad_000 = &off_56B0B4;
  ((UIFrameWnd *)((char *)this + 76))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00450710
_DWORD * UIWnd::ctor_710()
{
  ((UIListBox *)this)->UIListBox();
  ((UIWnd *)((char *)this + 72))->ctor_F7F0();
  *(_DWORD *)this->_pad_000 = &off_56B100;
  *((_DWORD *)this + 81) = 1120403456;
  return this->_pad_000;
}

// 0x00450790
void UIWnd::ctor_790()
{
  *(_DWORD *)this->_pad_000 = &off_56B100;
  ((UIWnd *)((char *)this + 72))->~UIWnd();
  this->~UIWnd();
}

// 0x00451CC0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_1CC0()
{
  this->UIWnd();
  ((UIWnd *)this + 1)->ctor_F7F0();
  ((UIWnd *)((char *)this + 312))->ctor_F7F0();
  `eh vector constructor iterator'(
    (char *)this + 556,
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 1012))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 1172,
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)this->_pad_000 = &off_56B19C;
  *((_DWORD *)this + 292) = 0;
  return (int)this->_pad_000;
}

// 0x00451DA0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_1DA0()
{
  *(_DWORD *)this->_pad_000 = &off_56B19C;
  `eh vector destructor iterator'((char *)this + 1172, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 1012))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 556, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 312))->~UIWnd();
  ((UIWnd *)this + 1)->~UIWnd();
  this->_UIWnd();
}

// 0x00452600
void UIWnd::ctor_2600()
{
  *(_DWORD *)this->_pad_000 = &off_56B1BC;
  ((UIWnd *)((char *)this + 1084))->ctor_1DA0();
  ((UIWnd *)((char *)this + 72))->ctor_2850();
  this->~UIWnd();
}

// 0x00452790
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_2790()
{
  this->UIWnd();
  ((UIScene *)(this + 1))->_UIScene();
  ((UIFrameWnd *)((char *)this + 412))->UIFrameWnd();
  ((UIWnd *)((char *)this + 564))->ctor_2E10();
  UIWnd_Init_444F60(this + 11);
  ((UIWnd *)((char *)this + 940))->DestroyChildren();
  *(_DWORD *)this->_pad_000 = &off_56B1DC;
  *((_DWORD *)this + 252) = 0;
  return (int)this->_pad_000;
}

// 0x00452850
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_2850()
{
  *(_DWORD *)this->_pad_000 = &off_56B1DC;
  ((j_UIWnd *)(UIWnd **)this + 235)->MoveWindow();
  UIWnd_Destructor(this + 11);
  ((UIWnd *)((char *)this + 564))->ctor_2E80();
  ((UIFrameWnd *)((char *)this + 412))->_UIFrameWnd();
  ((UIScene *)(this + 1))->Destroy2();
  this->_UIWnd();
}

// 0x00452FD0
int UIWnd::ctor_2FD0()
{
  char v3; // [esp+7h] [ebp-1h]

  this->UIWnd();
  *((_BYTE *)this + 68) = v3;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 20) = 0;
  *((_BYTE *)this + 84) = v3;
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 23) = 0;
  *((_DWORD *)this + 24) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B200;
  *((_BYTE *)this + 100) = 1;
  return (int)this->_pad_000;
}

// 0x00453030
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_3030()
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al
  int v5; // eax
  _BYTE *v6; // ecx
  char v7; // al

  *(_DWORD *)this->_pad_000 = &off_56B200;
  v2 = *((_DWORD *)this + 22);
  if ( v2 )
  {
    v3 = (_BYTE *)(v2 - 1);
    v4 = *(_BYTE *)(v2 - 1);
    if ( !v4 || v4 == -1 )
      operator delete(v3);
    else
      * v3 = (*)v4 - 1;
  }
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 23) = 0;
  *((_DWORD *)this + 24) = 0;
  v5 = *((_DWORD *)this + 18);
  if ( v5 )
  {
    v6 = (_BYTE *)(v5 - 1);
    v7 = *(_BYTE *)(v5 - 1);
    if ( v7 && v7 != -1 )
    {
      * v6 = (*)v7 - 1;
      *((_DWORD *)this + 18) = 0;
      *((_DWORD *)this + 19) = 0;
      *((_DWORD *)this + 20) = 0;
      this->_UIWnd();
      return;
    }
    operator delete(v6);
  }
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 20) = 0;
  this->_UIWnd();
}

// 0x00453D10
int UIWnd::ctor_3D10()
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 512))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 664,
    0x178u,
    3,
    (void (*)(void *))sub_43B3E0,
    (void (*)(void *))sub_43B4D0);
  ((UIScene *)((char *)this + 1792))->_UIScene();
  ((UIFrameWnd *)((char *)this + 2136))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2288))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2440))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 36)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2744))->UIFrameWnd();
  ((UIScene *)((char *)this + 2896))->_UIScene();
  ((UIScene *)((char *)this + 3240))->_UIScene();
  ((UIScene *)((char *)this + 3584))->_UIScene();
  ((UIItem *)(UIItem *)this + 3928)->Refresh();
  *((_DWORD *)this + 1328) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B22C;
  *((_DWORD *)this + 20) = 800;
  *((_DWORD *)this + 21) = 600;
  return (int)this->_pad_000;
}

// 0x00453E70
void UIWnd::ctor_3E70()
{
  *(_DWORD *)this->_pad_000 = &off_56B22C;
  ((UIItem *)(UIItem *)this + 3928)->UIItem();
  ((UIScene *)((char *)this + 3584))->Destroy2();
  ((UIScene *)((char *)this + 3240))->Destroy2();
  ((UIScene *)((char *)this + 2896))->Destroy2();
  ((UIFrameWnd *)((char *)this + 2744))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 36)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2440))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2288))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2136))->_UIFrameWnd();
  ((UIScene *)((char *)this + 1792))->Destroy2();
  `eh vector destructor iterator'((char *)this + 664, 0x178u, 3, (void (*)(void *))sub_43B4D0);
  ((UIFrameWnd *)((char *)this + 512))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00454590
int UIWnd::ctor_4590(int a2, int a3, int a4)
{
  int v6; // ecx
  int *v7; // eax
  char *Instance; // eax
  int v9; // ecx
  char *v10; // eax
  int v11; // ecx
  int *v12; // eax
  int v13; // ecx
  int *v14; // edi
  void *v15; // [esp-8h] [ebp-10h]
  void *v16; // [esp-8h] [ebp-10h]
  int v17; // [esp-4h] [ebp-Ch]

  switch ( a2 )
  {
    case 1000:
      if ( a3 )
      {
        sub_4544F0(this);
        *((_BYTE *)this + 5308) = 0;
      }
      return 1;
    case 1001:
      v6 = 0;
      v7 = dword_56B220;
      do
      {
        if ( a3 == *v7 )
        {
          *((_DWORD *)this + 1326) = v6 + 1;
          v15 = off_5ABBE0;
          Instance = (char *)CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v15, 1);
          sub_454420((int)this, 1u);
          sub_4543C0((int)this, 0);
          return 1;
        }
        ++v7;
        ++v6;
      }
      while ( (int)v7 < (int)&off_56B22C );
      switch ( a3 )
      {
        case 193:
          sub_44C970(*((_DWORD **)this + 1328), 0);
          break;
        case -1431699013:
          v9 = *((_DWORD *)this + 1328);
          v17 = *((_DWORD *)this + 1326);
          *((_BYTE *)this + 5308) = 1;
          sub_44DB50(v9, v17);
          v16 = off_5ABBE0;
LABEL_16:
          v10 = (char *)CScreenMode::GetInstance();
          ((CScreenMode *)v10)->AudioSetPosition(v16, 1);
          return 1;
        case -1431698501:
          sub_454420((int)this, 0);
          sub_4543C0((int)this, 1u);
          break;
        default:
          return 1;
      }
      v16 = off_5ABBE0;
      goto LABEL_16;
    case 1002:
      v11 = 0;
      v12 = dword_56B220;
      while ( a3 != *v12 )
      {
        ++v12;
        ++v11;
        if ( (int)v12 >= (int)&off_56B22C )
          return 1;
      }
      if ( v11 )
      {
        v13 = v11 - 1;
        if ( v13 )
        {
          if ( v13 == 1 )
            sprintf((char *const)this + 104, "%s\\n%s\\n%s\\n%s", byte_DD313C, byte_DD323C, byte_DD333C, byte_DD343C);
        }
        else
        {
          sprintf((char *const)this + 104, "%s\\n%s\\n%s\\n%s", byte_DD2D3C, byte_DD2E3C, byte_DD2F3C, byte_DD303C);
        }
      }
      else
      {
        sprintf((char *const)this + 104, "%s\\n%s\\n%s", byte_DD2A3C, byte_DD2B3C, byte_DD2C3C);
      }
      ((UIWnd *)((char *)this + 512))->SetEnable((const char *)this + 104, 0);
      return 1;
    case 1003:
      v14 = dword_56B220;
      do
      {
        if ( a3 == *v14 )
          ((UIWnd *)((char *)this + 512))->SetEnable(g_SceneMgr.m_szUIString, 0);
        ++v14;
      }
      while ( (int)v14 < (int)&off_56B22C );
      return 1;
    default:
      return a2->SendMessage(a3, a4);
  }
}

// 0x00454830
int UIWnd::ctor_4830()
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->UIFrameWnd();
  ((UIScene *)((char *)this + 512))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 892,
    0xDE8u,
    36,
    (void (*)(void *))sub_4549A0,
    (void (*)(void *))sub_454AA0);
  ((UIFrameWnd *)((char *)this + 129052))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 129204))->UIFrameWnd();
  ((UIScene *)((char *)this + 129356))->_UIScene();
  ((UIScene *)((char *)this + 129700))->_UIScene();
  ((UIWnd *)((char *)this + 130060))->ctor_BCE0();
  *((_DWORD *)this + 32585) = 92;
  *((_DWORD *)this + 32586) = 610;
  *((_DWORD *)this + 32587) = 0;
  *((_DWORD *)this + 32588) = 0;
  *((_DWORD *)this + 32589) = 0;
  ((UIItem *)(UIItem *)this + 130364)->Refresh();
  ((UIItem *)(UIItem *)this + 131732)->Refresh();
  *((_DWORD *)this + 33275) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 32590) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B274;
  *((_DWORD *)this + 20) = 800;
  *((_DWORD *)this + 21) = 600;
  memset((char *)this + 856, 0, 0x24u);
  return (int)this->_pad_000;
}

// 0x00454BA0
void UIWnd::ctor_4BA0()
{
  *(_DWORD *)this->_pad_000 = &off_56B274;
  ((UIItem *)(UIItem *)this + 131732)->UIItem();
  ((UIItem *)(UIItem *)this + 130364)->UIItem();
  ((UIWnd *)((char *)this + 130060))->~UIWnd();
  ((UIScene *)((char *)this + 129700))->Destroy2();
  ((UIScene *)((char *)this + 129356))->Destroy2();
  ((UIFrameWnd *)((char *)this + 129204))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 129052))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 892, 0xDE8u, 36, (void (*)(void *))sub_454AA0);
  ((UIScene *)((char *)this + 512))->Destroy2();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00456AB0
int UIWnd::ctor_6AB0()
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 512,
    0x178u,
    52,
    (void (*)(void *))sub_43B3E0,
    (void (*)(void *))sub_43B4D0);
  ((UIScene *)((char *)this + 20064))->_UIScene();
  ((UIFrameWnd *)((char *)this + 20408))->UIFrameWnd();
  *((_DWORD *)this + 5141) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B364;
  *((_DWORD *)this + 20) = 800;
  *((_DWORD *)this + 21) = 600;
  return (int)this->_pad_000;
}

// 0x00456B80
void UIWnd::ctor_6B80()
{
  *(_DWORD *)this->_pad_000 = &off_56B364;
  ((UIFrameWnd *)((char *)this + 20408))->_UIFrameWnd();
  ((UIScene *)((char *)this + 20064))->Destroy2();
  `eh vector destructor iterator'((char *)this + 512, 0x178u, 52, (void (*)(void *))sub_43B4D0);
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00457070
int UIWnd::ctor_7070(int a2, int a3, int a4)
{
  int result; // eax
  int v6; // eax
  int *v7; // ecx
  char *Instance; // eax
  int Width; // eax
  int v10; // ecx
  int *v11; // eax
  int *v12; // eax
  void *v13; // [esp-8h] [ebp-10h]
  int v14; // [esp-4h] [ebp-Ch]

  switch ( a2 )
  {
    case 1000:
      if ( !a3 )
        goto LABEL_20;
      sub_456EE0(this->_pad_000);
      *((_BYTE *)this + 20560) = 0;
      result = 1;
      break;
    case 1001:
      v6 = 0;
      v7 = dword_56B294;
      do
      {
        if ( a3 == *v7 )
        {
          sprintf((char *const)this + 104, "Movie\\%s.bik", (const char *)(30 * v6 + 5967612));
          ((CScreenMode *)&unk_A3A7D8)->CreateDevice((int)this + 104, (int)dword_BFDA4C, 0, 0);
          v14 = (600 - ((CScreenMode *)&unk_A3A7D8)->GetHeight()) / 2;
          Width = ((CScreenMode *)&unk_A3A7D8)->GetWidth();
          ((CScreenMode *)&unk_A3A7D8)->SetViewport((800 - Width) / 2, v14);
          sub_456E20(this, 0);
          *((_BYTE *)this + 20560) = 1;
          return 1;
        }
        ++v7;
        ++v6;
      }
      while ( (int)v7 < (int)&off_56B364 );
      if ( a3 != 177 )
        goto LABEL_20;
      v13 = off_5B0DA4;
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
      sub_44C970(*((_DWORD **)this + 5141), 0);
      result = 1;
      break;
    case 1002:
      v10 = 0;
      v11 = dword_56B294;
      do
      {
        if ( a3 == *v11 )
        {
          ((UIWnd *)((char *)this + 20408))->SetEnable(&byte_DD553C[256 * v10], 0);
          goto LABEL_20;
        }
        ++v11;
        ++v10;
      }
      while ( (int)v11 < (int)&off_56B364 );
      result = 1;
      break;
    case 1003:
      v12 = dword_56B294;
      while ( a3 != *v12 )
      {
        if ( (int)++v12 >= (int)&off_56B364 )
          return 1;
      }
      ((UIWnd *)((char *)this + 20408))->SetEnable(g_SceneMgr.m_szUIString, 0);
LABEL_20:
      result = 1;
      break;
    default:
      result = a2->SendMessage(a3, a4);
      break;
  }
  return result;
}

// 0x004590D0
int UIWnd::ctor_90D0()
{
  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 30) = 800;
  *((_DWORD *)this + 31) = 64;
  *((_DWORD *)this + 34) = 360;
  *((_DWORD *)this + 35) = 136;
  *((_BYTE *)this + 152) = 0;
  ((UIFrameWnd *)((char *)this + 164))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 316))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 468,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)((char *)this + 1228))->_UIScene();
  ((UIScene *)((char *)this + 1572))->_UIScene();
  ((UIScene *)((char *)this + 1916))->_UIScene();
  ((UIScene *)((char *)this + 2260))->_UIScene();
  *((_BYTE *)this + 2604) = 0;
  ((UIScene *)((char *)this + 2608))->_UIScene();
  ((UIFrameWnd *)(UIFrameWnd *)this + 41)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 3104))->UIFrameWnd();
  *((_DWORD *)this + 814) = 0;
  *((_DWORD *)this + 815) = 0;
  *((_DWORD *)this + 816) = 0;
  *((_DWORD *)this + 817) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B394;
  *((_DWORD *)this + 28) = 88;
  *((_DWORD *)this + 29) = 138;
  *((_DWORD *)this + 32) = 90;
  *((_DWORD *)this + 33) = 24;
  *((_WORD *)this + 80) = 0;
  *((_DWORD *)this + 818) = 0;
  *((_BYTE *)this + 3284) = 1;
  return (int)this->_pad_000;
}

// 0x00459260
void UIWnd::ctor_9260()
{
  *(_DWORD *)this->_pad_000 = &off_56B394;
  sub_459360((int)this);
  ((UIFrameWnd *)((char *)this + 3104))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 41)->_UIFrameWnd();
  ((UIScene *)((char *)this + 2608))->Destroy2();
  ((UIScene *)((char *)this + 2260))->Destroy2();
  ((UIScene *)((char *)this + 1916))->Destroy2();
  ((UIScene *)((char *)this + 1572))->Destroy2();
  ((UIScene *)((char *)this + 1228))->Destroy2();
  `eh vector destructor iterator'((char *)this + 468, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 316))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x0045A7B0
int UIWnd::ctor_A7B0()
{
  UIWnd *v2; // eax
  _DWORD *v3; // ebp
  bool v4; // zf
  int v5; // kr00_4
  UIWnd *v7; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 18) = 800;
  *((_DWORD *)this + 19) = 600;
  *((_DWORD *)this + 84) = 0;
  *((_DWORD *)this + 85) = 0;
  *((_DWORD *)this + 88) = 0;
  *((_DWORD *)this + 89) = 0;
  *((_DWORD *)this + 90) = 0;
  *((_DWORD *)this + 91) = 0;
  *((_BYTE *)this + 368) = 0;
  *((_DWORD *)this + 93) = 1090519040;
  *((_WORD *)this + 189) = 0;
  *((_DWORD *)this + 3568) = 0;
  v8 = 5;
  *((_DWORD *)this + 3569) = 0;
  memset(this + 210, 0, 0x640u);
  memset((char *)this + 17480, 0, 0x190u);
  memset((char *)this + 15880, 0, 0x640u);
  v2 = (UIWnd *)this + 263;
  *((_DWORD *)this + 94) = 0;
  *((_DWORD *)this + 4470) = 0;
  v7 = (UIWnd *)this + 263;
  v3 = (_DWORD *)((char *)this + 18744);
  while ( 1 )
  {
    *(_DWORD *)v2->_pad_000 = 0;
    *((_WORD *)v3 - 428) = 0;
    lstrcpyA((LPSTR)v3 - 854, g_SceneMgr.m_szUIString);
    lstrcpyA((LPSTR)v3 - 342, g_SceneMgr.m_szUIString);
    lstrcpyA((LPSTR)v3 - 312, g_SceneMgr.m_szUIString);
    lstrcpyA((LPSTR)v3 - 260, g_SceneMgr.m_szUIString);
    memset(v3 - 56, 0, 0x30u);
    *(v3 - 20) = 0;
    *(v3 - 2) = 0xFFFF;
    *(v3 - 1) = 0;
    *v3 = 0;
    v3[1] = 0xFFFF;
    v3[2] = 0;
    v3[3] = 0;
    v3[4] = 0xFFFF;
    v3[5] = 0;
    v3[6] = 0;
    ArraySort((int)(v3 + 7), 12, 2, (int)exception::exception);
    v3[13] = 0xFFFF;
    v3[14] = 0;
    v3[15] = 0;
    memset(v7, 0, 0x580u);
    v3 += 352;
    v4 = v8 == 1;
    v7 = (UIWnd *)((char *)v7 + 1408);
    --v8;
    if ( v4 )
      break;
    v2 = v7;
  }
  ((UIFrameWnd *)((char *)this + 24940))->UIFrameWnd();
  ((UIWnd *)this + 369)->ctor_D830();
  ((UIFrameWnd *)((char *)this + 25176))->UIFrameWnd();
  ((UIWnd *)((char *)this + 25328))->ctor_A160();
  `eh vector constructor iterator'(
    (char *)this + 25492,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 26356,
    0x98u,
    240,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *((_DWORD *)this + 16729) = 0;
  `eh vector constructor iterator'(
    (char *)this + 71000,
    0x34u,
    240,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  `eh vector constructor iterator'(
    (char *)this + 83480,
    0xB4u,
    30,
    (void (*)(void *))sub_444A20,
    (void (*)(void *))UIFrameWnd_Destructor_444AC0);
  `eh vector constructor iterator'(
    (char *)this + 88880,
    0x98u,
    30,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *((_BYTE *)this + 93440) = 0;
  *((_BYTE *)this + 93471) = 0;
  *((_DWORD *)this + 23368) = 0;
  *((_DWORD *)this + 23399) = 0;
  *((_DWORD *)this + 23400) = 0;
  ((UIWnd *)((char *)this + 93616))->ctor_9030();
  ((UIItem *)(UIItem *)this + 93924)->Refresh();
  ((UIFrameWnd *)((char *)this + 95292))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 95444))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 95596))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 95748))->UIFrameWnd();
  ((UIScene *)((char *)this + 95916))->_UIScene();
  ((UIScene *)((char *)this + 96260))->_UIScene();
  ((UIFrameWnd *)((char *)this + 96604))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 96772))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 96924,
    0x98u,
    13,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 98900))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 99052))->UIFrameWnd();
  ((UIListBox *)((char *)this + 99204))->UpdateKeyCtrl();
  ((UIScene *)((char *)this + 100460))->_UIScene();
  ((UIScene *)((char *)this + 100804))->_UIScene();
  *((_DWORD *)this + 25287) = 32;
  *((_DWORD *)this + 25288) = 16;
  *((_DWORD *)this + 25289) = 0;
  *((_DWORD *)this + 25290) = 0;
  ((UIFrameWnd *)((char *)this + 101176))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 101328))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 101496))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 1412)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 101832))->UIFrameWnd();
  ((UIScene *)(this + 1500))->_UIScene();
  ((UIScene *)((char *)this + 102364))->_UIScene();
  ((UIScene *)((char *)this + 102724))->_UIScene();
  ((UIScene *)((char *)this + 103084))->_UIScene();
  ((UIScene *)((char *)this + 103444))->_UIScene();
  ((UIScene *)((char *)this + 103788))->_UIScene();
  ((UIScene *)((char *)this + 104132))->_UIScene();
  ((UIScene *)((char *)this + 104476))->_UIScene();
  ((UIScene *)((char *)this + 104820))->_UIScene();
  ((UIFrameWnd *)(this + 1547))->UIFrameWnd();
  *((_BYTE *)this + 105348) = 0;
  *((_BYTE *)this + 105349) = 0;
  *((_BYTE *)this + 105862) = 0;
  *((_DWORD *)this + 26466) = 0;
  *((_DWORD *)this + 26467) = -1;
  *((_DWORD *)this + 26468) = -1;
  *((_BYTE *)this + 105876) = 0;
  *((_DWORD *)this + 26470) = 0;
  *((_DWORD *)this + 26471) = 0;
  *((_DWORD *)this + 26473) = 0;
  *((_DWORD *)this + 26474) = 0;
  *((_BYTE *)this + 105900) = 0;
  *((_BYTE *)this + 105908) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B5CC;
  lstrcpyA((LPSTR)this + 105350, byte_DC333C);
  lstrcpyA((LPSTR)this + 105606, byte_DC343C);
  memset((char *)this + 376, 0, 0x4460u);
  memset(this + 263, 0, 0x580u);
  *((_BYTE *)this + 26348) = 1;
  *((_BYTE *)this + 26352) = 0;
  *((_BYTE *)this + 26351) = 0;
  *((_BYTE *)this + 26350) = 0;
  *((_BYTE *)this + 26349) = 0;
  memset((char *)this + 93441, 0, 0x1Cu);
  *(_WORD *)((char *)this + 93469) = 0;
  memset((char *)this + 93476, 0xFFu, 0x78u);
  memset((char *)this + 66676, 0, 0xF0u);
  memset((char *)this + 66920, 0, 0xF0u);
  *((_DWORD *)this + 23401) = 0;
  *((_DWORD *)this + 23402) = 0;
  *((_WORD *)this + 46806) = 0;
  v5 = *((_DWORD *)this + 19);
  *((_DWORD *)this + 6583) = 68;
  *((_DWORD *)this + 6584) = v5 / 4;
  *((_DWORD *)this + 6585) = 65;
  *((_DWORD *)this + 6586) = 86;
  *((_DWORD *)this + 26472) = 0;
  return (int)this->_pad_000;
}

// 0x0045AE60
void UIWnd::ctor_AE60()
{
  void *v2; // eax

  *(_DWORD *)this->_pad_000 = &off_56B5CC;
  v2 = (void *)*((_DWORD *)this + 23368);
  if ( v2 )
  {
    operator delete(v2);
    *((_DWORD *)this + 23368) = 0;
  }
  if ( *((_DWORD *)this + 23399) )
  {
    operator delete(*((void **)this + 23399));
    *((_DWORD *)this + 23399) = 0;
  }
  if ( *((_DWORD *)this + 85) )
  {
    operator delete(*((void **)this + 85));
    *((_DWORD *)this + 85) = 0;
  }
  if ( *((_DWORD *)this + 23400) )
  {
    operator delete(*((void **)this + 23400));
    *((_DWORD *)this + 23400) = 0;
  }
  *((_BYTE *)this + 368) = 0;
  *((_BYTE *)this + 105908) = 0;
  ((UIListBox *)this)->SetScrollPos();
  ((UIFrameWnd *)(this + 1547))->_UIFrameWnd();
  ((UIScene *)((char *)this + 104820))->Destroy2();
  ((UIScene *)((char *)this + 104476))->Destroy2();
  ((UIScene *)((char *)this + 104132))->Destroy2();
  ((UIScene *)((char *)this + 103788))->Destroy2();
  ((UIScene *)((char *)this + 103444))->Destroy2();
  ((UIScene *)((char *)this + 103084))->Destroy2();
  ((UIScene *)((char *)this + 102724))->Destroy2();
  ((UIScene *)((char *)this + 102364))->Destroy2();
  ((UIScene *)(this + 1500))->Destroy2();
  ((UIFrameWnd *)((char *)this + 101832))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 1412)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 101496))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 101328))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 101176))->_UIFrameWnd();
  ((UIScene *)((char *)this + 100804))->Destroy2();
  ((UIScene *)((char *)this + 100460))->Destroy2();
  ((UIListBox *)((char *)this + 99204))->DeleteRow();
  ((UIFrameWnd *)((char *)this + 99052))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 98900))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 96924, 0x98u, 13, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 96772))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 96604))->_UIFrameWnd();
  ((UIScene *)((char *)this + 96260))->Destroy2();
  ((UIScene *)((char *)this + 95916))->Destroy2();
  ((UIFrameWnd *)((char *)this + 95748))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 95596))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 95444))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 95292))->_UIFrameWnd();
  ((UIItem *)(UIItem *)this + 93924)->UIItem();
  ((UIWnd *)((char *)this + 93616))->ctor_9130();
  `eh vector destructor iterator'((char *)this + 88880, 0x98u, 30, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'(
    (char *)this + 83480,
    0xB4u,
    30,
    (void (*)(void *))UIFrameWnd_Destructor_444AC0);
  `eh vector destructor iterator'((char *)this + 71000, 0x34u, 240, (void (*)(void *))nullsub_1);
  `eh vector destructor iterator'(
    (char *)this + 26356,
    0x98u,
    240,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 25492, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 25328))->ctor_A1F0();
  ((UIFrameWnd *)((char *)this + 25176))->_UIFrameWnd();
  ((UIWnd *)this + 369)->ctor_D880();
  ((UIFrameWnd *)((char *)this + 24940))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x0046D140
int UIWnd::ctor_D140()
{
  int v2; // eax

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 18) = 800;
  *((_DWORD *)this + 19) = 600;
  *((_DWORD *)this + 20) = 300;
  *((_DWORD *)this + 21) = 400;
  *((_WORD *)this + 45) = 0;
  *((_DWORD *)this + 3496) = 0;
  *((_DWORD *)this + 3497) = 0;
  memset((char *)this + 13992, 0, 0x640u);
  memset((char *)this + 17192, 0, 0x190u);
  memset((char *)this + 15592, 0, 0x640u);
  *((_DWORD *)this + 22) = 0;
  *((_DWORD *)this + 4398) = 0;
  *((_DWORD *)this + 4528) = 0;
  *((_DWORD *)this + 4529) = 0;
  *((_DWORD *)this + 4532) = 0;
  *((_DWORD *)this + 4533) = 0;
  *((_DWORD *)this + 4534) = 0;
  *((_BYTE *)this + 18140) = 0;
  ((UIFrameWnd *)(UIFrameWnd *)this + 252)->UIFrameWnd();
  ((UIWnd *)((char *)this + 18296))->ctor_D830();
  ((UIFrameWnd *)((char *)this + 18380))->UIFrameWnd();
  ((UIScene *)((char *)this + 18548))->_UIScene();
  ((UIWnd *)((char *)this + 18892))->ctor_A160();
  `eh vector constructor iterator'(
    (char *)this + 19056,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIItem *)(UIItem *)this + 19920)->Refresh();
  ((UIWnd *)((char *)this + 21288))->ctor_9030();
  ((UIFrameWnd *)((char *)this + 21596))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 21764))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 21916))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 22068))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 22220))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 22388))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 22540,
    0x98u,
    13,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 24516))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 24668))->UIFrameWnd();
  ((UIListBox *)((char *)this + 24836))->UpdateKeyCtrl();
  ((UIScene *)((char *)this + 26092))->_UIScene();
  ((UIScene *)((char *)this + 26436))->_UIScene();
  *((_DWORD *)this + 6695) = 32;
  *((_DWORD *)this + 6696) = 16;
  *((_DWORD *)this + 6697) = 0;
  *((_DWORD *)this + 6698) = 0;
  ((UIFrameWnd *)((char *)this + 26808))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 26960))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27112))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27264))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 381)->UIFrameWnd();
  ((UIScene *)((char *)this + 27600))->_UIScene();
  ((UIScene *)((char *)this + 27964))->_UIScene();
  ((UIScene *)((char *)this + 28324))->_UIScene();
  ((UIFrameWnd *)((char *)this + 28700))->UIFrameWnd();
  *((_DWORD *)this + 7213) = 0;
  *((_DWORD *)this + 7214) = 0;
  *((_DWORD *)this + 7215) = 0;
  *((_BYTE *)this + 28864) = 0;
  *((_BYTE *)this + 28865) = 0;
  *((_DWORD *)this + 7217) = 0;
  *((_DWORD *)this + 7218) = 1065353216;
  *((_DWORD *)this + 7219) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B688;
  memset((char *)this + 88, 0, 0x4460u);
  v2 = *((_DWORD *)this + 19);
  *((_BYTE *)this + 19912) = 1;
  *((_BYTE *)this + 19916) = 0;
  *((_DWORD *)this + 4975) = v2 / 4;
  *((_BYTE *)this + 19915) = 0;
  *((_BYTE *)this + 19914) = 0;
  *((_BYTE *)this + 19913) = 0;
  *((_DWORD *)this + 4974) = 68;
  *((_DWORD *)this + 4976) = 65;
  *((_DWORD *)this + 4977) = 86;
  *((_BYTE *)this + 28888) = 1;
  return (int)this->_pad_000;
}

// 0x0046D4E0
void UIWnd::ctor_D4E0()
{
  void *v2; // eax

  *(_DWORD *)this->_pad_000 = &off_56B688;
  v2 = (void *)*((_DWORD *)this + 4528);
  if ( v2 )
  {
    operator delete(v2);
    *((_DWORD *)this + 4528) = 0;
  }
  if ( *((_DWORD *)this + 4529) )
  {
    operator delete(*((void **)this + 4529));
    *((_DWORD *)this + 4529) = 0;
  }
  *((_BYTE *)this + 18140) = 0;
  *((_DWORD *)this + 7219) = 0;
  ((UIListBox *)this)->SetScrollPos();
  ((UIFrameWnd *)((char *)this + 28700))->_UIFrameWnd();
  ((UIScene *)((char *)this + 28324))->Destroy2();
  ((UIScene *)((char *)this + 27964))->Destroy2();
  ((UIScene *)((char *)this + 27600))->Destroy2();
  ((UIFrameWnd *)(UIFrameWnd *)this + 381)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27264))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27112))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 26960))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 26808))->_UIFrameWnd();
  ((UIScene *)((char *)this + 26436))->Destroy2();
  ((UIScene *)((char *)this + 26092))->Destroy2();
  ((UIListBox *)((char *)this + 24836))->DeleteRow();
  ((UIFrameWnd *)((char *)this + 24668))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 24516))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 22540, 0x98u, 13, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 22388))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 22220))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 22068))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 21916))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 21764))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 21596))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 21288))->ctor_9130();
  ((UIItem *)(UIItem *)this + 19920)->UIItem();
  `eh vector destructor iterator'((char *)this + 19056, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 18892))->ctor_A1F0();
  ((UIScene *)((char *)this + 18548))->Destroy2();
  ((UIFrameWnd *)((char *)this + 18380))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 18296))->ctor_D880();
  ((UIFrameWnd *)(UIFrameWnd *)this + 252)->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00470A60
int UIWnd::ctor_A60()
{
  UIWnd *v2; // eax
  int v3; // ecx
  UIWnd *v4; // eax
  int v5; // ecx
  int v6; // eax

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 18) = 800;
  *((_DWORD *)this + 19) = 600;
  *((_DWORD *)this + 148) = -1;
  *((_WORD *)this + 299) = 0;
  *((_DWORD *)this + 3623) = 0;
  *((_DWORD *)this + 3624) = 0;
  memset((char *)this + 14500, 0, 0x640u);
  memset((char *)this + 17700, 0, 0x190u);
  memset((char *)this + 16100, 0, 0x640u);
  *((_DWORD *)this + 149) = 0;
  v2 = (UIWnd *)((char *)this + 46832);
  v3 = 1794;
  do
  {
    *(_DWORD *)v2->_pad_000 = 0xFFFF;
    *(_DWORD *)v2->m_fontcolor = 0;
    *(_DWORD *)v2->m_wndcolor = 0;
    v2 = (UIWnd *)((char *)v2 + 12);
    --v3;
  }
  while ( v3 );
  v4 = (UIWnd *)((char *)this + 68360);
  v5 = 1794;
  do
  {
    *(_DWORD *)v4->_pad_000 = 0xFFFF;
    *(_DWORD *)v4->m_fontcolor = 0;
    *(_DWORD *)v4->m_wndcolor = 0;
    v4 = (UIWnd *)((char *)v4 + 12);
    --v5;
  }
  while ( v5 );
  *((_DWORD *)this + 25163) = 0;
  ((UIFrameWnd *)((char *)this + 100672))->UIFrameWnd();
  ((UIWnd *)((char *)this + 100824))->ctor_D830();
  ((UIFrameWnd *)((char *)this + 100908))->UIFrameWnd();
  ((UIScene *)((char *)this + 101060))->_UIScene();
  ((UIWnd *)((char *)this + 101420))->ctor_A160();
  `eh vector constructor iterator'(
    (char *)this + 101584,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *((_DWORD *)this + 25606) = 250;
  *((_DWORD *)this + 25607) = 150;
  ((UIItem *)(UIItem *)this + 102448)->Refresh();
  ((UIWnd *)((char *)this + 103816))->ctor_9030();
  ((UIFrameWnd *)((char *)this + 104140))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 104292))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 104444))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 104596))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 105020,
    0x158u,
    6,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)(this + 1575))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 107268,
    0xB4u,
    25,
    (void (*)(void *))sub_444A20,
    (void (*)(void *))UIFrameWnd_Destructor_444AC0);
  ((UIWnd *)((char *)this + 111768))->ctor_D830();
  ((UIFrameWnd *)((char *)this + 111852))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 112004,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)((char *)this + 113844))->UpdateKeyCtrl();
  ((UIListBox *)(this + 1692))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 116268))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 117480))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 118692))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 119904))->UpdateKeyCtrl();
  *((_DWORD *)this + 30279) = 0;
  *((_DWORD *)this + 30280) = 0;
  ((UIScene *)((char *)this + 121156))->_UIScene();
  ((UIScene *)((char *)this + 121500))->_UIScene();
  *((_DWORD *)this + 30461) = 32;
  *((_DWORD *)this + 30462) = 16;
  *((_DWORD *)this + 30463) = 0;
  *((_DWORD *)this + 30464) = 0;
  ((UIScene *)((char *)this + 121872))->_UIScene();
  ((UIScene *)((char *)this + 122216))->_UIScene();
  *((_DWORD *)this + 30640) = -1;
  ((UIScene *)((char *)this + 122580))->_UIScene();
  ((UIScene *)((char *)this + 122924))->_UIScene();
  ((UIFrameWnd *)((char *)this + 123268))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1815))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 123572))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 123740))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 123908))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 124076))->UIFrameWnd();
  *((_BYTE *)this + 124244) = 0;
  *((_BYTE *)this + 124245) = 0;
  *((_DWORD *)this + 31062) = 0;
  *(_DWORD *)this->_pad_000 = &off_56B794;
  *((_DWORD *)this + 30278) = 0;
  *((_DWORD *)this + 29975) = 0;
  *((_DWORD *)this + 29672) = 0;
  *((_DWORD *)this + 29369) = 0;
  *((_DWORD *)this + 29066) = 0;
  *((_DWORD *)this + 28763) = 0;
  *((_BYTE *)this + 46828) = 0;
  *((_BYTE *)this + 102440) = 1;
  *((_BYTE *)this + 102444) = 0;
  *((_BYTE *)this + 102443) = 0;
  *((_BYTE *)this + 102442) = 0;
  *((_BYTE *)this + 102441) = 0;
  memset((char *)this + 46832, 0, 0x5418u);
  memset((char *)this + 68360, 0, 0x5418u);
  memset((char *)this + 18100, 0, 0x3810u);
  memset((char *)this + 32452, 0, 0x1C08u);
  memset((char *)this + 39628, 0, 0x1C08u);
  memset((char *)this + 89888, 0, 0x1C08u);
  memset((char *)this + 46804, 0, 0x18u);
  lstrcpyA((LPSTR)this + 104764, g_SceneMgr.m_szUIString);
  v6 = *((_DWORD *)this + 19);
  *((_DWORD *)this + 25606) = 68;
  *((_DWORD *)this + 25608) = 65;
  *((_DWORD *)this + 25607) = v6 / 4;
  *((_DWORD *)this + 25609) = 86;
  *((_BYTE *)this + 124264) = 1;
  return (int)this->_pad_000;
}

// 0x00470F40
void UIWnd::ctor_F40()
{
  *(_DWORD *)this->_pad_000 = &off_56B794;
  *((_BYTE *)this + 46828) = 0;
  *((_DWORD *)this + 31062) = 0;
  ((UIListBox *)this)->SetScrollPos();
  ((UIFrameWnd *)((char *)this + 124076))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 123908))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 123740))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 123572))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 1815))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 123268))->_UIFrameWnd();
  ((UIScene *)((char *)this + 122924))->Destroy2();
  ((UIScene *)((char *)this + 122580))->Destroy2();
  ((UIScene *)((char *)this + 122216))->Destroy2();
  ((UIScene *)((char *)this + 121872))->Destroy2();
  ((UIScene *)((char *)this + 121500))->Destroy2();
  ((UIScene *)((char *)this + 121156))->Destroy2();
  ((UIListBox *)((char *)this + 119904))->DeleteRow();
  ((UIListBox *)((char *)this + 118692))->DeleteRow();
  ((UIListBox *)((char *)this + 117480))->DeleteRow();
  ((UIListBox *)((char *)this + 116268))->DeleteRow();
  ((UIListBox *)(this + 1692))->DeleteRow();
  ((UIListBox *)((char *)this + 113844))->DeleteRow();
  `eh vector destructor iterator'(
    (char *)this + 112004,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 111852))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 111768))->ctor_D880();
  `eh vector destructor iterator'(
    (char *)this + 107268,
    0xB4u,
    25,
    (void (*)(void *))UIFrameWnd_Destructor_444AC0);
  ((UIFrameWnd *)(this + 1575))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 105020, 0x158u, 6, (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)((char *)this + 104596))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 104444))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 104292))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 104140))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 103816))->ctor_9130();
  ((UIItem *)(UIItem *)this + 102448)->UIItem();
  `eh vector destructor iterator'((char *)this + 101584, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 101420))->ctor_A1F0();
  ((UIScene *)((char *)this + 101060))->Destroy2();
  ((UIFrameWnd *)((char *)this + 100908))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 100824))->ctor_D880();
  ((UIFrameWnd *)((char *)this + 100672))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00477BB0
int UIWnd::ctor_7BB0(int arg0, int a3, int a4)
{
  int v5; // eax
  UIWnd *v6; // ebx
  char *v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  char *v11; // ecx
  int result; // eax
  UIListBox *v13; // edi
  int *v14; // eax
  int v15; // eax
  int v16; // eax
  char *Instance; // eax
  int *v18; // eax
  int v19; // eax
  const char *v20; // ebp
  int v21; // eax
  const char *v22; // ebp
  char *v23; // edi
  int v24; // ebp
  int v25; // ebx
  const char **v26; // eax
  const char *v27; // ebp
  const char **v28; // eax
  const char **v29; // eax
  const char **v30; // eax
  const char **v31; // eax
  const char **v32; // eax
  int v33; // edi
  char *v34; // ebx
  int v35; // edi
  char *v36; // ebx
  int v37; // edi
  char *v38; // ebx
  int v39; // edi
  char *v40; // ebx
  int v41; // edi
  char *v42; // ebx
  int v43; // edx
  int *v44; // edi
  const char *v45; // eax
  const char *v46; // ecx
  int v47; // ebx
  int v48; // eax
  int v49; // ecx
  int v50; // edx
  int v51; // edx
  int v52; // ebp
  int v53; // edx
  int v54; // eax
  int v55; // eax
  int v56; // ecx
  signed int v57; // ecx
  void *v58; // [esp-8h] [ebp-160h]
  UIListBox *v59; // [esp-8h] [ebp-160h]
  UIListBox *v60; // [esp-8h] [ebp-160h]
  gbColorQuad v61; // [esp-4h] [ebp-15Ch]
  int v62; // [esp+10h] [ebp-148h]
  const char *v63; // [esp+10h] [ebp-148h]
  const char *v64; // [esp+14h] [ebp-144h]
  int a2; // [esp+18h] [ebp-140h] BYREF
  int v66; // [esp+1Ch] [ebp-13Ch]
  int v67; // [esp+20h] [ebp-138h]
  int v68; // [esp+24h] [ebp-134h]
  int v69; // [esp+28h] [ebp-130h] BYREF
  int v70; // [esp+30h] [ebp-128h] BYREF
  int v71; // [esp+38h] [ebp-120h] BYREF
  int pOut; // [esp+40h] [ebp-118h] BYREF
  int v73; // [esp+48h] [ebp-110h] BYREF
  int v74; // [esp+50h] [ebp-108h] BYREF
  char Buffer[253]; // [esp+58h] [ebp-100h] BYREF
  __int16 v76; // [esp+155h] [ebp-3h]
  char v77; // [esp+157h] [ebp-1h]

  switch ( arg0 )
  {
    case 1000:
      if ( !a3 )
        goto LABEL_36;
      sub_472AA0((int)this);
      sub_473520(this->_pad_000, 0);
      v5 = 0;
      v6 = (UIWnd *)((char *)this + 102348);
      v62 = 0;
      v7 = (char *)this + 107448;
      do
      {
        if ( *((_BYTE *)this + v5 + 102440) )
        {
          v8 = v6[-1].m_bfocus - 24;
          v66 = *(_DWORD *)v6->_pad_000 + 36;
          a2 = v8;
          v68 = v66 + 30;
          v67 = v8 + 24;
          ((UIWnd *)(v7 - 180))->GetRect(&a2);
          (**((void (***)(int, _DWORD))v7 - 45))((int)(v7 - 180), 0);
          ((UIWnd *)v7)->GetRect(&a2);
          (**(void (***)(char *, _DWORD))v7)(v7, 0);
          ((UIWnd *)(v7 + 180))->GetRect(&a2);
          v9 = *(_DWORD *)v6->_pad_000 + 36;
          a2 = *(_DWORD *)v6->m_fontcolor + 18;
          v67 = a2 + 22;
          v66 = v9;
          v68 = v9 + 30;
          ((UIWnd *)(v7 + 360))->GetRect(&a2);
          (**((void (***)(int, _DWORD))v7 + 90))((int)(v7 + 360), 0);
          ((UIWnd *)(v7 + 540))->GetRect(&a2);
          (**((void (***)(int, _DWORD))v7 + 135))((int)(v7 + 540), 0);
          v5 = v62;
        }
        ++v5;
        v6 = (UIWnd *)((char *)v6 + 16);
        v7 += 900;
        v62 = v5;
      }
      while ( v5 < 5 );
      *((_DWORD *)this + 148) = 0;
      if ( sub_43F650((int *)this + 28461) > 0 )
        (*(void (**)(UIWnd *, int, int, _DWORD))(*(_DWORD *)this->_pad_000 + 24))(
          this,
          1007,
          773,
          *((_DWORD *)this + 148));
      else
        *((_DWORD *)this + 148) = -1;
      if ( !*((_DWORD *)this + 31062) )
      {
        (**((void (***)(char *, int))this + 26149))((char *)this + 104596, 1);
        ((UIWnd *)((char *)this + 104596))->SetEnable((const char *)this + 1376, 0);
        v10 = lstrlenA((LPCSTR)this + 1376);
        v11 = (char *)this + 101420;
        if ( v10 > 0 )
          (**(void (***)(char *, int))v11)(v11, 1);
        else
          (**(void (***)(char *, _DWORD))v11)(v11, 0);
      }
      sprintf((char *const)this + 80, "%s %d", byte_DC5F3C, *(_DWORD *)&g_SceneMgr.m_slot4[828]);
      ((UIWnd *)((char *)this + 123908))->SetEnable((const char *)this + 80, 0);
      *((_BYTE *)this + 121869) = 1;
      *((_BYTE *)this + 121868) = 1;
      UICursor::IRender();
      result = 1;
      break;
    case 1001:
      v13 = 0;
      v14 = dword_56B77C;
      while ( a3 != *v14 )
      {
        ++v14;
        v13 = (UIListBox *)((char *)v13 + 1);
        if ( (int)v14 >= (int)&off_56B794 )
        {
          switch ( a3 )
          {
            case 770:
              sub_4777B0((int)this);
              v15 = *((_DWORD *)this + 31062);
              if ( v15 )
              {
                if ( v15 == 1 )
                  sub_523820(*((_DWORD **)this + 31064), 2);
              }
              else
              {
                sub_45A220(*((_DWORD **)this + 31063), 0);
              }
              goto LABEL_34;
            case 788:
              sub_475FC0((int)this);
              v58 = off_5B9DE4;
              goto LABEL_35;
            case 789:
              sub_4765D0(this);
              v16 = *((_DWORD *)this + 31062);
              if ( v16 )
              {
                if ( v16 == 1 )
                {
                  ((UIWnd *)((char *)this + 104596))->SetEnable(g_SceneMgr.m_szUIString, 0);
                  (**((void (***)(char *, _DWORD))this + 25355))((char *)this + 101420, 0);
                }
              }
              else
              {
                (**((void (***)(char *, int))this + 26149))((char *)this + 104596, 1);
                ((UIWnd *)((char *)this + 104596))->SetEnable((const char *)this + 1888, 0);
                (**((void (***)(char *, int))this + 25355))((char *)this + 101420, 1);
              }
              goto LABEL_34;
            case 819:
              v59 = (UIListBox *)*((_DWORD *)this + 30279);
              *((_DWORD *)this + 30640) = 3;
              sub_473B50((int)this, v59, (unsigned int *)3);
              v58 = off_5B9DE4;
              goto LABEL_35;
            case 820:
              v60 = (UIListBox *)*((_DWORD *)this + 30279);
              *((_DWORD *)this + 30640) = 0;
              sub_473B50((int)this, v60, 0);
LABEL_34:
              v58 = off_5B9DE4;
              goto LABEL_35;
            case 821:
              v61.ColorQuadFmt = *((_DWORD *)this + 30279);
              sub_4765F0((int)this, v61);
              goto LABEL_31;
            case 822:
              v61.ColorQuadFmt = *((_DWORD *)this + 30279);
              sub_476ED0((int)this, v61);
LABEL_31:
              ((UIWnd *)((char *)this + 104596))->SetEnable(g_SceneMgr.m_szUIString, 0);
              (**((void (***)(char *, _DWORD))this + 25355))((char *)this + 101420, 0);
              result = 1;
              break;
            default:
              goto LABEL_36;
          }
          return result;
        }
      }
      UIObj_SetState((UIWnd *)((char *)this + 344 * (_DWORD)v13 + 105020), 0);
      sub_473520(this->_pad_000, v13);
      ((UIWnd *)((char *)this + 104596))->SetEnable(g_SceneMgr.m_szUIString, 0);
      (**((void (***)(char *, _DWORD))this + 25355))((char *)this + 101420, 0);
      v58 = off_5B9DE4;
LABEL_35:
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v58, 1);
LABEL_36:
      result = 1;
      break;
    case 1005:
      (**((void (***)(char *, _DWORD))this + 30289))((char *)this + 121156, 0);
      (**((void (***)(char *, _DWORD))this + 30375))((char *)this + 121500, 0);
      result = 1;
      break;
    case 1007:
      *((_DWORD *)this + 148) = a4;
      if ( a4 <= -1 )
      {
        ((UIWnd *)this + 1815)->SetEnable(g_SceneMgr.m_szUIString, 0);
        *((_DWORD *)this + 25973) = 0;
        (**((void (***)(char *, _DWORD))this + 30289))((char *)this + 121156, 0);
        (**((void (***)(char *, _DWORD))this + 30375))((char *)this + 121500, 0);
        result = 1;
      }
      else
      {
        ((UIWnd *)((char *)this + 104596))->SetEnable(g_SceneMgr.m_szUIString, 0);
        (**((void (***)(char *, _DWORD))this + 25355))((char *)this + 101420, 0);
        sub_477A90((int)this, *((_DWORD *)this + 30279), *((_DWORD *)this + 148));
        v18 = (int *)*((_DWORD *)this + 897 * *((_DWORD *)this + 30279) + 3 * *((_DWORD *)this + 148) + 11710);
        if ( *((_BYTE *)v18 + 613) == 5 )
        {
          SetFloatParam((char *)this + 103816, 228.0);
          Camera_Method_439930((int)this + 103816, 330, 280, 600);
        }
        else if ( *((_BYTE *)v18 + 612) == 11 )
        {
          SetFloatParam((char *)this + 103816, 228.0);
          Camera_Method_439930((int)this + 103816, 330, 272, 600);
        }
        else
        {
          v19 = *v18;
          if ( v19 == 8114 || v19 == 8132 )
          {
            SetFloatParam((char *)this + 103816, 180.0);
            Camera_Method_439930((int)this + 103816, 330, 252, 600);
          }
          else
          {
            SetFloatParam((char *)this + 103816, 180.0);
            Camera_Method_439930((int)this + 103816, 330, 268, 600);
          }
        }
        if ( !strcmp(
                (const char *)(*((_DWORD *)this + 897 * *((_DWORD *)this + 30279) + 3 * *((_DWORD *)this + 148) + 11710)
                             + 36),
                g_SceneMgr.m_szUIString) )
        {
          sprintf((char *const)this + 80, "%s", aNone);
        }
        else
        {
          v20 = (const char *)(*((_DWORD *)this + 897 * *((_DWORD *)this + 30279) + 3 * *((_DWORD *)this + 148) + 11710)
                             + 36);
          sprintf((char *const)this + 80, "Item\\%s\\%s.pol", v20, v20);
        }
        sub_439230((int *)this + 25972, (const char *)this + 80, 0);
        v21 = *((_DWORD *)this + 897 * *((_DWORD *)this + 30279) + 3 * *((_DWORD *)this + 148) + 11710);
        v22 = (const char *)(v21 + 36);
        v63 = (const char *)(v21 + 66);
        if ( !strcmp((const char *)(v21 + 36), g_SceneMgr.m_szUIString) )
        {
          sprintf((char *const)this + 80, "%s", aNone);
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v76 = 0;
          v77 = 0;
          sprintf(Buffer, "%s%s", v22, v63);
          sprintf((char *const)this + 80, "Item\\%s\\%s.tga", v22, Buffer);
        }
        ((gbGeomNode *)*((gbGeomNode **)this + 25976))->ReplaceTexture((const char *)this + 80);
        *((_DWORD *)this + 25973) = 1;
        v23 = (char *)this + 107268;
        v24 = 5;
        do
        {
          v25 = 5;
          do
          {
            (**(void (***)(char *, _DWORD))v23)(v23, 0);
            v23 += 180;
            --v25;
          }
          while ( v25 );
          --v24;
        }
        while ( v24 );
        switch ( *((_DWORD *)this + 30279) )
        {
          case 0:
            GetGridOffset((char *)this + 113844, &pOut, *((_DWORD *)this + 148));
            v27 = (const char *)*v26;
            v64 = (const char *)v26[1];
            break;
          case 1:
            GetGridOffset(this + 1692, &v73, *((_DWORD *)this + 148));
            v27 = (const char *)*v28;
            v64 = (const char *)v28[1];
            break;
          case 2:
            GetGridOffset((char *)this + 116268, &v74, *((_DWORD *)this + 148));
            v27 = (const char *)*v29;
            v64 = (const char *)v29[1];
            break;
          case 3:
            GetGridOffset((char *)this + 117480, &v69, *((_DWORD *)this + 148));
            v27 = (const char *)*v30;
            v64 = (const char *)v30[1];
            break;
          case 4:
            GetGridOffset((char *)this + 118692, &v70, *((_DWORD *)this + 148));
            v27 = (const char *)*v31;
            v64 = (const char *)v31[1];
            break;
          case 5:
            GetGridOffset((char *)this + 119904, &v71, *((_DWORD *)this + 148));
            v27 = (const char *)*v32;
            v64 = (const char *)v32[1];
            switch ( *(_BYTE *)(*((_DWORD *)this + 3 * *((_DWORD *)this + 148) + 16195) + 612) )
            {
              case 7:
                v33 = 0;
                v34 = (char *)this + 107268;
                do
                {
                  if ( *((_BYTE *)this + v33 + 102440)
                    && *(_BYTE *)(*((_DWORD *)this + 3 * *((_DWORD *)this + 148) + 16195) + v33 + 614) )
                  {
                    (**(void (***)(char *, int))v34)(v34, 1);
                  }
                  ++v33;
                  v34 += 900;
                }
                while ( v33 < 5 );
                break;
              case 8:
                v35 = 0;
                v36 = (char *)this + 107808;
                do
                {
                  if ( *((_BYTE *)this + v35 + 102440)
                    && *(_BYTE *)(*((_DWORD *)this + 3 * *((_DWORD *)this + 148) + 16195) + v35 + 614) )
                  {
                    (**(void (***)(char *, int))v36)(v36, 1);
                  }
                  ++v35;
                  v36 += 900;
                }
                while ( v35 < 5 );
                break;
              case 9:
                v37 = 0;
                v38 = (char *)this + 107988;
                do
                {
                  if ( *((_BYTE *)this + v37 + 102440)
                    && *(_BYTE *)(*((_DWORD *)this + 3 * *((_DWORD *)this + 148) + 16195) + v37 + 614) )
                  {
                    (**(void (***)(char *, int))v38)(v38, 1);
                  }
                  ++v37;
                  v38 += 900;
                }
                while ( v37 < 5 );
                break;
              case 0xA:
                v39 = 0;
                v40 = (char *)this + 107628;
                do
                {
                  if ( *((_BYTE *)this + v39 + 102440)
                    && *(_BYTE *)(*((_DWORD *)this + 3 * *((_DWORD *)this + 148) + 16195) + v39 + 614) )
                  {
                    (**(void (***)(char *, int))v40)(v40, 1);
                  }
                  ++v39;
                  v40 += 900;
                }
                while ( v39 < 5 );
                break;
              case 0xB:
                v41 = 0;
                v42 = (char *)this + 107448;
                do
                {
                  if ( *((_BYTE *)this + v41 + 102440)
                    && *(_BYTE *)(*((_DWORD *)this + 3 * *((_DWORD *)this + 148) + 16195) + v41 + 614) )
                  {
                    (**(void (***)(char *, int))v42)(v42, 1);
                  }
                  ++v41;
                  v42 += 900;
                }
                while ( v41 < 5 );
                break;
              default:
                goto LABEL_95;
            }
            break;
          default:
            v27 = v63;
            break;
        }
LABEL_95:
        v43 = *((_DWORD *)this + 30463);
        v44 = (int *)((char *)this + 121124);
        v45 = (const char *)v64 - 4;
        v46 = (const char *)v27 + 162;
        if ( v43 )
        {
          if ( v43 == 1 )
          {
            v47 = *((_DWORD *)this + 30461);
            *((_DWORD *)this + 30286) = v45;
            *((_DWORD *)this + 30285) = v46;
            *((_DWORD *)this + 30287) = &v46[v47];
            *((_DWORD *)this + 30288) = &v45[*((_DWORD *)this + 30462)];
            ((UIWnd *)((char *)this + 121500))->GetRect((_DWORD *)this + 30285);
            v48 = *((_DWORD *)this + 30287) + *((_DWORD *)this + 30464);
            v49 = *((_DWORD *)this + 30461);
            *((_DWORD *)this + 30282) = *((_DWORD *)this + 30286);
            v50 = *((_DWORD *)this + 30288);
            *v44 = v48;
            *((_DWORD *)this + 30284) = v50;
            *((_DWORD *)this + 30283) = v49 + v48;
            ((UIWnd *)((char *)this + 121156))->GetRect((_DWORD *)this + 30281);
          }
        }
        else
        {
          v51 = *((_DWORD *)this + 30461);
          v52 = *((_DWORD *)this + 30462);
          *((_DWORD *)this + 30282) = v45;
          *v44 = (int)v46;
          *((_DWORD *)this + 30283) = &v46[v51];
          *((_DWORD *)this + 30284) = &v45[v52];
          ((UIWnd *)((char *)this + 121156))->GetRect((_DWORD *)this + 30281);
          v53 = *v44;
          v54 = *((_DWORD *)this + 30284) + *((_DWORD *)this + 30464);
          *((_DWORD *)this + 30286) = v54;
          *((_DWORD *)this + 30285) = v53;
          *((_DWORD *)this + 30287) = *((_DWORD *)this + 30283);
          *((_DWORD *)this + 30288) = *((_DWORD *)this + 30462) + v54;
          ((UIWnd *)((char *)this + 121500))->GetRect((_DWORD *)this + 30285);
        }
        (**((void (***)(char *, int))this + 30289))((char *)this + 121156, 1);
        (**((void (***)(char *, int))this + 30375))((char *)this + 121500, 1);
        v55 = 299 * *((_DWORD *)this + 30279) + *((_DWORD *)this + 148);
        v56 = *((_DWORD *)this + v55 + 8113);
        if ( v56 > 0 )
        {
          UIObj_SetState((UIWnd *)((char *)this + 121156), v56 != *((_DWORD *)this + v55 + 9907));
          UIObj_SetState((UIWnd *)((char *)this + 121500), 1);
        }
        else
        {
          UIObj_SetState((UIWnd *)((char *)this + 121156), 1);
          UIObj_SetState((UIWnd *)((char *)this + 121500), 0);
        }
        result = 1;
      }
      break;
    case 1009:
      if ( a3 == 801 )
      {
        v57 = HIWORD(a4);
        if ( (unsigned __int16)a4 > *((int *)this + 26187)
          && (unsigned __int16)a4 < *((int *)this + 26189)
          && v57 > *((_DWORD *)this + 26188)
          && v57 < *((_DWORD *)this + 26190) )
        {
          ((UIWnd *)((char *)this + 104596))->SetEnable(g_SceneMgr.m_szUIString, 0);
          (**((void (***)(char *, _DWORD))this + 25355))((char *)this + 101420, 0);
        }
      }
      result = 1;
      break;
    default:
      result = arg0->SendMessage(a3, a4);
      break;
  }
  return result;
}

// 0x00479300
int UIWnd::ctor_9300()
{
  UIWnd *v2; // eax
  int v3; // ecx
  UIWnd *v4; // eax
  int v5; // ecx
  UIWnd *v6; // eax
  int v7; // ecx
  UIWnd *v8; // eax
  int v9; // ecx

  ((UIListBox *)this)->UIListBox();
  v2 = (UIWnd *)((char *)this + 360);
  v3 = 99;
  do
  {
    *(_DWORD *)v2->_pad_000 = 0xFFFF;
    *(_DWORD *)v2->m_fontcolor = 0;
    *(_DWORD *)v2->m_wndcolor = 0;
    v2 = (UIWnd *)((char *)v2 + 12);
    --v3;
  }
  while ( v3 );
  v4 = (UIWnd *)((char *)this + 1548);
  v5 = 99;
  do
  {
    *(_DWORD *)v4->_pad_000 = 0xFFFF;
    *(_DWORD *)v4->m_fontcolor = 0;
    *(_DWORD *)v4->m_wndcolor = 0;
    v4 = (UIWnd *)((char *)v4 + 12);
    --v5;
  }
  while ( v5 );
  v6 = (UIWnd *)((char *)this + 2736);
  v7 = 99;
  do
  {
    *(_DWORD *)v6->_pad_000 = 0xFFFF;
    *(_DWORD *)v6->m_fontcolor = 0;
    *(_DWORD *)v6->m_wndcolor = 0;
    v6 = (UIWnd *)((char *)v6 + 12);
    --v7;
  }
  while ( v7 );
  v8 = (UIWnd *)((char *)this + 3924);
  v9 = 99;
  do
  {
    *(_DWORD *)v8->_pad_000 = 0xFFFF;
    *(_DWORD *)v8->m_fontcolor = 0;
    *(_DWORD *)v8->m_wndcolor = 0;
    v8 = (UIWnd *)((char *)v8 + 12);
    --v9;
  }
  while ( v9 );
  *((_DWORD *)this + 40705) = 0xFFFF;
  *((_DWORD *)this + 40706) = 0;
  *((_DWORD *)this + 40707) = 0;
  *((_DWORD *)this + 40708) = 0xFFFF;
  *((_DWORD *)this + 40709) = 0;
  *((_DWORD *)this + 40710) = 0;
  *((_DWORD *)this + 40711) = 0xFFFF;
  *((_DWORD *)this + 40712) = 0;
  *((_DWORD *)this + 40713) = 0;
  ((UIWnd *)((char *)this + 162880))->ctor_D830();
  ((UIFrameWnd *)((char *)this + 162964))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 163116))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2401))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 163420))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 163572))->UIFrameWnd();
  ((UIWnd *)((char *)this + 163724))->ctor_A160();
  ((UIFrameWnd *)((char *)this + 163888))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164040))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164192))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164344))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164496))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164648))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164800))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 164952,
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 166472))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 166624,
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)((char *)this + 167232))->UpdateKeyCtrl();
  ((UIScene *)((char *)this + 168440))->_UIScene();
  ((UIScene *)((char *)this + 168784))->_UIScene();
  ((UIScene *)((char *)this + 169128))->_UIScene();
  ((UIItem *)(UIItem *)this + 169472)->Refresh();
  ((UIItem *)(UIItem *)this + 170840)->Refresh();
  ((UIItem *)(UIItem *)this + 172208)->Refresh();
  ((UIWnd *)((char *)this + 173576))->ctor_9030();
  *((_BYTE *)this + 173892) = 0;
  *((_DWORD *)this + 43472) = 0;
  *((_DWORD *)this + 43471) = 0;
  *((_BYTE *)this + 173904) = 0;
  *((_DWORD *)this + 43475) = 0;
  *((_DWORD *)this + 43474) = 0;
  `eh vector constructor iterator'(
    (char *)this + 173948,
    0x248u,
    60,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  *(_DWORD *)this->_pad_000 = &off_56B820;
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_DWORD *)this + 25) = 0;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 40714) = 0;
  *((_DWORD *)this + 40715) = 0;
  *((_DWORD *)this + 40716) = 0;
  *((_DWORD *)this + 40717) = -1;
  *((_DWORD *)this + 40718) = 0;
  memset((char *)this + 162720, 0, 0x60u);
  *((_WORD *)this + 81408) = 0;
  *((_BYTE *)this + 162818) = 0;
  *((_DWORD *)this + 40707) = 0;
  *((_DWORD *)this + 40708) = 0;
  *((_DWORD *)this + 40709) = 0;
  *((_DWORD *)this + 40710) = 0;
  *((_DWORD *)this + 40711) = 0;
  *((_DWORD *)this + 40712) = 0;
  *((_BYTE *)this + 173940) = 0;
  *((_BYTE *)this + 173941) = 1;
  return (int)this->_pad_000;
}

// 0x00479680
void UIWnd::ctor_9680()
{
  *(_DWORD *)this->_pad_000 = &off_56B820;
  `eh vector destructor iterator'(
    (char *)this + 173948,
    0x248u,
    60,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIWnd *)((char *)this + 173576))->ctor_9130();
  ((UIItem *)(UIItem *)this + 172208)->UIItem();
  ((UIItem *)(UIItem *)this + 170840)->UIItem();
  ((UIItem *)(UIItem *)this + 169472)->UIItem();
  ((UIScene *)((char *)this + 169128))->Destroy2();
  ((UIScene *)((char *)this + 168784))->Destroy2();
  ((UIScene *)((char *)this + 168440))->Destroy2();
  ((UIListBox *)((char *)this + 167232))->DeleteRow();
  `eh vector destructor iterator'((char *)this + 166624, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 166472))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 164952,
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 164800))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164648))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164496))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164344))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164192))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 164040))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 163888))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 163724))->ctor_A1F0();
  ((UIFrameWnd *)((char *)this + 163572))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 163420))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 2401))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 163116))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 162964))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 162880))->ctor_D880();
  this->~UIWnd();
}

// 0x0047BBF0
int UIWnd::ctor_BBF0()
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)((char *)this + 128))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 280))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 432,
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)((char *)this + 888))->_UIScene();
  ((UIScene *)((char *)this + 1232))->_UIScene();
  ((UIScene *)((char *)this + 1576))->_UIScene();
  sub_44B850((int)this + 1920);
  *(_DWORD *)this->_pad_000 = &off_56B850;
  *((_DWORD *)this + 22) = 88;
  *((_DWORD *)this + 23) = 138;
  *((_DWORD *)this + 26) = 90;
  *((_DWORD *)this + 27) = 26;
  *((_DWORD *)this + 24) = 800;
  *((_DWORD *)this + 25) = 64;
  *((_DWORD *)this + 31) = 0;
  *((_DWORD *)this + 997) = 0;
  *((_BYTE *)this + 4000) = 1;
  return (int)this->_pad_000;
}

// 0x0047BD20
void UIWnd::ctor_BD20()
{
  *(_DWORD *)this->_pad_000 = &off_56B850;
  sub_47BDF0((int)this);
  j_PalScript_Cleanup((PalScript *)this + 30);
  ((UIScene *)((char *)this + 1576))->Destroy2();
  ((UIScene *)((char *)this + 1232))->Destroy2();
  ((UIScene *)((char *)this + 888))->Destroy2();
  `eh vector destructor iterator'((char *)this + 432, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 280))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 128))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x0047E5C0
int UIWnd::ctor_E5C0()
{
  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_BYTE *)this + 360) = 0;
  *((_BYTE *)this + 361) = 0;
  *((_DWORD *)this + 91) = 0;
  ((UIFrameWnd *)((char *)this + 368))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 520))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 672))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 824))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 976))->UIFrameWnd();
  ((UIScene *)((char *)this + 1128))->_UIScene();
  ((UIScene *)((char *)this + 1472))->_UIScene();
  ((UIScene *)((char *)this + 1816))->_UIScene();
  ((UIScene *)((char *)this + 2160))->_UIScene();
  ((UIScene *)((char *)this + 2504))->_UIScene();
  ((UIScene *)((char *)this + 2848))->_UIScene();
  ((UIScene *)((char *)this + 3192))->_UIScene();
  ((UIScene *)(this + 52))->_UIScene();
  ((UIScene *)((char *)this + 3880))->_UIScene();
  ((UIFrameWnd *)((char *)this + 4224))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 61)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4544))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 4696,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 79448,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIWnd *)((char *)this + 154340))->ctor_9030();
  ((UIWnd *)((char *)this + 154648))->ctor_9030();
  ((UIFrameWnd *)((char *)this + 154956))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2281))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 155260))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 155412,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 156172,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 156932,
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 157604))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 157756))->UIFrameWnd();
  ((UIScene *)((char *)this + 157908))->_UIScene();
  ((UIScene *)((char *)this + 158252))->_UIScene();
  ((UIStatic *)((char *)this + 158596))->UIStatic();
  ((UIStatic *)((char *)this + 158844))->UIStatic();
  ((UIStatic *)((char *)this + 159092))->UIStatic();
  ((UIStatic *)((char *)this + 159340))->UIStatic();
  ((UIStatic *)((char *)this + 159588))->UIStatic();
  ((UIStatic *)((char *)this + 159836))->UIStatic();
  *(_DWORD *)this->_pad_000 = &off_56B90C;
  *((_DWORD *)this + 38582) = 0;
  *((_DWORD *)this + 38583) = 0;
  *((_DWORD *)this + 38584) = 0;
  sub_47EC00((int)this);
  return (int)this->_pad_000;
}

// 0x0047E910
void UIWnd::ctor_E910()
{
  *(_DWORD *)this->_pad_000 = &off_56B90C;
  sub_47F410((int)this);
  ((UIWnd *)((char *)this + 159836))->~UIWnd();
  ((UIWnd *)((char *)this + 159588))->~UIWnd();
  ((UIWnd *)((char *)this + 159340))->~UIWnd();
  ((UIWnd *)((char *)this + 159092))->~UIWnd();
  ((UIWnd *)((char *)this + 158844))->~UIWnd();
  ((UIWnd *)((char *)this + 158596))->~UIWnd();
  ((UIScene *)((char *)this + 158252))->Destroy2();
  ((UIScene *)((char *)this + 157908))->Destroy2();
  ((UIFrameWnd *)((char *)this + 157756))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 157604))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 156932, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 156172, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 155412, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 155260))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 2281))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154956))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 154648))->ctor_9130();
  ((UIWnd *)((char *)this + 154340))->ctor_9130();
  `eh vector destructor iterator'(
    (char *)this + 79448,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 4696,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 4544))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 61)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4224))->_UIFrameWnd();
  ((UIScene *)((char *)this + 3880))->Destroy2();
  ((UIScene *)(this + 52))->Destroy2();
  ((UIScene *)((char *)this + 3192))->Destroy2();
  ((UIScene *)((char *)this + 2848))->Destroy2();
  ((UIScene *)((char *)this + 2504))->Destroy2();
  ((UIScene *)((char *)this + 2160))->Destroy2();
  ((UIScene *)((char *)this + 1816))->Destroy2();
  ((UIScene *)((char *)this + 1472))->Destroy2();
  ((UIScene *)((char *)this + 1128))->Destroy2();
  ((UIFrameWnd *)((char *)this + 976))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 824))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 672))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 520))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 368))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00482ED0
int UIWnd::ctor_2ED0()
{
  char *v2; // edi
  int v4; // [esp+10h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_BYTE *)this + 360) = 0;
  ((UIFrameWnd *)((char *)this + 368))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 520))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 672))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 824))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 976))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1128))->UIFrameWnd();
  ((UIScene *)((char *)this + 1280))->_UIScene();
  ((UIScene *)((char *)this + 1624))->_UIScene();
  ((UIScene *)((char *)this + 1968))->_UIScene();
  ((UIScene *)(this + 34))->_UIScene();
  ((UIScene *)((char *)this + 2656))->_UIScene();
  ((UIScene *)((char *)this + 3000))->_UIScene();
  ((UIScene *)((char *)this + 3344))->_UIScene();
  ((UIScene *)((char *)this + 3688))->_UIScene();
  ((UIScene *)((char *)this + 4032))->_UIScene();
  ((UIFrameWnd *)((char *)this + 4376))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4544))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4696))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4848))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 5000,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 79752,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  memset((char *)this + 154644, 0, 0x1Cu);
  *((_WORD *)this + 77336) = 0;
  *(_DWORD *)((char *)this + 154674) = 117901063;
  *((_BYTE *)this + 154678) = 7;
  ((UIFrameWnd *)((char *)this + 154696))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 154848,
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)this + 156588,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 157348,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *((_DWORD *)this + 39547) = 0;
  ((UIItem *)(UIItem *)this + 158192)->Refresh();
  v2 = (char *)this + 159592;
  v4 = 6;
  do
  {
    ((void (*)(char *))gbVec3D::`default constructor closure')(v2);
    v2 += 12;
    --v4;
  }
  while ( v4 );
  ((ObjectCamera *)(this + 2348))->Update();
  `eh vector constructor iterator'(
    (char *)this + 159816,
    0x98u,
    5,
    (void (*)(void *))ObjectCamera::Update,
    (void (*)(void *))Object3D::Object3D);
  `eh vector constructor iterator'(
    (char *)this + 160608,
    0x98u,
    6,
    (void (*)(void *))ObjectCamera::Update,
    (void (*)(void *))Object3D::Object3D);
  `eh vector constructor iterator'(
    (char *)this + 161520,
    0x798u,
    5,
    (void (*)(void *))sub_483280,
    (void (*)(void *))sub_483300);
  *((_DWORD *)this + 42810) = 0;
  *(_DWORD *)this->_pad_000 = &off_56BA30;
  *((_BYTE *)this + 365) = 0;
  *((_BYTE *)this + 364) = 0;
  *((_BYTE *)this + 362) = 0;
  *((_BYTE *)this + 361) = 0;
  *((_BYTE *)this + 363) = 0;
  memset((char *)this + 154644, 0, 0x1Cu);
  *((_WORD *)this + 77336) = 0;
  *(_DWORD *)((char *)this + 154674) = 0;
  *((_BYTE *)this + 154678) = 0;
  *((_DWORD *)this + 38658) = 0;
  *((_DWORD *)this + 38659) = 0;
  *((_DWORD *)this + 38660) = 0;
  *((_DWORD *)this + 39890) = -1038614528;
  *((_DWORD *)this + 39891) = 1072064102;
  *((_DWORD *)this + 39893) = 1094713344;
  *((_DWORD *)this + 39892) = 0;
  return (int)this->_pad_000;
}

// 0x00483380
void UIWnd::ctor_3380()
{
  ObjectCamera **v2; // ecx
  void *v3; // edi

  *(_DWORD *)this->_pad_000 = &off_56BA30;
  v2 = (ObjectCamera **)*((_DWORD *)this + 39892);
  if ( v2 )
  {
    v2->Destroy();
    v3 = (void *)*((_DWORD *)this + 39892);
    if ( v3 )
    {
      ((ObjectCamera *)*((ObjectCamera ***)this + 39892))->GetCameraDirect();
      operator delete(v3);
    }
    *((_DWORD *)this + 39892) = 0;
  }
  `eh vector destructor iterator'((char *)this + 161520, 0x798u, 5, (void (*)(void *))sub_483300);
  `eh vector destructor iterator'((char *)this + 160608, 0x98u, 6, (void (*)(void *))Object3D::Object3D);
  `eh vector destructor iterator'((char *)this + 159816, 0x98u, 5, (void (*)(void *))Object3D::Object3D);
  ((Object3D *)(this + 2348))->Object3D();
  ((UIItem *)(UIItem *)this + 158192)->UIItem();
  `eh vector destructor iterator'((char *)this + 157348, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 156588, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 154848, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)((char *)this + 154696))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 79752,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 5000,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 4848))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4696))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4544))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4376))->_UIFrameWnd();
  ((UIScene *)((char *)this + 4032))->Destroy2();
  ((UIScene *)((char *)this + 3688))->Destroy2();
  ((UIScene *)((char *)this + 3344))->Destroy2();
  ((UIScene *)((char *)this + 3000))->Destroy2();
  ((UIScene *)((char *)this + 2656))->Destroy2();
  ((UIScene *)(this + 34))->Destroy2();
  ((UIScene *)((char *)this + 1968))->Destroy2();
  ((UIScene *)((char *)this + 1624))->Destroy2();
  ((UIScene *)((char *)this + 1280))->Destroy2();
  ((UIFrameWnd *)((char *)this + 1128))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 976))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 824))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 672))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 520))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 368))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x004867F0
int UIWnd::ctor_67F0()
{
  char *v2; // edi
  int v3; // ebp

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_DWORD *)this + 218) = 0;
  *((_BYTE *)this + 876) = 0;
  *((_BYTE *)this + 889) = 0;
  *((_DWORD *)this + 223) = 0;
  *((_DWORD *)this + 224) = 0;
  *((_DWORD *)this + 225) = 0;
  *((_DWORD *)this + 226) = -1;
  *((_BYTE *)this + 908) = 0;
  *((_BYTE *)this + 910) = 0;
  *((_BYTE *)this + 911) = 0;
  *((_BYTE *)this + 912) = 0;
  *((_DWORD *)this + 229) = 0;
  *((_DWORD *)this + 830) = 0;
  *((_BYTE *)this + 3336) = 0;
  *((_BYTE *)this + 3337) = 0;
  *((_BYTE *)this + 3348) = 0;
  *((_DWORD *)this + 836) = 0;
  *((_DWORD *)this + 835) = 0;
  v2 = (char *)this + 3356;
  v3 = 40;
  do
  {
    ArraySort((int)v2, 12, 99, (int)sub_486CE0);
    v2 += 1192;
    --v3;
  }
  while ( v3 );
  *((_DWORD *)this + 12758) = 0;
  ((UIFrameWnd *)((char *)this + 51036))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51188))->UIFrameWnd();
  ((UIFrameWnd *)(this + 755))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51492))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51644))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51796))->UIFrameWnd();
  ((UIScene *)((char *)this + 51948))->_UIScene();
  ((UIScene *)(this + 769))->_UIScene();
  ((UIScene *)((char *)this + 52636))->_UIScene();
  ((UIScene *)((char *)this + 52980))->_UIScene();
  ((UIScene *)((char *)this + 53324))->_UIScene();
  ((UIScene *)((char *)this + 53668))->_UIScene();
  ((UIScene *)((char *)this + 54012))->_UIScene();
  ((UIScene *)((char *)this + 54356))->_UIScene();
  ((UIScene *)((char *)this + 54700))->_UIScene();
  ((UIFrameWnd *)((char *)this + 55044))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 55228,
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 55836))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 55988))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 56140,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 130892,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  *((_DWORD *)this + 51446) = 0;
  ((UIItem *)(UIItem *)this + 205788)->Refresh();
  ((UIItem *)(UIItem *)this + 207156)->Refresh();
  ((UIItem *)(UIItem *)this + 208524)->Refresh();
  `eh vector constructor iterator'(
    (char *)this + 209896,
    0x34u,
    5,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  ((UIWnd *)((char *)this + 210236))->ctor_D830();
  ((UIFrameWnd *)((char *)this + 210320))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 210472,
    0x98u,
    9,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 211840))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 211992))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212144))->UIFrameWnd();
  ((UIFrameWnd *)(this + 3122))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212448))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 212600,
    0x131Cu,
    5,
    (void (*)(void *))sub_486D20,
    (void (*)(void *))sub_486EF0);
  `eh vector constructor iterator'(
    (char *)this + 237060,
    0x158u,
    8,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIListBox *)((char *)this + 239812))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 241020))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 242228))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 243436))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 244644))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 245852))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 247060))->UpdateKeyCtrl();
  ((UIListBox *)(this + 3651))->UpdateKeyCtrl();
  ((UIWnd *)((char *)this + 249476))->ctor_9030();
  `eh vector constructor iterator'(
    (char *)this + 249784,
    0x248u,
    98,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 307040,
    0x248u,
    40,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 330400,
    0x248u,
    40,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  *(_DWORD *)this->_pad_000 = &off_56C590;
  *((_BYTE *)this + 881) = 0;
  *((_BYTE *)this + 880) = 0;
  *((_BYTE *)this + 878) = 0;
  *((_BYTE *)this + 877) = 0;
  *((_BYTE *)this + 879) = 0;
  *((_DWORD *)this + 833) = 0;
  *((_DWORD *)this + 832) = 0;
  *((_DWORD *)this + 831) = 0;
  *((_DWORD *)this + 76758) = 0;
  *((_DWORD *)this + 76759) = 0;
  *((_DWORD *)this + 51443) = 0;
  *((_DWORD *)this + 51444) = 0;
  *((_DWORD *)this + 51445) = 0;
  return (int)this->_pad_000;
}

// 0x004870C0
void UIWnd::ctor_70C0()
{
  *(_DWORD *)this->_pad_000 = &off_56C590;
  `eh vector destructor iterator'(
    (char *)this + 330400,
    0x248u,
    40,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 307040,
    0x248u,
    40,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 249784,
    0x248u,
    98,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIWnd *)((char *)this + 249476))->ctor_9130();
  ((UIListBox *)(this + 3651))->DeleteRow();
  ((UIListBox *)((char *)this + 247060))->DeleteRow();
  ((UIListBox *)((char *)this + 245852))->DeleteRow();
  ((UIListBox *)((char *)this + 244644))->DeleteRow();
  ((UIListBox *)((char *)this + 243436))->DeleteRow();
  ((UIListBox *)((char *)this + 242228))->DeleteRow();
  ((UIListBox *)((char *)this + 241020))->DeleteRow();
  ((UIListBox *)((char *)this + 239812))->DeleteRow();
  `eh vector destructor iterator'((char *)this + 237060, 0x158u, 8, (void (*)(void *))UIScene::Destroy2);
  `eh vector destructor iterator'((char *)this + 212600, 0x131Cu, 5, (void (*)(void *))sub_486EF0);
  ((UIFrameWnd *)((char *)this + 212448))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 3122))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212144))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 211992))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 211840))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 210472, 0x98u, 9, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 210320))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 210236))->ctor_D880();
  `eh vector destructor iterator'((char *)this + 209896, 0x34u, 5, (void (*)(void *))nullsub_1);
  ((UIItem *)(UIItem *)this + 208524)->UIItem();
  ((UIItem *)(UIItem *)this + 207156)->UIItem();
  ((UIItem *)(UIItem *)this + 205788)->UIItem();
  `eh vector destructor iterator'(
    (char *)this + 130892,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 56140,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 55988))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 55836))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 55228, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 55044))->_UIFrameWnd();
  ((UIScene *)((char *)this + 54700))->Destroy2();
  ((UIScene *)((char *)this + 54356))->Destroy2();
  ((UIScene *)((char *)this + 54012))->Destroy2();
  ((UIScene *)((char *)this + 53668))->Destroy2();
  ((UIScene *)((char *)this + 53324))->Destroy2();
  ((UIScene *)((char *)this + 52980))->Destroy2();
  ((UIScene *)((char *)this + 52636))->Destroy2();
  ((UIScene *)(this + 769))->Destroy2();
  ((UIScene *)((char *)this + 51948))->Destroy2();
  ((UIFrameWnd *)((char *)this + 51796))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51644))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51492))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 755))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51188))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 51036))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x004909F0
int UIWnd::ctor_9F0()
{
  UIWnd *v2; // eax
  char *v3; // ebp
  UIWnd *v5; // [esp+10h] [ebp-18h]
  int v6; // [esp+14h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_BYTE *)this + 360) = 0;
  *((_BYTE *)this + 367) = 0;
  *((_DWORD *)this + 92) = 0;
  *((_DWORD *)this + 93) = 0;
  *((_DWORD *)this + 94) = 7;
  *((_DWORD *)this + 95) = 0;
  ((UIFrameWnd *)((char *)this + 384))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 536))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 688))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 840))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 992))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1144))->UIFrameWnd();
  ((UIScene *)((char *)this + 1296))->_UIScene();
  ((UIScene *)((char *)this + 1640))->_UIScene();
  ((UIScene *)((char *)this + 1984))->_UIScene();
  ((UIScene *)((char *)this + 2328))->_UIScene();
  ((UIScene *)((char *)this + 2672))->_UIScene();
  ((UIScene *)((char *)this + 3016))->_UIScene();
  ((UIScene *)((char *)this + 3360))->_UIScene();
  ((UIScene *)((char *)this + 3704))->_UIScene();
  ((UIScene *)((char *)this + 4048))->_UIScene();
  ((UIFrameWnd *)(UIFrameWnd *)this + 61)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4560))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4712))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 4864,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 79616,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 154508,
    0x26FCu,
    5,
    (void (*)(void *))sub_490E90,
    (void (*)(void *))sub_4910B0);
  ((UIFrameWnd *)((char *)this + 204424))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 204576))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 204728))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 204880))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 205032))->UIFrameWnd();
  v2 = (UIWnd *)((char *)this + 205200);
  v5 = (UIWnd *)((char *)this + 205200);
  v6 = 5;
  v3 = (char *)this + 205206;
  while ( 1 )
  {
    *(_DWORD *)v2->_pad_000 = 0;
    *((_WORD *)v3 - 1) = 0;
    lstrcpyA(v3, g_SceneMgr.m_szUIString);
    lstrcpyA(v3 + 512, g_SceneMgr.m_szUIString);
    lstrcpyA(v3 + 542, g_SceneMgr.m_szUIString);
    lstrcpyA(v3 + 594, g_SceneMgr.m_szUIString);
    memset(v3 + 630, 0, 0x30u);
    *(_DWORD *)(v3 + 774) = 0;
    v3 += 852;
    v5 = (UIWnd *)((char *)v5 + 852);
    if ( !--v6 )
      break;
    v2 = v5;
  }
  ((UIItem *)(UIItem *)this + 209460)->Refresh();
  `eh vector constructor iterator'(
    (char *)this + 210828,
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)((char *)this + 212548))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212700))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212852))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 213004))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 213156))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 213308))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 213476,
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  *((_DWORD *)this + 53799) = -1;
  ((UIWnd *)((char *)this + 215200))->ctor_D830();
  ((UIFrameWnd *)((char *)this + 215284))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 215436,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 3195))->UIFrameWnd();
  ((UIListBox *)((char *)this + 217412))->UpdateKeyCtrl();
  *((_DWORD *)this + 54655) = -1;
  ((UIScene *)((char *)this + 218640))->_UIScene();
  ((UIScene *)((char *)this + 218984))->_UIScene();
  ((UIScene *)((char *)this + 219328))->_UIScene();
  *((_DWORD *)this + 54918) = -1;
  ((UIWnd *)((char *)this + 219676))->ctor_9030();
  *(_DWORD *)this->_pad_000 = &off_56D618;
  *((_BYTE *)this + 365) = 0;
  *((_BYTE *)this + 364) = 0;
  *((_BYTE *)this + 362) = 0;
  *((_BYTE *)this + 361) = 0;
  *((_BYTE *)this + 363) = 0;
  *((_DWORD *)this + 38624) = 0;
  *((_DWORD *)this + 38625) = 0;
  *((_DWORD *)this + 38626) = 0;
  return (int)this->_pad_000;
}

// 0x004912D0
void UIWnd::ctor_12D0()
{
  *(_DWORD *)this->_pad_000 = &off_56D618;
  ((UIWnd *)((char *)this + 219676))->ctor_9130();
  ((UIScene *)((char *)this + 219328))->Destroy2();
  ((UIScene *)((char *)this + 218984))->Destroy2();
  ((UIScene *)((char *)this + 218640))->Destroy2();
  ((UIListBox *)((char *)this + 217412))->DeleteRow();
  ((UIFrameWnd *)(this + 3195))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 215436,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 215284))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 215200))->ctor_D880();
  `eh vector destructor iterator'((char *)this + 213476, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)((char *)this + 213308))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 213156))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 213004))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212852))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212700))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 212548))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 210828, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIItem *)(UIItem *)this + 209460)->UIItem();
  ((UIFrameWnd *)((char *)this + 205032))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 204880))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 204728))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 204576))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 204424))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 154508, 0x26FCu, 5, (void (*)(void *))sub_4910B0);
  `eh vector destructor iterator'(
    (char *)this + 79616,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 4864,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 4712))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4560))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 61)->_UIFrameWnd();
  ((UIScene *)((char *)this + 4048))->Destroy2();
  ((UIScene *)((char *)this + 3704))->Destroy2();
  ((UIScene *)((char *)this + 3360))->Destroy2();
  ((UIScene *)((char *)this + 3016))->Destroy2();
  ((UIScene *)((char *)this + 2672))->Destroy2();
  ((UIScene *)((char *)this + 2328))->Destroy2();
  ((UIScene *)((char *)this + 1984))->Destroy2();
  ((UIScene *)((char *)this + 1640))->Destroy2();
  ((UIScene *)((char *)this + 1296))->Destroy2();
  ((UIFrameWnd *)((char *)this + 1144))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 992))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 840))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 688))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 536))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 384))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00498820
int UIWnd::ctor_8820()
{
  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_DWORD *)this + 26) = 0;
  *((_BYTE *)this + 620) = 0;
  *((_DWORD *)this + 157) = 0;
  *((_BYTE *)this + 633) = 0;
  *((_DWORD *)this + 159) = 0;
  *((_DWORD *)this + 160) = 0;
  *((_DWORD *)this + 161) = 0;
  *((_DWORD *)this + 162) = 0;
  *((_BYTE *)this + 653) = 0;
  *((_BYTE *)this + 654) = 0;
  *((_BYTE *)this + 655) = 0;
  *((_DWORD *)this + 164) = 0;
  ((UIFrameWnd *)((char *)this + 660))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 812))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 964))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1116))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1268))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1420))->UIFrameWnd();
  ((UIScene *)((char *)this + 1572))->_UIScene();
  ((UIScene *)((char *)this + 1916))->_UIScene();
  ((UIScene *)((char *)this + 2260))->_UIScene();
  ((UIScene *)((char *)this + 2604))->_UIScene();
  ((UIScene *)((char *)this + 2948))->_UIScene();
  ((UIScene *)((char *)this + 3292))->_UIScene();
  ((UIScene *)((char *)this + 3636))->_UIScene();
  ((UIScene *)((char *)this + 3980))->_UIScene();
  ((UIScene *)((char *)this + 4324))->_UIScene();
  ((UIFrameWnd *)((char *)this + 4668))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4836))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4988))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 5140,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 79892,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIItem *)(UIItem *)this + 154784)->Refresh();
  `eh vector constructor iterator'(
    (char *)this + 156152,
    0x131Cu,
    5,
    (void (*)(void *))sub_498C90,
    (void (*)(void *))sub_498E60);
  ((UIFrameWnd *)((char *)this + 180612))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180764))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180916))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2663))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 181236))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 181388,
    0x158u,
    6,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)this + 183452,
    0xF8u,
    6,
    (void (*)(void *))UIStatic::UIStatic,
    (void (*)(void *))UIWnd::~UIWnd);
  ((UIFrameWnd *)((char *)this + 184940))->UIFrameWnd();
  ((UIWnd *)((char *)this + 185092))->ctor_D830();
  ((UIFrameWnd *)((char *)this + 185176))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 185328,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)((char *)this + 187152))->UpdateKeyCtrl();
  ((UIListBox *)(this + 2770))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 189568))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 190776))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 191984))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 193192))->UpdateKeyCtrl();
  `eh vector constructor iterator'(
    (char *)this + 194400,
    0x34u,
    5,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  ((UIScene *)((char *)this + 194756))->_UIScene();
  ((UIScene *)((char *)this + 195100))->_UIScene();
  ((UIScene *)((char *)this + 195444))->_UIScene();
  *((_DWORD *)this + 48947) = -1;
  ((UIWnd *)((char *)this + 195792))->ctor_9030();
  `eh vector constructor iterator'(
    (char *)this + 196100,
    0x248u,
    60,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 231140,
    0x248u,
    60,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  *(_DWORD *)this->_pad_000 = &off_56E170;
  *((_BYTE *)this + 625) = 0;
  *((_BYTE *)this + 624) = 0;
  *((_BYTE *)this + 622) = 0;
  *((_BYTE *)this + 621) = 0;
  *((_BYTE *)this + 623) = 0;
  *((_DWORD *)this + 38693) = 0;
  *((_DWORD *)this + 38694) = 0;
  *((_DWORD *)this + 38695) = 0;
  return (int)this->_pad_000;
}

// 0x00499030
void UIWnd::ctor_9030_0()
{
  *(_DWORD *)this->_pad_000 = &off_56E170;
  `eh vector destructor iterator'(
    (char *)this + 231140,
    0x248u,
    60,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 196100,
    0x248u,
    60,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIWnd *)((char *)this + 195792))->ctor_9130();
  ((UIScene *)((char *)this + 195444))->Destroy2();
  ((UIScene *)((char *)this + 195100))->Destroy2();
  ((UIScene *)((char *)this + 194756))->Destroy2();
  `eh vector destructor iterator'((char *)this + 194400, 0x34u, 5, (void (*)(void *))nullsub_1);
  ((UIListBox *)((char *)this + 193192))->DeleteRow();
  ((UIListBox *)((char *)this + 191984))->DeleteRow();
  ((UIListBox *)((char *)this + 190776))->DeleteRow();
  ((UIListBox *)((char *)this + 189568))->DeleteRow();
  ((UIListBox *)(this + 2770))->DeleteRow();
  ((UIListBox *)((char *)this + 187152))->DeleteRow();
  `eh vector destructor iterator'(
    (char *)this + 185328,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 185176))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 185092))->ctor_D880();
  ((UIFrameWnd *)((char *)this + 184940))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 183452, 0xF8u, 6, (void (*)(void *))UIWnd::~UIWnd);
  `eh vector destructor iterator'((char *)this + 181388, 0x158u, 6, (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)((char *)this + 181236))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 2663))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180916))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180764))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 180612))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 156152, 0x131Cu, 5, (void (*)(void *))sub_498E60);
  ((UIItem *)(UIItem *)this + 154784)->UIItem();
  `eh vector destructor iterator'(
    (char *)this + 79892,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 5140,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 4988))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4836))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4668))->_UIFrameWnd();
  ((UIScene *)((char *)this + 4324))->Destroy2();
  ((UIScene *)((char *)this + 3980))->Destroy2();
  ((UIScene *)((char *)this + 3636))->Destroy2();
  ((UIScene *)((char *)this + 3292))->Destroy2();
  ((UIScene *)((char *)this + 2948))->Destroy2();
  ((UIScene *)((char *)this + 2604))->Destroy2();
  ((UIScene *)((char *)this + 2260))->Destroy2();
  ((UIScene *)((char *)this + 1916))->Destroy2();
  ((UIScene *)((char *)this + 1572))->Destroy2();
  ((UIFrameWnd *)((char *)this + 1420))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1268))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1116))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 964))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 812))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 660))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x004A2450
void UIWnd::ctor_2450()
{
  *(_DWORD *)this->_pad_000 = &off_56F040;
  sub_4A6600((int)this);
  ((UIFrameWnd *)((char *)this + 176092))->_UIFrameWnd();
  ((UIScene *)((char *)this + 175696))->Destroy2();
  `eh vector destructor iterator'((char *)this + 174856, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 174688))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 174080, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 155140, 0xECCu, 5, (void (*)(void *))sub_4A22E0);
  ((UIFrameWnd *)(this + 2279))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154820))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154668))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154516))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 79608,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 4856,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 4704))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4552))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4384))->_UIFrameWnd();
  ((UIScene *)((char *)this + 4040))->Destroy2();
  ((UIScene *)((char *)this + 3696))->Destroy2();
  ((UIScene *)((char *)this + 3352))->Destroy2();
  ((UIScene *)((char *)this + 3008))->Destroy2();
  ((UIScene *)((char *)this + 2664))->Destroy2();
  ((UIScene *)((char *)this + 2320))->Destroy2();
  ((UIScene *)((char *)this + 1976))->Destroy2();
  ((UIScene *)(this + 24))->Destroy2();
  ((UIScene *)((char *)this + 1288))->Destroy2();
  ((UIFrameWnd *)((char *)this + 1136))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 984))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 832))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 10))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 528))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 376))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x004A6F10
int UIWnd::ctor_6F10()
{
  UIWnd *v2; // eax
  CHAR *v3; // ebp
  bool v4; // zf
  UIWnd *v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 25) = 0;
  ((UIFrameWnd *)((char *)this + 364))->UIFrameWnd();
  v2 = (UIWnd *)((char *)this + 548);
  v6 = (UIWnd *)((char *)this + 548);
  v7 = 28;
  v3 = (char *)this + 608;
  while ( 1 )
  {
    *(_DWORD *)v2->_pad_000 = 0;
    lstrcpyA(v3 - 32, g_SceneMgr.m_szUIString);
    lstrcpyA(v3, g_SceneMgr.m_szUIString);
    memset(v3 + 532, 0, 0x18u);
    v3 += 760;
    v4 = v7 == 1;
    v6 = (UIWnd *)((char *)v6 + 760);
    --v7;
    if ( v4 )
      break;
    v2 = v6;
  }
  *((_BYTE *)this + 21841) = 0;
  *((_BYTE *)this + 21842) = 1;
  *((_BYTE *)this + 21843) = 1;
  *((_DWORD *)this + 5461) = 0;
  *((_DWORD *)this + 5462) = 0;
  *((_DWORD *)this + 5463) = 1127481344;
  *((_DWORD *)this + 5861) = 300;
  *((_DWORD *)this + 5862) = 0;
  *((_DWORD *)this + 5863) = 0;
  ((UIFrameWnd *)((char *)this + 23456))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 23608))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 330)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 23912))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 24064))->UIFrameWnd();
  ((UIScene *)((char *)this + 24216))->_UIScene();
  ((UIScene *)((char *)this + 24560))->_UIScene();
  ((UIScene *)((char *)this + 24904))->_UIScene();
  ((UIScene *)((char *)this + 25248))->_UIScene();
  ((UIScene *)((char *)this + 25592))->_UIScene();
  ((UIScene *)((char *)this + 25936))->_UIScene();
  ((UIScene *)((char *)this + 26280))->_UIScene();
  ((UIScene *)((char *)this + 26624))->_UIScene();
  ((UIScene *)((char *)this + 26968))->_UIScene();
  ((UIFrameWnd *)((char *)this + 27312))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27480))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27632))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 27784,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 102536,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 177428))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 177580))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 177732))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 177884))->UIFrameWnd();
  ((UIWnd *)((char *)this + 178036))->ctor_9030();
  ((UIWnd *)((char *)this + 178344))->ctor_9030();
  ((UIFrameWnd *)((char *)this + 178652))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 178804))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 178956))->UIFrameWnd();
  ((UIScene *)((char *)this + 179108))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 179508,
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)this + 181228,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 181988,
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)this + 183708,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 184468,
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *((_BYTE *)this + 185228) = 1;
  ((UIScene *)(this + 2724))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 185576,
    0x248u,
    168,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 283704,
    0x248u,
    168,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIScene *)((char *)this + 381816))->_UIScene();
  ((UIScene *)(this + 5620))->_UIScene();
  sub_4A6730((char *)this + 382744);
  *((_BYTE *)this + 383180) = 0;
  *((_DWORD *)this + 95794) = 0;
  *((_DWORD *)this + 95793) = 0;
  *((_BYTE *)this + 383200) = 0;
  *((_DWORD *)this + 95799) = 0;
  *((_DWORD *)this + 95798) = 0;
  ((UIWnd *)((char *)this + 383300))->ctor_D830();
  ((UIWnd *)this + 5638)->ctor_D830();
  `eh vector constructor iterator'(
    (char *)this + 383468,
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)((char *)this + 385188))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 385340))->UIFrameWnd();
  ((UIWnd *)this + 5669)->ctor_D830();
  ((UIFrameWnd *)((char *)this + 385576))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 385728))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 385880))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 386032))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 386184))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 386336,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 388160,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)((char *)this + 389984))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 391192))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 392400))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 393608))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 394816))->UpdateKeyCtrl();
  ((UIListBox *)((char *)this + 396024))->UpdateKeyCtrl();
  ((UIFrameWnd *)((char *)this + 397248))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 397400))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 397552))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 397720))->UIFrameWnd();
  ((UIWnd *)((char *)this + 397872))->ctor_D830();
  ((UIScene *)((char *)this + 397972))->_UIScene();
  ((UIScene *)((char *)this + 398316))->_UIScene();
  ((UIScene *)((char *)this + 398660))->_UIScene();
  ((UIScene *)((char *)this + 399004))->_UIScene();
  ((UIScene *)((char *)this + 399348))->_UIScene();
  ((UIScene *)((char *)this + 399692))->_UIScene();
  *((_DWORD *)this + 100009) = 0;
  sub_40CC60((int)this + 400040);
  ((UIItem *)(UIItem *)this + 400080)->Refresh();
  ((UIItem *)(UIItem *)this + 401448)->Refresh();
  *(_DWORD *)this->_pad_000 = &off_56F29C;
  dword_DE5FA0 = 0;
  unk_DE5FA4 = 0;
  dword_DE5F98 = 0;
  word_DE5FA8 = 0;
  LOBYTE(dword_DE5F9C) = 0;
  *((_DWORD *)this + 44354) = 0;
  *((_DWORD *)this + 44355) = 0;
  *((_DWORD *)this + 44356) = 0;
  *((_BYTE *)this + 383184) = 1;
  *((_BYTE *)this + 383185) = 0;
  *((_BYTE *)this + 383186) = 1;
  *((_BYTE *)this + 383187) = 1;
  *((_DWORD *)this + 95797) = 0;
  *((_DWORD *)this + 95802) = 100;
  *((_DWORD *)this + 95801) = 1000;
  *((_DWORD *)this + 5457) = 0;
  *((_DWORD *)this + 130) = 0;
  *((_DWORD *)this + 129) = 0;
  *((_DWORD *)this + 134) = 0;
  *((_DWORD *)this + 133) = 0;
  *((_DWORD *)this + 132) = 0;
  *((_DWORD *)this + 131) = 0;
  *((_DWORD *)this + 136) = 0;
  *((_DWORD *)this + 135) = 0;
  return (int)this->_pad_000;
}

// 0x004A7690
UIWnd::~UIWnd()
{
  UIWnd *v2; // edi

  *(_DWORD *)this->_pad_000 = &off_56F29C;
  v2 = (UIWnd *)((char *)this + 178036);
  (*(void (**)(char *))(*((_DWORD *)this + 44509) + 12))((char *)this + 178036);
  ((UIItem *)(UIItem *)this + 401448)->UIItem();
  ((UIItem *)(UIItem *)this + 400080)->UIItem();
  CCBStageRole_Init((int)this + 400040);
  ((UIScene *)((char *)this + 399692))->Destroy2();
  ((UIScene *)((char *)this + 399348))->Destroy2();
  ((UIScene *)((char *)this + 399004))->Destroy2();
  ((UIScene *)((char *)this + 398660))->Destroy2();
  ((UIScene *)((char *)this + 398316))->Destroy2();
  ((UIScene *)((char *)this + 397972))->Destroy2();
  ((UIWnd *)((char *)this + 397872))->ctor_D880();
  ((UIFrameWnd *)((char *)this + 397720))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 397552))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 397400))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 397248))->_UIFrameWnd();
  ((UIListBox *)((char *)this + 396024))->DeleteRow();
  ((UIListBox *)((char *)this + 394816))->DeleteRow();
  ((UIListBox *)((char *)this + 393608))->DeleteRow();
  ((UIListBox *)((char *)this + 392400))->DeleteRow();
  ((UIListBox *)((char *)this + 391192))->DeleteRow();
  ((UIListBox *)((char *)this + 389984))->DeleteRow();
  `eh vector destructor iterator'(
    (char *)this + 388160,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'(
    (char *)this + 386336,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 386184))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 386032))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 385880))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 385728))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 385576))->_UIFrameWnd();
  ((UIWnd *)this + 5669)->ctor_D880();
  ((UIFrameWnd *)((char *)this + 385340))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 385188))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 383468, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIWnd *)this + 5638)->ctor_D880();
  ((UIWnd *)((char *)this + 383300))->ctor_D880();
  sub_4A67B0((int)this + 382744);
  ((UIScene *)(this + 5620))->Destroy2();
  ((UIScene *)((char *)this + 381816))->Destroy2();
  `eh vector destructor iterator'(
    (char *)this + 283704,
    0x248u,
    168,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 185576,
    0x248u,
    168,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIScene *)(this + 2724))->Destroy2();
  `eh vector destructor iterator'((char *)this + 184468, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 183708, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 181988, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  `eh vector destructor iterator'((char *)this + 181228, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 179508, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIScene *)((char *)this + 179108))->Destroy2();
  ((UIFrameWnd *)((char *)this + 178956))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 178804))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 178652))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 178344))->ctor_9130();
  v2->ctor_9130();
  ((UIFrameWnd *)((char *)this + 177884))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 177732))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 177580))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 177428))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 102536,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 27784,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 27632))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27480))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 27312))->_UIFrameWnd();
  ((UIScene *)((char *)this + 26968))->Destroy2();
  ((UIScene *)((char *)this + 26624))->Destroy2();
  ((UIScene *)((char *)this + 26280))->Destroy2();
  ((UIScene *)((char *)this + 25936))->Destroy2();
  ((UIScene *)((char *)this + 25592))->Destroy2();
  ((UIScene *)((char *)this + 25248))->Destroy2();
  ((UIScene *)((char *)this + 24904))->Destroy2();
  ((UIScene *)((char *)this + 24560))->Destroy2();
  ((UIScene *)((char *)this + 24216))->Destroy2();
  ((UIFrameWnd *)((char *)this + 24064))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 23912))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 330)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 23608))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 23456))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 364))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x004B01D0
int UIWnd::ctor_1D0()
{
  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_BYTE *)this + 360) = 0;
  *((_DWORD *)this + 91) = 0;
  ((UIFrameWnd *)((char *)this + 368))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 520))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 672))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 824))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 976))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1128))->UIFrameWnd();
  ((UIScene *)((char *)this + 1280))->_UIScene();
  ((UIScene *)((char *)this + 1624))->_UIScene();
  ((UIScene *)((char *)this + 1968))->_UIScene();
  ((UIScene *)(this + 34))->_UIScene();
  ((UIScene *)((char *)this + 2656))->_UIScene();
  ((UIScene *)((char *)this + 3000))->_UIScene();
  ((UIScene *)((char *)this + 3344))->_UIScene();
  ((UIScene *)((char *)this + 3688))->_UIScene();
  ((UIScene *)((char *)this + 4032))->_UIScene();
  ((UIFrameWnd *)((char *)this + 4376))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4544))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4696))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 4848,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 79600,
    0x248u,
    128,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 154492))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154644))->UIFrameWnd();
  ((UIStatic *)((char *)this + 154796))->UIStatic();
  ((UIStatic *)((char *)this + 155044))->UIStatic();
  ((UIScene *)((char *)this + 155292))->_UIScene();
  ((UIScene *)((char *)this + 155636))->_UIScene();
  ((UIScene *)((char *)this + 155980))->_UIScene();
  `eh vector constructor iterator'(
    (char *)this + 156360,
    0xDE8u,
    36,
    (void (*)(void *))sub_4549A0,
    (void (*)(void *))sub_454AA0);
  ((UIScene *)((char *)this + 284520))->_UIScene();
  ((UIScene *)((char *)this + 284864))->_UIScene();
  ((UIWnd *)((char *)this + 285224))->ctor_BCE0();
  ((UIWnd *)((char *)this + 285504))->ctor_BCE0();
  ((UIWnd *)((char *)this + 285776))->ctor_BCE0();
  ((UIFrameWnd *)((char *)this + 286048))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 3975)->UIFrameWnd();
  *((_DWORD *)this + 71588) = 92;
  *((_DWORD *)this + 71589) = 610;
  *((_DWORD *)this + 71590) = 0;
  *((_DWORD *)this + 71591) = 0;
  *((_DWORD *)this + 71592) = 0;
  *((_DWORD *)this + 71593) = 0;
  ((UIItem *)(UIItem *)this + 286384)->Refresh();
  ((UIItem *)(UIItem *)this + 287752)->Refresh();
  ((UIItem *)(UIItem *)this + 289120)->Refresh();
  *(_DWORD *)this->_pad_000 = &off_56F33C;
  *((_DWORD *)this + 38620) = 0;
  *((_DWORD *)this + 38621) = 0;
  *((_DWORD *)this + 38622) = 0;
  *((_DWORD *)this + 71594) = 0;
  memset((char *)this + 156324, 0, 0x24u);
  return (int)this->_pad_000;
}

// 0x004B0540
void UIWnd::ctor_540()
{
  *(_DWORD *)this->_pad_000 = &off_56F33C;
  ((UIItem *)(UIItem *)this + 289120)->UIItem();
  ((UIItem *)(UIItem *)this + 287752)->UIItem();
  ((UIItem *)(UIItem *)this + 286384)->UIItem();
  ((UIFrameWnd *)(UIFrameWnd *)this + 3975)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 286048))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 285776))->~UIWnd();
  ((UIWnd *)((char *)this + 285504))->~UIWnd();
  ((UIWnd *)((char *)this + 285224))->~UIWnd();
  ((UIScene *)((char *)this + 284864))->Destroy2();
  ((UIScene *)((char *)this + 284520))->Destroy2();
  `eh vector destructor iterator'((char *)this + 156360, 0xDE8u, 36, (void (*)(void *))sub_454AA0);
  ((UIScene *)((char *)this + 155980))->Destroy2();
  ((UIScene *)((char *)this + 155636))->Destroy2();
  ((UIScene *)((char *)this + 155292))->Destroy2();
  ((UIWnd *)((char *)this + 155044))->~UIWnd();
  ((UIWnd *)((char *)this + 154796))->~UIWnd();
  ((UIFrameWnd *)((char *)this + 154644))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 154492))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 79600,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 4848,
    0x248u,
    128,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 4696))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4544))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4376))->_UIFrameWnd();
  ((UIScene *)((char *)this + 4032))->Destroy2();
  ((UIScene *)((char *)this + 3688))->Destroy2();
  ((UIScene *)((char *)this + 3344))->Destroy2();
  ((UIScene *)((char *)this + 3000))->Destroy2();
  ((UIScene *)((char *)this + 2656))->Destroy2();
  ((UIScene *)(this + 34))->Destroy2();
  ((UIScene *)((char *)this + 1968))->Destroy2();
  ((UIScene *)((char *)this + 1624))->Destroy2();
  ((UIScene *)((char *)this + 1280))->Destroy2();
  ((UIFrameWnd *)((char *)this + 1128))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 976))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 824))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 672))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 520))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 368))->_UIFrameWnd();
  this->~UIWnd();
}

// 0x004B7510
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56F404;
  sub_4B7AF0((gbRefObject **)this);
  sub_4B6FB0((int)this);
}

// 0x004B7CE0
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56F450;
  sub_4B7F00((gbRefObject **)this);
  sub_4B6FB0((int)this);
}

// 0x004BEF50
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_56F580;
  sub_4BF170((gbRefObject **)this);
  sub_4BC7B0((char *)this + 1108);
  sub_4B6FB0((int)this);
}

// 0x00504080
UIWnd::~UIWnd()
{
  *this = (UIWnd **)&off_56FD78;
  sub_5040D0(this);
  sub_41C090((void ***)this);
}

// 0x005160A0
_DWORD * UIWnd::ctor_60A0(int a2)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)this->_pad_000 = &off_5704A8;
  sub_516170(this);
  *((_DWORD *)this + 290) = a2;
  return this->_pad_000;
}

// 0x00516120
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_5704A8;
  sub_516170(this);
  this->~UIWnd();
}

// 0x00519310
_DWORD * UIWnd::ctor_9310()
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)this->_pad_000 = &off_5704C8;
  ((CCBUI *)this)->OnMessage();
  return this->_pad_000;
}

// 0x00519380
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_5704C8;
  ((CCBUI *)this)->OnMessage();
  this->~UIWnd();
}

// 0x00519B60
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_5704E4;
  ((CCBUI *)this)->Render();
  this->~UIWnd();
}

// 0x0051A3B0
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_570500;
  sub_51A400(this);
  this->~UIWnd();
}

// 0x0051ACB0
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_57051C;
  ((CCBControlWindow *)this)->CheckKeyInput();
  this->~UIWnd();
}

// 0x0051B180
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_570538;
  ((CCBItemWindow *)this)->Reset();
  this->~UIWnd();
}

// 0x0051B690
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_570554;
  sub_51B6E0(this);
  this->~UIWnd();
}

// 0x0051BC00
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_570570;
  ((CCBMagicWindow *)this)->OnMessage();
  this->~UIWnd();
}

// 0x0051C280
UIWnd::~UIWnd()
{
  *(_DWORD *)this->_pad_000 = &off_57058C;
  ((CCBSkillWindow *)this)->Reset();
  this->~UIWnd();
}

// 0x00523F30
int UIWnd::ctor_3F30()
{
  UIWnd *v2; // ecx
  char *v3; // eax
  int v4; // edx
  char *v5; // ebp
  char *v6; // ebp
  _DWORD *v7; // ebp

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_DWORD *)this + 24) = 0;
  *((_DWORD *)this + 25) = 0;
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 512))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 664))->UIFrameWnd();
  ((UIFrameWnd *)(this + 12))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 968))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1120))->UIFrameWnd();
  ((UIWnd *)((char *)this + 1272))->ctor_BCE0();
  ((UIScene *)((char *)this + 1544))->_UIScene();
  ((UIScene *)((char *)this + 1888))->_UIScene();
  *((_DWORD *)this + 558) = 0;
  sub_522030((_DWORD *)this + 559);
  *((_BYTE *)this + 3868) = 0;
  *((_DWORD *)this + 968) = 0;
  ((UIItem *)(UIItem *)this + 3876)->Refresh();
  v2 = (UIWnd *)((char *)this + 5296);
  *((_DWORD *)this + 1311) = 0;
  *((_DWORD *)this + 1312) = 0;
  *((_DWORD *)this + 1313) = 0;
  *((_DWORD *)this + 1314) = 0;
  *((_DWORD *)this + 1316) = 0;
  *((_DWORD *)this + 1317) = 0;
  v3 = (char *)this + 5332;
  v4 = 4;
  do
  {
    v5 = (char *)v3 - 24;
    *(_DWORD *)v2->_pad_000 = 0;
    *((_DWORD *)v3 - 8) = 0;
    *((_DWORD *)v3 - 7) = 0;
    *(_DWORD *)v5 = 0;
    v2 = (UIWnd *)((char *)v2 + 48);
    *((_DWORD *)v5 + 1) = 0;
    *((_DWORD *)v5 + 2) = 0;
    v6 = (char *)v3 - 12;
    *((_DWORD *)v3 - 3) = 0;
    *((_DWORD *)v6 + 1) = 0;
    *((_DWORD *)v6 + 2) = 0;
    v7 = v3;
    v3 += 48;
    --v4;
    *v7 = 0;
    v7[1] = 0;
    v7[2] = 0;
  }
  while ( v4 );
  *((_BYTE *)this + 5272) = 0;
  *((_BYTE *)this + 5273) = 0;
  *((_BYTE *)this + 5274) = 0;
  *((_BYTE *)this + 5275) = 0;
  *((_BYTE *)this + 5276) = 0;
  *((_BYTE *)this + 5277) = 0;
  *((_BYTE *)this + 5278) = 0;
  *((_DWORD *)this + 1320) = 1065353216;
  *((_DWORD *)this + 1321) = 0;
  *((_DWORD *)this + 1322) = 0;
  *((_DWORD *)this + 1323) = 0;
  *((_DWORD *)this + 1372) = 0;
  memset((char *)this + 5296, 0, 0xC0u);
  *(_DWORD *)this->_pad_000 = &off_570630;
  return (int)this->_pad_000;
}

// 0x00524130
void UIWnd::ctor_4130()
{
  *(_DWORD *)this->_pad_000 = &off_570630;
  ((UIItem *)(UIItem *)this + 3876)->UIItem();
  sub_522120((char *)this + 2236);
  ((UIScene *)((char *)this + 1888))->Destroy2();
  ((UIScene *)((char *)this + 1544))->Destroy2();
  ((UIWnd *)((char *)this + 1272))->~UIWnd();
  ((UIFrameWnd *)((char *)this + 1120))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 968))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 12))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 664))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 512))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->_UIFrameWnd();
  this->~UIWnd();
}

// 0x00525120
int UIWnd::ctor_5120()
{
  char *v2; // edi
  int v3; // ebp
  char *v4; // edi
  int v5; // ebp

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  `eh vector constructor iterator'(
    (char *)this + 352,
    0xF8u,
    5,
    (void (*)(void *))UIStatic::UIStatic,
    (void (*)(void *))UIWnd::~UIWnd);
  ((UIFrameWnd *)((char *)this + 1624))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1776))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1928))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 2080,
    0x158u,
    3,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIStatic *)((char *)this + 3164))->UIStatic();
  ((UIStatic *)((char *)this + 3412))->UIStatic();
  ((UIScene *)((char *)this + 3660))->_UIScene();
  ((UIWnd *)((char *)this + 4004))->ctor_9030();
  ((UIWnd *)((char *)this + 4312))->ctor_9030();
  ((UIWnd *)((char *)this + 4620))->ctor_9030();
  v2 = (char *)this + 4928;
  v3 = 2;
  do
  {
    ((void (*)(char *))gbVec3D::`default constructor closure')(v2);
    v2 += 12;
    --v3;
  }
  while ( v3 );
  ((UIFrameWnd *)((char *)this + 4952))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5104))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 73)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5408))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5560))->UIFrameWnd();
  ((UIFrameWnd *)(this + 84))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5864))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 6016))->UIFrameWnd();
  *((_BYTE *)this + 6192) = 0;
  *((_DWORD *)this + 1547) = 0;
  *((_DWORD *)this + 1546) = 0;
  *((_BYTE *)this + 6204) = 0;
  ((UIWnd *)((char *)this + 6208))->ctor_F7F0();
  UIWnd_Init_444F60((UIWnd *)((char *)this + 6468));
  ((UIFrameWnd *)((char *)this + 6660))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 6812))->UIFrameWnd();
  v4 = (char *)this + 6972;
  v5 = 5;
  do
  {
    ArraySort((int)v4, 800, 2, (int)sub_5254C0);
    v4 += 1608;
    --v5;
  }
  while ( v5 );
  *((_BYTE *)this + 15004) = 0;
  *((_DWORD *)this + 3752) = 0;
  *((_BYTE *)this + 15012) = 0;
  *((_BYTE *)this + 15018) = 0;
  *((_DWORD *)this + 3755) = 3;
  *((_DWORD *)this + 3758) = 0;
  *((_BYTE *)this + 15036) = 0;
  *((_BYTE *)this + 15037) = 0;
  *((_BYTE *)this + 15038) = 0;
  `eh vector constructor iterator'(
    (char *)this + 15068,
    0x248u,
    36,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 36092,
    0x248u,
    36,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 57116,
    0x248u,
    36,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 78140,
    0x248u,
    36,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  *((_BYTE *)this + 99196) = 0;
  *((_BYTE *)this + 99197) = 0;
  *((_DWORD *)this + 24800) = 0;
  ((UIItem *)(UIItem *)this + 99204)->Refresh();
  ((UIItem *)(UIItem *)this + 100572)->Refresh();
  *(_DWORD *)this->_pad_000 = &off_5706CC;
  *(_DWORD *)((char *)this + 15013) = 0;
  *((_BYTE *)this + 15017) = 0;
  *((_DWORD *)this + 3756) = 0;
  *((_BYTE *)this + 15028) = 0;
  *((_DWORD *)this + 3762) = 0;
  *((_DWORD *)this + 3761) = 0;
  *((_DWORD *)this + 3760) = 0;
  *((_DWORD *)this + 3766) = 0;
  *((_DWORD *)this + 3765) = 0;
  *((_DWORD *)this + 3764) = 0;
  *((_DWORD *)this + 3763) = 0;
  *((_DWORD *)this + 1550) = 0;
  *((_DWORD *)this + 1549) = 1;
  *((_BYTE *)this + 6176) = 0;
  *((_DWORD *)this + 1545) = 0;
  *((_WORD *)this + 1580) = (unsigned __int16)&unk_1010101;
  *((_BYTE *)this + 3162) = (unsigned __int8)&unk_1010101;
  return (int)this->_pad_000;
}

// 0x00525540
void UIWnd::ctor_5540()
{
  *(_DWORD *)this->_pad_000 = &off_5706CC;
  ((UIItem *)(UIItem *)this + 100572)->UIItem();
  ((UIItem *)(UIItem *)this + 99204)->UIItem();
  `eh vector destructor iterator'(
    (char *)this + 78140,
    0x248u,
    36,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 57116,
    0x248u,
    36,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 36092,
    0x248u,
    36,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 15068,
    0x248u,
    36,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIFrameWnd *)((char *)this + 6812))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 6660))->_UIFrameWnd();
  UIWnd_Destructor((UIWnd *)((char *)this + 6468));
  ((UIWnd *)((char *)this + 6208))->~UIWnd();
  ((UIFrameWnd *)((char *)this + 6016))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5864))->_UIFrameWnd();
  ((UIFrameWnd *)(this + 84))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5560))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5408))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 73)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 5104))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 4952))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4620))->ctor_9130();
  ((UIWnd *)((char *)this + 4312))->ctor_9130();
  ((UIWnd *)((char *)this + 4004))->ctor_9130();
  ((UIScene *)((char *)this + 3660))->Destroy2();
  ((UIWnd *)((char *)this + 3412))->~UIWnd();
  ((UIWnd *)((char *)this + 3164))->~UIWnd();
  `eh vector destructor iterator'((char *)this + 2080, 0x158u, 3, (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)((char *)this + 1928))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1776))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1624))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 352, 0xF8u, 5, (void (*)(void *))UIWnd::~UIWnd);
  this->~UIWnd();
}

// 0x005257B0
_DWORD * UIWnd::ctor_57B0(int a2)
{
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // ecx
  _DWORD *v12; // ebp
  gbRefObject **v13; // edi
  int v14; // edx
  int v15; // edx
  int (__stdcall **v16)(int); // ebp
  PalScript **v17; // edi
  int *v18; // ebx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // edx
  int v27; // edx
  int v28; // ecx
  int v29; // edx
  int v30; // ecx
  UIWnd *v31; // ebp
  int v32; // ebx
  UIWnd *v33; // ebp
  int v34; // ebx
  int v35; // edx
  UIWnd *v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // eax
  _BYTE id[3]; // [esp+130h] [ebp-D4h] BYREF
  char id_3; // [esp+133h] [ebp-D1h]
  int v43; // [esp+134h] [ebp-D0h] BYREF
  int v44; // [esp+138h] [ebp-CCh]
  int v45; // [esp+13Ch] [ebp-C8h]
  int v46; // [esp+140h] [ebp-C4h]
  int v47; // [esp+144h] [ebp-C0h] BYREF
  int v48; // [esp+148h] [ebp-BCh]
  int v49; // [esp+14Ch] [ebp-B8h]
  int v50; // [esp+150h] [ebp-B4h]
  int v51; // [esp+154h] [ebp-B0h] BYREF
  int v52; // [esp+158h] [ebp-ACh]
  int v53; // [esp+15Ch] [ebp-A8h]
  int v54; // [esp+160h] [ebp-A4h]
  int v55; // [esp+164h] [ebp-A0h] BYREF
  int v56; // [esp+168h] [ebp-9Ch]
  int v57; // [esp+16Ch] [ebp-98h]
  int v58; // [esp+170h] [ebp-94h]
  int v59; // [esp+174h] [ebp-90h] BYREF
  int v60; // [esp+178h] [ebp-8Ch]
  int v61; // [esp+17Ch] [ebp-88h]
  int v62; // [esp+180h] [ebp-84h]
  _DWORD v63[2]; // [esp+184h] [ebp-80h] BYREF
  int v64; // [esp+18Ch] [ebp-78h]
  int v65; // [esp+190h] [ebp-74h]
  _DWORD v66[2]; // [esp+194h] [ebp-70h] BYREF
  int v67; // [esp+19Ch] [ebp-68h]
  int v68; // [esp+1A0h] [ebp-64h]
  int a3[4]; // [esp+1A4h] [ebp-60h] BYREF
  _DWORD v70[4]; // [esp+1B4h] [ebp-50h] BYREF
  _DWORD v71[4]; // [esp+1C4h] [ebp-40h] BYREF
  _DWORD v72[4]; // [esp+1D4h] [ebp-30h] BYREF
  _DWORD v73[4]; // [esp+1E4h] [ebp-20h] BYREF
  _DWORD v74[4]; // [esp+1F4h] [ebp-10h] BYREF

  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 20) = *((_DWORD *)this + 22);
  *((_DWORD *)this + 21) = *((_DWORD *)this + 19) + *((_DWORD *)this + 23);
  ((UIListBox *)this)->SetSelTexture(-1, *((_DWORD *)this + 18), *((_DWORD *)this + 19), *((_DWORD *)this + 20), *((_DWORD *)this + 21), 0);
  *((_DWORD *)this + 24800) = a2;
  v3 = *((_DWORD *)this + 1238);
  v48 = 32;
  v47 = 168;
  v49 = 636;
  v50 = 136;
  (*(void (**)(char *, void *, int *, UIWnd *))(v3 + 16))((char *)this + 4952, &unk_AA0C00, &v47, this);
  ((UIWnd *)(UIWnd **)this + 1238)->CreateFromTemplate(aSubgameApprais_1, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  v4 = *((_DWORD *)this + 1276);
  v48 += 6;
  v47 += 24;
  v50 = v48 + 158;
  v49 = v47 + 428;
  (*(void (**)(char *, void *, int *, UIWnd *))(v4 + 16))((char *)this + 5104, &unk_AA0C00, &v47, this);
  ((UIWnd *)((char *)this + 5104))->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)&id[1] = 3103;
    id[0] = 0;
  }
  else
  {
    id[2] = 0;
    *(_WORD *)id = 7948;
  }
  id_3 = -1;
  ((UIWnd *)((char *)this + 5104))->GetChild((int)id);
  v5 = *((_DWORD *)this + 1466);
  v63[1] = 0;
  v63[0] = 0;
  v64 = 14;
  v65 = 600;
  (*(void (**)(char *, void *, _DWORD *, UIWnd *))(v5 + 16))((char *)this + 5864, &unk_AA0B00, v63, this);
  ((UIWnd *)(UIWnd **)this + 1466)->CreateFromTemplate(aUiGamemainuiCo_17, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  v6 = *((_DWORD *)this + 1504);
  v63[0] = 786;
  v64 = 800;
  (*(void (**)(char *, void *, _DWORD *, UIWnd *))(v6 + 16))((char *)this + 6016, &unk_AA0B00, v63, this);
  ((UIWnd *)(UIWnd **)this + 1504)->CreateFromTemplate(aUiGamemainuiCo_17, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  v7 = *((_DWORD *)this + 1552);
  v73[1] = 0;
  v73[0] = 16;
  v73[2] = 788;
  v73[3] = 92;
  (*(void (**)(char *, void *, _DWORD *, UIWnd *))(v7 + 16))((char *)this + 6208, &unk_AA0C00, v73, this);
  ((UIWnd *)(UIWnd **)this + 1552)->GetChildCount(aSubgameApprais_10, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  ((UIWnd *)(UIWnd **)this + 1552)->GetChildAt(aSubgameApprais_11, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  SetIntParam((char *)this + 6208, 0);
  ((UIWnd *)((char *)this + 6208))->FindChild(620.0);
  *((_DWORD *)this + 1605) = 1;
  *((_DWORD *)this + 1612) = 300;
  *((_DWORD *)this + 1610) = 1092616192;
  *((_DWORD *)this + 1607) = 255;
  ((UIWnd *)((char *)this + 6208))->FindChildByName(620.0);
  *((_DWORD *)this + 1580) = 1142620160;
  v8 = *((_DWORD *)this + 1352);
  v60 = 18;
  v59 = 64;
  v61 = 96;
  v62 = 42;
  (*(void (**)(char *, void *, int *, UIWnd *))(v8 + 16))((char *)this + 5408, &unk_AA0C00, &v59, this);
  v9 = *((_DWORD *)this + 1390);
  v60 = v62;
  v62 += 24;
  (*(void (**)(char *, void *, int *, UIWnd *))(v9 + 16))((char *)this + 5560, &unk_AA0C00, &v59, this);
  v10 = *((_DWORD *)this + 406);
  v70[1] = 136;
  v70[0] = 90;
  v70[2] = 714;
  v70[3] = 598;
  (*(void (**)(char *, void *, _DWORD *, UIWnd *))(v10 + 16))((char *)this + 1624, &unk_AA0C00, v70, this);
  ((UIWnd *)(UIWnd **)this + 406)->CreateFromTemplate(aSubgameApprais_2, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  v66[1] = 162;
  v66[0] = 120;
  v67 = 160;
  v68 = 208;
  v12 = (_DWORD *)&off_5706AC;
  v13 = (gbRefObject **)((char *)this + 352);
  do
  {
    LOBYTE(v11) = *(_BYTE *)(*((_DWORD *)this + 24800) + 1756);
    ((void (*)(gbRefObject **, _DWORD, _DWORD *, UIWnd *, char *, int))(*v13)[3].RefCount)(
      v13,
      *v12,
      v66,
      this,
      aSubgameApprais_3,
      v11);
    sub_440CE0(v13, aSubgameApprais_4, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
    ++v12;
    v66[0] = v67;
    v13 += 62;
    v67 += 40;
  }
  while ( (int)v12 < (int)&off_5706C0 );
  v14 = *((_DWORD *)this + 1314);
  v71[1] = 170;
  v71[0] = 326;
  v71[2] = 482;
  v71[3] = 202;
  (*(void (**)(char *, void *, _DWORD *, UIWnd *))(v14 + 16))((char *)this + 5256, &unk_AA0C21, v71, this);
  ((UIWnd *)((char *)this + 5256))->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)&id[1] = -5;
    id[0] = 31;
  }
  else
  {
    *(_WORD *)&id[1] = 8187;
    id[0] = -1;
  }
  id_3 = -1;
  ((UIWnd *)((char *)this + 5256))->GetChild((int)id);
  v52 = 146;
  v51 = 552;
  v53 = 597;
  v54 = 210;
  v16 = (int (__stdcall **)(int))&off_5706C0;
  v17 = (PalScript **)((char *)this + 2080);
  v18 = (int *)((char *)this + 3112);
  do
  {
    LOBYTE(v15) = *(_BYTE *)(*((_DWORD *)this + 24800) + 1756);
    (*(void (**)(PalScript **, int (__stdcall *)(int), int *, UIWnd *, char *, _DWORD, int))&(*v17)->_tail[20])(
      v17,
      *v16,
      &v51,
      this,
      aSubgameApprais_5,
      0,
      v15);
    v19 = v52;
    *v18 = v51;
    v20 = v53;
    v18[1] = v19;
    v21 = v54;
    v18[2] = v20;
    v18[3] = v21;
    v17->OpenScript(aSubgameApprais_7, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
    v15 = v53;
    ++v16;
    v18 += 4;
    v17 += 86;
    v51 = v53 + 2;
    v53 += 47;
  }
  while ( (int)v16 < (int)&off_5706CC );
  v22 = *((_DWORD *)this + 24800);
  v44 = 548;
  v43 = 213;
  v45 = 307;
  v46 = 568;
  LOBYTE(v22) = *(_BYTE *)(v22 + 1756);
  (*(void (**)(char *, void *, int *, UIWnd *, char *, int))(*((_DWORD *)this + 791) + 28))(
    (char *)this + 3164,
    &unk_AA0C16,
    &v43,
    this,
    aSubgameApprais_8,
    v22);
  v23 = v44;
  *((_DWORD *)this + 24791) = v43;
  v24 = v46;
  *((_DWORD *)this + 24792) = v23;
  v25 = v45;
  *((_DWORD *)this + 24793) = v45;
  v43 = v25 + 200;
  *((_DWORD *)this + 24794) = v24;
  v26 = *((_DWORD *)this + 24800);
  v45 = v25 + 294;
  LOBYTE(v26) = *(_BYTE *)(v26 + 1756);
  (*(void (**)(char *, void *, int *, UIWnd *, char *, int))(*((_DWORD *)this + 853) + 28))(
    (char *)this + 3412,
    &unk_AA0C17,
    &v43,
    this,
    aSubgameApprais_8,
    v26);
  v27 = v44;
  v72[1] = 573;
  v72[0] = 358;
  v72[2] = 448;
  *((_DWORD *)this + 24795) = v43;
  v28 = v45;
  v72[3] = 598;
  *((_DWORD *)this + 24796) = v27;
  v29 = v46;
  *((_DWORD *)this + 24797) = v28;
  v30 = *((_DWORD *)this + 24800);
  *((_DWORD *)this + 24798) = v29;
  LOBYTE(v29) = *(_BYTE *)(v30 + 1756);
  (*(void (**)(char *, void *, _DWORD *, UIWnd *, char *, _DWORD, int))(*((_DWORD *)this + 915) + 28))(
    (char *)this + 3660,
    &unk_AA0C18,
    v72,
    this,
    aUiGamemainuiMu_0,
    0,
    v29);
  (**((void (***)(char *, _DWORD))this + 915))((char *)this + 3660, 0);
  sub_439740((UIWnd *)((char *)this + 4004), (int)&unk_AA0C25, (int)this);
  SetFloatParam((char *)this + 4004, 600.0);
  sub_439850((int)this + 4004, 400, 320);
  v31 = (UIWnd *)this + 60;
  v32 = 5;
  do
  {
    *(_DWORD *)v31->_pad_000 = 0;
    sub_43A090((int)this + 4004, 1, 180.0);
    *((_DWORD *)this + 1062) = 58;
    v31 = (UIWnd *)((char *)v31 + 32);
    --v32;
    ++*((_DWORD *)this + 1018);
  }
  while ( v32 );
  sub_439740((UIWnd *)((char *)this + 4312), (int)&unk_AA0C26, (int)this);
  SetFloatParam((char *)this + 4312, 600.0);
  sub_439850((int)this + 4312, 400, 320);
  v33 = (UIWnd *)((char *)this + 4388);
  v34 = 5;
  do
  {
    *(_DWORD *)v33->_pad_000 = 0;
    sub_43A090((int)this + 4312, 1, 180.0);
    *((_DWORD *)this + 1139) = 58;
    v33 = (UIWnd *)((char *)v33 + 32);
    --v34;
    ++*((_DWORD *)this + 1095);
  }
  while ( v34 );
  v35 = *((_DWORD *)this + 444);
  *((_DWORD *)this + 1233) = -1029701632;
  *((_DWORD *)this + 1236) = -1029701632;
  *((_DWORD *)this + 1232) = -1017380864;
  *((_DWORD *)this + 1234) = 0;
  *((_DWORD *)this + 1235) = 1130102784;
  *((_DWORD *)this + 1237) = 0;
  v56 = 136;
  v55 = 90;
  v57 = 716;
  v58 = 603;
  (*(void (**)(char *, void *, int *, UIWnd *))(v35 + 16))((char *)this + 1776, &unk_AA0C19, &v55, this);
  ((UIWnd *)(UIWnd **)this + 444)->CreateFromTemplate(aSubgameApprais_9, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  (**((void (***)(char *, _DWORD))this + 444))((char *)this + 1776, 0);
  sub_439740((UIWnd *)((char *)this + 4620), (int)&unk_AA0C27, (int)this);
  SetFloatParam((char *)this + 4620, 580.0);
  sub_439850((int)this + 4620, 400, 346);
  v36 = (UIWnd *)((char *)this + 4696);
  v37 = 5;
  do
  {
    *(_DWORD *)v36->_pad_000 = 0;
    v36 = (UIWnd *)((char *)v36 + 32);
    --v37;
    ++*((_DWORD *)this + 1172);
  }
  while ( v37 );
  v38 = *((_DWORD *)this + 482);
  v56 = 164;
  v55 = 326;
  v57 = 482;
  v58 = 196;
  (*(void (**)(char *, void *, int *, UIWnd *))(v38 + 16))((char *)this + 1928, &unk_AA0C19, &v55, this);
  ((UIWnd *)((char *)this + 1928))->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)&id[1] = -5;
    id[0] = 31;
  }
  else
  {
    *(_WORD *)&id[1] = 8187;
    id[0] = -1;
  }
  id_3 = -1;
  ((UIWnd *)((char *)this + 1928))->GetChild((int)id);
  (**((void (***)(char *, _DWORD))this + 482))((char *)this + 1928, 0);
  v39 = *((_DWORD *)this + 1428);
  v74[1] = 158;
  v74[0] = 536;
  v74[2] = 581;
  v74[3] = 208;
  (*(void (**)(UIWnd *, void *, _DWORD *, UIWnd *))(v39 + 16))(this + 84, &unk_AA0C00, v74, this);
  ((UIWnd *)(UIWnd **)this + 1428)->CreateFromTemplate(aSubgameApprais_6, *(_BYTE *)(*((_DWORD *)this + 24800) + 1756));
  (**((void (***)(UIWnd *, _DWORD))this + 1428))(this + 84, 0);
  a3[0] = 300;
  a3[3] = 300;
  *((_DWORD *)this + 1542) = 45;
  *((_DWORD *)this + 1543) = 50;
  a3[1] = 200;
  a3[2] = 500;
  ((UIItem *)(UIItem *)this + 99204)->Create((int)&unk_ABE00B, (int)a3);
  ((UIItem *)(UIItem *)this + 99204)->SetData(31);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)&id[1] = -5;
    id[0] = 31;
  }
  else
  {
    *(_WORD *)&id[1] = 8187;
    id[0] = -1;
  }
  id_3 = -1;
  ((UIWnd *)((char *)this + 99204))->GetChild((int)id);
  ((UIItem *)(UIItem *)this + 100572)->Create((int)&unk_ABC00C, (int)a3);
  ((UIItem *)(UIItem *)this + 100572)->SetData(31);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)&id[1] = -5;
    id[0] = 31;
  }
  else
  {
    *(_WORD *)&id[1] = 8187;
    id[0] = -1;
  }
  id_3 = -1;
  ((UIWnd *)this + 1479)->GetChild((int)id);
  *((_DWORD *)this + 1614) = 120;
  *((_DWORD *)this + 1615) = 534;
  *((_DWORD *)this + 1616) = 420;
  *((_DWORD *)this + 1613) = 278;
  ((UINote *)((char *)this + 6468))->Create((int)&unk_AA0C22, (int)this + 6452, (int)this, aUiFlexNote);
  (**((void (***)(char *, _DWORD))this + 1617))((char *)this + 6468, 0);
  (*(void (**)(char *, void *, char *, UIWnd *))(*((_DWORD *)this + 1665) + 16))(
    (char *)this + 6660,
    &unk_AA0C22,
    (char *)this + 6452,
    this);
  ((UIWnd *)((char *)this + 6660))->SetShow(0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)&id[1] = -5;
    id[0] = 31;
  }
  else
  {
    *(_WORD *)&id[1] = 8187;
    id[0] = -1;
  }
  id_3 = -1;
  ((UIWnd *)((char *)this + 6660))->GetChild((int)id);
  (**((void (***)(char *, _DWORD))this + 1665))((char *)this + 6660, 0);
  (*(void (**)(char *, void *, char *, UIWnd *))(*((_DWORD *)this + 1703) + 16))(
    (char *)this + 6812,
    &unk_AA0C23,
    (char *)this + 6452,
    this);
  ((UIWnd *)((char *)this + 6812))->SetShow(0);
  (**((void (***)(char *, _DWORD))this + 1703))((char *)this + 6812, 0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)&id[1] = -5;
    id[0] = 31;
  }
  else
  {
    *(_WORD *)&id[1] = 8187;
    id[0] = -1;
  }
  id_3 = -1;
  return (_DWORD *)((UIWnd *)((char *)this + 6812))->GetChild((int)id);
}

// 0x00526A40
int UIWnd::ctor_6A40(int a2, int ( *a3)(int a2), int a4)
{
  int (__stdcall *v6)(int); // edx
  int v7; // eax
  int (__stdcall **v8)(int); // ecx
  int v9; // edi
  int (__stdcall **v10)(int); // ebp
  void (**v11)(UIWnd *, int); // edx
  char *Instance; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // ecx
  char *v16; // esi
  void (**v17)(char *, _DWORD); // edx
  void (**v18)(char *, _DWORD); // eax
  int v19; // ebp
  int *v20; // edi
  int v21; // edi
  UIWnd *v22; // ebp
  int v23; // ecx
  UIWnd *v24; // esi
  int v25; // edi
  int v26; // eax
  UIWnd *v27; // esi
  int v28; // edi
  void *v29; // [esp-8h] [ebp-24h]
  char *v30; // [esp-8h] [ebp-24h]
  int v31; // [esp-4h] [ebp-20h]
  int pOut; // [esp+10h] [ebp-Ch] BYREF
  int pOut2; // [esp+14h] [ebp-8h] BYREF
  int SkillNum; // [esp+18h] [ebp-4h]
  UIWnd *v35; // [esp+20h] [ebp+4h]

  switch ( a2 )
  {
    case 1000:
      if ( !a3 )
        return 1;
      sub_526300(this->_pad_000);
      sub_527130(this, *((_DWORD *)this + 3752));
      sub_5263C0((int)this);
      return 1;
    case 1001:
      v6 = a3;
      v7 = 0;
      v8 = (int (__stdcall **)(int))&off_5706AC;
      while ( a3 != *v8 )
      {
        ++v8;
        ++v7;
        if ( (int)v8 >= (int)&off_5706C0 )
        {
          v9 = 0;
          v10 = (int (__stdcall **)(int))&off_5706C0;
          v35 = (UIWnd *)((char *)this + 2080);
          do
          {
            if ( !*((_BYTE *)this + 6176) && v6 == *v10 )
            {
              if ( !*((_BYTE *)this + 15018) )
              {
                v11 = (void (**)(UIWnd *, int))*((_DWORD *)this + 1428);
                *((_BYTE *)this + 6176) = 1;
                (*v11)(this + 84, 1);
                *((_DWORD *)this + 1545) = v9;
                UIObj_SetState(v35, 0);
                *((_DWORD *)this + 1223) = 0;
                *((_DWORD *)this + 1222) = 0;
                *((_DWORD *)this + 1221) = 0;
              }
              v29 = off_5E7ECC;
              Instance = (char *)CScreenMode::GetInstance();
              ((CScreenMode *)Instance)->AudioSetPosition(v29, 1);
              v6 = a3;
            }
            ++v10;
            ++v9;
            v35 = (UIWnd *)((char *)v35 + 344);
          }
          while ( (int)v10 < (int)&off_5706CC );
          if ( (char *)v6 == (char *)&unk_AA0C16 )
          {
            if ( *((_BYTE *)this + 15018) )
              return 1;
            if ( *((_BYTE *)this + 6176) )
            {
              *((_DWORD *)this + 811) = 0;
              *((_BYTE *)this + 3232) = 0;
            }
            *((_BYTE *)this + 15012) = 1;
            *((_DWORD *)this + 873) = 0;
            *((_BYTE *)this + 3480) = 0;
            (**((void (***)(char *, int))this + 915))((char *)this + 3660, 1);
            if ( *((_DWORD *)this + 3758) )
              *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 0;
            else
              *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 1;
            if ( !*((_BYTE *)this + 3232) && !*((_BYTE *)this + 3480) )
            {
              v18 = (void (**)(char *, _DWORD))*((_DWORD *)this + 915);
              *((_BYTE *)this + 15012) = 0;
              (*v18)((char *)this + 3660, 0);
              *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 0;
            }
          }
          else
          {
            if ( (char *)v6 - (char *)&unk_AA0C16 != 1 )
            {
              if ( (char *)v6 - (char *)&unk_AA0C16 == 2 && !*((_BYTE *)this + 15018) && !*((_BYTE *)this + 6176) )
              {
                sub_5273D0((int)this);
                goto LABEL_20;
              }
              return 1;
            }
            if ( *((_BYTE *)this + 15018) )
              return 1;
            if ( *((_BYTE *)this + 6176) )
            {
              *((_DWORD *)this + 873) = 0;
              *((_BYTE *)this + 3480) = 0;
            }
            *((_BYTE *)this + 15012) = 1;
            *((_DWORD *)this + 811) = 0;
            *((_BYTE *)this + 3232) = 0;
            (**((void (***)(char *, int))this + 915))((char *)this + 3660, 1);
            if ( *((_DWORD *)this + 3758) )
              *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 0;
            else
              *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 1;
            if ( !*((_BYTE *)this + 3232) && !*((_BYTE *)this + 3480) )
            {
              v17 = (void (**)(char *, _DWORD))*((_DWORD *)this + 915);
              *((_BYTE *)this + 15012) = 0;
              (*v17)((char *)this + 3660, 0);
              *((_BYTE *)this + *((_DWORD *)this + 3752) + 15024) = 0;
            }
          }
          sub_527370((int)this, *((_DWORD *)this + 3752));
          v30 = (char *)off_5E7ECC;
          goto LABEL_21;
        }
      }
      if ( *((_BYTE *)this + 6176) )
      {
        v14 = (char *)&this->_pad_000[248 * v7];
        if ( v14[420] )
        {
          *((_DWORD *)v14 + 108) = 0;
          v14[420] = 0;
        }
        else
        {
          *((_DWORD *)v14 + 108) = 1;
          v14[420] = 1;
        }
        return 1;
      }
      if ( *((_BYTE *)this + 15012) || *((_BYTE *)this + 15018) )
      {
        if ( !*((_BYTE *)this + v7 + 15013) )
        {
          v15 = (char *)this + 248 * v7 + 352;
          *((_DWORD *)v15 + 20) = 0;
          v15[68] = 0;
        }
        if ( *((_DWORD *)this + 3752) == v7 )
        {
          v16 = (char *)this + 248 * v7 + 352;
          *((_DWORD *)v16 + 20) = 1;
          v16[68] = 1;
        }
        v30 = (char *)off_5E7ED8[0];
      }
      else if ( *((_BYTE *)this + v7 + 15013) )
      {
        v30 = (char *)off_5E7ED8[0];
      }
      else
      {
        *((_DWORD *)this + 3752) = v7;
        if ( sub_5270C0(this->_pad_000, v7) > 0 )
          sub_527130(this, *((_DWORD *)this + 3752));
LABEL_20:
        v30 = (char *)off_5E7ECC;
      }
LABEL_21:
      v13 = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)v13)->AudioSetPosition(v30, 1);
      return 1;
    case 1002:
      if ( (char *)a3 == (char *)&unk_AA0C16 )
      {
        if ( !*((_BYTE *)this + 15018) && !*((_BYTE *)this + 6176) )
          *((_BYTE *)this + 99196) = 1;
      }
      else if ( (char *)a3 - (char *)&unk_AA0C16 == 1 && !*((_BYTE *)this + 15018) && !*((_BYTE *)this + 6176) )
      {
        *((_BYTE *)this + 99197) = 1;
        return 1;
      }
      return 1;
    case 1009:
      if ( (char *)a3 != (char *)&unk_AA0C22 )
        return 1;
      if ( *(_BYTE *)(*((_DWORD *)this + 24800) + 1740) )
      {
        v19 = 0;
        v20 = (int *)((char *)this + 6968);
        do
        {
          if ( *((_BYTE *)this + v19 + 15024) )
          {
            v31 = *v20;
            pOut2 = 0;
            SkillNum = 0;
            pOut = v31;
            SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(v31);
            pOut2 = 1;
            CCBStageRole_GetAlive((int)&g_SceneMgr.m_slot4[792], &pOut);
          }
          ++v19;
          v20 += 402;
        }
        while ( v19 < 5 );
      }
      sub_527F50(*((int **)this + 24800), 3);
      return 1;
    case 1010:
      if ( *((_BYTE *)this + 15018) )
      {
        sub_527370((int)this, *((_DWORD *)this + 3752));
        *((_DWORD *)this + 1223) = 0;
        *((_DWORD *)this + 1222) = 0;
        *((_DWORD *)this + 1221) = 0;
        v21 = 0;
        v22 = (UIWnd *)((char *)this + 2080);
        do
        {
          if ( *((_BYTE *)this + v21 + 3160) )
            UIObj_SetState(v22, 1);
          ++v21;
          v22 = (UIWnd *)((char *)v22 + 344);
        }
        while ( v21 < 3 );
      }
      return 1;
    case 1013:
      if ( (char *)a3 == (char *)&unk_AA0C25 )
      {
        if ( *((_BYTE *)this + 6176) )
        {
          sub_527230((int)this, 0, *((_DWORD *)this + 3752));
          v26 = *((_DWORD *)this + 1545);
          v27 = (UIWnd *)((char *)this + 2080);
          v28 = 3;
          *((_BYTE *)&v27[15].m_benable + v26) = 0;
          do
          {
            UIObj_SetState(v27, 0);
            v27 = (UIWnd *)((char *)v27 + 344);
            --v28;
          }
          while ( v28 );
        }
        return 1;
      }
      if ( (char *)a3 - (char *)&unk_AA0C25 != 1 || !*((_BYTE *)this + 6176) )
        return 1;
      sub_527230((int)this, 1, *((_DWORD *)this + 3752));
      v23 = *((_DWORD *)this + 1545);
      v24 = (UIWnd *)((char *)this + 2080);
      v25 = 3;
      *((_BYTE *)&v24[15].m_benable + v23) = 0;
      do
      {
        UIObj_SetState(v24, 0);
        v24 = (UIWnd *)((char *)v24 + 344);
        --v25;
      }
      while ( v25 );
      return 1;
    case 1016:
      if ( (char *)a3 == (char *)&unk_AA0C27 )
      {
        ((GRPinput *)&g_Input)->GetMousePos(&pOut, &pOut2);
        *((float *)this + 1221) = (double)pOut2 + *((float *)this + 1221);
        *((float *)this + 1222) = (double)pOut + *((float *)this + 1222);
      }
      return 1;
    default:
      return a2->SendMessage((int)a3, a4);
  }
}

// 0x00527950
int UIWnd::ctor_7950()
{
  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_DWORD *)this + 88) = 0;
  ((UIItem *)(UIItem *)this + 356)->Refresh();
  *((_DWORD *)this + 431) = 0;
  *((_DWORD *)this + 432) = 0;
  *((_DWORD *)this + 436) = 0;
  *(_DWORD *)this->_pad_000 = &off_5706EC;
  *((_BYTE *)this + 1756) = 1;
  return (int)this->_pad_000;
}

// 0x005279F0
void UIWnd::ctor_79F0()
{
  int v2; // ecx
  int v3; // ecx

  *(_DWORD *)this->_pad_000 = &off_5706EC;
  v2 = *((_DWORD *)this + 431);
  if ( v2 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v2 + 20))(v2, 1);
    *((_DWORD *)this + 431) = 0;
  }
  v3 = *((_DWORD *)this + 432);
  if ( v3 )
  {
    (*(void (**)(int, int))(*(_DWORD *)v3 + 20))(v3, 1);
    *((_DWORD *)this + 432) = 0;
  }
  ((UIItem *)(UIItem *)this + 356)->UIItem();
  this->~UIWnd();
}

// 0x005282E0
int UIWnd::ctor_82E0()
{
  char *v2; // edi
  int v3; // ebp
  char *v4; // edi
  int v5; // ebp

  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  ((UIScene *)((char *)this + 352))->_UIScene();
  ((UIFrameWnd *)((char *)this + 696))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 848))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1000))->UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 16)->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1304))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1456))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1608))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1760))->UIFrameWnd();
  ((UIWnd *)((char *)this + 1912))->ctor_9030();
  v2 = (char *)this + 2220;
  v3 = 5;
  do
  {
    ((void (*)(char *))gbVec3D::`default constructor closure')(v2);
    v2 += 12;
    --v3;
  }
  while ( v3 );
  ((UIWnd *)((char *)this + 2280))->ctor_9030();
  ((UIFrameWnd *)((char *)this + 2588))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2740))->UIFrameWnd();
  ctor_0x431870((_DWORD *)this + 725);
  v4 = (char *)this + 4712;
  v5 = 5;
  do
  {
    ArraySort((int)v4, 800, 2, (int)sub_5254C0);
    v4 += 1608;
    --v5;
  }
  while ( v5 );
  *((_DWORD *)this + 3186) = 0;
  ((UIItem *)(UIItem *)this + 12752)->Refresh();
  `eh vector constructor iterator'(
    (char *)this + 14124,
    0x248u,
    36,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector constructor iterator'(
    (char *)this + 35148,
    0x248u,
    36,
    (void (*)(void *))UIObj_Reset,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  *((_BYTE *)this + 56188) = 0;
  *((_BYTE *)this + 56189) = 0;
  *(_DWORD *)this->_pad_000 = &off_570728;
  *((_DWORD *)this + 724) = 0;
  return (int)this->_pad_000;
}

// 0x005284E0
void UIWnd::ctor_84E0()
{
  *(_DWORD *)this->_pad_000 = &off_570728;
  `eh vector destructor iterator'(
    (char *)this + 35148,
    0x248u,
    36,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  `eh vector destructor iterator'(
    (char *)this + 14124,
    0x248u,
    36,
    (void (*)(void *))UIFrameWnd_Destructor_4B47E0);
  ((UIItem *)(UIItem *)this + 12752)->UIItem();
  PalScript_Cleanup((PalScript *)((char *)this + 2900));
  ((UIFrameWnd *)((char *)this + 2740))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2588))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 2280))->ctor_9130();
  ((UIWnd *)((char *)this + 1912))->ctor_9130();
  ((UIFrameWnd *)((char *)this + 1760))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1608))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1456))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1304))->_UIFrameWnd();
  ((UIFrameWnd *)(UIFrameWnd *)this + 16)->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1000))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 848))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 696))->_UIFrameWnd();
  ((UIScene *)((char *)this + 352))->Destroy2();
  this->~UIWnd();
}

// 0x005295F0
int UIWnd::ctor_95F0()
{
  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  *((_BYTE *)this + 352) = 0;
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 512,
    0xB8u,
    3,
    (void (*)(void *))UIWnd::ctor_2E10,
    (void (*)(void *))UIWnd::ctor_2E80);
  sub_444A20((UIFrameWnd *)((char *)this + 1064));
  *((_BYTE *)this + 1260) = 0;
  *((_DWORD *)this + 314) = 0;
  *((_DWORD *)this + 313) = 0;
  *((_BYTE *)this + 1280) = 0;
  *((_DWORD *)this + 319) = 0;
  *((_DWORD *)this + 318) = 0;
  ((UIFrameWnd *)((char *)this + 1284))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1436))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1840))->UIFrameWnd();
  UIWnd_Init_444F60((UIWnd *)((char *)this + 1992));
  *((_DWORD *)this + 317) = 32;
  *((_DWORD *)this + 316) = 32;
  *(_DWORD *)this->_pad_000 = &off_57076C;
  *((_DWORD *)this + 397) = 64;
  *((_DWORD *)this + 398) = 58;
  *((_DWORD *)this + 427) = 28;
  *((_DWORD *)this + 455) = 1065353216;
  *((_DWORD *)this + 456) = 1060152279;
  *((_DWORD *)this + 457) = 1036831949;
  *((_DWORD *)this + 458) = 1008981770;
  *((_DWORD *)this + 400) = 0;
  *((_DWORD *)this + 399) = 0;
  *((_DWORD *)this + 401) = 800;
  *((_DWORD *)this + 402) = 600;
  *((_DWORD *)this + 547) = 0;
  *((_BYTE *)this + 2200) = 1;
  return (int)this->_pad_000;
}

// 0x00529790
void UIWnd::ctor_9790()
{
  UIRenderObj *Instance; // eax

  *(_DWORD *)this->_pad_000 = &off_57076C;
  Instance = (UIRenderObj *)UIQuadManager::GetInstance();
  Instance->~UIRenderObj(1u);
  UIWnd_Destructor((UIWnd *)((char *)this + 1992));
  ((UIFrameWnd *)((char *)this + 1840))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1436))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1284))->_UIFrameWnd();
  UIFrameWnd_Destructor_444AC0((UIWnd *)((char *)this + 1064));
  `eh vector destructor iterator'((char *)this + 512, 0xB8u, 3, (void (*)(void *))UIWnd::ctor_2E80);
  ((UIFrameWnd *)(UIFrameWnd *)this + 5)->_UIFrameWnd();
  this->~UIWnd();
}

// 0x0052BA10
int UIWnd::ctor_BA10()
{
  ((UIListBox *)this)->UIListBox();
  *((_DWORD *)this + 22) = 800;
  *((_DWORD *)this + 23) = 600;
  ctor_0x431870((_DWORD *)this + 88);
  *((_DWORD *)this + 283) = 418;
  *((_DWORD *)this + 284) = 418;
  *((_DWORD *)this + 285) = 48;
  *((_DWORD *)this + 286) = 192;
  *((_DWORD *)this + 287) = 78;
  *((_DWORD *)this + 288) = 78;
  *((_BYTE *)this + 1156) = 0;
  *((_BYTE *)this + 1157) = 0;
  *((_BYTE *)this + 1159) = 0;
  ((UIFrameWnd *)((char *)this + 1160))->UIFrameWnd();
  ((UIWnd *)((char *)this + 1312))->ctor_2E10();
  `eh vector constructor iterator'(
    (char *)this + 1496,
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 2120))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2272))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 2424,
    0x610u,
    5,
    (void (*)(void *))sub_52BBD0,
    (void (*)(void *))sub_52BC90);
  *((_DWORD *)this + 2546) = 0;
  *((_BYTE *)this + 10188) = 1;
  *((_DWORD *)this + 2548) = 0;
  *((_DWORD *)this + 2549) = 1092616192;
  *((_BYTE *)this + 10200) = 0;
  *((_BYTE *)this + 10206) = 0;
  ((UIItem *)(UIItem *)this + 10208)->Refresh();
  ((UIItem *)(UIItem *)this + 11576)->Refresh();
  *(_DWORD *)this->_pad_000 = &off_570830;
  *((_DWORD *)this + 526) = -1;
  *((_DWORD *)this + 527) = -1;
  *((_DWORD *)this + 528) = -1;
  *((_DWORD *)this + 529) = -1;
  *(_DWORD *)((char *)this + 10201) = 0;
  *((_BYTE *)this + 10205) = 0;
  *((_BYTE *)this + 12953) = 1;
  return (int)this->_pad_000;
}

// 0x0052BD50
void UIWnd::ctor_BD50()
{
  *(_DWORD *)this->_pad_000 = &off_570830;
  ((UIItem *)(UIItem *)this + 11576)->UIItem();
  ((UIItem *)(UIItem *)this + 10208)->UIItem();
  `eh vector destructor iterator'((char *)this + 2424, 0x610u, 5, (void (*)(void *))sub_52BC90);
  ((UIFrameWnd *)((char *)this + 2272))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 2120))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 1496, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 1312))->ctor_2E80();
  ((UIFrameWnd *)((char *)this + 1160))->_UIFrameWnd();
  PalScript_Cleanup((PalScript *)((char *)this + 352));
  this->~UIWnd();
}

// 0x00531D20
int UIWnd::ctor_1D20()
{
  ((UIListBox *)this)->UIListBox();
  *((_BYTE *)this + 360) = 0;
  *((_DWORD *)this + 89) = 0;
  *((_DWORD *)this + 88) = 0;
  ((UIFrameWnd *)((char *)this + 364))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 1316))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)this + 1468,
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)this + 2988,
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *((_BYTE *)this + 4536) = 0;
  *((_DWORD *)this + 1133) = 0;
  *((_DWORD *)this + 1132) = 0;
  ((UIItem *)(UIItem *)this + 4540)->Refresh();
  ((UIItem *)(UIItem *)this + 5908)->Refresh();
  ((UIFrameWnd *)((char *)this + 7280))->UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 7432))->UIFrameWnd();
  *((_BYTE *)this + 7592) = 0;
  *((_DWORD *)this + 1897) = 0;
  *((_DWORD *)this + 1896) = 0;
  *(_DWORD *)this->_pad_000 = &off_570890;
  *((_DWORD *)this + 327) = 0;
  *((_BYTE *)this + 7598) = 1;
  return (int)this->_pad_000;
}

// 0x00531E70
void UIWnd::ctor_1E70()
{
  *(_DWORD *)this->_pad_000 = &off_570890;
  ((UIFrameWnd *)((char *)this + 7432))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 7280))->_UIFrameWnd();
  ((UIItem *)(UIItem *)this + 5908)->UIItem();
  ((UIItem *)(UIItem *)this + 4540)->UIItem();
  `eh vector destructor iterator'((char *)this + 2988, 0x98u, 10, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 1468, 0x98u, 10, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)((char *)this + 1316))->_UIFrameWnd();
  ((UIFrameWnd *)((char *)this + 364))->_UIFrameWnd();
  this->~UIWnd();
}
