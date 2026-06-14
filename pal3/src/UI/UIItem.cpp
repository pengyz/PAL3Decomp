#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "UI/UIItem.h"

// Forward declarations for unnamed functions
void * sub_446010(void *a2); // from annotations

// 0x004A14D0
void * UIItem::SetData(char pData)
{
  return sub_446010((char *)this + 456);
}
