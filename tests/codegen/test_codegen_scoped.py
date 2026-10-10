"""S2：codegen/probe/match 射程 —— 测试。

核心设计（对抗复核裁决，不得偏离）：
1. **头全量生成**（S0 已把 decomp 派生头决策缓存化 => 头全量安全，且天然解决依赖闭包）
2. **`.cpp` 射程** —— 只生成目标 TU 的 .cpp
3. **候选集合收窄在 `probe_compile.py` 产出端**（产小 census，S3 比对两份更直观）
4. **输出隔离**：射程 `match` 写 `data/status/s4_scoped_<target>.json`，
   **严禁写 `data/status/s4_baseline.json`**（否则 stats.match_L1 从 86 骤降
   => 棘轮误判「大幅回退」=> 数据损坏）
"""
import json
import os
import re
import sys
from pathlib import Path

import pytest

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))


# ---- 1. 射程 codegen 只产目标 .cpp，头全量 ----

def test_codegen_scoped_has_cpp_filter():
    """codegen 必须支持按类/函数过滤 .cpp 生成（头全量）。"""
    src = (REPO / 'pipeline' / 'gen' / 'codegen.py').read_text(encoding='utf-8')
    assert re.search(r'def\s+\w*scoped\w*\(', src) or 'CODEGEN_CLASS' in src or \
           'CODEGEN_FUNC' in src, 'codegen 缺射程入口'


def test_codegen_scoped_keeps_headers_full():
    """头必须全量生成（S0 后安全；射程头会让依赖闭包残缺）。

    判据：射程模式下 .h 的生成路径不得被过滤。
    """
    src = (REPO / 'pipeline' / 'gen' / 'codegen.py').read_text(encoding='utf-8')
    # 头生成分支不得引用射程过滤变量
    m = re.search(r'def\s+\w*header\w*\(.*?\n(?:.*\n){0,80}?(?=\ndef |\Z)', src)
    if m:
        assert 'CODEGEN_CLASS' not in m.group(0) and 'CODEGEN_FUNC' not in m.group(0), \
            '头生成分支不得被射程过滤'


# ---- 2. 射程 match 输出隔离（数据安全护栏）----

def test_scoped_match_output_is_isolated():
    """射程 match 必须写 s4_scoped_<target>.json，严禁写 s4_baseline.json。

    这是**数据安全护栏**：基线被污染会让棘轮误判并永久损坏 L1 记录。
    """
    src = (REPO / 'pipeline' / 'compare_pal3.py').read_text(encoding='utf-8')
    cli = (REPO / 'pipeline' / 'cli.py').read_text(encoding='utf-8')
    both = src + cli
    assert 's4_scoped' in both, '射程 match 缺独立输出文件名'
    # 射程路径上不得出现 s4_baseline **写入**（提及不算 —— 文档/注释合法）
    for m in re.finditer(r'def\s+\w*scoped\w*\(.*?\n(?:.*\n){0,120}?(?=\ndef |\Z)', both):
        body = m.group(0)
        # 只查真实写入：open(..., 'w') / json.dump / write_text 后跟 s4_baseline
        for w in re.finditer(r'(?:open|write_text|json\.dump)\s*\([^)]*s4_baseline', body):
            raise AssertionError('射程 match 写入 s4_baseline.json：%r' % w.group(0)[:120])


# ---- 3. 候选集合收窄在产出端 ----

def test_probe_scoped_narrows_at_producer():
    """候选集合收窄必须在 probe_compile.py 产出端（非 compare_pal3 消费端）。

    理由：产出端收窄 => probe_census.json 本身就是射程产物，
    S3 比对两份 census 更直观。
    """
    src = (REPO / 'pipeline' / 'probe_compile.py').read_text(encoding='utf-8')
    assert 'PROBE_ONLY' in src or re.search(r'def\s+\w*scoped\w*\(', src), \
        'probe_compile 缺射程收窄入口'


# ---- 4. compare_pal3 的符号提取逻辑不得改动（只改候选集合）----

def test_compare_symbol_extraction_unchanged():
    """`compare_pal3.py` 的符号提取逻辑不得改动 —— 只改候选集合。

    改了提取逻辑会让射程与全量不可比（S3 会抓，但改了就是返工）。
    本测试锁死关键函数的存在与签名形态。
    """
    src = (REPO / 'pipeline' / 'compare_pal3.py').read_text(encoding='utf-8')
    for fn in ('build_mangled_map', 'match_symbols'):
        assert re.search(r'def\s+%s\s*\(' % fn, src), '%s 丢失/改名' % fn
