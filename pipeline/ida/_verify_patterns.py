import json, traceback, sys
try:
    import ida_auto, ida_funcs, ida_hexrays, idautils, idc
    ida_auto.auto_wait()
    
    addr = 0x43DE40
    r = {'addr': hex(addr)}
    r['func_name'] = idc.get_func_name(addr)
    r['type'] = idc.get_type(addr)
    
    try:
        cfunc = ida_hexrays.decompile(addr)
        code = str(cfunc)
        r['decomp_preview'] = code[:2000]
    except Exception as e:
        r['decomp_error'] = str(e)
    
    # First 3 instructions
    insns = []
    for head in idautils.FuncItems(addr):
        insns.append(f'0x{head:X}: {idc.generate_disasm_line(head, 0)}')
        if len(insns) >= 8: break
    r['first_insns'] = insns
    
    json.dump(r, open('/tmp/verify_out.json', 'w'), indent=2)
except Exception as e:
    open('/tmp/verify_err.txt', 'w').write(traceback.format_exc())
idc.qexit(0)
