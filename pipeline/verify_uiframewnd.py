#!/usr/bin/env python3
"""
验证 UIFrameWnd offset 68 和 148 的字段定义
PAL3patch: offset 68 = char[80] szframe, offset 148 = int m_frameid
Ours:      offset 68 缺失,              offset 148 = float m_nBorderStyle
"""
import struct
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
EXE_PATH = PROJECT_ROOT / 'original/PAL3.exe'


def read_bytes(va: int, length: int) -> bytes:
    """从 PAL3.exe 读取字节"""
    with open(EXE_PATH, 'rb') as f:
        file_offset = va - 0x400000
        f.seek(file_offset)
        return f.read(length)


def scan_string_operations(start_va: int, end_va: int, target_offset: int) -> list:
    """扫描字符串操作指令（strcpy, memcpy, lea 等）"""
    # 搜索 LEA reg, [reg+offset] 模式（加载字符串缓冲区地址）
    results = []

    # 简化实现：扫描 .text 段查找 LEA 指令
    # LEA reg, [reg+disp32] = 8D XX [XX XX XX XX]
    text_start = 0x401000
    text_end = 0x600000
    scan_size = min(0x1000, end_va - start_va) if end_va > start_va else 0x10000

    with open(EXE_PATH, 'rb') as f:
        f.seek(start_va - 0x400000)
        code = f.read(scan_size)

    offset_bytes = struct.pack('<I', target_offset)

    # 查找包含目标 offset 的指令
    pos = 0
    while pos < len(code) - 6:
        if code[pos:pos+4] == offset_bytes:
            # 回溯看是否是 LEA/MOV 指令
            if pos >= 2:
                if code[pos-2] == 0x8D:  # LEA
                    va = start_va + pos - 2
                    results.append({
                        'va': hex(va),
                        'instruction': 'lea',
                        'offset': target_offset,
                        'bytes': code[pos-2:pos+6].hex().upper(),
                    })
        pos += 1

    return results


def check_offset_148_type():
    """验证 offset 148 是 int 还是 float"""
    print('验证 UIFrameWnd offset 148 类型')
    print('=' * 70)

    # 搜索访问 offset 148 (0x94) 的指令
    # 如果是 float：应该有 fld/fst (D9/DD)
    # 如果是 int：应该有 mov (8B/89)

    target_offset = 148
    offset_bytes = struct.pack('<I', target_offset)

    with open(EXE_PATH, 'rb') as f:
        # 扫描 .text 段
        f.seek(0x1000)  # .text start
        code = f.read(0x200000)  # ~2MB

    float_accesses = []
    int_accesses = []

    pos = 0
    while pos < len(code) - 6:
        if code[pos:pos+4] == offset_bytes:
            # 检查前面的指令
            if pos >= 2:
                op = code[pos-2]
                modrm = code[pos-1]

                if op in [0xD9, 0xDD, 0xDB]:  # FPU
                    float_accesses.append({
                        'va': hex(0x401000 + pos - 2),
                        'bytes': code[pos-2:pos+6].hex().upper(),
                    })
                elif op in [0x8B, 0x89, 0xC7]:  # MOV/MOV/MOV imm
                    int_accesses.append({
                        'va': hex(0x401000 + pos - 2),
                        'bytes': code[pos-2:pos+6].hex().upper(),
                    })

        pos += 1

    print(f'\nFloat 访问 (FPU 指令): {len(float_accesses)} 次')
    for acc in float_accesses[:5]:
        print(f'  {acc["va"]}: {acc["bytes"]}')

    print(f'\nInt 访问 (MOV 指令): {len(int_accesses)} 次')
    for acc in int_accesses[:5]:
        print(f'  {acc["va"]}: {acc["bytes"]}')

    if float_accesses and not int_accesses:
        print('\n→ 结论: offset 148 是 **float** (我们的定义正确)')
    elif int_accesses and not float_accesses:
        print('\n→ 结论: offset 148 是 **int** (PAL3patch 定义正确)')
    elif float_accesses and int_accesses:
        print(f'\n→ 结论: 混合访问 (float:{len(float_accesses)}, int:{len(int_accesses)})')
    else:
        print('\n→ 未找到明确访问')


def check_offset_68_is_string():
    """验证 offset 68 是否是 char[80] 字符串缓冲区"""
    print('\n\n验证 UIFrameWnd offset 68 是否是 char[80] szframe')
    print('=' * 70)

    target_offset = 68
    offset_bytes = struct.pack('<I', target_offset)

    with open(EXE_PATH, 'rb') as f:
        f.seek(0x1000)
        code = f.read(0x200000)

    # 查找 LEA 指令（加载字符串缓冲区地址）
    lea_count = 0
    strcpy_patterns = []

    pos = 0
    while pos < len(code) - 10:
        if code[pos:pos+4] == offset_bytes:
            if pos >= 2 and code[pos-2] == 0x8D:  # LEA
                lea_count += 1
                va = 0x401000 + pos - 2

                # 检查后续是否有 push + call strcpy/sprintf 模式
                next_20 = code[pos+4:pos+24]
                if b'\x50' in next_20:  # push eax/ecx/...
                    strcpy_patterns.append({
                        'va': hex(va),
                        'bytes': code[pos-2:pos+10].hex().upper(),
                    })

        pos += 1

    print(f'\nLEA [reg+0x44] 指令数: {lea_count}')
    print(f'疑似字符串操作模式: {len(strcpy_patterns)}')

    if strcpy_patterns:
        print('\n示例 (LEA + push/call 模式):')
        for pattern in strcpy_patterns[:3]:
            print(f'  {pattern["va"]}: {pattern["bytes"]}')

    if lea_count > 0:
        print('\n→ 结论: offset 68 很可能是字符串缓冲区 (PAL3patch 定义合理)')
        print('  char[80] 用于存储帧纹理路径 (szframe)')
    else:
        print('\n→ 结论: offset 68 未见明确字符串操作，需要更多证据')


def main():
    print('UIFrameWnd 字段验证\n')

    check_offset_148_type()
    check_offset_68_is_string()

    print('\n\n' + '=' * 70)
    print('总结:')
    print('  1. 运行上述分析')
    print('  2. 根据 float/int 访问比例判断 offset 148 类型')
    print('  3. 根据 LEA 使用判断 offset 68 是否是字符串缓冲区')
    print('  4. 如果 PAL3patch 定义准确，可以导入')


if __name__ == '__main__':
    main()
