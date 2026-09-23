"""`_estimate_member_size` 对 **枚举成员** 的尺寸 —— **先写测试**（TDD）。

## 背景（2026-09-23 实测，`UIStaticFlex`/`UIPushButton` 那批布局冲突的根因）

`ida_structs.json` 把枚举记为 `size=1`（**IDB 枚举导入伪影** ✗），
emitter 据此在枚举成员后插入 `char _gap_XXX[3]` ⇒ 而 MSVC6 把枚举编译成
**int（4 字节，无 sized enum）** ⇒ gap 与枚举本体碰撞 ⇒ 后续成员整体 +4 ✗
⇒ 沿 DAG 传播（UIStaticFlex 被 7 个类按值内嵌 ✗✗）。

## 判据（证据分级）

- **MSVC6 ABI**：`enum` 恒为 `int`（4 字节）——编译器事实 ✓✓
- **W4 mangled**：`?SetFontType@UIPushButton@@QAEXW4gbFontType@@@Z` 的 `W4` = 4 字节枚举 ✓
- **gbengine 真源码**（独立项目，`include/gbengine/gbPrintFont.h`）：`enum gbFontType {0..3}` ✓✓
- **步长**：UIPushButton `m_fonttype@0x4C → m_state@0x50`、`m_state@0x50 → m_texarray@0x54` 均为 4 ✓

枚举知识源：`data/annotations/enums.json`（66 项）+ `include/gbengine/*.h` 的 `enum` 声明（12 项）。

运行：`python3 tests/test_emit_member_size_enum.py`
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline' / 'gen'))

from stages import emit_headers as E  # noqa: E402


def test_annotation_enums_are_4():
    """enums.json 登记的枚举 ⇒ 4 字节（不再信 ida_structs 的 size=1 伪影 ✓）"""
    for t in ('ACTION_KIND', 'EEffect', 'WuLing', 'NOTE_STATE', 'gbPixelFmtType',
              'DLG_MSG', 'CG_PROPINFO', 'ECPKMode'):
        got = E._estimate_member_size(t)
        assert got == 4, '%s: 期望 4（MSVC6 enum=int），实得 %s' % (t, got)


def test_gbengine_header_enums_are_4():
    """gbengine 真源码定义的枚举 ⇒ 4 字节 ✓（gbFontType 是本次病灶 ✓）"""
    for t in ('gbFontType', 'gbPoolType'):
        assert E._is_known_enum(t), '%s 应被识别为枚举（gbengine 头/enums.json）' % t
        assert E._estimate_member_size(t) == 4


def test_enum_array_multiplies():
    """`gbFontType arr[3]` ⇒ 3 × 4 = 12 ✓（数组分支先于类型分支 ✓）"""
    assert E._estimate_member_size('gbFontType[3]') == 12


def test_non_enum_size1_struct_unchanged():
    """回归：真正 1 字节的非枚举类型不得被波及 ✓"""
    # 仓内真实存在的 1 字节语义：ida_structs 若记某非枚举 struct size=1，仍按原逻辑
    assert E._estimate_member_size('unsigned char') == 1
    assert E._estimate_member_size('BYTE') == 1


def test_unknown_type_still_defaults_4():
    """回归：未知类型兜底仍为 4 ✓"""
    assert E._estimate_member_size('SomeUnknownType') == 4


def test_type_extent_includes_arrays():
    """内联体记账必须含数组维度（PalScript +224 漂移的根因 ✓）

    旧 bug：`_inner_prev = off + _estimate_member_size(t)` 把 `float[48]` 记成 4 字节
    ⇒ 之后的 gap 与数组尾部重叠 ⇒ pack(1) 顺序布局被撑大 ✗
    """
    assert E._type_extent('float') == 4
    assert E._type_extent('float[48]') == 192
    assert E._type_extent('char[256]') == 256
    assert E._type_extent('unsigned char') == 1
    assert E._type_extent('int[2][3]') == 24
    assert E._type_extent('void *') == 4



if __name__ == '__main__':
    ok = fail = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)


def test_type_extent_includes_arrays():
    """内联体记账必须含数组维度（PalScript +224 漂移的根因 ✓）

    旧 bug：`_inner_prev = off + _estimate_member_size(t)` 把 `float[48]` 记成 4 字节
    ⇒ 之后的 gap 与数组尾部重叠 ⇒ pack(1) 顺序布局被撑大 ✗
    """
    assert E._type_extent('float') == 4
    assert E._type_extent('float[48]') == 192
    assert E._type_extent('char[256]') == 256
    assert E._type_extent('unsigned char') == 1
    assert E._type_extent('int[2][3]') == 24
    assert E._type_extent('void *') == 4
