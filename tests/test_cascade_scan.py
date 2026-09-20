"""只读级联扫描器（Spike）—— 验收 = 两个历史失败必须**改前就能报出** ✓

本机 pytest 在 collect 阶段崩（sys.path 混入 aide 的 pytest dev 构建 ✗）⇒ 自带走 __main__ runner ✓。
"""
import copy, os, sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tools'))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import cascade_scan as cs


def test_uistatic_reports_four_direct_derived():
    """UIStatic 152->248：必须报出 4 个直接派生类（UIStaticCB/EX/Flip/RM ✓）且为 mechanical。"""
    r = cs.scan('UIStatic', 248, cs._load())
    got = sorted(x['class'] for x in r['derived_direct'])
    assert got == ['UIStaticCB', 'UIStaticEX', 'UIStaticFlip', 'UIStaticRM'], got
    assert all(x['state'] == 'mechanical' for x in r['derived_direct']), r['derived_direct']
    # 候选新尺寸 = 旧尺寸 + delta(96) ✓
    d = {x['class']: x['binary_size'] for x in r['derived_direct']}
    assert d['UIStaticFlip'] == 156 and d['UIStaticEX'] == 184


def test_b34_replay_reports_union_and_landmine():
    """B34 回放：给 tagRoleSlot 注入 ctor/dtor（**内存副本**，不落盘）⇒ 必须报 union 引用 + landmine。"""
    structs = cs._load()
    r0 = cs.scan('tagRoleSlot', 896, structs)
    assert r0['union_byvalue_refs'], '必须报出 union 按值引用（PalScript.m_RoleSlotArray ✓）'
    assert r0['union_byvalue_refs'][0]['holder'] == 'PalScript'
    assert r0['union_landmine'] is False, '当前未注入 ⇒ 不应报 landmine'
    s2 = copy.deepcopy(structs)
    s2['tagRoleSlot'].setdefault('methods', {})['0xDEADBEEF'] = {
        'name': 'tagRoleSlot', 'signature': 'void __thiscall tagRoleSlot::tagRoleSlot()'}
    r = cs.scan('tagRoleSlot', 896, s2)
    assert r['union_landmine'] is True, '注入 ctor 后必须报 landmine（B34 成因 ✗）'


def test_scanner_discrimination_disabling_it_must_fail():
    """判别力自检：把"union 扫描"关掉 ⇒ 上面第二条断言必须失败（证明该断言真的在测东西 ✓）。"""
    structs = cs._load()
    orig = cs.scan

    def patched(target, new_size, st):
        out = orig(target, new_size, st)
        out['union_byvalue_refs'] = []      # 模拟"扫描器被关掉"
        out['union_landmine'] = False
        return out

    cs.scan = patched
    try:
        try:
            test_b34_replay_reports_union_and_landmine()
            raised = False
        except AssertionError:
            raised = True
        assert raised, '关掉 union 扫描后，B34 回放断言必须失败 ✗'
    finally:
        cs.scan = orig


if __name__ == '__main__':
    ok = fail = 0
    for nm, fn in list(globals().items()):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)
