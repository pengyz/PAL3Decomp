"""级联计划生成器（正确模型）—— **断言型**测试 ✓

本机 pytest collect 崩（sys.path 混入 aide 的 pytest dev 构建 ✗）⇒ 自带走 __main__ runner ✓。
锚点值来自与独立复核者 audit_v2.py 的**对账**（Δ(SystemUI)=222912=739548−516636 ✓、Δ(UITitle_JDHY)=200544 ✓）。
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tools'))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import cascade_plan as cp


def _S(classes):
    """构造合成语料：classes = {name: (binary_size, {offset: (type, count?)})}"""
    out = {}
    for n, (bs, mem) in classes.items():
        km = {}
        for off, spec in mem.items():
            t, c = (spec if isinstance(spec, tuple) else (spec, None))
            d = {'name': 'm%s' % off, 'type': t}
            if c is not None:
                d['count'] = c
            km[str(off)] = d
        out[n] = {'name': n, 'binary_size': bs, 'known_members': km}
    return out


def test_real_uistatic_plan_anchors():
    """真实语料：60 类 / 1507 ops / 自检 ok；Δ 锚点与复核者脚本一致 ✓。"""
    p = cp.build_plan('UIStatic', 248, cp.cs._load())
    assert not p.get('error'), p.get('error')
    assert p['classes'] == 60, p['classes']
    assert p['total_ops'] == 1507, p['total_ops']
    assert p['self_check']['ok'] is True, p['self_check']
    d = p['delta_of']
    assert d['UIStatic'] == 96
    assert d['SystemUI'] == 222912, d['SystemUI']      # = 739548 − 516636（复核者值 ✓）
    assert d['UITitle_JDHY'] == 200544, d['UITitle_JDHY']
    assert d['UISceneMap'] == 192, d['UISceneMap']      # ★ 与真实间隙 96 冲突 ⇒ 待裁决 ✓


def test_cycle_is_rejected():
    """包含环 ⇒ **拒绝**（返回 error），不得输出无意义计划 ✗。"""
    S = _S({'UIStatic': (152, {}),
            'X': (200, {'0': 'UIStatic', '8': 'Y'}),
            'Y': (200, {'0': 'X'})})
    p = cp.build_plan('UIStatic', 248, S)
    assert p.get('error'), '有环必须拒绝 ✗'
    assert p.get('cycle')


def test_pointer_members_do_not_grow():
    """`UIStatic *` 与 `UIStatic *[4]` ⇒ **不增长** ✓（值语义才增长）。"""
    S = _S({'UIStatic': (152, {}),
            'H': (1000, {'0': 'UIStatic *', '8': 'UIStatic *[4]', '64': 'int'})})
    p = cp.build_plan('UIStatic', 248, S)
    ops = [o for e in p['edits'] for o in e['ops']]
    assert not any(o['kind'] == 'set_size' and o.get('class') == 'H' for o in ops), ops
    assert not any(o['kind'] == 'shift_offset' for o in ops), ops


def test_struct_prefix_is_stripped():
    """`struct UIStatic` 拼写 ⇒ 必须识别为类 ✓（增长 +96）。"""
    S = _S({'UIStatic': (152, {}), 'H': (1000, {'0': 'struct UIStatic', '200': 'int'})})
    p = cp.build_plan('UIStatic', 248, S)
    ops = [o for e in p['edits'] for o in e['ops']]
    sz = [o for o in ops if o['kind'] == 'set_size' and o.get('class') == 'H']
    sh = [o for o in ops if o['kind'] == 'shift_offset']
    assert sz and sz[0]['to'] == 1096, sz          # +96 ✓
    assert sh and sh[0]['to'] == 296, sh           # 200 + 96 ✓


def test_multidim_and_count_multiply():
    """`UIStatic[2][3]` ⇒ 6 元素；带 `count=4` ⇒ 元素数再 ×4 ✓。"""
    S = _S({'UIStatic': (152, {}),
            'H': (2000, {'0': 'UIStatic[2][3]', '912': 'int'}),
            'C': (2000, {'0': ('UIStatic', 4), '608': 'int'})})
    p = cp.build_plan('UIStatic', 248, S)
    sh = {o['key']: o['to'] for e in p['edits'] for o in e['ops'] if o['kind'] == 'shift_offset'}
    assert sh.get('912') == 912 + 6 * 96, sh      # 维度连乘 = 6 ✓
    assert sh.get('608') == 608 + 4 * 96, sh      # count=4 ✓


def test_members_before_embedding_are_not_shifted():
    """内嵌对象**之前**的成员不动 ✓；之后 +Δ ✓。"""
    S = _S({'UIStatic': (152, {}), 'H': (1000, {'0': 'int', '64': 'UIStatic', '300': 'int'})})
    p = cp.build_plan('UIStatic', 248, S)
    sh = {o['key']: o['to'] for e in p['edits'] for o in e['ops'] if o['kind'] == 'shift_offset'}
    assert '0' not in sh, sh                       # 内嵌之前 ⇒ 不动 ✓
    assert '64' not in sh, sh                      # 内嵌自身 ⇒ 不动 ✓
    assert sh.get('300') == 396, sh                # 之后 ⇒ +96 ✓


def test_zero_length_array_does_not_grow():
    """`UIStatic[0]` ⇒ 0 元素 ⇒ 不增长 ✓。"""
    S = _S({'UIStatic': (152, {}), 'H': (1000, {'0': 'UIStatic[0]', '64': 'int'})})
    p = cp.build_plan('UIStatic', 248, S)
    ops = [o for e in p['edits'] for o in e['ops']]
    assert not any(o['kind'] == 'set_size' and o.get('class') == 'H' for o in ops), ops


def test_variant_offset_keys_are_rejected():
    """同 base offset 的 `_N` 变体键 ⇒ **拒绝**（避免重复计数 ✗）。"""
    S = _S({'UIStatic': (152, {}), 'H': (1000, {'0': 'UIStatic', '0_1': 'UIStatic'})})
    p = cp.build_plan('UIStatic', 248, S)
    assert p['rejected'], '变体键必须被拒绝 ✗'


def test_inline_union_value_variant_is_rejected():
    """内联 dict 的**按值变体**含受影响类 ⇒ **拒绝**（不静默 ✗）。"""
    S = {'UIStatic': {'name': 'UIStatic', 'binary_size': 152, 'known_members': {}},
         'H': {'name': 'H', 'binary_size': 1000, 'known_members': {
             '0': {'name': 'u', 'type': {'union': [{'type': 'UIStatic', 'name': 'v'}]}}}}}
    p = cp.build_plan('UIStatic', 248, S)
    assert p['rejected'], '内联按值变体必须被拒绝 ✗'


def test_discrimination_disabling_per_type_delta():
    """判别力自检：把"逐类型 Δ"退化为"单一 Δ" ⇒ 上面的锚点断言**必须失败** ✓。"""
    real = cp.build_plan
    try:
        def patched(target, new_size, structs):
            p = real(target, new_size, structs)
            p['delta_of'] = {k: (96 if k != target else 96) for k in (p.get('delta_of') or {})}
            return p
        cp.build_plan = patched
        raised = False
        try:
            test_real_uistatic_plan_anchors()
        except AssertionError:
            raised = True
        assert raised, '退化后锚点断言必须失败 ✗（否则测试无判别力）'
    finally:
        cp.build_plan = real


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
