// PAL3.exe Combat/CBSystem.cpp - CCBSystem class methods
// Compiler: MSVC 6.0 SP0 (cl.exe 12.00.8168)
// Source: D:\PAL3A\PAL3\Combat\CBSystem.cpp (from PAL3A PDB)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// ========================================================================
// CCBSystem::ProcUseItem
// Address: 0x00513380, Size: 16 bytes
// Mangled: ?ProcUseItem@CCBSystem@@QAEKK@Z
// Original asm:
//   8B 44 24 04   mov eax, [esp+4]     ; eax = hwnd argument
//   8B 49 1C      mov ecx, [ecx+0x1C]  ; ecx = this->m_pStage
//   50            push eax              ; push hwnd
//   E8 xx xx xx   call CCBStage::ProcUseItem (0x004E0530)
//   C2 04 00      ret 4                 ; clean 1 stack arg
// ========================================================================

class CCBStage {
public:
    unsigned long ProcUseItem(unsigned long hwnd);
};

class CCBSystem {
public:
    char _pad[0x1C];
    CCBStage *m_pStage;  // offset 0x1C

    unsigned long ProcUseItem(unsigned long hwnd);
};

unsigned long CCBSystem::ProcUseItem(unsigned long hwnd)
{
    return m_pStage->ProcUseItem(hwnd);
}
