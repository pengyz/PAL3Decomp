#!/usr/bin/env python3
"""
从 PAL3patch 导入基础类型（gbVec3D, gbColorQuad 等）到 annotations
这些类型在我们的 annotations 中不存在，可以直接创建
"""
import json
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ANN_DIR = PROJECT_ROOT / 'data/annotations/structs'

# PAL3patch 基础类型定义（手动整理）
BASIC_TYPES = {
    'gbVec3D': {
        'note': 'from PAL3patch:pal3.h, 3D vector',
        'binary_size': 12,
        'known_members': {
            '0': {'name': 'x', 'type': 'float', 'source': 'PAL3patch:pal3.h'},
            '4': {'name': 'y', 'type': 'float', 'source': 'PAL3patch:pal3.h'},
            '8': {'name': 'z', 'type': 'float', 'source': 'PAL3patch:pal3.h'},
        }
    },
    'gbQuaternion': {
        'note': 'from PAL3patch:pal3.h, quaternion for rotation',
        'binary_size': 16,
        'known_members': {
            '0': {'name': 'x', 'type': 'float', 'source': 'PAL3patch:pal3.h'},
            '4': {'name': 'y', 'type': 'float', 'source': 'PAL3patch:pal3.h'},
            '8': {'name': 'z', 'type': 'float', 'source': 'PAL3patch:pal3.h'},
            '12': {'name': 'w', 'type': 'float', 'source': 'PAL3patch:pal3.h'},
        }
    },
    'gbColorQuad': {
        'note': 'from PAL3patch:pal3.h, RGBA color (union with DWORD)',
        'binary_size': 4,
        'known_members': {
            '0': {'name': 'r', 'type': 'unsigned char', 'source': 'PAL3patch:pal3.h'},
            '1': {'name': 'g', 'type': 'unsigned char', 'source': 'PAL3patch:pal3.h'},
            '2': {'name': 'b', 'type': 'unsigned char', 'source': 'PAL3patch:pal3.h'},
            '3': {'name': 'a', 'type': 'unsigned char', 'source': 'PAL3patch:pal3.h'},
            # union 成员，共享同一偏移
            '0': {'name': 'color', 'type': 'unsigned int', 'source': 'PAL3patch:pal3.h (union)'},
        }
    },
}


def create_annotation(struct_name: str, definition: dict):
    """创建新的 annotation 文件"""
    ann_file = ANN_DIR / f'{struct_name}.json'

    if ann_file.exists():
        print(f'  ✗ {struct_name}: 已存在，跳过')
        return False

    # 添加 name 字段
    definition['name'] = struct_name

    with open(ann_file, 'w', encoding='utf-8') as f:
        json.dump(definition, f, indent=2, ensure_ascii=False)

    print(f'  ✓ {struct_name}: 创建成功 ({definition["binary_size"]} bytes, {len(definition["known_members"])} members)')
    return True


def main():
    print('从 PAL3patch 导入基础类型到 annotations\n')

    created = 0

    for struct_name, definition in BASIC_TYPES.items():
        if create_annotation(struct_name, definition):
            created += 1

    print(f'\n总计创建: {created} 个新结构体')

    if created > 0:
        print('\n下一步:')
        print('  1. python pipeline/check_annotations.py — 验证新创建的 annotations')
        print('  2. git add data/annotations/structs/')
        print('  3. git commit -m "feat(annotations): 从 PAL3patch 导入基础类型 (gbVec3D, gbQuaternion, gbColorQuad)"')

    return 0


if __name__ == '__main__':
    exit(main())
