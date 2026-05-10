#include "pal3/ida_defs.h"
#include "pal3/globals.h"

// 0x00553549
void `eh vector destructor iterator'(char *a1, unsigned int a2, int a3, void ( *a4)(void *))
{
  char *i; // [esp+30h] [ebp+8h]

  for ( i = &a1[a3 * a2]; --a3 >= 0; a4(i) )
    i -= a2;
}

// 0x00553627
void `eh vector constructor iterator'(
        char *a1,
        unsigned int a2,
        int a3,
        void (*a4)(void *),
        void (*a5)(void *))
{
  int i; // [esp+10h] [ebp-1Ch]

  for ( i = 0; i < a3; ++i )
  {
    a4(a1);
    a1 += a2;
  }
}
