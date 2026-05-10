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
char SceneObj::Update(unsigned int a2)
{
  _BYTE *d004; // eax
  char v4; // cl
  _BYTE *v6; // ecx
  char v7; // al
  unsigned int d00C; // ecx
  _BYTE *v9; // ecx
  char v10; // al
  int v11; // [esp+0h] [ebp-Ch]
  char v12; // [esp+14h] [ebp+8h]

  if ( a2 > 0xFFFFFFFD )
    v11->_Xlen();
  d004 = (_BYTE *)this->_d004;
  if ( d004 )
  {
    v4 = *(d004 - 1);
    if ( v4 )
    {
      if ( v4 != -1 )
      {
        if ( !a2 )
        {
          *(d004 - 1) = v4 - 1;
          this->_d004 = 0;
          this->_d008 = 0;
          this->_d00C = 0;
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
      if ( this->_d00C >= a2 )
        return 1;
LABEL_29:
      ((GRPinput *)this)->GetKeyState(a2);
      return 1;
    }
    d00C = this->_d00C;
    if ( d00C <= 0x1F && d00C >= a2 )
      return 1;
    if ( d004 )
    {
      v9 = (_BYTE *)d004 - 1;
      v10 = *(d004 - 1);
      if ( v10 && v10 != -1 )
      {
        * v9 = (*)v10 - 1;
        this->_d004 = 0;
        this->_d008 = 0;
        this->_d00C = 0;
        ((GRPinput *)this)->GetKeyState(a2);
        return 1;
      }
      operator delete(v9);
    }
    this->_d004 = 0;
    this->_d008 = 0;
    this->_d00C = 0;
    ((GRPinput *)this)->GetKeyState(a2);
    return 1;
  }
  else if ( v12 )
  {
    if ( d004 )
    {
      v6 = (_BYTE *)d004 - 1;
      v7 = *(d004 - 1);
      if ( v7 && v7 != -1 )
      {
        * v6 = (*)v7 - 1;
        this->_d004 = 0;
        this->_d008 = 0;
        this->_d00C = 0;
        return 0;
      }
      operator delete(v6);
    }
    this->_d004 = 0;
    this->_d008 = 0;
    this->_d00C = 0;
    return 0;
  }
  else
  {
    if ( d004 )
    {
      this->_d008 = 0;
      *d004 = 0;
    }
    return 0;
  }
}

// 0x00536260
int SceneObj::CreateUI()
{
  ((UIListBox *)this)->UIListBox();
  ((UIItem *)(UIItem *)this + 360)->Refresh();
  ((UIItem *)(UIItem *)this + 1728)->Refresh();
  ((UIWnd *)((char *)this + 3096))->ctor_F7F0();
  ((UIFrameWnd *)((char *)this + 3340))->UIFrameWnd();
  this->_p000 = &off_5708E8;
  ((Actor *)this)->ResetState();
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
  this->_p000 = &off_5708E8;
  ((UIFrameWnd *)((char *)this + 3340))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 3096))->~UIWnd();
  ((UIItem *)(UIItem *)this + 1728)->UIItem();
  ((UIItem *)(UIItem *)this + 360)->UIItem();
  ((UIWnd *)this)->~UIWnd();
}
