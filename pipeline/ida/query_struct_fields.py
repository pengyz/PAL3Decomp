"""
IDAPython: Analyze ALL methods of a struct, dump every [reg+disp] access
with full instruction context. Output grouped by offset.

Usage: idat -A -S"query_struct_fields.py ClassName" binary.i64
"""
import ida_auto, ida_funcs, ida_hexrays, ida_name, ida_ua
import idautils, idc, json, os, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "struct_field_analysis.json")

ANNOTATIONS_DIR = os.path.join(
    os.path.dirname(os.path.dirname(SCRIPT_DIR)),
    "data", "annotations"
)

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

def get_target_classes():
    for arg in idc.ARGV[1:]:
        if arg and not arg.startswith("-"):
            return [c.strip() for c in arg.split(",") if c.strip()]
    return []

def main():
    ida_auto.auto_wait()
    targets = get_target_classes()
    if not targets:
        print("No target classes specified")
        return
    
    # Collect method addresses for target classes from annotation
    structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    method_addrs = []
    for target in targets:
        fpath = os.path.join(structs_dir, f"{target}.json")
        if not os.path.exists(fpath):
            print(f"  {target}: annotation not found")
            continue
        with open(fpath) as f:
            sdata = json.load(f)
        for akey in sdata.get("methods", {}):
            try:
                ea = int(akey.replace("0x0x", "0x"), 16)
                if TEXT_START <= ea <= TEXT_END:
                    method_addrs.append((target, ea, sdata["methods"][akey].get("name","?")))
            except:
                pass
        
        # Also check all decomp files for this class
        decomp_dir = os.path.join(
            os.path.dirname(os.path.dirname(SCRIPT_DIR)),
            "asm", "pal3", "decomp"
        )
        if os.path.isdir(decomp_dir):
            import glob as _g
            for fn in _g.glob(f"{decomp_dir}/{target}_*.json"):
                try:
                    f = json.load(open(fn))
                    addr = f.get("address", "")
                    if addr:
                        ea = int(addr, 16)
                        if TEXT_START <= ea <= TEXT_END:
                            method_addrs.append((target, ea, f.get("name","?")))
                except:
                    pass
    
    # Analyze each method
    results = {}
    seen_pairs = set()
    
    for cls, ea, fname in method_addrs:
        if (cls, ea) in seen_pairs:
            continue
        seen_pairs.add((cls, ea))
        
        func = ida_funcs.get_func(ea)
        if not func:
            continue
        
        # Walk the function bytes and find [reg+disp32] accesses
        accesses = []
        for head in idautils.Heads(func.start_ea, func.end_ea):
            insn = ida_ua.insn_t()
            if not ida_ua.decode_insn(insn, head):
                continue
            
            for i in range(insn.size):
                op = insn.ops[i]
                if op.type == ida_ua.o_mem:  # direct memory
                    accesses.append({
                        'va': hex(head),
                        'type': 'mem',
                        'addr': hex(op.addr),
                        'mnem': idc.print_insn_mnem(head),
                        'width': ida_ua.get_dtype_size(op.dtype) if op.dtype > 0 else 0,
                    })
                elif op.type == ida_ua.o_displ:  # [reg+disp]
                    width = ida_ua.get_dtype_size(op.dtype) if op.dtype > 0 else 0
                    accesses.append({
                        'va': hex(head),
                        'type': 'displ',
                        'reg': ida_ua.get_reg_name(op.reg, 4) if op.reg > 0 else '',
                        'disp': op.addr,
                        'mnem': idc.print_insn_mnem(head),
                        'width': width,
                        'disasm': idc.generate_disasm_line(head, 0),
                    })
        
        if accesses:
            key = f"{cls}::{fname}"
            results[key] = {
                'address': hex(ea),
                'accesses': accesses
            }
    
    # Write output
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, 'w') as f:
        json.dump(results, f, indent=2)
    
    print(f"\nAnalyzed {len(results)} functions, output to {OUTPUT_FILE}")

if __name__ == '__main__':
    main()
