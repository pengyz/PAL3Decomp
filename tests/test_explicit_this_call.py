"""`Cls::M(obj, rest…)` → `((Cls *)obj)->M(rest…)` 的单元测试（**真实样本**）。

# 病灶层（2026-09-21 已只读验证，见模块内注释）

Hex-Rays **自己就产出**"类限定名 + 显式 this 作首实参"的形态：

    CCBControl::SetParam(*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8), 513, -1);
    NPC::UpdateAnim((NPC *)(v3 + 156304));

codegen 从未把它适配成 C++ 成员调用语法 ⇒ MSVC：
`C2660 'SetParam' : function does not take 3 parameters`
（声明 `int SetParam(int nVal, int nVal2)` 是 **2** 参 ⇒ 多出的第一个实参就是 `this`）。

实测规模（基线普查）：**53 条 / 13 个名字**。

# 安全闸（本测试的契约）

仅在"签名含 `__thiscall` **且** 实参数 == 形参数 + 1"时改写。该闸天然豁免：
声明/定义站点（实参数恰等于形参数）、真 static 调用（形参数已对齐）、签名未知、可变参。

运行方式: python3 tests/test_explicit_this_call.py
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
for p in ("pipeline/gen", "pipeline", "."):
    sys.path.insert(0, str(PROJECT_ROOT / p))

from stages.stage5_fixup import (  # noqa: E402
    _fix_explicit_this_calls, _sig_arity, rewrite_explicit_this_call,
)

# 真实签名（形如 `store.method_sigs['Cls::M']`，已实测的形态）
SIGS = {
    ('CCBControl', 'SetParam'): 'int __thiscall(int nVal, int nVal2)',          # 2 形参
    ('CCBSystem', 'GetCmdData'): 'char * __thiscall(int idx)',                  # 1
    ('InputSystem', 'ProcessKeyboard'): 'void __thiscall(int a1)',              # 1
    ('NPC', 'UpdateAnim'): 'void __thiscall()',                                 # 0
    ('gbOBBox', 'IsColOBB'): 'int __thiscall(struct gbOBBox *)',                # 1
    ('CCBControl', 'StaticThing'): 'void __cdecl(int, int)',                    # static
    ('Weird', 'Variadic'): 'int __thiscall(...)',                               # 可变参
    # ⚠️ 2026-09-21 实测的**两源不一致**样本：decomp 侧 2 参，生成头（注解）侧 3 参
    #    `char * DelTask(int nIndex, _BYTE *p_BYTE, int *p_DWORD);`
    # 调用 `A->CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v13)`（3 实参）⇒ 2+1==3 会误开闸 ✗
    ('CCBStage', 'DelTask'): 'char * __thiscall(int, _BYTE *)',
}


def _lookup(c, m):
    return SIGS.get((c, m))


# ===== ① 签名元数解析 =====
def test_sig_arity_forms():
    assert _sig_arity('int __thiscall(int nVal, int nVal2)') == (2, True)
    assert _sig_arity('void __thiscall()') == (0, True)
    assert _sig_arity('int __thiscall(...)') == (None, True)
    assert _sig_arity('void __cdecl(int, int)') == (None, False)      # 非 thiscall ⇒ 不参与
    assert _sig_arity(None) == (None, False)
    assert _sig_arity('') == (None, False)
    # 形参里有函数指针/逗号 ⇒ 按配平计数
    assert _sig_arity('int __thiscall(int (*)(int, int), char)') == (2, True)


# ===== ② 真实样本必须改写 =====
def test_real_sample_setparam():
    code = ("  CCBControl::SetParam(*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8),"
            " 513, -1);")
    out = _fix_explicit_this_calls(code, _lookup)
    assert out == ("  ((CCBControl *)*(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8))"
                   "->SetParam(513, -1);"), out


def test_real_sample_getcmddata():
    code = "  CCBSystem::GetCmdData(*(CCBSystem **)(*(_DWORD *)&this->m_pObjMsgBuffer[96] + 12), v4);"
    out = _fix_explicit_this_calls(code, _lookup)
    assert '->GetCmdData(v4);' in out and 'CCBSystem::GetCmdData(' not in out, out


def test_real_sample_processkeyboard_with_cast():
    out = _fix_explicit_this_calls("  InputSystem::ProcessKeyboard((InputSystem *)this, 1);", _lookup)
    assert out == "  ((InputSystem *)(InputSystem *)this)->ProcessKeyboard(1);", out


def test_real_sample_updateanim_zero_params():
    """0 形参 + 1 实参 ⇒ 改写为 `->UpdateAnim()`（真实样本的脱壳形态）。"""
    out = _fix_explicit_this_calls("  NPC::UpdateAnim((NPC *)(v3 + 156304));", _lookup)
    assert out.endswith('->UpdateAnim();'), out


def test_multiline_call_is_handled():
    """decomp 里该调用**跨行**（CCBItemWindow_HandleMessage 实测）。"""
    code = ("  CCBControl::SetParam(\n"
            "    *(CCBControl **)(this->m_pfather[17].m_fontcolor.Color + 8),\n"
            "    nMsg,\n"
            "    wParam);\n")
    out = _fix_explicit_this_calls(code, _lookup)
    assert 'CCBControl::SetParam' not in out, out
    assert '->SetParam(nMsg, wParam);' in out, out


def test_arg_with_nested_commas_is_not_split():
    """首实参/其余实参内含括号逗号时，元数判定仍必须正确。"""
    code = "  gbOBBox::IsColOBB(obj, MakeVec(1, 2));"      # 2 实参, 形参 1 ⇒ 应改写
    out = _fix_explicit_this_calls(code, _lookup)
    assert '->IsColOBB(MakeVec(1, 2));' in out, out


# ===== ③ 四条反面样本（**必须不改**）=====
def test_definition_head_is_untouched():
    """函数定义：实参数 == 形参数 ⇒ 闸不成立 ⇒ 不动（这是最重要的反面样本）。"""
    code = "int CCBControl::SetParam(int nVal, int nVal2)\n{\n  return 0;\n}\n"
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_static_call_is_untouched():
    """真 static 调用（`__cdecl`）⇒ 不动。"""
    code = "  CCBControl::StaticThing(1, 2);"
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_aligned_arity_is_untouched():
    """形参/实参已对齐的**普通调用** ⇒ 不动。"""
    code = "  CCBControl::SetParam(1, 2);"
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_unknown_signature_is_untouched():
    code = "  UnknownCls::UnknownM(a, b, c);"
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_variadic_signature_is_untouched():
    code = "  Weird::Variadic(1, 2, 3, 4);"
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_unbalanced_parens_do_not_crash():
    code = "  CCBControl::SetParam(a, b"
    assert _fix_explicit_this_calls(code, _lookup) == code


# ===== ③b 链式守卫：`A->Cls::M(...)` **必须不改**（2026-09-21 实测误伤）=====
def test_member_access_qualified_call_is_untouched():
    """**实测误伤样本**（曾把单文件从 35 条错打成 102 条、总数 2150→2242）。

    原形态 `A->Cls::M(explicit_this, args)`：**对象是前缀 `A`**，首实参不是 this。
    漏这条守卫 ⇒ 被改成 `A->((Cls *)explicit_this)->M(args)` —— 双解引用链 ✗。
    """
    code = ("  (((CCBStage *)this->m_pStage))->CCBStage::DelTask("
            "v4->nTaskIndex, &p_BYTE, &v13);")
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_dot_form_qualified_call_is_untouched():
    code = "  this->m_Stage.CCBStage::DelTask(v4->nTaskIndex, &p_BYTE, &v13);"
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_scope_chain_is_untouched():
    """`A::B::C(` 形态：`::` 链 ⇒ 不把 `B` 当类、`C` 当方法。"""
    code = "  return ns::Inner::Build(a, b, c);"
    assert _fix_explicit_this_calls(code, _lookup) == code


def test_statement_start_still_rewrites():
    """阳性对照：守卫不得把**语句起始**的合法形态也挡掉。"""
    code = "  CCBControl::SetParam(obj, 513, -1);"
    out = _fix_explicit_this_calls(code, _lookup)
    assert out == "  ((CCBControl *)obj)->SetParam(513, -1);", out


def test_after_return_and_equals_still_rewrites():
    for pref in ("return ", "v9 = ", ", "):
        code = "  %sCCBControl::SetParam(obj, 513, -1);" % pref
        out = _fix_explicit_this_calls(code, _lookup)
        assert '->SetParam(513, -1)' in out, (pref, out)


# ===== ④ 纯函数直接契约 =====
def test_pure_function_returns_none_when_arity_mismatch():
    # 形参 1、实参 3 ⇒ 既不是"对齐"也不是"多一个 this" ⇒ 不动
    assert rewrite_explicit_this_call('C', 'M', 'a, b, c', 'void __thiscall(int)') is None
    # 形参 1、实参 1 ⇒ 对齐 ⇒ 不动
    assert rewrite_explicit_this_call('C', 'M', 'a', 'void __thiscall(int)') is None
    # 形参 1、实参 2 ⇒ 恰多一个 this ⇒ 改写
    assert rewrite_explicit_this_call('C', 'M', 'a, b', 'void __thiscall(int)') == \
        '((C *)a)->M(b)'
    # 形参 0、实参 1 ⇒ 改写为空参调用
    assert rewrite_explicit_this_call('C', 'M', 'a', 'void __thiscall()') == '((C *)a)->M()'


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