#!/usr/bin/env python3
"""[Blocka 案行为钉死 2026-11-19] stage1 4c段 deleting dtor 织入物剥离——
flags 槽渲染名任意化（saved lvar 消歧名 Block/Blocka）后的形态全覆盖。

背景: IDB 陈旧 saved user lvars 把 deleting dtor 参数槽钉死为 Block/Blocka
（Block 全局撞名消歧），hexrays 体内引用 Blocka ≠ 4c段既有 a2/退化形模式 ⇒
半剥离（签名剥了/尾残留）⇒ C2065 ⇒ TU 编译死 ⇒ 整类退出 S4（L1 49→43 事件）。

钉死面:
  [P1] 消歧名形 `((unsigned __int8)Blocka & 1) != 0) operator delete(Block);`
  [P2] 无 cast 形 `((Blocka & 1) != 0)`（param 型健康时 hexrays 渲染）
  [P3] 块语句形 `if (...) { operator delete(this); }`
  [P4] 真逻辑体共存（SceneMgr 形: 数组清尾 + 织入尾共存, 只剥织入尾）
  [N1] 非 dtor 函数的 Blocka 引用不动（LoadFromFile 形）
  [N2] 非 deleting dtor (flags=['dtor']) 的真条件删不动
  [R1] 既有 a2 形回归保护

用法: python3 tools/test_stage1_blocka_strip_20261119.py
"""
import re
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline'))

from stages.stage1_structural import run as s1_run
from stages.transform import make_context

FAIL = []

def check(tag, cond, detail=''):
    if cond:
        print('  ✓ %s' % tag)
    else:
        FAIL.append(tag)
        print('  ✗ %s %s' % (tag, detail))

def strip_dtor(code, cls, sig, flags):
    ctx = make_context(cls, '~%s' % cls, sig=sig, flags=flags)
    return s1_run(code, ctx)

# ── P1: 消歧名形（CEffectSystem 0x4c5d50 真实语料形态）──
p1_in = '''CEffect *__thiscall CEffectSystem_0(CEffect *Block, void *Blocka)
{
  sub_4C5D70(Block);
  if ( ((unsigned __int8)Blocka & 1) != 0 )
    operator delete(Block);
  return Block;
}'''
p1_out = strip_dtor(p1_in, 'CEffectSystem',
                    'int __thiscall(CEffectSystem *this, void *Block, char)',
                    ['dtor', 'deleting'])
check('P1 尾剥除(Blocka 形)', '((unsigned __int8)Blocka & 1)' not in p1_out, p1_out)
check('P1 条件删语句消失', 'operator delete' not in p1_out, p1_out)
check('P1 return 织入物消失', 'return Block' not in p1_out and 'return this' not in p1_out, p1_out)
check('P1 Blocka 无残留引用', 'Blocka' not in p1_out, p1_out)
check('P1 真体保留(sub_调用)', 'sub_4C5D70' in p1_out, p1_out)

# ── P2: 无 cast 形 ──
p2_in = '''void *__thiscall X_Dtor(void *Block, char a2)
{
  if ( (a2 & 1) != 0 )
    operator delete(Block);
  return Block;
}'''
p2_out = strip_dtor(p2_in, 'X', 'int __thiscall(X *this, char a2)', ['dtor', 'deleting'])
check('P2 尾剥除(无 cast a2 形)', 'operator delete' not in p2_out and 'a2' not in p2_out, p2_out)

# ── P3: 块语句形 ──
p3_in = '''void *__thiscall Y_Dtor(void *Block, void *Blocka)
{
  init(Block);
  if ( ((unsigned __int8)Blocka & 1) != 0 )
  {
    operator delete(Block);
  }
  return Block;
}'''
p3_out = strip_dtor(p3_in, 'Y', 'int __thiscall(Y *this, void *Blocka, char)', ['dtor', 'deleting'])
check('P3 块语句尾剥除', 'operator delete' not in p3_out, p3_out)
check('P3 真体保留(init)', 'init' in p3_out, p3_out)

# ── P4: 真逻辑体共存（SceneMgr 0x4cd930 形, 缩略）──
p4_in = '''void *__thiscall SceneMgr(void *Block, void *Blocka)
{
  int v3;
  v3 = *((_DWORD *)Block + 7);
  if ( v3 )
  {
    operator delete(*((void **)Block + 3));
    *((_DWORD *)Block + 3) = 0;
  }
  if ( ((unsigned __int8)Blocka & 1) != 0 )
    operator delete(Block);
  return Block;
}'''
p4_out = strip_dtor(p4_in, 'SceneMgr', 'int __thiscall(SceneMgr *this, void *Blocka, char)', ['dtor', 'deleting'])
check('P4 织入尾剥除', 'operator delete(Block)' not in p4_out and '(Blocka & 1)' not in p4_out, p4_out)
# [T20 预期] 首参(this 槽) Block→this 改名是既有正确行为, 真体引用随迁
check('P4 真体数组删保留(T20 this 形)', 'operator delete(*((void **)this + 3))' in p4_out, p4_out)
check('P4 真体字段清零保留(T20 this 形)', '*((_DWORD *)this + 3) = 0' in p4_out, p4_out)

# ── N1: 非 dtor 函数的 flags 性质引用不被 4c 剥 ──
# 既有成员函数变换(this 参隐式化 + T20 改名)预期发生; 不变量 = 体内 Blocka
# 引用原样保留(非 dtor 无织入物剥除权)
n1_in = '''int __thiscall LoadFromFile(void *Block, void *Blocka, char *psz)
{
  return read(Block, Blocka, psz);
}'''
n1_out = s1_run(n1_in, make_context('ParticleEffect', 'LoadFromFile',
                                     sig='int __thiscall(ParticleEffect *this, void *Blocka, char *psz)',
                                     flags=None))
check('N1 非 dtor 体 Blocka 引用保留', 'Blocka' in n1_out, n1_out)
check('N1 非 dtor 体调用保留', 'read(' in n1_out, n1_out)
check('N1 非 dtor 无条件删剥', 'operator delete' not in n1_out, n1_out)

# ── N2: 非 deleting dtor 的真条件删不动 ──
n2_in = '''void __thiscall Z::~Z(Z *this)
{
  if ( m_bFlag & 1 )
    operator delete(this);
}'''
n2_out = strip_dtor(n2_in, 'Z', 'void __thiscall(Z *this)', ['dtor'])
check('N2 非 deleting dtor 条件删保留', 'operator delete' in n2_out, n2_out)

# ── R1: 既有 a2 形回归保护 ──
r1_in = '''int __thiscall W2(void *this, int a2)
{
  body(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}'''
r1_out = strip_dtor(r1_in, 'W', 'int __thiscall(W *this, int a2)', ['dtor', 'deleting'])
check('R1 a2 形仍剥', 'operator delete' not in r1_out and '(a2 & 1)' not in r1_out, r1_out)

print()
if FAIL:
    print('FAIL: %d 项 — %s' % (len(FAIL), FAIL))
    sys.exit(1)
print('ALL PASS')
