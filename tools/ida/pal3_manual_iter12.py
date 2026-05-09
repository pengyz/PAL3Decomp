"""
IDAPython: Manual iteration 12.
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter12_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    (0x00536D20, "Actor::LoadModel",
     "void * __thiscall Actor::LoadModel(void *this)"),
    (0x00536FD0, "Actor::PlayAction",
     "int __thiscall Actor::PlayAction(void *this, int actionId)"),
    (0x004F3AD0, "CCBRoleState::CalcMPCost",
     "int __thiscall CCBRoleState::CalcMPCost(CCBRoleState *this, int roleIdx)"),
    (0x004DB6E0, "CCBSystem::IsCmdEmpty",
     "bool __thiscall CCBSystem::IsCmdEmpty(CCBSystem *this, int idx)"),
    (0x004DB6C0, "CCBSystem::IsCmdReady",
     "bool __thiscall CCBSystem::IsCmdReady(CCBSystem *this, int idx)"),
    (0x004A14D0, "UIItem::SetData",
     "void * __thiscall UIItem::SetData(void *this, char a2)"),
    (0x004A16C0, "UIItem::Create",
     "int __thiscall UIItem::Create(void *this, int id, int a3)"),
    (0x004A4890, "UIBase::GetSelected",
     "int __thiscall UIBase::GetSelected(void *this)"),
    (0x0044F8A0, "CGameData::SetMode",
     "int __thiscall CGameData::SetMode(CGameData *this, int mode)"),
    (0x005371B0, "Actor::SetVisible",
     "void __thiscall Actor::SetVisible(void *this, int bVisible)"),
    (0x004DB780, "CCBSystem::GetCmdCount",
     "int __thiscall CCBSystem::GetCmdCount(CCBSystem *this, int idx)"),
    (0x004DB6A0, "CCBSystem::IsBusy",
     "bool __thiscall CCBSystem::IsBusy(CCBSystem *this)"),
    (0x004DC560, "CCBUI::GetState",
     "int __thiscall CCBUI::GetState(CCBUI *this)"),
    (0x004ED100, "CCBRoleState::GetForce",
     "int __thiscall CCBRoleState::GetForce(CCBRoleState *this, int roleIdx)"),
    (0x004F0530, "CCBRoleState::GetRoleNum",
     "int __thiscall CCBRoleState::GetRoleNum(CCBRoleState *this)"),
    (0x004F2910, "CCBRoleState::SetRoleHP",
     "int __thiscall CCBRoleState::SetRoleHP(CCBRoleState *this, int roleIdx, int value)"),
    (0x004F98B0, "CCBRoleState::ApplyDamage",
     "int __thiscall CCBRoleState::ApplyDamage(CCBRoleState *this, int roleIdx, int dmg)"),
    (0x004FA6A0, "CCBRoleState::CheckDeath",
     "int __thiscall CCBRoleState::CheckDeath(CCBRoleState *this, int roleIdx)"),
    (0x004FA8B0, "CCBRoleState::Revive",
     "int __thiscall CCBRoleState::Revive(CCBRoleState *this, int roleIdx)"),
    (0x00500170, "CCBSystem::EndBattle",
     "int __thiscall CCBSystem::EndBattle(CCBSystem *this)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 12")
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
