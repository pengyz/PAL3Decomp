"""
规范化 annotations 中的整数类型。

在 x86 Windows 上，以下类型等价（都是 32 位）：
- unsigned long = unsigned int = DWORD
- long = int

统一规范为：unsigned int 和 int（更符合 C++ 习惯）
"""
import json
import os
from pathlib import Path

def normalize_type(type_str):
    """将类型字符串中的 unsigned long/long 规范化为 unsigned int/int"""
    # 保留指针和数组标记
    original = type_str
    
    # 替换规则（注意顺序，先处理 unsigned long）
    # 1. unsigned long * -> unsigned int *
    type_str = type_str.replace('unsigned long *', 'unsigned int *')
    # 2. unsigned long -> unsigned int (standalone)
    type_str = type_str.replace('unsigned long', 'unsigned int')
    # 3. long * -> int * (但不能影响 unsigned long）
    # 4. long -> int (standalone，最后处理避免误替换 unsigned long)
    
    # 对于 long，需要更谨慎（避免影响已经处理过的 unsigned int）
    if ' long ' in type_str or type_str.endswith(' long') or type_str.startswith('long '):
        type_str = type_str.replace(' long ', ' int ')
        if type_str.endswith(' long'):
            type_str = type_str[:-5] + ' int'
        if type_str.startswith('long '):
            type_str = 'int ' + type_str[5:]
        if type_str == 'long':
            type_str = 'int'
    
    if type_str.endswith('long *'):
        type_str = type_str[:-6] + 'int *'
    
    return type_str

def normalize_struct(struct_path):
    """规范化单个结构体文件中的类型"""
    with open(struct_path, 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    changed = False
    members = data.get('known_members', {})
    
    for offset, member in members.items():
        old_type = member['type']
        new_type = normalize_type(old_type)
        if new_type != old_type:
            member['type'] = new_type
            changed = True
            print(f"  {struct_path.name:30s} offset {offset:4s}: {old_type} -> {new_type}")
    
    if changed:
        with open(struct_path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)
    
    return changed

def main():
    structs_dir = Path('data/annotations/structs')
    total_changed = 0
    
    print("规范化 annotations 中的整数类型...")
    print("unsigned long -> unsigned int")
    print("long -> int")
    print()
    
    for struct_file in sorted(structs_dir.glob('*.json')):
        if normalize_struct(struct_file):
            total_changed += 1
    
    print()
    print(f"完成：{total_changed} 个结构体已修改")

if __name__ == '__main__':
    main()
