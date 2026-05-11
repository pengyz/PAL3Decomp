"""
Fix CCBRoleState: set m_Role and m_RoleXor to tagRoleState[11] type.
Now that tagRoleState is correctly 892 bytes, this should work.
"""
import ida_auto, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_CCBRoleState_v2_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()

    # Verify tagRoleState size
    trs_tif = ida_typeinf.tinfo_t()
    trs_tif.get_named_type(til, "tagRoleState")
    log("[*] tagRoleState size: %d" % trs_tif.get_size())

    # Create tagRoleState[11] array type
    arr11_tif = ida_typeinf.tinfo_t()
    arr11_tif.create_array(trs_tif, 11)
    log("[*] tagRoleState[11] size: %d (expected %d)" % (arr11_tif.get_size(), 892*11))

    # Rebuild CCBRoleState with proper typed m_Role
    udt = ida_typeinf.udt_type_data_t()

    def add_member(offset, name, size, tif=None):
        m = ida_typeinf.udt_member_t()
        m.name = name
        m.offset = offset * 8
        m.size = size * 8
        if tif:
            m.type = tif
        elif size == 1:
            m.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT8 | ida_typeinf.BTMT_UNSIGNED)
        elif size == 4:
            m.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT32)
        elif size == 2:
            m.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT16)
        else:
            arr = ida_typeinf.tinfo_t()
            arr.create_array(ida_typeinf.tinfo_t(ida_typeinf.BT_INT8), size)
            m.type = arr
        udt.push_back(m)

    # Members before m_Role
    add_member(0x000, "m_sCombatDialog", 512)
    add_member(0x200, "m_fLastDialogTime", 4)
    add_member(0x204, "m_bCombatDialog", 1)
    add_member(0x208, "m_pCBSystem", 4)
    add_member(0x20C, "m_pStage", 4)
    add_member(0x210, "m_pUI", 4)
    add_member(0x214, "m_pUtil", 4)
    add_member(0x218, "m_bWeSneakAttackEnemy", 1)
    add_member(0x219, "m_bEnemySneakAttackUs", 1)
    add_member(0x21C, "m_nMaxRound", 4)
    add_member(0x220, "m_nBossRound", 4)
    add_member(0x224, "m_bMustFail", 1)
    add_member(0x225, "m_bFleeAlwaysSuccess", 1)
    add_member(0x226, "m_bCreatedNewRole", 1)

    # m_Role and m_RoleXor with PROPER TYPE
    add_member(0x228, "m_Role", 892*11, arr11_tif)
    add_member(0x287C, "m_RoleXor", 892*11, arr11_tif)

    # Tail members
    tail = 0x4ED0
    add_member(tail, "m_dwEXPTable", 400)
    add_member(tail + 400, "m_dwWinTaskID", 4)
    add_member(tail + 404, "m_bNGHDeadVariance", 4)
    add_member(tail + 408, "m_eSameRow", 36)
    add_member(tail + 444, "m_eSameColumn", 24)
    add_member(tail + 468, "m_fSwordStarTime", 4)

    tif = ida_typeinf.tinfo_t()
    if tif.create_udt(udt, ida_typeinf.BTF_STRUCT):
        err = tif.set_named_type(til, "CCBRoleState", ida_typeinf.NTF_REPLACE)
        log("[+] CCBRoleState: size=%d, err=%d" % (tif.get_size(), err))
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
