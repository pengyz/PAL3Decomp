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
int sub_433CD0(...);
int sub_433DC0(...);
int sub_434670(...);

// Unnamed globals (extern)
extern int stru_D8C2B8;
extern int unknown_libname_343;
extern int unknown_libname_344;

// 0x00431E60
PalScriptMgr::PalScriptMgr()
{
  unknown_libname_343();
  atexit(sub_431E90);
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
  if ( (stru_D8C2B8.m_keyStates[4] & 8) == 0 )
  {
    stru_D8C2B8.m_keyStates[4] |= 8u;
    ((PtrArray *)&stru_D8C2B8.m_mouseMinX)->Remove();
  }
}

// 0x004320A0
// likely std method (near _Freeze, _Split, max_size, allocator<char>>, _Xran)
void PalScriptMgr::Update(char *a1)
{
  unsigned int v1; // kr04_4
  unsigned int v2; // ebp
  IDirectInputDevice8A *m_lpDIDKeyboard; // edi
  IDirectInputDevice8A v4; // al
  int v5; // [esp+0h] [ebp-Ch]

  if ( ((PtrArray *)&stru_D8C2B8.m_joystickX)->InsertAt(a1) )
  {
    v1 = strlen(a1) + 1;
    v2 = v1 - 1;
    if ( v1 - 1 > 0xFFFFFFFD )
      v5->_Xlen();
    m_lpDIDKeyboard = (IDirectInputDevice8A *)stru_D8C2B8.m_lpDIDKeyboard;
    if ( stru_D8C2B8.m_lpDIDKeyboard && (v4 = stru_D8C2B8.m_lpDIDKeyboard[-1]) != 0 && v4 != 0xFF )
    {
      if ( v1 == 1 )
      {
        stru_D8C2B8.m_lpDIDKeyboard[-1] = (IDirectInputDevice8A)(*(_BYTE *)&v4 - 1);
        stru_D8C2B8.m_lpDIDKeyboard = 0;
        stru_D8C2B8.m_lpDIDMouse = 0;
        stru_D8C2B8.m_mouseSensitivity = 0.0;
        return;
      }
    }
    else
    {
      if ( v1 == 1 )
      {
        ((std *)&stru_D8C2B8)->string::_Tidy(1);
        return;
      }
      if ( LODWORD(stru_D8C2B8.m_mouseSensitivity) <= 0x1F && LODWORD(stru_D8C2B8.m_mouseSensitivity) >= v1 - 1 )
        goto LABEL_15;
      ((std *)&stru_D8C2B8)->string::_Tidy(1);
    }
    ((GRPinput *)&stru_D8C2B8)->GetKeyState(v2);
    m_lpDIDKeyboard = (IDirectInputDevice8A *)stru_D8C2B8.m_lpDIDKeyboard;
LABEL_15:
    qmemcpy(m_lpDIDKeyboard, a1, v2);
    stru_D8C2B8.m_lpDIDMouse = (IDirectInputDevice8A *)(v1 - 1);
    stru_D8C2B8.m_lpDIDKeyboard[v2] = 0;
  }
}

// 0x00432170
int * PalScriptMgr::Destroy(unsigned int a1, char a2)
{
  int *result; // eax
  int *v3; // edi
  _DWORD *v4; // eax
  _DWORD *v5; // esi

  result = (int *)a1;
  if ( a1 )
  {
    if ( a2 )
      result = (int *)sub_433DC0(&stru_D8C2B8.m_mouseMinX, a1, 0);
    else
      result = (int *)a1 >= 0x64 ? sub_433DC0(&stru_D8C2B8.m_joystickX, a1, 0) : sub_433DC0(&stru_D8C2B8.m_mousept.x, a1, 0);
    v3 = result;
    if ( result )
    {
      v4 = (_DWORD *)operator new(0x18u);
      if ( v4 )
        v5 = (_DWORD *)sub_431CB0(v4);
      else
        v5 = 0;
      if ( v5 )
      {
        v5[1] = v3;
        ((PtrArray *)&stru_D8C2B8.m_keyStates[8])->SetAt(*(int *)&stru_D8C2B8.m_keyStates[12], (int)v5);
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
  if ( *(int *)&stru_D8C2B8.m_keyStates[12] <= 0 )
    return 0;
  for ( i = *(int **)&stru_D8C2B8.m_keyStates[8]; ; ++i )
  {
    if ( v1 >= 0 && v1 < *(int *)&stru_D8C2B8.m_keyStates[12] )
    {
      result = *i;
      if ( *i )
      {
        if ( *(_DWORD *)(result + 4) == a1 )
          break;
      }
    }
    if ( ++v1 >= *(int *)&stru_D8C2B8.m_keyStates[12] )
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
    while ( ((PtrArray *)this->m_script.m_pData)->~PtrArray() != 2 )
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
void PalScriptMgr::RunSceneScript(int a2)
{
  int v1; // ebp
  int v2; // ebx
  int v3; // esi
  void **v4; // edi
  int v5; // eax
  int i; // esi

  v1 = *(_DWORD *)&stru_D8C2B8.m_keyStates[12];
  v2 = 0;
  v3 = 0;
  if ( *(int *)&stru_D8C2B8.m_keyStates[12] > 0 )
  {
    do
    {
      if ( v3 < 0 || v3 >= *(int *)&stru_D8C2B8.m_keyStates[12] )
        v4 = 0;
      else
        v4 = *(void ***)(*(_DWORD *)&stru_D8C2B8.m_keyStates[8] + 4 * v3);
      if ( ((PalScriptMgr *)v4)->IsScriptRuning(a2) )
      {
        if ( v4 )
        {
          sub_431CD0(v4);
          operator delete(v4);
        }
        if ( v3 >= 0 && v3 < *(int *)&stru_D8C2B8.m_keyStates[12] )
          *(_DWORD *)(*(_DWORD *)&stru_D8C2B8.m_keyStates[8] + 4 * v3) = 0;
        v2 = 1;
      }
      ++v3;
    }
    while ( v3 < v1 );
    if ( v2 )
    {
      v5 = *(_DWORD *)&stru_D8C2B8.m_keyStates[12];
      for ( i = 0; i < *(int *)&stru_D8C2B8.m_keyStates[12]; v5 = *(_DWORD *)&stru_D8C2B8.m_keyStates[12] )
      {
        if ( i >= 0 && i < v5 && *(_DWORD *)(*(_DWORD *)&stru_D8C2B8.m_keyStates[8] + 4 * i) )
          ++i;
        else
          ((PtrArray *)&stru_D8C2B8.m_keyStates[8])->InsertAt(i, 1);
      }
    }
  }
}

// 0x00432480
int PalScriptMgr::_CON_ReLoadScript()
{
  PalScriptMgr::IfHaveScript();
  PtrArray::SetSize();
  return sub_434670((int)&stru_D8C2B8.m_joystickX);
}

// 0x004324A0
BOOL PalScriptMgr::_CON_CloseScript()
{
  return *(_DWORD *)&stru_D8C2B8.m_keyStates[12] > 0;
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
  if ( *(int *)&stru_D8C2B8.m_keyStates[12] <= 0 )
    return 0;
  for ( i = *(_DWORD **)&stru_D8C2B8.m_keyStates[8]; ; ++i )
  {
    v3 = v1 < 0 || v1 >= *(int *)&stru_D8C2B8.m_keyStates[12] ? 0 : *i;
    if ( v3 == a1 )
      break;
    if ( ++v1 >= *(int *)&stru_D8C2B8.m_keyStates[12] )
      return 0;
  }
  return 1;
}

// 0x00432500
int * PalScriptMgr::FindScriptByDesc(const char *a1, const char *a2)
{
  unsigned int v2; // eax
  int *result; // eax
  char Buffer[64]; // [esp+0h] [ebp-40h] BYREF

  _snprintf(Buffer, 0x3Fu, "_%s_%s", a1, a2);
  v2 = sub_4325A0(Buffer);
  result = (int *)v2->Destroy(0);
  if ( result )
    stru_D8C2B8.m_keyStates[25] = 1;
  return result;
}

// 0x00432550
void PalScriptMgr::IfHaveScript()
{
  int v0; // eax
  int i; // edi
  void *v2; // esi

  v0 = *(_DWORD *)&stru_D8C2B8.m_keyStates[12];
  for ( i = 0; i < v0; ++i )
  {
    if ( i >= 0 && i < v0 )
    {
      v2 = (void *)*(void **)(*(_DWORD *)&stru_D8C2B8.m_keyStates[8] + 4 * i);
      if ( v2 )
      {
        sub_431CD0(*(void ***)(*(_DWORD *)&stru_D8C2B8.m_keyStates[8] + 4 * i));
        operator delete(v2);
        v0 = *(_DWORD *)&stru_D8C2B8.m_keyStates[12];
      }
    }
  }
  String_Assign_4326A0(&stru_D8C2B8.m_keyStates[8], 0, -1);
}
