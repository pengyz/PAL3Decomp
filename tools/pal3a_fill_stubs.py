#!/usr/bin/env python3
"""
PAL3A Stub 自动填充工具。

读取 IDA 反编译 JSON 导出 (asm/pal3a/decomp/)，
匹配函数名，替换 /* stub */ 函数体为 IDA 反编译代码。

质量门控:
  默认只填充质量合格的函数（无硬编码偏移、无 dword_ 全局变量）。
  使用 --no-quality-gate 可关闭门控强制填充所有。
  使用 --quality-report 查看质量统计。

全局变量替换:
  如果存在 asm/pal3a/globals_export.json，自动将 dword_XXXXX 等
  IDA 自动命名替换为 PDB 中的正式名称。

用法:
    python tools/pal3a_fill_stubs.py --all --dry-run       # 统计可填充数量
    python tools/pal3a_fill_stubs.py --all                 # 填充质量合格的
    python tools/pal3a_fill_stubs.py --all --no-quality-gate  # 填充所有（忽略质量）
    python tools/pal3a_fill_stubs.py --quality-report      # 查看质量统计
    python tools/pal3a_fill_stubs.py --file src/pal3a/Archive.cpp
    python tools/pal3a_fill_stubs.py --module combat
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
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3a" / "decomp"
SRC_DIR = PROJECT_ROOT / "src" / "pal3a"
GLOBALS_EXPORT = PROJECT_ROOT / "asm" / "pal3a" / "globals_export.json"

# Quality gate thresholds
MAX_RAW_OFFSETS = 3       # 最多允许的 *(type*)(ptr + N) 硬编码偏移
MAX_DWORD_REFS = 0        # 最多允许的 dword_XXXXX 引用
MAX_USERPURGE = 0         # 不允许 __userpurge/__usercall


def build_decomp_index():
    """构建 函数名 → json文件路径 的轻量索引。
    只读取每个JSON的name字段（文件头部），不加载decompiled_c。"""
    index = {}
    if not DECOMP_DIR.exists():
        return index

    for json_file in DECOMP_DIR.glob("*.json"):
        if json_file.name.startswith('_'):
            continue
        try:
            # 只读前200字节获取name字段，避免加载完整decompiled_c
            with open(json_file, 'r', encoding='utf-8') as f:
                head = f.read(256)
            m = re.search(r'"name"\s*:\s*"([^"]*)"', head)
            if not m:
                continue
            name = m.group(1)
            if not name:
                continue
            # 保留文件更大的版本
            if name not in index:
                index[name] = json_file
            else:
                existing_size = index[name].stat().st_size
                new_size = json_file.stat().st_size
                if new_size > existing_size:
                    index[name] = json_file
        except (IOError, OSError):
            continue

    return index


def load_decomp_data(json_path):
    """按需加载单个 JSON 文件"""
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            return json.load(f)
    except (json.JSONDecodeError, IOError):
        return None


def load_globals_map():
    """加载全局变量映射表 (IDA auto-name -> real name)"""
    if not GLOBALS_EXPORT.exists():
        return {}
    try:
        with open(GLOBALS_EXPORT, 'r', encoding='utf-8') as f:
            data = json.load(f)
        # Build reverse map: for each global, map address-based IDA name to real name
        # IDA names like dword_580000 correspond to address 0x00580000
        addr_to_name = {}
        for g in data.get('globals', []) + data.get('class_statics', []):
            addr_str = g.get('address', '')
            name = g.get('name', '')
            if addr_str and name:
                # Extract hex address -> generate IDA auto-name
                addr = int(addr_str, 16)
                ida_names = [
                    f"dword_{addr:X}",
                    f"dword_{addr:x}",
                    f"byte_{addr:X}",
                    f"word_{addr:X}",
                    f"flt_{addr:X}",
                    f"off_{addr:X}",
                    f"unk_{addr:X}",
                ]
                for ida_name in ida_names:
                    addr_to_name[ida_name] = name
        return addr_to_name
    except (json.JSONDecodeError, IOError):
        return {}


def check_quality(decompiled_c):
    """检查反编译代码质量，返回 (pass, issues_dict)"""
    issues = {
        'raw_offsets': 0,
        'dword_refs': 0,
        'userpurge': 0,
        'memory_macro': 0,
    }

    if not decompiled_c:
        return False, issues

    # Count raw memory offset patterns: *(_DWORD *)(xxx + N), *(_BYTE *)(
    issues['raw_offsets'] = len(re.findall(
        r'\*\(_(?:DWORD|WORD|BYTE|QWORD)\s*\*\)\s*\(', decompiled_c))

    # Count dword_XXXXX / byte_XXXXX / word_XXXXX references
    issues['dword_refs'] = len(re.findall(
        r'\b(?:dword|byte|word|flt|qword|unk)_[0-9A-Fa-f]+\b', decompiled_c))

    # Count __userpurge / __usercall (broken calling convention)
    issues['userpurge'] = len(re.findall(
        r'__user(?:purge|call)', decompiled_c))

    # Count MEMORY[0x...] references
    issues['memory_macro'] = len(re.findall(r'MEMORY\[', decompiled_c))

    passed = (issues['raw_offsets'] <= MAX_RAW_OFFSETS and
              issues['dword_refs'] <= MAX_DWORD_REFS and
              issues['userpurge'] <= MAX_USERPURGE and
              issues['memory_macro'] == 0)

    return passed, issues


def apply_globals_replacement(code, globals_map):
    """将 IDA 自动命名的全局变量替换为真实名称"""
    if not globals_map or not code:
        return code

    def replacer(m):
        ida_name = m.group(0)
        return globals_map.get(ida_name, ida_name)

    return re.sub(
        r'\b(?:dword|byte|word|flt|off|unk)_[0-9A-Fa-f]+\b',
        replacer, code)


def extract_body(decompiled_c):
    """从 IDA 反编译 C 中提取函数体"""
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

    # Remove IDA stack layout comments: // [esp+4h] [ebp-80h] BYREF
    body = re.sub(r'\s*//\s*\[esp[^\n]*$', '', body, flags=re.MULTILINE)

    # Collapse multiple blank lines
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
              globals_map=None, quality_stats=None):
    """填充单个 .cpp 文件中的 stub 函数。

    Returns:
        (filled, not_found, rejected, not_found_names)
    """
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

        # Match against decomp index (now stores file paths)
        json_path = decomp_index.get(func_name)
        # 析构函数: stub 用 ~ClassName, IDA JSON 用 _ClassName
        if not json_path and '::~' in func_name:
            alt_name = func_name.replace('::~', '::_')
            json_path = decomp_index.get(alt_name)
        # 构造函数: stub 用 Class::Class, IDA 可能存为 Class::_Class
        if not json_path and '::' in func_name and '::~' not in func_name:
            parts = func_name.split('::', 1)
            if parts[0] == parts[1]:
                alt_name = f"{parts[0]}::_{parts[1]}"
                json_path = decomp_index.get(alt_name)
        if not json_path:
            not_found += 1
            not_found_names.append(func_name)
            continue

        # 按需加载 JSON
        decomp = load_decomp_data(json_path)
        if not decomp:
            not_found += 1
            not_found_names.append(func_name)
            continue

        raw_c = decomp.get('decompiled_c', '')

        # Quality gate
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

        # Apply globals replacement
        if globals_map:
            body = apply_globals_replacement(body, globals_map)

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


def get_module_files(module_name):
    """获取模块下的所有 .cpp 文件"""
    if module_name == '(root)':
        return list(SRC_DIR.glob("*.cpp"))
    module_dir = SRC_DIR / module_name
    if module_dir.exists():
        return list(module_dir.rglob("*.cpp"))
    return []


def main():
    parser = argparse.ArgumentParser(description="PAL3A Stub 自动填充")
    parser.add_argument('--all', action='store_true',
                        help='填充所有 src/pal3a/ 下的 stub')
    parser.add_argument('--module', metavar='NAME',
                        help='填充指定模块 (script, gamebase, ui, ...)')
    parser.add_argument('--file', metavar='PATH',
                        help='填充指定 .cpp 文件')
    parser.add_argument('--dry-run', action='store_true',
                        help='仅统计可填充数量，不修改文件')
    parser.add_argument('--no-quality-gate', action='store_true',
                        help='关闭质量门控，填充所有（含低质量代码）')
    parser.add_argument('--quality-report', action='store_true',
                        help='输出质量统计报告（不修改文件）')
    parser.add_argument('--list-modules', action='store_true',
                        help='列出可用模块')
    args = parser.parse_args()

    if args.list_modules:
        print("可用模块:")
        for d in sorted(SRC_DIR.iterdir()):
            if d.is_dir():
                cpp_count = len(list(d.rglob("*.cpp")))
                if cpp_count > 0:
                    print(f"  {d.name:20s} ({cpp_count} .cpp files)")
        return

    if not args.all and not args.file and not args.module and not args.quality_report:
        parser.print_help()
        return

    # Build decomp index (lightweight - only file paths, not content)
    print("[*] 构建反编译索引 (轻量模式，仅索引文件名)...")
    decomp_index = build_decomp_index()
    if not decomp_index:
        print("[!] 未找到反编译数据 (asm/pal3a/decomp/)。请先运行 IDA pipeline。")
        sys.exit(1)
    print(f"    索引: {len(decomp_index)} 个函数名")

    # Load globals replacement map
    globals_map = load_globals_map()
    if globals_map:
        print(f"    全局变量映射: {len(globals_map)} 条")
    else:
        print("    全局变量映射: 无 (asm/pal3a/globals_export.json 不存在)")

    # Quality gate settings
    quality_gate = not args.no_quality_gate
    if quality_gate:
        print(f"    质量门控: ON (raw_offsets<={MAX_RAW_OFFSETS}, "
              f"dword_refs<={MAX_DWORD_REFS})")
    else:
        print("    质量门控: OFF")

    # Quality report mode
    if args.quality_report:
        print("\n[*] 生成质量报告 (扫描所有匹配的反编译结果)...")
        stats = defaultdict(int)
        files = list(SRC_DIR.rglob("*.cpp"))
        for cpp_path in sorted(files):
            fill_file(cpp_path, decomp_index, dry_run=True,
                      quality_gate=True, globals_map=None, quality_stats=stats)
        print(f"\n=== 质量报告 ===")
        total = stats.get('total_checked', 0)
        passed = stats.get('passed', 0)
        rejected = stats.get('rejected', 0)
        print(f"  总计检查: {total}")
        print(f"  质量合格: {passed} ({100*passed/max(total,1):.1f}%)")
        print(f"  质量不合格: {rejected} ({100*rejected/max(total,1):.1f}%)")
        print(f"  --- 问题分布 ---")
        print(f"  硬编码偏移 (raw_offsets): 总计 {stats.get('raw_offsets', 0)} 处")
        print(f"  未命名全局 (dword_refs):  总计 {stats.get('dword_refs', 0)} 处")
        print(f"  错误调用约定 (userpurge): 总计 {stats.get('userpurge', 0)} 处")
        print(f"  MEMORY 宏:               总计 {stats.get('memory_macro', 0)} 处")
        return

    # Determine files to process
    if args.file:
        files = [Path(args.file).resolve()]
    elif args.module:
        files = get_module_files(args.module)
        if not files:
            print(f"[!] 模块 '{args.module}' 无 .cpp 文件")
            sys.exit(1)
    else:
        files = list(SRC_DIR.rglob("*.cpp"))

    print(f"[*] 处理 {len(files)} 个文件...")
    if args.dry_run:
        print("    (dry-run 模式，不修改文件)")
    print()

    total_filled = 0
    total_not_found = 0
    total_rejected = 0
    files_modified = 0
    all_not_found_names = []
    quality_stats = defaultdict(int)

    for cpp_path in sorted(files):
        filled, not_found, rejected, nf_names = fill_file(
            cpp_path, decomp_index, dry_run=args.dry_run,
            quality_gate=quality_gate, globals_map=globals_map,
            quality_stats=quality_stats)
        if filled > 0 or not_found > 0:
            rel = cpp_path.relative_to(PROJECT_ROOT)
            if filled > 0:
                status = f"{filled} filled"
                if rejected > 0:
                    status += f", {rejected} rejected(quality)"
                if not_found > 0:
                    status += f", {not_found} not matched"
                print(f"  {rel}: {status}")
                files_modified += 1
            total_filled += filled
        total_not_found += not_found
        total_rejected += rejected
        all_not_found_names.extend(nf_names)

    print()
    verb = '可填充' if args.dry_run else '已填充'
    marker = '*' if args.dry_run else '+'
    print(f"[{marker}] {verb}: {total_filled} 个函数 ({files_modified} 个文件)")
    if total_rejected > 0:
        print(f"    质量不合格跳过: {total_rejected} 个函数")
    print(f"    未匹配: {total_not_found} 个函数")


if __name__ == '__main__':
    main()
