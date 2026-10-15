#!/usr/bin/env python3
"""phase2_retain 纯函数 + fixture 树单测（R15；不碰真 pal3/src）。

覆盖：
  ① manifest 读写往返 / 非法结构 fail-loud
  ② plan_apply 漂移判据：override 漂移→drift（exit 2 语义）· pin 漂移→skips ·
     匹配→action · new_unit 直接 action · 缺产出/缺 base→skips
  ③ plan_check 五分类（ok/missing/mismatch/orphans/no_overlay）
  ④ 端到端（fixture）：adopt+改+apply ⇒ 落盘；codegen 改变输出 ⇒ apply exit 2；
     手删 pal3/src 文件 ⇒ check fail（= 验收 c/d）
"""
import json
import os
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / 'tools'))

import phase2_retain as pr  # noqa: E402


def _mk(tmp, rel, content):
    p = os.path.join(str(tmp), rel)
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, 'w', encoding='utf-8') as f:
        f.write(content)
    return p


def _ctx(tmp):
    root = os.path.join(str(tmp), 'src')
    phase2 = os.path.join(str(tmp), 'phase2')
    os.makedirs(root, exist_ok=True)
    os.makedirs(phase2, exist_ok=True)
    return pr.Ctx(root, phase2)


# ── ① manifest ──────────────────────────────────────────────────────
def test_manifest_roundtrip(tmp_path):
    p = os.path.join(str(tmp_path), 'm.json')
    m = {'version': 1, 'entries': {'a/b.cpp': {'mode': 'override',
                                               'base_sha256': 'aa'}}}
    pr.save_manifest(p, m)
    assert pr.load_manifest(p) == m
    assert pr.load_manifest(os.path.join(str(tmp_path), 'nope.json')) == {
        'version': 1, 'entries': {}}


def test_manifest_invalid_fail_loud(tmp_path):
    p = _mk(tmp_path, 'm.json', json.dumps({'entries': {'x': {'mode': 'bogus'}}}))
    try:
        pr.load_manifest(p)
        assert False, '应 ValueError'
    except ValueError:
        pass


def test_normalize_rel_accepts_repo_prefix():
    assert pr.normalize_rel('pal3/src/Misc/File.cpp') == 'Misc/File.cpp'
    assert pr.normalize_rel('./Misc/File.cpp') == 'Misc/File.cpp'
    assert pr.normalize_rel('Misc\\File.cpp') == 'Misc/File.cpp'


# ── ② plan_apply 三分判据 ───────────────────────────────────────────
def test_plan_apply_three_way_judgement():
    manifest = {'entries': {
        'a.cpp': {'mode': 'override', 'base_sha256': 'h1'},   # fix 在位 ⇒ no-op
        'b.cpp': {'mode': 'pin', 'base_sha256': 'h2'},        # pin 漂移 ⇒ skip
        'c.cpp': {'mode': 'override', 'base_sha256': 'h3'},   # override 漂移 ⇒ drift
        'd.cpp': {'mode': 'override', 'base_sha256': 'h4'},   # codegen 重生成 ⇒ action
        'e.cpp': {'mode': 'override', 'base_sha256': 'h5'},   # root 被删 ⇒ 自愈 action
        'new.cpp': {'mode': 'override', 'new_unit': True},    # 无 base ⇒ action
    }}
    census = {
        'a.cpp': 'OV1',   # == overlay ⇒ 在位
        'b.cpp': 'X2',    # ≠ base ≠ overlay ⇒ pin 漂移
        'c.cpp': 'X3',    # ≠ base ≠ overlay ⇒ override 漂移
        'd.cpp': 'h4',    # == base ⇒ 拷 overlay
        # e.cpp 缺失 ⇒ 自愈
    }
    overlay = {'a.cpp': 'OV1', 'b.cpp': 'OV2', 'c.cpp': 'OV3',
               'd.cpp': 'OV4', 'e.cpp': 'OV5', 'new.cpp': 'OVN'}
    plan = pr.plan_apply(manifest, census, overlay)
    assert plan['inplace'] == ['a.cpp']
    assert plan['actions'] == [('d.cpp', 'h4'), ('e.cpp', 'h5'), ('new.cpp', None)]
    assert plan['drift'] == [('c.cpp', 'h3', 'X3', 'override')]
    assert [s[0] for s in plan['skips']] == ['b.cpp']
    assert 'pin 漂移' in plan['skips'][0][1]


def test_plan_apply_missing_base_and_overlay():
    manifest = {'entries': {'a.cpp': {'mode': 'override'},
                            'b.cpp': {'mode': 'override', 'base_sha256': 'h'}}}
    plan = pr.plan_apply(manifest, {'a.cpp': 'h', 'b.cpp': 'h'}, {})
    assert plan['actions'] == [] and plan['drift'] == []
    assert {s[0] for s in plan['skips']} == {'a.cpp', 'b.cpp'}


# ── ③ plan_check 五分类 ─────────────────────────────────────────────
def test_plan_check_five_buckets():
    manifest = {'entries': {
        'ok.cpp': {}, 'gone.cpp': {}, 'bad.cpp': {}, 'nool.cpp': {}}}
    root_h = {'ok.cpp': 'h', 'bad.cpp': 'OLD', 'stray_in_root.cpp': 'z'}
    ov_h = {'ok.cpp': 'h', 'bad.cpp': 'NEW', 'gone.cpp': 'h',
            'orphan.cpp': 'h'}
    plan = pr.plan_check(manifest, root_h, ov_h)
    assert plan['ok'] == ['ok.cpp']
    assert plan['missing'] == ['gone.cpp']
    assert plan['mismatch'] == [('bad.cpp', 'NEW', 'OLD')]
    assert plan['no_overlay'] == ['nool.cpp']
    assert plan['orphans'] == ['orphan.cpp']


# ── ④ 端到端 fixture（= 验收 b/c/d 的缩尺版）────────────────────────
def test_end_to_end_adopt_apply_check(tmp_path):
    ctx = _ctx(tmp_path)
    _mk(tmp_path, 'src/Mod/File.cpp', 'GEN\n')
    # adopt：收编基底
    assert pr.cmd_adopt(ctx, 'Mod/File.cpp') == pr.EXIT_OK
    m = pr.load_manifest(ctx.manifest_path)
    assert m['entries']['Mod/File.cpp']['base_sha256'] == pr.sha256_file(
        os.path.join(ctx.root, 'Mod/File.cpp'))
    # 改一行（模拟 Phase 2 手工 fix）
    _mk(tmp_path, 'phase2/overlay/Mod/File.cpp', 'GEN\nFIXED\n')
    # apply ⇒ pal3/src 含改动（验收 b）
    assert pr.cmd_apply(ctx) == pr.EXIT_OK
    assert open(os.path.join(ctx.root, 'Mod/File.cpp')).read() == 'GEN\nFIXED\n'
    assert pr.cmd_check(ctx) == pr.EXIT_OK
    # 幂等：再 apply（射程/重复调用形）不得误报漂移
    assert pr.cmd_apply(ctx) == pr.EXIT_OK
    # codegen 改变输出 ⇒ override 漂移 ⇒ exit 2（验收 c）
    _mk(tmp_path, 'src/Mod/File.cpp', 'GEN-CHANGED\n')
    assert pr.cmd_apply(ctx) == pr.EXIT_DRIFT
    # rebase 刷新 base 后可再 apply
    assert pr.cmd_rebase(ctx, 'Mod/File.cpp') == pr.EXIT_OK
    assert pr.cmd_apply(ctx) == pr.EXIT_OK
    # 手删 pal3/src 内 overlay 文件 ⇒ check fail（验收 d）
    os.remove(os.path.join(ctx.root, 'Mod/File.cpp'))
    assert pr.cmd_check(ctx) == pr.EXIT_FAIL


def test_empty_manifest_is_noop(tmp_path):
    ctx = _ctx(tmp_path)
    assert pr.cmd_apply(ctx) == pr.EXIT_OK
    assert pr.cmd_check(ctx) == pr.EXIT_OK


def test_pin_drift_skips_without_fail(tmp_path):
    ctx = _ctx(tmp_path)
    _mk(tmp_path, 'src/A.cpp', 'v1\n')
    assert pr.cmd_adopt(ctx, 'A.cpp') == pr.EXIT_OK
    m = pr.load_manifest(ctx.manifest_path)
    m['entries']['A.cpp']['mode'] = 'pin'
    pr.save_manifest(ctx.manifest_path, m)
    _mk(tmp_path, 'phase2/overlay/A.cpp', 'v1\nFIX\n')
    _mk(tmp_path, 'src/A.cpp', 'v2\n')          # codegen 变了
    assert pr.cmd_apply(ctx) == pr.EXIT_OK      # pin ⇒ 跳过不 fail


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
