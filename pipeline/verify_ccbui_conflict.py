#!/usr/bin/env python3
"""
验证 CCBUI offset 156, 180 的 A 级证据是否真的访问 CCBUI
"""
import struct
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
EXE_PATH = PROJECT_ROOT / 'original/PAL3.exe'

# 从 annotations 中声称有 A 级证据的字段
EVIDENCE_TO_VERIFY = [
    {
        'offset': 156,
        'name': 'm_nTargetHeight',
        'type': 'float',
        'evidence': 'A:FPU_disp32_0x518827',
        'va': 0x518827,
    },
    {
        'offset': 180,
        'name': 'm_nWindowY',
        'type': 'float',
        'evidence': 'A:FPU_disp32_0x441937',
        'va': 0x441937,
    },
    {
        'offset': 176,
        'name': 'm_nWindowX',
        'type': 'int',
        'evidence': 'binary:SetSelection',
        'va': None,  # 没有具体 VA
    },
]


def read_instruction(va: int, length: int = 20) -> bytes:
    """从 PAL3.exe 读取指令字节"""
    with open(EXE_PATH, 'rb') as f:
        # VA to file offset: VA - 0x400000
        file_offset = va - 0x400000
        f.seek(file_offset)
        return f.read(length)


def disasm_fpu_instruction(code: bytes) -> str:
    """简单解析 FPU 指令（检查是否是 disp32 访问）"""
    if len(code) < 6:
        return 'too short'

    # FPU 指令模式: D9/DB/DD xx [mod=10, reg, rm] disp32
    # D9 86 [disp32] = fld dword [esi+disp32]
    # DB 86 [disp32] = fild dword [esi+disp32] (整数→浮点)
    # DD 86 [disp32] = fld qword [esi+disp32] (double)

    if code[0] in [0xD9, 0xDB, 0xDD]:
        modrm = code[1]
        mod = (modrm >> 6) & 0x3
        reg = (modrm >> 3) & 0x7
        rm = modrm & 0x7

        if mod == 0b10:  # disp32
            disp32 = struct.unpack('<I', code[2:6])[0]

            # 解析 rm 字段（base register）
            base_reg = ['eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi'][rm]

            # 解析指令类型
            if code[0] == 0xD9:
                size = 'dword'
                if reg == 0:
                    op = 'fld'
                elif reg == 2:
                    op = 'fst'
                elif reg == 3:
                    op = 'fstp'
                else:
                    op = f'd9_{reg}'
            elif code[0] == 0xDB:
                size = 'dword'
                if reg == 0:
                    op = 'fild'  # 整数→浮点
                elif reg == 2:
                    op = 'fist'
                elif reg == 3:
                    op = 'fistp'
                else:
                    op = f'db_{reg}'
            elif code[0] == 0xDD:
                size = 'qword'
                if reg == 0:
                    op = 'fld'
                elif reg == 2:
                    op = 'fst'
                elif reg == 3:
                    op = 'fstp'
                else:
                    op = f'dd_{reg}'

            return f'{op} {size} [{base_reg}+0x{disp32:X}]'

    return 'unknown'


def main():
    print('验证 CCBUI 冲突字段的 A 级证据\n')
    print('=' * 80)

    for evidence in EVIDENCE_TO_VERIFY:
        if evidence['va'] is None:
            print(f"\n{evidence['offset']:4d}: {evidence['name']} — 无具体 VA，跳过")
            continue

        print(f"\n{evidence['offset']:4d}: {evidence['name']} ({evidence['type']})")
        print(f"  Evidence: {evidence['evidence']}")
        print(f"  VA: 0x{evidence['va']:X}")

        # 读取指令
        code = read_instruction(evidence['va'])
        print(f"  Bytes: {code[:10].hex().upper()}")

        # 解析指令
        disasm = disasm_fpu_instruction(code)
        print(f"  Disasm: {disasm}")

        # 提取 disp32
        if code[0] in [0xD9, 0xDB, 0xDD] and ((code[1] >> 6) & 0x3) == 0b10:
            disp32 = struct.unpack('<I', code[2:6])[0]
            modrm = code[1]
            rm = modrm & 0x7
            base_reg = ['eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi'][rm]

            print(f"  Disp32: 0x{disp32:X} = {disp32}")
            print(f"  Base: {base_reg}")

            if disp32 == evidence['offset']:
                print(f"  ✓ disp32 匹配 offset {evidence['offset']}")
                print(f"    → 需要确认 {base_reg} 是否指向 CCBUI this 指针")
            else:
                print(f"  ✗ disp32 不匹配! ({disp32} != {evidence['offset']})")
                print(f"    → offset {evidence['offset']} 的证据记录有误")
        else:
            print(f"  ⚠ 不是 FPU disp32 指令")

    print('\n' + '=' * 80)
    print('\n结论:')
    print('  1. 如果 disp32 匹配，说明我们的 offset 正确')
    print('  2. 如果 disp32 不匹配，说明：')
    print('     a) 证据记录错误（VA 或 offset 搞混了）')
    print('     b) 访问的不是 CCBUI 对象（this 指针推断错误）')
    print('  3. 如果是 b)，则 PAL3patch 的偏移可能是正确的')


if __name__ == '__main__':
    main()
