#!/usr/bin/env python3
"""[重载正确性判定函数 TDD 2026-11-16] C++ virtual override 签名一致性判定。

规则: 派生虚函数 override 基类虚函数 ⟺ 函数名相同 + 参数类型序列相同 + 返回型相同或协变。
C2555 = 参数一致但返回型不一致。
"""
import sys, os
sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))
from pipeline.sigmodel import override_check

PASS = FAIL = 0
def ok(cond, note):
    global PASS, FAIL
    if cond:
        PASS += 1
    else:
        FAIL += 1
        print('[FAIL] %s' % note)
        if hasattr(cond, 'mismatches'):
            print('  mismatches:', cond.get('mismatches'))

def N(ret, cc, params, varargs=False):
    """构建 SigNode 简写"""
    return {'return': ret, 'cc': cc,
            'params': [{'type': t, 'name': n} for t, n in params],
            'varargs': varargs, 'pending': False}

# ── 一致 ──
ok(override_check(
    N('void', 'thiscall', [('int', 'nVal')]),
    N('void', 'thiscall', [('int', 'nVal')])
)['compatible'], '完全一致→compatible')

ok(override_check(
    N('void', 'thiscall', [('int', 'nVal1')]),
    N('void', 'thiscall', [('int', 'nVal2')])
)['compatible'], '参数名不同→仍compatible(名不参与判等)')

ok(override_check(
    N('void', 'thiscall', [('int', None)]),
    N('void',  'thiscall', [('int', 'nVal')])
)['compatible'], '参数名None vs 有名→compatible')

# ── 返回型不一致 ──
r = override_check(
    N('void', 'thiscall', [('int', None)]),
    N('int',  'thiscall', [('int', None)]))
ok(not r['compatible'] and 'return_type' in str(r.get('mismatches')), 'void vs int→不兼容')

r = override_check(
    N('BOOL', 'thiscall', [('int', None)]),
    N('void', 'thiscall', [('int', None)]))
ok(not r['compatible'], 'BOOL vs void→不兼容')

# ── 参数个数不一致 ──
r = override_check(
    N('void', 'thiscall', [('int', None), ('int', None)]),
    N('void', 'thiscall', [('int', None)]))
ok(not r['compatible'] and 'param_count' in str(r.get('mismatches')), '2参vs1参→不兼容')

# ── 参数类型不一致(同个数) ──
r = override_check(
    N('void', 'thiscall', [('float', None)]),
    N('void', 'thiscall', [('int', None)]))
ok(not r['compatible'] and 'param[0]' in str(r.get('mismatches')), 'float参vs int参→不兼容')

# ── cc不一致 ──
r = override_check(
    N('void', 'thiscall', [('int', None)]),
    N('void', 'cdecl',    [('int', None)]))
ok(not r['compatible'] and 'cc' in str(r.get('mismatches')), 'thiscall vs cdecl→不兼容')

# ── varargs不一致 ──
r = override_check(
    N('void', 'thiscall', [('int', None)], True),
    N('void', 'thiscall', [('int', None)], False))
ok(not r['compatible'] and 'varargs' in str(r.get('mismatches')), 'varargs→不兼容')

# ── 空格归一 ──
ok(override_check(
    {'return': 'void', 'cc': 'thiscall', 'params': [{'type': 'unsigned  int', 'name': None}], 'varargs': False, 'pending': False},
    {'return': 'void', 'cc': 'thiscall', 'params': [{'type': 'unsigned int', 'name': None}], 'varargs': False, 'pending': False}
)['compatible'], '空格差异归一→compatible')

# ── mismatches 结构化输出 ──
r = override_check(
    N('void', 'thiscall', [('int', None)]),
    N('int', 'thiscall', [('float', None)]))
ok(len(r['mismatches']) >= 2, '多错同时报告: %s' % r['mismatches'])

# ── pending节点 → 不判(跳过) ──
r = override_check(
    {'return': None, 'cc': None, 'params': None, 'varargs': False, 'pending': True},
    N('void', 'thiscall', [('int', None)]))
ok(r.get('pending') is True, 'pending节点→跳过不判')

print('\n重载判定: %d pass / %d fail' % (PASS, FAIL))

# ── 指针声明排版归一(void* vs void *) ──
ok(override_check(
    N('void*', 'thiscall', []),
    N('void *', 'thiscall', [])
)['compatible'], 'void* vs void *归一同型')
r = override_check(
    N('int*', 'thiscall', [('char*', None)]),
    N('int *', 'thiscall', [('char *', None)]))
ok(r['compatible'], 'int*/char*排版差异归一')
print('排版归一补测: 通过')
print('总计: %d pass / %d fail' % (PASS, FAIL))
sys.exit(0 if FAIL == 0 else 1)
