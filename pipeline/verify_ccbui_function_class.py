#!/usr/bin/env python3
"""
验证 CCBUI offset 156/180 访问所在函数是否真的属于 CCBUI 类
通过检查 functions.json 中的函数归属
"""
import json
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
FUNCTIONS_FILE = PROJECT_ROOT / 'data/annotations/functions.json'
STRUCTS_DIR = PROJECT_ROOT / 'data/annotations/structs'

# 需要验证的访问点
ACCESSES_TO_VERIFY = [
    {
        'va': 0x518827,
        'offset': 156,
        'instruction': 'fild dword [eax+0x9C]',
        'base_reg': 'eax',
    },
    {
        'va': 0x441937,
        'offset': 180,
        'instruction': 'fild dword [esi+0xB4]',
        'base_reg': 'esi',
    },
]


def find_function_containing(va: int) -> dict:
    """查找包含该 VA 的函数"""
    with open(FUNCTIONS_FILE) as f:
        functions = json.load(f)

    for func_addr_str, func_info in functions.items():
        func_addr = int(func_addr_str, 16)
        func_size = func_info.get('size', 0)

        if func_addr <= va < func_addr + func_size:
            return {
                'address': func_addr,
                'name': func_info.get('name', 'unknown'),
                'signature': func_info.get('signature', ''),
                'size': func_size,
            }

    return None


def extract_class_from_function_name(func_name: str) -> str:
    """从函数名提取类名"""
    if '::' in func_name:
        return func_name.split('::')[0]
    return None


def check_vtable_membership(class_name: str, func_addr: int) -> bool:
    """检查函数地址是否出现在该类 per-class vtables 的任一 slot 中。"""
    struct_file = STRUCTS_DIR / ('%s.json' % class_name)
    if not struct_file.exists():
        return None

    with open(struct_file, encoding='utf-8') as f:
        sinfo = json.load(f)

    for vt in sinfo.get('vtables', []):
        for slot in vt.get('slots', []):
            saddr = slot.get('addr', '')
            if saddr and int(saddr, 16) == func_addr:
                return True

    return False


def main():
    print('验证 CCBUI offset 156/180 的函数归属\n')
    print('=' * 80)

    for access in ACCESSES_TO_VERIFY:
        va = access['va']
        offset = access['offset']

        print(f'\nOffset {offset} (VA=0x{va:X}):')
        print(f'  指令: {access["instruction"]}')
        print(f'  Base: {access["base_reg"]}')
        print()

        # 查找包含该 VA 的函数
        func = find_function_containing(va)

        if not func:
            print(f'  ✗ 未找到包含 VA 0x{va:X} 的函数')
            continue

        print(f'  函数: {func["name"]}')
        print(f'  地址: 0x{func["address"]:X}')
        print(f'  大小: {func["size"]} bytes')
        print(f'  签名: {func["signature"]}')
        print()

        # 提取类名
        class_name = extract_class_from_function_name(func['name'])

        if not class_name:
            print(f'  ⚠️  无法从函数名提取类名')
            continue

        print(f'  所属类: {class_name}')

        # 判断是否属于 CCBUI
        if class_name == 'CCBUI':
            print(f'  ✓ 函数属于 CCBUI 类')

            # 检查 vtable
            in_vtable = check_vtable_membership(class_name, func['address'])
            if in_vtable is not None:
                if in_vtable:
                    print(f'  ✓ 在 CCBUI vtable 中')
                else:
                    print(f'  ℹ  不在 vtable 中（可能是普通方法）')

            print(f'  → 结论: offset {offset} **属于 CCBUI**，应保留此字段')
        else:
            print(f'  ✗ 函数属于 {class_name}，不是 CCBUI')
            print(f'  → 结论: offset {offset} **不属于 CCBUI**，应删除此字段')

        print('\n' + '-' * 80)

    print('\n\n=== 总结 ===\n')
    print('如果 offset 156/180 的访问都不属于 CCBUI:')
    print('  → 说明这些字段被误归类到 CCBUI')
    print('  → 应该从 CCBUI annotations 中删除')
    print('  → PAL3patch 的布局更可能是正确的')
    print()
    print('如果 offset 156/180 的访问都属于 CCBUI:')
    print('  → 说明我们的字段定义是正确的')
    print('  → 但需要解释为什么和 PAL3patch 差 864 bytes')


if __name__ == '__main__':
    main()
