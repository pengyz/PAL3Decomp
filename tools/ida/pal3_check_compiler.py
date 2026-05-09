"""
IDAPython: Check compiler settings in the IDB (IDA 9.x compatible).
"""
import ida_auto, ida_ida, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_check_compiler_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Checking compiler/ABI settings (IDA 9.x)")

        # inf structure
        log("[*] inf settings:")
        log("  processor: %s" % ida_ida.inf_get_procname())
        log("  filetype: %d" % ida_ida.inf_get_filetype())

        # Compiler info via inf
        log("")
        log("[*] Compiler info:")
        cc_id = ida_ida.inf_get_cc_id()
        log("  cc_id: %d" % cc_id)
        comp_names = {0: "Unknown", 1: "Visual C++", 2: "Borland", 3: "Watcom", 6: "GNU", 7: "Visual C++ (new)"}
        log("  compiler: %s" % comp_names.get(cc_id, "ID=%d" % cc_id))

        cc_cm = ida_ida.inf_get_cc_cm()
        log("  cc_cm (memory model): 0x%02X" % cc_cm)

        cc_size_i = ida_ida.inf_get_cc_size_i()
        cc_size_b = ida_ida.inf_get_cc_size_b()
        cc_size_e = ida_ida.inf_get_cc_size_e()
        cc_size_l = ida_ida.inf_get_cc_size_l()
        cc_defalign = ida_ida.inf_get_cc_defalign()
        log("  sizeof(int): %d" % cc_size_i)
        log("  sizeof(bool): %d" % cc_size_b)
        log("  sizeof(enum): %d" % cc_size_e)
        log("  sizeof(long): %d" % cc_size_l)
        log("  default alignment: %d" % cc_defalign)

        # Calling convention
        cc_val = cc_cm & 0x30
        cc_names_map = {0x00: "cdecl", 0x10: "stdcall", 0x20: "fastcall", 0x30: "thiscall"}
        log("  default CC: %s (0x%02X)" % (cc_names_map.get(cc_val, "unknown"), cc_val))

        # ABI
        log("")
        log("[*] ABI:")
        try:
            abi = ida_typeinf.get_abi_name()
            log("  abi_name: %s" % abi)
        except:
            log("  abi_name: (not available)")

        # Check if __thiscall is default for member functions
        log("")
        log("[*] Type info library:")
        til = ida_typeinf.get_idati()
        log("  til: %s" % str(til))

        # Check pointer size
        log("")
        log("[*] Address/pointer info:")
        log("  inf_is_32bit: %s" % ida_ida.inf_is_32bit())
        log("  inf_is_64bit: %s" % ida_ida.inf_is_64bit())

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
