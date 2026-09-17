"""`scan_misattribution` 偏移链解析与函数边界取值的单元测试。

## 为什么先写这个
上一轮扫描器把 `&this->m_ListGrid[3].m_disablepic` 当成 `UIStatic`(152B) 的
对象去和 `UIListBox::SetLockSel` 的访问需求(1192B)比，判成"物理不可能"。
**71 个"物理不可能"候选里有 58 个（82%）带偏移链后缀** —— 也就是说这些结论
全部建立在错误的偏移/类型上。修之前必须先有用例把语义钉住。

## 三件事被钉住
1. `parse_decl_type`：`'UIStatic[14]'` / `'SaleUI_SortData[299][5]'` /
   `'UIListBox *[1]'` / `'CEffectSimple *'` 的 (base, dims, ptr) 分解。
2. `resolve_chain`：完整后缀 `[k]` / `.field` / `->field` 的偏移与**终值类型**；
   数组元素大小**必须**由声明维度推（不是 binary_size）；动态下标 ⇒ 类型已知、
   偏移未知（不得静默当成 0）。
3. `min_required_span`：**必须**被 `decomp/*.json` 的 `size_bytes` 约束。
   实测 `UIWnd::GetWidth`(13B) 只访问 `0x8c(%ecx)`=140，旧实现报 244
   （因为盲目扫到 `va+0x400`，跨进了后面 60 多个小函数）。

运行：`python3 -m unittest tools.test_scan_misattribution -v`
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools.scan_misattribution import (  # noqa: E402
    parse_decl_type, resolve_chain, sizeof_type, strip_scalar,
)

# ---- 合成 struct 表（用例自带，不依赖仓库数据） ----------------------------
S = {
    'SaleUI': {'size': 105912, 'members': {
        'm_ListGrid': (98620, 'UIStatic[14]'),
        'm_sort': (18100, 'SaleUI_SortData[299][5]'),
        'm_pRole': (48, 'Actor *'),
        'm_roles': (154116, 's_RoleState[5]'),
        'm_pUtil': (12, 'CCBUtil *'),
        'm_scrollbar': (80, 'UIScrollBar'),
    }, 'methods': {}},
    'UIStatic': {'size': 152, 'members': {
        'm_disablepic': (140, 'int'),
        'm_childs': (36, 'UIWnd *'),
        'm_text': (52, 'char[200]'),
    }, 'methods': {}},
    'SaleUI_SortData': {'size': 4, 'members': {}, 'methods': {}},
    's_RoleState': {'size': 3788, 'members': {
        'm_QiVal': (0, 's_QiVal'),
    }, 'methods': {}},
    's_QiVal': {'size': 64, 'members': {
        'm_rect': (0, 'tagRECT'),
    }, 'methods': {}},
    'tagRECT': {'size': 16, 'members': {
        'left': (0, 'int'), 'bottom': (12, 'int'),
    }, 'methods': {}},
    'CCBUtil': {'size': 400, 'members': {
        'm_pAttackSequen': (16, 'CCBAttackSequen *'),
    }, 'methods': {}},
    'CCBAttackSequen': {'size': 456, 'members': {}, 'methods': {}},
    'UIListBox': {'size': 1192, 'members': {}, 'methods': {}},
    'UIScrollBar': {'size': 352, 'members': {
        'm_texarrayInfo': (260, '_PlugInfo *[10]'),
    }, 'methods': {}},
    '_PlugInfo': {'size': 584, 'members': {}, 'methods': {}},
    'Actor': {'size': 820, 'members': {}, 'methods': {}},
}

prim = {'int': 4, 'char': 1, 'float': 4, 'void': 0, 'UIStatic': 152}


def size_of(t):
    return sizeof_type(S, t)


class TestParseDeclType(unittest.TestCase):
    def test_simple(self):
        self.assertEqual(parse_decl_type('UIStatic'), ('UIStatic', [], False))

    def test_one_dim(self):
        self.assertEqual(parse_decl_type('UIStatic[14]'), ('UIStatic', [14], False))

    def test_two_dims(self):
        self.assertEqual(parse_decl_type('SaleUI_SortData[299][5]'),
                         ('SaleUI_SortData', [299, 5], False))

    def test_pointer(self):
        self.assertEqual(parse_decl_type('CEffectSimple *'), ('CEffectSimple', [], True))

    def test_pointer_array(self):
        self.assertEqual(parse_decl_type('UIListBox *[1]'), ('UIListBox', [1], True))

    def test_whitespace_and_qualifier(self):
        self.assertEqual(parse_decl_type('  unsigned int '), ('unsigned', [], False))

    def test_unparsable_dim_is_None_not_zero(self):
        # 维度非字面量时必须显式 None，不能静默变 0
        b, d, p = parse_decl_type('Foo[n]')
        self.assertEqual((b, p), ('Foo', False))
        self.assertEqual(d, [None])


class TestSizeof(unittest.TestCase):
    def test_scalar(self):
        self.assertEqual(size_of('int'), 4)
        self.assertEqual(size_of('char[200]'), 200)

    def test_array_of_struct(self):
        self.assertEqual(size_of('UIStatic[14]'), 14 * 152)
        self.assertEqual(size_of('SaleUI_SortData[299][5]'), 299 * 5 * 4)

    def test_pointer_is_4(self):
        self.assertEqual(size_of('UIListBox *'), 4)

    def test_unknown_is_None(self):
        self.assertIsNone(size_of('NoSuchClass'))


class TestResolveChain(unittest.TestCase):
    def r(self, mem, suf, amp=False):
        return resolve_chain(S, 'SaleUI', mem, suf, amp)

    def test_plain_member(self):
        # this->m_pRole（无 &，成员是指针）⇒ 对象就是 Actor，偏移不可知
        r = self.r('m_pRole', '')
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'Actor')
        self.assertEqual(r['obj_size'], 820)
        self.assertTrue(r['via_deref'])

    def test_amp_plain_member(self):
        # &this->m_roles ⇒ 对象就是数组本身（5*3788）
        r = self.r('m_roles', '', amp=True)
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 's_RoleState')
        self.assertEqual(r['obj_size'], 5 * 3788)
        self.assertEqual(r['off'], 154116)

    def test_subscript_then_field(self):
        # 核心回归：元素大小必须由声明维度推
        r = self.r('m_ListGrid', '[3].m_disablepic', amp=True)
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'int')
        self.assertEqual(r['obj_size'], 4)
        self.assertEqual(r['off'], 98620 + 3 * 152 + 140)

    def test_two_subscripts(self):
        # 第二维步长 = 5*4 = 20（不是 binary_size）
        r = self.r('m_sort', '[349][3]', amp=True)
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'SaleUI_SortData')
        self.assertEqual(r['obj_size'], 4)
        self.assertEqual(r['off'], 18100 + 349 * 20 + 3 * 4)

    def test_three_level_field_chain(self):
        r = self.r('m_roles', '[5].m_QiVal.m_rect.bottom', amp=True)
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'int')
        self.assertEqual(r['obj_size'], 4)
        self.assertEqual(r['off'], 154116 + 5 * 3788 + 0 + 0 + 12)

    def test_arrow_detaches_from_this(self):
        # this->m_pUtil->m_pAttackSequen：对象在别处，绝对偏移不可知
        r = self.r('m_pUtil', '->m_pAttackSequen')
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'CCBAttackSequen')
        self.assertEqual(r['obj_size'], 456)
        self.assertTrue(r['via_deref'])
        self.assertIsNone(r['off'])

    def test_dynamic_index_type_known_offset_unknown(self):
        r = self.r('m_pRole', '[*v6]')
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'Actor')
        self.assertIsNone(r['off'])

    def test_unknown_field_is_explicit(self):
        r = self.r('m_ListGrid', '[3].m_nonexistent', amp=True)
        self.assertEqual(r['status'], 'unknown_field')
        self.assertIsNone(r['obj_type'])

    def test_index_on_non_array_pointer(self):
        # m_pRole[*v6] 里 m_pRole 是指针；this->m_pRole[3] 也算元素推进
        r = self.r('m_pRole', '[3]')
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'Actor')

    def test_scalar_used_without_amp_is_not_a_size_signal(self):
        # (X*)this->some_int ⇒ 整数里存的是地址，声明类型尺寸无意义
        S2 = dict(S)
        S2['SaleUI'] = {'size': 100, 'members': {'m_flag': (4, 'unsigned int')},
                        'methods': {}}
        r = resolve_chain(S2, 'SaleUI', 'm_flag', '', False)
        self.assertEqual(r['status'], 'scalar_as_ptr')
        self.assertIsNone(r['obj_size'])


class TestRealDataIntegration(unittest.TestCase):
    """对仓库真数据的最小断言（若结构变动则提示需要复核）。"""

    def test_saleui_m_sort_real(self):
        import json
        p = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                         'data', 'annotations', 'structs', 'SaleUI.json')
        if not os.path.exists(p):
            self.skipTest('SaleUI.json 不存在')
        d = json.load(open(p, encoding='utf-8'))
        km = d['known_members']
        self.assertEqual(str(km['18100']['type']), 'SaleUI_SortData[299][5]')

    def test_decomp_has_size_bytes(self):
        import glob
        import json
        root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        fs = glob.glob(os.path.join(root, 'asm', 'pal3', 'decomp', '*.json'))
        if not fs:
            self.skipTest('无 decomp')
        ok = 0
        for f in fs[:200]:
            d = json.load(open(f, encoding='utf-8'))
            v = d.get('size_bytes')
            if (isinstance(v, int) and v > 0) or \
               (isinstance(v, str) and v.isdigit() and int(v) > 0):
                ok += 1
        self.assertGreater(ok, 190, 'size_bytes 不可用 ⇒ 边界约束无从落地')



class TestNormVa(unittest.TestCase):
    """`norm_va` 是查函数尺寸表的键：`.lstrip('0X')` 会吃掉前导 0（真 bug）。"""

    def test_forms_agree(self):
        from tools.scan_misattribution import norm_va
        want = 0x4F3D90
        for s in ('0X004F3D90', '0x004f3d90', '004F3D90', '4F3D90', 0x4F3D90):
            self.assertEqual(norm_va(s), want, s)

    def test_leading_zero_not_eaten(self):
        from tools.scan_misattribution import norm_va
        self.assertEqual(norm_va('0X004F3D90'), 0x4F3D90)   # 不是 0x4F3D90>>0
        self.assertEqual(norm_va('0x00000010'), 0x10)

    def test_garbage_is_None(self):
        from tools.scan_misattribution import norm_va
        self.assertIsNone(norm_va(''))
        self.assertIsNone(norm_va(None))



class TestPointerArrayStride(unittest.TestCase):
    """指针数组的元素步长必须是 4，不是 sizeof(指向类型)。

    真值：`UIListBox::OnMessageEx` 里 `this->m_scrollbar.m_texarrayInfo[4]`
    调用点的 `lea` 是 356；若步长误用 sizeof(_PlugInfo)=584 会算成 2676。
    """

    def test_pointer_array_element_is_4(self):
        r = resolve_chain(S, 'SaleUI', 'm_scrollbar', '.m_texarrayInfo[4]', True)
        self.assertEqual(r['status'], 'ok')
        # off(m_scrollbar)=80, off(m_texarrayInfo)=260, 4 个指针 = 16
        self.assertEqual(r['off'], 80 + 260 + 4 * 4)
        # 终值对象是"被指向的 _PlugInfo"
        self.assertEqual(r['obj_type'], '_PlugInfo')
        self.assertEqual(r['obj_size'], 584)

    def test_struct_array_stride_unchanged(self):
        r = resolve_chain(S, 'SaleUI', 'm_sort', '[349][3]', True)
        self.assertEqual(r['off'], 18100 + 349 * 20 + 12)



class TestMemberKeyRadix(unittest.TestCase):
    """`known_members` 的键**大多是十进制无前缀**（9837/9849，仅 51 个带 `0x`）。

    这条是真踩过的坑：临时脚本对键调 `norm_va()`（按十六进制读），把
    `'64'` 读成 0x64=100，于是得出"UIWnd 成员上界 100 > binary_size 68"的
    **错误断言**。`load_structs` 的规则（`isdigit()` → 十进制）才是对的。
    """

    @classmethod
    def setUpClass(cls):
        from tools.scan_misattribution import load_structs
        cls.S = load_structs()

    def test_decimal_keys_read_as_decimal(self):
        # UIWnd.json 键为十进制：m_rect 在 16（不是 0x16=22）
        m = (self.S.get('UIWnd') or {}).get('members') or {}
        if 'm_rect' not in m:
            self.skipTest('UIWnd.m_rect 不存在')
        self.assertEqual(m['m_rect'][0], 16)
        if 'm_bfocus' in m:
            self.assertEqual(m['m_bfocus'][0], 64)

    def test_member_extent_matches_binary_size(self):
        """UIWnd 成员上界必须等于 binary_size=68（二者自洽，是勘误的依据）。"""
        d = self.S.get('UIWnd')
        if not d or not d.get('size'):
            self.skipTest('无 UIWnd')
        from tools.scan_misattribution import sizeof_type
        hi = max([0] + [off + (sizeof_type(self.S, ty) or 0)
                        for mn, (off, ty) in (d['members'] or {}).items()
                        if mn != '__vftable'])
        self.assertEqual(hi, d['size'])

    def test_hex_prefixed_keys_also_supported(self):
        # 至少存在带 0x 前缀的键（如 Actor.json），且能被解析
        import glob
        import json
        import os
        root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        found = False
        for f in glob.glob(os.path.join(root, 'data', 'annotations', 'structs', '*.json')):
            try:
                j = json.load(open(f, encoding='utf-8'))
            except Exception:
                continue
            if any(str(k).lower().startswith('0x') for k in (j.get('known_members') or {})):
                found = True
                break
        self.assertTrue(found, '已无 0x 前缀键 ⇒ 解析规则需重新确认')



class TestBaseClassMemberLookup(unittest.TestCase):
    """字段定义在**基类**时必须能查到（独立复核抓出的缺陷）。

    `UIStatic` 的 `.m_bcreateok` 实际在基类 `UIWnd` 里；只查
    `S[cls]['members']` 会把这类访问整片误判成 `unknown_field`。
    实测影响：`impossible` 70 -> 87，`unknown_field` 462 -> 253。
    """

    def test_inherited_field_found(self):
        from tools.scan_misattribution import _find_member
        S2 = {
            'UIWnd': {'size': 8, 'members': {'m_bcreateok': (4, 'bool')},
                      'methods': {}, 'bases': []},
            'UIStatic': {'size': 16, 'members': {'m_text': (0, 'char[16]')},
                         'methods': {}, 'bases': ['UIWnd']},
        }
        self.assertEqual(_find_member(S2, 'UIStatic', 'm_bcreateok'), (4, 'bool'))
        self.assertEqual(_find_member(S2, 'UIStatic', 'm_text'), (0, 'char[16]'))
        self.assertIsNone(_find_member(S2, 'UIStatic', 'm_nope'))

    def test_only_primary_base_is_searched(self):
        """次要基类偏移未知 ⇒ 绝不猜（多继承时非主基类不在 0 偏移）。"""
        from tools.scan_misattribution import _find_member
        S2 = {
            'A': {'size': 8, 'members': {'fa': (0, 'int')}, 'methods': {}, 'bases': []},
            'B': {'size': 8, 'members': {'fb': (0, 'int')}, 'methods': {}, 'bases': []},
            'D': {'size': 16, 'members': {}, 'methods': {}, 'bases': ['A', 'B']},
        }
        self.assertEqual(_find_member(S2, 'D', 'fa'), (0, 'int'))
        self.assertIsNone(_find_member(S2, 'D', 'fb'))

    def test_chain_resolves_through_base(self):
        S2 = {
            'UIWnd': {'size': 8, 'members': {'m_bcreateok': (4, 'bool')},
                      'methods': {}, 'bases': []},
            'UIStatic': {'size': 16, 'members': {}, 'methods': {}, 'bases': ['UIWnd']},
            'Panel': {'size': 64, 'members': {'m_w': (16, 'UIStatic')},
                      'methods': {}, 'bases': []},
        }
        r = resolve_chain(S2, 'Panel', 'm_w', '.m_bcreateok', True)
        self.assertEqual(r['status'], 'ok')
        self.assertEqual(r['obj_type'], 'bool')
        self.assertEqual(r['off'], 16 + 4)

    def test_cycle_does_not_hang(self):
        from tools.scan_misattribution import _find_member
        S2 = {
            'X': {'size': 8, 'members': {}, 'methods': {}, 'bases': ['Y']},
            'Y': {'size': 8, 'members': {}, 'methods': {}, 'bases': ['X']},
        }
        self.assertIsNone(_find_member(S2, 'X', 'nope'))


class TestDeclTypePrefixAndNested(unittest.TestCase):
    """真实数据里的 3 类坑：前缀关键字 15 个、嵌套 `::` 41 个、模板 33 个。

    `'AStarPathFinder::NODE *'` 若不处理会取到**外层类** `AStarPathFinder`，
    用错尺寸 —— 比漏判更危险。故嵌套/模板一律返回 base=None。
    """

    def test_const_and_struct_prefix_stripped(self):
        self.assertEqual(parse_decl_type('const struct TypeDescriptor *'),
                         ('TypeDescriptor', [], True))
        self.assertEqual(parse_decl_type('struct _EH3_EXCEPTION_REGISTRATION *'),
                         ('_EH3_EXCEPTION_REGISTRATION', [], True))
        self.assertEqual(parse_decl_type('const char *'), ('char', [], True))

    def test_nested_and_template_are_refused_not_misread(self):
        b, d, p = parse_decl_type('AStarPathFinder::NODE *')
        self.assertIsNone(b, '不许取外层类 AStarPathFinder')
        self.assertTrue(p)
        b2, _, _ = parse_decl_type('std::vector<int,std::allocator<int> >')
        self.assertIsNone(b2)

    def test_pointer_to_unknown_still_is_4_bytes(self):
        # 指针本身恒为 4 字节，即使基名查不到
        self.assertEqual(size_of('std::vector<int,std::allocator<int> > *'), 4)


class TestThisRegAndTrace(unittest.TestCase):
    """`this` 不恒在 `%esi`（`Actor::UpdateFrame` 用 `%ebp`，
    `UILoadingFrm::InitFullScreen` 用 `%edi`）。"""

    LINES = [
        '  4507f0:\t83 ec 10              \tsub    $0x10,%esp',
        '  4507f6:\t8b f9                 \tmov    %ecx,%edi',
        '  450801:\t8b 35 d4 d6 bf 00     \tmov    0xbfd6d4,%esi',
        '  450825:\t8d 77 48              \tlea    0x48(%edi),%esi',
        '  4508b7:\t8b ce                 \tmov    %esi,%ecx',
    ]

    def test_this_regs_detected(self):
        from tools.scan_misattribution import _this_regs
        regs = _this_regs(self.LINES)
        self.assertIn('%ecx', regs)
        self.assertIn('%edi', regs)      # mov %ecx,%edi
        self.assertNotIn('%esi', regs)   # %esi 是覆写过的，不是 this 别名

    def test_trace_reg_finds_lea_offset(self):
        from tools.scan_misattribution import _this_regs, _trace_reg
        regs = _this_regs(self.LINES)
        # 第4行 mov %esi,%ecx 处回溯 %esi -> lea 0x48(%edi) = 72
        self.assertEqual(_trace_reg(self.LINES, 4, '%esi', regs), 0x48)

    def test_trace_reg_stops_at_call(self):
        from tools.scan_misattribution import _trace_reg
        lines = ['  1:\tlea    0x48(%edi),%esi',
                 '  2:\tcall   0x123456',
                 '  3:\tmov    %esi,%ecx']
        self.assertIsNone(_trace_reg(lines, 2, '%esi', {'%ecx', '%edi'}))

    def test_trace_reg_rejects_non_this_base(self):
        from tools.scan_misattribution import _trace_reg
        lines = ['  1:\tlea    0x10(%esp),%esi', '  2:\tmov    %esi,%ecx']
        self.assertIsNone(_trace_reg(lines, 1, '%esi', {'%ecx'}))


if __name__ == '__main__':
    unittest.main()