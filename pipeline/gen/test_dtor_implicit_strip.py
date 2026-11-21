"""C8 4d 隐式析构剥离单测（T4-P2：AST 形状守卫固化——逗号/字面量/ERROR/作用域）。"""
import os
import sys
import unittest

_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))

import stage1_structural


def _body_of(code):
    """解析并定位函数体 compound_statement。"""
    tree = stage1_structural._parser.parse(code.encode('utf-8'))

    def find(n):
        if n.type == 'compound_statement':
            return n
        for c in n.children:
            r = find(c)
            if r is not None:
                return r
        return None

    return find(tree.root_node)


def _strip(code):
    body = _body_of(code)
    spans = stage1_structural._dtor_implicit_strip_spans(body, code.encode('utf-8'))
    b = code.encode('utf-8')
    for s, e in sorted(spans, reverse=True):
        b = b[:s] + b[e:]
    return b.decode('utf-8')


def _dtor(body_stmts):
    return 'void X::~X() {\n%s\n}' % body_stmts


class TestDtorImplicitStrip(unittest.TestCase):
    def test_base_dtor_call_stripped(self):
        # 基析构显式调用=隐式再生物 → 整句剥
        out = _strip(_dtor('  this->ClearAttackSequence();\n  this->UIListBox::~UIListBox();'))
        self.assertIn('ClearAttackSequence', out)
        self.assertNotIn('::~UIListBox', out)

    def test_member_render_stripped(self):
        # 成员/转换链渲染形 → 整句剥
        out = _strip(_dtor('  (((UIFrameContainer *)&this->m_probe.m_wndcolor))'
                           '->UIFrameContainer::~UIFrameContainer();'))
        self.assertNotIn('::~UIFrameContainer', out)

    def test_comma_user_call_preserved(self):
        # T4-P2①: 逗号表达式混合(用户调用+析构) → 只剥析构部分, 用户码保留
        out = _strip(_dtor('  Reset(this), this->X::~X();'))
        self.assertIn('Reset(this)', out)
        self.assertNotIn('::~X();', out)

    def test_comma_all_dtor_dropped(self):
        # 逗号表达式全为析构调用 → 整句剥
        out = _strip(_dtor('  this->A::~A(), this->B::~B();'))
        self.assertEqual(out.strip(), 'void X::~X() {\n}')

    def test_string_literal_not_stripped(self):
        # T4-P2②: 字面量含 '::~~' 形 → 不剥(假阳守卫)
        stmt = '  log("::~X danger");'
        code = _dtor(stmt)
        self.assertEqual(_strip(code), code)

    def test_user_call_not_stripped(self):
        # 用户码调用(非析构) → 保留
        stmt = '  this->ClearAttackSequence();'
        code = _dtor(stmt)
        self.assertEqual(_strip(code), code)

    def test_error_node_qqM_stripped(self):
        # T4-P2③: ??_M 族 tree-sitter ERROR 节点 → 文本兜底剥
        code = _dtor('  ??_M@YGXPAXIHP6EX0@Z@Z((void *)v, 8);')
        out = _strip(code)
        self.assertNotIn('??_M', out)

    def test_scope_guard_nondtor(self):
        # 作用域守卫: 非 dtor 函数含析构调用 → 不剥(4d 只对 dtor 定义体)
        code = ('void X::Run() {\n  this->UIListBox::~UIListBox();\n}')
        body = _body_of(code)
        spans = stage1_structural._dtor_implicit_strip_spans(body, code.encode('utf-8'))
        # 纯函数无 ctx 判定——span 逻辑本身返回剥 span, 作用域由调用方(ctx.is_dtor)把守
        self.assertEqual(len(spans), 1)  # 纯函数层面=形状成立; 调用方守卫在 stage1 4d


if __name__ == '__main__':
    unittest.main()
