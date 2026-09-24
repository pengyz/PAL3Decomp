"""`tools/vtable_slot_order.py` 的测试 —— **先写测试**（TDD，红→绿）。

本文件是 vtable **正向规则**（声明 → 槽序）的金样本回归集。所有 expected 值均为
**真机 MSVC 6.0 SP0（cl 12.00.8168，`tools/wine_cl.sh`）实测** vtable（`tools/coff_vtable.py`
按原始 COFF 索引解 reloc）逐槽读出，不是推演值：

* `_vtable_abi_probe_20260925/README.md` #8 —— T1/T2/T3/O（同名组逆序）与 DO（覆写原位）
  （README #8 只报了 T1/T3/O/DO，T2 为同目录 vt7.cpp 控制组，槽序亦实测复核）
* `_vtable_abi_probe_20260925/README.md` #1/#3 + vt2.cpp/vt3.cpp —— MI 多视图（vt2/vt3）
* `_vtable_advprobe_20260925/README.md` —— adv2（D2 尾插跨区段）· adv3（C3 合成槽）·
  adv4（D3 尾插段内逆序）
* `_vtable_attack_cases_20260925/README.md` A-1/A-2 —— a1/a2/a3/a4（派生类覆写+新增同名重载）
* **补充实测**（2026-09-25，本任务新增探针 syn_probe.cpp / syn_probe2.cpp，源码与完整输出见
  `.superpowers/sdd/2026-09-25-vtable-mapping-plan/task-1-report.md` 附录）——
  P1/P2/P2b/D5（合成槽"落声明位"的精确语义）· D7/D8（析构覆写原位）· D6（段内跨名打包）·
  D9/DA（覆写参与本地段打包后再摘除）· DB（派生段同名组跨名打包）

运行：`python3 tests/test_vtable_slot_order.py` 或 `pytest tests/test_vtable_slot_order.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from vtable_slot_order import (  # noqa: E402
    KIND_DELETING_DTOR,
    KIND_FUNC,
    VirtualDecl,
    compute_class_views,
    compute_slot_order,
    layout_local_segment,
    match_key,
)


# ---------------- 金样本小工具 ----------------

def V(name, sig, kind=KIND_FUNC, owner=''):
    return VirtualDecl(name=name, sig=sig, kind=kind, owner=owner)


def K(owner, name, sig, kind=KIND_FUNC):
    """expected 槽键：(声明类, 名字, 声明级签名, 槽型)。"""
    return (owner, name, sig, kind)


def SK(entries):
    """槽序列 → 槽键序列。"""
    return [(e.decl.owner, e.decl.name, e.decl.sig, e.decl.kind) for e in entries]


DT = KIND_DELETING_DTOR


# ================= 1. 同名组逆序（abi README #8，vt7.cpp / vt6.cpp） =================

def test_t1_same_name_group_reversed():
    """T1 decl[o(),o(int),o(double)] → 槽[o(double),o(int),o()]（实测 ?o@T1@@UAEXN/H/XZ）"""
    decls = [V('o', '()'), V('o', '(int)'), V('o', '(double)')]
    got = SK(compute_slot_order([], decls))
    assert got == [K('', 'o', '(double)'), K('', 'o', '(int)'), K('', 'o', '()')], got


def test_t2_distinct_names_keep_declaration_order():
    """T2 decl[a,b,c,d] → 槽[a,b,c,d]：无同名 ⇒ 无逆序（实测 ?a/?b/?c/?d@T2@@UAEXXZ）"""
    decls = [V(n, '()') for n in ('a', 'b', 'c', 'd')]
    got = SK(compute_slot_order([], decls))
    assert got == [K('', n, '()') for n in ('a', 'b', 'c', 'd')], got


def test_t3_group_packs_at_first_occurrence_and_interloper_moves_after():
    """T3 decl[p,o(int),q,o(double)] → 槽[p,o(double),o(int),q]：
    同名组**整组占据首现声明的组位**（连续区段），插队者 q 被挤到组后。"""
    decls = [V('p', '()'), V('o', '(int)'), V('q', '()'), V('o', '(double)')]
    got = SK(compute_slot_order([], decls))
    assert got == [K('', 'p', '()'), K('', 'o', '(double)'),
                   K('', 'o', '(int)'), K('', 'q', '()')], got


def test_o_four_overloads_fully_reversed():
    """O decl[o(int),o(double),o(char*,int),o()] → 槽[o(),o(char*,int),o(double),o(int)]
    （实测 ?o@O@@UAEHPADH@Z / UAEXXZ / UAEXN@Z / UAEXH@Z）"""
    decls = [V('o', '(int)'), V('o', '(double)'), V('o', '(char*,int)'), V('o', '()')]
    got = SK(compute_slot_order([], decls))
    assert got == [K('', 'o', '()'), K('', 'o', '(char*,int)'),
                   K('', 'o', '(double)'), K('', 'o', '(int)')], got


# ================= 2. 继承原位保留 / 覆写原位替换 =================

def test_do_override_replaces_in_place_only_one_slot_changes():
    """DO : O 只声明 1 个覆写 o(double) ⇒ 槽序逐位继承 O 的 4 槽，仅槽 2 原位替换
    （advprobe README vt6_repro 行：「槽序逐位继承 O 的 4 槽；平坦反演会造出 3 个幽灵覆写」）"""
    o_slots = compute_slot_order([], [V('o', '(int)', owner='O'), V('o', '(double)', owner='O'),
                                      V('o', '(char*,int)', owner='O'), V('o', '()', owner='O')])
    got = SK(compute_slot_order(o_slots, [V('o', '(double)', owner='DO')]))
    assert got == [K('O', 'o', '()'), K('O', 'o', '(char*,int)'),
                   K('DO', 'o', '(double)'), K('O', 'o', '(int)')], got


def test_q_pure_virtual_override_replaces_in_place():
    """Q decl[p()=0,r()] → [p,r]；DQ 覆写 p ⇒ [p@DQ,r@Q]（vt2.cpp 实测 __purecall 槽原位替换）"""
    q_slots = compute_slot_order([], [V('p', '()', owner='Q'), V('r', '()', owner='Q')])
    got = SK(compute_slot_order(q_slots, [V('p', '()', owner='DQ')]))
    assert got == [K('DQ', 'p', '()'), K('Q', 'r', '()')], got


def test_dtor_override_replaces_in_place_first_slot():
    """D7 : B7 decl[~D7,g()] ⇒ [??_ED7, f@B7, g@D7]：析构覆写原位替换 B7 的槽 0（syn_probe 实测）"""
    b7 = compute_slot_order([], [V('~B7', '()', DT, 'B7'), V('f', '()', owner='B7')])
    got = SK(compute_slot_order(b7, [V('~D7', '()', DT, 'D7'), V('g', '()', owner='D7')]))
    assert got == [K('D7', '~D7', '()', DT), K('B7', 'f', '()'), K('D7', 'g', '()')], got


def test_dtor_override_replaces_in_place_mid_class():
    """D8 : B8 decl[~D8,g()] ⇒ [f@B8, ??_ED8, h@B8, g@D8]：合成槽覆写同样**原位**替换（syn_probe 实测）"""
    b8 = compute_slot_order([], [V('f', '()', owner='B8'), V('~B8', '()', DT, 'B8'),
                                 V('h', '()', owner='B8')])
    got = SK(compute_slot_order(b8, [V('~D8', '()', DT, 'D8'), V('g', '()', owner='D8')]))
    assert got == [K('B8', 'f', '()'), K('D8', '~D8', '()', DT),
                   K('B8', 'h', '()'), K('D8', 'g', '()')], got


# ================= 3. 本地新增段尾插 + 段内同名组逆序 =================

def test_adv2_new_overload_tail_appends_never_merges_into_base_group():
    """adv2：D2 : B2 新增同名重载 o(char) ⇒ 尾插主表末（槽 3），**永不并入基类组区段**
    ⇒ 名 "o" 占 {0,1,3} 跨区段不连续（advprobe README adv2 行，实测 ?o@D2@@UAEXD@Z 槽 3）"""
    b2 = compute_slot_order([], [V('o', '(int)', owner='B2'), V('o', '(double)', owner='B2'),
                                 V('p', '()', owner='B2')])
    assert SK(b2) == [K('B2', 'o', '(double)'), K('B2', 'o', '(int)'), K('B2', 'p', '()')]
    got = SK(compute_slot_order(b2, [V('o', '(char)', owner='D2')]))
    assert got == [K('B2', 'o', '(double)'), K('B2', 'o', '(int)'),
                   K('B2', 'p', '()'), K('D2', 'o', '(char)')], got


def test_adv4_tail_segment_internal_group_reversal():
    """adv4：D3 : B3 尾插段两个同名重载 y(int),y(double) + x ⇒ [a@B3, x, y(double), y(int)]
    —— 真实规则 = 基类槽位原位保留 ++ 新增段组内逆序（advprobe README adv4 行）"""
    b3 = compute_slot_order([], [V('a', '()', owner='B3')])
    got = SK(compute_slot_order(b3, [V('x', '()', owner='D3'), V('y', '(int)', owner='D3'),
                                     V('y', '(double)', owner='D3')]))
    assert got == [K('B3', 'a', '()'), K('D3', 'x', '()'),
                   K('D3', 'y', '(double)'), K('D3', 'y', '(int)')], got


def test_a1_new_overloads_form_own_segment_never_join_base_group():
    """A-2（a1.cpp）：D : B 新增 o(float),o(char),h ⇒ [f, o(double)@B, o(int)@B, g,
    o(char)@D, o(float)@D, h]——派生类新组内部同样逆序，永不并入基类组区段"""
    b = compute_slot_order([], [V('f', '()', owner='B'), V('o', '(int)', owner='B'),
                                V('o', '(double)', owner='B'), V('g', '()', owner='B')])
    assert SK(b) == [K('B', 'f', '()'), K('B', 'o', '(double)'),
                     K('B', 'o', '(int)'), K('B', 'g', '()')]
    got = SK(compute_slot_order(b, [V('o', '(float)', owner='D'), V('o', '(char)', owner='D'),
                                    V('h', '()', owner='D')]))
    assert got == [K('B', 'f', '()'), K('B', 'o', '(double)'), K('B', 'o', '(int)'),
                   K('B', 'g', '()'), K('D', 'o', '(char)'), K('D', 'o', '(float)'),
                   K('D', 'h', '()')], got


def test_a2_der_overrides_in_place_plus_new_tail():
    """A-1（a2.cpp，决定性样本）：Base decl[o(),o(int),mid(),o(double)] ⇒ [o(double),o(int),o(),mid]；
    Der 覆写 o(double),o(int) 原位 + 新增 o(char*),tail 尾插 ⇒
    [o(double)@Der, o(int)@Der, o()@Base, mid@Base, o(char*)@Der, tail@Der]
    —— 名 "o" 占 {0,1,2,4} 非连续（attack README A-1，实测 ?o@Der@@UAEXPAD@Z 槽 4）"""
    base = compute_slot_order([], [V('o', '()', owner='Base'), V('o', '(int)', owner='Base'),
                                   V('mid', '()', owner='Base'), V('o', '(double)', owner='Base')])
    assert SK(base) == [K('Base', 'o', '(double)'), K('Base', 'o', '(int)'),
                        K('Base', 'o', '()'), K('Base', 'mid', '()')]
    der_decls = [V('o', '(double)', owner='Der'), V('o', '(int)', owner='Der'),
                 V('o', '(char*)', owner='Der'), V('tail', '()', owner='Der')]
    got = SK(compute_slot_order(base, der_decls))
    assert got == [K('Der', 'o', '(double)'), K('Der', 'o', '(int)'), K('Base', 'o', '()'),
                   K('Base', 'mid', '()'), K('Der', 'o', '(char*)'), K('Der', 'tail', '()')], got


def test_a3_single_new_overload_tail_appends():
    """A-2（a3.cpp）：D3 : B3 只新增同名重载 o(char*)+z ⇒ 追加表尾 [..base.., z, o(char*)]"""
    b3 = compute_slot_order([], [V('p', '()', owner='B3'), V('o', '(int)', owner='B3'),
                                 V('o', '(double)', owner='B3'), V('q', '()', owner='B3')])
    got = SK(compute_slot_order(b3, [V('z', '()', owner='D3'), V('o', '(char*)', owner='D3')]))
    assert got == [K('B3', 'p', '()'), K('B3', 'o', '(double)'), K('B3', 'o', '(int)'),
                   K('B3', 'q', '()'), K('D3', 'z', '()'), K('D3', 'o', '(char*)')], got


def test_a4_new_group_reversed_in_segment():
    """A-2（a4.cpp）：D4 : B4 decl[z,o(char*),o(short)] ⇒ [p,q,z,o(short),o(char*)]
    —— 派生类自己的新组内部同样逆序"""
    b4 = compute_slot_order([], [V('p', '()', owner='B4'), V('q', '()', owner='B4')])
    got = SK(compute_slot_order(b4, [V('z', '()', owner='D4'), V('o', '(char*)', owner='D4'),
                                     V('o', '(short)', owner='D4')]))
    assert got == [K('B4', 'p', '()'), K('B4', 'q', '()'), K('D4', 'z', '()'),
                   K('D4', 'o', '(short)'), K('D4', 'o', '(char*)')], got


def test_db_interleaved_group_packs_in_derived_segment():
    """DB : BB decl[z,o(int),y,o(char*)] ⇒ [w@BB, z, o(char*), o(int), y]
    —— 派生本地段与基类同规则：同名组 o 跨 y 打包并逆序（syn_probe2 DB 实测）"""
    bb = compute_slot_order([], [V('w', '()', owner='BB')])
    got = SK(compute_slot_order(bb, [V('z', '()', owner='DB'), V('o', '(int)', owner='DB'),
                                     V('y', '()', owner='DB'), V('o', '(char*)', owner='DB')]))
    assert got == [K('BB', 'w', '()'), K('DB', 'z', '()'), K('DB', 'o', '(char*)'),
                   K('DB', 'o', '(int)'), K('DB', 'y', '()')], got


# ================= 4. 合成槽：落声明位，不参与同名分组 =================

def test_adv3_deleting_dtor_first_decl_singleton_group():
    """adv3：C3 decl[~C3, o() const, o(int)] ⇒ [??_EC3, o(int), o() const]
    —— deleting dtor 落声明位（槽 0），o() const 与 o(int) 同名成组逆序
    （advprobe README adv3 行，实测 ??_EC3@@UAEPAXI@Z / ?o@C3@@UAEXH@Z / ?o@C3@@UBEXXZ）"""
    got = SK(compute_slot_order([], [V('~C3', '()', DT, 'C3'), V('o', '() const', owner='C3'),
                                     V('o', '(int)', owner='C3')]))
    assert got == [K('C3', '~C3', '()', DT), K('C3', 'o', '(int)'),
                   K('C3', 'o', '() const')], got


def test_syn_dtor_mid_group_is_singleton_group_not_pinned_index():
    """合成槽"落声明位"的**精确语义**（syn_probe P1 实测）：
    decl[o()(0), ~P1(1), o(int)(2)] ⇒ [o(int), o(), ??_E]。
    dtor 是**单槽组**，组位=其声明序在各组首现序中的秩 ⇒ 落槽 2，
    **不是**字面声明下标（钉在下标 1 会得 [o(int), ~, o()]，与实测不符）。"""
    got = SK(compute_slot_order([], [V('o', '()', owner='P1'), V('~P1', '()', DT, 'P1'),
                                     V('o', '(int)', owner='P1')]))
    assert got == [K('P1', 'o', '(int)'), K('P1', 'o', '()'),
                   K('P1', '~P1', '()', DT)], got


def test_syn_dtor_mid_group_const_overloads():
    """P2 decl[o() const, ~P2, o(int)] ⇒ [o(int), o() const, ??_E]（syn_probe 实测）"""
    got = SK(compute_slot_order([], [V('o', '() const', owner='P2'), V('~P2', '()', DT, 'P2'),
                                     V('o', '(int)', owner='P2')]))
    assert got == [K('P2', 'o', '(int)'), K('P2', 'o', '() const'),
                   K('P2', '~P2', '()', DT)], got


def test_syn_dtor_declared_before_last_group_member():
    """P2b decl[o(),o(int),~P2b,o(double)] ⇒ [o(double),o(int),o(),??_E]
    —— dtor 后面声明的 o(double) 仍入同名组逆序，跳过 dtor 打包（syn_probe 实测）"""
    got = SK(compute_slot_order([], [V('o', '()', owner='P2b'), V('o', '(int)', owner='P2b'),
                                     V('~P2b', '()', DT, 'P2b'), V('o', '(double)', owner='P2b')]))
    assert got == [K('P2b', 'o', '(double)'), K('P2b', 'o', '(int)'), K('P2b', 'o', '()'),
                   K('P2b', '~P2b', '()', DT)], got


def test_syn_dtor_in_derived_local_segment():
    """D5 : B5 decl[o(),~D5,o(int)] ⇒ [a@B5, o(int), o(), ??_ED5]
    —— 合成槽规则在派生本地段同样成立（syn_probe 实测 ?o@D5@@UAEXH@Z/UAEXXZ/??_ED5）"""
    b5 = compute_slot_order([], [V('a', '()', owner='B5')])
    got = SK(compute_slot_order(b5, [V('o', '()', owner='D5'), V('~D5', '()', DT, 'D5'),
                                     V('o', '(int)', owner='D5')]))
    assert got == [K('B5', 'a', '()'), K('D5', 'o', '(int)'), K('D5', 'o', '()'),
                   K('D5', '~D5', '()', DT)], got


def test_syn_synthetics_never_group_with_each_other():
    """合成槽不参与同名分组 ⇒ 两个合成声明各为单槽组（声明序的组秩），既不合并也不逆序。
    （真实 C++ 每类至多 1 个析构合成槽；本条锁定"不参与同名分组"的纯逻辑。）"""
    a = V('~X', '()', DT, 'X')
    b = V('adj', '()', 'adjustor_static', 'X')
    got = SK(compute_slot_order([], [a, b]))
    assert got == [K('X', '~X', '()', DT), K('X', 'adj', '()', 'adjustor_static')], got


# ================= 5. 打包细节：覆写参与本地段打包后再摘除 =================

def test_override_participates_in_segment_packing_then_excised():
    """DA : BA decl[o(int)覆写(0), z(1), o(char*)(2)] ⇒ [o(int)@DA, o(char*)@DA, z@DA]
    （syn_probe2 DA 实测，本规则的**判别样本**）：
    本地段按**全部**本地声明打包（同名组 o={0,2} 逆序 ⇒ [o(char*),o(int),z]）后，
    再把覆写者摘除原位替换 ⇒ 新增段 [o(char*), z]。
    「只按新增声明打包」会得 [o(int), z, o(char*)] ⇒ 与实测不符（slot1/2 互换）。"""
    ba = compute_slot_order([], [V('o', '(int)', owner='BA')])
    got = SK(compute_slot_order(ba, [V('o', '(int)', owner='DA'), V('z', '()', owner='DA'),
                                     V('o', '(char*)', owner='DA')]))
    assert got == [K('DA', 'o', '(int)'), K('DA', 'o', '(char*)'), K('DA', 'z', '()')], got


def test_d9_mixed_override_and_new_overloads_of_same_name():
    """D9 : B9 decl[o(char*)(0), o(int)覆写(1), o(short)(2)] ⇒ [o(int)@D9, o(short), o(char*)]
    —— 覆写者与新增同名重载同组逆序后摘除（syn_probe2/1 D9 实测 ?o@D9@@UAEXH/F/PAD）"""
    b9 = compute_slot_order([], [V('o', '(int)', owner='B9')])
    got = SK(compute_slot_order(b9, [V('o', '(char*)', owner='D9'), V('o', '(int)', owner='D9'),
                                     V('o', '(short)', owner='D9')]))
    assert got == [K('D9', 'o', '(int)'), K('D9', 'o', '(short)'),
                   K('D9', 'o', '(char*)')], got


def test_d6_group_packs_across_interloper_in_derived_segment():
    """D6 : B6 decl[x,y(int),z,y(double)] ⇒ [a@B6, x, y(double), y(int), z]
    —— 本地段同名组 y 跨 z 打包、组内逆序（syn_probe D6 实测）"""
    b6 = compute_slot_order([], [V('a', '()', owner='B6')])
    got = SK(compute_slot_order(b6, [V('x', '()', owner='D6'), V('y', '(int)', owner='D6'),
                                     V('z', '()', owner='D6'), V('y', '(double)', owner='D6')]))
    assert got == [K('B6', 'a', '()'), K('D6', 'x', '()'), K('D6', 'y', '(double)'),
                   K('D6', 'y', '(int)'), K('D6', 'z', '()')], got


# ================= 6. MI 多视图（abi README #1/#3，vt2.cpp / vt3.cpp） =================

def _hier_vt2():
    return {
        'A': {'bases': [], 'decls': [V('f', '()'), V('g', '(int)')]},
        'B': {'bases': [], 'decls': [V('h', '()'), V('k', '(double)')]},
        'D': {'bases': ['A', 'B'],
              'decls': [V('f', '()'), V('h', '()'), V('m', '()')]},
    }


def test_vt2_mi_new_virtual_appends_only_to_primary_view():
    """vt2 `D : A, B`（abi README #1）：新增虚函数 m **只追加到主表尾**；次表只含 B 的槽。
    A 视图 = [f@D, g@A, m@D]；B 视图 = [h@D, k@B]（实测 ??_7D@@6BA@@@ / ??_7D@@6BB@@@）"""
    views = compute_class_views(_hier_vt2(), 'D')
    assert [(lbl, SK(s)) for lbl, s in views] == [
        ('A', [K('D', 'f', '()'), K('A', 'g', '(int)'), K('D', 'm', '()')]),
        ('B', [K('D', 'h', '()'), K('B', 'k', '(double)')]),
    ], [(lbl, SK(s)) for lbl, s in views]


def test_vt2_mi_secondary_base_override_replaces_in_place():
    """D::h 覆写次基 B::h ⇒ 不生成顺序变化、槽原位指向本体（abi README #2/#1）"""
    views = dict(compute_class_views(_hier_vt2(), 'D'))
    assert SK(views['B'])[0] == K('D', 'h', '()')


def test_vt2_root_class_views():
    """无基类 ⇒ 单视图（Q decl[p()=0,r()] ⇒ [p,r]，vt2.cpp 实测 __purecall）"""
    views = compute_class_views({
        'Q': {'bases': [], 'decls': [V('p', '()'), V('r', '()')]},
    }, 'Q')
    assert [(lbl, SK(s)) for lbl, s in views] == [
        ('Q', [K('Q', 'p', '()'), K('Q', 'r', '()')]),
    ]


def test_vt3_one_decl_replaces_slots_in_both_views():
    """vt3 `D3 : A3, B3`（abi README #3）：一函数服务两个子对象槽 ⇒ 一个声明在**两个视图**
    各原位替换一槽（次视图槽内容是 W7 静态 adjustor，属 Task 2/6；**槽序不变**）。
    A3 视图 = [ff@D3, onlyA@A3]；B3 视图 = [ff@D3, onlyB@B3]"""
    views = compute_class_views({
        'A3': {'bases': [], 'decls': [V('ff', '()'), V('onlyA', '()')]},
        'B3v': {'bases': [], 'decls': [V('ff', '()'), V('onlyB', '()')]},
        'D3v': {'bases': ['A3', 'B3v'], 'decls': [V('ff', '()')]},
    }, 'D3v')
    assert [(lbl, SK(s)) for lbl, s in views] == [
        ('A3', [K('D3v', 'ff', '()'), K('A3', 'onlyA', '()')]),
        ('B3v', [K('D3v', 'ff', '()'), K('B3v', 'onlyB', '()')]),
    ], [(lbl, SK(s)) for lbl, s in views]


def test_virtual_base_rejected_not_silently_wrong():
    """虚继承视图合成不在本任务范围（attack README B-1..B-4：1 声明↔多视图多槽、
    声明落异己视图等缺口）⇒ 明确拒绝，不允许静默给出错误槽序。"""
    try:
        compute_class_views({
            'V': {'bases': [], 'decls': [V('v', '()')]},
            'DV': {'bases': ['V'], 'virtual_bases': ['V'], 'decls': [V('v', '()')]},
        }, 'DV')
    except NotImplementedError:
        pass
    else:
        raise AssertionError('virtual base 应当 NotImplementedError')


# ================= 7. 匹配键（覆写判定） =================

def test_match_key_owner_and_dtor_name_ignored():
    """覆写匹配看 (kind, 参数, 方法 cv)：声明类无关；析构跨类名匹配（~D 覆写 ~B）"""
    assert match_key(V('~B', '()', DT, 'B')) == match_key(V('~D', '()', DT, 'D'))
    assert match_key(V('o', '(int)', owner='B')) == match_key(V('o', '(int)', owner='D'))


def test_method_const_is_part_of_signature():
    """`o() const` 与 `o()` 不同签名（adv3：二者同名成组，槽位不同）"""
    assert match_key(V('o', '() const')) != match_key(V('o', '()'))


def test_top_level_param_const_does_not_prevent_override():
    """顶层参数 const 不区分签名（C++ 规则）：`o(const int)` 覆写 `o(int)`"""
    assert match_key(V('o', '(const int)')) == match_key(V('o', '(int)'))


def test_pointer_params_not_const_flattened():
    """`o(const char*)` ≠ `o(char*)`：指针指向的 const 是签名的一部分，不得抹掉"""
    assert match_key(V('o', '(const char*)')) != match_key(V('o', '(char*)'))


def test_layout_local_segment_empty():
    assert layout_local_segment([]) == []


def test_origin_labels_describe_current_class_only():
    """origin 描述**本类**贡献：跨层传入的 new/override 不泄漏（Task 5 的槽账依赖此契约）。
    DO : O 里 O 的4槽（O 层全是 new）到 DO 层全部回归 inherited，仅覆写槽为 override。"""
    o_slots = compute_slot_order([], [V('o', '(int)', owner='O'), V('o', '(double)', owner='O'),
                                      V('o', '(char*,int)', owner='O'), V('o', '()', owner='O')])
    do = compute_slot_order(o_slots, [V('o', '(double)', owner='DO')])
    assert [e.origin for e in do] == ['inherited', 'inherited', 'override', 'inherited'], \
        [e.origin for e in do]


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
