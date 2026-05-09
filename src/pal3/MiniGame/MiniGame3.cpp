#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/MiniGame3.h"

// 0x00535320
void MiniGame3::Render()
{
  gbSceneGraph *pSceneGraph; // ebx
  int v3; // eax
  struct gbCamera *v4; // eax
  gbMatrixStack *v5; // edi
  int v6; // ecx

  pSceneGraph = *(gbSceneGraph **)&g_pGfxManager[448];
  v3 = *((_DWORD *)this + 3);
  if ( v3 )
    v4 = (struct gbCamera *)(v3 + 4);
  else
    v4 = 0;
  pSceneGraph->Begin(v4);
  v5 = *(gbMatrixStack **)&g_pGfxManager[216];
  sub_533FD0(*((_DWORD *)this + 3));
  v5->Push();
  v6 = *(_DWORD *)(*((_DWORD *)this + 1) + 3216);
  if ( v6 )
    (*(void (__thiscall **)(int, _DWORD))(*(_DWORD *)v6 + 16))(v6, 0);
  sub_535F10(*(float **)this, v5);
  sub_535970(v5);
  v5->Pop();
  pSceneGraph->End();
}
