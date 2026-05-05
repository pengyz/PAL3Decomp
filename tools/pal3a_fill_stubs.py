#!/usr/bin/env python3
"""
PAL3A Stub 自动填充工具。

读取 Ghidra 反编译 JSON 导出，清理代码，替换 stub 函数体。

用法:
    python tools/pal3a_fill_stubs.py --module script
    python tools/pal3a_fill_stubs.py --module gamebase
    python tools/pal3a_fill_stubs.py --file src/pal3a/script/PalScript.cpp
    python tools/pal3a_fill_stubs.py --dry-run --module script
    python tools/pal3a_fill_stubs.py --list-modules
"""

import argparse
import json
import os
import re
import sys
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm" / "pal3a"
DECOMP_DIR = ASM_DIR / "decomp"
PDB_EXPORT = ASM_DIR / "pdb_export.json"
SRC_DIR = PROJECT_ROOT / "src" / "pal3a"


def load_pdb_index():
    """构建函数名 → (地址, 源文件) 的索引"""
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        data = json.load(f)

    index = {}
    for func in data['functions']:
        name = func.get('name', '')
        addr = func.get('address', '')
        src = func.get('source_file', '')
        if name and addr:
            index[name] = {
                'address': addr,
                'source_file': src,
                'size': func.get('size', 0),
                'mangled': func.get('mangled_name', ''),
            }
    return index


def build_decomp_index():
    """构建函数名 → JSON 文件路径的索引"""
    index = {}
    if not DECOMP_DIR.exists():
        return index

    for json_file in DECOMP_DIR.glob("*.json"):
        if json_file.name.startswith('_'):
            continue
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
            name = data.get('name', '')
            addr = data.get('address', '')
            if name:
                index[name] = json_file
                if addr:
                    index[addr] = json_file
        except (json.JSONDecodeError, IOError):
            continue
    return index


def clean_decompiled_c(raw_c, func_name):
    """清理 Ghidra 反编译输出，提取函数体"""
    if not raw_c:
        return None

    lines = raw_c.split('\n')

    # Find the function body braces
    brace_depth = 0
    body_start = -1
    body_end = -1

    for i, line in enumerate(lines):
        for ch in line:
            if ch == '{':
                if brace_depth == 0:
                    body_start = i
                brace_depth += 1
            elif ch == '}':
                brace_depth -= 1
                if brace_depth == 0:
                    body_end = i
                    break
        if body_end >= 0:
            break

    if body_start < 0 or body_end < 0:
        return None

    body_lines = lines[body_start + 1:body_end]
    body = '\n'.join(body_lines)

    # Remove Ghidra internal comments (address/ordinal/mangled name)
    body = re.sub(r'/\*\s*0x[0-9a-fA-F]+\s+\d+\s+\?.*?\*/', '', body)

    # Replace Ghidra undefined types
    body = body.replace('undefined4', 'int')
    body = body.replace('undefined2', 'short')
    body = body.replace('undefined1', 'char')
    body = body.replace('undefined8', '__int64')
    body = body.replace('undefined', 'int')
    body = body.replace('longlong', '__int64')
    body = body.replace('ulonglong', 'unsigned __int64')

    # Remove calling convention annotations in casts
    body = re.sub(r'\(__thiscall\s*\*\)', '(*)', body)
    body = re.sub(r'\(__cdecl\s*\*\)', '(*)', body)

    # Clean up extra blank lines
    body = re.sub(r'\n\s*\n\s*\n', '\n\n', body)

    if not body.strip():
        return None

    return body


def parse_stub_functions(cpp_path):
    """解析 .cpp 文件中的 stub 函数位置"""
    with open(cpp_path, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()
    lines = content.split('\n')

    stubs = []
    i = 0
    while i < len(lines):
        if '/* stub */' in lines[i]:
            # Find the opening brace (should be on a line before or at the stub marker)
            brace_line = -1
            for j in range(max(0, i - 5), i + 1):
                if '{' in lines[j]:
                    brace_line = j
                    break

            if brace_line < 0:
                i += 1
                continue

            # Find function signature above the brace
            sig_start = brace_line
            if lines[brace_line].strip() == '{':
                sig_start = brace_line - 1
            while sig_start > 0 and lines[sig_start - 1].strip() and \
                  not lines[sig_start - 1].strip().startswith('//') and \
                  not lines[sig_start - 1].strip().startswith('#') and \
                  not lines[sig_start - 1].strip().endswith('}') and \
                  not lines[sig_start - 1].strip().endswith(';'):
                sig_start -= 1

            # Find closing brace
            brace_depth = 0
            end_line = -1
            for j in range(brace_line, len(lines)):
                for ch in lines[j]:
                    if ch == '{':
                        brace_depth += 1
                    elif ch == '}':
                        brace_depth -= 1
                        if brace_depth == 0:
                            end_line = j
                            break
                if end_line >= 0:
                    break

            if end_line < 0:
                i += 1
                continue

            # Extract function name from signature
            sig_text = ' '.join(lines[sig_start:brace_line + 1])
            sig_text = sig_text.split('{')[0].strip()

            # Match Class::Method or plain FuncName before (
            match = re.search(r'(~?\w+(?:::\~?\w+)?)\s*\(', sig_text)
            func_name = match.group(1) if match else None

            if func_name:
                stubs.append({
                    'name': func_name,
                    'signature': sig_text,
                    'sig_start': sig_start,
                    'brace_line': brace_line,
                    'end_line': end_line,
                })

        i += 1

    return stubs


def fill_file(cpp_path, decomp_index, pdb_index, dry_run=False):
    """填充单个 .cpp 文件中的 stub 函数"""
    stubs = parse_stub_functions(cpp_path)
    if not stubs:
        return 0

    with open(cpp_path, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.read().split('\n')

    filled = 0
    offset = 0

    for stub in stubs:
        func_name = stub['name']

        # Try to find matching decomp JSON
        json_path = decomp_index.get(func_name)
        if not json_path:
            continue

        try:
            with open(json_path, 'r', encoding='utf-8') as f:
                decomp_data = json.load(f)
        except (json.JSONDecodeError, IOError):
            continue

        raw_c = decomp_data.get('decompiled_c', '')
        if not raw_c:
            continue

        body = clean_decompiled_c(raw_c, func_name)
        if not body:
            continue

        if dry_run:
            print(f"  [FILL] {func_name} ({decomp_data.get('size_bytes', '?')} bytes)")
            filled += 1
            continue

        # Replace the stub body
        brace_line = stub['brace_line'] + offset
        end_line = stub['end_line'] + offset

        # Build replacement: keep signature, replace body content
        new_body_lines = [lines[brace_line].split('{')[0] + '{']
        new_body_lines.append('    /* GHIDRA */')
        for body_line in body.split('\n'):
            new_body_lines.append(body_line)
        new_body_lines.append('}')

        old_count = end_line - brace_line + 1
        lines[brace_line:end_line + 1] = new_body_lines
        offset += len(new_body_lines) - old_count
        filled += 1

    if not dry_run and filled > 0:
        with open(cpp_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))

    return filled


def get_module_files(module_name):
    """获取模块下的所有 .cpp 文件"""
    if module_name == '(root)':
        return [f for f in SRC_DIR.glob("*.cpp")]
    else:
        module_dir = SRC_DIR / module_name
        if module_dir.exists():
            return list(module_dir.glob("*.cpp"))
        return []


def main():
    parser = argparse.ArgumentParser(description="PAL3A Stub 自动填充")
    parser.add_argument('--module', metavar='NAME',
                        help='填充指定模块 (script, gamebase, ui, ...)')
    parser.add_argument('--file', metavar='PATH',
                        help='填充指定 .cpp 文件')
    parser.add_argument('--dry-run', action='store_true',
                        help='仅显示将被替换的函数，不实际修改')
    parser.add_argument('--list-modules', action='store_true',
                        help='列出可用模块')
    args = parser.parse_args()

    if args.list_modules:
        print("可用模块:")
        for d in sorted(SRC_DIR.iterdir()):
            if d.is_dir():
                cpp_count = len(list(d.glob("*.cpp")))
                if cpp_count > 0:
                    print(f"  {d.name:20s} ({cpp_count} .cpp files)")
        return

    # Build decomp index
    print("[*] 构建反编译索引...")
    decomp_index = build_decomp_index()
    if not decomp_index:
        print("[!] 未找到反编译输出。请先运行:")
        print("    python tools/ghidra_analyze_pal3a.py --export-all")
        sys.exit(1)
    print(f"    索引: {len(decomp_index)} 个条目")

    # Build PDB index
    pdb_index = load_pdb_index()
    print(f"    PDB:  {len(pdb_index)} 个函数")

    # Determine files to process
    if args.file:
        files = [Path(args.file)]
    elif args.module:
        files = get_module_files(args.module)
        if not files:
            print(f"[!] 模块 '{args.module}' 无 .cpp 文件")
            sys.exit(1)
    else:
        parser.print_help()
        return

    print(f"[*] 处理 {len(files)} 个文件...")
    if args.dry_run:
        print("    (dry-run 模式)")
    print()

    total_filled = 0
    for cpp_path in sorted(files):
        rel_path = cpp_path.relative_to(PROJECT_ROOT)
        filled = fill_file(cpp_path, decomp_index, pdb_index, dry_run=args.dry_run)
        if filled > 0:
            status = 'would be filled' if args.dry_run else 'filled'
            print(f"  {rel_path}: {filled} functions {status}")
            total_filled += filled

    print()
    verb = '将被' if args.dry_run else '已'
    marker = '*' if args.dry_run else '+'
    print(f"[{marker}] 总计: {total_filled} 个函数{verb}填充")


if __name__ == '__main__':
    main()
