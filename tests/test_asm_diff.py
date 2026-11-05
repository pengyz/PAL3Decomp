"""L1 诊断工具层 ③：asm_diff 三态对齐（spec v2 §1.3·TDD 红→绿）。

整合复用（禁复制）：disasm/key/classify 自 byte_diff_explain import——
本件=align_disasm 三态编排（= / <原独有 / >我方独有）+首分歧高亮。
"""
from tools.asm_diff import align_disasm, first_divergence, render


def _i(addr, mn, ops=''):
    return (addr, mn, ops)


def test_align_equal():
    A = [_i(0, 'push', 'ebp'), _i(1, 'mov', 'ebp, esp')]
    pairs = align_disasm(A, list(A))
    assert all(p['tag'] == '=' for p in pairs)
    assert first_divergence(pairs) is None


def test_align_first_divergence_and_states():
    A = [_i(0, 'push', 'ebp'), _i(1, 'mov', 'ebp, esp'), _i(3, 'jl', 'short loc1')]
    B = [_i(0, 'push', 'ebp'), _i(1, 'mov', 'ebp, esp'), _i(3, 'jge', 'short loc1')]
    pairs = align_disasm(A, B)
    fd = first_divergence(pairs)
    assert fd is not None and fd['idx'] == 2
    assert fd['cls'] == 'cond-jump signedness differs (annotation type)', fd['cls']
    assert fd['orig'][1] == 'jl' and fd['ours'][1] == 'jge'


def test_align_delete_insert_states():
    A = [_i(0, 'push', 'ebp'), _i(1, 'xor', 'eax, eax')]
    B = [_i(0, 'push', 'ebp')]
    pairs = align_disasm(A, B)
    states = {p['tag'] for p in pairs}
    assert '=' in states and '<' in states, states   # 原独有=我们缺
    B2 = [_i(0, 'push', 'ebp'), _i(1, 'nop'), _i(2, 'xor', 'eax, eax')]
    pairs2 = align_disasm(A, B2)
    assert '>' in {p['tag'] for p in pairs2}, '我方独有=extra 必须显'


def test_render_marks_first_divergence():
    A = [_i(0, 'push', 'ebp'), _i(1, 'xor', 'eax, eax')]
    B = [_i(0, 'push', 'ebp'), _i(1, 'mov', 'eax, 0')]
    txt = render(align_disasm(A, B))
    assert '>>>' in txt, '首分歧必须高亮标记'
    assert '=' in txt and ('<' in txt or '>' in txt)


def test_reuse_no_copy():
    """复用断言：classify/disasm 源自 byte_diff_explain（TOS 单源·禁复制）。"""
    import tools.asm_diff as m
    # 按 __module__ 归属断（双导入身分假败修：package vs 平导=两实例不可比 identity）
    assert m.classify.__module__ == 'byte_diff_explain', \
        'classify 必须源自 byte_diff_explain（复制则 module=tools.asm_diff）'
    assert m.disasm.__module__ == 'byte_diff_explain'
    assert m.key.__module__ == 'byte_diff_explain'
