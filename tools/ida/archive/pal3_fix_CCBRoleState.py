"""
Fix CCBRoleState in IDA to use PAL3's correct tagRoleState size (892).

PAL3 CCBRoleState layout (verified from binary):
  +0x000 char[512] m_sCombatDialog
  +0x200 float m_fLastDialogTime
  +0x204 uchar m_bCombatDialog
  +0x208 CCBSystem * m_pCBSystem
  +0x20C CCBStage * m_pStage
  +0x210 CCBUI * m_pUI
  +0x214 CUtil * m_pUtil
  +0x218-0x227: misc flags
  +0x228 tagRoleState[11] m_Role      (892*11 = 9812 bytes)
  +0x287C tagRoleState[11] m_RoleXor  (892*11 = 9812 bytes)
  +0x4ED0 ... remaining members
"""
import ida_auto, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_CCBRoleState_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    ida_auto.auto_wait()
    log("[*] Fixing CCBRoleState with correct PAL3 tagRoleState size")
    
    til = ida_typeinf.get_idati()
    
    # Verify tagRoleState is 892
    trs = ida_typeinf.tinfo_t()
    if trs.get_named_type(til, "tagRoleState"):
        log("[*] tagRoleState size in IDA: %d" % trs.get_size())
    
    # Rebuild CCBRoleState with correct sizes
    # Key members and their PAL3 offsets:
    members = [
        (0x000, "m_sCombatDialog", 512),    # char[512]
        (0x200, "m_fLastDialogTime", 4),    # float
        (0x204, "m_bCombatDialog", 1),      # uchar
        (0x208, "m_pCBSystem", 4),          # ptr
        (0x20C, "m_pStage", 4),             # ptr
        (0x210, "m_pUI", 4),                # ptr
        (0x214, "m_pUtil", 4),              # ptr
        (0x218, "m_bWeSneakAttackEnemy", 1),
        (0x219, "m_bEnemySneakAttackUs", 1),
        (0x21C, "m_nMaxRound", 4),
        (0x220, "m_nBossRound", 4),
        (0x224, "m_bMustFail", 1),
        (0x225, "m_bFleeAlwaysSuccess", 1),
        (0x226, "m_bCreatedNewRole", 1),
        (0x228, "m_Role", 892 * 11),        # tagRoleState[11] = 9812
        (0x287C, "m_RoleXor", 892 * 11),    # tagRoleState[11] = 9812
    ]
    # Total up to end of m_RoleXor: 0x287C + 9812 = 0x4ED0
    # Add remaining members (estimated from PAL3A tail)
    tail_start = 0x4ED0
    tail_members = [
        (tail_start, "m_dwEXPTable", 400),      # DWORD[100]
        (tail_start + 400, "m_dwWinTaskID", 4),
        (tail_start + 404, "m_bNGHDeadVariance", 4),
        (tail_start + 408, "m_eSameRow", 36),
        (tail_start + 444, "m_eSameColumn", 24),
        (tail_start + 468, "m_fSwordStarTime", 4),
    ]
    all_members = members + tail_members
    total_size = tail_start + 472  # = 0x50A8
    
    udt = ida_typeinf.udt_type_data_t()
    for i, (offset, name, size) in enumerate(all_members):
        member = ida_typeinf.udt_member_t()
        member.name = name
        member.offset = offset * 8
        member.size = size * 8
        # Use char array for large members, int for 4-byte, char for 1-byte
        if size == 1:
            member.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT8 | ida_typeinf.BTMT_UNSIGNED)
        elif size == 4:
            member.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT32)
        else:
            arr = ida_typeinf.tinfo_t()
            arr.create_array(ida_typeinf.tinfo_t(ida_typeinf.BT_INT8), size)
            member.type = arr
        udt.push_back(member)
    
    tif = ida_typeinf.tinfo_t()
    if tif.create_udt(udt, ida_typeinf.BTF_STRUCT):
        err = tif.set_named_type(til, "CCBRoleState", ida_typeinf.NTF_REPLACE)
        if err == 0:
            log("[+] CCBRoleState created: size=%d (expected %d)" % (tif.get_size(), total_size))
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
