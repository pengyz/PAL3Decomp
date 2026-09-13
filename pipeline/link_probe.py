#!/usr/bin/env python3
"""Link-layer probe census for PAL3 decompilation (verification ladder step 3).

S1/S2 prove each unit compiles standalone (/c). This probe adds the LINK
layer: compile every S2-passing .cpp to .obj, then hand them all to the
bundled MSVC6 LINK.EXE together with the platform libs, and classify the
fallout:

  LNK2005 (duplicate symbol)          -> ODR violations across TUs
  LNK2001/LNK2019 (unresolved extern) -> missing definitions (CRT boundary,
                                         extern mismatch, undefined globals)
  LNK1104 / others                    -> environment/toolchain issues

Linking is NOT expected to succeed yet; the census turns "does the whole
program link" from a holistic unknown into a monotone metric (unresolved
count, duplicate count) that shrinks as annotations/codegen converge.

Usage:  python3 pipeline/link_probe.py [--limit N] [--keep-objs]
Output: data/status/link_census.json (+ human summary on stdout)
"""

import argparse
import json
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict
from datetime import datetime
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO / 'pipeline'))

import probe_compile as pc  # noqa: E402  (run_cl, INCLUDE_DIRS, wpath, OBJ_DIR, NATIVE_WIN)

CENSUS = REPO / 'data' / 'status' / 'probe_census.json'
OUT_JSON = REPO / 'data' / 'status' / 'link_census.json'
LINK_EXE = REPO / 'tools' / 'compilers' / 'msvc6.0' / 'Bin' / 'LINK.EXE'
LIB_DIRS = [
    REPO / 'tools' / 'compilers' / 'msvc6.0' / 'Lib',
    REPO / 'tools' / 'vc6' / 'Lib',
]
# Platform libs the game imports (kernel/user/gdi/winmm...); CRT comes from
# the vc6 Lib dir via the linker's default lookup.
PLATFORM_LIBS = ['kernel32.lib', 'user32.lib', 'gdi32.lib', 'winmm.lib']

LNK_RE = re.compile(r'^(?P<where>.+?)\s*:\s*(?P<fatal>fatal )?error (?P<code>LNK\d+):\s*(?P<msg>.*)$')


def run_link(obj_paths, out_exe):
    cmd = [str(LINK_EXE)] if pc.NATIVE_WIN else ['wine', pc.wpath(str(LINK_EXE))]
    args = ['/nologo', '/OUT:' + pc.wpath(out_exe), '/SUBSYSTEM:WINDOWS',
            '/MACHINE:I386']
    for lib in PLATFORM_LIBS:
        args.append('/DEFAULTLIB:' + lib)
    for d in LIB_DIRS:
        args.append('/LIBPATH:' + pc.wpath(str(d)))
    args += [pc.wpath(p) for p in obj_paths]
    try:
        proc = subprocess.run(cmd + args, capture_output=True, text=True,
                              errors='replace', timeout=600, cwd=str(REPO))
        return proc.stdout + '\n' + proc.stderr
    except OSError as e:
        return 'link spawn failed: %s' % e


def parse_link_output(text):
    """Return (by_code, unresolved_symbols, duplicates).

    unresolved_symbols: symbol -> set of 'where' strings that reference it
    duplicates:         symbol -> list of 'where' strings that define it
    """
    by_code = Counter()
    unresolved = defaultdict(set)
    duplicates = defaultdict(list)
    for line in text.splitlines():
        m = LNK_RE.match(line.strip())
        if not m:
            continue
        code, msg, where = m.group('code'), m.group('msg'), m.group('where')
        by_code[code] += 1
        if code == 'LNK2001' or code == 'LNK2019':
            sm = re.search(r'"?(?P<sym>[^"]+)"?(?: referenced in function "?(?P<fn>[^"]+)"?)?$',
                           msg)
            sym = sm.group('sym').strip() if sm else msg.strip()
            unresolved[sym].add(where)
        elif code == 'LNK2005':
            dm = re.search(r'"?(?P<sym>[^"]+)"? already defined in (?P<other>.+)', msg)
            if dm:
                duplicates[dm.group('sym').strip()].append(dm.group('other').strip())
            else:
                duplicates[msg.strip()].append(where)
    return by_code, unresolved, duplicates


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--census', default=str(CENSUS))
    ap.add_argument('--limit', type=int, default=0,
                    help='only link the first N S2-passing units')
    ap.add_argument('--keep-objs', action='store_true',
                    help='keep the scratch .obj directory for inspection')
    args = ap.parse_args()

    census = json.loads(Path(args.census).read_text())
    passing = [r['unit'] for r in census['s2']['results'] if r['status'] == 'ok']
    if args.limit:
        passing = passing[:args.limit]
    print('S2-passing units to link: %d' % len(passing))
    if not passing:
        print('nothing to link')
        return 1

    obj_dir = os.path.join(pc.OBJ_DIR, 'link')
    os.makedirs(obj_dir, exist_ok=True)

    obj_paths, skipped = [], []
    for n, unit in enumerate(passing, 1):
        src = str(REPO / unit)
        obj = os.path.join(obj_dir, '%d.obj' % (abs(hash(unit)) % 10 ** 8))
        out, hard = pc.run_cl(
            ['/Fo' + pc.wpath(obj), pc.wpath(src)]
            + ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS], timeout=180)
        if hard or not os.path.exists(obj):
            skipped.append((unit, hard or 'no obj'))
            continue
        obj_paths.append(obj)
    print('compiled %d/%d objs (%d skipped)' % (len(obj_paths), len(passing), len(skipped)))

    out_exe = os.path.join(obj_dir, 'pal3_link_probe.exe')
    print('linking %d objs ...' % len(obj_paths))
    text = run_link(obj_paths, out_exe)

    by_code, unresolved, duplicates = parse_link_output(text)

    print('\n=== link census ===')
    print('linker errors by code:', dict(by_code.most_common()))
    print('unresolved external symbols: %d (referenced by %d sites)' % (
        len(unresolved), sum(len(v) for v in unresolved.values())))
    for sym, wheres in sorted(unresolved.items(), key=lambda kv: -len(kv[1]))[:15]:
        print('  %3dx  %s' % (len(wheres), sym[:70]))
    print('duplicate definitions: %d symbols' % len(duplicates))
    for sym, defs in sorted(duplicates.items(), key=lambda kv: -len(kv[1]))[:10]:
        print('  %s (%d defs)' % (sym[:60], len(defs) + 1))

    if not args.keep_objs:
        import shutil
        shutil.rmtree(obj_dir, ignore_errors=True)

    OUT_JSON.parent.mkdir(parents=True, exist_ok=True)
    OUT_JSON.write_text(json.dumps({
        'generated_at': datetime.now().isoformat(timespec='seconds'),
        'units_linked': len(obj_paths), 'units_skipped': len(skipped),
        'skipped': [{'unit': u, 'detail': d} for u, d in skipped],
        'errors_by_code': dict(by_code),
        'unresolved': {s: sorted(w) for s, w in
                       sorted(unresolved.items(), key=lambda kv: -len(kv[1]))},
        'duplicates': {s: sorted(set(d)) for s, d in
                       sorted(duplicates.items(), key=lambda kv: -len(kv[1]))},
    }, indent=1, ensure_ascii=False))
    print('report -> %s' % OUT_JSON)
    return 0


if __name__ == '__main__':
    sys.exit(main())
