#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIRoleSelectDialog.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445FA0(void *a2); // from annotations
void * sub_446010(void *a2); // from annotations

// Unnamed globals (extern)
extern char byte_80AB20;
extern int dword_DD353C;
extern int dword_DD363C;
extern int dword_DDC23C;
extern char * off_5ED1D0;
extern void * off_5ED1D4;
extern RoleSystem stru_C059A0;
extern unsigned int unk_5DFDEC;

// 0x00451980
int UIRoleSelectDialog::CreateDialog(int id, void *pRect, int parent, char *tex)
{
  int v6; // eax
  void *m_id; // edx
  int result; // eax
  _DWORD v9[2]; // [esp+0x18] [ebp-0x10] BYREF
  int v10; // [esp+0x20] [ebp-0x8]
  int v11; // [esp+0x24] [ebp-0x4]

  ((PalScript *)this)->Create(id, (tagRECT *)pRect, parent);
  ((UINote *)&this->m_list.m_column[1].items.m_nSize)->Create(0, (int)pRect, (int)this, "ui\\flex\\note");
  sub_445FA0(&this->m_list.m_column[1].items.m_nSize);
  v6 = *((_DWORD *)pRect + 3);
  v10 = *((_DWORD *)pRect + 2) - *(_DWORD *)pRect - 16;
  m_id = this->m_bk.m_id;
  v11 = v6 - *((_DWORD *)pRect + 1) - 16;
  v9[0] = 8;
  v9[1] = 0;
  (*((void ( **)(void **, _DWORD, _DWORD *, UIRoleSelectDialog *, _DWORD, _DWORD, _DWORD))m_id + 7))(
    &this->m_bk.m_id,
    0,
    v9,
    this,
    0,
    0,
    0);
  ((UIListBox *)&this->m_bk.m_id)->SetFirstShow((int)"_seldlg", v10 - v9[0]);
  ((UIListBox *)&this->m_bk.m_id)->SetItemData(1);
  sub_446010(&this->m_bk.m_id);
  ((UIListBox *)&this->m_bk.m_id)->GetSel((int)"ui\\scene\\SelPic.tga", 0);
  this->ShowWindow(0);
  *(_DWORD *)&this->m_list.m_column[0].head[60] = 20;
  ((UIListBox *)&this->m_bk.m_id)->SetLockSel();
  return result;
}

// 0x005295F0
int UIRoleSelectDialog::ctor_95F0()
{
  this->m_bk.m_id = (void *)800;
  this->m_bk.m_rect.left = 600;
  LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 0;
  sub_4422E0(&this->m_ani.m_texarray.m_ptex[4]);
  this->m_list.m_column[1].head[36] = 0;
  *(_DWORD *)&this->m_list.m_column[1].head[32] = 0;
  *(_DWORD *)&this->m_list.m_column[1].head[28] = 0;
  this->m_list.m_column[1].head[56] = 0;
  *(_DWORD *)&this->m_list.m_column[1].head[52] = 0;
  *(_DWORD *)&this->m_list.m_column[1].head[48] = 0;
  sub_4422E0(&this->m_list.m_column[1].head[60]);
  sub_4422E0(&this->m_list.m_column[3].head[44]);
  sub_4422E0(&this->m_list.m_scrollRc.right);
  ((UITextArea *)&this->m_maxlen)->InitAfterClear();
  *(_DWORD *)&this->m_list.m_column[1].head[44] = 32;
  *(_DWORD *)&this->m_list.m_column[1].head[40] = 32;
  *(_DWORD *)&this->m_list.m_column[5].head[28] = 64;
  *(_DWORD *)&this->m_list.m_column[5].head[32] = 58;
  this->m_list.m_column[6].items.m_pData = (char *)28;
  this->m_list.m_firstshow = 1065353216;
  this->m_list.m_onsel = 1060152279;
  this->m_list.m_locksel = 1036831949;
  this->m_list.m_scrollRc.left = 1008981770;
  *(_DWORD *)&this->m_list.m_column[5].head[40] = 0;
  *(_DWORD *)&this->m_list.m_column[5].head[36] = 0;
  *(_DWORD *)&this->m_list.m_column[5].head[44] = 800;
  *(_DWORD *)&this->m_list.m_column[5].head[48] = 600;
  *((_DWORD *)this + 547) = 0;
  *((_BYTE *)this + 2200) = 1;
  return (int)this;
}

// 0x00529790
void UIRoleSelectDialog::ctor()
{
  UIQuadManager *Instance; // eax

  Instance = UIQuadManager::GetInstance();
  ((UIRenderObj *)Instance)->_UIRenderObj();
  ((UITextArea *)&this->m_maxlen)->Destroy();
  ((UIFrameWnd *)&this->m_list.m_scrollRc.right)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_list.m_column[3].head[44])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_list.m_column[1].head[60])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_list.m_scrollbar.m_texarrayInfo[5])->_UIFrameWnd_Full();
  ((UIFrameWnd *)&this->m_ani.m_texarray.m_ptex[4])->UIFrameWnd::_UIFrameWnd();
  ((UIListBox *)this)->_UIListBox();
}

// 0x00529CF0
void UIRoleSelectDialog::Render()
{
  float *p_m_ratioh; // edi
  int *p_width; // ebx
  CCBMagicWindow *v4; // [esp+0x0] [ebp-0x20]
  char *v5; // [esp+0x4] [ebp-0x1C]
  int v6; // [esp+0x8] [ebp-0x18]

  ((UISceneMap *)this)->Render_529c80();
  v6 = 0;
  if ( *(int *)&this->m_list.m_column[6].head[48] > 0 )
  {
    p_m_ratioh = &this->m_face.m_ratioh;
    p_width = &this->m_list.m_column[5].width;
    v5 = &this->m_list.m_column[5].head[52];
    do
    {
      if ( *(_DWORD *)v5 <= 1u )
        sub_445FA0(p_m_ratioh);
      (*(void ( **)(float *))(*(_DWORD *)p_m_ratioh + 4))(p_m_ratioh);
      v5 += 4;
      p_width += 2;
      p_m_ratioh += 46;
      ++v6;
    }
    while ( v6 < *(_DWORD *)&this->m_list.m_column[6].head[48] );
  }
  ((CCBControlWindow *)this)->Render(v4);
}

// 0x00529E40
double UIRoleSelectDialog::HandleInput(
        
        double st6_0,
        double result,
        int arg0,
        int arg0a)
{
  double v5; // st7
  DWORD TickCount; // eax
  DWORD v8; // eax
  unsigned int v9; // ecx
  BOOL ( *v10)(const RECT *, POINT); // ebp
  int v11; // edi
  DWORD v12; // eax
  DWORD v13; // eax
  int v14; // ebx
  CScreenMode *Instance; // eax
  int v16; // ebx
  int v17; // ebx
  int v18; // ecx
  int v19; // ebp
  int v20; // eax
  bool v21; // dl
  bool v22; // al
  int v23; // ecx
  int v24; // edx
  CCBStageRole *v25; // eax
  float *v26; // ebx
  int v27; // eax
  int v28; // eax
  int v29; // ecx
  char *v30; // eax
  CCBStageRole *v31; // eax
  int v32; // ecx
  char *v33; // eax
  int capacity; // eax
  double v35; // st7
  double v36; // st7
  int v37; // ecx
  double v38; // st7
  double v39; // st7
  int v40; // ecx
  double v41; // st7
  int v42; // ecx
  double v43; // st7
  double v44; // st7
  int v45; // ecx
  UIQuadManager *v46; // eax
  int v47; // eax
  gbTexture *v48; // eax
  CCBStageRole *v49; // eax
  const void *v50; // [esp+0x4] [ebp-0x74]
  char *v51; // [esp+0x8] [ebp-0x70]
  char *v52; // [esp+0x8] [ebp-0x70]
  char *v53; // [esp+0x8] [ebp-0x70]
  int v54; // [esp+0xC] [ebp-0x6C]
  char v55; // [esp+0x1C] [ebp-0x5C]
  char v56; // [esp+0x1D] [ebp-0x5B]
  bool v57; // [esp+0x1E] [ebp-0x5A]
  char v58; // [esp+0x1F] [ebp-0x59]
  int v59; // [esp+0x28] [ebp-0x50]
  int v60; // [esp+0x2C] [ebp-0x4C]
  POINT Point; // [esp+0x30] [ebp-0x48]
  POINT pt; // [esp+0x38] [ebp-0x40]
  float v63; // [esp+0x40] [ebp-0x38]
  float v64; // [esp+0x44] [ebp-0x34]
  float v65; // [esp+0x4C] [ebp-0x2C]
  float v66; // [esp+0x50] [ebp-0x28]
  int v67; // [esp+0x60] [ebp-0x18]
  int v68; // [esp+0x64] [ebp-0x14]
  int v69; // [esp+0x68] [ebp-0x10]
  int v70; // [esp+0x6C] [ebp-0xC]
  int v71; // [esp+0x74] [ebp-0x4]

  if ( !this->m_list.m_column[1].head[36] )
  {
    TickCount = GetTickCount();
    *(_DWORD *)&this->m_list.m_column[1].head[28] = TickCount;
    *(_DWORD *)&this->m_list.m_column[1].head[32] = TickCount;
    this->m_list.m_column[1].head[36] = 1;
  }
  v8 = GetTickCount();
  v9 = v8 - *(_DWORD *)&this->m_list.m_column[1].head[32];
  *(_DWORD *)&this->m_list.m_column[1].head[28] = v8;
  if ( v9 > 0x898 )
  {
    *(_DWORD *)&this->m_list.m_column[1].head[32] = v8;
    this->m_list.m_column[1].head[36] = 0;
    ((CCBResultWindow *)&this->m_list.m_scrollbar.m_texarrayInfo[5])->SetDirty();
    ((void ( *)(_PlugInfo **, _DWORD))this->m_list.m_scrollbar.m_texarrayInfo[5]->filepos)(
      &this->m_list.m_scrollbar.m_texarrayInfo[5],
      0);
    this->m_list.m_column[1].head[20] = 1;
  }
  v59 = *(_DWORD *)&this->m_list.m_column[5].head[44] - *(_DWORD *)&this->m_list.m_column[5].head[36];
  v10 = PtInRect;
  v60 = *(_DWORD *)&this->m_list.m_column[5].head[48] - *(_DWORD *)&this->m_list.m_column[5].head[40];
  v11 = 0;
  if ( *(int *)&this->m_list.m_column[6].head[48] > 0 )
  {
    while ( 1 )
    {
      (*(void ( **)(_DWORD, _DWORD))(*((_DWORD *)&this->m_face.m_ratioh + 46 * v11) + 8))(
        LODWORD(st6_0),
        HIDWORD(st6_0));
      if ( *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] == 3 )
        goto LABEL_125;
      ((GRPinput *)&g_Input)->GetCursorPos();
      v55 = 0;
      if ( PtInRect((const RECT *)&this->m_list.m_column[5].head[36], pt) )
      {
        if ( !this->m_list.m_column[1].head[56] )
        {
          v12 = GetTickCount();
          *(_DWORD *)&this->m_list.m_column[1].head[48] = v12;
          *(_DWORD *)&this->m_list.m_column[1].head[52] = v12;
          this->m_list.m_column[1].head[56] = 1;
        }
        v13 = GetTickCount();
        v14 = *(_DWORD *)&this->m_list.m_column[1].head[52];
        *(_DWORD *)&this->m_list.m_column[1].head[48] = v13;
        if ( v13 - v14 > 0x64 )
        {
          *(_DWORD *)&this->m_list.m_column[1].head[52] = v13;
          this->m_list.m_column[1].head[56] = 0;
          (**(void ( ***)(char *, int))&this->m_list.m_column[1].head[60])(
            &this->m_list.m_column[1].head[60],
            1);
          (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[3].head[44])(
            &this->m_list.m_column[3].head[44],
            0);
        }
        v55 = 1;
      }
      else
      {
        (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[1].head[60])(
          &this->m_list.m_column[1].head[60],
          0);
        (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[3].head[44])(
          &this->m_list.m_column[3].head[44],
          0);
      }
      sub_445FA0(&this->m_list.m_column[1].head[60]);
      sub_445FA0(&this->m_list.m_column[3].head[44]);
      if ( g_Input.KeyInfo[0].PressTime == 1 && !LOBYTE(this->m_ani.m_texarray.m_ptex[2]) )
      {
        if ( v55 )
        {
          (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[1].head[60])(
            &this->m_list.m_column[1].head[60],
            0);
          (**(void ( ***)(char *, int))&this->m_list.m_column[3].head[44])(
            &this->m_list.m_column[3].head[44],
            1);
          v50 = off_5ED1D4;
          Instance = CScreenMode::GetInstance();
          ((CScreenMode *)Instance)->AudioSetPosition(v50, 1);
        }
        *((_BYTE *)this + 2184) = 0;
      }
      v16 = *(_DWORD *)&this->m_list.m_column[1].head[40];
      v70 = (__int64)(*(float *)&this->m_list.m_column[6].head[8 * v11]
                    - (double)(*(_DWORD *)&this->m_list.m_column[1].head[44] / 2));
      v5 = *((float *)&this->m_list.m_column[5].width + 2 * v11) - (double)(v16 / 2);
      v69 = (__int64)v5;
      v17 = v69 + v16;
      v71 = *(_DWORD *)&this->m_list.m_column[1].head[44] + v70;
      v18 = pt.y - *(_DWORD *)&this->m_list.m_column[5].head[32] / 2;
      v19 = v18 + 45;
      v20 = pt.x - *(_DWORD *)&this->m_list.m_column[5].head[28] / 2;
      v68 = v18 + 45;
      v67 = v20 + 45;
      if ( *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] == 1 )
        goto LABEL_72;
      if ( v20 < v69 )
      {
        if ( v67 <= v69 )
        {
          v19 = v18 + 45;
        }
        else
        {
          if ( v18 > v70 && v18 < v71 )
          {
            v19 = v18 + 45;
            v56 = 1;
            goto LABEL_30;
          }
          v19 = v18 + 45;
          if ( v68 > v70 && v68 < v71 )
          {
            v56 = 1;
            goto LABEL_30;
          }
        }
      }
      v56 = 0;
LABEL_30:
      v57 = v20 < v17 && v67 > v17 && (v18 > v70 && v18 < v71 || v19 > v70 && v19 < v71);
      if ( v18 < v70 && v19 > v70 )
      {
        if ( v20 > v69 && v20 < v17 )
          goto LABEL_45;
        if ( v67 > v69 && v67 < v17 )
        {
          v19 = v18 + 45;
LABEL_45:
          v58 = 1;
          goto LABEL_48;
        }
        v19 = v18 + 45;
      }
      v58 = 0;
LABEL_48:
      v21 = v18 < v71 && v19 > v71 && (v20 > v69 && v20 < v17 || v67 > v69 && v67 < v17);
      v22 = v18 > v70 && v20 > v69 && v67 < v17 && v68 < v71;
      if ( (v56 || v57 || v58 || v21 || v22) && v55 && g_Input.KeyInfo[0].PressTime == 1 )
      {
        v23 = *(_DWORD *)&this->m_list.m_column[6].head[48];
        v24 = this->m_list.m_column[5].items.m_needscriptdel + 1;
        this->m_list.m_column[5].items.m_needscriptdel = v24;
        if ( v24 >= v23 )
        {
          v51 = off_5ED1D0;
          v25 = (CCBStageRole *)CScreenMode::GetInstance();
          ((CCBStageRole *)v25)->PlaySound(v51, v54);
        }
        v26 = &this->m_face.m_ratioh + 46 * v11;
        ((UIStatic *)v26)->CreateFromTemplate();
        *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] = 1;
        *(_DWORD *)&this->m_list.m_column[7].head[4 * v11 + 44] = 1050253722;
        goto LABEL_73;
      }
LABEL_72:
      v26 = &this->m_face.m_ratioh + 46 * v11;
LABEL_73:
      v27 = *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52];
      if ( v27 )
      {
        v28 = v27 - 1;
        if ( v28 )
        {
          if ( v28 == 1 && !LOBYTE(this->m_list.m_scrollRc.top) )
          {
            (**(void ( ***)(float *, _DWORD))v26)(v26, 0);
            v29 = *(_DWORD *)&this->m_list.m_column[6].head[48];
            v30 = this->m_list.m_column[5].items.m_pData + 1;
            this->m_list.m_column[5].items.m_pData = v30;
            if ( (int)v30 >= v29 )
            {
              LOBYTE(this->m_list.m_scrollRc.top) = 1;
              v52 = off_5ED1D0;
              v31 = (CCBStageRole *)CScreenMode::GetInstance();
              ((CCBStageRole *)v31)->PlaySound(v52, v54);
            }
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] = 3;
          }
        }
        else
        {
          *(float *)&this->m_list.m_column[6].head[8 * v11] = *(float *)&this->m_list.m_column[6].head[8 * v11]
                                                            + *(float *)&this->m_list.m_column[7].head[4 * v11 + 44];
          *(float *)&this->m_list.m_column[7].head[4 * v11 + 44] = *(float *)&this->m_list.m_column[7].head[4 * v11 + 44]
                                                                 + 0.0099999998;
          v5 = (double)(*(_DWORD *)&this->m_list.m_column[5].head[48] - 2 * (int)this->m_list.m_column[6].items.m_pData);
          if ( v5 <= *(float *)&this->m_list.m_column[6].head[8 * v11] )
          {
            (**(void ( ***)(float *, _DWORD))v26)(v26, 0);
            *(&this->m_list.m_column[5].width + 2 * v11) = 1137180672;
            *(_DWORD *)&this->m_list.m_column[6].head[8 * v11 + 24] = 1137180672;
            *(_DWORD *)&this->m_list.m_column[6].head[8 * v11] = 1133903872;
            *(_DWORD *)&this->m_list.m_column[6].head[8 * v11 + 28] = 1133903872;
            *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = 0;
            if ( !LOBYTE(this->m_list.m_scrollRc.top) )
            {
              v32 = *(_DWORD *)&this->m_list.m_column[6].head[48];
              v33 = this->m_list.m_column[5].items.m_pData + 1;
              this->m_list.m_column[5].items.m_pData = v33;
              if ( (int)v33 >= v32 )
                LOBYTE(this->m_list.m_scrollRc.top) = 1;
              *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] = 3;
              capacity = this->m_list.m_column[5].items.capacity;
              ++this->m_list.m_column[5].items.m_nSize;
              this->m_list.m_column[5].items.capacity = *(&this->m_list.m_column[7].width + v11) + capacity;
            }
          }
        }
        goto LABEL_125;
      }
      if ( this->m_list.m_column[6].head[v11 + 20] )
      {
        *(float *)&this->m_list.m_column[6].head[8 * v11 + 24] = (float)(*(_DWORD *)&this->m_list.m_column[5].head[36]
                                                                       + rand() % v59);
        *(float *)&this->m_list.m_column[6].head[8 * v11 + 28] = (float)(*(_DWORD *)&this->m_list.m_column[5].head[40]
                                                                       + rand() % v60);
        *((float *)&this->m_list.m_column[6].items.capacity + 2 * v11) = *(float *)&this->m_list.m_column[6].head[8 * v11 + 24]
                                                                       - *((float *)&this->m_list.m_column[5].width
                                                                         + 2 * v11);
        v35 = *(float *)&this->m_list.m_column[6].head[8 * v11 + 28] - *(float *)&this->m_list.m_column[6].head[8 * v11];
        *((float *)&this->m_list.m_column[6].items.m_nSize + 2 * v11) = v35;
        v65 = *((float *)&this->m_list.m_column[6].items.capacity + 2 * v11);
        v66 = v35;
        v63 = *(float *)&this->m_list.m_column[7].head[8 * v11 + 8];
        v64 = *(float *)&this->m_list.m_column[7].head[8 * v11 + 12];
        v5 = acos((v64 * v66 + v63 * v65) / (sqrt(v64 * v64 + v63 * v63) + sqrt(v66 * v66 + v65 * v65))) * 57.29578;
        if ( v65 < 0.0 )
          v5 = 180.0 - v5 + 180.0;
        v26[40] = v5;
        *((_BYTE *)v26 + 172) = 0;
        this->m_list.m_column[6].head[v11 + 20] = 0;
        goto LABEL_125;
      }
      if ( *((float *)&this->m_list.m_column[5].width + 2 * v11) >= (double)*(float *)&this->m_list.m_column[6].head[8 * v11 + 24] )
      {
        if ( *((float *)&this->m_list.m_column[5].width + 2 * v11) > (double)*(float *)&this->m_list.m_column[6].head[8 * v11 + 24] )
        {
          v38 = *((float *)&this->m_list.m_column[5].width + 2 * v11);
          if ( *(&this->m_list.m_column[7].items.capacity + v11) )
            v39 = v38 - *(float *)&this->m_list.m_column[7].head[4 * v11 + 56];
          else
            v39 = v38 - *(float *)&this->m_list.m_column[7].head[4 * v11 + 44];
          *((float *)&this->m_list.m_column[5].width + 2 * v11) = v39;
          v5 = (double)(unsigned int)&this->m_list.m_column[6].items.m_pData[*(_DWORD *)&this->m_list.m_column[5].head[36]];
          if ( v5 >= *((float *)&this->m_list.m_column[5].width + 2 * v11) )
          {
            v40 = *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] + 1;
            *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = v40;
            if ( v40 >= 2 )
            {
              *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] = 2;
              *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = 0;
            }
            goto LABEL_124;
          }
          v5 = *((float *)&this->m_list.m_column[5].width + 2 * v11);
          if ( v5 <= *(float *)&this->m_list.m_column[6].head[8 * v11 + 24] )
          {
            *(&this->m_list.m_column[5].width + 2 * v11) = *(_DWORD *)&this->m_list.m_column[6].head[8 * v11 + 24];
            goto LABEL_124;
          }
        }
      }
      else
      {
        if ( *(&this->m_list.m_column[7].items.capacity + v11) )
          v36 = *(float *)&this->m_list.m_column[7].head[4 * v11 + 56];
        else
          v36 = *(float *)&this->m_list.m_column[7].head[4 * v11 + 44];
        *((float *)&this->m_list.m_column[5].width + 2 * v11) = v36
                                                              + *((float *)&this->m_list.m_column[5].width + 2 * v11);
        v5 = (double)(*(_DWORD *)&this->m_list.m_column[5].head[44]
                    - (unsigned int)this->m_list.m_column[6].items.m_pData);
        if ( v5 < *((float *)&this->m_list.m_column[5].width + 2 * v11) )
        {
          v37 = *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] + 1;
          *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = v37;
          if ( v37 >= 2 )
          {
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] = 2;
            *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = 0;
          }
          goto LABEL_124;
        }
        v5 = *((float *)&this->m_list.m_column[5].width + 2 * v11);
        if ( v5 >= *(float *)&this->m_list.m_column[6].head[8 * v11 + 24] )
        {
          *(&this->m_list.m_column[5].width + 2 * v11) = *(_DWORD *)&this->m_list.m_column[6].head[8 * v11 + 24];
LABEL_124:
          this->m_list.m_column[6].head[v11 + 20] = 1;
          goto LABEL_125;
        }
      }
      if ( *(float *)&this->m_list.m_column[6].head[8 * v11] >= (double)*(float *)&this->m_list.m_column[6].head[8 * v11 + 28] )
      {
        v5 = *(float *)&this->m_list.m_column[6].head[8 * v11];
        if ( v5 > *(float *)&this->m_list.m_column[6].head[8 * v11 + 28] )
        {
          v43 = *(float *)&this->m_list.m_column[6].head[8 * v11];
          if ( *(&this->m_list.m_column[7].items.capacity + v11) )
            v44 = v43 - *(float *)&this->m_list.m_column[7].head[4 * v11 + 56];
          else
            v44 = v43 - *(float *)&this->m_list.m_column[7].head[4 * v11 + 44];
          *(float *)&this->m_list.m_column[6].head[8 * v11] = v44;
          v5 = (double)(unsigned int)&this->m_list.m_column[6].items.m_pData[*(_DWORD *)&this->m_list.m_column[5].head[40]];
          if ( v5 >= *(float *)&this->m_list.m_column[6].head[8 * v11] )
          {
            v45 = *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] + 1;
            *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = v45;
            if ( v45 >= 2 )
            {
              *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] = 2;
              *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = 0;
            }
            goto LABEL_124;
          }
          v5 = *(float *)&this->m_list.m_column[6].head[8 * v11];
          if ( v5 <= *(float *)&this->m_list.m_column[6].head[8 * v11 + 28] )
            goto LABEL_124;
        }
      }
      else
      {
        if ( *(&this->m_list.m_column[7].items.capacity + v11) )
          v41 = *(float *)&this->m_list.m_column[7].head[4 * v11 + 56];
        else
          v41 = *(float *)&this->m_list.m_column[7].head[4 * v11 + 44];
        *(float *)&this->m_list.m_column[6].head[8 * v11] = v41 + *(float *)&this->m_list.m_column[6].head[8 * v11];
        v5 = (double)(*(_DWORD *)&this->m_list.m_column[5].head[48]
                    - (unsigned int)this->m_list.m_column[6].items.m_pData);
        if ( v5 <= *(float *)&this->m_list.m_column[6].head[8 * v11] )
        {
          v42 = *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] + 1;
          *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = v42;
          if ( v42 >= 2 )
          {
            *(_DWORD *)&this->m_list.m_column[5].head[4 * v11 + 52] = 2;
            *(_DWORD *)&this->m_list.m_column[6].head[4 * v11 + 52] = 0;
          }
          goto LABEL_124;
        }
        v5 = *(float *)&this->m_list.m_column[6].head[8 * v11];
        if ( v5 >= *(float *)&this->m_list.m_column[6].head[8 * v11 + 28] )
          goto LABEL_124;
      }
LABEL_125:
      if ( ++v11 >= *(_DWORD *)&this->m_list.m_column[6].head[48] )
      {
        v10 = PtInRect;
        break;
      }
    }
  }
  if ( LOBYTE(this->m_list.m_scrollRc.top)
    && (int)this->m_list.m_column[5].items.m_pData >= *(_DWORD *)&this->m_list.m_column[6].head[48] )
  {
    (*(void ( **)(int *, int))this->m_maxlen)(&this->m_maxlen, 1);
    (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[1].head[60])(&this->m_list.m_column[1].head[60], 0);
    (**(void ( ***)(char *, _DWORD))&this->m_list.m_column[3].head[44])(&this->m_list.m_column[3].head[44], 0);
  }
  if ( *((_DWORD *)this + 541) == 2 )
  {
    sprintf(
      (char *const)&this->m_bk.m_rect.top,
      "\\n\\n %s %d %s\\n %s %d \n",
      (const char *)dword_DD353C,
      this->m_list.m_column[5].items.m_nSize,
      (const char *)dword_DDC23C,
      (const char *)dword_DD363C,
      this->m_list.m_column[5].items.capacity);
    ((UICaption *)&this->m_list.m_scrollRc.right)->SetEnable((int)&this->m_bk.m_rect.top, 0);
    (*(void ( **)(LONG *, int))this->m_list.m_scrollRc.right)(&this->m_list.m_scrollRc.right, 1);
    v46 = UIQuadManager::GetInstance();
    ((UIRenderObj *)v46)->_UIRenderObj();
    LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 1;
  }
  v47 = *(_DWORD *)&this->m_list.m_column[6].head[48];
  if ( (int)this->m_list.m_column[5].items.m_pData >= v47 && v47 > 0 )
    this->m_list.m_column[5].items.m_pData = 0;
  ((GRPinput *)&g_Input)->GetCursorPos();
  v48 = this->m_ani.m_texarray.m_ptex[3];
  if ( v48 == (gbTexture *)1 )
  {
    if ( v10((const RECT *)&this->m_list.m_column[5].head[36], Point) )
      this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)2;
  }
  else if ( v48 == (gbTexture *)2 && !v10((const RECT *)&this->m_list.m_column[5].head[36], Point) )
  {
    this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)1;
  }
  if ( LOBYTE(this->m_ani.m_texarray.m_ptex[2]) )
  {
    if ( !v10((const RECT *)&this->m_list.m_column[5].head[36], Point) && g_Input.KeyInfo[1].PressTime == 1
      || v10((const RECT *)&this->m_list.m_column[5].head[36], Point) && g_Input.KeyInfo[0].PressTime == 1 )
    {

      return v5;
    }
    if ( *(int *)&this->m_list.m_column[6].head[48] <= 0 )

    goto LABEL_149;
  }
  if ( v10((const RECT *)&this->m_list.m_column[5].head[36], Point)
    || g_Input.KeyInfo[1].PressTime != 1
    || !*((_BYTE *)this + 2184) )
  {
LABEL_149:
    ((UIListBox *)this)->Update(SLODWORD(st6_0), SHIDWORD(st6_0));
    return v5;
  }

  v53 = off_5ED1D0;
  v49 = (CCBStageRole *)CScreenMode::GetInstance();
  ((CCBStageRole *)v49)->PlaySound(v53, v54);
  return v5;
}

// 0x0052AA50
int UIRoleSelectDialog::SubtractFromStats()
{
  ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom += this->m_list.m_column[5].items.capacity;
  *(_DWORD *)&Buffer.m_partyActor.m_curact[39] -= *(_DWORD *)&this->m_list.m_column[1].head[24];
  if ( *(int *)&Buffer.m_partyActor.m_curact[39] <= 0 )
    *(_DWORD *)&Buffer.m_partyActor.m_curact[39] = 1;
  if ( this->m_ani.m_texarray.m_ptex[3] == (gbTexture *)2 )
    this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)1;
  return ((CGameData *)&g_gamefrm)->Load(0);
}

// 0x0052AAB0
int UIRoleSelectDialog::ProcessDialog()
{
  char *v3; // edi
  char *v4; // esi
  double v5; // st7
  DWORD Time; // eax
  int v7; // eax
  UIStatic *v8; // esi
  int *p_m_itemheight; // edi
  float *p_m_ratioh; // esi
  int *p_width; // edi
  CScreenMode *Instance; // eax
  char *v13; // [esp-0x10] [ebp-0x14]
  int nVal; // [esp+0xC] [ebp+0x8]
  char *nMsg; // [esp+0x10] [ebp+0xC]
  int nMsga; // [esp+0x10] [ebp+0xC]
  int nMsgb; // [esp+0x10] [ebp+0xC]
  float nMsge; // [esp+0x10] [ebp+0xC]
  int nMsgc; // [esp+0x10] [ebp+0xC]
  int nMsgd; // [esp+0x10] [ebp+0xC]
  int wParam; // [esp+0x14] [ebp+0x10]

  if ( nVal != 1000 )
  {
    if ( nVal != 1009 )
      return ((PalScript *)this)->OnMessage(nVal, (int)nMsg, wParam);
    if ( nMsg == &byte_80AB20 )
    {
      (*(void ( **)(int *, _DWORD))this->m_maxlen)(&this->m_maxlen, 0);
      (*(void ( **)(LONG *, _DWORD))this->m_list.m_scrollRc.right)(&this->m_list.m_scrollRc.right, 0);
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
  v3 = &this->m_list.m_column[7].head[32];
  v4 = &this->m_list.m_column[6].head[28];
  do
  {
    *((_DWORD *)v3 - 37) = 0;
    *((_DWORD *)v4 - 8) = 1137180672;
    *((_DWORD *)v4 - 1) = 1137180672;
    *((_DWORD *)v4 - 7) = 1133903872;
    *(_DWORD *)v4 = 1133903872;
    this->m_list.m_column[6].head[nMsga + 20] = 1;
    *(_DWORD *)v3 = 0;
    *((_DWORD *)v4 + 16) = 0;
    *((_DWORD *)v4 + 17) = 1065353216;
    *((_DWORD *)v4 + 10) = *((_DWORD *)v4 - 8);
    *((_DWORD *)v4 + 11) = *((_DWORD *)v4 - 7);
    *((_DWORD *)v3 - 16) = 0;
    v3 += 4;
    v4 += 8;
    v5 = (double)(rand() % 12 - 6) * 0.1 + 0.80000001;
    *((float *)v3 + 2) = v5;
    *((float *)v3 + 5) = v5 * 1.6;
    *((_DWORD *)v3 + 8) = 0;
    *((_DWORD *)v3 + 11) = 0;
    ++nMsga;
  }
  while ( nMsga < 3 );
  LOBYTE(this->m_list.m_scrollRc.top) = 0;
  LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 0;
  this->m_ani.m_texarray.m_ptex[3] = 0;
  this->m_list.m_column[5].items.m_nSize = 0;
  this->m_list.m_column[5].items.capacity = 0;
  this->m_list.m_column[5].items.m_pData = 0;
  this->m_list.m_column[5].items.m_needscriptdel = 0;
  Time = timeGetTime();
  CRT_set_new_handler(Time);
  nMsgb = (__int64)(*(float *)&this->m_list.m_firstshow * 100.0);
  if ( nMsgb <= 0
    || (nMsge = (double)nMsgb * 10.24,
        ++*(_DWORD *)&g_TempBuffer1024[912],
        unk_5DFDEC = 214013 * unk_5DFDEC + 2531011,
        (((int)unk_5DFDEC >> 16) & 0x3FF) >= (int)nMsge) )
  {
    LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 1;
  }
  else
  {
    nMsgc = 0;
    *(_DWORD *)&this->m_list.m_column[6].head[48] = 1;
    ++*(_DWORD *)&g_TempBuffer1024[912];
    unk_5DFDEC = 214013 * unk_5DFDEC + 2531011;
    if ( (((int)unk_5DFDEC >> 16) & 0x3FF) < (int)102.39999 )
      *(_DWORD *)&this->m_list.m_column[6].head[48] = 3;
    v7 = *(_DWORD *)&this->m_list.m_column[6].head[48];
    if ( v7 == 3 )
    {
      this->m_list.m_column[7].items.capacity = 1;
      this->m_list.m_column[7].width = rand() % 100 + 100;
      ((UIStatic *)&this->m_face.m_ratioh)->CreateFromTemplate();
      (*(void ( **)(float *, int))LODWORD(this->m_face.m_ratioh))(&this->m_face.m_ratioh, 1);
      nMsgd = 1;
      if ( *(int *)&this->m_list.m_column[6].head[48] > 1 )
      {
        v8 = (UIStatic *)(&this->m_static.m_bInvalidate + 20);
        p_m_itemheight = &this->m_list.m_itemheight;
        do
        {
          *(p_m_itemheight - 3) = 0;
          *p_m_itemheight = rand() % 20 + 1;
          ((UIStatic *)v8)->CreateFromTemplate();
// [VFTABLE] ((void ( *)(UIStatic *, int))v8->__vftable->ShowWindow)(v8, 1);
          ++p_m_itemheight;
          v8 = (UIStatic *)((char *)v8 + 184);
          ++nMsgd;
        }
        while ( nMsgd < *(_DWORD *)&this->m_list.m_column[6].head[48] );
      }
    }
    else if ( v7 > 0 )
    {
      p_m_ratioh = &this->m_face.m_ratioh;
      p_width = &this->m_list.m_column[7].width;
      do
      {
        *(p_width - 3) = 0;
        *p_width = rand() % 20 + 1;
        ((UIStatic *)p_m_ratioh)->CreateFromTemplate();
        (**(void ( ***)(float *, int))p_m_ratioh)(p_m_ratioh, 1);
        ++p_width;
        p_m_ratioh += 46;
        ++nMsgc;
      }
      while ( nMsgc < *(_DWORD *)&this->m_list.m_column[6].head[48] );
    }
    LOBYTE(this->m_ani.m_texarray.m_ptex[2]) = 0;
    v13 = off_5ED1D0;
    Instance = CScreenMode::GetInstance();
    ((CScreenMode *)Instance)->AudioSetPosition(v13, 0);
  }
  g_nSceneState = 1;
  this->m_ani.m_texarray.m_ptex[3] = (gbTexture *)2;
  return 1;
}

// 0x0052BBD0
void UIRoleSelectDialog::DestroyStatics()
{
  sub_4422E0(this);
  sub_4422E0(&this->m_bk.m_currect.right);
  sub_4422E0(&this->m_ani.m_childs);
  sub_4422E0(&this->m_face.m_rect.right);
  ((UIButton *)&this->m_static.m_id)->ctor_17();
  sub_4422E0(&this->m_list.m_scrollbar.m_bPress);
  sub_4422E0(&this->m_list.m_scrollbar.m_texarray.m_ptex[7]);
  ((UIButton *)&this->m_list.m_column[0].head[16])->ctor_17();
  sub_4422E0(&this->m_list.m_column[3].head[8]);
}

// 0x0052BC90
void UIRoleSelectDialog::DestroyFrames()
{
  ((UIFrameWnd *)&this->m_list.m_column[3].head[8])->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_list.m_column[0].head[16])->_UIButton();
  ((UIFrameWnd *)&this->m_list.m_scrollbar.m_texarray.m_ptex[7])->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_list.m_scrollbar.m_bPress)->UIFrameWnd::_UIFrameWnd();
  ((UIButton *)&this->m_static.m_id)->_UIButton();
  ((UIFrameWnd *)&this->m_face.m_rect.right)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_ani.m_childs)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)&this->m_bk.m_currect.right)->UIFrameWnd::_UIFrameWnd();
  ((UIFrameWnd *)this)->UIFrameWnd::_UIFrameWnd();
}

// 0x0052D200
char UIRoleSelectDialog::IsRoleSelectable(int nVal)
{
  int v3; // eax
  int *i; // ecx

  if ( *((_BYTE *)&((RoleSystem *)&stru_C059A0)->m_teamSlots[-9] + nVal) )
  {
    v3 = 0;
    for ( i = &this->m_mode + 25; *i == nVal; ++i )
    {
      if ( ++v3 >= 4 )
        return 1;
    }
  }
  return 0;
}
