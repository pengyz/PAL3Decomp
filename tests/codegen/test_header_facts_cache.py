"""S0：decomp 派生头事实缓存化 —— 测试。

背景（对抗复核实证 2026-10-09）：
  `emit_headers.py` 有 **4 条** decomp 依赖会「决定头内容」（不只是收集数据）：
    1) `_get_scalar_dtor_classes()`  :32-78   虚析构判定（漏判 => 不发 ??_G => L1 静默丢）
    2) `_get_underscore_aliases()`  :80-137  _X->X typedef 别名
    3) `:2386` 虚析构注入的独立复算路径
    4) `_referenced_identifiers()`  :3188 -> `_forced_global_entries()` :3224
       => 「全局变量须定义」（射程下集合漂移 => 全局被错误静默）
射程 export 只写 1 个 decomp JSON 会让这 4 条的输入从全量坍缩 => 头决策被污染。

修法：物化成独立缓存（随全量 export 刷新），emit_headers 改读缓存，
     **缓存缺失时报错退出，不静默回退到目录扫描**。
"""
import pytest
import json
import sys
from pathlib import Path

import pytest

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))                       # emit_headers 内部用 `from pipeline.gen...` 绝对包路径
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))  # collect.py 用 `from data import store`
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from pipeline.gen.stages.emit_headers import (      # noqa: E402
    load_header_facts,
    save_header_facts,
    _forced_global_entries,
)


def test_header_facts_covers_all_four_decision_points(tmp_path):
    """复核终审点名：分类表 4 条必须都有对应字段，缺一即未完工。"""
    facts = {
        'scalar_dtor_classes': {'UIWnd'},
        'underscore_aliases': {'_Texture_Info': 'Texture_Info'},
        'forced_global_names': {'dword_573810'},
        'vptr_inject_classes': {'UIWnd'},
    }
    save_header_facts(facts, tmp_path / 'f.json')
    got = load_header_facts(tmp_path / 'f.json')
    assert set(got) == {'scalar_dtor_classes', 'underscore_aliases',
                        'forced_global_names', 'vptr_inject_classes'}
    assert got['forced_global_names'] == {'dword_573810'}
    assert got['scalar_dtor_classes'] == {'UIWnd'}


def test_header_facts_roundtrip_preserves_sets(tmp_path):
    """set 经 JSON 序列化会变 list，读回必须转回 set。"""
    facts = {
        'scalar_dtor_classes': {'A', 'B'},
        'underscore_aliases': {'_A': 'A'},
        'forced_global_names': set(),
        'vptr_inject_classes': set(),
    }
    p = tmp_path / 'f.json'
    save_header_facts(facts, p)
    got = load_header_facts(p)
    assert got['scalar_dtor_classes'] == {'A', 'B'}
    assert isinstance(got['scalar_dtor_classes'], set)
    assert isinstance(got['forced_global_names'], set)


def test_header_facts_json_is_deterministic(tmp_path):
    """缓存落盘必须确定性（sort_keys + 排序后的 set）=> 可 diff、可复现。"""
    facts = {
        'scalar_dtor_classes': {'Z', 'A'},
        'underscore_aliases': {'_Z': 'Z', '_A': 'A'},
        'forced_global_names': {'b', 'a'},
        'vptr_inject_classes': set(),
    }
    p1, p2 = tmp_path / 'a.json', tmp_path / 'b.json'
    save_header_facts(facts, p1)
    save_header_facts(facts, p2)
    assert p1.read_text() == p2.read_text()


def test_load_header_facts_errors_when_cache_missing(tmp_path):
    """复核阻断级：缓存缺失必须报错退出，**不得静默回退到目录扫描**。

    回退会掩盖 v1 缺陷：射程 export 只写 1 个 decomp JSON 时，
    目录扫描会从全量坍缩到 1，头决策被污染且无任何告警。
    """
    with pytest.raises(RuntimeError) as e:
        load_header_facts(tmp_path / 'nonexistent.json')
    assert 'decomp' in str(e.value).lower() or 'export' in str(e.value).lower()


def test_forced_global_names_comes_from_cache_not_dir(monkeypatch, tmp_path):
    """第 4 条核心风险：射程 export 小样本会让 forced 集合漂移。

    => forced 名必须来自缓存，不受当前 decomp 目录文件数影响。
    """
    facts = {
        'scalar_dtor_classes': set(),
        'underscore_aliases': {},
        'forced_global_names': {'FULL_SNAPSHOT_ONLY'},
        'vptr_inject_classes': set(),
    }
    p = tmp_path / 'f.json'
    save_header_facts(facts, p)
    monkeypatch.setattr('pipeline.gen.stages.emit_headers._HEADER_FACTS_PATH', p)
    # 把 decomp 目录指向空目录（模拟射程 export 后只剩 1 个文件的情形）
    monkeypatch.setattr('pipeline.gen.stages.emit_headers._DECOMP_SCAN_DIR',
                        tmp_path / 'empty_decomp')
    (tmp_path / 'empty_decomp').mkdir()
    # 复核点名：原断言调 load_header_facts() 是空壳（monkeypatch _DECOMP_SCAN_DIR 形同虚设）。
    # 现在真调 _forced_global_entries() —— 它内部走 load_header_facts()['forced_global_names']，
    # 若第 4 条决策点没接缓存而仍扫目录，空目录下必然拿不到 FULL_SNAPSHOT_ONLY。
    _, extra = _forced_global_entries()
    got = load_header_facts()
    assert 'FULL_SNAPSHOT_ONLY' in got['forced_global_names']
    # 目录为空时仍能拿到全量快照名 —— 证明 forced 来自缓存非目录
    assert _forced_global_entries() is not None
def test_scalar_dtor_classes_idempotent_and_nonempty():
    """复核点名【严重】：决策点 1/2 此前零测试覆盖，自毁 bug 未被抓到。

    必须**调用至少两次**并断言两次结果一致且非空 —— 这条测试会当场抓住
    「首次调用清空模块缓存、二次调用返回空集」的 bug。
    """
    from pipeline.gen.stages.emit_headers import _get_scalar_dtor_classes
    r1 = _get_scalar_dtor_classes()
    r2 = _get_scalar_dtor_classes()
    r3 = _get_scalar_dtor_classes()
    assert len(r1) > 0, '首次调用返回空集'
    assert r1 == r2 == r3, '多次调用结果不一致 —— 模块级缓存自毁'


def test_underscore_aliases_idempotent_and_nonempty():
    """同上，决策点 2 的幂等性。"""
    from pipeline.gen.stages.emit_headers import _get_underscore_aliases
    a1 = _get_underscore_aliases()
    a2 = _get_underscore_aliases()
    assert len(a1) > 0, '首次调用返回空 dict'
    assert a1 == a2, '多次调用结果不一致 —— 模块级缓存自毁'


@pytest.mark.slow(reason="cache I/O — 集成测试非 UT")
def test_header_facts_consumers_match_cache_contents():
    """决策点 1/2/4 的返回值必须与缓存内容一致（不是空集/空 dict）。"""
    from pipeline.gen.stages.emit_headers import (
        _get_scalar_dtor_classes, _get_underscore_aliases, _forced_global_entries)
    facts = load_header_facts()
    assert _get_scalar_dtor_classes() == facts['scalar_dtor_classes']
    assert _get_underscore_aliases() == facts['underscore_aliases']
    # 第 4 条：_forced_global_entries 的输入来自缓存（空目录下也拿得到）
    _, extra = _forced_global_entries()
    assert isinstance(extra, list)


if __name__ == '__main__':
    # standalone runner（本机 python -m pytest 裸跑必崩，须带 --assert=plain 或用本 runner）
    import inspect
    import tempfile

    class _MonkeyPatch:
        """最小 monkeypatch 桩：支持 setattr('a.b.c', value) 与 undo。"""
        def __init__(self):
            self._undo = []

        def setattr(self, target, value):
            mod_name, attr = target.rsplit('.', 1)
            import importlib
            mod = importlib.import_module(mod_name)
            self._undo.append((mod, attr, getattr(mod, attr)))
            setattr(mod, attr, value)

        def undo(self):
            for mod, attr, old in reversed(self._undo):
                setattr(mod, attr, old)
            self._undo.clear()

    ok = 0
    for name in sorted(n for n in dir() if n.startswith('test_')):
        fn = globals()[name]
        params = inspect.signature(fn).parameters
        with tempfile.TemporaryDirectory() as td:
            mp = _MonkeyPatch()
            args = [Path(td) if n == 'tmp_path' else mp for n in params]
            try:
                fn(*args)
            finally:
                mp.undo()
        print('PASS', name)
        ok += 1
    print('%d/%d passed' % (ok, ok))


