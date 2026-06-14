#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Combat/CCBControl.h"

// 0x004DC240
int CCBControl::GetActiveAttackCount()
{
  int result; // eax

  LOBYTE(result) = this->m_bActive;
  if ( (_BYTE)result )
    LOBYTE(result) = ((CCBUI *)this)->CountAttackSequences();
  return result;
}

// 0x004DC560
int CCBControl::GetState()
{
  int result; // eax

  LOBYTE(result) = this->m_bForceRelease;
  if ( !(_BYTE)result )
  {
    this->m_bForceRelease = 1;
    return ((CCBSystem *)this)->FindFreeThread(0 /* TODO: (int)CCBRoleState::ExecuteCombatCommand */, 0, 0, 0, 0, 0, 0, -1, 0);
  }
  return result;
}

// 0x004DC5B0
int CCBControl::GetControl()
{
  return this->m_nController;
}

// 0x004DC5C0
int CCBControl::SetParam(int nVal, int nVal2)
{
  int result; // eax
  unsigned int v4; // [esp+0x10] [ebp+0xC]

  result = nVal;
  this->m_InputData.dwParam1 = nVal2;
  this->m_InputData.bValid = 1;
  this->m_InputData.dwButtonID = nVal;
  this->m_InputData.dwParam2 = v4;
  switch ( nVal )
  {
    case 259:
    case 260:
    case 261:
    case 262:
    case 265:
    case 267:
      this->m_InputData.dwButtonID = nVal;
      break;
    default:
      return result;
  }
  return result;
}
