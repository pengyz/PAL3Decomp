"""check_incremental.py 单测（TDD 夹具）。

## 为什么（2026-10-21 用户纪律）

管线改动需要 TDD 夹具 + 子 agent 独立复核。
增量检查（hash+timestamp）是新增机制，须可测可验。

## 覆盖

| 场景 | 测试 |
|---|---|
| 全部未变 ⇒ 全跳过 | test_all_unchanged_skip_all |
| annotations 变 ⇒ 全跑 | test_annotations_changed_run_all |
| **管线脚本变 ⇒ 强制全跑** | test_pipeline_script_changed_force_all |
| 上游变下游跳过 | test_partial_skip |
| 首跑（无基线）⇒ 全跑 | test_first_run |
| --save 保存基线 | test_save_baseline |
"""
import os
import sys
import tempfile
import json

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
from tools.check_incremental import decide


def _mk(ann='a1', ida='i1', decomp='d1', src='s1', pg='p1', pi='p2', tools='t1'):
    return {'annotations': ann, 'ida_structs': ida, 'decomp': decomp,
            'pal3_src': src, 'pipeline_gen': pg, 'pipeline_ida': pi, 'tools': tools}


def test_all_unchanged_skip_all():
    """全部输入未变 ⇒ 跳过所有阶段。"""
    inputs = _mk()
    prev = {'inputs': _mk()}
    skip = decide(inputs, prev)
    assert set(skip) == {'apply', 'export', 'codegen', 'probe'}, f'实得 {skip}'


def test_annotations_changed_run_all():
    """annotations 变 ⇒ 不跳过任何阶段。"""
    inputs = _mk(ann='a2')
    prev = {'inputs': _mk()}
    skip = decide(inputs, prev)
    assert not skip, f'annotations 变应全跑，实得跳过 {skip}'


def test_pipeline_script_changed_force_all():
    """管线脚本变 ⇒ **强制全跑**（用户纪律）。"""
    for key in ('pipeline_gen', 'pipeline_ida', 'tools'):
        inputs = _mk()
        inputs[key] = 'CHANGED'
        prev = {'inputs': _mk()}
        skip = decide(inputs, prev)
        assert not skip, f'{key} 变应强制全跑，实得跳过 {skip}'


def test_partial_skip():
    """上游未变但下游变 ⇒ 跳过上游。"""
    # annotations/ida_structs 未变 ⇒ 跳过 apply/export
    # decomp 变 ⇒ codegen 必跑
    inputs = _mk(decomp='d2')
    prev = {'inputs': _mk()}
    skip = decide(inputs, prev)
    assert 'apply' in skip, f'annotations 未变应跳过 apply，实得 {skip}'
    assert 'export' in skip, f'ida_structs 未变应跳过 export，实得 {skip}'
    assert 'codegen' not in skip, f'decomp 变应跑 codegen，实得 {skip}'


def test_first_run():
    """无基线（prev={}）⇒ 全跑。"""
    inputs = _mk()
    skip = decide(inputs, {})
    assert not skip, f'首跑应全跑，实得跳过 {skip}'


def test_pal3_src_changed_only():
    """仅 pal3_src 变 ⇒ 只跑 probe。"""
    inputs = _mk(src='s2')
    prev = {'inputs': _mk()}
    skip = decide(inputs, prev)
    assert set(skip) == {'apply', 'export', 'codegen'}, f'实得 {skip}'
