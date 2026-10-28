"""[TOS 2026-10-28·C4] 通用文本件单一真相源（_strip_outer_parens，stage3 原件正典
——语义=完整包裹判据；stage5 同义实现收敛于此，None-safe 为正典形）。"""

def _strip_outer_parens(text):
    """剥掉**完整包裹**在最外层的圆括号（`(a) + (b)` 这类不剥）。"""
    s = str(text or '').strip()
    while s.startswith('(') and s.endswith(')'):
        depth, complete = 0, True
        for i, ch in enumerate(s):
            if ch == '(':
                depth += 1
            elif ch == ')':
                depth -= 1
                if depth == 0 and i != len(s) - 1:
                    complete = False
                    break
        if not complete or depth != 0:
            break
        s = s[1:-1].strip()
    return s
