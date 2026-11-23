#!/usr/bin/env python3
"""[vtbl 槽型传播审计 2026-11-21] 全 vtbl 槽 sig 解析差分——FP 伪造类型族根因量化。

背景: hexrays 对 vtbl 成员函数指针型引用渲染间接调用; 槽 sig 解析失败回退
`int (*name)();` 泛型成员 ⇒ hexrays 无真型可用 ⇒ 自造伪型(CCBUI:5302 案
`(int ( **)(_BYTE *, char *, ...))` 用法推断形)⇒C2664/C2440 ×65 族。

审计口径(与 apply [5b]/resolve_vtable_slots 同源):
  槽址 → 本类 methods → functions.json → sig_model 渲染
  分档: OK(有sig) / EMPTY(sig_model缺或渲染空) / NOENTRY(址无条目任何层)

用法: python3 tools/audit_vtbl_slot_types_20261121.py [--json OUT]
"""
import json
import os
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
S = REPO / 'data' / 'annotations'

sys.path.insert(0, str(REPO / 'pipeline'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))

from sigmodel import node_of, render  # noqa: E402


def sig_str_of(m):
    sm = m.get('sig_model') or {}
    n = node_of(m)
    if n:
        return render(n)
    return ''


def main():
    structs = {}
    for fp in sorted((S / 'structs').glob('*.json')):
        try:
            d = json.loads(fp.read_text(encoding='utf-8'))
        except Exception:
            continue
        name = d.get('name') or fp.stem
        structs[name] = d
    # functions.json 兜底层
    funcs = {}
    try:
        funcs = json.loads((S / 'functions.json').read_text(encoding='utf-8'))
    except Exception:
        pass

    # [祖先兜底 20261121] 与 resolve_vtable_slots 双修同链——继承槽址查全类索引
    idx = {}
    for cls0, d0 in structs.items():
        for a0, m0 in (d0.get('methods') or {}).items():
            idx.setdefault(a0, (cls0, m0))
    ok, empty, noentry, dup = [], [], [], []
    for cls, d in sorted(structs.items()):
        for vt in (d.get('vtables') or []):
            vt_addr = vt.get('addr')
            for i, s in enumerate(vt.get('slots') or []):
                sa = s.get('addr')
                if not sa:
                    continue
                m = (d.get('methods') or {}).get(sa)
                if m is None:
                    m = funcs.get(sa)
                if m is None and sa in idx:
                    m = idx[sa][1]
                if m is None:
                    noentry.append((cls, vt_addr, i, sa, s.get('name')))
                    continue
                sig = sig_str_of(m)
                if sig:
                    ok.append((cls, vt_addr, i, sa, m.get('name')))
                else:
                    empty.append((cls, vt_addr, i, sa, m.get('name'),
                                  (m.get('sig_model') or {}).get('pending')))

    print('== vtbl 槽型传播审计 ==')
    print('OK=%d EMPTY=%d NOENTRY=%d' % (len(ok), len(empty), len(noentry)))
    if empty:
        print('\n-- EMPTY 槽(sig_model 缺/渲染空) %d:' % len(empty))
        for cls, vt, i, sa, nm, pend in empty:
            print('  %-14s %s slot%d %s %-22s pending=%s'
                  % (cls, vt, i, sa, nm, pend))
    if noentry:
        print('\n-- NOENTRY 槽(址无条目) %d:' % len(noentry))
        for cls, vt, i, sa, nm in noentry[:40]:
            print('  %-14s %s slot%d %s %s' % (cls, vt, i, sa, nm))
        if len(noentry) > 40:
            print('  ... 共 %d' % len(noentry))
    out = {'ok': len(ok), 'empty': empty, 'noentry': noentry}
    if '--json' in sys.argv:
        outp = S / 'archive' / 'vtbl_slot_type_audit_20261121.json'
        outp.write_text(json.dumps(out, ensure_ascii=False, indent=1),
                        encoding='utf-8')
        print('归档 ->', outp.name)


if __name__ == '__main__':
    main()
