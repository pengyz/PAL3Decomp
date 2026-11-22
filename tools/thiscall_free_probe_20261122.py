#!/usr/bin/env python3
"""[__thiscall 自由函数归属考证 2026-11-22] check 警告 __thiscall×13 批量取证。

每条: ①函数头 this(ecx) 使用的偏移域 ②全部调用点 ecx 来源形态(全局单例/
局部对象/数组元素) ③归属判定素材(thiscall 成员 vs free helper)。
"""
import struct
import capstone

EXE = '/home/peng/workspace/PAL3Decomp/original/PAL3.exe'
IMAGE_BASE = 0x400000

TARGETS = [
    (0x00422950, 'LoadScene'),
    (0x00538260, 'ClearModelFlag'),
    (0x00446030, 'AddToArray'),
    (0x00523cb0, 'Method_3CB0'),
    (0x0043fd90, 'SetFrameIndex'),
    (0x0043fdb0, 'SetFrameCount'),
    (0x00445bf0, 'SetArrayElement'),
    (0x0044f130, 'InitUIComponents'),
    (0x0045add0, 'InitState'),
    (0x0047f590, 'ProcessTree'),
    (0x004ab560, 'Method_B560'),
    (0x004c4b00, 'SetValue'),
    (0x005306a0, 'Initialize_06A0'),
]


def load():
    d = open(EXE, 'rb').read()
    e = struct.unpack_from('<I', d, 0x3C)[0]
    opt = struct.unpack_from('<H', d, e + 20)[0]
    sec0 = e + 24 + opt
    nsec = struct.unpack_from('<H', d, e + 6)[0]
    secs = {}
    for i in range(nsec):
        s = sec0 + 40 * i
        nm = d[s:s + 8].rstrip(b'\0').decode()
        vs, va, rs, ra = struct.unpack_from('<IIII', d, s + 8)
        secs[nm] = (va + IMAGE_BASE, d[ra:ra + rs])
    return d, secs


def main():
    d, secs = load()
    text_va, text = secs['.text']
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    for tgt, nm in TARGETS:
        # ①函数头 0x60 字节: this(ecx) 使用偏移域
        off = tgt - text_va
        this_offs = set()
        ins_count = 0
        end_va = 0
        for ins in md.disasm(text[off:off + 0x60], tgt):
            ins_count += 1
            end_va = ins.address + ins.size
            # this 通常先被缓存: mov e?X, ecx → 后续 [reg+off]
            m = ins.op_str
            if ', ecx' in m and ins.mnemonic == 'mov':
                pass
        # 取 this 域: 找首条 mov reg, ecx 之后的 [reg+imm] 访问
        this_reg = None
        head_lines = []
        for ins in md.disasm(text[off:off + 0x50], tgt):
            head_lines.append('  0x%08X %-6s %s' % (ins.address, ins.mnemonic, ins.op_str))
            if len(head_lines) >= 14:
                break
        # ②调用点
        callers = []
        for o in range(len(text) - 5):
            if text[o] == 0xE8:
                rel = int.from_bytes(text[o + 1:o + 5], 'little', signed=True)
                if text_va + o + 5 + rel == tgt and len(callers) < 8:
                    callers.append(text_va + o)
        print('== %s @0x%08X (%d 个可见调用点) ==' % (nm, tgt, len(callers)))
        for ln in head_lines:
            print(ln)
        ecx_srcs = []
        for c in callers:
            o = c - 16 - text_va
            frag = []
            for ins in md.disasm(text[o:c + 1], c - 16):
                frag.append('%s %s' % (ins.mnemonic, ins.op_str))
                if ins.address >= c - 1:
                    break
            ecx_srcs.append(' | '.join(frag[-3:]))
        for s in ecx_srcs[:5]:
            print('   caller: %s' % s)
        print()


if __name__ == '__main__':
    main()
