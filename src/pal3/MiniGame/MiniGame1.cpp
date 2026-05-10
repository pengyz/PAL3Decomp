#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MiniGame1.h"

// Forward declarations for unnamed functions
int sub_52AFC0(...);

// 0x0052B860
void MiniGame1::Render()
{
  gbSceneGraph *pSceneGraph; // ebx
  gbMatrixStack *v3; // edi
  int v4; // ecx
  char *v5; // ebx
  int v6; // ebp
  int v7; // [esp+0h] [ebp-10h]
  int v8; // [esp+4h] [ebp-Ch]
  gbMatrixStack *v9; // [esp+8h] [ebp-8h]

  pSceneGraph = (gbSceneGraph *)*(gbSceneGraph **)&g_pGfxManager[448];
  v3 = (gbMatrixStack *)*(gbMatrixStack **)&g_pGfxManager[216];
  pSceneGraph->Begin(**((struct gbCamera ***)this + 3));
  LOBYTE(pSceneGraph->?[9].m[0]) = 0;
  gbCamera::SetAsCurrent(**((gbCamera ***)this + 3), 3);
  v3->Push();
  v4 = *((_DWORD *)this + 2);
  if ( v4 )
    (*(void (**)(int, _DWORD))(*(_DWORD *)v4 + 16))(v4, 0);
  sub_52AFC0(*(int **)this, (int)v3);
  v3->Pop();
  pSceneGraph->End();
  v5 = (char *)this + 16;
  v6 = 5;
  do
  {
    Object3D::GetScreenDegree((int)v5, (int)v3, v7, v8, v9);
    v5 += 152;
    --v6;
  }
  while ( v6 );
  Object3D::GetScreenDegree((int)this + 856, 0, v7, v8, v9);
}
