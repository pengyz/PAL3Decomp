#!/usr/bin/env python3
"""[dtor 载体完备性审计 2026-11-21] 全量 dtor 注册符号 × S4 匹配态交叉审计。

方法论（L1恢复战役提炼，详见 docs/knowledge/methodology_dtor_governance_20261121.md）:
  载体律: 每个注册表 dtor 符号(??1/??_G)必须有编译载体。
    ??_G 载体 = virtual ~Cls() 头声明(删除式条目供给) + 类内 dtor 定义 → MSVC 合成。
    删除式 wrapper 体从不发射(collect backtick→_scalar_dtor 泛化跳过)，非载体。
  证据律: S4 100.0% 字节匹配可证伪"体不可信/编译器包装"理论注册。

审计旗标:
  F1 曾L1丢失: 03:17 基线 match_L1 → 当前非 match_L1(无行/部分)
  F2 双形全压制: 删除式+完全形都 type=skip/decl_only → 类级 dtor 符号双丢
  F3 删除式唯一形态被压制: 类只有删除式注册且被压制 → 无任何 dtor 载体
  F4 双形同发: 两形态都未压制 → C2084 风险(实测 collect 泛化跳过天然保护, 0例)
  F5 头声明 virtual 缺失: 头有 ~Cls 但无 virtual → ??_G 不合成(ParticleEffect 案)

用法: python3 tools/audit_dtor_carriers_20261121.py [--cur <s4_baseline>] [--old <0317基线>]
"""
import json
import glob
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

REPO = Path(__file__).parent.parent
CUR = REPO / 'data' / 'status' / 's4_baseline.json'
OLD = Path('/tmp/s4_base_backup.json')  # 03:17 参考基线(临时通道)
ARCH = REPO / 'asm' / 'pal3' / 'decomp' / '_stale_purged_20261121'


def norm(a):
    try:
        return '0x%08X' % int(a, 16)
    except (ValueError, TypeError):
        return a


def load_rows(p):
    if not p.exists():
        return {}
    return {x['symbol']: x for x in json.load(open(p))['rows']}


cur, old = load_rows(CUR), load_rows(OLD)

# 单元在场索引
units = defaultdict(list)
for d in (str(REPO / 'asm/pal3/decomp'), str(ARCH)):
    for f in glob.glob(d + '/*.json'):
        try:
            units[norm(os.path.basename(f)[:-5].rsplit('_', 1)[-1])].append(f)
        except ValueError:
            pass

# 头声明索引
hdr = {}
for f in glob.glob(str(REPO / 'pal3/src/**/*.h'), recursive=True):
    t = open(f, encoding='utf-8', errors='ignore').read()
    for m in re.finditer(r'(virtual\s+)?~(\w+)\s*\(', t):
        hdr.setdefault(m.group(2), []).append(bool(m.group(1)))

pop = defaultdict(lambda: {'del': [], 'comp': []})
n = 0
for fp in glob.glob(str(REPO / 'data/annotations/structs/*.json')):
    d = json.load(open(fp))
    cls = d.get('name') or os.path.basename(fp)[:-5]
    for a, m in (d.get('methods') or {}).items():
        fl = m.get('flags') or []
        nm = str(m.get('name') or '')
        if not ('dtor' in fl or nm.startswith('~')):
            continue
        n += 1
        rec = {'addr': norm(a), 'name': nm, 'type': m.get('type'),
               'decl': bool(m.get('declaration_only')),
               'units': units.get(norm(a), [])}
        pop[cls]['del' if 'deleting' in fl else 'comp'].append(rec)

print('== dtor 人口: %d 条目 / %d 类 (删除式 %d / 完全形 %d)' % (
    n, len(pop), sum(len(v['del']) for v in pop.values()),
    sum(len(v['comp']) for v in pop.values())))

# dtor 注册符号三态
syms = sorted(set(s for s in list(cur) + list(old)
                  if s.startswith('??1') or s.startswith('??_G')))
healthy = lost = gained = never = 0
print('\n== 注册 dtor 符号 %d 个 =='.strip() % len(syms))
for s in syms:
    o, c = old.get(s), cur.get(s)
    os_ = o['status'] if o else '-'
    cs_ = c['status'] if c else '-'
    if os_ == 'match_L1' and cs_ == 'match_L1':
        healthy += 1
    elif os_ == 'match_L1':
        lost += 1
        print('  F1 曾L1现丢 %-45s %s→%s' % (s[:45], os_, cs_))
    elif cs_ == 'match_L1':
        gained += 1
        print('  新L1  %-45s %s→%s' % (s[:45], os_, cs_))
    else:
        never += 1
print('健康L1 %d | 曾L1丢 %d | 新L1 %d | 从未L1 %d' % (healthy, lost, gained, never))

# 类级旗标
f2, f3, f4, f5 = [], [], [], []
for cls, forms in pop.items():
    dels, comps = forms['del'], forms['comp']
    sup = lambda r: r['type'] == 'skip' or r['decl']
    if dels and comps and all(sup(r) for r in dels + comps):
        f2.append(cls)
    if dels and not comps and all(sup(r) for r in dels):
        f3.append(cls)
    if dels and comps and not any(sup(r) for r in dels) \
            and not any(sup(r) for r in comps):
        f4.append(cls)
    if not any(virtual for virtual in hdr.get(cls, [])) and hdr.get(cls):
        f5.append(cls)

print('\n== 类级旗标 ==')
print('F2 双形全压制(%d): %s' % (len(f2), ','.join(f2[:8])))
print('F3 删除式唯一形态被压制(%d): %s' % (len(f3), ','.join(f3[:8])))
print('F4 双形同发C2084风险(%d): %s' % (len(f4), ','.join(f4[:8])))
print('F5 头声明无virtual(%d): %s' % (len(f5), ','.join(f5[:8])))
print('\n注: F4 实测安全(collect 泛化跳过使 wrapper 体从不发射, C2084=0);')
print('    F2/F3 类的 dtor 符号当前无载体, 但多数从未 L1(逐例定谳战役挂账)。')
