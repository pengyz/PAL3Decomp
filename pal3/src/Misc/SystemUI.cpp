#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SystemUI.h"

// Forward declarations for unnamed functions
int sub_41F8C0(...);
int sub_426EB0(...);
int sub_445E50(int a2); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

// Unnamed globals (extern)
extern char byte_A00102;
extern char byte_A00103;
extern char byte_A00104;
extern char byte_A00105;
extern char byte_A00106;
extern char byte_A00107;
extern char byte_A00108;
extern char byte_A00109;
extern char byte_A00110;
extern char byte_A00539;
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DDA73C[512];
extern int dword_56F224[];
extern int dword_56F228[];
extern int dword_56F22C[];
extern int dword_56F230[];
extern int dword_56F234[];
extern int dword_C10CC4;
extern int dword_D8BBEC;
extern int dword_DC933C;
extern int dword_DC943C;
extern int dword_DC9F3C;
extern int dword_DCE93C;
extern int dword_DD253C;
extern int dword_DD3D3C;
extern int dword_DD433C;
extern const char * off_56F1A4;
extern const char * off_56F1B8;
extern const char * off_56F1CC;
extern const char * off_56F1E0;
extern const char * off_56F1F4;
extern const char * off_56F208;
extern void *off_5CF1EC;
extern void * off_5CF1F0;
extern void * off_5CF220;
extern RoleSystem stru_C059A0;

// 0x0041F6F0
void SystemUI::Reset()
{
  *(_DWORD *)&this->buf[36] = 0;
  *(_DWORD *)&this->buf[40] = 0;
  *(_DWORD *)&this->buf[44] = 0;
  *(_DWORD *)&this->buf[48] = 0;
  *(_DWORD *)&this->buf[52] = 0;
  *(_DWORD *)&this->buf[56] = 0;
  ((PtrArray *)&this->buf[60])->Clear();
  ((GRPinput *)&this->m_NoteItem[98].m_HeadShot[2].m_pbk2)->AcquireMouse();
  *(_DWORD *)&this->buf[28] = 0;
  this->m_par[12][6].par_radiusY = 0;
  this->m_NoteItem[98].m_NoteTime.m_childs.capacity = 0;
  *((_DWORD *)&this->_field_0B4 + 10) = 0;
  this->m_NoteItem[98].m_NoteTime.m_childs.m_pData = 0;
  this->m_NoteItem[98].m_NoteTime.m_childs.m_nSize = 0;
  *(_DWORD *)&this->buf[32] = 0;
  this->m_NoteItem[98].m_NoteTime.m_bcreateok = 0;
  LOBYTE(this->m_NoteItem[98].m_NoteTime.m_childs.m_needscriptdel) = -1;
}

// 0x0041F800
void SystemUI::Close()
{
  sub_41F8C0();
  ((GRPinput *)&this->m_NoteItem[98].m_HeadShot[2].m_pbk2)->UnacquireKeyboard();
  ((UIListBox *)&this->buf[60])->ReleaseVtable();
}

// 0x004200A0
int SystemUI::Render(int nVal)
{
  int result; // eax
  char *m_pData; // ecx
  int v5; // ebx
  UIBigMap *v6; // esi

  result = this->m_NoteItem[98].m_NoteTime.m_childs.capacity;
  if ( result )
  {
    m_pData = this->m_NoteItem[98].m_NoteTime.m_childs.m_pData;
    if ( m_pData )
    {
      ((gbVisNode *)m_pData)->SetTimeScale(0.2);
      (*(void ( **)(char *, _DWORD))(*(_DWORD *)this->m_NoteItem[98].m_NoteTime.m_childs.m_pData + 16))(
        this->m_NoteItem[98].m_NoteTime.m_childs.m_pData,
        0);
    }
    result = *((_DWORD *)&this->_field_0B4 + 10);
    v5 = 0;
    if ( result > 0 )
    {
      v6 = (UIBigMap *)(&this->_field_0B4 + 11);
      do
      {
        if ( v6->bkWndX != 4 )
          ((UIBigMap *)v6)->RenderRole((gbMatrixStack *)nVal, 0);
        result = *((_DWORD *)&this->_field_0B4 + 10);
        ++v5;
        v6 = (UIBigMap *)((char *)v6 + 896);
      }
      while ( v5 < result );
    }
  }
  return result;
}

// 0x00420110
int SystemUI::RenderWithStack(void *pStack)
{
  int v3; // esi
  int result; // eax
  int *p_W; // edi

  v3 = 0;
  result = this->m_par[12][6].par_radiusY;
  if ( result > 0 )
  {
    p_W = &this->m_par[12][6]._W;
    do
    {
      ((RoleSystem *)p_W)->RenderRole((gbMatrixStack *)pStack, 0);
      result = this->m_par[12][6].par_radiusY;
      ++v3;
      p_W += 2176;
    }
    while ( v3 < result );
  }
  return result;
}

// 0x00420150
double SystemUI::UIUpdate(double result, double pData)
{
  char *m_pData; // ecx
  int v5; // edi
  double v6; // st7
  int *p_W; // ebx
  int v8; // edi
  void **v9; // ebx
  float dt; // [esp+0x10] [ebp-0x4]
  float dta; // [esp+0x10] [ebp-0x4]

  if ( this->m_NoteItem[98].m_NoteTime.m_childs.capacity )
  {
    m_pData = this->m_NoteItem[98].m_NoteTime.m_childs.m_pData;
    if ( m_pData )
      (*(void ( **)(char *))(*(_DWORD *)m_pData + 20))(m_pData);
    v5 = 0;
    if ( this->m_par[12][6].par_radiusY > 0 )
    {
      v6 = result;
      p_W = &this->m_par[12][6]._W;
      do
      {
        dt = result;
        ((ScriptSystem *)dt)->UpdateTimers();
        ++v5;
        p_W += 2176;
      }
      while ( v5 < this->m_par[12][6].par_radiusY );
    }
    if ( g_nSceneState != 9 )
    {
      v8 = 0;
      if ( *((int *)&this->_field_0B4 + 10) > 0 )
      {
        v6 = result;
        v9 = &this->_field_0B4 + 11;
        do
        {
          dta = result;
          sub_426EB0((int)v9, dta);
          ++v8;
          v9 += 224;
        }
        while ( v8 < *((_DWORD *)&this->_field_0B4 + 10) );
      }
    }
  }
  return v6;
}

// 0x00421A40
int SystemUI::GetNoteItemData(int *item)
{
  item[3] = (int)this->m_NoteItem[98].m_HeadShot[3].m_disablepic;
  item[4] = (int)this->m_NoteItem[98].m_HeadShot[3].m_disablepicInfo;
  item[5] = (int)this->m_NoteItem[98].m_HeadShot[3].m_pbk2;
  *item = (int)this->m_NoteItem[98].m_HeadShot[3].m_pbkInfo;
  item[1] = (int)this->m_NoteItem[98].m_HeadShot[3].m_ppic;
  item[2] = (int)this->m_NoteItem[98].m_HeadShot[3].m_ppicInfo;
  return 1;
}

// 0x004A7690
void SystemUI::_SystemUI()
{
  PalScript *p_m_needscriptdel; // edi
  int v3; // [esp+0x0] [ebp-0x18]

  p_m_needscriptdel = (PalScript *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel;
  (*(void ( **)(int *))(this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel + 12))(&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel);
  ((UIRoleDialog *)&this->m_NoteItem[72].m_NoteLv[3].m_nTextW)->_UIRoleDialog();
  ((UIRoleDialog *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor)->_UIRoleDialog();
  ((CCBStageRole *)&this->m_NoteItem[72].m_HeadShot[1].m_pbkInfo)->Init(v3);
  ((UICaption *)&this->m_NoteItem[72].m_HeadShot_NO_SEL[4].m_align)->Destroy2();
  ((UICaption *)&this->m_NoteItem[72].m_HeadShot_NO_SEL[2].m_pfather)->Destroy2();
  ((UICaption *)&this->m_NoteItem[72].m_NoteState.m_FVF)->Destroy2();
  ((UICaption *)&this->m_NoteItem[72].m_NoteItemBk.m_caption[104])->Destroy2();
  ((UICaption *)&this->m_NoteItem[71].m_NotePicName.m_ppic)->Destroy2();
  ((UICaption *)&this->m_NoteItem[71].m_NoteLv[4].m_ratioh)->Destroy2();
  ((UI3DCtrl *)&this->m_NoteItem[71].m_NoteLv[3].m_disablepicInfo)->ctor();
  ((UIFrameWnd *)&this->m_NoteItem[71].m_NoteLv[2].m_disablepicInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[71].m_NoteLv[0].m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[71].m_NoteMoney.m_pbkInfo)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo)->DeleteRow();
  ((UIListBox *)&this->m_NoteItem[71].m_NoteItemBk.m_id)->DeleteRow();
  ((UIListBox *)&this->m_NoteItem[70].m_NoteMoney.m_childs)->DeleteRow();
  ((UIListBox *)&this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok)->DeleteRow();
  ((UIListBox *)&this->m_NoteItem[69].m_NotePicName.m_pbkInfo)->DeleteRow();
  ((UIListBox *)&this->m_NoteItem[69].m_NoteTime.m_ppicInfo)->DeleteRow();
  ((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot[4].m_childs.m_nSize)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot[2].m_childs.m_nSize)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot[1].m_childs.m_nSize)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot[0].m_childs.m_nSize)->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)&this->m_NoteItem[68].m_HeadShot_NO_SEL[4].m_pbk)->ctor();
  ((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot_NO_SEL[3].m_pbk)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot_NO_SEL[2].m_pbk)->UIFrameWnd::_UIFrameWnd();
  ((UI3DCtrl *)&this->m_NoteItem[67].m_NoteLv[2].m_childs)->ctor();
  ((UI3DCtrl *)&this->m_NoteItem[67].m_NoteLv[1].m_text[8])->ctor();
  ((CCCTData *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor)->DestroyImage();
  ((UICaption *)&this->m_NoteItem[67].m_HeadShot[1].m_childs)->Destroy2();
  ((UICaption *)&this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW)->Destroy2();
  ((UICaption *)&this->m_NoteItem[12].m_NoteID.m_ppicInfo)->Destroy2();
  ((UICaption *)&this->m_NoteItem[10].m_HeadShot[0].m_bvisible)->Destroy2();
  ((UIFrameWnd *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[2].m_bvisible)->UIFrameWnd::_UIFrameWnd();
  ((PalScript *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[0].m_bcreateok)->PalScript_Init();
  ((PalScript *)p_m_needscriptdel)->PalScript_Init();
  ((UIFrameWnd *)&this->m_NoteItem[10].m_NoteItemBk.m_caption[48])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[10].m_NoteItemBk.m_offsety)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[9].m_NotePicName.m_text[8])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_NoteItem[9].m_NotePic.m_text[8])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[5][3]._element.m_childs.capacity)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[5][3]._texName[148])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[5][3]._y)->UIFrameWnd::_UIFrameWnd();
  ((UICaption *)&this->m_par[5][2]._texName[220])->Destroy2();
  ((UICaption *)&this->m_par[5][2]._H)->Destroy2();
  ((UICaption *)&this->m_par[5][1]._texName[116])->Destroy2();
  ((UICaption *)this->m_par[5][0]._element.m_text)->Destroy2();
  ((UICaption *)&this->m_par[5][0]._texName[12])->Destroy2();
  ((UICaption *)&this->m_par[4][6]._texName[252])->Destroy2();
  ((UICaption *)&this->m_par[4][6].m_posx)->Destroy2();
  ((UICaption *)&this->m_par[4][5]._texName[148])->Destroy2();
  ((UICaption *)&this->m_par[4][4]._element.m_disablepic)->Destroy2();
  ((UIFrameWnd *)&this->m_par[4][4]._texName[236])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[4][4]._texName[84])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[4][4].m_riseY)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[4][3]._element.m_text[8])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_par[4][3]._texName[212])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->pStateUI)->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x004A7C40
int SystemUI::LayoutWidgets()
{
  float m_riseY; // eax
  float *p_m_riseY; // edi
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  unsigned int v9; // edx
  unsigned int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // edx
  int v16; // eax
  char *v17; // ecx
  int v18; // edx
  int v19; // eax
  float y; // eax
  int v21; // eax
  int v22; // eax
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // edx
  int H; // edx
  int v31; // eax
  int v32; // ecx
  int v33; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v36; // ecx
  int v37; // eax
  _DWORD v39[2]; // [esp+0x8C] [ebp-0x20] BYREF
  int v40; // [esp+0x94] [ebp-0x18]
  int v41; // [esp+0x98] [ebp-0x14]
  _DWORD v42[4]; // [esp+0x9C] [ebp-0x10] BYREF

  m_riseY = this->m_par[4][4].m_riseY;
  p_m_riseY = &this->m_par[4][4].m_riseY;
  v39[1] = 543;
  v39[0] = 0;
  v40 = 256;
  v41 = 600;
  (*(void ( **)(float *, int, _DWORD *, SystemUI *))(LODWORD(m_riseY) + 16))(
    &this->m_par[4][4].m_riseY,
    161,
    v39,
    this);
  ((UIStatic *)p_m_riseY)->CreateFromTemplate();
  v4 = *(_DWORD *)&this->m_par[4][4]._texName[84];
  v39[0] = v40;
  v40 += 512;
  (*(void ( **)(char *, int, _DWORD *, SystemUI *))(v4 + 16))(&this->m_par[4][4]._texName[84], 161, v39, this);
  ((UIStatic *)&this->m_par[4][4]._texName[84])->CreateFromTemplate();
  v39[0] = v40;
  v40 += 32;
  (*(void ( **)(char *, int, _DWORD *, SystemUI *))(*(_DWORD *)&this->m_par[4][4]._texName[236] + 16))(
    &this->m_par[4][4]._texName[236],
    161,
    v39,
    this);
  ((UIStatic *)&this->m_par[4][4]._texName[236])->CreateFromTemplate();
  *(_DWORD *)&this->m_par[5][3]._texName[136] = 546;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = 38;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = 148;
  *(_DWORD *)&this->m_par[5][3]._texName[144] = *(_DWORD *)&this->m_par[5][3]._texName[136] + 50;
  LOBYTE(v5) = g_bDebugMode;
  ((void ( *)(gbTexture **, char *, char *, SystemUI *, char *, int, int))this->m_par[4][4]._element.m_disablepic->Height)(
    &this->m_par[4][4]._element.m_disablepic,
    &byte_A00102,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v5);
  this->m_NoteItem[9].m_NoteLv[4].m_ppic = (gbTexture *)(*(_DWORD *)&this->m_par[5][3]._texName[136] + 5);
  this->m_NoteItem[9].m_NoteLv[4].m_pbkInfo = (_PlugInfo *)(*(_DWORD *)&this->m_par[5][3]._texName[132] + 35);
  this->m_NoteItem[9].m_NoteLv[4].m_ppicInfo = (_PlugInfo *)(*(_DWORD *)&this->m_par[5][3]._texName[140] - 36);
  this->m_NoteItem[9].m_NoteLv[4].m_disablepic = (gbTexture *)(*(_DWORD *)&this->m_par[5][3]._texName[144] - 5);
  v6 = *(_DWORD *)&this->m_par[5][3]._texName[140] - 22;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = v6;
  v6 += 110;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = v6;
  LOBYTE(v6) = g_bDebugMode;
  (*(void ( **)(char *, char *, SystemUI *, char *, int, int))(*(_DWORD *)&this->m_par[4][6]._texName[252] + 28))(
    &byte_A00105,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v6);
  this->m_NoteItem[9].m_NotePic.m_rect.left = *(_DWORD *)&this->m_par[5][3]._texName[136] + 5;
  this->m_NoteItem[9].m_NotePic.m_id = (void *)(*(_DWORD *)&this->m_par[5][3]._texName[132] + 35);
  this->m_NoteItem[9].m_NotePic.m_rect.top = *(_DWORD *)&this->m_par[5][3]._texName[140] - 36;
  this->m_NoteItem[9].m_NotePic.m_rect.right = *(_DWORD *)&this->m_par[5][3]._texName[144] - 5;
  v7 = *(_DWORD *)&this->m_par[5][3]._texName[140] - 22;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = v7;
  v7 += 110;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = v7;
  LOBYTE(v7) = g_bDebugMode;
  (*(void ( **)(char *, char *, SystemUI *, char *, int, int))(LODWORD(this->m_par[4][6].m_posx) + 28))(
    &byte_A00104,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v7);
// [VFTABLE] this->m_NoteItem[9].m_NotePic.__vftable = (vtbl_0056AE2C *)(*(_DWORD *)&this->m_par[5][3]._texName[136] + 5);
  this->m_NoteItem[9].m_NoteLv[4].m_nTextW = *(_DWORD *)&this->m_par[5][3]._texName[132] + 35;
  v8 = *(_DWORD *)&this->m_par[5][3]._texName[140];
  v9 = *(_DWORD *)&this->m_par[5][3]._texName[144];
  v10 = v8 - 36;
  v8 -= 22;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = v8;
  v9 -= 5;
  this->m_NoteItem[9].m_NotePic.m_fontcolor.Color = v10;
  this->m_NoteItem[9].m_NotePic.m_wndcolor.Color = v9;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = v8 + 110;
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, SystemUI *, char *, int, unsigned int))(*(_DWORD *)&this->m_par[4][5]._texName[148]
                                                                                            + 28))(
    &this->m_par[4][5]._texName[148],
    &byte_A00103,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v9);
  v11 = *(_DWORD *)&this->m_par[5][3]._texName[132];
  this->m_NoteItem[9].m_NoteLv[4].m_pbk2 = (gbTexture *)(*(_DWORD *)&this->m_par[5][3]._texName[136] + 5);
  v12 = *(_DWORD *)&this->m_par[5][3]._texName[140];
  this->m_NoteItem[9].m_NoteLv[4].m_disablepicInfo = (_PlugInfo *)(v11 + 35);
  v13 = *(_DWORD *)&this->m_par[5][3]._texName[144];
  v14 = v12 - 36;
  v12 -= 22;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = v12;
  v12 += 110;
  *(_DWORD *)&this->m_NoteItem[9].m_NoteLv[4].m_mouseoff = v14;
  this->m_NoteItem[9].m_NoteLv[4].m_FVF = v13 - 5;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = v12;
  LOBYTE(v12) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, SystemUI *, char *, int, int))(*(_DWORD *)&this->m_par[5][1]._texName[116]
                                                                               + 28))(
    &this->m_par[5][1]._texName[116],
    &byte_A00108,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v12);
  v15 = *(_DWORD *)&this->m_par[5][3]._texName[132];
  v16 = *(_DWORD *)&this->m_par[5][3]._texName[140];
  this->m_NoteItem[9].m_NotePic.m_pfather = (UIWnd *)(*(_DWORD *)&this->m_par[5][3]._texName[136] + 5);
  v17 = (char *)(v16 - 36);
  this->m_NoteItem[9].m_NotePic.m_rect.bottom = v15 + 35;
  v18 = *(_DWORD *)&this->m_par[5][3]._texName[144];
  v16 -= 22;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = v16;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = v16 + 110;
  v19 = *(_DWORD *)&this->m_par[5][3]._texName[132] - 38;
  v42[1] = 546;
  v42[0] = v19;
  this->m_NoteItem[9].m_NotePic.m_childs.m_pData = v17;
  v42[2] = v19 + 256;
  y = this->m_par[5][3]._y;
  this->m_NoteItem[9].m_NotePic.m_childs.capacity = v18 - 5;
  v42[3] = 610;
  (*(void ( **)(float *, int, _DWORD *, SystemUI *))(LODWORD(y) + 16))(&this->m_par[5][3]._y, 161, v42, this);
  ((UIStatic *)&this->m_par[5][3]._y)->CreateFromTemplate();
  LOBYTE(v21) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, SystemUI *, char *, int, int))(*(_DWORD *)&this->m_par[5][0]._texName[12]
                                                                               + 28))(
    &this->m_par[5][0]._texName[12],
    &byte_A00106,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v21);
  v22 = *(_DWORD *)&this->m_par[5][3]._texName[140];
  v23 = *(_DWORD *)&this->m_par[5][3]._texName[132] + 35;
  this->m_NoteItem[9].m_NotePic.m_childs.m_needscriptdel = *(_DWORD *)&this->m_par[5][3]._texName[136] + 5;
  this->m_NoteItem[9].m_NotePic.m_childs.m_nSize = v23;
  v24 = v22 - 36;
  v25 = *(_DWORD *)&this->m_par[5][3]._texName[144];
  v22 -= 22;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = v22;
  v25 -= 5;
  this->m_NoteItem[9].m_NotePic.m_bcreateok = v24;
  this->m_NoteItem[9].m_NotePic.m_bvisible = v25;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = v22 + 110;
  LOBYTE(v25) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, SystemUI *, char *, int, int))(*(_DWORD *)this->m_par[5][0]._element.m_text
                                                                                          + 28))(
    this->m_par[5][0]._element.m_text,
    &byte_A00107,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v25);
  v26 = *(_DWORD *)&this->m_par[5][3]._texName[132];
  v27 = *(_DWORD *)&this->m_par[5][3]._texName[140];
  this->m_NoteItem[9].m_NotePic.m_bfocus = *(_DWORD *)&this->m_par[5][3]._texName[136] + 5;
  v28 = *(_DWORD *)&this->m_par[5][3]._texName[144] - 5;
  this->m_NoteItem[9].m_NotePic.m_benable = v26 + 35;
  this->m_NoteItem[9].m_NotePic.pDebugTex = (gbTexture *)(v27 - 36);
  v29 = *(_DWORD *)&this->m_par[5][2]._texName[220];
  this->m_NoteItem[9].m_NotePic.m_align = v28;
  LOBYTE(v28) = g_bDebugMode;
  (*(void ( **)(char *, char *, char *, SystemUI *, char *, int, int))(v29 + 28))(
    &this->m_par[5][2]._texName[220],
    byte_A00110,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v28);
  H = this->m_par[5][2]._H;
  v31 = *(_DWORD *)&this->m_par[5][3]._texName[140] - 22;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = v31;
  v31 += 110;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = v31;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(int *, char *, char *, SystemUI *, char *, int, int))(H + 28))(
    &this->m_par[5][2]._H,
    byte_A00109,
    &this->m_par[5][3]._texName[132],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v31);
  v32 = *(_DWORD *)&this->m_par[5][3]._texName[136];
  v33 = *(_DWORD *)&this->m_par[5][3]._texName[140] - 36;
  LODWORD(this->m_NoteItem[9].m_NotePic.m_ratiow) = *(_DWORD *)&this->m_par[5][3]._texName[132] + 35;
  bkWndY = this->bkWndY;
  this->m_NoteItem[9].m_NotePic.m_textx = v33;
  bkWndX = this->bkWndX;
  LODWORD(this->m_NoteItem[9].m_NotePic.m_ratioh) = v32 + 5;
  v36 = *(_DWORD *)&this->m_par[5][3]._texName[144];
  bkWndX -= 38;
  *(_DWORD *)&this->m_par[5][3]._texName[136] = bkWndY - 51;
  *(_DWORD *)&this->m_par[5][3]._texName[132] = bkWndX;
  *(_DWORD *)&this->m_par[5][3]._texName[140] = bkWndX + 38;
  v37 = *(_DWORD *)&this->m_par[5][3]._texName[136];
  this->m_NoteItem[9].m_NotePic.m_texty = v36 - 5;
  *(_DWORD *)&this->m_par[5][3]._texName[144] = v37 + 48;
  return sub_445FA0(&this->m_par[5][2]._texName[220]);
}

// 0x004A8150
int SystemUI::ShowPage()
{
  PalScript *v2; // ebx

  v2 = (PalScript *)&this->m_par[5][0]._texName[12];
  if ( g_bRoleFlag1 )
    ((PalScript *)v2)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnSword.tga", g_bDebugMode);
  else
    ((PalScript *)v2)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
  if ( !g_bRoleFlag2 )
    ((PalScript *)this->m_par[5][0]._element.m_text)->OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)this->m_par[5][0]._element.m_text);
  sub_445E50((int)v2);
  sub_445E50((int)&this->m_par[4][4]._element.m_disablepic);
  sub_445E50((int)&this->m_par[4][5]._texName[148]);
  sub_445E50((int)&this->m_par[4][6].m_posx);
  sub_445E50((int)&this->m_par[4][6]._texName[252]);
  sub_445E50((int)&this->m_par[5][1]._texName[116]);
  sub_445E50((int)&this->m_par[5][2]._H);
  return sub_445E50((int)&this->m_par[5][2]._texName[220]);
}

// 0x004A8260
char SystemUI::CreateNoteEntry(
        
        int nVal,
        int nVal2,
        int nVal3,
        char pData,
        int nVal4,
        int nVal5,
        unsigned __int8 a8)
{
  int v8; // ebx
  int v9; // ebp
  int v10; // edi
  char result; // al
  BOOL v13; // edi
  char *m_pData; // eax
  LONG *p_right; // edi
  gbTexture **p_m_pbk2; // ebp
  int v17; // ebx
  int v18; // ebx
  gbTexture **v19; // ebp
  LONG *v20; // edi
  void ( ***v21)(_DWORD, int, BOOL); // ecx
  gbTexture *v22; // edx
  gbTexture **v23; // ecx
  gbTexture **p_m_ppic; // ecx
  bool v25; // zf
  int v26; // eax
  int v27; // [esp+0x98] [ebp-0x18]
  int v28; // [esp+A0h] [ebp-0x10]
  int v29; // [esp+A4h] [ebp-0xC]
  BOOL v30; // [esp+A4h] [ebp-0xC]
  gbTexture **nVala; // [esp+B4h] [ebp+0x4]
  int nVal2a; // [esp+B8h] [ebp+0x8]

  result = g_nFiveNimbusCount;
  if ( g_nFiveNimbusCount != 5 )
  {
    v27 = v10;
    LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) = (_BYTE)nVal == 0;
    v13 = (_BYTE)nVal == 0;
    (*(void ( **)(BOOL, int, int, int))this->m_NoteItem[10].m_HeadShot_NO_SEL[2].m_bvisible)(v13, v27, v9, v8);
    (**(void ( ***)(char *, BOOL))&this->m_NoteItem[9].m_NotePicName.m_text[8])(
      &this->m_NoteItem[9].m_NotePicName.m_text[8],
      v13);
    (*(void ( **)(int *, BOOL))this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible)(
      &this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible,
      v13);
    (*(void ( **)(int *, BOOL))this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)(
      &this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible,
      v13);
    (**(void ( ***)(char *, BOOL))&this->m_NoteItem[9].m_NotePic.m_text[8])(
      &this->m_NoteItem[9].m_NotePic.m_text[8],
      v13);
    if ( g_bUIWnd_DE625A )
      (*(void ( **)(int *, BOOL))this->m_NoteItem[10].m_HeadShot[0].m_bvisible)(
        &this->m_NoteItem[10].m_HeadShot[0].m_bvisible,
        v13);
    (*(void ( **)(float *, BOOL))LODWORD(this->m_NoteItem[10].m_NoteItemBk.m_offsety))(
      &this->m_NoteItem[10].m_NoteItemBk.m_offsety,
      v13);this->pStateUI->ShowWindow(v13);
(**(void ( ***)(char *, BOOL))&this->m_NoteItem[10].m_NoteItemBk.m_caption[48])(
      &this->m_NoteItem[10].m_NoteItemBk.m_caption[48],
      v13);
    (*(void ( **)(float *, BOOL))LODWORD(this->m_NoteItem[10].m_NoteItemBk.m_offsety))(
      &this->m_NoteItem[10].m_NoteItemBk.m_offsety,
      v13);
    this->m_NoteItem[10].m_HeadShot_NO_SEL[0].m_disablepic = (gbTexture *)v13;
    if ( (_BYTE)nVal )
    {
      ((MUIDialog *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor)->InvokeCallback();
      (*(void ( **)(PtrArray *, BOOL))this->m_NoteItem[67].m_HeadShot[1].m_childs.m_pData)(
        &this->m_NoteItem[67].m_HeadShot[1].m_childs,
        v13);
      (*(void ( **)(int *, BOOL))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW)(
        &this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW,
        v13);
    }
    else
    {
      m_pData = this->m_NoteItem[67].m_HeadShot[1].m_childs.m_pData;
      if ( BYTE2(this->m_par[4][0]._element.m_texty) )
      {
        (*(void ( **)(int, int))m_pData)(1, v29);
        (*(void ( **)(int *, _DWORD))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW)(
          &this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW,
          0);
      }
      else
      {
        (*(void ( **)(_DWORD, int))m_pData)(0, v29);
        (*(void ( **)(int *, int))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW)(
          &this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW,
          1);
      }
    }
    this->m_NoteItem[10].m_NoteID.m_ppicInfo = (_PlugInfo *)v13;
    if ( (_BYTE)nVal )
    {
      p_right = &this->m_NoteItem[11].m_NoteLv[0].m_rect.right;
      p_m_pbk2 = &this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2;
      v17 = 5;
      do
      {
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*(p_m_pbk2 - 620))->0)(p_m_pbk2 - 620, 0);
        (*(void ( **)(LONG *, _DWORD))*(p_right - 620))(p_right - 620, 0);
        // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*p_m_pbk2)->0)(p_m_pbk2, 0);
        (*(void ( **)(LONG *, _DWORD))*p_right)(p_right, 0);
        (*(void ( **)(LONG *, _DWORD))p_right[190])(p_right + 190, 0);
        p_m_pbk2 += 86;
        p_right += 38;
        --v17;
      }
      while ( v17 );
      v28 = *(_DWORD *)&this->m_par[4][3]._texName[200];
      *(_DWORD *)&this->m_par[4][3]._texName[204] = 0;
      sprintf(this->buf, "%d/%d", 0, v28);
      ((UICaption *)&this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo)->SetEnable((int)this->buf, 0);
    }
    else
    {
      v18 = 0;
      v19 = &this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2;
      v20 = &this->m_NoteItem[11].m_NoteItemBk.m_rect.right;
      do
      {
        v21 = (void ( ***)(_DWORD, int, BOOL))(v20 + 810);
        if ( *((_BYTE *)&g_nActorState + v18) )
        {
          (**v21)(v21, 1, v30);
          (*(void ( **)(LONG *, _DWORD))v20[620])(v20 + 620, 0);
          (*(void ( **)(LONG *, _DWORD))*v20)(v20, 0);
          // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*v19)->0)(v19, 0);
          v22 = *(v19 - 620);
          v23 = v19 - 620;
          v30 = 0;
        }
        else
        {
          ((void ( *)(void ( ***)(_DWORD, int, BOOL), _DWORD))**v21)(v21, 0);
          if ( *((_BYTE *)&g_nRoleParam + v18) )
          {
            (*(void ( **)(LONG *, _DWORD, BOOL))v20[620])(
              v20 + 620,
              *((unsigned __int8 *)&g_nRoleParam + v18),
              v30);
            // [VTBL_DISPATCH] ((void ( *)(gbTexture **, bool))(*v19)->0)(v19, *((_BYTE *)&g_nRoleParam + v18) == 0);
            (*(void ( **)(LONG *, _DWORD))*v20)(v20, *((unsigned __int8 *)&g_nRoleState + v18 + 1));
            v22 = *(v19 - 620);
            v23 = v19 - 620;
            v30 = *((_BYTE *)&g_nRoleState + v18 + 1) == 0;
          }
          else
          {
            (*(void ( **)(LONG *, _DWORD, BOOL))*v20)(v20, *((unsigned __int8 *)&g_nRoleState + v18 + 1), v30);
            // [VTBL_DISPATCH] ((void ( *)(gbTexture **, bool))(*(v19 - 620))->0)(
              // [VTBL_DISPATCH]   v19 - 620,
              // [VTBL_DISPATCH]   *((_BYTE *)&g_nRoleState + v18 + 1) == 0);
            (*(void ( **)(LONG *, _DWORD))v20[620])(v20 + 620, *((unsigned __int8 *)&g_nRoleParam + v18));
            v22 = *v19;
            v30 = *((_BYTE *)&g_nRoleParam + v18) == 0;
            v23 = v19;
          }
        }
        ((void ( *)(gbTexture **))*((_DWORD *)v22))(v23);
        ++v18;
        v20 += 38;
        v19 += 86;
      }
      while ( v18 < 5 );
    }
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[4].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[4].m_childs.m_nSize,
      (unsigned __int8)pData);
    p_m_ppic = &this->m_NoteItem[67].m_NoteLv[2].m_ppic;
    nVal2a = 5;
    for ( nVala = &this->m_NoteItem[67].m_NoteLv[2].m_ppic; ; p_m_ppic = nVala )
    {
      // [VTBL_DISPATCH] ((void ( *)(gbTexture **, _DWORD))(*p_m_ppic)->0)(p_m_ppic, (unsigned __int8)pData);
      v25 = nVal2a == 1;
      nVala += 86;
      --nVal2a;
      if ( v25 )
        break;
    }
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[0].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[0].m_childs.m_nSize,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[1].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[1].m_childs.m_nSize,
      (unsigned __int8)pData);
    ((void ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[69].m_NoteTime.m_ppicInfo->filepos)(
      &this->m_NoteItem[69].m_NoteTime.m_ppicInfo,
      (unsigned __int8)pData);
    ((void ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[69].m_NotePicName.m_pbkInfo->filepos)(
      &this->m_NoteItem[69].m_NotePicName.m_pbkInfo,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok)(
      &this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok,
      (unsigned __int8)pData);
    (*(void ( **)(PtrArray *, _DWORD))this->m_NoteItem[70].m_NoteMoney.m_childs.m_pData)(
      &this->m_NoteItem[70].m_NoteMoney.m_childs,
      (unsigned __int8)pData);
    (*(void ( **)(void **, _DWORD))this->m_NoteItem[71].m_NoteItemBk.m_id)(
      &this->m_NoteItem[71].m_NoteItemBk.m_id,
      (unsigned __int8)pData);
    ((void ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo->filepos)(
      &this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))this->m_NoteItem[68].m_HeadShot_NO_SEL[2].*((_DWORD *)m_pbk))(
      &this->m_NoteItem[68].m_HeadShot_NO_SEL[2].m_pbk,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))this->m_NoteItem[68].m_HeadShot_NO_SEL[3].*((_DWORD *)m_pbk))(
      &this->m_NoteItem[68].m_HeadShot_NO_SEL[3].m_pbk,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))this->m_NoteItem[68].m_HeadShot_NO_SEL[4].*((_DWORD *)m_pbk))(
      &this->m_NoteItem[68].m_HeadShot_NO_SEL[4].m_pbk,
      (unsigned __int8)pData);
    (**(void ( ***)(char *, _DWORD))&this->m_NoteItem[67].m_NoteLv[1].m_text[8])(
      &this->m_NoteItem[67].m_NoteLv[1].m_text[8],
      (unsigned __int8)pData);
    (*(void ( **)(PtrArray *, _DWORD))this->m_NoteItem[67].m_NoteLv[2].m_childs.m_pData)(
      &this->m_NoteItem[67].m_NoteLv[2].m_childs,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[4].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[4].m_childs.m_nSize,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[2].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[2].m_childs.m_nSize,
      (unsigned __int8)pData);
    this->i = 0;
    do
    {
      (**((void ( ***)(char *, _DWORD))&this->m_NoteItem[68].m_NoteTime.m_childs.m_pData + 38 * this->i))(
        (char *)&this->m_NoteItem[68].m_NoteTime.m_childs + 152 * this->i,
        (unsigned __int8)pData);
      (**((void ( ***)(_PlugInfo **, _DWORD))&this->m_NoteItem[69].m_NoteID.m_disablepicInfo + 38 * this->i))(
        &this->m_NoteItem[69].m_NoteID.m_disablepicInfo + 38 * this->i,
        (unsigned __int8)pData);
      v26 = this->i + 1;
      this->i = v26;
    }
    while ( v26 < 12 );
    (*(void ( **)(float *, _DWORD))LODWORD(this->m_NoteItem[71].m_NoteLv[4].m_ratioh))(
      &this->m_NoteItem[71].m_NoteLv[4].m_ratioh,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))this->m_NoteItem[71].m_NotePicName.*((_DWORD *)m_ppic))(
      &this->m_NoteItem[71].m_NotePicName.m_ppic,
      (unsigned __int8)pData);
    (**(void ( ***)(char *))&this->m_NoteItem[72].m_NoteItemBk.m_caption[104])(&this->m_NoteItem[72].m_NoteItemBk.m_caption[104]);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[72].m_NoteState.m_FVF)(
      &this->m_NoteItem[72].m_NoteState.m_FVF,
      (unsigned __int8)pData);
// [VFTABLE] ((void ( *)(UIWnd **, _DWORD))this->m_NoteItem[72].m_HeadShot_NO_SEL[2].m_pfather->__vftable)(
// [VFTABLE]   &this->m_NoteItem[72].m_HeadShot_NO_SEL[2].m_pfather,
// [VFTABLE]   (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[72].m_HeadShot_NO_SEL[4].m_align)(
      &this->m_NoteItem[72].m_HeadShot_NO_SEL[4].m_align,
      (unsigned __int8)pData);
    ((void ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo->filepos)(
      &this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo,
      (unsigned __int8)pData);
    result = (char)nVala;
    if ( (_BYTE)nVala )
      return ((CCBCamControl *)this)->ShowAllSlots(0);
  }
  return result;
}

// 0x004AC8B0
void SystemUI::ReplaceTextures()
{
  int RoleNum; // eax
  int v3; // esi
  gbColorQuad *p_m_fontcolor; // edi
  int v5; // esi
  float *p_m_ratiow; // edi
  gbTexture *v7; // eax
  char pData; // [esp+0x13] [ebp-0x15] BYREF
  char v9; // [esp+0x14] [ebp-0x14]
  char v10; // [esp+0x15] [ebp-0x13]
  char v11; // [esp+0x16] [ebp-0x12]
  char v12; // [esp+0x17] [ebp-0x11]
  char v13; // [esp+0x18] [ebp-0x10]
  char v14; // [esp+0x19] [ebp-0xF]
  char v15; // [esp+0x1A] [ebp-0xE]
  char v16; // [esp+0x1B] [ebp-0xD]
  char v17; // [esp+0x1C] [ebp-0xC]
  char v18; // [esp+0x1D] [ebp-0xB]
  char v19; // [esp+0x1E] [ebp-0xA]
  char v20; // [esp+0x1F] [ebp-0x9]
  char v21; // [esp+0x20] [ebp-0x8]
  char v22; // [esp+0x21] [ebp-0x7]
  char v23; // [esp+0x22] [ebp-0x6]
  char v24; // [esp+0x23] [ebp-0x5]
  char v25; // [esp+0x24] [ebp-0x4]
  char v26; // [esp+0x25] [ebp-0x3]
  char v27; // [esp+0x26] [ebp-0x2]
  char v28; // [esp+0x27] [ebp-0x1]

  switch ( g_nFiveNimbusCount )
  {
    case 0:
      ((UIStatic *)&this->m_NoteItem[9].m_NotePicName.m_text[8])->CreateFromTemplate();
      if ( gbColorQuad::ColorQuadFmt )
      {
        v11 = -7;
        v10 = -34;
        v9 = -102;
      }
      else
      {
        v11 = -102;
        v10 = -34;
        v9 = -7;
      }
      v12 = -1;
      goto LABEL_21;
    case 1:
      ((UIStatic *)&this->m_NoteItem[9].m_NotePicName.m_text[8])->CreateFromTemplate();
      if ( gbColorQuad::ColorQuadFmt )
      {
        v15 = -72;
        v14 = -71;
        v13 = -1;
      }
      else
      {
        v14 = -71;
        v15 = -1;
        v13 = -72;
      }
      v16 = -1;
      goto LABEL_21;
    case 2:
      ((UIStatic *)&this->m_NoteItem[9].m_NotePicName.m_text[8])->CreateFromTemplate();
      if ( gbColorQuad::ColorQuadFmt )
      {
        v19 = -1;
        v18 = -73;
        v17 = -54;
      }
      else
      {
        v19 = -54;
        v18 = -73;
        v17 = -1;
      }
      v20 = -1;
      goto LABEL_21;
    case 3:
      ((UIStatic *)&this->m_NoteItem[9].m_NotePicName.m_text[8])->CreateFromTemplate();
      if ( gbColorQuad::ColorQuadFmt )
      {
        v23 = -48;
        v22 = -1;
        v24 = -1;
        v21 = -73;
      }
      else
      {
        v23 = -73;
        v22 = -1;
        v24 = -1;
        v21 = -48;
      }
      goto LABEL_21;
    case 4:
      ((UIStatic *)&this->m_NoteItem[9].m_NotePicName.m_text[8])->CreateFromTemplate();
      if ( gbColorQuad::ColorQuadFmt )
      {
        v27 = -73;
        v26 = -20;
        v25 = -1;
      }
      else
      {
        v26 = -20;
        v27 = -1;
        v25 = -73;
      }
      v28 = -1;
LABEL_21:
      sub_446010(&this->m_NoteItem[9].m_NotePic.m_text[8]);
      break;
    default:
      break;
  }
  RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*((int *)&Buffer.m_partyActor.m_fSpeed + 3));
  ((UICaption *)&this->m_NoteItem[9].m_NotePic.m_text[8])->SetEnable(RoleNum + 28, 0);
  (**(void ( ***)(char *, int))&this->m_NoteItem[9].m_NotePic.m_text[8])(
    &this->m_NoteItem[9].m_NotePic.m_text[8],
    1);
  ((PalScriptWaitObj *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor)->ReleaseObject("UI\\GameMainUI\\Sword\\Data\\J131Src.tga");
  ((TextureLib *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor)->LoadTexture(pszPath);
  v3 = 0;
  p_m_fontcolor = &this->m_NoteItem[67].m_HeadShot[4].m_fontcolor;
  do
  {
    ((TextureLib *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor)->CreateFromFile();
    ++v3;
    p_m_fontcolor += 4;
  }
  while ( v3 < 5 );
  v5 = 0;
  p_m_ratiow = &this->m_NoteItem[67].m_HeadShot[3].m_ratiow;
  do
  {
    ((TextureLib *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor)->CreateFromFile();
    ++v5;
    p_m_ratiow += 4;
  }
  while ( v5 < 5 );
  pData = 0;
  v7 = ((TextureLib *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor)->CreateFromMemory(&pData, 1, 1);
  ((gbGeomNode *)this->m_NoteItem[10].m_NoteID.m_pbk2)->ReplaceTexture(v7);
}

// 0x004ACC10
int SystemUI::InitSlotEffects(int nVal)
{
  char *v4; // edi
  int *v5; // ebx
  int v6; // esi
  int *p_par_radiusY; // ebp
  int v8; // eax
  int v9; // eax
  int *v10; // edi
  int *v11; // esi
  bool v12; // zf
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fXb; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  char *v19; // [esp+0x18] [ebp-0xC]
  int v20; // [esp+0x1C] [ebp-0x8]
  int nVala; // [esp+0x28] [ebp+0x4]

  this->m_NoteItem[9].m_NotePic.m_fonttype = 0;
  *(_DWORD *)this->m_NoteItem[9].m_NotePic.m_text = 0;
  nVala = 16;
  *((_BYTE *)&this->m_NoteItem[9].m_NotePic.m_fonttype + nVal) = 1;
  v4 = (char *)this + 16 * nVal;
  v5 = (int *)(v4 + 177288);
  v6 = *((_DWORD *)&this->m_NoteItem[9].m_NoteLv[4].m_ppicInfo + 4 * nVal) - *((_DWORD *)v4 + 44322);
  v19 = v4;
  v20 = v6;
  p_par_radiusY = &this->m_par[5][16 * nVal + 4].par_radiusY;
  while ( 1 )
  {
    ((RenderTarget *)p_par_radiusY)->LoadTexture(szFilename);
    ((RenderTarget *)p_par_radiusY)->SetSize(32);
    fY = rand() % 10 + 238;
    fX = rand() % 10 + 68;
    v8 = rand();
    ((RenderTarget *)p_par_radiusY)->SetColor(v8 % 10 - 88, fX, fY);
    v9 = rand();
    ((RenderTarget *)p_par_radiusY)->SetAlpha(v9 % 55 - 56);
    *((_BYTE *)p_par_radiusY + 104) = 1;
    ((RenderTarget *)p_par_radiusY)->SetField084();
    ((RenderTarget *)p_par_radiusY)->SetState();
    fYa = (float)*((int *)v4 + 44323);
    fXa = (float)(*v5 + rand() % v6);
    ((RenderTarget *)p_par_radiusY)->UpdateTransform(fXa, fYa);
    ((RenderTarget *)p_par_radiusY)->Render(*v5, v5[1], v5[2]);
    rand();
    *(float *)&fXb = (float)(rand() % 2 + 1);
    ((RenderTarget *)p_par_radiusY)->SetOffset(fXb);
    ((RenderTarget *)p_par_radiusY)->SetScale(0);
    ((RenderTarget *)p_par_radiusY)->SetVisible(1);
    v10 = p_par_radiusY + 18688;
    v11 = p_par_radiusY;
    p_par_radiusY += 146;
    result = nVala - 1;
    v12 = nVala == 1;
    qmemcpy(v10, v11, 0x248u);
    --nVala;
    if ( v12 )
      break;
    v4 = v19;
    v6 = v20;
  }
  return result;
}

// 0x004ACDE0
int SystemUI::UpdateNoteScroll()
{
  int v2; // ebx
  char *v3; // ebp
  void **p_m_id; // esi
  int v5; // eax
  int v6; // eax
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x28]
  float fXa; // [esp+0x0] [ebp-0x28]
  int fXb; // [esp+0x0] [ebp-0x28]
  int fXc; // [esp+0x0] [ebp-0x28]
  int v12; // [esp+0x4] [ebp-0x24]
  LONG right; // [esp+0x18] [ebp-0x10]
  int v14; // [esp+0x18] [ebp-0x10]
  float fY; // [esp+0x20] [ebp-0x8]
  int v16; // [esp+0x24] [ebp-0x4]

  v2 = this->m_NoteItem[39].m_NoteLv[2].m_rect.bottom - this->m_NoteItem[39].m_NoteLv[2].m_rect.top;
  right = this->m_NoteItem[39].m_NoteLv[2].m_rect.right;
  v3 = (char *)this->m_NoteItem[39].m_NoteLv[2].m_pfather - right;
  fY = (float)right;
  p_m_id = &this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id;
  v14 = 168;
  do
  {
    v16 = this->m_NoteItem[39].m_NoteLv[2].m_rect.top + rand() % (v2 / 2);
    ((RenderTarget *)p_m_id)->LoadTexture("UI\\GameMainUI\\Par_Effect\\star.tga");
    ((RenderTarget *)p_m_id)->SetSize(32);
    v12 = rand() % 10 + 38;
    fX = rand() % 10 + 98;
    v5 = rand();
    ((RenderTarget *)p_m_id)->SetColor(v5 % 10 - 34, fX, v12);
    v6 = rand();
    ((RenderTarget *)p_m_id)->SetAlpha(v6 % 46 - 58);
    ((RenderTarget *)p_m_id)->SetField084();
    ((RenderTarget *)p_m_id)->SetState();
    fXa = (float)v16;
    ((RenderTarget *)p_m_id)->UpdateTransform(fXa, fY);
    ((RenderTarget *)p_m_id)->CalcRenderDimensions(v2, (int)v3);
    rand();
    *(float *)&fXb = (float)(rand() % 6 + 5);
    ((RenderTarget *)p_m_id)->SetOffset(fXb);
    rand();
    *(float *)&fXc = (float)(rand() % 6 + 6);
    ((RenderTarget *)p_m_id)->SetScale(fXc);
    ((RenderTarget *)p_m_id)->SetVisible(1);
    p_m_id += 146;
    result = --v14;
  }
  while ( v14 );
  return result;
}

// 0x004ACF90
int SystemUI::UpdateNoteScrollAlt()
{
  int v2; // ebx
  char *v3; // ebp
  PtrArray *p_m_childs; // esi
  int v5; // eax
  int v6; // eax
  int result; // eax
  int fX; // [esp+0x0] [ebp-0x28]
  float fXa; // [esp+0x0] [ebp-0x28]
  int fXb; // [esp+0x0] [ebp-0x28]
  int fXc; // [esp+0x0] [ebp-0x28]
  int v12; // [esp+0x4] [ebp-0x24]
  LONG right; // [esp+0x18] [ebp-0x10]
  int v14; // [esp+0x18] [ebp-0x10]
  float fY; // [esp+0x20] [ebp-0x8]
  int v16; // [esp+0x24] [ebp-0x4]

  v2 = this->m_NoteItem[39].m_NoteLv[2].m_rect.bottom - this->m_NoteItem[39].m_NoteLv[2].m_rect.top;
  right = this->m_NoteItem[39].m_NoteLv[2].m_rect.right;
  v3 = (char *)this->m_NoteItem[39].m_NoteLv[2].m_pfather - right;
  fY = (float)right;
  p_m_childs = &this->m_NoteItem[39].m_NoteLv[2].m_childs;
  v14 = 168;
  do
  {
    v16 = this->m_NoteItem[39].m_NoteLv[2].m_rect.top + rand() % (v2 / 2);
    ((RenderTarget *)p_m_childs)->LoadTexture(szFilename);
    ((RenderTarget *)p_m_childs)->SetSize(32);
    v12 = rand() % 10 + 98;
    fX = rand() % 10 + 188;
    v5 = rand();
    ((RenderTarget *)p_m_childs)->SetColor(v5 % 10 + 68, fX, v12);
    v6 = rand();
    ((RenderTarget *)p_m_childs)->SetAlpha(v6 % 10 - 28);
    ((RenderTarget *)p_m_childs)->SetField084();
    ((RenderTarget *)p_m_childs)->SetState();
    fXa = (float)v16;
    ((RenderTarget *)p_m_childs)->UpdateTransform(fXa, fY);
    ((RenderTarget *)p_m_childs)->CalcRenderDimensions(v2, (int)v3);
    rand();
    *(float *)&fXb = (float)(rand() % 5 + 1);
    ((RenderTarget *)p_m_childs)->SetOffset(fXb);
    rand();
    *(float *)&fXc = (float)(rand() % 6 + 1);
    ((RenderTarget *)p_m_childs)->SetScale(fXc);
    ((RenderTarget *)p_m_childs)->SetVisible(1);
    p_m_childs = (PtrArray *)((char *)p_m_childs + 584);
    result = --v14;
  }
  while ( v14 );
  return result;
}

// 0x004AD140
void SystemUI::ProcessFrame()
{
  char *v2; // ebp
  int v3; // edi
  gbTexture *TickCount; // eax
  gbTexture *v5; // eax
  unsigned int v6; // ecx
  unsigned __int8 v7; // dl
  int v8; // eax
  int v9; // eax
  void **p_m_id; // edi
  int v11; // ebx
  int i; // edi
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int fY; // [esp+0x4] [ebp-0x20]
  float fYa; // [esp+0x4] [ebp-0x20]
  CCBMagicWindow *v17; // [esp+0x10] [ebp-0x14]
  LONG right; // [esp+0x1C] [ebp-0x8]
  int v19; // [esp+0x20] [ebp-0x4]

  ((CCBControlWindow *)this)->Render(v17);
  if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
  {
    if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) && *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 1) )
    {
      right = this->m_NoteItem[39].m_NoteLv[2].m_rect.right;
      v2 = (char *)this->m_NoteItem[39].m_NoteLv[2].m_pfather - right;
      v3 = this->m_NoteItem[39].m_NoteLv[2].m_rect.bottom - this->m_NoteItem[39].m_NoteLv[2].m_rect.top;
      if ( !LOBYTE(this->m_NoteItem[67].m_NoteLv[0].m_pbk2) )
      {
        TickCount = (gbTexture *)GetTickCount();
        this->m_NoteItem[67].m_NoteLv[0].m_disablepic = TickCount;
        this->m_NoteItem[67].m_NoteLv[0].m_disablepicInfo = (_PlugInfo *)TickCount;
        LOBYTE(this->m_NoteItem[67].m_NoteLv[0].m_pbk2) = 1;
      }
      v5 = (gbTexture *)GetTickCount();
      v6 = (char *)v5 - (char *)this->m_NoteItem[67].m_NoteLv[0].m_disablepicInfo;
      this->m_NoteItem[67].m_NoteLv[0].m_disablepic = v5;
      if ( v6 > 0x7D0 )
      {
        this->m_NoteItem[67].m_NoteLv[0].m_disablepicInfo = (_PlugInfo *)v5;
        LOBYTE(this->m_NoteItem[67].m_NoteLv[0].m_pbk2) = 0;
        *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 3) = *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 3) == 0;
      }
      if ( *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 3) )
      {
// [IDA_MISID]         if ( !((Concurrency *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->details::VirtualProcessor::IsThrottled() )
        {
          v19 = this->m_NoteItem[39].m_NoteLv[2].m_rect.top + rand() % (v3 / 2);
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->LoadTexture("UI\\GameMainUI\\Par_Effect\\flare.tga");
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetSize(32);
          if ( HIBYTE(this->m_par[4][0]._element.m_texty) )
          {
            fY = rand() % 10 + 224;
            fX = rand() % 10 + 84;
            v7 = rand() % 10 - 118;
          }
          else
          {
            fY = rand() % 10 + 58;
            fX = rand() % 10 + 128;
            v7 = rand() % 10 - 58;
          }
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetColor(v7, fX, fY);
          v8 = rand();
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetAlpha(v8 % 25 - 26);
          rand();
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                                                   + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetField084();
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                                                + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetState();
          fYa = (float)right;
          fXa = (float)v19;
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->UpdateTransform(fXa, fYa);
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->CalcRenderDimensions(v3, (int)v2);
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetOffset(1084227584);
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetScale(1086324736);
          ((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF))->SetVisible(1);
        }
        v9 = this->m_NoteItem[67].m_NoteLv[0].m_FVF + 1;
        this->m_NoteItem[67].m_NoteLv[0].m_FVF = v9;
        if ( v9 >= 168 )
          this->m_NoteItem[67].m_NoteLv[0].m_FVF = 0;
      }
      p_m_id = &this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id;
      v11 = 168;
      do
      {
// [IDA_MISID]         if ( ((Concurrency *)(p_m_id + 24532))->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)(p_m_id + 24532))->Apply();
// [IDA_MISID]         if ( ((Concurrency *)p_m_id)->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)p_m_id)->Apply();
        p_m_id += 146;
        --v11;
      }
      while ( v11 );
    }
    if ( *((_BYTE *)&this->m_NoteItem[9].m_NotePic.m_fonttype + *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4]) )
    {
      for ( i = 0; i < 16; ++i )
      {
// [IDA_MISID]         if ( ((Concurrency *)&this->m_par[5][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] + 4 + i].par_radiusY)->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)&this->m_par[5][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4]
                                                            + 4
                                                            + i].par_radiusY)->Apply();
// [IDA_MISID]         if ( ((Concurrency *)&this->m_par2[7][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] + 4 + i]._texName[140])->details::VirtualProcessor::IsThrottled() )
          ((ScreenEffect *)&this->m_par2[7][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4]
                                                             + 4
                                                             + i]._texName[140])->Apply();
      }
    }
  }
}

// 0x004AD540
BOOL SystemUI::UpdateSwordDisplay(int nVal, int nVal2)
{
  gbTexture *v4; // eax
  __int64 v5; // rax
  int v6; // edi
  int v7; // ebp
  int v8; // edx
  int State; // eax
  char *m_pData; // eax
  void ( **m_nTextW)(int *); // edx
  int *p_m_nTextW; // ecx
  CScreenMode *Instance; // eax
  bool v14; // sf
  int v15; // eax
  __int64 v16; // rax
  void *m_id; // ecx
  double v18; // st7
  gbTexture **p_m_pbk; // edi
  int v20; // ebx
  __int64 v21; // rax
  int v22; // ebx
  __int64 v23; // rax
  gbTexture *v24; // edi
  char *v25; // eax
  const void *v27; // [esp+0x0] [ebp-0x2C]
  int value; // [esp+0x4] [ebp-0x28]
  float valuea; // [esp+0x4] [ebp-0x28]
  float valueb; // [esp+0x4] [ebp-0x28]
  int v31; // [esp+0x8] [ebp-0x24]
  int v32; // [esp+0x8] [ebp-0x24]
  int v33; // [esp+0xC] [ebp-0x20]
  char v34; // [esp+0x10] [ebp-0x1C]
  int v35; // [esp+0x14] [ebp-0x18]
  int v36; // [esp+0x18] [ebp-0x14] BYREF
  gbTexture *m_pbk; // [esp+0x1C] [ebp-0x10]
  _DWORD p_DWORD[3]; // [esp+0x20] [ebp-0xC] BYREF

  HIBYTE(v36) = 0;
  v4 = ((TextureLib *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor)->CreateFromMemory((_BYTE *)&v36 + 3, 5, 0);
  if ( HIBYTE(v36) && v4 )
    ((gbGeomNode *)this->m_NoteItem[10].m_NoteID.m_pbk2)->ReplaceTexture(v4);
  v5 = (__int64)g_fGameTimer;
  v6 = (int)v5 / 3600;
  v7 = (int)v5 / 60 % 60;
  v8 = (int)v5 % 60;
  if ( (int)v5 / 3600 < 100 )
    sprintf(this->buf, "%02d:%02d:%02d", v6, v7, v8);
  else
    sprintf(this->buf, "%03d:%02d:%02d", v6, v7, v8);
  ((UICaption *)&this->m_par[5][3]._texName[148])->SetEnable((int)this->buf, 0);
  sprintf(this->buf, &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)&this->m_par[5][3]._element.m_childs.capacity)->SetEnable((int)this->buf, 0);
  State = ((UIParabolaCtrl *)&this->m_NoteItem[72].m_NoteLv[3].m_nTextW)->GetState();
  if ( State )
  {
    if ( State == 1 )
    {
      v15 = dword_C10CC4 - 1;
      v14 = dword_C10CC4 - 1 < 0;
      *((_BYTE *)&g_nActorState + g_nFiveNimbusCount) = 0;
      dword_C10CC4 = v15;
      if ( v14 )
        dword_C10CC4 = 0;
    }
  }
  else
  {
    ((SwordUI *)this)->RenderSword();
    --*(_DWORD *)&this->m_IsMsg;
    p_DWORD[2] = 0;
    p_DWORD[0] = 6408;
    p_DWORD[1] = 1;
    ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->PassCmd(p_DWORD);
    sprintf(this->buf, "%s %d", (const char *)dword_DC943C, *(_DWORD *)&this->m_IsMsg);
    ((UICaption *)&this->pStateUI)->SetEnable((int)this->buf, 0);
    if ( *((_BYTE *)&g_nActorState + g_nFiveNimbusCount) )
    {
      (**((void ( ***)(gbTexture **, _DWORD))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount,
        0);
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
// [VFTABLE] (**((void ( ***)(char *, _DWORD))&this->m_NoteItem[10].m_HeadShot[3].__vftable + 86 * g_nFiveNimbusCount))(
// [VFTABLE]   (char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount,
// [VFTABLE]   0);
      (**((void ( ***)(LONG *, _DWORD))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right
        + 38 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount,
        0);
// [VFTABLE] (**((void ( ***)(char *, _DWORD))&this->m_NoteItem[10].m_HeadShot[3].__vftable + 86 * g_nFiveNimbusCount))(
// [VFTABLE]   (char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount,
// [VFTABLE]   0);
      (**((void ( ***)(LONG *, _DWORD))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right
        + 38 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount,
        0);
      (**((void ( ***)(gbTexture **, _DWORD))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount,
        0);
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
      (**((void ( ***)(LONG *, int))&this->m_NoteItem[11].m_NotePic.m_rect.right + 38 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_NotePic.m_rect.right + 38 * g_nFiveNimbusCount,
        1);
      *((_BYTE *)&g_nActorState + g_nFiveNimbusCount) = 1;
    }
    else if ( *((_BYTE *)&g_nRoleState + g_nFiveNimbusCount + 1) )
    {
      (**((void ( ***)(gbTexture **, _DWORD))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount,
        0);
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
// [VFTABLE] (**((void ( ***)(char *, _DWORD))&this->m_NoteItem[10].m_HeadShot[3].__vftable + 86 * g_nFiveNimbusCount))(
// [VFTABLE]   (char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount,
// [VFTABLE]   0);
      (**((void ( ***)(LONG *, int))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount,
        1);
      *((_BYTE *)&g_nRoleParam + g_nFiveNimbusCount) = 1;
    }
    else
    {
      (**((void ( ***)(gbTexture **, int))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount,
        1);
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
// [VFTABLE] (**((void ( ***)(char *, _DWORD))&this->m_NoteItem[10].m_HeadShot[3].__vftable + 86 * g_nFiveNimbusCount))(
// [VFTABLE]   (char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount,
// [VFTABLE]   0);
      (**((void ( ***)(LONG *, _DWORD))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right
        + 38 * g_nFiveNimbusCount))(
        &this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount,
        0);
      if ( HIBYTE(this->m_par[4][0]._element.m_texty) )
        *((_BYTE *)&g_nRoleParam + g_nFiveNimbusCount) = 1;
      else
        *((_BYTE *)&g_nRoleState + g_nFiveNimbusCount + 1) = 1;
    }
    this->CreateNoteEntry(0, v31, v33, v34, v35, v36, (unsigned __int8)m_pbk);
    ((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo)->ClearAll();
    ((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo)->GetItem();
    m_pData = this->m_NoteItem[67].m_HeadShot[1].m_childs.m_pData;
    if ( HIBYTE(this->m_par[4][0]._element.m_texty) )
    {
      (*(void ( **)(int, int))m_pData)(1, v32);
      m_nTextW = (void ( **)(int *))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      p_m_nTextW = &this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      v31 = 0;
    }
    else
    {
      (*(void ( **)(_DWORD, int))m_pData)(0, v32);
      m_nTextW = (void ( **)(int *))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      p_m_nTextW = &this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      v31 = 1;
    }
    (*m_nTextW)(p_m_nTextW);
    value = *(_DWORD *)&this->m_par[4][3]._texName[200];
    *((_DWORD *)&this->m_Frame + 38) = 0;
    this->m_Frame.m_nTextW = 0;
    this->m_TimeMoney.m_wndcolor.Color = 0;
    this->m_TimeMoney.m_fontcolor.Color = 0;
// [VFTABLE] this->m_TimeMoney.__vftable = 0;
    *((_DWORD *)&this->m_Frame + 39) = 0;
    this->m_TimeMoney.m_rect.left = 0;
    this->m_TimeMoney.m_id = 0;
    *(_DWORD *)&this->m_par[4][3]._texName[204] = 0;
    sprintf(this->buf, "%d/%d", 0, value);
    ((UICaption *)&this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo)->SetEnable((int)this->buf, 0);
    memset(&this->m_par[4][0]._element.m_text[12], 0, 0x630u);

    v27 = off_5CF220;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v27, 1);
  }
  if ( LOBYTE(this->m_par[4][0]._element.m_texty) )
  {
    if ( this->m_NoteItem[67].m_NoteLv[0].m_mouseoff )
    {
      v16 = (__int64)((double)(int)this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color - *(float *)&nVal * 500.0);
      m_id = this->m_NoteItem[67].m_NoteLv[1].m_id;
      this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color = v16;
      if ( (int)v16 <= (int)m_id )
        this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color = (unsigned int)m_id;
      valuea = (float)(int)this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color;
      ((CCBFiveNimbusWindow *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetFloatParam(valuea);
    }
    if ( *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 2) )
    {
      v18 = *(float *)&nVal * 460.0 + *(float *)&this->m_par[4][0]._element.m_text[8];
      *(float *)&this->m_par[4][0]._element.m_text[8] = v18;
      if ( v18 >= 0.0 )
        *(_DWORD *)&this->m_par[4][0]._element.m_text[8] = 0;
      *(_DWORD *)&this->m_NoteItem[10].m_NoteState.m_mouseoff = 1;
      ((UIPushButton *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetParam(*(_DWORD *)&this->m_par[4][0]._element.m_text[8]);
      if ( *(float *)&this->m_par[4][0]._element.m_text[8] == 0.0 )
      {
        *(_DWORD *)&this->m_NoteItem[10].m_NoteState.m_mouseoff = 98;
        ((UIPushButton *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetParam(0);
        ((UIPushButton *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetAnimOffset(2, *(_DWORD *)&this->m_par[4][0]._element.m_text[4], *(float *)&v31);
        LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) = 1;
        this->m_NoteItem[67].m_NoteLv[0].m_mouseoff = 0;
        *(_WORD *)(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 1) = 1;

        valueb = (float)(int)this->m_NoteItem[67].m_NoteLv[1].m_id;
        ((CCBFiveNimbusWindow *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetFloatParam(valueb);
      }
    }
    if ( this->m_NoteItem[10].m_HeadShot[2].m_nTextW )
    {
      p_m_pbk = &this->m_NoteItem[10].m_HeadShot[2].m_pbk;
      HIWORD(v20) = 0;
      m_pbk = this->m_NoteItem[10].m_HeadShot[2].m_pbk;
      LOWORD(v20) = this->m_NoteItem[10].m_HeadShot[2].m_FVF;
      if ( (int)m_pbk > (unsigned __int16)v20 )
      {
        v21 = (__int64)((double)(int)m_pbk - *(float *)&nVal * 220.0);
        *p_m_pbk = (gbTexture *)v21;
        if ( (int)v21 <= v20 )
          *p_m_pbk = (gbTexture *)v20;
        this->m_NoteItem[10].m_HeadShot[2].m_ppic = (gbTexture *)((char *)*p_m_pbk + 218);
LABEL_41:
        sub_445FA0(&this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible);
        v24 = *p_m_pbk;
        v25 = &this->m_NoteItem[10].m_HeadShot[2].m_pbkInfo->name[32];
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[4] = v25;
        *(_DWORD *)this->m_NoteItem[10].m_HeadShot[2].m_text = v24 + 4;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[8] = (char *)v24 + 212;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[12] = v25 + 326;
        sub_445FA0(&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
      }
    }
    else
    {
      p_m_pbk = &this->m_NoteItem[10].m_HeadShot[2].m_pbk;
      HIWORD(v22) = 0;
      m_pbk = this->m_NoteItem[10].m_HeadShot[2].m_pbk;
      LOWORD(v22) = HIWORD(this->m_NoteItem[10].m_HeadShot[2].m_FVF);
      if ( (int)m_pbk < (unsigned __int16)v22 )
      {
        v23 = (__int64)(*(float *)&nVal * 220.0 + (double)(int)m_pbk);
        *p_m_pbk = (gbTexture *)v23;
        if ( (int)v23 >= v22 )
          *p_m_pbk = (gbTexture *)v22;
        this->m_NoteItem[10].m_HeadShot[2].m_ppic = (gbTexture *)((char *)*p_m_pbk + 218);
        goto LABEL_41;
      }
    }
  }
  return ((UIListBox *)this)->Update(nVal, nVal2);
}

// 0x004ADC30
int SystemUI::InitScreenUI(int nVal, UIWnd *pWnd, int nVal2, char *pszBuf, int nVal3)
{
  int i; // edi
  int *v8; // eax
  void ( **m_bvisible)(int *, _DWORD); // eax
  char *m_pData; // eax
  int v11; // eax
  char *v12; // eax
  void **v13; // ecx
  int result; // eax
  UIWnd *v15; // ecx
  const char **v16; // ebx
  gbTexture **p_m_ppic; // edi
  int v18; // ebp
  CScreenMode *Instance; // eax
  int v20; // eax
  CScreenMode *v21; // eax
  CScreenMode *v22; // eax
  CScreenMode *v23; // eax
  CScreenMode *v24; // eax
  const char *v25; // ecx
  CScreenMode *v26; // eax
  CScreenMode *v27; // eax
  CScreenMode *v28; // eax
  CScreenMode *v29; // eax
  CScreenMode *v30; // eax
  CScreenMode *v31; // eax
  CScreenMode *v32; // eax
  CScreenMode *v33; // eax
  CScreenMode *v34; // eax
  CScreenMode *v35; // eax
  CScreenMode *v36; // eax
  CScreenMode *v37; // eax
  CScreenMode *v38; // eax
  CScreenMode *v39; // eax
  CScreenMode *v40; // eax
  CScreenMode *v41; // eax
  void ( **m_nTextW)(int *, _DWORD); // eax
  void ( **v43)(int *, int); // edx
  CScreenMode *v44; // eax
  CScreenMode *v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int RoleNum; // eax
  Parent_Data *m_fonttype; // eax
  int v51; // eax
  UIListBox *p_m_ppicInfo; // edi
  Parent_Data *Child; // eax
  Parent_Data *v54; // eax
  Parent_Data *v55; // eax
  Parent_Data *v56; // eax
  Parent_Data *v57; // eax
  int ItemData; // ebx
  _PlugInfo **p_m_pbkInfo; // ebp
  int LockedSel; // edi
  int v61; // eax
  _PlugInfo **v62; // ecx
  int v63; // esi
  const char *v64; // [esp-0x8] [ebp-ACh]
  const char *v65; // [esp-0x8] [ebp-ACh]
  const void *v66; // [esp-0x8] [ebp-ACh]
  const void *v67; // [esp-0x8] [ebp-ACh]
  const char *v68; // [esp-0x8] [ebp-ACh]
  const char *v69; // [esp-0x8] [ebp-ACh]
  const char *v70; // [esp-0x8] [ebp-ACh]
  const char *v71; // [esp-0x8] [ebp-ACh]
  const char *v72; // [esp-0x8] [ebp-ACh]
  const char *v73; // [esp-0x8] [ebp-ACh]
  const char *v74; // [esp-0x8] [ebp-ACh]
  const char *v75; // [esp-0x8] [ebp-ACh]
  const char *v76; // [esp-0x8] [ebp-ACh]
  const char *v77; // [esp-0x8] [ebp-ACh]
  const char *v78; // [esp-0x8] [ebp-ACh]
  const char *v79; // [esp-0x8] [ebp-ACh]
  const char *v80; // [esp-0x8] [ebp-ACh]
  const char *v81; // [esp-0x8] [ebp-ACh]
  const char *v82; // [esp-0x8] [ebp-ACh]
  const char *v83; // [esp-0x8] [ebp-ACh]
  const char *v84; // [esp-0x8] [ebp-ACh]
  const char *v85; // [esp-0x8] [ebp-ACh]
  const char *v86; // [esp-0x8] [ebp-ACh]
  int v87; // [esp-0x4] [ebp-A8h]
  int v88; // [esp+0x0] [ebp-A4h]
  int v89; // [esp+0x4] [ebp-A0h]
  char v90; // [esp+0x8] [ebp-0x9C]
  int v91; // [esp+0xC] [ebp-0x98]
  _BYTE String1[12]; // [esp+0x10] [ebp-0x94] BYREF
  int a2; // [esp+0x1C] [ebp-0x88]
  int v94; // [esp+0x20] [ebp-0x84]
  char Buffer[125]; // [esp+0x24] [ebp-0x80] BYREF
  __int16 v96; // [esp+A1h] [ebp-0x3]
  char v97; // [esp+A3h] [ebp-0x1]

  switch ( nVal )
  {
    case 1000:
      if ( pWnd )
      {
        for ( i = 0; i < 8; ++i )
          this->InitSlotEffects(i);
        this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 0;


        *(_DWORD *)&String1[4] = 0;
        *(_DWORD *)&String1[8] = 0;
        *(_DWORD *)String1 = 6408;
        v8 = ((CCBStageRole *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetByIndex((int *)String1);
        if ( v8 )
          *(_DWORD *)&this->m_IsMsg = v8[1];
        else
          *(_DWORD *)&this->m_IsMsg = 0;
        sprintf(this->buf, "%s %d", (const char *)dword_DC943C, *(_DWORD *)&this->m_IsMsg);
        ((UICaption *)&this->pStateUI)->SetEnable((int)this->buf, 0);
        *((_DWORD *)&this->m_Frame + 38) = 0;
        m_bvisible = (void ( **)(int *, _DWORD))this->m_NoteItem[10].m_HeadShot[0].m_bvisible;
        this->m_Frame.m_nTextW = 0;
        this->m_TimeMoney.m_wndcolor.Color = 0;
        this->m_TimeMoney.m_fontcolor.Color = 0;
// [VFTABLE] this->m_TimeMoney.__vftable = 0;
        *((_DWORD *)&this->m_Frame + 39) = 0;
        this->m_TimeMoney.m_rect.left = 0;
        this->m_TimeMoney.m_id = 0;
        (*m_bvisible)(&this->m_NoteItem[10].m_HeadShot[0].m_bvisible, g_bUIWnd_DE625A);
        this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color = 1000;
        ((CCBFiveNimbusWindow *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetFloatParam(1000.0);
        this->CreateNoteEntry(0, v88, v89, v90, v91, *(int *)String1, String1[4]);
        m_pData = this->m_NoteItem[67].m_HeadShot[1].m_childs.m_pData;
        LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) = 0;
        HIBYTE(this->m_par[4][0]._element.m_texty) = 1;
        (*(void ( **)(PtrArray *, int))m_pData)(&this->m_NoteItem[67].m_HeadShot[1].m_childs, 1);
        (*(void ( **)(int *, _DWORD))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW)(
          &this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW,
          0);
        v11 = g_nFiveNimbusCount;
        if ( g_nFiveNimbusCount >= 5 )
        {
          v11 = 3;
          g_nFiveNimbusCount = 3;
        }
        this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_fonttype = (Parent_Data *)v11;
        if ( ::Buffer.m_partyActor.m_dwMatMsg[8] )
          this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] = *(_DWORD *)::Buffer.m_partyActor.m_dwMatMsg[8] == 6603;
        else
          this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] = 0;
        this->m_NoteItem[10].m_HeadShot[2].m_pbk = this->m_NoteItem[10].m_HeadShot[2].m_disablepic;
        this->m_NoteItem[10].m_HeadShot[2].m_pbkInfo = this->m_NoteItem[10].m_HeadShot[2].m_disablepicInfo;
        this->m_NoteItem[10].m_HeadShot[2].m_ppic = this->m_NoteItem[10].m_HeadShot[2].m_pbk2;
        this->m_NoteItem[10].m_HeadShot[2].m_ppicInfo = *(_PlugInfo **)&this->m_NoteItem[10].m_HeadShot[2].m_mouseoff;
        sub_445FA0(&this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible);
        v12 = &this->m_NoteItem[10].m_HeadShot[2].m_pbkInfo->name[32];
        v13 = &this->m_NoteItem[10].m_HeadShot[2].*((_DWORD *)m_pbk) + 4;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[4] = v12;
        *(_DWORD *)this->m_NoteItem[10].m_HeadShot[2].m_text = v13;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[8] = v13 + 49;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[12] = v12 + 326;
        sub_445FA0(&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
        if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
        {
          this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 1;
          ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&g_ComposeRecipeTable[256], 0);
        }
        else
        {
          this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 0;
          ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)g_szSceneUIText, 0);
        }
        this->m_NoteItem[9].m_NotePic.m_fonttype = 0;
        *(_DWORD *)this->m_NoteItem[9].m_NotePic.m_text = 0;
        ((UICursor *)&this->m_NoteItem[9].m_NotePic.m_fonttype)->IRender();
        LOBYTE(this->m_par[4][0]._element.m_texty) = 1;
        return 1;
      }
      else
      {
        LOBYTE(this->m_par[4][0]._element.m_texty) = 0;
        this->CreateNoteEntry(0, v88, v89, v90, v91, *(int *)String1, String1[4]);
        ((UIListBox *)this)->ResetAllListBoxes();
        ((UIListBox *)this)->ShowSlotUI();
        this->m_NoteItem[67].m_NoteLv[0].m_mouseoff = 1;
        *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 1) = 0;
        *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 2) = 1;
        *(_DWORD *)&this->m_par[4][0]._element.m_text[8] = -997785600;
        *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 3) = 1;
        return 1;
      }
    case 1001:
      v15 = pWnd;
      v94 = 0;
      v16 = &off_56F1F4;
      a2 = (int)&this->m_NoteItem[67].m_NoteLv[2].m_ppic;
      do
      {
        if ( v15 == (UIWnd *)*v16 )
        {
          if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
            goto LABEL_54;
          p_m_ppic = &this->m_NoteItem[67].m_NoteLv[2].m_ppic;
          v18 = 5;
          do
          {
            sub_445E50((int)p_m_ppic);
            p_m_ppic += 86;
            --v18;
          }
          while ( v18 );
          sub_445E50(a2);
          ((CCBCamControl *)this)->ShowAllSlots(v94);
          v64 = g_pCScreenMode_5CF1E8;
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v64, 1);
          v15 = pWnd;
        }
        ++v16;
        ++v94;
        a2 += 344;
      }
      while ( (int)v16 < (int)&off_56F208 );
      v20 = 0;
      while ( v15 != (UIWnd *)(&off_56F1CC)[v20] )
      {
        if ( v15 == (UIWnd *)(&off_56F1E0)[v20] )
        {
          if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) && this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
          {
            if ( *(_DWORD *)&this->m_IsMsg )
            {
              if ( !HIBYTE(this->m_par[4][0]._element.m_texty) )
              {
                if ( LOBYTE(this->m_NoteItem[10].m_NoteState.m_pbk2) )
                {
                  g_nFiveNimbusCount = v20;
                  this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_fonttype = (Parent_Data *)v20;
                  if ( !*((_BYTE *)&g_nActorState + g_nFiveNimbusCount) )
                  {
                    if ( *((_BYTE *)&g_nRoleState + g_nFiveNimbusCount + 1) )
                    {
LABEL_56:
                      v25 = g_pCScreenMode_5CF1F4;
LABEL_57:
                      v69 = v25;
                    }
                    else
                    {
                      BYTE2(this->m_par[4][0]._element.m_texty) = 0;
                      this->CreateNoteEntry(1, v88, v89, v90, v91, *(int *)String1, String1[4]);
                      ((CCBCamControl *)this)->ShowAllSlots(0);
                      v69 = g_pCScreenMode_5CF1E8;
                    }
                    goto LABEL_107;
                  }
                }
                goto LABEL_54;
              }
LABEL_40:
              sprintf(this->buf, "\\n\\n      %s", (const char *)dword_DD3D3C);
              ((UICaption *)&this->m_NoteItem[72].m_isHead[4])->SetEnable((int)this->buf, 0);
              ((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor)->SetByte(1);
              v67 = off_5CF1F0;
              v23 = CScreenMode::GetInstance();
              ((CScreenMode *)v23)->AudioSetPosition(v67, 1);
              return 1;
            }
LABEL_38:
            sprintf(this->buf, "\\n     %s\\n     %s", (const char *)dword_DD253C, (const char *)dword_DD433C);
            ((UICaption *)&this->m_NoteItem[72].m_isHead[4])->SetEnable((int)this->buf, 0);
            ((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor)->SetByte(1);
            v66 = off_5CF1F0;
            v22 = CScreenMode::GetInstance();
            ((CScreenMode *)v22)->AudioSetPosition(v66, 1);
            return 1;
          }
          goto LABEL_54;
        }
        if ( ++v20 >= 5 )
        {
          if ( v15 > (UIWnd *)byte_A00110 )
          {
            switch ( (unsigned int)v15 )
            {
              case 0xA00536u:
                ((CCBUI *)this)->CreatePanelUI();
                return 1;
              case 0xA00537u:
                ((UIListBox *)this)->ResetAllListBoxes();
                this->CreateNoteEntry(0, v88, v89, v90, v91, *(int *)String1, String1[4]);
                goto LABEL_106;
              case 0xA00555u:
                this->m_NoteItem[72].m_HeadShot[1].m_pbk = 0;
                ((UIListBox *)this)->_todo_4A9870();
                goto LABEL_98;
              case 0xA00556u:
                this->m_NoteItem[72].m_HeadShot[1].m_pbk = (gbTexture *)1;
                ((UIListBox *)this)->_todo_4A9870();
                v69 = g_pCScreenMode_5CF1E8;
                goto LABEL_107;
              case 0xA00557u:
                ((CCBUI *)this)->DestroyDynamic(0);
                goto LABEL_98;
              case 0xA00558u:
                v86 = g_pCScreenMode_5CF1E8;
                v45 = CScreenMode::GetInstance();
                ((CScreenMode *)v45)->AudioSetPosition(v86, 1);
                ((CCBUI *)this)->DestroyDynamic(1);
                return 1;
              case 0xA00564u:
                if ( !LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic)
                  || !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0]
                  || !LOBYTE(this->m_NoteItem[10].m_NoteState.m_pbk2) )
                {
                  goto LABEL_54;
                }
                m_nTextW = (void ( **)(int *, _DWORD))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
                HIBYTE(this->m_par[4][0]._element.m_texty) = 1;
                (*m_nTextW)(&this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW, 0);
                (*(void ( **)(PtrArray *, int))this->m_NoteItem[67].m_HeadShot[1].m_childs.m_pData)(
                  &this->m_NoteItem[67].m_HeadShot[1].m_childs,
                  1);

                ((UIPushButton *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetAnimOffset(2, *(_DWORD *)&this->m_par[4][0]._element.m_text[4], *(float *)&v88);
                goto LABEL_98;
              case 0xA00565u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) && this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
                {
                  if ( !LOBYTE(this->m_NoteItem[10].m_NoteState.m_pbk2) )
                    goto LABEL_54;
                  v43 = (void ( **)(int *, int))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
                  HIBYTE(this->m_par[4][0]._element.m_texty) = 0;
                  (*v43)(&this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW, 1);
                  (*(void ( **)(PtrArray *, _DWORD))this->m_NoteItem[67].m_HeadShot[1].m_childs.m_pData)(
                    &this->m_NoteItem[67].m_HeadShot[1].m_childs,
                    0);

                  ((UIPushButton *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel)->SetAnimOffset(2, *(_DWORD *)&this->m_par[4][0]._element.m_text[4], *(float *)&v88);
LABEL_106:
                  v69 = g_pCScreenMode_5CF1E8;
                }
                else
                {
                  v69 = g_pCScreenMode_5CF1F4;
                }
                goto LABEL_107;
              case 0xA00571u:
                if ( dword_D8BBEC == 2 )
                {
                  sprintf(this->buf, "\\n\\n    %s", &byte_DDA73C[256]);
                  ((UICaption *)&this->m_NoteItem[72].m_isHead[4])->SetEnable((int)this->buf, 0);
                  ((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor)->SetByte(1);
                  v69 = (const char *)off_5CF1F0;
                  goto LABEL_107;
                }
                if ( ((UIScene *)"Q14")->ProcessInput(0) )
                {
                  sprintf(this->buf, "\\n\\n       %s", (const char *)dword_DC9F3C);
                  ((UICaption *)&this->m_NoteItem[72].m_isHead[4])->SetEnable((int)this->buf, 0);
                  ((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor)->SetByte(1);
                  v25 = (const char *)off_5CF1F0;
                  goto LABEL_57;
                }
                v85 = g_pCScreenMode_5CF1E8;
                v41 = CScreenMode::GetInstance();
                ((CScreenMode *)v41)->AudioSetPosition(v85, 1);
                ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                result = 1;
                break;
              default:
                return 1;
            }
          }
          else if ( v15 == (UIWnd *)byte_A00110 )
          {
            if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
            {
              v84 = g_pCScreenMode_5CF1E8;
              v40 = CScreenMode::GetInstance();
              ((CScreenMode *)v40)->AudioSetPosition(v84, 1);
              ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
            }
            else
            {
              v83 = g_pCScreenMode_5CF1F4;
              v39 = CScreenMode::GetInstance();
              ((CScreenMode *)v39)->AudioSetPosition(v83, 1);
            }
            return 1;
          }
          else
          {
            switch ( (unsigned int)v15 )
            {
              case 0xA00102u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v70 = g_pCScreenMode_5CF1E8;
                  v26 = CScreenMode::GetInstance();
                  ((CScreenMode *)v26)->AudioSetPosition(v70, 1);
                  ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                }
                else
                {
                  v65 = g_pCScreenMode_5CF1F4;
                  v21 = CScreenMode::GetInstance();
                  ((CScreenMode *)v21)->AudioSetPosition(v65, 1);
                }
                result = 1;
                break;
              case 0xA00103u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v72 = g_pCScreenMode_5CF1E8;
                  v28 = CScreenMode::GetInstance();
                  ((CScreenMode *)v28)->AudioSetPosition(v72, 1);
                  ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                }
                else
                {
                  v71 = g_pCScreenMode_5CF1F4;
                  v27 = CScreenMode::GetInstance();
                  ((CScreenMode *)v27)->AudioSetPosition(v71, 1);
                }
                result = 1;
                break;
              case 0xA00104u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v74 = g_pCScreenMode_5CF1E8;
                  v30 = CScreenMode::GetInstance();
                  ((CScreenMode *)v30)->AudioSetPosition(v74, 1);
                  ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                }
                else
                {
                  v73 = g_pCScreenMode_5CF1F4;
                  v29 = CScreenMode::GetInstance();
                  ((CScreenMode *)v29)->AudioSetPosition(v73, 1);
                }
                result = 1;
                break;
              case 0xA00105u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v76 = g_pCScreenMode_5CF1E8;
                  v32 = CScreenMode::GetInstance();
                  ((CScreenMode *)v32)->AudioSetPosition(v76, 1);
                  ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                }
                else
                {
                  v75 = g_pCScreenMode_5CF1F4;
                  v31 = CScreenMode::GetInstance();
                  ((CScreenMode *)v31)->AudioSetPosition(v75, 1);
                }
                result = 1;
                break;
              case 0xA00107u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v78 = g_pCScreenMode_5CF1E8;
                  v34 = CScreenMode::GetInstance();
                  ((CScreenMode *)v34)->AudioSetPosition(v78, 1);
                  ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                }
                else
                {
                  v77 = g_pCScreenMode_5CF1F4;
                  v33 = CScreenMode::GetInstance();
                  ((CScreenMode *)v33)->AudioSetPosition(v77, 1);
                }
                result = 1;
                break;
              case 0xA00108u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v80 = g_pCScreenMode_5CF1E8;
                  v36 = CScreenMode::GetInstance();
                  ((CScreenMode *)v36)->AudioSetPosition(v80, 1);
                  ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                }
                else
                {
                  v79 = g_pCScreenMode_5CF1F4;
                  v35 = CScreenMode::GetInstance();
                  ((CScreenMode *)v35)->AudioSetPosition(v79, 1);
                }
                result = 1;
                break;
              case 0xA00109u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v82 = g_pCScreenMode_5CF1E8;
                  v38 = CScreenMode::GetInstance();
                  ((CScreenMode *)v38)->AudioSetPosition(v82, 1);
                  ((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208])->HandleMessage();
                }
                else
                {
                  v81 = g_pCScreenMode_5CF1F4;
                  v37 = CScreenMode::GetInstance();
                  ((CScreenMode *)v37)->AudioSetPosition(v81, 1);
                }
                result = 1;
                break;
              default:
                return 1;
            }
          }
          return result;
        }
      }
      if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) && this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
      {
        if ( !*(_DWORD *)&this->m_IsMsg )
          goto LABEL_38;
        if ( !HIBYTE(this->m_par[4][0]._element.m_texty) )
          goto LABEL_40;
        if ( LOBYTE(this->m_NoteItem[10].m_NoteState.m_pbk2) )
        {
          g_nFiveNimbusCount = v20;
          this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_fonttype = (Parent_Data *)v20;
          if ( !*((_BYTE *)&g_nActorState + g_nFiveNimbusCount) && !*((_BYTE *)&g_nRoleParam + g_nFiveNimbusCount) )
          {
            BYTE2(this->m_par[4][0]._element.m_texty) = 1;
            this->CreateNoteEntry(1, v88, v89, v90, v91, *(int *)String1, String1[4]);
            ((CCBCamControl *)this)->ShowAllSlots(0);
LABEL_98:
            v69 = g_pCScreenMode_5CF1E8;
            goto LABEL_107;
          }
        }
      }
LABEL_54:
      v68 = g_pCScreenMode_5CF1F4;
      v24 = CScreenMode::GetInstance();
      ((CScreenMode *)v24)->AudioSetPosition(v68, 1);
      return 1;
    case 1002:
      v46 = 0;
      while ( 2 )
      {
        if ( pWnd == (UIWnd *)(&off_56F1CC)[v46] && this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
        {
          ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&Destination[256 * dword_56F22C[5 * v46]], 0);
          goto LABEL_149;
        }
        if ( pWnd == (UIWnd *)(&off_56F1E0)[v46] && this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
        {
          v47 = dword_56F224[5 * v46];
        }
        else
        {
          if ( pWnd == (UIWnd *)(&off_56F1A4)[v46] && this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
          {
            ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&Destination[256 * dword_56F230[5 * v46]], 0);
            goto LABEL_149;
          }
          if ( pWnd == (UIWnd *)(&off_56F1B8)[v46] && this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
          {
            ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&Destination[256 * dword_56F228[5 * v46]], 0);
            goto LABEL_149;
          }
          if ( pWnd != (UIWnd *)(&off_56F208)[v46] || !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
          {
            if ( ++v46 >= 5 )
              goto LABEL_149;
            continue;
          }
          v47 = dword_56F234[5 * v46];
        }
        break;
      }
      ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&Destination[256 * v47], 0);
LABEL_149:
      switch ( (unsigned int)pWnd )
      {
        case 0xA00510u:
          if ( !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
            goto LABEL_168;
          v48 = 233;
          goto LABEL_167;
        case 0xA00564u:
        case 0xA00565u:
          if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
            ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&g_ComposeRecipeTable[7936], 0);
          goto LABEL_168;
        case 0xA00571u:
          v48 = 265;
LABEL_167:
          ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&Destination[256 * v48], 0);
          goto LABEL_168;
        case 0xA00572u:
          if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
          {
            this->buf[0] = 0;
            RoleNum = ((PAL_GDB *)&g_pGDB)->GDB_GetRoleNum(*((int *)&::Buffer.m_partyActor.m_fSpeed + 3));
            if ( RoleNum )
              lstrcpyA(this->buf, (LPCSTR)(RoleNum + 60));
            else
              lstrcpyA(this->buf, g_szSceneUIText);
            m_fonttype = this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_fonttype;
            memset(String1, 0, 10);
            switch ( (unsigned int)m_fonttype )
            {
              case 0u:
                lstrcpyA(String1, (LPCSTR)g_bSlotFlag);
                break;
              case 1u:
                lstrcpyA(String1, (LPCSTR)&g_bSlotFlag[256]);
                break;
              case 2u:
                lstrcpyA(String1, byte_DC3F3C);
                break;
              case 3u:
                lstrcpyA(String1, (LPCSTR)&g_bSlotFlag[512]);
                break;
              case 4u:
                lstrcpyA(String1, byte_DC403C);
                break;
              default:
                break;
            }
            memset(Buffer, 0, sizeof(Buffer));
            v96 = 0;
            v97 = 0;
            sprintf(
              Buffer,
              "\\n\\n%s: %d\\n%s:   %s",
              (const char *)dword_DCE93C,
              ::Buffer.m_partyActor.m_fAngleDeg,
              (const char *)dword_DC933C,
              String1);
            lstrcatA(this->buf, Buffer);
            ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)this->buf, 0);
LABEL_168:
            switch ( (unsigned int)pWnd )
            {
              case 0xA00102u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 0;
                if ( LOBYTE(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_185;
                this->InitSlotEffects(0);
                result = 1;
                break;
              case 0xA00103u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 1;
                if ( BYTE1(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_185;
                this->InitSlotEffects(1);
                result = 1;
                break;
              case 0xA00104u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 2;
                if ( BYTE2(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_185;
                this->InitSlotEffects(2);
                result = 1;
                break;
              case 0xA00105u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 3;
                if ( HIBYTE(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_185;
                this->InitSlotEffects(3);
                result = 1;
                break;
              case 0xA00106u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 5;
                if ( this->m_NoteItem[9].m_NotePic.m_text[1] )
                  goto LABEL_185;
                this->InitSlotEffects(5);
                result = 1;
                break;
              case 0xA00107u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 6;
                if ( this->m_NoteItem[9].m_NotePic.m_text[2] )
                  goto LABEL_185;
                this->InitSlotEffects(6);
                result = 1;
                break;
              case 0xA00108u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 4;
                if ( this->m_NoteItem[9].m_NotePic.m_text[0] )
                  goto LABEL_185;
                this->InitSlotEffects(4);
                result = 1;
                break;
              case 0xA00109u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 7;
                if ( !this->m_NoteItem[9].m_NotePic.m_text[3] )
                  this->InitSlotEffects(7);
                goto LABEL_185;
              default:
LABEL_185:
                result = 1;
                break;
            }
          }
          else
          {
            result = 1;
          }
          break;
        default:
          goto LABEL_168;
      }
      return result;
    case 1003:
      v51 = 0;
      break;
    case 1007:
      this->m_par[4][0]._element.m_fonttype = (Parent_Data *)nVal2;
      return 1;
    case 1008:
      switch ( (unsigned int)pWnd )
      {
        case 0xA00529u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[69].m_NoteTime.m_ppicInfo;
          Child = (Parent_Data *)((NPC *)&this->m_NoteItem[69].m_NoteTime.m_ppicInfo)->CreateChild();
          this->m_par[4][0]._element.m_fonttype = Child;
          if ( (int)Child < 0 )
          {
            v69 = g_pCScreenMode_5CF1F4;
            break;
          }
          ((UIListBox *)this)->InsertUIListBox(0);
          goto LABEL_227;
        case 0xA00530u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[69].m_NotePicName.m_pbkInfo;
          v54 = (Parent_Data *)((NPC *)&this->m_NoteItem[69].m_NotePicName.m_pbkInfo)->CreateChild();
          this->m_par[4][0]._element.m_fonttype = v54;
          v87 = 1;
          if ( (int)v54 >= 0 )
            goto LABEL_226;
          v69 = g_pCScreenMode_5CF1F4;
          break;
        case 0xA00531u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok;
          v55 = (Parent_Data *)((NPC *)&this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok)->CreateChild();
          this->m_par[4][0]._element.m_fonttype = v55;
          if ( (int)v55 < 0 )
          {
            v69 = g_pCScreenMode_5CF1F4;
            break;
          }
          ((UIListBox *)this)->InsertUIListBox((void *)2);
          goto LABEL_227;
        case 0xA00532u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[70].m_NoteMoney.m_childs;
          v56 = (Parent_Data *)((NPC *)&this->m_NoteItem[70].m_NoteMoney.m_childs)->CreateChild();
          this->m_par[4][0]._element.m_fonttype = v56;
          if ( (int)v56 < 0 )
          {
            v69 = g_pCScreenMode_5CF1F4;
            break;
          }
          ((UIListBox *)this)->InsertUIListBox((void *)3);
          goto LABEL_227;
        case 0xA00533u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[71].m_NoteItemBk.m_id;
          v57 = (Parent_Data *)((NPC *)&this->m_NoteItem[71].m_NoteItemBk.m_id)->CreateChild();
          this->m_par[4][0]._element.m_fonttype = v57;
          if ( (int)v57 >= 0 )
          {
            v87 = 4;
LABEL_226:
            ((UIListBox *)this)->InsertUIListBox((void *)v87);
LABEL_227:
            ItemData = ((UIListBox *)p_m_ppicInfo)->GetItemData();
            ((UIListBox *)p_m_ppicInfo)->GetItem();
            if ( ItemData < (int)this->m_par[4][0]._element.m_fonttype )
              ((UIListBox *)p_m_ppicInfo)->GetItem();
            v69 = off_5CF1EC[0];
          }
          else
          {
            v69 = g_pCScreenMode_5CF1F4;
          }
          break;
        case 0xA00534u:
          p_m_pbkInfo = &this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo;
          LockedSel = ((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo)->GetLockedSel();
          if ( LockedSel < 0
            || LockedSel >= ((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo)->GetItemData() )
          {
            goto LABEL_56;
          }
          ((UIListBox *)this)->ProcessListInput(LockedSel);
          v61 = ((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo)->GetItemData();
          v62 = &this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo;
          v63 = v61;
          ((UIListBox *)v62)->GetItem();
          if ( v63 < LockedSel )
            ((UIListBox *)p_m_pbkInfo)->GetItem();
          v69 = off_5CF1EC[0];
          break;
        default:
          return 1;
      }
LABEL_107:
      v44 = CScreenMode::GetInstance();
      ((CScreenMode *)v44)->AudioSetPosition(v69, 1);
      return 1;
    case 1014:
      if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
      {
        if ( pWnd == (UIWnd *)byte_A00539 )
        {
          ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&g_ComposeRecipeTable[7680], 0);
        }
        else if ( (char *)pWnd - byte_A00539 == 7 )
        {
          ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&g_ComposeRecipeTable[512], 0);
        }
      }
      return 1;
    case 1015:
      if ( !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
        return 1;
      if ( pWnd == (UIWnd *)byte_A00539 || (char *)pWnd - byte_A00539 == 7 )
        ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&g_ComposeRecipeTable[256], 0);
      return 1;
    case 1017:
      result = 1;
      if ( pWnd == (UIWnd *)byte_A00539 )
        this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 1;
      return result;
    case 1018:
      if ( pWnd != (UIWnd *)byte_A00539 )
        return 1;
      this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 0;
      return 1;
    default:
      return ((PalScript *)this)->OnMessage(nVal, (int)pWnd, nVal2);
  }
  while ( pWnd != (UIWnd *)(&off_56F1CC)[v51]
       && !(&off_56F1E0)[v51]
       && !(&off_56F1A4)[v51]
       && !(&off_56F1B8)[v51]
       && !(&off_56F208)[v51] )
  {
    if ( ++v51 >= 5 )
      goto LABEL_197;
  }
  if ( !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
    return 1;
  ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&g_ComposeRecipeTable[256], 0);
LABEL_197:
  switch ( (unsigned int)pWnd )
  {
    case 0xA00510u:
    case 0xA00564u:
    case 0xA00565u:
    case 0xA00571u:
    case 0xA00572u:
      if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
        ((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)->SetEnable((int)&g_ComposeRecipeTable[256], 0);
      break;
    default:
      break;
  }
  switch ( (unsigned int)pWnd )
  {
    case 0xA00102u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 0;
      LOBYTE(this->m_NoteItem[9].m_NotePic.m_fonttype) = 0;
      result = 1;
      break;
    case 0xA00103u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 1;
      BYTE1(this->m_NoteItem[9].m_NotePic.m_fonttype) = 0;
      result = 1;
      break;
    case 0xA00104u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 2;
      BYTE2(this->m_NoteItem[9].m_NotePic.m_fonttype) = 0;
      result = 1;
      break;
    case 0xA00105u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 3;
      HIBYTE(this->m_NoteItem[9].m_NotePic.m_fonttype) = 0;
      result = 1;
      break;
    case 0xA00106u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 5;
      this->m_NoteItem[9].m_NotePic.m_text[1] = 0;
      result = 1;
      break;
    case 0xA00107u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 6;
      this->m_NoteItem[9].m_NotePic.m_text[2] = 0;
      result = 1;
      break;
    case 0xA00108u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 4;
      this->m_NoteItem[9].m_NotePic.m_text[0] = 0;
      result = 1;
      break;
    case 0xA00109u:
      *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 7;
      this->m_NoteItem[9].m_NotePic.m_text[3] = 0;
      goto LABEL_209;
    default:
LABEL_209:
      result = 1;
      break;
  }
  return result;
}

// 0x0051F130
int SystemUI::UpdateParticles()
{
  float m_ratioh; // eax
  float yi; // edx
  __int64 v3; // rax
  int result; // eax

  if ( SLODWORD(this->m_par[0][5]._xi) > 0 )
  {
    m_ratioh = this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_ratioh;
    yi = this->m_par[0][5]._yi;
    v3 = (__int64)((*(float *)(LODWORD(yi)
                             + 4 * (this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_align + 4 * (3 * LODWORD(m_ratioh) + 3)))
                  + *(float *)(LODWORD(yi)
                             + 4
                             * (12 * LODWORD(m_ratioh) + LODWORD(this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_ratiow))
                             + 60)
                  + *(float *)(LODWORD(yi)
                             + 4 * ((int)this->m_NoteItem[52].m_HeadShot_NO_SEL[1].pDebugTex + 12 * LODWORD(m_ratioh))
                             + 36))
                 * (double)this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_benable
                 + (double)this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_benable);
    this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_bfocus = v3;
    *(_DWORD *)&this->m_NoteItem[102].m_NoteTime.m_text[4] = v3;
  }
  result = this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_bfocus;
  this->m_NoteItem[52].m_HeadShot_NO_SEL[1].m_bfocus = 0;
  return result;
}
