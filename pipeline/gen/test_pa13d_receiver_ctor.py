"""P-A13d-2 (2026-11-22) 接收者前缀 ctor 调用——P-A13d 宽门误吞守卫测试。

病灶(CScreenMode::SetMode / gbAudioManager 实证, IAT mangle
??0gbAudioManager@@QAE@AAHPAUgbAudioMgrDesc@@@Z = (int&, gbAudioMgrDesc*)):
  stage2 方法化 → `v3->gbAudioManager::gbAudioManager(&v9, &v13);`
  P-A13d `\bCls::Cls(&obj, args)` 的 \\b 在 `->` 之后照样命中, `v3->` 残留
  ⇒ `v3->v9 = gbAudioManager(&v13);` 假成员访问(C2039 'v9' : is not a member
  of 'gbAudioManager' + C2440 级联)。
语义: PTR 上就地构造(C++ 无显式 ctor 调用语法) ⇒ placement new 兄弟形
  (P-A13/P-A13b/P-A13e 同律)。
"""
import os
import sys
import unittest
_GEN = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, _GEN)
os.environ.setdefault('PROJECT_ROOT', os.path.dirname(os.path.dirname(_GEN)))
from stages.stage5_fixup import _run_inner
from stages.transform import make_context


class TestPA13dReceiverCtor(unittest.TestCase):
    def _run(self, code, cls='CScreenMode', meth='SetMode'):
        return _run_inner(code, make_context(cls, meth))

    def test_receiver_ctor_becomes_placement_new(self):
        code = ('void CScreenMode::SetMode(int mode)\n{\n'
                '  gbAudioManager *v3;\n'
                '  int v9;\n'
                '  gbAudioMgrDesc v13;\n'
                '  if ( v3 )\n'
                '    v3->gbAudioManager::gbAudioManager(&v9, &v13);\n'
                '}\n')
        out = self._run(code)
        self.assertIn('new ((void *)v3) gbAudioManager(v9, &v13);', out)
        self.assertNotIn('v3->v9', out)

    def test_receiver_ctor_this_receiver(self):
        code = ('void Cls::Init(void)\n{\n'
                '  int v9;\n'
                '  gbAudioMgrDesc v13;\n'
                '  this->gbAudioManager::gbAudioManager(&v9, &v13);\n'
                '}\n')
        out = self._run(code, cls='Cls', meth='Init')
        self.assertIn('new ((void *)this) gbAudioManager(v9, &v13);', out)
        self.assertNotIn('->v9', out)

    def test_free_form_still_rewritten(self):
        # P-A13d 原语义保持: Cls::Cls(&obj, args) → obj = Cls(args) (无接收者前缀)
        code = ('void CScreenMode::SetMode(int mode)\n{\n'
                '  gbVec3D v1;\n'
                '  gbVec3D::gbVec3D(&v1, 0, 0);\n'
                '}\n')
        out = self._run(code)
        self.assertIn('v1 = gbVec3D(0, 0);', out)

    def test_receiver_form_no_longer_mangled_by_pa13d(self):
        # 双保险: 即使接收者规则未命中(如括号接收者), P-A13d 也不许再吞
        # —— lookbehind 守卫使其 fail-loud(留未改写=编译器可见)而非静默错形
        code = ('void CScreenMode::SetMode(int mode)\n{\n'
                '  gbAudioManager *v3;\n'
                '  int v9;\n'
                '  gbAudioMgrDesc v13;\n'
                '  v3->gbAudioManager::gbAudioManager(&v9, &v13);\n'
                '}\n')
        out = self._run(code)
        self.assertNotIn('v3->v9 =', out)


if __name__ == '__main__':
    unittest.main()
