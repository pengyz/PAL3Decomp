"""O5 特形符号解码+身份清单 join 测试（2026-11-22）。

对抗复核+架构审计双报告定谳的接线验收：
- 解码 T 矩阵：??_G/??1/??0/??_E 有类名段 → (kind, cls)；??_H/??3 全局特形无类名 → None；
  普通 ? 符号 → None；??_7 vftable → None（非函数身份）。
- join：真值表 (ann_class, ann_kind) 命中产候选；data_suspect 条目过滤（双保险）；
  多行同键 → 候选 list（R6 多址，字节择优）；size 仅 int>0 才带。
"""
import os
import sys
import unittest
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import compare_pal3 as cp


class TestDecodeSpecialSym(unittest.TestCase):
    def test_deleting_dtor(self):
        self.assertEqual(cp._decode_special_sym('??_GUIWnd@@UAEPAXI@Z'),
                         ('deleting_dtor', 'UIWnd'))

    def test_complete_dtor(self):
        self.assertEqual(cp._decode_special_sym('??1UIWnd@@QAE@XZ'),
                         ('complete_dtor', 'UIWnd'))

    def test_ctor(self):
        self.assertEqual(cp._decode_special_sym('??0CCBStage@@QAE@XZ'),
                         ('ctor', 'CCBStage'))

    def test_vector_dtor(self):
        self.assertEqual(cp._decode_special_sym('??_EFoo@@QAEPAXI@Z'),
                         ('vector_dtor', 'Foo'))

    def test_nested_class_chain(self):
        # 嵌套类链 AStarPathFinder::NODE —— cls 段取到 @@ 前的第一段即可配
        # (清单 ann_class 为文件级类名, 嵌套类条目 kind=method 不在特形射程)
        r = cp._decode_special_sym('??_GNODE@AStarPathFinder@@UAEPAXI@Z')
        self.assertEqual(r, ('deleting_dtor', 'NODE'))

    def test_global_specials_no_class(self):
        # ??_H(new失败)/??3(operator delete) 无类名段 → None
        self.assertIsNone(cp._decode_special_sym('??_H@YAPAXI@Z'))
        self.assertIsNone(cp._decode_special_sym('??3@YAXPAXI@Z'))

    def test_vftable_not_function(self):
        self.assertIsNone(cp._decode_special_sym('??_7UIWnd@@6B@'))

    def test_regular_symbol_none(self):
        self.assertIsNone(cp._decode_special_sym('?Create@UIWnd@@QAEHH@Z'))
        self.assertIsNone(cp._decode_special_sym('_some_c_sym'))


class TestIdentityJoin(unittest.TestCase):
    def _prep(self, rows):
        cp._FUNCTION_IDENTITY = rows
        cp._FUNCTION_IDENTITY_BY_ID = {}
        for r in rows:
            cp._FUNCTION_IDENTITY_BY_ID.setdefault(
                (r.get('ann_class'), r.get('ann_kind')), []).append(r)

    def test_hit_with_size(self):
        self._prep([{'va': '0x00445b20', 'size': 57, 'ann_class': 'UIWnd',
                     'ann_kind': 'deleting_dtor', 'data_suspect': ''}])
        cand = cp._identity_candidates('deleting_dtor', 'UIWnd')
        self.assertEqual(len(cand), 1)
        self.assertEqual(cand[0]['va'], 0x445b20)
        self.assertEqual(cand[0]['size'], 57)
        self.assertIn('deleting destructor', cand[0]['name'])

    def test_null_size_omitted(self):
        self._prep([{'va': '0x0043be10', 'size': None, 'ann_class': 'UIScene',
                     'ann_kind': 'deleting_dtor', 'data_suspect': ''}])
        cand = cp._identity_candidates('deleting_dtor', 'UIScene')
        self.assertEqual(len(cand), 1)
        self.assertNotIn('size', cand[0])   # 缺 size → compare_units 用编译长回退

    def test_suspect_filtered(self):
        self._prep([{'va': '0x004bef50', 'size': 10, 'ann_class': 'UIRoleDialog',
                     'ann_kind': 'method', 'data_suspect': '外类条目'}])
        self.assertEqual(cp._identity_candidates('method', 'UIRoleDialog'), [])

    def test_multi_row_same_key_candidates(self):
        # CEffQuake 双条目(标准形 0x4d32e0 + adjustor 0x4d3860) → 候选 list 择优
        self._prep([
            {'va': '0x004d32e0', 'size': 30, 'ann_class': 'CEffQuake',
             'ann_kind': 'deleting_dtor', 'data_suspect': ''},
            {'va': '0x004d3860', 'size': 13, 'ann_class': 'CEffQuake',
             'ann_kind': 'deleting_dtor', 'data_suspect': ''}])
        cand = cp._identity_candidates('deleting_dtor', 'CEffQuake')
        self.assertEqual({c['va'] for c in cand}, {0x4d32e0, 0x4d3860})

    def test_match_symbols_union_dedup(self):
        self._prep([{'va': 4498720, 'size': 57, 'ann_class': 'UIWnd',
                     'ann_class2': None, 'ann_kind': 'deleting_dtor',
                     'data_suspect': ''}])
        mm = {'??_GUIWnd@@UAEPAXI@Z': [{'name': 'UIWnd::~UIWnd', 'va': 4498720,
                                        'size': 57}]}
        got = cp.match_symbols(['??_GUIWnd@@UAEPAXI@Z'], mm, {})
        entries = got['??_GUIWnd@@UAEPAXI@Z']
        vas = [e['va'] for e in entries]
        self.assertEqual(len(vas), len(set(vas)))   # 同址去重不双计
        self.assertGreaterEqual(len(entries), 1)

    def test_match_symbols_miss_identity_hit(self):
        self._prep([{'va': 4260560, 'size': 40, 'ann_class': 'Role',
                     'ann_kind': 'deleting_dtor', 'data_suspect': ''}])
        got = cp.match_symbols(['??_GRole@@UAEPAXI@Z'], {}, {})
        self.assertEqual(got['??_GRole@@UAEPAXI@Z'][0]['va'], 4260560)


if __name__ == '__main__':
    unittest.main()
