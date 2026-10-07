"""F2 基类读 offset 形 TDD（TaskMgr +40 型——非零基类·纪律流程）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestBaseOffsetReadForm(unittest.TestCase):
    def test_nonzero_base_read(self):
        # 样张：this->TaskMgr_SceneObjParam_SceneObj（基类 @40）→ *(T*)((char*)this+40)
        from ast_transform import rewrite_base_offset_read
        s = 'x = this->TaskMgr_SceneObjParam_SceneObj;'
        out = rewrite_base_offset_read(s, base_offsets={('CCBRoleState', 'TaskMgr_SceneObjParam_SceneObj'): 40})
        self.assertIn('((char *)this + 40)', out)

    def test_zero_base_untouched(self):
        # +0 基类不动（B1 面）
        from ast_transform import rewrite_base_offset_read
        s = 'x = this->UIWnd;'
        out = rewrite_base_offset_read(s, base_offsets={('A', 'UIWnd'): 0})
        self.assertEqual(out, s)

    def test_semicolon_preserved(self):
        from ast_transform import rewrite_base_offset_read
        s = 'x = this->TaskMgr_SceneObjParam_SceneObj;'
        out = rewrite_base_offset_read(s, base_offsets={('CCBRoleState', 'TaskMgr_SceneObjParam_SceneObj'): 40})
        self.assertIn(';', out)


if __name__ == '__main__':
    unittest.main()
