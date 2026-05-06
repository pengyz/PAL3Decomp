#!/usr/bin/env python3
"""
PAL3A 按文件导出/填充工具。

基于 PDB source_file_index 建立精确的 C++ 文件 ↔ 函数映射,
支持逐文件导出、质量检查、填充。

工作流:
  1. list    — 列出所有源文件及函数数/质量状态
  2. show    — 显示指定文件的所有函数及质量评分
  3. fill    — 填充指定文件 (仅质量合格的函数)
  4. quality — 对指定文件的反编译结果做详细质量分析
  5. status  — 总览: 各模块的填充进度

用法:
    python tools/pal3a_file_export.py list [--module combat]
    python tools/pal3a_file_export.py show combat/CBEditor.cpp
    python tools/pal3a_file_export.py quality combat/CBEditor.cpp
    python tools/pal3a_file_export.py fill combat/CBEditor.cpp [--dry-run]
    python tools/pal3a_file_export.py status
"""

import argparse
import json
import os
import re
import sys
from pathlib import Path
from collections import defaultdict, Counter

PROJECT_ROOT = Path(__file__).parent.parent
PDB_EXPORT = PROJECT_ROOT / "asm" / "pal3a" / "pdb_export.json"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3a" / "decomp"
SRC_DIR = PROJECT_ROOT / "src" / "pal3a"
GLOBALS_EXPORT = PROJECT_ROOT / "asm" / "pal3a" / "globals_export.json"

# PDB path prefix
PDB_PREFIX = "D:\\PAL3A\\PAL3\\"

# Directory case normalization (PDB has mixed case)
DIR_NORMALIZE = {
    'Combat': 'combat', 'GAMEBASE': 'gamebase',
    'GameMainUI': 'gamemainui', 'GAMEMAINUI': 'gamemainui',
    'GameUI': 'gameui', 'GAMEUI': 'gameui',
    'Fight': 'fight', 'UI': 'ui',
    'ArcInfo': 'arcinfo', 'CatchGhost': 'catchghost',
    'Compose': 'compose', 'Effect': 'effect',
    'Assistant System': 'assistant_system',
}


def normalize_pdb_path(pdb_path):
    """将 PDB 路径转为本地 src/pal3a/ 相对路径"""
    p = pdb_path
    if p.startswith(PDB_PREFIX):
        p = p[len(PDB_PREFIX):]
    p = p.replace('\\', '/')

    # Normalize first directory component
    parts = p.split('/')
    if parts and parts[0] in DIR_NORMALIZE:
        parts[0] = DIR_NORMALIZE[parts[0]]
    return '/'.join(parts)


def load_file_function_map():
    """加载 PDB source_file_index → 构建 文件 → 函数列表 映射"""
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        pdb = json.load(f)

    sfi = pdb.get('source_file_index', {})
    file_map = {}  # normalized_path -> [func_info, ...]

    for pdb_path, func_list in sfi.items():
        # Skip system headers
        if 'VisualStudio' in pdb_path or 'Microsoft' in pdb_path:
            continue
        if 'INCLUDE' in pdb_path and 'PAL3' not in pdb_path:
            continue
        if PDB_PREFIX not in pdb_path and 'PAL3' not in pdb_path:
            continue

        norm = normalize_pdb_path(pdb_path)

        # Skip .h files that don't correspond to implementation
        # (keep .h if it has inline implementations - these are common in game code)

        if norm not in file_map:
            file_map[norm] = []
        file_map[norm].extend(func_list)

    return file_map


def build_decomp_index():
    """构建 函数名 → json 文件路径 的索引"""
    index = {}
    if not DECOMP_DIR.exists():
        return index

    for json_file in DECOMP_DIR.glob("*.json"):
        if json_file.name.startswith('_'):
            continue
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                head = f.read(256)
            m = re.search(r'"name"\s*:\s*"([^"]*)"', head)
            if not m:
                continue
            name = m.group(1)
            if not name:
                continue
            if name not in index:
                index[name] = json_file
            else:
                if json_file.stat().st_size > index[name].stat().st_size:
                    index[name] = json_file
        except (IOError, OSError):
            continue
    return index


def build_addr_decomp_index():
    """构建 地址 → json 文件路径 的索引"""
    index = {}
    if not DECOMP_DIR.exists():
        return index

    for json_file in DECOMP_DIR.glob("*.json"):
        if json_file.name.startswith('_'):
            continue
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                head = f.read(512)
            m = re.search(r'"address"\s*:\s*"(0x[0-9A-Fa-f]+)"', head)
            if m:
                addr = m.group(1).upper()
                index[addr] = json_file
        except (IOError, OSError):
            continue
    return index


def check_function_quality(decompiled_c):
    """评估单个函数的反编译质量。返回 (score, issues)"""
    if not decompiled_c:
        return 0, ['no_code']

    issues = []
    lines = decompiled_c.split('\n')
    total_lines = len(lines)

    # Count problems
    raw_offsets = len(re.findall(r'\*\(_(?:DWORD|WORD|BYTE|QWORD)\s*\*\)\s*\(', decompiled_c))
    dword_refs = len(re.findall(r'\b(?:dword|byte|word|flt|qword|unk)_[0-9A-Fa-f]+\b', decompiled_c))
    userpurge = '__userpurge' in decompiled_c or '__usercall' in decompiled_c
    memory_macro = 'MEMORY[' in decompiled_c
    jumpout = 'JUMPOUT' in decompiled_c

    if userpurge:
        issues.append('userpurge')
    if jumpout:
        issues.append('jumpout')
    if memory_macro:
        issues.append('MEMORY[]')
    if dword_refs > 0:
        issues.append(f'dword_x{dword_refs}')
    if raw_offsets > 3:
        issues.append(f'raw_offset_x{raw_offsets}')

    # Score: 100 = perfect, 0 = terrible
    score = 100
    if userpurge:
        score -= 50
    if jumpout:
        score -= 40
    if memory_macro:
        score -= 30
    score -= min(30, dword_refs * 10)
    score -= min(30, raw_offsets * 3)
    score = max(0, score)

    return score, issues


def cmd_list(args, file_map):
    """列出所有源文件"""
    module_filter = args.module.lower() if args.module else None

    # Group by module
    by_module = defaultdict(list)
    for norm_path, funcs in sorted(file_map.items()):
        parts = norm_path.split('/')
        module = parts[0] if len(parts) > 1 else '(root)'
        if module_filter and module.lower() != module_filter:
            continue
        by_module[module].append((norm_path, len(funcs)))

    for module in sorted(by_module.keys()):
        files = by_module[module]
        total_funcs = sum(cnt for _, cnt in files)
        print(f"\n{module}/ ({total_funcs} functions, {len(files)} files)")
        print(f"{'─' * 60}")
        for path, cnt in sorted(files, key=lambda x: -x[1]):
            # Check if local .cpp exists
            local_path = SRC_DIR / path
            exists = '✓' if local_path.exists() else ' '
            print(f"  {exists} {cnt:4d}  {path}")


def cmd_show(args, file_map, decomp_index):
    """显示指定文件的函数列表及质量"""
    target = args.path
    # Try to find in file_map
    matched = None
    for norm_path in file_map:
        if target in norm_path or norm_path.endswith(target):
            matched = norm_path
            break

    if not matched:
        print(f"[!] 未找到文件: {target}")
        print(f"    提示: 使用 'list' 命令查看可用文件")
        return

    funcs = file_map[matched]
    print(f"文件: {matched}")
    print(f"函数数: {len(funcs)}")
    print(f"{'─' * 70}")

    for func in sorted(funcs, key=lambda f: f.get('address', '')):
        name = func.get('name', '?')
        addr = func.get('address', '?')
        size = func.get('size', 0)

        # Check if we have decompilation
        json_path = decomp_index.get(name)
        if not json_path:
            # Try by address
            json_path = None  # addr index is expensive, skip for now

        quality_str = '  --'
        if json_path:
            try:
                with open(json_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                code = data.get('decompiled_c', '')
                score, issues = check_function_quality(code)
                issue_str = ', '.join(issues) if issues else 'clean'
                quality_str = f'{score:3d}  {issue_str}'
            except:
                quality_str = '  ERR'
        else:
            quality_str = '  N/A (no export)'

        print(f"  {addr}  {size:5d}B  {quality_str:30s}  {name}")


def cmd_quality(args, file_map, decomp_index):
    """指定文件的详细质量分析"""
    target = args.path
    matched = None
    for norm_path in file_map:
        if target in norm_path or norm_path.endswith(target):
            matched = norm_path
            break

    if not matched:
        print(f"[!] 未找到文件: {target}")
        return

    funcs = file_map[matched]
    print(f"质量分析: {matched}")
    print(f"函数总数: {len(funcs)}")
    print()

    scores = []
    has_export = 0
    no_export = 0
    by_issue = Counter()

    for func in funcs:
        name = func.get('name', '?')
        json_path = decomp_index.get(name)
        if not json_path:
            no_export += 1
            continue

        has_export += 1
        try:
            with open(json_path, 'r', encoding='utf-8') as f:
                data = json.load(f)
            code = data.get('decompiled_c', '')
            score, issues = check_function_quality(code)
            scores.append(score)
            for issue in issues:
                by_issue[issue.split('_x')[0]] += 1
        except:
            pass

    print(f"  有反编译结果: {has_export}/{len(funcs)}")
    print(f"  无反编译结果: {no_export}")
    if scores:
        avg = sum(scores) / len(scores)
        perfect = sum(1 for s in scores if s == 100)
        good = sum(1 for s in scores if s >= 70)
        poor = sum(1 for s in scores if s < 50)
        print(f"  平均质量分: {avg:.1f}/100")
        print(f"  完美 (100):  {perfect}")
        print(f"  良好 (≥70):  {good}")
        print(f"  较差 (<50):  {poor}")
        print()
        print(f"  问题分布:")
        for issue, cnt in by_issue.most_common():
            print(f"    {issue:20s}: {cnt}")

        # Recommendation
        print()
        if avg >= 70 and poor == 0:
            print(f"  >>> 推荐: 可以填充此文件 (质量良好)")
        elif avg >= 50:
            print(f"  >>> 建议: 需要先在 IDA 中优化类型标注")
        else:
            print(f"  >>> 警告: 质量过低，需要大量 IDA 类型标注工作")


def cmd_fill(args, file_map, decomp_index):
    """填充指定文件"""
    target = args.path
    matched = None
    for norm_path in file_map:
        if target in norm_path or norm_path.endswith(target):
            matched = norm_path
            break

    if not matched:
        print(f"[!] 未找到文件: {target}")
        return

    # Determine local .cpp path
    local_cpp = SRC_DIR / matched
    if not local_cpp.exists():
        # Try .cpp extension
        if matched.endswith('.h'):
            cpp_path = matched[:-2] + '.cpp'
            local_cpp = SRC_DIR / cpp_path
        if not local_cpp.exists():
            print(f"[!] 本地文件不存在: {local_cpp}")
            print(f"    请先确认 src/pal3a/{matched} 已创建")
            return

    funcs = file_map[matched]
    print(f"填充: {matched} -> {local_cpp.relative_to(PROJECT_ROOT)}")
    print(f"PDB 函数: {len(funcs)}")

    # Collect quality-passing functions
    fillable = []
    rejected = 0
    no_export = 0

    for func in funcs:
        name = func.get('name', '')
        if not name:
            continue
        json_path = decomp_index.get(name)
        if not json_path:
            no_export += 1
            continue

        try:
            with open(json_path, 'r', encoding='utf-8') as f:
                data = json.load(f)
            code = data.get('decompiled_c', '')
            score, issues = check_function_quality(code)

            if score >= 70 or args.force:
                fillable.append((name, code, score, issues))
            else:
                rejected += 1
                if not args.quiet:
                    print(f"  [SKIP] {name} (score={score}, {','.join(issues)})")
        except:
            no_export += 1

    print(f"  可填充: {len(fillable)}, 跳过(质量): {rejected}, 无导出: {no_export}")

    if not fillable:
        print("  无可填充函数。")
        return

    if args.dry_run:
        print(f"  (dry-run, 不修改文件)")
        for name, _, score, issues in fillable:
            print(f"    [{score:3d}] {name}")
        return

    # Actually fill: import from pal3a_fill_stubs
    sys.path.insert(0, str(Path(__file__).parent))
    from pal3a_fill_stubs import parse_stub_functions, extract_body

    with open(local_cpp, 'r', encoding='utf-8', errors='replace') as f:
        lines = f.read().split('\n')

    stubs = parse_stub_functions(local_cpp)
    stub_names = {s['name']: s for s in stubs}

    filled = 0
    offset = 0

    for name, raw_c, score, issues in fillable:
        # Find matching stub
        stub = stub_names.get(name)
        if not stub:
            # Try without class prefix for file-level functions
            short = name.split('::')[-1] if '::' in name else name
            stub = stub_names.get(short)
        if not stub:
            continue

        body = extract_body(raw_c)
        if not body:
            continue

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

    if filled > 0:
        with open(local_cpp, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        print(f"  [+] 已填充 {filled} 个函数")
    else:
        print(f"  [-] 未找到匹配的 stub（函数名不匹配）")


def cmd_status(file_map):
    """总览: 各模块填充状态"""
    by_module = defaultdict(lambda: {'files': 0, 'funcs': 0, 'has_cpp': 0})

    for norm_path, funcs in file_map.items():
        parts = norm_path.split('/')
        module = parts[0] if len(parts) > 1 else '(root)'
        by_module[module]['files'] += 1
        by_module[module]['funcs'] += len(funcs)
        local_path = SRC_DIR / norm_path
        if local_path.exists():
            by_module[module]['has_cpp'] += 1

    print(f"{'模块':<20s} {'文件':>5s} {'有cpp':>6s} {'函数':>6s}")
    print('─' * 45)
    total_files = 0
    total_cpp = 0
    total_funcs = 0
    for module in sorted(by_module.keys(), key=lambda m: -by_module[m]['funcs']):
        info = by_module[module]
        print(f"{module:<20s} {info['files']:>5d} {info['has_cpp']:>6d} {info['funcs']:>6d}")
        total_files += info['files']
        total_cpp += info['has_cpp']
        total_funcs += info['funcs']
    print('─' * 45)
    print(f"{'TOTAL':<20s} {total_files:>5d} {total_cpp:>6d} {total_funcs:>6d}")


def main():
    parser = argparse.ArgumentParser(
        description="PAL3A 按文件导出/填充工具",
        formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest='command')

    # list
    p_list = sub.add_parser('list', help='列出所有源文件')
    p_list.add_argument('--module', help='按模块过滤')

    # show
    p_show = sub.add_parser('show', help='显示文件的函数列表')
    p_show.add_argument('path', help='PDB 相对路径 (如 combat/CBEditor.cpp)')

    # quality
    p_qual = sub.add_parser('quality', help='文件质量分析')
    p_qual.add_argument('path', help='PDB 相对路径')

    # fill
    p_fill = sub.add_parser('fill', help='填充指定文件')
    p_fill.add_argument('path', help='PDB 相对路径')
    p_fill.add_argument('--dry-run', action='store_true', help='仅预览')
    p_fill.add_argument('--force', action='store_true', help='忽略质量门控')
    p_fill.add_argument('--quiet', action='store_true', help='不输出跳过原因')

    # status
    sub.add_parser('status', help='总览状态')

    args = parser.parse_args()
    if not args.command:
        parser.print_help()
        return

    # Load data
    if not PDB_EXPORT.exists():
        print(f"[!] PDB 导出不存在: {PDB_EXPORT}")
        sys.exit(1)

    print("[*] 加载 PDB 文件映射...")
    file_map = load_file_function_map()
    print(f"    {len(file_map)} 个源文件, "
          f"{sum(len(v) for v in file_map.values())} 个函数")

    if args.command == 'list':
        cmd_list(args, file_map)
    elif args.command == 'show':
        print("[*] 构建反编译索引...")
        decomp_index = build_decomp_index()
        print(f"    {len(decomp_index)} 个已导出函数")
        cmd_show(args, file_map, decomp_index)
    elif args.command == 'quality':
        print("[*] 构建反编译索引...")
        decomp_index = build_decomp_index()
        print(f"    {len(decomp_index)} 个已导出函数")
        cmd_quality(args, file_map, decomp_index)
    elif args.command == 'fill':
        print("[*] 构建反编译索引...")
        decomp_index = build_decomp_index()
        print(f"    {len(decomp_index)} 个已导出函数")
        cmd_fill(args, file_map, decomp_index)
    elif args.command == 'status':
        cmd_status(file_map)


if __name__ == '__main__':
    main()
