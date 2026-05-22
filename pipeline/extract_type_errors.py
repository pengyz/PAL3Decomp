#!/usr/bin/env python3
"""
从编译错误中提取可通过 annotation 修正的候选字段。

用法: python pipeline/extract_type_errors.py [snapshot_dir]

默认使用最新的 snapshot。

输出: pipeline/_logs/batch1/candidates.json
"""
import sys
import os
import re
import json
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
SRC_DIR = PROJECT_ROOT / "src" / "pal3"
ANNOTATIONS_DIR = PROJECT_ROOT / "data" / "annotations" / "structs"
SNAPSHOTS_DIR = PROJECT_ROOT / "pipeline" / "snapshots" / "data"
OUTPUT_DIR = PROJECT_ROOT / "pipeline" / "_logs" / "batch1"


def find_latest_snapshot():
    if not SNAPSHOTS_DIR.exists():
        return None
    dirs = sorted([d for d in SNAPSHOTS_DIR.iterdir() if d.is_dir()])
    return dirs[-1] if dirs else None


def parse_error_line(line):
    """解析错误行: File(line): error CODE: message"""
    m = re.match(r'(.+?)\((\d+)\): error (C\d+): (.+)', line)
    if not m:
        return None
    return {
        'file': m.group(1),
        'line': int(m.group(2)),
        'code': m.group(3),
        'message': m.group(4),
    }


def extract_type_from_c2440(msg):
    """从 C2440 消息提取 from_type 和 to_type"""
    m = re.search(r"cannot convert from '(.+?)' to '(.+?)'", msg)
    if m:
        return m.group(1), m.group(2)
    return None, None


def read_source_line(src_file, lineno):
    """读取源码行"""
    full_path = SRC_DIR / src_file.replace('\\', '/')
    if not full_path.exists():
        return None
    try:
        lines = full_path.read_text(encoding='utf-8', errors='ignore').split('\n')
        if lineno <= len(lines):
            return lines[lineno - 1]
    except:
        pass
    return None


def find_function_va(src_file, lineno):
    """从源码中向上搜索函数地址注释 // 0xADDR"""
    full_path = SRC_DIR / src_file.replace('\\', '/')
    if not full_path.exists():
        return None
    try:
        lines = full_path.read_text(encoding='utf-8', errors='ignore').split('\n')
        for i in range(min(lineno - 1, len(lines) - 1), -1, -1):
            m = re.match(r'^// (0x[0-9A-Fa-f]+)', lines[i])
            if m:
                return m.group(1)
    except:
        pass
    return None


def get_class_from_file(src_file):
    """从文件名推断类名"""
    basename = Path(src_file.replace('\\', '/')).stem
    return basename


def classify_error(source_line, from_type, to_type, error_code):
    """
    分类错误:
    - this_field: this->field 被赋值为不兼容类型 → annotation 修正
    - lodword_field: LODWORD(this->field) = ptr → float 应为 int/ptr
    - local_var: 局部变量类型问题 → codegen 问题
    - func_sig: 函数签名问题
    - other: 其他
    """
    if source_line is None:
        return 'unknown'

    line = source_line.strip()

    # LODWORD(this->field) = value → 字段被标注为 float 但实际是 int/ptr
    if re.search(r'LODWORD\(this->\w+\)', line):
        return 'lodword_field'

    # this->field = value (直接赋值)
    if re.search(r'this->\w+\s*=', line):
        return 'this_field'

    # *(_DWORD *)this->array 模式
    if re.search(r'\*\(_DWORD\s*\*\)this->', line):
        return 'this_field'

    # 局部变量赋值 (v10[N] = ..., v24 = ..., 等)
    if re.match(r'\s*(v\d+|[a-z]\d*)\s*=', line) or re.match(r'\s*(v\d+)\[', line):
        return 'local_var'

    # 函数调用参数问题
    if error_code == 'C2664':
        return 'func_sig'

    return 'other'


def extract_field_from_line(source_line):
    """从源码行提取字段名"""
    if source_line is None:
        return None

    # LODWORD(this->field_name)
    m = re.search(r'LODWORD\(this->(\w+)\)', source_line)
    if m:
        return m.group(1)

    # this->field_name = ...
    m = re.search(r'this->(\w+)', source_line)
    if m:
        return m.group(1)

    return None


def lookup_annotation(class_name, field_name):
    """查找 annotation 中的字段信息"""
    anno_file = ANNOTATIONS_DIR / f"{class_name}.json"
    if not anno_file.exists():
        return None

    try:
        data = json.loads(anno_file.read_text(encoding='utf-8'))
        members = data.get('known_members', {})
        for offset, member in members.items():
            if member.get('name') == field_name:
                return {
                    'offset': offset,
                    'type': member.get('type', ''),
                    'source': member.get('source', ''),
                }
    except:
        pass
    return None


def main():
    # 确定 snapshot 目录
    if len(sys.argv) > 1:
        snapshot_dir = Path(sys.argv[1])
    else:
        snapshot_dir = find_latest_snapshot()
        if snapshot_dir is None:
            print("错误：找不到 snapshot 目录")
            sys.exit(1)

    errors_file = snapshot_dir / "all_errors.txt"
    if not errors_file.exists():
        print(f"错误：找不到 {errors_file}")
        sys.exit(1)

    print(f"=== 从编译错误提取 annotation 修正候选 ===")
    print(f"Snapshot: {snapshot_dir.name}")
    print()

    # 解析所有 C2440/C2664 错误
    errors = []
    with open(errors_file, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            parsed = parse_error_line(line)
            if parsed and parsed['code'] in ('C2440', 'C2664'):
                errors.append(parsed)

    print(f"C2440/C2664 错误总数: {len(errors)}")

    # 分类并提取候选
    candidates_raw = defaultdict(lambda: {
        'errors': [],
        'category': None,
        'field': None,
        'class': None,
        'from_types': set(),
        'to_types': set(),
        'function_vas': set(),
    })

    stats = defaultdict(int)

    for err in errors:
        src_file = err['file']
        lineno = err['line']
        code = err['code']
        msg = err['message']

        from_type, to_type = extract_type_from_c2440(msg)
        source_line = read_source_line(src_file, lineno)
        category = classify_error(source_line, from_type, to_type, code)
        stats[category] += 1

        if category not in ('this_field', 'lodword_field'):
            continue

        field_name = extract_field_from_line(source_line)
        if not field_name:
            continue

        class_name = get_class_from_file(src_file)
        function_va = find_function_va(src_file, lineno)

        key = f"{class_name}.{field_name}"
        cand = candidates_raw[key]
        cand['field'] = field_name
        cand['class'] = class_name
        cand['category'] = category
        cand['errors'].append(f"{src_file}:{lineno}")
        if from_type:
            cand['from_types'].add(from_type)
        if to_type:
            cand['to_types'].add(to_type)
        if function_va:
            cand['function_vas'].add(function_va)

    print(f"\n分类统计:")
    for cat, count in sorted(stats.items(), key=lambda x: -x[1]):
        marker = " ← 可修正" if cat in ('this_field', 'lodword_field') else ""
        print(f"  {cat:20s}: {count:4d}{marker}")

    # 查找 annotation 信息并生成最终候选列表
    candidates = []
    no_annotation = 0

    for key, cand in candidates_raw.items():
        class_name = cand['class']
        field_name = cand['field']

        anno_info = lookup_annotation(class_name, field_name)
        if anno_info is None:
            no_annotation += 1
            continue

        # 推断建议类型
        suggested_type = None
        from_types = list(cand['from_types'])
        to_types = list(cand['to_types'])

        # C2440: "cannot convert from 'X *' to 'unsigned long'"
        # → 字段当前是 unsigned long，应该改为 X *
        for ft in from_types:
            if '*' in ft and any('unsigned long' in t or 'int' == t.strip() for t in to_types):
                suggested_type = ft
                break

        # LODWORD 模式：float 字段实际是 int/ptr
        if cand['category'] == 'lodword_field':
            if any('*' in ft for ft in from_types):
                suggested_type = next(ft for ft in from_types if '*' in ft)
            elif not suggested_type:
                suggested_type = 'int'

        candidates.append({
            'struct': class_name,
            'field': field_name,
            'offset': anno_info['offset'],
            'current_type': anno_info['type'],
            'current_source': anno_info['source'],
            'suggested_type': suggested_type,
            'error_count': len(cand['errors']),
            'category': cand['category'],
            'error_lines': cand['errors'][:10],
            'from_types': list(cand['from_types']),
            'to_types': list(cand['to_types']),
            'function_vas': list(cand['function_vas'])[:5],
        })

    # 按 error_count 倒序排序
    candidates.sort(key=lambda x: -x['error_count'])

    print(f"\n候选字段:")
    print(f"  可修正候选: {len(candidates)}")
    print(f"  无 annotation: {no_annotation}")

    # 输出
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    output_file = OUTPUT_DIR / "candidates.json"
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(candidates, f, indent=2, ensure_ascii=False)

    print(f"\n输出: {output_file}")

    # 打印前 20 个候选
    if candidates:
        print(f"\n=== 前 20 个候选（按 error_count 排序）===")
        print(f"{'#':<4} {'结构体':<25} {'字段':<25} {'当前类型':<20} {'建议类型':<25} {'错误数'}")
        print("=" * 130)
        for i, c in enumerate(candidates[:20]):
            print(f"{i+1:<4} {c['struct']:<25} {c['field']:<25} {c['current_type']:<20} {str(c['suggested_type']):<25} {c['error_count']}")


if __name__ == '__main__':
    main()
