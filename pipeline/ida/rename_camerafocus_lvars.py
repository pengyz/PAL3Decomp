"""
Rename local variables in PalScript::Op_CameraFocusPoint via direct API.

Usage:
  idat -A -S"pipeline/ida/rename_camerafocus_lvars.py" original/PAL3.exe.i64
"""
import ida_hexrays, ida_funcs, ida_pro, ida_auto, os

FUNC_EA = 0x00435830

LOG_FILE = os.path.join(os.path.dirname(__file__), "_logs", "lvar_rename_log.txt")

# new_name -> (old_name set for verification)
RENAME_MAP = {
    'nItemGDB_ID':      {'pConfig'},
    'nItemCount':       {'v19'},
    'pSkillData':       {'SkillNum'},
    'pSkillDataStored': {'v20'},
    'nItemType':        {'v8'},
    'nSkillGDB_ID':     {'v15'},
    'nSkillCount':      {'v16'},
    'pSkillResult':     {'v17'},
    'pSendTarget':      {'p_pConfig'},
    'nNextEventID':     {'v14'},
    'nAttrIdx':         {'i'},
    'nCurAttrVal':      {'v6'},
    'nMaxAttrVal':      {'v7'},
    'pScrEffMgr':       {'v11'},
    'pScrEffect':       {'Instance'},
    'pScrMode':         {'v13'},
    'pszCountParam':    {'v3'},
    'pszEventName':     {'v10'},
    'pszItemParam':     {'String'},
}

def log(msg):
    with open(LOG_FILE, 'a') as f:
        f.write(msg + '\n')
    print(msg)

def main():
    ida_auto.auto_wait()
    
    func = ida_funcs.get_func(FUNC_EA)
    if not func:
        log("[ERROR] Function not found")
        return

    try:
        cfunc = ida_hexrays.decompile(func)
    except Exception as e:
        log(f"[ERROR] Decompile failed: {e}")
        return

    lvars = cfunc.lvars
    renamed = 0
    fail = 0
    log(f"Function has {len(lvars)} local variables")

    for lvar in lvars:
        try:
            old = lvar.name
            new = None
            for new_name, old_names in RENAME_MAP.items():
                if old in old_names:
                    new = new_name
                    break
            
            if new:
                loc = lvar.location
                info = f"  {old} -> {new}"
                if loc.is_stkoff():
                    info += f" (stack@{loc.stkoff()})"
                else:
                    info += f" (reg)"
                
                if lvar.name != new:
                    lvar.name = new
                    renamed += 1
                    info += " OK"
                else:
                    info += " (already set)"
                log(info)
            else:
                loc = lvar.location
                loc_info = ""
                if loc.is_stkoff():
                    loc_info = f" stkoff={loc.stkoff()}"
                elif loc.is_reg1():
                    loc_info = f" reg={loc.reg1()}"
                log(f"  (unmatched) {old}{loc_info}")
        except Exception as e:
            log(f"  ERROR processing lvar '{lvar.name}': {e}")

    if renamed:
        log("  Saving lvar settings...")
        try:
            lvinf = ida_hexrays.lvar_saved_infos_t()
            lvinf.set(cfunc.lvars)
            ida_hexrays.save_user_lvar_settings(FUNC_EA, lvinf)
            log("  save: OK")
        except Exception as e:
            log(f"  save failed: {e}")
            import traceback
            traceback.print_exc()
        log(f"\nRenamed {renamed} variables ({fail} failed)")
    else:
        log("\nNo renames applied")

    ida_pro.beep()

if __name__ == '__main__':
    main()
