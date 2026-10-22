#!/usr/bin/env python3
"""T2-F 差分验证器（语义等价判据）。

## 背景

T2 = 语义等价（同输入 => 同行为，不要求同字节）
T2-F = 函数级差分（原版 vs 重制版）

## 判据

| 维度 | 判据 |
|---|---|
| 返回值 | 相等 |
| 语义状态 | 白名单字段相等 |
| 浮点 | ULP<=2 |
| 指针 | 对象 id（别名同 id）|
| padding | 归零 |

## 用法

    python3 tools/t2/t2_diff.py --original X --remake Y --input Z
    python3 tools/t2/t2_diff.py --state-a a.json --state-b b.json   # 直接比对快照
"""
import argparse
import json
import sys

sys.path.insert(0, 'tests/t2')
from test_normalize import _normalize_ptr_map, _zero_padding, _float_close, _norm_zero


def normalize_state(state):
    """规范化状态快照（T2-F 核心）。"""
    pm = {}
    state = _normalize_ptr_map(state, pm)
    state = _zero_padding(state)
    # 浮点归一（±0、NaN）
    for k, v in state.items():
        if isinstance(v, float):
            state[k] = _norm_zero(v)
    return state


def diff_states(a, b, ulp=2):
    """差分两个规范化状态（返回差异 dict）。"""
    na, nb = normalize_state(a), normalize_state(b)
    diffs = {}
    keys = set(na.keys()) | set(nb.keys())
    for k in sorted(keys):
        va, vb = na.get(k), nb.get(k)
        if va is None or vb is None:
            diffs[k] = (va, vb)
        elif isinstance(va, float) and isinstance(vb, float):
            if not _float_close(va, vb, ulp):
                diffs[k] = (va, vb)
        elif va != vb:
            diffs[k] = (va, vb)
    return diffs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--state-a', help='状态快照 A (JSON)')
    ap.add_argument('--state-b', help='状态快照 B (JSON)')
    ap.add_argument('--ulp', type=int, default=2)
    ap.add_argument('--expect-equal', action='store_true', help='断言相等')
    args = ap.parse_args()

    if not args.state_a or not args.state_b:
        print('ERROR: 需 --state-a 和 --state-b')
        return 2

    with open(args.state_a) as f:
        a = json.load(f)
    with open(args.state_b) as f:
        b = json.load(f)

    diffs = diff_states(a, b, ulp=args.ulp)
    if diffs:
        print(f'DIFF {len(diffs)} fields:')
        for k, (va, vb) in diffs.items():
            print(f'  {k}: {va!r} != {vb!r}')
    else:
        print('EQUAL')

    if args.expect_equal and diffs:
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
