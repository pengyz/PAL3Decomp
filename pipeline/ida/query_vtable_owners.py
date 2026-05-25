"""Query: find which constructors write each CCBUI-family vtable address.
Run on work IDB: idat -A -S"pipeline/ida/query_vtable_owners.py" original/PAL3.exe.i64
"""
import ida_auto, ida_xref, ida_name, ida_funcs, idc, idautils
import json, os

ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)

# Vtable addresses to investigate
VTABLES = {
    0x005704A8: "off_5704A8 (labeled CCBUI)",
    0x005704C8: "off_5704C8 (labeled CCBUI)", 
    0x005706CC: "off_5706CC (labeled CCBUI)",
    0x005704E4: "off_5704E4 (labeled CCBUIPanel)",
    0x00570500: "off_570500 (labeled CCBItemWindow)",
    0x0057051C: "off_57051C (labeled CCBControlWindow)",
    0x00570538: "off_570538 (labeled CCBLineupWindow)",
    0x00570570: "off_570570 (labeled CCBSkillWindow)",
    0x0057058C: "off_57058C (labeled CCBParabolaWindow)",
    0x005705D0: "off_5705D0 (labeled CCBProtectWindow)",
}

results = {}
for vt_addr, label in VTABLES.items():
    xrefs = []
    for xref in idautils.XrefsTo(vt_addr):
        func = ida_funcs.get_func(xref.frm)
        if func:
            func_name = ida_name.get_name(func.start_ea) or ("sub_%X" % func.start_ea)
            xrefs.append({
                "from_addr": "0x%08X" % xref.frm,
                "func_addr": "0x%08X" % func.start_ea,
                "func_name": func_name,
            })
    results[("0x%08X" % vt_addr)] = {
        "label": label,
        "xref_count": len(xrefs),
        "xrefs": xrefs[:10],  # limit to first 10
    }
    print("[*] %s: %d xrefs" % (label, len(xrefs)))
    for x in xrefs[:5]:
        print("    <- %s (%s)" % (x["func_name"], x["func_addr"]))

output_path = os.path.join(LOG_DIR, "vtable_owners.json")
with open(output_path, 'w', encoding='utf-8') as f:
    json.dump(results, f, indent=2, ensure_ascii=False)
print("[*] Results written to %s" % output_path)

idc.qexit(0)
