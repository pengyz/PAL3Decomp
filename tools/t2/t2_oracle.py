#!/usr/bin/env python3
"""T2 oracle（原版 PAL3.exe 可执行 + 4 通道捕获）。

## 背景

T2 = 语义等价（同输入 => 同行为，不要求同字节）
oracle = 原版 PAL3.exe（wine 跑）作为「真值」

## 4 通道捕获

| 通道 | 内容 | 用途 |
|---|---|---|
| 返回值 | 进程 exit code | 函数级差分 |
| stdout/stderr | 标准输出 | 诊断 |
| 存档字节 | save 文件（T2-IO 保留 T1）| 精确相等 |
| 截图 | 画面（T2-Frame）| 截图 diff |

## 确定性门槛

同输入连跑 2 次 canonical hash 全等才准入语料（防 flaky）

## 用法

    python3 tools/t2/t2_oracle.py --input X --output-dir Y
    python3 tools/t2/t2_oracle.py --verify-deterministic --input X
"""
import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ORIGINAL = os.path.join(ROOT, 'original', 'PAL3.exe')


def canonical_hash(artifacts):
    """canonical hash（排序键 + 内容）。"""
    h = hashlib.sha256()
    for k in sorted(artifacts.keys()):
        v = artifacts[k]
        h.update(k.encode())
        if isinstance(v, bytes):
            h.update(v)
        else:
            h.update(str(v).encode())
    return h.hexdigest()


def run_oracle(input_path, output_dir, timeout=30):
    """跑原版 PAL3.exe，4 通道捕获。"""
    if not os.path.exists(ORIGINAL):
        return {'error': f'original/PAL3.exe not found'}

    os.makedirs(output_dir, exist_ok=True)
    artifacts = {}

    # 1. 返回值 + stdout/stderr（wine 跑）
    try:
        env = os.environ.copy()
        env['WINEDEBUG'] = '-all'
        env['WINEPREFIX'] = os.path.join(ROOT, '.wine-t2')  # 隔离 prefix
        r = subprocess.run(
            ['wine', ORIGINAL],
            capture_output=True, timeout=timeout, env=env, cwd=ROOT)
        artifacts['exit_code'] = r.returncode
        artifacts['stdout'] = r.stdout
        artifacts['stderr'] = r.stderr
    except subprocess.TimeoutExpired:
        artifacts['exit_code'] = 'timeout'
    except Exception as e:
        return {'error': f'oracle run failed: {e}'}

    # 2. 存档字节（save 文件）
    save_path = os.path.join(ROOT, 'original', 'save')
    if os.path.exists(save_path):
        with open(save_path, 'rb') as f:
            artifacts['save_bytes'] = f.read()

    # 3. 截图（待实施：wine + 截图工具）
    artifacts['screenshot'] = None  # TODO

    return artifacts


def verify_deterministic(input_path, runs=2):
    """确定性验证：同输入连跑 N 次，canonical hash 全等。"""
    hashes = []
    for i in range(runs):
        out_dir = f'/tmp/t2_oracle_{i}'
        if os.path.exists(out_dir):
            shutil.rmtree(out_dir)
        result = run_oracle(input_path, out_dir)
        if 'error' in result:
            return {'error': result['error']}
        # 只 hash 确定性部分（不含时间戳/路径）
        det = {k: v for k, v in result.items() if k not in ('screenshot',)}
        hashes.append(canonical_hash(det))

    if len(set(hashes)) == 1:
        return {'deterministic': True, 'hash': hashes[0]}
    else:
        return {'deterministic': False, 'hashes': hashes}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--input', help='输入（脚本/边界值）')
    ap.add_argument('--output-dir', default='/tmp/t2_oracle')
    ap.add_argument('--verify-deterministic', action='store_true')
    ap.add_argument('--timeout', type=int, default=30)
    args = ap.parse_args()

    if args.verify_deterministic:
        result = verify_deterministic(args.input)
        print(json.dumps(result, indent=2, default=str))
        return 0 if result.get('deterministic') else 1

    if not args.input:
        print('ERROR: 需 --input')
        return 2

    result = run_oracle(args.input, args.output_dir, args.timeout)
    if 'error' in result:
        print(f'ERROR: {result["error"]}')
        return 1

    print(f'exit_code: {result.get("exit_code")}')
    print(f'stdout: {len(result.get("stdout", b""))} bytes')
    print(f'stderr: {len(result.get("stderr", b""))} bytes')
    print(f'canonical_hash: {canonical_hash({k: v for k, v in result.items() if k != "screenshot"})}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
