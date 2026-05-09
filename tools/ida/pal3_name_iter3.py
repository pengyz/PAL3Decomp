"""
IDAPython: Name functions iteration 3 - PtrArray, UIWnd helpers, ScriptSystem.
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_name_iter3_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # PtrArray methods (0x4326xx-0x4327xx area)
    (0x00432660, "PtrArray::Clear"),
    (0x00432770, "PtrArray::SetAt"),
    (0x004327B0, "PtrArray::InsertAt"),

    # UIWnd additional methods (0x445xxx)
    (0x00445CD0, "UIWnd::GetID"),
    (0x00445C10, "UIWnd::UpdateChildren"),
    (0x00445F20, "UIWnd::MoveWindow"),

    # UIWnd property setters (0x43Fxxx)
    (0x0043FDB0, "UIWnd::SetFrameRate"),
    (0x0043FDC0, "UIWnd::GetWidth"),
    (0x0043FDD0, "UIWnd::GetHeight"),
    (0x0043FDE0, "UIWnd::GetPosition"),
    (0x0043FEC0, "UIWnd::AddChild"),

    # UIFrameWnd methods
    (0x00442C60, "UIFrameWnd::SetPosition"),

    # UIScene related
    (0x0043A810, "UIScene::Destroy2"),

    # Script/string utilities
    (0x00434C00, "PalScript::GetString"),

    # Scene/UI bridge
    (0x004235B0, "UIScene::ProcessInput"),
    (0x0043F560, "UIWnd::CreateChild"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Naming functions (iteration 3)")
        named = 0
        for addr, name in ANNOTATIONS:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1
                log("  [+] 0x%08X: %s" % (addr, name))
            else:
                log("  [-] 0x%08X: failed %s" % (addr, name))
        log("[*] Named: %d / %d" % (named, len(ANNOTATIONS)))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] Done")
    except Exception as e:
        import traceback
        log("[!] %s" % str(e))
        log(traceback.format_exc())
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
