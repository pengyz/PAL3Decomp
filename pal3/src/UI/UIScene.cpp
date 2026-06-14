#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIScene.h"

// Forward declarations for unnamed functions
void * GetSaveDataManager(void); // from annotations
int UISceneUpdate(void); // from annotations
int sub_4019F0(...);
int sub_442000(void); // from annotations
int sub_445AA0(void); // from annotations
int sub_445E50(int a2); // from annotations
void * sub_445EA0(void); // from annotations
int sub_445ED0(int a2, int a3); // from annotations
int sub_445F60(unsigned int a2); // from annotations
void * sub_446010(void *a2); // from annotations

int crt_sub_00540070(void); // from annotations
int crt_sub_00540D20(void); // from annotations
int crt_sub_00540FD0(void); // from annotations
BOOL __stdcall MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint); // from annotations
float * Vec3D_Lerp(float *pOut, float *pSrc, float fLerpFactor); // from annotations

// Unnamed globals (extern)
extern char byte_A00B00;
extern char byte_A00B01;
extern char byte_A00B02;
extern char byte_A00B03;
extern char byte_A00B04;
extern char byte_A00B05;
extern char byte_A00B06;
extern char byte_A00B07;
extern int dword_A00B08;
extern _SPropValue * off_59DC84;
extern void * off_59DC90;
extern TextureLibDataBase stru_1894B78;
extern RoleSystem stru_C059A0;
extern float unk_D91780;

// 0x00419C20
int UIScene::RenderVertexPool()
{
  int result; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  RoleSystem *v11; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  RoleSystem *v20; // eax
  int v22; // eax
  int v24; // [esp+0x24] [ebp-0x50]
  int v25; // [esp+0x24] [ebp-0x50]
  gbDynVertBuf *DynVertBuf; // [esp+0x40] [ebp-0x34]
  gbVec3D v27; // [esp+0x44] [ebp-0x30] BYREF
  gbVec3D v28; // [esp+0x50] [ebp-0x24] BYREF
  gbVec3D v29; // [esp+0x5C] [ebp-0x18] BYREF
  int v30; // [esp+0x68] [ebp-0xC]
  int v31; // [esp+0x6C] [ebp-0x8]
  float pOut; // [esp+0x70] [ebp-0x4] BYREF
v27.x = -0.5;
  v27.y = 0.0;
  v27.z = 0.87;
  v28.x = 0.5;
  v28.y = 0.0;
  v28.z = 0.87;
  ((gbVec3D *)&v27)->Normalize();
  __asm
  {
    fld     _flt_500_0
    fmul    [esp+0x40+var_30]
  }
  __asm
  {
    fstp    [esp+0x40+var_30]
    fld     dword ptr [flt_56A99C]
    fmul    [esp+0x40+var_2C]
    fstp    [esp+0x40+var_2C]
    fld     [esp+0x40+fLerpFactor]
    fmul    _flt_500_0
    fstp    [esp+0x40+fLerpFactor]
  }
  gbVec3D::Normalize(&v28);
  __asm
  {
    fld     _flt_500_0
    fmul    [esp+0x40+var_24]
  }
  __asm
  {
    fstp    [esp+0x44+var_24]
    fld     [esp+0x44+var_20]
    fmul    _flt_500_0
    fstp    [esp+0x44+var_20]
    fld     [esp+0x44+var_1C]
    fmul    _flt_500_0
    fstp    [esp+0x44+var_1C]
  }
  DynVertBuf = ((gbVertPoolMgr *)gfxMgr->pVertPoolMgr)->GetDynVertBuf(5u);
  result = ((int (*)(gbDynVertBuf *, int))DynVertBuf->pGfxMgr->DrvInfo.type)(DynVertBuf, 3);
  _ESI = result;
  if ( result )
  {
    v4 = Vec3D_Lerp(&pOut, (float *)&this->m_pfather, v27.z);
    ((gbVec3D *)_ESI)->operator=(v4);
    v5 = Vec3D_Lerp(&pOut, (float *)&this->m_childs.m_nSize, v28.x);
    ((gbVec3D *)&v29.z)->operator=(v5);
    ((gbVec3D *)_ESI)->operator+=(&v29.z);
    v6 = Vec3D_Lerp(&pOut, (float *)&this->m_rect.top, v28.y);
    ((gbVec3D *)&v29.z)->operator=(v6);
    ((gbVec3D *)_ESI)->operator+=(&v29.z);
    __asm
    {
      fld     dword ptr [esi]
      fadd    dword ptr [edi+4]
    }
    _EBX = _ESI + 4;
    __asm { fstp    dword ptr [esi] }
    *(float *)_ESI = _ET1;
    __asm
    {
      fld     dword ptr [edi+8]
      fadd    dword ptr [ebx]
      fstp    dword ptr [ebx]
    }
    *(float *)_EBX = _ET1;
    __asm
    {
      fld     dword ptr [edi+0x0C]
      fadd    dword ptr [esi+8]
      fstp    dword ptr [esi+8]
    }
    *(float *)(_ESI + 8) = _ET1;
    v24 = *(&_EDI[1].m_hTexture + 19);
    v11 = (RoleSystem *)UISceneUpdate();
    ((RoleSystem *)v11)->SetRoleParam(v24, (float *)_ESI, 0, 0);
    __asm { fstp    dword ptr [ebx] }
    *(float *)_EBX = _ET1;
    _EBP = (float *)(_ESI + 32);
    *(_DWORD *)(_ESI + 16) = this->m_bLoadState;
    *(_DWORD *)(_ESI + 20) = this->m_pChildData;
    *(float *)(_ESI + 24) = this->m_fAngle;
    v29.z = 0.0;
    v30 = 0;
    v31 = 0;
    v14 = Vec3D_Lerp(&pOut, (float *)&this->m_pfather, v28.z);
    ((gbVec3D *)_ESI + 32)->operator=(v14);
    v15 = Vec3D_Lerp(&pOut, (float *)&this->m_childs.m_nSize, v29.x);
    ((gbVec3D *)&v29.z)->operator=(v15);
    ((gbVec3D *)_ESI + 32)->operator+=(&v29.z);
    v16 = Vec3D_Lerp(&pOut, (float *)&this->m_rect.top, v29.y);
    ((gbVec3D *)&v29.z)->operator=(v16);
    ((gbVec3D *)_ESI + 32)->operator+=(&v29.z);
    __asm
    {
      fld     dword ptr [edi+4]
      fadd    dword ptr [ebp+0]
    }
    __asm { fstp    dword ptr [ebp+0] }
    *_EBP = _ET1;
    __asm
    {
      fld     dword ptr [edi+8]
      fadd    dword ptr [ebp+4]
      fstp    dword ptr [ebp+4]
    }
    *(float *)(_ESI + 36) = _ET1;
    __asm
    {
      fld     dword ptr [edi+0x0C]
      fadd    dword ptr [ebp+8]
      fstp    dword ptr [ebp+8]
    }
    *(float *)(_ESI + 40) = _ET1;
    v25 = *(&_EDI[1].m_hTexture + 19);
    v20 = (RoleSystem *)UISceneUpdate();
    ((RoleSystem *)v20)->SetRoleParam(v25, (float *)(_ESI + 32), 0, 0);
    // __asm { fstp    dword ptr [esi+0x24] }
    *(float *)(_ESI + 36) = _ET1;
    v22 = 3;
    do
    {
      v27.x = COERCE_FLOAT(-2147104763);
      *(_DWORD *)(_EBX + 8) = -2147104763;
      __asm
      {
        fld     dword ptr [ebx]
        fadd    _flt_2_0
      }
      _EBX += 16;
      --v22;
      __asm { fstp    dword ptr [ebx-0x10] }
      *(float *)(_EBX - 16) = _ET1;
    }
    while ( v22 );
    return (*(int (**)(_DWORD, int))(*(_DWORD *)LODWORD(v27.y) + 20))(LODWORD(v27.y), 1);
  }
  return result;
}

// 0x00421A10
int UIScene::NotifyRender()
{
  int v2; // esi
  int result; // eax

  v2 = 0;
  result = LODWORD(this->m_fAngle);
  if ( result > 0 )
  {
    do
    {
      sub_4019F0(*(_DWORD *)&this->m_pChildData[4 * v2]);
      result = LODWORD(this->m_fAngle);
      ++v2;
    }
    while ( v2 < result );
  }
  return result;
}

// 0x004220A0
int UIScene::OverlayRender(int nVal)
{
  int v3; // edi
  int result; // eax
  UIBigMap *v5; // esi

  v3 = 0;
  result = *(&this->m_hTexture + 3);
  if ( result > 0 )
  {
    v5 = (UIBigMap *)(&this->m_hTexture + 4);
    do
    {
      if ( v5->bkWndX == 4 )
        ((UIBigMap *)v5)->RenderRole((gbMatrixStack *)nVal, 0);
      result = *(&this->m_hTexture + 3);
      ++v3;
      v5 = (UIBigMap *)((char *)v5 + 896);
    }
    while ( v3 < result );
  }
  return result;
}

// 0x004234D0
int UIScene::CombatCheck()
{
  int v2; // eax

  if ( !*(_DWORD *)(UISceneUpdate() + 136) )
    return 0;
  v2 = UISceneUpdate();
  (*(void ( **)(_DWORD, _DWORD))(**(_DWORD **)(v2 + 136) + 16))(*(_DWORD *)(v2 + 136), 0);
  return 1;
}

// 0x004235B0
BOOL UIScene::ProcessInput(char *pszBuf)
{
  const char *v2; // esi
  bool v3; // bl
  bool v4; // al

  v2 = (const char *)UISceneUpdate();
  v3 = _strcmpi(String1, v2) == 0;
  v4 = 1;
  if ( pszBuf )
    v4 = _strcmpi(pszBuf, v2 + 32) == 0;
  return v3 && v4;
}

// 0x0043A4B0
int UIScene::SetController(int nVal)
{
  this->m_nViewW = nVal;
  return nVal;
}

// 0x0043A4C0
void UIScene::LoadResource(void *path)
{
  HWND v2; // ebp
  int v3; // edi
  HWND v5; // [esp-0x4] [ebp-0x124]
  int v6; // [esp+0x0] [ebp-0x120]
  int v7; // [esp+0x0] [ebp-0x120]
  int v8; // [esp+0x4] [ebp-0x11C]
  int v9; // [esp+0x4] [ebp-0x11C]
  int v10; // [esp+0x8] [ebp-0x118]
  int v11; // [esp+0x8] [ebp-0x118]
  OpenBaseFile v12; // [esp+0xC] [ebp-0x114] BYREF
  BOOL Buffer[65]; // [esp+0x10] [ebp-0x110] BYREF
  int v14; // [esp+0x11C] [ebp-0x4]

  v3 = 0;
  if ( path )
  {
    MoveWindow(v2, v6, v8, v10, (int)v12.m_plastsys, Buffer[0]);
    this->m_dwColor = 0;
    v14 = 0;
    sprintf((char *const)Buffer, "%s%d.tga", (const char *)path, 0);
    while ( (int)((gbVFileSystem *)g_pVFileSys)->FileExistNum((char *)Buffer) > 0 )
    {
      if ( !sub_445ED0((int)Buffer, 1) )
        MoveWindow(v5, v7, v9, v11, (int)v12.m_plastsys, Buffer[0]);
      ++v3;
      ++this->m_dwColor;
      sprintf((char *const)Buffer, "%s%d.tga", (const char *)path, v3);
    }
    this->m_bLoadState = 0;

    v14 = -1;
  }
}

// 0x0043A5D0
gbVFileSystem * UIScene::OpenAndLoadResource(BOOL bVisible, UIWnd *pWnd)
{
  gbVFileSystem *result; // eax
  HWND v5; // [esp+0x0] [ebp-0x18]
  int v6; // [esp+0x4] [ebp-0x14]
  OpenBaseFile v7; // [esp+0x8] [ebp-0x10] BYREF
  int v8; // [esp+0xC] [ebp-0xC]
  int v9; // [esp+0x10] [ebp-0x8]
  BOOL v10; // [esp+0x14] [ebp-0x4]

  MoveWindow(v5, v6, (int)v7.m_plastsys, v8, v9, v10);
  v10 = 0;
  sub_445ED0(bVisible, 1);
  this->m_bLoadState = 1;
  this->m_dwColor = (unsigned int)pWnd;

  v10 = -1;
  return result;
}

// 0x0043A660
int UIScene::ResetState()
{
  this->m_nNotifyRender = 0;
  this->m_fScaleY = 0.0;
  this->m_hScrollBar = 0;
  return 0;
}

// 0x0043A680
int UIScene::SetColors(int nVal)
{
  this->m_nColors = nVal;
  return nVal;
}

// 0x0043A770
NameSys * UIScene::GetSys()
{
  int v0; // ecx
  int v1; // esi

  v1 = v0;
  sub_445AA0();
  sub_445EA0();
  *(_DWORD *)(v1 + 96) = 0;
  *(_DWORD *)(v1 + 196) = 0;
  *(_BYTE *)(v1 + 204) = 1;
  memset((void *)(v1 + 212), 0, 0x80u);
  *(_DWORD *)(v1 + 76) = 1065353216;
  *(_DWORD *)(v1 + 72) = 1065353216;
  *(_DWORD *)(v1 + 208) = 1;
  return (NameSys *)v1;
}

// 0x0043A870
gbVFileSystem * UIScene::CreateChildWidget(
        
        int id,
        void *pRect,
        gbVFileSystem *parent,
        const char *pszName,
        char pData,
        char pData2)
{
  gbVFileSystem *result; // eax
  int v8; // ebp
  Parent_Data **p_m_bVisible; // edi
  CHAR *v11; // eax
  HWND v12; // [esp+0x0] [ebp-0x128]
  int v13; // [esp+0x4] [ebp-0x124]
  int v14; // [esp+0x8] [ebp-0x120]
  int v15; // [esp+0xC] [ebp-0x11C]
  OpenBaseFile v16; // [esp+0x10] [ebp-0x118] BYREF
  BOOL bRepaint; // [esp+0x14] [ebp-0x114]
  char Buffer[260]; // [esp+0x18] [ebp-0x110] BYREF
  int v19; // [esp+0x124] [ebp-0x4]

  result = parent;
  v8 = 0;
  if ( parent && pszName )
  {
    v19 = 0;
    bRepaint = (BOOL)&this->m_nClipW;
    p_m_bVisible = &this->m_bVisible;
    do
    {
      sprintf(Buffer, "%s%d.tga", pszName, v8);
      *p_m_bVisible = 0;
      if ( pData2 )
      {
        *p_m_bVisible = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(Buffer);
        v11 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(Buffer);
        lstrcpyA(Buffer, v11);
      }
      if ( !sub_445ED0((int)Buffer, 1) )
      {
        MoveWindow(v12, v13, v14, v15, (int)v16.m_plastsys, bRepaint);
        goto LABEL_11;
      }
      ++v8;
      ++p_m_bVisible;
    }
    while ( v8 < 3 );
    *((_BYTE *)&this->m_hTexture + 132) = 1;
    LOBYTE(this->m_nClipX) = 1;
    *(_DWORD *)&this->m_bOverlayRender = 0;
    sprintf(Buffer, "%s%d.tga", pszName, 3);
    if ( ((gbVFileSystem *)g_pVFileSys)->FileExistNum(Buffer) )
      ((PalScript *)this)->OpenScript(Buffer, 0);
    LOBYTE(this->m_nViewW) = pData;
    this->m_nRectX = 0;
    this->m_nClipY = 0;
    LOBYTE(this->m_nRectY) = 0;
    ((PalScript *)this)->Create(id, (tagRECT *)pRect, (int)parent);
LABEL_11:
    v19 = -1;
  }
  return result;
}

// 0x0043AB20
BOOL UIScene::Update2(int nVal, int nVal2)
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
  POINT pt; // [esp+0x10] [ebp-0x8]

  ((GRPinput *)&g_Input)->GetCursorPos();
  v4 = PtInRect(&this->m_rect, pt);
  if ( !this->m_bvisible )
    return 0;
  if ( !LOBYTE(this->m_nClipX) )
  {
    if ( v4 )
      this->m_pChildWnd = (UIWnd *)1;
    return 0;
  }
  if ( !this->m_benable )
  {
    if ( v4 && g_Input.KeyInfo[0].PressTime == 1 )
    {
      m_pfather = this->m_pfather;
      if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, int))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1021,
// [VFTABLE]   this->m_id,
// [VFTABLE]   1);
      if ( *((_BYTE *)&this->m_hTexture + 132) )
      {
        v14 = pData;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v14, 1);
      }
    }
    this->m_pChildWnd = 0;
    return 0;
  }
  if ( !nVal2 )
  {
    this->m_pChildWnd = 0;
    return ((UIListBox *)this)->Update(nVal, 0);
  }
  if ( this->m_pChildWnd != (UIWnd *)2 )
  {
    if ( !v4 )
    {
      this->m_pChildWnd = 0;
      goto LABEL_27;
    }
    this->m_pChildWnd = (UIWnd *)1;
  }
  if ( !v4 )
  {
LABEL_27:
    if ( !this->m_bCursorLeft )
    {
      v9 = this->m_pfather;
      this->m_bCursorLeft = 1;
      if ( v9 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v9->__vftable->OnMessage)(v9, 1003, this->m_id, 0);
    }
    goto LABEL_30;
  }
  if ( g_Input.KeyInfo[0].PressTime == 1 && (g_Input.KeyInfo[0].Data & 0xF) == 2 && LOBYTE(this->m_nViewW) )
  {
    v8 = this->m_pfather;
    this->m_pChildWnd = (UIWnd *)2;
    if ( v8 )
    {
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v8->__vftable->OnMessage)(v8, 1020, this->m_id, 0);
      this->m_bCursorLeft = 0;
      goto LABEL_30;
    }
  }
  else if ( g_Input.KeyInfo[0].PressTime == 1 )
  {
    v11 = this->m_pfather;
    this->m_pChildWnd = (UIWnd *)2;
    if ( v11 )
    {
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v11->__vftable->OnMessage)(v11, 1004, this->m_id, 0);
      this->m_bCursorLeft = 0;
      goto LABEL_30;
    }
  }
  else
  {
    v12 = this->m_pfather;
    if ( v12 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v12->__vftable->OnMessage)(v12, 1002, this->m_id, 0);
  }
  this->m_bCursorLeft = 0;
LABEL_30:
  if ( this->m_pChildWnd == (UIWnd *)2 && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( v4 )
    {
      v10 = this->m_pfather;
      this->m_pChildWnd = (UIWnd *)1;
      if ( v10 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v10->__vftable->OnMessage)(v10, 1001, this->m_id, 0);
    }
    else
    {
      this->m_pChildWnd = 0;
    }
  }
  v13 = ((UIListBox *)this)->Update(nVal, nVal2);
  return v4 || v13;
}

// 0x0043AD40
void UIScene::Render()
{
  LONG left; // ecx
  int v3; // eax
  double v4; // st7
  LONG top; // ecx
  double v6; // st7
  double v7; // st6
  __int64 v8; // rax
  double v9; // st7
  gbTexture *v10; // ebx
  unsigned int m_pChildWnd; // ecx
  TextureLibDataBase *v12; // ecx
  TextureLibDataBase *v13; // ecx
  LONG v14; // eax
  LONG v15; // ecx
  LONG bottom; // ecx
  LONG v17; // edx
  LONG v18; // eax
  LONG v19; // ecx
  int m_nRectX; // edi
  int v21; // ecx
  int m_benable; // eax
  UIWnd *v23; // eax
  gbColorQuad v24; // [esp-0xC] [ebp-0x94] BYREF
  LONG v25; // [esp-0x8] [ebp-0x90]
  unsigned int m_hTexture; // [esp-0x4] [ebp-0x8C]
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
  v4 = 1.0 - this->m_fScaleY;
  top = this->m_rect.top;
  nY = v3 / 2;
  v6 = v4 * (double)(v3 / 2);
  nW = this->m_rect.bottom;
  v31 = top;
  v7 = (double)v29 * this->m_fScaleY;
  v34 = (top + nW) / 2;
  *(_DWORD *)pszBuf = (__int64)(v7 + v6);
  v8 = (__int64)((double)right * this->m_fScaleY + v6);
  v9 = (1.0 - this->m_fScaleX) * (double)v34;
  v39 = v8;
  v38 = (__int64)((double)top * this->m_fScaleX + v9);
  v40 = (__int64)((double)nW * this->m_fScaleX + v9);
  v10 = (gbTexture *)sub_445F60((unsigned int)this->m_pChildWnd);
  if ( !v10 )
  {
    bottom = this->m_rect.bottom;
    v17 = this->m_rect.right;
    m_hTexture = (unsigned int)&unk_D91780;
    v25 = bottom;
    v24.Color = v17;
    goto LABEL_8;
  }
  m_pChildWnd = (unsigned int)this->m_pChildWnd;
  m_hTexture = (unsigned int)(&this->m_bVisible)[m_pChildWnd];
  v25 = 276;
  v24.Color = m_pChildWnd;
  ((TextureLibDataBase *)v12)->_CheckItem((char *)&this->m_rect, pszBuf);
  if ( !this->m_benable )
  {
    if ( this->m_pTexture )
    {
      m_hTexture = *(_DWORD *)&this->m_bOverlayRender;
      v25 = 276;
      v24.Color = m_hTexture;
      ((TextureLibDataBase *)v13)->_CheckItem((char *)&this->m_rect, (char *)&this->m_rect);
      goto LABEL_9;
    }
    v14 = this->m_rect.bottom;
    v15 = this->m_rect.right;
    m_hTexture = (unsigned int)&unk_D91780;
    v25 = v14;
    v24.Color = v15;
LABEL_8:
    crt_sub_00540070();
  }
LABEL_9:
  if ( *((_BYTE *)&this->m_hTexture + 4) )
  {
    v18 = this->m_rect.left;
    nW = this->m_fontcolor.Color;
    v19 = this->m_rect.top;
    v35 = this->m_rect.right;
    m_nRectX = this->m_nRectX;
    v36 = this->m_rect.bottom;
    v21 = m_nRectX + v19;
    nY = this->m_nClipY + v18;
    m_benable = this->m_benable;
    v34 = v21;
    if ( !m_benable || this->m_pChildWnd == (UIWnd *)2 )
    {
      BYTE2(nW) = (BYTE2(nW) - 64) & ((BYTE2(nW) - 64 < 0) - 1);
      BYTE1(nW) = (BYTE1(nW) - 64) & ((BYTE1(nW) - 64 < 0) - 1);
      v23 = this->m_pChildWnd;
      LOBYTE(nW) = (nW - 64) & (((unsigned __int8)nW - 64 < 0) - 1);
      if ( v23 == (UIWnd *)2 )
        v34 = v21 + 6;
    }
    if ( LOBYTE(this->m_nRectY) )
    {
      m_hTexture = 1;
      v25 = 2;
    }
    else
    {
      m_hTexture = this->m_hTexture;
      v25 = 1;
    }
    UIRenderPar((int)(&this->m_hTexture + 1), (int)&nY, (int)&nW, v25, (gbColorQuad *)m_hTexture, v27, v28);
  }
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
}

// 0x0043AFE0
unsigned __int8 UIScene::SetupRenderClip(
        
        int nVal,
        unsigned int dwVal,
        unsigned int dwVal2,
        int nVal2)
{
  Parent_Data *v5; // edx
  gbTexture_D3D *v6; // eax
  unsigned int v8; // [esp-0xC] [ebp-0x14]
  unsigned int v9; // [esp-0x8] [ebp-0x10]

  if ( (dwVal & 0x80000000) != 0 )
    return 0;
  v5 = (&this->m_bVisible)[nVal];
  if ( dwVal >= *(_DWORD *)&v5[260] || (dwVal2 & 0x80000000) != 0 || dwVal2 >= *(_DWORD *)&v5[261] )
    return 0;
  v9 = nVal2 + 4 * (*(_DWORD *)&v5[258] + dwVal);
  v8 = *(_DWORD *)&v5[259] - *(_DWORD *)&v5[257] - dwVal2 + 1024;
  v6 = (gbTexture_D3D *)sub_445F60(0);
  return ((gbTexture_D3D *)v6)->GetByte(v8, v9);
}

// 0x0043B060
gbVFileSystem * UIScene::CreateTextureWidget(
        
        int id,
        void *pRect,
        gbVFileSystem *parent,
        const char *pszName,
        char pData)
{
  gbVFileSystem *result; // eax
  int v7; // edi
  Parent_Data **p_m_bVisible; // esi
  CHAR *v10; // eax
  HWND v11; // [esp+0x0] [ebp-0x124]
  int v12; // [esp+0x4] [ebp-0x120]
  int v13; // [esp+0x8] [ebp-0x11C]
  int v14; // [esp+0xC] [ebp-0x118]
  OpenBaseFile v15; // [esp+0x10] [ebp-0x114] BYREF
  BOOL Buffer[65]; // [esp+0x14] [ebp-0x110] BYREF
  int v17; // [esp+0x120] [ebp-0x4]

  result = parent;
  v7 = 0;
  if ( parent && pszName )
  {
    v17 = 0;
    p_m_bVisible = &this->m_bVisible;
    do
    {
      sprintf((char *const)Buffer, "%s%d.tga", pszName, v7);
      *p_m_bVisible = 0;
      if ( pData )
      {
        *p_m_bVisible = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData((LPCSTR)Buffer);
        v10 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV((LPCSTR)Buffer);
        lstrcpyA((LPSTR)Buffer, v10);
        if ( !sub_445ED0((int)Buffer, 2) )
          goto LABEL_14;
      }
      else if ( !sub_445ED0((int)Buffer, 2) )
      {
LABEL_14:
        MoveWindow(v11, v12, v13, v14, (int)v15.m_plastsys, Buffer[0]);
        goto LABEL_12;
      }
      ++v7;
      ++p_m_bVisible;
    }
    while ( v7 < 3 );
    sprintf((char *const)Buffer, "%s%d.tga", pszName, 3);
    if ( ((gbVFileSystem *)g_pVFileSys)->FileExistNum((char *)Buffer) )
      ((PalScript *)this)->OpenScript((const char *)Buffer, 0);
    ((PalScript *)this)->Create(id, (tagRECT *)pRect, (int)parent);
LABEL_12:
    v17 = -1;
  }
  return result;
}

// 0x0043B1E0
BOOL UIScene::Update(int nVal, int nVal2)
{
  tagRECT *p_m_rect; // ebp
  BOOL v6; // eax
  LONG left; // edx
  LONG top; // ecx
  int v9; // edi
  int v10; // ebp
  unsigned __int8 PixelChannel; // al
  UIWnd *m_pfather; // ecx
  UIWnd *v13; // ecx
  UIWnd *v14; // ecx
  int v15; // eax
  BOOL v16; // [esp+0xC] [ebp-0xC]
  POINT pt; // [esp+0x10] [ebp-0x8]

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
  {
    this->m_pChildWnd = 0;
    return 0;
  }
  if ( !nVal2 )
  {
    this->m_pChildWnd = 0;
    return ((UIListBox *)this)->Update(nVal, 0);
  }
  ((GRPinput *)&g_Input)->GetCursorPos();
  p_m_rect = &this->m_rect;
  v6 = PtInRect(&this->m_rect, pt);
  v16 = v6;
  if ( this->m_pChildWnd != (UIWnd *)2 )
  {
    if ( !v6 )
    {
      this->m_pChildWnd = 0;
      goto LABEL_14;
    }
    this->m_pChildWnd = (UIWnd *)1;
  }
  if ( !v6 )
  {
LABEL_14:
    if ( !this->m_bCursorLeft )
    {
      m_pfather = this->m_pfather;
      this->m_bCursorLeft = 1;
      if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1003,
// [VFTABLE]   this->m_id,
// [VFTABLE]   0);
    }
    goto LABEL_17;
  }
  left = p_m_rect->left;
  top = this->m_rect.top;
  v9 = pt.x - p_m_rect->left;
  v10 = pt.y - top;
  if ( this->m_bVisible )
  {
    PixelChannel = this->SetupRenderClip(0, pt.x - left, pt.y - top, 3);
  }
  else
  {
    if ( v9 >= *(_DWORD *)(sub_445F60(0) + 24) )
      v9 = *(_DWORD *)(sub_445F60(0) + 24) - 1;
    if ( v10 >= *(_DWORD *)(sub_445F60(0) + 28) )
      v10 = *(_DWORD *)(sub_445F60(0) + 28) - 1;
    PixelChannel = ((UIScene *)&this->m_nClipW)->GetPixelChannel(0, v9, v10, 3);
  }
  if ( PixelChannel < 6u )
  {
    v16 = 0;
    this->m_pChildWnd = 0;
  }
  else if ( g_Input.KeyInfo[0].PressTime == 1 )
  {
    this->m_pChildWnd = (UIWnd *)2;
    this->m_bCursorLeft = 0;
  }
  else
  {
    v14 = this->m_pfather;
    if ( v14 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v14->__vftable->OnMessage)(v14, 1002, this->m_id, 0);
    this->m_bCursorLeft = 0;
  }
LABEL_17:
  if ( this->m_pChildWnd == (UIWnd *)2 && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( v16 )
    {
      v13 = this->m_pfather;
      this->m_pChildWnd = (UIWnd *)1;
      if ( v13 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v13->__vftable->OnMessage)(v13, 1001, this->m_id, 0);
    }
    else
    {
      this->m_pChildWnd = 0;
    }
  }
  v15 = ((UIListBox *)this)->Update(nVal, nVal2);
  return v16 || v15;
}

// 0x0043B500
unsigned __int8 UIScene::GetChildWidget(unsigned int dwVal, unsigned int dwVal2, int nVal)
{
  Parent_Data *m_bVisible; // edx
  gbTexture_D3D *v5; // eax
  unsigned int v7; // [esp-0xC] [ebp-0x14]
  unsigned int v8; // [esp-0x8] [ebp-0x10]

  if ( (dwVal & 0x80000000) != 0 )
    return 0;
  m_bVisible = this->m_bVisible;
  if ( dwVal >= *(_DWORD *)&m_bVisible[260] || (dwVal2 & 0x80000000) != 0 || dwVal2 >= *(_DWORD *)&m_bVisible[261] )
    return 0;
  v8 = nVal + 4 * (*(_DWORD *)&m_bVisible[258] + dwVal);
  v7 = *(_DWORD *)&m_bVisible[259] - *(_DWORD *)&m_bVisible[257] - dwVal2 + 1024;
  v5 = (gbTexture_D3D *)sub_445F60(0);
  return ((gbTexture_D3D *)v5)->GetByte(v7, v8);
}

// 0x0043B570
gbVFileSystem * UIScene::CreateLabelWidget(
        
        int id,
        void *pRect,
        gbVFileSystem *parent,
        LPCSTR lpString,
        char pData)
{
  gbVFileSystem *result; // eax
  const CHAR *v8; // edi
  CHAR *v9; // eax
  HWND v10; // [esp+0x0] [ebp-0x18]
  int v11; // [esp+0x4] [ebp-0x14]
  int v12; // [esp+0x8] [ebp-0x10]
  int v13; // [esp+0xC] [ebp-0xC]
  int v14; // [esp+0x10] [ebp-0x8]

  result = parent;
  if ( parent )
  {
    v8 = lpString;
    if ( lpString )
    {
      this->m_bVisible = 0;
      this->m_hFont = 0;
      this->m_bEnabled = 0;
      *(_DWORD *)&this->m_bOverlayRender = 0;
      if ( pData )
      {
        this->m_bVisible = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v8);
        v9 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v8);
        if ( !sub_445ED0((int)v9, 1) )
        {
LABEL_5:
          MoveWindow(v10, v11, v12, v13, v14, 0);
LABEL_8:
          return result;
        }
      }
      else if ( !sub_445ED0((int)v8, 2) )
      {
        goto LABEL_5;
      }
      ((PalScript *)this)->Create(id, (tagRECT *)pRect, (int)parent);
      goto LABEL_8;
    }
  }
  return result;
}

// 0x0043B660
int UIScene::Render_b660()
{
  int result; // eax
  LONG top; // edx
  tagRECT *p_m_rect; // edi
  int v5; // eax
  LONG bottom; // eax
  int v7; // ebx
  UIWnd *m_pChildWnd; // eax
  char *v9; // eax
  Parent_Data *v10; // eax
  int v11; // eax
  TextureLibDataBase *v12; // ecx
  LONG v13; // ecx
  LONG v14; // edx
  LONG v15; // edx
  LONG v16; // eax
  int m_benable; // eax
  UIWnd *v18; // eax
  char *left; // [esp-0x20] [ebp-0x124]
  char *v20; // [esp-0x20] [ebp-0x124]
  TextureLibDataBase *v21; // [esp-0x1C] [ebp-0x120]
  TextureLibDataBase *v22; // [esp-0x18] [ebp-0x11C]
  gbColorQuad v23; // [esp-0xC] [ebp-0x110] BYREF
  int p_nTex; // [esp-0x8] [ebp-0x10C]
  unsigned int m_bVisible; // [esp-0x4] [ebp-0x108]
  gbTextureArray *v26; // [esp+0x0] [ebp-0x104]
  _PlugInfo *v27; // [esp+0x4] [ebp-0x100]
  int nW; // [esp+0x10] [ebp-F4h] BYREF
  int v29; // [esp+0x18] [ebp-ECh] BYREF
  int v30; // [esp+0x1C] [ebp-E8h]
  LONG right; // [esp+0x20] [ebp-E4h]
  LONG v32; // [esp+0x24] [ebp-E0h]
  int nY; // [esp+0x28] [ebp-DCh] BYREF
  int v34; // [esp+0x2C] [ebp-D8h]
  LONG v35; // [esp+0x30] [ebp-D4h]
  LONG v36; // [esp+0x34] [ebp-D0h]
  int v37[16]; // [esp+0x38] [ebp-CCh] BYREF
  int v38; // [esp+0x78] [ebp-0x8C]
  int v39; // [esp+0x7C] [ebp-0x88] BYREF
  gbTextureArray v40; // [esp+0x80] [ebp-0x84] BYREF
  int v41; // [esp+0x100] [ebp-0x4]

  result = this->m_bvisible;
  if ( !result )
    return result;
  top = this->m_rect.top;
  p_m_rect = &this->m_rect;
  v5 = this->m_rect.left + 2;
  right = this->m_rect.right;
  v29 = v5;
  bottom = this->m_rect.bottom;
  v30 = top + 2;
  v32 = bottom;
  v7 = sub_445F60(0);
  if ( !v7 )
  {
    v15 = this->m_rect.bottom;
    v16 = this->m_rect.right;
    m_bVisible = (unsigned int)&unk_D91780;
    p_nTex = v15;
    v23.Color = v16;
    goto LABEL_17;
  }
  m_pChildWnd = this->m_pChildWnd;
  if ( m_pChildWnd )
  {
    v9 = (char *)&m_pChildWnd[-1].m_bfocus + 3;
    if ( v9 )
    {
      if ( v9 == (char *)1 )
      {
        m_bVisible = (unsigned int)this->m_bVisible;
        p_nTex = (int)&v40.nTex;
        v23.Color = (unsigned int)this + 372;
        v41 = 1;
        v40.nTex = v7;
        ((TextureLibDataBase *)&v29)->GetTextureInfo((char *)&this->m_rect);
      }
    }
    else
    {
      m_bVisible = (unsigned int)this->m_bVisible;
      p_nTex = 1;
      v23.Color = (unsigned int)&v39;
      v21 = (TextureLibDataBase *)this->m_rect.top;
      left = (char *)p_m_rect->left;
      v40.pTexPt[15] = (gbTexture *)1;
      v39 = v7;
      ((TextureLibDataBase *)v21)->GetLibInfo(left);
    }
  }
  else
  {
    v10 = this->m_bVisible;
    m_bVisible = 1;
    p_nTex = (int)v10;
    v23.Color = 276;
    v38 = 1;
    v37[0] = v7;
    ((TextureLibDataBase *)v37)->SetLibFolder((char *)&this->m_rect);
  }
  if ( this->m_benable )
    goto LABEL_18;
  v11 = *((_DWORD *)this + 90);
  if ( v11 )
  {
    if ( v11 == 1 )
    {
      m_bVisible = *(_DWORD *)&this->m_bOverlayRender;
      p_nTex = 1;
      v23.Color = (unsigned int)v37;
      v22 = (TextureLibDataBase *)this->m_rect.right;
      v20 = (char *)p_m_rect->left;
      v38 = 1;
      v37[0] = v7;
      ((TextureLibDataBase *)v22)->GetLibInfo(v20);
    }
    goto LABEL_18;
  }
  if ( !this->m_pTexture )
  {
    v13 = this->m_rect.bottom;
    v14 = this->m_rect.right;
    m_bVisible = (unsigned int)&unk_D91780;
    p_nTex = v13;
    v23.Color = v14;
LABEL_17:
    crt_sub_00540070();
    goto LABEL_18;
  }
  m_bVisible = *(_DWORD *)&this->m_bOverlayRender;
  p_nTex = 276;
  v23.Color = m_bVisible;
  ((TextureLibDataBase *)v12)->_CheckItem((char *)&this->m_rect, (char *)&this->m_rect);
LABEL_18:
  if ( *((_BYTE *)&this->m_hTexture + 4) )
  {
    nW = this->m_fontcolor.Color;
    nY = v29;
    v35 = right;
    m_benable = this->m_benable;
    v34 = v30;
    v36 = v32;
    if ( !m_benable || this->m_pChildWnd == (UIWnd *)2 )
    {
      BYTE2(nW) = (BYTE2(nW) - 64) & ((BYTE2(nW) - 64 < 0) - 1);
      BYTE1(nW) = (BYTE1(nW) - 64) & ((BYTE1(nW) - 64 < 0) - 1);
      v18 = this->m_pChildWnd;
      LOBYTE(nW) = (nW - 64) & (((unsigned __int8)nW - 64 < 0) - 1);
      if ( v18 == (UIWnd *)2 )
        v34 = v30 + 6;
    }
    UIRenderPar((int)(&this->m_hTexture + 1), (int)&nY, (int)&nW, 1, (gbColorQuad *)1, v26, v27);
  }
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  return result;
}

// 0x0043B900
BOOL UIScene::Update_b900(int nVal, int nVal2)
{
  tagRECT *p_m_rect; // ebp
  BOOL v6; // eax
  LONG left; // edx
  LONG top; // ecx
  int v9; // edi
  int v10; // ebp
  unsigned __int8 ChildWidget; // al
  UIWnd *m_pfather; // ecx
  UIWnd *v13; // ecx
  UIWnd *v14; // ecx
  int v15; // eax
  BOOL v16; // [esp+0xC] [ebp-0xC]
  POINT pt; // [esp+0x10] [ebp-0x8]

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
  {
    this->m_pChildWnd = 0;
    return 0;
  }
  if ( !nVal2 )
  {
    this->m_pChildWnd = 0;
    return ((UIListBox *)this)->Update(nVal, 0);
  }
  ((GRPinput *)&g_Input)->GetCursorPos();
  p_m_rect = &this->m_rect;
  v6 = PtInRect(&this->m_rect, pt);
  v16 = v6;
  if ( this->m_pChildWnd != (UIWnd *)2 )
  {
    if ( !v6 )
    {
      this->m_pChildWnd = 0;
      goto LABEL_14;
    }
    this->m_pChildWnd = (UIWnd *)1;
  }
  if ( !v6 )
  {
LABEL_14:
    if ( !this->m_bCursorLeft )
    {
      m_pfather = this->m_pfather;
      this->m_bCursorLeft = 1;
      if ( m_pfather )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))m_pfather->__vftable->OnMessage)(
// [VFTABLE]   m_pfather,
// [VFTABLE]   1003,
// [VFTABLE]   this->m_id,
// [VFTABLE]   0);
    }
    goto LABEL_17;
  }
  left = p_m_rect->left;
  top = this->m_rect.top;
  v9 = pt.x - p_m_rect->left;
  v10 = pt.y - top;
  if ( this->m_bVisible )
  {
    ChildWidget = this->GetChildWidget(pt.x - left, pt.y - top, 3);
  }
  else
  {
    if ( v9 >= *(_DWORD *)(sub_445F60(0) + 24) )
      v9 = *(_DWORD *)(sub_445F60(0) + 24) - 1;
    if ( v10 >= *(_DWORD *)(sub_445F60(0) + 28) )
      v10 = *(_DWORD *)(sub_445F60(0) + 28) - 1;
    ChildWidget = ((UIScene *)&this->m_nClipW)->GetPixelChannel(0, v9, v10, 3);
  }
  if ( ChildWidget < 6u )
  {
    v16 = 0;
    this->m_pChildWnd = 0;
  }
  else if ( g_Input.KeyInfo[0].PressTime == 1 )
  {
    this->m_pChildWnd = (UIWnd *)2;
    this->m_bCursorLeft = 0;
  }
  else
  {
    v14 = this->m_pfather;
    if ( v14 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v14->__vftable->OnMessage)(v14, 1002, this->m_id, 0);
    this->m_bCursorLeft = 0;
  }
LABEL_17:
  if ( this->m_pChildWnd == (UIWnd *)2 && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( v16 )
    {
      v13 = this->m_pfather;
      this->m_pChildWnd = (UIWnd *)1;
      if ( v13 )
// [VFTABLE] ((void ( *)(UIWnd *, int, void *, _DWORD))v13->__vftable->OnMessage)(v13, 1001, this->m_id, 0);
    }
    else
    {
      this->m_pChildWnd = 0;
    }
  }
  v15 = ((UIListBox *)this)->Update(nVal, nVal2);
  return v16 || v15;
}

// 0x0043BCE0
// write access to const memory has been detected, the output may be wrong!
int *UIScene::ctor()
{
  sub_445AA0();
  this->m_nShowState = 32;
  this->m_pChildWnd = (UIWnd *)32;
  *(&this->m_hTexture + 7) = 0x40000000;
  this->m_nClipX = 0;
  LOBYTE(this->m_nClipY) = 0;
  this->m_nRectX = 0;
  *(_DWORD *)&this->m_bCursorLeft = 0;
  *(&this->m_hTexture + 1) = 0;
  *(&this->m_hTexture + 3) = 0;
  *(&this->m_hTexture + 4) = 0;
  *(&this->m_hTexture + 5) = 0;
  *(&this->m_hTexture + 6) = 0;
  *(&this->m_hTexture + 8) = 0;
  *(&this->m_hTexture + 10) = 0;
  *(&this->m_hTexture + 11) = 0;
  *(&this->m_hTexture + 12) = 0;
  *(&this->m_hTexture + 13) = 0;
  *(&this->m_hTexture + 14) = 0;
  *(&this->m_hTexture + 15) = 0;
  this->m_nFieldD0 = 0;
  this->m_bVisible = 0;
  this->m_hFont = 0;
  this->m_fAngle = -1.7014636e38;
  this->m_fCameraOffset = NAN;
  gbColorQuad::ColorQuadFmt = 1;
  BYTE2(this->m_bFieldCC) = -1;
  BYTE1(this->m_bFieldCC) = 0;
  LOBYTE(this->m_bFieldCC) = 0;
  HIBYTE(this->m_bFieldCC) = -1;
  this->m_nRectY = 0;
  this->m_nClipW = 0;
  *(&this->m_hTexture + 9) = 0;
  this->m_hTexture = 0;
  *(&this->m_hTexture + 2) = 0;
  this->m_bEnabled = 0;
  this->m_pTexture = 0;
  *(_DWORD *)&this->m_bOverlayRender = 0;
  return (int *)this;
}

// 0x0043BE80
void UIScene::ReleaseTexture()
{
  int *p_m_nFieldD0; // esi
  int v2; // ebx

  p_m_nFieldD0 = &this->m_nFieldD0;
  v2 = 3;
  do
  {
    if ( *p_m_nFieldD0 )
    {
      ((gbRefObject *)*p_m_nFieldD0)->Release();
      *p_m_nFieldD0 = 0;
    }
    ++p_m_nFieldD0;
    --v2;
  }
  while ( v2 );
}

// 0x0043BEB0
void UIScene::SetTexture(LPCSTR lpString, char pData)
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
    v5 = *(gbRefObject **)&this->m_bCursorLeft;
    if ( v5 )
      ((gbRefObject *)v5)->Release();
    v6 = pData == 0;
    this->m_hTexture = 0;
    if ( v6 )
    {
      *(_DWORD *)&this->m_bCursorLeft = (*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(
                                          gfxMgr,
                                          v3);
    }
    else
    {
      v7 = *(_DWORD *)gfxMgr;
      v8 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v3);
      *(_DWORD *)&this->m_bCursorLeft = (*(int ( **)(gbGfxManager *, CHAR *))(v7 + 8))(gfxMgr, v8);
      this->m_hTexture = (int)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v3);
    }
    v9 = *(gbTexture **)&this->m_bCursorLeft;
    if ( v9 )
      ((gbTexture *)v9)->LoadTexture(1);
  }
}

// 0x0043C0F0
void UIScene::UpdateLayout(float fVal)
{
  int v3; // eax
  unsigned int m_dwColor; // edi
  int m_nLoadResource; // ecx
  int v6; // eax
  UIWnd *m_pChildWnd; // ebx
  __int64 v8; // rax
  int v9; // ecx
  UIWnd *v10; // edi
  __int64 v11; // rax
  int v12; // ecx
  int m_nNotifyRender; // ebx
  int m_nPosY; // ecx
  int v15; // eax
  UIWnd *v16; // ebp
  int v17; // edi
  __int64 v18; // rax
  int m_nShowState; // ecx
  int v20; // edi
  int v21; // ebp
  UIWnd *v22; // ebx
  int v23; // edi
  __int64 v24; // rax
  double v25; // st7
  int v26; // [esp+0x4] [ebp-0x4]

  if ( fVal >= 0.0 )
  {
    v3 = *(&this->m_hTexture + 14);
    if ( v3 )
    {
      if ( v3 == 1 )
      {
        m_dwColor = this->m_dwColor;
        m_nLoadResource = this->m_nLoadResource;
        v6 = *(&this->m_hTexture + 15);
        *((float *)&this->m_hTexture + 4) = (double)(int)this->m_dwColor
                                          - *((float *)&this->m_hTexture + 7)
                                          + *((float *)&this->m_hTexture + 13)
                                          - ((double)m_nLoadResource
                                           + *((float *)&this->m_hTexture + 12)
                                           + *((float *)&this->m_hTexture + 7));
        if ( v6 )
        {
          if ( v6 == 1 )
          {
            m_pChildWnd = this->m_pChildWnd;
            v8 = (__int64)((double)(int)(m_dwColor - (int)m_pChildWnd / 2)
                         - *((float *)&this->m_hTexture + 7)
                         + *((float *)&this->m_hTexture + 13));
            HIDWORD(v8) = this->m_nShowState;
            v9 = this->m_nNotifyRender + *(&this->m_hTexture + 9) - HIDWORD(v8);
            this->m_nRectW = v8;
            this->m_nRectH = v9;
            this->m_nScrollWidget = HIDWORD(v8) + v9;
            this->m_nPosX = (int)m_pChildWnd + v8;
          }
        }
        else
        {
          v10 = this->m_pChildWnd;
          v11 = (__int64)((double)(m_nLoadResource - (int)v10 / 2)
                        + *((float *)&this->m_hTexture + 12)
                        + *((float *)&this->m_hTexture + 7));
          HIDWORD(v11) = this->m_nShowState;
          v12 = this->m_nPosY + *(&this->m_hTexture + 9) - HIDWORD(v11);
          this->m_nRectW = v11;
          this->m_nRectH = v12;
          this->m_nScrollWidget = HIDWORD(v11) + v12;
          this->m_nPosX = (int)v10 + v11;
        }
      }
      goto LABEL_13;
    }
    m_nNotifyRender = this->m_nNotifyRender;
    m_nPosY = this->m_nPosY;
    v15 = *(&this->m_hTexture + 15);
    *((float *)&this->m_hTexture + 4) = (double)this->m_nNotifyRender
                                      - *((float *)&this->m_hTexture + 7)
                                      + *((float *)&this->m_hTexture + 11)
                                      - ((double)m_nPosY
                                       + *((float *)&this->m_hTexture + 10)
                                       + *((float *)&this->m_hTexture + 7));
    if ( v15 )
    {
      if ( v15 != 1 )
      {
LABEL_13:
        v25 = fVal / *((float *)&this->m_hTexture + 4);
        *((float *)&this->m_hTexture + 5) = fVal;
        *((float *)&this->m_hTexture + 8) = v25;
        return;
      }
      v16 = this->m_pChildWnd;
      v17 = this->m_nLoadResource + *(&this->m_hTexture + 9) - (_DWORD)v16;
      v26 = m_nNotifyRender - this->m_nShowState / 2;
      this->m_nRectW = v17;
      v18 = (__int64)((double)v26 - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 11));
      m_nShowState = this->m_nShowState;
      this->m_nRectH = v18;
      v20 = (int)v16 + v17;
      this->m_nScrollWidget = m_nShowState + v18;
    }
    else
    {
      v21 = this->m_nShowState;
      v22 = this->m_pChildWnd;
      v23 = this->m_nLoadResource + *(&this->m_hTexture + 9) - (_DWORD)v22;
      this->m_nRectW = v23;
      v24 = (__int64)((double)(m_nPosY - v21 / 2)
                    + *((float *)&this->m_hTexture + 10)
                    + *((float *)&this->m_hTexture + 7));
      this->m_nRectH = v24;
      this->m_nScrollWidget = v21 + v24;
      v20 = (int)v22 + v23;
    }
    this->m_nPosX = v20;
    goto LABEL_13;
  }
}

// 0x0043C330
int UIScene::RefreshLayout()
{
  int v2; // eax
  int result; // eax
  unsigned int m_dwColor; // edi
  int m_nLoadResource; // ecx
  int v6; // eax
  UIWnd *m_pChildWnd; // ebx
  __int64 v8; // rax
  int v9; // ecx
  UIWnd *v10; // edi
  __int64 v11; // rax
  int v12; // ecx
  int m_nNotifyRender; // ebx
  int m_nPosY; // ecx
  int v15; // eax
  UIWnd *v16; // ebp
  int v17; // edi
  __int64 v18; // rax
  int m_nShowState; // ecx
  int v20; // ebp
  UIWnd *v21; // ebx
  int v22; // edi
  __int64 v23; // rax
  int v24; // [esp+0x14] [ebp-0x4]

  v2 = *(&this->m_hTexture + 14);
  *(&this->m_hTexture + 3) = 0;
  *(&this->m_hTexture + 6) = 0;
  if ( v2 )
  {
    result = v2 - 1;
    if ( !result )
    {
      m_dwColor = this->m_dwColor;
      m_nLoadResource = this->m_nLoadResource;
      v6 = *(&this->m_hTexture + 15);
      *((float *)&this->m_hTexture + 4) = (double)(int)this->m_dwColor
                                        - *((float *)&this->m_hTexture + 7)
                                        + *((float *)&this->m_hTexture + 13)
                                        - ((double)m_nLoadResource
                                         + *((float *)&this->m_hTexture + 7)
                                         + *((float *)&this->m_hTexture + 12));
      if ( v6 )
      {
        result = v6 - 1;
        if ( !result )
        {
          m_pChildWnd = this->m_pChildWnd;
          v8 = (__int64)((double)(int)(m_dwColor - (int)m_pChildWnd / 2)
                       - *((float *)&this->m_hTexture + 7)
                       + *((float *)&this->m_hTexture + 13));
          HIDWORD(v8) = this->m_nShowState;
          v9 = this->m_nNotifyRender + *(&this->m_hTexture + 9) - HIDWORD(v8);
          this->m_nRectW = v8;
          this->m_nRectH = v9;
          result = (int)m_pChildWnd + v8;
          this->m_nScrollWidget = HIDWORD(v8) + v9;
          this->m_nPosX = result;
        }
      }
      else
      {
        v10 = this->m_pChildWnd;
        v11 = (__int64)((double)(m_nLoadResource - (int)v10 / 2)
                      + *((float *)&this->m_hTexture + 7)
                      + *((float *)&this->m_hTexture + 12));
        HIDWORD(v11) = this->m_nShowState;
        v12 = this->m_nPosY + *(&this->m_hTexture + 9) - HIDWORD(v11);
        this->m_nRectW = v11;
        this->m_nRectH = v12;
        result = (int)v10 + v11;
        this->m_nScrollWidget = HIDWORD(v11) + v12;
        this->m_nPosX = result;
      }
    }
  }
  else
  {
    m_nNotifyRender = this->m_nNotifyRender;
    m_nPosY = this->m_nPosY;
    v15 = *(&this->m_hTexture + 15);
    *((float *)&this->m_hTexture + 4) = (double)this->m_nNotifyRender
                                      - *((float *)&this->m_hTexture + 7)
                                      + *((float *)&this->m_hTexture + 11)
                                      - ((double)m_nPosY
                                       + *((float *)&this->m_hTexture + 7)
                                       + *((float *)&this->m_hTexture + 10));
    if ( v15 )
    {
      result = v15 - 1;
      if ( !result )
      {
        v16 = this->m_pChildWnd;
        v17 = this->m_nLoadResource + *(&this->m_hTexture + 9) - (_DWORD)v16;
        v24 = m_nNotifyRender - this->m_nShowState / 2;
        this->m_nRectW = v17;
        v18 = (__int64)((double)v24 - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 11));
        m_nShowState = this->m_nShowState;
        this->m_nRectH = v18;
        result = m_nShowState + v18;
        this->m_nPosX = (int)v16 + v17;
        this->m_nScrollWidget = result;
      }
    }
    else
    {
      v20 = this->m_nShowState;
      v21 = this->m_pChildWnd;
      v22 = this->m_nLoadResource + *(&this->m_hTexture + 9) - (_DWORD)v21;
      this->m_nRectW = v22;
      v23 = (__int64)((double)(m_nPosY - v20 / 2)
                    + *((float *)&this->m_hTexture + 7)
                    + *((float *)&this->m_hTexture + 10));
      this->m_nRectH = v23;
      result = v20 + v23;
      this->m_nScrollWidget = result;
      this->m_nPosX = (int)v21 + v22;
    }
  }
  return result;
}

// 0x0043C7B0
gbVFileSystem * UIScene::CreateScrollWidget(
        
        int id,
        int *p_DWORD,
        int parent,
        gbVFileSystem *pVFileSystem,
        char pData)
{
  int m_nShowState; // ebp
  UIWnd *m_pChildWnd; // ebx
  __int64 v9; // rax
  __int64 v10; // rax
  double m_nNotifyRender; // st7
  gbVFileSystem *result; // eax
  double v13; // st7
  double v14; // st6
  double v15; // st7
  int v16; // ebp
  int *p_m_nFieldD0; // edi
  int v18; // ebx
  CHAR *v19; // eax
  OpenBaseFile v20; // [esp+0x10] [ebp-0x110] BYREF
  char Buffer[256]; // [esp+0x14] [ebp-0x10C] BYREF
  int v22; // [esp+0x11C] [ebp-0x4]

  m_nShowState = this->m_nShowState;
  this->m_nPosY = *p_DWORD;
  this->m_nLoadResource = p_DWORD[1];
  this->m_nNotifyRender = p_DWORD[2];
  this->m_dwColor = p_DWORD[3];
  this->m_hScrollBar = *p_DWORD;
  this->m_nColors = p_DWORD[1];
  this->m_bLoadState = p_DWORD[2];
  m_pChildWnd = this->m_pChildWnd;
  this->m_pChildData = (char *)p_DWORD[3];
  this->m_nRectW = p_DWORD[1] - (_DWORD)m_pChildWnd;
  v9 = (__int64)((double)(*p_DWORD - m_nShowState / 2) + *((float *)&this->m_hTexture + 7));
  this->m_nRectH = v9;
  v20.m_plastsys = (gbVFileSystem *)(m_nShowState + v9);
  v10 = (__int64)((double)(m_nShowState + (int)v9) - *((float *)&this->m_hTexture + 7));
  m_nNotifyRender = (double)this->m_nNotifyRender;
  HIDWORD(v10) = this->m_nRectW;
  this->m_nScrollWidget = v10;
  result = pVFileSystem;
  v13 = m_nNotifyRender - *((float *)&this->m_hTexture + 7);
  v14 = (double)this->m_nPosY + *((float *)&this->m_hTexture + 7);
  this->m_nPosX = (int)m_pChildWnd + HIDWORD(v10);
  v15 = v13 - v14;
  *((float *)&this->m_hTexture + 4) = v15;
  *((float *)&this->m_hTexture + 5) = v15;
  *((float *)&this->m_hTexture + 8) = v15 / v15;
  if ( pVFileSystem )
  {
    v22 = 0;
    v16 = 0;
    p_m_nFieldD0 = &this->m_nFieldD0;
    do
    {
      p_m_nFieldD0[3] = 0;
      if ( *p_m_nFieldD0 )
        ((gbRefObject *)*p_m_nFieldD0)->Release();
      sprintf(Buffer, "%s%d.tga", (const char *)pVFileSystem, v16);
      if ( pData )
      {
        v18 = *(_DWORD *)gfxMgr;
        v19 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(Buffer);
        *p_m_nFieldD0 = (*(int ( **)(gbGfxManager *, CHAR *))(v18 + 8))(gfxMgr, v19);
        p_m_nFieldD0[3] = (int)((TextureLibDataBase *)&stru_1894B78)->CreateParentData(Buffer);
      }
      else
      {
        *p_m_nFieldD0 = (*(int ( **)(gbGfxManager *, char *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, Buffer);
      }
      if ( *p_m_nFieldD0 )
        ((gbTexture *)*p_m_nFieldD0)->LoadTexture(1);
      ++v16;
      ++p_m_nFieldD0;
    }
    while ( v16 < 3 );
    *(_DWORD *)&this->_todo_050 = this->m_nRectW;
    LODWORD(this->m_fScaleX) = *p_DWORD;
    this->m_nScrollState = p_DWORD[2];
    this->m_nScrollIdx = p_DWORD[3];
    LODWORD(this->m_fScaleY) = id;
    this->m_nViewW = parent;
    ((PalScript *)this)->Create(id, (tagRECT *)&this->m_fScaleX, parent);
    v22 = -1;
  }
  return result;
}

// 0x0043C9D0
void UIScene::fill(PlayerItem *a2, PlayerItem *a3)
{
  float *v3; // ecx
  int v4; // eax
  float *v5; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  int v9; // edi
  __int64 v10; // rax
  int v11; // ecx
  int v12; // ebp
  int v13; // ecx
  int v14; // ebx
  int v15; // ecx
  int v16; // eax
  int v17; // ebp
  int v18; // edi
  __int64 v19; // rax
  int v20; // ecx
  int v21; // edi
  int v22; // ebp
  int v23; // ebx
  int v24; // edi
  __int64 v25; // rax
  PlayerItem *a1a; // [esp+0x18] [ebp+0x4]

  v4 = (int)a1;
  v5 = v3;
  if ( (int)a1 <= 1 )
  {
    if ( (int)a1 < 0 )
      v4 = 0;
  }
  else
  {
    v4 = 1;
  }
  *((_DWORD *)v3 + 66) = v4;
  if ( !v4 )
  {
    v14 = *((_DWORD *)v3 + 36);
    v15 = *((_DWORD *)v3 + 34);
    v16 = *((_DWORD *)v5 + 67);
    v5[56] = (double)*((int *)v5 + 36) - v5[59] + v5[63] - ((double)v15 + v5[62] + v5[59]);
    if ( v16 )
    {
      if ( v16 != 1 )
        goto LABEL_17;
      v17 = *((_DWORD *)v5 + 24);
      v18 = *((_DWORD *)v5 + 35) + *((_DWORD *)v5 + 61) - v17;
      a1a = (PlayerItem *)(v14 - *((_DWORD *)v5 + 23) / 2);
      *((_DWORD *)v5 + 31) = v18;
      v19 = (__int64)((double)(int)a1a - v5[59] + v5[63]);
      v20 = *((_DWORD *)v5 + 23);
      *((_DWORD *)v5 + 30) = v19;
      v21 = v17 + v18;
      *((_DWORD *)v5 + 32) = v20 + v19;
    }
    else
    {
      v22 = *((_DWORD *)v5 + 23);
      v23 = *((_DWORD *)v5 + 24);
      v24 = *((_DWORD *)v5 + 35) + *((_DWORD *)v5 + 61) - v23;
      *((_DWORD *)v5 + 31) = v24;
      v25 = (__int64)((double)(v15 - v22 / 2) + v5[62] + v5[59]);
      *((_DWORD *)v5 + 30) = v25;
      *((_DWORD *)v5 + 32) = v22 + v25;
      v21 = v23 + v24;
    }
    *((_DWORD *)v5 + 33) = v21;
    goto LABEL_17;
  }
  if ( v4 == 1 )
  {
    v6 = *((_DWORD *)v3 + 37);
    v7 = *((_DWORD *)v5 + 35);
    v8 = *((_DWORD *)v5 + 67);
    v5[56] = (double)*((int *)v5 + 37) - v5[59] + v5[65] - ((double)v7 + v5[64] + v5[59]);
    if ( !v8 )
    {
      v9 = *((_DWORD *)v5 + 24);
      v10 = (__int64)((double)(v7 - v9) + v5[64] + v5[59]);
      *((float *)&v10 + 1) = v5[23];
      v11 = *((_DWORD *)v5 + 61);
      v12 = *((_DWORD *)v5 + 34);
      *((_DWORD *)v5 + 31) = v10;
      goto LABEL_10;
    }
    if ( v8 == 1 )
    {
      v9 = *((_DWORD *)v5 + 24);
      v10 = (__int64)((double)(v6 - v9) - v5[59] + v5[65]);
      *((float *)&v10 + 1) = v5[23];
      v11 = *((_DWORD *)v5 + 61);
      v12 = *((_DWORD *)v5 + 36);
      *((_DWORD *)v5 + 31) = v10;
LABEL_10:
      v13 = v12 + v11 - HIDWORD(v10);
      *((_DWORD *)v5 + 30) = v13;
      *((_DWORD *)v5 + 32) = HIDWORD(v10) + v13;
      *((_DWORD *)v5 + 33) = v9 + v10;
    }
  }
LABEL_17:
  v5[60] = v5[57] / v5[56];
}

// 0x0043CBD0
int UIScene::ResizeContentAlt(int nVal)
{
  int v3; // eax
  int result; // eax
  unsigned int m_dwColor; // ecx
  int v6; // edx
  UIWnd *v7; // edi
  __int64 v8; // rax
  int v9; // ecx
  int v10; // ebp
  int v11; // ecx
  int m_nNotifyRender; // ebx
  int m_nPosY; // ecx
  int v14; // eax
  UIWnd *m_pChildWnd; // ebp
  int v16; // edi
  __int64 v17; // rax
  int m_nShowState; // ecx
  int v19; // edi
  int v20; // ebp
  UIWnd *v21; // ebx
  int v22; // edi
  __int64 v23; // rax
  int nVala; // [esp+0x18] [ebp+0x4]

  *(&this->m_hTexture + 15) = nVal;
  if ( nVal < 0 )
    *(&this->m_hTexture + 15) = 0;
  if ( *(&this->m_hTexture + 15) > 1 )
    *(&this->m_hTexture + 15) = 1;
  v3 = *(&this->m_hTexture + 14);
  if ( !v3 )
  {
    m_nNotifyRender = this->m_nNotifyRender;
    m_nPosY = this->m_nPosY;
    v14 = *(&this->m_hTexture + 15);
    *((float *)&this->m_hTexture + 4) = (double)this->m_nNotifyRender
                                      - *((float *)&this->m_hTexture + 7)
                                      + *((float *)&this->m_hTexture + 11)
                                      - ((double)m_nPosY
                                       + *((float *)&this->m_hTexture + 10)
                                       + *((float *)&this->m_hTexture + 7));
    if ( v14 )
    {
      result = v14 - 1;
      if ( result )
        goto LABEL_17;
      m_pChildWnd = this->m_pChildWnd;
      v16 = this->m_nLoadResource + *(&this->m_hTexture + 9) - (_DWORD)m_pChildWnd;
      nVala = m_nNotifyRender - this->m_nShowState / 2;
      this->m_nRectW = v16;
      v17 = (__int64)((double)nVala - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 11));
      m_nShowState = this->m_nShowState;
      this->m_nRectH = v17;
      result = m_nShowState + v17;
      v19 = (int)m_pChildWnd + v16;
      this->m_nScrollWidget = result;
    }
    else
    {
      v20 = this->m_nShowState;
      v21 = this->m_pChildWnd;
      v22 = this->m_nLoadResource + *(&this->m_hTexture + 9) - (_DWORD)v21;
      this->m_nRectW = v22;
      v23 = (__int64)((double)(m_nPosY - v20 / 2)
                    + *((float *)&this->m_hTexture + 10)
                    + *((float *)&this->m_hTexture + 7));
      this->m_nRectH = v23;
      result = v20 + v23;
      this->m_nScrollWidget = result;
      v19 = (int)v21 + v22;
    }
    this->m_nPosX = v19;
    goto LABEL_17;
  }
  result = v3 - 1;
  if ( !result )
  {
    m_dwColor = this->m_dwColor;
    result = this->m_nLoadResource;
    v6 = *(&this->m_hTexture + 15);
    *((float *)&this->m_hTexture + 4) = (double)(int)this->m_dwColor
                                      - *((float *)&this->m_hTexture + 7)
                                      + *((float *)&this->m_hTexture + 13)
                                      - ((double)result
                                       + *((float *)&this->m_hTexture + 12)
                                       + *((float *)&this->m_hTexture + 7));
    if ( !v6 )
    {
      v7 = this->m_pChildWnd;
      v8 = (__int64)((double)(result - (int)v7) + *((float *)&this->m_hTexture + 12) + *((float *)&this->m_hTexture + 7));
      HIDWORD(v8) = this->m_nShowState;
      v9 = *(&this->m_hTexture + 9);
      v10 = this->m_nPosY;
      this->m_nRectW = v8;
      goto LABEL_10;
    }
    if ( v6 == 1 )
    {
      v7 = this->m_pChildWnd;
      v8 = (__int64)((double)(int)(m_dwColor - (_DWORD)v7)
                   - *((float *)&this->m_hTexture + 7)
                   + *((float *)&this->m_hTexture + 13));
      HIDWORD(v8) = this->m_nShowState;
      v9 = *(&this->m_hTexture + 9);
      v10 = this->m_nNotifyRender;
      this->m_nRectW = v8;
LABEL_10:
      v11 = v10 + v9 - HIDWORD(v8);
      this->m_nRectH = v11;
      result = (int)v7 + v8;
      this->m_nScrollWidget = HIDWORD(v8) + v11;
      this->m_nPosX = result;
    }
  }
LABEL_17:
  *((float *)&this->m_hTexture + 8) = *((float *)&this->m_hTexture + 5) / *((float *)&this->m_hTexture + 4);
  return result;
}

// 0x0043CDF0
int UIScene::Render_cdf0()
{
  int *p_m_nPosY; // edi
  int v3; // eax
  int v4; // eax
  char *v5; // ebx
  double v6; // st7
  __int64 v7; // rax
  double m_nNotifyRender; // st7
  double v9; // st7
  int v10; // ebx
  __int64 v11; // rax
  double v12; // st7
  __int64 v13; // rax
  double v14; // st7
  __int64 v15; // rax
  int v16; // eax
  double v17; // st7
  double v18; // st6
  __int64 v19; // rax
  double v20; // st7
  double v21; // st7
  int v22; // edi
  double v23; // st7
  __int64 v24; // rax
  int v25; // ecx
  int result; // eax
  int v27[16]; // [esp+0x10] [ebp-0x44] BYREF
  int v28; // [esp+0x50] [ebp-0x4]

  if ( *(_DWORD *)&this->m_bCursorLeft )
  {
    v27[0] = *(_DWORD *)&this->m_bCursorLeft;
    p_m_nPosY = &this->m_nPosY;
    v28 = 1;
    ((TextureLibDataBase *)v27)->SetLibFolder((char *)&this->m_nPosY);
  }
  else
  {
    p_m_nPosY = &this->m_nPosY;
    crt_sub_00540070();
  }
  v3 = *(&this->m_hTexture + 14);
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      v4 = *(&this->m_hTexture + 15);
      if ( v4 )
      {
        if ( v4 == 1 )
        {
          v5 = (char *)(__int64)((double)(int)this->m_dwColor
                               - (*((float *)&this->m_hTexture + 12)
                                + *((float *)&this->m_hTexture + 7)));
          this->m_pChildData = v5;
          v6 = (double)(int)v5;
          v7 = (__int64)(v6 - *((float *)&this->m_hTexture + 3));
          this->m_nColors = v7;
          if ( (double)(int)&v5[-v7] > *((float *)&this->m_hTexture + 4) )
            this->m_nColors = (__int64)(v6 - *((float *)&this->m_hTexture + 4));
          m_nNotifyRender = (double)this->m_nNotifyRender;
          this->m_hScrollBar = (__int64)((double)*p_m_nPosY + *((float *)&this->m_hTexture + 7));
          this->m_bLoadState = (__int64)(m_nNotifyRender - *((float *)&this->m_hTexture + 7));
        }
      }
      else
      {
        v9 = (double)*p_m_nPosY;
        v10 = (__int64)(*((float *)&this->m_hTexture + 12)
                      + *((float *)&this->m_hTexture + 7)
                      + (double)this->m_nLoadResource);
        this->m_nColors = v10;
        v11 = (__int64)(v9 + *((float *)&this->m_hTexture + 7));
        v12 = (double)this->m_nNotifyRender;
        this->m_hScrollBar = v11;
        v13 = (__int64)(v12 - *((float *)&this->m_hTexture + 7));
        v14 = (double)v10;
        this->m_bLoadState = v13;
        v15 = (__int64)(v14 + *((float *)&this->m_hTexture + 3));
        this->m_pChildData = (char *)v15;
        if ( (double)((int)v15 - v10) > *((float *)&this->m_hTexture + 4) )
          this->m_pChildData = (char *)(__int64)(v14 + *((float *)&this->m_hTexture + 4));
      }
    }
  }
  else
  {
    v16 = *(&this->m_hTexture + 15);
    if ( v16 )
    {
      if ( v16 != 1 )
        goto LABEL_20;
      v17 = (double)this->m_nNotifyRender;
      v18 = *((float *)&this->m_hTexture + 10) + *((float *)&this->m_hTexture + 7);
      this->m_nColors = (__int64)((double)this->m_nLoadResource + *((float *)&this->m_hTexture + 7));
      v19 = (__int64)(v17 - v18);
      v20 = v17 - *((float *)&this->m_hTexture + 3);
      this->m_bLoadState = v19;
      this->m_hScrollBar = (__int64)v20;
      if ( (double)(int)(v19 - (__int64)v20) > *((float *)&this->m_hTexture + 4) )
        this->m_hScrollBar = (__int64)((double)(int)v19 - *((float *)&this->m_hTexture + 4));
    }
    else
    {
      v21 = *((float *)&this->m_hTexture + 10) + *((float *)&this->m_hTexture + 7) + (double)*p_m_nPosY;
      this->m_nColors = (__int64)((double)this->m_nLoadResource + *((float *)&this->m_hTexture + 7));
      v22 = (__int64)v21;
      this->m_hScrollBar = v22;
      v23 = (double)v22;
      v24 = (__int64)(v23 + *((float *)&this->m_hTexture + 3));
      this->m_bLoadState = v24;
      if ( (double)((int)v24 - v22) > *((float *)&this->m_hTexture + 4) )
        this->m_bLoadState = (__int64)(v23 + *((float *)&this->m_hTexture + 4));
    }
    this->m_pChildData = (char *)(__int64)((double)(int)this->m_dwColor - *((float *)&this->m_hTexture + 7));
  }
LABEL_20:
  if ( *(&this->m_hTexture + 1) )
  {
    v27[0] = *(&this->m_hTexture + 1);
    v28 = 1;
    ((TextureLibDataBase *)&this->m_wndcolor)->SetLibFolder((char *)&this->m_hScrollBar);
  }
  else
  {
    crt_sub_00540070();
  }
  if ( this != (UIScene *)-180 )
  {
    v25 = *(&this->m_nFieldD0 + this->m_nRectX);
    v28 = 1;
    v27[0] = v25;
    ((TextureLibDataBase *)v27)->SetLibFolder((char *)&this->m_nRectH);
  }
// [VFTABLE] ((UIWnd *)&this->__vftable)->Render();
  return result;
}

// 0x0043D1A0
BOOL UIScene::CheckMouseHit(int nVal, int nVal2)
{
  int v5; // eax
  int m_nPosX; // eax
  int m_nRectW; // ecx
  int m_nScrollWidget; // eax
  int m_nRectH; // ecx
  char m_nClipY; // al
  int m_nRectX; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // eax
  UIWnd *m_pChildWnd; // edi
  double v18; // st7
  double v19; // st7
  double v20; // st6
  int v21; // ecx
  double v22; // st7
  int v23; // eax
  int v24; // edx
  int v25; // ecx
  int v26; // eax
  double v27; // st7
  UIWnd *v28; // edi
  double v29; // st7
  double v30; // st7
  double v31; // st6
  double v32; // st7
  int v33; // ecx
  int m_nViewW; // edi
  int v35; // eax
  LONG m_nPosY; // eax
  LONG x; // edx
  int v38; // ecx
  bool v39; // cc
  int m_nShowState; // edi
  double v41; // st7
  int v42; // edx
  double v43; // st7
  double v44; // st7
  double v45; // st6
  int v46; // edx
  LONG v47; // eax
  LONG v48; // edx
  int v49; // ecx
  double v50; // st7
  int v51; // edx
  double v52; // st7
  double v53; // st6
  double v54; // st7
  int v55; // ecx
  int v56; // edx
  int v57; // eax
  int m_nLoadResource; // [esp+0x8] [ebp-0x28]
  int v59; // [esp+0x8] [ebp-0x28]
  int m_nNotifyRender; // [esp+0x8] [ebp-0x28]
  int m_dwColor; // [esp+0xC] [ebp-0x24]
  int v62; // [esp+0xC] [ebp-0x24]
  int v63; // [esp+0x10] [ebp-0x20]
  POINT pt; // [esp+0x18] [ebp-0x18]
  int pOut; // [esp+0x20] [ebp-0x10] BYREF
  int pOut2; // [esp+0x24] [ebp-0xC] BYREF
  struct tagPOINT Point; // [esp+0x28] [ebp-0x8]

  if ( !nVal2 )
    return ((UIListBox *)this)->Update(nVal, 0);
  ((GRPinput *)&g_Input)->GetCursorPos();
  if ( this->m_nRectX == 1 || (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( PtInRect((const RECT *)&this->m_nRectH, pt) )
    {
      this->m_nRectX = 1;
      if ( (g_Input.KeyInfo[0].Data & 0xF) == 1 )
      {
        m_nClipY = this->m_nClipY;
        this->m_nRectX = 2;
        if ( !m_nClipY )
          *(POINT *)&this->m_nRectY = pt;
        LOBYTE(this->m_nClipY) = 1;
        goto LABEL_21;
      }
    }
    else
    {
      m_nRectX = this->m_nRectX;
      this->m_nRectX = 0;
      if ( m_nRectX == 2 )
      {
        LOBYTE(this->m_nClipY) = 1;
        goto LABEL_21;
      }
    }
    LOBYTE(this->m_nClipY) = 0;
    goto LABEL_21;
  }
  v5 = *(&this->m_hTexture + 14);
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      m_nPosX = this->m_nPosX;
      m_nRectW = this->m_nRectW;
      if ( pt.y > 2 * m_nPosX - m_nRectW || pt.y < 2 * m_nRectW - m_nPosX )
        goto LABEL_9;
    }
  }
  else
  {
    m_nScrollWidget = this->m_nScrollWidget;
    m_nRectH = this->m_nRectH;
    if ( pt.x > 2 * m_nScrollWidget - m_nRectH )
    {
LABEL_9:
      LOBYTE(this->m_nClipY) = 0;
      this->m_nRectX = 0;
      goto LABEL_21;
    }
    if ( pt.x < 2 * m_nRectH - m_nScrollWidget )
    {
      LOBYTE(this->m_nClipY) = 0;
      this->m_nRectX = 0;
    }
  }
LABEL_21:
  if ( !LOBYTE(this->m_nClipY) )
    goto LABEL_54;
  ((GRPinput *)&g_Input)->GetMousePos(&pOut, &pOut2);
  ((GRPinput *)&g_Input)->GetCursorPos();
  v12 = *(&this->m_hTexture + 14);
  if ( v12 )
  {
    if ( v12 != 1 )
      goto LABEL_54;
    v13 = *(&this->m_hTexture + 15);
    if ( v13 )
    {
      if ( v13 == 1 )
      {
        v14 = this->m_nPosX;
        m_dwColor = this->m_dwColor;
        v15 = -pOut2;
        v63 = -pOut2;
        this->m_nClipX = -pOut2;
        if ( v14 <= m_dwColor )
        {
          v16 = this->m_nRectW;
          m_nLoadResource = this->m_nLoadResource;
          if ( v16 >= m_nLoadResource )
          {
            m_pChildWnd = this->m_pChildWnd;
            this->m_nRectW = v16 - v15;
            v18 = (double)v63 + *((float *)&this->m_hTexture + 3);
            this->m_nPosX = (int)m_pChildWnd + v16 - v15;
            this->m_nClipW = pt.y;
            *((float *)&this->m_hTexture + 3) = v18;
            *((float *)&this->m_hTexture + 6) = v18 * *((float *)&this->m_hTexture + 8);
            v19 = (double)((int)m_pChildWnd / 2);
            v20 = (double)m_nLoadResource + *((float *)&this->m_hTexture + 12) + *((float *)&this->m_hTexture + 7) - v19;
            if ( (double)(v16 - v15) <= v20 )
            {
              v21 = *(&this->m_hTexture + 5);
              this->m_nRectW = (__int64)v20;
              *(&this->m_hTexture + 6) = v21;
              this->m_nPosX = (int)m_pChildWnd + (__int64)v20;
              *(&this->m_hTexture + 3) = *(&this->m_hTexture + 4);
            }
            v22 = v19 + (double)m_dwColor - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 13);
            if ( (double)this->m_nPosX >= v22 )
            {
              this->m_nPosX = (__int64)v22;
              this->m_nRectW = (__int64)v22 - (_DWORD)m_pChildWnd;
              *(&this->m_hTexture + 3) = 0;
              *(&this->m_hTexture + 6) = 0;
            }
          }
        }
      }
    }
    else
    {
      v23 = this->m_dwColor;
      v24 = this->m_nPosX;
      v25 = pOut2;
      this->m_nClipX = pOut2;
      v62 = v23;
      if ( v24 <= v23 )
      {
        v26 = this->m_nRectW;
        v59 = this->m_nLoadResource;
        if ( v26 >= v59 )
        {
          v27 = (double)pOut2;
          v28 = this->m_pChildWnd;
          this->m_nRectW = v25 + v26;
          v29 = v27 + *((float *)&this->m_hTexture + 3);
          this->m_nPosX = (int)v28 + v25 + v26;
          this->m_nClipW = pt.y;
          *((float *)&this->m_hTexture + 3) = v29;
          *((float *)&this->m_hTexture + 6) = v29 * *((float *)&this->m_hTexture + 8);
          v30 = (double)((int)v28 / 2);
          v31 = (double)v59 + *((float *)&this->m_hTexture + 12) + *((float *)&this->m_hTexture + 7) - v30;
          if ( (double)(v25 + v26) <= v31 )
          {
            this->m_nRectW = (__int64)v31;
            this->m_nPosX = (int)v28 + (__int64)v31;
            *(&this->m_hTexture + 3) = 0;
            *(&this->m_hTexture + 6) = 0;
          }
          v32 = v30 + (double)v62 - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 13);
          if ( (double)this->m_nPosX >= v32 )
          {
            v33 = *(&this->m_hTexture + 5);
            this->m_nPosX = (__int64)v32;
            *(&this->m_hTexture + 6) = v33;
            this->m_nRectW = (__int64)v32 - (_DWORD)v28;
            *(&this->m_hTexture + 3) = *(&this->m_hTexture + 4);
          }
        }
      }
    }
    m_nViewW = this->m_nViewW;
    *(POINT *)&this->m_nRectY = pt;
    if ( !m_nViewW )
      goto LABEL_54;
    goto LABEL_53;
  }
  v35 = *(&this->m_hTexture + 15);
  if ( v35 )
  {
    if ( v35 != 1 )
      goto LABEL_52;
    m_nPosY = this->m_nPosY;
    x = Point.x;
    v38 = pOut;
    v39 = Point.x < m_nPosY;
    this->m_nClipX = pOut;
    if ( v39 )
      goto LABEL_52;
    m_nNotifyRender = this->m_nNotifyRender;
    if ( x > m_nNotifyRender )
      goto LABEL_52;
    m_nShowState = this->m_nShowState;
    v41 = (double)pOut;
    v42 = this->m_nRectH - v38;
    this->m_nRectY = pt.x;
    this->m_nRectH = v42;
    v43 = v41 + *((float *)&this->m_hTexture + 3);
    this->m_nScrollWidget = m_nShowState + v42;
    *((float *)&this->m_hTexture + 3) = v43;
    *((float *)&this->m_hTexture + 6) = v43 * *((float *)&this->m_hTexture + 8);
    v44 = (double)(m_nShowState / 2);
    v45 = (double)m_nPosY + *((float *)&this->m_hTexture + 10) + *((float *)&this->m_hTexture + 7) - v44;
    if ( (double)v42 <= v45 )
    {
      v46 = *(&this->m_hTexture + 4);
      this->m_nRectH = (__int64)v45;
      *(&this->m_hTexture + 3) = v46;
      this->m_nScrollWidget = m_nShowState + (__int64)v45;
      *(&this->m_hTexture + 6) = *(&this->m_hTexture + 5);
    }
  }
  else
  {
    v47 = this->m_nPosY;
    v48 = Point.x;
    v49 = pOut;
    v39 = Point.x < v47;
    this->m_nClipX = pOut;
    if ( v39 )
      goto LABEL_52;
    m_nNotifyRender = this->m_nNotifyRender;
    if ( v48 > m_nNotifyRender )
      goto LABEL_52;
    m_nShowState = this->m_nShowState;
    v50 = (double)pOut;
    v51 = v49 + this->m_nRectH;
    this->m_nRectY = pt.x;
    this->m_nRectH = v51;
    v52 = v50 + *((float *)&this->m_hTexture + 3);
    this->m_nScrollWidget = m_nShowState + v51;
    *((float *)&this->m_hTexture + 3) = v52;
    *((float *)&this->m_hTexture + 6) = v52 * *((float *)&this->m_hTexture + 8);
    v44 = (double)(m_nShowState / 2);
    v53 = (double)v47 + *((float *)&this->m_hTexture + 10) + *((float *)&this->m_hTexture + 7) - v44;
    if ( (double)v51 <= v53 )
    {
      this->m_nRectH = (__int64)v53;
      this->m_nScrollWidget = m_nShowState + (__int64)v53;
      *(&this->m_hTexture + 3) = 0;
      *(&this->m_hTexture + 6) = 0;
    }
  }
  v54 = v44 + (double)m_nNotifyRender - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 11);
  if ( (double)this->m_nScrollWidget >= v54 )
  {
    v55 = *(&this->m_hTexture + 4);
    v56 = *(&this->m_hTexture + 5);
    this->m_nScrollWidget = (__int64)v54;
    this->m_nRectH = (__int64)v54 - m_nShowState;
    *(&this->m_hTexture + 3) = v55;
    *(&this->m_hTexture + 6) = v56;
  }
LABEL_52:
  m_nViewW = this->m_nViewW;
  *(POINT *)&this->m_nRectY = pt;
  if ( m_nViewW )
LABEL_53:
    (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)m_nViewW + 24))(
      m_nViewW,
      1019,
      LODWORD(this->m_fScaleY),
      (__int64)*((float *)&this->m_hTexture + 6));
LABEL_54:
  v57 = ((UIListBox *)this)->Update(nVal, nVal2);
  return LOBYTE(this->m_nClipY) || v57;
}

// 0x0043FA00
int UIScene::GetChildCount()
{
  const CHAR *v1; // edi
  float m_fCameraOffset; // ecx
  bool v4; // zf
  int v5; // ebp
  CHAR *v6; // eax
  float v7; // ecx
  int result; // eax
  LPCSTR lpString; // [esp+0x1C] [ebp+0x4] BYREF
  char v10; // [esp+0x20] [ebp+0x8]

  v1 = lpString;
  if ( lpString )
  {
    m_fCameraOffset = this->m_fCameraOffset;
    if ( m_fCameraOffset != 0.0 )
      ((gbRefObject *)LODWORD(m_fCameraOffset))->Release();
    v4 = v10 == 0;
    this->m_bFieldCC = 0;
    if ( v4 )
    {
      LODWORD(this->m_fCameraOffset) = (*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(
                                         gfxMgr,
                                         v1);
    }
    else
    {
      v5 = *(_DWORD *)gfxMgr;
      v6 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v1);
      LODWORD(this->m_fCameraOffset) = (*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6);
      this->m_bFieldCC = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v1);
    }
    v7 = this->m_fCameraOffset;
    if ( v7 != 0.0 )
      ((gbTexture *)LODWORD(v7))->LoadTexture(1);
  }
  return result;
}

// 0x0043FAE0
int UIScene::GetChildAt()
{
  const CHAR *v1; // edi
  gbRefObject *m_nFieldD0; // ecx
  bool v4; // zf
  int v5; // ebp
  CHAR *v6; // eax
  gbTexture *v7; // ecx
  int result; // eax
  LPCSTR lpString; // [esp+0x1C] [ebp+0x4] BYREF
  char v10; // [esp+0x20] [ebp+0x8]

  v1 = lpString;
  if ( lpString )
  {
    m_nFieldD0 = (gbRefObject *)this->m_nFieldD0;
    if ( m_nFieldD0 )
      ((gbRefObject *)m_nFieldD0)->Release();
    v4 = v10 == 0;
    this->m_bVisible = 0;
    if ( v4 )
    {
      this->m_nFieldD0 = (*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, v1);
    }
    else
    {
      v5 = *(_DWORD *)gfxMgr;
      v6 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v1);
      this->m_nFieldD0 = (*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6);
      this->m_bVisible = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v1);
    }
    v7 = (gbTexture *)this->m_nFieldD0;
    if ( v7 )
      ((gbTexture *)v7)->LoadTexture(1);
  }
  return result;
}

// 0x0043FBC0
void UIScene::SetTextParam()
{
  const CHAR *v1; // edi
  gbRefObject *m_hFont; // ecx
  bool v4; // zf
  int v5; // ebp
  CHAR *v6; // eax
  gbTexture *v7; // ecx
  LPCSTR lpString; // [esp+0x1C] [ebp+0x4] BYREF
  char v9; // [esp+0x20] [ebp+0x8]

  v1 = lpString;
  if ( lpString )
  {
    m_hFont = (gbRefObject *)this->m_hFont;
    if ( m_hFont )
      ((gbRefObject *)m_hFont)->Release();
    v4 = v9 == 0;
    this->m_bEnabled = 0;
    if ( v4 )
    {
      this->m_hFont = (*(int ( **)(gbGfxManager *, const CHAR *))(*(_DWORD *)gfxMgr + 8))(gfxMgr, v1);
    }
    else
    {
      v5 = *(_DWORD *)gfxMgr;
      v6 = ((TextureLib_Data *)&stru_1894B78)->_CalculateUV(v1);
      this->m_hFont = (*(int ( **)(gbGfxManager *, CHAR *))(v5 + 8))(gfxMgr, v6);
      this->m_bEnabled = ((TextureLibDataBase *)&stru_1894B78)->CreateParentData(v1);
    }
    v7 = (gbTexture *)this->m_hFont;
    if ( v7 )
      ((gbTexture *)v7)->LoadTexture(1);
  }
}

// 0x00442060
void UIScene::SetFirstShow()
{
  char *m_pChildData; // eax
  float m_fAngle; // eax
  Parent_Data *v4; // eax
  float v5; // [esp+0x8] [ebp+0x4]

  m_pChildData = this->m_pChildData;
  this->m_fCameraOffset = v5;
  if ( SLODWORD(v5) < (int)m_pChildData )
    LODWORD(this->m_fCameraOffset) = m_pChildData;
  m_fAngle = this->m_fAngle;
  if ( SLODWORD(this->m_fCameraOffset) > SLODWORD(m_fAngle) )
    this->m_fCameraOffset = m_fAngle;
  v4 = (Parent_Data *)sub_442000();
  this->m_nFieldD0 = (int)v4;
  this->m_bFieldCC = v4;
}

// 0x004427A0
int UIScene::SetShow(int bShow)
{
  int result; // eax

  result = bShow;
  if ( bShow )
    this->m_nShowState = 2;
  else
    this->m_nShowState = 1;
  return result;
}

// 0x00445930
void UIScene::SetState()
{
  int v1; // [esp+0x4] [ebp+0x4]

  this->m_hFont = v1;
  if ( v1 )
  {
    LODWORD(this->m_fCameraOffset) = 2;
    *(tagRECT *)&this->m_nScrollIdx = this->m_rect;
  }
}

// 0x00445F80
unsigned __int8 UIScene::GetPixelChannel(int nX, int nY, int nW, int nH)
{
// [VFTABLE] return ((gbTexture *)*((gbTexture **)&this->__vftable + nX))->GetPixelChannel(nY, nW, nH);
}

// 0x0044DAC0
void UIScene::Render_dac0()
{
  int v1; // ecx

  switch ( *((_DWORD *)this + 3467) )
  {
    case 0:
      ((CCBControlWindow *)this)->Render((CCBMagicWindow *)this);
      break;
    case 1:
      v1 = *((_DWORD *)this + 3464);
      goto LABEL_6;
    case 3:
      (*(void ( **)(_DWORD, UIScene *))(**((_DWORD **)this + 3465) + 4))(*((_DWORD *)this + 3465), this);
      break;
    case 4:
      v1 = *((_DWORD *)this + 3466);
LABEL_6:
      (*(void ( **)(int, UIScene *))(*(_DWORD *)v1 + 4))(v1, this);
      break;
    default:
      break;
  }
  crt_sub_00540FD0();
}

// 0x0044DFC0
int UIScene::OnMessage(UICursor *msg, int wparam, int lparam)
{
  int result; // eax
  CScreenMode *Instance; // eax
  Actor *SaveDataManager; // eax
  CScreenMode *v8; // eax
  _SPropValue *v9; // edx
  int v10; // edi
  int v11; // ebp
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  _SPropValue *v16; // [esp-0x14] [ebp-0x18]
  _SPropValue *v17; // [esp-0xC] [ebp-0x10]
  _SPropValue *v18; // [esp-0xC] [ebp-0x10]
  const void *v19; // [esp-0xC] [ebp-0x10]
  _SPropValue *v20; // [esp-0xC] [ebp-0x10]
  _SPropValue *v21; // [esp-0xC] [ebp-0x10]

  if ( msg == (UICursor *)1000 )
  {
    if ( wparam )
    {
      *((_BYTE *)this + 13853) = 0;
      *((_BYTE *)this + 11288) = 0;
      *((_DWORD *)this + 2820) = 1077097267;
      *((_DWORD *)this + 2824) = 1077097267;
      *((_DWORD *)this + 2868) = 1077097267;
      *((_DWORD *)this + 2872) = 1077097267;
      *((_BYTE *)this + 11480) = 0;
      *((_DWORD *)this + 2823) = 1056964608;
      *((_DWORD *)this + 2871) = 1056964608;
      ((UICursor *)0x3E8)->IRender();
    }
    return 1;
  }
  else if ( msg == (UICursor *)1001 )
  {
    switch ( wparam )
    {
      case 161:
        if ( *((_BYTE *)this + 13853) || *((_BYTE *)this + 14232) )
          goto LABEL_25;
        PAL3::LoadRoleByIndex();
        *((_BYTE *)this + 13852) = 1;
        v17 = off_59DC84;
        Instance = CScreenMode::GetInstance();
        ((CScreenMode *)Instance)->AudioSetPosition(v17, 1);
        SaveDataManager = (Actor *)GetSaveDataManager();
        ((Actor *)SaveDataManager)->IterateActiveActors();
        return 1;
      case 162:
        if ( *((_BYTE *)this + 13853) || *((_BYTE *)this + 14232) )
          goto LABEL_17;
        ((ChoseCompose *)this)->Init(1);
        v18 = off_59DC84;
        v8 = CScreenMode::GetInstance();
        ((CScreenMode *)v8)->AudioSetPosition(v18, 1);
        return 1;
      case 163:
        if ( *((_BYTE *)this + 13853) || *((_BYTE *)this + 14232) )
          goto LABEL_17;
        ((UICoverFrm *)this)->SetDefaultValues();
        v9 = off_59DC84;
        goto LABEL_26;
      case 164:
        if ( *((_BYTE *)this + 13853) || *((_BYTE *)this + 14232) )
          goto LABEL_17;
        v10 = BYTE1(g_dwUISettings);
        v11 = BYTE2(g_dwUISettings);
        ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_S_GAME")->WriteRegistryDword((DWORD)"S_GAME_A", (unsigned __int8)g_dwUISettings);
        ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_S_GAME")->WriteRegistryDword((DWORD)"S_GAME_B", v10);
        ((PAL3 *)"SOFTWARE\\SOFTSTAR\\PAL3_S_GAME")->WriteRegistryDword((DWORD)"S_GAME_C", v11);
        *((_BYTE *)this + 13853) = 1;
        *((_DWORD *)this + 2821) = 1;
        *((_DWORD *)this + 2818) = 1;
        *((_DWORD *)this + 2819) = 0;
        *((_BYTE *)this + 11288) = 0;
        *((_DWORD *)this + 2869) = 1;
        *((_DWORD *)this + 2866) = 1;
        *((_DWORD *)this + 2867) = 0;
        *((_BYTE *)this + 11480) = 0;
        v16 = off_59DC84;
        v12 = CScreenMode::GetInstance();
        ((CScreenMode *)v12)->AudioSetPosition(v16, 1);
        return 1;
      case 165:
        if ( *((_BYTE *)this + 13853) || *((_BYTE *)this + 14232) )
        {
LABEL_17:
          v19 = off_59DC90;
          v13 = CScreenMode::GetInstance();
          ((CScreenMode *)v13)->AudioSetPosition(v19, 1);
          return 1;
        }
        ((ChoseCompose *)this)->Init(3);
        v9 = off_59DC84;
        goto LABEL_26;
      case 166:
        if ( *((_BYTE *)this + 13853) || *((_BYTE *)this + 14232) )
        {
LABEL_25:
          v9 = (_SPropValue *)off_59DC90;
LABEL_26:
          v21 = v9;
          v15 = CScreenMode::GetInstance();
          ((CScreenMode *)v15)->AudioSetPosition(v21, 1);
LABEL_27:
          result = 1;
        }
        else
        {
          v20 = off_59DC84;
          v14 = CScreenMode::GetInstance();
          ((CScreenMode *)v14)->AudioSetPosition(v20, 1);
          ((ChoseCompose *)this)->Init(4);
          result = 1;
        }
        break;
      default:
        goto LABEL_27;
    }
  }
  else
  {
    return ((PalScript *)this)->OnMessage((int)msg, wparam, lparam);
  }
  return result;
}

// 0x00455190
int UIScene::SetParam(int nVal)
{
  this->m_bFieldCC = (Parent_Data *)nVal;
  return nVal;
}

// 0x00459900
int UIScene::RenderUI()
{
  int result; // eax

  result = *((_DWORD *)this + 818);
  if ( result )
    return crt_sub_00540D20();
  return result;
}

// 0x0045ADF0
void UIScene::DestroyParent()
{
  ((UICaption *)((char *)this + 376))->Destroy2();
  ((UICaption *)&this->m_pfather)->Destroy2();
}

// 0x004932D0
int UIScene::LoadRoleSkillData(int nRoleIndex)
{
  char *v3; // edi
  void **v4; // ecx
  void **v5; // edx
  signed __int16 *v6; // eax
  int result; // eax
  _BYTE pOut[12]; // [esp+0x18] [ebp-0xC] BYREF

  v3 = 0;
  if ( ((NPC *)((char *)this + 217412))->CreateChild() >= 0 )
  {
    v6 = (signed __int16 *)((PtrArray *)&((RoleSystem *)&stru_C059A0)->m_fMoveParamZ)->GetAt(pOut, *((_DWORD *)this + 92));
LABEL_12:
    v3 = (char *)*((_DWORD *)v6 + 2);
  }
  else
  {
    switch ( *((_DWORD *)this + 93) )
    {
      case 0:
        v4 = (void **)&Buffer.m_partyActor.m_dwMatMsg[352 * nRoleIndex + 6];
        goto LABEL_4;
      case 1:
        v5 = &Buffer.m_partyActor.m_pParticleData + 352 * nRoleIndex + 1;
        goto LABEL_6;
      case 2:
        v6 = &Buffer.m_partyActor.m_nAnimFrame + 704 * nRoleIndex + 2;
        goto LABEL_12;
      case 3:
        v4 = &Buffer.m_partyActor.m_pParticleData + 352 * nRoleIndex + 4;
LABEL_4:
        v3 = (char *)v4[2];
        break;
      case 4:
        v5 = (void **)&Buffer.m_partyActor.m_dwMatMsg[352 * nRoleIndex];
LABEL_6:
        v3 = (char *)v5[2];
        break;
      case 5:
        v6 = (signed __int16 *)&Buffer.m_partyActor.m_dwMatMsg[352 * nRoleIndex + 3];
        goto LABEL_12;
      default:
        break;
    }
  }
  ((RoleSystem *)((char *)&Buffer + 1408 * nRoleIndex))->RecalcAggregatedStats(0);
  ((StateUI *)this)->UpdateAttributeDisplay(nRoleIndex, v3, *((float *)this + 93));
  return result;
}

// 0x00524230
char UIScene::InitScriptScene(int nVal)
{
  int m_nScrollIdx; // eax
  int m_nShowState; // ecx
  int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // ebp
  int v16; // eax
  double v17; // st7
  int v18; // ecx
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  int v22; // ebx
  int v23; // ebp
  int v24; // eax
  double v25; // st7
  __int64 v26; // rax
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  __int64 v30; // rax
  int v31; // ecx
  int v32; // eax
  int v33; // ecx
  int v34; // edx
  int v35; // edx
  int v36; // ecx
  float fVal; // [esp+0x5C] [ebp-0x88]
  int v39; // [esp+0x74] [ebp-0x70] BYREF
  int v40; // [esp+0x78] [ebp-0x6C]
  int v41; // [esp+0x7C] [ebp-0x68]
  int v42; // [esp+0x80] [ebp-0x64]
  _DWORD v43[2]; // [esp+0x84] [ebp-0x60] BYREF
  int v44; // [esp+0x8C] [ebp-0x58]
  int v45; // [esp+0x90] [ebp-0x54]
  _DWORD v46[2]; // [esp+0x94] [ebp-0x50] BYREF
  int v47; // [esp+0x9C] [ebp-0x48]
  int v48; // [esp+A0h] [ebp-0x44]
  _DWORD v49[2]; // [esp+A4h] [ebp-0x40] BYREF
  int v50; // [esp+ACh] [ebp-0x38]
  int v51; // [esp+B0h] [ebp-0x34]
  _DWORD v52[4]; // [esp+B4h] [ebp-0x30] BYREF
  _DWORD v53[4]; // [esp+C4h] [ebp-0x20] BYREF
  int v54[4]; // [esp+D4h] [ebp-0x10] BYREF

  m_nScrollIdx = this->m_nScrollIdx;
  m_nShowState = this->m_nShowState;
  *(_DWORD *)&this->_todo_050 = m_nScrollIdx;
  this->m_nScrollState = m_nShowState;
  this->m_fScaleX = 0.0;
  this->m_fScaleY = 0.0;
  ((UIListBox *)this)->SetSelTexture(-1, 0, 0, *(_DWORD *)&this->_todo_050, this->m_nScrollState, 0);
  v5 = *((_DWORD *)this + 90);
  *((_DWORD *)this + 1312) = nVal;
  v40 = 84;
  v39 = 112;
  v41 = 655;
  v42 = 318;
  (*(void ( **)(char *, char *, int *, UIScene *))(v5 + 16))((char *)this + 360, &byte_A00B00, &v39, this);
  ((UIStatic *)((char *)this + 360))->CreateFromTemplate();
  v52[1] = v40;
  v52[0] = v39 + 288;
  v52[2] = v39 + 416;
  v52[3] = v40 + 32;
  (*(void ( **)(char *, char *, _DWORD *, UIScene *))(*((_DWORD *)this + 280) + 16))(
    (char *)this + 1120,
    &byte_A00B05,
    v52,
    this);
  ((UIScene *)((char *)this + 1120))->SetShow(0);
  sub_446010((char *)this + 1120);
  v46[0] = v39 + 172;
  v46[1] = v40 + 42;
  v47 = v39 + 300;
  v48 = v40 + 74;
  (*(void ( **)(char *, char *, _DWORD *, UIScene *))(*((_DWORD *)this + 204) + 16))(
    (char *)this + 816,
    &byte_A00B03,
    v46,
    this);
  ((UIScene *)((char *)this + 816))->SetShow(0);
  sub_446010((char *)this + 816);
  v6 = *((_DWORD *)this + 242);
  v46[0] = 558;
  v47 = 686;
  (*(void ( **)(char *, char *, _DWORD *, UIScene *))(v6 + 16))((char *)this + 968, &byte_A00B04, v46, this);
  ((UIScene *)((char *)this + 968))->SetShow(0);
  sub_446010((char *)this + 968);
  v7 = *((_DWORD *)this + 128);
  v49[1] = v40 + 82;
  v49[0] = v39 + 172;
  v51 = v40 + 114;
  v50 = v39 + 300;
  (*(void ( **)(char *, char *, _DWORD *, UIScene *))(v7 + 16))((char *)this + 512, &byte_A00B02, v49, this);
  ((UIScene *)((char *)this + 512))->SetShow(0);
  sub_446010((char *)this + 512);
  sprintf((char *const)&this->m_nClipY, &dir[20], ((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom);
  ((UICaption *)((char *)this + 512))->SetEnable((int)&this->m_nClipY, 0);
  v8 = *((_DWORD *)this + 166);
  v49[0] = 558;
  v50 = 686;
  (*(void ( **)(char *, char *, _DWORD *, UIScene *))(v8 + 16))((char *)this + 664, &byte_A00B06, v49, this);
  ((UIScene *)((char *)this + 664))->SetShow(0);
  sub_446010((char *)this + 664);
  sprintf((char *const)&this->m_nClipY, &dir[20], (unsigned int)(__int64)*((float *)this + 376));
  ((UICaption *)((char *)this + 664))->SetEnable((int)&this->m_nClipY, 0);
  v53[1] = v40 + 132;
  v53[0] = v39 + 74;
  v53[3] = v40 + 170;
  v9 = *((_DWORD *)this + 1312);
  v10 = v39 + 477;
  v11 = *((_DWORD *)this + 318);
  v53[2] = v39 + 477;
  LOBYTE(v10) = *(_BYTE *)(v9 + 1768);
  (*(void ( **)(char *, char *, _DWORD *, UIScene *, char *, int))(v11 + 28))(
    (char *)this + 1272,
    &byte_A00B01,
    v53,
    this,
    "UI\\GameMainUI\\Communal\\scroll\\scrollbar",
    v10);
  ((UIScene *)((char *)this + 1272))->SetTexture("SubGame\\HockShop\\Invest\\DragBar_bk.tga", *(_BYTE *)(*((_DWORD *)this + 1312) + 1768));
  ((UIScene *)((char *)this + 1272))->SetParam(0);
  *((_DWORD *)this + 380) = 1112014848;
  *((_DWORD *)this + 381) = -1027866624;
  ((UIBigMap *)((char *)this + 1272))->Update(26, 28);
  v12 = *((_DWORD *)this + 384);
  *((_DWORD *)this + 379) = 32;
  if ( v12 )
  {
    if ( v12 == 1 )
    {
      v13 = *((_DWORD *)this + 385);
      if ( !v13 )
      {
        v14 = *((_DWORD *)this + 342);
        v18 = *((_DWORD *)this + 352);
        v15 = (__int64)((double)(*((_DWORD *)this + 353) - v14 / 2) + *((float *)this + 382) + *((float *)this + 377));
        v19 = *((_DWORD *)this + 341);
        *((_DWORD *)this + 349) = v15;
        v17 = (double)(v18 - v19 - 32) + *((float *)this + 380);
        goto LABEL_7;
      }
      if ( v13 == 1 )
      {
        v14 = *((_DWORD *)this + 342);
        v15 = (__int64)((double)*((int *)this + 355)
                      - *((float *)this + 377)
                      - (double)(v14 / 2)
                      - *((float *)this + 383));
        v16 = *((_DWORD *)this + 354);
        *((_DWORD *)this + 349) = v15;
        v17 = (double)(v16 + 32) - *((float *)this + 377) - *((float *)this + 381);
LABEL_7:
        v20 = *((_DWORD *)this + 341);
        *((_DWORD *)this + 348) = (__int64)v17;
        *((_DWORD *)this + 350) = (__int64)v17 + v20;
LABEL_12:
        *((_DWORD *)this + 351) = v14 + v15;
      }
    }
  }
  else
  {
    v21 = *((_DWORD *)this + 385);
    if ( !v21 )
    {
      v15 = *((_DWORD *)this + 342);
      v14 = (__int64)((double)(*((_DWORD *)this + 353) - v15 - 32) + *((float *)this + 382));
      v28 = *((_DWORD *)this + 341);
      v29 = *((_DWORD *)this + 352);
      *((_DWORD *)this + 349) = v14;
      v30 = (__int64)((double)(v29 - v28 / 2) + *((float *)this + 380) + *((float *)this + 377));
      v31 = *((_DWORD *)this + 341);
      *((_DWORD *)this + 348) = v30;
      *((_DWORD *)this + 350) = v31 + v30;
      goto LABEL_12;
    }
    if ( v21 == 1 )
    {
      v22 = *((_DWORD *)this + 342);
      v23 = (__int64)((double)(*((_DWORD *)this + 353) - v22 - 32) + *((float *)this + 382));
      v24 = *((_DWORD *)this + 341);
      v25 = (double)*((int *)this + 354) - *((float *)this + 377);
      *((_DWORD *)this + 349) = v23;
      v26 = (__int64)(v25 - (double)(v24 / 2) - *((float *)this + 381));
      v27 = *((_DWORD *)this + 341);
      *((_DWORD *)this + 348) = v26;
      *((_DWORD *)this + 350) = v27 + v26;
      *((_DWORD *)this + 351) = v23 + v22;
    }
  }
  fVal = (float)((RoleSystem *)&stru_C059A0)->_embed_UIWnd_624.m_rect.bottom;
  ((UIScene *)((char *)this + 1272))->UpdateLayout(fVal);
  v43[0] = v39 + 126;
  v43[1] = v40 + 203;
  v45 = v40 + 229;
  v32 = *((_DWORD *)this + 1312);
  v33 = v39 + 216;
  v34 = *((_DWORD *)this + 386);
  v44 = v39 + 216;
  LOBYTE(v33) = *(_BYTE *)(v32 + 1768);
  (*(void ( **)(char *, char *, _DWORD *, UIScene *, char *, _DWORD, int))(v34 + 28))(
    (char *)this + 1544,
    &byte_A00B07,
    v43,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\Yes",
    0,
    v33);
  ((PalScript *)((char *)this + 1544))->OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnYes.tga", *(_BYTE *)(*((_DWORD *)this + 1312) + 1768));
  sub_445E50((int)this + 1544);
  v35 = v44;
  v36 = *((_DWORD *)this + 1312);
  v43[0] = v44 + 100;
  v44 += 190;
  LOBYTE(v35) = *(_BYTE *)(v36 + 1768);
  (*(void ( **)(char *, int *, _DWORD *, UIScene *, char *, _DWORD, int))(*((_DWORD *)this + 472) + 28))(
    (char *)this + 1888,
    dword_A00B08,
    v43,
    this,
    "UI\\GameMainUI\\MUIDialog\\Normal\\No",
    0,
    v35);
  ((PalScript *)((char *)this + 1888))->OpenScript("UI\\GameMainUI\\MUIDialog\\Normal\\UnNo.tga", *(_BYTE *)(*((_DWORD *)this + 1312) + 1768));
  v54[1] = 200;
  v54[0] = 300;
  v54[3] = 300;
  v54[2] = 600;
  ((ARC_PlayerAtt *)((char *)this + 3876))->Create((int)&g_PlayerAttBuffer2, (int)v54);
  ((UIItem *)((char *)this + 3876))->SetData(18);
  return ((PalScript *)((char *)this + 2236))->LoadSceneConfig("SubGame\\HockShop\\Data\\HockShopLevel.hsl");
}

// 0x0052E120
void UIScene::LoadMapData()
{
  int v1; // [esp+0x4] [ebp+0x4]

  this->m_bfocus = v1;
  this->CalcViewTransform(1);
}

// 0x0052E140
int UIScene::CalcViewTransform(int nVal)
{
  long double v2; // st7
  double v3; // st6
  long double v4; // st7
  long double v5; // st6
  long double v6; // st5
  double v7; // st4
  double v8; // st3
  double v9; // st2
  double v10; // st3
  double v11; // st4
  double v12; // st3
  double v13; // st7
  double v14; // st6
  double v15; // st5
  float v17; // [esp+0x0] [ebp-0x20]
  float v18; // [esp+0x4] [ebp-0x1C]
  float v19; // [esp+0x8] [ebp-0x18]
  float v20; // [esp+0xC] [ebp-0x14]
  float v21; // [esp+0x10] [ebp-0x10]
  float v22; // [esp+0x14] [ebp-0xC]
  float v23; // [esp+0x18] [ebp-0x8]
  unsigned int v24; // [esp+0x18] [ebp-0x8]
  LONG v25; // [esp+0x18] [ebp-0x8]
  int v26; // [esp+0x18] [ebp-0x8]
  float v27; // [esp+0x1C] [ebp-0x4]
  LONG v28; // [esp+0x1C] [ebp-0x4]
  int v29; // [esp+0x1C] [ebp-0x4]

  if ( *((_BYTE *)&this->m_hTexture + 8) )
  {
    v2 = (*(float *)&this->m_bVisible + *(float *)&this->m_bcreateok) * 0.017453292;
    v17 = (*(float *)&this->m_hFont + *(float *)&this->m_bvisible) * 0.017453292;
    v3 = *(float *)&this->m_bEnabled + *(float *)&this->m_benable;
  }
  else
  {
    v2 = *(float *)&this->m_bcreateok * 0.017453292;
    v17 = *(float *)&this->m_bvisible * 0.017453292;
    v3 = *(float *)&this->m_benable;
  }
  v18 = v3 * 0.017453292;
  v21 = cos(v2);
  v19 = cos(v17);
  v20 = cos(v18);
  v4 = sin(v2);
  v5 = sin(v17);
  v6 = sin(v18);
  *(float *)&this->_todo_050 = v4 * v19;
  *(float *)&this->m_nScrollState = v5;
  *(float *)&this->m_nScrollIdx = -(v19 * v21);
  v7 = *(float *)&this->m_bfocus;
  v22 = v7 * *(float *)&this->_todo_050;
  v23 = v7 * *(float *)&this->m_nScrollState;
  if ( nVal )
  {
    v8 = *(float *)&this->m_rect.left - v22;
    *(float *)&v24 = *(float *)&this->m_rect.top - v23;
    v9 = *(float *)&this->m_rect.right - v7 * *(float *)&this->m_nScrollIdx;
    this->m_wndcolor.Color = v24;
    v27 = v9;
    *(float *)&this->m_fontcolor.Color = v8;
    *(float *)&this->m_id = v27;
  }
  else
  {
    *(float *)&v25 = v23 + *(float *)&this->m_wndcolor.Color;
    v10 = v7 * *(float *)&this->m_nScrollIdx;
    v11 = v22 + *(float *)&this->m_fontcolor.Color;
    v12 = v10 + *(float *)&this->m_id;
    this->m_rect.top = v25;
    *(float *)&v28 = v12;
    *(float *)&this->m_rect.left = v11;
    this->m_rect.right = v28;
  }
  *(float *)&this->m_rect.bottom = -(v6 * v21) - v5 * v4 * v20;
  *(float *)&this->m_pfather = v20 * v19;
  *(float *)&this->m_childs.m_pData = -(v6 * v4) - -(v5 * v20 * v21);
  v13 = *(float *)&this->m_nScrollState * *(float *)&this->m_childs.m_pData
      - *(float *)&this->m_nScrollIdx * *(float *)&this->m_pfather;
  *(float *)&v26 = *(float *)&this->m_nScrollIdx * *(float *)&this->m_rect.bottom
                 - *(float *)&this->m_childs.m_pData * *(float *)&this->_todo_050;
  v14 = *(float *)&this->m_pfather * *(float *)&this->_todo_050;
  v15 = *(float *)&this->m_nScrollState * *(float *)&this->m_rect.bottom;
  this->m_pChildWnd = (UIWnd *)v26;
  *(float *)&v29 = v14 - v15;
  *(float *)&this->m_nShowState = v13;
  this->m_nClipX = v29;
  return v26;
}

// 0x00532D60
void UIScene::UpdateAlpha()
{
  char m_nClipY; // dl
  double v2; // st7
  double v4; // st7
  unsigned __int8 v5; // c0
  unsigned __int8 v6; // c3
  double v7; // st7
  double v8; // st7

  m_nClipY = this->m_nClipY;
  if ( BYTE1(this->m_nClipY) != m_nClipY )
  {
    switch ( m_nClipY )
    {
      case 0:
// [VFTABLE] v2 = *(float *)&this->__vftable[7].Create;
        goto LABEL_7;
      case 1:
// [VFTABLE] v2 = *(float *)&this->__vftable[7].Destroy;
        goto LABEL_7;
      case 2:
// [VFTABLE] v2 = *(float *)&this->__vftable[7].Update_2ff0;
        goto LABEL_7;
      case 3:
// [VFTABLE] v2 = *(float *)&this->__vftable[7].Render;
LABEL_7:
        *(float *)&this->m_pChildWnd = v2;
        break;
      default:
        break;
    }
    BYTE1(this->m_nClipY) = m_nClipY;
  }
  v4 = *(float *)&this->m_nShowState;
  if ( v5 | v6 )
  {
    if ( v4 < *(float *)&this->m_pChildWnd )
    {
      v8 = *(float *)&this->m_nClipX + *(float *)&this->m_nShowState;
      *(float *)&this->m_nShowState = v8;
      if ( v8 >= *(float *)&this->m_pChildWnd )
        this->m_nShowState = (int)this->m_pChildWnd;
    }
  }
  else
  {
    v7 = v4 - *(float *)&this->m_nClipX;
    *(float *)&this->m_nShowState = v7;
    if ( v7 <= *(float *)&this->m_pChildWnd )
      this->m_nShowState = (int)this->m_pChildWnd;
  }
}

// 0x00535AE0
int UIScene::ClearColors()
{
// [VFTABLE] this->__vftable = 0;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 0;
  *(&this->m_hTexture + 4) = 0;
  this->m_fAngle = -96.279999;
  this->m_fCameraOffset = 0.0;
  this->m_bFieldCC = (Parent_Data *)-982398730;
  this->m_nFieldD0 = LODWORD(this->m_fAngle);
  this->m_bVisible = (Parent_Data *)LODWORD(this->m_fCameraOffset);
  this->m_hFont = (int)this->m_bFieldCC;
  this->m_nColors = 1065353216;
  this->m_bLoadState = 0;
  this->m_pChildData = 0;
  this->m_bEnabled = 0;
  *((_BYTE *)&this->m_hTexture + 8) = 0;
  *((_BYTE *)&this->m_hTexture + 9) = 0;
  *(_DWORD *)&this->m_bOverlayRender = 1070386381;
  *(_DWORD *)&this->m_bCursorLeft = 1067534254;
  this->m_hTexture = 1059984507;
  *(&this->m_hTexture + 1) = 1049582633;
  *((_BYTE *)&this->m_hTexture + 10) = 0;
  *((_BYTE *)&this->m_hTexture + 11) = 0;
  *((_BYTE *)&this->m_hTexture + 12) = 0;
  *((_BYTE *)&this->m_hTexture + 13) = 0;
  return 0;
}

// 0x00535BA0
int UIScene::ResetCameraOffset()
{
  this->m_fAngle = 80.0;
  this->m_fCameraOffset = 0.0;
  this->m_bFieldCC = (Parent_Data *)1141112832;
  this->m_nFieldD0 = LODWORD(this->m_fAngle);
  this->m_bVisible = (Parent_Data *)LODWORD(this->m_fCameraOffset);
  this->m_hFont = (int)this->m_bFieldCC;
  this->m_nColors = 1065353216;
  this->m_bLoadState = 0;
  this->m_pChildData = 0;
  this->m_bEnabled = 0;
  *((_BYTE *)&this->m_hTexture + 8) = 0;
  *((_BYTE *)&this->m_hTexture + 9) = 0;
  *((_BYTE *)&this->m_hTexture + 10) = 0;
  *((_BYTE *)&this->m_hTexture + 11) = 0;
  *((_BYTE *)&this->m_hTexture + 12) = 0;
  *((_BYTE *)&this->m_hTexture + 13) = 0;
  return 0;
}
