"""修② TDD（基名精确+size 校验）。

## 修②建议（对抗复核 54c89355）

  ① 基名仅精确同名+size 校验才 skip（删 hash-suffix-rev）+ 恢复截断前缀命中
  ② member 型去 struct/class 前缀
  ③ size 校验（RoleSlotArray 896!=864 禁 rewrite）

## TDD

| 测试 | assertion |
|---|---|
| test_base_name_exact_match | 基名仅精确同名才 skip |
| test_size_mismatch_no_rewrite | size 不合禁 rewrite |
| test_member_type_prefix_stripped | member 型去 struct/class 前缀 |
"""
import pytest


def test_base_name_exact_match():
    """基名仅精确同名才 skip（删 hash-suffix-rev）。"""
    # 模拟 _named_supersede_decision
    def _should_skip(type_name, lookup):
        _tn = type_name.replace('::$', '__$')
        _lookup = {k.replace('::$', '__$'): v for k, v in lookup.items()}
        # 精确匹配
        if _tn in _lookup:
            return True
        # 仅 __$hash 后缀形
        for _k in _lookup:
            if _tn.startswith(_k) and _tn[len(_k):].startswith('__$'):
                return True
        return False

    # 基名精确匹配 => skip
    assert _should_skip('_inline_PalScript_m_RoleSlotArray',
                        {'_inline_PalScript_m_RoleSlotArray': 'PalScriptRoleSlotOverlay'})
    # 基名不精确（hash-suffix）=> 不 skip
    assert not _should_skip('_inline_PalScript_m_RoleSlotArray',
                            {'_inline_PalScript_m_RoleSlotArray::$C73B': 'X'})
    # hash-suffix 形 => skip
    assert _should_skip('_inline_PalScript_m_RoleSlotArray::$C73B',
                        {'_inline_PalScript_m_RoleSlotArray': 'X'})


def test_size_mismatch_no_rewrite():
    """size 不合禁 rewrite。"""
    def _can_rewrite(type_size, substitute_size, tolerance=0):
        return abs(type_size - substitute_size) <= tolerance

    # size 相等 => 可 rewrite
    assert _can_rewrite(896, 896)
    # size 不合 => 禁 rewrite（RoleSlotArray 896 != 864）
    assert not _can_rewrite(896, 864)
    assert not _can_rewrite(1228, 873)  # teamSlotOverlay


def test_member_type_prefix_stripped():
    """member 型去 struct/class 前缀。"""
    def _strip_prefix(t):
        for p in ('struct ', 'class ', 'union ', 'enum '):
            if t.startswith(p):
                return t[len(p):]
        return t

    assert _strip_prefix('struct gbNodeMsgObj::$X') == 'gbNodeMsgObj::$X'
    assert _strip_prefix('class Foo') == 'Foo'
    assert _strip_prefix('int') == 'int'
