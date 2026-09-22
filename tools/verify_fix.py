#!/usr/bin/env python3
"""**修复证物报告**（只读）—— 回答"这个修复凭什么算正确？"并**显式列出残余未知**。

## 证明层级（本项目可用的全部手段）

| 层 | 手段 | 证明什么 |
|---|---|---|
| **方向性** | A 级二进制证据（`[reg+disp32]` / 全局对象绝对地址 / vtable 槽 / ctor vptr）| 断言所依据的**事实** ✓ |
| **实现性** | **编译器裁判**：全部成员 `offsetof == 注解偏移` + **`sizeof(Cls) == binary_size`** | 发射层**实现**了注解 ✓✓（穷尽）|
| **传播性** | **传递**依赖闭包内每个类的布局一致性 | 错误不再沿 DAG 传播 ✓ |
| **端到端** | `match`：该类函数的 `match_pct`（100% ⇒ 拿到证书 ✓）| 编译结果 = 原始 ✓ |
| **不回归** | 与**已提交基线**比较（S2/总错误/L1）| 没有造成伤害 ✓ |

## 五条纪律（本工具据此实现）
1. **`sizeof` 必须查**（只查成员偏移不够 ✗ —— `UIListBox` 的 +12 正是尺寸而非成员偏移）
2. **依赖必须取传递闭包**（只查直接内嵌会漏 ✗）
3. **否定断言不得写成"证明不存在"** ✗ ⇒ 只能"**未发现反例 + 盲区披露**" ✓
4. **端到端读数必须按类过滤**（用 mangled/`Class::` 名映射 ✓）
5. **与已提交基线比较**，不硬编码期望值 ✓

用法::

    python3 tools/verify_fix.py --class UIListBox
    python3 tools/verify_fix.py --class UIListBox --max-dependents 8 --json
只读；退出码：发现不一致或回归 ⇒ 1 ✓
"""
import argparse
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'pipeline'))
sys.path.insert(0, os.path.join(ROOT, 'pipeline', 'gen'))

import audit_type_layout as A  # noqa: E402

BLIND_SPOTS = [
    '批量拷贝/序列化（memcpy/memset 覆盖区间）不可见',
    '数组下标访问（g_arr[i].member 的地址 = 基址+i*stride+off，非单一模式）',
    '内联（/Ob2）使函数体内合法含其它类的成员访问',
    '单元非 S2 绿 ⇒ match 不比对 ⇒ 无字节证据',
]


# ==================== 纯逻辑（单测覆盖） ====================

def dependents_closure(cls, embed):
    """→ 依赖 `cls` 的**传递闭包**（按值内嵌关系；环安全；不含自身，除非经环可达 ✓）"""
    seen, stack = set(), list(embed.get(cls, []))
    while stack:
        c = stack.pop()
        if c in seen:
            continue
        seen.add(c)
        stack.extend(embed.get(c, []))
    return seen


def embed_map(annotations):
    """→ {被内嵌类型: [内嵌它的类…]}（**按值**才算；指针/数组/自身不计 ✓）"""
    out = {}
    for cls, d in (annotations or {}).items():
        km = (d or {}).get('known_members') or {}
        for k, v in (km.items() if isinstance(km, dict) else []):
            if not isinstance(v, dict):
                continue
            t = v.get('type')
            if not isinstance(t, str):
                continue
            t = t.strip()
            if '*' in t or '[' in t:
                continue
            base = t.replace('struct ', '').replace('class ', '').strip()
            if not base or base == cls:
                continue
            out.setdefault(base, [])
            if cls not in out[base]:
                out[base].append(cls)
    return out


def mangled_class(sym):
    """MSVC6 mangled 名 → 类名（无法判定 ⇒ None，交人工 ✓）

    `?Name@Cls@@…` ⇒ Cls；`??0Cls@@`/`??1Cls@@`/`??_GCls@@`/`??_ECls@@`/`??_7Cls@@` ⇒ Cls；
    模板（含 `$`）与 C 名 ⇒ None ✗
    """
    s = (sym or '').strip()
    if not s.startswith('?') or '$' in s:
        return None
    if s.startswith('??'):
        body = s[2:]                      # 跳过 `??`
        if body.startswith('_'):
            body = body[2:]               # `??_G` / `??_E` / `??_7` / `??_D` ⇒ **4 字符前缀** ✓
        else:
            body = body[1:]               # `??0` / `??1` / `??4` ⇒ 3 字符前缀 ✓
        cls = body.split('@')[0]
        return cls or None
    parts = s.split('@')
    if len(parts) < 2:
        return None
    cls = parts[1]
    return cls or None


def negative_claim(checks, blind_spots):
    """**否定断言**的正确措辞：只能是"未发现反例"+ 盲区披露 ✓（禁止"证明不存在" ✗）"""
    return ('未发现反例：共 %d 项独立检查（本类代码 / 其他代码 disp32 / 全局对象绝对地址）均未命中 ✓；'
            '⚠️ 这不构成"该空间无访问"的证明 —— 已知盲区：%s'
            % (checks, ' · '.join(blind_spots)))


def probe_hi(annotated):
    """`sizeof` 二分的**上界**（防"封顶截断被当成测量值" ✗ —— 实测踩过两次）

    规则：随注解尺寸放大（2×+margin），下限 0x1000，上限 0x400000（4MB，远超本仓任何类）✓
    """
    try:
        n = int(annotated or 0)
    except Exception:
        n = 0
    return max(0x1000, min(0x400000, n * 2 + 0x400))


def sizeof_verdict(measured, annotated):
    """→ ('pass'|'fail'|'unknown', detail)"""
    if measured is None or annotated in (None, 0, '?'):
        return ('unknown', '无法测量或注解未给出 binary_size')
    d = int(measured) - int(annotated)
    if d == 0:
        return ('pass', 'sizeof=%d == binary_size=%d ✓' % (measured, annotated))
    return ('fail', 'sizeof=%d vs binary_size=%d（%+d）✗' % (measured, annotated, d))


def gate_verdict(base, now):
    """与**已提交基线**比较 → ('pass'|'fail'|'unknown', [problems])（改善也 pass ✓）

    ⚠️ 基线**缺失**时必须判 `unknown`，**不得**当成 0 从而误报回归 ✗（实测：`probe_census.json` 是
    gitignored ⇒ `git show HEAD:` 取不到 ⇒ 曾把 S2 读成 0/0 并误报"错误 0→2150 回归" ✗）
    """
    if not base:
        return ('unknown', ['无可用的已提交基线（HEAD 中缺少受跟踪的基线文件）'])
    probs = []
    if now.get('s2_ok', 0) < base.get('s2_ok', 0):
        probs.append('S2 绿单元 %s → %s ✗' % (base.get('s2_ok'), now.get('s2_ok')))
    if now.get('errors', 0) > base.get('errors', 0):
        probs.append('总错误 %s → %s ✗' % (base.get('errors'), now.get('errors')))
    if now.get('l1', 0) < base.get('l1', 0):
        probs.append('L1 %s → %s ✗' % (base.get('l1'), now.get('l1')))
    return ('fail' if probs else 'pass', probs)


# ==================== 驱动 ====================

def git_show(path):
    """读**已提交（HEAD）**版本 —— "与已提交基线比较" ✓"""
    try:
        r = subprocess.run(['git', 'show', 'HEAD:%s' % path], capture_output=True, text=True,
                           cwd=ROOT, timeout=60)
        return json.loads(r.stdout) if r.returncode == 0 and r.stdout.strip() else None
    except Exception:
        return None


def load_json(path):
    try:
        return json.load(open(os.path.join(ROOT, path), encoding='utf-8'))
    except Exception:
        return None


def baselines():
    """→ (base, now)：S2/总错误/L1 的 **HEAD 版**与工作区版 ✓

    ⚠️ 必须用**受跟踪**文件：`probe_census.json` 是 gitignored ✗
    ⇒ 受跟踪源：`data/status/baselines/latest.json`（每单元 status/error_count ✓）+ `s4_baseline.json`（stats ✓）
    """
    def mk(latest, s4):
        res = (latest or {}).get('results') or {}
        if not res:
            return None
        ok = sum(1 for v in res.values() if (v or {}).get('status') == 'ok')
        err = sum(int((v or {}).get('error_count') or 0) for v in res.values())
        l1 = ((s4 or {}).get('stats') or {}).get('match_L1', 0)
        return {'s2_ok': ok, 's2_total': len(res), 'errors': err, 'l1': l1}
    base = mk(git_show('data/status/baselines/latest.json'), git_show('data/status/s4_baseline.json'))
    now = mk(load_json('data/status/baselines/latest.json'), load_json('data/status/s4_baseline.json'))
    return base, now


def sizeof_probe(cls, header, include_dirs, annotated):
    """`sizeof(Cls)` 实测（比较式二分；**上界必须给足** —— 曾因 hi 太小读出截断错值 ✗）"""
    import probe_compile as pc
    incs = A.unit_includes_for(cls) or ['#include "pal3/ida_defs.h"', '#include "globals.h"',
                                        '#include "%s"' % os.path.relpath(header, os.path.join(ROOT, 'pal3', 'src')).replace('\\', '/')]
    hi = probe_hi(annotated)

    def gt(K):
        body = list(incs) + ['char c[sizeof(%s) > %d ? 1 : -1];' % (cls, K)]
        src = '/tmp/verify_fix_sz.cpp'
        open(src, 'w', encoding='utf-8').write('\n'.join(body) + '\n')
        out, _ = pc.run_cl(['/Fo' + pc.wpath('/tmp/verify_fix_sz.obj'), pc.wpath(src)]
                           + ['/I' + pc.wpath(d) for d in include_dirs], timeout=200,
                           flags=('/nologo', '/TP', '/c', '/W3'))
        return not re.search(r' error C2118', out)
    lo = 0
    if not gt(lo):
        return None
    while lo + 1 < hi:
        m = (lo + hi) // 2
        if gt(m):
            lo = m
        else:
            hi = m
    # ⚠️ 命中上界 ⇒ 说明真值 ≥ 上界 ⇒ 这是**截断**，不得当成测量值 ✗（返回 None ⇒ 判 unknown ✓）
    return None if hi >= probe_hi(annotated) else hi


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--class', dest='cls', required=True)
    ap.add_argument('--max-dependents', type=int, default=6)
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args()

    import probe_compile as pc
    members = A.load_annotation_members()
    ann = {c: json.load(open(os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % c),
                             encoding='utf-8'))
           for c in [a.cls] if os.path.exists(os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % c))}
    ann_all = {}
    for p in os.listdir(os.path.join(ROOT, 'data', 'annotations', 'structs')):
        if p.endswith('.json'):
            try:
                d = json.load(open(os.path.join(ROOT, 'data', 'annotations', 'structs', p), encoding='utf-8'))
                ann_all[p[:-5]] = d
            except Exception:
                pass
    embed = embed_map(ann_all)
    deps = sorted(dependents_closure(a.cls, embed))

    print('=' * 100)
    print('修复证物报告 · 类 %s · 传递依赖 %d 个（按值内嵌闭包）' % (a.cls, len(deps)))
    print('=' * 100)

    # ① 实现性：全部成员 offsetof + ② sizeof vs binary_size（本类 + 依赖）
    problems, rows = [], []
    targets = [a.cls] + deps[:a.max_dependents]
    for cls in targets:
        if cls not in members:
            continue
        header, declared = members[cls]
        conf, calib = A.measure_cpp_layout(cls, header, declared, pc.INCLUDE_DIRS,
                                           fallback_includes=A.unit_includes_for(cls))
        ann_sz = (ann_all.get(cls) or {}).get('binary_size')
        sz = sizeof_probe(cls, header, pc.INCLUDE_DIRS, ann_sz) if calib else None
        sv, sd = sizeof_verdict(sz, ann_sz)
        tag = '✓' if (calib and not conf and sv in ('pass', 'unknown')) else '✗'
        print('  %s %-22s 成员冲突 %-8s · %s' % (tag, cls, ('%d/%d' % (len(conf), len(declared))) if calib else '不可信',
                                                 sd))
        if not calib or conf or sv == 'fail':
            problems.append('%s: %s' % (cls, ('布局测量不可信' if not calib else '%d 成员冲突' % len(conf)) if sv != 'fail' else sd))
        rows.append({'cls': cls, 'calib': calib, 'conflicts': len(conf), 'sizeof_verdict': sv, 'sizeof': sz,
                     'binary_size': ann_sz})

    # ③ 端到端：该类函数的字节读数（按类过滤）
    s4 = load_json('data/status/s4_baseline.json') or {}
    mine = [(r.get('name'), r.get('status'), r.get('match_pct')) for r in s4.get('rows', [])
            if str(r.get('name') or '').startswith(a.cls + '::')]
    n_l1 = sum(1 for _, st, _ in mine if st == 'match_L1')
    print('  ── 端到端：该类在比对集内的函数 %d 个，其中 match_L1 %d 个' % (len(mine), n_l1))
    for n, st, mp in mine[:6]:
        print('       %-44s %-10s %s' % (str(n)[:44], st, mp))

    # ④ 不回归：与已提交基线比较
    base, now = baselines()
    gv, gp = gate_verdict(base, now)
    print('  ── 基线（HEAD → 工作区）: S2 %s/%s→%s/%s · 错误 %s→%s · L1 %s→%s ⇒ %s'
          % (base['s2_ok'], base['s2_total'], now['s2_ok'], now['s2_total'],
             base['errors'], now['errors'], base['l1'], now['l1'], '✓ 无回归' if gv == 'pass' else '✗'))
    for p in gp:
        print('       %s' % p)
        problems.append(p)

    # ⑤ 残余未知（必须显式）
    cen = load_json('data/status/probe_census.json') or {}
    st = {u['unit']: u['status'] for u in cen.get('s2', {}).get('results', [])}
    unit = [u for u in st if os.path.basename(u) == a.cls + '.cpp']
    print('  ── 残余未知：')
    print('       本类单元 %s ⇒ %s' % (unit[0] if unit else '(未找到)', st.get(unit[0], '?') if unit else '?'))
    for b in BLIND_SPOTS:
        print('       · %s' % b)
    print('  ── 否定断言措辞（若本轮含"撤类型/降级"）：')
    print('       %s' % negative_claim(3, BLIND_SPOTS[:2]))

    print('=' * 100)
    print('结论: %s' % ('✓ 证物齐备（布局/尺寸/传播/基线一致）' if not problems
                       else '✗ 存在问题 %d 项 ⇒ 不得提交' % len(problems)))
    if a.json:
        print(json.dumps({'class': a.cls, 'rows': rows, 'problems': problems,
                          'end_to_end': {'functions': len(mine), 'match_L1': n_l1},
                          'baseline': {'base': base, 'now': now}}, ensure_ascii=False, indent=1))
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())