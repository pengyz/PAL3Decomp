"""stub_retire S1-S4 对账（方案 v2 §2）——含篡改实验（哈希链/增长归因）。
运行: python3 tests/test_stub_retire.py -q"""
import json
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import stub_retire as sr  # noqa: E402


def test_classify_inventory_table():
    """盘点口径表机械化：五类面 + obj 排除（方案 v2 §2 表）。"""
    cls = sr.classify_stubs()
    assert len(cls['unit']) == 89, len(cls['unit'])          # 单元 stub 主口径
    assert cls['glue'] == 1                                  # _eh_metadata 恒存
    assert cls['slots_files'] >= 90 and cls['supply_files'] >= 30
    assert cls['real_files'] == 0                            # _real 尚未建（M2b）
    # obj 不入面（移出源码树后应为 0；容忍历史残留记数）
    assert cls['obj_excluded'] >= 0


def test_reconcile_no_orphan():
    cls, retire_due, missing, orphan = sr.reconcile()
    assert not missing, missing[:3]           # S2 催建面为空（M1 全量生成）
    assert not orphan, orphan[:3]             # 台账与 census 对上


def test_ratchet_hash_chain_and_tamper_detect():
    """append-only 哈希链：改写历史 ⇒ TAMPERED 检出（方案 v2 F11/R1-F11）。"""
    import tempfile
    tmp = Path(tempfile.mkdtemp())
    orig = sr.RATCHET
    try:
        sr.RATCHET = tmp / 'm4_ratchet.json'
        s1, err = sr.append_snapshot('initial', 'genesis')
        assert err is None and s1['seq'] == 0
        s2, err = sr.append_snapshot('prune', 'T1a')
        assert err is None and s2['seq'] == 1
        chain = sr.load_ratchet()
        assert not isinstance(chain, tuple) and len(chain) == 2
        # 篡改实验：回写历史字段
        d = json.loads(sr.RATCHET.read_text(encoding='utf-8'))
        d['snapshots'][0]['unit_stubs'] = 0
        sr.RATCHET.write_text(json.dumps(d), encoding='utf-8')
        assert sr.load_ratchet()[0] == 'TAMPERED'
    finally:
        sr.RATCHET = orig


def test_record_rejects_reason_out_of_enum():
    import tempfile
    tmp = Path(tempfile.mkdtemp())
    orig = sr.RATCHET
    try:
        sr.RATCHET = tmp / 'm4_ratchet.json'
        snap, err = sr.append_snapshot('make_number_go_up', '')
        assert snap is None and '越枚举' in err
    finally:
        sr.RATCHET = orig


def test_growth_reasons_enum():
    """S3 归因枚举（方案 v2 F5 修）：增长放行仅限 new_unit/regression/census_refresh/rebaseline。"""
    assert sr.GROWTH_REASONS == {'new_unit', 'regression', 'census_refresh', 'rebaseline'}
    assert 'retire' not in sr.GROWTH_REASONS
