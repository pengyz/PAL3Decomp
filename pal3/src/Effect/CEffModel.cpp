#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffModel.h"

// Forward declarations for unnamed functions
int sub_4CFD00(...);
int sub_4D0850(...);
void __cdecl todo_401800(void);

// Unnamed globals (extern)
extern int dword_17A7B58;
extern int dword_17A7B5C;
extern int dword_17A7B60;
extern int dword_17A7B68;
extern int dword_17A7B6C;
extern int dword_17A7B70;
extern int dword_17A7B78;
extern int dword_17A7B7C;
extern int dword_17A7B80;
extern int dword_5D4DAC;
extern int dword_5D4DB8;
extern int dword_5D4DC4;
extern int dword_5D4DCC;
extern int dword_5D4DD4;
extern int dword_5D4E24;
extern int dword_5D4E30;
extern int dword_5D4E38;
extern int dword_5D4E40;
extern int dword_5D4FF0;
extern int dword_5D5038;
extern int dword_5D5040;
extern int dword_5D5048;
extern int dword_5D5050;
extern int dword_5D51B0;
void __cdecl nullsub_86(void);
void __cdecl nullsub_87(void);
void __cdecl nullsub_88(void);

// 0x004CEC80
int CEffModel::CreateInstance(CEffModel *pSrc, int nVal, CEffModel *pParam)
{
  int v4; // ebp
  _BYTE *i; // eax
  char *v7; // ebx
  const char *v8; // edi
  CEffModel *v9; // eax
  int *v10; // eax

  v4 = 0;
  for ( i = &this->m_bVisible; *i; i += 72 )
  {
    if ( ++v4 >= 32 )
      return -1;
  }
  v7 = (char *)this + 72 * v4;
  strcpy(v7 + 28, (const char *)pSrc);
  v8 = (const char *)pParam;
  if ( !pParam )
    v8 = g_szSceneUIText;
  strcpy(v7 + 58, v8);
  v7[88] = 1;
  v9 = (CEffModel *)operator new(0x10B0u);
  if ( v9 )
    v10 = ((CEffModel *)v9)->Reset();
  else
    v10 = 0;
  *((_DWORD *)v7 + 24) = v10;
  if ( (g_bEffSystemFlags & 1) == 0 )
  {
    g_bEffSystemFlags |= 1u;
    ((CEffMgr *)&g_pCEffMgrBackup)->Reset();
    atexit(todo_401800);
  }
  *((_DWORD *)v7 + 23) = ((CEffSParticle *)&g_pCEffMgrBackup)->GetEditorTaskDescription((int)pSrc);
  return v4;
}

// 0x004CFC70
CEffModel::CEffModel()
{
  this->m_pEM = 0;
  this->m_bIdle = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 1) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 2) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 3) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 4) = -1;
// [VFTABLE] *((_DWORD *)&this->__vftable + 5) = -1;
// [VFTABLE] *((_DWORD *)&this->__vftable + 6) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 7) = 0;
  this->m_pGeomNode = 0;
  *((_DWORD *)&this->m_pGeomNode + 1) = 0;
  *((_DWORD *)&this->m_pGeomNode + 2) = 0;
  *((_DWORD *)&this->m_pGeomNode + 3) = 0;
  this->m_vecOffsetPos.x = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  this->m_vecOffsetPos.z = 0.0;
  this->m_vecRot.x = 0.0;
  this->m_vecRot.y = 0.0;
  this->m_vecRot.z = 0.0;
  this->m_pGeomNode = 0;
  *((_DWORD *)&this->m_pGeomNode + 3) = 0;
  *((_DWORD *)&this->m_pGeomNode + 2) = 0;
  *((_DWORD *)&this->m_pGeomNode + 1) = 0;
  this->m_vecOffsetPos.z = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  this->m_vecOffsetPos.x = 0.0;
  this->m_vecRot.z = 0.0;
  this->m_vecRot.y = 0.0;
  this->m_vecRot.x = 0.0;
  this->m_bVisible = 0;
  this->m_bAdditiveBlend = 0;
  this->m_bNoZTest = 0;
  this->m_fSizeX = 1.0;
  this->m_fSizeY = 1.0;
  this->m_fSizeZ = 1.0;
  this;
}

// 0x004CFD00
int CEffModel::sub_4CFD00()
{
  CEffModel *v0; // eax

  v0 = (CEffModel *)operator new(0x68u);
  if ( v0 )
    return ((CEffModel *)v0); // ctor auto-called
  else
    return 0;
}

// 0x004CFEB0
bool CEffModel::LoadFromNode(int nVal)
{
  void *v3; // eax
  int v4; // ebp
  int v5; // edi
  int v6; // edi
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v11; // ebx
  int v12; // edi

  v3 = operator new(0x4C0u);
// [VFTABLE] *((_DWORD *)&this->__vftable + 3) = v3;
  if ( v3 )
  {
    v4 = 0;
    v5 = 0;
    while ( 1 )
    {
// [VFTABLE] *(_DWORD *)(*((_DWORD *)&this->__vftable + 3) + v5) = operator new(0x2D0u);
// [VFTABLE] if ( !*(_DWORD *)(*((_DWORD *)&this->__vftable + 3) + v5) )
        break;
      v5 += 152;
      ++v4;
      if ( v5 >= 1216 )
      {
        v6 = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 7) = 8;
        this->m_pGeomNode = (gbGeomNode *)10;
        v7 = 0;
        do
        {
// [VFTABLE] *(_BYTE *)(*((_DWORD *)&this->__vftable + 3) + v7 + 148) = 0;
          v8 = 0;
          if ( (int)this->m_pGeomNode > 0 )
          {
            v9 = 0;
            do
            {
              ++v8;
              v9 += 72;
// [VFTABLE] *(_BYTE *)(v9 + *(_DWORD *)(v7 + *((_DWORD *)&this->__vftable + 3)) - 8) = 0;
            }
            while ( v8 < (int)this->m_pGeomNode );
          }
          ++v6;
          v7 += 152;
        }
// [VFTABLE] while ( v6 < *((_DWORD *)&this->__vftable + 7) );
        return ((GeomNode *)this)->LoadFromNode((const gbGeomNode *)(nVal + 40));
      }
    }
    if ( v4 > 0 && v4 - 1 >= 0 )
    {
      v11 = v4;
      v12 = 152 * (v4 - 1);
      do
      {
// [VFTABLE] operator delete(*(void **)(*((_DWORD *)&this->__vftable + 3) + v12));
        v12 -= 152;
        --v11;
      }
      while ( v11 );
    }
// [VFTABLE] operator delete(*(&this->__vftable + 3));
  }
  return ((GeomNode *)this)->LoadFromNode((const gbGeomNode *)(nVal + 40));
}

// 0x004CFFA0
// attributes: thunk
void CEffModel::DestroyEffect()
{
  ((CEffgbParticle *)this)->DestroyEffect();
}

// 0x004D01C0
void CEffModel::RenderScenePass()
{
  gbMatrixStack *v2; // edi
  double v3; // st7
  double v4; // st7
  gbGeomNode *m_pGeomNode; // esi
  float v6; // [esp+0x4] [ebp-0x18]
  float v7; // [esp+0x8] [ebp-0x14]
  float v8; // [esp+0xC] [ebp-0x10]
  struct gbVec3D v9; // [esp+0x10] [ebp-0xC] BYREF

  if ( (g_bgbMatrixStackFlag_17A7B84 & 1) == 0 )
  {
    dword_17A7B78 = 1065353216;
    g_bgbMatrixStackFlag_17A7B84 |= 1u;
    dword_17A7B7C = 0;
    dword_17A7B80 = 0;
    atexit(nullsub_88);
  }
  if ( (g_bgbMatrixStackFlag_17A7B84 & 2) == 0 )
  {
    dword_17A7B68 = 0;
    g_bgbMatrixStackFlag_17A7B84 |= 2u;
    dword_17A7B6C = 1065353216;
    dword_17A7B70 = 0;
    atexit(nullsub_87);
  }
  if ( (g_bgbMatrixStackFlag_17A7B84 & 4) == 0 )
  {
    dword_17A7B58 = 0;
    g_bgbMatrixStackFlag_17A7B84 |= 4u;
    dword_17A7B5C = 0;
    dword_17A7B60 = 1065353216;
    atexit(nullsub_86);
  }
  if ( !this->m_bIdle && this->m_bVisible )
  {
    v2 = this->m_pEM->m_pDisplay->pMatrixStack[1];
    ((gbMatrixStack *)v2)->Push();
    v6 = this->m_vecOffsetPos.x + *((float *)&this->m_pGeomNode + 1);
    v3 = this->m_vecOffsetPos.y + *((float *)&this->m_pGeomNode + 2);
    v9.x = v6;
    v7 = v3;
    v4 = this->m_vecOffsetPos.z + *((float *)&this->m_pGeomNode + 3);
    v9.y = v7;
    v8 = v4;
    v9.z = v8;
    ((gbMatrixStack *)v2)->Translate(v9);
    ((gbMatrixStack *)v2)->Rotate(this->m_vecRot.x, (gbVec3D *)&dword_17A7B78);
    ((gbMatrixStack *)v2)->Rotate(this->m_vecRot.y, (gbVec3D *)&dword_17A7B68);
    ((gbMatrixStack *)v2)->Rotate(this->m_vecRot.z, (gbVec3D *)&dword_17A7B58);
    ((gbMatrixStack *)v2)->Scale(this->m_fSizeX,   this->m_fSizeY,   this->m_fSizeZ);
    m_pGeomNode = this->m_pGeomNode;
    if ( m_pGeomNode )
      (*(void ( **)(gbGeomNode *, _DWORD))(*(_DWORD *)m_pGeomNode + 16))(m_pGeomNode, 0);
    ((gbMatrixStack *)v2)->Pop();
  }
}

// 0x004D0390
void CEffModel::GetRenderNode()
{
  gbGeomNode *m_pGeomNode; // ecx
  float v2; // [esp+0x4] [ebp+0x4]

  m_pGeomNode = this->m_pGeomNode;
  if ( m_pGeomNode )
    ((gbVisNode *)m_pGeomNode)->SetTimeScale(v2);
}

// 0x004D03B0
void CEffModel::RenderModel()
{
  CTaskTpl_tagEffTaskParam_CEffModel *p_vftable; // ebx
  int v2; // ecx
  int v3; // edx
  int v4; // esi
  _BYTE *i; // eax
  int v6; // ebp
  unsigned int v7; // eax
  int m_pGeomNode; // ecx
  int v9; // eax
  int v10; // edi
  _BYTE *v11; // esi
  int ( **v12)(CEffect *, int); // esi
  unsigned int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // edi
  _BYTE *v17; // esi
  int ( **v18)(CEffect *, int); // esi
  unsigned int v19; // eax
  const void *v20; // [esp+0x18] [ebp+0x4]

// [VFTABLE] p_vftable = (CTaskTpl_tagEffTaskParam_CEffModel *)&this->__vftable;
// [VFTABLE] v2 = *((_DWORD *)&this->__vftable + 7);
  v3 = 0;
  if ( v2 > 0 )
  {
// [VFTABLE] v4 = *((_DWORD *)&p_vftable->__vftable + 3);
    for ( i = (_BYTE *)(v4 + 148); *i; i += 152 )
    {
      if ( ++v3 >= v2 )
        return;
    }
    v6 = 152 * v3;
    *(_DWORD *)(v4 + v6 + 12) = 2;
// [VFTABLE] *(_BYTE *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 148) = 1;
// [VFTABLE] *(_BYTE *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 149) = 1;
    v7 = ++g_nEffectUID;
    if ( !g_nEffectUID || v7 >= 0x7FFFFFFF )
    {
      v7 = 1;
      g_nEffectUID = 1;
    }
// [VFTABLE] *(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 16) = v7;
// [VFTABLE] *(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 4) = 0;
// [VFTABLE] *(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 8) = 0;
// [VFTABLE] *(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 20) = 0;
    if ( v20 )
// [VFTABLE] qmemcpy((void *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 24), v20, 0x7Cu);
    else
// [VFTABLE] memset((void *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 24), 0, 0x7Cu);
// [VFTABLE] ++*((_DWORD *)&p_vftable->__vftable + 6);
    if ( v3 != -1 )
    {
      m_pGeomNode = (int)p_vftable->m_pGeomNode;
      v9 = 0;
      if ( m_pGeomNode > 0 )
      {
// [VFTABLE] v10 = *(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + 152 * v3);
        v11 = (_BYTE *)(v10 + 64);
        while ( *v11 )
        {
          ++v9;
          v11 += 72;
          if ( v9 >= m_pGeomNode )
            goto LABEL_22;
        }
        v12 = (int ( **)(CEffect *, int))(v10 + 72 * v9);
        memset(v12, 0, 0x48u);
        *v12 = CEffect::SetParam;
        *((_BYTE *)v12 + 64) = 1;
        *((_BYTE *)v12 + 65) = 0;
        v12[1] = 0;
        v12[2] = (int ( *)(CEffect *, int))2;
        v13 = ++g_nEffectUID;
        if ( !g_nEffectUID || v13 >= 0x7FFFFFFF )
        {
          v13 = 1;
          g_nEffectUID = 1;
        }
        v12[3] = (int ( *)(CEffect *, int))v13;
        v12[5] = 0;
        v12[4] = 0;
        v12[6] = 0;
// [VFTABLE] ++*(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 4);
      }
LABEL_22:
      v14 = (int)p_vftable->m_pGeomNode;
      v15 = 0;
      if ( v14 > 0 )
      {
// [VFTABLE] v16 = *(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + 152 * v3);
        v17 = (_BYTE *)(v16 + 64);
        while ( *v17 )
        {
          ++v15;
          v17 += 72;
          if ( v15 >= v14 )
            goto LABEL_31;
        }
        v18 = (int ( **)(CEffect *, int))(v16 + 72 * v15);
        memset(v18, 0, 0x48u);
        *v18 = CEffect::SetParam;
        *((_BYTE *)v18 + 64) = 1;
        *((_BYTE *)v18 + 65) = 0;
        v18[1] = 0;
        v18[2] = (int ( *)(CEffect *, int))2;
        v19 = ++g_nEffectUID;
        if ( !g_nEffectUID || v19 >= 0x7FFFFFFF )
        {
          v19 = 1;
          g_nEffectUID = 1;
        }
        v18[3] = (int ( *)(CEffect *, int))v19;
        v18[5] = 0;
        v18[4] = 0;
        v18[6] = 0;
// [VFTABLE] ++*(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 4);
      }
LABEL_31:
      ((GeomNode *)p_vftable)->DestroyChildren();
// [VFTABLE] *(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6 + 12) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6) + 8) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)(*((_DWORD *)&p_vftable->__vftable + 3) + v6) + 16) = *((_DWORD *)&p_vftable->__vftable + 1);
    }
  }
}

// 0x004D0850
int CEffModel::sub_4D0850(int nVal)
{
  int result; // eax

  switch ( nVal )
  {
    case 0:
      result = (int)dword_5D5050;
      break;
    case 1:
      result = (int)dword_5D4E40;
      break;
    case 2:
      result = (int)dword_5D4E38;
      break;
    case 3:
      result = (int)dword_5D4E30;
      break;
    case 4:
      result = (int)dword_5D4E24;
      break;
    case 5:
      result = (int)dword_5D5048;
      break;
    case 6:
      result = (int)dword_5D5040;
      break;
    case 7:
      result = (int)dword_5D5038;
      break;
    case 9:
      result = (int)&g_EffEditorState;
      break;
    case 10:
      result = (int)dword_5D51B0;
      break;
    case 12:
      result = (int)dword_5D4DD4;
      break;
    case 13:
      result = (int)dword_5D4DCC;
      break;
    case 14:
      result = (int)dword_5D4DC4;
      break;
    case 15:
      result = (int)dword_5D4DB8;
      break;
    case 16:
      result = (int)dword_5D4DAC;
      break;
    case 20:
      result = (int)&g_pszEditorDesc;
      break;
    case 21:
      result = (int)dword_5D4FF0;
      break;
    default:
      result = (int)&g_EffCylinderEditorData;
      break;
  }
  return result;
}

// 0x004D0BD0
void CEffModel::UpdateDuration()
{
  int v2; // eax
  int v3; // ebx
  int v4; // edi
  char v5; // [esp+0x8] [ebp+0x4]

// [VFTABLE] v2 = *((_DWORD *)&this->__vftable + 4);
// [VFTABLE] if ( v2 || *((_DWORD *)&this->__vftable + 5) )
  {
    v3 = 0;
    if ( v2 > 0 )
    {
      v4 = 0;
      do
      {
// [VFTABLE] operator delete(*(void **)((char *)this->__vftable + v4));
        ++v3;
// [VFTABLE] *(_DWORD *)((char *)this->__vftable + v4) = 0;
        v4 += 152;
      }
// [VFTABLE] while ( v3 < *((_DWORD *)&this->__vftable + 4) );
    }
// [VFTABLE] operator delete(this->__vftable);
// [VFTABLE] this->__vftable = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 4) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 5) = 0;
  }
  if ( (v5 & 1) != 0 )
    operator delete(this);
}

// 0x004D0CE0
int * CEffModel::Reset()
{
  this->m_pEM = 0;
  this->m_bIdle = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 1) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 2) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 3) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 4) = -1;
// [VFTABLE] *((_DWORD *)&this->__vftable + 5) = -1;
// [VFTABLE] *((_DWORD *)&this->__vftable + 6) = 0;
// [VFTABLE] *((_DWORD *)&this->__vftable + 7) = 0;
  this->m_pGeomNode = 0;
  this->m_vecOffsetPos.z = NAN;
  LOBYTE(this->m_pGeomNode) = 0;
  BYTE1(this->m_pGeomNode) = 0;
  BYTE2(this->m_pGeomNode) = 0;
  HIBYTE(this->m_pGeomNode) = 0;
  *((_BYTE *)&this->m_pGeomNode + 6) = 0;
  *((_BYTE *)&this->m_pGeomNode + 4) = 0;
  *((_BYTE *)&this->m_pGeomNode + 5) = 0;
  *((_DWORD *)&this->m_pGeomNode + 2) = 0;
  *((_DWORD *)&this->m_pGeomNode + 3) = 0;
  this->m_vecOffsetPos.x = 0.0;
  this->m_vecOffsetPos.y = 0.0;
  *((_DWORD *)this + 39) = 0;
  *((_DWORD *)this + 40) = 0;
  *((_DWORD *)this + 41) = 0;
  *((_DWORD *)this + 1066) = 0;
  *((_DWORD *)this + 1067) = 0;
  memset((char *)this + 168, 0, 0x1000u);
  return (int *)this;
}
