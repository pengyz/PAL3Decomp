#!/usr/bin/env python3
"""[警告当量质量口径 2026-11-18 用户裁定] 错误数随类型完备度波动不可比——
当量分 = errors + W_EQUIV × 弹性警告族。弹性族=类型不精确时编译过、精确后
升格错误的警告: C4311/C4312(指针截断)/C4244(转换损失)/C4700(未初始化)/
C4800(int→bool)/C4090(const性)/C4047(间接级别)。

用法: python3 tools/compile_quality_metric.py [--save]
  读 data/status/probe_census.json → 输出当量分与分解; --save 更新基线。
"""
import json, re, sys, os
from collections import Counter

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CENSUS = os.path.join(REPO, 'data', 'status', 'probe_census.json')
BASELINE = os.path.join(REPO, 'data', 'status', 'quality_equiv_baseline.json')
W_EQUIV = 0.2
ELASTIC = {'C4311', 'C4312', 'C4244', 'C4700', 'C4800', 'C4090', 'C4047',
           'C4133', 'C4049', 'C4028'}


def compute(s2):
    errors = 0
    elastic_warns = 0
    hard_warns = 0
    ok = 0
    total = 0
    for r in (s2.get('results') or []):
        total += 1
        if r.get('status') == 'ok':
            ok += 1
        errors += len(r.get('errors') or [])
    # census的warnings是int计数(无码文本)——当量分用保守口径:
    #   全部警告×W_EQUIV计入弹性池(高估弹性, 但同口径可比)
    total_warns = sum(r.get('warnings') or 0 for r in (s2.get('results') or []))
    equiv = errors + W_EQUIV * total_warns
    return {'total': total, 'ok': ok, 'errors': errors, 'warnings': total_warns,
            'equiv': round(equiv, 1), 'w_equiv': W_EQUIV}


def main():
    s2 = json.load(open(CENSUS, encoding='utf-8')).get('s2') or {}
    m = compute(s2)
    print('警告当量口径 (errors + %.1f×warnings):' % m['w_equiv'])
    print('  units: %d/%d ok' % (m['ok'], m['total']))
    print('  errors: %d | warnings: %d | 当量分: %.1f' % (m['errors'], m['warnings'], m['equiv']))
    base = None
    if os.path.exists(BASELINE):
        try:
            base = json.load(open(BASELINE, encoding='utf-8'))
        except Exception:
            base = None
    if base:
        d = base['equiv'] - m['equiv']
        print('  基线(%.1f)→现在(%.1f): 当量%.1f %s' % (base['equiv'], m['equiv'], abs(d), '改善' if d > 0 else '回潮'))
        for k in ('errors', 'ok'):
            print('    %s: %d→%d' % (k, base.get(k, 0), m[k]))
    if '--save' in sys.argv:
        m['_saved_at'] = __import__('datetime').datetime.now().isoformat()
        json.dump(m, open(BASELINE, 'w', encoding='utf-8'), indent=1)
        print('基线已保存 →', BASELINE)


if __name__ == '__main__':
    main()
