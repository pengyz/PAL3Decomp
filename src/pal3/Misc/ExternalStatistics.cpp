#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/ExternalStatistics.h"

// 0x00532D50
void Concurrency::details::ExternalStatistics::MarkInactive(Concurrency::details::ExternalStatistics *this)
{
  *((_DWORD *)this + 6) = 0;
}
