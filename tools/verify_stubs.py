#!/usr/bin/env python3
"""
verify_stubs.py - 验证 /* STUB */ 标记并移除已确认实现的函数的标记

判断标准:
1. 真 STUB（保留标记）：函数体有效代码只有 (void)0; / return 0; / return NULL; / 空
2. 已实现（移除标记）：函数体有 3+ 行有效代码，且含实质逻辑
3. 存疑（保留标记）：函数体有代码但标注 /* UNCERTAIN */ 或逻辑明显不完整

运行: python tools/verify_stubs.py [--dry-run]
"""

import re
import sys
from pathlib import Path

SRC_DIR = Path(__file__).parent.parent / "src" / "gbengine"

# 真 stub 的函数体模式（去掉注释和空行后）
TRUE_STUB_PATTERNS = [
    r'^\s*\(void\)\s*0\s*;\s*$',
    r'^\s*return\s+0\s*;\s*$',
    r'^\s*return\s+NULL\s*;\s*$',
    r'^\s*return\s+nullptr\s*;\s*$',
    r'^\s*return\s*;\s*$',
]


def extract_functions(filepath):
    """解析文件，提取所有函数及其信息"""
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()

    lines = content.split('\n')
    functions = []
    i = 0

    while i < len(lines):
        line = lines[i]

        # 检测函数定义
        if '::' not in line or '(' not in line:
            i += 1
            continue

        stripped = line.strip()
        if stripped.startswith('//') or stripped.startswith('/*') or stripped.startswith('*'):
            i += 1
            continue
        if stripped.startswith('#') or stripped.startswith('typedef'):
            i += 1
            continue
        if stripped.startswith('struct ') or stripped.startswith('class ') or stripped.startswith('enum '):
            if '::' not in stripped:
                i += 1
                continue

        # 找到 { 的位置
        brace_line = -1
        for offset in range(0, 6):
            if i + offset >= len(lines):
                break
            if '{' in lines[i + offset]:
                brace_line = i + offset
                break

        if brace_line < 0:
            i += 1
            continue

        # 验证这确实是函数定义（{ 在 ) 之后）
        combined = ' '.join(lines[i:brace_line+1])
        if '::' not in combined or '(' not in combined:
            i += 1
            continue

        # 找到匹配的 }
        brace_count = 0
        func_end = -1
        for j in range(brace_line, len(lines)):
            for ch in lines[j]:
                if ch == '{':
                    brace_count += 1
                elif ch == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        func_end = j
                        break
            if func_end >= 0:
                break

        if func_end < 0:
            i += 1
            continue

        # 提取函数信息
        sig_lines = lines[i:brace_line+1]
        sig = ' '.join(l.strip() for l in sig_lines)

        # 提取函数体（{ 和 } 之间）
        body_lines = []
        if brace_line == func_end:
            # 单行函数
            text = lines[brace_line]
            open_pos = text.find('{')
            close_pos = text.rfind('}')
            inner = text[open_pos+1:close_pos].strip()
            if inner:
                body_lines = [inner]
        else:
            for k in range(brace_line + 1, func_end):
                body_lines.append(lines[k])

        # 检查是否有 STUB 标记
        has_stub = any('/* STUB */' in lines[k] for k in range(brace_line, func_end + 1))

        # 检查注释中是否有地址信息（在签名行前几行或签名中）
        has_address = False
        for lookback in range(max(0, i-3), brace_line+1):
            if re.search(r'0x[0-9a-fA-F]{8}', lines[lookback]):
                has_address = True
                break

        # 检查是否有 UNCERTAIN 标注
        has_uncertain = any('UNCERTAIN' in l for l in body_lines)

        functions.append({
            'file': filepath,
            'line_start': i,
            'line_end': func_end,
            'brace_line': brace_line,
            'signature': sig,
            'body_lines': body_lines,
            'has_stub': has_stub,
            'has_address': has_address,
            'has_uncertain': has_uncertain,
        })

        i = func_end + 1

    return functions


def get_effective_lines(body_lines):
    """提取有效代码行（去除空行、注释、STUB 标记）"""
    effective = []
    in_block = False
    for line in body_lines:
        stripped = line.strip()
        if in_block:
            if '*/' in stripped:
                in_block = False
            continue
        if stripped.startswith('/*'):
            if '*/' not in stripped:
                in_block = True
            continue
        if stripped.startswith('//') or stripped == '':
            continue
        effective.append(stripped)
    return effective


def is_true_stub(effective_lines):
    """判断是否为真 stub（只有一行无意义代码或空）"""
    if len(effective_lines) == 0:
        return True
    if len(effective_lines) == 1:
        line = effective_lines[0]
        for pat in TRUE_STUB_PATTERNS:
            if re.match(pat, line):
                return True
    return False


def is_trivial_getter_setter(effective_lines, sig):
    """判断是否为简单的 getter/setter（1-2行，直接返回成员或赋值）"""
    if len(effective_lines) > 2:
        return False
    if len(effective_lines) == 1:
        line = effective_lines[0]
        # return member;
        if re.match(r'^return\s+\w+(\.\w+)*\s*;$', line):
            return True
        # return &member;
        if re.match(r'^return\s+&\w+(\.\w+)*\s*;$', line):
            return True
        # return (type*)member;
        if re.match(r'^return\s+\([^)]+\)\s*\w+\s*;$', line):
            return True
        # member = param;
        if re.match(r'^\w+(\.\w+)*\s*=\s*\w+\s*;$', line):
            return True
    return False


def classify_function(func):
    """
    分类函数:
    - 'true_stub': 真 stub，保留标记
    - 'implemented': 已实现，移除标记
    - 'uncertain': 存疑，保留标记
    """
    effective = get_effective_lines(func['body_lines'])

    # 真 stub
    if is_true_stub(effective):
        return 'true_stub'

    # 有 UNCERTAIN 标注 → 存疑
    if func['has_uncertain']:
        return 'uncertain'

    # 简单 getter/setter (1-2行直接 return member) → 已实现
    if is_trivial_getter_setter(effective, func['signature']):
        return 'implemented'

    # 3行以上有效代码 → 已实现
    if len(effective) >= 3:
        return 'implemented'

    # 2行有效代码且有地址注释 → 已实现
    if len(effective) == 2 and func['has_address']:
        return 'implemented'

    # 其他情况保留
    return 'uncertain'


def remove_stub_marker(filepath, functions_to_unstub):
    """从文件中移除指定函数的 /* STUB */ 标记"""
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    # 收集需要删除的行号（含 /* STUB */ 的行）
    lines_to_remove = set()
    for func in functions_to_unstub:
        for k in range(func['brace_line'], func['line_end'] + 1):
            if k < len(lines) and '/* STUB */' in lines[k]:
                # 如果整行只有 /* STUB */ (加空白), 删除整行
                if lines[k].strip() == '/* STUB */':
                    lines_to_remove.add(k)
                else:
                    # 行内有其他内容，只删 /* STUB */ 部分
                    lines[k] = lines[k].replace('/* STUB */', '').rstrip() + '\n'

    result = [lines[k] for k in range(len(lines)) if k not in lines_to_remove]
    return result


def main():
    dry_run = '--dry-run' in sys.argv
    verbose = '--verbose' in sys.argv or '-v' in sys.argv

    total_functions = 0
    total_stub = 0
    total_implemented = 0
    total_uncertain = 0
    files_modified = 0

    cpp_files = sorted(SRC_DIR.glob('*.cpp'))

    for filepath in cpp_files:
        functions = extract_functions(filepath)
        if not functions:
            continue

        stub_functions = [f for f in functions if f['has_stub']]
        if not stub_functions:
            continue

        to_unstub = []
        file_stub = 0
        file_impl = 0
        file_unc = 0

        for func in stub_functions:
            cls = classify_function(func)
            if cls == 'true_stub':
                file_stub += 1
            elif cls == 'implemented':
                file_impl += 1
                to_unstub.append(func)
            else:
                file_unc += 1

        total_functions += len(stub_functions)
        total_stub += file_stub
        total_implemented += file_impl
        total_uncertain += file_unc

        if to_unstub:
            print(f"  {filepath.name}: -{file_impl} STUB (保留 {file_stub} stub + {file_unc} uncertain)")
            if verbose:
                for f in to_unstub:
                    # 提取函数名
                    m = re.search(r'(\w+::\w+)', f['signature'])
                    name = m.group(1) if m else '?'
                    print(f"    [OK] {name}")

            if not dry_run:
                result = remove_stub_marker(filepath, to_unstub)
                with open(filepath, 'w', encoding='utf-8', newline='') as f:
                    f.writelines(result)
                files_modified += 1

    print(f"\n总计 {total_functions} 个标记函数:")
    print(f"  已实现 (移除 STUB): {total_implemented}")
    print(f"  真 stub (保留):     {total_stub}")
    print(f"  存疑 (保留):        {total_uncertain}")
    print(f"  修改文件: {files_modified}")

    if dry_run:
        print("\n(dry-run 模式, 未实际修改)")


if __name__ == '__main__':
    main()
