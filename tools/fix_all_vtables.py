#!/usr/bin/env python3
"""Universal vtable fix: keep only primary vtable for each class.

Strategy:
1. For each class with vtables in annotation, read binary vtable data
2. Detect merged adjustment vtables via repeating pattern
3. Keep only primary sub-table (entries before first repeat)
4. If primary address differs from annotation address, use correct one

Usage:
    python tools/fix_all_vtables.py --dry    # Preview
    python tools/fix_all_vtables.py          # Apply fixes
"""
import json, struct, os, sys
from collections import Counter, defaultdict

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
    return v2o

v2o, ib = pe_init() if False else (None, None)

def _v2o(va):
    global v2o, ib
    if v2o is None:
        _pe_init = pe_init
        # hack: just read sections again
        with open(EXE_PATH, 'rb') as f:
            f.seek(0x3C); po = struct.unpack('<I', f.read(4))[0]
            f.seek(po+0x34); ib = struct.unpack('<I', f.read(4))[0]
            f.seek(po+0xF8)
            for _ in range(4):
                nm = f.read(8).rstrip(b'\0').decode()
                vs = struct.unpack('<I', f.read(4))[0]
                vaa = struct.unpack('<I', f.read(4))[0]
                rs = struct.unpack('<I', f.read(4))[0]
                ro = struct.unpack('<I', f.read(4))[0]
                f.read(16)
                if vaa <= (va-ib) < vaa+vs:
                    return ro + ((va-ib) - vaa)
        return None
    return v2o(va)

def read_vtable(va, n):
    off = _v2o(va)
    if off is None: return None
    with open(EXE_PATH, 'rb') as f:
        f.seek(off)
        return [struct.unpack('<I', f.read(4))[0] for _ in range(n)]

def find_primary_vtable(binary):
    """Find primary vtable from merged binary data.
    Returns (start_offset, count) or None if no merge detected.
    """
    n = len(binary)
    if n < 4: return None
    
    # Find repeating pattern
    freq = Counter(binary)
    common = [v for v, c in freq.most_common(10) if c >= 2 and 0x00400000 < v < 0x0056A000]
    if len(common) < 2: return None
    
    # Use most common value as anchor
    anchor = common[0]
    positions = [i for i, x in enumerate(binary) if x == anchor]
    if len(positions) < 2: return None
    
    stride = positions[1] - positions[0]
    if stride <= 0 or stride >= n: return None
    
    # Check if next common values confirm the stride
    confirm = 0
    for v in common[1:4]:
        p = [i for i, x in enumerate(binary) if x == v]
        if len(p) >= 2 and (p[1] - p[0]) == stride:
            confirm += 1
    
    if confirm < 1: return None  # Not confident
    
    # Primary = entries before first repeat
    primary_end = positions[1]
    
    # Skip header entries (non-function at slot 0)
    primary_start = 0
    if primary_end > 0 and not (0x00400000 < binary[0] < 0x0056A000):
        primary_start = 1
    
    return (primary_start, primary_end - primary_start)


def fix_class_vtables(cls_name, data):
    """Fix vtables for one class. Returns True if changed."""
    vts = data.get('vtables', [])
    if not vts: return False
    
    methods = data.get('methods', {})
    changed = False
    new_vts = []
    
    # Track address ranges we've processed
    kept_ranges = []
    
    for vi, vt in enumerate(vts):
        addr_str = vt.get('addr', '')
        if not addr_str: continue
        addr = int(addr_str, 16)
        slots = vt.get('slots', [])
        n = len(slots)
        
        # Check if this vtable overlaps with a previously kept one
        vt_end = addr + n * 4
        overlaps = False
        for kept_addr, kept_end in kept_ranges:
            if addr < kept_end and vt_end > kept_addr:
                overlaps = True
                break
        
        if overlaps:
            print(f"  [{vi}] @{addr_str}: REMOVED (overlaps with kept range)")
            changed = True
            continue
        
        binary = read_vtable(addr, n)
        if binary is None:
            new_vts.append(vt)
            kept_ranges.append((addr, addr + n * 4))
            continue
        
        primary = find_primary_vtable(binary)
        
        if primary:
            start, count = primary
            new_addr = addr + start * 4
            new_slots = slots[start:start+count]
            new_vts.append({
                'addr': f'0x{new_addr:08X}',
                'slots': [dict(s) for s in new_slots],
            })
            kept_ranges.append((new_addr, new_addr + count * 4))
            if n != count:
                print(f"  [{vi}] @{addr_str}: {n}→{count} slots @0x{new_addr:08X}")
                changed = True
            else:
                print(f"  [{vi}] @{addr_str}: {count} slots (kept)")
        else:
            new_vts.append(vt)
            kept_ranges.append((addr, addr + n * 4))
    
    if changed:
        data['vtables'] = new_vts
    
    return changed


def main():
    dry_run = '--dry' in sys.argv
    
    # Load annotations
    ann_data = {}
    for fn in sorted(os.listdir(ANN_DIR)):
        if fn.endswith('.json') and '.fixed' not in fn:
            try:
                a = json.load(open(os.path.join(ANN_DIR, fn)))
                ann_data[a.get('name', fn[:-5])] = a
            except:
                pass
    
    # Process all classes with vtables
    total_fixed = 0
    for cls in sorted(ann_data):
        data = ann_data[cls]
        vts = data.get('vtables', [])
        if not vts: continue
        
        print(f"\n{cls}:")
        if fix_class_vtables(cls, data):
            if not dry_run:
                fp = os.path.join(ANN_DIR, f"{cls}.json")
                json.dump(data, open(fp, 'w'), indent=2, ensure_ascii=False)
                print(f"  → WROTE {fp}")
            else:
                print(f"  → DRY RUN: would write")
            total_fixed += 1
    
    print(f"\n{'='*50}")
    print(f"Total classes fixed: {total_fixed}")
    print(f"Mode: {'DRY RUN' if dry_run else 'APPLIED'}")


if __name__ == '__main__':
    main()
