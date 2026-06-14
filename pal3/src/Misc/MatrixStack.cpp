#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/MatrixStack.h"

// 0x0052FC60
void MatrixStack::BeginScene()
{
  gbSceneGraph *pSceneGraph; // esi
  gbMatrixStack *v3; // esi
  MatrixStack *v4; // ebx
  gbVec3D *v5; // ebp
  int v6; // eax
  MatrixStack *v7; // ebx
  gbVec3D *v8; // ebp
  float v9; // edx
  float v10; // [esp+0x1C] [ebp-0x2C]
  float v11; // [esp+0x1C] [ebp-0x2C]
  int v12; // [esp+0x34] [ebp-0x14]
  int v13; // [esp+0x34] [ebp-0x14]
  gbSceneGraph *v14; // [esp+0x38] [ebp-0x10]
  struct gbVec3D v15; // [esp+0x3C] [ebp-0xC] BYREF

  pSceneGraph = gfxMgr->pSceneGraph;
  v14 = pSceneGraph;
  ((gbSceneGraph *)pSceneGraph)->Begin(**((gbCamera ***)this + 552));
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v3 = gfxMgr->pMatrixStack[1];
  ((gbCamera *)**((gbCamera ***)this + 552))->SetAsCurrent(3);
  ((gbMatrixStack *)v3)->Push();
v5 = (gbVec3D *)(this + 420);
  v12 = 6;
  do
  {
    ((gbMatrixStack *)v3)->Push();
    ((gbMatrixStack *)v3)->Translate(v5);
    (*(void ( **)(MatrixStack *, _DWORD))(*(_DWORD *)v4 + 16))(v4, 0);
    ((gbMatrixStack *)v3)->Pop();
    ++v5;
    v4 += 70;
    --v12;
  }
  while ( v12 );
  v6 = 0;
  v7 = this + 556;
  v13 = 0;
  v8 = (gbVec3D *)(this + 766);
  do
  {
    if ( *((_BYTE *)this + v6 + 3328) )
    {
      ((gbMatrixStack *)v3)->Push();
      ((gbMatrixStack *)v3)->Translate(v8);
      v10 = *((float *)this + 833);
      v15.x = 0.0;
      v15.y = 1.0;
      v15.z = 0.0;
      ((gbMatrixStack *)v3)->Rotate(v10, v15);
      (*(void ( **)(MatrixStack *, _DWORD))(*(_DWORD *)v7 + 16))(v7, 0);
      ((gbMatrixStack *)v3)->Pop();
      v6 = v13;
    }
    ++v6;
    ++v8;
    v7 += 70;
    v13 = v6;
  }
  while ( v6 < 3 );
  if ( *((_BYTE *)this + 3744) )
  {
    ((gbMatrixStack *)v3)->Push();
    ((gbMatrixStack *)v3)->Translate((gbVec3D *)(this + 907));
    v9 = *((float *)this + 934);
    v15.x = 0.0;
    v15.y = 1.0;
    v15.z = 0.0;
    ((gbMatrixStack *)v3)->Rotate(v9, v15);
    v11 = *((float *)this + 940);
    v15.x = 1.0;
    v15.y = 0.0;
    v15.z = 0.0;
    ((gbMatrixStack *)v3)->Rotate(v11, v15);
    (*(void ( **)(MatrixStack *, _DWORD))(*((_DWORD *)this + 834) + 16))(this + 834, 0);
    ((gbMatrixStack *)v3)->Pop();
  }
  ((gbMatrixStack *)v3)->Pop();
  ((gbSceneGraph *)v14)->End();
}

// 0x00530350
void MatrixStack::RenderScenePass()
{
  gbSceneGraph *pSceneGraph; // edi
  gbMatrixStack *v3; // ebx

  pSceneGraph = gfxMgr->pSceneGraph;
  ((gbSceneGraph *)pSceneGraph)->Begin(**((gbCamera ***)this + 1));
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v3 = gfxMgr->pMatrixStack[1];
  ((gbCamera *)**((gbCamera ***)this + 1))->SetAsCurrent(3);
  ((gbMatrixStack *)v3)->Push();
  (*(void ( **)(MatrixStack, _DWORD))(**(_DWORD **)this + 16))(*this, 0);
  ((gbMatrixStack *)v3)->Pop();
  ((gbSceneGraph *)pSceneGraph)->End();
}

// 0x00530C70
void MatrixStack::BeginSceneWithRotation()
{
  gbSceneGraph *pSceneGraph; // ebp
  gbMatrixStack *v3; // edi
  double v4; // st7
  float v5; // ecx
  int v6; // eax
  double v7; // st7
  float v8; // [esp+0x34] [ebp-0x94]
  float v9; // [esp+0x34] [ebp-0x94]
  struct gbVec3D v10; // [esp+0x4C] [ebp-0x7C] BYREF
  gbQuaternion v11; // [esp+0x58] [ebp-0x70] BYREF
  gbQuaternion v12; // [esp+0x68] [ebp-0x60] BYREF
  struct gbQuaternion v13; // [esp+0x78] [ebp-0x50] BYREF
  gbMatrix4 v14; // [esp+0x88] [ebp-0x40] BYREF

  pSceneGraph = gfxMgr->pSceneGraph;
  ((gbSceneGraph *)pSceneGraph)->Begin(**((gbCamera ***)this + 144));
  LOBYTE(pSceneGraph->pnodebuf[713]) = 0;
  v3 = gfxMgr->pMatrixStack[1];
  ((gbCamera *)**((gbCamera ***)this + 144))->SetAsCurrent(3);
  ((gbMatrixStack *)v3)->Push();
  memset(&v11, 0, 12);
  v11.w = 1.0;
  memset(&v12, 0, 12);
  v12.w = 1.0;
  memset(&v13, 0, 12);
  v13.w = 1.0;
  v10.x = 1.0;
  v10.y = 0.0;
  v10.z = 0.0;
  ((gbQuaternion *)&v11)->SetAxisAngle(&v10, 45.0);
  v10.x = 0.0;
  v10.y = 1.0;
  v10.z = 0.0;
  ((gbQuaternion *)&v12)->SetAxisAngle(&v10, 90.0);
  ((gbQuaternion *)&v12)->MultiplyBy(&v11, &v13);
  ((gbQuaternion *)&v13)->GetMatrix((gbMatrix4 *)(this + 24));
  (*(void ( **)(MatrixStack *, _DWORD))(*((_DWORD *)this + 2) + 16))(this + 2, 0);
  if ( *((_DWORD *)this + 196) == 2 )
  {
    v10.x = *((float *)this + 158);
    v10.y = *((float *)this + 205);
    v10.z = *((float *)this + 160);
    ((gbMatrixStack *)v3)->Translate(v10);
  }
  else
  {
    ((gbMatrixStack *)v3)->Translate((gbVec3D *)(this + 158));
  }
  if ( *((_DWORD *)this + 196) == 3 )
  {
    v4 = *((float *)this + 169) - 90.0;
    v10.x = 0.0;
    v10.y = 1.0;
    v10.z = 0.0;
    v8 = v4;
    ((gbMatrixStack *)v3)->Rotate(v8, v10);
  }
  else
  {
    v5 = *((float *)this + 169);
    v10.x = 0.0;
    v10.y = 1.0;
    v10.z = 0.0;
    ((gbMatrixStack *)v3)->Rotate(v5, v10);
  }
  v6 = *((_DWORD *)this + 196);
  if ( v6 == 1 || v6 == 3 )
  {
    v10.x = 0.0;
    v10.y = 0.0;
    v10.z = 1.0;
    ((gbMatrixStack *)v3)->Rotate(0.0, v10);
  }
  else
  {
    v7 = *((float *)this + 170) - 90.0;
    v10.x = 0.0;
    v10.y = 0.0;
    v10.z = 1.0;
    v9 = v7;
    ((gbMatrixStack *)v3)->Rotate(v9, v10);
  }
  if ( *((_DWORD *)this + 196) != 3 )
  {
    ((gbMatrixStack *)v3)->Push();
    ((gbActor *)*(gbActor **)(*(_DWORD *)this + 16))->GetTagNodeTM(&v14, "tag_weapon1");
    ((gbMatrixStack *)v3)->MultMatrix(&v14);
    (*(void ( **)(_DWORD, _DWORD))(**((_DWORD **)this + 1) + 16))(*((_DWORD *)this + 1), 0);
    ((gbMatrixStack *)v3)->Pop();
  }
  ((Actor *)*(Actor **)this)->DispatchAction(0);
  ((gbMatrixStack *)v3)->Pop();
  ((gbSceneGraph *)pSceneGraph)->End();
}
