#include "pal3/ida_defs.h"
#include "pal3/globals.h"

// Unnamed globals (extern)
extern int dword_1895304;

// 0x00541D10
void operator delete(void *Block)
{
  free(Block);
}

// 0x00547B27
void operator delete()
{
  int v0; // ebx
  _DWORD *v1; // esi
  _DWORD *v2; // eax
  _DWORD *v3; // edi

  v0 = 0;
  if ( !dword_1895304 )
  {
    dword_1895304 = 1;
    v1 = (_DWORD *)operator new(0);
    v2 = (_DWORD *)operator new(0);
    v3 = v2;
    if ( !v1 || !v2 || v1 == v2 )
      v0 = 1;
    if ( v1 )
      operator delete(v1);
    if ( v3 && v3 != v1 )
      operator delete(v3);
    operator delete(0);
    if ( v0 )
    {
      OutputDebugStringA("D3DX: (WARN) Overloaded ::new and ::delete operators do not conform to C++ standards:\r\n");
      OutputDebugStringA("D3DX: (WARN) An allocation of zero bytes should return a unique non-null pointer to at\r\n");
      OutputDebugStringA("D3DX: (WARN) least zero bytes. Deletion of a null pointer should quietly do nothing.\r\n");
      OutputDebugStringA("D3DX: (WARN) D3DX relies upon this behavior.\r\n");
    }
  }
}
