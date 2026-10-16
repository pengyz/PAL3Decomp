"""
AST-based C++ code transformations using tree-sitter.

Replaces regex-based OOP conversion with correct AST analysis.
Only transforms calls where first argument is safe to convert.
"""

import tree_sitter_cpp as tscpp
import tree_sitter
import re
import os
import json

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)

# Cache class hierarchy from annotation data
_CLASS_BASES = None

# Cache ret-N param-slot evidence: (cls, method) -> slots or None
_RET_SLOTS_CACHE = None

_RET_SLOTS_WARNED = set()

# ---------------------------------------------------------------------------
# AR-002 EVIDENCE-SOURCE DECLARATION (declared, deliberately NOT migrated)
# ---------------------------------------------------------------------------
# WHAT IS READ  : `data/annotations/structs/*.json` — `methods{addr: {name}}`,
#                 used as the (class, method) -> VA index for the ret-N probe.
# WHY IT MUST BE READ
#               : the gate needs a *binary* fact (the function-tail `ret N`
#                 immediate = true __thiscall stack-param byte count). The only
#                 route from a rendered `Cls::Method(...)` call to that fact is
#                 an address, and the address is only carried by the struct
#                 annotations' method table.
# WHY IT CANNOT BE MIGRATED TO AN EXPORT PRODUCT TODAY (all measured on this
# worktree, 2026-09-15; harness = the real `transform_oop_calls` driven over
# all 3524 class-member decomp JSONs, pure in-memory — see
# `data/status/_cleanup_fix_codegen_policy.json` -> harness_evidence):
#   * `_sig_evidence_pack.json` as the ONLY source -> 167/3524 files drift and
#     90.0% of the evidence table (3299 -> 335 non-None entries) disappears;
#     the direction includes *silent passes* (a gate that can no longer block).
#   * slot counts parsed from `asm/pal3/ida_structs.json` signatures ->
#     219/3524 files drift; the two sources disagree on 758 of 3332 callees.
#   * the two sources are NOT interchangeable: neither is a superset of the
#     other, so a migration is a semantic change, not a refactor.
# AR-002 (docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md, ruling
# (a)) classifies this read as a C1 architectural violation. It stays here
# DECLARED until the migration is proven output-identical; lifting the
# CLAUDE.md red line is a user decision, not a codegen decision.
# ---------------------------------------------------------------------------


# ---- 指令级 retn 证据源（模块级，便于测试与复用）-------------------
_AST_PROJ = os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__))))

_ASM_RET_RE = re.compile(r'^(?:retn|ret)(?:\s+([0-9A-Fa-f]+h?))?\s*$')

def _parse_retn(text):
    """retn 立即数 -> 栈字节数。注意 h 必须留在捕获组内（见 gotcha_*_h 后缀）。"""
    m = _ASM_RET_RE.match(text)
    if not m:
        return None
    t = m.group(1)
    if not t:
        return 0
    return int(t[:-1], 16) if t.lower().endswith('h') else int(t)

_ASM_RETNS = None

def _asm_retn_map():
    """**一次遍历**建 label -> retn 立即数列表（避免逐函数重扫 18MB 清单）。

    只用 `proc near` / `endp` 定界，取区间内所有 retn；调用方只接受
    "值唯一"的情形，多个不一致的 retn 视为无证据（保守）。
    """
    nonlocal_state = _asm_retn_map.__dict__
    if 'cache' in nonlocal_state:
        return nonlocal_state['cache']
    m = {}
    try:
        path = os.path.join(_AST_PROJ, 'original', 'PAL3.exe.asm')
        with open(path, encoding='utf-8', errors='replace') as fh:
            cur = None
            for line in fh:
                if cur is None:
                    pm = re.match(r'^(\S+)\s+proc near', line)
                    if pm:
                        cur = pm.group(1)
                        m[cur] = []
                elif re.match(r'^\S+\s+endp', line):
                    cur = None
                else:
                    v = _parse_retn(line.strip())
                    if v is not None:
                        m[cur].append(v)
    except OSError as _e:
        print('[WARN] ast_transform: 指令级 retn 源不可读 (%s)；将退回裸字节扫描'
              % _e, file=_sys.stderr)
        m = {}
    nonlocal_state['cache'] = m
    return m

_ASM_SRC_STATS = {'asm': 0, 'byte': 0, 'none': 0}

def ret_n_at_asm(va):
    """从 IDA 反汇编清单取函数尾 retn（指令级，不会把操作数当函数尾）。"""
    m = _asm_retn_map()
    if not m:
        return None
    vals = m.get('sub_%X' % va)
    if not vals or len(set(vals)) != 1:
        return None
    return vals[0]



def _ret_param_slots(cls_name, method_name):
    """True stack-param slot count for a method, from the binary.

    MSVC6 __thiscall callees clean their own stack: the function-tail
    'ret N' immediate is the parameter byte-count (4 per 4-byte slot).
    This is compiler-generated ground truth used to gate the
    explicit-this member-call rewrite: the rewrite is only valid when
    the rendered arg count is consistent with first-arg = this.

    Returns slot count (N/4, requiring N%%4==0), 0 for no-param, or
    None when the evidence is unavailable/ambiguous."""
    global _RET_SLOTS_CACHE
    if _RET_SLOTS_CACHE is None:
        _RET_SLOTS_CACHE = {}
        _load_ret_slots()
    hit = _RET_SLOTS_CACHE.get((cls_name, method_name))
    if hit is None and (cls_name, method_name) not in _RET_SLOTS_WARNED:
        _RET_SLOTS_WARNED.add((cls_name, method_name))
    return hit


def _load_ret_slots():
    """Build (cls, method) -> param slots from structs annotations + exe."""
    import struct as _struct
    import sys as _sys
    _gen_dir = os.path.dirname(os.path.abspath(__file__))
    _proj = os.path.dirname(os.path.dirname(_gen_dir))
    _structs_dir = os.path.join(_proj, 'data', 'annotations', 'structs')
    exe_path = os.path.join(_proj, 'original', 'PAL3.exe')
    if not os.path.isfile(exe_path):
        print('[WARN] ast_transform: ret-N evidence source missing: %s '
              '(ret-N gate will block every site => more [MISATTRIBUTED])'
              % exe_path, file=_sys.stderr)
        return
    try:
        _exe = open(exe_path, 'rb').read()
    except OSError as _e:
        print('[WARN] ast_transform: cannot read %s (%s) '
              '(ret-N gate will block every site)' % (exe_path, _e),
              file=_sys.stderr)
        return

    def va2off(va):
        return 0x1000 + (va - 0x401000)

    # ---- 指令级 retn 证据源（主源） ------------------------------------
    # R3(2026-09-18)：裸字节扫描会把**指令操作数里的** 0xC2/0xC3 当成函数尾
    # （下面 ret_n_at 的既有注释已自承这个盲区）。实测对 3395 个注解方法：
    # 3178 个能在 original/PAL3.exe.asm 里做指令级取值，其中与裸扫描
    # **分歧 367 个（11.6%）**，且幅度极大（Actor::LoadActorModel asm=4 而裸扫描=420
    # ⇒ 105 个假 slots；Actor::SetVisible asm=12 而裸扫描=0）。
    # 故改为：**asm 指令级为主**，裸扫描仅作 asm 不可用时的回退（并计数上报）。
    def ret_n_at(va, max_scan=0x600):
        off = va2off(va)
        if off < 0x1000 or off + max_scan > len(_exe):
            return None
        for i in range(off, off + max_scan):
            b = _exe[i]
            if b == 0xC2:
                n = _struct.unpack_from('<H', _exe, i + 1)[0]
                if n <= 0x200:
                    return n
            elif b == 0xC3:
                return 0
        return None

    # 2026-09-20 审计 P1-5（第六批）：**路径枚举**收敛到单一读点
    # `annotation_view.iter_struct_files()`（排序 glob，与原 `sorted(listdir)+endswith`
    # 等价）；**保留本处的容错策略**（坏文件打印 WARN 再 continue —— 不是静默跳过，
    # 与 annotation_view 的"调用方保留各自容错"设计原则一致）。
    import annotation_view as _av
    for _path in _av.iter_struct_files(_structs_dir):
        _f = os.path.basename(_path)
        try:
            d = json.load(open(_path, encoding='utf-8'))
        except Exception as _e:
            print('[WARN] ast_transform: skipping unreadable struct '
                  'annotation %s (%s)' % (_f, _e), file=_sys.stderr)
            continue
        cls = d.get('name') or _f[:-5]
        for a, m in (d.get('methods') or {}).items():
            mn = str(m.get('name', ''))
            try:
                va = int(a, 16)
            except ValueError as _e:
                print('[WARN] ast_transform: non-hex method address %r in %s '
                      '(%s)' % (a, _f, _e), file=_sys.stderr)
                continue
            if (cls, mn) in _RET_SLOTS_CACHE:
                continue
            n = ret_n_at_asm(va)
            if n is None:
                n = ret_n_at(va)
                _ASM_SRC_STATS['byte' if n is not None else 'none'] += 1
            else:
                _ASM_SRC_STATS['asm'] += 1
            if n is not None and n % 4 == 0:
                _RET_SLOTS_CACHE[(cls, mn)] = n // 4
            else:
                _RET_SLOTS_CACHE[(cls, mn)] = None

    if _ASM_SRC_STATS['byte'] or _ASM_SRC_STATS['none']:
        print('[ret-N evidence] 指令级(asm) %d / 裸扫描回退 %d / 无证据 %d'
              % (_ASM_SRC_STATS['asm'], _ASM_SRC_STATS['byte'],
                 _ASM_SRC_STATS['none']), file=_sys.stderr)

    # MCP-verified evidence overrides the raw byte-scan. sig_evidence.py
    # extracts ret instructions via IDA disassemble_function (instruction-
    # accurate; the byte-scan above misreads early 0xC2/0xC3 bytes inside
    # function bodies — e.g. conditional returns — as the function tail,
    # which wrongly blocks the explicit-this gate). Pack entries are graded:
    # 'slots' exists only for unanimous, %4==0 rets, so ambiguous callees
    # stay unevidenced and the gate conservatively blocks.
    # 2026-09-20 审计 P1-5（第六批）**边界裁定**：本处读的是 `data/status/` 的
    # **状态产物**（`_sig_evidence_pack.json`），**不是注解** ⇒ **不纳入 P1-5 的
    # "注解直读收敛"范围**（annotation_view 只管 data/annotations/**）。
    # 且下方注释已说明：该 typed except 是**有意保留**的（C3b：冗余但非缺陷），
    # 实测 335/335 个 pack 键已在 byte-scan 表中且 0 处冲突 ⇒ 损坏的 pack 不会改变判定。
    _pack_path = os.path.join(_proj, 'data', 'status', '_sig_evidence_pack.json')
    if os.path.isfile(_pack_path):
        # t6 §4: this typed except is KEPT on purpose and recorded as C3b
        # (redundant, not a defect): `_sig_evidence_pack` is an OPTIONAL
        # evidence-refinement input — every (cls, method) it carries is
        # already present in the byte-scan table above with an identical
        # value (measured: 335/335 pack keys exist in the cache and 0 of
        # them disagree), so a corrupt pack cannot change the verdict.
        # Making it fatal would turn an optional refinement into a hard
        # dependency.  It is NOT silent: the failure is reported.
        try:
            _pack = json.load(open(_pack_path, encoding='utf-8'))
            for _c in _pack.get('graded', []):
                if not isinstance(_c, dict) or 'slots' not in _c:
                    continue
                _key = (_c.get('cls'), _c.get('method'))
                if _key[0] and _key[1]:
                    _RET_SLOTS_CACHE[_key] = _c['slots']
        except Exception as _e:
            print('[WARN] ast_transform: %s unreadable (%s); continuing with '
                  'the raw byte-scan only' % (_pack_path, _e), file=_sys.stderr)


_ROWTABLE_CACHE = None


def _rowtable_family():
    """Classes whose 7-slot handler tables share framework slots (gbUI
    message-handler registration family; see
    docs/knowledge/decision_sceneobj_composition_not_inheritance.md).

    CG-023: a missing/corrupt family list used to fall back to an EMPTY set
    (`except (OSError, ValueError): _ROWTABLE_CACHE = set()`). Every family
    class then took the `else` arm and emitted `[MISATTRIBUTED]` instead of
    `[ROWTABLE]` — a whole-tree reclassification with NO signal in the
    generated source and none on stderr. Measured cost of that fallback on
    this worktree: 588 sites change / 328 files change. An input contract
    this load-bearing must fail loudly; `RuntimeError` (not a silent
    default) is the contract.
    """
    global _ROWTABLE_CACHE
    if _ROWTABLE_CACHE is not None:
        return _ROWTABLE_CACHE
    import json as _json
    _p = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
        os.path.abspath(__file__)))), 'data', 'status', '_rowtable_family.json')
    try:
        with open(_p, encoding='utf-8') as _fh:
            _ROWTABLE_CACHE = set(_json.load(_fh))
    except (OSError, ValueError) as _e:
        raise RuntimeError(
            'ast_transform: the [ROWTABLE] family list is required but could '
            'not be read: %s (%s). Falling back to an empty family would '
            'silently reclassify every [ROWTABLE] site as [MISATTRIBUTED] '
            '(measured: 588 sites / 328 files), so this is a hard failure. '
            'Regenerate/restore the file instead of continuing.' % (_p, _e))
    return _ROWTABLE_CACHE


# ---------------------------------------------------------------------------
# AR-002 EVIDENCE-SOURCE DECLARATION (declared, deliberately NOT migrated)
# ---------------------------------------------------------------------------
# WHAT IS READ  : `data/annotations/structs/*.json` — `base_class` (+ `name`),
#                 used as the class-hierarchy edge set for `_is_derived_from`.
# WHY IT MUST BE READ
#               : the OOP transform has to decide whether `Derived::this` and
#                 `Base::Method` are related, i.e. whether a qualified call is
#                 a legal base-class direct call (which SHADOWS a virtual and
#                 is therefore byte-relevant) or an unrelated-class call. That
#                 relation exists nowhere in the rendered code.
# WHY IT CANNOT BE MIGRATED TO AN EXPORT PRODUCT TODAY (measured on this
# worktree, 2026-09-15, same pure in-memory harness):
#   * `asm/pal3/ida_structs.json.bases` is NOT equivalent: the annotation
#     source has 179 classes with `base_class`, the export has 175 non-empty
#     `bases`; neither is a superset. The export is missing all four of
#     CEffCamera / CEffTemplate / CEffTime / _Item_List_Info (they carry a
#     `base_class` in annotations and an EMPTY `bases` in the export) and no
#     export-only base exists whose annotation is empty. Value disagreements
#     among the shared keys: 0.
#   * Swapping the source changed 0/3524 files on the current corpus, i.e. the
#     swap is *currently* output-neutral — but it is neutral only because no
#     live site today touches those four classes. That is an accident of the
#     corpus, not an equivalence proof: the tables differ, so the next
#     annotation/export cycle can move the difference into the output. A
#     migration must therefore be argued as a semantic change (with the four
#     classes ruled on explicitly), not as a refactor.
# AR-002 (ruling (a)) classifies this read as a C1 architectural violation.
# It stays DECLARED until the migration is proven output-identical on a
# corpus that exercises the differing entries.
# ---------------------------------------------------------------------------


def _ensure_bases():
    global _CLASS_BASES
    if _CLASS_BASES is not None:
        return
    _CLASS_BASES = {}
    _gen_dir = os.path.dirname(os.path.abspath(__file__))
    _proj = os.path.dirname(os.path.dirname(_gen_dir))
    _structs_dir = os.path.join(_proj, 'data', 'annotations', 'structs')
    if not os.path.isdir(_structs_dir):
        return
    for _f in sorted(os.listdir(_structs_dir)):
        if not _f.endswith('.json'):
            continue
        _sd = json.load(open(os.path.join(_structs_dir, _f), encoding='utf-8'))
        _c = _sd.get('name', '')
        _b = _sd.get('base_class')
        if _b:
            if isinstance(_b, str):
                _b = [_b]
            _CLASS_BASES[_c] = _b

def _is_derived_from(derived, base):
    """Check if derived class inherits from base (directly or transitively)."""
    if derived == base:
        return True
    if not _CLASS_BASES:
        return False
    _bases = _CLASS_BASES.get(derived, [])
    for _b in _bases:
        if _is_derived_from(_b, base):
            return True
    return False


# ---------------------------------------------------------------------------
# IDB-export vtable-slot evidence (Track 1 of the t6 double-track policy)
# ---------------------------------------------------------------------------
# `asm/pal3/ida_structs.json` is an EXPORT product (per AR-002 ruling (a) it is
# the legitimate channel), so consuming it does not add a new C1 read of
# `data/annotations/`. It answers exactly one question that the ret-N gate
# cannot: does the callee VA actually OCCUPY a vtable slot of some class?
# Occupying a slot is what makes `ret N` a *component-object-model* fact
# ("self-cleaning __thiscall member") rather than "some function with a
# stack-cleaning tail". See the Track-1 gate in `transform_oop_calls`.
_VTABLE_EVIDENCE = None
_VA_BY_METHOD = None


def _vtable_slot_evidence():
    """(frozenset of slot VAs, frozenset of (cls, method) ctor/dtor keys)."""
    global _VTABLE_EVIDENCE
    if _VTABLE_EVIDENCE is not None:
        return _VTABLE_EVIDENCE
    _proj = os.path.dirname(os.path.dirname(
        os.path.dirname(os.path.abspath(__file__))))
    _p = os.path.join(_proj, 'asm', 'pal3', 'ida_structs.json')
    try:
        with open(_p, encoding='utf-8') as _fh:
            _d = json.load(_fh)
    except (OSError, ValueError) as _e:
        # No silent fallback: `transform_oop_calls` is the only consumer and a
        # missing export would silently change its verdicts.
        raise RuntimeError(
            'ast_transform: vtable-slot evidence is required for the '
            'cross-class `(T*)this` gate but %s could not be read (%s). '
            'Run the IDA export (pipeline/cli.py export) instead of '
            'silently degrading the gate.' % (_p, _e))
    _slots = set()
    _ctor_dtor = set()
    for _c, _v in _d.items():
        if _c.startswith('_') or not isinstance(_v, dict):
            continue
        for _vt in (_v.get('vtables') or []):
            for _sl in (_vt.get('slots') or []):
                _a = _sl.get('addr')
                if not _a:
                    continue
                try:
                    _slots.add(int(_a, 16))
                except (TypeError, ValueError):
                    continue
        for _a, _m in (_v.get('methods') or {}).items():
            _mn = str(_m.get('name', ''))
            if _mn == _c or _mn == '~' + _c or _mn == '_' + _c:
                _ctor_dtor.add((_c, _mn))
    _VTABLE_EVIDENCE = (frozenset(_slots), frozenset(_ctor_dtor))
    return _VTABLE_EVIDENCE


def _occupies_vtable_slot(cls_name, method_name):
    """True when the callee's VA is present in some class's vtable slots."""
    _cache = _VA_BY_METHOD
    if _cache is None:
        _load_va_by_method()
        _cache = _VA_BY_METHOD
    _va = _cache.get((cls_name, method_name))
    if _va is None:
        return False
    return _va in _vtable_slot_evidence()[0]


def _is_ctor_or_dtor(cls_name, method_name):
    return (cls_name, method_name) in _vtable_slot_evidence()[1]


def _load_va_by_method():
    """(cls, method) -> VA index from the IDB export (one pass, cached)."""
    global _VA_BY_METHOD
    if _VA_BY_METHOD is not None:
        return _VA_BY_METHOD
    _proj = os.path.dirname(os.path.dirname(
        os.path.dirname(os.path.abspath(__file__))))
    _p = os.path.join(_proj, 'asm', 'pal3', 'ida_structs.json')
    try:
        with open(_p, encoding='utf-8') as _fh:
            _d = json.load(_fh)
    except (OSError, ValueError) as _e:
        raise RuntimeError(
            'ast_transform: method->VA index is required for the cross-class '
            '`(T*)this` gate but %s could not be read (%s). Run the IDA '
            'export (pipeline/cli.py export) instead of silently degrading '
            'the gate.' % (_p, _e))
    _m = {}
    for _c, _v in _d.items():
        if _c.startswith('_') or not isinstance(_v, dict):
            continue
        for _a, _mi in (_v.get('methods') or {}).items():
            try:
                _m[(_c, str(_mi.get('name', '')))] = int(_a, 16)
            except (TypeError, ValueError):
                continue
    _VA_BY_METHOD = _m
    return _VA_BY_METHOD


def _is_this_expr(s):
    """W6（复核 0cc3dbf0 裁决）：显式 this 的对象指针表达式可为复杂形
    （`**((gbCamera ***)this + 552)` 族）。词法安全=括号/方括号配平 + 禁赋值/语句字符
    （`=`/`;`/`{`/`}`）；AST 层已豁免定义头与字符串/注释，此处不重复。"""
    if not s or len(s) > 400:
        return False
    if not re.match(r'^[\w\s\.\+\-\*/%&\|^~!?:<>=()\[\]]+$', s):
        return False
    bal = 0
    for ch in s:
        if ch in '([':
            bal += 1
        elif ch in ')]':
            bal -= 1
            if bal < 0:
                return False
        elif ch in '=;{}':
            return False
    return bal == 0


def _mask_strings_comments(code):
    """E-1（c1e92014）：字符串/字符字面量与注释**同长遮蔽**（保位移）——
    匹配与计数在掩码上做、替换落回原文，根治'字符串内调用形被改写'类孔。
    5a7a3b86：E-2 `_expand_pair64_double` 同用此掩码（掩码纪律贯彻全族）。"""
    out = list(code)
    i, n = 0, len(code)
    while i < n:
        ch = code[i]
        if ch in '"\'':
            q = ch
            j = i + 1
            while j < n and code[j] != q:
                if code[j] == '\\':
                    out[j] = 'x'
                    j += 1
                out[j] = 'x'
                j += 1
            if j < n:
                out[j] = q
            i = j + 1
        elif ch == '/' and i + 1 < n and code[i + 1] == '/':
            while i < n and code[i] != '\n':
                out[i] = 'x'
                i += 1
        elif ch == '/' and i + 1 < n and code[i + 1] == '*':
            out[i] = out[i + 1] = 'x'
            i += 2
            while i < n and not (code[i] == '*' and i + 1 < n and code[i + 1] == '/'):
                out[i] = 'x'
                i += 1
            if i < n:
                out[i] = out[i + 1] = 'x'
                i += 2
        else:
            i += 1
    return ''.join(out)


def drop_call_echo_arg(code, sig_slots_by_method):
    """批 E C2660 族（Comp_DonateUI:41 UpdateAnim 双参 vs retn 4=1 参铁证）：
    调用形回波首参剔除。**词法化三证据门**（E-1，c1e92014 残孔全封）：
    ①槽数相等 ②回波形（`(int)<x>` 铸形**或**裸标识符∈外层**真定义头**形参集
    （控制流头/else/宏头不入、数字/浮点/十六进制字面量不入）③匹配与 argc 计数
    **全程掩码**（字符串/字符字面量/`//`/`/* */` 同长遮蔽——根治字面量内容被改写）。"""
    if not sig_slots_by_method:
        return code
    masked = _mask_strings_comments(code)
    # 外层函数真定义头形参集（掩码上提取——注释/宏头污染根治）
    fn_params = set()
    for mdef in re.finditer(r'^([\w:\*~& ]+)\(([^)]*)\)\s*$', masked, re.MULTILINE):
        head = mdef.group(1).strip()
        if re.match(r'^(if|else|while|for|switch|return|sizeof|catch)\b', head):
            continue
        if not re.match(r'^[\w:\*~& ]+$', head):
            continue                       # 宏头（ASSERT 等）非定义头
        # [T51] 方法隐式 this 入回波形参集（F-echo-drop-this-gap 闭合）：
        # this-strip 后 def-head 无 this，但调用形渲 `this` 回波须剔
        # （thiscall 语义 ✓——A 级：thunk `e9 0b 00 00 00` jmp 形无实参设置）。
        if '::' in head:
            fn_params.add('this')
        for pm in re.finditer(r'\b(\w+)\s*(?:\[[^\]]*\])?\s*(?=,|$)', mdef.group(2)):
            # 字面量守卫（07fe8e00 残孔补：0x10i64/100i64 MSVC __int64 后缀、(int)0x10u 铸形）
            _v = pm.group(1)
            if re.match(r'^(0[xX][0-9a-fA-F]+[uUlL]*(?:i64|ui64)?|\d+[uUlLfF]*(?:i64|ui64)?'
                        r'|\d+\.\d+[fF]?|\d+[eE][+-]?\d+[fF]?)$', _v):
                continue
            fn_params.add(_v)

    def _echo_ok(first):
        f = first.strip()
        # (int) 铸形回波：07fe8e00 G9 残孔——`(int)0x10u` 等**字面量铸形**不是回波（真参！）
        m = re.match(r'^\(\s*int\s*\)\s*([\w\->.\[\]]+)$', f)
        if m:
            return not re.match(r'^(0[xX][0-9a-fA-F]+|\d+)', m.group(1))
        return re.match(r'^\w+$', f) is not None and f in fn_params

    pat = re.compile(
        r'(?<!\w)(?P<method>\w+)\s*\((?P<first>[^(),]+(?:\([^()]*\)[^(),]*)*'
        r'|\([^()]*\)[^(),]*)\s*,\s*')
    edits = []
    # [T51] 单实参 this 回波形（f(this)——pattern 的 `,\s*` 尾要求多实参，
    # 单实参形不入）：0 槽数签名 + 唯一实参 this + **thunk 属性证据**
    # （decomp `// attributes: thunk` 注记——A 级：thunk `e9 0b 00 00 00`
    # jmp 形无实参设置）⇒ 剔除。当场读实证：无 thunk 证据的 f(this) 有
    # 真实参案（UI3DModelNode/_Console 翻红）⇒ 证据门收窄至此。
    # [T86] 名形扩 `~?\w+`（dtor 形）：ObjectCamera ctor→dtor COMDAT 别名的
    # `~ObjectCamera(this)` 回波须入（T85 定位——原 \w+ 头不含 ~）。
    pat_this = re.compile(r'(?<![\w~])(?P<method>~?\w+)\s*\(\s*this\s*\)')
    # [T53-F2] 证据门锚定行首注释形（非裸子串——字面量含该短语即误放行）
    if re.search(r'^\s*//\s*attributes:\s*thunk', code, re.M):
        for m in pat_this.finditer(masked):
            if sig_slots_by_method.get(m.group('method')) == 0:
                edits.append((m.start(), m.end(), '%s()' % m.group('method')))
    for m in pat.finditer(masked):
        method = m.group('method')
        slots = sig_slots_by_method.get(method)
        if slots is None or slots < 1 or not _echo_ok(m.group('first')):
            # slots<1（0 槽数签名）=证据不足不动（2026-09-29：SetVideoRect/LayoutSlot 族
            # 0 槽数签名把唯一实参当回波剔掉 ⇒ C2660 "does not take 0 parameters"）
            continue
        start = m.end()
        depth, argc = 1, 1
        i = start
        while i < len(masked) and depth:
            ch = masked[i]
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
            elif ch == ',' and depth == 1:
                argc += 1
            i += 1
        if argc + 1 == slots + 1:
            edits.append((m.start(), m.end(), '%s(' % method))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


def collect_struct_value_members(member_type_pairs, base_names=None):
    """批 3 成员集判别（6e90d6f0 清账条件1+2：提纯函数+N-a 廉价收窄）。
    判别：类/结构体/union **值**（含 `Cls[N]` 数组、dict 形内联）才入集。
    **N-a 收窄**：同名任一实例是标量/指针/别名 ⇒ 该名整体不入集。
    【挂账⑥】`base_names`：+0 首基类名入集。
    【挂账⑥ N-a 类域化】member_type_pairs 元素可为 (name, type) 或 (name, type, cls)——
    三元组时 N-a **按类**收窄（同类同名标量才出局——desc/Remark/yaw 三件类域恢复）。
    """
    _SCALARS = {'int', 'float', 'double', 'char', 'bool', 'void', 'long', 'short',
                'DWORD', 'BYTE', 'UINT', 'WORD', 'BOOL', 'HWND', 'INT', 'LONG',
                'FLOAT', 'CHAR', 'UCHAR', 'USHORT', 'ULONG', 'SIZE_T', 'WPARAM',
                'LPARAM', 'HRESULT', 'HANDLE', 'COLORREF', 'RECT', 'POINT',
                'PVOID', 'PSCOPETABLE_ENTRY'}
    name_all = {}      # name(或 cls|name) -> True 若出现过标量/指针实例
    name_ok = set()
    scoped = False
    for item in member_type_pairs:
        if len(item) >= 3:
            name, t, cls = item[0], item[1], item[2]
            scoped = True
            key = '%s|%s' % (cls, name)
        else:
            name, t = item[0], item[1]
            key = name
        if not name:
            continue
        if isinstance(t, dict):
            name_ok.add(name)                # inline union/struct 值
            continue
        ts = str(t)
        base = re.sub(r'\s*\[[^\]]*\]\s*$', '', ts).strip()
        if not base or '*' in base or ts.strip().endswith('*'):
            name_all[key] = True             # 指针实例 ⇒ 该名出局
            continue
        b2 = base.lstrip('const ').strip()
        if b2 in _SCALARS or base in _SCALARS:
            name_all[key] = True             # 标量实例 ⇒ 该名出局
            continue
        if re.match(r'^(?:const\s+)?[A-Z]\w*$', base):
            name_ok.add(name)
    for bn in (base_names or ()):
        if bn and not name_all.get(bn):
            name_ok.add(bn)
    if scoped:
        # 类域 N-a：任一类同名标量出局（保守向——跨类不救）
        bad = {k.split('|', 1)[1] for k, v in name_all.items() if v}
        return {n for n in name_ok if n not in bad}
    return {n for n in name_ok if not name_all.get(n)}


def normalize_deref_cast_parens(code):
    """C2100 形归一（TDD）：`*(T**)(x)` → `*((T**)(x))`（显式括号——双括号歧义防）。
    MSVC6 对 `*(T**)(x)` 的 `*` 解析歧义（乘法/间接）——显式括号形消歧。"""
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    pat = re.compile(r'\*\s*\(\s*(?:[A-Za-z_]\w*(?:\s+|\s*\*\s*)?)+\s*\*\s*\)\s*\(')
    edits = []
    for m in pat.finditer(masked):
        orig = m.group(0)
        # 窄形（回滚教训 2026-10-07）：仅病灶形——操作数含 member-chain（this->X / X->Y）
        _operand = masked[m.end():m.end() + 60]
        if not re.match(r'\s*(?:this->|[\w\[\]]+->)', _operand):
            continue
        # `*(T**)` → `*((T**)` + 末尾配 `)`——形：*(T**)( → *((T**)( ... )
        if 'x' * 3 in masked[m.start():m.end()] and 'x' * 3 not in code[m.start():m.end()]:
            continue
        start = m.end() - 1
        depth = 0
        end = None
        for i in range(start, len(masked)):
            if masked[i] == '(':
                depth += 1
            elif masked[i] == ')':
                depth -= 1
                if depth == 0:
                    end = i
                    break
        if end is None:
            continue
        rep = orig.replace('*(', '*((', 1)
        edits.append((m.start(), m.end(), rep, end))
    out = code
    for s, e, rep, close in reversed(edits):
        out = out[:s] + rep + out[e:close] + ')' + out[close:]
        # 末尾补 )——从 match 后找表达式末（简化：在 rep 后第一个 `)` 后插 `)`
    return out


def drop_redundant_mid_qualifier(code, pairs=None):
    """B1 限定链修（接线三清账版·TDD 9 测）：`recv->A::Base::m` → `recv->Base::m`。
    ①判别器（pairs：A∈基链∧B∈A 基类才删——合法三段形不动）②≤3 轮收敛 ③掩码红线。
    pairs=None=无判别（仅限已证形——接线批须传基链）。"""
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    pat = re.compile(
        r'((?:->|\.))'
        r'([A-Za-z_]\w*)'       # 中间限定段 A
        r'::([A-Za-z_]\w*::)'   # 末级 Base::
        r'((?:(?:::)?[A-Za-z_~]\w*)+)'  # 成员面
        )
    for _round in range(3):
        edits = []
        for m in pat.finditer(masked):
            sep, mid, base, rest = m.group(1), m.group(2), m.group(3), m.group(4)
            if pairs is not None:
                _mid_ok = any(bb == mid for (_cc, bb) in pairs)
                _base_ok = any(cc == mid and bb == base.rstrip(':') for (cc, bb) in pairs)
                if not (_mid_ok and _base_ok):
                    continue    # 非基链——合法形/未知不动
            rep = sep + base + rest
            if 'x' * 3 in masked[m.start():m.end()] and 'x' * 3 not in code[m.start():m.end()]:
                continue
            if rep != m.group(0):
                edits.append((m.start(), m.end(), rep))
        if not edits:
            break
        out = code
        for s, e, rep in reversed(edits):
            out = out[:s] + rep + out[e:]
        code = out
        try:
            masked = _mask_strings_comments(code)
        except Exception:
            masked = code
    return code


def dedupe_identical_lvars(decls):
    """A 簇 lvar 归并（返工 R-A/R-C）：全等去重 + **同名裁决闭环**。
    归并键=(func,loc,name,type) 全等去重；同 (func,loc,name) 异型 ⇒ 单留原声明+冲突报出
    （C2371 防——复核实证：语料 9 组同槽同名异型）。出口不变量：每 (func,name) 至多一条。
    ④ live-range match=接线批待办（复核 R-D 显式降级）。"""
    seen = set()
    out = []
    by_name = {}
    conflicts = []
    for d in decls or ():
        if not d.get('name'):
            continue                       # 空名滤（复核新发现4）
        t = d.get('type')
        tkey = json.dumps(t, sort_keys=True, default=str) if isinstance(t, (dict, list)) else t
        key = (d.get('func'), d.get('loc'), d.get('name'), tkey)
        if key in seen:
            continue
        seen.add(key)
        nk = (d.get('func'), d.get('loc'), d.get('name'))
        if nk in by_name:
            conflicts.append((nk, by_name[nk].get('type'), t))
            continue                       # 同名单留（R-A：C2371 防）
        by_name[nk] = d
        out.append(d)
    return out, conflicts


def adjudicate_lvar_type(location, uses_evidence):
    """A 簇型仲裁（返工 R-B）：证据一致性分类器——**返回域封闭**。
    返回 'consistent'（同型证据一致）/ 'keep_original'（无证据/缺 scale/越域）/ 'conflict'。
    注：证据标签（ptr_scale_N）不等于 C 类型——stride→sizeof 注册表解析=接线批（复核 R-B）。"""
    kinds = set()
    for u in uses_evidence or ():
        if not isinstance(u, dict):
            return 'keep_original'
        if u.get('kind') == 'ptr_scale':
            sc = u.get('scale')
            if not isinstance(sc, int):
                return 'keep_original'      # 缺 scale/字符串 scale=非证据
            kinds.add('ptr_scale_%d' % sc)
        elif u.get('kind'):
            kinds.add(str(u.get('kind')))
        else:
            return 'keep_original'          # 空 kind=非证据（返回域封闭）
    if not kinds:
        return 'keep_original'
    if len(kinds) == 1:
        return 'consistent'
    return 'conflict'


def position_lvar_by_ordinal(lvars, stkoff, ordinal):
    """per-lvar ordinal 定位（TDD 3 测·复核 R4）：同址第 N 个 lvar 定位（0 基）。
    同址多 lvar（FullInit 14 件）——ordinal 区分（apply/export 的批量改名修正）。"""
    hits = [v for v in (lvars or ()) if v.get('stkoff') == stkoff]
    if 0 <= ordinal < len(hits):
        return hits[ordinal]
    return None


def split_lvar_names_by_addr(lvars):
    """跨址同名拆名（TDD·复核 M1）：pSceneName 型跨址（56/60）——按址归名。"""
    seen = {}
    out = []
    for v in (lvars or ()):
        addr = v.get('stkoff')
        base = v.get('name')
        if base in seen and seen[base] != addr:
            v = dict(v)
            v['name'] = '%s_%d' % (base, addr)   # 跨址拆名（语义名+址后缀）
        else:
            seen[base] = addr
        out.append(v)
    return out


def fix_void_ptr_arith_cast(code):
    """C2036 形修（TDD）：`(void *)p + N` → `(char *)p + N`（字节算术等价形）。
    MSVC void* 算术=C2036——char* 字节指针等价（宽度同）·指针算术语义保。"""
    import re as _re
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    pat = _re.compile(r'\(\s*void\s*\*\s*\)\s*([\w\)\]]+(?:\[[^\]]*\])*)\s*(\+|-)\s*(\d+)')
    edits = []
    for m in pat.finditer(masked):
        if 'x' * 3 in masked[m.start():m.end()] and 'x' * 3 not in code[m.start():m.end()]:
            continue
        # 红线修（根因分析）：替换取**原文**切片（掩码 x 禁入——arabo 教训）
        g1 = code[m.start(1):m.end(1)]
        g2 = code[m.start(2):m.end(2)]
        g3 = code[m.start(3):m.end(3)]
        rep = '(char *)%s %s %s' % (g1, g2, g3)
        edits.append((m.start(), m.end(), rep))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


CPP_KEYWORDS = {
    'int', 'void', 'char', 'short', 'long', 'float', 'double', 'bool', 'signed', 'unsigned',
    'const', 'static', 'extern', 'register', 'volatile', 'auto', 'inline', 'virtual',
    'class', 'struct', 'union', 'enum', 'typedef', 'template', 'namespace', 'using',
    'public', 'private', 'protected', 'operator', 'new', 'delete', 'this', 'return',
    'if', 'else', 'for', 'while', 'do', 'switch', 'case', 'default', 'break', 'continue',
    'goto', 'sizeof', 'typeof', 'try', 'catch', 'throw', 'true', 'false', 'nullptr',
}


def is_valid_identifier(name):
    """codegen 关键字守卫（Phase 2·TDD 3 测）：标识符合法性（关键字/非法形拒收）。
    毒名（int/void 当函数名——批 21 事故）拒收·响亮计数。"""
    if not name or not re.match(r'^[A-Za-z_]\w*$', name):
        return False
    return name not in CPP_KEYWORDS


def fix_macro_safe_decl(code):
    """宏规避形修（TDD 3 测）：`int (Name)(...)` → `int Name_(...)`（宏安全后缀）。
    Win32 宏（CreateDialog 型）规避形 `int (Name)(...)` 语法错（C2629）——后缀形替代。"""
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    pat = re.compile(r'\b(?:int|void|bool|char|float|double|[\w:]+\s*\*?)\s*\((\w+)\)\s*\(')
    edits = []
    for m in pat.finditer(masked):
        name = code[m.start(1):m.end(1)]
        if 'x' * 3 in masked[m.start():m.end()] and 'x' * 3 not in code[m.start():m.end()]:
            continue
        rep = m.group(0).replace('(%s)' % name, '%s_' % name)
        edits.append((m.start(), m.end(), rep))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


# [F-CG#23 2026-10-15] Win32 import 族 fnptr cast 补 __stdcall：
#   `v6 = (void ( *)(LPSTR, LPCSTR))lstrcatA;` ⇒ `(void (__stdcall *)(…))lstrcatA`
# 病灶：Hex-Rays 的 cast 文本 fnptr 型无显式约定 ⇒ 默认 __cdecl，而 lstrcatA/
# lstrcpyA 是 WINAPI(__stdcall)（windows.h 声明）⇒ 调用约定错位（经 v6 的间接
# 调用走 cdecl 形=错字节/错清栈；实测 SaleUI.cpp:7574/7580 · TaskBookUI.cpp:297/303）。
# 等价变换：仅对**已知 WINAPI 导入名**的 cast 目标补限定（不误伤普通 fnptr cast）。
_WINQAPI_FN_NAMES = ('lstrcatA', 'lstrcpyA', 'lstrcmpA', 'lstrlenA', 'wsprintfA')

_WINQAPI_CAST_RE = re.compile(
    r'\(\s*([\w ]+?)\(\s*\*\s*\)\s*\(([^()]*)\)\s*\)\s*('
    + '|'.join(_WINQAPI_FN_NAMES) + r')\b')


# ═══ [型名替换缺陷签名逆转 2026-10-16] ═══════════════════════════════
# 机制（analyzer 病灶层纠正，T66-F1 措辞精确）：IDB 里 m_rect@16 全库唯一属 UIWnd
# ⇒ Hex-Rays 把 `*((T**)X+4)`（X+16 指针槽读）按**型名替换**渲染成 `X->m_rect.left`
# （数字巧合：N×4 == UIWnd.m_rect.left 偏移 16）。**位等价但型谎言**（S2/L1 无感）；
# decomp 原文已带此形 ⇒ codegen 转写无辜 ⇒ 修点=codegen **后处理签名逆转**。
# 签名 1（28 处）：`<铸>`包裹坐标值（值即刻指针化）→ *((T**)X+N)
# 签名 2（9 处）：坐标值进乘/除/下标/地址算术（无浮点铸前缀）→ 同式槽读
# ⚠️ **禁全量逆转**：1410 处里 1373 处是真成员访问（`(double)X->m_rect.right * v8`
# 这类浮点缩放/比较/赋值/传参）⇒ 判据只吃签名命中形，真访问零触碰。
_MRECT_SLOT_N = {'left': 4, 'top': 5, 'right': 6, 'bottom': 7}
_MRECT_FIND_RE = re.compile(r'(->|\.)\s*m_rect\s*\.\s*(left|top|right|bottom)\b')
_MRECT_REAL_CAST_RE = re.compile(
    r'\(\s*(?:double|float|int|LONG|UINT|DWORD|unsigned[ ]\w+|signed[ ]\w+|short|char|__int\d+)\s*\)\s*$')


def _scan_mrect_base(code, pos):
    """pos = `->`/`.m_rect` 前；向左扫出基表达式 X 的起始下标（标识符/下标/箭头/成员链）。"""
    i = pos
    while i > 0:
        ch = code[i - 1]
        if ch.isalnum() or ch == '_':
            j = i - 1
            while j > 0 and (code[j - 1].isalnum() or code[j - 1] == '_'):
                j -= 1
            i = j
        elif ch == ']':
            depth, j = 1, i - 1
            while j > 0 and depth:
                j -= 1
                if code[j] == ']':
                    depth += 1
                elif code[j] == '[':
                    depth -= 1
            i = j
        elif ch == ')':
            depth, j = 1, i - 1
            while j > 0 and depth:
                j -= 1
                if code[j] == ')':
                    depth += 1
                elif code[j] == '(':
                    depth -= 1
            # 括组内容形如「型名+星」或含 fnptr 织别 `(*` ⇒ 是**铸**不是基表达式
            _inner = code[j + 1:i - 1]
            if (re.match(r'^\s*[\w\s:]*\*+\s*$', _inner)
                    or re.match(r'^\s*[\w\s:]+\s*\([^()]*\)\s*\*+\s*$', _inner)
                    or re.search(r'\(\s*\*', _inner)):
                break
            i = j
        elif ch == '>':
            if i >= 2 and code[i - 2] == '-':
                i -= 2
            else:
                break
        elif ch == '.':
            j = i - 1
            while j > 0 and (code[j - 1].isalnum() or code[j - 1] == '_'):
                j -= 1
            i = j
        elif ch.isspace():
            j = i - 1
            while j > 0 and code[j - 1].isspace():
                j -= 1
            if j > 0 and (code[j - 1].isalnum() or code[j - 1] in '_)]>.'):
                i = j
                continue
            break
        else:
            break
    return i


def reverse_mrect_typelie(code):
    """[型名替换缺陷签名逆转] 只动签名 1/2 命中形（等价变换，位保持逐字节）。"""
    out = []
    pos = 0
    while True:
        m = _MRECT_FIND_RE.search(code, pos)
        if not m:
            out.append(code[pos:])
            break
        b_start = _scan_mrect_base(code, m.start())
        base = code[b_start:m.start()]
        field = m.group(2)
        n = _MRECT_SLOT_N[field]
        tail = m.end()
        after = code[tail:tail + 24]
        before = code[:b_start].rstrip()

        replaced = None
        # ── 签名 1：简单指针铸直接包裹 `(<T> *)<base>` ──
        cm = re.search(r'\(\s*([\w\s:]+?)\s*(\*+)\s*\)$', before)
        if cm:
            ty = cm.group(1).strip()
            start = b_start - (len(before) - cm.start())
            out.append(code[pos:start])
            out.append('*((%s **)%s + %d)' % (ty, base.strip(), n))
            pos = tail
            continue
        # ── 签名 1'：复杂铸（fnptr 形）包裹 ⇒ 仅逆转访问本身为整数槽读 ──
        if before.endswith(')'):
            out.append(code[pos:b_start])
            out.append('*((_DWORD *)%s + %d)' % (base.strip(), n))
            pos = tail
            continue
        # ── 签名 2：乘/除/下标/地址算术位（无浮点铸前缀）──
        preceded_amp = code[:b_start].rstrip().endswith('&')
        arith_next = bool(re.match(r'\s*[\*/]', after))
        # 左邻乘/除（`9344 * X.m_rect.right` 形——值作右操作数）
        arith_prev = bool(re.search(r'[\*/]\s*$', code[:b_start]))
        amp_arith = bool(re.match(r'\s*[+\-]', after))
        real_cast = bool(_MRECT_REAL_CAST_RE.search(code[:m.start()].rstrip()))
        if (arith_next or arith_prev or (preceded_amp and amp_arith)) and not real_cast:
            out.append(code[pos:b_start])
            if preceded_amp:
                # `&X.m_rect.<f>` 在算术位 ⇒ 取槽址：(_DWORD *)X + N
                out.append('((_DWORD *)%s + %d)' % (base.strip(), n))
            else:
                out.append('*((_DWORD *)%s + %d)' % (base.strip(), n))
            pos = tail
            continue
        # 真成员访问：零触碰
        out.append(code[pos:tail])
        pos = tail
    return ''.join(out)


def fix_winqapi_fnptr_casts(code):
    """[F-CG#23] Win32 import 族 fnptr cast 补 `__stdcall`（幂等：已带约定的不动）。"""
    def _sub(m):
        ret, args, tgt = m.group(1), m.group(2), m.group(3)
        return '(%s (__stdcall *)(%s))%s' % (ret.strip(), args, tgt)
    return _WINQAPI_CAST_RE.sub(_sub, code)


def fix_fnptr_qualified_call(code, base_names=None):
    """C2273 fn-ptr 限定形（TDD 3 测）：`recv->Base(args)` → `((Base&)recv).M(args)`（子对象形）。
    fn-ptr 调用渲染名=基类名——子对象引用形（复核真形 f3d 编译器证）·分号保全。"""
    bn = base_names or set()
    if not bn:
        return code
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    edits = []
    for name in sorted(bn, key=len, reverse=True):
        pat = re.compile(
            r'(?<![\w])((?:this->|[\w]+->))' + re.escape(name) + r'\(([^;]*?)\)\s*;')
        for m in pat.finditer(masked):
            recv = code[m.start(1):m.end(1)].rstrip('->').rstrip('.')
            args = code[m.start(2):m.end(2)]
            if 'x' * 3 in masked[m.start():m.end()] and 'x' * 3 not in code[m.start():m.end()]:
                continue
            rep = '((%s &)%s).M(%s);' % (name, recv, args)
            edits.append((m.start(), m.end(), rep))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


def rewrite_base_offset_read(code, base_offsets=None):
    """F2 基类读 offset 形（TDD 3 测）：`recv->Base`（非零基类 @off）→ `*(T*)((char*)recv+off)`。
    非零基类读（TaskMgr @40 型）——offset 形（保偏移）·+0 基类不动（B1 面）·分号保全。"""
    bo = base_offsets or {}
    if not bo:
        return code
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    edits = []
    for (cls, name), off in bo.items():
        if off == 0:
            continue
        pat = re.compile(
            r'(?<![\w])((?:this->|[\w]+->))' + re.escape(name) + r'(?![\w:])'
            r'(\s*(?:=[^=]|;))')
        for m in pat.finditer(masked):
            recv = code[m.start(1):m.end(1)]
            tail = code[m.start(2):m.end(2)]
            if 'x' * 3 in masked[m.start():m.end()] and 'x' * 3 not in code[m.start():m.end()]:
                continue
            rep = '(%s)((char *)%s + %d)%s' % (name, recv.rstrip('->').rstrip('.'), off, tail)
            edits.append((m.start(), m.end(), rep))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


def fix_arg_type_casts(code, sig_params=None):
    """codegen 参铸扩展（TDD 4 测·C2664 族通解）：签名参型 vs 实参型铸补。
    `X->M(&recv)` vs `const char*` → `(const char*)&recv`。元数门（复核结论）：参不齐不动。
    已铸/无签名/元数异=保守不动。"""
    sp = sig_params or []
    if not sp:
        return code
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    pat = re.compile(r'((?:->|\.))(\w+)\(([^;]*?)\)\s*;')
    edits = []
    for m in pat.finditer(masked):
        args = m.group(3)
        # 元数门
        if args.count(',') + 1 != len(sp):
            continue
        # 多参铸补（族级扩展）
        parts = args.split(',')
        new_parts = []
        changed = False
        for i, p in enumerate(parts):
            arg_o = p.strip()
            if arg_o.startswith('(') or not arg_o.startswith('&'):
                new_parts.append(p)
                continue
            typ = sp[i] if i < len(sp) else sp[-1]
            # 替换取原文（掩码红线）
            idx = m.start(3) + args.find(arg_o)
            arg_real = code[idx:idx + len(arg_o)]
            new_parts.append(p.replace(arg_o, '(%s)%s' % (typ, arg_real), 1))
            changed = True
        if not changed:
            continue
        edits.append((m.start(3), m.end(3), ','.join(new_parts)))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


def rewrite_base_suffix_bare_form(code, base_names=None, base_sizes=None,
                                  nonzero_offsets=None):
    """B′ 形扩展（复核样张表·TDD 5 测）：F1 裸值形基类后缀重写。
    `recv.Base = V` → `*(W *)&recv = V`（W=基类 size 证据）。
    "+0 全称"守卫：混偏移名（任一接收者非 +0）不动。`::` 守卫·词界·掩码。"""
    bn = base_names or set()
    bs = base_sizes or {}
    nz = nonzero_offsets or {}
    if not bn:
        return code
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    edits = []
    for name in sorted(bn, key=len, reverse=True):
        # 混偏移守卫（+0 全称）
        if any(nb == name for (_t, nb) in nz):
            continue
        w = bs.get(name, 4)
        typ = '_DWORD' if w == 4 else 'int'
        pat = re.compile(
            r'(?<![\w])((?:this->|[\w]+->)[\w]+(?:\[[^\]]*\])*(?:(?:->|\.)[\w]+(?:\[[^\]]*\])*)*?)(?=\.' + re.escape(name) + r'(?![\w:]))'
            r'\.' + re.escape(name) + r'(?![\w:])'
            r'(\s*(?:=[^=]|;|,|\)|\+|-))')    # 表达式内尾（赋值/语句末/逗号/括号/算符）
        for m in pat.finditer(masked):
            recv, tail = m.group(1), m.group(2)
            if 'x' * 3 in masked[m.start():m.end()] and 'x' * 3 not in code[m.start():m.end()]:
                continue
            # 红线修（arabo 复发）：替换取**原文**切片（掩码 x 禁入）
            recv_o = code[m.start(1):m.end(1)]
            tail_o = code[m.start(2):m.end(2)]
            rep = '*(%s *)&%s%s' % (typ, recv_o, tail_o)
            edits.append((m.start(), m.end(), rep))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


def build_member_index_from_headers(hdrs, cls=None):
    """member_index 构建（TDD 3 测·复核"生成头为准"）：成员声明解析+继承链传递。
    hdrs={类名: 头文本}——编译器视图（生成头）。cls 给定时传递基类链成员。"""
    import re as _re
    members = {}
    bases = {}
    for cname, txt in (hdrs or {}).items():
        ms = set()
        for m in _re.finditer(r'^\s*(?:virtual\s+)?[\w:*<>,\s&]+?\s+(\w+)\s*\([^;]*\)\s*;',
                             txt, _re.M):
            ms.add(m.group(1))
        for m in _re.finditer(r'^\s*[\w:*<>,\s&]+?\s+(\w+)\s*(?:\[[^\]]*\])?\s*;\s*(?://.*)?$',
                             txt, _re.M):
            ms.add(m.group(1))
        members[cname] = ms
        bm = _re.search(r'^\s*(?:class|struct)\s+\w+\s*:\s*([^{]+)\{', txt, _re.M)
        if bm:
            bases[cname] = set()
            for b in bm.group(1).split(','):
                b = _re.sub(r'\b(?:public|protected|private|virtual)\b', '', b)
                b = b.split('<')[0].strip().split('::')[-1].strip()
                if b and b != cname:
                    bases[cname].add(b)
    if cls:
        # 基类链传递（风险 2 修）
        chain = set()
        stack = [cls]
        while stack:
            c = stack.pop()
            if c in chain:
                continue
            chain.add(c)
            for b in (bases.get(c) or ()):
                stack.append(b)
        merged = set()
        for c in chain:
            merged |= members.get(c, set())
        return {cls: merged}
    return members


def resolve_method_identity(addr, ann_structs=None, functions=None, decomp=None,
                            ida_methods=None, allowlist=None):
    """A′ 身份决议器（复核修订案·TDD 9 样张）：同址多源身份决议。
    优先级：structs methods > functions.json > decomp > ida_structs（注解权威）。
    ①坏名拒收 ②归一化等价 ③同名异址不合并 ④跨类豁免 ⑤同址多源幂等。"""
    a = ann_structs or {}
    f = functions or {}
    d = decomp or {}
    im = ida_methods or {}
    allow = allowlist or {'0x00445D10'}

    def _norm(n):
        # 返工（复核：vector-dtor bug+__ovl_ 分叉）——对齐 collect/emit_headers 三处规则
        n = (n or '').split('(')[0].strip()
        if n.startswith('`') and n.endswith("'"):
            if 'deleting' in n:
                n = '_vector_dtor' if 'vector' in n else '_scalar_dtor'
            else:
                n = n.strip('`').strip("'")
        n = re.sub(r'__ovl_[0-9a-fA-F]+$', '', n)     # 去序号（collect 同款——非保序）
        return n

    def _bad(cls, name):
        if '::' in name:
            parts = name.split('::')
            if len(parts) >= 3:
                return True
            if cls and parts[0] != cls:
                return True
        return False

    if addr in a:
        e = a[addr]
        cls, name = e.get('cls'), _norm(e.get('name'))
        if addr in allow:
            return (cls, name, e.get('sig'), 'allowlist_cross_class')
        if _bad(cls, name):
            return (cls, name, e.get('sig'), 'rejected_bad_name')
        return (cls, name, e.get('sig'), 'structs')
    if addr in f:
        e = f[addr]
        nm = _norm(e.get('name'))
        cls = nm.split('::')[0] if '::' in nm else None
        name = nm.split('::')[-1] if '::' in nm else nm
        return (cls, name, e.get('sig'), 'functions')
    if d:
        nm = _norm(d.get('name'))
        cls = nm.split('::')[0] if '::' in nm else None
        name = nm.split('::')[-1] if '::' in nm else nm
        return (cls, name, d.get('sig'), 'decomp')
    if addr in im:
        e = im[addr]
        return (e.get('cls'), _norm(e.get('name')), e.get('sig'), 'ida')
    return (None, None, None, 'unknown')


def fix_struct_value_casts(code, struct_member_names, cls=None, base_map=None):
    """挂账② B1 步 1（2026-10-06 方案复核证伪 &-插入）：结构体值铸标量的 **重解释重写**。
    等价依据（复核四站实证）：`(int)x.Base`＝**首 DWORD 装载**（孪生 `*(_DWORD *)&x.Base`
    同值——CCBUIPanel v57/v60 对照）——`&`-插入是 lea≠mov 语义反转（m_Slots −27 先例
    =错误数降+字节污染，已回修）。
    等价前提（收窄不变）：表达式终止于 `m_X[i]`/`m_X` 且成员是类/结构体/union 值。
    ①掩码全程 ②名字双侧词界 ③类域化（cls+base_map）④铸前缀形不动
    ⑤终止判别含 `::`（限定形 `x.Base::m` 是值用法不重写——复核守卫洞实证）⑥重解释形。"""
    if not struct_member_names:
        return code
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        masked = code
    # 类域化：cls 的成员集 ∩ 全局结构体值集（跨类同名标量防误伤）
    names = set(struct_member_names)
    if cls and base_map:
        scope = set()
        for c in [cls] + list(base_map.get(cls) or ()):
            scope |= set(base_map.get(c + ':members') or ())
        if scope:
            names &= scope
    if not names:
        return code
    alt = '|'.join(re.escape(n) for n in sorted(names, key=len, reverse=True))
    # 双侧词界 + 终止判别（含 ::）+ 铸前缀形结构性免疫
    pat = re.compile(
        r'(\(\s*(?:int|unsigned long|DWORD|unsigned int)\s*\))'
        r'((?:this|\w+)(?:\s*(?:->|\.)\s*\w+)*\s*(?:->|\.)\s*'
        r'(' + alt + r')(?:\s*\[[^\]]*\])?)'
        r'(?![\w])'                                  # 名字右词界
        r'(?!\s*(?:->|\.|\[|::))'                    # 终止判别（含 :: 限定形守卫）
        )
    def _sub(m):
        cast, target = m.group(1), m.group(2)
        if target.lstrip().startswith('&'):
            return m.group(0)
        if m.group(0).lstrip().startswith('*('):     # 已重解释形幂等
            return m.group(0)
        inner = cast.strip()[1:-1].strip()           # (int) → int
        # B1：重解释装载形 `*(T*)&expr`（首 DWORD 装载语义——等价变换）
        return '*(%s *)&%s' % (inner, target)
    # edits 逆序落原文（掩码仅定位）
    edits = []
    for m in pat.finditer(masked):
        rep = _sub(m)
        if rep != m.group(0):
            edits.append((m.start(), m.end(), rep))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


def build_ref_arg_context(cls_member_names, var_types):
    """批 16 构造器（复核四反例防线）：fix_ref_arg_calls 的 struct_value_exprs 构造。
    集 = **成员名**（struct_value 成员）+ **裸 lvar 名**（kind=value 且 base 为类/结构体型）。
    四反例防线实证（复核 Q1）：`this`/指针变量/字面量/数组名 不入集。
    类型判别：标识符形 base（**含小写起首**——gbVec3D/gbTexture 真实类名形）排除标量表。"""
    _SCALARS = {'int', 'float', 'double', 'char', 'bool', 'void', 'long', 'short',
                'DWORD', 'BYTE', 'UINT', 'WORD', 'BOOL', 'HWND', 'INT', 'LONG',
                'FLOAT', 'CHAR', 'UCHAR', 'USHORT', 'ULONG', 'SIZE_T', 'WPARAM',
                'LPARAM', 'HRESULT', 'HANDLE', 'COLORREF', 'RECT', 'POINT'}
    exprs = set()
    for n in (cls_member_names or ()):
        if n and not re.match(r'^(?:this|0[xX]|[\d.])', str(n)):
            exprs.add(str(n))
    for name, t in (var_types or {}).items():
        if not name or name == 'this':
            continue
        if not isinstance(t, dict):
            continue
        base = str(t.get('base', '')).lstrip('const ').strip()
        if t.get('kind') == 'value' and base and base not in _SCALARS \
                and re.match(r'^[A-Za-z_]\w*$', base):
            exprs.add(name)
    return exprs


def fix_ref_arg_calls(code, sig_params, struct_value_exprs):
    """批 15 返工（复核 B-1/B-2）：实参位丢 & 补全。
    **纯插入式**（B-1：重建式回写泄掩码毁字符串注释）：掩码仅定位——`&` 以**偏移插入点**
    落原文（天然不重叠 ⇒ B-2 嵌套拼接错位根治），逆序应用。
    等价前提：签名形参 T&/T* 且实参为已知结构体值表达式（alts 全匹）⇒ 取址。
    保守：已取址/值形形参/嵌套实参/数字字面量/**元数不符** 不动；解引用/铸解引用形为
    显式非目标（val_pat 拒）。残余风险：同名多签名撞车（'Rotate' 4 真签名）——
    ptr 位重合时侥幸、不重合时漏修（保守向）。"""
    if not sig_params or not struct_value_exprs:
        return code
    try:
        masked = _mask_strings_comments(code)
    except Exception:
        return code                     # 掩码不可用=不动（E-1 纪律——禁静默降级）
    alts = '^(?:%s)$' % '|'.join(re.escape(x) for x in sorted(struct_value_exprs, key=len, reverse=True))
    alts_re = re.compile(alts)
    val_pat = re.compile(r'^(?:this|[\w\)\]]+)(?:\s*(?:->|\.)\s*\w+)*(?:\s*\[[^\]]*\])?$')
    inserts = []                        # (offset) 纯插入——不重建
    for fn, ptypes in sig_params.items():
        # 【N1 修正（批 16 复核）】仅 **`T*` 指针参**补 &——`T&` 引用参 lvalue 直绑
        # 不需 &（且 &-临时量非法）；C2664 `to 'T *'` 真相=临时量绑非 const 引用失败。
        ptr_idx = {i for i, t in enumerate(ptypes)
                   if isinstance(t, str) and t.rstrip().endswith('*')}
        if not ptr_idx:
            continue
        call_pat = re.compile(r'(?<!\w)' + re.escape(fn) + r'\s*\(')
        for m in call_pat.finditer(masked):
            start = m.end()
            depth, spans, cur_start, i = 1, [], start, start
            while i < len(masked) and depth:
                ch = masked[i]
                if ch == '(':
                    depth += 1
                elif ch == ')':
                    depth -= 1
                    if depth == 0:
                        break
                elif ch == ',' and depth == 1:
                    spans.append((cur_start, i))
                    cur_start = i + 1
                    i += 1
                    continue
                i += 1
            if depth != 0:
                continue
            spans.append((cur_start, i))
            if len(spans) != len(ptypes):
                continue                # 元数门（复核修件3）
            for k, (a, b) in enumerate(spans):
                if k not in ptr_idx:
                    continue
                ast = masked[a:b].strip()
                if not ast or ast.startswith('&'):
                    continue
                if re.match(r'^(?:0[xX][0-9a-fA-F]+|\d+(?:\.\d+)?)[uUlLfF]*$', ast):
                    continue            # 数字字面量（&0.5f 非法——复核实证）
                if not val_pat.match(ast):
                    continue
                # alts 全匹：全表达式（裸 lvar）或**末段**（成员链——`this->m_v` 的 m_v）
                last = re.sub(r'\s*\[[^\]]*\]\s*$', '', ast.split('->')[-1].split('.')[-1]).strip()
                if not (alts_re.match(ast) or alts_re.match(last)):
                    continue
                ins_off = a + (len(masked[a:b]) - len(masked[a:b].lstrip()))
                inserts.append(ins_off)
    out = code
    for off in sorted(set(inserts), reverse=True):
        out = out[:off] + '&' + out[off:]
    return out


def _parse_sig_arity(sig):
    """[T27] 签名元数门解析：返回 (this_type, 非 this 形参数) 或 None。
    __thiscall(Cls *this, p1, ...) ⇒ ('Cls', N)；非 thiscall/无 this ⇒ None。"""
    if not sig or '__thiscall' not in sig:
        return None
    m = re.search(r'\((.*)\)\s*$', sig)
    if not m:
        return None
    plist = [x.strip() for x in m.group(1).split(',') if x.strip()]
    if not plist:
        return None
    tm = re.match(r'^(?:struct\s+)?([A-Za-z_]\w*)\s*\*+\s*(?:this|_this)\s*$', plist[0])
    if not tm:
        return None
    return tm.group(1), len(plist) - 1


def rewrite_unqualified_member_call(code, methods_by_cls, exclude=None, slots_by_method=None, sig_map=None):
    """批 E C2065#1：Hex-Rays 丢类限定的成员调用等价转写。

    `name((T *)recv, ...)` 且 name ∈ methods_by_cls[T] ⇒ `(((T *)recv))->T::name(...)`
    证据门：①name ∈ T.methods ②exclude（static_methods）不转。
    ⚠️ 槽数门已撤（5a7a3b86 假门清）；slots_by_method 参数保留接口兼容但不参与判定。"""
    if not methods_by_cls and not sig_map:
        return code
    ex = exclude or set()
    # [T27] 签名元数门（T26 教训：宽 map 证损伤/唯一名回退实测净负 ⇒ 收窄到
    # (name, 元数) 精准匹配）：候选=sig 为 __thiscall(this, N 形参) 的方法且
    # 调用实参数（recv-cast 之外）恰为 N；(name,N) 唯一 ⇒ 以 sig 的 this 型
    # 为类（cast 型是 E.T 噪声不作依据）。非 thiscall/元数不符/多命中 ⇒ 不转。
    _by_na = {}
    for _k, _s in (sig_map or {}).items():
        if '::' not in _k:
            continue
        _c, _n = _k.split('::', 1)
        _n = _n.split('(')[0]
        _pa = _parse_sig_arity(_s)
        # [T69] 裸 `__thiscall()` 形（0 形参 thiscall=仅 this）：_parse_sig_arity
        # 返 None ⇒ _by_na 缺项（T27 裸名 feed 同族缺口，F80 族 GetActiveAttackCount
        # 实证）⇒ 按 (键类, 元数 0) 补——this 型回落键类（方法归属即 this 型等价证据）。
        if _pa is None and '__thiscall' in str(_s) and re.search(r'\(\s*\)\s*$', str(_s)):
            _pa = (None, 0)
        _this_ty = _pa[0] if _pa else None
        if not _this_ty:
            _this_ty = _c
        if _pa:
            _by_na.setdefault((_n, _pa[1]), []).append(_this_ty)
    pat = re.compile(
        r'(?<![\w:])(?:(?P<qcls>\w+)::)?(?P<name>\w+)\s*\(\s*\(\s*(?P<cls>\w+)\s*\*\s*\)\s*'
        r'(?P<recv>[\w\->.\[\]]+)\s*(?P<rest>,[^;]*)?\)')

    def _sub(m):
        qcls, cls, name = m.group('qcls'), m.group('cls'), m.group('name')
        if name in ex:
            return m.group(0)
        rest = m.group('rest') or ''
        # [T27] 语义确定门：recv 仅 this/_this（T26/T27 实证——非 this 接收者的
        # 宽改写在实链产生嵌套改写垃圾（CCBMagicWindow +102 等 3 单元损伤）；
        # this 接收者 + (name,元数) 唯一 + thiscall 三门齐 ⇒ 成员调用形确定。
        if m.group('recv') not in ('this', '_this'):
            return m.group(0)
        nargs = len([x for x in rest.lstrip(', ').split(',') if x.strip()]) if rest else 0
        if sig_map is not None:
            cands = _by_na.get((name, nargs)) or []
            if len(cands) != 1:
                return m.group(0)          # 元数不符/多命中 ⇒ 不转（禁猜测）
            target = cands[0]
        else:
            if name not in (methods_by_cls.get(cls) or ()):
                return m.group(0)
            target = cls
        return '(((%s *)%s))->%s::%s(%s)' % (
            target, m.group('recv'), target, name, rest.lstrip(', '))

    return pat.sub(_sub, code)


def transform_oop_calls(code, static_methods=None, cls_name=None):
    """
    Transform Class::Method(obj, args) -> obj->Method(args)
    Only when:
    - Function is qualified (Class::Method)
    - First argument is a simple identifier or 'this'
    - Function is NOT a static (__cdecl) method

    Does NOT transform when first arg is:
    - Cast expression: (Type *)expr
    - Member access: obj->field
    - Array subscript: arr[i]
    - Any other complex expression
    """
    if static_methods is None:
        static_methods = set()

    # Preprocess Hex-Rays ->N (offset N access) patterns before tree-sitter parsing.
    # Hex-Rays generates "&var->N" meaning "address of member at offset N" which in C
    # is just "var" (the pointer itself). "var->N" alone means "first DWORD at *var".
    # tree-sitter can't parse ->N as valid C++, so we must normalize first.
    code = re.sub(r'&(\w+(?:\s*->\s*\w+)*)\s*->\s*0\b', r'\1', code)
    code = re.sub(r'\b(\w+(?:\s*->\s*\w+)*)\s*->\s*0\b', r'*((_DWORD *)\1)', code)

    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)

    # Collect replacements (offset, length, new_text)
    replacements = []

    def process_node(node):
        if node.type == 'call_expression':
            func_node = node.child_by_field_name('function')
            args_node = node.child_by_field_name('arguments')

            if func_node and args_node and func_node.type == 'qualified_identifier':
                # It's a Class::Method(...) call
                scope_node = func_node.child_by_field_name('scope')
                name_node = func_node.child_by_field_name('name')

                if scope_node and name_node:
                    class_name = scope_node.text.decode('utf-8').rstrip(':')
                    method_name = name_node.text.decode('utf-8')

                    # ⚠️ tree-sitter 对 `std::string::_Eos(...)` 给的是**嵌套**
                    # qualified_identifier：scope='std'、name='string::_Eos'。
                    # 只取一层会让 class_name='std' ⇒ 产出 `((std *)v6)->std::string::_Eos()`
                    # —— cast 类型错，且限定符重复。这里把嵌套摊平到最内层。
                    _guard = 0
                    while name_node is not None and name_node.type == 'qualified_identifier' \
                            and _guard < 8:
                        _sc = name_node.child_by_field_name('scope')
                        _nm = name_node.child_by_field_name('name')
                        if not _sc or not _nm:
                            break
                        class_name = '%s::%s' % (
                            class_name, _sc.text.decode('utf-8').rstrip(':'))
                        name_node = _nm
                        method_name = name_node.text.decode('utf-8')
                        _guard += 1

                    # `p->Cls::M()` 只在 Cls 是**简单类名**时合法。当 scope 是
                    # **限定名**（`std::string`、`std::codecvt_base`）时，MSVC 会把
                    # `->std` 当成成员查找：
                    #     C2039: 'std' : is not a member of 'GRPinput'
                    #     C2653: 'std' : is not a class or namespace name
                    # 实测生成物里有 **75 处**这种非法形态
                    # （std::string::_Tidy/_Eos/_Split/_Freeze/_Grow、std::codecvt_base::...）。
                    # ⇒ 限定名时省略 `Cls::` 限定符，但**保留 cast**：
                    #     ((std::string *)this)->_Tidy(...)
                    _qual = '' if '::' in class_name else (class_name + '::')

                    # Skip static (__cdecl) methods — their first arg is data, not this
                    qualified = '%s::%s' % (class_name, method_name)
                    if qualified in static_methods:
                        return

                    # Skip operator calls (operator new, operator delete, etc.)
                    if class_name == 'operator' or method_name == 'operator':
                        return

                    # Get arguments (skip parens and commas)
                    arg_nodes = [c for c in args_node.children
                                 if c.type not in ('(', ')', ',', 'comment')]

                    # Primitive-type class names are Hex-Rays misattributions.
                    # Strip the class qualifier to produce a free-function call.
                    # E.g. BYTE::_sub_4CD0D0(args) → _sub_4CD0D0(args)
                    _PRIMITIVE_TYPES = frozenset({
                        'BYTE', 'CHAR', 'WPARAM', 'float', 'double',
                        'int', 'long', 'short', 'char', 'void',
                        '_BYTE', '_DWORD', '_WORD', 'signed',
                        'unsigned', 'BOOL', 'DWORD', 'WORD',
                    })
                    if class_name in _PRIMITIVE_TYPES:
                        arg_texts = [a.text.decode('utf-8') for a in arg_nodes]
                        new_text = '%s(%s)' % (method_name, ', '.join(arg_texts))
                        replacements.append((
                            node.start_byte, node.end_byte, new_text))
                        import sys as _sys
                        print('[WARN] Hex-Rays misattribution: %s::%s → %s' % (
                            class_name, method_name, new_text[:80]), file=_sys.stderr)
                        return

                    if not arg_nodes and cls_name:
                        # Zero-arg qualified call (Hex-Rays omits the implicit
                        # this in dtor chains, e.g. Base::Cleanup() inside a
                        # derived dtor). Related targets emit the legal
                        # this-qualified form; unrelated ones pass through
                        # untouched — blanket-marking them only added ~400
                        # noise markers on calls that already compile.
                        _ensure_bases()
                        if class_name == cls_name or _is_derived_from(cls_name, class_name):
                            new_text = 'this->%s::%s()' % (class_name, method_name)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                        return

                    if arg_nodes:
                        first_arg = arg_nodes[0]
                        first_arg_text = first_arg.text.decode('utf-8')

                        # Constructor call: Class::Class(&var, args) -> var.Class(args)
                        # Hex-Rays emits explicit-this ctor calls (placement style).
                        _short_cls = class_name.split('::')[-1]
                        if method_name == _short_cls:
                            _ctor_rest = ', '.join(
                                a.text.decode('utf-8') for a in arg_nodes[1:])
                            if first_arg_text.startswith('&'):
                                # Construct at address &var -> var.Class(args)
                                _obj = first_arg_text[1:]
                                new_text = '%s.%s(%s)' % (
                                    _obj, _short_cls, _ctor_rest)
                            elif first_arg_text == 'this':
                                new_text = 'this->%s(%s)' % (
                                    _short_cls, _ctor_rest)
                            else:
                                # Class::Class(ptr) -> ptr->Class()
                                new_text = '%s->%s(%s)' % (
                                    first_arg_text, _short_cls, _ctor_rest)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return

                        # Determine conversion strategy based on first arg type
                        rest_args = [a.text.decode('utf-8')
                                     for a in arg_nodes[1:]]
                        rest_str = ', '.join(rest_args)

                        if first_arg.type == 'this':
                            # Map IDA internal destructor name _ClassName -> ~ClassName
                            _method_out = method_name
                            if method_name == '_' + class_name.split('::')[-1]:
                                _method_out = '~' + class_name.split('::')[-1]

                            # Constructor call: Class::Class(this) -> this->Class()
                            _short_cls = class_name.split('::')[-1]
                            if method_name == _short_cls:
                                _ensure_bases()
                                _is_base = _is_derived_from(cls_name, class_name)
                                if _is_base and class_name != cls_name:
                                    new_text = '%s::%s(%s)' % (class_name, _method_out, rest_str)
                                else:
                                    new_text = 'this->%s(%s)' % (_method_out, rest_str)
                                replacements.append((
                                    node.start_byte, node.end_byte, new_text))
                                return

                            _ensure_bases()
                            _is_base = _is_derived_from(cls_name, class_name)
                            # Use qualified Base::Method(rest) when calling base class method
                            # from derived class that may SHADOW the base method.
                            if _is_base and class_name != cls_name:
                                # 裸限定 Base::Method(rest) 缺对象 → C2352；
                                # this->Base::Method(rest) 是合法基类直调
                                new_text = 'this->%s::%s(%s)' % (
                                    class_name, _method_out, rest_str)
                            elif class_name == cls_name or _is_base:
                                # Qualified call preserves the direct-call
                                # semantics Hex-Rays reported (unqualified
                                # this->M() on a virtual M compiles to vtable
                                # dispatch — different bytes). Explicit dtor
                                # calls are already direct, keep them clean.
                                if _method_out.startswith('~'):
                                    new_text = 'this->%s()' % _method_out
                                else:
                                    new_text = 'this->%s::%s(%s)' % (
                                        class_name, _method_out, rest_str)
                            else:
                                # Explicit base-dtor chain call: legal whether
                                # or not annotations record the derivation
                                # (destruction sequences are real code), keep
                                # the old clean form.
                                if _method_out.startswith('~'):
                                    new_text = 'this->%s()' % _method_out
                                else:
                                    # Unrelated class called on our own this:
                                    # confirmed IDB attribution error (the
                                    # original source could never write this
                                    # call). Keep the static call form so
                                    # MSVC6 reports C2352 — precise signal to
                                    # fix the callee's IDB name — and mark it.
                                    # Never launder into legal syntax.
                                    _args = 'this' + \
                                        (', ' + rest_str if rest_str else '')
                                    new_text = (
                                        '/* [MISATTRIBUTED] %s::%s on %s::this '
                                        '-> fix IDB name of callee */ %s::%s(%s)'
                                        % (class_name, _method_out, cls_name,
                                           class_name, _method_out, _args))
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return
                        elif first_arg.type == 'identifier':
                            # Simple var: cast to the class so the qualified call
                            # compiles regardless of the local's declared type.
                            # The cast is the isomorphic form of Hex-Rays' own
                            # explicit-this convention (same this value, same
                            # call target — nothing invented).
                            _strip = first_arg_text.lstrip(':')
                            _needs_addr = (
                                class_name[0].isupper()
                                and _strip.startswith('g_')
                                and _strip not in static_methods
                            )
                            _obj = '&' + first_arg_text if _needs_addr else first_arg_text
                            new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                class_name, _obj, class_name, method_name, rest_str)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return
                        else:
                            # Complex expression as this-pointer
                            # Literals (numbers/strings/chars) can NEVER be a this
                            # pointer. Hex-Rays emits e.g. std::string::_Tidy(1)
                            # where 1 is a real parameter. Keep the static call
                            # form so the compiler reports an accurate error.
                            if first_arg.type in ('number', 'string_literal', 'character_literal'):
                                return
                            # Skip function call results — they return values, not objects
                            if first_arg.type == 'call_expression':
                                return
                            if first_arg.type == 'cast_expression':
                                val_node = first_arg.child_by_field_name('value')
                                inner = val_node.text.decode('utf-8') if val_node else first_arg_text
                                _inner_strip = inner.lstrip(':')
                                _qualified = '%s::%s' % (class_name, method_name)
                                if _qualified in static_methods:
                                    return
                                if inner == 'this':
                                    # (T*)this: the object's TRUE type is known
                                    # (cls_name). If the method's class is this
                                    # class or one of its bases, the qualified
                                    # call is legal and preserves the direct-call
                                    # semantics Hex-Rays reported.
                                    _ensure_bases()
                                    if class_name == cls_name or \
                                            _is_derived_from(cls_name, class_name):
                                        new_text = 'this->%s::%s(%s)' % (
                                            class_name, method_name, rest_str)
                                    else:
                                        # Row-table family: gbUI registers a
                                        # 7-function message-handler table per
                                        # window class (slot0/4/6 framework
                                        # entries shared across the family,
                                        # slot1/2/3/5 per-class handlers).
                                        # X::M((X*)this) from any registered
                                        # class is framework dispatch through
                                        # the caller's table — emit the
                                        # faithful cast+qualified form.
                                        if class_name in _rowtable_family():
                                            _rest = [a.text.decode('utf-8')
                                                     for a in arg_nodes[1:]]
                                            new_text = (
                                                '(((%s *)this))->%s::%s(%s) /* [ROWTABLE] */'
                                                % (class_name, class_name,
                                                   method_name, ', '.join(_rest)))
                                        else:
                                            # Unrelated class on our own this: the IDB
                                            # name of the callee cannot be right (the
                                            # original source could never write this
                                            # call). Do NOT launder it into legal
                                            # syntax — keep the static call form and
                                            # mark it; MSVC6 reports C2352, which is
                                            # the honest "fix the IDB attribution"
                                            # signal (C2039 would mislead people into
                                            # adding declarations).
                                            #
                                            # Track-1 exception (t6 double-track
                                            # policy, strictly 3 sites): the marker's
                                            # own action text ("fix IDB name of
                                            # callee") is DISPROVEN when two
                                            # independent binary facts hold at the
                                            # SAME site:
                                            #   (1) the ret-N gate passes
                                            #       (_ret_param_slots == len(args)-1):
                                            #       the rendered arg count is exactly
                                            #       the __thiscall stack-param count,
                                            #       so "first arg == this" is
                                            #       self-consistent;
                                            #   (2) the callee VA OCCUPIES a vtable
                                            #       slot of its class: the callee is a
                                            #       real member of that class, so the
                                            #       attribution is correct and only
                                            #       the CALLER's this-type is
                                            #       unverified.
                                            # Together they say: keep the cast AND keep
                                            # the qualified direct-call form
                                            # (byte-faithful — the binary does a direct
                                            # E8 call here, not a vtable dispatch),
                                            # and drop the marker whose premise is
                                            # falsified. This is NOT "laundering into
                                            # legal syntax": the static-call shape and
                                            # the `(Cls*)this` cast are preserved
                                            # verbatim; only the false claim goes.
                                            # Ctor/dtor are excluded on purpose — a
                                            # ctor/dtor is never the "unrelated class's
                                            # vtable slot on our own this" case.
                                            # NEITHER condition alone is admissible:
                                            # the ret-N gate alone rewrites 298 sites /
                                            # 189 files on this corpus; the vtable fact
                                            # alone also opens 3.
                                            _margs = first_arg_text +                                                 (', ' + rest_str if rest_str else '')
                                            _t1_slots = _ret_param_slots(
                                                class_name, method_name)
                                            _t1_retn = (
                                                _t1_slots is not None
                                                and _t1_slots == len(arg_nodes) - 1)
                                            _t1_vt = _occupies_vtable_slot(
                                                class_name, method_name)
                                            if (_t1_retn and _t1_vt
                                                    and not _is_ctor_or_dtor(
                                                        class_name, method_name)):
                                                new_text = (
                                                    '(((%s *)this))->%s%s(%s)'
                                                    % (class_name, _qual,
                                                       method_name, rest_str))
                                            else:
                                                # 【候选①·复核者反例】保留 cast 与 IDB 归属，
                                                # 只补上对象解引用（与 Track-1/ROWTABLE 同形状）
                                                new_text = '((%s))->%s%s(%s)' % (
                                                    first_arg_text, _qual,
                                                    method_name, rest_str)
                                else:
                                    # Normalize the cast to the method's class and
                                    # keep the qualifier: ((Cls*)X)->Cls::M(rest).
                                    # X is an untyped local/global or a member
                                    # subobject address — the call defines the
                                    # this-contract, so this is reconstruction
                                    # (Hex-Rays lost the local's type), not a lie.
                                    new_text = '(((%s *)%s))->%s%s(%s)' % (
                                        class_name, inner, _qual,
                                        method_name, rest_str)
                                replacements.append((
                                    node.start_byte, node.end_byte, new_text))
                                return
                            elif first_arg.type == 'qualified_identifier':
                                _scope = first_arg.child_by_field_name('scope')
                                _name = first_arg.child_by_field_name('name')
                                _inner = (_scope.text.decode() if _scope else '') + (_name.text.decode() if _name else '')
                                _strip = _inner.lstrip(':')
                                _needs_addr = (
                                    class_name[0].isupper()
                                    and _strip.startswith('g_')
                                )
                                _obj = '&' + _inner if _needs_addr else _inner
                                new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                    class_name, _obj, class_name, method_name, rest_str)
                                replacements.append((
                                    node.start_byte, node.end_byte, new_text))
                                return
                            elif first_arg.type == 'pointer_expression':
                                _op_node = first_arg.child_by_field_name('operator')
                                _op = _op_node.text.decode('utf-8') if _op_node is not None else ''
                                _ptr_inner = first_arg_text[1:].lstrip(':').lstrip()
                                # 证据门控：__thiscall 被调方自清栈，尾部 ret N
                                # 即真实栈参数字节数（4B/槽）。槽 == len(args)-1
                                # ⇔ "首参=this" 解释自洽 → 成员调用形式同构重写；
                                # 否则首参是真参数（静态/ cdecl 形态），保持原样
                                # 让 MSVC6 诚实报错。
                                _slots = _ret_param_slots(class_name, method_name)
                                _this_consistent = (
                                    _slots is not None
                                    and _slots == len(arg_nodes) - 1)
                                if _op == '&' and re.match(
                                        r'^[A-Za-z_][\w\.\[\]\->]*$', _ptr_inner):
                                    # F71（第 131 轮）：显式取址的 this 形态。
                                    # 与上面 identifier 分支同一条约定（Hex-Rays 的显式 this 习惯：
                                    # 首参就是对象指针），而实测它正是 C2660 大家族的主因：
                                    #   `gbVec3D::operator=(&v21.Direction, ViewTarget);`
                                    #   `gbVec3D::SetParam(&…, …)` / `RenderGeomQuad` / `ReplaceTexture` …
                                    # 第 129 轮的判定性实验已排除"靠改声明通过"的路线
                                    # （VC6 对**任何**成员的 `Class::method(obj, args)` 都按普通函数
                                    #   解析 ⇒ 必报 C2660），故只能在 codegen 侧改写。
                                    # 改写为 `((Cls *)&obj)->Cls::method(rest)`：this 值不变、调用目标不变。
                                    new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                        class_name, first_arg_text, class_name,
                                        method_name, rest_str)
                                    replacements.append(
                                        (node.start_byte, node.end_byte, new_text))
                                    return
                                # F72（第 132 轮）：`*simple_expr` 形态同样按"Hex-Rays 显式 this 习惯"改写。
                                # 原条件要求 `_this_consistent`（ret-N 证据），但**导入成员没有函数体** ⇒
                                # 该证据恒为 None ⇒ 这一族永远改不动，实测剩下：
                                #   `gbGeomNode::ReplaceTexture(*m_pCorpse, v11);`（C2661 ×12）
                                # 与 `identifier`/`&obj` 两条 arm 一致：限定名 + 首参是对象指针表达式即可。
                                # W6（复核 0cc3dbf0 裁决）：放宽到**复杂 `*expr`/`**expr`**——
                                #   `gbCamera::SetAsCurrent(**((gbCamera ***)this + 552), 3);`
                                #   `gbCamera::SetAsCurrent(*((gbCamera **)this + 73), 3);`
                                #   `gbGeomNode::GetOBBox(*(gbCamera **)&v3[144], …)`
                                # AST 层天然豁免定义头/字符串/注释；此处词法安全=括号配平+禁赋值。
                                # W6-修正（codegen 实测 6×C2227）：`*expr` 臂必须**带 cast 重建**
                                # （与 :901 规则 c 同一保真形态）——`*(_DWORD*)(slot)` 一族解引用出的
                                # 是无类型槽值，裸 `->` 必 C2227；cast 恢复 this 契约类型，字节零差。
                                if _op == '*' and not _this_consistent and (
                                        re.match(r'^[A-Za-z_][\w\.\[\]\->]*$', _ptr_inner)
                                        or _is_this_expr(_ptr_inner)):
                                    new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                        class_name, first_arg_text, class_name,
                                        method_name, rest_str)
                                    replacements.append(
                                        (node.start_byte, node.end_byte, new_text))
                                    return
                                if _op == '*' and _this_consistent:
                                    new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                        class_name, first_arg_text, class_name,
                                        method_name, rest_str)
                                    replacements.append((
                                        node.start_byte, node.end_byte, new_text))
                                    return
                                if _op == '&' and _this_consistent:
                                    # 全局对象地址作 this：obj.Cls::M(rest)
                                    _ptr_strip = _ptr_inner.lstrip(':')
                                    if re.match(r'^(g_[A-Z]|unk_|stru_|dword_)', _ptr_strip):
                                        new_text = '%s.%s::%s(%s)' % (
                                            _ptr_strip, class_name,
                                            method_name, rest_str)
                                        replacements.append((
                                            node.start_byte, node.end_byte, new_text))
                                    else:
                                        # 成员子对象地址（&this->m_x 等）作 this：
                                        # cast 重建形式 —— 与未知类型局部变量的
                                        # ((A*)p)->A::f(x) 同一保真规则（规则 c）：
                                        # 调用本身定义了 this 契约，地址是真实的
                                        # 对象位置，cast 只是恢复 Hex-Rays 丢失的
                                        # 子对象类型，不是类型谎言。
                                        new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                            class_name, first_arg_text,
                                            class_name, method_name, rest_str)
                                        replacements.append((
                                            node.start_byte, node.end_byte, new_text))
                                    return
                                # 其余（局部 &local、无法定位对象等）：保持静态形式，
                                # 让 MSVC6 诚实报错 —— 不做任何编辑
                                return
                            elif first_arg.type in ('binary_expression', 'parenthesized_expression'):
                                # Complex expression like (Type*)ptr - offset or (ptr + N)
                                # Cast + parens preserve precedence and type
                                new_text = '((%s *)(%s))->%s::%s(%s)' % (
                                    class_name, first_arg_text, class_name,
                                    method_name, rest_str)
                                replacements.append((
                                    node.start_byte, node.end_byte, new_text))
                                return
                            else:
                                new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                    class_name, first_arg_text, class_name,
                                    method_name, rest_str)
                            replacements.append((
                                node.start_byte, node.end_byte, new_text))
                            return

        for child in node.children:
            process_node(child)

    process_node(tree.root_node)

    # Apply replacements in reverse order (to preserve offsets)
    result = code_bytes
    for start, end, new_text in sorted(replacements, reverse=True):
        result = result[:start] + new_text.encode('utf-8') + result[end:]

    # 兜底归一化：`p->A::B::m(` / `this->A::B::m(` 在 MSVC6 下非法
    # （C2039 'std' is not a member of ... / C2653）。合法 C++ **绝不会**出现
    # 连续 ≥2 段限定名跟在 `->` 后（单段 `p->Cls::m()` 是合法的，且是刻意保留的
    # 非虚调用形式，这里**不动**）。实测生成物里曾有 75 处。
    # 只折叠限定符、保留对象表达式本身；对非虚方法调用语义等价。
    _QUAL2 = re.compile(rb'->\s*(?:[A-Za-z_]\w*::){2,}([A-Za-z_~]\w*)\s*\(')
    result = _QUAL2.sub(rb'->\1(', result)

    return _qualify_this_member_calls(result.decode('utf-8'), cls_name)


# ============================================================
# F82（第 141 轮）：非限定成员直调 `M(this, rest)` ⇒ `this->Cls::M(rest)`
# ============================================================
#
# 实测链（§48）：Hex-Rays 对成员直调有时**不写类限定**（decomp 原文 `ProcessKeyboard(this, 1);`），
# `transform_oop_calls` 只处理 `qualified_identifier` 被调方 ⇒ 这里原样输出；
# 之后生成侧的名字解析把它**限定成** `InputSystem::ProcessKeyboard(this, 1)`
# ——只加前缀、没动接收者，于是 VC6 按类作用域的 `void ProcessKeyboard(int a1)` 数两个实参 ⇒
# `C2660 : function does not take 2 parameters`（实测 12 条）。
#
# 判据（不是猜测）：`Cls` 的**生成头**里确实声明了名为 `M` 的成员
# （编译器将来就按那份声明检查 `Cls::M`），且首参就是 `this`。
# 改写后 this 值不变、调用目标不变；`this->Cls::M(rest)` 是合法且非虚的直调形式。
_METHOD_INDEX_CACHE = None


def _class_method_index():
    """{类名: {成员函数名}} —— 直接读生成头（`pal3/src/**/*.h` 的文件名即类名）。"""
    global _METHOD_INDEX_CACHE
    if _METHOD_INDEX_CACHE is None:
        import os
        import glob
        idx = {}
        root = os.path.join(os.path.dirname(os.path.dirname(
            os.path.dirname(os.path.abspath(__file__)))), 'pal3', 'src')
        for p in glob.glob(os.path.join(root, '**', '*.h'), recursive=True):
            cls = os.path.basename(p)[:-2]
            try:
                with open(p, encoding='utf-8', errors='replace') as fh:
                    txt = fh.read()
            except OSError:
                continue
            names = set()
            for line in txt.splitlines():
                s = line.strip()
                if not s or s.startswith('//') or s.startswith('#'):
                    continue
                m = re.match(r'^(?:virtual\s+)?[\w:<>\*&\s]+?\b(\w+)\s*\(', s)
                if m and (';' in s or '{' in s):
                    names.add(m.group(1))
            if names:
                idx.setdefault(cls, set()).update(names)
        _METHOD_INDEX_CACHE = idx
    return _METHOD_INDEX_CACHE


def _qualify_this_member_calls(code, cls_name):
    """把本类成员头里的 `M(this, rest)` 改写成 `this->Cls::M(rest)`。"""
    if not cls_name:
        return code
    names = _class_method_index().get(cls_name)
    if not names:
        return code
    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)
    replacements = []

    def process_node(node):
        if node.type == 'call_expression':
            fn = node.child_by_field_name('function')
            ar = node.child_by_field_name('arguments')
            if fn is not None and ar is not None and fn.type == 'identifier':
                mname = fn.text.decode('utf-8')
                if mname in names:
                    args = [c for c in ar.children
                            if c.type not in ('(', ')', ',', 'comment')]
                    if args and args[0].type == 'this':
                        rest = ', '.join(a.text.decode('utf-8') for a in args[1:])
                        new_text = 'this->%s::%s(%s)' % (cls_name, mname, rest)
                        replacements.append((node.start_byte, node.end_byte, new_text))
        for child in node.children:
            process_node(child)

    process_node(tree.root_node)
    if not replacements:
        return code
    result = code_bytes
    for start, end, new_text in sorted(replacements, reverse=True):
        result = result[:start] + new_text.encode('utf-8') + result[end:]
    return result.decode('utf-8')


# ---------------------------------------------------------------- COERCE 变换
# 【2026-09-15 加】为什么用 AST 而不是正则（本会话实测教训）：
#   `COERCE_FLOAT(x)` / `COERCE_DOUBLE(x)` 在 include/pal3/ida_defs.h 里定义为
#   `(*(float*)&(x))` / `(*(double*)&(x))` —— **内部对实参取地址**。
#   而 MSVC6 **不允许对 rvalue 取地址**：最小样例实测
#       `float a = *(float*)&(GetTickCount());`  →  `error C2102: '&' requires l-value`
#   ⇒ 当 Hex-Rays 产出 `COERCE_FLOAT(GetTickCount())`（实测
#      pal3/src/Misc/UI3DCtrl.cpp:384/389）时编译失败。
#   修法：改用 ida_defs.h 里**取值传参的 __forceinline 辅助函数**
#   （形参本身即 lvalue ⇒ 语义等价、零开销）。
#
#   判据是【语法结构】——"实参是不是函数调用"。**正则做不到可靠**：
#   本会话我在正则上连错 4 次（交替顺序、贪婪匹配、把 this->m_x 的 '-' 当运算符、
#   0x10000000i64 的 i64 后缀破匹配）。tree-sitter 直接给出节点类型 ⇒ 无歧义。
def _is_coerce_lvalue(n):
    """[F-CG#15 2026-10-15] 判实参是否左值（`&(x)` 在 MSVC6 合法的前提）。

    保留不动（左值）：identifier / field_expression / subscript_expression /
    qualified_identifier / 解引用 `*p`（pointer_expression op='*'）/ 括号包左值。
    **注释修正**：原注释称"字面量/其它表达式 &(x) 合法"——**有误**（T66-F1 族
    措辞纪律）：只有左值合法；`LODWORD(dt) | 0x100000000i64`（binary_expression）
    实测 C2102 '&' requires l-value。
    """
    t = n.type
    if t in ('identifier', 'field_expression', 'subscript_expression',
             'qualified_identifier'):
        return True
    if t == 'parenthesized_expression':
        inner = [c for c in n.children if c.type not in ('(', ')')]
        return len(inner) == 1 and _is_coerce_lvalue(inner[0])
    if t == 'pointer_expression':
        op = n.child_by_field_name('operator')
        return op is not None and op.text == b'*'
    return False


def transform_coerce_calls(code):
    """把 `COERCE_FLOAT(<rvalue>)` / `COERCE_DOUBLE(<rvalue>)` 改为辅助函数调用。

    [F-CG#15 2026-10-15] 判据从「实参=call_expression」扩为「实参=**非左值**」
    （call/binary/cast/literal/unary/conditional… 即改 helper）；identifier/
    member/subscript/解引用等左值保持原样（最小 churn——既有 51 处用法不动）。
    等价变换：helper 取值传参（形参即 lvalue）与宏的位重解释一致。
    """
    _MAP = {'COERCE_FLOAT': '_pal3_coerce_f32', 'COERCE_DOUBLE': '_pal3_coerce_f64'}
    code_bytes = code.encode('utf-8')
    tree = _parser.parse(code_bytes)
    replacements = []

    def process_node(node):
        if node.type == 'call_expression':
            fn = node.child_by_field_name('function')
            ar = node.child_by_field_name('arguments')
            if fn is not None and ar is not None and fn.type == 'identifier':
                helper = _MAP.get(fn.text.decode('utf-8'))
                if helper:
                    exprs = [c for c in ar.children if c.type not in ('(', ')', ',')]
                    if len(exprs) == 1 and not _is_coerce_lvalue(exprs[0]):
                        replacements.append((fn.start_byte, fn.end_byte, helper))
        for child in node.children:
            process_node(child)

    process_node(tree.root_node)
    result = code_bytes
    for start, end, new_text in sorted(replacements, reverse=True):
        result = result[:start] + new_text.encode('utf-8') + result[end:]
    return result.decode('utf-8')


if __name__ == '__main__':
    # Test
    test_code = """
int CCBRoleState::Update()
{
  CCBRoleState::CheckStatus(this);
  CCBRoleState::ProcessActions(this);
  CCBStage::Update((CCBStage *)this->m_pStage);
  CCBControl::Update(v3);
  sub_4F3020(this, 3);
  return CCBRoleState::UpdateEffects(this);
}
"""
    result = transform_oop_calls(test_code, cls_name='CCBRoleState')
    print('=== cls matches ===')
    print(result)
    print()
    ok = True
    for desc, check in [
        ('this->CheckStatus()', 'this->CheckStatus' in result),
        ('this->ProcessActions()', 'this->ProcessActions' in result),
        ('((CCBStage *)this->m_pStage)->Update', '((CCBStage *)this->m_pStage)->Update' in result),
        ('sub_4F3020 unchanged', 'sub_4F3020(this, 3)' in result),
    ]:
        st = '✅' if check else '❌'
        print(f'{st} {desc}')
        ok = ok and check
    
    # Test with derived class context (base class Method calls)
    test_code2 = """
void CCBControlWindow::_CCBControlWindow()
{
  UIListBox::_UIListBox(this);
}
UIListBox * CCBControlWindow::CreateButton()
{
  PalScript::Create(this, 1879048195, (tagRECT *)pRect, parent);
  UIWnd::Create(this, 1879048196, (tagRECT *)pRect, parent);
  return this;
}
"""
    result2 = transform_oop_calls(test_code2, cls_name='CCBControlWindow')
    print()
    print('=== derived context ===')
    print(result2)
    print()
    for desc, check in [
        ('this->~UIListBox() for dtor', 'this->~UIListBox()' in result2),
        ('No _UIListBox call', 'UIListBox::_UIListBox' not in result2),
        ('PalScript::Create(this,...) kept',
         'PalScript::Create(this, 1879048195' in result2),
        ('UIWnd::Create(...) for base call (avoid shadow)',
         'UIWnd::Create(1879048196' in result2),
        ('NOT this->Create', 'this->Create(1879048196' not in result2),
    ]:
        st = '✅' if check else '❌'
        print(f'{st} {desc}')
        ok = ok and check
    
    status = 'PASSED' if ok else 'FAILED'
    print(f'\nAll: {status}')
