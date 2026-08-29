#!/usr/bin/env python3
"""S4 byte-match baseline for PAL3.exe (G0 layer-4 measurement).

For each S2-passing .cpp (per data/status/probe_census.json):
  1. compile it to .obj with the canonical probe flags
  2. extract function bodies from the COFF symbol table
     (reuses tools/gbengine_compare.parse_coff_obj)
  3. match obj symbols to annotated functions:
       - class methods: forward-mangled via pipeline/ida/vc6_mangler
       - free functions: COFF underscore rules ('_name' cdecl, '_name@N' stdcall)
  4. compare compiled bytes against original PAL3.exe .text at the annotated
     address (decomp JSON size_bytes is authoritative; relocation bytes are
     don't-care per gbengine_compare.compare_bytes)

Honesty rules: unmatched symbols and mangling failures are counted, never
silently dropped. 'match_L1' requires equal length AND zero differing bytes
outside relocations.

Usage:  python3 pipeline/compare_pal3.py [--census PATH] [--limit N]
Output: data/status/s4_baseline.json + data/status/pal3_registry.jsonl
"""

import argparse
import json
import os
import re
import struct
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO / 'tools'))
sys.path.insert(0, str(REPO / 'pipeline'))

import gbengine_compare as gc   # noqa: E402  (parse_coff_obj, compare_bytes)
import probe_compile as pc      # noqa: E402  (run_cl, INCLUDE_DIRS, wpath, OBJ_DIR)

EXE = REPO / 'original' / 'PAL3.exe'
DECOMP = REPO / 'asm' / 'pal3' / 'decomp'
CENSUS = REPO / 'data' / 'status' / 'probe_census.json'
OUT_JSON = REPO / 'data' / 'status' / 's4_baseline.json'
OUT_REG = REPO / 'data' / 'status' / 'pal3_registry.jsonl'


def exe_text_image():
    """Return (image_base, text_bytes, text_rva)."""
    data = EXE.read_bytes()
    pe = struct.unpack_from('<I', data, 0x3C)[0]
    num_sec = struct.unpack_from('<H', data, pe + 6)[0]
    opt_size = struct.unpack_from('<H', data, pe + 20)[0]
    image_base = struct.unpack_from('<I', data, pe + 24 + 28)[0]
    sec0 = pe + 24 + opt_size
    for i in range(num_sec):
        off = sec0 + i * 40
        name = data[off:off + 8].rstrip(b'\x00').decode('ascii', 'replace')
        _vsz, virt_addr, _rsz, raw_ptr = struct.unpack_from('<IIII', data, off + 8)
        if name == '.text':
            return image_base, data[raw_ptr:raw_ptr + 0x10000000], virt_addr
    raise RuntimeError('.text section not found in %s' % EXE)


def load_decomp_index():
    idx = {}
    for f in DECOMP.glob('*.json'):
        try:
            d = json.loads(f.read_text())
        except (json.JSONDecodeError, OSError):
            continue
        name, addr, size = d.get('name'), d.get('address'), d.get('size_bytes')
        if not (name and addr and size):
            continue
        try:
            va = int(addr, 16) if isinstance(addr, str) else int(addr)
        except (TypeError, ValueError):
            continue
        idx[name] = {'name': name, 'va': va, 'size': int(size),
                     'signature': d.get('signature', '')}
    return idx


def build_mangled_map(decomp_idx):
    sys.path.insert(0, str(REPO / 'pipeline' / 'ida'))
    import vc6_mangler as vm
    m2e, failed = {}, 0
    for name, e in decomp_idx.items():
        if '::' not in name:
            continue
        base = name.split('(')[0]
        if '::' not in base:
            continue
        cls, method = base.rsplit('::', 1)
        sig = e.get('signature') or ''
        try:
            m = vm.mangle(cls, method, sig)
            m2e.setdefault(m, e)
            # probe variants the annotation signature can't express:
            # virtual (vtable methods) and static (SA-prefix members)
            for kw in ({'virtual_': True}, {'static_': True}):
                mv = vm.mangle(cls, method, sig, **kw)
                if mv != m:
                    m2e.setdefault(mv, e)
        except Exception:
            failed += 1
            continue
    return m2e, failed


def build_basename_index(decomp_idx):
    """base name (no params) -> entry, only when unambiguous."""
    by_base = {}
    for name, e in decomp_idx.items():
        by_base.setdefault(name.split('(')[0], []).append(e)
    return {k: v[0] for k, v in by_base.items() if len(v) == 1}


def match_symbols(funcs, mangled_map, base_idx):
    matched = {}
    for sym in funcs:
        if sym in mangled_map:
            matched[sym] = mangled_map[sym]
            continue
        if sym.startswith('?'):
            continue  # mangled but no mangler match
        cand = sym[1:] if sym.startswith('_') else sym
        cand = re.sub(r'@\d+$', '', cand)
        if cand in base_idx:
            matched[sym] = base_idx[cand]
    return matched


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--census', default=str(CENSUS))
    ap.add_argument('--limit', type=int, default=0)
    args = ap.parse_args()

    census = json.loads(Path(args.census).read_text())
    passing = [r['unit'] for r in census['s2']['results'] if r['status'] == 'ok']
    if args.limit:
        passing = passing[:args.limit]
    print('S2-passing units: %d' % len(passing))

    decomp_idx = load_decomp_index()
    mangled_map, mangle_failed = build_mangled_map(decomp_idx)
    base_idx = build_basename_index(decomp_idx)
    print('decomp entries: %d | mangled methods: %d (mangle-fail %d) | unambiguous bases: %d'
          % (len(decomp_idx), len(mangled_map), mangle_failed, len(base_idx)))

    image_base, text, text_rva = exe_text_image()
    print('exe .text: base 0x%X rva 0x%X captured %d bytes' % (image_base, text_rva, len(text)))

    os.makedirs(pc.OBJ_DIR, exist_ok=True)
    rows = []
    stats = {'symbols': 0, 'matched': 0, 'unmatched': 0,
             'match_L1': 0, 'partial': 0, 'oob': 0, 'compile_skip': 0}

    for n, unit in enumerate(passing, 1):
        src = str(REPO / unit)
        obj = os.path.join(pc.OBJ_DIR, 's4_%d.obj' % (abs(hash(unit)) % 10 ** 8))
        out, hard = pc.run_cl(
            ['/Fo' + pc.wpath(obj), pc.wpath(src)]
            + ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS], timeout=180)
        if hard or not os.path.exists(obj):
            stats['compile_skip'] += 1
            print('  [%3d] COMPILE-SKIP %s (%s)' % (n, unit, hard or 'no obj'))
            continue
        funcs = gc.parse_coff_obj(obj)
        matched = match_symbols(funcs, mangled_map, base_idx)
        stats['symbols'] += len(funcs)
        stats['unmatched'] += len(funcs) - len(matched)
        stats['matched'] += len(matched)
        p1 = pp = 0
        for sym, e in matched.items():
            info = funcs[sym]
            size = e['size']
            idx0 = e['va'] - image_base - text_rva
            if idx0 < 0 or idx0 + size > len(text):
                stats['oob'] += 1
                rows.append({'file': unit, 'symbol': sym, 'name': e['name'],
                             'va': '0x%08X' % e['va'], 'status': 'out_of_range', 'size': size})
                continue
            compiled = info['bytes'][:size]
            relocs = {r for r in info['relocs'] if r < size}
            res = gc.compare_bytes(compiled, text[idx0:idx0 + size], e['name'],
                                   verbose=False, relocs=relocs)
            status = 'match_L1' if res['perfect'] else 'partial'
            if status == 'match_L1':
                p1 += 1
            else:
                pp += 1
            rows.append({'file': unit, 'symbol': sym[:80], 'name': e['name'],
                         'va': '0x%08X' % e['va'], 'status': status,
                         'match_pct': round(res['match_pct'], 1), 'size': size})
        stats['match_L1'] += p1
        stats['partial'] += pp
        print('  [%3d] %-45s funcs=%3d matched=%3d L1=%2d partial=%2d'
              % (n, unit, len(funcs), len(matched), p1, pp))

    print('\n=== S4 baseline ===')
    print('matched %d/%d symbols | L1 %d | partial %d | oob %d | unmatched %d | compile-skip %d'
          % (stats['matched'], stats['symbols'], stats['match_L1'],
             stats['partial'], stats['oob'], stats['unmatched'], stats['compile_skip']))
    total = stats['match_L1'] + stats['partial']
    if total:
        print('L1 rate over matched: %d/%d = %.1f%%'
              % (stats['match_L1'], total, 100.0 * stats['match_L1'] / total))

    OUT_JSON.parent.mkdir(parents=True, exist_ok=True)
    OUT_JSON.write_text(json.dumps(
        {'generated_by': 'pipeline/compare_pal3.py', 'stats': stats, 'rows': rows},
        indent=1, ensure_ascii=False))
    with open(OUT_REG, 'w') as f:
        for r in rows:
            f.write(json.dumps({'addr': r['va'], 'name': r['name'], 'file': r['file'],
                                'status': r['status'],
                                'match_pct': r.get('match_pct'),
                                'size': r.get('size')}, ensure_ascii=False) + '\n')
    print('report -> %s' % OUT_JSON)
    print('registry -> %s' % OUT_REG)


if __name__ == '__main__':
    main()
