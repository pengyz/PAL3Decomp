#!/usr/bin/env python3
"""Generate corrected vtable annotations by splitting merged sub-tables.

Reads annotation JSON, binary vtable data, detects merged sub-tables,
and outputs corrected vtable definitions ready for manual verification.

Usage:
    python tools/fix_vtable_splits.py CLASS_NAME    # Show fix for one class
    python tools/fix_vtable_splits.py --all         # Show all affected
    python tools/fix_vtable_splits.py --apply CLASS  # Apply fix (careful!)
"""
import json, struct, os, sys
from collections import Counter

PROJ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDA_STRUCTS = os.path.join(PROJ, "asm/pal3/ida_structs.json")
ANN_DIR = os.path.join(PROJ, "data/annotations/structs")
EXE_PATH = os.path.join(PROJ, "original/PAL3.exe")

def _pe_sections():
    with open(EXE_PATH, 'rb') as f:
        f.seek(0x3C); po = struct.unpack('<I', f.read(4))[0]
        f.seek(po+0x34); ib = struct.unpack('<I', f.read(4))[0]
        f.seek(po+0xF8)
        secs = []
        for _ in range(4):
            nm = f.read(8).rstrip(b'\0').decode()
            vs = struct.unpack('<I', f.read(4))[0]
            va = struct.unpack('<I', f.read(4))[0]
            rs = struct.unpack('<I', f.read(4))[0]
            ro = struct.unpack('<I', f.read(4))[0]
            f.read(16)
            secs.append((nm, va, vs, ro, rs))
    def v2o(va):
        rva = va - ib
        for nm, sva, svs, ro, rs in secs:
            if sva <= rva < sva+svs: return ro + (rva - sva)
        return None
    return v2o

def read_binary_vtable(va_str, n):
    addr = int(va_str, 16)
    v2o = _pe_sections()
    off = v2o(addr)
    if off is None: return None
    with open(EXE_PATH, 'rb') as f:
        f.seek(off)
        return [struct.unpack('<I', f.read(4))[0] for _ in range(n)]

def detect_subs(binary, methods, slots_data):
    """Detect sub-vtables recursively. Returns list of split slot indices."""
    n = len(binary)
    if n < 4: return None
    
    # Find repeating base-class function addresses
    freq = Counter(binary)
    common_val = [v for v, c in freq.most_common(8) if c >= 2 and v > 0x00400000]
    if len(common_val) < 2: return None
    
    candidates = {}
    for v in common_val[:5]:
        pos = [i for i, x in enumerate(binary) if x == v]
        if len(pos) >= 2:
            candidates[v] = pos
    
    if not candidates: return None
    anchor = max(candidates.values(), key=len)
    splits = sorted(set(anchor))
    if len(splits) < 2: return None
    
    # Validate and build final split list
    base = splits[0]
    valid = [base]
    for sp in splits[1:]:
        off = sp - base
        ok = True
        for v, pos_list in candidates.items():
            ref = pos_list[0]
            exp = ref + off
            if exp < n and binary[exp] != v and v != binary[sp] and binary[exp] != binary[sp]:
                ok = False
                break
        if ok: valid.append(sp)
    
    if len(valid) < 2: return None
    return valid


def generate_fix(cls_name, cls_data):
    """Generate corrected vtable definitions."""
    vts = cls_data.get('vtables', [])
    if not vts: return None
    
    methods = cls_data.get('methods', {})
    bc = cls_data.get('base_class', cls_data.get('base_class', None))
    
    result = {
        'name': cls_name,
        'base_class': bc,
        'base_size': cls_data.get('base_size'),
        'binary_size': cls_data.get('binary_size'),
        'known_members': cls_data.get('known_members', {}),
        'methods': methods,
        'vtables': [],
    }
    
    # Copy non-vtable fields
    for k in ['deleted_members', 'is_union', 'pack', '_flexible', 'nested_types']:
        if k in cls_data:
            result[k] = cls_data[k]
    
    for vi, vt in enumerate(vts):
        addr = vt.get('addr', '')
        slots = vt.get('slots', [])
        n = len(slots)
        binary = read_binary_vtable(addr, n)
        if binary is None:
            result['vtables'].append(vt)  # Keep as-is
            continue
        
        subs = detect_subs(binary, methods, slots)
        if subs and len(subs) >= 2:
            base_addr = int(addr, 16)
            # Build initial sub-tables
            stables = []
            for si in range(len(subs)):
                start = subs[si]
                end = subs[si+1] if si+1 < len(subs) else n
                stables.append((start, end))
            
            # Recursively split sub-tables
            result_vts = []
            for start, end in stables:
                sub_binary = binary[start:end]
                sub_slots_raw = [dict(slots[j]) if j < len(slots) else {} for j in range(start, end)]
                deeper = detect_subs(sub_binary, methods, sub_slots_raw)
                if deeper and len(deeper) >= 2:
                    for si in range(len(deeper)):
                        ds = deeper[si]
                        de = deeper[si+1] if si+1 < len(deeper) else len(sub_binary)
                        real_s = start + ds
                        real_e = start + de
                        sa = base_addr + real_s * 4
                        s_slots = [dict(slots[j]) if j < len(slots) else {} for j in range(real_s, real_e)]
                        result_vts.append({'addr': f'0x{sa:08X}', 'slots': s_slots})
                else:
                    sa = base_addr + start * 4
                    result_vts.append({'addr': f'0x{sa:08X}', 'slots': sub_slots_raw})
            
            for vt in result_vts:
                result['vtables'].append(vt)
            print(f"  ✓ Split vtable[{vi}] @{addr} into {len(result_vts)} sub-tables")
        else:
            result['vtables'].append(vt)
    
    return result


def main():
    targets = sys.argv[1:]
    apply_mode = False
    if '--apply' in targets:
        apply_mode = True
        targets.remove('--apply')
    
    ida_structs = json.load(open(IDA_STRUCTS))
    ann_data = {}
    for fn in sorted(os.listdir(ANN_DIR)):
        if fn.endswith('.json'):
            a = json.load(open(os.path.join(ANN_DIR, fn)))
            ann_data[a.get('name', fn[:-5])] = a
    
    if not targets or '--all' in targets:
        classes = sorted(k for k, v in ida_structs.items()
                        if isinstance(v, dict) and v.get('vtables'))
    else:
        classes = [t for t in targets if not t.startswith('--')]
    
    for cls in classes:
        data = ann_data.get(cls, ida_structs.get(cls, {}))
        if not data or not data.get('vtables'):
            continue
        
        print(f"\n{'='*60}")
        print(f"  {cls}")
        print(f"{'='*60}")
        
        fix = generate_fix(cls, data)
        if fix and len(fix['vtables']) > len(data.get('vtables', [])):
            print(f"  Original: {len(data['vtables'])} vtable(s)")
            print(f"  Proposed: {len(fix['vtables'])} vtable(s)")
            for vi, vt in enumerate(fix['vtables']):
                print(f"    [{vi}] @{vt['addr']} ({len(vt['slots'])} slots)")
            
            fp = os.path.join(ANN_DIR, f"{cls}.json.fixed")
            json.dump(fix, open(fp, 'w'), indent=2, ensure_ascii=False)
            print(f"  Written: {fp}")
        else:
            print(f"  No split needed (or insufficient data)")


if __name__ == '__main__':
    main()
