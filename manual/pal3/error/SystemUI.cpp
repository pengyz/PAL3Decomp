#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/SystemUI.h"
#include "Role/Actor.h"
#include "Combat/CCBCamControl.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBStage.h"
#include "Combat/CCBUI.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "Misc/MUIDialog.h"
#include "Misc/MainEquipUI.h"
#include "Data/PAL_GDB.h"
#include "Script/PalScript.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Script/ScriptSystem.h"
#include "Misc/ScriptSystemData.h"
#include "UI/StateUI.h"
#include "Misc/SwordUI.h"
#include "Render/TextureLib.h"
#include "Misc/UIBigMap.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "Misc/UIParticle.h"
#include "Misc/UIRoleDialog.h"
#include "Misc/UIRoleSelect.h"
#include "UI/UIScene.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_41F8C0(...);
int sub_426EB0(...);

// Unnamed globals (extern)
extern CHAR byte_DC3F3C[256];
extern CHAR byte_DC403C[256];
extern CHAR byte_DDA73C[512];

// 0x0041F6F0
void SystemUI::Reset()
{
  *(_DWORD *)&this->buf[36] = 0;
  *(_DWORD *)&this->buf[40] = 0;
  *(_DWORD *)&this->buf[44] = 0;
  *(_DWORD *)&this->buf[48] = 0;
  *(_DWORD *)&this->buf[52] = 0;
  *(_DWORD *)&this->buf[56] = 0;
  (((PtrArray *)&this->buf[60]))->PtrArray::Clear();
  (((GRPinput *)&this->m_NoteItem[98].m_HeadShot[2].m_pbk2))->GRPinput::AcquireMouse();
  *(_DWORD *)&this->buf[28] = 0;
  this->m_par[12][6].par_radiusY = 0;
  this->m_NoteItem[98].m_NoteTime.m_childs.capacity = 0;
  *((_DWORD *)&this->m_nTodo_0B4 + 10) = 0;
  this->m_NoteItem[98].m_NoteTime.m_childs.m_pData = ((char *)0);
  this->m_NoteItem[98].m_NoteTime.m_childs.m_nSize = 0;
  *(_DWORD *)&this->buf[32] = 0;
  this->m_NoteItem[98].m_NoteTime.m_bcreateok = 0;
  LOBYTE(this->m_NoteItem[98].m_NoteTime.m_childs.m_needscriptdel) = -1;
}

// 0x0041F800
void SystemUI::Close()
{
  sub_41F8C0(this);
  (((GRPinput *)&this->m_NoteItem[98].m_HeadShot[2].m_pbk2))->GRPinput::UnacquireKeyboard();
  (((UIListBox *)&this->buf[60]))->UIListBox::ReleaseVtable();
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
      (((gbVisNode *)m_pData))->gbVisNode::SetTimeScale(0.2);
      (*(void ( **)(char *, _DWORD))(*(_DWORD *)this->m_NoteItem[98].m_NoteTime.m_childs.m_pData + 16))(
        this->m_NoteItem[98].m_NoteTime.m_childs.m_pData,
        0);
    }
    result = *((_DWORD *)&this->m_nTodo_0B4 + 10);
    v5 = 0;
    if ( result > 0 )
    {
      v6 = (UIBigMap *)(&this->m_nTodo_0B4 + 11);
      do
      {
        if ( v6->bkWndX != 4 )
          (((UIBigMap *)v6))->UIBigMap::RenderRole((gbMatrixStack *)nVal, 0);
        result = *((_DWORD *)&this->m_nTodo_0B4 + 10);
        ++v5;
        v6 = (UIBigMap *)((char *)v6 + 896);
      }
      while ( v5 < result );
    }
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
      p_W = (int *)&this->m_par[12][6]._W;
      do
      {
        dt = result;
        ScriptSystem::UpdateTimers(dt);
        ++v5;
        p_W += 2176;
      }
      while ( v5 < this->m_par[12][6].par_radiusY );
    }
    if ( g_nSceneState != 9 )
    {
      v8 = 0;
      if ( *((int *)&this->m_nTodo_0B4 + 10) > 0 )
      {
        v6 = result;
        v9 = (void **)(&this->m_nTodo_0B4 + 11);
        do
        {
          dta = result;
          sub_426EB0((int)v9, dta);
          ++v8;
          v9 += 224;
        }
        while ( v8 < *((_DWORD *)&this->m_nTodo_0B4 + 10) );
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
SystemUI::~SystemUI()
{
  int *p_m_needscriptdel; // edi
  int v3; // [esp+0x0] [ebp-0x18]
  int v4; // [esp+0x0] [ebp-0x18]

  p_m_needscriptdel = (int *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel;
  (*(void (**)(int *))(this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel + 12))(&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel);
  (((UIRoleDialog *)&this->m_NoteItem[72].m_NoteLv[3].m_nTextW))->UIRoleDialog::~UIRoleDialog();
  (((UIRoleDialog *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor))->UIRoleDialog::~UIRoleDialog();
  (((CCBStage *)&this->m_NoteItem[72].m_HeadShot[1].m_pbkInfo))->CCBStage::Init(v3);
  (((UICaption *)&this->m_NoteItem[72].m_HeadShot_NO_SEL[4].m_align))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[72].m_HeadShot_NO_SEL[2].m_pfather))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[72].m_NoteState.m_FVF))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[72].m_NoteItemBk.m_caption[104]))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[71].m_NotePicName.m_ppic))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[71].m_NoteLv[4].m_ratioh))->UICaption::Destroy2();
  UIFrameWnd__deleting_view((UIFrameWnd *)&this->m_NoteItem[71].m_NoteLv[3].m_disablepicInfo);
  (((UIFrameContainer *)&this->m_NoteItem[71].m_NoteLv[2].m_disablepicInfo))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[71].m_NoteLv[0].m_pbkInfo))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[71].m_NoteMoney.m_pbkInfo))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo))->UIListBox::DeleteRow();
  (((UIListBox *)&this->m_NoteItem[71].m_NoteItemBk.m_id))->UIListBox::DeleteRow();
  (((UIListBox *)&this->m_NoteItem[70].m_NoteMoney.m_childs))->UIListBox::DeleteRow();
  (((UIListBox *)&this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok))->UIListBox::DeleteRow();
  (((UIListBox *)&this->m_NoteItem[69].m_NotePicName.m_pbkInfo))->UIListBox::DeleteRow();
  (((UIListBox *)&this->m_NoteItem[69].m_NoteTime.m_ppicInfo))->UIListBox::DeleteRow();
  (((UIFrameContainer *)&this->m_NoteItem[68].m_HeadShot[4].m_childs.m_nSize))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[68].m_HeadShot[2].m_childs.m_nSize))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[68].m_HeadShot[1].m_childs.m_nSize))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[68].m_HeadShot[0].m_childs.m_nSize))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)&this->m_NoteItem[68].m_HeadShot_NO_SEL[4].m_pbk);
  (((UIFrameContainer *)&this->m_NoteItem[68].m_HeadShot_NO_SEL[3].m_pbk))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[68].m_HeadShot_NO_SEL[2].m_pbk))->UIFrameContainer::~UIFrameContainer();
  UIFrameWnd__deleting_view((UIFrameWnd *)&this->m_NoteItem[67].m_NoteLv[2].m_childs);
  UIFrameWnd__deleting_view((UIFrameWnd *)&this->m_NoteItem[67].m_NoteLv[1].m_text[8]);
  CCCTData_DestroyImage(v4);
  (((UICaption *)&this->m_NoteItem[67].m_HeadShot[1].m_childs))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[12].m_NoteID.m_ppicInfo))->UICaption::Destroy2();
  (((UICaption *)&this->m_NoteItem[10].m_HeadShot[0].m_bvisible))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[2].m_bvisible))->UIFrameContainer::~UIFrameContainer();
  (((PalScript *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[0].m_bcreateok))->PalScript::Reset();
  (((PalScript *)p_m_needscriptdel))->PalScript::Reset();
  (((UIFrameContainer *)&this->m_NoteItem[10].m_NoteItemBk.m_caption[48]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[10].m_NoteItemBk.m_offsety))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[9].m_NotePicName.m_text[8]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_NoteItem[9].m_NotePic.m_text[8]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[5][3]._element.m_childs.capacity))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[5][3]._texName[148]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[5][3]._y))->UIFrameContainer::~UIFrameContainer();
  (((UICaption *)&this->m_par[5][2]._texName[220]))->UICaption::Destroy2();
  (((UICaption *)&this->m_par[5][2]._H))->UICaption::Destroy2();
  (((UICaption *)&this->m_par[5][1]._texName[116]))->UICaption::Destroy2();
  (((UICaption *)this->m_par[5][0]._element.m_text))->UICaption::Destroy2();
  (((UICaption *)&this->m_par[5][0]._texName[12]))->UICaption::Destroy2();
  (((UICaption *)&this->m_par[4][6]._texName[252]))->UICaption::Destroy2();
  (((UICaption *)&this->m_par[4][6].m_posx))->UICaption::Destroy2();
  (((UICaption *)&this->m_par[4][5]._texName[148]))->UICaption::Destroy2();
  (((UICaption *)&this->m_par[4][4]._element.m_disablepic))->UICaption::Destroy2();
  (((UIFrameContainer *)&this->m_par[4][4]._texName[236]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[4][4]._texName[84]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[4][4].m_riseY))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[4][3]._element.m_text[8]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_par[4][3]._texName[212]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->pStateUI))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
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
    (**(void ( ***)(char *, BOOL))&this->m_NoteItem[9].m_NotePicName.m_text[8])((char *)(&this->m_NoteItem[9].m_NotePicName.m_text[8]), (BOOL)(v13));
    (*(void ( **)(int *, BOOL))this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible)(
      &this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible,
      v13);
    (*(void ( **)(int *, BOOL))this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible)(
      &this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible,
      v13);
    (**(void ( ***)(char *, BOOL))&this->m_NoteItem[9].m_NotePic.m_text[8])((char *)(&this->m_NoteItem[9].m_NotePic.m_text[8]), (BOOL)(v13));
    if ( g_bUIWnd_DE625A )
      (*(void ( **)(int *, BOOL))this->m_NoteItem[10].m_HeadShot[0].m_bvisible)(
        &this->m_NoteItem[10].m_HeadShot[0].m_bvisible,
        v13);
    (*(void ( **)(float *, BOOL))LODWORD(this->m_NoteItem[10].m_NoteItemBk.m_offsety))(
      &this->m_NoteItem[10].m_NoteItemBk.m_offsety,
      v13);
    ((void ( *)(StateUI **, BOOL))((UIWnd *)this->pStateUI))(&this->pStateUI, v13);
    (**(void ( ***)(char *, BOOL))&this->m_NoteItem[10].m_NoteItemBk.m_caption[48])((char *)(&this->m_NoteItem[10].m_NoteItemBk.m_caption[48]), (BOOL)(v13));
    (*(void ( **)(float *, BOOL))LODWORD(this->m_NoteItem[10].m_NoteItemBk.m_offsety))(
      &this->m_NoteItem[10].m_NoteItemBk.m_offsety,
      v13);
    this->m_NoteItem[10].m_HeadShot_NO_SEL[0].m_disablepic = (gbTexture *)v13;
    if ( (_BYTE)nVal )
    {
      (((MUIDialog *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor))->MUIDialog::InvokeCallback();
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
      p_right = (LONG *)&this->m_NoteItem[11].m_NoteLv[0].m_rect.right;
      p_m_pbk2 = (gbTexture **)&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2;
      v17 = 5;
      do
      {
        ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)(*(p_m_pbk2 - 620))))(p_m_pbk2 - 620, 0);
        (*(void ( **)(LONG *, _DWORD))*(p_right - 620))(p_right - 620, 0);
        ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)(*p_m_pbk2)))(p_m_pbk2, 0);
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
      SetEnable((UICaption *)&this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo);
    }
    else
    {
      v18 = 0;
      v19 = (gbTexture **)&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2;
      v20 = (LONG *)&this->m_NoteItem[11].m_NoteItemBk.m_rect.right;
      do
      {
        v21 = (void ( ***)(_DWORD, int, BOOL))(v20 + 810);
        if ( *((_BYTE *)&g_nActorState + v18) )
        {
          (**v21)((_DWORD)((_DWORD)(v21)), (int)(1), (BOOL)(v30));
          (*(void ( **)(LONG *, _DWORD))v20[620])(v20 + 620, 0);
          (*(void ( **)(LONG *, _DWORD))*v20)(v20, 0);
          ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)(*v19)))(v19, 0);
          v22 = *(v19 - 620);
          v23 = (gbTexture **)(v19 - 620);
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
            ((void ( *)(gbTexture **, bool))((gbRefObject *)(*v19)))(v19, *((_BYTE *)&g_nRoleParam + v18) == 0);
            (*(void ( **)(LONG *, _DWORD))*v20)(v20, *((unsigned __int8 *)&g_nRoleState + v18 + 1));
            v22 = *(v19 - 620);
            v23 = (gbTexture **)(v19 - 620);
            v30 = *((_BYTE *)&g_nRoleState + v18 + 1) == 0;
          }
          else
          {
            (*(void ( **)(LONG *, _DWORD, BOOL))*v20)(v20, *((unsigned __int8 *)&g_nRoleState + v18 + 1), v30);
            ((void ( *)(gbTexture **, bool))((gbRefObject *)(*(v19 - 620))))(
              v19 - 620,
              *((_BYTE *)&g_nRoleState + v18 + 1) == 0);
            (*(void ( **)(LONG *, _DWORD))v20[620])(v20 + 620, *((unsigned __int8 *)&g_nRoleParam + v18));
            v22 = (gbTexture *)*v19;
            v30 = *((_BYTE *)&g_nRoleParam + v18) == 0;
            v23 = (gbTexture **)v19;
          }
        }
        ((void ( *)(gbTexture **))((gbRefObject *)v22))(v23);
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
    p_m_ppic = (gbTexture **)&this->m_NoteItem[67].m_NoteLv[2].m_ppic;
    nVal2a = 5;
    for ( nVala = &this->m_NoteItem[67].m_NoteLv[2].m_ppic; ; p_m_ppic = nVala )
    {
      ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)(*p_m_ppic)))(p_m_ppic, (unsigned __int8)pData);
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
    (*(void ( **)(unsigned int *, _DWORD))this->m_NoteItem[71].m_NoteItemBk.m_id)(
      &this->m_NoteItem[71].m_NoteItemBk.m_id,
      (unsigned __int8)pData);
    ((void ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo->filepos)(
      &this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_NoteItem[68].m_HeadShot_NO_SEL[2].m_pbk))(
      &this->m_NoteItem[68].m_HeadShot_NO_SEL[2].m_pbk,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_NoteItem[68].m_HeadShot_NO_SEL[3].m_pbk))(
      &this->m_NoteItem[68].m_HeadShot_NO_SEL[3].m_pbk,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize)(
      &this->m_NoteItem[68].m_HeadShot[3].m_childs.m_nSize,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_NoteItem[68].m_HeadShot_NO_SEL[4].m_pbk))(
      &this->m_NoteItem[68].m_HeadShot_NO_SEL[4].m_pbk,
      (unsigned __int8)pData);
    (**(void ( ***)(char *, _DWORD))&this->m_NoteItem[67].m_NoteLv[1].m_text[8])((char *)(&this->m_NoteItem[67].m_NoteLv[1].m_text[8]), (_DWORD)((unsigned __int8)pData));
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
      (**((void ( ***)(char *, _DWORD))&this->m_NoteItem[68].m_NoteTime.m_childs.m_pData + 38 * this->i))((char *)((char *)&this->m_NoteItem[68].m_NoteTime.m_childs + 152 * this->i), (_DWORD)((unsigned __int8)pData));
      (**((void ( ***)(_PlugInfo **, _DWORD))&this->m_NoteItem[69].m_NoteID.m_disablepicInfo + 38 * this->i))((_PlugInfo **)(&this->m_NoteItem[69].m_NoteID.m_disablepicInfo + 38 * this->i), (_DWORD)((unsigned __int8)pData));
      v26 = this->i + 1;
      this->i = v26;
    }
    while ( v26 < 12 );
    (*(void ( **)(float *, _DWORD))LODWORD(this->m_NoteItem[71].m_NoteLv[4].m_ratioh))(
      &this->m_NoteItem[71].m_NoteLv[4].m_ratioh,
      (unsigned __int8)pData);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)this->m_NoteItem[71].m_NotePicName.m_ppic))(
      &this->m_NoteItem[71].m_NotePicName.m_ppic,
      (unsigned __int8)pData);
    (**(void ( ***)(char *))&this->m_NoteItem[72].m_NoteItemBk.m_caption[104])((char *)(&this->m_NoteItem[72].m_NoteItemBk.m_caption[104]));
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[72].m_NoteState.m_FVF)(
      &this->m_NoteItem[72].m_NoteState.m_FVF,
      (unsigned __int8)pData);
    (*(void ( **)(UIWnd **, _DWORD))this->m_NoteItem[72].m_HeadShot_NO_SEL[2].m_pfather)(
      &this->m_NoteItem[72].m_HeadShot_NO_SEL[2].m_pfather,
      (unsigned __int8)pData);
    (*(void ( **)(int *, _DWORD))this->m_NoteItem[72].m_HeadShot_NO_SEL[4].m_align)(
      &this->m_NoteItem[72].m_HeadShot_NO_SEL[4].m_align,
      (unsigned __int8)pData);
    ((void ( *)(_PlugInfo **, _DWORD))this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo->filepos)(
      &this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo,
      (unsigned __int8)pData);
    result = (char)nVala;
    if ( (_BYTE)nVala )
      return CCBCamControl_ShowAllSlots(0);
  }
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
  unsigned int *p_m_id; // edi
  int v11; // ebx
  int i; // edi
  int fX; // [esp+0x0] [ebp-0x24]
  float fXa; // [esp+0x0] [ebp-0x24]
  int nVal1; // [esp+0x4] [ebp-0x20]
  int nVal1a; // [esp+0x4] [ebp-0x20]
  float nVal1b; // [esp+0x4] [ebp-0x20]
  CCBMagicWindow *v18; // [esp+0x10] [ebp-0x14]
  LONG right; // [esp+0x1C] [ebp-0x8]
  int v20; // [esp+0x20] [ebp-0x4]

  (((CCBControlWindow *)this))->CCBControlWindow::Render(v18) /* [ROWTABLE] */;
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
        if ( !IsVisible((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                                       + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)) )
        {
          v20 = this->m_NoteItem[39].m_NoteLv[2].m_rect.top + rand() % (v3 / 2);
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::LoadTexture("UI\\GameMainUI\\Par_Effect\\flare.tga");
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetSize(32);
          if ( HIBYTE(this->m_par[4][0]._element.m_texty) )
          {
            nVal1 = rand() % 10 + 224;
            fX = rand() % 10 + 84;
            v7 = rand() % 10 - 118;
          }
          else
          {
            nVal1 = rand() % 10 + 58;
            fX = rand() % 10 + 128;
            v7 = rand() % 10 - 58;
          }
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetColor(v7, fX, nVal1);
          v8 = rand();
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetAlpha(v8 % 25 - 26);
          *(float *)&nVal1a = (float)(rand() % 2 + 4);
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetField084(nVal1a);
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetState(1058642330);
          nVal1b = (float)right;
          fXa = (float)v20;
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::UpdateTransform(fXa, nVal1b);
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::CalcRenderDimensions(v3, (int)v2);
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetOffset(5.0, 3.0);
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetScale(1086324736, 1082130432);
          (((RenderTarget *)(&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id
                           + 146 * this->m_NoteItem[67].m_NoteLv[0].m_FVF)))->RenderTarget::SetVisible(1);
        }
        v9 = this->m_NoteItem[67].m_NoteLv[0].m_FVF + 1;
        this->m_NoteItem[67].m_NoteLv[0].m_FVF = v9;
        if ( v9 >= 168 )
          this->m_NoteItem[67].m_NoteLv[0].m_FVF = 0;
      }
      p_m_id = (unsigned int *)&this->m_NoteItem[12].m_HeadShot_NO_SEL[1].m_id;
      v11 = 168;
      do
      {
        if ( IsVisible((RenderTarget *)(p_m_id + 24532)) )
          (((UIParticle *)(p_m_id + 24532)))->UIParticle::Apply(8);
        if ( IsVisible((RenderTarget *)p_m_id) )
          (((UIParticle *)p_m_id))->UIParticle::Apply(12);
        p_m_id += 146;
        --v11;
      }
      while ( v11 );
    }
    if ( *((_BYTE *)&this->m_NoteItem[9].m_NotePic.m_fonttype + *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4]) )
    {
      for ( i = 0; i < 16; ++i )
      {
        if ( IsVisible((RenderTarget *)&this->m_par[5][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] + 4 + i].par_radiusY) )
          (((UIParticle *)&this->m_par[5][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] + 4 + i].par_radiusY))->UIParticle::Apply(11);
        if ( IsVisible((RenderTarget *)&this->m_par2[7][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] + 4 + i]._texName[140]) )
          (((UIParticle *)&this->m_par2[7][16 * *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] + 4 + i]._texName[140]))->UIParticle::Apply(10);
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
  int m_id; // ecx
  float v18; // st7
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
  int v33; // [esp+0x8] [ebp-0x24]
  int v34; // [esp+0x8] [ebp-0x24]
  int v35; // [esp+0xC] [ebp-0x20]
  char v36; // [esp+0x10] [ebp-0x1C]
  int v37; // [esp+0x14] [ebp-0x18]
  int v38; // [esp+0x18] [ebp-0x14] BYREF
  gbTexture *m_pbk; // [esp+0x1C] [ebp-0x10]
  _DWORD p_DWORD[3]; // [esp+0x20] [ebp-0xC] BYREF

  HIBYTE(v38) = 0;
  v4 = (((TextureLib *)&this->m_NoteItem[67].m_NoteTime.m_fontcolor))->TextureLib::CreateFromMemory((_BYTE *)&v38 + 3, 5, 0);
  if ( HIBYTE(v38) && v4 )
    (((gbGeomNode *)this->m_NoteItem[10].m_NoteID.m_pbk2))->gbGeomNode::ReplaceTexture(v4);
  v5 = (__int64)g_fGameTimer;
  v6 = (int)v5 / 3600;
  v7 = (int)v5 / 60 % 60;
  v8 = (int)v5 % 60;
  if ( (int)v5 / 3600 < 100 )
    sprintf(this->buf, "%02d:%02d:%02d", v6, v7, v8);
  else
    sprintf(this->buf, "%03d:%02d:%02d", v6, v7, v8);
  SetEnable((UICaption *)&this->m_par[5][3]._texName[148]);
  sprintf(this->buf, (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)&this->m_par[5][3]._element.m_childs.capacity);
  State = UIParabolaCtrl_GetState(v31);
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
    (((SwordUI *)this))->SwordUI::RenderSword();
    --*(_DWORD *)&this->m_IsMsg;
    p_DWORD[2] = 0;
    p_DWORD[0] = 6408;
    p_DWORD[1] = 1;
    (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::PassCmd(p_DWORD);
    sprintf(this->buf, "%s %d", (const char *)&dword_DC943C, *(_DWORD *)&this->m_IsMsg);
    SetEnable((UICaption *)&this->pStateUI);
    if ( *((_BYTE *)&g_nActorState + g_nFiveNimbusCount) )
    {
      (**((void ( ***)(gbTexture **, _DWORD))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))((gbTexture **)(&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount), (_DWORD)(0));
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
      (**((void ( ***)(char *, _DWORD))((UIWnd *)&this->m_NoteItem[10].m_HeadShot[3]) + 86 * g_nFiveNimbusCount))((char *)((char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount), (_DWORD)(0));
      (**((void ( ***)(LONG *, _DWORD))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right
        + 38 * g_nFiveNimbusCount))((LONG *)(&this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount), (_DWORD)(0));
      (**((void ( ***)(char *, _DWORD))((UIWnd *)&this->m_NoteItem[10].m_HeadShot[3]) + 86 * g_nFiveNimbusCount))((char *)((char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount), (_DWORD)(0));
      (**((void ( ***)(LONG *, _DWORD))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right
        + 38 * g_nFiveNimbusCount))((LONG *)(&this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount), (_DWORD)(0));
      (**((void ( ***)(gbTexture **, _DWORD))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))((gbTexture **)(&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount), (_DWORD)(0));
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
      (**((void ( ***)(LONG *, int))&this->m_NoteItem[11].m_NotePic.m_rect.right + 38 * g_nFiveNimbusCount))((LONG *)(&this->m_NoteItem[11].m_NotePic.m_rect.right + 38 * g_nFiveNimbusCount), (int)(1));
      *((_BYTE *)&g_nActorState + g_nFiveNimbusCount) = 1;
    }
    else if ( *((_BYTE *)&g_nRoleState + g_nFiveNimbusCount + 1) )
    {
      (**((void ( ***)(gbTexture **, _DWORD))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))((gbTexture **)(&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount), (_DWORD)(0));
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
      (**((void ( ***)(char *, _DWORD))((UIWnd *)&this->m_NoteItem[10].m_HeadShot[3]) + 86 * g_nFiveNimbusCount))((char *)((char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount), (_DWORD)(0));
      (**((void ( ***)(LONG *, int))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount))((LONG *)(&this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount), (int)(1));
      *((_BYTE *)&g_nRoleParam + g_nFiveNimbusCount) = 1;
    }
    else
    {
      (**((void ( ***)(gbTexture **, int))&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2
        + 86 * g_nFiveNimbusCount))((gbTexture **)(&this->m_NoteItem[11].m_HeadShot_NO_SEL[0].m_pbk2 + 86 * g_nFiveNimbusCount), (int)(1));
      (*(void ( **)(LONG *, _DWORD))this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right)(
        &this->m_NoteItem[11].m_NoteLv[g_nFiveNimbusCount].m_rect.right,
        0);
      (**((void ( ***)(char *, _DWORD))((UIWnd *)&this->m_NoteItem[10].m_HeadShot[3]) + 86 * g_nFiveNimbusCount))((char *)((char *)&this->m_NoteItem[10].m_HeadShot[3] + 344 * g_nFiveNimbusCount), (_DWORD)(0));
      (**((void ( ***)(LONG *, _DWORD))&this->m_NoteItem[11].m_NoteItemBk.m_rect.right
        + 38 * g_nFiveNimbusCount))((LONG *)(&this->m_NoteItem[11].m_NoteItemBk.m_rect.right + 38 * g_nFiveNimbusCount), (_DWORD)(0));
      if ( HIBYTE(this->m_par[4][0]._element.m_texty) )
        *((_BYTE *)&g_nRoleParam + g_nFiveNimbusCount) = 1;
      else
        *((_BYTE *)&g_nRoleState + g_nFiveNimbusCount + 1) = 1;
    }
    this->SystemUI::CreateNoteEntry(0, v32, v35, v36, v37, v38, (unsigned __int8)m_pbk);
    (((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo))->UIListBox::ClearAll();
    (((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo))->UIListBox::GetItem();
    m_pData = this->m_NoteItem[67].m_HeadShot[1].m_childs.m_pData;
    if ( HIBYTE(this->m_par[4][0]._element.m_texty) )
    {
      (*(void ( **)(int, int))m_pData)(1, v33);
      m_nTextW = (void ( **)(int *))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      p_m_nTextW = (int *)&this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      v34 = 0;
    }
    else
    {
      (*(void ( **)(_DWORD, int))m_pData)(0, v33);
      m_nTextW = (void ( **)(int *))this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      p_m_nTextW = (int *)&this->m_NoteItem[67].m_HeadShot_NO_SEL[3].m_nTextW;
      v34 = 1;
    }
    (*m_nTextW)(p_m_nTextW);
    value = *(_DWORD *)&this->m_par[4][3]._texName[200];
    *((_DWORD *)&this->m_Frame + 38) = 0;
    this->m_Frame.m_nTextW = 0;
    this->m_TimeMoney.m_wndcolor.Color = 0;
    this->m_TimeMoney.m_fontcolor.Color = 0;
    *(_DWORD *)((UIWnd *)&this->m_TimeMoney) = 0;
    *((_DWORD *)&this->m_Frame + 39) = 0;
    this->m_TimeMoney.m_rect.left = 0;
    this->m_TimeMoney.m_id = 0;
    *(_DWORD *)&this->m_par[4][3]._texName[204] = 0;
    sprintf(this->buf, "%d/%d", 0, value);
    SetEnable((UICaption *)&this->m_NoteItem[71].m_NoteLv[1].m_pbkInfo);
    memset(&this->m_par[4][0]._element.m_text[12], 0, 0x630u);
    SystemUI_UpdateNoteScrollAlt(v34);
    v27 = (const void *)off_5CF220;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v27, 1);
  }
  if ( LOBYTE(this->m_par[4][0]._element.m_texty) )
  {
    if ( this->m_NoteItem[67].m_NoteLv[0].m_mouseoff )
    {
      v16 = (__int64)((double)(int)this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color - *(float *)&nVal * 500.0);
      m_id = this->m_NoteItem[67].m_NoteLv[1].m_id;
      this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color = v16;
      if ( (int)v16 <= m_id )
        this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color = m_id;
      valuea = (float)(int)this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color;
      (((CCBFiveNimbusWindow *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel))->CCBFiveNimbusWindow::SetFloatParam(valuea);
    }
    if ( *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 2) )
    {
      v18 = *(float *)&nVal * 460.0f + *(float *)&this->m_par[4][0]._element.m_text[8];
      *(float *)&this->m_par[4][0]._element.m_text[8] = v18;
      if ( v18 >= 0.0f )
        *(_DWORD *)&this->m_par[4][0]._element.m_text[8] = 0;
      *(_DWORD *)&this->m_NoteItem[10].m_NoteState.m_mouseoff = 1;
      UIPushButton_SetParam(*(_DWORD *)&this->m_par[4][0]._element.m_text[8]);
      if ( *(float *)&this->m_par[4][0]._element.m_text[8] == 0.0f )
      {
        *(_DWORD *)&this->m_NoteItem[10].m_NoteState.m_mouseoff = 98;
        UIPushButton_SetParam(0);
        sub_43A090(
          (int)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel,
          2,
          *(float *)&this->m_par[4][0]._element.m_text[4]);
        LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) = 1;
        this->m_NoteItem[67].m_NoteLv[0].m_mouseoff = 0;
        *(_WORD *)(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 1) = 1;
        SystemUI_UpdateNoteScroll(v32);
        valueb = (float)(int)this->m_NoteItem[67].m_NoteLv[1].m_id;
        (((CCBFiveNimbusWindow *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel))->CCBFiveNimbusWindow::SetFloatParam(valueb);
      }
    }
    if ( this->m_NoteItem[10].m_HeadShot[2].m_nTextW )
    {
      p_m_pbk = (gbTexture **)&this->m_NoteItem[10].m_HeadShot[2].m_pbk;
      HIWORD(v20) = 0;
      m_pbk = (gbTexture *)this->m_NoteItem[10].m_HeadShot[2].m_pbk;
      LOWORD(v20) = this->m_NoteItem[10].m_HeadShot[2].m_FVF;
      if ( (int)m_pbk > (unsigned __int16)v20 )
      {
        v21 = (__int64)((double)(int)m_pbk - *(float *)&nVal * 220.0);
        *p_m_pbk = (gbTexture *)v21;
        if ( (int)v21 <= v20 )
          *p_m_pbk = (gbTexture *)v20;
        this->m_NoteItem[10].m_HeadShot[2].m_ppic = (gbTexture *)((char *)*p_m_pbk + 218);
LABEL_41:
        (((UIWnd *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible))->UIWnd::sub_445FA0(p_m_pbk);
        v24 = (gbTexture *)*p_m_pbk;
        v25 = (char *)&this->m_NoteItem[10].m_HeadShot[2].m_pbkInfo->name[32];
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[4] = (_DWORD)v25;
        *(_DWORD *)this->m_NoteItem[10].m_HeadShot[2].m_text = (_DWORD)&v24->IsLoaded;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[8] = (unsigned long)((char *)v24 + 212);
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[12] = (_DWORD)v25 + 326;
        (((UIWnd *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible))->UIWnd::sub_445FA0(this->m_NoteItem[10].m_HeadShot[2].m_text);
      }
    }
    else
    {
      p_m_pbk = (gbTexture **)&this->m_NoteItem[10].m_HeadShot[2].m_pbk;
      HIWORD(v22) = 0;
      m_pbk = (gbTexture *)this->m_NoteItem[10].m_HeadShot[2].m_pbk;
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
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
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
  int *p_IsLoaded; // ecx
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
  int RoleNum; // eax
  Parent_Data *m_fonttype; // eax
  int v49; // eax
  UIListBox *p_m_ppicInfo; // edi
  Parent_Data *Child; // eax
  Parent_Data *v52; // eax
  Parent_Data *v53; // eax
  Parent_Data *v54; // eax
  Parent_Data *v55; // eax
  int ItemData; // ebx
  _PlugInfo **p_m_pbkInfo; // ebp
  int LockedSel; // edi
  int v59; // eax
  _PlugInfo **v60; // ecx
  int v61; // esi
  const char *v62; // [esp-0x8] [ebp-ACh]
  const char *v63; // [esp-0x8] [ebp-ACh]
  const void *v64; // [esp-0x8] [ebp-ACh]
  const void *v65; // [esp-0x8] [ebp-ACh]
  const char *v66; // [esp-0x8] [ebp-ACh]
  const char *v67; // [esp-0x8] [ebp-ACh]
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
  int v85; // [esp-0x4] [ebp-A8h]
  int v86; // [esp-0x4] [ebp-A8h]
  int v87; // [esp-0x4] [ebp-A8h]
  int v88; // [esp+0x0] [ebp-A4h]
  int v89; // [esp+0x0] [ebp-A4h]
  int v90; // [esp+0x0] [ebp-A4h]
  int v91; // [esp+0x0] [ebp-A4h]
  int v92; // [esp+0x0] [ebp-A4h]
  int v93; // [esp+0x0] [ebp-A4h]
  int v94; // [esp+0x4] [ebp-A0h]
  char v95; // [esp+0x8] [ebp-0x9C]
  int v96; // [esp+0xC] [ebp-0x98]
  _BYTE String1[12]; // [esp+0x10] [ebp-0x94] BYREF
  int a2; // [esp+0x1C] [ebp-0x88]
  int v99; // [esp+0x20] [ebp-0x84]
  char Buffer[125]; // [esp+0x24] [ebp-0x80] BYREF
  __int16 v101; // [esp+A1h] [ebp-0x3]
  char v102; // [esp+A3h] [ebp-0x1]

  switch ( nVal )
  {
    case 1000:
      if ( pWnd )
      {
        for ( i = 0; i < 8; ++i )
          SystemUI_InitSlotEffects(i);
        this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 0;
        SystemUI_ShowPage(v88);
        SystemUI_ReplaceTextures(v89);
        *(_DWORD *)&String1[4] = 0;
        *(_DWORD *)&String1[8] = 0;
        *(_DWORD *)String1 = 6408;
        v8 = (((CCBStage *)(&g_RoleSlotBuf.dword_17AA450 + 138)))->CCBStage::GetByIndex((int *)String1);
        if ( v8 )
          *(_DWORD *)&this->m_IsMsg = (unsigned long)v8[1];
        else
          *(_DWORD *)&this->m_IsMsg = 0;
        sprintf(this->buf, "%s %d", (const char *)&dword_DC943C, *(_DWORD *)&this->m_IsMsg);
        SetEnable((UICaption *)&this->pStateUI);
        *((_DWORD *)&this->m_Frame + 38) = 0;
        m_bvisible = (void ( **)(int *, _DWORD))this->m_NoteItem[10].m_HeadShot[0].m_bvisible;
        this->m_Frame.m_nTextW = 0;
        this->m_TimeMoney.m_wndcolor.Color = 0;
        this->m_TimeMoney.m_fontcolor.Color = 0;
        *(_DWORD *)((UIWnd *)&this->m_TimeMoney) = 0;
        *((_DWORD *)&this->m_Frame + 39) = 0;
        this->m_TimeMoney.m_rect.left = 0;
        this->m_TimeMoney.m_id = 0;
        (*m_bvisible)(&this->m_NoteItem[10].m_HeadShot[0].m_bvisible, g_bUIWnd_DE625A);
        this->m_NoteItem[67].m_NoteLv[1].m_wndcolor.Color = 1000;
        (((CCBFiveNimbusWindow *)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel))->CCBFiveNimbusWindow::SetFloatParam(1000.0);
        this->SystemUI::CreateNoteEntry(0, v90, v94, v95, v96, *(int *)String1, String1[4]);
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
        if ( g_RoleSlotBuf.m_partyActor.m_pSelfAtt )
          this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] = *(_DWORD *)g_RoleSlotBuf.m_partyActor.m_pSelfAtt == 6603;
        else
          this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] = 0;
        this->m_NoteItem[10].m_HeadShot[2].m_pbk = this->m_NoteItem[10].m_HeadShot[2].m_disablepic;
        this->m_NoteItem[10].m_HeadShot[2].m_pbkInfo = this->m_NoteItem[10].m_HeadShot[2].m_disablepicInfo;
        this->m_NoteItem[10].m_HeadShot[2].m_ppic = this->m_NoteItem[10].m_HeadShot[2].m_pbk2;
        this->m_NoteItem[10].m_HeadShot[2].m_ppicInfo = *(_PlugInfo **)&this->m_NoteItem[10].m_HeadShot[2].m_mouseoff;
        (((UIWnd *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[3].m_bvisible))->UIWnd::sub_445FA0(&this->m_NoteItem[10].m_HeadShot[2].m_pbk);
        v12 = (char *)&this->m_NoteItem[10].m_HeadShot[2].m_pbkInfo->name[32];
        p_IsLoaded = (int *)&this->m_NoteItem[10].m_HeadShot[2].m_pbk->IsLoaded;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[4] = (_DWORD)v12;
        *(_DWORD *)this->m_NoteItem[10].m_HeadShot[2].m_text = (_DWORD)p_IsLoaded;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[8] = (_DWORD)p_IsLoaded + 49;
        *(_DWORD *)&this->m_NoteItem[10].m_HeadShot[2].m_text[12] = (_DWORD)v12 + 326;
        (((UIWnd *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible))->UIWnd::sub_445FA0(this->m_NoteItem[10].m_HeadShot[2].m_text);
        if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
          this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 1;
        else
          this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 0;
        SetEnable((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
        this->m_NoteItem[9].m_NotePic.m_fonttype = ((Parent_Data *)0);
        *(_DWORD *)this->m_NoteItem[9].m_NotePic.m_text = 0;
        (((UICursor *)&this->m_NoteItem[9].m_NotePic.m_fonttype))->UICursor::_todo_541CC0();
        LOBYTE(this->m_par[4][0]._element.m_texty) = 1;
        return 1;
      }
      else
      {
        LOBYTE(this->m_par[4][0]._element.m_texty) = 0;
        this->SystemUI::CreateNoteEntry(0, v88, v94, v95, v96, *(int *)String1, String1[4]);
        UIListBox_ResetAllListBoxes(v91);
        UIListBox_ShowSlotUI(v92);
        this->m_NoteItem[67].m_NoteLv[0].m_mouseoff = 1;
        *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 1) = 0;
        *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 2) = 1;
        *(_DWORD *)&this->m_par[4][0]._element.m_text[8] = -997785600;
        *(&this->m_NoteItem[67].m_NoteLv[0].m_mouseoff + 3) = 1;
        return 1;
      }
    case 1001:
      v15 = (UIWnd *)pWnd;
      v99 = 0;
      v16 = (const char **)&off_56F1F4;
      a2 = (int)&this->m_NoteItem[67].m_NoteLv[2].m_ppic;
      do
      {
        if ( v15 == (UIWnd *)*v16 )
        {
          if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
            goto LABEL_54;
          p_m_ppic = (gbTexture **)&this->m_NoteItem[67].m_NoteLv[2].m_ppic;
          v18 = 5;
          do
          {
            sub_445E50((int)p_m_ppic);
            p_m_ppic += 86;
            --v18;
          }
          while ( v18 );
          sub_445E50(a2);
          CCBCamControl_ShowAllSlots(v99);
          v62 = g_pCScreenMode_5CF1E8;
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v62, 1);
          v15 = (UIWnd *)pWnd;
        }
        ++v16;
        ++v99;
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
                      v67 = (const char *)v25;
                    }
                    else
                    {
                      BYTE2(this->m_par[4][0]._element.m_texty) = 0;
                      this->SystemUI::CreateNoteEntry(1, v88, v94, v95, v96, *(int *)String1, String1[4]);
                      CCBCamControl_ShowAllSlots(0);
                      v67 = g_pCScreenMode_5CF1E8;
                    }
                    goto LABEL_107;
                  }
                }
                goto LABEL_54;
              }
LABEL_40:
              sprintf(this->buf, "\\n\\n      %s", (const char *)&dword_DD3D3C);
              SetEnable((UICaption *)&this->m_NoteItem[72].m_isHead[4]);
              (((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor))->UIRoleSelect::SetByte(1);
              v65 = (const void *)off_5CF1F0;
              v23 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v23))->CScreenMode::AudioSetPosition(v65, 1);
              return 1;
            }
LABEL_38:
            sprintf(this->buf, "\\n     %s\\n     %s", (const char *)&dword_DD253C, (const char *)&dword_DD433C);
            SetEnable((UICaption *)&this->m_NoteItem[72].m_isHead[4]);
            (((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor))->UIRoleSelect::SetByte(1);
            v64 = (const void *)off_5CF1F0;
            v22 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v22))->CScreenMode::AudioSetPosition(v64, 1);
            return 1;
          }
          goto LABEL_54;
        }
        if ( ++v20 >= 5 )
        {
          if ( v15 > (UIWnd *)&byte_A00110 )
          {
            switch ( (unsigned int)v15 )
            {
              case 0xA00536u:
                (((CCBUI *)this))->CCBUI::CreatePanelUI();
                return 1;
              case 0xA00537u:
                UIListBox_ResetAllListBoxes(v88);
                this->SystemUI::CreateNoteEntry(0, v93, v94, v95, v96, *(int *)String1, String1[4]);
                goto LABEL_106;
              case 0xA00555u:
                v85 = *(_DWORD *)this->m_par[4][0]._element.m_text;
                this->m_NoteItem[72].m_HeadShot[1].m_pbk = ((gbTexture *)0);
                UIListBox__todo(v85);
                goto LABEL_98;
              case 0xA00556u:
                v86 = *(_DWORD *)this->m_par[4][0]._element.m_text;
                this->m_NoteItem[72].m_HeadShot[1].m_pbk = (gbTexture *)1;
                UIListBox__todo(v86);
                v67 = g_pCScreenMode_5CF1E8;
                goto LABEL_107;
              case 0xA00557u:
                (((CCBUI *)this))->CCBUI::DestroyDynamic(0);
                goto LABEL_98;
              case 0xA00558u:
                v84 = g_pCScreenMode_5CF1E8;
                v45 = (CScreenMode *)CScreenMode::GetInstance();
                (((CScreenMode *)v45))->CScreenMode::AudioSetPosition(v84, 1);
                (((CCBUI *)this))->CCBUI::DestroyDynamic(1);
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
                SystemUI_UpdateNoteScroll(v88);
                sub_43A090(
                  (int)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel,
                  2,
                  *(float *)&this->m_par[4][0]._element.m_text[4]);
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
                  SystemUI_UpdateNoteScroll(v88);
                  sub_43A090(
                    (int)&this->m_NoteItem[10].m_NoteID.m_childs.m_needscriptdel,
                    2,
                    *(float *)&this->m_par[4][0]._element.m_text[4]);
LABEL_106:
                  v67 = g_pCScreenMode_5CF1E8;
                }
                else
                {
                  v67 = g_pCScreenMode_5CF1F4;
                }
                goto LABEL_107;
              case 0xA00571u:
                if ( g_ScriptSystemData.m_nGameMode == 2 )
                {
                  sprintf(this->buf, "\\n\\n    %s", &byte_DDA73C[256]);
                  SetEnable((UICaption *)&this->m_NoteItem[72].m_isHead[4]);
                  (((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor))->UIRoleSelect::SetByte(1);
                  v67 = (const char *)off_5CF1F0;
                  goto LABEL_107;
                }
                if ( UIScene::ProcessInput("Q14", 0) )
                {
                  sprintf(this->buf, "\\n\\n       %s", (const char *)&dword_DC9F3C);
                  SetEnable((UICaption *)&this->m_NoteItem[72].m_isHead[4]);
                  (((UIRoleSelect *)&this->m_NoteItem[72].m_HeadShot[2].m_fontcolor))->UIRoleSelect::SetByte(1);
                  v25 = (const char *)off_5CF1F0;
                  goto LABEL_57;
                }
                v83 = g_pCScreenMode_5CF1E8;
                v41 = (CScreenMode *)CScreenMode::GetInstance();
                (((CScreenMode *)v41))->CScreenMode::AudioSetPosition(v83, 1);
                (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(8);
                result = 1;
                break;
              default:
                return 1;
            }
          }
          else if ( v15 == (UIWnd *)&byte_A00110 )
          {
            if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
            {
              v82 = g_pCScreenMode_5CF1E8;
              v40 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v40))->CScreenMode::AudioSetPosition(v82, 1);
              (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(9);
            }
            else
            {
              v81 = g_pCScreenMode_5CF1F4;
              v39 = (CScreenMode *)CScreenMode::GetInstance();
              (((CScreenMode *)v39))->CScreenMode::AudioSetPosition(v81, 1);
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
                  v68 = g_pCScreenMode_5CF1E8;
                  v26 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v26))->CScreenMode::AudioSetPosition(v68, 1);
                  (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(0);
                }
                else
                {
                  v63 = g_pCScreenMode_5CF1F4;
                  v21 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v21))->CScreenMode::AudioSetPosition(v63, 1);
                }
                result = 1;
                break;
              case 0xA00103u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v70 = g_pCScreenMode_5CF1E8;
                  v28 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v28))->CScreenMode::AudioSetPosition(v70, 1);
                  (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(3);
                }
                else
                {
                  v69 = g_pCScreenMode_5CF1F4;
                  v27 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v27))->CScreenMode::AudioSetPosition(v69, 1);
                }
                result = 1;
                break;
              case 0xA00104u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v72 = g_pCScreenMode_5CF1E8;
                  v30 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v30))->CScreenMode::AudioSetPosition(v72, 1);
                  (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(2);
                }
                else
                {
                  v71 = g_pCScreenMode_5CF1F4;
                  v29 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v29))->CScreenMode::AudioSetPosition(v71, 1);
                }
                result = 1;
                break;
              case 0xA00105u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v74 = g_pCScreenMode_5CF1E8;
                  v32 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v32))->CScreenMode::AudioSetPosition(v74, 1);
                  (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(1);
                }
                else
                {
                  v73 = g_pCScreenMode_5CF1F4;
                  v31 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v31))->CScreenMode::AudioSetPosition(v73, 1);
                }
                result = 1;
                break;
              case 0xA00107u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v76 = g_pCScreenMode_5CF1E8;
                  v34 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v34))->CScreenMode::AudioSetPosition(v76, 1);
                  (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(6);
                }
                else
                {
                  v75 = g_pCScreenMode_5CF1F4;
                  v33 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v33))->CScreenMode::AudioSetPosition(v75, 1);
                }
                result = 1;
                break;
              case 0xA00108u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v78 = g_pCScreenMode_5CF1E8;
                  v36 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v36))->CScreenMode::AudioSetPosition(v78, 1);
                  (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(4);
                }
                else
                {
                  v77 = g_pCScreenMode_5CF1F4;
                  v35 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v35))->CScreenMode::AudioSetPosition(v77, 1);
                }
                result = 1;
                break;
              case 0xA00109u:
                if ( LOBYTE(this->m_NoteItem[12].m_NoteID.m_ppic) )
                {
                  v80 = g_pCScreenMode_5CF1E8;
                  v38 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v38))->CScreenMode::AudioSetPosition(v80, 1);
                  (((MainEquipUI *)*(MainEquipUI **)&this->m_par[4][3]._texName[208]))->MainEquipUI::HandleMessage(7);
                }
                else
                {
                  v79 = g_pCScreenMode_5CF1F4;
                  v37 = (CScreenMode *)CScreenMode::GetInstance();
                  (((CScreenMode *)v37))->CScreenMode::AudioSetPosition(v79, 1);
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
            this->SystemUI::CreateNoteEntry(1, v88, v94, v95, v96, *(int *)String1, String1[4]);
            CCBCamControl_ShowAllSlots(0);
LABEL_98:
            v67 = g_pCScreenMode_5CF1E8;
            goto LABEL_107;
          }
        }
      }
LABEL_54:
      v66 = g_pCScreenMode_5CF1F4;
      v24 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v24))->CScreenMode::AudioSetPosition(v66, 1);
      return 1;
    case 1002:
      v46 = 0;
      while ( (pWnd != (UIWnd *)(&off_56F1CC)[v46] || !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0])
           && (pWnd != (UIWnd *)(&off_56F1E0)[v46] || !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0])
           && (pWnd != (UIWnd *)(&off_56F1A4)[v46] || !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0])
           && (pWnd != (UIWnd *)(&off_56F1B8)[v46] || !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0])
           && (pWnd != (UIWnd *)(&off_56F208)[v46] || !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0]) )
      {
        if ( ++v46 >= 5 )
          goto LABEL_144;
      }
      SetEnable((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
LABEL_144:
      switch ( (unsigned int)pWnd )
      {
        case 0xA00510u:
          if ( !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
            goto LABEL_162;
          goto LABEL_161;
        case 0xA00564u:
        case 0xA00565u:
          if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
            goto LABEL_161;
          goto LABEL_162;
        case 0xA00571u:
          goto LABEL_161;
        case 0xA00572u:
          if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
          {
            this->buf[0] = 0;
            RoleNum = (((PAL_GDB *)&g_pGDB))->PAL_GDB::GDB_GetRoleNum(*(int *)&g_RoleSlotBuf.m_partyActor.m_curact[11]);
            if ( RoleNum )
              lstrcpyA(this->buf, (LPCSTR)(RoleNum + 60));
            else
              lstrcpyA(this->buf, unk_C10D38);
            m_fonttype = (Parent_Data *)this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_fonttype;
            memset(String1, 0, 10);
            switch ( (unsigned int)m_fonttype )
            {
              case 0u:
                lstrcpyA((char *)String1, (LPCSTR)g_bSlotFlag);
                break;
              case 1u:
                lstrcpyA((char *)String1, (LPCSTR)&g_bSlotFlag[256]);
                break;
              case 2u:
                lstrcpyA((char *)String1, byte_DC3F3C);
                break;
              case 3u:
                lstrcpyA((char *)String1, (LPCSTR)&g_bSlotFlag[512]);
                break;
              case 4u:
                lstrcpyA((char *)String1, byte_DC403C);
                break;
              default:
                break;
            }
            memset(Buffer, 0, sizeof(Buffer));
            v101 = 0;
            v102 = 0;
            sprintf(
              Buffer,
              "\\n\\n%s: %d\\n%s:   %s",
              (const char *)&dword_DCE93C,
              *(_DWORD *)&g_RoleSlotBuf.m_partyActor.m_curact[15],
              (const char *)&dword_DC933C,
              String1);
            lstrcatA(this->buf, Buffer);
LABEL_161:
            SetEnable((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
LABEL_162:
            switch ( (unsigned int)pWnd )
            {
              case 0xA00102u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 0;
                if ( LOBYTE(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_179;
                SystemUI_InitSlotEffects(0);
                result = 1;
                break;
              case 0xA00103u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 1;
                if ( BYTE1(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_179;
                SystemUI_InitSlotEffects(1);
                result = 1;
                break;
              case 0xA00104u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 2;
                if ( BYTE2(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_179;
                SystemUI_InitSlotEffects(2);
                result = 1;
                break;
              case 0xA00105u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 3;
                if ( HIBYTE(this->m_NoteItem[9].m_NotePic.m_fonttype) )
                  goto LABEL_179;
                SystemUI_InitSlotEffects(3);
                result = 1;
                break;
              case 0xA00106u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 5;
                if ( this->m_NoteItem[9].m_NotePic.m_text[1] )
                  goto LABEL_179;
                SystemUI_InitSlotEffects(5);
                result = 1;
                break;
              case 0xA00107u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 6;
                if ( this->m_NoteItem[9].m_NotePic.m_text[2] )
                  goto LABEL_179;
                SystemUI_InitSlotEffects(6);
                result = 1;
                break;
              case 0xA00108u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 4;
                if ( this->m_NoteItem[9].m_NotePic.m_text[0] )
                  goto LABEL_179;
                SystemUI_InitSlotEffects(4);
                result = 1;
                break;
              case 0xA00109u:
                *(_DWORD *)&this->m_NoteItem[9].m_NotePic.m_text[4] = 7;
                if ( !this->m_NoteItem[9].m_NotePic.m_text[3] )
                  SystemUI_InitSlotEffects(7);
                goto LABEL_179;
              default:
LABEL_179:
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
          goto LABEL_162;
      }
      return result;
    case 1003:
      v49 = 0;
      break;
    case 1007:
      this->m_par[4][0]._element.m_fonttype = (Parent_Data *)nVal2;
      return 1;
    case 1008:
      switch ( (unsigned int)pWnd )
      {
        case 0xA00529u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[69].m_NoteTime.m_ppicInfo;
          Child = (Parent_Data *)(((UIListBox *)&this->m_NoteItem[69].m_NoteTime.m_ppicInfo))->UIListBox::CreateChild();
          this->m_par[4][0]._element.m_fonttype = Child;
          if ( (int)Child < 0 )
          {
            v67 = g_pCScreenMode_5CF1F4;
            break;
          }
          UIListBox_InsertUIListBox(0);
          goto LABEL_221;
        case 0xA00530u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[69].m_NotePicName.m_pbkInfo;
          v52 = (Parent_Data *)(((UIListBox *)&this->m_NoteItem[69].m_NotePicName.m_pbkInfo))->UIListBox::CreateChild();
          this->m_par[4][0]._element.m_fonttype = v52;
          v87 = 1;
          if ( (int)v52 >= 0 )
            goto LABEL_220;
          v67 = g_pCScreenMode_5CF1F4;
          break;
        case 0xA00531u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok;
          v53 = (Parent_Data *)(((UIListBox *)&this->m_NoteItem[70].m_HeadShot_NO_SEL[3].m_bcreateok))->UIListBox::CreateChild();
          this->m_par[4][0]._element.m_fonttype = v53;
          if ( (int)v53 < 0 )
          {
            v67 = g_pCScreenMode_5CF1F4;
            break;
          }
          UIListBox_InsertUIListBox(2);
          goto LABEL_221;
        case 0xA00532u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[70].m_NoteMoney.m_childs;
          v54 = (Parent_Data *)(((UIListBox *)&this->m_NoteItem[70].m_NoteMoney.m_childs))->UIListBox::CreateChild();
          this->m_par[4][0]._element.m_fonttype = v54;
          if ( (int)v54 < 0 )
          {
            v67 = g_pCScreenMode_5CF1F4;
            break;
          }
          UIListBox_InsertUIListBox(3);
          goto LABEL_221;
        case 0xA00533u:
          p_m_ppicInfo = (UIListBox *)&this->m_NoteItem[71].m_NoteItemBk.m_id;
          v55 = (Parent_Data *)(((UIListBox *)&this->m_NoteItem[71].m_NoteItemBk.m_id))->UIListBox::CreateChild();
          this->m_par[4][0]._element.m_fonttype = v55;
          if ( (int)v55 >= 0 )
          {
            v87 = 4;
LABEL_220:
            UIListBox_InsertUIListBox(v87);
LABEL_221:
            ItemData = (((UIListBox *)p_m_ppicInfo))->UIListBox::GetItemData();
            (((UIListBox *)p_m_ppicInfo))->UIListBox::GetItem();
            if ( ItemData < (int)this->m_par[4][0]._element.m_fonttype )
              (((UIListBox *)p_m_ppicInfo))->UIListBox::GetItem();
            v67 = (const char *)off_5CF1EC;
          }
          else
          {
            v67 = g_pCScreenMode_5CF1F4;
          }
          break;
        case 0xA00534u:
          p_m_pbkInfo = (_PlugInfo **)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo;
          LockedSel = (((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo))->UIListBox::GetLockedSel();
          if ( LockedSel < 0
            || LockedSel >= (((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo))->UIListBox::GetItemData() )
          {
            goto LABEL_56;
          }
          UIListBox_ProcessListInput(LockedSel);
          v59 = (((UIListBox *)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo))->UIListBox::GetItemData();
          v60 = (_PlugInfo **)&this->m_NoteItem[71].m_HeadShot_NO_SEL[3].m_pbkInfo;
          v61 = v59;
          (((UIListBox *)v60))->UIListBox::GetItem();
          if ( v61 < LockedSel )
            (((UIListBox *)p_m_pbkInfo))->UIListBox::GetItem();
          v67 = (const char *)off_5CF1EC;
          break;
        default:
          return 1;
      }
LABEL_107:
      v44 = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)v44))->CScreenMode::AudioSetPosition(v67, 1);
      return 1;
    case 1014:
      if ( !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0]
        || pWnd != (UIWnd *)&byte_A00539 && (char *)pWnd - (char *)&byte_A00539 != 7 )
      {
        return 1;
      }
      goto LABEL_128;
    case 1015:
      if ( !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
        return 1;
      if ( pWnd == (UIWnd *)&byte_A00539 || (char *)pWnd - (char *)&byte_A00539 == 7 )
LABEL_128:
        SetEnable((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
      return 1;
    case 1017:
      result = 1;
      if ( pWnd == (UIWnd *)&byte_A00539 )
        this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 1;
      return result;
    case 1018:
      if ( pWnd != (UIWnd *)&byte_A00539 )
        return 1;
      this->m_NoteItem[10].m_HeadShot[2].m_nTextW = 0;
      return 1;
    default:
      return this->UIWnd::OnMessage(nVal, (int)pWnd, nVal2);
  }
  while ( pWnd != (UIWnd *)(&off_56F1CC)[v49]
       && !(&off_56F1E0)[v49]
       && !(&off_56F1A4)[v49]
       && !(&off_56F1B8)[v49]
       && !(&off_56F208)[v49] )
  {
    if ( ++v49 >= 5 )
      goto LABEL_191;
  }
  if ( !this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
    return 1;
  SetEnable((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
LABEL_191:
  switch ( (unsigned int)pWnd )
  {
    case 0xA00510u:
    case 0xA00564u:
    case 0xA00565u:
    case 0xA00571u:
    case 0xA00572u:
      if ( this->m_NoteItem[73].m_HeadShot_NO_SEL[1].m_text[0] )
        SetEnable((UICaption *)&this->m_NoteItem[10].m_HeadShot_NO_SEL[4].m_bvisible);
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
      goto LABEL_203;
    default:
LABEL_203:
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
