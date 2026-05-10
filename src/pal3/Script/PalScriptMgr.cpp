#include "pal3/ida_defs.h"
#include "pal3/globals.h"
#include "pal3/gen/PalScriptMgr.h"
#include "pal3/gen/GRPinput.h"
#include "pal3/gen/PtrArray.h"

// Forward declarations for unnamed functions
int sub_431CB0(...);
int sub_431CD0(...);
int sub_431E90(...);
int sub_4325A0(...);
int sub_4326A0(...);
int sub_433CD0(...);
int sub_433DC0(...);
int sub_434670(...);

// Unnamed globals (extern)
extern unsigned char byte_D8C2B8;
extern unsigned char byte_D8C324;
extern unsigned char byte_D8C339;
extern int dword_D8C2BC;
extern int dword_D8C2C0;
extern int dword_D8C2C4;
extern int dword_D8C2C8;
extern int dword_D8C2E8;
extern int dword_D8C308;
extern int stru_D8C328;
extern int unknown_libname_343;
extern int unknown_libname_344;

// 0x00431E60
PalScriptMgr::PalScriptMgr()
{
  unknown_libname_343();
  return atexit(sub_431E90);
}

// 0x00431EB0
int PalScriptMgr::OpenSCE()
{
  unknown_libname_344();
  return atexit(PalScriptMgr::FindScript);
}

// 0x00431EE0
void PalScriptMgr::FindScript()
{
  if ( (byte_D8C324 & 8) == 0 )
  {
    byte_D8C324 |= 8u;
    dword_D8C2C8->Remove();
  }
}

// 0x004320A0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void PalScriptMgr::Update(const char *a1)
{
  unsigned int v1; // kr04_4
  unsigned int v2; // ebp
  char *v3; // edi
  char v4; // al

  if ( a1->InsertAt() )
  {
    v1 = strlen(a1) + 1;
    v2 = v1 - 1;
    if ( v1 - 1 > 0xFFFFFFFD )
      std::_Xlen();
    v3 = (char *)dword_D8C2BC;
    if ( dword_D8C2BC && (v4 = *(_BYTE *)(dword_D8C2BC - 1)) != 0 && v4 != -1 )
    {
      if ( v1 == 1 )
      {
        *(_BYTE *)(dword_D8C2BC - 1) = v4 - 1;
        dword_D8C2BC = 0;
        dword_D8C2C0 = 0;
        dword_D8C2C4 = 0;
        return;
      }
    }
    else
    {
      if ( v1 == 1 )
      {
        ((std *)&byte_D8C2B8)->string::_Tidy(1);
        return;
      }
      if ( (unsigned int)dword_D8C2C4 <= 0x1F && dword_D8C2C4 >= v1 - 1 )
        goto LABEL_15;
      ((std *)&byte_D8C2B8)->string::_Tidy(1);
    }
    ((int)&byte_D8C2B8)->GetKeyState(v2);
    v3 = (char *)dword_D8C2BC;
LABEL_15:
    qmemcpy(v3, a1, v2);
    dword_D8C2C0 = v1 - 1;
    *(_BYTE *)(dword_D8C2BC + v2) = 0;
  }
}

// 0x00432170
_DWORD * PalScriptMgr::Destroy(unsigned int a1, char a2)
{
  _DWORD *result; // eax
  void *v3; // edi
  _DWORD *v4; // eax
  _DWORD *v5; // esi

  result = (_DWORD *)a1;
  if ( a1 )
  {
    if ( a2 )
      result = (_DWORD *)sub_433DC0(dword_D8C2C8, a1, 0);
    else
      result = (_DWORD *)(a1 >= 0x64 ? sub_433DC0(dword_D8C308, a1, 0) : sub_433DC0(dword_D8C2E8, a1, 0));
    v3 = result;
    if ( result )
    {
      v4 = ((operator *)0x18u)->new();
      if ( v4 )
        v5 = (_DWORD *)sub_431CB0(v4);
      else
        v5 = 0;
      if ( v5 )
      {
        v5[1] = v3;
        ((PtrArray *)MEMORY[0xD8C32C])->SetAt(v5);
        return v5;
      }
      else
      {
        sub_433CD0(v3);
        return 0;
      }
    }
  }
  return result;
}

// 0x00432260
int PalScriptMgr::_CON_State(int a1)
{
  int v1; // ecx
  int *i; // edx
  int result; // eax

  v1 = 0;
  if ( MEMORY[0xD8C32C] <= 0 )
    return 0;
  for ( i = (int *)stru_D8C328; ; ++i )
  {
    if ( v1 >= 0 && v1 < MEMORY[0xD8C32C] )
    {
      result = *i;
      if ( *i )
      {
        if ( *(_DWORD *)(result + 4) == a1 )
          break;
      }
    }
    if ( ++v1 >= MEMORY[0xD8C32C] )
      return 0;
  }
  return result;
}

// 0x004322A0
int PalScriptMgr::IfAnyScriptRunning(int a2)
{
  int result; // eax

  ((PtrArray *)&this->m_script.m_nSize)->SetAt(this->m_script.m_nMaxSize, a2);
  return result;
}

// 0x004322C0
int PalScriptMgr::IsScriptRuning(int a2)
{
  int m_nMaxSize; // eax
  int v5; // ebp
  int v6; // edi
  PtrArray *p_m_nSize; // ebx
  _DWORD *v8; // esi
  int v9; // esi

  m_nMaxSize = this->m_script.m_nMaxSize;
  if ( m_nMaxSize )
  {
    v5 = 0;
    v6 = 0;
    if ( m_nMaxSize > 0 )
    {
      p_m_nSize = (PtrArray *)&this->m_script.m_nSize;
      do
      {
        if ( v6 < 0 || v6 >= p_m_nSize->m_nSize )
          v8 = 0;
        else
          v8 = (_DWORD *)*((_DWORD *)p_m_nSize->m_pData + v6);
        if ( (*(int (**)(_DWORD *))(*v8 + 4))(v8) )
        {
          (*(void (**)(_DWORD *, int))(*v8 + 8))(v8, a2);
        }
        else
        {
          if ( v8[1] && v8 )
            (*(void (**)(_DWORD *, int))*v8)(v8, 1);
          if ( v6 >= 0 && v6 < p_m_nSize->m_nSize )
            *((_DWORD *)p_m_nSize->m_pData + v6) = 0;
          v5 = 1;
        }
        ++v6;
      }
      while ( v6 < this->m_script.m_nMaxSize );
      if ( v5 )
      {
        v9 = 0;
        while ( v9 < this->m_script.m_nMaxSize )
        {
          if ( v9 >= 0 && v9 < p_m_nSize->m_nSize && *((_DWORD *)p_m_nSize->m_pData + v9) )
            ++v9;
          else
            p_m_nSize->InsertAt(v9, 1);
        }
      }
    }
  }
  else
  {
    while ( ((int)this->m_script.m_pData)->~PtrArray() != 2 )
    {
      if ( this->m_script.m_nMaxSize > 0 )
        return 0;
    }
    if ( !this->m_script.m_nMaxSize )
      return 1;
  }
  return 0;
}

// 0x004323C0
void PalScriptMgr::RunSceneScript(int a1)
{
  int v1; // ebp
  int v2; // ebx
  int v3; // esi
  char *v4; // edi
  int v5; // eax
  int i; // esi

  v1 = MEMORY[0xD8C32C];
  v2 = 0;
  v3 = 0;
  if ( MEMORY[0xD8C32C] > 0 )
  {
    do
    {
      if ( v3 < 0 || v3 >= MEMORY[0xD8C32C] )
        v4 = 0;
      else
        v4 = (char *)*(char **)(stru_D8C328 + 4 * v3);
      if ( v4->IsScriptRuning(a1) )
      {
        if ( v4 )
        {
          sub_431CD0(v4);
          operator delete(v4);
        }
        if ( v3 >= 0 && v3 < MEMORY[0xD8C32C] )
          *(_DWORD *)(stru_D8C328 + 4 * v3) = 0;
        v2 = 1;
      }
      ++v3;
    }
    while ( v3 < v1 );
    if ( v2 )
    {
      v5 = MEMORY[0xD8C32C];
      for ( i = 0; i < MEMORY[0xD8C32C]; v5 = MEMORY[0xD8C32C] )
      {
        if ( i >= 0 && i < v5 && *(_DWORD *)(stru_D8C328 + 4 * i) )
          ++i;
        else
          i->InsertAt(1);
      }
    }
  }
}

// 0x00432480
int PalScriptMgr::_CON_ReLoadScript()
{
  PalScriptMgr::IfHaveScript();
  PtrArray::SetSize();
  return sub_434670(dword_D8C308);
}

// 0x004324A0
BOOL PalScriptMgr::_CON_CloseScript()
{
  return MEMORY[0xD8C32C] > 0;
}

// 0x004324B0
int PalScriptMgr::ClearAllScript(int a1)
{
  int v1; // eax
  _DWORD *i; // esi
  int v3; // ecx

  if ( !a1 )
    return 0;
  v1 = 0;
  if ( MEMORY[0xD8C32C] <= 0 )
    return 0;
  for ( i = (_DWORD *)stru_D8C328; ; ++i )
  {
    v3 = v1 < 0 || v1 >= MEMORY[0xD8C32C] ? 0 : *i;
    if ( v3 == a1 )
      break;
    if ( ++v1 >= MEMORY[0xD8C32C] )
      return 0;
  }
  return 1;
}

// 0x00432500
_DWORD * PalScriptMgr::FindScriptByDesc(const char *a1, const char *a2)
{
  unsigned int v2; // eax
  _DWORD *result; // eax
  char Buffer[64]; // [esp+0h] [ebp-40h] BYREF

  _snprintf(Buffer, 0x3Fu, "_%s_%s", a1, a2);
  v2 = sub_4325A0(Buffer);
  result = (_DWORD *)v2->Destroy(0);
  if ( result )
    byte_D8C339 = 1;
  return result;
}

// 0x00432550
int PalScriptMgr::IfHaveScript()
{
  int v0; // eax
  int i; // edi
  void *v2; // esi

  v0 = MEMORY[0xD8C32C];
  for ( i = 0; i < v0; ++i )
  {
    if ( i >= 0 && i < v0 )
    {
      v2 = (void *)*(void **)(stru_D8C328 + 4 * i);
      if ( v2 )
      {
        sub_431CD0(*(char **)(stru_D8C328 + 4 * i));
        operator delete(v2);
        v0 = MEMORY[0xD8C32C];
      }
    }
  }
  return sub_4326A0(0, -1);
}
