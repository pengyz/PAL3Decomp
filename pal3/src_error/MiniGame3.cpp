#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "MiniGame/MiniGame3.h"
#include "Misc/OpenBaseFile.h"
#include "Misc/OpenNULLFile.h"
#include "Scene/Scene.h"
#include "Misc/SystemUI.h"
#include "free_functions.h"

// Forward declarations for unnamed functions

// 0x00533FD0
void MiniGame3::SetCameraActive()
{
  (((gbCamera *)&this[1]))->gbCamera::SetAsCurrent(3);
}

// 0x00535320
void MiniGame3::Render()
{
  gbSceneGraph *pSceneGraph; // ebx
  MiniGame3 v3; // eax
  gbCamera *v4; // eax
  gbMatrixStack *v5; // edi
  int v6; // ecx

  pSceneGraph = gfxMgr->pSceneGraph;
  v3 = this[3];
  if ( v3 )
    v4 = (gbCamera *)(*(_DWORD *)&v3 + 4);
  else
    v4 = 0;
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(v4);
  v5 = gfxMgr->pMatrixStack[1];
  (((MiniGame3 *)*(MiniGame3 **)&this[3]))->MiniGame3::SetCameraActive();
  (((gbMatrixStack *)v5))->gbMatrixStack::Push();
  v6 = *(_DWORD *)(*(_DWORD *)&this[1] + 3216);
  if ( v6 )
    (*(void ( **)(int, _DWORD))(*(_DWORD *)v6 + 16))(v6, 0);
  (((MiniGame3 *)*(MiniGame3 **)this))->MiniGame3::RenderWithTransform(v5);
  (((MiniGame3 *)*(MiniGame3 **)&this[1]))->MiniGame3::PushPopStack(v5);
  (((gbMatrixStack *)v5))->gbMatrixStack::Pop();
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
}

// 0x00535970
void MiniGame3::PushPopStack(gbMatrixStack *pStack)
{
  Scene *v2; // eax

  (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
  v2 = UISceneUpdate();
  (((SystemUI *)v2))->SystemUI::Render((int)pStack);
  UISceneUpdate();
  SystemUI_RenderWithStack((int)pStack);
  (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
}

// 0x00535C30
char MiniGame3::LoadModels(
        
        const char *pszModel1,
        const char *pszModel2,
        const char *pszModel3)
{
    MiniGame3 *_this = this;
  void *v5; // eax
  MiniGame3 v6; // edi
  void *v7; // eax
  MiniGame3 v8; // edi
  void *v9; // eax
  MiniGame3 v10; // edi
  OpenBaseFile v12; // [esp+0x1C] [ebp-0x114] BYREF
  void *v13; // [esp+0x20] [ebp-0x110]
  char Buffer[256]; // [esp+0x24] [ebp-0x10C] BYREF
  int v15; // [esp+0x12C] [ebp-0x4]

  v15 = 0;
  v5 = (void *)operator new(0x118u);
  v6 = (MiniGame3)v5;
  v13 = (void *)v5;
  LOBYTE(v15) = 1;
  if ( v5 )
    v5->gbGeomNode::gbGeomNode();
  else
    v6 = 0;
  *_this = v6;
  LOBYTE(v15) = 0;
  sprintf(Buffer, "%s%s", off_60113C, pszModel1);
  if ( !(((gbGeomNode *)*(gbGeomNode **)_this))->gbGeomNode::LoadFromFile(Buffer, 0, 0) )
    goto LABEL_16;
  (((gbGeomNode *)*(gbGeomNode **)_this))->gbGeomNode::GetTotalOBBox((gbOBBox *)&_this[3]);
  if ( pszModel2 )
  {
    v7 = (void *)operator new(0x118u);
    v8 = (MiniGame3)v7;
    v13 = (void *)v7;
    LOBYTE(v15) = 2;
    if ( v7 )
      v7->gbGeomNode::gbGeomNode();
    else
      v8 = 0;
    _this[1] = v8;
    LOBYTE(v15) = 0;
    sprintf(Buffer, "%s%s", off_60113C, pszModel2);
    if ( !(((gbGeomNode *)*(gbGeomNode **)&_this[1]))->gbGeomNode::LoadFromFile(Buffer, 0, 0) )
      goto LABEL_16;
  }
  if ( !pszModel3 )
    goto LABEL_17;
  v9 = (void *)operator new(0x118u);
  v10 = (MiniGame3)v9;
  v13 = (void *)v9;
  LOBYTE(v15) = 3;
  if ( v9 )
    v9->gbGeomNode::gbGeomNode();
  else
    v10 = 0;
  _this[2] = v10;
  LOBYTE(v15) = 0;
  sprintf(Buffer, "%s%s", off_60113C, pszModel3);
  if ( (((gbGeomNode *)*(gbGeomNode **)&_this[2]))->gbGeomNode::LoadFromFile(Buffer, 0, 0) )
  {
LABEL_17:
    v15 = -1;
    ((OpenNULLFile *)&v12)->OpenNULLFile::OpenNULLFile();
    return 1;
  }
  else
  {
LABEL_16:
    v15 = -1;
    ((OpenNULLFile *)&v12)->OpenNULLFile::OpenNULLFile();
    return 0;
  }
}

// 0x00535F10
void MiniGame3::RenderWithTransform(gbMatrixStack *pStack)
{
  float v3; // st7
  MiniGame3 v4; // ecx
  MiniGame3 v5; // ecx
  float v6; // [esp+0x4] [ebp-0x20]
  float v7; // [esp+0x4] [ebp-0x20]
  struct gbVec3D v8; // [esp+0x18] [ebp-0xC] BYREF

  (((gbMatrixStack *)pStack))->gbMatrixStack::Push();
  (((gbMatrixStack *)pStack))->gbMatrixStack::Translate(*(gbVec3D *)&this[42]);
  v3 = *(float *)&this[48] + 180.0f;
  v8.x = 0.0;
  v6 = v3;
  v8.y = 1.0;
  v8.z = 0.0;
  (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(v6,  v8);
  v7 = *(float *)&this[49];
  v8.x = 1.0;
  v8.y = 0.0;
  v8.z = 0.0;
  (((gbMatrixStack *)pStack))->gbMatrixStack::Rotate(v7,  v8);
  (*(void ( **)(MiniGame3, _DWORD))(**(_DWORD **)this + 16))(*this, 0);
  v4 = this[1];
  if ( v4 )
    (*(void ( **)(MiniGame3, _DWORD))(**(_DWORD **)&v4 + 16))(v4, 0);
  v5 = this[2];
  if ( v5 )
    (*(void ( **)(MiniGame3, _DWORD))(**(_DWORD **)&v5 + 16))(v5, 0);
  (((gbMatrixStack *)pStack))->gbMatrixStack::Pop();
}
