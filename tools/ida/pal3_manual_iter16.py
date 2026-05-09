"""
IDAPython: Manual iteration 16.
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter16_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    (0x004A1410, "UIItem::UIItem",
     "void __thiscall UIItem::UIItem(void *this)"),
    (0x0050A980, "CCBStageRole::IsReady",
     "bool __thiscall CCBStageRole::IsReady(CCBStageRole *this, int idx)"),
    (0x004DFE00, "CCBAIWindow::SetText",
     "int __thiscall CCBAIWindow::SetText(void *this, int a2, int a3)"),
    (0x004F3C00, "CCBRoleState::IsForce1",
     "int __stdcall CCBRoleState::IsForce1(int force)"),
    (0x004CE460, "CEffect::Render",
     "int __thiscall CEffect::Render(void *this, int a2)"),
    (0x004A12F0, "UIItem::Refresh",
     "int __thiscall UIItem::Refresh(void *this)"),
    (0x004DC5B0, "CCBSystem::GetControl",
     "int __thiscall CCBSystem::GetControl(CCBSystem *this)"),
    (0x004ED060, "CCBRoleState::GetRoleType",
     "char __thiscall CCBRoleState::GetRoleType(CCBRoleState *this, int roleIdx)"),
    (0x004F3430, "CCBRoleState::CheckBuff",
     "char __thiscall CCBRoleState::CheckBuff(CCBRoleState *this, int roleIdx)"),
    (0x0050B330, "CCBStageRole::GetCurrentState",
     "char __thiscall CCBStageRole::GetCurrentState(CCBStageRole *this)"),
    (0x0050D440, "CCBStage::CheckAllDone",
     "int __thiscall CCBStage::CheckAllDone(CCBStage *this)"),
    (0x0050E0D0, "CCBStage::ProcessCommand",
     "int __thiscall CCBStage::ProcessCommand(CCBStage *this)"),
    (0x0050FE50, "CCBStageScene::Update",
     "int __thiscall CCBStageScene::Update(void *this)"),
    (0x00503020, "CCBStage::ResetAll",
     "int __thiscall CCBStage::ResetAll(CCBStage *this)"),
    (0x00513840, "CCBSystem::CheckBattleEnd",
     "int __thiscall CCBSystem::CheckBattleEnd(CCBSystem *this)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 16")
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
