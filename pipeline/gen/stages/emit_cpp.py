"""C++ file generation stage.

Transforms decomp output through the pipeline and emits .cpp files
organized by class and free functions.
"""
import os
import re
from pathlib import Path

from data import store
from stages.transform import run_transforms, make_context
from stages.collect import collect_functions, get_class_dir, CLASS_DIRS

# nullsub functions that are referenced in code but skipped from codegen.
# These need empty function bodies generated in free_functions.cpp.
_nullsub_stubs = set()


# ---------------------------------------------------------------------------
# 无 this 的编译器桩（等价变换：R1 thunk 尾跳）
# ---------------------------------------------------------------------------
# 二进制实证（2026-10-09）：
#   0x509090: e9 0b 00 00 00   jmp  0x5090a0   (5B) + 11 NOP 对齐
#   0x5090a0: a1 88 ff 56 00   mov  eax,ds:0x56ff88 ... 纯全局读写，**全程不读 ecx**
#   0x532a30: fld ds:0x5708ac / fadd st,st / fstp ds:0x17b02e8 / ret  同样不读 ecx
# Hex-Rays 按 ABI（jmp 不改 ecx）把 this 塞给目标 ⇒ 生成 `f(this)`；
# 而 emit 原发 `int f(...);`（可变参）⇒ MSVC6 **不能尾调用** ⇒ 编译成
# `51 E8 .. 59 C3`（push ecx/call/pop ecx/ret，8B）而非 `E9 ..`（jmp，5B）
# ⇒ 破 `data/status/_d1_ledger.md` 的「thunk 契约 = jmp->retn」⇒ 真字节回归
# （CCBStageEffect::PreLoadEffGroup @0x509090 L1→partial）。
#
# 修法（等价变换）：目标不读 ecx ⇒ ① 声明发 `void f(void)` 使 MSVC6 可尾调用
#   ② 调用点去掉多余的 this 实参。二者必须同改，缺一即 C2660。
# 判据（窄）：名字形如 `compiler_init_<hex>` / `compiler_global_init_*` /
#   `_todo_<hex>` / `todo_<hex>`。
_NOARG_STUB_RE = re.compile(
    r'^(?:compiler_init_[0-9A-Fa-f]+|compiler_global_init_\w+|_?todo_[0-9A-Fa-f]+)$')


def _is_noarg_stub(name):
    """编译器桩（不读 ecx ⇒ 无参）—— 判据窄，避免误伤真实函数。

    ⚠️ 阻断级护栏（对抗复核实测 2026-10-09）：`_todo_0047E536` 与 `todo_0047E536`
    是**同一桩的两种渲染**（decomp 吃前导下划线，见
    data/status/_attr_cards_20261009/FINDINGS_post_review.md G1），
    但 `free_functions.h:350-351` 按**带下划线**的拼写声明了 **3 个真参数**
    （DllMain 别名桩）。若只按裸名判"无参桩"，会覆盖注解签名 ⇒ C2660
    （实测 `UITitle_YXXX.cpp:400` / `RoleSystem.cpp:9751` 两文件 COMPILE-SKIP；
     A/B 因果明确：HEAD~1 编译出 .obj、HEAD 失败）。
    ⇒ 必须先按**两种拼写**查 `store.free_func_sigs`，命中即非无参桩。
    """
    if not _NOARG_STUB_RE.match(name):
        return False
    _alt = ('_' + name) if not name.startswith('_') else name.lstrip('_')
    try:
        _sigs = store.free_func_sigs
    except Exception:
        _sigs = {}
    return not (name in _sigs or _alt in _sigs)


def strip_noarg_stub_this_args(code):
    """`<stub>(this[, ...])` → `<stub>([, ...])`。等价：目标不读 ecx。"""
    def _repl(m):
        name, args = m.group(1), (m.group(2) or '').strip()
        if not _is_noarg_stub(name):
            return m.group(0)
        parts = [a for a in args.split(',') if a.strip()]
        if not parts or parts[0].strip() != 'this':
            return m.group(0)
        return '%s(%s)' % (name, ', '.join(p.strip() for p in parts[1:]))
    return re.sub(r'\b([A-Za-z_]\w*)\s*\(([^()]*)\)', _repl, code)


def collect_sub_refs(code):
    """Find all sub_XXXXX and named function references needing forward declaration."""
    # _todo_/todo_ after . or -> are FIELD references, not functions — skip them
    refs = set(re.findall(r'(?<![.>])\b(_todo_[0-9A-Fa-f]+|todo_[0-9A-Fa-f]+)\b', code))
    # sub_ after . or -> are method calls, not free functions — skip them
    refs.update(re.findall(r'(?<![.>])\b(sub_[0-9A-Fa-f]+)\b', code))
    # PascalCase game function calls (not preceded by . or -> or ::)
    for m in re.finditer(
        r'(?<![.>:])\b([A-Z][a-zA-Z0-9_]*'
        r'(?:Update|Init|Create|Destroy|Render|Sort|Check|Process|'
        r'SetState|GetState|Reset|Load|Save|Release|Free|Manager|Info|Cleanup))\s*\(',
        code
    ):
        refs.add(m.group(1))
    # Specific patterns: UIObj_XXX, GetXxxManager_N, etc.
    for m in re.finditer(
        r'(?<![.>:])(?<!\w)\b((?:UIObj_\w+|Get\w+Manager(?:_\d+)?|Texture_Info_\w+|GetGfxManager_\d+))\s*\(',
        code
    ):
        refs.add(m.group(1))
    return refs


def collect_undefined_refs(code):
    """Find likely undefined identifiers that need extern/forward decl."""
    refs = set()
    # IDA string constants: aXxxxx and asc_XXXXX (exclude those replaced by literals)
    refs.update(r for r in re.findall(r'\b(a[A-Z]\w{3,})\b', code)
                if r not in store.literals)
    refs.update(r for r in re.findall(r'\b(asc_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    # IDA unnamed globals (only as identifiers, not those replaced by literals)
    refs.update(r for r in re.findall(r'\b(dword_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(r for r in re.findall(r'\b(byte_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(re.findall(r'\b(word_[0-9A-Fa-f]+)\b', code))
    refs.update(r for r in re.findall(r'\b(flt_[0-9A-Fa-f]+)\b', code)
                if r not in store.literals)
    refs.update(re.findall(r'\b(off_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(unk_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(stru_[0-9A-Fa-f]+)\b', code))
    # pTarget: Hex-Rays synthesized local, NOT declared in decomp JSON's local_vars
    refs.update(re.findall(r'\b(pTarget)\b', code))
    # IDA named but unresolved
    refs.update(re.findall(r'\b(nullsub_\d+)\b', code))
    refs.update(re.findall(r'\b(unknown_libname_\d+)\b', code))
    # 【批 11 全撤（2026-09-29 零回归门）】函数形未声明名收集——生产实测 C2668 +79
    # （`int name(...)` 幻影声明与 free_functions.h 真声明成歧义重载）+C2199/C2059
    # 族 31 真新增。**声明面合成与 free_functions/globals/macros 互连过深**——
    # 三轮 review 全过但生产即爆（review 静态面≠生产实效面第三次实证）。
    # DllMain C2065 挂账【2026-10-06 方案复核翻案订正】：旧叙事"Hex-Rays 别名缓存"是错的——
    # `return DllMain(...)` 的渲染名属于 0x47E536/0x5329BE **另一函数**（jz 尾跳桩
    # `mov eax,1; retn 0xC`）——原名 _DllMain@12_* 无权威源（PAL3 字节串/PDB/FLIRT 三处
    # 零命中）。已按 E 案改名 _todo_+实参形收编（functions.json）。
    return refs


_undeclared_off_globals = set()


def generate_forward_decls(all_code):
    """Generate minimal forward declarations: only what this file actually references."""
    lines = []
    subs = collect_sub_refs(all_code)
    # Detect functions passed to atexit (need void __cdecl(void) signature)
    atexit_funcs = set(re.findall(r'atexit\(\s*(\w+)\s*\)', all_code))

    # free_functions.h is included when free_func_sigs is non-empty,
    # so skip per-file forward declarations for functions already declared there.
    _skip_free_funcs = bool(store.free_func_sigs)

    if subs:
        lines.append("// Forward declarations for unnamed functions")
        for s in sorted(subs):
            if _skip_free_funcs and s in store.free_func_sigs:
                continue
            # Skip if the function has a definition in this file (::sub_XXXX)
            if re.search(r'(?:\w+::)?\b' + re.escape(s) + r'\s*\(', all_code):
                if re.search(r'::' + re.escape(s) + r'\s*\(', all_code):
                    continue
            # Filter out decompiler artifacts: addresses below .text section
            _saddr = None
            _sm = re.match(r'(?:sub|todo|_todo)_([0-9A-Fa-f]+)', s)
            if _sm:
                _saddr = int(_sm.group(1), 16)
            if _saddr is not None and _saddr < 0x401000:
                continue
            # Skip if the function has a definition in this file (::sub_XXXX)
            if re.search(r'(?:\w+::)?\b' + re.escape(s) + r'\s*\(', all_code):
                # Check if there's a definition (:: prefix) not just a declaration
                if re.search(r'::' + re.escape(s) + r'\s*\(', all_code):
                    continue
            if s in atexit_funcs:
                lines.append("void __cdecl %s(void);" % s)
            elif s in store.free_func_sigs:
                lines.append("%s; // from annotations" % store.free_func_sigs[s])
            else:
                if _is_noarg_stub(s):
                    # R1：无 this 编译器桩发 `void f(void)` ⇒ MSVC6 可尾调用成 `jmp`
                    lines.append("void %s(void); // no-arg compiler stub (does not read ecx)" % s)
                else:
                    lines.append("int %s(...);" % s)
        lines.append("")

    # Known free functions referenced in code but not caught by collect_sub_refs
    if not _skip_free_funcs:
        for fname, decl in store.free_func_sigs.items():
            if fname not in subs and re.search(r'\b' + re.escape(fname) + r'\s*\(', all_code):
                if fname not in store.declared_globals:
                    subs.add(fname)
                    lines.append("%s; // from annotations" % decl)
    if lines and lines[-1] != '':
        lines.append("")

    undef = collect_undefined_refs(all_code)
    undef -= store.declared_globals

    _seen_addrs = {}
    for _u in list(undef):
        if _u.startswith('unknown_libname'):
            undef.discard(_u)
            continue
        _ua = store.global_addrs.get(_u)
        if _ua is None:
            _m = re.match(r'(?:dword|byte|word|flt|unk|off|stru)_([0-9a-fA-F]+)', _u)
            if _m:
                _ua = int(_m.group(1), 16)
        if _ua is not None:
            if _ua < 0x580000:
                undef.discard(_u)
                continue
            if _ua >= 0x1897000:
                undef.discard(_u)
                continue
            if _ua in (0x01010101, 0x00FFFFFF, 0x01234567):
                undef.discard(_u)
                continue
            for _base, _end, _, _ in store.struct_instances:
                if _base < _ua < _end:
                    undef.discard(_u)
                    break
        if _u in undef:
            if _ua and any(ga == _ua for gn, ga in store.skip_globals.items()):
                undef.discard(_u)
                continue
            if _u in store.skip_globals:
                undef.discard(_u)
                continue
            if _u in store.globals_map:
                undef.discard(_u)
                continue
        if _ua is not None:
            for _base, _end, _, _ in store.struct_instances:
                if _base < _ua < _end:
                    undef.discard(_u)
                    break

    # Detect off_ variables used as arrays
    off_as_array = set()
    for u in undef:
        if u.startswith('off_'):
            if re.search(r'\b' + re.escape(u) + r'\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*[<>]', all_code):
                off_as_array.add(u)

    # Collect nullsub references for stub body generation in free_functions.cpp
    # Keep them in undef so per-file forward declarations are still emitted.
    for u in list(undef):
        if u.startswith('nullsub_') and u in store.skip_funcs:
            _nullsub_stubs.add(u)

    if undef:
        # 2026-09-27：extern 块里的自定义类类型（如 RoleCameraCtrl）在该 TU
        # 可能无定义 ⇒ extern 不完整类型前置声明（合法且足以链接）。
        # 复核：3 cpp 的 C2146/C2373 即缺此声明。
        _class_type_externs = []
        for u in sorted(undef):
            gt = store.global_types.get(u, '')
            # W3 修 2（复核 695bcbb4，2026-09-28）：**全大写形态=typedef 惯例**
            # （LPCSTR/HWND/HANDLE 族，windows.h 已定义）⇒ 不得发 class 前向声明——
            # 曾把 LPCSTR 当类前向 ⇒ 与 typedef 冲突 = C2040 'class LPCSTR' 族根因。
            if gt and re.match(r'^[A-Z]\w+$', gt) and gt not in ('int', 'float', 'char') \
                    and not gt.isupper():
                _class_type_externs.append((u, gt))
        if _class_type_externs:
            seen_t = set()
            for _u, _t in _class_type_externs:
                if _t in seen_t:
                    continue
                seen_t.add(_t)
                lines.append('class %s;' % _t)
            lines.append('')
        lines.append("// Unnamed globals (extern)")
        for u in sorted(undef):
            if u in atexit_funcs:
                lines.append("void __cdecl %s(void);" % u)
                continue
            if u.startswith('nullsub_'):
                lines.append("void __cdecl %s(...);" % u)
                continue
            # Check if annotated in globals.json (non-IDA globals with semantic names)
            if u in store.annotated_globals:
                _ann_name, _ann_type = store.annotated_globals[u]
                lines.append("extern %s %s;" % (_ann_type, _ann_name))
                continue
            if u in store.global_types:
                gt = store.global_types[u]
                arr_m = re.match(r'^(.+?)(\[\d*\])$', gt)
                if arr_m:
                    lines.append("extern %s %s%s;" % (arr_m.group(1), u, arr_m.group(2)))
                else:
                    lines.append("extern %s %s;" % (gt, u))
            elif u.startswith('flt_'):
                if re.search(r'\b' + re.escape(u) + r'\s*\[', all_code):
                    lines.append("extern float %s[];" % u)
                else:
                    lines.append("extern float %s;" % u)
            # W3 类型源统一（复核 695bcbb4 条件②，2026-09-28）：前缀启发回退**必须走
            # emit_headers._prefix_type 同一函数**——此前本块自带 byte_→'char' 而
            # globals.h 侧是 'unsigned char' ⇒ C2371 redefinition×N。同源后即便
            # globals.h 与就地 extern 同名并存也是**相容重复声明**（无错）。
            elif u.startswith('asc_'):
                lines.append("extern char %s[];" % u)
            else:
                from stages.emit_headers import _prefix_type
                if u.startswith('off_'):
                    _undeclared_off_globals.add(u)      # 保留原状态记账
                _pt = _prefix_type(u) or 'int'
                _is_arr = bool(re.search(r'\b' + re.escape(u) + r'\s*\[', all_code)) \
                    or _pt.endswith('[]')
                _base = _pt[:-2].strip() if _pt.endswith('[]') else _pt
                if _is_arr:
                    lines.append("extern %s %s[];" % (_base, u))
                else:
                    lines.append("extern %s %s;" % (_pt, u))
        lines.append("")

    return '\n'.join(lines)


def _detect_needed_includes(cls_name, methods):
    """Auto-detect additional #include headers needed from code content."""
    header_dir = store.header_dir
    all_code_preview = '\n'.join(m['code'] for m in methods)
    needed_classes = set()

    def _header_exists(name):
        """Check if a class header exists, searching subdirectories."""
        _sub = get_class_dir(name)
        if _sub:
            return (header_dir / _sub / ("%s.h" % name)).exists()
        return (header_dir / ("%s.h" % name)).exists()

    # ClassName:: static calls
    for match in re.finditer(r'\b([A-Z]\w+)::', all_code_preview):
        c = match.group(1)
        if c != cls_name and _header_exists(c):
            needed_classes.add(c)

    # (ClassName *) casts -- accessing members requires full definition
    for match in re.finditer(r'\((\w+)\s*\*+\s*\)', all_code_preview):
        c = match.group(1)
        if c != cls_name and _header_exists(c):
            needed_classes.add(c)

    # Any word matching a known header file name in the code
    known_headers = {f.stem for f in header_dir.rglob("*.h")}
    for match in re.finditer(r'\b([A-Za-z_]\w+)\b', all_code_preview):
        c = match.group(1)
        if c != cls_name and c in known_headers and c not in needed_classes:
            needed_classes.add(c)

    # 2026-09-20 修复（用户指派，A 项）：**函数调用结果的解引用**同样需要完整定义。
    # 形态：`fn(...)->` / `fn()->` / `fn(...)[` —— 即"调用后立即成员访问/取下标"。
    # 返回类型是**已知类**时，必须 include 该类的头；否则生成 `X->member` 而只有前向声明
    # ⇒ `C2027 use of undefined type` + `C2227 left of '->m' must point to class`。
    #
    # 根因案例：`UIAnimateCtrlEX.cpp` 的 `(Role *)&UISceneUpdate()->m_roles[50]`
    # —— 需要完整定义的是 **Scene**，但 `Scene` 在代码里**不出现字面量**，
    # 故原有 4 条启发式（`X::` / `(X *)` / 类名字面量 / globals.h 前向声明）全部漏掉它。
    #
    # 性能：先用**子串**预筛（绝大多数函数名不会出现在本单元），再做正则 ⇒ 每单元只跑几条。
    _sigs = {}
    for _src in (getattr(store, 'free_func_sigs', None) or {},
                 getattr(store, 'method_sigs', None) or {}):
        try:
            _sigs.update(_src)
        except Exception:
            pass
    _DEREF_AFTER_CALL = r'\b%s\s*\([^;\n]{0,240}?\)\s*(?:->|\.|\[)'
    for _fn, _sig in _sigs.items():
        if not _fn or _fn == cls_name or _fn not in all_code_preview:
            continue
        if not re.search(_DEREF_AFTER_CALL % re.escape(_fn), all_code_preview):
            continue
        _rm = re.match(r'\s*(?:struct\s+|class\s+|enum\s+|union\s+)?([A-Za-z_]\w*)\s*(\**)',
                       str(_sig))
        if not _rm:
            continue
        _rt = _rm.group(1)
        if _rt and _rt != cls_name and _rt in known_headers:
            needed_classes.add(_rt)

    # Resolve indirect dependencies: check EACH header we're about to include
    # for forward-declared types. If a type is forward-declared in a header
    # we include AND that type name appears in the code, include its header too.
    # This handles the case where a->b->c needs c.h but only b is directly included.
    fwd_types = set()
    all_included = needed_classes | {cls_name}
    # Also scan globals.h for forward-declared types (included by all .cpp files)
    # AND for extern variable declarations (var name → type mapping)
    _globals_h = header_dir / "globals.h"
    if _globals_h.exists():
        with open(_globals_h, 'r', encoding='utf-8', errors='replace') as _gh:
            _extern_map = {}  # var_name → type_name
            for _hl in _gh:
                # Scan forward declarations: class X;
                _fwd = re.match(r'^\s*class\s+(\w+)\s*;\s*', _hl)
                if _fwd:
                    _t = _fwd.group(1)
                    if _t in known_headers and not _t.startswith('gb'):
                        # Check: exact class name, g_p+Name, or g_+Name in code
                        _in_code = _t in all_code_preview
                        _in_code = _in_code or ('g_p' + _t in all_code_preview)
                        _in_code = _in_code or ('g_' + _t in all_code_preview)
                        # Also check for common shortened prefixes: g_pCBSystem → CCBSystem
                        if _t.startswith('CCB') and 'g_pCB' + _t[3:] in all_code_preview:
                            _in_code = True
                        if _in_code:
                            all_included.add(_t)
                            needed_classes.add(_t)
                # Scan extern declarations: extern Type var_name;
                _ext = re.match(r'^\s*extern\s+(?:(?:class|struct)\s+)?(\w+)\s+(\w+)\s*;', _hl)
                if _ext:
                    _ext_type = _ext.group(1)
                    _ext_var = _ext.group(2)
                    if _ext_type in known_headers and not _ext_type.startswith('gb'):
                        _extern_map[_ext_var] = _ext_type
            # Check if any extern variable is used in the code with member access
            for _var, _typ in _extern_map.items():
                if _typ not in all_included and _var in all_code_preview:
                    all_included.add(_typ)
                    needed_classes.add(_typ)
    # Also add headers included by the class's own header
    _cls_sub = get_class_dir(cls_name)
    cls_hpath = (header_dir / _cls_sub / ("%s.h" % cls_name)) if _cls_sub else (header_dir / ("%s.h" % cls_name))
    if cls_hpath.exists():
        with open(cls_hpath, 'r', encoding='utf-8', errors='replace') as hf:
            for hline in hf:
                inc_m = re.match(r'#include\s+"([^"]*)"', hline)
                if inc_m:
                    inc_stem = inc_m.group(1).split('/')[-1].replace('.h', '')
                    if inc_stem in known_headers:
                        all_included.add(inc_stem)
    # One-level BFS: scan headers we're including for forward-declared types
    for inc_cls in list(all_included):
        _inc_sub = get_class_dir(inc_cls)
        hpath = (header_dir / _inc_sub / ("%s.h" % inc_cls)) if _inc_sub else (header_dir / ("%s.h" % inc_cls))
        if not hpath.exists():
            continue
        with open(hpath, 'r', encoding='utf-8', errors='replace') as hf:
            for hline in hf:
                fwd_m = re.match(r'^\s*class\s+(\w+)\s*;\s*(?://.*)?$', hline)
                if fwd_m:
                    fwd_type = fwd_m.group(1)
                    if fwd_type in known_headers and fwd_type not in all_included \
                            and not fwd_type.startswith('gb'):
                        # Check if the type is used: exact name, member access, or field type
                        _used = fwd_type in all_code_preview
                        # Check if any struct member type matches (e.g., ObjectCamera as field type)
                        if not _used:
                            for _sn, _sm in store.struct_members.items():
                                for _so, (_sfn, _sft) in _sm.items():
                                    if fwd_type in _sft and _sfn in all_code_preview:
                                        _used = True
                                        break
                                if _used:
                                    break
                        if _used:
                            fwd_types.add(fwd_type)
                            all_included.add(fwd_type)
    needed_classes |= fwd_types

    return needed_classes


# ---------------------------------------------------------------------------
# memfnptr ABI 槽赋值修复（P0.5 · T9 · 2026-10-12）
# ---------------------------------------------------------------------------
# 病灶层三问（实测定位）：
#   1. 病灶在 codegen：stage1_structural._find_cc_nodes 递归剥调用约定（本意只剥
#      定义头），把体内 `int (__thiscall **v13)(CEffect *, int)` 的 __thiscall
#      一并剥掉 ⇒ 槽视图坍为 __cdecl fnptr ⇒ `*v13 = CEffect::SetParam` 报 C2440。
#   2. 消费者：MSVC6 编译 .cpp 时读该槽类型（局部声明/类型转换表达式）。
#   3. C2440 只给两端类型，缺「RHS 是 __thiscall 非静态成员函数」这一事实。
# 二进制证据（A 级，objdump CEffCylinder::ProcInitTask @0x4c49e3 附近）：
#   `mov DWORD PTR [esi],edx`（edx=0x4CA400=CEffect::SetParam）后隔 3 条指令才
#   `mov DWORD PTR [esi+0x4],eax` ⇒ 槽是 4 字节裸指针、+4 是独立语句（非 PMF 拷贝）。
# MSVC6 实测（probe_compile 探针，2026-10-12）：
#   `typedef int (__thiscall *FP)(Cls*,int)` ⇒ C4234 非法；PMF↔fnptr 任何 cast 全
#   C2440；**sizeof(成员函数指针)==4**（单继承紧凑形）⇒ 用 PMF 视图存槽与二进制
#   的 4 字节单存一致；`*p = Cls::M`（裸名）与 `p[i]=0` 合法、`(PMF)整数` 非法
#   ⇒ 只能逐赋值点改 LHS 视图，不能整体改声明（整数槽 `v13[2]=(T)2` 会炸）。
# 修法（等价变换，仅动「RHS=__thiscall 成员函数」的赋值行）：
#   `*v13 = CEffect::SetParam;`
#     → `*(int (CEffect::**)(int))v13 = CEffect::SetParam;`        # LHS=*ptr 形
#   `v8 = CCBStage::UpdateTaskNormals;`
#     → `*(int (CCBStage::**)(int))&(v8) = CCBStage::UpdateTaskNormals;`  # LHS=变量形
#   PMF 形参表 = 方法签名去 this 形参；method_sigs 缺项时回退同体局部声明的
#   fnptr 元素型（错误文本 `void (__thiscall gbVFileSystem::*)…` 证明其为非静态成员）。
#   其余语句零改动 ⇒ 字节面不变。
# 实测（2026-10-12，probe 当场读 vs 前态 census）：C2440 389→335 · C2248 75→31
#   （_Tidy 访问面 hack 连带解掉 m_ParamHandle 等私有访问族）· 总错误 1720→1643 ·
#   S2 绿 101/209→106/209（CEffCylinder/CEffMeteor/CEffSParticle/CEffAction/
#   PalScriptIdleObj 五单元归零）· free_functions C1003 最大行号 5193→5205 后移。
#   已知漏网 2 形（非槽赋值，见任务报告）：逗号表达式内赋值 `v8 = Cls::M,` 与
#   实参位置整型 cast `f((unsigned int)Cls::M, …)`。
_TYPE_KEYWORDS = {
    'int', 'char', 'float', 'double', 'void', 'long', 'short', 'bool',
    'unsigned', 'signed', 'const', 'struct', 'class', 'enum', 'union',
    '__int64', '__int32', '__int16', '__int8', 'wchar_t',
    'BYTE', 'WORD', 'DWORD', 'UINT', 'BOOL', 'HANDLE', 'HWND', 'LPVOID',
}


def _strip_param_names(params):
    """形参表 → 纯类型表（去尾部形参名；类型关键字结尾不动）。"""
    out = []
    for p in [x.strip() for x in params.split(',')]:
        if not p:
            continue
        m = re.match(r'^(.*\S)\s+([A-Za-z_]\w*)$', p)
        if m and m.group(2) not in _TYPE_KEYWORDS:
            out.append(m.group(1))
        else:
            out.append(re.sub(r'\*+\s*[A-Za-z_]\w*$',
                              lambda mm: '*' * mm.group(0).count('*'), p))
    return ', '.join(out)


def _memberfn_pmf_type(cls, method, body=None, lhs_var=None):
    """cls::method（__thiscall 非静态成员）⇒ 成员函数指针类型串；定不出返回 None。"""
    sig = store.method_sigs.get('%s::%s' % (cls, method))
    if sig:
        if '__thiscall' not in sig:
            return None                      # static/cdecl 成员：现状可编译，不动
        m = re.match(r'^\s*(.+?)\s*__thiscall\s*\((.*)\)\s*$', sig)
        if m:
            ret = m.group(1).strip()
            plist = [x.strip() for x in m.group(2).split(',') if x.strip()]
            if plist and re.match(r'^[\w:]+\s*\*+\s*(this|_this)$', plist[0]):
                plist = plist[1:]
            return '%s (%s::*)(%s)' % (ret, cls,
                                       _strip_param_names(', '.join(plist)))
        return None
    if body and lhs_var:
        # 回退：同体局部声明的 fnptr 元素型（首参=对象指针 ⇒ 非静态成员）
        dm = re.search(r'^\s*([\w:<>,\s\*&]+?)\s*\(\s*\*+\s*' + re.escape(lhs_var) +
                       r'\s*\)\s*\(([^;]*?)\)\s*;', body, re.M)
        if dm:
            ret = dm.group(1).strip()
            plist = [x.strip() for x in dm.group(2).split(',') if x.strip()]
            pcls = None
            if plist:
                fm = re.match(r'^([\w:]+)\s*\*+', plist[0])
                if fm:
                    pcls = fm.group(1)
                    plist = plist[1:]
            if pcls:
                return '%s (%s::*)(%s)' % (ret, pcls,
                                           _strip_param_names(', '.join(plist)))
    return None


_MEMBERFN_ASSIGN_RE = re.compile(
    r'^(\s*)(\*?\s*[\w\[\]\.()>&\-]+?)\s*=\s*'
    r'((?:[A-Za-z_]\w*::)+[A-Za-z_~]\w*)\s*([;,])', re.M)
# [T14/T9-F-memfnptr] 实参整型 cast 形：`(uint)Cls::M` —— MSVC6 拒绝 PMF↔整型
# 直接 cast（C2440，T9 探针实测）⇒ 等价改写为 pmf_to_u32(Cls::M)（union 位拷贝，
# 单继承 PMF=4 字节纯地址 ⇒ 出参=原地址入参，字节不变；helper 在
# include/pal3/ida_defs.h，全生成单元经该头可见）。仅 __thiscall 成员触发
# （_memberfn_pmf_type 三段判据守卫，静态成员不动）。
_MEMBERFN_INTCAST_RE = re.compile(
    r'\(\s*(?:unsigned\s+int|unsigned|DWORD|int)\s*\)\s*'
    r'((?:[A-Za-z_]\w*::)+[A-Za-z_~]\w*)')


def rewrite_memberfn_slot_assignments(body):
    """RHS=__thiscall 成员函数的槽赋值 ⇒ LHS 视图 cast 成员函数指针指针。"""
    def _repl(m):
        indent, lhs, rhs, term = (m.group(1), m.group(2).strip(),
                                  m.group(3), m.group(4))
        cls, method = rhs.rsplit('::', 1)
        lhs_var = None
        if lhs.startswith('*'):
            lhs_var = re.sub(r'\[.*', '', lhs[1:]).strip()
        pmf = _memberfn_pmf_type(cls, method, body=body, lhs_var=lhs_var)
        if not pmf:
            return m.group(0)               # 定不出类型 ⇒ 不动（禁止猜测）
        pmf_ptr = pmf.replace('::*)(', '::**)(')
        if lhs.startswith('*'):
            target = '*(%s)%s' % (pmf_ptr, lhs[1:].strip())
        else:
            target = '*(%s)&(%s)' % (pmf_ptr, lhs)
        return '%s%s = %s%s' % (indent, target, rhs, term)

    def _repl_cast(m):
        rhs = m.group(1)
        cls, method = rhs.rsplit('::', 1)
        pmf = _memberfn_pmf_type(cls, method, body=body)
        if not pmf:
            return m.group(0)               # 静态/未名 ⇒ 不动
        # 显式 PMF cast 前缀：MSVC6 模板推导对裸成员名（PMF 常量）会退化为
        # fn 形（实测 C2664 'int (int)'→'int (__thiscall *)(int)'）⇒ 显式定型。
        return 'pmf_to_u32((%s)%s)' % (pmf, rhs)

    body = _MEMBERFN_ASSIGN_RE.sub(_repl, body)
    return _MEMBERFN_INTCAST_RE.sub(_repl_cast, body)


# [T9] std::string::_Tidy 是 MSVC6 STL 私有成员（C2248）。二进制里是裸 call
# （等价性要求保留调用本体）⇒ 只能开访问面：本单元先 include <string> 再恢复
# private。纯编译面变换，字节零变化；不丢失任何类型信息。
_STRING_PRIVATE_HACK = (
    '// [T9] std::string::_Tidy private-access workaround (compile-surface only)\n'
    '#define private public\n'
    '#include <string>\n'
    '#undef private\n\n')


def generate_class_cpp(cls_name, methods):
    """Generate .cpp content for a class."""
    lines = []
    header_dir = store.header_dir

    # 先变换全部方法代码：include 检测必须基于变换后的代码
    # （stage2 OOP 解析会引入 Class::Method 形态的类引用）
    methods.sort(key=lambda m: m['addr'])
    transformed = []
    transformed_methods = []
    # 本输出文件共享的 stub 去重集合（同一签名只发射一次定义，避免 C2084/C2371/C2556）
    _stub_reg = set()
    for m in methods:
        ctx = make_context(cls_name, m['method'], sig=m.get('sig', ''),
                           stub_registry=_stub_reg)
        code = run_transforms(m['code'].strip(), ctx)
        code = rewrite_memberfn_slot_assignments(code)   # [T9] memfnptr 槽赋值
        transformed.append((m['addr'], code))
        transformed_methods.append({'code': code, 'method': m['method']})

    # Standard includes
    lines.append('#include "pal3/ida_defs.h"')
    lines.append('#include "globals.h"')
    lines.append('#include "pal3/pal3_constants.h"')
    _cls_subdir = get_class_dir(cls_name)
    _cls_header_subdir = header_dir / _cls_subdir
    header_path = _cls_header_subdir / ("%s.h" % cls_name)
    if header_path.exists():
        if _cls_subdir:
            lines.append('#include "%s/%s.h"' % (_cls_subdir, cls_name))
        else:
            lines.append('#include "%s.h"' % cls_name)

    # Auto-detect additional includes (on TRANSFORMED code)
    needed_classes = _detect_needed_includes(cls_name, transformed_methods)

    # CRT/system types that should never be included
    _SKIP_INCLUDE = {
        '_ThrowInfo', '_CatchableType', '_CatchableTypeArray',
        '_s_ThrowInfo', '_s__ThrowInfo',
        'string', 'exception', 'type_info', 'stdiobuf', 'filebuf',
        'ios_base', 'facet', 'codecvt_base', 'strstreambuf',
    }
    for c in sorted(needed_classes):
        if c.startswith('vtbl_') or c in _SKIP_INCLUDE:
            continue
        _c_subdir = get_class_dir(c)
        if _c_subdir:
            lines.append('#include "%s/%s.h"' % (_c_subdir, c))
        else:
            lines.append('#include "%s.h"' % c)

    # Include free_functions.h if any free function is called or referenced
    free_func_h = header_dir / "free_functions.h"
    if free_func_h.exists() and cls_name != 'free_functions':
        all_code = '\n'.join(m['code'] for m in methods)
        if store.free_func_sigs:
            import re as _re_inc
            for fname in store.free_func_sigs:
                if _re_inc.search(r'\b' + _re_inc.escape(fname) + r'\b', all_code):
                    lines.append('#include "free_functions.h"')
                    break

    lines.append("")

    # Generate forward declarations based on all code in this file
    transformed = [(a, strip_noarg_stub_this_args(c)) for a, c in transformed]
    all_code = '\n'.join(code for _, code in transformed)
    fwd = generate_forward_decls(all_code)
    if fwd:
        lines.append(fwd)

    # Emit transformed code
    for addr, code in transformed:
        lines.append("// %s" % addr)
        lines.append(code)
        lines.append("")

    content = '\n'.join(lines)
    if '_Tidy(' in content:                 # [T9] 私有成员访问面 workaround
        content = _STRING_PRIVATE_HACK + content
    return content


def generate_free_funcs_cpp(funcs):
    """Generate .cpp for free functions."""
    lines = []
    lines.append('#include "pal3/ida_defs.h"')
    lines.append('#include "globals.h"')
    lines.append('#include "free_functions.h"')

    # Scan all function bodies for ClassName:: and (ClassName *) references, add includes
    import re
    all_code_text = '\n'.join(f.get('code', '') for f in funcs)
    referenced_classes = set(re.findall(r'\b([A-Z][A-Za-z0-9_]+)::', all_code_text))
    # Also detect (ClassName *) casts — casting to a class pointer requires full definition
    for m in re.finditer(r'\((\w+)\s*\*+\s*\)', all_code_text):
        c = m.group(1)
        if c[0].isupper():
            referenced_classes.add(c)
    header_dir = store.project_root / "pal3" / "src"
    for cls in sorted(referenced_classes):
        _subdir = get_class_dir(cls)
        hpath = (header_dir / _subdir / ("%s.h" % cls)) if _subdir else (header_dir / ("%s.h" % cls))
        if hpath.exists():
            if _subdir:
                lines.append('#include "%s/%s.h"' % (_subdir, cls))
            else:
                lines.append('#include "%s.h"' % cls)
    lines.append("")
    lines.append("// Free functions (not belonging to any class)")
    lines.append("")

    funcs.sort(key=lambda f: f['addr'])

    # Transform all through the pipeline (as free functions)
    transformed = []
    _stub_reg = set()
    for f in funcs:
        ctx = make_context('', f['name'], sig=f.get('sig', ''), is_free=True,
                           stub_registry=_stub_reg)
        code = run_transforms(f['code'].strip(), ctx)
        code = rewrite_memberfn_slot_assignments(code)   # [T9] memfnptr 槽赋值
        transformed.append((f['addr'], code))

    # Forward declarations
    transformed = [(a, strip_noarg_stub_this_args(c)) for a, c in transformed]
    all_code = '\n'.join(code for _, code in transformed)
    fwd = generate_forward_decls(all_code)
    if fwd:
        lines.append(fwd)

    for addr, code in transformed:
        lines.append("// %s" % addr)
        lines.append(code)
        lines.append("")

    # Nullsub stubs for compiler-generated nop functions referenced in code
    if _nullsub_stubs:
        lines.append("")
        lines.append("// Nullsub stubs (compiler-generated empty bodies)")
        lines.append("")
        for ns in sorted(_nullsub_stubs):
            lines.append("void __cdecl %s(...) {}" % ns)
        lines.append("")

    content = '\n'.join(lines)
    if '_Tidy(' in content:                 # [T9] 私有成员访问面 workaround
        content = _STRING_PRIVATE_HACK + content
    return content


def _emit_free_functions_header(store, header_dir):
    """[R75 修 2026-10-22·对抗复核 must-fix] 单一 free_functions.h 生成函数。

    合并原双写点（预生成无前向声明 + 全量有前向声明）
    => 前向声明恒生成，filter_classes 跑不再留编译破坏态。
    """
    h_lines = ['#pragma once',
               '// Auto-generated: free function forward declarations',
               '#include "pal3/ida_defs.h"', '']
    # Forward declare game struct types used as pointers in signatures
    _SYSTEM_TYPES = {'int', 'void', 'char', 'float', 'double', 'short', 'long',
                     'unsigned', 'const', 'BYTE', 'WORD', 'DWORD', 'UINT', 'BOOL',
                     'LPCSTR', 'LPSTR', 'CHAR', 'HRESULT', 'HANDLE', 'HWND', 'RECT',
                     'FILE', '_DWORD', '_BYTE', '_WORD', 'POINT', 'SIZE',
                     'WPARAM', 'LPARAM', 'LRESULT', 'LCID',
                     'INT_PTR', 'UINT_PTR', 'LONG_PTR', 'ULONG_PTR', 'DWORD_PTR',
                     '__int8', '__int16', '__int32', '__int64',
                     'unsigned __int8', 'unsigned __int16', 'unsigned __int32', 'unsigned __int64'}
    fwd_types = set()
    for fname, decl in store.free_func_sigs.items():
        for m in re.finditer(r'\b(\w+)\s*\*', decl):
            t = m.group(1)
            if t not in _SYSTEM_TYPES:
                fwd_types.add(t)
    if fwd_types:
        for t in sorted(fwd_types):
            h_lines.append('class %s;' % t)
        h_lines.append('')
    for fname, decl in sorted(store.free_func_sigs.items()):
        h_lines.append('%s;' % decl)
    h_lines.append('')
    with open(header_dir / 'free_functions.h', 'w', encoding='utf-8') as f:
        f.write('\n'.join(h_lines))


def run_cpp_generation(filter_classes=None):
    """Main entry point: generate .cpp files from decomp JSONs.

    Always performs full generation (no incremental caching).

    Args:
        filter_classes: If set, only generate these class names.
    """
    output_dir = store.project_root / "pal3" / "src"

    print("Collecting functions from decomp...")
    by_class, free_funcs = collect_functions()

    print("  Classes with methods: %d" % len(by_class))
    print("  Free functions: %d" % len(free_funcs))

    output_dir.mkdir(parents=True, exist_ok=True)
    generated = 0
    total_funcs = 0

    # [R75 修 2026-10-22·对抗复核 must-fix] 合并 free_functions.h 双写点
    # 原双写点：预生成（无前向声明）+ 全量（有前向声明）=> filter_classes 跑即留编译破坏态（102 error）
    # 修：单一 _emit_free_functions_header()，前向声明恒生成
    _header_dir = store.header_dir
    if os.environ.get('EXPORT_FUNC') or os.environ.get('EXPORT_CLASS') or \
       os.environ.get('CODEGEN_CLASS') or os.environ.get('PROBE_ONLY'):
        print('[S3] scoped mode: skip free_functions.h regeneration (keep full)')
    else:
        _emit_free_functions_header(store, _header_dir)

    for cls_name, methods in sorted(by_class.items()):
        if filter_classes and cls_name not in filter_classes:
            total_funcs += len(methods)
            continue

        subdir = get_class_dir(cls_name)
        out_dir = output_dir / subdir
        out_dir.mkdir(parents=True, exist_ok=True)

        # [F-CG#2 防御补丁 2026-10-15] 替换表补 `(`/`)`：collect 侧 name 参数表含 `::`
        # 嵌套型的根因已修（先剥参数表再 rsplit）；此处兜底防文件名再带括号
        safe_name = cls_name.replace('<', '_').replace('>', '_').replace(':', '_').replace('"', '_').replace('?', '_').replace('*', '_').replace('|', '_').replace('\\', '_').replace('/', '_').replace('(', '_').replace(')', '_').strip()
        out_path = out_dir / ("%s.cpp" % safe_name)
        content = generate_class_cpp(cls_name, methods)
        with open(out_path, 'w', encoding='utf-8') as f:
            f.write(content)
        generated += 1
        total_funcs += len(methods)

    # Free functions
    if free_funcs and not filter_classes:
        out_path = output_dir / "free_functions.cpp"
        content = generate_free_funcs_cpp(free_funcs)
        with open(out_path, 'w', encoding='utf-8') as f:
            f.write(content)
        generated += 1
        total_funcs += len(free_funcs)




    print("\nGenerated %d .cpp files (%d functions) in %s" % (
        generated, total_funcs, output_dir))

    # Summary by directory
    for subdir in sorted(set(CLASS_DIRS.values()) | {'Misc'}):
        d = output_dir / subdir
        if d.exists():
            count = len(list(d.glob("*.cpp")))
            if count > 0:
                print("  %s/: %d files" % (subdir, count))

    if _undeclared_off_globals:
        print("\n  [WARN] %d off_ globals without type annotation (undeclared)" % len(_undeclared_off_globals))
