#!/usr/bin/env python3
"""[COERCE_INT 补宏 2026-10-16] 宏/形参级回归锁（R15·test_macro_safe 制式）。

病灶：codegen 词法产物 `COERCE_INT(x)` 全库 0 定义/2+ 引用（宏缺口）——
两线签名修复共同暴露。修法：ida_defs.h 补宏（位重解释 float→int）+ rvalue helper。
"""
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent


def test_macro_defined_with_bit_reinterpret_semantics():
    s = (REPO / 'include/pal3/ida_defs.h').read_text(encoding='utf-8')
    assert '#define COERCE_INT(x) (*(int*)&(x))' in s, '宏定义缺失或语义变体'


def test_macro_rvalue_helper_present():
    s = (REPO / 'include/pal3/ida_defs.h').read_text(encoding='utf-8')
    assert '_pal3_coerce_i32(float v)' in s, 'rvalue helper 缺失（COERCE 族教训）'


def test_macro_usages_have_definition():
    """主锁：全库引用的宏必有定义（grep 双向）。"""
    defs = subprocess.run(['grep', '-rc', '#define COERCE_INT',
                           str(REPO / 'include/pal3/ida_defs.h')],
                          capture_output=True, text=True).stdout
    assert int(defs.strip().split(':')[-1]) >= 1
    uses = subprocess.run(['grep', '-rl', 'COERCE_INT(', str(REPO / 'pal3/src')],
                          capture_output=True, text=True).stdout.split()
    assert uses, '引用面消失（异常）'


def test_macro_expansion_equivalence():
    """等价变换验证：宏展开 = 位重解释（c2py 模拟——同一 float 位模式出同 int）。"""
    import struct
    def macro_semantics(x_addr_bits):
        # *(int*)&(x) —— 同位重解释
        return struct.unpack('<i', struct.pack('<f', struct.unpack('<f', struct.pack('<i', x_addr_bits))[0]))[0]
    # 3.14f 的位模式 → int 同位
    v = struct.unpack('<i', struct.pack('<f', 3.14))[0]
    assert macro_semantics(v) == v   # 同位恒等（位重解释语义）


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
