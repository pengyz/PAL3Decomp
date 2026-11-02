"""E2E 一键判（规则: docs/specs/2026-11-02-e2e-fixture-rules.md §5）
D1 布局对账 · D2 编译桶白名单 · D3 渲染语义钉 · D4 对拍（IDA 轨挂位）
用法: python3 ghidra_track/fixture/run_e2e.py <case-id>"""
import json, os, re, subprocess, sys
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CASE = os.path.join(ROOT, 'ghidra_track/fixture/cases', sys.argv[1])
OUT = os.path.join(ROOT, 'ghidra_track/out', sys.argv[1])
os.makedirs(OUT, exist_ok=True)
def load(p): return json.load(open(p))
def sh(cmd): return subprocess.run(cmd, shell=True, capture_output=True, text=True)
rep = {'case': sys.argv[1], 'D1': {}, 'D2': {}, 'D3': {}, 'D4': 'pending-ida-track'}

# ---- fixture 编译+运行（冒烟）----
src = os.path.join(CASE, 'src', 'fixture.cpp')
r = sh('g++ -std=c++98 -O0 -o %s %s' % (os.path.join(OUT, 'fixture'), src))
smoke = sh(os.path.join(OUT, 'fixture'))
rep['smoke'] = {'compile_ok': r.returncode == 0, 'run': smoke.stdout.strip()[:80]}

# ---- D1a: layout 机测 vs expected ----
layout_src = os.path.join(CASE, 'src', 'layout_dump.cpp')
if os.path.exists(layout_src):
    sh('g++ -std=c++98 -o %s %s' % (os.path.join(OUT, 'layout_dump'), layout_src))
    act = {}
    for ln in sh(os.path.join(OUT, 'layout_dump')).stdout.splitlines():
        m = re.match(r'^SIZE (\w+) (\d+)', ln) or re.match(r'^(\w+) (\w+) (\d+)', ln)
        if ln.startswith('SIZE '):
            _, n, s = ln.split(); act[n] = {'size': int(s), 'members': act.get(n, {}).get('members', {})}
        else:
            parts = ln.split()
            if len(parts) == 3 and not ln.startswith('SIZE'):
                act.setdefault(parts[0], {'size': 0, 'members': {}})['members'][parts[1]] = int(parts[2])
    exp = load(os.path.join(CASE, 'expected', 'layout.json'))
    diffs = []
    for n, e in exp.items():
        if not isinstance(e, dict) or 'size' not in e: continue
        a = act.get(n)
        if not a or a['size'] != e['size']:
            diffs.append({'struct': n, 'kind': 'size', 'exp': e['size'], 'act': a and a['size']})
        for mn, mo in e.get('members', {}).items():
            if a and a['members'].get(mn) != mo:
                diffs.append({'struct': n, 'kind': 'offset:' + mn, 'exp': mo, 'act': a['members'].get(mn)})
    rep['D1']['layout'] = 'PASS' if not diffs else diffs

# ---- D1c + 出码: ghidra apply（生成 plan 后）----
plan = os.path.join(ROOT, 'ghidra_track/out', sys.argv[1] + '_plan.json')
if os.path.exists(plan):
    gh = os.path.join(ROOT, 'tools/ghidra/ghidra_12.1.2_PUBLIC')
    env = 'GHIDRA_INSTALL_DIR=%s ' % gh
    # fixture exe 导入（幂等：已存在跳过）
    sh('%s/support/analyzeHeadless %s PAL3_FX -import %s' % (
        gh, os.path.join(ROOT, 'ghidra_track/ghidra_proj'), os.path.join(OUT, 'fixture')))
    sh(env + 'python3.10 ghidra_track/apply_plan.py %s PAL3_FX /fixture %s %s' % (
        os.path.join(ROOT, 'ghidra_track/ghidra_proj'), plan, os.path.join(OUT, 'slice')))
    aj = os.path.join(OUT, 'apply_report.json')
    if os.path.exists(aj):
        a = load(aj)
        rep['D1']['sizeof_reconcile'] = 'PASS' if not a.get('sizeof_mismatch') else a['sizeof_mismatch']
        slice_dir = os.path.join(OUT, 'slice')
        units = [f for f in os.listdir(slice_dir) if f.endswith('.c')] if os.path.isdir(slice_dir) else []
        # ---- D2: 编译桶 ----
        isms = os.path.join(slice_dir, 'ghidra_isms.h')
        if units:
            tdir = os.path.join(CASE, 'annotations')
            # 复用 types.h 生成（case 注解）
            sh('python3 %s %s %s' % (os.path.join(ROOT, 'ghidra_track/fixture/gen_types.py'),
               tdir, os.path.join(slice_dir, 'types.h')))
            cat = os.path.join(slice_dir, 'all_units.cc')
            with open(cat, 'w') as w:
                w.write('#include "types.h"\n#include "ghidra_isms.h"\n')
                for f in units:
                    w.write(open(os.path.join(slice_dir, f)).read())
            cc = sh('g++ -fsyntax-only -fpermissive %s 2>&1 | grep -c "error:"' % cat)
            errs = sh('g++ -fsyntax-only -fpermissive %s 2>&1 | grep "error:"' % cat).stdout
            buckets = {'noise-missing-src': 0, 'ghidra-ism': 0, 'transform-broken': 0, 'annotation-signal': 0}
            for ln in errs.splitlines():
                if re.search(r'\b(LAB|FUN|DAT)_\w+ .*undeclared|unknown type name .undefined', ln):
                    if 'undefined' in ln: buckets['ghidra-ism'] += 1
                    else: buckets['noise-missing-src'] += 1
                elif re.search(r'constructor|code\*|template|::', ln):
                    buckets['transform-broken'] += 1
                elif re.search(r'no member|has no member|cannot convert|invalid', ln):
                    buckets['annotation-signal'] += 1
                else: buckets['transform-broken'] += 1
            exp2 = load(os.path.join(CASE, 'expected', 'compile.json'))
            allowed = exp2.get('allowed_buckets', {})
            verdict = {k: {'count': v, 'allowed': allowed.get(k, 0), 'ok': v <= allowed.get(k, 0) if k != 'annotation-signal' else v == 0}
                       for k, v in buckets.items()}
            rep['D2'] = {'total_errors': int(cc.stdout.strip() or 0), 'buckets': verdict,
                         'D2': 'PASS' if all(x['ok'] for x in verdict.values()) else 'FAIL'}
        # ---- D3: 渲染钉 ----
        rj = load(os.path.join(CASE, 'expected', 'render.json'))
        results = []
        allc = ''.join(open(os.path.join(slice_dir, f)).read() for f in units) if units else ''
        for a in rj.get('assertions', []):
            if 'regex' in a:
                ok = bool(re.search(a['regex'], allc))
            elif 'count_min' in a:
                ok = len(re.findall(r'\bcalc\b', allc)) >= a['count_min']
            else: ok = False
            results.append({'id': a['id'], 'ok': ok})
        rep['D3'] = results
outp = os.path.join(CASE, 'report.json')
json.dump(rep, open(outp, 'w'), indent=1)
print(json.dumps(rep, indent=1)[:1500])
