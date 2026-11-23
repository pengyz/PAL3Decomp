#!/usr/bin/env python3
"""Allocation-site sizeof adjudicator for PAL3Decomp (v2, ctor-anchored).

MSVC emits `push SIZE; call operator new; ...; call ctor` for heap
constructions — the pushed immediate IS sizeof(Class), compiler-generated
ground truth. With /O2 the window between `call new` and `call ctor`
carries argument pushes and register moves, so a fixed local window misses
most sites (v1 found 54/422). v2 inverts the pairing:

  for every KNOWN ctor (annotations), take its call sites and walk BACKWARD
  through the call list to the nearest `call operator new` within 96 bytes
  whose preceding instruction is `push imm` (4 <= size < 0x20000, which
  also excludes SEH/atexit address pushes).

Discrepancies are adjudication requests: the allocation immediate wins
over scan radii and container guesses (see CCBResultWindow 180/2628
incident in the memory file). Phantom-class rows (ctor known only from
stale IDA exports) are excluded from verdicts.

Usage:  python3 tools/alloc_sizeof.py
Output: stdout table + data/status/alloc_sizeof.json
"""
import json
import struct
from collections import Counter, defaultdict
from pathlib import Path


# ---- 2026-09-20 审计 P2-4：无参数解析工具的统一护栏 ----------------------------
# 本工具**会写盘**且**没有任何 argparse/sys.argv 处理** ⇒ 传任何 `-` 开头的参数
# （最典型的是 `--help`）此前会被当作普通输入，**执行全流程并覆盖产物**。
# 本次审计期间已因此发生 **2 起事故**（`sig_evidence.py` 删掉 6020 行、
# `misattribution_ledger.py` 把 197 cluster 改写成 3）。
# 统一护栏：见到任何以 `-` 开头的参数即打印用法并**退出，不执行任何工作**。
import sys as _sys_guard
if any(_a.startswith('-') for _a in _sys_guard.argv[1:]):
    print('[%s] 本工具不接受命令行开关；收到 %r ⇒ 不执行任何操作。'
          % (__file__.rsplit('/', 1)[-1], _sys_guard.argv[1:]))
    print('用法: python3 %s    # 无参数，直接运行' % __file__)
    _sys_guard.exit(0)
# ---------------------------------------------------------------------------

REPO = Path(__file__).parent.parent
EXE = REPO / 'original' / 'PAL3.exe'
OUT = REPO / 'data' / 'status' / 'alloc_sizeof.json'
IMGBASE = 0x400000
TEXT_LO, TEXT_HI = 0x1000, 0x16A000  # file offsets (.text)
PAIR_WINDOW = 96


def load_text():
    return EXE.read_bytes()


def call_sites(data):
    """[(site_foff, target_va)] for every E8 rel32 in .text."""
    out = []
    for i in range(TEXT_LO, TEXT_HI - 5):
        if data[i] == 0xE8:
            rel = struct.unpack_from('<i', data, i + 1)[0]
            out.append((i, i + 5 + rel + IMGBASE))
    return out


def _push_size_before(data, foff):
    """Size pushed immediately before a call at foff, else None.
    push imm32 (0x68) or push imm8 (0x6A); address pushes (>=0x401000)
    are excluded by the size bound."""
    if foff >= 5 and data[foff - 5] == 0x68:
        v = struct.unpack_from('<I', data, foff - 4)[0]
        if 4 <= v < 0x20000:
            return v
    if foff >= 2 and data[foff - 2] == 0x6A:
        v = data[foff - 1]
        if 4 <= v:
            return v
    return None


def find_operator_new(data, sites):
    """Most frequent push-preceded E8 target whose size looks like an
    allocation (the static operator new; no CRT DLL import here)."""
    cand = Counter()
    for foff, tgt in sites:
        if _push_size_before(data, foff) is not None:
            cand[tgt] += 1
    if not cand:
        return None
    return cand.most_common(1)[0][0]


def _ctor_maps():
    """ctor_va -> class, from three sources (structs annotations are the
    post-round-5 authoritative source; ida_structs may retain stale
    phantom-class entries)."""
    known = set()
    names = {}
    fj = json.loads((REPO / 'data' / 'annotations' / 'functions.json').read_text(encoding='utf-8'))
    for a, v in fj.items():
        n = str(v.get('name', ''))
        cls = n.split('::')[0] if '::' in n else None
        meth = n.split('::')[-1]
        if cls and (meth == cls or meth == 'ctor'):
            va = int(a, 16)
            known.add(va)
            names.setdefault(va, cls)
    for f in (REPO / 'data' / 'annotations' / 'structs').glob('*.json'):
        d = json.loads(f.read_text(encoding='utf-8'))
        cls = d.get('name', f.stem)
        for a, m in (d.get('methods') or {}).items():
            mn = str(m.get('name', ''))
            if mn == cls or mn == 'ctor':
                va = int(a, 16)
                known.add(va)
                names.setdefault(va, cls)
    ida_file = REPO / 'asm' / 'pal3' / 'ida_structs.json'
    if ida_file.exists():
        ida = json.loads(ida_file.read_text(encoding='utf-8'))
        for cls, s in ida.items():
            for a, m in s.get('methods', {}).items():
                if m.get('name') == cls:
                    va = int(a, 16)
                    known.add(va)
                    names.setdefault(va, cls)
    return known, names


def main():
    data = load_text()
    sites = call_sites(data)
    site_by_foff = dict(sites)
    foffs_sorted = sorted(site_by_foff)
    known_ctors, names = _ctor_maps()

    new_va = find_operator_new(data, sites)
    print('operator new @ %s' % ('0x%08X' % new_va if new_va else '?'))

    ann_size = {}
    sdir = REPO / 'data' / 'annotations' / 'structs'
    for f in sdir.glob('*.json'):
        d = json.loads(f.read_text(encoding='utf-8'))
        if d.get('binary_size'):
            ann_size[d.get('name', f.stem)] = d['binary_size']

    import bisect
    alloc = defaultdict(Counter)   # ctor_va -> {size: count}
    exhibits = defaultdict(dict)   # ctor_va -> size -> [(alloc_va, ctor_call_va)]
    ambiguous = Counter()          # ctor_va -> sites dropped by intervening-ctor guard
    for ctor_va in sorted(known_ctors):
        callers = sorted(f for f, t in sites if t == ctor_va)
        for cf in callers:
            # nearest preceding E8 site whose target is operator new;
            # AMBIGUITY GUARD: if another KNOWN ctor call sits between the
            # new call and this ctor call, this is the chained-allocation
            # pattern (`new A; new B; ctorB; ctorA`) - the nearest new is
            # B's, not ours. Drop rather than misattribute.
            i = bisect.bisect_left(foffs_sorted, cf) - 1
            while i >= 0:
                pf = foffs_sorted[i]
                if cf - pf > PAIR_WINDOW:
                    break
                tgt = site_by_foff[pf]
                if tgt in known_ctors and tgt != ctor_va:
                    ambiguous[ctor_va] += 1
                    break
                if tgt == new_va:
                    size = _push_size_before(data, pf)
                    if size is not None:
                        alloc[ctor_va][size] += 1
                        exhibits[ctor_va].setdefault(size, []).append(
                            ('0x%08X' % (pf + IMGBASE), '0x%08X' % (cf + IMGBASE)))
                    break
                i -= 1

    rows = []
    phantom = 0
    for ctor_va, sizes in sorted(alloc.items()):
        cls = names.get(ctor_va)
        if not cls:
            continue
        size, cnt = sizes.most_common(1)[0]
        note = '' if cnt >= sum(sizes.values()) * 0.7 else 'mixed:%s' % dict(sizes)
        cur = ann_size.get(cls)
        if cur is None:
            phantom += 1
            rows.append({'class': cls, 'ctor': '0x%08X' % ctor_va,
                         'alloc_size': size, 'sites': sum(sizes.values()),
                         'annotation_size': None, 'verdict': 'PHANTOM',
                         'note': note})
            continue
        if cur <= 16:
            # opaque pseudo-type (ida_structs artifact): layout not modeled
            rows.append({'class': cls, 'ctor': '0x%08X' % ctor_va,
                         'alloc_size': size, 'sites': sum(sizes.values()),
                         'annotation_size': cur, 'verdict': 'OPAQUE',
                         'note': note})
            continue
        rows.append({'class': cls, 'ctor': '0x%08X' % ctor_va,
                     'alloc_size': size, 'sites': sum(sizes.values()),
                     'annotation_size': cur,
                     'verdict': 'OK' if cur == size else 'MISMATCH',
                     'note': note,
                     'exhibits': exhibits.get(ctor_va, {}).get(size, [])[:3]})

    verdicts = Counter(r['verdict'] for r in rows)
    amb = sum(ambiguous.values())
    print('ctor-anchored pairs: %d | ambiguous(chained-alloc) drops: %d | %s'
          % (len(rows), amb, dict(verdicts)))
    mism = [r for r in rows if r['verdict'] == 'MISMATCH']
    print('annotation mismatches: %d' % len(mism))
    for r in sorted(mism, key=lambda r: -abs((r['annotation_size'] or 0) - r['alloc_size']))[:20]:
        print('  %-24s alloc=%-7d ann=%-7d sites=%d %s' % (
            r['class'], r['alloc_size'], r['annotation_size'] or -1,
            r['sites'], r['note']))

    OUT.write_text(json.dumps({'operator_new': new_va and '0x%08X' % new_va,
                               'rows': rows}, indent=1, ensure_ascii=False),
                   encoding='utf-8')
    print('report -> %s' % OUT)


if __name__ == '__main__':
    main()
