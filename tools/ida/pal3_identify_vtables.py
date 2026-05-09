"""
IDAPython: Identify classes by vtable addresses and name the constructor/destructor functions.
"""
import ida_auto, ida_name, ida_bytes, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_identify_vtables_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Vtable addresses found in high-frequency sub_ functions
VTABLES_TO_CHECK = [
    0x0056AC70,
    0x0056AD88,
    0x0056ADD0,
    0x005705D0,  # from the stdiobuf example earlier
]

# Functions to name based on vtable analysis
# Will be filled after checking vtables
FUNC_NAMES = []

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Identifying vtables and naming functions")

        # For each vtable, check what name IDA has and what RTTI says
        for vt_addr in VTABLES_TO_CHECK:
            name = ida_name.get_name(vt_addr)
            # Read first few entries (function pointers)
            entries = []
            for i in range(5):
                fptr = ida_bytes.get_dword(vt_addr + i * 4)
                fname = ida_name.get_name(fptr) if fptr else ""
                entries.append((fptr, fname))

            log("  vtable 0x%08X: name=%s" % (vt_addr, name))
            for fptr, fname in entries:
                if fptr:
                    log("    0x%08X: %s" % (fptr, fname))

            # Check for RTTI: usually 4 bytes before vtable is the RTTI Complete Object Locator
            rtti_ptr = ida_bytes.get_dword(vt_addr - 4)
            if rtti_ptr:
                rtti_name = ida_name.get_name(rtti_ptr)
                log("    RTTI: 0x%08X %s" % (rtti_ptr, rtti_name if rtti_name else ""))

        log("")

        # Also check UIWnd-related functions in 0x445xxx range
        log("[*] Checking UI helper functions (0x445xxx):")
        ui_funcs = [
            0x00445AA0, 0x00445B40, 0x00445C60, 0x00445D10,
            0x00445D20, 0x00445D40, 0x00445EA0, 0x00445FA0,
            0x00445FE0, 0x00446010, 0x00446020,
        ]
        for addr in ui_funcs:
            name = ida_name.get_name(addr)
            log("  0x%08X: %s" % (addr, name if name else "sub_%X" % addr))

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
