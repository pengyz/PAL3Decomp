"""Fix this-pointer type for 12 functions (round 2)."""
import ida_auto, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_all_this_r2_log.txt")
log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

FIXES = [
    (0x004111C0, 'int __thiscall Array::Size(Array *this)'),
    (0x0051B210, 'char __thiscall CCBItemWindow::Create(CCBItemWindow *this, _DWORD *pRect, int parent)'),
    (0x0051C330, 'char __thiscall CCBSkillWindow::Create(CCBSkillWindow *this, _DWORD *pRect, int parent)'),
    (0x005183C0, 'int ( __thiscall CCBUI::CreateMagicWindow(CCBUI *this))(_DWORD, _DWORD)'),
    (0x00403370, 'char * __thiscall GRPinput::AcquireMouse(GRPinput *this)'),
    (0x004B73D0, 'int __thiscall MvcController::SetComponent(MvcController *this, int a2)'),
    (0x0043A4B0, 'int __thiscall MvcViewport::SetController(MvcViewport *this, int a2)'),
    (0x00431F00, 'int __thiscall PalScript::AddWaitObj(PalScript *this)'),
    (0x00407B30, 'int __thiscall std::basic_string<char,std::char_traits<char>,std::allocator<char>>::_Eos(std *this, int a2)'),
    (0x00407AB0, 'char __thiscall std::basic_string<char,std::char_traits<char>,std::allocator<char>>::_Freeze(std *this)'),
    (0x00402FB0, 'void __thiscall std::basic_string<char,std::char_traits<char>,std::allocator<char>>::_Tidy(std *this, char a2)'),
    (0x00430790, 'void __thiscall std::basic_string<char,std::char_traits<char>,std::allocator<char>>::~basic_string<char,std::char_traits<char>,std::allocator<char>>(std *this)'),
]

def main():
    ida_auto.auto_wait()
    log("[*] Fixing this-type for %d functions (round 2)" % len(FIXES))
    fixed = 0
    for addr, sig in FIXES:
        if idc.SetType(addr, sig):
            fixed += 1
    log("[*] Fixed: %d / %d" % (fixed, len(FIXES)))
    ida_auto.auto_wait()
    idc.save_database(idc.get_idb_path(), 0)
    log("[*] Done")
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, "w") as f:
        f.write(chr(10).join(log_lines))
    idc.qexit(0)

if __name__ == "__main__":
    main()