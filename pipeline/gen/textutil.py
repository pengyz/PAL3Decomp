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


# [T4 批1 2026-10-29] 删析构调用形转写（B 组 _sdtor_call_dtor 0x4431B0=ret 4 flags 形证据）：
# Hex-Rays 把 ~X()/delete X 渲成 X->Cls::_sdtor_call_dtor(0/1) ⇒ 还原源语义（等价变换）。
import re as _re_t
_DDTOR_STMT = _re_t.compile(
    r'(?m)^(?P<ind>\s*)(?P<recv>.+?)->(?P<cls>\w+)::_sdtor_call_dtor\((?P<flag>[01])\);')


def rewrite_deleting_dtor_calls(code):
    """flags=0 → recv->~cls()（显式析构）；flags=1 → delete recv（delete）。
    限定形（Cls::_sdtor_call_dtor）才转写——非限定形无类证据，保持原样（批2 挂账）。"""
    def _sub(m):
        if m.group('flag') == '0':
            return '%s%s->~%s();' % (m.group('ind'), m.group('recv'), m.group('cls'))
        return '%sdelete %s;' % (m.group('ind'), m.group('recv'))
    return _DDTOR_STMT.sub(_sub, code)
