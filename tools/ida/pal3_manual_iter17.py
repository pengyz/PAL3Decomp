"""
IDAPython: Manual iteration 17 - CCBAI stubs (actually CCBRoleState methods).
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter17_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    (0x004014F0, "CCBAI::Thunk_GetValue",
     "char __stdcall CCBAI::Thunk_GetValue(int a1, int a2)"),
    (0x004EF980, "CCBRoleState::CalcHealAmount",
     "int __thiscall CCBRoleState::CalcHealAmount(CCBRoleState *this, int roleIdx)"),
    (0x004F3570, "CCBRoleState::CalcMagicAttack",
     "int __thiscall CCBRoleState::CalcMagicAttack(CCBRoleState *this, int roleIdx)"),
    (0x004F36D0, "CCBRoleState::CalcMagicDefense",
     "int __thiscall CCBRoleState::CalcMagicDefense(CCBRoleState *this, int roleIdx)"),
    (0x004F4DA0, "CCBRoleState::ProcessAttackResult",
     "int __thiscall CCBRoleState::ProcessAttackResult(CCBRoleState *this, int roleIdx)"),
    (0x004F5070, "CCBRoleState::ProcessMagicResult",
     "int __thiscall CCBRoleState::ProcessMagicResult(CCBRoleState *this, int roleIdx)"),
    (0x004F55D0, "CCBRoleState::CalcPhysicalDamage",
     "int __thiscall CCBRoleState::CalcPhysicalDamage(CCBRoleState *this, int roleIdx)"),
    (0x004F57A0, "CCBRoleState::CalcMagicDamage",
     "int __thiscall CCBRoleState::CalcMagicDamage(CCBRoleState *this, int roleIdx)"),
    (0x004F5970, "CCBRoleState::ProcessSkillEffect",
     "int __thiscall CCBRoleState::ProcessSkillEffect(CCBRoleState *this, int roleIdx)"),
    (0x004F5B70, "CCBRoleState::ProcessItemEffect",
     "int __thiscall CCBRoleState::ProcessItemEffect(CCBRoleState *this, int roleIdx)"),

    # Also fix remaining stubs in other classes
    # CCBSystem (1 stub)
    (0x004FC940, "CCBSystem::GetStageRoleByIdx",
     "char __thiscall CCBSystem::GetStageRoleByIdx(CCBSystem *this, int idx)"),
    # CCBStage (2 stubs)
    (0x004DFAA0, "CCBStage::InitRound",
     "int __thiscall CCBStage::InitRound(CCBStage *this)"),
    (0x004DFED0, "CCBStage::EndRound",
     "int __thiscall CCBStage::EndRound(CCBStage *this)"),
    # PAL3 (2 stubs)
    (0x004118D0, "PAL3::UpdateSubsystems",
     "int __cdecl PAL3::UpdateSubsystems()"),
    (0x0041EE40, "PAL3::UIPostProcess",
     "int __cdecl PAL3::UIPostProcess()"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 17: CCBAI stubs + class cleanup")
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
