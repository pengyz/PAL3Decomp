#!/usr/bin/env python3
"""
mark_stubs.py - 给 gbengine 中的 stub 函数添加 /* STUB */ 标记

Stub 函数定义：函数体只含以下内容之一（忽略空行和注释）：
- (void)0;
- return 0;
- return NULL; / return nullptr;
- return; (void 函数)
- 完全空的函数体
- 只有一句简单 return (如 return member;)

不标记的情况：
- 已经有 /* STUB */ 标记
- 函数体有 2 行以上有效代码（非注释非空行）
- 内联 getter/setter（return this->field）保留但不标记——它们是完整实现
"""

import re
import os
import sys
from pathlib import Path

SRC_DIR = Path(__file__).parent.parent / "src" / "gbengine"

# 匹配 stub 函数体的模式（去掉空白和注释后）
STUB_PATTERNS = [
    r'^\s*\(void\)\s*0\s*;\s*$',
    r'^\s*return\s+0\s*;\s*$',
    r'^\s*return\s+NULL\s*;\s*$',
    r'^\s*return\s+nullptr\s*;\s*$',
    r'^\s*return\s*;\s*$',
    r'^\s*$',  # 完全空
]

def is_comment_line(line):
    stripped = line.strip()
    return stripped.startswith('//') or stripped.startswith('/*') or stripped.startswith('*')

def is_empty_or_comment(line):
    stripped = line.strip()
    return stripped == '' or is_comment_line(line)

def extract_effective_lines(body_lines):
    """提取函数体中的有效代码行（去除空行和注释）"""
    effective = []
    in_block_comment = False
    for line in body_lines:
        stripped = line.strip()
        if in_block_comment:
            if '*/' in stripped:
                in_block_comment = False
            continue
        if stripped.startswith('/*'):
            if '*/' not in stripped:
                in_block_comment = True
            continue
        if stripped.startswith('//') or stripped == '':
            continue
        effective.append(stripped)
    return effective

def is_stub_body(effective_lines):
    """判断函数体是否为 stub"""
    if len(effective_lines) == 0:
        return True
    if len(effective_lines) == 1:
        line = effective_lines[0]
        # 典型 stub 模式
        if re.match(r'^\(void\)\s*0\s*;$', line):
            return True
        if re.match(r'^return\s+0\s*;$', line):
            return True
        if re.match(r'^return\s+NULL\s*;$', line):
            return True
        if re.match(r'^return\s+nullptr\s*;$', line):
            return True
        if re.match(r'^return\s*;$', line):
            return True
    return False

def find_functions_and_mark(filepath):
    """解析 C++ 文件，找到 stub 函数并添加标记"""
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    modified = False
    result_lines = []
    i = 0
    stubs_found = 0
    already_marked = 0

    while i < len(lines):
        line = lines[i]

        # 检测函数定义的开始：
        # 模式: 返回类型 类名::函数名(...) { 或 返回类型 类名::函数名(...) const {
        # 函数体开始于 { 所在行

        # 查找包含 '::' 且紧跟 '{' 的行（可能在同一行或下一行）
        # 简化：找到以 '{' 结尾的行，且前面有 '::' 和 ')'

        stripped = line.rstrip()

        # 检查是否是函数定义开始
        is_func_start = False
        open_brace_line = i

        # Case 1: ... ClassName::FuncName(...) { 在同一行
        if '::' in line and '{' in line and ')' in line:
            # 确保 { 在 ) 之后
            paren_pos = line.rfind(')')
            brace_pos = line.find('{', paren_pos if paren_pos >= 0 else 0)
            if brace_pos >= 0 and paren_pos >= 0 and brace_pos > paren_pos:
                is_func_start = True
                open_brace_line = i

        # Case 2: ... ClassName::FuncName(...)\n{
        elif '::' in line and ')' in line.rstrip() or (')' in line and 'const' in lines[i+1] if i+1 < len(lines) else False):
            pass  # 下面处理

        # Case 3: 函数签名在一行，{ 在下一行
        if not is_func_start and i + 1 < len(lines):
            next_stripped = lines[i + 1].strip()
            if '::' in line and ')' in line and next_stripped == '{':
                is_func_start = True
                open_brace_line = i + 1
            # 处理 const/override 等在括号和花括号之间的情况
            elif '::' in line and ')' in line:
                # 检查下一行是否是 "const {"  或 "{"
                if next_stripped.endswith('{') and ('const' in next_stripped or next_stripped == '{'):
                    is_func_start = True
                    open_brace_line = i + 1

        # Case 4: 多行签名 - 检查前一行有 :: 当前行有 ) 和 {
        if not is_func_start and '{' in line:
            # 回看几行找 ::
            for lookback in range(1, min(5, i + 1)):
                prev = lines[i - lookback]
                if '::' in prev and ('(' in prev or '(' in ''.join(lines[i-lookback:i+1])):
                    is_func_start = True
                    open_brace_line = i
                    break

        if not is_func_start:
            result_lines.append(line)
            i += 1
            continue

        # 找到函数开始，现在提取函数体
        # 从 open_brace_line 的 { 开始，计数括号直到匹配的 }
        brace_count = 0
        func_start = i
        body_start = open_brace_line
        j = body_start
        body_lines_content = []
        found_end = False

        # 计算 open_brace_line 中 { 之前的内容
        brace_line = lines[body_start]
        brace_pos = brace_line.find('{')

        # 从 { 开始计数
        for j in range(body_start, len(lines)):
            for ch in lines[j]:
                if ch == '{':
                    brace_count += 1
                elif ch == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        found_end = True
                        break
            if found_end:
                break

        if not found_end:
            result_lines.append(line)
            i += 1
            continue

        func_end = j  # 包含 } 的行

        # 提取函数体内容（{ 之后到 } 之前）
        body_content_lines = []
        for k in range(body_start, func_end + 1):
            body_content_lines.append(lines[k])

        # 去掉首尾的 { } 行，提取中间内容
        inner_lines = []
        if body_start == func_end:
            # 单行函数 { ... }
            text = lines[body_start]
            brace_open = text.find('{')
            brace_close = text.rfind('}')
            if brace_open >= 0 and brace_close > brace_open:
                inner_text = text[brace_open+1:brace_close].strip()
                if inner_text:
                    inner_lines = [inner_text]
        else:
            # 多行函数体
            # 第一行：{ 之后的内容
            first_line = lines[body_start]
            after_brace = first_line[first_line.find('{')+1:].strip()
            if after_brace:
                inner_lines.append(after_brace)
            # 中间行
            for k in range(body_start + 1, func_end):
                inner_lines.append(lines[k].rstrip('\n').rstrip('\r'))
            # 最后一行：} 之前的内容
            last_line = lines[func_end]
            before_brace = last_line[:last_line.rfind('}')].strip()
            if before_brace:
                inner_lines.append(before_brace)

        # 检查是否已有 STUB 标记
        has_stub_marker = any('/* STUB */' in l for l in lines[func_start:func_end+1])

        if has_stub_marker:
            already_marked += 1
            for k in range(func_start, func_end + 1):
                result_lines.append(lines[k])
            i = func_end + 1
            continue

        # 提取有效代码行
        effective = extract_effective_lines(inner_lines)

        # 判断是否为 stub
        if is_stub_body(effective):
            stubs_found += 1
            modified = True

            # 插入 /* STUB */ 标记
            # 输出函数签名行到 { 行
            for k in range(func_start, body_start + 1):
                result_lines.append(lines[k])

            # 在 { 之后插入标记
            if body_start == func_end:
                # 单行函数，改为多行
                indent = '    '
                brace_line = lines[body_start]
                brace_pos = brace_line.find('{')
                prefix = brace_line[:brace_pos+1]
                result_lines[-1] = prefix + '\n'
                result_lines.append(indent + '/* STUB */\n')
                # 保留原始函数体内容
                for el in effective:
                    result_lines.append(indent + el + '\n')
                result_lines.append('}\n')
            else:
                # 多行函数，在 { 下一行插入 /* STUB */
                indent = '    '
                # 检测现有缩进
                for k in range(body_start + 1, func_end):
                    stripped_k = lines[k].strip()
                    if stripped_k and not stripped_k.startswith('//') and not stripped_k.startswith('/*'):
                        # 用现有行的缩进
                        indent = lines[k][:len(lines[k]) - len(lines[k].lstrip())]
                        break

                result_lines.append(indent + '/* STUB */\n')
                for k in range(body_start + 1, func_end + 1):
                    result_lines.append(lines[k])

            i = func_end + 1
        else:
            # 不是 stub，原样保留
            for k in range(func_start, func_end + 1):
                result_lines.append(lines[k])
            i = func_end + 1

    return result_lines, modified, stubs_found, already_marked

def main():
    dry_run = '--dry-run' in sys.argv

    total_stubs = 0
    total_already = 0
    total_files_modified = 0

    cpp_files = sorted(SRC_DIR.glob('*.cpp'))

    for filepath in cpp_files:
        result_lines, modified, stubs_found, already_marked = find_functions_and_mark(filepath)

        if stubs_found > 0 or already_marked > 0:
            print(f"  {filepath.name}: {stubs_found} stubs marked, {already_marked} already marked")

        total_stubs += stubs_found
        total_already += already_marked

        if modified and not dry_run:
            total_files_modified += 1
            with open(filepath, 'w', encoding='utf-8', newline='\n') as f:
                f.writelines(result_lines)

    print(f"\n总计: {total_stubs} 个 stub 函数已标记, {total_already} 个已有标记")
    print(f"修改了 {total_files_modified} 个文件")

    if dry_run:
        print("(dry-run 模式, 未实际修改文件)")

if __name__ == '__main__':
    main()
