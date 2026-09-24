#!/usr/bin/env python3
"""布局断言生成器（Task 4）—— 产出 `_layout_asserts.h`（MSVC6 负数组技巧）。

**职责**：把 annotation 里的类布局（继承形状 / sizeof / 成员偏移）渲染成**编译期**校验，
让布局错误在编译时暴露，而不是等到 L1 字节比对。默认启用，全反编译期持续。

## 三条编译器规则（真机 MSVC 6.0 SP0，cl 12.00.8168 实测）

探针与逐字错误输出：`data/status/_layout_assert_probe_20260925/README.md`
（`p3.cpp` 复现 E-4，`shape.cpp` / `off.cpp` 为本任务新增的边界实测）。

1. **PMF 尺寸封闭规则（E-4）**：`sizeof(void (Cls::*)())` 是**继承形状**的函数：
   ```
   继承闭包内有虚基 ⇒ 12；否则闭包内出现多继承分支 ⇒ 8；否则 ⇒ 4
   ```
   * 多虚基仍是 12（不是 16）；
   * ★ **判据必须走传递闭包**：`DERofMI2 : MI2`（单直接基、但基类是多继承类）实测 **8**，
     只看直接基个数会预测 4 ⇒ 假 C2118 ⇒ 管线停摆（`shape.cpp:28/29` 逐字）。
2. **`offsetof` 虚基区域不可用（E-3）**：虚基成员（`p3.cpp:28` ⇒ C2057）、以及虚基的
   非虚基之成员（`off.cpp:18` ⇒ C2057）**都不是常量表达式** ⇒ 必须跳过；
   而"有虚基的类里，本类成员 / 非虚基成员"的 offsetof **是常量**（`off.cpp` o3/o4/o6
   只有 C2118 值不符，无 C2057）⇒ 只跳过**虚基区域**。
3. **`offsetof` 需要 `#include <stddef.h>`**：`p2.cpp` 缺它 ⇒ C2065 'offsetof' undeclared。

## 常量可信度（E-1 / E-2：不要把生成器变成"判死正确注解"的凶器）

| trust | 判据 | 默认动作 |
|---|---|---|
| `trusted` | 形态 A **且** 独立于 annotation **且** 未被疑误归属 | 生成生效断言 |
| `same-source` | 形态 A 但**与 annotation 同源** ⇒ 零判别力（E-2：错误注解照样编译通过） | 注释留痕（`[SAME-SOURCE]`） |
| `suspect` | 形态非 A，或已疑误归属（E-1：被污染的 A 级常量判死正确注解 ⇒ C2118） | 注释留痕（`[SUSPECT]`） |

`--untrusted-policy` 可切 `comment`（默认，留痕不生效）/ `skip`（完全不写）/ `assert`（生效，风险自担）。
**A 级是证据形态等级，不是独立性等级** —— 这条写进头文件的错误处理表（branch 2）。

## 用法

```sh
# 真实数据（输出 _layout_asserts.h）
python3 tools/layout_assert_gen.py \
    --structs data/annotations/structs --tree data/status/_inheritance_tree.json \
    --out _layout_asserts.h

# 独立 A 级证据（IDA 二进制直接读取）灌入后，size/offset 断言才会生效
python3 tools/layout_assert_gen.py --evidence evidence.json --out _layout_asserts.h

# 只生成某几个类；确定性重放校验
python3 tools/layout_assert_gen.py --only CEffSParticle,CCBUI --out /tmp/x.h
python3 tools/layout_assert_gen.py --out _layout_asserts.h --check   # 与磁盘逐字比对
```

**include 契约**：`_layout_asserts.h` 必须在**全部类声明之后**包含（`sizeof`/`offsetof`
需要完整类型，前向声明不够 ⇒ C2027）。

## 只读契约

本工具**只读** `data/annotations/**`，从不写回（`main()` 硬拒 `--out` 落在该目录下）；
真值源只允许经 IDA/证据文件进入。
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Iterable, List, Mapping, Optional, Sequence, Tuple

# ============================== 词表 ==============================

PMF_SIZE_SINGLE = 4         # 单继承链
PMF_SIZE_MULTIPLE = 8       # 闭包内有多继承分支（无虚基）
PMF_SIZE_VIRTUAL = 12       # 闭包内有虚基（多虚基仍是 12）

GRADE_A = 'A'               # 证据形态：reg+disp32 / 绝对地址
GRADE_B = 'B'               # 证据形态：PDB 等参考
GRADE_C = 'C'               # 证据形态：decomp / 猜测 / 无

TRUST_TRUSTED = 'trusted'
TRUST_SAME_SOURCE = 'same-source'
TRUST_SUSPECT = 'suspect'

KIND_SHAPE = 'shape'
KIND_SIZE = 'size'
KIND_OFFSET = 'offset'

STATUS_ACTIVE = 'active'
STATUS_COMMENTED = 'commented'
STATUS_OMITTED = 'omitted'

POLICY_COMMENT = 'comment'
POLICY_SKIP = 'skip'
POLICY_ASSERT = 'assert'
ALL_POLICIES = (POLICY_COMMENT, POLICY_SKIP, POLICY_ASSERT)

MARK_SUSPECT = '[SUSPECT]'
MARK_SAME_SOURCE = '[SAME-SOURCE]'

#: 形状断言的常量出处：MSVC6 探针（独立于 annotation，A 形态）
SHAPE_EVIDENCE_DETAIL = ('MSVC6 SP0 实测矩阵 E-4：虚基⇒12 / 多继承分支⇒8 / 单继承⇒4'
                         '（data/status/_layout_assert_probe_20260925）')

#: A 形态判据（证据原文逐字）：reg+disp32
_RE_REG_DISP = re.compile(r'\[\s*(?:e[a-z]{2}|reg|this|[A-Za-z_][A-Za-z0-9_]*)\s*[+-]\s*(?:0[xX])?[0-9A-Fa-f]+[hH]?\s*\]')
#: A 形态判据：绝对地址（0x00xxxxxx 段）
_RE_ABS_ADDR = re.compile(r'\b0[xX]0{2}[0-9A-Fa-f]{6}\b')
#: 多继承被建模成"内嵌基类成员"的痕迹（声明形状 ≠ 注解形状 ⇒ 形状断言必须降级）
_RE_EMBED_MARK = re.compile(r'multi_inheritance_as_embed', re.I)
_RE_BASECLASS_NAME = re.compile(r'baseclass\d*$')
_IDENT_RE = re.compile(r'^[A-Za-z_][A-Za-z0-9_]*$')

DEFAULT_STRUCTS_DIR = ('data', 'annotations', 'structs')
DEFAULT_TREE = ('data', 'status', '_inheritance_tree.json')


# ============================== 数据模型 ==============================

@dataclass(frozen=True)
class Evidence:
    """一条断言常量的证据记录。

    `grade` 是**形态**等级（A = reg+disp32/绝对地址），`independent` 才是**独立性**等级
    （E-2：A 级形态 + 同源 annotation ⇒ 零判别力）。`misattributed` 标记已疑误归属（E-1）。
    """
    grade: str = GRADE_C
    origin: str = 'annotation'
    detail: str = ''
    independent: bool = False
    misattributed: bool = False

    def trust(self) -> str:
        return evidence_trust(self)


EVIDENCE_DEFAULT = Evidence()
EVIDENCE_SHAPE_PROBE = Evidence(grade=GRADE_A, origin='probe',
                                detail=SHAPE_EVIDENCE_DETAIL, independent=True)


@dataclass(frozen=True)
class BaseSpec:
    name: str
    offset: Optional[int] = None          # 注解记录的基类子对象偏移（虚基者运行期才定）
    is_virtual: bool = False


@dataclass(frozen=True)
class MemberSpec:
    name: str
    offset: int
    owner: Optional[str] = None           # 声明该成员的类（None = 本类）
    in_virtual_base: bool = False
    type: str = ''
    source: str = ''
    evidence: Evidence = EVIDENCE_DEFAULT


@dataclass(frozen=True)
class ClassLayout:
    name: str
    bases: Tuple[BaseSpec, ...] = ()
    members: Tuple[MemberSpec, ...] = ()
    binary_size: Optional[int] = None
    size_evidence: Evidence = EVIDENCE_DEFAULT
    bases_known: bool = True              # False = 注解/继承树都没有该类的基类信息
    polymorphic: bool = False             # 有 methods/vtables（漏注基类的风险最高，必须有断言）
    source_file: str = ''


@dataclass(frozen=True)
class ShapeInfo:
    pmf_size: int
    has_virtual_base: bool
    branching: bool
    closure: frozenset = frozenset()
    unresolved: frozenset = frozenset()
    reason: str = ''
    proven: bool = True


@dataclass(frozen=True)
class Assertion:
    kind: str
    cls: str
    name: str
    condition: str
    expected: int
    evidence: Evidence
    trust: str
    status: str
    reason: str = ''
    member: Optional[str] = None


@dataclass(frozen=True)
class GenOptions:
    untrusted_policy: str = POLICY_COMMENT
    emit_shape: bool = True
    emit_size: bool = True
    emit_offset: bool = True
    include_stddef: bool = True
    header_guard: str = 'PAL3_LAYOUT_ASSERTS_H'
    generated_note: str = ''
    #: 形状断言是否要求"闭包闭世界"（闭包内每个类都有基类信息）。默认 False =
    #: 与 codegen 同源的"声明一致性"口径；True = 最保守（真实数据下 active 从 ~170 降到 ~1）。
    require_closed_world_shape: bool = False
    #: 只**渲染**这些类（闭包查表仍用全部布局 —— 否则形状会被误判为"闭包不完整"）
    only: Optional[frozenset] = None


@dataclass
class HeaderResult:
    text: str = ''
    assertions: Tuple[Assertion, ...] = ()
    census: Dict[str, object] = field(default_factory=dict)
    warnings: Tuple[str, ...] = ()
    offset_skipped: Tuple[str, ...] = ()


# ============================== 证据可信度 ==============================

def evidence_trust(ev: Evidence) -> str:
    """`trusted` / `same-source` / `suspect` 三态（见模块 docstring 的表）。"""
    if ev.misattributed:
        return TRUST_SUSPECT
    if ev.grade != GRADE_A:
        return TRUST_SUSPECT
    if not ev.independent:
        return TRUST_SAME_SOURCE
    return TRUST_TRUSTED


def evidence_from_source(text: Optional[str], origin: str = 'annotation') -> Evidence:
    """从注解 `source` 文本推断证据**形态**等级。

    A：`[reg+0Ch]` 形（reg+disp32）或 `0x00xxxxxx` 绝对地址；
    B：PDB 参考；C：decomp / 猜测 / 空。

    `independent` 只对非 annotation 血缘的 origin 为真 —— 从
    `data/annotations/structs/*.json` 读到的任何文本，**即使是 A 形态也不是独立证据**
    （E-2）。
    """
    s = text or ''
    independent = origin in ('ida_binary', 'binary_ida', 'probe')
    if _RE_REG_DISP.search(s) or _RE_ABS_ADDR.search(s):
        return Evidence(grade=GRADE_A, origin=origin, detail=s[:200], independent=independent)
    if 'pdb' in s.lower():
        return Evidence(grade=GRADE_B, origin=origin, detail=s[:200], independent=independent)
    if s.strip():
        return Evidence(grade=GRADE_C, origin=origin, detail=s[:200], independent=independent)
    return Evidence(grade=GRADE_C, origin=origin, detail='', independent=independent)


def _trust_reason(ev: Evidence) -> str:
    trust = evidence_trust(ev)
    if trust == TRUST_TRUSTED:
        return ''
    if ev.misattributed:
        return '常量可疑: 证据归属存疑（E-1：w1/w2.cpp 实测被污染的 A 级常量判死正确注解 ⇒ C2118）'
    if ev.grade != GRADE_A:
        return '常量可疑: 证据形态等级 %s（非 reg+disp32/绝对地址）' % ev.grade
    return '同源常量: 证据与 annotation 同源 ⇒ 零判别力（E-2：错误注解也会编译通过）'


# ============================== 继承形状 ==============================

def _direct_bases(layout: ClassLayout) -> Tuple[BaseSpec, ...]:
    return tuple(layout.bases)


def transitive_bases(name: str, layouts: Mapping[str, ClassLayout],
                     _seen: Optional[set] = None) -> frozenset:
    """`name` 的传递基类闭包（不含自身；未知基类只记名字，不再展开）。"""
    seen = set() if _seen is None else _seen
    layout = layouts.get(name)
    if layout is None:
        return frozenset(seen)
    for b in _direct_bases(layout):
        if b.name in seen:
            continue
        seen.add(b.name)
        transitive_bases(b.name, layouts, seen)
    return frozenset(seen)


def _closure_of_bases(bases: Sequence[BaseSpec],
                      layouts: Mapping[str, ClassLayout]) -> frozenset:
    """直接基列表 → 传递闭包（**不含自身**）。`pmf_size_for` 用（探针类不在 layouts 里）。"""
    seen: set = set()
    stack = [b.name for b in bases]
    while stack:
        n = stack.pop()
        if n in seen:
            continue
        seen.add(n)
        bl = layouts.get(n)
        if bl is not None:
            stack.extend(b.name for b in _direct_bases(bl))
    return frozenset(seen)


def shape_info(layout: ClassLayout, layouts: Mapping[str, ClassLayout]) -> ShapeInfo:
    """按实际继承形状算 PMF 尺寸（E-4 封闭规则，走传递闭包）。"""
    closure = _closure_of_bases(layout.bases, layouts)
    unresolved = {b for b in closure if b not in layouts}

    has_virtual = any(b.is_virtual for b in _direct_bases(layout))
    branching = len(_direct_bases(layout)) > 1
    for b in closure:
        bl = layouts.get(b)
        if bl is None:
            continue
        if any(x.is_virtual for x in _direct_bases(bl)):
            has_virtual = True
        if len(_direct_bases(bl)) > 1:
            branching = True

    if has_virtual:
        pmf = PMF_SIZE_VIRTUAL
    elif branching:
        pmf = PMF_SIZE_MULTIPLE
    else:
        pmf = PMF_SIZE_SINGLE

    if not layout.bases_known:
        proven = False
        reason = '该类的基类信息缺失（注解与继承树均无）⇒ 形状不可证'
    elif unresolved:
        proven = False
        reason = '继承闭包不完整：未知基类 %s ⇒ 形状不可证' % ','.join(sorted(unresolved))
    else:
        proven = True
        vbs = {b.name for b in _direct_bases(layout) if b.is_virtual}
        vbs |= {b for b in closure
                if b in layouts and any(x.is_virtual for x in _direct_bases(layouts[b]))}
        if has_virtual:
            reason = ('继承闭包内有虚基（%s）⇒ 12；E-4 实测虚基优先于多继承，多虚基仍是 12'
                      % ','.join(sorted(vbs)))
        elif branching:
            reason = '继承闭包内有多继承分支 ⇒ 8（★ 单直接基但基类是多继承类时也是 8）'
        else:
            reason = '单继承链 ⇒ 4'
    return ShapeInfo(pmf_size=pmf, has_virtual_base=has_virtual, branching=branching,
                     closure=closure, unresolved=frozenset(unresolved), reason=reason,
                     proven=proven)


def pmf_size_for(bases: Sequence[BaseSpec], layouts: Mapping[str, ClassLayout]) -> int:
    """给定直接基列表，返回 MSVC6 的 `sizeof(void (Cls::*)())`。"""
    probe = ClassLayout(name='<probe>', bases=tuple(bases))
    return shape_info(probe, layouts).pmf_size


def virtual_base_region(layout: ClassLayout, layouts: Mapping[str, ClassLayout]) -> frozenset:
    """必须跳过 offsetof 的类集合 = 各虚基 + 它们的传递闭包（E-3）。

    这些类里的成员 offset 需运行期查 vbtable ⇒ 不是常量表达式（C2057）。
    """
    region: set = set()
    for b in _direct_bases(layout):
        if b.is_virtual:
            region.add(b.name)
            region |= transitive_bases(b.name, layouts)
    return frozenset(region)


def _shape_proven_under_options(layout: ClassLayout, layouts: Mapping[str, ClassLayout],
                                info: ShapeInfo, options: GenOptions) -> Tuple[bool, str]:
    if not info.proven:
        return False, info.reason
    embedding = _embed_model_marker(layout)
    if embedding:
        return False, ('该类把多继承建模成内嵌基类成员（%s）⇒ 声明的继承形状 ≠ 注解形状 ⇒ '
                       'PMF 断言不可证' % embedding)
    if options.require_closed_world_shape:
        for b in info.closure:
            bl = layouts.get(b)
            if bl is not None and not bl.bases_known:
                return False, ('严格口径：闭包内 %s 的基类信息缺失 ⇒ 闭包不闭世界 ⇒ 形状不可证' % b)
    return True, info.reason


def _embed_model_marker(layout: ClassLayout) -> str:
    for m in layout.members:
        if _RE_EMBED_MARK.search(m.source or '') or _RE_BASECLASS_NAME.search(m.name or ''):
            return '%s (offset=%d)' % (m.name or '<unnamed>', m.offset)
    return ''


# ============================== offsetof 可用性 ==============================

def member_offset_assertable(layout: ClassLayout, member: MemberSpec,
                            layouts: Mapping[str, ClassLayout]) -> Tuple[bool, str]:
    """该成员的 `offsetof` 能不能作**常量表达式**（E-3 三条判据）。"""
    name = member.name or ''
    if not _IDENT_RE.match(name):
        return False, '成员名不是合法标识符（%r）⇒ 无法生成 offsetof 断言' % name
    if member.in_virtual_base:
        return False, ('成员声明在虚基内 ⇒ offsetof 不是常量表达式（C2057，E-3 p3.cpp:28 实测）⇒ 跳过')
    region = virtual_base_region(layout, layouts)
    if member.owner and member.owner in region:
        return False, ('成员来自虚基 %s ⇒ offsetof 不是常量表达式（C2057，E-3 实测）⇒ 跳过'
                       % member.owner)
    if member.owner is None:
        for b in _direct_bases(layout):
            if not b.is_virtual or b.offset is None:
                continue
            bl = layouts.get(b.name)
            if bl is None or bl.binary_size is None:
                continue
            if b.offset <= member.offset < b.offset + bl.binary_size:
                return False, ('成员 offset=%d 落在虚基 %s 的记录区间 [%d,%d) 内 ⇒ 保守跳过'
                               '（C2057 风险，虚基成员 offsetof 不可用）'
                               % (member.offset, b.name, b.offset, b.offset + bl.binary_size))
    return True, '本类/非虚基成员 ⇒ offsetof 为常量表达式'


# ============================== 断言类型名 ==============================

def sanitize_ident(s: str) -> str:
    out = re.sub(r'[^0-9A-Za-z_]', '_', s or '')
    if not out:
        return '_'
    if out[0].isdigit():
        out = '_' + out
    return out


class NameRegistry:
    """断言 typedef 名的全局唯一登记簿（同名 ⇒ MSVC6 C2086 重定义）。

    MSVC6 标识符上限 247 字符，超长部分按确定性规则截断后再去重。
    """

    MAX_LEN = 200

    def __init__(self) -> None:
        self.used: set = set()

    def reserve(self, base: str) -> str:
        cand = base
        if len(cand) > self.MAX_LEN:
            cand = cand[:self.MAX_LEN]
        if cand not in self.used:
            self.used.add(cand)
            return cand
        n = 2
        while True:
            alt = '%s__%d' % (cand, n)
            if alt not in self.used:
                self.used.add(alt)
                return alt
            n += 1


# ============================== 断言构建 ==============================

def _normalize_layouts(layouts) -> Tuple[Dict[str, ClassLayout], List[str]]:
    warnings: List[str] = []
    out: Dict[str, ClassLayout] = {}
    if isinstance(layouts, Mapping):
        items: Iterable[ClassLayout] = layouts.values()
    else:
        items = layouts
    for lay in items:
        if lay.name in out:
            warnings.append('重复输入的类 %s ⇒ 去重（保留首个）' % lay.name)
            continue
        out[lay.name] = lay
    return out, warnings


def build_assertions(layouts, options: GenOptions = GenOptions()) -> List[Assertion]:
    return _plan(layouts, options)[0]


def _status_for(trust: str, policy: str) -> str:
    if trust == TRUST_TRUSTED:
        return STATUS_ACTIVE
    if policy == POLICY_ASSERT:
        return STATUS_ACTIVE
    if policy == POLICY_SKIP:
        return STATUS_OMITTED
    return STATUS_COMMENTED


def _plan(layouts, options: GenOptions
          ) -> Tuple[List[Assertion], List[str], List[str], List[str]]:
    """→ (assertions, skipped 描述, warnings, offset_skipped 键)"""
    norm, warnings = _normalize_layouts(layouts)
    registry = NameRegistry()
    assertions: List[Assertion] = []
    skipped: List[str] = []
    offset_skipped: List[str] = []

    for cls_name in sorted(norm):
        if options.only is not None and cls_name not in options.only:
            continue
        layout = norm[cls_name]
        san = sanitize_ident(cls_name)

        # --- 继承形状（PMF 尺寸）---
        # 无基类信息且非多态的 POD 结构体（RECT/tag* 之类）不生成形状断言：
        # PMF 断言对它们无意义；多态类则必须可见（漏注基类的风险最高）。
        if options.emit_shape and (layout.bases_known or layout.polymorphic):
            info = shape_info(layout, norm)
            proven, reason = _shape_proven_under_options(layout, norm, info, options)
            ev = EVIDENCE_SHAPE_PROBE if proven else Evidence(
                grade=GRADE_C, origin='shape_model', detail=reason, independent=False)
            trust = evidence_trust(ev)
            assertions.append(Assertion(
                kind=KIND_SHAPE, cls=cls_name,
                name=registry.reserve('_a_%s_pmf' % san),
                condition='sizeof(void (%s::*)()) == %d' % (cls_name, info.pmf_size),
                expected=info.pmf_size, evidence=ev, trust=trust,
                status=_status_for(trust, options.untrusted_policy),
                reason=reason if trust != TRUST_TRUSTED else '',
            ))

        # --- sizeof ---
        if options.emit_size and layout.binary_size is not None:
            ev = layout.size_evidence
            trust = evidence_trust(ev)
            assertions.append(Assertion(
                kind=KIND_SIZE, cls=cls_name,
                name=registry.reserve('_a_%s_size' % san),
                condition='sizeof(%s) == %d' % (cls_name, layout.binary_size),
                expected=int(layout.binary_size), evidence=ev, trust=trust,
                status=_status_for(trust, options.untrusted_policy),
                reason=_trust_reason(ev),
            ))

        # --- 成员偏移 ---
        if options.emit_offset:
            for m in sorted(layout.members, key=lambda x: (x.offset, x.name or '')):
                ok, why = member_offset_assertable(layout, m, norm)
                if not ok:
                    skipped.append('%s::%s@%d: %s' % (cls_name, m.name or '<unnamed>',
                                                      m.offset, why))
                    offset_skipped.append('%s::%s' % (cls_name, m.name or '<unnamed>'))
                    continue
                ev = m.evidence
                trust = evidence_trust(ev)
                assertions.append(Assertion(
                    kind=KIND_OFFSET, cls=cls_name, member=m.name,
                    name=registry.reserve('_a_%s_%s' % (san, sanitize_ident(m.name))),
                    condition='offsetof(%s, %s) == %d' % (cls_name, m.name, m.offset),
                    expected=int(m.offset), evidence=ev, trust=trust,
                    status=_status_for(trust, options.untrusted_policy),
                    reason=_trust_reason(ev),
                ))
    return assertions, skipped, warnings, offset_skipped


def _census(assertions: Sequence[Assertion], skipped: Sequence[str]) -> Dict[str, object]:
    by_kind: Dict[str, int] = {}
    by_trust: Dict[str, int] = {}
    skip_reasons: Dict[str, int] = {}
    for a in assertions:
        by_kind[a.kind] = by_kind.get(a.kind, 0) + 1
        by_trust[a.trust] = by_trust.get(a.trust, 0) + 1
    for s in skipped:
        reason = s.split(': ', 1)[1] if ': ' in s else s
        skip_reasons[reason] = skip_reasons.get(reason, 0) + 1
    c: Dict[str, object] = {
        'total': len(assertions),
        'active': sum(1 for a in assertions if a.status == STATUS_ACTIVE),
        'commented': sum(1 for a in assertions if a.status == STATUS_COMMENTED),
        'omitted': sum(1 for a in assertions if a.status == STATUS_OMITTED),
        'skipped': len(skipped),
        TRUST_TRUSTED: by_trust.get(TRUST_TRUSTED, 0),
        TRUST_SAME_SOURCE: by_trust.get(TRUST_SAME_SOURCE, 0),
        TRUST_SUSPECT: by_trust.get(TRUST_SUSPECT, 0),
        'by_kind': by_kind,
        'by_trust': by_trust,
        'skip_reasons': skip_reasons,
    }
    return c


# ============================== 渲染 ==============================

_ERROR_TABLE = """\
/* ============================ 错误处理表 ============================
 * 编译失败时按以下分支归因，**不要**跳过分支直接改注解：
 *
 *  branch 1  断言失败 ∧ 常量可信（A 形态 ∧ 独立于 annotation ∧ 无疑似误归属）
 *            ⇒ 真布局错误：修 annotation / 类型 / 成员偏移（本仓四道门流程）。
 *  branch 2  断言失败 ∧ **常量本身可疑**（行首 [SUSPECT]：形态非 A，或已疑误归属 E-1）
 *            ⇒ 常量（或其归属）错，**不得**改动正确注解 —— w1/w2.cpp 实测：被污染的
 *              A 级常量会把正确注解判死（C2118），工程师唯一"合规"出路是把注解改坏 ⇒
 *              全下游成员位移连环错。正确动作：重取**独立**的 IDA 二进制证据
 *              （reg+disp32 / 绝对地址），再解除注释。
 *              同理，[SAME-SOURCE] 行（A 形态但同源，E-2）编译通过**不代表**布局正确：
 *              它与注解出自同一次读数，零判别力。
 *  branch 3  C2057 'expected constant expression' / C2466（offsetof 于虚基区域）
 *            ⇒ 生成器本应跳过该类成员（E-3：p3.cpp:28 与 off.cpp:18 实测虚基成员、
 *              虚基的非虚基之成员都不是常量表达式）⇒ 报生成器缺陷，不要手删断言了事。
 *
 * 另：本文件必须在**全部类声明之后**包含（sizeof/offsetof 需要完整类型）；
 *     若报 C2027 'use of undefined type' ⇒ include 位置不对，不是布局错误。
 * MSVC6 无编译期静态断言关键字 ⇒ 全部断言用负数组技巧（false ⇒ 负下标 ⇒ C2118）。
 * ==================================================================== */
"""


def _render_assertion(a: Assertion) -> str:
    body = 'typedef char %s[(%s) ? 1 : -1];' % (a.name, a.condition)
    tail_bits = [a.kind, a.trust]
    detail = (a.evidence.detail or '').replace('*/', '* /').replace('\n', ' ')
    if a.reason:
        tail_bits.append(a.reason)
    elif detail:
        tail_bits.append(detail)
    tail = ' /* %s */' % ' | '.join(tail_bits)
    if a.status == STATUS_ACTIVE:
        return body + tail
    mark = MARK_SUSPECT if a.trust == TRUST_SUSPECT else MARK_SAME_SOURCE
    return '// %s %s%s' % (mark, body, tail)


def _class_header(layout: ClassLayout, layouts: Mapping[str, ClassLayout]) -> str:
    info = shape_info(layout, layouts)
    bases = ', '.join(
        ('virtual ' if b.is_virtual else '') + b.name for b in layout.bases) or '-'
    return ('/* ===== %s ===== bases: %s | pmf(%s) = %d | %s */'
            % (layout.name, bases, layout.name, info.pmf_size, info.reason))


def render_header(res: HeaderResult, options: GenOptions,
                  layouts: Optional[Mapping[str, ClassLayout]] = None) -> str:
    c = res.census
    guard = options.header_guard
    lines: List[str] = []
    lines.append('/* _layout_asserts.h —— 数据布局的编译期校验（由 tools/layout_assert_gen.py 生成，请勿手改）')
    lines.append(' * 生成口径: untrusted-policy=%s%s%s%s'
                 % (options.untrusted_policy,
                    '' if options.emit_shape else ' -shape',
                    '' if options.emit_size else ' -size',
                    '' if options.emit_offset else ' -offset'))
    lines.append(' * 统计: total=%s active=%s commented=%s omitted=%s skipped=%s'
                 % (c.get('total'), c.get('active'), c.get('commented'),
                    c.get('omitted'), c.get('skipped')))
    lines.append(' *   trusted=%s same-source=%s suspect=%s'
                 % (c.get(TRUST_TRUSTED), c.get(TRUST_SAME_SOURCE), c.get(TRUST_SUSPECT)))
    if options.generated_note:
        lines.append(' * 注记: %s' % options.generated_note.replace('\n', ' '))
    lines.append(' */')
    lines.append(_ERROR_TABLE)
    lines.append('#ifndef %s' % guard)
    lines.append('#define %s' % guard)
    lines.append('')
    if options.include_stddef:
        lines.append('#include <stddef.h>   /* offsetof */')
        lines.append('')

    by_cls: Dict[str, List[Assertion]] = {}
    for a in res.assertions:
        if a.status == STATUS_OMITTED:
            continue                                   # policy=skip：不落盘（仅记账）
        by_cls.setdefault(a.cls, []).append(a)
    for cls_name in sorted(by_cls):
        layout = (layouts or {}).get(cls_name)
        if layout is not None:
            note = _class_header(layout, layouts or {})
            lines.append(note)
        else:
            lines.append('/* ===== %s ===== */' % cls_name)
        for a in sorted(by_cls[cls_name], key=lambda x: (x.kind, x.expected, x.name)):
            lines.append(_render_assertion(a))
        lines.append('')
    lines.append('#endif /* %s */' % guard)
    return '\n'.join(lines) + '\n'


# ============================== 顶层 ==============================

def generate(layouts, options: GenOptions = GenOptions()) -> HeaderResult:
    """布局（Mapping 或 ClassLayout 序列）⇒ 头文件文本 + 台账。"""
    assertions, skipped, warnings, offset_skipped = _plan(layouts, options)
    norm, _ = _normalize_layouts(layouts)
    census = _census(assertions, skipped)
    res = HeaderResult(assertions=tuple(assertions), census=census,
                       warnings=tuple(warnings), offset_skipped=tuple(offset_skipped))
    res.text = render_header(res, options, norm)
    if skipped:
        res.text = res.text.replace(
            '#endif /* %s */' % options.header_guard,
            '/* 已跳过（不是常量表达式/无法命名）%d 条，例如: %s\n */\n#endif /* %s */'
            % (len(skipped), ' ; '.join(skipped[:5]), options.header_guard))
    return res


# ============================== 数据源装载 ==============================

def _offset_key_to_int(key) -> int:
    """annotation 的 known_members 键：`'12'` / `'0x44'` / `'1684_0'`（overlay）三种形。"""
    s = str(key).strip()
    if s[:2].lower() == '0x':
        return int(s, 16)
    m = re.match(r'^(-?\d+)(?:_\d+)*$', s)
    if m:
        return int(m.group(1))
    m2 = re.match(r'^(-?\d+)', s)
    if m2:
        return int(m2.group(1))
    raise ValueError('无法解析成员偏移键: %r' % key)


def _as_name_list(value) -> List[str]:
    if value is None:
        return []
    if isinstance(value, str):
        return [value] if value else []
    out = []
    for v in value:
        if isinstance(v, str) and v:
            out.append(v)
        elif isinstance(v, dict) and v.get('name'):
            out.append(v['name'])
    return out


def _evidence_from_record(rec) -> Evidence:
    if rec is None:
        return EVIDENCE_DEFAULT
    if isinstance(rec, Evidence):
        return rec
    if isinstance(rec, str):
        return evidence_from_source(rec)
    return Evidence(grade=rec.get('grade', GRADE_C),
                    origin=rec.get('origin', 'evidence_file'),
                    detail=rec.get('detail', ''),
                    independent=bool(rec.get('independent', False)),
                    misattributed=bool(rec.get('misattributed', False)))


def load_virtual_bases(path) -> Dict[str, List[str]]:
    """`{"Cls": ["Base", ...]}` ⇒ 把给定类的这些基标记为**虚基**（E-4 形状判据的输入）。"""
    data = json.loads(Path(path).read_text(encoding='utf-8'))
    out: Dict[str, List[str]] = {}
    for cls, bases in (data or {}).items():
        out[cls] = _as_name_list(bases)
    return out


def load_evidence(path) -> Dict[str, Dict[str, object]]:
    """独立证据文件：`{"Cls": {"size": {...}, "members": {...}, "shape": {...}}}`。"""
    data = json.loads(Path(path).read_text(encoding='utf-8'))
    return {k: (v or {}) for k, v in (data or {}).items()}


def load_struct_layouts(structs_dir, tree_path=None, virtual_bases=None,
                        evidence=None) -> Dict[str, ClassLayout]:
    """annotation structs（+ 继承树 + 虚基覆盖 + 证据文件）⇒ `{类名: ClassLayout}`。

    只读；文件名重复的类以**文件名排序后的首个**为准（并留 warning）。
    """
    structs_dir = Path(structs_dir)
    objs: Dict[str, dict] = {}
    warnings: List[str] = []
    for path in sorted(structs_dir.glob('*.json')):
        try:
            obj = json.loads(path.read_text(encoding='utf-8'))
        except Exception as exc:                       # pragma: no cover - 坏 JSON
            warnings.append('跳过坏 JSON %s: %s' % (path.name, exc))
            continue
        name = obj.get('name') or path.stem
        if name in objs:
            warnings.append('类名重复 %s（%s 被忽略）' % (name, path.name))
            continue
        objs[name] = obj

    tree: Dict[str, object] = {}
    if tree_path is not None and Path(tree_path).exists():
        tree = json.loads(Path(tree_path).read_text(encoding='utf-8')) or {}

    virtual_bases = virtual_bases or {}
    evidence = evidence or {}
    layouts: Dict[str, ClassLayout] = {}
    for name, obj in objs.items():
        base_names = _as_name_list(obj.get('base_class'))
        if not base_names and name in tree:
            base_names = _as_name_list(tree[name])
        bases_known = bool(base_names) or (name in tree) or ('base_class' in obj)

        offsets: Dict[str, int] = {}
        vb_from_obj: set = set()
        for b in (obj.get('bases') or []):
            if not isinstance(b, dict):
                continue
            bn = b.get('name')
            if not bn:
                continue
            if b.get('offset') is not None:
                try:
                    offsets[bn] = int(b['offset'])
                except (TypeError, ValueError):
                    pass
            if b.get('is_virtual') or b.get('virtual'):
                vb_from_obj.add(bn)
        vb = set(virtual_bases.get(name, [])) | vb_from_obj
        bases = tuple(BaseSpec(name=bn, offset=offsets.get(bn), is_virtual=bn in vb)
                      for bn in base_names)

        ev_rec = evidence.get(name, {}) or {}
        size_evidence = _evidence_from_record(ev_rec.get('size'))
        if ev_rec.get('size') is None:
            for fld in ('binary_size_source', 'size_evidence', '_size_evidence', 'size_note'):
                if obj.get(fld):
                    size_evidence = evidence_from_source(str(obj[fld]))
                    break

        members: List[MemberSpec] = []
        for key, m in sorted((obj.get('known_members') or {}).items()):
            if not isinstance(m, dict):
                continue
            try:
                off = _offset_key_to_int(key)
            except ValueError as exc:
                warnings.append('%s: %s' % (name, exc))
                continue
            mname = m.get('name') or ''
            src = str(m.get('source') or m.get('note') or '')
            ov = ((ev_rec.get('members') or {}).get(mname))
            ev = _evidence_from_record(ov) if ov is not None else evidence_from_source(src)
            members.append(MemberSpec(
                name=mname, offset=off, owner=m.get('owner'), type=str(m.get('type') or ''),
                in_virtual_base=bool(m.get('in_virtual_base')), source=src, evidence=ev))

        size = obj.get('binary_size')
        members.sort(key=lambda m: (m.offset, m.name))
        layouts[name] = ClassLayout(
            name=name, bases=bases, members=tuple(members),
            binary_size=int(size) if size is not None else None,
            size_evidence=size_evidence, bases_known=bases_known,
            polymorphic=bool(obj.get('methods') or obj.get('vtables')),
            source_file=str(structs_dir))
    load_struct_layouts.warnings = warnings        # 供 CLI/报告读取（不改变返回值契约）
    return layouts


load_struct_layouts.warnings = []                   # type: ignore[attr-defined]


# ============================== CLI ==============================

def _build_argparser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(
        description='布局断言生成器：annotation 布局 ⇒ _layout_asserts.h（MSVC6 负数组技巧）')
    p.add_argument('--structs', default=str(Path(*DEFAULT_STRUCTS_DIR)))
    p.add_argument('--tree', default=str(Path(*DEFAULT_TREE)))
    p.add_argument('--virtual-bases', default=None,
                   help='虚基覆盖 JSON：{"Cls": ["Base", ...]}')
    p.add_argument('--evidence', default=None,
                   help='独立证据 JSON：{"Cls": {"size": {...}, "members": {...}}}')
    p.add_argument('--out', default='_layout_asserts.h')
    p.add_argument('--untrusted-policy', choices=ALL_POLICIES, default=POLICY_COMMENT)
    p.add_argument('--only', default=None, help='逗号分隔的类名白名单')
    p.add_argument('--no-shape', action='store_true')
    p.add_argument('--no-size', action='store_true')
    p.add_argument('--no-offset', action='store_true')
    p.add_argument('--no-stddef', action='store_true')
    p.add_argument('--require-closed-world-shape', action='store_true')
    p.add_argument('--census-json', default=None)
    p.add_argument('--check', action='store_true', help='只与 --out 现有内容比对，不写盘')
    p.add_argument('--quiet', action='store_true')
    return p


def main(argv=None) -> int:
    args = _build_argparser().parse_args(argv)
    out_path = Path(args.out).resolve()
    ann_root = (Path(__file__).resolve().parents[1] / 'data' / 'annotations').resolve()
    if ann_root == out_path or ann_root in out_path.parents:
        print('拒绝写入 annotation 真相源目录: %s' % out_path, file=sys.stderr)
        return 2

    vb = load_virtual_bases(args.virtual_bases) if args.virtual_bases else None
    ev = load_evidence(args.evidence) if args.evidence else None
    layouts = load_struct_layouts(args.structs, tree_path=args.tree,
                                  virtual_bases=vb, evidence=ev)
    if args.only:
        keep = frozenset(s.strip() for s in args.only.split(',') if s.strip())
        missing = sorted(keep - set(layouts))
        if missing:
            print('未知类名: %s' % ','.join(missing), file=sys.stderr)
            return 2
    else:
        keep = None

    options = GenOptions(
        untrusted_policy=args.untrusted_policy,
        emit_shape=not args.no_shape, emit_size=not args.no_size,
        emit_offset=not args.no_offset, include_stddef=not args.no_stddef,
        require_closed_world_shape=args.require_closed_world_shape,
        generated_note='--structs %s%s' % (args.structs,
                                           '' if not keep else ' --only %s' % ','.join(sorted(keep))),
        only=keep,
    )
    res = generate(layouts, options)

    for w in list(load_struct_layouts.warnings) + list(res.warnings):
        print('WARN %s' % w, file=sys.stderr)

    if args.census_json:
        Path(args.census_json).write_text(
            json.dumps({'census': res.census, 'warnings': list(res.warnings),
                        'skipped': list(res.offset_skipped)}, ensure_ascii=False, indent=1),
            encoding='utf-8')

    if args.check:
        existing = out_path.read_text(encoding='utf-8') if out_path.exists() else ''
        if existing != res.text:
            print('CHECK FAILED: %s 与生成结果不一致' % out_path, file=sys.stderr)
            return 1
        print('CHECK OK: %s' % out_path)
        return 0

    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(res.text, encoding='utf-8')
    if not args.quiet:
        c = res.census
        print('wrote %s | total=%s active=%s commented=%s omitted=%s skipped=%s '
              '(trusted=%s same-source=%s suspect=%s)'
              % (out_path, c['total'], c['active'], c['commented'], c['omitted'],
                 c['skipped'], c[TRUST_TRUSTED], c[TRUST_SAME_SOURCE], c[TRUST_SUSPECT]))
    return 0


if __name__ == '__main__':
    sys.exit(main())