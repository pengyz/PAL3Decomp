#!/usr/bin/env python3
"""
gbengine 函数注册表 - 日常操作 CLI

唯一权威数据源: data/gbengine_registry.jsonl

用法:
    python tools/registry.py status                     # 统计总览
    python tools/registry.py show 0x10014F10            # 查看单个函数
    python tools/registry.py list --status=todo         # 按状态筛选
    python tools/registry.py list --file=gbMesh.cpp     # 按文件筛选
    python tools/registry.py list --status=done --file=gbGlobals.cpp
    python tools/registry.py mark 0x10014F10 done --file=gbSceneGraph.cpp --our-name=CompareFunction
    python tools/registry.py mark 0x10085EEB not_needed --note="D3DX9 shader compiler"
    python tools/registry.py bulk-mark --addr-range=0x100D0000-0x100FFFFF --status=not_needed --note="CRT"
    python tools/registry.py import-symbols             # 从编译结果更新 done/stub
    python tools/registry.py verify                     # 校验文件字段
"""

import json
import sys
import os
import re
import argparse
import subprocess
import glob
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
REGISTRY_FILE = PROJECT_ROOT / "data" / "gbengine_registry.jsonl"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
COMPARE_TOOL = PROJECT_ROOT / "tools" / "gbengine_compare.py"

VALID_STATUSES = {"done", "stub", "todo", "not_needed", "auto", "unknown"}


def load_registry():
    """Load registry from JSONL file."""
    entries = []
    if not REGISTRY_FILE.exists():
        print(f"错误: 注册表文件不存在: {REGISTRY_FILE}", file=sys.stderr)
        print(f"请先运行: python tools/registry_init.py", file=sys.stderr)
        sys.exit(1)

    with open(REGISTRY_FILE) as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            try:
                entries.append(json.loads(line))
            except json.JSONDecodeError as e:
                print(f"警告: 第 {line_num} 行 JSON 解析错误: {e}", file=sys.stderr)

    return entries


def save_registry(entries):
    """Save registry to JSONL file."""
    REGISTRY_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(REGISTRY_FILE, 'w') as f:
        for entry in entries:
            # Remove None values
            clean = {k: v for k, v in entry.items() if v is not None}
            f.write(json.dumps(clean, ensure_ascii=False) + "\n")


def normalize_addr(addr_str):
    """Normalize address string to 0x10XXXXXX format."""
    if isinstance(addr_str, int):
        return f"0x{addr_str:08X}"
    addr_str = addr_str.strip()
    if addr_str.startswith("0x") or addr_str.startswith("0X"):
        val = int(addr_str, 16)
    else:
        val = int(addr_str, 16)
    return f"0x{val:08X}"


def cmd_status(args, entries):
    """Print status overview."""
    by_status = defaultdict(int)
    by_status_bytes = defaultdict(int)
    by_file = defaultdict(lambda: defaultdict(int))

    for e in entries:
        status = e.get("status", "unknown")
        size = e.get("size", 0)
        by_status[status] += 1
        by_status_bytes[status] += size
        if e.get("file"):
            by_file[e["file"]][status] += 1

    total = len(entries)
    print(f"{'='*60}")
    print(f" gbengine.dll 函数注册表状态")
    print(f"{'='*60}")
    print(f"  总函数数: {total}")
    print(f"  注册表: {REGISTRY_FILE}")
    print()
    print(f"  {'状态':<12} {'数量':>6} {'代码量':>10} {'占比':>7}")
    print(f"  {'-'*40}")

    for status in ["done", "stub", "todo", "not_needed", "auto", "unknown"]:
        count = by_status.get(status, 0)
        bytes_val = by_status_bytes.get(status, 0)
        pct = 100 * count / total if total else 0
        if count > 0:
            print(f"  {status:<12} {count:>6} {bytes_val/1024:>8.1f} KB {pct:>6.1f}%")

    # Progress calculation
    not_needed = by_status.get("not_needed", 0)
    auto = by_status.get("auto", 0)
    target = total - not_needed - auto
    done = by_status.get("done", 0)
    stub = by_status.get("stub", 0)

    target_bytes = sum(e.get("size", 0) for e in entries
                       if e.get("status") not in ("not_needed", "auto"))
    done_bytes = sum(e.get("size", 0) for e in entries if e.get("status") == "done")
    stub_bytes = sum(e.get("size", 0) for e in entries if e.get("status") == "stub")

    print()
    print(f"  {'─'*40}")
    print(f"  目标函数: {target} (排除 {not_needed} not_needed + {auto} auto)")
    print(f"  已完成 (done): {done} 个函数 ({100*done/target:.1f}%)")
    if stub:
        print(f"  部分完成 (stub): {stub} 个函数")
    print(f"  代码覆盖: {done_bytes/1024:.1f} / {target_bytes/1024:.1f} KB "
          f"({100*done_bytes/target_bytes:.1f}%)")

    # Per-file summary (top files)
    if by_file:
        print()
        print(f"  源文件 (done 数量 top 15):")
        file_done = [(f, counts.get("done", 0)) for f, counts in by_file.items()]
        file_done.sort(key=lambda x: -x[1])
        for fname, count in file_done[:15]:
            total_in_file = sum(by_file[fname].values())
            print(f"    {fname:<30} {count:>4}/{total_in_file}")


def cmd_show(args, entries):
    """Show details for a single function."""
    target_addr = normalize_addr(args.address)

    for e in entries:
        if normalize_addr(e["addr"]) == target_addr:
            print(json.dumps(e, indent=2, ensure_ascii=False))
            return

    # Try partial match
    for e in entries:
        if target_addr.lower() in e["addr"].lower():
            print(json.dumps(e, indent=2, ensure_ascii=False))
            return

    print(f"未找到地址: {target_addr}", file=sys.stderr)
    sys.exit(1)


def cmd_list(args, entries):
    """List functions matching filters."""
    filtered = entries

    if args.status:
        statuses = set(args.status.split(","))
        filtered = [e for e in filtered if e.get("status") in statuses]

    if args.file:
        filtered = [e for e in filtered if e.get("file") == args.file]

    if args.name:
        pattern = args.name.lower()
        filtered = [e for e in filtered
                    if pattern in e.get("name", "").lower()
                    or pattern in (e.get("our_name") or "").lower()]

    if args.min_size:
        filtered = [e for e in filtered if e.get("size", 0) >= args.min_size]

    # Sort
    if args.sort == "size":
        filtered.sort(key=lambda e: -e.get("size", 0))
    elif args.sort == "addr":
        filtered.sort(key=lambda e: int(e["addr"], 16))
    elif args.sort == "name":
        filtered.sort(key=lambda e: e.get("name", ""))

    # Limit
    total_filtered = len(filtered)
    if args.limit:
        filtered = filtered[:args.limit]

    # Output
    if args.json:
        for e in filtered:
            print(json.dumps(e, ensure_ascii=False))
    else:
        print(f"共 {total_filtered} 个函数" +
              (f" (显示前 {len(filtered)})" if len(filtered) < total_filtered else ""))
        print()
        print(f"{'地址':<12} {'大小':>6} {'状态':<11} {'名称'}")
        print(f"{'-'*70}")
        for e in filtered:
            addr = e["addr"]
            size = e.get("size", 0)
            status = e.get("status", "?")
            name = e.get("our_name") or e.get("name", "?")
            file_info = f" [{e['file']}]" if e.get("file") else ""
            print(f"{addr:<12} {size:>5}B {status:<11} {name}{file_info}")


def cmd_mark(args, entries):
    """Mark a function's status."""
    target_addr = normalize_addr(args.address)
    new_status = args.new_status

    if new_status not in VALID_STATUSES:
        print(f"错误: 无效状态 '{new_status}'. 有效值: {VALID_STATUSES}", file=sys.stderr)
        sys.exit(1)

    found = False
    for e in entries:
        if normalize_addr(e["addr"]) == target_addr:
            old_status = e.get("status", "unknown")
            e["status"] = new_status
            if args.file:
                e["file"] = args.file
            if args.our_name:
                e["our_name"] = args.our_name
            if args.note:
                e["note"] = args.note

            print(f"更新: {e['addr']} {e.get('name','')}")
            print(f"  状态: {old_status} → {new_status}")
            if args.file:
                print(f"  文件: {args.file}")
            if args.our_name:
                print(f"  our_name: {args.our_name}")
            if args.note:
                print(f"  note: {args.note}")

            found = True
            break

    if not found:
        print(f"错误: 未找到地址 {target_addr}", file=sys.stderr)
        sys.exit(1)

    save_registry(entries)
    print("已保存")


def cmd_bulk_mark(args, entries):
    """Bulk mark functions by address range or pattern."""
    new_status = args.status
    if new_status not in VALID_STATUSES:
        print(f"错误: 无效状态 '{new_status}'", file=sys.stderr)
        sys.exit(1)

    count = 0

    if args.addr_range:
        parts = args.addr_range.split("-")
        if len(parts) != 2:
            print("错误: --addr-range 格式应为 0xSTART-0xEND", file=sys.stderr)
            sys.exit(1)
        start = int(parts[0], 16)
        end = int(parts[1], 16)

        for e in entries:
            addr = int(e["addr"], 16)
            if start <= addr <= end:
                if e.get("status") != new_status:
                    e["status"] = new_status
                    if args.note:
                        e["note"] = args.note
                    count += 1

    elif args.name_pattern:
        pat = re.compile(args.name_pattern)
        for e in entries:
            if pat.search(e.get("name", "")):
                if e.get("status") != new_status:
                    e["status"] = new_status
                    if args.note:
                        e["note"] = args.note
                    count += 1

    if count > 0:
        save_registry(entries)
    print(f"已更新 {count} 个函数为 {new_status}")


def cmd_import_symbols(args, entries):
    """Import symbols from compilation results to update done/stub status."""
    print("编译源码收集符号...", file=sys.stderr)

    # Build address lookup
    addr_map = {normalize_addr(e["addr"]): e for e in entries}
    mangled_map = {e["mangled"]: e for e in entries if e.get("mangled")}
    name_map = {}
    for e in entries:
        name = e.get("name", "")
        short = name.split("(")[0] if "(" in name else name
        if short:
            name_map.setdefault(short, []).append(e)

    src_files = sorted(glob.glob(str(SRC_DIR / "*.cpp")))
    updated = 0

    for src in src_files:
        try:
            r = subprocess.run(
                [sys.executable, str(COMPARE_TOOL), "--compile", src, "--all"],
                capture_output=True, text=True, timeout=120,
                cwd=str(PROJECT_ROOT)
            )
        except (subprocess.TimeoutExpired, Exception) as ex:
            print(f"  跳过 {os.path.basename(src)}: {ex}", file=sys.stderr)
            continue

        basename = os.path.basename(src)
        current_func = None
        for line in r.stdout.split("\n"):
            m = re.match(r"^\s+(\S.*?):\s*$", line)
            if m:
                current_func = m.group(1)
                # Try to find this function in registry
                matched_entry = None
                if current_func in mangled_map:
                    matched_entry = mangled_map[current_func]
                elif current_func in name_map:
                    candidates = name_map[current_func]
                    if len(candidates) == 1:
                        matched_entry = candidates[0]

                if matched_entry and matched_entry.get("status") != "done":
                    matched_entry["status"] = "done"
                    matched_entry["file"] = basename
                    matched_entry["our_name"] = current_func
                    updated += 1

    if updated > 0:
        save_registry(entries)
    print(f"已更新 {updated} 个函数为 done")


def cmd_verify(args, entries):
    """Verify registry consistency."""
    issues = []

    for e in entries:
        addr = e.get("addr", "?")

        # Check file exists
        if e.get("file"):
            fpath = SRC_DIR / e["file"]
            if not fpath.exists():
                issues.append(f"  {addr}: file '{e['file']}' 不存在")

        # Check status validity
        status = e.get("status", "")
        if status not in VALID_STATUSES:
            issues.append(f"  {addr}: 无效状态 '{status}'")

        # Check done/stub should have file
        if status in ("done", "stub") and not e.get("file"):
            issues.append(f"  {addr}: 状态为 {status} 但缺少 file 字段")

        # Check size
        if e.get("size", 0) <= 0:
            issues.append(f"  {addr}: size <= 0")

    if issues:
        print(f"发现 {len(issues)} 个问题:")
        for issue in issues[:50]:
            print(issue)
        if len(issues) > 50:
            print(f"  ... 还有 {len(issues)-50} 个问题")
    else:
        print("注册表验证通过，无问题。")


def main():
    parser = argparse.ArgumentParser(
        description="gbengine 函数注册表 CLI",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    subparsers = parser.add_subparsers(dest="command", help="子命令")

    # status
    sub = subparsers.add_parser("status", help="统计总览")

    # show
    sub = subparsers.add_parser("show", help="查看单个函数")
    sub.add_argument("address", help="函数地址 (hex)")

    # list
    sub = subparsers.add_parser("list", help="列出函数")
    sub.add_argument("--status", help="按状态筛选 (逗号分隔)")
    sub.add_argument("--file", help="按源文件筛选")
    sub.add_argument("--name", help="按名称模糊搜索")
    sub.add_argument("--min-size", type=int, help="最小字节数")
    sub.add_argument("--sort", choices=["addr", "size", "name"], default="addr")
    sub.add_argument("--limit", type=int, help="最大显示数量")
    sub.add_argument("--json", action="store_true", help="JSON 输出")

    # mark
    sub = subparsers.add_parser("mark", help="修改函数状态")
    sub.add_argument("address", help="函数地址 (hex)")
    sub.add_argument("new_status", help=f"新状态: {VALID_STATUSES}")
    sub.add_argument("--file", help="源文件名")
    sub.add_argument("--our-name", help="我们的函数名")
    sub.add_argument("--note", help="备注")

    # bulk-mark
    sub = subparsers.add_parser("bulk-mark", help="批量修改状态")
    sub.add_argument("--addr-range", help="地址范围 (0xSTART-0xEND)")
    sub.add_argument("--name-pattern", help="名称正则匹配")
    sub.add_argument("--status", required=True, help="新状态")
    sub.add_argument("--note", help="备注")

    # import-symbols
    sub = subparsers.add_parser("import-symbols", help="从编译结果更新状态")

    # verify
    sub = subparsers.add_parser("verify", help="校验注册表一致性")

    args = parser.parse_args()

    if not args.command:
        parser.print_help()
        sys.exit(0)

    entries = load_registry()

    if args.command == "status":
        cmd_status(args, entries)
    elif args.command == "show":
        cmd_show(args, entries)
    elif args.command == "list":
        cmd_list(args, entries)
    elif args.command == "mark":
        cmd_mark(args, entries)
    elif args.command == "bulk-mark":
        cmd_bulk_mark(args, entries)
    elif args.command == "import-symbols":
        cmd_import_symbols(args, entries)
    elif args.command == "verify":
        cmd_verify(args, entries)


if __name__ == "__main__":
    main()
