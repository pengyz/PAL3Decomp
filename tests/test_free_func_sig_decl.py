"""自由函数 decl 合成分类器（data.free_sig_decl）单元测试。

背景（T1 病灶实证 2026-10-28）：原内联判据仅认 __thiscall/__cdecl/__stdcall，
__fastcall 静默落空档 ⇒ Destroy__ovl_03 无声明 ⇒ 10 单元 C2065；
且签名形若把名字放在 cc 与 `(` 之间（`int __thiscall Destroy(int nMode)`）
正则不匹配 ⇒ 同样静默丢弃（NullCallback 机制的真身）。
__fastcall 是唯一 ABI 等价的自由形（ecx 传 this；MSVC6 禁自由 __thiscall）。

运行: python3 tests/test_free_func_sig_decl.py
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

try:
    from data import free_sig_decl
except ImportError:
    from pipeline.gen.data import free_sig_decl  # noqa: E402


def test_fastcall_free_decl_emitted_with_cc():
    # ABI 等价载体：fastcall int 参走 ecx = 原 thiscall 的 this 入口
    assert free_sig_decl('Destroy__ovl_03', 'void __fastcall(int self)') \
        == 'void __fastcall Destroy__ovl_03(int self)'


def test_cdecl_drops_cc_and_empty_params_become_void():
    assert free_sig_decl('crt_sub_00540070', 'int __cdecl()') \
        == 'int crt_sub_00540070(void)'


def test_thiscall_drops_cc_and_renames_this():
    assert free_sig_decl('f', 'void __thiscall(this)') == 'void f(_this)'


def test_stdcall_keeps_cc():
    assert free_sig_decl('g', 'void __stdcall(int a)') == 'void __stdcall g(int a)'


def test_named_sig_between_cc_and_paren_accepted():
    # decomp 渲染名字夹 cc 与 ( 间（T1 二诊：line428 _dd 源即此形）⇒ 同样产 decl
    assert free_sig_decl('Destroy__ovl_03', 'void __fastcall Destroy__ovl_03(int self)') \
        == 'void __fastcall Destroy__ovl_03(int self)'
    assert free_sig_decl('Destroy__ovl_03', 'int __thiscall Destroy(int nMode)') \
        == 'int Destroy__ovl_03(int nMode)'


def test_plain_free_sig_returns_none():
    assert free_sig_decl('h', 'void(int)') is None
