"""
IDAPython: Manual iteration 4 - depth 2 expansion.
ScriptSystem::Destroy, PAL3::InitSubsystems, UIManager::Render callees.

Usage:
  idat.exe -A -S"pal3_manual_iter4.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter4_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # ScriptSystem::Destroy callees
    (0x0040C790, "ScriptSystem::Cleanup",
     "int __cdecl ScriptSystem::Cleanup()"),
    (0x00412680, "ScriptObj::Destroy",
     "int __thiscall ScriptObj::Destroy(void *this)"),
    (0x0043A250, "PalScript::Reset",
     "int __thiscall PalScript::Reset(char *this)"),
    (0x00445920, "UIWnd::Reset",
     "int __thiscall UIWnd::Reset(char *this)"),

    # PAL3::InitSubsystems callees
    (0x00408FD0, "PAL3::FullInit",
     "int __cdecl PAL3::FullInit()"),
    (0x0043A4C0, "UIScene::LoadResource",
     "void __thiscall UIScene::LoadResource(void *this, char *path)"),
    (0x004450A0, "UINote::Create",
     "void * __thiscall UINote::Create(void *this, int id, int a3, int a4, char *tex)"),
    (0x00445930, "UIWnd::SetState",
     "int __thiscall UIWnd::SetState(void *this, int state)"),

    # Also annotate global variables discovered
    # unk_BFDAB0 = UIScene global (passed to UIWnd::Reset in Destroy)
    # unk_C10968 = PalScript global (passed to PalScript::Reset)
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 4: depth 2 expansion")
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

        # Annotate globals
        globals_to_name = [
            (0x00BFDAB0, "g_UIScene"),
            (0x00C10968, "g_PalScript"),
            (0x00BFDA80, "g_pMiniGame1"),
            (0x00BFDA7C, "g_pMiniGame2"),
            (0x00BFDA84, "g_pMiniGame3"),
        ]
        for addr, gname in globals_to_name:
            cur = ida_name.get_name(addr) or ""
            if cur.startswith("dword_") or cur.startswith("unk_") or not cur:
                ida_name.set_name(addr, gname, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                log("  [g] 0x%08X: %s" % (addr, gname))

        log("[*] Named: %d, Signatures: %d" % (named, sigs))
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
