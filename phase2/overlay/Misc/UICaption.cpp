// [T9] std::string::_Tidy private-access workaround (compile-surface only)
#define private public
#include <string>
#undef private

#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UICaption.h"
#include "Render/CScreenMode.h"
#include "GameBase/GRPinput.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Script/PalScript.h"
#include "Scene/SceneObj.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIFrameWnd.h"
#include "Misc/UIScenePanel.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/_Texture_Info.h"
#include "free_functions.h"

class TextureLibDataBase;

// Unnamed globals (extern)
extern TextureLibDataBase stru_1894B78;

// 0x0043A870
gbVFileSystem * UICaption::CreateChildWidget(
        
        int id,
        void *pRect,
        gbVFileSystem *parent,
        const char *pszName,
        char pData,
        char pData2)
{
  gbVFileSystem *result; // eax
  int v8; // ebp
  float *v10; // edi
  CHAR *v11; // eax
  OpenBaseFile v12; // [esp+0x10] [ebp-0x118] BYREF
  UIWnd *v13; // [esp+0x14] [ebp-0x114]
  char Buffer[260]; // [esp+0x18] [ebp-0x110] BYREF
  int v15; // [esp+0x124] [ebp-0x4]

  result = (gbVFileSystem *)parent;
  v8 = 0;
  if ( parent && pszName )
  {
    v15 = 0;
    v13 = (UICaption *)(&this->m_linetime + 6);
    v10 = (float *)(&this->m_linetime + 23);
    do
    {
      sprintf(Buffer, "%s%d.tga", pszName, v8);
      *v10 = 0.0;
      if ( pData2 )
      {
        *(_DWORD *)v10 = (unsigned long)(((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(Buffer);
        v11 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(Buffer);
        lstrcpyA((char *)Buffer, v11);
      }
      if ( !LoadUISceneTexture((int)Buffer, 1) )
      {
        (((UIWnd *)v13))->UIWnd::MoveWindow();
        goto LABEL_11;
      }
      ++v8;
      ++v10;
    }
    while ( v8 < 3 );
    *((_BYTE *)&this->m_linetime + 248) = 1;
    *((_BYTE *)&this->m_linetime + 8) = 1;
    *((_DWORD *)&this->m_linetime + 27) = 0;
    sprintf(Buffer, "%s%d.tga", pszName, 3);
    if ( (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) )
      (((PalScript *)this))->PalScript::OpenScript(Buffer, 0);
    LOBYTE(this->m_nTodo_000) = pData;
    *((_DWORD *)&this->m_linetime + 4) = 0;
    *((_DWORD *)&this->m_linetime + 3) = 0;
    *((_BYTE *)&this->m_linetime + 20) = 0;
    this->UIWnd::Create(id, (tagRECT *)pRect, (UIWnd *)parent);
LABEL_11:
    v15 = -1;
    ((OpenNULLFile *)&v12)->OpenNULLFile::OpenNULLFile();
  }
  return result;
}

// 0x0043AB00
void UICaption::Destroy()
{
  (((UIWnd *)(&this->m_linetime + 6)))->UIWnd::MoveWindow();
  (((SceneObj *)this))->SceneObj::HideAll() /* [ROWTABLE] */;
}

// 0x0043AB20
BOOL UICaption::Update2(int nVal, int nVal2)
{
  BOOL v4; // edi
  UIWnd *m_pfather; // ecx
  CScreenMode *Instance; // eax
  UIWnd *v8; // ecx
  UIWnd *v9; // ecx
  UIWnd *v10; // ecx
  UIWnd *v11; // ecx
  UIWnd *v12; // ecx
  int v13; // eax
  const void *v14; // [esp-0x8] [ebp-0x20]
  POINT pt; // [esp+0x10] [ebp-0x8] BYREF

  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
  v4 = PtInRect(&this->m_rect, pt);
  if ( !this->m_bvisible )
    return 0;
  if ( !*((_BYTE *)&this->m_linetime + 8) )
  {
    if ( v4 )
      *((_DWORD *)&this->m_linetime + 1) = 1;
    return 0;
  }
  if ( !this->m_benable )
  {
    if ( v4 && g_Input.KeyInfo[0].PressTime == 1 )
    {
      m_pfather = this->m_pfather;
      if ( m_pfather )
        m_pfather->OnMessage(1021, this->m_id, 1);
      if ( *((_BYTE *)&this->m_linetime + 248) )
      {
        v14 = pData;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v14, 1);
      }
    }
    *((_DWORD *)&this->m_linetime + 1) = 0;
    return 0;
  }
  if ( !nVal2 )
  {
    *((_DWORD *)&this->m_linetime + 1) = 0;
    return (((SceneObj *)this))->SceneObj::Update(nVal, 0) /* [ROWTABLE] */;
  }
  if ( *((_DWORD *)&this->m_linetime + 1) != 2 )
  {
    if ( !v4 )
    {
      *((_DWORD *)&this->m_linetime + 1) = 0;
      goto LABEL_27;
    }
    *((_DWORD *)&this->m_linetime + 1) = 1;
  }
  if ( !v4 )
  {
LABEL_27:
    if ( !*((_BYTE *)&this->m_linetime + 112) )
    {
      v9 = this->m_pfather;
      *((_BYTE *)&this->m_linetime + 112) = 1;
      if ( v9 )
        v9->OnMessage(1003, this->m_id, 0);
    }
    goto LABEL_30;
  }
  if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 && LOBYTE(this->m_nTodo_000) )
  {
    v8 = this->m_pfather;
    *((_DWORD *)&this->m_linetime + 1) = 2;
    if ( v8 )
    {
      v8->OnMessage(1020, this->m_id, 0);
      *((_BYTE *)&this->m_linetime + 112) = 0;
      goto LABEL_30;
    }
  }
  else if ( g_Input.KeyInfo[0].PressTime == 1 )
  {
    v11 = this->m_pfather;
    *((_DWORD *)&this->m_linetime + 1) = 2;
    if ( v11 )
    {
      v11->OnMessage(1004, this->m_id, 0);
      *((_BYTE *)&this->m_linetime + 112) = 0;
      goto LABEL_30;
    }
  }
  else
  {
    v12 = this->m_pfather;
    if ( v12 )
      v12->OnMessage(1002, this->m_id, 0);
  }
  *((_BYTE *)&this->m_linetime + 112) = 0;
LABEL_30:
  if ( *((_DWORD *)&this->m_linetime + 1) == 2 && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( v4 )
    {
      v10 = this->m_pfather;
      *((_DWORD *)&this->m_linetime + 1) = 1;
      if ( v10 )
        v10->OnMessage(1001, this->m_id, 0);
    }
    else
    {
      *((_DWORD *)&this->m_linetime + 1) = 0;
    }
  }
  v13 = (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return v4 || v13;
}

// 0x0043AD40
void UICaption::Render()
{
  LONG left; // ecx
  int v3; // eax
  float v4; // st7
  LONG top; // ecx
  float v6; // st7
  float v7; // st6
  __int64 v8; // rax
  float v9; // st7
  gbTexture *TableEntry16; // ebx
  unsigned int v11; // ecx
  TextureLibDataBase *v12; // ecx
  TextureLibDataBase *v13; // ecx
  LONG v14; // eax
  LONG v15; // ecx
  LONG bottom; // ecx
  LONG v17; // edx
  LONG v18; // eax
  LONG v19; // ecx
  int v20; // edi
  int v21; // ecx
  int m_benable; // eax
  int v23; // eax
  gbColorQuad v24; // [esp-0xC] [ebp-0x94] BYREF
  LONG v25; // [esp-0x8] [ebp-0x90]
  unsigned int v26; // [esp-0x4] [ebp-0x8C]
  gbTextureArray *v27; // [esp+0x0] [ebp-0x88]
  _PlugInfo *v28; // [esp+0x4] [ebp-0x84]
  int v29; // [esp+0x10] [ebp-0x78]
  LONG right; // [esp+0x14] [ebp-0x74]
  LONG v31; // [esp+0x18] [ebp-0x70]
  int nW; // [esp+0x1C] [ebp-0x6C] BYREF
  int nY; // [esp+0x24] [ebp-0x64] BYREF
  int v34; // [esp+0x28] [ebp-0x60]
  LONG v35; // [esp+0x2C] [ebp-0x5C]
  LONG v36; // [esp+0x30] [ebp-0x58]
  char pszBuf[4]; // [esp+0x34] [ebp-0x54] BYREF
  int v38; // [esp+0x38] [ebp-0x50]
  int v39; // [esp+0x3C] [ebp-0x4C]
  int v40; // [esp+0x40] [ebp-0x48]
  _BYTE v41[64]; // [esp+0x48] [ebp-0x40] BYREF

  if ( !this->m_bvisible )
    return;
  left = this->m_rect.left;
  right = this->m_rect.right;
  v3 = left + right;
  v29 = left;
  v4 = 1.0f - *(float *)&this->m_needscriptdel;
  top = this->m_rect.top;
  nY = v3 / 2;
  v6 = v4 * (float)(v3 / 2);
  nW = this->m_rect.bottom;
  v31 = top;
  v7 = (float)v29 * *(float *)&this->m_needscriptdel;
  v34 = (top + nW) / 2;
  *(_DWORD *)pszBuf = (__int64)(v7 + v6);
  v8 = (__int64)((double)right * *(float *)&this->m_needscriptdel + v6);
  v9 = (1.0f - *(float *)&this->m_tex) * (float)v34;
  v39 = v8;
  v38 = (__int64)((double)top * *(float *)&this->m_tex + v9);
  v40 = (__int64)((double)nW * *(float *)&this->m_tex + v9);
  TableEntry16 = (gbTexture *)GetTableEntry16(*((_DWORD *)&this->m_linetime + 1));
  if ( !TableEntry16 )
  {
    bottom = this->m_rect.bottom;
    v17 = this->m_rect.right;
    v26 = (unsigned int)&g_fUIColorParam;
    v25 = bottom;
    v24.Color = v17;
    goto LABEL_8;
  }
  v11 = *((_DWORD *)&this->m_linetime + 1);
  v26 = *((_DWORD *)&this->m_linetime + v11 + 23);
  v25 = 276;
  v24.Color = v11;
  ((gbTextureArray *)v41)->gbTextureArray::gbTextureArray(TableEntry16);
  (((TextureLibDataBase *)v12))->TextureLibDataBase::_CheckItem((char *)&this->m_rect, pszBuf);
  if ( !this->m_benable )
  {
    if ( *((_DWORD *)&this->m_linetime + 26) )
    {
      v26 = *((_DWORD *)&this->m_linetime + 27);
      v25 = 276;
      v24.Color = v26;
      ((gbTextureArray *)v41)->gbTextureArray::gbTextureArray(*((gbTexture **)&this->m_linetime + 26));
      (((TextureLibDataBase *)v13))->TextureLibDataBase::_CheckItem((char *)&this->m_rect, (char *)&this->m_rect);
      goto LABEL_9;
    }
    v14 = this->m_rect.bottom;
    v15 = this->m_rect.right;
    v26 = (unsigned int)&g_fUIColorParam;
    v25 = v14;
    v24.Color = v15;
LABEL_8:
    crt_sub_00540070();
  }
LABEL_9:
  if ( *((_BYTE *)&this->m_linetime + 120) )
  {
    v18 = this->m_rect.left;
    nW = this->m_fontcolor.Color;
    v19 = this->m_rect.top;
    v35 = this->m_rect.right;
    v20 = *((_DWORD *)&this->m_linetime + 4);
    v36 = this->m_rect.bottom;
    v21 = v20 + v19;
    nY = *((_DWORD *)&this->m_linetime + 3) + v18;
    m_benable = this->m_benable;
    v34 = v21;
    if ( !m_benable || *((_DWORD *)&this->m_linetime + 1) == 2 )
    {
      BYTE2(nW) = (BYTE2(nW) - 64) & ((BYTE2(nW) - 64 < 0) - 1);
      BYTE1(nW) = (BYTE1(nW) - 64) & ((BYTE1(nW) - 64 < 0) - 1);
      v23 = *((_DWORD *)&this->m_linetime + 1);
      LOBYTE(nW) = (nW - 64) & (((unsigned __int8)nW - 64 < 0) - 1);
      if ( v23 == 2 )
        v34 = v21 + 6;
    }
    if ( *((_BYTE *)&this->m_linetime + 20) )
    {
      v26 = 1;
      v25 = 2;
    }
    else
    {
      v26 = *((_DWORD *)&this->m_linetime + 29);
      v25 = 1;
    }
    UIRenderPar((int)(&this->m_linetime + 30), (int)&nY, (int)&nW, v25, (gbColorQuad *)v26, v27, v28);
  }
  (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
}

// 0x004427C0
void UICaption::SetEnable()
{
  float *v1; // ebp
  unsigned int v2; // kr04_4
  unsigned int v3; // ebx
  int v4; // ecx
  char v5; // al
  unsigned int v6; // eax
  int v7; // ecx
  const char *v9; // [esp+0x10] [ebp+0x4]
  int v10; // [esp+0x14] [ebp+0x8]

  if ( v9 )
  {
    v1 = (float *)(&this->m_linetime + 1);
    v2 = strlen(v9) + 1;
    v3 = v2 - 1;
    if ( v2 - 1 > 0xFFFFFFFD )
      std::_Xlen();
    v4 = *((_DWORD *)v1 + 1);
    if ( v4 && (v5 = *(_BYTE *)(v4 - 1)) != 0 && v5 != -1 )
    {
      if ( v2 == 1 )
      {
        *(_BYTE *)(v4 - 1) = v5 - 1;
        v1[1] = 0.0;
        v1[2] = 0.0;
        v1[3] = 0.0;
        goto LABEL_16;
      }
    }
    else
    {
      if ( v2 == 1 )
      {
        (((std::string *)1))->_Tidy();
        goto LABEL_16;
      }
      v6 = *((_DWORD *)v1 + 3);
      if ( v6 <= 0x1F && v6 >= v3 )
      {
LABEL_15:
        qmemcpy(*((void **)v1 + 1), v9, v3);
        v7 = *((_DWORD *)v1 + 1);
        *((_DWORD *)v1 + 2) = v3;
        *(_BYTE *)(v7 + v3) = 0;
LABEL_16:
        if ( v10 )
          this->m_needscriptdel = ((gbImage2D *)((gbImage2D *)1));
        else
          this->m_needscriptdel = ((gbImage2D *)0);
        return;
      }
      (((std::string *)1))->_Tidy();
    }
    (((GRPinput *)v1))->GRPinput::PollInputState(v3);
    goto LABEL_15;
  }
}

// 0x004461F0
void UICaption::DestroyPanel()
{
  (((UIScenePanel *)(&this->m_linetime + 1)))->UIScenePanel::~UIScenePanel();
}

// 0x0044BDA0
void UICaption::DestroyAll()
{
  this->UICaption::Destroy2();
}

// 0x00450320
void UICaption::LayoutDefault()
{
  ((UIFrameWnd *)this)->UIFrameWnd::UIFrameWnd();
  this->m_tex = ((gbTexture *)0);
  this->m_curline = 0;
  this->m_lineheight = 0;
  this->m_nTodo_000 = ((void *)((void *)1));
  this->m_linetime = 0.0f;
  this->m_numline = 0;
  memset(&this->m_linetime + 1, 0, 0x100u);
}

// 0x00450670
void UICaption::UICaption_Destroy()
{
  int v0; // ecx
  int v1; // esi
  gbRefObject *v2; // ecx

  v1 = v0;
  v2 = (gbRefObject *)*(gbRefObject **)(v0 + 92);
  if ( v2 )
  {
    (((gbRefObject *)v2))->gbRefObject::Release();
    *(_DWORD *)(v1 + 92) = 0;
  }
  (((SceneObj *)v1))->SceneObj::HideAll();
}

// 0x004506C0
void UICaption::_UICaption_adjthunk()
{
  char v1; // [esp+0x4] [ebp+0x4]

  // [overlay-fix 2026-10-27] C2065: sdtor_15 无定义/声明（scalar deleting dtor 合成名）——待归属定谳
  // sdtor_15(&this[-1].m_linetime + 45, v1);
}
