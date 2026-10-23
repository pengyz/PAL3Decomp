"""Export `_inline_*` 对称性 TDD（红绿测试）。

## 背景

export_full.py:714 删 `_inline_*` 合成名定义（避免 C2011 双源）
但 `data_members` 仍引用 ⇒ 不对称（引用 vs 定义）

## TDD

| 测试 | assertion |
|---|---|
| test_inline_reference_consistency | data_members 引用的 _inline_* 都有定义 |
| test_no_dangling_inline_ref | 无悬空 _inline_* 引用 |
"""
import json
import pytest


def test_inline_reference_consistency():
    """data_members 引用的 _inline_* 都有定义（对称）。"""
    ida = json.load(open('asm/pal3/ida_structs.json'))
    dangling = []
    for cls_name, v in ida.items():
        if not isinstance(v, dict):
            continue
        for m in (v.get('data_members') or []):
            t = str(m.get('type', ''))
            if t.startswith('_inline_') and t not in ida:
                dangling.append((cls_name, m.get('name'), t))
    assert not dangling, f'悬空 _inline_* 引用: {dangling[:3]}'


def test_no_dangling_inline_ref():
    """无悬空 _inline_* 引用（对称）。"""
    ida = json.load(open('asm/pal3/ida_structs.json'))
    refs = set()
    defs = set()
    for cls_name, v in ida.items():
        if not isinstance(v, dict):
            continue
        if cls_name.startswith('_inline_'):
            defs.add(cls_name)
        for m in (v.get('data_members') or []):
            t = str(m.get('type', ''))
            if t.startswith('_inline_'):
                refs.add(t)
    dangling = refs - defs
    assert not dangling, f'悬空引用: {dangling}'
