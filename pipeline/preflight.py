#!/usr/bin/env python3
"""管线状态预检 / 基线一致性（**只读**，秒级）。

## 为什么存在（2026-09-21）

管线有**三份互不相干的"基线真相源"**，实测它们互相矛盾：

| 文件 | 记录 | 谁在消费 |
|---|---|---|
| `data/status/compile_baseline.json` | S2 `76/206` | `tools/compile_regression.py`（`codegen all` 内部调用）|
| `data/status/baselines/latest.json` | S2 `75/205` | `tools/regression_detector.py`（`probe` 内部调用）|
| `data/status/s4_baseline.json` | `match_L1` `38` | `pipeline/compare_pal3.py` 的 L1 棘轮 |

后果：在干净 HEAD 上 `codegen all` 与 `match` **恒 exit 1**（都是陈旧棘轮造成的假失败），
于是**自动化循环无法区分信号与噪声** ✗ —— 这是"不可持续"的根因之一。
本模块把这三份状态、以及"哪些门禁已知恒红"，**在一个命令里如实打印**出来。

**它不做任何写入、不做任何刷新** —— 刷新棘轮基线是决策，必须由人显式执行
（`python3 tools/compile_regression.py --update-baseline` 等）。

用法::

    python3 pipeline/cli.py status            # 人读
    python3 pipeline/cli.py status --strict   # 基线不一致 ⇒ exit 1（给脚本用）
    python3 pipeline/preflight.py             # 等价
"""
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STATUS = os.path.join(REPO, 'data', 'status')

# 阶段顺序 = 一次完整迭代的**唯一权威顺序**（按依赖，不可乱序）
STAGES = [
    ('apply',   'annotations → work IDB'),
    ('export',  'IDB → Hex-Rays decomp JSON'),
    ('codegen', 'decomp JSON → pal3/src（含内部 S2 普查 + compile_regression）'),
    ('probe',   'S1/S2 全量编译普查 + regression_detector 对账'),
    ('match',   'S4 字节匹配裁判 + L1 棘轮'),
]
SECONDS_GATE = 'python3 pipeline/cli.py check   # 秒级闸（实测 ~2.3s，不进 IDB）'


def _load(path):
    try:
        with open(path, encoding='utf-8') as f:
            return json.load(f)
    except Exception:
        return None


def collect_state(status_dir=None):
    """收集当前状态（**只读**，不抛异常：缺失的文件以 None 表示）。"""
    sd = status_dir or STATUS
    st = {'status_dir': sd}

    cen = _load(os.path.join(sd, 'probe_census.json'))
    if isinstance(cen, dict) and isinstance(cen.get('s2'), dict):
        s2 = cen['s2']
        errs = sum(len(u.get('errors') or []) for u in (s2.get('results') or []))
        st['live_s2'] = {'ok': s2.get('ok'), 'total': s2.get('total'), 'errors': errs,
                         'generated_at': cen.get('generated_at')}
    else:
        st['live_s2'] = None

    for key, fn in (('compile_baseline', 'compile_baseline.json'),
                    ('latest_baseline', os.path.join('baselines', 'latest.json')),
                    ('s4_baseline', 's4_baseline.json')):
        st[key] = _load(os.path.join(sd, fn))

    st['loop_last'] = _load(os.path.join(sd, '_loop_last.json'))
    return st


def _s2_of_compile_baseline(d):
    s2 = (d or {}).get('s2')
    if isinstance(s2, dict):
        return s2.get('ok'), s2.get('total')
    return None, None


def _s2_of_latest(d):
    res = (d or {}).get('results')
    if isinstance(res, dict):
        return sum(1 for v in res.values() if v.get('status') == 'ok'), len(res)
    return None, None


def _loop_match(state):
    """`_loop_last.json` 里 match 阶段的读数。

    ⚠️ 形状是 `{'stages': {'match': {...}}}` —— 2026-09-21 实测踩到：
    我按 `{'match': {...}}` 写了读取与 fixture，两者**一致地错**，
    于是单测全绿而 `--expect-l1` 在真实文件上恒报 `实得 None` ✗
    （同 `docs/knowledge/gotcha_plan_code_snippets_must_be_validated_on_real_input.md`）。
    """
    ll = state.get('loop_last') or {}
    stages = ll.get('stages') if isinstance(ll.get('stages'), dict) else {}
    m = stages.get('match') if isinstance(stages.get('match'), dict) else {}
    return m


def _l1_of_s4(d):
    """`s4_baseline.json` 的 L1 棘轮值：在 `stats.match_L1`（顶层 `match_L1`/`L1` 作后备）。"""
    d = d or {}
    st = d.get('stats') if isinstance(d.get('stats'), dict) else {}
    for src in (st, d):
        for k in ('match_L1', 'L1', 'l1'):
            if src.get(k) is not None:
                return src[k]
    return None


def baseline_rows(state):
    """三方对照（**纯函数**，便于单测）：每行 {name, ok, total, note}。"""
    cb = state.get('compile_baseline')
    lb = state.get('latest_baseline')
    sb = state.get('s4_baseline')
    cok, ctot = _s2_of_compile_baseline(cb)
    lok, ltot = _s2_of_latest(lb)
    return [
        {'name': 'compile_baseline.json', 'ok': cok, 'total': ctot,
         'note': 'tools/compile_regression.py（codegen all 内部）',
         'timestamp': (cb or {}).get('timestamp')},
        {'name': 'baselines/latest.json', 'ok': lok, 'total': ltot,
         'note': 'tools/regression_detector.py（probe 内部）',
         'timestamp': (lb or {}).get('timestamp')},
        {'name': 's4_baseline.json', 'ok': None, 'total': None,
         'note': 'L1 棘轮=%s（pipeline/compare_pal3.py）' % _l1_of_s4(sb),
         'timestamp': (sb or {}).get('timestamp') or (sb or {}).get('generated_at')},
    ]


def known_red_gates(state):
    """**已知恒红**的门禁（纯函数）：在干净 HEAD 上也会 exit 1 —— 自动化循环必须先知道。"""
    rows = baseline_rows(state)
    cok, ctot = rows[0]['ok'], rows[0]['total']
    lok, ltot = rows[1]['ok'], rows[1]['total']
    out = []
    if cok is not None and lok is not None and (cok, ctot) != (lok, ltot):
        out.append({
            'gate': 'codegen all → compile_regression',
            'recorded': '%s/%s' % (cok, ctot), 'live_baseline': '%s/%s' % (lok, ltot),
            'why': 'compile_baseline.json 陈旧（文件集变化被当成回归）',
            'fix': 'python3 tools/compile_regression.py --update-baseline  # 棘轮决策，需人确认',
        })
    sb = state.get('s4_baseline') or {}
    ratchet = _l1_of_s4(sb)
    live_l1 = _loop_match(state).get('L1')
    if ratchet is not None and live_l1 is not None and live_l1 < ratchet:
        out.append({
            'gate': 'match → L1 棘轮',
            'recorded': str(ratchet), 'live_baseline': str(live_l1),
            'why': 's4_baseline.json 的 L1 上限来自更早的树（棘轮只显式前进）',
            'fix': '确认无退化后显式推进棘轮（见 pipeline/compare_pal3.py 的 ratchet 分支）',
        })
    elif ratchet is not None and live_l1 is None:
        out.append({
            'gate': 'match → L1 棘轮（待测）',
            'recorded': str(ratchet), 'live_baseline': '未知',
            'why': '尚无本次 loop 的 L1 读数；status 只能显示记录值',
            'fix': '跑一次 python3 pipeline/cli.py loop（或在 match 输出里读 "L1 <n>"）',
        })
    return out


def parse_expect(s2=None, errors=None, l1=None):
    """解析 `--expect-s2 75/205` / `--expect-errors 2150` / `--expect-l1 35`（纯函数）。"""
    exp = {}
    if s2:
        m = re.match(r'^\s*(\d+)\s*/\s*(\d+)\s*$', str(s2))
        if not m:
            raise ValueError('--expect-s2 需要 OK/TOTAL 形式，如 75/205；收到 %r' % s2)
        exp['s2'] = (int(m.group(1)), int(m.group(2)))
    if errors is not None:
        exp['errors'] = int(errors)
    if l1 is not None:
        exp['l1'] = int(l1)
    return exp


def check_expectations(state, exp):
    """对照期望（纯函数）→ 失败原因列表（空 = 全部满足）。"""
    fails = []
    live = state.get('live_s2') or {}
    if 's2' in exp:
        got = (live.get('ok'), live.get('total'))
        if got != exp['s2']:
            fails.append('S2 期望 %s/%s，实得 %s/%s' % (exp['s2'][0], exp['s2'][1], got[0], got[1]))
    if 'errors' in exp:
        if live.get('errors') != exp['errors']:
            fails.append('总错误期望 %d，实得 %s' % (exp['errors'], live.get('errors')))
    if 'l1' in exp:
        got_l1 = _loop_match(state).get('L1')
        if got_l1 != exp['l1']:
            fails.append('L1 期望 %d，实得 %s' % (exp['l1'], got_l1))
    return fails


def render(state, width=78):
    """人读报告（纯函数）。"""
    L = []
    L.append('=' * width)
    L.append('管线状态预检（只读；不刷新任何基线）')
    L.append('=' * width)
    L.append('')
    L.append('一次完整迭代的唯一权威顺序（**不可乱序**）：')
    ll = (state.get('loop_last') or {}).get('stages') or {}
    for i, (name, desc) in enumerate(STAGES, 1):
        secs = (ll.get(name) or {}).get('secs')
        L.append('  %d. %-8s %-46s %s' % (i, name, desc,
                                           ('实测 %ss' % secs) if secs is not None else ''))
    L.append('  秒级闸（进管线前先用）: %s' % SECONDS_GATE)
    if not ll:
        L.append('  （尚无本次迭代的实测耗时；跑一次 `loop` 会写入 data/status/_loop_last.json）')
    L.append('')

    live = state.get('live_s2')
    L.append('当前普查（data/status/probe_census.json）：')
    if live:
        L.append('  S2 %s/%s · 总错误 %s · %s' % (live['ok'], live['total'],
                                                 live['errors'], live.get('generated_at')))
    else:
        L.append('  (缺失)')
    L.append('')

    L.append('⚠️ 基线"真相源"（**三方互不相干**，全部只读展示）：')
    rows = baseline_rows(state)
    for r in rows:
        s2 = ('S2 %s/%s' % (r['ok'], r['total'])) if r['ok'] is not None else r['note']
        if r['ok'] is not None:
            s2 = 'S2 %-8s | %s' % ('%s/%s' % (r['ok'], r['total']), r['note'])
        L.append('  %-26s %s' % (r['name'], s2))
        if r.get('timestamp'):
            L.append('  %-26s   @ %s' % ('', r['timestamp']))
    cok, ctot = rows[0]['ok'], rows[0]['total']
    lok, ltot = rows[1]['ok'], rows[1]['total']
    if cok is not None and lok is not None:
        if (cok, ctot) == (lok, ltot):
            L.append('  ⇒ 两份 S2 基线**一致** ✓')
        else:
            L.append('  ⇒ ❌ **两份 S2 基线互相矛盾**（%s/%s vs %s/%s）' % (cok, ctot, lok, ltot))
    L.append('')

    red = known_red_gates(state)
    L.append('已知恒红门禁（%d 条）—— 自动化循环必须先知道它们，否则分不清信号与噪声：' % len(red))
    if not red:
        L.append('  （无）✓')
    for g in red:
        L.append('  ❌ %s' % g['gate'])
        L.append('       记录 %s / 实况 %s —— %s' % (g['recorded'], g['live_baseline'], g['why']))
        L.append('       处理: %s' % g['fix'])
    L.append('')
    L.append('提示：`python3 pipeline/cli.py loop` = 一次跑完上述 5 阶段（可选 --expect-* 断言基线）；')
    L.append('=' * width)
    return '\n'.join(L)


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    state = collect_state()
    print(render(state))
    strict = '--strict' in argv
    rows = baseline_rows(state)
    inconsistent = rows[0]['ok'] is not None and rows[1]['ok'] is not None and \
        (rows[0]['ok'], rows[0]['total']) != (rows[1]['ok'], rows[1]['total'])
    if strict and (inconsistent or known_red_gates(state)):
        print('[status --strict] 基线不一致或存在恒红门禁 ⇒ exit 1')
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())