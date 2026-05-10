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
  v3 = (_BYTE *)*(_BYTE **)&this->_pad_0000[4];
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
          *(_DWORD *)&this->_pad_0000[4] = 0;
          *(_DWORD *)&this->_pad_0000[8] = 0;
          *(_DWORD *)&this->_pad_0000[12] = 0;
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
      if ( *(_DWORD *)&this->_pad_0000[12] >= a2 )
        return 1;
LABEL_29:
      ((GRPinput *)this)->GetKeyState(a2);
      return 1;
    }
    v8 = *(_DWORD *)&this->_pad_0000[12];
    if ( v8 <= 0x1F && v8 >= a2 )
      return 1;
    if ( v3 )
    {
      v9 = (_BYTE *)v3 - 1;
      v10 = *(v3 - 1);
      if ( v10 && v10 != -1 )
      {
        * v9 = (*)v10 - 1;
        *(_DWORD *)&this->_pad_0000[4] = 0;
        *(_DWORD *)&this->_pad_0000[8] = 0;
        *(_DWORD *)&this->_pad_0000[12] = 0;
        ((GRPinput *)this)->GetKeyState(a2);
        return 1;
      }
      operator delete(v9);
    }
    *(_DWORD *)&this->_pad_0000[4] = 0;
    *(_DWORD *)&this->_pad_0000[8] = 0;
    *(_DWORD *)&this->_pad_0000[12] = 0;
    ((GRPinput *)this)->GetKeyState(a2);
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
        *(_DWORD *)&this->_pad_0000[4] = 0;
        *(_DWORD *)&this->_pad_0000[8] = 0;
        *(_DWORD *)&this->_pad_0000[12] = 0;
        return 0;
      }
      operator delete(v6);
    }
    *(_DWORD *)&this->_pad_0000[4] = 0;
    *(_DWORD *)&this->_pad_0000[8] = 0;
    *(_DWORD *)&this->_pad_0000[12] = 0;
    return 0;
  }
  else
  {
    if ( v3 )
    {
      *(_DWORD *)&this->_pad_0000[8] = 0;
      *v3 = 0;
    }
    return 0;
  }
}

// 0x00536260
int SceneObj::CreateUI()
{
  ((UIListBox *)this)->UIListBox();
  ((UIItem *)&this->mOBBox[15])->Refresh();
  ((UIItem *)&this->m_common[20])->Refresh();
  ((UIWnd *)((char *)this + 3096))->ctor_F7F0();
  ((UIFrameWnd *)((char *)this + 3340))->UIFrameWnd();
  *(_DWORD *)this->_pad_0000 = &off_5708E8;
  ((Actor *)this)->ResetState();
  *((_BYTE *)this + 3492) = 1;
  return (int)this->_pad_0000;
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
  *(_DWORD *)this->_pad_0000 = &off_5708E8;
  ((UIFrameWnd *)((char *)this + 3340))->_UIFrameWnd();
  ((UIWnd *)((char *)this + 3096))->~UIWnd();
  ((UIItem *)&this->m_common[20])->UIItem();
  ((UIItem *)&this->mOBBox[15])->UIItem();
  ((UIWnd *)this)->~UIWnd();
}
