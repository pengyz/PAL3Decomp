"""ref_params TOS（C1 纯新增）单元测试——A/B 平价 + 尾折叠 + Case 行为锁。

设计定稿：data/status/review_ref_tos_merge_design_20261028.md（T1-T5 子集）。
运行: python3 tests/test_ref_params_tos.py
"""
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

# 身份/取源铁律：只准包绝对形取 ref_params（平铺双注册致 is 断言假红）
from pipeline.gen.ref_params import _fix_ref_params  # noqa: E402
from stages.stage5_fixup import _fix_ref_params as _s5_legacy  # noqa: E402

CASES = [
    # Case1 剥 &
    ('obj->Translate(&vec);', 'obj->Translate(vec);'),
    # Case2 指针→ref 补 *
    ('obj->GetAABBox(pBox);', 'obj->GetAABBox(*pBox);'),
    # tail 折叠（stage3 随迁件）
    ('w = h->_tail_000;', 'w = *(void**)(h);'),
    ('w = h->_tail_000[2];', 'w = h->_tail_000[2];'),   # 带下标不折叠
    # 无关代码不动
    ('x = y + z;', 'x = y + z;'),
]


def test_shared_fixer_behavior_locked():
    for src, want in CASES:
        got = _fix_ref_params(src)
        assert got == want, (src, got, want)


def test_ab_parity_non_tail_superset_on_tail():
    """C1 平价契约：非尾折叠件与 legacy 逐字平价；_tail_000 件=超集（D0 随迁件）。"""
    for src, _ in CASES:
        s = _fix_ref_params(src)
        lg = _s5_legacy(src)
        if re.search(r'->_tail_000(?!\[)', src):
            assert s != lg, src          # 超集面：legacy 不折叠
            assert '_tail_000' not in s, src
        else:
            assert s == lg, src


def test_single_apply_contract_double_apply_is_hazard():
    """危险性锁死（legacy 继承性质）：Case1 剥 & 后 Case2 会再补 * ⇒ 二次应用腐蚀
    （Translate(&vec)→Translate(vec)→Translate(*vec)）。管线每 stage 只跑一次；
    此测试把「禁二次应用」固化为契约——重构须保持单次语义或双侧同改。"""
    once = _fix_ref_params('obj->Translate(&vec);')
    assert once == 'obj->Translate(vec);'
    assert _fix_ref_params(once) == 'obj->Translate(*vec);'   # 已知危险面，禁静默改判


def test_tail_fold_does_not_touch_non_tail_names():
    assert _fix_ref_params('a->_tail_0001;') == 'a->_tail_0001;'
    assert _fix_ref_params('a->tail_000;') == 'a->tail_000;'


def test_case3_no_gate_degradation_matches_legacy():
    """D0' 锁：无 ctx 时行为与 legacy 完全一致（防静默改判）。"""
    src = 'Rotate(v10, v15);'
    assert _fix_ref_params(src) == _s5_legacy(src)
