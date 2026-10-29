"""债回收（spec #9/#1 残项）——Destroy__ovl_03 族批（t1_followups：10 处/9 文件）。
回收判据：注释块移除 + 真码行回装 + 该单元纯态编译 ok（loop/PROBE_ONLY 验证）。
运行: pytest tests/test_debt_recovery_pure.py -q"""
import glob, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]


def test_destroy_ovl03_family_recovered():
    hits = []
    for f in glob.glob(str(ROOT / 'phase2/overlay/**/*.cpp'), recursive=True):
        t = open(f).read()
        for i, line in enumerate(t.splitlines(), 1):
            if 'Destroy__ovl_03' in line and line.strip().startswith('//'):
                hits.append((f.split('/')[-1], i))
    assert not hits, hits        # 注释形态零残留（真码行回装后无注释）


def test_manifest_destroy_family_retired():
    """Destroy 族 9 条目整退役（T1 上游修复消债根）——manifest 47→38。"""
    import json
    m = json.load(open(ROOT / 'phase2/manifest.json'))
    ent = m['entries']
    assert len(ent) == 35, len(ent)   # 47 - Destroy9 - 净件3
    for f in ('UI/UIListBox.cpp', 'Combat/CCBItemWindow.cpp', 'Misc/UISceneFrm.cpp'):
        assert f not in ent, f


def test_overlay_marker_count_accounted():
    import glob as _g
    n = sum(open(f).read().count('[overlay-fix') for f in _g.glob(str(ROOT / 'phase2/overlay/**/*.cpp'), recursive=True))
    assert n <= 107, n           # 棘轮上限（Destroy 11 + 净件批递减；逐批退役须改账）
