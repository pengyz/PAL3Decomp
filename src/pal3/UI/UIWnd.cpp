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
int sub_40CC60(...);
int sub_41C090(...);
int sub_431870(...);
int sub_4318A0(...);
int sub_431C10(...);
int sub_432680(...);
int sub_4326A0(...);
int sub_4391A0(...);
int sub_439230(...);
int sub_439740(...);
int sub_439810(...);
int sub_439850(...);
int sub_439930(...);
int sub_43A070(...);
int sub_43A090(...);
int sub_43B3E0(...);
int sub_43B4D0(...);
int sub_43BE80(...);
int sub_43EBB0(...);
int sub_43F650(...);
int sub_43F9C0(...);
int sub_43FD90(...);
int sub_440CE0(...);
int sub_4414D0(...);
int sub_443190(...);
int sub_4431D0(...);
int sub_4434C0(...);
int sub_4438F0(...);
int sub_444A20(...);
int sub_444AC0(...);
int sub_444F60(...);
int sub_445010(...);
int sub_445BF0(...);
int sub_445E10(...);
int sub_445E50(...);
int sub_4461B0(...);
int sub_4461F0(...);
int sub_44A3D0(...);
int sub_44A7F0(...);
int sub_44B850(...);
int sub_44B890(...);
int sub_44BD60(...);
int sub_44BD80(...);
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
int sub_4A1530(...);
int sub_4A22E0(...);
int sub_4A6600(...);
int sub_4A6730(...);
int sub_4B4690(...);
int sub_4B47E0(...);
int sub_4B6FB0(...);
int sub_4B7AF0(...);
int sub_4B7F00(...);
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
extern int unk_DE5FA4;
extern int word_DE5FA8;

// 0x00439030
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_DWORD * UIWnd::ctor_9030()
{
  this->UIWnd();
  `eh vector constructor iterator'(
    (char *)&this->m_childs,
    0x20u,
    5,
    (void (*)(void *))sub_4391A0,
    nullsub_3);
  *((_DWORD *)this + 74) = 0;
  *((_DWORD *)this + 75) = 0;
  *((_DWORD *)this + 76) = 0;
  *((_DWORD *)this + 71) = 1065353216;
  *((_DWORD *)this + 70) = 1065353216;
  *((_DWORD *)this + 69) = 1065353216;
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AC20;
  *((_DWORD *)this + 73) = 0;
  this->m_pfather = 0;
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
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x00439130
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_9130(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AC20;
  sub_439810((int)this);
  `eh vector destructor iterator'((char *)this + 72, 0x20u, 5, nullsub_3);
  this->_UIWnd();
}

// 0x0043A160
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_A160()
{
  this->UIWnd();
  ((UIWnd *)&this->m_childs.m_nSize)->DestroyChildren();
  *((_DWORD *)this + 36) = 0;
  this->m_childs.m_pData = 0;
  *((_DWORD *)this + 37) = 0;
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AC4C;
  this->m_pfather = (UIWnd *)1092616192;
  *((_DWORD *)this + 39) = -1;
}

// 0x0043A1F0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_A1F0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AC4C;
  ((PalScript *)this)->Reset();
  ((j_UIWnd *)(char *)this + 76)->MoveWindow();
  this->_UIWnd();
}

// 0x0043BB70
_DWORD * UIWnd::ctor_BB70()
{
  this->UIWnd();
  this->m_fontcolor.ColorQuadFmt = (int)&off_56ACB8;
  this->m_pfather = 0;
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0043BBB0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_BBB0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ACB8;
  this->_UIWnd();
}

// 0x0043BCE0
// write access to const memory has been detected, the output may be wrong!
_DWORD * UIWnd::ctor_BCE0()
{
  this->UIWnd();
  this->m_bvisible = 32;
  this->m_benable = 32;
  *((_DWORD *)this + 59) = 0x40000000;
  this->m_bfocus = 0;
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
  this->m_fontcolor.ColorQuadFmt = (int)&off_56ACD8;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 46) = 0;
  *((_DWORD *)this + 47) = 0;
  *((_DWORD *)this + 42) = -16776961;
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
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0043BE10
UIWnd * UIWnd::`scalar deleting destructor'(UIWnd *Block, char a2)
{
  UIWnd::~UIWnd(Block);
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}

// 0x0043BE30
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ACD8;
  sub_43BE80((gbRefObject **)this);
  this->_UIWnd();
}

// 0x0043D830
_DWORD * UIWnd::ctor_D830()
{
  this->UIWnd();
  this->m_fontcolor.ColorQuadFmt = (int)&off_56ACFC;
  this->m_childs.m_nMaxSize = 0;
  this->m_childs.m_nSize = 0;
  this->m_pfather = (UIWnd *)32;
  this->m_childs.m_pData = (void *)32;
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0043D880
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_D880(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ACFC;
  this->_UIWnd();
}

// 0x0043DD10
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD20;
  ((UIListBox **)this)->SetScrollPos();
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
  this->m_pfather = 0;
  this->m_childs.m_pData = 0;
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
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AD64;
  *((_DWORD *)this + 41) = -1;
  gbColorQuad::ColorQuadFmt = 1;
  *((_DWORD *)this + 42) = -65536;
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
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x0043F970
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD64;
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
  CHAR *v8; // eax
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
      *((_DWORD *)this + 43) = (UIWnd *)(*(int (**)(int, const CHAR *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                                g_Input.KeyInfo[177].Data,
                                v3);
    }
    else
    {
      v7 = *(_DWORD *)g_Input.KeyInfo[177].Data;
      v8 = ((int)dword_1894B78)->_CalculateUV(v3);
      *((_DWORD *)this + 43) = (UIWnd *)(*(int (**)(int, CHAR *))(v7 + 8))(g_Input.KeyInfo[177].Data, v8);
      *((_DWORD *)this + 44) = (UIWnd *)((int)dword_1894B78)->Parent_Data(v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 43);
    if ( v9 )
      v9->LoadTexture(1);
    ((OpenNULLFile **)&lpString)->OpenNULLFile();
  }
}

// 0x0043FAE0
void UIWnd::GetChildAt(LPCSTR lpString, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  CHAR *v8; // eax
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
      *((_DWORD *)this + 45) = (UIWnd *)(*(int (**)(int, const CHAR *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                                g_Input.KeyInfo[177].Data,
                                v3);
    }
    else
    {
      v7 = *(_DWORD *)g_Input.KeyInfo[177].Data;
      v8 = ((int)dword_1894B78)->_CalculateUV(v3);
      *((_DWORD *)this + 45) = (UIWnd *)(*(int (**)(int, CHAR *))(v7 + 8))(g_Input.KeyInfo[177].Data, v8);
      *((_DWORD *)this + 46) = (UIWnd *)((int)dword_1894B78)->Parent_Data(v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 45);
    if ( v9 )
      v9->LoadTexture(1);
    ((OpenNULLFile **)&lpString)->OpenNULLFile();
  }
}

// 0x0043FCA0
void UIWnd::FindChild(int _this, float a2)
{
  int v2; // eax
  double v3; // st7
  double v4; // st6

  *(float *)(this + 124) = a2;
  if ( a2 >= 0.0 )
  {
    v2 = *(_DWORD *)(this + 68);
    if ( v2 )
    {
      if ( v2 != 1 )
      {
LABEL_7:
        *(float *)(this + 128) = *(float *)(this + 120) / a2;
        *(float *)(this + 152) = a2 / *(float *)(this + 120);
        return;
      }
      v3 = (double)*(int *)(this + 28) - *(float *)(this + 148) - *(float *)(this + 132);
      v4 = (double)*(int *)(this + 20) + *(float *)(this + 144);
    }
    else
    {
      v3 = (double)*(int *)(this + 24) - *(float *)(this + 140) - *(float *)(this + 132);
      v4 = (double)*(int *)(this + 16) + *(float *)(this + 136);
    }
    *(float *)(this + 120) = v3 - (v4 + *(float *)(this + 132));
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
void UIWnd::FindChildByName(int _this, float a2)
{
  double v2; // st7
  double v3; // st6

  if ( *(float *)(this + 124) > 0.0 )
  {
    v2 = a2;
    if ( a2 < 0.0 )
      v2 = 0.0;
    if ( v2 > *(float *)(this + 124) )
      v2 = *(float *)(this + 124);
    v3 = v2 * *(float *)(this + 128);
    *(float *)(this + 116) = v3;
    if ( v3 >= *(float *)(this + 120) )
      *(_DWORD *)(this + 116) = *(_DWORD *)(this + 120);
    *(float *)(this + 156) = *(float *)(this + 152) * *(float *)(this + 108);
    if ( v2 > (double)*(int *)(this + 240) )
    {
      *(_BYTE *)(this + 238) = 1;
    }
    else
    {
      *(_BYTE *)(this + 237) = 1;
      *(_BYTE *)(this + 238) = 0;
    }
    *(_BYTE *)(this + 160) = 0;
  }
}

// 0x0043FEC0
int UIWnd::AddChild(_DWORD *a2)
{
  int *p_m_nSize; // edx
  __int32 *p_Alpha; // ecx
  int result; // eax

  p_m_nSize = (int *)&this->m_childs.m_nSize;
  p_Alpha = (__int32 *)&this->m_fontcolor.Alpha;
  * p_m_nSize = (*)*a2;
  p_m_nSize[1] = a2[1];
  p_m_nSize[2] = a2[2];
  p_m_nSize[3] = a2[3];
  * p_Alpha = (*)*a2;
  p_Alpha[1] = a2[1];
  p_Alpha[2] = a2[2];
  result = a2[3];
  p_Alpha[3] = result;
  return result;
}

// 0x004407C0
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD88;
  ((UIStatic **)this)->OnMessage();
  this->_UIWnd();
}

// 0x004410F0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_DWORD * UIWnd::ctor_10F0()
{
  this->UIWnd();
  ((UIWnd *)&this->m_childs)->ctor_D830();
  ((UIWnd *)((char *)this + 192))->DestroyChildren();
  this->m_fontcolor.ColorQuadFmt = (int)&off_56ADAC;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 42) = 100;
  *((_DWORD *)this + 43) = 0;
  *((_DWORD *)this + 40) = 5;
  LOBYTE(this->m_pfather) = 0;
  BYTE1(this->m_pfather) = 0;
  *((_DWORD *)this + 47) = 10;
  *((_DWORD *)this + 39) = 16;
  *((_DWORD *)this + 44) = 0;
  *((_DWORD *)this + 45) = 0;
  *((_DWORD *)this + 75) = 0;
  *((_DWORD *)this + 84) = 0;
  memset((char *)this + 260, 0, 0x28u);
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x004411D0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_11D0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ADAC;
  sub_4414D0((UIWnd **)this);
  ((j_UIWnd *)(char *)this + 192)->MoveWindow();
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
  CHAR *v8; // eax
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
      v7 = *(_DWORD *)g_Input.KeyInfo[177].Data;
      v8 = ((int)dword_1894B78)->_CalculateUV(v3);
      *((_DWORD *)this + 28) = (UIWnd *)(*(int (**)(int, CHAR *))(v7 + 8))(g_Input.KeyInfo[177].Data, v8);
      *((_DWORD *)this + 29) = (UIWnd *)((int)dword_1894B78)->Parent_Data(v3);
    }
    else
    {
      *((_DWORD *)this + 28) = (UIWnd *)(*(int (**)(int, const CHAR *))(*(_DWORD *)g_Input.KeyInfo[177].Data + 8))(
                                g_Input.KeyInfo[177].Data,
                                v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 28);
    if ( v9 )
      v9->LoadTexture(1);
    if ( !lstrcmpA(v3, String2) )
      *(_DWORD *)&g_GameData_0._data[10364] = *((_DWORD *)this + 28);
    ((OpenNULLFile **)&lpString1)->OpenNULLFile();
  }
}

// 0x004427A0
int UIWnd::SetShow(int a2)
{
  int result; // eax

  result = a2;
  if ( a2 )
    this->m_bvisible = 2;
  else
    this->m_bvisible = 1;
  return result;
}

// 0x004427C0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::SetEnable(const char *a2, int a3)
{
  int *p_m_benable; // ebp
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  int v6; // ecx
  char v7; // al
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // [esp-8h] [ebp-14h]

  if ( a2 )
  {
    p_m_benable = (int *)&this->m_benable;
    v4 = strlen(a2) + 1;
    v5 = v4 - 1;
    if ( v4 - 1 > 0xFFFFFFFD )
      v10->_Xlen();
    v6 = p_m_benable[1];
    if ( v6 && (v7 = *(_BYTE *)(v6 - 1)) != 0 && v7 != -1 )
    {
      if ( v4 == 1 )
      {
        *(_BYTE *)(v6 - 1) = v7 - 1;
        p_m_benable[1] = 0;
        p_m_benable[2] = 0;
        p_m_benable[3] = 0;
        goto LABEL_16;
      }
    }
    else
    {
      if ( v4 == 1 )
      {
        p_m_benable->string::_Tidy(1);
        goto LABEL_16;
      }
      v8 = p_m_benable[3];
      if ( v8 <= 0x1F && v8 >= v5 )
      {
LABEL_15:
        qmemcpy((void *)p_m_benable[1], a2, v5);
        v9 = p_m_benable[1];
        p_m_benable[2] = v5;
        *(_BYTE *)(v9 + v5) = 0;
LABEL_16:
        if ( a3 )
          this->m_childs.m_pData = (void *)1;
        else
          this->m_childs.m_pData = 0;
        return;
      }
      p_m_benable->string::_Tidy(1);
    }
    ((int)p_m_benable)->GetKeyState(v5);
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
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AE10;
  *((_DWORD *)this + 36) = 21;
}

// 0x00442E80
void UIWnd::ctor_2E80(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AE10;
  this->_UIFrameWnd();
}

// 0x00443550
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AE64;
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
    this->m_bcreateok = this->m_fontcolor.Alpha;
    this->m_bvisible = this->m_fontcolor.Color;
    this->m_benable = this->m_wndcolor.ColorQuadFmt;
    result = this->m_wndcolor.Blue;
    this->m_bfocus = result;
  }
  return result;
}

// 0x00445AA0
UIWnd::UIWnd()
{
  __int32 v3; // [esp+4h] [ebp-4h]

  ((PtrArray *)&this->m_wndcolor.Red)->Clear();
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AEC8;
  this->m_fontcolor.Red = -1;
  this->m_fontcolor.Alpha = 0;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.ColorQuadFmt = 0;
  this->m_wndcolor.Blue = 0;
  this->m_wndcolor.Green = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  this->m_rect.right = 0;
  this->m_rect.bottom = 0;
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
  this->m_fontcolor.Blue = v3;
  this->m_fontcolor.Green = -1;
  &this->m_fontcolor.ColorQuadFmt;
}

// 0x00445B40
void UIWnd::_UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AEC8;
  ((UIWnd *)this)->UpdateChildren();
  sub_432680((void **)&this->_data[36]);
}

// 0x00445B90
int UIWnd::Create(int id, void *pRect, int parent)
{
  this->m_fontcolor.Red = id;
  this->m_fontcolor.Alpha = *(_DWORD *)pRect;
  this->m_fontcolor.Color = *((_DWORD *)pRect + 1);
  this->m_wndcolor.ColorQuadFmt = *((_DWORD *)pRect + 2);
  this->m_wndcolor.Blue = *((_DWORD *)pRect + 3);
  this->m_wndcolor.Green = parent;
  if ( parent )
  {
    sub_445BF0((int *)parent, (int)this);
    sub_445E10((_DWORD *)this->m_wndcolor.Green, &this->m_fontcolor.Alpha);
  }
  this->m_rect.left = 1;
  this->m_rect.top = 1;
  this->m_rect.right = 1;
  return 1;
}

// 0x00445C10
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::UpdateChildren()
{
  __int32 v2; // edi
  int v3; // ecx

  v2 = 0;
  this->m_rect.left = 0;
  this->m_rect.top = 0;
  for ( this->m_rect.right = 0; v2 < this->m_wndcolor.Alpha; ++v2 )
  {
    v3 = *(_DWORD *)(this->m_wndcolor.Red + 4 * v2);
    (*(void (**)(int))(*(_DWORD *)v3 + 12))(v3);
  }
  sub_4326A0((int)&this->m_wndcolor.Red, 0, -1);
}

// 0x00445C60
BOOL UIWnd::HitTest(int a2, int a3)
{
  __int32 v5; // edi
  int v6; // esi
  int v7; // ecx

  if ( !this->m_rect.top )
    return 0;
  if ( !this->m_rect.right )
    return 0;
  v5 = this->m_wndcolor.Alpha - 1;
  if ( v5 < 0 )
    return a3 == 0;
  v6 = a3;
  do
  {
    v7 = *(_DWORD *)(this->m_wndcolor.Red + 4 * v5);
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

  result = this->m_rect.top;
  if ( result )
  {
    result = this->m_wndcolor.Alpha;
    for ( i = 0; i < result; ++i )
    {
      v4 = (_DWORD *)*(_DWORD **)(this->m_wndcolor.Red + 4 * i);
      if ( v4[14] )
        (*(void (**)(_DWORD *))(*v4 + 4))(v4);
      result = this->m_wndcolor.Alpha;
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
  return this->ClientToScreen(a2 - this->m_fontcolor.Alpha, a3 - this->m_fontcolor.Color);
}

// 0x00445D40
int UIWnd::ClientToScreen(int a2, int a3)
{
  __int32 Alpha; // ebp
  int ColorQuadFmt; // edi
  __int32 Color; // edx
  __int32 Blue; // ecx
  int result; // eax
  int i; // edi

  Alpha = this->m_fontcolor.Alpha;
  ColorQuadFmt = this->m_wndcolor.ColorQuadFmt;
  Color = this->m_fontcolor.Color;
  Blue = this->m_wndcolor.Blue;
  this->m_fontcolor.Alpha = a2 + Alpha;
  this->m_wndcolor.ColorQuadFmt = a2 + ColorQuadFmt;
  this->m_fontcolor.Color = a3 + Color;
  this->m_wndcolor.Blue = a3 + Blue;
  if ( this )
    (*(void (**)(UIWnd *, int, _DWORD, _DWORD))(this->m_fontcolor.ColorQuadFmt + 24))(this, 1022, 0, 0);
  result = this->m_wndcolor.Alpha;
  for ( i = 0; i < result; ++i )
  {
    ((UIWnd *)*(UIWnd **)(this->m_wndcolor.Red + 4 * i))->ClientToScreen(a2, a3);
    result = this->m_wndcolor.Alpha;
  }
  return result;
}

// 0x00445DB0
int UIWnd::SetVisible(int bVisible)
{
  int Data; // ebx
  int HoldTime; // edx
  int v4; // esi
  int v5; // edi

  if ( bVisible )
  {
    v4 = *(_DWORD *)(bVisible + 16);
    v5 = *(_DWORD *)(bVisible + 20);
    Data = *(_DWORD *)(bVisible + 24);
    HoldTime = *(_DWORD *)(bVisible + 28);
  }
  else
  {
    Data = g_Input.KeyInfo[120].Data;
    HoldTime = g_Input.KeyInfo[120].HoldTime;
    v4 = 0;
    v5 = 0;
  }
  return this->ScreenToClient(v4 + (Data + this->m_fontcolor.Alpha - this->m_wndcolor.ColorQuadFmt - v4) / 2, v5 + (HoldTime + this->m_fontcolor.Color - this->m_wndcolor.Blue - v5) / 2);
}

// 0x00445E70
int UIWnd::Destroy(int a2)
{
  int result; // eax
  int ColorQuadFmt; // edx

  result = this->m_rect.left;
  if ( result )
  {
    result = a2;
    if ( this->m_rect.top != a2 )
    {
      ColorQuadFmt = this->m_fontcolor.ColorQuadFmt;
      this->m_rect.top = a2;
      return (*(int (__stdcall **)(int, int, _DWORD))(ColorQuadFmt + 24))(1000, a2, 0);
    }
  }
  return result;
}

// 0x00445EA0
void * UIWnd::DestroyChildren()
{
  memset(this, 0, 0x44u);
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

  result = (int)&this->m_fontcolor.Alpha;
  this->m_fontcolor.Alpha = *a2;
  this->m_fontcolor.Color = a2[1];
  this->m_wndcolor.ColorQuadFmt = a2[2];
  this->m_wndcolor.Blue = a2[3];
  if ( this )
    return (*(int (**)(UIWnd *, int, _DWORD, _DWORD))(this->m_fontcolor.ColorQuadFmt + 24))(this, 1022, 0, 0);
  return result;
}

// 0x00445FE0
_DWORD * UIWnd::SetRect(_DWORD *a2)
{
  __int32 *p_Alpha; // ecx

  p_Alpha = (__int32 *)&this->m_fontcolor.Alpha;
  * a2 = (*)*p_Alpha;
  a2[1] = p_Alpha[1];
  a2[2] = p_Alpha[2];
  a2[3] = p_Alpha[3];
  return a2;
}

// 0x00446010
int UIWnd::GetChild(int id)
{
  this->m_fontcolor.Blue = *(_DWORD *)id;
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
  ((UIWnd *)this + 179)->ctor_A160();
  *((_DWORD *)this + 4709) = 38;
  ((UIItem *)(UIItem *)this + 18840)->Refresh();
  ((UIItem *)(UIItem *)this + 20208)->Refresh();
  sub_431870((_DWORD *)this + 5394);
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AF80;
  this->m_childs.m_nSize = 0;
  this->m_childs.m_pData = 0;
  this->m_childs.m_nMaxSize = 800;
  this->m_childs.m_nGrowBy = 600;
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x00446200
void UIWnd::ctor_6200()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AF80;
  ((gbRefObject **)this)->SetScrollPos();
  sub_4318A0((int)this + 21576);
  ((UIItem *)(UIItem *)this + 20208)->UIItem();
  ((UIItem *)(UIItem *)this + 18840)->UIItem();
  ((UIWnd *)(this + 179))->ctor_A1F0();
  `eh vector destructor iterator'((char *)this + 512, 0x1DCu, 38, (void (*)(void *))sub_4461F0);
  ((UIWnd *)(UIWnd *)this + 9)->~UIWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x0044A540
int UIWnd::ctor_A540(int _this, int a2, int a3, int a4)
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
      *(_DWORD *)(this + 18836) = -1;
      sub_44A3D0(this);
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
    if ( !*(_BYTE *)(this + 18824) )
    {
      memset(Destination, 0, sizeof(Destination));
      v9 = 0;
      v10 = 0;
      ((PalScript *)(this + 21576))->SetDirectory(&aQ07[64 * v6]);
      sub_431C10((PalScript *)(this + 21576), aDefault, Destination, 256);
      if ( !*(_BYTE *)(this + 476 * v6 + 596) )
      {
        sprintf((char *const)(this + 104), "%s%s%s", byte_DDB03C, Destination, byte_DDB13C);
        ((UIWnd *)(this + 20664))->SetEnable((const char *)(this + 104), 1);
        sub_4A1530(this + 20208, 1);
        return 1;
      }
      sprintf((char *const)(this + 104), "%s%s%s", byte_DD953C, Destination, byte_DD963C);
      memset(Buffer, 0, sizeof(Buffer));
      v12 = 0;
      v13 = 0;
      sprintf(Buffer, "%s", (const char *)(this + 104));
      ((UIWnd *)(this + 19296))->SetEnable(Buffer, 1);
      sub_4A1530(this + 18840, 1);
      *(_DWORD *)(this + 18836) = v6;
    }
    return 1;
  }
}

// 0x0044AB90
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_AB90(int _this)
{
  ((UIWnd *)this)->UIWnd();
  *(_DWORD *)(this + 108) = 360;
  *(_DWORD *)(this + 112) = 136;
  ((UIFrameWnd *)(this + 124))->UIFrameWnd();
  ((UIFrameWnd *)(this + 276))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 428),
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)(this + 884))->_UIScene();
  ((UIScene *)(this + 1228))->_UIScene();
  ((UIScene *)(this + 1572))->_UIScene();
  ((UIItem *)(this + 1916))->Refresh();
  *(_BYTE *)(this + 3300) = 0;
  *(_DWORD *)(this + 3296) = 0;
  *(_DWORD *)(this + 3292) = 0;
  ((UIItem *)(this + 3308))->Refresh();
  ((UIItem *)(this + 4676))->Refresh();
  ((UIItem *)(this + 6044))->Refresh();
  sub_44B850(this + 7420);
  *(_DWORD *)this = &off_56AFD4;
  *(_DWORD *)(this + 116) = 90;
  *(_DWORD *)(this + 120) = 24;
  return this;
}

// 0x0044ACE0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_ACE0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AFD4;
  sub_44B890((int)this + 7420);
  ((UIItem *)(UIItem *)this + 6044)->UIItem();
  ((UIItem *)(UIItem *)this + 4676)->UIItem();
  ((UIItem *)(UIItem *)this + 3308)->UIItem();
  ((UIItem *)(UIItem *)this + 1916)->UIItem();
  ((UIWnd *)((char *)this + 1572))->Destroy2();
  ((UIWnd *)((char *)this + 1228))->Destroy2();
  ((UIWnd *)((char *)this + 884))->Destroy2();
  `eh vector destructor iterator'((char *)this + 428, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 276))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 124))->_UIFrameWnd();
  this->_UIWnd();
}

// 0x0044BA60
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_BA60(int _this)
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(this + 360))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 512),
    0xD0u,
    22,
    (void (*)(void *))sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 5088),
    0xD0u,
    16,
    (void (*)(void *))sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 8416),
    0xD0u,
    10,
    (void (*)(void *))sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 10496))->UIFrameWnd();
  ((UIFrameWnd *)(this + 10648))->UIFrameWnd();
  ((UIFrameWnd *)(this + 10800))->UIFrameWnd();
  ((UIFrameWnd *)(this + 10952))->UIFrameWnd();
  sub_443190((UIWnd *)(this + 11116));
  sub_443190((UIWnd *)(this + 11308));
  ((UIScene *)(this + 11500))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 11844),
    0x10u,
    3,
    (void (*)(void *))sub_44BD60,
    (void (*)(void *))sub_44BD80);
  *(_DWORD *)(this + 11500) = &off_56B018;
  ((UIScene *)(this + 11892))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 12236),
    0x10u,
    3,
    (void (*)(void *))sub_44BD60,
    (void (*)(void *))sub_44BD80);
  *(_DWORD *)(this + 11892) = &off_56B018;
  ((UIScene *)(this + 12284))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 12628),
    0x10u,
    3,
    (void (*)(void *))sub_44BD60,
    (void (*)(void *))sub_44BD80);
  *(_DWORD *)(this + 12284) = &off_56B018;
  ((UIScene *)(this + 12676))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 13020),
    0x10u,
    3,
    (void (*)(void *))sub_44BD60,
    (void (*)(void *))sub_44BD80);
  *(_DWORD *)(this + 12676) = &off_56B018;
  ((UIScene *)(this + 13068))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 13412),
    0x10u,
    3,
    (void (*)(void *))sub_44BD60,
    (void (*)(void *))sub_44BD80);
  *(_DWORD *)(this + 13068) = &off_56B018;
  ((UIScene *)(this + 13460))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 13804),
    0x10u,
    3,
    (void (*)(void *))sub_44BD60,
    (void (*)(void *))sub_44BD80);
  *(_DWORD *)(this + 13460) = &off_56B018;
  *(_DWORD *)(this + 13868) = 0;
  *(_DWORD *)(this + 13872) = 0;
  *(_DWORD *)(this + 13876) = 0;
  *(_DWORD *)(this + 13884) = 0;
  *(_BYTE *)(this + 13892) = 1;
  *(_BYTE *)(this + 13893) = 1;
  *(_BYTE *)(this + 13894) = 0;
  ((UIFrameWnd *)(this + 13904))->UIFrameWnd();
  ((UIFrameWnd *)(this + 14080))->UIFrameWnd();
  *(_DWORD *)this = &off_56AFFC;
  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 80) = 800;
  *(_DWORD *)(this + 84) = 600;
  *(_BYTE *)(this + 13852) = 0;
  *(_BYTE *)(this + 13853) = 0;
  *(_DWORD *)(this + 13856) = 0;
  *(_DWORD *)(this + 13860) = 0;
  *(_DWORD *)(this + 13864) = 0;
  return this;
}

// 0x0044BE80
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_BE80()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56AFFC;
  sub_44C910((int)this);
  ((UIFrameWnd *)(UIWnd *)this + 352)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 13904))->_UIFrameWnd();
  if ( *((_DWORD *)this + 3469) )
  {
    operator delete(*((void **)this + 3469));
    *((_DWORD *)this + 3469) = 0;
  }
  *((_DWORD *)this + 3365) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13804, 0x10u, 3, (void (*)(void *))sub_44BD80);
  ((UIWnd *)((char *)this + 13460))->Destroy2();
  *((_DWORD *)this + 3267) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13412, 0x10u, 3, (void (*)(void *))sub_44BD80);
  ((UIWnd *)((char *)this + 13068))->Destroy2();
  *((_DWORD *)this + 3169) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13020, 0x10u, 3, (void (*)(void *))sub_44BD80);
  ((UIWnd *)((char *)this + 12676))->Destroy2();
  *((_DWORD *)this + 3071) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 12628, 0x10u, 3, (void (*)(void *))sub_44BD80);
  ((UIWnd *)((char *)this + 12284))->Destroy2();
  *((_DWORD *)this + 2973) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 12236, 0x10u, 3, (void (*)(void *))sub_44BD80);
  ((UIWnd *)((char *)this + 11892))->Destroy2();
  *((_DWORD *)this + 2875) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 11844, 0x10u, 3, (void (*)(void *))sub_44BD80);
  ((UIWnd *)((char *)this + 11500))->Destroy2();
  sub_4431D0((UIWnd *)((char *)this + 11308));
  sub_4431D0((UIWnd *)((char *)this + 11116));
  ((UIWnd *)((char *)this + 10952))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 270)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 10648))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 10496))->_UIFrameWnd();
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
  ((UIFrameWnd *)(UIWnd *)this + 9)->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x0044F050
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_F050(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56B094;
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
int UIWnd::ctor_FFE0(int _this)
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(this + 76))->UIFrameWnd();
  *(_DWORD *)this = &off_56B0B4;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 8) = -1;
  return this;
}

// 0x00450090
void UIWnd::ctor_90()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B0B4;
  ((UIWnd *)&this->m_childs.m_nSize)->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00450710
_DWORD * UIWnd::ctor_710()
{
  ((UIListBox *)this)->UIListBox();
  ((UIWnd *)&this->m_childs)->ctor_F7F0();
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B100;
  *((_DWORD *)this + 81) = 1120403456;
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x00450790
void UIWnd::ctor_790()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B100;
  ((UIWnd *)&this->m_childs)->~UIWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00451CC0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_1CC0(int _this)
{
  ((UIWnd *)this)->UIWnd();
  ((UIWnd *)(this + 68))->ctor_F7F0();
  ((UIWnd *)(this + 312))->ctor_F7F0();
  `eh vector constructor iterator'(
    (char *)(this + 556),
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 1012))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 1172),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)this = &off_56B19C;
  *(_DWORD *)(this + 1168) = 0;
  return this;
}

// 0x00451DA0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_1DA0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56B19C;
  `eh vector destructor iterator'((char *)this + 1172, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 1012))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 556, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 312))->~UIWnd();
  ((UIWnd *)((char *)this + 68))->~UIWnd();
  this->_UIWnd();
}

// 0x00452600
void UIWnd::ctor_2600()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B1BC;
  ((UIWnd *)((char *)this + 1084))->ctor_1DA0();
  ((UIWnd *)&this->m_childs)->ctor_2850();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00452790
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int UIWnd::ctor_2790(int _this)
{
  ((UIWnd *)this)->UIWnd();
  ((UIScene *)(this + 68))->_UIScene();
  ((UIFrameWnd *)(this + 412))->UIFrameWnd();
  ((UIWnd *)(this + 564))->ctor_2E10();
  sub_444F60((UIWnd *)(this + 748));
  ((UIWnd *)(this + 940))->DestroyChildren();
  *(_DWORD *)this = &off_56B1DC;
  *(_DWORD *)(this + 1008) = 0;
  return this;
}

// 0x00452850
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_2850(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56B1DC;
  ((j_UIWnd *)(char *)this + 940)->MoveWindow();
  sub_445010((UIWnd *)((char *)this + 748));
  ((UIWnd *)((char *)this + 564))->ctor_2E80();
  ((UIWnd *)((char *)this + 412))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 68))->Destroy2();
  this->_UIWnd();
}

// 0x00452FD0
int UIWnd::ctor_2FD0(int _this)
{
  char v3; // [esp+7h] [ebp-1h]

  ((UIWnd *)this)->UIWnd();
  *(_BYTE *)(this + 68) = v3;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 80) = 0;
  *(_BYTE *)(this + 84) = v3;
  *(_DWORD *)(this + 88) = 0;
  *(_DWORD *)(this + 92) = 0;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)this = &off_56B200;
  *(_BYTE *)(this + 100) = 1;
  return this;
}

// 0x00453030
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void UIWnd::ctor_3030(UIWnd *this)
{
  int v2; // eax
  _BYTE *v3; // ecx
  char v4; // al
  int v5; // eax
  _BYTE *v6; // ecx
  char v7; // al

  *(_DWORD *)this->_data = &off_56B200;
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
int UIWnd::ctor_3D10(int _this)
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(this + 360))->UIFrameWnd();
  ((UIFrameWnd *)(this + 512))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 664),
    0x178u,
    3,
    (void (*)(void *))sub_43B3E0,
    (void (*)(void *))sub_43B4D0);
  ((UIScene *)(this + 1792))->_UIScene();
  ((UIFrameWnd *)(this + 2136))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2288))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2440))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2592))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2744))->UIFrameWnd();
  ((UIScene *)(this + 2896))->_UIScene();
  ((UIScene *)(this + 3240))->_UIScene();
  ((UIScene *)(this + 3584))->_UIScene();
  ((UIItem *)(this + 3928))->Refresh();
  *(_DWORD *)(this + 5312) = 0;
  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)this = &off_56B22C;
  *(_DWORD *)(this + 80) = 800;
  *(_DWORD *)(this + 84) = 600;
  return this;
}

// 0x00453E70
void UIWnd::ctor_3E70()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B22C;
  ((UIItem *)(UIItem *)this + 3928)->UIItem();
  ((UIWnd *)((char *)this + 3584))->Destroy2();
  ((UIScene *)(UIWnd *)this + 81)->Destroy2();
  ((UIWnd *)((char *)this + 2896))->Destroy2();
  ((UIWnd *)((char *)this + 2744))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 2592))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 61)->_UIFrameWnd();
  ((UIWnd *)(this + 22))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 2136))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1792))->Destroy2();
  `eh vector destructor iterator'((char *)this + 664, 0x178u, 3, (void (*)(void *))sub_43B4D0);
  ((UIWnd *)((char *)this + 512))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 9)->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00454590
int UIWnd::ctor_4590(int _this, int a2, int a3, int a4)
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
        sub_4544F0((_DWORD *)this);
        *(_BYTE *)(this + 5308) = 0;
      }
      return 1;
    case 1001:
      v6 = 0;
      v7 = dword_56B220;
      do
      {
        if ( a3 == *v7 )
        {
          *(_DWORD *)(this + 5304) = v6 + 1;
          v15 = off_5ABBE0;
          Instance = (char *)CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v15, 1);
          sub_454420(this, 1u);
          sub_4543C0(this, 0);
          return 1;
        }
        ++v7;
        ++v6;
      }
      while ( (int)v7 < (int)&off_56B22C );
      switch ( a3 )
      {
        case 193:
          sub_44C970(*(_DWORD **)(this + 5312), 0);
          break;
        case -1431699013:
          v9 = *(_DWORD *)(this + 5312);
          v17 = *(_DWORD *)(this + 5304);
          *(_BYTE *)(this + 5308) = 1;
          sub_44DB50(v9, v17);
          v16 = off_5ABBE0;
LABEL_16:
          v10 = (char *)CScreenMode::GetInstance();
          ((CScreenMode *)v10)->AudioSetPosition(v16, 1);
          return 1;
        case -1431698501:
          sub_454420(this, 0);
          sub_4543C0(this, 1u);
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
            sprintf((char *const)(this + 104), "%s\\n%s\\n%s\\n%s", byte_DD313C, byte_DD323C, byte_DD333C, byte_DD343C);
        }
        else
        {
          sprintf((char *const)(this + 104), "%s\\n%s\\n%s\\n%s", byte_DD2D3C, byte_DD2E3C, byte_DD2F3C, byte_DD303C);
        }
      }
      else
      {
        sprintf((char *const)(this + 104), "%s\\n%s\\n%s", byte_DD2A3C, byte_DD2B3C, byte_DD2C3C);
      }
      ((UIWnd *)(this + 512))->SetEnable((const char *)(this + 104), 0);
      return 1;
    case 1003:
      v14 = dword_56B220;
      do
      {
        if ( a3 == *v14 )
          ((UIWnd *)(this + 512))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
        ++v14;
      }
      while ( (int)v14 < (int)&off_56B22C );
      return 1;
    default:
      return a2->SendMessage(a3, a4);
  }
}

// 0x00454830
int UIWnd::ctor_4830(int _this)
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(this + 360))->UIFrameWnd();
  ((UIScene *)(this + 512))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 892),
    0xDE8u,
    36,
    (void (*)(void *))sub_4549A0,
    (void (*)(void *))sub_454AA0);
  ((UIFrameWnd *)(this + 129052))->UIFrameWnd();
  ((UIFrameWnd *)(this + 129204))->UIFrameWnd();
  ((UIScene *)(this + 129356))->_UIScene();
  ((UIScene *)(this + 129700))->_UIScene();
  ((UIWnd *)(this + 130060))->ctor_BCE0();
  *(_DWORD *)(this + 130340) = 92;
  *(_DWORD *)(this + 130344) = 610;
  *(_DWORD *)(this + 130348) = 0;
  *(_DWORD *)(this + 130352) = 0;
  *(_DWORD *)(this + 130356) = 0;
  ((UIItem *)(this + 130364))->Refresh();
  ((UIItem *)(this + 131732))->Refresh();
  *(_DWORD *)(this + 133100) = 0;
  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 130360) = 0;
  *(_DWORD *)this = &off_56B274;
  *(_DWORD *)(this + 80) = 800;
  *(_DWORD *)(this + 84) = 600;
  memset((void *)(this + 856), 0, 0x24u);
  return this;
}

// 0x00454BA0
void UIWnd::ctor_4BA0()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B274;
  ((UIItem *)(UIItem *)this + 131732)->UIItem();
  ((UIItem *)(UIItem *)this + 130364)->UIItem();
  ((UIWnd *)((char *)this + 130060))->~UIWnd();
  ((UIWnd *)((char *)this + 129700))->Destroy2();
  ((UIWnd *)((char *)this + 129356))->Destroy2();
  ((UIWnd *)((char *)this + 129204))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 129052))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 892, 0xDE8u, 36, (void (*)(void *))sub_454AA0);
  ((UIWnd *)((char *)this + 512))->Destroy2();
  ((UIFrameWnd *)(UIWnd *)this + 9)->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00456AB0
int UIWnd::ctor_6AB0(int _this)
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(this + 360))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 512),
    0x178u,
    52,
    (void (*)(void *))sub_43B3E0,
    (void (*)(void *))sub_43B4D0);
  ((UIScene *)(this + 20064))->_UIScene();
  ((UIFrameWnd *)(this + 20408))->UIFrameWnd();
  *(_DWORD *)(this + 20564) = 0;
  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)this = &off_56B364;
  *(_DWORD *)(this + 80) = 800;
  *(_DWORD *)(this + 84) = 600;
  return this;
}

// 0x00456B80
void UIWnd::ctor_6B80()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B364;
  ((UIWnd *)((char *)this + 20408))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 20064))->Destroy2();
  `eh vector destructor iterator'((char *)this + 512, 0x178u, 52, (void (*)(void *))sub_43B4D0);
  ((UIFrameWnd *)(UIWnd *)this + 9)->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00457070
int UIWnd::ctor_7070(int _this, int a2, int a3, int a4)
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
      sub_456EE0((char *)this);
      *(_BYTE *)(this + 20560) = 0;
      result = 1;
      break;
    case 1001:
      v6 = 0;
      v7 = dword_56B294;
      do
      {
        if ( a3 == *v7 )
        {
          sprintf((char *const)(this + 104), "Movie\\%s.bik", (const char *)(30 * v6 + 5967612));
          ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->CreateDevice(this + 104, g_Input.KeyInfo[175].PressTime, 0, 0);
          v14 = (600 - ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->GetHeight()) / 2;
          Width = ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->GetWidth();
          ((CScreenMode *)&g_GDB.m_ItemData[360].desc[144])->SetViewport((800 - Width) / 2, v14);
          sub_456E20((void (***)(_DWORD, _DWORD))this, 0);
          *(_BYTE *)(this + 20560) = 1;
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
      sub_44C970(*(_DWORD **)(this + 20564), 0);
      result = 1;
      break;
    case 1002:
      v10 = 0;
      v11 = dword_56B294;
      do
      {
        if ( a3 == *v11 )
        {
          ((UIWnd *)(this + 20408))->SetEnable(&byte_DD553C[256 * v10], 0);
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
      ((UIWnd *)(this + 20408))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
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
int UIWnd::ctor_90D0(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 120) = 800;
  *(_DWORD *)(this + 124) = 64;
  *(_DWORD *)(this + 136) = 360;
  *(_DWORD *)(this + 140) = 136;
  *(_BYTE *)(this + 152) = 0;
  ((UIFrameWnd *)(this + 164))->UIFrameWnd();
  ((UIFrameWnd *)(this + 316))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 468),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)(this + 1228))->_UIScene();
  ((UIScene *)(this + 1572))->_UIScene();
  ((UIScene *)(this + 1916))->_UIScene();
  ((UIScene *)(this + 2260))->_UIScene();
  *(_BYTE *)(this + 2604) = 0;
  ((UIScene *)(this + 2608))->_UIScene();
  ((UIFrameWnd *)(this + 2952))->UIFrameWnd();
  ((UIFrameWnd *)(this + 3104))->UIFrameWnd();
  *(_DWORD *)(this + 3256) = 0;
  *(_DWORD *)(this + 3260) = 0;
  *(_DWORD *)(this + 3264) = 0;
  *(_DWORD *)(this + 3268) = 0;
  *(_DWORD *)this = &off_56B394;
  *(_DWORD *)(this + 112) = 88;
  *(_DWORD *)(this + 116) = 138;
  *(_DWORD *)(this + 128) = 90;
  *(_DWORD *)(this + 132) = 24;
  *(_WORD *)(this + 160) = 0;
  *(_DWORD *)(this + 3272) = 0;
  *(_BYTE *)(this + 3284) = 1;
  return this;
}

// 0x00459260
void UIWnd::ctor_9260()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B394;
  sub_459360((int)this);
  ((UIWnd *)((char *)this + 3104))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 2952))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 2608))->Destroy2();
  ((UIWnd *)((char *)this + 2260))->Destroy2();
  ((UIWnd *)((char *)this + 1916))->Destroy2();
  ((UIWnd *)((char *)this + 1572))->Destroy2();
  ((UIWnd *)((char *)this + 1228))->Destroy2();
  `eh vector destructor iterator'((char *)this + 468, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 316))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 164))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x0045A7B0
int UIWnd::ctor_A7B0(int _this)
{
  _DWORD *v2; // eax
  _DWORD *v3; // ebp
  bool v4; // zf
  int v5; // kr00_4
  char *v7; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 72) = 800;
  *(_DWORD *)(this + 76) = 600;
  *(_DWORD *)(this + 336) = 0;
  *(_DWORD *)(this + 340) = 0;
  *(_DWORD *)(this + 352) = 0;
  *(_DWORD *)(this + 356) = 0;
  *(_DWORD *)(this + 360) = 0;
  *(_DWORD *)(this + 364) = 0;
  *(_BYTE *)(this + 368) = 0;
  *(_DWORD *)(this + 372) = 1090519040;
  *(_WORD *)(this + 378) = 0;
  *(_DWORD *)(this + 14272) = 0;
  v8 = 5;
  *(_DWORD *)(this + 14276) = 0;
  memset((void *)(this + 14280), 0, 0x640u);
  memset((void *)(this + 17480), 0, 0x190u);
  memset((void *)(this + 15880), 0, 0x640u);
  v2 = (_DWORD *)(this + 17884);
  *(_DWORD *)(this + 376) = 0;
  *(_DWORD *)(this + 17880) = 0;
  v7 = (char *)(this + 17884);
  v3 = (_DWORD *)(this + 18744);
  while ( 1 )
  {
    *v2 = 0;
    *((_WORD *)v3 - 428) = 0;
    lstrcpyA((LPSTR)v3 - 854, (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    lstrcpyA((LPSTR)v3 - 342, (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    lstrcpyA((LPSTR)v3 - 312, (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    lstrcpyA((LPSTR)v3 - 260, (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
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
    v7 += 1408;
    --v8;
    if ( v4 )
      break;
    v2 = v7;
  }
  ((UIFrameWnd *)(this + 24940))->UIFrameWnd();
  ((UIWnd *)(this + 25092))->ctor_D830();
  ((UIFrameWnd *)(this + 25176))->UIFrameWnd();
  ((UIWnd *)(this + 25328))->ctor_A160();
  `eh vector constructor iterator'(
    (char *)(this + 25492),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 26356),
    0x98u,
    240,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)(this + 66916) = 0;
  `eh vector constructor iterator'(
    (char *)(this + 71000),
    0x34u,
    240,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  `eh vector constructor iterator'(
    (char *)(this + 83480),
    0xB4u,
    30,
    (void (*)(void *))sub_444A20,
    (void (*)(void *))sub_444AC0);
  `eh vector constructor iterator'(
    (char *)(this + 88880),
    0x98u,
    30,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_BYTE *)(this + 93440) = 0;
  *(_BYTE *)(this + 93471) = 0;
  *(_DWORD *)(this + 93472) = 0;
  *(_DWORD *)(this + 93596) = 0;
  *(_DWORD *)(this + 93600) = 0;
  ((UIWnd *)(this + 93616))->ctor_9030();
  ((UIItem *)(this + 93924))->Refresh();
  ((UIFrameWnd *)(this + 95292))->UIFrameWnd();
  ((UIFrameWnd *)(this + 95444))->UIFrameWnd();
  ((UIFrameWnd *)(this + 95596))->UIFrameWnd();
  ((UIFrameWnd *)(this + 95748))->UIFrameWnd();
  ((UIScene *)(this + 95916))->_UIScene();
  ((UIScene *)(this + 96260))->_UIScene();
  ((UIFrameWnd *)(this + 96604))->UIFrameWnd();
  ((UIFrameWnd *)(this + 96772))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 96924),
    0x98u,
    13,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 98900))->UIFrameWnd();
  ((UIFrameWnd *)(this + 99052))->UIFrameWnd();
  ((UIListBox *)(this + 99204))->UpdateKeyCtrl();
  ((UIScene *)(this + 100460))->_UIScene();
  ((UIScene *)(this + 100804))->_UIScene();
  *(_DWORD *)(this + 101148) = 32;
  *(_DWORD *)(this + 101152) = 16;
  *(_DWORD *)(this + 101156) = 0;
  *(_DWORD *)(this + 101160) = 0;
  ((UIFrameWnd *)(this + 101176))->UIFrameWnd();
  ((UIFrameWnd *)(this + 101328))->UIFrameWnd();
  ((UIFrameWnd *)(this + 101496))->UIFrameWnd();
  ((UIFrameWnd *)(this + 101664))->UIFrameWnd();
  ((UIFrameWnd *)(this + 101832))->UIFrameWnd();
  ((UIScene *)(this + 102000))->_UIScene();
  ((UIScene *)(this + 102364))->_UIScene();
  ((UIScene *)(this + 102724))->_UIScene();
  ((UIScene *)(this + 103084))->_UIScene();
  ((UIScene *)(this + 103444))->_UIScene();
  ((UIScene *)(this + 103788))->_UIScene();
  ((UIScene *)(this + 104132))->_UIScene();
  ((UIScene *)(this + 104476))->_UIScene();
  ((UIScene *)(this + 104820))->_UIScene();
  ((UIFrameWnd *)(this + 105196))->UIFrameWnd();
  *(_BYTE *)(this + 105348) = 0;
  *(_BYTE *)(this + 105349) = 0;
  *(_BYTE *)(this + 105862) = 0;
  *(_DWORD *)(this + 105864) = 0;
  *(_DWORD *)(this + 105868) = -1;
  *(_DWORD *)(this + 105872) = -1;
  *(_BYTE *)(this + 105876) = 0;
  *(_DWORD *)(this + 105880) = 0;
  *(_DWORD *)(this + 105884) = 0;
  *(_DWORD *)(this + 105892) = 0;
  *(_DWORD *)(this + 105896) = 0;
  *(_BYTE *)(this + 105900) = 0;
  *(_BYTE *)(this + 105908) = 0;
  *(_DWORD *)this = &off_56B5CC;
  lstrcpyA((LPSTR)(this + 105350), byte_DC333C);
  lstrcpyA((LPSTR)(this + 105606), byte_DC343C);
  memset((void *)(this + 376), 0, 0x4460u);
  memset((void *)(this + 17884), 0, 0x580u);
  *(_BYTE *)(this + 26348) = 1;
  *(_BYTE *)(this + 26352) = 0;
  *(_BYTE *)(this + 26351) = 0;
  *(_BYTE *)(this + 26350) = 0;
  *(_BYTE *)(this + 26349) = 0;
  memset((void *)(this + 93441), 0, 0x1Cu);
  *(_WORD *)(this + 93469) = 0;
  memset((void *)(this + 93476), 0xFFu, 0x78u);
  memset((void *)(this + 66676), 0, 0xF0u);
  memset((void *)(this + 66920), 0, 0xF0u);
  *(_DWORD *)(this + 93604) = 0;
  *(_DWORD *)(this + 93608) = 0;
  *(_WORD *)(this + 93612) = 0;
  v5 = *(_DWORD *)(this + 76);
  *(_DWORD *)(this + 26332) = 68;
  *(_DWORD *)(this + 26336) = v5 / 4;
  *(_DWORD *)(this + 26340) = 65;
  *(_DWORD *)(this + 26344) = 86;
  *(_DWORD *)(this + 105888) = 0;
  return this;
}

// 0x0045AE60
void UIWnd::ctor_AE60()
{
  void *v2; // eax

  this->m_fontcolor.ColorQuadFmt = (int)&off_56B5CC;
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
  ((UIListBox **)this)->SetScrollPos();
  ((UIWnd *)((char *)this + 105196))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 104820))->Destroy2();
  ((UIWnd *)((char *)this + 104476))->Destroy2();
  ((UIWnd *)((char *)this + 104132))->Destroy2();
  ((UIWnd *)((char *)this + 103788))->Destroy2();
  ((UIWnd *)((char *)this + 103444))->Destroy2();
  ((UIWnd *)((char *)this + 103084))->Destroy2();
  ((UIWnd *)((char *)this + 102724))->Destroy2();
  ((UIWnd *)((char *)this + 102364))->Destroy2();
  ((UIScene *)(UIWnd *)this + 2550)->Destroy2();
  ((UIWnd *)((char *)this + 101832))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 101664))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 101496))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 101328))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 101176))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 100804))->Destroy2();
  ((UIWnd *)((char *)this + 100460))->Destroy2();
  ((UIWnd *)((char *)this + 99204))->DeleteRow();
  ((UIWnd *)((char *)this + 99052))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 98900))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 96924, 0x98u, 13, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 96772))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 96604))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 96260))->Destroy2();
  ((UIWnd *)((char *)this + 95916))->Destroy2();
  ((UIWnd *)((char *)this + 95748))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 95596))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 95444))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 95292))->_UIFrameWnd();
  ((UIItem *)(UIItem *)this + 93924)->UIItem();
  ((UIWnd *)((char *)this + 93616))->ctor_9130();
  `eh vector destructor iterator'((char *)this + 88880, 0x98u, 30, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 83480, 0xB4u, 30, (void (*)(void *))sub_444AC0);
  `eh vector destructor iterator'((char *)this + 71000, 0x34u, 240, (void (*)(void *))nullsub_1);
  `eh vector destructor iterator'(
    (char *)this + 26356,
    0x98u,
    240,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 25492, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 25328))->ctor_A1F0();
  ((UIWnd *)((char *)this + 25176))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 25092))->ctor_D880();
  ((UIWnd *)((char *)this + 24940))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x0046D140
int UIWnd::ctor_D140(int _this)
{
  int v2; // eax

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 72) = 800;
  *(_DWORD *)(this + 76) = 600;
  *(_DWORD *)(this + 80) = 300;
  *(_DWORD *)(this + 84) = 400;
  *(_WORD *)(this + 90) = 0;
  *(_DWORD *)(this + 13984) = 0;
  *(_DWORD *)(this + 13988) = 0;
  memset((void *)(this + 13992), 0, 0x640u);
  memset((void *)(this + 17192), 0, 0x190u);
  memset((void *)(this + 15592), 0, 0x640u);
  *(_DWORD *)(this + 88) = 0;
  *(_DWORD *)(this + 17592) = 0;
  *(_DWORD *)(this + 18112) = 0;
  *(_DWORD *)(this + 18116) = 0;
  *(_DWORD *)(this + 18128) = 0;
  *(_DWORD *)(this + 18132) = 0;
  *(_DWORD *)(this + 18136) = 0;
  *(_BYTE *)(this + 18140) = 0;
  ((UIFrameWnd *)(this + 18144))->UIFrameWnd();
  ((UIWnd *)(this + 18296))->ctor_D830();
  ((UIFrameWnd *)(this + 18380))->UIFrameWnd();
  ((UIScene *)(this + 18548))->_UIScene();
  ((UIWnd *)(this + 18892))->ctor_A160();
  `eh vector constructor iterator'(
    (char *)(this + 19056),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIItem *)(this + 19920))->Refresh();
  ((UIWnd *)(this + 21288))->ctor_9030();
  ((UIFrameWnd *)(this + 21596))->UIFrameWnd();
  ((UIFrameWnd *)(this + 21764))->UIFrameWnd();
  ((UIFrameWnd *)(this + 21916))->UIFrameWnd();
  ((UIFrameWnd *)(this + 22068))->UIFrameWnd();
  ((UIFrameWnd *)(this + 22220))->UIFrameWnd();
  ((UIFrameWnd *)(this + 22388))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 22540),
    0x98u,
    13,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 24516))->UIFrameWnd();
  ((UIFrameWnd *)(this + 24668))->UIFrameWnd();
  ((UIListBox *)(this + 24836))->UpdateKeyCtrl();
  ((UIScene *)(this + 26092))->_UIScene();
  ((UIScene *)(this + 26436))->_UIScene();
  *(_DWORD *)(this + 26780) = 32;
  *(_DWORD *)(this + 26784) = 16;
  *(_DWORD *)(this + 26788) = 0;
  *(_DWORD *)(this + 26792) = 0;
  ((UIFrameWnd *)(this + 26808))->UIFrameWnd();
  ((UIFrameWnd *)(this + 26960))->UIFrameWnd();
  ((UIFrameWnd *)(this + 27112))->UIFrameWnd();
  ((UIFrameWnd *)(this + 27264))->UIFrameWnd();
  ((UIFrameWnd *)(this + 27432))->UIFrameWnd();
  ((UIScene *)(this + 27600))->_UIScene();
  ((UIScene *)(this + 27964))->_UIScene();
  ((UIScene *)(this + 28324))->_UIScene();
  ((UIFrameWnd *)(this + 28700))->UIFrameWnd();
  *(_DWORD *)(this + 28852) = 0;
  *(_DWORD *)(this + 28856) = 0;
  *(_DWORD *)(this + 28860) = 0;
  *(_BYTE *)(this + 28864) = 0;
  *(_BYTE *)(this + 28865) = 0;
  *(_DWORD *)(this + 28868) = 0;
  *(_DWORD *)(this + 28872) = 1065353216;
  *(_DWORD *)(this + 28876) = 0;
  *(_DWORD *)this = &off_56B688;
  memset((void *)(this + 88), 0, 0x4460u);
  v2 = *(_DWORD *)(this + 76);
  *(_BYTE *)(this + 19912) = 1;
  *(_BYTE *)(this + 19916) = 0;
  *(_DWORD *)(this + 19900) = v2 / 4;
  *(_BYTE *)(this + 19915) = 0;
  *(_BYTE *)(this + 19914) = 0;
  *(_BYTE *)(this + 19913) = 0;
  *(_DWORD *)(this + 19896) = 68;
  *(_DWORD *)(this + 19904) = 65;
  *(_DWORD *)(this + 19908) = 86;
  *(_BYTE *)(this + 28888) = 1;
  return this;
}

// 0x0046D4E0
void UIWnd::ctor_D4E0()
{
  void *v2; // eax

  this->m_fontcolor.ColorQuadFmt = (int)&off_56B688;
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
  ((UIListBox **)this)->SetScrollPos();
  ((UIWnd *)((char *)this + 28700))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 28324))->Destroy2();
  ((UIWnd *)((char *)this + 27964))->Destroy2();
  ((UIScene *)(UIWnd *)this + 690)->Destroy2();
  ((UIWnd *)((char *)this + 27432))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 27264))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 27112))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 674)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 26808))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 26436))->Destroy2();
  ((UIWnd *)((char *)this + 26092))->Destroy2();
  ((UIWnd *)((char *)this + 24836))->DeleteRow();
  ((UIWnd *)((char *)this + 24668))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 24516))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 22540, 0x98u, 13, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 22388))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 22220))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 22068))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 21916))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 21764))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 21596))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 21288))->ctor_9130();
  ((UIItem *)(UIItem *)this + 19920)->UIItem();
  `eh vector destructor iterator'((char *)this + 19056, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 18892))->ctor_A1F0();
  ((UIWnd *)((char *)this + 18548))->Destroy2();
  ((UIWnd *)((char *)this + 18380))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 18296))->ctor_D880();
  ((UIWnd *)((char *)this + 18144))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00470A60
int UIWnd::ctor_A60(int _this)
{
  _DWORD *v2; // eax
  int v3; // ecx
  _DWORD *v4; // eax
  int v5; // ecx
  int v6; // eax

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 72) = 800;
  *(_DWORD *)(this + 76) = 600;
  *(_DWORD *)(this + 592) = -1;
  *(_WORD *)(this + 598) = 0;
  *(_DWORD *)(this + 14492) = 0;
  *(_DWORD *)(this + 14496) = 0;
  memset((void *)(this + 14500), 0, 0x640u);
  memset((void *)(this + 17700), 0, 0x190u);
  memset((void *)(this + 16100), 0, 0x640u);
  *(_DWORD *)(this + 596) = 0;
  v2 = (_DWORD *)(this + 46832);
  v3 = 1794;
  do
  {
    *v2 = 0xFFFF;
    v2[1] = 0;
    v2[2] = 0;
    v2 += 3;
    --v3;
  }
  while ( v3 );
  v4 = (_DWORD *)(this + 68360);
  v5 = 1794;
  do
  {
    *v4 = 0xFFFF;
    v4[1] = 0;
    v4[2] = 0;
    v4 += 3;
    --v5;
  }
  while ( v5 );
  *(_DWORD *)(this + 100652) = 0;
  ((UIFrameWnd *)(this + 100672))->UIFrameWnd();
  ((UIWnd *)(this + 100824))->ctor_D830();
  ((UIFrameWnd *)(this + 100908))->UIFrameWnd();
  ((UIScene *)(this + 101060))->_UIScene();
  ((UIWnd *)(this + 101420))->ctor_A160();
  `eh vector constructor iterator'(
    (char *)(this + 101584),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)(this + 102424) = 250;
  *(_DWORD *)(this + 102428) = 150;
  ((UIItem *)(this + 102448))->Refresh();
  ((UIWnd *)(this + 103816))->ctor_9030();
  ((UIFrameWnd *)(this + 104140))->UIFrameWnd();
  ((UIFrameWnd *)(this + 104292))->UIFrameWnd();
  ((UIFrameWnd *)(this + 104444))->UIFrameWnd();
  ((UIFrameWnd *)(this + 104596))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 105020),
    0x158u,
    6,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)(this + 107100))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 107268),
    0xB4u,
    25,
    (void (*)(void *))sub_444A20,
    (void (*)(void *))sub_444AC0);
  ((UIWnd *)(this + 111768))->ctor_D830();
  ((UIFrameWnd *)(this + 111852))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 112004),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)(this + 113844))->UpdateKeyCtrl();
  ((UIListBox *)(this + 115056))->UpdateKeyCtrl();
  ((UIListBox *)(this + 116268))->UpdateKeyCtrl();
  ((UIListBox *)(this + 117480))->UpdateKeyCtrl();
  ((UIListBox *)(this + 118692))->UpdateKeyCtrl();
  ((UIListBox *)(this + 119904))->UpdateKeyCtrl();
  *(_DWORD *)(this + 121116) = 0;
  *(_DWORD *)(this + 121120) = 0;
  ((UIScene *)(this + 121156))->_UIScene();
  ((UIScene *)(this + 121500))->_UIScene();
  *(_DWORD *)(this + 121844) = 32;
  *(_DWORD *)(this + 121848) = 16;
  *(_DWORD *)(this + 121852) = 0;
  *(_DWORD *)(this + 121856) = 0;
  ((UIScene *)(this + 121872))->_UIScene();
  ((UIScene *)(this + 122216))->_UIScene();
  *(_DWORD *)(this + 122560) = -1;
  ((UIScene *)(this + 122580))->_UIScene();
  ((UIScene *)(this + 122924))->_UIScene();
  ((UIFrameWnd *)(this + 123268))->UIFrameWnd();
  ((UIFrameWnd *)(this + 123420))->UIFrameWnd();
  ((UIFrameWnd *)(this + 123572))->UIFrameWnd();
  ((UIFrameWnd *)(this + 123740))->UIFrameWnd();
  ((UIFrameWnd *)(this + 123908))->UIFrameWnd();
  ((UIFrameWnd *)(this + 124076))->UIFrameWnd();
  *(_BYTE *)(this + 124244) = 0;
  *(_BYTE *)(this + 124245) = 0;
  *(_DWORD *)(this + 124248) = 0;
  *(_DWORD *)this = &off_56B794;
  *(_DWORD *)(this + 121112) = 0;
  *(_DWORD *)(this + 119900) = 0;
  *(_DWORD *)(this + 118688) = 0;
  *(_DWORD *)(this + 117476) = 0;
  *(_DWORD *)(this + 116264) = 0;
  *(_DWORD *)(this + 115052) = 0;
  *(_BYTE *)(this + 46828) = 0;
  *(_BYTE *)(this + 102440) = 1;
  *(_BYTE *)(this + 102444) = 0;
  *(_BYTE *)(this + 102443) = 0;
  *(_BYTE *)(this + 102442) = 0;
  *(_BYTE *)(this + 102441) = 0;
  memset((void *)(this + 46832), 0, 0x5418u);
  memset((void *)(this + 68360), 0, 0x5418u);
  memset((void *)(this + 18100), 0, 0x3810u);
  memset((void *)(this + 32452), 0, 0x1C08u);
  memset((void *)(this + 39628), 0, 0x1C08u);
  memset((void *)(this + 89888), 0, 0x1C08u);
  memset((void *)(this + 46804), 0, 0x18u);
  lstrcpyA((LPSTR)(this + 104764), (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
  v6 = *(_DWORD *)(this + 76);
  *(_DWORD *)(this + 102424) = 68;
  *(_DWORD *)(this + 102432) = 65;
  *(_DWORD *)(this + 102428) = v6 / 4;
  *(_DWORD *)(this + 102436) = 86;
  *(_BYTE *)(this + 124264) = 1;
  return this;
}

// 0x00470F40
void UIWnd::ctor_F40()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B794;
  *((_BYTE *)this + 46828) = 0;
  *((_DWORD *)this + 31062) = 0;
  ((UIListBox **)this)->SetScrollPos();
  ((UIWnd *)((char *)this + 124076))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 123908))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 123740))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 123572))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 123420))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 123268))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 122924))->Destroy2();
  ((UIWnd *)((char *)this + 122580))->Destroy2();
  ((UIWnd *)((char *)this + 122216))->Destroy2();
  ((UIWnd *)((char *)this + 121872))->Destroy2();
  ((UIWnd *)((char *)this + 121500))->Destroy2();
  ((UIWnd *)((char *)this + 121156))->Destroy2();
  ((UIWnd *)((char *)this + 119904))->DeleteRow();
  ((UIWnd *)((char *)this + 118692))->DeleteRow();
  ((UIListBox *)(UIWnd *)this + 2937)->DeleteRow();
  ((UIWnd *)((char *)this + 116268))->DeleteRow();
  ((UIWnd *)((char *)this + 115056))->DeleteRow();
  ((UIWnd *)((char *)this + 113844))->DeleteRow();
  `eh vector destructor iterator'(
    (char *)this + 112004,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 111852))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 111768))->ctor_D880();
  `eh vector destructor iterator'((char *)this + 107268, 0xB4u, 25, (void (*)(void *))sub_444AC0);
  ((UIWnd *)((char *)this + 107100))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 105020, 0x158u, 6, (void (*)(void *))UIScene::Destroy2);
  ((UIWnd *)((char *)this + 104596))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 104444))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 104292))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 104140))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 103816))->ctor_9130();
  ((UIItem *)(UIItem *)this + 102448)->UIItem();
  `eh vector destructor iterator'((char *)this + 101584, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 101420))->ctor_A1F0();
  ((UIWnd *)((char *)this + 101060))->Destroy2();
  ((UIWnd *)((char *)this + 100908))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 100824))->ctor_D880();
  ((UIWnd *)(this + 968))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00477BB0
int UIWnd::ctor_7BB0(int _this, int arg0, int a3, int a4)
{
  int v5; // eax
  _DWORD *v6; // ebx
  int v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  void (***v11)(_DWORD, int); // ecx
  int result; // eax
  int v13; // edi
  int *v14; // eax
  int v15; // eax
  int v16; // eax
  char *Instance; // eax
  int *v18; // eax
  int v19; // eax
  const char *v20; // ebp
  int v21; // eax
  const char *v22; // ebp
  void (***v23)(_DWORD, _DWORD); // edi
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
  void (***v34)(_DWORD, int); // ebx
  int v35; // edi
  void (***v36)(_DWORD, int); // ebx
  int v37; // edi
  void (***v38)(_DWORD, int); // ebx
  int v39; // edi
  void (***v40)(_DWORD, int); // ebx
  int v41; // edi
  void (***v42)(_DWORD, int); // ebx
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
  int v72; // [esp+40h] [ebp-118h] BYREF
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
      sub_472AA0(this);
      sub_473520((char *)this, 0);
      v5 = 0;
      v6 = (_DWORD *)(this + 102348);
      v62 = 0;
      v7 = this + 107448;
      do
      {
        if ( *(_BYTE *)(this + v5 + 102440) )
        {
          v8 = *(v6 - 1) - 24;
          v66 = *v6 + 36;
          a2 = v8;
          v68 = v66 + 30;
          v67 = v8 + 24;
          ((UIWnd *)(v7 - 180))->GetRect(&a2);
          (**(void (***)(int, _DWORD))(v7 - 180))(v7 - 180, 0);
          ((UIWnd *)v7)->GetRect(&a2);
          (**(void (***)(int, _DWORD))v7)(v7, 0);
          ((UIWnd *)(v7 + 180))->GetRect(&a2);
          v9 = *v6 + 36;
          a2 = v6[1] + 18;
          v67 = a2 + 22;
          v66 = v9;
          v68 = v9 + 30;
          ((UIWnd *)(v7 + 360))->GetRect(&a2);
          (**(void (***)(int, _DWORD))(v7 + 360))(v7 + 360, 0);
          ((UIWnd *)(v7 + 540))->GetRect(&a2);
          (**(void (***)(int, _DWORD))(v7 + 540))(v7 + 540, 0);
          v5 = v62;
        }
        ++v5;
        v6 += 4;
        v7 += 900;
        v62 = v5;
      }
      while ( v5 < 5 );
      *(_DWORD *)(this + 592) = 0;
      if ( sub_43F650((int *)(this + 113844)) > 0 )
        (*(void (**)(int, int, int, _DWORD))(*(_DWORD *)this + 24))(this, 1007, 773, *(_DWORD *)(this + 592));
      else
        *(_DWORD *)(this + 592) = -1;
      if ( !*(_DWORD *)(this + 124248) )
      {
        (**(void (***)(int, int))(this + 104596))(this + 104596, 1);
        ((UIWnd *)(this + 104596))->SetEnable((const char *)(this + 1376), 0);
        v10 = lstrlenA((LPCSTR)(this + 1376));
        v11 = (void (***)(_DWORD, int))(this + 101420);
        if ( v10 > 0 )
          (**v11)(v11, 1);
        else
          (**v11)(v11, 0);
      }
      sprintf((char *const)(this + 80), "%s %d", byte_DC5F3C, g_SceneMgr.m_npc[0].m_path.normal[82].y);
      ((UIWnd *)(this + 123908))->SetEnable((const char *)(this + 80), 0);
      *(_BYTE *)(this + 121869) = 1;
      *(_BYTE *)(this + 121868) = 1;
      UICursor::IRender();
      result = 1;
      break;
    case 1001:
      v13 = 0;
      v14 = dword_56B77C;
      while ( a3 != *v14 )
      {
        ++v14;
        ++v13;
        if ( (int)v14 >= (int)&off_56B794 )
        {
          switch ( a3 )
          {
            case 770:
              sub_4777B0(this);
              v15 = *(_DWORD *)(this + 124248);
              if ( v15 )
              {
                if ( v15 == 1 )
                  sub_523820(*(_DWORD **)(this + 124256), 2);
              }
              else
              {
                sub_45A220(*(_DWORD **)(this + 124252), 0);
              }
              goto LABEL_34;
            case 788:
              sub_475FC0(this);
              v58 = off_5B9DE4;
              goto LABEL_35;
            case 789:
              sub_4765D0((void *)this);
              v16 = *(_DWORD *)(this + 124248);
              if ( v16 )
              {
                if ( v16 == 1 )
                {
                  ((UIWnd *)(this + 104596))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
                  (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
                }
              }
              else
              {
                (**(void (***)(int, int))(this + 104596))(this + 104596, 1);
                ((UIWnd *)(this + 104596))->SetEnable((const char *)(this + 1888), 0);
                (**(void (***)(int, int))(this + 101420))(this + 101420, 1);
              }
              goto LABEL_34;
            case 819:
              v59 = (UIListBox *)*(UIListBox **)(this + 121116);
              *(_DWORD *)(this + 122560) = 3;
              sub_473B50(this, v59, (unsigned int *)3);
              v58 = off_5B9DE4;
              goto LABEL_35;
            case 820:
              v60 = (UIListBox *)*(UIListBox **)(this + 121116);
              *(_DWORD *)(this + 122560) = 0;
              sub_473B50(this, v60, 0);
LABEL_34:
              v58 = off_5B9DE4;
              goto LABEL_35;
            case 821:
              v61.ColorQuadFmt = *(_DWORD *)(this + 121116);
              sub_4765F0(this, v61);
              goto LABEL_31;
            case 822:
              v61.ColorQuadFmt = *(_DWORD *)(this + 121116);
              sub_476ED0(this, v61);
LABEL_31:
              ((UIWnd *)(this + 104596))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
              (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
              result = 1;
              break;
            default:
              goto LABEL_36;
          }
          return result;
        }
      }
      sub_445E50((_DWORD *)(this + 344 * v13 + 105020), 0);
      sub_473520((char *)this, v13);
      ((UIWnd *)(this + 104596))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
      (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
      v58 = off_5B9DE4;
LABEL_35:
      Instance = (char *)CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v58, 1);
LABEL_36:
      result = 1;
      break;
    case 1005:
      (**(void (***)(int, _DWORD))(this + 121156))(this + 121156, 0);
      (**(void (***)(int, _DWORD))(this + 121500))(this + 121500, 0);
      result = 1;
      break;
    case 1007:
      *(_DWORD *)(this + 592) = a4;
      if ( a4 <= -1 )
      {
        ((UIWnd *)(this + 123420))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
        *(_DWORD *)(this + 103892) = 0;
        (**(void (***)(int, _DWORD))(this + 121156))(this + 121156, 0);
        (**(void (***)(int, _DWORD))(this + 121500))(this + 121500, 0);
        result = 1;
      }
      else
      {
        ((UIWnd *)(this + 104596))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
        (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
        sub_477A90(this, *(_DWORD *)(this + 121116), *(_DWORD *)(this + 592));
        v18 = (int *)*(int **)(this + 12 * (*(_DWORD *)(this + 592) + 299 * *(_DWORD *)(this + 121116)) + 46840);
        if ( *((_BYTE *)v18 + 613) == 5 )
        {
          sub_43A070(this + 103816, 228.0);
          sub_439930(this + 103816, 330, 280, 600);
        }
        else if ( *((_BYTE *)v18 + 612) == 11 )
        {
          sub_43A070(this + 103816, 228.0);
          sub_439930(this + 103816, 330, 272, 600);
        }
        else
        {
          v19 = *v18;
          if ( v19 == 8114 || v19 == 8132 )
          {
            sub_43A070(this + 103816, 180.0);
            sub_439930(this + 103816, 330, 252, 600);
          }
          else
          {
            sub_43A070(this + 103816, 180.0);
            sub_439930(this + 103816, 330, 268, 600);
          }
        }
        if ( !strcmp(
                (const char *)(*(_DWORD *)(this
                                         + 12 * (*(_DWORD *)(this + 592) + 299 * *(_DWORD *)(this + 121116))
                                         + 46840)
                             + 36),
                (const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y) )
        {
          sprintf((char *const)(this + 80), "%s", aNone);
        }
        else
        {
          v20 = (const char *)(*(_DWORD *)(this
                                         + 12 * (*(_DWORD *)(this + 592) + 299 * *(_DWORD *)(this + 121116))
                                         + 46840)
                             + 36);
          sprintf((char *const)(this + 80), "Item\\%s\\%s.pol", v20, v20);
        }
        sub_439230((int *)(this + 103888), (const char *)(this + 80), 0);
        v21 = *(_DWORD *)(this + 12 * (*(_DWORD *)(this + 592) + 299 * *(_DWORD *)(this + 121116)) + 46840);
        v22 = (const char *)(v21 + 36);
        v63 = (const char *)(v21 + 66);
        if ( !strcmp((const char *)(v21 + 36), (const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y) )
        {
          sprintf((char *const)(this + 80), "%s", aNone);
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v76 = 0;
          v77 = 0;
          sprintf(Buffer, "%s%s", v22, v63);
          sprintf((char *const)(this + 80), "Item\\%s\\%s.tga", v22, Buffer);
        }
        ((gbGeomNode *)*(gbGeomNode **)(this + 103904))->ReplaceTexture((const char *)(this + 80));
        *(_DWORD *)(this + 103892) = 1;
        v23 = (void (***)(_DWORD, _DWORD))(this + 107268);
        v24 = 5;
        do
        {
          v25 = 5;
          do
          {
            (**v23)(v23, 0);
            v23 += 45;
            --v25;
          }
          while ( v25 );
          --v24;
        }
        while ( v24 );
        switch ( *(_DWORD *)(this + 121116) )
        {
          case 0:
            v26 = (const char **)sub_43EBB0((_DWORD *)(this + 113844), &v72, *(_DWORD *)(this + 592));
            v27 = (const char *)*v26;
            v64 = (const char *)v26[1];
            break;
          case 1:
            v28 = (const char **)sub_43EBB0((_DWORD *)(this + 115056), &v73, *(_DWORD *)(this + 592));
            v27 = (const char *)*v28;
            v64 = (const char *)v28[1];
            break;
          case 2:
            v29 = (const char **)sub_43EBB0((_DWORD *)(this + 116268), &v74, *(_DWORD *)(this + 592));
            v27 = (const char *)*v29;
            v64 = (const char *)v29[1];
            break;
          case 3:
            v30 = (const char **)sub_43EBB0((_DWORD *)(this + 117480), &v69, *(_DWORD *)(this + 592));
            v27 = (const char *)*v30;
            v64 = (const char *)v30[1];
            break;
          case 4:
            v31 = (const char **)sub_43EBB0((_DWORD *)(this + 118692), &v70, *(_DWORD *)(this + 592));
            v27 = (const char *)*v31;
            v64 = (const char *)v31[1];
            break;
          case 5:
            v32 = (const char **)sub_43EBB0((_DWORD *)(this + 119904), &v71, *(_DWORD *)(this + 592));
            v27 = (const char *)*v32;
            v64 = (const char *)v32[1];
            switch ( *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + 612) )
            {
              case 7:
                v33 = 0;
                v34 = (void (***)(_DWORD, int))(this + 107268);
                do
                {
                  if ( *(_BYTE *)(this + v33 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v33 + 614) )
                  {
                    (**v34)(v34, 1);
                  }
                  ++v33;
                  v34 += 225;
                }
                while ( v33 < 5 );
                break;
              case 8:
                v35 = 0;
                v36 = (void (***)(_DWORD, int))(this + 107808);
                do
                {
                  if ( *(_BYTE *)(this + v35 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v35 + 614) )
                  {
                    (**v36)(v36, 1);
                  }
                  ++v35;
                  v36 += 225;
                }
                while ( v35 < 5 );
                break;
              case 9:
                v37 = 0;
                v38 = (void (***)(_DWORD, int))(this + 107988);
                do
                {
                  if ( *(_BYTE *)(this + v37 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v37 + 614) )
                  {
                    (**v38)(v38, 1);
                  }
                  ++v37;
                  v38 += 225;
                }
                while ( v37 < 5 );
                break;
              case 0xA:
                v39 = 0;
                v40 = (void (***)(_DWORD, int))(this + 107628);
                do
                {
                  if ( *(_BYTE *)(this + v39 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v39 + 614) )
                  {
                    (**v40)(v40, 1);
                  }
                  ++v39;
                  v40 += 225;
                }
                while ( v39 < 5 );
                break;
              case 0xB:
                v41 = 0;
                v42 = (void (***)(_DWORD, int))(this + 107448);
                do
                {
                  if ( *(_BYTE *)(this + v41 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v41 + 614) )
                  {
                    (**v42)(v42, 1);
                  }
                  ++v41;
                  v42 += 225;
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
        v43 = *(_DWORD *)(this + 121852);
        v44 = (int *)(this + 121124);
        v45 = (const char *)v64 - 4;
        v46 = (const char *)v27 + 162;
        if ( v43 )
        {
          if ( v43 == 1 )
          {
            v47 = *(_DWORD *)(this + 121844);
            *(_DWORD *)(this + 121144) = v45;
            *(_DWORD *)(this + 121140) = v46;
            *(_DWORD *)(this + 121148) = &v46[v47];
            *(_DWORD *)(this + 121152) = &v45[*(_DWORD *)(this + 121848)];
            ((UIWnd *)(this + 121500))->GetRect((_DWORD *)(this + 121140));
            v48 = *(_DWORD *)(this + 121148) + *(_DWORD *)(this + 121856);
            v49 = *(_DWORD *)(this + 121844);
            *(_DWORD *)(this + 121128) = *(_DWORD *)(this + 121144);
            v50 = *(_DWORD *)(this + 121152);
            *v44 = v48;
            *(_DWORD *)(this + 121136) = v50;
            *(_DWORD *)(this + 121132) = v49 + v48;
            ((UIWnd *)(this + 121156))->GetRect((_DWORD *)(this + 121124));
          }
        }
        else
        {
          v51 = *(_DWORD *)(this + 121844);
          v52 = *(_DWORD *)(this + 121848);
          *(_DWORD *)(this + 121128) = v45;
          *v44 = (int)v46;
          *(_DWORD *)(this + 121132) = &v46[v51];
          *(_DWORD *)(this + 121136) = &v45[v52];
          ((UIWnd *)(this + 121156))->GetRect((_DWORD *)(this + 121124));
          v53 = *v44;
          v54 = *(_DWORD *)(this + 121136) + *(_DWORD *)(this + 121856);
          *(_DWORD *)(this + 121144) = v54;
          *(_DWORD *)(this + 121140) = v53;
          *(_DWORD *)(this + 121148) = *(_DWORD *)(this + 121132);
          *(_DWORD *)(this + 121152) = *(_DWORD *)(this + 121848) + v54;
          ((UIWnd *)(this + 121500))->GetRect((_DWORD *)(this + 121140));
        }
        (**(void (***)(int, int))(this + 121156))(this + 121156, 1);
        (**(void (***)(int, int))(this + 121500))(this + 121500, 1);
        v55 = 299 * *(_DWORD *)(this + 121116) + *(_DWORD *)(this + 592);
        v56 = *(_DWORD *)(this + 4 * v55 + 32452);
        if ( v56 > 0 )
        {
          sub_445E50((_DWORD *)(this + 121156), v56 != *(_DWORD *)(this + 4 * v55 + 39628));
          sub_445E50((_DWORD *)(this + 121500), 1);
        }
        else
        {
          sub_445E50((_DWORD *)(this + 121156), 1);
          sub_445E50((_DWORD *)(this + 121500), 0);
        }
        result = 1;
      }
      break;
    case 1009:
      if ( a3 == 801 )
      {
        v57 = HIWORD(a4);
        if ( (unsigned __int16)a4 > *(int *)(this + 104748)
          && (unsigned __int16)a4 < *(int *)(this + 104756)
          && v57 > *(_DWORD *)(this + 104752)
          && v57 < *(_DWORD *)(this + 104760) )
        {
          ((UIWnd *)(this + 104596))->SetEnable((const char *)&g_SceneMgr.m_npc[5].m_path.normal[140].y, 0);
          (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
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
int UIWnd::ctor_9300(int _this)
{
  _DWORD *v2; // eax
  int v3; // ecx
  _DWORD *v4; // eax
  int v5; // ecx
  _DWORD *v6; // eax
  int v7; // ecx
  _DWORD *v8; // eax
  int v9; // ecx

  ((UIListBox *)this)->UIListBox();
  v2 = (_DWORD *)(this + 360);
  v3 = 99;
  do
  {
    *v2 = 0xFFFF;
    v2[1] = 0;
    v2[2] = 0;
    v2 += 3;
    --v3;
  }
  while ( v3 );
  v4 = (_DWORD *)(this + 1548);
  v5 = 99;
  do
  {
    *v4 = 0xFFFF;
    v4[1] = 0;
    v4[2] = 0;
    v4 += 3;
    --v5;
  }
  while ( v5 );
  v6 = (_DWORD *)(this + 2736);
  v7 = 99;
  do
  {
    *v6 = 0xFFFF;
    v6[1] = 0;
    v6[2] = 0;
    v6 += 3;
    --v7;
  }
  while ( v7 );
  v8 = (_DWORD *)(this + 3924);
  v9 = 99;
  do
  {
    *v8 = 0xFFFF;
    v8[1] = 0;
    v8[2] = 0;
    v8 += 3;
    --v9;
  }
  while ( v9 );
  *(_DWORD *)(this + 162820) = 0xFFFF;
  *(_DWORD *)(this + 162824) = 0;
  *(_DWORD *)(this + 162828) = 0;
  *(_DWORD *)(this + 162832) = 0xFFFF;
  *(_DWORD *)(this + 162836) = 0;
  *(_DWORD *)(this + 162840) = 0;
  *(_DWORD *)(this + 162844) = 0xFFFF;
  *(_DWORD *)(this + 162848) = 0;
  *(_DWORD *)(this + 162852) = 0;
  ((UIWnd *)(this + 162880))->ctor_D830();
  ((UIFrameWnd *)(this + 162964))->UIFrameWnd();
  ((UIFrameWnd *)(this + 163116))->UIFrameWnd();
  ((UIFrameWnd *)(this + 163268))->UIFrameWnd();
  ((UIFrameWnd *)(this + 163420))->UIFrameWnd();
  ((UIFrameWnd *)(this + 163572))->UIFrameWnd();
  ((UIWnd *)(this + 163724))->ctor_A160();
  ((UIFrameWnd *)(this + 163888))->UIFrameWnd();
  ((UIFrameWnd *)(this + 164040))->UIFrameWnd();
  ((UIFrameWnd *)(this + 164192))->UIFrameWnd();
  ((UIFrameWnd *)(this + 164344))->UIFrameWnd();
  ((UIFrameWnd *)(this + 164496))->UIFrameWnd();
  ((UIFrameWnd *)(this + 164648))->UIFrameWnd();
  ((UIFrameWnd *)(this + 164800))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 164952),
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 166472))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 166624),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)(this + 167232))->UpdateKeyCtrl();
  ((UIScene *)(this + 168440))->_UIScene();
  ((UIScene *)(this + 168784))->_UIScene();
  ((UIScene *)(this + 169128))->_UIScene();
  ((UIItem *)(this + 169472))->Refresh();
  ((UIItem *)(this + 170840))->Refresh();
  ((UIItem *)(this + 172208))->Refresh();
  ((UIWnd *)(this + 173576))->ctor_9030();
  *(_BYTE *)(this + 173892) = 0;
  *(_DWORD *)(this + 173888) = 0;
  *(_DWORD *)(this + 173884) = 0;
  *(_BYTE *)(this + 173904) = 0;
  *(_DWORD *)(this + 173900) = 0;
  *(_DWORD *)(this + 173896) = 0;
  `eh vector constructor iterator'(
    (char *)(this + 173948),
    0x248u,
    60,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  *(_DWORD *)this = &off_56B820;
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 100) = 0;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 162856) = 0;
  *(_DWORD *)(this + 162860) = 0;
  *(_DWORD *)(this + 162864) = 0;
  *(_DWORD *)(this + 162868) = -1;
  *(_DWORD *)(this + 162872) = 0;
  memset((void *)(this + 162720), 0, 0x60u);
  *(_WORD *)(this + 162816) = 0;
  *(_BYTE *)(this + 162818) = 0;
  *(_DWORD *)(this + 162828) = 0;
  *(_DWORD *)(this + 162832) = 0;
  *(_DWORD *)(this + 162836) = 0;
  *(_DWORD *)(this + 162840) = 0;
  *(_DWORD *)(this + 162844) = 0;
  *(_DWORD *)(this + 162848) = 0;
  *(_BYTE *)(this + 173940) = 0;
  *(_BYTE *)(this + 173941) = 1;
  return this;
}

// 0x00479680
void UIWnd::ctor_9680()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B820;
  `eh vector destructor iterator'((char *)this + 173948, 0x248u, 60, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)(this + 1669))->ctor_9130();
  ((UIItem *)(UIItem *)this + 172208)->UIItem();
  ((UIItem *)(UIItem *)this + 170840)->UIItem();
  ((UIItem *)(UIItem *)this + 169472)->UIItem();
  ((UIWnd *)((char *)this + 169128))->Destroy2();
  ((UIWnd *)((char *)this + 168784))->Destroy2();
  ((UIScene *)(UIWnd *)this + 4211)->Destroy2();
  ((UIWnd *)(this + 1608))->DeleteRow();
  `eh vector destructor iterator'((char *)this + 166624, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 166472))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 164952,
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(UIWnd *)this + 4120)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 164648))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 164496))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 164344))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 164192))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 4101)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 163888))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 163724))->ctor_A1F0();
  ((UIWnd *)((char *)this + 163572))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 163420))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 163268))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 163116))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 162964))->_UIFrameWnd();
  ((UIWnd *)(UIWnd *)this + 4072)->ctor_D880();
  ((UIWnd *)this)->~UIWnd();
}

// 0x0047BBF0
int UIWnd::ctor_BBF0(int _this)
{
  ((UIListBox *)this)->UIListBox();
  ((UIFrameWnd *)(this + 128))->UIFrameWnd();
  ((UIFrameWnd *)(this + 280))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 432),
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIScene *)(this + 888))->_UIScene();
  ((UIScene *)(this + 1232))->_UIScene();
  ((UIScene *)(this + 1576))->_UIScene();
  sub_44B850(this + 1920);
  *(_DWORD *)this = &off_56B850;
  *(_DWORD *)(this + 88) = 88;
  *(_DWORD *)(this + 92) = 138;
  *(_DWORD *)(this + 104) = 90;
  *(_DWORD *)(this + 108) = 26;
  *(_DWORD *)(this + 96) = 800;
  *(_DWORD *)(this + 100) = 64;
  *(_DWORD *)(this + 124) = 0;
  *(_DWORD *)(this + 3988) = 0;
  *(_BYTE *)(this + 4000) = 1;
  return this;
}

// 0x0047BD20
void UIWnd::ctor_BD20()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B850;
  sub_47BDF0((int)this);
  sub_44B890((int)this + 1920);
  ((UIWnd *)((char *)this + 1576))->Destroy2();
  ((UIWnd *)((char *)this + 1232))->Destroy2();
  ((UIWnd *)((char *)this + 888))->Destroy2();
  `eh vector destructor iterator'((char *)this + 432, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(UIWnd *)this + 7)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 128))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x0047E5C0
int UIWnd::ctor_E5C0(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  *(_BYTE *)(this + 361) = 0;
  *(_DWORD *)(this + 364) = 0;
  ((UIFrameWnd *)(this + 368))->UIFrameWnd();
  ((UIFrameWnd *)(this + 520))->UIFrameWnd();
  ((UIFrameWnd *)(this + 672))->UIFrameWnd();
  ((UIFrameWnd *)(this + 824))->UIFrameWnd();
  ((UIFrameWnd *)(this + 976))->UIFrameWnd();
  ((UIScene *)(this + 1128))->_UIScene();
  ((UIScene *)(this + 1472))->_UIScene();
  ((UIScene *)(this + 1816))->_UIScene();
  ((UIScene *)(this + 2160))->_UIScene();
  ((UIScene *)(this + 2504))->_UIScene();
  ((UIScene *)(this + 2848))->_UIScene();
  ((UIScene *)(this + 3192))->_UIScene();
  ((UIScene *)(this + 3536))->_UIScene();
  ((UIScene *)(this + 3880))->_UIScene();
  ((UIFrameWnd *)(this + 4224))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4392))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4544))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 4696),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 79448),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  ((UIWnd *)(this + 154340))->ctor_9030();
  ((UIWnd *)(this + 154648))->ctor_9030();
  ((UIFrameWnd *)(this + 154956))->UIFrameWnd();
  ((UIFrameWnd *)(this + 155108))->UIFrameWnd();
  ((UIFrameWnd *)(this + 155260))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 155412),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 156172),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 156932),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 157604))->UIFrameWnd();
  ((UIFrameWnd *)(this + 157756))->UIFrameWnd();
  ((UIScene *)(this + 157908))->_UIScene();
  ((UIScene *)(this + 158252))->_UIScene();
  ((UIStatic *)(this + 158596))->UIStatic();
  ((UIStatic *)(this + 158844))->UIStatic();
  ((UIStatic *)(this + 159092))->UIStatic();
  ((UIStatic *)(this + 159340))->UIStatic();
  ((UIStatic *)(this + 159588))->UIStatic();
  ((UIStatic *)(this + 159836))->UIStatic();
  *(_DWORD *)this = &off_56B90C;
  *(_DWORD *)(this + 154328) = 0;
  *(_DWORD *)(this + 154332) = 0;
  *(_DWORD *)(this + 154336) = 0;
  sub_47EC00(this);
  return this;
}

// 0x0047E910
void UIWnd::ctor_E910()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56B90C;
  sub_47F410((int)this);
  ((UIWnd *)((char *)this + 159836))->~UIWnd();
  ((UIWnd *)((char *)this + 159588))->~UIWnd();
  ((UIWnd *)((char *)this + 159340))->~UIWnd();
  ((UIWnd *)((char *)this + 159092))->~UIWnd();
  ((UIWnd *)((char *)this + 158844))->~UIWnd();
  ((UIWnd *)((char *)this + 158596))->~UIWnd();
  ((UIWnd *)((char *)this + 158252))->Destroy2();
  ((UIWnd *)((char *)this + 157908))->Destroy2();
  ((UIWnd *)((char *)this + 157756))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 157604))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 156932, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 156172, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 155412, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 155260))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 155108))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 154956))->_UIFrameWnd();
  ((UIWnd *)(this + 1487))->ctor_9130();
  ((UIWnd *)((char *)this + 154340))->ctor_9130();
  `eh vector destructor iterator'((char *)this + 79448, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4696, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 4544))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4392))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4224))->_UIFrameWnd();
  ((UIScene *)(UIWnd *)this + 97)->Destroy2();
  ((UIWnd *)(this + 34))->Destroy2();
  ((UIWnd *)((char *)this + 3192))->Destroy2();
  ((UIWnd *)((char *)this + 2848))->Destroy2();
  ((UIWnd *)((char *)this + 2504))->Destroy2();
  ((UIScene *)(UIWnd *)this + 54)->Destroy2();
  ((UIWnd *)((char *)this + 1816))->Destroy2();
  ((UIWnd *)((char *)this + 1472))->Destroy2();
  ((UIWnd *)((char *)this + 1128))->Destroy2();
  ((UIWnd *)((char *)this + 976))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 824))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 672))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 13)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 368))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00482ED0
int UIWnd::ctor_2ED0(int _this)
{
  int v2; // edi
  int v4; // [esp+10h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  ((UIFrameWnd *)(this + 368))->UIFrameWnd();
  ((UIFrameWnd *)(this + 520))->UIFrameWnd();
  ((UIFrameWnd *)(this + 672))->UIFrameWnd();
  ((UIFrameWnd *)(this + 824))->UIFrameWnd();
  ((UIFrameWnd *)(this + 976))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1128))->UIFrameWnd();
  ((UIScene *)(this + 1280))->_UIScene();
  ((UIScene *)(this + 1624))->_UIScene();
  ((UIScene *)(this + 1968))->_UIScene();
  ((UIScene *)(this + 2312))->_UIScene();
  ((UIScene *)(this + 2656))->_UIScene();
  ((UIScene *)(this + 3000))->_UIScene();
  ((UIScene *)(this + 3344))->_UIScene();
  ((UIScene *)(this + 3688))->_UIScene();
  ((UIScene *)(this + 4032))->_UIScene();
  ((UIFrameWnd *)(this + 4376))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4544))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4696))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4848))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 5000),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 79752),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  memset((void *)(this + 154644), 0, 0x1Cu);
  *(_WORD *)(this + 154672) = 0;
  *(_DWORD *)(this + 154674) = 117901063;
  *(_BYTE *)(this + 154678) = 7;
  ((UIFrameWnd *)(this + 154696))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 154848),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)(this + 156588),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 157348),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)(this + 158188) = 0;
  ((UIItem *)(this + 158192))->Refresh();
  v2 = this + 159592;
  v4 = 6;
  do
  {
    ((void (*)(int))gbVec3D::`default constructor closure')(v2);
    v2 += 12;
    --v4;
  }
  while ( v4 );
  ((ObjectCamera *)(this + 159664))->Update();
  `eh vector constructor iterator'(
    (char *)(this + 159816),
    0x98u,
    5,
    (void (*)(void *))ObjectCamera::Update,
    (void (*)(void *))Object3D::Object3D);
  `eh vector constructor iterator'(
    (char *)(this + 160608),
    0x98u,
    6,
    (void (*)(void *))ObjectCamera::Update,
    (void (*)(void *))Object3D::Object3D);
  `eh vector constructor iterator'(
    (char *)(this + 161520),
    0x798u,
    5,
    (void (*)(void *))sub_483280,
    (void (*)(void *))sub_483300);
  *(_DWORD *)(this + 171240) = 0;
  *(_DWORD *)this = &off_56BA30;
  *(_BYTE *)(this + 365) = 0;
  *(_BYTE *)(this + 364) = 0;
  *(_BYTE *)(this + 362) = 0;
  *(_BYTE *)(this + 361) = 0;
  *(_BYTE *)(this + 363) = 0;
  memset((void *)(this + 154644), 0, 0x1Cu);
  *(_WORD *)(this + 154672) = 0;
  *(_DWORD *)(this + 154674) = 0;
  *(_BYTE *)(this + 154678) = 0;
  *(_DWORD *)(this + 154632) = 0;
  *(_DWORD *)(this + 154636) = 0;
  *(_DWORD *)(this + 154640) = 0;
  *(_DWORD *)(this + 159560) = -1038614528;
  *(_DWORD *)(this + 159564) = 1072064102;
  *(_DWORD *)(this + 159572) = 1094713344;
  *(_DWORD *)(this + 159568) = 0;
  return this;
}

// 0x00483380
void UIWnd::ctor_3380()
{
  ObjectCamera **v2; // ecx
  void *v3; // edi

  this->m_fontcolor.ColorQuadFmt = (int)&off_56BA30;
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
  ((Object3D *)((char *)this + 159664))->Object3D();
  ((UIItem *)(UIItem *)this + 158192)->UIItem();
  `eh vector destructor iterator'((char *)this + 157348, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 156588, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 154848, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIWnd *)((char *)this + 154696))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 79752, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 5000, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 4848))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4696))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4544))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4376))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4032))->Destroy2();
  ((UIWnd *)((char *)this + 3688))->Destroy2();
  ((UIWnd *)((char *)this + 3344))->Destroy2();
  ((UIScene *)(UIWnd *)this + 75)->Destroy2();
  ((UIWnd *)((char *)this + 2656))->Destroy2();
  ((UIWnd *)((char *)this + 2312))->Destroy2();
  ((UIWnd *)((char *)this + 1968))->Destroy2();
  ((UIWnd *)((char *)this + 1624))->Destroy2();
  ((UIScene *)(UIWnd *)this + 32)->Destroy2();
  ((UIWnd *)((char *)this + 1128))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 976))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 824))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 672))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 13)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 368))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x004867F0
int UIWnd::ctor_67F0(int _this)
{
  int v2; // edi
  int v3; // ebp

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 872) = 0;
  *(_BYTE *)(this + 876) = 0;
  *(_BYTE *)(this + 889) = 0;
  *(_DWORD *)(this + 892) = 0;
  *(_DWORD *)(this + 896) = 0;
  *(_DWORD *)(this + 900) = 0;
  *(_DWORD *)(this + 904) = -1;
  *(_BYTE *)(this + 908) = 0;
  *(_BYTE *)(this + 910) = 0;
  *(_BYTE *)(this + 911) = 0;
  *(_BYTE *)(this + 912) = 0;
  *(_DWORD *)(this + 916) = 0;
  *(_DWORD *)(this + 3320) = 0;
  *(_BYTE *)(this + 3336) = 0;
  *(_BYTE *)(this + 3337) = 0;
  *(_BYTE *)(this + 3348) = 0;
  *(_DWORD *)(this + 3344) = 0;
  *(_DWORD *)(this + 3340) = 0;
  v2 = this + 3356;
  v3 = 40;
  do
  {
    ArraySort(v2, 12, 99, (int)sub_486CE0);
    v2 += 1192;
    --v3;
  }
  while ( v3 );
  *(_DWORD *)(this + 51032) = 0;
  ((UIFrameWnd *)(this + 51036))->UIFrameWnd();
  ((UIFrameWnd *)(this + 51188))->UIFrameWnd();
  ((UIFrameWnd *)(this + 51340))->UIFrameWnd();
  ((UIFrameWnd *)(this + 51492))->UIFrameWnd();
  ((UIFrameWnd *)(this + 51644))->UIFrameWnd();
  ((UIFrameWnd *)(this + 51796))->UIFrameWnd();
  ((UIScene *)(this + 51948))->_UIScene();
  ((UIScene *)(this + 52292))->_UIScene();
  ((UIScene *)(this + 52636))->_UIScene();
  ((UIScene *)(this + 52980))->_UIScene();
  ((UIScene *)(this + 53324))->_UIScene();
  ((UIScene *)(this + 53668))->_UIScene();
  ((UIScene *)(this + 54012))->_UIScene();
  ((UIScene *)(this + 54356))->_UIScene();
  ((UIScene *)(this + 54700))->_UIScene();
  ((UIFrameWnd *)(this + 55044))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 55228),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 55836))->UIFrameWnd();
  ((UIFrameWnd *)(this + 55988))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 56140),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 130892),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  *(_DWORD *)(this + 205784) = 0;
  ((UIItem *)(this + 205788))->Refresh();
  ((UIItem *)(this + 207156))->Refresh();
  ((UIItem *)(this + 208524))->Refresh();
  `eh vector constructor iterator'(
    (char *)(this + 209896),
    0x34u,
    5,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  ((UIWnd *)(this + 210236))->ctor_D830();
  ((UIFrameWnd *)(this + 210320))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 210472),
    0x98u,
    9,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 211840))->UIFrameWnd();
  ((UIFrameWnd *)(this + 211992))->UIFrameWnd();
  ((UIFrameWnd *)(this + 212144))->UIFrameWnd();
  ((UIFrameWnd *)(this + 212296))->UIFrameWnd();
  ((UIFrameWnd *)(this + 212448))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 212600),
    0x131Cu,
    5,
    (void (*)(void *))sub_486D20,
    (void (*)(void *))sub_486EF0);
  `eh vector constructor iterator'(
    (char *)(this + 237060),
    0x158u,
    8,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIListBox *)(this + 239812))->UpdateKeyCtrl();
  ((UIListBox *)(this + 241020))->UpdateKeyCtrl();
  ((UIListBox *)(this + 242228))->UpdateKeyCtrl();
  ((UIListBox *)(this + 243436))->UpdateKeyCtrl();
  ((UIListBox *)(this + 244644))->UpdateKeyCtrl();
  ((UIListBox *)(this + 245852))->UpdateKeyCtrl();
  ((UIListBox *)(this + 247060))->UpdateKeyCtrl();
  ((UIListBox *)(this + 248268))->UpdateKeyCtrl();
  ((UIWnd *)(this + 249476))->ctor_9030();
  `eh vector constructor iterator'(
    (char *)(this + 249784),
    0x248u,
    98,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 307040),
    0x248u,
    40,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 330400),
    0x248u,
    40,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  *(_DWORD *)this = &off_56C590;
  *(_BYTE *)(this + 881) = 0;
  *(_BYTE *)(this + 880) = 0;
  *(_BYTE *)(this + 878) = 0;
  *(_BYTE *)(this + 877) = 0;
  *(_BYTE *)(this + 879) = 0;
  *(_DWORD *)(this + 3332) = 0;
  *(_DWORD *)(this + 3328) = 0;
  *(_DWORD *)(this + 3324) = 0;
  *(_DWORD *)(this + 307032) = 0;
  *(_DWORD *)(this + 307036) = 0;
  *(_DWORD *)(this + 205772) = 0;
  *(_DWORD *)(this + 205776) = 0;
  *(_DWORD *)(this + 205780) = 0;
  return this;
}

// 0x004870C0
void UIWnd::ctor_70C0()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56C590;
  `eh vector destructor iterator'((char *)this + 330400, 0x248u, 40, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 307040, 0x248u, 40, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 249784, 0x248u, 98, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 249476))->ctor_9130();
  ((UIWnd *)((char *)this + 248268))->DeleteRow();
  ((UIWnd *)((char *)this + 247060))->DeleteRow();
  ((UIWnd *)((char *)this + 245852))->DeleteRow();
  ((UIWnd *)((char *)this + 244644))->DeleteRow();
  ((UIWnd *)((char *)this + 243436))->DeleteRow();
  ((UIWnd *)((char *)this + 242228))->DeleteRow();
  ((UIWnd *)((char *)this + 241020))->DeleteRow();
  ((UIWnd *)((char *)this + 239812))->DeleteRow();
  `eh vector destructor iterator'((char *)this + 237060, 0x158u, 8, (void (*)(void *))UIScene::Destroy2);
  `eh vector destructor iterator'((char *)this + 212600, 0x131Cu, 5, (void (*)(void *))sub_486EF0);
  ((UIWnd *)((char *)this + 212448))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 212296))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 212144))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 211992))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 5296)->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 210472, 0x98u, 9, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(UIWnd *)this + 5258)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 210236))->ctor_D880();
  `eh vector destructor iterator'((char *)this + 209896, 0x34u, 5, (void (*)(void *))nullsub_1);
  ((UIItem *)(UIItem *)this + 208524)->UIItem();
  ((UIItem *)(UIItem *)this + 207156)->UIItem();
  ((UIItem *)(UIItem *)this + 205788)->UIItem();
  `eh vector destructor iterator'((char *)this + 130892, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 56140, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 55988))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 55836))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 55228, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 55044))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 54700))->Destroy2();
  ((UIWnd *)((char *)this + 54356))->Destroy2();
  ((UIWnd *)((char *)this + 54012))->Destroy2();
  ((UIWnd *)((char *)this + 53668))->Destroy2();
  ((UIWnd *)((char *)this + 53324))->Destroy2();
  ((UIWnd *)((char *)this + 52980))->Destroy2();
  ((UIWnd *)((char *)this + 52636))->Destroy2();
  ((UIWnd *)((char *)this + 52292))->Destroy2();
  ((UIWnd *)((char *)this + 51948))->Destroy2();
  ((UIWnd *)((char *)this + 51796))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 51644))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 51492))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 51340))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 51188))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 51036))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x004909F0
int UIWnd::ctor_9F0(int _this)
{
  _DWORD *v2; // eax
  int v3; // ebp
  _DWORD *v5; // [esp+10h] [ebp-18h]
  int v6; // [esp+14h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  *(_BYTE *)(this + 367) = 0;
  *(_DWORD *)(this + 368) = 0;
  *(_DWORD *)(this + 372) = 0;
  *(_DWORD *)(this + 376) = 7;
  *(_DWORD *)(this + 380) = 0;
  ((UIFrameWnd *)(this + 384))->UIFrameWnd();
  ((UIFrameWnd *)(this + 536))->UIFrameWnd();
  ((UIFrameWnd *)(this + 688))->UIFrameWnd();
  ((UIFrameWnd *)(this + 840))->UIFrameWnd();
  ((UIFrameWnd *)(this + 992))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1144))->UIFrameWnd();
  ((UIScene *)(this + 1296))->_UIScene();
  ((UIScene *)(this + 1640))->_UIScene();
  ((UIScene *)(this + 1984))->_UIScene();
  ((UIScene *)(this + 2328))->_UIScene();
  ((UIScene *)(this + 2672))->_UIScene();
  ((UIScene *)(this + 3016))->_UIScene();
  ((UIScene *)(this + 3360))->_UIScene();
  ((UIScene *)(this + 3704))->_UIScene();
  ((UIScene *)(this + 4048))->_UIScene();
  ((UIFrameWnd *)(this + 4392))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4560))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4712))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 4864),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 79616),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 154508),
    0x26FCu,
    5,
    (void (*)(void *))sub_490E90,
    (void (*)(void *))sub_4910B0);
  ((UIFrameWnd *)(this + 204424))->UIFrameWnd();
  ((UIFrameWnd *)(this + 204576))->UIFrameWnd();
  ((UIFrameWnd *)(this + 204728))->UIFrameWnd();
  ((UIFrameWnd *)(this + 204880))->UIFrameWnd();
  ((UIFrameWnd *)(this + 205032))->UIFrameWnd();
  v2 = (_DWORD *)(this + 205200);
  v5 = (_DWORD *)(this + 205200);
  v6 = 5;
  v3 = this + 205206;
  while ( 1 )
  {
    *v2 = 0;
    *(_WORD *)(v3 - 2) = 0;
    lstrcpyA((LPSTR)v3, (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    lstrcpyA((LPSTR)(v3 + 512), (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    lstrcpyA((LPSTR)(v3 + 542), (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    lstrcpyA((LPSTR)(v3 + 594), (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    memset((void *)(v3 + 630), 0, 0x30u);
    *(_DWORD *)(v3 + 774) = 0;
    v3 += 852;
    v5 += 213;
    if ( !--v6 )
      break;
    v2 = v5;
  }
  ((UIItem *)(this + 209460))->Refresh();
  `eh vector constructor iterator'(
    (char *)(this + 210828),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)(this + 212548))->UIFrameWnd();
  ((UIFrameWnd *)(this + 212700))->UIFrameWnd();
  ((UIFrameWnd *)(this + 212852))->UIFrameWnd();
  ((UIFrameWnd *)(this + 213004))->UIFrameWnd();
  ((UIFrameWnd *)(this + 213156))->UIFrameWnd();
  ((UIFrameWnd *)(this + 213308))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 213476),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  *(_DWORD *)(this + 215196) = -1;
  ((UIWnd *)(this + 215200))->ctor_D830();
  ((UIFrameWnd *)(this + 215284))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 215436),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 217260))->UIFrameWnd();
  ((UIListBox *)(this + 217412))->UpdateKeyCtrl();
  *(_DWORD *)(this + 218620) = -1;
  ((UIScene *)(this + 218640))->_UIScene();
  ((UIScene *)(this + 218984))->_UIScene();
  ((UIScene *)(this + 219328))->_UIScene();
  *(_DWORD *)(this + 219672) = -1;
  ((UIWnd *)(this + 219676))->ctor_9030();
  *(_DWORD *)this = &off_56D618;
  *(_BYTE *)(this + 365) = 0;
  *(_BYTE *)(this + 364) = 0;
  *(_BYTE *)(this + 362) = 0;
  *(_BYTE *)(this + 361) = 0;
  *(_BYTE *)(this + 363) = 0;
  *(_DWORD *)(this + 154496) = 0;
  *(_DWORD *)(this + 154500) = 0;
  *(_DWORD *)(this + 154504) = 0;
  return this;
}

// 0x004912D0
void UIWnd::ctor_12D0()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56D618;
  ((UIWnd *)((char *)this + 219676))->ctor_9130();
  ((UIWnd *)((char *)this + 219328))->Destroy2();
  ((UIWnd *)((char *)this + 218984))->Destroy2();
  ((UIScene *)(UIWnd *)this + 5466)->Destroy2();
  ((UIWnd *)((char *)this + 217412))->DeleteRow();
  ((UIWnd *)((char *)this + 217260))->_UIFrameWnd();
  `eh vector destructor iterator'(
    (char *)this + 215436,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 215284))->_UIFrameWnd();
  ((UIWnd *)(UIWnd *)this + 5380)->ctor_D880();
  `eh vector destructor iterator'((char *)this + 213476, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIWnd *)((char *)this + 213308))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 213156))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 213004))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 212852))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 212700))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 212548))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 210828, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  ((UIItem *)(UIItem *)this + 209460)->UIItem();
  ((UIWnd *)((char *)this + 205032))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 5122)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 204728))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 204576))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 204424))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 154508, 0x26FCu, 5, (void (*)(void *))sub_4910B0);
  `eh vector destructor iterator'((char *)this + 79616, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4864, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 4712))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 114)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4392))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4048))->Destroy2();
  ((UIWnd *)((char *)this + 3704))->Destroy2();
  ((UIScene *)(UIWnd *)this + 84)->Destroy2();
  ((UIWnd *)(this + 29))->Destroy2();
  ((UIWnd *)((char *)this + 2672))->Destroy2();
  ((UIWnd *)((char *)this + 2328))->Destroy2();
  ((UIWnd *)((char *)this + 1984))->Destroy2();
  ((UIScene *)(UIWnd *)this + 41)->Destroy2();
  ((UIWnd *)((char *)this + 1296))->Destroy2();
  ((UIWnd *)(this + 11))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 992))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 21)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 688))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 536))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 384))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00498820
int UIWnd::ctor_8820(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 104) = 0;
  *(_BYTE *)(this + 620) = 0;
  *(_DWORD *)(this + 628) = 0;
  *(_BYTE *)(this + 633) = 0;
  *(_DWORD *)(this + 636) = 0;
  *(_DWORD *)(this + 640) = 0;
  *(_DWORD *)(this + 644) = 0;
  *(_DWORD *)(this + 648) = 0;
  *(_BYTE *)(this + 653) = 0;
  *(_BYTE *)(this + 654) = 0;
  *(_BYTE *)(this + 655) = 0;
  *(_DWORD *)(this + 656) = 0;
  ((UIFrameWnd *)(this + 660))->UIFrameWnd();
  ((UIFrameWnd *)(this + 812))->UIFrameWnd();
  ((UIFrameWnd *)(this + 964))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1116))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1268))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1420))->UIFrameWnd();
  ((UIScene *)(this + 1572))->_UIScene();
  ((UIScene *)(this + 1916))->_UIScene();
  ((UIScene *)(this + 2260))->_UIScene();
  ((UIScene *)(this + 2604))->_UIScene();
  ((UIScene *)(this + 2948))->_UIScene();
  ((UIScene *)(this + 3292))->_UIScene();
  ((UIScene *)(this + 3636))->_UIScene();
  ((UIScene *)(this + 3980))->_UIScene();
  ((UIScene *)(this + 4324))->_UIScene();
  ((UIFrameWnd *)(this + 4668))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4836))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4988))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 5140),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 79892),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  ((UIItem *)(this + 154784))->Refresh();
  `eh vector constructor iterator'(
    (char *)(this + 156152),
    0x131Cu,
    5,
    (void (*)(void *))sub_498C90,
    (void (*)(void *))sub_498E60);
  ((UIFrameWnd *)(this + 180612))->UIFrameWnd();
  ((UIFrameWnd *)(this + 180764))->UIFrameWnd();
  ((UIFrameWnd *)(this + 180916))->UIFrameWnd();
  ((UIFrameWnd *)(this + 181084))->UIFrameWnd();
  ((UIFrameWnd *)(this + 181236))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 181388),
    0x158u,
    6,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)(this + 183452),
    0xF8u,
    6,
    (void (*)(void *))UIStatic::UIStatic,
    (void (*)(void *))UIWnd::~UIWnd);
  ((UIFrameWnd *)(this + 184940))->UIFrameWnd();
  ((UIWnd *)(this + 185092))->ctor_D830();
  ((UIFrameWnd *)(this + 185176))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 185328),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)(this + 187152))->UpdateKeyCtrl();
  ((UIListBox *)(this + 188360))->UpdateKeyCtrl();
  ((UIListBox *)(this + 189568))->UpdateKeyCtrl();
  ((UIListBox *)(this + 190776))->UpdateKeyCtrl();
  ((UIListBox *)(this + 191984))->UpdateKeyCtrl();
  ((UIListBox *)(this + 193192))->UpdateKeyCtrl();
  `eh vector constructor iterator'(
    (char *)(this + 194400),
    0x34u,
    5,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  ((UIScene *)(this + 194756))->_UIScene();
  ((UIScene *)(this + 195100))->_UIScene();
  ((UIScene *)(this + 195444))->_UIScene();
  *(_DWORD *)(this + 195788) = -1;
  ((UIWnd *)(this + 195792))->ctor_9030();
  `eh vector constructor iterator'(
    (char *)(this + 196100),
    0x248u,
    60,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 231140),
    0x248u,
    60,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  *(_DWORD *)this = &off_56E170;
  *(_BYTE *)(this + 625) = 0;
  *(_BYTE *)(this + 624) = 0;
  *(_BYTE *)(this + 622) = 0;
  *(_BYTE *)(this + 621) = 0;
  *(_BYTE *)(this + 623) = 0;
  *(_DWORD *)(this + 154772) = 0;
  *(_DWORD *)(this + 154776) = 0;
  *(_DWORD *)(this + 154780) = 0;
  return this;
}

// 0x00499030
void UIWnd::ctor_9030_0()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56E170;
  `eh vector destructor iterator'((char *)this + 231140, 0x248u, 60, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 196100, 0x248u, 60, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 195792))->ctor_9130();
  ((UIWnd *)((char *)this + 195444))->Destroy2();
  ((UIWnd *)((char *)this + 195100))->Destroy2();
  ((UIWnd *)((char *)this + 194756))->Destroy2();
  `eh vector destructor iterator'((char *)this + 194400, 0x34u, 5, (void (*)(void *))nullsub_1);
  ((UIWnd *)((char *)this + 193192))->DeleteRow();
  ((UIWnd *)(this + 1846))->DeleteRow();
  ((UIWnd *)((char *)this + 190776))->DeleteRow();
  ((UIWnd *)((char *)this + 189568))->DeleteRow();
  ((UIListBox *)(UIWnd *)this + 4709)->DeleteRow();
  ((UIWnd *)((char *)this + 187152))->DeleteRow();
  `eh vector destructor iterator'(
    (char *)this + 185328,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 185176))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 185092))->ctor_D880();
  ((UIWnd *)((char *)this + 184940))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 183452, 0xF8u, 6, (void (*)(void *))UIWnd::~UIWnd);
  `eh vector destructor iterator'((char *)this + 181388, 0x158u, 6, (void (*)(void *))UIScene::Destroy2);
  ((UIWnd *)((char *)this + 181236))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 181084))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 180916))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 180764))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 180612))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 156152, 0x131Cu, 5, (void (*)(void *))sub_498E60);
  ((UIItem *)(UIItem *)this + 154784)->UIItem();
  `eh vector destructor iterator'((char *)this + 79892, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 5140, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 4988))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4836))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4668))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4324))->Destroy2();
  ((UIWnd *)((char *)this + 3980))->Destroy2();
  ((UIWnd *)((char *)this + 3636))->Destroy2();
  ((UIWnd *)((char *)this + 3292))->Destroy2();
  ((UIWnd *)((char *)this + 2948))->Destroy2();
  ((UIWnd *)((char *)this + 2604))->Destroy2();
  ((UIWnd *)((char *)this + 2260))->Destroy2();
  ((UIWnd *)((char *)this + 1916))->Destroy2();
  ((UIWnd *)((char *)this + 1572))->Destroy2();
  ((UIWnd *)((char *)this + 1420))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1268))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1116))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 964))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 812))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 660))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x004A2450
void UIWnd::ctor_2450()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56F040;
  sub_4A6600((int)this);
  ((UIWnd *)((char *)this + 176092))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 175696))->Destroy2();
  `eh vector destructor iterator'((char *)this + 174856, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 174688))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 174080, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 155140, 0xECCu, 5, (void (*)(void *))sub_4A22E0);
  ((UIWnd *)((char *)this + 154972))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 154820))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 154668))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 154516))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 79608, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4856, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 4704))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4552))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4384))->_UIFrameWnd();
  ((UIScene *)(UIWnd *)this + 101)->Destroy2();
  ((UIWnd *)((char *)this + 3696))->Destroy2();
  ((UIWnd *)((char *)this + 3352))->Destroy2();
  ((UIWnd *)((char *)this + 3008))->Destroy2();
  ((UIWnd *)((char *)this + 2664))->Destroy2();
  ((UIScene *)(UIWnd *)this + 58)->Destroy2();
  ((UIWnd *)(this + 19))->Destroy2();
  ((UIWnd *)((char *)this + 1632))->Destroy2();
  ((UIWnd *)((char *)this + 1288))->Destroy2();
  ((UIWnd *)((char *)this + 1136))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 984))->_UIFrameWnd();
  ((UIWnd *)(this + 8))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 17)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 528))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 376))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x004A6F10
int UIWnd::ctor_6F10(int _this)
{
  _DWORD *v2; // eax
  CHAR *v3; // ebp
  bool v4; // zf
  _DWORD *v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 100) = 0;
  ((UIFrameWnd *)(this + 364))->UIFrameWnd();
  v2 = (_DWORD *)(this + 548);
  v6 = (_DWORD *)(this + 548);
  v7 = 28;
  v3 = (CHAR *)(this + 608);
  while ( 1 )
  {
    *v2 = 0;
    lstrcpyA(v3 - 32, (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    lstrcpyA(v3, (LPCSTR)&g_SceneMgr.m_npc[5].m_path.normal[140].y);
    memset(v3 + 532, 0, 0x18u);
    v3 += 760;
    v4 = v7 == 1;
    v6 += 190;
    --v7;
    if ( v4 )
      break;
    v2 = v6;
  }
  *(_BYTE *)(this + 21841) = 0;
  *(_BYTE *)(this + 21842) = 1;
  *(_BYTE *)(this + 21843) = 1;
  *(_DWORD *)(this + 21844) = 0;
  *(_DWORD *)(this + 21848) = 0;
  *(_DWORD *)(this + 21852) = 1127481344;
  *(_DWORD *)(this + 23444) = 300;
  *(_DWORD *)(this + 23448) = 0;
  *(_DWORD *)(this + 23452) = 0;
  ((UIFrameWnd *)(this + 23456))->UIFrameWnd();
  ((UIFrameWnd *)(this + 23608))->UIFrameWnd();
  ((UIFrameWnd *)(this + 23760))->UIFrameWnd();
  ((UIFrameWnd *)(this + 23912))->UIFrameWnd();
  ((UIFrameWnd *)(this + 24064))->UIFrameWnd();
  ((UIScene *)(this + 24216))->_UIScene();
  ((UIScene *)(this + 24560))->_UIScene();
  ((UIScene *)(this + 24904))->_UIScene();
  ((UIScene *)(this + 25248))->_UIScene();
  ((UIScene *)(this + 25592))->_UIScene();
  ((UIScene *)(this + 25936))->_UIScene();
  ((UIScene *)(this + 26280))->_UIScene();
  ((UIScene *)(this + 26624))->_UIScene();
  ((UIScene *)(this + 26968))->_UIScene();
  ((UIFrameWnd *)(this + 27312))->UIFrameWnd();
  ((UIFrameWnd *)(this + 27480))->UIFrameWnd();
  ((UIFrameWnd *)(this + 27632))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 27784),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 102536),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  ((UIFrameWnd *)(this + 177428))->UIFrameWnd();
  ((UIFrameWnd *)(this + 177580))->UIFrameWnd();
  ((UIFrameWnd *)(this + 177732))->UIFrameWnd();
  ((UIFrameWnd *)(this + 177884))->UIFrameWnd();
  ((UIWnd *)(this + 178036))->ctor_9030();
  ((UIWnd *)(this + 178344))->ctor_9030();
  ((UIFrameWnd *)(this + 178652))->UIFrameWnd();
  ((UIFrameWnd *)(this + 178804))->UIFrameWnd();
  ((UIFrameWnd *)(this + 178956))->UIFrameWnd();
  ((UIScene *)(this + 179108))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 179508),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)(this + 181228),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 181988),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (char *)(this + 183708),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 184468),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_BYTE *)(this + 185228) = 1;
  ((UIScene *)(this + 185232))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 185576),
    0x248u,
    168,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 283704),
    0x248u,
    168,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  ((UIScene *)(this + 381816))->_UIScene();
  ((UIScene *)(this + 382160))->_UIScene();
  sub_4A6730((char *)(this + 382744));
  *(_BYTE *)(this + 383180) = 0;
  *(_DWORD *)(this + 383176) = 0;
  *(_DWORD *)(this + 383172) = 0;
  *(_BYTE *)(this + 383200) = 0;
  *(_DWORD *)(this + 383196) = 0;
  *(_DWORD *)(this + 383192) = 0;
  ((UIWnd *)(this + 383300))->ctor_D830();
  ((UIWnd *)(this + 383384))->ctor_D830();
  `eh vector constructor iterator'(
    (char *)(this + 383468),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIFrameWnd *)(this + 385188))->UIFrameWnd();
  ((UIFrameWnd *)(this + 385340))->UIFrameWnd();
  ((UIWnd *)(this + 385492))->ctor_D830();
  ((UIFrameWnd *)(this + 385576))->UIFrameWnd();
  ((UIFrameWnd *)(this + 385728))->UIFrameWnd();
  ((UIFrameWnd *)(this + 385880))->UIFrameWnd();
  ((UIFrameWnd *)(this + 386032))->UIFrameWnd();
  ((UIFrameWnd *)(this + 386184))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 386336),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 388160),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIListBox *)(this + 389984))->UpdateKeyCtrl();
  ((UIListBox *)(this + 391192))->UpdateKeyCtrl();
  ((UIListBox *)(this + 392400))->UpdateKeyCtrl();
  ((UIListBox *)(this + 393608))->UpdateKeyCtrl();
  ((UIListBox *)(this + 394816))->UpdateKeyCtrl();
  ((UIListBox *)(this + 396024))->UpdateKeyCtrl();
  ((UIFrameWnd *)(this + 397248))->UIFrameWnd();
  ((UIFrameWnd *)(this + 397400))->UIFrameWnd();
  ((UIFrameWnd *)(this + 397552))->UIFrameWnd();
  ((UIFrameWnd *)(this + 397720))->UIFrameWnd();
  ((UIWnd *)(this + 397872))->ctor_D830();
  ((UIScene *)(this + 397972))->_UIScene();
  ((UIScene *)(this + 398316))->_UIScene();
  ((UIScene *)(this + 398660))->_UIScene();
  ((UIScene *)(this + 399004))->_UIScene();
  ((UIScene *)(this + 399348))->_UIScene();
  ((UIScene *)(this + 399692))->_UIScene();
  *(_DWORD *)(this + 400036) = 0;
  sub_40CC60(this + 400040);
  ((UIItem *)(this + 400080))->Refresh();
  ((UIItem *)(this + 401448))->Refresh();
  *(_DWORD *)this = &off_56F29C;
  dword_DE5FA0 = 0;
  unk_DE5FA4 = 0;
  dword_DE5F98 = 0;
  word_DE5FA8 = 0;
  LOBYTE(dword_DE5F9C) = 0;
  *(_DWORD *)(this + 177416) = 0;
  *(_DWORD *)(this + 177420) = 0;
  *(_DWORD *)(this + 177424) = 0;
  *(_BYTE *)(this + 383184) = 1;
  *(_BYTE *)(this + 383185) = 0;
  *(_BYTE *)(this + 383186) = 1;
  *(_BYTE *)(this + 383187) = 1;
  *(_DWORD *)(this + 383188) = 0;
  *(_DWORD *)(this + 383208) = 100;
  *(_DWORD *)(this + 383204) = 1000;
  *(_DWORD *)(this + 21828) = 0;
  *(_DWORD *)(this + 520) = 0;
  *(_DWORD *)(this + 516) = 0;
  *(_DWORD *)(this + 536) = 0;
  *(_DWORD *)(this + 532) = 0;
  *(_DWORD *)(this + 528) = 0;
  *(_DWORD *)(this + 524) = 0;
  *(_DWORD *)(this + 544) = 0;
  *(_DWORD *)(this + 540) = 0;
  return this;
}

// 0x004B01D0
int UIWnd::ctor_1D0(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  *(_DWORD *)(this + 364) = 0;
  ((UIFrameWnd *)(this + 368))->UIFrameWnd();
  ((UIFrameWnd *)(this + 520))->UIFrameWnd();
  ((UIFrameWnd *)(this + 672))->UIFrameWnd();
  ((UIFrameWnd *)(this + 824))->UIFrameWnd();
  ((UIFrameWnd *)(this + 976))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1128))->UIFrameWnd();
  ((UIScene *)(this + 1280))->_UIScene();
  ((UIScene *)(this + 1624))->_UIScene();
  ((UIScene *)(this + 1968))->_UIScene();
  ((UIScene *)(this + 2312))->_UIScene();
  ((UIScene *)(this + 2656))->_UIScene();
  ((UIScene *)(this + 3000))->_UIScene();
  ((UIScene *)(this + 3344))->_UIScene();
  ((UIScene *)(this + 3688))->_UIScene();
  ((UIScene *)(this + 4032))->_UIScene();
  ((UIFrameWnd *)(this + 4376))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4544))->UIFrameWnd();
  ((UIFrameWnd *)(this + 4696))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 4848),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 79600),
    0x248u,
    128,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  ((UIFrameWnd *)(this + 154492))->UIFrameWnd();
  ((UIFrameWnd *)(this + 154644))->UIFrameWnd();
  ((UIStatic *)(this + 154796))->UIStatic();
  ((UIStatic *)(this + 155044))->UIStatic();
  ((UIScene *)(this + 155292))->_UIScene();
  ((UIScene *)(this + 155636))->_UIScene();
  ((UIScene *)(this + 155980))->_UIScene();
  `eh vector constructor iterator'(
    (char *)(this + 156360),
    0xDE8u,
    36,
    (void (*)(void *))sub_4549A0,
    (void (*)(void *))sub_454AA0);
  ((UIScene *)(this + 284520))->_UIScene();
  ((UIScene *)(this + 284864))->_UIScene();
  ((UIWnd *)(this + 285224))->ctor_BCE0();
  ((UIWnd *)(this + 285504))->ctor_BCE0();
  ((UIWnd *)(this + 285776))->ctor_BCE0();
  ((UIFrameWnd *)(this + 286048))->UIFrameWnd();
  ((UIFrameWnd *)(this + 286200))->UIFrameWnd();
  *(_DWORD *)(this + 286352) = 92;
  *(_DWORD *)(this + 286356) = 610;
  *(_DWORD *)(this + 286360) = 0;
  *(_DWORD *)(this + 286364) = 0;
  *(_DWORD *)(this + 286368) = 0;
  *(_DWORD *)(this + 286372) = 0;
  ((UIItem *)(this + 286384))->Refresh();
  ((UIItem *)(this + 287752))->Refresh();
  ((UIItem *)(this + 289120))->Refresh();
  *(_DWORD *)this = &off_56F33C;
  *(_DWORD *)(this + 154480) = 0;
  *(_DWORD *)(this + 154484) = 0;
  *(_DWORD *)(this + 154488) = 0;
  *(_DWORD *)(this + 286376) = 0;
  memset((void *)(this + 156324), 0, 0x24u);
  return this;
}

// 0x004B0540
void UIWnd::ctor_540()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56F33C;
  ((UIItem *)(UIItem *)this + 289120)->UIItem();
  ((UIItem *)(UIItem *)this + 287752)->UIItem();
  ((UIItem *)(UIItem *)this + 286384)->UIItem();
  ((UIFrameWnd *)(UIWnd *)this + 7155)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 286048))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 285776))->~UIWnd();
  ((UIWnd *)((char *)this + 285504))->~UIWnd();
  ((UIWnd *)((char *)this + 285224))->~UIWnd();
  ((UIWnd *)((char *)this + 284864))->Destroy2();
  ((UIScene *)(UIWnd *)this + 7113)->Destroy2();
  `eh vector destructor iterator'((char *)this + 156360, 0xDE8u, 36, (void (*)(void *))sub_454AA0);
  ((UIWnd *)((char *)this + 155980))->Destroy2();
  ((UIWnd *)((char *)this + 155636))->Destroy2();
  ((UIWnd *)((char *)this + 155292))->Destroy2();
  ((UIWnd *)((char *)this + 155044))->~UIWnd();
  ((UIWnd *)((char *)this + 154796))->~UIWnd();
  ((UIWnd *)((char *)this + 154644))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 154492))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 79600, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4848, 0x248u, 128, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 4696))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4544))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4376))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4032))->Destroy2();
  ((UIWnd *)((char *)this + 3688))->Destroy2();
  ((UIWnd *)((char *)this + 3344))->Destroy2();
  ((UIScene *)(UIWnd *)this + 75)->Destroy2();
  ((UIWnd *)((char *)this + 2656))->Destroy2();
  ((UIWnd *)((char *)this + 2312))->Destroy2();
  ((UIWnd *)((char *)this + 1968))->Destroy2();
  ((UIWnd *)((char *)this + 1624))->Destroy2();
  ((UIScene *)(UIWnd *)this + 32)->Destroy2();
  ((UIWnd *)((char *)this + 1128))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 976))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 824))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 672))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 13)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 368))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x004B7510
UIWnd::~UIWnd()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56F404;
  sub_4B7AF0((gbRefObject **)this);
  sub_4B6FB0((int)this);
}

// 0x004B7CE0
UIWnd::~UIWnd()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_56F450;
  sub_4B7F00((gbRefObject **)this);
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
  this->m_fontcolor.ColorQuadFmt = (int)&off_5704A8;
  sub_516170(this);
  *((_DWORD *)this + 290) = a2;
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x00516120
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_5704A8;
  sub_516170(this);
  this->~UIWnd();
}

// 0x00519310
_DWORD * UIWnd::ctor_9310()
{
  ((UIListBox *)this)->UIListBox();
  this->m_fontcolor.ColorQuadFmt = (int)&off_5704C8;
  ((CCBUI *)this)->OnMessage();
  return &this->m_fontcolor.ColorQuadFmt;
}

// 0x00519380
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_5704C8;
  ((CCBUI *)this)->OnMessage();
  this->~UIWnd();
}

// 0x00519B60
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_5704E4;
  ((CCBUI *)this)->Render();
  this->~UIWnd();
}

// 0x0051A3B0
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570500;
  sub_51A400(this);
  this->~UIWnd();
}

// 0x0051ACB0
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_57051C;
  ((CCBControlWindow *)this)->CheckKeyInput();
  this->~UIWnd();
}

// 0x0051B180
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570538;
  ((CCBItemWindow *)this)->Reset();
  this->~UIWnd();
}

// 0x0051B690
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570554;
  sub_51B6E0(this);
  this->~UIWnd();
}

// 0x0051BC00
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570570;
  ((CCBMagicWindow *)this)->OnMessage();
  this->~UIWnd();
}

// 0x0051C280
UIWnd::~UIWnd(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_57058C;
  ((CCBSkillWindow *)this)->Reset();
  this->~UIWnd();
}

// 0x00523F30
int UIWnd::ctor_3F30(int _this)
{
  _DWORD *v2; // ecx
  _DWORD *v3; // eax
  int v4; // edx
  _DWORD *v5; // ebp
  _DWORD *v6; // ebp
  _DWORD *v7; // ebp

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 100) = 0;
  ((UIFrameWnd *)(this + 360))->UIFrameWnd();
  ((UIFrameWnd *)(this + 512))->UIFrameWnd();
  ((UIFrameWnd *)(this + 664))->UIFrameWnd();
  ((UIFrameWnd *)(this + 816))->UIFrameWnd();
  ((UIFrameWnd *)(this + 968))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1120))->UIFrameWnd();
  ((UIWnd *)(this + 1272))->ctor_BCE0();
  ((UIScene *)(this + 1544))->_UIScene();
  ((UIScene *)(this + 1888))->_UIScene();
  *(_DWORD *)(this + 2232) = 0;
  sub_522030((_DWORD *)(this + 2236));
  *(_BYTE *)(this + 3868) = 0;
  *(_DWORD *)(this + 3872) = 0;
  ((UIItem *)(this + 3876))->Refresh();
  v2 = (_DWORD *)(this + 5296);
  *(_DWORD *)(this + 5244) = 0;
  *(_DWORD *)(this + 5248) = 0;
  *(_DWORD *)(this + 5252) = 0;
  *(_DWORD *)(this + 5256) = 0;
  *(_DWORD *)(this + 5264) = 0;
  *(_DWORD *)(this + 5268) = 0;
  v3 = (_DWORD *)(this + 5332);
  v4 = 4;
  do
  {
    v5 = (_DWORD *)v3 - 6;
    *v2 = 0;
    *(v3 - 8) = 0;
    *(v3 - 7) = 0;
    *v5 = 0;
    v2 += 12;
    v5[1] = 0;
    v5[2] = 0;
    v6 = (_DWORD *)v3 - 3;
    *(v3 - 3) = 0;
    v6[1] = 0;
    v6[2] = 0;
    v7 = v3;
    v3 += 12;
    --v4;
    *v7 = 0;
    v7[1] = 0;
    v7[2] = 0;
  }
  while ( v4 );
  *(_BYTE *)(this + 5272) = 0;
  *(_BYTE *)(this + 5273) = 0;
  *(_BYTE *)(this + 5274) = 0;
  *(_BYTE *)(this + 5275) = 0;
  *(_BYTE *)(this + 5276) = 0;
  *(_BYTE *)(this + 5277) = 0;
  *(_BYTE *)(this + 5278) = 0;
  *(_DWORD *)(this + 5280) = 1065353216;
  *(_DWORD *)(this + 5284) = 0;
  *(_DWORD *)(this + 5288) = 0;
  *(_DWORD *)(this + 5292) = 0;
  *(_DWORD *)(this + 5488) = 0;
  memset((void *)(this + 5296), 0, 0xC0u);
  *(_DWORD *)this = &off_570630;
  return this;
}

// 0x00524130
void UIWnd::ctor_4130()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_570630;
  ((UIItem *)(UIItem *)this + 3876)->UIItem();
  sub_522120((char *)this + 2236);
  ((UIWnd *)((char *)this + 1888))->Destroy2();
  ((UIWnd *)((char *)this + 1544))->Destroy2();
  ((UIWnd *)((char *)this + 1272))->~UIWnd();
  ((UIFrameWnd *)(UIWnd *)this + 28)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 968))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 816))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 664))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 512))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 9)->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x00525120
int UIWnd::ctor_5120(int _this)
{
  int v2; // edi
  int v3; // ebp
  int v4; // edi
  int v5; // ebp

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  `eh vector constructor iterator'(
    (char *)(this + 352),
    0xF8u,
    5,
    (void (*)(void *))UIStatic::UIStatic,
    (void (*)(void *))UIWnd::~UIWnd);
  ((UIFrameWnd *)(this + 1624))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1776))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1928))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 2080),
    0x158u,
    3,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  ((UIStatic *)(this + 3164))->UIStatic();
  ((UIStatic *)(this + 3412))->UIStatic();
  ((UIScene *)(this + 3660))->_UIScene();
  ((UIWnd *)(this + 4004))->ctor_9030();
  ((UIWnd *)(this + 4312))->ctor_9030();
  ((UIWnd *)(this + 4620))->ctor_9030();
  v2 = this + 4928;
  v3 = 2;
  do
  {
    ((void (*)(int))gbVec3D::`default constructor closure')(v2);
    v2 += 12;
    --v3;
  }
  while ( v3 );
  ((UIFrameWnd *)(this + 4952))->UIFrameWnd();
  ((UIFrameWnd *)(this + 5104))->UIFrameWnd();
  ((UIFrameWnd *)(this + 5256))->UIFrameWnd();
  ((UIFrameWnd *)(this + 5408))->UIFrameWnd();
  ((UIFrameWnd *)(this + 5560))->UIFrameWnd();
  ((UIFrameWnd *)(this + 5712))->UIFrameWnd();
  ((UIFrameWnd *)(this + 5864))->UIFrameWnd();
  ((UIFrameWnd *)(this + 6016))->UIFrameWnd();
  *(_BYTE *)(this + 6192) = 0;
  *(_DWORD *)(this + 6188) = 0;
  *(_DWORD *)(this + 6184) = 0;
  *(_BYTE *)(this + 6204) = 0;
  ((UIWnd *)(this + 6208))->ctor_F7F0();
  sub_444F60((UIWnd *)(this + 6468));
  ((UIFrameWnd *)(this + 6660))->UIFrameWnd();
  ((UIFrameWnd *)(this + 6812))->UIFrameWnd();
  v4 = this + 6972;
  v5 = 5;
  do
  {
    ArraySort(v4, 800, 2, (int)sub_5254C0);
    v4 += 1608;
    --v5;
  }
  while ( v5 );
  *(_BYTE *)(this + 15004) = 0;
  *(_DWORD *)(this + 15008) = 0;
  *(_BYTE *)(this + 15012) = 0;
  *(_BYTE *)(this + 15018) = 0;
  *(_DWORD *)(this + 15020) = 3;
  *(_DWORD *)(this + 15032) = 0;
  *(_BYTE *)(this + 15036) = 0;
  *(_BYTE *)(this + 15037) = 0;
  *(_BYTE *)(this + 15038) = 0;
  `eh vector constructor iterator'(
    (char *)(this + 15068),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 36092),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 57116),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 78140),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  *(_BYTE *)(this + 99196) = 0;
  *(_BYTE *)(this + 99197) = 0;
  *(_DWORD *)(this + 99200) = 0;
  ((UIItem *)(this + 99204))->Refresh();
  ((UIItem *)(this + 100572))->Refresh();
  *(_DWORD *)this = &off_5706CC;
  *(_DWORD *)(this + 15013) = 0;
  *(_BYTE *)(this + 15017) = 0;
  *(_DWORD *)(this + 15024) = 0;
  *(_BYTE *)(this + 15028) = 0;
  *(_DWORD *)(this + 15048) = 0;
  *(_DWORD *)(this + 15044) = 0;
  *(_DWORD *)(this + 15040) = 0;
  *(_DWORD *)(this + 15064) = 0;
  *(_DWORD *)(this + 15060) = 0;
  *(_DWORD *)(this + 15056) = 0;
  *(_DWORD *)(this + 15052) = 0;
  *(_DWORD *)(this + 6200) = 0;
  *(_DWORD *)(this + 6196) = 1;
  *(_BYTE *)(this + 6176) = 0;
  *(_DWORD *)(this + 6180) = 0;
  *(_WORD *)(this + 3160) = (unsigned __int16)&unk_1010101;
  *(_BYTE *)(this + 3162) = (unsigned __int8)&unk_1010101;
  return this;
}

// 0x00525540
void UIWnd::ctor_5540()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_5706CC;
  ((UIItem *)(UIItem *)this + 100572)->UIItem();
  ((UIItem *)(UIItem *)this + 99204)->UIItem();
  `eh vector destructor iterator'((char *)this + 78140, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 57116, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 36092, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 15068, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  ((UIWnd *)((char *)this + 6812))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 6660))->_UIFrameWnd();
  sub_445010((UIWnd *)((char *)this + 6468));
  ((UIWnd *)((char *)this + 6208))->~UIWnd();
  ((UIWnd *)((char *)this + 6016))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 5864))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 5712))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 139)->_UIFrameWnd();
  ((UIWnd *)(this + 52))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 5256))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 5104))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4952))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 4620))->ctor_9130();
  ((UIWnd *)((char *)this + 4312))->ctor_9130();
  ((UIWnd *)((char *)this + 4004))->ctor_9130();
  ((UIWnd *)((char *)this + 3660))->Destroy2();
  ((UIWnd *)((char *)this + 3412))->~UIWnd();
  ((UIWnd *)((char *)this + 3164))->~UIWnd();
  `eh vector destructor iterator'((char *)this + 2080, 0x158u, 3, (void (*)(void *))UIScene::Destroy2);
  ((UIWnd *)((char *)this + 1928))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1776))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1624))->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 352, 0xF8u, 5, (void (*)(void *))UIWnd::~UIWnd);
  ((UIWnd *)this)->~UIWnd();
}

// 0x005257B0
_DWORD * UIWnd::ctor_57B0(int _this, int a2)
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
  _DWORD *v31; // ebp
  int v32; // ebx
  _DWORD *v33; // ebp
  int v34; // ebx
  int v35; // edx
  _DWORD *v36; // eax
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

  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 80) = *(_DWORD *)(this + 88);
  *(_DWORD *)(this + 84) = *(_DWORD *)(this + 76) + *(_DWORD *)(this + 92);
  ((UIListBox *)this)->SetSelTexture(-1, *(_DWORD *)(this + 72), *(_DWORD *)(this + 76), *(_DWORD *)(this + 80), *(_DWORD *)(this + 84), 0);
  *(_DWORD *)(this + 99200) = a2;
  v3 = *(_DWORD *)(this + 4952);
  v48 = 32;
  v47 = 168;
  v49 = 636;
  v50 = 136;
  (*(void (**)(int, void *, int *, int))(v3 + 16))(this + 4952, &unk_AA0C00, &v47, this);
  ((UIWnd **)(this + 4952))->CreateFromTemplate(aSubgameApprais_1, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v4 = *(_DWORD *)(this + 5104);
  v48 += 6;
  v47 += 24;
  v50 = v48 + 158;
  v49 = v47 + 428;
  (*(void (**)(int, void *, int *, int))(v4 + 16))(this + 5104, &unk_AA0C00, &v47, this);
  ((UIWnd *)(this + 5104))->SetShow(0);
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
  ((UIWnd *)(this + 5104))->GetChild((int)id);
  v5 = *(_DWORD *)(this + 5864);
  v63[1] = 0;
  v63[0] = 0;
  v64 = 14;
  v65 = 600;
  (*(void (**)(int, void *, _DWORD *, int))(v5 + 16))(this + 5864, &unk_AA0B00, v63, this);
  ((UIWnd **)(this + 5864))->CreateFromTemplate(aUiGamemainuiCo_17, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v6 = *(_DWORD *)(this + 6016);
  v63[0] = 786;
  v64 = 800;
  (*(void (**)(int, void *, _DWORD *, int))(v6 + 16))(this + 6016, &unk_AA0B00, v63, this);
  ((UIWnd **)(this + 6016))->CreateFromTemplate(aUiGamemainuiCo_17, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v7 = *(_DWORD *)(this + 6208);
  v73[1] = 0;
  v73[0] = 16;
  v73[2] = 788;
  v73[3] = 92;
  (*(void (**)(int, void *, _DWORD *, int))(v7 + 16))(this + 6208, &unk_AA0C00, v73, this);
  ((UIWnd **)(this + 6208))->GetChildCount(aSubgameApprais_10, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  ((UIWnd **)(this + 6208))->GetChildAt(aSubgameApprais_11, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  sub_43FD90((float *)(this + 6208), 0);
  ((UIWnd *)this + 6208)->FindChild(620.0);
  *(_DWORD *)(this + 6420) = 1;
  *(_DWORD *)(this + 6448) = 300;
  *(_DWORD *)(this + 6440) = 1092616192;
  *(_DWORD *)(this + 6428) = 255;
  ((UIWnd *)this + 6208)->FindChildByName(620.0);
  *(_DWORD *)(this + 6320) = 1142620160;
  v8 = *(_DWORD *)(this + 5408);
  v60 = 18;
  v59 = 64;
  v61 = 96;
  v62 = 42;
  (*(void (**)(int, void *, int *, int))(v8 + 16))(this + 5408, &unk_AA0C00, &v59, this);
  v9 = *(_DWORD *)(this + 5560);
  v60 = v62;
  v62 += 24;
  (*(void (**)(int, void *, int *, int))(v9 + 16))(this + 5560, &unk_AA0C00, &v59, this);
  v10 = *(_DWORD *)(this + 1624);
  v70[1] = 136;
  v70[0] = 90;
  v70[2] = 714;
  v70[3] = 598;
  (*(void (**)(int, void *, _DWORD *, int))(v10 + 16))(this + 1624, &unk_AA0C00, v70, this);
  ((UIWnd **)(this + 1624))->CreateFromTemplate(aSubgameApprais_2, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v66[1] = 162;
  v66[0] = 120;
  v67 = 160;
  v68 = 208;
  v12 = (_DWORD *)&off_5706AC;
  v13 = (gbRefObject **)(this + 352);
  do
  {
    LOBYTE(v11) = *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756);
    ((void (*)(gbRefObject **, _DWORD, _DWORD *, int, char *, int))(*v13)[7].RefCount)(
      v13,
      *v12,
      v66,
      this,
      aSubgameApprais_3,
      v11);
    sub_440CE0(v13, aSubgameApprais_4, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
    ++v12;
    v66[0] = v67;
    v13 += 62;
    v67 += 40;
  }
  while ( (int)v12 < (int)&off_5706C0 );
  v14 = *(_DWORD *)(this + 5256);
  v71[1] = 170;
  v71[0] = 326;
  v71[2] = 482;
  v71[3] = 202;
  (*(void (**)(int, void *, _DWORD *, int))(v14 + 16))(this + 5256, &unk_AA0C21, v71, this);
  ((UIWnd *)(this + 5256))->SetShow(0);
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
  ((UIWnd *)(this + 5256))->GetChild((int)id);
  v52 = 146;
  v51 = 552;
  v53 = 597;
  v54 = 210;
  v16 = (int (__stdcall **)(int))&off_5706C0;
  v17 = (PalScript **)(this + 2080);
  v18 = (int *)(this + 3112);
  do
  {
    LOBYTE(v15) = *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756);
    ((void (*)(PalScript **, int (__stdcall *)(int), int *, int, char *, _DWORD, int))(*v17)->m_CamObj.m_nSize)(
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
    v17->OpenScript(aSubgameApprais_7, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
    v15 = v53;
    ++v16;
    v18 += 4;
    v17 += 86;
    v51 = v53 + 2;
    v53 += 47;
  }
  while ( (int)v16 < (int)&off_5706CC );
  v22 = *(_DWORD *)(this + 99200);
  v44 = 548;
  v43 = 213;
  v45 = 307;
  v46 = 568;
  LOBYTE(v22) = *(_BYTE *)(v22 + 1756);
  (*(void (**)(int, void *, int *, int, char *, int))(*(_DWORD *)(this + 3164) + 28))(
    this + 3164,
    &unk_AA0C16,
    &v43,
    this,
    aSubgameApprais_8,
    v22);
  v23 = v44;
  *(_DWORD *)(this + 99164) = v43;
  v24 = v46;
  *(_DWORD *)(this + 99168) = v23;
  v25 = v45;
  *(_DWORD *)(this + 99172) = v45;
  v43 = v25 + 200;
  *(_DWORD *)(this + 99176) = v24;
  v26 = *(_DWORD *)(this + 99200);
  v45 = v25 + 294;
  LOBYTE(v26) = *(_BYTE *)(v26 + 1756);
  (*(void (**)(int, void *, int *, int, char *, int))(*(_DWORD *)(this + 3412) + 28))(
    this + 3412,
    &unk_AA0C17,
    &v43,
    this,
    aSubgameApprais_8,
    v26);
  v27 = v44;
  v72[1] = 573;
  v72[0] = 358;
  v72[2] = 448;
  *(_DWORD *)(this + 99180) = v43;
  v28 = v45;
  v72[3] = 598;
  *(_DWORD *)(this + 99184) = v27;
  v29 = v46;
  *(_DWORD *)(this + 99188) = v28;
  v30 = *(_DWORD *)(this + 99200);
  *(_DWORD *)(this + 99192) = v29;
  LOBYTE(v29) = *(_BYTE *)(v30 + 1756);
  (*(void (**)(int, void *, _DWORD *, int, char *, _DWORD, int))(*(_DWORD *)(this + 3660) + 28))(
    this + 3660,
    &unk_AA0C18,
    v72,
    this,
    aUiGamemainuiMu_0,
    0,
    v29);
  (**(void (***)(int, _DWORD))(this + 3660))(this + 3660, 0);
  sub_439740((UIWnd *)(this + 4004), (int)&unk_AA0C25, this);
  sub_43A070(this + 4004, 600.0);
  sub_439850(this + 4004, 400, 320);
  v31 = (_DWORD *)(this + 4080);
  v32 = 5;
  do
  {
    *v31 = 0;
    sub_43A090(this + 4004, 1, 180.0);
    *(_DWORD *)(this + 4248) = 58;
    v31 += 8;
    --v32;
    ++*(_DWORD *)(this + 4072);
  }
  while ( v32 );
  sub_439740((UIWnd *)(this + 4312), (int)&unk_AA0C26, this);
  sub_43A070(this + 4312, 600.0);
  sub_439850(this + 4312, 400, 320);
  v33 = (_DWORD *)(this + 4388);
  v34 = 5;
  do
  {
    *v33 = 0;
    sub_43A090(this + 4312, 1, 180.0);
    *(_DWORD *)(this + 4556) = 58;
    v33 += 8;
    --v34;
    ++*(_DWORD *)(this + 4380);
  }
  while ( v34 );
  v35 = *(_DWORD *)(this + 1776);
  *(_DWORD *)(this + 4932) = -1029701632;
  *(_DWORD *)(this + 4944) = -1029701632;
  *(_DWORD *)(this + 4928) = -1017380864;
  *(_DWORD *)(this + 4936) = 0;
  *(_DWORD *)(this + 4940) = 1130102784;
  *(_DWORD *)(this + 4948) = 0;
  v56 = 136;
  v55 = 90;
  v57 = 716;
  v58 = 603;
  (*(void (**)(int, void *, int *, int))(v35 + 16))(this + 1776, &unk_AA0C19, &v55, this);
  ((UIWnd **)(this + 1776))->CreateFromTemplate(aSubgameApprais_9, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  (**(void (***)(int, _DWORD))(this + 1776))(this + 1776, 0);
  sub_439740((UIWnd *)(this + 4620), (int)&unk_AA0C27, this);
  sub_43A070(this + 4620, 580.0);
  sub_439850(this + 4620, 400, 346);
  v36 = (_DWORD *)(this + 4696);
  v37 = 5;
  do
  {
    *v36 = 0;
    v36 += 8;
    --v37;
    ++*(_DWORD *)(this + 4688);
  }
  while ( v37 );
  v38 = *(_DWORD *)(this + 1928);
  v56 = 164;
  v55 = 326;
  v57 = 482;
  v58 = 196;
  (*(void (**)(int, void *, int *, int))(v38 + 16))(this + 1928, &unk_AA0C19, &v55, this);
  ((UIWnd *)(this + 1928))->SetShow(0);
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
  ((UIWnd *)(this + 1928))->GetChild((int)id);
  (**(void (***)(int, _DWORD))(this + 1928))(this + 1928, 0);
  v39 = *(_DWORD *)(this + 5712);
  v74[1] = 158;
  v74[0] = 536;
  v74[2] = 581;
  v74[3] = 208;
  (*(void (**)(int, void *, _DWORD *, int))(v39 + 16))(this + 5712, &unk_AA0C00, v74, this);
  ((UIWnd **)(this + 5712))->CreateFromTemplate(aSubgameApprais_6, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  (**(void (***)(int, _DWORD))(this + 5712))(this + 5712, 0);
  a3[0] = 300;
  a3[3] = 300;
  *(_DWORD *)(this + 6168) = 45;
  *(_DWORD *)(this + 6172) = 50;
  a3[1] = 200;
  a3[2] = 500;
  ((UIItem *)(this + 99204))->Create((int)&unk_ABE00B, (int)a3);
  ((UIItem *)(this + 99204))->SetData(31);
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
  ((UIWnd *)(this + 99204))->GetChild((int)id);
  ((UIItem *)(this + 100572))->Create((int)&unk_ABC00C, (int)a3);
  ((UIItem *)(this + 100572))->SetData(31);
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
  ((UIWnd *)(this + 100572))->GetChild((int)id);
  *(_DWORD *)(this + 6456) = 120;
  *(_DWORD *)(this + 6460) = 534;
  *(_DWORD *)(this + 6464) = 420;
  *(_DWORD *)(this + 6452) = 278;
  ((UINote *)(this + 6468))->Create((int)&unk_AA0C22, this + 6452, this, aUiFlexNote);
  (**(void (***)(int, _DWORD))(this + 6468))(this + 6468, 0);
  (*(void (**)(int, void *, int, int))(*(_DWORD *)(this + 6660) + 16))(
    this + 6660,
    &unk_AA0C22,
    this + 6452,
    this);
  ((UIWnd *)(this + 6660))->SetShow(0);
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
  ((UIWnd *)(this + 6660))->GetChild((int)id);
  (**(void (***)(int, _DWORD))(this + 6660))(this + 6660, 0);
  (*(void (**)(int, void *, int, int))(*(_DWORD *)(this + 6812) + 16))(
    this + 6812,
    &unk_AA0C23,
    this + 6452,
    this);
  ((UIWnd *)(this + 6812))->SetShow(0);
  (**(void (***)(int, _DWORD))(this + 6812))(this + 6812, 0);
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
  return (_DWORD *)((UIWnd *)(this + 6812))->GetChild((int)id);
}

// 0x00526A40
int UIWnd::ctor_6A40(int _this, int a2, int ( *a3)(int a2), int a4)
{
  int (__stdcall *v6)(int); // edx
  int v7; // eax
  int (__stdcall **v8)(int); // ecx
  int v9; // edi
  int (__stdcall **v10)(int); // ebp
  void (**v11)(int, int); // edx
  char *Instance; // eax
  char *v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // esi
  void (**v17)(int, _DWORD); // edx
  void (**v18)(int, _DWORD); // eax
  int v19; // ebp
  int *v20; // edi
  int v21; // edi
  _DWORD *v22; // ebp
  int v23; // ecx
  _DWORD *v24; // esi
  int v25; // edi
  int v26; // eax
  _DWORD *v27; // esi
  int v28; // edi
  void *v29; // [esp-8h] [ebp-24h]
  char *v30; // [esp-8h] [ebp-24h]
  int v31; // [esp-4h] [ebp-20h]
  int pOut; // [esp+10h] [ebp-Ch] BYREF
  int pOut2; // [esp+14h] [ebp-8h] BYREF
  int SkillNum; // [esp+18h] [ebp-4h]
  _DWORD *v35; // [esp+20h] [ebp+4h]

  switch ( a2 )
  {
    case 1000:
      if ( !a3 )
        return 1;
      sub_526300((char *)this);
      sub_527130((_DWORD *)this, *(_DWORD *)(this + 15008));
      sub_5263C0(this);
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
          v35 = (_DWORD *)(this + 2080);
          do
          {
            if ( !*(_BYTE *)(this + 6176) && v6 == *v10 )
            {
              if ( !*(_BYTE *)(this + 15018) )
              {
                v11 = *(void (***)(int, int))(this + 5712);
                *(_BYTE *)(this + 6176) = 1;
                (*v11)(this + 5712, 1);
                *(_DWORD *)(this + 6180) = v9;
                sub_445E50(v35, 0);
                *(_DWORD *)(this + 4892) = 0;
                *(_DWORD *)(this + 4888) = 0;
                *(_DWORD *)(this + 4884) = 0;
              }
              v29 = off_5E7ECC;
              Instance = (char *)CScreenMode::GetInstance();
              ((CScreenMode *)Instance)->AudioSetPosition(v29, 1);
              v6 = a3;
            }
            ++v10;
            ++v9;
            v35 += 86;
          }
          while ( (int)v10 < (int)&off_5706CC );
          if ( (char *)v6 == (char *)&unk_AA0C16 )
          {
            if ( *(_BYTE *)(this + 15018) )
              return 1;
            if ( *(_BYTE *)(this + 6176) )
            {
              *(_DWORD *)(this + 3244) = 0;
              *(_BYTE *)(this + 3232) = 0;
            }
            *(_BYTE *)(this + 15012) = 1;
            *(_DWORD *)(this + 3492) = 0;
            *(_BYTE *)(this + 3480) = 0;
            (**(void (***)(int, int))(this + 3660))(this + 3660, 1);
            if ( *(_DWORD *)(this + 15032) )
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 0;
            else
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 1;
            if ( !*(_BYTE *)(this + 3232) && !*(_BYTE *)(this + 3480) )
            {
              v18 = *(void (***)(int, _DWORD))(this + 3660);
              *(_BYTE *)(this + 15012) = 0;
              (*v18)(this + 3660, 0);
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 0;
            }
          }
          else
          {
            if ( (char *)v6 - (char *)&unk_AA0C16 != 1 )
            {
              if ( (char *)v6 - (char *)&unk_AA0C16 == 2 && !*(_BYTE *)(this + 15018) && !*(_BYTE *)(this + 6176) )
              {
                sub_5273D0(this);
                goto LABEL_20;
              }
              return 1;
            }
            if ( *(_BYTE *)(this + 15018) )
              return 1;
            if ( *(_BYTE *)(this + 6176) )
            {
              *(_DWORD *)(this + 3492) = 0;
              *(_BYTE *)(this + 3480) = 0;
            }
            *(_BYTE *)(this + 15012) = 1;
            *(_DWORD *)(this + 3244) = 0;
            *(_BYTE *)(this + 3232) = 0;
            (**(void (***)(int, int))(this + 3660))(this + 3660, 1);
            if ( *(_DWORD *)(this + 15032) )
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 0;
            else
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 1;
            if ( !*(_BYTE *)(this + 3232) && !*(_BYTE *)(this + 3480) )
            {
              v17 = *(void (***)(int, _DWORD))(this + 3660);
              *(_BYTE *)(this + 15012) = 0;
              (*v17)(this + 3660, 0);
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 0;
            }
          }
          sub_527370(this, *(_DWORD *)(this + 15008));
          v30 = (char *)off_5E7ECC;
          goto LABEL_21;
        }
      }
      if ( *(_BYTE *)(this + 6176) )
      {
        v14 = this + 248 * v7;
        if ( *(_BYTE *)(v14 + 420) )
        {
          *(_DWORD *)(v14 + 432) = 0;
          *(_BYTE *)(v14 + 420) = 0;
        }
        else
        {
          *(_DWORD *)(v14 + 432) = 1;
          *(_BYTE *)(v14 + 420) = 1;
        }
        return 1;
      }
      if ( *(_BYTE *)(this + 15012) || *(_BYTE *)(this + 15018) )
      {
        if ( !*(_BYTE *)(v7 + this + 15013) )
        {
          v15 = this + 248 * v7 + 352;
          *(_DWORD *)(v15 + 80) = 0;
          *(_BYTE *)(v15 + 68) = 0;
        }
        if ( *(_DWORD *)(this + 15008) == v7 )
        {
          v16 = this + 248 * v7 + 352;
          *(_DWORD *)(v16 + 80) = 1;
          *(_BYTE *)(v16 + 68) = 1;
        }
        v30 = (char *)off_5E7ED8[0];
      }
      else if ( *(_BYTE *)(v7 + this + 15013) )
      {
        v30 = (char *)off_5E7ED8[0];
      }
      else
      {
        *(_DWORD *)(this + 15008) = v7;
        if ( sub_5270C0((char *)this, v7) > 0 )
          sub_527130((_DWORD *)this, *(_DWORD *)(this + 15008));
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
        if ( !*(_BYTE *)(this + 15018) && !*(_BYTE *)(this + 6176) )
          *(_BYTE *)(this + 99196) = 1;
      }
      else if ( (char *)a3 - (char *)&unk_AA0C16 == 1 && !*(_BYTE *)(this + 15018) && !*(_BYTE *)(this + 6176) )
      {
        *(_BYTE *)(this + 99197) = 1;
        return 1;
      }
      return 1;
    case 1009:
      if ( (char *)a3 != (char *)&unk_AA0C22 )
        return 1;
      if ( *(_BYTE *)(*(_DWORD *)(this + 99200) + 1740) )
      {
        v19 = 0;
        v20 = (int *)(this + 6968);
        do
        {
          if ( *(_BYTE *)(this + v19 + 15024) )
          {
            v31 = *v20;
            pOut2 = 0;
            SkillNum = 0;
            pOut = v31;
            SkillNum = ((PAL_GDB *)&g_GDB)->GDB_GetSkillNum(v31);
            pOut2 = 1;
            CCBStageRole_GetAlive((int)&g_SceneMgr.m_npc[0].m_path.normal[79].y, &pOut);
          }
          ++v19;
          v20 += 402;
        }
        while ( v19 < 5 );
      }
      sub_527F50(*(int **)(this + 99200), 3);
      return 1;
    case 1010:
      if ( *(_BYTE *)(this + 15018) )
      {
        sub_527370(this, *(_DWORD *)(this + 15008));
        *(_DWORD *)(this + 4892) = 0;
        *(_DWORD *)(this + 4888) = 0;
        *(_DWORD *)(this + 4884) = 0;
        v21 = 0;
        v22 = (_DWORD *)(this + 2080);
        do
        {
          if ( *(_BYTE *)(this + v21 + 3160) )
            sub_445E50(v22, 1);
          ++v21;
          v22 += 86;
        }
        while ( v21 < 3 );
      }
      return 1;
    case 1013:
      if ( (char *)a3 == (char *)&unk_AA0C25 )
      {
        if ( *(_BYTE *)(this + 6176) )
        {
          sub_527230(this, 0, *(_DWORD *)(this + 15008));
          v26 = *(_DWORD *)(this + 6180);
          v27 = (_DWORD *)(this + 2080);
          v28 = 3;
          *((_BYTE *)v27 + v26 + 1080) = 0;
          do
          {
            sub_445E50(v27, 0);
            v27 += 86;
            --v28;
          }
          while ( v28 );
        }
        return 1;
      }
      if ( (char *)a3 - (char *)&unk_AA0C25 != 1 || !*(_BYTE *)(this + 6176) )
        return 1;
      sub_527230(this, 1, *(_DWORD *)(this + 15008));
      v23 = *(_DWORD *)(this + 6180);
      v24 = (_DWORD *)(this + 2080);
      v25 = 3;
      *((_BYTE *)v24 + v23 + 1080) = 0;
      do
      {
        sub_445E50(v24, 0);
        v24 += 86;
        --v25;
      }
      while ( v25 );
      return 1;
    case 1016:
      if ( (char *)a3 == (char *)&unk_AA0C27 )
      {
        ((GRPinput *)&g_Input)->GetMousePos(&pOut, &pOut2);
        *(float *)(this + 4884) = (double)pOut2 + *(float *)(this + 4884);
        *(float *)(this + 4888) = (double)pOut + *(float *)(this + 4888);
      }
      return 1;
    default:
      return a2->SendMessage((int)a3, a4);
  }
}

// 0x00527950
int UIWnd::ctor_7950(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 352) = 0;
  ((UIItem *)(this + 356))->Refresh();
  *(_DWORD *)(this + 1724) = 0;
  *(_DWORD *)(this + 1728) = 0;
  *(_DWORD *)(this + 1744) = 0;
  *(_DWORD *)this = &off_5706EC;
  *(_BYTE *)(this + 1756) = 1;
  return this;
}

// 0x005279F0
void UIWnd::ctor_79F0()
{
  int v2; // ecx
  int v3; // ecx

  this->m_fontcolor.ColorQuadFmt = (int)&off_5706EC;
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
  ((UIWnd *)this)->~UIWnd();
}

// 0x005282E0
int UIWnd::ctor_82E0(int _this)
{
  int v2; // edi
  int v3; // ebp
  int v4; // edi
  int v5; // ebp

  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  ((UIScene *)(this + 352))->_UIScene();
  ((UIFrameWnd *)(this + 696))->UIFrameWnd();
  ((UIFrameWnd *)(this + 848))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1000))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1152))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1304))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1456))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1608))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1760))->UIFrameWnd();
  ((UIWnd *)(this + 1912))->ctor_9030();
  v2 = this + 2220;
  v3 = 5;
  do
  {
    ((void (*)(int))gbVec3D::`default constructor closure')(v2);
    v2 += 12;
    --v3;
  }
  while ( v3 );
  ((UIWnd *)(this + 2280))->ctor_9030();
  ((UIFrameWnd *)(this + 2588))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2740))->UIFrameWnd();
  sub_431870((_DWORD *)(this + 2900));
  v4 = this + 4712;
  v5 = 5;
  do
  {
    ArraySort(v4, 800, 2, (int)sub_5254C0);
    v4 += 1608;
    --v5;
  }
  while ( v5 );
  *(_DWORD *)(this + 12744) = 0;
  ((UIItem *)(this + 12752))->Refresh();
  `eh vector constructor iterator'(
    (char *)(this + 14124),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (char *)(this + 35148),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  *(_BYTE *)(this + 56188) = 0;
  *(_BYTE *)(this + 56189) = 0;
  *(_DWORD *)this = &off_570728;
  *(_DWORD *)(this + 2896) = 0;
  return this;
}

// 0x005284E0
void UIWnd::ctor_84E0()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_570728;
  `eh vector destructor iterator'((char *)this + 35148, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 14124, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  ((UIItem *)(UIItem *)this + 12752)->UIItem();
  sub_4318A0((int)this + 2900);
  ((UIWnd *)((char *)this + 2740))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 2588))->_UIFrameWnd();
  ((UIWnd *)(UIWnd *)this + 57)->ctor_9130();
  ((UIWnd *)((char *)this + 1912))->ctor_9130();
  ((UIFrameWnd *)(UIWnd *)this + 44)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1608))->_UIFrameWnd();
  ((UIWnd *)(this + 14))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1304))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1152))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 25)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 848))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 696))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 352))->Destroy2();
  ((UIWnd *)this)->~UIWnd();
}

// 0x005295F0
int UIWnd::ctor_95F0(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 352) = 0;
  ((UIFrameWnd *)(this + 360))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 512),
    0xB8u,
    3,
    (void (*)(void *))UIWnd::ctor_2E10,
    (void (*)(void *))UIWnd::ctor_2E80);
  sub_444A20((UIFrameWnd *)(this + 1064));
  *(_BYTE *)(this + 1260) = 0;
  *(_DWORD *)(this + 1256) = 0;
  *(_DWORD *)(this + 1252) = 0;
  *(_BYTE *)(this + 1280) = 0;
  *(_DWORD *)(this + 1276) = 0;
  *(_DWORD *)(this + 1272) = 0;
  ((UIFrameWnd *)(this + 1284))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1436))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1840))->UIFrameWnd();
  sub_444F60((UIWnd *)(this + 1992));
  *(_DWORD *)(this + 1268) = 32;
  *(_DWORD *)(this + 1264) = 32;
  *(_DWORD *)this = &off_57076C;
  *(_DWORD *)(this + 1588) = 64;
  *(_DWORD *)(this + 1592) = 58;
  *(_DWORD *)(this + 1708) = 28;
  *(_DWORD *)(this + 1820) = 1065353216;
  *(_DWORD *)(this + 1824) = 1060152279;
  *(_DWORD *)(this + 1828) = 1036831949;
  *(_DWORD *)(this + 1832) = 1008981770;
  *(_DWORD *)(this + 1600) = 0;
  *(_DWORD *)(this + 1596) = 0;
  *(_DWORD *)(this + 1604) = 800;
  *(_DWORD *)(this + 1608) = 600;
  *(_DWORD *)(this + 2188) = 0;
  *(_BYTE *)(this + 2200) = 1;
  return this;
}

// 0x00529790
void UIWnd::ctor_9790()
{
  UIRenderObj *Instance; // eax

  this->m_fontcolor.ColorQuadFmt = (int)&off_57076C;
  Instance = (UIRenderObj *)UIQuadManager::GetInstance();
  Instance->~UIRenderObj(1u);
  sub_445010((UIWnd *)((char *)this + 1992));
  ((UIFrameWnd *)(UIWnd *)this + 46)->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1436))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 1284))->_UIFrameWnd();
  sub_444AC0((UIWnd *)((char *)this + 1064));
  `eh vector destructor iterator'((char *)this + 512, 0xB8u, 3, (void (*)(void *))UIWnd::ctor_2E80);
  ((UIFrameWnd *)(UIWnd *)this + 9)->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}

// 0x0052BA10
int UIWnd::ctor_BA10(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  sub_431870((_DWORD *)(this + 352));
  *(_DWORD *)(this + 1132) = 418;
  *(_DWORD *)(this + 1136) = 418;
  *(_DWORD *)(this + 1140) = 48;
  *(_DWORD *)(this + 1144) = 192;
  *(_DWORD *)(this + 1148) = 78;
  *(_DWORD *)(this + 1152) = 78;
  *(_BYTE *)(this + 1156) = 0;
  *(_BYTE *)(this + 1157) = 0;
  *(_BYTE *)(this + 1159) = 0;
  ((UIFrameWnd *)(this + 1160))->UIFrameWnd();
  ((UIWnd *)(this + 1312))->ctor_2E10();
  `eh vector constructor iterator'(
    (char *)(this + 1496),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIFrameWnd *)(this + 2120))->UIFrameWnd();
  ((UIFrameWnd *)(this + 2272))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 2424),
    0x610u,
    5,
    (void (*)(void *))sub_52BBD0,
    (void (*)(void *))sub_52BC90);
  *(_DWORD *)(this + 10184) = 0;
  *(_BYTE *)(this + 10188) = 1;
  *(_DWORD *)(this + 10192) = 0;
  *(_DWORD *)(this + 10196) = 1092616192;
  *(_BYTE *)(this + 10200) = 0;
  *(_BYTE *)(this + 10206) = 0;
  ((UIItem *)(this + 10208))->Refresh();
  ((UIItem *)(this + 11576))->Refresh();
  *(_DWORD *)this = &off_570830;
  *(_DWORD *)(this + 2104) = -1;
  *(_DWORD *)(this + 2108) = -1;
  *(_DWORD *)(this + 2112) = -1;
  *(_DWORD *)(this + 2116) = -1;
  *(_DWORD *)(this + 10201) = 0;
  *(_BYTE *)(this + 10205) = 0;
  *(_BYTE *)(this + 12953) = 1;
  return this;
}

// 0x0052BD50
void UIWnd::ctor_BD50()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_570830;
  ((UIItem *)(UIItem *)this + 11576)->UIItem();
  ((UIItem *)(UIItem *)this + 10208)->UIItem();
  `eh vector destructor iterator'((char *)this + 2424, 0x610u, 5, (void (*)(void *))sub_52BC90);
  ((UIWnd *)((char *)this + 2272))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 53)->_UIFrameWnd();
  `eh vector destructor iterator'((char *)this + 1496, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 1312))->ctor_2E80();
  ((UIFrameWnd *)(UIWnd *)this + 29)->_UIFrameWnd();
  sub_4318A0((int)this + 352);
  ((UIWnd *)this)->~UIWnd();
}

// 0x00531D20
int UIWnd::ctor_1D20(int _this)
{
  ((UIListBox *)this)->UIListBox();
  *(_BYTE *)(this + 360) = 0;
  *(_DWORD *)(this + 356) = 0;
  *(_DWORD *)(this + 352) = 0;
  ((UIFrameWnd *)(this + 364))->UIFrameWnd();
  ((UIFrameWnd *)(this + 1316))->UIFrameWnd();
  `eh vector constructor iterator'(
    (char *)(this + 1468),
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (char *)(this + 2988),
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_BYTE *)(this + 4536) = 0;
  *(_DWORD *)(this + 4532) = 0;
  *(_DWORD *)(this + 4528) = 0;
  ((UIItem *)(this + 4540))->Refresh();
  ((UIItem *)(this + 5908))->Refresh();
  ((UIFrameWnd *)(this + 7280))->UIFrameWnd();
  ((UIFrameWnd *)(this + 7432))->UIFrameWnd();
  *(_BYTE *)(this + 7592) = 0;
  *(_DWORD *)(this + 7588) = 0;
  *(_DWORD *)(this + 7584) = 0;
  *(_DWORD *)this = &off_570890;
  *(_DWORD *)(this + 1308) = 0;
  *(_BYTE *)(this + 7598) = 1;
  return this;
}

// 0x00531E70
void UIWnd::ctor_1E70()
{
  this->m_fontcolor.ColorQuadFmt = (int)&off_570890;
  ((UIWnd *)((char *)this + 7432))->_UIFrameWnd();
  ((UIFrameWnd *)(UIWnd *)this + 182)->_UIFrameWnd();
  ((UIItem *)(UIItem *)this + 5908)->UIItem();
  ((UIItem *)(UIItem *)this + 4540)->UIItem();
  `eh vector destructor iterator'((char *)this + 2988, 0x98u, 10, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 1468, 0x98u, 10, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  ((UIWnd *)((char *)this + 1316))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 364))->_UIFrameWnd();
  ((UIWnd *)this)->~UIWnd();
}
