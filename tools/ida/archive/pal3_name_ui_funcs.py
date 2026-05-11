"""
IDAPython: Name high-frequency UI functions based on vtable analysis.

Vtable analysis shows:
- off_56AC70, off_56AD88, off_56ADD0 are UIWnd subclass vtables
- All have UIWnd::Create at slot 5
- 0x445AA0 is UIWnd base init (called by all constructors)
- 0x445B40 is UIWnd::~UIWnd (misidentified as std::ios_base::~ios_base)
- 0x445D20 is UIWnd::ScreenToClient
- 0x445C60 is UIWnd::HitTest
- 0x445FA0 is UIWnd::GetRect
- 0x445FE0 is UIWnd::SetRect
- 0x445EA0 is UIWnd::DestroyChildren
- 0x445D10 is UIWnd::SendMessage (stdcall with msg params)

Constructor/destructor patterns:
- sub_43A770: vtable off_56AC70 -> UIScene (based on nearby UIScene:: methods)
- sub_440740: vtable off_56AD88 -> UIStatic (intermediate UI class)
- sub_4422E0: vtable off_56ADD0 -> UIFrameWnd (has sub_445AA0 + member init)
- sub_442390: vtable off_56ADD0 -> UIFrameWnd::~UIFrameWnd
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_name_ui_funcs_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # UIWnd base methods
    (0x00445AA0, "UIWnd::UIWnd"),
    (0x00445B40, "UIWnd::~UIWnd"),
    (0x00445C60, "UIWnd::HitTest"),
    (0x00445D10, "UIWnd::SendMessage"),
    (0x00445D20, "UIWnd::ScreenToClient"),
    (0x00445D40, "UIWnd::ClientToScreen"),
    (0x00445EA0, "UIWnd::DestroyChildren"),
    (0x00445FA0, "UIWnd::GetRect"),
    (0x00445FE0, "UIWnd::SetRect"),
    (0x00445E70, "UIWnd::Destroy"),

    # UIFrameWnd (vtable off_56ADD0)
    (0x004422E0, "UIFrameWnd::UIFrameWnd"),
    (0x00442390, "UIFrameWnd::~UIFrameWnd"),
    (0x00442890, "UIFrameWnd::Render"),
    (0x00442AD0, "UIFrameWnd::Update"),
    (0x00442420, "UIFrameWnd::OnMessage"),

    # UIStatic (vtable off_56AD88)
    (0x00440740, "UIStatic::UIStatic"),
    (0x00440F30, "UIStatic::Render"),
    (0x00440DD0, "UIStatic::Update"),
    (0x00440BA0, "UIStatic::OnMessage"),

    # UIScene-related (vtable off_56AC70)
    (0x0043A770, "UIScene::~UIScene"),
    (0x0043AD40, "UIScene::Create2"),
    (0x0043AB20, "UIScene::Update2"),
    (0x0043AB00, "UIScene::OnMessage2"),

    # UIWnd common helpers
    (0x004426B0, "UIWnd::CreateFromTemplate"),
    (0x004427A0, "UIWnd::SetShow"),
    (0x004427C0, "UIWnd::SetEnable"),

    # Other high-frequency
    (0x0043AA00, "PalScript::OpenScript"),
    (0x0043FCA0, "UIWnd::FindChild"),
    (0x0043FDF0, "UIWnd::FindChildByName"),
    (0x0043FA00, "UIWnd::GetChildCount"),
    (0x0043FAE0, "UIWnd::GetChildAt"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Naming UI functions (iteration 2)")

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
        log("[*] Saved. Done.")

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
