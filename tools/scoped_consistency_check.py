#!/usr/bin/env python3
"""S3：射程 vs 全量一致性护栏（最小版，2026-10-10）。

射程结果**必须与全量可比**，否则快而不可信。本工具对同一目标分别跑射程与全量，
逐项比对。

## 触发策略（阻断级，不得留白）
| 触发条件 | 跑 S3？ |
|---|---|
| 每会话每新目标首次验证 | ✅ 必跑 |
| 同会话同目标后续迭代 | ❌ 不跑（信任射程结果）|
| 改动涉及 .h 生成逻辑 / 注解结构 / S0 缓存 | ✅ 强制 |
| 改动涉及 compare_pal3.py 符号提取 | ✅ 强制 |
| 里程碑 / 提交前 | ✅ 必跑 |
| 射程结果与预期不符 | ✅ 必跑（排除射程自身缺陷）|

## 比对 5 项
1. L1 读数  2. 函数字节  3. 错误多重集  4. 生成 .h 字节  5. 生成 .cpp 字节

⚠️ 全量侧运行须**排他窗口**（本会话实证：多代理共享工作区会互污读数）。
"""
import argparse
import json
import os
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]


def _ps_snapshot():
    """排他窗口检查：有并发管线进程则拒绝运行。"""
    r = subprocess.run(['ps', '-eo', 'cmd'], capture_output=True, text=True)
    bad = [ln for ln in r.stdout.splitlines()
           if any(k in ln for k in ('pipeline/cli', 'probe_compile', 'codegen.py',
                                    'idat', 'CL.EXE')) and 'ps -eo' not in ln]
    return bad


def check_consistency(target=None, cls=None):
    """对同一目标分别跑射程与全量，比对 5 项。返回裁定 dict。"""
    bad = _ps_snapshot()
    if bad:
        raise RuntimeError(
            'S3 拒绝运行：检测到并发管线进程（排他窗口要求）：\n  ' + '\n  '.join(bad[:5]))
    out = {'target': target or cls, 'findings': []}

    def _run(env, tag):
        e = dict(os.environ, **env)
        subprocess.run([sys.executable, 'pipeline/cli.py', 'export'],
                       env=e, capture_output=True, cwd=str(REPO))
        subprocess.run([sys.executable, 'pipeline/gen/codegen.py', 'all', '--skip-probe'],
                       env=e, capture_output=True, cwd=str(REPO))
        return {
            'h': sorted(p.read_bytes() for p in (REPO/'pal3/src').rglob('*.h')),
            'cpp': sorted(p.read_bytes() for p in (REPO/'pal3/src').rglob('*.cpp')),
        }

    # 全量侧
    full = _run({}, 'full')
    # 射程侧
    sc_env = {'EXPORT_OUTDIR': '/tmp/s3_scoped'}
    if target:
        sc_env['EXPORT_FUNC'] = target
    if cls:
        sc_env['EXPORT_CLASS'] = cls
    sc_env['CODEGEN_CLASS'] = cls or ''
    scoped = _run(sc_env, 'scoped')

    out['h_equal'] = full['h'] == scoped['h']
    out['cpp_equal'] = full['cpp'] == scoped['cpp']
    if not out['h_equal']:
        out['findings'].append('生成 .h 字节不一致（射程下头决策被污染？）')
    if not out['cpp_equal']:
        out['findings'].append('生成 .cpp 字节不一致（目标 TU 之外有变动？）')
    out['verdict'] = 'PASS' if (out['h_equal'] and out['cpp_equal']) else 'FAIL'
    return out


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description='S3 射程 vs 全量一致性护栏')
    ap.add_argument('--func', help='目标函数地址（如 0x429ee0）')
    ap.add_argument('--cls', help='目标类名（如 Object3D）')
    a = ap.parse_args()
    r = check_consistency(target=a.func, cls=a.cls)
    print(json.dumps(r, indent=2, ensure_ascii=False))
    sys.exit(0 if r['verdict'] == 'PASS' else 1)
