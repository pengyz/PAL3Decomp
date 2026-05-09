"""
IDAPython: Manual iteration 15 - CCBSystem command system (0x4DB000 area).
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter15_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # Thunks
    (0x004DB3A0, "CCBSystem::InitCmdTable1_thunk", "int __cdecl CCBSystem::InitCmdTable1_thunk()"),
    (0x004DB3B0, "CCBSystem::InitCmdTable1", "int __cdecl CCBSystem::InitCmdTable1()"),
    (0x004DB3F0, "CCBSystem::InitCmdTable2_thunk", "int __cdecl CCBSystem::InitCmdTable2_thunk()"),
    (0x004DB400, "CCBSystem::InitCmdTable2", "int __cdecl CCBSystem::InitCmdTable2()"),
    (0x004DB440, "CCBSystem::InitCmdTable3_thunk", "int __cdecl CCBSystem::InitCmdTable3_thunk()"),
    (0x004DB450, "CCBSystem::InitCmdTable3", "int __cdecl CCBSystem::InitCmdTable3()"),

    # CCBSystem init/destroy
    (0x004DB490, "CCBSystem::InitCmd",
     "void * __thiscall CCBSystem::InitCmd(CCBSystem *this, int a2)"),
    (0x004DB4C0, "CCBSystem::ResetFlags",
     "int __thiscall CCBSystem::ResetFlags(CCBSystem *this)"),
    (0x004DB4F0, "CCBSystem::DestroySubsystems",
     "char __thiscall CCBSystem::DestroySubsystems(CCBSystem *this)"),

    # Utility
    (0x004DB640, "CCBSystem::CalcSpeed",
     "int __stdcall CCBSystem::CalcSpeed(int roleIdx, int a2)"),
    (0x004DB660, "CCBSystem::GetCmdSlot",
     "int __thiscall CCBSystem::GetCmdSlot(CCBSystem *this, int idx)"),
    (0x004DB690, "CCBSystem::GetCmdType",
     "char __thiscall CCBSystem::GetCmdType(CCBSystem *this, int idx)"),
    (0x004DB700, "CCBSystem::GetCmdValue",
     "int __thiscall CCBSystem::GetCmdValue(CCBSystem *this, int idx)"),
    (0x004DB7A0, "CCBSystem::ProcessAllCmds",
     "int __thiscall CCBSystem::ProcessAllCmds(CCBSystem *this)"),
    (0x004DB8B0, "CCBSystem::GetCmdString",
     "char * __thiscall CCBSystem::GetCmdString(CCBSystem *this, int idx)"),

    # More CCBSystem (from remaining)
    (0x004DB950, "CCBSystem::SetCmdType",
     "int __thiscall CCBSystem::SetCmdType(CCBSystem *this, int idx, int type)"),
    (0x004DB970, "CCBSystem::ClearCmd",
     "int __thiscall CCBSystem::ClearCmd(CCBSystem *this, int idx)"),
    (0x004DB9A0, "CCBSystem::AddCmd",
     "int __thiscall CCBSystem::AddCmd(CCBSystem *this, int type, int target)"),
    (0x004DBA00, "CCBSystem::RemoveCmd",
     "int __thiscall CCBSystem::RemoveCmd(CCBSystem *this, int idx)"),
    (0x004DBA30, "CCBSystem::GetActiveCmdCount",
     "int __thiscall CCBSystem::GetActiveCmdCount(CCBSystem *this)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 15: CCBSystem command system")
        named = 0
        sigs = 0
        for entry in ANNOTATIONS:
            addr, name = entry[0], entry[1]
            sig = entry[2] if len(entry) > 2 else None
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1
                log("  [+] 0x%08X: %s" % (addr, name))
            if sig and idc.SetType(addr, sig):
                sigs += 1
        log("[*] Named: %d, Sigs: %d" % (named, sigs))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] Done")
    except Exception as e:
        log("[!] %s" % str(e))
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
