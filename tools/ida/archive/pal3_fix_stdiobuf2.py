"""
IDAPython: Phase 2 - Delete stdiobuf/std::ios_base from local types.
Once removed, Hex-Rays will fall back to using void* or the correct type
for arguments that were previously typed as stdiobuf*.
"""
import ida_auto, ida_typeinf, ida_name, idc, idautils, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_stdiobuf2_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Phase 2: Remove stdiobuf type and fix remaining references")

        til = ida_typeinf.get_idati()

        # Try to delete stdiobuf from local types
        tif = ida_typeinf.tinfo_t()
        if tif.get_named_type(til, "stdiobuf"):
            log("[*] stdiobuf found in local types, removing...")
            # Can't easily delete, but can redefine as alias for UIWnd
            decl = "struct stdiobuf;"  # forward declare only
            new_tif = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(new_tif, til, decl, ida_typeinf.PT_TYP) is not None:
                new_tif.set_named_type(til, "stdiobuf", ida_typeinf.NTF_REPLACE)
                log("  [+] Replaced stdiobuf with forward decl")

        # Also handle ios_base mangled names in function list
        fixed = 0
        for func_ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(func_ea)
            if not name:
                continue
            if 'ios_base' in name or 'stdiobuf' in name:
                # Check if this is in game code area (not CRT)
                if func_ea < 0x00430000:
                    continue  # Skip actual CRT area

                new_name = name
                new_name = new_name.replace('ios_base@std@@', 'UIWnd@@')
                new_name = new_name.replace('stdiobuf@@', 'UIWnd@@')
                new_name = new_name.replace('ios_base', 'UIWnd')
                new_name = new_name.replace('stdiobuf', 'UIWnd')

                if new_name != name:
                    if ida_name.set_name(func_ea, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                        fixed += 1
                        if fixed <= 10:
                            log("  [+] 0x%08X: -> %s" % (func_ea, new_name))

        log("[*] Fixed %d more names" % fixed)
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
