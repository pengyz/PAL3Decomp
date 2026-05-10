#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/strstreambuf.h"
#include "pal3/gen/CPK.h"

// Forward declarations for unnamed functions
int sub_53C420(...);

// Unnamed globals (extern)
extern void *off_570A04;

// 0x0053C2D0
strstreambuf::~strstreambuf()
{
  *(_DWORD *)this = &off_570A04;
  sub_53C420((int *)this);
  ((CPK *)((char *)this + 917964))->~CPK();
  ((CPK *)((char *)this + 16))->~CPK();
}
