#!/usr/bin/env python3
"""形状常量的**独立**二进制佐证（不是注解文本，也不是同源 annotation）。

Task 4 的形状断言常量来自 MSVC6 探针（E-4 规则），但**规则的输入**（"这个类是多继承吗"）
来自 annotation。本脚本用两个独立于 annotation 的来源核对这个输入：

1. `original/PAL3.exe.asm`（IDA 对**二进制**的列表）里，类构造函数体内的
   `mov dword ptr [reg+OFF], offset off_X` —— 次基子对象的 **vfptr 写入**；
2. `original/PAL3.exe` 的 **.rdata 原始字节**：`off_X` 指向的内容是**代码地址**
   （⇒ 是 vtable）还是**小整数偏移**（⇒ 是 vbtable）。虚拟继承只引入 vbptr（指向 vbtable），
   多继承才引入第二张 vtable —— 这是"MI 还是虚继承"的判别点。

复现：
```sh
cd /home/peng/workspace/PAL3Decomp
python3 data/status/_layout_assert_probe_20260925/check_shape_against_binary.py
```
"""
from __future__ import annotations

import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
EXE = ROOT / 'original' / 'PAL3.exe'
ASM = ROOT / 'original' / 'PAL3.exe.asm'

# (类名, 列表里的 ctor 标签, 次基子对象偏移, 注解里的直接基数)
CASES = [
    ('CEffSParticle', 'sub_4D4EA0', 0x0C, 2),     # 注解：CEffObj@0 + CTaskTpl_...@12
    ('UIEmote', 'sub_44E530', 0x44, 2),           # 注解：UIWnd@0 + PalScriptWaitObj@68
]

_VPTR_STORE = re.compile(r'mov\s+dword ptr \[(e[a-z]{2})\+([0-9A-Fa-f]+)h\],\s*offset (off_[0-9A-Fa-f]+)')


def _pe_sections():
    d = EXE.read_bytes()
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    nsec = struct.unpack_from('<H', d, pe + 6)[0]
    sizeopt = struct.unpack_from('<H', d, pe + 20)[0]
    opt = pe + 24
    imagebase = struct.unpack_from('<I', d, opt + 28)[0]
    secs = []
    for i in range(nsec):
        o = opt + sizeopt + 40 * i
        name = d[o:o + 8].rstrip(b'\x00').decode()
        vsz, va, raw, ptr = struct.unpack_from('<IIII', d, o + 8)
        secs.append((name, va, vsz, ptr, raw))
    return d, imagebase, secs


def _read_words(d, imagebase, secs, vaddr, nbytes=16):
    rva = vaddr - imagebase
    for name, va, vsz, ptr, raw in secs:
        if va <= rva < va + max(vsz, raw):
            fo = ptr + (rva - va)
            return name, [struct.unpack_from('<I', d, fo + 4 * i)[0]
                          for i in range(nbytes // 4)]
    return None, []


def _ctor_body(label: str) -> list:
    text = ASM.read_text(encoding='utf-8', errors='replace').splitlines()
    out, inside = [], False
    for line in text:
        if re.match(r'^%s\s+proc near' % re.escape(label), line):
            inside = True
            continue
        if inside and re.match(r'^%s\s+endp' % re.escape(label), line):
            break
        if inside:
            out.append(line)
    if not out:
        raise SystemExit('未在列表里找到 %s' % label)
    return out


def main() -> int:
    if not (EXE.exists() and ASM.exists()):
        print('缺少 %s 或 %s' % (EXE, ASM), file=sys.stderr)
        return 2
    d, imagebase, secs = _pe_sections()
    print('imagebase=0x%08X sections=%s' % (imagebase, [s[0] for s in secs]))
    ok = True
    for cls, label, second_off, direct_bases in CASES:
        body = _ctor_body(label)
        stores = []
        for line in body:
            m = _VPTR_STORE.search(line)
            if m:
                stores.append((int(m.group(2), 16), m.group(3), line.strip()))
        print('\n== %s (%s) ==' % (cls, label))
        for off, sym, line in stores:
            print('   %s' % line)
        second = [(off, sym) for off, sym, _ in stores if off == second_off]
        if not second:
            print('   ✗ 未找到 +0x%X 的 vfptr 写入 ⇒ 无法证明多继承' % second_off)
            ok = False
            continue
        name, words = _read_words(d, imagebase, secs,
                                  int(second[-1][1].replace('off_', ''), 16))
        look_like_code = all(imagebase <= w < imagebase + 0x168000 for w in words)
        kind = 'vtable（内容全是代码地址）' if look_like_code else 'vbtable/其它（内容是小整数）'
        print('   ⇒ +0x%X 处写入 %s，其 .rdata 内容 = %s ⇒ %s'
              % (second_off, second[-1][1], ' '.join('%08X' % w for w in words), kind))
        verdict = look_like_code and direct_bases > 1
        print('   ⇒ 结论：该类的**二进制**继承形状 = %s（注解记 %d 个直接基）'
              % ('多继承' if verdict else '非多继承/待定', direct_bases))
        ok = ok and verdict
    print('\n%s' % ('BINARY CROSS-CHECK PASSED（形状输入 = 多继承，由二进制独立佐证）'
                    if ok else 'BINARY CROSS-CHECK FAILED'))
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())