#!/usr/bin/env python3
"""
校验 annotations.json 数据合法性。
用法: python tools/check_annotations.py
      或作为 git pre-commit hook 调用

检查项:
  1. JSON 格式合法
  2. functions: 每个必须有 name + signature
  3. globals: 每个必须有 name（type 可选但缺失会警告）
  4. structs: 无重复成员名，offset 递增，base_class 如有则必须存在
  5. 地址格式: 0x00XXXXXX
"""

import json
import sys
import os
import re

ANN_DIR = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'data', 'annotations')

def load_annotations():
    """从拆分目录加载标注数据。"""
    funcs = json.load(open(os.path.join(ANN_DIR, 'functions.json'), encoding='utf-8'))
    globs = json.load(open(os.path.join(ANN_DIR, 'globals.json'), encoding='utf-8'))
    structs = {}
    structs_dir = os.path.join(ANN_DIR, 'structs')
    for fname in os.listdir(structs_dir):
        if fname.endswith('.json'):
            sdata = json.load(open(os.path.join(structs_dir, fname), encoding='utf-8'))
            sname = sdata.pop('name', fname.replace('.json', ''))
            structs[sname] = sdata
    enums = {}
    enums_path = os.path.join(ANN_DIR, 'enums.json')
    if os.path.exists(enums_path):
        enums = json.load(open(enums_path, encoding='utf-8'))
    return {'functions': funcs, 'globals': globs, 'structs': structs, 'enums': enums}

def _estimate_member_size(mtype, structs):
    """Estimate member size for overlap detection."""
    if '*' in mtype:
        return 4
    arr = re.search(r'\[(\d+)\]', mtype)
    if arr:
        base = re.sub(r'\[\d+\].*', '', mtype).strip()
        elem = _estimate_member_size(base, structs)
        total = elem
        for m in re.finditer(r'\[(\d+)\]', mtype):
            total = int(m.group(1)) * elem
        return total
    t = mtype.strip().replace('struct ', '').replace('class ', '')
    if t in ('char', 'unsigned char', 'BYTE', '_BYTE', 'bool'):
        return 1
    if t in ('short', 'unsigned short', 'WORD', '_WORD'):
        return 2
    if t in ('int', 'unsigned int', 'long', 'unsigned long', 'DWORD', '_DWORD',
             'float', 'BOOL', 'HRESULT', 'HWND', 'HANDLE', 'UINT', 'LONG'):
        return 4
    if t in ('double', '__int64', 'LONGLONG'):
        return 8
    if t in ('RECT', 'tagRECT', '_RECTL'):
        return 16
    if t in ('gbVec3D',):
        return 12
    if t in ('gbMatrix',):
        return 64
    if t in structs:
        sz = structs[t].get('binary_size', 0)
        if sz:
            return int(sz)
    return 4


def check():
    errors = []
    warnings = []

    # 1. Load JSON
    try:
        ann = load_annotations()
    except Exception as e:
        errors.append(f"JSON parse error: {e}")
        return errors, warnings

    # 2. Functions
    funcs = ann.get('functions', {})
    # Track (name, normalized_signature) for duplicate detection
    sig_index = {}  # (name, sig_norm) -> first_addr
    for addr, info in funcs.items():
        if not re.match(r'^0x[0-9A-F]{8}$', addr):
            errors.append(f"functions[{addr}]: invalid address format")
        if not info.get('name'):
            errors.append(f"functions[{addr}]: missing name")
        if not info.get('signature'):
            errors.append(f"functions[{addr}]: missing signature (name={info.get('name')})")
        # Check for duplicate (name + normalized signature)
        name = info.get('name', '')
        sig = info.get('signature', '')
        if name and sig:
            # Normalize: strip return type + calling convention + function name,
            # keep just parameter list e.g. "void __thiscall(PalScript *this, int n)" -> "(int n)"
            sig_norm = re.sub(r'^.*?__thiscall\(', '(this, ', sig)
            sig_norm = re.sub(r'^.*?__cdecl\(', '(', sig_norm)
            sig_norm = re.sub(r'^.*?__stdcall\(', '(', sig_norm)
            key = (name, sig_norm)
            if key in sig_index:
                errors.append(
                    f"functions[{addr}]: duplicate function '{name}' with signature "
                    f"'{sig_norm}' (first at {sig_index[key]})")
            else:
                sig_index[key] = addr

    # 2b. Thunk/virtual/attribution consistency checks
    for addr, info in funcs.items():
        name = info.get('name', '')
        sig = info.get('signature', '')

        # Check 1: 'virtual' on free function (Hex-Rays artifact, invalid C++)
        # These need class attribution to make 'virtual' valid. Functions with
        # generic Block types (void*, char*) cannot be attributed. Functions
        # with known class types should be moved to struct annotations.
        if 'virtual' in sig and '::' not in name:
            m = re.search(r'(?:virtual\s+)?(\w[\w:]*)\s*\*+\s*(?:Block|this)', sig)
            if m and m.group(1) not in ('void', 'char', 'int', '_BYTE'):
                errors.append(
                    f"functions[{addr}]: 'virtual' in free function '{name}' "
                    f"(sig: {sig[:60]}) — member of '{m.group(1)}', "
                    f"add {m.group(1)}:: prefix to make 'virtual' valid")
            else:
                warnings.append(
                    f"functions[{addr}]: 'virtual' in free function '{name}' "
                    f"(sig: {sig[:60]}) — generic this type, cannot determine class")

        # Check 2: __thiscall without :: suggests misattributed member function
        if '__thiscall' in sig and '::' not in name:
            # Exclude known-nonmember patterns: _sdtor_, _nearby_, sub_ etc.
            if not name.startswith(('_sdtor', '_nearby', '_sub', '_todo', '_init_', 'sub_', '_old_')):
                first_param = sig.split('(')[1].split(',')[0].strip() if '(' in sig else ''
                # If first param is a real class pointer -> likely misattributed member
                # Downgrade to WARNING — proper attribution requires IDA
                # investigation to determine the correct class.
                warnings.append(
                    f"functions[{addr}]: '__thiscall' without '::' in '{name}' "
                    f"(sig: {sig[:60]}) — likely member function, needs IDA investigation")

    # 2c. Check for entries missing mandatory __ovl_ suffix
    # IDA requires unique function names per IDB entry. If two functions share a base name
    # (after __ovl_ stripping), the one(s) without __ovl_ must add it for IDB uniqueness.
    # Entries WITH __ovl_ sharing the same base are validated by section 2c (different sigs required).
    # Build base -> [(addr, name, has_ovl)]
    base_groups = {}
    OVL_SUFFIX = re.compile(r'__ovl_[0-9a-fA-F]+$')
    for addr, info in funcs.items():
        name = info.get('name', '')
        if not name or info.get('type') == 'skip':
            continue
        base = OVL_SUFFIX.sub('', name)
        has_ovl = bool(OVL_SUFFIX.search(name))
        base_groups.setdefault(base, []).append((addr, name, has_ovl))
    for base, members in base_groups.items():
        if len(members) < 2:
            continue
        no_ovl = [m for m in members if not m[2]]
        for addr, name, _ in no_ovl:
            errors.append(
                f"functions[{addr}]: '{name}' needs __ovl_ suffix — "
                f"base name '{base}' collides with {len(members)} entries")

    # 2c. Check __ovl_ overload validity: same base name must have different signatures
    for base, members in base_groups.items():
        if len(members) < 2:
            continue
        has_ovl = [m for m in members if m[2]]
        if len(has_ovl) < 2:
            continue
        # All entries with __ovl_ and same base must have different signatures
        seen_sigs = {}
        for addr, name, _ in has_ovl:
            sig = funcs[addr].get('signature', '')
            sig_norm = re.sub(r'^.*?__thiscall\(', '(this, ', sig)
            sig_norm = re.sub(r'^.*?__cdecl\(', '(', sig_norm)
            sig_norm = re.sub(r'^.*?__stdcall\(', '(', sig_norm)
            if sig_norm in seen_sigs:
                errors.append(
                    f"functions[{addr}]: '{name}' shares signature '{sig_norm}' with "
                    f"'{seen_sigs[sig_norm]}' — forms duplicate, not overload, of '{base}'")
            else:
                seen_sigs[sig_norm] = f"{name} @ {addr}"

    # 2d. Check for collisions AFTER __ovl_ stripping (simulates codegen behavior)
    stripped_sigs = {}  # (stripped_name, sig_norm) -> addr
    for addr, info in funcs.items():
        name = info.get('name', '')
        sig = info.get('signature', '')
        if not name or not sig:
            continue
        stripped = re.sub(r'__ovl_[0-9a-fA-F]+$', '', name)
        sig_norm = re.sub(r'^.*?__thiscall\(', '(this, ', sig)
        sig_norm = re.sub(r'^.*?__cdecl\(', '(', sig_norm)
        sig_norm = re.sub(r'^.*?__stdcall\(', '(', sig_norm)
        key = (stripped, sig_norm)
        if key in stripped_sigs:
            errors.append(
                f"functions[{addr}]: '{name}' collides with '{stripped_sigs[key]}' "
                f"after __ovl_ stripping → same signature '{sig_norm}'")
        else:
            stripped_sigs[key] = f"{name} @ {addr}"

    # 3. Globals
    globs = ann.get('globals', {})
    no_type = 0
    for addr, info in globs.items():
        if info.get('type') == 'skip':
            continue  # known-unnameable entries are valid
        if not info.get('name'):
            errors.append(f"globals[{addr}]: missing name")
        if not info.get('type'):
            no_type += 1
    if no_type > 0:
        warnings.append(f"globals: {no_type}/{len(globs)} missing type")

    # 3b. Global overlap check: detect globals that fall within another named global's range
    # Build address ranges for non-skip globals that have struct types with binary_size
    all_structs = ann.get('structs', {})
    global_ranges = []  # [(addr_start, addr_end, name, type)]
    for addr_str, info in globs.items():
        if info.get('type') == 'skip':
            continue
        gtype = info.get('type', '')
        gname = info.get('name', '')
        if not gtype or not gname:
            continue
        # Check if this global's type has a binary_size
        gstruct = all_structs.get(gtype, {})
        gsize = gstruct.get('binary_size', 0) or gstruct.get('pdb_size', 0)
        if not gsize:
            continue
        try:
            gaddr = int(addr_str, 16)
        except ValueError:
            continue
        global_ranges.append((gaddr, gaddr + int(gsize), gname, gtype))

    for addr_str, info in globs.items():
        if info.get('type') == 'skip':
            continue
        gtype = info.get('type', '')
        gname = info.get('name', '')
        if not gtype or not gname:
            continue
        try:
            gaddr = int(addr_str, 16)
        except ValueError:
            continue
        # Check if this address falls within any other global's range
        expected_overlaps = set(info.get('overlaps_with', []) or [])
        for rstart, rend, rname, rtype in global_ranges:
            if rname == gname:
                continue  # skip self
            if rstart <= gaddr < rend:
                if rname in expected_overlaps:
                    continue  # explicitly marked as intended overlap
                gstruct = all_structs.get(gtype, {})
                gsize = gstruct.get('binary_size', 0) or gstruct.get('pdb_size', 0)
                if gsize:
                    gend = gaddr + int(gsize)
                    containment = "(entirely within)" if gend <= rend else "(extends beyond)"
                    errors.append(
                        f"globals[{addr_str}]: '{gname}' ({gtype}, {gsize}b) at +{gaddr - rstart} "
                        f"inside '{rname}' ({rtype}) range [0x{rstart:X}-0x{rend:X}] "
                        f"{containment} — add 'overlaps_with' to globals[{addr_str}] if intentional")

    # 3c. Annotation globals that are neither in export nor in struct_instance range
    # A global in globals.json with a type must be either:
    # 1. In ida_structs.json _globals (properly exported), or
    # 2. Within a struct_instance range (phantom, handled by overlap), or
    # 3. Marked as "type": "skip" (intentionally excluded)
    # If none of these, codegen cannot handle it — annotation is incomplete.
    _is_path3 = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'asm', 'pal3', 'ida_structs.json')
    if os.path.exists(_is_path3):
        _is_data3 = json.load(open(_is_path3, encoding='utf-8'))
        _exp_glob3 = _is_data3.get('_globals', {})
        _exp_names3 = {info.get('name') for info in _exp_glob3.values() if info.get('name')}
        _exp_ranges3 = []
        for _addr_s, _ginfo in _exp_glob3.items():
            _gt = _ginfo.get('type', '')
            _gn = _ginfo.get('name', '')
            if not _gt or not _gn:
                continue
            _st = _is_data3.get(_gt, {})
            _sz = _st.get('size', 0)
            if not _sz:
                continue
            try:
                _ga = int(_addr_s, 16)
            except ValueError:
                continue
            _exp_ranges3.append((_ga, _ga + _sz, _gn, _gt))
        for _addr_s, _ginfo in globs.items():
            if _ginfo.get('type') == 'skip':
                continue
            _gn = _ginfo.get('name', '')
            _gt = _ginfo.get('type', '')
            if not _gn or not _gt:
                continue
            if _gn in _exp_names3:
                continue  # in export — OK
            try:
                _ga = int(_addr_s, 16)
            except ValueError:
                continue
            _in_range = any(_rs < _ga < _re for _rs, _re, _, _ in _exp_ranges3)
            if not _in_range:
                errors.append(
                    f"globals[{_addr_s}]: '{_gn}' ({_gt}) is not in ida_structs.json _globals "
                    f"and not in any struct_instance range — codegen cannot handle it. "
                    f"Either fix the annotation so IDB includes it, or mark as 'skip' if phantom.")

    # 4. Structs
    structs = ann.get('structs', {})
    all_struct_names = set(structs.keys())

    for sname, sinfo in structs.items():
        members = sinfo.get('known_members', {})
        is_union = sinfo.get('is_union', False)

        # Check duplicate member names
        names_seen = {}
        for off, m in members.items():
            mname = m.get('name', '')
            if mname in names_seen:
                errors.append(f"structs[{sname}]: duplicate member '{mname}' at offsets {names_seen[mname]} and {off}")
            names_seen[mname] = off

        # Union-specific validation
        if is_union:
            binary_sz = sinfo.get('binary_size', 0)
            for off, m in members.items():
                real_off = int(off.split('_')[0], 0)
                if real_off != 0:
                    errors.append(f"union[{sname}]: member '{m.get('name')}' at +{real_off} (must be 0)")
                # Each union member size must fit within binary_size
                msz = _estimate_member_size(m.get('type', 'int'), structs)
                if msz > binary_sz:
                    errors.append(f"union[{sname}]: member '{m.get('name')}' size {msz} > binary_size {binary_sz}")
            # Unions cannot have base_class
            base = sinfo.get('base_class')
            if base:
                errors.append(f"union[{sname}]: unions cannot have base_class")
        else:
            # Check member overlap (using known struct sizes) - structs only
            sorted_m = sorted(members.items(), key=lambda x: int(x[0], 0))
            max_extent = 0
            for i in range(len(sorted_m) - 1):
                off1 = int(sorted_m[i][0], 0)
                m1 = sorted_m[i][1]
                off2 = int(sorted_m[i + 1][0], 0)
                size1 = _estimate_member_size(m1.get('type', 'int'), structs)
                end1 = off1 + size1
                if end1 > off2:
                    # CCBStage.m_Task[256] is an intentional union overlay
                    if sname == 'CCBStage' and m1.get('name') == 'm_Task':
                        continue
                    # SceneMgr has multiple memory views (flexible layout);
                    # m_pRoleSystemArrayEnd at +50814 is part of a different view
                    # than m_partyInitData at +50816 — intentional overlap.
                    if sname == 'SceneMgr' and m1.get('name') in ('m_pRoleSystemArrayEnd',):
                        continue
                    # Skip if either member's source explicitly mentions overlap
                    if 'overlap' in (m1.get('source', '') + sorted_m[i+1][1].get('source', '')).lower():
                        continue
                    msg = (f"structs[{sname}]: member overlap: " 
                           f"{m1.get('name')}({m1.get('type')}, size={size1})@{off1} " 
                           f"ends@{end1} > next {sorted_m[i+1][1].get('name')}@{off2}")
                    errors.append(msg)
                if end1 > max_extent:
                    max_extent = end1
            # Check member alignment: pointers must be 4-aligned, shorts 2-aligned
            for off_str, m in members.items():
                off = int(off_str, 0)
                mtype = m.get('type', '')
                name = m.get('name', '')
                if off == 0:
                    continue
                if name.startswith('_pad_') or name.startswith('_gap_'):
                    continue
                # Skip alignment for members in documented flexible/overlap regions
                if any(kw in m.get('source', '').lower() for kw in ('overlap', 'confirmed', 'flexible')):
                    continue
                if '*' in mtype and off % 4 != 0:
                    errors.append(
                        f"structs[{sname}]: ALIGN: +{off} {name} = {mtype} (pointer not 4-aligned)")
                elif any(mtype.startswith(t) for t in ['short', 'unsigned short', 'WORD', '_WORD']):
                    if off % 2 != 0:
                        errors.append(
                            f"structs[{sname}]: ALIGN: +{off} {name} = {mtype} (short not 2-aligned)")
            # Check last member extent vs binary_size
            if sorted_m:
                last_off = int(sorted_m[-1][0])
                last_m = sorted_m[-1][1]
                last_sz = _estimate_member_size(last_m.get('type', 'int'), structs)
                last_end = last_off + last_sz
                if last_end > max_extent:
                    max_extent = last_end
                binary_sz = sinfo.get('binary_size', 0)
                if binary_sz and max_extent > binary_sz:
                    errors.append(
                        f"structs[{sname}]: members extend to +{max_extent} but binary_size={binary_sz} "
                        f"(gap={binary_sz - max_extent})")

        # Check base_class exists (structs only - unions checked above)
        if not is_union:
            base = sinfo.get('base_class')
            if base:
                bases = [base] if isinstance(base, str) else base
                for b in bases:
                    if b not in all_struct_names:
                        warnings.append(f"structs[{sname}]: base_class '{b}' not in structs (may be in PDB)")

        # Check struct has size
        size = max(sinfo.get('binary_size', 0), sinfo.get('pdb_size', 0))
        if size == 0 and members:
            warnings.append(f"structs[{sname}]: no size (has {len(members)} members but size=0)")

        # Check nested_types format
        for nt_name, nt_info in sinfo.get("nested_types", {}).items():
            kind = nt_info.get("kind", "")
            if kind not in ("struct", "class", "enum"):
                errors.append(
                    f"structs[{sname}].nested_types[{nt_name}]: kind must be "
                    f"struct/class/enum (got '{kind}')"
                )
            if kind in ("struct", "class") and not nt_info.get("binary_size"):
                errors.append(
                    f"structs[{sname}].nested_types[{nt_name}]: kind={kind} "
                    f"requires binary_size"
                )
            if kind == "enum" and not nt_info.get("values"):
                errors.append(
                    f"structs[{sname}].nested_types[{nt_name}]: kind=enum "
                    f"requires values"
                )

    # 5. Check skip_functions thunks vs struct methods / functions conflicts
    # When a function is in skip as reason=thunk AND in struct methods,
    # apply_annotations step 1 sets the mangled name, then the skip override
    # (line 1038) overwrites it with the raw skip name, breaking the mangler.
    skip_path = os.path.join(ANN_DIR, 'skip_functions.json')
    if os.path.exists(skip_path):
        skip_data = json.load(open(skip_path, encoding='utf-8'))
        # Build set of all method addresses from structs + functions
        method_addrs = set()
        for sname, sinfo in structs.items():
            for addr in sinfo.get('methods', {}):
                method_addrs.add(addr)
        for addr in funcs:
            method_addrs.add(addr)
        # A function must not be in both skip_functions AND struct methods/functions.
        # skip means "don't export"; struct methods means "is a real function".
        # Both can't be true — remove from skip_functions.json.
        for addr in skip_data:
            if addr in method_addrs:
                skip_name = skip_data[addr].get('name', '?')
                errors.append(
                    f"skip_functions[{addr}] '{skip_name}' also exists in"
                    f" struct methods or functions.json — remove from skip_functions.json (one source only)"
                        )

    # 6. Exported globals overlap check (ida_structs.json)
    # ida_structs.json is the actual data source for codegen.
    # Overlapping globals in export = codegen produces wrong declarations.
    _is_path = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'asm', 'pal3', 'ida_structs.json')
    if os.path.exists(_is_path):
        _is_data = json.load(open(_is_path, encoding='utf-8'))
        _exp_globs = _is_data.get('_globals', {})
        _exp_ranges = []
        for _addr_s, _ginfo in _exp_globs.items():
            _gt = _ginfo.get('type', '')
            _gn = _ginfo.get('name', '')
            if not _gt or not _gn:
                continue
            _st = _is_data.get(_gt, {})
            _sz = _st.get('size', 0)
            if not _sz:
                continue
            try:
                _ga = int(_addr_s, 16)
            except ValueError:
                continue
            _exp_ranges.append((_ga, _ga + _sz, _gn, _gt))
        for _addr_s, _ginfo in _exp_globs.items():
            _gt = _ginfo.get('type', '')
            _gn = _ginfo.get('name', '')
            if not _gt or not _gn:
                continue
            try:
                _ga = int(_addr_s, 16)
            except ValueError:
                continue
            for _rs, _re, _rn, _rt in _exp_ranges:
                if _rn == _gn:
                    continue
                if _rs < _ga < _re:
                    _has_own = any(_b == _ga for _b, _e, _, _ in _exp_ranges)
                    if not _has_own:
                        warnings.append(
                            f"export[0x{_ga:X}]: '{_gn}' ({_gt}) at +0x{_ga - _rs:X} inside "
                            f"'{_rn}' ({_rt}) [0x{_rs:X}-0x{_re:X}] — phantom global, "
                            f"skipped by generate_globals() (not a real global)")

    return errors, warnings


if __name__ == '__main__':
    errors, warnings = check()

    for w in warnings:
        print(f"WARN: {w}")
    for e in errors:
        print(f"ERROR: {e}")

    if errors:
        print(f"\n{len(errors)} errors, {len(warnings)} warnings — FAIL")
        sys.exit(1)
    else:
        print(f"\n0 errors, {len(warnings)} warnings — PASS")
        sys.exit(0)
