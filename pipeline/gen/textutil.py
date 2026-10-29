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


# [T5(i) 2026-10-29] SingletonThunk 胶水剥离——编译器随全局对象定义再生（B9 imm32 E9 形证据），
# 手写胶水（atexit 注册+立即调用）为合成物渲染残骸，等价变换删除。
# [D2 修 2026-10-29·复核 f20cc6e7] 证据分流：仅 4 胶水件可剥——
# 0x431D90/0x431DB0=Iostream_init CRT 对称双剥（Site1）· 0x4B6D70/0x4BFD60=
# NullCallback 空跳（Site4/5）；0x431E70/0x431EC0=手工单例语义对（Site2/3，带
# 0xD8C324 位守卫 + 配对 cleanup atexit）**禁剥**——半剥离=真初始化丢失（D2）。
_GLUE_NAMES = ('00431D90', '00431DB0', '004B6D70', '004BFD60')
_ST_GLUE = _re_t.compile(
    r'(?m)^\s*(?:atexit\(\s*(?:\([^;]*?\)\s*)?SingletonThunk_(?:%s)\s*\)'
    r'|SingletonThunk_(?:%s)\s*\([^;]*?\))\s*;\s*\n' % ('|'.join(_GLUE_NAMES), '|'.join(_GLUE_NAMES)))


def strip_singleton_thunk_glue(code):
    """删**证据核验**的 4 胶水件语句。语义对（Site2/3）禁剥——见 D2 注记。"""
    return _ST_GLUE.sub('', code)


# [D2b 2026-10-29] SingletonThunk 伪参剥离——B9 imm32 形（自载对象、零栈参读取）⇒
# Hex-Rays ecx 建模渲染的 (this) 实参为噪声；保留语句（Site2/3 语义对）仅剥参。
_ST_ARG = _re_t.compile(r'(SingletonThunk_[0-9A-Fa-f]+)\s*\([^;]*?\)')


def strip_singleton_thunk_args(code):
    """SingletonThunk_*() 调用剥伪参（thunk 零栈参=字节形证据）。"""
    return _ST_ARG.sub(r'\1()', code)
