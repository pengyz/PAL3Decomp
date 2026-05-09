"""
IDAPython: Manual iteration 10 - Fix remaining high-frequency functions.
Also fixes CEffMgr_sub_4D58A0 style names from bad xref propagation.

Usage:
  idat.exe -A -S"pal3_manual_iter10.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter10_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # CEffMgr (fix bad name from xref propagation)
    (0x004D58A0, "CEffMgr::Reset",
     "_DWORD * __thiscall CEffMgr::Reset(CEffMgr *this)"),

    # CCBSystem array accessors (stride 40)
    (0x004DB920, "CCBSystem::SetCmdParam",
     "int __thiscall CCBSystem::SetCmdParam(CCBSystem *this, int idx, int value)"),
    (0x004DB710, "CCBSystem::GetCmdPtr",
     "char * __thiscall CCBSystem::GetCmdPtr(CCBSystem *this, int idx)"),
    (0x004DB750, "CCBSystem::GetCmdData",
     "char * __thiscall CCBSystem::GetCmdData(CCBSystem *this, int idx)"),

    # CCBStageRole
    (0x0053E310, "CCBStageRole::PlaySound",
     "void __thiscall CCBStageRole::PlaySound(CCBStageRole *this, char *name, int a3)"),

    # CCBSystem (stride 22*a2+38)
    (0x00515C50, "CCBSystem::ClearEffect",
     "char __thiscall CCBSystem::ClearEffect(CCBSystem *this, int idx)"),

    # CCBUI
    (0x004DC5C0, "CCBUI::SetParam",
     "int __thiscall CCBUI::SetParam(CCBUI *this, int a2, int a3)"),

    # CCBRoleState (2400B - big state update)
    (0x004F3E20, "CCBRoleState::ProcessRound",
     "char __thiscall CCBRoleState::ProcessRound(CCBRoleState *this, unsigned int a2)"),

    # CCBRoleState helper
    (0x004EFFC0, "CCBRoleState::IsRoleReady",
     "bool __thiscall CCBRoleState::IsRoleReady(CCBRoleState *this, int roleIdx)"),

    # CCBSystem (stride 658 for stage role)
    (0x004FC8F0, "CCBSystem::GetStageRole",
     "char __thiscall CCBSystem::GetStageRole(CCBSystem *this, int idx)"),

    # RoleSystem animation
    (0x00412940, "RoleSystem::UpdatePath",
     "int __thiscall RoleSystem::UpdatePath(RoleSystem *this, int a2)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 10: Fix high-frequency remaining")
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
