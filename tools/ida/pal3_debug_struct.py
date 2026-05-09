"""
IDAPython: Dump full struct definition for CCBStage as seen by Hex-Rays.
Also decompile one function and print raw type info.
"""
import ida_auto, ida_typeinf, ida_hexrays, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_debug_struct_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def dump_struct(til, name):
    """Dump full struct layout."""
    tif = ida_typeinf.tinfo_t()
    if not tif.get_named_type(til, name):
        log("  [!] Type '%s' not found" % name)
        return
    log("  size: %d (0x%X)" % (tif.get_size(), tif.get_size()))
    log("  is_struct: %s" % tif.is_struct())

    if not tif.is_struct():
        log("  (not a struct)")
        return

    si = ida_typeinf.udt_type_data_t()
    if not tif.get_udt_details(si):
        log("  [!] Cannot get udt details")
        return

    log("  total members: %d" % si.size())
    for i in range(si.size()):
        m = si[i]
        mtype_str = m.type.dstr() if m.type else "?"
        is_base = m.is_baseclass()
        log("    [%d] +0x%04X size=0x%04X %-30s %s%s" % (
            i, m.offset // 8, m.size // 8,
            mtype_str, m.name, " (BASE)" if is_base else ""))

def main():
    try:
        ida_auto.auto_wait()
        til = ida_typeinf.get_idati()

        # Dump CCBStage struct
        log("=== CCBStage ===")
        dump_struct(til, "CCBStage")
        log("")

        # Dump CCBSystem struct (first 10 members)
        log("=== CCBSystem (first 15) ===")
        tif = ida_typeinf.tinfo_t()
        if tif.get_named_type(til, "CCBSystem"):
            si = ida_typeinf.udt_type_data_t()
            if tif.get_udt_details(si):
                log("  size: %d, members: %d" % (tif.get_size(), si.size()))
                for i in range(min(si.size(), 15)):
                    m = si[i]
                    mtype_str = m.type.dstr() if m.type else "?"
                    log("    [%d] +0x%04X size=0x%04X %-30s %s" % (
                        i, m.offset // 8, m.size // 8, mtype_str, m.name))
        log("")

        # Check what Hex-Rays thinks about CCBStage::Update (0x4FC0A0)
        log("=== Hex-Rays view of 0x4FC0A0 ===")
        addr = 0x004FC0A0
        func_type = idc.get_type(addr)
        log("  function type: %s" % func_type)

        # Try to get the this variable type from Hex-Rays
        try:
            cfunc = ida_hexrays.decompile(addr)
            if cfunc:
                # Get 'this' variable
                lvars = cfunc.get_lvars()
                for lv in lvars:
                    if lv.name == "this" or "this" in str(lv.name):
                        log("  this var: name=%s type=%s" % (lv.name, lv.type().dstr()))
                        break
                # Print first 10 lines of pseudocode
                lines = cfunc.get_pseudocode()
                for i in range(min(len(lines), 15)):
                    log("  %s" % lines[i].line)
        except Exception as e:
            log("  Hex-Rays error: %s" % str(e))

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
