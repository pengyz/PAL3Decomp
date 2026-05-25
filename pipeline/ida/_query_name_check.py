"""Check actual IDA names for specific addresses after apply_annotations."""
import ida_auto, ida_name, ida_funcs, idautils, idc
import json, os

ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

# Check these specific addresses
CHECK_ADDRS = [0x0053D150, 0x0053DF70]

results = {}
for ea in CHECK_ADDRS:
    name = ida_name.get_name(ea)
    results[hex(ea)] = {"name": name, "has_func": bool(ida_funcs.get_func(ea))}
    print("0x%08X: '%s'" % (ea, name))

# Also find ALL functions containing 'GetInstance' in their IDA name
print("\nAll functions with 'GetInstance' in name:")
for ea in idautils.Functions(0x401000, 0x5695D0):
    name = ida_name.get_name(ea)
    if name and 'GetInstance' in name:
        print("  0x%08X: '%s'" % (ea, name))

# Check: is there a name conflict? Search for any name containing 'df70'
print("\nFunctions with 'df70' in name:")
for ea in idautils.Functions(0x401000, 0x5695D0):
    name = ida_name.get_name(ea)
    if name and 'df70' in name.lower():
        print("  0x%08X: '%s'" % (ea, name))

output_path = os.path.join(LOG_DIR, "name_check.json")
with open(output_path, 'w') as f:
    json.dump(results, f, indent=2)

idc.qexit(0)
