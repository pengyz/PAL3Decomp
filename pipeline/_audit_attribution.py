"""Audit: find functions where raw this+N offsets exceed struct binary_size.
This identifies potential function attribution errors."""
import json, os, re

DECOMP = 'asm/pal3/decomp'
FUNCS = 'data/annotations/functions.json'
STRUCTS = 'data/annotations/structs'

# Load struct sizes
struct_sizes = {}
struct_members = {}
for f in sorted(os.listdir(STRUCTS)):
    if not f.endswith('.json'): continue
    with open(os.path.join(STRUCTS, f), encoding='utf-8') as fh:
        d = json.load(fh)
    struct_sizes[d.get('name','')] = d.get('binary_size', 0)
    struct_members[d.get('name','')] = len(d.get('known_members', {}))

# Load field_overrides (these provide member names for offsets beyond struct size)
field_overrides = {}
fo_path = 'data/annotations/field_overrides.json'
if os.path.exists(fo_path):
    with open(fo_path, encoding='utf-8') as fh:
        fo_data = json.load(fh)
    for fo_cls, fo_info in fo_data.items():
        if fo_cls.startswith('_'): continue
        fields = fo_info.get('fields', {})
        if fields:
            field_overrides[fo_cls] = {
                'max_off': max(int(k) for k in fields.keys()),
                'count': len(fields),
            }

with open(FUNCS, encoding='utf-8') as f:
    funcs = json.load(f)

results = []
for addr, info in sorted(funcs.items()):
    name = info.get('name', '')
    if '::' not in name: continue
    if name.startswith('misattrib_'): continue
    
    cls = name.split('::')[0]
    bs = struct_sizes.get(cls, 0)
    if bs == 0: continue
    
    suffix = addr[2:].lower()
    found = None
    for f in sorted(os.listdir(DECOMP)):
        if suffix in f and f.endswith('.json'):
            found = f
            break
    if not found: continue
    
    with open(os.path.join(DECOMP, found), encoding='utf-8') as fh:
        try:
            d = json.load(fh)
        except:
            continue
    
    code = d.get('decompiled_c', '')
    sz = d.get('size_bytes', 0)
    
    # Find max this+N offset
    max_from_dword = 0
    max_from_float = 0
    max_from_byte = 0
    max_from_this = 0
    
    for m in re.finditer(r'this\s*\+\s*(\d+)', code):
        try:
            off = int(m.group(1))
            if off > max_from_this: max_from_this = off
        except: pass
    
    # DWORD offset: *((_DWORD *)this + N) -> byte offset = N*4
    for m in re.finditer(r'\*\(\(_DWORD \*\)this \+ (\d+)\)', code):
        off = int(m.group(1)) * 4
        if off > max_from_dword: max_from_dword = off
    
    # Float offset
    for m in re.finditer(r'\*\(\(float \*\)this \+ (\d+)\)', code):
        off = int(m.group(1)) * 4
        if off > max_from_float: max_from_float = off
    
    # Byte offset
    for m in re.finditer(r'\(_BYTE \*\)\(this \+ (\d+)\)', code):
        off = int(m.group(1))
        if off > max_from_byte: max_from_byte = off
    
    max_off = max(max_from_dword, max_from_float, max_from_byte, max_from_this)
    
    if max_off > bs:
        # Skip if covered by field_overrides (struct has known field names at these offsets)
        if cls in field_overrides and field_overrides[cls]['max_off'] >= max_off:
            continue
        
        # Find candidate real classes
        candidates = []
        for cname, cbs in sorted(struct_sizes.items()):
            if cbs >= max_off * 0.9 and cbs <= max_off * 1.5:
                candidates.append((cname, cbs))
        
        ratio = max_off / bs if bs > 0 else 0
        results.append((ratio, max_off, bs, name, sz, candidates, cls))

# Sort by ratio descending (most egregious first)
results.sort(key=lambda x: x[0], reverse=True)

print("Functions with this+N exceeding struct size (potential attribution errors)")
print("=" * 90)
print(f"{'Ratio':>6s} {'MaxOff':>7s} {'BSize':>6s} {'Function':55s} {'Size':>5s}  Candidates")
print("-" * 90)
for ratio, max_off, bs, name, sz, candidates, cls in results[:40]:
    cand_str = ", ".join(f"{c}({s})" for c, s in candidates[:3])
    if not cand_str:
        cand_str = "(no match)"
    ratio_str = f"{ratio:.0f}x" if ratio > 10 else f"{ratio:.1f}x"
    print(f"{ratio_str:>6s} {max_off:7d} {bs:6d} {name:55s} {sz:5d}  {cand_str}")

print()
print(f"Total potential attribution errors: {len(results)}")
