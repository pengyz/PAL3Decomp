#!/usr/bin/env python3
"""
系统性扫描类的所有方法，提取 member access 模式
用于验证结构体布局的完整性
"""
import json
import struct
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
EXE_PATH = PROJECT_ROOT / 'original/PAL3.exe'
FUNCTIONS_FILE = PROJECT_ROOT / 'data/annotations/functions.json'


def read_bytes(va: int, length: int) -> bytes:
    """从 PAL3.exe 读取字节"""
    with open(EXE_PATH, 'rb') as f:
        file_offset = va - 0x400000
        f.seek(file_offset)
        return f.read(length)



def parse_displacement(code, i, mod, this_idx, rm):
    """解析 displacement 字段，返回 (disp_value, instruction_length) 或 None"""
    if rm != this_idx:
        return None
    
    if mod == 2:  # disp32
        disp = struct.unpack('<i', code[i+2:i+6])[0]
        return (disp, 6)
    elif mod == 1:  # disp8
        disp = struct.unpack('<b', code[i+2:i+3])[0]
        return (disp, 3)
    else:
        return None

def find_this_register(func_va: int) -> str:
    """在函数序言中找到 this 指针保存的寄存器"""
    # 读取函数头部
    code = read_bytes(func_va, 50)

    # 查找 mov reg, ecx 模式
    # 8B F1 = mov esi, ecx
    # 8B F9 = mov edi, ecx
    # 8B D9 = mov ebx, ecx
    # 8B C1 = mov eax, ecx

    for i in range(min(30, len(code) - 1)):
        if code[i] == 0x8B:
            modrm = code[i + 1]
            if modrm == 0xF1:
                return 'esi'
            elif modrm == 0xF9:
                return 'edi'
            elif modrm == 0xD9:
                return 'ebx'
            elif modrm == 0xC1:
                return 'eax'

    # 如果没找到 mov reg, ecx，默认返回 ecx（直接使用 this）
    # 这种情况常见于小函数，不需要保存 this 到其他寄存器
    return 'ecx'


def scan_member_accesses(func_va: int, func_size: int, this_reg: str) -> list:
    """扫描函数中所有对 this->member 的访问"""
    if func_size == 0:
        func_size = 0x1000  # 默认最大扫描 4KB

    code = read_bytes(func_va, min(func_size, 0x2000))

    # 寄存器编码
    reg_map = {
        'eax': 0, 'ecx': 1, 'edx': 2, 'ebx': 3,
        'esp': 4, 'ebp': 5, 'esi': 6, 'edi': 7
    }

    if this_reg not in reg_map:
        return []

    this_idx = reg_map[this_reg]

    accesses = []
    i = 0

    while i < len(code) - 6:
        va = func_va + i
        opcode = code[i]

        # 检查常见访问模式
        # mov [reg+disp32], ...
        # mov ..., [reg+disp32]
        # fld/fstp/fild/fistp [reg+disp32]
        # lea reg, [reg+disp32]

        access_type = None
        access_width = None

        # MOV instructions (8B/89)
        if opcode == 0x8B or opcode == 0x89:
            modrm = code[i + 1]
            mod = (modrm >> 6) & 3
            reg = (modrm >> 3) & 7
            rm = modrm & 7

            if mod == 2 and rm == this_idx:  # [this_reg+disp32]
                disp = struct.unpack('<i', code[i+2:i+6])[0]
                access_type = 'store' if opcode == 0x89 else 'load'
                access_width = 4
                accesses.append({
                    'va': va,
                    'offset': disp,
                    'type': access_type,
                    'width': access_width,
                    'instruction': code[i:i+6].hex().upper()
                })
                i += 6
                continue
            elif mod == 1 and rm == this_idx:  # [this_reg+disp8]
                disp = struct.unpack('<b', code[i+2:i+3])[0]  # signed byte
                if disp >= 0:  # 只记录正偏移
                    access_type = 'store' if opcode == 0x89 else 'load'
                    access_width = 4
                    accesses.append({
                        'va': va,
                        'offset': disp,
                        'type': access_type,
                        'width': access_width,
                        'instruction': code[i:i+3].hex().upper()
                    })
                i += 3
                continue

        # MOVZX byte (0F B6)
        elif opcode == 0x0F and i + 7 < len(code) and code[i+1] == 0xB6:
            modrm = code[i + 2]
            mod = (modrm >> 6) & 3
            rm = modrm & 7

            if mod == 2 and rm == this_idx:
                disp = struct.unpack('<i', code[i+3:i+7])[0]
                accesses.append({
                    'va': va,
                    'offset': disp,
                    'type': 'load_byte',
                    'width': 1,
                    'instruction': code[i:i+7].hex().upper()
                })
                i += 7
                continue
            elif mod == 1 and rm == this_idx:
                disp = struct.unpack('<b', code[i+3:i+4])[0]
                if disp >= 0:
                    accesses.append({
                        'va': va,
                        'offset': disp,
                        'type': 'load_byte',
                        'width': 1,
                        'instruction': code[i:i+4].hex().upper()
                    })
                i += 4
                continue

        # MOV byte (C6/88/8A)
        elif opcode == 0xC6 or opcode == 0x88 or opcode == 0x8A:
            modrm = code[i + 1]
            mod = (modrm >> 6) & 3
            rm = modrm & 7

            if mod == 2 and rm == this_idx:
                disp = struct.unpack('<i', code[i+2:i+6])[0]
                access_type = 'store_byte' if opcode in [0xC6, 0x88] else 'load_byte'
                accesses.append({
                    'va': va,
                    'offset': disp,
                    'type': access_type,
                    'width': 1,
                    'instruction': code[i:i+6].hex().upper()
                })
                i += 6
                continue
            elif mod == 1 and rm == this_idx:
                disp = struct.unpack('<b', code[i+2:i+3])[0]
                if disp >= 0:
                    access_type = 'store_byte' if opcode in [0xC6, 0x88] else 'load_byte'
                    accesses.append({
                        'va': va,
                        'offset': disp,
                        'type': access_type,
                        'width': 1,
                        'instruction': code[i:i+3].hex().upper()
                    })
                i += 3
                continue

        # FPU instructions (D9/DB/DD)
        elif opcode in [0xD9, 0xDB, 0xDD]:
            modrm = code[i + 1]
            mod = (modrm >> 6) & 3
            rm = modrm & 7

            if mod == 2 and rm == this_idx:
                disp = struct.unpack('<i', code[i+2:i+6])[0]

                # D9 = fld/fst float (4 bytes)
                # DB = fild/fistp int (4 bytes) or fld/fstp extended
                # DD = fld/fst double (8 bytes)

                if opcode == 0xD9:
                    access_type = 'fld_float'
                    access_width = 4
                elif opcode == 0xDB:
                    # 需要看 ModR/M 的 reg 字段区分 fild vs fld
                    reg_field = (modrm >> 3) & 7
                    if reg_field == 0:  # fild
                        access_type = 'fild_int'
                        access_width = 4
                    else:
                        access_type = 'fld_unknown'
                        access_width = 4
                elif opcode == 0xDD:
                    access_type = 'fld_double'
                    access_width = 8

                accesses.append({
                    'va': va,
                    'offset': disp,
                    'type': access_type,
                    'width': access_width,
                    'instruction': code[i:i+6].hex().upper()
                })
                i += 6
                continue
            elif mod == 1 and rm == this_idx:
                disp = struct.unpack('<b', code[i+2:i+3])[0]
                if disp >= 0:
                    if opcode == 0xD9:
                        access_type = 'fld_float'
                        access_width = 4
                    elif opcode == 0xDB:
                        reg_field = (modrm >> 3) & 7
                        if reg_field == 0:
                            access_type = 'fild_int'
                            access_width = 4
                        else:
                            access_type = 'fld_unknown'
                            access_width = 4
                    elif opcode == 0xDD:
                        access_type = 'fld_double'
                        access_width = 8
                    accesses.append({
                        'va': va,
                        'offset': disp,
                        'type': access_type,
                        'width': access_width,
                        'instruction': code[i:i+3].hex().upper()
                    })
                i += 3
                continue


        # LEA (8D)
        elif opcode == 0x8D:
            modrm = code[i + 1]
            mod = (modrm >> 6) & 3
            rm = modrm & 7

            if mod == 2 and rm == this_idx:
                disp = struct.unpack('<i', code[i+2:i+6])[0]
                accesses.append({
                    'va': va,
                    'offset': disp,
                    'type': 'lea',
                    'width': 0,  # LEA 不访问内存
                    'instruction': code[i:i+6].hex().upper()
                })
                i += 6
                continue
            elif mod == 1 and rm == this_idx:
                disp = struct.unpack('<b', code[i+2:i+3])[0]
                if disp >= 0:
                    accesses.append({
                        'va': va,
                        'offset': disp,
                        'type': 'lea',
                        'width': 0,
                        'instruction': code[i:i+3].hex().upper()
                    })
                i += 3
                continue

        i += 1

    return accesses


def scan_class_methods(class_name: str):
    """扫描指定类的所有方法"""
    with open(FUNCTIONS_FILE) as f:
        functions = json.load(f)

    # 收集该类的所有方法
    methods = []
    for addr_str, func_info in functions.items():
        func_name = func_info.get('name', '')
        if func_name.startswith(f'{class_name}::'):
            addr = int(addr_str, 16)
            size = func_info.get('size', 0)
            methods.append({
                'address': addr,
                'name': func_name,
                'size': size,
                'signature': func_info.get('signature', '')
            })

    print(f'找到 {len(methods)} 个 {class_name} 方法')
    print()

    # 扫描每个方法
    offset_stats = defaultdict(lambda: {
        'count': 0,
        'access_types': defaultdict(int),
        'examples': []
    })

    for method in sorted(methods, key=lambda m: m['address']):
        addr = method['address']
        size = method['size']
        name = method['name']

        # 找 this 寄存器
        this_reg = find_this_register(addr)

        if not this_reg:
            continue

        # 扫描 member accesses
        accesses = scan_member_accesses(addr, size, this_reg)

        for access in accesses:
            offset = access['offset']

            # 过滤负偏移（可能是访问基类或栈变量）
            if offset < 0:
                continue

            # 过滤过大的偏移（可能是全局变量）
            if offset > 10000:
                continue

            stats = offset_stats[offset]
            stats['count'] += 1
            stats['access_types'][access['type']] += 1

            # 保存前几个例子
            if len(stats['examples']) < 3:
                stats['examples'].append({
                    'method': name,
                    'va': f'0x{access["va"]:X}',
                    'instruction': access['instruction'],
                    'type': access['type']
                })

    return offset_stats


def main():
    import sys

    if len(sys.argv) < 2:
        print('用法: python scan_class_members.py <ClassName>')
        print('示例: python scan_class_members.py CCBUI')
        sys.exit(1)

    class_name = sys.argv[1]

    print(f'扫描 {class_name} 类的 member access 模式')
    print('=' * 80)
    print()

    stats = scan_class_methods(class_name)

    # 按偏移排序输出
    print(f'\n发现 {len(stats)} 个不同的 offset:')
    print()

    for offset in sorted(stats.keys()):
        info = stats[offset]
        print(f'Offset {offset} (0x{offset:X}):')
        print(f'  访问次数: {info["count"]}')
        print(f'  访问类型:')
        for access_type, count in sorted(info['access_types'].items()):
            print(f'    {access_type}: {count}')

        print(f'  示例:')
        for ex in info['examples']:
            print(f'    {ex["method"]}')
            print(f'      VA={ex["va"]}: {ex["instruction"]} ({ex["type"]})')

        print()

    # 输出 JSON 报告
    output_file = PROJECT_ROOT / f'pipeline/_logs/member_scan_{class_name}.json'
    output_file.parent.mkdir(parents=True, exist_ok=True)

    # 转换为可序列化格式
    json_stats = {
        str(offset): {
            'count': info['count'],
            'access_types': dict(info['access_types']),
            'examples': info['examples']
        }
        for offset, info in stats.items()
    }

    with open(output_file, 'w') as f:
        json.dump(json_stats, f, indent=2)

    print(f'详细报告已保存到: {output_file}')


if __name__ == '__main__':
    main()
