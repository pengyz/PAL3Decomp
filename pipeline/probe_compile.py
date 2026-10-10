import os
#!/usr/bin/env python3
"""S1/S2 probe-compile census for PAL3 decompilation.

Layer model (see docs/knowledge + G0 framework discussion):
  S1  header standalone compile  — each .h must compile as an independent TU
  S2  translation unit compile   — each .cpp compiles /c with the canonical
                                   include set, independent of all other cpp

S2 failures carry per-error attribution so a file whose errors all point into
included headers is counted as "imported failure" (blocked-by root headers),
not as an independent regression. This kills the globals.h cascade distortion:
the census reports root-cause headers, not 205 uniformly red files.

Usage:
  python3 pipeline/probe_compile.py            # S1 + S2
  python3 pipeline/probe_compile.py s1         # headers only
  python3 pipeline/probe_compile.py s2         # cpp only
  python3 pipeline/probe_compile.py --out PATH # write JSON here

Output: data/status/probe_census.json (+ human summary on stdout).
"""

import argparse
import concurrent.futures as futures
import json
import os
import re
import shutil
import subprocess
import sys
import time
from datetime import datetime

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(REPO, 'pal3', 'src')
# MSVC6 CL.EXE is a native Win32 binary: run it directly on Windows, via
# wine elsewhere. Keep the scratch dir off the repo on both platforms.
NATIVE_WIN = (os.name == 'nt')
OBJ_DIR = os.path.join(os.environ.get('TEMP', '/tmp') if NATIVE_WIN else '/tmp',
                       'pal3_probe')
CL = os.path.join(REPO, 'tools', 'compilers', 'msvc6.0', 'Bin', 'CL.EXE')

INCLUDE_DIRS = [
    os.path.join(REPO, 'include'),
    SRC,
    os.path.join(REPO, 'tools', 'compilers', 'msvc6.0', 'Include'),
    os.path.join(REPO, 'tools', 'vc6', 'Include'),
]

# wine's default Z: drive maps to the filesystem root; build Windows paths
# directly instead of spawning winepath ~950 times.
def wpath(p):
    p = os.path.abspath(p)
    if NATIVE_WIN:
        return p.replace('/', '\\')
    return 'Z:' + p.replace('/', '\\')

ERR_RE = re.compile(r'^(?P<file>.+?)\((?P<line>\d+)\) : (?:(?P<fatal>fatal) )?error (?P<code>[A-Z]\d+): (?P<msg>.*)$')
WARN_RE = re.compile(r' warning (?P<code>[A-Z]\d+)')


def normalize_err_path(p):
    """CL prints Z:\\...\\PAL3Decomp\\pal3\\src\\Misc/X.h (mixed separators).
    Normalize to repo-relative posix path."""
    p = p.replace('\\', '/')
    marker = 'PAL3Decomp/'
    i = p.find(marker)
    if i >= 0:
        return p[i + len(marker):]
    return p


def run_cl(args, timeout=90, flags=('/nologo', '/TP', '/c', '/W3')):
    if NATIVE_WIN:
        prefix = [wpath(CL)]
    else:
        prefix = ['wine', wpath(CL)]
    cmd = prefix + list(flags) + args
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True,
                              errors='replace', timeout=timeout, cwd=REPO)
        return proc.stdout + '\n' + proc.stderr, None
    except subprocess.TimeoutExpired:
        return '', 'timeout after %ss' % timeout
    except OSError as e:
        return '', 'spawn failed: %s' % e


def parse_output(text):
    errors, warn_count = [], 0
    for line in text.splitlines():
        m = ERR_RE.match(line.strip())
        if m:
            errors.append({
                'file': normalize_err_path(m.group('file')),
                'line': int(m.group('line')),
                'code': m.group('code'),
                'msg': m.group('msg')[:200],
            })
        else:
            if WARN_RE.search(line):
                warn_count += 1
    return errors, warn_count


def probe_unit(unit, probe_src, tag):
    """unit: repo-relative source path (or header rel for S1).
    probe_src: None → compile unit directly; else text of a synthetic TU."""
    src_abs = os.path.join(REPO, unit)
    obj = os.path.join(OBJ_DIR, '%s_%s.obj' % (tag, abs(hash(unit)) % 10**8))
    args = ['/Fo' + wpath(obj)]
    if probe_src is not None:
        pfile = os.path.join(OBJ_DIR, '%s_%s.cpp' % (tag, abs(hash(unit)) % 10**8))
        with open(pfile, 'w') as f:
            f.write(probe_src)
        src_for_cl = wpath(pfile)
    else:
        src_for_cl = wpath(src_abs)
    args.append(src_for_cl)
    for d in INCLUDE_DIRS:
        args.append('/I' + wpath(d))

    t0 = time.time()
    text, hard_err = run_cl(args)
    dur = round(time.time() - t0, 2)
    errors, warns = parse_output(text)
    # False-OK guard: cl must either report errors or actually produce the
    # object file. A silent short-circuit (wine spawn glitch, arg mangling)
    # would otherwise be indistinguishable from success.
    if not hard_err and not errors and not os.path.exists(obj):
        return {'unit': unit, 'status': 'harness_error', 'errors': [],
                'warnings': 0, 'detail': 'cl reported nothing and produced no obj', 'secs': dur}
    if hard_err:
        return {'unit': unit, 'status': 'harness_error', 'errors': [],
                'warnings': 0, 'detail': hard_err, 'secs': dur}
    return {'unit': unit, 'status': ('ok' if not errors else 'fail'),
            'errors': errors, 'warnings': warns, 'secs': dur}


def collect(pattern, ext):
    out = []
    for dirpath, _, files in os.walk(SRC):
        for f in files:
            if f.endswith(ext):
                # posix-relative, so unit keys match normalize_err_path output
                # and summarize_s2's own-vs-foreign attribution on any OS
                rel = os.path.relpath(os.path.join(dirpath, f), REPO)
                out.append(rel.replace(os.sep, '/'))
    return sorted(out)


def census(layer):
    units = collect('*.h', '.h') if layer == 's1' else collect('*.cpp', '.cpp')
    # S2 接线（接线审计定论）：**产出端收窄** —— census 只含射程单元，
    # probe_census.json 本身就是射程产物，S3 比对两份 census 更直观。
    # 收窄点 = collect() 之后、遍历之前（此处是唯一的单元消费点）。
    if PROBE_ONLY is not None:
        _want = {os.path.basename(u) for u in PROBE_ONLY}
        _before = len(units)
        units = [u for u in units if os.path.basename(u) in _want]
        print('[S2] probe scoped: %d -> %d units' % (_before, len(units)))
    results = []
    with futures.ThreadPoolExecutor(max_workers=6) as ex:
        futs = {}
        for u in units:
            if layer == 's1':
                # include path must be relative to the pal3/src include root
                rel = os.path.relpath(u, SRC)
                probe = '#include "%s"\nint _probe_pad;\n' % rel
                futs[ex.submit(probe_unit, u, probe, 's1')] = u
            else:
                futs[ex.submit(probe_unit, u, None, 's2')] = u
        for fu in futures.as_completed(futs):
            results.append(fu.result())
    return sorted(results, key=lambda r: r['unit'])


def summarize_s2(s2):
    """own/imported attribution: a cpp is an imported failure iff every error
    points into some *other* file (i.e. headers it includes)."""
    root_blame = {}
    imported, owned, ok = [], [], 0
    for r in s2:
        if r['status'] == 'ok':
            ok += 1
            continue
        if r['status'] != 'fail':
            owned.append(r['unit'])  # harness errors surfaced separately
            continue
        foreign = {e['file'] for e in r['errors'] if e['file'] != r['unit']}
        own = [e for e in r['errors'] if e['file'] == r['unit']]
        if own or not foreign:
            owned.append(r['unit'])
        else:
            imported.append(r['unit'])
        for h in foreign:
            root_blame.setdefault(h, []).append(r['unit'])
    return {
        'ok': ok,
        'fail_own': len(owned),
        'fail_imported_only': len(imported),
        'imported_units': imported,
        'root_blame': {h: sorted(v) for h, v in
                       sorted(root_blame.items(), key=lambda kv: -len(kv[1]))},
    }


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('layer', nargs='?', default='all', choices=['s1', 's2', 'all'])
    ap.add_argument('--out', default=os.path.join(REPO, 'data', 'status', 'probe_census.json'))
    args = ap.parse_args()

    os.makedirs(OBJ_DIR, exist_ok=True)
    # Merge into any existing report so single-layer runs don't clobber
    # the other layer's results.
    report = {}
    if os.path.exists(args.out):
        try:
            prev = json.load(open(args.out, encoding='utf-8'))
            if isinstance(prev, dict):
                report = {k: prev[k] for k in prev if k in ('s1', 's2')}
        except (json.JSONDecodeError, OSError, UnicodeDecodeError):
            pass
    report['generated_at'] = datetime.now().isoformat(timespec='seconds')
    report['compiler'] = ('MSVC6 SP0 native' if NATIVE_WIN
                          else 'MSVC6 SP0 via wine') + ' (/TP /c /W3)'

    if args.layer in ('s1', 'all'):
        t0 = time.time()
        s1 = census('s1')
        ok = sum(1 for r in s1 if r['status'] == 'ok')
        report['s1'] = {
            'total': len(s1), 'ok': ok, 'fail': len(s1) - ok,
            'results': s1,
        }
        print('S1 headers: %d/%d ok  (%.0fs)' % (ok, len(s1), time.time() - t0))
        for r in s1:
            if r['status'] == 'fail':
                first = r['errors'][0] if r['errors'] else {'code': '?', 'msg': r.get('detail', '')}
                print('  FAIL %-40s %s: %s' % (r['unit'], first.get('code'), first.get('msg', '')[:90]))

    if args.layer in ('s2', 'all'):
        t0 = time.time()
        s2 = census('s2')
        summ = summarize_s2(s2)
        report['s2'] = {'total': len(s2), 'ok': summ['ok'],
                        'fail_own': summ['fail_own'],
                        'fail_imported_only': summ['fail_imported_only'],
                        'imported_units': summ['imported_units'],
                        'root_blame': summ['root_blame'],
                        'results': s2}
        print('S2 cpp: %d/%d ok | own-fail %d | imported-only %d  (%.0fs)' % (
            summ['ok'], len(s2), summ['fail_own'], summ['fail_imported_only'],
            time.time() - t0))
        print('Top root-cause headers (files blocked):')
        for h, blocked in list(summ['root_blame'].items())[:15]:
            print('  %-45s blocks %3d cpp' % (h, len(blocked)))

    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, 'w', encoding='utf-8') as f:
        json.dump(report, f, indent=1, ensure_ascii=False)
    print('report -> %s' % args.out)
    shutil.rmtree(OBJ_DIR, ignore_errors=True)


if __name__ == '__main__':
    main()


# ---------------------------------------------------------------------------
# S2：射程收窄（产出端，2026-10-10）
# ---------------------------------------------------------------------------
# 对抗复核裁决：候选集合收窄必须在**产出端**（本文件），而非 compare_pal3 消费端
# => probe_census.json 本身就是射程产物，S3 比对两份 census 更直观。
# S2 修复：同 codegen.py —— 从环境变量初始化（PROBE_ONLY=逗号分隔单元名）
_raw = os.environ.get('PROBE_ONLY')
PROBE_ONLY = set(x.strip() for x in _raw.split(',')) if _raw else None   # None=全量


def scoped_units(all_units):
    """按 PROBE_ONLY 收窄单元列表（产出端收窄）。None = 全量。"""
    if PROBE_ONLY is None:
        return all_units
    want = {os.path.basename(u) if isinstance(u, str) else u for u in PROBE_ONLY}
    return [u for u in all_units
            if (os.path.basename(u) if isinstance(u, str) else u) in want]
