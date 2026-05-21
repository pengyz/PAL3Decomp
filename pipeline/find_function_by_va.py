#!/usr/bin/env python3
"""
通过回溯找到包含给定 VA 的函数起始位置
查找函数序言模式（push ebp; mov ebp, esp）
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


def find_function_start(va: int, max_backward: int = 0x1000) -> int:
    """回溯查找函数起始（函数序言）"""
    # 常见函数序言模式:
    # 55           push ebp
    # 8B EC        mov ebp, esp
    # 或:
    # 55           push ebp
    # 89 E5        mov ebp, esp
    # 或:
    # 56           push esi
    # 57           push edi
    # 53           push ebx

    # 从 VA 向前扫描
    for offset in range(0, max_backward, 1):
        test_va = va - offset

        if test_va < 0x401000:  # .text 段开始
            break

        code = read_bytes(test_va, 6)

        # 模式 1: 55 8B EC (push ebp; mov ebp, esp)
        if code[0] == 0x55 and code[1] == 0x8B and code[2] == 0xEC:
            return test_va

        # 模式 2: 55 89 E5 (push ebp; mov ebp, esp)
        if code[0] == 0x55 and code[1] == 0x89 and code[2] == 0xE5:
            return test_va

        # 模式 3: 56 57 (push esi; push edi) - 常见于无帧指针优化
        if code[0] == 0x56 and code[1] == 0x57:
            return test_va

        # 模式 4: 53 56 57 (push ebx; push esi; push edi)
        if code[0] == 0x53 and code[1] == 0x56 and code[2] == 0x57:
            return test_va

    return None


def analyze_function_context(va: int):
    """分析包含 VA 的函数上下文"""
    func_start = find_function_start(va, max_backward=0x2000)

    if not func_start:
        print(f'  ✗ 未找到函数起始 (回溯 8KB)')
        return None

    print(f'  ✓ 函数起始: 0x{func_start:X}')
    print(f'  ✓ VA 在函数内偏移: +0x{va - func_start:X}')

    # 读取函数头部
    prologue = read_bytes(func_start, 20)
    print(f'  序言: {prologue.hex().upper()}')

    # 检查是否有 this 指针加载（ecx → esi/edi/ebx）
    # 常见模式: 8B F1 (mov esi, ecx) / 8B F9 (mov edi, ecx)
    if b'\x8B\xF1' in prologue:
        print(f'  ✓ 发现 mov esi, ecx (this → esi)')
    elif b'\x8B\xF9' in prologue:
        print(f'  ✓ 发现 mov edi, ecx (this → edi)')
    elif b'\x8B\xD9' in prologue:
        print(f'  ✓ 发现 mov ebx, ecx (this → ebx)')
    elif b'\x8B\xC1' in prologue:
        print(f'  ✓ 发现 mov eax, ecx (this → eax)')

    # 读取 VA 附近的指令
    context_code = read_bytes(va - 10, 30)
    print(f'  上下文: {context_code.hex().upper()}')

    return {
        'function_start': func_start,
        'offset_in_function': va - func_start,
    }


def main():
    print('查找 CCBUI offset 156/180 访问所在的函数\n')
    print('=' * 80)

    vas = [
        (0x518827, 156, 'fild dword [eax+0x9C]', 'eax'),
        (0x441937, 180, 'fild dword [esi+0xB4]', 'esi'),
    ]

    for va, offset, instruction, base_reg in vas:
        print(f'\nOffset {offset} (VA=0x{va:X}):')
        print(f'  指令: {instruction}')
        print(f'  Base: {base_reg}')
        print()

        func_info = analyze_function_context(va)

        if func_info:
            print()
            print(f'  → 函数范围: 0x{func_info["function_start"]:X} + ...')
            print(f'  → 需要在 IDA 中查看函数 0x{func_info["function_start"]:X} 的类归属')

        print('\n' + '-' * 80)

    print('\n\n下一步:')
    print('  1. 在 IDA 中定位这两个函数（上面列出的函数起始地址）')
    print('  2. 查看函数名/注释，确认是否属于 CCBUI 类')
    print('  3. 检查 vtable 或者 xrefs 来确认类归属')


if __name__ == '__main__':
    main()
