#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/String.h"
#include "Misc/ScriptSystemData.h"

// 0x004326A0
void String::Assign(char *src, int len)
{
  // [overlay-fix 2026-10-27] 整函数垃圾形（String 作标量强转 ×8 / C2451 ×2）批量注释——待语义修复
  //     String *_this = this;
  //   String v5; // eax
  //   String v6; // eax
  //   String v7; // eax
  //   char *srca; // [esp+0x10] [ebp+0x4]
  //   String lena; // [esp+0x14] [ebp+0x8]

  //   if ( len > 0 )
  //     _this[3] = (String)len;
  //   v5 = *_this;
  //   if ( src )
  //   {
  //     if ( v5 )
  //     {
  //       if ( (int)src > *(_DWORD *)&_this[2] )
  //       {
  //         lena = (String)src;
  //         if ( (int)src <= *(_DWORD *)&_this[3] + *(_DWORD *)&_this[1] )
  //           lena = (g_ScriptSystemData.m_String)(*(_DWORD *)&_this[3] + *(_DWORD *)&_this[1]);
  //         srca = (char *)malloc(4 * *(_DWORD *)&lena);
  //         qmemcpy(srca, *(const void **)_this, 4 * *(_DWORD *)&_this[1]);
  //         free(*(void **)_this);
  //         _this[1] = (String)src;
  //         *_this = (String)srca;
  //         _this[2] = lena;
  //       }
  //       else
  //       {
  //         _this[1] = (String)src;
  //       }
  //     }
  //     else
  //     {
  //       v6 = _this[3];
  //       _this[1] = (String)src;
  //       v7 = (g_ScriptSystemData.m_String)&src[*(_DWORD *)&v6];
  //       _this[2] = v7;
  //       *_this = (String)malloc(4 * *(_DWORD *)&v7);
  //     }
  //   }
  //   else
  //   {
  //     if ( v5 )
  //     {
  //       free(*(void **)_this);
  //       *_this = 0;
  //     }
  //     _this[2] = 0;
  //     _this[1] = 0;
  //   }
}
