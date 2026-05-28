"""
Test and fix lvar save API for IDA 9.1.
Tests multiple save approaches and applies the working one.
"""
import ida_hexrays, ida_funcs, ida_pro, ida_auto, os, sys

FUNC_EA = 0x00435830
LOG_FILE = os.path.join(os.path.dirname(__file__), "_logs", "lvar_save_fix_log.txt")

def log(msg):
    with open(LOG_FILE, 'a') as f:
        f.write(str(msg) + '\n')
    print(msg)

def test_save_methods():
    func = ida_funcs.get_func(FUNC_EA)
    if not func:
        log("ERROR: function not found")
        return False

    cfunc = ida_hexrays.decompile(func)
    log(f"Decompiled OK, {len(cfunc.lvars)} lvars")

    # Step 1: Set a test rename to verify persistence
    for lvar in cfunc.lvars:
        if lvar.name == 'v15':
            lvar.name = 'nSkillGDB_ID'
            log(f"  Set v15 → nSkillGDB_ID")
            break

    # Step 2: Try all save methods
    results = {}
    
    # Method 1: modify_user_lvars
    try:
        log("  Trying modify_user_lvars...")
        ida_hexrays.modify_user_lvars(FUNC_EA)
        log("  modify_user_lvars: OK")
        results['modify_user_lvars'] = True
    except Exception as e:
        log(f"  modify_user_lvars FAILED: {e}")
        results['modify_user_lvars'] = False

    # Method 2: build lvinf manually
    try:
        log("  Trying save_user_lvar_settings with lvinf...")
        lvinf = ida_hexrays.lvar_saved_infos_t()
        for lv in cfunc.lvars:
            si = ida_hexrays.lvar_saved_info_t()
            si.ll = lv.location
            si.name = lv.name
            si.type = lv.type
            lvinf.push_back(si)
        ida_hexrays.save_user_lvar_settings(FUNC_EA, lvinf)
        log(f"  save_user_lvar_settings: OK ({len(cfunc.lvars)} lvars saved)")
        results['save_user_lvar_settings'] = True
    except Exception as e:
        log(f"  save_user_lvar_settings FAILED: {e}")
        results['save_user_lvar_settings'] = False

    # Method 3: hx_save_user_lvar_settings
    try:
        log("  Trying hx_save_user_lvar_settings...")
        lvinf2 = ida_hexrays.lvar_saved_infos_t()
        for lv in cfunc.lvars:
            si = ida_hexrays.lvar_saved_info_t()
            si.ll = lv.location
            si.name = lv.name
            si.type = lv.type
            lvinf2.push_back(si)
        ida_hexrays.hx_save_user_lvar_settings(FUNC_EA, lvinf2)
        log(f"  hx_save_user_lvar_settings: OK")
        results['hx_save_user_lvar_settings'] = True
    except Exception as e:
        log(f"  hx_save_user_lvar_settings FAILED: {e}")
        results['hx_save_user_lvar_settings'] = False

    return results

def main():
    ida_auto.auto_wait()
    log("=== Lvar save API test ===")
    results = test_save_methods()
    
    success = any(results.values())
    if success:
        log(f"\nAt least one method worked: {[k for k,v in results.items() if v]}")
        log("Done - will verify persistence on next export")
    else:
        log("\nNO method worked - need deeper investigation")
        # Check if save_user_lvar_settings accepts just func_ea
        for method_name in ['save_user_lvar_settings', 'hx_save_user_lvar_settings']:
            try:
                func = getattr(ida_hexrays, method_name)
                log(f"  {method_name} signature: {func}")
                log(f"  {method_name} doc: {func.__doc__}")
            except:
                pass
    
    ida_pro.beep()

if __name__ == '__main__':
    main()
