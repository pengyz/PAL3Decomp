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
    # Case2 限定形（gbOBBox=AAU 引用形）补 *；裸形出表后不动（C8·B 修补条 2026-10-28）
    ('obj->GetAABBox(pBox);', 'obj->GetAABBox(pBox);'),
    ('x->gbOBBox::GetAABBox(pBox);', 'x->gbOBBox::GetAABBox(*pBox);'),
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


def test_ab_parity_legacy_is_shared_post_c2():
    """C2 后契约：legacy 别名即共享体（C1 期的超集差已被消费）；行为面由
    test_shared_fixer_behavior_locked 钉住（含 _tail_000 折叠件）。"""
    for src, want in CASES:
        assert _s5_legacy(src) == want == _fix_ref_params(src), src


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


def test_c2_stage5_rewired_identity():
    """C2 零行为提交锁：stage5 消费共享实现（身份同一，禁本地副本）。"""
    import stages.stage5_fixup as _s5mod
    import pipeline.gen.ref_params as _rp
    assert _s5mod._fix_ref_params is _rp._fix_ref_params
    assert _s5mod._build_var_types is _rp._build_var_types
    assert _s5mod._GB_REF_PARAM_TYPES is _rp._GB_REF_PARAM_TYPES


def test_e1_noctx_degradation_absolute():
    """D0' 绝对锁（设计 T2）：无 ctx 时 Case2 对裸标识符补 * 的退化形为逐案钉死。
    C3 启用 ctx 后此面须收窄——断言变化即 D0' 门生效证据，禁静默改判。"""
    # [F1 修 2026-10-28] 裸形出表（B 修补条合法废止旧断言）；限定形为修复面
    assert _fix_ref_params('obj->GetAABBox(pBox);') == 'obj->GetAABBox(pBox);'
    assert _fix_ref_params('x->gbOBBox::GetAABBox(pBox);') == 'x->gbOBBox::GetAABBox(*pBox);'
    assert _fix_ref_params('Rotate(v10, v15);') == 'Rotate(v10, v15);'   # 元数感知：双参位不动
    assert _fix_ref_params('obj->Translate((T*)&x);') == 'obj->Translate(*(T*)&x);'


def test_e2_tail_fold_idempotent():
    """T5 明文锁：尾折叠步自身幂等。"""
    once = re.sub(r'(\w+)->_tail_000\b(?!\[)', r'*(void**)(\1)', 'w = h->_tail_000;')
    assert re.sub(r'(\w+)->_tail_000\b(?!\[)', r'*(void**)(\1)', once) == once
    assert _fix_ref_params(_fix_ref_params('w = h->_tail_000;')) == _fix_ref_params('w = h->_tail_000;')


def test_c3_stage3_rewired_ctx_gate():
    """C3 锁：stage3 消费共享实现且调用点传 ctx（D0' 证据门启用）。"""
    import stages.stage3_cleanup as _s3
    import pipeline.gen.ref_params as _rp
    assert _s3._fix_ref_params is _rp._fix_ref_params
    import inspect
    assert '_fix_ref_params(code, ctx)' in inspect.getsource(_s3.run)


def test_c3_stage3_rewired_ctx_gate():
    """C3 锁：stage3 消费共享实现且调用点传 ctx（D0p 证据门启用）。"""
    import stages.stage3_cleanup as _s3
    import pipeline.gen.ref_params as _rp
    assert _s3._fix_ref_params is _rp._fix_ref_params
    import inspect
    assert '_fix_ref_params(code, ctx)' in inspect.getsource(_s3.run)


def test_c5_call_return_type_disambiguated():
    """C5 锁：同名异义已双改名（node 入参/注解源 vs name 入参/decomp 源），禁回流同名。"""
    import stages.stage4_substitution as _s4, stages.stage5_fixup as _s5
    assert hasattr(_s4, '_node_call_return_type') and not hasattr(_s4, '_call_return_type')
    assert hasattr(_s5, '_sig_call_return_type') and not hasattr(_s5, '_call_return_type')


def test_t2p_pointworldtoscr_qualified():
    """T2' 首键：gbCamera::PointWorldToScr {1,2}（A 级 mangled：PAUgbVec3D@@AAM1）。
    三面真契约：@1/2 剥 & · @0 指针不动 · no-ctx 裸标识符退化补 *（E1 同款危险面，
    ctx 证据门启用后应收窄——变化即门生效证据）。"""
    assert _fix_ref_params('x->gbCamera::PointWorldToScr(&pOut, &v48, &v40);') \
        == 'x->gbCamera::PointWorldToScr(&pOut, v48, v40);'
    assert _fix_ref_params('f->gbCamera::PointWorldToScr(p, a, b);') \
        == 'f->gbCamera::PointWorldToScr(p,  *a,  *b);'   # no-ctx 退化面（已知）
    assert _fix_ref_params('x->gbCamera::PointWorldToScr(&p, v48, &v40);') \
        == 'x->gbCamera::PointWorldToScr(&p,  *v48, v40);'
