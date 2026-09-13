#!/usr/bin/env python3
"""Misattribution ledger: cluster [MISATTRIBUTED] markers and bucket them by
evidence strength so renames can be applied in one batch.

Buckets:
  A  decisive-by-callers  — every marker caller is the same class, callee is
                            in NO vtable, callee has no different struct-layer
                            owner -> rename to the caller class
  B  decisive-by-vtable   — callee address sits in some class's vtable slots
                            -> rename to that vtable's class
  C  mixed                — multiple marker callers, or conflicting owners
                            -> needs manual archaeology

Usage:  python3 tools/misattribution_ledger.py [--min-sites N]
Output: data/status/misattribution_ledger.json + ranked table on stdout.
"""
import json
import os
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO = Path(__file__).parent.parent
SRC = REPO / 'pal3' / 'src'
IDA_STRUCTS = REPO / 'asm' / 'pal3' / 'ida_structs.json'
DECOMP = REPO / 'asm' / 'pal3' / 'decomp'
OUT = REPO / 'data' / 'status' / 'misattribution_ledger.json'

MARK = re.compile(
    r'\[MISATTRIBUTED\] (\w+)(?:::(\w+))? on (\w+)::this'
    r' -> fix IDB name of callee \*/ (\w+)::(\w+)')


def main():
    min_sites = 1
    if '--min-sites' in sys.argv:
        min_sites = int(sys.argv[sys.argv.index('--min-sites') + 1])

    # 1. collect markers -> clusters keyed by (callee_class, method)
    clusters = defaultdict(lambda: {'sites': 0, 'callers': Counter(),
                                    'files': set(), 'marked_names': Counter()})
    for root, _, files in os.walk(SRC):
        for f in files:
            if not f.endswith(('.cpp', '.h')):
                continue
            try:
                txt = (Path(root) / f).read_text(encoding='utf-8', errors='replace')
            except OSError:
                continue
            for m in MARK.finditer(txt):
                _, _, caller, cc, method = m.groups()
                c = clusters[(cc, method)]
                c['sites'] += 1
                c['callers'][caller] += 1
                c['files'].add(str((Path(root) / f).relative_to(REPO)).replace('\\', '/'))

    # 2. decomp pass: addr resolution + FULL caller-class distribution
    #    (marker callers only cover MISATTRIBUTED sites; phantom-class
    #    internal calls are invisible to markers — CCBStageRole lesson)
    name_addrs = defaultdict(list)
    call_edges = Counter()          # (callee_class, method) -> caller_class counter
    QUAL = re.compile(r'([A-Z]\w*)::(\w+)\s*\(')
    for f in DECOMP.glob('*.json'):
        try:
            d = json.loads(f.read_text(encoding='utf-8'))
        except (json.JSONDecodeError, OSError):
            continue
        name = d.get('name', '')
        if '::' not in name:
            continue
        cls, meth = name.split('::', 1)
        meth = meth.split('(')[0]
        name_addrs[(cls, meth)].append((d.get('address', ''), d.get('signature', '')))
        caller_cls = cls
        body = d.get('decompiled_c', '')
        for m in QUAL.finditer(body):
            call_edges[(m.group(1), m.group(2))][caller_cls] += 1

    # 3. vtable ownership
    ida = json.loads(IDA_STRUCTS.read_text(encoding='utf-8'))
    vmap = {}
    for cls, s in ida.items():
        for vt in s.get('vtables', []):
            for slot in vt.get('slots', []):
                a = slot.get('addr')
                if a:
                    vmap.setdefault(int(a, 16), cls)

    # 4. struct-layer owners (annotation methods maps)
    owners = {}
    sdir = REPO / 'data' / 'annotations' / 'structs'
    for sf in sdir.glob('*.json'):
        try:
            sd = json.loads(sf.read_text(encoding='utf-8'))
        except (json.JSONDecodeError, OSError):
            continue
        for a in sd.get('methods', {}):
            owners.setdefault(int(a, 16), sd.get('name', sf.stem))

    ledger = []
    for (cc, cm), c in clusters.items():
        if c['sites'] < min_sites:
            continue
        addrs = name_addrs.get((cc, cm), [])
        vt_owners = {vmap.get(int(a, 16)) for a, _ in
                     ((x[0], x[1]) for x in addrs) if int(a, 16) in vmap}
        vt_owners.discard(None)
        st_owners = {owners.get(int(a, 16)) for a, _ in addrs if int(a, 16) in owners}
        st_owners.discard(None)
        # full caller distribution from decomp bodies (self-calls excluded)
        full_callers = Counter({k: n for k, n in
                                call_edges.get((cc, cm), {}).items() if k != cc})

        if len(vt_owners) == 1 and next(iter(vt_owners)) != cc:
            bucket, target = 'B', next(iter(vt_owners))
        elif len(vt_owners) == 1 and next(iter(vt_owners)) == cc:
            # vtable confirms the CURRENT name — the caller side is wrong
            bucket, target = 'C', None
        marker_callers = set(c['callers'])
        if (len(marker_callers) == 1 and not vt_owners
                and st_owners <= marker_callers | {cc}
                and full_callers and set(full_callers) <= marker_callers):
            bucket, target = 'A', next(iter(marker_callers))
        else:
            bucket, target = 'C', None
        c['full_callers'] = dict(full_callers)
        ledger.append({
            'callee': f'{cc}::{cm}', 'callee_class': cc, 'method': cm,
            'sites': c['sites'], 'callers': dict(c['callers']),
            'files': sorted(c['files']), 'addrs': [a for a, _ in addrs],
            'vtable_owners': sorted(x for x in vt_owners if x),
            'struct_owners': sorted(x for x in st_owners if x),
            'full_callers': c.get('full_callers', {}),
            'bucket': bucket, 'rename_to': target,
        })

    ledger.sort(key=lambda e: (-e['sites'] if e['bucket'] in 'AB' else 0, -e['sites']))
    by_bucket = Counter(e['bucket'] for e in ledger)
    sites_by_bucket = Counter()
    for e in ledger:
        sites_by_bucket[e['bucket']] += e['sites']

    print('=== misattribution ledger ===')
    print('clusters: %d | A(decisive-callers) %d (%d sites) | B(vtable) %d (%d sites) | C(mixed) %d (%d sites)'
          % (len(ledger), by_bucket['A'], sites_by_bucket['A'],
             by_bucket['B'], sites_by_bucket['B'],
             by_bucket['C'], sites_by_bucket['C']))
    for e in ledger:
        if e['bucket'] != 'C':
            print('  [%s] %3dx %-42s -> %s' % (e['bucket'], e['sites'],
                                               e['callee'][:42], e['rename_to']))
    print('  --- C bucket (needs archaeology) top10 ---')
    for e in [x for x in ledger if x['bucket'] == 'C'][:10]:
        print('  [C] %3dx %-42s callers=%s vt=%s st=%s'
              % (e['sites'], e['callee'][:42], list(e['callers']),
                 e['vtable_owners'], e['struct_owners']))

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(json.dumps({'generated_by': __file__, 'ledger': ledger},
                              indent=1, ensure_ascii=False))
    print('ledger -> %s' % OUT)


if __name__ == '__main__':
    main()
