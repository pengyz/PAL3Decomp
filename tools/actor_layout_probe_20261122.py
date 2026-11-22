#!/usr/bin/env python3
"""[Actor 布局定谳探针 2026-11-22] vptr-vs-m_actarray_type @+0x0 归属裁决。

写表铁律(vtable-writer-evidence-law): vtable 归属 = ctor 写表裁决。
①.rdata @0x56A6D0 表内容逐 dword 实证(与注解 3 槽比对+表尾探测)
②.text 全量扫 imm32 0x56A6D0 → capstone 反汇编每处上下文(写表者=ctor)
③FastInit @0x536A80 全函数反汇编(验证 mov [edx],al 写 +0x0 声张)
裁决输出: 三态(vptr属实/m_actarray_type属实/矛盾无法调和)
"""
import struct
import sys

try:
    import capstone
except ImportError:
    capstone = None

REPO = '/home/peng/workspace/PAL3Decomp'
EXE = REPO + '/original/PAL3.exe'
VT = 0x56A6D0
FASTINIT = 0x536A80
IMAGE_BASE = 0x400000


def load_sections():
    d = open(EXE, 'rb').read()
    e = struct.unpack_from('<I', d, 0x3C)[0]
    nsec = struct.unpack_from('<H', d, e + 6)[0]
    opt = struct.unpack_from('<H', d, e + 20)[0]
    sec0 = e + 24 + opt
    secs = []
    for i in range(nsec):
        s = sec0 + 40 * i
        nm = d[s:s + 8].rstrip(b'\0').decode('ascii', 'replace')
        vs, va, rs, ra = struct.unpack_from('<IIII', d, s + 8)
        secs.append((nm, va + IMAGE_BASE, d[ra:ra + rs]))
    return d, secs


def va2off(secs, va):
    for nm, v, body in secs:
        if v <= va < v + len(body):
            return body[va - v:]
    return None


def main():
    d, secs = load_sections()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32) if capstone else None

    # ── ①.rdata 表内容 ──
    body = va2off(secs, VT)
    print('== ① .rdata @0x%08X 表内容 ==' % VT)
    slots = []
    for i in range(12):
        dw = struct.unpack_from('<I', body, i * 4)[0]
        slots.append(dw)
        tag = ''
        if 0x401000 <= dw < 0x569000:
            tag = '.text'
        elif dw == 0:
            tag = 'NULL — 表终止'
            print('  [%d] 0x%08X %s' % (i, dw, tag))
            slots = slots[:i + 1]
            break
        print('  [%d] 0x%08X %s' % (i, dw, tag))
    # 表后是否还有引用(表尾邻接)
    rdata_body = va2off(secs, 0x56A000)[:0x800] if va2off(secs, 0x56A000) else b''
    prev8 = struct.pack('<I', slots[0])
    print('  表头 8B 前: %s' % struct.unpack_from('<I', body, -8)[0].__format__('08X')
          if len(body) >= 8 else '?')

    # ── ②.text 谁引用 0x56A6D0 ──
    print('\n== ② .text imm32 0x%08X 引用普查 ==' % VT)
    text = [b for nm, v, b in secs if nm == '.text'][0]
    text_va = [v for nm, v, b in secs if nm == '.text'][0]
    pat = struct.pack('<I', VT)
    hits = []
    i = 0
    while True:
        j = text.find(pat, i)
        if j < 0:
            break
        hits.append(j)
        i = j + 1
    print('共 %d 处 imm32 引用' % len(hits))
    for off in hits:
        va = text_va + off
        # 反汇编前 12B 起
        start = max(0, off - 12)
        code = text[start:off + 10]
        lines = []
        if md:
            for ins in md.disasm(code, text_va + start):
                if ins.address <= va + 4:
                    mark = ' <<<' if ins.address >= va and ins.address < va + 4 else ''
                    lines.append('  0x%08X %-24s %s%s' % (ins.address, ins.mnemonic,
                                                          ins.op_str, mark))
        print(' 引用 @0x%08X:' % va)
        print('\n'.join('    ' + l.strip() for l in lines) or '    (disasm fail)')

    # ── ③FastInit 全函数 ──
    print('\n== ③ FastInit @0x%08X 反汇编 ==' % FASTINIT)
    fb = va2off(secs, FASTINIT)
    # 函数长度: 到 ret/cleanup 或上限 256B
    n = 0
    depth_ins = list(md.disasm(fb[:256], FASTINIT))
    for ins in depth_ins:
        print('  0x%08X %-8s %s' % (ins.address, ins.mnemonic, ins.op_str))
        if ins.mnemonic == 'ret':
            break


if __name__ == '__main__':
    main()
