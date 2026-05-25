"""Find all functions in IDB that are NOT in annotations.
These are functions IDA auto-detected but we never annotated.
"""
import ida_auto, ida_name, ida_funcs, idautils, idc
import json, os

ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

# Load annotations
ann_path = os.path.join(PROJECT_ROOT, "data", "annotations", "functions.json")
with open(ann_path, 'r', encoding='utf-8') as f:
    ann_funcs = json.load(f)
ann_addrs = set(int(a, 16) for a in ann_funcs.keys())

# Load skip list
skip_path = os.path.join(PROJECT_ROOT, "data", "annotations", "skip_functions.json")
with open(skip_path, 'r', encoding='utf-8') as f:
    skip_funcs = json.load(f)
skip_addrs = set(int(a, 16) for a in skip_funcs.keys())

# Scan all functions in .text section
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

unlisted = []
for ea in idautils.Functions(TEXT_START, TEXT_END):
    if ea in ann_addrs or ea in skip_addrs:
        continue
    func = ida_funcs.get_func(ea)
    if not func:
        continue
    name = ida_name.get_name(ea) or ""
    size = func.size()
    # Skip tiny thunks (1-2 bytes)
    if size <= 2:
        continue
    unlisted.append({
        "address": "0x%08X" % ea,
        "name": name,
        "size": size,
    })

print("[*] Functions in IDB but NOT in annotations or skip: %d" % len(unlisted))
print("[*] (Annotated: %d, Skipped: %d)" % (len(ann_addrs), len(skip_addrs)))

# Categorize
named_non_sub = [f for f in unlisted if f["name"] and not f["name"].startswith("sub_")]
sub_only = [f for f in unlisted if f["name"].startswith("sub_") or not f["name"]]

print("[*] Named (non-sub_): %d" % len(named_non_sub))
print("[*] Unnamed (sub_): %d" % len(sub_only))

# Show named ones (these are the problematic ones that cause _XXXX suffix issues)
print("\nNamed unlisted functions (cause IDA naming conflicts):")
for f in sorted(named_non_sub, key=lambda x: x["address"])[:50]:
    print("  %s (%dB) %s" % (f["address"], f["size"], f["name"]))

output_path = os.path.join(LOG_DIR, "unlisted_functions.json")
with open(output_path, 'w', encoding='utf-8') as f:
    json.dump({"named": named_non_sub, "unnamed": sub_only}, f, indent=2, ensure_ascii=False)
print("\n[*] Full results: %s" % output_path)

idc.qexit(0)
