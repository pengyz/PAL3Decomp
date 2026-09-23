"""对齐感知 gap 抑制 —— sg_* / ARC_PlayerAtt 家族漂移根因（TDD）。

旧 bug 两型：
① `_estimate_member_size('ARC_PlayerItem')` 取 ida_structs size=10 ✗
   —— C++ 编译器按对齐(4)补足为 12 ⇒ 之后的显式 gap 与自然填充叠加 ⇒ +4 ✗
② gap 小于下一成员对齐 ⇒ 编译器本来就会自然填充 ⇒ 显式 gap 反而多余 ✗

判据：`_gap_needed(start_off, off, next_type)` = off-start_off 是否**大于**
编译器自然填充量（(-start_off) % align(next_type)）；自然填充已覆盖 ⇒ 不发 gap ✓
"""
import sys
from pathlib import Path
PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT)); sys.path.insert(0, str(PROJECT_ROOT/'pipeline')); sys.path.insert(0, str(PROJECT_ROOT/'pipeline'/'gen'))
from stages import emit_headers as E

def test_type_align_primitives():
    assert E._type_align('char') == 1
    assert E._type_align('BYTE') == 1
    assert E._type_align('short') == 2
    assert E._type_align('int') == 4
    assert E._type_align('float') == 4
    assert E._type_align('void *') == 4

def test_type_align_d3dx():
    assert E._type_align('D3DXVECTOR3') == 4
    assert E._type_align('D3DXCOLOR') == 4

def test_type_align_struct_from_ida():
    """ida_structs 有成员的类型 ⇒ 对齐 = 成员对齐最大值（上限 8）✓"""
    # ARC_PlayerItem: DWORD+int+short ⇒ align 4
    assert E._type_align('ARC_PlayerItem') == 4

def test_gap_needed_natural_pad_covers():
    """start=0x36A, next off=0x36C, next align=4 ⇒ 自然填充 2 恰好覆盖 gap 2 ⇒ 不发 ✗→✓"""
    assert E._gap_needed(0x36A, 0x36C, 'ARC_PlayerItem') is False

def test_gap_needed_real_gap():
    """真正缺字节时仍要发 gap ✓"""
    assert E._gap_needed(0x40, 0x4C, 'D3DXVECTOR3') is True   # 缺 12，自然填充 0

def test_gap_needed_exact_zero_gap():
    assert E._gap_needed(0x4C, 0x4C, 'int') is False

if __name__ == '__main__':
    ok=fail=0
    for nm,fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try: fn(); print('  PASS',nm); ok+=1
            except Exception as e: print('  FAIL',nm,type(e).__name__,e); fail+=1
    print('Results: %d passed, %d failed'%(ok,fail)); sys.exit(1 if fail else 0)
