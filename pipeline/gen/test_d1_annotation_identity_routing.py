"""D1 路由判据测试（2026-11-22）——UIWnd 0x445B20 双定义(C2084 ×12)案的判据固化。

病灶链: decomp 名 `_UIWnd_0` 不被旧名形条件(_scalar_dtor/_sdtor 前缀)命中 →
P-A5 按注解名(~UIWnd)翻名走通用路径 → 与完全形 0x445B40 双定义。
判据律: 名形=拟合, 注解身份=唯一真值——所有"将以 dtor 身份进 TU"的单元
(名形命中 OR 注解 flags dtor OR 注解 ~名)都必须前置仲裁。
"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))
from dtor_intent import should_route_dtor


class TestD1AnnotationIdentityRouting(unittest.TestCase):
    def test_scalar_dtor_name_shape(self):
        self.assertTrue(should_route_dtor('UIWnd::_scalar_dtor', None))

    def test_sdtor_prefix(self):
        self.assertTrue(should_route_dtor('_sdtor_15', None))

    def test_vector_dtor_name_shape(self):
        self.assertTrue(should_route_dtor('Cls::_vector_dtor', None))

    def test_normalized_carrier_name_with_dtor_flags(self):
        # UIWnd 0x445B20 本案: _UIWnd_0 + 注解 flags=[dtor, deleting]
        e = {'name': '~UIWnd', 'flags': ['dtor', 'deleting']}
        self.assertTrue(should_route_dtor('_UIWnd_0', e))

    def test_normalized_carrier_name_with_tilde_name(self):
        # 注解名 ~ 形即身份(即使 flags 通道缺失)
        e = {'name': '~UIWnd'}
        self.assertTrue(should_route_dtor('_UIWnd_0', e))

    def test_carrier_name_no_annotation_goes_generic(self):
        # 无注解身份的名形外单元: 通用路径(拒发计数在 collect 侧另有 D12 族)
        self.assertFalse(should_route_dtor('_UIWnd_0', None))

    def test_plain_method_with_dtor_flags_routes(self):
        # 冒名家族(gbChain1DNode Process/Method 形): 原始名非 dtor 形但注解已定谳
        e = {'name': '~gbChain1DNode', 'flags': ['dtor', 'deleting']}
        self.assertTrue(should_route_dtor('Method', e))

    def test_plain_method_non_dtor_annotation_goes_generic(self):
        e = {'name': 'UpdatePost', 'flags': None}
        self.assertFalse(should_route_dtor('UpdatePost', e))

    def test_tilde_raw_name_with_annotation(self):
        # 完全形(0x445B40 形): 原始名已是 ~UIWnd + 注解 → 走仲裁(body_emit 仲裁不变语义)
        e = {'name': '~UIWnd', 'flags': ['dtor']}
        self.assertTrue(should_route_dtor('~UIWnd', e))

    def test_none_method_safe(self):
        self.assertFalse(should_route_dtor(None, None))


if __name__ == '__main__':
    unittest.main()
