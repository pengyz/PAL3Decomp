"""One-at-a-time size-update landing with probe verification.

For each (class, size): edit structs JSON -> codegen headers -> probe S1+S2.
Keep if S1 >= baseline and S2 >= baseline; else revert and restore headers.
Baseline: S1 731/751, S2 49/197.
"""
import json, subprocess, sys, os
from pathlib import Path

ROOT = Path(__file__).parent.parent
UPDATES = [
    ('UIStatic', 248),
    ('CCBUIPanel', 22112),
    ('UISceneFrm', 3288),
    ('UITitle_ArcSave', 4004),
    ('JusticeBookUI', 56192),
    ('UIRoleSelectDialog', 2204),
    ('CScreenMode', 5496),
    ('UIListBox', 1760),
]
BASE_S1, BASE_S1_TOTAL = 731, 751
BASE_S2, BASE_S2_TOTAL = 49, 197
PY = sys.executable


def run(cmd, timeout=420):
    r = subprocess.run([PY] + cmd, capture_output=True, text=True,
                       errors='replace', cwd=str(ROOT), timeout=timeout)
    return r.returncode, r.stdout + '\n' + r.stderr


def codegen_headers():
    return run([str(ROOT / 'pipeline' / 'cli.py'), 'codegen', 'headers', '--no-snapshot'])


def probe(layer):
    rc, out = run([str(ROOT / 'pipeline' / 'probe_compile.py'), layer], timeout=420)
    import re
    if layer == 's1':
        m = re.search(r'S1 headers: (\d+)/(\d+)', out)
        return (int(m.group(1)), int(m.group(2))) if m else (0, 0)
    m = re.search(r'S2 cpp: (\d+)/(\d+)', out)
    return (int(m.group(1)), int(m.group(2))) if m else (0, 0)


def set_size(cls, size):
    p = ROOT / 'data' / 'annotations' / 'structs' / ('%s.json' % cls)
    d = json.loads(p.read_text(encoding='utf-8'))
    d['binary_size'] = size
    p.write_text(json.dumps(d, ensure_ascii=False, indent=1) + '\n', encoding='utf-8')


results = []
for cls, size in UPDATES:
    set_size(cls, size)
    codegen_headers()
    s1 = probe('s1')
    s2 = probe('s2')
    ok = s1[0] >= BASE_S1 and s2[0] >= BASE_S2
    if ok:
        results.append((cls, size, 'KEPT', s1, s2))
        print('[KEPT] %-20s size=%d  S1=%d/%d S2=%d/%d' % (cls, size, s1[0], s1[1], s2[0], s2[1]))
    else:
        # revert to HEAD (original size) and restore headers
        subprocess.run(['git', 'checkout', '--', 'data/annotations/structs/%s.json' % cls], cwd=str(ROOT))
        codegen_headers()
        results.append((cls, size, 'REVERTED', s1, s2))
        print('[REVERTED] %-20s size=%d  S1=%d/%d S2=%d/%d' % (cls, size, s1[0], s1[1], s2[0], s2[1]))

print('\n=== SUMMARY ===')
for r in results:
    print(r)
json.dump([{'class': r[0], 'size': r[1], 'verdict': r[2], 's1': r[3], 's2': r[4]} for r in results],
          open(ROOT / 'data' / 'status' / '_size_landing_report.json', 'w'), indent=1)
