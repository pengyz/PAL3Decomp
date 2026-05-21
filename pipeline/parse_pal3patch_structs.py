#!/usr/bin/env python3
"""
从 PAL3patch/pal3.h 解析结构体定义，转换为 annotations 格式
"""
import json
import re
from pathlib import Path
from typing import Dict, List, Tuple

PROJECT_ROOT = Path(__file__).parent.parent
PAL3PATCH_H = PROJECT_ROOT / 'extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h'
ANN_DIR = PROJECT_ROOT / 'data/annotations/structs'

# 类型映射：PAL3patch → annotations
TYPE_MAP = {
    'DWORD': 'unsigned int',
    'ULONG': 'unsigned long',
    'BYTE': 'unsigned char',
    'WORD': 'unsigned short',
    'RECT': 'tagRECT',
    'int': 'int',
    'float': 'float',
    'char': 'char',
    'void': 'void',
}

# 类型大小（用于计算偏移）
TYPE_SIZES = {
    'int': 4,
    'unsigned int': 4,
    'unsigned long': 4,
    'unsigned char': 1,
    'unsigned short': 2,
    'float': 4,
    'char': 1,
    'void *': 4,
    # 已知复合类型大小
    'gbColorQuad': 4,  # DWORD
    'tagRECT': 16,     # 4 LONG (left, top, right, bottom)
    'PtrArray': 16,    # 4个指针/int
    'gbVec3D': 12,     # 3 float
    'gbQuaternion': 16, # 4 float
}


def parse_struct_definition(lines: List[str], start_idx: int) -> Tuple[str, Dict, int]:
    """
    解析一个结构体定义
    返回: (struct_name, members_dict, end_idx)
    """
    # 第一行应该是 "struct StructName {"
    first_line = lines[start_idx].strip()
    match = re.match(r'struct\s+(\w+)\s*\{', first_line)
    if not match:
        return None, {}, start_idx

    struct_name = match.group(1)
    members = {}
    current_offset = 0

    idx = start_idx + 1
    while idx < len(lines):
        line = lines[idx].strip()
        idx += 1

        # 结束标记
        if line.startswith('}'):
            break

        # 跳过空行和注释
        if not line or line.startswith('//'):
            continue

        # 解析成员定义
        # 支持的模式:
        # 1. type name;
        # 2. type name[SIZE];
        # 3. struct Type name;
        # 4. struct Type *name;

        # 移除行尾分号和注释
        line = re.sub(r'//.*$', '', line)
        line = line.rstrip(';').strip()

        if not line:
            continue

        # 解析类型和名称
        parts = line.split()
        if len(parts) < 2:
            continue

        # 处理 struct 关键字
        if parts[0] == 'struct':
            type_name = parts[1]
            field_name = parts[2] if len(parts) > 2 else ''
            # 处理指针
            if field_name.startswith('*'):
                type_name = f'struct {type_name} *'
                field_name = field_name[1:]
            else:
                type_name = f'struct {type_name}'
        else:
            type_name = parts[0]
            field_name = parts[1]

        # 处理数组
        array_match = re.match(r'(\w+)\[0x([0-9A-Fa-f]+)\]', field_name)
        if array_match:
            field_name = array_match.group(1)
            array_size = int(array_match.group(2), 16)
            # 数组类型
            type_name = f'{type_name}[{array_size}]'

        # 处理指针
        if field_name.startswith('*'):
            type_name = f'{type_name} *'
            field_name = field_name[1:]

        # 计算字段大小
        field_size = get_type_size(type_name)

        # 添加到成员列表
        members[current_offset] = {
            'name': field_name,
            'type': normalize_type(type_name),
            'source': 'PAL3patch:pal3.h',
        }

        current_offset += field_size

    return struct_name, members, idx


def normalize_type(type_str: str) -> str:
    """标准化类型名"""
    # 移除 struct 关键字前缀（我们的 annotations 不使用）
    type_str = re.sub(r'^struct\s+', '', type_str)

    # 应用类型映射
    for old, new in TYPE_MAP.items():
        type_str = type_str.replace(old, new)

    return type_str


def get_type_size(type_str: str, known_struct_sizes: Dict[str, int] = None) -> int:
    """获取类型大小"""
    # 处理数组
    array_match = re.match(r'(.+)\[(\d+)\]', type_str)
    if array_match:
        base_type = array_match.group(1)
        count = int(array_match.group(2))
        return get_type_size(base_type, known_struct_sizes) * count

    # 处理指针
    if '*' in type_str:
        return 4

    # 查表
    normalized = normalize_type(type_str)
    if normalized in TYPE_SIZES:
        return TYPE_SIZES[normalized]

    # 查询已解析的结构体大小
    if known_struct_sizes and normalized in known_struct_sizes:
        return known_struct_sizes[normalized]

    # 从 annotations 查询
    ann = load_existing_annotation(normalized)
    if ann and 'binary_size' in ann:
        return ann['binary_size']

    # 默认返回 4（假设是 DWORD 或指针）
    print(f'  ⚠ 未知类型大小: {type_str}, 假设为 4 字节')
    return 4


def load_existing_annotation(struct_name: str) -> Dict:
    """加载已有的 annotation"""
    ann_file = ANN_DIR / f'{struct_name}.json'
    if ann_file.exists():
        with open(ann_file, encoding='utf-8') as f:
            return json.load(f)
    return None


def compare_with_annotation(struct_name: str, pal3patch_members: Dict) -> Dict:
    """对比 PAL3patch 定义和现有 annotations"""
    ann = load_existing_annotation(struct_name)
    if not ann:
        return {
            'status': 'new',
            'pal3patch_members': pal3patch_members,
        }

    differences = []
    matches = []

    for offset, pal3_member in pal3patch_members.items():
        offset_str = str(offset)
        if offset_str in ann['known_members']:
            ann_member = ann['known_members'][offset_str]

            # 比较类型
            pal3_type = pal3_member['type']
            ann_type = ann_member['type']

            if pal3_type != ann_type:
                differences.append({
                    'offset': offset,
                    'field': pal3_member['name'],
                    'pal3patch_type': pal3_type,
                    'annotation_type': ann_type,
                    'annotation_name': ann_member['name'],
                })
            else:
                matches.append({
                    'offset': offset,
                    'field': pal3_member['name'],
                    'type': pal3_type,
                })
        else:
            differences.append({
                'offset': offset,
                'field': pal3_member['name'],
                'pal3patch_type': pal3_member['type'],
                'annotation_type': None,
                'annotation_name': None,
            })

    return {
        'status': 'exists',
        'binary_size': ann.get('binary_size'),
        'matches': matches,
        'differences': differences,
    }


def main():
    """主函数"""
    print(f'解析 PAL3patch 结构体定义: {PAL3PATCH_H}\n')

    if not PAL3PATCH_H.exists():
        print(f'错误: 文件不存在: {PAL3PATCH_H}')
        return 1

    # 读取文件
    with open(PAL3PATCH_H, encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    # 查找所有结构体定义
    structs_found = {}
    idx = 0

    while idx < len(lines):
        line = lines[idx].strip()

        # 查找 struct 定义开始
        if line.startswith('struct ') and '{' in line and not line.endswith(';'):
            struct_name, members, end_idx = parse_struct_definition(lines, idx)
            if struct_name and members:
                structs_found[struct_name] = members
                print(f'✓ 解析: {struct_name} ({len(members)} members)')
            idx = end_idx
        else:
            idx += 1

    print(f'\n共解析 {len(structs_found)} 个结构体\n')

    # 对比重点结构体
    priority_structs = [
        'UIWnd', 'UIFrameWnd', 'UIListBox', 'UIStatic',
        'gbVec3D', 'gbColorQuad', 'PtrArray', 'RenderTarget',
    ]

    print('=== 对比分析（优先结构体）===\n')

    for struct_name in priority_structs:
        if struct_name not in structs_found:
            print(f'⊘ {struct_name}: PAL3patch 中未定义')
            continue

        comparison = compare_with_annotation(struct_name, structs_found[struct_name])

        if comparison['status'] == 'new':
            print(f'[NEW] {struct_name}: annotations 中不存在')
            continue

        print(f'[{struct_name}] binary_size={comparison["binary_size"]}')

        if comparison['differences']:
            print(f'  ✗ {len(comparison["differences"])} 个差异:')
            for diff in comparison['differences']:
                if diff['annotation_type'] is None:
                    print(f'    {diff["offset"]:4d}: {diff["field"]:20s} — PAL3patch 有, annotations 无 ({diff["pal3patch_type"]})')
                else:
                    print(f'    {diff["offset"]:4d}: {diff["field"]:20s} — 类型不匹配')
                    print(f'          PAL3patch:   {diff["pal3patch_type"]}')
                    print(f'          annotations: {diff["annotation_type"]} ({diff["annotation_name"]})')

        if comparison['matches']:
            print(f'  ✓ {len(comparison["matches"])} 个字段匹配')

        print()

    return 0


if __name__ == '__main__':
    exit(main())
