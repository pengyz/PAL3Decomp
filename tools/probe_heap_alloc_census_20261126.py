#!/usr/bin/env python3
"""probe_heap_alloc_census_20261126.py — 全二进制大堆分配普查(编译器 sizeof 金表)。

扫全部函数的 ??2@YAPAXI@Z(operator new) 调用点, 回溯 push 尺寸字面量,
前向找 ctor 调用与存储目标 —— 产出大模块家族表 {size, ctor, caller, store}。
判据: size ≥ 0x4000(16KB) 的大对象分配。
用途: 孪生案重建①——堆相机类真尺寸 + 全项目注解 binary_size 对账。
"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_heap_alloc_census_20261126.json'
MIN_SIZE = 0x4000

allocs = []
nfun = 0
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    nfun += 1
    cn = idc.get_func_name(f.start_ea)
    lines = []
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 6000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        lines.append((hex(cur), t))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    for i, (a, t) in enumerate(lines):
        if 'call' not in t or '??2@YAPAXI@Z' not in t:
            continue
        size = None
        for j in range(i - 1, max(i - 4, 0), -1):
            m = re.match(r'^push\s+([0-9A-Fa-f]+)h', lines[j][1])
            if m:
                size = int(m.group(1), 16)
                break
        if size is None or size < MIN_SIZE:
            continue
        ctor, store = None, None
        for j in range(i + 1, min(i + 14, len(lines))):
            tt = lines[j][1]
            cm = re.match(r'^call\s+(\S+)', tt)
            if cm and '??2@' not in cm.group(1) and ctor is None:
                ctor = cm.group(1)
            sm = re.search(r'mov\s+\[(e[a-z]{2})\+([0-9A-Fa-f]+)h\],\s*eax', tt)
            if sm:
                store = '%s+0x%s' % (sm.group(1), sm.group(2))
                break
        allocs.append({'size': size, 'ctor': ctor, 'store': store,
                       'caller': cn, 'site': a})

allocs.sort(key=lambda x: -x['size'])
# 按尺寸聚合(同类多次分配)
bysize = collections.Counter(a['size'] for a in allocs)
report = {'n_functions': nfun, 'n_allocs': len(allocs), 'allocs': allocs[:400],
          'by_size_top': [(hex(k), v) for k, v in bysize.most_common(40)]}
json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
print('函数 %d | 大分配(≥0x4000) %d 笔 | 唯一尺寸 %d' % (nfun, len(allocs), len(bysize)))
print('== 尺寸 top30 ==')
for sz, cnt in bysize.most_common(30):
    rows = [a for a in allocs if a['size'] == sz]
    ctors = sorted(set((a['ctor'] or '?')[:44] for a in rows))
    print('  0x%-7x (%7d) x%-2d %s' % (sz, sz, cnt, ctors[:2]))
idapro.close_database(False)
