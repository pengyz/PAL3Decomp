#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UINote.h"

// Forward declarations for unnamed functions
int sub_445ED0(int a2, int a3); // from annotations
int sub_445F60(unsigned int a2); // from annotations

// 0x004450A0
void * UINote::Create(int id, int nVal, int nVal2, char *tex)
{
  int v6; // esi
  void *result; // eax
  OpenBaseFile v8; // [esp+0x10] [ebp-0x110] BYREF
  char Buffer[256]; // [esp+0x14] [ebp-0x10C] BYREF
  int v10; // [esp+0x11C] [ebp-0x4]

  ((PalScript *)this)->Create(id, (tagRECT *)nVal, nVal2);
  v6 = 0;
  v10 = 0;
  do
  {
    sprintf(Buffer, "%s%d.tga", tex, v6);
    sub_445ED0((int)Buffer, 1);
    ++v6;
  }
  while ( v6 < 9 );
  this->m_static.m_texs.m_ptex[7] = *(gbTexture **)(sub_445F60(0) + 24);
  this->m_static.m_texs.m_ptex[4] = 0;
  this->m_bvisible = 0;
  v10 = -1;
  return result;
}

// 0x004B7F00
void UINote::ReleaseResources()
{
  void ( ***v2)(_DWORD, int); // ecx
  gbRefObject *v3; // ecx
  gbRefObject *v4; // ecx
  gbRefObject *right; // ecx

  v2 = (void ( ***)(_DWORD, int))*((_DWORD *)this + 264);
  if ( v2 )
  {
    (**v2)(v2, 1);
    *((_DWORD *)this + 264) = 0;
  }
  v3 = (gbRefObject *)this->m_static.m_texs.m_ptex[3];
  if ( v3 )
  {
    ((gbRefObject *)v3)->Release();
    this->m_static.m_texs.m_ptex[3] = 0;
  }
  v4 = (gbRefObject *)this->m_static.m_texs.m_ptex[2];
  if ( v4 )
  {
    ((gbRefObject *)v4)->Release();
    this->m_static.m_texs.m_ptex[2] = 0;
  }
  right = (gbRefObject *)this->m_static.m_rect.right;
  if ( right )
  {
    ((gbRefObject *)right)->Release();
    this->m_static.m_rect.right = 0;
  }
  this->m_static.m_texs.m_ptex[1] = 0;
}

// 0x00528D30
int UINote::GetEntryPtr(int nIndex)
{
  return (int)this + 256 * nIndex + 3424;
}

// 0x0052AFC0
int UINote::RenderIfVisible(gbMatrixStack *pMatrixStack)
{
  int result; // eax

  result = *(&this->m_static.m_openstyle + 4);
  if ( result )
  {
    this->RenderWithStack(pMatrixStack);
    return (*(int ( **)(_DWORD, _DWORD))(**((_DWORD **)&this->m_static.m_openstyle + 4) + 16))(
             *(&this->m_static.m_openstyle + 4),
             0);
  }
  return result;
}

// 0x0052AFF0
void UINote::RenderWithStack(gbMatrixStack *pStack)
{
  ((gbMatrixStack *)pStack)->Push();
  ((gbMatrixStack *)pStack)->Translate((gbVec3D *)(this + 1));
  (*(void ( **)(_DWORD, _DWORD))(*(_DWORD *)LODWORD(this->time) + 16))(LODWORD(this->time), 0);
  ((gbMatrixStack *)pStack)->Pop();
}

// 0x0052B030
int UINote::CallVtableMethod(double pData)
{
  float v3; // [esp+0x0] [ebp-0x4]

  v3 = pData;
  return (*(int ( **)(_DWORD))(*(_DWORD *)LODWORD(this->time) + 48))(LODWORD(v3));
}
