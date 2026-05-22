#!/usr/bin/env python3
"""
从 PAL3Patch 匹配字段名到 annotations 中的 _todo_ 字段。

用法：python pipeline/match_pal3patch_fields.py <ClassName>

策略：
1. 解析 PAL3Patch pal3.h 中的结构体定义
2. 计算字段偏移（基于 MSVC 6.0 32-bit 对齐规则）
3. 对于 annotations 中每个 _todo_ 字段，查找 PAL3Patch 中相同偏移的字段
4. 如果类型兼容，建议采用 PAL3Patch 的命名
"""

import sys
import json
import re
from pathlib import Path

# Load struct sizes from annotations
def load_struct_sizes():
    sizes = {}
    for f in Path('data/annotations/structs').glob('*.json'):
        with open(f, 'r', encoding='utf-8') as fp:
            data = json.load(fp)
            sizes[data['name']] = data.get('binary_size', 0)
    return sizes

ANNO_SIZES = load_struct_sizes()

# Type sizes (MSVC 6.0 32-bit)
TYPE_SIZES = {
    'char': 1, 'unsigned char': 1, 'BYTE': 1,
    'short': 2, 'unsigned short': 2, 'WORD': 2,
    'int': 4, 'unsigned int': 4, 'long': 4, 'unsigned long': 4,
    'float': 4, 'DWORD': 4, 'BOOL': 4,
    'double': 8,
    'void*': 4, 'char*': 4,
    'RECT': 16, 'POINT': 8, 'tagRECT': 16, 'tagPOINT': 8,
    'gbColorQuad': 4,
    'std_vector_int': 16,
    'std_basic_string': 16,  # std::string (MSVC 6.0 STL)
}
TYPE_SIZES.update(ANNO_SIZES)

def get_type_info(typ):
    """返回 (size, alignment)"""
    # Enum types are int-sized
    if typ.startswith('enum '):
        return (4, 4)

    base_type = typ.replace('struct ', '').replace('enum ', '').strip()

    # Pointer
    if '*' in base_type:
        return (4, 4)

    # Array
    array_match = re.match(r'(\w+)\[(\d+)\]', base_type)
    if array_match:
        elem_type = array_match.group(1)
        count = int(array_match.group(2))
        if elem_type in TYPE_SIZES:
            elem_size = TYPE_SIZES[elem_type]
            elem_align = min(elem_size, 4)
            return (elem_size * count, elem_align)
        return (None, None)

    # Known type
    if base_type in TYPE_SIZES:
        size = TYPE_SIZES[base_type]
        align = min(size, 8)
        return (size, align)

    return (None, None)

def parse_pal3patch_struct(struct_name):
    """从 PAL3patch 的 pal3.h 中解析结构体定义"""
    pal3_h = Path('extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h')
    if not pal3_h.exists():
        print(f"错误：找不到 {pal3_h}")
        return None

    content = pal3_h.read_text(encoding='utf-8', errors='ignore')
    pattern = rf'^struct {re.escape(struct_name)} {{\s*$'
    match = re.search(pattern, content, re.MULTILINE)

    if not match:
        return None

    # Extract struct body
    start = match.end()
    brace_count = 1
    pos = start
    while pos < len(content) and brace_count > 0:
        if content[pos] == '{':
            brace_count += 1
        elif content[pos] == '}':
            brace_count -= 1
        pos += 1

    struct_body = content[start:pos-1]

    # Parse fields
    fields = []
    for line in struct_body.split('\n'):
        line = line.strip()
        if not line or line.startswith('//') or line.startswith('/*'):
            continue

        # Match field definition
        m = re.match(r'(struct |enum )?(\w+(?:\s*\*)?)\s+(\w+)(?:\[(\d+)\])?;', line)
        if m:
            prefix, typ, name, array_size = m.groups()
            if prefix:
                typ = prefix.strip() + ' ' + typ
            if array_size:
                typ = typ + '[' + array_size + ']'
            fields.append((typ.strip(), name))

    return fields

def calculate_offsets(fields):
    """计算字段偏移"""
    result = []
    offset = 0

    for typ, name in fields:
        size, align = get_type_info(typ)

        if size is None:
            # Unknown type, can't continue
            result.append({
                'offset': offset,
                'name': name,
                'type': typ,
                'size': '?',
                'note': 'unknown_type'
            })
            return result  # Stop here

        # Handle baseclass
        if 'baseclass' in name:
            result.append({
                'offset': 0,
                'name': name,
                'type': typ,
                'size': size,
                'note': 'baseclass'
            })
            offset = size
            continue

        # Alignment
        if align > 1:
            offset = (offset + align - 1) & ~(align - 1)

        result.append({
            'offset': offset,
            'name': name,
            'type': typ,
            'size': size
        })
        offset += size

    return result

def type_compatible(patch_type, anno_type):
    """检查类型是否兼容"""
    # 简单的字符串匹配
    p = patch_type.replace('struct ', '').replace('enum ', '').strip()
    a = anno_type.replace('struct ', '').replace('enum ', '').strip()

    # Direct match
    if p == a:
        return True

    # Both pointers - compatible regardless of target type
    if '*' in p and '*' in a:
        return True

    # float vs pointer - NOT compatible even if same size
    p_is_ptr = '*' in p
    a_is_ptr = '*' in a
    p_is_float = 'float' in p or 'double' in p
    a_is_float = 'float' in a or 'double' in a

    if p_is_ptr != a_is_ptr:  # One pointer, one not
        return False

    if p_is_float != a_is_float:  # One float, one not
        return False

    # Size-based match for integer types only (int, char, short, long, DWORD, etc.)
    p_size, _ = get_type_info(patch_type)
    a_size, _ = get_type_info(anno_type)
    if p_size and a_size and p_size == a_size:
        # Same size integer types are compatible
        if p_size in [1, 2, 4, 8] and not p_is_float and not a_is_float and not p_is_ptr and not a_is_ptr:
            return True

    return False

def main():
    if len(sys.argv) < 2:
        print("用法: python pipeline/match_pal3patch_fields.py <ClassName>")
        print("示例: python pipeline/match_pal3patch_fields.py UIListBox")
        sys.exit(1)

    struct_name = sys.argv[1]

    print(f"=== 匹配 PAL3Patch 字段名: {struct_name} ===\n")

    # Parse PAL3Patch
    print("1. 解析 PAL3Patch 结构体...")
    patch_fields_raw = parse_pal3patch_struct(struct_name)
    if not patch_fields_raw:
        print(f"   错误：PAL3Patch 中未找到 {struct_name}")
        sys.exit(1)
    print(f"   找到 {len(patch_fields_raw)} 个字段\n")

    # Calculate offsets
    print("2. 计算字段偏移...")
    patch_fields = calculate_offsets(patch_fields_raw)

    # Check for unknown types
    unknown = [f for f in patch_fields if f.get('note') == 'unknown_type']
    if unknown:
        print(f"   警告：遇到未知类型，无法计算后续偏移")
        print(f"   未知类型: {unknown[0]['type']} (字段: {unknown[0]['name']})")
        print()

    # Load annotations
    print("3. 加载 annotations...")
    anno_file = Path(f'data/annotations/structs/{struct_name}.json')
    if not anno_file.exists():
        print(f"   错误：annotations 中未找到 {struct_name}.json")
        sys.exit(1)

    with open(anno_file, 'r', encoding='utf-8') as f:
        anno_data = json.load(f)

    members = anno_data.get('known_members', {})

    # Build patch offset map
    patch_by_offset = {}
    for field in patch_fields:
        off = field.get('offset')
        if off is not None and off != 0:
            patch_by_offset[off] = field

    # Find matches
    print("4. 匹配 _todo_ 字段...\n")
    print(f"{'偏移':<8} {'Anno类型':<25} {'Anno字段名':<20} {'→':<3} {'Patch类型':<25} {'Patch字段名'}")
    print("=" * 110)

    matches = []
    for off_str, member in sorted(members.items(), key=lambda x: int(x[0])):
        name = member['name']
        if not (name.startswith('_todo_') or name.startswith('_field_')):
            continue

        off = int(off_str)
        anno_type = member['type']

        if off in patch_by_offset:
            patch_field = patch_by_offset[off]
            patch_type = patch_field['type']
            patch_name = patch_field['name']

            if type_compatible(patch_type, anno_type):
                print(f"{off:<8} {anno_type:<25} {name:<20} {'→':<3} {patch_type:<25} {patch_name}")
                matches.append({
                    'offset': off,
                    'anno_name': name,
                    'anno_type': anno_type,
                    'patch_name': patch_name,
                    'patch_type': patch_type
                })
            else:
                print(f"{off:<8} {anno_type:<25} {name:<20} {'≠':<3} {patch_type:<25} {patch_name} (类型不兼容)")

    print(f"\n找到 {len(matches)} 个可匹配的 _todo_ 字段")

    # Output suggested changes
    if matches:
        print("\n=== 建议的修改 ===")
        print("将以下字段重命名：")
        for m in matches:
            print(f"  offset {m['offset']:4d} (0x{m['offset']:03X}): {m['anno_name']:20s} → {m['patch_name']}")

if __name__ == '__main__':
    main()
