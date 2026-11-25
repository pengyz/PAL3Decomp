"""挂账①B 修 R15 测（效果复核点名 4 条——此前被改路径零覆盖/三突变各杀 0 实证）。
覆盖：双载选位/限定键匹配/类型键承重（C2100 复燃面）/PAU 形不动。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
sys.path.insert(0, os.path.join(_GEN, 'stages'))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))


class TestRefParamTableB(unittest.TestCase):
    def test_arity_dual_overload_positions(self):
        # ①双载选位：2 元 ref@1 / 1 元 ref@0（gbMatrixStack::Rotate）
        from stage5_fixup import _GB_REF_PARAM_FUNCS as F
        self.assertEqual(F['gbMatrixStack::Rotate'][2], {1})
        self.assertEqual(F['gbMatrixStack::Rotate'][1], {0})

    def test_qualified_key_matching(self):
        # ②限定键命中（Cls::fn 形）——71 站点实效面
        from stage5_fixup import _fix_ref_params
        code = 'obj->gbMatrixStack::Rotate(v1, v2);'
        out = _fix_ref_params(code, None)
        self.assertNotEqual(out, code)             # 限定形被处理（ref@1 剥 & 等）
        code2 = 'obj->Rotate(v1, v2);'
        self.assertEqual(_fix_ref_params(code2, None), code2)  # 裸形出表后不动

    def test_type_key_followup_carries(self):
        # ③类型键随迁承重（C2100 +24 复燃面——`*stru_` 需 ref_type 触发 Case2b 地址形）
        # [刷新 2026-11-22 对齐 L-VAR 修复(2026-11-11)] 表键=**裸名**('Rotate',1)
        #   ——限定名直接 get 落空曾是 3199 名失效族病灶；消费侧 ref_params.py:350
        #   带 func_name.split('::')[-1] 裸名回退。原断言"限定名在表/裸名不在表"
        #   是修复前旧世界。
        from ref_params import _GB_REF_PARAM_TYPES as T
        # [Phase1 单源化 2026-11-25 重基线] 限定键直查替代裸名回退(多载异型名裸键禁入=复核旗舰案)
        self.assertIn(('gbMatrixStack::Rotate', 1), T)
        self.assertEqual(T[('gbMatrixStack::Rotate', 1)], 'struct gbVec3D')
        self.assertEqual(T[('gbMatrixStack::Rotate', 0)], 'struct gbQuaternion')
        # [Phase1 2026-11-25 重基线] 裸 IsColOBB 反证据禁入(gbOBBox::IsColOBB(gbOBBox *)
        # = 指针形同名列)→限定键承接; 8 条无背书死条目同步清
        self.assertIn(('gbRay::IsColOBB', 0), T)
        self.assertIn(('gbPlane::IsColOBB', 0), T)

    def test_pau_pointer_form_untouched(self):
        # ④PAU 指针形不动（gbMatrix4::Rotate(gbVec3D const*,gbVec3D*) 出表）
        from stage5_fixup import _fix_ref_params
        code = 'x->gbMatrix4::Rotate(&a, &b);'
        self.assertEqual(_fix_ref_params(code, None), code)

    def test_getaabox_cross_class_form_split(self):
        # ⑤GetAABBox 跨类形参形态相反（B 修补条 2026-10-14）：
        #   gbengine.def mangled 名 A 级：gbOBBox=AAU 引用形留表；
        #   gbVisNode/gbGeomNode=PAU 指针形出表（裸键曾误解引用实参 ⇒ ScreenEffectMgr C2664）。
        from stage5_fixup import _GB_REF_PARAM_FUNCS as F, _fix_ref_params
        self.assertNotIn('GetAABBox', F)              # 裸键出表（指针形不再被解引用）
        self.assertIn('gbOBBox::GetAABBox', F)        # 引用形限定键留表
        # PAU 形（gbVisNode）不动：实参 p0 保持指针形
        code_ptr = 'x->gbVisNode::GetAABBox(p0);'
        self.assertEqual(_fix_ref_params(code_ptr, None), code_ptr)
        # AAU 形（gbOBBox）保留既有解引用形（生产 4 站点形）
        code_ref = 'x->gbOBBox::GetAABBox(*pBox);'
        self.assertEqual(_fix_ref_params(code_ref, None), code_ref)


if __name__ == '__main__':
    unittest.main()
