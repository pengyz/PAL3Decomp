#!/usr/bin/env python3
"""vtable **编译产物对比器** —— vtable 数据的最终裁判（Task 6）。

## 为什么需要它（本工具存在的理由）

L1 字节比对只比 `.text` 函数体，对 **vtable 数据结构性失明**：表少一槽、槽序互换、
thunk 归一错（`this` 调整量错）都能让 L1 全绿而二进制不等。`.rdata` vtable 的最终裁判
只能是**编译产物（.obj 合成表）vs 二进制真实表**的逐槽对比。

## 两侧怎么比（关键设计）

| 维度 | .obj 侧（编译产物） | 二进制侧（PAL3.exe） |
|---|---|---|
| 槽内容 | **符号重定位**（数据字节是 0，语义在 reloc 里） | 4 字节 VA |
| 归约 | reloc 目标**符号名** → 名字键 `Cls::Func` | VA → `va_index()`（decomp/注解）名字键 |
| 槽数 | `??_7<Cls>@@6B...@` 符号的 DWORD 序列（**不含** `vtable[-1]` 的 RTTI COL） | ctor 实写的表起始（`vtable_compare.bin_vptr_targets`）→ 表长界定 |
| thunk | obj 内 thunk 体解码（`sub ecx,N; jmp <reloc 目标>`） | 镜像内 thunk 体解码（同解码器） |
| vbtable | `??_8<Cls>@@7B@` 的**字面量** DWORD（无重定位） | 表起始 VA 的 DWORD 序列 |

两侧归一成同一 `NormSlot`：

    (目标函数键, kind)                          —— 普通槽
    (目标函数键, kind, this 调整量)              —— 静态 adjustor thunk（二元组语义）
    (目标函数键, kind, 'dynamic', const)         —— 动态 delta（**三元组**，见 B-4）

**身份判据是 VA，不是名字文本**（C1 修复轮 R=1 的结论）：名字键只是归约的中间量，
两侧键空间本就不同——`.obj` 侧从 mangled 归约**永远不带参数表**（`gbLightObj::GetGfxManager`），
而二进制侧 `va_index()` 的名字**带参数表**（`gbLightObj::GetGfxManager(void)`，真机 3618 条
里 3185 条如此）⇒ 只比名字文本时"表完全正确"也逐槽假报 `slot_key`（真机量化：189 表 /
639 槽中 ≥552 槽必误报）。故：

1. `.obj` 侧由 `name_to_va_candidates(idx, image)` 造 **名字→候选 VA 集**（参数表剥离 +
   thunk 名字重定向到 `jmp` 目标 + **歧义名保留**），`main()` 对比模式必须传入；
2. 二进制侧 `va` **直接取已知真实 VA**（普通槽 = 槽自身，thunk 槽 = `jmp` 目标），
   **不做名字反查**（反查会把真实 VA 丢掉）；
3. 两侧都有单一 VA ⇒ 比 VA；一侧单一 VA、另一侧**候选集** ⇒ 要求 `VA ∈ 候选集`；
   两侧都无 VA 信息 ⇒ 才比 `strip_param_list` 后的名字（次优判据）。混比两种判据必然假报。

**R=2 修复轮（歧义名不得静默放行）**：R=1 的歧义名剔除留下一个新假通过面——真机
**24/639 槽（3.8%）** 的 `name_id` 在 idx 里对应 **≥2 个 VA**（评审实测 24/24 候选体各不
相同 ⇒ 真重载），`.obj` 侧 va 退为 None ⇒ 退回名字判据，而 `name_key` **抹掉参数编码**
（`?DestroyEffBase@RenderTarget2@@UAEXD@Z` 与 `...UAEXXZ` 都归约成
`RenderTarget2::DestroyEffBase`）⇒ 两侧被判相同。真机实证（本工具复现，坐标经
`func_bounds` 双证）：表 `0x56F674` 槽 0 是 `DestroyEffBase(char)`@`0x4C1640`，`.obj`
装 `(void)`（真值 `0x4C1660`）时**修复前 ok=True、零偏差**。故：

* 候选集**不丢弃**，并用 `.obj` 符号**自身的参数编码**（`idx 参数文本 → mangled 参数
  后缀`，借管线的 `vc6_mangler.encode_type`）把候选集**收敛**到具体重载；
* 收敛不了（idx 名同签名 / 编码不可确定）⇒ 退回**包含判据** `bin.va ∈ 候选集`；
* **只有**两侧都没有任何 VA 信息时才退回纯名字判据。

`kind` 词表复用 Task 2 的 `vtable_slot_classifier.classify_slot`（6 种：
`fn`/`deleting_dtor`/`adjustor_static`/`adjustor_vbase`/`purecall`/`composite`）——
判据全部落在**原始指令字节/符号**上，不解析 mangling、不读 decomp JSON。

## 三个必须照做的实测事实（本任务真机复现，逐条留痕）

1. **reloc 的符号索引是原始 COFF 索引（含 aux 占位）**：`coff_vtable.parse_obj` 已按原始
   索引建映射，本工具**复用**它，不重新按"遍历序"计数。
   `??_7C2@@6B@` 符号 value = **4**：COL 在 value-4，address point 在 value
   ⇒ 槽数从 address point 数，COL **不得**被数成槽。
2. **thunk 归一（真机字节）**：
   * `?ff@D3@@W7AEHXZ` = `83 e9 08; e9 <rel ?ff@D3@@UAEHXZ>`（vt3.cpp）⇒ offset 8
   * `?v@DV2@@$4PPPPPPPM@A@AEXXZ` = `2b 49 fc; e9 <rel>`（dv2.cpp）⇒ dynamic
   * `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z` = `2b 49 fc; 83 e9 10; e9 <rel ??_ED@@UAEPAXI@Z>`
     （attack README B-1）⇒ composite + dynamic + const 0x10
3. **vtable 惰性 COMDAT 发射 ⇒ 必须强制发射**（真机实测，本任务）：
   * 普通类只定义虚函数、不构造对象 ⇒ `??_7C2@@6B@` **缺失**；构造对象（全局对象最稳）⇒ 出现
   * 抽象类：定义**具体派生类**并构造（/Od 下借派生 ctor 写基类 vptr）⇒ 基类表出现；
     **/O2 死存储消除会把基类 vptr 写吃掉** ⇒ 基类表仍缺失（本工具**必须捕获**，见下）
   * 无虚析构的抽象类：dummy `Cls::Cls() { }` 定义即发射（/Od 与 /O2 都实测发射）
   * ⇒ `force_emit()` 编译后**必须看到** `??_7<Cls>@@` 符号，否则换下一策略；
     全部失败 ⇒ `EmissionError`（带探针源 + 每次尝试痕迹），**绝不**静默返回 0 槽的"通过"

## 真机 RTTI 实测（2026-09-25，本任务；直接决定 address point 的算法）

`original/PAL3.exe` 全库只有 **6** 条 `.?AV` 串且全部是 CRT/STL
（`_Exception`/`exception`/`logic_error`/`length_error`/`out_of_range`/`type_info`）
⇒ **游戏类 vtable 没有 RTTI COL**：189 张 ctor 实写表里，`base-4` 是 float 数据/相邻表槽的
184 张，另 5 张的 `base-4` 虽落在 `.rdata` 但目标无名（该地址处也无 `.?AV` 串）⇒ 五张
本身更像是 `mov $数据表, (%reg)` 扫出来的**非 vtable 常量**，不是 COL。而本仓管线编译**带 `/GR`**（`pipeline/compare.py`）
⇒ 若 .obj 侧出现 `??_R4...` COL，`address_point_rtti` 偏差就是**真发现**（目标表少 4 字节、
逐槽地址整体位移），不是噪声。**两侧都提供的 COL 只比存在性**（身份空间不同：
obj 是符号名、bin 是 VA）。

## 偏差报告契约

偏差**必须定位到具体槽位 + kind**（不是"表不等"）：
`Deviation(kind, index, obj, bin)`，kind ∈
`slot_count` | `address_point_rtti` | `slot_key` | `slot_kind` | `this_adjust` |
`vbtable_count` | `vbtable_value`。

## 边界（有意不做）

* 不做槽序**逆映射**（attack README A-1/A-3 证伪，归 Task 5/7）
* 不做签名推断（Task 3）与声明校验（Task 5）
* 二进制侧表长界定是**启发式**（沿用 `vtable_compare.bin_table` 的三信号：硬上界 /
  非代码指针 / 类族不一致），结果带 `confidence` 与 `broken_at`——低置信必须人工核

用法：
    python3 tools/vtable_verify.py --obj /tmp/x.obj --list
    python3 tools/vtable_verify.py --obj /tmp/x.obj --cls CEffCylinder --bin-base 0x56F7C8
    python3 tools/vtable_verify.py --probe-src CEffCylinder --abstract --pure 'int p()'
    python3 tools/vtable_verify.py --selfcheck                 # 合成夹具自检（无需 IDB/PAL3）
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys
from dataclasses import dataclass, replace

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))

import coff_vtable as cv  # noqa: E402  复用：COFF 解析 + vtable 符号重定位解名
from vtable_slot_classifier import (  # noqa: E402  复用（Task 2）：槽型词表 + 分类器
    KIND_ADJUSTOR_STATIC,
    KIND_ADJUSTOR_VBASE,
    KIND_COMPOSITE,
    KIND_DELETING_DTOR,
    KIND_FN,
    KIND_PURECALL,
    SlotEvidence,
    classify_slot,
)

__all__ = [
    'KIND_FN', 'KIND_DELETING_DTOR', 'KIND_ADJUSTOR_STATIC', 'KIND_ADJUSTOR_VBASE',
    'KIND_PURECALL', 'KIND_COMPOSITE',
    'SIDE_OBJ', 'SIDE_BIN', 'DYNAMIC_MARK',
    'name_key', 'mangled_class_token', 'is_thunk_symbol', 'strip_param_list',
    'name_to_va_index', 'name_to_va_candidates',
    'ObjSlot', 'ObjVTable', 'ObjArtifacts', 'parse_obj_artifacts',
    'obj_vtables', 'obj_vbtables', 'resolve_obj_thunk',
    'AdjustorChain', 'decode_adjustor_chain', 'image_thunk',
    'ImageError', 'PEImage', 'BytesImage',
    'BinTable', 'bin_table_from_image', 'bin_vbtable',
    'NormSlot', 'normalize_obj_slots', 'normalize_bin_slots',
    'Deviation', 'CompareResult', 'compare_tables', 'compare_vbtable', 'render_report',
    'DEFAULT_PROBE_FLAGS', 'PROBE_STRATEGY_OBJECT', 'PROBE_STRATEGY_DERIVED',
    'PROBE_STRATEGY_DUMMY_CTOR', 'ProbeSpec', 'EmissionError', 'EmissionResult',
    'default_strategies', 'build_probe_source', 'compile_probe', 'force_emit',
    'load_bin_targets', 'load_va_index',
    'build_arg_parser', 'main',
]

SIDE_OBJ = 'obj'
SIDE_BIN = 'bin'
DYNAMIC_MARK = 'dynamic'

EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
WINE_CL = os.path.join(ROOT, 'tools', 'wine_cl.sh')
MSVC_INCLUDE = os.path.join(ROOT, 'tools', 'compilers', 'msvc6.0', 'Include')

#: 强制发射默认编译选项。**刻意用 /Od**：真机实测 /O2 会把"派生 ctor 里的基类 vptr 写"
#: 当死存储消除（只留派生表）⇒ 抽象类的 derived 策略在 /O2 下可能不发射基类表。
#: /Od 下三种策略（object/derived/dummy_ctor）都实测发射。
DEFAULT_PROBE_FLAGS = ('/Od', '/GR')


# =====================================================================================
# 1. 符号名归约（两侧共同的"名字键"）
# =====================================================================================

def _class_tokens(rest):
    """mangled 里的类令牌序列（内层→外层，遇空令牌终止）。

    MSVC 规则：`?func@Innermost@...@Outermost@@<qual>` ⇒ C++ 名是 `Outermost::...::func`。
    thunk 的 `W<n>` / `$4...` 出现在**空令牌之后**，不属于类序列。
    """
    parts = rest.split('@')
    toks = []
    for p in parts:
        if p == '':
            break
        toks.append(p)
    return list(reversed(toks))


def name_key(name):
    """符号名/mangled 名 → 两侧可比的名字键 `Class::Func`。

    覆盖（真机符号）：
      `?ff@D3@@UAEHXZ`           → `D3::ff`
      `?ff@D3@@W7AEHXZ`          → `D3::ff`（静态 adjustor thunk）
      `?v@DV2@@$4PPPPPPPM@A@AEXXZ` → `DV2::v`（动态 adjustor thunk）
      `??_ED@@$4...`/`??_ED@@UAEPAXI@Z` → `D::~D`（deleting dtor）
      `??1D@@UAE@XZ`             → `D::~D`（complete dtor）
      `??_7D3@@6BA3@@@`          → `D3::__vftable[A3]`（视图=A3 基类令牌）
      `??_8D3@@7B@`              → `D3::__vbtable`
      `__purecall` / `_purecall` → `__purecall`
      `CEffCylinder::Create`     → 原样（注解/decomp 侧的文本名）
    """
    if not name:
        return ''
    s = name.strip()
    s = re.sub(r'^\[thunk\]:\s*', '', s)
    s = re.sub(r"\s*`adjustor\{-?0x[0-9a-fA-F]+\}'\s*$", '', s)
    if s.startswith('??_7'):                       # vftable
        rest = s[4:]
        cls = rest.split('@')[0]
        i = rest.find('6B')
        view = rest[i + 2:].split('@')[0] if i >= 0 else ''
        return '%s::__vftable%s' % (cls, ('[%s]' % view) if view else '')
    if s.startswith('??_8'):                       # vbtable
        return '%s::__vbtable' % s[4:].split('@')[0]
    if s.startswith('??_E') or s.startswith('??_G'):   # vector/scalar deleting dtor
        cls = s[4:].split('@')[0]
        return '%s::~%s' % (cls, cls)
    if s.startswith('??1'):                        # complete dtor
        cls = s[3:].split('@')[0]
        return '%s::~%s' % (cls, cls)
    if s.startswith('?'):
        body = s[1:]
        func = body.split('@')[0]
        rest = body[len(func):]
        if rest.startswith('@'):
            toks = _class_tokens(rest[1:])
            if toks and not toks[0].startswith(('?', '$')):
                return '%s::%s' % ('::'.join(toks), func)
        return func
    low = s.lower().lstrip('_')
    if low == 'purecall':
        return '__purecall'
    return s


def mangled_class_token(cls):
    """`Outer::Inner` → `Inner@Outer`（MSVC vftable 符号里的类令牌）。"""
    return '@'.join(reversed([p for p in cls.split('::') if p]))


#: 参数表后缀（`GetGfxManager(void)` / `GetCGEntry(char)` / `OnKeyDown(int,unsigned int)`）
_PARAM_LIST_RE = re.compile(r'\(.*\)\s*$')


def strip_param_list(name):
    """`Cls::Func(void)` / `Cls::Func(gbAABBox *)` → `Cls::Func`（**参数表剥离归一**）。

    为什么必须有：**decomp JSON / 注解里的名字带参数表**（真机 `va_index()` 3618 条里
    3185 条带参数表），而 .obj 侧从 mangled 符号归约出来的键**永远不带**（`name_key` 只取
    类令牌链 + 函数名）⇒ 两侧若不归一到同一名字空间，**表完全正确也会逐槽误报 `slot_key`**
    （评审 R=1 真机量化：189 表 / 639 槽中 406 槽带参数表 + 146 槽无名字 ⇒ ≥552 槽必误报）。

    只剥**末尾整段**参数表：mangled 名（`?GetCGEntry@gbLightObj@@W7AEXXZ`）不含括号尾，
    原样返回；`__purecall` / `D3::ff` 亦然。
    """
    if not name:
        return ''
    return _PARAM_LIST_RE.sub('', name).strip()


def is_thunk_symbol(name):
    """adjustor thunk 符号判据（只认 MSVC 的两处 mangling 标记）。

    * 静态 adjustor：`@@W<n><cc>...`（真机 `?ff@D3@@W7AEHXZ`）
    * 动态/vtordisp：`@@$4...`（真机 `?v@DV2@@$4PPPPPPPM@A@AEXXZ`）
    """
    if not name or not name.startswith('?'):
        return False
    return '@@W' in name or '@@$' in name or '$4' in name


# =====================================================================================
# 1b. 重载判别：idx 参数文本 → mangled **参数编码后缀**（R=2 的候选集收敛判据）
# =====================================================================================
#
# 用途只有一个：`.obj` 符号是 mangled 名（**参数编码在里面**），idx 侧名字是
# `Cls::Func(char)`（**参数文本**）——两者唯一的桥是"把参数文本编成 mangled 后缀，
# 再看它是不是 `.obj` 符号的后缀"。判不出来就**不收敛**（退回包含判据），绝不猜。

#: 参数编码的**类型别名归一**（idx 文本 → mangler 认识的拼写）。
#: 只加实测需要的：真机 idx 的重载组里大量出现 `(uint)`，而 `vc6_mangler._TC` 只有
#: `unsigned int`/`UINT` ⇒ 不归一会把 `uint` 兜底成 `int`（`H`），真名却是 `I`
#: （实测：真机 24 个歧义槽里 5 个 `_sdtor_*(uint)` 组因此编码失败 ⇒ 收敛不可用）。
_PARAM_TYPE_ALIASES = {'uint': 'unsigned int'}

_MANGLER = None


def _vc6_mangler():
    """`pipeline/ida/vc6_mangler`（**只借它的 `encode_type` / `strip_param_name`**）。

    复用它而不是在工具里再写一份类型编码表：同一份"VC6 类型 → 编码"知识两处维护必然
    漂移，而那份表是 `tools/mangler_bench.py` 离线复测过的（matched 139）。
    导入失败（工具被单独拷走）⇒ 返回 None ⇒ 收敛判据整体关闭、退回包含判据（绝不猜）。
    """
    global _MANGLER
    if _MANGLER is None:
        try:
            sys.path.insert(0, os.path.join(ROOT, 'pipeline', 'ida'))
            import vc6_mangler as m
            _MANGLER = m
        except Exception:                      # noqa: BLE001  可选依赖：拿不到就降级
            _MANGLER = False
    return _MANGLER or None


def _split_top_level(text):
    """按**顶层**逗号切分参数表（跳过 `<>()[]` 嵌套 ⇒ 模板/函数指针不会切错）。"""
    out, depth, cur = [], 0, ''
    for ch in text:
        if ch in '<([{':
            depth += 1
        elif ch in '>)]}':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    out.append(cur)
    return [p.strip() for p in out if p.strip()]


def _swap_class_tag(code):
    """类名编码的 `V`/`U` tag → 另一个（`PAV_BYTE@@` → `PAU_BYTE@@`）；非类名编码 ⇒ None。

    ⚠️ 为什么不能靠 `encode_type('struct ' + p)`：`vc6_mangler.encode_type` 里
    `ptr > 0` 分支**先于** tag 分支（第 75 行 vs 第 87 行）⇒ `struct X *` 仍然编成
    `PAVX@@`（tag 被丢掉）。实测代价（真机）：
    `CCBStage::DelTask(int,_BYTE *,int *)` 的 V 变体编成 `HPAV_BYTE@@PAH@Z`，真名却是
    `HPAU_BYTE@@PAH@Z` ⇒ 该候选**收敛失败**，另一个候选 `(int)`（`H@Z`，恰好是长名的
    后缀）被判成唯一命中 ⇒ **把正确重载误报成错装**（真机 1/112 候选命中此坑）。
    类名编码的形态固定是 `[PABQ]*[VU]<名>@@` ⇒ tag 就在第一个非前缀字符处。
    """
    i = 0
    while i < len(code) and code[i] in 'PABQ':
        i += 1
    if i < len(code) and code[i] in 'VU':
        return code[:i] + ('U' if code[i] == 'V' else 'V') + code[i + 1:]
    return None


def _param_code_variants(vm, text, cls=''):
    """单个参数的**可接受编码集**（如 `{'PAVgbVec3D@@', 'PAUgbVec3D@@'}`）。

    为什么收两个 tag 变体：MSVC 对 `class` 用 `V`、对 `struct` 用 `U`，而 decomp/idx 的
    签名文本里**拿不到这个区分**（`vc6_mangler` 同款已知限制：真机符号 `PAV : PAU` = 8:2）
    ⇒ 只收一种会把正确重载判成"编码失败"，收两种才不漏（漏判正确重载 = 假报）。

    不可**确定**编码的形式（数组/函数指针/引用/模板/可变参）⇒ 返回 None（不收敛）。
    """
    p = vm.strip_param_name(text.strip()) if text else ''
    if not p or any(t in p for t in ('[', ']', '&', '<', '>', '...', '(*')):
        return None
    toks = [_PARAM_TYPE_ALIASES.get(t, t) for t in p.replace('*', ' * ').split()]
    p = ' '.join(toks).replace(' * ', '*')
    try:
        code = vm.encode_type(p)
    except Exception:                          # noqa: BLE001  编码器不认识 ⇒ 不收敛
        return None
    out = {code}
    alt = _swap_class_tag(code)
    if alt:
        out.add(alt)
    backref = getattr(vm, '_self_ref_backref', None)
    if backref is not None and cls:
        # 本类引用有**两种**真机形态：回指 `1@`（mangler 实测规则 F61，返回类型处）与
        # 全名 `PAUCEffgbParticle@@`（实测：`?Create@CEffgbParticle@@QAEPAXPAUCEffgbParticle@@D@Z`
        # 的**参数**就是全名）。只收一种会把另一种判成"编码失败"⇒ 正确重载收敛不出来。
        out |= {backref(c, cls) for c in out}
    return frozenset(out)


def _param_suffix_variants(name_text, cls=''):
    """idx 名（**带参数表**）→ 该重载可接受的 mangled **参数编码后缀**集合。

    `RenderTarget2::DestroyEffBase(char)` ⇒ `{'D@Z'}`；
    `RenderTarget2::DestroyEffBase(void)` ⇒ `{'XZ'}`（无参数形态）；
    名字不带参数表 / 任一个参数编码不可确定 ⇒ None（调用方**不收敛**）。
    """
    vm = _vc6_mangler()
    if vm is None or not name_text:
        return None
    if '(' not in name_text or not name_text.rstrip().endswith(')'):
        return None
    body = name_text[name_text.find('(') + 1:name_text.rfind(')')].strip()
    if body in ('', 'void'):
        return frozenset({'XZ'})
    params = _split_top_level(body)
    if not params:
        return None
    variants = ['']
    for p in params:
        pv = _param_code_variants(vm, p, cls)
        if pv is None:
            return None
        variants = [a + b for a in variants for b in pv]
        if len(variants) > 64:                 # 变体爆炸 ⇒ 判不了，别硬撑
            return None
    return frozenset(v + '@Z' for v in variants)


def _refine_candidates_by_symbol(symbol, key, candmap):
    """`.obj` 符号 + 名字键 + 候选集 → **收敛后的候选子集**（收敛不了 ⇒ 原样返回）。

    收敛前提（**三个都必须成立**，否则原样返回走包含判据）：

    1. 候选名**都**带参数表且编码可确定；
    2. 各候选的编码**互不相同**（同签名重载如 `_sdtor_*(uint)` ⇒ 本来就不该收敛）；
    3. 恰好**一个**候选的编码是 `.obj` 符号的后缀。

    宁可少一分特异性，不可多一分假报：编码表拿不准的类型一律判"不可确定"。
    """
    if not symbol or not symbol.startswith('?') or len(candmap) < 2:
        return candmap
    cls = key.rsplit('::', 1)[0] if '::' in key else ''
    codes = {}
    for va, text in candmap.items():
        variants = _param_suffix_variants(text, cls)
        if not variants:
            return candmap
        codes[va] = variants
    if len({frozenset(v) for v in codes.values()}) != len(codes):
        return candmap
    hit = {va for va, v in codes.items() if any(symbol.endswith(c) for c in v)}
    if 0 < len(hit) < len(candmap):
        return {va: candmap[va] for va in hit}
    return candmap


def _hex_va(va):
    return '0x%08X' % va if va is not None else '—'


def _fmt_vas(vas):
    return '{%s}' % ', '.join('0x%08X' % v for v in (vas or ()))


# =====================================================================================
# 2. .obj 侧读取（复用 coff_vtable 的 reloc/aux 索引处理）
# =====================================================================================

@dataclass(frozen=True)
class ObjSlot:
    """一个槽：reloc 目标**符号名**（`None` = 字面量 0 槽/未解析）+ 节内偏移。"""
    name: str
    offset: int

    @property
    def is_literal(self):
        return self.name is None


@dataclass(frozen=True)
class ObjVTable:
    """编译产物侧的一张表。

    value = 符号值 = **address point 偏移**（真机 = 4：前面 4 字节是 RTTI COL 指针）。
    col_symbol = `vtable[-1]` 处 reloc 指向的 `??_R4...`（无 COL ⇒ None）。
    """
    symbol: str
    section_index: int
    value: int
    slots: tuple
    col_symbol: str = None
    address_point_offset: int = 0
    pre_col_symbol: str = None
    notes: tuple = ()


@dataclass(frozen=True)
class ObjArtifacts:
    """一次解析出的 COFF 全量件（sections / 原始索引符号表 / reloc / 函数符号索引）。"""
    path: str
    sections: tuple
    by_index: dict
    relocs: dict
    sym_index: dict

    def section(self, index):
        return self.sections[index]

    def symbol(self, name):
        i = self.sym_index.get(name)
        return self.by_index.get(i) if i is not None else None


def parse_obj_artifacts(path):
    """解析 .obj → ObjArtifacts（**复用** `coff_vtable.parse_obj`，不重复建设）。"""
    sections, by_index, relocs = cv.parse_obj(path)
    sym_index = {}
    for i, s in by_index.items():
        sym_index.setdefault(s['name'], i)
    return ObjArtifacts(path=path, sections=tuple(sections), by_index=by_index,
                        relocs=relocs, sym_index=sym_index)


def obj_vtables(path, artifacts=None):
    """`??_7<Cls>@@6B...@` 符号 → ObjVTable（槽名序列 + COL/address point）。

    槽序列**复用** `coff_vtable.extract_vtables`（含其终止规则与原始索引解名）。
    槽偏移 = `value + 4*i`（表槽是连续 DWORD，真机实测与 reloc 偏移一致）。
    """
    art = artifacts if artifacts is not None else parse_obj_artifacts(path)
    names = cv.extract_vtables(path)
    out = {}
    for sym, slot_names in names.items():
        info = art.symbol(sym)
        if not info:
            continue
        si = info['section'] - 1
        if si < 0 or si >= len(art.sections):
            continue
        value = info['value']
        slots = tuple(ObjSlot(nm, value + 4 * i) for i, nm in enumerate(slot_names))
        pre = art.relocs.get((si, value - 4)) if value >= 4 else None
        col = pre if (pre and pre.startswith('??_R4')) else None
        notes = []
        if pre and not col:
            notes.append('value-4 处有非 ??_R4 的 reloc（%s）⇒ 未计为 RTTI COL' % pre)
        out[sym] = ObjVTable(symbol=sym, section_index=si, value=value, slots=slots,
                             col_symbol=col, address_point_offset=value,
                             pre_col_symbol=pre, notes=tuple(notes))
    return out


def obj_vbtables(path, artifacts=None):
    """`??_8<Cls>@@7B@` → vbtable 内容（**字面量** DWORD 序列，无重定位）。

    真机：`??_8D@@7B@` = [-4, 24]（首项 = vbtable 自身的 this 偏移，其后 = 各虚基偏移）。
    """
    art = artifacts if artifacts is not None else parse_obj_artifacts(path)
    out = {}
    for i, s in sorted(art.by_index.items()):
        if not s['name'].startswith('??_8'):
            continue
        si = s['section'] - 1
        if si < 0 or si >= len(art.sections):
            continue
        data = art.sections[si]['data']
        off = s['value']
        n = (len(data) - off) // 4
        out[s['name']] = tuple(
            struct.unpack_from('<i', data, off + 4 * k)[0] for k in range(max(n, 0)))
    return out


def resolve_obj_thunk(artifacts, name):
    """obj 内 thunk 体解码 → AdjustorChain（**跳转目标用 reloc 解，不用算地址**）。"""
    info = artifacts.symbol(name)
    if not info:
        return AdjustorChain(ok=False, reason='符号不在符号表：%s' % name)
    si = info['section'] - 1
    if si < 0 or si >= len(artifacts.sections):
        return AdjustorChain(ok=False, reason='符号未定义在本 .obj 的节里：%s' % name)
    sec = artifacts.sections[si]
    data = sec['data']
    base = info['value']

    def read(off, n):
        return data[off:off + n] if 0 <= off and off + n <= len(data) else b''

    chain = decode_adjustor_chain(read, base)
    if not chain.ok:
        return chain
    tgt = None
    if chain.jmp_operand_offset >= 0:
        tgt = artifacts.relocs.get((si, base + chain.jmp_operand_offset))
    notes = chain.notes
    if tgt is None and chain.jmp_operand_offset >= 0:
        notes = notes + ('尾 jmp 处无 DIR32 reloc ⇒ 目标未知（非 adjustor 形态？）',)
    return replace(chain, target_symbol=tgt, notes=notes)


# =====================================================================================
# 3. thunk 解码（两侧共用：读函数注入 ⇒ .obj 用节偏移，镜像用 VA）
# =====================================================================================

@dataclass(frozen=True)
class AdjustorChain:
    """adjustor thunk 的解码结果（归一所需的全部量）。

    static_delta：`sub ecx,N` ⇒ +N；`add ecx,N` ⇒ -N（语义 = **子对象偏移**，
                  真机 vt3：B3 子对象在 D3 里偏移 8，thunk = `sub ecx,8`）。
    dynamic：     delta 来自 vbtable 运行期值（`2b 49 xx` = `sub ecx,[ecx+disp]`）。
    steps：       归一后的指令文本（喂 Task 2 分类器；它只认原始指令形态）。
    """
    ok: bool
    kind: str = ''
    kind_hint: str = ''
    static_delta: int = 0
    dynamic: bool = False
    dynamic_disp: int = 0
    target_va: int = 0
    target_symbol: str = None
    key: str = ''
    steps: tuple = ()
    jmp_operand_offset: int = -1
    reason: str = ''
    notes: tuple = ()


def _hex(v):
    return ('-0x%x' % -v) if v < 0 else ('0x%x' % v)


def _read_some(read, addr, n):
    """尽力读 n 字节（节尾的 5 字节 jmp 常读不满 8）——返回可读到的字节（可能 < n）。"""
    for k in range(n, 1, -1):
        try:
            b = read(addr, k)
        except Exception:
            continue
        if b and len(b) == k:
            return b
    try:
        return read(addr, 2) or b''
    except Exception:
        return b''


def decode_adjustor_chain(read, addr, max_steps=8):
    """解码 `[this 调整链] + 尾部 jmp` → AdjustorChain（两侧共用）。

    支持的真机形态（x86 32 位，全部来自实测反汇编）：
      `83 e9 ib` / `81 e9 id`  sub ecx, imm     （静态；真机 vt3/c2）
      `83 c1 ib` / `81 c1 id`  add ecx, imm     （静态，反向；真机 PAL3 0x445920）
      `2b 49 xx` / `03 49 xx`  sub/add ecx,[ecx+disp]（动态 delta；真机 dv2/c2）
      `8b 49 xx`               mov ecx,[ecx+disp]   （动态 delta 中转）
      `e9 rel32` / `eb rel8`   jmp target       （thunk 尾；obj 侧目标另由 reloc 解）

    **只接受"整条链恰好以 jmp 结束"**：普通函数的序言（如 `8b 41 10`）会立刻落到
    未知指令 ⇒ ok=False，不会把普通函数误判成 thunk。

    `read` 可以是 `f(addr, n)->bytes`，也可以是任何带 `.read` 的镜像对象。
    """
    if not callable(read) and hasattr(read, 'read'):
        read = read.read
    steps = []
    notes = []
    delta = 0
    dynamic = False
    dynamic_disp = 0
    cursor = addr
    for _ in range(max_steps):
        b = _read_some(read, cursor, 8)
        if len(b) < 2:
            return AdjustorChain(ok=False, reason='读取越界（0x%X）' % cursor)
        if b[0] == 0xE9 and len(b) >= 5:
            rel = struct.unpack_from('<i', b, 1)[0]
            target = cursor + 5 + rel
            steps.append('jmp     0x%x' % target)
            kind_hint = KIND_ADJUSTOR_VBASE if dynamic else KIND_ADJUSTOR_STATIC
            return AdjustorChain(ok=True, kind_hint=kind_hint, static_delta=delta,
                                 dynamic=dynamic, dynamic_disp=dynamic_disp,
                                 target_va=target, steps=tuple(steps),
                                 jmp_operand_offset=cursor - addr + 1, notes=tuple(notes))
        if b[0] == 0xEB and len(b) >= 2:
            rel = struct.unpack_from('<b', b, 1)[0]
            target = cursor + 2 + rel
            steps.append('jmp     0x%x' % target)
            kind_hint = KIND_ADJUSTOR_VBASE if dynamic else KIND_ADJUSTOR_STATIC
            return AdjustorChain(ok=True, kind_hint=kind_hint, static_delta=delta,
                                 dynamic=dynamic, dynamic_disp=dynamic_disp,
                                 target_va=target, steps=tuple(steps),
                                 jmp_operand_offset=cursor - addr + 1, notes=tuple(notes))
        if b[0] == 0x83 and b[1] in (0xE9, 0xC1) and len(b) >= 3:
            imm = struct.unpack_from('<b', b, 2)[0]
            step = imm if b[1] == 0xE9 else -imm
            delta += step
            steps.append('%s     ecx, 0x%x' % ('sub' if b[1] == 0xE9 else 'add', imm))
            cursor += 3
            continue
        if b[0] == 0x81 and b[1] in (0xE9, 0xC1) and len(b) >= 6:
            imm = struct.unpack_from('<i', b, 2)[0]
            step = imm if b[1] == 0xE9 else -imm
            delta += step
            steps.append('%s     ecx, 0x%x' % ('sub' if b[1] == 0xE9 else 'add', imm))
            cursor += 6
            continue
        if b[0] in (0x2B, 0x03, 0x8B) and b[1] == 0x49 and len(b) >= 3:
            disp = struct.unpack_from('<b', b, 2)[0]
            dynamic = True
            dynamic_disp = disp
            mnem = {0x2B: 'sub', 0x03: 'add', 0x8B: 'mov'}[b[0]]
            steps.append('%s     ecx, [ecx%s]' % (mnem, _hex(disp)))
            notes.append('动态 delta：从 vbtable/[ecx%s] 取值（B-4 三元组的 dynamic 维）'
                         % _hex(disp))
            cursor += 3
            continue
        return AdjustorChain(ok=False, reason='非 adjustor 形态（0x%X: %s）'
                             % (cursor, b[:4].hex(' ')), steps=tuple(steps))
    return AdjustorChain(ok=False, reason='调整链超过 %d 步' % max_steps, steps=tuple(steps))


# =====================================================================================
# 4. 二进制镜像（PE 读取 + 节判定）
# =====================================================================================

class ImageError(Exception):
    pass


class PEImage:
    """PAL3.exe 的只读镜像视图（VA → 文件偏移）。

    真机节表（image base 0x400000）：`.text va=0x1000 rsz=0x169000` /
    `.rdata va=0x16A000 rsz=0x16000` ⇒ VA-0x400000 即文件偏移（节对齐一致）。
    这里仍按节表通用计算，不硬编码。
    """

    is_pe = True

    def __init__(self, path=EXE):
        self.path = path
        with open(path, 'rb') as f:
            self.data = f.read()
        pe = struct.unpack_from('<I', self.data, 0x3c)[0]
        if self.data[pe:pe + 4] != b'PE\x00\x00':
            raise ImageError('不是 PE 文件：%s' % path)
        nsec = struct.unpack_from('<H', self.data, pe + 6)[0]
        optsz = struct.unpack_from('<H', self.data, pe + 20)[0]
        self.image_base = struct.unpack_from('<I', self.data, pe + 24 + 28)[0]
        so = pe + 24 + optsz
        secs = []
        for _ in range(nsec):
            nm = self.data[so:so + 8].rstrip(b'\x00').decode('ascii', 'replace')
            vsz, va, rsz, roff = struct.unpack_from('<IIII', self.data, so + 8)
            chars = struct.unpack_from('<I', self.data, so + 36)[0]
            secs.append({'name': nm, 'va': self.image_base + va, 'vsize': vsz,
                         'raw': roff, 'rsize': rsz, 'executable': bool(chars & 0x20000000)})
            so += 40
        self.sections = tuple(secs)

    def _sec_of(self, va):
        for s in self.sections:
            size = max(s['vsize'], s['rsize'])
            if s['va'] <= va < s['va'] + size:
                return s
        return None

    def can_read(self, va, n=4):
        s = self._sec_of(va)
        return bool(s) and (va - s['va']) + n <= s['rsize']

    def read(self, va, n):
        s = self._sec_of(va)
        if not s or (va - s['va']) + n > s['rsize']:
            raise ImageError('VA 0x%X 不可读（%d 字节）' % (va, n))
        off = s['raw'] + (va - s['va'])
        return self.data[off:off + n]

    def dword(self, va):
        return struct.unpack('<I', self.read(va, 4))[0]

    def in_section(self, va, name):
        s = self._sec_of(va)
        return bool(s) and s['name'] == name

    def in_code(self, va):
        s = self._sec_of(va)
        return bool(s) and s['executable']


class BytesImage:
    """内存镜像（测试/合成用）：`add_section(name, va, data)`。

    `va` 是**相对 `image_base` 的节 RVA**（与 PE 节表一致）；读写一律用**绝对 VA**。
    """

    is_pe = False

    def __init__(self, image_base=0x400000):
        self.image_base = image_base
        self.sections = []

    def add_section(self, name, va, data, executable=False):
        self.sections.append({'name': name, 'va': self.image_base + va,
                              'vsize': len(data), 'raw': None, 'rsize': len(data),
                              'executable': executable, 'data': bytes(data)})
        self.sections.sort(key=lambda s: s['va'])
        return len(self.sections)

    def _sec_of(self, va):
        for s in self.sections:
            if s['va'] <= va < s['va'] + len(s['data']):
                return s
        return None

    def can_read(self, va, n=4):
        s = self._sec_of(va)
        return bool(s) and (va - s['va']) + n <= len(s['data'])

    def read(self, va, n):
        s = self._sec_of(va)
        if not s or (va - s['va']) + n > len(s['data']):
            raise ImageError('VA 0x%X 不可读（%d 字节）' % (va, n))
        off = va - s['va']
        return s['data'][off:off + n]

    def dword(self, va):
        return struct.unpack('<I', self.read(va, 4))[0]

    def in_section(self, va, name):
        s = self._sec_of(va)
        return bool(s) and s['name'] == name

    def in_code(self, va):
        s = self._sec_of(va)
        return bool(s) and s['executable']


# =====================================================================================
# 5. 二进制侧表界定 + 归一
# =====================================================================================

@dataclass(frozen=True)
class BinTable:
    """二进制侧一张表：base = address point（ctor 实写的 vptr 目标）。"""
    base: int
    end: int
    slots: tuple
    confidence: str = 'high'
    family: str = None
    col: int = None
    broken_at: str = None
    address_point_offset: int = 0
    notes: tuple = ()

    @property
    def count(self):
        return len(self.slots)


def _default_family_of(idx):
    import vtable_compare as vc

    def f(va):
        return vc.class_family((idx or {}).get(va, ''))
    return f


def bin_table_from_image(image, base, *, idx=None, targets=(), family_of=None,
                         max_slots=4096):
    """界定二进制表长并读出槽 VA 序列（三信号，与 `vtable_compare.bin_table` 同规则）。

    1. **硬上界**：下一个 ctor 实写的表起始（`targets`，由 `load_bin_targets` 给）；
    2. **非代码指针**：槽必须落在可执行节，否则断表；
    3. **类族一致性**：首槽的类族已知时，出现**可识别为别的类族**的槽即断表
       （提不出类族的槽不算断裂；真机 `CEffShock` 的连续子表排布实测需要这条）。

    **address point 偏移**：若传入的 `base` 其实是 **RTTI COL 地址**（`base` 处是
    `.rdata` 指针而 `base+4` 起才是代码指针），自动前进 4 字节并把
    `address_point_offset=4` 记进结果（简报"槽数数含 RTTI COL 前缀"）。

    ⚠️ 与 `vtable_compare.bin_table` 的关系：规则相同，但本函数把**镜像与索引**做成
    注入件（`vtable_compare.bin_table` 硬绑 PAL3.exe 常量、每次调用重读文件 ⇒
    不可测）。真机路径上两者结果**逐字一致**（189/189，见
    `tests/test_vtable_verify.py::test_bin_table_matches_vtable_compare_on_real_binary`）。

    ⚠️ 真机 RTTI 实测（2026-09-25，本任务）：`original/PAL3.exe` 全库只有 6 条
    `.?AV` 串且全是 CRT/STL（`_Exception`/`exception`/`logic_error`/`length_error`/
    `out_of_range`/`type_info`）⇒ **游戏类 vtable 没有 COL**（189 张表仅 5 张的前一
    DWORD 恰好落在 .rdata 且多为 float 数据，不是 COL）。因此若 .obj 侧出现
    `??_R4...` COL，`compare_tables` 的 `address_point_rtti` 偏差就是**真发现**
    （目标表少 4 字节 ⇒ 逐槽地址位移），不是噪声。
    """
    ap = 0
    if base >= 4 and image.can_read(base + 4, 4):
        here = image.dword(base)
        nxt = image.dword(base + 4)
        if (image.in_section(here, '.rdata') and not image.in_code(here)
                and image.in_code(nxt)):
            ap = 4
    start = base + ap
    fam_of = family_of or _default_family_of(idx)
    nxt = [t for t in targets if t > base]
    hard_end = nxt[0] if nxt else base + 0x400
    # 类族只从**槽 0** 判定一次（与 `vtable_compare.bin_table` 逐字同规则：首槽提不出
    # 类族 ⇒ 全程不判断裂）。
    fam = fam_of(image.dword(start)) if image.can_read(start, 4) else None
    slots = []
    broken = None
    a = start
    while a + 4 <= hard_end and len(slots) < max_slots and image.can_read(a, 4):
        v = image.dword(a)
        if not image.in_code(v):
            break
        f = fam_of(v)
        if fam and f and f != fam:
            broken = '%s(0x%X)' % (f, v)
            break
        slots.append(v)
        a += 4
    col = None
    if start >= 4 and image.can_read(start - 4, 4):
        cand = image.dword(start - 4)
        if image.in_section(cand, '.rdata'):
            col = cand
    return BinTable(base=base, end=a, slots=tuple(slots),
                    confidence='high' if broken is None else 'low',
                    family=fam, col=col, broken_at=broken,
                    address_point_offset=ap,
                    notes=(('传入地址是 RTTI COL，address point = base+4',) if ap else ()))


def _classifier_kind(name, target_name, steps, is_external=False, external_symbol=''):
    """喂 Task 2 分类器（**原始指令文本 + 符号**，不解析 mangling）。"""
    syms = tuple(dict.fromkeys(x for x in (name, target_name) if x))
    ev = SlotEvidence(symbols=syms,
                      instructions='\n'.join(steps) if steps else '',
                      is_external=is_external,
                      external_symbol=external_symbol if is_external else '')
    return classify_slot(ev)


def bin_vbtable(image, va, count):
    """读二进制侧 vbtable 内容（`count` 项，由 .obj 侧的项数给出；项是**有符号**偏移）。"""
    vals = []
    for k in range(count):
        if not image.can_read(va + 4 * k, 4):
            raise ImageError('vbtable 0x%X 第 %d 项不可读' % (va, k))
        vals.append(struct.unpack('<i', image.read(va + 4 * k, 4))[0])
    return tuple(vals)


def _va_resolver(va_of):
    if va_of is None:
        return lambda key: None
    if callable(va_of):
        return va_of
    return lambda key: va_of.get(key)


def _name_candidate_groups(index, image=None):
    """VA→名字索引 → `{名字键: {目标 VA: 该候选的 idx 名}}`（**歧义名不丢弃**）。

    三条规则（每条都有真机证据，**不猜**）：

    1. **参数表剥离**（`strip_param_list`）：`gbLightObj::GetCGEntry(char)` ⇒
       `gbLightObj::GetCGEntry`——.obj 侧 mangled 归约键的形态。
    2. **thunk 名字重定向到 jmp 目标**（给了 `image` 时）：真机 0x42C8D0 的 idx 名是
       `gbLightObj::GetCGEntry(char)`（名字挂在 **thunk 自身**上），而它的 jmp 目标
       0x423860 在 idx 里**没有名字** ⇒ 不重定向就会把 .obj 侧指到 thunk 地址，
       于是"表完全正确"时反而报 `slot_key`（真机实测 8 处，全是 adjustor thunk）。
       重定向由 `decode_adjustor_chain` 的**字节**决定（`jmp rel32` 目标），不是名字猜测。
       ⚠️ 真机另有 79 条 `e9 <rel>; padding` 形态（ILT/跳转桩）同样命中此规则，
       bin 侧 `image_thunk()` 对它们给出**同一目标** ⇒ 两侧判据一致。
    3. **同名多目标全部保留**（R=2）：真机 53 组歧义名（24 槽命中、3.8%）里 43 组是
       **真重载**（`(char)`/`(void)`）、10 组**同签名**（`_sdtor_*`）——候选 VA 集是这两个
       场景唯一的可比信息；丢掉它，判据就退化成**抹掉参数编码**的名字文本 ⇒ 真重载被
       静默放行（`?DestroyEffBase@RenderTarget2@@UAEXD@Z` 与 `...UAEXXZ` 同名）。
       同一目标 VA 有多个来源名时优先留**带参数表**的那个：它是收敛判据的输入。
    """
    groups = {}
    for va, name in (index or {}).items():
        if not name:
            continue
        key = strip_param_list(name_key(name))
        if not key:
            continue
        target = va
        if image is not None:
            chain = decode_adjustor_chain(image.read, va)
            if chain.ok and chain.target_va:
                target = chain.target_va
        cur = groups.setdefault(key, {})
        old = cur.get(target)
        if old is None or ('(' in name and '(' not in old):
            cur[target] = name
    return groups


def name_to_va_candidates(index, image=None):
    """VA→名字索引 → **名字→候选 VA 集**：`{名字键: {VA: 该候选的 idx 名}}`。

    R=1 的 `name_to_va_index` 只能表达单值 ⇒ 歧义名整体剔除；而这些槽（真机 24/639）
    的 `.obj` 侧随即 `va=None` ⇒ 退回**抹掉参数**的名字判据 ⇒ 真重载被静默放行（R=2
    要挡的失效模式）。本函数保留候选集，让 `normalize_obj_slots` 能用 `.obj` 符号
    **自身的参数编码**收敛到具体重载；收敛不了则由 `compare_tables` 用包含判据判。
    """
    return _name_candidate_groups(index, image)


def name_to_va_index(index, image=None):
    """VA→名字索引 → **名字→单一 VA**（`{名字键: VA}`）——歧义名仍然剔除。

    规则见 `_name_candidate_groups`。歧义名（真机 53 组）**不进**这张单值表：单值投影
    无法表达"多个可能目标"，猜一个就是造假证据。需要候选集请用 `name_to_va_candidates`
    （R=2 起 `main()` 对比路径走它）。
    """
    return {k: next(iter(v)) for k, v in _name_candidate_groups(index, image).items()
            if len(v) == 1}


@dataclass(frozen=True)
class NormSlot:
    """归一化后的一个槽（两侧同构，可比）。

    key       名字键（`Cls::Func`）——两侧归约到同一键空间
    name_id   `key` 的**参数表剥离形态**（`GetCGEntry(char)` ⇒ `GetCGEntry`）：
              VA 不可解析时的次优判据；两侧键空间本来就不同（decomp 带参数表、
              mangled 不带），不剥就恒不等 ⇒ 表正确也误报
    va        该槽**目标函数**的 VA（能归约出来时填；两侧都有 ⇒ 身份判据用 VA）
    va_candidates
              该槽名字键在 idx 里对应的**全部候选 VA**（≥2 才填，R=2）：名字歧义
              （真重载/同签名多目标）时 `.obj` 侧只能靠它 + 参数编码收敛来判身份，
              **不可**退回抹掉参数的名字文本
    kind      Task 2 词表（fn/deleting_dtor/adjustor_static/adjustor_vbase/purecall/composite）
    offset    this 调整量。纯静态链 = 子对象偏移（`sub ecx,N` ⇒ +N）；
              **动态链上它是链里的常量部分**（B-4 三元组的 const 维），
              动态部分本身由 `dynamic` 标记（`(key, kind, 'dynamic', offset)`）
    dynamic   delta 是否来自 vbtable 运行期值（B-4）
    """
    side: str
    raw: object
    key: str
    kind: str
    offset: int = 0
    dynamic: bool = False
    va: int = None
    va_candidates: tuple = ()
    slot_index: int = -1
    notes: tuple = ()
    resolution: str = 'name'

    @property
    def name_id(self):
        """名字身份 = `key` 的**参数表剥离**形态（VA 不可解析时的判据）。"""
        return strip_param_list(self.key)

    @property
    def identity(self):
        """**单侧**身份（VA 优先，退化到名字身份）。两侧判等请用 `compare_tables`
        （它就是为此存在的：一侧有 VA、另一侧没有时**不可**拿两种判据互比；
        `va_candidates` 非空时更不可——名字键抹掉了参数编码）。"""
        return ('va', self.va) if self.va is not None else ('key', self.name_id)

    @property
    def normalized(self):
        """归一化元组（简报 §3.6）：普通 `(key,kind)`｜静态/复合 `(key,kind,offset)`
        ｜动态 `(key,kind,'dynamic',const)`。

        ⚠️ 静态 adjustor 这里是**三元组**（`(目标函数, 槽型, this 调整量)`），简报 §3.6 的
        "二元组"指 `(目标函数, this 调整量)` 这一**语义**——多出的 `kind` 维是 Task 2 词表
        要求的归一分量（复合槽与静态槽必须可比），两者语义等价，故保持三元组。
        """
        if self.dynamic:
            return (self.key, self.kind, DYNAMIC_MARK, self.offset)
        if self.kind in (KIND_ADJUSTOR_STATIC, KIND_ADJUSTOR_VBASE, KIND_COMPOSITE):
            return (self.key, self.kind, self.offset)
        return (self.key, self.kind)

    def with_va(self, va):
        return replace(self, va=va, resolution='va')

    def to_dict(self):
        d = {'side': self.side, 'index': self.slot_index, 'raw': self.raw,
             'key': self.key, 'kind': self.kind, 'normalized': list(self.normalized)}
        if self.offset:
            d['this_offset'] = self.offset
        if self.dynamic:
            d['dynamic'] = True
            d['dynamic_const'] = self.offset
        if self.va is not None:
            d['va'] = '0x%08X' % self.va
        if self.va_candidates:
            d['va_candidates'] = ['0x%08X' % v for v in self.va_candidates]
        if self.notes:
            d['notes'] = list(self.notes)
        return d


def _candidate_resolver(cands_of):
    """`va_candidates_of` → 解析函数 `名字键 → {VA: idx 名}`（值给 VA 序列也接受）。"""
    if cands_of is None:
        return lambda key: None
    get = cands_of if callable(cands_of) else (lambda key: (cands_of or {}).get(key))

    def f(key):
        v = get(key)
        if not v:
            return None
        if isinstance(v, dict):
            return dict(v)
        return {va: None for va in v}
    return f


def normalize_obj_slots(table, artifacts, va_of=None, va_candidates_of=None):
    """编译产物侧 → list[NormSlot]（thunk 归一 + kind 分类 + VA 归约）。

    `va_of` = **名字→单一 VA** 映射（R=1 路径；键是参数表剥离后的名字）。
    `va_candidates_of` = **名字→候选 VA 集**（`name_to_va_candidates()` 的产物；
    值可为 `{VA: idx 名}` 或 VA 序列）。`.obj` 是**可重定位**产物、自己不知道会被链到
    哪 ⇒ 只能靠符号名键查真实 VA；查不到就退：**歧义名（≥2 候选）**先用 `.obj` 符号
    **自身的参数编码**收敛（`_refine_candidates_by_symbol`），收敛不了就把候选集记进
    `NormSlot.va_candidates` 交给 `compare_tables` 的**包含判据**（R=2）；
    两侧都没有任何 VA 信息时才退回名字判据。
    """
    resolve = _va_resolver(va_of)
    cand_of = _candidate_resolver(va_candidates_of)
    out = []
    for i, slot in enumerate(table.slots):
        if slot.is_literal:
            out.append(NormSlot(side=SIDE_OBJ, raw=None, key='<literal>', kind=KIND_FN,
                                slot_index=i, notes=('字面量 0 槽（无 reloc）',),
                                resolution='literal'))
            continue
        chain = resolve_obj_thunk(artifacts, slot.name) if is_thunk_symbol(slot.name) else None
        target = (chain.target_symbol if chain and chain.target_symbol else slot.name)
        steps = chain.steps if chain else ()
        ext = (slot.name or '').lower().lstrip('_') == 'purecall'
        cl = _classifier_kind(slot.name, target if target != slot.name else '', steps,
                              is_external=ext, external_symbol=slot.name if ext else '')
        notes = list(cl.notes)
        if chain and not chain.ok:
            notes.append('thunk 符号但体解码失败：%s' % chain.reason)
        if chain and chain.ok:
            notes.extend(chain.notes)
        key = name_key(target)
        keyid = strip_param_list(key)
        va = resolve(key)
        if va is None and keyid != key:
            # 文本名带参数表时（非 mangled 符号）也尝试剥离形态
            va = resolve(keyid)
        cands = ()
        if va is None:
            cm = cand_of(keyid) or cand_of(key)
            if cm and len(cm) >= 2:
                cands = tuple(sorted(cm))
                narrowed = _refine_candidates_by_symbol(target, keyid or key, cm)
                if len(narrowed) == 1:
                    va = next(iter(narrowed))
                    notes.append('名字歧义（同一 name_id 对应 %d 个候选 VA %s）：按 .obj 符号'
                                 '%s 的参数编码收敛到 %s'
                                 % (len(cm), _fmt_vas(cands), target, _hex_va(va)))
                else:
                    notes.append('名字歧义（同一 name_id 对应 %d 个候选 VA %s）：参数编码不可'
                                 '收敛 ⇒ 由 compare_tables 用**包含判据**判（不退回名字）'
                                 % (len(cm), _fmt_vas(cands)))
            elif cm and len(cm) == 1:
                va = next(iter(cm))
        out.append(NormSlot(side=SIDE_OBJ, raw=slot.name, key=key, kind=cl.kind,
                            offset=(chain.static_delta if chain and chain.ok else 0),
                            dynamic=bool(chain and chain.ok and chain.dynamic),
                            va=va, va_candidates=cands, slot_index=i, notes=tuple(notes),
                            resolution=('va' if va is not None
                                        else ('candidates' if cands else 'name'))))
    return out


def image_thunk(image, addr, index=None):
    """镜像侧 thunk 解码 + 分类（目标 VA 直接由 `jmp rel32` 算出）。"""
    chain = decode_adjustor_chain(image.read, addr)
    if not chain.ok:
        return chain
    name = (index or {}).get(addr, '')
    tname = (index or {}).get(chain.target_va, '')
    ext = (name or '').lower().lstrip('_') == 'purecall'
    cl = _classifier_kind(name, tname, chain.steps, is_external=ext,
                          external_symbol=name if ext else '')
    key = name_key(tname) if tname else (name_key(name) or '0x%08X' % addr)
    return replace(chain, kind=cl.kind, key=key, notes=tuple(chain.notes) + tuple(cl.notes))


def normalize_bin_slots(table, image, index=None):
    """二进制侧 → list[NormSlot]（thunk 归一 + kind 分类 + **已知真实 VA**）。

    `va` **直接取已知的真实 VA**：thunk 槽 = `jmp` 目标（`th.target_va`），普通槽 = 槽自身 VA。

    ⚠️ **刻意不做名字反查**（C1 修复轮 R=1 的同源缺陷）：反查要么依赖外部映射、
    要么把**已经算出来的真实 VA 丢掉**（真机 146 槽在 idx 里没有名字 ⇒ 反查必得 None），
    于是两侧 `va` 恒为 None、身份判据退化成名字文本 ⇒ 表正确也误报。
    这里的 VA 是**字节证据**（槽指针 + `jmp rel32`），不依赖名字，也不依赖 idx 覆盖。
    """
    out = []
    for i, va in enumerate(table.slots):
        name = (index or {}).get(va, '')
        th = image_thunk(image, va, index)
        if th.ok:
            tname = (index or {}).get(th.target_va, '')
            key = th.key
            kind = th.kind
            notes = th.notes
            dyn = th.dynamic
            off = th.static_delta
            tva = th.target_va                       # jmp 目标 = 真实目标函数 VA
        else:
            cl = _classifier_kind(name, '', ())
            key = name_key(name) or '0x%08X' % va
            kind = cl.kind
            notes = tuple(cl.notes)
            dyn = False
            off = 0
            tva = va                                 # 普通槽：它自己就是目标函数
        out.append(NormSlot(side=SIDE_BIN, raw='0x%08X' % va, key=key, kind=kind,
                            offset=off, dynamic=dyn, va=tva, slot_index=i,
                            notes=notes, resolution='va'))
    return out


# =====================================================================================
# 6. 对比 + 偏差报告
# =====================================================================================

@dataclass(frozen=True)
class Deviation:
    """一处偏差：**定位到具体槽位 + kind**（这是本工具的核心契约）。"""
    kind: str
    index: int
    obj: object = None
    bin: object = None
    detail: str = ''

    def to_dict(self):
        return {'kind': self.kind, 'index': self.index, 'obj': self.obj,
                'bin': self.bin, 'detail': self.detail}


@dataclass
class CompareResult:
    ok: bool
    obj_count: int
    bin_count: int
    deviations: tuple = ()
    identity_mode: str = 'name'
    obj_label: str = ''
    bin_label: str = ''
    obj_col: object = None
    bin_col: object = None
    obj_address_point_offset: object = None
    bin_address_point_offset: object = None
    notes: tuple = ()

    def to_dict(self):
        return {'ok': self.ok, 'obj_label': self.obj_label, 'bin_label': self.bin_label,
                'obj_count': self.obj_count, 'bin_count': self.bin_count,
                'identity_mode': self.identity_mode,
                'obj_col': self.obj_col, 'bin_col': self.bin_col,
                'obj_address_point_offset': self.obj_address_point_offset,
                'bin_address_point_offset': self.bin_address_point_offset,
                'notes': list(self.notes),
                'deviations': [d.to_dict() for d in self.deviations]}


def _inherited_alias_hint(k1, k2):
    """`A3::onlyA` vs `D3::onlyA` 这类"仅归属类不同"的**提示**（不改判据，只帮人工定性）。

    MI 下继承槽在 .obj 侧保留**基类** mangled 归属，而二进制侧名字可能来自注解/IDA
    显示名（写派生类）⇒ 逐槽对比会在这里报 `slot_key`。**不自动判等**：把
    `A3::ff` 当成 `D3::ff` 会放过"表里装了错误基类函数"的真错，故只留痕。

    比较前**剥参数表**（C1 修复轮 R=1）：bin 侧真机名形如 `D3::onlyA(char)`，不剥就
    `onlyA` ≠ `onlyA(char)` ⇒ 连提示都不留。

    ⚠️ **归属类必须真的不同**（R=2）：真重载（`Cls::m(char)` vs `Cls::m(void)`）方法名
    相同、类相同，此时提示"仅归属类不同"是**误导**（会把操作员引到 MI 归属方向，而真因
    是重载装错）。
    """
    k1, k2 = strip_param_list(k1), strip_param_list(k2)
    if not k1 or not k2 or '::' not in k1 or '::' not in k2:
        return ''
    c1, f1 = k1.rsplit('::', 1)
    c2, f2 = k2.rsplit('::', 1)
    if f1 == f2 and c1 != c2:
        return '（方法名一致、仅归属类不同 ⇒ 可能是 MI 继承槽的名字归属差异，需人工核）'
    return ''


def _name_id_unknown(key):
    """名字键是 `0x<VA>` 占位（idx 里没有名字）⇒ 名字判据不可用（真机 146 槽）。"""
    return bool(key) and key.startswith('0x') and all(
        c in '0123456789ABCDEFabcdefx' for c in key)


def _slot_identity_decision(o, b):
    """逐槽身份判据 → `(same, crit, used_va_info)`。

    判据优先级（C1 R=1 + R=2）：

    1. 两侧都有**单一 VA** ⇒ 比 VA（唯一真身份）；
    2. 一侧单一 VA、另一侧**候选集** ⇒ 要求 `VA ∈ 候选集`（**包含判据**）；
    3. 两侧都只有**候选集** ⇒ 要求两集**交集非空**；
    4. 两侧都没有任何 VA 信息 ⇒ 才比 `name_id`（参数表剥离后的名字，次优判据）。

    ⚠️ 候选集非空时**绝不**退回名字判据：`name_key` 抹掉参数编码，真重载会被判相同
    （真机 `?DestroyEffBase@RenderTarget2@@UAEXD@Z` vs `...UAEXXZ` ⇒ 静默放行）。
    ⚠️ 只有 `.obj` 侧可能有候选集：bin 侧 `va` 一定是已知真实 VA（字节证据）。
    """
    if o.va is not None and b.va is not None:
        return (o.va == b.va), 'VA', True
    if o.va is not None and b.va_candidates:
        return (o.va in b.va_candidates), '候选集', True
    if b.va is not None and o.va_candidates:
        return (b.va in o.va_candidates), '候选集', True
    if o.va_candidates and b.va_candidates:
        return bool(set(o.va_candidates) & set(b.va_candidates)), '候选集', True
    return (o.name_id == b.name_id), '名字', False


def compare_vbtable(obj_vals, bin_vals, obj_label='obj', bin_label='bin'):
    """vbtable 内容逐项对比（虚继承类）。偏差定位到**项下标**。"""
    obj_vals = tuple(obj_vals or ())
    bin_vals = tuple(bin_vals or ())
    devs = []
    if len(obj_vals) != len(bin_vals):
        devs.append(Deviation('vbtable_count', min(len(obj_vals), len(bin_vals)),
                              len(obj_vals), len(bin_vals),
                              'vbtable 项数不同'))
    for i in range(min(len(obj_vals), len(bin_vals))):
        if obj_vals[i] != bin_vals[i]:
            devs.append(Deviation('vbtable_value', i, obj_vals[i], bin_vals[i],
                                  'vbtable[%d] %d ≠ %d' % (i, obj_vals[i], bin_vals[i])))
    return CompareResult(ok=not devs, obj_count=len(obj_vals), bin_count=len(bin_vals),
                         deviations=tuple(devs), obj_label=obj_label, bin_label=bin_label)


def compare_tables(obj_slots, bin_slots, *, obj_col=None, bin_col=None,
                   obj_label='obj', bin_label='bin',
                   obj_vbtable=None, bin_vbtable=None,
                   obj_address_point_offset=None, bin_address_point_offset=None):
    """两侧归一槽序列对比 → CompareResult（逐槽 + 槽数 + COL + vbtable）。

    **逐槽身份判据**（C1 修复轮 R=1 + R=2）：见 `_slot_identity_decision`——两侧都有单一
    VA ⇒ 比 VA；一侧单一 VA、另一侧候选集 ⇒ 包含判据；两侧都只有候选集 ⇒ 交集非空；
    **只有**两侧都没有任何 VA 信息时才比 `name_id`（参数表剥离后的名字）。

    混用两种判据**不可**（一侧有 VA 一侧没有时拿 `('va',N)` 与 `('key','X')` 比恒不等
    ⇒ 必然假报），这正是修复前的退化形态。名字判据更**不可**用于有候选集的槽：名字键
    抹掉参数编码 ⇒ 真重载被判相同（R=2 的真机实证：表 `0x56F674` 槽 0 是
    `DestroyEffBase(char)`@`0x4C1640`，`.obj` 装 `(void)` 时修复前零偏差）。

    `address_point_offset` 只**留痕**不参与判定：COL 的存在性已由 `address_point_rtti`
    判据覆盖（两侧 COL 都存在时偏移差异是 0 vs 0），单独判定会与那条判据重复报同一事实。
    """
    obj_slots = list(obj_slots or [])
    bin_slots = list(bin_slots or [])
    devs = []
    notes = []

    # RTTI COL 前缀（address point 前的 4 字节）：只比**存在性**（两侧身份空间不同）
    if (obj_col is None) != (bin_col is None):
        devs.append(Deviation('address_point_rtti', -1, obj_col, bin_col,
                              'RTTI COL 前缀不一致：obj=%r bin=%r' % (obj_col, bin_col)))
    if obj_col is not None and bin_col is not None:
        notes.append('RTTI COL：obj=%r bin=0x%X' % (obj_col, bin_col))

    if len(obj_slots) != len(bin_slots):
        devs.append(Deviation('slot_count', min(len(obj_slots), len(bin_slots)),
                              len(obj_slots), len(bin_slots),
                              '槽数不同：obj %d ≠ bin %d' % (len(obj_slots), len(bin_slots))))

    votes = set()
    unnamed = 0
    cand_slots = 0
    for i in range(min(len(obj_slots), len(bin_slots))):
        o, b = obj_slots[i], bin_slots[i]
        same, crit, used_va = _slot_identity_decision(o, b)
        votes.add('va' if used_va else 'name')
        if crit == '候选集':
            cand_slots += 1
        if not same:
            if crit == '名字' and (_name_id_unknown(o.name_id) or _name_id_unknown(b.name_id)):
                unnamed += 1
            detail = 'slot %d 目标不同（%s判据）：obj=%s bin=%s' % (i, crit, o.key, b.key)
            if crit == 'VA':
                detail += '（VA obj=%s bin=%s）' % (_hex_va(o.va), _hex_va(b.va))
            elif crit == '候选集':
                detail += '（候选集 %s；obj VA=%s bin VA=%s）' % (
                    _fmt_vas(o.va_candidates or b.va_candidates), _hex_va(o.va), _hex_va(b.va))
            hint = _inherited_alias_hint(o.key, b.key)
            if hint:
                detail += ' ' + hint
            devs.append(Deviation('slot_key', i, o.key, b.key, detail))
            continue
        if o.kind != b.kind:
            devs.append(Deviation('slot_kind', i, o.kind, b.kind,
                                  'slot %d 槽型不同：obj=%s bin=%s' % (i, o.kind, b.kind)))
        if (o.offset, o.dynamic) != (b.offset, b.dynamic):
            devs.append(Deviation('this_adjust', i, (o.offset, o.dynamic),
                                  (b.offset, b.dynamic),
                                  'slot %d this 归一不同：obj=%s bin=%s'
                                  % (i, o.normalized, b.normalized)))

    if cand_slots:
        notes.append('%d 槽以**候选集判据**判定（同一 name_id 对应多个 VA：真重载/同签名'
                     '多目标；参数编码不可收敛时用它，**绝不**退回抹掉参数的名字文本）'
                     % cand_slots)

    if unnamed:
        notes.append('%d 槽的名字判据失败且**至少一侧无名字**（idx 无覆盖的槽，真机多为 '
                     'import thunk `ff 25 <IAT>` / CRT）⇒ VA 与名字两条判据都不可用，'
                     '按 slot_key 保守留痕，不静默放过' % unnamed)

    if obj_vbtable is not None and bin_vbtable is not None:
        devs.extend(compare_vbtable(obj_vbtable, bin_vbtable, obj_label, bin_label).deviations)
    elif obj_vbtable is not None or bin_vbtable is not None:
        # 虚继承类：vbtable 维度**未比**必须留痕（绝不静默当作"通过"）
        notes.append('vbtable 维度未比：obj=%r bin=%r（缺一侧 ⇒ 需 --bin-vbtable / '
                     '二进制 vbtable VA）' % (obj_vbtable, bin_vbtable))

    mode = 'mixed' if len(votes) > 1 else (votes.pop() if votes else 'name')
    return CompareResult(ok=not devs, obj_count=len(obj_slots), bin_count=len(bin_slots),
                         deviations=tuple(devs), identity_mode=mode,
                         obj_label=obj_label, bin_label=bin_label,
                         obj_col=obj_col, bin_col=bin_col,
                         obj_address_point_offset=obj_address_point_offset,
                         bin_address_point_offset=bin_address_point_offset,
                         notes=tuple(notes))


def render_report(result):
    """人读报告（偏差逐条带 **slot 下标 + kind**）。"""
    lines = ['vtable 对比：%s  vs  %s' % (result.obj_label, result.bin_label)]
    lines.append('  槽数：obj %d / bin %d（identity=%s）'
                 % (result.obj_count, result.bin_count, result.identity_mode))
    lines.append('  RTTI COL：obj %s / bin %s'
                 % ('有（%r）' % (result.obj_col,) if result.obj_col is not None else '无',
                    ('有（0x%X）' % result.bin_col) if result.bin_col is not None else '无'))
    if result.obj_address_point_offset is not None or result.bin_address_point_offset is not None:
        lines.append('  address point 偏移：obj %s / bin %s'
                     % (result.obj_address_point_offset, result.bin_address_point_offset))
    for n in result.notes:
        lines.append('  注：%s' % n)
    if result.ok:
        lines.append('  ✅ 逐槽一致')
        return '\n'.join(lines)
    lines.append('  ❌ %d 处偏差（定位到槽位 + kind）：' % len(result.deviations))
    for d in result.deviations:
        loc = ('slot %d' % d.index) if d.index >= 0 else 'table'
        lines.append('    %-8s %-18s obj=%r  bin=%r  %s'
                     % (loc, d.kind, d.obj, d.bin, d.detail))
    return '\n'.join(lines)


# =====================================================================================
# 7. 强制发射（lazy COMDAT 对抗）
# =====================================================================================

PROBE_STRATEGY_OBJECT = 'object'          # 普通类：构造对象
PROBE_STRATEGY_DERIVED = 'derived'        # 抽象类：具体派生类 + 构造
PROBE_STRATEGY_DUMMY_CTOR = 'dummy_ctor'  # 无虚析构的抽象类：dummy Cls::Cls(){}

ALL_PROBE_STRATEGIES = (PROBE_STRATEGY_OBJECT, PROBE_STRATEGY_DERIVED,
                        PROBE_STRATEGY_DUMMY_CTOR)


@dataclass(frozen=True)
class ProbeSpec:
    """探针 TU 的输入（类名 + 头 + 抽象性 + 纯虚清单 + 是否声明 ctor）。"""
    cls: str
    header: str = ''
    abstract: bool = False
    has_virtual_dtor: bool = False
    ctor_declared: bool = False
    pure_virtuals: tuple = ()
    extra_preamble: str = ''
    strategies: tuple = ()

    @property
    def shim(self):
        return 'VtvProbe' + self.cls.replace('::', '_')


@dataclass
class EmissionResult:
    obj_path: str
    strategy: str
    symbols: tuple
    attempts: tuple = ()
    stdout: str = ''
    notes: tuple = ()

    def to_dict(self):
        return {'obj': self.obj_path, 'strategy': self.strategy,
                'symbols': list(self.symbols), 'attempts': self.attempts,
                'notes': list(self.notes)}


class EmissionError(Exception):
    """全部策略都无法让 `??_7<Cls>@@` 出现在 .obj 里。

    带 `probe_source`（最后尝试的探针源）与 `attempts`（每次策略的痕迹）——
    这正是"惰性 COMDAT 未发射"与"对比通过"的分界线。
    """

    def __init__(self, message, probe_source='', attempts=()):
        super().__init__(message)
        self.probe_source = probe_source
        self.attempts = list(attempts)


def default_strategies(spec):
    """策略顺序：**先最稳的**。

    抽象类：有 ctor 声明 ⇒ 先 dummy ctor（真机实测 /Od 与 /O2 都发射），再 derived；
            否则只能 derived（真机 /Od 发射；/O2 可能被死存储消除 ⇒ 发射检查会抓到）。
    普通类：先 object（全局对象 ⇒ ctor 必发射），有 ctor 声明时兜底 dummy ctor。
    """
    if spec.strategies:
        return tuple(spec.strategies)
    if spec.abstract:
        out = []
        if spec.ctor_declared:
            out.append(PROBE_STRATEGY_DUMMY_CTOR)
        out.append(PROBE_STRATEGY_DERIVED)
        return tuple(out)
    out = [PROBE_STRATEGY_OBJECT]
    if spec.ctor_declared:
        out.append(PROBE_STRATEGY_DUMMY_CTOR)
    return tuple(out)


def _override_body(sig):
    return '' if sig.strip().startswith('void') else 'return 0;'


def build_probe_source(spec, strategy=None):
    """生成**强制发射**探针源（策略见 `default_strategies`）。

    三条真机事实决定了源形态：
      1. 全局对象 `Cls vtv_probe_object;` + 取址函数 ⇒ ctor 必被发射（普通类）；
      2. 抽象类只能经**具体派生类**构造（借派生 ctor 写基类 vptr）；
      3. 无虚析构的抽象类用 dummy `Cls::Cls() { }`（定义即发射；派生 shim 的 ctor
         **显式调用**它 ⇒ 不可能被当成未使用而丢弃）。
    """
    strategy = strategy or default_strategies(spec)[0]
    if strategy not in ALL_PROBE_STRATEGIES:
        raise ValueError('未知发射策略：%r' % (strategy,))
    if strategy == PROBE_STRATEGY_OBJECT and spec.abstract:
        raise ValueError('抽象类不能走 object 策略（无法构造对象）：%s' % spec.cls)
    if strategy == PROBE_STRATEGY_DERIVED:
        if not spec.abstract:
            raise ValueError('derived 策略只用于抽象类：%s' % spec.cls)
        if not spec.pure_virtuals:
            raise ValueError('derived 策略需要 pure_virtuals（否则派生类仍是抽象类）：%s'
                             % spec.cls)
    lines = []
    if spec.extra_preamble:
        lines.append(spec.extra_preamble.rstrip())
    if spec.header:
        h = spec.header.strip()
        lines.append(h if h.startswith('#') else '#include "%s"' % h)
    lines.append('// vtable_verify 强制发射探针：%s（策略 %s）' % (spec.cls, strategy))
    if strategy == PROBE_STRATEGY_DUMMY_CTOR:
        lines.append('%s::%s() { }' % (spec.cls, spec.cls))
    if spec.abstract:
        lines.append('struct %s : %s {' % (spec.shim, spec.cls))
        if strategy == PROBE_STRATEGY_DUMMY_CTOR and spec.ctor_declared:
            lines.append('    %s() : %s() { }' % (spec.shim, spec.cls))
        for sig in spec.pure_virtuals:
            lines.append('    %s { %s}' % (sig, _override_body(sig)))
        lines.append('};')
        if spec.pure_virtuals:
            lines.append('static %s vtv_probe_object;' % spec.shim)
        else:
            lines.append('// 无纯虚清单 ⇒ 只靠上面的实体定义强制发射；'
                         '若未发射，force_emit 会换策略/报错')
    else:
        lines.append('%s vtv_probe_object;' % spec.cls)
    lines.append('void* vtv_probe_used() { return (void*)&vtv_probe_object; }')
    return '\n'.join(lines) + '\n'


def compile_probe(spec, workdir, strategy, *, compiler=None, include_dirs=(),
                  flags=None):
    """写探针源并编译 → (obj 路径, 源路径, CompletedProcess)。`compiler` 可注入。"""
    os.makedirs(workdir, exist_ok=True)
    src = os.path.join(workdir, '%s_%s.cpp' % (spec.cls.replace('::', '_'), strategy))
    obj = os.path.join(workdir, '%s_%s.obj' % (spec.cls.replace('::', '_'), strategy))
    with open(src, 'w', encoding='utf-8') as f:
        f.write(build_probe_source(spec, strategy))
    fl = list(flags if flags is not None else DEFAULT_PROBE_FLAGS)
    incs = [MSVC_INCLUDE] + [d for d in include_dirs if d != MSVC_INCLUDE]
    cmd = [WINE_CL, '/c', '/nologo'] + fl + ['/I' + d for d in incs] + ['/Fo' + obj, src]
    runner = compiler or (lambda c, cwd=None: subprocess.run(
        c, cwd=cwd, capture_output=True, text=True))
    proc = runner(cmd, cwd=ROOT)
    return obj, src, proc


def force_emit(spec, workdir, *, compiler=None, include_dirs=(), flags=None):
    """按策略顺序强制发射，**编译后必须看到** `??_7<Cls>@@` 符号才算成功。

    Returns: EmissionResult（obj_path/strategy/symbols/attempts）
    Raises:  EmissionError（全部策略失败；含每次痕迹与最后的探针源）
    """
    pref = '??_7%s@@' % mangled_class_token(spec.cls)
    attempts = []
    last_src = ''
    for strategy in default_strategies(spec):
        try:
            last_src = build_probe_source(spec, strategy)
        except ValueError as e:
            attempts.append({'strategy': strategy, 'emitted': False, 'error': str(e)})
            continue
        obj, src, proc = compile_probe(spec, workdir, strategy, compiler=compiler,
                                       include_dirs=include_dirs, flags=flags)
        tail = ((proc.stdout or '') + (proc.stderr or ''))[-400:]
        if proc.returncode != 0:
            attempts.append({'strategy': strategy, 'emitted': False,
                             'error': '编译失败 exit=%s' % proc.returncode,
                             'output': tail})
            continue
        if not os.path.exists(obj):
            attempts.append({'strategy': strategy, 'emitted': False,
                             'error': '编译器未产出 %s' % obj, 'output': tail})
            continue
        found = tuple(sorted(s for s in obj_vtables(obj) if s.startswith(pref)))
        if found:
            attempts.append({'strategy': strategy, 'emitted': True, 'symbols': list(found)})
            return EmissionResult(obj_path=obj, strategy=strategy, symbols=found,
                                  attempts=tuple(attempts), stdout=tail,
                                  notes=('发射成功：%s' % ', '.join(found),))
        all_syms = tuple(sorted(obj_vtables(obj)))
        attempts.append({'strategy': strategy, 'emitted': False, 'missing': pref,
                         'symbols': list(all_syms),
                         'error': '惰性 COMDAT 未发射（缺 %s）' % pref})
    raise EmissionError(
        '强制发射失败：%s 在 %d 个策略下都没有 vtable 符号（缺 %s）'
        % (spec.cls, len(attempts), pref), probe_source=last_src, attempts=attempts)


# =====================================================================================
# 8. 真机数据接入（复用 vtable_compare 的 ctor 扫描与 VA→名字索引）
# =====================================================================================

def load_bin_targets(dis_path='/tmp/pal3.dis'):
    """ctor 实写的 vptr 目标（= 各表 address point）——复用 `vtable_compare`。"""
    import vtable_compare as vc
    return vc.bin_vptr_targets(dis_path)


def load_va_index():
    """VA → 名字（decomp JSON + 注解 functions + 注解 struct methods）——复用 `vtable_compare`。"""
    import vtable_compare as vc
    return vc.va_index()


def _pick_obj_table(tables, cls=None):
    """选一张 .obj 侧的表：`cls` 过滤；优先**主表**（`??_7<Cls>@@6B@`，无基类令牌）。"""
    cands = list(tables.values()) if not cls else         [t for t in tables.values() if cls in t.symbol]
    if not cands:
        return None
    prim = [t for t in cands if name_key(t.symbol).endswith('__vftable')]
    return sorted(prim or cands, key=lambda t: t.symbol)[0]


# =====================================================================================
# 9. CLI
# =====================================================================================

def build_arg_parser():
    ap = argparse.ArgumentParser(
        prog='vtable_verify',
        description='vtable 编译产物对比（最终裁判）：.obj 合成表 vs 二进制真实表')
    ap.add_argument('--obj', help='编译产物 .obj（取合成表）')
    ap.add_argument('--cls', help='类名过滤（对比模式下选主表）')
    ap.add_argument('--bin-base', help='二进制表 address point VA，如 0x56F7C8')
    ap.add_argument('--bin-vbtable', help='二进制 vbtable VA（虚继承类；项数取自 .obj 侧）')
    ap.add_argument('--list', action='store_true', help='列出 .obj 侧全部表（归一后）')
    ap.add_argument('--json', action='store_true', help='机读输出')
    ap.add_argument('--probe-src', metavar='CLS', help='打印强制发射探针源（不编译）')
    ap.add_argument('--header', help='探针要 #include 的头（或整条 #include 行）')
    ap.add_argument('--abstract', action='store_true', help='类为抽象类')
    ap.add_argument('--has-virtual-dtor', action='store_true', help='类有虚析构')
    ap.add_argument('--ctor-declared', action='store_true', help='类声明了 ctor')
    ap.add_argument('--pure', action='append', default=[], help='纯虚签名（可重复）')
    ap.add_argument('--selfcheck', action='store_true', help='合成夹具自检（无需 IDB/PAL3）')
    return ap


def _vbtable_for_table(vbs, table_symbol):
    """`??_7<Cls>@@6B...@` → 同类族的 `??_8<Cls>@@7B@` 内容（无则 None）。

    注意两者是**不同符号**（vbtable 不附在 vftable 符号上），必须按类令牌关联——
    真机 `??_7D3@@6BA3@@@` 与 `??_8D3@@7B@` 同属 D3。
    """
    cls = table_symbol[4:].split('@')[0] if table_symbol.startswith('??_7') else None
    if not cls:
        return None
    for sym, vals in vbs.items():
        if sym.startswith('??_8%s@@' % cls):
            return vals
    return None


def _obj_report(path, cls=None):
    art = parse_obj_artifacts(path)
    tables = obj_vtables(path, art)
    vbs = obj_vbtables(path, art)
    out = []
    for sym in sorted(tables):
        t = tables[sym]
        if cls and cls not in sym:
            continue
        slots = normalize_obj_slots(t, art)
        vb = _vbtable_for_table(vbs, sym)
        out.append({'symbol': sym, 'view': name_key(sym), 'section': t.section_index,
                    'address_point_offset': t.address_point_offset,
                    'col_symbol': t.col_symbol, 'count': len(slots),
                    'slots': [s.to_dict() for s in slots],
                    'vbtable': (list(vb) if vb is not None else None)})
    return {'obj': path, 'vtables': out}


def main(argv=None):
    args = build_arg_parser().parse_args(argv)

    if args.probe_src:
        spec = ProbeSpec(cls=args.probe_src, header=args.header or '',
                         abstract=args.abstract, has_virtual_dtor=args.has_virtual_dtor,
                         ctor_declared=args.ctor_declared,
                         pure_virtuals=tuple(args.pure))
        print(build_probe_source(spec))
        return 0

    if args.selfcheck:
        return _selfcheck()

    if not args.obj:
        print('错误：需要 --obj（或 --probe-src / --selfcheck）', file=sys.stderr)
        return 2
    if not os.path.exists(args.obj):
        print('错误：找不到 %s' % args.obj, file=sys.stderr)
        return 2

    if args.list or not args.bin_base:
        rep = _obj_report(args.obj, args.cls)
        if not rep['vtables'] and args.cls:
            print('错误：.obj 里没有匹配 %r 的 vtable' % args.cls, file=sys.stderr)
            return 2
        if args.json:
            print(json.dumps(rep, ensure_ascii=False, indent=2))
        else:
            print('%s：%d 张表' % (args.obj, len(rep['vtables'])))
            for t in rep['vtables']:
                print('  %s（%d 槽，COL=%s，address point=%d）'
                      % (t['symbol'], t['count'], t['col_symbol'],
                         t['address_point_offset']))
                for s in t['slots']:
                    print('     [%2d] %-22s %-18s %s'
                          % (s['index'], s['key'], s['kind'], s['normalized']))
                if t['vbtable'] is not None:
                    print('     vbtable = %s' % (t['vbtable'],))
        return 0

    # 对比模式
    try:
        base = int(args.bin_base, 16)
    except ValueError:
        print('错误：--bin-base 需为十六进制，如 0x56F7C8', file=sys.stderr)
        return 2
    if not os.path.exists(EXE):
        print('错误：找不到 %s' % EXE, file=sys.stderr)
        return 2
    image = PEImage(EXE)
    if not image.can_read(base, 4):
        print('错误：--bin-base 0x%X 不在 %s 的可读节里' % (base, EXE), file=sys.stderr)
        return 2
    art = parse_obj_artifacts(args.obj)
    tables = obj_vtables(args.obj, art)
    tbl = _pick_obj_table(tables, args.cls)
    if tbl is None:
        print('错误：.obj 里没有可用的 vtable（--cls 过滤太严？）', file=sys.stderr)
        return 2
    idx = load_va_index()
    targets = load_bin_targets()
    bt = bin_table_from_image(image, base, idx=idx, targets=targets)
    # C1 修复轮 R=1：由**已加载的 idx** 造 名字→VA 映射（参数表剥离 + thunk 名字重定向）
    # 传给 .obj 侧 —— 不传就是修复前的形态：两侧 va 恒 None、判据退化成名字文本。
    # R=2 修复轮：改用**候选集**映射 —— 同一 name_id 对应多个 VA（真重载，真机 24/639 槽）
    # 时单值映射只能整体剔除，该槽随即退回**抹掉参数编码**的名字判据 ⇒ 真重载静默放行。
    cands = name_to_va_candidates(idx, image)
    obj_slots = normalize_obj_slots(tbl, art, va_candidates_of=cands)
    bin_slots = normalize_bin_slots(bt, image, idx)
    obj_vb = _vbtable_for_table(obj_vbtables(args.obj, art), tbl.symbol)
    bin_vb = None
    if args.bin_vbtable:
        try:
            vb_va = int(args.bin_vbtable, 16)
            bin_vb = bin_vbtable(image, vb_va, len(obj_vb or ()))
        except (ValueError, ImageError) as e:
            print('错误：--bin-vbtable 不可读（%s）' % e, file=sys.stderr)
            return 2
    res = compare_tables(obj_slots, bin_slots, obj_col=tbl.col_symbol, bin_col=bt.col,
                         obj_label='%s:%s' % (args.obj, tbl.symbol),
                         bin_label='0x%X' % base,
                         obj_vbtable=obj_vb,
                         bin_vbtable=bin_vb,
                         obj_address_point_offset=tbl.address_point_offset,
                         bin_address_point_offset=bt.address_point_offset)
    if args.json:
        print(json.dumps(res.to_dict(), ensure_ascii=False, indent=2))
    else:
        print(render_report(res))
        if bt.broken_at:
            print('  ⚠️ 表长界定置信度 %s（在 %s 处断裂 ⇒ 需人工核）'
                  % (bt.confidence, bt.broken_at))
    return 0 if res.ok else 1


def _selfcheck():
    """合成夹具自检：无需 IDB / PAL3.exe 即可验证归约与对比主链路。"""
    import tempfile
    with tempfile.TemporaryDirectory() as d:
        path = _selfcheck_fixture(os.path.join(d, 'self.obj'))
        rep = _obj_report(path, 'D3')
    prim = [t for t in rep['vtables'] if t['symbol'] == '??_7D3@@6BA3@@@'][0]
    ok = (prim['count'] == 2 and prim['col_symbol'] == '??_R4D3@@6BA3@@@'
          and prim['slots'][0]['key'] == 'D3::ff')
    print('selfcheck: %s（%s 槽 %d COL=%s）'
          % ('PASS' if ok else 'FAIL', prim['symbol'], prim['count'], prim['col_symbol']))
    return 0 if ok else 1


def _selfcheck_fixture(path):
    """与 tests/test_vtable_verify.py 同形的最小夹具（CLI 自检不依赖测试模块）。"""
    _b = _MiniCoff()
    text = bytearray()
    off = {}

    def emit(name, data):
        off[name] = len(text)
        text.extend(data)
        while len(text) % 4:
            text.append(0x90)

    emit('?ff@D3@@UAEHXZ', b'\x8b\x41\x10\xc3')
    emit('?onlyA@A3@@UAEHXZ', b'\x8b\x41\x08\xc3')
    emit('?ff@D3@@W7AEHXZ', b'\x83\xe9\x08\xe9\x00\x00\x00\x00')
    ti = _b.add_section('.text', bytes(text), chars=0x60000020)
    _b.add_reloc(ti, off['?ff@D3@@W7AEHXZ'] + 4, '?ff@D3@@UAEHXZ')
    for nm in ('?ff@D3@@UAEHXZ', '?onlyA@A3@@UAEHXZ', '?ff@D3@@W7AEHXZ'):
        _b.add_symbol(nm, ti, off[nm])
    ri = _b.add_section('.rdata', b'\x00' * 12)
    _b.add_symbol('??_7D3@@6BA3@@@', ri, 4)
    _b.add_symbol('??_R4D3@@6BA3@@@', ri, 0)
    _b.add_reloc(ri, 0, '??_R4D3@@6BA3@@@')
    _b.add_reloc(ri, 4, '?ff@D3@@UAEHXZ')
    _b.add_reloc(ri, 8, '?onlyA@A3@@UAEHXZ')
    return _b.write(path)


class _MiniCoff:
    """极小 COFF 写出器（自检用；与测试夹具同布局规则）。"""

    def __init__(self):
        self.sections = []
        self.symbols = []

    def add_section(self, name, data, chars=0x40000040):
        self.sections.append({'name': name, 'data': bytes(data), 'relocs': [],
                              'chars': chars})
        return len(self.sections)

    def add_reloc(self, sec, offset, sym):
        self.sections[sec - 1]['relocs'].append((offset, sym))

    def add_symbol(self, name, section, value, naux=0):
        self.symbols.append({'name': name, 'value': value, 'section': section,
                             'naux': naux})

    def write(self, path):
        idx = {}
        i = 0
        for s in self.symbols:
            idx.setdefault(s['name'], i)
            i += 1 + s['naux']
        num = i
        strtab = bytearray()                    # 内容从 str_tab+4 开始

        def sadd(name):
            off = 4 + len(strtab)
            strtab.extend(name.encode('ascii') + b'\x00')
            return off

        cur = 20 + 40 * len(self.sections)
        doff = []
        for s in self.sections:
            doff.append(cur if s['data'] else 0)
            cur = (cur + len(s['data']) + 3) // 4 * 4
        roff = []
        for s in self.sections:
            roff.append(cur if s['relocs'] else 0)
            cur += 10 * len(s['relocs'])
        symoff = (cur + 3) // 4 * 4
        out = bytearray(struct.pack('<HHIIIHH', 0x14c, len(self.sections), 0, symoff,
                                    num, 0, 0))
        for k, s in enumerate(self.sections):
            out += s['name'].encode()[:8].ljust(8, b'\x00')
            out += struct.pack('<IIII', 0, 0, len(s['data']), doff[k])
            out += struct.pack('<II', roff[k], 0)
            out += struct.pack('<HH', len(s['relocs']), 0)
            out += struct.pack('<I', s['chars'])
        for k, s in enumerate(self.sections):
            if not s['data']:
                continue
            out += b'\x00' * (doff[k] - len(out)) + s['data']
        for k, s in enumerate(self.sections):
            if not s['relocs']:
                continue
            out += b'\x00' * (roff[k] - len(out))
            for o, sym in sorted(s['relocs']):
                out += struct.pack('<IIH', o, idx[sym], 6)
        out += b'\x00' * (symoff - len(out))
        for s in self.symbols:
            nm = s['name'].encode('ascii')
            out += (nm.ljust(8, b'\x00') if len(nm) <= 8
                    else struct.pack('<II', 0, sadd(s['name'])))
            out += struct.pack('<IhHBB', s['value'], s['section'], 0, 2, s['naux'])
            out += b'\x00' * (18 * s['naux'])
        total = 4 + len(strtab)
        out += struct.pack('<I', total) + bytes(strtab)
        with open(path, 'wb') as f:
            f.write(bytes(out))
        return path


if __name__ == '__main__':
    sys.exit(main())