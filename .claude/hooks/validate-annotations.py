#!/usr/bin/env python3
"""PreToolUse hook: annotations 数据写入守卫。

拦截所有对 pipeline/data/annotations/ 的写入操作：
- Edit/Write 工具：验证文件内容合规性
- Bash 工具：检测命令中对 annotations 路径的写入意图

对 structs/*.json: 检查对齐和重叠
对 functions.json: 检查地址格式和必填字段
对 globals.json: 检查地址格式和必填字段

exit 0 = 放行, exit 2 = 阻止
"""
import json
import sys
import re
import os

ANNOTATIONS_PATH = 'pipeline/data/annotations'


def get_alignment(mtype):
    if '*' in mtype:
        return 4
    for t in ['int', 'float', 'DWORD', 'unsigned long', 'unsigned int', 'LONG', 'UINT', 'BOOL']:
        if t in mtype:
            return 4
    for t in ['short', 'WORD', 'unsigned short']:
        if t in mtype:
            return 2
    for t in ['char', 'unsigned char', 'bool', 'BYTE']:
        if t in mtype:
            return 1
    if 'double' in mtype:
        return 8
    arr = re.search(r'\[', mtype)
    if arr:
        return get_alignment(mtype[:arr.start()].strip())
    return 4


def get_member_size(mtype):
    a = get_alignment(mtype)
    if 'double' in mtype:
        return 8
    return max(a, 1)


def validate_struct(data):
    errors = []
    members = data.get('known_members', {})
    if not members:
        return True, []

    sorted_m = sorted([(int(off), members[off]) for off in members], key=lambda x: x[0])

    # 对齐
    for off, m in sorted_m:
        align = get_alignment(m.get('type', ''))
        if align > 1 and off % align != 0:
            errors.append(f"ALIGN: +{off} ({hex(off)}) {m['type']} {m.get('name','')}")

    # 重叠
    prev_end = 0
    prev_name = ''
    for off, m in sorted_m:
        sz = get_member_size(m.get('type', ''))
        if off < prev_end:
            errors.append(f"OVERLAP: +{off} {m.get('name','')} conflicts with {prev_name}")
        prev_end = off + sz
        prev_name = m.get('name', '')

    return len(errors) == 0, errors


def validate_functions(data):
    errors = []
    for addr, info in data.items():
        if not re.match(r'^0x[0-9A-Fa-f]{8}$', addr):
            errors.append(f"BAD_ADDR: {addr}")
        if not info.get('name'):
            errors.append(f"NO_NAME: {addr}")
        if not info.get('signature'):
            errors.append(f"NO_SIG: {addr}")
    return len(errors) == 0, errors


def validate_globals(data):
    errors = []
    for addr, info in data.items():
        if not re.match(r'^0x[0-9A-Fa-f]{6,8}$', addr):
            errors.append(f"BAD_ADDR: {addr}")
        if not info.get('name'):
            errors.append(f"NO_NAME: {addr}")
    return len(errors) == 0, errors


def check_file_content(file_path, content_str):
    """根据文件路径选择验证器"""
    if '/annotations/structs/' in file_path and file_path.endswith('.json'):
        try:
            data = json.loads(content_str)
            passed, errors = validate_struct(data)
            return passed, errors
        except json.JSONDecodeError:
            return False, ["INVALID_JSON"]

    if file_path.endswith('functions.json') and '/annotations/' in file_path:
        try:
            data = json.loads(content_str)
            passed, errors = validate_functions(data)
            return passed, errors
        except json.JSONDecodeError:
            return False, ["INVALID_JSON"]

    if file_path.endswith('globals.json') and '/annotations/' in file_path:
        try:
            data = json.loads(content_str)
            passed, errors = validate_globals(data)
            return passed, errors
        except json.JSONDecodeError:
            return False, ["INVALID_JSON"]

    return True, []


def handle_write(tool_input):
    file_path = tool_input.get('file_path', '')
    if ANNOTATIONS_PATH not in file_path:
        return True, []
    content = tool_input.get('content', '')
    return check_file_content(file_path, content)


def handle_edit(tool_input):
    file_path = tool_input.get('file_path', '')
    if ANNOTATIONS_PATH not in file_path:
        return True, []
    if not os.path.exists(file_path):
        return True, []
    try:
        with open(file_path, 'r') as f:
            current = f.read()
        old = tool_input.get('old_string', '')
        new = tool_input.get('new_string', '')
        if old and old in current:
            result = current.replace(old, new, 1)
            return check_file_content(file_path, result)
    except Exception:
        pass
    return True, []


def handle_bash(tool_input):
    cmd = tool_input.get('command', '')
    # 检测对 annotations 的写入意图
    write_patterns = [
        r'>\s*\S*annotations/structs/',
        r'json\.dump.*annotations/',
        r'open\(.*annotations/structs/.*["\']w',
        r'cp\s+\S+\s+\S*annotations/structs/',
        r'mv\s+\S+\s+\S*annotations/structs/',
        r'tee\s+\S*annotations/',
    ]
    for pat in write_patterns:
        if re.search(pat, cmd):
            print(f"BLOCK: Bash 命令检测到对 annotations 的写入操作。", file=sys.stderr)
            print(f"请使用 Edit/Write 工具修改 annotations 文件，以便 hook 进行合规性验证。", file=sys.stderr)
            print(f"命令: {cmd[:100]}", file=sys.stderr)
            sys.exit(2)
    return True, []


def main():
    try:
        hook_input = json.load(sys.stdin)
    except json.JSONDecodeError:
        sys.exit(0)

    tool_name = hook_input.get('tool_name', '')
    tool_input = hook_input.get('tool_input', {})

    if tool_name == 'Write':
        passed, errors = handle_write(tool_input)
    elif tool_name == 'Edit':
        passed, errors = handle_edit(tool_input)
    elif tool_name == 'Bash':
        passed, errors = handle_bash(tool_input)
    else:
        sys.exit(0)

    if not passed:
        print(f"BLOCK: annotations 验证失败 ({len(errors)} 个错误):", file=sys.stderr)
        for e in errors[:10]:
            print(f"  {e}", file=sys.stderr)
        if len(errors) > 10:
            print(f"  ... +{len(errors)-10} more", file=sys.stderr)
        sys.exit(2)

    sys.exit(0)


if __name__ == '__main__':
    main()
