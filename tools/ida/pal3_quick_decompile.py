"""
Quick single-function decompile for verification.
Decompiles one function and prints output, without saving to file.

Usage:
  idat.exe -A -S"pal3_quick_decompile.py 0x004CDA10" original/PAL3.exe.i64

  Or set ADDR environment variable:
  set PAL3_VERIFY_ADDR=0x004CDA10
  idat.exe -A -S"pal3_quick_decompile.py" original/PAL3.exe.i64
"""
import ida_auto
import ida_hexrays
import ida_name
import idc
import os
import sys

def main():
    ida_auto.auto_wait()

    # Get address from script args or environment
    addr = None
    if idc.ARGV and len(idc.ARGV) > 1:
        try:
            addr = int(idc.ARGV[1], 16) if idc.ARGV[1].startswith('0x') else int(idc.ARGV[1])
        except:
            pass
    if not addr:
        addr_str = os.environ.get('PAL3_VERIFY_ADDR', '0x004CDA10')
        addr = int(addr_str, 16) if addr_str.startswith('0x') else int(addr_str)

    name = ida_name.get_name(addr) or "unknown"
    print("=" * 60)
    print("[*] Quick decompile: 0x%08X (%s)" % (addr, name))
    print("=" * 60)

    ida_hexrays.mark_cfunc_dirty(addr)
    try:
        cfunc = ida_hexrays.decompile(addr)
        if cfunc:
            print(str(cfunc))
        else:
            print("[!] Decompile returned None")
    except Exception as e:
        print("[!] Error: %s" % str(e))

    idc.qexit(0)

main()
