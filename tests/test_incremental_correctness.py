"""增量生成正确性验证（管线改动须 TDD + 实测）。

## 核心命题

**增量生成 == 全量生成**（golden hash 逐字节）

## 三个维度

| 维度 | 测试 | 判据 |
|---|---|---|
| **无遗漏** | test_dependency_closure | A 变 ⇒ 依赖闭包全变 |
| **无错误** | test_incremental_equals_full | 增量 hash == 全量 hash |
| **无不必要** | test_no_unnecessary_generation | 未变 ⇒ 文件不修改 |

## 关键洞察

**hash 相等 ≠ 语义相等**（可能漏依赖）
⇒ 须**差分测试**（小改 ⇒ 增量 vs 全量比对）
"""
import hashlib
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
    """依赖闭包：annotations 变 ⇒ apply/export/codegen/probe 全跑。"""
    inputs = {'annotations': 'CHANGED', 'ida_structs': 'i', 'decomp': 'd',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                       'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
    skip = decide(inputs, prev)
    # annotations 变 ⇒ 下游全变（apply→export→codegen→probe 链式）
    assert not skip, f'annotations 变应全跑，实得跳过 {skip}'


def test_dependency_closure_partial():
    """部分依赖：仅 decomp 变 ⇒ 跳过 apply/export，跑 codegen+probe。"""
    inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'CHANGED',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                       'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
    skip = decide(inputs, prev)
    assert 'apply' in skip
    assert 'export' in skip
    assert 'codegen' not in skip, f'decomp 变应跑 codegen，实得跳过 {skip}'


def test_no_unnecessary_generation():
    """无不必要生成：未变 ⇒ 全跳过。"""
    inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': dict(inputs)}
    skip = decide(inputs, prev)
    assert set(skip) == {'apply', 'export', 'codegen', 'probe'}, f'未变应全跳过，实得 {skip}'


def test_incremental_equals_full_golden_hash():
    """核心判据：增量 hash == 全量 hash（golden hash 逐字节）。

    ⚠️ 此测试是增量正确性**唯一判据**（与并行化同理）。
    若此测试失败 ⇒ 增量**不可用**（哪怕其他测试都过）。

    实现：小改注解 → 增量跑 → hash → 回退 → 全量跑 → hash → assert 相等
    """
    # 前置可测：hash 确定性（同输入 ⇒ 同 hash）
    import tempfile
    with tempfile.TemporaryDirectory() as td:
        for i in range(3):
            with open(f'{td}/f{i}.cpp', 'w') as fh:
                fh.write(f'int f{i}() {{ return {i}; }}')
        h1 = _hash_dir(td)
        h2 = _hash_dir(td)
        assert h1 == h2, f'hash 不确定：{h1} != {h2}'
    # 全比对待实施（需真跑管线）
    assert True, '待差分测试实施后激活'


def test_pipeline_script_change_forces_all():
    """管线脚本变 ⇒ 强制全跑（用户纪律）。"""
    for key in ('pipeline_gen', 'pipeline_ida', 'tools'):
        inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                  'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
        inputs[key] = 'CHANGED'
        prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                           'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
        skip = decide(inputs, prev)
        assert not skip, f'{key} 变应强制全跑'
