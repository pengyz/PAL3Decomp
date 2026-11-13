#!/usr/bin/env python3
"""[归属审计普查 2026-11-13] 全树函数归属系统性排查(用户指令: 没报错≠归属正确)。

三类铁证(批量归属战役双实证):
  E1 ecx-leak:   `Type vN; // ecx` 声明后未赋值即用 ⇒ IDB 型非 thiscall,
                 this 被 cdecl 渲染吞掉(成员函数错型/错归属的第一现场)
  E2 vt-dispatch: (**vN)(...) 虚表派发形态(全局函数不可能访问 vtable)
  E3 leaked-stack: `Type aX; // [ebp+M]` M>0 且被用 ⇒ 栈参泄漏成局部
                   (thiscall 第2+参被 cdecl 渲染吞掉)

交叉对账: 函数当前归属(定义行) vs 证据。
  free_functions.cpp 内含任一铁证 ⇒ SUSPECT-free(应归属成员)
  类单元内含 E1/E3 ⇒ SUSPECT-type(归属对但 IDB 型未落 thiscall)
产出: data/status/attribution_census_20261113.json + 控制台摘要
只读审计, 零改动。
"""
import json
import os
import re
import collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, 'pal3', 'src')

DEF_RE = re.compile(r'^\s*(?:static\s+)?([\w: ]+\**)\s*([\w:~]+)\(([^;]*)\)\s*$')
ECX_DECL_RE = re.compile(r'^\s*(?:int|unsigned int) (\w+); // ecx')
STACK_LEAK_RE = re.compile(r'^\s*([\w ]+\**)\s*(\w+); // \[esp\+0x[0-9a-f]+\] \[ebp\+0x([0-9a-f]+)\]')
VT_DISPATCH_RE = re.compile(r'\(\*\*\s*\w+\)\s*\(')


def scan_file(path, rel):
    ls = open(path, encoding='utf-8', errors='ignore').read().split('\n')
    funcs = []
    _CTRL = ('if', 'for', 'while', 'switch', 'return', 'else', 'do',
             'LOBYTE', 'HIBYTE', 'LOWORD', 'HIWORD', 'LODWORD', 'HIDWORD')
    for i, l in enumerate(ls, 1):
        if l.strip().startswith('//'):
            continue
        if not l.rstrip().endswith(')') or '=' in l.split('(')[0]:
            continue
        m = re.match(r'^\s*(?:static\s+)?([A-Za-z][\w: ]*?(?:[ \*]|::))\s*([A-Za-z_]\w*)\(([^;]*)\)\s*$', l)
        if not m:
            continue
        nm = m.group(2)
        if nm in _CTRL or nm.startswith('_'):
            continue
        # 返回类型必须含类型词(排掉 'while ( x )' 形)
        ret = m.group(1).strip()
        if not ret or ret.split()[0] in _CTRL:
            continue
        funcs.append((i, nm, m.group(3)))
    out = []
    for idx, (i, name, params) in enumerate(funcs):
        end = funcs[idx + 1][0] - 1 if idx + 1 < len(funcs) else len(ls)
        body = ls[i:end]
        ecx_var = None
        ecx_used = False
        leaked = []
        vt = 0
        for l in body:
            if ecx_var is None:
                m = ECX_DECL_RE.match(l)
                if m:
                    ecx_var = m.group(1)
                    continue
            if STACK_LEAK_RE.match(l):
                mm = STACK_LEAK_RE.match(l)
                if int(mm.group(3), 16) > 0:
                    leaked.append((mm.group(1).strip(), mm.group(2)))
            vt += len(VT_DISPATCH_RE.findall(l))
            if ecx_var and not ecx_used:
                if re.search(r'\b%s\b' % ecx_var, l) and '=' in l and '// ecx' not in l:
                    ecx_used = True
        # 归属
        is_free_unit = 'free_functions' in rel
        if '::' in name:
            attr = name.split('::')[0]
        elif is_free_unit:
            attr = '(free)'
        else:
            attr = os.path.basename(rel)[:-4]
        verdict = 'clean'
        if is_free_unit and (ecx_used or vt >= 1 or leaked):
            verdict = 'SUSPECT-free'
        elif not is_free_unit and (ecx_used or leaked):
            verdict = 'SUSPECT-type'
        out.append({
            'file': rel, 'line': i, 'name': name, 'attr': attr,
            'ecx_leak': ecx_used, 'vt_dispatch': vt, 'leaked_params': leaked,
            'verdict': verdict,
        })
    return out


def main():
    all_f = []
    for root, dirs, files in os.walk(SRC):
        for f in files:
            if not f.endswith('.cpp'):
                continue
            p = os.path.join(root, f)
            rel = os.path.relpath(p, SRC)
            all_f.extend(scan_file(p, rel))

    total = len(all_f)
    by_verdict = collections.Counter(f['verdict'] for f in all_f)
    suspects_free = [f for f in all_f if f['verdict'] == 'SUSPECT-free']
    suspects_type = [f for f in all_f if f['verdict'] == 'SUSPECT-type']

    print('全树函数: %d' % total)
    print('判定: clean=%d  SUSPECT-free=%d  SUSPECT-type=%d' % (
        by_verdict.get('clean', 0), by_verdict.get('SUSPECT-free', 0),
        by_verdict.get('SUSPECT-type', 0)))
    print('\n== SUSPECT-free 错归属候选(按类前缀聚类):')
    pref = collections.Counter()
    for f in sorted(suspects_free, key=lambda x: -x['vt_dispatch']):
        m = re.match(r'([A-Za-z]+?)_', f['name'])
        pref[m.group(1) if m else f['name'][:8]] += 1
    for c, n in pref.most_common(15):
        print('  %-18s %d' % (c, n))
    print('\nSUSPECT-free 明细(前25):')
    for f in sorted(suspects_free, key=lambda x: -x['vt_dispatch'])[:25]:
        print('  %-30s %-24s vt=%-2d ecx=%s leak=%d' % (
            f['name'][:30], f['file'], f['vt_dispatch'],
            'Y' if f['ecx_leak'] else '-', len(f['leaked_params'])))
    print('\n== SUSPECT-type(归属对但IDB型缺thiscall) 前15:')
    for f in sorted(suspects_type, key=lambda x: -(x['vt_dispatch'] + len(x['leaked_params'])))[:15]:
        print('  %-30s %-22s vt=%-2d ecx=%s leak=%d' % (
            f['name'][:30], f['file'], f['vt_dispatch'],
            'Y' if f['ecx_leak'] else '-', len(f['leaked_params'])))

    out_path = os.path.join(ROOT, 'data', 'status', 'attribution_census_20261113.json')
    json.dump({'total': total, 'verdicts': dict(by_verdict), 'functions': all_f},
              open(out_path, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('\n产出: %s' % out_path)


if __name__ == '__main__':
    main()
