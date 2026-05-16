"""Export all IDA aXxx string names with their addresses."""
import ida_auto, ida_name, idautils, idc, json, os

ida_auto.auto_wait()
script_dir = os.path.dirname(os.path.abspath(__file__))
out_path = os.path.join(script_dir, "_logs", "ida_astring_names.json")
os.makedirs(os.path.dirname(out_path), exist_ok=True)

result = {}
for ea, name in idautils.Names():
    if name and len(name) >= 3 and name[0] == 'a' and name[1].isupper():
        # Read the string at this address
        s = idc.get_strlit_contents(ea, -1, idc.STRTYPE_C)
        if s is not None:
            try:
                result[name] = {"address": "0x%08X" % ea, "value": s.decode('gbk', errors='replace')}
            except:
                result[name] = {"address": "0x%08X" % ea, "value": s.hex()}

with open(out_path, 'w', encoding='utf-8') as f:
    json.dump(result, f, indent=2, ensure_ascii=False)
print("[*] Exported %d aXxx string names" % len(result))
idc.qexit(0)
