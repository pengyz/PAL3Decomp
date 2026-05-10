#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PAL_GDB.h"
#include "pal3/gen/PalScript.h"

// Unnamed globals (extern)
extern char aSec1[];
extern unsigned char byte_DC333C;
extern void *off_58B448;

// 0x00457410
char PAL_GDB::LoadLanguage(char *path)
{
  PalScript *v3; // esi
  char *v4; // edi

  v3 = (PalScript *)&this->m_ItemData[360].desc[440];
  ((PalScript *)&this->m_ItemData[360].desc[440])->LoadFromFile(path);
  v3->SetDirectory(aSec1);
  if ( v3->HasNext() )
  {
    v4 = byte_DC333C;
    do
    {
      if ( !_strcmpi(off_58B448, (const char *)v3) )
        break;
      v3->LoadNext();
      strncpy(v4, (const char *)v3, 0x100u);
      v4 += 256;
    }
    while ( v3->HasNext() );
  }
  this->m_ItemData[360].desc[436] = 1;
  return 1;
}
