#!/usr/bin/env python3
"""
导入 PAL3patch CCBUI 字段定义到 annotations
基于 member scan 验证结果
"""
import json
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
CCBUI_FILE = PROJECT_ROOT / 'data/annotations/structs/CCBUI.json'

# 高置信度字段（二进制验证通过）
HIGH_CONFIDENCE_FIELDS = [
    {
        'offset': 152,
        'name': 'm_pAttackSequenBack',
        'type': 'UIStatic *',
        'source': 'PAL3patch:pal3.h + binary_verified: 6 mov accesses (store:4, load:2)',
        'evidence_confidence': 90,
    },
    {
        'offset': 156,
        'name': 'm_pAttackSequenFace',
        'type': 'UIStatic *[11]',
        'source': 'PAL3patch:pal3.h + binary_verified: 9 access points in range, 6 LEA (array element addressing)',
        'evidence_confidence': 95,
        'note': 'Covers offset 156~199 (44 bytes). Some non-pointer accesses in range may indicate field reuse or union.',
    },
    {
        'offset': 216,
        'name': 'm_pRoleStateFace',
        'type': 'UIStatic *[5]',
        'source': 'PAL3patch:pal3.h + binary_verified: offset 220 has 11 accesses (lea:1, load:10)',
        'evidence_confidence': 85,
        'note': 'PAL3patch size [5] verified. Existing annotation had [3] with span=12.',
    },
]

# 中等置信度字段（PAL3patch 定义但扫描无访问）
MEDIUM_CONFIDENCE_FIELDS = [
    {
        'offset': 200,
        'name': 'm_pRoleStatePanel',
        'type': 'UIStatic *[4]',
        'source': 'PAL3patch:pal3.h (no binary access found in scan, field may be unused)',
        'evidence_confidence': 60,
    },
    {
        'offset': 236,
        'name': 'm_pRoleStateFaceName',
        'type': 'UIStatic *[5]',
        'source': 'PAL3patch:pal3.h (no binary access found in scan, field may be unused)',
        'evidence_confidence': 60,
    },
]


def array_covers_range(offset: int, type_str: str) -> tuple:
    """计算数组覆盖的 offset 范围"""
    if '[' not in type_str:
        # 不是数组，只占 4 字节（假设是指针）
        return (offset, offset + 4)

    # 解析数组大小
    # 例如: "UIStatic *[11]" -> 11
    count_str = type_str.split('[')[1].split(']')[0]
    count = int(count_str)

    # 指针数组，每个元素 4 字节
    return (offset, offset + count * 4)


def import_fields(confidence_level: str):
    """导入指定置信度级别的字段"""
    with open(CCBUI_FILE) as f:
        ccbui = json.load(f)

    if confidence_level == 'high':
        fields_to_import = HIGH_CONFIDENCE_FIELDS
    elif confidence_level == 'medium':
        fields_to_import = MEDIUM_CONFIDENCE_FIELDS
    else:
        fields_to_import = HIGH_CONFIDENCE_FIELDS + MEDIUM_CONFIDENCE_FIELDS

    imported = []
    conflicts = []

    for field in fields_to_import:
        offset = field['offset']
        offset_str = str(offset)

        # 计算覆盖范围
        start, end = array_covers_range(offset, field['type'])

        # 检查冲突
        conflicting_offsets = []
        for existing_offset_str in ccbui['known_members']:
            existing_offset = int(existing_offset_str)
            if start <= existing_offset < end and existing_offset != offset:
                conflicting_offsets.append(existing_offset_str)

        if conflicting_offsets:
            conflicts.append({
                'new_field': field,
                'conflicts': conflicting_offsets,
                'range': (start, end)
            })

        # 添加或覆盖字段
        ccbui['known_members'][offset_str] = {
            'name': field['name'],
            'type': field['type'],
            'source': field['source'],
        }

        if 'note' in field:
            ccbui['known_members'][offset_str]['note'] = field['note']

        imported.append(field['name'])

    # 保存
    with open(CCBUI_FILE, 'w') as f:
        json.dump(ccbui, f, indent=2, ensure_ascii=False)

    return imported, conflicts


def main():
    import sys

    confidence = sys.argv[1] if len(sys.argv) > 1 else 'high'

    print(f'导入 PAL3patch CCBUI 字段 (置信度: {confidence})')
    print('=' * 80)
    print()

    imported, conflicts = import_fields(confidence)

    print(f'成功导入 {len(imported)} 个字段:')
    for name in imported:
        print(f'  - {name}')
    print()

    if conflicts:
        print(f'发现 {len(conflicts)} 个冲突:')
        for conflict in conflicts:
            field = conflict['new_field']
            print(f'\n  {field["name"]} @ offset {field["offset"]}:')
            print(f'    覆盖范围: {conflict["range"][0]}~{conflict["range"][1]-1}')
            print(f'    冲突字段:')
            for off_str in conflict['conflicts']:
                print(f'      offset {off_str}')
        print()
        print('建议: 检查冲突字段，确认是否需要删除或标记为 union')
    else:
        print('无冲突 ✓')

    print()
    print(f'已更新: {CCBUI_FILE}')


if __name__ == '__main__':
    main()
