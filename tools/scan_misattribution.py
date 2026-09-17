"""扫描"归属误判"候选：**方法 M 声明属于类 C，但其 `this->member` 被当作
另一个类的对象使用**（`CalcSpeed` / `ProcessAllCmds` 那一型）。

## 判据

对 decomp 里每个方法 M（声明为 `C::M`），找形态：
    `X::Y( (X *)this->m<suffix> , ... )` 或  `X::Y( &this->m<suffix> , ... )`

其中：
  1. **P1 偏移链可解析**：`<suffix>` 是 `[k]` / `.field` / `->field` 的序列，
     且能被解析成一个**已知声明类型的对象**（数组元素大小由 `type` 里的
     声明维度推，见 `parse_decl_type`）。解析不出来 ⇒ **不出结论**。
  2. **P2 callee 访问自洽**：被调函数的 `min_required_span` 不得超过
     **它自己所属类** 的 `binary_size`。超过 ⇒ 说明 `%ecx==this` 的前提高估了
     访问需求（实测 40 处），**不出结论**。
  3. **P3 物理不可能**：`min_required_span(callee) > sizeof(链终值声明类型)`
     ⇒ 被调函数读到了声明类型之外 ⇒ 归属或成员类型有误。

## 三个曾经导致假阳性的缺陷（都已修，见 tools/test_scan_misattribution.py）

| # | 旧行为 | 后果 | 修法 |
|---|--------|------|------|
| 1 | 正则只抓 `m_\w+`，忽略 `[k]`/`.f` 后缀 | **71 个候选里 58 个（82%）** 拿 head 类型尺寸去比，算错 | `resolve_chain` 完整解析 |
| 2 | 盲目反汇编 `va..va+0x400` | `UIWnd::GetWidth`(13B) 报 need=244（实测 140）| 用 `decomp/*.json` 的 `size_bytes` 约束 |
| 3 | `%ecx` 活性判据写反（`mov %ecx,` 当成被覆盖）| callee 需求被高估 | 改成 `,%ecx`（AT&T 目标操作数）+ 先读后覆盖 |

## 用法（只读，不改任何东西）
    python3 tools/scan_misattribution.py [--limit N] [--only CLASS]
输出：候选清单（按置信度），并标注"是否物理不可能"。
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANNO = os.path.join(ROOT, 'data', 'annotations', 'structs')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')

PRIM_SIZES = {
    'void': 0, 'bool': 1, 'char': 1, 'signed': 4, 'unsigned': 4, 'uchar': 1,
    'byte': 1, '_BYTE': 1, '__int8': 1, 'short': 2, 'wchar_t': 2, '__int16': 2,
    'int': 4, 'long': 4, 'float': 4, '__int32': 4, 'DWORD': 4, '_DWORD': 4,
    'double': 8, '__int64': 8, '_QWORD': 8, 'signed': 4,
}


# ---- 类型字符串解析 ---------------------------------------------------------
def parse_decl_type(t):
    """`'SaleUI_SortData[299][5]'` -> `('SaleUI_SortData', [299, 5], False)`

    `'UIListBox *[1]'` -> `('UIListBox', [1], True)`
    `'CEffectSimple *'` -> `('CEffectSimple', [], True)`
    维度非字面量（`'Foo[n]'`）时该维为 **None**（绝不静默当 0）。

    ️ 三个真实数据里存在的坑（926 个类型串中：嵌套 `::` 41 个、模板 33 个、
    前缀关键字 15 个）：
      · `'const struct TypeDescriptor *'` —— 不剥前缀会抓出 `base='const'`；
      · `'AStarPathFinder::NODE *'` —— 抓出外层类 `AStarPathFinder`（**尺寸是错的**，
        比漏判更危险）；
      · `'std::vector<T,std::allocator<T> >'` —— 抓出 `'std'`。
    模板/嵌套名在 structs 里没有对应条目 ⇒ 一律返回 `base=None`（保守拒答），
    绝不用外层类冒充。
    """
    t = (t or '').strip()
    dims = []
    while t.endswith(']'):
        i = t.rfind('[')
        if i < 0:
            break
        inner = t[i + 1:-1].strip()
        dims.insert(0, int(inner) if inner.isdigit() else None)
        t = t[:i].strip()
    ptr = False
    while t.endswith('*'):
        ptr = True
        t = t[:-1].strip()
    for kw in ('const', 'volatile', 'struct', 'class', 'enum', 'union'):
        t = re.sub(r'\b%s\b\s*' % kw, '', t).strip()
    if '::' in t or '<' in t:
        # 嵌套 / 模板类型名：structs 里查不到，宁可拒答也不用外层类冒充
        return None, dims, ptr
    m = re.search(r'([A-Za-z_]\w*)', t)
    return (m.group(1) if m else None), dims, ptr


def sizeof_type(S, t):
    """声明类型**作为存储**占多少字节（数组 = 各维乘积 × 基类型；指针 = 4）。

    None = 未知。注意指针必须先判：`'std::vector<...> *'` 的基名查不到，
    但指针本身恒为 4 字节。
    """
    base, dims, ptr = parse_decl_type(t)
    if ptr:
        return 4
    if base is None:
        return None
    n = 1
    for d in dims:
        if d is None:
            return None          # 维度未知 ⇒ 尺寸未知
        n *= d
    if base in PRIM_SIZES:
        return n * PRIM_SIZES[base]
    sz = (S.get(base) or {}).get('size')
    return None if sz is None else n * sz


def strip_scalar(S, t):
    """该声明类型是否是标量（标量尺寸不能和"callee 需要多少字节"比）。"""
    base, dims, ptr = parse_decl_type(t)
    return (not dims) and (not ptr) and base in PRIM_SIZES


# ---- 数据加载 ---------------------------------------------------------------
def load_structs():
    """name -> {'size','members':{mname:(off,type)},'methods':{VA:{name,sig}}}"""
    out = {}
    for p in glob.glob(os.path.join(ANNO, '*.json')):
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        n = d.get('name')
        if not n:
            continue
        offs = {}
        for k, m in (d.get('known_members') or {}).items():
            try:
                off = int(k, 16) if k.lower().startswith('0x') or not k.isdigit() else int(k)
            except Exception:
                continue
            offs[(m or {}).get('name')] = (off, str((m or {}).get('type') or ''))
        meths = {}
        for k, m in (d.get('methods') or {}).items():
            meths[k.upper()] = {'name': (m or {}).get('name'),
                                'sig': str((m or {}).get('signature') or '')}
        out[n] = {'size': d.get('binary_size'), 'members': offs, 'methods': meths,
                  'bases': list(d.get('base_class') or [])}
    return out


def norm_va(s):
    """VA 归一化：`'0X004F3D90'` / `'0x4f3d90'` / `'4F3D90'` -> `0x4F3D90`(int)。

    ⚠️ 绝不能用 `.lstrip('0X')`：它按**字符集**剥离，`'0X004F3D90'` 会变成
    `'4F3D90'`（连前导 `0` 一起吃掉）⇒ 查表永远失败。
    """
    if isinstance(s, int):
        return s
    t = (s or '').strip().upper()
    if t.startswith('0X'):
        t = t[2:]
    try:
        return int(t, 16)
    except Exception:
        return None


FUNC_SIZE = {}
FUNC_CODE = {}


def load_decomp():
    """VA(hex upper, no 0x) -> (name, code)"""
    out = {}
    for p in glob.glob(os.path.join(DECOMP, '*.json')):
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        a = (d.get('address') or '').upper().replace('0X', '')
        if not a:
            continue
        out[a] = ((d.get('name') or ''), (d.get('decompiled_c') or ''))
        try:
            FUNC_SIZE[norm_va(a)] = int(d.get('size_bytes') or 0)
        except Exception:
            FUNC_SIZE[norm_va(a)] = 0
    return out


# ---- 偏移链解析 -------------------------------------------------------------
_STEP_RE = re.compile(r'\[\s*([^\]]*?)\s*\]|->\s*([A-Za-z_]\w*)|\.\s*([A-Za-z_]\w*)')


def _int_literal(expr):
    """`'3'` -> 3；`'0x10'` -> 16；`'38 * v36 + 3'` -> None"""
    expr = (expr or '').strip()
    try:
        if expr.lower().startswith('0x'):
            return int(expr, 16)
        if re.fullmatch(r'\d+', expr):
            return int(expr)
        if re.fullmatch(r'-\d+', expr):
            return int(expr)
    except Exception:
        pass
    return None


def resolve_chain(S, cls, mem, suffix, amp):
    """解析 `this->mem<suffix>`，返回链终值对象的声明类型、尺寸与常量偏移。

    返回 dict：
      status    ok | unknown_member | scalar_as_ptr | addr_of_pointer |
                unknown_field | not_an_array
      obj_type  链终值对象的声明基类型（None = 不可知）
      obj_size  对应字节数（None = 不可知 ⇒ 不得出结论）
      off       相对声明类起始的常量偏移（None = 动态下标或已跨指针）
      via_deref 是否经由指针间接（决定 off 是否还是"相对 this"）
    """
    info = _find_member(S, cls, mem)
    if not info:
        return {'status': 'unknown_member', 'obj_type': None, 'obj_size': None,
                'off': None, 'via_deref': False}
    off, decl = info
    base, dims, ptr = parse_decl_type(decl)

    if not amp:
        # `this->m` 作为地址用：值的来源是指针（或整数里存的地址）
        if not ptr and not dims and base in PRIM_SIZES:
            return {'status': 'scalar_as_ptr', 'obj_type': None, 'obj_size': None,
                    'off': None, 'via_deref': True}
        state = {'base': base, 'dims': list(dims), 'ptr': ptr,
                 'off': None, 'via_deref': True}
    else:
        if ptr:
            # &this->p 是"指针槽本身的地址"，不是对象地址 ⇒ 无尺寸信号
            return {'status': 'addr_of_pointer', 'obj_type': None, 'obj_size': None,
                    'off': None, 'via_deref': False}
        state = {'base': base, 'dims': list(dims), 'ptr': False,
                 'off': off, 'via_deref': False}

    for mm in _STEP_RE.finditer(suffix or ''):
        idx_expr, arrow, field = mm.groups()
        if idx_expr is not None:
            k = _int_literal(idx_expr)
            if state['dims']:
                elem_dims = state['dims'][1:]
                elem_sz = _elem_size(S, state['base'], elem_dims, state['ptr'])
                if state['off'] is not None and k is not None and elem_sz is not None:
                    state['off'] += k * elem_sz
                else:
                    state['off'] = None
                state['dims'] = elem_dims
            else:
                # 非数组：当指针下标看待（this->p[k]），步长 = 指向对象的尺寸
                elem_sz = _elem_size(S, state['base'], [], False)
                if state['off'] is not None and k is not None and elem_sz is not None:
                    state['off'] += k * elem_sz
                else:
                    state['off'] = None
                state['via_deref'] = True
        elif arrow is not None:
            tgt = state['base']
            if not tgt or tgt not in S:
                return {'status': 'unknown_field', 'obj_type': None,
                        'obj_size': None, 'off': None, 'via_deref': True}
            # ️ `_STEP_RE` 的三组是 (下标, `->`字段, `.`字段)：
            # `->` 分支必须用 `arrow`，不是 `field`（写成 field 会拿到 None ⇒
            # 所有 `->` 链都被误判成 unknown_field）。
            fi = _find_member(S, tgt, arrow)
            if not fi:
                return {'status': 'unknown_field', 'obj_type': None,
                        'obj_size': None, 'off': None, 'via_deref': True}
            foff, fdecl = fi
            fb, fd, fp = parse_decl_type(fdecl)
            state = {'base': fb, 'dims': fd, 'ptr': fp,
                     'off': None, 'via_deref': True}
        else:
            cur = state['base']
            # 若当前是数组，字段访问作用在元素上
            if cur not in S:
                return {'status': 'unknown_field', 'obj_type': None,
                        'obj_size': None, 'off': None, 'via_deref': state['via_deref']}
            fi = _find_member(S, cur, field)
            if not fi:
                return {'status': 'unknown_field', 'obj_type': None,
                        'obj_size': None, 'off': None, 'via_deref': state['via_deref']}
            foff, fdecl = fi
            if state['off'] is not None:
                state['off'] += foff
            fb, fd, fp = parse_decl_type(fdecl)
            state['base'] = fb
            state['dims'] = fd
            state['ptr'] = fp

    # 终值对象尺寸：数组整体（若还有维度）或基类型
    if state['base'] is None:
        return {'status': 'unknown_field', 'obj_type': None, 'obj_size': None,
                'off': state['off'], 'via_deref': state['via_deref']}
    if state['dims']:
        sz = _elem_size(S, state['base'], state['dims'], state['ptr'])
    elif state['ptr']:
        sz = (S.get(state['base']) or {}).get('size')
    else:
        sz = _dims_size(S, state['base'], [])
    return {'status': 'ok', 'obj_type': state['base'], 'obj_size': sz,
            'off': state['off'], 'via_deref': state['via_deref'],
            'dims': state['dims'], 'ptr': state['ptr']}


def _find_member(S, cls, field, _depth=0):
    """在 `cls` 及其**主基类**链上找成员，返回 `(off, decl_type)` 或 None。

    ⚠️ 只沿 `bases[0]` 递归：C++/MSVC 里主基类子对象位于偏移 0，所以基类成员的
    偏移可直接沿用。**次要基类（`bases[1:]`）的偏移未知，绝不猜**（多继承时
    非主基类不在 0 偏移）。

    这条是独立复核抓出的缺陷：`UIStatic` 的 `.m_bcreateok` 实际定义在基类
    `UIWnd`，只查 `S[cls]['members']` 会把这类访问整片误判成 `unknown_field`
    而拒答（实测 311 个 `unknown_field` 里绝大多数属此）。
    """
    if not cls or _depth > 8:
        return None
    info = S.get(cls)
    if not info:
        return None
    got = (info.get('members') or {}).get(field)
    if got:
        return got
    bases = info.get('bases') or []
    if not bases:
        return None
    return _find_member(S, bases[0], field, _depth + 1)


def _elem_size(S, base, dims_after, ptr):
    """按声明 `base<dims_after>` 求**一个元素**的字节数。

    ⚠️ 指针数组（`_PlugInfo *[10]`）每元素是 **4 字节的指针**，
    绝不是 `sizeof(_PlugInfo)`。搞错会让整个下标链偏移爆炸
    （实测：`m_scrollbar.m_texarrayInfo[4]` 解析成 2676，真值 356）。
    """
    n = 1
    for d in dims_after:
        if d is None:
            return None
        n *= d
    if ptr:
        return 4 * n
    b = PRIM_SIZES.get(base) if base in PRIM_SIZES else (S.get(base) or {}).get('size')
    return None if b is None else n * b


def _dims_size(S, base, dims):
    if base is None:
        return None
    if not dims:
        if base in PRIM_SIZES:
            return PRIM_SIZES[base]
        return (S.get(base) or {}).get('size')
    n = 1
    for d in dims:
        if d is None:
            return None
        n *= d
    b = PRIM_SIZES.get(base) if base in PRIM_SIZES else (S.get(base) or {}).get('size')
    return None if b is None else n * b


# ---- 被调函数的"最小访问需求" ----------------------------------------------
_REQ_CACHE = {}


def _objdump(va, end):
    try:
        return subprocess.run(['objdump', '-d', '--start-address=%d' % va,
                               '--stop-address=%d' % end, EXE],
                              capture_output=True, text=True, timeout=30).stdout
    except Exception:
        return ''


def min_required_span(va_hex, depth=0):
    """反汇编整个函数体（**按 size_bytes 界定**），返回入口 `this` 被访问的
    最大偏移 + 4（近似"最小所需尺寸"）。

    只统计**入口 this 寄存器**（`__thiscall` 的 `%ecx`）的访问：
      · AT&T 里 `, %ecx` 表示 ecx 是目标操作数 ⇒ 该指令执行后 ecx 不再是 this；
      · **先算本指令的读，再判覆盖**（`mov 0x8(%ecx),%ecx` 的读必须算进去）；
      · 遇到 `ret` 立即停止（不越界到下一个函数）。
    va 不是 `__thiscall`、或没有 `size_bytes` ⇒ 返回 None（**不出结论**）。
    """
    va_hex = norm_va(va_hex)
    if va_hex in _REQ_CACHE:
        return _REQ_CACHE[va_hex]
    if va_hex is None:
        return None
    va = va_hex
    size = FUNC_SIZE.get(va, 0)
    if size <= 0:
        _REQ_CACHE[va] = None
        return None
    out = _objdump(va, va + size)
    # 跳转 thunk：整函数只有一条 jmp ⇒ 跟随
    tgt = re.search(r'^\s*[0-9a-f]+:\s+[0-9a-f ]+\s+jmp\s+([0-9a-f]+)', out, re.M)
    if tgt and depth < 3:
        r = min_required_span(tgt.group(1), depth + 1)
        _REQ_CACHE[va] = r
        return r

    req = 0
    live = True
    for line in out.splitlines():
        if not re.match(r'\s+[0-9a-f]+:', line):
            continue
        body = line.split(':', 1)[1] if ':' in line else line
        if re.search(r'\bret\b', body):
            break
        if live:
            m = re.search(r'0x([0-9a-f]+)\(' + re.escape('%ecx') +
                          r'(?:,([0-9a-f]+),([0-9a-f]))?\)', body)
            if m:
                req = max(req, int(m.group(1), 16))
        # 覆盖检测：`, %ecx` ⇒ ecx 是目标操作数；`pop %ecx`
        if re.search(r',\s*%ecx\b', body) or re.search(r'\bpop\s+%ecx\b', body):
            live = False
    _REQ_CACHE[va] = (req + 4) if req else None
    return _REQ_CACHE[va]


# ---- 主流程 -----------------------------------------------------------------
PAT = re.compile(
    r'(\w+)::(\w+)\(\s*(?:\(\s*(\w+)\s*\*\s*\)\s*)?'
    r'(&?)this->(m_\w+)((?:\[[^\]]*\]|\.\s*[A-Za-z_]\w*|->\s*[A-Za-z_]\w*)*)')


def scan(S, D):
    cand = []
    for va, (nm, code) in D.items():
        if '::' not in nm or not code:
            continue
        cls = nm.split('::')[0]
        for mm in PAT.finditer(code):
            called_cls, called_m, cast_cls, amp, mem, suffix = mm.groups()
            if not _find_member(S, cls, mem):
                continue
            r = resolve_chain(S, cls, mem, suffix or '', amp == '&')
            tgt = cast_cls or called_cls
            head_decl = _find_member(S, cls, mem)[1]
            head_base, _hd, _hp = parse_decl_type(head_decl)
            callee_va = None
            for k, v in (S.get(tgt, {}).get('methods') or {}).items():
                if v.get('name') == called_m:
                    callee_va = k
                    break
            sig = ''
            if callee_va:
                sig = (S.get(tgt, {}).get('methods') or {})[callee_va].get('sig') or ''
            need = None
            if callee_va and '__thiscall' in sig:
                need = min_required_span(callee_va)
            callee_sz = (S.get(tgt) or {}).get('size')
            self_overflow = (need is not None and callee_sz is not None
                             and need > callee_sz)
            osz = r['obj_size']
            impossible = bool(r['status'] == 'ok' and osz is not None
                              and need is not None and need > osz
                              and not self_overflow)
            cand.append({
                'method_va': va, 'method': nm, 'member': mem,
                'member_suffix': suffix or '',
                'member_off': r['off'],
                'chain_status': r['status'],
                'via_deref': r['via_deref'],
                'head_decl_type': head_decl,
                'head_type': head_base,
                # 旧判据的"类型不符"过滤（head 类型 != 被调类）——保留以便对照
                'head_type_differs': bool(head_base and tgt and head_base != tgt),
                'member_type': r['obj_type'],
                'member_size': osz,
                'called_class': tgt, 'called_method': called_m,
                'callee_va': callee_va, 'callee_sig': sig,
                'callee_min_need': need, 'callee_class_size': callee_sz,
                'callee_self_overflow': self_overflow,
                'impossible': impossible,
            })
    return cand


def _this_regs(lines):
    """函数入口 `this`（`%ecx`）在序言里被复制到哪些寄存器。

    只看**第一次 `call` 之前**的指令（之后 `%ecx` 可能已是别的对象）。
    `Actor::UpdateFrame` 用 `%ebp`、`UILoadingFrm::InitFullScreen` 用 `%edi`，
    所以**不能**假定 this 恒在 `%esi`。
    """
    regs = {'%ecx'}
    for l in lines:
        if re.search(r'\bcall\b', l):
            break
        m = re.search(r'\bmov\s+%ecx\s*,\s*(%[a-z]{2,3})\b', l)
        if m:
            regs.add(m.group(1))
    return regs


def _trace_reg(lines, start, reg, this_regs, max_back=24):
    """从 `lines[start]` 往回找 `reg` 的偏移来源。

    命中 `lea X(%this),%reg`（`%this` ∈ this_regs）⇒ 返回 X；否则 None。
    遇 `call` 或 `reg` 被写即中断（跨调用/被覆盖都不可信）。
    """
    for j in range(start - 1, max(-1, start - max_back), -1):
        b = lines[j]
        if re.search(r'\bcall\b', b):
            return None
        m = re.search(r'lea\s+0x([0-9a-f]+)\((%[a-z0-9]+)\),\s*' + re.escape(reg) + r'\b', b)
        if m:
            return int(m.group(1), 16) if m.group(2) in this_regs else None
        if re.search(r',\s*' + re.escape(reg) + r'\b', b) or \
           re.search(r'\bpop\s+' + re.escape(reg) + r'\b', b):
            return None      # reg 在此被写，来源断了
    return None


def _ecx_sources(va, size, callee_va):
    """在 `va..va+size` 里找 `call callee_va`，回溯 `%ecx` 的来源。

    返回 [(kind, disp)]：
      · `'lea'`（`lea X(%this),%ecx`，X 是相对 this 的偏移，**可用来校验**）；
      · `'lea_otherbase'`（`lea X(%r),%ecx` 但 `%r` 不是 this ⇒ 不可校验，
        旧版会把 `lea X(%esp),%ecx` 这种**栈局部变量**误当 this 偏移）；
      · `'reg'`（`mov %r,%ecx` 且 `%r` 追不到 `lea X(%this)` ⇒ 不可校验，
        **旧版把它误判成 `clobber`**，见独立复核）；
      · `'mov'`（`mov X(%r),%ecx` 从指针装载）/ `'clobber'` / `'unknown'`。
    """
    out = _objdump(va, va + size)
    lines = [l for l in out.splitlines() if re.match(r'\s+[0-9a-f]+:', l)]
    this_regs = _this_regs(lines)
    res = []
    for i, l in enumerate(lines):
        if not re.search(r'call\s+0x0*%x\b' % callee_va, l):
            continue
        found = ('unknown', None)
        for j in range(i - 1, max(-1, i - 12), -1):
            b = lines[j]
            m = re.search(r'lea\s+0x([0-9a-f]+)\((%[a-z0-9]+)\),\s*%ecx', b)
            if m:
                found = ('lea', int(m.group(1), 16)) if m.group(2) in this_regs \
                    else ('lea_otherbase', int(m.group(1), 16))
                break
            m = re.search(r'mov\s+0x([0-9a-f]+)\(%[a-z0-9]+\),\s*%ecx', b)
            if m:
                found = ('mov', int(m.group(1), 16))
                break
            m = re.search(r'mov\s+(%[a-z]{2,3}),\s*%ecx\b', b)
            if m:
                d = _trace_reg(lines, j, m.group(1), this_regs)
                found = ('lea', d) if d is not None else ('reg', None)
                break
            if re.search(r',\s*%ecx\b', b) or re.search(r'\bpop\s+%ecx\b', b):
                found = ('clobber', None)
                break
        res.append(found)
    return res


def verify_offsets(cand, S, D):
    """用**二进制真值**校验 `resolve_chain` 的偏移：调用点 `lea X(%this),%ecx`
    里的 X 必须等于解析出的 `member_off`。

    只对 **(caller, callee) 恰有一个调用点、且该候选是唯一解析值** 的组合下结论
    —— 多调用点时必须先做表达式↔指令配对，集合级比较不构成证据。
    """
    groups = {}
    for x in cand:
        if x['via_deref'] or x['member_off'] is None:
            continue
        key = (x['method_va'], x['callee_va'])
        groups.setdefault(key, []).append(x)
    ok, mismatch, multi, noneed = 0, [], 0, 0
    for (mva, cva), xs in groups.items():
        mv = norm_va(mva)
        cv = norm_va(cva)
        sz = FUNC_SIZE.get(mv, 0)
        if cv is None or sz <= 0:
            noneed += 1
            continue
        srcs = _ecx_sources(mv, sz, cv)
        if len(srcs) != 1 or len(xs) != 1:
            multi += 1
            continue
        kind, disp = srcs[0]
        if kind != 'lea':
            noneed += 1
            continue
        if disp == xs[0]['member_off']:
            ok += 1
        else:
            mismatch.append((xs[0]['method'], xs[0]['member'],
                             xs[0]['member_suffix'], xs[0]['member_off'], disp))
    return {'ok': ok, 'mismatch': mismatch, 'multi_site': multi, 'unverifiable': noneed}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--limit', type=int, default=40)
    ap.add_argument('--only', default=None, help='只扫这个类的方法')
    ap.add_argument('--out', default='_scan_misattribution_v2.json')
    ap.add_argument('--verify-offsets', action='store_true',
                    help='用调用点 lea 真值校验解析出的偏移')
    args = ap.parse_args()

    S = load_structs()
    D = load_decomp()
    print("  已加载 structs=%d  decomp=%d" % (len(S), len(D)))
    if args.only:
        D = {k: v for k, v in D.items() if v[0].split('::')[0] == args.only}

    cand = scan(S, D)
    imp = [c for c in cand if c['impossible']]
    print("  候选总数 %d；其中 **物理不可能 %d**" % (len(cand), len(imp)))
    print("  （链不可解析 %d；callee 自洽性不成立 %d）"
          % (sum(1 for c in cand if c['chain_status'] != 'ok'),
             sum(1 for c in cand if c['callee_self_overflow'])))
    print()
    print("  === 物理不可能（P1∧P2∧P3）===")
    for c in imp[:args.limit]:
        print("    %-12s %-34s this->%-16s%-22s %s(%sB) -> %s::%s need=%s"
              % (c['method_va'], c['method'][:34], c['member'][:16],
                 c['member_suffix'][:22], c['member_type'], c['member_size'],
                 c['called_class'], c['called_method'], c['callee_min_need']))
    json.dump(cand, open(os.path.join(ROOT, 'data', 'status', args.out), 'w',
                         encoding='utf-8'), ensure_ascii=False, indent=1)
    print()
    print("  完整清单 -> data/status/%s" % args.out)

    if args.verify_offsets:
        v = verify_offsets(cand, S, D)
        print()
        print("  === 偏移链 vs 二进制真值（调用点 lea）===")
        print("    单点可判定：吻合 %d，不吻合 %d；多点需配对 %d；无法判定 %d"
              % (v['ok'], len(v['mismatch']), v['multi_site'], v['unverifiable']))
        for m in v['mismatch'][:10]:
            print("      不吻合: %-30s this->%-12s%-16s 解析=%-8s 实测=%s" % m)


if __name__ == '__main__':
    main()