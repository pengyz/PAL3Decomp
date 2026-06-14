#!/usr/bin/env python3
"""Fix merged vtables: keep only primary vtable, remove adjustment duplicates.

Usage:
    python tools/apply_vtable_fix.py CLASS_NAME   # Fix one class
    python tools/apply_vtable_fix.py --all        # Fix all affected classes
    python tools/apply_vtable_fix.py --dry CLASS  # Preview without writing
"""
import json, struct, os, sys
from collections import Counter

PROJ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN_DIR = os.path.join(PROJ, "data/annotations/structs")
EXE_PATH = os.path.join(PROJ, "original/PAL3.exe")

def pe_init():
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
            if sva <= rva < sva+svs:
                return ro + (rva - sva)
        return None
    return v2o, ib

v2o, ib = pe_init()

def read_vtable(va, n):
    off = v2o(va)
    if off is None: return None
    with open(EXE_PATH, 'rb') as f:
        f.seek(off)
        return [struct.unpack('<I', f.read(4))[0] for _ in range(n)]

def find_primary_subtable(binary):
    """Find primary vtable from merged binary data.
    Returns (start_offset, num_slots) for the primary sub-table.
    """
    n = len(binary)
    if n < 3: return (0, n)
    
    # Find first function pointer
    first_func = None
    for i, v in enumerate(binary):
        if 0x00400000 < v < 0x0056A000:
            first_func = i
            break
    if first_func is None: return (0, n)
    
    # Check for repeating pattern from first_func
    freq = Counter(binary)
    common = [v for v, c in freq.most_common(8) if c >= 2 and 0x00400000 < v < 0x0056A000]
    
    if len(common) < 2:
        return (first_func, n - first_func)
    
    # Use the first common value to detect stride
    anchor_val = common[0]
    positions = [i for i, x in enumerate(binary) if x == anchor_val]
    
    if len(positions) < 2:
        return (first_func, n - first_func)
    
    # Stride = distance between first two occurrences
    stride = positions[1] - positions[0]
    
    if stride <= 0 or stride >= n:
        return (first_func, n - first_func)
    
    # Primary sub-table: from first_func to first_func + stride
    primary_start = first_func
    primary_end = min(first_func + stride, n)
    
    # But verify: the first sub-table might include a header at slot 0
    # If slot 0 is not a valid function address, skip it
    if primary_start == 0 and not (0x00400000 < binary[0] < 0x0056A000):
        if len(binary) > 1 and 0x00400000 < binary[1] < 0x0056A000:
            primary_start = 1
    
    return (primary_start, primary_end - primary_start)


def fix_vtables(cls_name, methods, vts_original):
    """Fix vtables for a class: keep only primary vtable."""
    fixed_vts = []
    
    for vi, vt in enumerate(vts_original):
        addr_str = vt.get('addr', '')
        if not addr_str: continue
        addr = int(addr_str, 16)
        slots = vt.get('slots', [])
        n = len(slots)
        
        binary = read_vtable(addr, n)
        if binary is None:
            print(f"    [{vi}] @{addr_str}: CANNOT READ BINARY, skipping")
            fixed_vts.append(vt)
            continue
        
        # Detect primary sub-table
        start, count = find_primary_subtable(binary)
        
        if count < n and count >= 3:
            # Take only primary sub-table
            new_slots = slots[start:start+count]
            new_addr = addr + start * 4
            fixed_vts.append({
                'addr': f'0x{new_addr:08X}',
                'slots': [dict(s) for s in new_slots],
            })
            print(f"    [{vi}] @{addr_str}: {n} slots → {count} slots @0x{new_addr:08X} (primary)")
        else:
            fixed_vts.append(vt)
            print(f"    [{vi}] @{addr_str}: {n} slots → kept as-is")
    
    return fixed_vts


def main():
    dry_run = '--dry' in sys.argv
    all_mode = '--all' in sys.argv
    
    # Load annotation data
    ann_data = {}
    for fn in sorted(os.listdir(ANN_DIR)):
        if fn.endswith('.json') and '.fixed' not in fn:
            a = json.load(open(os.path.join(ANN_DIR, fn)))
            ann_data[a.get('name', fn[:-5])] = a
    
    # Classes known to be affected
    affected = [
        'CCBControlWindow', 'CCBFiveNimbusWindow', 'CCBItemWindow',
        'CCBResultWindow', 'CEffectSystem', 'PalScript', 'UICaption',
        'UIFrameWnd', 'UIWnd', 'UIScenePanel', 'UIStatic',
    ]
    
    targets = [t for t in sys.argv if not t.startswith('--') and t != sys.argv[0]]
    if not targets and all_mode:
        targets = affected
    
    for cls in targets:
        if cls not in ann_data:
            print(f"SKIP {cls}: not in annotation")
            continue
        
        data = ann_data[cls]
        vts = data.get('vtables', [])
        if not vts:
            print(f"SKIP {cls}: no vtables")
            continue
        
        methods = data.get('methods', {})
        print(f"\n{cls}:")
        
        old_count = len(vts)
        new_vts = fix_vtables(cls, methods, vts)
        
        if new_vts != vts:
            data['vtables'] = new_vts
            fp = os.path.join(ANN_DIR, f"{cls}.json")
            if dry_run:
                print(f"  DRY RUN: would write {fp} ({old_count}vt→{len(new_vts)}vt)")
            else:
                json.dump(data, open(fp, 'w'), indent=2, ensure_ascii=False)
                print(f"  WROTE {fp} ({old_count}vt→{len(new_vts)}vt)")
        else:
            print(f"  No change needed")


if __name__ == '__main__':
    main()
