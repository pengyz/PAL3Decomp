#!/usr/bin/env python3
"""[用例钉死行为 2026-11-15] format_non_slot_decl 测试集。

来源: AStarPathFinder.h G1b 三缺陷事故的回归钉死:
  1. 多token返回类型(unsigned __int8) + name位置类限定名 → 名字重复拼接(C2146)
  2. 单参数有名this(A *this)未剥除 → 声明带this参数
  3. dtor/ctor形态 → 非法C++声明, 必须返回None(调用者专用路径发射)
"""
import sys
import os

sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))
from tools.format_non_slot_decl import format_non_slot_decl as f

CLS = 'AStarPathFinder'

CASES = [
    # (name, signature, expected, 说明)
    ('ReleaseAll', 'void __thiscall AStarPathFinder::ReleaseAll()',
     'void ReleaseAll()', '基本: void返回+无参'),
    ('GetHeuristicIdx', 'unsigned __int8 __thiscall AStarPathFinder::GetHeuristicIdx(AStarPathFinder *this, int nX, int nY)',
     'unsigned __int8 GetHeuristicIdx(int, int)', '多token返回+双参[事故钉死#1]'),
    ('PopStack', 'AStarPathFinder::NODE *__thiscall AStarPathFinder::PopStack(AStarPathFinder *this)',
     'NODE * PopStack()', '指针返回+嵌套类型限定名+单参this[事故钉死#2]'),
    ('~AStarPathFinder', 'void __thiscall ~AStarPathFinder(AStarPathFinder *this)',
     None, 'dtor必须None[事故钉死#3]'),
    ('AStarPathFinder', 'AStarPathFinder *__thiscall AStarPathFinder(AStarPathFinder *this)',
     None, 'ctor必须None(专用路径)'),
    ('`scalar deleting destructor\'', 'void __thiscall `scalar deleting destructor\'(AStarPathFinder *this, char)',
     None, '编译器生成dtor族必须None[事故钉死#4:C2018]'),
    ('`vcall\'0\'', 'int `vcall\'0\'()',
     None, 'vcall thunk必须None'),
    ('_scalar_dtor_BE40', 'void __thiscall _scalar_dtor_BE40(UIScene *this, int)',
     None, 'dtor族分析名必须None[事故钉死#5]'),
    ('F', 'void __thiscall UIScenePanel::F(UIScene *this, int a)',
     'void F(int)', '泛化this剥除(他类this拷贝)[事故钉死#6]'),
    ('G', 'void __thiscall G(CGame *pObj)',
     'void G(CGame *pObj)', '非this名指针参不误剥'),
    ('IsInBounds', 'int __thiscall AStarPathFinder::IsInBounds(AStarPathFinder *this, int nX, int nY)',
     'int IsInBounds(int, int)', 'int返回+多参this首剥'),
    ('TryExpand', 'int __thiscall AStarPathFinder::TryExpand(AStarPathFinder *this, AStarPathFinder::NODE *pNode, int nTileX)',
     'int TryExpand(NODE *pNode, int)', 'this剥除+自有限定名剥+指针参名保留(类内合法)'),
    ('Reset', 'virtual void __thiscall AStarPathFinder::Reset(AStarPathFinder *this)',
     'void Reset()', 'virtual前缀剥除'),
    ('FindInOpen', 'int __thiscall AStarPathFinder::FindInBounds(AStarPathFinder *this, int n)',
     'int FindInOpen(int)', '名字由调用者传入(不取signature中的名)'),
    ('Cb', 'void __cdecl Cb(int a, char *p)',
     'void Cb(int, char *p)', '__cdecl自由函数+指针参名保留(声明合法)'),
    ('F', 'AStarPathFinder::F()',
     'void F()', '单word前缀→void推断(文档化行为)'),
    ('W', 'void __thiscall W(AStarPathFinder *this)',
     'void W()', '裸单参有名this变体'),
    ('F', 'void __thiscall AStarPathFinder::F(AStarPathFinder *)',
     'void F()', '无名this(A *)剥除'),
    ('G', 'int G(this)',
     'int G()', '(this)独参剥除'),
    ('H', 'void __thiscall H(AStarPathFinder *this, const char *fmt, ...)',
     'void H(const char *fmt, ...)', '可变参保留'),
    (None, 'void A::F()', None, '无名字→None'),
    ('F', '', None, '空signature→None'),
    ('F', 'no parens here', None, '无括号→None'),
    ('operator=', 'void __thiscall AStarPathFinder::operator=(AStarPathFinder *this, int v)',
     'void operator=(int)', 'operator形态(调用者另行过滤)'),
    ('slot_0', 'void __thiscall AStarPathFinder::slot_0(AStarPathFinder *this)',
     'void slot_0()', 'slot_N占位名'),
]


def main():
    passed, failed = 0, 0
    for name, sig, expect, note in CASES:
        got = f(name, sig, CLS)
        ok = got == expect
        passed += ok
        failed += not ok
        mark = 'PASS' if ok else 'FAIL'
        print('[{}] {} — {}'.format(mark, note, repr(got) if not ok else ''))
        if not ok:
            print('      expect: {}'.format(repr(expect)))
    print('\n{}/{} pass'.format(passed, len(CASES)))
    return 0 if failed == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
