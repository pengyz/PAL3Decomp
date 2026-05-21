#!/usr/bin/env python3
"""
系统化验证 PAL3patch 结构体定义的二进制证据
对核心结构体做深度对比，评估 PAL3patch 的置信度
"""
import struct
import json
from pathlib import Path
from typing import List, Tuple, Dict

PROJECT_ROOT = Path(__file__).parent.parent
EXE_PATH = PROJECT_ROOT / 'original/PAL3.exe'
ANN_DIR = PROJECT_ROOT / 'data/annotations/structs'

# 优先验证的核心结构体
PRIORITY_STRUCTS = [
    'UIWnd',       # 基础 UI 类
    'PtrArray',    # 基础容器
    'UIFrameWnd',  # CCBUI 基类
]

# PAL3patch 定义（来自 pal3.h，手动整理）
PAL3PATCH_CORE_DEFS = {
    'UIWnd': {
        'size': 68,
        'fields': [
            (0, 'vfptr', 'UIWndVtbl *', 4),
            (4, 'm_fontcolor', 'gbColorQuad', 4),
            (8, 'm_wndcolor', 'gbColorQuad', 4),
            (12, 'm_id', 'unsigned int', 4),
            (16, 'm_rect', 'tagRECT', 16),  # RECT = 4 LONG (16 bytes)
            (32, 'm_pfather', 'UIWnd *', 4),
            (36, 'm_childs', 'PtrArray', 16),
            (52, 'm_bcreateok', 'int', 4),
            (56, 'm_bvisible', 'int', 4),
            (60, 'm_benable', 'int', 4),
            (64, 'm_bfocus', 'int', 4),
        ],
        'note': 'Base UI window class',
    },
    'PtrArray': {
        'size': 16,
        'fields': [
            (0, 'buf', 'void **', 4),
            (4, 'capacity', 'int', 4),
            (8, 'length', 'int', 4),
            (12, 'increase', 'int', 4),
        ],
        'note': 'Dynamic pointer array container',
    },
    'UIFrameWnd': {
        'size': 152,  # UIWnd (68) + own fields (84)
        'base': 'UIWnd',
        'base_size': 68,
        'fields': [
            (68, 'szframe', 'char[80]', 80),
            (148, 'm_frameid', 'int', 4),
        ],
        'note': 'Frame window with texture path',
    },
}


def read_bytes(va: int, length: int) -> bytes:
    """从 PAL3.exe 读取字节"""
    with open(EXE_PATH, 'rb') as f:
        file_offset = va - 0x400000
        f.seek(file_offset)
        return f.read(length)


def find_global_instance(struct_name: str) -> List[Tuple[int, str]]:
    """查找全局实例（从 globals.json）"""
    globals_file = PROJECT_ROOT / 'data/annotations/globals.json'
    if not globals_file.exists():
        return []

    with open(globals_file) as f:
        globals_data = json.load(f)

    instances = []
    for addr_str, info in globals_data.items():
        if struct_name in info.get('type', ''):
            instances.append((int(addr_str, 16), info['name']))

    return instances


def scan_constructor_calls(struct_name: str) -> List[int]:
    """扫描构造函数调用模式（在 .text 段搜索 LEA+CALL）"""
    # 简化实现：从 functions.json 查找构造函数
    functions_file = PROJECT_ROOT / 'data/annotations/functions.json'
    if not functions_file.exists():
        return []

    with open(functions_file) as f:
        functions = json.load(f)

    ctors = []
    for addr_str, info in functions.items():
        name = info.get('name', '')
        if f'{struct_name}::' in name and ('ctor' in name.lower() or name.endswith('::Create')):
            ctors.append(int(addr_str, 16))

    return ctors


def validate_field_access(va: int, expected_offset: int, expected_size: int) -> Dict:
    """验证字段访问指令"""
    code = read_bytes(va, 10)

    # 解析 mov/lea 等指令的 disp32
    result = {
        'va': hex(va),
        'bytes': code[:8].hex().upper(),
        'match': False,
        'actual_offset': None,
        'instruction': 'unknown',
    }

    # 常见模式: 8B XX [disp32] / 89 XX [disp32] / 8D XX [disp32]
    if len(code) < 6:
        return result

    if code[0] in [0x8B, 0x89, 0x8D]:  # mov/lea
        modrm = code[1]
        mod = (modrm >> 6) & 0x3
        if mod == 0b10:  # [reg + disp32]
            disp32 = struct.unpack('<I', code[2:6])[0]
            result['actual_offset'] = disp32
            result['match'] = (disp32 == expected_offset)

            rm = modrm & 0x7
            base_reg = ['eax', 'ecx', 'edx', 'ebx', 'esp', 'ebp', 'esi', 'edi'][rm]

            if code[0] == 0x8B:
                result['instruction'] = f'mov ??, [{base_reg}+0x{disp32:X}]'
            elif code[0] == 0x89:
                result['instruction'] = f'mov [{base_reg}+0x{disp32:X}], ??'
            elif code[0] == 0x8D:
                result['instruction'] = f'lea ??, [{base_reg}+0x{disp32:X}]'

    return result


def compare_struct_definitions(struct_name: str) -> Dict:
    """对比 PAL3patch 和 annotations 的定义"""
    pal3patch_def = PAL3PATCH_CORE_DEFS.get(struct_name)
    if not pal3patch_def:
        return {'error': 'No PAL3patch definition'}

    ann_file = ANN_DIR / f'{struct_name}.json'
    if not ann_file.exists():
        return {'error': 'No annotations file'}

    with open(ann_file) as f:
        our_def = json.load(f)

    comparison = {
        'struct_name': struct_name,
        'pal3patch_size': pal3patch_def['size'],
        'our_size': our_def.get('binary_size', 0),
        'size_match': pal3patch_def['size'] == our_def.get('binary_size', 0),
        'field_comparisons': [],
        'score': 0,
        'total_fields': len(pal3patch_def['fields']),
    }

    matches = 0
    for offset, name, type_, size in pal3patch_def['fields']:
        our_member = our_def['known_members'].get(str(offset))

        field_cmp = {
            'offset': offset,
            'pal3patch_name': name,
            'pal3patch_type': type_,
            'our_name': our_member['name'] if our_member else None,
            'our_type': our_member['type'] if our_member else None,
            'offset_exists': our_member is not None,
            'type_match': False,
        }

        if our_member:
            # 类型标准化比较
            our_type_norm = our_member['type'].replace('unsigned int', 'DWORD').replace('tagRECT', 'RECT')
            pal3_type_norm = type_.replace('DWORD', 'unsigned int').replace('RECT', 'tagRECT')
            field_cmp['type_match'] = (our_type_norm == pal3_type_norm or
                                       our_member['type'] == type_ or
                                       our_type_norm == type_)
            if field_cmp['type_match']:
                matches += 1

        comparison['field_comparisons'].append(field_cmp)

    comparison['score'] = (matches / comparison['total_fields']) * 100 if comparison['total_fields'] > 0 else 0

    return comparison


def main():
    print('PAL3patch 结构体定义二进制验证\n')
    print('=' * 80)

    results = {}

    for struct_name in PRIORITY_STRUCTS:
        print(f'\n### {struct_name} ###\n')

        # 1. 定义对比
        comparison = compare_struct_definitions(struct_name)
        results[struct_name] = comparison

        if 'error' in comparison:
            print(f'  ✗ {comparison["error"]}')
            continue

        print(f'  大小: PAL3patch={comparison["pal3patch_size"]}, Ours={comparison["our_size"]} {"✓" if comparison["size_match"] else "✗"}')
        print(f'  字段匹配率: {comparison["score"]:.1f}% ({int(comparison["score"] * comparison["total_fields"] / 100)}/{comparison["total_fields"]})\n')

        # 2. 字段详细对比
        print('  字段对比:')
        for field in comparison['field_comparisons']:
            status = '✓' if field['type_match'] else ('?' if field['offset_exists'] else '✗')
            print(f'    {status} offset {field["offset"]:3d}: {field["pal3patch_name"]:20s} ({field["pal3patch_type"]})')
            if field['offset_exists'] and not field['type_match']:
                print(f'      {"":3s}   → Ours: {field["our_name"]:20s} ({field["our_type"]})')

        # 3. 全局实例查找
        instances = find_global_instance(struct_name)
        if instances:
            print(f'\n  全局实例 ({len(instances)} 个):')
            for addr, name in instances[:3]:  # 只显示前 3 个
                print(f'    0x{addr:X}: {name}')

        # 4. 置信度评估
        confidence = 0
        if comparison['size_match']:
            confidence += 40
        confidence += comparison['score'] * 0.6  # 字段匹配占 60%

        print(f'\n  📊 置信度评估: {confidence:.0f}/100')
        if confidence >= 95:
            print(f'  ✅ **高置信度** — 可直接导入 PAL3patch 定义')
        elif confidence >= 80:
            print(f'  ⚠️  需要少量修正后导入')
        elif confidence >= 60:
            print(f'  ⚠️  有差异，需要逐字段验证')
        else:
            print(f'  ❌ 差异太大，不建议直接导入')

        print('\n' + '-' * 80)

    # 总结
    print('\n\n=== 总结 ===\n')
    high_confidence = [name for name, res in results.items()
                       if 'score' in res and res['size_match'] and res['score'] >= 90]
    medium_confidence = [name for name, res in results.items()
                         if 'score' in res and (res['score'] >= 80 or res['size_match'])]

    print(f'高置信度（可直接导入）: {", ".join(high_confidence) if high_confidence else "无"}')
    print(f'中置信度（需少量修正）: {", ".join(medium_confidence) if medium_confidence else "无"}')

    # 输出 JSON 结果
    output_file = PROJECT_ROOT / 'pipeline/ida/_logs/pal3patch_validation.json'
    output_file.parent.mkdir(parents=True, exist_ok=True)
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    print(f'\n详细结果: {output_file}')

    return 0


if __name__ == '__main__':
    exit(main())
