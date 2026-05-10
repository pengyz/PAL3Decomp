"""
IDAPython: Fix tagRoleState to use PAL3's correct size (892 bytes, not PAL3A's 1040).
The stride 892 is confirmed from binary: m_sCombatDialog[892 * roleIdx + N]

Uses PAL3A PDB member names where offset < 892.
"""
import ida_auto, ida_typeinf, idc, os, json

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
PDB_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_tagRoleState_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

PAL3_SIZE = 892  # From binary stride analysis

def main():
    ida_auto.auto_wait()
    log("[*] Fixing tagRoleState to PAL3 size: %d bytes" % PAL3_SIZE)

    # Load PAL3A PDB members (for names, use offsets < PAL3_SIZE)
    with open(PDB_FILE, 'r') as f:
        pdb = json.load(f)

    pal3a_members = None
    for c in pdb['classes']:
        if c['name'] == 'tagRoleState':
            pal3a_members = c['data_members']
            break

    if not pal3a_members:
        log("[!] tagRoleState not found in PDB")
        return

    # Filter members that fit in PAL3's 892 bytes
    valid_members = [m for m in pal3a_members if m['offset'] < PAL3_SIZE]
    log("[*] PAL3A members within PAL3 range: %d / %d" % (len(valid_members), len(pal3a_members)))

    til = ida_typeinf.get_idati()

    # Build UDT with correct sizes based on PAL3 stride
    udt = ida_typeinf.udt_type_data_t()

    for i, m in enumerate(valid_members):
        mname = m['name']
        moffset = m['offset']

        # Calculate size from next member or struct end
        if i + 1 < len(valid_members):
            msize = valid_members[i+1]['offset'] - moffset
        else:
            msize = PAL3_SIZE - moffset

        if msize <= 0:
            msize = 1

        member = ida_typeinf.udt_member_t()
        member.name = mname
        member.offset = moffset * 8
        member.size = msize * 8

        # Use char[size] for all members to guarantee correct total size
        if msize == 1:
            member.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT8 | ida_typeinf.BTMT_UNSIGNED)
        elif msize == 4:
            member.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT32)
        else:
            arr_tif = ida_typeinf.tinfo_t()
            arr_tif.create_array(ida_typeinf.tinfo_t(ida_typeinf.BT_INT8), msize)
            member.type = arr_tif

        udt.push_back(member)

    # Create the struct
    tif = ida_typeinf.tinfo_t()
    if tif.create_udt(udt, ida_typeinf.BTF_STRUCT):
        err = tif.set_named_type(til, "tagRoleState", ida_typeinf.NTF_REPLACE)
        if err == 0:
            log("[+] tagRoleState created: size=%d" % tif.get_size())
        else:
            log("[-] set_named_type failed: %d" % err)
    else:
        log("[-] create_udt failed")

    ida_auto.auto_wait()
    idc.save_database(idc.get_idb_path(), 0)
    log("[*] Done")

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w') as f:
        f.write(chr(10).join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
