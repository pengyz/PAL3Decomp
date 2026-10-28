"""[TOS 2026-10-28·C6] 签名解析件单一真相源（自 stage4_substitution 下沉——
清 stage↔stage 违例边 emit_headers→stage4；_try_struct_member_resolution 公有化
=try_struct_member_resolution）。"""
import re

from data import store

_ELEM_SIZES = {'int': 4, 'float': 4, 'unsigned int': 4, 'unsigned long': 4,
               'char': 1, 'unsigned char': 1, 'bool': 1,
               'short': 2, 'unsigned short': 2, 'double': 8, 'long long': 8}

_FPTR_PARAM_RE = re.compile(
    r'^(.*?)\(\s*__thiscall\s*\*\s*(\w*)\s*\)\s*\((.*)\)$', re.S)

_THIS_NAME_RE = re.compile(r'(?:^|\s)(?:\w+\s*\*+\s*)?(?:this|_this)$')

_ANON_PTR_ARG_RE = re.compile(r'^\w[\w\s]*\s*\*+\s*$')

def _anon_aggregate(mtype):
    """inline union/struct 递归引用形——emit_headers._keep_anonymous 同族谓词
    （2026-09-28 bDestRole/_field_C67E 双层实证：匿名聚合内层名提升，不得合成外层名）。"""
    t = (mtype or '').strip()
    return t.startswith('_inline_') or '::$' in t

def _resolve_offset(type_name, offset, prefix):
    """Recursively resolve an offset within a type to '.member' or '.member[N]'。
    2026-09-28 修（悬空渲染根因）：导出 data_members 可带 **空串 name**（匿名 union 族）
    ⇒ `'.%s' % ''` 产出 `g_SceneMgr.` 悬空。合成实名（与 emit_headers 同公式
    `_field_%04X % off` ⇒ 头文件与渲染同名一致）；**匿名聚合体豁免合成**（内层名提升）。"""
    members = store.struct_members.get(type_name, {})
    info = members.get(offset)
    if info:
        mname, mtype = info
        if not mname and not _anon_aggregate(mtype):
            mname = '_field_%04X' % offset          # 标量空名合成
        mt = mtype.strip().lower()
        if prefix == 'byte' and not any(t in mt for t in ('char', 'byte', 'bool')) and '*' not in mtype:
            pass
        elif prefix == 'word' and not any(t in mt for t in ('short', 'word', 'wchar')):
            pass
        elif prefix == 'off' and '*' not in mtype:
            pass
        elif prefix == 'flt' and 'float' not in mt:
            pass
        else:
            return ('.%s' % mname) if mname else None    # 匿名聚合无路径分量（内层名另行提升）
    for moff, (mname, mtype) in sorted(members.items(), reverse=True):
        if not mname and not _anon_aggregate(mtype):
            mname = '_field_%04X' % moff       # 标量空名合成（匿名聚合豁免，同上）
        if moff > offset:
            continue
        rel = offset - moff
        if rel == 0:
            continue
        arr_m = re.match(r'^([\w\s\*]+?)\[(\d+)\]$', mtype.strip())
        if arr_m:
            elem_type = arr_m.group(1).strip()
            arr_count = int(arr_m.group(2))
            elem_sz = _ELEM_SIZES.get(elem_type)
            if elem_sz is None:
                elem_sz = store.struct_sizes.get(elem_type, 0)
                if elem_sz == 0:
                    elem_sz = 4 if store.struct_members.get(elem_type) else 0
            if not elem_sz:
                sub_m = store.struct_members.get(elem_type)
                if sub_m:
                    elem_sz = 4
            if elem_sz and rel < arr_count * elem_sz:
                idx = rel // elem_sz
                sub_rel = rel - idx * elem_sz
                _is_primitive = elem_type in _ELEM_SIZES and not store.struct_members.get(elem_type)
                if sub_rel == 0:
                    if _is_primitive:
                        continue  # byte-level array, try structured array
                    return (('.%s[%d]' % (mname, idx)) if mname else None)   # 空名数组形态保守弃
                if not _is_primitive:
                    sub_members = store.struct_members.get(elem_type)
                    if sub_members:
                        sub = _resolve_offset(elem_type, sub_rel, prefix)
                        if sub:
                            return (('.%s[%d]%s' % (mname, idx, sub)) if mname else sub)
                if _is_primitive:
                    continue
                return (('.%s[%d]' % (mname, idx)) if mname else None)
        embedded = store.struct_members.get(mtype.strip().rstrip('*').strip())
        if embedded and '*' not in mtype:
            # Use struct's full size as threshold (not primitive default 0x1000)
            _embedded_offsets = list(embedded.keys())
            _max_off = max(_embedded_offsets) if _embedded_offsets else 0
            _struct_sz = max(rel + 1, _max_off + 4)
            if rel < _struct_sz:
                sub = _resolve_offset(mtype.strip(), rel, prefix)
                if sub:
                    return (('.%s%s' % (mname, sub)) if mname else sub)   # 匿名聚合：内层名提升直用
    return None

def rewrite_thiscall_fnptr_param(param, cls_name):
    """Rewrite one parameter spelled as a thiscall fn-ptr to member-ptr form.

    'int (__thiscall *a2)(int this, int a2)' — Hex-Rays' rendering of a
    member-pointer callback with a synthetic this argument — becomes
    'int (CLS::*a2)(int, int)'.  The callback class is the enclosing
    method's class (binary evidence: the values passed at call sites are
    methods of that same class).  VC6 cannot spell the __thiscall fn-ptr
    form at all (C4234).
    """
    text, _name, _dropped = rewrite_thiscall_fnptr_param_ex(param, cls_name)
    return text

def rewrite_thiscall_fnptr_param_ex(param, cls_name):
    """同 rewrite_thiscall_fnptr_param，另回传 (文本, 参数名, 是否剥了合成 this)。
    剥了合成 this 的名字必须由调用方继续做**直调改写**（成员指针不可直调）。"""
    m = _FPTR_PARAM_RE.match(param.strip())
    if not m:
        return param, None, False
    pre, name, inner = m.groups()
    depth = 0
    args, cur = [], ''
    for ch in inner:
        if ch in '(<':
            depth += 1
        elif ch in ')>':
            depth -= 1
        if ch == ',' and depth == 0:
            args.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        args.append(cur.strip())
    dropped = False
    if len(args) >= 2 and (_THIS_NAME_RE.search(args[0])
                           or _ANON_PTR_ARG_RE.match(args[0])):
        args = args[1:]
        dropped = True
    return ('%s(%s::*%s)(%s)' % (pre, cls_name, name or 'pFn', ', '.join(args)),
            (name or 'pFn'), dropped)

def try_struct_member_resolution(name):
    """Resolve IDA unnamed references (dword_XXXX) to struct member expressions."""
    if name.startswith('sub_'):
        return None
    try:
        addr = int(name.split('_', 1)[1], 16)
    except (ValueError, IndexError):
        return None
    if addr < 0x00401000 or addr > 0x01800000:
        return None
    prefix = name.split('_')[0]
    for base, end, gname, gtype in store.struct_instances:
        if base <= addr < end:
            offset = addr - base
            # Check for a named global at the exact address within this range.
            # If it has its own struct_instance, it's independent — use its name directly.
            # Otherwise it's a phantom — resolve as parent.member access.
            has_own_instance = any(b == addr for b, e, _, _ in store.struct_instances)
            if has_own_instance:
                for _gn, _ga in store.global_addrs.items():
                    if _ga == addr:
                        return _gn
            resolved = _resolve_offset(gtype, offset, prefix)
            if resolved:
                return '%s%s' % (gname, resolved)
    return None
