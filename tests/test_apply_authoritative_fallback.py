#!/usr/bin/env python3
"""[方案 A 2026-10-16] apply FATAL 路径权威回退判据单测（R15）。

病灶：两级继承 UDT 读回失败族（41/41 base_class=['UIFrameWnd']）——
get_udt_details()==False 单因 FATAL 未沿用 [i] 组 binary_size 权威回退。
"""
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))


def _load_fn():
    src = (REPO / 'pipeline/ida/apply_annotations.py').read_text(encoding='utf-8')
    m = re.search(r'def _should_authoritative_fallback\(.*?\n(?=def )', src, re.S)
    ns = {}
    exec(m.group(0), ns)   # 纯函数体（无 ida 依赖）可 exec
    return ns['_should_authoritative_fallback']


def test_single_reason_fallback_true():
    fn = _load_fn()
    assert fn(["get_udt_details()==False (incomplete UDT shell)"], 152) is True
    assert fn(["get_udt_details()==False (incomplete UDT shell)"], 209008) is True


def test_multi_reason_or_zero_size_stays_fatal():
    fn = _load_fn()
    assert fn(["get_udt_details()==False (incomplete UDT shell)", "member count mismatch"], 152) is False
    assert fn(["get_udt_details()==False (incomplete UDT shell)"], 0) is False
    assert fn(["member count mismatch"], 152) is False
    assert fn([], 152) is False


def test_fallback_preserves_last_mile_verify():
    """回退钩必须保留 _verify_named_udt（SceneObj 事故收口不跳过）。"""
    src = (REPO / 'pipeline/ida/apply_annotations.py').read_text(encoding='utf-8')
    m = re.search(r'if _should_authoritative_fallback\((.*?)\n\n        # 逐 struct', src, re.S)
    assert m, '回退钩缺失'
    assert '_verify_named_udt' in m.group(1), 'last-mile 核被跳过 ✗'
