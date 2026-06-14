#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "MiniGame/MiniGame3.h"

// Forward declarations for unnamed functions
int UISceneUpdate(void); // from annotations

// Unnamed globals (extern)
extern const char * off_60113C;

// 0x00533FD0
void MiniGame3::SetCameraActive()
{
  ((gbCamera *)(this + 1))->SetAsCurrent(3);
}

// 0x00535320
void MiniGame3::Render()
{
  gbSceneGraph *pSceneGraph; // ebx
  int v3; // eax
  gbCamera *v4; // eax
  gbMatrixStack *v5; // edi
  int v6; // ecx

  pSceneGraph = gfxMgr->pSceneGraph;
  v3 = *((_DWORD *)this + 3);
  if ( v3 )
    v4 = (gbCamera *)(v3 + 4);
  else
    v4 = 0;
  ((gbSceneGraph *)pSceneGraph)->Begin(v4);
  v5 = gfxMgr->pMatrixStack[1];
  ((MiniGame3 *)*((MiniGame3 **)this + 3))->SetCameraActive();
  ((gbMatrixStack *)v5)->Push();
  v6 = *(_DWORD *)(*((_DWORD *)this + 1) + 3216);
  if ( v6 )
    (*(void ( **)(int, _DWORD))(*(_DWORD *)v6 + 16))(v6, 0);
  ((MiniGame3 *)*(MiniGame3 **)this)->RenderWithTransform(v5);
  ((MiniGame3 *)*((MiniGame3 **)this + 1))->PushPopStack(v5);
  ((gbMatrixStack *)v5)->Pop();
  ((gbSceneGraph *)pSceneGraph)->End();
}

// 0x00535970
void MiniGame3::PushPopStack(gbMatrixStack *pStack)
{
  SystemUI *v2; // eax
  SystemUI *v3; // eax

  ((gbMatrixStack *)pStack)->Push();
  v2 = (SystemUI *)UISceneUpdate();
  ((SystemUI *)v2)->Render((int)pStack);
  v3 = (SystemUI *)UISceneUpdate();
  ((SystemUI *)v3)->RenderWithStack(pStack);
  ((gbMatrixStack *)pStack)->Pop();
}

// 0x00535C30
char MiniGame3::LoadModels(
        
        const char *pszModel1,
        const char *pszModel2,
        const char *pszModel3)
{
  void *v5; // eax
  MiniGame3 v6; // edi
  void *v7; // eax
  void *v8; // edi
  void *v9; // eax
  void *v10; // edi
  OpenBaseFile v12; // [esp+0x1C] [ebp-0x114] BYREF
  void *v13; // [esp+0x20] [ebp-0x110]
  char Buffer[256]; // [esp+0x24] [ebp-0x10C] BYREF
  int v15; // [esp+0x12C] [ebp-0x4]

  v15 = 0;
  v5 = operator new(0x118u);
  v6 = (MiniGame3)v5;
  v13 = v5;
  LOBYTE(v15) = 1;
  if ( v5 )
  {
  }
  else
    v6 = 0;
  *this = v6;
  LOBYTE(v15) = 0;
  sprintf(Buffer, "%s%s", off_60113C, pszModel1);
  if ( !((gbGeomNode *)*(gbGeomNode **)this)->LoadFromFile(Buffer, 0, 0) )
    goto LABEL_16;
  ((gbGeomNode *)*(gbGeomNode **)this)->GetTotalOBBox((gbOBBox *)(this + 3));
  if ( pszModel2 )
  {
    v7 = operator new(0x118u);
    v8 = v7;
    v13 = v7;
    LOBYTE(v15) = 2;
    if ( v7 )
    {
    }
    else
      v8 = 0;
    *((_DWORD *)this + 1) = v8;
    LOBYTE(v15) = 0;
    sprintf(Buffer, "%s%s", off_60113C, pszModel2);
    if ( !((gbGeomNode *)*((gbGeomNode **)this + 1))->LoadFromFile(Buffer, 0, 0) )
      goto LABEL_16;
  }
  if ( !pszModel3 )
    goto LABEL_17;
  v9 = operator new(0x118u);
  v10 = v9;
  v13 = v9;
  LOBYTE(v15) = 3;
  if ( v9 )
  {
  }
  else
    v10 = 0;
  *((_DWORD *)this + 2) = v10;
  LOBYTE(v15) = 0;
  sprintf(Buffer, "%s%s", off_60113C, pszModel3);
  if ( ((gbGeomNode *)*((gbGeomNode **)this + 2))->LoadFromFile(Buffer, 0, 0) )
  {
LABEL_17:
    v15 = -1;
    return 1;
  }
  else
  {
LABEL_16:
    v15 = -1;
    return 0;
  }
}

// 0x00535F10
void MiniGame3::RenderWithTransform(gbMatrixStack *pStack)
{
  double v3; // st7
  int v4; // ecx
  int v5; // ecx
  float v6; // [esp+0x4] [ebp-0x20]
  float v7; // [esp+0x4] [ebp-0x20]
  struct gbVec3D v8; // [esp+0x18] [ebp-0xC] BYREF

  ((gbMatrixStack *)pStack)->Push();
  ((gbMatrixStack *)pStack)->Translate((gbVec3D *)this + 14);
  v3 = *((float *)this + 48) + 180.0;
  v8.x = 0.0;
  v6 = v3;
  v8.y = 1.0;
  v8.z = 0.0;
  ((gbMatrixStack *)pStack)->Rotate(v6, v8);
  v7 = *((float *)this + 49);
  v8.x = 1.0;
  v8.y = 0.0;
  v8.z = 0.0;
  ((gbMatrixStack *)pStack)->Rotate(v7, v8);
  (*(void ( **)(MiniGame3, _DWORD))(**(_DWORD **)this + 16))(*this, 0);
  v4 = *((_DWORD *)this + 1);
  if ( v4 )
    (*(void ( **)(int, _DWORD))(*(_DWORD *)v4 + 16))(v4, 0);
  v5 = *((_DWORD *)this + 2);
  if ( v5 )
    (*(void ( **)(int, _DWORD))(*(_DWORD *)v5 + 16))(v5, 0);
  ((gbMatrixStack *)pStack)->Pop();
}
