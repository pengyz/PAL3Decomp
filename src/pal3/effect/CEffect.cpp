#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/CEffect.h"
#include "pal3/gen/CEffMgr.h"

// Forward declarations for unnamed functions
int sub_4CDCA0(...);

// Unnamed globals (extern)
extern int dword_1895980;
extern int dword_EC9E70;
extern int dword_EC9E74;
extern int nullsub_1;
extern int unk_EC9EB4;

// 0x004CA400
int CEffect::SetParam(int a2)
{
  int v2; // edx
  char v3; // bl
  int v4; // edx

  v2 = *(_DWORD *)(this->m_nPartical + 152 * (int)this->m_Partical[0].pPic);
  v3 = *(_BYTE *)(v2 + 72 * this->m_Partical[0].nQuadIndex + 65);
  v4 = v2 + 72 * this->m_Partical[0].nQuadIndex;
  if ( !v3 )
    *(_BYTE *)(v4 + 65) = 1;
  if ( *(_BYTE *)(v4 + 66) == 1 || *(float *)&this->m_DeltaTime - *(float *)(v4 + 16) >= *(float *)(v4 + 24) )
    *(_DWORD *)(v4 + 8) = 4;
  return 0;
}

// 0x004CE460
int CEffect::Render(int a2)
{
  int result; // eax
  int v3; // esi
  int v4; // ebx
  int v5; // edi
  char *v6; // esi
  int v7; // ebp
  bool v8; // cc
  char *v9; // [esp+8h] [ebp-10h]
  int v11; // [esp+10h] [ebp-8h]
  int v12; // [esp+14h] [ebp-4h]
  int *a2a; // [esp+1Ch] [ebp+4h]

  if ( (g_bCursorVisible & 1) == 0 )
  {
    g_bCursorVisible |= 1u;
    ((CEffMgr *)&g_nCursorState)->Reset();
    atexit(nullsub_1);
  }
  result = dword_1895980;
  if ( dword_1895980 == -1 )
    result = 1;
  v3 = result;
  dword_1895980 = result + 1;
  v12 = result;
  v11 = 0;
  v4 = 3985 * a2;
  if ( dword_EC9E70[3985 * a2] > 0 )
  {
    v9 = (char *)&unk_EC9EB4 + v4 * 4;
    a2a = (int *)&dword_EC9E74[v4];
    do
    {
      v5 = sub_4CDCA0((int *)this, *a2a, v3, 0, 0, 0);
      if ( v5 != -1 )
      {
        v6 = v9;
        v7 = 8;
        do
        {
          if ( v6[88] )
            (*(void (**)(_DWORD, char *))(**((_DWORD **)&this->m_Partical[32].bAniFrame + 5 * v5) + 36))(
              *(&this->m_Partical[32].bAniFrame + 5 * v5),
              v6);
          v6 += 124;
          --v7;
        }
        while ( v7 );
        v3 = v12;
      }
      v8 = ++v11 < dword_EC9E70[v4];
      ++a2a;
      v9 += 992;
    }
    while ( v8 );
    return v3;
  }
  return result;
}
