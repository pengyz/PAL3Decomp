#!/usr/bin/env python3
"""
分析 raw IDB 导出的方法，提取字段偏移模式
对比当前 annotations，找出类型/偏移错误
"""
import json
import re
from collections import defaultdict

def extract_field_accesses(decompiled_code):
    """从反编译代码中提取字段访问模式"""
    accesses = []

    # 模式 1: *(_TYPE *)(this + OFFSET) = VALUE
    pattern1 = r'\*\(_(\w+) \*\)\(this \+ (\d+)\)\s*=\s*([^;]+);'
    for match in re.finditer(pattern1, decompiled_code):
        type_hint = match.group(1)
        offset = int(match.group(2))
        value = match.group(3).strip()
        accesses.append({
            'pattern': 'store',
            'offset': offset,
            'type_hint': type_hint,
            'value': value
        })

    # 模式 2: variable = *(_TYPE *)(this + OFFSET)
    pattern2 = r'=\s*\*\(_(\w+) \*\)\(this \+ (\d+)\)'
    for match in re.finditer(pattern2, decompiled_code):
        type_hint = match.group(1)
        offset = int(match.group(2))
        accesses.append({
            'pattern': 'load',
            'offset': offset,
            'type_hint': type_hint,
        })

    return accesses

def infer_class_from_method(method_name):
    """从方法名推断类名"""
    # Camera_ctor → Camera
    # CCBStage_Init → CCBStage
    parts = method_name.split('_')
    if len(parts) >= 2:
        return parts[0]
    return None

def analyze_raw_idb_export(json_path):
    """分析 raw IDB 导出的 JSON"""
    with open(json_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    # 按类组织字段访问
    class_fields = defaultdict(lambda: defaultdict(list))

    for method_name, method_data in data.items():
        class_name = infer_class_from_method(method_name)
        if not class_name:
            continue

        decompiled = method_data.get('decompiled', '')
        accesses = extract_field_accesses(decompiled)

        for access in accesses:
            offset = access['offset']
            class_fields[class_name][offset].append({
                'method': method_name,
                'pattern': access['pattern'],
                'type_hint': access.get('type_hint'),
                'value': access.get('value'),
            })

    return class_fields

def load_annotations(struct_name):
    """加载 annotations 中的结构体定义"""
    try:
        with open(f'data/annotations/structs/{struct_name}.json', 'r', encoding='utf-8') as f:
            return json.load(f)
    except:
        return None

def compare_with_annotations(class_fields):
    """对比 raw IDB 字段与 annotations"""
    results = []

    for class_name, fields in sorted(class_fields.items()):
        ann = load_annotations(class_name)
        if not ann:
            continue

        ann_members = ann.get('known_members', {})

        for offset, accesses in sorted(fields.items()):
            offset_str = str(offset)

            # 推断类型（基于 type_hint 和 value）
            type_hints = [a['type_hint'] for a in accesses if a.get('type_hint')]
            values = [a['value'] for a in accesses if a.get('value')]

            inferred_type = None
            confidence = 0

            # IEEE754 常量识别
            if '1065353216' in str(values):
                inferred_type = 'float'
                confidence = 95
            elif 'DWORD' in type_hints:
                inferred_type = 'int'
                confidence = 70
            elif 'BYTE' in type_hints:
                inferred_type = 'unsigned char'
                confidence = 70

            # 对比 annotations
            if offset_str in ann_members:
                ann_member = ann_members[offset_str]
                ann_type = ann_member['type']
                ann_name = ann_member['name']

                if inferred_type and ann_type != inferred_type:
                    results.append({
                        'class': class_name,
                        'offset': offset,
                        'name': ann_name,
                        'current_type': ann_type,
                        'inferred_type': inferred_type,
                        'confidence': confidence,
                        'evidence': f'{len(accesses)} accesses, hints={set(type_hints)}, values={values[:3]}'
                    })

    return results

def main():
    print('分析 raw IDB 导出的字段偏移...\n')

    # 分析 raw IDB
    class_fields = analyze_raw_idb_export('pipeline/ida/_logs/raw_core_classes.json')

    print('发现的类和字段:')
    for class_name, fields in sorted(class_fields.items()):
        print(f'  {class_name}: {len(fields)} 个字段')
    print()

    # 对比 annotations
    mismatches = compare_with_annotations(class_fields)

    if mismatches:
        print(f'发现 {len(mismatches)} 个类型不匹配:\n')
        for m in mismatches:
            print(f"{m['class']}.{m['offset']} ({m['name']}):")
            print(f"  当前类型: {m['current_type']}")
            print(f"  推断类型: {m['inferred_type']}")
            print(f"  置信度: {m['confidence']}")
            print(f"  证据: {m['evidence']}")
            print()
    else:
        print('未发现类型不匹配（在已导出的方法范围内）')

if __name__ == '__main__':
    main()
