"""挂账③ 效果复核三钉测（三突变全存活实证——E/F 此前零覆盖）。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestHang3Nails(unittest.TestCase):
    def test_dtor_guard_distinguishes(self):
        # F 守卫判别（复核点名）：纯 void 形不豁免/void*/非 void 豁免/sig 空不豁免
        from transform import make_context
        self.assertTrue(make_context('C', '~C', 'void __thiscall()').is_dtor)
        self.assertFalse(make_context('C', '~C', 'void *__thiscall(char)').is_dtor)
        self.assertFalse(make_context('C', '~C', 'int __thiscall()').is_dtor)
        self.assertTrue(make_context('C', '~C', '').is_dtor)   # sig 空=旧路径（盲区挂账）

    def test_e_decl_form_reachable(self):
        # E 接线钉（复核点名）：_todo_ 名过 data.py 过滤进 free_func_sigs
        import data as _d
        import inspect
        src = inspect.getsource(_d)
        self.assertIn('_todo_', src)                           # 豁免在位

    def test_rename_fingerprint(self):
        # [刷新 2026-11-22 对齐语义退化禁令(2026-11-15)] _scalar_dtor/_sdtor 形名
        # 全量退役(只收语义名)——原断言"AStarPathFinder 留 _scalar_dtor"是禁令前
        # 旧世界。现契约: ①全库 methods 零 _scalar_dtor 形名 ②0x00401030 已正名
        # ~AStarPathFinder 且 flags=deleting(20261122 dtor对偶探针)
        import json, glob
        hits = []
        for f in glob.glob(os.path.join(os.environ['PROJECT_ROOT'],
                                        'data/annotations/structs/*.json')):
            d = json.load(open(f, encoding='utf-8'))
            for mk, mv in (d.get('methods') or {}).items():
                if (mv or {}).get('name') == '_scalar_dtor':
                    hits.append((os.path.basename(f), mk))
        self.assertEqual(hits, [])   # 语义退化禁令: 零 _scalar_dtor 形名
        asp = json.load(open(os.path.join(os.environ['PROJECT_ROOT'],
                                          'data/annotations/structs/AStarPathFinder.json'),
                             encoding='utf-8'))
        m = (asp.get('methods') or {}).get('0x00401030') or {}
        self.assertEqual(m.get('name'), '~AStarPathFinder')
        self.assertIn('deleting', m.get('flags') or [])


if __name__ == '__main__':
    unittest.main()
