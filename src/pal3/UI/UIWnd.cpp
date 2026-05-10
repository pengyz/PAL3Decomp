#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/UIWnd.h"

// Forward declarations for unnamed functions
int sub_40CC60(...);
int sub_41C090(...);
int sub_431870(...);
int sub_4318A0(...);
int sub_431C10(...);
int sub_432680(...);
int sub_4326A0(...);
int sub_439030(...);
int sub_439130(...);
int sub_4391A0(...);
int sub_439230(...);
int sub_439740(...);
int sub_439810(...);
int sub_439850(...);
int sub_439930(...);
int sub_43A070(...);
int sub_43A090(...);
int sub_43A160(...);
int sub_43A1F0(...);
int sub_43B3E0(...);
int sub_43B4D0(...);
int sub_43BBB0(...);
int sub_43BCE0(...);
int sub_43BE80(...);
int sub_43D880(...);
int sub_43EBB0(...);
int sub_43F650(...);
int sub_43F7F0(...);
int sub_43F9C0(...);
int sub_43FD90(...);
int sub_440CE0(...);
int sub_4410F0(...);
int sub_4411D0(...);
int sub_4414D0(...);
int sub_4427C0(...);
int sub_443190(...);
int sub_4431D0(...);
int sub_4434C0(...);
int sub_4438F0(...);
int sub_444A20(...);
int sub_444AC0(...);
int sub_444F60(...);
int sub_445010(...);
int sub_445BF0(...);
int sub_445C10(...);
int sub_445E10(...);
int sub_445E50(...);
int sub_4461B0(...);
int sub_4461F0(...);
int sub_44A3D0(...);
int sub_44A7F0(...);
int sub_44AB90(...);
int sub_44ACE0(...);
int sub_44B850(...);
int sub_44B890(...);
int sub_44BA60(...);
int sub_44BD60(...);
int sub_44BD80(...);
int sub_44BE60(...);
int sub_44BE80(...);
int sub_44C910(...);
int sub_44C970(...);
int sub_44DB50(...);
int sub_44E5E0(...);
int sub_44F050(...);
int sub_450390(...);
int sub_450AD0(...);
int sub_450EB0(...);
int sub_451900(...);
int sub_451CC0(...);
int sub_451DA0(...);
int sub_452790(...);
int sub_452850(...);
int sub_453030(...);
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
_DWORD *sub_439030(_DWORD *this)
{
  UIWnd::UIWnd();
  `eh vector constructor iterator'(this + 18, 0x20u, 5, sub_4391A0, nullsub_3);
  *((_DWORD *)this + 74) = 0;
  *((_DWORD *)this + 75) = 0;
  *((_DWORD *)this + 76) = 0;
  *((_DWORD *)this + 71) = 1065353216;
  *((_DWORD *)this + 70) = 1065353216;
  *((_DWORD *)this + 69) = 1065353216;
  * this = (*)&off_56AC20;
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
  return this;
}

// 0x00439130
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_439130(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AC20;
  sub_439810();
  `eh vector destructor iterator'((char *)this + 72, 0x20u, 5, nullsub_3);
  this->_UIWnd();
}

// 0x0043A160
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_43A160(_DWORD *this)
{
  UIWnd::UIWnd();
  UIWnd::DestroyChildren(this + 19);
  *((_DWORD *)this + 36) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 37) = 0;
  * this = (*)&off_56AC4C;
  *((_DWORD *)this + 17) = 1092616192;
  *((_DWORD *)this + 39) = -1;
}

// 0x0043A1F0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_43A1F0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AC4C;
  this->Reset();
  (char *->MoveWindow()this + 76);
  this->_UIWnd();
}

// 0x0043BB70
_DWORD * UIWnd::ctor_BB70()
{
  UIWnd::UIWnd();
  * this = (*)&off_56ACB8;
  *((_DWORD *)this + 17) = 0;
  return this;
}

// 0x0043BBB0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_43BBB0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ACB8;
  this->_UIWnd();
}

// 0x0043BCE0
// write access to const memory has been detected, the output may be wrong!
_DWORD *sub_43BCE0(_DWORD *this)
{
  UIWnd::UIWnd();
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
  * this = (*)&off_56ACD8;
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
  return this;
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
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ACD8;
  sub_43BE80();
  this->_UIWnd();
}

// 0x0043D830
_DWORD * UIWnd::ctor_D830()
{
  UIWnd::UIWnd();
  * this = (*)&off_56ACFC;
  *((_DWORD *)this + 20) = 0;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 17) = 32;
  *((_DWORD *)this + 18) = 32;
  return this;
}

// 0x0043D880
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_43D880(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ACFC;
  this->_UIWnd();
}

// 0x0043DD10
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD20;
  UIListBox::SetScrollPos();
  this->_UIWnd();
}

// 0x0043F560
int UIWnd::CreateChild()
{
  int v1; // edx

  if ( *((_DWORD *)this + 108) <= 0 )
    return -1;
  v1 = *((_DWORD *)this + 280);
  if ( v1 == -1 )
    return -1;
  else
    return v1 + *((_DWORD *)this + 279);
}

// 0x0043F7F0
// write access to const memory has been detected, the output may be wrong!
_DWORD *sub_43F7F0(_DWORD *this)
{
  int v2; // ecx

  UIWnd::UIWnd();
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
  * this = (*)&off_56AD64;
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
  return this;
}

// 0x0043F970
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD64;
  sub_43F9C0();
  this->_UIWnd();
}

// 0x0043FA00
void UIWnd::GetChildCount(gbRefObject **this, LPCSTR lpString, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  int v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString;
  if ( lpString )
  {
    v5 = *((_DWORD *)this + 43);
    if ( v5 )
      v5->Release();
    OpenBaseFile::OpenBaseFile(&lpString);
    v6 = a3 == 0;
    *((_DWORD *)this + 44) = 0;
    if ( v6 )
    {
      *((_DWORD *)this + 43) = (gbRefObject *)(*(int (**)(int, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                      g_pGfxManager,
                                      v3);
    }
    else
    {
      v7 = *(_DWORD *)g_pGfxManager;
      v8 = v3->_CalculateUV();
      *((_DWORD *)this + 43) = (gbRefObject *)(*(int (**)(int, int))(v7 + 8))(g_pGfxManager, v8);
      *((_DWORD *)this + 44) = (gbRefObject *)v3->Parent_Data();
    }
    v9 = (gbTexture *)*((_DWORD *)this + 43);
    if ( v9 )
      v9->LoadTexture(1);
    (struct gbVFileSystem **->OpenNULLFile()&lpString);
  }
}

// 0x0043FAE0
void UIWnd::GetChildAt(gbRefObject **this, LPCSTR lpString, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  bool v6; // zf
  int v7; // ebp
  int v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString;
  if ( lpString )
  {
    v5 = *((_DWORD *)this + 45);
    if ( v5 )
      v5->Release();
    OpenBaseFile::OpenBaseFile(&lpString);
    v6 = a3 == 0;
    *((_DWORD *)this + 46) = 0;
    if ( v6 )
    {
      *((_DWORD *)this + 45) = (gbRefObject *)(*(int (**)(int, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                      g_pGfxManager,
                                      v3);
    }
    else
    {
      v7 = *(_DWORD *)g_pGfxManager;
      v8 = v3->_CalculateUV();
      *((_DWORD *)this + 45) = (gbRefObject *)(*(int (**)(int, int))(v7 + 8))(g_pGfxManager, v8);
      *((_DWORD *)this + 46) = (gbRefObject *)v3->Parent_Data();
    }
    v9 = (gbTexture *)*((_DWORD *)this + 45);
    if ( v9 )
      v9->LoadTexture(1);
    (struct gbVFileSystem **->OpenNULLFile()&lpString);
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
  *((_DWORD *)this + 34) = (float)a2;
}

// 0x0043FDC0
void UIWnd::GetWidth(int a2)
{
  *((_DWORD *)this + 35) = (float)a2;
}

// 0x0043FDD0
void UIWnd::GetHeight(int a2)
{
  *((_DWORD *)this + 36) = (float)a2;
}

// 0x0043FDE0
void UIWnd::GetPosition(int a2)
{
  *((_DWORD *)this + 37) = (float)a2;
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
  _DWORD *v2; // edx
  _DWORD *v3; // ecx
  int result; // eax

  v2 = this + 19;
  v3 = this + 4;
  * v2 = (*)*a2;
  v2[1] = a2[1];
  v2[2] = a2[2];
  v2[3] = a2[3];
  * v3 = (*)*a2;
  v3[1] = a2[1];
  v3[2] = a2[2];
  result = a2[3];
  v3[3] = result;
  return result;
}

// 0x004407C0
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AD88;
  UIStatic::OnMessage();
  this->_UIWnd();
}

// 0x004410F0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
_DWORD *sub_4410F0(_DWORD *this)
{
  UIWnd::UIWnd();
  UIWnd::ctor_D830(this + 18);
  UIWnd::DestroyChildren(this + 48);
  * this = (*)&off_56ADAC;
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
  memset(this + 65, 0, 0x28u);
  return this;
}

// 0x004411D0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_4411D0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56ADAC;
  sub_4414D0();
  (char *->MoveWindow()this + 192);
  (UIWnd *->ctor_D880()((char *)this + 72));
  this->_UIWnd();
}

// 0x004426B0
void UIWnd::CreateFromTemplate(gbRefObject **this, LPCSTR lpString1, char a3)
{
  const CHAR *v3; // edi
  gbRefObject *v5; // ecx
  char v6; // al
  int v7; // ebx
  int v8; // eax
  gbTexture *v9; // ecx

  v3 = lpString1;
  if ( lpString1 )
  {
    v5 = *((_DWORD *)this + 28);
    if ( v5 )
      v5->Release();
    OpenBaseFile::OpenBaseFile(&lpString1);
    lstrcmpA(v3, String2);
    v6 = a3;
    *((_DWORD *)this + 29) = 0;
    if ( v6 )
    {
      v7 = *(_DWORD *)g_pGfxManager;
      v8 = v3->_CalculateUV();
      *((_DWORD *)this + 28) = (gbRefObject *)(*(int (**)(int, int))(v7 + 8))(g_pGfxManager, v8);
      *((_DWORD *)this + 29) = (gbRefObject *)v3->Parent_Data();
    }
    else
    {
      *((_DWORD *)this + 28) = (gbRefObject *)(*(int (**)(int, const CHAR *))(*(_DWORD *)g_pGfxManager + 8))(
                                      g_pGfxManager,
                                      v3);
    }
    v9 = (gbTexture *)*((_DWORD *)this + 28);
    if ( v9 )
      v9->LoadTexture(1);
    if ( !lstrcmpA(v3, String2) )
      MEMORY[0xD90D3C] = (int)*((_DWORD *)this + 28);
    (struct gbVFileSystem **->OpenNULLFile()&lpString1);
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
void sub_4427C0(_DWORD *this, const char *a2, int a3)
{
  int v3; // ebp
  unsigned int v4; // kr04_4
  unsigned int v5; // ebx
  int v6; // ecx
  char v7; // al
  unsigned int v8; // eax
  int v9; // ecx

  if ( a2 )
  {
    v3 = (int)(this + 24);
    v4 = strlen(a2) + 1;
    v5 = v4 - 1;
    if ( v4 - 1 > 0xFFFFFFFD )
      std::_Xlen();
    v6 = *(_DWORD *)(v3 + 4);
    if ( v6 && (v7 = *(_BYTE *)(v6 - 1)) != 0 && v7 != -1 )
    {
      if ( v4 == 1 )
      {
        *(_BYTE *)(v6 - 1) = v7 - 1;
        *(_DWORD *)(v3 + 4) = 0;
        *(_DWORD *)(v3 + 8) = 0;
        *(_DWORD *)(v3 + 12) = 0;
        goto LABEL_16;
      }
    }
    else
    {
      if ( v4 == 1 )
      {
        std::(_DWORD *->_Tidy()v3, 1);
        goto LABEL_16;
      }
      v8 = *(_DWORD *)(v3 + 12);
      if ( v8 <= 0x1F && v8 >= v5 )
      {
LABEL_15:
        qmemcpy(*(void **)(v3 + 4), a2, v5);
        v9 = *(_DWORD *)(v3 + 4);
        *(_DWORD *)(v3 + 8) = v5;
        *(_BYTE *)(v9 + v5) = 0;
LABEL_16:
        if ( a3 )
          *((_DWORD *)this + 18) = 1;
        else
          *((_DWORD *)this + 18) = 0;
        return;
      }
      std::(_DWORD *->_Tidy()v3, 1);
    }
    v3->GetKeyState(v5);
    goto LABEL_15;
  }
}

// 0x00442E10
void UIWnd::ctor_2E10()
{
  this->UIFrameWnd();
  *((_DWORD *)this + 41) = 1056964608;
  *((_DWORD *)this + 38) = 0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 42) = 0;
  *((_BYTE *)this + 172) = 0;
  *((_DWORD *)this + 44) = 0;
  * this = (*)&off_56AE10;
  *((_DWORD *)this + 36) = 21;
}

// 0x00442E80
void UIWnd::ctor_2E80(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AE10;
  this->_UIFrameWnd();
}

// 0x00443550
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AE64;
  sub_4438F0();
  this->_UIWnd();
}

// 0x00445920
int UIWnd::Reset()
{
  return (gbRefObject **->MoveWindow()this + 26);
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
    *((_DWORD *)this + 22) = *(_DWORD *)&this->m_fontcolor[16];
    *((_DWORD *)this + 23) = *(_DWORD *)&this->m_fontcolor[20];
    *((_DWORD *)this + 24) = *(_DWORD *)&this->m_fontcolor[24];
    result = *(_DWORD *)&this->m_fontcolor[28];
    *((_DWORD *)this + 25) = result;
  }
  return result;
}

// 0x00445AA0
UIWnd::UIWnd()
{
  int v3; // [esp+4h] [ebp-4h]

  PtrArray::Clear(this + 9);
  * this = (*)&off_56AEC8;
  *((_DWORD *)this + 3) = -1;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) = 0;
  *((_DWORD *)this + 6) = 0;
  *((_DWORD *)this + 7) = 0;
  *((_DWORD *)this + 8) = 0;
  *((_DWORD *)this + 13) = 0;
  *((_DWORD *)this + 14) = 0;
  *((_DWORD *)this + 15) = 0;
  *((_DWORD *)this + 16) = 0;
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
  *((_DWORD *)this + 1) = v3;
  *((_DWORD *)this + 2) = -1;
  return this;
}

// 0x00445B40
void std::ios_base::~ios_base(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AEC8;
  this->UpdateChildren();
  sub_432680((void **)&this->_data[36]);
}

// 0x00445B90
int UIWnd::Create(int id, void *pRect, int parent)
{
  *(_DWORD *)&this->m_fontcolor[12] = id;
  *(_DWORD *)&this->m_fontcolor[16] = *(_DWORD *)pRect;
  *(_DWORD *)&this->m_fontcolor[20] = *((_DWORD *)pRect + 1);
  *(_DWORD *)&this->m_fontcolor[24] = *((_DWORD *)pRect + 2);
  *(_DWORD *)&this->m_fontcolor[28] = *((_DWORD *)pRect + 3);
  *(_DWORD *)&this->m_fontcolor[32] = parent;
  if ( parent )
  {
    sub_445BF0((int *)parent, (int)this);
    sub_445E10(*(_DWORD **)&this->m_fontcolor[32], &this->m_fontcolor[16]);
  }
  *(_DWORD *)&this->m_fontcolor[52] = 1;
  *(_DWORD *)&this->m_fontcolor[56] = 1;
  *(_DWORD *)&this->m_fontcolor[60] = 1;
  return 1;
}

// 0x00445C10
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_445C10(_DWORD *this)
{
  int v2; // edi
  int v3; // ecx

  v2 = 0;
  *((_DWORD *)this + 13) = 0;
  *((_DWORD *)this + 14) = 0;
  for ( *((_DWORD *)this + 15) = 0; v2 < *((_DWORD *)this + 10); ++v2 )
  {
    v3 = *(_DWORD *)(*((_DWORD *)this + 9) + 4 * v2);
    (*(void (**)(int))(*(_DWORD *)v3 + 12))(v3);
  }
  sub_4326A0((int)(this + 9), 0, -1);
}

// 0x00445C60
BOOL UIWnd::HitTest(int a2, int a3)
{
  int v5; // edi
  int v6; // esi
  int v7; // ecx

  if ( !*((_DWORD *)this + 14) )
    return 0;
  if ( !*((_DWORD *)this + 15) )
    return 0;
  v5 = *((_DWORD *)this + 10) - 1;
  if ( v5 < 0 )
    return a3 == 0;
  v6 = a3;
  do
  {
    v7 = *(_DWORD *)(*((_DWORD *)this + 9) + 4 * v5);
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

  result = *((_DWORD *)this + 14);
  if ( result )
  {
    result = *((_DWORD *)this + 10);
    for ( i = 0; i < result; ++i )
    {
      v4 = *(_DWORD **)(*((_DWORD *)this + 9) + 4 * i);
      if ( v4[14] )
        (*(void (**)(_DWORD *))(*v4 + 4))(v4);
      result = *((_DWORD *)this + 10);
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
  return UIWnd::ClientToScreen(a2 - *((_DWORD *)this + 4), a3 - *((_DWORD *)this + 5));
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

  v4 = *((_DWORD *)this + 4);
  v5 = *((_DWORD *)this + 6);
  v6 = *((_DWORD *)this + 5);
  v7 = *((_DWORD *)this + 7);
  *((_DWORD *)this + 4) = a2 + v4;
  *((_DWORD *)this + 6) = a2 + v5;
  *((_DWORD *)this + 5) = a3 + v6;
  *((_DWORD *)this + 7) = a3 + v7;
  if ( this )
    (*(void (**)(_DWORD *, int, _DWORD, _DWORD))(*this + 24))(this, 1022, 0, 0);
  result = *((_DWORD *)this + 10);
  for ( i = 0; i < result; ++i )
  {
    a2->ClientToScreen(a3);
    result = *((_DWORD *)this + 10);
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
    v2 = MEMORY[0xBFD6D0];
    v3 = MEMORY[0xBFD6D4];
    v4 = 0;
    v5 = 0;
  }
  return this->ScreenToClient(v4 + (v2 + *(_DWORD *)&this->m_fontcolor[16] - *(_DWORD *)&this->m_fontcolor[24] - v4) / 2,
           v5 + (v3 + *(_DWORD *)&this->m_fontcolor[20] - *(_DWORD *)&this->m_fontcolor[28] - v5) / 2);
}

// 0x00445E70
int UIWnd::Destroy(int a2)
{
  int result; // eax
  int v3; // edx

  result = *((_DWORD *)this + 13);
  if ( result )
  {
    result = a2;
    if ( *((_DWORD *)this + 14) != a2 )
    {
      v3 = *this;
      *((_DWORD *)this + 14) = a2;
      return (*(int (__stdcall **)(int, int, _DWORD))(v3 + 24))(1000, a2, 0);
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
int UIWnd::MoveWindow(gbRefObject **this)
{
  int v2; // esi
  gbRefObject **v3; // ebx

  v2 = 0;
  if ( (int)*((_DWORD *)this + 16) > 0 )
  {
    v3 = this;
    do
    {
      gbRefObject::Release(*v3);
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

  result = (int)(this + 4);
  *((_DWORD *)this + 4) = *a2;
  *((_DWORD *)this + 5) = a2[1];
  *((_DWORD *)this + 6) = a2[2];
  *((_DWORD *)this + 7) = a2[3];
  if ( this )
    return (*(int (**)(_DWORD *, int, _DWORD, _DWORD))(*this + 24))(this, 1022, 0, 0);
  return result;
}

// 0x00445FE0
_DWORD * UIWnd::SetRect(_DWORD *a2)
{
  _DWORD *v3; // ecx

  v3 = this + 4;
  * a2 = (*)*v3;
  a2[1] = v3[1];
  a2[2] = v3[2];
  a2[3] = v3[3];
  return a2;
}

// 0x00446010
int UIWnd::GetChild(int id)
{
  *(_DWORD *)&this->m_fontcolor[4] = *(_DWORD *)id;
  return id;
}

// 0x004460D0
_DWORD * UIWnd::ctor_60D0()
{
  this->UIListBox();
  sub_4434C0(this + 90);
  `eh vector constructor iterator'(this + 128, 0x1DCu, 38, sub_4461B0, sub_4461F0);
  UIWnd::ctor_A160(this + 4654);
  *((_DWORD *)this + 4709) = 38;
  UIItem::Refresh(this + 4710);
  UIItem::Refresh(this + 5052);
  sub_431870(this + 5394);
  * this = (*)&off_56AF80;
  *((_DWORD *)this + 19) = 0;
  *((_DWORD *)this + 18) = 0;
  *((_DWORD *)this + 20) = 800;
  *((_DWORD *)this + 21) = 600;
  return this;
}

// 0x00446200
void UIWnd::ctor_6200()
{
  *(_DWORD *)this = &off_56AF80;
  (gbRefObject **->SetScrollPos()this);
  sub_4318A0((char *)this + 21576);
  (char *->UIItem()this + 20208);
  (char *->UIItem()this + 18840);
  (UIWnd *->ctor_A1F0()((char *)this + 18616));
  `eh vector destructor iterator'((char *)this + 512, 0x1DCu, 38, (void (*)(void *))sub_4461F0);
  UIWnd::~UIWnd((UIWnd *)this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
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
    v7 = &dword_56AEE8;
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
      (char *->SetDirectory()(this + 21576), &aQ07[64 * v6]);
      sub_431C10((char *)(this + 21576), aDefault, Destination, 256);
      if ( !*(_BYTE *)(this + 476 * v6 + 596) )
      {
        sprintf((char *const)(this + 104), "%s%s%s", byte_DDB03C, Destination, byte_DDB13C);
        (_DWORD *->SetEnable()(this + 20664), (const char *)(this + 104), 1);
        sub_4A1530(1);
        return 1;
      }
      sprintf((char *const)(this + 104), "%s%s%s", byte_DD953C, Destination, byte_DD963C);
      memset(Buffer, 0, sizeof(Buffer));
      v12 = 0;
      v13 = 0;
      sprintf(Buffer, "%s", (const char *)(this + 104));
      (_DWORD *->SetEnable()(this + 19296), Buffer, 1);
      sub_4A1530(1);
      *(_DWORD *)(this + 18836) = v6;
    }
    return 1;
  }
}

// 0x0044AB90
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int sub_44AB90(int _this)
{
  (_DWORD *->UIWnd()this);
  *(_DWORD *)(this + 108) = 360;
  *(_DWORD *)(this + 112) = 136;
  (_BYTE *->UIFrameWnd()(this + 124));
  (_BYTE *->UIFrameWnd()(this + 276));
  `eh vector constructor iterator'(
    (void *)(this + 428),
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_DWORD *->_UIScene()(this + 884));
  (_DWORD *->_UIScene()(this + 1228));
  (_DWORD *->_UIScene()(this + 1572));
  UIItem::Refresh(this + 1916);
  *(_BYTE *)(this + 3300) = 0;
  *(_DWORD *)(this + 3296) = 0;
  *(_DWORD *)(this + 3292) = 0;
  UIItem::Refresh(this + 3308);
  UIItem::Refresh(this + 4676);
  UIItem::Refresh(this + 6044);
  sub_44B850(this + 7420);
  *(_DWORD *)this = &off_56AFD4;
  *(_DWORD *)(this + 116) = 90;
  *(_DWORD *)(this + 120) = 24;
  return this;
}

// 0x0044ACE0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_44ACE0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56AFD4;
  sub_44B890((char *)this + 7420);
  (char *->UIItem()this + 6044);
  (char *->UIItem()this + 4676);
  (char *->UIItem()this + 3308);
  (char *->UIItem()this + 1916);
  (UIWnd *->Destroy2()((char *)this + 1572));
  (UIWnd *->Destroy2()((char *)this + 1228));
  (UIWnd *->Destroy2()((char *)this + 884));
  `eh vector destructor iterator'((char *)this + 428, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 276));
  (UIWnd *->_UIFrameWnd()((char *)this + 124));
  this->_UIWnd();
}

// 0x0044BA60
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int sub_44BA60(int _this)
{
  (_DWORD *->UIListBox()this);
  (_BYTE *->UIFrameWnd()(this + 360));
  `eh vector constructor iterator'(
    (void *)(this + 512),
    0xD0u,
    22,
    sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 5088),
    0xD0u,
    16,
    sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 8416),
    0xD0u,
    10,
    sub_44BE60,
    (void (*)(void *))j_UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 10496));
  (_BYTE *->UIFrameWnd()(this + 10648));
  (_BYTE *->UIFrameWnd()(this + 10800));
  (_BYTE *->UIFrameWnd()(this + 10952));
  sub_443190((_DWORD *)(this + 11116));
  sub_443190((_DWORD *)(this + 11308));
  (_DWORD *->_UIScene()(this + 11500));
  `eh vector constructor iterator'((void *)(this + 11844), 0x10u, 3, sub_44BD60, sub_44BD80);
  *(_DWORD *)(this + 11500) = &off_56B018;
  (_DWORD *->_UIScene()(this + 11892));
  `eh vector constructor iterator'((void *)(this + 12236), 0x10u, 3, sub_44BD60, sub_44BD80);
  *(_DWORD *)(this + 11892) = &off_56B018;
  (_DWORD *->_UIScene()(this + 12284));
  `eh vector constructor iterator'((void *)(this + 12628), 0x10u, 3, sub_44BD60, sub_44BD80);
  *(_DWORD *)(this + 12284) = &off_56B018;
  (_DWORD *->_UIScene()(this + 12676));
  `eh vector constructor iterator'((void *)(this + 13020), 0x10u, 3, sub_44BD60, sub_44BD80);
  *(_DWORD *)(this + 12676) = &off_56B018;
  (_DWORD *->_UIScene()(this + 13068));
  `eh vector constructor iterator'((void *)(this + 13412), 0x10u, 3, sub_44BD60, sub_44BD80);
  *(_DWORD *)(this + 13068) = &off_56B018;
  (_DWORD *->_UIScene()(this + 13460));
  `eh vector constructor iterator'((void *)(this + 13804), 0x10u, 3, sub_44BD60, sub_44BD80);
  *(_DWORD *)(this + 13460) = &off_56B018;
  *(_DWORD *)(this + 13868) = 0;
  *(_DWORD *)(this + 13872) = 0;
  *(_DWORD *)(this + 13876) = 0;
  *(_DWORD *)(this + 13884) = 0;
  *(_BYTE *)(this + 13892) = 1;
  *(_BYTE *)(this + 13893) = 1;
  *(_BYTE *)(this + 13894) = 0;
  (_BYTE *->UIFrameWnd()(this + 13904));
  (_BYTE *->UIFrameWnd()(this + 14080));
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
void sub_44BE80(UIWnd *this)
{
  *(_DWORD *)this = &off_56AFFC;
  sub_44C910();
  (UIWnd *->_UIFrameWnd()this + 352);
  (UIWnd *->_UIFrameWnd()((char *)this + 13904));
  if ( *((_DWORD *)this + 3469) )
  {
    operator delete(*((void **)this + 3469));
    *((_DWORD *)this + 3469) = 0;
  }
  *((_DWORD *)this + 3365) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13804, 0x10u, 3, (void (*)(void *))sub_44BD80);
  (UIWnd *->Destroy2()((char *)this + 13460));
  *((_DWORD *)this + 3267) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13412, 0x10u, 3, (void (*)(void *))sub_44BD80);
  (UIWnd *->Destroy2()((char *)this + 13068));
  *((_DWORD *)this + 3169) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 13020, 0x10u, 3, (void (*)(void *))sub_44BD80);
  (UIWnd *->Destroy2()((char *)this + 12676));
  *((_DWORD *)this + 3071) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 12628, 0x10u, 3, (void (*)(void *))sub_44BD80);
  (UIWnd *->Destroy2()((char *)this + 12284));
  *((_DWORD *)this + 2973) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 12236, 0x10u, 3, (void (*)(void *))sub_44BD80);
  (UIWnd *->Destroy2()((char *)this + 11892));
  *((_DWORD *)this + 2875) = &off_56B018;
  `eh vector destructor iterator'((char *)this + 11844, 0x10u, 3, (void (*)(void *))sub_44BD80);
  (UIWnd *->Destroy2()((char *)this + 11500));
  sub_4431D0((UIWnd *)((char *)this + 11308));
  sub_4431D0((UIWnd *)((char *)this + 11116));
  (UIWnd *->_UIFrameWnd()((char *)this + 10952));
  (UIWnd *->_UIFrameWnd()this + 270);
  (UIWnd *->_UIFrameWnd()((char *)this + 10648));
  (UIWnd *->_UIFrameWnd()((char *)this + 10496));
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
  (UIWnd *->_UIFrameWnd()this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x0044F050
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_44F050(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56B094;
  this->Destroy();
  `eh vector destructor iterator'((char *)this + 14544, 0x8E0u, 6, (void (*)(void *))sub_44E5E0);
  (UIWnd *->ctor_ACE0()((char *)this + 5012));
  sub_450EB0((char *)this + 3904);
  `eh vector destructor iterator'((char *)this + 2144, 0x160u, 5, sub_450390);
  sub_451900((char *)this + 656);
  sub_450AD0((char *)this + 356);
  sub_44A7F0((int)this + 260);
  this->_UIWnd();
}

// 0x0044FFE0
int UIWnd::ctor_FFE0(int _this)
{
  (_DWORD *->UIListBox()this);
  (_BYTE *->UIFrameWnd()(this + 76));
  *(_DWORD *)this = &off_56B0B4;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 8) = -1;
  return this;
}

// 0x00450090
void UIWnd::ctor_90()
{
  *(_DWORD *)this = &off_56B0B4;
  (UIWnd *->_UIFrameWnd()((char *)this + 76));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00450710
_DWORD * UIWnd::ctor_710()
{
  this->UIListBox();
  UIWnd::ctor_F7F0(this + 18);
  * this = (*)&off_56B100;
  *((_DWORD *)this + 81) = 1120403456;
  return this;
}

// 0x00450790
void UIWnd::ctor_790()
{
  *(_DWORD *)this = &off_56B100;
  UIWnd::~UIWnd((UIWnd *)((char *)this + 72));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00451CC0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int sub_451CC0(int _this)
{
  (_DWORD *->UIWnd()this);
  (_DWORD *->ctor_F7F0()(this + 68));
  (_DWORD *->ctor_F7F0()(this + 312));
  `eh vector constructor iterator'(
    (void *)(this + 556),
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 1012));
  `eh vector constructor iterator'(
    (void *)(this + 1172),
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
void sub_451DA0(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56B19C;
  `eh vector destructor iterator'((char *)this + 1172, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 1012));
  `eh vector destructor iterator'((char *)this + 556, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  UIWnd::~UIWnd((UIWnd *)((char *)this + 312));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 68));
  this->_UIWnd();
}

// 0x00452600
void UIWnd::ctor_2600()
{
  *(_DWORD *)this = &off_56B1BC;
  (UIWnd *->ctor_1DA0()((char *)this + 1084));
  (UIWnd *->ctor_2850()((char *)this + 72));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00452790
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
int sub_452790(int _this)
{
  (_DWORD *->UIWnd()this);
  (_DWORD *->_UIScene()(this + 68));
  (_BYTE *->UIFrameWnd()(this + 412));
  (_DWORD *->ctor_2E10()(this + 564));
  sub_444F60((_BYTE *)(this + 748));
  (void *->DestroyChildren()(this + 940));
  *(_DWORD *)this = &off_56B1DC;
  *(_DWORD *)(this + 1008) = 0;
  return this;
}

// 0x00452850
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void sub_452850(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_56B1DC;
  (char *->MoveWindow()this + 940);
  sub_445010((UIWnd *)((char *)this + 748));
  (UIWnd *->ctor_2E80()((char *)this + 564));
  (UIWnd *->_UIFrameWnd()((char *)this + 412));
  (UIWnd *->Destroy2()((char *)this + 68));
  this->_UIWnd();
}

// 0x00452FD0
int UIWnd::ctor_2FD0(int _this)
{
  char v3; // [esp+7h] [ebp-1h]

  (_DWORD *->UIWnd()this);
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
void sub_453030(UIWnd *this)
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
  (_DWORD *->UIListBox()this);
  (_BYTE *->UIFrameWnd()(this + 360));
  (_BYTE *->UIFrameWnd()(this + 512));
  `eh vector constructor iterator'(
    (void *)(this + 664),
    0x178u,
    3,
    (void (*)(void *))sub_43B3E0,
    (void (*)(void *))sub_43B4D0);
  (_DWORD *->_UIScene()(this + 1792));
  (_BYTE *->UIFrameWnd()(this + 2136));
  (_BYTE *->UIFrameWnd()(this + 2288));
  (_BYTE *->UIFrameWnd()(this + 2440));
  (_BYTE *->UIFrameWnd()(this + 2592));
  (_BYTE *->UIFrameWnd()(this + 2744));
  (_DWORD *->_UIScene()(this + 2896));
  (_DWORD *->_UIScene()(this + 3240));
  (_DWORD *->_UIScene()(this + 3584));
  UIItem::Refresh(this + 3928);
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
  *(_DWORD *)this = &off_56B22C;
  (char *->UIItem()this + 3928);
  (UIWnd *->Destroy2()((char *)this + 3584));
  (UIWnd *->Destroy2()this + 81);
  (UIWnd *->Destroy2()((char *)this + 2896));
  (UIWnd *->_UIFrameWnd()((char *)this + 2744));
  (UIWnd *->_UIFrameWnd()((char *)this + 2592));
  (UIWnd *->_UIFrameWnd()this + 61);
  (UIWnd *->_UIFrameWnd()((char *)this + 2288));
  (UIWnd *->_UIFrameWnd()((char *)this + 2136));
  (UIWnd *->Destroy2()((char *)this + 1792));
  `eh vector destructor iterator'((char *)this + 664, 0x178u, 3, (void (*)(void *))sub_43B4D0);
  (UIWnd *->_UIFrameWnd()((char *)this + 512));
  (UIWnd *->_UIFrameWnd()this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00454590
int UIWnd::ctor_4590(int _this, int a2, int a3, int a4)
{
  int v6; // ecx
  int *v7; // eax
  int v8; // ecx
  int v9; // ecx
  int *v10; // eax
  int v11; // ecx
  int *v12; // edi
  char *v13; // [esp-8h] [ebp-10h]
  char *v14; // [esp-8h] [ebp-10h]
  int v15; // [esp-4h] [ebp-Ch]

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
          v13 = off_5ABBE0[0];
          CScreenMode::GetInstance();
          v13->AudioSetPosition(1);
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
          v8 = *(_DWORD *)(this + 5312);
          v15 = *(_DWORD *)(this + 5304);
          *(_BYTE *)(this + 5308) = 1;
          sub_44DB50(v8, v15);
          v14 = off_5ABBE0[0];
LABEL_16:
          CScreenMode::GetInstance();
          v14->AudioSetPosition(1);
          return 1;
        case -1431698501:
          sub_454420(this, 0);
          sub_4543C0(this, 1u);
          break;
        default:
          return 1;
      }
      v14 = off_5ABBE0[0];
      goto LABEL_16;
    case 1002:
      v9 = 0;
      v10 = dword_56B220;
      while ( a3 != *v10 )
      {
        ++v10;
        ++v9;
        if ( (int)v10 >= (int)&off_56B22C )
          return 1;
      }
      if ( v9 )
      {
        v11 = v9 - 1;
        if ( v11 )
        {
          if ( v11 == 1 )
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
      (_DWORD *->SetEnable()(this + 512), (const char *)(this + 104), 0);
      return 1;
    case 1003:
      v12 = dword_56B220;
      do
      {
        if ( a3 == *v12 )
          (_DWORD *->SetEnable()(this + 512), MEMORY[0xC10D38], 0);
        ++v12;
      }
      while ( (int)v12 < (int)&off_56B22C );
      return 1;
    default:
      return a2->SendMessage(a3, a4);
  }
}

// 0x00454830
int UIWnd::ctor_4830(int _this)
{
  (_DWORD *->UIListBox()this);
  (_BYTE *->UIFrameWnd()(this + 360));
  (_DWORD *->_UIScene()(this + 512));
  `eh vector constructor iterator'((void *)(this + 892), 0xDE8u, 36, sub_4549A0, sub_454AA0);
  (_BYTE *->UIFrameWnd()(this + 129052));
  (_BYTE *->UIFrameWnd()(this + 129204));
  (_DWORD *->_UIScene()(this + 129356));
  (_DWORD *->_UIScene()(this + 129700));
  (_DWORD *->ctor_BCE0()(this + 130060));
  *(_DWORD *)(this + 130340) = 92;
  *(_DWORD *)(this + 130344) = 610;
  *(_DWORD *)(this + 130348) = 0;
  *(_DWORD *)(this + 130352) = 0;
  *(_DWORD *)(this + 130356) = 0;
  UIItem::Refresh(this + 130364);
  UIItem::Refresh(this + 131732);
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
  *(_DWORD *)this = &off_56B274;
  (char *->UIItem()this + 131732);
  (char *->UIItem()this + 130364);
  UIWnd::~UIWnd((UIWnd *)((char *)this + 130060));
  (UIWnd *->Destroy2()((char *)this + 129700));
  (UIWnd *->Destroy2()((char *)this + 129356));
  (UIWnd *->_UIFrameWnd()((char *)this + 129204));
  (UIWnd *->_UIFrameWnd()((char *)this + 129052));
  `eh vector destructor iterator'((char *)this + 892, 0xDE8u, 36, (void (*)(void *))sub_454AA0);
  (UIWnd *->Destroy2()((char *)this + 512));
  (UIWnd *->_UIFrameWnd()this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00456AB0
int UIWnd::ctor_6AB0(int _this)
{
  (_DWORD *->UIListBox()this);
  (_BYTE *->UIFrameWnd()(this + 360));
  `eh vector constructor iterator'(
    (void *)(this + 512),
    0x178u,
    52,
    (void (*)(void *))sub_43B3E0,
    (void (*)(void *))sub_43B4D0);
  (_DWORD *->_UIScene()(this + 20064));
  (_BYTE *->UIFrameWnd()(this + 20408));
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
  *(_DWORD *)this = &off_56B364;
  (UIWnd *->_UIFrameWnd()((char *)this + 20408));
  (UIWnd *->Destroy2()((char *)this + 20064));
  `eh vector destructor iterator'((char *)this + 512, 0x178u, 52, (void (*)(void *))sub_43B4D0);
  (UIWnd *->_UIFrameWnd()this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00457070
int UIWnd::ctor_7070(int _this, int a2, int a3, int a4)
{
  int result; // eax
  int v6; // eax
  int *v7; // ecx
  int v8; // eax
  int v9; // ecx
  int *v10; // eax
  int *v11; // eax
  char *v12; // [esp-8h] [ebp-10h]
  int v13; // [esp-4h] [ebp-Ch]

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
          CScreenMode::CreateDevice(this + 104, MEMORY[0xBFDA4C], 0, 0);
          v13 = (600 - CScreenMode::GetHeight(&g_DisplayConfig)) / 2;
          v8 = CScreenMode::GetWidth(&g_DisplayConfig);
          CScreenMode::SetViewport((800 - v8) / 2, v13);
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
      v12 = off_5B0DA4[0];
      CScreenMode::GetInstance();
      v12->AudioSetPosition(1);
      sub_44C970(*(_DWORD **)(this + 20564), 0);
      result = 1;
      break;
    case 1002:
      v9 = 0;
      v10 = dword_56B294;
      do
      {
        if ( a3 == *v10 )
        {
          (_DWORD *->SetEnable()(this + 20408), &byte_DD553C[256 * v9], 0);
          goto LABEL_20;
        }
        ++v10;
        ++v9;
      }
      while ( (int)v10 < (int)&off_56B364 );
      result = 1;
      break;
    case 1003:
      v11 = dword_56B294;
      while ( a3 != *v11 )
      {
        if ( (int)++v11 >= (int)&off_56B364 )
          return 1;
      }
      (_DWORD *->SetEnable()(this + 20408), MEMORY[0xC10D38], 0);
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
  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 120) = 800;
  *(_DWORD *)(this + 124) = 64;
  *(_DWORD *)(this + 136) = 360;
  *(_DWORD *)(this + 140) = 136;
  *(_BYTE *)(this + 152) = 0;
  (_BYTE *->UIFrameWnd()(this + 164));
  (_BYTE *->UIFrameWnd()(this + 316));
  `eh vector constructor iterator'(
    (void *)(this + 468),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_DWORD *->_UIScene()(this + 1228));
  (_DWORD *->_UIScene()(this + 1572));
  (_DWORD *->_UIScene()(this + 1916));
  (_DWORD *->_UIScene()(this + 2260));
  *(_BYTE *)(this + 2604) = 0;
  (_DWORD *->_UIScene()(this + 2608));
  (_BYTE *->UIFrameWnd()(this + 2952));
  (_BYTE *->UIFrameWnd()(this + 3104));
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
  *(_DWORD *)this = &off_56B394;
  sub_459360();
  (UIWnd *->_UIFrameWnd()((char *)this + 3104));
  (UIWnd *->_UIFrameWnd()((char *)this + 2952));
  (UIWnd *->Destroy2()((char *)this + 2608));
  (UIWnd *->Destroy2()((char *)this + 2260));
  (UIWnd *->Destroy2()((char *)this + 1916));
  (UIWnd *->Destroy2()((char *)this + 1572));
  (UIWnd *->Destroy2()((char *)this + 1228));
  `eh vector destructor iterator'((char *)this + 468, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 316));
  (UIWnd *->_UIFrameWnd()((char *)this + 164));
  UIWnd::~UIWnd((UIWnd *)this);
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

  (_DWORD *->UIListBox()this);
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
    lstrcpyA((LPSTR)v3 - 854, MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)v3 - 342, MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)v3 - 312, MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)v3 - 260, MEMORY[0xC10D38]);
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
    ArraySort((int)(v3 + 7), 12, 2, (int (*)(int))exception::exception);
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
  (_BYTE *->UIFrameWnd()(this + 24940));
  (_DWORD *->ctor_D830()(this + 25092));
  (_BYTE *->UIFrameWnd()(this + 25176));
  (_DWORD *->ctor_A160()(this + 25328));
  `eh vector constructor iterator'(
    (void *)(this + 25492),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 26356),
    0x98u,
    240,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)(this + 66916) = 0;
  `eh vector constructor iterator'(
    (void *)(this + 71000),
    0x34u,
    240,
    sub_45ADD0,
    (void (*)(void *))nullsub_1);
  `eh vector constructor iterator'(
    (void *)(this + 83480),
    0xB4u,
    30,
    (void (*)(void *))sub_444A20,
    (void (*)(void *))sub_444AC0);
  `eh vector constructor iterator'(
    (void *)(this + 88880),
    0x98u,
    30,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_BYTE *)(this + 93440) = 0;
  *(_BYTE *)(this + 93471) = 0;
  *(_DWORD *)(this + 93472) = 0;
  *(_DWORD *)(this + 93596) = 0;
  *(_DWORD *)(this + 93600) = 0;
  (_DWORD *->ctor_9030()(this + 93616));
  UIItem::Refresh(this + 93924);
  (_BYTE *->UIFrameWnd()(this + 95292));
  (_BYTE *->UIFrameWnd()(this + 95444));
  (_BYTE *->UIFrameWnd()(this + 95596));
  (_BYTE *->UIFrameWnd()(this + 95748));
  (_DWORD *->_UIScene()(this + 95916));
  (_DWORD *->_UIScene()(this + 96260));
  (_BYTE *->UIFrameWnd()(this + 96604));
  (_BYTE *->UIFrameWnd()(this + 96772));
  `eh vector constructor iterator'(
    (void *)(this + 96924),
    0x98u,
    13,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 98900));
  (_BYTE *->UIFrameWnd()(this + 99052));
  (char *->UpdateKeyCtrl()(this + 99204));
  (_DWORD *->_UIScene()(this + 100460));
  (_DWORD *->_UIScene()(this + 100804));
  *(_DWORD *)(this + 101148) = 32;
  *(_DWORD *)(this + 101152) = 16;
  *(_DWORD *)(this + 101156) = 0;
  *(_DWORD *)(this + 101160) = 0;
  (_BYTE *->UIFrameWnd()(this + 101176));
  (_BYTE *->UIFrameWnd()(this + 101328));
  (_BYTE *->UIFrameWnd()(this + 101496));
  (_BYTE *->UIFrameWnd()(this + 101664));
  (_BYTE *->UIFrameWnd()(this + 101832));
  (_DWORD *->_UIScene()(this + 102000));
  (_DWORD *->_UIScene()(this + 102364));
  (_DWORD *->_UIScene()(this + 102724));
  (_DWORD *->_UIScene()(this + 103084));
  (_DWORD *->_UIScene()(this + 103444));
  (_DWORD *->_UIScene()(this + 103788));
  (_DWORD *->_UIScene()(this + 104132));
  (_DWORD *->_UIScene()(this + 104476));
  (_DWORD *->_UIScene()(this + 104820));
  (_BYTE *->UIFrameWnd()(this + 105196));
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

  *(_DWORD *)this = &off_56B5CC;
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
  (gbRefObject **->SetScrollPos()this);
  (UIWnd *->_UIFrameWnd()((char *)this + 105196));
  (UIWnd *->Destroy2()((char *)this + 104820));
  (UIWnd *->Destroy2()((char *)this + 104476));
  (UIWnd *->Destroy2()((char *)this + 104132));
  (UIWnd *->Destroy2()((char *)this + 103788));
  (UIWnd *->Destroy2()((char *)this + 103444));
  (UIWnd *->Destroy2()((char *)this + 103084));
  (UIWnd *->Destroy2()((char *)this + 102724));
  (UIWnd *->Destroy2()((char *)this + 102364));
  (UIWnd *->Destroy2()this + 2550);
  (UIWnd *->_UIFrameWnd()((char *)this + 101832));
  (UIWnd *->_UIFrameWnd()((char *)this + 101664));
  (UIWnd *->_UIFrameWnd()((char *)this + 101496));
  (UIWnd *->_UIFrameWnd()((char *)this + 101328));
  (UIWnd *->_UIFrameWnd()((char *)this + 101176));
  (UIWnd *->Destroy2()((char *)this + 100804));
  (UIWnd *->Destroy2()((char *)this + 100460));
  (UIWnd *->DeleteRow()((char *)this + 99204));
  (UIWnd *->_UIFrameWnd()((char *)this + 99052));
  (UIWnd *->_UIFrameWnd()((char *)this + 98900));
  `eh vector destructor iterator'((char *)this + 96924, 0x98u, 13, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 96772));
  (UIWnd *->_UIFrameWnd()((char *)this + 96604));
  (UIWnd *->Destroy2()((char *)this + 96260));
  (UIWnd *->Destroy2()((char *)this + 95916));
  (UIWnd *->_UIFrameWnd()((char *)this + 95748));
  (UIWnd *->_UIFrameWnd()((char *)this + 95596));
  (UIWnd *->_UIFrameWnd()((char *)this + 95444));
  (UIWnd *->_UIFrameWnd()((char *)this + 95292));
  (char *->UIItem()this + 93924);
  (UIWnd *->ctor_9130()((char *)this + 93616));
  `eh vector destructor iterator'((char *)this + 88880, 0x98u, 30, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 83480, 0xB4u, 30, (void (*)(void *))sub_444AC0);
  `eh vector destructor iterator'((char *)this + 71000, 0x34u, 240, (void (*)(void *))nullsub_1);
  `eh vector destructor iterator'(
    (char *)this + 26356,
    0x98u,
    240,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 25492, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->ctor_A1F0()((char *)this + 25328));
  (UIWnd *->_UIFrameWnd()((char *)this + 25176));
  (UIWnd *->ctor_D880()((char *)this + 25092));
  (UIWnd *->_UIFrameWnd()((char *)this + 24940));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x0046D140
int UIWnd::ctor_D140(int _this)
{
  int v2; // eax

  (_DWORD *->UIListBox()this);
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
  (_BYTE *->UIFrameWnd()(this + 18144));
  (_DWORD *->ctor_D830()(this + 18296));
  (_BYTE *->UIFrameWnd()(this + 18380));
  (_DWORD *->_UIScene()(this + 18548));
  (_DWORD *->ctor_A160()(this + 18892));
  `eh vector constructor iterator'(
    (void *)(this + 19056),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  UIItem::Refresh(this + 19920);
  (_DWORD *->ctor_9030()(this + 21288));
  (_BYTE *->UIFrameWnd()(this + 21596));
  (_BYTE *->UIFrameWnd()(this + 21764));
  (_BYTE *->UIFrameWnd()(this + 21916));
  (_BYTE *->UIFrameWnd()(this + 22068));
  (_BYTE *->UIFrameWnd()(this + 22220));
  (_BYTE *->UIFrameWnd()(this + 22388));
  `eh vector constructor iterator'(
    (void *)(this + 22540),
    0x98u,
    13,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 24516));
  (_BYTE *->UIFrameWnd()(this + 24668));
  (char *->UpdateKeyCtrl()(this + 24836));
  (_DWORD *->_UIScene()(this + 26092));
  (_DWORD *->_UIScene()(this + 26436));
  *(_DWORD *)(this + 26780) = 32;
  *(_DWORD *)(this + 26784) = 16;
  *(_DWORD *)(this + 26788) = 0;
  *(_DWORD *)(this + 26792) = 0;
  (_BYTE *->UIFrameWnd()(this + 26808));
  (_BYTE *->UIFrameWnd()(this + 26960));
  (_BYTE *->UIFrameWnd()(this + 27112));
  (_BYTE *->UIFrameWnd()(this + 27264));
  (_BYTE *->UIFrameWnd()(this + 27432));
  (_DWORD *->_UIScene()(this + 27600));
  (_DWORD *->_UIScene()(this + 27964));
  (_DWORD *->_UIScene()(this + 28324));
  (_BYTE *->UIFrameWnd()(this + 28700));
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

  *(_DWORD *)this = &off_56B688;
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
  (gbRefObject **->SetScrollPos()this);
  (UIWnd *->_UIFrameWnd()((char *)this + 28700));
  (UIWnd *->Destroy2()((char *)this + 28324));
  (UIWnd *->Destroy2()((char *)this + 27964));
  (UIWnd *->Destroy2()this + 690);
  (UIWnd *->_UIFrameWnd()((char *)this + 27432));
  (UIWnd *->_UIFrameWnd()((char *)this + 27264));
  (UIWnd *->_UIFrameWnd()((char *)this + 27112));
  (UIWnd *->_UIFrameWnd()this + 674);
  (UIWnd *->_UIFrameWnd()((char *)this + 26808));
  (UIWnd *->Destroy2()((char *)this + 26436));
  (UIWnd *->Destroy2()((char *)this + 26092));
  (UIWnd *->DeleteRow()((char *)this + 24836));
  (UIWnd *->_UIFrameWnd()((char *)this + 24668));
  (UIWnd *->_UIFrameWnd()((char *)this + 24516));
  `eh vector destructor iterator'((char *)this + 22540, 0x98u, 13, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 22388));
  (UIWnd *->_UIFrameWnd()((char *)this + 22220));
  (UIWnd *->_UIFrameWnd()((char *)this + 22068));
  (UIWnd *->_UIFrameWnd()((char *)this + 21916));
  (UIWnd *->_UIFrameWnd()((char *)this + 21764));
  (UIWnd *->_UIFrameWnd()((char *)this + 21596));
  (UIWnd *->ctor_9130()((char *)this + 21288));
  (char *->UIItem()this + 19920);
  `eh vector destructor iterator'((char *)this + 19056, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->ctor_A1F0()((char *)this + 18892));
  (UIWnd *->Destroy2()((char *)this + 18548));
  (UIWnd *->_UIFrameWnd()((char *)this + 18380));
  (UIWnd *->ctor_D880()((char *)this + 18296));
  (UIWnd *->_UIFrameWnd()((char *)this + 18144));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00470A60
int UIWnd::ctor_A60(int _this)
{
  _DWORD *v2; // eax
  int v3; // ecx
  _DWORD *v4; // eax
  int v5; // ecx
  int v6; // eax

  (_DWORD *->UIListBox()this);
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
  (_BYTE *->UIFrameWnd()(this + 100672));
  (_DWORD *->ctor_D830()(this + 100824));
  (_BYTE *->UIFrameWnd()(this + 100908));
  (_DWORD *->_UIScene()(this + 101060));
  (_DWORD *->ctor_A160()(this + 101420));
  `eh vector constructor iterator'(
    (void *)(this + 101584),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)(this + 102424) = 250;
  *(_DWORD *)(this + 102428) = 150;
  UIItem::Refresh(this + 102448);
  (_DWORD *->ctor_9030()(this + 103816));
  (_BYTE *->UIFrameWnd()(this + 104140));
  (_BYTE *->UIFrameWnd()(this + 104292));
  (_BYTE *->UIFrameWnd()(this + 104444));
  (_BYTE *->UIFrameWnd()(this + 104596));
  `eh vector constructor iterator'(
    (void *)(this + 105020),
    0x158u,
    6,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  (_BYTE *->UIFrameWnd()(this + 107100));
  `eh vector constructor iterator'(
    (void *)(this + 107268),
    0xB4u,
    25,
    (void (*)(void *))sub_444A20,
    (void (*)(void *))sub_444AC0);
  (_DWORD *->ctor_D830()(this + 111768));
  (_BYTE *->UIFrameWnd()(this + 111852));
  `eh vector constructor iterator'(
    (void *)(this + 112004),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (char *->UpdateKeyCtrl()(this + 113844));
  (char *->UpdateKeyCtrl()(this + 115056));
  (char *->UpdateKeyCtrl()(this + 116268));
  (char *->UpdateKeyCtrl()(this + 117480));
  (char *->UpdateKeyCtrl()(this + 118692));
  (char *->UpdateKeyCtrl()(this + 119904));
  *(_DWORD *)(this + 121116) = 0;
  *(_DWORD *)(this + 121120) = 0;
  (_DWORD *->_UIScene()(this + 121156));
  (_DWORD *->_UIScene()(this + 121500));
  *(_DWORD *)(this + 121844) = 32;
  *(_DWORD *)(this + 121848) = 16;
  *(_DWORD *)(this + 121852) = 0;
  *(_DWORD *)(this + 121856) = 0;
  (_DWORD *->_UIScene()(this + 121872));
  (_DWORD *->_UIScene()(this + 122216));
  *(_DWORD *)(this + 122560) = -1;
  (_DWORD *->_UIScene()(this + 122580));
  (_DWORD *->_UIScene()(this + 122924));
  (_BYTE *->UIFrameWnd()(this + 123268));
  (_BYTE *->UIFrameWnd()(this + 123420));
  (_BYTE *->UIFrameWnd()(this + 123572));
  (_BYTE *->UIFrameWnd()(this + 123740));
  (_BYTE *->UIFrameWnd()(this + 123908));
  (_BYTE *->UIFrameWnd()(this + 124076));
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
  lstrcpyA((LPSTR)(this + 104764), MEMORY[0xC10D38]);
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
  *(_DWORD *)this = &off_56B794;
  *((_BYTE *)this + 46828) = 0;
  *((_DWORD *)this + 31062) = 0;
  (gbRefObject **->SetScrollPos()this);
  (UIWnd *->_UIFrameWnd()((char *)this + 124076));
  (UIWnd *->_UIFrameWnd()((char *)this + 123908));
  (UIWnd *->_UIFrameWnd()((char *)this + 123740));
  (UIWnd *->_UIFrameWnd()((char *)this + 123572));
  (UIWnd *->_UIFrameWnd()((char *)this + 123420));
  (UIWnd *->_UIFrameWnd()((char *)this + 123268));
  (UIWnd *->Destroy2()((char *)this + 122924));
  (UIWnd *->Destroy2()((char *)this + 122580));
  (UIWnd *->Destroy2()((char *)this + 122216));
  (UIWnd *->Destroy2()((char *)this + 121872));
  (UIWnd *->Destroy2()((char *)this + 121500));
  (UIWnd *->Destroy2()((char *)this + 121156));
  (UIWnd *->DeleteRow()((char *)this + 119904));
  (UIWnd *->DeleteRow()((char *)this + 118692));
  (UIWnd *->DeleteRow()this + 2937);
  (UIWnd *->DeleteRow()((char *)this + 116268));
  (UIWnd *->DeleteRow()((char *)this + 115056));
  (UIWnd *->DeleteRow()((char *)this + 113844));
  `eh vector destructor iterator'(
    (char *)this + 112004,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 111852));
  (UIWnd *->ctor_D880()((char *)this + 111768));
  `eh vector destructor iterator'((char *)this + 107268, 0xB4u, 25, (void (*)(void *))sub_444AC0);
  (UIWnd *->_UIFrameWnd()((char *)this + 107100));
  `eh vector destructor iterator'((char *)this + 105020, 0x158u, 6, (void (*)(void *))UIScene::Destroy2);
  (UIWnd *->_UIFrameWnd()((char *)this + 104596));
  (UIWnd *->_UIFrameWnd()((char *)this + 104444));
  (UIWnd *->_UIFrameWnd()((char *)this + 104292));
  (UIWnd *->_UIFrameWnd()((char *)this + 104140));
  (UIWnd *->ctor_9130()((char *)this + 103816));
  (char *->UIItem()this + 102448);
  `eh vector destructor iterator'((char *)this + 101584, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->ctor_A1F0()((char *)this + 101420));
  (UIWnd *->Destroy2()((char *)this + 101060));
  (UIWnd *->_UIFrameWnd()((char *)this + 100908));
  (UIWnd *->ctor_D880()((char *)this + 100824));
  (UIWnd *->_UIFrameWnd()((char *)this + 100672));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00477BB0
int UIWnd::ctor_7BB0(int _this, int a2, int a3, int a4)
{
  int v5; // eax
  _DWORD *v6; // ebx
  _DWORD *v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  void (***v11)(_DWORD, int); // ecx
  int result; // eax
  int v13; // edi
  int *v14; // eax
  int v15; // eax
  int v16; // eax
  int *v17; // eax
  int v18; // eax
  const char *v19; // ebp
  int v20; // eax
  const char *v21; // ebp
  void (***v22)(_DWORD, _DWORD); // edi
  int v23; // ebp
  int v24; // ebx
  const char **v25; // eax
  const char *v26; // ebp
  const char **v27; // eax
  const char **v28; // eax
  const char **v29; // eax
  const char **v30; // eax
  const char **v31; // eax
  int v32; // edi
  void (***v33)(_DWORD, int); // ebx
  int v34; // edi
  void (***v35)(_DWORD, int); // ebx
  int v36; // edi
  void (***v37)(_DWORD, int); // ebx
  int v38; // edi
  void (***v39)(_DWORD, int); // ebx
  int v40; // edi
  void (***v41)(_DWORD, int); // ebx
  int v42; // edx
  int *v43; // edi
  const char *v44; // eax
  const char *v45; // ecx
  int v46; // ebx
  int v47; // eax
  int v48; // ecx
  int v49; // edx
  int v50; // edx
  int v51; // ebp
  int v52; // edx
  int v53; // eax
  int v54; // eax
  int v55; // ecx
  signed int v56; // ecx
  char *v57; // [esp-8h] [ebp-160h]
  int v58; // [esp-8h] [ebp-160h]
  int v59; // [esp-8h] [ebp-160h]
  int v60; // [esp+10h] [ebp-148h]
  const char *v61; // [esp+10h] [ebp-148h]
  const char *v62; // [esp+14h] [ebp-144h]
  int v63; // [esp+18h] [ebp-140h] BYREF
  int v64; // [esp+1Ch] [ebp-13Ch]
  int v65; // [esp+20h] [ebp-138h]
  int v66; // [esp+24h] [ebp-134h]
  int v67; // [esp+28h] [ebp-130h] BYREF
  int v68; // [esp+30h] [ebp-128h] BYREF
  int v69; // [esp+38h] [ebp-120h] BYREF
  int v70; // [esp+40h] [ebp-118h] BYREF
  int v71; // [esp+48h] [ebp-110h] BYREF
  int v72; // [esp+50h] [ebp-108h] BYREF
  char Buffer[253]; // [esp+58h] [ebp-100h] BYREF
  __int16 v74; // [esp+155h] [ebp-3h]
  char v75; // [esp+157h] [ebp-1h]

  switch ( a2 )
  {
    case 1000:
      if ( !a3 )
        goto LABEL_36;
      sub_472AA0(this);
      sub_473520((char *)this, 0);
      v5 = 0;
      v6 = (_DWORD *)(this + 102348);
      v60 = 0;
      v7 = (_DWORD *)(this + 107448);
      do
      {
        if ( *(_BYTE *)(this + v5 + 102440) )
        {
          v8 = *(v6 - 1) - 24;
          v64 = *v6 + 36;
          v63 = v8;
          v66 = v64 + 30;
          v65 = v8 + 24;
          UIWnd::GetRect(v7 - 45, &v63);
          (*(void (**)(_DWORD *, _DWORD))*(v7 - 45))(v7 - 45, 0);
          v7->GetRect(&v63);
          (*(void (**)(_DWORD *, _DWORD))*v7)(v7, 0);
          UIWnd::GetRect(v7 + 45, &v63);
          v9 = *v6 + 36;
          v63 = v6[1] + 18;
          v65 = v63 + 22;
          v64 = v9;
          v66 = v9 + 30;
          UIWnd::GetRect(v7 + 90, &v63);
          (*(void (**)(_DWORD *, _DWORD))v7[90])(v7 + 90, 0);
          UIWnd::GetRect(v7 + 135, &v63);
          (*(void (**)(_DWORD *, _DWORD))v7[135])(v7 + 135, 0);
          v5 = v60;
        }
        ++v5;
        v6 += 4;
        v7 += 225;
        v60 = v5;
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
        (_DWORD *->SetEnable()(this + 104596), (const char *)(this + 1376), 0);
        v10 = lstrlenA((LPCSTR)(this + 1376));
        v11 = (void (***)(_DWORD, int))(this + 101420);
        if ( v10 > 0 )
          (**v11)(v11, 1);
        else
          (**v11)(v11, 0);
      }
      sprintf((char *const)(this + 80), "%s %d", byte_DC5F3C, MEMORY[0xC05F54]);
      (_DWORD *->SetEnable()(this + 123908), (const char *)(this + 80), 0);
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
                  sub_523820(2);
              }
              else
              {
                sub_45A220(*(_DWORD **)(this + 124252), 0);
              }
              goto LABEL_34;
            case 788:
              sub_475FC0(this);
              v57 = off_5B9DE4[0];
              goto LABEL_35;
            case 789:
              sub_4765D0((void *)this);
              v16 = *(_DWORD *)(this + 124248);
              if ( v16 )
              {
                if ( v16 == 1 )
                {
                  (_DWORD *->SetEnable()(this + 104596), MEMORY[0xC10D38], 0);
                  (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
                }
              }
              else
              {
                (**(void (***)(int, int))(this + 104596))(this + 104596, 1);
                (_DWORD *->SetEnable()(this + 104596), (const char *)(this + 1888), 0);
                (**(void (***)(int, int))(this + 101420))(this + 101420, 1);
              }
              goto LABEL_34;
            case 819:
              v58 = *(_DWORD *)(this + 121116);
              *(_DWORD *)(this + 122560) = 3;
              sub_473B50(this, v58, 3);
              v57 = off_5B9DE4[0];
              goto LABEL_35;
            case 820:
              v59 = *(_DWORD *)(this + 121116);
              *(_DWORD *)(this + 122560) = 0;
              sub_473B50(this, v59, 0);
LABEL_34:
              v57 = off_5B9DE4[0];
              goto LABEL_35;
            case 821:
              sub_4765F0(this, *(_DWORD *)(this + 121116));
              goto LABEL_31;
            case 822:
              sub_476ED0(this, *(_DWORD *)(this + 121116));
LABEL_31:
              (_DWORD *->SetEnable()(this + 104596), MEMORY[0xC10D38], 0);
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
      (_DWORD *->SetEnable()(this + 104596), MEMORY[0xC10D38], 0);
      (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
      v57 = off_5B9DE4[0];
LABEL_35:
      CScreenMode::GetInstance();
      v57->AudioSetPosition(1);
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
        (_DWORD *->SetEnable()(this + 123420), MEMORY[0xC10D38], 0);
        *(_DWORD *)(this + 103892) = 0;
        (**(void (***)(int, _DWORD))(this + 121156))(this + 121156, 0);
        (**(void (***)(int, _DWORD))(this + 121500))(this + 121500, 0);
        result = 1;
      }
      else
      {
        (_DWORD *->SetEnable()(this + 104596), MEMORY[0xC10D38], 0);
        (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
        sub_477A90(this, *(_DWORD *)(this + 121116), *(_DWORD *)(this + 592));
        v17 = *(int **)(this + 12 * (*(_DWORD *)(this + 592) + 299 * *(_DWORD *)(this + 121116)) + 46840);
        if ( *((_BYTE *)v17 + 613) == 5 )
        {
          sub_43A070(this + 103816, 228.0);
          sub_439930(this + 103816, 330, 280, 600);
        }
        else if ( *((_BYTE *)v17 + 612) == 11 )
        {
          sub_43A070(this + 103816, 228.0);
          sub_439930(this + 103816, 330, 272, 600);
        }
        else
        {
          v18 = *v17;
          if ( v18 == 8114 || v18 == 8132 )
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
                MEMORY[0xC10D38]) )
        {
          sprintf((char *const)(this + 80), "%s", aNone);
        }
        else
        {
          v19 = (const char *)(*(_DWORD *)(this
                                         + 12 * (*(_DWORD *)(this + 592) + 299 * *(_DWORD *)(this + 121116))
                                         + 46840)
                             + 36);
          sprintf((char *const)(this + 80), "Item\\%s\\%s.pol", v19, v19);
        }
        sub_439230((int *)(this + 103888), (const char *)(this + 80), 0);
        v20 = *(_DWORD *)(this + 12 * (*(_DWORD *)(this + 592) + 299 * *(_DWORD *)(this + 121116)) + 46840);
        v21 = (const char *)(v20 + 36);
        v61 = (const char *)(v20 + 66);
        if ( !strcmp((const char *)(v20 + 36), MEMORY[0xC10D38]) )
        {
          sprintf((char *const)(this + 80), "%s", aNone);
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v74 = 0;
          v75 = 0;
          sprintf(Buffer, "%s%s", v21, v61);
          sprintf((char *const)(this + 80), "Item\\%s\\%s.tga", v21, Buffer);
        }
        gbGeomNode::ReplaceTexture(*(gbGeomNode **)(this + 103904), (const char *)(this + 80));
        *(_DWORD *)(this + 103892) = 1;
        v22 = (void (***)(_DWORD, _DWORD))(this + 107268);
        v23 = 5;
        do
        {
          v24 = 5;
          do
          {
            (**v22)(v22, 0);
            v22 += 45;
            --v24;
          }
          while ( v24 );
          --v23;
        }
        while ( v23 );
        switch ( *(_DWORD *)(this + 121116) )
        {
          case 0:
            v25 = (const char **)sub_43EBB0((_DWORD *)(this + 113844), &v70, *(_DWORD *)(this + 592));
            v26 = *v25;
            v62 = v25[1];
            break;
          case 1:
            v27 = (const char **)sub_43EBB0((_DWORD *)(this + 115056), &v71, *(_DWORD *)(this + 592));
            v26 = *v27;
            v62 = v27[1];
            break;
          case 2:
            v28 = (const char **)sub_43EBB0((_DWORD *)(this + 116268), &v72, *(_DWORD *)(this + 592));
            v26 = *v28;
            v62 = v28[1];
            break;
          case 3:
            v29 = (const char **)sub_43EBB0((_DWORD *)(this + 117480), &v67, *(_DWORD *)(this + 592));
            v26 = *v29;
            v62 = v29[1];
            break;
          case 4:
            v30 = (const char **)sub_43EBB0((_DWORD *)(this + 118692), &v68, *(_DWORD *)(this + 592));
            v26 = *v30;
            v62 = v30[1];
            break;
          case 5:
            v31 = (const char **)sub_43EBB0((_DWORD *)(this + 119904), &v69, *(_DWORD *)(this + 592));
            v26 = *v31;
            v62 = v31[1];
            switch ( *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + 612) )
            {
              case 7:
                v32 = 0;
                v33 = (void (***)(_DWORD, int))(this + 107268);
                do
                {
                  if ( *(_BYTE *)(this + v32 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v32 + 614) )
                  {
                    (**v33)(v33, 1);
                  }
                  ++v32;
                  v33 += 225;
                }
                while ( v32 < 5 );
                break;
              case 8:
                v34 = 0;
                v35 = (void (***)(_DWORD, int))(this + 107808);
                do
                {
                  if ( *(_BYTE *)(this + v34 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v34 + 614) )
                  {
                    (**v35)(v35, 1);
                  }
                  ++v34;
                  v35 += 225;
                }
                while ( v34 < 5 );
                break;
              case 9:
                v36 = 0;
                v37 = (void (***)(_DWORD, int))(this + 107988);
                do
                {
                  if ( *(_BYTE *)(this + v36 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v36 + 614) )
                  {
                    (**v37)(v37, 1);
                  }
                  ++v36;
                  v37 += 225;
                }
                while ( v36 < 5 );
                break;
              case 0xA:
                v38 = 0;
                v39 = (void (***)(_DWORD, int))(this + 107628);
                do
                {
                  if ( *(_BYTE *)(this + v38 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v38 + 614) )
                  {
                    (**v39)(v39, 1);
                  }
                  ++v38;
                  v39 += 225;
                }
                while ( v38 < 5 );
                break;
              case 0xB:
                v40 = 0;
                v41 = (void (***)(_DWORD, int))(this + 107448);
                do
                {
                  if ( *(_BYTE *)(this + v40 + 102440)
                    && *(_BYTE *)(*(_DWORD *)(this + 12 * *(_DWORD *)(this + 592) + 64780) + v40 + 614) )
                  {
                    (**v41)(v41, 1);
                  }
                  ++v40;
                  v41 += 225;
                }
                while ( v40 < 5 );
                break;
              default:
                goto LABEL_95;
            }
            break;
          default:
            v26 = v61;
            break;
        }
LABEL_95:
        v42 = *(_DWORD *)(this + 121852);
        v43 = (int *)(this + 121124);
        v44 = v62 - 4;
        v45 = v26 + 162;
        if ( v42 )
        {
          if ( v42 == 1 )
          {
            v46 = *(_DWORD *)(this + 121844);
            *(_DWORD *)(this + 121144) = v44;
            *(_DWORD *)(this + 121140) = v45;
            *(_DWORD *)(this + 121148) = &v45[v46];
            *(_DWORD *)(this + 121152) = &v44[*(_DWORD *)(this + 121848)];
            (_DWORD *->GetRect()(this + 121500), (_DWORD *)(this + 121140));
            v47 = *(_DWORD *)(this + 121148) + *(_DWORD *)(this + 121856);
            v48 = *(_DWORD *)(this + 121844);
            *(_DWORD *)(this + 121128) = *(_DWORD *)(this + 121144);
            v49 = *(_DWORD *)(this + 121152);
            *v43 = v47;
            *(_DWORD *)(this + 121136) = v49;
            *(_DWORD *)(this + 121132) = v48 + v47;
            (_DWORD *->GetRect()(this + 121156), (_DWORD *)(this + 121124));
          }
        }
        else
        {
          v50 = *(_DWORD *)(this + 121844);
          v51 = *(_DWORD *)(this + 121848);
          *(_DWORD *)(this + 121128) = v44;
          *v43 = (int)v45;
          *(_DWORD *)(this + 121132) = &v45[v50];
          *(_DWORD *)(this + 121136) = &v44[v51];
          (_DWORD *->GetRect()(this + 121156), (_DWORD *)(this + 121124));
          v52 = *v43;
          v53 = *(_DWORD *)(this + 121136) + *(_DWORD *)(this + 121856);
          *(_DWORD *)(this + 121144) = v53;
          *(_DWORD *)(this + 121140) = v52;
          *(_DWORD *)(this + 121148) = *(_DWORD *)(this + 121132);
          *(_DWORD *)(this + 121152) = *(_DWORD *)(this + 121848) + v53;
          (_DWORD *->GetRect()(this + 121500), (_DWORD *)(this + 121140));
        }
        (**(void (***)(int, int))(this + 121156))(this + 121156, 1);
        (**(void (***)(int, int))(this + 121500))(this + 121500, 1);
        v54 = 299 * *(_DWORD *)(this + 121116) + *(_DWORD *)(this + 592);
        v55 = *(_DWORD *)(this + 4 * v54 + 32452);
        if ( v55 > 0 )
        {
          sub_445E50((_DWORD *)(this + 121156), v55 != *(_DWORD *)(this + 4 * v54 + 39628));
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
        v56 = HIWORD(a4);
        if ( (unsigned __int16)a4 > *(int *)(this + 104748)
          && (unsigned __int16)a4 < *(int *)(this + 104756)
          && v56 > *(_DWORD *)(this + 104752)
          && v56 < *(_DWORD *)(this + 104760) )
        {
          (_DWORD *->SetEnable()(this + 104596), MEMORY[0xC10D38], 0);
          (**(void (***)(int, _DWORD))(this + 101420))(this + 101420, 0);
        }
      }
      result = 1;
      break;
    default:
      result = a2->SendMessage(a3, a4);
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

  (_DWORD *->UIListBox()this);
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
  (_DWORD *->ctor_D830()(this + 162880));
  (_BYTE *->UIFrameWnd()(this + 162964));
  (_BYTE *->UIFrameWnd()(this + 163116));
  (_BYTE *->UIFrameWnd()(this + 163268));
  (_BYTE *->UIFrameWnd()(this + 163420));
  (_BYTE *->UIFrameWnd()(this + 163572));
  (_DWORD *->ctor_A160()(this + 163724));
  (_BYTE *->UIFrameWnd()(this + 163888));
  (_BYTE *->UIFrameWnd()(this + 164040));
  (_BYTE *->UIFrameWnd()(this + 164192));
  (_BYTE *->UIFrameWnd()(this + 164344));
  (_BYTE *->UIFrameWnd()(this + 164496));
  (_BYTE *->UIFrameWnd()(this + 164648));
  (_BYTE *->UIFrameWnd()(this + 164800));
  `eh vector constructor iterator'(
    (void *)(this + 164952),
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 166472));
  `eh vector constructor iterator'(
    (void *)(this + 166624),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (char *->UpdateKeyCtrl()(this + 167232));
  (_DWORD *->_UIScene()(this + 168440));
  (_DWORD *->_UIScene()(this + 168784));
  (_DWORD *->_UIScene()(this + 169128));
  UIItem::Refresh(this + 169472);
  UIItem::Refresh(this + 170840);
  UIItem::Refresh(this + 172208);
  (_DWORD *->ctor_9030()(this + 173576));
  *(_BYTE *)(this + 173892) = 0;
  *(_DWORD *)(this + 173888) = 0;
  *(_DWORD *)(this + 173884) = 0;
  *(_BYTE *)(this + 173904) = 0;
  *(_DWORD *)(this + 173900) = 0;
  *(_DWORD *)(this + 173896) = 0;
  `eh vector constructor iterator'((void *)(this + 173948), 0x248u, 60, sub_4B4690, sub_4B47E0);
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
  *(_DWORD *)this = &off_56B820;
  `eh vector destructor iterator'((char *)this + 173948, 0x248u, 60, sub_4B47E0);
  (UIWnd *->ctor_9130()((char *)this + 173576));
  (char *->UIItem()this + 172208);
  (char *->UIItem()this + 170840);
  (char *->UIItem()this + 169472);
  (UIWnd *->Destroy2()((char *)this + 169128));
  (UIWnd *->Destroy2()((char *)this + 168784));
  (UIWnd *->Destroy2()this + 4211);
  (UIWnd *->DeleteRow()((char *)this + 167232));
  `eh vector destructor iterator'((char *)this + 166624, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 166472));
  `eh vector destructor iterator'(
    (char *)this + 164952,
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()this + 4120);
  (UIWnd *->_UIFrameWnd()((char *)this + 164648));
  (UIWnd *->_UIFrameWnd()((char *)this + 164496));
  (UIWnd *->_UIFrameWnd()((char *)this + 164344));
  (UIWnd *->_UIFrameWnd()((char *)this + 164192));
  (UIWnd *->_UIFrameWnd()this + 4101);
  (UIWnd *->_UIFrameWnd()((char *)this + 163888));
  (UIWnd *->ctor_A1F0()((char *)this + 163724));
  (UIWnd *->_UIFrameWnd()((char *)this + 163572));
  (UIWnd *->_UIFrameWnd()((char *)this + 163420));
  (UIWnd *->_UIFrameWnd()((char *)this + 163268));
  (UIWnd *->_UIFrameWnd()((char *)this + 163116));
  (UIWnd *->_UIFrameWnd()((char *)this + 162964));
  (UIWnd *->ctor_D880()this + 4072);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x0047BBF0
int UIWnd::ctor_BBF0(int _this)
{
  (_DWORD *->UIListBox()this);
  (_BYTE *->UIFrameWnd()(this + 128));
  (_BYTE *->UIFrameWnd()(this + 280));
  `eh vector constructor iterator'(
    (void *)(this + 432),
    0x98u,
    3,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_DWORD *->_UIScene()(this + 888));
  (_DWORD *->_UIScene()(this + 1232));
  (_DWORD *->_UIScene()(this + 1576));
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
  *(_DWORD *)this = &off_56B850;
  sub_47BDF0();
  sub_44B890((char *)this + 1920);
  (UIWnd *->Destroy2()((char *)this + 1576));
  (UIWnd *->Destroy2()((char *)this + 1232));
  (UIWnd *->Destroy2()((char *)this + 888));
  `eh vector destructor iterator'((char *)this + 432, 0x98u, 3, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()this + 7);
  (UIWnd *->_UIFrameWnd()((char *)this + 128));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x0047E5C0
int UIWnd::ctor_E5C0(int _this)
{
  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  *(_BYTE *)(this + 361) = 0;
  *(_DWORD *)(this + 364) = 0;
  (_BYTE *->UIFrameWnd()(this + 368));
  (_BYTE *->UIFrameWnd()(this + 520));
  (_BYTE *->UIFrameWnd()(this + 672));
  (_BYTE *->UIFrameWnd()(this + 824));
  (_BYTE *->UIFrameWnd()(this + 976));
  (_DWORD *->_UIScene()(this + 1128));
  (_DWORD *->_UIScene()(this + 1472));
  (_DWORD *->_UIScene()(this + 1816));
  (_DWORD *->_UIScene()(this + 2160));
  (_DWORD *->_UIScene()(this + 2504));
  (_DWORD *->_UIScene()(this + 2848));
  (_DWORD *->_UIScene()(this + 3192));
  (_DWORD *->_UIScene()(this + 3536));
  (_DWORD *->_UIScene()(this + 3880));
  (_BYTE *->UIFrameWnd()(this + 4224));
  (_BYTE *->UIFrameWnd()(this + 4392));
  (_BYTE *->UIFrameWnd()(this + 4544));
  `eh vector constructor iterator'((void *)(this + 4696), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 79448), 0x248u, 128, sub_4B4690, sub_4B47E0);
  (_DWORD *->ctor_9030()(this + 154340));
  (_DWORD *->ctor_9030()(this + 154648));
  (_BYTE *->UIFrameWnd()(this + 154956));
  (_BYTE *->UIFrameWnd()(this + 155108));
  (_BYTE *->UIFrameWnd()(this + 155260));
  `eh vector constructor iterator'(
    (void *)(this + 155412),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 156172),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 156932),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 157604));
  (_BYTE *->UIFrameWnd()(this + 157756));
  (_DWORD *->_UIScene()(this + 157908));
  (_DWORD *->_UIScene()(this + 158252));
  (char *->UIStatic()(this + 158596));
  (char *->UIStatic()(this + 158844));
  (char *->UIStatic()(this + 159092));
  (char *->UIStatic()(this + 159340));
  (char *->UIStatic()(this + 159588));
  (char *->UIStatic()(this + 159836));
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
  *(_DWORD *)this = &off_56B90C;
  sub_47F410();
  UIWnd::~UIWnd((UIWnd *)((char *)this + 159836));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 159588));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 159340));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 159092));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 158844));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 158596));
  (UIWnd *->Destroy2()((char *)this + 158252));
  (UIWnd *->Destroy2()((char *)this + 157908));
  (UIWnd *->_UIFrameWnd()((char *)this + 157756));
  (UIWnd *->_UIFrameWnd()((char *)this + 157604));
  `eh vector destructor iterator'((char *)this + 156932, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 156172, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 155412, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 155260));
  (UIWnd *->_UIFrameWnd()((char *)this + 155108));
  (UIWnd *->_UIFrameWnd()((char *)this + 154956));
  (UIWnd *->ctor_9130()((char *)this + 154648));
  (UIWnd *->ctor_9130()((char *)this + 154340));
  `eh vector destructor iterator'((char *)this + 79448, 0x248u, 128, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4696, 0x248u, 128, sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 4544));
  (UIWnd *->_UIFrameWnd()((char *)this + 4392));
  (UIWnd *->_UIFrameWnd()((char *)this + 4224));
  (UIWnd *->Destroy2()this + 97);
  (UIWnd *->Destroy2()((char *)this + 3536));
  (UIWnd *->Destroy2()((char *)this + 3192));
  (UIWnd *->Destroy2()((char *)this + 2848));
  (UIWnd *->Destroy2()((char *)this + 2504));
  (UIWnd *->Destroy2()this + 54);
  (UIWnd *->Destroy2()((char *)this + 1816));
  (UIWnd *->Destroy2()((char *)this + 1472));
  (UIWnd *->Destroy2()((char *)this + 1128));
  (UIWnd *->_UIFrameWnd()((char *)this + 976));
  (UIWnd *->_UIFrameWnd()((char *)this + 824));
  (UIWnd *->_UIFrameWnd()((char *)this + 672));
  (UIWnd *->_UIFrameWnd()this + 13);
  (UIWnd *->_UIFrameWnd()((char *)this + 368));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00482ED0
int UIWnd::ctor_2ED0(int _this)
{
  gbVec3D *v2; // edi
  int v4; // [esp+10h] [ebp-14h]

  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  (_BYTE *->UIFrameWnd()(this + 368));
  (_BYTE *->UIFrameWnd()(this + 520));
  (_BYTE *->UIFrameWnd()(this + 672));
  (_BYTE *->UIFrameWnd()(this + 824));
  (_BYTE *->UIFrameWnd()(this + 976));
  (_BYTE *->UIFrameWnd()(this + 1128));
  (_DWORD *->_UIScene()(this + 1280));
  (_DWORD *->_UIScene()(this + 1624));
  (_DWORD *->_UIScene()(this + 1968));
  (_DWORD *->_UIScene()(this + 2312));
  (_DWORD *->_UIScene()(this + 2656));
  (_DWORD *->_UIScene()(this + 3000));
  (_DWORD *->_UIScene()(this + 3344));
  (_DWORD *->_UIScene()(this + 3688));
  (_DWORD *->_UIScene()(this + 4032));
  (_BYTE *->UIFrameWnd()(this + 4376));
  (_BYTE *->UIFrameWnd()(this + 4544));
  (_BYTE *->UIFrameWnd()(this + 4696));
  (_BYTE *->UIFrameWnd()(this + 4848));
  `eh vector constructor iterator'((void *)(this + 5000), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 79752), 0x248u, 128, sub_4B4690, sub_4B47E0);
  memset((void *)(this + 154644), 0, 0x1Cu);
  *(_WORD *)(this + 154672) = 0;
  *(_DWORD *)(this + 154674) = 117901063;
  *(_BYTE *)(this + 154678) = 7;
  (_BYTE *->UIFrameWnd()(this + 154696));
  `eh vector constructor iterator'(
    (void *)(this + 154848),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (void *)(this + 156588),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 157348),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_DWORD *)(this + 158188) = 0;
  UIItem::Refresh(this + 158192);
  v2 = (gbVec3D *)(this + 159592);
  v4 = 6;
  do
  {
    gbVec3D::`default constructor closure'(v2);
    v2 = (gbVec3D *)((char *)v2 + 12);
    --v4;
  }
  while ( v4 );
  (_DWORD *->Update()(this + 159664));
  `eh vector constructor iterator'(
    (void *)(this + 159816),
    0x98u,
    5,
    (void (*)(void *))ObjectCamera::Update,
    (void (*)(void *))Object3D::Object3D);
  `eh vector constructor iterator'(
    (void *)(this + 160608),
    0x98u,
    6,
    (void (*)(void *))ObjectCamera::Update,
    (void (*)(void *))Object3D::Object3D);
  `eh vector constructor iterator'(
    (void *)(this + 161520),
    0x798u,
    5,
    sub_483280,
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
  void **v2; // ecx
  void *v3; // edi

  *(_DWORD *)this = &off_56BA30;
  v2 = (void **)*((_DWORD *)this + 39892);
  if ( v2 )
  {
    v2->Destroy();
    v3 = (void *)*((_DWORD *)this + 39892);
    if ( v3 )
    {
      ObjectCamera::GetCameraDirect();
      operator delete(v3);
    }
    *((_DWORD *)this + 39892) = 0;
  }
  `eh vector destructor iterator'((char *)this + 161520, 0x798u, 5, (void (*)(void *))sub_483300);
  `eh vector destructor iterator'((char *)this + 160608, 0x98u, 6, (void (*)(void *))Object3D::Object3D);
  `eh vector destructor iterator'((char *)this + 159816, 0x98u, 5, (void (*)(void *))Object3D::Object3D);
  (_DWORD *->Object3D()this + 39916);
  (char *->UIItem()this + 158192);
  `eh vector destructor iterator'((char *)this + 157348, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 156588, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 154848, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  (UIWnd *->_UIFrameWnd()((char *)this + 154696));
  `eh vector destructor iterator'((char *)this + 79752, 0x248u, 128, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 5000, 0x248u, 128, sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 4848));
  (UIWnd *->_UIFrameWnd()((char *)this + 4696));
  (UIWnd *->_UIFrameWnd()((char *)this + 4544));
  (UIWnd *->_UIFrameWnd()((char *)this + 4376));
  (UIWnd *->Destroy2()((char *)this + 4032));
  (UIWnd *->Destroy2()((char *)this + 3688));
  (UIWnd *->Destroy2()((char *)this + 3344));
  (UIWnd *->Destroy2()this + 75);
  (UIWnd *->Destroy2()((char *)this + 2656));
  (UIWnd *->Destroy2()((char *)this + 2312));
  (UIWnd *->Destroy2()((char *)this + 1968));
  (UIWnd *->Destroy2()((char *)this + 1624));
  (UIWnd *->Destroy2()this + 32);
  (UIWnd *->_UIFrameWnd()((char *)this + 1128));
  (UIWnd *->_UIFrameWnd()((char *)this + 976));
  (UIWnd *->_UIFrameWnd()((char *)this + 824));
  (UIWnd *->_UIFrameWnd()((char *)this + 672));
  (UIWnd *->_UIFrameWnd()this + 13);
  (UIWnd *->_UIFrameWnd()((char *)this + 368));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x004867F0
int UIWnd::ctor_67F0(int _this)
{
  int v2; // edi
  int v3; // ebp

  (_DWORD *->UIListBox()this);
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
    ArraySort(v2, 12, 99, (int (*)(int))sub_486CE0);
    v2 += 1192;
    --v3;
  }
  while ( v3 );
  *(_DWORD *)(this + 51032) = 0;
  (_BYTE *->UIFrameWnd()(this + 51036));
  (_BYTE *->UIFrameWnd()(this + 51188));
  (_BYTE *->UIFrameWnd()(this + 51340));
  (_BYTE *->UIFrameWnd()(this + 51492));
  (_BYTE *->UIFrameWnd()(this + 51644));
  (_BYTE *->UIFrameWnd()(this + 51796));
  (_DWORD *->_UIScene()(this + 51948));
  (_DWORD *->_UIScene()(this + 52292));
  (_DWORD *->_UIScene()(this + 52636));
  (_DWORD *->_UIScene()(this + 52980));
  (_DWORD *->_UIScene()(this + 53324));
  (_DWORD *->_UIScene()(this + 53668));
  (_DWORD *->_UIScene()(this + 54012));
  (_DWORD *->_UIScene()(this + 54356));
  (_DWORD *->_UIScene()(this + 54700));
  (_BYTE *->UIFrameWnd()(this + 55044));
  `eh vector constructor iterator'(
    (void *)(this + 55228),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 55836));
  (_BYTE *->UIFrameWnd()(this + 55988));
  `eh vector constructor iterator'((void *)(this + 56140), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 130892), 0x248u, 128, sub_4B4690, sub_4B47E0);
  *(_DWORD *)(this + 205784) = 0;
  UIItem::Refresh(this + 205788);
  UIItem::Refresh(this + 207156);
  UIItem::Refresh(this + 208524);
  `eh vector constructor iterator'(
    (void *)(this + 209896),
    0x34u,
    5,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  (_DWORD *->ctor_D830()(this + 210236));
  (_BYTE *->UIFrameWnd()(this + 210320));
  `eh vector constructor iterator'(
    (void *)(this + 210472),
    0x98u,
    9,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 211840));
  (_BYTE *->UIFrameWnd()(this + 211992));
  (_BYTE *->UIFrameWnd()(this + 212144));
  (_BYTE *->UIFrameWnd()(this + 212296));
  (_BYTE *->UIFrameWnd()(this + 212448));
  `eh vector constructor iterator'(
    (void *)(this + 212600),
    0x131Cu,
    5,
    sub_486D20,
    (void (*)(void *))sub_486EF0);
  `eh vector constructor iterator'(
    (void *)(this + 237060),
    0x158u,
    8,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  (char *->UpdateKeyCtrl()(this + 239812));
  (char *->UpdateKeyCtrl()(this + 241020));
  (char *->UpdateKeyCtrl()(this + 242228));
  (char *->UpdateKeyCtrl()(this + 243436));
  (char *->UpdateKeyCtrl()(this + 244644));
  (char *->UpdateKeyCtrl()(this + 245852));
  (char *->UpdateKeyCtrl()(this + 247060));
  (char *->UpdateKeyCtrl()(this + 248268));
  (_DWORD *->ctor_9030()(this + 249476));
  `eh vector constructor iterator'((void *)(this + 249784), 0x248u, 98, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 307040), 0x248u, 40, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 330400), 0x248u, 40, sub_4B4690, sub_4B47E0);
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
  *(_DWORD *)this = &off_56C590;
  `eh vector destructor iterator'((char *)this + 330400, 0x248u, 40, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 307040, 0x248u, 40, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 249784, 0x248u, 98, sub_4B47E0);
  (UIWnd *->ctor_9130()((char *)this + 249476));
  (UIWnd *->DeleteRow()((char *)this + 248268));
  (UIWnd *->DeleteRow()((char *)this + 247060));
  (UIWnd *->DeleteRow()((char *)this + 245852));
  (UIWnd *->DeleteRow()((char *)this + 244644));
  (UIWnd *->DeleteRow()((char *)this + 243436));
  (UIWnd *->DeleteRow()((char *)this + 242228));
  (UIWnd *->DeleteRow()((char *)this + 241020));
  (UIWnd *->DeleteRow()((char *)this + 239812));
  `eh vector destructor iterator'((char *)this + 237060, 0x158u, 8, (void (*)(void *))UIScene::Destroy2);
  `eh vector destructor iterator'((char *)this + 212600, 0x131Cu, 5, (void (*)(void *))sub_486EF0);
  (UIWnd *->_UIFrameWnd()((char *)this + 212448));
  (UIWnd *->_UIFrameWnd()((char *)this + 212296));
  (UIWnd *->_UIFrameWnd()((char *)this + 212144));
  (UIWnd *->_UIFrameWnd()((char *)this + 211992));
  (UIWnd *->_UIFrameWnd()this + 5296);
  `eh vector destructor iterator'((char *)this + 210472, 0x98u, 9, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()this + 5258);
  (UIWnd *->ctor_D880()((char *)this + 210236));
  `eh vector destructor iterator'((char *)this + 209896, 0x34u, 5, (void (*)(void *))nullsub_1);
  (char *->UIItem()this + 208524);
  (char *->UIItem()this + 207156);
  (char *->UIItem()this + 205788);
  `eh vector destructor iterator'((char *)this + 130892, 0x248u, 128, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 56140, 0x248u, 128, sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 55988));
  (UIWnd *->_UIFrameWnd()((char *)this + 55836));
  `eh vector destructor iterator'((char *)this + 55228, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 55044));
  (UIWnd *->Destroy2()((char *)this + 54700));
  (UIWnd *->Destroy2()((char *)this + 54356));
  (UIWnd *->Destroy2()((char *)this + 54012));
  (UIWnd *->Destroy2()((char *)this + 53668));
  (UIWnd *->Destroy2()((char *)this + 53324));
  (UIWnd *->Destroy2()((char *)this + 52980));
  (UIWnd *->Destroy2()((char *)this + 52636));
  (UIWnd *->Destroy2()((char *)this + 52292));
  (UIWnd *->Destroy2()((char *)this + 51948));
  (UIWnd *->_UIFrameWnd()((char *)this + 51796));
  (UIWnd *->_UIFrameWnd()((char *)this + 51644));
  (UIWnd *->_UIFrameWnd()((char *)this + 51492));
  (UIWnd *->_UIFrameWnd()((char *)this + 51340));
  (UIWnd *->_UIFrameWnd()((char *)this + 51188));
  (UIWnd *->_UIFrameWnd()((char *)this + 51036));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x004909F0
int UIWnd::ctor_9F0(int _this)
{
  _DWORD *v2; // eax
  int v3; // ebp
  _DWORD *v5; // [esp+10h] [ebp-18h]
  int v6; // [esp+14h] [ebp-14h]

  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  *(_BYTE *)(this + 367) = 0;
  *(_DWORD *)(this + 368) = 0;
  *(_DWORD *)(this + 372) = 0;
  *(_DWORD *)(this + 376) = 7;
  *(_DWORD *)(this + 380) = 0;
  (_BYTE *->UIFrameWnd()(this + 384));
  (_BYTE *->UIFrameWnd()(this + 536));
  (_BYTE *->UIFrameWnd()(this + 688));
  (_BYTE *->UIFrameWnd()(this + 840));
  (_BYTE *->UIFrameWnd()(this + 992));
  (_BYTE *->UIFrameWnd()(this + 1144));
  (_DWORD *->_UIScene()(this + 1296));
  (_DWORD *->_UIScene()(this + 1640));
  (_DWORD *->_UIScene()(this + 1984));
  (_DWORD *->_UIScene()(this + 2328));
  (_DWORD *->_UIScene()(this + 2672));
  (_DWORD *->_UIScene()(this + 3016));
  (_DWORD *->_UIScene()(this + 3360));
  (_DWORD *->_UIScene()(this + 3704));
  (_DWORD *->_UIScene()(this + 4048));
  (_BYTE *->UIFrameWnd()(this + 4392));
  (_BYTE *->UIFrameWnd()(this + 4560));
  (_BYTE *->UIFrameWnd()(this + 4712));
  `eh vector constructor iterator'((void *)(this + 4864), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 79616), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'(
    (void *)(this + 154508),
    0x26FCu,
    5,
    sub_490E90,
    (void (*)(void *))sub_4910B0);
  (_BYTE *->UIFrameWnd()(this + 204424));
  (_BYTE *->UIFrameWnd()(this + 204576));
  (_BYTE *->UIFrameWnd()(this + 204728));
  (_BYTE *->UIFrameWnd()(this + 204880));
  (_BYTE *->UIFrameWnd()(this + 205032));
  v2 = (_DWORD *)(this + 205200);
  v5 = (_DWORD *)(this + 205200);
  v6 = 5;
  v3 = this + 205206;
  while ( 1 )
  {
    *v2 = 0;
    *(_WORD *)(v3 - 2) = 0;
    lstrcpyA((LPSTR)v3, MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v3 + 512), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v3 + 542), MEMORY[0xC10D38]);
    lstrcpyA((LPSTR)(v3 + 594), MEMORY[0xC10D38]);
    memset((void *)(v3 + 630), 0, 0x30u);
    *(_DWORD *)(v3 + 774) = 0;
    v3 += 852;
    v5 += 213;
    if ( !--v6 )
      break;
    v2 = v5;
  }
  UIItem::Refresh(this + 209460);
  `eh vector constructor iterator'(
    (void *)(this + 210828),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  (_BYTE *->UIFrameWnd()(this + 212548));
  (_BYTE *->UIFrameWnd()(this + 212700));
  (_BYTE *->UIFrameWnd()(this + 212852));
  (_BYTE *->UIFrameWnd()(this + 213004));
  (_BYTE *->UIFrameWnd()(this + 213156));
  (_BYTE *->UIFrameWnd()(this + 213308));
  `eh vector constructor iterator'(
    (void *)(this + 213476),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  *(_DWORD *)(this + 215196) = -1;
  (_DWORD *->ctor_D830()(this + 215200));
  (_BYTE *->UIFrameWnd()(this + 215284));
  `eh vector constructor iterator'(
    (void *)(this + 215436),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 217260));
  (char *->UpdateKeyCtrl()(this + 217412));
  *(_DWORD *)(this + 218620) = -1;
  (_DWORD *->_UIScene()(this + 218640));
  (_DWORD *->_UIScene()(this + 218984));
  (_DWORD *->_UIScene()(this + 219328));
  *(_DWORD *)(this + 219672) = -1;
  (_DWORD *->ctor_9030()(this + 219676));
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
  *(_DWORD *)this = &off_56D618;
  (UIWnd *->ctor_9130()((char *)this + 219676));
  (UIWnd *->Destroy2()((char *)this + 219328));
  (UIWnd *->Destroy2()((char *)this + 218984));
  (UIWnd *->Destroy2()this + 5466);
  (UIWnd *->DeleteRow()((char *)this + 217412));
  (UIWnd *->_UIFrameWnd()((char *)this + 217260));
  `eh vector destructor iterator'(
    (char *)this + 215436,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 215284));
  (UIWnd *->ctor_D880()this + 5380);
  `eh vector destructor iterator'((char *)this + 213476, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  (UIWnd *->_UIFrameWnd()((char *)this + 213308));
  (UIWnd *->_UIFrameWnd()((char *)this + 213156));
  (UIWnd *->_UIFrameWnd()((char *)this + 213004));
  (UIWnd *->_UIFrameWnd()((char *)this + 212852));
  (UIWnd *->_UIFrameWnd()((char *)this + 212700));
  (UIWnd *->_UIFrameWnd()((char *)this + 212548));
  `eh vector destructor iterator'((char *)this + 210828, 0x158u, 5, (void (*)(void *))UIScene::Destroy2);
  (char *->UIItem()this + 209460);
  (UIWnd *->_UIFrameWnd()((char *)this + 205032));
  (UIWnd *->_UIFrameWnd()this + 5122);
  (UIWnd *->_UIFrameWnd()((char *)this + 204728));
  (UIWnd *->_UIFrameWnd()((char *)this + 204576));
  (UIWnd *->_UIFrameWnd()((char *)this + 204424));
  `eh vector destructor iterator'((char *)this + 154508, 0x26FCu, 5, (void (*)(void *))sub_4910B0);
  `eh vector destructor iterator'((char *)this + 79616, 0x248u, 128, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4864, 0x248u, 128, sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 4712));
  (UIWnd *->_UIFrameWnd()this + 114);
  (UIWnd *->_UIFrameWnd()((char *)this + 4392));
  (UIWnd *->Destroy2()((char *)this + 4048));
  (UIWnd *->Destroy2()((char *)this + 3704));
  (UIWnd *->Destroy2()this + 84);
  (UIWnd *->Destroy2()((char *)this + 3016));
  (UIWnd *->Destroy2()((char *)this + 2672));
  (UIWnd *->Destroy2()((char *)this + 2328));
  (UIWnd *->Destroy2()((char *)this + 1984));
  (UIWnd *->Destroy2()this + 41);
  (UIWnd *->Destroy2()((char *)this + 1296));
  (UIWnd *->_UIFrameWnd()((char *)this + 1144));
  (UIWnd *->_UIFrameWnd()((char *)this + 992));
  (UIWnd *->_UIFrameWnd()this + 21);
  (UIWnd *->_UIFrameWnd()((char *)this + 688));
  (UIWnd *->_UIFrameWnd()((char *)this + 536));
  (UIWnd *->_UIFrameWnd()((char *)this + 384));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00498820
int UIWnd::ctor_8820(int _this)
{
  (_DWORD *->UIListBox()this);
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
  (_BYTE *->UIFrameWnd()(this + 660));
  (_BYTE *->UIFrameWnd()(this + 812));
  (_BYTE *->UIFrameWnd()(this + 964));
  (_BYTE *->UIFrameWnd()(this + 1116));
  (_BYTE *->UIFrameWnd()(this + 1268));
  (_BYTE *->UIFrameWnd()(this + 1420));
  (_DWORD *->_UIScene()(this + 1572));
  (_DWORD *->_UIScene()(this + 1916));
  (_DWORD *->_UIScene()(this + 2260));
  (_DWORD *->_UIScene()(this + 2604));
  (_DWORD *->_UIScene()(this + 2948));
  (_DWORD *->_UIScene()(this + 3292));
  (_DWORD *->_UIScene()(this + 3636));
  (_DWORD *->_UIScene()(this + 3980));
  (_DWORD *->_UIScene()(this + 4324));
  (_BYTE *->UIFrameWnd()(this + 4668));
  (_BYTE *->UIFrameWnd()(this + 4836));
  (_BYTE *->UIFrameWnd()(this + 4988));
  `eh vector constructor iterator'((void *)(this + 5140), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 79892), 0x248u, 128, sub_4B4690, sub_4B47E0);
  UIItem::Refresh(this + 154784);
  `eh vector constructor iterator'(
    (void *)(this + 156152),
    0x131Cu,
    5,
    sub_498C90,
    (void (*)(void *))sub_498E60);
  (_BYTE *->UIFrameWnd()(this + 180612));
  (_BYTE *->UIFrameWnd()(this + 180764));
  (_BYTE *->UIFrameWnd()(this + 180916));
  (_BYTE *->UIFrameWnd()(this + 181084));
  (_BYTE *->UIFrameWnd()(this + 181236));
  `eh vector constructor iterator'(
    (void *)(this + 181388),
    0x158u,
    6,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (void *)(this + 183452),
    0xF8u,
    6,
    (void (*)(void *))UIStatic::UIStatic,
    (void (*)(void *))UIWnd::~UIWnd);
  (_BYTE *->UIFrameWnd()(this + 184940));
  (_DWORD *->ctor_D830()(this + 185092));
  (_BYTE *->UIFrameWnd()(this + 185176));
  `eh vector constructor iterator'(
    (void *)(this + 185328),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (char *->UpdateKeyCtrl()(this + 187152));
  (char *->UpdateKeyCtrl()(this + 188360));
  (char *->UpdateKeyCtrl()(this + 189568));
  (char *->UpdateKeyCtrl()(this + 190776));
  (char *->UpdateKeyCtrl()(this + 191984));
  (char *->UpdateKeyCtrl()(this + 193192));
  `eh vector constructor iterator'(
    (void *)(this + 194400),
    0x34u,
    5,
    (void (*)(void *))sub_45ADD0,
    (void (*)(void *))nullsub_1);
  (_DWORD *->_UIScene()(this + 194756));
  (_DWORD *->_UIScene()(this + 195100));
  (_DWORD *->_UIScene()(this + 195444));
  *(_DWORD *)(this + 195788) = -1;
  (_DWORD *->ctor_9030()(this + 195792));
  `eh vector constructor iterator'((void *)(this + 196100), 0x248u, 60, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 231140), 0x248u, 60, sub_4B4690, sub_4B47E0);
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
  *(_DWORD *)this = &off_56E170;
  `eh vector destructor iterator'((char *)this + 231140, 0x248u, 60, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 196100, 0x248u, 60, sub_4B47E0);
  (UIWnd *->ctor_9130()((char *)this + 195792));
  (UIWnd *->Destroy2()((char *)this + 195444));
  (UIWnd *->Destroy2()((char *)this + 195100));
  (UIWnd *->Destroy2()((char *)this + 194756));
  `eh vector destructor iterator'((char *)this + 194400, 0x34u, 5, (void (*)(void *))nullsub_1);
  (UIWnd *->DeleteRow()((char *)this + 193192));
  (UIWnd *->DeleteRow()((char *)this + 191984));
  (UIWnd *->DeleteRow()((char *)this + 190776));
  (UIWnd *->DeleteRow()((char *)this + 189568));
  (UIWnd *->DeleteRow()this + 4709);
  (UIWnd *->DeleteRow()((char *)this + 187152));
  `eh vector destructor iterator'(
    (char *)this + 185328,
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 185176));
  (UIWnd *->ctor_D880()((char *)this + 185092));
  (UIWnd *->_UIFrameWnd()((char *)this + 184940));
  `eh vector destructor iterator'((char *)this + 183452, 0xF8u, 6, (void (*)(void *))UIWnd::~UIWnd);
  `eh vector destructor iterator'((char *)this + 181388, 0x158u, 6, (void (*)(void *))UIScene::Destroy2);
  (UIWnd *->_UIFrameWnd()((char *)this + 181236));
  (UIWnd *->_UIFrameWnd()((char *)this + 181084));
  (UIWnd *->_UIFrameWnd()((char *)this + 180916));
  (UIWnd *->_UIFrameWnd()((char *)this + 180764));
  (UIWnd *->_UIFrameWnd()((char *)this + 180612));
  `eh vector destructor iterator'((char *)this + 156152, 0x131Cu, 5, (void (*)(void *))sub_498E60);
  (char *->UIItem()this + 154784);
  `eh vector destructor iterator'((char *)this + 79892, 0x248u, 128, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 5140, 0x248u, 128, sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 4988));
  (UIWnd *->_UIFrameWnd()((char *)this + 4836));
  (UIWnd *->_UIFrameWnd()((char *)this + 4668));
  (UIWnd *->Destroy2()((char *)this + 4324));
  (UIWnd *->Destroy2()((char *)this + 3980));
  (UIWnd *->Destroy2()((char *)this + 3636));
  (UIWnd *->Destroy2()((char *)this + 3292));
  (UIWnd *->Destroy2()((char *)this + 2948));
  (UIWnd *->Destroy2()((char *)this + 2604));
  (UIWnd *->Destroy2()((char *)this + 2260));
  (UIWnd *->Destroy2()((char *)this + 1916));
  (UIWnd *->Destroy2()((char *)this + 1572));
  (UIWnd *->_UIFrameWnd()((char *)this + 1420));
  (UIWnd *->_UIFrameWnd()((char *)this + 1268));
  (UIWnd *->_UIFrameWnd()((char *)this + 1116));
  (UIWnd *->_UIFrameWnd()((char *)this + 964));
  (UIWnd *->_UIFrameWnd()((char *)this + 812));
  (UIWnd *->_UIFrameWnd()((char *)this + 660));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x004A2450
void UIWnd::ctor_2450()
{
  *(_DWORD *)this = &off_56F040;
  sub_4A6600();
  (UIWnd *->_UIFrameWnd()((char *)this + 176092));
  (UIWnd *->Destroy2()((char *)this + 175696));
  `eh vector destructor iterator'((char *)this + 174856, 0x98u, 5, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 174688));
  `eh vector destructor iterator'((char *)this + 174080, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 155140, 0xECCu, 5, (void (*)(void *))sub_4A22E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 154972));
  (UIWnd *->_UIFrameWnd()((char *)this + 154820));
  (UIWnd *->_UIFrameWnd()((char *)this + 154668));
  (UIWnd *->_UIFrameWnd()((char *)this + 154516));
  `eh vector destructor iterator'((char *)this + 79608, 0x248u, 128, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4856, 0x248u, 128, sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 4704));
  (UIWnd *->_UIFrameWnd()((char *)this + 4552));
  (UIWnd *->_UIFrameWnd()((char *)this + 4384));
  (UIWnd *->Destroy2()this + 101);
  (UIWnd *->Destroy2()((char *)this + 3696));
  (UIWnd *->Destroy2()((char *)this + 3352));
  (UIWnd *->Destroy2()((char *)this + 3008));
  (UIWnd *->Destroy2()((char *)this + 2664));
  (UIWnd *->Destroy2()this + 58);
  (UIWnd *->Destroy2()((char *)this + 1976));
  (UIWnd *->Destroy2()((char *)this + 1632));
  (UIWnd *->Destroy2()((char *)this + 1288));
  (UIWnd *->_UIFrameWnd()((char *)this + 1136));
  (UIWnd *->_UIFrameWnd()((char *)this + 984));
  (UIWnd *->_UIFrameWnd()((char *)this + 832));
  (UIWnd *->_UIFrameWnd()this + 17);
  (UIWnd *->_UIFrameWnd()((char *)this + 528));
  (UIWnd *->_UIFrameWnd()((char *)this + 376));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x004A6F10
int UIWnd::ctor_6F10(int _this)
{
  _DWORD *v2; // eax
  CHAR *v3; // ebp
  bool v4; // zf
  _DWORD *v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]

  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 100) = 0;
  (_BYTE *->UIFrameWnd()(this + 364));
  v2 = (_DWORD *)(this + 548);
  v6 = (_DWORD *)(this + 548);
  v7 = 28;
  v3 = (CHAR *)(this + 608);
  while ( 1 )
  {
    *v2 = 0;
    lstrcpyA(v3 - 32, MEMORY[0xC10D38]);
    lstrcpyA(v3, MEMORY[0xC10D38]);
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
  (_BYTE *->UIFrameWnd()(this + 23456));
  (_BYTE *->UIFrameWnd()(this + 23608));
  (_BYTE *->UIFrameWnd()(this + 23760));
  (_BYTE *->UIFrameWnd()(this + 23912));
  (_BYTE *->UIFrameWnd()(this + 24064));
  (_DWORD *->_UIScene()(this + 24216));
  (_DWORD *->_UIScene()(this + 24560));
  (_DWORD *->_UIScene()(this + 24904));
  (_DWORD *->_UIScene()(this + 25248));
  (_DWORD *->_UIScene()(this + 25592));
  (_DWORD *->_UIScene()(this + 25936));
  (_DWORD *->_UIScene()(this + 26280));
  (_DWORD *->_UIScene()(this + 26624));
  (_DWORD *->_UIScene()(this + 26968));
  (_BYTE *->UIFrameWnd()(this + 27312));
  (_BYTE *->UIFrameWnd()(this + 27480));
  (_BYTE *->UIFrameWnd()(this + 27632));
  `eh vector constructor iterator'((void *)(this + 27784), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 102536), 0x248u, 128, sub_4B4690, sub_4B47E0);
  (_BYTE *->UIFrameWnd()(this + 177428));
  (_BYTE *->UIFrameWnd()(this + 177580));
  (_BYTE *->UIFrameWnd()(this + 177732));
  (_BYTE *->UIFrameWnd()(this + 177884));
  (_DWORD *->ctor_9030()(this + 178036));
  (_DWORD *->ctor_9030()(this + 178344));
  (_BYTE *->UIFrameWnd()(this + 178652));
  (_BYTE *->UIFrameWnd()(this + 178804));
  (_BYTE *->UIFrameWnd()(this + 178956));
  (_DWORD *->_UIScene()(this + 179108));
  `eh vector constructor iterator'(
    (void *)(this + 179508),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (void *)(this + 181228),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 181988),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  `eh vector constructor iterator'(
    (void *)(this + 183708),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 184468),
    0x98u,
    5,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_BYTE *)(this + 185228) = 1;
  (_DWORD *->_UIScene()(this + 185232));
  `eh vector constructor iterator'((void *)(this + 185576), 0x248u, 168, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 283704), 0x248u, 168, sub_4B4690, sub_4B47E0);
  (_DWORD *->_UIScene()(this + 381816));
  (_DWORD *->_UIScene()(this + 382160));
  sub_4A6730((char *)(this + 382744));
  *(_BYTE *)(this + 383180) = 0;
  *(_DWORD *)(this + 383176) = 0;
  *(_DWORD *)(this + 383172) = 0;
  *(_BYTE *)(this + 383200) = 0;
  *(_DWORD *)(this + 383196) = 0;
  *(_DWORD *)(this + 383192) = 0;
  (_DWORD *->ctor_D830()(this + 383300));
  (_DWORD *->ctor_D830()(this + 383384));
  `eh vector constructor iterator'(
    (void *)(this + 383468),
    0x158u,
    5,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  (_BYTE *->UIFrameWnd()(this + 385188));
  (_BYTE *->UIFrameWnd()(this + 385340));
  (_DWORD *->ctor_D830()(this + 385492));
  (_BYTE *->UIFrameWnd()(this + 385576));
  (_BYTE *->UIFrameWnd()(this + 385728));
  (_BYTE *->UIFrameWnd()(this + 385880));
  (_BYTE *->UIFrameWnd()(this + 386032));
  (_BYTE *->UIFrameWnd()(this + 386184));
  `eh vector constructor iterator'(
    (void *)(this + 386336),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 388160),
    0x98u,
    12,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (char *->UpdateKeyCtrl()(this + 389984));
  (char *->UpdateKeyCtrl()(this + 391192));
  (char *->UpdateKeyCtrl()(this + 392400));
  (char *->UpdateKeyCtrl()(this + 393608));
  (char *->UpdateKeyCtrl()(this + 394816));
  (char *->UpdateKeyCtrl()(this + 396024));
  (_BYTE *->UIFrameWnd()(this + 397248));
  (_BYTE *->UIFrameWnd()(this + 397400));
  (_BYTE *->UIFrameWnd()(this + 397552));
  (_BYTE *->UIFrameWnd()(this + 397720));
  (_DWORD *->ctor_D830()(this + 397872));
  (_DWORD *->_UIScene()(this + 397972));
  (_DWORD *->_UIScene()(this + 398316));
  (_DWORD *->_UIScene()(this + 398660));
  (_DWORD *->_UIScene()(this + 399004));
  (_DWORD *->_UIScene()(this + 399348));
  (_DWORD *->_UIScene()(this + 399692));
  *(_DWORD *)(this + 400036) = 0;
  sub_40CC60(this + 400040);
  UIItem::Refresh(this + 400080);
  UIItem::Refresh(this + 401448);
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
  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 360) = 0;
  *(_DWORD *)(this + 364) = 0;
  (_BYTE *->UIFrameWnd()(this + 368));
  (_BYTE *->UIFrameWnd()(this + 520));
  (_BYTE *->UIFrameWnd()(this + 672));
  (_BYTE *->UIFrameWnd()(this + 824));
  (_BYTE *->UIFrameWnd()(this + 976));
  (_BYTE *->UIFrameWnd()(this + 1128));
  (_DWORD *->_UIScene()(this + 1280));
  (_DWORD *->_UIScene()(this + 1624));
  (_DWORD *->_UIScene()(this + 1968));
  (_DWORD *->_UIScene()(this + 2312));
  (_DWORD *->_UIScene()(this + 2656));
  (_DWORD *->_UIScene()(this + 3000));
  (_DWORD *->_UIScene()(this + 3344));
  (_DWORD *->_UIScene()(this + 3688));
  (_DWORD *->_UIScene()(this + 4032));
  (_BYTE *->UIFrameWnd()(this + 4376));
  (_BYTE *->UIFrameWnd()(this + 4544));
  (_BYTE *->UIFrameWnd()(this + 4696));
  `eh vector constructor iterator'((void *)(this + 4848), 0x248u, 128, sub_4B4690, sub_4B47E0);
  `eh vector constructor iterator'((void *)(this + 79600), 0x248u, 128, sub_4B4690, sub_4B47E0);
  (_BYTE *->UIFrameWnd()(this + 154492));
  (_BYTE *->UIFrameWnd()(this + 154644));
  (char *->UIStatic()(this + 154796));
  (char *->UIStatic()(this + 155044));
  (_DWORD *->_UIScene()(this + 155292));
  (_DWORD *->_UIScene()(this + 155636));
  (_DWORD *->_UIScene()(this + 155980));
  `eh vector constructor iterator'(
    (void *)(this + 156360),
    0xDE8u,
    36,
    (void (*)(void *))sub_4549A0,
    (void (*)(void *))sub_454AA0);
  (_DWORD *->_UIScene()(this + 284520));
  (_DWORD *->_UIScene()(this + 284864));
  (_DWORD *->ctor_BCE0()(this + 285224));
  (_DWORD *->ctor_BCE0()(this + 285504));
  (_DWORD *->ctor_BCE0()(this + 285776));
  (_BYTE *->UIFrameWnd()(this + 286048));
  (_BYTE *->UIFrameWnd()(this + 286200));
  *(_DWORD *)(this + 286352) = 92;
  *(_DWORD *)(this + 286356) = 610;
  *(_DWORD *)(this + 286360) = 0;
  *(_DWORD *)(this + 286364) = 0;
  *(_DWORD *)(this + 286368) = 0;
  *(_DWORD *)(this + 286372) = 0;
  UIItem::Refresh(this + 286384);
  UIItem::Refresh(this + 287752);
  UIItem::Refresh(this + 289120);
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
  *(_DWORD *)this = &off_56F33C;
  UIItem::UIItem((int)this + 289120);
  UIItem::UIItem((int)this + 287752);
  UIItem::UIItem((int)this + 286384);
  (UIWnd *->_UIFrameWnd()this + 7155);
  (UIWnd *->_UIFrameWnd()((char *)this + 286048));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 285776));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 285504));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 285224));
  (UIWnd *->Destroy2()((char *)this + 284864));
  (UIWnd *->Destroy2()this + 7113);
  `eh vector destructor iterator'((char *)this + 156360, 0xDE8u, 36, (void (*)(void *))sub_454AA0);
  (UIWnd *->Destroy2()((char *)this + 155980));
  (UIWnd *->Destroy2()((char *)this + 155636));
  (UIWnd *->Destroy2()((char *)this + 155292));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 155044));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 154796));
  (UIWnd *->_UIFrameWnd()((char *)this + 154644));
  (UIWnd *->_UIFrameWnd()((char *)this + 154492));
  `eh vector destructor iterator'((char *)this + 79600, 0x248u, 128, sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 4848, 0x248u, 128, sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 4696));
  (UIWnd *->_UIFrameWnd()((char *)this + 4544));
  (UIWnd *->_UIFrameWnd()((char *)this + 4376));
  (UIWnd *->Destroy2()((char *)this + 4032));
  (UIWnd *->Destroy2()((char *)this + 3688));
  (UIWnd *->Destroy2()((char *)this + 3344));
  (UIWnd *->Destroy2()this + 75);
  (UIWnd *->Destroy2()((char *)this + 2656));
  (UIWnd *->Destroy2()((char *)this + 2312));
  (UIWnd *->Destroy2()((char *)this + 1968));
  (UIWnd *->Destroy2()((char *)this + 1624));
  (UIWnd *->Destroy2()this + 32);
  (UIWnd *->_UIFrameWnd()((char *)this + 1128));
  (UIWnd *->_UIFrameWnd()((char *)this + 976));
  (UIWnd *->_UIFrameWnd()((char *)this + 824));
  (UIWnd *->_UIFrameWnd()((char *)this + 672));
  (UIWnd *->_UIFrameWnd()this + 13);
  (UIWnd *->_UIFrameWnd()((char *)this + 368));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x004B7510
void UIWnd::~stdiobuf()
{
  *(_DWORD *)this = &off_56F404;
  sub_4B7AF0();
  sub_4B6FB0((int)this);
}

// 0x004B7CE0
void UIWnd::~stdiobuf()
{
  *(_DWORD *)this = &off_56F450;
  sub_4B7F00();
  sub_4B6FB0((int)this);
}

// 0x00504080
void UIWnd::~stdiobuf(void ***this)
{
  *this = (void **)&off_56FD78;
  sub_5040D0(this);
  sub_41C090(this);
}

// 0x005160A0
_DWORD * UIWnd::ctor_60A0(int a2)
{
  this->UIListBox();
  * this = (*)&off_5704A8;
  sub_516170(this);
  *((_DWORD *)this + 290) = a2;
  return this;
}

// 0x00516120
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_5704A8;
  sub_516170(this);
  UIWnd::~UIWnd(this);
}

// 0x00519310
_DWORD * UIWnd::ctor_9310()
{
  this->UIListBox();
  * this = (*)&off_5704C8;
  this->OnMessage();
  return this;
}

// 0x00519380
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_5704C8;
  this->OnMessage();
  UIWnd::~UIWnd(this);
}

// 0x00519B60
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_5704E4;
  this->Render();
  UIWnd::~UIWnd(this);
}

// 0x0051A3B0
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570500;
  sub_51A400(this);
  UIWnd::~UIWnd(this);
}

// 0x0051ACB0
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_57051C;
  this->CheckKeyInput();
  UIWnd::~UIWnd(this);
}

// 0x0051B180
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570538;
  this->Reset();
  UIWnd::~UIWnd(this);
}

// 0x0051B690
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570554;
  sub_51B6E0(this);
  UIWnd::~UIWnd(this);
}

// 0x0051BC00
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_570570;
  this->OnMessage();
  UIWnd::~UIWnd(this);
}

// 0x0051C280
void UIWnd::~stdiobuf(UIWnd *this)
{
  *(_DWORD *)this->_data = &off_57058C;
  this->Reset();
  UIWnd::~UIWnd(this);
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

  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 100) = 0;
  (_BYTE *->UIFrameWnd()(this + 360));
  (_BYTE *->UIFrameWnd()(this + 512));
  (_BYTE *->UIFrameWnd()(this + 664));
  (_BYTE *->UIFrameWnd()(this + 816));
  (_BYTE *->UIFrameWnd()(this + 968));
  (_BYTE *->UIFrameWnd()(this + 1120));
  (_DWORD *->ctor_BCE0()(this + 1272));
  (_DWORD *->_UIScene()(this + 1544));
  (_DWORD *->_UIScene()(this + 1888));
  *(_DWORD *)(this + 2232) = 0;
  sub_522030((_DWORD *)(this + 2236));
  *(_BYTE *)(this + 3868) = 0;
  *(_DWORD *)(this + 3872) = 0;
  UIItem::Refresh(this + 3876);
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
    v5 = v3 - 6;
    *v2 = 0;
    *(v3 - 8) = 0;
    *(v3 - 7) = 0;
    *v5 = 0;
    v2 += 12;
    v5[1] = 0;
    v5[2] = 0;
    v6 = v3 - 3;
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
  *(_DWORD *)this = &off_570630;
  UIItem::UIItem((int)this + 3876);
  sub_522120((int)this + 2236);
  (UIWnd *->Destroy2()((char *)this + 1888));
  (UIWnd *->Destroy2()((char *)this + 1544));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 1272));
  (UIWnd *->_UIFrameWnd()this + 28);
  (UIWnd *->_UIFrameWnd()((char *)this + 968));
  (UIWnd *->_UIFrameWnd()((char *)this + 816));
  (UIWnd *->_UIFrameWnd()((char *)this + 664));
  (UIWnd *->_UIFrameWnd()((char *)this + 512));
  (UIWnd *->_UIFrameWnd()this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00525120
int UIWnd::ctor_5120(int _this)
{
  gbVec3D *v2; // edi
  int v3; // ebp
  int v4; // edi
  int v5; // ebp

  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  `eh vector constructor iterator'(
    (void *)(this + 352),
    0xF8u,
    5,
    (void (*)(void *))UIStatic::UIStatic,
    (void (*)(void *))UIWnd::~UIWnd);
  (_BYTE *->UIFrameWnd()(this + 1624));
  (_BYTE *->UIFrameWnd()(this + 1776));
  (_BYTE *->UIFrameWnd()(this + 1928));
  `eh vector constructor iterator'(
    (void *)(this + 2080),
    0x158u,
    3,
    (void (*)(void *))UIScene::_UIScene,
    (void (*)(void *))UIScene::Destroy2);
  (char *->UIStatic()(this + 3164));
  (char *->UIStatic()(this + 3412));
  (_DWORD *->_UIScene()(this + 3660));
  (_DWORD *->ctor_9030()(this + 4004));
  (_DWORD *->ctor_9030()(this + 4312));
  (_DWORD *->ctor_9030()(this + 4620));
  v2 = (gbVec3D *)(this + 4928);
  v3 = 2;
  do
  {
    gbVec3D::`default constructor closure'(v2);
    v2 = (gbVec3D *)((char *)v2 + 12);
    --v3;
  }
  while ( v3 );
  (_BYTE *->UIFrameWnd()(this + 4952));
  (_BYTE *->UIFrameWnd()(this + 5104));
  (_BYTE *->UIFrameWnd()(this + 5256));
  (_BYTE *->UIFrameWnd()(this + 5408));
  (_BYTE *->UIFrameWnd()(this + 5560));
  (_BYTE *->UIFrameWnd()(this + 5712));
  (_BYTE *->UIFrameWnd()(this + 5864));
  (_BYTE *->UIFrameWnd()(this + 6016));
  *(_BYTE *)(this + 6192) = 0;
  *(_DWORD *)(this + 6188) = 0;
  *(_DWORD *)(this + 6184) = 0;
  *(_BYTE *)(this + 6204) = 0;
  (_DWORD *->ctor_F7F0()(this + 6208));
  sub_444F60((_BYTE *)(this + 6468));
  (_BYTE *->UIFrameWnd()(this + 6660));
  (_BYTE *->UIFrameWnd()(this + 6812));
  v4 = this + 6972;
  v5 = 5;
  do
  {
    ArraySort(v4, 800, 2, (int (*)(int))sub_5254C0);
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
    (void *)(this + 15068),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (void *)(this + 36092),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (void *)(this + 57116),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (void *)(this + 78140),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  *(_BYTE *)(this + 99196) = 0;
  *(_BYTE *)(this + 99197) = 0;
  *(_DWORD *)(this + 99200) = 0;
  UIItem::Refresh(this + 99204);
  UIItem::Refresh(this + 100572);
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
  *(_DWORD *)this = &off_5706CC;
  UIItem::UIItem((int)this + 100572);
  UIItem::UIItem((int)this + 99204);
  `eh vector destructor iterator'((char *)this + 78140, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 57116, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 36092, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 15068, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  (UIWnd *->_UIFrameWnd()((char *)this + 6812));
  (UIWnd *->_UIFrameWnd()((char *)this + 6660));
  sub_445010((UIWnd *)((char *)this + 6468));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 6208));
  (UIWnd *->_UIFrameWnd()((char *)this + 6016));
  (UIWnd *->_UIFrameWnd()((char *)this + 5864));
  (UIWnd *->_UIFrameWnd()((char *)this + 5712));
  (UIWnd *->_UIFrameWnd()this + 139);
  (UIWnd *->_UIFrameWnd()((char *)this + 5408));
  (UIWnd *->_UIFrameWnd()((char *)this + 5256));
  (UIWnd *->_UIFrameWnd()((char *)this + 5104));
  (UIWnd *->_UIFrameWnd()((char *)this + 4952));
  (UIWnd *->ctor_9130()((char *)this + 4620));
  (UIWnd *->ctor_9130()((char *)this + 4312));
  (UIWnd *->ctor_9130()((char *)this + 4004));
  (UIWnd *->Destroy2()((char *)this + 3660));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 3412));
  UIWnd::~UIWnd((UIWnd *)((char *)this + 3164));
  `eh vector destructor iterator'((char *)this + 2080, 0x158u, 3, (void (*)(void *))UIScene::Destroy2);
  (UIWnd *->_UIFrameWnd()((char *)this + 1928));
  (UIWnd *->_UIFrameWnd()((char *)this + 1776));
  (UIWnd *->_UIFrameWnd()((char *)this + 1624));
  `eh vector destructor iterator'((char *)this + 352, 0xF8u, 5, (void (*)(void *))UIWnd::~UIWnd);
  UIWnd::~UIWnd((UIWnd *)this);
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
  gbRefObject **v17; // edi
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
  int v41; // [esp+130h] [ebp-D4h] BYREF
  int v42; // [esp+134h] [ebp-D0h] BYREF
  int v43; // [esp+138h] [ebp-CCh]
  int v44; // [esp+13Ch] [ebp-C8h]
  int v45; // [esp+140h] [ebp-C4h]
  int v46; // [esp+144h] [ebp-C0h] BYREF
  int v47; // [esp+148h] [ebp-BCh]
  int v48; // [esp+14Ch] [ebp-B8h]
  int v49; // [esp+150h] [ebp-B4h]
  int v50; // [esp+154h] [ebp-B0h] BYREF
  int v51; // [esp+158h] [ebp-ACh]
  int v52; // [esp+15Ch] [ebp-A8h]
  int v53; // [esp+160h] [ebp-A4h]
  int v54; // [esp+164h] [ebp-A0h] BYREF
  int v55; // [esp+168h] [ebp-9Ch]
  int v56; // [esp+16Ch] [ebp-98h]
  int v57; // [esp+170h] [ebp-94h]
  int v58; // [esp+174h] [ebp-90h] BYREF
  int v59; // [esp+178h] [ebp-8Ch]
  int v60; // [esp+17Ch] [ebp-88h]
  int v61; // [esp+180h] [ebp-84h]
  _DWORD v62[2]; // [esp+184h] [ebp-80h] BYREF
  int v63; // [esp+18Ch] [ebp-78h]
  int v64; // [esp+190h] [ebp-74h]
  _DWORD v65[2]; // [esp+194h] [ebp-70h] BYREF
  int v66; // [esp+19Ch] [ebp-68h]
  int v67; // [esp+1A0h] [ebp-64h]
  int v68[4]; // [esp+1A4h] [ebp-60h] BYREF
  _DWORD v69[4]; // [esp+1B4h] [ebp-50h] BYREF
  _DWORD v70[4]; // [esp+1C4h] [ebp-40h] BYREF
  _DWORD v71[4]; // [esp+1D4h] [ebp-30h] BYREF
  _DWORD v72[4]; // [esp+1E4h] [ebp-20h] BYREF
  _DWORD v73[4]; // [esp+1F4h] [ebp-10h] BYREF

  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 80) = *(_DWORD *)(this + 88);
  *(_DWORD *)(this + 84) = *(_DWORD *)(this + 76) + *(_DWORD *)(this + 92);
  (UIWnd *->SetSelTexture()this,
    -1,
    *(_DWORD *)(this + 72),
    *(_DWORD *)(this + 76),
    *(_DWORD *)(this + 80),
    *(_DWORD *)(this + 84),
    0);
  *(_DWORD *)(this + 99200) = a2;
  v3 = *(_DWORD *)(this + 4952);
  v47 = 32;
  v46 = 168;
  v48 = 636;
  v49 = 136;
  (*(void (**)(int, void *, int *, int))(v3 + 16))(this + 4952, &unk_AA0C00, &v46, this);
  (gbRefObject **->CreateFromTemplate()(this + 4952),
    aSubgameApprais_1,
    *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v4 = *(_DWORD *)(this + 5104);
  v47 += 6;
  v46 += 24;
  v49 = v47 + 158;
  v48 = v46 + 428;
  (*(void (**)(int, void *, int *, int))(v4 + 16))(this + 5104, &unk_AA0C00, &v46, this);
  (_DWORD *->SetShow()(this + 5104), 0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v41 + 1) = 3103;
    LOBYTE(v41) = 0;
  }
  else
  {
    BYTE2(v41) = 0;
    LOWORD(v41) = 7948;
  }
  HIBYTE(v41) = -1;
  (_DWORD *->GetChild()(this + 5104), &v41);
  v5 = *(_DWORD *)(this + 5864);
  v62[1] = 0;
  v62[0] = 0;
  v63 = 14;
  v64 = 600;
  (*(void (**)(int, void *, _DWORD *, int))(v5 + 16))(this + 5864, &unk_AA0B00, v62, this);
  (gbRefObject **->CreateFromTemplate()(this + 5864),
    aUiGamemainuiCo_17,
    *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v6 = *(_DWORD *)(this + 6016);
  v62[0] = 786;
  v63 = 800;
  (*(void (**)(int, void *, _DWORD *, int))(v6 + 16))(this + 6016, &unk_AA0B00, v62, this);
  (gbRefObject **->CreateFromTemplate()(this + 6016),
    aUiGamemainuiCo_17,
    *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v7 = *(_DWORD *)(this + 6208);
  v72[1] = 0;
  v72[0] = 16;
  v72[2] = 788;
  v72[3] = 92;
  (*(void (**)(int, void *, _DWORD *, int))(v7 + 16))(this + 6208, &unk_AA0C00, v72, this);
  (gbRefObject **->GetChildCount()(this + 6208), aSubgameApprais_10, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  (gbRefObject **->GetChildAt()(this + 6208), aSubgameApprais_11, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  sub_43FD90((float *)(this + 6208), 0);
  UIWnd::FindChild(this + 6208, 620.0);
  *(_DWORD *)(this + 6420) = 1;
  *(_DWORD *)(this + 6448) = 300;
  *(_DWORD *)(this + 6440) = 1092616192;
  *(_DWORD *)(this + 6428) = 255;
  UIWnd::FindChildByName(this + 6208, 620.0);
  *(_DWORD *)(this + 6320) = 1142620160;
  v8 = *(_DWORD *)(this + 5408);
  v59 = 18;
  v58 = 64;
  v60 = 96;
  v61 = 42;
  (*(void (**)(int, void *, int *, int))(v8 + 16))(this + 5408, &unk_AA0C00, &v58, this);
  v9 = *(_DWORD *)(this + 5560);
  v59 = v61;
  v61 += 24;
  (*(void (**)(int, void *, int *, int))(v9 + 16))(this + 5560, &unk_AA0C00, &v58, this);
  v10 = *(_DWORD *)(this + 1624);
  v69[1] = 136;
  v69[0] = 90;
  v69[2] = 714;
  v69[3] = 598;
  (*(void (**)(int, void *, _DWORD *, int))(v10 + 16))(this + 1624, &unk_AA0C00, v69, this);
  (gbRefObject **->CreateFromTemplate()(this + 1624),
    aSubgameApprais_2,
    *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  v65[1] = 162;
  v65[0] = 120;
  v66 = 160;
  v67 = 208;
  v12 = &off_5706AC;
  v13 = (gbRefObject **)(this + 352);
  do
  {
    LOBYTE(v11) = *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756);
    ((void (*)(gbRefObject **, _DWORD, _DWORD *, int, char *, int))(*v13)[7].RefCount)(
      v13,
      *v12,
      v65,
      this,
      aSubgameApprais_3,
      v11);
    sub_440CE0(v13, aSubgameApprais_4, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
    ++v12;
    v65[0] = v66;
    v13 += 62;
    v66 += 40;
  }
  while ( (int)v12 < (int)&off_5706C0 );
  v14 = *(_DWORD *)(this + 5256);
  v70[1] = 170;
  v70[0] = 326;
  v70[2] = 482;
  v70[3] = 202;
  (*(void (**)(int, void *, _DWORD *, int))(v14 + 16))(this + 5256, &unk_AA0C21, v70, this);
  (_DWORD *->SetShow()(this + 5256), 0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v41 + 1) = -5;
    LOBYTE(v41) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v41 + 1) = 8187;
    LOBYTE(v41) = -1;
  }
  HIBYTE(v41) = -1;
  (_DWORD *->GetChild()(this + 5256), &v41);
  v51 = 146;
  v50 = 552;
  v52 = 597;
  v53 = 210;
  v16 = (int (__stdcall **)(int))&off_5706C0;
  v17 = (gbRefObject **)(this + 2080);
  v18 = (int *)(this + 3112);
  do
  {
    LOBYTE(v15) = *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756);
    ((void (*)(gbRefObject **, int (__stdcall *)(int), int *, int, char *, _DWORD, int))(*v17)[7].RefCount)(
      v17,
      *v16,
      &v50,
      this,
      aSubgameApprais_5,
      0,
      v15);
    v19 = v51;
    *v18 = v50;
    v20 = v52;
    v18[1] = v19;
    v21 = v53;
    v18[2] = v20;
    v18[3] = v21;
    v17->OpenScript(aSubgameApprais_7, *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
    v15 = v52;
    ++v16;
    v18 += 4;
    v17 += 86;
    v50 = v52 + 2;
    v52 += 47;
  }
  while ( (int)v16 < (int)&off_5706CC );
  v22 = *(_DWORD *)(this + 99200);
  v43 = 548;
  v42 = 213;
  v44 = 307;
  v45 = 568;
  LOBYTE(v22) = *(_BYTE *)(v22 + 1756);
  (*(void (**)(int, void *, int *, int, char *, int))(*(_DWORD *)(this + 3164) + 28))(
    this + 3164,
    &unk_AA0C16,
    &v42,
    this,
    aSubgameApprais_8,
    v22);
  v23 = v43;
  *(_DWORD *)(this + 99164) = v42;
  v24 = v45;
  *(_DWORD *)(this + 99168) = v23;
  v25 = v44;
  *(_DWORD *)(this + 99172) = v44;
  v42 = v25 + 200;
  *(_DWORD *)(this + 99176) = v24;
  v26 = *(_DWORD *)(this + 99200);
  v44 = v25 + 294;
  LOBYTE(v26) = *(_BYTE *)(v26 + 1756);
  (*(void (**)(int, void *, int *, int, char *, int))(*(_DWORD *)(this + 3412) + 28))(
    this + 3412,
    &unk_AA0C17,
    &v42,
    this,
    aSubgameApprais_8,
    v26);
  v27 = v43;
  v71[1] = 573;
  v71[0] = 358;
  v71[2] = 448;
  *(_DWORD *)(this + 99180) = v42;
  v28 = v44;
  v71[3] = 598;
  *(_DWORD *)(this + 99184) = v27;
  v29 = v45;
  *(_DWORD *)(this + 99188) = v28;
  v30 = *(_DWORD *)(this + 99200);
  *(_DWORD *)(this + 99192) = v29;
  LOBYTE(v29) = *(_BYTE *)(v30 + 1756);
  (*(void (**)(int, void *, _DWORD *, int, char *, _DWORD, int))(*(_DWORD *)(this + 3660) + 28))(
    this + 3660,
    &unk_AA0C18,
    v71,
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
  v55 = 136;
  v54 = 90;
  v56 = 716;
  v57 = 603;
  (*(void (**)(int, void *, int *, int))(v35 + 16))(this + 1776, &unk_AA0C19, &v54, this);
  (gbRefObject **->CreateFromTemplate()(this + 1776),
    aSubgameApprais_9,
    *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
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
  v55 = 164;
  v54 = 326;
  v56 = 482;
  v57 = 196;
  (*(void (**)(int, void *, int *, int))(v38 + 16))(this + 1928, &unk_AA0C19, &v54, this);
  (_DWORD *->SetShow()(this + 1928), 0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v41 + 1) = -5;
    LOBYTE(v41) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v41 + 1) = 8187;
    LOBYTE(v41) = -1;
  }
  HIBYTE(v41) = -1;
  (_DWORD *->GetChild()(this + 1928), &v41);
  (**(void (***)(int, _DWORD))(this + 1928))(this + 1928, 0);
  v39 = *(_DWORD *)(this + 5712);
  v73[1] = 158;
  v73[0] = 536;
  v73[2] = 581;
  v73[3] = 208;
  (*(void (**)(int, void *, _DWORD *, int))(v39 + 16))(this + 5712, &unk_AA0C00, v73, this);
  (gbRefObject **->CreateFromTemplate()(this + 5712),
    aSubgameApprais_6,
    *(_BYTE *)(*(_DWORD *)(this + 99200) + 1756));
  (**(void (***)(int, _DWORD))(this + 5712))(this + 5712, 0);
  v68[0] = 300;
  v68[3] = 300;
  *(_DWORD *)(this + 6168) = 45;
  *(_DWORD *)(this + 6172) = 50;
  v68[1] = 200;
  v68[2] = 500;
  UIItem::Create(this + 99204, (int)&unk_ABE00B, v68, this, 3, 0);
  (_DWORD *->SetData()(this + 99204), 31, 251, 255, 255);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v41 + 1) = -5;
    LOBYTE(v41) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v41 + 1) = 8187;
    LOBYTE(v41) = -1;
  }
  HIBYTE(v41) = -1;
  (_DWORD *->GetChild()(this + 99204), &v41);
  UIItem::Create(this + 100572, (int)&unk_ABC00C, v68, this, 3, 0);
  (_DWORD *->SetData()(this + 100572), 31, 251, 255, 255);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v41 + 1) = -5;
    LOBYTE(v41) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v41 + 1) = 8187;
    LOBYTE(v41) = -1;
  }
  HIBYTE(v41) = -1;
  (_DWORD *->GetChild()(this + 100572), &v41);
  *(_DWORD *)(this + 6456) = 120;
  *(_DWORD *)(this + 6460) = 534;
  *(_DWORD *)(this + 6464) = 420;
  *(_DWORD *)(this + 6452) = 278;
  (UINote *->Create()(this + 6468), (int)&unk_AA0C22, this + 6452, this, aUiFlexNote);
  (**(void (***)(int, _DWORD))(this + 6468))(this + 6468, 0);
  (*(void (**)(int, void *, int, int))(*(_DWORD *)(this + 6660) + 16))(
    this + 6660,
    &unk_AA0C22,
    this + 6452,
    this);
  (_DWORD *->SetShow()(this + 6660), 0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v41 + 1) = -5;
    LOBYTE(v41) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v41 + 1) = 8187;
    LOBYTE(v41) = -1;
  }
  HIBYTE(v41) = -1;
  (_DWORD *->GetChild()(this + 6660), &v41);
  (**(void (***)(int, _DWORD))(this + 6660))(this + 6660, 0);
  (*(void (**)(int, void *, int, int))(*(_DWORD *)(this + 6812) + 16))(
    this + 6812,
    &unk_AA0C23,
    this + 6452,
    this);
  (_DWORD *->SetShow()(this + 6812), 0);
  (**(void (***)(int, _DWORD))(this + 6812))(this + 6812, 0);
  if ( gbColorQuad::ColorQuadFmt )
  {
    *(_WORD *)((char *)&v41 + 1) = -5;
    LOBYTE(v41) = 31;
  }
  else
  {
    *(_WORD *)((char *)&v41 + 1) = 8187;
    LOBYTE(v41) = -1;
  }
  HIBYTE(v41) = -1;
  return (_DWORD *->GetChild()(this + 6812), &v41);
}

// 0x00526A40
int UIWnd::ctor_6A40(int _this, int a2, _BYTE *a3, int a4)
{
  _BYTE *v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edi
  void **v10; // ebp
  void (**v11)(int, int); // edx
  int v12; // eax
  int v13; // esi
  void (**v14)(int, _DWORD); // edx
  void (**v15)(int, _DWORD); // eax
  int v16; // ebp
  int *v17; // edi
  int v18; // edi
  _DWORD *v19; // ebp
  int v20; // ecx
  _DWORD *v21; // esi
  int v22; // edi
  int v23; // eax
  _DWORD *v24; // esi
  int v25; // edi
  char *v26; // [esp-8h] [ebp-24h]
  char *v27; // [esp-8h] [ebp-24h]
  int v28; // [esp-4h] [ebp-20h]
  int v29; // [esp+10h] [ebp-Ch] BYREF
  int v30; // [esp+14h] [ebp-8h] BYREF
  int v31; // [esp+18h] [ebp-4h]
  _DWORD *v32; // [esp+20h] [ebp+4h]

  switch ( a2 )
  {
    case 1000:
      if ( !a3 )
        return 1;
      sub_526300((char *)this);
      sub_527130(*(_DWORD *)(this + 15008));
      sub_5263C0(this);
      return 1;
    case 1001:
      v6 = a3;
      v7 = 0;
      v8 = (int)&off_5706AC;
      while ( a3 != *(_BYTE **)v8 )
      {
        v8 += 4;
        ++v7;
        if ( v8 >= (int)&off_5706C0 )
        {
          v9 = 0;
          v10 = (void **)&off_5706C0;
          v32 = (_DWORD *)(this + 2080);
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
                sub_445E50(v32, 0);
                *(_DWORD *)(this + 4892) = 0;
                *(_DWORD *)(this + 4888) = 0;
                *(_DWORD *)(this + 4884) = 0;
              }
              v26 = off_5E7ECC[0];
              v8->GetInstance();
              v26->AudioSetPosition(1);
              v6 = a3;
            }
            ++v10;
            ++v9;
            v8 = (int)(v32 + 86);
            v32 += 86;
          }
          while ( (int)v10 < (int)&off_5706CC );
          if ( v6 == (_BYTE *)&unk_AA0C16 )
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
              v15 = *(void (***)(int, _DWORD))(this + 3660);
              *(_BYTE *)(this + 15012) = 0;
              (*v15)(this + 3660, 0);
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 0;
            }
          }
          else
          {
            if ( v6 - (_BYTE *)&unk_AA0C16 != 1 )
            {
              if ( v6 - (_BYTE *)&unk_AA0C16 == 2 && !*(_BYTE *)(this + 15018) && !*(_BYTE *)(this + 6176) )
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
              v14 = *(void (***)(int, _DWORD))(this + 3660);
              *(_BYTE *)(this + 15012) = 0;
              (*v14)(this + 3660, 0);
              *(_BYTE *)(*(_DWORD *)(this + 15008) + this + 15024) = 0;
            }
          }
          sub_527370(*(_DWORD *)(this + 15008));
          v27 = off_5E7ECC[0];
          goto LABEL_21;
        }
      }
      if ( *(_BYTE *)(this + 6176) )
      {
        v12 = this + 248 * v7;
        if ( *(_BYTE *)(v12 + 420) )
        {
          *(_DWORD *)(v12 + 432) = 0;
          *(_BYTE *)(v12 + 420) = 0;
        }
        else
        {
          *(_DWORD *)(v12 + 432) = 1;
          *(_BYTE *)(v12 + 420) = 1;
        }
        return 1;
      }
      if ( *(_BYTE *)(this + 15012) || *(_BYTE *)(this + 15018) )
      {
        if ( !*(_BYTE *)(v7 + this + 15013) )
        {
          v8 = this + 248 * v7 + 352;
          *(_DWORD *)(v8 + 80) = 0;
          *(_BYTE *)(v8 + 68) = 0;
        }
        if ( *(_DWORD *)(this + 15008) == v7 )
        {
          v8 = 31 * v7;
          v13 = this + 248 * v7 + 352;
          *(_DWORD *)(v13 + 80) = 1;
          *(_BYTE *)(v13 + 68) = 1;
        }
        v27 = off_5E7ED8[0];
      }
      else if ( *(_BYTE *)(v7 + this + 15013) )
      {
        v27 = off_5E7ED8[0];
      }
      else
      {
        *(_DWORD *)(this + 15008) = v7;
        if ( (int)sub_5270C0(v7) > 0 )
          sub_527130(*(_DWORD *)(this + 15008));
LABEL_20:
        v8 = (int)off_5E7ECC[0];
        v27 = off_5E7ECC[0];
      }
LABEL_21:
      v8->GetInstance();
      v27->AudioSetPosition(1);
      return 1;
    case 1002:
      if ( a3 == (_BYTE *)&unk_AA0C16 )
      {
        if ( !*(_BYTE *)(this + 15018) && !*(_BYTE *)(this + 6176) )
          *(_BYTE *)(this + 99196) = 1;
      }
      else if ( a3 - (_BYTE *)&unk_AA0C16 == 1 && !*(_BYTE *)(this + 15018) && !*(_BYTE *)(this + 6176) )
      {
        *(_BYTE *)(this + 99197) = 1;
        return 1;
      }
      return 1;
    case 1009:
      if ( a3 != (_BYTE *)&unk_AA0C22 )
        return 1;
      if ( *(_BYTE *)(*(_DWORD *)(this + 99200) + 1740) )
      {
        v16 = 0;
        v17 = (int *)(this + 6968);
        do
        {
          if ( *(_BYTE *)(this + v16 + 15024) )
          {
            v28 = *v17;
            v30 = 0;
            v31 = 0;
            v29 = v28;
            v31 = g_GDB->GDB_GetSkillNum(v28);
            v30 = 1;
            CCBStageRole_GetAlive((int)MEMORY[0xC05F30], &v29);
          }
          ++v16;
          v17 += 402;
        }
        while ( v16 < 5 );
      }
      sub_527F50(3);
      return 1;
    case 1010:
      if ( *(_BYTE *)(this + 15018) )
      {
        sub_527370(*(_DWORD *)(this + 15008));
        *(_DWORD *)(this + 4892) = 0;
        *(_DWORD *)(this + 4888) = 0;
        *(_DWORD *)(this + 4884) = 0;
        v18 = 0;
        v19 = (_DWORD *)(this + 2080);
        do
        {
          if ( *(_BYTE *)(this + v18 + 3160) )
            sub_445E50(v19, 1);
          ++v18;
          v19 += 86;
        }
        while ( v18 < 3 );
      }
      return 1;
    case 1013:
      if ( a3 == (_BYTE *)&unk_AA0C25 )
      {
        if ( *(_BYTE *)(this + 6176) )
        {
          sub_527230(0, *(_DWORD *)(this + 15008));
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
        }
        return 1;
      }
      if ( a3 - (_BYTE *)&unk_AA0C25 != 1 || !*(_BYTE *)(this + 6176) )
        return 1;
      sub_527230(1, *(_DWORD *)(this + 15008));
      v20 = *(_DWORD *)(this + 6180);
      v21 = (_DWORD *)(this + 2080);
      v22 = 3;
      *((_BYTE *)v21 + v20 + 1080) = 0;
      do
      {
        sub_445E50(v21, 0);
        v21 += 86;
        --v22;
      }
      while ( v22 );
      return 1;
    case 1016:
      if ( a3 == (_BYTE *)&unk_AA0C27 )
      {
        GRPinput::GetMousePos(&g_Input, &v29, &v30);
        *(float *)(this + 4884) = (double)v30 + *(float *)(this + 4884);
        *(float *)(this + 4888) = (double)v29 + *(float *)(this + 4888);
      }
      return 1;
    default:
      return a2->SendMessage((int)a3, a4);
  }
}

// 0x00527950
int UIWnd::ctor_7950(int _this)
{
  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_DWORD *)(this + 352) = 0;
  UIItem::Refresh(this + 356);
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

  *(_DWORD *)this = &off_5706EC;
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
  UIItem::UIItem((int)this + 356);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x005282E0
int UIWnd::ctor_82E0(int _this)
{
  gbVec3D *v2; // edi
  int v3; // ebp
  int v4; // edi
  int v5; // ebp

  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  (_DWORD *->_UIScene()(this + 352));
  (_BYTE *->UIFrameWnd()(this + 696));
  (_BYTE *->UIFrameWnd()(this + 848));
  (_BYTE *->UIFrameWnd()(this + 1000));
  (_BYTE *->UIFrameWnd()(this + 1152));
  (_BYTE *->UIFrameWnd()(this + 1304));
  (_BYTE *->UIFrameWnd()(this + 1456));
  (_BYTE *->UIFrameWnd()(this + 1608));
  (_BYTE *->UIFrameWnd()(this + 1760));
  (_DWORD *->ctor_9030()(this + 1912));
  v2 = (gbVec3D *)(this + 2220);
  v3 = 5;
  do
  {
    gbVec3D::`default constructor closure'(v2);
    v2 = (gbVec3D *)((char *)v2 + 12);
    --v3;
  }
  while ( v3 );
  (_DWORD *->ctor_9030()(this + 2280));
  (_BYTE *->UIFrameWnd()(this + 2588));
  (_BYTE *->UIFrameWnd()(this + 2740));
  sub_431870((_DWORD *)(this + 2900));
  v4 = this + 4712;
  v5 = 5;
  do
  {
    ArraySort(v4, 800, 2, (int (*)(int))sub_5254C0);
    v4 += 1608;
    --v5;
  }
  while ( v5 );
  *(_DWORD *)(this + 12744) = 0;
  UIItem::Refresh(this + 12752);
  `eh vector constructor iterator'(
    (void *)(this + 14124),
    0x248u,
    36,
    (void (*)(void *))sub_4B4690,
    (void (*)(void *))sub_4B47E0);
  `eh vector constructor iterator'(
    (void *)(this + 35148),
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
  *(_DWORD *)this = &off_570728;
  `eh vector destructor iterator'((char *)this + 35148, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  `eh vector destructor iterator'((char *)this + 14124, 0x248u, 36, (void (*)(void *))sub_4B47E0);
  UIItem::UIItem((int)this + 12752);
  sub_4318A0((char *)this + 2900);
  (UIWnd *->_UIFrameWnd()((char *)this + 2740));
  (UIWnd *->_UIFrameWnd()((char *)this + 2588));
  (UIWnd *->ctor_9130()this + 57);
  (UIWnd *->ctor_9130()((char *)this + 1912));
  (UIWnd *->_UIFrameWnd()this + 44);
  (UIWnd *->_UIFrameWnd()((char *)this + 1608));
  (UIWnd *->_UIFrameWnd()((char *)this + 1456));
  (UIWnd *->_UIFrameWnd()((char *)this + 1304));
  (UIWnd *->_UIFrameWnd()((char *)this + 1152));
  (UIWnd *->_UIFrameWnd()this + 25);
  (UIWnd *->_UIFrameWnd()((char *)this + 848));
  (UIWnd *->_UIFrameWnd()((char *)this + 696));
  (UIWnd *->Destroy2()((char *)this + 352));
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x005295F0
int UIWnd::ctor_95F0(int _this)
{
  (_DWORD *->UIListBox()this);
  *(_DWORD *)(this + 88) = 800;
  *(_DWORD *)(this + 92) = 600;
  *(_BYTE *)(this + 352) = 0;
  (_BYTE *->UIFrameWnd()(this + 360));
  `eh vector constructor iterator'(
    (void *)(this + 512),
    0xB8u,
    3,
    (void (*)(void *))UIWnd::ctor_2E10,
    (void (*)(void *))UIWnd::ctor_2E80);
  sub_444A20((unsigned __int8 *)(this + 1064));
  *(_BYTE *)(this + 1260) = 0;
  *(_DWORD *)(this + 1256) = 0;
  *(_DWORD *)(this + 1252) = 0;
  *(_BYTE *)(this + 1280) = 0;
  *(_DWORD *)(this + 1276) = 0;
  *(_DWORD *)(this + 1272) = 0;
  (_BYTE *->UIFrameWnd()(this + 1284));
  (_BYTE *->UIFrameWnd()(this + 1436));
  (_BYTE *->UIFrameWnd()(this + 1840));
  sub_444F60((_BYTE *)(this + 1992));
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
  *(_DWORD *)this = &off_57076C;
  UIQuadManager::GetInstance();
  UIRenderObj::~UIRenderObj(1);
  sub_445010((UIWnd *)((char *)this + 1992));
  (UIWnd *->_UIFrameWnd()this + 46);
  (UIWnd *->_UIFrameWnd()((char *)this + 1436));
  (UIWnd *->_UIFrameWnd()((char *)this + 1284));
  sub_444AC0((UIWnd *)((char *)this + 1064));
  `eh vector destructor iterator'((char *)this + 512, 0xB8u, 3, (void (*)(void *))UIWnd::ctor_2E80);
  (UIWnd *->_UIFrameWnd()this + 9);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x0052BA10
int UIWnd::ctor_BA10(int _this)
{
  (_DWORD *->UIListBox()this);
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
  (_BYTE *->UIFrameWnd()(this + 1160));
  (_DWORD *->ctor_2E10()(this + 1312));
  `eh vector constructor iterator'(
    (void *)(this + 1496),
    0x98u,
    4,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (_BYTE *->UIFrameWnd()(this + 2120));
  (_BYTE *->UIFrameWnd()(this + 2272));
  `eh vector constructor iterator'(
    (void *)(this + 2424),
    0x610u,
    5,
    sub_52BBD0,
    (void (*)(void *))sub_52BC90);
  *(_DWORD *)(this + 10184) = 0;
  *(_BYTE *)(this + 10188) = 1;
  *(_DWORD *)(this + 10192) = 0;
  *(_DWORD *)(this + 10196) = 1092616192;
  *(_BYTE *)(this + 10200) = 0;
  *(_BYTE *)(this + 10206) = 0;
  UIItem::Refresh(this + 10208);
  UIItem::Refresh(this + 11576);
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
  *(_DWORD *)this = &off_570830;
  UIItem::UIItem((int)this + 11576);
  UIItem::UIItem((int)this + 10208);
  `eh vector destructor iterator'((char *)this + 2424, 0x610u, 5, (void (*)(void *))sub_52BC90);
  (UIWnd *->_UIFrameWnd()((char *)this + 2272));
  (UIWnd *->_UIFrameWnd()this + 53);
  `eh vector destructor iterator'((char *)this + 1496, 0x98u, 4, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->ctor_2E80()((char *)this + 1312));
  (UIWnd *->_UIFrameWnd()this + 29);
  sub_4318A0((char *)this + 352);
  UIWnd::~UIWnd((UIWnd *)this);
}

// 0x00531D20
int UIWnd::ctor_1D20(int _this)
{
  (_DWORD *->UIListBox()this);
  *(_BYTE *)(this + 360) = 0;
  *(_DWORD *)(this + 356) = 0;
  *(_DWORD *)(this + 352) = 0;
  (_BYTE *->UIFrameWnd()(this + 364));
  (_BYTE *->UIFrameWnd()(this + 1316));
  `eh vector constructor iterator'(
    (void *)(this + 1468),
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector constructor iterator'(
    (void *)(this + 2988),
    0x98u,
    10,
    (void (*)(void *))UIFrameWnd::UIFrameWnd,
    (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  *(_BYTE *)(this + 4536) = 0;
  *(_DWORD *)(this + 4532) = 0;
  *(_DWORD *)(this + 4528) = 0;
  UIItem::Refresh(this + 4540);
  UIItem::Refresh(this + 5908);
  (_BYTE *->UIFrameWnd()(this + 7280));
  (_BYTE *->UIFrameWnd()(this + 7432));
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
  *(_DWORD *)this = &off_570890;
  (UIWnd *->_UIFrameWnd()((char *)this + 7432));
  (UIWnd *->_UIFrameWnd()this + 182);
  UIItem::UIItem((int)this + 5908);
  UIItem::UIItem((int)this + 4540);
  `eh vector destructor iterator'((char *)this + 2988, 0x98u, 10, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  `eh vector destructor iterator'((char *)this + 1468, 0x98u, 10, (void (*)(void *))UIFrameWnd::_UIFrameWnd);
  (UIWnd *->_UIFrameWnd()((char *)this + 1316));
  (UIWnd *->_UIFrameWnd()((char *)this + 364));
  UIWnd::~UIWnd((UIWnd *)this);
}
