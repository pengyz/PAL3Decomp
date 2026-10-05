# -*- coding: utf-8 -*-
"""批 E 族 1（基类名后缀访问重写）纯函数单测——R15：先测后实现。

规则（33c45090 Q1 + N5 收窄）：
  `<recv>(\.|->)<Base>` 其中 Base 是 recv 静态类型的基类**且后随字符非 `:`** ⇒ 等价重写：
    读值形（int/指针/函数指针/比较）  → `*(DWORD *)&<recv-lvalue>`
    写值形 `x.Base = rhs`            → `*(DWORD *)&<recv-lvalue> = rhs`
    整拷贝形 `*p = x.Base`（T 名义）  → `*p = *(T *)&<recv-lvalue>`
  合法限定形 `x.Base::member`、`x.Base:field`、非基类同名成员（`->Logger`）**一律不动**。
目标：C2273+C2274 全量 106 点位同形（33c45090 逐点实证）。
"""
import os
import sys
import unittest

# 与 test_pipeline 同款路径布设（ast_transform/data/stages 可导入）
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))

from gen.stages.base_suffix_rewrite import rewrite_base_suffix


class TestPair64DoubleCast(unittest.TestCase):
    """批 E 单点（TextureLibDataBase C2520）：(double)__PAIR64__(H,L) 在 MSVC6 报
    unsigned __int64→double 无转换——等价展开 H*2^32+L（双精对 32+32 位无损）。"""

    def test_double_pair64_expansion(self):
        from gen.stages.stage3_cleanup import _expand_pair64_double
        out = _expand_pair64_double(
            'v11 = (__int64)((double)__PAIR64__(HIDWORD(v2), *(_DWORD *)(v22 + 1040)) + v8);')
        self.assertIn('* 4294967296.0', out)
        self.assertNotIn('(double)__PAIR64__', out)

    def test_untouched_other_contexts(self):
        from gen.stages.stage3_cleanup import _expand_pair64_double
        s = 'x = __PAIR64__(a, b) + 1;'
        self.assertEqual(_expand_pair64_double(s), s)

    def test_comment_comma(self):
        # 07fe8e00 A2
        from gen.stages.stage3_cleanup import _expand_pair64_double
        out = _expand_pair64_double('x=(double)__PAIR64__(a /* x,y */, b);')
        self.assertIn('* 4294967296.0', out)
        self.assertIn('/* x,y */', out)

    def test_single_arg_malformed(self):
        # 07fe8e00 A4
        from gen.stages.stage3_cleanup import _expand_pair64_double
        s = 'x=(double)__PAIR64__(a);'
        self.assertEqual(_expand_pair64_double(s), s)

    def test_string_comma_split(self):
        # 07fe8e00 A5
        from gen.stages.stage3_cleanup import _expand_pair64_double
        out = _expand_pair64_double('x=(double)__PAIR64__("a,b", c);')
        self.assertIn('"(a,b)"' if False else '(unsigned int)("a,b")', out)

    def test_string_internal_paren(self):
        # 07fe8e00 A3（串内右括号洞——扫描器边界修）
        from gen.stages.stage3_cleanup import _expand_pair64_double
        out = _expand_pair64_double('x=(double)__PAIR64__(a, "x)");')
        self.assertIn('"x)"', out)
        self.assertEqual(out.count('4294967296.0'), 1)

    def test_line_comment_tail_keeps_newline(self):
        # 07fe8e00 C8（// 尾注释吞 `));` 洞）
        from gen.stages.stage3_cleanup import _expand_pair64_double
        out = _expand_pair64_double('x=(double)__PAIR64__(a, b // c\n);')
        self.assertIn('// c', out)
        self.assertNotIn('// c));', out)

    def test_comment_internal_paren(self):
        # 07fe8e00 C2（注释内 ) 截断洞）
        from gen.stages.stage3_cleanup import _expand_pair64_double
        out = _expand_pair64_double('x=(double)__PAIR64__(a, /* x) */ b);')
        self.assertIn('* 4294967296.0', out)
        self.assertIn('/* x) */', out)

    def test_i64_suffix_not_in_params(self):
        # 07fe8e00 G4/G5（MSVC __int64 后缀）
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1 = 0x10i64, int v4)\n{\n'
                '    x->UpdateAnim(0x10i64, v4);\n}')
        self.assertIn('UpdateAnim(0x10i64, v4)', drop_call_echo_arg(code, {'UpdateAnim': 1}))

    def test_int_cast_literal_not_echo(self):
        # 07fe8e00 G9（(int)<字面量> 铸形非回波）
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1, int v4)\n{\n'
                '    x->UpdateAnim((int)0x10u, v4);\n}')
        self.assertIn('UpdateAnim((int)0x10u, v4)', drop_call_echo_arg(code, {'UpdateAnim': 1}))


class TestUnqualifiedMemberCall(unittest.TestCase):
    """批 E C2065#1（CCBResultWindow:38 `ReleaseTexture((UIScene *)this)`）：Hex-Rays 丢
    类限定的成员调用——裸名+((T*)recv) 首参且 name∈T.methods ⇒ 候选①成员形转写。
    ⚠️ 不得误伤真自由函数（name∉T.methods 时保持原样）。"""

    def test_member_form_rewrite(self):
        from ast_transform import rewrite_unqualified_member_call
        out = rewrite_unqualified_member_call(
            'ReleaseTexture((UIScene *)this);',
            {'UIScene': {'ReleaseTexture', 'Create'}})
        self.assertIn('UIScene::ReleaseTexture', out)
        self.assertIn('(((UIScene *)this))', out)

    def test_free_function_untouched(self):
        from ast_transform import rewrite_unqualified_member_call
        s = 'memset((UIScene *)this, 0, 4);'
        self.assertEqual(rewrite_unqualified_member_call(
            s, {'UIScene': {'ReleaseTexture'}}), s)


class TestDropCallEchoArg(unittest.TestCase):
    """批 E C2660 族：首参 (int) 回波剔除（UpdateAnim retn 4=1 参铁证族）。"""

    def test_echo_dropped_when_slots_match(self):
        from ast_transform import drop_call_echo_arg
        code = ('void Comp_DonateUI::Update(int a1, int v4)\n'
                '{\n'
                '    x->UpdateAnim(a1, v4);\n'
                '}')
        out = drop_call_echo_arg(code, {'UpdateAnim': 1})
        self.assertIn('UpdateAnim(v4)', out)

    def test_no_echo_untouched(self):
        from ast_transform import drop_call_echo_arg
        s = 'x->UpdateAnim(v4);'
        self.assertEqual(drop_call_echo_arg(s, {'UpdateAnim': 1}), s)

    def test_unknown_method_untouched(self):
        from ast_transform import drop_call_echo_arg
        s = 'Foo((int)this, 1, 2);'
        self.assertEqual(drop_call_echo_arg(s, {'UpdateAnim': 1}), s)

    def test_string_literal_comma_not_dropped(self):
        # d0643565 反例 A：字面量内逗号失真切真参
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1, int v4)\n{\n'
                '    x->UpdateAnim(a1, "x,y");\n}')
        self.assertIn('a1, "x,y"', drop_call_echo_arg(code, {'UpdateAnim': 2}))

    def test_control_flow_head_not_in_params(self):
        # d0643565 反例 B：if (v5) 头污染 fn_params
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1, int v4)\n{\n'
                '    if (v5)\n        x->UpdateAnim(v5, v4);\n}')
        self.assertIn('UpdateAnim(v5, v4)', drop_call_echo_arg(code, {'UpdateAnim': 1}))

    def test_default_param_digit_not_dropped(self):
        # d0643565 反例 C：默认参数字入形参集
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1 = 5, int v4)\n{\n'
                '    x->UpdateAnim(5, a1);\n}')
        self.assertIn('UpdateAnim(5, a1)', drop_call_echo_arg(code, {'UpdateAnim': 1}))

    def test_int_cast_echo_fires(self):
        # d0643565：原捕获组致 (int) 铸形分支死代码——返工后应触发
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1, int v4)\n{\n'
                '    x->UpdateAnim((int)a1, v4);\n}')
        self.assertIn('UpdateAnim(v4)', drop_call_echo_arg(code, {'UpdateAnim': 1}))

    def test_block_comment_comma_not_dropped(self):
        # E-1（c1e92014 孔1）：块注释逗号虚增 argc
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1, int v4)\n{\n'
                '    x->UpdateAnim(a1, v4 /* , x */);\n}')
        self.assertIn('UpdateAnim(a1, v4', drop_call_echo_arg(code, {'UpdateAnim': 2}))

    def test_else_if_head_not_in_params(self):
        # E-1（c1e92014 孔2）：else if/宏头污染
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1, int v4)\n{\n'
                '    else if (v5)\n        x->UpdateAnim(v5, v4);\n'
                '    ASSERT(v6);\n    x->UpdateAnim(v6, v4);\n}')
        out = drop_call_echo_arg(code, {'UpdateAnim': 1})
        self.assertIn('UpdateAnim(v5, v4)', out)
        self.assertIn('UpdateAnim(v6, v4)', out)

    def test_hex_literal_not_in_params(self):
        # E-1（c1e92014 孔3）：0x10/100u 字面量入形参集
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1 = 0x10, int v4)\n{\n'
                '    x->UpdateAnim(0x10, v4);\n}')
        self.assertIn('UpdateAnim(0x10, v4)', drop_call_echo_arg(code, {'UpdateAnim': 1}))

    def test_string_literal_content_untouched(self):
        # E-1（c1e92014 孔4）：字符串内调用形被改写
        from ast_transform import drop_call_echo_arg
        code = ('void F::Upd(int a1, int v4)\n{\n'
                '    sprintf(buf, "UpdateAnim(a1, v4)");\n}')
        self.assertIn('"UpdateAnim(a1, v4)"', drop_call_echo_arg(code, {'UpdateAnim': 1}))


class TestBaseSuffixRewrite(unittest.TestCase):
    def test_read_value_int_cast(self):
        out = rewrite_base_suffix('v10 = (int)this->m_Static_20408.UIWnd;',
                                  {'UIWnd', 'ObjectInfoBase'})
        self.assertIn('*(_DWORD *)&this->m_Static_20408', out)
        self.assertNotIn('.UIWnd', out)

    def test_write_value(self):
        out = rewrite_base_suffix('this->info.ObjectInfoBase = 0;',
                                  {'ObjectInfoBase'})
        self.assertIn('*(_DWORD *)&this->info', out)
        self.assertNotIn('.ObjectInfoBase', out)

    def test_whole_subobject_copy(self):
        out = rewrite_base_suffix(
            '*(TaskMgr_SceneObjParam_SceneObj *)p_DWORD = this->TaskMgr_SceneObjParam_SceneObj;',
            {'TaskMgr_SceneObjParam_SceneObj'})
        self.assertIn('*(TaskMgr_SceneObjParam_SceneObj *)&this', out)

    def test_vtable_call_first_dword(self):
        out = rewrite_base_suffix(
            '((int ( *)(UIStatic **, int))this->m_pAttackSequenBack->UIWnd)(&this->m_pAttackSequenBack, v2);',
            {'UIWnd'})
        self.assertIn('*(_DWORD *)&this->m_pAttackSequenBack', out)

    def test_qualified_form_untouched(self):
        # N5：后随 `::` 的合法限定形绝不许动
        s = '(((UIWnd *)v4))->UIWnd::sub_445FA0(1);'
        self.assertEqual(rewrite_base_suffix(s, {'UIWnd'}), s)

    def test_colon_label_untouched(self):
        s = 'x.Base:label'
        self.assertEqual(rewrite_base_suffix(s, {'Base'}), s)

    def test_non_base_member_untouched(self):
        # 同名非基类成员（Logger 等）不许动
        s = 'this->Logger->Write();'
        self.assertEqual(rewrite_base_suffix(s, {'UIWnd'}), s)


if __name__ == '__main__':
    unittest.main()
