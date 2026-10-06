"""批 3（工具批）：结构体值铸标量的 &-补全转写测试（d8ca4fd2 返工：**import 生产函数**——
影子副本教训：本地副本突变杀 0/5）。覆盖返工反例：子成员值铸/前缀碰撞/铸前缀形/掩码纪律。"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))
from ast_transform import fix_struct_value_casts


class TestStructValueCastFix(unittest.TestCase):
    def test_m_slots_addr_fix(self):
        # 【B1 重解释形】(int)x.Base＝首 DWORD 装载——`*(int*)&` 等价（&-插入=lea≠mov 已证伪）
        s = 'v18 = (int)this->m_Slots[20];'
        out = fix_struct_value_casts(s, {'m_Slots'})
        self.assertIn('*(int *)&this->m_Slots[20]', out)

    def test_dword_and_uint_variants(self):
        for cast in ('unsigned long', 'DWORD', 'unsigned int'):
            s = 'x = (%s)a->m_Slots[3];' % cast
            out = fix_struct_value_casts(s, {'m_Slots'})
            self.assertIn('*(%s *)&a->m_Slots[3]' % cast, out, cast)

    def test_plain_member_untouched(self):
        s = 'x = (int)this->m_nCount;'
        self.assertEqual(fix_struct_value_casts(s, {'m_Slots'}), s)

    def test_already_addr_untouched(self):
        s = 'x = (int)&this->m_Slots[2];'
        self.assertEqual(fix_struct_value_casts(s, {'m_Slots'}), s)

    def test_non_scalar_cast_untouched(self):
        s = 'x = (float)this->m_Slots[1];'
        self.assertEqual(fix_struct_value_casts(s, {'m_Slots'}), s)

    def test_submember_value_cast_untouched(self):
        # d8ca4fd2 最强反例：子成员值铸合法——补 & 即语义反转
        s = 'v = (int)this->m_Slots[20].m_nCount;'
        self.assertEqual(fix_struct_value_casts(s, {'m_Slots'}), s)

    def test_prefix_collision_untouched(self):
        # 名字右词界（m_S 前缀撞 m_Slots 教训——d8ca4fd2 实锤）
        s = 'v = (int)this->m_SlotsEx[2];'
        self.assertEqual(fix_struct_value_casts(s, {'m_Slots'}), s)

    def test_cast_prefix_form_untouched(self):
        # 铸前缀形补 & 优先级错（C2102）——不动
        s = 'v = (int)(CCBUIPanel *)v2->m_Slots[3];'
        self.assertEqual(fix_struct_value_casts(s, {'m_Slots'}), s)

    def test_string_content_untouched(self):
        # 掩码纪律（E-1 教训——d8ca4fd2 实锤复发封堵）
        s = 'sprintf(buf, "(int)this->m_Slots[20]");'
        self.assertEqual(fix_struct_value_casts(s, {'m_Slots'}), s)

    def test_no_index_form(self):
        s = 'v = (int)this->m_Slots;'
        out = fix_struct_value_casts(s, {'m_Slots'})
        self.assertIn('*(int *)&this->m_Slots;', out)

    def test_colon_guard(self):
        # 挂账②复核 M2 零守护补测：`::` 限定形（值用法）不重写
        for s in ('v = (int)this->m_X.Base::m;', 'v = (int)a->Base::m;',
                  'v = (int)x.A::B::m;'):
            out = fix_struct_value_casts(s, {'Base', 'A'})
            self.assertEqual(out, s, s)

    def test_base_names_collected(self):
        # 挂账②复核 M3 零守护补测：base_names 入集+N-a 同适用
        from ast_transform import collect_struct_value_members
        self.assertIn('UIWnd', collect_struct_value_members([], {'UIWnd'}))
        # N-a：同名标量实例整名出局（基类名同适用）
        out = collect_struct_value_members([('UIWnd', 'int')], {'UIWnd'})
        self.assertNotIn('UIWnd', out)

    def test_m_bactive_scalar_not_in_set(self):
        # 6e90d6f0 N-f：型注错标量反例（m_bActive 同名任一实例为标量 ⇒ 整名出局）
        from ast_transform import collect_struct_value_members
        pairs = [('m_bActive', 'unsigned char'), ('m_bActive', 'int'),
                 ('m_Slots', 'CCBPanelSlot[30]'),
                 ('m_pScene', 'UIScene'), ('m_pScene', 'CCBStageScene *')]
        out = collect_struct_value_members(pairs)
        self.assertNotIn('m_bActive', out)     # 标量实例 ⇒ 出局
        self.assertNotIn('m_pScene', out)      # N-a 廉价收窄：任一指针实例 ⇒ 出局
        self.assertIn('m_Slots', out)          # 纯结构体数组 ⇒ 入集

    def test_predicate_battery(self):
        from ast_transform import collect_struct_value_members
        pairs = [('a_dword', 'DWORD'), ('a_ptr', 'T *'), ('a_voidp', 'PVOID'),
                 ('a_int_arr', 'int[4]'), ('a_struct', 'X'),
                 ('a_struct_arr', 'X[8]'), ('a_union', {'union': []})]
        out = collect_struct_value_members(pairs)
        self.assertIn('a_struct', out)
        self.assertIn('a_struct_arr', out)
        self.assertIn('a_union', out)
        for bad in ('a_dword', 'a_ptr', 'a_voidp', 'a_int_arr'):
            self.assertNotIn(bad, out, bad)


if __name__ == '__main__':
    unittest.main()
