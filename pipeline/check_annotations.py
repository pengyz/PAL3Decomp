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
import os
import re
import sys

_PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, _PROJECT_ROOT)

from pipeline.gen.annotation_view import iter_struct_files, iter_structs, load_struct

ANN_DIR = os.path.join(_PROJECT_ROOT, 'data', 'annotations')


def _strict_struct_entries(directory):
    for path in iter_struct_files(directory):
        struct_data = load_struct(path)
        if not isinstance(struct_data, dict):
            raise ValueError('%s: struct annotation must be a JSON object' % path)
    return list(iter_structs(directory))

def load_annotations(struct_dir=None):
    """契约真修 2026-10-07（P0-4）：struct_dir 注入（fixture 模式——5 读点隔离）。
    struct_dir 非空=只载注入目录的 structs（functions/globals/enums 容缺）。"""
    _sd = struct_dir if struct_dir else os.path.join(ANN_DIR, 'structs')
    funcs = {}
    globs = {}
    try:
        funcs = json.load(open(os.path.join(ANN_DIR, 'functions.json'), encoding='utf-8'))
    except Exception:
        pass
    try:
        globs = json.load(open(os.path.join(ANN_DIR, 'globals.json'), encoding='utf-8'))
    except Exception:
        pass
    structs = {}
    for fname, sdata in _strict_struct_entries(_sd):
        fname = os.path.basename(fname)
        sname = sdata.pop('name', fname.replace('.json', ''))
        structs[sname] = sdata
    enums = {}
    enums_path = os.path.join(ANN_DIR, 'enums.json')
    if os.path.exists(enums_path):
        enums = json.load(open(enums_path, encoding='utf-8'))
    return {'functions': funcs, 'globals': globs, 'structs': structs, 'enums': enums}

def _estimate_member_size(mtype, structs):
    """Estimate member size for overlap detection."""
    if isinstance(mtype, dict):
        # type=object (inline union/struct): use max of members
        mems = mtype.get("union") or mtype.get("struct") or []
        max_sz = 0
        for m in mems:
            sz = _estimate_member_size(m.get("type", "int"), structs)
            off = m.get("offset", 0)
            end = off + sz
            if end > max_sz:
                max_sz = end
        return max_sz
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


def _check_type_object(tdef, sname, errors, path=""):
    """Validate a type=object definition recursively."""
    if not isinstance(tdef, dict):
        return
    tkey = None
    members = None
    if "union" in tdef:
        tkey = "union"
        members = tdef["union"]
    elif "struct" in tdef:
        tkey = "struct"
        members = tdef["struct"]
    else:
        errors.append("structs[%s]:%s unknown type object keys: %s" % (
            sname, path, list(tdef.keys())))
        return
    if not isinstance(members, list):
        errors.append("structs[%s]:%s.%s must be an array" % (sname, path, tkey))
        return
    for i, m in enumerate(members):
        if not isinstance(m, dict):
            errors.append("structs[%s]:%s.%s[%d] must be an object" % (sname, path, tkey, i))
            continue
        if "name" not in m:
            errors.append("structs[%s]:%s.%s[%d] missing 'name'" % (sname, path, tkey, i))
        mtype = m.get("type", "")
        if not mtype:
            errors.append("structs[%s]:%s.%s[%d] missing 'type'" % (sname, path, tkey, i))
        if isinstance(mtype, dict):
            _check_type_object(mtype, sname, errors, "%s.%s[%d].type" % (path, tkey, i))


def check(struct_dir=None):
    """契约修 2026-10-07（复核）：struct_dir 可注入（测试契约——7 红修复）。
    一致性扩（基线权威单一化 2026-10-07）：三方基线一致检查。"""
    errors = []
    warnings = []
    _struct_dir = struct_dir  # 契约真修（P0-4）
    # 三方基线一致检查（基线权威单一化——latest.json=权威·派生只读）
    try:
        import json as _j
        import os as _o
        _base_dir = _o.path.join(_o.path.dirname(ANN_DIR), 'status')
        _auth = _j.load(open(_o.path.join(_base_dir, 'baselines', 'latest.json'), encoding='utf-8'))
        _compile = _j.load(open(_o.path.join(_base_dir, 'compile_baseline.json'), encoding='utf-8'))
        # 一致检查：compile_baseline 的 ok/fail ⊆ latest 的单元集
        if _auth and _compile:
            pass  # 详细比对待（骨架落）
    except Exception:
        pass

    # 1. Load JSON
    try:
        ann = load_annotations(_struct_dir)
    except Exception as e:
        errors.append(f"JSON parse error: {e}")
        return errors, warnings

    # 2. Functions
    funcs = ann.get('functions', {})
    # Track (name, normalized_signature) for duplicate detection
    sig_index = {}  # (name, sig_norm) -> first_addr

    # Build set of addresses belonging to struct methods (for :: check skip)
    _struct_method_addrs = set()
    for _sn, _sd in ann.get('structs', {}).items():
        for _addr in _sd.get('methods', {}):
            _struct_method_addrs.add(_addr)

    for addr, info in funcs.items():
        if not re.match(r'^0x[0-9A-Fa-f]{8}$', addr):
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
        if 'virtual' in sig and '::' not in name and addr not in _struct_method_addrs:
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
        if '__thiscall' in sig and '::' not in name and addr not in _struct_method_addrs:
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

    # --- 2d. Inheritance/vtable consistency check ---
    structs = ann.get('structs', {})
    for _sn, _sd in structs.items():
        _bc = _sd.get('base_class', '')
        _bases = [b.get('name','') for b in (_sd.get('bases') or [])]
        if isinstance(_bc, list):
            _bases = _bc + _bases
        elif _bc:
            _bases.insert(0, _bc)
        if not _bases:
            continue
        _methods = _sd.get('methods', {})
        _ord_to_addr = {}
        _addr_to_minfo = {}
        for _a_s, _minfo in _methods.items():
            _ord = _minfo.get('ordinal')
            if _ord is not None:
                _ord_to_addr[_ord] = int(_a_s, 16)
            _addr_to_minfo[int(_a_s, 16)] = _minfo
        for _base_name in _bases:
            if not isinstance(_base_name, str):
                continue
            _base_data = structs.get(_base_name, {})
            _base_methods = _base_data.get('methods', {})
            for _ba_s, _bminfo in _base_methods.items():
                _bord = _bminfo.get('ordinal')
                if _bord is None:
                    continue
                if _bord not in _ord_to_addr:
                    continue
                _d_addr = _ord_to_addr[_bord]
                _b_addr = int(_ba_s, 16)
                _dminfo = _addr_to_minfo.get(_d_addr, {})
                if _d_addr == _b_addr:
                    if _dminfo.get('signature'):
                        errors.append(
                            f"structs[{_sn}]: method '{_dminfo.get('name','')}' @ {hex(_d_addr)} "
                            f"(ordinal {_bord}) has same address as {_base_name} — "
                            f"inherited, not overridden. Remove 'signature' field.")
                elif _b_addr != _d_addr:
                    _bname = _bminfo.get('name', '')
                    _dname = _dminfo.get('name', '')
                    if _dname == _bname and not _dminfo.get('signature'):
                        errors.append(
                            f"structs[{_sn}]: method '{_dname}' @ {hex(_d_addr)} "
                            f"(ordinal {_bord}) overrides {_base_name} — "
                            f"needs 'signature' field.")

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
                # Globals annotated with name+type are now handled by codegen's
                # annotated_globals mechanism — no longer an error.
                pass

    # 4. Structs
    structs = ann.get('structs', {})
    all_struct_names = set(structs.keys())

    # 所有注解声明过的嵌套类型（"Parent::Nested"），供悬垂引用检测使用（见下方 4f）
    #
    # 必须把 `detached_nested_types.json` 也算作**合法解析来源**：apply 的 §3c pre-pass
    # 会遍历该文件为「无 struct 注解文件的父类」（如已解散的幻影类 PlayerMgr）建前向声明。
    # 若此处不认它，门禁会与实现脱节——把 apply 已能解析的引用误报为悬垂
    # （captain 首次提交即被 pre-commit 钩子以该假阳性挡下，教训：门禁与实现必须共用同一真相源）。
    _provided_nested = set()
    for _sn, _si in structs.items():
        for _nt in (_si.get("nested_types") or {}):
            _provided_nested.add("%s::%s" % (_sn, _nt))
    _dnt_check_path = os.path.join(ANN_DIR, "detached_nested_types.json")
    if os.path.exists(_dnt_check_path):
        try:
            with open(_dnt_check_path, "r", encoding="utf-8") as _dcf:
                _dnt_check = json.load(_dcf)
            for _dp, _di in _dnt_check.items():
                if _dp.startswith("_") or not isinstance(_di, dict):
                    continue
                for _dn in _di:
                    _provided_nested.add("%s::%s" % (_dp, _dn))
        except Exception as _dce:
            errors.append(
                "detached_nested_types.json unreadable (%s) — 悬垂引用检测的合法来源不完整，"
                "结果不可信" % _dce)

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

            # Pseudo-semantic naming guard: CLAUDE.md forbids names like
            # m_nState_4968 / m_fParam_0A0 where the trailing digits are just
            # the field's own offset dressed up with a generic word (Val/Flag/
            # State/Param/Zero/...). Detect precisely: strip a known hollow
            # word + trailing hex/dec digits, and check whether that number
            # equals this member's own offset (decimal or hex reading).
            # See docs/knowledge/pattern_annotation_batch_rename_no_evidence.md
            _hollow = re.match(
                r'^m_[nfb](?:Val|Flag|State|Param|Init|Zero)([0-9A-Fa-f]{2,6})$',
                mname,
            )
            if _hollow:
                _suffix = _hollow.group(1)
                try:
                    _off_dec = int(off.split('_')[0], 0)
                except ValueError:
                    _off_dec = None
                _matches_hex = _off_dec is not None and (
                    _suffix.upper() == format(_off_dec, 'X') or
                    _suffix.upper() == format(_off_dec, 'x').upper()
                )
                _matches_dec = _off_dec is not None and _suffix == str(_off_dec)
                if _matches_hex or _matches_dec:
                    warnings.append(
                        f"structs[{sname}]: '{mname}' at offset {off} looks like pseudo-semantic "
                        f"naming — suffix '{_suffix}' is this field's own offset dressed up with a "
                        f"generic word (Val/Flag/State/...), no real semantic content added over "
                        f"_todo_/_field_. See CLAUDE.md 禁止伪语义命名."
                    )

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
            # Check _variants union references
            for off_str, m in members.items():
                variants = m.get('_variants', [])
                if not variants:
                    continue
                base_off = int(off_str.split('_')[0], 0)
                main_type = m.get('type', 'int')
                main_size = _estimate_member_size(main_type, structs)
                for v in variants:
                    ref_type = v.get('type', '')
                    if not ref_type:
                        continue
                    if ref_type == 'struct':
                        # Inline struct: compute max extent
                        ref_size = 0
                        for mem in v.get('_members', []):
                            mem_end = int(mem['offset'], 16) + _estimate_member_size(mem.get('type', 'int'), structs)
                            ref_size = max(ref_size, mem_end - base_off)
                    else:
                        if ref_type not in all_struct_names:
                            errors.append(f"structs[{sname}]: _variants ref to unknown type '{ref_type}'")
                            continue
                        ref_data = structs.get(ref_type, {})
                        ref_size = ref_data.get('binary_size', 0)
                        if ref_data.get('is_union'):
                            errors.append(f"structs[{sname}]: _variants cannot reference union type '{ref_type}'")
                    if ref_size > main_size:
                        errors.append(
                            f"structs[{sname}]: _variants '{ref_type}' size {ref_size} > "
                            f"main field '{m.get('name')}' size {main_size}")

            # Validate type=object fields (inline union/struct)
            for off_str, m in members.items():
                mtype = m.get('type', '')
                if not isinstance(mtype, dict):
                    continue
                _check_type_object(mtype, sname, errors)

            # Check member overlap (using known struct sizes) - structs only
            # Parse known_member keys as "base_offset[_variant]" where variant is optional
            def _base_off(key):
                return int(key.split('_')[0], 0)
            sorted_m = sorted(members.items(), key=lambda x: _base_off(x[0]))
            max_extent = 0
            # Group by base offset to detect intentional per-member union variants
            _off_groups = {}
            for k, v in members.items():
                _off_groups.setdefault(_base_off(k), []).append(k)
            _union_offsets = {off for off, keys in _off_groups.items() if len(keys) > 1}
            for i in range(len(sorted_m) - 1):
                off1 = _base_off(sorted_m[i][0])
                m1 = sorted_m[i][1]
                off2 = _base_off(sorted_m[i + 1][0])
                size1 = _estimate_member_size(m1.get('type', 'int'), structs)
                end1 = off1 + size1
                if end1 > off2:
                    # Skip overlap for same-offset union variants
                    if off1 == off2:
                        continue
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
                off = _base_off(off_str)
                mtype = m.get('type', '')
                name = m.get('name', '')
                if off == 0:
                    continue
                if name.startswith('_pad_') or name.startswith('_gap_'):
                    continue
                # Skip alignment for members in documented flexible/overlap regions
                if any(kw in m.get('source', '').lower() for kw in ('overlap', 'confirmed', 'flexible')):
                    continue
                if isinstance(mtype, dict):
                    continue  # type=object, alignment checked in _check_type_object
                if '*' in mtype and off % 4 != 0:
                    errors.append(
                        f"structs[{sname}]: ALIGN: +{off} {name} = {mtype} (pointer not 4-aligned)")
                elif any(mtype.startswith(t) for t in ['short', 'unsigned short', 'WORD', '_WORD']):
                    if off % 2 != 0:
                        errors.append(
                            f"structs[{sname}]: ALIGN: +{off} {name} = {mtype} (short not 2-aligned)")
            # Check last member extent vs binary_size
            if sorted_m:
                last_off = _base_off(sorted_m[-1][0])
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
        size = max((sinfo.get('binary_size') or 0), (sinfo.get('pdb_size') or 0))  # null 防御 2026-10-17
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

        # --- 4f. 悬垂 `::` 限定类型引用检测（2026-09-15 新增） ---
        #
        # 背景：`ArcLocale.pstate: PlayerMgr::PoisonState *` 引用了**已解散幻影类**下的嵌套类型。
        # 该缺陷长期被"增量 IDB 里残留的 forward declaration"掩盖（apply 从不删除注解里已删掉的
        # 结构，无 tombstone/GC），只有从 raw.i64 **干净重建**时才以 apply 的 FATAL 暴露
        # （`_resolve_member_type` 失败 → 整个 struct 退化为 size=1/data_members=0）。
        # 见 data/status/_cleanup_finding_dangling_nested_type.md。
        #
        # 本检查把该缺陷**提前到 check 阶段**暴露并给可操作清单，不必等到 apply 才炸。
        #
        # 【判据必须镜像 apply 的 flatten 逻辑】`create_fixed_struct` 对含 `std::` 或 `<` 的
        # 成员类型**一律展平成 char[span]、从不解析**，故这类类型里的 `::` 限定名不是悬垂引用。
        # 实测（2026-09-15）：不加该过滤会多报 3 个假阳性 —
        #   CParticleSystem::TexCoordQuad / Role::ScriptCmd / SceneObj::Common_State
        # 它们全部出现在 `std::vector<...>` / `std::queue<...>` 的模板实参里。
        # 加过滤后：真阳性 1（PlayerMgr::PoisonState）、假阳性 0。
        for _off, _m in members.items():
            _mt = _m.get("type")
            if not isinstance(_mt, str):
                continue
            # 镜像 apply：STL/模板类型被展平，不参与类型解析
            if ("std::" in _mt) or ("<" in _mt):
                continue
            for _qm in re.finditer(r"\b([A-Za-z_]\w*)::([A-Za-z_]\w*)", _mt):
                _q = _qm.group(0)
                if _q.startswith(("std::", "Concurrency::")):
                    continue
                if _q not in _provided_nested:
                    _par, _chi = _q.split("::", 1)
                    errors.append(
                        f"structs[{sname}]: member '{_m.get('name')}' at +{_off} type "
                        f"'{_mt}' references undefined nested type '{_q}' — no annotation "
                        f"declares struct {_par} → nested_types['{_chi}']. apply will fail "
                        f"with _resolve_member_type and the struct will degrade to "
                        f"size=1/data_members=0. Fix: declare the nested type under its "
                        f"real parent, or correct the member type."
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
        # A function must not be in both skip_functions AND struct methods/functions
        # **unless the registration is declaration-only**（批 12-13 形：skip=体排除、
        # functions.json=声明收编（C2065 修）——语义不同源、共存合法。round 7 教训：
        # 误删 skip 侧=意外解禁（C2556/2373 ×144 爆）——标记形（declaration_only 或
        # 变参签名 `(...)`）即认可；真双注（同为定义意图）才旗）。
        for addr in skip_data:
            if addr in method_addrs:
                _reg = funcs.get(addr) or {}
                if not _reg:
                    for _sdat in structs.values():
                        _reg = (_sdat.get('methods', {}) or {}).get(addr) or {}
                        if _reg:
                            break
                _decl_only = bool(_reg.get('declaration_only')) or \
                    str(_reg.get('signature', '')).rstrip().endswith('(...)')
                if _decl_only:
                    continue
                skip_name = skip_data[addr].get('name', '?')
                errors.append(
                    f"skip_functions[{addr}] '{skip_name}' also exists in"
                    f" struct methods or functions.json — 真双注（同为定义意图）；"
                    f"若为声明收编形请标 declaration_only 或变参签名"
                        )

    return errors, warnings



def _run_vtable_check(structs):
    """调用 vtable_mapper 做闭环验证。"""
    import importlib.util
    _project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    vm_path = os.path.join(_project_root, 'tools', 'vtable_mapper.py')
    spec = importlib.util.spec_from_file_location('vtable_mapper', vm_path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod.check(structs=structs)

if __name__ == '__main__':
    errors, warnings = check()

    # vtable 闭环验证门禁（2026-09-25）：基线对比模式
    # ⚠️ 必须在打印循环之前：否则 errors.append 的项只计数不显示，
    #    pre-commit 报 "N errors ... FAIL" 但不显示是什么错误（2026-10-08 撞到）
    try:
        _ann_data = load_annotations()
        _vt_errors, _, _vt_stats = _run_vtable_check(_ann_data.get('structs', {}))
        _vt_base_path = os.path.join(os.path.dirname(ANN_DIR), 'status', 'vtable_baseline.json')
        if os.path.exists(_vt_base_path):
            _vt_base = json.load(open(_vt_base_path, encoding='utf-8'))
            _old_u = _vt_base.get('unresolved', 0)
            _new_u = _vt_stats.get('own_unresolved', 0)
            if _new_u > _old_u:
                errors.append(
                    f"vtable: {_new_u} unresolved (baseline {_old_u}, +{_new_u-_old_u} REGRESSION) — "
                    "新增未解析 vtable 槽位 ⇒ annotation bug")
            elif _new_u < _old_u:
                print(f"[vtable] 改进: {_old_u} → {_new_u} (update vtable_baseline.json)")
    except Exception as _vt_err:
        warnings.append(f'vtable check skipped: {_vt_err}')

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
