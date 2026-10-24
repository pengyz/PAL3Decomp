"""free_functions.h 写出位置契约（R90·2026-10-24 恢复会话）。

## 背景（C1083 ×152 实证）

free_functions.h 是唯一跟随 cfg.output_headers（机器本地 gitignored 的
pipeline.toml）漂移的产物，而**全部消费者只认 pal3/src**：

- 发射的 include 是裸名 `#include "free_functions.h"`（5d96faefb 起）
- probe /I = include、pal3/src、编译器 Include —— 无 include/pal3/gen
- stage5_fixup._load_free_func_names() 硬编码读 pal3/src/free_functions.h

本机 toml 漂到 include/pal3/gen ⇒ 头文件写进无人引用的地址 ⇒ C1083 ×152。
漂移源头 = cli.py/config.py 的 toml 引导模板写死 include/pal3/gen。

## 契约

1. **pal3/src 恒写**（canonical，与消费者对齐；_ns_udts.h 双址先例同法）
2. header_dir 异址时补写（向后兼容旧消费方）
3. 同址时去重（只写一次）
4. 两份内容逐字节一致
"""
import sys
import types
from pathlib import Path

import pytest

REPO = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / "pipeline" / "gen"))
sys.path.insert(0, str(REPO / "pipeline" / "gen" / "stages"))

from stages.emit_cpp import _emit_free_functions_header


def _fake_store(project_root):
    return types.SimpleNamespace(
        free_func_sigs={
            "AddMoney": "void AddMoney(int nAmount)",
            "AllocObject": "void * AllocObject(void *a2)",
        },
        project_root=project_root,
    )


def test_dual_write_canonical_and_divergent_header_dir(tmp_path):
    """header_dir ≠ pal3/src ⇒ 两处都写，内容逐字节一致."""
    store = _fake_store(tmp_path)
    divergent = tmp_path / "include" / "pal3" / "gen"

    _emit_free_functions_header(store, divergent)

    canonical = tmp_path / "pal3" / "src" / "free_functions.h"
    mirrored = divergent / "free_functions.h"
    assert canonical.exists(), "canonical pal3/src 必须恒写（消费者只认这里）"
    assert mirrored.exists(), "header_dir 异址时须补写（兼容旧消费方）"
    assert canonical.read_bytes() == mirrored.read_bytes()
    assert b"void AddMoney(int nAmount);" in canonical.read_bytes()


def test_same_location_dedup(tmp_path):
    """header_dir == pal3/src（健康配置）⇒ 单写不重复."""
    store = _fake_store(tmp_path)
    canonical_dir = tmp_path / "pal3" / "src"

    _emit_free_functions_header(store, canonical_dir)

    assert (canonical_dir / "free_functions.h").exists()
