"""[N20 dtor 载体门活性单测 2026-11-21] N19 协议——门禁写了必须证明会响。

纯函数核 _n20_scan(cls_forms, s4_rows) 合成态断言:
  T1 N20a: 压制删除式条目 且 地址==??_G L1符号va → 必须报错
  T2 N20a精化: 多删除式兄弟(压制的是非VA兄弟) → 不报(VA级判据, Role案)
  T3 N20b: 类内全压制 → WARN 类级载体全空
  T4 N20c: 删除式唯一形态未压制 → WARN 泛化跳过预警
  T5 阴性: 未压制条目 + L1 符号 → 零报错(健康态)
  T6 阳性对照: 压制完全形 且 ??1 符号 L1 → 必须报错
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from check_annotations import _n20_scan


class TestN20DtorCarrierGate(unittest.TestCase):
    ROWS = {
        '??_GRole@@UAEPAXI@Z': {'status': 'match_L1', 'va': '0x00411BD0'},
        '??1Role@@UAE@XZ': {'status': 'partial', 'va': '0x00411CA0'},
        '??1UIProgressBar@@UAE@XZ': {'status': 'match_L1', 'va': '0x00439150'},
        '??_GCameraCtrl@@UAEPAXI@Z': {'status': 'match_L1', 'va': '0x0045C2A0'},
    }

    def test_t1_suppress_va_hit_fires(self):
        # [O5 重校准 2026-11-22] del 压制+L1=advisory(配对与压制正——manifest
        # 数据层+编译器合成均不受语料压制影响, 33 L1 deleting 压制态实证);
        # comp 压制+L1=HARD(定义源切断=合成消失, T6 保留)。
        errs, warns = _n20_scan(
            {'Role': {'del': [{'addr': '0x00411bd0', 'suppressed': True}],
                      'comp': []}}, self.ROWS)
        self.assertFalse([e for e in errs if 'N20a' in e], errs)
        self.assertTrue(any('N20a' in w and 'Role' in w for w in warns), warns)

    def test_t1b_comp_suppress_va_hit_hard(self):
        errs, _ = _n20_scan(
            {'UIProgressBar': {'del': [],
                               'comp': [{'addr': '0x00439150', 'suppressed': True}]}},
            self.ROWS)
        self.assertTrue(any('N20a' in e and 'UIProgressBar' in e for e in errs), errs)

    def test_t2_sibling_suppress_no_fire(self):
        # 压制的是 0x411bb0(VA兄弟), 载体 0x411bd0 未压制 → 不报
        errs, _ = _n20_scan(
            {'Role': {'del': [{'addr': '0x00411bb0', 'suppressed': True},
                              {'addr': '0x00411bd0', 'suppressed': False}],
                      'comp': []}}, self.ROWS)
        self.assertFalse([e for e in errs if 'N20a' in e], errs)

    def test_t3_all_suppressed_warns(self):
        _, warns = _n20_scan(
            {'X': {'del': [{'addr': '0x1', 'suppressed': True}],
                   'comp': [{'addr': '0x2', 'suppressed': True}]}}, self.ROWS)
        self.assertTrue(any('N20b' in w and 'X' in w for w in warns), warns)

    def test_t4_deleting_only_unsuppressed_warns(self):
        _, warns = _n20_scan(
            {'UIProgressBar': {'del': [{'addr': '0x439110', 'suppressed': False}],
                               'comp': []}}, self.ROWS)
        self.assertTrue(any('N20c' in w and 'UIProgressBar' in w for w in warns),
                        warns)

    def test_t5_healthy_silent(self):
        errs, _ = _n20_scan(
            {'Role': {'del': [{'addr': '0x00411bd0', 'suppressed': False}],
                      'comp': []}}, self.ROWS)
        self.assertFalse(errs)

    def test_t6_complete_form_hit_fires(self):
        errs, _ = _n20_scan(
            {'UIProgressBar': {'del': [],
                               'comp': [{'addr': '0x00439150',
                                         'suppressed': True}]}}, self.ROWS)
        self.assertTrue(any('N20a' in e and 'UIProgressBar' in e for e in errs),
                        errs)

    def test_t7_non_l1_symbol_no_fire(self):
        # 符号仅 partial(非L1) → 压制不触发 N20a(证据不足不拦截)
        errs, _ = _n20_scan(
            {'Role': {'del': [{'addr': '0x00411ca0', 'suppressed': True}],
                      'comp': []}}, self.ROWS)
        self.assertFalse([e for e in errs if 'N20a' in e], errs)


if __name__ == '__main__':
    unittest.main()
