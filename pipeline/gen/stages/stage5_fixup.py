"""Stage 5: Compiler compatibility fixups (pure text-level, no AST).

Applies ~20 independent regex/text transformations that make IDA-generated
code compile under MSVC6. Each transformation is self-contained and idempotent.

Topics:
- Type aliases and suffixes
- Algebraic pointer decomposition
- Inline asm fixes (float constants, data labels, MASM hex)
- Static method call conversion
- Register-this alias elimination
- Reference parameter restoration
- Pointer cast fixups for MSVC6 compatibility
- C2440 cast insertion (pointer RHS into DWORD slots, ptr/ptr sign)
- IDA artifact cleanup (null checks, return statements)
- Struct overlap resolution
- Struct global array access fix
"""
import re
import struct as _struct

from data import store


# ============================================================
# Type alias substitution (text-level, STL/GB engine patterns)
# ============================================================

def _apply_text_substitutions(code, ctx):
    """Apply text-level substitutions: type aliases, suffixes, thunk classes."""

    # Normalize IDA __hidden this marker in body text: it now appears inside
    # function-pointer declarators rendered from adopted definite types,
    # e.g. `unsigned int (__thiscall *v21)(Cls *__hidden, int)`. `__hidden`
    # is never valid C++ — global strip is safe (display-convention token).
    code = re.sub(r'\b__hidden\b\s*', '', code)

    # Replace IDA container structures with STL types
    _type_map = {
        'std::_String_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::iterator',
        'std::_String_const_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::const_iterator',
        'std::_String_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::iterator',
        'std::_String_const_iterator<char,std::char_traits<char>,std::allocator<char>>':
            'std::string::const_iterator',
    }
    for old, new in sorted(_type_map.items(), key=lambda x: -len(x[0])):
        code = code.replace(old, new)

    # Replace 'class ' prefix on types used in variable declarations
    code = re.sub(r'\bclass\s+(\w[\w<>,: ]*\w)(\s+(?:\*|&|\w+))', r'\1\2', code)
    code = re.sub(r'class\s+', '', code)
    code = re.sub(r'\bstruct\s+(\w[\w<>,: ]*\w)(\s+(?:\*|&))', r'\1\2', code)

    # thunk class qualifier injection for Stage3 mis-removed ctors
    if ctx.cls_name in store.thunk_classes and ctx.cls_name and not ctx.is_free_function:
        code = code.replace(ctx.method_name, '%s::%s' % (ctx.cls_name, ctx.method_name), 1)

    # Remove redundant 'struct' before template function pointer params
    code = re.sub(r'struct\s+([A-Za-z_]\w*(?:<[^>]*>)?)\s*\(', r'\1 (', code)

    # F80（2026-09-25）：`this = expr` 渲染守卫。Hex-Rays 把"存放 this 的寄存器被
    # 复用"渲染成对 this 的赋值（CEffShock dtor 槽定型时实测 3 处 ⇒ C2106，MSVC6
    # 视 this 不可赋值）。忠实重写 = 函数体内 this 全部换名 _this（Hex-Rays 的
    # 寄存器复用视图），首行注入 `Cls *_this = this;`；签名内的 this 形参不动。
    if ctx.cls_name and not ctx.is_free_function and re.search(r'\bthis\s*=[^=]', code):
        i = code.find('{')
        if i != -1:
            head, body = code[:i + 1], code[i + 1:]
            body = re.sub(r'\bthis\b', '_this', body)
            code = head + ('\n    %s *_this = this;' % ctx.cls_name) + body

    # F82（2026-09-25）：__asm 块内 `符号.x/.y/.z/.w` 烘焙为数字偏移。Hex-Rays 对
    # 浮点指令序列渲染原生 __asm，成员引用（gbVec3D/四元数的 x/y/z/w=0/4/8/12）
    # 在 MSVC6 内联汇编里因符号无 C 声明 ⇒ 成员名歧义 C2410（实测 234 条，集中在
    # ScriptVM/UIScene/RoleSystem 三个封顶单元）。x/y/z/w 布局在两个类里一致；
    # 带名成员（m_xxx）偏移不定，不动（保持诚实账面）。
    _asm_chunks = re.split(r'(__asm\s*\{)', code)
    if len(_asm_chunks) > 1:
        _off = {'x': 0, 'y': 4, 'z': 8, 'w': 12}
        _rebuilt = [_asm_chunks[0]]
        for _i in range(1, len(_asm_chunks), 2):
            _asm_txt = _asm_chunks[_i + 1]
            _end = _asm_txt.find('}')
            _in_asm, _rest = (_asm_txt[:_end], _asm_txt[_end:]) if _end != -1 else (_asm_txt, '')
            _in_asm = re.sub(
                r'(\w+)\.(x|y|z|w)\b',
                lambda m: m.group(1) + ('' if _off[m.group(2)] == 0 else '+%d' % _off[m.group(2)]),
                _in_asm)
            _rebuilt.append(_asm_chunks[_i]); _rebuilt.append(_in_asm); _rebuilt.append(_rest)
        code = ''.join(_rebuilt)

    # C′ R1：别名修复**前置**（F83 前——删 `_ESI = this;` 后 _assigned_regs 不见 ⇒ 无悬挂声明）
    code = _fix_register_this_alias(code)
    # F83（2026-09-25）：寄存器伪名**赋值**⇒ 变量提升。ida_defs.h 把 _EAX 等定义为
    # 字面量 0（只读约定），但 Hex-Rays 在寄存器被复用时渲染 `_EAX = expr` ⇒ 展开
    # 成 `0 = expr`（C2440/C2106，实测 67 处/8 单元；ScriptVM 解封后 +39）。忠实重写 =
    # 体被赋值的伪名全部换名 reg_XX 并首行注入 `unsigned long reg_XX = 0;`
    # （初值 0 保持"赋值前读 0"的旧语义；纯读未赋值的伪名不动，仍走宏常量）。
    # 指针值 RHS 的 cast 由后续 C2440 pass 补（reg_XX 是值局部 ⇒ DWORD 槽路线）。
    _assigned_regs = set(re.findall(r'\b(_E[A-Z]{2})\s*=[^=]', code))
    if _assigned_regs:
        for _p in sorted(_assigned_regs):
            code = re.sub(r'\b%s\b' % _p, 'reg_' + _p[1:], code)
        # 【C′ A（方案复核判 C′·R2 证据序）】别名证据（reg_X = this）⇒ 类型化声明
        # `<Cls> *reg_X = this;`（R3 位移门：[N] 按 sizeof(Cls) 缩放——8692 恒等式证）
        # 无别名证 ⇒ `unsigned long reg_X = 0;`（现行为——R2 末位形态扫描留批）
        _cls = getattr(ctx, 'cls_name', None) if ctx is not None else None
        _decls = []
        for _p in sorted(_assigned_regs):
            _rn = 'reg_' + _p[1:]
            if _cls and re.search(r'\b%s\s*=\s*this\s*;' % re.escape(_rn), code):
                _decls.append('    %s *%s = this;\n' % (_cls, _rn))
            else:
                _decls.append('    unsigned long %s = 0;\n' % _rn)
        _decls = ''.join(_decls)
        _i = code.find('{')
        if _i != -1:
            code = code[:_i + 1] + '\n' + _decls + code[_i + 1:]
        # 【批 5 回退（2026-09-29 零回归门）】cast_reg_assignments 接线撤销——
        # 实测真新增 15（UIScene +13：类值/指针链 RHS 铸坏成员访问 C2227/2228；
        # PAL3 +2：类值铸 C2679；ScriptVM 60→102 级联）⇒ 无条件 `(unsigned long)` 铸
        # 对**类值/指针链 RHS** 不是恒等（显式铸改变重载决议/成员访问语法）。
        # 纯函数+测保留（test_cast_reg_assignments.py）——精确化（类值豁免/型判别铸）
        # 后再接线；40 件 reg_ 指针族留批 F。

    # F84（2026-09-25）：raw vtable 间接调用 `(**(RET (***)(P1,P2))X)(a1,a2)` 与
    # 裸形态 `(**v)(v,a)` 的实参类型合规。Hex-Rays 对无类型槽位渲染该形态——间接
    # 调用 = 字节忠实，必须保留（限定直呼会压制虚机制破坏字节）。实参里的指针
    # 表达式隐式转整型被 MSVC6 拒绝 ⇒ C2664（实测 24 处）。逐实参按 fnptr 声明
    # 参数类型补 cast（取声明文本逐字 cast，位保留，兼容 _DWORD/char* 混合参数表）；
    # 裸形态的参数表从 _build_var_types 的 fnptr 局部声明取。
    # 判定记录（用户质疑驱动）：UIWnd slot0=ShowWindow 标注经函数体反汇编确认
    # 正确（去重消息发送非析构）——cast 是类型系统合规，非洗白；devirt 扩展
    # （非限定虚调用）为后续路线。
    _pos = 0
    _out84 = []
    _vt84 = None
    while True:
        _k = code.find('(**', _pos)
        if _k == -1:
            _out84.append(code[_pos:])
            break
        # 组1：`(**` 之后的平衡组——带型 `((RET (***)(P1,P2))X)` / 裸 `(**NAME)`
        _d = 0; _i1 = _k
        while _i1 < len(code):
            if code[_i1] == '(': _d += 1
            elif code[_i1] == ')':
                _d -= 1
                if _d == 0: break
            _i1 += 1
        if _i1 >= len(code):
            _out84.append(code[_pos:]); break
        _g1 = code[_k:_i1 + 1]
        _pm = re.search(r'\*\*\*\s*\)\s*\(([^()]*)\)', _g1)
        _bare = _pm is None
        if _bare:
            _bm = re.match(r'^\(\*\*\s*(\w+)\s*\)$', _g1)
            if _bm:
                if _vt84 is None:
                    _vt84 = _build_var_types(code, ctx)
                _vi = _vt84.get(_bm.group(1)) or {}
                if _vi.get('kind') == 'fnptr':
                    _pm = re.match(r'^(.*)$', _vi.get('params') or '')
        # 组2：实参表（紧跟包装组闭合后的平衡组）
        _a_open = _i1 + 1
        if _a_open >= len(code) or code[_a_open] != '(':
            _out84.append(code[_pos:_i1 + 1]); _pos = _i1 + 1; continue
        _d = 1; _m = _a_open + 1
        while _m < len(code) and _d > 0:
            if code[_m] == '(': _d += 1
            elif code[_m] == ')': _d -= 1
            _m += 1
        _args = code[_a_open + 1:_m - 1]
        _alist = _split_toplevel(_args)
        if _pm:
            _plist = [x.strip() for x in _pm.group(1).split(',') if x.strip()]
            if len(_plist) == len(_alist):
                _new_args = ', '.join(
                    '(%s)(%s)' % (_plist[i], a.strip()) if a.strip() else a
                    for i, a in enumerate(_alist))
                _out84.append(code[_pos:_a_open + 1])
                _out84.append(_new_args)
                _pos = _m - 1
                continue
        _out84.append(code[_pos:_m]); _pos = _m
    code = ''.join(_out84)

    return code


def _split_toplevel(args):
    """按顶层逗号切分实参串（括号深度感知）。"""
    parts, depth, last = [], 0, 0
    for i, ch in enumerate(args):
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif ch == ',' and depth == 0:
            parts.append(args[last:i]); last = i + 1
    parts.append(args[last:])
    return parts







# ============================================================
# Algebraic decomposition: (char *)this + S*var + C → this->array[var].field
# ============================================================

def _build_array_stride_index():
    idx = {}
    for type_name, members in store.struct_members.items():
        for offset, (mname, mtype) in members.items():
            m = re.match(r'^([\w\s\*]+?)\[(\d+)\]$', mtype.strip())
            if m:
                elem_type = m.group(1).strip()
                arr_count = int(m.group(2))
                _ELEM_SIZES = {
                    'int': 4, 'float': 4, 'unsigned int': 4,
                    'unsigned long': 4, 'char': 1, 'unsigned char': 1,
                    'bool': 1, 'short': 2, 'unsigned short': 2,
                    'double': 8, 'long long': 8,
                }
                elem_sz = _ELEM_SIZES.get(elem_type, 4)
                stride = elem_sz
                for off2, (mn2, mt2) in sorted(members.items()):
                    if off2 > offset and off2 < offset + arr_count * elem_sz:
                        stride = off2 - offset
                        break
                idx.setdefault(type_name, []).append({
                    'name': mname, 'offset': offset, 'stride': stride,
                    'elem_count': arr_count, 'elem_type': elem_type,
                })
    return idx


_ARRAY_STRIDE_INDEX = None


def _get_arrays_for(typename):
    global _ARRAY_STRIDE_INDEX
    if _ARRAY_STRIDE_INDEX is None:
        _ARRAY_STRIDE_INDEX = _build_array_stride_index()
    return _ARRAY_STRIDE_INDEX.get(typename, [])


def _decompose_raw_pointer_arithmetic(code):
    """Convert (char *)this + S*var + C → this->array[var].field pattern."""
    lines = code.split('\n')
    out = []
    for line in lines:
        if 'this' not in line:
            out.append(line)
            continue
        m = re.match(
            r'^(\s*)\*\(\(_BYTE\s*\*\)this\s*\+\s*(\d+)\s*\*\s*(\w+)\s*\+\s*(\d+)\)\s*=\s*(.*);$',
            line
        )
        if m:
            indent, stride, var, base, val = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
            stride_val = int(stride, 0)
            base_val = int(base, 0)
            out.append('%sthis->m_pData[%d * %s + %d] = %s;' % (indent, stride_val, var, base_val, val))
        else:
            out.append(line)
    return '\n'.join(out)


# ============================================================
# Inline asm fixes
# ============================================================

def _fix_asm_float_constants(code):
    """Replace IDA 'ds:1.2f' style float constants with static const variable syntax.
    
    Hex-Rays generates inline float literals like 'ds:1.5f' inside __asm blocks.
    MSVC doesn't support this inline syntax, so we need to extract them.
    """
    floats = set(re.findall(r'ds:(-?\d+\.\d+[eE]?[+-]?\d*)[fF]?', code))
    lines = code.split('\n')
    out = []
    for f in sorted(floats):
        _varname = '_flt_%s' % f.replace('.', '_').replace('-', 'neg').replace('+', 'pos')
        code = code.replace('ds:%sf' % f, _varname)
        code = code.replace('ds:%s' % f, _varname)
    return code


def _fix_asm_data_labels(code):
    """Replace IDA ds:XXXXX references with dword ptr [...] syntax."""
    code = re.sub(r'\bds:([a-zA-Z_]\w*)\b', r'dword ptr [\1]', code)
    code = re.sub(r'\bds:([0-9A-Fa-f]+[hH])\b', r'dword ptr [\1]', code)
    return code


def _fix_asm_hex_ambiguity(code):
    """Fix MASM hex constants like 0E0h → 0xE0 to prevent C parser confusion."""
    def _fix_hex(m):
        digits = m.group(1)
        if digits[0].isdigit() or len(digits) <= 1:
            return '0x' + digits
        return m.group(0)
    code = re.sub(r'\b([0-9A-Fa-f]+)h\b', _fix_hex, code)
    return code


# ============================================================
# Static method call: ((Type*)0)->Method() → Type::Method()
# ============================================================

def _fix_static_method_calls(code):
    """Convert ((ClassName *)0)->Method() to ClassName::Method() for static methods."""
    code = re.sub(
        r'\(\((\w+)\s*\*\)\s*0\)\s*->\s*(\w+)\s*\(',
        r'\1::\2(',
        code
    )
    return code


# ============================================================
# Win32 `ShowWindow` 被继承来的成员**遮蔽** ⇒ 补 `::`
#
# 病灶（2026-09-21，**编译器实测复现** ✓）：
#   `class UIStatic : public UIWnd`，`UIWnd` 有 `virtual int ShowWindow(int nFlags)`
#   ⇒ 成员函数内写 `ShowWindow(g_hMainWnd, 4)` 会命中**继承来的 1 参成员**，
#     Win32 的 `::ShowWindow(HWND, int)` 被遮蔽 ⇒ MSVC：
#       C2660 'ShowWindow' : function does not take 2 parameters
#   （同一调用在命名空间作用域下是 C2065 —— 含 windows.h 时绑定 Win32 ✓）
#
# **为什么安全**：被遮蔽的成员是 **1 参**，故**任何 2 实参**的 `ShowWindow(...)`
# 都不可能是该成员 ⇒ 补 `::` 不改变任何合法调用的语义 ✓。
# `::ShowWindow` 可见性已证明：`include/pal3/ida_defs.h:5` 即 `#include <windows.h>`，
# 且每个生成 .cpp 首位 include 它 ✓。
#
# 实测规模：生成树里**非限定**调用 **11 处，全部 2 实参**，第 2 参为 4/5（`SW_*` 命令常量）✓
# 回归守卫：tests/test_showwindow_qualify.py
# ============================================================

def _split_top_args(args_text):
    """顶层（括号/方括号外）逗号切分（纯函数）。"""
    args, depth, cur = [], 0, ''
    for ch in args_text:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            args.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        args.append(cur.strip())
    return args


def is_win32_showwindow(args_text):
    """**纯函数**：该实参表是否属于 Win32 `::ShowWindow(HWND, int)`（恰 2 实参）。"""
    return len(_split_top_args(args_text)) == 2


def _qualify_win32_showwindow(code):
    """把**非限定**的 2 实参 `ShowWindow(...)` 补成 `::ShowWindow(...)`。

    lookbehind 排除 `\\w`/`>`/`.`/`:` ⇒ `p->ShowWindow(` / `x.ShowWindow(` / `::ShowWindow(` 都不匹配 ✓
    """
    pat = re.compile(r'(?<![\w>:.])ShowWindow\s*\(')
    out, i = [], 0
    while True:
        m = pat.search(code, i)
        if not m:
            out.append(code[i:])
            break
        j = m.end()
        depth, k = 1, j
        while k < len(code) and depth:
            if code[k] == '(':
                depth += 1
            elif code[k] == ')':
                depth -= 1
            k += 1
        if depth:
            out.append(code[i:])
            break
        if is_win32_showwindow(code[j:k - 1]):
            out.append(code[i:m.start()])
            out.append('::ShowWindow(')
            i = m.end()
        else:
            out.append(code[i:m.end()])
            i = m.end()
    return ''.join(out)


# ============================================================
# 显式 this 的类限定调用：`Cls::M(obj, rest...)` → `((Cls *)obj)->M(rest...)`
#
# 病灶层（2026-09-21 已只读验证 ✓）：**Hex-Rays 自己就这么输出** ——
#     CCBControl::SetParam(*(CCBControl **)(... + 8), 513, -1);
#     NPC::UpdateAnim((NPC *)(v3 + 156304));
# 即它把 `__thiscall` 调用建模为"类限定名 + 显式 this 作首实参"。
# codegen 从未把它适配成 C++ 成员调用语法 ⇒ MSVC 报
#     C2660 'SetParam' : function does not take 3 parameters
# 实测规模（基线普查）：**53 条 / 13 个名字**（SetParam 16 · GetCmdData 10 ·
# ProcessKeyboard 10 · UpdateAnim 4 · EndTurnAndAdvance 3 · …）。
#
# **安全闸**：仅当签名是 `__thiscall` **且** `实参数 == 形参数 + 1` 时才改写。
# 该闸天然豁免"声明/定义"站点（它们的实参数恰等于形参数 ✓），也豁免真正的
# static 调用（形参数已对齐 ✓）与签名未知的符号（保守跳过 ✓）。
# 回归守卫：tests/test_explicit_this_call.py（含真实样本与四条反面样本）
# ============================================================

def _sig_arity(sig):
    """`'int __thiscall(int a, char *b)'` → `(2, True)`；取不到 → `(None, False)`。

    返回值 = (形参数, 是否 `__thiscall`)。参数里的括号/逗号按配平处理。
    """
    if not sig or '__thiscall' not in sig:
        return None, False
    m = re.match(r'^\s*(.*?)\s*\((.*)\)\s*$', sig)
    if not m:
        return None, False
    inner = m.group(2).strip()
    if inner in ('', 'void'):
        return 0, True
    if inner == '...':
        return None, True                       # 可变参 ⇒ 元数不限，不改写
    depth, n, saw = 0, 1, False
    for ch in inner:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif ch == ',' and depth == 0:
            n += 1
        if not ch.isspace():
            saw = True
    return (n if saw else 0), True


def rewrite_explicit_this_call(cls, method, args_text, sig):
    """**纯函数**：`Cls::M(a1, a2, …)` 的实参文本 + 声明签名 → 替换文本；不该改 ⇒ None。

    只在"签名是 `__thiscall` 且 实参数 == 形参数 + 1"时改写，
    并把首实参识别为 this：`((Cls *)a1)->M(a2, …)`。
    顶层逗号切分（括号/方括号内不切），故实参含函数指针 cast 也安全。
    """
    decl, is_thiscall = _sig_arity(sig)
    if not is_thiscall or decl is None:
        return None
    args, depth, cur = [], 0, ''
    for ch in args_text:
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        if ch == ',' and depth == 0:
            args.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        args.append(cur.strip())
    if not args or len(args) != decl + 1:
        return None
    obj = args[0]
    rest = ', '.join(args[1:])
    return '((%s *)%s)->%s(%s)' % (cls, obj, method, rest)


def _fix_explicit_this_calls(code, sig_lookup=None):
    """扫描并改写显式 this 的类限定调用（`sig_lookup(Cls, M) -> sig|None`）。

    ⚠️⚠️ **尚未接线（已实现 + 19 项单测，但不被 run() 调用）** —— 2026-09-21 实测：
    安全闸所需的"形参数"若取自 `store.method_sigs`（**decomp 侧**签名），与
    **生成头（注解侧）声明**会不一致 ⇒ 两类独立误伤（真实样本见 tests/）：

    * ① `A->Cls::M(explicit_this, args)`：对象是**前缀**，首实参不是 this
      ⇒ 改写后成双解引用链 `A->((Cls *)B)->M(...)`，`CCBSystem.cpp` 35→102 条错；
    * ② **函数定义头** `BOOL Cls::CreateObj(3 参)`：decomp 侧记 2 参 ⇒ 被改写成
      `BOOL ((Cls *)CCBUI **ppUI)->CreateObj(...)` ⇒ C2199/C2143/C2447。

    ① 已由下方 `CHAIN` 守卫修掉；② 的根治前提是**元数取自注解声明**（编译器实际读的那份）
    —— 正是"先验证消费者实际读哪份声明"这条纪律的又一实例。
    实测净效应（带①的守卫）：C2660 **0**、总错误 2150→2152 ⇒ 发布门禁拦下，故不接线。
    """
    if sig_lookup is None:
        def sig_lookup(c, m):
            return store.method_sigs.get('%s::%s' % (c, m))
    pat = re.compile(r'\b([A-Za-z_]\w*)::([A-Za-z_]\w*)\s*\(')
    CHAIN = ('>', '.', ':')          # `->` / `.` / `::` 之后 ⇒ 对象是前缀，不改写
    out, i = [], 0
    while True:
        m = pat.search(code, i)
        if not m:
            out.append(code[i:])
            break
        j = m.end()                                  # 位于 '(' 之后
        depth, k = 1, j
        while k < len(code) and depth:
            if code[k] == '(':
                depth += 1
            elif code[k] == ')':
                depth -= 1
            k += 1
        if depth:                                    # 括号不配平 ⇒ 不碰
            out.append(code[i:])
            break
        prev = code[i:m.start()].rstrip()            # 只看本段内、紧邻的非空字符
        if prev and prev[-1] in CHAIN:
            out.append(code[i:m.end()])
            i = m.end()
            continue
        args_text = code[j:k - 1]
        repl = rewrite_explicit_this_call(m.group(1), m.group(2), args_text,
                                          sig_lookup(m.group(1), m.group(2)))
        if repl is None:
            out.append(code[i:m.end()])
            i = m.end()
        else:
            out.append(code[i:m.start()])
            out.append(repl)
            i = k
    return ''.join(out)


# ============================================================
# Register-this alias: _REG = this; _REG->x → this->x
# ============================================================

def _fix_register_this_alias(code):
    """C′ R1（复核判须修订·别名恢复）：寄存器 this 别名改写——**全用法形**改 this，
    赋值删除（F83 前置运行 ⇒ 无 _ESI 赋值则无悬挂声明）。
    前版只改 `alias->` 形 ⇒ `alias[1].x`/`(T*)alias`/`alias+C` 悬挂（C2228/C2109 57 件根因）。"""
    m = re.search(r'^\s*(\w+)\s*=\s*this\s*;\s*$', code, re.MULTILINE)
    if m:
        alias = m.group(1)
        a = re.escape(alias)
        # 全用法形改写（R1 收窄——复核 R3 位移门）：`->`/`(T*)` 形改 this（安全）；
        # `+=`/`[` 形**不动**（stride/可赋性——`(char*)this +=` 语法炸实证 MatrixStack C2106）
        # 保留赋值 ⇒ F83 声明路径接管（后续 C′ A 受限定型）
        code = re.sub(r'\b' + a + r'\s*->', 'this->', code)
        code = re.sub(r'\(\s*([\w\s:*]+?)\s*\*\s*\)\s*' + a + r'\b(?!\s*\[)', r'(\1 *)this', code)
        # 赋值保留（仅当别名有 `+=`/`[` 残留用法时——否则删除（无用声明））
        if re.search(r'\b' + a + r'\s*(?:\+=|\[)', code):
            pass                       # 保留 `alias = this;`（F83 接管声明）
        else:
            code = re.sub(r'\s*' + a + r'\s*=\s*this\s*;\s*', '\n', code)
    return code


# ============================================================
# Reference parameter restoration (gbengine &param fix)
# ============================================================

_GB_REF_PARAM_FUNCS = {
    'Translate': {0}, 'Scale': {0},
    'LeftTranslate': {0}, 'RightTranslate': {0},
    'MakeMatrix': {0, 1, 2}, 'IntersectPlane': {0, 1},
    'IsColAABB': {0}, 'IsColOBB_H': {0},
    'IsColPoint': {0}, 'IsColQuad': {0, 1, 2},
    'IsColSphere': {0}, 'IsColTriangle': {0, 1, 2, 3},
    'GetAABBox': {0}, 'GetSphere': {0}, 'GetCollideOBB': {0},
    'SetPosition': {0}, 'GetPosition': {0}, 'SetVelocity': {0},
    'SetOrientation': {0}, 'SetListenerPosition': {0},
    'SetListenerOrientation': {0, 1}, 'GetListenerPosition': {0},
    'PushMessage': {0}, 'PopMessage': {0},
    'GetViewport': {0}, 'GetViewSizeOnNearPlane': {0, 1},
    'GetViewPort': {0, 1, 2, 3},
    'PointWorldToScr': {1, 2},  # (gbVec3D*, float&, float&)
    'GetBlend': {0}, 'SetBlend': {0},
    'RightMultiply': {0},
    # 【B 修（方案复核判须修订）】PAU/AAU 分流（gbengine_registry 签名 A 级证）：
    # 指针形出表（gbMatrix4::Rotate(gbVec3D const*,gbVec3D*)=PAU 出；gbOBBox::IsColOBB
    # (gbOBBox*)=PAU 出）——裸名键拆限定键（同名跨类形参形态相反：指针/引用混同=病灶根因）
    'gbMatrixStack::Rotate': {2: {1}, 1: {0}},  # (float,gbVec3D&) 2 元 ref@1；
    #   (gbQuaternion&) 1 元 ref@0 ——元数感知（_ref_positions 按实参数选位）
    'gbRay::IsColOBB': {0}, 'gbPlane::IsColOBB': {0},   # (gbOBBox&) 引用形留表
}

# F81（2026-09-25）：引用参数的**实参类型**（SDK 头权威，include/gbengine）。
# 供 Case 2b 把 `*stru_XXXX`（无型数据全局被解引用作引用实参）重写为
# `*(T *)&stru_XXXX` —— MSVC6 的 T& 只绑同型左值，无 T 则 C2100。
# 键 (func, arg_idx)；未录入的组合保持原行为（保守不变）。返回类型差异
# （如 RightMultiply 的 gbMatrix4/gbQuaternion 两载）不录入，防错型。
_GB_REF_PARAM_TYPES = {
    ('gbMatrixStack::Rotate', 1): 'struct gbVec3D',  # B 修键随迁（失配致 Case2b 不触发 C2100 +24 实证）
    ('Translate', 0): 'struct gbVec3D',     # :158 Translate(gbVec3D&)
    ('Scale', 0): 'struct gbVec3D',         # :154 Scale(gbVec3D&)
    ('LeftTranslate', 0): 'struct gbVec3D', # gbengine_types.h:128
    ('RightTranslate', 0): 'struct gbVec3D',
    ('MakeMatrix', 0): 'struct gbVec3D',    # gbengine_types.h:131
    ('MakeMatrix', 1): 'struct gbVec3D',
    ('MakeMatrix', 2): 'struct gbVec3D',
    ('LeftMultiply', 0): 'struct gbMatrix4',
    ('IntersectPlane', 0): 'struct gbVec3D',  # gbengine_types.h:197
    ('IntersectPlane', 1): 'struct gbVec3D',
    ('IsColAABB', 0): 'struct gbAABBox',
    ('gbRay::IsColOBB', 0): 'struct gbOBBox', ('gbPlane::IsColOBB', 0): 'struct gbOBBox',
    ('IsColOBB_H', 0): 'struct gbOBBox',
    ('IsColQuad', 0): 'struct gbVec3D',
    ('IsColQuad', 1): 'struct gbVec3D',
    ('IsColQuad', 2): 'struct gbVec3D',
    ('IsColSphere', 0): 'struct gbSphere',
    ('IsColTriangle', 0): 'struct gbVec3D',
    ('IsColTriangle', 1): 'struct gbVec3D',
    ('IsColTriangle', 2): 'struct gbVec3D',
    ('IsColTriangle', 3): 'struct gbVec3D',
}

# NOTE (F1b): 'SetAxisAngle': {0} was WRONG and has been deleted.
# `gbengine/gbengine.def` (authoritative, compiler-emitted mangled names):
#   ?SetAxisAngle@gbQuaternion@@QAEXPAUgbVec3D@@M@Z  -> (gbVec3D *, float)  = POINTER
#   ?SetAxisAngle@gbMatrix4@@QAEXPAUgbVec3D@@M@Z     -> (gbVec3D *, float)  = POINTER
#   ?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@M@Z       -> (gbAxis, float)
#   ?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@MM@Z      -> (gbAxis, float, float)
# `PAU` = pointer, not `AAU` = reference — contradicting the `Translate`/`Rotate`
# family this table was built for.  Treating arg 0 as a reference (a) stripped a
# required `&`, and (b) for the static form `Cls::SetAxisAngle(&this_, axis, f)`
# it consumed the `this` argument and shifted every later argument by one.
# Deleting the entry makes the pass leave `SetAxisAngle` alone, restoring the
# decompiler's own `&` (e.g. `SetAxisAngle(&v4, 0, angle)`).

# Local kinds that are positive evidence the identifier is NOT a `T` pointed at
# by the reference parameter (see the F1a gate in `_fix_single_ref_arg`).
_NON_POINTER_LOCAL_KINDS = frozenset(('value', 'array', 'fnptr'))


def _fix_ref_params(code, ctx=None):
    """Fix arguments passed to functions that take reference params.

    Two cases handled:
    1. Hex-Rays outputs &arg for reference params  → strip &:
       obj->Translate(&vec)   → obj->Translate(vec)
    2. Hex-Rays passes a pointer/cast-pointer to a reference param → add *:
       obj->GetAABBox(pBox)   → obj->GetAABBox(*pBox)
       obj->Translate((T*)&x) → obj->Translate(*(T*)&x)

    `ctx` is threaded in only to supply local-declaration evidence for the
    Case 3 gate in `_fix_single_ref_arg`; omitting it degrades to the legacy
    (evidence-free) behaviour.
    """
    vt = _build_var_types(code, ctx) if ctx is not None else {}
    for func_name, ref_indices in _GB_REF_PARAM_FUNCS.items():
        # B 修：限定键（`Cls::fn`）与裸名双形——限定形按全名匹配（类消歧），
        # 元数感知值（dict{arity:set}）按实参数选位（gbMatrixStack::Rotate 双载）
        if '::' in func_name:
            pattern = re.escape(func_name) + r'\s*\('
        else:
            pattern = r'(?:->|::|\.)' + re.escape(func_name) + r'\s*\('
        def _ref_positions(nargs, ref_idx=ref_indices):
            if isinstance(ref_idx, dict):
                return ref_idx.get(nargs, set())
            return ref_idx
        pos = 0
        result = []
        while True:
            m = re.search(pattern, code[pos:])
            if not m:
                result.append(code[pos:])
                break
            call_start = pos + m.end()
            result.append(code[pos:call_start])
            depth = 1
            arg_start = call_start
            arg_idx = 0
            i = call_start
            # B 修：元数预数（dict 形 ref_indices 需 arity 定位）
            if isinstance(ref_indices, dict):
                _d, _j, _na = 1, call_start, 1
                while _j < len(code) and _d > 0:
                    _c = code[_j]
                    if _c == '(':
                        _d += 1
                    elif _c == ')':
                        _d -= 1
                    elif _c == ',' and _d == 1:
                        _na += 1
                    _j += 1
                ref_positions = ref_indices.get(_na, set())
            else:
                ref_positions = ref_indices
            while i < len(code) and depth > 0:
                ch = code[i]
                if ch == '(':
                    depth += 1
                elif ch == ')':
                    depth -= 1
                    if depth == 0:
                        arg = code[arg_start:i]
                        if arg_idx in ref_positions:
                            arg = _fix_single_ref_arg(arg, vt, ref_type=_GB_REF_PARAM_TYPES.get((func_name, arg_idx)))
                        result.append(arg)
                        result.append(')')
                        break
                elif ch == ',' and depth == 1:
                    arg = code[arg_start:i]
                    if arg_idx in ref_positions:
                        arg = _fix_single_ref_arg(arg, vt, ref_type=_GB_REF_PARAM_TYPES.get((func_name, arg_idx)))
                    result.append(arg)
                    result.append(', ')
                    arg_idx += 1
                    arg_start = i + 1
                i += 1
            pos = i + 1
        code = ''.join(result)
    return code


def _fix_single_ref_arg(arg, vt=None, ref_type=None):
    """Fix a single argument for a reference parameter.

    Case 1: starts with '&'  → strip '&'
    Case 2: cast-to-pointer  → add '*' before the cast: (T*)x → *(T*)x
    Case 2b (F81): `*IDA-artifact global` with known ref type → *(T *)&global
    Case 3: plain identifier  → add '*':  pBox → *pBox  **only with evidence**

    Case 3 evidence gate (F1a).  Case 3 used to fire on the *text shape*
    alone (`^\\s*\\w+\\s*$`), which double-applies the `&`-strip that stage 3
    already performed on the SAME table:

        decomp `Rotate(v10, &v15)`  --stage3 Case1-->  `Rotate(v10, v15)`
                                    --stage5 Case3-->  `Rotate(v10,  *v15)`  (C2100)

    The generated text carries a reproducible fingerprint of this: the extra
    `', '` separator emitted by `_fix_ref_params` plus Case 3's preserved
    leading whitespace yields a DOUBLE space — `Rotate(v10,  *v15)`.  A
    decompiler-authored `*v15` would give a single space.

    The fix requires positive evidence from this function's own declarations
    (`_build_var_types`, the same table the C2440 fixer uses):

      * `ptr`               → keep the legacy `*`  (e.g. `Translate(*v5)`
                              where `gbVec3D *v5;` — genuinely a pointer)
      * `value`/`array`/
        `fnptr`             → leave the bare identifier alone.  `&`-stripping
                              is what produced this shape, so the reference
                              argument is the object itself (`Rotate(…, v15)`
                              with `struct gbVec3D v15; // BYREF`).
      * unknown (globals,
        members, …)         → keep the legacy `*` — conservative, no change.

    This is an equivalence-preserving transform, not invention: the verdict
    comes from declarations already present in the same function text.
    """
    arg_stripped = arg.lstrip()
    # Case 1: &arg → arg
    if arg_stripped.startswith('&') and not arg_stripped.startswith('&&'):
        return arg_stripped[1:]
    # Case 2: cast-to-pointer  (Type *)expr  or  (Type *)__thiscall
    cast_m = re.match(r'^(\s*\([^)]*\*\)\s*)', arg)
    if cast_m:
        return '*' + arg
    # Case 2b (F81): `*无型数据全局` 作引用实参 —— Hex-Rays 对未定型 stru_/dword_
    # 等全局渲染裸解引用，MSVC6 的 T& 只绑同型左值 ⇒ C2100。用被调方 SDK 头的
    # 参数类型重写为 `*(T *)&全局`（同一对象的再解释绑定，语义等价）。
    deref_m = re.match(r'^\s*\*\s*((?:stru|byte|word|dword|flt|dbl|unk)_[0-9A-Fa-f]+)\s*$', arg)
    if deref_m and ref_type:
        return '*(%s *)&%s' % (ref_type, deref_m.group(1))
    # Case 3: plain identifier (simple variable name, NOT numeric constants)
    ident_m = re.match(r'^(\s*)(\w+)\s*$', arg)
    if ident_m and not ident_m.group(2).isdigit():
        vt = vt or {}
        kind = (vt.get(ident_m.group(2)) or {}).get('kind')
        if kind in _NON_POINTER_LOCAL_KINDS:
            # Positive evidence this is not a pointer: the `&` stage 3 removed
            # was the reference-taking one.  Leave the object expression.
            # 【批 E】array 形补 [0]（Camera:165 pTarget gbVec3D[2]→gbVec3D& C2664
            # 缺角）：数组实参绑引用=首元素绑定，`arg[0]` 与基址传递字节等价。
            if kind == 'array':
                return ident_m.group(1) + ident_m.group(2) + '[0]'
            return arg
        # F81b: the identifier is an already-typed global - decide based on the emitted type. Example: stru_17A7E78 is
        # `struct gbVec3D` in globals.h (object not pointer), and the reference binding of Rotate(_, gbVec3D&)
        # wants the object itself => bare name; only pointer slots (`T *`) get `*` added.
        if ref_type:
            _gt = (store.global_types.get(ident_m.group(2)) or '').strip()
            if _gt:
                _norm = lambda t: re.sub(r'^(?:struct|class|enum|union)\s+', '', t.strip())
                if not _gt.endswith('*') and _norm(_gt) == _norm(ref_type):
                    return arg  # object-type global: bare name binds reference
                # 【批 E】全局数组型→引用参：`gbVec3D [2]` 形补 [0]（同局部 array 分支）
                if re.match(r'^%s\s*\[[0-9]+\]$' % re.escape(_norm(ref_type)), _norm(_gt)):
                    return ident_m.group(1) + ident_m.group(2) + '[0]'
                if _gt.endswith('*'):
                    return ident_m.group(1) + '*' + ident_m.group(2)
        return ident_m.group(1) + '*' + ident_m.group(2)
    # Unknown pattern — leave unchanged to be safe
    return arg


# ============================================================
# C2440 fixups: MSVC6 strictness — pointer RHS into DWORD slots,
# and pointer/pointer assignment mismatches.
# ============================================================

# Element/pointee bases whose slots receive raw address bits (DWORD slots).
_DWORD_SLOT_BASES = frozenset((
    'unsigned long', 'unsigned int', '_DWORD', 'DWORD', 'long', 'int',
))

# Calls returning pointers that are not in decomp signatures (Win32/CRT).
_PTR_RETURN_FUNCS = frozenset((
    'operator new', 'GetDlgItem', 'malloc', 'calloc', 'realloc',
    'LocalAlloc', 'GlobalAlloc', 'HeapAlloc',
    'LoadIcon', 'LoadCursor', 'LoadBitmap', 'LoadMenu',
))

# IDA auto-named globals whose bare reference yields a pointer (address):
# byte_/off_/stru_/flt_/dbl_/asc_ name arrays/functions/data whose value in
# expression position is the address itself. word_/dword_ are VALUES → not here.
_IDA_PTR_GLOBAL_RE = re.compile(r'^(?:byte|off|stru|flt|dbl|asc)_[0-9A-Fa-f]+$')

# LHS forms that denote a DWORD slot (each alternative is anchored to the
# '=' that follows it, so == / != / >= can never match):
#   LODWORD(x) / BYTE1(x) / HIWORD(x) ...  — IDA byte/word/dword slot macros
#   *((_DWORD *)X + N) =       — DWORD slot by index
#   *(_DWORD *)X =             — DWORD slot by address
_SLOT_LHS_RE = re.compile(
    r'\b(?:LO|HI)?(?:BYTE|WORD|DWORD)[0-9]?\s*\([^()]*\)\s*=(?!=)'
    r'|\*\s*\(\s*\(\s*(?:_DWORD|unsigned long|unsigned int)\s*\*\s*\)[^;=]*?\)\s*=(?!=)'
    r'|\*\s*\(\s*(?:_DWORD|unsigned long|unsigned int)\s*\*\s*\)[^;=]+?\s*=(?!=)'
)

# Cast-to-pointer prefix: (T *), (unsigned int **), (int (__cdecl *)...)
_CAST_PTR_RE = re.compile(
    r'^\(\s*[A-Za-z_][\w:]*(?:\s+(?:unsigned|signed|long|short|char|int|double|float))*\s*'
    r'(?:__cdecl|__stdcall|__thiscall)?\s*\*+\s*\)'
)

_DECL_KEYWORDS = frozenset(('return', 'goto', 'case', 'delete', 'new', 'else', 'sizeof'))


def _split_top_commas(s):
    parts, depth, cur = [], 0, []
    for ch in s:
        if ch in '(<[':
            depth += 1
        elif ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(''.join(cur))
            cur = []
        else:
            cur.append(ch)
    if cur:
        parts.append(''.join(cur))
    return parts


def _build_var_types(code, ctx):
    """Map local/param names to declared types for pointer-ness decisions.
    批 8 修（vt 跨函数混淆）：同名多 kind ⇒ 标 ambiguous（判别保守 False——
    不按别的函数的声明裁决本函数表达式）。"""
    vt = {}
    # fnptr locals:  int ( **v12)(CEffect *, int);
    for m in re.finditer(r'^\s+([A-Za-z_]\w*)\s*\(\s*(\*+)\s*(\w+)\s*\)\s*\(([^()]*)\)\s*;',
                         code, re.M):
        vt[m.group(3)] = {'kind': 'fnptr', 'ret': m.group(1).strip(),
                          'params': m.group(4), 'stars': len(m.group(2))}
    # pointer locals:  UIButton *pButton;  unsigned char *v2;
    for m in re.finditer(r'^\s+((?:(?:unsigned|signed|const|struct|class|enum)\s+)*[A-Za-z_]\w*)'
                         r'\s*(\*+)\s*(\w+)\s*;', code, re.M):
        if m.group(1) not in _DECL_KEYWORDS:
            vt.setdefault(m.group(3), {'kind': 'ptr', 'base': m.group(1),
                                       'stars': len(m.group(2))})
    # value locals:  int v10;  unsigned long v3;  unsigned long reg_EDI = 0;（含初始化）
    # 批 7（2026-09-29）：初始化形补——F83 注入的 `unsigned long reg_X = 0;` 此前不入 vt
    # ⇒ reg_ 族 C2440 精确铸不触发（三判别器仅 vt 间隙，实测定位）
    for m in re.finditer(r'^\s+((?:(?:unsigned|signed|const|struct|class|enum)\s+)*[A-Za-z_]\w*)'
                         r'\s+(\w+)\s*(?:=\s*[^;]+)?;', code, re.M):
        if m.group(1) not in _DECL_KEYWORDS:
            vt.setdefault(m.group(2), {'kind': 'value', 'base': m.group(1), 'stars': 0})
    # array locals:  unsigned long v10[4];  (element type = base)
    for m in re.finditer(r'^\s+((?:(?:unsigned|signed|const|struct|class|enum)\s+)*[A-Za-z_]\w*)'
                         r'\s+(\w+)\s*\[[^\]]+\]\s*;', code, re.M):
        if m.group(1) not in _DECL_KEYWORDS:
            vt.setdefault(m.group(2), {'kind': 'array', 'base': m.group(1), 'stars': 0})
    # parameters from ctx.sig: "... __cc(Cls *this, int nVal)"
    sig = getattr(ctx, 'sig', '') or ''
    pm = re.search(r'__(?:thiscall|cdecl|stdcall)\s*(?:[A-Za-z_][\w:]*\s*)?\((.*)\)\s*$', sig)
    if pm:
        for p in _split_top_commas(pm.group(1)):
            p = p.strip()
            if not p or p == 'void':
                continue
            nm = re.search(r'(\w+)\s*(?:\[[^\]]*\])?\s*$', p)
            if not nm:
                continue
            name = nm.group(1)
            if name == 'this':
                continue  # `this` is never an assignable local; assigning to
                # it (Hex-Rays ctor artifact) must stay uncast
            # base = param text without the name (else the name leaks into
            # synthesized casts, e.g. `(Cls *this *)`)
            base = p[:nm.start()].strip() or p
            # array params decay to pointers
            is_ptr = '*' in p or '[' in p
            vt.setdefault(name, {'kind': 'ptr' if is_ptr else 'value',
                                 'base': base, 'stars': max(p.count('*'), 1)})
    return vt


_MEMBER_TYPE_INDEX = None


def _member_type(cls, member):
    """Declared type of a struct member, or None."""
    global _MEMBER_TYPE_INDEX
    if _MEMBER_TYPE_INDEX is None:
        idx = {}
        for type_name, members in store.struct_members.items():
            for _off, (mname, mtype) in members.items():
                idx.setdefault(type_name, {})[mname] = mtype
        _MEMBER_TYPE_INDEX = idx
    return _MEMBER_TYPE_INDEX.get(cls, {}).get(member)


def _call_return_type(name):
    """Return-type text for 'Cls::Method' or 'Func', or None if unknown."""
    sig = store.method_sigs.get(name)
    if sig is None:
        sig = store.free_func_sigs.get(name)
    if not sig:
        return None
    m = re.match(r'^(.*?)\s*__(?:thiscall|cdecl|stdcall)\b', sig)
    if not m:
        return None
    return re.sub(r'^virtual\s+', '', m.group(1).strip()) or None


def _strip_outer_parens(e):
    e = e.strip()
    while e.startswith('('):
        depth = 0
        for i, ch in enumerate(e):
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth == 0:
                    if i == len(e) - 1:
                        e = e[1:i].strip()
                    else:
                        return e
                    break
        else:
            return e
    return e


_GLOBAL_BASE_TYPE_MAP = None


def _global_base_type(name):
    """Struct type of a named global instance (g_X), or None."""
    global _GLOBAL_BASE_TYPE_MAP
    if _GLOBAL_BASE_TYPE_MAP is None:
        m = {}
        for _base, _end, gname, gtype in store.struct_instances:
            m[gname] = gtype
        _GLOBAL_BASE_TYPE_MAP = m
    return _GLOBAL_BASE_TYPE_MAP.get(name)


def _path_is_pointer(path, vt, ctx):
    """Resolve a member access path like g_X.a.b / this->m_x / p->a.b.

    Returns True/False when decidable, None when any link is unknown.
    """
    parts = re.split(r'(?:->|\.)', path.strip())
    if len(parts) < 2:
        return None
    parts = [re.sub(r'\s*\[[^\]]*\]', '', p).strip() for p in parts]
    base = parts[0]
    if base == 'this':
        cls = ctx.cls_name
    else:
        cls = _global_base_type(base)
        if not cls:
            t = vt.get(base)
            if t and t.get('base'):
                cls = t['base']
    if not cls:
        return None
    for member in parts[1:]:
        if not member:
            return None
        mt = _member_type(cls, member)
        if mt is None:
            return None
        mt = str(mt).strip()
        if '*' in mt:
            return True
        cls = re.sub(r'\s*\[[^\]]*\]\s*$', '', mt)
    return False


def _expr_is_pointer(e, vt, ctx):
    """Positive-only pointer detection.

    Returns True only when pointer-ness is provable from expression text +
    declarations; unknown forms return False (no cast inserted — a cast on a
    float/int RHS would silently change semantics, e.g. float→ulong converts
    the value instead of copying bits).
    """
    e = _strip_outer_parens(e)
    if not e:
        return False
    c0 = e[0]
    if c0 == '"' or c0 == '&':
        return True
    if c0 == '*':
        # *(T **)expr — 解引用"指针的指针"型 cast，结果必为指针（cast 内 ≥2 颗星）。
        # 注意 *(T *)expr 结果是 T 值（一颗星），不可判定，不在此列。
        m2 = re.match(r'\*\s*\(\s*[\w\s:]*\*\s*\*[\s\*]*\)', e)
        if m2:
            return True
        m = re.match(r'\*\s*(\w+)', e)
        if m:
            t = vt.get(m.group(1))
            return bool(t) and t['kind'] in ('ptr', 'fnptr')
        return False
    if _CAST_PTR_RE.match(e):
        return True
    m = re.match(r'^(%s)\b' % '|'.join(sorted(_PTR_RETURN_FUNCS)), e)
    if m:
        return True
    # qualified member call anywhere in the expression
    m = re.search(r'([A-Za-z_]\w*)::([A-Za-z_]\w*)\s*\(', e)
    if m:
        ret = _call_return_type('%s::%s' % (m.group(1), m.group(2)))
        return bool(ret) and '*' in ret
    # unqualified call at expression start
    m = re.match(r'([A-Za-z_]\w*)\s*\(', e)
    if m and '::' not in e:
        n = m.group(1)
        if n in _PTR_RETURN_FUNCS:
            return True
        ret = _call_return_type(n)
        return bool(ret) and '*' in ret
    # multi-level member path, with optional trailing subscripts:
    #   g_RoleSlotBuf.m_partyActor.m_pEquipAtt1[352 * n + 1]
    # (mid-path subscripts allowed; resolved after part-splitting)
    m = re.match(r'([\w>.\-\[\]]+?)\s*(?:\[[^\]]*\])+\s*$', e)
    if m:
        pt = _path_is_pointer(m.group(1), vt, ctx)
        if pt is not None:
            return pt
    if re.search(r'(?:->|\.)', e):
        pt = _path_is_pointer(e, vt, ctx)
        if pt is not None:
            return pt
    # subscript: base[...] keeps the base's pointer-ness
    m = re.match(r'(\w+)\s*\[', e)
    if m:
        t = vt.get(m.group(1))
        return bool(t) and t['kind'] in ('ptr', 'fnptr')
    # plain identifier
    m = re.match(r'^(\w+)$', e)
    if m:
        if _IDA_PTR_GLOBAL_RE.match(m.group(1)):
            return True
        t = vt.get(m.group(1))
        return bool(t) and t['kind'] in ('ptr', 'fnptr')
    # top-level +/- : pointer arithmetic preserves pointer-ness
    # 【批 8 回退（2026-09-29 零回归门）】箭头豁免/单星=值/歧义保守三修件全撤——
    # 生产实测真新增 2（SceneObj L292 撤载重铸 C2440 复发；CEffCustomShape L32 撤载重铸
    # 新失败）——"冗余铸"主张被生产证伪：(unsigned long) 对**指针 RHS 是载重**（隐式
    # 转换本非法）⇒ 撤铸方向不安全。教训：**撤铸同样不是恒等**（与批 5 补铸陷阱对偶）。
    depth = 0
    for i, ch in enumerate(e):
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif ch in '+-' and depth == 0 and i > 0 and e[i - 1] not in 'eE':
            return _expr_is_pointer(e[:i], vt, ctx)
    return False


def _needs_parens(e):
    """True when a cast placed at the START of `e` would bind only to the
    first operand instead of the whole expression (top-level binary op)."""
    depth = 0
    prev = None  # last non-whitespace char seen
    for i, ch in enumerate(e):
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif depth == 0 and ch in '+-*/%&|^':
            if ch == '-' and i + 1 < len(e) and e[i + 1] == '>':
                pass  # '->' arrow operator, not subtraction
            elif prev is not None and (prev.isalnum() or prev in '_)]'):
                return True  # binary operator (operand before it)
        if ch not in ' \t':
            prev = ch
    return False


def _scan_rhs_end(line, start):
    """End of the assignment RHS: first ; , ) at bracket-depth 0."""
    depth = 0
    i = start
    while i < len(line):
        ch = line[i]
        if ch in '([':
            depth += 1
        elif ch in ')]':
            if depth == 0:
                return i
            depth -= 1
        elif ch in ';,' and depth == 0:
            return i
        i += 1
    return i


def _fix_line_dword_slots(line, vt, ctx):
    if '=' not in line:
        return line
    cand = []
    for m in _SLOT_LHS_RE.finditer(line):
        # 槽位构造若位于未闭合 '[' 之内 ⇒ 它其实在下标表达式里（假阳性，
        # 如 `arr[3 * *(_DWORD *)&x] = rhs` 的真实左值是 arr），不得插 cast。
        if line.count('[', 0, m.start()) > line.count(']', 0, m.start()):
            continue
        # m.end() is right after the assignment '='
        p = m.end()
        while p < len(line) and line[p] in ' \t':
            p += 1
        cand.append(p)
    for m in re.finditer(r'\b(\w+)\s*\[[^\]]*\]\s*=(?!=)', line):
        t = vt.get(m.group(1))
        if t and t.get('kind') in ('ptr', 'array') and t.get('base') in _DWORD_SLOT_BASES:
            p = m.end()
            while p < len(line) and line[p] in ' \t':
                p += 1
            cand.append(p)
    if not cand:
        return line
    inserts = []
    for p in sorted(set(cand)):
        rhs_end = _scan_rhs_end(line, p)
        rhs = line[p:rhs_end]
        if rhs.strip().startswith('(unsigned long)'):
            continue
        if _expr_is_pointer(rhs, vt, ctx):
            inserts.append(p)
    if not inserts:
        return line
    out = line
    for p in reversed(inserts):
        rhs_end = _scan_rhs_end(out, p)
        rhs = out[p:rhs_end]
        cast = '(unsigned long)'
        if _needs_parens(rhs):
            cast += '(%s)' % rhs
            out = out[:p] + cast + out[rhs_end:]
        else:
            out = out[:p] + cast + out[p:]
    return out


# ============================================================
# NOTE: explicit-this static-call rewriting (`Cls::M(obj, rest)` →
# `((Cls *)obj)->Cls::M(rest)`) deliberately does NOT live here.
# Call-form policy is single-sourced in ast_transform.transform_oop_calls
# (the OOP stage), which already has the first-arg branches and the
# ret-N evidence gate. Stage 5 is text-level compatibility fixups only.
# ============================================================


def _fix_line_plain_var_assign(line, vt, ctx):
    """Statement `ident = RHS;` where the LHS is a declared local/param:

    - LHS pointer decl + provably-pointer RHS (different pointee): insert a
      cast to the LHS declared type — pointer→pointer, byte-neutral.
    - LHS DWORD-width value decl + provably-pointer RHS: insert (unsigned long)
      — the mirror of the slot rule (ptr → 32-bit int slot).
    """
    m = re.match(r'^(\s*)([A-Za-z_]\w*)\s*=(?!=)\s*', line)
    if not m:
        return line
    t = vt.get(m.group(2))
    if not t:
        return line
    rhs_start = m.end()
    rhs_end = _scan_rhs_end(line, rhs_start)
    rhs = line[rhs_start:rhs_end]
    if rhs.strip().startswith('('):
        return line
    # 2026-09-26：`vN = sub_XXXX(...);`——自由函数（无名 sub_）的返回类型
    # _expr_is_pointer 无签名可证（Hex-Rays 只在 C 语义下省略 void*→T* 的
    # cast，重导出后返回型变的站点触发 C2440）。此时 Hex-Rays 省略 cast
    # 本身即指针兼容证据 ⇒ 直接以 LHS 声明类型插 cast（指针→指针，字节中性）。
    if not _expr_is_pointer(rhs, vt, ctx):
        if t.get('kind') == 'ptr' and re.match(r'^sub_[0-9A-Fa-f]+\s*\(', rhs):
            base = t.get('base')
            if base and re.match(r'^[A-Za-z_][\w:]*$', base):
                cast = '(%s %s)' % (base, '*' * max(t.get('stars', 1), 1))
                if _needs_parens(rhs):
                    rhs = '(%s)' % rhs
                return line[:rhs_start] + cast + rhs + line[rhs_end:]
        return line
    if _needs_parens(rhs):
        rhs_wrapped = '(%s)' % rhs
    else:
        rhs_wrapped = rhs
    if t.get('kind') == 'ptr' and t.get('base'):
        base = t['base']
        # only build casts from clean type texts (defense against name leaks)
        if not re.match(r'^[A-Za-z_][\w:]*(?:\s+(?:unsigned|signed|const|long|short|int|char'
                        r'|double|float|struct|class|enum|__int8|__int16|__int32|__int64))*$', base):
            return line
        cast = '(%s %s)' % (base, '*' * max(t.get('stars', 1), 1))
        return line[:rhs_start] + cast + rhs_wrapped + line[rhs_end:]
    if t.get('kind') == 'value' and t.get('base') in _DWORD_SLOT_BASES:
        return line[:rhs_start] + '(unsigned long)' + rhs_wrapped + line[rhs_end:]
    return line


_SDK_MEMBER_INDEX = None

def _sdk_member_type(cls, member):
    """SDK（gbengine）类的成员声明类型，来自 include/gbengine/*.h（SoT）。

    ida_structs 不含 SDK 类（DLL 导入侧），成员类型只能从头文件本身取。
    按行解析 `float ScaleX; // +0x30` 形态的成员声明。不可知返回 None。
    """
    global _SDK_MEMBER_INDEX
    if _SDK_MEMBER_INDEX is None:
        import os as _os
        idx = {}
        root = _os.path.dirname(_os.path.dirname(_os.path.dirname(
            _os.path.dirname(_os.path.abspath(__file__)))))
        gdir = _os.path.join(root, 'include', 'gbengine')
        if _os.path.isdir(gdir):
            for fn in sorted(_os.listdir(gdir)):
                if not fn.endswith('.h'):
                    continue
                cur = None
                for ln in open(_os.path.join(gdir, fn), encoding='utf-8',
                               errors='replace'):
                    cm = re.match(r'(?:class|struct)\s+(?:GBAPI\s+)?(\w+)', ln)
                    if cm and '{' in ln:
                        cur = cm.group(1)
                        continue
                    dm = re.match(r'\s+(?:GBAPI\s+|static\s+|mutable\s+)*'
                                  r'([A-Za-z_][\w:]*(?:\s+)*\**)\s+(\w+)\s*(?:\[[^\]]*\])?\s*;',
                                  ln)
                    if dm and cur and not ln.strip().startswith(('virtual', '//')):
                        t = dm.group(1).strip()
                        if t and t not in ('return', 'class', 'struct'):
                            idx.setdefault(cur, {})[dm.group(2)] = t
        _SDK_MEMBER_INDEX = idx
    return _SDK_MEMBER_INDEX.get(cls, {}).get(member)


def _member_type_path(path, vt, ctx):
    """沿 `base->m1.m2` 路径解析最终成员的声明类型文本；不可知返回 None。"""
    parts = re.split(r'(?:->|\.)', path.strip())
    parts = [re.sub(r'\s*\[[^\]]*\]', '', p).strip() for p in parts]
    base = parts[0]
    if base == 'this':
        cls = ctx.cls_name
    else:
        t = vt.get(base)
        if not t or not t.get('base'):
            return None
        cls = t['base']
    mt = None
    for member in parts[1:]:
        if not member:
            return None
        # ida_structs 优先；SDK 类（DLL 导入侧不在 IDB）落 gbengine 头索引
        mt = _member_type(cls, member)
        if mt is None:
            mt = _sdk_member_type(cls, member)
        if mt is None:
            return None
        mt = re.sub(r'\s*\[[^\]]*\]\s*$', '', str(mt).strip())
        cls = mt
    return mt


def _inline_single_use_fpu_vars(code, ctx):
    """单用途 FPU 伪变量内联（FPU 批次，2026-09-26）。

    Hex-Rays 对 x87 寄存器变量恒物化成具名局部（`float v2; // st7`），但原始
    编译器让值全程驻留 x87 寄存器、fstp 直落最终目标——物化局部会让 VC6 多出
    栈槽（帧尺寸 +4/+8 ⇒ 全帧偏移错位）和多余的 fld/fstp 对。当变量恰好
    单定义、单使用、且 def→use 区间无线性外分支时，把定义表达式代入使用点并
    删除声明/定义行——VC6 随后把表达式直接算进 fstp，与原始同形。
    """
    lines = code.split('\n')
    # 收集 FPU 伪变量声明行: `  float v2; // st7`
    decl_re = re.compile(r'^(\s*)(float|double)\s+(v[A-Za-z0-9_]+);\s*//\s*st(\d+)\s*$')
    changed = True
    while changed:
        changed = False
        # 函数边界守卫（列 0 非空行 = 新顶层块起点）：var 的 decl/def/use 必须同块。
        # fid 必须在每轮 while 内重算——删除行后 lines 位移，陈旧 fid 会让后续
        # 匹配跨函数错配（UICamera C2065 事故）。
        # 标签行（`LABEL_33:`）在函数【内部】但位于列 0，会把一个函数劈成多个块
        # ⇒ def/use 计数漏数误删（StateUI C2065 事故）——fid 增量必须跳过标签行。
        fid = []
        _c = 0
        for _ln in lines:
            if _ln and not _ln[0].isspace() and _ln.strip() \
                    and not re.match(r'^[A-Za-z_][A-Za-z0-9_]*:\s*$', _ln):
                _c += 1
            fid.append(_c)
        for i, ln in enumerate(lines):
            dm = decl_re.match(ln)
            if not dm:
                continue
            var = dm.group(3)
            blk = fid[i]
            # 唯一定义行
            def_re = re.compile(r'^(\s*)%s\s*=(?!=)\s*(.+?);\s*$' % re.escape(var))
            defs = [(j, def_re.match(l2)) for j, l2 in enumerate(lines)
                    if fid[j] == blk and def_re.match(l2)]
            defs = [(j, mm) for j, mm in defs if mm]
            if len(defs) != 1:
                continue
            j, dmm = defs[0]
            if j < i:
                continue
            # 使用点按【出现次数】计数（`v12 * v12` 一行两次使用曾因按行计数
            # 被误判单用，count=1 替换后第二个 v12 成孤儿 ⇒ C2065），恰一次才内联
            use_re = re.compile(r'\b%s\b' % re.escape(var))
            uses = [(k, len(use_re.findall(l2))) for k, l2 in enumerate(lines)
                    if k not in (i, j) and fid[k] == blk and use_re.search(l2)]
            if sum(c for _, c in uses) != 1:
                continue
            k = uses[0][0]
            if k < j:
                continue
            # def→use 区间必须线性（无分支/标签），且期间不得再引用 var
            region = lines[j+1:k]
            if any(re.match(r'^\s*(if|for|while|switch|do|goto)\b|:\s*$', r2) for r2 in region):
                continue
            if any(use_re.search(r2) for r2 in region):
                continue
            expr = dmm.group(2).strip()
            # 纯度守卫：表达式含函数调用（可能有副作用）时不允许跨语句位置搬运
            # （def 在分支外、use 在分支内的内联会把调用搬进/搬出执行路径）
            if re.search(r'\w+\s*\(', expr):
                continue
            lines[k] = use_re.sub('(%s)' % expr, lines[k], count=1)
            del lines[j]
            lines.pop(i)
            changed = True
            break
    return '\n'.join(lines)


def _fix_float_literal_form(code, ctx):
    """浮点字面量形态（FPU 批次组件 3.5，2026-09-26）。

    Hex-Rays 把 x87 中间值默认定型 double，赋给 float 目标时表达式仍渲染成
    double 域（`fv = 32.0 / (double)x;`）⇒ VC6 发 fdivr qword + qword 常量
    编码，而原始是 float 域（fdivr dword + dword 常量——原始 x87 内存操作
    数尺寸即本规则的二进制证据）。当赋值目标为 float 局部变量时，把 RHS 的
    无后缀浮点字面量改写为最近 float 的 f 后缀字面量、`(double)` cast 改
    `(float)`——改写后 VC6 重新发出 float 编码，且字面量位型与原始一致。
    范围：单行赋值，目标是 **float 局部变量**（vt 表）或 **float 类型成员**
    （`path->member` / `path.member`，经 _member_type 沿路径解析成员类型）。
    """
    import struct as _struct
    vt = _build_var_types(code, ctx)
    out = []
    _NUM = re.compile(r'(?<![\w.])(\d+\.\d+(?:[eE][+-]?\d+)?)(?![fF\w])')

    def _lhs_is_float(lhs_text):
        m2 = re.match(r'^([A-Za-z_]\w*)$', lhs_text)
        if m2:
            t = vt.get(m2.group(1))
            return bool(t) and t.get('base') == 'float'
        # 成员路径 `a->b.c` / `this->m_x`——最终成员声明类型为 float 即改写
        # （类型证据：ida_structs / gbengine SDK 头）；_path_is_pointer 的
        # None（路径不可知）不拦 SDK 类，直接由 _member_type_path 裁决。
        m2 = re.match(r'^([A-Za-z_][\w>.\-\[\]]*(?:->|\.)([A-Za-z_]\w*))\s*$', lhs_text)
        if m2:
            mt = _member_type_path(m2.group(1), vt, ctx)
            return bool(mt) and mt.strip() == 'float'
        return False

    for line in code.split('\n'):
        # 注意：不要在 match 里消费 RHS（如 `([^=].*)$`）——m.end() 之后的
        # 文本才是 RHS，吞掉会导致空 RHS 无字面量可改。
        m = re.match(r'^(\s*)(.+?)\s*=(?!=)\s*', line)
        if m:
            if _lhs_is_float(m.group(2).strip()):
                rhs_start = m.end()
                rhs = line[rhs_start:]

                def _to_f32(mo):
                    try:
                        val = float(mo.group(1))
                        f32 = _struct.unpack('f', _struct.pack('f', val))[0]
                        return repr(f32) + 'f'
                    except Exception:
                        return mo.group(0)

                new_rhs = _NUM.sub(_to_f32, rhs)
                if '(double)' in new_rhs:
                    new_rhs = new_rhs.replace('(double)', '(float)')
                if new_rhs != rhs:
                    line = line[:rhs_start] + new_rhs
        out.append(line)
    return '\n'.join(out)


def _fix_c2440_casts(code, ctx):
    """Insert explicit casts where Hex-Rays relies on implicit pointer
    conversions MSVC6 rejects (C2440).

    Family 1 — pointer-valued RHS written into DWORD slots (LODWORD(...),
    BYTE1(x), *((_DWORD*)X+N), *(_DWORD*)X, ulong* element): insert
    (unsigned long). Pointer→ulong is a bit-preserving no-op on x86, so the
    cast is byte-neutral. Only positively-identified pointer RHS get casts.
    Family 2 — statement assignments: &-rooted or otherwise provably-pointer
    RHS into a differently-typed pointer local → cast to LHS declared type;
    pointer RHS into a DWORD-width value local → (unsigned long).
    """
    vt = _build_var_types(code, ctx)
    out = []
    for line in code.split('\n'):
        line = _fix_line_dword_slots(line, vt, ctx)
        line = _fix_line_plain_var_assign(line, vt, ctx)
        out.append(line)
    return '\n'.join(out)

def _fix_ulong_uint_cast(code):
    """Add explicit casts for unsigned long* → unsigned int* conversions.
    
    x86 safe: both are 32-bit, but MSVC6 requires explicit cast. Fixes IDA
    function pointer type inference errors.
    """
    _fixes = {
        'unsigned long *': 'unsigned int *',
    }
    for old, new in _fixes.items():
        code = code.replace(old, new)
    return code


def _fix_operator_new_cast(code):
    """Add explicit casts for operator new return values.

    MSVC6 does not allow implicit void* → T* conversion.
    Pattern: var = operator new(size);
    Fix:     var = (T *)operator new(size);

    Looks up variable type from declarations in the same function body.
    Falls back to (char *) if type not found.
    """
    # Build a map of variable names → pointer types from declarations
    # Matches:  Type *var;  or  Type *var = ...;  or  Type *var, ...
    var_types = {}
    for m in re.finditer(r'^\s+([\w:]+(?:\s+\w+)*)\s+\*\s*(\w+)', code, re.MULTILINE):
        var_types[m.group(2)] = m.group(1).strip()

    def _replace_new(m):
        prefix = m.group(1)  # whitespace + "var = "
        var_match = re.search(r'(\w+)\s*=\s*$', prefix)
        if var_match:
            var_name = var_match.group(1)
            typ = var_types.get(var_name)
            if typ:
                return '%s(%s *)operator new(' % (prefix, typ)
        # Fallback: cast to char * (always compatible with pointer types)
        return '%s(char *)operator new(' % prefix

    code = re.sub(r'^(\s+\w+\s*=\s*)operator new\(', _replace_new, code, flags=re.MULTILINE)
    return code


# ============================================================
# struct_instances overlap resolution: dword_XXXX.member → cast
# ============================================================

def _resolve_stru_overlap(code):
    """Replace stru_XXXX.member[N] with (cast to containing struct) access.

    Only rewrites stru_XXXX in *value position* (start of an expression).
    When stru_XXXX is itself a MEMBER name (e.g. an embedded struct member
    in SceneMgr named after its address: g_SceneMgr.stru_C059A0.m_retry),
    it is already legal C++ and must NOT be cast-rewritten — hence the
    negative lookbehind blocking '.', '->' and word chars before it.
    """
    for base, end, gname, gtype in store.struct_instances:
        _stru_name = 'stru_%X' % base
        _pattern = r'(?<![.>\w])' + _stru_name + r'\.([a-zA-Z_]\w*(?:\[\d+\])?)'
        _replacement = r'((%s *)&%s)->\1' % (gtype, gname)
        code = re.sub(_pattern, _replacement, code)
    return code


# ============================================================
# Main entry
# ============================================================

def _run_inner(code, ctx):
    """Stage 5: compiler compatibility fixups (text-level, no AST)."""
    # Strip __noreturn (VC6 doesn't support this IDA attribute)
    code = re.sub(r'\b__noreturn\s*(?=\()', '', code)

    # Strip 'virtual' from free function definitions (not valid for non-member functions)
    if ctx.is_free_function:
        code = re.sub(r'\bvirtual\s+', '', code)

    # Strip Hex-Rays j_ thunk class scope from member calls:
    #   obj->j_ClassName::Method() → obj->Method()
    # These are IDA decompiler artifacts — the binary has a direct call,
    # Hex-Rays incorrectly inserts the thunk class name as scope qualifier.
    # Only affects call sites (-> form), not function definitions.
    code = re.sub(r'->j_([A-Z]\w*)::', '->', code)

    # Strip j_ prefix from thunk-qualified casts:
    #   ((j_NPC *)nVal)->NPC::Method() → ((NPC *)nVal)->NPC::Method()
    # The explicit qualified call target is unchanged, so the cast type
    # spelling is cosmetic.
    code = re.sub(r'\(j_([A-Z]\w*)\s*\*', r'(\1 *', code)

    # Strip Hex-Rays mangled name decorations in qualified method calls:
    #   obj->Class::?method@namespace@@...() → obj->Class::method()
    #   obj->?method@namespace@@...()        → obj->method()
    # The ?...@...@...@... suffix is MSVC mangling that leaks through
    # when Hex-Rays can't resolve the call target.
    code = re.sub(r'::\?(\w+)@[A-Za-z0-9_@]+(?=\()', r'::\1', code)
    code = re.sub(r'->\?(\w+)@[A-Za-z0-9_@]+(?=\()', r'->\1', code)

    # Replace compiler-generated _scalar_dtor calls with equivalent expressions.
    # _scalar_dtor(this, 1) = delete + destructor = delete this
    # _scalar_dtor(this, 0) = destructor only = ~ClassName(this) -- handled by dtor body
    # _scalar_dtor may have address suffix (_scalar_dtor_XXXX)
    code = re.sub(r'(\w+)\s*->\s*_scalar_dtor\w*\s*\(\s*(\w+)\s*,\s*1\s*\)', r'delete \1', code)
    # also handle single-param form: _scalar_dtor(char deleting)
    code = re.sub(r'(\w+)\s*->\s*_scalar_dtor\w*\s*\(\s*1\s*\)', r'delete \1', code)
    code = re.sub(r'(\w+)\s*->\s*_scalar_dtor\w*\s*\(\s*0\s*\)', r'', code)

    # _sdtor_call_dtor is an alternate name for the scalar deleting destructor
    # generated by some Hex-Rays versions (same semantics as _scalar_dtor).
    # Also handles: _sdtor_N (address-suffixed), dot access (.), arrow (->).
    for _dtor_pat in (r'_sdtor_call_dtor', r'_sdtor_\w+'):
        code = re.sub(r'(\w+)\s*->\s*' + _dtor_pat + r'\s*\(\s*(\w+)\s*,\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*\.\s*' + _dtor_pat + r'\s*\(\s*(\w+)\s*,\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*->\s*' + _dtor_pat + r'\s*\(\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*\.\s*' + _dtor_pat + r'\s*\(\s*1\s*\)', r'delete \1', code)
        code = re.sub(r'(\w+)\s*->\s*' + _dtor_pat + r'\s*\(\s*0\s*\)', r'', code)
        code = re.sub(r'(\w+)\s*\.\s*' + _dtor_pat + r'\s*\(\s*0\s*\)', r'', code)

    # UIScene::GetSys is a static method but Hex-Rays calls it without scope.
    code = re.sub(r'(?<!::)\bGetSys\s*\(', 'UIScene::GetSys(', code)

    # Win32 `ShowWindow` 被继承来的 1 参成员遮蔽 ⇒ 非限定的 **2 实参**调用补 `::`
    # （机制由真实 MSVC6 编译复现；安全性见该函数上方注释；11 处真实站点全部 2 实参）
    code = _qualify_win32_showwindow(code)

    # Text-level substitutions (type aliases, suffixes, thunk classes)
    code = _apply_text_substitutions(code, ctx)

    # VC6 doesn't know C99/C++11 integer literal suffixes LL/ULL/ll/ull.
    # The MSVC-specific equivalent is i64/ui64. Same 64-bit constant, same
    # generated code bytes. (Removing the suffix would change semantics:
    # constants wider than 32 bits would be truncated by VC6.)
    code = re.sub(r'\b([0-9][0-9a-fA-FxX]*)[uU][lL]{2}\b', r'\1ui64', code)
    code = re.sub(r'\b([0-9][0-9a-fA-FxX]*)[lL]{2}\b', r'\1i64', code)

    # Algebraic decomposition: (char *)this + S*var + C → this->array[var].field
    code = _decompose_raw_pointer_arithmetic(code)

    # ASM fixups
    code = _fix_asm_float_constants(code)
    code = _fix_asm_data_labels(code)
    code = _fix_asm_hex_ambiguity(code)

    # Static method call conversion
    code = _fix_static_method_calls(code)

    # ⚠️ `_fix_explicit_this_calls` **已实现但故意不接线**（2026-09-21 实测后撤下）：
    # 它的安全闸依赖"形参数"，而 `store.method_sigs` 是 **decomp 侧**签名，
    # 与**生成头（注解侧）声明**实测**会不一致** ⇒ 两处独立误伤：
    #   ① `A->Cls::M(explicit_this, args)`（对象是前缀）被当成"缺 this"
    #      ⇒ 双解引用链，单文件 35→102 条错；
    #   ② **函数定义头** `BOOL Cls::CreateObj(3 参)` 因 decomp 侧记 2 参而被改写成
    #      `BOOL ((Cls *)CCBUI **ppUI)->CreateObj(...)` ⇒ C2199/C2143/C2447。
    # 链式守卫已修 ①；② 的根治前提是**元数取自注解声明**（编译器实际读的那份），
    # 即 R16"消费者实际读哪份声明"。实测净效应：C2660 **0**、总错误 +2 ⇒ 门禁拦下。
    # 机制与守卫已固化为纯函数 + 19 项单测（tests/test_explicit_this_call.py）；
    # 待"注解元数"可用后再接线。

    # Register-this alias elimination
    code = _fix_register_this_alias(code)

    # Reference parameter restoration
    code = _fix_ref_params(code, ctx)

    # ulong* → uint* cast fix
    code = _fix_ulong_uint_cast(code)

    # operator new return value cast (MSVC6 requires explicit void* → T*)
    code = _fix_operator_new_cast(code)

    # C2440 cast insertion: pointer RHS into DWORD slots + ptr/ptr sign
    code = _fix_c2440_casts(code, ctx)

    # 浮点字面量形态：float 目标赋值表达式的 double 字面量/cast → float 形态
    # （原始 x87 dword 操作数尺寸为证据；FPU 批次组件 3.5）
    code = _fix_float_literal_form(code, ctx)

    # 单用途 FPU 伪变量内联：【停用】（2026-09-26 Render2 实验：原始源码本身
    # 使用具名 float 临时——ORIG 先算 height 除法后算 width 的求值顺序即证据；
    # 内联翻转求值序 nd 257→261。类型注解+字面量形态已足够复现 FPU 编码。
    # 保留实现供未来有字节证据支持的个别函数手动启用。）
    # code = _inline_single_use_fpu_vars(code, ctx)

    # Empty if-body before else
    code = re.sub(
        r'^(\s*)if\s*\((.*?)\)\s*\n\s*else\b',
        r'\1if (\2)\n\1{\n\1}\n\1else',
        code, flags=re.MULTILINE
    )

    # if-with-comment-body: stage3 comments out vtable accesses inside if
    # bodies, leaving bare comments without braces. MSVC6 C2143.
    code = re.sub(
        r'^(\s*)if\s*\((.*?)\)\s*\n(\s*//.*?)$',
        r'\1if (\2)\n\1{\n\3\n\1}',
        code, flags=re.MULTILINE
    )

    # Hex-Rays (int)this cast artifact: Method((int)this) → this->Method()
    # This is a self-call where Hex-Rays inserted an (int) cast on this.
    #
    # FIX(2026-09-18)：`\b(\w+)\(` 也会命中**限定/成员调用之后**的形态，于是
    #   obj->Cls::Method((int)this)   →   obj->Cls::this->Method()   (畸形，且丢实参)
    #   ::ShowWindow((int)this)       →   ::this->ShowWindow()       (畸形)
    # 实测改前生成树里这类畸形共 **15 处**（`::this->Xxx` / `->this->ShowWindow`）。
    # 本替换的语义只适用**未限定**的自调用 `Method((int)this)`，故加负向后顾排除
    # `\w` `:` `.` `>`：限定形态交给 ast_transform 的显式-this 分支处理（它会给出
    # `(obj)->Cls::Method(rest)` 或实施静态调用，都比畸形文本可读且报错准确）。
    code = re.sub(r'(?<![\w:.>])(\w+)\(\(int\)this\)', r'this->\1()', code)

    # !this null check → (this == NULL)
    code = re.sub(r'\b!this\b', '(this == NULL)', code)
    code = re.sub(r'\bthis\s*==\s*0\b', '(this == NULL)', code)

    # return byte_1010101 → return (void*)byte_1010101
    code = re.sub(r'return\s+byte_1010101', r'return (void*)byte_1010101', code)

    # Struct overlap resolution
    code = _resolve_stru_overlap(code)

    # Typed pointer arithmetic: *(this + N) = (Type*)val
    code = re.sub(
        r'\*\(this\s*\+\s*(\d+)\)\s*=\s*\([^)]+\*\)\s*(\w+)',
        r'*((_DWORD *)this + \1) = (unsigned long)(\2)',
        code
    )

    # Struct global array access: g_StructName[N] → *(int *)((char *)&g_StructName + N*4)
    _array_globals = []
    for gname, gtype in store.global_types.items():
        if gname in store.globals_map:
            gname = store.globals_map[gname]
        if gname.startswith('g_') and gtype and '[' not in gtype:
            for base, end, _, _ in store.struct_instances:
                if base <= int(gname.split('_')[1], 16) < end if re.match(r'^g_\w+$', gname) and False else False:
                    _array_globals.append(gname)
                    break
    for _ag in _array_globals:
        code = re.sub(
            r'\b' + re.escape(_ag) + r'\[(\d+)\]',
            lambda m: '*(int *)((char *)&' + _ag + ' + ' + m.group(1) + ' * 4)',
            code
        )

    # --- H（2026-09-15）：dtor 形参被剥后残留的自由变量（必须放在本函数**最末**） ---
    #
    # 问题：`pipeline/gen/stages/stage1_structural.py:177-190` 对析构函数
    # 「Dtor: strip all params」**无差别剥掉全部形参**。其本意是剥掉隐式的 `Cls *this`，
    # 但当签名里除 `this` 外**还有真实语义形参**时（实测全树 9 个 dtor），
    # 该形参名会变成自由变量。例：
    #   decomp signature = `virtual void *__thiscall(AStarPathFinder *this, char a2)`
    #   decompiled_c     = `void *__thiscall AStarPathFinder::~AStarPathFinder(AStarPathFinder *this, char a2)`
    #                      `{ AStarPathFinder::ReleaseAll(this); if ((a2 & 1) != 0) operator delete(this); ... }`
    #   生成后 : .h `~AStarPathFinder();` / .cpp `AStarPathFinder::~AStarPathFinder()`
    #           但函数体仍写 `if ( (a2 & 1) != 0 )`
    #
    # 后果**不是恒定的**：`a2`/`nVal` 这类名字在 VC6 自动名体系里（`globals.h` 的
    # `char a2[]` 等）**常常恰好存在同名全局** → 于是**侥幸编译通过**；一旦 IDA 的自动名
    # 换代（干净重建后 `0x590638` 从 `int a2` 变成 `char a2[]`），同一行就报
    # `C2296 '&' : illegal, left operand has type 'char []'`。
    # ⇒ 这是"**看 globals.h 里恰好有没有那个名字**"的**假通过**路径，而非稳定的正确产物。
    # 该缺陷**长期存在**：2026-09-01 基线里同一行就是 `C2065 'a2' : undeclared identifier`。
    #
    # 修法：**每个函数体的调用形态已经蕴含了调用时传入的 flag 值**。签名里该形参名已被
    # stage1 删除，故把函数体内对它的引用**替换为那个常量**即恢复原语义 ——
    # 这不是猜测，是「调用点已给出该值」的直接推论。
    #
    # 单参形态（实测全树 9 个 dtor 中 6 个是单参）确定的语义只有一种：
    # VC6 标量删除析构的 deleting flag，且该析构体**自身**负责 `operator delete`，
    # 故它是在 `delete p` 路径上被调用的，flag 恒为 **1**。
    #   `CEffgbParticle::~CEffgbParticle(int,int,int,int *,int,int)` 等多参形态
    #   **无法从单点确定**，本处**不动**（留给 Phase 2 / 或改为保留形参的根治方案）。
    #
    # 【位置要求】必须放在本函数**末尾**：前面多处 `code = re.sub(...)` 会整体覆盖 `code`，
    # 放在中间会被覆盖掉（captain 第一版即因此静默失效）。
    _sig_h = getattr(ctx, 'sig', None) or ''
    # 真实 sig 形如 `virtual void *__thiscall(AStarPathFinder *this, char a2)` ——
    # **含显式 `this`**，故必须先剔除它，剩下的才是被 stage1 剥掉的语义形参。
    #
    # ⚠️⚠️ 必须有 `ctx.is_dtor` 守卫（2026-09-15 独立复核 M1 抓出，captain 补）：
    # 缺此守卫时，本块会命中**任何**「恰好 1 个 int/char 类形参」的**普通函数**，
    # 把该形参名在整段函数体里替换成常量 `1` ⇒ **语义损坏**，不只是语法错：
    #   decomp    : *(_DWORD *)(result + 362768) = a2;      // 存形参
    #   generated : int CEffCylinder::Update(int 1) { ... *(_DWORD *)(result + 362768) = 1; }
    # 实测半径：谓词命中 decomp 51 个函数，其中**真 dtor 只有 1 个**；
    # `pal3/src` 里 **30 处签名 / 17 个文件**被毁（含 `int 1`/`char 1` 这类非法形参名）。
    # 更危险的是**它让度量反向**：受害者文件本来全是 fail，被解析崩塌后
    # error_count 反而下降（18:24→18:40 的「−294 修正」里 −293 全是这个假降），
    # 而 `compile_regression.py` 只比 ok/fail ⇒ **无门禁可发现**。
    # 故本块**仅对析构函数**生效，且只限「单参标量 deleting flag」这一确定语义。
    _m_h = re.search(r'\(\s*([^)]*)\)', _sig_h)
    if _m_h and getattr(ctx, 'is_dtor', False):
        _params_h = [p.strip() for p in _m_h.group(1).split(',') if p.strip()]
        _params_h = [p for p in _params_h if not re.search(r'\bthis\b', p)]
        if len(_params_h) == 1:
            _pn_h = re.search(r'([A-Za-z_]\w*)\s*$', _params_h[0])
            _pt_h = _params_h[0][:_pn_h.start()].strip() if _pn_h else ''
            if _pn_h and re.fullmatch(r'a\d+', _pn_h.group(1)) and \
                    _pt_h in ('char', 'int', 'unsigned int', '__int8', '__int16', '__int32'):
                _flag_name = _pn_h.group(1)
                # 仅对 dtor：该形参名已从签名删除、函数体内无声明，**不可能是合法标识符**，
                # 故替换不可能覆盖真实的局部变量/参数。且该析构体自身负责 `operator delete`、
                # 只能由 `delete` 路径进入 ⇒ flag 恒为 1（否则 double-free）。
                code = re.sub(r'\b' + re.escape(_flag_name) + r'\b', '1', code)

    return code


def cast_reg_assignments(code):
    """批 5 返工（复核 B1/B2）：reg_ 伪名赋值 RHS `(unsigned long)` 显式铸统一。
    等价变换：原码隐式转换的显式化（整型 RHS 恒等铸、指针 RHS 为原意显式化——
    cl 单案裁判：8/16/32 位/bool/__int64/浮点/指针/函数返回全恒等）。
    返工封堵：①`=` 边界 `(?<![=!<>])(?!=)`（`reg_X == y` 不吃）②顶层逗号 rhs 不动
    （B2 语义反转）③掩码字符串/注释（E-1 纪律）④链式赋号保守不动。"""
    try:
        from ast_transform import _mask_strings_comments as _msc
        masked = _msc(code)
    except Exception:
        masked = code
    pat = re.compile(
        r'(\breg_\w+\s*(?<![=!<>])=(?!=)\s*)'
        r'(?!\s*\(unsigned long\))'
        r'([^;]+?)\s*;')
    edits = []
    for m in pat.finditer(masked):
        rhs = m.group(2).strip()
        if re.match(r'^(?:-?(?:0[xX][0-9a-fA-F]+|\d+)[uUlL]*)$', rhs):
            continue
        if re.match(r'^reg_\w+$', rhs):
            continue
        # B2：顶层逗号 ⇒ 保守不动；括号不平（depth<0/收尾≠0）同样保守
        depth, comma, neg = 0, False, False
        for ch in rhs:
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth < 0:
                    neg = True
                    break
            elif ch == ',' and depth == 0:
                comma = True
                break
        if comma or neg or depth != 0:
            continue
        # 链式赋号（rhs 含裸 =）保守不动
        if re.search(r'(?<![=!<>])=(?!=)', rhs):
            continue
        # 语句边界（A8/A9：非边界错捕保守不动）——match 起点须为行首/`;{}` 后
        pre = masked[max(0, m.start() - 2):m.start()]
        if pre.strip() and not pre.rstrip().endswith((';', '{', '}')):
            continue
        # rhs 从**原文**取（掩码 x 替身毁字面量教训——复判 M5）
        rhs_orig = code[m.start(2):m.end(2)].strip()
        prefix = code[m.start():m.start(2)]
        edits.append((m.start(), m.end(),
                      '%s(unsigned long)(%s);' % (prefix, rhs_orig)))
    out = code
    for s, e, rep in reversed(edits):
        out = out[:s] + rep + out[e:]
    return out


def run(code, ctx):
    out = _run_inner(code, ctx)
    # 钩子后置 2026-10-07（stage4 钩子位错实证——形产于 stage5 铸机后）：C2100 形归一
    try:
        from ast_transform import normalize_deref_cast_parens
        out = normalize_deref_cast_parens(out)
    except Exception:
        pass
    return out
