"""
Scan .rdata for vtable-like structures and export them.
A vtable is a sequence of code pointers in .rdata.

Output: prints JSON with all detected vtables.

Usage:
  idat -A -S"tools/ida/pal3_scan_vtables.py" original/PAL3.exe.raw.i64
"""
import ida_auto
import ida_bytes
import ida_segment
import idc
import json

def is_code_addr(ea):
    return 0x00401000 <= ea < 0x00560000

def main():
    ida_auto.auto_wait()

    seg = ida_segment.get_segm_by_name(".rdata")
    if not seg:
        print("[!] .rdata segment not found")
        idc.qexit(1)
        return

    start = seg.start_ea
    end = seg.end_ea
    print("[*] Scanning .rdata: 0x%08X - 0x%08X" % (start, end))

    vtables = []
    ea = start
    while ea < end - 4:
        # Look for sequences of code pointers (at least 3)
        if is_code_addr(ida_bytes.get_dword(ea)):
            vt_start = ea
            count = 0
            while ea < end and is_code_addr(ida_bytes.get_dword(ea)):
                count += 1
                ea += 4
            if count >= 3:
                methods = []
                for i in range(count):
                    methods.append("0x%08X" % ida_bytes.get_dword(vt_start + i * 4))
                vtables.append({
                    "address": "0x%08X" % vt_start,
                    "methods": methods,
                    "count": count
                })
        else:
            ea += 4

    print("[*] Found %d vtable candidates" % len(vtables))

    # Write output
    import os
    out_path = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                           "pipeline", "ida", "_logs", "vtable_scan.json")
    with open(out_path, "w") as f:
        json.dump(vtables, f, indent=2)
    print("[*] Written to %s" % out_path)

    idc.qexit(0)

main()
