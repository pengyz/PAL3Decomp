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
import glob
import os
import re
try:
    from pipeline.sigmodel import parse_signature, node_of, override_check, render
except ImportError:  # 脚本模式(sys.path[0]=pipeline/)兼容
    from sigmodel import parse_signature, node_of, override_check, render

import sys

_PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, _PROJECT_ROOT)

from pipeline.gen.annotation_view import iter_struct_files, iter_structs, load_struct, sm_text
from pipeline.ida.vc6_mangler import strip_stamp   # [D7] 单源

ANN_DIR = os.path.join(_PROJECT_ROOT, 'data', 'annotations')

def _exe_text_span(exe_path):
    """读 exe .text (VA, body)——N22 对偶闭环/N24 地址域门共用。异常返回 None。"""
    import struct as _s22x
    try:
        _d = open(exe_path, 'rb').read()
    except OSError:
        return None
    try:
        _e = _s22x.unpack_from('<I', _d, 0x3C)[0]
        _ns = _s22x.unpack_from('<H', _d, _e + 6)[0]
        _opt = _s22x.unpack_from('<H', _d, _e + 20)[0]
        for _i in range(_ns):
            _s = _e + 24 + _opt + 40 * _i
            if _d[_s:_s + 8].rstrip(b'\0') == b'.text':
                _vs, _va, _rs, _ra = _s22x.unpack_from('<IIII', _d, _s + 8)
                return (_va + 0x400000, _d[_ra:_ra + _rs])
    except Exception:
        pass
    return None






def _sig_str_of_local(m):
    """[退役字段修正 2026-11-21] sig_model 单源渲染（apply_annotations._sig_str_of
    同款）——signature 字段已退役，一切 structs 域签名读取必须走此处。"""
    sm = m.get('sig_model') or {}
    if sm.get('pending'):
        return ''
    try:
        _n = node_of(m)
        return render(_n) if _n else ''
    except Exception:
        return ''


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

        # [N24 地址域门 2026-11-22] functions 条目地址必须落在 .text——
        #   .rdata/数据区"函数"=IDA 误析幽灵(本会话 gbVec3D_ctor size=3B 实证:
        #   字节=指针数组, 零呼叫者)。ERROR 级: 数据区无代码语义。
        _exe_span24 = _exe_text_span(os.path.join(_PROJECT_ROOT, 'original', 'PAL3.exe'))
        try:
            _addr24 = int(addr, 16)
        except (ValueError, TypeError):
            _addr24 = None
        if _exe_span24 and _addr24 is not None:
            _t24va, _t24body = _exe_span24
            if not (_t24va <= _addr24 < _t24va + len(_t24body)):
                errors.append(
                    f"functions[{addr}]: 地址不在 .text 段({nm} in "
                    f"{hex(_t24va)}-{hex(_t24va + len(_t24body))})——数据区幽灵条目, 删除")

        # Check 2: __thiscall without :: suggests misattributed member function
        # （判据修正 2026-10-17 verifier：签名含 '::' 不报——R15 纯函数）
        # [free_helper 豁免 2026-11-22] 数据层字段 free_helper_confirmed=true = 该
        #   __thiscall 自由助手已经五面/ECX 呼叫点取证确认（AllocObject 100 站案）
        #   ——PAL3 存在无类全局 thiscall 工具函数族，门禁机械尊重数据层标记
        _free_helper = bool(info.get('free_helper_confirmed'))
        if addr not in _struct_method_addrs and not _free_helper \
                and needs_member_attr_warning(name, sig):
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
                    if sm_text(_dminfo):
                        errors.append(
                            f"structs[{_sn}]: method '{_dminfo.get('name','')}' @ {hex(_d_addr)} "
                            f"(ordinal {_bord}) has same address as {_base_name} — "
                            f"inherited, not overridden. Remove 'signature' field.")
                elif _b_addr != _d_addr:
                    _bname = _bminfo.get('name', '')
                    _dname = _dminfo.get('name', '')
                    if _dname == _bname and not sm_text(_dminfo):
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
            # [R6 门禁升级 20261120] 两新模式(登记级 warning):
            #   A. 尾部大写单字母 A-E(CachedA/B 族残种——伪语义台账 20261118 在案)
            #   B. 下划线分隔形 m_XX_State_4968(老正则无分隔符分支漏检——CLAUDE.md 例)
            # 词干须含小写+不含数字; 白名单尾词=合法缩写(ID/CRC/NPC/VB/IB)与
            # 过去式后缀(ED——CatchED 动词形), 非序列字母
            _AB_LOWER = re.match(r'^m_[a-z]\D*([A-E])$', mname)
            _tail_upper = _AB_LOWER if (_AB_LOWER and not re.search(
                r'(?:ID|CRC|NPC|VB|IB|ED)$', mname)
                and not re.search(r'(?:Param|Todo|Field)[0-9A-Fa-f]{0,2}[A-E]$', mname)
                and 'Todo' not in mname
                and not re.search(r'[A-Z]{3,}$', mname)) else None
            _hollow_sep = re.match(
                r'^m_[nfb]\w*_(?:Val|Flag|State|Param|Init|Zero)_?([0-9A-Fa-f]{2,6})$',
                mname,
            )
            _hollow = re.match(
                r'^m_[nfb](?:Val|Flag|State|Param|Init|Zero)([0-9A-Fa-f]{2,6})$',
                mname,
            )
            if _tail_upper:
                warnings.append(
                    f"structs[{sname}]: '{mname}' at offset {off} 尾部大写单字母 "
                    f"'{_tail_upper.group(1)}'(A-E)——伪语义台账 20261118 CachedA/B 族残种形态, "
                    f"禁止新增(R6 门禁升级登记)"
                )
                continue  # 已报, 不重复走 hollow 判定
            if _hollow_sep:
                warnings.append(
                    f"structs[{sname}]: '{mname}' at offset {off} 下划线分隔伪语义形"
                    f"(HOLLOW_词_序号)——CLAUDE.md 禁止伪语义命名(R6 门禁升级登记)"
                )
                continue
            if _hollow:
                _suffix = _hollow.group(1)
                try:
                    _off_dec = int(off.split('_')[0], 16)
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
                real_off = int(off.split('_')[0], 16)
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
                    str(_sig_str_of_local(_reg) or '').rstrip().endswith('(...)')  # [退役字段修正] sig_model单源
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
    _run_n15_ctor_gate(errors, warnings)
    _run_n16_schema_gate(errors, warnings)
    _run_n17_addr_unique_gate(errors, warnings)
    _run_type_resolve_gate(errors, warnings)
    return errors, warnings


def _run_type_resolve_gate(errors, warnings):
    """[REF 类型完备性门 2026-11-20·用户裁定] ref语义前置化——任何被引用类型
    (含primitive)必须能resolve。pipeline/type_resolver.py 全量普查(17880位点/
    注册表1198条/七类声明域), 首跑 2066→84 全部人工定性为真数据病(零假阳性:
    *this污染×57/存储类污染×9/拼写病×9/return吞名×3/幽灵嵌套引用×5/gbOBBox
    无声明×1), 84项的 [5b] 应用失败已在 apply fail-loud 实证同源。
    未resolve数据病不容错(哑忍⇒hexrays重推断⇒C2511族重演)⇒硬错。
    宇宙缺口(新类型域出现)时该门会以假阳性显形⇒届时补声明域再修数据。"""
    try:
        import type_resolver as _tr
    except ImportError:
        try:
            from pipeline import type_resolver as _tr
        except ImportError:
            warnings.append('REF:type_resolver导入失败(门未生效)')
            return
    try:
        _failures, _warns, _nrefs, _nreg, _edges = _tr.collect()
    except Exception as _e:
        errors.append('REF:internal_error %s' % _e)
        return
    for _w in _warns:
        warnings.append('REF:%s' % _w)
    for _src, _own, _fld, _ts, _base, _why in _failures:
        errors.append('REF:%s:%s:%s type=%r 未resolve(%s)'
                      % (_src, str(_own)[:14], _fld, str(_ts)[:50], _why))


def _run_n17_addr_unique_gate(errors, warnings):
    """[N17 地址唯一性 2026-11-17 用户裁定] 一地址一条methods条目(唯一所有者类)。
    虚表槽不受限(槽=契约)。折叠载体多类声明唯一合法通道=multi_claim_ledger登记
    (逐条evidence); 未登记多认领=ERROR。"""
    import glob as _glob
    _owner = {}
    _multi = {}
    for _fp in _glob.glob(os.path.join(_PROJECT_ROOT, 'data', 'annotations', 'structs', '*.json')):
        _cls = os.path.basename(_fp)[:-5]
        try:
            _d = json.load(open(_fp, encoding='utf-8'))
        except Exception:
            continue
        for _ea in (_d.get('methods') or {}):
            try:
                _k = int(str(_ea), 16)
            except (ValueError, TypeError):
                continue
            if _k in _owner:
                _multi.setdefault(_k, [_owner[_k]]).append(_cls)
            else:
                _owner[_k] = _cls
    _led_p = os.path.join(_PROJECT_ROOT, 'data', 'status', 'pending', 'multi_claim_ledger.json')
    _led_ok = set()
    try:
        _led = json.load(open(_led_p, encoding='utf-8'))
        for _e in (_led if isinstance(_led, list) else (_led.get('entries') or [])):
            _a = str((_e.get('addr') or '')) if isinstance(_e, dict) else ''
            if _a:
                _led_ok.add(int(_a, 16))
    except Exception:
        pass
    for _k, _clss in sorted(_multi.items()):
        if _k in _led_ok:
            continue
        errors.append('N17:0x%08x 多类认领methods(%s)——折叠载体须ledger登记, '
                      '归属错误须删认领(唯一所有者律)' % (_k, ','.join(_clss[:6])))


def _run_n16_schema_gate(errors, warnings):
    """[N16 schema 2026-11-17 用户裁定] 标注层数据格式门禁——按
    data/annotations/annotation_schema.json 校验。退役字段=禁止存在。"""
    import glob as _glob
    _sch_p = os.path.join(_PROJECT_ROOT, 'data', 'annotations', 'annotation_schema.json')
    try:
        _sch = json.load(open(_sch_p, encoding='utf-8'))
    except Exception as _e:
        errors.append('N16:schema_unreadable %s' % _e)
        return
    _sc = _sch['structs_class']
    _me = _sc['methods_entry']
    _n = 0
    for _fp in _glob.glob(os.path.join(_PROJECT_ROOT, 'data', 'annotations', 'structs', '*.json')):
        _cls = os.path.basename(_fp)[:-5]
        try:
            _d = json.load(open(_fp, encoding='utf-8'))
        except Exception:
            continue
        for _b in _sc['banned']:
            if _b in _d:
                errors.append('N16:structs[%s] 退役字段 %s 存在(禁止, 非null=不存在)' % (_cls, _b))
                _n += 1
        if _cls != _d.get('name'):
            errors.append('N16:structs[%s] name=%r 与文件名不符' % (_cls, _d.get('name')))
            _n += 1
        for _ea, _m in (_d.get('methods') or {}).items():
            if not isinstance(_m, dict):
                continue
            if not re.match(_me.get('key_format', ''), str(_ea)):
                errors.append('N16:structs[%s].%s 键形违规' % (_cls, _ea))
                _n += 1
            for _b in _me['banned']:
                if _b in _m:
                    errors.append('N16:structs[%s].%s 退役字段 %s 存在' % (_cls, _ea, _b))
                    _n += 1
            _fl = _m.get('flags') or []
            for _f in _fl:
                if _f not in _me['flags_vocabulary']:
                    errors.append('N16:structs[%s].%s flags词表外: %r' % (_cls, _ea, _f))
                    _n += 1
            if 'override' in _fl and not _m.get('override_of'):
                errors.append('N16:structs[%s].%s override缺override_of' % (_cls, _ea))
                _n += 1
            # [N18 2026-11-19 用户裁定] dtor 名形冗余强校验——flags 与名字互为
            # 双向断言, 违规报错禁准入(不 warns):
            #   dtor/deleting ∈ flags ⇔ 名呈 ~X 形(可推导标签, 形态信息上移 flags,
            #   名槽禁 _sdtor*/_scalar_dtor*/scalar_deleting 等二进制形态名)
            _is_dtor_flag = 'dtor' in _fl or 'deleting' in _fl
            _is_dtor_name = bool(re.match(r'^~', str(_m.get('name') or '')))
            if _is_dtor_flag and not _is_dtor_name:
                errors.append(
                    'N18:structs[%s].%s flags含dtor/deleting但名非~X形: %r '
                    '——析构源名唯一可推导(~类名), 形态信息须上移flags, '
                    '_sdtor*/_scalar_dtor* 形态名禁入名槽' % (_cls, _ea, _m.get('name')))
                _n += 1
            elif _is_dtor_name and not _is_dtor_flag:
                errors.append(
                    'N18:structs[%s].%s 名呈~X形但flags缺dtor——身份标注缺失, '
                    '先修flags再准入' % (_cls, _ea))
                _n += 1
            if 'deleting' in _fl and 'dtor' not in _fl:
                errors.append(
                    'N18:structs[%s].%s deleting须与dtor同现(deleting=析构的'
                    '编译器形态标记, 不能独立存在)' % (_cls, _ea))
                _n += 1
            _sm = _m.get('sig_model')
            if _sm is not None:
                for _r in _me['sig_model_required']:
                    if _r not in _sm:
                        errors.append('N16:structs[%s].%s sig_model缺%s' % (_cls, _ea, _r))
                        _n += 1
                # [N19 裸void参数禁令 2026-11-20] C2860直证: Actor.h:239
                # `void GetAnimDataBuffer(void, int)` 单行级联封死222cpp+6头
                # (S2 ok 0/222)。裸void参数在C++非法(C2860 "'void' cannot be
                # an argument type")——出参占位用void*(N17律先例), 无参用[]。
                # return=void合法(无返回值), 不在禁列。
                for _pi, _pp in enumerate(_sm.get('params') or []):
                    if isinstance(_pp, dict) and str(_pp.get('type') or '').strip() == 'void':
                        errors.append(
                            'N19:structs[%s].%s 参数#%d type=裸void——C2860级联源'
                            '(Actor.h:239案), 出参占位void*/无参用params:[]'
                            % (_cls, _ea, _pi))
                        _n += 1
                # [类型令牌/cc 校验已上移 2026-11-20·用户裁定] N21/N22 令牌黑名单
                # 方案被否, 职责由 REF 类型完备性门(_run_type_resolve_gate,
                # pipeline/type_resolver.py)承担——resolve不变量覆盖一切类型病;
                # 成员cc规范(析构恒thiscall/非thiscall裁定队列)留待REF战役后
                # 以独立小门回归。
        for _vt in (_d.get('vtables') or []):
            for _s in (_vt.get('slots') or []):
                for _b in _sc['vtable_slot']['banned']:
                    if _b in _s:
                        errors.append('N16:structs[%s] 槽退役字段 %s 存在' % (_cls, _b))
                        _n += 1
    # functions.json
    _fj = _sch['functions_json']
    _fpj = os.path.join(_PROJECT_ROOT, 'data', 'annotations', 'functions.json')
    try:
        _fdata = json.load(open(_fpj, encoding='utf-8'))
    except Exception as _e:
        errors.append('N16:functions_unreadable %s' % _e)
        return
    for _ea, _e in _fdata.items():
        if not isinstance(_e, dict):
            continue
        if not re.match(_fj['key_format'], str(_ea)):
            errors.append('N16:functions.%s 键形违规' % _ea)
            _n += 1
        _nm = _e.get('name') or ''
        if '::' in _nm:
            errors.append('N16:functions.%s 类方法名 %r 禁止(structs层权威)' % (_ea, _nm[:40]))
            _n += 1
        for _bad in _fj['signature_banned_substrings']:
            if _bad in str(_e.get('signature') or ''):
                errors.append('N16:functions.%s signature含禁止子串 %r' % (_ea, _bad))
                _n += 1
        # [N19 裸void参数禁令 2026-11-20] 同structs侧——sig_model与legacy signature
        # 双源都查(Actor.h:239 C2860级联案, S2 ok 0/222)。
        _fsm = _e.get('sig_model')
        if isinstance(_fsm, dict):
            for _pi, _pp in enumerate(_fsm.get('params') or []):
                if isinstance(_pp, dict) and str(_pp.get('type') or '').strip() == 'void':
                    errors.append(
                        'N19:functions.%s 参数#%d type=裸void——C2860级联源, '
                        '出参占位void*/无参用params:[]' % (_ea, _pi))
                    _n += 1
    if _n:
        warnings.insert(0, 'N16[schema]: %d 处格式违规(详见errors——当前计入errors硬失败, 清零后转常规)' % _n)


def _run_n15_ctor_gate(errors, warnings):
    """[N15 ctor存在性 2026-11-17 用户裁定] 真正的类必须有构造——有vtable类
    无ctor证据=伪造候选(身份案队列)。证据源仅两个: ctor写表普查(二进制)+
    注解flags(决策层); ida_structs是导出数据不作证据(谱系裁定 2026-11-17)。
    gb*引擎类豁免(头来自gbengine_prelude非生成物)。advisory普查模式——
    逐例裁定清零后升硬失败(房规)。"""
    try:
        _reg_p = os.path.join(_PROJECT_ROOT, 'data', 'status',
                              'ctor_evidence_registry_20261117.json')
        _reg = set(json.load(open(_reg_p, encoding='utf-8')).get('classes') or {})
        _ida_p = os.path.join(_PROJECT_ROOT, 'asm', 'pal3', 'ida_structs.json')
        _ida = json.load(open(_ida_p, encoding='utf-8'))
        _n15 = sorted(
            _n for _n, _e in _ida.items()
            if isinstance(_e, dict) and _e.get('vtables') and not _n.startswith('gb')
            and _n not in _reg)
        if _n15:
            warnings.append(
                'N15[advisory普查]: %d个有vtable类无ctor证据=伪造候选(身份案队列): %s'
                % (len(_n15), ','.join(_n15[:20])))
    except Exception as _e:
        errors.append('N15:internal_error %s' % _e)



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
    _pre_slot_addrs_by_idx = {}   # cls -> [int addr按槽序] 主表槽地址序列 [C9槽位匹配 2026-11-16]
    _pre_slot_names = {}   # cls -> {slot_idx: 槽名} 每槽一名链律载体 [C9槽名比较 2026-11-16]
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
        _vts0 = _d0.get('vtables') or []
        # 主表=首张vtable(MSVC每多态子对象恰1表; 槽位匹配按主表序)
        if _vts0:
            _lst0 = []
            _nm0 = {}
            for _i0, _s0 in enumerate(_vts0[0].get('slots') or []):
                try:
                    _lst0.append(int(_s0.get('addr') or 'x', 16))
                except (ValueError, TypeError):
                    _lst0.append(None)  # 槽位占位保持序号对齐
                if _s0.get('name'):
                    _nm0[_i0] = str(_s0.get('name'))
            _pre_slot_addrs_by_idx[_c0] = _lst0
            _pre_slot_names[_c0] = _nm0
        for _vt0 in _vts0:
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
            # [退役字段消费修正 2026-11-21] 旧读 m['signature'](已退役恒空)
            # ⇒ C3 检查从未生效(死检); sig 单源=_sig_str_of
            _c3sig = _sig_str_of_local(m)
            if m.get('non_virtual') and 'virtual' in str(_c3sig).lower():
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
                _m6 = (d.get('methods') or {}).get(_ma)  # [键形归一后精确查找 2026-11-16, 双形态容忍已拆]
                if _m6 and sm_text(_m6):
                    import re as _re6
                    _n6 = lambda x: _re6.sub(r'\s+', ' ', re.sub(r'\b(this|a\d+|nVal\d*|p\w+|f\w+)\b(?![\w*])', '', str(x).strip())).strip()
                    if _n6(sm_text(_m6)) != _n6(s.get('sig', '')):
                        cur_viol['C6:%s:%s' % (cls, _ma)] = '%s %s: 条目sig %r != 槽位裁决 %r' % (
                            cls, s.get('name'), sm_text(_m6)[:40], s.get('sig', '')[:40])

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
        # [N18 产物族豁免 2026-11-19 用户裁定] dtor 归一名槽后, ~X 多址=编译器
        # 产物族(??1 + ??_G + 多态链各表 ??_G), 非数据冲突——豁免判据:
        # 条目任一 (flags含deleting ∨ declaration_only) 即产物成员; 族内须
        # 恰有一个非产物成员(定义源), 两个定义源仍报错(真冲突不豁免)。
        _seen_nm = {}
        _dtor_family = {}
        for a8, m8 in ms8.items():
            nm8 = str(m8.get('name') or '')
            if not nm8: continue
            bare = nm8.split('::')[-1] if '::' in nm8 else nm8
            _fl8 = m8.get('flags') or []
            if bare.startswith('~') and m8.get('declaration_only'):
                _dtor_family.setdefault(bare, []).append(a8)
                continue  # 产物成员不参与同名冲突计数
            if bare in _seen_nm:
                # [签名感知 2026-11-17 与CXX_GATE闸②同裁定] 同名异签=合法重载
                # (C++同名不同参=不同函数, SaleUI Update 0参/2参实证);
                # 同名同签双址=真冲突
                _s1 = re.sub(r'\s+', ' ', sm_text(m8))
                _s2 = re.sub(r'\s+', ' ', sm_text(ms8.get(_seen_nm[bare]) or {}))
                if _s1 == _s2:
                    cur_viol['C8:%s:%s:%s:%s' % (cls8, bare, _seen_nm[bare], a8)] = (
                        '%s 同名同签双地址: %s@%s vs %s@%s — 同类内同名同签冲突' % (
                            cls8, bare, _seen_nm[bare][-8:], bare, a8[-8:]))
            else:
                _seen_nm[bare] = a8
        # 产物族一致性: 每个析构名须有定义源(非产物成员), 否则=全伴生无主
        # [T4-P0 20261121] 两向收紧: ①定义源形状校验(定义源不得含deleting flag——
        #   WeatherEffectNode案: 删除式被立为定义源=双析构); ②no_complete_form豁免:
        #   VC6 /O1 可将完全形内联进删除式后丢弃独立完全形(四形态全删除式实证),
        #   类note含 no_complete_form 标记时孤儿降级warning+债登记(源dtor体待手写)
        _ncf = 'no_complete_form' in str(d8.get('note') or '')
        # [deleted-form ABI 判据 20261121] C8 旧模型"删除式不得立为定义源"已被
        # S4 字节证据证伪(CameraCtrl/UI3DCtrl/TextureLib 族: 类内全为删除式形态,
        # 完全形不存在(trivial析构/ICF折叠桩)——删除式=唯一 dtor=必须的定义源,
        # N18 源级化承担体; 合成模型下 ??1/??_G 双符号自该定义再生)。
        # 新判据: 族内无非删除条目时, 未压制的删除式条目=合法定义源。
        for _fb, _faddrs in _dtor_family.items():
            _family_all_deleting = all(
                'deleting' in str(m9.get('flags') or [])
                for a9, m9 in ms8.items() if str(m9.get('name') or '') == _fb)
            _has_src = False
            _src_bad = []
            for a9, m9 in ms8.items():
                if str(m9.get('name') or '') == _fb and a9 not in _faddrs:
                    if 'deleting' in str(m9.get('flags') or []):
                        if _family_all_deleting:
                            _has_src = True   # deleted-form ABI: 唯一形态=定义源
                            break
                        _src_bad.append(a9)
                        continue
                    _has_src = True
                    break
            if not _has_src:
                _msg = '%s %s 产物族(%s)无定义源条目——伴生标记缺失, 补 declaration_only/' \
                       'deleting 判定' % (cls8, _fb, ','.join(_faddrs))
                if _src_bad:
                    _msg += '；[T4-P0] 定义源形状违例: %s 含deleting flag(删除式不得立为定义源)' % ','.join(_src_bad)
                if _ncf:
                    warnings.append('C8:no_complete_family:%s:%s %s — 无完全形族(源dtor体待手写, 债登记)' % (cls8, _fb, _msg))
                else:
                    cur_viol['C8:%s:%s:orphan_family' % (cls8, _fb)] = _msg

        # [C9 2026-11-16 v3 槽位感知·名字+签名双检] override链一致性:
        #   同槽位: 基/派生名字应一致(override=C++同名规则), 签名应兼容(C2555判据)
        #   名字不一致=silent bug(折叠载体名≠链律名), 签名冲突=C2555
        #   双检全拦截 [用户裁定"名字对不上也是需要被检出的bug"]
        _re9 = re.compile(r'_scalar_dtor|_sdtor|scalar_deleting|scalar deleting|`')

        def _anc_slot_chain(_cls, _slot_idx, _seen=None, _first=None):
            """沿祖先链找同一slot位的条目节点, 返回(祖先名, addr, node)或None
            [MI双基链 2026-11-16] _first=首跳基覆盖(tidx>=1次表↔bases[tidx]链,
            后续跳仍沿各祖先bases[0]链, 每祖先取其主表vtables[0])"""
            _seen = _seen if _seen is not None else set()
            for _bn in (_first if _first is not None else _pre_bases.get(_cls, [])):
                if _bn in _seen:
                    continue
                _seen.add(_bn)
                # 预扫的按序槽地址列表(None占位=该槽无地址, 视为链断)
                _bslot_addrs = _pre_slot_addrs_by_idx.get(_bn)
                if _bslot_addrs and _slot_idx < len(_bslot_addrs):
                    _baddr_int = _bslot_addrs[_slot_idx]
                    _bnode = _pre_entry.get(_bn, {}).get(_baddr_int) if _baddr_int is not None else None
                    if _bnode is not None:
                        return _bn, _baddr_int, _bnode
                _r = _anc_slot_chain(_bn, _slot_idx, _seen)
                if _r:
                    return _r
            return None

        # 本类vtable slot_idx→addr映射(用于找methods条目的slot位置)
        # [MI双基链建模 2026-11-16] addr→(表序tidx, 槽序sidx); tidx=k比较沿bases[k]链
        # (复核P0-1实证: tables[k]↔bases[k], 后续跳沿祖先bases[0]链取主表)
        _my_slot_by_addr = {}
        _mi_pending = set()
        _my_slot_names = {}
        _my_vts_me = d8.get('vtables') or []
        for _ti_me, _vt_me in enumerate(_my_vts_me):
            for _si_me, _sl_me in enumerate(_vt_me.get('slots') or []):
                try:
                    _a_me = int(_sl_me.get('addr'), 16)
                    _my_slot_by_addr[_a_me] = (_ti_me, _si_me)
                except (ValueError, TypeError):
                    pass
        if _my_vts_me:
            for _si_me, _sl_me in enumerate(_my_vts_me[0].get('slots') or []):
                if _sl_me.get('name'):
                    _my_slot_names[_si_me] = str(_sl_me.get('name'))

        for _a9, _m9 in ms8.items():
            _n9 = str(_m9.get('name') or '')
            if not _n9 or _n9.startswith('~') or _re9.search(_n9):
                continue
            try:
                _ai9 = int(_a9, 16)
            except (ValueError, TypeError):
                continue
            _tinfo = _my_slot_by_addr.get(_ai9)
            if _tinfo is None:
                continue  # 非槽函数(不在任何vtable slot位), 不判
            _tidx9, _si9 = _tinfo
            _first9 = None
            if _tidx9 >= 1:
                _bl9 = _pre_bases.get(cls8, [])
                if _tidx9 >= len(_bl9):
                    _mi_pending.add(_ai9)
                    continue  # 次表无对应基声明, 不判(MI待补)
                _first9 = [_bl9[_tidx9]]
            # 槽位匹配祖先链查找
            _hit = _anc_slot_chain(cls8, _si9, None, _first9)
            if _hit:
                _bn, _baddr_int, _bnode = _hit
                _nd_me = node_of(_m9)
                _nd_base = _bnode
                if _nd_me.get('pending') or _nd_base.get('pending'):
                    continue  # 零证据诚实态不判
                # 检1: 名字一致性(override=C++同名规则, 名字不一致=silent bug)
                # [槽名优先 2026-11-16] 每槽一名: 折叠载体一址多槽名时, 槽名(vtable slot
                # name字段)=链律真承载, methods名(址级语义名)仅回退 — CEffObj 0x401800
                # 四槽四名(DestroyEffect/RenderScenePass/Destroy/UpdateParticles)实证
                _my_slotnm = (_my_slot_names.get(_si9) or '') or _n9
                _base_nm = (_pre_slot_names.get(_bn, {}).get(_si9) or '') or (_nd_base.get('name') or '')
                _my_nm = _my_slotnm
                if _my_nm != _base_nm:
                    cur_viol['C9:%s:%s:name' % (cls8, _a9)] = (
                        '%s slot%d 名字与基类不一致: 本=%s(%s) 基=%s(%s) → 折叠载体名≠链律名, 语义名需定谳' % (
                            cls8, _si9, _my_nm, _a9[-8:], _base_nm, '%08x' % _baddr_int))
                # 检2: 签名一致性(重载正确性判定 2026-11-16: cc+参数序列+返回型+varargs逐维报告)
                # [折叠载体基锚错位跳过 2026-11-17] 基条目名≠槽链名(如0x4af760=
                # UpdateFrame条目被Update槽链引用)时, 条目签名属他链(UpdateFrame void(float))
                # 非本链(Update BOOL(int))真值——比较错位签名=假信号; 链名状态由检1独立报告
                _base_entry_nm = str(_nd_base.get('name') or '').split('::')[-1]
                _sig_cmp_ok = (_base_entry_nm == _base_nm) or (_base_nm == _base_entry_nm)
                if not _sig_cmp_ok and _base_nm:
                    pass  # 错位: 跳过sig检(名检已报)
                else:
                    _oc = override_check(_nd_me, _nd_base)
                    if not _oc.get('pending') and not _oc['compatible']:
                        cur_viol['C9:%s:%s:sig' % (cls8, _a9)] = (
                            '%s %s 签名与基类不一致: %s; 本=%s 基=%s → C2555前置; '
                            '取证=两侧函数体出口eax+调用点消费' % (
                                cls8, _n9, '; '.join(_oc['mismatches']),
                                render(_nd_me), render(_nd_base)))

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
            sig = sm_text(m)
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
    # [C10 2026-11-16 用户裁定] 布局一致性门禁: 内存计算规则
    #   尺寸表: 标量(int/BOOL/DWORD/float=4, BYTE/char/bool=1, WORD/short=2, double=8);
    #   指针=4; 数组T[N]=size(T)*N; 类类型=该类注解binary_size(递归, 未知=诚实跳过)。
    #   C10a 基区重叠: bases声明的基类子对象区[offset, offset+S_B)内不得有known_member
    #     (RoleCameraCtrl实证: bases=[UIWnd@0,S=68]但成员@+8起 → apply推68字节基对象
    #      压毁UDT → get_size=-1 → CG_Scene跨引用断链)
    #   C10b 越界: 成员末端 > binary_size
    #   C10c 成员互叠: 非union类内可计算尺寸成员互相重叠 (union类豁免)
    _SCALAR10 = {'int': 4, 'unsigned int': 4, 'bool': 1, 'BOOL': 4, 'long': 4,
                 'unsigned long': 4, 'DWORD': 4, 'LONG': 4, 'UINT': 4, 'float': 4,
                 'BYTE': 1, 'char': 1, 'unsigned char': 1, 'WORD': 2, 'short': 2,
                 'unsigned short': 2, 'double': 8, 'HANDLE': 4, 'HWND': 4,
                 'HINSTANCE': 4, 'HCURSOR': 4}
    _sizes10 = {}
    for _fp10 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        try:
            _d10 = json.load(open(_fp10, encoding='utf-8'))
        except Exception:
            continue
        _bs10 = _d10.get('binary_size')
        if isinstance(_bs10, int) and _bs10 > 0:
            _sizes10[os.path.basename(_fp10)[:-5]] = _bs10

    def _tsize10(t, _depth=0):
        if _depth > 6 or not t:
            return None
        t = str(t).strip()
        if t.endswith('*'):
            return 4
        _m10 = re.match(r'^(.+?)\[(\d+)\]$', t)
        if _m10:
            _e10 = _tsize10(_m10.group(1).strip(), _depth + 1)
            return _e10 * int(_m10.group(2)) if _e10 is not None else None
        if t in _SCALAR10:
            return _SCALAR10[t]
        return _sizes10.get(t)

    for _fp10 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        _cls10 = os.path.basename(_fp10)[:-5]
        try:
            _d10 = json.load(open(_fp10, encoding='utf-8'))
        except Exception:
            continue
        _km10 = _d10.get('known_members') or {}
        _mem10 = []
        for _k10, _v10 in _km10.items():
            try:
                _o10 = int(str(_k10).split('_')[0], 16)
            except (ValueError, TypeError):
                continue
            _mem10.append((_o10, _v10.get('name'), _v10.get('type')))
        _mem10.sort()
        # C10a
        for _b10 in (_d10.get('bases') or []):
            _bn10 = _b10.get('name') if isinstance(_b10, dict) else _b10
            _bo10 = _b10.get('offset', 0) if isinstance(_b10, dict) else 0
            _sb10 = _sizes10.get(_bn10)
            if _sb10 is None:
                continue
            for _o10, _nm10, _t10 in _mem10:
                if _bo10 <= _o10 < _bo10 + _sb10:
                    errors.append('CANON:C10:%s:%s:a %s.%s@+%d 落入基类%s子对象区[%d,%d) — 布局冲突'
                                  % (_cls10, _nm10, _cls10, _nm10, _o10, _bn10, _bo10, _bo10 + _sb10))
        _bs10c = _d10.get('binary_size')
        if not (isinstance(_bs10c, int) and _bs10c > 0):
            continue
        # C10b
        for _o10, _nm10, _t10 in _mem10:
            _sz10 = _tsize10(_t10)
            if _sz10 is not None and _o10 + _sz10 > _bs10c:
                errors.append('CANON:C10:%s:%s:b %s.%s@+%d(size %d) 末端%d > binary_size %d — 越界'
                              % (_cls10, _nm10, _cls10, _nm10, _o10, _sz10, _o10 + _sz10, _bs10c))
        # C10c (union豁免)
        if _d10.get('is_union'):
            continue
        _prev10 = None
        for _o10, _nm10, _t10 in _mem10:
            _sz10 = _tsize10(_t10)
            if _sz10 is None:
                continue
            if _prev10 and _o10 < _prev10[0] + _prev10[1]:
                errors.append('CANON:C10:%s:%s:c %s.%s@+%d 与 %s@+%d(size %d) 重叠(非union) — 布局冲突'
                              % (_cls10, _nm10, _cls10, _nm10, _o10, _prev10[2], _prev10[0], _prev10[1]))
            _prev10 = (_o10, _sz10, _nm10)
    # [C11 2026-11-17 复核P0教训] bases变更棘轮门禁: bases声明只能随ctor/dtor链
    #   证据变更(4例P0误摘教训: "未找到"证无效, 继承定谳必须基构造直调+双方存表律)。
    #   快照=批准态; 与快照不符的类必须落 bases_adjudications.json 条目
    #   (含ctor_evidence/dtor_evidence), 否则硬错拒绝。
    _snap_path = os.path.join(root, 'data', 'status', 'bases_snapshot.json')
    _adj_path = os.path.join(root, 'data', 'status', 'bases_adjudications.json')
    try:
        _snap11 = json.load(open(_snap_path, encoding='utf-8')).get('snapshot') or {}
    except Exception:
        _snap11 = None  # 快照缺失=门禁未初始化, 不拦(初始化由脚本落)
    if _snap11 is not None:
        try:
            _adj11 = json.load(open(_adj_path, encoding='utf-8')) or {}
        except Exception:
            _adj11 = {}
        for _fp11 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
            _cls11 = os.path.basename(_fp11)[:-5]
            try:
                _d11 = json.load(open(_fp11, encoding='utf-8'))
            except Exception:
                continue
            _cur11 = [(b.get('name') if isinstance(b, dict) else b)
                      for b in (_d11.get('bases') or [])]
            if _cur11 != (_snap11.get(_cls11) or []):
                _a11 = _adj11.get(_cls11) or {}
                if not _a11.get('ctor_evidence'):
                    errors.append(
                        'CANON:C11:%s bases变更无裁决条目: 快照%s → 现%s; '
                        '须落 data/status/bases_adjudications.json (ctor_evidence=基构造直调地址链)'
                        % (_cls11, _snap11.get(_cls11), _cur11))
    # [N13 2026-11-17 S2崩盘教训] 跨层名字契约门(三层子检):
    #   (a) 字段契约: 语料函数(类由name字段定)的 ->M 引用必须∈类链known_members名
    #       (抓CCCTData/C2227族——引用了注解没有的字段)
    #   (b) 发射路由契约: 注解methods条目若被语料以C::M(引用, 必须有发射路由
    #       (语料按址文件 ∨ known_methods), 否则头文件不声明→C2039
    #       (抓NullCallback族: 0x408bd0条目在methods但无语料文件且known_methods空)
    #   (c) 限定调用契约: 语料C::M(引用的M必须∈注解methods名∪语料归属名
    #       (抓改名断链: cpp调旧名, 注解已正名)
    _re_arrow = re.compile(r'this\s*->\s*([A-Za-z_]\w*)')  # [精度修正] 仅this锚定箭头
    _struct_names = set()
    for _fp13 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        _struct_names.add(os.path.basename(_fp13)[:-5])
    _re_qual = re.compile(r'\b([A-Za-z_]\w*)::([A-Za-z_]\w*)\s*\(')
    # 语料装载: (类名, 函数名, body) + 按址文件存在性
    _corpus_fn = []
    _corpus_addrs = set()
    for _fp13 in sorted(_glob.glob(os.path.join(root, 'asm', 'pal3', 'decomp', '*.json'))):
        try:
            _dd = json.load(open(_fp13, encoding='utf-8'))
        except Exception:
            continue
        _nm13 = str(_dd.get('name') or '')
        _corpus_addrs.add(str(_dd.get('address') or '').lower())
        if '::' in _nm13:
            _cp, _mp = _nm13.split('::', 1)
            _corpus_fn.append((_cp.strip(), _mp.split('(')[0].strip(), _dd.get('decompiled_c') or ''))
    # (a) 字段契约
    _kmnames = {}
    def _chain_km(cls):
        if cls in _kmnames:
            return _kmnames[cls]
        names = set()
        _seen13 = set()
        _queue13 = [cls]
        # [修正 2026-11-18] 全基遍历(原 bases[0] 单链走不到 MI 二基——
        # CEffObj@0 + CTaskTpl_tagEffTaskParam_X@12 双基布局, m_fCurTime 等模板
        # 字段在二基, 单链误报 N13a×77)。语义=C++ 成员查找搜全部直接基。
        while _queue13:
            _cur = _queue13.pop(0)
            if not _cur or _cur in _seen13:
                continue
            _seen13.add(_cur)
            try:
                _dd = json.load(open(os.path.join(root, 'data', 'annotations', 'structs', '%s.json' % _cur), encoding='utf-8'))
            except Exception:
                continue
            for _v13 in (_dd.get('known_members') or {}).values():
                _n13 = _v13.get('name')
                if _n13:
                    names.add(str(_n13))
            for _b13 in (_dd.get('bases') or []):
                _bn13 = _b13.get('name') if isinstance(_b13, dict) else _b13
                if _bn13:
                    _queue13.append(_bn13)
        _kmnames[cls] = names
        return names
    _field_miss = {}
    for _cp13, _mp13, _body13 in _corpus_fn:
        for _m13 in _re_arrow.findall(_body13):
            # [精度] 基类子对象访问记法(this->基类名.字段)豁免——箭头目标=类名
            if _m13 in _struct_names:
                continue
            if _m13 not in _chain_km(_cp13) and _m13 not in ('m_pData',):
                _field_miss.setdefault((_cp13, _m13), 0)
                _field_miss[(_cp13, _m13)] += 1
    for (_c13, _m13), _n13 in sorted(_field_miss.items()):
        errors.append('DATA:N13a:%s::%s 字段契约断(语料->引用%d次, 类链known_members无名) '
                      '→ C2227族预测' % (_c13, _m13, _n13))
    # (b) 发射路由契约
    _cpp_qualified = set()
    for _cp13, _mp13, _body13 in _corpus_fn:
        for _q13 in _re_qual.findall(_body13):
            _cpp_qualified.add((_q13[0], _q13[1]))
    _emit_miss = []
    for _fp13 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        _cls13 = os.path.basename(_fp13)[:-5]
        try:
            _dd = json.load(open(_fp13, encoding='utf-8'))
        except Exception:
            continue
        _has_km = bool(_dd.get('known_methods'))
        for _a13, _e13 in (_dd.get('methods') or {}).items():
            _n13 = str(_e13.get('name') or '').split('::')[-1]
            if not _n13 or _n13.startswith('~') or '_scalar_dtor' in _n13 or '_sdtor' in _n13:
                continue
            # [路由更新 2026-11-17] name-aware skip落地后: methods条目经ida_structs
            # (apply透传)进methods循环即发射(折叠别名放行) → 路由已通; 残条件仅查
            # ida_structs缺条目(apply未跑/漂移) → 降级WARN
            if (_cls13, _n13) in _cpp_qualified and _a13.lower() not in _corpus_addrs and not _has_km:
                _ann_has = bool(_dd.get('methods', {}).get(_a13))
                if _ann_has:
                    warnings.append('N13b:%s::%s@%s 发射路由=注解methods直通(依赖apply新鲜度)' % (_cls13, _n13, _a13))
                else:
                    _emit_miss.append((_cls13, _n13, _a13))
    for _c13, _n13, _a13 in _emit_miss[:20]:
        errors.append('DATA:N13b:%s::%s@%s 发射路由断(语料引用但无按址文件且known_methods空) '
                      '→ C2039族预测' % (_c13, _n13, _a13))
    # (c) 限定调用契约
    _meth_names = {}
    for _fp13 in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        _cls13 = os.path.basename(_fp13)[:-5]
        try:
            _dd = json.load(open(_fp13, encoding='utf-8'))
        except Exception:
            continue
        _names13 = set()
        for _e13 in (_dd.get('methods') or {}).values():
            _n13 = str(_e13.get('name') or '').split('::')[-1]
            if _n13:
                _names13.add(_n13)
        _meth_names[_cls13] = _names13
    # [导入引擎头族声明源 20261120] include/gbengine/*.h 已重建的导入类头=方法
    # 声明真值源之一(gbengine.dll 方法体在 DLL, PAL3 侧声明由头族承载)。
    # N13c 预测职责="会编译失败"——头族已声明⇒预测失准(probe 实测 0 gbXxx
    # C2065/C2039 兑现, 语料态A→B 渲染面变化使 _corpus_owned 豁免丢失后显形)。
    # 判据消费已有产物(头族), 非发明。
    _gbeng_dir = os.path.join(root, 'include', 'gbengine')
    if os.path.isdir(_gbeng_dir):
        for _gh in sorted(_glob.glob(os.path.join(_gbeng_dir, '*.h'))):
            try:
                _gtxt = open(_gh, encoding='utf-8', errors='replace').read()
            except Exception:
                continue
            for _cm in re.finditer(r'(?:class|struct)\s+(?:\w+\s+)?(\w+)\s*(?::[^{]*)?\{([\s\S]*?)\n\};', _gtxt, re.S):
                _gcls, _gbody = _cm.group(1), _cm.group(2)
                _gnames = set(re.findall(r'([~A-Za-z_]\w*)\s*\(', _gbody))
                _gnames -= {'if', 'for', 'while', 'switch', 'sizeof', 'return', 'catch'}
                if _gcls in _meth_names:
                    _meth_names[_gcls] |= _gnames
                else:
                    _meth_names[_gcls] = _gnames
    _call_miss = {}
    _corpus_owned = set()
    for _cp13, _mp13, _body13 in _corpus_fn:
        _corpus_owned.add((_cp13, _mp13))
    for (_c13, _m13) in sorted(_cpp_qualified):
        if _c13.startswith('std::') or _c13 == 'std':
            continue  # [CRT 内部 20261120] std::_Xlen/_Xran=VC6 <xstring> 自带声明, 预测不成立
        if _c13 in _meth_names and _m13 not in _meth_names[_c13] and (_c13, _m13) not in _corpus_owned:
            _call_miss[(_c13, _m13)] = _call_miss.get((_c13, _m13), 0) + 1
    for (_c13, _m13), _n13 in sorted(_call_miss.items())[:20]:
        errors.append('DATA:N13c:%s::%s 限定调用契约断(语料引用但注解methods与语料归属皆无名) '
                      '→ C2039/C2065族预测' % (_c13, _m13))
    # [N14 2026-11-17] 引用类型存在性门: 语料C::前缀类型必须有注解建档
    _type_miss = collections.Counter() if False else {}
    import collections as _coll14
    _type_miss = _coll14.Counter()
    for (_c13, _m13) in _cpp_qualified:
        if _c13 in _struct_names or _c13.startswith(('gb', 'j_')) or _c13 in (
                'std', 'HANDLE', 'HWND', 'string', 'wstring', 'vector', 'map', 'list',
                'deque', 'set', 'pair', 'allocator', 'codecvt', 'codecvt_base',
                'char_traits', 'basic_string', 'istream', 'ostream', 'iostream',
                'fstream', 'sstream', 'basic_ostream', 'basic_istream', 'locale',
                'ctype', 'num_put', 'num_get', 'basic_filebuf', 'int_char',
                'HANDLE', 'tagRECT', 'tagPOINT'):
            continue
        _type_miss[_c13] += 1
    for _t13, _n13 in _type_miss.most_common(15):
        errors.append('DATA:N14:%s 引用类型无建档(语料限定前缀%d次) → C2061族预测' % (_t13, _n13))
    # [N11s 2026-11-16 用户裁定] structs注解键形门禁: 不合法十六进制全ban。
    #   地址键 ^0x[0-9a-f]{8}$ 小写8位(external+external:true=合法豁免);
    #   known_members键 ^0x[0-9a-f]+(_N)?$ 偏移小写hex。
    #   病灶: 大小写/短形/0X前缀混用531+处, apply字符串查找静默miss
    #   (RoleCameraCtrl空壳断链实证); 门禁与消费方地址相等语义必须一致。
    _re_addr8 = re.compile(r'^0x[0-9a-f]{8}$')
    _re_offhex = re.compile(r'^0x[0-9a-f]+(_[0-9]+)?$')
    for _fp11s in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        _cls11s = os.path.basename(_fp11s)[:-5]
        try:
            _d11s = json.load(open(_fp11s, encoding='utf-8'))
        except Exception:
            continue
        for _k11s in (_d11s.get('methods') or {}):
            if not _re_addr8.match(_k11s):
                errors.append('DATA:N11s:%s methods键非规范形(须0x+8位小写hex): %r'
                              % (_cls11s, _k11s))
        for _vt11s in (_d11s.get('vtables') or []):
            _a11s = _vt11s.get('addr')
            if (_a11s and _a11s != 'external'
                    and not _re_addr8.match(str(_a11s))):
                errors.append('DATA:N11s:%s vtable表址非规范形: %r' % (_cls11s, _a11s))
            for _s11s in (_vt11s.get('slots') or []):
                _sa11s = _s11s.get('addr')
                if (_sa11s and _sa11s != 'external'
                        and not _re_addr8.match(str(_sa11s))):
                    errors.append('DATA:N11s:%s 槽址非规范形: %r' % (_cls11s, _sa11s))
        for _k11s in (_d11s.get('known_members') or {}):
            if not _re_offhex.match(str(_k11s)):
                errors.append('DATA:N11s:%s known_members键非规范hex形: %r'
                              % (_cls11s, _k11s))
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


def _n20_scan(cls_forms, s4_rows):
    """[N20 纯函数核] (cls_forms, s4_rows) → (errors, warnings)。活性单测入口。

    cls_forms: cls → {'del': [{'addr','suppressed'}], 'comp': [...]}
    s4_rows: symbol → row(含 va/status)
    判据精化(VA级): 压制地址 == L1 符号 va 才断载体
    (Role 多删除式兄弟案: ??_G 载体由 VA 对应条目承担, 兄弟压制无害)。
    """
    errors, warnings = [], []
    # 符号 → (cls, kind, va) 索引: 仅 match_L1 行
    l1_by_cls = {}   # cls -> set of (kind, va_norm)
    for s, r in s4_rows.items():
        if r.get('status') != 'match_L1':
            continue
        m = re.match(r'^\?\?(_G|1)([A-Za-z_][\w]*)@@', s)
        if not m:
            continue
        kind = 'del' if m.group(1) == '_G' else 'comp'
        l1_by_cls.setdefault(m.group(2), set()).add((kind, r.get('va')))

    def _norm(a):
        try:
            return '0x%08X' % int(str(a), 16)
        except (ValueError, TypeError):
            return a

    for cls, recs in cls_forms.items():
        l1set = l1_by_cls.get(cls) or set()
        # [O5 重校准 2026-11-22] 身份清单架构(function_identity manifest +
        # compare_pal3 O5 结构解码)下, 删除式的配对=数据层真值 join + 编译器
        # 合成——**都与语料压制无关**(实证: 33 L1 deleting 全部为压制态且
        # 100% 配对; 2 例"唯一载体压制"亦经未注解语料路径存活)。N20a 对 del
        # 降级为 advisory(载体若真死, coverage 棘轮接住); comp 压制保持 HARD
        # (定义源切断=合成消失, 真实 P0)。
        comp_alive = any(not r['suppressed'] for r in recs['comp'])
        for kind, lst in (('del', recs['del']), ('comp', recs['comp'])):
            for r in lst:
                if not r['suppressed']:
                    continue
                va = _norm(r['addr'])
                hit = [sv for kv, sv in l1set if kv == kind and sv == va]
                if not hit:
                    continue
                _msg = ("N20a[%s]:%s %s 压制态 L1 载体(注册符号 va=%s 当前 match_L1, "
                        "字节匹配=最高证据级; O5 架构下配对与压制正交"
                        % (cls, r['addr'], kind, hit[0]))
                if kind == 'del':
                    warnings.append(_msg + '——del 压制 advisory(coverage 棘轮兜底))')
                else:
                    errors.append(_msg + '; 恢复=解除declaration_only/type=skip)')
        allr = recs['del'] + recs['comp']
        if allr and all(r['suppressed'] for r in allr):
            warnings.append(
                "N20b[%s]: 类级载体全空(%d条dtor全压制) → ??1/??_G 符号双丢(债务可见)"
                % (cls, len(allr)))
        # [N20c 退役 2026-11-22] 原警告"删除式唯一形态未压制(collect 泛化跳过阻塞
        #   载体)"引用的机制已退役——S3 改革(dtor_intent 路由, collect.py D1 注释
        #   12/12 字节证据证伪旧理论)后, "类仅删除式且未压制"=deleted-form ABI
        #   **合法定义源态**(resolve_dtor_intent deleting_source body_emit=True,
        #   N18 源级化)。该数据态不再是债务, 警告退役(plan_dtor_intent_reform
        #   第145行自列此债)。扫描面扩 vtable slots(D14)由 N20a/b 的
        #   cls_forms 构建侧吸收——slot 声明型条目已入 del/comp 计数。

    # [N22 dtor 对偶闭环门 2026-11-22] 本会话深层发现的产线化:
    #   删除式存根(标准形 568bf1+E8) call@3 REL32 目标=同类完全形真址(编译器
    #   配对语义, 与名字标签无关=最硬锚定)。双向闭环:
    #   N22a 删除式→完全形: slot-verified 删除式的 call 目标必须存在同类 ~Cls
    #        complete_dtor 注解条目——缺失=完全形缺失/误名预测(本会话 24 案
    #        MULTI_CLAIM+6 误名+Actor 全为此形态)
    #   N22b 完全形→删除式锚定: complete_dtor 条目未被同类删除式 call@3 锚定
    #        =裸 claim 预测(CEffect::UpdateCallback 0x4D0DB0 案)
    # 裁决三态先例(正名/退役/暂留)逐案消费本清单, 警告聚合单条防反弹。
    import struct as _s22
    _n22_span = _exe_text_span(os.path.join(_PROJECT_ROOT, 'original', 'PAL3.exe'))
    if _n22_span:
        _tva, _tbody = _n22_span
        _STUB = b'\x56\x8b\xf1\xe8'
        # ①索引: 删除式(标准形)与其 call 目标; 完全形注解址
        _del_rows = []   # (cls, del_va, target_va, slot_verified)
        _comp_addrs = {}  # (cls) → set(va) kind=complete_dtor 且非 decl 产物
        for _sf in sorted(glob.glob(os.path.join(_PROJECT_ROOT, 'data', 'annotations',
                                                  'structs', '*.json'))):
            try:
                _sd22 = json.load(open(_sf, encoding='utf-8'))
            except Exception:
                continue
            _cn22 = _sd22.get('name') or os.path.basename(_sf)[:-5]
            for _a22, _m22 in (_sd22.get('methods') or {}).items():
                if (_m22 or {}).get('adjudication') == 'rejected':
                    continue
                _fl = _m22.get('flags') or []
                try:
                    _va = int(_a22, 16)
                except (ValueError, TypeError):
                    continue
                if 'dtor' not in _fl:
                    continue
                if 'deleting' in _fl:
                    _off = _va - _tva
                    if 0 <= _off < len(_tbody) - 30:
                        _b = _tbody[_off:_off + 30]
                        if _b[:4] == _STUB:
                            _rel = _s22.unpack('<i', _b[4:8])[0]
                            _del_rows.append((_cn22, _va, _va + 8 + _rel,
                                              _m22.get('slot_verified') is True))
                else:
                    _comp_addrs.setdefault(_cn22, set()).add(_va)

        _n22a_miss, _n22b_naked = [], []
        for _cn, _dva, _tva22, _sv in _del_rows:
            if _tva22 in _comp_addrs.get(_cn, ()):
                continue
            _n22a_miss.append({'cls': _cn, 'deleting_va': '0x%08x' % _dva,
                               'target_va': '0x%08x' % _tva22,
                               'slot_verified': _sv,
                               'predict': '该址=同类完全形真址(编译器配对), '
                                          '未注解或误名——正名/退役/暂留三态裁决'})
        # [N22b 字节证据豁免 20261122] s4_rows 配对(match_L1/partial)=该址字节已证
        #   ——锚定定义漏 adjustor/ICF 链的假阳豁免(18/42 实测)
        _paired_vas = set()
        for _r22 in s4_rows.values():
            try:
                if _r22.get('status') in ('match_L1', 'partial'):
                    _paired_vas.add(int(str(_r22.get('va')), 16))
            except (ValueError, TypeError):
                pass
        for _cn, _cset in _comp_addrs.items():
            # ②反向: 完全形注解址未被同类任一删除式锚定 → 裸 claim
            # [字节证据豁免 20261122] s4_rows 配对(match_L1/partial)=该址字节已证
            #   ——锚定定义漏 adjustor/ICF 链的假阳豁免(18/42 实测)
            _del_targets = {t for _, _, t, _ in _del_rows}
            for _cva in _cset:
                if _cva not in _del_targets and _cva not in _paired_vas:
                    _n22b_naked.append({'cls': _cn, 'va': '0x%08x' % _cva})
        if _n22a_miss or _n22b_naked:
            _wl = {'_doc': ('N22 dtor 对偶闭环工作清单 2026-11-22——三态裁决'
                            '(正名/退役/暂留)逐案消费'),
                   'n22a_complete_missing': _n22a_miss,
                   'n22b_naked_complete': _n22b_naked}
            _wl_p = os.path.join(_PROJECT_ROOT, 'data', 'status', 'n22_pair_closure.json')
            with open(_wl_p, 'w', encoding='utf-8') as _f22:
                json.dump(_wl, _f22, ensure_ascii=False, indent=1)
            warnings.append(
                'N22[dtor对偶闭环]: N22a 完全形缺失/误名 %d + N22b 裸claim %d '
                '——工作清单 data/status/n22_pair_closure.json(三态裁决逐案)'
                % (len(_n22a_miss), len(_n22b_naked)))

    return errors, warnings


def check_dtor_carrier_gate(_selftest=False):
    """[N20 dtor 载体门 2026-11-21] 压制 dtor 条目前置检出符号供给链断裂。

    方法论: docs/knowledge/methodology_dtor_governance_20261121.md
      ??_G 载体 = virtual ~Cls() 头声明(删除式条目供给) + 类内 dtor 定义 → MSVC 合成。
      对删除式条目的压制(declaration_only/type='skip')会切断 virtual 供给 → ??_G 丢失。
      12/12 实证(20261121 L1恢复战役: 03:17基线 ??_G 全部 100.0% 字节完美被 C8 批次压制蒸发)。

    三级:
      N20a HARD(errors): 压制删除式/完全形条目 且 压制地址==对应注册符号
          (??_G/??1 <Cls>@@)的 match_L1 va → 压制=切断L1载体, 必须阻断。
          (100.0% 字节匹配=最高证据级; VA级判据: Role 多删除式兄弟无害)
      N20b WARN: 类级载体全空(类内所有 dtor 条目都被压制) → ??1/??_G 双丢债务可见。
      N20c WARN: 删除式唯一形态未压制(载体被 collect backtick→_scalar_dtor 泛化跳过
          阻塞的管线限制, UIProgressBar 案) → 提示待 N18 联动通路。
    活性验证(N19协议): --selftest 走合成态断言三门触发(见 test_n20_dtor_carrier_gate)。

    返回 (errors, warnings)
    """
    import glob as _glob
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    _s4_rows = {}
    _s4p = os.path.join(root, 'data', 'status', 's4_baseline.json')
    if os.path.exists(_s4p):
        try:
            _s4_rows = {x['symbol']: x for x in
                        json.load(open(_s4p, encoding='utf-8')).get('rows', [])}
        except Exception:
            _s4_rows = {}

    cls_forms = {}
    for fp in sorted(_glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json'))):
        try:
            d = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        cls = d.get('name') or os.path.basename(fp)[:-5]
        recs = cls_forms.setdefault(cls, {'del': [], 'comp': []})
        for a, m in (d.get('methods') or {}).items():
            fl = m.get('flags') or []
            nm = str(m.get('name') or '')
            if not ('dtor' in fl or nm.startswith('~')):
                continue
            rec = {'addr': a, 'suppressed': m.get('type') == 'skip'
                   or bool(m.get('declaration_only'))}
            recs['del' if 'deleting' in fl else 'comp'].append(rec)

    errors, warnings = _n20_scan(cls_forms, _s4_rows)
    if _selftest:
        print('[N20 selftest] 现役 N20a=%d N20b=%d N20c=%d (活性单测见 test_n20)'
              % (len([e for e in errors if 'N20a' in e]),
                 sum(1 for w in warnings if 'N20b' in w),
                 sum(1 for w in warnings if 'N20c' in w)))
    return errors, warnings


if __name__ == '__main__':
    errors, warnings = check()

    # [DBCS 吞行门 2026-11-22] VC6 预处理器 DBCS 配对(lead∈[0x81,0xFE]无条件吞
    #   下一字节含\n)——头/源文件行尾配对余数=毒行, 声明被续行注释吞掉
    #   (gbMatrixStack/gbVFileSystem/gbAudio 三头 6 毒行实证: Scale(gbVec3D&)/
    #   SceneRenderWithRotation/UIPostUpdate/m_fp 声明全被吃, C2039 持续)。
    #   检查器=tools/fix_vc6_dbcs_comment_splice.py(2026-11-09 建, 但从未接入门禁
    #   ——上批补声明未跑它, 修复以死告终又被当新缺口立战役, 规模评估全程误导)。
    #   接线=HARD: 毒行存在即 FAIL, 修法=行尾补 ASCII 空格(lead 配对空格, \n 释放)。
    import subprocess as _sp_dbcs
    _dbcs = _sp_dbcs.run(
        [sys.executable, os.path.join(os.path.dirname(os.path.dirname(
            os.path.abspath(__file__))), 'tools', 'fix_vc6_dbcs_comment_splice.py'),
         '--check'],
        capture_output=True, text=True)
    if _dbcs.returncode != 0:
        for _dl in (_dbcs.stdout or '').splitlines():
            if _dl.startswith('[POISON]'):
                errors.append('DATA:DBCS-SPLICE:%s 行尾配对毒行——声明将被续行注释吞掉, '
                              '跑 tools/fix_vc6_dbcs_comment_splice.py 修复' % _dl)

    # [canonical 契约断言 2026-11-14] 四条非法态棘轮
    # [2026-11-16 吞异常拆除] except→warning曾把C9块NameError静默成PASS
    #   (门禁写了没跑过一次实证); 文件级加载错误已在块内各自守卫,
    #   此处异常=门禁自身bug, 必须炸出而非降级。
    _cc_errors, _cc_warnings = check_canonical_contract()
    errors.extend(_cc_errors)
    warnings.extend(_cc_warnings)

    # [N20 dtor 载体门 2026-11-21] 压制切断 L1 载体前置检出(HARD)+债务可见(WARN)
    #   硬纪律: 门禁必须活性验证(N19协议)——selftest 断言规则结构+当前触发数。
    _n20_errors, _n20_warnings = check_dtor_carrier_gate(_selftest=True)
    errors.extend(_n20_errors)
    warnings.extend(_n20_warnings)

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

    # [基线分账 2026-11-18 用户裁定] 台账基线错误=存量冻结(advisory), 新增=硬失败(阻断)。
    # 基线文件=上一次全绿时的errors快照; 基线不存在=全量advisory(首轮建账期)。
    _baseline_p = os.path.join(_PROJECT_ROOT, 'data', 'status', 'check_baseline_errors.json')
    _baseline_set = set()
    if os.path.exists(_baseline_p):
        try:
            _baseline_set = set(json.load(open(_baseline_p, encoding='utf-8')))
        except Exception:
            pass

    _new_errors = [e for e in errors if e not in _baseline_set]
    _frozen_errors = [e for e in errors if e in _baseline_set]

    for e in _frozen_errors:
        print(f"FROZEN: {e}")
    for e in _new_errors:
        print(f"ERROR: {e}")

    if _new_errors:
        print(f"\n{len(_new_errors)} new errors + {len(_frozen_errors)} frozen (advisory), "
              f"{len(warnings)} warnings — FAIL (新增违规阻断; 存量冻结请修后从基线移除)")
        sys.exit(1)
    else:
        _fz = (' + %d frozen(advisory)' % len(_frozen_errors)) if _frozen_errors else ''
        print(f"\n0 new errors{_fz}, {len(warnings)} warnings — PASS")
        sys.exit(0)
