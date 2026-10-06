"""A 簇 lvar 归并 TDD 测试（复核修订案·同槽同名归并纯函数）。
归并键=(func_ea,location)·全等去重·逐使用点定型（A 级证据）·冲突留原。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestLvarDedupe(unittest.TestCase):
    def test_identical_dedup(self):
        # 样张：同 (name,type,location) 全等去重——纯等价（返工：tuple 返回）
        from ast_transform import dedupe_identical_lvars
        decls = [
            {'name': 'pNewBuffer', 'type': 'void*', 'loc': '[ebp-0x28]'},
            {'name': 'pNewBuffer', 'type': 'void*', 'loc': '[ebp-0x28]'},
            {'name': 'pNewBuffer', 'type': 'int', 'loc': '[ebp-0x28]'},
        ]
        out, conflicts = dedupe_identical_lvars(decls)
        self.assertEqual(len(out), 1)                     # 同名单留（R-A：C2371 防）
        self.assertEqual(len(conflicts), 1)               # 异型冲突报出

    def test_same_name_single_decl_invariant(self):
        # R-A 出口不变量：每 (func,loc,name) 至多一条声明（pNewBuffer 语料样张形）
        from ast_transform import dedupe_identical_lvars
        decls = [
            {'name': 'pNewBuffer', 'type': 'int', 'loc': '[ebp-0x28]', 'func': 0x408FD0},
            {'name': 'pNewBuffer', 'type': 'void*', 'loc': '[ebp-0x28]', 'func': 0x408FD0},
            {'name': 'pNewBuffer', 'type': 'gbVec3D*', 'loc': '[ebp-0x28]', 'func': 0x408FD0},
        ]
        out, conflicts = dedupe_identical_lvars(decls)
        names = [d['name'] for d in out]
        self.assertEqual(len(names), len(set(names)))     # 无同名重复

    def test_different_location_kept(self):
        from ast_transform import dedupe_identical_lvars
        decls = [
            {'name': 'pNewBuffer', 'type': 'void*', 'loc': '[ebp-0x28]'},
            {'name': 'pNewBuffer', 'type': 'void*', 'loc': '[ebp-0x2c]'},
        ]
        out, _ = dedupe_identical_lvars(decls)
        self.assertEqual(len(out), 2)

    def test_name_component_guard(self):
        # R-C：name 分量看门（删 name 突变杀点）——同 func 同 loc 同 type 异名留 2
        from ast_transform import dedupe_identical_lvars
        decls = [
            {'name': 'x', 'type': 'int', 'loc': '[ebp-0x4]', 'func': 0x401000},
            {'name': 'y', 'type': 'int', 'loc': '[ebp-0x4]', 'func': 0x401000},
        ]
        out, _ = dedupe_identical_lvars(decls)
        self.assertEqual(len(out), 2)

    def test_empty_name_filtered(self):
        from ast_transform import dedupe_identical_lvars
        decls = [{'name': '', 'type': 'int', 'loc': '[ebp-0x4]'}]
        out, _ = dedupe_identical_lvars(decls)
        self.assertEqual(len(out), 0)

    def test_dict_type_no_crash(self):
        # R-B 健壮性：dict 形 type（inline union 合法形）不崩
        from ast_transform import dedupe_identical_lvars
        decls = [{'name': 'u', 'type': {'union': []}, 'loc': '[ebp-0x8]'},
                 {'name': 'u', 'type': {'union': []}, 'loc': '[ebp-0x8]'}]
        out, _ = dedupe_identical_lvars(decls)
        self.assertEqual(len(out), 1)

    def test_conflict_reported(self):
        from ast_transform import adjudicate_lvar_type
        v = adjudicate_lvar_type(
            '[ebp-0x28]',
            uses_evidence=[{'kind': 'int_arith'}, {'kind': 'ptr_scale', 'scale': 12}])
        self.assertEqual(v, 'conflict')

    def test_uniform_evidence_consistent(self):
        from ast_transform import adjudicate_lvar_type
        v = adjudicate_lvar_type('[ebp-0x2c]',
            uses_evidence=[{'kind': 'ptr_scale', 'scale': 12}] * 3)
        self.assertEqual(v, 'consistent')       # R-B 返回域封闭

    def test_no_evidence_keeps_original(self):
        from ast_transform import adjudicate_lvar_type
        self.assertEqual(adjudicate_lvar_type('[ebp-0x30]', uses_evidence=[]), 'keep_original')
        self.assertEqual(adjudicate_lvar_type('[ebp-0x30]', uses_evidence=[{'kind': 'ptr_scale'}]), 'keep_original')  # 缺 scale
        self.assertEqual(adjudicate_lvar_type('[ebp-0x30]', uses_evidence=[{'kind': 'ptr_scale', 'scale': '12'}]), 'keep_original')  # 字符串 scale 不崩
        self.assertEqual(adjudicate_lvar_type('[ebp-0x30]', uses_evidence=[{}]), 'keep_original')

    def test_cross_function_isolation(self):
        from ast_transform import dedupe_identical_lvars
        decls = [
            {'name': 'x', 'type': 'int', 'loc': '[ebp-0x4]', 'func': 0x401000},
            {'name': 'x', 'type': 'int', 'loc': '[ebp-0x4]', 'func': 0x402000},
        ]
        out, _ = dedupe_identical_lvars(decls)
        self.assertEqual(len(out), 2)


if __name__ == '__main__':
    unittest.main()
