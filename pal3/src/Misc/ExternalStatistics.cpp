#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ExternalStatistics.h"

// Forward declarations for unnamed functions
int todo_408BD0(...);

// 0x00534DD0
int ExternalStatistics::CheckKeyPress(int nParam)
{
  int result; // eax

  result = g_Input.KeyInfo[nParam].Data & 0xF;
  if ( result == 1
    || g_Input.KeyInfo[nParam].PressTime == 1
    || (g_Input.KeyInfo[nParam].Data & 0xFu) > 1
    || (LOWORD(result) = ((GRPinput *)&g_Input)->GetKeyState(nParam), (_WORD)result == 2) )
  {
    *((_BYTE *)this + 4) = 1;
    LOBYTE(result) = 1;
  }
  else
  {
    LOBYTE(result) = 0;
  }
  return result;
}

// 0x00534E30
int ExternalStatistics::Reset(int nParam)
{
  int result; // eax

  if ( !*((_BYTE *)this + 4) || (result = 16 * nParam, g_Input.KeyInfo[nParam].Data) )
  {
    LOBYTE(result) = 0;
  }
  else
  {
    *((_BYTE *)this + 4) = 0;
    LOBYTE(result) = 1;
  }
  return result;
}

// 0x00534E60
void ExternalStatistics::UpdateFromRole(int nVal, int nVal2)
{
  void *v4; // [esp+0x0] [ebp-0x4]

  if ( (unsigned __int8)this->CheckKeyPress(2) )
  {
    ((RoleSystem *)*(RoleSystem **)this)->GetStateMode();
  }
  else if ( (unsigned __int8)this->CheckKeyPress(3) )
  {
    ((RoleSystem *)*(RoleSystem **)this)->NegateStateMode();
  }
  else if ( (unsigned __int8)this->Reset(2) || (unsigned __int8)this->Reset(3) )
  {
// [IDA_MISID]     ((Concurrency *)*(Concurrency::details::ExternalStatistics **)this)->details::ExternalStatistics::MarkInactive();
  }
  if ( (unsigned __int8)this->CheckKeyPress(4) )
    todo_408BD0(v4);
  if ( (unsigned __int8)this->CheckKeyPress(5) )
    todo_408BD0(v4);
}
