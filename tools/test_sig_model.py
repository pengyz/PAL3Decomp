#!/usr/bin/env python3
"""[S1用例表 2026-11-16] sigmodel 行为钉死 — 全部用例源自实战伤痕。"""
import sys, os
sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))
from pipeline.sigmodel import parse_signature, render, render_decl, validate, params_equal, returns_absent, c2555_conflict

CASES = [
    # (输入, 期望节点关键字段, 说明)
    ('void __thiscall()', {'return': 'void', 'cc': 'thiscall', 'nparams': 0}, '基础void thiscall'),
    ('int __thiscall(int nMsg, unsigned int wParam, long lParam)',
     {'return': 'int', 'cc': 'thiscall', 'nparams': 3,
      'p0': ('int', 'nMsg'), 'p1': ('unsigned int', 'wParam'), 'p2': ('long', 'lParam')},
     'OnMessage真形: unsigned int双词类型保真'),
    ('void __thiscall UITabCtrl::Render()',
     {'return': 'void', 'cc': 'thiscall', 'nparams': 0}, '限定名头[战痕: UITabCtrl解析bug]'),
    ('__thiscall void()', {'return': 'void', 'cc': 'thiscall', 'nparams': 0}, 'cc序畸形[战痕: CCBStage]'),
    ('gbVFileSys *__thiscall()', {'return': 'gbVFileSys *', 'cc': 'thiscall', 'nparams': 0}, '指针返回[战痕: C6]'),
    ('char __thiscall(tagEffObjType *)', {'return': 'char', 'nparams': 1, 'p0': ('tagEffObjType *', None)}, '无名指针参'),
    ('unsigned __int8 __thiscall(int, int, int, int)', {'return': 'unsigned __int8', 'nparams': 4}, 'MSVC双词返回'),
    ('virtual void __thiscall(CEffObj *this, int nVal1)',
     {'return': 'void', 'cc': 'thiscall', 'nparams': 1, 'p0': ('int', 'nVal1')}, 'decomp形: virtual前缀+this参剥除'),
    ('virtual int __thiscall(UIScene *this)', {'return': 'int', 'cc': 'thiscall', 'nparams': 0}, 'decomp形: 仅this参'),
    ('void __thiscall(int nVal, ...)', {'return': 'void', 'varargs': True, 'nparams': 1}, '可变参'),
    ('int __thiscall(int, int, int)', {'return': 'int', 'nparams': 3, 'p0': ('int', None)}, '全无名参'),
    ('BOOL __thiscall(int nVal, int nVal2)', {'return': 'BOOL', 'nparams': 2, 'p0': ('int', 'nVal')}, 'BOOL返回'),
]
GARBAGE = [None, '', 'no parens', '()', '   ']

def check(node, expect):
    errs = []
    for k, v in expect.items():
        if k == 'nparams':
            if len(node.get('params') or []) != v: errs.append('nparams≠%d' % v)
        elif k == 'p0':
            p0 = (node.get('params') or [{}])[0]
            if (p0.get('type'), p0.get('name')) != v: errs.append('p0≠%r' % (v,))
        elif k == 'p1':
            p1 = (node.get('params') or [{}, {}])[1]
            if (p1.get('type'), p1.get('name')) != v: errs.append('p1≠%r' % (v,))
        elif k == 'p2':
            p2 = (node.get('params') or [{}, {}, {}])[2]
            if (p2.get('type'), p2.get('name')) != v: errs.append('p2≠%r' % (v,))
        elif node.get(k) != v:
            errs.append('%s=%r≠%r' % (k, node.get(k), v))
    return errs

def main():
    passed, failed = 0, 0
    for s, expect, note in CASES:
        node = parse_signature(s)
        if node is None:
            print('[FAIL] %s — parse返回None' % note); failed += 1; continue
        errs = check(node, expect) if isinstance(expect, dict) else []
        # 关键字段子集校验
        for k in ('return', 'cc', 'varargs'):
            if k in expect and node.get(k) != expect[k] and k not in str(errs):
                if not any(k in e for e in errs): errs.append('%s=%r≠%r' % (k, node.get(k), expect[k]))
        if errs:
            print('[FAIL] %s: %s → %s' % (note, s, errs)); failed += 1
        else:
            passed += 1
    for g in GARBAGE:
        if parse_signature(g) is not None:
            print('[FAIL] 垃圾输入未拒: %r' % (g,)); failed += 1
        else:
            passed += 1
    # 幂等: parse→render→parse
    for s, expect, note in CASES[:6]:
        n1 = parse_signature(s)
        r = render(n1)
        n2 = parse_signature(r)
        if n1 != n2:
            print('[FAIL] 幂等 %s: %r vs %r' % (note, n1, n2)); failed += 1
        else:
            passed += 1
    # C2555判据(可观测契约)
    a = parse_signature('void __thiscall(int, int, int)')
    b = parse_signature('int __thiscall(int, int, int)')
    c = parse_signature('void __thiscall()')
    dd = parse_signature('int __thiscall(float)')
    assert c2555_conflict(a, b) is True, 'void/int(int,int,int)应判冲突'
    assert c2555_conflict(c, dd) is False, '参数不同=隐藏合法不判'
    assert c2555_conflict(a, a) is False, '相同不判'
    passed += 3
    # validate
    assert validate({'return': None, 'cc': 'wat', 'params': []}) and 'return缺失' in str(validate({'return': None, 'cc': 'wat', 'params': []}))
    passed += 1
    print('\n%d pass / %d fail' % (passed, failed))
    return 0 if failed == 0 else 1

if __name__ == '__main__':
    sys.exit(main())
