#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/UI3DCtrl.h"

// Forward declarations for unnamed functions
int sub_445AA0(void); // from annotations

// 0x0043D830
int * UI3DCtrl::ctor_D830()
{
  sub_445AA0();
  this->m_obj[0].m_needdel = 0;
  this->m_obj[0].m_enable = 0;
  this->m_numobj = 32;
  *(_DWORD *)&this->m_obj[0].m_mouseoff = 32;
  return (int *)this;
}

// 0x0043D880
void UI3DCtrl::ctor()
{
// [VFTABLE] ((UIWnd *)&this->__vftable)->_UIWnd();
}

// 0x0043D890
gbVFileSystem * UI3DCtrl::CreateWithTexture(
        
        int id,
        void *pRect,
        int nVal,
        unsigned int dwVal,
        int parent)
{
  gbTexture *v7; // eax
  gbVFileSystem *result; // eax

  ((PalScript *)this)->Create(id, (tagRECT *)pRect, parent);
  v7 = (gbTexture *)(*(int ( **)(gbGfxManager *, int))(*(_DWORD *)gfxMgr + 8))(gfxMgr, nVal);
  this->m_obj[0].m_enable = (int)v7;
  if ( v7 )
    ((gbTexture *)v7)->LoadTexture(1);
  this->m_obj[0].m_needdel = dwVal;
  return result;
}

// 0x0043D940
void UI3DCtrl::Render()
{
  int m_needdel; // eax
  tagRECT *p_m_rect; // ebx
  int v4; // eax
  LONG i; // edi
  int left; // edx
  LONG v7; // ecx
  LONG bottom; // ebx
  int v9; // edx
  tagRECT *v10; // ebx
  int v11; // edx
  int m_numobj; // eax
  int j; // edi
  int v14; // edx
  LONG v15; // ecx
  LONG v16; // eax
  int v17; // edx
  int pnVal; // [esp+0xC] [ebp-0x10] BYREF
  LONG top; // [esp+0x10] [ebp-0xC]
  LONG right; // [esp+0x14] [ebp-0x8]
  LONG v21; // [esp+0x18] [ebp-0x4]

  if ( this->m_bvisible )
  {
    m_needdel = this->m_obj[0].m_needdel;
    if ( m_needdel )
    {
      if ( m_needdel == 1 )
      {
        p_m_rect = &this->m_rect;
        pnVal = this->m_rect.left;
        top = this->m_rect.top;
        right = this->m_rect.right;
        v21 = top + *(_DWORD *)&this->m_obj[0].m_mouseoff;
        ((UIStatic *)this)->RenderQuadSlice(&pnVal, 2);
        v4 = *(_DWORD *)&this->m_obj[0].m_mouseoff;
        for ( i = v4 + this->m_rect.top; i < this->m_rect.bottom - v4; i += v4 )
        {
          top = i;
          v21 = i + v4;
          ((UIStatic *)this)->RenderQuadSlice(&pnVal, 1);
          v4 = *(_DWORD *)&this->m_obj[0].m_mouseoff;
        }
        left = p_m_rect->left;
        v7 = this->m_rect.right;
        bottom = this->m_rect.bottom;
        pnVal = left;
        v9 = *(_DWORD *)&this->m_obj[0].m_mouseoff;
        v21 = bottom;
        right = v7;
        top = bottom - v9;
        ((UIStatic *)this)->RenderQuadSlice(&pnVal, 0);
      }
    }
    else
    {
      v10 = &this->m_rect;
      pnVal = this->m_rect.left;
      top = this->m_rect.top;
      right = this->m_rect.right;
      v11 = pnVal + this->m_numobj;
      v21 = this->m_rect.bottom;
      right = v11;
      ((UIStatic *)this)->RenderQuadSlice(&pnVal, 0);
      m_numobj = this->m_numobj;
      for ( j = m_numobj + v10->left; j < this->m_rect.right - m_numobj; j += m_numobj )
      {
        pnVal = j;
        right = j + m_numobj;
        ((UIStatic *)this)->RenderQuadSlice(&pnVal, 1);
        m_numobj = this->m_numobj;
      }
      v14 = v10->left;
      v15 = this->m_rect.bottom;
      top = this->m_rect.top;
      v16 = this->m_rect.right;
      pnVal = v14;
      v17 = this->m_numobj;
      right = v16;
      v21 = v15;
      pnVal = v16 - v17;
      ((UIStatic *)this)->RenderQuadSlice(&pnVal, 2);
    }
  }
}

// 0x0052AF20
char UI3DCtrl::LoadModel(const char *pszModelName)
{
  UI3DModelNode *v3; // eax
  float v4; // eax
  const char *v6; // [esp+0x0] [ebp-0x10]

  this->LoadEncampModel(pszModelName, v6);
  v3 = (UI3DModelNode *)operator new(0xF8u);
  if ( v3 )
  {
  }
  else
    v4 = 0.0;
  this->m_dropx = v4;
  (*(void ( **)(float, int))(*(_DWORD *)LODWORD(v4) + 40))(COERCE_FLOAT(LODWORD(v4)), 3);
  this->m_dropy = -2.5999999;
  this->m_dropz = 7.8000002;
  this->m_scalex = -237.0;
  return 1;
}

// 0x0052B050
char UI3DCtrl::LoadEncampModel(const char *pszModelName, const char *pszName)
{
  gbGeomNode *v5; // eax
  gbGeomNode *v6; // esi
  gbGeomNode *v7; // ecx
  int v8; // eax
  OpenBaseFile v9; // [esp+0xC] [ebp-0x814] BYREF
  gbGeomNode *v10; // [esp+0x10] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x14] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x414] [ebp-0x40C] BYREF
  int v13; // [esp+0x81C] [ebp-0x4]

  if ( !pszModelName )
    return 0;
  v13 = 0;
  sprintf((char *const)this, "SubGame\\Encampment\\Encamp_Scene\\%s.pol", pszModelName);
  v5 = (gbGeomNode *)operator new(0x118u);
  v6 = v5;
  v10 = v5;
  LOBYTE(v13) = 1;
  if ( v5 )
  {
    v7 = v6;
  }
  else
  {
    v7 = 0;
  }
  LOBYTE(v13) = 0;
  LODWORD(this->m_rotx) = v7;
  if ( !v7 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], "D:\\Project\\PAL3\\subgame\\Encampment\\Encampment_scene.cpp", 115),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v8 = ((gbGeomNode *)v7)->LoadFromFile((const char *)this, 0, 0);
  v13 = -1;
  if ( v8 )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// 0x0052E8C0
double UI3DCtrl::UpdateRotation()
{
  double v1; // st7
  double v3; // st7

  if ( BYTE1(this->m_lightobj) )
  {
    v1 = this->m_dropx + this->m_dropy;
    this->m_dropy = v1;
    if ( *(float *)&this->m_speed <= fabs(v1) )
    {
      this->m_dropy = 0.0;
      BYTE1(this->m_lightobj) = 0;
      return this->m_dropy;
    }
  }
  else
  {
    v3 = this->m_dropy - this->m_dropx;
    this->m_dropy = v3;
    if ( *(float *)&this->m_speed >= fabs(v3) )
    {
      this->m_dropy = 0.0;
      BYTE1(this->m_lightobj) = 1;
    }
  }
  return this->m_dropy;
}

// 0x0052E940
double UI3DCtrl::UpdateOscillation()
{
  double v1; // st7
  double v3; // st7

  if ( BYTE2(this->m_lightobj) )
  {
    v1 = this->m_dropx + this->m_dropz;
    this->m_dropz = v1;
    if ( this->m_rotate <= fabs(v1) )
    {
      this->m_dropz = 0.0;
      BYTE2(this->m_lightobj) = 0;
      return this->m_dropz;
    }
  }
  else
  {
    v3 = this->m_dropz - this->m_dropx;
    this->m_dropz = v3;
    if ( this->m_rotate >= fabs(v3) )
    {
      this->m_dropz = 0.0;
      BYTE2(this->m_lightobj) = 1;
    }
  }
  return this->m_dropz;
}

// 0x0052E9C0
double UI3DCtrl::UpdateOscillationX()
{
  double v1; // st7
  double v3; // st7

  if ( HIBYTE(this->m_lightobj) )
  {
    v1 = this->m_dropx + this->m_scalex;
    this->m_scalex = v1;
    if ( this->m_rotatetarget <= fabs(v1) )
    {
      this->m_scalex = 0.0;
      HIBYTE(this->m_lightobj) = 0;
      return this->m_scalex;
    }
  }
  else
  {
    v3 = this->m_scalex - this->m_dropx;
    this->m_scalex = v3;
    if ( this->m_rotatetarget >= fabs(v3) )
    {
      this->m_scalex = 0.0;
      HIBYTE(this->m_lightobj) = 1;
    }
  }
  return this->m_scalex;
}

// 0x0052EA40
double UI3DCtrl::UpdateOscillationY()
{
  double v1; // st7
  double v3; // st7

  if ( LOBYTE(this->m_camera) )
  {
    v1 = this->m_dropx + this->m_scaley;
    this->m_scaley = v1;
    if ( this->m_rotx <= fabs(v1) )
    {
      this->m_scaley = 0.0;
      LOBYTE(this->m_camera) = 0;
      return this->m_scaley;
    }
  }
  else
  {
    v3 = this->m_scaley - this->m_dropx;
    this->m_scaley = v3;
    if ( this->m_rotx >= fabs(v3) )
    {
      this->m_scaley = 0.0;
      LOBYTE(this->m_camera) = 1;
    }
  }
  return this->m_scaley;
}

// 0x0052EAC0
char UI3DCtrl::UpdateTransform(int nVal)
{
  char result; // al
  double updated; // st7
  char m_lightobj; // al
  double v6; // st7
  char v7; // al
  double v8; // st7
  char v9; // al
  float m_scalez; // ebp
  float v11; // eax
  float v12; // eax
  unsigned int v13; // ecx

  result = this->m_isrotateto;
  if ( result )
  {
    if ( LOBYTE(this->m_rotz) )
    {
      updated = this->UpdateRotation();
      m_lightobj = (char)this->m_lightobj;
      *(float *)&this->m_fontcolor.Color = updated + *(float *)&this->m_fontcolor.Color;
      if ( m_lightobj )
        *(float *)&this->m_rect.left = this->UpdateRotation() + *(float *)&this->m_rect.left;
    }
    if ( BYTE1(this->m_rotz) )
    {
      v6 = this->UpdateOscillation();
      v7 = (char)this->m_lightobj;
      *(float *)&this->m_wndcolor.Color = v6 + *(float *)&this->m_wndcolor.Color;
      if ( v7 )
        *(float *)&this->m_rect.top = this->UpdateOscillation() + *(float *)&this->m_rect.top;
    }
    if ( BYTE2(this->m_rotz) )
    {
      v8 = this->UpdateOscillationX();
      v9 = (char)this->m_lightobj;
      *(float *)&this->m_id = v8 + *(float *)&this->m_id;
      if ( v9 )
        *(float *)&this->m_rect.right = this->UpdateOscillationX() + *(float *)&this->m_rect.right;
    }
    if ( HIBYTE(this->m_rotz) )
      *(float *)&this->m_bfocus = this->UpdateOscillationY() + *(float *)&this->m_bfocus;
    m_scalez = this->m_scalez;
    if ( !LOBYTE(this->m_rotatemode) )
    {
      v11 = COERCE_FLOAT(GetTickCount());
      this->m_obj[4].m_pos.z = v11;
      this->m_orthosize = v11;
      LOBYTE(this->m_rotatemode) = 1;
    }
    v12 = COERCE_FLOAT(GetTickCount());
    v13 = LODWORD(v12) - LODWORD(this->m_orthosize);
    this->m_obj[4].m_pos.z = v12;
    if ( v13 > LODWORD(m_scalez) )
    {
      this->m_orthosize = v12;
      LOBYTE(this->m_rotatemode) = 0;
      this->m_isrotateto = 0;
      this->m_dropx = 1.0;
    }
    return ((UIScene *)this)->CalcViewTransform(1);
  }
  return result;
}
