"""C2273 fn-ptr 形扩展 TDD（族级批量——优先③·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestFnptrExtend(unittest.TestCase):
    def test_multi_base_names(self):
        # 族级：多基类名批量（UIWnd/gbRefObject/TextureLibDataBase）
        from ast_transform import fix_fnptr_qualified_call
        s = 'a->gbRefObject(1);\nb->TextureLibDataBase(2);'
        out = fix_fnptr_qualified_call(s, base_names={'UIWnd', 'gbRefObject', 'TextureLibDataBase'})
        self.assertNotIn('->gbRefObject(', out)
        self.assertNotIn('->TextureLibDataBase(', out)

    def test_semicolon_preserved(self):
        from ast_transform import fix_fnptr_qualified_call
        s = 'x->UIWnd(1);'
        out = fix_fnptr_qualified_call(s, base_names={'UIWnd'})
        self.assertIn(';', out)

    def test_non_base_untouched(self):
        from ast_transform import fix_fnptr_qualified_call
        s = 'x->doThing(1);'
        self.assertEqual(fix_fnptr_qualified_call(s, base_names={'UIWnd'}), s)


if __name__ == '__main__':
    unittest.main()
