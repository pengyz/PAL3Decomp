"""
IDAPython: Test - set ppvOut type to GRPinput, re-decompile PAL3::Create
See if Hex-Rays outputs OOP style (ppvOut.Method()) or still flattened

Usage:
  idat.exe -A -S"pal3_test_oop_output.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_hexrays
import ida_name
import ida_typeinf
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_test_oop_output_log.txt")

log_lines = []

def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    ida_auto.auto_wait()
    log("[*] Test: OOP output after type annotation")

    til = ida_typeinf.get_idati()

    # Step 1: Define GRPinput struct in IDA
    grpinput_decl = """
    struct GRPinput {
        void *m_lpDI;
        void *m_lpDIDKeyboard;
        void *m_lpDIDMouse;
        float m_mouseSensitivity;
        long m_mouseMinX;
        long m_mouseMinY;
        long m_mouseMaxX;
        long m_mouseMaxY;
        long m_joystickMinX;
        long m_joystickMinY;
        long m_joystickMaxX;
        long m_joystickMaxY;
        char _pad[9000];
    };
    """
    tinfo = ida_typeinf.tinfo_t()
    result = ida_typeinf.parse_decl(tinfo, til, grpinput_decl.strip(), ida_typeinf.PT_TYP)
    if result is not None:
        tinfo.set_named_type(til, "GRPinput", ida_typeinf.NTF_REPLACE)
        log("[+] GRPinput struct defined")
    else:
        log("[-] Failed to define GRPinput")

    # Step 2: Find ppvOut address and set its type
    ppvOut_addr = ida_name.get_name_ea(0, "ppvOut")
    if ppvOut_addr == 0xFFFFFFFF:
        # try to find by scanning known address
        ppvOut_addr = 0x00BFDA40  # approximate from call_graph globals
        log("[*] ppvOut not found by name, trying 0x%08X" % ppvOut_addr)

    # Set type of ppvOut to GRPinput
    if ppvOut_addr != 0xFFFFFFFF:
        if idc.SetType(ppvOut_addr, "GRPinput ppvOut"):
            log("[+] ppvOut type set to GRPinput at 0x%08X" % ppvOut_addr)
        else:
            log("[-] Failed to set ppvOut type")

    # Step 3: Also set sub_402270 signature properly
    # void __thiscall sub_402270(GRPinput *this, long, long, long, long)
    addr_402270 = 0x00402270
    sig = "int __thiscall sub_402270(GRPinput *this, long a2, long a3, long a4, long a5)"
    if idc.SetType(addr_402270, sig):
        log("[+] sub_402270 signature set with GRPinput *this")
    else:
        log("[-] Failed to set sub_402270 signature")

    # Also set GRPinput_SetMode
    addr_4022B0 = 0x004022B0
    sig2 = "int __thiscall GRPinput_SetMode(GRPinput *this, int mode)"
    if idc.SetType(addr_4022B0, sig2):
        log("[+] GRPinput_SetMode signature set")
    else:
        log("[-] Failed to set GRPinput_SetMode signature")

    ida_auto.auto_wait()

    # Step 4: Re-decompile PAL3::Create and check output
    log("")
    log("[*] Re-decompiling PAL3::Create (0x00404800)...")
    try:
        cfunc = ida_hexrays.decompile(0x00404800)
        if cfunc:
            code = str(cfunc)
            log("[*] Output (first 1000 chars):")
            log(code[:1000])

            # Check if OOP style appears
            if "ppvOut." in code or "ppvOut->" in code:
                log("")
                log("[!!!] SUCCESS: Hex-Rays outputs OOP style!")
            elif "&ppvOut" in code:
                log("")
                log("[!!!] STILL FLATTENED: Hex-Rays still uses &ppvOut as explicit arg")

            # Save full output
            output_path = os.path.join(PROJECT_ROOT, "asm", "pal3", "_test_oop_create.txt")
            with open(output_path, 'w', encoding='utf-8') as f:
                f.write(code)
            log("[*] Full output saved to: %s" % output_path)
        else:
            log("[-] Decompilation failed")
    except Exception as e:
        log("[-] Error: %s" % str(e))

    idc.save_database(idc.get_idb_path(), 0)
    log("[*] IDB saved")

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
