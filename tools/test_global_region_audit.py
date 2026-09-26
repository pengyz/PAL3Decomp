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


# ---------- 阶段 2：非重叠分区树 ----------

def test_partition_containment():
    """包含关系：inner 成为 outer 的成员，不再出现在顶层。"""
    anchors = [
        {'base': 0x1000, 'end': 0x2000, 'name': 'outer', 'type': 'A'},
        {'base': 0x1100, 'end': 0x1200, 'name': 'inner', 'type': 'B'},
    ]
    p = gra.build_partition(anchors)
    tops = [t['name'] for t in p['top_levels']]
    assert tops == ['outer']
    assert p['members'][0]['name'] == 'inner'
    assert p['members'][0]['parent'] == 'outer'
    assert p['conflicts'] == []


def test_partition_disjoint_and_adjacent():
    """不相交与相邻（[1000,1010)+[1010,1020)）都是顶层。"""
    anchors = [
        {'base': 0x1000, 'end': 0x1010, 'name': 'a', 'type': 'A'},
        {'base': 0x1010, 'end': 0x1020, 'name': 'b', 'type': 'A'},
        {'base': 0x3000, 'end': 0x3010, 'name': 'c', 'type': 'A'},
    ]
    p = gra.build_partition(anchors)
    assert sorted(t['name'] for t in p['top_levels']) == ['a', 'b', 'c']
    assert p['conflicts'] == []


def test_partition_partial_overlap_conflict():
    """部分重叠 → 双双冻结进 conflicts（B9），不进顶层。"""
    anchors = [
        {'base': 0x1000, 'end': 0x2000, 'name': 'x', 'type': 'A'},
        {'base': 0x1800, 'end': 0x2800, 'name': 'y', 'type': 'A'},
    ]
    p = gra.build_partition(anchors)
    assert p['top_levels'] == []
    assert len(p['conflicts']) == 2
    assert {c['name'] for c in p['conflicts']} == {'x', 'y'}


def test_partition_identical_extents_conflict():
    """完全相同 extent → 冲突（归属二义），不是静默包含。"""
    anchors = [
        {'base': 0x1000, 'end': 0x2000, 'name': 'x', 'type': 'A'},
        {'base': 0x1000, 'end': 0x2000, 'name': 'y', 'type': 'A'},
    ]
    p = gra.build_partition(anchors)
    assert p['top_levels'] == []
    assert len(p['conflicts']) == 2


def test_partition_same_base_containment():
    """同基不同尺寸：大的顶层，小的成员。"""
    anchors = [
        {'base': 0x1000, 'end': 0x1400, 'name': 'small', 'type': 'A'},
        {'base': 0x1000, 'end': 0x2000, 'name': 'big', 'type': 'A'},
    ]
    p = gra.build_partition(anchors)
    assert [t['name'] for t in p['top_levels']] == ['big']
    assert p['members'][0]['name'] == 'small'


def test_partition_deterministic():
    a1 = [
        {'base': 0x1000, 'end': 0x2000, 'name': 'outer', 'type': 'A'},
        {'base': 0x1100, 'end': 0x1200, 'name': 'inner', 'type': 'B'},
        {'base': 0x5000, 'end': 0x5100, 'name': 'z', 'type': 'C'},
    ]
    p1 = gra.build_partition(a1)
    p2 = gra.build_partition(list(reversed([dict(x) for x in a1])))
    assert json.dumps(p1, sort_keys=True) == json.dumps(p2, sort_keys=True)
    assert [t['base'] for t in p1['top_levels']] == sorted(t['base'] for t in p1['top_levels'])


def test_partition_chain_overlap_no_silent_top(S=None):
    """S1 回归：A-B 冲突冻结后，与 frozen-B 重叠的 C 不得无声顶层化。

    A[1000,2000) vs B[1800,2800) 冲突；C[2600,3600) 与 B 重叠 → C 必须冻结
    （链式传染），顶层必须为空。实现缺陷时 C 会无声成为顶层（B9 安全网漏报）。
    """
    anchors = [
        {'base': 0x1000, 'end': 0x2000, 'name': 'A', 'type': 'A'},
        {'base': 0x1800, 'end': 0x2800, 'name': 'B', 'type': 'A'},
        {'base': 0x2600, 'end': 0x3600, 'name': 'C', 'type': 'A'},
    ]
    p = gra.build_partition(anchors)
    assert p['top_levels'] == []
    frozen_names = {c['name'] for c in p['conflicts']}
    assert frozen_names == {'A', 'B', 'C'}


def test_partition_parent_frozen_members_suspended():
    """S3 回归：顶层被冻结后，其成员随父挂起（不得指向不存在的顶层）。"""
    anchors = [
        {'base': 0x1000, 'end': 0x2000, 'name': 'X', 'type': 'A'},
        {'base': 0x1100, 'end': 0x1200, 'name': 'I', 'type': 'A'},   # X 的成员
        {'base': 0x1800, 'end': 0x2800, 'name': 'Y', 'type': 'A'},   # 与 X 部分重叠
    ]
    p = gra.build_partition(anchors)
    top_names = {t['name'] for t in p['top_levels']}
    # X 被冻结；成员 I 的 parent 不得指向已不存在的顶层
    dangling = [m for m in p['members'] if m['parent'] not in top_names]
    assert dangling == [], dangling
    # I 的处置必须是显式的（随父挂起进 conflicts 或有 parent 仍在顶层）


def test_partition_three_level_nesting_tightest_host():
    """S4 回归：A⊃B⊃C 三层嵌套，C 挂最紧包含者 B（成员可嵌套树语义）。"""
    anchors = [
        {'base': 0x1000, 'end': 0x3000, 'name': 'A', 'type': 'A'},
        {'base': 0x1200, 'end': 0x2800, 'name': 'B', 'type': 'A'},
        {'base': 0x1400, 'end': 0x1600, 'name': 'C', 'type': 'A'},
    ]
    p = gra.build_partition(anchors)
    tops = {t['name'] for t in p['top_levels']}
    assert tops == {'A'}
    host_of = {m['name']: m['parent'] for m in p['members']}
    assert host_of.get('B') == 'A'
    assert host_of.get('C') == 'B'


def test_partition_real_anchors_known_facts():
    """真实锚的已知事实（对抗复核实测）：ScriptSystemData 顶层吞洲 1；
    g_RoleSlotBuf 与 g_palScript 是 g_SceneMgr 的成员（重叠 3 对中的 2 对）；
    g_vRotateAxis 是 ScriptSystemData 的成员。"""
    anchors = gra.collect_anchor_containers()
    names = {a['name'] for a in anchors}
    assert 'g_ScriptSystemData' in names and 'g_SceneMgr' in names
    p = gra.build_partition(anchors)
    tops = {t['name']: t for t in p['top_levels']}
    ssd = tops['g_ScriptSystemData']
    assert ssd['base'] == 0xD8B318 and ssd['end'] == 0xD8B318 + 12624
    members_by_parent = {}
    for m in p['members']:
        members_by_parent.setdefault(m['parent'], []).append(m['name'])
    assert 'g_RoleSlotBuf' in members_by_parent.get('g_SceneMgr', [])
    assert 'g_palScript' in members_by_parent.get('g_SceneMgr', [])
    assert 'g_vRotateAxis' in members_by_parent.get('g_ScriptSystemData', [])
    # 门禁：顶层零重叠
    tops_sorted = sorted(p['top_levels'], key=lambda t: t['base'])
    for a, b in zip(tops_sorted, tops_sorted[1:]):
        assert a['end'] <= b['base'], (a['name'], b['name'])


# ---------- 阶段 3：E 类单例三元组 + D 类动态初始化器锚 ----------

def test_scan_singletons_real_sample():
    """真实样本：CCBStage::DoTask 的 gbMatrix4 静态局部构造三元组。"""
    triplets = gra.scan_singleton_triplets(os.path.join(ROOT, 'asm', 'pal3', 'decomp'))
    by_name = {}
    for t in triplets:
        by_name.setdefault(t['global_name'], t)
    t = by_name['stru_17AB828']
    assert t['class'] == 'gbMatrix4'
    assert t['func_file'].startswith('CCBStage_DoTask')


def test_scan_singletons_corpus_count():
    """全语料：可解析全局名的 E 类三元组（实测 1）。

    局限记录：15 个 guard+atexit+self-ctor 函数里 24/25 的 ctor 首参是
    Hex-Rays 局部渲染（&v25——静态对象地址未显形），decomp 文本不可解析；
    这批的地址归属走 D 类二进制链（atexit 注册桩→thunk→全局），
    两类证据互为补充。
    """
    triplets = gra.scan_singleton_triplets(os.path.join(ROOT, 'asm', 'pal3', 'decomp'))
    assert len(triplets) >= 1
    names = {r['name'] for r in gra.build_census()['rows']}
    unresolved = [t for t in triplets if t['global_name'] not in names]
    assert unresolved == [], unresolved[:5]


def test_singleton_anchor_extent():
    """类尺寸解析：ida_structs 的 IDB UDT size 优先（gbMatrix4=64 实测）。"""
    size = gra.class_size('gbMatrix4')
    assert size == 64


def test_scan_xcu_real_anchor():
    """D 类：g_palScript @0xC10968 的 atexit 注册桩→析构 thunk→vtable 反解链。

    实测三元组布局（0x4086C0/0x4086D0/0x4086E0）：初始化 thunk
    (mov ecx,&g; jmp ctor) + atexit 注册桩 + 析构 thunk。0x43A1F0 为析构。
    """
    sites = gra.scan_xcu_initializers(os.path.join(ROOT, 'original', 'PAL3.exe'))
    pal = [s for s in sites if s['global_addr'] == 0xC10968]
    assert pal, [hex(s['global_addr']) for s in sites]
    assert any(s.get('class') == 'PalScript' for s in pal)
    assert any(s.get('vtable') == 0x56AC4C for s in pal)


def test_scan_xcu_corpus_and_vtable_class():
    """D 类语料规模 + vtable→类反解（ctor 体写自身 vtable 的证据链）。"""
    sites = gra.scan_xcu_initializers(os.path.join(ROOT, 'original', 'PAL3.exe'))
    assert len(sites) >= 10                       # 复核实测 60 站点/18 全局（窗口差异）
    assert len({s['global_addr'] for s in sites}) >= 8
    # 至少一个站点能经 vtable 反解出类名
    with_class = [s for s in sites if s.get('class')]
    assert with_class, 'vtable 反解全空——vtables 注解映射断了'


def test_partition_with_evidence_anchors():
    """证据锚并入分区：E/D 锚不与既有顶层冲突（当前数据），总数不减。"""
    base_anchors = gra.collect_anchor_containers()
    ev = gra.collect_evidence_anchors()
    merged = gra.merge_anchors(base_anchors, ev)
    assert len(merged) >= len(base_anchors)
    p = gra.build_partition(merged)
    tops_sorted = sorted(p['top_levels'], key=lambda t: t['base'])
    for a, b in zip(tops_sorted, tops_sorted[1:]):
        assert a['end'] <= b['base'], (a['name'], b['name'])


def test_scan_xcu_byte_level_coverage():
    """复核修正：线性 disasm 在 0x408E18 停机漏 16 锚（覆盖率 2.2% 事故）——
    字节级重同步扫描必须回收全部真实锚（复核实测 26 个唯一 (全局,dtor) 对）。"""
    sites = gra.scan_xcu_initializers(os.path.join(ROOT, 'original', 'PAL3.exe'))
    uniq = {(s['global_addr'], s['target']) for s in sites}
    assert len(uniq) >= 20, len(uniq)
    ga = {s['global_addr'] for s in sites}
    for known in (0x17B41E8,   # g_CScreenMode 真单例（dtor 0x53DC50）
                  0xDB9FD0,    # g_gamefrm
                  0xD8E4C0,    # g_GameData
                  0x17B1EC0,   # g_InputState
                  0xC10968):   # g_palScript
        assert known in ga, hex(known)


def test_scan_xcu_helper_pinned():
    """off-by-5 修正：CRT helper 实证 0x553041（push [esp+4]/call 0x552FD4 形态）。"""
    sites = gra.scan_xcu_initializers(os.path.join(ROOT, 'original', 'PAL3.exe'))
    assert sites, 'no sites'
    assert gra.detect_atexit_helper(os.path.join(ROOT, 'original', 'PAL3.exe')) == 0x553041


def test_partition_same_base_identity_conflict():
    """同基不同 extent/type = 身份矛盾 → B9（CPK@0xA3A7D8 vs g_ScreenMode 事故）。"""
    anchors = [
        {'base': 0x1000, 'end': 0x2400, 'name': 'g_Small', 'type': 'CScreenMode'},
        {'base': 0x1000, 'end': 0xB1A994 - 0xA3A7D8 + 0x1000, 'name': 'g_Big', 'type': 'CPK'},
    ]
    p = gra.build_partition(anchors)
    kinds = {c['kind'] for c in p['conflicts']}
    assert 'same_base' in kinds
    assert p['top_levels'] == []


def test_partition_frozen_host_and_member_partial():
    """S1/S3 残余：冻结宿主上再到的 contained 锚 → 冻结（frozen_host）；
    与成员态区间的部分重叠 → 双方冻结。"""
    anchors = [
        {'base': 0x1000, 'end': 0x2000, 'name': 'X', 'type': 'A'},
        {'base': 0x1800, 'end': 0x2800, 'name': 'Y', 'type': 'A'},
        {'base': 0x2000, 'end': 0x2400, 'name': 'C', 'type': 'A'},  # ⊂ frozen-Y
        {'base': 0x2100, 'end': 0x2300, 'name': 'D', 'type': 'A'},  # ⊂ C(frozen)
    ]
    p = gra.build_partition(anchors)
    top_names = {t['name'] for t in p['top_levels']}
    assert top_names == set(), top_names
    kinds = {c['name']: c['kind'] for c in p['conflicts']}
    assert kinds.get('C') == 'frozen_host'
    assert kinds.get('D') == 'frozen_host'
    # 成员态区间（无）——member partial 用另例
    anchors2 = [
        {'base': 0x5000, 'end': 0x6000, 'name': 'T', 'type': 'A'},
        {'base': 0x5100, 'end': 0x5200, 'name': 'M', 'type': 'A'},   # T 的成员
        {'base': 0x5180, 'end': 0x5300, 'name': 'P', 'type': 'A'},   # 与 M 部分重叠
    ]
    p2 = gra.build_partition(anchors2)
    kinds2 = {c['name']: c['kind'] for c in p2['conflicts']}
    # kind=冲突语境：新到者 P 记 'member'（对方是成员态）；
    # 成员 M 记 'member_partial'（被卷入时的自身状态）
    assert kinds2.get('P') == 'member'
    assert kinds2.get('M') == 'member_partial'
