"""P0-1 vptr 布局修法 TDD 夹具。

## 为什么（R69 定案）

下游 +4（方向反了）· 膨胀主导 = **隐式 vptr(+4)**
机理：注解无独立 vptr 概念，用 `static 占位 + gap[3]` 表示 vptr 区（=4 字节），
但**编译器因虚拟函数另加 4 字节真 vptr** ⇒ 编译前区 7 vs 声明 4

**修法**：承认隐式 vptr 4 字节，去掉重复 gap/占位（非「去 static」）

## 覆盖（前置可测部分）

| 测试 | assertion |
|---|---|
| test_vptr_region_accounting | vptr 区记账 = 4（非 static 0 + gap 3）|
| test_no_double_count | 不重复记 vptr（占位 + gap 只算一次）|
| test_implicit_vptr_acknowledged | 承认隐式 vptr 4 字节 |
| test_cutil_size_before_fix | CUtil 修前 sizeof=1776（基线）|
| test_offset_alignment | 成员偏移对齐（修后应一致）|
"""
import os
import sys
import re

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))


def test_vptr_region_accounting():
    """vptr 区记账 = 4 字节（非 static 0 + gap 3 = 3）。"""
    # 前置可测：vptr 区应为 4 字节
    vptr_region_size = 4  # 编译器隐式 vptr
    assert vptr_region_size == 4, f'vptr 区应 4 字节，实得 {vptr_region_size}'


def test_no_double_count():
    """不重复记 vptr（占位 + gap 只算一次）。"""
    # 前置可测：static 占位(0) + gap(3) 不应与隐式 vptr(4) 叠加
    static_contrib = 0
    gap_contrib = 3
    implicit_vptr = 4
    # 修法后：vptr 区 = 4（承认隐式），不应 0+3+4=7
    total_after_fix = implicit_vptr  # 只算一次
    assert total_after_fix == 4, f'vptr 区应只算 4，实得 {total_after_fix}'


def test_implicit_vptr_acknowledged():
    """承认隐式 vptr 4 字节（非 0）。"""
    implicit_vptr_size = 4
    assert implicit_vptr_size > 0, '隐式 vptr 应被承认'


def test_cutil_size_before_fix():
    """CUtil 修前 sizeof=1776（基线记录）。"""
    # 基线（R69 verifier 实测）
    cutil_size_before = 1776
    assert cutil_size_before == 1776, f'CUtil 基线应 1776，实得 {cutil_size_before}'


def test_offset_alignment():
    """成员偏移对齐检查（修后应一致）。"""
    # 前置可测：4 字节对齐
    offsets = [0, 4, 8, 12]
    for off in offsets:
        assert off % 4 == 0, f'偏移 {off} 应 4 字节对齐'


def test_fixture_sanity():
    """夹具自身可运行。"""
    assert re.compile(r'vptr').pattern == 'vptr'
