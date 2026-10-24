"""增量生成正确性验证(管线改动须 TDD + 实测).

## 核心命题

**增量生成 == 全量生成**(golden hash 逐字节)

## 三个维度

| 维度 | 测试 | 判据 |
|---|---|---|
| **无遗漏** | test_dependency_closure | A 变 => 依赖闭包全变 |
| **无错误** | test_incremental_equals_full | 增量 hash == 全量 hash |
| **无不必要** | test_no_unnecessary_generation | 未变 => 文件不修改 |

## 关键洞察

**hash 相等 ≠ 语义相等**(可能漏依赖)
=> 须**差分测试**(小改 => 增量 vs 全量比对)
"""
import hashlib
import pytest
import os
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from check_incremental import compute_inputs, decide


def _hash_dir(path, pattern='.cpp'):
    h = hashlib.sha256()
    for dirpath, _, filenames in os.walk(path):
        for fn in sorted(filenames):
            if not fn.endswith(pattern):
                continue
            fp = os.path.join(dirpath, fn)
            try:
                with open(fp, 'rb') as fh:
                    h.update(fh.read())
                h.update(fp.encode())
            except OSError:
                pass
    return h.hexdigest()


def test_dependency_closure():
    """依赖闭包：annotations 变 => apply/export/codegen/probe 全跑."""
    inputs = {'annotations': 'CHANGED', 'ida_structs': 'i', 'decomp': 'd',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                       'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
    skip = decide(inputs, prev)
    # annotations 变 => 下游全变(apply→export→codegen→probe 链式)
    assert not skip, f'annotations 变应全跑,实得跳过 {skip}'


def test_dependency_closure_partial():
    """部分依赖：仅 decomp 变 => 跳过 apply/export,跑 codegen+probe."""
    inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'CHANGED',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                       'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
    skip = decide(inputs, prev)
    assert 'apply' in skip
    assert 'export' in skip
    assert 'codegen' not in skip, f'decomp 变应跑 codegen,实得跳过 {skip}'


def test_no_unnecessary_generation():
    """无不必要生成：未变 => 全跳过."""
    inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': dict(inputs)}
    skip = decide(inputs, prev)
    assert set(skip) == {'apply', 'export', 'codegen', 'probe'}, f'未变应全跳过,实得 {skip}'


@pytest.mark.slow(reason="需 2 次全量 pipeline 跑(600s x 2)—— 集成测试非 UT")
def test_incremental_equals_full_golden_hash():
    """核心判据：增量 hash == 全量 hash(golden hash 逐字节).

    ⚠️ 此测试是增量正确性**唯一判据**(与并行化同理).
    若此测试失败 => 增量**不可用**(哪怕其他测试都过).

    [R73 实现 2026-10-22·TDD 复核 must-fix ③] 真 golden hash 测试：
      1. touch 注解(小改)→ 增量跑 → hash outputs
      2. 强制全量跑(--force)→ hash outputs
      3. assert hash 相等(逐字节)
    """
    import subprocess
    import tempfile
    _state = os.path.join(ROOT, 'data', 'status', 'incremental_state.json')
    _backup = _state + '.test_backup'
    try:
        # 备份 state(测试隔离)
        if os.path.exists(_state):
            import shutil
            shutil.copy2(_state, _backup)

        # 步骤 1：增量跑(touch 注解触发)
        _ann = os.path.join(ROOT, 'data', 'annotations', 'functions.json')
        with open(_ann, 'a') as fh:
            fh.write('\n')  # touch(改 mtime)
        r1 = subprocess.run(
            ['python3', 'tools/run_pipeline_incremental.py', '--save'],
            cwd=ROOT, capture_output=True, text=True, timeout=3600)
        assert r1.returncode == 0, f'增量跑失败: {r1.stderr[:500]}'
        h1 = _hash_dir(os.path.join(ROOT, 'pal3', 'src'), pattern='.cpp')

        # 步骤 2：强制全量跑
        r2 = subprocess.run(
            ['python3', 'tools/run_pipeline_incremental.py', '--force'],
            cwd=ROOT, capture_output=True, text=True, timeout=3600)
        assert r2.returncode == 0, f'全量跑失败: {r2.stderr[:500]}'
        h2 = _hash_dir(os.path.join(ROOT, 'pal3', 'src'), pattern='.cpp')

        # 核心断言：增量 == 全量(逐字节)
        assert h1 == h2, f'增量 hash != 全量 hash：{h1} != {h2}'
    finally:
        # 恢复 state
        if os.path.exists(_backup):
            import shutil
            shutil.move(_backup, _state)


def test_pipeline_script_change_forces_all():
    """管线脚本变 => 强制全跑(用户纪律)."""
    for key in ('pipeline_gen', 'pipeline_ida', 'tools'):
        inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                  'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
        inputs[key] = 'CHANGED'
        prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                           'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
        skip = decide(inputs, prev)
        assert not skip, f'{key} 变应强制全跑'


# [R89 修 2026-10-24·崩塌复盘] 头文件树完整性纳入增量判据
# 实证：include/pal3/gen（free_functions.h/_ns_udts.h/类头）原不在任何 hash 里
#   ⇒ 头文件被删/空壳/陈旧时 codegen/probe 照常跳过 ⇒ 崩塌被掩盖（0/213 当晚不可见）
_BASE_INPUTS = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                'pal3_src': 's', 'gen_headers': 'gh',
                'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}


def test_header_tree_corruption_forces_codegen_and_probe():
    """头文件树变(decomp 未变) => codegen+probe 必须跑(自愈重生成+验证).

    场景即 2026-10-23 崩塌: free_functions.h 空壳/_ns_udts.h 顺序坏,
    decomp 未变 ⇒ 原 decide 照样跳过 codegen ⇒ 坏树不重建、不被 probe 抓.
    """
    inputs = dict(_BASE_INPUTS)
    inputs['gen_headers'] = 'CORRUPTED'
    prev = {'inputs': dict(_BASE_INPUTS)}
    skip = decide(inputs, prev)
    assert 'apply' in skip, 'annotations 未变应跳 apply'
    assert 'export' in skip, 'ida_structs 未变应跳 export'
    assert 'codegen' not in skip, f'头文件树变必须重跑 codegen 自愈,实得跳过 {skip}'
    assert 'probe' not in skip, f'头文件树变必须跑 probe 验证,实得跳过 {skip}'


def test_header_tree_unchanged_still_skips():
    """头文件树未变(含 gen_headers 键) => 全跳过(不误伤正常增量)."""
    inputs = dict(_BASE_INPUTS)
    prev = {'inputs': dict(_BASE_INPUTS)}
    skip = decide(inputs, prev)
    assert set(skip) == {'apply', 'export', 'codegen', 'probe'}, f'未变应全跳过,实得 {skip}'
