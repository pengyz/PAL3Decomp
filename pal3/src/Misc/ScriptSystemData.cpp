#include "pal3/ida_defs.h"
#include "globals.h"
#include "pal3/pal3_constants.h"
#include "Misc/ScriptSystemData.h"

// 0x0051F070
int ScriptSystemData::Update(int deltatime)
{
  this->m_CmdTable[223].flags = deltatime;
  return deltatime;
}

// 0x0051F080
void ScriptSystemData::CCBResultWindow(int nVal)
{
  *(_DWORD *)&this->m_CmdTable[224].cmd_id = nVal;
}

// 0x0051F090
void ScriptSystemData::_CCBResultWindow(int nVal)
{
  this->m_CmdTable[224].handler = nVal;
}
