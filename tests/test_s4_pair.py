"""s4 成对恢复（s4 源修·病灶：棘轮真退步恢复只写 baseline，detail 已被新 run
覆盖 ⇒ 双文件异源（161 vs 110 实证）——恢复必须成对·诊断不丢存档）。"""
import json
import os

from pipeline.s4_pair import restore_pair


def _paths(tmp_path):
    return (tmp_path / 's4_baseline.json', tmp_path / 's4_diff_detail.json',
            tmp_path / 'archive')


def test_restore_pair_writes_both(tmp_path):
    s4, det, arc = _paths(tmp_path)
    s4.write_text('OLD_BASE'); det.write_text('NEW_DETAIL')
    r = restore_pair(str(s4), str(det), prev_s4_text='OLD_BASE',
                     prev_detail_text='OLD_DETAIL', cur_detail_text='NEW_DETAIL',
                     archive_dir=str(arc))
    assert s4.read_text() == 'OLD_BASE' and det.read_text() == 'OLD_DETAIL', \
        '恢复必须成对（baseline+detail 同回滚·禁单文件异源）'
    assert r['archived'] and os.path.exists(r['archived'])
    assert open(r['archived']).read() == 'NEW_DETAIL', 'regressed 诊断必须存档不丢'


def test_restore_pair_no_prev_detail(tmp_path):
    """prev detail 缺 → cur 存档+detail 移除（宁缺勿伪同源·match_progress 将响亮报缺）。"""
    s4, det, arc = _paths(tmp_path)
    s4.write_text('OLD'); det.write_text('CUR')
    r = restore_pair(str(s4), str(det), prev_s4_text='OLD',
                     prev_detail_text=None, cur_detail_text='CUR',
                     archive_dir=str(arc))
    assert s4.read_text() == 'OLD'
    assert not det.exists(), '无 prev detail 禁留 cur（伪同源）'
    assert r['archived'] and open(r['archived']).read() == 'CUR'


def test_restore_pair_no_change_needed(tmp_path):
    """cur==prev（无退步）→ 不写不动（幂等面）。"""
    s4, det, arc = _paths(tmp_path)
    s4.write_text('X'); det.write_text('Y')
    r = restore_pair(str(s4), str(det), prev_s4_text='X',
                     prev_detail_text='Y', cur_detail_text='Y',
                     archive_dir=str(arc))
    assert r['restored'] is False and not r['archived']
