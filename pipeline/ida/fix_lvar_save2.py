"""
Fix lvar save using modify_user_lvars with a no-op callback.
"""
import ida_hexrays, ida_funcs, ida_pro, ida_auto, os

FUNC_EA = 0x00435830
LOG_FILE = os.path.join(os.path.dirname(__file__), "_logs", "lvar_save_fix_log.txt")

def log(msg):
    with open(LOG_FILE, 'a') as f:
        f.write(str(msg) + '\n')
    print(msg)

class SaveModifier(ida_hexrays.user_lvar_modifier_t):
    """No-op modifier: just accepts current state, triggering save."""
    def handle_lvar(self, ea, lvar):
        return 0  # 0 = continue without changes

def main():
    ida_auto.auto_wait()
    log("=== Lvar save fix v2 ===")
    
    func = ida_funcs.get_func(FUNC_EA)
    cfunc = ida_hexrays.decompile(func)
    log(f"Decompiled OK, {len(cfunc.lvars)} lvars")
    
    # Set all renames on cfunc
    rename_map = {
        'v14': 'nNextEventID', 'v15': 'nSkillGDB_ID', 'v16': 'nSkillCount',
        'v17': 'pSkillResult', 'pConfig': 'nItemGDB_ID', 'v19': 'nItemCount',
        'v20': 'pSkillDataStored', 'Buffer': 'szEventName',
        'String': 'pszItemParam', 'v3': 'pszCountParam',
        'SkillNum': 'pSkillData', 'i': 'nAttrIdx', 'v6': 'nCurAttrVal',
        'v7': 'nMaxAttrVal', 'v8': 'nItemType', 'p_pConfig': 'pSendTarget',
        'v10': 'pszEventName', 'v11': 'pScrEffMgr',
        'Instance': 'pScrEffect', 'v13': 'pScrMode',
    }
    renamed = 0
    for lvar in cfunc.lvars:
        if lvar.name in rename_map:
            new_name = rename_map[lvar.name]
            if lvar.name != new_name:
                lvar.name = new_name
                renamed += 1
                log(f"  {lvar.name} → {rename_map[lvar.name]}")
    
    log(f"\n{renamed} variables renamed in-memory")
    
    # Try to persist using modify_user_lvars with no-op callback
    log("Saving via modify_user_lvars...")
    try:
        mod = SaveModifier()
        ida_hexrays.modify_user_lvars(FUNC_EA, mod)
        log("modify_user_lvars OK")
    except Exception as e:
        log(f"modify_user_lvars FAILED: {e}")
        
        # Fallback: try direct cfunc API
        log("Trying cfunc methods...")
        for method in ['save_user_lvars', 'save_func', 'save_user_iflags',
                       'save_user_labels', 'save_user_numforms']:
            if hasattr(cfunc, method):
                try:
                    getattr(cfunc, method)()
                    log(f"  cfunc.{method}() OK")
                except Exception as e2:
                    log(f"  cfunc.{method}() FAILED: {e2}")
    
    ida_pro.beep()
    log("[DONE]")

if __name__ == '__main__':
    main()
