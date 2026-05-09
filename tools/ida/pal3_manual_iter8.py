"""
IDAPython: Manual iteration 8 - Combat subsystem depth 3.
CCBUI/CCBStage/CCBAttackSequen/CCBRoleState internal methods.

Usage:
  idat.exe -A -S"pal3_manual_iter8.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter8_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # CCBUI internal methods (this-source: CCBUI::Update passes its own this)
    (0x004E0690, "CCBUI::UpdateInput",
     "char __thiscall CCBUI::UpdateInput(CCBUI *this)"),
    (0x004E0740, "CCBUI::UpdateDisplay",
     "char __thiscall CCBUI::UpdateDisplay(CCBUI *this)"),
    (0x004E0820, "CCBUI::UpdateAnimation",
     "char __thiscall CCBUI::UpdateAnimation(CCBUI *this)"),
    (0x004E0980, "CCBUI::UpdateState",
     "char __thiscall CCBUI::UpdateState(CCBUI *this)"),
    (0x00513330, "CCBSystem::GetRenderFlag",
     "int __cdecl CCBSystem::GetRenderFlag()"),
    (0x00513390, "CCBSystem::SetRenderFlag",
     "int __thiscall CCBSystem::SetRenderFlag(CCBSystem *this, char flag)"),

    # CCBStage internal methods
    (0x00503CF0, "CCBStage::UpdatePhysics",
     "int __thiscall CCBStage::UpdatePhysics(CCBStage *this)"),
    (0x005045B0, "CCBStage::ProcessTurn",
     "char __thiscall CCBStage::ProcessTurn(CCBStage *this)"),

    # CCBAttackSequen internal methods
    (0x004DBA60, "CCBAttackSequen::ProcessQueue",
     "char __thiscall CCBAttackSequen::ProcessQueue(CCBAttackSequen *this)"),
    (0x004DBB20, "CCBAttackSequen::CheckComplete",
     "char __thiscall CCBAttackSequen::CheckComplete(CCBAttackSequen *this)"),
    (0x004DBD40, "CCBAttackSequen::AdvanceStep",
     "int __thiscall CCBAttackSequen::AdvanceStep(CCBAttackSequen *this)"),

    # CCBRoleState internal methods
    (0x004F7880, "CCBRoleState::CheckStatus",
     "unsigned int __thiscall CCBRoleState::CheckStatus(CCBRoleState *this)"),
    (0x004F7910, "CCBRoleState::ProcessActions",
     "void * __thiscall CCBRoleState::ProcessActions(CCBRoleState *this)"),
    (0x004F8480, "CCBRoleState::UpdateEffects",
     "int __thiscall CCBRoleState::UpdateEffects(CCBRoleState *this)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 8: Combat depth 3")
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
