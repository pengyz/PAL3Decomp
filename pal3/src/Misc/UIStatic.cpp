#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UIStatic.h"

// Forward declarations for unnamed functions
void sub_4422E0(void *_this); // from annotations
int sub_445AA0(void); // from annotations

int crt_sub_00540070(void); // from annotations

// Unnamed globals (extern)
extern char byte_5967B0[3];
extern void * off_5974E0;
extern TextureLibDataBase stru_1894B78;
extern int unk_D90D3C;

// 0x0043D920
void UIStatic::Destroy()
{
  float m_ratiow; // ecx

  m_ratiow = this->m_ratiow;
  if ( m_ratiow != 0.0 )
  {
    ((gbRefObject *)LODWORD(m_ratiow))->Release();
    this->m_ratiow = 0.0;
  }
}

// 0x0043DAB0
void UIStatic::RenderQuadSlice(int *pnVal, int nVal)
{
  float m_ratioh; // eax
  float v5; // ecx
  double v6; // st7
  double v7; // st7
  int v8; // eax
  double v9; // st6
  int v10; // edx
  float m_ratiow; // ecx
  double v12; // st7
  double v13; // st7
  int v14; // edx
  double v15; // st6
  int v16; // eax
  gbDynVertBuf *DynVertBuf; // eax
  double v18; // st7
  double v19; // st7
  float v20; // [esp+0x8] [ebp-0x74]
  float v21; // [esp+0x8] [ebp-0x74]
  struct gbUIQuad v22; // [esp+0x10] [ebp-0x6C] BYREF
  struct gbTextureArray v23; // [esp+0x38] [ebp-0x44] BYREF

  v22.color = -1;
  v22.z = 0.0;
  m_ratioh = this->m_ratioh;
  if ( m_ratioh == 0.0 )
  {
    m_ratiow = this->m_ratiow;
    v12 = (double)*(int *)(LODWORD(m_ratiow) + 24);
    v21 = (double)(int)this->pDebugTex / v12;
    v13 = (double)(pnVal[2] - *pnVal) / v12;
    if ( v21 < v13 )
      v13 = v21;
    v14 = pnVal[3];
    v15 = (double)nVal * v21;
    v22.su = v15;
    v22.eu = v15 + v13;
    v16 = *(_DWORD *)(LODWORD(m_ratiow) + 28);
    v22.sv = 0.0;
    v22.ev = (double)(v14 - pnVal[1]) / (double)*(int *)(LODWORD(m_ratiow) + 28) - 0.5 / (double)v16;
  }
  else if ( LODWORD(m_ratioh) == 1 )
  {
    v5 = this->m_ratiow;
    v6 = (double)*(int *)(LODWORD(v5) + 28);
    v20 = (double)this->m_align / v6;
    v7 = (double)(pnVal[3] - pnVal[1]) / v6;
    if ( v20 < v7 )
      v7 = v20;
    v8 = pnVal[2];
    v9 = 1.0 - (double)nVal * v20;
    v22.sv = v9;
    v22.ev = v9 - v7;
    v10 = *(_DWORD *)(LODWORD(v5) + 24);
    v22.su = 0.0;
    v22.eu = (double)(v8 - *pnVal) / (double)*(int *)(LODWORD(v5) + 24) - 0.5 / (double)v10;
  }
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  v18 = (double)*pnVal;
  v23.pTexPt[0] = (gbTexture *)LODWORD(this->m_ratiow);
  v22.sx = v18;
  v22.ey = (float)pnVal[1];
  v19 = (double)pnVal[2];
  v23.nTex = 1;
  v22.ex = v19;
  v22.sy = (float)pnVal[3];
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v22, 1, g_pRenderEffect_189504C, &v23);
}

// 0x00440740
UIStatic::UIStatic()
{
  Parent_Data **p_m_fonttype; // eax
  int v3; // ecx

  sub_445AA0();
  LOBYTE(this->pDebugTex) = 0;
  BYTE1(this->pDebugTex) = 0;
  this->m_ratioh = 0.0;
  p_m_fonttype = &this->m_fonttype;
  v3 = 2;
  do
  {
    *(p_m_fonttype - 2) = 0;
    *p_m_fonttype++ = 0;
    --v3;
  }
  while ( v3 );
  memset(&this->m_ppic, 0, 0x80u);
  LODWORD(this->m_ratiow) = 1;
  this->m_pbk = 0;
  this->m_pbkInfo = 0;
  *(_DWORD *)&this->m_text[8] = 0;
  *(_DWORD *)&this->m_text[12] = 0;
}

// 0x004407C0
void UIStatic::_UIStatic()
{

// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x00440810
gbVFileSystem * UIStatic::CreateWithTextures(
        
        int id,
        void *pRect,
        gbVFileSystem *parent,
        const char *pszName,
        char pData)
{
  gbVFileSystem *result; // eax
  int v7; // edi
  PalScript *v8; // ebp
  char *p_todo_054; // esi
  int v10; // ebp
  CHAR *v11; // eax
  Parent_Data *ParentData; // eax
  OpenBaseFile v13; // [esp+0x8] [ebp-0x118] BYREF
  PalScript *v14; // [esp+0xC] [ebp-0x114]
  char Buffer[260]; // [esp+0x10] [ebp-0x110] BYREF
  int v16; // [esp+0x11C] [ebp-0x4]

  result = parent;
  v7 = 0;
  v8 = (PalScript *)this;
  v14 = (PalScript *)this;
  if ( parent && pszName )
  {
    v16 = 0;
    p_todo_054 = (char *)&v8->_todo_054;
    do
    {
      if ( *(_DWORD *)p_todo_054 )
        ((gbRefObject *)*(gbRefObject **)p_todo_054)->Release();
      sprintf(Buffer, "%s%d.tga", pszName, v7);
      if ( pData )
      {
        v10 = *(_DWORD *)gfxMgr;
        v11 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(Buffer);
        *(_DWORD *)p_todo_054 = (*(int ( **)(gbGfxManager *, CHAR *))(v10 + 8))(gfxMgr, v11);
        ParentData = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(Buffer);
        v8 = v14;
        *((_DWORD *)p_todo_054 + 2) = ParentData;
      }
      else
      {
        *(_DWORD *)p_todo_054 = (*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, Buffer);
      }
      if ( *(_DWORD *)p_todo_054 )
        ((gbTexture *)*(gbTexture **)p_todo_054)->LoadTexture(1);
      ++v7;
      p_todo_054 += 4;
    }
    while ( v7 < 2 );
    ((PalScript *)v8)->Create(id, (tagRECT *)pRect, (int)parent);
    *((_BYTE *)&v8->m_RoleArray + 12) = 0;
    BYTE2(v8->_todo_044) = 1;
    v16 = -1;
  }
  return result;
}

// 0x00440960
void UIStatic::FormatText()
{
  gbRefObject *v2; // ecx
  int v3; // ebx
  CHAR *v4; // eax
  gbTexture *v5; // ecx
  OpenBaseFile v6; // [esp+0x8] [ebp-0x10] BYREF
  int v7; // [esp+0x14] [ebp-0x4]
  const CHAR *lpString; // [esp+0x1C] [ebp+0x4]
  char v9; // [esp+0x20] [ebp+0x8]

  v2 = *(gbRefObject **)&this->m_text[8];
  v7 = 0;
  if ( v2 )
    ((gbRefObject *)v2)->Release();
  if ( v9 )
  {
    v3 = *(_DWORD *)gfxMgr;
    v4 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(lpString);
    *(_DWORD *)&this->m_text[8] = (*(int ( **)(gbGfxManager *, CHAR *))(v3 + 8))(gfxMgr, v4);
    *(_DWORD *)&this->m_text[12] = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(lpString);
  }
  else
  {
    *(_DWORD *)&this->m_text[8] = (*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(
                                    gfxMgr,
                                    lpString);
  }
  v5 = *(gbTexture **)&this->m_text[8];
  if ( v5 )
    ((gbTexture *)v5)->LoadTexture(1);
  v7 = -1;
}

// 0x00440A20
gbVFileSystem * UIStatic::LoadResource(LPCSTR lpString, char nFlags)
{
  gbRefObject *m_textx; // ecx
  int v5; // ebx
  CHAR *v6; // eax
  gbTexture *v7; // ecx
  gbVFileSystem *result; // eax
  OpenBaseFile v9; // [esp+0x8] [ebp-0x10] BYREF
  int v10; // [esp+0x14] [ebp-0x4]

  m_textx = (gbRefObject *)this->m_textx;
  v10 = 0;
  if ( m_textx )
    ((gbRefObject *)m_textx)->Release();
  if ( nFlags )
  {
    v5 = *(_DWORD *)gfxMgr;
    v6 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(lpString);
    this->m_textx = (*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6);
    this->m_fonttype = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(lpString);
  }
  else
  {
    this->m_textx = (*(int ( **)(gbGfxManager *, LPCSTR))(*(_DWORD *)gfxMgr + 8))(gfxMgr, lpString);
  }
  v7 = (gbTexture *)this->m_textx;
  if ( v7 )
    ((gbTexture *)v7)->LoadTexture(1);
  v10 = -1;
  return result;
}

// 0x00440AE0
void UIStatic::LoadTexture()
{
  gbRefObject *m_texty; // ecx
  int v3; // ebx
  CHAR *v4; // eax
  gbTexture *v5; // ecx
  OpenBaseFile v6; // [esp+0x8] [ebp-0x10] BYREF
  int v7; // [esp+0x14] [ebp-0x4]
  const CHAR *lpString; // [esp+0x1C] [ebp+0x4]
  char v9; // [esp+0x20] [ebp+0x8]

  m_texty = (gbRefObject *)this->m_texty;
  v7 = 0;
  if ( m_texty )
    ((gbRefObject *)m_texty)->Release();
  if ( v9 )
  {
    v3 = *(_DWORD *)gfxMgr;
    v4 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(lpString);
    this->m_texty = (*(int ( **)(gbGfxManager *, CHAR *))(v3 + 8))(gfxMgr, v4);
    *(_DWORD *)this->m_text = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(lpString);
  }
  else
  {
    this->m_texty = (*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, lpString);
  }
  v5 = (gbTexture *)this->m_texty;
  if ( v5 )
    ((gbTexture *)v5)->LoadTexture(1);
  v7 = -1;
}

// 0x00440BA0
int UIStatic::OnMessage()
{
  int *p_m_textx; // esi
  int v3; // ebx
  int result; // eax

  p_m_textx = &this->m_textx;
  v3 = 2;
  do
  {
    if ( *p_m_textx )
    {
      ((gbRefObject *)*p_m_textx)->Release();
      *p_m_textx = 0;
    }
    ++p_m_textx;
    --v3;
  }
  while ( v3 );
// [VFTABLE] ((UIWnd *)&this->__vftable)->HideAll();
  return result;
}

// 0x00440CE0
void UIStatic::SetText()
{
  gbRefObject *m_pbk; // ecx
  int v3; // ebx
  CHAR *v4; // eax
  gbTexture *v5; // ecx
  OpenBaseFile v6; // [esp+0x8] [ebp-0x110] BYREF
  char Buffer[256]; // [esp+0xC] [ebp-0x10C] BYREF
  int v8; // [esp+0x114] [ebp-0x4]
  const CHAR *lpString; // [esp+0x11C] [ebp+0x4]
  char v10; // [esp+0x120] [ebp+0x8]

  v8 = 0;
  sprintf(Buffer, byte_5967B0, lpString);
  m_pbk = (gbRefObject *)this->m_pbk;
  if ( m_pbk )
    ((gbRefObject *)m_pbk)->Release();
  if ( v10 )
  {
    v3 = *(_DWORD *)gfxMgr;
    v4 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(lpString);
    this->m_pbk = (gbTexture *)(*(int ( **)(gbGfxManager *, CHAR *))(v3 + 8))(gfxMgr, v4);
    this->m_pbkInfo = (_PlugInfo *)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(lpString);
  }
  else
  {
    this->m_pbk = (gbTexture *)(*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, Buffer);
  }
  v5 = this->m_pbk;
  if ( v5 )
    ((gbTexture *)v5)->LoadTexture(1);
  v8 = -1;
}

// 0x00440DD0
BOOL UIStatic::Update(float deltatime, int haveinput)
{
  BOOL v5; // eax
  UIWnd *v6; // ecx
  CScreenMode *Instance; // eax
  char pDebugTex; // dl
  UIWnd *v9; // ecx
  UIWnd *m_pfather; // ecx
  UIWnd *v11; // ecx
  UIWnd *v12; // ecx
  const void *v13; // [esp-0x8] [ebp-0x1C]
  POINT pt; // [esp+0xC] [ebp-0x8]

  if ( !this->m_bvisible )
    return 0;
  ((GRPinput *)&g_Input)->GetCursorPos();
  v5 = PtInRect(&this->m_rect, pt);
  if ( this->m_benable )
  {
    if ( haveinput )
    {
      if ( v5 )
      {
        if ( g_Input.KeyInfo[0].PressTime == 1 )
        {
          pDebugTex = (char)this->pDebugTex;
          BYTE1(this->pDebugTex) = 1;
          LOBYTE(this->pDebugTex) = pDebugTex == 0;
          if ( pDebugTex )
          {
            m_pfather = this->m_pfather;
            this->m_ratioh = 0.0;
            if ( m_pfather )
// [VFTABLE] m_pfather->__vftable->OnMessage(1001, (int)this->m_id, 0);
          }
          else
          {
            v9 = this->m_pfather;
            LODWORD(this->m_ratioh) = 1;
            if ( v9 )
// [VFTABLE] v9->__vftable->OnMessage(1001, (int)this->m_id, 1);
          }
          BYTE1(this->pDebugTex) = 0;
          BYTE2(this->pDebugTex) = 0;
        }
        else
        {
          v11 = this->m_pfather;
          this->m_text[4] = 1;
          BYTE2(this->pDebugTex) = 0;
          if ( v11 )
// [VFTABLE] v11->__vftable->OnMessage(1002, (int)this->m_id, 0);
        }
      }
      else if ( !BYTE2(this->pDebugTex) )
      {
        v12 = this->m_pfather;
        this->m_text[4] = 0;
        BYTE2(this->pDebugTex) = 1;
        if ( v12 )
// [VFTABLE] v12->__vftable->OnMessage(1003, (int)this->m_id, 0);
      }
      return ((UIListBox *)this)->Update(SLODWORD(deltatime), haveinput);
    }
    else
    {
      return ((UIListBox *)this)->Update(SLODWORD(deltatime), 0);
    }
  }
  else
  {
    if ( v5 && g_Input.KeyInfo[0].PressTime == 1 )
    {
      v6 = this->m_pfather;
      if ( v6 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))v6->__vftable->OnMessage)(v6, 1021, this->m_id, 1);
      v13 = off_5974E0;
      Instance = CScreenMode::GetInstance();
      ((CScreenMode *)Instance)->AudioSetPosition(v13, 1);
    }
    return 0;
  }
}

// 0x00440F30
void UIStatic::Render()
{
  _PlugInfo *v1; // ebx
  gbTextureArray *v2; // edi
  float m_ratioh; // eax
  int *v5; // ecx
  char *p_m_rect; // edi
  gbTexture *m_pbk; // eax
  TextureLibDataBase *m_pbkInfo; // [esp-0x10] [ebp-0x58]
  gbTextureArray *v9; // [esp-0x8] [ebp-0x50]
  int v10; // [esp+0x4] [ebp-0x44] BYREF
  int v11; // [esp+0x44] [ebp-0x4]

  if ( this->m_bvisible )
  {
    m_ratioh = this->m_ratioh;
    v9 = v2;
    if ( *(&this->m_textx + LODWORD(m_ratioh)) )
    {
      if ( this->m_text[4] && *(_DWORD *)&this->m_text[8] && LODWORD(m_ratioh) != 1 )
      {
        v10 = *(_DWORD *)&this->m_text[8];
        v5 = &v10;
        v11 = 1;
        p_m_rect = (char *)&this->m_rect;
      }
      else
      {
        v5 = (int *)*(&this->m_textx + LODWORD(m_ratioh));
        v11 = 1;
        v10 = (int)v5;
        p_m_rect = (char *)&this->m_rect;
      }
      ((TextureLibDataBase *)v5)->SetLibFolder(p_m_rect);
      if ( !this->m_benable )
      {
        m_pbk = this->m_pbk;
        if ( m_pbk )
        {
          m_pbkInfo = (TextureLibDataBase *)this->m_pbkInfo;
          v11 = 1;
          v10 = (int)m_pbk;
          ((TextureLibDataBase *)m_pbkInfo)->SetLibFolder(p_m_rect);
        }
      }
    }
    else
    {
      p_m_rect = (char *)&this->m_rect;
      crt_sub_00540070();
    }
    if ( LOBYTE(this->m_ppic) )
      UIRenderPar((int)&this->m_ppic, (int)p_m_rect, (int)&this->m_align, 1, (gbColorQuad *)1, v9, v1);
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  }
}

// 0x00442480
void UIStatic::LoadTextureByName(LPCSTR lpString, char pData)
{
  const CHAR *v3; // edi
  gbRefObject *m_ppic; // ecx
  int v6; // ebx
  CHAR *v7; // eax
  gbTexture *v8; // ecx

  v3 = lpString;
  if ( lpString )
  {
    m_ppic = (gbRefObject *)this->m_ppic;
    if ( m_ppic )
      ((gbRefObject *)m_ppic)->Release();
    if ( pData )
    {
      v6 = *(_DWORD *)gfxMgr;
      v7 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v3);
      this->m_ppic = (gbTexture *)(*(int ( **)(gbGfxManager *, CHAR *))(v6 + 8))(gfxMgr, v7);
      this->m_ppicInfo = (_PlugInfo *)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v3);
    }
    else
    {
      this->m_ppic = (gbTexture *)(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(
                                    gfxMgr,
                                    v3);
    }
    v8 = this->m_ppic;
    if ( v8 )
      ((gbTexture *)v8)->LoadTexture(1);
  }
}

// 0x004426B0
void UIStatic::CreateFromTemplate()
{
  const CHAR *v1; // edi
  gbRefObject *m_pbk; // ecx
  char v4; // al
  int v5; // ebx
  CHAR *v6; // eax
  gbTexture *v7; // ecx
  LPCSTR lpString1; // [esp+0x20] [ebp+0x4] BYREF
  char v9; // [esp+0x24] [ebp+0x8]

  v1 = lpString1;
  if ( lpString1 )
  {
    m_pbk = (gbRefObject *)this->m_pbk;
    if ( m_pbk )
      ((gbRefObject *)m_pbk)->Release();
    lstrcmpA(v1, String2);
    v4 = v9;
    this->m_pbkInfo = 0;
    if ( v4 )
    {
      v5 = *(_DWORD *)gfxMgr;
      v6 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v1);
      this->m_pbk = (gbTexture *)(*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6);
      this->m_pbkInfo = (_PlugInfo *)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v1);
    }
    else
    {
      this->m_pbk = (gbTexture *)(*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(
                                   gfxMgr,
                                   v1);
    }
    v7 = this->m_pbk;
    if ( v7 )
      ((gbTexture *)v7)->LoadTexture(1);
    if ( !lstrcmpA(v1, String2) )
      unk_D90D3C = this->m_pbk;
  }
}

// 0x00442D00
UIStatic * UIStatic::CtorWithFlag()
{
  sub_4422E0(this);
  *((_DWORD *)this + 38) = 1;
  return this;
}

// 0x00443380
UIStatic * UIStatic::UIStatic_Base()
{
  sub_4422E0(this);
  return this;
}

// 0x0044A820
int UIStatic::GetUIElements(float fVal, int nVal)
{
  double v4; // st7
  int m_texty; // edx
  float m_ratioh; // eax

  if ( !this->m_bvisible )
    return 0;
  v4 = fVal + *(float *)&this->m_fonttype;
  m_texty = this->m_texty;
  m_ratioh = this->m_ratioh;
  *(float *)&this->m_fonttype = v4;
  if ( m_texty > SLODWORD(m_ratioh) || v4 <= 2.0 )
    return 1;
  this->m_fonttype = 0;
  this->m_texty = m_texty + 1;
  return 1;
}

// 0x0044A870
void UIStatic::RenderText()
{
  float m_ratioh; // ebp
  int m_texty; // eax
  int v4; // edi
  double v5; // st7
  double v6; // st7
  int v7; // edi

  if ( this->m_bvisible )
  {
    if ( LODWORD(this->m_ratiow) )
    {
      m_ratioh = this->m_ratioh;
      if ( SLODWORD(m_ratioh) > 0 )
      {
        m_texty = this->m_texty;
        if ( m_texty > SLODWORD(m_ratioh) )
        {
          v5 = *(float *)&this->m_fonttype - 5.0;
          if ( v5 <= 0.0 )
            v5 = 0.0;
          v6 = 1.0 - v5 * 0.33333334;
          if ( v6 < 0.0 )
            v6 = 0.0;
          v7 = 0;
          do
            this->RenderTile(v7++, (__int64)(v6 * 255.0));
          while ( v7 <= SLODWORD(this->m_ratioh) );
          if ( !(unsigned __int8)(__int64)(v6 * 255.0) )
          {
// [VFTABLE] ((void ( *)(UIStatic *))this->__vftable->Destroy)(this);
            this->ShowWindow(0);
          }
        }
        else
        {
          v4 = 0;
          if ( m_texty > 0 )
          {
            do
              this->RenderTile(v4++, 255);
            while ( v4 < this->m_texty );
          }
          this->RenderTile(this->m_texty, (__int64)(*(float *)&this->m_fonttype / 2.0 * 255.0));
        }
      }
    }
  }
}

// 0x0044AA20
void UIStatic::RenderTile(int nVal, char pData)
{
  float m_ratiow; // edx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st6
  gbDynVertBuf *DynVertBuf; // eax
  int m_textx; // [esp+0x0] [ebp-0x70]
  int v10; // [esp+0x0] [ebp-0x70]
  struct gbUIQuad v11; // [esp+0x4] [ebp-0x6C] BYREF
  struct gbTextureArray v12; // [esp+0x2C] [ebp-0x44] BYREF

  m_ratiow = this->m_ratiow;
  m_textx = this->m_textx;
  v4 = (double)m_textx;
  v5 = v4 / (double)*(int *)(LODWORD(m_ratiow) + 24);
  v10 = this->m_rect.right - nVal * m_textx;
  LOWORD(v11.color) = -1;
  BYTE2(v11.color) = -1;
  v11.z = 0.0;
  v11.sv = 0.0;
  v11.ev = 1.0;
  HIBYTE(v11.color) = pData;
  v12.nTex = 1;
  *(float *)v12.pTexPt = m_ratiow;
  v6 = 1.0 - (double)nVal * v5;
  v11.eu = v6;
  v11.su = v6 - v5;
  v7 = (double)v10;
  v11.ex = v7;
  v11.sx = v7 - v4;
  v11.ey = (float)this->m_rect.top;
  v11.sy = (float)this->m_rect.bottom;
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(0x114u);
  ((gbDynVertBuf *)DynVertBuf)->RenderUIQuad(&v11, 1, g_pRenderEffect_189504C, &v12);
}

// 0x0044BE60
void UIStatic::DestroyChainToBase()
{
  sub_4422E0(this);
}

// 0x004538D0
BOOL UIStatic::IsHidden()
{
  return LODWORD(this->m_ratiow) == 0;
}
