#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/InternalContextBase.h"

// 0x00479250
struct Concurrency::IThreadProxy * Concurrency::details::InternalContextBase::GetProxy(
        Concurrency::details::InternalContextBase *this)
{
  return (struct Concurrency::IThreadProxy *)*((_DWORD *)this + 39);
}
