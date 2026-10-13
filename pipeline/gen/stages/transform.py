"""Transform pipeline: 5 deterministic stages.

Stage 1 - structural:     Function signature modification (before OOP)
Stage 2 - semantic:       OOP call rewrite (tree-sitter AST)
Stage 3 - cleanup:        Remove/comment IDA artifacts (depends on Stage 2)
Stage 4 - resolution:     AST-based identifier/type resolution (no text hacks)
Stage 5 - fixup:          Compiler compatibility patches (text-level, no AST)
"""
from dataclasses import dataclass
import re

from stages import stage1_structural, stage2_semantic, stage3_cleanup
from stages import stage4_substitution, stage5_fixup


@dataclass
class TransformContext:
    cls_name: str
    method_name: str
    sig: str
    is_ctor: bool
    is_dtor: bool
    is_free_function: bool
    # 同一**输出文件**内共享的 stub 去重集合（由 emit_cpp 按文件创建）。
    # None ⇒ 不去重（旧行为，安全回退）。
    stub_registry: object = None
    member_index: object = None
    classless_names: object = None


_MEMBER_INDEX_CACHE = None


def make_context(cls_name, method_name, sig='', is_free=False, stub_registry=None):
    is_ctor = (method_name == cls_name) if cls_name else False
    is_dtor = (method_name == '~%s' % cls_name) if cls_name else False
    if is_dtor and sig:
        _ret = sig.split('(')[0].strip()
        if 'void' not in _ret or '*' in _ret:
            is_dtor = False
    # 路由数据流 2026-10-07（复核 R-C）：member_index（类+基类链成员·生成头为准）+
    # classless_names（functions.json classless 条目——32 带 class 排除）
    member_index = None
    classless_names = None
    global _MEMBER_INDEX_CACHE
    try:
        if _MEMBER_INDEX_CACHE is None:
            import glob as _glob
            import os as _os
            from ast_transform import build_member_index_from_headers
            _hdrs = {}
            _root = _os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), 'pal3', 'src')
            for _p in _glob.glob(_os.path.join(_root, '**', '*.h'), recursive=True):
                try:
                    _hdrs[_os.path.basename(_p)[:-2]] = open(_p, encoding='utf-8', errors='replace').read()
                except Exception:
                    continue
            # 一次 parse 全类（成员+基类）——per-cls 组装查缓存
            _MEMBER_INDEX_CACHE = build_member_index_from_headers(_hdrs) if _hdrs else {}
        if cls_name and _MEMBER_INDEX_CACHE:
            _mi = _MEMBER_INDEX_CACHE
            member_index = {cls_name: set(_mi.get(cls_name, set()))}
    except Exception:
        member_index = None
    try:
        import json as _json
        _fp = _os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))), 'data', 'annotations', 'functions.json')
        _fd = _json.load(open(_fp, encoding='utf-8'))
        classless_names = set()
        for _k, _v in _fd.items():
            if isinstance(_v, dict) and not _v.get('class') and _v.get('name'):
                classless_names.add(str(_v['name']).split('(')[0])
    except Exception:
        classless_names = None
    return TransformContext(
        cls_name=cls_name, method_name=method_name, sig=sig,
        is_ctor=is_ctor, is_dtor=is_dtor, is_free_function=is_free,
        stub_registry=stub_registry,
        member_index=member_index, classless_names=classless_names)


def _thunk_keep_tailjump(code, ctx, is_thunk):
    """F20（2026-09-19，长线计划）：thunk（IDA `// attributes: thunk`）必须是 5 字节 `E9 rel32` 尾跳。

    实测（独立复核，用仓库自带 CL.EXE + 项目同款 flags）：我们当前发射的形态（末句调用 /
    `return call`）**本来就会**编译成 `E9 rel32`；真正的阻塞是 `/Ob2` 把 callee 在**同一个 TU** 内联掉，
    函数体变成 callee 的副本（11~64 字节）。`#pragma inline_depth(0)` 是唯一能在**保留全局优化器**
    （TCO 由它做）的同时阻止内联的局部手段：`auto_inline(off)`/`inline_recursion(off)` 都无效，
    `optimize("g", off)` 会把 TCO 一起关掉（更糟）。
    **门（实测必需）**：ctor/dtor 不算 —— dtor thunk 加 pragma 反而多出基类 dtor 调用 + EH 帧。
    另：函数体必须只有一条调用语句（decomp 里带 `int result; … return result;` 的是**签名误标**产物，
    属注解批，不在这里处理）。
    """
    if not is_thunk:
        return code
    if getattr(ctx, 'is_ctor', False) or getattr(ctx, 'is_dtor', False):
        return code
    # 只取**大括号之间**的语句：先把签名行/标记注释排除掉（首版用 split()[1:] 误把签名行当语句，
    # 导致门恒不通过、stage6 完全空转——已由 A/B（L1 未变）暴露）。
    _ls = code.split('\n')
    _open = next((i for i, l in enumerate(_ls) if l.strip() == '{'), None)
    _close = next((i for i in range(len(_ls) - 1, -1, -1) if _ls[i].strip() == '}'), None)
    if _open is None or _close is None or _close <= _open:
        return code
    _body = [l.strip() for l in _ls[_open + 1:_close]
             if l.strip() and not l.strip().startswith('//')]
    if len(_body) != 1 or not _body[0].endswith(';'):
        return code
    # [T89] 内联抑制探针（T88 缺件定性：dtor 体被 /Ob2 内联而非尾跳）——
    # inline_depth(0) 不抑成员调用内联（T88 实证）⇒ 叠加 auto_inline(off)。
    # ⚠️ 影响面收窄至本包装函数（thunk 体）——先测后改（T88 提示）。
    return ('#pragma inline_depth(0)\n#pragma auto_inline(off)\n%s\n'
            '#pragma auto_inline(on)\n#pragma inline_depth()') % code


# --- F51: JUMPOUT(0xADDR) 还原成真正的尾调用 -------------------------------
# `include/pal3/ida_defs.h` 里 `#define JUMPOUT(x)` 展开为**空**，于是 Hex-Rays 用来表示
# "跳到一个不是函数入口的代码块" 的尾跳被整个丢掉。
# 唯一活体：TextureLib::ClearAndJump @0x0053F550（10 字节）
#   E8 rel32   call TextureLib::ClearGlobalVars (0x53F560)
#   E9 rel32   jmp  0x53F570                     <- 真尾跳，0x53F570 是真实代码块
# 我们原先生成 33 字节（/Ob2 把 ClearGlobalVars 内联进来 + 跳转消失）。
# 两道闸（实测）：
#   1) 目标必须落在 .text 映像内 —— PAL3.cpp:4042 的 0x2EE3E9A 是 IDA 伪造的 `je` 目标；
#   2) 函数体里必须至少有一条非 JUMPOUT 语句 —— free_functions.cpp 的 4 处是 IDA 函数边界
#      假函数（位于 `align 10h` 填充里，体只有 `JUMPOUT(自己的末尾)`）。
# `#pragma inline_depth(0)` 与 F20 同机制，实测必需（否则前置调用仍被内联）。
_TEXT_LO, _TEXT_HI = 0x401000, 0x56A000
_JUMPOUT_RE = re.compile(r'JUMPOUT\(\s*(0x[0-9A-Fa-f]+)\s*\)')


def _jumpout_to_tailcall(code):
    """把 `JUMPOUT(0xNNN)` 改写成对真实代码块 `sub_NNN()` 的尾调用。"""
    _m = _JUMPOUT_RE.search(code)
    if _m is None:
        return code
    _t = int(_m.group(1), 16)
    if not (_TEXT_LO <= _t < _TEXT_HI):
        return code
    _ls = code.split('\n')
    _open = next((i for i, l in enumerate(_ls) if l.strip() == '{'), None)
    _close = next((i for i in range(len(_ls) - 1, -1, -1) if _ls[i].strip() == '}'), None)
    if _open is None or _close is None or _close <= _open:
        return code
    _stmts = [l.strip() for l in _ls[_open + 1:_close]
              if l.strip() and not l.strip().startswith('//')]
    if not [s for s in _stmts if not s.startswith('JUMPOUT(')]:
        return code
    code = _JUMPOUT_RE.sub(lambda mm: 'sub_%X()' % int(mm.group(1), 16), code)
    # [T89] 内联抑制探针（T88 缺件定性：dtor 体被 /Ob2 内联而非尾跳）——
    # inline_depth(0) 不抑成员调用内联（T88 实证）⇒ 叠加 auto_inline(off)。
    # ⚠️ 影响面收窄至本包装函数（thunk 体）——先测后改（T88 提示）。
    return ('#pragma inline_depth(0)\n#pragma auto_inline(off)\n%s\n'
            '#pragma auto_inline(on)\n#pragma inline_depth()') % code


def run_transforms(code, ctx):
    """Execute 5 stages in strict order (+ stage6: thunk 尾跳保持)."""
    # thunk 判定取在**变换前**：防止某个阶段把标记注释/剥掉。
    # 注意标记**不一定在第一行**（实测前面常有 `// 0x004EC480` 这类地址注释）⇒ 扫前几行。
    _is_thunk = any('attributes: thunk' in _l for _l in code.split('\n')[:4])
    code = stage1_structural.run(code, ctx)
    code = stage2_semantic.run(code, ctx)
    code = stage3_cleanup.run(code, ctx)
    code = stage4_substitution.run(code, ctx)
    code = stage5_fixup.run(code, ctx)
    return _jumpout_to_tailcall(_thunk_keep_tailjump(code, ctx, _is_thunk))
