#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "MiniGame/MiniGame1.h"
#include "Role/Object3D.h"
#include "free_functions.h"

// 0x0052B860
void MiniGame1::Render()
{
  gbSceneGraph *pSceneGraph; // ebx
  gbMatrixStack *v3; // edi
  MiniGame1 v4; // ecx
  MiniGame1 *v5; // ebx
  int v6; // ebp
  gbVec3D v7; // [esp-0x4] [ebp-0x14]
  gbMatrixStack *v8; // [esp+0x8] [ebp-0x8]

  pSceneGraph = gfxMgr->pSceneGraph;
  v3 = gfxMgr->pMatrixStack[1];
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::Begin(**(gbCamera ***)&this[3]);
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  (((gbCamera *)**(gbCamera ***)&this[3]))->gbCamera::SetAsCurrent(3);
  (((gbMatrixStack *)v3))->gbMatrixStack::Push();
  v4 = this[2];
  if ( v4 )
    (*(void ( **)(MiniGame1, _DWORD))(**(_DWORD **)&v4 + 16))(v4, 0);
  UINote_RenderIfVisible((int)v3);
  (((gbMatrixStack *)v3))->gbMatrixStack::Pop();
  (((gbSceneGraph *)pSceneGraph))->gbSceneGraph::End();
  v5 = this + 4;
  v6 = 5;
  do
  {
    LODWORD(v7.x) = (unsigned long)v3;
    (((Object3D *)v7))->Object3D::RenderObjectScene(v8);
    v5 += 38;
    --v6;
  }
  while ( v6 );
  v7.x = 0.0f;
  (((Object3D *)v7))->Object3D::RenderObjectScene(v8);
}
