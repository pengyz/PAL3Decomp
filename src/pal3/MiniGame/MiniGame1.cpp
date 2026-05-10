#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MiniGame1.h"
#include "pal3/gen/Object3D.h"

// Forward declarations for unnamed functions
int sub_52AFC0(...);

// 0x0052B860
void MiniGame1::Render()
{
  int v1; // ebx
  gbMatrixStack *v3; // edi
  int v4; // ecx
  char *v5; // ebx
  int v6; // ebp
  int v7; // [esp+0h] [ebp-10h]
  int v8; // [esp+4h] [ebp-Ch]
  gbMatrixStack *v9; // [esp+8h] [ebp-8h]

  v1 = *(_DWORD *)(g_Input.KeyInfo[177].Data + 448);
  v3 = (gbMatrixStack *)*(gbMatrixStack **)(g_Input.KeyInfo[177].Data + 216);
  ((gbSceneGraph *)v1)->Begin(**((struct gbCamera ***)this + 3));
  *(_BYTE *)(v1 + 19244) = 0;
  ((gbCamera *)**((gbCamera ***)this + 3))->SetAsCurrent(3);
  v3->Push();
  v4 = *((_DWORD *)this + 2);
  if ( v4 )
    (*(void (**)(int, _DWORD))(*(_DWORD *)v4 + 16))(v4, 0);
  sub_52AFC0(*(int **)this, v3);
  v3->Pop();
  ((gbSceneGraph *)v1)->End();
  v5 = (char *)this + 16;
  v6 = 5;
  do
  {
    ((Object3D *)v5)->GetScreenDegree((int)v3, v7, v8, v9);
    v5 += 152;
    --v6;
  }
  while ( v6 );
  ((Object3D *)(int)this + 856)->GetScreenDegree(0, v7, v8, v9);
}
