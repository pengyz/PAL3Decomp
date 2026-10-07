"""member_index 构建 TDD（生成头直读——编译器视图·复核"生成头为准"）。
成员声明解析+继承链传递——UIFrameWnd 型基类成员入链（风险 2 修）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestMemberIndexBuilder(unittest.TestCase):
    def test_member_parse(self):
        # 样张：生成头成员声明解析
        from ast_transform import build_member_index_from_headers
        hdrs = {'UIFrameWnd': 'class UIFrameWnd {\npublic:\n  virtual void Destroy();\n  int m_x; // +0x4\n};\n'}
        mi = build_member_index_from_headers(hdrs)
        self.assertIn('Destroy', mi.get('UIFrameWnd', set()))
        self.assertIn('m_x', mi.get('UIFrameWnd', set()))

    def test_base_chain_members(self):
        # 风险 2 样张：基类链成员传递（CCBControlWindow: UIFrameWnd→Destroy）
        from ast_transform import build_member_index_from_headers
        hdrs = {
            'UIFrameWnd': 'class UIFrameWnd {\npublic:\n  virtual void Destroy();\n};\n',
            'CCBControlWindow': 'class CCBControlWindow : public UIFrameWnd {\npublic:\n  int m_y;\n};\n',
        }
        mi = build_member_index_from_headers(hdrs, cls='CCBControlWindow')
        self.assertIn('Destroy', mi.get('CCBControlWindow', set()))  # 基类成员入链
        self.assertIn('m_y', mi.get('CCBControlWindow', set()))

    def test_empty_headers(self):
        from ast_transform import build_member_index_from_headers
        self.assertEqual(build_member_index_from_headers({}), {})


if __name__ == '__main__':
    unittest.main()
