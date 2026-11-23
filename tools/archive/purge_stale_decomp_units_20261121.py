#!/usr/bin/env python3
"""[陈旧反编译单元清仓 2026-11-21] 地址已 declaration_only/type=skip 的反编译单元清除。

根因: 导出对体排除地址不再生成新单元, 但历史单元残留磁盘, collect 照常消费
→ 换牌/C8 翻转后旧名单元带假名/包装体流入发射面(RenderTargetNode._ParticleEffect_0
  C2039 / CEffQuake_0 C2065 案)。

清除判据(大小写无关): 单元地址 ∈ {declaration_only} ∪ {type='skip'}
清除 125 个(decl_only 85 + skip 40), 移入 asm/pal3/decomp/_stale_purged_20261121/ 归档。

用法: python3 tools/purge_stale_decomp_units_20261121.py [--dry]
"""
import json
import glob
import os
import shutil
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
D = REPO / 'asm' / 'pal3' / 'decomp'
ARCH = D / '_stale_purged_20261121'

decl, skip = set(), set()
for fp in glob.glob(str(REPO / 'data' / 'annotations' / 'structs' / '*.json')):
    d = json.loads(Path(fp).read_text(encoding='utf-8'))
    for a, m in (d.get('methods') or {}).items():
        k = '0x%08X' % int(a, 16)
        if m.get('declaration_only'):
            decl.add(k)
        if m.get('type') == 'skip':
            skip.add(k)
fns = json.loads((REPO / 'data' / 'annotations' / 'functions.json').read_text(encoding='utf-8'))
for a, v in fns.items():
    if isinstance(v, dict):
        k = '0x%08X' % int(a, 16)
        if v.get('declaration_only'):
            decl.add(k)
        if v.get('type') == 'skip':
            skip.add(k)
sfk = json.loads((REPO / 'data' / 'annotations' / 'skip_functions.json').read_text(encoding='utf-8'))
for a, v in sfk.items():
    if isinstance(v, dict) and v.get('type') == 'skip':
        skip.add('0x%08X' % int(a, 16))

stale = []
for f in glob.glob(str(D / '*.json')):
    base = os.path.basename(f)[:-5]
    try:
        a = '0x%08X' % int(base.rsplit('_', 1)[-1], 16)
    except Exception:
        continue
    why = 'decl_only' if a in decl else ('skip' if a in skip else None)
    if why:
        stale.append((f, a, why))

if not DRY:
    ARCH.mkdir(parents=True, exist_ok=True)
for f, a, why in stale:
    print(' purge', os.path.basename(f), '(%s)' % why)
    if not DRY:
        shutil.move(f, str(ARCH / os.path.basename(f)))

print('\n清除 %d (decl_only %d + skip %d) dry=%s' % (
    len(stale),
    sum(1 for _, _, w in stale if w == 'decl_only'),
    sum(1 for _, _, w in stale if w == 'skip'), DRY))
