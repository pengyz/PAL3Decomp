#!/usr/bin/env python3
"""
gbengine.dll Stub 自动填充工具 (IDA Hex-Rays 版)

读取 IDA 反编译 JSON 导出 (asm/gbengine_ida/)，
匹配函数名，替换 /* stub */ 函数体为 IDA 反编译代码。

用法:
    python tools/gbengine_fill_stubs.py --file src/gbengine/gbCamera.cpp
    python tools/gbengine_fill_stubs.py --all --dry-run
    python tools/gbengine_fill_stubs.py --all
    python tools/gbengine_fill_stubs.py --all --no-quality-gate
    python tools/gbengine_fill_stubs.py --quality-report
"""

import argparse
import json
import os
import re
import sys
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
DECOMP_DIR = PROJECT_ROOT / "asm" / "gbengine_ida"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"

MAX_RAW_OFFSETS = 3
MAX_DWORD_REFS = 2
MAX_USERPURGE = 0


def build_decomp_index():
    """构建 函数名 → json文件路径 的索引。

    gbengine 的 IDA 导出使用 demangled 名称格式:
      "Class::Method(args)" 或 "FreeFunction(args)"
    我们需要将其与源码中的 Class::Method 匹配。
    """
    index = {}
    if not DECOMP_DIR.exists():
        print(f"[!] 反编译目录不存在: {DECOMP_DIR}")
        return index

    for json_file in DECOMP_DIR.glob("*.json"):
        if json_file.name.startswith('_'):
            continue
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                head = f.read(512)
            m = re.search(r'"name"\s*:\s*"([^"]*)"', head)
            if not m:
                continue
            full_name = m.group(1)
            if not full_name:
                continue

            # "Class::Method(args)" -> "Class::Method"
            # "FreeFunc(args)" -> "FreeFunc"
            paren_idx = full_name.find('(')
            if paren_idx > 0:
                short_name = full_name[:paren_idx]
            else:
                short_name = full_name

            # Keep the larger file if duplicate
            if short_name not in index:
                index[short_name] = json_file
            else:
                existing_size = index[short_name].stat().st_size
                new_size = json_file.stat().st_size
                if new_size > existing_size:
                    index[short_name] = json_file
        except (IOError, OSError):
            continue

    return index


def load_decomp_data(json_path):
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            return json.load(f)
    except (json.JSONDecodeError, IOError):
        return None


def check_quality(decompiled_c):
    issues = {
        'raw_offsets': 0,
        'dword_refs': 0,
        'userpurge': 0,
        'memory_macro': 0,
    }

    if not decompiled_c:
        return False, issues

    issues['raw_offsets'] = len(re.findall(
        r'\*\(_(?:DWORD|WORD|BYTE|QWORD)\s*\*\)\s*\(', decompiled_c))
    issues['dword_refs'] = len(re.findall(
        r'\b(?:dword|byte|word|flt|qword|unk)_[0-9A-Fa-f]+\b', decompiled_c))
    issues['userpurge'] = len(re.findall(
        r'__user(?:purge|call)', decompiled_c))
    issues['memory_macro'] = len(re.findall(r'MEMORY\[', decompiled_c))

    passed = (issues['raw_offsets'] <= MAX_RAW_OFFSETS and
              issues['dword_refs'] <= MAX_DWORD_REFS and
              issues['userpurge'] <= MAX_USERPURGE and
              issues['memory_macro'] == 0)

    return passed, issues


def extract_body(decompiled_c):
    if not decompiled_c:
        return None

    lines = decompiled_c.split('\n')
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

    # Remove IDA stack layout comments
    body = re.sub(r'\s*//\s*\[esp[^\n]*$', '', body, flags=re.MULTILINE)
    # Remove IDA variable type comments: // eax, edx, etc
    body = re.sub(r'\s*//\s*[a-z]{2,3}$', '', body, flags=re.MULTILINE)
    # Collapse multiple blank lines
    body = re.sub(r'\n\s*\n\s*\n', '\n\n', body)

    if not body.strip():
        return None

    return body


def parse_stub_functions(cpp_path):
    with open(cpp_path, 'r', encoding='utf-8', errors='replace') as f:
        content = f.read()
    lines = content.split('\n')

    stubs = []
    i = 0
    while i < len(lines):
        if '/* stub */' not in lines[i]:
            i += 1
            continue

        # Find opening brace
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
        for j in range(brace_line, min(len(lines), brace_line + 30)):
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

        # Extract signature text
        sig_text = ' '.join(lines[sig_start:brace_line + 1]).split('{')[0].strip()

        # Parse Class::Method or ~Dtor or plain function
        match = re.search(r'(\w+)::(~?\w+)\s*\(', sig_text)
        if match:
            func_name = f"{match.group(1)}::{match.group(2)}"
        else:
            match = re.search(r'(\w+)\s*\(', sig_text)
            func_name = match.group(1) if match else None

        if func_name:
            stubs.append({
                'name': func_name,
                'sig_text': sig_text,
                'brace_line': brace_line,
                'end_line': end_line,
            })

        i = end_line + 1

    return stubs


def fill_file(cpp_path, decomp_index, dry_run=False, quality_gate=True,
              quality_stats=None):
    stubs = parse_stub_functions(cpp_path)
    if not stubs:
        return 0, 0, 0, []

    with open(cpp_path, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.read().split('\n')

    filled = 0
    not_found = 0
    rejected = 0
    not_found_names = []
    offset = 0

    for stub in stubs:
        func_name = stub['name']

        json_path = decomp_index.get(func_name)
        # Destructor: stub uses ~ClassName, IDA might use _ClassName
        if not json_path and '::~' in func_name:
            alt_name = func_name.replace('::~', '::_')
            json_path = decomp_index.get(alt_name)
        # Also try with tilde
        if not json_path and '::~' in func_name:
            alt_name = func_name.replace('::', '::~')
            json_path = decomp_index.get(alt_name)

        if not json_path:
            not_found += 1
            not_found_names.append(func_name)
            continue

        decomp = load_decomp_data(json_path)
        if not decomp:
            not_found += 1
            not_found_names.append(func_name)
            continue

        raw_c = decomp.get('decompiled_c', '')

        if quality_gate:
            passed, issues = check_quality(raw_c)
            if quality_stats is not None:
                for k, v in issues.items():
                    quality_stats[k] = quality_stats.get(k, 0) + v
                quality_stats['total_checked'] = quality_stats.get('total_checked', 0) + 1
                if passed:
                    quality_stats['passed'] = quality_stats.get('passed', 0) + 1
                else:
                    quality_stats['rejected'] = quality_stats.get('rejected', 0) + 1
            if not passed:
                rejected += 1
                continue

        body = extract_body(raw_c)
        if not body:
            not_found += 1
            not_found_names.append(func_name)
            continue

        if dry_run:
            filled += 1
            continue

        # Replace stub body
        brace_line = stub['brace_line'] + offset
        end_line = stub['end_line'] + offset

        brace_prefix = lines[brace_line].split('{')[0]
        new_lines = [brace_prefix + '{']
        for body_line in body.split('\n'):
            new_lines.append(body_line)
        new_lines.append('}')

        old_count = end_line - brace_line + 1
        lines[brace_line:end_line + 1] = new_lines
        offset += len(new_lines) - old_count
        filled += 1

    if not dry_run and filled > 0:
        with open(cpp_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))

    return filled, not_found, rejected, not_found_names


def main():
    parser = argparse.ArgumentParser(description='gbengine stub 填充 (IDA Hex-Rays)')
    parser.add_argument('--file', help='填充指定文件')
    parser.add_argument('--all', action='store_true', help='填充所有 stub 文件')
    parser.add_argument('--dry-run', action='store_true', help='只统计不写入')
    parser.add_argument('--no-quality-gate', action='store_true', help='关闭质量门控')
    parser.add_argument('--quality-report', action='store_true', help='质量报告')
    args = parser.parse_args()

    if not args.file and not args.all and not args.quality_report:
        parser.print_help()
        sys.exit(1)

    print("[*] 构建反编译索引...")
    decomp_index = build_decomp_index()
    print(f"    索引: {len(decomp_index)} 个函数")

    if not decomp_index:
        print("[!] 没有找到反编译数据。请先运行 IDA 导出脚本。")
        sys.exit(1)

    quality_gate = not args.no_quality_gate
    quality_stats = defaultdict(int)

    if args.quality_report:
        total_stubs = 0
        all_not_found = []
        for cpp_file in sorted(SRC_DIR.glob("*.cpp")):
            stubs = parse_stub_functions(cpp_file)
            for stub in stubs:
                total_stubs += 1
                func_name = stub['name']
                json_path = decomp_index.get(func_name)
                if not json_path and '::~' in func_name:
                    json_path = decomp_index.get(func_name.replace('::~', '::_'))
                if not json_path:
                    all_not_found.append(func_name)
                    continue
                decomp = load_decomp_data(json_path)
                if decomp:
                    check_quality(decomp.get('decompiled_c', ''))
                    quality_stats['total_checked'] += 1

        print(f"\n[*] 质量报告:")
        print(f"    总 stub 函数: {total_stubs}")
        print(f"    IDA 有反编译: {quality_stats['total_checked']}")
        print(f"    IDA 无数据: {len(all_not_found)}")
        if all_not_found[:20]:
            print(f"    找不到的函数 (前20):")
            for name in all_not_found[:20]:
                print(f"      - {name}")
        return

    if args.file:
        cpp_path = Path(args.file)
        if not cpp_path.is_absolute():
            cpp_path = PROJECT_ROOT / cpp_path
        if not cpp_path.exists():
            print(f"[!] 文件不存在: {cpp_path}")
            sys.exit(1)

        filled, not_found, rejected, not_found_names = fill_file(
            cpp_path, decomp_index, dry_run=args.dry_run,
            quality_gate=quality_gate, quality_stats=quality_stats)

        action = "可填充" if args.dry_run else "已填充"
        print(f"\n[*] {cpp_path.name}: {action}={filled}, 未找到={not_found}, 拒绝={rejected}")
        if not_found_names:
            print(f"    未找到: {', '.join(not_found_names[:10])}")

    elif args.all:
        total_filled = 0
        total_not_found = 0
        total_rejected = 0
        all_not_found_names = []

        for cpp_file in sorted(SRC_DIR.glob("*.cpp")):
            filled, not_found, rejected, not_found_names = fill_file(
                cpp_file, decomp_index, dry_run=args.dry_run,
                quality_gate=quality_gate, quality_stats=quality_stats)

            if filled > 0 or not_found > 0:
                action = "可填充" if args.dry_run else "已填充"
                print(f"  {cpp_file.name}: {action}={filled}, 未找到={not_found}, 拒绝={rejected}")

            total_filled += filled
            total_not_found += not_found
            total_rejected += rejected
            all_not_found_names.extend(not_found_names)

        action = "可填充" if args.dry_run else "已填充"
        print(f"\n[*] 总计: {action}={total_filled}, 未找到={total_not_found}, 拒绝={total_rejected}")


if __name__ == '__main__':
    main()
