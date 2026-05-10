"""
IDAPython: Batch scan all vtables to identify classes and name constructors/destructors.

Strategy: Find all vtable assignments (*this = &vtable), identify the class from
the vtable's first unique virtual function, then name the function containing the
vtable assignment as the constructor/destructor.
"""
import ida_auto, ida_name, ida_bytes, ida_xref, ida_funcs, idc, os, json

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_batch_vtable_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Text segment range
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

# Known vtable -> class name (from previous analysis)
KNOWN_VTABLES = {
    0x0056AC70: "UIScene",
    0x0056AD88: "UIStatic",
    0x0056ADD0: "UIFrameWnd",
    0x005705D0: "CCBResultWindow",
}


def main():
    try:
        ida_auto.auto_wait()
        log("[*] Batch vtable scan")

        # Find all 'off_' named addresses in .rdata that look like vtables
        # Vtables are in .rdata (0x558000-0x56xxxx) or .data
        vtables = {}
        rdata_start = 0x00558000
        rdata_end = 0x00580000

        # Scan for vtables: consecutive function pointers
        addr = rdata_start
        while addr < rdata_end:
            # Check if this looks like a vtable (4+ consecutive code pointers)
            is_vtable = True
            for i in range(4):
                ptr = ida_bytes.get_dword(addr + i * 4)
                if ptr < TEXT_START or ptr >= TEXT_END:
                    is_vtable = False
                    break
            if is_vtable:
                # Count how many consecutive function pointers
                count = 0
                while True:
                    ptr = ida_bytes.get_dword(addr + count * 4)
                    if ptr < TEXT_START or ptr >= TEXT_END:
                        break
                    count += 1
                    if count > 100:
                        break

                if count >= 3:
                    name = ida_name.get_name(addr)
                    vtables[addr] = {
                        "name": name if name else "off_%X" % addr,
                        "entries": count,
                        "first_func": ida_bytes.get_dword(addr),
                    }
                addr += count * 4
            else:
                addr += 4

        log("[*] Found %d potential vtables" % len(vtables))

        # For each vtable, find xrefs (who writes this vtable address)
        # These are constructors/destructors
        annotations = []
        for vt_addr, vt_info in sorted(vtables.items()):
            # Skip if already known
            class_name = KNOWN_VTABLES.get(vt_addr)

            # Find xrefs to this vtable address
            xrefs = []
            ref = ida_xref.get_first_dref_to(vt_addr)
            while ref != 0xFFFFFFFF and ref != 0xFFFFFFFFFFFFFFFF:
                if TEXT_START <= ref < TEXT_END:
                    func_addr = ida_funcs.get_func(ref)
                    if func_addr:
                        xrefs.append(func_addr.start_ea)
                xrefs.append(ref)
                ref = ida_xref.get_next_dref_to(vt_addr, ref)

            # Get unique function addresses that reference this vtable
            func_addrs = set()
            for ref_addr in xrefs:
                func = ida_funcs.get_func(ref_addr)
                if func:
                    func_addrs.add(func.start_ea)

            if func_addrs and not class_name:
                # Try to determine class from the vtable's function names
                first_func = ida_bytes.get_dword(vt_addr)
                first_name = ida_name.get_name(first_func)
                if first_name and '::' in first_name:
                    class_name = first_name.split('::')[0]

            if class_name and func_addrs:
                for fa in func_addrs:
                    fname = ida_name.get_name(fa)
                    if not fname or fname.startswith('sub_'):
                        annotations.append((fa, class_name, vt_addr))

        log("[*] Found %d unnamed ctor/dtor candidates" % len(annotations))

        # Name the functions
        named = 0
        for func_addr, class_name, vt_addr in annotations[:100]:  # limit to 100
            current_name = ida_name.get_name(func_addr)
            if current_name and not current_name.startswith('sub_'):
                continue
            # Determine if ctor or dtor by checking if vtable is set at start or end
            new_name = "%s::ctor_%X" % (class_name, func_addr & 0xFFFF)
            if ida_name.set_name(func_addr, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1
                if named <= 20:
                    log("  [+] 0x%08X: %s (vtable 0x%X)" % (func_addr, new_name, vt_addr))

        log("[*] Named: %d" % named)
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
