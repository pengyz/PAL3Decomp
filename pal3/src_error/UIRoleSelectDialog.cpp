#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIRoleSelectDialog.h"
#include "Role/Actor.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCBStage.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "Misc/PtrArray.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "Misc/UIButton.h"
#include "Misc/UICaption.h"
#include "Misc/UIFrameContainer.h"
#include "Misc/UIFrameWnd.h"
#include "UI/UIListBox.h"
#include "UI/UINote.h"
#include "Misc/UIPushButton.h"
#include "UI/UIQuadManager.h"
#include "UI/UIRenderObj.h"
#include "UI/UIScene.h"
#include "Misc/UISceneMap.h"
#include "Misc/UIStatic.h"
#include "Misc/UITextArea.h"
#include "Misc/UITextureArray.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x00451980
int UIRoleSelectDialog::CreateDialog(int id, void *pRect, int parent, char *tex)
{
  int v6; // eax
  unsigned int m_id; // edx
  int result; // eax
  _DWORD v9[2]; // [esp+0x18] [ebp-0x10] BYREF
  int v10; // [esp+0x20] [ebp-0x8]
  int v11; // [esp+0x24] [ebp-0x4]

  this->UIWnd::Create(id, (tagRECT *)pRect, parent);
  (((UINote *)&this->m_list.m_column[0].items.capacity))->UINote::Create(0, (int)pRect, (int)this, "ui\\flex\\note");
  (((UIWnd *)&this->m_list.m_column[0].items.capacity))->UIWnd::sub_445FA0(pRect);
  v6 = *((_DWORD *)pRect + 3);
  v10 = *((_DWORD *)pRect + 2) - *(_DWORD *)pRect - 16;
  m_id = this->m_bk.m_id;
  v11 = v6 - *((_DWORD *)pRect + 1) - 16;
  v9[0] = 8;
  v9[1] = 0;
  (*(void ( **)(unsigned int *, _DWORD, _DWORD *, UIRoleSelectDialog *, _DWORD, _DWORD, _DWORD))(m_id + 28))(
    &this->m_bk.m_id,
    0,
    (_DWORD *)(v9),
    this,
    0,
    0,
    0);
  (((UIListBox *)&this->m_bk.m_id))->UIListBox::SetColumnHead((int)"_seldlg", v10 - v9[0]);
  UIListBox_SetItemData(1);
  AllocObject(&this->m_bk.m_id);
  (((UIListBox *)&this->m_bk.m_id))->UIListBox::GetSel((int)"ui\\scene\\SelPic.tga", 0);
  (**(void ( ***)(UIRoleSelectDialog *, _DWORD))((UIWnd *)this))((UIRoleSelectDialog *)(this), (_DWORD)(0));
  this->m_list.m_scrollbar.m_btnrect[1].right = 20;
  (((UIListBox *)&this->m_bk.m_id))->UIListBox::SetLockSel(20);
  return result;
}

// 0x005295F0
UIRoleSelectDialog::UIRoleSelectDialog()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->m_bk.m_id = 800;
  this->m_bk.m_rect.left = 600;
  LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 0;
  (((UIFrameContainer *)&this->m_ani.m_texarray.m_ptex[4]))->UIFrameContainer::ResetContainerState();
  ((CCBResultWindow *)&this->m_list.m_scrollbar.m_texarray)->CCBResultWindow::CCBResultWindow();
  this->m_list.m_column[0].head[32] = 0;
  *(_DWORD *)&this->m_list.m_column[0].head[28] = 0;
  *(_DWORD *)&this->m_list.m_column[0].head[24] = 0;
  this->m_list.m_column[0].head[52] = 0;
  *(_DWORD *)&this->m_list.m_column[0].head[48] = 0;
  *(_DWORD *)&this->m_list.m_column[0].head[44] = 0;
  (((UIFrameContainer *)&this->m_list.m_column[0].head[56]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_list.m_column[2].head[40]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_list.m_column[7].head[24]))->UIFrameContainer::ResetContainerState();
  (((UITextArea *)&this->m_list.m_rowenable[8]))->UITextArea::InitAfterClear();
  *(_DWORD *)&this->m_list.m_column[0].head[40] = 32;
  *(_DWORD *)&this->m_list.m_column[0].head[36] = 32;
  *(_DWORD *)&this->m_list.m_column[4].head[24] = 64;
  *(_DWORD *)&this->m_list.m_column[4].head[28] = 58;
  *(_DWORD *)&this->m_list.m_column[5].head[60] = 28;
  *(_DWORD *)&this->m_list.m_column[7].head[4] = 1065353216;
  *(_DWORD *)&this->m_list.m_column[7].head[8] = 1060152279;
  *(_DWORD *)&this->m_list.m_column[7].head[12] = 1036831949;
  *(_DWORD *)&this->m_list.m_column[7].head[16] = 1008981770;
  *(_DWORD *)&this->m_list.m_column[4].head[36] = 0;
  *(_DWORD *)&this->m_list.m_column[4].head[32] = 0;
  *(_DWORD *)&this->m_list.m_column[4].head[40] = 800;
  *(_DWORD *)&this->m_list.m_column[4].head[44] = 600;
  *(&this->m_mode + 24) = 0;
  *((_BYTE *)&this->m_mode + 108) = 1;
}

// 0x00529790
UIRoleSelectDialog::~UIRoleSelectDialog()
{
  UIQuadManager *Instance; // eax

  Instance = (UIQuadManager *)UIQuadManager::GetInstance();
  (((UIRenderObj *)Instance))->UIRenderObj::_sdtor_call_dtor(1);
  UITextArea_Destroy();
  (((UIFrameContainer *)&this->m_list.m_column[7].head[24]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_list.m_column[2].head[40]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_list.m_column[0].head[56]))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameWnd *)&this->m_list.m_scrollbar.m_texarray))->UIFrameWnd::_UIFrameWnd_Full();
  (((UIFrameContainer *)&this->m_ani.m_texarray.m_ptex[4]))->UIFrameContainer::~UIFrameContainer();
  (((UIListBox *)this))->UIListBox::~UIListBox() /* [ROWTABLE] */;
}

// 0x00529CF0
void UIRoleSelectDialog::Render()
{
  float *p_m_ratioh; // edi
  float *p_m_needscriptdel; // ebx
  int v4; // ebp
  int v5; // ecx
  int v6; // ebp
  int v7; // ecx
  CCBMagicWindow *v8; // [esp+0x0] [ebp-0x20]
  char *v9; // [esp+0x4] [ebp-0x1C]
  int v10; // [esp+0x8] [ebp-0x18]
  int a2; // [esp+0x10] [ebp-0x10] BYREF
  int v12; // [esp+0x14] [ebp-0xC]
  int v13; // [esp+0x18] [ebp-0x8]
  int v14; // [esp+0x1C] [ebp-0x4]

  (((UISceneMap *)this))->UISceneMap::Render_529c80() /* [ROWTABLE] */;
  v10 = 0;
  if ( *(int *)&this->m_list.m_column[5].head[44] > 0 )
  {
    p_m_ratioh = (float *)&this->m_face.m_ratioh;
    p_m_needscriptdel = (float *)&this->m_list.m_column[4].items.m_needscriptdel;
    v9 = (char *)&this->m_list.m_column[4].head[48];
    do
    {
      if ( *(_DWORD *)v9 )
      {
        if ( *(_DWORD *)v9 == 1 )
        {
          v4 = *(_DWORD *)&this->m_list.m_column[0].head[40];
          v12 = (__int64)(p_m_needscriptdel[1] - (double)(v4 / 2));
          v5 = *(_DWORD *)&this->m_list.m_column[0].head[36];
          a2 = (__int64)(*p_m_needscriptdel - (double)(v5 / 2));
          v13 = a2 + v5;
          v14 = v12 + v4;
          (((UIWnd *)p_m_ratioh))->UIWnd::sub_445FA0(&a2);
        }
      }
      else
      {
        v6 = *(_DWORD *)&this->m_list.m_column[0].head[40];
        v12 = (__int64)(p_m_needscriptdel[1] - (double)(v6 / 2));
        v7 = (__int64)(*p_m_needscriptdel - (double)(*(_DWORD *)&this->m_list.m_column[0].head[36] / 2))
           + *(_DWORD *)&this->m_list.m_column[0].head[36];
        a2 = (__int64)(*p_m_needscriptdel - (double)(*(_DWORD *)&this->m_list.m_column[0].head[36] / 2));
        v13 = v7;
        v14 = v12 + v6;
        (((UIWnd *)p_m_ratioh))->UIWnd::sub_445FA0(&a2);
      }
      (*(void ( **)(float *))(*(_DWORD *)p_m_ratioh + 4))(p_m_ratioh);
      v9 += 4;
      p_m_needscriptdel += 2;
      p_m_ratioh += 46;
      ++v10;
    }
    while ( v10 < *(_DWORD *)&this->m_list.m_column[5].head[44] );
  }
  (((CCBControlWindow *)this))->CCBControlWindow::Render(v8) /* [ROWTABLE] */;
}

// 0x00529E40
double UIRoleSelectDialog::HandleInput(
        
        double st6_0,
        double result,
        int arg0,
        int arg0a)
{
  float v5; // st7
  DWORD TickCount; // eax
  DWORD v8; // eax
  unsigned int v9; // ecx
  BOOL ( *v10)(const RECT *, POINT); // ebp
  int v11; // edi
  DWORD v12; // eax
  DWORD v13; // eax
  int v14; // ebx
  int v15; // kr00_4
  int v16; // ebx
  CScreenMode *Instance; // eax
  int v18; // ebp
  int v19; // ebx
  int v20; // ebx
  int v21; // eax
  int v22; // ecx
  int v23; // ebp
  int v24; // eax
  bool v25; // dl
  bool v26; // al
  int v27; // ecx
  int v28; // edx
  CCBStage *v29; // eax
  float *v30; // ebx
  int v31; // eax
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  CCBStage *v35; // eax
  int v36; // ecx
  int v37; // eax
  char *m_pData; // eax
  float v39; // st7
  float v40; // st7
  float v41; // st7
  int v42; // ecx
  float v43; // st7
  float v44; // st7
  int v45; // ecx
  float v46; // st7
  int v47; // ecx
  float v48; // st7
  float v49; // st7
  int v50; // ecx
  UIQuadManager *v51; // eax
  int v52; // eax
  gbTexture *v53; // eax
  CCBStage *v54; // eax
  const void *v55; // [esp+0x4] [ebp-0x74]
  char *v56; // [esp+0x8] [ebp-0x70]
  char *v57; // [esp+0x8] [ebp-0x70]
  char *v58; // [esp+0x8] [ebp-0x70]
  int v59; // [esp+0xC] [ebp-0x6C]
  char v60; // [esp+0x1C] [ebp-0x5C]
  char v61; // [esp+0x1D] [ebp-0x5B]
  bool v62; // [esp+0x1E] [ebp-0x5A]
  char v63; // [esp+0x1F] [ebp-0x59]
  int v64; // [esp+0x28] [ebp-0x50]
  int v65; // [esp+0x2C] [ebp-0x4C]
  POINT Point; // [esp+0x30] [ebp-0x48] BYREF
  POINT pt; // [esp+0x38] [ebp-0x40] BYREF
  float v68; // [esp+0x40] [ebp-0x38]
  float v69; // [esp+0x44] [ebp-0x34]
  float v70; // [esp+0x4C] [ebp-0x2C]
  float v71; // [esp+0x50] [ebp-0x28]
  int a2; // [esp+0x58] [ebp-0x20] BYREF
  int v73; // [esp+0x5C] [ebp-0x1C]
  int v74; // [esp+0x60] [ebp-0x18]
  int v75; // [esp+0x64] [ebp-0x14]
  int v76; // [esp+0x68] [ebp-0x10]
  int v77; // [esp+0x6C] [ebp-0xC]
  int v78; // [esp+0x74] [ebp-0x4]

  if ( !this->m_list.m_column[0].head[32] )
  {
    TickCount = GetTickCount();
    *(_DWORD *)&this->m_list.m_column[0].head[24] = TickCount;
    *(_DWORD *)&this->m_list.m_column[0].head[28] = TickCount;
    this->m_list.m_column[0].head[32] = 1;
  }
  v8 = GetTickCount();
  v9 = v8 - *(_DWORD *)&this->m_list.m_column[0].head[28];
  *(_DWORD *)&this->m_list.m_column[0].head[24] = v8;
  if ( v9 > 0x898 )
  {
    *(_DWORD *)&this->m_list.m_column[0].head[28] = v8;
    this->m_list.m_column[0].head[32] = 0;
    (((CCBResultWindow *)&this->m_list.m_scrollbar.m_texarray))->CCBResultWindow::SetDirty();
    ((void ( *)(UITextureArray *, _DWORD))((gbRefObject *)this->m_list.m_scrollbar.m_texarray.m_ptex[0]))(
      &this->m_list.m_scrollbar.m_texarray,
      0);
    this->m_list.m_column[0].head[16] = 1;
  }
  v64 = *(_DWORD *)&this->m_list.m_column[4].head[40] - *(_DWORD *)&this->m_list.m_column[4].head[32];
  v10 = PtInRect;
  v65 = *(_DWORD *)&this->m_list.m_column[4].head[44] - *(_DWORD *)&this->m_list.m_column[4].head[36];
  v11 = 0;
  if ( *(int *)&this->m_list.m_column[5].head[44] > 0 )
  {
    while ( 1 )
    {
      (*(void ( **)(_DWORD, _DWORD))(*((_DWORD *)&this->m_face.m_ratioh + 46 * v11) + 8))(
        LODWORD(st6_0),
        HIDWORD(st6_0));
      if ( *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] == 3 )
        goto LABEL_125;
      (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
      v60 = 0;
      if ( PtInRect((const RECT *)&this->m_list.m_column[4].head[32], pt) )
      {
        if ( !this->m_list.m_column[0].head[52] )
        {
          v12 = GetTickCount();
          *(_DWORD *)&this->m_list.m_column[0].head[44] = v12;
          *(_DWORD *)&this->m_list.m_column[0].head[48] = v12;
          this->m_list.m_column[0].head[52] = 1;
        }
        v13 = GetTickCount();
        v14 = *(_DWORD *)&this->m_list.m_column[0].head[48];
        *(_DWORD *)&this->m_list.m_column[0].head[44] = v13;
        if ( v13 - v14 > 0x64 )
        {
          *(_DWORD *)&this->m_list.m_column[0].head[48] = v13;
          this->m_list.m_column[0].head[52] = 0;
          (**(void ( ***)(char *, int))&this->m_list.m_column[0].head[56])((char *)(&this->m_list.m_column[0].head[56]), (int)(1));
          (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[2].head[40])((char *)(&this->m_list.m_column[2].head[40]), (_DWORD)(0));
        }
        v60 = 1;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[0].head[56])((char *)(&this->m_list.m_column[0].head[56]), (_DWORD)(0));
        (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[2].head[40])((char *)(&this->m_list.m_column[2].head[40]), (_DWORD)(0));
      }
      v15 = *(_DWORD *)&this->m_list.m_column[4].head[24];
      a2 = pt.x - v15 / 2;
      v16 = *(_DWORD *)&this->m_list.m_column[4].head[28];
      v74 = pt.x + v15 - v15 / 2;
      v75 = v16 + pt.y - v16 / 2;
      v73 = pt.y - v16 / 2;
      (((UIWnd *)&this->m_list.m_column[0].head[56]))->UIWnd::sub_445FA0(&a2);
      (((UIWnd *)&this->m_list.m_column[2].head[40]))->UIWnd::sub_445FA0(&a2);
      if ( g_Input.KeyInfo[0].PressTime == 1 && !LOBYTE(this->m_ani.m_texarray.m_ptex[2]) )
      {
        if ( v60 )
        {
          (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[0].head[56])((char *)(&this->m_list.m_column[0].head[56]), (_DWORD)(0));
          (**(void ( ***)(char *, int))&this->m_list.m_column[2].head[40])((char *)(&this->m_list.m_column[2].head[40]), (int)(1));
          v55 = (const void *)off_5ED1D4;
          Instance = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v55, 1);
        }
        *((_BYTE *)&this->m_mode + 92) = 0;
      }
      v18 = *(_DWORD *)&this->m_list.m_column[0].head[40];
      v19 = *(_DWORD *)&this->m_list.m_column[0].head[36];
      v77 = (__int64)(*((float *)&this->m_list.m_column[4].width + 2 * v11) - (double)(v18 / 2));
      v5 = *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) - (float)(v19 / 2);
      v76 = (__int64)v5;
      v20 = v76 + v19;
      v21 = *(_DWORD *)&this->m_list.m_column[4].head[28];
      v78 = v18 + v77;
      v22 = pt.y - v21 / 2;
      v23 = v22 + 45;
      v24 = pt.x - *(_DWORD *)&this->m_list.m_column[4].head[24] / 2;
      v73 = v22;
      a2 = v24;
      v75 = v22 + 45;
      v74 = v24 + 45;
      if ( *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] == 1 )
        goto LABEL_72;
      if ( v24 < v76 )
      {
        if ( v74 <= v76 )
        {
          v23 = v75;
        }
        else
        {
          if ( v22 > v77 && v22 < v78 )
          {
            v23 = v75;
            v61 = 1;
            goto LABEL_30;
          }
          v23 = v75;
          if ( v75 > v77 && v75 < v78 )
          {
            v61 = 1;
            goto LABEL_30;
          }
        }
      }
      v61 = 0;
LABEL_30:
      v62 = v24 < v20 && v74 > v20 && (v22 > v77 && v22 < v78 || v23 > v77 && v23 < v78);
      if ( v22 < v77 && v23 > v77 )
      {
        if ( v24 > v76 && v24 < v20 )
          goto LABEL_45;
        if ( v74 > v76 && v74 < v20 )
        {
          v23 = v75;
LABEL_45:
          v63 = 1;
          goto LABEL_48;
        }
        v23 = v75;
      }
      v63 = 0;
LABEL_48:
      v25 = v22 < v78 && v23 > v78 && (v24 > v76 && v24 < v20 || v74 > v76 && v74 < v20);
      v26 = v22 > v77 && v24 > v76 && v74 < v20 && v75 < v78;
      if ( (v61 || v62 || v63 || v25 || v26) && v60 && g_Input.KeyInfo[0].PressTime == 1 )
      {
        v27 = *(_DWORD *)&this->m_list.m_column[5].head[44];
        v28 = this->m_list.m_column[4].items.m_nSize + 1;
        this->m_list.m_column[4].items.m_nSize = v28;
        if ( v28 >= v27 )
        {
          v56 = (char *)off_5ED1D0;
          v29 = (CCBStage *)CScreenMode::GetInstance();
          (((CCBStage *)v29))->CCBStage::PlaySound(v56, v59);
        }
        LOBYTE(v28) = *((_BYTE *)&this->m_mode + 108);
        v30 = (float *)(&this->m_face.m_ratioh + 46 * v11);
        (((UIPushButton *)v30))->UIPushButton::CreateFromTemplate("SubGame\\KillFlyer\\FlyerDie.tga", v28);
        *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] = 1;
        *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 40] = 1050253722;
        goto LABEL_73;
      }
LABEL_72:
      v30 = (float *)(&this->m_face.m_ratioh + 46 * v11);
LABEL_73:
      v31 = *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48];
      if ( v31 )
      {
        v32 = v31 - 1;
        if ( v32 )
        {
          if ( v32 == 1 && !this->m_list.m_column[7].head[20] )
          {
            (**(void ( ***)(float *, _DWORD))v30)((float *)(v30), (_DWORD)(0));
            v33 = *(_DWORD *)&this->m_list.m_column[5].head[44];
            v34 = *(_DWORD *)&this->m_list.m_column[4].head[60] + 1;
            *(_DWORD *)&this->m_list.m_column[4].head[60] = v34;
            if ( v34 >= v33 )
            {
              this->m_list.m_column[7].head[20] = 1;
              v57 = (char *)off_5ED1D0;
              v35 = (CCBStage *)CScreenMode::GetInstance();
              (((CCBStage *)v35))->CCBStage::PlaySound(v57, v59);
            }
            *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] = 3;
          }
        }
        else
        {
          *((float *)&this->m_list.m_column[4].width + 2 * v11) = *((float *)&this->m_list.m_column[4].width + 2 * v11)
                                                                + *(float *)&this->m_list.m_column[6].head[4 * v11 + 40];
          *(float *)&this->m_list.m_column[6].head[4 * v11 + 40] = *(float *)&this->m_list.m_column[6].head[4 * v11 + 40]
                                                                 + 0.0099999998;
          v5 = (float)(*(_DWORD *)&this->m_list.m_column[4].head[44] - 2
                                                                      * *(_DWORD *)&this->m_list.m_column[5].head[60]);
          if ( v5 <= *((float *)&this->m_list.m_column[4].width + 2 * v11) )
          {
            (**(void ( ***)(float *, _DWORD))v30)((float *)(v30), (_DWORD)(0));
            *(&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) = 1137180672;
            *(_DWORD *)&this->m_list.m_column[5].head[8 * v11 + 20] = 1137180672;
            *(&this->m_list.m_column[4].width + 2 * v11) = 1133903872;
            *(_DWORD *)&this->m_list.m_column[5].head[8 * v11 + 24] = 1133903872;
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = 0;
            if ( !this->m_list.m_column[7].head[20] )
            {
              v36 = *(_DWORD *)&this->m_list.m_column[5].head[44];
              v37 = *(_DWORD *)&this->m_list.m_column[4].head[60] + 1;
              *(_DWORD *)&this->m_list.m_column[4].head[60] = v37;
              if ( v37 >= v36 )
                this->m_list.m_column[7].head[20] = 1;
              *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] = 3;
              m_pData = (char *)this->m_list.m_column[4].items.m_pData;
              ++this->m_list.m_column[4].items.capacity;
              this->m_list.m_column[4].items.m_pData = &m_pData[*(&this->m_list.m_column[6].items.m_needscriptdel + v11)];
            }
          }
        }
        goto LABEL_125;
      }
      if ( this->m_list.m_column[5].head[v11 + 16] )
      {
        *(float *)&this->m_list.m_column[5].head[8 * v11 + 20] = (float)(*(_DWORD *)&this->m_list.m_column[4].head[32]
                                                                       + rand() % v64);
        *(float *)&this->m_list.m_column[5].head[8 * v11 + 24] = (float)(*(_DWORD *)&this->m_list.m_column[4].head[36]
                                                                       + rand() % v65);
        *((float *)&this->m_list.m_column[5].items.m_pData + 2 * v11) = *(float *)&this->m_list.m_column[5].head[8 * v11 + 20]
                                                                      - *((float *)&this->m_list.m_column[4].items.m_needscriptdel
                                                                        + 2 * v11);
        v39 = *(float *)&this->m_list.m_column[5].head[8 * v11 + 24]
            - *((float *)&this->m_list.m_column[4].width + 2 * v11);
        *((float *)&this->m_list.m_column[5].items.capacity + 2 * v11) = v39;
        v70 = *((float *)&this->m_list.m_column[5].items.m_pData + 2 * v11);
        v71 = v39;
        v68 = *(float *)&this->m_list.m_column[6].head[8 * v11 + 4];
        v40 = *(float *)&this->m_list.m_column[6].head[8 * v11 + 8];
        v69 = *(float *)&this->m_list.m_column[6].head[8 * v11 + 8];
        v5 = acos((v40 * v71 + v68 * v70) / (sqrt(v69 * v69 + v68 * v68) + sqrt(v71 * v71 + v70 * v70))) * 57.295780181884766f;
        if ( *((float *)&this->m_list.m_column[5].items.m_pData + 2 * v11) < 0.0 )
          v5 = 180.0f - v5 + 180.0f;
        v30[40] = v5;
        *((_BYTE *)v30 + 172) = 0;
        this->m_list.m_column[5].head[v11 + 16] = 0;
        goto LABEL_125;
      }
      if ( *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) >= (double)*(float *)&this->m_list.m_column[5].head[8 * v11 + 20] )
      {
        if ( *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) > (double)*(float *)&this->m_list.m_column[5].head[8 * v11 + 20] )
        {
          v43 = *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11);
          if ( *((_DWORD *)&this->m_list.m_column[6].items.m_pData + v11) )
            v44 = v43 - *(float *)&this->m_list.m_column[6].head[4 * v11 + 52];
          else
            v44 = v43 - *(float *)&this->m_list.m_column[6].head[4 * v11 + 40];
          *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) = v44;
          v5 = (float)(*(_DWORD *)&this->m_list.m_column[4].head[32] + *(_DWORD *)&this->m_list.m_column[5].head[60]);
          if ( v5 >= *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) )
          {
            v45 = *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] + 1;
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = v45;
            if ( v45 >= 2 )
            {
              *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] = 2;
              *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = 0;
            }
            goto LABEL_124;
          }
          v5 = *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11);
          if ( v5 <= *(float *)&this->m_list.m_column[5].head[8 * v11 + 20] )
          {
            *(&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) = *(_DWORD *)&this->m_list.m_column[5].head[8 * v11 + 20];
            goto LABEL_124;
          }
        }
      }
      else
      {
        if ( *((_DWORD *)&this->m_list.m_column[6].items.m_pData + v11) )
          v41 = *(float *)&this->m_list.m_column[6].head[4 * v11 + 52];
        else
          v41 = *(float *)&this->m_list.m_column[6].head[4 * v11 + 40];
        *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) = v41
                                                                              + *((float *)&this->m_list.m_column[4].items.m_needscriptdel
                                                                                + 2 * v11);
        v5 = (float)(*(_DWORD *)&this->m_list.m_column[4].head[40] - *(_DWORD *)&this->m_list.m_column[5].head[60]);
        if ( v5 < *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) )
        {
          v42 = *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] + 1;
          *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = v42;
          if ( v42 >= 2 )
          {
            *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] = 2;
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = 0;
          }
          goto LABEL_124;
        }
        v5 = *((float *)&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11);
        if ( v5 >= *(float *)&this->m_list.m_column[5].head[8 * v11 + 20] )
        {
          *(&this->m_list.m_column[4].items.m_needscriptdel + 2 * v11) = *(_DWORD *)&this->m_list.m_column[5].head[8 * v11 + 20];
LABEL_124:
          this->m_list.m_column[5].head[v11 + 16] = 1;
          goto LABEL_125;
        }
      }
      if ( *((float *)&this->m_list.m_column[4].width + 2 * v11) >= (double)*(float *)&this->m_list.m_column[5].head[8 * v11 + 24] )
      {
        v5 = *((float *)&this->m_list.m_column[4].width + 2 * v11);
        if ( v5 > *(float *)&this->m_list.m_column[5].head[8 * v11 + 24] )
        {
          v48 = *((float *)&this->m_list.m_column[4].width + 2 * v11);
          if ( *((_DWORD *)&this->m_list.m_column[6].items.m_pData + v11) )
            v49 = v48 - *(float *)&this->m_list.m_column[6].head[4 * v11 + 52];
          else
            v49 = v48 - *(float *)&this->m_list.m_column[6].head[4 * v11 + 40];
          *((float *)&this->m_list.m_column[4].width + 2 * v11) = v49;
          v5 = (float)(*(_DWORD *)&this->m_list.m_column[4].head[36] + *(_DWORD *)&this->m_list.m_column[5].head[60]);
          if ( v5 >= *((float *)&this->m_list.m_column[4].width + 2 * v11) )
          {
            v50 = *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] + 1;
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = v50;
            if ( v50 >= 2 )
            {
              *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] = 2;
              *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = 0;
            }
            goto LABEL_124;
          }
          v5 = *((float *)&this->m_list.m_column[4].width + 2 * v11);
          if ( v5 <= *(float *)&this->m_list.m_column[5].head[8 * v11 + 24] )
            goto LABEL_124;
        }
      }
      else
      {
        if ( *((_DWORD *)&this->m_list.m_column[6].items.m_pData + v11) )
          v46 = *(float *)&this->m_list.m_column[6].head[4 * v11 + 52];
        else
          v46 = *(float *)&this->m_list.m_column[6].head[4 * v11 + 40];
        *((float *)&this->m_list.m_column[4].width + 2 * v11) = v46
                                                              + *((float *)&this->m_list.m_column[4].width + 2 * v11);
        v5 = (float)(*(_DWORD *)&this->m_list.m_column[4].head[44] - *(_DWORD *)&this->m_list.m_column[5].head[60]);
        if ( v5 <= *((float *)&this->m_list.m_column[4].width + 2 * v11) )
        {
          v47 = *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] + 1;
          *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = v47;
          if ( v47 >= 2 )
          {
            *(_DWORD *)&this->m_list.m_column[4].head[4 * v11 + 48] = 2;
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 48] = 0;
          }
          goto LABEL_124;
        }
        v5 = *((float *)&this->m_list.m_column[4].width + 2 * v11);
        if ( v5 >= *(float *)&this->m_list.m_column[5].head[8 * v11 + 24] )
          goto LABEL_124;
      }
LABEL_125:
      if ( ++v11 >= *(_DWORD *)&this->m_list.m_column[5].head[44] )
      {
        v10 = PtInRect;
        break;
      }
    }
  }
  if ( this->m_list.m_column[7].head[20]
    && *(_DWORD *)&this->m_list.m_column[4].head[60] >= *(_DWORD *)&this->m_list.m_column[5].head[44] )
  {
    (**(void ( ***)(_BYTE *, int))&this->m_list.m_rowenable[8])((_BYTE *)(&this->m_list.m_rowenable[8]), (int)(1));
    (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[0].head[56])((char *)(&this->m_list.m_column[0].head[56]), (_DWORD)(0));
    (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[2].head[40])((char *)(&this->m_list.m_column[2].head[40]), (_DWORD)(0));
  }
  if ( *(&this->m_mode + 18) == 2 )
  {
    sprintf(
      (char *const)&this->m_bk.m_rect.top,
      "\\n\\n %s %d %s\\n %s %d \n",
      (const char *)&dword_DD353C,
      this->m_list.m_column[4].items.capacity,
      (const char *)&dword_DDC23C,
      (const char *)&dword_DD363C,
      this->m_list.m_column[4].items.m_pData);
    SetEnable((UICaption *)&this->m_list.m_column[7].head[24]);
    (**(void ( ***)(char *, int))&this->m_list.m_column[7].head[24])((char *)(&this->m_list.m_column[7].head[24]), (int)(1));
    v51 = (UIQuadManager *)UIQuadManager::GetInstance();
    (((UIRenderObj *)v51))->UIRenderObj::_sdtor_call_dtor(1);
    LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 1;
  }
  v52 = *(_DWORD *)&this->m_list.m_column[5].head[44];
  if ( *(_DWORD *)&this->m_list.m_column[4].head[60] >= v52 && v52 > 0 )
    *(_DWORD *)&this->m_list.m_column[4].head[60] = 0;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&Point);
  v53 = (gbTexture *)this->m_ani.m_texarray.m_ptex[3];
  if ( v53 == (gbTexture *)1 )
  {
    if ( v10((const RECT *)&this->m_list.m_column[4].head[32], Point) )
      this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)2;
  }
  else if ( v53 == (gbTexture *)2 && !v10((const RECT *)&this->m_list.m_column[4].head[32], Point) )
  {
    this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)1;
  }
  if ( LOBYTE(this->m_ani.m_texarray.m_ptex[2]) )
  {
    if ( !v10((const RECT *)&this->m_list.m_column[4].head[32], Point) && g_Input.KeyInfo[1].PressTime == 1
      || v10((const RECT *)&this->m_list.m_column[4].head[32], Point) && g_Input.KeyInfo[0].PressTime == 1 )
    {
      this->UIRoleSelectDialog::SubtractFromStats();
      return v5;
    }
    if ( *(int *)&this->m_list.m_column[5].head[44] <= 0 )
      this->UIRoleSelectDialog::SubtractFromStats();
    goto LABEL_149;
  }
  if ( v10((const RECT *)&this->m_list.m_column[4].head[32], Point)
    || g_Input.KeyInfo[1].PressTime != 1
    || !*((_BYTE *)&this->m_mode + 92) )
  {
LABEL_149:
    (((SceneObj *)this))->SceneObj::Update(SLODWORD(st6_0), SHIDWORD(st6_0)) /* [ROWTABLE] */;
    return v5;
  }
  this->UIRoleSelectDialog::SubtractFromStats();
  v58 = (char *)off_5ED1D0;
  v54 = (CCBStage *)CScreenMode::GetInstance();
  (((CCBStage *)v54))->CCBStage::PlaySound(v58, v59);
  return v5;
}

// 0x0052AA50
int UIRoleSelectDialog::SubtractFromStats()
{
  *(&g_RoleSlotBuf.dword_17AA450 + 147) += (int)this->m_list.m_column[4].items.m_pData;
  g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] -= *(_DWORD *)&this->m_list.m_column[0].head[20];
  if ( (int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] <= 0 )
    g_RoleSlotBuf.m_partyActor.m_dwMatMsg[2] = 1;
  if ( this->m_ani.m_texarray.m_ptex[3] == (gbTexture *)2 )
    this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)1;
  return (((CGameData *)&g_gamefrm))->CGameData::Load(0);
}

// 0x0052AAB0
int UIRoleSelectDialog::ProcessDialog(int nVal1)
{
  char *v4; // edi
  float v5; // esi
  double v6; // st7
  DWORD Time; // eax
  int v8; // eax
  int v9; // edx
  int *p_m_nTodo_64; // esi
  int *p_width; // edi
  int v12; // edx
  float *p_m_ratioh; // esi
  int *p_m_needscriptdel; // edi
  int v15; // edx
  CScreenMode *Instance; // eax
  const void *v17; // [esp-0x10] [ebp-0x14]
  int *nMsg; // [esp+0x10] [ebp+0xC]
  int nMsga; // [esp+0x10] [ebp+0xC]
  int nMsgb; // [esp+0x10] [ebp+0xC]
  float nMsge; // [esp+0x10] [ebp+0xC]
  int nMsgc; // [esp+0x10] [ebp+0xC]
  int nMsgd; // [esp+0x10] [ebp+0xC]
  int wParam; // [esp+0x14] [ebp+0x10]

  if ( nVal1 != 1000 )
  {
    if ( nVal1 != 1009 )
      return this->UIWnd::OnMessage(nVal1, (int)nMsg, wParam);
    if ( nMsg == &byte_80AB20 )
    {
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_list.m_rowenable[8])((_BYTE *)(&this->m_list.m_rowenable[8]), (_DWORD)(0));
      (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[7].head[24])((char *)(&this->m_list.m_column[7].head[24]), (_DWORD)(0));
      LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 1;
      return 1;
    }
    return 1;
  }
  if ( !nMsg )
  {
    g_nSceneState = 2;
    if ( this->m_ani.m_texarray.m_ptex[3] == (gbTexture *)2 )
      this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)1;
    return 1;
  }
  nMsga = 0;
  v4 = (char *)&this->m_list.m_column[6].head[28];
  v5 = &this->m_list.m_column[5].head[24];
  do
  {
    *((_DWORD *)v4 - 37) = 0;
    *((_DWORD *)v5 - 8) = 1137180672;
    *((_DWORD *)v5 - 1) = 1137180672;
    *((_DWORD *)v5 - 7) = 1133903872;
    *(_DWORD *)v5 = 1133903872;
    this->m_list.m_column[5].head[nMsga + 16] = 1;
    *(_DWORD *)v4 = 0;
    *((_DWORD *)v5 + 16) = 0;
    *((_DWORD *)v5 + 17) = 1065353216;
    *((_DWORD *)v5 + 10) = *((_DWORD *)v5 - 8);
    *((_DWORD *)v5 + 11) = *((_DWORD *)v5 - 7);
    *((_DWORD *)v4 - 16) = 0;
    v4 += 4;
    v5 += 8;
    v6 = (double)(rand() % 12 - 6) * 0.1 + 0.80000001;
    *((float *)v4 + 2) = v6;
    *((float *)v4 + 5) = v6 * 1.6;
    *((_DWORD *)v4 + 8) = 0;
    *((_DWORD *)v4 + 11) = 0;
    ++nMsga;
  }
  while ( nMsga < 3 );
  this->m_list.m_column[7].head[20] = 0;
  LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 0;
  this->m_ani.m_texarray.m_ptex[3] = 0;
  this->m_list.m_column[4].items.capacity = 0;
  this->m_list.m_column[4].items.m_pData = ((char *)0);
  *(_DWORD *)&this->m_list.m_column[4].head[60] = 0;
  this->m_list.m_column[4].items.m_nSize = 0;
  Time = timeGetTime();
  CRT_set_new_handler(Time);
  nMsgb = (__int64)(*(float *)&this->m_list.m_column[7].head[4] * 100.0);
  if ( nMsgb <= 0
    || (nMsge = (double)nMsgb * 10.24,
        ++*(_DWORD *)&g_TempBuffer1024[912],
        g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011,
        (((int)g_nCombatRandSeed >> 16) & 0x3FF) >= (int)nMsge) )
  {
    LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 1;
  }
  else
  {
    nMsgc = 0;
    *(_DWORD *)&this->m_list.m_column[5].head[44] = 1;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    g_nCombatRandSeed = 214013 * g_nCombatRandSeed + 2531011;
    if ( (((int)g_nCombatRandSeed >> 16) & 0x3FF) < (int)102.39999 )
      *(_DWORD *)&this->m_list.m_column[5].head[44] = 3;
    v8 = *(_DWORD *)&this->m_list.m_column[5].head[44];
    if ( v8 == 3 )
    {
      this->m_list.m_column[6].items.m_pData = (char *)1;
      v9 = rand() % 100 + 100;
      this->m_list.m_column[6].items.m_needscriptdel = v9;
      LOBYTE(v9) = *((_BYTE *)&this->m_mode + 108);
      (((UIPushButton *)&this->m_face.m_ratioh))->UIPushButton::CreateFromTemplate("SubGame\\KillFlyer\\Flyer_gold.tga", v9);
      (*(void ( **)(float *, int))LODWORD(this->m_face.m_ratioh))(&this->m_face.m_ratioh, 1);
      nMsgd = 1;
      if ( *(int *)&this->m_list.m_column[5].head[44] > 1 )
      {
        p_m_nTodo_64 = (int *)&this->m_static.m_nTodo_64;
        p_width = (int *)&this->m_list.m_column[6].width;
        do
        {
          *(p_width - 3) = 0;
          v12 = rand() % 20 + 1;
          *p_width = v12;
          LOBYTE(v12) = *((_BYTE *)&this->m_mode + 108);
          (((UIPushButton *)p_m_nTodo_64))->UIPushButton::CreateFromTemplate("SubGame\\KillFlyer\\Flyer_nor.tga", v12);
          (*(void ( **)(int *, int))*p_m_nTodo_64)(p_m_nTodo_64, 1);
          ++p_width;
          p_m_nTodo_64 += 46;
          ++nMsgd;
        }
        while ( nMsgd < *(_DWORD *)&this->m_list.m_column[5].head[44] );
      }
    }
    else if ( v8 > 0 )
    {
      p_m_ratioh = (float *)&this->m_face.m_ratioh;
      p_m_needscriptdel = (int *)&this->m_list.m_column[6].items.m_needscriptdel;
      do
      {
        *(p_m_needscriptdel - 3) = 0;
        v15 = rand() % 20 + 1;
        *p_m_needscriptdel = v15;
        LOBYTE(v15) = *((_BYTE *)&this->m_mode + 108);
        (((UIPushButton *)p_m_ratioh))->UIPushButton::CreateFromTemplate("SubGame\\KillFlyer\\Flyer_nor.tga", v15);
        (**(void ( ***)(float *, int))p_m_ratioh)((float *)(p_m_ratioh), (int)(1));
        ++p_m_needscriptdel;
        p_m_ratioh += 46;
        ++nMsgc;
      }
      while ( nMsgc < *(_DWORD *)&this->m_list.m_column[5].head[44] );
    }
    LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 0;
    v17 = (const void *)off_5ED1D0;
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v17, 0);
  }
  g_nSceneState = 1;
  this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)2;
  return 1;
}

// 0x0052BBD0
void UIRoleSelectDialog::DestroyStatics()
{
  (((UIFrameContainer *)this))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_bk.m_currect.right))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_ani.m_childs))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_face.m_rect.right))->UIFrameContainer::ResetContainerState();
  ctor_17((UIButton *)&this->m_static.m_id);
  (((UIFrameContainer *)&this->m_list.m_benable))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_list.m_scrollbar.m_bk.m_benable))->UIFrameContainer::ResetContainerState();
  ctor_17((UIButton *)&this->m_list.m_scrollbar.m_texarrayInfo[6]);
  (((UIFrameContainer *)&this->m_list.m_column[2].head[4]))->UIFrameContainer::ResetContainerState();
}

// 0x0052BC90
void UIRoleSelectDialog::DestroyFrames()
{
  (((UIFrameContainer *)&this->m_list.m_column[2].head[4]))->UIFrameContainer::~UIFrameContainer();
  (((UIButton *)&this->m_list.m_scrollbar.m_texarrayInfo[6]))->UIButton::~UIButton();
  (((UIFrameContainer *)&this->m_list.m_scrollbar.m_bk.m_benable))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_list.m_benable))->UIFrameContainer::~UIFrameContainer();
  (((UIButton *)&this->m_static.m_id))->UIButton::~UIButton();
  (((UIFrameContainer *)&this->m_face.m_rect.right))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_ani.m_childs))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)&this->m_bk.m_currect.right))->UIFrameContainer::~UIFrameContainer();
  (((UIFrameContainer *)this))->UIFrameContainer::~UIFrameContainer();
}

// 0x0052D200
char UIRoleSelectDialog::IsRoleSelectable(int nVal)
{
  int v3; // eax
  int *i; // ecx

  if ( *((_BYTE *)&g_RoleSlotBuf.m_teamData3[586] + nVal) )
  {
    v3 = 0;
    for ( i = &this->m_mode + 3; *i == nVal; ++i )
    {
      if ( ++v3 >= 4 )
        return 1;
    }
  }
  return 0;
}
