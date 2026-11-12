#!/usr/bin/env python3
"""[P-A19残段退役回归 2026-11-12] operator new 诚实 cast 保真测试。

背景定谳:
  IDB lvars 通路落库(apply_annotations Section 9b)后, Hex-Rays 新导出对
  char* 型 lvar 渲染诚实形态 `v = (char *)operator new(N);`(decomp 全库
  12 站点, (int) 站点=0)。stage5 曾有全局替换
  `(char *)operator new` → `(int)operator new`(P-A19 2026-11-11 残段),
  专门破坏诚实渲染制造 C2440——annotation 完备性铁律: 标注对了, 变换就该拆。

本测试锁定退役后的发射行为(反回归):
  T1 诚实体保真:   干净导出体过发射链后 (char *)operator new 原样保留,
                   且不得出现 (int)operator new。
  T2 bare渲染补cast: 无 cast 的 `v = operator new(N)` 且 v 有指针声明
                   → 补 (char *) 仍生效(不影响 bare 案例的原有服务)。
  T3 声明保真:      `char *v5;` 声明不被改写为 int。

通过判据: T1-T3 全 PASS(退出码 0)。
"""
import json
import os
import re
import sys

_PROJECT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for _p in (_PROJECT, os.path.join(_PROJECT, 'pipeline'),
           os.path.join(_PROJECT, 'pipeline', 'gen')):
    if _p not in sys.path:
        sys.path.insert(0, _p)

FAILS = []


def check(name, cond, detail=''):
    print('[%s] %s%s' % ('PASS' if cond else 'FAIL', name,
                         (' -- ' + detail) if detail and not cond else ''))
    if not cond:
        FAILS.append(name)


def main():
    # 数据源: 真实导出体(不是手造字符串——保真测试必须打真数据)
    decomp = os.path.join(_PROJECT, 'asm', 'pal3', 'decomp',
                          'VideoPlayer_SetRegionint_int_0053b720.json')
    d = json.load(open(decomp, encoding='utf-8'))
    body = d['decompiled_c'].strip()
    check('T0 导出体含诚实 (char *)operator new',
          '(char *)operator new' in body)

    # 发射链前段(与 emit_cpp.generate_class_cpp 同序)
    from stages.emit_cpp import _apply_lvar_overrides
    from stages.transform import run_transforms, make_context
    code = _apply_lvar_overrides(body, '0x0053B720')
    ctx = make_context('VideoPlayer', 'SetRegion', sig=d.get('signature', ''),
                       stub_registry=set())
    out = run_transforms(code, ctx)

    # T1 诚实 cast 保真
    check('T1 (char *)operator new 保真',
          '(char *)operator new' in out,
          '产物含: %s' % [l.strip() for l in out.split('\n') if 'operator new' in l][:3])
    check('T1b 无 (int)operator new 残留',
          '(int)operator new' not in out)

    # T3 声明保真(_apply_lvar_overrides 改写后带空格: `char * v5;`)
    check('T3 char *v5 声明保真',
          re.search(r'char \*\s*v5;', out) is not None,
          '声明行: %s' % [l.strip() for l in out.split('\n') if 'v5;' in l][:2])

    # T2 bare 渲染补 cast 不受影响(合成最小案例, 指针声明 → (char *))
    bare = 'void VideoPlayer::T2Case(void)\n{\n  char *v9;\n  v9 = operator new(8);\n}\n'
    ctx2 = make_context('VideoPlayer', 'T2Case', sig='void __cdecl(void)',
                        stub_registry=set())
    out2 = run_transforms(bare, ctx2)
    check('T2 bare 渲染仍补 (char *) cast',
          'v9 = (char *)operator new(8);' in out2,
          '产物: %s' % [l.strip() for l in out2.split('\n') if 'operator new' in l][:2])

    # T4 int 声明 bare 渲染 → (int)(P-A19 原服务的活客户群, 121 站点)
    bare_int = ('void VideoPlayer::T4Case(void)\n{\n  int v15;\n'
                '  v15 = operator new(12);\n}\n')
    ctx3 = make_context('VideoPlayer', 'T4Case', sig='void __cdecl(void)',
                        stub_registry=set())
    out3 = run_transforms(bare_int, ctx3)
    check('T4 int 声明 bare 渲染补 (int) cast',
          'v15 = (int)operator new(12);' in out3,
          '产物: %s' % [l.strip() for l in out3.split('\n') if 'operator new' in l][:2])

    # T5 诚实 (char *) + int 声明并存(历史矛盾形态)
    # → 管线任一正确产物皆可: (int) 转译 或 stage4 (int)(char *) 双cast(均合法 C++)
    mixed = ('void VideoPlayer::T5Case(void)\n{\n  int v15;\n'
             '  v15 = (char *)operator new(12);\n}\n')
    out4 = run_transforms(mixed, ctx3)
    t5_line = [l.strip() for l in out4.split('\n') if 'operator new' in l]
    check('T5 (char*)+int声明 → 语句以 (int) 收编',
          any(l.startswith('v15 = (int)') for l in t5_line),
          '产物: %s' % t5_line[:2])

    # T6 诚实 (char *) + 指针声明(已判 T1)之外的反向锁定:
    #    unsigned long 声明同样视为整型族
    bare_ul = ('void VideoPlayer::T6Case(void)\n{\n  unsigned long v15;\n'
               '  v15 = operator new(12);\n}\n')
    out5 = run_transforms(bare_ul, ctx3)
    check('T6 unsigned long 声明 bare 渲染补 (int) cast',
          'v15 = (int)operator new(12);' in out5,
          '产物: %s' % [l.strip() for l in out5.split('\n') if 'operator new' in l][:2])

    print('\n=== %s ===' % ('ALL PASS' if not FAILS else 'FAILED: %s' % FAILS))
    return 1 if FAILS else 0


if __name__ == '__main__':
    sys.exit(main())
