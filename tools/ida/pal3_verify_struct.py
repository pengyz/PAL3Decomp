"""
IDAPython: Verify CCBRoleState struct in IDA - check if m_Role is correctly typed.
"""
import ida_auto, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_verify_struct_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()

    for name in ["CCBRoleState", "tagRoleState", "CCBStageRole", "CCBSystem"]:
        tif = ida_typeinf.tinfo_t()
        if tif.get_named_type(til, name):
            log("=== %s (size=%d) ===" % (name, tif.get_size()))
            si = ida_typeinf.udt_type_data_t()
            if tif.get_udt_details(si):
                log("  members: %d" % si.size())
                for i in range(min(si.size(), 5)):
                    m = si[i]
                    mtype = m.type.dstr() if m.type else "?"
                    log("    +0x%X %s %s" % (m.offset//8, mtype, m.name))
                if si.size() > 5:
                    log("    ...")
                    # Show m_Role specifically for CCBRoleState
                    for i in range(si.size()):
                        m = si[i]
                        if 'Role' in m.name or 'role' in m.name:
                            mtype = m.type.dstr() if m.type else "?"
                            log("    [%d] +0x%X %s %s" % (i, m.offset//8, mtype, m.name))
        else:
            log("=== %s: NOT FOUND ===" % name)
        log("")

    ida_auto.auto_wait()
    log("[*] Done")
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w') as f:
        f.write(chr(10).join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
