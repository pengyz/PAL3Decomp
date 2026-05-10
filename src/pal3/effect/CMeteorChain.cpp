#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CMeteorChain.h"

// Unnamed globals (extern)
extern int dword_DE9CA8;

// 0x004CD0A0
CMeteorChain::CMeteorChain()
{
  _DWORD *v2; // esi
  void *v3; // eax

  v2 = (_DWORD *)*(_DWORD **)&this->m_pEM[20];
  while ( v2 )
  {
    v3 = v2;
    v2 = (_DWORD *)v2[8];
    operator delete(v3);
  }
  if ( *(_DWORD *)&this->m_pEM[4] )
    operator delete(*(void **)&this->m_pEM[4]);
}

// 0x004CD7E0
int CMeteorChain::Update(int a2, int a3, int a4, _DWORD *a5, int a6, int a7)
{
  float m_fLastTime; // ecx
  int v9; // esi
  gbTexture *v10; // edx
  __int32 *i; // eax
  int *v13; // edx
  unsigned int v14; // eax
  _DWORD *v15; // edx

  m_fLastTime = this->m_fLastTime;
  v9 = 0;
  if ( SLODWORD(m_fLastTime) <= 0 )
    return -1;
  v10 = (gbTexture *)this->m_pTextureArray->pTexPt[38 * a2];
  for ( i = &v10->InFmt.r_mask; *(_BYTE *)i; i += 18 )
  {
    if ( ++v9 >= SLODWORD(m_fLastTime) )
      return -1;
  }
  v13 = (int *)&v10->RefCount + 18 * v9;
  memset(v13, 0, 0x48u);
  *((_BYTE *)v13 + 65) = 0;
  *((_BYTE *)v13 + 64) = 1;
  *v13 = a3;
  v13[1] = a4;
  v13[2] = 2;
  v14 = ++dword_DE9CA8;
  if ( !dword_DE9CA8 || v14 >= 0x7FFFFFFF )
  {
    v14 = 1;
    dword_DE9CA8 = 1;
  }
  v13[3] = v14;
  v13[4] = 0;
  v13[5] = a6;
  v13[6] = a7;
  if ( a5 )
  {
    v15 = (_DWORD *)v13 + 7;
    * v15 = (*)*a5;
    v15[1] = a5[1];
    v15[2] = a5[2];
    v15[3] = a5[3];
  }
  ++this->m_pTextureArray->pTexPt[38 * a2 + 1];
  return v9;
}
