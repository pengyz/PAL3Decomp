"""S2 的纯函数单测（R15 ✓：新逻辑必须先过单测，再进管线）。

不 import 管线模块（避免依赖 ✓）；用**与 stage3_cleanup 中逐字相同**的两段逻辑：
  ① owner 链正则（H6 后的版本 ✓）
  ② _drop_self_arg（H6 后剥 `&` 的版本 ✓）
以及 ③ stub 分支的 self 丢弃规则 ✓
真实样本取自本会话实测（data/status/_d1_ledger.md ✓）。
"""
import re
import sys

# ── ① owner 链正则（与 stage3_cleanup.py 的 AST 层两处一致 ✓）
OWNER_NEW = r'([A-Za-z_]\w*(?:(?:\s*(?:->|\.)\s*[A-Za-z_]\w*)|(?:\s*\[[^\[\]]*\]))*)'
OWNER_OLD = r'(\w+(?:\s*->\s*\w+)*)'
RX_NEW = re.compile(OWNER_NEW + r'\s*->\s*__vftable\s*->\s*(\w+)')
RX_OLD = re.compile(OWNER_OLD + r'\s*->\s*__vftable\s*->\s*(\w+)')

# ── ② _drop_self_arg（H6 后：剥简单 cast **与** 前导 & ✓）
def drop_self_arg(args, obj):
    if not args:
        return args
    first = args[0].strip()
    obj_n = ' '.join(obj.split())
    stripped = re.sub(r'^\(\s*[\w :]+\*+\s*\)\s*', '', first).strip()
    if stripped.startswith('&'):
        stripped = stripped[1:].strip()
    if first == obj_n or stripped == obj_n:
        return args[1:]
    return args

# ── ③ stub 分支的 self 丢弃（S2 新增 ✓）
SELF_FIRST = frozenset({'CreateFromMemory'})

def stub_drop(args, method):
    if args and method in SELF_FIRST and args[0].strip().startswith('&'):
        return args[1:]
    return args


# ===== ① 正则：必须抓到**完整链**（H6 的核心 ✓）
def test_owner_regex_captures_full_chain():
    cases = [
        ('this->me_Role[2].m_RoleAttCng[0].pDebugTex->__vftable->IsLoaded',
         'this->me_Role[2].m_RoleAttCng[0].pDebugTex', 'IsLoaded'),
        ('this->m_Slots[21].m_Widget->__vftable->ShowWindow',
         'this->m_Slots[21].m_Widget', 'ShowWindow'),
        ('this->mb_OK.m_texarray.m_ptex[1]->__vftable->CreateFromMemory',
         'this->mb_OK.m_texarray.m_ptex[1]', 'CreateFromMemory'),
        ('m_pbktex->__vftable->UpdateTexture', 'm_pbktex', 'UpdateTexture'),
    ]
    for text, want_owner, want_m in cases:
        m = RX_NEW.search(text)
        assert m, 'NEW 正则未匹配: %s' % text
        assert m.group(1) == want_owner, '期望 owner=%r 实得 %r' % (want_owner, m.group(1))
        assert m.group(2) == want_m, '期望 method=%r 实得 %r' % (want_m, m.group(2))


# ===== ② 旧正则的**截断**必须被记录为"已修复的病灶"（回归防护 ✓）
def test_old_regex_truncated_and_new_fixes_it():
    text = 'this->me_Role[2].m_RoleAttCng[0].pDebugTex->__vftable->IsLoaded'
    assert RX_OLD.search(text).group(1) == 'pDebugTex', '旧正则应截断为 pDebugTex（病灶 ✓）'
    assert RX_NEW.search(text).group(1) == 'this->me_Role[2].m_RoleAttCng[0].pDebugTex', '新正则应给完整链 ✓'


# ===== ③ _drop_self_arg：剥 cast 与 &（H6 ✓）
def test_drop_self_arg_handles_amp_and_cast():
    cases = [
        (['this', 'pData'], 'this', ['pData']),
        (['&this->mb_OK.m_ptex[1]', '0'], 'this->mb_OK.m_ptex[1]', ['0']),
        (['(gbTexture **)&this->m_pbk', '1'], 'this->m_pbk', ['1']),
        (['pData'], 'this', ['pData']),          # 不相干 ⇒ 不动 ✓
    ]
    for args, obj, want in cases:
        got = [a for a in drop_self_arg(list(args), obj)]
        assert got == want, 'args=%r obj=%r 期望 %r 实得 %r' % (args, obj, want, got)


# ===== ④ stub 分支的 self 丢弃（S2 的关键修复 ✓）
def test_stub_branch_drops_self_for_self_first_methods():
    # 病灶形态 ✓：`(*v5)->CreateFromMemory(&X, 1)` 的实参列表
    assert stub_drop(['&this->m_mapbk.m_texs.m_ptex[4]', '1'], 'CreateFromMemory') == ['1']
    # 非 self-first 方法 ⇒ **不动** ✓（避免猜测性归一 ✗）
    assert stub_drop(['&x', '1'], 'SomeOtherMethod') == ['&x', '1']
    # 首参不是取址形 ⇒ 不动 ✓
    assert stub_drop(['pData', '1'], 'CreateFromMemory') == ['pData', '1']


if __name__ == '__main__':
    ok = fail = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except AssertionError as e:
                print('  FAIL %s: %s' % (nm, e)); fail += 1
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)
