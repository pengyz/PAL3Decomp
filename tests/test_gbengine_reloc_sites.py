#!/usr/bin/env python3
"""[T146/P2] gbengine_compare 重定位核对的纯函数单测（R15：改工具必须跑其测试）。

覆盖：
  ① reloc_site_starts —— 字节偏移集合 → 站点起点（连续 4 字节=1 站点）；
     原实现把每字节偏移当站点 ⇒ 每站点重复计 4 次、比较窗口错位（ok 恒 0）。
  ② compare_bytes 的 reloc_target 站点级三分：ok / mismatch / unresolved。
     —— 纯计量，不改变 perfect 判据（回归断言一并锁死）。
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / 'tools'))

import gbengine_compare as gc  # noqa: E402


def test_reloc_site_starts_groups_4byte_runs():
    # 两个站点：0..3 与 8..11；4..7 不是重定位
    offs = {3, 1, 0, 2, 11, 9, 8, 10}
    assert gc.reloc_site_starts(offs) == [0, 8]


def test_reloc_site_starts_single_site_and_tail():
    # 单站点 + 尾部不足 4 字节的残段（仍取起点，越界由调用方判断）
    assert gc.reloc_site_starts({5, 6, 7, 8}) == [5]
    assert gc.reloc_site_starts({5, 6}) == [5]
    assert gc.reloc_site_starts(set()) == []


def test_compare_bytes_reloc_target_three_way():
    # 3 个站点（各 4 字节）：ok(原值在有效节范围) / ok / unresolved
    # [T146/P2 判据变更] 只看 original 的目标 VA 是否在有效节范围（obj 的 reloc 值
    # 是未链接的相对 addend，exe 是最终指令流 ⇒ cv == ov 恒假，不能双侧比较）。
    # PAL3.exe 节表（image base 0x400000）：.text 0x401000-0x5695d0 · .rdata 0x56a000-0x57f178
    #   · .data 0x580000-0x1897000 · .rsrc 0x1897000-0x189c3ca
    size = 12
    orig = bytearray(size)
    comp = bytearray(size)
    relocs = set()
    # 站点 0：ok —— 原值 0x00401000（.text 起点）
    orig[0:4] = (0x00401000).to_bytes(4, 'little')
    comp[0:4] = (0x00000000).to_bytes(4, 'little')  # obj addend
    # 站点 4：ok —— 原值 0x00500000（.text 内）
    orig[4:8] = (0x00500000).to_bytes(4, 'little')
    comp[4:8] = (0x00000000).to_bytes(4, 'little')
    # 站点 8：unresolved —— 原值 0x00000000（不在任何节）
    orig[8:12] = (0x00000000).to_bytes(4, 'little')
    comp[8:12] = (0x00000000).to_bytes(4, 'little')
    for s in (0, 4, 8):
        for b in range(4):
            relocs.add(s + b)
    res = gc.compare_bytes(bytes(comp), bytes(orig), 'T', verbose=False,
                           relocs=relocs)
    rt = res['reloc_target']
    assert rt['total'] == 3, rt
    assert rt['ok'] == 2, rt       # 站点 0 + 4 都在 .text
    assert rt['mismatch'] == 0, rt  # 新判据不比 cv/ov，无 mismatch
    assert rt['unresolved'] == 1, rt  # 站点 8 不在任何节
    # 回归锁：完美性判据不被核对改变（全部站点差异都被跳过 ⇒ perfect）
    assert res['perfect'] is True
    # 隐藏差异字节数（逐字节实数）：站点0 四字节同=0；
    # 站点4 00 20 40 00 vs 00 30 40 00 ⇒ +5 一字节；
    # 站点8 00 40 40 00 vs 00 00 00 00 ⇒ +9/+10 两字节 ⇒ 共 3
    assert res['reloc_diffs'] == 3


def test_compare_bytes_perfect_semantics_unchanged():
    # 字节全同定义回归锁：长度必须相等，且非重定位字节必须逐字节相同
    a = bytes([1, 2, 3, 4])
    assert gc.compare_bytes(a, a, 'T', verbose=False)['perfect'] is True
    assert gc.compare_bytes(a, a[:3], 'T', verbose=False)['perfect'] is False
    b = bytes([1, 2, 9, 4])
    assert gc.compare_bytes(b, a, 'T', verbose=False)['perfect'] is False
    # 同一字节若在重定位位 ⇒ 计为 match（don't care）
    assert gc.compare_bytes(b, a, 'T', verbose=False,
                            relocs={2})['perfect'] is True


def test_compare_bytes_rel32_target_formula_plus4():
    # [task-6 2026-10-15] REL32 目标 = va + s0 + **4** + rel32（A 级：0x401059
    # `e8 42 07 00 00 call` ⇒ s0=0x0A、rel32=0x742 ⇒ 0x4017A0 = Reset ✓；
    # +5 得 0x4017A1 ✗）。rel32 读数 = original[s0:s0+4]（signed）。
    va = 0x401050
    s0 = 0x0A
    rel32 = 0x742
    size = 16
    orig = bytearray(size)
    comp = bytearray(size)
    orig[s0:s0 + 4] = rel32.to_bytes(4, 'little', signed=True)
    relocs = {s0 + b for b in range(4)}
    res = gc.compare_bytes(bytes(comp), bytes(orig), 'T', verbose=False,
                           relocs=relocs, reloc_type_map={s0: 20}, va=va)
    rt = res['reloc_target']
    # 目标 0x4017A0 ∈ .text ⇒ ok；若用 +5（0x4017A1 仍在界内）此断言不区分 ⇒
    # 由下一用例的边界钉死 +4。
    assert rt == {'total': 1, 'ok': 1, 'mismatch': 0, 'unresolved': 0}, rt


def test_compare_bytes_rel32_boundary_distinguishes_plus5():
    # 边界钉：+4 形目标 = 0x5695CF（.text 最后有效字节，hi=0x5695d0 开区间），
    # +5 形会落到 0x5695D0（出界）⇒ 若实现误用 +5，本用例必红。
    va = 0x401050
    s0 = 0x0A
    rel32 = 0x5695CF - (va + s0 + 4)
    assert rel32 == 0x168571
    size = 16
    orig = bytearray(size)
    comp = bytearray(size)
    orig[s0:s0 + 4] = rel32.to_bytes(4, 'little', signed=True)
    relocs = {s0 + b for b in range(4)}
    res = gc.compare_bytes(bytes(comp), bytes(orig), 'T', verbose=False,
                           relocs=relocs, reloc_type_map={s0: 20}, va=va)
    rt = res['reloc_target']
    assert rt == {'total': 1, 'ok': 1, 'mismatch': 0, 'unresolved': 0}, rt


def test_compare_bytes_rel32_negative_and_no_va():
    # 负 rel32（回跳目标）：va=0x401500 → 目标 0x401050（signed 读数必须为负）
    va = 0x401500
    s0 = 0x0A
    rel32 = 0x401050 - (va + s0 + 4)   # = -0x4BE
    assert rel32 < 0
    size = 16
    orig = bytearray(size)
    comp = bytearray(size)
    orig[s0:s0 + 4] = rel32.to_bytes(4, 'little', signed=True)
    relocs = {s0 + b for b in range(4)}
    res = gc.compare_bytes(bytes(comp), bytes(orig), 'T', verbose=False,
                           relocs=relocs, reloc_type_map={s0: 20}, va=va)
    assert res['reloc_target']['ok'] == 1, res['reloc_target']
    # 无 va 上下文 ⇒ 不猜，落 unresolved
    res2 = gc.compare_bytes(bytes(comp), bytes(orig), 'T', verbose=False,
                            relocs=relocs, reloc_type_map={s0: 20})
    assert res2['reloc_target'] == {'total': 1, 'ok': 0, 'mismatch': 0,
                                    'unresolved': 1}, res2['reloc_target']


# ─── [mismatch 修法 1+2] rsite 名字比对归一 + ctor/dtor 族容差 ─────────
sys.path.insert(0, str(REPO / 'pipeline'))
import compare_pal3 as cp3  # noqa: E402


def test_norm_name_strips_void_param_suffix():
    assert cp3._norm_name('CEffGrid::~CEffGrid(void)') == 'CEffGrid::~CEffGrid'
    assert cp3._norm_name('X::~X ( void )') == 'X::~X'
    assert cp3._norm_name('Foo::Bar(uint)') == 'Foo::Bar'
    # 非 (void)/(uint) 尾参表不剥（真签名差异不得被归一吞掉）
    assert cp3._norm_name('A::B(int)') == 'A::B(int)'


def test_ctor_dtor_family():
    for n in ('UIWnd::~UIWnd', "CCBLineupWindow::`scalar deleting destructor'(uint)",
              'CEffCylinder::_scalar_dtor_3db0(int)', 'UIWnd::_sdtor_14',
              'UI3DCtrl::ctor(int)', 'UISceneMap::ctor_90(void)',
              'UICoverFrm::UICoverFrm(void)', 'UIFrameWnd::_UIFrameWnd(void)'):
        assert cp3._ctor_dtor_family(n), n
    for n in ('RoleSystem::UpdateTransform(void)', 'sub_445FE0',
              'Array::Insert(void *,void *)', 'OpenNULLFile::OpenNULLFileX(void)'):
        assert not cp3._ctor_dtor_family(n), n


def test_rsite_names_match_three_way():
    # ① 归一相等（修法 1）
    assert cp3._rsite_names_match('CEffGrid::~CEffGrid(void)', 'CEffGrid::~CEffGrid')
    # ② 双侧 ctor/dtor 族（修法 2，含跨类——IDB 命名互换）
    assert cp3._rsite_names_match('JusticeBookUI::JusticeBookUI(void)',
                                  'JusticeBookUI::~JusticeBookUI')
    assert cp3._rsite_names_match('scScriptInstance::~scScriptInstance(void)',
                                  'UIWnd::~UIWnd')
    # ③ 真差异保持 mismatch（判别力回归锁）
    assert not cp3._rsite_names_match('Array::Insert(void *,void *)',
                                      'Array::Erase(int,int)')
    assert not cp3._rsite_names_match('CEffect::DestroyCallback(void)',
                                      'CEffShock::~CEffShock')


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
