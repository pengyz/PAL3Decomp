"""批 15（工具批）：实参位丢 & 补全测试（import 生产函数——影子副本教训）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))
from ast_transform import fix_ref_arg_calls


class TestFixRefArgCalls(unittest.TestCase):
    def test_ref_param_addr_added(self):
        # 【N1 修正】引用参**不补 &**（lvalue 直绑）——仅指针参补（批 16 复核 N1 定谳：
        # C2664 `to 'gbVec3D *'` 真相=临时量绑非 const 引用失败（ABI 形报文）——
        # &-补全对 rvalue 非法。现测断言：T& 位不动、T* 位补。
        s = 'm->Rotate(0.5f, v);'
        out = fix_ref_arg_calls(s, {'Rotate': ['float', 'gbVec3D&']},
                               {'v', 'this->m_v'})
        self.assertEqual(out, s)                 # T& 位不动
        out2 = fix_ref_arg_calls(s, {'Rotate': ['float', 'gbVec3D*']}, {'v'})
        self.assertIn('Rotate(0.5f,&v)', out2.replace(' ', ''))  # T* 位补

    def test_value_param_untouched(self):
        s = 'f(a, v);'
        out = fix_ref_arg_calls(s, {'f': ['int', 'gbVec3D']}, {'v'})
        self.assertEqual(out, s)

    def test_already_addr_untouched(self):
        s = 'm->Rotate(0.5f, &v);'
        self.assertEqual(fix_ref_arg_calls(s, {'Rotate': ['float', 'gbVec3D&']}, {'v'}), s)

    def test_non_struct_arg_untouched(self):
        s = 'm->Rotate(0.5f, n);'
        self.assertEqual(fix_ref_arg_calls(s, {'Rotate': ['float', 'gbVec3D&']}, {'v'}), s)

    def test_first_param_ref(self):
        s = 'IsColOBB(box, b2);'
        out = fix_ref_arg_calls(s, {'IsColOBB': ['gbOBBox*', 'gbOBBox*']},
                               {'box', 'b2'})
        self.assertIn('&box', out)
        self.assertIn('&b2', out)

    def test_member_chain_arg(self):
        # N1 修正：指针参（T*）补 &——成员链同
        s = 'm->Rotate(0.5f, this->m_v);'
        out = fix_ref_arg_calls(s, {'Rotate': ['float', 'gbVec3D*']},
                               {'this->m_v'})
        self.assertIn('&this->m_v', out)

    def test_string_content_untouched(self):
        s = 'sprintf(buf, "Rotate(0.5f, v)");'
        self.assertEqual(fix_ref_arg_calls(s, {'Rotate': ['float', 'gbVec3D&']}, {'v'}), s)

    def test_nested_call_no_corruption(self):
        # 复核 B-2（嵌套拼接错位毁码）——纯插入式括号数不变（N1：指针参形）
        s = 'f(g(x), v);'
        out = fix_ref_arg_calls(s, {'f': ['int', 'gbVec3D*'], 'g': ['gbVec3D*']},
                               {'x', 'v'})
        self.assertIn('&v', out)
        self.assertEqual(out.count('('), s.count('('))
        self.assertEqual(out.count(')'), s.count(')'))

    def test_string_in_changed_call_preserved(self):
        # 复核 B-1（重建式回写泄掩码）——字面量保真
        s = 'f(v, "hello");'
        out = fix_ref_arg_calls(s, {'f': ['int', 'char*']}, {'v'})
        self.assertIn('"hello"', out)
        self.assertNotIn('xxxxx', out)

    def test_comment_in_changed_call_preserved(self):
        s = 'f(v, /* keep */ 1);'
        out = fix_ref_arg_calls(s, {'f': ['int', 'int']}, {'v'})
        self.assertIn('/* keep */', out)

    def test_anchor_full_match(self):
        # 复核 M2 突变存活——x/xx 全匹锚判别力
        s1 = 'f(xx);'
        self.assertEqual(fix_ref_arg_calls(s1, {'f': ['gbVec3D*']}, {'x'}), s1)
        s2 = 'f(x);'
        self.assertIn('&x', fix_ref_arg_calls(s2, {'f': ['gbVec3D*']}, {'x'}))

    def test_arity_gate(self):
        # 复核修件3（元数门）
        s = 'f(v, w, u);'
        self.assertEqual(
            fix_ref_arg_calls(s, {'f': ['int', 'gbVec3D&']}, {'v', 'w', 'u'}), s)

    def test_numeric_literal_untouched(self):
        # 复核 val_pat 数字穿透（&0.5f 非法）
        s = 'f(0.5f);'
        self.assertEqual(fix_ref_arg_calls(s, {'f': ['gbVec3D&']}, {'0.5f'}), s)

    def test_builder_four_counterexamples(self):
        # 批 16 构造器四反例防线（复核 Q1）：this/指针/字面量/数组不入集
        from ast_transform import build_ref_arg_context
        members = {'m_Slots', 'this', '0x10', '123'}
        vt = {'this': {'kind': 'value', 'base': 'int'},
              'p': {'kind': 'ptr', 'base': 'gbVec3D', 'stars': 1},
              'arr': {'kind': 'array', 'base': 'int', 'stars': 0},
              'v': {'kind': 'value', 'base': 'gbVec3D'},
              'n': {'kind': 'value', 'base': 'int'}}
        out = build_ref_arg_context(members, vt)
        self.assertIn('m_Slots', out)
        self.assertIn('v', out)              # 结构体型裸 lvar 入集
        for bad in ('this', '0x10', '123', 'p', 'arr', 'n'):
            self.assertNotIn(bad, out, bad)

    def test_builder_end_to_end(self):
        # 构造器→变换端到端（成员名+lvar 名双源；N1：指针参）
        from ast_transform import build_ref_arg_context
        exprs = build_ref_arg_context({'m_v'}, {'v': {'kind': 'value', 'base': 'gbVec3D'}})
        s = 'f(this->m_v, v);'
        out = fix_ref_arg_calls(s, {'f': ['gbVec3D*', 'gbVec3D*']}, exprs)
        self.assertIn('&this->m_v', out)
        self.assertIn('&v', out)


if __name__ == '__main__':
    unittest.main()
