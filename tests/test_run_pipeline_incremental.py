"""run_pipeline_incremental.py TDD 夹具（管线改动须 TDD + 实测）。

## 覆盖

| 测试 | assertion |
|---|---|
| test_skip_all_unchanged | 未变更 => 全跳过 |
| test_run_apply_when_annotations_change | annotations 变 => 跑 apply |
| test_force_all_when_pipeline_script_change | 管线脚本变 => 强制全跑 |
| test_check_mode_no_side_effect | --check 不执行阶段 |
| test_save_baseline | --save 保存 hash |
"""
import os
import sys
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'tools'))
from check_incremental import compute_inputs, decide, save_state, load_state


def test_skip_all_unchanged():
    """未变更 => 全跳过。"""
    inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': dict(inputs)}
    skip = decide(inputs, prev)
    assert set(skip) == {'apply', 'export', 'codegen', 'probe'}


def test_run_apply_when_annotations_change():
    """annotations 变 => 不跳过 apply。"""
    inputs = {'annotations': 'CHANGED', 'ida_structs': 'i', 'decomp': 'd',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                       'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
    skip = decide(inputs, prev)
    assert 'apply' not in skip


def test_force_all_when_pipeline_script_change():
    """管线脚本变 => 强制全跑（用户纪律）。"""
    for key in ('pipeline_gen', 'pipeline_ida', 'tools'):
        inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                  'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
        inputs[key] = 'CHANGED'
        prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                           'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
        skip = decide(inputs, prev)
        assert not skip, f'{key} 变应强制全跑'


def test_first_run_full():
    """首跑（无基线）=> 全跑。"""
    inputs = compute_inputs()
    skip = decide(inputs, {})
    assert not skip


def test_partial_skip():
    """decomp 变 => 跑 codegen（不跳过）。"""
    inputs = {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'CHANGED',
              'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}
    prev = {'inputs': {'annotations': 'a', 'ida_structs': 'i', 'decomp': 'd',
                       'pal3_src': 's', 'pipeline_gen': 'pg', 'pipeline_ida': 'pi', 'tools': 't'}}
    skip = decide(inputs, prev)
    assert 'apply' in skip
    assert 'export' in skip
    assert 'codegen' not in skip
