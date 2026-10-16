# R15（data/status/_d1_ledger.md）：xref 覆盖扩展纯函数单测——语料外（gap 域）补扫
from tools.member_existence_gate import classify_gap_regions, scan_shape_index

def test_gap_regions_complement():
    # 函数域 [0x1000,+0x100), [0x1200,+0x100) 在 .text [0x1000,0x1400) ⇒ 缺口=0x1100..0x1200, 0x1300..0x1400
    gaps = classify_gap_regions((0x1000, 0x1400), [(0x1000, 0x100), (0x1200, 0x100)])
    assert gaps == [(0x1100, 0x100), (0x1300, 0x100)]

def test_gap_regions_full_cover():
    assert classify_gap_regions((0x1000, 0x1200), [(0x1000, 0x200)]) == []

def test_gap_regions_overlap_clip():
    # 函数域与 .text 边界外溢出须裁剪
    gaps = classify_gap_regions((0x1000, 0x1100), [(0x0F00, 0x200)])
    assert gaps == []

def test_gap_regions_empty_funcs():
    assert classify_gap_regions((0x1000, 0x1100), []) == [(0x1000, 0x100)]

def test_scan_shape_index_gap_evidence():
    # 语料外裸字节：mov eax,[0xDC1B5C] = A1 5C 1B DC 00 ⇒ mov_load 形态命中
    code = bytes.fromhex('A15C1BDC00') + bytes.fromhex('C3')
    idx = scan_shape_index(code, base_va=0x401000, va2off=lambda va: va - 0x401000,
                           ranges=[(0x401000, len(code))])
    assert 0x00DC1B5C in idx
    assert idx[0x00DC1B5C][0][2] == 'mov_load'

def test_scan_shape_index_tolerates_junk():
    # 垃圾字节（不可解码）不得崩——单遍前进（R15 契约：确定性、零 IO 副作用）
    code = bytes.fromhex('0F0B') * 4 + bytes.fromhex('C3')
    idx = scan_shape_index(code, base_va=0x401000, va2off=lambda va: va - 0x401000,
                           ranges=[(0x401000, len(code))])
    assert isinstance(idx, dict)
