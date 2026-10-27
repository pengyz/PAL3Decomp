#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/LineupUI.h"
#include "Misc/ARC_PlayerAtt.h"
#include "Misc/ArcLocaleRole.h"
#include "Combat/CCBControlWindow.h"
#include "Misc/CCBFiveNimbusWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Render/CScreenMode.h"
#include "Scene/Camera.h"
#include "Misc/ChoseCompose.h"
#include "Misc/LineupComp.h"
#include "Misc/MainEquipUI.h"
#include "Misc/NameSys.h"
#include "Role/Object3D.h"
#include "Role/ObjectCamera.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Render/RenderTarget.h"
#include "Role/RoleSystem.h"
#include "Scene/SceneObj.h"
#include "UI/StateUI.h"
#include "Misc/TaskBookUI.h"
#include "Misc/UIButtonEX.h"
#include "Misc/UICaption.h"
#include "UI/UICursor.h"
#include "Misc/UIFrameContainer.h"
#include "UI/UIItem.h"
#include "UI/UIListBox.h"
#include "Misc/UIParticle.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIRoleDialog.h"
#include "UI/UIScene.h"
#include "Misc/UIScrollBar.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/scAsmDecoder.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// Unnamed globals (extern)
extern LPCSTR off_5C641C;
extern LPCSTR off_5C6420;

// 0x00474C50
int LineupUI::UpdateAndForward(int nVal, int nVal2)
{
  this->LineupUI::GetUpdateFlag();
  LineupUI_ProcessMouseInput(nVal);
  (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return 1;
}

// 0x004765D0
int LineupUI::UpdateAllSlots()
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 6; ++i )
    result = LineupUI_PopulateList(i);
  return result;
}

// 0x00477BB0
int LineupUI::OnMessage(int msg, int wparam, int lparam)
{
  int v5; // eax
  char *v6; // ebx
  char *v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  _BYTE *p_m_mouseoff; // ecx
  UICursor *v12; // ecx
  int result; // eax
  int v14; // edi
  int *v15; // eax
  int par_radiusY; // eax
  int v17; // eax
  CScreenMode *Instance; // eax
  int *v19; // eax
  int v20; // eax
  const char *v21; // ebp
  int v22; // eax
  const char *v23; // ebp
  int *p_m_nTextW; // edi
  int v25; // ebp
  int v26; // ebx
  const char **v27; // eax
  const char *v28; // ebp
  const char **v29; // eax
  const char **v30; // eax
  const char **v31; // eax
  const char **v32; // eax
  const char **v33; // eax
  int v34; // edi
  int *v35; // ebx
  int v36; // edi
  char *v37; // ebx
  int v38; // edi
  unsigned int *p_m_sec; // ebx
  int v40; // edi
  char *v41; // ebx
  int v42; // edi
  char *v43; // ebx
  _PlugInfo *m_disablepicInfo; // edx
  char *v45; // edi
  unsigned int v46; // eax
  unsigned int v47; // ecx
  _PlugInfo *m_ppicInfo; // ebx
  char *v49; // eax
  _PlugInfo *v50; // ecx
  LONG left; // edx
  _PlugInfo *v52; // edx
  gbTexture *m_disablepic; // ebp
  unsigned int v54; // edx
  char *v55; // eax
  signed int v56; // ecx
  const void *v57; // [esp-0x8] [ebp-0x160]
  int v58; // [esp-0x8] [ebp-0x160]
  int v59; // [esp-0x8] [ebp-0x160]
  int v60; // [esp+0x0] [ebp-0x158]
  int v61; // [esp+0x10] [ebp-0x148]
  const char *v62; // [esp+0x10] [ebp-0x148]
  const char *v63; // [esp+0x14] [ebp-0x144]
  int a2; // [esp+0x18] [ebp-0x140] BYREF
  int v65; // [esp+0x1C] [ebp-0x13C]
  int v66; // [esp+0x20] [ebp-0x138]
  int v67; // [esp+0x24] [ebp-0x134]
  int v68; // [esp+0x28] [ebp-0x130] BYREF
  int v69; // [esp+0x30] [ebp-0x128] BYREF
  int v70; // [esp+0x38] [ebp-0x120] BYREF
  int pOut; // [esp+0x40] [ebp-0x118] BYREF
  int v72; // [esp+0x48] [ebp-0x110] BYREF
  int v73; // [esp+0x50] [ebp-0x108] BYREF
  char Buffer[253]; // [esp+0x58] [ebp-0x100] BYREF
  __int16 v75; // [esp+0x155] [ebp-0x3]
  char v76; // [esp+0x157] [ebp-0x1]

  switch ( msg )
  {
    case 1000:
      if ( !wparam )
        goto LABEL_36;
      LineupUI_RefreshListData(v60);
      LineupUI_Render3DModels(0);
      v5 = 0;
      v6 = (char *)&this->m_btnPar2[7][1]._texName[160];
      v61 = 0;
      v7 = (char *)&this->m_btnPar2[8][3]._texName[4];
      do
      {
        if ( this->m_btnPar2[7][1]._texName[v5 + 252] )
        {
          v8 = *((_DWORD *)v6 - 1) - 24;
          v65 = *(_DWORD *)v6 + 36;
          a2 = v8;
          v67 = v65 + 30;
          v66 = v8 + 24;
          (((UIWnd *)(v7 - 180)))->UIWnd::sub_445FA0(&a2);
          (**((void ( ***)(int, _DWORD))v7 - 45))((int)((int)(v7 - 180)), (_DWORD)(0));
          (((UIWnd *)v7))->UIWnd::sub_445FA0(&a2);
          (**(void ( ***)(char *, _DWORD))v7)((char *)(v7), (_DWORD)(0));
          (((UIWnd *)(v7 + 180)))->UIWnd::sub_445FA0(&a2);
          v9 = *(_DWORD *)v6 + 36;
          a2 = *((_DWORD *)v6 + 1) + 18;
          v66 = a2 + 22;
          v65 = v9;
          v67 = v9 + 30;
          (((UIWnd *)(v7 + 360)))->UIWnd::sub_445FA0(&a2);
          (**((void ( ***)(int, _DWORD))v7 + 90))((int)((int)(v7 + 360)), (_DWORD)(0));
          (((UIWnd *)(v7 + 540)))->UIWnd::sub_445FA0(&a2);
          (**((void ( ***)(int, _DWORD))v7 + 135))((int)((int)(v7 + 540)), (_DWORD)(0));
          v5 = v61;
        }
        ++v5;
        v6 += 16;
        v7 += 900;
        v61 = v5;
      }
      while ( v5 < 5 );
      this->m_TimeMoney.m_bfocus = 0;
      if ( (((UIListBox *)&this->m_btnPar2[10][0]._x))->UIListBox::GetItemData() > 0 )
        (*(void ( **)(LineupUI *, int, int, int))(*(_DWORD *)((UIWnd *)this) + 24))(
          this,
          1007,
          773,
          this->m_TimeMoney.m_bfocus);
      else
        this->m_TimeMoney.m_bfocus = -1;
      if ( !this->m_btnPar2[12][4].par_radiusY )
      {
        (**(void ( ***)(char *, int))&this->m_btnPar2[7][5]._texName[72])((char *)(&this->m_btnPar2[7][5]._texName[72]), (int)(1));
        SetEnable((UICaption *)&this->m_btnPar2[7][5]._texName[72]);
        v10 = lstrlenA((LPCSTR)&this->stp_BarL.m_childs.m_needscriptdel);
        p_m_mouseoff = (_BYTE *)&this->m_btnPar2[6][6]._element.m_mouseoff;
        if ( v10 > 0 )
          (**(void ( ***)(_BYTE *, int))p_m_mouseoff)((_BYTE *)(p_m_mouseoff), (int)(1));
        else
          (**(void ( ***)(_BYTE *, _DWORD))p_m_mouseoff)((_BYTE *)(p_m_mouseoff), (_DWORD)(0));
      }
      sprintf((char *const)&this->rc.right, "%s %d", (const char *)&g_bSaveFlag, *(&g_RoleSlotBuf.dword_17AA450 + 147));
      SetEnable((UICaption *)&this->m_btnPar2[12][3]._texName[112]);
      BYTE1(this->m_btnPar2[11][6]._element.m_nTextW) = 1;
      LOBYTE(this->m_btnPar2[11][6]._element.m_nTextW) = 1;
      (((UICursor *)v12))->UICursor::_todo_541CC0();
      result = 1;
      break;
    case 1001:
      v14 = 0;
      v15 = (int *)&dword_56B77C;
      while ( wparam != *v15 )
      {
        ++v15;
        ++v14;
        if ( (int)v15 >= (int)&off_56B794 )
        {
          switch ( wparam )
          {
            case 770:
              LineupUI_RefreshDisplayEx(v60);
              par_radiusY = this->m_btnPar2[12][4].par_radiusY;
              if ( par_radiusY )
              {
                if ( par_radiusY == 1 )
                  CUtil_Update(2);
              }
              else
              {
                UIFrameWnd_OnPaintUpdate(0);
              }
              goto LABEL_34;
            case 788:
              LineupUI_RefreshDisplay(v60);
              v57 = (const void *)off_5B9DE4;
              goto LABEL_35;
            case 789:
              this->LineupUI::UpdateAllSlots();
              v17 = this->m_btnPar2[12][4].par_radiusY;
              if ( v17 )
              {
                if ( v17 == 1 )
                {
                  SetEnable((UICaption *)&this->m_btnPar2[7][5]._texName[72]);
                  (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)((_BYTE *)(&this->m_btnPar2[6][6]._element.m_mouseoff), (_DWORD)(0));
                }
              }
              else
              {
                (**(void ( ***)(char *, int))&this->m_btnPar2[7][5]._texName[72])((char *)(&this->m_btnPar2[7][5]._texName[72]), (int)(1));
                SetEnable((UICaption *)&this->m_btnPar2[7][5]._texName[72]);
                (**(void ( ***)(_BYTE *, int))&this->m_btnPar2[6][6]._element.m_mouseoff)((_BYTE *)(&this->m_btnPar2[6][6]._element.m_mouseoff), (int)(1));
              }
              goto LABEL_34;
            case 819:
              v58 = *(_DWORD *)&this->m_btnPar2[11][5]._texName[240];
              LODWORD(this->m_btnPar2[12][1].m_riseY) = 3;
              LineupUI_InitItemList(v58);
              v57 = (const void *)off_5B9DE4;
              goto LABEL_35;
            case 820:
              v59 = *(_DWORD *)&this->m_btnPar2[11][5]._texName[240];
              this->m_btnPar2[12][1].m_riseY = 0.0;
              LineupUI_InitItemList(v59);
LABEL_34:
              v57 = (const void *)off_5B9DE4;
              goto LABEL_35;
            case 821:
              LineupUI_SetItemDisplay(*(_DWORD *)&this->m_btnPar2[11][5]._texName[240]);
              goto LABEL_31;
            case 822:
              LineupUI_SetItemColors(*(_DWORD *)&this->m_btnPar2[11][5]._texName[240]);
LABEL_31:
              SetEnable((UICaption *)&this->m_btnPar2[7][5]._texName[72]);
              (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)((_BYTE *)(&this->m_btnPar2[6][6]._element.m_mouseoff), (_DWORD)(0));
              result = 1;
              break;
            default:
              goto LABEL_36;
          }
          return result;
        }
      }
      sub_445E50((int)(&this->m_btnPar2[7][6].m_posy + 86 * v14));
      LineupUI_Render3DModels(v14);
      SetEnable((UICaption *)&this->m_btnPar2[7][5]._texName[72]);
      (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)((_BYTE *)(&this->m_btnPar2[6][6]._element.m_mouseoff), (_DWORD)(0));
      v57 = (const void *)off_5B9DE4;
LABEL_35:
      Instance = (CScreenMode *)CScreenMode::GetInstance();
      (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v57, 1);
LABEL_36:
      result = 1;
      break;
    case 1005:
      (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
        &this->m_btnPar2[11][5]._element.m_rect.top,
        0);
      (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])((char *)(&this->m_btnPar2[11][6]._texName[40]), (_DWORD)(0));
      result = 1;
      break;
    case 1007:
      this->m_TimeMoney.m_bfocus = lparam;
      if ( lparam <= -1 )
      {
        SetEnable((UICaption *)&this->m_btnPar2[12][2]._texName[208]);
        this->m_btnPar2[7][4].m_time.oldtick = 0;
        (*(void ( **)(LONG *, _DWORD))this->m_btnPar2[11][5]._element.m_rect.top)(
          &this->m_btnPar2[11][5]._element.m_rect.top,
          0);
        (**(void ( ***)(char *, _DWORD))&this->m_btnPar2[11][6]._texName[40])((char *)(&this->m_btnPar2[11][6]._texName[40]), (_DWORD)(0));
        result = 1;
      }
      else
      {
        SetEnable((UICaption *)&this->m_btnPar2[7][5]._texName[72]);
        (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)((_BYTE *)(&this->m_btnPar2[6][6]._element.m_mouseoff), (_DWORD)(0));
        (((TaskBookUI *)this))->TaskBookUI::SetEntryCaption(*(_DWORD *)&this->m_btnPar2[11][5]._texName[240], this->m_TimeMoney.m_bfocus) /* [ROWTABLE] */;
        v19 = (int *)*(&this->m_btnPar[9][6].view_radiusY
                     + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
                     + 3 * this->m_TimeMoney.m_bfocus);
        if ( *((_BYTE *)v19 + 613) == 5 )
        {
          (((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)&this->m_btnPar2[7][4]._H))->Camera::UpdateCameraLookAt(330, 280, 600);
        }
        else if ( *((_BYTE *)v19 + 612) == 11 )
        {
          (((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H))->CCBFiveNimbusWindow::SetFloatParam(228.0);
          (((Camera *)&this->m_btnPar2[7][4]._H))->Camera::UpdateCameraLookAt(330, 272, 600);
        }
        else
        {
          v20 = (unsigned long)*v19;
          if ( v20 == 8114 || v20 == 8132 )
          {
            (((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H))->CCBFiveNimbusWindow::SetFloatParam(180.0);
            (((Camera *)&this->m_btnPar2[7][4]._H))->Camera::UpdateCameraLookAt(330, 252, 600);
          }
          else
          {
            (((CCBFiveNimbusWindow *)&this->m_btnPar2[7][4]._H))->CCBFiveNimbusWindow::SetFloatParam(180.0);
            (((Camera *)&this->m_btnPar2[7][4]._H))->Camera::UpdateCameraLookAt(330, 268, 600);
          }
        }
        if ( !strcmp(
                (const char *)(*(&this->m_btnPar[9][6].view_radiusY
                               + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
                               + 3 * this->m_TimeMoney.m_bfocus)
                             + 36),
                unk_C10D38) )
        {
          sprintf((char *const)&this->rc.right, "%s", "NONE");
        }
        else
        {
          v21 = (const char *)(*(&this->m_btnPar[9][6].view_radiusY
                               + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
                               + 3 * this->m_TimeMoney.m_bfocus)
                             + 36);
          sprintf((char *const)&this->rc.right, "Item\\%s\\%s.pol", v21, v21);
        }
        (((PalScript *)&this->m_btnPar2[7][4].m_time))->PalScript::LoadModel((const char *)&this->rc.right, 0);
        v22 = *(&this->m_btnPar[9][6].view_radiusY
              + 897 * *(_DWORD *)&this->m_btnPar2[11][5]._texName[240]
              + 3 * this->m_TimeMoney.m_bfocus);
        v23 = (const char *)(v22 + 36);
        v62 = (const char *)(v22 + 66);
        if ( !strcmp((const char *)(v22 + 36), unk_C10D38) )
        {
          sprintf((char *const)&this->rc.right, "%s", "NONE");
        }
        else
        {
          memset(Buffer, 0, sizeof(Buffer));
          v75 = 0;
          v76 = 0;
          sprintf(Buffer, "%s%s", v23, v62);
          sprintf((char *const)&this->rc.right, "Item\\%s\\%s.tga", v23, Buffer);
        }
        (((gbGeomNode *)this->m_btnPar2[7][4].m_color.Color))->gbGeomNode::ReplaceTexture((const char *)&this->rc.right);
        this->m_btnPar2[7][4].m_time.oldtick = 1;
        p_m_nTextW = (int *)&this->m_btnPar2[8][2]._element.m_nTextW;
        v25 = 5;
        do
        {
          v26 = 5;
          do
          {
            (*(void ( **)(int *, _DWORD))*p_m_nTextW)(p_m_nTextW, 0);
            p_m_nTextW += 45;
            --v26;
          }
          while ( v26 );
          --v25;
        }
        while ( v25 );
        switch ( *(_DWORD *)&this->m_btnPar2[11][5]._texName[240] )
        {
          case 0:
            (((UIListBox *)&this->m_btnPar2[10][0]._x))->UIListBox::GetGridOffset(&pOut, this->m_TimeMoney.m_bfocus);
            v28 = (const char *)*v27;
            v63 = (const char *)v27[1];
            break;
          case 1:
            (((UIListBox *)&this->m_btnPar2[10][2]._texName[20]))->UIListBox::GetGridOffset(&v72, this->m_TimeMoney.m_bfocus);
            v28 = (const char *)*v29;
            v63 = (const char *)v29[1];
            break;
          case 2:
            (((UIListBox *)&this->m_btnPar2[10][4]._texName[64]))->UIListBox::GetGridOffset(&v73, this->m_TimeMoney.m_bfocus);
            v28 = (const char *)*v30;
            v63 = (const char *)v30[1];
            break;
          case 3:
            (((UIListBox *)&this->m_btnPar2[10][6]._texName[108]))->UIListBox::GetGridOffset(&v68, this->m_TimeMoney.m_bfocus);
            v28 = (const char *)*v31;
            v63 = (const char *)v31[1];
            break;
          case 4:
            (((UIListBox *)&this->m_btnPar2[11][1]._texName[152]))->UIListBox::GetGridOffset(&v69, this->m_TimeMoney.m_bfocus);
            v28 = (const char *)*v32;
            v63 = (const char *)v32[1];
            break;
          case 5:
            (((UIListBox *)&this->m_btnPar2[11][3]._texName[196]))->UIListBox::GetGridOffset(&v70, this->m_TimeMoney.m_bfocus);
            v28 = (const char *)*v33;
            v63 = (const char *)v33[1];
            switch ( *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus) + 612) )
            {
              case 7:
                v34 = 0;
                v35 = (int *)&this->m_btnPar2[8][2]._element.m_nTextW;
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v34 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v34
                                + 614) )
                  {
                    (*(void ( **)(int *, int))*v35)(v35, 1);
                  }
                  ++v34;
                  v35 += 225;
                }
                while ( v34 < 5 );
                break;
              case 8:
                v36 = 0;
                v37 = (char *)&this->m_btnPar2[8][3]._element.m_text[8];
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v36 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v36
                                + 614) )
                  {
                    (**(void ( ***)(char *, int))v37)((char *)(v37), (int)(1));
                  }
                  ++v36;
                  v37 += 900;
                }
                while ( v36 < 5 );
                break;
              case 9:
                v38 = 0;
                p_m_sec = (unsigned int *)&this->m_btnPar2[8][4].m_sec;
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v38 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v38
                                + 614) )
                  {
                    (*(void ( **)(unsigned int *, int))*p_m_sec)(p_m_sec, 1);
                  }
                  ++v38;
                  p_m_sec += 225;
                }
                while ( v38 < 5 );
                break;
              case 0xA:
                v40 = 0;
                v41 = (char *)&this->m_btnPar2[8][3]._texName[184];
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v40 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v40
                                + 614) )
                  {
                    (**(void ( ***)(char *, int))v41)((char *)(v41), (int)(1));
                  }
                  ++v40;
                  v41 += 900;
                }
                while ( v40 < 5 );
                break;
              case 0xB:
                v42 = 0;
                v43 = (char *)&this->m_btnPar2[8][3]._texName[4];
                do
                {
                  if ( this->m_btnPar2[7][1]._texName[v42 + 252]
                    && *(_BYTE *)(*(&this->m_btnPar[14][1]._element.m_rect.top + 3 * this->m_TimeMoney.m_bfocus)
                                + v42
                                + 614) )
                  {
                    (**(void ( ***)(char *, int))v43)((char *)(v43), (int)(1));
                  }
                  ++v42;
                  v43 += 900;
                }
                while ( v42 < 5 );
                break;
              default:
                goto LABEL_95;
            }
            break;
          default:
            v28 = (const char *)v62;
            break;
        }
LABEL_95:
        m_disablepicInfo = this->m_btnPar2[11][6]._element.m_disablepicInfo;
        v45 = (char *)&this->m_btnPar2[11][5]._texName[248];
        v46 = (unsigned int)(v63 - 4);
        v47 = (unsigned int)(v28 + 162);
        if ( m_disablepicInfo )
        {
          if ( m_disablepicInfo == (_PlugInfo *)1 )
          {
            m_ppicInfo = this->m_btnPar2[11][6]._element.m_ppicInfo;
            this->m_btnPar2[11][5]._element.m_wndcolor.Color = v46;
            this->m_btnPar2[11][5]._element.m_fontcolor.Color = v47;
            this->m_btnPar2[11][5]._element.m_id = (unsigned int)m_ppicInfo + v47;
            this->m_btnPar2[11][5]._element.m_rect.left = (LONG)this->m_btnPar2[11][6]._element.m_disablepic + v46;
            (((UIWnd *)&this->m_btnPar2[11][6]._texName[40]))->UIWnd::sub_445FA0(&this->m_btnPar2[11][5]._element.m_fontcolor);
            v49 = (char *)this->m_btnPar2[11][6]._element.m_pbk2 + this->m_btnPar2[11][5]._element.m_id;
            v50 = this->m_btnPar2[11][6]._element.m_ppicInfo;
            *(_DWORD *)&this->m_btnPar2[11][5]._texName[252] = this->m_btnPar2[11][5]._element.m_wndcolor.Color;
            left = this->m_btnPar2[11][5]._element.m_rect.left;
            *(_DWORD *)v45 = (_DWORD)v49;
            *(_DWORD *)((UIWnd *)&this->m_btnPar2[11][5]._element) = left;
            this->m_btnPar2[11][5]._ptex = (gbTexture *)&v49[(_DWORD)v50];
            (((UIWnd *)&this->m_btnPar2[11][5]._element.m_rect.top))->UIWnd::sub_445FA0(&this->m_btnPar2[11][5]._texName[248]);
          }
        }
        else
        {
          v52 = this->m_btnPar2[11][6]._element.m_ppicInfo;
          m_disablepic = this->m_btnPar2[11][6]._element.m_disablepic;
          *(_DWORD *)&this->m_btnPar2[11][5]._texName[252] = v46;
          *(_DWORD *)v45 = v47;
          this->m_btnPar2[11][5]._ptex = (gbTexture *)((char *)v52 + v47);
          *(_DWORD *)((UIWnd *)&this->m_btnPar2[11][5]._element) = (unsigned long)((char *)m_disablepic + v46);
          (((UIWnd *)&this->m_btnPar2[11][5]._element.m_rect.top))->UIWnd::sub_445FA0(&this->m_btnPar2[11][5]._texName[248]);
          v54 = *(_DWORD *)v45;
          v55 = (char *)this->m_btnPar2[11][6]._element.m_pbk2 + *(_DWORD *)((UIWnd *)&this->m_btnPar2[11][5]._element);
          this->m_btnPar2[11][5]._element.m_wndcolor.Color = (unsigned int)v55;
          this->m_btnPar2[11][5]._element.m_fontcolor.Color = v54;
          this->m_btnPar2[11][5]._element.m_id = (unsigned int)this->m_btnPar2[11][5]._ptex;
          this->m_btnPar2[11][5]._element.m_rect.left = (LONG)this->m_btnPar2[11][6]._element.m_disablepic
                                                      + (unsigned int)v55;
          (((UIWnd *)&this->m_btnPar2[11][6]._texName[40]))->UIWnd::sub_445FA0(&this->m_btnPar2[11][5]._element.m_fontcolor);
        }
        (*(void ( **)(LONG *, int))this->m_btnPar2[11][5]._element.m_rect.top)(
          &this->m_btnPar2[11][5]._element.m_rect.top,
          1);
        (**(void ( ***)(char *, int))&this->m_btnPar2[11][6]._texName[40])((char *)(&this->m_btnPar2[11][6]._texName[40]), (int)(1));
        sub_445E50((int)&this->m_btnPar2[11][5]._element.m_rect.top);
        sub_445E50((int)&this->m_btnPar2[11][6]._texName[40]);
        result = 1;
      }
      break;
    case 1009:
      if ( wparam == 801 )
      {
        v56 = HIWORD(lparam);
        if ( (unsigned __int16)lparam > *(int *)&this->m_btnPar2[7][5]._texName[224]
          && (unsigned __int16)lparam < *(int *)&this->m_btnPar2[7][5]._texName[232]
          && v56 > *(_DWORD *)&this->m_btnPar2[7][5]._texName[228]
          && v56 < *(_DWORD *)&this->m_btnPar2[7][5]._texName[236] )
        {
          SetEnable((UICaption *)&this->m_btnPar2[7][5]._texName[72]);
          (**(void ( ***)(_BYTE *, _DWORD))&this->m_btnPar2[6][6]._element.m_mouseoff)((_BYTE *)(&this->m_btnPar2[6][6]._element.m_mouseoff), (_DWORD)(0));
        }
      }
      result = 1;
      break;
    default:
      result = this->UIWnd::OnMessage(msg, wparam, lparam);
      break;
  }
  return result;
}

// 0x0047B0E0
char LineupUI::CountVisibleItems(int nVal)
{
  int v3; // esi
  _inline_MUIDialog_m_btRc *v4; // ebx

  v3 = 0;
  if ( *((int *)&this->pStateUI + 1344) <= 0 )
    return 1;
  v4 = (_inline_MUIDialog_m_btRc *)(&this->m_DlgEx.m_btRc + 17);
  do
  {
    UIListBox_SetChildParam(v3++);
    v4 = (_inline_MUIDialog_m_btRc *)((char *)v4 + 796);
  }
  while ( v3 < *((_DWORD *)&this->pStateUI + 1344) );
  return 1;
}

// 0x0047E5C0
LineupUI::LineupUI()
{
  ((UIListBox *)this)->UIListBox::UIListBox();
  this->bkWndX = 800;
  this->bkWndY = 600;
  this->m_IsMsg = 0;
  this->m_Is[0] = 0;
  *(_DWORD *)&this->m_Is[3] = 0;
  (((UIFrameContainer *)&this->m_Frame))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->m_Frame + 1)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_TimeMoney.m_FVF))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_OutFrameT.m_pbk2))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_OutFrameR.m_disablepic))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->stp_Exit.m_offsetx))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->stp_Exit.m_caption[60]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->stp_Effect.m_benable))->UIFrameContainer::ResetContainerState();
  (((UIProgressBar *)&this->m_CtrlPlank[11].m_Name.m_ppic))->UIProgressBar::ctor();
  (((UIProgressBar *)&this->m_CtrlPlank[11].m_Btn[124]))->UIProgressBar::ctor();
  (((UIFrameContainer *)&this->m_CtrlPlank[12].m_Name.m_rect.right))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_CtrlPlank[12].m_Dw.m_rect.right))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_CtrlPlank[12].m_Btn[24]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->pStateUI + 29)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->pStateUI + 67)))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  ((UIPushButton *)(&this->pStateUI + 277))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->pStateUI + 339))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->pStateUI + 401))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->pStateUI + 463))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->pStateUI + 525))->UIPushButton::UIPushButton();
  ((UIPushButton *)(&this->pStateUI + 587))->UIPushButton::UIPushButton();
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_text[12] = 0;
  this->m_CtrlPlank[11].m_Name.m_pbk = ((gbTexture *)0);
  this->m_CtrlPlank[11].m_Name.m_pbkInfo = ((_PlugInfo *)0);
  (((MainEquipUI *)this))->MainEquipUI::ClearState() /* [ROWTABLE] */;
}

// 0x0047F880
void LineupUI::RenderEffects()
{
  int i; // edi
  CCBMagicWindow *v3; // [esp+0x0] [ebp-0x4]

  (((CCBControlWindow *)this))->CCBControlWindow::Render(v3) /* [ROWTABLE] */;
  if ( this->m_CtrlPlank[11].m_Name.m_text[(unsigned int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + 12] )
  {
    for ( i = 0; i < 16; ++i )
    {
      if ( IsVisible((RenderTarget *)((char *)&this->m_GameTime.m_childs
                                    + 9344 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo
                                    + 584 * i)) )
        ((UIParticle *)((UIParticle *)&this->m_GameTime.m_childs + 16 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + i))->UIParticle::Apply(11);
      if ( IsVisible((RenderTarget *)&this->m_btnPar2[1][16 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + 4 + i]._texName[36]) )
        (((UIParticle *)&this->m_btnPar2[1][16 * (int)this->m_CtrlPlank[11].m_Name.m_pbkInfo + 4 + i]._texName[36]))->UIParticle::Apply(10);
    }
  }
}

// 0x0047F970
int LineupUI::CleanupAndForwardInput()
{
  __int64 v2; // rax
  int v3; // ebx
  int v4; // ebp
  char *v5; // edi
  int v6; // ebp
  char *v7; // edi
  int v8; // ebp
  char *v9; // edi
  int v10; // ebp
  int v11; // edi
  StateUI **v12; // ecx
  int v14; // [esp+0x1C] [ebp-0x14]
  int fVal; // [esp+0x34] [ebp+0x4]
  int a3; // [esp+0x38] [ebp+0x8]

  v2 = (__int64)g_fGameTimer;
  v3 = (int)v2 / 3600;
  v4 = (int)v2 / 60 % 60;
  v14 = (int)v2 % 60;
  if ( (int)v2 / 3600 < 100 )
    sprintf(this->buf, "%02d:%02d:%02d", v3, v4, v14);
  else
    sprintf(this->buf, "%03d:%02d:%02d", v3, v4, v14);
  SetEnable((UICaption *)&this->stp_Exit.m_caption[60]);
  sprintf(this->buf, (const char *)&dir[20], *(&g_RoleSlotBuf.dword_17AA450 + 147));
  SetEnable((UICaption *)&this->stp_Effect.m_benable);
  (((ArcLocaleRole *)this))->ArcLocaleRole::HandleKeyInput();
  (((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbGeomNode::SetAnimLoop(1);
  if ( (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::CheckAnimOver() )
  {
    (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(0.0);
    *((_BYTE *)&this->pStateUI + 5260) = 1;
  }
  if ( *((_BYTE *)&this->pStateUI + 5260) )
  {
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 105))((StateUI **)(&this->pStateUI + 105), (int)(1));
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 191))((StateUI **)(&this->pStateUI + 191), (int)(1));
    (*(void ( **)(LONG *, int))this->m_CtrlPlank[12].m_Name.m_rect.right)(
      &this->m_CtrlPlank[12].m_Name.m_rect.right,
      1);
    (*(void ( **)(LONG *, int))this->m_CtrlPlank[12].m_Dw.m_rect.right)(
      &this->m_CtrlPlank[12].m_Dw.m_rect.right,
      1);
    (**(void ( ***)(char *, int))&this->m_CtrlPlank[12].m_Btn[24])((char *)(&this->m_CtrlPlank[12].m_Btn[24]), (int)(1));
    v5 = (char *)&this->m_CtrlPlank[12].m_Btn[176];
    v6 = 5;
    do
    {
      (**(void ( ***)(char *, int))v5)((char *)(v5), (int)(1));
      v5 += 152;
      --v6;
    }
    while ( v6 );
    v7 = (char *)&this->m_CtrlPlank[13].m_Btn[224];
    v8 = 5;
    do
    {
      (**(void ( ***)(char *, int))v7)((char *)(v7), (int)(1));
      v7 += 152;
      --v8;
    }
    while ( v8 );
    v9 = (char *)&this->m_ProtectPanel.m_WPXFace + 252;
    v10 = 4;
    do
    {
      (**(void ( ***)(char *, int))v9)((char *)(v9), (int)(1));
      v9 += 152;
      --v10;
    }
    while ( v10 );
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 29))((StateUI **)(&this->pStateUI + 29), (int)(1));
    (**((void ( ***)(StateUI **, int))&this->pStateUI + 67))((StateUI **)(&this->pStateUI + 67), (int)(1));
    *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[200] = *((int *)&this->pStateUI + *((_DWORD *)&this->pStateUI + 1258) + 651) > 0;
    v11 = *((_DWORD *)&this->pStateUI + 1316);
    *((_BYTE *)&this->pStateUI + 5280) = 1;
    if ( v11 >= 0 )
    {
      if ( *((_BYTE *)&this->pStateUI + 5261) )
      {
        if ( v11 > 1 )
          v11 = 1;
        switch ( *((_DWORD *)&this->pStateUI + 1257) )
        {
          case 0:
            Object3D_LoadActorModel(0);
            goto LABEL_22;
          case 1:
            if ( v11 )
            {
LABEL_22:
              Object3D_LoadActorModel(1);
LABEL_23:
              Object3D_LoadActorModel(2);
LABEL_24:
              Object3D_LoadActorModel(3);
LABEL_25:
              Object3D_LoadActorModel(4);
LABEL_26:
              Object3D_LoadActorModel(5);
            }
            else
            {
              Object3D_LoadActorModel(0);
            }
            break;
          case 2:
            if ( v11 )
              goto LABEL_23;
            Object3D_LoadActorModel(0);
            Object3D_LoadActorModel(1);
            break;
          case 3:
            if ( v11 )
              goto LABEL_24;
            Object3D_LoadActorModel(0);
            Object3D_LoadActorModel(1);
            Object3D_LoadActorModel(2);
            break;
          case 4:
            if ( v11 )
              goto LABEL_25;
            Object3D_LoadActorModel(0);
            Object3D_LoadActorModel(1);
            Object3D_LoadActorModel(2);
            Object3D_LoadActorModel(3);
            break;
          case 5:
            if ( v11 )
              goto LABEL_26;
            Object3D_LoadActorModel(0);
            Object3D_LoadActorModel(1);
            Object3D_LoadActorModel(2);
            Object3D_LoadActorModel(3);
            Object3D_LoadActorModel(4);
            break;
          default:
            break;
        }
        (((StateUI *)this))->StateUI::ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 1u, *((UIWnd **)&this->pStateUI + 1316)) /* [ROWTABLE] */;
        *((_BYTE *)&this->pStateUI + 5261) = 0;
      }
      else
      {
        Object3D_LoadActorModel(*((_DWORD *)&this->pStateUI + 1257));
        switch ( *((_DWORD *)&this->pStateUI + 1257) )
        {
          case 0:
            (**((void ( ***)(StateUI **, int))&this->pStateUI + 277))((StateUI **)(&this->pStateUI + 277), (int)(1));
            break;
          case 1:
            v12 = (StateUI **)(&this->pStateUI + 339);
            goto LABEL_45;
          case 2:
            (**((void ( ***)(StateUI **, int))&this->pStateUI + 401))((StateUI **)(&this->pStateUI + 401), (int)(1));
            break;
          case 3:
            v12 = (StateUI **)(&this->pStateUI + 463);
            goto LABEL_45;
          case 4:
            (**((void ( ***)(StateUI **, int))&this->pStateUI + 525))((StateUI **)(&this->pStateUI + 525), (int)(1));
            break;
          case 5:
            v12 = (StateUI **)(&this->pStateUI + 587);
LABEL_45:
            ((void ( *)(StateUI **, int))((UIWnd *)(*v12)))(v12, 1);
            break;
          default:
            break;
        }
      }
      *((_DWORD *)&this->pStateUI + 1316) = -1;
    }
    *((_BYTE *)&this->pStateUI + 5260) = 0;
  }
  sub_445E50((int)(&this->pStateUI + 105));
  sub_445E50((int)(&this->pStateUI + 191));
  if ( *((_BYTE *)&this->pStateUI + 5280) )
    (((MainEquipUI *)this))->MainEquipUI::UpdateFadeAlpha(*(float *)&fVal) /* [ROWTABLE] */;
  return (((SceneObj *)this))->SceneObj::Update(fVal, a3) /* [ROWTABLE] */;
}

// 0x00480600
int LineupUI::OnMessage(int nVal, char *pszBuf, int nVal2)
{
  int v5; // edi
  int i; // edi
  CScreenMode *Instance; // eax
  char *v8; // esi
  UICursor *v9; // ecx
  int result; // eax
  CScreenMode *v11; // eax
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  CScreenMode *v16; // eax
  CScreenMode *v17; // eax
  CScreenMode *v18; // eax
  int v19; // eax
  int v20; // ecx
  bool v21; // sf
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // ecx
  StateUI **v26; // ecx
  int v27; // ecx
  CScreenMode *v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // eax
  CScreenMode *v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // ecx
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // ecx
  int v44; // ecx
  CScreenMode *v45; // eax
  int v46; // eax
  CScreenMode *v47; // eax
  int v48; // eax
  CScreenMode *v49; // eax
  int v50; // eax
  int v51; // eax
  int v52; // eax
  char v53; // al
  int v54; // [esp-0xC] [ebp-0x18]
  const void *v55; // [esp-0x8] [ebp-0x14]
  const void *v56; // [esp-0x8] [ebp-0x14]
  const void *v57; // [esp-0x8] [ebp-0x14]
  const void *v58; // [esp-0x8] [ebp-0x14]
  const void *v59; // [esp-0x8] [ebp-0x14]
  const void *v60; // [esp-0x8] [ebp-0x14]
  const void *v61; // [esp-0x8] [ebp-0x14]
  const void *v62; // [esp-0x8] [ebp-0x14]
  const void *v63; // [esp-0x8] [ebp-0x14]
  int v64; // [esp-0x8] [ebp-0x14]
  int v65; // [esp-0x8] [ebp-0x14]
  const void *v66; // [esp-0x8] [ebp-0x14]
  int v67; // [esp-0x8] [ebp-0x14]
  const void *v68; // [esp-0x8] [ebp-0x14]
  int v69; // [esp-0x8] [ebp-0x14]
  int v70; // [esp-0x8] [ebp-0x14]
  const void *v71; // [esp-0x8] [ebp-0x14]
  const void *v72; // [esp-0x8] [ebp-0x14]
  const void *v73; // [esp-0x8] [ebp-0x14]
  int v74; // [esp-0x4] [ebp-0x10]
  int v75; // [esp-0x4] [ebp-0x10]
  int v76; // [esp-0x4] [ebp-0x10]

  v5 = 3;
  switch ( nVal )
  {
    case 1000:
      if ( pszBuf )
      {
        this->m_Is[0] = 1;
        for ( i = 0; i < 8; ++i )
          (((StateUI *)this))->StateUI::AutoScrollParticles(i) /* [ROWTABLE] */;
        this->LineupUI::ShowPage();
        gfxMgr->fSelfIllum = 1.0;
        (((StateUI *)this))->StateUI::CategorizeRoles() /* [ROWTABLE] */;
        (((MainEquipUI *)this))->MainEquipUI::SelectWithSound(0) /* [ROWTABLE] */;
        v55 = (const void *)off_5C3ED4;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v55, 1);
        v8 = (char *)&this->m_CtrlPlank[11].m_Name.m_text[12];
        g_nSceneState = 1;
        *(_DWORD *)v8 = 0;
        *((_DWORD *)v8 + 1) = 0;
        (((UICursor *)v9))->UICursor::_todo_541CC0();
        result = 1;
      }
      else
      {
        (((StateUI *)this))->StateUI::ReleaseResource() /* [ROWTABLE] */;
        *((_DWORD *)&this->pStateUI + 297) = 0;
        *((_BYTE *)&this->pStateUI + 1176) = 0;
        *((_DWORD *)&this->pStateUI + 359) = 0;
        *((_BYTE *)&this->pStateUI + 1424) = 0;
        *((_DWORD *)&this->pStateUI + 421) = 0;
        *((_BYTE *)&this->pStateUI + 1672) = 0;
        *((_DWORD *)&this->pStateUI + 483) = 0;
        *((_BYTE *)&this->pStateUI + 1920) = 0;
        *((_DWORD *)&this->pStateUI + 545) = 0;
        *((_BYTE *)&this->pStateUI + 2168) = 0;
        *((_DWORD *)&this->pStateUI + 607) = 0;
        *((_BYTE *)&this->pStateUI + 2416) = 0;
        MainEquipUI_LoadFromFile(0);
        (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\close.CVD", 0);
        (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(0.0);
        this->m_Is[0] = 0;
        result = 1;
      }
      break;
    case 1001:
      if ( pszBuf > (char *)&byte_A00110 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00604u:
            if ( *((_DWORD *)&this->pStateUI + 1317) != 2 )
            {
              (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
            }
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_bvisible + 24))(
              this->m_CtrlPlank[11].m_Dw.m_bvisible,
              0);
            (((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbGeomNode::SetAnimLoop(1);
            v19 = *((_DWORD *)&this->pStateUI + 1260) - 1;
            *((_DWORD *)&this->pStateUI + 1260) = v19;
            if ( v19 )
            {
              v20 = *((_DWORD *)&this->pStateUI + 1257);
              v21 = v19 < 0;
              v22 = *((_DWORD *)&this->pStateUI + 1258);
              if ( v21 )
              {
                if ( v20 != v22 )
                  *((_DWORD *)&this->pStateUI + 1257) = v22;
                v23 = v22 - 1;
                *((_DWORD *)&this->pStateUI + 1258) = v23;
                *((_DWORD *)&this->pStateUI + 1257) = v23;
                if ( v23 < 0 )
                {
                  v24 = v23 + 1;
                  *((_DWORD *)&this->pStateUI + 1260) = 0;
                  *((_DWORD *)&this->pStateUI + 1257) = v24;
                  *((_DWORD *)&this->pStateUI + 1258) = v24;
                  return 1;
                }
                v25 = *((_DWORD *)&this->pStateUI + v23 + 651);
                if ( v25 <= 0 )
                {
                  v26 = (StateUI **)(&this->pStateUI + 105);
                  goto LABEL_30;
                }
                v27 = v25 - 1;
                *((_DWORD *)&this->pStateUI + 1260) = v27;
                if ( !v27 )
                {
                  *((_DWORD *)&this->pStateUI + 1316) = 1;
                  (((StateUI *)this))->StateUI::DispatchCmd(v23) /* [ROWTABLE] */;
                  *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
                }
                v22 = *((_DWORD *)&this->pStateUI + 1258);
              }
              else if ( v20 != v22 )
              {
                *((_DWORD *)&this->pStateUI + 1257) = v22;
              }
              (((MainEquipUI *)this))->MainEquipUI::SelectWithSound(v22) /* [ROWTABLE] */;
            }
            else
            {
              v64 = *((_DWORD *)&this->pStateUI + 1258);
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              (((StateUI *)this))->StateUI::DispatchCmd(v64) /* [ROWTABLE] */;
              (((MainEquipUI *)this))->MainEquipUI::SelectWithSound(*((_DWORD *)&this->pStateUI + 1258)) /* [ROWTABLE] */;
              *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
            }
            (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(2.0);
            (((MainEquipUI *)this))->MainEquipUI::SetAdornVisible(0) /* [ROWTABLE] */;
            v66 = (const void *)off_5C3ED4;
            v28 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v28))->CScreenMode::AudioSetPosition(v66, 1);
            return 1;
          case 0xA00605u:
            if ( *((_DWORD *)&this->pStateUI + 1317) != 1 )
            {
              (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 1;
            }
            (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_bvisible + 24))(
              this->m_CtrlPlank[11].m_Dw.m_bvisible,
              0);
            (((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbGeomNode::SetAnimLoop(1);
            v29 = *((_DWORD *)&this->pStateUI + 1258);
            ++*((_DWORD *)&this->pStateUI + 1260);
            if ( *((int *)&this->pStateUI + v29 + 651) <= 0 )
            {
              v35 = v29 + 1;
              *((_DWORD *)&this->pStateUI + 1258) = v35;
              *((_DWORD *)&this->pStateUI + 1257) = v35;
              if ( v35 < 6 )
              {
                v26 = (StateUI **)(&this->pStateUI + 191);
LABEL_30:
                sub_445E50((int)v26);
                v74 = *((_DWORD *)&this->pStateUI + 1317);
                v65 = *((_DWORD *)&this->pStateUI + 1258);
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(v65, v74) /* [ROWTABLE] */;
                return 1;
              }
              else
              {
                v36 = v35 - 1;
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                *((_DWORD *)&this->pStateUI + 1258) = v36;
                *((_DWORD *)&this->pStateUI + 1257) = v36;
                return 1;
              }
            }
            else
            {
              if ( *((_DWORD *)&this->pStateUI + 1257) != v29 )
                *((_DWORD *)&this->pStateUI + 1257) = v29;
              v30 = *((_DWORD *)&this->pStateUI + 1257);
              v31 = *((_DWORD *)&this->pStateUI + 1260);
              if ( v31 < *((_DWORD *)&this->pStateUI + v30 + 651) )
              {
                sub_445E50((int)(&this->pStateUI + 105));
                if ( *((_DWORD *)&this->pStateUI + 1260) == 1 )
                {
                  v67 = *((_DWORD *)&this->pStateUI + 1257);
                  *((_DWORD *)&this->pStateUI + 1316) = 0;
                  (((StateUI *)this))->StateUI::DispatchCmd(v67) /* [ROWTABLE] */;
                }
                else
                {
                  *((_DWORD *)&this->pStateUI + 1316) = -1;
                }
                (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(2.0);
                (((MainEquipUI *)this))->MainEquipUI::SetAdornVisible(0) /* [ROWTABLE] */;
                (((MainEquipUI *)this))->MainEquipUI::RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257)) /* [ROWTABLE] */;
                v68 = (const void *)off_5C3ED4;
                v34 = (CScreenMode *)CScreenMode::GetInstance();
                (((CScreenMode *)v34))->CScreenMode::AudioSetPosition(v68, 1);
                return 1;
              }
              else
              {
                v32 = v30 + 1;
                *((_DWORD *)&this->pStateUI + 1257) = v32;
                *((_DWORD *)&this->pStateUI + 1258) = v32;
                if ( v32 < 6 )
                {
                  v75 = *((_DWORD *)&this->pStateUI + 1317);
                  *((_DWORD *)&this->pStateUI + 1260) = 0;
                  (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(v32, v75) /* [ROWTABLE] */;
                }
                else
                {
                  v33 = v32 - 1;
                  *((_DWORD *)&this->pStateUI + 1257) = v33;
                  *((_DWORD *)&this->pStateUI + 1258) = v33;
                  *((_DWORD *)&this->pStateUI + 1260) = v31 - 1;
                }
                return 1;
              }
            }
          case 0xA00606u:
            v37 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v37 <= 0 )
            {
              if ( v37 )
                goto LABEL_84;
              if ( *((_DWORD *)&this->pStateUI + 1317) != 2 )
              {
                (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
                *((_DWORD *)&this->pStateUI + 1317) = 2;
              }
              (*(void ( **)(int, _DWORD))(*(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_bvisible + 24))(
                this->m_CtrlPlank[11].m_Dw.m_bvisible,
                0);
              (((gbGeomNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbGeomNode::SetAnimLoop(1);
              v38 = *((_DWORD *)&this->pStateUI + 1260) - 1;
              *((_DWORD *)&this->pStateUI + 1260) = v38;
              if ( v38 )
              {
                v39 = *((_DWORD *)&this->pStateUI + 1257);
                v21 = v38 < 0;
                v40 = *((_DWORD *)&this->pStateUI + 1258);
                if ( v21 )
                {
                  if ( v39 != v40 )
                    *((_DWORD *)&this->pStateUI + 1257) = v40;
                  v41 = v40 - 1;
                  *((_DWORD *)&this->pStateUI + 1258) = v41;
                  *((_DWORD *)&this->pStateUI + 1257) = v41;
                  if ( v41 < 0 )
                  {
                    v42 = v41 + 1;
                    *((_DWORD *)&this->pStateUI + 1260) = 0;
                    *((_DWORD *)&this->pStateUI + 1257) = v42;
                    *((_DWORD *)&this->pStateUI + 1258) = v42;
                    goto LABEL_84;
                  }
                  v43 = *((_DWORD *)&this->pStateUI + v41 + 651);
                  if ( v43 <= 0 )
                  {
                    sub_445E50((int)(&this->pStateUI + 105));
                    v76 = *((_DWORD *)&this->pStateUI + 1317);
                    v70 = *((_DWORD *)&this->pStateUI + 1258);
                    *((_DWORD *)&this->pStateUI + 1260) = 0;
                    (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(v70, v76) /* [ROWTABLE] */;
                    goto LABEL_84;
                  }
                  v44 = v43 - 1;
                  *((_DWORD *)&this->pStateUI + 1260) = v44;
                  if ( !v44 )
                  {
                    *((_DWORD *)&this->pStateUI + 1316) = 1;
                    (((StateUI *)this))->StateUI::DispatchCmd(v41) /* [ROWTABLE] */;
                    *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
                  }
                  v40 = *((_DWORD *)&this->pStateUI + 1258);
                }
                else if ( v39 != v40 )
                {
                  *((_DWORD *)&this->pStateUI + 1257) = v40;
                }
                (((MainEquipUI *)this))->MainEquipUI::SelectWithSound(v40) /* [ROWTABLE] */;
              }
              else
              {
                v69 = *((_DWORD *)&this->pStateUI + 1258);
                *((_DWORD *)&this->pStateUI + 1316) = 1;
                (((StateUI *)this))->StateUI::DispatchCmd(v69) /* [ROWTABLE] */;
                (((MainEquipUI *)this))->MainEquipUI::SelectWithSound(*((_DWORD *)&this->pStateUI + 1258)) /* [ROWTABLE] */;
                *((_DWORD *)&this->pStateUI + 1257) = *((_DWORD *)&this->pStateUI + 1258);
              }
              (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(2.0);
              (((MainEquipUI *)this))->MainEquipUI::SetAdornVisible(0) /* [ROWTABLE] */;
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1257) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 0;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              v54 = *((_DWORD *)&this->pStateUI + 1257);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              (((StateUI *)this))->StateUI::ShowPanels(v54, 0, (UIWnd *)1) /* [ROWTABLE] */;
              (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(2.0);
              (((MainEquipUI *)this))->MainEquipUI::SetAdornVisible(0) /* [ROWTABLE] */;
              (((MainEquipUI *)this))->MainEquipUI::RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257)) /* [ROWTABLE] */;
              *((_BYTE *)&this->pStateUI + 5261) = 1;
            }
            v71 = (const void *)off_5C3ED4;
            v45 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v45))->CScreenMode::AudioSetPosition(v71, 1);
            goto LABEL_84;
          case 0xA00607u:
            v46 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v46 <= 1 )
            {
              if ( v46 >= 1 )
                goto LABEL_104;
              *((_DWORD *)&this->pStateUI + 1257) = 1;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 1;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 1;
              *((_DWORD *)&this->pStateUI + 1316) = 0;
              (((StateUI *)this))->StateUI::ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, 0) /* [ROWTABLE] */;
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1257) = 1;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 1;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              (((StateUI *)this))->StateUI::ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, (UIWnd *)1) /* [ROWTABLE] */;
            }
            (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(2.0);
            (((MainEquipUI *)this))->MainEquipUI::SetAdornVisible(0) /* [ROWTABLE] */;
            (((MainEquipUI *)this))->MainEquipUI::RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257)) /* [ROWTABLE] */;
            *((_BYTE *)&this->pStateUI + 5261) = 1;
            v72 = (const void *)off_5C3ED4;
            v47 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v47))->CScreenMode::AudioSetPosition(v72, 1);
LABEL_104:
            *((_DWORD *)&this->pStateUI + 359) = 1;
            *((_BYTE *)&this->pStateUI + 1424) = 1;
            return 1;
          case 0xA00608u:
            v48 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v48 <= 2 )
            {
              if ( v48 >= 2 )
                break;
              *((_DWORD *)&this->pStateUI + 1257) = 2;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 2;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgdw.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 1;
              *((_DWORD *)&this->pStateUI + 1316) = 0;
              (((StateUI *)this))->StateUI::ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, 0) /* [ROWTABLE] */;
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1257) = 2;
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              *((_DWORD *)&this->pStateUI + 1258) = 2;
              *((_DWORD *)&this->pStateUI + 297) = 0;
              *((_BYTE *)&this->pStateUI + 1176) = 0;
              *((_DWORD *)&this->pStateUI + 359) = 0;
              *((_BYTE *)&this->pStateUI + 1424) = 0;
              *((_DWORD *)&this->pStateUI + 421) = 0;
              *((_BYTE *)&this->pStateUI + 1672) = 0;
              *((_DWORD *)&this->pStateUI + 483) = 0;
              *((_BYTE *)&this->pStateUI + 1920) = 0;
              *((_DWORD *)&this->pStateUI + 545) = 0;
              *((_BYTE *)&this->pStateUI + 2168) = 0;
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
              switch ( *((_DWORD *)&this->pStateUI + 1257) )
              {
                case 0:
                  *((_DWORD *)&this->pStateUI + 297) = 1;
                  *((_BYTE *)&this->pStateUI + 1176) = 1;
                  break;
                case 1:
                  *((_DWORD *)&this->pStateUI + 359) = 1;
                  *((_BYTE *)&this->pStateUI + 1424) = 1;
                  break;
                case 2:
                  *((_DWORD *)&this->pStateUI + 421) = 1;
                  *((_BYTE *)&this->pStateUI + 1672) = 1;
                  break;
                case 3:
                  *((_DWORD *)&this->pStateUI + 483) = 1;
                  *((_BYTE *)&this->pStateUI + 1920) = 1;
                  break;
                case 4:
                  *((_DWORD *)&this->pStateUI + 545) = 1;
                  *((_BYTE *)&this->pStateUI + 2168) = 1;
                  break;
                case 5:
                  *((_DWORD *)&this->pStateUI + 607) = 1;
                  *((_BYTE *)&this->pStateUI + 2416) = 1;
                  break;
                default:
                  break;
              }
              (((PalScript *)&this->m_CtrlPlank[11].m_Dw.m_childs.capacity))->PalScript::LoadModel("UI\\GameMainUI\\JusticeBook\\CVD\\pgup.CVD", 0);
              *((_DWORD *)&this->pStateUI + 1317) = 2;
              *((_DWORD *)&this->pStateUI + 1316) = 1;
              (((StateUI *)this))->StateUI::ShowPanels(*((_DWORD *)&this->pStateUI + 1257), 0, (UIWnd *)1) /* [ROWTABLE] */;
            }
            (((gbVisNode *)this->m_CtrlPlank[11].m_Dw.m_bvisible))->gbVisNode::SetTimeScale(2.0);
            (((MainEquipUI *)this))->MainEquipUI::SetAdornVisible(0) /* [ROWTABLE] */;
            (((MainEquipUI *)this))->MainEquipUI::RenderEquipDetails(*((_DWORD *)&this->pStateUI + 1257)) /* [ROWTABLE] */;
            *((_BYTE *)&this->pStateUI + 5261) = 1;
            v73 = (const void *)off_5C3ED4;
            v49 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v49))->CScreenMode::AudioSetPosition(v73, 1);
            break;
          case 0xA00609u:
            v50 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v50 <= 3 )
            {
              if ( v50 < 3 )
              {
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(3, 1) /* [ROWTABLE] */;
              }
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(3, 2) /* [ROWTABLE] */;
            }
            goto LABEL_129;
          case 0xA00610u:
            v51 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v51 <= 4 )
            {
              if ( v51 < 4 )
              {
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(4, 1) /* [ROWTABLE] */;
              }
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(4, 2) /* [ROWTABLE] */;
            }
            goto LABEL_134;
          case 0xA00611u:
            v52 = *((_DWORD *)&this->pStateUI + 1257);
            if ( v52 >= 5 )
            {
              if ( v52 == 5 )
              {
                *((_DWORD *)&this->pStateUI + 1260) = 0;
                (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(5, 2) /* [ROWTABLE] */;
              }
            }
            else
            {
              *((_DWORD *)&this->pStateUI + 1260) = 0;
              (((MainEquipUI *)this))->MainEquipUI::ShowPanelsWithSound(5, 1) /* [ROWTABLE] */;
            }
            goto LABEL_139;
          default:
            goto LABEL_140;
        }
LABEL_124:
        *((_DWORD *)&this->pStateUI + 421) = 1;
        *((_BYTE *)&this->pStateUI + 1672) = 1;
        result = 1;
      }
      else if ( pszBuf == (char *)&byte_A00110 )
      {
        v63 = (const void *)off_5C3EAC;
        v18 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v18))->CScreenMode::AudioSetPosition(v63, 1);
        (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(9);
        result = 1;
      }
      else
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00102u:
            v56 = (const void *)off_5C3EAC;
            v11 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v11))->CScreenMode::AudioSetPosition(v56, 1);
            (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(0);
            result = 1;
            break;
          case 0xA00103u:
            v57 = (const void *)off_5C3EAC;
            v12 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(v57, 1);
            (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(3);
            result = 1;
            break;
          case 0xA00104u:
            v58 = (const void *)off_5C3EAC;
            v13 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v13))->CScreenMode::AudioSetPosition(v58, 1);
            (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(2);
            result = 1;
            break;
          case 0xA00105u:
            v59 = (const void *)off_5C3EAC;
            v14 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(v59, 1);
            (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(1);
            result = 1;
            break;
          case 0xA00106u:
            v60 = (const void *)off_5C3EAC;
            v15 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(v60, 1);
            (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(5);
            result = 1;
            break;
          case 0xA00108u:
            v61 = (const void *)off_5C3EAC;
            v16 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v16))->CScreenMode::AudioSetPosition(v61, 1);
            (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(4);
            result = 1;
            break;
          case 0xA00109u:
            v62 = (const void *)off_5C3EAC;
            v17 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v17))->CScreenMode::AudioSetPosition(v62, 1);
            (((MainEquipUI *)*(MainEquipUI **)&this->m_Is[3]))->MainEquipUI::HandleMessage(7);
            result = 1;
            break;
          default:
            goto LABEL_140;
        }
      }
      break;
    case 1002:
      if ( pszBuf > (char *)&byte_A00606 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00607u:
            *((_DWORD *)&this->pStateUI + 359) = 1;
            *((_BYTE *)&this->pStateUI + 1424) = 1;
            return 1;
          case 0xA00608u:
            goto LABEL_124;
          case 0xA00609u:
LABEL_129:
            *((_DWORD *)&this->pStateUI + 483) = 1;
            *((_BYTE *)&this->pStateUI + 1920) = 1;
            return 1;
          case 0xA00610u:
LABEL_134:
            *((_DWORD *)&this->pStateUI + 545) = 1;
            *((_BYTE *)&this->pStateUI + 2168) = 1;
            return 1;
          case 0xA00611u:
LABEL_139:
            *((_DWORD *)&this->pStateUI + 607) = 1;
            *((_BYTE *)&this->pStateUI + 2416) = 1;
            goto LABEL_140;
          default:
LABEL_140:
            result = 1;
            break;
        }
      }
      else if ( pszBuf == (char *)&byte_A00606 )
      {
LABEL_84:
        *((_DWORD *)&this->pStateUI + 297) = 1;
        *((_BYTE *)&this->pStateUI + 1176) = 1;
        result = 1;
      }
      else
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00102u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = ((_PlugInfo *)0);
            if ( this->m_CtrlPlank[11].m_Name.m_text[12] )
              goto LABEL_140;
            (((StateUI *)this))->StateUI::AutoScrollParticles(0) /* [ROWTABLE] */;
            return 1;
          case 0xA00103u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)1;
            if ( this->m_CtrlPlank[11].m_Name.m_text[13] )
              goto LABEL_140;
            (((StateUI *)this))->StateUI::AutoScrollParticles(1) /* [ROWTABLE] */;
            return 1;
          case 0xA00104u:
            v5 = 2;
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)2;
            v53 = this->m_CtrlPlank[11].m_Name.m_text[14];
            goto LABEL_150;
          case 0xA00105u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)3;
            v53 = this->m_CtrlPlank[11].m_Name.m_text[15];
LABEL_150:
            if ( v53 )
              goto LABEL_140;
            (((StateUI *)this))->StateUI::AutoScrollParticles(v5) /* [ROWTABLE] */;
            result = 1;
            break;
          case 0xA00106u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)5;
            if ( BYTE1(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_140;
            (((StateUI *)this))->StateUI::AutoScrollParticles(5) /* [ROWTABLE] */;
            return 1;
          case 0xA00107u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)6;
            if ( BYTE2(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_140;
            (((StateUI *)this))->StateUI::AutoScrollParticles(6) /* [ROWTABLE] */;
            return 1;
          case 0xA00108u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)4;
            if ( LOBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_140;
            (((StateUI *)this))->StateUI::AutoScrollParticles(4) /* [ROWTABLE] */;
            return 1;
          case 0xA00109u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)7;
            if ( HIBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) )
              goto LABEL_140;
            (((StateUI *)this))->StateUI::AutoScrollParticles(7) /* [ROWTABLE] */;
            return 1;
          default:
            goto LABEL_140;
        }
      }
      break;
    case 1003:
      if ( pszBuf > (char *)&byte_A00606 )
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00607u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 1 )
              goto LABEL_186;
            *((_DWORD *)&this->pStateUI + 359) = 0;
            *((_BYTE *)&this->pStateUI + 1424) = 0;
            result = 1;
            break;
          case 0xA00608u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 2 )
              goto LABEL_186;
            *((_DWORD *)&this->pStateUI + 421) = 0;
            *((_BYTE *)&this->pStateUI + 1672) = 0;
            result = 1;
            break;
          case 0xA00609u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 3 )
              goto LABEL_186;
            *((_DWORD *)&this->pStateUI + 483) = 0;
            *((_BYTE *)&this->pStateUI + 1920) = 0;
            result = 1;
            break;
          case 0xA00610u:
            if ( *((_DWORD *)&this->pStateUI + 1258) == 4 )
              goto LABEL_186;
            *((_DWORD *)&this->pStateUI + 545) = 0;
            *((_BYTE *)&this->pStateUI + 2168) = 0;
            result = 1;
            break;
          case 0xA00611u:
            if ( *((_DWORD *)&this->pStateUI + 1258) != 5 )
            {
              *((_DWORD *)&this->pStateUI + 607) = 0;
              *((_BYTE *)&this->pStateUI + 2416) = 0;
            }
            goto LABEL_186;
          default:
            goto LABEL_186;
        }
      }
      else if ( pszBuf == (char *)&byte_A00606 )
      {
        if ( *((_DWORD *)&this->pStateUI + 1258) )
        {
          *((_DWORD *)&this->pStateUI + 297) = 0;
          *((_BYTE *)&this->pStateUI + 1176) = 0;
          result = 1;
        }
        else
        {
LABEL_186:
          result = 1;
        }
      }
      else
      {
        switch ( (unsigned int)pszBuf )
        {
          case 0xA00102u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = ((_PlugInfo *)0);
            this->m_CtrlPlank[11].m_Name.m_text[12] = 0;
            result = 1;
            break;
          case 0xA00103u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)1;
            this->m_CtrlPlank[11].m_Name.m_text[13] = 0;
            result = 1;
            break;
          case 0xA00104u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)2;
            this->m_CtrlPlank[11].m_Name.m_text[14] = 0;
            result = 1;
            break;
          case 0xA00105u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)3;
            this->m_CtrlPlank[11].m_Name.m_text[15] = 0;
            result = 1;
            break;
          case 0xA00106u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)5;
            BYTE1(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          case 0xA00107u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)6;
            BYTE2(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          case 0xA00108u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)4;
            LOBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          case 0xA00109u:
            this->m_CtrlPlank[11].m_Name.m_pbkInfo = (_PlugInfo *)7;
            HIBYTE(this->m_CtrlPlank[11].m_Name.m_pbk) = 0;
            result = 1;
            break;
          default:
            goto LABEL_186;
        }
      }
      break;
    default:
      result = this->UIWnd::OnMessage(nVal, (int)pszBuf, nVal2);
      break;
  }
  return result;
}

// 0x004826A0
int LineupUI::RebuildSystemPage()
{
  int m_FVF; // eax
  int *p_m_FVF; // edi
  int v4; // edx
  gbTexture *m_pbk2; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  LONG v12; // edx
  LONG v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  unsigned int v17; // edx
  int v18; // edx
  int v19; // eax
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // eax
  int v24; // ecx
  gbTexture *v25; // edx
  int m_offsetx; // edx
  int v27; // ecx
  int v28; // edx
  int v29; // ecx
  int v30; // edx
  void *v31; // eax
  int v32; // edx
  int v33; // edx
  int v34; // eax
  int v35; // ecx
  int v36; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v39; // ecx
  int v40; // eax
  _DWORD v42[2]; // [esp+A4h] [ebp-0x20] BYREF
  int v43; // [esp+ACh] [ebp-0x18]
  int v44; // [esp+B0h] [ebp-0x14]
  _DWORD v45[4]; // [esp+B4h] [ebp-0x10] BYREF

  m_FVF = this->m_TimeMoney.m_FVF;
  p_m_FVF = (int *)&this->m_TimeMoney.m_FVF;
  v42[1] = 543;
  v42[0] = 0;
  v43 = 256;
  v44 = 600;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_FVF + 16))(
    &this->m_TimeMoney.m_FVF,
    161,
    (_DWORD *)(v42),
    this);
  LOBYTE(v4) = g_bDebugMode;
  (((UIPushButton *)p_m_FVF))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v4);
  m_pbk2 = (gbTexture *)this->m_OutFrameT.m_pbk2;
  v42[0] = v43;
  v43 += 512;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2->IsLoaded)(
    &this->m_OutFrameT.m_pbk2,
    161,
    v42,
    this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameT.m_pbk2))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v6);
  v42[0] = v43;
  v43 += 32;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))this->m_OutFrameR.m_disablepic->IsLoaded)(
    &this->m_OutFrameR.m_disablepic,
    161,
    v42,
    this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameR.m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v7);
  *(_DWORD *)&this->stp_Exit.m_caption[48] = 546;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = 38;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = 148;
  *(_DWORD *)&this->stp_Exit.m_caption[56] = *(_DWORD *)&this->stp_Exit.m_caption[48] + 50;
  LOBYTE(v8) = g_bDebugMode;
  ((void ( *)(gbTexture **, int *, char *, LineupUI *, char *, int, int))this->m_OutFrameL.m_ppic->Height)(
    &this->m_OutFrameL.m_ppic,
    &byte_A00102,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v8);
  this->m_CtrlPlank[11].m_Up.m_pbk2 = (gbTexture *)(*(_DWORD *)&this->stp_Exit.m_caption[48] + 5);
  this->m_CtrlPlank[11].m_Up.m_disablepicInfo = (_PlugInfo *)(*(_DWORD *)&this->stp_Exit.m_caption[44] + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Up.m_mouseoff = *(_DWORD *)&this->stp_Exit.m_caption[52] - 36;
  this->m_CtrlPlank[11].m_Up.m_FVF = *(_DWORD *)&this->stp_Exit.m_caption[56] - 5;
  v9 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v9;
  v9 += 110;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v9;
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(int *, char *, LineupUI *, char *, int, int))(this->stp_Magic.m_offsetx + 28))(
    &byte_A00105,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v9);
  this->m_CtrlPlank[11].m_Name.m_pfather = (UIWnd *)(*(_DWORD *)&this->stp_Exit.m_caption[48] + 5);
  this->m_CtrlPlank[11].m_Name.m_rect.bottom = *(_DWORD *)&this->stp_Exit.m_caption[44] + 35;
  this->m_CtrlPlank[11].m_Name.m_childs.m_pData = (char *)(*(_DWORD *)&this->stp_Exit.m_caption[52] - 36);
  this->m_CtrlPlank[11].m_Name.m_childs.capacity = *(_DWORD *)&this->stp_Exit.m_caption[56] - 5;
  v10 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v10;
  v10 += 110;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v10;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(int *, char *, LineupUI *, char *, int, int))(this->stp_State.m_offsetx + 28))(
    &byte_A00104,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v10);
  this->m_CtrlPlank[11].m_Name.m_rect.left = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  this->m_CtrlPlank[11].m_Name.m_id = *(_DWORD *)&this->stp_Exit.m_caption[44] + 35;
  v11 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  v12 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v13 = v11 - 36;
  v11 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v11;
  v12 -= 5;
  this->m_CtrlPlank[11].m_Name.m_rect.top = v13;
  this->m_CtrlPlank[11].m_Name.m_rect.right = v12;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v11 + 110;
  LOBYTE(v12) = g_bDebugMode;
  (*(void ( **)(int *, int *, char *, LineupUI *, char *, int, LONG))(this->stp_BarL.m_FVF + 28))(
    &this->stp_BarL.m_FVF,
    &byte_A00103,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v12);
  v14 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  *(_DWORD *)((UIWnd *)&this->m_CtrlPlank[11].m_Name) = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  v15 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  this->m_CtrlPlank[11].m_Up.m_nTextW = v14 + 35;
  v16 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v17 = v15 - 36;
  v15 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v15;
  v15 += 110;
  this->m_CtrlPlank[11].m_Name.m_fontcolor.Color = v17;
  this->m_CtrlPlank[11].m_Name.m_wndcolor.Color = v16 - 5;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v15;
  LOBYTE(v15) = g_bDebugMode;
  (*(void ( **)(int *, int *, char *, LineupUI *, char *, int, int))(this->stp_BattleArray.m_offsetx
                                                                                        + 28))(
    &this->stp_BattleArray.m_offsetx,
    &byte_A00108,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v15);
  v18 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  v19 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  this->m_CtrlPlank[11].m_Name.m_childs.m_needscriptdel = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  v20 = v19 - 36;
  this->m_CtrlPlank[11].m_Name.m_childs.m_nSize = v18 + 35;
  v21 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v19 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v19;
  v21 -= 5;
  this->m_CtrlPlank[11].m_Name.m_bcreateok = v20;
  this->m_CtrlPlank[11].m_Name.m_bvisible = v21;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v19 + 110;
  LOBYTE(v21) = g_bDebugMode;
  (*(void ( **)(int *, int *, char *, LineupUI *, char *, int, int))(this->stp_Equip.m_offsetx + 28))(
    &this->stp_Equip.m_offsetx,
    &byte_A00106,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v21);
  v22 = *(_DWORD *)&this->stp_Exit.m_caption[44] + 35;
  this->m_CtrlPlank[11].m_Name.m_bfocus = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  v23 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  this->m_CtrlPlank[11].m_Name.m_benable = v22;
  v24 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  v25 = (gbTexture *)(v23 - 36);
  v23 -= 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v23;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v23 + 110;
  v45[0] = *(_DWORD *)&this->stp_Exit.m_caption[44] - 38;
  v45[1] = 546;
  v45[2] = v45[0] + 256;
  this->m_CtrlPlank[11].m_Name.pDebugTex = v25;
  m_offsetx = this->stp_Exit.m_offsetx;
  this->m_CtrlPlank[11].m_Name.m_align = v24 - 5;
  v45[3] = 610;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_offsetx + 16))(
    &this->stp_Exit.m_offsetx,
    161,
    (_DWORD *)(v45),
    this);
  LOBYTE(v27) = g_bDebugMode;
  (((UIPushButton *)&this->stp_Exit.m_offsetx))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v27);
  LOBYTE(v28) = g_bDebugMode;
  (*(void ( **)(int *, int *, char *, LineupUI *, char *, int, int))(this->stp_Prop.m_offsetx + 28))(
    &this->stp_Prop.m_offsetx,
    &byte_A00107,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v28);
  v29 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  v30 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  LODWORD(this->m_CtrlPlank[11].m_Name.m_ratioh) = *(_DWORD *)&this->stp_Exit.m_caption[48] + 5;
  v31 = (void *)(*(_DWORD *)&this->stp_Exit.m_caption[56] - 5);
  LODWORD(this->m_CtrlPlank[11].m_Name.m_ratiow) = v29 + 35;
  this->m_CtrlPlank[11].m_Name.m_textx = (void *)(v30 - 36);
  v32 = this->stp_System.m_offsetx;
  this->m_CtrlPlank[11].m_Name.m_texty = v31;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(int *, int *, char *, LineupUI *, char *, int, void *))(v32 + 28))(
    &this->stp_System.m_offsetx,
    &byte_A00110,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v31);
  v33 = this->stp_TaskBook.m_offsetx;
  v34 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 22;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = v34;
  v34 += 110;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = v34;
  LOBYTE(v34) = g_bDebugMode;
  (*(void ( **)(int *, int *, char *, LineupUI *, char *, int, int))(v33 + 28))(
    &this->stp_TaskBook.m_offsetx,
    &byte_A00109,
    &this->stp_Exit.m_caption[44],
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v34);
  v35 = *(_DWORD *)&this->stp_Exit.m_caption[48];
  v36 = *(_DWORD *)&this->stp_Exit.m_caption[52] - 36;
  this->m_CtrlPlank[11].m_Name.m_fonttype = (Parent_Data *)(*(_DWORD *)&this->stp_Exit.m_caption[44] + 35);
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_text[4] = v36;
  bkWndX = this->bkWndX;
  *(_DWORD *)this->m_CtrlPlank[11].m_Name.m_text = v35 + 5;
  v39 = *(_DWORD *)&this->stp_Exit.m_caption[56];
  bkWndX -= 38;
  *(_DWORD *)&this->stp_Exit.m_caption[48] = bkWndY - 51;
  *(_DWORD *)&this->stp_Exit.m_caption[44] = bkWndX;
  *(_DWORD *)&this->stp_Exit.m_caption[52] = bkWndX + 38;
  v40 = *(_DWORD *)&this->stp_Exit.m_caption[48];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_text[8] = v39 - 5;
  *(_DWORD *)&this->stp_Exit.m_caption[56] = v40 + 48;
  return (((UIWnd *)&this->stp_System.m_offsetx))->UIWnd::sub_445FA0(&this->stp_Exit.m_caption[44]);
}

// 0x00482BB0
int LineupUI::ShowPage()
{
  int *p_m_offsetx; // ecx

  if ( g_bRoleFlag1 )
  {
    p_m_offsetx = (int *)&this->stp_Equip.m_offsetx;
  }
  else
  {
    (((PalScript *)&this->stp_Equip.m_offsetx))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoSword.tga", g_bDebugMode);
    p_m_offsetx = (int *)&this->stp_Equip.m_offsetx;
  }
  sub_445E50((int)p_m_offsetx);
  if ( g_bRoleFlag2 )
    (((PalScript *)&this->stp_Prop.m_offsetx))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\UnJusticeBook.tga", g_bDebugMode);
  else
    (((PalScript *)&this->stp_Prop.m_offsetx))->PalScript::OpenScript("UI\\GameMainUI\\Communal\\StpCtl\\NoJusticeBook.tga", g_bDebugMode);
  sub_445E50((int)&this->stp_Prop.m_offsetx);
  sub_445E50((int)&this->m_OutFrameL.m_ppic);
  sub_445E50((int)&this->stp_BarL.m_FVF);
  sub_445E50((int)&this->stp_State.m_offsetx);
  sub_445E50((int)&this->stp_Magic.m_offsetx);
  sub_445E50((int)&this->stp_BattleArray.m_offsetx);
  sub_445E50((int)&this->stp_TaskBook.m_offsetx);
  return sub_445E50((int)&this->stp_System.m_offsetx);
}

// 0x00482ED0
int LineupUI::Save()
{
  StateUI **v2; // edi
  int v4; // [esp+0x10] [ebp-0x14]

  ((UIListBox *)this)->UIListBox::UIListBox();
  this->bkWndX = 800;
  this->bkWndY = 600;
  this->m_IsMsg = 0;
  (((UIFrameContainer *)&this->m_Frame))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)(&this->m_Frame + 1)))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_TimeMoney.m_FVF))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_OutFrameT.m_pbk2))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_OutFrameR.m_disablepic))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_OutFrameL.m_ppic))->UIFrameContainer::ResetContainerState();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  NameSys::GetSys();
  (((UIFrameContainer *)&this->stp_Exit.m_caption[44]))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->stp_Effect.m_benable))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_GameTime.m_childs))->UIFrameContainer::ResetContainerState();
  (((UIFrameContainer *)&this->m_GameMoney.m_rect.bottom))->UIFrameContainer::ResetContainerState();
  memset(&this->m_CtrlPlank[11].m_Btn[120], 0, 0x1Cu);
  *(_WORD *)&this->m_CtrlPlank[11].m_Btn[148] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[150] = 117901063;
  this->m_CtrlPlank[11].m_Btn[154] = 7;
  (((UIFrameContainer *)&this->m_CtrlPlank[11].m_Btn[172]))->UIFrameContainer::ResetContainerState();
  *((_DWORD *)&this->pStateUI + 175) = 0;
  ((UIRoleDialog *)(&this->pStateUI + 176))->UIRoleDialog::UIRoleDialog();
  v2 = (StateUI **)(&this->pStateUI + 526);
  v4 = 6;
  do
  {
    v2 += 3;
    --v4;
  }
  while ( v4 );
  (((ObjectCamera *)(&this->pStateUI + 544)))->ObjectCamera::Update();
  *((_DWORD *)&this->pStateUI + 3438) = 0;
  this->m_Is[4] = 0;
  this->m_Is[3] = 0;
  this->m_Is[1] = 0;
  this->m_Is[0] = 0;
  this->m_Is[2] = 0;
  memset(&this->m_CtrlPlank[11].m_Btn[120], 0, 0x1Cu);
  *(_WORD *)&this->m_CtrlPlank[11].m_Btn[148] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[150] = 0;
  this->m_CtrlPlank[11].m_Btn[154] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[108] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[112] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[116] = 0;
  *((_DWORD *)&this->pStateUI + 518) = -1038614528;
  *((_DWORD *)&this->pStateUI + 519) = 1072064102;
  *((_DWORD *)&this->pStateUI + 521) = 1094713344;
  *((_DWORD *)&this->pStateUI + 520) = 0;
  return (int)this;
}

// 0x00483650
void * LineupUI::CreatePreviewScene(int nVal)
{
  tagRECT *p_rc; // edi
  int v4; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int m_FVF; // edx
  int v9; // ecx
  char *m_pData; // eax
  int m_benable; // edx
  int v12; // edx
  int v13; // eax
  int v14; // edx
  StateUI **v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  StateUI **v20; // ebp
  UIPushButton *v21; // edi
  int v22; // ebx
  int v23; // ecx
  int v24; // ecx
  int v25; // ebx
  UIPushButton *v26; // edi
  gbTexture **p_pDebugTex; // ebp
  int v28; // ecx
  int i; // edi
  LONG bottom; // eax
  int v31; // edx
  ObjectCamera *v32; // eax
  float *v33; // eax
  float *v34; // ebp
  char *v35; // edi
  float v36; // st7
  bool v37; // cc
  Object3D *v38; // edi
  int v39; // ebx
  int v40; // edx
  int v41; // eax
  int v42; // ecx
  int v43; // edx
  gbVec3D v45; // [esp+0x6C] [ebp-A4h]
  int v46; // [esp+0x8C] [ebp-0x84]
  char *pszName; // [esp+0x90] [ebp-0x80]
  char *pszNamea; // [esp+0x90] [ebp-0x80]
  float v49; // [esp+0x98] [ebp-0x78]
  float v50; // [esp+0x98] [ebp-0x78]
  float v51; // [esp+0x98] [ebp-0x78]
  float v52; // [esp+0x98] [ebp-0x78]
  float v53; // [esp+0x98] [ebp-0x78]
  float v54; // [esp+0x98] [ebp-0x78]
  int v55; // [esp+C4h] [ebp-0x4C] BYREF
  int v56; // [esp+C8h] [ebp-0x48]
  int v57; // [esp+CCh] [ebp-0x44]
  int v58; // [esp+D0h] [ebp-0x40]
  int v59; // [esp+D4h] [ebp-0x3C] BYREF
  int v60; // [esp+D8h] [ebp-0x38]
  int v61; // [esp+DCh] [ebp-0x34]
  int v62; // [esp+E0h] [ebp-0x30]
  _DWORD v63[8]; // [esp+E4h] [ebp-0x2C] BYREF
  int v64; // [esp+0x10C] [ebp-0x4]

  p_rc = (tagRECT *)&this->rc;
  this->rc.top = 0;
  this->rc.left = 0;
  this->rc.right = this->bkWndX;
  this->rc.bottom = this->bkWndY;
  (((UIListBox *)this))->UIListBox::SetSelTexture(-1, this->rc.left, this->rc.top, this->rc.right, this->rc.bottom) /* [ROWTABLE] */;
  v4 = this->rc.top + 18;
  v59 = (unsigned long)(p_rc->left + 631);
  v60 = v4;
  v61 = v59 + 153;
  v62 = v4 + 526;
  (*(void ( **)(UIStatic *, int *, int *, LineupUI *))(*(_DWORD *)((UIWnd *)&this->m_Frame) + 16))(
    &this->m_Frame,
    &byte_1234567,
    &v59,
    this);
  LOBYTE(v5) = g_bDebugMode;
  (((UIPushButton *)&this->m_Frame))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Lineup\\Frame.tga", v5);
  v6 = *((_DWORD *)&this->m_Frame + 38);
  v60 += 26;
  v59 = v61;
  v62 = v60 + 526;
  v61 += 17;
  (*(void ( **)(UIStatic *, int, int *, LineupUI *))(v6 + 16))(&this->m_Frame + 1, 161, &v59, this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)(&this->m_Frame + 1)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Frame_Line.tga", v7);
  v56 = 0;
  v55 = v61 - 205;
  v57 = v61 - 205 + 203;
  m_FVF = this->m_TimeMoney.m_FVF;
  v58 = 64;
  (*(void ( **)(int *, int, int *, LineupUI *))(m_FVF + 16))(
    &this->m_TimeMoney.m_FVF,
    161,
    &v55,
    this);
  LOBYTE(v9) = g_bDebugMode;
  (((UIPushButton *)&this->m_TimeMoney.m_FVF))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\TimeMoney.tga", v9);
  m_pData = this->m_GameTime.m_childs.m_pData;
  v56 = -4;
  v55 = 618;
  v57 = 738;
  v58 = 28;
  (*((void ( **)(PtrArray *, int, int *, LineupUI *))m_pData + 4))(
    &this->m_GameTime.m_childs,
    161,
    &v55,
    this);
  (((UIScene *)&this->m_GameTime.m_childs))->UIScene::SetShow(0);
  AllocObject(&this->m_GameTime.m_childs);
  m_benable = this->stp_Effect.m_benable;
  v56 = 16;
  v55 = 668;
  v57 = 748;
  v58 = 48;
  (*(void ( **)(int *, int, int *, LineupUI *))(m_benable + 16))(
    &this->stp_Effect.m_benable,
    161,
    &v55,
    this);
  (((UIScene *)&this->stp_Effect.m_benable))->UIScene::SetShow(0);
  AllocObject(&this->stp_Effect.m_benable);
  this->LineupUI::RebuildNavPage();
  v12 = *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[172];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[160] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[156] = 0;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[164] = 488;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[168] = 110;
  v13 = (*(int ( **)(char *, int *, char *, LineupUI *))(v12 + 16))(
          &this->m_CtrlPlank[11].m_Btn[172],
          &byte_A00001,
          &this->m_CtrlPlank[11].m_Btn[156],
          this);
  LOBYTE(v13) = g_bDebugMode;
  (((UIPushButton *)&this->m_CtrlPlank[11].m_Btn[172]))->UIPushButton::CreateFromTemplate((void *)off_5C641C, v13);
  v14 = 5;
  v15 = (StateUI **)(&this->pStateUI + 156);
  do
  {
    *v15 = (StateUI *)24;
    v15 += 4;
    --v14;
  }
  while ( v14 );
  v16 = *((_DWORD *)&this->pStateUI + 156);
  v17 = *((_DWORD *)&this->pStateUI + 164);
  *((_DWORD *)&this->pStateUI + 162) = *((_DWORD *)&this->pStateUI + 160) + 57;
  *((_DWORD *)&this->pStateUI + 158) = v16 + 57;
  v18 = *((_DWORD *)&this->pStateUI + 168);
  *((_DWORD *)&this->pStateUI + 169) = 351;
  *((_DWORD *)&this->pStateUI + 173) = 351;
  v19 = *((_DWORD *)&this->pStateUI + 172);
  v20 = (StateUI **)(&this->pStateUI + 155);
  *((_DWORD *)&this->pStateUI + 166) = v17 + 57;
  *((_DWORD *)&this->pStateUI + 155) = 50;
  *((_DWORD *)&this->pStateUI + 157) = 105;
  *((_DWORD *)&this->pStateUI + 159) = 136;
  *((_DWORD *)&this->pStateUI + 161) = 191;
  *((_DWORD *)&this->pStateUI + 163) = 216;
  *((_DWORD *)&this->pStateUI + 165) = 271;
  *((_DWORD *)&this->pStateUI + 167) = 296;
  *((_DWORD *)&this->pStateUI + 170) = v18 + 57;
  *((_DWORD *)&this->pStateUI + 171) = 296;
  *((_DWORD *)&this->pStateUI + 174) = v19 + 57;
  v21 = (UIPushButton *)&this->m_ProtectPanel.m_WHFace.m_caption[40];
  v22 = 5;
  do
  {
    (*(void ( **)(UIPushButton *, int *, StateUI **, LineupUI *))(*(_DWORD *)((UIWnd *)v21) + 16))(
      v21,
      &byte_A00001,
      v20,
      this);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v21))((UIPushButton *)(v21), (_DWORD)(0));
    LOBYTE(v23) = g_bDebugMode;
    (((UIPushButton *)v21))->UIPushButton::CreateFromTemplate((void *)off_5C6420, v23);
    v20 += 4;
    v21 = (UIPushButton *)((char *)v21 + 152);
    --v22;
  }
  while ( v22 );
  v25 = 0;
  v26 = (UIPushButton *)((char *)&this->m_ProtectPanel.m_WPXFace + 668);
  p_pDebugTex = (gbTexture **)&this->m_CtrlPlank[12].m_Up.pDebugTex;
  pszName = (char *)(&this->pStateUI + 155);
  v46 = 0;
  do
  {
    LOBYTE(v24) = g_bDebugMode;
    ((void ( *)(gbTexture **, const char *, char *, LineupUI *, char *, int, int))(*p_pDebugTex)->Height)(
      p_pDebugTex,
      (&off_56B97C)[v25],
      pszName,
      this,
      &"UI\\GameMainUI\\Lineup\\Head0"[v46],
      1,
      v24);
    ((void ( *)(gbTexture **, _DWORD))((gbRefObject *)(*p_pDebugTex)))(p_pDebugTex, 0);
    (*(void ( **)(UIPushButton *, const char *, StateUI **, LineupUI *))(*(_DWORD *)((UIWnd *)v26) + 16))(
      v26,
      (&off_56BA08)[v25],
      &this->pStateUI + 155,
      this);
    LOBYTE(v28) = g_bDebugMode;
    (((UIPushButton *)v26))->UIPushButton::CreateFromTemplate(&"UI\\GameMainUI\\Lineup\\jingtian_lead.tga"[v46], v28);
    (**(void ( ***)(UIPushButton *, _DWORD))((UIWnd *)v26))((UIPushButton *)(v26), (_DWORD)(0));
    ++v25;
    p_pDebugTex += 86;
    pszName += 16;
    v26 = (UIPushButton *)((char *)v26 + 152);
    v46 += 256;
  }
  while ( v25 < 5 );
  for ( i = 0; i < 5; ++i )
    (((LineupComp *)this))->LineupComp::ShowById(i);
  bottom = this->m_GameMoney.m_rect.bottom;
  v63[1] = 95;
  v63[0] = 100;
  v63[2] = 142;
  v63[3] = 318;
  (*(void ( **)(LONG *, int *, _DWORD *, LineupUI *))(bottom + 16))(
    &this->m_GameMoney.m_rect.bottom,
    &byte_A00001,
    (_DWORD *)(v63),
    this);
  LOBYTE(v31) = g_bDebugMode;
  (((UIPushButton *)&this->m_GameMoney.m_rect.bottom))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Lineup\\zhenlie.tga", v31);
  *((_DWORD *)&this->pStateUI + 3438) = nVal;
  v32 = (ObjectCamera *)operator new(0x7Cu);
  v64 = 0;
  if ( v32 )
    v33 = (((ObjectCamera *)v32))->ObjectCamera::Create();
  else
    v33 = 0;
  *((_DWORD *)&this->pStateUI + 520) = (unsigned long)v33;
  v64 = -1;
  (((ObjectCamera *)v33))->ObjectCamera::SetCameraEyePosition(gfxMgr);
  v45.x = 0.0f;
  *(_QWORD *)&v45.y = 0x43C8000042480000i64;
  (((ObjectCamera *)*((ObjectCamera **)&this->pStateUI + 520)))->ObjectCamera::SetCameraAtPosition(v45, 1);
  (((ObjectCamera *)*((ObjectCamera **)&this->pStateUI + 520)))->ObjectCamera::SetCameraDist(0, *((_DWORD *)&this->pStateUI + 518), 1078774989);
  (((Object3D *)(&this->pStateUI + 544)))->Object3D::_todo_0047CB90("ui\\GameMainUI\\Lineup\\wl.pol", 0);
  (((Object3D *)(&this->pStateUI + 544)))->Object3D::VecAngle(-30.0, 30.0, 0.0);
  v34 = (float *)(&this->pStateUI + 552);
  *((_DWORD *)&this->pStateUI + 565) = *((_DWORD *)&this->pStateUI + 520);
  pszNamea = (char *)&g_RoleSlotBuf.dword_17AA450 + 774;
  *((float *)&this->pStateUI + 578) = *((float *)&this->pStateUI + 519);
  *((_DWORD *)&this->pStateUI + 580) = 1;
  v35 = (char *)&this->pStateUI + 2349;
  do
  {
    (((Object3D *)(v35 - 21)))->Object3D::_todo_0047CB90(pszNamea, 16);
    v35[59] = 0;
    *v35 = 0;
    (((Object3D *)(v35 - 21)))->Object3D::VecAngle(*v34, *((float *)&this->pStateUI + 553), *((float *)&this->pStateUI + 554));
    (((Object3D *)(v35 - 21)))->Object3D::SetObjectPosition(*v34, *((float *)&this->pStateUI + 553), *((float *)&this->pStateUI + 554));
    *(_DWORD *)(v35 + 63) = *((_DWORD *)&this->pStateUI + 520);
    *(float *)(v35 + 115) = *((float *)&this->pStateUI + 519);
    v35[99] = 1;
    (((Object3D *)(v35 - 21)))->Object3D::LoadObject("ui\\GameMainUI\\Lineup\\pointer.cvd", 0);
    v36 = *(float *)(v35 + 7);
    v35 += 152;
    v37 = (int)(pszNamea + 8704) < (int)byte_C10A0E;
    pszNamea += 8704;
    *(float *)(v35 - 149) = v36 + *((float *)&this->pStateUI + 521);
  }
  while ( v37 );
  v38 = (Object3D *)(&this->pStateUI + 780);
  v39 = 6;
  v49 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 526) = -1041235968;
  *((float *)&this->pStateUI + 527) = v49;
  *((_DWORD *)&this->pStateUI + 528) = -1033895936;
  v50 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 529) = 1103626240;
  *((float *)&this->pStateUI + 530) = v50;
  *((_DWORD *)&this->pStateUI + 531) = -1047527424;
  v51 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 532) = 1082130432;
  *((float *)&this->pStateUI + 533) = v51;
  *((_DWORD *)&this->pStateUI + 534) = 1109917696;
  v52 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 535) = -1031667712;
  *((float *)&this->pStateUI + 536) = v52;
  *((_DWORD *)&this->pStateUI + 537) = 1109917696;
  v53 = *((float *)&this->pStateUI + 553);
  *((_DWORD *)&this->pStateUI + 538) = -1029701632;
  *((float *)&this->pStateUI + 539) = v53;
  *((_DWORD *)&this->pStateUI + 540) = -1046478848;
  v40 = *((_DWORD *)&this->pStateUI + 553);
  v41 = *((_DWORD *)&this->pStateUI + 554);
  *((float *)&this->pStateUI + 541) = *v34;
  *((_DWORD *)&this->pStateUI + 542) = v40;
  *((_DWORD *)&this->pStateUI + 543) = v41;
  do
  {
    (((Object3D *)v38))->Object3D::_todo_0047CB90("ui\\GameMainUI\\Lineup\\pointer.cvd", 0);
    v38->m_visible = 0;
    v38->m_showSubObj = 0;
    v54 = *((float *)&this->pStateUI + 553) + *((float *)&this->pStateUI + 521);
    (((Object3D *)v38))->Object3D::SetObjectPosition(*v34, v54, *((float *)&this->pStateUI + 554));
    v38->m_pCamera = (ObjectCamera *)*((_DWORD *)&this->pStateUI + 520);
    ++v38;
    v38[-1].m_rotDstSpeed = *((float *)&this->pStateUI + 519);
    v38[-1].m_isActionRelativeRot = 1;
    --v39;
  }
  while ( v39 );
  v63[5] = 200;
  v63[4] = 300;
  v63[6] = 500;
  v63[7] = 300;
  Create__ovl_1((ARC_PlayerAtt *)(&this->pStateUI + 176));
  v42 = *((_DWORD *)&this->pStateUI + 196);
  v43 = *((_DWORD *)&this->pStateUI + 198);
  *((_DWORD *)&this->pStateUI + 201) = *((_DWORD *)&this->pStateUI + 197) + 14;
  *((_DWORD *)&this->pStateUI + 200) = v42 + 6;
  *((_DWORD *)&this->pStateUI + 203) = *((_DWORD *)&this->pStateUI + 199) - 38;
  *((_DWORD *)&this->pStateUI + 512) = 0;
  *((_DWORD *)&this->pStateUI + 513) = 8;
  *((_DWORD *)&this->pStateUI + 202) = v43 - 6;
  (((UIWnd *)(&this->pStateUI + 290)))->UIWnd::sub_445FA0(&this->pStateUI + 200);
  return (((UIItem *)(&this->pStateUI + 176)))->UIItem::SetData(31);
}

// 0x00484360
int LineupUI::GetSlotRect(int nVal, unsigned int dwVal)
{
  int v3; // ebp
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  char *v9; // ebp
  scAsmDecoder *v10; // ecx
  int result; // eax
  int v12; // [esp-0x8] [ebp-0x10]
  gbTexture **nVala; // [esp+0xC] [ebp+0x4]

  if ( (unsigned int)nVal <= 4 )
  {
    v12 = v3;
    (((UIWnd *)(&this->m_CtrlPlank[12].m_Up.pDebugTex + 86 * nVal)))->UIWnd::sub_445FA0(&this->pStateUI + 155);
    (((UIWnd *)(&this->m_CtrlPlank[12].m_Up.pDebugTex + 86 * *((_DWORD *)&this->pStateUI + 175))))->UIWnd::sub_445FA0(&this->pStateUI + 4 * *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * nVal + 20] + 155);
    v6 = *((_DWORD *)&this->pStateUI + 175);
    *((_DWORD *)&this->pStateUI + 175) = nVal;
    v7 = *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * nVal + 20];
    v8 = 0;
    v9 = (char *)&this->m_ProtectPanel.m_WPXFace + 668;
    *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * nVal + 20] = *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * v6 + 20];
    *(_DWORD *)&this->m_ProtectPanel.m_WHFace.m_caption[4 * v6 + 20] = v7;
    nVala = (gbTexture **)&this->m_CtrlPlank[12].m_Up.pDebugTex;
    do
    {
      if ( this->m_Is[v8] )
      {
        (**(void ( ***)(char *, _DWORD))v9)((char *)(v9), (_DWORD)(0));
        ((void ( *)(gbTexture **, int))((gbRefObject *)(*nVala)))(nVala, 1);
      }
      ++v8;
      v9 += 152;
      nVala += 86;
    }
    while ( v8 < 5 );
    (**((void ( ***)(char *, int, int))&this->m_ProtectPanel.m_WPXFace
      + 38 * *((_DWORD *)&this->pStateUI + 175)
      + 167))((char *)((char *)&this->m_ProtectPanel.m_WPXFace + 152 * *((_DWORD *)&this->pStateUI + 175) + 668), (int)(1), (int)(v12));
    (**((void ( ***)(gbTexture **, _DWORD))&this->m_CtrlPlank[12].m_Up.pDebugTex
      + 86 * *((_DWORD *)&this->pStateUI + 175)))((gbTexture **)(&this->m_CtrlPlank[12].m_Up.pDebugTex + 86 * *((_DWORD *)&this->pStateUI + 175)), (_DWORD)(0));
    return (((scAsmDecoder *)v10))->scAsmDecoder::Execute(nVal, 1);
  }
  return result;
}

// 0x00484810
int LineupUI::RebuildNavPage()
{
  gbTexture *m_pbk2; // eax
  gbTexture **p_m_pbk2; // edi
  int v4; // edx
  gbTexture *m_disablepic; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int m_bcreateok; // eax
  int m_bvisible; // edx
  int v13; // ecx
  int m_nSize; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // eax
  int v24; // ecx
  int v25; // edx
  int v26; // eax
  int v27; // edx
  int v28; // ecx
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // eax
  int v33; // edx
  int v34; // edx
  int v35; // eax
  int m_needscriptdel; // ecx
  int v37; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v40; // ecx
  int v41; // eax
  _DWORD v43[2]; // [esp+0x74] [ebp-0x20] BYREF
  int v44; // [esp+0x7C] [ebp-0x18]
  int v45; // [esp+0x80] [ebp-0x14]
  _DWORD v46[4]; // [esp+0x84] [ebp-0x10] BYREF

  m_pbk2 = (gbTexture *)this->m_OutFrameT.m_pbk2;
  p_m_pbk2 = (gbTexture **)&this->m_OutFrameT.m_pbk2;
  v43[1] = 543;
  v43[0] = 0;
  v44 = 256;
  v45 = 600;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2->IsLoaded)(
    &this->m_OutFrameT.m_pbk2,
    161,
    v43,
    this);
  LOBYTE(v4) = g_bDebugMode;
  (((UIPushButton *)p_m_pbk2))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v4);
  m_disablepic = (gbTexture *)this->m_OutFrameR.m_disablepic;
  v43[0] = v44;
  v44 += 512;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))m_disablepic->IsLoaded)(
    &this->m_OutFrameR.m_disablepic,
    161,
    v43,
    this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameR.m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v6);
  v43[0] = v44;
  v44 += 32;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))this->m_OutFrameL.m_ppic->IsLoaded)(
    &this->m_OutFrameL.m_ppic,
    161,
    v43,
    this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameL.m_ppic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v7);
  this->stp_Effect.m_childs.m_needscriptdel = 546;
  this->stp_Effect.m_childs.m_nSize = 38;
  this->stp_Effect.m_bcreateok = 148;
  this->stp_Effect.m_bvisible = this->stp_Effect.m_childs.m_needscriptdel + 50;
  LOBYTE(v8) = g_bDebugMode;
  ((void ( *)(gbTexture **, int *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_pbk->Height)(
    &this->m_OutFrameB.m_pbk,
    &byte_A00102,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v8);
  this->m_CtrlPlank[11].m_Dw.m_pbk2 = (gbTexture *)(this->stp_Effect.m_childs.m_needscriptdel + 5);
  this->m_CtrlPlank[11].m_Dw.m_disablepicInfo = (_PlugInfo *)(this->stp_Effect.m_childs.m_nSize + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_mouseoff = this->stp_Effect.m_bcreateok - 36;
  this->m_CtrlPlank[11].m_Dw.m_FVF = this->stp_Effect.m_bvisible - 5;
  v9 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v9;
  v9 += 110;
  this->stp_Effect.m_bcreateok = v9;
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[44]
                                                                                          + 28))(
    &byte_A00105,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v9);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[32] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[28] = this->stp_Effect.m_childs.m_nSize + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[36] = this->stp_Effect.m_bcreateok - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[40] = this->stp_Effect.m_bvisible - 5;
  v10 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v10;
  v10 += 110;
  this->stp_Effect.m_bcreateok = v10;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[44]
                                                                                          + 28))(
    &byte_A00104,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v10);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[16] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[12] = this->stp_Effect.m_childs.m_nSize + 35;
  m_bcreateok = this->stp_Effect.m_bcreateok;
  m_bvisible = this->stp_Effect.m_bvisible;
  v13 = m_bcreateok - 36;
  m_bcreateok -= 22;
  this->stp_Effect.m_childs.m_nSize = m_bcreateok;
  m_bvisible -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[20] = v13;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[24] = m_bvisible;
  this->stp_Effect.m_bcreateok = m_bcreateok + 110;
  LOBYTE(m_bvisible) = g_bDebugMode;
  (*(void ( **)(int *, int *, int *, LineupUI *, char *, int, int))(this->stp_BarR.m_bcreateok + 28))(
    &this->stp_BarR.m_bcreateok,
    &byte_A00103,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    m_bvisible);
  m_nSize = this->stp_Effect.m_childs.m_nSize;
  *(_DWORD *)this->m_CtrlPlank[11].m_Btn = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v15 = this->stp_Effect.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_nTextW = m_nSize + 35;
  v16 = this->stp_Effect.m_bvisible;
  v17 = v15 - 36;
  v15 -= 22;
  this->stp_Effect.m_childs.m_nSize = v15;
  this->stp_Effect.m_bcreateok = v15 + 110;
  v18 = this->stp_Effect.m_childs.m_nSize - 38;
  v46[1] = 546;
  v46[0] = v18;
  v46[2] = v18 + 256;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[4] = v17;
  v19 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[8] = v16 - 5;
  v46[3] = 610;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v19 + 16))(&this->stp_Exit.m_caption[44], 161, (_DWORD *)(v46), this);
  LOBYTE(v20) = g_bDebugMode;
  (((UIPushButton *)&this->stp_Exit.m_caption[44]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v20);
  LOBYTE(v21) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_BattleArray.m_caption[44]
                                                                                        + 28))(
    &this->stp_BattleArray.m_caption[44],
    &byte_A00108,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v21);
  v22 = this->stp_Effect.m_childs.m_nSize + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[48] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v23 = this->stp_Effect.m_bcreateok;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[44] = v22;
  v24 = this->stp_Effect.m_bvisible;
  v25 = v23 - 36;
  v23 -= 22;
  this->stp_Effect.m_childs.m_nSize = v23;
  v23 += 110;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[52] = v25;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[56] = v24 - 5;
  this->stp_Effect.m_bcreateok = v23;
  LOBYTE(v23) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_caption[44] + 28))(
    &this->stp_Equip.m_caption[44],
    &byte_A00106,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v23);
  v26 = this->stp_Effect.m_bcreateok;
  v27 = this->stp_Effect.m_childs.m_nSize + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[64] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[60] = v27;
  v28 = v26 - 36;
  v29 = this->stp_Effect.m_bvisible;
  v26 -= 22;
  this->stp_Effect.m_childs.m_nSize = v26;
  v29 -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[68] = v28;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[72] = v29;
  this->stp_Effect.m_bcreateok = v26 + 110;
  LOBYTE(v29) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Prop.m_caption[44] + 28))(
    &this->stp_Prop.m_caption[44],
    &byte_A00107,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v29);
  v30 = this->stp_Effect.m_childs.m_nSize;
  v31 = this->stp_Effect.m_bcreateok;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[80] = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v32 = this->stp_Effect.m_bvisible - 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[76] = v30 + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[84] = v31 - 36;
  v33 = *(_DWORD *)&this->stp_System.m_caption[44];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[88] = v32;
  LOBYTE(v32) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v33 + 28))(
    &this->stp_System.m_caption[44],
    &byte_A00110,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v32);
  v34 = *(_DWORD *)&this->stp_TaskBook.m_caption[44];
  v35 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v35;
  v35 += 110;
  this->stp_Effect.m_bcreateok = v35;
  LOBYTE(v35) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v34 + 28))(
    &this->stp_TaskBook.m_caption[44],
    &byte_A00109,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v35);
  m_needscriptdel = this->stp_Effect.m_childs.m_needscriptdel;
  v37 = this->stp_Effect.m_bcreateok - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[92] = this->stp_Effect.m_childs.m_nSize + 35;
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[100] = v37;
  bkWndX = this->bkWndX;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[96] = m_needscriptdel + 5;
  v40 = this->stp_Effect.m_bvisible;
  bkWndX -= 38;
  this->stp_Effect.m_childs.m_needscriptdel = bkWndY - 51;
  this->stp_Effect.m_childs.m_nSize = bkWndX;
  this->stp_Effect.m_bcreateok = bkWndX + 38;
  v41 = this->stp_Effect.m_childs.m_needscriptdel;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[104] = v40 - 5;
  this->stp_Effect.m_bvisible = v41 + 48;
  return (((UIWnd *)&this->stp_System.m_caption[44]))->UIWnd::sub_445FA0(&this->stp_Effect.m_childs.m_nSize);
}

// 0x00488DE0
void LineupUI::LoadRoleData()
{
  int v0; // ecx
  int v1; // esi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  float fValue; // [esp+0x0] [ebp-0x1C]
  float fValuea; // [esp+0x0] [ebp-0x1C]
  float fValueb; // [esp+0x0] [ebp-0x1C]
  float fValuec; // [esp+0x0] [ebp-0x1C]
  float fValued; // [esp+0x0] [ebp-0x1C]
  float fValuee; // [esp+0x0] [ebp-0x1C]

  v1 = v0;
  *(_DWORD *)(v0 + 96) = 0;
  do
  {
    v2 = *(_DWORD *)(v1 + 96);
    if ( *(_BYTE *)(v2 + v1 + 877) )
    {
      (((RoleSystem *)((char *)&g_RoleSlotBuf + 1408 * v2)))->RoleSystem::RecalcAggregatedStats(0);
      v3 = *(_DWORD *)(v1 + 96);
      fValue = (float)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * v3);
      (((UIScrollBar *)(4892 * v3 + v1 + 213400)))->UIScrollBar::SetRange(fValue);
      v4 = *(_DWORD *)(v1 + 96);
      fValuea = (float)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * v4 + 1);
      (((UIScrollBar *)(4892 * v4 + v1 + 214496)))->UIScrollBar::SetRange(fValuea);
      v5 = *(_DWORD *)(v1 + 96);
      fValueb = (float)*((int *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * v5 + 2);
      (((UIScrollBar *)(4892 * v5 + v1 + 213948)))->UIScrollBar::SetRange(fValueb);
      v6 = *(_DWORD *)(v1 + 96);
      fValuec = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * v6 + 2];
      (((UIProgressBar *)(4892 * v6 + v1 + 213400)))->UIProgressBar::FindChildByName(fValuec);
      v7 = *(_DWORD *)(v1 + 96);
      fValued = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * v7 + 3];
      (((UIProgressBar *)(4892 * v7 + v1 + 214496)))->UIProgressBar::FindChildByName(fValued);
      v8 = *(_DWORD *)(v1 + 96);
      fValuee = (float)(int)g_RoleSlotBuf.m_partyActor.m_dwMatMsg[352 * v8 + 4];
      (((UIProgressBar *)(4892 * v8 + v1 + 213948)))->UIProgressBar::FindChildByName(fValuee);
      sprintf(
        (char *const)(v1 + 104),
        "%d/%d",
        (int)*(float *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 213556),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)(v1 + 96)));
      SetEnable((UICaption *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 213644));
      sprintf(
        (char *const)(v1 + 104),
        "%d/%d",
        (int)*(float *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214652),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)(v1 + 96) + 1));
      SetEnable((UICaption *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214740));
      sprintf(
        (char *const)(v1 + 104),
        "%d/%d",
        (int)*(float *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214104),
        *((_DWORD *)&g_RoleSlotBuf.m_partyActor.m_nAnimFrame + 352 * *(_DWORD *)(v1 + 96) + 2));
      SetEnable((UICaption *)(4892 * *(_DWORD *)(v1 + 96) + v1 + 214192));
    }
    v9 = *(_DWORD *)(v1 + 96) + 1;
    *(_DWORD *)(v1 + 96) = v9;
  }
  while ( v9 < 5 );
}

// 0x00491630
int LineupUI::RebuildExitPage()
{
  int v2; // eax
  UIPushButton *v3; // edi
  int v4; // edx
  int m_FVF; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  gbTexture *v9; // eax
  int m_bfocus; // ecx
  unsigned int *p_r_mask; // eax
  char *v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  gbTexture *pDebugTex; // eax
  char *v17; // edx
  int m_align; // ecx
  int m_benable; // edx
  gbTexture *v20; // eax
  LONG v21; // ecx
  LONG v22; // edx
  int v23; // ecx
  gbTexture *v24; // eax
  int v25; // ecx
  gbTexture *v26; // edx
  gbTexture *v27; // eax
  float v28; // edx
  unsigned int *v29; // ecx
  char *v30; // edx
  int v31; // ecx
  gbTexture *v32; // edx
  int v33; // eax
  int v34; // edx
  int v35; // edx
  gbTexture *v36; // eax
  int v37; // ecx
  _PlugInfo *v38; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v41; // ecx
  int v42; // eax
  _DWORD v44[2]; // [esp+0x44] [ebp-0x20] BYREF
  int v45; // [esp+0x4C] [ebp-0x18]
  int v46; // [esp+0x50] [ebp-0x14]
  _DWORD v47[4]; // [esp+0x54] [ebp-0x10] BYREF

  v2 = *((_DWORD *)&this->m_OutFrameT + 38);
  v3 = (UIPushButton *)(&this->m_OutFrameT + 1);
  v44[1] = 543;
  v44[0] = 0;
  v45 = 256;
  v46 = 600;
  (*(void ( **)(UIStatic *, int, _DWORD *, LineupUI *))(v2 + 16))(&this->m_OutFrameT + 1, 161, (_DWORD *)(v44), this);
  LOBYTE(v4) = g_bDebugMode;
  (((UIPushButton *)v3))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v4);
  m_FVF = this->m_OutFrameR.m_FVF;
  v44[0] = v45;
  v45 += 512;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_FVF + 16))(
    &this->m_OutFrameR.m_FVF,
    161,
    (_DWORD *)(v44),
    this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameR.m_FVF))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v6);
  v44[0] = v45;
  v45 += 32;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))this->m_OutFrameL.m_pbk2->IsLoaded)(
    &this->m_OutFrameL.m_pbk2,
    161,
    v44,
    this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameL.m_pbk2))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v7);
  this->stp_Effect.m_bfocus = 546;
  this->stp_Effect.m_benable = 38;
  this->stp_Effect.pDebugTex = ((gbTexture *)((gbTexture *)148));
  this->stp_Effect.m_align = this->stp_Effect.m_bfocus + 50;
  LOBYTE(v8) = g_bDebugMode;
  ((void ( *)(gbTexture **, int *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_disablepic->Height)(
    &this->m_OutFrameB.m_disablepic,
    &byte_A00102,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v8);
  *(_DWORD *)((UIWnd *)&this->m_CtrlPlank[11].m_Dw) = this->stp_Effect.m_bfocus + 5;
  this->m_CtrlPlank[11].m_Name.m_nTextW = this->stp_Effect.m_benable + 35;
  this->m_CtrlPlank[11].m_Dw.m_fontcolor.Color = (unsigned int)&this->stp_Effect.pDebugTex[-1].InFmt.r_mask;
  this->m_CtrlPlank[11].m_Dw.m_wndcolor.Color = this->stp_Effect.m_align - 5;
  v9 = (gbTexture *)((char *)this->stp_Effect.pDebugTex - 22);
  this->stp_Effect.m_benable = (int)v9;
  v9 = (gbTexture *)((char *)v9 + 110);
  this->stp_Effect.pDebugTex = ((gbTexture *)(v9));
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(int *, int *, LineupUI *, char *, int, gbTexture *))(*(_DWORD *)&this->stp_Magic.m_caption[60]
                                                                                       + 28))(
    &byte_A00105,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v9);
  m_bfocus = this->stp_Effect.m_bfocus;
  v47[1] = 546;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_needscriptdel = m_bfocus + 5;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_nSize = this->stp_Effect.m_benable + 35;
  p_r_mask = (unsigned int *)&this->stp_Effect.pDebugTex[-1].InFmt.r_mask;
  v47[3] = 610;
  this->m_CtrlPlank[11].m_Dw.m_bcreateok = (int)p_r_mask;
  this->m_CtrlPlank[11].m_Dw.m_bvisible = this->stp_Effect.m_align - 5;
  v12 = (char *)&this->stp_Effect.pDebugTex[-1].InFmt.a_mask + 2;
  this->stp_Effect.m_benable = (int)v12;
  this->stp_Effect.pDebugTex = ((gbTexture *)((gbTexture *)(v12 + 110)));
  v13 = *(_DWORD *)&this->stp_Exit.m_caption[60];
  v47[0] = this->stp_Effect.m_benable - 38;
  v47[2] = v47[0] + 256;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v13 + 16))(&this->stp_Exit.m_caption[60], 161, (_DWORD *)(v47), this);
  LOBYTE(v14) = g_bDebugMode;
  (((UIPushButton *)&this->stp_Exit.m_caption[60]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v14);
  LOBYTE(v15) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[60]
                                                                                        + 28))(
    &this->stp_State.m_caption[60],
    &byte_A00104,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v15);
  this->m_CtrlPlank[11].m_Dw.m_pfather = (UIWnd *)(this->stp_Effect.m_bfocus + 5);
  pDebugTex = (gbTexture *)this->stp_Effect.pDebugTex;
  this->m_CtrlPlank[11].m_Dw.m_rect.bottom = this->stp_Effect.m_benable + 35;
  v17 = (char *)&pDebugTex[-1].InFmt.r_mask;
  m_align = this->stp_Effect.m_align;
  pDebugTex = (gbTexture *)((char *)pDebugTex - 22);
  this->stp_Effect.m_benable = (int)pDebugTex;
  pDebugTex = (gbTexture *)((char *)pDebugTex + 110);
  this->m_CtrlPlank[11].m_Dw.m_childs.m_pData = v17;
  this->m_CtrlPlank[11].m_Dw.m_childs.capacity = m_align - 5;
  this->stp_Effect.pDebugTex = ((gbTexture *)(pDebugTex));
  LOBYTE(pDebugTex) = g_bDebugMode;
  ((void ( *)(gbTexture **, int *, int *, LineupUI *, char *, int, gbTexture *))this->stp_BarR.pDebugTex->Height)(
    &this->stp_BarR.pDebugTex,
    &byte_A00103,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    pDebugTex);
  m_benable = this->stp_Effect.m_benable;
  v20 = (gbTexture *)this->stp_Effect.pDebugTex;
  this->m_CtrlPlank[11].m_Dw.m_rect.left = this->stp_Effect.m_bfocus + 5;
  v21 = (LONG)&v20[-1].InFmt.r_mask;
  this->m_CtrlPlank[11].m_Dw.m_id = m_benable + 35;
  v22 = this->stp_Effect.m_align;
  v20 = (gbTexture *)((char *)v20 - 22);
  this->stp_Effect.m_benable = (int)v20;
  v22 -= 5;
  this->m_CtrlPlank[11].m_Dw.m_rect.top = v21;
  this->m_CtrlPlank[11].m_Dw.m_rect.right = v22;
  this->stp_Effect.pDebugTex = ((gbTexture *)((gbTexture *)((char *)v20 + 110)));
  LOBYTE(v22) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, LONG))(*(_DWORD *)&this->stp_BattleArray.m_caption[60]
                                                                                         + 28))(
    &this->stp_BattleArray.m_caption[60],
    &byte_A00108,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v22);
  v23 = this->stp_Effect.m_benable + 35;
  this->m_CtrlPlank[11].m_Dw.m_bfocus = this->stp_Effect.m_bfocus + 5;
  v24 = (gbTexture *)this->stp_Effect.pDebugTex;
  this->m_CtrlPlank[11].m_Dw.m_benable = v23;
  v25 = this->stp_Effect.m_align;
  v26 = (gbTexture *)((char *)v24 - 36);
  v24 = (gbTexture *)((char *)v24 - 22);
  this->stp_Effect.m_benable = (int)v24;
  v24 = (gbTexture *)((char *)v24 + 110);
  this->m_CtrlPlank[11].m_Dw.pDebugTex = v26;
  this->m_CtrlPlank[11].m_Dw.m_align = v25 - 5;
  this->stp_Effect.pDebugTex = ((gbTexture *)(v24));
  LOBYTE(v24) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, gbTexture *))(*(_DWORD *)&this->stp_Equip.m_caption[60]
                                                                                                + 28))(
    &this->stp_Equip.m_caption[60],
    &byte_A00106,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v24);
  v27 = (gbTexture *)this->stp_Effect.pDebugTex;
  LODWORD(v28) = this->stp_Effect.m_benable + 35;
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratioh) = this->stp_Effect.m_bfocus + 5;
  this->m_CtrlPlank[11].m_Dw.m_ratiow = v28;
  v29 = (unsigned int *)&v27[-1].InFmt.r_mask;
  v30 = (char *)this->stp_Effect.m_align;
  v27 = (gbTexture *)((char *)v27 - 22);
  this->stp_Effect.m_benable = (int)v27;
  v30 -= 5;
  this->m_CtrlPlank[11].m_Dw.m_textx = v29;
  this->m_CtrlPlank[11].m_Dw.m_texty = v30;
  this->stp_Effect.pDebugTex = ((gbTexture *)((gbTexture *)((char *)v27 + 110)));
  LOBYTE(v30) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, char *))(*(_DWORD *)&this->stp_Prop.m_caption[60]
                                                                                           + 28))(
    &this->stp_Prop.m_caption[60],
    &byte_A00107,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v30);
  v31 = this->stp_Effect.m_benable;
  v32 = (gbTexture *)this->stp_Effect.pDebugTex;
  *(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_text = this->stp_Effect.m_bfocus + 5;
  v33 = this->stp_Effect.m_align - 5;
  this->m_CtrlPlank[11].m_Dw.m_fonttype = (Parent_Data *)(v31 + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[4] = (unsigned long)((char *)v32 - 36);
  v34 = *(_DWORD *)&this->stp_System.m_caption[60];
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[8] = v33;
  LOBYTE(v33) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v34 + 28))(
    &this->stp_System.m_caption[60],
    &byte_A00110,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v33);
  v35 = *(_DWORD *)&this->stp_TaskBook.m_caption[60];
  v36 = (gbTexture *)((char *)this->stp_Effect.pDebugTex - 22);
  this->stp_Effect.m_benable = (int)v36;
  v36 = (gbTexture *)((char *)v36 + 110);
  this->stp_Effect.pDebugTex = ((gbTexture *)(v36));
  LOBYTE(v36) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, gbTexture *))(v35 + 28))(
    &this->stp_TaskBook.m_caption[60],
    &byte_A00109,
    &this->stp_Effect.m_benable,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v36);
  v37 = this->stp_Effect.m_bfocus;
  v38 = (_PlugInfo *)&this->stp_Effect.pDebugTex[-1].InFmt.r_mask;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[12] = this->stp_Effect.m_benable + 35;
  bkWndY = this->bkWndY;
  this->m_CtrlPlank[11].m_Dw.m_pbkInfo = v38;
  bkWndX = this->bkWndX;
  this->m_CtrlPlank[11].m_Dw.m_pbk = (gbTexture *)(v37 + 5);
  v41 = this->stp_Effect.m_align;
  bkWndX -= 38;
  this->stp_Effect.m_bfocus = bkWndY - 51;
  this->stp_Effect.m_benable = bkWndX;
  this->stp_Effect.pDebugTex = ((gbTexture *)((gbTexture *)(bkWndX + 38)));
  v42 = this->stp_Effect.m_bfocus;
  this->m_CtrlPlank[11].m_Dw.m_ppic = (gbTexture *)(v41 - 5);
  this->stp_Effect.m_align = v42 + 48;
  return (((UIWnd *)&this->stp_System.m_caption[60]))->UIWnd::sub_445FA0(&this->stp_Effect.m_benable);
}

// 0x004993D0
int LineupUI::RebuildCaptionPage()
{
  int v2; // eax
  UIPushButton *v3; // edi
  int v4; // edx
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // edx
  unsigned int v10; // eax
  unsigned int Color; // edx
  int v12; // ecx
  int v13; // edx
  unsigned int v14; // eax
  unsigned int v15; // eax
  unsigned int v16; // ecx
  unsigned int m_id; // edx
  int v18; // ecx
  unsigned int v19; // eax
  unsigned int v20; // ecx
  unsigned int v21; // edx
  int v22; // edx
  unsigned int v23; // eax
  unsigned int v24; // ecx
  unsigned int v25; // edx
  int v26; // ecx
  unsigned int v27; // eax
  unsigned int v28; // edx
  unsigned int v29; // ecx
  int v30; // edx
  unsigned int v31; // eax
  unsigned int v32; // ecx
  int v33; // edx
  int v34; // edx
  unsigned int v35; // eax
  unsigned int v36; // ecx
  unsigned int v37; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  unsigned int v40; // ecx
  unsigned int v41; // eax
  _DWORD v43[2]; // [esp+0x2C] [ebp-0x20] BYREF
  int v44; // [esp+0x34] [ebp-0x18]
  int v45; // [esp+0x38] [ebp-0x14]
  _DWORD v46[4]; // [esp+0x3C] [ebp-0x10] BYREF

  v2 = *(_DWORD *)&this->m_OutFrameL.m_text[12];
  v3 = (UIPushButton *)&this->m_OutFrameL.m_text[12];
  v43[1] = 543;
  v43[0] = 0;
  v44 = 256;
  v45 = 600;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v2 + 16))(&this->m_OutFrameL.m_text[12], 161, (_DWORD *)(v43), this);
  LOBYTE(v4) = g_bDebugMode;
  (((UIPushButton *)v3))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v4);
  v5 = *(_DWORD *)&this->m_OutFrameB.m_text[4];
  v43[0] = v44;
  v44 += 512;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v5 + 16))(&this->m_OutFrameB.m_text[4], 161, (_DWORD *)(v43), this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameB.m_text[4]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v6);
  v43[0] = v44;
  v44 += 32;
  ((void ( *)(Parent_Data **, int, _DWORD *, LineupUI *))this->stp_BarL.m_fonttype[4])(
    &this->stp_BarL.m_fonttype,
    161,
    v43,
    this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)&this->stp_BarL.m_fonttype))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v7);
  this->m_GameMoney.m_fontcolor.Color = 546;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = 38;
  this->m_GameMoney.m_wndcolor.Color = 148;
  this->m_GameMoney.m_id = this->m_GameMoney.m_fontcolor.Color + 50;
  LOBYTE(v8) = g_bDebugMode;
  (*(void ( **)(UIStatic *, int *, UIStatic *, LineupUI *, char *, int, int))(*(_DWORD *)((UIWnd *)&this->stp_BarR)
                                                                                      + 28))(
    &this->stp_BarR,
    &byte_A00102,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v8);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[124] = this->m_GameMoney.m_fontcolor.Color + 5;
  v9 = *(_DWORD *)((UIWnd *)&this->m_GameMoney) + 35;
  v46[1] = 546;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[120] = v9;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[128] = this->m_GameMoney.m_wndcolor.Color - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[132] = this->m_GameMoney.m_id - 5;
  v10 = this->m_GameMoney.m_wndcolor.Color - 22;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = v10;
  this->m_GameMoney.m_wndcolor.Color = v10 + 110;
  Color = this->m_GameTime.m_wndcolor.Color;
  v46[0] = *(_DWORD *)((UIWnd *)&this->m_GameMoney) - 38;
  v46[2] = v46[0] + 256;
  v46[3] = 610;
  (*(void ( **)(gbColorQuad *, int, _DWORD *, LineupUI *))(Color + 16))(
    &this->m_GameTime.m_wndcolor,
    161,
    (_DWORD *)(v46),
    this);
  LOBYTE(v12) = g_bDebugMode;
  (((UIPushButton *)&this->m_GameTime.m_wndcolor))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v12);
  LOBYTE(v13) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_mouseoff
                                                                                   + 28))(
    &this->stp_Equip.m_mouseoff,
    &byte_A00105,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v13);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[172] = this->m_GameMoney.m_fontcolor.Color + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[168] = *(_DWORD *)((UIWnd *)&this->m_GameMoney) + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[176] = this->m_GameMoney.m_wndcolor.Color - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[180] = this->m_GameMoney.m_id - 5;
  v14 = this->m_GameMoney.m_wndcolor.Color - 22;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = v14;
  v14 += 110;
  this->m_GameMoney.m_wndcolor.Color = v14;
  LOBYTE(v14) = g_bDebugMode;
  (*(void ( **)(int *, UIStatic *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_Magic.m_mouseoff
                                                                                      + 28))(
    &byte_A00104,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v14);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[156] = this->m_GameMoney.m_fontcolor.Color + 5;
  v15 = this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[152] = *(_DWORD *)((UIWnd *)&this->m_GameMoney) + 35;
  v16 = v15 - 36;
  m_id = this->m_GameMoney.m_id;
  v15 -= 22;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = v15;
  m_id -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[160] = v16;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[164] = m_id;
  this->m_GameMoney.m_wndcolor.Color = v15 + 110;
  LOBYTE(m_id) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_State.m_mouseoff
                                                                                                + 28))(
    &this->stp_State.m_mouseoff,
    &byte_A00103,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    m_id);
  v18 = *(_DWORD *)((UIWnd *)&this->m_GameMoney) + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[140] = this->m_GameMoney.m_fontcolor.Color + 5;
  v19 = this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[136] = v18;
  v20 = this->m_GameMoney.m_id;
  v21 = v19 - 36;
  v19 -= 22;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = v19;
  v19 += 110;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[144] = v21;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[148] = v20 - 5;
  this->m_GameMoney.m_wndcolor.Color = v19;
  LOBYTE(v19) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_TaskBook.m_mouseoff
                                                                                                + 28))(
    &this->stp_TaskBook.m_mouseoff,
    &byte_A00108,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v19);
  v22 = (int)((UIWnd *)&this->m_GameMoney);
  v23 = this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[188] = this->m_GameMoney.m_fontcolor.Color + 5;
  v24 = v23 - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[184] = v22 + 35;
  v25 = this->m_GameMoney.m_id;
  v23 -= 22;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = v23;
  v25 -= 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[192] = v24;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[196] = v25;
  this->m_GameMoney.m_wndcolor.Color = v23 + 110;
  LOBYTE(v25) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_Prop.m_mouseoff
                                                                                                + 28))(
    &this->stp_Prop.m_mouseoff,
    &byte_A00106,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v25);
  v26 = *(_DWORD *)((UIWnd *)&this->m_GameMoney) + 35;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[204] = this->m_GameMoney.m_fontcolor.Color + 5;
  v27 = this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[200] = v26;
  v28 = v27 - 36;
  v29 = this->m_GameMoney.m_id;
  v27 -= 22;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = v27;
  v27 += 110;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[208] = v28;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[212] = v29 - 5;
  this->m_GameMoney.m_wndcolor.Color = v27;
  LOBYTE(v27) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_BattleArray.m_mouseoff
                                                                                                + 28))(
    &this->stp_BattleArray.m_mouseoff,
    &byte_A00107,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v27);
  v30 = (int)((UIWnd *)&this->m_GameMoney);
  v31 = this->m_GameMoney.m_wndcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[220] = this->m_GameMoney.m_fontcolor.Color + 5;
  v31 -= 36;
  v32 = this->m_GameMoney.m_id - 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[216] = v30 + 35;
  v33 = *(_DWORD *)&this->stp_Exit.m_mouseoff;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[224] = v31;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[228] = v32;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, unsigned int))(v33 + 28))(
    &this->stp_Exit.m_mouseoff,
    &byte_A00110,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v31);
  v34 = *(_DWORD *)&this->stp_System.m_mouseoff;
  v35 = this->m_GameMoney.m_wndcolor.Color - 22;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = v35;
  v35 += 110;
  this->m_GameMoney.m_wndcolor.Color = v35;
  LOBYTE(v35) = g_bDebugMode;
  (*(void ( **)(_BYTE *, int *, UIStatic *, LineupUI *, char *, int, unsigned int))(v34 + 28))(
    &this->stp_System.m_mouseoff,
    &byte_A00109,
    &this->m_GameMoney,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v35);
  v36 = this->m_GameMoney.m_fontcolor.Color;
  v37 = this->m_GameMoney.m_wndcolor.Color - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[232] = *(_DWORD *)((UIWnd *)&this->m_GameMoney) + 35;
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[240] = v37;
  bkWndX = this->bkWndX;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[236] = v36 + 5;
  v40 = this->m_GameMoney.m_id;
  bkWndX -= 38;
  this->m_GameMoney.m_fontcolor.Color = bkWndY - 51;
  *(_DWORD *)((UIWnd *)&this->m_GameMoney) = bkWndX;
  this->m_GameMoney.m_wndcolor.Color = bkWndX + 38;
  v41 = this->m_GameMoney.m_fontcolor.Color;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Btn[244] = v40 - 5;
  this->m_GameMoney.m_id = v41 + 48;
  return (((UIWnd *)&this->stp_Exit.m_mouseoff))->UIWnd::sub_445FA0(&this->m_GameMoney);
}

// 0x004A26D0
int LineupUI::RebuildFontPage()
{
  int m_FVF; // eax
  int *p_m_FVF; // edi
  int v4; // edx
  gbTexture *m_pbk2; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int m_benable; // eax
  UIWnd *v14; // edx
  unsigned int v15; // ecx
  int v16; // eax
  int m_bfocus; // ecx
  unsigned int v18; // edx
  int m_bcreateok; // edx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  gbTexture *v23; // ecx
  int v24; // eax
  float v25; // ecx
  int v26; // edx
  Parent_Data *v27; // eax
  int v28; // ecx
  int v29; // edx
  int v30; // edx
  int v31; // eax
  int m_bvisible; // ecx
  int v33; // eax
  int bkWndY; // edx
  int bkWndX; // eax
  int v36; // ecx
  int v37; // eax
  _DWORD v39[2]; // [esp+0x18] [ebp-0x20] BYREF
  int v40; // [esp+0x20] [ebp-0x18]
  int v41; // [esp+0x24] [ebp-0x14]
  _DWORD v42[4]; // [esp+0x28] [ebp-0x10] BYREF

  m_FVF = this->m_OutFrameT.m_FVF;
  p_m_FVF = (int *)&this->m_OutFrameT.m_FVF;
  v39[1] = 543;
  v39[0] = 0;
  v40 = 256;
  v41 = 600;
  (*(void ( **)(int *, int, _DWORD *, LineupUI *))(m_FVF + 16))(
    &this->m_OutFrameT.m_FVF,
    161,
    (_DWORD *)(v39),
    this);
  LOBYTE(v4) = g_bDebugMode;
  (((UIPushButton *)p_m_FVF))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v4);
  m_pbk2 = (gbTexture *)this->m_OutFrameR.m_pbk2;
  v39[0] = v40;
  v40 += 512;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2->IsLoaded)(
    &this->m_OutFrameR.m_pbk2,
    161,
    v39,
    this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameR.m_pbk2))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v6);
  v39[0] = v40;
  v40 += 32;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))this->m_OutFrameL.m_disablepic->IsLoaded)(
    &this->m_OutFrameL.m_disablepic,
    161,
    v39,
    this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameL.m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v7);
  v8 = *(_DWORD *)&this->stp_Exit.m_caption[52];
  v42[1] = 546;
  v42[0] = 0;
  v42[2] = 256;
  v42[3] = 610;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v8 + 16))(&this->stp_Exit.m_caption[52], 161, (_DWORD *)(v42), this);
  LOBYTE(v9) = g_bDebugMode;
  (((UIPushButton *)&this->stp_Exit.m_caption[52]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v9);
  this->stp_Effect.m_bvisible = 546;
  this->stp_Effect.m_bcreateok = 38;
  this->stp_Effect.m_benable = 148;
  v10 = this->stp_Effect.m_bvisible + 50;
  this->stp_Effect.m_bfocus = v10;
  LOBYTE(v10) = g_bDebugMode;
  ((void ( *)(int *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_ppic->Height)(
    &byte_A00102,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v10);
  this->m_CtrlPlank[11].m_Name.m_FVF = this->stp_Effect.m_bvisible + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_mouseoff = this->stp_Effect.m_bcreateok + 35;
  this->m_CtrlPlank[11].m_Name.m_nTextW = this->stp_Effect.m_benable - 36;
  *(_DWORD *)((UIWnd *)&this->m_CtrlPlank[11].m_Dw) = this->stp_Effect.m_bfocus - 5;
  v11 = this->stp_Effect.m_benable - 22;
  this->stp_Effect.m_bcreateok = v11;
  v11 += 110;
  this->stp_Effect.m_benable = v11;
  LOBYTE(v11) = g_bDebugMode;
  (*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[52]
                                                                                          + 28))(
    &byte_A00105,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v11);
  this->m_CtrlPlank[11].m_Dw.m_childs.capacity = this->stp_Effect.m_bvisible + 5;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_pData = (char *)(this->stp_Effect.m_bcreateok + 35);
  this->m_CtrlPlank[11].m_Dw.m_childs.m_nSize = this->stp_Effect.m_benable - 36;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_needscriptdel = this->stp_Effect.m_bfocus - 5;
  v12 = this->stp_Effect.m_benable - 22;
  this->stp_Effect.m_bcreateok = v12;
  v12 += 110;
  this->stp_Effect.m_benable = v12;
  LOBYTE(v12) = g_bDebugMode;
  (*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[52]
                                                                                          + 28))(
    &byte_A00104,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v12);
  this->m_CtrlPlank[11].m_Dw.m_rect.right = this->stp_Effect.m_bvisible + 5;
  m_benable = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_rect.top = this->stp_Effect.m_bcreateok + 35;
  v14 = (UIWnd *)(this->stp_Effect.m_bfocus - 5);
  this->m_CtrlPlank[11].m_Dw.m_rect.bottom = m_benable - 36;
  m_benable -= 22;
  this->m_CtrlPlank[11].m_Dw.m_pfather = v14;
  this->stp_Effect.m_bcreateok = m_benable;
  this->stp_Effect.m_benable = m_benable + 110;
  LOBYTE(v14) = g_bDebugMode;
  (*(void ( **)(int *, int *, int *, LineupUI *, char *, int, UIWnd *))(this->stp_BarR.m_benable + 28))(
    &this->stp_BarR.m_benable,
    &byte_A00103,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v14);
  v15 = this->stp_Effect.m_bcreateok + 35;
  this->m_CtrlPlank[11].m_Dw.m_wndcolor.Color = this->stp_Effect.m_bvisible + 5;
  v16 = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_fontcolor.Color = v15;
  m_bfocus = this->stp_Effect.m_bfocus;
  v18 = v16 - 36;
  v16 -= 22;
  this->stp_Effect.m_bcreateok = v16;
  v16 += 110;
  this->m_CtrlPlank[11].m_Dw.m_id = v18;
  this->m_CtrlPlank[11].m_Dw.m_rect.left = m_bfocus - 5;
  this->stp_Effect.m_benable = v16;
  LOBYTE(v16) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_BattleArray.m_caption[52] + 28))(
    &this->stp_BattleArray.m_caption[52],
    &byte_A00108,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v16);
  m_bcreateok = this->stp_Effect.m_bcreateok;
  v20 = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_bvisible = this->stp_Effect.m_bvisible + 5;
  v21 = v20 - 36;
  this->m_CtrlPlank[11].m_Dw.m_bcreateok = m_bcreateok + 35;
  v22 = this->stp_Effect.m_bfocus;
  v20 -= 22;
  this->stp_Effect.m_bcreateok = v20;
  v22 -= 5;
  this->m_CtrlPlank[11].m_Dw.m_benable = v21;
  this->m_CtrlPlank[11].m_Dw.m_bfocus = v22;
  this->stp_Effect.m_benable = v20 + 110;
  LOBYTE(v22) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_caption[52] + 28))(
    &this->stp_Equip.m_caption[52],
    &byte_A00106,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v22);
  v23 = (gbTexture *)(this->stp_Effect.m_bcreateok + 35);
  this->m_CtrlPlank[11].m_Dw.m_align = this->stp_Effect.m_bvisible + 5;
  v24 = this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.pDebugTex = v23;
  LODWORD(v25) = this->stp_Effect.m_bfocus - 5;
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratiow) = v24 - 36;
  v24 -= 22;
  this->m_CtrlPlank[11].m_Dw.m_ratioh = v25;
  this->stp_Effect.m_bcreateok = v24;
  v24 += 110;
  this->stp_Effect.m_benable = v24;
  LOBYTE(v24) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Prop.m_caption[52] + 28))(
    &this->stp_Prop.m_caption[52],
    &byte_A00107,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v24);
  v26 = this->stp_Effect.m_bcreateok;
  v27 = (Parent_Data *)this->stp_Effect.m_benable;
  this->m_CtrlPlank[11].m_Dw.m_texty = (void *)(this->stp_Effect.m_bvisible + 5);
  v27 -= 9;
  v28 = this->stp_Effect.m_bfocus - 5;
  this->m_CtrlPlank[11].m_Dw.m_textx = (void *)(v26 + 35);
  v29 = *(_DWORD *)&this->stp_System.m_caption[52];
  this->m_CtrlPlank[11].m_Dw.m_fonttype = v27;
  *(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_text = v28;
  LOBYTE(v27) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, Parent_Data *))(v29 + 28))(
    &this->stp_System.m_caption[52],
    &byte_A00110,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
    1,
    v27);
  v30 = *(_DWORD *)&this->stp_TaskBook.m_caption[52];
  v31 = this->stp_Effect.m_benable - 22;
  this->stp_Effect.m_bcreateok = v31;
  v31 += 110;
  this->stp_Effect.m_benable = v31;
  LOBYTE(v31) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v30 + 28))(
    &this->stp_TaskBook.m_caption[52],
    &byte_A00109,
    &this->stp_Effect.m_bcreateok,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v31);
  m_bvisible = this->stp_Effect.m_bvisible;
  v33 = this->stp_Effect.m_benable - 36;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[4] = this->stp_Effect.m_bcreateok + 35;
  bkWndY = this->bkWndY;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[12] = v33;
  bkWndX = this->bkWndX;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[8] = m_bvisible + 5;
  v36 = this->stp_Effect.m_bfocus;
  bkWndX -= 38;
  this->stp_Effect.m_bvisible = bkWndY - 51;
  this->stp_Effect.m_bcreateok = bkWndX;
  this->stp_Effect.m_benable = bkWndX + 38;
  v37 = this->stp_Effect.m_bvisible + 48;
  this->m_CtrlPlank[11].m_Dw.m_pbk = (gbTexture *)(v36 - 5);
  this->stp_Effect.m_bfocus = v37;
  return (((UIWnd *)&this->stp_System.m_caption[52]))->UIWnd::sub_445FA0(&this->stp_Effect.m_bcreateok);
}

// 0x004B1920
int * LineupUI::UpdateProtectPanel(int nVal)
{
  int v3; // eax
  int v4; // esi
  int v5; // ebx
  UIPushButton *v6; // ebp
  int v7; // edx
  int v8; // ecx
  int v10; // [esp+0x0] [ebp-0x20]
  int v11; // [esp+0x18] [ebp-0x8]

  v3 = 40;
  v4 = *(_DWORD *)&this[1].m_btnPar2[10][2]._texName[72] + 40;
  v11 = *(_DWORD *)&this[1].m_btnPar2[10][2]._texName[76] + 12;
  v5 = 0;
  v6 = (UIPushButton *)&this->m_ProtectPanel.m_WPXFace.m_caption[72];
  do
  {
    (((ChoseCompose *)this))->ChoseCompose::LayoutItem(v5, 12, v3, v11, v4);
    sub_445E50((int)&v6[-2]);
    if ( nVal )
    {
      if ( nVal == 1 )
      {
        LOBYTE(v8) = g_bDebugMode;
        (((UIPushButton *)v6))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\dq.tga", v8);
      }
    }
    else
    {
      LOBYTE(v7) = g_bDebugMode;
      (((UIPushButton *)v6))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\System\\cc.tga", v7);
    }
    v3 = v4;
    v4 += *(_DWORD *)&this[1].m_btnPar2[10][2]._texName[72];
    ++v5;
    v6 = (UIPushButton *)((char *)v6 + 3560);
  }
  while ( v5 < 36 );
  sub_445E50((int)&this->m_ProtectPanel.m_BK.m_text[12]);
  return (int *)UITitle_JDHY_UpdateButtonStates(v10);
}

// 0x004B3DA0
int LineupUI::RebuildMainPage()
{
  gbTexture *m_pbk2; // eax
  gbTexture **p_m_pbk2; // edi
  int v4; // edx
  gbTexture *m_disablepic; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int m_bcreateok; // edx
  int m_bvisible; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // edx
  unsigned int v16; // ecx
  unsigned int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // ecx
  int v21; // edx
  int m_nSize; // edx
  int v23; // eax
  gbTexture *v24; // ecx
  int v25; // edx
  int v26; // ecx
  int v27; // eax
  void *v28; // edx
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // edx
  int v33; // edx
  int v34; // ecx
  int v35; // edx
  int v36; // ecx
  int v37; // eax
  int v38; // edx
  _DWORD v40[2]; // [esp+D0h] [ebp-0x30] BYREF
  int v41; // [esp+D8h] [ebp-0x28]
  int v42; // [esp+DCh] [ebp-0x24]
  _DWORD v43[4]; // [esp+E0h] [ebp-0x20] BYREF
  _DWORD v44[4]; // [esp+F0h] [ebp-0x10] BYREF

  m_pbk2 = (gbTexture *)this->m_OutFrameT.m_pbk2;
  p_m_pbk2 = (gbTexture **)&this->m_OutFrameT.m_pbk2;
  v40[1] = 543;
  v40[0] = 0;
  v41 = 256;
  v42 = 600;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))m_pbk2->IsLoaded)(
    &this->m_OutFrameT.m_pbk2,
    161,
    v40,
    this);
  LOBYTE(v4) = g_bDebugMode;
  (((UIPushButton *)p_m_pbk2))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarL.tga", v4);
  m_disablepic = (gbTexture *)this->m_OutFrameR.m_disablepic;
  v40[0] = v41;
  v41 += 512;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))m_disablepic->IsLoaded)(
    &this->m_OutFrameR.m_disablepic,
    161,
    v40,
    this);
  LOBYTE(v6) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameR.m_disablepic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarM.tga", v6);
  v40[0] = v41;
  v41 += 32;
  ((void ( *)(gbTexture **, int, _DWORD *, LineupUI *))this->m_OutFrameL.m_ppic->IsLoaded)(
    &this->m_OutFrameL.m_ppic,
    161,
    v40,
    this);
  LOBYTE(v7) = g_bDebugMode;
  (((UIPushButton *)&this->m_OutFrameL.m_ppic))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\StpBarR.tga", v7);
  this->stp_Effect.m_childs.m_needscriptdel = 546;
  this->stp_Effect.m_childs.m_nSize = 38;
  this->stp_Effect.m_bcreateok = 148;
  this->stp_Effect.m_bvisible = this->stp_Effect.m_childs.m_needscriptdel + 50;
  LOBYTE(v8) = g_bDebugMode;
  ((void ( *)(gbTexture **, int *, int *, LineupUI *, char *, int, int))this->m_OutFrameB.m_pbk->Height)(
    &this->m_OutFrameB.m_pbk,
    &byte_A00102,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\State",
    1,
    v8);
  this->m_CtrlPlank[11].m_Name.m_pbk2 = (gbTexture *)(this->stp_Effect.m_childs.m_needscriptdel + 5);
  this->m_CtrlPlank[11].m_Name.m_disablepicInfo = (_PlugInfo *)(this->stp_Effect.m_childs.m_nSize + 35);
  *(_DWORD *)&this->m_CtrlPlank[11].m_Name.m_mouseoff = this->stp_Effect.m_bcreateok - 36;
  this->m_CtrlPlank[11].m_Name.m_FVF = this->stp_Effect.m_bvisible - 5;
  v9 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v9;
  v9 += 110;
  this->stp_Effect.m_bcreateok = v9;
  LOBYTE(v9) = g_bDebugMode;
  (*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Magic.m_caption[44]
                                                                                          + 28))(
    &byte_A00105,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Prop",
    1,
    v9);
  this->m_CtrlPlank[11].m_Dw.m_pfather = (UIWnd *)(this->stp_Effect.m_childs.m_needscriptdel + 5);
  this->m_CtrlPlank[11].m_Dw.m_rect.bottom = this->stp_Effect.m_childs.m_nSize + 35;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_pData = (char *)(this->stp_Effect.m_bcreateok - 36);
  this->m_CtrlPlank[11].m_Dw.m_childs.capacity = this->stp_Effect.m_bvisible - 5;
  v10 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v10;
  v10 += 110;
  this->stp_Effect.m_bcreateok = v10;
  LOBYTE(v10) = g_bDebugMode;
  (*(void ( **)(int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_State.m_caption[44]
                                                                                          + 28))(
    &byte_A00104,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Equip",
    1,
    v10);
  this->m_CtrlPlank[11].m_Dw.m_rect.left = this->stp_Effect.m_childs.m_needscriptdel + 5;
  this->m_CtrlPlank[11].m_Dw.m_id = this->stp_Effect.m_childs.m_nSize + 35;
  m_bcreateok = this->stp_BarR.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_rect.top = this->stp_Effect.m_bcreateok - 36;
  m_bvisible = this->stp_Effect.m_bvisible;
  v13 = this->stp_Effect.m_bcreateok - 22;
  this->stp_Effect.m_childs.m_nSize = v13;
  v13 += 110;
  this->m_CtrlPlank[11].m_Dw.m_rect.right = m_bvisible - 5;
  this->stp_Effect.m_bcreateok = v13;
  LOBYTE(v13) = g_bDebugMode;
  (*(void ( **)(int *, int *, int *, LineupUI *, char *, int, int))(m_bcreateok + 28))(
    &this->stp_BarR.m_bcreateok,
    &byte_A00103,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Magic",
    1,
    v13);
  v14 = this->stp_Effect.m_bcreateok;
  v15 = this->stp_Effect.m_childs.m_nSize + 35;
  *(_DWORD *)((UIWnd *)&this->m_CtrlPlank[11].m_Dw) = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v16 = v14 - 36;
  this->m_CtrlPlank[11].m_Name.m_nTextW = v15;
  v14 -= 22;
  v17 = this->stp_Effect.m_bvisible - 5;
  this->stp_Effect.m_childs.m_nSize = v14;
  this->m_CtrlPlank[11].m_Dw.m_fontcolor.Color = v16;
  this->m_CtrlPlank[11].m_Dw.m_wndcolor.Color = v17;
  this->stp_Effect.m_bcreateok = v14 + 110;
  LOBYTE(v17) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, unsigned int))(*(_DWORD *)&this->stp_BattleArray.m_caption[44] + 28))(
    &this->stp_BattleArray.m_caption[44],
    &byte_A00108,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Battle_Array",
    1,
    v17);
  v18 = this->stp_Effect.m_childs.m_nSize + 35;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_needscriptdel = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v19 = this->stp_Effect.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_childs.m_nSize = v18;
  v20 = this->stp_Effect.m_bvisible;
  v21 = v19 - 36;
  v19 -= 22;
  this->stp_Effect.m_childs.m_nSize = v19;
  v19 += 110;
  this->m_CtrlPlank[11].m_Dw.m_bcreateok = v21;
  this->m_CtrlPlank[11].m_Dw.m_bvisible = v20 - 5;
  this->stp_Effect.m_bcreateok = v19;
  LOBYTE(v19) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Equip.m_caption[44] + 28))(
    &this->stp_Equip.m_caption[44],
    &byte_A00106,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\Sword",
    1,
    v19);
  m_nSize = this->stp_Effect.m_childs.m_nSize;
  v23 = this->stp_Effect.m_bcreateok;
  this->m_CtrlPlank[11].m_Dw.m_bfocus = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v24 = (gbTexture *)(v23 - 36);
  this->m_CtrlPlank[11].m_Dw.m_benable = m_nSize + 35;
  v25 = this->stp_Effect.m_bvisible;
  v23 -= 22;
  this->stp_Effect.m_childs.m_nSize = v23;
  v25 -= 5;
  this->m_CtrlPlank[11].m_Dw.pDebugTex = v24;
  this->m_CtrlPlank[11].m_Dw.m_align = v25;
  this->stp_Effect.m_bcreateok = v23 + 110;
  LOBYTE(v25) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_Prop.m_caption[44] + 28))(
    &this->stp_Prop.m_caption[44],
    &byte_A00107,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\JusticeBook",
    1,
    v25);
  v26 = this->stp_Effect.m_childs.m_nSize;
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratioh) = this->stp_Effect.m_childs.m_needscriptdel + 5;
  v27 = this->stp_Effect.m_bcreateok;
  v43[1] = 546;
  v28 = (void *)(v27 - 36);
  LODWORD(this->m_CtrlPlank[11].m_Dw.m_ratiow) = v26 + 35;
  v29 = this->stp_Effect.m_bvisible;
  v27 -= 22;
  this->stp_Effect.m_childs.m_nSize = v27;
  this->stp_Effect.m_bcreateok = v27 + 110;
  v43[0] = this->stp_Effect.m_childs.m_nSize - 38;
  v43[2] = v43[0] + 256;
  this->m_CtrlPlank[11].m_Dw.m_textx = v28;
  v30 = *(_DWORD *)&this->stp_Exit.m_caption[44];
  this->m_CtrlPlank[11].m_Dw.m_texty = (void *)(v29 - 5);
  v43[3] = 610;
  (*(void ( **)(char *, int, _DWORD *, LineupUI *))(v30 + 16))(&this->stp_Exit.m_caption[44], 161, (_DWORD *)(v43), this);
  LOBYTE(v31) = g_bDebugMode;
  (((UIPushButton *)&this->stp_Exit.m_caption[44]))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\StpCtl\\Effect.tga", v31);
  LOBYTE(v32) = g_bDebugMode;
  (*(void ( **)(char *, int *, int *, LineupUI *, char *, int, int))(*(_DWORD *)&this->stp_TaskBook.m_caption[44]
                                                                                        + 28))(
    &this->stp_TaskBook.m_caption[44],
    &byte_A00109,
    &this->stp_Effect.m_childs.m_nSize,
    this,
    "UI\\GameMainUI\\Communal\\StpCtl\\System",
    1,
    v32);
  v33 = this->stp_Effect.m_bcreateok;
  v34 = this->stp_Effect.m_childs.m_nSize;
  *(_DWORD *)this->m_CtrlPlank[11].m_Dw.m_text = this->stp_Effect.m_childs.m_needscriptdel + 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[8] = this->stp_Effect.m_bvisible - 5;
  *(_DWORD *)&this->m_CtrlPlank[11].m_Dw.m_text[4] = v33 - 36;
  v35 = *((_DWORD *)&this->m_Frame + 38);
  this->m_CtrlPlank[11].m_Dw.m_fonttype = (Parent_Data *)(v34 + 35);
  v44[1] = 64;
  v44[0] = 784;
  v44[2] = 800;
  v44[3] = 590;
  (*(void ( **)(UIStatic *, int, _DWORD *, LineupUI *))(v35 + 16))(&this->m_Frame + 1, 161, (_DWORD *)(v44), this);
  LOBYTE(v36) = g_bDebugMode;
  (((UIPushButton *)(&this->m_Frame + 1)))->UIPushButton::CreateFromTemplate("UI\\GameMainUI\\Communal\\Frame_Line.tga", v36);
  this->stp_Effect.m_childs.m_needscriptdel = this->bkWndY - 51;
  v37 = this->bkWndX - 38;
  v38 = *(_DWORD *)&this->stp_System.m_caption[44];
  this->stp_Effect.m_childs.m_nSize = v37;
  v37 += 38;
  this->stp_Effect.m_bcreateok = v37;
  this->stp_Effect.m_bvisible = this->stp_Effect.m_childs.m_needscriptdel + 48;
  LOBYTE(v37) = g_bDebugMode;
  return (*(int ( **)(char *, int *, int *, LineupUI *, char *, int, int))(v38 + 28))(
           &this->stp_System.m_caption[44],
           &byte_A00110,
           &this->stp_Effect.m_childs.m_nSize,
           this,
           "UI\\GameMainUI\\Communal\\StpCtl\\Exit",
           1,
           v37);
}
