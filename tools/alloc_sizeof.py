#!/usr/bin/env python3
"""Allocation-site sizeof adjudicator for PAL3Decomp.

MSVC emits `push SIZE; call operator new; mov ecx,eax; call ctor` for
heap constructions — the pushed immediate IS sizeof(Class), compiler-
generated ground truth. This tool:

  1. locates the static operator new (the E8-call target most frequently
     preceded by `push imm32` — no CRT DLL import in this binary)
  2. for every constructor known to annotations (functions.json +
     struct methods with name == class), collects allocation sites and
     the pushed sizes
  3. reports class -> {size: count} vs the annotation binary_size

Discrepancies are adjudication requests: the allocation immediate wins
over scan radii and container guesses (see CCBResultWindow 180/2628
incident in the memory file).

Usage:  python3 tools/alloc_sizeof.py [--json]
Output: stdout table + data/status/alloc_sizeof.json
"""
import json
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO = Path(__file__).parent.parent
EXE = REPO / 'original' / 'PAL3.exe'
OUT = REPO / 'data' / 'status' / 'alloc_sizeof.json'
IMGBASE = 0x400000
TEXT_LO, TEXT_HI = 0x1000, 0x16A000  # file offsets (.text)


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


def _is_alloc_site(data, foff):
    """push SIZE(imm32 or imm8); call new; mov reg,eax — excludes SEH/atexit
    sites that push ADDRESSES (>=0x401000) and follow with `pop ecx; ret`."""
    size = None
    if data[foff - 5] == 0x68:
        size = struct.unpack_from('<I', data, foff - 4)[0]
    elif data[foff - 2] == 0x6A:
        size = data[foff - 1]
    if size is None or not (4 <= size < 0x20000):
        return False
    post = data[foff + 5:foff + 9]
    return len(post) >= 2 and (
        (post[0] == 0x8B and post[1] in (0xC8, 0xD8, 0xF0, 0xF8, 0xC6, 0xDE))
        or (post[0] == 0x89 and post[1] in (0x01, 0x08, 0x06, 0x0E)))


def _alloc_size_at(data, foff):
    if data[foff - 5] == 0x68:
        return struct.unpack_from('<I', data, foff - 4)[0]
    return data[foff - 1]


def find_operator_new(data, sites, known_ctors):
    """Score every push-preceded E8 target by how often its site's next
    E8 lands on a KNOWN constructor — operator new's defining signature.
    (A bare frequency count picks mid-function false positives.)"""
    cand = Counter()
    for foff, tgt in sites:
        if _is_alloc_site(data, foff):
            cand[tgt] += 1
    scores = Counter()
    for foff, tgt in sites:
        if cand.get(tgt, 0) < 10 or not _is_alloc_site(data, foff):
            continue
        seg = data[foff + 5:foff + 53]
        j = 0
        while j < len(seg) - 5:
            if seg[j] == 0xE8:
                rel = struct.unpack_from('<i', seg, j + 1)[0]
                nxt = foff + 5 + j + 5 + rel + IMGBASE
                if nxt in known_ctors:
                    scores[tgt] += 1
                break
            j += 1
    if scores:
        return scores.most_common(1)[0][0], cand
    # no site's ctor is in the annotation set yet — fall back to the
    # most frequent alloc-shaped target (the shape is specific enough)
    if cand:
        return cand.most_common(1)[0][0], cand
    return None, cand


def main():
    data = load_text()
    sites = call_sites(data)
    known_ctors = set()
    fj = json.loads((REPO / 'data' / 'annotations' / 'functions.json').read_text(encoding='utf-8'))
    for a, v in fj.items():
        n = str(v.get('name', ''))
        cls = n.split('::')[0] if '::' in n else None
        if cls and n.split('::')[-1] == cls:
            known_ctors.add(int(a, 16))
    ida = json.loads((REPO / 'asm' / 'pal3' / 'ida_structs.json').read_text(encoding='utf-8'))
    for cls, s in ida.items():
        for a, m in s.get('methods', {}).items():
            if m.get('name') == cls:
                known_ctors.add(int(a, 16))
    new_va, tgt_push = find_operator_new(data, sites, known_ctors)

    # sites of operator new with the pushed size
    # pattern: 68 SIZE(lo32) [e8 new] then within 16 bytes: 8b c8 / 89 01 /
    # 8b f0 etc (mov ecx,eax) and e8 ctor
    new_sites = [foff for foff, tgt in sites if tgt == new_va]

    # map site -> (size, ctor_va): walk forward, SKIPPING complete
    # push/call-new pairs (chained allocations `new A; new B; ctorB;
    # ctorA` make the first E8 another new, not a ctor)
    alloc = defaultdict(Counter)   # ctor_va -> size counter
    for foff in new_sites:
        if not _is_alloc_site(data, foff):
            continue
        size = _alloc_size_at(data, foff)
        seg_start = foff + 5
        j = 0
        ctor = None
        window = 96
        while j < window - 6:
            b = data[seg_start + j]
            if b == 0xE8:
                j += 5              # any call: skip and keep walking
                continue
            # mov ecx, reg (8B C8..CF) followed within 4 bytes by E8 =
            # __thiscall ctor binding — the real ctor signature; plain
            # buffer allocs feed memcpy-style calls without ecx binding
            if b == 0x8B and 0xC8 <= data[seg_start + j + 1] <= 0xCF:
                k = j + 2
                while k <= j + 8 and k < window - 5:
                    if data[seg_start + k] == 0xE8:
                        rel = struct.unpack_from('<i', data, seg_start + k + 1)[0]
                        ctor = seg_start + k + 5 + rel + IMGBASE
                        break
                    k += 1
                if ctor:
                    break
            j += 1
        if ctor:
            alloc[ctor][size] += 1

    # ctor name map from annotations
    ctors = {}
    fj = json.loads((REPO / 'data' / 'annotations' / 'functions.json').read_text(encoding='utf-8'))
    for a, v in fj.items():
        n = str(v.get('name', ''))
        cls = n.split('::')[0] if '::' in n else None
        meth = n.split('::')[-1]
        if cls and meth == cls:
            ctors[int(a, 16)] = cls
    ida = json.loads((REPO / 'asm' / 'pal3' / 'ida_structs.json').read_text(encoding='utf-8'))
    for cls, s in ida.items():
        for a, m in s.get('methods', {}).items():
            if m.get('name') == cls:
                ctors.setdefault(int(a, 16), cls)

    ann_size = {}
    sdir = REPO / 'data' / 'annotations' / 'structs'
    for f in sdir.glob('*.json'):
        d = json.loads(f.read_text(encoding='utf-8'))
        if d.get('binary_size'):
            ann_size[d.get('name', f.stem)] = d['binary_size']

    rows = []
    for ctor_va, sizes in sorted(alloc.items()):
        cls = ctors.get(ctor_va)
        if not cls:
            continue
        size, cnt = sizes.most_common(1)[0]
        if cnt < sum(sizes.values()) * 0.7:
            note = 'mixed:%s' % dict(sizes)
        else:
            note = ''
        cur = ann_size.get(cls)
        verdict = 'OK' if cur == size else ('NO-ANNOTATION' if cur is None else 'MISMATCH')
        rows.append({'class': cls, 'ctor': '0x%08X' % ctor_va,
                     'alloc_size': size, 'sites': sum(sizes.values()),
                     'annotation_size': cur, 'verdict': verdict, 'note': note})

    mism = [r for r in rows if r['verdict'] == 'MISMATCH']
    print('operator new @ %s | %d alloc sites | %d ctors resolved'
          % ('0x%08X' % new_va if new_va else '?', len(new_sites), len(rows)))
    print('annotation mismatches: %d' % len(mism))
    for r in sorted(mism, key=lambda r: -abs((r['annotation_size'] or 0) - r['alloc_size']))[:20]:
        print('  %-24s alloc=%-7d ann=%-7d %s' % (r['class'], r['alloc_size'],
                                                  r['annotation_size'] or -1, r['note']))

    OUT.write_text(json.dumps({'operator_new': new_va and '0x%08X' % new_va,
                               'rows': rows}, indent=1, ensure_ascii=False), encoding='utf-8')
    print('report -> %s' % OUT)


if __name__ == '__main__':
    main()
