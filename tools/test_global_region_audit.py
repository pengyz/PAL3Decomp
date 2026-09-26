"""global_region_audit 阶段 1（census）契约测试。TDD：先于实现编写。

门禁（对抗复核报告 §3.4 / 阶段 1 + 阶段 2 前补强清单）：
  - 分母 = pal3/src/globals.h 的 extern 总数（当前 2,734），每条恰一行 census
  - 每行含 addr/name/type/array/dims/section/bucket/size_bytes/evidence_refs
    /in_annotations/anno_name_matches/anno_skip
  - 行唯一性：addr 与 name 均无重复
  - section 判定来自 PE 节表（非魔法数），三类：data_init/bss/rdata；边界含成
    合成节表用例（==va+rsz、节间 gap）
  - _meta 含双输入 md5 指纹
  - census 确定性：同输入两次构建逐字节一致
"""
import json
import os
import sys

import pytest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))

import global_region_audit as gra  # noqa: E402

GLOBALS_H = os.path.join(ROOT, 'pal3', 'src', 'globals.h')


# ---------- 解析器 ----------

def test_parse_count_matches_file():
    """分母契约：解析数 == 文件内带址 extern 行数（数组形态含在内）。"""
    entries = gra.parse_globals_h(GLOBALS_H)
    raw = 0
    for ln in open(GLOBALS_H, encoding='utf-8', errors='replace'):
        if ln.startswith('extern') and '//' in ln and '0x' in ln:
            raw += 1
    assert len(entries) == raw
    assert len(entries) == 2734


def test_parse_array_and_scalar():
    """数组/标量/无长度数组三种形态都要出全字段。"""
    entries = gra.parse_globals_h(GLOBALS_H)
    by_name = {e['name']: e for e in entries}
    # 数组（元素数已知）
    e = by_name['g_nStatePanelL']
    assert e['addr'] == 0x56FCC8 and e['array'] == 4
    # 无长度数组
    e = by_name['g_MonsterEntryTable']
    assert e['addr'] == 0x56C568 and e['array'] is None
    # 标量
    e = by_name['dword_BFDAB0'] if 'dword_BFDAB0' in by_name else by_name.get('g_RoleSlotBuf')
    assert e is not None and e['array'] is None


def test_parse_two_dimensional_array():
    """回归：二维数组 `char g_pfnUpdateFuncs[4][5];` 曾因单维正则漏解析。"""
    entries = gra.parse_globals_h(GLOBALS_H)
    by_name = {e['name']: e for e in entries}
    e = by_name['g_pfnUpdateFuncs']
    assert e['addr'] == 0x58618C
    assert e['array'] == 4 and e['dims'] == [4, 5]


def test_parse_fields_complete():
    entries = gra.parse_globals_h(GLOBALS_H)
    for e in entries:
        assert isinstance(e['addr'], int) and e['addr'] > 0
        assert e['name']
        assert isinstance(e['type'], str) and e['type']
        assert set(e.keys()) >= {'addr', 'name', 'type', 'array'}


# ---------- PE 节分类 ----------

def test_pe_sections_loaded():
    secs = gra.load_pe_sections(os.path.join(ROOT, 'original', 'PAL3.exe'))
    names = [s['name'] for s in secs]
    assert names[:4] == ['.text', '.rdata', '.data', '.rsrc']
    data = [s for s in secs if s['name'] == '.data'][0]
    assert data['va'] == 0x580000  # 已知锚（asm dword_580000）


def test_classify_known_addresses():
    secs = gra.load_pe_sections(os.path.join(ROOT, 'original', 'PAL3.exe'))
    assert gra.classify_section(0x56A5E0, secs) == 'rdata'      # g_fHeuristicScale
    assert gra.classify_section(0xC043A0, secs) == 'bss'        # g_RoleSlotBuf
    assert gra.classify_section(0x580000, secs) == 'data_init'  # .data 起始


# ---------- census ----------

def test_census_total_and_buckets():
    census = gra.build_census(GLOBALS_H, os.path.join(ROOT, 'original', 'PAL3.exe'))
    rows = census['rows']
    assert len(rows) == 2734
    # 完备门（阶段 1 形态）：每行有 section 与 bucket；rdata 即 B7，
    # 其余为 pending（最终 bucket 由分区/锚定阶段细分——完备性在全部阶段后达成）
    for r in rows:
        assert r['section'] in ('data_init', 'bss', 'rdata', 'other')
        assert r['bucket'] == 'B7' or r['bucket'] == 'pending'
    # 阶段 1 的 bucket 只做初步：rdata→B7，其余 pending（后续阶段细分）
    by_sec = {}
    for r in rows:
        by_sec.setdefault(r['section'], []).append(r)
    assert all(r['bucket'] == 'B7' for r in by_sec.get('rdata', []))
    assert len(by_sec.get('data_init', [])) == 937
    assert len(by_sec.get('bss', [])) == 1642


def test_census_deterministic(tmp_path):
    c1 = gra.build_census(GLOBALS_H, os.path.join(ROOT, 'original', 'PAL3.exe'))
    c2 = gra.build_census(GLOBALS_H, os.path.join(ROOT, 'original', 'PAL3.exe'))
    assert json.dumps(c1, sort_keys=True) == json.dumps(c2, sort_keys=True)
    # 地址严格递增（可复现顺序）
    addrs = [r['addr'] for r in c1['rows']]
    assert addrs == sorted(addrs)


def test_census_row_uniqueness():
    """唯一性断言（前瞻）：同计数下的同址/同名重复必须红。"""
    census = gra.build_census(GLOBALS_H, os.path.join(ROOT, 'original', 'PAL3.exe'))
    addrs = [r['addr'] for r in census['rows']]
    names = [r['name'] for r in census['rows']]
    assert len(set(addrs)) == len(addrs)
    assert len(set(names)) == len(names)


def test_classify_synthetic_boundaries():
    """合成节表边界：==va+rsz 落 bss、节间 gap 落 other、节后地址落 other。"""
    secs = [
        {'name': '.text', 'va': 0x401000, 'vsz': 0x1000, 'rsz': 0x1000, 'roff': 0x400},
        {'name': '.data', 'va': 0x580000, 'vsz': 0x3000, 'rsz': 0x2000, 'roff': 0x2000},
    ]
    assert gra.classify_section(0x580000 + 0x1FFF, secs) == 'data_init'
    assert gra.classify_section(0x580000 + 0x2000, secs) == 'bss'    # == va+rsz
    assert gra.classify_section(0x580000 + 0x2FFF, secs) == 'bss'
    assert gra.classify_section(0x580000 + 0x3000, secs) == 'other'  # 节后
    assert gra.classify_section(0x500000, secs) == 'other'           # 节间 gap


def test_census_row_schema_fields():
    """复核补强清单：dims/size_bytes/evidence_refs/anno 交叉字段/_meta md5。"""
    census = gra.build_census(GLOBALS_H, os.path.join(ROOT, 'original', 'PAL3.exe'))
    for r in census['rows']:
        assert 'dims' in r
        assert 'size_bytes' in r          # [] 无长度 → None；可算者 → int
        assert r['evidence_refs'] == []   # 阶段 3/4 回填占位
        assert isinstance(r['in_annotations'], bool)
        assert isinstance(r['anno_skip'], bool)
        assert isinstance(r['anno_name_matches'], bool)
    meta = census['_meta']
    assert len(meta.get('md5_globals_h', '')) == 32
    assert len(meta.get('md5_pal3_exe', '')) == 32


def test_census_size_bytes_known_types():
    """size_bytes：已知基型 × 维度可算；[] 与未知基型 → None。"""
    census = gra.build_census(GLOBALS_H, os.path.join(ROOT, 'original', 'PAL3.exe'))
    by_name = {r['name']: r for r in census['rows']}
    e = by_name['g_nStatePanelL']          # int[4]
    assert e['size_bytes'] == 16
    e = by_name['g_MonsterEntryTable']     # int[] 无长度
    assert e['size_bytes'] is None


def test_census_annotation_cross():
    """annotations 交叉：具名条目 in_annotations=True；skip 类型被标记。"""
    census = gra.build_census(GLOBALS_H, os.path.join(ROOT, 'original', 'PAL3.exe'))
    rows = census['rows']
    n_in = sum(1 for r in rows if r['in_annotations'])
    assert 1100 <= n_in <= 1200          # 复核实测 1,158
    n_skip = sum(1 for r in rows if r['anno_skip'])
    assert 100 <= n_skip <= 150          # 复核实测 123
    # 名字一致性：严格文本比对（globals.h 由 annotations 生成，漂移=生成滞后
    # 信号，大小写差异也算——如 dword_58619c vs dword_58619C）。复核实测 19；
    # 大小写归一口径为 4（复核 agent 口径），两口径都已记录在案。
    n_mismatch = sum(1 for r in rows if r['in_annotations'] and not r['anno_name_matches'])
    assert 15 <= n_mismatch <= 25
