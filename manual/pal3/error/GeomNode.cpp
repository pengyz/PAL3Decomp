#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/GeomNode.h"
#include "Effect/CEffgbParticle.h"
#include "GameBase/Logger.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Misc/String.h"
#include "free_functions.h"

// Forward declarations for unnamed functions
int sub_4B70C0(...);
int sub_4B7220(...);

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
  if ( ((gbChain1DNode *)pGeomNode) == 43 )
  {
    this->pNext = ((GeomNode *)((GeomNode *)4));
  }
  else
  {
    v5 = (char *)pGeomNode + v4 - 4;
    if ( _strcmpi(v5, ".cvd") )
    {
      if ( !_strcmpi(v5, ".pol") )
        this->pNext = ((GeomNode *)((GeomNode *)2));
    }
    else
    {
      this->pNext = ((GeomNode *)((GeomNode *)3));
    }
  }
  pNext = (GeomNode *)this->pNext;
  if ( (int)this->pNext >= 2 )
  {
    if ( (int)pNext <= 3 )
    {
      v8 = (GeomNode *)operator new(0x118u);
      v9 = (GeomNode *)v8;
      v13 = 0;
      if ( v8 )
      {
        v8->gbGeomNode::gbGeomNode();
        v10 = (GeomNode *)v9;
      }
      else
      {
        v10 = 0;
      }
      v13 = -1;
      this->pParent = ((GeomNode *)(v10));
      if ( !(((gbGeomNode *)v10))->gbGeomNode::LoadFromFile((const char *)pGeomNode, 0, 0) )
        this->pNext = ((GeomNode *)0);
      (*(void ( **)(GeomNode *, _DWORD))&this->pParent->pNext->children[16])(this->pParent, 0);
      (((gbVisNode *)this->pParent))->gbVisNode::SetTimeScale(0.0);
      (*(void ( **)(GeomNode *))&this->pParent->pNext->children[12])(this->pParent);
      (((gbGeomNode *)this->pParent))->gbGeomNode::GetTotalOBBox((gbOBBox *)this->children);
      (*(void ( **)(GeomNode *, _DWORD))&this->pParent->pNext->children[16])(this->pParent, 0);
      (((gbVisNode *)this->pParent))->gbVisNode::SetTimeScale(1.0);
    }
    else if ( pNext == (GeomNode *)4 )
    {
      strcpy((char *)String, (const char *)pGeomNode);
      String[0] = 48;
      v11 = atoi((const char *)String);
      sub_4B7220();
      v7 = (GeomNode *)sub_4B70C0(v11);
      this->pParent = ((GeomNode *)(v7));
      if ( v7 )
        (*(void ( **)(GeomNode *, int))&v7->pNext->children[32])(v7, nVal);
      else
        this->pNext = ((GeomNode *)0);
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

  (((CEffgbParticle *)this))->CEffgbParticle::DestroyEffect() /* [ROWTABLE] */;
  v15 = 0;
  v3 = (gbGeomNode *)operator new(0x118u);
  v4 = (gbGeomNode *)v3;
  v12 = (gbGeomNode *)v3;
  LOBYTE(v15) = 1;
  if ( v3 )
  {
    v3->gbGeomNode::gbGeomNode();
    v5 = (gbGeomNode *)v4;
  }
  else
  {
    v5 = 0;
  }
  LOBYTE(v15) = 0;
  *(_DWORD *)&this->children[40] = (_DWORD)v5;
  if ( !v5 )
  {
    qmemcpy(
      pExceptionObject,
      (((Logger *)&ArgList))->Logger::FormatException(&path[164], aDProjectPal3Co_2, 343),
      sizeof(pExceptionObject));
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI1_AV_Exception__);
  }
  v6 = (((gbGeomNode *)v5))->gbGeomNode::LoadFromFile((const char *)pNode, 0, 0);
  v7 = v6 == 1;
  if ( v6 != 1 )
  {
    v8 = *(void ( ****)(_DWORD, int))&this->children[40];
    if ( v8 )
      (**v8)((_DWORD)((_DWORD)(v8)), (int)(1));
    *(_DWORD *)&this->children[40] = 0;
    v7 = v6 == 1;
  }
  v15 = -1;
  v9 = v7;
  ((OpenNULLFile *)&v11)->OpenNULLFile::OpenNULLFile();
  return v9;
}

// 0x004D0A80
void GeomNode::DestroyChildren(int nVal1)
{
  int v3; // ecx
  int v4; // esi
  int v5; // edx
  _BYTE *i; // eax
  _DWORD *v7; // edx
  unsigned int v8; // eax
  _DWORD *v9; // edx
  int v10; // [esp+0x14] [ebp+0x8]
  int v11; // [esp+0x18] [ebp+0xC]
  _DWORD *v12; // [esp+0x1C] [ebp+0x10]
  int v13; // [esp+0x20] [ebp+0x14]
  int v14; // [esp+0x24] [ebp+0x18]

  v3 = *(_DWORD *)&this->children[24];
  v4 = 0;
  if ( v3 > 0 )
  {
    v5 = *(_DWORD *)(*(_DWORD *)&this->children[4] + 152 * nVal1);
    for ( i = (_BYTE *)(v5 + 64); *i; i += 72 )
    {
      if ( ++v4 >= v3 )
        return;
    }
    v7 = (_DWORD *)(v5 + 72 * v4);
    memset(v7, 0, 0x48u);
    *((_BYTE *)v7 + 65) = 0;
    *((_BYTE *)v7 + 64) = 1;
    *v7 = v10;
    v7[1] = v11;
    v7[2] = 2;
    v8 = ++g_nEffectUID;
    if ( !g_nEffectUID || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      g_nEffectUID = 1;
    }
    v7[3] = v8;
    v7[4] = 0;
    v7[5] = v13;
    v7[6] = v14;
    if ( v12 )
    {
      v9 = (_DWORD *)(v7 + 7);
      *v9 = *v12;
      v9[1] = (unsigned long)v12[1];
      v9[2] = (unsigned long)v12[2];
      v9[3] = (unsigned long)v12[3];
    }
    ++*(_DWORD *)(*(_DWORD *)&this->children[4] + 152 * nVal1 + 4);
  }
}
