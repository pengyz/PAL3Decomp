"""
IDAPython: Fix stdiobuf/std::ios_base type misidentification.

IDA incorrectly identifies UIWnd-related functions as stdiobuf/ios_base.
This script:
1. Finds all functions with stdiobuf/ios_base in their signature
2. Replaces with UIWnd* (for thiscall) or appropriate game types
3. Renames stdiobuf::~stdiobuf to UIWnd::~UIWnd where applicable
"""
import ida_auto, ida_name, ida_typeinf, ida_funcs, idc, idautils, os, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_stdiobuf_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Address range of game code (not CRT)
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

# Known UIWnd::~UIWnd address
UIWND_DTOR = 0x00445B40


def main():
    try:
        ida_auto.auto_wait()
        log("[*] Fixing stdiobuf/ios_base type misidentification")

        til = ida_typeinf.get_idati()
        fixed_sigs = 0
        fixed_names = 0

        # Iterate all functions in game code range
        for func_ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(func_ea)
            sig = idc.get_type(func_ea)

            if not sig:
                continue

            # Check if signature contains stdiobuf or ios_base
            if 'stdiobuf' not in sig and 'ios_base' not in sig:
                continue

            # Replace stdiobuf* with UIWnd* in signature
            new_sig = sig.replace('stdiobuf *', 'UIWnd *')
            new_sig = new_sig.replace('std::ios_base *', 'UIWnd *')
            new_sig = new_sig.replace('stdiobuf', 'UIWnd')
            new_sig = new_sig.replace('std::ios_base', 'UIWnd')

            if new_sig != sig:
                # Build full function signature with name
                func_name = name if name else "sub_%X" % func_ea
                # Apply the new type
                tif = ida_typeinf.tinfo_t()
                full_decl = new_sig
                if ida_typeinf.parse_decl(tif, til, full_decl + ";", ida_typeinf.PT_SIL) is not None:
                    if idc.SetType(func_ea, new_sig):
                        fixed_sigs += 1
                        if fixed_sigs <= 20:
                            log("  [+] 0x%08X: %s" % (func_ea, new_sig[:80]))
                    else:
                        # Try alternate approach
                        pass

            # Fix function names containing stdiobuf
            if name and 'stdiobuf' in name:
                new_name = name.replace('stdiobuf', 'UIWnd')
                new_name = new_name.replace('std::ios_base', 'UIWnd')
                if ida_name.set_name(func_ea, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    fixed_names += 1
                    if fixed_names <= 10:
                        log("  [N] 0x%08X: %s -> %s" % (func_ea, name, new_name))

        log("[*] Fixed signatures: %d, Fixed names: %d" % (fixed_sigs, fixed_names))

        # Also fix: any named function called "stdiobuf::~stdiobuf" or similar
        # that's actually in the UIWnd vtable area
        for func_ea in idautils.Functions(0x00430000, 0x00450000):
            name = ida_name.get_name(func_ea)
            if name and ('stdiobuf' in name or 'ios_base' in name):
                # These are in UI code area, not CRT
                new_name = name.replace('stdiobuf::~stdiobuf', 'UIWnd::Destroy_internal')
                new_name = new_name.replace('stdiobuf::', 'UIWnd::')
                new_name = new_name.replace('ios_base', 'UIWnd')
                if new_name != name:
                    ida_name.set_name(func_ea, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                    fixed_names += 1

        log("[*] Total: %d sigs, %d names fixed" % (fixed_sigs, fixed_names))
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
