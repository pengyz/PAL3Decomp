#!/usr/bin/env python3
"""[task F-STR/F-TAB/F-CST 2026-10-15] 纯函数单测（R15）。

覆盖：
  ① stage4 `_fix_setvariant_enum_or` —— enum|enum 实参 ⇒ (GBPARAMHANDLE) cast
     （幂等守卫：已 cast 的不动；非 GBPARAM_ 形不动）
  ② emit_headers `_ann_global_type_map` —— globals.json 复活型解析：
     orig_type 优先 > 非 skip 的 type > skip 无 orig_type 不入表；坏地址跳过
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from data import store  # noqa: E402,F401  (stage4_substitution 依赖)
import stage4_substitution as s4    # noqa: E402
import emit_headers as eh           # noqa: E402


# ── ① F-CST ──────────────────────────────────────────────────────────
def test_setvariant_enum_or_casted():
    src = ('SetVariant(GBPARAM_TEXTURE1|GBPARAM_PROJMATRIX, &v8);')
    out = s4._fix_setvariant_enum_or(src)
    assert out == 'SetVariant((GBPARAMHANDLE)(GBPARAM_TEXTURE1|GBPARAM_PROJMATRIX), &v8);'


def test_setvariant_enum_or_three_operand_chain():
    src = 'SetVariant(GBPARAM_A|GBPARAM_B|GBPARAM_C, x)'
    out = s4._fix_setvariant_enum_or(src)
    assert out == 'SetVariant((GBPARAMHANDLE)(GBPARAM_A|GBPARAM_B|GBPARAM_C), x)'


def test_setvariant_enum_or_idempotent():
    src = 'SetVariant((GBPARAMHANDLE)(GBPARAM_TEXTURE1|GBPARAM_PROJMATRIX), &v8);'
    assert s4._fix_setvariant_enum_or(src) == src


def test_setvariant_plain_arg_untouched():
    src = 'SetVariant(GBPARAM_TEXTURE1, x); SetVariant(v1, x);'
    assert s4._fix_setvariant_enum_or(src) == src


# ── ② F-TAB 复活型解析 ───────────────────────────────────────────────
def test_ann_global_type_map_orig_type_wins():
    data = {
        '0x00570298': {'name': 'off_570298', 'type': 'const char *',
                       'orig_type': 'const char *'},
        '0x005AC098': {'name': 'off_5AC098', 'type': 'void *[]'},
    }
    m = eh._ann_global_type_map(data)
    assert m[0x570298] == 'const char *'
    assert m[0x5AC098] == 'void *[]'


def test_ann_global_type_map_skip_without_orig_type_excluded():
    data = {
        '0x0056F314': {'name': 'off_56F314', 'type': 'skip',
                       'skip_reason': 'rdata:compiler_generated'},
        '0x0056F328': {'name': 'off_56F328', 'type': 'skip',
                       'orig_type': 'const char *[]'},
    }
    m = eh._ann_global_type_map(data)
    assert 0x56F314 not in m              # skip 无 orig_type ⇒ 回退名字启发
    assert m[0x56F328] == 'const char *[]'  # tombstone orig_type 优先


def test_ann_global_type_map_bad_addr_and_non_dict_skipped():
    data = {'nonsense': {'type': 'int'}, '0xZZ': {'type': 'int'},
            '0x00401000': 'not-a-dict', '0x00402000': {'type': 'int'}}
    m = eh._ann_global_type_map(data)
    assert m == {0x402000: 'int'}


# ── ③ F-TAB 定义侧字符串路径排除指针型 ──────────────────────────────
def test_read_init_value_pointer_array_not_stringified():
    # [F-TAB 修] 指针数组型（const char *[]）此前命中字符串路径 ⇒
    # `T* X[] = "字节串"` ⇒ C2440 ×4。指针型必须排除。
    foff = 0x56F314 - 0x400000
    exe = b'\x00' * foff + b'l\n[\x00' + b'\x00' * 16
    val = eh._read_init_value(0x56F314, 'const char *[]', exe)
    assert val is None or not (isinstance(val, str) and val.startswith('"')), val
    # 真 char[] 字符串型仍走字符串路径（回归锁）
    val2 = eh._read_init_value(0x56F314, 'char[]', exe)
    assert isinstance(val2, str) and val2.startswith('"'), val2


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
