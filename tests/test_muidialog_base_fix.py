import json
import unittest


class TestMUIDialogBaseFix(unittest.TestCase):
    def test_base_class_not_ambiguous(self):
        """基类不得含菱形歧义（如同时含 UIDialog 与 UIFrameWnd）。"""
        with open('data/annotations/structs/MUIDialog.json', encoding='utf-8') as file:
            d = json.load(file)
        bc = d.get('base_class') or []
        # UIDialog 与 UIFrameWnd 都派生自 UIWnd ⇒ 同时含会歧义
        self.assertFalse(('UIDialog' in bc) and ('UIFrameWnd' in bc),
                         f'菱形歧义: {bc}')

    def test_archaeologically_supported_bases(self):
        # pal3.h:1134 实证：MUIDialog 只有 1 个基类 UIDialog；
        # +72 是 ptr_Dlg 成员指针（非 MUIDialogMgr 基类）
        with open('data/annotations/structs/MUIDialog.json', encoding='utf-8') as file:
            d = json.load(file)
        self.assertEqual(d.get('base_class'), ['UIDialog'])
        self.assertEqual(d.get('base_size'), 72)

    def test_member_mapping_not_shrunk_or_moved(self):
        with open('data/annotations/structs/MUIDialog.json', encoding='utf-8') as file:
            d = json.load(file)
        with open('data/status/_e2p_member_snapshot_MUIDialog.json', encoding='utf-8') as file:
            snap = json.load(file)
        current = {value.get('name', key): int(key)
                   for key, value in d.get('known_members', {}).items()}
        self.assertEqual(current, snap)


if __name__ == '__main__':
    unittest.main()
