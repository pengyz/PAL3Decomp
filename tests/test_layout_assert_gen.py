"""`tools/layout_assert_gen.py` 的测试 —— **先写测试**（TDD，红→绿）。

被测对象：布局断言生成器（Task 4）。产出 `_layout_asserts.h`，用 MSVC6
负数组技巧做**编译期**布局校验。

所有"编译器规则"期望值均为真机 MSVC 6.0 SP0（cl 12.00.8168，`tools/wine_cl.sh`）实测，
探针源与逐字错误输出见 `data/status/_layout_assert_probe_20260925/README.md`：

* **E-4 PMF 尺寸封闭规则**（`p3.cpp` 复现 + 本轮 `shape.cpp` 扩展）
  ```
  有虚基(传递闭包内) ⇒ 12；否则闭包内出现多继承分支 ⇒ 8；否则 ⇒ 4
  ```
  扩展实测（本轮，`shape.cpp`）：**单直接基、但其基类是多继承类 ⇒ 8（不是 4）**；
  单直接基含虚基 ⇒ 12；深单继承链 ⇒ 4。⇒ 判据必须走**传递闭包**，不能只看直接基个数。
* **E-3 `offsetof` 虚基成员 ⇒ C2057**（`p3.cpp:28` 逐字复现）：
  虚基成员、以及**虚基的非虚基之成员**（`off.cpp:18`）都不是常量表达式 ⇒ 必须跳过；
  而"有虚基的类里，非虚基成员/本类成员"的 offsetof **是常量**（`off.cpp` o3/o4/o6 行
  仅 C2118 值不符、无 C2057）⇒ 只有**虚基区域**内的成员跳过。
* **E-1 被污染的常量会判死正确注解**（`w1/w2.cpp`）⇒ 可疑常量必须有独立分支；
  **E-2 同源常量零判别力**（编译通过但无校验价值）。

运行：`python3 tests/test_layout_assert_gen.py` 或 `pytest tests/test_layout_assert_gen.py`
"""
import json
import re
import sys
import tempfile
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from layout_assert_gen import (  # noqa: E402
    EVIDENCE_DEFAULT,
    GRADE_A,
    GRADE_B,
    GRADE_C,
    KIND_OFFSET,
    KIND_SHAPE,
    KIND_SIZE,
    MARK_SAME_SOURCE,
    MARK_SUSPECT,
    PMF_SIZE_MULTIPLE,
    PMF_SIZE_SINGLE,
    PMF_SIZE_VIRTUAL,
    POLICY_ASSERT,
    POLICY_COMMENT,
    POLICY_SKIP,
    STATUS_ACTIVE,
    STATUS_COMMENTED,
    STATUS_OMITTED,
    TRUST_SAME_SOURCE,
    TRUST_SUSPECT,
    TRUST_TRUSTED,
    BaseSpec,
    ClassLayout,
    Evidence,
    GenOptions,
    MemberSpec,
    NameRegistry,
    build_assertions,
    evidence_from_source,
    evidence_trust,
    generate,
    load_evidence,
    load_struct_layouts,
    load_virtual_bases,
    member_offset_assertable,
    pmf_size_for,
    shape_info,
    virtual_base_region,
)

REAL_STRUCTS = PROJECT_ROOT / 'data' / 'annotations' / 'structs'
REAL_TREE = PROJECT_ROOT / 'data' / 'status' / '_inheritance_tree.json'

# 生成行形态：`typedef char NAME[(COND) ? 1 : -1];`（注释掉的行同样被这条正则捕获）
TYPEDEF_RE = re.compile(r'typedef char (\w+)\s*\[\((?P<cond>.+?)\)\s*\?\s*1\s*:\s*-1\];')
ACTIVE_RE = re.compile(r'^typedef char (\w+)\s*\[', re.M)


# ================= 夹具构造 =================

def _ev(grade=GRADE_A, origin='ida_binary', detail='mov [ecx+0Ch], eax @0x4C5D50',
        independent=True, misattributed=False):
    return Evidence(grade=grade, origin=origin, detail=detail,
                    independent=independent, misattributed=misattributed)


def _b(name, offset=None, virtual=False):
    return BaseSpec(name=name, offset=offset, is_virtual=virtual)


def _m(name, offset, owner=None, in_vbase=False, ev=None, type_='int'):
    return MemberSpec(name=name, offset=offset, owner=owner, in_virtual_base=in_vbase,
                      type=type_, evidence=ev if ev is not None else EVIDENCE_DEFAULT)


def _cls(name, bases=(), members=(), size=None, size_ev=None):
    return ClassLayout(name=name, bases=tuple(bases), members=tuple(members),
                       binary_size=size,
                       size_evidence=size_ev if size_ev is not None else EVIDENCE_DEFAULT)


def _names(text):
    """生成文本里出现过的全部断言类型名（active + commented 行都算）。"""
    return [m.group(1) for m in TYPEDEF_RE.finditer(text)]


def _active_names(text):
    return [m.group(1) for m in ACTIVE_RE.finditer(text)]


def _line_for(text, name):
    for line in text.splitlines():
        if TYPEDEF_RE.search(line) and (' %s[' % name) in line:
            return line
    raise AssertionError('no line for %s' % name)


def _trusted_layouts():
    """一个形状完整、常量全部可信的最小布局集。"""
    return {
        'A': _cls('A', members=[_m('a', 4, ev=_ev())], size=8, size_ev=_ev()),
        'V1': _cls('V1', members=[_m('vv', 4)], size=8),
        'D': _cls('D', bases=[_b('A')], members=[_m('d', 8, ev=_ev())], size=16,
                  size_ev=_ev()),
    }


# ================= 1. 继承形状 → PMF 尺寸（E-4 封闭规则） =================

def test_single_inheritance_pmf_is_4():
    """单直接基、其基类也是单链 ⇒ `sizeof(void (D::*)()) == 4`（p3.cpp t_SI4 通过）。"""
    layouts = {'A': _cls('A'), 'D': _cls('D', bases=[_b('A')])}
    assert pmf_size_for(layouts['D'].bases, layouts) == PMF_SIZE_SINGLE
    assert PMF_SIZE_SINGLE == 4


def test_multiple_inheritance_two_bases_pmf_is_8():
    """`MI2 : A1, B1` ⇒ 8（p3.cpp t_MI28 通过、t_MI38 逐字）。"""
    layouts = {'A': _cls('A'), 'B': _cls('B'), 'M': _cls('M', bases=[_b('A'), _b('B')])}
    assert pmf_size_for(layouts['M'].bases, layouts) == PMF_SIZE_MULTIPLE


def test_three_bases_pmf_is_8():
    layouts = {'A': _cls('A'), 'B': _cls('B'), 'C': _cls('C'),
               'M': _cls('M', bases=[_b('A'), _b('B'), _b('C')])}
    assert pmf_size_for(layouts['M'].bases, layouts) == PMF_SIZE_MULTIPLE


def test_virtual_base_only_pmf_is_12():
    """`VOnly : virtual V1` ⇒ 12（p3.cpp t_VI12 通过）。"""
    layouts = {'V': _cls('V'), 'D': _cls('D', bases=[_b('V', virtual=True)])}
    assert pmf_size_for(layouts['D'].bases, layouts) == PMF_SIZE_VIRTUAL


def test_multiple_inheritance_plus_virtual_base_pmf_is_12():
    """★ 优先级：`MIV : A1, B1, virtual V1` ⇒ **12**。

    E-4：若先判"多继承 ⇒ 8"就假失败（p3.cpp:19 `t_MIV8` 实测 **C2118**，
    而 :20 `t_MIV12` 通过）⇒ 虚基判定必须先于多继承判定。
    """
    layouts = {'A': _cls('A'), 'B': _cls('B'), 'V': _cls('V'),
               'M': _cls('M', bases=[_b('A'), _b('B'), _b('V', virtual=True)])}
    assert pmf_size_for(layouts['M'].bases, layouts) == PMF_SIZE_VIRTUAL


def test_two_virtual_bases_stay_12_not_16():
    """多虚基仍是 12（p3.cpp:25 `t_VV16` 实测 C2118、:24 `t_VV12` 通过）。"""
    layouts = {'V1': _cls('V1'), 'V2': _cls('V2'),
               'D': _cls('D', bases=[_b('V1', virtual=True), _b('V2', virtual=True)])}
    got = pmf_size_for(layouts['D'].bases, layouts)
    assert got == PMF_SIZE_VIRTUAL and got != 16


def test_single_base_whose_ancestor_is_mi_pmf_is_8():
    """★★ 本轮实测修正：`DERofMI2 : MI2`（单直接基，但 MI2 是多继承类）⇒ **8**，不是 4。

    `shape.cpp:28` `t_DERofMI2_4` 实测 C2118、:29 `t_DERofMI2_8` 通过
    ⇒ 只看"直接基个数"的朴素规则会假失败（E-4 同类停摆）。
    """
    layouts = {'A': _cls('A'), 'B': _cls('B'),
               'MI2': _cls('MI2', bases=[_b('A'), _b('B')]),
               'D': _cls('D', bases=[_b('MI2')])}
    assert pmf_size_for(layouts['D'].bases, layouts) == PMF_SIZE_MULTIPLE


def test_deep_single_chain_below_mi_pmf_is_8():
    """MI 之下的深单链仍是 8（`shape.cpp:34/35`：DERofDERofMI2 ⇒ 8）。"""
    layouts = {'A': _cls('A'), 'B': _cls('B'),
               'MI2': _cls('MI2', bases=[_b('A'), _b('B')]),
               'D1': _cls('D1', bases=[_b('MI2')]),
               'D2': _cls('D2', bases=[_b('D1')])}
    assert pmf_size_for(layouts['D2'].bases, layouts) == PMF_SIZE_MULTIPLE


def test_single_base_with_virtual_ancestor_pmf_is_12():
    """虚基在祖先里 ⇒ 后代仍是 12（`shape.cpp:32/33`：DERofV ⇒ 12）。"""
    layouts = {'V': _cls('V'), 'VOnly': _cls('VOnly', bases=[_b('V', virtual=True)]),
               'D': _cls('D', bases=[_b('VOnly')])}
    assert pmf_size_for(layouts['D'].bases, layouts) == PMF_SIZE_VIRTUAL


def test_deep_single_inheritance_chain_pmf_is_4():
    """纯单链多深都是 4（`shape.cpp:31`：DERofSI ⇒ 4）。"""
    layouts = {'A': _cls('A'), 'B': _cls('B', bases=[_b('A')]),
               'C': _cls('C', bases=[_b('B')])}
    assert pmf_size_for(layouts['C'].bases, layouts) == PMF_SIZE_SINGLE


def test_golden_shape_matrix_matches_msvc6_probe():
    """表驱动总控：探针矩阵逐行（含本轮扩展行）与实现一致。"""
    layouts = {
        'A1': _cls('A1'), 'B1': _cls('B1'), 'C1': _cls('C1'),
        'V1': _cls('V1'), 'V2': _cls('V2'),
    }
    layouts.update({
        'SI': _cls('SI', bases=[_b('A1')]),
        'DERofSI': _cls('DERofSI', bases=[_b('SI')]),
        'MI2': _cls('MI2', bases=[_b('A1'), _b('B1')]),
        'MI3': _cls('MI3', bases=[_b('A1'), _b('B1'), _b('C1')]),
        'DERofMI2': _cls('DERofMI2', bases=[_b('MI2')]),
        'DERofDERofMI2': _cls('DERofDERofMI2', bases=[_b('DERofMI2')]),
        'VOnly': _cls('VOnly', bases=[_b('V1', virtual=True)]),
        'DERofV': _cls('DERofV', bases=[_b('VOnly')]),
        'MIV': _cls('MIV', bases=[_b('A1'), _b('B1'), _b('V1', virtual=True)]),
        'MIVV': _cls('MIVV', bases=[_b('A1'), _b('V1', virtual=True), _b('V2', virtual=True)]),
        'VV': _cls('VV', bases=[_b('V1', virtual=True), _b('V2', virtual=True)]),
    })
    # (形状, 实测 PMF, 探针出处行)
    golden = [
        ('SI', 4, 'p3.cpp t_SI4'),
        ('DERofSI', 4, 'shape.cpp t_DERofSI_4'),
        ('MI2', 8, 'p3.cpp t_MI28'),
        ('MI3', 8, 'p3.cpp t_MI38'),
        ('DERofMI2', 8, 'shape.cpp t_DERofMI2_8'),
        ('DERofDERofMI2', 8, 'shape.cpp t_DERofDERofMI2_8'),
        ('VOnly', 12, 'p3.cpp t_VI12'),
        ('DERofV', 12, 'shape.cpp t_DERofV_12'),
        ('MIV', 12, 'p3.cpp t_MIV12'),
        ('MIVV', 12, 'p3.cpp t_MIVV12'),
        ('VV', 12, 'p3.cpp t_VV12'),
    ]
    for cls, expected, src in golden:
        got = pmf_size_for(layouts[cls].bases, layouts)
        assert got == expected, '%s: got %d, want %d (%s)' % (cls, got, expected, src)


def test_shape_info_reports_reason_and_closure():
    layouts = {'A': _cls('A'), 'B': _cls('B'), 'V': _cls('V'),
               'M': _cls('M', bases=[_b('A'), _b('B'), _b('V', virtual=True)])}
    info = shape_info(layouts['M'], layouts)
    assert info.pmf_size == PMF_SIZE_VIRTUAL
    assert info.has_virtual_base is True
    assert info.branching is True
    assert 'V' in info.closure and 'A' in info.closure
    assert '虚基' in info.reason
    single = shape_info(layouts['A'], layouts)
    assert '单继承' in single.reason


def test_shape_assert_is_suspect_when_base_graph_incomplete():
    """★ 安全属性：基类本身没有布局信息 ⇒ 形状不可证 ⇒ 断言必须降级为可疑。

    否则"未知基类恰好是多继承类"会被当成 4 ⇒ **假 C2118 停摆**（E-4 同型）。
    """
    layouts = {'D': _cls('D', bases=[_b('UnknownBase')])}
    info = shape_info(layouts['D'], layouts)
    assert info.unresolved == frozenset({'UnknownBase'})
    assert '不可证' in info.reason
    res = generate(layouts, GenOptions())
    assert all(a.status == STATUS_COMMENTED for a in res.assertions if a.kind == KIND_SHAPE)
    assert MARK_SUSPECT in res.text


def test_embed_modeled_multi_inheritance_shape_is_suspect():
    """★ 真数据里的具体雷：多继承被建模成内嵌基类成员（UIEmote 的 `baseclass2`，
    source=`PAL3patch:multi_inheritance_as_embed`）⇒ 声明的继承形状 ≠ 注解形状 ⇒
    若照注解形状断言 8，而 codegen 声明是单继承 ⇒ **假 C2118 停摆**。
    """
    layouts = {
        'UIWnd': _cls('UIWnd'),
        'PalScriptWaitObj': _cls('PalScriptWaitObj'),
        'UIEmote': _cls('UIEmote', bases=[_b('UIWnd'), _b('PalScriptWaitObj')],
                        members=[_m('baseclass2', 68, ev=_ev()),
                                 _m('m_cur', 76, ev=_ev())]),
    }
    embed = _m('baseclass2', 68, ev=_ev())
    layouts['UIEmote'] = ClassLayout(
        name='UIEmote', bases=(_b('UIWnd'), _b('PalScriptWaitObj')),
        members=(MemberSpec(name='baseclass2', offset=68, type='PalScriptWaitObj',
                            source='PAL3patch:multi_inheritance_as_embed', evidence=_ev()),
                 embed),
        binary_size=2272)
    res = generate(layouts, GenOptions())
    shape = [a for a in res.assertions if a.kind == KIND_SHAPE and a.cls == 'UIEmote'][0]
    assert shape.trust == TRUST_SUSPECT
    assert shape.status == STATUS_COMMENTED
    assert '内嵌基类成员' in shape.reason or '内嵌' in shape.reason


# ================= 2. offsetof 虚基跳过（E-3） =================

def test_member_of_virtual_base_is_skipped():
    """虚基成员 offsetof **不是常量表达式**（p3.cpp:28 实测 C2057）⇒ 跳过。"""
    layouts = {'V': _cls('V', members=[_m('vv', 4)]),
               'D': _cls('D', bases=[_b('V', virtual=True)], members=[_m('dm', 4)])}
    ok, reason = member_offset_assertable(layouts['D'], _m('vv', 8, owner='V'), layouts)
    assert ok is False
    assert 'C2057' in reason or '虚基' in reason


def test_member_of_nonvirtual_base_of_virtual_base_is_skipped():
    """虚基的**非虚基**之成员同样非常量（off.cpp:18 实测 C2057）⇒ 跳过（传递闭包）。"""
    layouts = {
        'V1': _cls('V1', members=[_m('w', 4)]),
        'VB2': _cls('VB2', bases=[_b('V1')], members=[_m('x', 8)]),
        'D': _cls('D', bases=[_b('VB2', virtual=True)], members=[_m('dm', 4)]),
    }
    assert 'V1' in virtual_base_region(layouts['D'], layouts)
    assert 'VB2' in virtual_base_region(layouts['D'], layouts)
    ok, reason = member_offset_assertable(layouts['D'], _m('w', 12, owner='V1'), layouts)
    assert ok is False and ('C2057' in reason or '虚基' in reason)


def test_own_member_of_virtual_inheriting_class_is_assertable():
    """有虚基的类的**本类**成员 offsetof 是常量（off.cpp o4/o6 只有 C2118 无 C2057）⇒ 可断言。"""
    layouts = {'V': _cls('V', members=[_m('vv', 4)]),
               'D': _cls('D', bases=[_b('V', virtual=True)], members=[_m('dm', 4)])}
    ok, reason = member_offset_assertable(layouts['D'], layouts['D'].members[0], layouts)
    assert ok is True, reason


def test_nonvirtual_base_member_stays_assertable_when_class_has_virtual_base():
    """有虚基的类里，**非虚基**成员 offsetof 是常量（off.cpp o3 ⇒ 可断言）。"""
    layouts = {'A': _cls('A', members=[_m('a', 4)]), 'V': _cls('V'),
               'D': _cls('D', bases=[_b('A'), _b('V', virtual=True)],
                         members=[_m('x', 8)])}
    ok, reason = member_offset_assertable(layouts['D'], _m('a', 4, owner='A'), layouts)
    assert ok is True, reason
    assert virtual_base_region(layouts['D'], layouts) == frozenset({'V'})


def test_member_inside_recorded_virtual_base_range_is_skipped_conservatively():
    """注解若把虚基成员摊平进本类（offset 落在虚基记录区间内）⇒ 保守跳过。"""
    layouts = {
        'V': _cls('V', members=[_m('vv', 4)], size=8),
        'D': _cls('D', bases=[_b('V', offset=12, virtual=True)],
                  members=[_m('dm', 4), _m('flattened', 16)]),
    }
    ok, reason = member_offset_assertable(layouts['D'], _m('flattened', 16), layouts)
    assert ok is False and ('虚基' in reason)
    ok2, _ = member_offset_assertable(layouts['D'], _m('dm', 4), layouts)
    assert ok2 is True


def test_unnamed_member_is_skipped():
    layouts = {'A': _cls('A', members=[_m('', 4)])}
    res = generate(layouts, GenOptions())
    assert res.census['skipped'] >= 1
    assert res.offset_skipped, res.offset_skipped
    assert not any(a.kind == KIND_OFFSET and a.status == STATUS_ACTIVE for a in res.assertions)


def test_skipped_member_appears_in_census_with_reason():
    layouts = {'V': _cls('V'), 'D': _cls('D', bases=[_b('V', virtual=True)],
                                         members=[_m('dm', 4, owner='V')])}
    res = generate(layouts, GenOptions())
    assert res.census['skipped'] == 1
    assert any('虚基' in r for r in res.census['skip_reasons'])


# ================= 3. 断言类型名全局唯一 =================

def test_assertion_type_names_are_globally_unique():
    """同名 typedef ⇒ MSVC6 C2086（重定义）⇒ 生成器必须全局去重。"""
    layouts = {
        'A<B>': _cls('A<B>', members=[_m('x', 4, ev=_ev()), _m('x', 4, ev=_ev())]),
        'A_B_': _cls('A_B_', members=[_m('x', 4, ev=_ev())]),
        'D': _cls('D', bases=[_b('A<B>')], members=[_m('x', 4, ev=_ev()), _m('y', 8, ev=_ev())],
                  size=16, size_ev=_ev()),
    }
    text = generate(layouts, GenOptions()).text
    names = _names(text)
    assert len(names) == len(set(names)), 'duplicate typedef names: %s' % names
    assert len(names) >= 6


def test_colliding_sanitized_class_names_are_disambiguated():
    """两个类名 sanitize 后相同（`Foo<Bar>` / `Foo_Bar_`）⇒ 名字仍唯一。"""
    reg = NameRegistry()
    a = reg.reserve('_a_Foo_Bar__x')
    b = reg.reserve('_a_Foo_Bar__x')
    assert a != b
    assert reg.reserve('_a_Foo_Bar__x') not in (a, b)


def test_duplicate_layout_input_is_deduped():
    """同一类被喂两次 ⇒ 不得产生重复 typedef。"""
    layouts = {'A': _cls('A', members=[_m('a', 4, ev=_ev())])}
    res = generate([layouts['A'], layouts['A']], GenOptions())
    names = _names(res.text)
    assert len(names) == len(set(names))
    assert res.warnings and any('重复' in w for w in res.warnings)


def test_non_identifier_member_names_are_skipped_not_sanitized_into_collisions():
    """真数据里出现过的空成员名/非标识符名 ⇒ 跳过并留痕（不得生成非法/撞名 typedef）。"""
    layouts = {'A': _cls('A', members=[_m('', 4), _m('a b', 8), _m('ok', 12, ev=_ev())])}
    res = generate(layouts, GenOptions())
    names = _names(res.text)
    assert len(names) == len(set(names))
    assert 'ok' in res.text
    assert res.census['skipped'] == 2


# ================= 4. 头文件结构（#include <stddef.h> 注入等） =================

def test_stddef_include_is_injected():
    """`offsetof` 需要 `#include <stddef.h>`（p2.cpp 缺它 ⇒ C2065 'offsetof' undeclared）。"""
    text = generate(_trusted_layouts(), GenOptions()).text
    assert '#include <stddef.h>' in text
    assert 'offsetof(' in text


def test_stddef_include_can_be_disabled():
    text = generate(_trusted_layouts(), GenOptions(include_stddef=False)).text
    assert '#include <stddef.h>' not in text


def test_include_guard_present():
    text = generate(_trusted_layouts(), GenOptions()).text
    assert '#ifndef PAL3_LAYOUT_ASSERTS_H' in text
    assert '#define PAL3_LAYOUT_ASSERTS_H' in text
    assert text.rstrip().endswith('#endif /* PAL3_LAYOUT_ASSERTS_H */')


def test_negative_array_typedef_form():
    """三态断言统一用 MSVC6 负数组技巧（无 static_assert）。"""
    text = generate(_trusted_layouts(), GenOptions()).text
    assert 'static_assert' not in text
    for name in _active_names(text):
        assert TYPEDEF_RE.search(_line_for(text, name)), name
    assert 'sizeof(void (A::*)()) == 4' in text
    assert 'sizeof(A) == 8' in text
    assert 'offsetof(A, a) == 4' in text


def test_header_carries_error_handling_table_with_suspect_branch():
    """★ E-1：错误处理表必须含"常量本身可疑"分支，否则工程师唯一出路是把正确注解改坏。"""
    text = generate(_trusted_layouts(), GenOptions()).text
    assert '错误处理表' in text
    assert '常量可疑' in text or '常量本身可疑' in text
    assert 'C2057' in text          # 虚基 offsetof 分支
    assert 'E-1' in text and 'E-2' in text


def test_deterministic_output():
    """连续两次生成逐字相同（可重跑、可进棘轮）。"""
    layouts = _trusted_layouts()
    a = generate(layouts, GenOptions()).text
    b = generate(layouts, GenOptions()).text
    assert a == b


def test_only_option_still_resolves_closure_for_shape():
    """`--only` 只过滤**渲染**哪些类；闭包查表必须仍用全部布局。

    否则被选中类的基类会变成"未知基类" ⇒ 形状被误判为不可证 ⇒ 静默丢覆盖。
    （真实数据实测：`--only CEffSParticle,CCBUI,SceneObj` 曾产出 0 条断言。）
    """
    layouts = {
        'A': _cls('A', members=[_m('a', 4, ev=_ev())], size=8, size_ev=_ev()),
        'B': _cls('B', members=[_m('b', 4, ev=_ev())], size=8, size_ev=_ev()),
        'D': _cls('D', bases=[_b('A'), _b('B')], size=16, size_ev=_ev()),
    }
    res = generate(layouts, GenOptions(only=frozenset({'D'})))
    assert {a.cls for a in res.assertions} == {'D'}
    shape = [a for a in res.assertions if a.kind == KIND_SHAPE][0]
    assert shape.expected == PMF_SIZE_MULTIPLE          # 8：闭包仍看得见 A/B
    assert shape.status == STATUS_ACTIVE
    assert 'sizeof(void (D::*)()) == 8' in res.text


# ================= 5. 常量可信度（A 级形态 ≠ 独立性；E-1/E-2） =================

def test_evidence_trust_matrix():
    assert evidence_trust(_ev()) == TRUST_TRUSTED
    assert evidence_trust(_ev(misattributed=True)) == TRUST_SUSPECT
    assert evidence_trust(_ev(grade=GRADE_B, origin='pdb')) == TRUST_SUSPECT
    assert evidence_trust(_ev(grade=GRADE_C, origin='decomp')) == TRUST_SUSPECT
    assert evidence_trust(_ev(independent=False)) == TRUST_SAME_SOURCE
    # ★ A 级是**形态**等级，不是独立性等级：A + 非独立 ⇒ 同源（零判别力）
    assert evidence_trust(_ev(grade=GRADE_A, independent=False)) != TRUST_TRUSTED


def test_misattributed_evidence_marks_suspect_and_comments_out():
    """★ E-1：常量被怀疑时**不得**生成生效断言（否则判死正确注解）。"""
    layouts = {'A': _cls('A', members=[_m('a', 12, ev=_ev(misattributed=True))])}
    res = generate(layouts, GenOptions(emit_shape=False))
    line = _line_for(res.text, [a.name for a in res.assertions if a.kind == KIND_OFFSET][0])
    assert line.lstrip().startswith('//')
    assert MARK_SUSPECT in line
    assert '常量可疑' in line
    assert res.census['commented'] >= 1 and res.census['active'] == 0


def test_same_source_evidence_is_marked_and_not_active_by_default():
    """★ E-2：同源常量编译通过但零判别力 ⇒ 默认只留痕不生效。"""
    layouts = {'A': _cls('A', members=[_m('a', 4, ev=_ev(independent=False, origin='annotation'))])}
    res = generate(layouts, GenOptions())
    line = _line_for(res.text, [a.name for a in res.assertions if a.kind == KIND_OFFSET][0])
    assert line.lstrip().startswith('//')
    assert MARK_SAME_SOURCE in line
    assert res.census[TRUST_SAME_SOURCE] == 1


def test_untrusted_policy_assert_emits_active_lines():
    layouts = {'A': _cls('A', members=[_m('a', 12, ev=_ev(misattributed=True))])}
    res = generate(layouts, GenOptions(untrusted_policy=POLICY_ASSERT, emit_shape=False))
    assert res.census['active'] == 1
    assert MARK_SUSPECT in res.text          # 生效但仍留可疑标记
    assert all(not l.lstrip().startswith('//')
               for l in res.text.splitlines() if 'offsetof(A, a)' in l)


def test_untrusted_policy_skip_omits_lines_entirely():
    layouts = {'A': _cls('A', members=[_m('a', 12, ev=_ev(misattributed=True))])}
    res = generate(layouts, GenOptions(untrusted_policy=POLICY_SKIP, emit_shape=False))
    assert res.census['omitted'] == 1
    assert 'offsetof(A, a)' not in res.text


def test_shape_assertion_is_trusted_with_probe_evidence():
    """形状断言的常量来自 MSVC6 探针（A 形态 + 独立于 annotation）⇒ 默认可生效。"""
    res = generate(_trusted_layouts(), GenOptions())
    shapes = [a for a in res.assertions if a.kind == KIND_SHAPE]
    assert shapes and all(a.trust == TRUST_TRUSTED for a in shapes)
    assert all(a.status == STATUS_ACTIVE for a in shapes)
    assert 'probe' in shapes[0].evidence.origin or 'probe' in shapes[0].evidence.detail


def test_census_counts_by_kind_and_trust():
    res = generate(_trusted_layouts(), GenOptions())
    c = res.census
    assert c['total'] == len(res.assertions)
    assert c['active'] + c['commented'] + c['omitted'] == c['total']
    assert set(c['by_kind']) == {KIND_SHAPE, KIND_SIZE, KIND_OFFSET}
    assert c[TRUST_TRUSTED] >= 1
    assert c['skipped'] == 0


def test_evidence_from_source_grades_a_form():
    """A 形态判据：reg+disp32 或绝对地址（规则原文逐字）。"""
    assert evidence_from_source('binary: ctor `mov [ecx+0Ch], offset <vtable>`').grade == GRADE_A
    assert evidence_from_source('A: mov [reg+0Ch], eax @0x004D4F00').grade == GRADE_A
    assert evidence_from_source('abs 0x0056FB34 write').grade == GRADE_A
    assert evidence_from_source('PDB:m_cur_16_hint').grade == GRADE_B
    assert evidence_from_source('decomp:9x_direct_read(size_or_count)').grade == GRADE_C
    assert evidence_from_source('').grade == GRADE_C
    # 来源是注解 ⇒ 一律非独立（A 级形态 ≠ 独立性）
    ev = evidence_from_source('binary: mov [ecx+0Ch]')
    assert ev.grade == GRADE_A and ev.independent is False
    assert evidence_trust(ev) == TRUST_SAME_SOURCE


# ================= 6. 数据源装载（annotation / 继承树 / 覆盖文件） =================

def _write(tmp, name, obj):
    p = Path(tmp) / name
    p.write_text(json.dumps(obj), encoding='utf-8')
    return p


def test_load_struct_layouts_reads_bases_members_and_hex_offsets():
    with tempfile.TemporaryDirectory() as tmp:
        d = Path(tmp) / 'structs'
        d.mkdir()
        _write(d, 'A.json', {'name': 'A', 'binary_size': 8,
                             'known_members': {'0': {'name': 'a', 'type': 'int',
                                                     'source': 'binary: mov [ecx+4], eax'}}})
        _write(d, 'D.json', {'name': 'D', 'binary_size': 16, 'base_class': ['A'],
                             'base_size': 8,
                             'known_members': {
                                 '8': {'name': 'd', 'type': 'int',
                                       'source': 'decomp:9x_direct_read'},
                                 '0x0C': {'name': 'e', 'type': 'int',
                                          'source': 'binary: mov [ecx+0Ch], eax'}}})
        layouts = load_struct_layouts(d)
        assert set(layouts) == {'A', 'D'}
        assert layouts['D'].bases == (BaseSpec(name='A', offset=None, is_virtual=False),)
        assert [m.offset for m in layouts['D'].members] == [8, 12]     # '0x0C' 被解析
        assert layouts['D'].members[1].evidence.grade == GRADE_A
        assert layouts['D'].members[0].evidence.grade == GRADE_C
        assert layouts['D'].binary_size == 16


def test_tree_is_fallback_for_classes_without_base_class():
    with tempfile.TemporaryDirectory() as tmp:
        d = Path(tmp) / 'structs'
        d.mkdir()
        _write(d, 'A.json', {'name': 'A', 'binary_size': 4})
        _write(d, 'X.json', {'name': 'X', 'binary_size': 8})
        tree = _write(tmp, 'tree.json', {'X': 'A', 'A': None})
        layouts = load_struct_layouts(d, tree_path=tree)
        assert layouts['X'].bases == (BaseSpec(name='A', offset=None, is_virtual=False),)
        assert layouts['A'].bases == ()


def test_load_virtual_bases_override_is_honored():
    with tempfile.TemporaryDirectory() as tmp:
        d = Path(tmp) / 'structs'
        d.mkdir()
        _write(d, 'V.json', {'name': 'V', 'binary_size': 8})
        _write(d, 'D.json', {'name': 'D', 'binary_size': 16, 'base_class': ['V']})
        vb = _write(tmp, 'vb.json', {'D': ['V']})
        layouts = load_struct_layouts(d, virtual_bases=load_virtual_bases(vb))
        assert layouts['D'].bases[0].is_virtual is True
        assert pmf_size_for(layouts['D'].bases, layouts) == PMF_SIZE_VIRTUAL


def test_load_evidence_json_is_applied_and_marks_independence():
    with tempfile.TemporaryDirectory() as tmp:
        d = Path(tmp) / 'structs'
        d.mkdir()
        _write(d, 'A.json', {'name': 'A', 'binary_size': 8, 'base_class': [],
                             'known_members': {'4': {'name': 'a', 'type': 'int',
                                                     'source': 'annotation'}}})
        evp = _write(tmp, 'ev.json', {
            'A': {'size': {'grade': 'A', 'origin': 'ida_binary', 'independent': True,
                           'detail': 'operator new(8) @0x41BE80'},
                  'members': {'a': {'grade': 'A', 'origin': 'ida_binary', 'independent': True,
                                    'detail': 'mov [ecx+4], eax @0x4C5D50'}}}})
        layouts = load_struct_layouts(d, evidence=load_evidence(evp))
        res = generate(layouts, GenOptions())
        assert layouts['A'].size_evidence.trust() == TRUST_TRUSTED
        assert layouts['A'].members[0].evidence.trust() == TRUST_TRUSTED
        assert res.census['active'] == 3          # shape + size + offset 全生效


def test_real_annotations_load_without_error():
    layouts = load_struct_layouts(REAL_STRUCTS, tree_path=REAL_TREE)
    assert len(layouts) >= 880          # 898 个文件，17 组同名（HBRUSH_/HBRUSH__ 之类）⇒ 去重
    # SceneObj 的 known_members 用 '0x44' 形键 ⇒ 必须能解析
    assert any(m.offset == 0x44 for m in layouts['SceneObj'].members)
    # 注解里 31 个多基类必须被识别
    multi = [c for c in layouts.values() if len(c.bases) > 1]
    assert len(multi) >= 25, len(multi)


def test_real_data_generates_header_with_active_shape_asserts():
    layouts = load_struct_layouts(REAL_STRUCTS, tree_path=REAL_TREE)
    res = generate(layouts, GenOptions())
    assert res.census['total'] > 100
    assert res.census['active'] >= 50
    assert '#include <stddef.h>' in res.text
    names = _names(res.text)
    assert len(names) == len(set(names))


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)