#!/usr/bin/env python3
"""任务 1 等价性核证（对抗复核）：tagRECT* 伪装改写**改写前后编出的字节必须逐位一致**。

三方对照（被测函数体取自**真实生成物** `pal3/src/Misc/UIPushButton.cpp` 的
`UIPushButton::CreateWithTextures`，两侧只有两条语句不同，其余同源）：

  A = 改写前形：`p_m_rect->left = (LONG)gfxMgr->NewTexture(v11);`
      （tagRECT 字段 lvalue + 最小 `(LONG)` 补偿转换 —— 原码语义的最小可编译形）
  B = 改写后形：`*(DWORD *)((char *)p_m_rect + 0*4) = (DWORD)gfxMgr->NewTexture(v11);`
      （任务 1 产物；另一条同形，`v11`→`Buffer`）
  C = original/PAL3.exe 的 CreateWithTextures（VA 0x00440810，长 0x146 = 326 字节，
      末条 `440953 c2 14 00 ret 0x14`；来自全量反汇编核证）—— **信息项**

判据：**A 与 B 编出的函数字节逐位相同**（这就是"等价变换：改写后编译出的字节不变"）。
C 作参考基准：整 TU 编译上下文（内联/寄存器分配）与当年整文件编译可能有差异，
不同则如实报告，不作为失败判据；真正权威的整函数字节裁决是 `pipeline/cli.py match`
（等 B 族修完、UIPushButton.cpp 转绿后自动进入 L1 比对）。

用法（需 wine + 仓内 MSVC6 CL）：
    python3 tests/equiv/task1_ptr_disguise_equiv.py
"""
import os
import re
import sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(PROJECT_ROOT, 'tools'))
sys.path.insert(0, os.path.join(PROJECT_ROOT, 'pipeline'))

import gbengine_compare as gc          # noqa: E402  parse_coff_obj
import probe_compile as pc             # noqa: E402  run_cl / INCLUDE_DIRS / wpath

GEN_CPP = os.path.join(PROJECT_ROOT, 'pal3', 'src', 'Misc', 'UIPushButton.cpp')
EXE = os.path.join(PROJECT_ROOT, 'original', 'PAL3.exe')
FUNC_VA = 0x00440810
FUNC_SIZE = 0x146                      # 0x440956 - 0x440810（objdump 全量核证）

# 与 `pipeline/cli.py match` 同一组校准 flags（compare_pal3.HYPOTHESIS_FLAGS）
FLAGS = ['/O2', '/Ob2', '/Oi', '/Ot', '/Oy', '/GF', '/Gy', '/GX', '/GR', '/MD', '/Gd']

# 两条被改写语句的精确文本（NEW = 任务 1 产物；OLD = tagRECT 字段最小可编译原形）
NEW1 = '*(DWORD *)((char *)p_m_rect + 0*4) = (DWORD)gfxMgr->NewTexture(v11);'
OLD1 = 'p_m_rect->left = (LONG)gfxMgr->NewTexture(v11);'
NEW2 = '*(DWORD *)((char *)p_m_rect + 0*4) = (DWORD)gfxMgr->NewTexture(Buffer);'
OLD2 = 'p_m_rect->left = (LONG)gfxMgr->NewTexture(Buffer);'
RAW1 = 'p_m_rect->left = gfxMgr->NewTexture(v11);'     # 生成物旧形（无补偿转换）
RAW2 = 'p_m_rect->left = gfxMgr->NewTexture(Buffer);'


def extract_tu_parts():
    """从真实生成物抽取（前言, CreateWithTextures 函数体）。"""
    src = open(GEN_CPP, encoding='utf-8').read()
    lines = src.splitlines()
    # 前言 = 到 `extern TextureLibDataBase stru_1894B78;` 为止（含头文件块）
    cut = next(i for i, l in enumerate(lines) if l.startswith('extern TextureLibDataBase stru_1894B78'))
    prologue = '\n'.join(lines[:cut + 1])
    # 函数体 = `// 0x00440810` 注释行 到 下一个 `// 0x...` 注释行
    start = next(i for i, l in enumerate(lines) if l.strip() == '// 0x00440810')
    end = next(i for i in range(start + 1, len(lines)) if re.match(r'^// 0x[0-9A-Fa-f]{6,8}\s*$', lines[i]))
    func = '\n'.join(lines[start + 1:end])
    return prologue, func


def two_forms(func):
    """函数体 → (改写前形 A, 改写后形 B)。生成物无论当前处于哪一侧都可推导。"""
    before = func
    for new, old, raw in ((NEW1, OLD1, RAW1), (NEW2, OLD2, RAW2)):
        before = before.replace(new, old).replace(raw, old)
    after = func
    for new, old, raw in ((NEW1, OLD1, RAW1), (NEW2, OLD2, RAW2)):
        after = after.replace(raw, new).replace(old, new)
    assert '*(DWORD ' not in before, 'A 形（改写前）不得含 DWORD 改写形'
    assert 'p_m_rect->left =' not in after, 'B 形（改写后）不得再有 tagRECT 字段赋值'
    assert after.count('(DWORD)') >= 2, 'B 形应含两条 (DWORD) 补偿转换'
    return before, after


def compile_func(tag, prologue, func):
    """编译单函数 TU → 该函数的机器码字节（列表，逐字节）。"""
    tu = prologue + '\n\n' + func + '\n'
    src = '/tmp/t1_equiv_%s.cpp' % tag
    obj = '/tmp/t1_equiv_%s.obj' % tag
    with open(src, 'w', encoding='utf-8') as fh:
        fh.write(tu)
    if os.path.exists(obj):
        os.remove(obj)
    out, hard = pc.run_cl(
        ['/Fo' + pc.wpath(obj), pc.wpath(src)]
        + ['/I' + pc.wpath(d) for d in pc.INCLUDE_DIRS],
        timeout=180, flags=('/nologo', '/TP', '/c', '/W3') + tuple(FLAGS))
    assert not hard, 'CL 失败（%s）: %s' % (tag, hard)
    assert os.path.exists(obj), 'CL 未产出 obj（%s）：\n%s' % (tag, out[-2000:])
    errs, _w = pc.parse_output(out)
    assert not errs, 'CL 报错（%s）：%s' % (tag, errs[:5])
    funcs = gc.parse_coff_obj(obj)
    hits = [v['bytes'] for k, v in funcs.items() if 'CreateWithTextures' in k]
    assert len(hits) == 1, '符号命中数应为 1，实得 %d（%s）' % (len(hits), sorted(funcs))
    return hits[0]


def original_bytes():
    """original/PAL3.exe 的 CreateWithTextures 字节（信息项）。"""
    data = open(EXE, 'rb').read()
    pe = int.from_bytes(data[0x3c:0x40], 'little')
    nsec = int.from_bytes(data[pe + 6:pe + 8], 'little')
    optsz = int.from_bytes(data[pe + 20:pe + 22], 'little')
    image_base = int.from_bytes(data[pe + 24 + 28:pe + 24 + 32], 'little')
    for i in range(nsec):
        off = pe + 24 + optsz + 40 * i
        va = int.from_bytes(data[off + 12:off + 16], 'little')
        rawsz = int.from_bytes(data[off + 16:off + 20], 'little')
        rawptr = int.from_bytes(data[off + 20:off + 24], 'little')
        if va <= FUNC_VA - image_base < va + rawsz:
            idx0 = (FUNC_VA - image_base) - va + rawptr
            return data[idx0:idx0 + FUNC_SIZE]
    raise AssertionError('PE 节表里找不到 VA 0x%08X' % FUNC_VA)


def main():
    prologue, func = extract_tu_parts()
    before, after = two_forms(func)
    a_bytes = compile_func('before', prologue, before)
    b_bytes = compile_func('after', prologue, after)
    print('A（改写前形）CreateWithTextures: %d 字节' % len(a_bytes))
    print('B（改写后形）CreateWithTextures: %d 字节' % len(b_bytes))
    ok = True
    if a_bytes == b_bytes:
        print('✅ A == B：改写前后编出的字节**逐位一致**（等价变换成立）')
    else:
        ok = False
        diff = [(i, x, y) for i, (x, y) in enumerate(zip(a_bytes, b_bytes)) if x != y]
        print('❌ A != B：%d 处字节差异（前 10）：%s' % (
            len(diff) + abs(len(a_bytes) - len(b_bytes)), diff[:10]))
    c_bytes = original_bytes()
    print('C（original/PAL3.exe @0x%08X）：%d 字节' % (FUNC_VA, len(c_bytes)))
    if b_bytes == list(c_bytes):
        print('✅ B == C：与原二进制逐位一致')
    else:
        same = sum(1 for x, y in zip(b_bytes, c_bytes) if x == y)
        print('ℹ️  B != C（信息项，不作判据）：同 %d/%d 字节；整 TU 编译上下文差异属已知因素'
              % (same, max(len(b_bytes), len(c_bytes))))
    print('RESULT:', 'PASS' if ok else 'FAIL')
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
