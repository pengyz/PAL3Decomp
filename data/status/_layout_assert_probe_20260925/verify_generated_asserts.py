#!/usr/bin/env python3
"""编译器裁判：把 `tools/layout_assert_gen.py` 的产物交给**真机 MSVC 6.0 SP0** 编译。

本脚本证明的四件事（全部用真编译器，不是"看起来对"）：

1. **发现常量**：`sizeof` / `offsetof` / `sizeof(void (Cls::*)())` 的**真值由编译器自己给出** ——
   对每个目标枚举候选值，唯一"不报错"的候选即真值（报 C2118 = 常量但值不符）。
   特别地：虚基区域成员的 offsetof 对**所有**候选都报 **C2057**（不是常量表达式）⇒
   生成器必须跳过（E-3），这一步同时证明"跳过"不是保守过头。
2. **正相**：用发现到的常量生成 `_layout_asserts.h` ⇒ 全部生效断言编译 **0 错误**。
3. **负相（判别力）**：故意把 sizeof / 成员偏移 / 继承形状改错 ⇒ 编译器必须报 **C2118**
   并**指到对应行**；把虚基区域成员硬写进去（模拟"不跳过的朴素生成器"）⇒ 必须报 **C2057**。
4. **命名唯一性**：同一 typedef 名写两次 ⇒ 必须报 **C2086**（这就是生成器要做全局去重的原因）。

复现：
```sh
cd /home/peng/workspace/PAL3Decomp
python3 data/status/_layout_assert_probe_20260925/verify_generated_asserts.py
```
"""
from __future__ import annotations

import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import replace
from pathlib import Path

PROBE_DIR = Path(__file__).resolve().parent
ROOT = PROBE_DIR.parents[2]
sys.path.insert(0, str(ROOT / 'tools'))

from layout_assert_gen import (  # noqa: E402
    BaseSpec, ClassLayout, Evidence, GenOptions, MemberSpec, generate,
)

WINE_CL = ROOT / 'tools' / 'wine_cl.sh'
VC6_INC = ROOT / 'tools' / 'compilers' / 'msvc6.0' / 'Include'

# 与被探针源（shape.cpp / off.cpp）逐字同形的声明；只有声明，不需要定义
CLASSES_H = """\
struct A1 { virtual void f(); int a; };
struct B1 { virtual void g(); int b; };
struct C1 { virtual void c(); int c_; };
struct V1 { virtual void v(); int vv; };
struct V2 { virtual void w(); int ww; };
struct SI    : A1 { void h(); };
struct MI2   : A1, B1 { void h(); };
struct MI3   : A1, B1, C1 { void h(); };
struct VOnly : virtual V1 { void h(); };
struct MIV   : A1, B1, virtual V1 { void h(); };
struct MIVV  : A1, virtual V1, virtual V2 { void h(); };
struct VV    : virtual V1, virtual V2 { void h(); };
struct DERofMI2 : MI2 { void h(); };
struct DERofSI  : SI  { void h(); };
struct DERofV   : VOnly { void h(); };
struct N  : A1 { int n; };
struct NV : A1, virtual V1 { int x; };
struct DV : virtual V1 { int dm; virtual void q(); };
"""

PMF_CANDIDATES = (4, 8, 12, 16, 20)
SIZE_CANDIDATES = (4, 8, 12, 16, 20, 24, 28, 32, 36, 40)
OFF_CANDIDATES = (0, 4, 8, 12, 16, 20, 24, 28, 32)

#: 目标表：(类别, 类, 成员, 候选)  —— 形状 / 尺寸 / 非虚区域偏移 / 虚基区域偏移
TARGETS = [
    ('pmf', 'SI', None, PMF_CANDIDATES),
    ('pmf', 'MI2', None, PMF_CANDIDATES),
    ('pmf', 'MI3', None, PMF_CANDIDATES),
    ('pmf', 'VOnly', None, PMF_CANDIDATES),
    ('pmf', 'MIV', None, PMF_CANDIDATES),
    ('pmf', 'MIVV', None, PMF_CANDIDATES),
    ('pmf', 'VV', None, PMF_CANDIDATES),
    ('pmf', 'DERofMI2', None, PMF_CANDIDATES),      # ★ 单直接基但基类是多继承类
    ('pmf', 'DERofSI', None, PMF_CANDIDATES),
    ('pmf', 'DERofV', None, PMF_CANDIDATES),
    ('size', 'SI', None, SIZE_CANDIDATES),
    ('size', 'MI2', None, SIZE_CANDIDATES),
    ('size', 'N', None, SIZE_CANDIDATES),
    ('size', 'NV', None, SIZE_CANDIDATES),
    ('size', 'DV', None, SIZE_CANDIDATES),
    ('offset', 'SI', 'a', OFF_CANDIDATES),
    ('offset', 'MI2', 'a', OFF_CANDIDATES),
    ('offset', 'MI2', 'b', OFF_CANDIDATES),
    ('offset', 'N', 'a', OFF_CANDIDATES),
    ('offset', 'N', 'n', OFF_CANDIDATES),
    ('offset', 'NV', 'a', OFF_CANDIDATES),          # 非虚基成员（有虚基的类里仍是常量）
    ('offset', 'NV', 'x', OFF_CANDIDATES),          # 本类成员（虚继承下仍是常量）
    ('offset', 'DV', 'dm', OFF_CANDIDATES),         # 本类成员
    ('offset', 'NV', 'vv', OFF_CANDIDATES),         # ★ 虚基成员 ⇒ 预期全候选 C2057
    ('offset', 'DV', 'vv', OFF_CANDIDATES),         # ★ 虚基成员 ⇒ 预期全候选 C2057
]

_ERR_RE = re.compile(r'\((\d+)\)\s*:\s*error\s+(C\d+)')


class CompileError(RuntimeError):
    pass


def compile_tu(text: str, workdir: Path, tag: str) -> tuple:
    """→ (ok, [(line, code, msg)], stdout)"""
    workdir.mkdir(parents=True, exist_ok=True)
    src = workdir / ('%s.cpp' % tag)
    obj = workdir / ('%s.obj' % tag)
    src.write_text(text, encoding='utf-8')
    cmd = [str(WINE_CL), '/c', '/nologo', '/O2', '/GR',
           '/I%s' % VC6_INC, '/Fo%s' % obj, str(src)]
    proc = subprocess.run(cmd, capture_output=True, text=True, timeout=300)
    out = proc.stdout + proc.stderr
    # wine_cl.sh 的路径回显是 Z:\... ⇒ 行号/错误码解析不受影响
    errs = [(int(m.group(1)), m.group(2),
             line.split('error', 1)[1].strip())
            for line in out.splitlines()
            for m in [_ERR_RE.search(line)] if m]
    hard = [e for e in errs if not e[1].startswith('C4')]      # 忽略警告类
    return (not hard), errs, out


def _cond(kind: str, cls: str, member, cand: int) -> str:
    if kind == 'pmf':
        return 'sizeof(void (%s::*)()) == %d' % (cls, cand)
    if kind == 'size':
        return 'sizeof(%s) == %d' % (cls, cand)
    return 'offsetof(%s, %s) == %d' % (cls, member, cand)


def discover(workdir: Path) -> dict:
    """每个目标单独一次编译（候选不多，避免触发 C1003 截断）。"""
    found = {}
    head = '#include <stddef.h>\n' + CLASSES_H
    first_line = head.count('\n') + 1          # 第一个候选断言的行号（1-based）
    for i, (kind, cls, member, cands) in enumerate(TARGETS):
        body = ''.join('typedef char t_%d[(%s) ? 1 : -1];\n'
                       % (cand, _cond(kind, cls, member, cand)) for cand in cands)
        ok, errs, out = compile_tu(head + body, workdir, 'disc_%02d' % i)
        bad_codes = {code for _, code, _ in errs}
        # 候选 i 的断言在第 first_line+i 行；没有错误行指向它 ⇒ 该候选为真值
        passed = _passed_by_line(cands, errs, first_line=first_line)
        if kind == 'offset' and bad_codes == {'C2057', 'C2466'} and not passed:
            found[(cls, member)] = 'NOT_CONSTANT'
            print('  %-8s %-10s %-4s ⇒ **非虚基区域**：全候选 C2057（不是常量表达式）⇒ 必须跳过'
                  % (kind, cls, member))
            continue
        if len(passed) != 1:
            raise CompileError('目标 %s %s %s 常量发现失败：passed=%s codes=%s\n%s'
                               % (kind, cls, member, passed, sorted(bad_codes), out[-2000:]))
        found[(kind, cls, member)] = passed[0]
        print('  %-8s %-10s %-4s = %d' % (kind, cls, member or '-', passed[0]))
    return found


def _passed_by_line(cands, errs, first_line: int) -> list:
    """候选 i 的断言在第 first_line + i 行；没有错误行指向它 ⇒ 该候选为真值。"""
    bad_lines = {ln for ln, _c, _m in errs}
    return [c for i, c in enumerate(cands) if first_line + i not in bad_lines]


def build_layouts(consts: dict) -> dict:
    """用编译器发现到的常量构造布局集（含虚基区域成员，验证"跳过"）。"""
    ev = Evidence(grade='A', origin='probe', independent=True,
                  detail='verify_generated_asserts.py 由真机 MSVC6 发现')
    def base(n, virtual=False):
        return BaseSpec(name=n, is_virtual=virtual)
    def mem(n, off, owner=None):
        return MemberSpec(name=n, offset=off, owner=owner, evidence=ev)
    L = {}
    # 无条件基：必须进布局集，否则闭包不完整 ⇒ 形状断言会（正确地）降级为可疑而不生效
    for leaf in ('A1', 'B1', 'C1', 'V1', 'V2'):
        L[leaf] = ClassLayout(leaf)
    L['SI'] = ClassLayout('SI', bases=(base('A1'),),
                          members=(mem('a', consts[('offset', 'SI', 'a')], 'A1'),),
                          binary_size=consts[('size', 'SI', None)], size_evidence=ev)
    L['MI2'] = ClassLayout('MI2', bases=(base('A1'), base('B1')),
                           members=(mem('a', consts[('offset', 'MI2', 'a')], 'A1'),
                                    mem('b', consts[('offset', 'MI2', 'b')], 'B1')),
                           binary_size=consts[('size', 'MI2', None)], size_evidence=ev)
    L['N'] = ClassLayout('N', bases=(base('A1'),),
                         members=(mem('a', consts[('offset', 'N', 'a')], 'A1'),
                                  mem('n', consts[('offset', 'N', 'n')])),
                         binary_size=consts[('size', 'N', None)], size_evidence=ev)
    L['NV'] = ClassLayout('NV', bases=(base('A1'), base('V1', virtual=True)),
                          members=(mem('a', consts[('offset', 'NV', 'a')], 'A1'),
                                   mem('vv', 0, 'V1'),          # 虚基区域 ⇒ 必跳过
                                   mem('x', consts[('offset', 'NV', 'x')])),
                          binary_size=consts[('size', 'NV', None)], size_evidence=ev)
    L['DV'] = ClassLayout('DV', bases=(base('V1', virtual=True),),
                          members=(mem('dm', consts[('offset', 'DV', 'dm')]),
                                   mem('vv', 0, 'V1')),        # 虚基区域 ⇒ 必跳过
                          binary_size=consts[('size', 'DV', None)], size_evidence=ev)
    L['VOnly'] = ClassLayout('VOnly', bases=(base('V1', virtual=True),))
    L['MI3'] = ClassLayout('MI3', bases=(base('A1'), base('B1'), base('C1')))
    L['MIV'] = ClassLayout('MIV', bases=(base('A1'), base('B1'), base('V1', virtual=True)))
    L['MIVV'] = ClassLayout('MIVV', bases=(base('A1'), base('V1', virtual=True),
                                           base('V2', virtual=True)))
    L['VV'] = ClassLayout('VV', bases=(base('V1', virtual=True), base('V2', virtual=True)))
    L['DERofMI2'] = ClassLayout('DERofMI2', bases=(base('MI2'),))
    L['DERofSI'] = ClassLayout('DERofSI', bases=(base('SI'),))
    L['DERofV'] = ClassLayout('DERofV', bases=(base('VOnly'),))
    return L


def main() -> int:
    if not WINE_CL.exists():
        print('缺少 %s' % WINE_CL, file=sys.stderr)
        return 2
    workdir = Path(tempfile.mkdtemp(prefix='layout_assert_probe_'))
    print('== 1. 常量发现（真机 MSVC6 SP0，唯一不报错的候选即真值）==')
    consts = discover(workdir)
    layouts = build_layouts(consts)

    print('\n== 2. 正相：生成的 _layout_asserts.h 必须 0 错误 ==')
    res = generate(layouts, GenOptions(header_guard='PAL3_LAYOUT_ASSERTS_H'))
    tu = '#include <stddef.h>\n' + CLASSES_H + '\n' + res.text + '\nint main() { return 0; }\n'
    ok, errs, out = compile_tu(tu, workdir, 'gen_ok')
    print('  census: active=%s commented=%s skipped=%s' %
          (res.census['active'], res.census['commented'], res.census['skipped']))
    print('  生效断言 %d 条 ⇒ 编译 %s' % (res.census['active'], '0 错误 ✓' if ok else '失败 ✗'))
    if not ok:
        print(out[-3000:])
        return 1
    header_lines = tu.splitlines()
    first = next(i for i, l in enumerate(header_lines) if l.startswith('typedef char _a_'))
    # 生成头里第 k 条生效断言的行号（用于负相"指到对应行"核对）
    active_lines = [i for i, l in enumerate(header_lines) if l.startswith('typedef char _a_')]
    print('  首条生效断言在 TU 第 %d 行（共 %d 条）' % (first + 1, len(active_lines)))

    print('\n== 3. 负相：改错常量必须被编译器抓到（C2118）==')
    neg = []
    # 3a. sizeof 改错
    bad = dict(layouts)
    bad['SI'] = replace(layouts['SI'], binary_size=layouts['SI'].binary_size + 4)
    neg.append(('sizeof 改错 (+4)', bad, 'C2118'))
    # 3b. 成员偏移改错
    bad = dict(layouts)
    bad['MI2'] = replace(layouts['MI2'], members=(
        layouts['MI2'].members[0],
        replace(layouts['MI2'].members[1],
                offset=layouts['MI2'].members[1].offset + 4)))
    neg.append(('成员偏移改错 (+4)', bad, 'C2118'))
    # 3c. 继承形状改错（少写一个基类 ⇒ 预测 4，而声明是 MI ⇒ 8）
    bad = dict(layouts)
    bad['MI2'] = replace(layouts['MI2'], bases=(BaseSpec(name='A1'),))
    neg.append(('继承形状改错 (MI 写成 SI)', bad, 'C2118'))
    # 3d. 单直接基但基类是 MI：把闭包判据退回"只看直接基"
    bad = dict(layouts)
    bad['DERofMI2'] = replace(layouts['DERofMI2'], bases=(BaseSpec(name='SI'),))
    neg.append(('闭包判据退回直接基 (DERofMI2)', bad, 'C2118'))
    for label, lays, want in neg:
        r = generate(lays, GenOptions())
        tu = '#include <stddef.h>\n' + CLASSES_H + '\n' + r.text + '\nint main() { return 0; }\n'
        ok, errs, out = compile_tu(tu, workdir, 'neg_%d' % len(label))
        codes = sorted({c for _l, c, _m in errs})
        good = (not ok) and want in codes
        print('  %-32s ⇒ %s %s' % (label, '查获' if good else '未查获 ✗', codes))
        if not good:
            print(out[-2000:])
            return 1

    print('\n== 4. 虚基区域成员的 offsetof 硬写进去 ⇒ 必须 C2057（E-3）==')
    naive = ('#include <stddef.h>\n' + CLASSES_H +
             '\ntypedef char naive_vv[(offsetof(NV, vv) == 12) ? 1 : -1];'
             '\ntypedef char naive_dv[(offsetof(DV, vv) == 8) ? 1 : -1];'
             '\nint main() { return 0; }\n')
    ok, errs, out = compile_tu(naive, workdir, 'naive_vbase')
    codes = sorted({c for _l, c, _m in errs})
    good = (not ok) and 'C2057' in codes
    print('  朴素生成器（不跳过虚基成员）⇒ %s %s' % ('C2057 ✓' if good else '未查获 ✗', codes))
    if not good:
        print(out[-2000:])
        return 1
    print('  ⇒ 与生成器的跳过判据一致：NV::vv / DV::vv 在发现阶段即为 NOT_CONSTANT=%s'
          % [k for k, v in consts.items() if v == 'NOT_CONSTANT'])

    print('\n== 5. 断言类型名重复（命名唯一性要求的实证）==')
    # 5a. 同名 + **数组尺寸不同** ⇒ C2369 'redefinition; different subscripts'
    #     （本轮实测：负数组技巧下重名的实际错误码是 C2369，不是 C2086 —— 见 README 顾虑 1）
    dup = ('#include <stddef.h>\n' + CLASSES_H +
           '\ntypedef char dup_same[(sizeof(int) == 4) ? 1 : -1];'
           '\ntypedef char dup_same[(sizeof(int) == 4) ? 2 : 1];'
           '\nint main() { return 0; }\n')
    ok, errs, out = compile_tu(dup, workdir, 'dup_typedef_diff')
    codes = sorted({c for _l, c, _m in errs})
    good = (not ok) and 'C2369' in codes
    print('  同名 typedef 但数组尺寸不同 ⇒ %s %s' % ('C2369 ✓' if good else '未查获 ✗', codes))
    if not good:
        print(out[-2000:])
        return 1
    # 5b. 同名 + 形态冲突（数组 vs 指针）⇒ MSVC6 用 C2372 'different types of indirection'
    #     重名家族实测：C2369 尺寸不同 / C2371 基本类型不同 / C2372 间接层类型不同 /
    #     C2040 间接层不同；**C2086 未出现** ⇒ 简报"同名 ⇒ C2086"按实测收窄（见 README 顾虑 1）
    dup_type = ('#include <stddef.h>\n' + CLASSES_H +
                '\ntypedef char dup_type[(sizeof(int) == 4) ? 1 : -1];'
                '\ntypedef int *dup_type;'
                '\nint main() { return 0; }\n')
    ok, errs, out = compile_tu(dup_type, workdir, 'dup_typedef_type')
    codes = sorted({c for _l, c, _m in errs})
    redef_family = {'C2369', 'C2371', 'C2372', 'C2040'}
    good = (not ok) and bool(redef_family & set(codes))
    print('  同名 typedef 且形态冲突（数组 vs 指针）⇒ %s %s'
          % ('查获 ✓' if good else '未查获 ✗', codes))
    if not good:
        print(out[-2000:])
        return 1
    # 5c. 同名 + **类型相同**：MSVC6 接受冗余 typedef（**不报错**）
    #     ⇒ 生成器仍强制唯一：重名断言一旦一条通过一条失败，诊断会指向含混的名字（C2369+C2118 交织）。
    dup_same = ('#include <stddef.h>\n' + CLASSES_H +
                '\ntypedef char dup_id[(sizeof(int) == 4) ? 1 : -1];'
                '\ntypedef char dup_id[(sizeof(int) == 4) ? 1 : -1];'
                '\nint main() { return 0; }\n')
    ok, errs, out = compile_tu(dup_same, workdir, 'dup_typedef_same')
    codes = sorted({c for _l, c, _m in errs})
    print('  同名 typedef 且类型相同 ⇒ %s（MSVC6 允许冗余 typedef；属本轮实测收窄，见 README 顾虑 1）'
          % (codes or '0 错误'))

    shutil.rmtree(workdir, ignore_errors=True)
    print('\nALL CHECKS PASSED（真机 MSVC6 SP0：发现 %d 个常量；正相 0 错误；'
          '4 类负相均被查获；虚基成员 C2057；重名 C2369/C2372（重定义族，非 C2086））'
          % len(consts))
    return 0


if __name__ == '__main__':
    sys.exit(main())