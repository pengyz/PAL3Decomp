#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/GeomNode.h"

// Forward declarations for unnamed functions
int sub_4B70C0(...);
int sub_4B7220(...);

gbActorMgr * GetActorMgr(void); // from annotations

// 0x00429AF0
void GeomNode::InitFromFile(const gbGeomNode *pGeomNode, int nVal)
{
  unsigned int v4; // ecx
  const char *v5; // edi
  GeomNode *pNext; // eax
  GeomNode *v7; // eax
  GeomNode *v8; // eax
  GeomNode *v9; // edi
  GeomNode *v10; // ecx
  int v11; // [esp-0x4] [ebp-0x124]
  char String[260]; // [esp+0x10] [ebp-0x110] BYREF
  int v13; // [esp+0x11C] [ebp-0x4]

  GetActorMgr();
  v4 = strlen((const char *)pGeomNode);
  if ( *((_DWORD *)pGeomNode) == 43 )
  {
    this->pNext = (GeomNode *)4;
  }
  else
  {
    v5 = (char *)pGeomNode + v4 - 4;
    if ( _strcmpi(v5, ".cvd") )
    {
      if ( !_strcmpi(v5, ".pol") )
        this->pNext = (GeomNode *)2;
    }
    else
    {
      this->pNext = (GeomNode *)3;
    }
  }
  pNext = this->pNext;
  if ( (int)this->pNext >= 2 )
  {
    if ( (int)pNext <= 3 )
    {
      v8 = (GeomNode *)operator new(0x118u);
      v9 = v8;
      v13 = 0;
      if ( v8 )
      {
        v10 = v9;
      }
      else
      {
        v10 = 0;
      }
      v13 = -1;
      this->pParent = v10;
      if ( !((gbGeomNode *)v10)->LoadFromFile((const char *)pGeomNode, 0, 0) )
        this->pNext = 0;
      (*(void ( **)(GeomNode *, _DWORD))&this->pParent->pNext->children[16])(this->pParent, 0);
      ((gbVisNode *)this->pParent)->SetTimeScale(0.0);
      (*(void ( **)(GeomNode *))&this->pParent->pNext->children[12])(this->pParent);
      ((gbGeomNode *)this->pParent)->GetTotalOBBox((gbOBBox *)this->children);
      (*(void ( **)(GeomNode *, _DWORD))&this->pParent->pNext->children[16])(this->pParent, 0);
      ((gbVisNode *)this->pParent)->SetTimeScale(1.0);
    }
    else if ( pNext == (GeomNode *)4 )
    {
      strcpy(g_ScriptSystemData.m_String, (const char *)pGeomNode);
      g_ScriptSystemData.m_String[0] = 48;
      v11 = atoi(g_ScriptSystemData.m_String);
      sub_4B7220();
      v7 = (GeomNode *)sub_4B70C0(v11);
      this->pParent = v7;
      if ( v7 )
        (*(void ( **)(GeomNode *, int))&v7->pNext->children[32])(v7, nVal);
      else
        this->pNext = 0;
    }
  }
}

// 0x004D0950
bool GeomNode::LoadFromNode(const gbGeomNode *pNode)
{
  gbGeomNode *v3; // eax
  gbGeomNode *v4; // esi
  gbGeomNode *v5; // ecx
  int v6; // esi
  bool v7; // zf
  void ( ***v8)(_DWORD, int); // ecx
  bool v9; // bl
  OpenBaseFile v11; // [esp+0x10] [ebp-0x814] BYREF
  gbGeomNode *v12; // [esp+0x14] [ebp-0x810]
  char pExceptionObject[1024]; // [esp+0x18] [ebp-0x80C] BYREF
  char ArgList; // [esp+0x418] [ebp-0x40C] BYREF
  int v15; // [esp+0x820] [ebp-0x4]

  ((CEffgbParticle *)this)->DestroyEffect();
  v15 = 0;
  v3 = (gbGeomNode *)operator new(0x118u);
  v4 = v3;
  v12 = v3;
  LOBYTE(v15) = 1;
  if ( v3 )
  {
    v5 = v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v15) = 0;
  *(_DWORD *)&this->children[40] = v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      ((Logger *)&ArgList)->FormatException(&path[164], (char *)&pTarget.m_pfnStageComposite, 343),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v6 = ((gbGeomNode *)v5)->LoadFromFile((const char *)pNode, 0, 0);
  v7 = v6 == 1;
  if ( v6 != 1 )
  {
    v8 = *(void ( ****)(_DWORD, int))&this->children[40];
    if ( v8 )
      (**v8)(v8, 1);
    *(_DWORD *)&this->children[40] = 0;
    v7 = v6 == 1;
  }
  v15 = -1;
  v9 = v7;
  return v9;
}

// 0x004D0A80
void GeomNode::DestroyChildren()
{
  int v2; // ecx
  int v3; // esi
  int v4; // edx
  _BYTE *i; // eax
  _DWORD *v6; // edx
  unsigned int v7; // eax
  _DWORD *v8; // edx
  int v9; // [esp+0x10] [ebp+0x4]
  int v10; // [esp+0x14] [ebp+0x8]
  int v11; // [esp+0x18] [ebp+0xC]
  _DWORD *v12; // [esp+0x1C] [ebp+0x10]
  int v13; // [esp+0x20] [ebp+0x14]
  int v14; // [esp+0x24] [ebp+0x18]

  v2 = *(_DWORD *)&this->children[24];
  v3 = 0;
  if ( v2 > 0 )
  {
    v4 = *(_DWORD *)(*(_DWORD *)&this->children[4] + 152 * v9);
    for ( i = (_BYTE *)(v4 + 64); *i; i += 72 )
    {
      if ( ++v3 >= v2 )
        return;
    }
    v6 = (_DWORD *)(v4 + 72 * v3);
    memset(v6, 0, 0x48u);
    *((_BYTE *)v6 + 65) = 0;
    *((_BYTE *)v6 + 64) = 1;
    *v6 = v10;
    v6[1] = v11;
    v6[2] = 2;
    v7 = ++g_nEffectUID;
    if ( !g_nEffectUID || v7 >= 0x7FFFFFFF )
    {
      v7 = 1;
      g_nEffectUID = 1;
    }
    v6[3] = v7;
    v6[4] = 0;
    v6[5] = v13;
    v6[6] = v14;
    if ( v12 )
    {
      v8 = v6 + 7;
      *v8 = *v12;
      v8[1] = v12[1];
      v8[2] = v12[2];
      v8[3] = v12[3];
    }
    ++*(_DWORD *)(*(_DWORD *)&this->children[4] + 152 * v9 + 4);
  }
}
