// PAL3.exe Combat/CBSystem.cpp - CCBSystem class methods
// Compiler: MSVC 6.0 SP0 (cl.exe 12.00.8168)
// Source: D:\PAL3A\PAL3\Combat\CBSystem.cpp (from PAL3A PDB)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "pal3/CCBSystem.h"

// ========================================================================
// CCBSystem::ProcUseItem
// Address: 0x00513380, Size: 16 bytes, Status: matched
// ========================================================================

class CCBStage {
public:
    unsigned long ProcUseItem(unsigned long hwnd);
};

unsigned long CCBSystem::ProcUseItem(unsigned long hwnd)
{
    return m_pStage->ProcUseItem(hwnd);
}

// === STUB: CCBSystem::~CCBSystem (nullsub) ===
CCBSystem::~CCBSystem() {}

// === STUB: CCBSystem::ProcFling ===
void CCBSystem::ProcFling(void) {}
