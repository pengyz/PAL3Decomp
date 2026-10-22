#!/usr/bin/env python3
"""增量检查（hash + timestamp）—— 跳过未变更阶段。

## 为什么（2026-10-21 用户思路）

IDA 管线耗时：apply 11s → export **151s** → codegen **200s** → probe
⇒ 每次全跑 6+ 分钟。若 annotation 未变，export/codegen 是**冗余的**。

## 增量规则

| 阶段 | 输入 | 跳过条件 |
|---|---|---|
| apply | `data/annotations/` | annotations hash 未变 |
| export | `data/annotations/` + `asm/pal3/ida_structs.json` | 上游 hash 未变 |
| codegen | `asm/pal3/decomp/` | decomp hash 未变 |
| probe | `pal3/src/` | codegen 输出未变 |

## 实现

  `data/status/incremental_state.json` 记录上次各阶段的输入 hash
  每次跑前比对：hash 一致 ⇒ 跳过该阶段及下游

## 用法
    python3 tools/check_incremental.py           # 报告可跳过的阶段
    python3 tools/check_incremental.py --apply   # 跑 apply 前先查
"""
import argparse
import hashlib
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STATE = os.path.join(ROOT, 'data', 'status', 'incremental_state.json')


def _hash_dir(path, pattern='.json'):
    """目录下指定后缀文件的 **内容级 hash**。

    [R73 修 2026-10-22·TDD 复核 must-fix ②] 原 mtime+size 可伪造
    （同 size 改内容 + mtime 还原 = 漏检）⇒ 改内容级 hash。
    """
    h = hashlib.sha256()
    items = []
    for dirpath, _, filenames in os.walk(path):
        for fn in sorted(filenames):
            if pattern != '*' and not fn.endswith(pattern):
                continue
            fp = os.path.join(dirpath, fn)
            try:
                with open(fp, 'rb') as fh:
                    content = fh.read()
                items.append((fp, content))
            except OSError:
                pass
    for fp, content in sorted(items):
        h.update(fp.encode())
        h.update(content)
    return h.hexdigest()


def _hash_file(path):
    if not os.path.exists(path):
        return 'missing'
    try:
        with open(path, 'rb') as fh:
            content = fh.read()
        return hashlib.sha256(path.encode() + content).hexdigest()
    except OSError:
        return 'error'


def compute_inputs():
    # [R60 用户纪律] **管线脚本改动必须强制重生成**
    # 否则增量会用旧逻辑（改了 stage1-5/emit_headers 等但 hash 未含 ⇒ 跳过 codegen = 错）
    # [R73 修 2026-10-22·TDD 复核 must-fix ①] hash 覆盖 13 项漏项
    # 漏掉 pipeline/cli.py / phase2/overlay / cmake/toolchain 等 ⇒ 改这些文件不会强制全跑
    return {
        # 数据输入
        'annotations': _hash_dir(os.path.join(ROOT, 'data', 'annotations'), pattern='.json'),
        'ida_structs': _hash_file(os.path.join(ROOT, 'asm', 'pal3', 'ida_structs.json')),
        'decomp': _hash_dir(os.path.join(ROOT, 'asm', 'pal3', 'decomp'), pattern='.json'),
        'pal3_src': _hash_dir(os.path.join(ROOT, 'pal3', 'src'), pattern='.cpp'),
        # 管线脚本（改动 ⇒ 全阶段强制重生成）
        'pipeline_gen': _hash_dir(os.path.join(ROOT, 'pipeline', 'gen'), pattern='.py'),
        'pipeline_ida': _hash_dir(os.path.join(ROOT, 'pipeline', 'ida'), pattern='.py'),
        'pipeline_cli': _hash_file(os.path.join(ROOT, 'pipeline', 'cli.py')),
        'pipeline_other': _hash_dir(os.path.join(ROOT, 'pipeline'), pattern='.py'),
        'tools': _hash_dir(os.path.join(ROOT, 'tools'), pattern='.py'),
        # phase2 overlay（手工 fix ⇒ 影响 codegen 输出）
        'phase2_overlay': _hash_dir(os.path.join(ROOT, 'phase2'), pattern='*'),
        # 构建配置（影响编译）
        'cmake_toolchain': _hash_file(os.path.join(ROOT, 'cmake', 'toolchain-vc6.cmake')),
        'pal3_cmake': _hash_file(os.path.join(ROOT, 'pal3', 'CMakeLists.txt')),
    }


def load_state():
    try:
        with open(STATE, encoding='utf-8') as fh:
            return json.load(fh)
    except (OSError, ValueError):
        return {}


def save_state(inputs):
    import time
    state = {'inputs': inputs, 'updated_at': time.strftime('%Y-%m-%dT%H:%M:%S')}
    os.makedirs(os.path.dirname(STATE), exist_ok=True)
    with open(STATE, 'w', encoding='utf-8') as fh:
        json.dump(state, fh, ensure_ascii=False, indent=2)
    return state


def decide(inputs, prev):
    """返回可跳过的阶段列表。"""
    prev_in = (prev or {}).get('inputs') or {}
    skip = []
    # [R60 用户纪律] 管线脚本变 ⇒ **强制全重生成**（不跳过任何阶段）
    script_changed = any(
        prev_in.get(k) != inputs.get(k)
        for k in ('pipeline_gen', 'pipeline_ida', 'tools')
    )
    if script_changed:
        return []  # 全跑
    # apply: annotations 未变
    if prev_in.get('annotations') == inputs.get('annotations'):
        skip.append('apply')
        # export: apply 可跳过 + ida_structs 未变
        if prev_in.get('ida_structs') == inputs.get('ida_structs'):
            skip.append('export')
            # codegen: export 可跳过 + decomp 未变
            if prev_in.get('decomp') == inputs.get('decomp'):
                skip.append('codegen')
                # probe: codegen 可跳过 + src 未变
                if prev_in.get('pal3_src') == inputs.get('pal3_src'):
                    skip.append('probe')
    return skip


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--apply', action='store_true', help='跑 apply 前查')
    ap.add_argument('--save', action='store_true', help='保存当前 hash 为新基线')
    ap.add_argument('--json', action='store_true')
    args = ap.parse_args()

    inputs = compute_inputs()
    prev = load_state()
    skip = decide(inputs, prev)

    if args.save:
        save_state(inputs)
        print('✅ 已保存增量基线')

    script_changed = any(
        (prev.get('inputs') or {}).get(k) != inputs.get(k)
        for k in ('pipeline_gen', 'pipeline_ida', 'tools')
    )
    out = {
        'inputs': {k: v[:12] for k, v in inputs.items()},
        'prev_inputs': {k: (v or '')[:12] for k, v in ((prev.get('inputs') or {}).items())},
        'script_changed': script_changed,
        'skip_stages': skip,
        'must_run': [s for s in ('apply', 'export', 'codegen', 'probe') if s not in skip],
    }
    if args.json:
        print(json.dumps(out, ensure_ascii=False, indent=2))
    else:
        print('=== 增量检查 ===')
        for k, v in out['inputs'].items():
            pv = out['prev_inputs'].get(k, '无')
            mark = '✓' if v == pv else '✗ 变更'
            print(f'  {k:14} {v}  (prev {pv})  {mark}')
        if out['script_changed']:
            print('\n⚠️ **管线脚本变更** ⇒ 强制全重生成（不跳过任何阶段）')
        print(f'\n可跳过: {skip or "无（全跑）"}')
        print(f'须运行: {out["must_run"]}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
