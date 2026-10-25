#!/usr/bin/env python3
"""近失 Top 字节差分析（一次性，2026-10-25）：n_diff≤2 的 6 个函数逐字节解剖。"""
import json
import os
import sys
import hashlib
from pathlib import Path

REPO = Path('.').resolve()
sys.path.insert(0, str(REPO / 'tools'))
sys.path.insert(0, str(REPO / 'pipeline'))

import gbengine_compare as gc   # noqa: E402
import probe_compile as pc      # noqa: E402
from compare_pal3 import exe_text_image  # noqa: E402

dd4 = json.load(open('data/status/s4_diff_detail.json', encoding='utf-8'))
nm = json.load(open('data/status/_near_miss_20261025.json', encoding='utf-8'))
targets = [r for r in nm['near_miss'] if r['n_diff'] <= 2]
full = {}
for u, fns in dd4['units'].items():
    for f in fns:
        full[f.get('va')] = (u, f)   # va 唯一
image_base, text, text_rva, text_raw = exe_text_image()
print('image_base=0x%X text_rva=0x%X' % (image_base, text_rva))

os.makedirs(pc.OBJ_DIR, exist_ok=True)
for r in targets:
    va = int(r['va'], 16)
    unit, f = full.get(r['va'], (None, None))
    if unit is None:
        print('unit 未回填:', r['name'])
        continue
    print()
    print('==== %s | %s | va=0x%X size=%d diffs=%s' % (r['name'], unit, va, f['size'], f['diffs']))
    off = va - image_base - text_rva
    ob = text[off:off + f['size']]
    print('  原版:', ob.hex(' '))
    obj = os.path.join(pc.OBJ_DIR, 's4_%s.obj' % hashlib.md5(unit.encode('utf-8')).hexdigest()[:8])
    if not os.path.exists(obj):
        S4_FLAGS = ['/nologo', '/TP', '/c', '/W3', '/O2', '/Ob2', '/Oi', '/Ot', '/Oy', '/GF', '/Gy', '/GX', '/GR', '/MT', '/Gd']
        pc.run_cl(['/Fo' + pc.wpath(obj), pc.wpath(str(REPO / unit))]
                  + ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS] + S4_FLAGS, timeout=180)
    if not os.path.exists(obj):
        print('  COMPILE-FAIL')
        continue
    funcs = gc.parse_coff_obj(obj)
    sym = funcs.get(r['symbol'])
    if sym is None:
        print('  符号未找到:', r['symbol'][:50])
        continue
    cb = sym.get('bytes') or b''
    print('  编译:', cb.hex(' '))
    for o in f['diffs']:
        o = int(o)
        print('  @%-3d 原=%s 编=%s' % (o,
            ob[o:o+1].hex() if o < len(ob) else '-',
            cb[o:o+1].hex() if o < len(cb) else '-'))
