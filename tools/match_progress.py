"""match_progress — L1 进度作战图（spec v2 §1.1·oot retail_progress 借鉴）。

同源校验（fail-loud·复核实证硬伤）：s4_baseline 与 s4_diff_detail 实测不同源
（stats.match_L1=161 vs detail.l1=110·1 函数状态相反）⇒ 跨文件聚合前必校验，
不等即拒（禁自欺读数）。L1 权威=s4_baseline（rows status 计数 == stats.match_L1
内部自洽断言·键名写死）。数据零新采集：只读三份既有 status 文件。
"""
import json
import re
import sys
from collections import Counter

_BASE = 'data/status/s4_baseline.json'
_DET = 'data/status/s4_diff_detail.json'
_CEN = 'data/status/probe_census.json'


def check_same_source(baseline, detail):
    """跨文件同源 + 同文件自洽 → (ok, msg)。复核硬伤①：不同源禁聚合。
    域感知（自验修正）：detail.units=其覆盖域——全局标量差混范围差
    （161=域内103+域外58）⇒ 域内对账为准 + 状态相反逐行检测。"""
    stats = baseline.get('stats') or {}
    rows = baseline.get('rows') or []
    n_all = sum(1 for r in rows if r.get('status') == 'match_L1')
    if n_all != stats.get('match_L1'):
        return False, ('同文件自洽破坏: rows match_L1 计数=%d != stats.match_L1=%s'
                       % (n_all, stats.get('match_L1')))
    units = detail.get('units') or {}
    if units:
        dom = set(units)
        n = sum(1 for r in rows if r.get('file') in dom
                and r.get('status') == 'match_L1')
        got = detail.get('l1')
        if n != got:
            return False, ('域内不同源: baseline∈detail域 match_L1=%d vs '
                           'detail.l1=%d（同域仍差=非范围差·疑棘轮回写）' % (n, got))
        # 状态相反逐行检测（复核实证 1 例 0x4420C0）
        for r in rows:
            if r.get('file') not in dom:
                continue
            for dr in units.get(r['file']) or []:
                if dr.get('va') != r.get('va') or dr.get('n_diff') is None:
                    continue
                d_st = 'match_L1' if dr['n_diff'] == 0 else 'partial'
                if r.get('status') in ('match_L1', 'partial') and d_st != r['status']:
                    return False, ('状态相反 %s: baseline=%s detail=%s(n_diff=%d)'
                                   % (r.get('va'), r.get('status'), d_st, dr['n_diff']))
        return True, 'same-source ok (域内 match_L1=%s·状态一致)' % got
    want = stats.get('match_L1')
    if want != detail.get('l1'):
        return False, ('不同源禁聚合: s4_baseline.stats.match_L1=%s vs '
                       's4_diff_detail.l1=%s' % (want, detail.get('l1')))
    return True, 'same-source ok (match_L1=%s)' % want


def _top_error(errors_field):
    """census errors JSON 串 → 出现最多的错误码（无则 '-'）。"""
    try:
        errs = json.loads(errors_field or '[]')
    except ValueError:
        return '-'
    codes = []
    for e in errs:
        if isinstance(e, str):
            codes.append(e.split()[0])
        elif isinstance(e, dict):
            codes.append(str(e.get('code') or e.get('msg') or '?').split()[0])
    return Counter(codes).most_common(1)[0][0] if codes else '-'


def build_progress(baseline, census):
    """聚合 → {units: [...], totals}（L1 列总和断言==stats.match_L1·键名写死）。"""
    rows = baseline.get('rows') or []
    want = (baseline.get('stats') or {}).get('match_L1')
    n = sum(1 for r in rows if r.get('status') == 'match_L1')
    if n != want:
        raise ValueError('rows match_L1 计数=%d != stats.match_L1=%s（同文件账不符禁出表）'
                         % (n, want))
    per = {}
    for r in rows:
        u = r.get('file') or '?'
        d = per.setdefault(u, {'unit': u, 'l1': 0, 'partial': 0, 'other': 0})
        st = r.get('status')
        if st == 'match_L1':
            d['l1'] += 1
        elif st == 'partial':
            d['partial'] += 1
        else:
            d['other'] += 1
    s2 = {}
    for r in ((census.get('s2') or {}).get('results') or []):
        s2[r.get('unit')] = r
    out = []
    for u, d in per.items():
        c = s2.get(u) or {}
        out.append({'unit': u, 's2': c.get('status') or 'not-in-census',
                    'l1': d['l1'], 'partial': d['partial'], 'other': d['other'],
                    'top_error': _top_error(c.get('errors')) if c else '-'})
    for u in s2:                       # 有 census 无 baseline 行的 unit
        if u not in per:
            c = s2[u]
            out.append({'unit': u, 's2': c.get('status'), 'l1': 0, 'partial': 0,
                        'other': 0, 'top_error': _top_error(c.get('errors'))})
    out.sort(key=lambda x: (-x['partial'], -x['other'], x['unit']))
    assert sum(x['l1'] for x in out) == want, 'L1 列总和 != stats.match_L1'
    return {'units': out,
            'totals': {'l1': want, 'partial': sum(x['partial'] for x in out),
                       'units': len(out)}}


def main(argv):
    baseline = json.load(open(_BASE))
    detail = json.load(open(_DET))
    ok, msg = check_same_source(baseline, detail)
    if not ok:
        print('FAIL: %s' % msg, file=sys.stderr)
        return 1
    print('same-source: %s' % msg)
    census = json.load(open(_CEN))
    p = build_progress(baseline, census)
    print('%-46s %-10s %4s %7s %6s %s' % ('unit', 'S2', 'L1', 'partial', 'other', 'top_err'))
    for u in p['units']:
        print('%-46s %-10s %4d %7d %6d %s' % (
            u['unit'][:46], u['s2'][:10], u['l1'], u['partial'], u['other'], u['top_error']))
    print('TOTAL: l1=%(l1)d partial=%(partial)d units=%(units)d' % p['totals'])
    with open('data/status/match_progress.json', 'w') as fh:
        json.dump(p, fh, ensure_ascii=False, indent=1)
    print('→ data/status/match_progress.json')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
