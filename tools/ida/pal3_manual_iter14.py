"""
IDAPython: Manual iteration 14 - CCBRoleState methods (0x4F3000 area).
All operate on tagRoleState[11] array (stride 892).
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter14_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    (0x004F3020, "CCBRoleState::CalcAttackPower",
     "int __thiscall CCBRoleState::CalcAttackPower(CCBRoleState *this, int roleIdx)"),
    (0x004F31C0, "CCBRoleState::CalcDefensePower",
     "int __thiscall CCBRoleState::CalcDefensePower(CCBRoleState *this, int roleIdx)"),
    (0x004F3380, "CCBRoleState::GetMaxHP",
     "int __thiscall CCBRoleState::GetMaxHP(CCBRoleState *this, int roleIdx)"),
    (0x004F33D0, "CCBRoleState::GetMaxMP",
     "int __thiscall CCBRoleState::GetMaxMP(CCBRoleState *this, int roleIdx)"),
    (0x004F3420, "CCBRoleState::GetTotalRounds",
     "int __thiscall CCBRoleState::GetTotalRounds(CCBRoleState *this)"),
    (0x004F34E0, "CCBRoleState::CanUseSkill",
     "char __thiscall CCBRoleState::CanUseSkill(CCBRoleState *this, int roleIdx)"),
    (0x004F3620, "CCBRoleState::CalcMPRegen",
     "int __thiscall CCBRoleState::CalcMPRegen(CCBRoleState *this, int roleIdx)"),
    (0x004F37A0, "CCBRoleState::GetAttackBonus",
     "int __thiscall CCBRoleState::GetAttackBonus(CCBRoleState *this, int roleIdx)"),
    (0x004F3820, "CCBRoleState::GetDefenseBonus",
     "int __thiscall CCBRoleState::GetDefenseBonus(CCBRoleState *this, int roleIdx)"),
    (0x004F3920, "CCBRoleState::GetSpeedBonus",
     "int __thiscall CCBRoleState::GetSpeedBonus(CCBRoleState *this, int roleIdx)"),
    (0x004F39A0, "CCBRoleState::GetRoleLevel",
     "int __thiscall CCBRoleState::GetRoleLevel(CCBRoleState *this, int roleIdx)"),
    (0x004F39F0, "CCBRoleState::GetRoleExp",
     "int __thiscall CCBRoleState::GetRoleExp(CCBRoleState *this, int roleIdx)"),
    (0x004F3A30, "CCBRoleState::SetRoleFlag",
     "char __thiscall CCBRoleState::SetRoleFlag(CCBRoleState *this, int roleIdx, char flag)"),
    (0x004F3AD0, "CCBRoleState::CalcMPCost",
     "int __thiscall CCBRoleState::CalcMPCost(CCBRoleState *this, int roleIdx)"),
    (0x004F3C20, "CCBRoleState::IsPlayerTeam",
     "char __stdcall CCBRoleState::IsPlayerTeam(int force)"),
    (0x004F3C70, "CCBRoleState::GetRoleForce",
     "char __thiscall CCBRoleState::GetRoleForce(CCBRoleState *this, int roleIdx)"),
    (0x004F3CC0, "CCBRoleState::IsRoleInForce",
     "bool __thiscall CCBRoleState::IsRoleInForce(CCBRoleState *this, int roleIdx)"),
    (0x004F3D10, "CCBRoleState::CanRoleAct",
     "char __thiscall CCBRoleState::CanRoleAct(CCBRoleState *this, int roleIdx)"),
    (0x004F3DC0, "CCBRoleState::GetRoleSpeed",
     "int __thiscall CCBRoleState::GetRoleSpeed(CCBRoleState *this, int roleIdx)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 14: CCBRoleState methods")
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
