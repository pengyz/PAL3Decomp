"""
Fix lvar save: properly construct lvar_locator_t for save_user_lvar_settings.
Also handles register variables.
"""
import ida_hexrays, ida_funcs, ida_pro, ida_auto, os

FUNC_EA = 0x00435830
LOG_FILE = os.path.join(os.path.dirname(__file__), "_logs", "lvar_save_fix_log.txt")

def log(msg):
    with open(LOG_FILE, 'a') as f:
        f.write(str(msg) + '\n')
    print(msg)

def main():
    ida_auto.auto_wait()
    log("=== Lvar save fix v3 ===")
    
    func = ida_funcs.get_func(FUNC_EA)
    cfunc = ida_hexrays.decompile(func)
    log(f"Decompiled OK, {len(cfunc.lvars)} lvars")
    
    # Set all renames on the cfunc
    rename_map = {
        'v14': 'nNextEventID', 'v15': 'nSkillGDB_ID', 'v16': 'nSkillCount',
        'v17': 'pSkillResult', 'pConfig': 'nItemGDB_ID', 'v19': 'nItemCount',
        'v20': 'pSkillDataStored', 'Buffer': 'szEventName',
        'String': 'pszItemParam', 'v3': 'pszCountParam',
        'SkillNum': 'pSkillData', 'i': 'nAttrIdx', 'v6': 'nCurAttrVal',
        'v7': 'nMaxAttrVal', 'v8': 'nItemType', 'p_pConfig': 'pSendTarget',
        'v10': 'pszEventName', 'v11': 'pScrEffMgr',
        'Instance': 'pScrEffect', 'v13': 'pScrMode',
        'v2': 'pGetStrThis',
    }
    
    renamed = 0
    for lvar in cfunc.lvars:
        old = lvar.name
        if old in rename_map:
            new = rename_map[old]
            if old != new:
                lvar.name = new
                renamed += 1
                loc = lvar.location
                loc_info = f"reg={loc.reg1()}" if loc.is_reg1() else f"stkoff={loc.stkoff()}"
                log(f"  {old} → {new} ({loc_info})")
    
    log(f"\n{renamed} lvars renamed in-memory")
    
    # Build lvar_saved_infos_t
    log("Building lvar_uservec_t via lvvec...")
    try:
        uvec = ida_hexrays.lvar_uservec_t()
        uvec.lvvec = ida_hexrays.lvar_saved_infos_t()
        for lv in cfunc.lvars:
            si = ida_hexrays.lvar_saved_info_t()
            ll = ida_hexrays.lvar_locator_t()
            ll.location = lv.location
            ll.defea = cfunc.entry_ea
            si.ll = ll
            si.name = lv.name
            uvec.lvvec.push_back(si)
        log(f"  Built {uvec.lvvec.size()} lvar entries")
        ida_hexrays.save_user_lvar_settings(FUNC_EA, uvec)
        log("save_user_lvar_settings: OK")
    except Exception as e:
        log(f"save_user_lvar_settings FAILED: {e}")
    
    ida_pro.beep()
    log("[DONE]")

if __name__ == '__main__':
    main()
