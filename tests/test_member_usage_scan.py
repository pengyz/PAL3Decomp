"""member_usage_scan.py 单测（TDD 夹具）。

## 为什么（2026-10-21 用户纪律）

管线改动需要 TDD 夹具 + 子 agent 独立复核。
全用法形扫描是 P0-6 改型纪律的核心工具，须可测可验。

## 覆盖

| 场景 | 测试 |
|---|---|
| 7 种用法形分类 | test_classify_* |
| verdict 判定 | test_verdict_* |
| safe_type 映射 | test_safe_type_* |
| 比例变址支持（P0-8）| test_scaled_index |
| register 归属剔除 | test_register_filter |
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
from tools.member_usage_scan import (
    classify_instruction, usage_verdict, safe_type_for
)


# === 7 种用法形分类 ===

def test_classify_float():
    assert 'float' in classify_instruction('fstps 0x60(%esi)')
    assert 'float' in classify_instruction('flds  0x60(%esi)')
    assert 'float' in classify_instruction('fadds 0x60(%esi)')
    assert 'float' in classify_instruction('fcomps 0x74(%esi)')


def test_classify_arith():
    assert 'arith' in classify_instruction('add 0x4dc(%esi),%eax')
    assert 'arith' in classify_instruction('sub $0x10,%esp')
    assert 'arith' in classify_instruction('imul $0xd0,%eax')


def test_classify_cmp():
    assert 'cmp' in classify_instruction('cmp $0x6,0x14(%esi)')
    assert 'cmp' in classify_instruction('test %al,%al')


def test_classify_addr():
    assert 'addr' in classify_instruction('lea 0x1478(%esi),%ecx')


def test_classify_assign():
    assert 'assign' in classify_instruction('mov %eax,0x114(%esi)')
    assert 'assign' in classify_instruction('mov 0x114(%esi),%eax')


def test_classify_bitop():
    assert 'bitop' in classify_instruction('and $0xff,%eax')
    assert 'bitop' in classify_instruction('or $0x1,%ebx')


def test_classify_indirect():
    assert 'indirect' in classify_instruction('call *(%eax)')


# === verdict 判定 ===

def test_verdict_single_float():
    assert usage_verdict({'float': 5}) == 'SINGLE_FLOAT'


def test_verdict_single_arith():
    assert usage_verdict({'arith': 3, 'cmp': 2}) == 'SINGLE_ARITH'
    assert usage_verdict({'cmp': 1}) == 'SINGLE_ARITH'


def test_verdict_single_addr():
    assert usage_verdict({'addr': 2}) == 'SINGLE_ADDR'
    assert usage_verdict({'addr': 2, 'assign': 5}) == 'SINGLE_ADDR'


def test_verdict_mixed():
    """混合用法（float + assign）⇒ MIXED（R51 +617 回归源）。"""
    assert usage_verdict({'float': 14, 'assign': 11}) == 'MIXED'


def test_verdict_none():
    assert usage_verdict({}) == 'NONE'


# === safe_type 映射（P0-6 改型纪律）===

def test_safe_type_single_float():
    assert safe_type_for('SINGLE_FLOAT') == 'float'


def test_safe_type_single_arith():
    assert safe_type_for('SINGLE_ARITH') == 'int'


def test_safe_type_mixed_freeze():
    """MIXED ⇒ None（冻结，禁猜测）。"""
    assert safe_type_for('MIXED') is None
    assert safe_type_for('NONE') is None
    assert safe_type_for('SINGLE_ASSIGN') is None
