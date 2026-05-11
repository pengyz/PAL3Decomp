#pragma once
// Auto-generated: PalScriptMgr

#include "PtrArray.h"
#include "scSCEFile.h"

class PalScriptMgr {
public:
    BYTE m_bGetSceneScript; // +0x0
    PtrArray m_script; // +0x0
    scSCEFile m_scefile; // +0x0
    scSCEFile m_scesys; // +0x0
    int m_scepath; // +0x0 (std::basic_string<char,std::char_traits<char>,std::allocator<char> >)
    scSCEFile m_bigmapsce; // +0x0
    // total size: 0x1 (1)

    PalScriptMgr(); // 0x00431E60
    static int OpenSCE(); // 0x00431EB0
    static void FindScript(); // 0x00431EE0
    static void Update(char *a1); // 0x004320A0
    static int * Destroy(unsigned int a1, char a2); // 0x00432170
    int IfAnyScriptRunning(int a2); // 0x004322A0
    int IsScriptRuning(int a2); // 0x004322C0
    static void RunSceneScript(int a2); // 0x004323C0
    static int ClearAllScript(int a1); // 0x004324B0
    static int * FindScriptByDesc(const char *a1, const char *a2); // 0x00432500
    static void IfHaveScript(); // 0x00432550
};
