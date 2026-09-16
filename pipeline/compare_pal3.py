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
    """Return (image_base, text_bytes, text_rva, text_raw_size).

    ⚠️ `text_bytes` **只含 `.text`**（`raw_ptr .. raw_ptr + raw_size`）。

    R8（2026-09-15 第 6 任复核者 kiro 发现、captain 量化并修）：
    本函数原先返回 `data[raw_ptr : raw_ptr + 0x10000000]` —— Python 切片**超尾静默截断**
    ⇒ 实际得到 `data[raw_ptr:]` = **到文件末尾**（实测 0x211000 字节），
    而 `.text` 只有 `raw_size = 0x169000`。该窗口跨越 `.text + .rdata + .data + .rsrc`。
    后果：下游 `oob` 判据用 `len(text)` 作界 ⇒ **近恒真**（`.rdata` 里的地址也判"在界内"），
    为本会话第 6 例恒真/近恒真门禁。
    `raw_size` 一并返回，供调用方做**正确的 `.text` 边界判定**。
    """
    data = EXE.read_bytes()
    pe = struct.unpack_from('<I', data, 0x3C)[0]
    num_sec = struct.unpack_from('<H', data, pe + 6)[0]
    opt_size = struct.unpack_from('<H', data, pe + 20)[0]
    image_base = struct.unpack_from('<I', data, pe + 24 + 28)[0]
    sec0 = pe + 24 + opt_size
    for i in range(num_sec):
        off = sec0 + i * 40
        name = data[off:off + 8].rstrip(b'\x00').decode('ascii', 'replace')
        _vsz, virt_addr, raw_size, raw_ptr = struct.unpack_from('<IIII', data, off + 8)
        if name == '.text':
            return image_base, data[raw_ptr:raw_ptr + raw_size], virt_addr, raw_size
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


def _split_mangled_name(name):
    """从 **本身已是 mangled 名** 的 decomp name 里提取 (cls, method)。

    0b-③ 补（2026-09-15）：实测量得 5 个 decomp 条目的 `name` 以 `?` 开头
    （本身就是 mangled 名，形如
    `?PushOpen@AStarPathFinder@@QAEHPAUAStarPathFinder::NODE@@@Z` 或含 `[thunk]`）。
    原 `build_mangled_map` 假设所有 name 都是 `Cls::meth(...)` 形态，对它做
    `base.rsplit('::', 1)` ⇒ cls 变成 `?PushOpen@AStarPathFinder@@QAEHPAUAStarPathFinder`、
    method 变成 `NODE@@@Z`，产出**垃圾名**（永远匹配不上）。

    正确做法：从 mangled 名解析出 `?<method>@<class>@@`。
    返回 `(cls, method)`，无法解析时返回 `(None, None)`。
    """
    m = re.match(r'^\?+[0-9A-Za-z_]*?(\w+)@(\w+)@@', name)
    if m:
        return m.group(2), m.group(1)
    # ctor/dtor: ??0Cls@@ / ??1Cls@@
    m = re.match(r'^\?\?[01](\w+)@@', name)
    if m:
        return m.group(1), m.group(1)
    return None, None


def build_mangled_map(decomp_idx):
    sys.path.insert(0, str(REPO / 'pipeline' / 'ida'))
    import vc6_mangler as vm
    m2e, failed = {}, 0
    for name, e in decomp_idx.items():
        if name.startswith('?'):
            # name 本身即 mangled 名 ⇒ 解析出 cls/method 后**用签名重算**
            # （mangler 可能生成得比 IDA 的 mangled name 更准，例如嵌套类层级号）
            cls, method = _split_mangled_name(name)
            if not cls:
                continue
        else:
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


PROBE_FLAGS = ['/nologo', '/TP', '/c', '/W3']
# docs/compiler_setup.md hypothesis flag set (needs byte-compare calibration —
# that is exactly what --flags-matrix does)
HYPOTHESIS_FLAGS = ['/O2', '/Ob2', '/Oi', '/Ot', '/Oy', '/GF', '/Gy',
                    '/GX', '/GR', '/MD', '/Gd']


def compare_units(passing, flags, decomp_idx, mangled_map, base_idx,
                  image_base, text, text_rva, text_raw_size=None):
    """Run the S4 byte-match over `passing` units with the given CL flags.

    `text_raw_size` = `.text` 的 `raw_size`，用作**正确的越界界**（R8）。
    None 时退回 `len(text)`（仅为向后兼容，会退化为近恒真的旧行为）。"""
    os.makedirs(pc.OBJ_DIR, exist_ok=True)
    rows = []
    stats = {'symbols': 0, 'matched': 0, 'unmatched': 0,
             'match_L1': 0, 'partial': 0, 'oob': 0, 'compile_skip': 0,
            # R8：两种越界语义**不得合并计数**。
            #   oob_text_end —— 越过 `.text` 尾（真实代码区之外）⇒ 比对数据不可信
            #   oob_file_end —— 越过文件末尾 ⇒ 连字节都取不到
            'oob_text_end': 0, 'oob_file_end': 0}

    for n, unit in enumerate(passing, 1):
        src = str(REPO / unit)
        obj = os.path.join(pc.OBJ_DIR, 's4_%d.obj' % (abs(hash(unit)) % 10 ** 8))
        out, hard = pc.run_cl(
            ['/Fo' + pc.wpath(obj), pc.wpath(src)]
            + ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS],
            timeout=180, flags=flags)
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
            # R8：界的语义必须正确 —— 用 **`.text` 的 raw_size**，不是缓冲区长度。
            # 缓冲区长度曾是"文件末尾到 .text 起点"（0x211000），比 .text（0x169000）大一截，
            # 使该判据近恒真（`.rdata` 里的地址也判"在界内"）。本会话第 6 例恒真门禁。
            _limit = text_raw_size if text_raw_size is not None else len(text)
            if idx0 < 0 or idx0 + size > _limit:
                stats['oob'] += 1
                if idx0 < 0 or idx0 + size > len(text):
                    stats['oob_file_end'] += 1
                else:
                    stats['oob_text_end'] += 1
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

    print('matched %d/%d symbols | L1 %d | partial %d | oob %d (text_end %d / file_end %d) '
          '| unmatched %d | compile-skip %d'
          % (stats['matched'], stats['symbols'], stats['match_L1'],
             stats['partial'], stats['oob'], stats['oob_text_end'], stats['oob_file_end'],
             stats['unmatched'], stats['compile_skip']))
    total = stats['match_L1'] + stats['partial']
    if total:
        print('L1 rate over matched: %d/%d = %.1f%%'
              % (stats['match_L1'], total, 100.0 * stats['match_L1'] / total))

    return stats, rows


def _flags_matrix(units, decomp_idx, mangled_map, base_idx, image_base, text, text_rva,
                  text_raw_size=None):
    """Calibrate CL flags: probe defaults vs the hypothesis set vs
    leave-one-out perturbations of the hypothesis. Ranks combos by L1."""
    combos = [('probe-defaults', PROBE_FLAGS), ('hypothesis', list(HYPOTHESIS_FLAGS))]
    for f in HYPOTHESIS_FLAGS:
        combos.append(('hypothesis-minus-' + f.lstrip('/'),
                       [x for x in HYPOTHESIS_FLAGS if x != f]))

    results = []
    for label, flags in combos:
        print('\n--- %s: %s ---' % (label, ' '.join(flags)))
        stats, _ = compare_units(units, flags, decomp_idx, mangled_map,
                                 base_idx, image_base, text, text_rva, text_raw_size)
        results.append({'label': label, 'flags': flags, 'stats': stats})

    results.sort(key=lambda r: (-r['stats']['match_L1'],
                                -r['stats']['match_L1'] - r['stats']['partial']))
    print('\n=== flags matrix (sorted by L1) ===')
    for r in results:
        s = r['stats']
        print('%-28s L1 %3d | partial %3d | matched %3d/%3d' % (
            r['label'], s['match_L1'], s['partial'], s['matched'], s['symbols']))

    out = REPO / 'data' / 'status' / 'flags_matrix.json'
    out.write_text(json.dumps({'generated_by': 'pipeline/compare_pal3.py',
                               'units': units, 'results': results},
                              indent=1, ensure_ascii=False))
    print('matrix -> %s' % out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--census', default=str(CENSUS))
    ap.add_argument('--limit', type=int, default=0)
    ap.add_argument('--flags', default=None,
                    help='override CL flags, e.g. --flags "/TP /c /O2 /Gy"')
    ap.add_argument('--flags-matrix', action='store_true',
                    help='compile+compare a unit sample under probe defaults, '
                         'the hypothesis set, and leave-one-out perturbations; '
                         'ranks flag combos by L1 match rate')
    args = ap.parse_args()

    census_path = Path(args.census)
    if not census_path.exists():
        # Prerequisite guard: this used to die with a bare FileNotFoundError
        # traceback, and `cli.py match` (which must enforce the L1 ratchet)
        # would then report nothing useful about why.
        print('[ERROR] probe census not found: %s' % census_path, file=sys.stderr)
        print('  data/status/probe_census.json is produced by the S2 probe:', file=sys.stderr)
        print('      python pipeline/cli.py probe all', file=sys.stderr)
        print('  Refusing to run: byte-match L1 cannot be computed without the S2 list.',
              file=sys.stderr)
        sys.exit(2)
    try:
        census = json.loads(census_path.read_text())
    except (json.JSONDecodeError, UnicodeDecodeError, OSError) as e:
        print('[ERROR] probe census is unreadable/invalid: %s' % census_path, file=sys.stderr)
        print('  %s' % e, file=sys.stderr)
        print('  Re-run: python pipeline/cli.py probe all', file=sys.stderr)
        sys.exit(2)
    s2 = census.get('s2') if isinstance(census, dict) else None
    if not isinstance(s2, dict) or not isinstance(s2.get('results'), list):
        print('[ERROR] probe census has no usable s2.results list: %s' % census_path,
              file=sys.stderr)
        print('  Expected a census written by pipeline/probe_compile.py.', file=sys.stderr)
        print('  Re-run: python pipeline/cli.py probe all', file=sys.stderr)
        sys.exit(2)
    malformed = [i for i, r in enumerate(s2['results'])
                 if not isinstance(r, dict) or 'unit' not in r or 'status' not in r]
    if malformed:
        # Never silently skip an entry: a dropped S2-passing unit would silently
        # shrink the byte-match denominator and inflate the L1 rate.
        print('[ERROR] probe census has %d malformed s2.results entr(ies) (first idx %d): %s'
              % (len(malformed), malformed[0], census_path), file=sys.stderr)
        print('  Every entry needs "unit" and "status". Re-run: '
              'python pipeline/cli.py probe all', file=sys.stderr)
        sys.exit(2)
    passing = [r['unit'] for r in census['s2']['results'] if r['status'] == 'ok']
    if args.limit:
        passing = passing[:args.limit]
    print('S2-passing units: %d' % len(passing))

    decomp_idx = load_decomp_index()
    mangled_map, mangle_failed = build_mangled_map(decomp_idx)
    base_idx = build_basename_index(decomp_idx)
    print('decomp entries: %d | mangled methods: %d (mangle-fail %d) | unambiguous bases: %d'
          % (len(decomp_idx), len(mangled_map), mangle_failed, len(base_idx)))

    image_base, text, text_rva, text_raw_size = exe_text_image()
    print('exe .text: base 0x%X rva 0x%X captured %d bytes' % (image_base, text_rva, len(text)))

    if args.flags_matrix:
        sample = passing[:5] if args.limit == 0 else passing
        return _flags_matrix(sample, decomp_idx, mangled_map, base_idx,
                             image_base, text, text_rva, text_raw_size)

    flags = args.flags.split() if args.flags else PROBE_FLAGS
    stats, rows = compare_units(passing, flags, decomp_idx, mangled_map,
                                base_idx, image_base, text, text_rva, text_raw_size)

    total = stats['match_L1'] + stats['partial']
    if total:
        print('L1 rate over matched: %d/%d = %.1f%%'
              % (stats['match_L1'], total, 100.0 * stats['match_L1'] / total))

    OUT_JSON.parent.mkdir(parents=True, exist_ok=True)
    OUT_JSON.write_text(json.dumps(
        {'generated_by': 'pipeline/compare_pal3.py', 'flags': flags,
         'stats': stats, 'rows': rows},
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
