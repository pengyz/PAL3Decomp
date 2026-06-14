#!/usr/bin/env python3
"""Detect merged sub-vtables by analyzing repeating patterns in binary vtable data.

MSVC generates multiple vtable entrances for each base class subobject.
These are stored contiguously in .rdata and are often merged into one
oversized vtable by IDA/annotation export. This script detects the boundaries.

Usage:
    python tools/detect_vtable_splits.py CLASS_NAME
    python tools/detect_vtable_splits.py --all
"""
import json, os, sys, struct, re

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDA_STRUCTS = os.path.join(PROJECT_ROOT, "asm", "pal3", "ida_structs.json")
ANN_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
EXE_PATH = os.path.join(PROJECT_ROOT, "original", "PAL3.exe")

def read_pe_sections():
    """Read PE section headers for VA→file offset conversion."""
    with open(EXE_PATH, 'rb') as f:
        f.seek(0x3C)
        pe_off = struct.unpack('<I', f.read(4))[0]
        f.seek(pe_off)
        assert struct.unpack('<I', f.read(4))[0] == 0x4550, "Not a PE file"
        f.seek(pe_off + 0x34)
        image_base = struct.unpack('<I', f.read(4))[0]
        f.seek(pe_off + 6)
        num_sections = struct.unpack('<H', f.read(2))[0]
        f.seek(pe_off + 0xF8)
        sections = []
        for _ in range(num_sections):
            name = f.read(8).rstrip(b'\0').decode()
            vsize = struct.unpack('<I', f.read(4))[0]
            va = struct.unpack('<I', f.read(4))[0]
            rsize = struct.unpack('<I', f.read(4))[0]
            roff = struct.unpack('<I', f.read(4))[0]
            f.read(16)
            sections.append((name, va, vsize, roff, rsize))
    def va_to_offset(va):
        rva = va - image_base
        for name, sec_va, sec_vsize, sec_roff, sec_rsize in sections:
            if sec_va <= rva < sec_va + sec_vsize:
                return sec_roff + (rva - sec_va)
        return None
    return va_to_offset


def read_vtable_slots(exe_path, va_addr, num_slots):
    """Read function pointers from binary vtable at va_addr."""
    va_to_offset = read_pe_sections()
    off = va_to_offset(va_addr)
    if off is None:
        return None
    slots = []
    with open(exe_path, 'rb') as f:
        f.seek(off)
        for _ in range(num_slots):
            val = struct.unpack('<I', f.read(4))[0]
            slots.append(val)
    return slots


def detect_sub_vtables(slots):
    """Detect sub-vtable boundaries in merged vtable by finding repeating patterns.
    
    MSVC adds the same base-class vtable entries in each sub-table.
    Find the positions where a slot value repeats — these are sub-table starts.
    
    Returns list of split slot indices.
    """
    n = len(slots)
    if n < 4:
        return []
    
    # Find the most common slot values (base class inherited functions)
    from collections import Counter
    freq = Counter(slots)
    # Get top values that appear 2+ times and are unique
    common = [v for v, c in freq.most_common(10) if c >= 2]
    
    if len(common) < 2:
        return []
    
    # For each common value, find its first occurrence (assumed in first sub-table)
    # and then find all later occurrences — these mark sub-table boundaries
    first_positions = {}
    for v in common[:5]:  # Limit to 5 common values
        positions = [i for i, x in enumerate(slots) if x == v]
        if len(positions) >= 2:
            stride = min(p2 - p1 for p1, p2 in zip(positions, positions[1:]))
            first_positions[v] = {'first': positions[0], 'stride': stride, 'all': positions}
    
    if not first_positions:
        return []
    
    # Use the most common value's first occurrence as reference
    anchor = max(first_positions.values(), key=lambda x: len(x['all']))
    splits = sorted(set(anchor['all']))
    
    # Filter: only keep splits where ALL common values also appear
    # at the expected position relative to each split
    valid_splits = [splits[0]]
    for sp in splits[1:]:
        expected_offsets = {}
        matching = True
        for v, info in first_positions.items():
            expected_pos = info['first']
            if expected_pos + (sp - splits[0]) < n:
                if slots[expected_pos + (sp - splits[0])] != v and slots[expected_pos + (sp - splits[0])] == slots[sp]:
                    matching = False
                    break
        if matching:
            valid_splits.append(sp)
    
    return valid_splits


def analyze_class_vtables(cls_name, ida_structs, ann_data):
    """Analyze a class's vtables for sub-vtable merging."""
    cls_data = ida_structs.get(cls_name, {})
    vtables = cls_data.get('vtables', [])
    methods = cls_data.get('methods', {})
    
    if not vtables:
        # Fall back to annotation vtables
        if ann_data:
            vtables = ann_data.get('vtables', [])
    
    print(f"\n{'='*60}")
    print(f"Class: {cls_name}")
    print(f"{'='*60}")
    
    for vi, vt in enumerate(vtables):
        addr_str = vt.get('addr', '')
        if not addr_str:
            continue
        addr = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
        slots_data = vt.get('slots', [])
        n_slots = len(slots_data)
        
        # Read binary vtable
        binary = read_vtable_slots(EXE_PATH, addr, n_slots)
        if binary is None:
            print(f"  vtable[{vi}] @{addr_str}: Cannot read binary (out of range)")
            continue
        
        # Detect sub-vtables
        splits = detect_sub_vtables(binary)
        if len(splits) < 2:
            print(f"  vtable[{vi}] @{addr_str} ({n_slots} slots): No sub-tables detected")
            continue
        
        print(f"  vtable[{vi}] @{addr_str} ({n_slots} slots):")
        print(f"    Proposed {len(splits)} sub-vtables (at slots {splits}):")
        
        for si in range(len(splits)):
            start = splits[si]
            end = splits[si + 1] if si + 1 < len(splits) else n_slots
            sub_addr = addr + start * 4
            sub_slots = binary[start:end]
            print(f"\n      Sub-table[{si}] @0x{sub_addr:08X} ({end-start} slots):")
            for j, val in enumerate(sub_slots):
                # Find slot name from annotation
                slot_idx = start + j
                slot_info = slots_data[slot_idx] if slot_idx < len(slots_data) else {}
                slot_addr = slot_info.get('addr', '')
                slot_from = slot_info.get('from', '')
                name = ''
                if slot_addr and slot_addr in methods:
                    name = methods[slot_addr].get('name', '').split('::')[-1]
                print(f"        [{j}] 0x{val:08X}  {'('+name+')' if name else ''} from={slot_from}")


def main():
    ida_structs = json.load(open(IDA_STRUCTS))
    
    ann_data = {}
    if os.path.isdir(ANN_DIR):
        for fn in sorted(os.listdir(ANN_DIR)):
            if fn.endswith('.json'):
                a = json.load(open(os.path.join(ANN_DIR, fn)))
                ann_data[a.get('name', fn[:-5])] = a
    
    targets = sys.argv[1:]
    if not targets or '--all' in targets:
        classes = [k for k, v in ida_structs.items() 
                   if isinstance(v, dict) and v.get('vtables')]
        classes.sort()
    elif '--all' not in targets:
        classes = targets
    
    for cls in classes:
        ad = ann_data.get(cls, {})
        analyze_class_vtables(cls, ida_structs, ad)


if __name__ == '__main__':
    main()
