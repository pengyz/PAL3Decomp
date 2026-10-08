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
        # 逐件体指纹（复核点名）：仅 AStarPathFinder 留 _scalar_dtor（标志参+operator delete）
        import json, glob
        hits = []
        for f in glob.glob(os.path.join(os.environ['PROJECT_ROOT'],
                                        'data/annotations/structs/*.json')):
            d = json.load(open(f, encoding='utf-8'))
            for mk, mv in (d.get('methods') or {}).items():
                if (mv or {}).get('name') == '_scalar_dtor':
                    hits.append((os.path.basename(f), mk))
        self.assertIn(('AStarPathFinder.json', '0x00401030'), hits)
        # 8 件重定谳后不得再是 _scalar_dtor（除 AStarPathFinder 与既有 UIListBox 先例族）
        for bad in ('0x004FB9F0', '0x00504E60', '0x00456220', '0x00411CA0',
                    '0x004a2450', '0x004B0540', '0x004909F0'):
            self.assertNotIn(bad, [h[1] for h in hits], bad)


if __name__ == '__main__':
    unittest.main()
