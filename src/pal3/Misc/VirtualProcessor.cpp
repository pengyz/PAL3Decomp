#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/VirtualProcessor.h"

// 0x004790F0
unsigned int Concurrency::details::VirtualProcessor::GetExecutionResourceId(
        Concurrency::details::VirtualProcessor *this)
{
  return *((_DWORD *)this + 35);
}

// 0x004B4830
bool Concurrency::details::VirtualProcessor::IsThrottled(Concurrency::details::VirtualProcessor *this)
{
  return *((_BYTE *)this + 128);
}
