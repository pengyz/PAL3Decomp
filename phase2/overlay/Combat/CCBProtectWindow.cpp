#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBProtectWindow.h"
#include "Combat/CCBUI.h"
#include "Misc/SceneInfo.h"
#include "Scene/SceneObj.h"
#include "Misc/UIButton.h"
#include "Misc/UIProgressBar.h"
#include "Misc/UIPushButton.h"
#include "Misc/UIStatic.h"
#include "UI/UIWnd.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_519180(...);

// 0x0043D920
void CCBProtectWindow::Destroy_D920()
{
  gbRefObject *m_pWHFace; // ecx

  m_pWHFace = (gbRefObject *)this->m_pWHFace;
  if ( m_pWHFace )
  {
    (((gbRefObject *)m_pWHFace))->gbRefObject::Release();
    this->m_pWHFace = ((UIPushButton *)0);
  }
}

// 0x00449BE0
char CCBProtectWindow::ValidateSlot(unsigned int dwVal)
{
  char result; // al

  result = dwVal;
  if ( dwVal <= 0x25 )
    return (((SceneInfo *)(&this->m_pOk + 67)))->SceneInfo::ProcessCollision(*((_DWORD *)&this->m_pOk + 119 * dwVal + 108), *((_DWORD *)&this->m_pOk + 119 * dwVal + 109));
  return result;
}

// 0x0044A820
int CCBProtectWindow::GetUIElements(float fVal, int nVal)
{
  float v4; // st7
  UIProgressBar *m_pWPXLove; // edx
  UIPushButton *m_pWPXFace; // eax

  if ( !this->m_bvisible )
    return 0;
  v4 = fVal + *(float *)&this->m_pOk;
  m_pWPXLove = (UIProgressBar *)this->m_pWPXLove;
  m_pWPXFace = (UIPushButton *)this->m_pWPXFace;
  *(float *)&this->m_pOk = v4;
  if ( (int)m_pWPXLove > (int)m_pWPXFace || v4 <= 2.0f )
    return 1;
  this->m_pOk = ((UIButton *)0);
  this->m_pWPXLove = ((UIProgressBar *)((UIProgressBar *)((char *)((UIWnd *)m_pWPXLove) + 1)));
  return 1;
}

// 0x0044A870
void CCBProtectWindow::RenderText()
{
  UIPushButton *m_pWPXFace; // ebp
  UIProgressBar *m_pWPXLove; // eax
  int v4; // edi
  float v5; // st7
  float v6; // st7
  int v7; // edi

  if ( this->m_bvisible )
  {
    if ( this->m_pWHFace )
    {
      m_pWPXFace = (UIPushButton *)this->m_pWPXFace;
      if ( (int)m_pWPXFace > 0 )
      {
        m_pWPXLove = (UIProgressBar *)this->m_pWPXLove;
        if ( (int)m_pWPXLove > (int)m_pWPXFace )
        {
          v5 = *(float *)&this->m_pOk - 5.0f;
          if ( v5 <= 0.0f )
            v5 = 0.0f;
          v6 = 1.0f - v5 * 0.3333333432674408f;
          if ( v6 < 0.0f )
            v6 = 0.0f;
          v7 = 0;
          do
            (((UIPushButton *)this))->UIPushButton::RenderTile(v7++, (__int64)(v6 * 255.0));
          while ( v7 <= (int)this->m_pWPXFace );
          if ( !(unsigned __int8)(__int64)(v6 * 255.0) )
          {
            (*(void ( **)(CCBProtectWindow *))(*(_DWORD *)((UIWnd *)this) + 12))(this);
            (**(void ( ***)(CCBProtectWindow *, _DWORD))((UIWnd *)this))((CCBProtectWindow *)(this), (_DWORD)(0));
          }
        }
        else
        {
          v4 = 0;
          if ( (int)m_pWPXLove > 0 )
          {
            do
              (((UIPushButton *)this))->UIPushButton::RenderTile(v4++, 255);
            while ( v4 < (int)this->m_pWPXLove );
          }
          (((UIPushButton *)this))->UIPushButton::RenderTile((int)this->m_pWPXLove, (__int64)(*(float *)&this->m_pOk / 2.0 * 255.0));
        }
      }
    }
  }
}

// 0x005164D0
void CCBProtectWindow::Destroy()
{
  UIStatic *m_pBack; // ecx
  UIPushButton **p_m_pWHFace; // esi
  int v4; // edi
  int v5; // ecx
  UIButton **v6; // esi
  int v7; // edi
  int v8; // ecx
  UIButton *v9; // ecx
  UIButton *v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  int v34; // ecx
  int v35; // ecx
  int v36; // ecx
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  UIButton **v42; // esi
  int v43; // edi
  int v44; // ecx
  int v45; // ecx
  int v46; // ecx
  int v47; // ecx
  int v48; // ecx
  int v49; // ecx
  int v50; // ecx
  int v51; // ecx
  UIButton **v52; // esi
  int v53; // edi

  // [overlay-fix 2026-10-27] C2065: Destroy__ovl_03 无定义/声明（IDA overlay 合成名）——待归属定谳
  // Destroy__ovl_03((int)this);
  m_pBack = (UIStatic *)this->m_pBack;
  if ( m_pBack )
  {
    (*(void ( **)(UIStatic *, int))(*(_DWORD *)((UIWnd *)m_pBack) + 20))(m_pBack, 1);
    this->m_pBack = ((UIStatic *)0);
  }
  p_m_pWHFace = (UIPushButton **)&this->m_pWHFace;
  v4 = 11;
  do
  {
    if ( *p_m_pWHFace )
    {
      (*(void ( **)(UIPushButton *, int))(*(_DWORD *)((UIWnd *)(*p_m_pWHFace)) + 20))(*p_m_pWHFace, 1);
      *p_m_pWHFace = 0;
    }
    ++p_m_pWHFace;
    --v4;
  }
  while ( v4 );
  v5 = *((_DWORD *)&this->m_pOk + 244);
  if ( v5 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v5 + 20))(v5, 1);
    *((_DWORD *)&this->m_pOk + 244) = 0;
  }
  v6 = (UIButton **)(&this->m_pOk + 232);
  v7 = 4;
  do
  {
    v8 = (int)*(v6 - 225);
    if ( v8 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v8 + 20))(v8, 1);
      *(v6 - 225) = 0;
    }
    if ( *v6 )
    {
      (*(void ( **)(UIButton *, int))(*(_DWORD *)((UIWnd *)(*v6)) + 20))(*v6, 1);
      *v6 = 0;
    }
    v9 = (UIButton *)v6[4];
    if ( v9 )
    {
      (*(void ( **)(UIButton *, int))(*(_DWORD *)((UIWnd *)v9) + 20))(v9, 1);
      v6[4] = 0;
    }
    v10 = (UIButton *)v6[8];
    if ( v10 )
    {
      (*(void ( **)(UIButton *, int))(*(_DWORD *)((UIWnd *)v10) + 20))(v10, 1);
      v6[8] = 0;
    }
    v11 = (int)*(v6 - 211);
    if ( v11 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v11 + 20))(v11, 1);
      *(v6 - 211) = 0;
    }
    v12 = (int)*(v6 - 200);
    if ( v12 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v12 + 20))(v12, 1);
      *(v6 - 200) = 0;
    }
    v13 = (int)*(v6 - 189);
    if ( v13 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v13 + 20))(v13, 1);
      *(v6 - 189) = 0;
    }
    v14 = (int)*(v6 - 178);
    if ( v14 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v14 + 20))(v14, 1);
      *(v6 - 178) = 0;
    }
    v15 = (int)*(v6 - 145);
    if ( v15 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v15 + 20))(v15, 1);
      *(v6 - 145) = 0;
    }
    v16 = (int)*(v6 - 134);
    if ( v16 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v16 + 20))(v16, 1);
      *(v6 - 134) = 0;
    }
    v17 = (int)*(v6 - 167);
    if ( v17 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v17 + 20))(v17, 1);
      *(v6 - 167) = 0;
    }
    v18 = (int)*(v6 - 156);
    if ( v18 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v18 + 20))(v18, 1);
      *(v6 - 156) = 0;
    }
    v19 = (int)*(v6 - 123);
    if ( v19 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v19 + 20))(v19, 1);
      *(v6 - 123) = 0;
    }
    v20 = (int)*(v6 - 112);
    if ( v20 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v20 + 20))(v20, 1);
      *(v6 - 112) = 0;
    }
    v21 = (int)*(v6 - 101);
    if ( v21 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v21 + 20))(v21, 1);
      *(v6 - 101) = 0;
    }
    v22 = (int)*(v6 - 90);
    if ( v22 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v22 + 20))(v22, 1);
      *(v6 - 90) = 0;
    }
    v23 = (int)*(v6 - 79);
    if ( v23 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v23 + 20))(v23, 1);
      *(v6 - 79) = 0;
    }
    v24 = (int)*(v6 - 68);
    if ( v24 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v24 + 20))(v24, 1);
      *(v6 - 68) = 0;
    }
    v25 = (int)*(v6 - 57);
    if ( v25 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v25 + 20))(v25, 1);
      *(v6 - 57) = 0;
    }
    v26 = (int)*(v6 - 46);
    if ( v26 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v26 + 20))(v26, 1);
      *(v6 - 46) = 0;
    }
    v27 = (int)*(v6 - 35);
    if ( v27 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v27 + 20))(v27, 1);
      *(v6 - 35) = 0;
    }
    v28 = (int)*(v6 - 24);
    if ( v28 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v28 + 20))(v28, 1);
      *(v6 - 24) = 0;
    }
    v29 = (int)*(v6 - 13);
    if ( v29 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v29 + 20))(v29, 1);
      *(v6 - 13) = 0;
    }
    ++v6;
    --v7;
  }
  while ( v7 );
  v30 = *((_DWORD *)&this->m_pOk + 245);
  if ( v30 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v30 + 20))(v30, 1);
    *((_DWORD *)&this->m_pOk + 245) = 0;
  }
  v31 = *((_DWORD *)&this->m_pOk + 246);
  if ( v31 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v31 + 20))(v31, 1);
    *((_DWORD *)&this->m_pOk + 246) = 0;
  }
  v32 = *((_DWORD *)&this->m_pOk + 230);
  if ( v32 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v32 + 20))(v32, 1);
    *((_DWORD *)&this->m_pOk + 230) = 0;
  }
  v33 = *((_DWORD *)&this->m_pOk + 231);
  if ( v33 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v33 + 20))(v33, 1);
    *((_DWORD *)&this->m_pOk + 231) = 0;
  }
  v34 = *((_DWORD *)&this->m_pOk + 248);
  if ( v34 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v34 + 20))(v34, 1);
    *((_DWORD *)&this->m_pOk + 248) = 0;
  }
  v35 = *((_DWORD *)&this->m_pOk + 249);
  if ( v35 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v35 + 20))(v35, 1);
    *((_DWORD *)&this->m_pOk + 249) = 0;
  }
  v36 = *((_DWORD *)&this->m_pOk + 250);
  if ( v36 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v36 + 20))(v36, 1);
    *((_DWORD *)&this->m_pOk + 250) = 0;
  }
  v37 = *((_DWORD *)&this->m_pOk + 251);
  if ( v37 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v37 + 20))(v37, 1);
    *((_DWORD *)&this->m_pOk + 251) = 0;
  }
  v38 = *((_DWORD *)&this->m_pOk + 252);
  if ( v38 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v38 + 20))(v38, 1);
    *((_DWORD *)&this->m_pOk + 252) = 0;
  }
  v39 = *((_DWORD *)&this->m_pOk + 253);
  if ( v39 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v39 + 20))(v39, 1);
    *((_DWORD *)&this->m_pOk + 253) = 0;
  }
  v40 = *((_DWORD *)&this->m_pOk + 254);
  if ( v40 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v40 + 20))(v40, 1);
    *((_DWORD *)&this->m_pOk + 254) = 0;
  }
  v41 = *((_DWORD *)&this->m_pOk + 255);
  if ( v41 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v41 + 20))(v41, 1);
    *((_DWORD *)&this->m_pOk + 255) = 0;
  }
  v42 = (UIButton **)(&this->m_pOk + 16);
  v43 = 5;
  do
  {
    v44 = (int)*(v42 - 5);
    if ( v44 )
    {
      (*(void ( **)(int, int))(*(_DWORD *)v44 + 20))(v44, 1);
      *(v42 - 5) = 0;
    }
    if ( *v42 )
    {
      (*(void ( **)(UIButton *, int))(*(_DWORD *)((UIWnd *)(*v42)) + 20))(*v42, 1);
      *v42 = 0;
    }
    ++v42;
    --v43;
  }
  while ( v43 );
  v45 = *((_DWORD *)&this->m_pOk + 256);
  if ( v45 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v45 + 20))(v45, 1);
    *((_DWORD *)&this->m_pOk + 256) = 0;
  }
  v46 = *((_DWORD *)&this->m_pOk + 257);
  if ( v46 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v46 + 20))(v46, 1);
    *((_DWORD *)&this->m_pOk + 257) = 0;
  }
  v47 = *((_DWORD *)&this->m_pOk + 258);
  if ( v47 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v47 + 20))(v47, 1);
    *((_DWORD *)&this->m_pOk + 258) = 0;
  }
  v48 = *((_DWORD *)&this->m_pOk + 259);
  if ( v48 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v48 + 20))(v48, 1);
    *((_DWORD *)&this->m_pOk + 259) = 0;
  }
  v49 = *((_DWORD *)&this->m_pOk + 260);
  if ( v49 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v49 + 20))(v49, 1);
    *((_DWORD *)&this->m_pOk + 260) = 0;
  }
  v50 = *((_DWORD *)&this->m_pOk + 261);
  if ( v50 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v50 + 20))(v50, 1);
    *((_DWORD *)&this->m_pOk + 261) = 0;
  }
  v51 = *((_DWORD *)&this->m_pOk + 262);
  if ( v51 )
  {
    (*(void ( **)(int, int))(*(_DWORD *)v51 + 20))(v51, 1);
    *((_DWORD *)&this->m_pOk + 262) = 0;
  }
  v52 = (UIButton **)(&this->m_pOk + 263);
  v53 = 4;
  do
  {
    if ( *v52 )
    {
      (*(void ( **)(UIButton *, int))(*(_DWORD *)((UIWnd *)(*v52)) + 20))(*v52, 1);
      *v52 = 0;
    }
    ++v52;
    --v53;
  }
  while ( v53 );
}

// 0x00518E30
BOOL CCBProtectWindow::ShowAndNotify(int nVal, int nVal2)
{
  sub_519180();
  (((CCBUI *)this))->CCBUI::ShowDialogWindow();
  (((CCBUI *)this))->CCBUI::HideAll();
  return (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
}

// 0x0051D6E0
CCBProtectWindow::CCBProtectWindow()
{
  dword_17AD59C = 1094713344;
}

// 0x0051D6F0
// attributes: thunk
CCBProtectWindow::~CCBProtectWindow()
{
  this->CCBProtectWindow::Reset();
}

// 0x0051D700
void CCBProtectWindow::Reset()
{
  flt_17AD598 = 12.0 + 12.0;
}

// 0x0051F0A0
int CCBProtectWindow::OnCommand(int nVal, int nVal2)
{
  int v4; // eax
  const void *v5; // esi
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx

  v4 = *((_DWORD *)&this[3].m_pOk + 14);
  v5 = (const void *)*((_DWORD *)&this[3].m_pOk + 15);
  v6 = *((_DWORD *)&(&this[124].m_pOk)[1] + 52);
  *((_DWORD *)&this[131].m_pOk + 172) = *((_DWORD *)&(&this[124].m_pOk)[1] + 46);
  *((_DWORD *)&this[131].m_pOk + 174) = v4;
  v7 = *((_DWORD *)&(&this[124].m_pOk)[1] + 49);
  qmemcpy(&this[131].m_pOk + 175, v5, 0xDCu);
  v8 = *((_DWORD *)&(&this[124].m_pOk)[1] + 50);
  *((_DWORD *)&this[192].m_pOk + 499) = v6;
  v9 = *((_DWORD *)&(&this[124].m_pOk)[1] + 51);
  *((_DWORD *)&this[192].m_pOk + 496) = v7;
  *((_DWORD *)&this[192].m_pOk + 497) = v8;
  *((_DWORD *)&this[192].m_pOk + 498) = v9;
  StopSceneScripts((const char *)nVal);
  (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return 1;
}
