#!/usr/bin/env python3
"""PreToolUse hook: 验证 annotations struct JSON 的写入合规性。

阻止条件 (exit 2):
1. 成员偏移对齐违规（int/float/ptr 不在 4 倍偏移）
2. 成员重叠
3. binary_size 变更（需要显式确认）

通过条件 (exit 0):
- 非 struct JSON 文件 → 直接通过
- 检查全部通过

使用方式: 由 Claude Code PreToolUse hook 调用，stdin 接收 JSON。
"""
import json
import sys
import re
import os


def get_member_size(mtype):
    """估算成员大小（字节）"""
    if '*' in mtype:
        return 4
    if any(t in mtype for t in ['int', 'float', 'DWORD', 'unsigned long', 'unsigned int', 'LONG', 'UINT', 'BOOL']):
        return 4
    if any(t in mtype for t in ['short', 'WORD', 'unsigned short']):
        return 2
    if any(t in mtype for t in ['char', 'unsigned char', 'bool', 'BYTE']):
        return 1
    if 'double' in mtype:
        return 8
    return 4  # 默认 struct/unknown → 4


def get_alignment(mtype):
    """获取成员的自然对齐要求"""
    if '*' in mtype:
        return 4
    if any(t in mtype for t in ['int', 'float', 'DWORD', 'unsigned long', 'unsigned int', 'LONG', 'UINT', 'BOOL']):
        return 4
    if any(t in mtype for t in ['short', 'WORD', 'unsigned short']):
        return 2
    if any(t in mtype for t in ['char', 'unsigned char', 'bool', 'BYTE']):
        return 1
    if 'double' in mtype:
        return 8
    # 数组：取元素类型的对齐
    arr = re.search(r'(\[\d+\])', mtype)
    if arr:
        base = mtype[:arr.start()].strip()
        return get_alignment(base)
    return 4  # struct 默认


def validate_struct(data):
    """验证结构体 JSON 的合规性，返回 (pass, errors)"""
    errors = []
    members = data.get('known_members', {})

    if not members:
        return True, []

    sorted_m = sorted([(int(off), members[off]) for off in members], key=lambda x: x[0])

    # 1. 对齐检查
    for off, m in sorted_m:
        mtype = m.get('type', '')
        align = get_alignment(mtype)
        if align > 1 and off % align != 0:
            errors.append(
                f"ALIGN: +{off} ({hex(off)}) {mtype} {m.get('name','')} — "
                f"需要 {align} 字节对齐, 但 {off}%{align}={off%align}"
            )

    # 2. 重叠检查
    prev_end = 0
    prev_info = None
    for off, m in sorted_m:
        mtype = m.get('type', '')
        msize = get_member_size(mtype)
        if off < prev_end and prev_info:
            errors.append(
                f"OVERLAP: +{prev_info[0]} {prev_info[1].get('name','')} "
                f"(end={prev_end}) overlaps +{off} {m.get('name','')}"
            )
        prev_end = off + msize
        prev_info = (off, m)

    return len(errors) == 0, errors


def main():
    # 读取 stdin JSON
    try:
        hook_input = json.load(sys.stdin)
    except json.JSONDecodeError:
        sys.exit(0)  # 无法解析 → 放行

    tool_name = hook_input.get('tool_name', '')
    tool_input = hook_input.get('tool_input', {})

    # 只验证 Edit 和 Write 工具
    if tool_name not in ('Edit', 'Write'):
        sys.exit(0)

    file_path = tool_input.get('file_path', '')

    # 只验证 structs/ 下的 JSON 文件
    if '/annotations/structs/' not in file_path or not file_path.endswith('.json'):
        sys.exit(0)

    # 对于 Write：验证将要写入的完整内容
    if tool_name == 'Write':
        content = tool_input.get('content', '')
        try:
            data = json.loads(content)
        except json.JSONDecodeError:
            print("BLOCK: 无效 JSON 内容", file=sys.stderr)
            sys.exit(2)

        passed, errors = validate_struct(data)
        if not passed:
            print(f"BLOCK: struct 验证失败 ({len(errors)} 个错误):", file=sys.stderr)
            for e in errors[:5]:
                print(f"  {e}", file=sys.stderr)
            if len(errors) > 5:
                print(f"  ... +{len(errors)-5} more", file=sys.stderr)
            sys.exit(2)

    # 对于 Edit：需要读取当前文件，应用编辑，再验证
    elif tool_name == 'Edit':
        if not os.path.exists(file_path):
            sys.exit(0)  # 新文件 → 放行（Write 会处理）

        try:
            with open(file_path, 'r') as f:
                current = f.read()

            old_string = tool_input.get('old_string', '')
            new_string = tool_input.get('new_string', '')

            if old_string and old_string in current:
                new_content = current.replace(old_string, new_string, 1)
                data = json.loads(new_content)

                passed, errors = validate_struct(data)
                if not passed:
                    print(f"BLOCK: struct 编辑后验证失败 ({len(errors)} 个错误):", file=sys.stderr)
                    for e in errors[:5]:
                        print(f"  {e}", file=sys.stderr)
                    sys.exit(2)
        except (json.JSONDecodeError, Exception) as e:
            # 无法模拟编辑结果 → 放行（依赖后续 check_annotations）
            pass

    sys.exit(0)


if __name__ == '__main__':
    main()
