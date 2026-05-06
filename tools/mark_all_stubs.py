#!/usr/bin/env python3
"""
mark_all_stubs.py - 给 gbengine 中所有函数无条件添加 /* STUB */ 标记

保守策略：先全部标记，再逐个验证移除。
跳过已有 /* STUB */ 标记的函数。
"""

import re
import os
import sys
from pathlib import Path

SRC_DIR = Path(__file__).parent.parent / "src" / "gbengine"


def find_all_functions_and_mark(filepath):
    """解析 C++ 文件，给所有成员函数添加 /* STUB */ 标记"""
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()

    lines = content.split('\n')
    result_lines = []
    i = 0
    stubs_added = 0
    already_marked = 0
    total_functions = 0

    while i < len(lines):
        line = lines[i]

        # 检测函数定义：包含 :: 且后面有 { 的模式
        # 需要识别：返回类型 ClassName::FuncName(params) [const] {
        # 也要处理 { 在下一行的情况

        func_start = detect_function_start(lines, i)

        if func_start is None:
            result_lines.append(line)
            i += 1
            continue

        sig_start, brace_line_idx = func_start

        # 确保我们从 sig_start 开始处理
        if sig_start != i:
            result_lines.append(line)
            i += 1
            continue

        # 找到函数体的结束 }
        brace_count = 0
        func_end = None
        for j in range(brace_line_idx, len(lines)):
            for ch in lines[j]:
                if ch == '{':
                    brace_count += 1
                elif ch == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        func_end = j
                        break
            if func_end is not None:
                break

        if func_end is None:
            result_lines.append(line)
            i += 1
            continue

        total_functions += 1

        # 检查函数体是否已有 /* STUB */ 标记
        body_text = '\n'.join(lines[brace_line_idx:func_end+1])
        if '/* STUB */' in body_text:
            already_marked += 1
            for k in range(i, func_end + 1):
                result_lines.append(lines[k])
            i = func_end + 1
            continue

        # 添加 /* STUB */ 标记
        stubs_added += 1

        # 输出签名行到 { 所在行
        for k in range(i, brace_line_idx + 1):
            result_lines.append(lines[k])

        # 检测缩进
        indent = '    '
        for k in range(brace_line_idx + 1, func_end):
            stripped = lines[k].strip()
            if stripped and not stripped.startswith('//') and not stripped.startswith('/*') and not stripped.startswith('*'):
                indent = lines[k][:len(lines[k]) - len(lines[k].lstrip())]
                break

        # 单行函数体处理: RetType Class::Func() { return x; }
        if brace_line_idx == func_end:
            # { 和 } 在同一行，拆成多行
            brace_line = lines[brace_line_idx]
            open_pos = brace_line.find('{')
            close_pos = brace_line.rfind('}')
            before_brace = brace_line[:open_pos+1]
            inner = brace_line[open_pos+1:close_pos].strip()

            result_lines[-1] = before_brace  # 替换最后添加的行
            result_lines.append(indent + '/* STUB */')
            if inner:
                result_lines.append(indent + inner)
            result_lines.append('}')
        else:
            # 多行函数体，在 { 后插入 /* STUB */
            result_lines.append(indent + '/* STUB */')
            for k in range(brace_line_idx + 1, func_end + 1):
                result_lines.append(lines[k])

        i = func_end + 1

    return result_lines, stubs_added, already_marked, total_functions


def detect_function_start(lines, i):
    """
    检测第 i 行是否是 C++ 成员函数定义的起始行。
    返回 (sig_start, brace_line_idx) 或 None。

    识别模式：
    - 行中有 :: 且有 (
    - 同一行或后续几行有 {
    - 排除 struct/class/enum 定义、注释、预处理指令
    """
    line = lines[i]
    stripped = line.strip()

    # 跳过空行、注释、预处理指令、struct/class/enum/namespace 定义
    if not stripped or stripped.startswith('//') or stripped.startswith('/*') or stripped.startswith('*'):
        return None
    if stripped.startswith('#'):
        return None
    if stripped.startswith('struct ') or stripped.startswith('class ') or stripped.startswith('enum '):
        if '::' not in stripped:
            return None
    if stripped.startswith('namespace ') or stripped.startswith('extern '):
        return None
    if stripped.startswith('typedef '):
        return None
    # 跳过 static 变量定义（无括号）
    if '::' in stripped and '(' not in stripped and '{' not in stripped:
        return None

    # 必须包含 :: (成员函数)
    if '::' not in line:
        return None

    # 必须包含 ( (函数参数)
    if '(' not in line:
        return None

    # 检查是否是函数调用而非定义（前面没有类型）
    # 函数定义通常在行首（可能有返回类型），不在赋值或表达式中
    if '=' in stripped.split('(')[0] and '==' not in stripped.split('(')[0] and '!=' not in stripped.split('(')[0]:
        # 可能是赋值语句中的调用
        before_paren = stripped.split('(')[0]
        if '=' in before_paren and '::' in before_paren.split('=')[1]:
            return None

    # 查找 { 的位置
    # Case 1: { 在当前行
    if '{' in line:
        paren_close = find_matching_paren_close(line)
        brace_pos = line.find('{', paren_close if paren_close >= 0 else 0)
        if brace_pos >= 0:
            return (i, i)

    # Case 2: 查找后续几行的 {
    for offset in range(1, 6):
        if i + offset >= len(lines):
            break
        next_line = lines[i + offset].strip()

        # 如果遇到另一个函数定义或空行后的非延续，停止
        if next_line == '' and offset > 2:
            break

        # 可能是续行（参数列表、const、override 等）
        if '{' in lines[i + offset]:
            return (i, i + offset)

        # 如果遇到了不像是函数签名延续的内容，停止
        if next_line and not next_line.startswith(')') and not next_line.startswith('const') \
           and not next_line.startswith(':') and ',' not in next_line and ')' not in next_line \
           and not next_line.startswith('//'):
            break

    return None


def find_matching_paren_close(line):
    """找到最后一个匹配的 ) 位置"""
    count = 0
    last_close = -1
    for idx, ch in enumerate(line):
        if ch == '(':
            count += 1
        elif ch == ')':
            count -= 1
            last_close = idx
    return last_close


def main():
    dry_run = '--dry-run' in sys.argv

    total_added = 0
    total_already = 0
    total_funcs = 0
    files_modified = 0

    cpp_files = sorted(SRC_DIR.glob('*.cpp'))

    for filepath in cpp_files:
        result_lines, added, already, funcs = find_all_functions_and_mark(filepath)

        if funcs > 0:
            print(f"  {filepath.name}: {funcs} functions, +{added} STUB, {already} already marked")

        total_added += added
        total_already += already
        total_funcs += funcs

        if added > 0 and not dry_run:
            files_modified += 1
            with open(filepath, 'w', encoding='utf-8', newline='\n') as f:
                f.write('\n'.join(result_lines))

    print(f"\n总计: {total_funcs} 个函数")
    print(f"  新标记: {total_added}")
    print(f"  已有标记: {total_already}")
    print(f"  修改文件: {files_modified}")

    if dry_run:
        print("(dry-run 模式, 未实际修改文件)")


if __name__ == '__main__':
    main()
