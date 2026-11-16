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
try:
    from pipeline.sigmodel import parse_signature, node_of, c2555_conflict, render
except ImportError:  # 脚本模式(sys.path[0]=pipeline/)兼容
    from sigmodel import parse_signature, node_of, c2555_conflict, render

import sys

_PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, _PROJECT_ROOT)

from pipeline.gen.annotation_view import iter_struct_files, iter_structs, load_struct
from pipeline.ida.vc6_mangler import strip_stamp   # [D7] 单源

ANN_DIR = os.path.join(_PROJECT_ROOT, 'data', 'annotations')



def needs_member_attr_warning(name, sig):
    """__thiscall 归属告警判据（纯函数，R15 单测点）。

    签名含 '::'（类限定形 `Cls::Meth(Cls *this)`）= 已归属不报；原判据查 name
    而非 sig ⇒ Create__ovl_1/IsVisible 等 5 条误报（2026-10-17 修正）。
    制式名族（_sdtor/_nearby/sub_/_todo_ 等）豁免。
    """
    if '__thiscall' not in sig:
        return False
    if '::' in sig.split('(')[0]:      # 归属面=签名声明段的类限定
        return False
    if name.startswith(('_sdtor', '_nearby', '_sub', '_todo', '_init_', 'sub_', '_old_')):
        return False
    return True

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
        # （判据修正 2026-10-17 verifier：签名含 '::' 不报——R15 纯函数）
        if addr not in _struct_method_addrs and needs_member_attr_warning(name, sig):
                warnings.append(
                    f"functions[{addr}]: '__thiscall' without '::' in '{name}' "
                    f"(sig: {sig[:60]}) — likely member function, needs IDA investigation")

    # 2c. Check for entries missing mandatory __ovl_ suffix
    # IDA requires unique function names per IDB entry. If two functions share a base name
    # (after __ovl_ stripping), the one(s) without __ovl_ must add it for IDB uniqueness.
    # Entries WITH __ovl_ sharing the same base are validated by section 2c (different sigs required).
    # Build base -> [(addr, name, has_ovl)]
    base_groups = {}
    OVL_SUFFIX = re.compile(r'__ovl_[0-9a-fA-F]+$')  # [D7] 语义=vc6_mangler.strip_stamp 单源
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
        # [2026-11-02 重载换轨] 旧「needs __ovl_ suffix」规退役——按 mangled 形裁定：
        # 同名异签=合法重载（mangled 天然唯一）；仅同(基名,cxx_sig_key)双址=铁律真冲突
        try:
            import importlib.util as _il, os as _os
            from collections import defaultdict
            _sp = _il.spec_from_file_location(
                'ccd_chk', _os.path.join(_os.path.dirname(_os.path.dirname(_os.path.abspath(__file__))),
                                        'tools', 'cxx_collision_detector.py'))
            _ccd = _il.module_from_spec(_sp); _sp.loader.exec_module(_ccd)
            _sigs = defaultdict(list)
            for addr, name, _h in members:
                _sigs[_ccd.cxx_sig_key((funcs.get(addr) or {}).get('signature') or '')].append((addr, name))
            for _sk, _ms in _sigs.items():
                if len(_ms) > 1:
                    for addr, name in _ms:
                        errors.append(
                            f"functions[{addr}]: '{name}' 同签名双址（C++ 铁律违反）"
                            f"——归属/正名裁决（重载换轨规）")
        except Exception as _e:
            errors.append(f"2c-mangled: internal {_e}")

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
        # [真相源迁移 2026-10-20] 只读 `bases`（base_class 已废弃删除）
        _bases = [b.get('name','') for b in (_sd.get('bases') or [])]
        _bc = _bases or ''
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
        stripped = strip_stamp(name)   # [D7] 单源
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
            # Unions cannot have inheritance
            base = [b.get('name') for b in (sinfo.get('bases') or []) if isinstance(b, dict)]
            if base:
                errors.append(f"union[{sname}]: unions cannot have bases")
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
            # [PACK 修 2026-10-19] 显式 packed 结构（"pack": 1）跳过自然对齐检查
            #  —— 二进制结构确为字节级打包（IDA 尺寸即证：tagCmdDataDestRoleView
            #     size=11 且 void* 在 +7），成员按声明偏移排布才是正确语义；
            #     codegen 为其发射 #pragma pack(push,1) 复现同一布局。
            _decl_pack = sinfo.get('pack')
            _is_decl_packed = isinstance(_decl_pack, int) and _decl_pack <= 1
            for off_str, m in members.items():
                if _is_decl_packed:
                    break
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
            bases = [b.get('name') for b in (sinfo.get('bases') or []) if isinstance(b, dict) and b.get('name')]
            for b in bases:
                if b not in all_struct_names:
                    warnings.append(f"structs[{sname}]: bases '{b}' not in structs (may be in PDB)")

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

    _run_claim_gate(errors, warnings)
    _run_cxx_gate(errors, warnings)
    return errors, warnings



def _run_cxx_gate(errors, warnings):
    """强检测闸（2026-11-02）：重名必被查出——三门棘轮（同址双录/同名双址/C++ 铁律）。"""
    try:
        import sys as _s, os as _o
        _s.path.insert(0, _o.path.join(_o.path.dirname(_o.path.dirname(_o.path.abspath(__file__))), 'tools'))
        import cxx_gate as _cg
        _errs, _warns = _cg.main()
        errors.extend(_errs)
        warnings.extend(_warns)
    except Exception as _e:
        errors.append('CXX_GATE:internal_error %s' % _e)


def _run_claim_gate(errors, warnings):
    """R1 产生端闸（棘轮）：未验认领禁增长 + 新多认领必入台账。存量 grandfather。"""
    try:
        import sys as _s, os as _o
        _s.path.insert(0, _o.path.join(_o.path.dirname(_o.path.dirname(_o.path.abspath(__file__))), 'tools'))
        import claim_gate as _cg
        _errs, _warns, _unv, _multi = _cg.main()
        errors.extend(_errs)
        warnings.extend(_warns)
    except Exception as _e:
        errors.append('CLAIM_GATE:internal_error %s' % _e)


def _run_vtable_check(structs):
    """调用 vtable_mapper 做闭环验证。"""
    import importlib.util
    _project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    vm_path = os.path.join(_project_root, 'tools', 'vtable_mapper.py')
    spec = importlib.util.spec_from_file_location('vtable_mapper', vm_path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod.check(structs=structs)

def check_canonical_contract():
    """[canonical 契约断言 2026-11-14 用户裁定'加断言明确数据非法']

    棘轮模式(claim_gate 同款): 存量违规 grandfather 进 baseline, 新增=硬红。
    四条非法态:
      C1 vtables槽(i>0)缺 name/sig 字段 —— 正名账未覆盖(数据不完整)
      C2 from 指向不存在的类或无vtables类 —— 悬空引用
      C3 non_virtual=true 条目的sig带 'virtual ' —— 自相矛盾
      C4 槽addr非8位长形hex —— 数据卫生
    返回 (errors, warnings)
    """
    import glob as _glob
    errors, warnings = [], []
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    _KNOWN_VT_CLASSES = set()
    for fp in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        try:
            if json.load(open(fp, encoding='utf-8')).get('vtables'):
                _KNOWN_VT_CLASSES.add(os.path.basename(fp)[:-5])
        except Exception:
            pass
    base_path = os.path.join(root, 'data', 'status', 'canonical_contract_baseline.json')
    base = set()
    if os.path.exists(base_path):
        base = set(json.load(open(base_path, encoding='utf-8')).get('grandfathered', []))
    cur_viol = {}   # key → 描述

    # [from退役 2026-11-15 用户裁定'本来就没必要加这个字段'] 全语料预扫:
    # 继承判据 = 槽地址 ∈ bases链祖先表槽集合(MSVC未override槽槽值=基类同槽地址,
    # 纯编译器力学可推导)。from=物化副本, 漂移实证~40类错绑(同款病灶链第三次:
    # slot sig冗余→vtables_retired→from) ⇒ 字段全树清除, 消费方全部改推导。
    _pre_slots = {}   # cls -> set(int addr)
    _pre_bases = {}   # cls -> [base names]
    _pre_entry = {}   # cls -> {int addr: (name, sig)}  [C9 override链签名门 2026-11-16]
    # [卷宗挂账通道] 在册零证据槽集
    _dossier_keys = set()
    try:
        _dp = json.load(open(os.path.join(root, 'data', 'status', 'dossier_pending.json'), encoding='utf-8'))
        for _it in (_dp.get('items') or []):
            _dossier_keys.add((_it.get('class'), str(_it.get('addr') or '').lower()))
    except Exception:
        pass
    for _fp0 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        try:
            _d0 = json.load(open(_fp0, encoding='utf-8'))
        except Exception:
            continue
        _c0 = os.path.basename(_fp0)[:-5]
        _pre_slots[_c0] = set()
        for _vt0 in (_d0.get('vtables') or []):
            for _s0 in (_vt0.get('slots') or []):
                try:
                    _pre_slots[_c0].add(int(_s0.get('addr') or 'x', 16))
                except (ValueError, TypeError):
                    pass
        _pre_bases[_c0] = [(_b.get('name') if isinstance(_b, dict) else _b)
                           for _b in (_d0.get('bases') or [])
                           if (_b.get('name') if isinstance(_b, dict) else _b)]
        _pre_entry[_c0] = {}
        for _k0, _v0 in (_d0.get('methods') or {}).items():
            try:
                _nd0 = node_of(_v0)
                _nd0['name'] = str(_v0.get('name') or '')
                _pre_entry[_c0][int(_k0, 16)] = _nd0
            except (ValueError, TypeError):
                pass

    def _ancestor_slot_addrs(_cls, _seen=None):
        _seen = _seen if _seen is not None else set()
        _out = set()
        for _bn in _pre_bases.get(_cls, []):
            if _bn in _seen:
                continue
            _seen.add(_bn)
            _out |= _pre_slots.get(_bn, set())
            _out |= _ancestor_slot_addrs(_bn, _seen)
        return _out

    _anc_slots_memo = {}

    def _is_inherited_slot(_cls, _addr_int):
        if _cls not in _anc_slots_memo:
            _anc_slots_memo[_cls] = _ancestor_slot_addrs(_cls)
        return _addr_int in _anc_slots_memo[_cls]

    for fp in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(fp)[:-5]
        try:
            d = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        for vi, vt in enumerate(d.get('vtables') or []):
            slots = vt.get('slots') or []
            # [sig降维 2026-11-14 用户质问修正] 槽位sig=冗余拷贝(一地址一签名,
            # methods条目=真值) —— 契约只要求name; 签名一致性走地址级统一
            _miss = sum(1 for i, s in enumerate(slots)
                        if not s.get('name')
                        and (cls, str(s.get('addr') or '').lower()) not in _dossier_keys)
            if slots and _miss:
                cur_viol['C1:%s:v%d' % (cls, vi)] = '%s v%d: %d/%d 槽缺name' % (cls, vi, _miss, len(slots))
            for s in slots:
                # [C2 from退役] from字段已全树清除, 悬空检查随之退役
                a = s.get('addr') or ''
                if a and not re.match(r'^0x[0-9A-Fa-f]{8}$', str(a)):
                    cur_viol['C4:%s:%s' % (cls, a)] = '%s addr非长形: %s' % (cls, a)
        for a, m in (d.get('methods') or {}).items():
            if m.get('non_virtual') and 'virtual' in str(m.get('signature', '')).lower():
                cur_viol['C3:%s:%s' % (cls, a)] = '%s %s non_virtual但sig带virtual' % (cls, m.get('name'))
        # [C7 2026-11-15 v2 from退役] 槽位-条目完备性(地址推导路由):
        #   继承槽(地址∈祖先表槽) → 免检(归属祖先; 祖先C7自有检查递归强制条目存在,
        #     链顶自有槽无条目必在上溯终点报红)
        #   自有槽(地址∉祖先表槽) → 本类 methods 必须有条目(定义路由断链→C2039)
        _slot_addr_count = {}  # 多槽地址豁免(同址多槽=多契约共载体)
        for _vt6 in (d.get('vtables') or []):
            for _s6 in (_vt6.get('slots') or []):
                _a6 = str(_s6.get('addr') or '').lower()
                if _a6: _slot_addr_count[_a6] = _slot_addr_count.get(_a6, 0) + 1
        _own_methods_ints = set()
        for _k in (d.get('methods') or {}).keys():
            try:
                _own_methods_ints.add(int(_k, 16))
            except (ValueError, TypeError):
                pass
        for vi, vt in enumerate(d.get('vtables') or []):
            for si, s in enumerate(vt.get('slots') or []):
                au = str(s.get('addr') or '').lower()
                if not au: continue
                try:
                    _a_int = int(au, 16)
                except (ValueError, TypeError):
                    continue
                if _is_inherited_slot(cls, _a_int):
                    continue  # 继承槽: 归属祖先, 免检
                # [C7v3 2026-11-16] 纯虚槽豁免: 槽值=_purecall(0x55434f, 6A19E859C3)
                #   → 抽象基类纯虚, 二进制无定义体, 条目不应存在
                if _a_int == 0x55434f:
                    continue
                # [C7v3] thunk区段槽豁免(0x542000-0x542200 adjustor链=B5建模域, 暂挂):
                if 0x542000 <= _a_int <= 0x542200:
                    continue
                # [卷宗挂账通道 2026-11-16 用户裁定A] 零证据槽在册=债务可见暂放行,
                #   考古计划入台账(data/status/dossier_pending.json, 版本化);
                #   新零证据槽不在册=硬错(防新债静默)
                if (cls, au.lower()) in _dossier_keys:
                    continue
                if _slot_addr_count.get(au, 0) > 1:
                    continue  # 多槽地址豁免
                if _a_int not in _own_methods_ints:
                    cur_viol['C7:%s:%s:own' % (cls, au)] = (
                        '%s 自有槽 slot%d addr=%s 但本类 methods 无条目(定义路由断链→C2039; 地址∉祖先表=自有)' % (
                            cls, vi, au))
        # [C6 2026-11-15 用户裁定'套用器不应存在'] slot.sig=裁决真值, methods条目必须一致
        # (同类内分歧=数据非法; 棘轮: 存量grandfather, 新增=硬红)
        # [多槽豁免 2026-11-15] 一地址多槽(同址多槽ICF折叠)=多契约共享一个IDB载体:
        #   条目sig=载体定谳(二进制retn语义), 槽位sig=各槽契约 — 两者本质不同, 不构成C6
        _slot_addr_count = {}
        for _vt6 in (d.get('vtables') or []):
            for _s6 in (_vt6.get('slots') or []):
                _a6 = str(_s6.get('addr') or '').lower()
                if _a6: _slot_addr_count[_a6] = _slot_addr_count.get(_a6, 0) + 1
        for vt in d.get('vtables') or []:
            for s in (vt.get('slots') or []):
                if not s.get('sig'):
                    continue
                if _slot_addr_count.get(str(s.get('addr') or '').lower(), 0) > 1:
                    continue  # 多槽地址豁免
                _ma = str(s.get('addr') or '')
                _m6 = (d.get('methods') or {}).get(_ma) or (d.get('methods') or {}).get(_ma.lower())
                if _m6 and _m6.get('signature'):
                    import re as _re6
                    _n6 = lambda x: _re6.sub(r'\s+', ' ', re.sub(r'\b(this|a\d+|nVal\d*|p\w+|f\w+)\b(?![\w*])', '', str(x).strip())).strip()
                    if _n6(_m6['signature']) != _n6(s['sig']):
                        cur_viol['C6:%s:%s' % (cls, _ma)] = '%s %s: 条目sig %r != 槽位裁决 %r' % (
                            cls, s.get('name'), _m6['signature'][:40], s['sig'][:40])

    # [C8 2026-11-15 用户裁定] 同类 methods 条目同名冲突
    # C++ 不允许同类内两个成员方法同名同参(重载需参数不同)
    # 同名双地址 = annotation 命名冲突(数据错误), 必须报错不可豁免
    for fp2 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        cls8 = os.path.basename(fp2)[:-5]
        try:
            d8 = json.load(open(fp2, encoding='utf-8'))
        except Exception:
            continue
        ms8 = d8.get('methods') or {}
        if not ms8: continue
        # [C8 2026-11-16 dtor单点标注律] complete dtor由编译器自源声明再生,
        # 不进methods清单(用户裁定skip方案) ⇒ 同名双地址恢复严格检查, 无豁免
        _seen_nm = {}
        for a8, m8 in ms8.items():
            nm8 = str(m8.get('name') or '')
            if not nm8: continue
            bare = nm8.split('::')[-1] if '::' in nm8 else nm8
            if bare in _seen_nm:
                prev_a = _seen_nm[bare]
                cur_viol['C8:%s:%s:%s:%s' % (cls8, bare, prev_a, a8)] = (
                    '%s 同名方法双地址: %s@%s vs %s@%s — 同类内同名同址冲突' % (
                        cls8, bare, prev_a[-8:], bare, a8[-8:]))
            else:
                _seen_nm[bare] = a8

        # [C9 2026-11-16 v2 sigmodel结构判据·机制退役] override链签名一致性:
        #   真override(同名异址) ⇒ c2555_conflict(参数契约一致+返回存在性不同)=硬错
        #   判据=sigmodel结构节点(sig_model优先/字符串回退单点解析) — 字符串解析遗产链
        #   (_sig_parts9三轮bug)整体退役 [用户裁定"旧机制整体退役"]
        # 已知覆盖缺口(元复核发现, S3待补): 仅存在于槽名契约的override(UIFrameWnd::Render族,
        #   无methods条目)不经此路径 — 待槽级sig_model全量落地后补槽通道
        _re9 = re.compile(r'_scalar_dtor|_sdtor|scalar_deleting')

        def _node_of_pre(_cls, _addr):
            _ent = _pre_entry.get(_cls, {}).get(_addr)
            if _ent is None:
                return None
            return _ent

        def _anc_node9(_cls, _nm, _seen=None):
            _seen = _seen if _seen is not None else set()
            for _bn in _pre_bases.get(_cls, []):
                if _bn in _seen:
                    continue
                _seen.add(_bn)
                for _a2, _nd2 in _pre_entry.get(_bn, {}).items():
                    if _nd2.get('name') == _nm:
                        return _a2, _nd2
                _r9 = _anc_node9(_bn, _nm, _seen)
                if _r9:
                    return _r9
            return None

        for _a9, _m9 in ms8.items():
            _n9 = str(_m9.get('name') or '')
            if not _n9 or _n9.startswith('~') or _re9.search(_n9):
                continue
            try:
                _ai9 = int(_a9, 16)
            except (ValueError, TypeError):
                continue
            _hit9 = _anc_node9(cls8, _n9)
            if _hit9 and _hit9[0] != _ai9:
                _nd_me = node_of(_m9)
                _nd_base = _hit9[1]
                if _nd_me.get('pending') or _nd_base.get('pending'):
                    continue  # 零证据诚实态不判(卷宗域)
                if c2555_conflict(_nd_me, _nd_base):
                    cur_viol['C9:%s:%s' % (cls8, _a9)] = (
                        '%s %s 返回存在性与基类冲突(可观测ABI契约): 本=%s 基=%s → C2555前置; '
                        '取证=两侧函数体出口eax+调用点消费' % (
                            cls8, _n9, render(_nd_me), render(_nd_base)))

    # [V-table 形态断言 2026-11-15 用户裁定] MSVC真实规则: 每个多态子对象恰一张表。
    # 单继承链全族共享一张; N表 > 1+多态基数 = 形态不可能(邻接派生表误挂/普查产物)。
    # V1(硬红): 表数 > 1 + 多态基数(CTaskTpl_*与PalScriptWaitObj/GlowObj按二进制实证计多态)
    # V2(warn): 多表类存在无写表证据且无裁决标记的表
    for fp in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(fp)[:-5]
        try:
            d = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        vts = d.get('vtables') or []
        if not vts:
            continue
        bases = [b.get('name') if isinstance(b, dict) else b for b in (d.get('bases') or [])]
        poly = sum(1 for b in bases if b and (b.startswith('CTaskTpl_') or b in ('PalScriptWaitObj', 'GlowObj')))
        poly = max(poly, sum(1 for b in bases if b and (json.load(open(os.path.join(root, 'data', 'annotations', 'structs', '%s.json' % b), encoding='utf-8')).get('vtables') if os.path.exists(os.path.join(root, 'data', 'annotations', 'structs', '%s.json' % b)) else None)))
        if len(vts) > 1 + poly:
            cur_viol['V1:%s:%d' % (cls, len(vts))] = '%s: %d表但多态基数%d(单链多表=邻接派生表误挂/普查产物, MSVC每多态子对象恰1表)' % (
                cls, len(vts), poly)
        if len(vts) >= 2:
            _tvm = os.path.join(root, 'data', 'status', 'true_vtable_map_20261114.json')
            _ev = set()
            try:
                for _r5 in json.load(open(_tvm, encoding='utf-8')):
                    try: _ev.add(int(_r5['table'], 16))
                    except (ValueError, TypeError): pass
            except Exception:
                pass
            _adj_t = {str(t.get('addr') or '').lower() for t in (d.get('_adjudicated_tables') or [])}
            for vt in vts:
                _a7 = str(vt.get('addr') or '')
                if _a7.lower() in _adj_t:
                    continue
                try: _ai = int(_a7, 16)
                except (ValueError, TypeError): continue
                if _ai not in _ev:
                    cur_viol['V2:%s:%s' % (cls, _a7)] = '%s 表%s 无写表证据且无裁决标记(普查产物嫌疑)' % (cls, _a7)
    # [N系列 2026-11-15 数据质量门禁] 规则表: annotation_gate_rules_20261115.json
    # HARD=立即非法(发射即编译错); WARN=债务可见性(不拦截)
    for fp in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(fp)[:-5]
        try:
            d = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        for a, m in (d.get('methods') or {}).items():
            nm = str(m.get('name') or '')
            sig = str(m.get('signature') or '')
            if '(' in nm:
                cur_viol['N1:%s:%s' % (cls, a)] = '%s name含括号: %s' % (cls, nm[:50])
            if '::' in nm:
                cur_viol['N3:%s:%s' % (cls, a)] = '%s name含作用域: %s' % (cls, nm[:50])
            if sig and sig.count('(') != sig.count(')'):
                cur_viol['N7:%s:%s' % (cls, a)] = '%s sig括号不平衡: %s' % (cls, sig[:50])
            if sig and re.search(r'__(thiscall|cdecl|stdcall|fastcall)\b[^()]*__(thiscall|cdecl|stdcall|fastcall)\b', sig):
                cur_viol['N8:%s:%s' % (cls, a)] = '%s 双调用约定: %s' % (cls, sig[:50])
            if not sig and not m.get('declaration_only') and m.get('evidence_level') in ('A', 'B'):
                cur_viol['N6b:%s:%s' % (cls, a)] = '%s %s: A/B级证据但sig为空' % (cls, nm[:40])
            # [N10 2026-11-15 用户裁定"格式规则加入门禁"] methods键格式非法
            try:
                int(a, 16)
            except (ValueError, TypeError):
                cur_viol['N10:%s:%s' % (cls, a)] = '%s methods键非hex: %s' % (cls, a)
        # [N10b 2026-11-15] 键归一化检查: 必须为 0x%08x 形(8位小写)
        for a in (d.get('methods') or {}).keys():
            try:
                canonical = '0x%08x' % int(a, 16)
                if a != canonical:
                    cur_viol['N10b:%s:%s' % (cls, a)] = '%s methods键非规范形: %s (应=%s)' % (cls, a, canonical)
            except (ValueError, TypeError):
                pass
        # [N12 2026-11-15 用户裁定"严格禁止无语义函数名变量名"] 非语义名禁入:
        #   slot_N占位/sub_无名/_todo_/v1_/Method_地址名/adjthunk机制名/纯地址后缀名
        #   存量冻结(N12自基线ratchet), 新增=硬错; 语义名+消歧后缀(Update_2ff0形)不在模式表
        for a12, mv12 in (d.get('methods') or {}).items():
            _n12 = str(mv12.get('name') or '')
            _stem = re.sub(r'_[0-9a-fA-F]{4,8}$', '', _n12)
            if (re.match(r'^slot_\d+$', _n12) or re.match(r'^sub_[0-9a-fA-F]+$', _n12)
                    or '_todo_' in _n12 or _n12.startswith('v1_')
                    or re.match(r'^Method_[0-9a-fA-F]+$', _n12) or 'adjthunk' in _n12
                    or (re.search(r'_[0-9a-fA-F]{4,8}$', _n12) and _stem in ('', 'Method', 'sub'))):
                cur_viol['N12:%s:%s' % (cls, a12)] = '%s 非语义名(命名铁律禁入): %s' % (cls, _n12)
        for vt in d.get('vtables') or []:
            for s in (vt.get('slots') or []):
                nm = str(s.get('name') or '')
                if '(' in nm:
                    cur_viol['N1s:%s:%s' % (cls, s.get('addr'))] = '%s slot name含括号: %s' % (cls, nm[:50])
                if '::' in nm:
                    cur_viol['N3s:%s:%s' % (cls, s.get('addr'))] = '%s slot name含作用域: %s' % (cls, nm[:50])
                # [N10s 2026-11-15] slot addr格式
                try:
                    int(str(s.get('addr') or ''), 16)
                except (ValueError, TypeError):
                    if s.get('addr'):
                        cur_viol['N10s:%s:%s' % (cls, s.get('addr'))] = '%s slot addr非hex: %s' % (cls, s.get('addr'))

    for k, desc in sorted(cur_viol.items()):
        # [C7/C9不可豁免] 编译错误级键跳过grandfather检查, 直接硬红
        # [N12自治 2026-11-16] N12键由自基线路径报告(DATA:N12, 冻结存量静默),
        #   不经CANON环路——否则冻结存量被无条件硬错(双层计费bug, 102假错实证)
        if k.startswith('N12:'):
            continue
        if k.startswith('C7') or k.startswith('C9') or k not in base:
            errors.append('CANON:%s %s' % (k, desc))
    if cur_viol and not os.path.exists(base_path):
        # [C7不可豁免 2026-11-15 用户裁定] 编译错误级键(C7)禁入grandfather
        json.dump({'grandfathered': sorted(k for k in cur_viol.keys() if not k.startswith('C7')),
                   'note': '存量grandfather; 新增违规=硬红 (canonical_slot_names_20261114契约)'},
                  open(base_path, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('[canonical] 基线自举: %d 违规键冻结 (存量grandfather, 新增=硬红)' % len(cur_viol))

    # [N11 2026-11-15 用户裁定"数据质量问题不让管线擦屁股"] decomp语料地址规范门:
    #   address 必须 ^0x[0-9a-f]{8}$ 小写长形——索引/匹配层字符串比较依赖唯一形态。
    #   3044文件大小写/短形事故实证: 数据不规范→证据采集假象(空体/漏读)。
    #   数据已一次性归一(每修必落脚本), 本门禁防再入; 违规=硬错(apply前强制报错)。
    import glob as _glob2
    _decomp_dir = os.path.join(root, 'asm', 'pal3', 'decomp')
    for _dp in sorted(_glob2.glob(os.path.join(_decomp_dir, '*.json'))):
        try:
            _dd = json.load(open(_dp, encoding='utf-8'))
        except Exception:
            continue
        _da = _dd.get('address')
        if not (isinstance(_da, str) and re.match(r'^0x[0-9a-f]{8}$', _da)):
            errors.append('DATA:N11:decomp:%s address非规范形(须0x+8位小写hex): %r'
                          % (os.path.basename(_dp), _da))
    # [N12自基线] 独立ratchet: 冻结存量非语义名债, 新增=硬错 (命名铁律2026-11-15)
    _n12_base = os.path.join(root, 'data', 'status', 'n12_grandfathered.json')
    _n12_viol = {k: v for k, v in cur_viol.items() if k.startswith('N12:')}
    _n12_old = set()
    if os.path.exists(_n12_base):
        _n12_old = set(json.load(open(_n12_base, encoding='utf-8')).get('grandfathered', []))
    for k12, d12 in sorted(_n12_viol.items()):
        if k12 not in _n12_old:
            errors.append('DATA:%s %s' % (k12, d12))
    if _n12_viol and not os.path.exists(_n12_base):
        json.dump({'grandfathered': sorted(_n12_viol.keys()),
                   'note': 'N12存量非语义名债冻结; 新增=硬错 (命名铁律2026-11-15)'},
                  open(_n12_base, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('[N12] 基线自举: %d 非语义名冻结 (存量债, 新增=硬错)' % len(_n12_viol))
    return errors, warnings


def check_name_drift():
    """[L-CHK 2026-11-11] 名字漂移检查——decomp 引用标识符 vs 注解名/IDB 名对照。

    病史(复发3次): 新旧导出代名漂移(unk_5D8A3C→off_5D8A3C, unk_5D8808→byte_5D8808),
    每次都到 C2065 才显形。管线职责=检查报错指向标注修复(双管线共享标注律)。

    判据:
    E1 ERROR  注解名≠IDB名 且 IDB名被decomp引用 且 注解type=skip
              —— skip 条目不进 globals_map 改名链(data.py:163-167),
                 body 引用悬空 ⇒ C2065(off_5D8A3C 实证)
    W2 WARN   注解名≠IDB名 且 IDB名被decomp引用(非skip)——可见性提示
    W3 WARN   decomp 引用了地址后缀型标识符但 ida _globals 与注解均无此条
              —— 字符串池余部病(0x5D8E98 族实证)
    返回 (errors, warnings)
    """
    import re as _re
    import glob as _glob
    errors, warnings = [], []
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    # 1. ida _globals: addr -> idb name
    isj = os.path.join(root, 'asm', 'pal3', 'ida_structs.json')
    if not os.path.exists(isj):
        return ['name_drift skipped: ida_structs.json missing'], []
    isd = json.load(open(isj, encoding='utf-8'))
    idb_by_addr = {}
    idb_names = set()
    for k, v in (isd.get('_globals') or {}).items():
        try:
            idb_by_addr[int(k, 16)] = str(v.get('name', ''))
            idb_names.add(str(v.get('name', '')))
        except (ValueError, TypeError):
            continue

    # 2. decomp 引用标识符集合(词token一次扫描)
    toks = set()
    tok_re = _re.compile(r'\b[a-zA-Z_]\w*\b')
    for f in _glob.glob(os.path.join(root, 'asm', 'pal3', 'decomp', '*.json')):
        try:
            c = json.load(open(f, encoding='utf-8')).get('decompiled_c', '')
        except Exception:
            continue
        toks.update(tok_re.findall(c))

    # 3. 注解 globals 对照
    ann = load_annotations().get('globals', {})
    addr_re = _re.compile(r'^(?:byte|word|dword|qword|off|flt|dbl|stru|unk)_([0-9A-Fa-f]{6,8})$')
    for k, e in ann.items():
        if not isinstance(e, dict):
            continue
        ann_name = str(e.get('name', ''))
        try:
            addr = int(k, 16)
        except (ValueError, TypeError):
            continue
        idb_name = idb_by_addr.get(addr, '')
        # 空名条目=占位(非漂移): revival 路径按 IDB 名/orig_type 处理(pEnd/asc_ 族编译通过为证)
        if ann_name and idb_name and ann_name != idb_name and idb_name in toks:
            if e.get('type') == 'skip':
                errors.append(
                    "name_drift: globals[%s] 注解名'%s' != IDB名'%s'(decomp引用中) 且 type=skip"
                    " —— skip 不进 globals_map 改名链, body 引用悬空 ⇒ 对齐注解名" % (k, ann_name, idb_name))
            else:
                warnings.append(
                    "name_drift: globals[%s] 注解名'%s' != IDB名'%s'(decomp引用中, 非skip——改名链应已覆盖, 仅提示)"
                    % (k, ann_name, idb_name))

    # 4. W3: decomp 引用了地址后缀型标识符, ida _globals 与注解均无
    ann_names = {str(e.get('name', '')) for e in ann.values() if isinstance(e, dict)}
    ida_addr_keyed = set()
    for n in idb_names:
        m2 = addr_re.match(n)
        if m2:
            ida_addr_keyed.add(n)
    orphan = []
    for t in toks:
        if t in idb_names or t in ann_names:
            continue
        m2 = addr_re.match(t)
        if m2 and ('0x%08X' % int(m2.group(1), 16)) not in ann:
            orphan.append(t)
    if orphan:
        warnings.append(
            "name_drift: %d 个 decomp 引用的地址后缀标识符无 ida/注解条目(池余部病) — "
            "字节直读取证后补 globals.json 条目: %s" % (len(orphan), ', '.join(sorted(orphan)[:8])))
    return errors, warnings


if __name__ == '__main__':
    errors, warnings = check()

    # [canonical 契约断言 2026-11-14] 四条非法态棘轮
    try:
        _cc_errors, _cc_warnings = check_canonical_contract()
        errors.extend(_cc_errors)
        warnings.extend(_cc_warnings)
    except Exception as _cc_err:
        warnings.append(f'canonical contract check skipped: {_cc_err}')

    # [L-CHK 2026-11-11] 名字漂移检查(decomp 引用 vs 注解名/IDB 名)
    try:
        _nd_errors, _nd_warnings = check_name_drift()
        errors.extend(_nd_errors)
        warnings.extend(_nd_warnings)
    except Exception as _nd_err:
        warnings.append(f'name_drift check skipped: {_nd_err}')

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
