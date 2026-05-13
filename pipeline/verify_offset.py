"""从 PAL3.exe 二进制中验证结构体字段偏移。

用法:
  python3 pipeline/verify_offset.py RoleSystem 0xCE
  python3 pipeline/verify_offset.py --global 0xC04390 SceneMgr 0xD35C

对于全局结构体实例，搜索绝对地址引用。
对于 this 指针访问，搜索 [reg+offset] 指令模式。
"""
import struct, sys, json, os, re
from collections import defaultdict

BINARY = 'original/PAL3.exe'
TEXT_VA_START = 0x401000
TEXT_VA_END = 0x5695D0
IMAGE_BASE = 0x400000

# x86 指令解码（简化版，只识别常见的内存访问模式）
def load_binary():
    with open(BINARY, 'rb') as f:
        return f.read()

def find_abs_refs(binary, target_addr):
    """搜索对绝对地址的直接引用"""
    needle = struct.pack('<I', target_addr)
    text_start = TEXT_VA_START - IMAGE_BASE
    text_end = TEXT_VA_END - IMAGE_BASE

    hits = []
    pos = text_start
    while pos < text_end:
        idx = binary.find(needle, pos, text_end)
        if idx == -1:
            break
        va = idx + IMAGE_BASE
        # 前 6 字节 + 后 4 字节
        pre = binary[max(0, idx-6):idx]
        post = binary[idx+4:idx+8]

        # 解码指令类型
        insn = decode_mem_instruction(pre, target_addr, post)
        hits.append({'va': va, 'pre': pre.hex(), 'post': post.hex(), 'insn': insn})
        pos = idx + 1
    return hits

def decode_mem_instruction(pre, addr, post):
    """简化 x86 内存访问指令解码"""
    if len(pre) < 1:
        return 'unknown'

    # mov eax, [addr] — A1
    if pre[-1:] == b'\xa1':
        return 'load eax <- [addr]'
    # mov [addr], eax — A3
    if pre[-1:] == b'\xa3':
        return 'store [addr] <- eax'

    if len(pre) >= 2:
        op2 = pre[-2:]
        # mov [addr], imm32 — C7 05
        if op2 == b'\xc7\x05':
            imm = struct.unpack('<I', post[:4])[0] if len(post) >= 4 else '?'
            return f'store [addr] <- imm32({imm})'
        # mov reg, [addr] — 8B xx
        if op2[0] == 0x8B:
            regs = ['eax','ecx','edx','ebx','esp','ebp','esi','edi']
            reg = regs[(op2[1] >> 3) & 7] if op2[1] & 0xC7 == 0x05 else '?'
            return f'load {reg} <- [addr]'
        # mov [addr], reg — 89 xx
        if op2[0] == 0x89:
            regs = ['eax','ecx','edx','ebx','esp','ebp','esi','edi']
            reg = regs[(op2[1] >> 3) & 7] if op2[1] & 0xC7 == 0x05 else '?'
            return f'store [addr] <- {reg}'
        # fld [addr] — D9 05
        if op2 == b'\xd9\x05':
            return 'fld float [addr]'
        # fstp [addr] — D9 1D
        if op2 == b'\xd9\x1d':
            return 'fstp float [addr]'
        # fld qword [addr] — DD 05
        if op2 == b'\xdd\x05':
            return 'fld double [addr]'
        # cmp [addr], ... — 83 3D
        if op2 == b'\x83\x3d':
            return f'cmp [addr], imm8'
        # push [addr] — FF 35
        if op2 == b'\xff\x35':
            return 'push [addr]'
        # cmp reg, [addr] — 3B xx
        if op2[0] == 0x3B:
            return 'cmp reg, [addr]'
        # movzx — 0F B6/B7
        if op2 == b'\x0f\xb6' or (len(pre) >= 3 and pre[-3:-1] == b'\x0f\xb6'):
            return 'movzx byte [addr]'
        if op2 == b'\x0f\xb7' or (len(pre) >= 3 and pre[-3:-1] == b'\x0f\xb7'):
            return 'movzx word [addr]'

    return f'other(pre={pre[-2:].hex()})'

def infer_access_width(insn):
    """从指令推断访问宽度"""
    if 'float' in insn or 'fld' in insn or 'fstp' in insn:
        return 4  # float
    if 'double' in insn:
        return 8
    if 'byte' in insn or 'movzx byte' in insn:
        return 1
    if 'word' in insn or 'movzx word' in insn:
        return 2
    if 'eax' in insn or 'ecx' in insn or 'edx' in insn or 'ebx' in insn or 'esi' in insn or 'edi' in insn:
        return 4
    if 'imm32' in insn:
        return 4
    if 'imm8' in insn:
        return 4  # cmp dword, imm8 still accesses 4 bytes
    return 0  # unknown

def main():
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)

    binary = load_binary()

    if sys.argv[1] == '--global':
        # 验证全局结构体实例的字段
        base_addr = int(sys.argv[2], 16)
        struct_name = sys.argv[3]
        field_offset = int(sys.argv[4], 16)
        abs_addr = base_addr + field_offset

        print(f"=== {struct_name}+{hex(field_offset)} (abs: {hex(abs_addr)}) ===")
        hits = find_abs_refs(binary, abs_addr)
        print(f"直接引用: {len(hits)} 处")

        widths = []
        for h in hits:
            w = infer_access_width(h['insn'])
            widths.append(w)
            print(f"  {hex(h['va'])}: {h['insn']} (width={w})")

        if widths:
            common_width = max(set(widths), key=widths.count)
            print(f"\n推断类型宽度: {common_width} bytes")
            print(f"偏移对齐: {field_offset} % {common_width} = {field_offset % common_width if common_width > 0 else '?'}")
    else:
        # 验证结构体内的偏移（通用，搜索所有全局实例）
        struct_name = sys.argv[1]
        field_offset = int(sys.argv[2], 16)

        # 从 globals.json 找此结构体的全局实例
        globs = json.load(open('pipeline/data/annotations/globals.json'))
        instances = []
        for addr, g in globs.items():
            if g.get('type', '').replace('struct ', '').replace('class ', '') == struct_name:
                instances.append((int(addr, 16), g['name']))

        if not instances:
            print(f"未找到 {struct_name} 的全局实例，请用 --global 指定基址")
            sys.exit(1)

        for base, gname in instances:
            abs_addr = base + field_offset
            print(f"=== {gname} ({struct_name}) + {hex(field_offset)} = {hex(abs_addr)} ===")
            hits = find_abs_refs(binary, abs_addr)
            print(f"直接引用: {len(hits)} 处")
            for h in hits:
                w = infer_access_width(h['insn'])
                print(f"  {hex(h['va'])}: {h['insn']} (width={w})")
            print()

if __name__ == '__main__':
    main()
