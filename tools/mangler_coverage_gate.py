#!/usr/bin/env python3
"""unmatched 率棘轮门禁（plan-1to5 §487 · 2026-11-03）。
- evaluate_coverage(): 判定纯函数（R15 单测锁定）
- CLI: --check（默认）/ --rebaseline "<理由>"（重锚须理由，link_census 同纪律）
语料=mangler_bench 当前 obj 集；退化=率升 ⇒ exit 1 且不刷新基线。"""
import argparse, json, os, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASELINE = os.path.join(ROOT, 'data', 'status', 'mangler_coverage.json')


def evaluate_coverage(matched, unmatched, baseline):
    total = matched + unmatched
    if total == 0:
        return {'ok': False, 'reason': 'empty-corpus'}
    rate = unmatched / total
    if not baseline:
        return {'ok': True, 'reason': 'first-run', 'rate': rate}
    bt = baseline['matched'] + baseline['unmatched']
    brate = baseline['unmatched'] / bt if bt else 0.0
    if rate <= brate + 1e-9:
        return {'ok': True, 'reason': 'improved' if rate < brate else 'held', 'rate': rate}
    return {'ok': False, 'reason': 'rate-worse', 'rate': rate, 'baseline_rate': brate}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--matched', type=int, required=True)
    ap.add_argument('--unmatched', type=int, required=True)
    ap.add_argument('--rebaseline', default=None, help='重锚理由（空=棘轮模式）')
    a = ap.parse_args()
    base = json.load(open(BASELINE)) if os.path.exists(BASELINE) else None
    v = evaluate_coverage(a.matched, a.unmatched, base)
    print('unmatched率门禁: %s (%s) rate=%.4f' % ('PASS' if v['ok'] else 'FAIL', v['reason'], v.get('rate', -1)))
    if a.rebaseline:
        json.dump({'matched': a.matched, 'unmatched': a.unmatched, 'reason': a.rebaseline},
                  open(BASELINE, 'w'), indent=1)
        print('基线重锚（理由: %s）→ %s' % (a.rebaseline, BASELINE))
        return 0
    if not v['ok']:
        print('  率恶化：修复 mangler 或 --rebaseline "<理由>" 显式重锚')
        return 1
    if base is None:
        json.dump({'matched': a.matched, 'unmatched': a.unmatched, 'reason': 'first-run'},
                  open(BASELINE, 'w'), indent=1)
        print('首跑建档 → %s' % BASELINE)
    return 0


if __name__ == '__main__':
    sys.exit(main())
