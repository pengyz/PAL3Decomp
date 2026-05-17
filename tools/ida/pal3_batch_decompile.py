"""
Batch decompile multiple functions. Output to stdout for capture.

Usage:
  idat.exe -A -S"tools/ida/pal3_batch_decompile.py" original/PAL3.exe.91.i64

Reads addresses from PAL3_BATCH_ADDRS env var (comma-separated hex).
"""
import ida_auto
import ida_hexrays
import ida_name
import idc
import os

def main():
    ida_auto.auto_wait()

    addrs_str = os.environ.get('PAL3_BATCH_ADDRS', '')
    if not addrs_str:
        print("[!] Set PAL3_BATCH_ADDRS env var")
        idc.qexit(1)
        return

    addrs = [int(a.strip(), 16) for a in addrs_str.split(',') if a.strip()]
    print("[*] Batch decompile: %d functions" % len(addrs))

    for addr in addrs:
        name = ida_name.get_name(addr) or "sub_%X" % addr
        print("###FUNC### 0x%08X %s" % (addr, name))
        ida_hexrays.mark_cfunc_dirty(addr)
        try:
            cfunc = ida_hexrays.decompile(addr)
            if cfunc:
                print(str(cfunc))
            else:
                print("[!] None")
        except Exception as e:
            print("[!] Error: %s" % str(e))
        print("###END###")

    idc.qexit(0)

main()
