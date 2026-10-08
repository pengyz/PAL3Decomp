"""A′ 身份决议器 TDD 测试（复核 9 样张——复杂方案先测后实现）。
优先级：structs methods > functions.json > decomp > ida_structs；坏名拒收·同址多源幂等。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestIdentityResolver(unittest.TestCase):
    def test_annotation_wins_same_addr(self):
        # 样张1：0x522030 structs ctor vs functions.json 旧名 vs decomp 旧名
        from ast_transform import resolve_method_identity
        got = resolve_method_identity(
            '0x00522030',
            ann_structs={'0x00522030': {'cls': 'CCBStageRole', 'name': 'CCBStageRole',
                                        'sig': 'CCBStageRole *__thiscall(CCBStageRole *this)'}},
            functions={'0x00522030': {'name': 'CCBStage::CCBStageRole',
                                      'sig': 'CCBStage *__thiscall(CCBStage *this)'}},
            decomp={'name': 'CCBStage::CCBStageRole(void)'},
            ida_methods={})
        self.assertEqual(got[0], 'CCBStageRole')
        self.assertEqual(got[1], 'CCBStageRole')
        self.assertEqual(got[3], 'structs')

    def test_pseudo_name_rejected(self):
        # 样张2：0x508930 _todo_ vs ~CCBStageRole vs _CCBStageRole ——伪语义名不得胜
        from ast_transform import resolve_method_identity
        got = resolve_method_identity(
            '0x00508930',
            ann_structs={'0x00508930': {'cls': 'CCBStage', 'name': '_todo_00508930', 'sig': 'void __thiscall()'}},
            functions={'0x00508930': {'name': 'CCBStage::~CCBStageRole', 'sig': 'void __thiscall()'}},
            decomp={'name': '_CCBStageRole'},
            ida_methods={})
        self.assertEqual(got[1], '_todo_00508930')

    def test_same_name_diff_addr_kept(self):
        # 样张3：同名异址（Destroy 两址）——决议器按址独立（不合并/不互斥）
        from ast_transform import resolve_method_identity
        a = resolve_method_identity('0x004C6290',
            ann_structs={'0x004C6290': {'cls': 'CEffectSystem', 'name': 'Destroy', 'sig': 'void __thiscall()'}},
            functions={}, decomp={}, ida_methods={})
        b = resolve_method_identity('0x004C6360',
            ann_structs={'0x004C6360': {'cls': 'CEffectSystem', 'name': 'Destroy', 'sig': 'void __thiscall()'}},
            functions={}, decomp={}, ida_methods={})
        self.assertEqual(a[1], b[1])           # 同名各自成立
        self.assertEqual(a[3], 'structs')      # 各自独立决议（无跨址合并）

    def test_normalized_equivalence_no_conflict(self):
        # 样张4：scalar deleting destructor ≡ _scalar_dtor ——归一化等价不报冲突
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x004525E0',
            ann_structs={'0x004525E0': {'cls': 'UIListBox', 'name': '_scalar_dtor', 'sig': 'void *__thiscall(void*,char)'}},
            functions={},
            decomp={'name': '`scalar deleting destructor\''},
            ida_methods={})
        self.assertEqual(got[3], 'structs')

    def test_bad_name_rejected(self):
        # 样张5：坏名（类段≠属主）——报出不导入
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x0051B4B0',
            ann_structs={'0x0051B4B0': {'cls': 'CCBItemWindow', 'name': 'CCBItemWindow::CCBFiveNimbusWindow::OnMessage',
                                        'sig': 'void __thiscall()'}},
            functions={}, decomp={}, ida_methods={})
        self.assertEqual(got[3], 'rejected_bad_name')

    def test_cross_class_allowlist(self):
        # 样张6：UIWnd::OnMessage@0x445D10 跨类豁免——不搬迁
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x00445D10',
            ann_structs={'0x00445D10': {'cls': 'UIWnd', 'name': 'OnMessage', 'sig': 'int __thiscall(int,int,int)'}},
            functions={},
            decomp={'name': 'CGameData::OnMessage(int,int,int)'},
            ida_methods={})
        self.assertEqual(got[3], 'allowlist_cross_class')

    def test_underscore_form_structs_wins(self):
        # 样张7：Actor_SetActorAction ≡ Actor::SetActorAction ——structs 形胜
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x00536160',
            ann_structs={'0x00536160': {'cls': 'Actor', 'name': 'SetParam', 'sig': 'void __thiscall(int)'}},
            functions={'0x00536160': {'name': 'Actor_SetParam', 'sig': 'void __thiscall(int)'}},
            decomp={}, ida_methods={})
        self.assertEqual(got[3], 'structs')
        self.assertEqual(got[1], 'SetParam')

    def test_pure_derived_fallback(self):
        # 样张8（返工补断言）：decomp 名沿用——cls/name 提取钉
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x00999999',
            ann_structs={}, functions={},
            decomp={'name': 'Foo::Bar(void)'},
            ida_methods={})
        self.assertEqual(got[3], 'decomp')
        self.assertEqual(got[0], 'Foo')          # cls 提取
        self.assertEqual(got[1], 'Bar')          # name 提取

    def test_ida_last_priority(self):
        # 样张9（返工补断言）：ida 末位——返回值钉
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x00888888',
            ann_structs={}, functions={}, decomp={},
            ida_methods={'0x00888888': {'cls': 'X', 'name': 'Y', 'sig': 'void __thiscall()'}})
        self.assertEqual(got[3], 'ida')
        self.assertEqual(got[0], 'X')
        self.assertEqual(got[1], 'Y')

    def test_vector_dtor_normalization(self):
        # 返工补（复核 bug 实证）：vector deleting destructor → _vector_dtor（非 _scalar）
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x004525E0',
            ann_structs={},
            functions={},
            decomp={'name': '`vector deleting destructor\''},
            ida_methods={})
        self.assertEqual(got[1], '_vector_dtor')

    def test_functions_branch_coverage(self):
        # 返工补（复核：functions 分支 0 覆盖）——Cls::Method 拆分钉
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x00536160',
            ann_structs={},
            functions={'0x00536160': {'name': 'Actor::SetParam', 'sig': 'void __thiscall(int)'}},
            decomp={}, ida_methods={})
        self.assertEqual(got[3], 'functions')
        self.assertEqual(got[0], 'Actor')
        self.assertEqual(got[1], 'SetParam')

    def test_bad_name_2seg_mismatch(self):
        # 返工补（复核：坏名 2 段 mismatch 分支 0 覆盖）
        from ast_transform import resolve_method_identity
        got = resolve_method_identity('0x0051B4B0',
            ann_structs={'0x0051B4B0': {'cls': 'CCBItemWindow',
                                        'name': 'CCBFiveNimbusWindow::OnMessage', 'sig': 'void __thiscall()'}},
            functions={}, decomp={}, ida_methods={})
        self.assertEqual(got[3], 'rejected_bad_name')


if __name__ == '__main__':
    unittest.main()
