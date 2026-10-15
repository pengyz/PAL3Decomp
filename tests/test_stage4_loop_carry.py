#!/usr/bin/env python3
"""[task-6 2026-10-15] stage4 单循环变量结构改写的纯函数单测（R15）。

覆盖：
  ① 命中形：for(i=Y->next;i;i=i->next){if(i->f…)break;Y=i;} ⇒ for(;Y->next;Y=Y->next){if(Y->next->f…)break;}
     （增量 i=Y->next 形同）
  ② 守卫：体 3 句 / else / 非 break 后果 / 函数内 i 其它引用 ⇒ 不改写（fired=False）
  ③ 回归锁：改写终形与受控实验 vK 同形（MSVC6 编出与原 0x401500 34 字节全同的唯一形）
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from data import store  # noqa: E402,F401  (stage4_substitution 依赖)
import tree_sitter          # noqa: E402
import tree_sitter_cpp as tscpp  # noqa: E402
import stage4_substitution as s4  # noqa: E402

_lang = tree_sitter.Language(tscpp.language())
_parser = tree_sitter.Parser(_lang)


def _apply(code: bytes, edits):
    out = code
    for start, end, repl in sorted(edits, reverse=True):
        out = out[:start] + repl + out[end:]
    return out


def _rewrite(code: bytes):
    tree = _parser.parse(code)
    fn = None
    st = [tree.root_node]
    while st:
        n = st.pop()
        if n.type == 'for_statement':
            fn = n
            break
        st.extend(reversed(n.children))
    assert fn is not None, 'no for_statement in sample'
    return s4._try_loop_carry_rewrite(fn)


SAMPLE = b'''void F() {
  NODE *OPEN;
  NODE *i;
  OPEN = this->OPEN;
  for ( i = OPEN->next; i; i = i->next )
  {
    if ( i->key == nTileIdx )
      break;
    OPEN = i;
  }
  return (int)OPEN->next;
}'''

EXPECTED = (b'void F() {\n'
            b'  NODE *OPEN;\n'
            b'  NODE *i;\n'
            b'  OPEN = this->OPEN;\n'
            b'  for ( ; OPEN->next; OPEN = OPEN->next )\n'
            b'  {\n'
            b'    if ( OPEN->next->key == nTileIdx )\n'
            b'      break;\n'
            b'    \n'          # 末句 `OPEN = i;` 删除后留下的缩进
            b'  }\n'
            b'  return (int)OPEN->next;\n'
            b'}')


def test_rewrite_fires_and_produces_single_var_form():
    fired, own, claimed = _rewrite(SAMPLE)
    assert fired
    out = _apply(SAMPLE, own)
    # 增量/条件/条件内基址全部经 OPEN（单循环变量形）
    assert b'for ( ; OPEN->next; OPEN = OPEN->next )' in out
    assert b'if ( OPEN->next->key == nTileIdx )' in out
    # 末句 `OPEN = i;` 被删、`i = i->next` 消失
    assert b'OPEN = i;' not in out
    assert b'i = i->next' not in out
    assert out == EXPECTED


def test_rewrite_accepts_increment_via_Y():
    code = SAMPLE.replace(b'i = i->next', b'i = OPEN->next')
    fired, own, _ = _rewrite(code)
    assert fired
    out = _apply(code, own)
    assert b'for ( ; OPEN->next; OPEN = OPEN->next )' in out


def test_guard_rejects_three_stmt_body():
    code = SAMPLE.replace(b'      break;\n    OPEN = i;',
                         b'      break;\n    OPEN = i;\n    n = n;')
    fired, _, _ = _rewrite(code)
    assert not fired


def test_guard_rejects_else_clause():
    code = SAMPLE.replace(b'      break;\n    OPEN = i;',
                         b'      break;\n    else\n      OPEN = i;')
    fired, _, _ = _rewrite(code)
    assert not fired


def test_guard_rejects_non_break_consequence():
    code = SAMPLE.replace(b'      break;\n    OPEN = i;',
                         b'      n = 1;\n    OPEN = i;')
    fired, _, _ = _rewrite(code)
    assert not fired


def test_guard_rejects_external_i_use():
    code = SAMPLE.replace(b'  return (int)OPEN->next;',
                         b'  i = 0;\n  return (int)OPEN->next;')
    fired, _, _ = _rewrite(code)
    assert not fired


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
