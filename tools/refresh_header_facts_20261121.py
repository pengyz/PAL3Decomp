#!/usr/bin/env python3
"""[S0③ header_facts 刷新 2026-11-21] 缓存陈旧修复——纯目录扫描物化, 不依赖 IDB 进程。

根因(复核D13+本日实证): _write_header_facts_cache() 排在 export_full main() 之后,
但 [S1-DIAG] main() end 从未出现在日志(main 被后续流程终止) ⇒ 缓存自 2026-11-09
起冻结(80 类 vs fresh 27 类, 双向差 65/13)——emit_headers 的 vptr 注入分支运行在
过期事实上。

修: 缓存事实 = 纯 decomp 目录扫描(零 IDA 依赖) ⇒ 本工具在普通进程调
emit_headers 的 *_scan_impl + save_header_facts 直接物化。与 export 内调用逐字段
等值(同一扫描函数), 差异仅进程宿主。

用法: python3 tools/refresh_header_facts_20261121.py [--diff-only]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO))                # pipeline 包根
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))

DIFF_ONLY = '--diff-only' in sys.argv

import emit_headers as eh

# IDA 进程内的调用约定: 模块级累加器先清零(见 export_full._write_header_facts_cache)
eh._scalar_dtor_classes = set()
eh._underscore_aliases = {}
facts = {
    'scalar_dtor_classes': set(eh._get_scalar_dtor_classes_scan_impl()),
    'underscore_aliases': dict(eh._get_underscore_aliases_scan_impl()),
    'forced_global_names': set(eh._referenced_identifiers()),
    'vptr_inject_classes': set(eh._get_scalar_dtor_classes_scan_impl()),
}

old_p = REPO / 'data' / 'status' / '_decomp_derived_header_facts.json'
old = json.loads(old_p.read_text(encoding='utf-8')) if old_p.exists() else {}

for key in ('scalar_dtor_classes', 'vptr_inject_classes'):
    o = set(old.get(key, []))
    n = facts[key]
    gained, lost = sorted(n - o), sorted(o - n)
    print('%s: %d → %d (+%d/-%d)' % (key, len(o), len(n), len(gained), len(lost)))
    if gained[:10]:
        print('  +:', ', '.join(gained[:10]))
    if lost[:10]:
        print('  -:', ', '.join(lost[:10]))
oa = set(old.get('underscore_aliases', {}))
na = set(facts['underscore_aliases'])
print('underscore_aliases: %d → %d (+%d/-%d)' % (len(oa), len(na), len(na - oa), len(oa - na)))
of = old.get('forced_global_names', [])
nf = facts['forced_global_names']
print('forced_global_names: %d → %d (+%d/-%d)' % (
    len(of), len(nf), len(set(nf) - set(of)), len(set(of) - set(nf))))

if DIFF_ONLY:
    print('[diff-only] 未写盘')
    sys.exit(0)

eh.save_header_facts(facts)
print('\n缓存已刷新 →', eh._HEADER_FACTS_PATH.name)
