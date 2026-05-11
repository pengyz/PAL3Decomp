"""
IDAPython: Manual iteration 7 - ScriptUpdate + InputUpdate + CombatUpdate callees.

CombatUpdate members verified against PDB CCBSystem layout:
  +0x00: m_pUtil, +0x04: m_pUI, +0x08: m_pControl
  +0x0C: m_pAttackSequen, +0x10: m_pRoleState, +0x14: m_pStage
  +0x18: m_pAI, +0x1C: m_pEditor

Usage:
  idat.exe -A -S"pal3_manual_iter7.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter7_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Struct forward declarations to add before setting signatures
STRUCT_DECLS = [
    "struct CCBControl;",
    "struct CCBAttackSequen;",
    "struct CCBRoleState;",
    "struct CCBStage;",
    "struct CCBUI;",
    "struct CCBSystem;",
    "struct RoleSystem;",
]

ANNOTATIONS = [
    # ScriptUpdate callees (ScriptSystem methods, cdecl)
    (0x004100A0, "ScriptSystem::RunScript",
     "int __cdecl ScriptSystem::RunScript(int a1, int a2, int a3)"),
    (0x004101F0, "ScriptSystem::RunWithDelay",
     "int __cdecl ScriptSystem::RunWithDelay(float delay, int a2, int a3)"),
    (0x00410470, "ScriptSystem::RunEvent",
     "int __cdecl ScriptSystem::RunEvent(int eventId, int a2, int a3)"),
    (0x00411F60, "ScriptSystem::UpdateTimers",
     "int __cdecl ScriptSystem::UpdateTimers(float dt)"),
    (0x004194C0, "ScriptSystem::UpdateObjects",
     "int __cdecl ScriptSystem::UpdateObjects(float dt)"),

    # InputUpdate callees
    (0x0041C540, "InputSystem::ProcessMouse",
     "void __cdecl InputSystem::ProcessMouse(int a1)"),
    (0x0041C710, "InputSystem::ProcessKeyboard",
     "int __cdecl InputSystem::ProcessKeyboard(int a1)"),

    # CombatUpdate callees - verified against PDB CCBSystem member offsets
    # this+8=m_pControl, this+12=m_pAttackSequen, this+16=m_pRoleState, this+20=m_pStage
    (0x004DC240, "CCBControl::Update",
     "int __thiscall CCBControl::Update(CCBControl *this)"),
    (0x004DB5C0, "CCBAttackSequen::Update",
     "int __thiscall CCBAttackSequen::Update(CCBAttackSequen *this)"),
    (0x004ECB00, "CCBRoleState::Update",
     "int __thiscall CCBRoleState::Update(CCBRoleState *this)"),
    (0x004FC0A0, "CCBStage::Update",
     "int __thiscall CCBStage::Update(CCBStage *this)"),
    (0x004E04C0, "CCBUI::Update",
     "int __thiscall CCBUI::Update(CCBUI *this)"),

    # CombatUpdate itself gets proper signature
    (0x00513060, "CCBSystem::CombatUpdate",
     "int __thiscall CCBSystem::CombatUpdate(CCBSystem *this, double dt)"),

    # NPCAnimUpdate callee
    (0x00446020, "NPC::UpdateAnim",
     "int __cdecl NPC::UpdateAnim(int a1)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 7: Script/Input/Combat Update callees")

        # Import forward declarations
        import ida_typeinf
        til = ida_typeinf.get_idati()
        for decl in STRUCT_DECLS:
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                import re
                m = re.search(r'struct\s+(\w+)', decl)
                if m:
                    tinfo.set_named_type(til, m.group(1), ida_typeinf.NTF_REPLACE)

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
        import traceback
        log(traceback.format_exc())
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
