#!/usr/bin/env python3
"""增量管线执行（降验证成本 10x）。

## 为什么（2026-10-22 对抗性复核 C 最强证据）

验证链 ≈ 生成链 **53×**：
  生成：apply 11.3s（一次性）
  验证：export 151s + codegen 200s + probe 60s + match 186s = **596s**（每次）

540 基线快照 = 540 轮 × 360s = **54h 纯机器等待**
30% 误判 = **16h 白烧**

## 增量规则（7 项输入 hash）

| 输入 | 变化 ⇒ 跳过 |
|---|---|
| annotations | 未变 ⇒ 跳过 apply+export |
| ida_structs | 未变 ⇒ 跳过 export |
| decomp | 未变 ⇒ 跳过 codegen |
| pal3_src | 未变 ⇒ 跳过 probe |
| pipeline_gen/ida/tools | **变 ⇒ 强制全跑**（用户纪律）|

## 用法

    python3 tools/run_pipeline_incremental.py           # 智能增量
    python3 tools/run_pipeline_incremental.py --force    # 强制全跑
    python3 tools/run_pipeline_incremental.py --check    # 只查不跑
"""
import argparse
import os
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from check_incremental import compute_inputs, load_state, save_state, decide


def run_stage(name, cmd, timeout=1800):
    """跑一个阶段，计时。"""
    t0 = time.time()
    print(f'\n=== [{name}] ===')
    r = subprocess.run(cmd, shell=True, cwd=ROOT, timeout=timeout)
    dt = time.time() - t0
    print(f'=== [{name}] rc={r.returncode} {dt:.1f}s ===')
    return r.returncode, dt


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--force', action='store_true', help='强制全跑')
    ap.add_argument('--check', action='store_true', help='只查不跑')
    ap.add_argument('--save', action='store_true', help='保存当前 hash 为新基线')
    args = ap.parse_args()

    inputs = compute_inputs()
    prev = load_state()
    skip = decide(inputs, prev)

    if args.force:
        skip = []

    must_run = [s for s in ('apply', 'export', 'codegen', 'probe') if s not in skip]

    print('=== 增量管线 ===')
    print(f'可跳过: {skip or "无（全跑）"}')
    print(f'须运行: {must_run}')

    if args.check:
        return 0

    if not must_run:
        print('\n✅ 无变更，跳过全部阶段')
        return 0

    total = 0
    if 'apply' in must_run:
        rc, dt = run_stage('apply', 'python3 pipeline/cli.py apply')
        total += dt
        if rc != 0:
            return rc
    if 'export' in must_run:
        rc, dt = run_stage('export', 'python3 pipeline/cli.py export', timeout=3600)
        total += dt
        if rc != 0:
            return rc
    if 'codegen' in must_run:
        rc, dt = run_stage('codegen', 'python3 pipeline/cli.py codegen all --skip-probe')
        total += dt
        if rc != 0:
            return rc
    if 'probe' in must_run:
        rc, dt = run_stage('probe', 'python3 pipeline/cli.py probe s2')
        total += dt

    print(f'\n=== 总耗时 {total:.1f}s ===')
    if args.save:
        save_state(inputs)
        print('✅ 已保存增量基线')
    return 0


if __name__ == '__main__':
    sys.exit(main())
