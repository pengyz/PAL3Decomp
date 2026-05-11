"""
IDAPython: Manual iteration 9 - High-frequency game logic functions.
Verified by: function body analysis (array indexing patterns) + caller context.

Usage:
  idat.exe -A -S"pal3_manual_iter9.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter9_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # CCBRoleState array accessors (stride 892 = sizeof(tagRoleState) in PAL3)
    (0x004F3D90, "CCBRoleState::GetRoleField",
     "char __thiscall CCBRoleState::GetRoleField(CCBRoleState *this, int roleIdx, int fieldOff)"),
    (0x004ED010, "CCBRoleState::IsRoleAlive",
     "char __thiscall CCBRoleState::IsRoleAlive(CCBRoleState *this, int roleIdx)"),
    (0x004F38A0, "CCBRoleState::GetRoleState",
     "int __thiscall CCBRoleState::GetRoleState(CCBRoleState *this, int roleIdx)"),
    (0x004F3BC0, "CCBRoleState::GetRoleHP",
     "int __thiscall CCBRoleState::GetRoleHP(CCBRoleState *this, int roleIdx)"),
    (0x004F3B90, "CCBRoleState::GetRoleMP",
     "int __thiscall CCBRoleState::GetRoleMP(CCBRoleState *this, int roleIdx)"),
    (0x004F7500, "CCBRoleState::GetRoleAI",
     "char __thiscall CCBRoleState::GetRoleAI(CCBRoleState *this, void *pOut)"),
    (0x004F2BB0, "CCBRoleState::SetRoleField",
     "int __thiscall CCBRoleState::SetRoleField(CCBRoleState *this, int roleIdx, int value)"),
    (0x004FA540, "CCBRoleState::CheckRoleStatus",
     "int __thiscall CCBRoleState::CheckRoleStatus(CCBRoleState *this, int roleIdx)"),

    # CCBStageRole array accessor (stride 2632)
    (0x004FC940, "CCBStageRole::GetByIndex",
     "char __thiscall CCBStageRole::GetByIndex(CCBStageRole *this, int index)"),
    (0x0050A520, "CCBStageRole::GetStatus",
     "int __thiscall CCBStageRole::GetStatus(CCBStageRole *this, int index)"),
    (0x004ED040, "CCBStageRole::IsActive",
     "char __thiscall CCBStageRole::IsActive(CCBStageRole *this, int index)"),

    # CCBSystem
    (0x004DB910, "CCBSystem::GetDeltaTime",
     "double __thiscall CCBSystem::GetDeltaTime(CCBSystem *this)"),

    # RoleSystem (stride 164 * index + 492776 offset)
    (0x00420F30, "RoleSystem::GetRolePtr",
     "int __thiscall RoleSystem::GetRolePtr(RoleSystem *this, int index)"),
    (0x00412710, "RoleSystem::UpdateTransform",
     "int __thiscall RoleSystem::UpdateTransform(RoleSystem *this)"),
    (0x00412400, "RoleSystem::RenderRole",
     "void __thiscall RoleSystem::RenderRole(RoleSystem *this, void *pStack, int a3)"),
    (0x00410E40, "RoleSystem::CheckVisible",
     "int __cdecl RoleSystem::CheckVisible(int a1)"),

    # CCBAI utility
    (0x0040CFE0, "CCBAI::GetTargetRole",
     "void * __thiscall CCBAI::GetTargetRole(CCBAI *this, void *pOut)"),

    # UI
    (0x004A3900, "UIBase::SetItemData",
     "int __thiscall UIBase::SetItemData(void *this, int id, unsigned int data)"),
    (0x00446010, "UIWnd::GetChild",
     "int __thiscall UIWnd::GetChild(UIWnd *this, int id)"),

    # Audio in scene
    (0x0053E2E0, "CScreenMode::AudioSetPosition",
     "void __thiscall CScreenMode::AudioSetPosition(CScreenMode *this, void *pPos, int a3)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 9: High-frequency game logic")
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
