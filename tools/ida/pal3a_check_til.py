"""
IDAPython: Check struct storage in PAL3A IDB.
"""
import ida_auto, ida_typeinf, ida_struct, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3a_check_til_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Checking struct storage in PAL3A IDB")

        # Check IDA structs (ida_struct module)
        struct_count = ida_struct.get_struc_qty()
        log("[*] IDA structs (ida_struct): %d" % struct_count)

        # List some structs
        for i in range(min(struct_count, 30)):
            sid = ida_struct.get_struc_by_idx(i)
            sname = ida_struct.get_struc_name(sid)
            sptr = ida_struct.get_struc(sid)
            if sptr:
                log("  [%d] %-30s size=%d members=%d" % (
                    i, sname, ida_struct.get_struc_size(sptr), sptr.memqty))

        # Try to find specific classes
        log("")
        log("[*] Looking for key classes:")
        test_names = ["CCBSystem", "CCBRoleState", "UIWnd", "Actor", "PAL3",
                      "tagRoleState", "GRPinput", "CGameData"]
        for name in test_names:
            sid = ida_struct.get_struc_id(name)
            if sid != 0xFFFFFFFFFFFFFFFF and sid != 0xFFFFFFFF:
                sptr = ida_struct.get_struc(sid)
                if sptr:
                    log("  [+] %-20s id=0x%X size=%d members=%d" % (
                        name, sid, ida_struct.get_struc_size(sptr), sptr.memqty))
                    # Show first few members
                    for j in range(min(sptr.memqty, 5)):
                        mptr = sptr.get_member(j)
                        if mptr:
                            mname = ida_struct.get_member_name(mptr.id)
                            moff = mptr.soff
                            log("      +0x%04X %s" % (moff, mname))
            else:
                log("  [-] %-20s not found" % name)

        # Check local types for these names
        log("")
        log("[*] Checking local types (ida_typeinf):")
        til = ida_typeinf.get_idati()
        for name in test_names:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                log("  [+] %-20s (local type, size=%d)" % (name, tif.get_size()))
            else:
                log("  [-] %-20s not in local types" % name)

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
