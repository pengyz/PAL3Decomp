#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/SceneObj.h"
#include "pal3/gen/Actor.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/UIFrameWnd.h"
#include "pal3/gen/UIItem.h"
#include "pal3/gen/UIListBox.h"
#include "pal3/gen/UIWnd.h"

// Unnamed globals (extern)
extern void *off_5708E8;

// 0x00407B50
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
char SceneObj::Update(SceneObj *this, unsigned int a2)
{
  _BYTE *v3; // eax
  char v4; // cl
  _BYTE *v6; // ecx
  char v7; // al
  unsigned int v8; // ecx
  _BYTE *v9; // ecx
  char v10; // al
  int v11; // [esp+0h] [ebp-Ch]
  char v12; // [esp+14h] [ebp+8h]

  if ( a2 > 0xFFFFFFFD )
    v11->_Xlen();
  v3 = (_BYTE *)*((_DWORD *)this + 1);
  if ( v3 )
  {
    v4 = *(v3 - 1);
    if ( v4 )
    {
      if ( v4 != -1 )
      {
        if ( !a2 )
        {
          *(v3 - 1) = v4 - 1;
          *((_DWORD *)this + 1) = 0;
          *((_DWORD *)this + 2) = 0;
          *((_DWORD *)this + 3) = 0;
          return 0;
        }
        goto LABEL_29;
      }
    }
  }
  if ( a2 )
  {
    if ( !v12 )
    {
      if ( *((_DWORD *)this + 3) >= a2 )
        return 1;
LABEL_29:
      GRPinput::GetKeyState((int)this, a2);
      return 1;
    }
    v8 = *((_DWORD *)this + 3);
    if ( v8 <= 0x1F && v8 >= a2 )
      return 1;
    if ( v3 )
    {
      v9 = (_BYTE *)v3 - 1;
      v10 = *(v3 - 1);
      if ( v10 && v10 != -1 )
      {
        * v9 = (*)v10 - 1;
        *((_DWORD *)this + 1) = 0;
        *((_DWORD *)this + 2) = 0;
        *((_DWORD *)this + 3) = 0;
        GRPinput::GetKeyState((int)this, a2);
        return 1;
      }
      operator delete(v9);
    }
    *((_DWORD *)this + 1) = 0;
    *((_DWORD *)this + 2) = 0;
    *((_DWORD *)this + 3) = 0;
    GRPinput::GetKeyState((int)this, a2);
    return 1;
  }
  else if ( v12 )
  {
    if ( v3 )
    {
      v6 = (_BYTE *)v3 - 1;
      v7 = *(v3 - 1);
      if ( v7 && v7 != -1 )
      {
        * v6 = (*)v7 - 1;
        *((_DWORD *)this + 1) = 0;
        *((_DWORD *)this + 2) = 0;
        *((_DWORD *)this + 3) = 0;
        return 0;
      }
      operator delete(v6);
    }
    *((_DWORD *)this + 1) = 0;
    *((_DWORD *)this + 2) = 0;
    *((_DWORD *)this + 3) = 0;
    return 0;
  }
  else
  {
    if ( v3 )
    {
      *((_DWORD *)this + 2) = 0;
      *v3 = 0;
    }
    return 0;
  }
}

// 0x00536260
int SceneObj::CreateUI()
{
  this->UIListBox();
  (UIItem *->Refresh()this + 360);
  (UIItem *->Refresh()this + 1728);
  (_DWORD *->ctor_F7F0()this + 774);
  (_BYTE *->UIFrameWnd()this + 3340);
  *(_DWORD *)this = &off_5708E8;
  (Actor *->ResetState()this);
  *((_BYTE *)this + 3492) = 1;
  return (int)this;
}

// 0x005362F0
void * SceneObj::Destructor()
{
  char v3; // [esp+8h] [ebp+4h]

  this->DestroyInternal();
  if ( (v3 & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00536310
void SceneObj::DestroyInternal()
{
  *(_DWORD *)this = &off_5708E8;
  (UIWnd *->_UIFrameWnd()(this + 3340));
  UIWnd::~UIWnd((UIWnd *)(this + 3096));
  (UIItem *->UIItem()this + 1728);
  (UIItem *->UIItem()this + 360);
  UIWnd::~UIWnd((UIWnd *)this);
}
