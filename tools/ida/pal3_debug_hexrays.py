"""
IDAPython: Debug why Hex-Rays doesn't use CCBSystem struct properly.
Check the this type as Hex-Rays sees it during decompilation.
"""
import ida_auto, ida_typeinf, ida_hexrays, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_debug_hexrays_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    try:
        ida_auto.auto_wait()
        til = ida_typeinf.get_idati()

        # 1. Check CCBSystem struct as stored in TIL
        log("=== CCBSystem in TIL ===")
        tif = ida_typeinf.tinfo_t()
        if tif.get_named_type(til, "CCBSystem"):
            log("  size: %d (0x%X)" % (tif.get_size(), tif.get_size()))
            si = ida_typeinf.udt_type_data_t()
            if tif.get_udt_details(si):
                log("  members: %d" % si.size())
                # Show member at offset 0x40 (should be m_DeltaTime)
                for i in range(si.size()):
                    m = si[i]
                    off = m.offset // 8
                    if off >= 0x38 and off <= 0x70:
                        mtype = m.type.dstr() if m.type else "?"
                        log("    [%d] +0x%04X %s %s" % (i, off, mtype, m.name))
        else:
            log("  NOT FOUND!")

        # 2. Check function 0x513060 signature
        log("")
        log("=== Function 0x513060 (CCBSystem::CombatUpdate) ===")
        addr = 0x00513060
        ftype = idc.get_type(addr)
        log("  idc.get_type: %s" % ftype)

        # 3. Decompile and check this variable type
        log("")
        log("=== Hex-Rays decompilation ===")
        try:
            cfunc = ida_hexrays.decompile(addr)
            if cfunc:
                lvars = cfunc.get_lvars()
                for lv in lvars:
                    if "this" in str(lv.name):
                        t = lv.type()
                        log("  this var: type='%s' size=%d" % (t.dstr(), t.get_size()))
                        # If it's a pointer, check pointee
                        if t.is_ptr():
                            pointee = t.get_pointed_object()
                            log("  pointee: '%s' size=%d is_struct=%s" % (
                                pointee.dstr(), pointee.get_size(), pointee.is_struct()))
                            if pointee.is_struct():
                                si = ida_typeinf.udt_type_data_t()
                                if pointee.get_udt_details(si):
                                    log("  pointee members: %d" % si.size())
                                    for i in range(min(si.size(), 5)):
                                        m = si[i]
                                        mtype = m.type.dstr() if m.type else "?"
                                        log("    +0x%04X %s %s" % (m.offset//8, mtype, m.name))
                        break

                # Show first 5 lines of decompiled output
                lines = cfunc.get_pseudocode()
                log("")
                log("  First statements:")
                for i in range(min(len(lines), 20)):
                    line_text = ida_hexrays.tag_remove(lines[i].line)
                    if 'm_' in line_text or 'this' in line_text:
                        log("    %s" % line_text)
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
