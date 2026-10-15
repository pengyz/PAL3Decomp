#!/usr/bin/env python3
"""[F-CG#15/#19 2026-10-15] COERCE rvalue 判据扩展 + (POINT)__PAIR64__ 展开单测（R15）。"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from data import store  # noqa: E402,F401
import ast_transform as at   # noqa: E402
import stage3_cleanup as s3  # noqa: E402


# ── #15 COERCE rvalue 判据 ───────────────────────────────────────────
def test_coerce_binary_expression_now_rewritten():
    # 病灶形：`LODWORD(dt) | 0x100000000i64` = binary_expression ⇒ 宏内 &(x) C2102
    src = 'float f = COERCE_DOUBLE(LODWORD(dt) | 0x100000000i64);'
    out = at.transform_coerce_calls(src)
    assert out == 'float f = _pal3_coerce_f64(LODWORD(dt) | 0x100000000i64);'


def test_coerce_call_cast_literal_rewritten():
    # 注：实参判定用**语句上下文**（裸串 `COERCE_FLOAT(GetTickCount())` 会被
    # tree-sitter 解成 declaration——最烦人解析；真实生成码恒在语句位 ✓）
    def _t(e):
        return at.transform_coerce_calls('float v = %s;' % e)
    assert _t('COERCE_FLOAT(GetTickCount())') == 'float v = _pal3_coerce_f32(GetTickCount());'
    assert _t('COERCE_FLOAT((float)x)') == 'float v = _pal3_coerce_f32((float)x);'
    # 指针/cast 形实参同样改 helper（模板化 helper 吃全型——回归修 UIBigMap:300）
    assert _t('COERCE_FLOAT((UIBigMap *)&x)') == 'float v = _pal3_coerce_f32((UIBigMap *)&x);'
    assert _t('COERCE_FLOAT(0)') == 'float v = _pal3_coerce_f32(0);'


def test_coerce_lvalues_untouched():
    # 左值保持原样（最小 churn——既有 51 处用法不动）
    for e in ('COERCE_FLOAT(a)', 'COERCE_FLOAT(a->b)', 'COERCE_FLOAT(a.b)',
              'COERCE_FLOAT(arr[i])', 'COERCE_FLOAT(*p)', 'COERCE_FLOAT((a))'):
        src = 'float v = %s;' % e
        assert at.transform_coerce_calls(src) == src, e


# ── #19 (POINT)__PAIR64__ 展开 ───────────────────────────────────────
def test_pair64_point_expanded():
    out = s3._expand_pair64_point('r = (POINT)__PAIR64__(hi, lo);')
    assert out == 'r = _pal3_pair_to_point(hi, lo);'


def test_pair64_point_nested_parens_and_untouched():
    out = s3._expand_pair64_point('r = (POINT)__PAIR64__((a + b), (c | d));')
    assert out == 'r = _pal3_pair_to_point((a + b), (c | d));'
    # 非 POINT 形不动（(double) 形归 _expand_pair64_double）
    src = 'x = (double)__PAIR64__(h, l);'
    assert s3._expand_pair64_point(src) == src


# ── #23 Win32 import fnptr cast 补 __stdcall ─────────────────────────
def test_stdcall_import_cast_gets_convention():
    src = '    v6 = (void ( *)(LPSTR, LPCSTR))lstrcatA;\n'
    out = at.fix_winqapi_fnptr_casts(src)
    assert out == '    v6 = (void (__stdcall *)(LPSTR, LPCSTR))lstrcatA;\n'


def test_stdcall_import_cast_idempotent_and_scope():
    src = 'v6 = (void (__stdcall *)(LPSTR, LPCSTR))lstrcatA;'
    assert at.fix_winqapi_fnptr_casts(src) == src      # 已带约定不动（幂等）
    # 非 WINAPI 导入名不动（防误伤普通 fnptr cast）
    src2 = 'v7 = (void (*)(int, int))myFunc;'
    assert at.fix_winqapi_fnptr_casts(src2) == src2


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
