import ida_auto, ida_hexrays, ida_funcs, idc
import json, os

ida_auto.auto_wait()

# Read addresses from input file
input_path = 'D:/workspace/PAL3Decomp/pipeline/ida/_logs/raw_query_input.json'
output_path = 'D:/workspace/PAL3Decomp/pipeline/ida/_logs/raw_query_output.json'

if os.path.exists(input_path):
    addrs = json.load(open(input_path))
else:
    addrs = []

results = {}
errors = []

for addr in addrs:
    if isinstance(addr, str):
        addr = int(addr, 16)
    func = ida_funcs.get_func(addr)
    if not func:
        errors.append('no func at 0x%X' % addr)
        continue
    try:
        cfunc = ida_hexrays.decompile(func)
        if cfunc:
            results['0x%08X' % addr] = str(cfunc)
        else:
            errors.append('decompile returned None at 0x%X' % addr)
    except Exception as e:
        errors.append('decompile error at 0x%X: %s' % (addr, str(e)))

with open(output_path, 'w') as f:
    json.dump({'results': results, 'errors': errors}, f, indent=2)

idc.qexit(0)
