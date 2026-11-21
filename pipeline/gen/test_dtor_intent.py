"""[D10 dtor_intent 活性单测 2026-11-21] T 矩阵核心(plan_dtor_intent_reform §四)。

T1 命名 vintage 矩阵 | T2 双形单源仲裁(Role/CCBResultWindow) | T3 no_complete_form ABI
T5 suppressed 三方一致 | T9 跨类名规范化+[]陷阱语义 | T14 sig-vs-deleting 交叉核
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(
    os.path.dirname(os.path.abspath(__file__)))))
from dtor_intent import resolve_dtor_intent

CLS = 'CameraCtrl'


def _run(entry, siblings=(), unit_present=True, vintage='named',
         flags_channel=None, scalar=False, s4=None, vtable_slot_addrs=()):
    return resolve_dtor_intent(
        cls=CLS, entry_addr=entry.get('addr', '0x00000000'), entry=entry,
        siblings=list(siblings), unit_present=unit_present, unit_vintage=vintage,
        flags_channel=flags_channel, header_facts_scalar=scalar, s4_symbols=s4,
        vtable_slot_addrs=vtable_slot_addrs)


class TestDtorIntentT1(unittest.TestCase):
    """T1: 同一删除式单元 × 命名 vintage × 有无注解。"""

    def test_backtick_vintage_with_annotation(self):
        it = _run({'addr': '0x1', 'name': '~CameraCtrl', 'flags': ['dtor', 'deleting']},
                  vintage='backtick', flags_channel=['dtor', 'deleting'])
        self.assertTrue(it.body_emit)
        self.assertTrue(it.n18_strip)
        self.assertEqual(it.role, 'deleting_source')
        self.assertEqual(it.name, '~CameraCtrl')

    def test_cross_class_name_normalized(self):
        # T9a: 槽链律名 ~GameObject → 发射域 ~CameraCtrl(S0①律)
        it = _run({'addr': '0x1', 'name': '~GameObject', 'flags': ['dtor', 'deleting']},
                  flags_channel=['dtor', 'deleting'])
        self.assertEqual(it.name, '~CameraCtrl')
        self.assertIn('规范化', it.reason)

    def test_non_dtor_shape_name_normalized(self):
        # T9b: _nearby_41cbc0 形名 + flags dtor → 规范化
        it = _run({'addr': '0x1', 'name': '_nearby_41cbc0', 'flags': ['dtor']},
                  flags_channel=['dtor'])
        self.assertEqual(it.name, '~CameraCtrl')

    def test_no_annotation_no_flags_suspect(self):
        # 无 ~ 名且 flags 缺 → data_suspect(sig-vs-flags 失配族)
        it = _run({'addr': '0x1', 'name': '_nearby_41cbc0', 'flags': []},
                  flags_channel=[])
        self.assertTrue(it.data_suspect)


class TestDtorIntentT2(unittest.TestCase):
    """T2: 双形单源仲裁(唯一源律)。"""

    def test_complete_wins_owner(self):
        comp = {'addr': '0x00411ca0', 'name': '~Role', 'flags': ['dtor']}
        dele = {'addr': '0x00411bd0', 'name': '~Role', 'flags': ['dtor', 'deleting']}
        it = _run(dele, siblings=[
            {'addr': '0x00411ca0', 'entry': comp, 'unit_present': True}],
            flags_channel=['dtor', 'deleting'])
        self.assertFalse(it.body_emit)
        self.assertEqual(it.definition_owner, '0x00411ca0')
        self.assertTrue(it.decl_emit)

    def test_deleting_source_when_no_complete(self):
        dele = {'addr': '0x0043d860', 'name': '~UI3DCtrl', 'flags': ['dtor', 'deleting']}
        it = _run(dele, flags_channel=['dtor', 'deleting'])
        self.assertTrue(it.body_emit)
        self.assertTrue(it.n18_strip)
        self.assertEqual(it.definition_owner, '0x0043d860')

    def test_unit_absent_no_body(self):
        dele = {'addr': '0x1', 'name': '~X', 'flags': ['dtor', 'deleting']}
        it = _run(dele, unit_present=False, flags_channel=['dtor', 'deleting'])
        self.assertFalse(it.body_emit)
        self.assertTrue(it.decl_emit)


class TestDtorIntentT3(unittest.TestCase):
    """T3: no_complete_form ABI(CEffObj 0x4c0620 形)。"""

    def test_decl_only_deleting_keeps_decl(self):
        # 有槽证据 → virtual(合成载体)
        it = _run({'addr': '0x4c0620', 'name': '~CEffObj',
                   'flags': ['dtor', 'deleting'], 'declaration_only': True},
                  flags_channel=['dtor', 'deleting'],
                  vtable_slot_addrs={0x004C0620})
        self.assertFalse(it.body_emit)
        self.assertTrue(it.decl_emit)
        self.assertTrue(it.decl_virtual)

    def test_no_slot_evidence_not_virtual(self):
        # [virtual 证据律] flags 不可证虚——无槽证据 → decl_virtual=False
        # (F5 31 类出处: 非槽 dtor 误标虚=vtable 布局灾难)
        it = _run({'addr': '0x1', 'name': '~X', 'flags': ['dtor', 'deleting']},
                  flags_channel=['dtor', 'deleting'])
        self.assertTrue(it.decl_emit)
        self.assertFalse(it.decl_virtual)


class TestDtorIntentT5(unittest.TestCase):
    """T5: suppressed 语义(type='skip')。"""

    def test_suppressed_no_decl_no_body(self):
        it = _run({'addr': '0x1', 'name': '~X', 'flags': ['dtor', 'deleting'],
                   'type': 'skip'}, flags_channel=['dtor', 'deleting'])
        self.assertFalse(it.body_emit)
        self.assertFalse(it.decl_emit)
        self.assertEqual(it.role, 'suppressed')


class TestDtorIntentT14(unittest.TestCase):
    """T14: sig-vs-deleting 交叉核(ParticleEffect 0x4bc790 形)。"""

    def test_deleting_with_zero_param_sig_suspect(self):
        it = _run({'addr': '0x4bc790', 'name': '~ParticleEffect',
                   'flags': ['dtor', 'deleting'],
                   'sig_model': {'return': 'void', 'cc': 'thiscall',
                                 'params': [], 'pending': False}},
                  flags_channel=['dtor', 'deleting'])
        self.assertTrue(it.data_suspect)

    def test_pending_sig_not_suspect(self):
        it = _run({'addr': '0x1', 'name': '~X', 'flags': ['dtor', 'deleting'],
                   'sig_model': {'pending': True}}, flags_channel=['dtor', 'deleting'])
        self.assertFalse(it.data_suspect)


if __name__ == '__main__':
    unittest.main()
