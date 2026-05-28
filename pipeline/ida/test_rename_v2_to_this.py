"""
Experiment: rename v2 to 'this' - what does Hex-Rays do with duplicate name?
"""
import ida_hexrays, ida_funcs, ida_pro, os

FUNC_EA = 0x00435830
LOG_FILE = os.path.join(os.path.dirname(__file__), "_logs", "rename_v2_test.txt")

def main():
    with open(LOG_FILE, 'w') as f:
        func = ida_funcs.get_func(FUNC_EA)
        cfunc = ida_hexrays.decompile(func)
        
        # Find v2
        v2_lvar = None
        this_lvar = None
        for lv in cfunc.lvars:
            if lv.name == 'v2':
                v2_lvar = lv
            if lv.name == 'this':
                this_lvar = lv
        
        f.write(f"v2:   loc.is_reg1={v2_lvar.location.is_reg1()}, reg1={v2_lvar.location.reg1() if v2_lvar else 'N/A'}\n")
        if this_lvar:
            f.write(f"this: loc.is_reg1={this_lvar.location.is_reg1()}, reg1={this_lvar.location.reg1()}\n")
        else:
            f.write("this: NOT FOUND\n")
        
        if v2_lvar:
            # Try renaming v2 → 'this' using rename_lvar API
            f.write("\nTrying rename_lvar(v2→this)...\n")
            try:
                result = ida_hexrays.rename_lvar(FUNC_EA, 'v2', 'this')
                f.write(f"rename_lvar returned: {result}\n")
            except Exception as e:
                f.write(f"rename_lvar FAILED: {e}\n")
            
            # Also try direct assignment
            f.write("\nTrying lvar.name = 'this'...\n")
            try:
                old_name = v2_lvar.name
                v2_lvar.name = 'this'
                f.write(f"v2_lvar.name changed to '{v2_lvar.name}'\n")
            except Exception as e:
                f.write(f"Direct assignment FAILED: {e}\n")
        else:
            f.write("v2: NOT FOUND\n")
        
        # Re-decompile and show
        cfunc2 = ida_hexrays.decompile(func)
        code = str(cfunc2)
        f.write(f"\nDecompiled code:\n")
        for line in code.split('\n')[:8]:
            f.write(f"  {line}\n")
        
        # Count v2 and this references
        v2_count = code.count('v2') - code.count('v2_')  # rough
        this_count = code.count('this')
        f.write(f"\nv2 references in code: {v2_count}\n")
        f.write(f"this references in code: {this_count}\n")
    
    ida_pro.beep()

if __name__ == '__main__':
    main()
