#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/CCBEditor.h"

// 0x0044B630
int CCBEditor::UpdateItemScript(CHAR *lpString2, int nVal, int nVal2, int nVal3)
{
  int result; // eax
  CHAR *v7; // [esp+0x0] [ebp-0x4]

  ((PalScript *)&this->m_NewItem[463].fnHP)->SetDialogTemplate(lpString2, v7);
  this->m_dwTrickID[352] = nVal;
  this->m_dwTrickID[353] = nVal2;
  this->m_dwTrickID[354] = nVal3;
  if ( this )
    ((void ( *)(CCBEditor *, int, int, _DWORD))this->m_fpThis->m_NewItem[1].dwItemID)(this, 1000, 1, 0);
  result = ((RoleSystem *)this)->ProcessWaypoint();
  LOBYTE(this->m_dwTrickID[358]) = 1;
  return result;
}

// 0x0044B690
int CCBEditor::InvokeItemMethod()
{
  int ( **p_fnHP)(void *, unsigned int); // edi
  int v3; // ebx
  int result; // eax

  (*(void ( **)(float *, _DWORD))LODWORD(this->m_NewItem[54].fMP))(&this->m_NewItem[54].fMP, 0);
  (*(void ( **)(int ( **)(void *, unsigned int), _DWORD))this->m_NewItem[76].fnHP)(
    &this->m_NewItem[76].fnHP,
    0);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_NewItem[97].fMP))(&this->m_NewItem[97].fMP, 0);
  (*(void ( **)(int ( **)(void *, unsigned int), _DWORD))this->m_NewItem[7].fnHP)(
    &this->m_NewItem[7].fnHP,
    0);
  (*(void ( **)(float *, _DWORD))LODWORD(this->m_NewItem[16].fMP))(&this->m_NewItem[16].fMP, 0);
  p_fnHP = &this->m_NewItem[26].fnHP;
  v3 = 3;
  do
  {
    result = (*(int ( **)(_DWORD, _DWORD))*p_fnHP)(p_fnHP, 0);
    p_fnHP += 38;
    --v3;
  }
  while ( v3 );
  LOBYTE(this->m_NewItem[463].dwItemID) = 1;
  LOBYTE(this->m_dwTrickID[358]) = 0;
  return result;
}
