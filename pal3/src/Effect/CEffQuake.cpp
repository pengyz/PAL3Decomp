#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Effect/CEffQuake.h"

// Forward declarations for unnamed functions
int sub_4D35E0(...);
int sub_4D3660(...);
int sub_4D36C0(...);

// Unnamed globals (extern)
extern int dword_17A7E50;

// 0x004D32C0
int * CEffQuake::Destroy()
{
  CEffShock *v1; // eax
  int v3; // [esp+0x4] [ebp+0x4]

  v1 = (CEffShock *)operator new(0x30u);
  if ( v1 )
    return (int *)((CEffShock *)v1)->GetEditorTaskDescription(v3);
  else
    return 0;
}

// 0x004D3300
int CEffQuake::Update()
{
  CEffObj *v1; // esi
  int result; // eax
  int v3; // ebx
  int v4; // edi

  v1 = this != 0 ? this + 1 : 0;
// [VFTABLE] if ( v1[2].m_pEM || (result = (int)(this != 0 ? (CEffObj *)((char *)this + 44) : (CEffObj *)32)->__vftable) != 0 )
  {
    v3 = 0;
// [VFTABLE] if ( (int)(this != 0 ? (CEffObj *)((char *)this + 40) : (CEffObj *)28)->__vftable > 0 )
    {
      v4 = 0;
      do
      {
// [VFTABLE] operator delete(*(void **)((char *)v1[1].__vftable + v4));
        ++v3;
// [VFTABLE] *(_DWORD *)((char *)v1[1].__vftable + v4) = 0;
        v4 += 152;
      }
      while ( v3 < (int)v1[2].m_pEM );
    }
// [VFTABLE] operator delete(v1[1].__vftable);
// [VFTABLE] v1[1].__vftable = 0;
    v1[2].m_pEM = 0;
    *(_DWORD *)&v1[2].m_bIdle = 0;
    return 0;
  }
  return result;
}

// 0x004D33A0
void CEffQuake::_sub_4D33A0(int a2, int a3, int a4, int a5)
{
  *(this + 8) = 0;
}

// 0x004D33B0
int CEffQuake::RenderEffectPass(int a2)
{
  int result; // eax
  CEffObj *v3; // ebx
  int v4; // ecx
  int v5; // edx
  char *vftable; // esi
  int v7; // ebp
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  _BYTE *v12; // esi
  int ( **v13)(CEffect *, int); // esi
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  _BYTE *v18; // esi
  int ( **v19)(CEffect *, int); // esi
  unsigned int v20; // eax

  v3 = this + 1;
  v4 = *((_DWORD *)this + 10);
  v5 = 0;
  if ( v4 > 0 )
  {
// [VFTABLE] vftable = (char *)v3[1].__vftable;
    result = (int)(vftable + 148);
    while ( *(_BYTE *)result )
    {
      ++v5;
      result += 152;
      if ( v5 >= v4 )
        return result;
    }
    v7 = 152 * v5;
    *(_DWORD *)&vftable[v7 + 12] = 2;
// [VFTABLE] *((_BYTE *)v3[1].__vftable + v7 + 148) = 1;
// [VFTABLE] *((_BYTE *)v3[1].__vftable + v7 + 149) = 1;
    v8 = ++dword_17A7E50;
    if ( !dword_17A7E50 || v8 >= 0x7FFFFFFF )
    {
      v8 = 1;
      dword_17A7E50 = 1;
    }
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 16) = v8;
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 4) = 0;
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 8) = 0;
// [VFTABLE] result = (int)v3[1].__vftable;
    *(_DWORD *)(result + v7 + 20) = 0;
    if ( a2 )
    {
// [VFTABLE] qmemcpy((char *)v3[1].__vftable + v7 + 24, (const void *)a2, 0x7Cu);
    }
    else
    {
      result = 0;
// [VFTABLE] memset((char *)v3[1].__vftable + v7 + 24, 0, 0x7Cu);
    }
// [VFTABLE] ++v3[2].__vftable;
    if ( v5 != -1 )
    {
      v9 = *(_DWORD *)&v3[2].m_bIdle;
      v10 = 0;
      if ( v9 > 0 )
      {
// [VFTABLE] v11 = *((_DWORD *)v3[1].__vftable + 38 * v5);
        v12 = (_BYTE *)(v11 + 64);
        while ( *v12 )
        {
          ++v10;
          v12 += 72;
          if ( v10 >= v9 )
            goto LABEL_22;
        }
        v13 = (int ( **)(CEffect *, int))(v11 + 72 * v10);
        memset(v13, 0, 0x48u);
        *v13 = CEffect::SetParam;
        *((_BYTE *)v13 + 64) = 1;
        *((_BYTE *)v13 + 65) = 0;
        v13[1] = 0;
        v13[2] = (int ( *)(CEffect *, int))2;
        v14 = ++dword_17A7E50;
        if ( !dword_17A7E50 || v14 >= 0x7FFFFFFF )
        {
          v14 = 1;
          dword_17A7E50 = 1;
        }
        v13[3] = (int ( *)(CEffect *, int))v14;
        v13[5] = 0;
        v13[4] = 0;
        v13[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v3[1].__vftable + v7 + 4);
      }
LABEL_22:
      v15 = *(_DWORD *)&v3[2].m_bIdle;
      v16 = 0;
      if ( v15 > 0 )
      {
// [VFTABLE] v17 = *((_DWORD *)v3[1].__vftable + 38 * v5);
        v18 = (_BYTE *)(v17 + 64);
        while ( *v18 )
        {
          ++v16;
          v18 += 72;
          if ( v16 >= v15 )
            goto LABEL_31;
        }
        v19 = (int ( **)(CEffect *, int))(v17 + 72 * v16);
        memset(v19, 0, 0x48u);
        *v19 = CEffect::SetParam;
        *((_BYTE *)v19 + 64) = 1;
        *((_BYTE *)v19 + 65) = 0;
        v19[1] = 0;
        v19[2] = (int ( *)(CEffect *, int))2;
        v20 = ++dword_17A7E50;
        if ( !dword_17A7E50 || v20 >= 0x7FFFFFFF )
        {
          v20 = 1;
          dword_17A7E50 = 1;
        }
        v19[3] = (int ( *)(CEffect *, int))v20;
        v19[5] = 0;
        v19[4] = 0;
        v19[6] = 0;
// [VFTABLE] ++*(_DWORD *)((char *)v3[1].__vftable + v7 + 4);
      }
LABEL_31:
      sub_4D36C0(v5, sub_4D35E0, 0, 0, *(_DWORD *)(a2 + 72), *(_DWORD *)(a2 + 76));
// [VFTABLE] *(_DWORD *)((char *)v3[1].__vftable + v7 + 12) = 3;
// [VFTABLE] *(_DWORD *)(*(_DWORD *)((char *)v3[1].__vftable + v7) + 8) = 3;
// [VFTABLE] result = *(_DWORD *)((char *)v3[1].__vftable + v7);
      *(_DWORD *)(result + 16) = v3->m_pEM;
    }
  }
  return result;
}

// 0x004D3660
int CEffQuake::sub_4D3660(int a2)
{
  int result; // eax

  switch ( a2 )
  {
    case 0:
      result = (int)(&pTarget.m_pfnStageCleanup + 19);
      break;
    case 1:
      result = (int)(&pTarget.m_pfnStageCleanup + 16);
      break;
    case 2:
      result = (int)(&pTarget.m_pfnStageCleanup + 13);
      break;
    case 9:
      result = (int)&g_EffEditorState;
      break;
    default:
      result = (int)&g_EffCylinderEditorData;
      break;
  }
  return result;
}
