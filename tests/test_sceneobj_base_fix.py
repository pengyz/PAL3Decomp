import json
import unittest


class TestSceneObjBaseFix(unittest.TestCase):
    def test_base_class_is_uiwnd(self):
        with open('data/annotations/structs/SceneObj.json', encoding='utf-8') as f:
            d = json.load(f)
        self.assertEqual(d.get('base_class'), ['UIWnd'],
                         'SceneObj 的 base_class 应为 [UIWnd]（objdump 实证）')

    def test_base_size_is_68(self):
        with open('data/annotations/structs/SceneObj.json', encoding='utf-8') as f:
            d = json.load(f)
        self.assertEqual(d.get('base_size'), 68,
                         'base_size 应为 68（UIWnd 的尺寸）')

    def test_member_count_not_shrunk(self):
        with open('data/annotations/structs/SceneObj.json', encoding='utf-8') as f:
            d = json.load(f)
        with open('data/status/_e2p_member_snapshot_SceneObj.json', encoding='utf-8') as f:
            snap = json.load(f)
        actual = {member['name']: int(offset)
                  for offset, member in d.get('known_members', {}).items()}
        self.assertEqual(actual, snap, '成员清单或偏移发生丢失/漂移')


if __name__ == '__main__':
    unittest.main()
