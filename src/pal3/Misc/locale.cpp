#include "pal3/ida_defs.h"
#include "pal3/globals.h"

// Unnamed globals (extern)
extern void *off_56A9C0;
extern void *off_56A9CC;
extern void *off_56F62C;

// 0x00411B80
std::locale::facet * std::locale::facet::`scalar deleting destructor'(std::locale::facet *this, char a2)
{
  *(_DWORD *)this->_pad_0000 = &off_56A9CC;
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x00411BB0
std::locale::facet * std::locale::facet::`scalar deleting destructor'(std::locale::facet *this, char a2)
{
  *(_DWORD *)this->_pad_0000 = &off_56A9C0;
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

// 0x004C0620
std::locale::facet * std::locale::facet::`scalar deleting destructor'(std::locale::facet *this, char a2)
{
  *(_DWORD *)this->_pad_0000 = &off_56F62C;
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}
