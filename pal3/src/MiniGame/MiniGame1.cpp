#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "MiniGame/MiniGame1.h"

// 0x0052B860
void MiniGame1::Render()
{
  gbSceneGraph *pSceneGraph; // ebx
  gbMatrixStack *v3; // edi
  int v4; // ecx
  Object3D *v5; // ebx
  int v6; // ebp
  int v7; // [esp+0x0] [ebp-0x10]
  int v8; // [esp+0x4] [ebp-0xC]
  gbMatrixStack *v9; // [esp+0x8] [ebp-0x8]

  pSceneGraph = gfxMgr->pSceneGraph;
  v3 = gfxMgr->pMatrixStack[1];
  ((gbSceneGraph *)pSceneGraph)->Begin(**((gbCamera ***)this + 3));
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  ((gbCamera *)**((gbCamera ***)this + 3))->SetAsCurrent(3);
  ((gbMatrixStack *)v3)->Push();
  v4 = *((_DWORD *)this + 2);
  if ( v4 )
    (*(void ( **)(int, _DWORD))(*(_DWORD *)v4 + 16))(v4, 0);
  ((UINote *)*(UINote **)this)->RenderIfVisible(v3);
  ((gbMatrixStack *)v3)->Pop();
  ((gbSceneGraph *)pSceneGraph)->End();
  v5 = (Object3D *)(this + 4);
  v6 = 5;
  do
  {
    ((Object3D *)v5++)->GetScreenDegree((int)v3, v7, v8, v9);
    --v6;
  }
  while ( v6 );
  ((Object3D *)(this + 214))->GetScreenDegree(0, v7, v8, v9);
}
