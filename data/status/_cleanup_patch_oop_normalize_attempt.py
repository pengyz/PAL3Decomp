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

    for _f in sorted(os.listdir(_structs_dir)):
        if not _f.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(_structs_dir, _f), encoding='utf-8'))
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
            n = ret_n_at(va)
            if n is not None and n % 4 == 0:
                _RET_SLOTS_CACHE[(cls, mn)] = n // 4
            else:
                _RET_SLOTS_CACHE[(cls, mn)] = None

    # MCP-verified evidence overrides the raw byte-scan. sig_evidence.py
    # extracts ret instructions via IDA disassemble_function (instruction-
    # accurate; the byte-scan above misreads early 0xC2/0xC3 bytes inside
    # function bodies — e.g. conditional returns — as the function tail,
    # which wrongly blocks the explicit-this gate). Pack entries are graded:
    # 'slots' exists only for unanimous, %4==0 rets, so ambiguous callees
    # stay unevidenced and the gate conservatively blocks.
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
                                                    '(((%s *)this))->%s::%s(%s)'
                                                    % (class_name, class_name,
                                                       method_name, rest_str))
                                            else:
                                                # 【2026-09-15 归一化修】原实现在这里只加
                                                # `[MISATTRIBUTED]` 注释、**保持静态调用形式**
                                                # ⇒ 产物 `Cls::M((Cls*)this, ...)` **不合法**
                                                # （非静态成员函数无对象调用 ⇒ C2352/C2660）。
                                                # 实测规模：**C2660 632 条 / 101 个文件**
                                                # （= 71% 的失败文件）都产生于这一支。
                                                #
                                                # 归一化判据（与 Track-1 同源，只加一条）：
                                                # 当 `_t1_retn` 成立（**渲染实参数 == 该方法的
                                                # __thiscall 栈参数数**，即"首参 == this"自洽）
                                                # 时，**对象就是调用者自己的 this**
                                                # ⇒ 用**调用者的类**生成合法且忠实的调用：
                                                #     ((cls_name *)this)->cls_name::M(rest)
                                                # 依据（实测 CCBAttackSequen.cpp:172 → 0x4DB640）：
                                                #   4db667  mov %ecx,%esi   ← 调用者的 this
                                                #   4db669  push $0x0 / 4db66e push %edi
                                                #   4db672  call 0x4db640  ← %ecx 即调用者 this
                                                #   ⇒ 该对象**确实**是调用者实例，
                                                #     IDB 的 `Cls::M` 归属不可信（`_t1_vt` 亦为假）。
                                                # 仍**不**采用 `Cls*`：那会断言一个已被证伪的归属。
                                                if _t1_retn and cls_name:
                                                    new_text = (
                                                        '((%s *)this)->%s::%s(%s)'
                                                        % (cls_name, cls_name,
                                                           method_name, rest_str))
                                                else:
                                                    new_text = (
                                                        '/* [MISATTRIBUTED] %s on %s::this '
                                                        '-> fix IDB name of callee */ %s::%s(%s)'
                                                        % (class_name, cls_name, class_name,
                                                           method_name, _margs))
                                else:
                                    # Normalize the cast to the method's class and
                                    # keep the qualifier: ((Cls*)X)->Cls::M(rest).
                                    # X is an untyped local/global or a member
                                    # subobject address — the call defines the
                                    # this-contract, so this is reconstruction
                                    # (Hex-Rays lost the local's type), not a lie.
                                    new_text = '(((%s *)%s))->%s::%s(%s)' % (
                                        class_name, inner, class_name,
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
                                if _op == '*' and _this_consistent:
                                    new_text = '(%s)->%s::%s(%s)' % (
                                        first_arg_text, class_name,
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
def transform_coerce_calls(code):
    """把 `COERCE_FLOAT(<函数调用>)` / `COERCE_DOUBLE(<函数调用>)` 改为辅助函数调用。

    只改**实参是 `call_expression`**（真正的 rvalue）的情形；
    实参为标识符 / 成员访问 / 字面量 / 其它表达式**一律保持原样**
    （那些在 MSVC6 下 `&(x)` 合法；不动它们可避免影响既有 51 处用法）。
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
                    if len(exprs) == 1 and exprs[0].type == 'call_expression':
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
