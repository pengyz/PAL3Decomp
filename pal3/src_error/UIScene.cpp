#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIScene.h"
#include "Role/Actor.h"
#include "Combat/CCBControlWindow.h"
#include "Combat/CCBMagicWindow.h"
#include "Combat/CCBResultWindow.h"
#include "Combat/CCCTData.h"
#include "Data/CGameData.h"
#include "Render/CScreenMode.h"
#include "Combat/CUtil.h"
#include "Misc/ChoseCompose.h"
#include "GameBase/GRPinput.h"
#include "Misc/JusticeBookUI.h"
#include "Role/NPC.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "GameBase/PAL3.h"
#include "Script/PalScript.h"
#include "Script/PalScriptMgr.h"
#include "Misc/Parent_Data.h"
#include "Misc/PtrArray.h"
#include "Role/Role.h"
#include "Role/RoleSystem.h"
#include "Scene/Scene.h"
#include "Scene/SceneObj.h"
#include "Misc/TaskBookUI.h"
#include "Misc/TextureLibDataBase.h"
#include "Misc/UIBigMap.h"
#include "Misc/UICaption.h"
#include "Misc/UICoverFrm.h"
#include "UI/UICursor.h"
#include "Misc/UIScenePanel.h"
#include "Misc/UITitle_BBTY.h"
#include "UI/UIWnd.h"
#include "Misc/_PlugInfo.h"
#include "Misc/_Texture_Info.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4019F0(...);
int sub_407790(...);

class TextureLibDataBase;

// Unnamed globals (extern)
extern TextureLibDataBase stru_1894B78;

// 0x00419C20
int UIScene::RenderVertexPool()
{
    unsigned long reg_EBP = 0;
    unsigned long reg_EBX = 0;
    UIScene *reg_EDI = this;
    unsigned long reg_ESI = 0;

  int result; // eax
  const gbVec3D *v4; // eax
  const gbVec3D *v5; // eax
  const gbVec3D *v6; // eax
  RoleSystem *v11; // eax
  const gbVec3D *v14; // eax
  const gbVec3D *v15; // eax
  const gbVec3D *v16; // eax
  RoleSystem *v20; // eax
  int v22; // eax
  int v24; // [esp+0x24] [ebp-0x50]
  int v25; // [esp+0x24] [ebp-0x50]
  float v26; // [esp+0x34] [ebp-0x40]
  float v27; // [esp+0x34] [ebp-0x40]
  float v28; // [esp+0x34] [ebp-0x40]
  float v29; // [esp+0x34] [ebp-0x40]
  float v30; // [esp+0x34] [ebp-0x40]
  float v31; // [esp+0x34] [ebp-0x40]
  gbDynVertBuf *DynVertBuf; // [esp+0x40] [ebp-0x34]
  gbVec3D v33; // [esp+0x44] [ebp-0x30] BYREF
  gbVec3D v34; // [esp+0x50] [ebp-0x24] BYREF
  gbVec3D v35; // [esp+0x5C] [ebp-0x18] BYREF
  int v36; // [esp+0x68] [ebp-0xC]
  int v37; // [esp+0x6C] [ebp-0x8]
  float pOut; // [esp+0x70] [ebp-0x4] BYREF

  reg_EDI = this;
  v33.x = -0.5f;
  v33.y = 0.0f;
  v33.z = 0.8700000047683716f;
  v34.x = 0.5f;
  v34.y = 0.0f;
  v34.z = 0.8700000047683716f;
  (((gbVec3D *)&v33))->gbVec3D::Normalize();
  __asm
  {
    fld     _flt_500_0
    fmul    [esp+0x40+var_30]
  }
  __asm
  {
    fstp    [esp+0x40+var_30]
    fld     dword ptr [flt_56A99C]
    fmul    [esp+0x40+var_30+4]
    fstp    [esp+0x40+var_30+4]
    fld     [esp+0x40+var_30+8]
    fmul    _flt_500_0
    fstp    [esp+0x40+var_30+8]
  }
  gbVec3D::Normalize(&v34);
  __asm
  {
    fld     _flt_500_0
    fmul    [esp+0x40+var_24]
  }
  __asm
  {
    fstp    [esp+0x44+var_24]
    fld     [esp+0x44+var_24+4]
    fmul    _flt_500_0
    fstp    [esp+0x44+var_24+4]
    fld     [esp+0x44+var_24+8]
    fmul    _flt_500_0
    fstp    [esp+0x44+var_24+8]
  }
  DynVertBuf = (((gbVertPoolMgr *)gfxMgr->pVertPoolMgr))->gbVertPoolMgr::GetDynVertBuf(5u);
  result = ((int (*)(gbDynVertBuf *, int))DynVertBuf->pGfxMgr->DrvInfo.type)(DynVertBuf, 3);
  reg_ESI = result;
  if ( result )
  {
    v4 = (const gbVec3D *)Vec3Lerp(&pOut, (float *)&this->m_pfather, v33.z, v26);
    (((gbVec3D *)reg_ESI))->gbVec3D::operator=(*(v4));
    v5 = (const gbVec3D *)Vec3Lerp(&pOut, (float *)&this->m_childs.m_nSize, v34.x, v27);
    (((gbVec3D *)&v35.z))->gbVec3D::operator=(*(v5));
    (((gbVec3D *)reg_ESI))->gbVec3D::operator+=(*((gbVec3D *)&v35.z));
    v6 = (const gbVec3D *)Vec3Lerp(&pOut, (float *)&this->m_rect.top, v34.y, v28);
    (((gbVec3D *)&v35.z))->gbVec3D::operator=(*(v6));
    (((gbVec3D *)reg_ESI))->gbVec3D::operator+=(*((gbVec3D *)&v35.z));
    __asm
    {
      fld     dword ptr [esi]
      fadd    dword ptr [edi+4]
    }
    reg_EBX = reg_ESI + 4;
    __asm { fstp    dword ptr [esi] }
    *(float *)reg_ESI = _ET1;
    __asm
    {
      fld     dword ptr [edi+8]
      fadd    dword ptr [ebx]
      fstp    dword ptr [ebx]
    }
    *(float *)reg_EBX = _ET1;
    __asm
    {
      fld     dword ptr [edi+0x0C]
      fadd    dword ptr [esi+8]
      fstp    dword ptr [esi+8]
    }
    *(float *)(reg_ESI + 8) = _ET1;
    v24 = *(&reg_EDI[1].m_hTexture + 19);
    v11 = (RoleSystem *)UISceneUpdate();
    (((RoleSystem *)v11))->RoleSystem::SetRoleParam(v24, (float *)reg_ESI, 0, 0);
    __asm { fstp    dword ptr [ebx] }
    *(float *)reg_EBX = _ET1;
    reg_EBP = (unsigned long)(float *)(reg_ESI + 32);
    *(_DWORD *)(reg_ESI + 16) = this->m_bLoadState;
    *(_DWORD *)(reg_ESI + 20) = (unsigned long)this->m_pChildData;
    *(float *)(reg_ESI + 24) = this->m_fAngle;
    v35.z = 0.0f;
    v36 = 0;
    v37 = 0;
    v14 = (const gbVec3D *)Vec3Lerp(&pOut, (float *)&this->m_pfather, v34.z, v29);
    (((gbVec3D *)(reg_ESI + 32)))->gbVec3D::operator=(*(v14));
    v15 = (const gbVec3D *)Vec3Lerp(&pOut, (float *)&this->m_childs.m_nSize, v35.x, v30);
    (((gbVec3D *)&v35.z))->gbVec3D::operator=(*(v15));
    (((gbVec3D *)(reg_ESI + 32)))->gbVec3D::operator+=(*((gbVec3D *)&v35.z));
    v16 = (const gbVec3D *)Vec3Lerp(&pOut, (float *)&this->m_rect.top, v35.y, v31);
    (((gbVec3D *)&v35.z))->gbVec3D::operator=(*(v16));
    (((gbVec3D *)(reg_ESI + 32)))->gbVec3D::operator+=(*((gbVec3D *)&v35.z));
    __asm
    {
      fld     dword ptr [edi+4]
      fadd    dword ptr [ebp+0]
    }
    __asm { fstp    dword ptr [ebp+0] }
    // [I1] _ET1 占位宏右值（_ETn 只读约定·无可表达语义）——原 `*reg_EBP = _ET1;` 已由上方 asm 存储覆盖

    __asm
    {
      fld     dword ptr [edi+8]
      fadd    dword ptr [ebp+4]
      fstp    dword ptr [ebp+4]
    }
    *(float *)(reg_ESI + 36) = _ET1;
    __asm
    {
      fld     dword ptr [edi+0x0C]
      fadd    dword ptr [ebp+8]
      fstp    dword ptr [ebp+8]
    }
    *(float *)(reg_ESI + 40) = _ET1;
    v25 = *(&reg_EDI[1].m_hTexture + 19);
    v20 = (RoleSystem *)UISceneUpdate();
    (((RoleSystem *)v20))->RoleSystem::SetRoleParam(v25, (float *)(reg_ESI + 32), 0, 0);
    // __asm { fstp    dword ptr [esi+0x24] }
    *(float *)(reg_ESI + 36) = _ET1;
    v22 = 3;
    do
    {
      v33.x = _pal3_coerce_f32(-2147104763);
      *(_DWORD *)(reg_EBX + 8) = -2147104763;
      __asm
      {
        fld     dword ptr [ebx]
        fadd    dword ptr [flt_56AA5C]
      }
      reg_EBX += 16;
      --v22;
      __asm { fstp    dword ptr [ebx-0x10] }
      *(float *)(reg_EBX - 16) = _ET1;
    }
    while ( v22 );
    return (*(int (**)(_DWORD, int))(*(_DWORD *)LODWORD(v33.y) + 20))(LODWORD(v33.y), 1);
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
      sub_4019F0(*(gbTextureArray **)&this->m_pChildData[4 * v2]);
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
        (((UIBigMap *)v5))->UIBigMap::RenderRole((gbMatrixStack *)nVal, 0);
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
  Scene *v2; // eax

  if ( !UISceneUpdate()->m_lights )
    return 0;
  v2 = UISceneUpdate();
  (*(void ( **)(gbVisNode *, _DWORD))(*(_DWORD *)((gbChain1DNode *)v2->m_lights) + 16))(v2->m_lights, 0);
  return 1;
}

// 0x004235B0
BOOL UIScene::ProcessInput(char *String1, char *pszBuf)
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

// 0x0043A4C0
void UIScene::LoadResource(void *path)
{
  int v2; // edi
  OpenBaseFile v4; // [esp+0xC] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x10] [ebp-0x110] BYREF
  int v6; // [esp+0x11C] [ebp-0x4]

  v2 = 0;
  if ( path )
  {
    (((UIWnd *)&this->m_fScaleX))->UIWnd::MoveWindow();
    this->m_dwColor = 0;
    v6 = 0;
    sprintf(Buffer, "%s%d.tga", (const char *)path, 0);
    while ( (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) > 0 )
    {
      if ( !LoadUISceneTexture((int)Buffer, 1) )
        (((UIWnd *)&this->m_fScaleX))->UIWnd::MoveWindow();
      ++v2;
      ++this->m_dwColor;
      sprintf(Buffer, "%s%d.tga", (const char *)path, v2);
    }
    this->m_bLoadState = 0;
    this->UIScene::ResetState();
    v6 = -1;
    ((OpenNULLFile *)&v4)->OpenNULLFile::OpenNULLFile();
  }
}

// 0x0043A660
int UIScene::ResetState()
{
  int result; // eax

  result = 0;
  this->m_nNotifyRender = 0;
  this->m_fScaleY = 0.0f;
  this->m_hScrollBar = 0;
  return result;
}

// 0x0043A680
int UIScene::SetColors(int nVal)
{
  int result; // eax

  result = nVal;
  this->m_nColors = nVal;
  return result;
}

// 0x0043AFE0
unsigned __int8 UIScene::SetupRenderClip(
        
        int nVal,
        unsigned int dwVal,
        unsigned int dwVal2,
        int nVal2)
{
  Parent_Data *v5; // edx
  gbTexture_D3D *TableEntry16; // eax
  int v8; // [esp-0xC] [ebp-0x14]
  int v9; // [esp-0x8] [ebp-0x10]

  if ( (dwVal & 0x80000000) != 0 )
    return 0;
  v5 = (&this->m_bVisible)[nVal];
  if ( dwVal >= *(_DWORD *)&v5[260] || (dwVal2 & 0x80000000) != 0 || dwVal2 >= *(_DWORD *)&v5[261] )
    return 0;
  v9 = nVal2 + 4 * (*(_DWORD *)&v5[258] + dwVal);
  v8 = *(_DWORD *)&v5[259] - *(_DWORD *)&v5[257] - dwVal2 + 1024;
  TableEntry16 = (gbTexture_D3D *)GetTableEntry16(0);
  return (((gbTexture_D3D *)TableEntry16))->gbTexture_D3D::GetByte(v8, v9);
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
  OpenBaseFile v11; // [esp+0x10] [ebp-0x114] BYREF
  char Buffer[260]; // [esp+0x14] [ebp-0x110] BYREF
  int v13; // [esp+0x120] [ebp-0x4]

  result = (gbVFileSystem *)parent;
  v7 = 0;
  if ( parent && pszName )
  {
    v13 = 0;
    p_m_bVisible = (Parent_Data **)&this->m_bVisible;
    do
    {
      sprintf(Buffer, "%s%d.tga", pszName, v7);
      *p_m_bVisible = 0;
      if ( pData )
      {
        *p_m_bVisible = (((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(Buffer);
        v10 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(Buffer);
        lstrcpyA((char *)Buffer, v10);
        if ( !LoadUISceneTexture((int)Buffer, 2) )
          goto LABEL_14;
      }
      else if ( !LoadUISceneTexture((int)Buffer, 2) )
      {
LABEL_14:
        (((UIWnd *)&this->m_nClipW))->UIWnd::MoveWindow();
        goto LABEL_12;
      }
      ++v7;
      ++p_m_bVisible;
    }
    while ( v7 < 3 );
    sprintf(Buffer, "%s%d.tga", pszName, 3);
    if ( (((gbVFileSystem *)g_pVFileSys))->gbVFileSystem::FileExistNum(Buffer) )
      (((PalScript *)this))->PalScript::OpenScript(Buffer, 0);
    this->UIWnd::Create(id, (tagRECT *)pRect, (int)parent);
LABEL_12:
    v13 = -1;
    ((OpenNULLFile *)&v11)->OpenNULLFile::OpenNULLFile();
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
  POINT pt; // [esp+0x10] [ebp-0x8] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
  {
    this->m_pChildWnd = ((UIWnd *)0);
    return 0;
  }
  if ( !nVal2 )
  {
    this->m_pChildWnd = ((UIWnd *)0);
    return (((SceneObj *)this))->SceneObj::Update(nVal, 0) /* [ROWTABLE] */;
  }
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
  p_m_rect = (tagRECT *)&this->m_rect;
  v6 = PtInRect(&this->m_rect, pt);
  v16 = v6;
  if ( this->m_pChildWnd != (UIWnd *)2 )
  {
    if ( !v6 )
    {
      this->m_pChildWnd = ((UIWnd *)0);
      goto LABEL_14;
    }
    this->m_pChildWnd = ((UIWnd *)((UIWnd *)1));
  }
  if ( !v6 )
  {
LABEL_14:
    if ( !this->m_bCursorLeft )
    {
      m_pfather = this->m_pfather;
      this->m_bCursorLeft = 1;
      if ( m_pfather )
        m_pfather->OnMessage(1003, this->m_id, 0);
    }
    goto LABEL_17;
  }
  left = p_m_rect->left;
  top = this->m_rect.top;
  v9 = pt.x - p_m_rect->left;
  v10 = pt.y - top;
  if ( this->m_bVisible )
  {
    PixelChannel = this->UIScene::SetupRenderClip(0, pt.x - left, pt.y - top, 3);
  }
  else
  {
    if ( v9 >= *(_DWORD *)(GetTableEntry16(0) + 24) )
      v9 = *(_DWORD *)(GetTableEntry16(0) + 24) - 1;
    if ( v10 >= *(_DWORD *)(GetTableEntry16(0) + 28) )
      v10 = *(_DWORD *)(GetTableEntry16(0) + 28) - 1;
    PixelChannel = (((UIScene *)&this->m_nClipW))->UIScene::GetPixelChannel(0, v9, v10, 3);
  }
  if ( PixelChannel < 6u )
  {
    v16 = 0;
    this->m_pChildWnd = ((UIWnd *)0);
  }
  else if ( g_Input.KeyInfo[0].PressTime == 1 )
  {
    this->m_pChildWnd = ((UIWnd *)((UIWnd *)2));
    this->m_bCursorLeft = 0;
  }
  else
  {
    v14 = this->m_pfather;
    if ( v14 )
      v14->OnMessage(1002, this->m_id, 0);
    this->m_bCursorLeft = 0;
  }
LABEL_17:
  if ( this->m_pChildWnd == (UIWnd *)2 && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( v16 )
    {
      v13 = this->m_pfather;
      this->m_pChildWnd = ((UIWnd *)((UIWnd *)1));
      if ( v13 )
        v13->OnMessage(1001, this->m_id, 0);
    }
    else
    {
      this->m_pChildWnd = ((UIWnd *)0);
    }
  }
  v15 = (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return v16 || v15;
}

// 0x0043B500
unsigned __int8 UIScene::GetChildWidget(unsigned int dwVal, unsigned int dwVal2, int nVal)
{
  Parent_Data *m_bVisible; // edx
  gbTexture_D3D *TableEntry16; // eax
  int v7; // [esp-0xC] [ebp-0x14]
  int v8; // [esp-0x8] [ebp-0x10]

  if ( (dwVal & 0x80000000) != 0 )
    return 0;
  m_bVisible = (Parent_Data *)this->m_bVisible;
  if ( dwVal >= *(_DWORD *)&m_bVisible[260] || (dwVal2 & 0x80000000) != 0 || dwVal2 >= *(_DWORD *)&m_bVisible[261] )
    return 0;
  v8 = nVal + 4 * (*(_DWORD *)&m_bVisible[258] + dwVal);
  v7 = *(_DWORD *)&m_bVisible[259] - *(_DWORD *)&m_bVisible[257] - dwVal2 + 1024;
  TableEntry16 = (gbTexture_D3D *)GetTableEntry16(0);
  return (((gbTexture_D3D *)TableEntry16))->gbTexture_D3D::GetByte(v7, v8);
}

// 0x0043B660
int UIScene::Render()
{
  int result; // eax
  LONG top; // edx
  tagRECT *p_m_rect; // edi
  int v5; // eax
  LONG bottom; // eax
  int TableEntry16; // ebx
  UIWnd *m_pChildWnd; // eax
  char *v9; // eax
  Parent_Data *v10; // eax
  LONG v11; // eax
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
  p_m_rect = (tagRECT *)&this->m_rect;
  v5 = this->m_rect.left + 2;
  right = this->m_rect.right;
  v29 = v5;
  bottom = this->m_rect.bottom;
  v30 = top + 2;
  v32 = bottom;
  TableEntry16 = GetTableEntry16(0);
  if ( !TableEntry16 )
  {
    v15 = this->m_rect.bottom;
    v16 = this->m_rect.right;
    m_bVisible = (unsigned int)&g_fUIColorParam;
    p_nTex = v15;
    v23.Color = v16;
    goto LABEL_17;
  }
  m_pChildWnd = (UIWnd *)this->m_pChildWnd;
  if ( m_pChildWnd )
  {
    v9 = (char *)&m_pChildWnd[-1].m_bfocus + 3;
    if ( v9 )
    {
      if ( v9 == (char *)1 )
      {
        m_bVisible = (unsigned int)this->m_bVisible;
        p_nTex = (int)&v40.nTex;
        v23.Color = (unsigned int)&this[1].m_rect.bottom;
        v41 = 1;
        v40.nTex = TableEntry16;
        (((TextureLibDataBase *)&v29))->TextureLibDataBase::GetTextureInfo((char *)&this->m_rect);
      }
    }
    else
    {
      m_bVisible = (unsigned int)this->m_bVisible;
      p_nTex = 1;
      v23.Color = (unsigned int)&v39;
      v21 = *((TextureLibDataBase **)this + 5);
      left = (char *)p_m_rect->left;
      v40.pTexPt[15] = (gbTexture *)1;
      v39 = TableEntry16;
      (((TextureLibDataBase *)v21))->TextureLibDataBase::GetLibInfo(left);
    }
  }
  else
  {
    v10 = (Parent_Data *)this->m_bVisible;
    m_bVisible = 1;
    p_nTex = (int)v10;
    v23.Color = 276;
    v38 = 1;
    v37[0] = TableEntry16;
    (((TextureLibDataBase *)v37))->TextureLibDataBase::SetLibFolder((const char *)&this->m_rect, (int)&this->m_wndcolor);
  }
  if ( this->m_benable )
    goto LABEL_18;
  v11 = this[1].m_rect.left;
  if ( v11 )
  {
    if ( v11 == 1 )
    {
      m_bVisible = *(_DWORD *)&this->m_bOverlayRender;
      p_nTex = 1;
      v23.Color = (unsigned int)v37;
      v22 = *((TextureLibDataBase **)this + 6);
      v20 = (char *)p_m_rect->left;
      v38 = 1;
      v37[0] = TableEntry16;
      (((TextureLibDataBase *)v22))->TextureLibDataBase::GetLibInfo(v20);
    }
    goto LABEL_18;
  }
  if ( !this->m_pTexture )
  {
    v13 = this->m_rect.bottom;
    v14 = this->m_rect.right;
    m_bVisible = (unsigned int)&g_fUIColorParam;
    p_nTex = v13;
    v23.Color = v14;
LABEL_17:
    crt_sub_00540070();
    goto LABEL_18;
  }
  m_bVisible = *(_DWORD *)&this->m_bOverlayRender;
  p_nTex = 276;
  v23.Color = m_bVisible;
  (((TextureLibDataBase *)v12))->TextureLibDataBase::_CheckItem((char *)&this->m_rect, (char *)&this->m_rect);
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
      v18 = (UIWnd *)this->m_pChildWnd;
      LOBYTE(nW) = (nW - 64) & (((unsigned __int8)nW - 64 < 0) - 1);
      if ( v18 == (UIWnd *)2 )
        v34 = v30 + 6;
    }
    UIRenderPar((int)(&this->m_hTexture + 1), (int)&nY, (int)&nW, 1, (gbColorQuad *)1, v26, v27);
  }
  (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
  return result;
}

// 0x0043B900
BOOL UIScene::Update_B900(int nVal, int nVal2)
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
  POINT pt; // [esp+0x10] [ebp-0x8] BYREF

  if ( !this->m_bvisible )
    return 0;
  if ( !this->m_benable )
  {
    this->m_pChildWnd = ((UIWnd *)0);
    return 0;
  }
  if ( !nVal2 )
  {
    this->m_pChildWnd = ((UIWnd *)0);
    return (((SceneObj *)this))->SceneObj::Update(nVal, 0) /* [ROWTABLE] */;
  }
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
  p_m_rect = (tagRECT *)&this->m_rect;
  v6 = PtInRect(&this->m_rect, pt);
  v16 = v6;
  if ( this->m_pChildWnd != (UIWnd *)2 )
  {
    if ( !v6 )
    {
      this->m_pChildWnd = ((UIWnd *)0);
      goto LABEL_14;
    }
    this->m_pChildWnd = ((UIWnd *)((UIWnd *)1));
  }
  if ( !v6 )
  {
LABEL_14:
    if ( !this->m_bCursorLeft )
    {
      m_pfather = this->m_pfather;
      this->m_bCursorLeft = 1;
      if ( m_pfather )
        m_pfather->OnMessage(1003, this->m_id, 0);
    }
    goto LABEL_17;
  }
  left = p_m_rect->left;
  top = this->m_rect.top;
  v9 = pt.x - p_m_rect->left;
  v10 = pt.y - top;
  if ( this->m_bVisible )
  {
    ChildWidget = this->UIScene::GetChildWidget(pt.x - left, pt.y - top, 3);
  }
  else
  {
    if ( v9 >= *(_DWORD *)(GetTableEntry16(0) + 24) )
      v9 = *(_DWORD *)(GetTableEntry16(0) + 24) - 1;
    if ( v10 >= *(_DWORD *)(GetTableEntry16(0) + 28) )
      v10 = *(_DWORD *)(GetTableEntry16(0) + 28) - 1;
    ChildWidget = (((UIScene *)&this->m_nClipW))->UIScene::GetPixelChannel(0, v9, v10, 3);
  }
  if ( ChildWidget < 6u )
  {
    v16 = 0;
    this->m_pChildWnd = ((UIWnd *)0);
  }
  else if ( g_Input.KeyInfo[0].PressTime == 1 )
  {
    this->m_pChildWnd = ((UIWnd *)((UIWnd *)2));
    this->m_bCursorLeft = 0;
  }
  else
  {
    v14 = this->m_pfather;
    if ( v14 )
      v14->OnMessage(1002, this->m_id, 0);
    this->m_bCursorLeft = 0;
  }
LABEL_17:
  if ( this->m_pChildWnd == (UIWnd *)2 && (g_Input.KeyInfo[0].Data & 0xF) != 1 )
  {
    if ( v16 )
    {
      v13 = this->m_pfather;
      this->m_pChildWnd = ((UIWnd *)((UIWnd *)1));
      if ( v13 )
        v13->OnMessage(1001, this->m_id, 0);
    }
    else
    {
      this->m_pChildWnd = ((UIWnd *)0);
    }
  }
  v15 = (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return v16 || v15;
}

// 0x0043BCE0
// write access to const memory has been detected, the output may be wrong!
int *UIScene::ctor()
{
  ClearSubArraySlot();
  this->m_nShowState = 32;
  this->m_pChildWnd = ((UIWnd *)((UIWnd *)32));
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
  this->m_bVisible = ((Parent_Data *)0);
  this->m_hFont = 0;
  this->m_fAngle = -1.7014635547491816e+38f;
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
  this->m_bEnabled = ((Parent_Data *)0);
  this->m_pTexture = ((gbTexture *)0);
  *(_DWORD *)&this->m_bOverlayRender = 0;
  return (int *)this;
}

// 0x0043BE10
void * UIScene::_sdtor_call_dtor(char a2)
{
  (((CCBResultWindow *)this))->CCBResultWindow::~CCBResultWindow() /* [ROWTABLE] */;
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x0043BE80
void UIScene::ReleaseTexture()
{
  int *p_m_nFieldD0; // esi
  int v2; // ebx

  p_m_nFieldD0 = (int *)&this->m_nFieldD0;
  v2 = 3;
  do
  {
    if ( *p_m_nFieldD0 )
    {
      (((gbRefObject *)*p_m_nFieldD0))->gbRefObject::Release();
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
    v5 = (gbRefObject *)(*(gbRefObject **)&this->m_bCursorLeft);
    if ( v5 )
      (((gbRefObject *)v5))->gbRefObject::Release();
    ((OpenBaseFile *)&lpString)->OpenBaseFile::OpenBaseFile();
    v6 = (bool)pData == 0;
    this->m_hTexture = 0;
    if ( v6 )
    {
      *(_DWORD *)&this->m_bCursorLeft  = (unsigned long)(gfxMgr->NewTexture((const char *)v3));
    }
    else
    {
      v7 = *(_DWORD *)*(void**)(gfxMgr);
      v8 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(v3);
      *(_DWORD *)&this->m_bCursorLeft  = (unsigned long)(gfxMgr->NewTexture((const char *)v8));
      this->m_hTexture = (int)(((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(v3);
    }
    v9 = (gbTexture *)(*(gbTexture **)&this->m_bCursorLeft);
    if ( v9 )
      (((gbTexture *)v9))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&lpString)->OpenNULLFile::OpenNULLFile();
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
  float v25; // st7
  int v26; // [esp+0x4] [ebp-0x4]

  if ( fVal >= 0.0f )
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
            m_pChildWnd = (UIWnd *)this->m_pChildWnd;
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
          v10 = (UIWnd *)this->m_pChildWnd;
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
      v16 = (UIWnd *)this->m_pChildWnd;
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
      v22 = (UIWnd *)this->m_pChildWnd;
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
          m_pChildWnd = (UIWnd *)this->m_pChildWnd;
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
        v10 = (UIWnd *)this->m_pChildWnd;
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
        v16 = (UIWnd *)this->m_pChildWnd;
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
      v21 = (UIWnd *)this->m_pChildWnd;
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
  float m_nNotifyRender; // st7
  gbVFileSystem *result; // eax
  float v13; // st7
  float v14; // st6
  float v15; // st7
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
  m_pChildWnd = (UIWnd *)this->m_pChildWnd;
  this->m_pChildData = ((char *)((char *)p_DWORD[3]));
  this->m_nRectW = p_DWORD[1] - (_DWORD)m_pChildWnd;
  v9 = (__int64)((double)(*p_DWORD - m_nShowState / 2) + *((float *)&this->m_hTexture + 7));
  this->m_nRectH = v9;
  v20.m_plastsys = (gbVFileSystem *)(m_nShowState + v9);
  v10 = (__int64)((double)(m_nShowState + (int)v9) - *((float *)&this->m_hTexture + 7));
  m_nNotifyRender = (float)this->m_nNotifyRender;
  HIDWORD(v10) = this->m_nRectW;
  this->m_nScrollWidget = v10;
  result = (gbVFileSystem *)pVFileSystem;
  v13 = m_nNotifyRender - *((float *)&this->m_hTexture + 7);
  v14 = (float)this->m_nPosY + *((float *)&this->m_hTexture + 7);
  this->m_nPosX = (int)m_pChildWnd + HIDWORD(v10);
  v15 = v13 - v14;
  *((float *)&this->m_hTexture + 4) = v15;
  *((float *)&this->m_hTexture + 5) = v15;
  *((float *)&this->m_hTexture + 8) = v15 / v15;
  if ( pVFileSystem )
  {
    v22 = 0;
    v16 = 0;
    p_m_nFieldD0 = (int *)&this->m_nFieldD0;
    do
    {
      p_m_nFieldD0[3] = 0;
      if ( *p_m_nFieldD0 )
        (((gbRefObject *)*p_m_nFieldD0))->gbRefObject::Release();
      sprintf(Buffer, "%s%d.tga", (const char *)pVFileSystem, v16);
      if ( pData )
      {
        v18 = *(_DWORD *)*(void**)(gfxMgr);
        v19 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(Buffer);
        *p_m_nFieldD0 = gfxMgr->NewTexture((const char *)v19);
        p_m_nFieldD0[3] = (unsigned long)(int)(((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(Buffer);
      }
      else
      {
        *p_m_nFieldD0 = gfxMgr->NewTexture((const char *)Buffer);
      }
      if ( *p_m_nFieldD0 )
        (((gbTexture *)*p_m_nFieldD0))->gbTexture::LoadTexture(1);
      ++v16;
      ++p_m_nFieldD0;
    }
    while ( v16 < 3 );
    *(_DWORD *)&this->m_nTodo_050 = this->m_nRectW;
    LODWORD(this->m_fScaleX) = (unsigned long)*p_DWORD;
    this->m_nScrollState = p_DWORD[2];
    this->m_nScrollIdx = p_DWORD[3];
    LODWORD(this->m_fScaleY) = id;
    this->m_nViewW = parent;
    this->UIWnd::Create(id, (tagRECT *)&this->m_fScaleX, parent);
    v22 = -1;
    ((OpenNULLFile *)&v20)->OpenNULLFile::OpenNULLFile();
  }
  return result;
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
      m_pChildWnd = (UIWnd *)this->m_pChildWnd;
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
      v21 = (UIWnd *)this->m_pChildWnd;
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
      v7 = (UIWnd *)this->m_pChildWnd;
      v8 = (__int64)((double)(result - (int)v7) + *((float *)&this->m_hTexture + 12) + *((float *)&this->m_hTexture + 7));
      HIDWORD(v8) = this->m_nShowState;
      v9 = *(&this->m_hTexture + 9);
      v10 = this->m_nPosY;
      this->m_nRectW = v8;
      goto LABEL_10;
    }
    if ( v6 == 1 )
    {
      v7 = (UIWnd *)this->m_pChildWnd;
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
  float v6; // st7
  __int64 v7; // rax
  float m_nNotifyRender; // st7
  float v9; // st7
  int v10; // ebx
  __int64 v11; // rax
  float v12; // st7
  __int64 v13; // rax
  float v14; // st7
  __int64 v15; // rax
  int v16; // eax
  float v17; // st7
  float v18; // st6
  __int64 v19; // rax
  float v20; // st7
  float v21; // st7
  int v22; // edi
  float v23; // st7
  __int64 v24; // rax
  int v25; // ecx
  int result; // eax
  int v27[16]; // [esp+0x10] [ebp-0x44] BYREF
  int v28; // [esp+0x50] [ebp-0x4]

  if ( *(_DWORD *)&this->m_bCursorLeft )
  {
    v27[0] = *(_DWORD *)&this->m_bCursorLeft;
    p_m_nPosY = (int *)&this->m_nPosY;
    v28 = 1;
    (((TextureLibDataBase *)v27))->TextureLibDataBase::SetLibFolder((const char *)&this->m_nPosY, (int)&this->m_wndcolor);
  }
  else
  {
    p_m_nPosY = (int *)&this->m_nPosY;
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
          this->m_pChildData = ((char *)(v5));
          v6 = (float)(int)v5;
          v7 = (__int64)(v6 - *((float *)&this->m_hTexture + 3));
          this->m_nColors = v7;
          if ( (double)(int)&v5[-v7] > *((float *)&this->m_hTexture + 4) )
            this->m_nColors = (__int64)(v6 - *((float *)&this->m_hTexture + 4));
          m_nNotifyRender = (float)this->m_nNotifyRender;
          this->m_hScrollBar = (__int64)((double)*p_m_nPosY + *((float *)&this->m_hTexture + 7));
          this->m_bLoadState = (__int64)(m_nNotifyRender - *((float *)&this->m_hTexture + 7));
        }
      }
      else
      {
        v9 = (float)*p_m_nPosY;
        v10 = (__int64)(*((float *)&this->m_hTexture + 12)
                      + *((float *)&this->m_hTexture + 7)
                      + (double)this->m_nLoadResource);
        this->m_nColors = v10;
        v11 = (__int64)(v9 + *((float *)&this->m_hTexture + 7));
        v12 = (float)this->m_nNotifyRender;
        this->m_hScrollBar = v11;
        v13 = (__int64)(v12 - *((float *)&this->m_hTexture + 7));
        v14 = (float)v10;
        this->m_bLoadState = v13;
        v15 = (__int64)(v14 + *((float *)&this->m_hTexture + 3));
        this->m_pChildData = ((char *)((char *)v15));
        if ( (double)((int)v15 - v10) > *((float *)&this->m_hTexture + 4) )
          this->m_pChildData = ((char *)((char *)(__int64)(v14 + *((float *)&this->m_hTexture + 4))));
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
      v17 = (float)this->m_nNotifyRender;
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
      v21 = *((float *)&this->m_hTexture + 10) + *((float *)&this->m_hTexture + 7) + (float)*p_m_nPosY;
      this->m_nColors = (__int64)((double)this->m_nLoadResource + *((float *)&this->m_hTexture + 7));
      v22 = (__int64)v21;
      this->m_hScrollBar = v22;
      v23 = (float)v22;
      v24 = (__int64)(v23 + *((float *)&this->m_hTexture + 3));
      this->m_bLoadState = v24;
      if ( (double)((int)v24 - v22) > *((float *)&this->m_hTexture + 4) )
        this->m_bLoadState = (__int64)(v23 + *((float *)&this->m_hTexture + 4));
    }
    this->m_pChildData = ((char *)((char *)(__int64)((double)(int)this->m_dwColor - *((float *)&this->m_hTexture + 7))));
  }
LABEL_20:
  if ( *(&this->m_hTexture + 1) )
  {
    v27[0] = *(&this->m_hTexture + 1);
    v28 = 1;
    (((TextureLibDataBase *)&this->m_wndcolor))->TextureLibDataBase::SetLibFolder((const char *)&this->m_hScrollBar, (int)&this->m_wndcolor);
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
    (((TextureLibDataBase *)v27))->TextureLibDataBase::SetLibFolder((const char *)&this->m_nRectH, (int)&this->m_wndcolor);
  }
  (((UITitle_BBTY *)this))->UITitle_BBTY::Render() /* [ROWTABLE] */;
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
  int y; // ecx
  int m_nRectX; // eax
  int v13; // eax
  int v14; // eax
  int v15; // ebp
  int v16; // edx
  int v17; // ecx
  int v18; // eax
  UIWnd *m_pChildWnd; // edi
  float v20; // st7
  float v21; // st7
  float v22; // st6
  int v23; // ecx
  float v24; // st7
  int v25; // eax
  int v26; // edx
  int v27; // ecx
  int v28; // eax
  float v29; // st7
  UIWnd *v30; // edi
  float v31; // st7
  float v32; // st7
  float v33; // st6
  float v34; // st7
  int v35; // ecx
  int m_nViewW; // edi
  int v37; // eax
  int x; // ebp
  int m_nPosY; // eax
  int v40; // edx
  int v41; // ecx
  bool v42; // cc
  int m_nShowState; // edi
  float v44; // st7
  int v45; // edx
  float v46; // st7
  float v47; // st7
  float v48; // st6
  int v49; // edx
  int v50; // eax
  int v51; // edx
  int v52; // ecx
  float v53; // st7
  int v54; // edx
  float v55; // st7
  float v56; // st6
  float v57; // st7
  int v58; // ecx
  int v59; // edx
  int v60; // eax
  int v61; // eax
  int m_nLoadResource; // [esp+0x8] [ebp-0x28]
  int v63; // [esp+0x8] [ebp-0x28]
  int m_nNotifyRender; // [esp+0x8] [ebp-0x28]
  int m_dwColor; // [esp+0xC] [ebp-0x24]
  int v66; // [esp+0xC] [ebp-0x24]
  int v67; // [esp+0x10] [ebp-0x20]
  POINT pt; // [esp+0x18] [ebp-0x18] BYREF
  int pOut; // [esp+0x20] [ebp-0x10] BYREF
  int pOut2; // [esp+0x24] [ebp-0xC] BYREF
  struct tagPOINT Point; // [esp+0x28] [ebp-0x8] BYREF

  if ( !nVal2 )
    return (((SceneObj *)this))->SceneObj::Update(nVal, 0) /* [ROWTABLE] */;
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&pt);
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
        {
          y = pt.y;
          this->m_nRectY = pt.x;
          this->m_nClipW = y;
        }
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
  (((GRPinput *)&g_Input))->GRPinput::GetMousePos(&pOut, &pOut2);
  (((GRPinput *)&g_Input))->GRPinput::GetCursorPos(&Point);
  v13 = *(&this->m_hTexture + 14);
  if ( v13 )
  {
    if ( v13 != 1 )
      goto LABEL_54;
    v14 = *(&this->m_hTexture + 15);
    v15 = pt.y;
    if ( v14 )
    {
      if ( v14 == 1 )
      {
        v16 = this->m_nPosX;
        m_dwColor = this->m_dwColor;
        v17 = -pOut2;
        v67 = -pOut2;
        this->m_nClipX = -pOut2;
        if ( v16 <= m_dwColor )
        {
          v18 = this->m_nRectW;
          m_nLoadResource = this->m_nLoadResource;
          if ( v18 >= m_nLoadResource )
          {
            m_pChildWnd = (UIWnd *)this->m_pChildWnd;
            this->m_nRectW = v18 - v17;
            v20 = (float)v67 + *((float *)&this->m_hTexture + 3);
            this->m_nPosX = (int)m_pChildWnd + v18 - v17;
            this->m_nClipW = v15;
            *((float *)&this->m_hTexture + 3) = v20;
            *((float *)&this->m_hTexture + 6) = v20 * *((float *)&this->m_hTexture + 8);
            v21 = (float)((int)m_pChildWnd / 2);
            v22 = (float)m_nLoadResource + *((float *)&this->m_hTexture + 12) + *((float *)&this->m_hTexture + 7) - v21;
            if ( (double)(v18 - v17) <= v22 )
            {
              v23 = *(&this->m_hTexture + 5);
              this->m_nRectW = (__int64)v22;
              *(&this->m_hTexture + 6) = v23;
              this->m_nPosX = (int)m_pChildWnd + (__int64)v22;
              *(&this->m_hTexture + 3) = *(&this->m_hTexture + 4);
            }
            v24 = v21 + (float)m_dwColor - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 13);
            if ( (double)this->m_nPosX >= v24 )
            {
              this->m_nPosX = (__int64)v24;
              this->m_nRectW = (__int64)v24 - (_DWORD)m_pChildWnd;
              *(&this->m_hTexture + 3) = 0;
              *(&this->m_hTexture + 6) = 0;
            }
          }
        }
      }
    }
    else
    {
      v25 = this->m_dwColor;
      v26 = this->m_nPosX;
      v27 = pOut2;
      this->m_nClipX = pOut2;
      v66 = v25;
      if ( v26 <= v25 )
      {
        v28 = this->m_nRectW;
        v63 = this->m_nLoadResource;
        if ( v28 >= v63 )
        {
          v29 = (float)pOut2;
          v30 = (UIWnd *)this->m_pChildWnd;
          this->m_nRectW = v27 + v28;
          v31 = v29 + *((float *)&this->m_hTexture + 3);
          this->m_nPosX = (int)v30 + v27 + v28;
          this->m_nClipW = v15;
          *((float *)&this->m_hTexture + 3) = v31;
          *((float *)&this->m_hTexture + 6) = v31 * *((float *)&this->m_hTexture + 8);
          v32 = (float)((int)v30 / 2);
          v33 = (float)v63 + *((float *)&this->m_hTexture + 12) + *((float *)&this->m_hTexture + 7) - v32;
          if ( (double)(v27 + v28) <= v33 )
          {
            this->m_nRectW = (__int64)v33;
            this->m_nPosX = (int)v30 + (__int64)v33;
            *(&this->m_hTexture + 3) = 0;
            *(&this->m_hTexture + 6) = 0;
          }
          v34 = v32 + (float)v66 - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 13);
          if ( (double)this->m_nPosX >= v34 )
          {
            v35 = *(&this->m_hTexture + 5);
            this->m_nPosX = (__int64)v34;
            *(&this->m_hTexture + 6) = v35;
            this->m_nRectW = (__int64)v34 - (_DWORD)v30;
            *(&this->m_hTexture + 3) = *(&this->m_hTexture + 4);
          }
        }
      }
    }
    m_nViewW = this->m_nViewW;
    this->m_nRectY = pt.x;
    this->m_nClipW = v15;
    if ( !m_nViewW )
      goto LABEL_54;
    goto LABEL_53;
  }
  v37 = *(&this->m_hTexture + 15);
  x = pt.x;
  if ( v37 )
  {
    if ( v37 != 1 )
      goto LABEL_52;
    m_nPosY = this->m_nPosY;
    v40 = Point.x;
    v41 = pOut;
    v42 = Point.x < m_nPosY;
    this->m_nClipX = pOut;
    if ( v42 )
      goto LABEL_52;
    m_nNotifyRender = this->m_nNotifyRender;
    if ( v40 > m_nNotifyRender )
      goto LABEL_52;
    m_nShowState = this->m_nShowState;
    v44 = (float)pOut;
    v45 = this->m_nRectH - v41;
    this->m_nRectY = x;
    this->m_nRectH = v45;
    v46 = v44 + *((float *)&this->m_hTexture + 3);
    this->m_nScrollWidget = m_nShowState + v45;
    *((float *)&this->m_hTexture + 3) = v46;
    *((float *)&this->m_hTexture + 6) = v46 * *((float *)&this->m_hTexture + 8);
    v47 = (float)(m_nShowState / 2);
    v48 = (float)m_nPosY + *((float *)&this->m_hTexture + 10) + *((float *)&this->m_hTexture + 7) - v47;
    if ( (double)v45 <= v48 )
    {
      v49 = *(&this->m_hTexture + 4);
      this->m_nRectH = (__int64)v48;
      *(&this->m_hTexture + 3) = v49;
      this->m_nScrollWidget = m_nShowState + (__int64)v48;
      *(&this->m_hTexture + 6) = *(&this->m_hTexture + 5);
    }
  }
  else
  {
    v50 = this->m_nPosY;
    v51 = Point.x;
    v52 = pOut;
    v42 = Point.x < v50;
    this->m_nClipX = pOut;
    if ( v42 )
      goto LABEL_52;
    m_nNotifyRender = this->m_nNotifyRender;
    if ( v51 > m_nNotifyRender )
      goto LABEL_52;
    m_nShowState = this->m_nShowState;
    v53 = (float)pOut;
    v54 = v52 + this->m_nRectH;
    this->m_nRectY = x;
    this->m_nRectH = v54;
    v55 = v53 + *((float *)&this->m_hTexture + 3);
    this->m_nScrollWidget = m_nShowState + v54;
    *((float *)&this->m_hTexture + 3) = v55;
    *((float *)&this->m_hTexture + 6) = v55 * *((float *)&this->m_hTexture + 8);
    v47 = (float)(m_nShowState / 2);
    v56 = (float)v50 + *((float *)&this->m_hTexture + 10) + *((float *)&this->m_hTexture + 7) - v47;
    if ( (double)v54 <= v56 )
    {
      this->m_nRectH = (__int64)v56;
      this->m_nScrollWidget = m_nShowState + (__int64)v56;
      *(&this->m_hTexture + 3) = 0;
      *(&this->m_hTexture + 6) = 0;
    }
  }
  v57 = v47 + (float)m_nNotifyRender - *((float *)&this->m_hTexture + 7) + *((float *)&this->m_hTexture + 11);
  if ( (double)this->m_nScrollWidget >= v57 )
  {
    v58 = *(&this->m_hTexture + 4);
    v59 = *(&this->m_hTexture + 5);
    this->m_nScrollWidget = (__int64)v57;
    this->m_nRectH = (__int64)v57 - m_nShowState;
    *(&this->m_hTexture + 3) = v58;
    *(&this->m_hTexture + 6) = v59;
  }
LABEL_52:
  m_nViewW = this->m_nViewW;
  v60 = pt.y;
  this->m_nRectY = x;
  this->m_nClipW = v60;
  if ( m_nViewW )
LABEL_53:
    (*(void ( **)(int, int, _DWORD, _DWORD))(*(_DWORD *)m_nViewW + 24))(
      m_nViewW,
      1019,
      LODWORD(this->m_fScaleY),
      (__int64)*((float *)&this->m_hTexture + 6));
LABEL_54:
  v61 = (((SceneObj *)this))->SceneObj::Update(nVal, nVal2) /* [ROWTABLE] */;
  return LOBYTE(this->m_nClipY) || v61;
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
    if ( m_fCameraOffset != 0.0f )
      (((gbRefObject *)LODWORD(m_fCameraOffset)))->gbRefObject::Release();
    ((OpenBaseFile *)&lpString)->OpenBaseFile::OpenBaseFile();
    v4 = v10 == 0;
    this->m_bFieldCC = ((Parent_Data *)0);
    if ( v4 )
    {
      LODWORD(this->m_fCameraOffset) = gfxMgr->NewTexture((const char *)v1);
    }
    else
    {
      v5 = *(_DWORD *)*(void**)(gfxMgr);
      v6 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(v1);
      LODWORD(this->m_fCameraOffset) = gfxMgr->NewTexture((const char *)v6);
      this->m_bFieldCC = ((Parent_Data *)((((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(v1)));
    }
    v7 = this->m_fCameraOffset;
    if ( v7 != 0.0f )
      (((gbTexture *)LODWORD(v7)))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&lpString)->OpenNULLFile::OpenNULLFile();
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
      (((gbRefObject *)m_nFieldD0))->gbRefObject::Release();
    ((OpenBaseFile *)&lpString)->OpenBaseFile::OpenBaseFile();
    v4 = v10 == 0;
    this->m_bVisible = ((Parent_Data *)0);
    if ( v4 )
    {
      this->m_nFieldD0 = gfxMgr->NewTexture((const char *)v1);
    }
    else
    {
      v5 = *(_DWORD *)*(void**)(gfxMgr);
      v6 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(v1);
      this->m_nFieldD0 = gfxMgr->NewTexture((const char *)v6);
      this->m_bVisible = ((Parent_Data *)((((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(v1)));
    }
    v7 = (gbTexture *)this->m_nFieldD0;
    if ( v7 )
      (((gbTexture *)v7))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&lpString)->OpenNULLFile::OpenNULLFile();
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
      (((gbRefObject *)m_hFont))->gbRefObject::Release();
    ((OpenBaseFile *)&lpString)->OpenBaseFile::OpenBaseFile();
    v4 = v9 == 0;
    this->m_bEnabled = ((Parent_Data *)0);
    if ( v4 )
    {
      this->m_hFont = gfxMgr->NewTexture((const char *)v1);
    }
    else
    {
      v5 = *(_DWORD *)*(void**)(gfxMgr);
      v6 = (((_Texture_Info *)&stru_1894B78))->_Texture_Info::_CalculateUV(v1);
      this->m_hFont = gfxMgr->NewTexture((const char *)v6);
      this->m_bEnabled = ((Parent_Data *)((((TextureLibDataBase *)&stru_1894B78))->TextureLibDataBase::CreateParentData(v1)));
    }
    v7 = (gbTexture *)this->m_hFont;
    if ( v7 )
      (((gbTexture *)v7))->gbTexture::LoadTexture(1);
    ((OpenNULLFile *)&lpString)->OpenNULLFile::OpenNULLFile();
  }
}

// 0x00442060
void UIScene::SetFirstShow(int nVal1)
{
  char *m_pChildData; // eax
  float m_fAngle; // eax
  Parent_Data *v5; // eax

  m_pChildData = (char *)this->m_pChildData;
  LODWORD(this->m_fCameraOffset) = nVal1;
  if ( nVal1 < (int)m_pChildData )
    LODWORD(this->m_fCameraOffset) = (unsigned long)m_pChildData;
  m_fAngle = this->m_fAngle;
  if ( SLODWORD(this->m_fCameraOffset) > SLODWORD(m_fAngle) )
    this->m_fCameraOffset = m_fAngle;
  v5 = (Parent_Data *)CalcWeightedOffset();
  this->m_nFieldD0 = (int)v5;
  this->m_bFieldCC = ((Parent_Data *)(v5));
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
void UIScene::SetState(int nVal1)
{
  this->m_hFont = nVal1;
  if ( nVal1 )
  {
    LODWORD(this->m_fCameraOffset) = 2;
    *(tagRECT *)&this->m_nScrollIdx = this->m_rect;
  }
}

// 0x00445F80
unsigned __int8 UIScene::GetPixelChannel(int nX, int nY, int nW, int nH)
{
  return (((gbTexture *)*((gbTexture **)((UIWnd *)this) + nX)))->gbTexture::GetPixelChannel(nY, nW, nH);
}

// 0x0044BE40
void UIScene::sub_44BE40(int a2)
{
  (((UIScenePanel *)this))->UIScenePanel::_scalar_dtor_BE80() /* [ROWTABLE] */;
  if ( (a2 & 1) != 0 )
    operator delete(this);
}

// 0x0044C910
void UIScene::Destroy_C910()
{
  UIWnd *m_pChildWnd; // ecx
  int m_nClipX; // ecx
  int m_nClipY; // ecx

  Destroy__ovl_03((int)this);
  m_pChildWnd = (UIWnd *)this[40].m_pChildWnd;
  if ( m_pChildWnd )
    delete m_pChildWnd;
  m_nClipX = this[40].m_nClipX;
  if ( m_nClipX )
    (*(void ( **)(int, int))(*(_DWORD *)m_nClipX + 20))(m_nClipX, 1);
  m_nClipY = this[40].m_nClipY;
  if ( m_nClipY )
    (*(void ( **)(int, int))(*(_DWORD *)m_nClipY + 20))(m_nClipY, 1);
  this[40].m_pChildWnd = ((UIWnd *)0);
  this[40].m_nClipX = 0;
  this[40].m_nClipY = 0;
}

// 0x0044DAC0
void UIScene::PostRender()
{
  int m_pChildWnd; // ecx

  switch ( this[40].m_nRectX )
  {
    case 0:
      (((CCBControlWindow *)this))->CCBControlWindow::Render((CCBMagicWindow *)this) /* [ROWTABLE] */;
      break;
    case 1:
      m_pChildWnd = (int)this[40].m_pChildWnd;
      goto LABEL_6;
    case 3:
      (*(void ( **)(int, UIScene *))(*(_DWORD *)this[40].m_nClipX + 4))(this[40].m_nClipX, this);
      break;
    case 4:
      m_pChildWnd = this[40].m_nClipY;
LABEL_6:
      (*(void ( **)(int, UIScene *))(*(_DWORD *)m_pChildWnd + 4))(m_pChildWnd, this);
      break;
    default:
      break;
  }
  crt_sub_00540FD0();
}

// 0x0044DB70
int UIScene::StopAllSounds(float fFade, int nFlags)
{
  CScreenMode *Instance; // eax
  gbAudioManager *AudioManager; // eax
  __int64 v6; // rcx
  int v7; // esi
  int v8; // esi
  CScreenMode *v9; // eax
  gbAudioManager *v10; // eax
  gbAudioManager *v11; // esi
  CScreenMode *v13; // eax
  gbAudioManager *v14; // eax
  gbAudioManager *v15; // esi
  CScreenMode *v16; // eax
  gbAudioManager *v17; // eax
  gbAudioManager *v18; // esi
  PalScriptMgr *v19; // ecx
  char v20; // al
  unsigned int v21; // ecx
  unsigned int v22; // edx
  float *m_nClipW; // eax
  int v24; // edx
  double v25; // st7
  int v26; // edi
  double v27; // st7
  void ( **v28)(int *, _DWORD); // edx
  int m_pChildWnd; // ecx
  int m_nClipY; // eax
  CScreenMode *v31; // eax
  gbAudioManager *v32; // eax
  gbAudioManager *v33; // esi
  CScreenMode *v34; // eax
  double v35; // [esp-0x4] [ebp-0x18]
  int fFadea; // [esp+0x18] [ebp+0x4]

  if ( g_nSceneState != 2 && (g_dwGameFlags & 1) != 0 )
  {
    Instance = (CScreenMode *)CScreenMode::GetInstance();
    AudioManager = (gbAudioManager *)(((CScreenMode *)Instance))->CScreenMode::GetAudioManager();
    (((gbAudioManager *)AudioManager))->gbAudioManager::DetachAll3D();
  }
  HIDWORD(v6) = 0;
  if ( !LOBYTE(this[40].m_nPosY) )
  {
    switch ( this[40].m_nRectX )
    {
      case 0:
        if ( !LOBYTE(this[40].m_nShowState) )
        {
          if ( !BYTE1(this[40].m_nPosX) )
          {
            if ( LOBYTE(this[40].m_nPosX) )
              LOBYTE(this[40].m_nPosX) = 0;
            *(float *)(this[40].m_nClipW + 4 * this[40].m_nRectW) = fFade;
            v20 = BYTE2(this[40].m_nPosX);
            v21 = this[40].m_nRectW + 1;
            this[40].m_nRectW = v21;
            v22 = v21;
            if ( !v20 )
              BYTE2(this[40].m_nPosX) = v21 >= this[40].m_nRectY;
            LODWORD(v6) = this[40].m_nRectY;
            this[40].m_nRectH = 0;
            this[40].m_nRectW = v22 < (unsigned int)v6 ? v22 : 0;
            if ( (_DWORD)v6 )
            {
              m_nClipW = (float *)this[40].m_nClipW;
              v24 = v6;
              do
              {
                v25 = *m_nClipW++ + *(float *)&this[40].m_nRectH;
                --v24;
                *(float *)&this[40].m_nRectH = v25;
              }
              while ( v24 );
            }
            fFade = *(float *)&this[40].m_nRectH / (float)v6;
          }
          if ( !BYTE2(this[40].m_nPosX) )
            return 1;
          v26 = LODWORD(fFade);
          (((CCCTData *)this))->CCCTData::InitEntries(fFade);
          if ( LOBYTE(this[41].m_nScrollWidget) )
          {
            if ( !(((UICoverFrm *)this))->UICoverFrm::UpdateAnimation(fFade) /* [ROWTABLE] */ )
            {
              v27 = *(float *)&this[32].m_nClipX - fFade * 80.0;
              *(float *)&this[32].m_nClipX = v27;
              if ( v27 <= 0.0 )
                this[32].m_nClipX = 0;
              if ( (*(_WORD *)((char *)&fFadea + 1) = -1,
                    LOBYTE(fFadea) = -1,
                    HIBYTE(fFadea) = (__int64)*(float *)&this[32].m_nClipX,
                    (((NPC *)(&this[31].m_hTexture + 20)))->NPC::UpdateAnim(fFadea),
                    g_Input.KeyInfo[0].PressTime == 1)
                && (g_Input.KeyInfo[0].Data & 0xF) == 1
                || g_Input.KeyInfo[1].PressTime == 1 && (g_Input.KeyInfo[1].Data & 0xF) == 1 )
              {
                (((UICoverFrm *)this))->UICoverFrm::SetDefaultValues() /* [ROWTABLE] */;
                v28 = (void ( **)(int *, _DWORD))*(&this[40].m_hTexture + 28);
                LOBYTE(this[41].m_nScrollWidget) = 0;
                (*v28)(&this[40].m_hTexture + 28, 0);
                LOBYTE(this[32].m_pChildWnd) = 1;
                (((SceneObj *)this))->SceneObj::Update(v26, nFlags) /* [ROWTABLE] */;
                goto LABEL_43;
              }
            }
          }
          else
          {
            (((JusticeBookUI *)this))->JusticeBookUI::UpdateFadeAnim(fFade) /* [ROWTABLE] */;
          }
          (((SceneObj *)this))->SceneObj::Update(v26, nFlags) /* [ROWTABLE] */;
          goto LABEL_43;
        }
        sub_407790();
        g_nSceneState = 2;
        (((PalScriptMgr *)v19))->PalScriptMgr::Destroy();
        (((CGameData *)&g_gamefrm))->CGameData::Load(0);
        (((GRPinput *)&g_Input))->GRPinput::Reset();
        return 1;
      case 1:
        m_pChildWnd = (int)this[40].m_pChildWnd;
        goto LABEL_42;
      case 3:
        m_pChildWnd = this[40].m_nClipX;
LABEL_42:
        (*(void ( **)(int, _DWORD, int))(*(_DWORD *)m_pChildWnd + 8))(
          m_pChildWnd,
          LODWORD(fFade),
          nFlags);
        goto LABEL_43;
      case 4:
        (*(void ( **)(int, _DWORD, int))(*(_DWORD *)this[40].m_nClipY + 8))(
          this[40].m_nClipY,
          LODWORD(fFade),
          nFlags);
        m_nClipY = this[40].m_nClipY;
        if ( !*(_DWORD *)(m_nClipY + 130360) )
          goto LABEL_43;
        LODWORD(v35) = *(_DWORD *)(m_nClipY + 130352);
        (((TaskBookUI *)v35))->TaskBookUI::_todo_456200();
        return 1;
      case 5:
        if ( (g_dwGameFlags & 4) != 0 )
        {
          v31 = (CScreenMode *)CScreenMode::GetInstance();
          v32 = (gbAudioManager *)(((CScreenMode *)v31))->CScreenMode::GetAudioManager();
          v33 = (gbAudioManager *)v32;
          if ( v32 )
          {
            (((gbAudioManager *)v32))->gbAudioManager::StopSoundStream(1);
            (((gbAudioManager *)v33))->gbAudioManager::StopSoundStream(2);
            v34 = (CScreenMode *)CScreenMode::GetInstance();
            (((CScreenMode *)v34))->CScreenMode::AudioStopAll();
          }
        }
        (((CGameData *)&g_gamefrm))->CGameData::Load(0);
        return 1;
      default:
LABEL_43:
        if ( BYTE1(this[40].m_nShowState) && *((_BYTE *)&this[32].m_hTexture + 72) && LOBYTE(this[33].m_nScrollWidget) )
          PostQuitMessage(0);
        return 1;
    }
  }
  v7 = this[40].m_nLoadResource - 1;
  if ( v7 )
  {
    v8 = v7 - 1;
    if ( v8 )
    {
      if ( v8 == 1 )
      {
        v9 = (CScreenMode *)CScreenMode::GetInstance();
        v10 = (gbAudioManager *)(((CScreenMode *)v9))->CScreenMode::GetAudioManager();
        v11 = (gbAudioManager *)v10;
        if ( v10 )
        {
          (((gbAudioManager *)v10))->gbAudioManager::DetachAll3D();
          (((gbAudioManager *)v11))->gbAudioManager::StopSoundStream(0);
          (((gbAudioManager *)v11))->gbAudioManager::StopSoundStream(2);
          (((gbAudioManager *)v11))->gbAudioManager::StopSoundStream(1);
        }
        (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)0xB);
        return 1;
      }
      else
      {
        return 1;
      }
    }
    else
    {
      v13 = (CScreenMode *)CScreenMode::GetInstance();
      v14 = (gbAudioManager *)(((CScreenMode *)v13))->CScreenMode::GetAudioManager();
      v15 = (gbAudioManager *)v14;
      if ( v14 )
      {
        (((gbAudioManager *)v14))->gbAudioManager::DetachAll3D();
        (((gbAudioManager *)v15))->gbAudioManager::StopSoundStream(0);
        (((gbAudioManager *)v15))->gbAudioManager::StopSoundStream(2);
        (((gbAudioManager *)v15))->gbAudioManager::StopSoundStream(1);
      }
      (((CGameData *)&g_gamefrm))->CGameData::Load((CUtil *)8);
      return 1;
    }
  }
  else
  {
    v16 = (CScreenMode *)CScreenMode::GetInstance();
    v17 = (gbAudioManager *)(((CScreenMode *)v16))->CScreenMode::GetAudioManager();
    v18 = (gbAudioManager *)v17;
    if ( v17 )
    {
      (((gbAudioManager *)v17))->gbAudioManager::DetachAll3D();
      (((gbAudioManager *)v18))->gbAudioManager::StopSoundStream(0);
      (((gbAudioManager *)v18))->gbAudioManager::StopSoundStream(2);
      (((gbAudioManager *)v18))->gbAudioManager::StopSoundStream(1);
    }
    PAL3::SnapScreen();
    return 1;
  }
}

// 0x0044DFC0
int UIScene::OnMessage(UICursor *msg, int wparam, int lparam)
{
  int result; // eax
  CScreenMode *Instance; // eax
  Actor *SaveDataManager; // eax
  CScreenMode *v8; // eax
  void *v9; // edx
  int v10; // edi
  int v11; // ebp
  CScreenMode *v12; // eax
  CScreenMode *v13; // eax
  CScreenMode *v14; // eax
  CScreenMode *v15; // eax
  const void *v16; // [esp-0x14] [ebp-0x18]
  const void *v17; // [esp-0xC] [ebp-0x10]
  const void *v18; // [esp-0xC] [ebp-0x10]
  const void *v19; // [esp-0xC] [ebp-0x10]
  const void *v20; // [esp-0xC] [ebp-0x10]
  const void *v21; // [esp-0xC] [ebp-0x10]

  if ( msg == (UICursor *)1000 )
  {
    if ( wparam )
    {
      BYTE1(this[40].m_nShowState) = 0;
      *((_BYTE *)&this[32].m_hTexture + 72) = 0;
      *(&this[32].m_hTexture + 16) = 1077097267;
      *(&this[32].m_hTexture + 20) = 1077097267;
      this[33].m_nRectH = 1077097267;
      this[33].m_nPosY = 1077097267;
      LOBYTE(this[33].m_nScrollWidget) = 0;
      *(&this[32].m_hTexture + 19) = 1056964608;
      this[33].m_nPosX = 1056964608;
      (((UICursor *)0x3E8))->UICursor::_todo_541CC0();
    }
    return 1;
  }
  else if ( msg == (UICursor *)1001 )
  {
    switch ( wparam )
    {
      case 161:
        if ( BYTE1(this[40].m_nShowState) || LOBYTE(this[41].m_nScrollWidget) )
          goto LABEL_25;
        PAL3::LoadRoleByIndex(0);
        LOBYTE(this[40].m_nShowState) = 1;
        v17 = off_59DC84;
        Instance = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)Instance))->CScreenMode::AudioSetPosition(v17, 1);
        SaveDataManager = (Actor *)GetSaveDataManager();
        (((Actor *)SaveDataManager))->Actor::IterateActiveActors();
        return 1;
      case 162:
        if ( BYTE1(this[40].m_nShowState) || LOBYTE(this[41].m_nScrollWidget) )
          goto LABEL_17;
        (((ChoseCompose *)this))->ChoseCompose::Init(1);
        v18 = off_59DC84;
        v8 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v8))->CScreenMode::AudioSetPosition(v18, 1);
        return 1;
      case 163:
        if ( BYTE1(this[40].m_nShowState) || LOBYTE(this[41].m_nScrollWidget) )
          goto LABEL_17;
        (((UICoverFrm *)this))->UICoverFrm::SetDefaultValues() /* [ROWTABLE] */;
        v9 = (void *)off_59DC84;
        goto LABEL_26;
      case 164:
        if ( BYTE1(this[40].m_nShowState) || LOBYTE(this[41].m_nScrollWidget) )
          goto LABEL_17;
        v10 = BYTE1(g_dwUISettings);
        v11 = BYTE2(g_dwUISettings);
        PAL3::WriteRegistryDword(szSubKey, szValueName, (unsigned __int8)g_dwUISettings);
        PAL3::WriteRegistryDword(szSubKey, "S_GAME_B", v10);
        PAL3::WriteRegistryDword(szSubKey, "S_GAME_C", v11);
        BYTE1(this[40].m_nShowState) = 1;
        *(&this[32].m_hTexture + 17) = 1;
        *(&this[32].m_hTexture + 14) = 1;
        *(&this[32].m_hTexture + 15) = 0;
        *((_BYTE *)&this[32].m_hTexture + 72) = 0;
        this[33].m_nRectW = 1;
        this[33].m_nRectY = 1;
        this[33].m_nClipW = 0;
        LOBYTE(this[33].m_nScrollWidget) = 0;
        v16 = off_59DC84;
        v12 = (CScreenMode *)CScreenMode::GetInstance();
        (((CScreenMode *)v12))->CScreenMode::AudioSetPosition(v16, 1);
        return 1;
      case 165:
        if ( BYTE1(this[40].m_nShowState) || LOBYTE(this[41].m_nScrollWidget) )
        {
LABEL_17:
          v19 = (const void *)off_59DC90;
          v13 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v13))->CScreenMode::AudioSetPosition(v19, 1);
          return 1;
        }
        (((ChoseCompose *)this))->ChoseCompose::Init(3);
        v9 = (void *)off_59DC84;
        goto LABEL_26;
      case 166:
        if ( BYTE1(this[40].m_nShowState) || LOBYTE(this[41].m_nScrollWidget) )
        {
LABEL_25:
          v9 = (void *)off_59DC90;
LABEL_26:
          v21 = v9;
          v15 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v15))->CScreenMode::AudioSetPosition(v21, 1);
LABEL_27:
          result = 1;
        }
        else
        {
          v20 = off_59DC84;
          v14 = (CScreenMode *)CScreenMode::GetInstance();
          (((CScreenMode *)v14))->CScreenMode::AudioSetPosition(v20, 1);
          (((ChoseCompose *)this))->ChoseCompose::Init(4);
          result = 1;
        }
        break;
      default:
        goto LABEL_27;
    }
  }
  else
  {
    return this->UIWnd::OnMessage((int)msg, wparam, lparam);
  }
  return result;
}

// 0x00455190
int UIScene::SetParam(int nVal)
{
  int result; // eax

  result = nVal;
  this->m_bFieldCC = ((Parent_Data *)((Parent_Data *)nVal));
  return result;
}

// 0x0045ADF0
void UIScene::DestroyParent()
{
  (((UICaption *)&this[1].m_pfather))->UICaption::Destroy2();
  (((UICaption *)&this->m_pfather))->UICaption::Destroy2();
}

// 0x0052E120
void UIScene::LoadMapData(int a1)
{
  this->m_bfocus = a1;
  this->UIScene::CalcViewTransform(1);
}

// 0x0052E140
int UIScene::CalcViewTransform(int nVal)
{
  long double v2; // st7
  float v3; // st6
  long double v4; // st7
  long double v5; // st6
  long double v6; // st5
  float v7; // st4
  float v8; // st3
  float v9; // st2
  float v10; // st3
  float v11; // st4
  float v12; // st3
  float v13; // st7
  float v14; // st6
  float v15; // st5
  int result; // eax
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
  unsigned int v27; // [esp+0x1C] [ebp-0x4]
  LONG v28; // [esp+0x1C] [ebp-0x4]
  int v29; // [esp+0x1C] [ebp-0x4]

  if ( *((_BYTE *)&this->m_hTexture + 8) )
  {
    v2 = (*(float *)&this->m_bVisible + *(float *)&this->m_bcreateok) * 0.017453292;
    v17 = (*(float *)&this->m_hFont + *(float *)&this->m_bvisible) * 0.01745329238474369f;
    v3 = *(float *)&this->m_bEnabled + *(float *)&this->m_benable;
  }
  else
  {
    v2 = *(float *)&this->m_bcreateok * 0.017453292;
    v17 = *(float *)&this->m_bvisible * 0.01745329238474369f;
    v3 = *(float *)&this->m_benable;
  }
  v18 = v3 * 0.01745329238474369f;
  v21 = cos(v2);
  v19 = cos(v17);
  v20 = cos(v18);
  v4 = sin(v2);
  v5 = sin(v17);
  v6 = sin(v18);
  *(float *)&this->m_nTodo_050 = v4 * v19;
  *(float *)&this->m_nScrollState = v5;
  *(float *)&this->m_nScrollIdx = -(v19 * v21);
  v7 = *(float *)&this->m_bfocus;
  v22 = v7 * *(float *)&this->m_nTodo_050;
  v23 = v7 * *(float *)&this->m_nScrollState;
  if ( nVal )
  {
    v8 = *(float *)&this->m_rect.left - v22;
    *(float *)&v24 = *(float *)&this->m_rect.top - v23;
    v9 = *(float *)&this->m_rect.right - v7 * *(float *)&this->m_nScrollIdx;
    this->m_wndcolor.Color = v24;
    *(float *)&v27 = v9;
    *(float *)&this->m_fontcolor.Color = v8;
    this->m_id = v27;
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
                 - *(float *)&this->m_childs.m_pData * *(float *)&this->m_nTodo_050;
  v14 = *(float *)&this->m_pfather * *(float *)&this->m_nTodo_050;
  v15 = *(float *)&this->m_nScrollState * *(float *)&this->m_rect.bottom;
  result = v26;
  this->m_pChildWnd = ((UIWnd *)((UIWnd *)v26));
  *(float *)&v29 = v14 - v15;
  *(float *)&this->m_nShowState = v13;
  this->m_nClipX = v29;
  return result;
}

// 0x00532D60
void UIScene::UpdateAlpha()
{
  char m_nClipY; // dl
  float v2; // st7
  float v4; // st7
  unsigned __int8 v5; // c0
  unsigned __int8 v6; // c3
  float v7; // st7
  float v8; // st7

  m_nClipY = this->m_nClipY;
  if ( BYTE1(this->m_nClipY) != m_nClipY )
  {
    switch ( m_nClipY )
    {
      case 0:
        v2 = *(float *)(*(_DWORD *)((UIWnd *)this) + 212);
        goto LABEL_7;
      case 1:
        v2 = *(float *)(*(_DWORD *)((UIWnd *)this) + 208);
        goto LABEL_7;
      case 2:
        v2 = *(float *)(*(_DWORD *)((UIWnd *)this) + 204);
        goto LABEL_7;
      case 3:
        v2 = *(float *)(*(_DWORD *)((UIWnd *)this) + 200);
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
  int result; // eax

  result = 0;
  *(_DWORD *)((UIWnd *)this) = 0;
  this->m_fontcolor.Color = 0;
  this->m_wndcolor.Color = 0;
  *(&this->m_hTexture + 4) = 0;
  this->m_fAngle = -96.27999877929688f;
  this->m_fCameraOffset = 0.0f;
  this->m_bFieldCC = ((Parent_Data *)((Parent_Data *)-982398730));
  this->m_nFieldD0 = LODWORD(this->m_fAngle);
  this->m_bVisible = ((Parent_Data *)((Parent_Data *)LODWORD(this->m_fCameraOffset)));
  this->m_hFont = (int)this->m_bFieldCC;
  this->m_nColors = 1065353216;
  this->m_bLoadState = 0;
  this->m_pChildData = ((char *)0);
  this->m_bEnabled = ((Parent_Data *)0);
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
  return result;
}

// 0x00535BA0
int UIScene::ResetCameraOffset()
{
  int result; // eax

  result = 0;
  this->m_fAngle = 80.0f;
  this->m_fCameraOffset = 0.0f;
  this->m_bFieldCC = ((Parent_Data *)((Parent_Data *)1141112832));
  this->m_nFieldD0 = LODWORD(this->m_fAngle);
  this->m_bVisible = ((Parent_Data *)((Parent_Data *)LODWORD(this->m_fCameraOffset)));
  this->m_hFont = (int)this->m_bFieldCC;
  this->m_nColors = 1065353216;
  this->m_bLoadState = 0;
  this->m_pChildData = ((char *)0);
  this->m_bEnabled = ((Parent_Data *)0);
  *((_BYTE *)&this->m_hTexture + 8) = 0;
  *((_BYTE *)&this->m_hTexture + 9) = 0;
  *((_BYTE *)&this->m_hTexture + 10) = 0;
  *((_BYTE *)&this->m_hTexture + 11) = 0;
  *((_BYTE *)&this->m_hTexture + 12) = 0;
  *((_BYTE *)&this->m_hTexture + 13) = 0;
  return result;
}
