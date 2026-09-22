"""`tools/audit_attribution_evidence.py` 的测试 —— **先写测试**（TDD）。

本工具用的是**可证**的归属证据（不同于实验性的"成员集合唯一相容性"）：
1. **vtable 槽位**：函数出现在类 C 的 vtable 里 ⇒ 槽的 `from` 给出**声明/继承来源类** ✓（无 `from` ⇒ 归 C ✓）
2. **祖先关系**：方法当前归 D，而证据类 B 是 D 的**祖先** ⇒ 相容 ✓；**无祖先关系** ⇒ `contradiction` ✓
3. **ctor/dtor 的 vptr 存储**：函数体内 `mov [this], <C 的 vtable>` ⇒ 该函数属于 C ✓

结论四态：`consistent` · `contradiction` · `no-evidence` · `unknown-target`（vptr 目标无法对应到类）

运行：`python3 tests/test_audit_attribution_evidence.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

import audit_attribution_evidence as E  # noqa: E402


def _ida():
    """合成 ida_structs：`Derived` 继承 `Base`；两者各有 vtable ✓"""
    return {
        'Base': {'bases': [], 'vtables': [
            {'addr': '0x600000', 'base': 'Base',
             'slots': [{'addr': '0x1000', 'from': None}, {'addr': '0x1010', 'from': None}]}]},
        'Derived': {'bases': ['Base'], 'vtables': [
            {'addr': '0x600010', 'base': 'Base',
             'slots': [{'addr': '0x1000', 'from': 'Base'}, {'addr': '0x1020', 'from': None}]}]},
        'Other': {'bases': [], 'vtables': [
            {'addr': '0x600020', 'base': 'Other', 'slots': [{'addr': '0x2000', 'from': None}]}]},
        'NoVt': {'bases': []},
    }


# ---------------- ① vtable 槽位 → 函数归属证据 ----------------

def test_vtable_evidence_uses_from_when_present_else_owner():
    ev = E.vtable_evidence(_ida())
    # ⚠️ 0x1000 同时出现在 Base 与 Derived 的 vtable 里（Derived 的槽 from=Base）
    # ⇒ **两条主张都要保留** ✓（与 test_vtable_evidence_keeps_multiple_claims 同一契约）
    assert sorted(ev[0x1000]) == [('Base', 'Base'), ('Derived', 'Base')], ev.get(0x1000)
    assert ev[0x1020] == [('Derived', 'Derived')], ev.get(0x1020)  # 无 from ⇒ 归 owner ✓
    assert ev[0x2000] == [('Other', 'Other')], ev.get(0x2000)


def test_vtable_evidence_keeps_multiple_claims():
    """同一函数出现在多个类的 vtable 里 ⇒ **多条**证据都要保留（不得只留一条 ✗）"""
    ida = _ida()
    ida['Third'] = {'bases': [], 'vtables': [
        {'addr': '0x600030', 'base': 'Third', 'slots': [{'addr': '0x2000', 'from': None}]}]}
    ev = E.vtable_evidence(ida)
    assert sorted(c for c, _ in ev[0x2000]) == ['Other', 'Third'], ev[0x2000]


# ---------------- ② 祖先关系 ----------------

def test_ancestors_transitive():
    ida = _ida()
    assert E.ancestors('Derived', ida) == {'Derived', 'Base'}
    assert E.ancestors('Other', ida) == {'Other'}


def test_ancestors_tolerates_missing_and_unknown():
    assert E.ancestors('Nope', _ida()) == {'Nope'}


# ---------------- ③ 对账四态 ----------------

def test_reconcile_consistent_when_current_is_descendant_of_evidence():
    """当前归 `Derived`，证据类 `Base` 是其祖先 ⇒ 相容 ✓（vtables 里继承槽的正常情形）"""
    ida = _ida()
    assert E.reconcile('0x1000', 'Derived', ida)[0] == 'consistent'


def test_reconcile_contradiction_when_unrelated():
    """当前归 `Other`，而证据类 `Base` 与其无祖先关系 ⇒ **contradiction** ✓"""
    ida = _ida()
    v, detail = E.reconcile('0x1000', 'Other', ida)
    assert v == 'contradiction' and 'Base' in detail, (v, detail)


def test_reconcile_no_evidence_without_slot():
    assert E.reconcile('0x9999', 'Base', _ida())[0] == 'no-evidence'


# ---------------- ④ ctor/dtor 的 vptr 存储 ----------------

def _l(addr, ins):
    return {'addr': addr, 'instruction': ins}


def test_ctor_vptr_store_detected():
    """`mov esi,ecx` ⇒ esi≡this；`mov dword ptr [esi], offset off_56F9B4` ⇒ ctor 存 vtable ✓"""
    lines = [_l('0x1000', 'push esi'), _l('0x1001', 'mov esi, ecx'),
             _l('0x1003', 'mov dword ptr [esi], offset off_56F9B4')]
    assert E.vptr_stores(lines) == {'off_56F9B4'}, E.vptr_stores(lines)


def test_ctor_vptr_store_ignores_non_this_base():
    """`[eax]` 而 eax **不是** this ⇒ 不得计入 ✗"""
    lines = [_l('0x2000', 'mov eax, [ecx+4]'), _l('0x2003', 'mov dword ptr [eax], offset off_111111')]
    assert E.vptr_stores(lines) == set()


def test_ctor_vptr_store_ignores_plain_field_store():
    """往 `[this+off]` 存普通值不是 vptr 存储 ⇒ 不计 ✓"""
    lines = [_l('0x3000', 'mov esi, ecx'), _l('0x3002', 'mov dword ptr [esi+1Ch], 0')]
    assert E.vptr_stores(lines) == set()


# ---------------- ⑤ vtable 地址 → 类 ----------------

def test_vtable_addr_to_class_index():
    idx = E.vtable_addr_to_class(_ida())
    assert idx['0x600010'] == 'Derived' and idx['0x600000'] == 'Base', idx


# ---------------- ⑥ `bases` 真实形状回归（dict 列表）----------------
# 2026-09-22 实测：IDB 导出的 `bases` 是 **dict 列表**（`[{'name':'UIWnd','offset':0}]`），
# 而 `ancestors()` 原先只认字符串 ✗ ⇒ **祖先集恒为空** ⇒ 对账退化成 `src == current` ✗
def test_ancestors_accepts_idb_dict_form_bases():
    ida = {'D': {'bases': [{'name': 'B', 'offset': 0}, {'name': 'C', 'offset': 64}]},
           'B': {'bases': []}, 'C': {'bases': []}}
    assert E.ancestors('D', ida) == {'D', 'B', 'C'}


def test_ancestors_mixed_string_and_dict_forms():
    ida = {'D': {'bases': ['B', {'name': 'C', 'offset': 4}]}, 'B': {'bases': []}, 'C': {'bases': []}}
    assert E.ancestors('D', ida) == {'D', 'B', 'C'}


# ---------------- ⑦ owner 侧规则（可区分用例）----------------
def test_owner_side_consistent_when_current_is_owner():
    assert E.reconcile('0x1020', 'Derived', _ida())[0] == 'consistent'


def test_owner_side_consistent_when_current_is_owner_ancestor():
    """owner=Derived、current=Base（owner 的祖先）⇒ consistent（实现来自基类 ✓）"""
    assert E.reconcile('0x1000', 'Base', _ida())[0] == 'consistent'


def test_owner_side_contradiction_for_unrelated_class():
    """owner=Base、current=Other（无祖先关系）⇒ contradiction ✓"""
    v, d = E.reconcile('0x1010', 'Other', _ida())
    assert v == 'contradiction' and 'Base' in d, (v, d)


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