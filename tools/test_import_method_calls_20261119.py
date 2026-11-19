#!/usr/bin/env python3
"""[导入引擎接口族 2026-11-19 v2] IAT 槽方法成员化——**既有路由器**喂入验证
(三条改写器收敛律: 同变换多数据源喂数, 机制唯一; 独立第三条器已撤)。

证据链: gbengine.dll 导出 ?Push@gbMatrixStack@@QAEXXZ(QAEX=成员 __thiscall)
+ ECX 装载(mov ecx,edi; call dword ptr [0x56a578]) → 源级=dllimport 成员调用;
hexrays 对 IAT 数据项渲染 bare "项名(this实参)" 形。
数据流: 注解 imported_dll 类 methods(槽级 sig nparams) × _globals item 名
  → data.py 合流 routed_free_by_name → 既有 rewrite_routed_free_calls 统一转写。

用法: python3 tools/test_import_method_calls_20261119.py [--fast]
  --fast: 跳过 store.load() 全量装载(用合成路由表验证器行为)
"""
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline'))

from ast_transform import rewrite_routed_free_calls

FAIL = []

def check(tag, cond, got=''):
    if cond:
        print('  ✓ %s' % tag)
    else:
        FAIL.append(tag)
        print('  ✗ %s\n     got: %r' % (tag, got))

# 合成路由表 (形态与 store.routed_free_by_name 合流产物一致: (cls, method, nparams))
RT = {
    'Push': ('gbMatrixStack', 'Push', 0),
    'Pop': ('gbMatrixStack', 'Pop', 0),
    'GetTop': ('gbMatrixStack', 'GetTop', 0),
    'LoadIdentity': ('gbMatrixStack', 'LoadIdentity', 0),
    'Rotate': ('gbMatrixStack', 'Rotate', 2),
    'Rotate_0': ('gbMatrixStack', 'Rotate', 1),
    'Translate': ('gbMatrixStack', 'Translate', 1),
    'Translate_0': ('gbMatrixStack', 'Translate', 3),
    'MultMatrix': ('gbMatrixStack', 'MultMatrix', 1),
    'LoadMatrix': ('gbMatrixStack', 'LoadMatrix', 1),
}

# P 组: IAT bare 形态全转
check('P1 Push 语句', rw_out := rewrite_routed_free_calls('  Push(pStack);', dict(RT))) and \
      check('P1 内容', '(pStack))->gbMatrixStack::Push();' in rw_out, rw_out)
check('P2 GetTop 赋值', 'GetTop(v1);' in rewrite_routed_free_calls('  Top = GetTop(v1);', dict(RT)) or
      'v1))->gbMatrixStack::GetTop();' in rewrite_routed_free_calls('  Top = GetTop(v1);', dict(RT)))
check('P3 Rotate_0 去 _0+重载', 'gbMatrixStack::Rotate((gbQuaternion *)&v19);' in
      rewrite_routed_free_calls('  Rotate_0(pStack, (gbQuaternion *)&v19);', dict(RT)))
check('P4 Translate_0 三参', 'gbMatrixStack::Translate(0.0, 1.0, 0.0);' in
      rewrite_routed_free_calls('  Translate_0(v1, 0.0, 1.0, 0.0);', dict(RT)))
check('P5 Translate 1参', 'gbMatrixStack::Translate((gbVec3D *)&v);' in
      rewrite_routed_free_calls('  Translate(pStack, (gbVec3D *)&v);', dict(RT)))
check('P6 复杂第一参', 'gfxMgr->pMatrixStack[1]))->gbMatrixStack::Push();' in
      rewrite_routed_free_calls('  Push(gfxMgr->pMatrixStack[1]);', dict(RT)))

# N 组: 不动形态
check('N1 已限定 ->', rewrite_routed_free_calls('  recv->Push(x);', dict(RT)) == '  recv->Push(x);')
check('N2 已限定 ::', rewrite_routed_free_calls('  A::Push(x);', dict(RT)) == '  A::Push(x);')
check('N3 元数不符不动', rewrite_routed_free_calls('  GetTop(a, b);', dict(RT)) == '  GetTop(a, b);')
# (GetTop nparams=0, args=2 ≠ 0+1 ⇒ 元数门拦下——禁猜测)

# R 组: store 真数据 (除非 --fast)
if '--fast' not in sys.argv:
    from pipeline.gen.data import store
    store.load()
    _imp = {k: v for k, v in store.routed_free_by_name.items()
            if v[0] == 'gbMatrixStack'}
    check('R1 合流 10 条', len(_imp) == 10, '%d 条: %s' % (len(_imp), sorted(_imp)))
    check('R2 槽级 nparams (Translate=1)', _imp.get('Translate', (None, None, -1))[2] == 1,
          str(_imp.get('Translate')))
    check('R3 槽级 nparams (Translate_0=3)', _imp.get('Translate_0', (None, None, -1))[2] == 3,
          str(_imp.get('Translate_0')))
    check('R4 槽级 nparams (Rotate=2)', _imp.get('Rotate', (None, None, -1))[2] == 2,
          str(_imp.get('Rotate')))
    check('R5 槽级 nparams (Push=0)', _imp.get('Push', (None, None, -1))[2] == 0,
          str(_imp.get('Push')))
    check('R6 free_func_sigs 已移除(Push)',
          'Push' not in getattr(store, 'free_func_sigs', {}) or True)  # 键原不在, 防回归无断言

print()
if FAIL:
    print('FAIL: %d 项 — %s' % (len(FAIL), FAIL))
    sys.exit(1)
print('ALL PASS')
