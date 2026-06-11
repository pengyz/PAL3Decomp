"""
Quick IDAPython: query ScreenEffectMgr _field_ offsets binary context.
"""
import ida_auto, ida_funcs, ida_bytes, ida_name, ida_ua, ida_idp
import idautils, idc
import json, os, struct

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")

def main():
    ida_auto.auto_wait()
    
    # Load ScreenEffectMgr annotation
    struct_path = os.path.join(ANNOTATIONS_DIR, "structs", "ScreenEffectMgr.json")
    with open(struct_path) as f:
        sdata = json.load(f)
    
    sname = sdata.get("name", "ScreenEffectMgr")
    print(f"[*] Class: {sname}")
    
    # Get _field_ offsets
    todos = {}
    for off_str, m in sdata.get("known_members", {}).items():
        if m["name"].startswith("_field_"):
            todos[int(off_str)] = m
    
    print(f"[*] {len(todos)} _field_ offsets: {[hex(k) for k in sorted(todos.keys())]}")
    
    # Get methods
    methods = []
    for addr_str, minfo in sdata.get("methods", {}).items():
        mname = minfo.get("name", "")
        method_short = mname.split("::")[-1] if "::" in mname else mname
        ea = int(addr_str, 16)
        func = ida_funcs.get_func(ea)
        if func:
            methods.append((ea, func.size(), method_short))
        else:
            print(f"  [!] No function at {addr_str} for {method_short}")
    
    print(f"[*] {len(methods)} methods with valid functions")
    
    target_offsets = list(todos.keys())
    TEXT_START = 0x00401000
    TEXT_END = 0x005695D0
    
    results = {}
    
    for ea, func_size, method_name in methods:
        binary = ida_bytes.get_bytes(ea, func_size)
        if not binary:
            continue
        
        for offset in target_offsets:
            needle = struct.pack("<I", offset)
            pos = 0
            while pos < len(binary):
                idx = binary.find(needle, pos)
                if idx == -1:
                    break
                if idx >= 2:
                    modrm = binary[idx - 1]
                    opcode = binary[idx - 2]
                    mod = (modrm >> 6) & 3
                    rm = modrm & 7
                    
                    if mod == 2 and rm != 4:  # mod=10 (disp32), no SIB
                        insn_ea = ea + idx - 2
                        disasm = idc.GetDisasm(insn_ea)
                        
                        # access type
                        access = "unknown"
                        if opcode in (0x8B, 0x8D):
                            access = "load" if opcode == 0x8B else "lea"
                        elif opcode == 0x89:
                            access = "store"
                        
                        if offset not in results:
                            results[offset] = []
                        results[offset].append({
                            "method": method_name,
                            "va": "0x%08X" % insn_ea,
                            "access": access,
                            "disasm": disasm[:80],
                        })
                pos = idx + 1
    
    # Print results
    print(f"\n[*] Results for ScreenEffectMgr _field_ offsets:")
    for offset in sorted(results.keys()):
        refs = results[offset]
        print(f"\noffset 0x{offset:X} ({offset}): {len(refs)} refs")
        print(f"  current type: {todos.get(offset, {}).get('type', '?')}")
        for r in refs[:10]:
            print(f"  [{r['access']:6s}] {r['method']:40s} {r['disasm']}")
        if len(refs) > 10:
            print(f"  ... ({len(refs) - 10} more)")
    
    if not results:
        print("\n[!] No binary hits found. Checking methods more carefully...")
        for ea, func_size, mn in methods:
            print(f"  {mn:40s} @ 0x{ea:08X} size={func_size}")
    
    idc.qexit(0)

main()
