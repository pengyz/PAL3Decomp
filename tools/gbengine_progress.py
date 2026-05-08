#!/usr/bin/env python3
"""
gbengine.dll - 进度报告工具

从 data/gbengine_registry.jsonl 读取函数状态（唯一权威数据源）。
可选：编译并验证字节匹配质量。

用法:
    python tools/gbengine_progress.py                # 完整报告
    python tools/gbengine_progress.py --summary      # 简要摘要
    python tools/gbengine_progress.py --missing      # 未实现函数 (按大小排序)
    python tools/gbengine_progress.py --missing 100  # 前100个
    python tools/gbengine_progress.py --by-class     # 按类分组
    python tools/gbengine_progress.py --quality      # 字节匹配质量 (需编译)
    python tools/gbengine_progress.py --json         # 输出 JSON 到 build/
"""

import re
import os
import sys
import json
import subprocess
import argparse
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
REGISTRY_FILE = PROJECT_ROOT / "data" / "gbengine_registry.jsonl"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
COMPARE_TOOL = PROJECT_ROOT / "tools" / "gbengine_compare.py"
OUTPUT_JSON = PROJECT_ROOT / "build" / "gbengine_progress.json"


def load_registry():
    """Load function registry from JSONL."""
    if not REGISTRY_FILE.exists():
        print(f"错误: 注册表不存在: {REGISTRY_FILE}", file=sys.stderr)
        print(f"请先运行: python tools/registry_init.py", file=sys.stderr)
        sys.exit(1)

    entries = []
    with open(REGISTRY_FILE) as f:
        for line in f:
            line = line.strip()
            if line:
                entries.append(json.loads(line))
    return entries


def categorize_entry(entry):
    """Map registry status to display category."""
    status = entry.get("status", "unknown")
    if status in ("not_needed", "auto"):
        return "thirdparty"
    # Distinguish exported vs internal for display
    name = entry.get("name", "")
    mangled = entry.get("mangled", "")
    # Check if it's an exported function (has mangled C++ name or known export)
    if entry.get("_exported"):
        return "exported"
    return "engine"


def get_class_name(entry):
    """Extract class name from function name."""
    name = entry.get("name", "")
    if "::" in name:
        return name.split("::")[0]
    return "(global)"


def compile_and_verify_quality(entries):
    """Compile source and check byte-match quality for 'done' functions."""
    done_entries = [e for e in entries if e.get("status") == "done" and e.get("file")]
    # Group by file
    by_file = defaultdict(list)
    for e in done_entries:
        by_file[e["file"]].append(e)

    quality_results = {}  # addr -> {match, total, size_ok}

    for src_file in sorted(by_file.keys()):
        src_path = SRC_DIR / src_file
        if not src_path.exists():
            continue

        try:
            r = subprocess.run(
                [sys.executable, str(COMPARE_TOOL), "--compile", str(src_path), "--all"],
                capture_output=True, text=True, timeout=120,
                cwd=str(PROJECT_ROOT)
            )
        except (subprocess.TimeoutExpired, Exception):
            continue

        current_func = None
        current_info = None
        for line in r.stdout.split("\n"):
            m = re.match(r"^\s+(\S.*?):\s*$", line)
            if m:
                current_func = m.group(1)
                current_info = {"match": 0, "total": 0, "size_ok": True}
                quality_results[current_func] = current_info
                continue

            if current_info:
                if "Size: MISMATCH" in line:
                    current_info["size_ok"] = False
                m2 = re.search(r"Match: (\d+)/(\d+) bytes", line)
                if m2:
                    current_info["match"] = int(m2.group(1))
                    current_info["total"] = int(m2.group(2))

    return quality_results


def print_summary(entries):
    """Print progress summary from registry."""
    not_needed = [e for e in entries if e.get("status") in ("not_needed", "auto")]
    target = [e for e in entries if e.get("status") not in ("not_needed", "auto")]

    done = [e for e in target if e.get("status") == "done"]
    stub = [e for e in target if e.get("status") == "stub"]
    todo = [e for e in target if e.get("status") == "todo"]
    unknown = [e for e in target if e.get("status") == "unknown"]

    total_bytes = sum(e.get("size", 0) for e in target)
    done_bytes = sum(e.get("size", 0) for e in done)
    stub_bytes = sum(e.get("size", 0) for e in stub)

    print("=" * 68)
    print(" gbengine.dll 反编译进度 (from registry)")
    print("=" * 68)
    print(f"  总函数: {len(entries)}")
    print(f"  排除 (not_needed/auto): {len(not_needed)}")
    print(f"  目标函数: {len(target)}")
    print()
    print(f"  {'状态':<12} {'函数数':>6} {'代码量':>10} {'占目标':>7}")
    print(f"  {'-'*42}")
    print(f"  {'done':<12} {len(done):>6} {done_bytes/1024:>8.1f} KB "
          f"{100*done_bytes/total_bytes:>6.1f}%")
    if stub:
        print(f"  {'stub':<12} {len(stub):>6} {stub_bytes/1024:>8.1f} KB "
              f"{100*stub_bytes/total_bytes:>6.1f}%")
    print(f"  {'todo':<12} {len(todo):>6} {sum(e.get('size',0) for e in todo)/1024:>8.1f} KB")
    print(f"  {'unknown':<12} {len(unknown):>6} "
          f"{sum(e.get('size',0) for e in unknown)/1024:>8.1f} KB")
    print()
    print(f"  覆盖率 (按函数): {100*len(done)/len(target):.1f}%")
    print(f"  覆盖率 (按代码): {100*done_bytes/total_bytes:.1f}%")

    # Named vs sub_ breakdown for remaining work
    remaining = todo + unknown
    named_remaining = [e for e in remaining if not e.get("name", "").startswith("sub_")]
    sub_remaining = [e for e in remaining if e.get("name", "").startswith("sub_")]
    print()
    print(f"  剩余工作:")
    print(f"    有名称: {len(named_remaining)} 个 "
          f"({sum(e.get('size',0) for e in named_remaining)/1024:.1f} KB)")
    print(f"    sub_XX: {len(sub_remaining)} 个 "
          f"({sum(e.get('size',0) for e in sub_remaining)/1024:.1f} KB)")


def print_quality(entries):
    """Print byte-match quality breakdown (requires compilation)."""
    print("\n编译并验证字节匹配...", file=sys.stderr)
    quality = compile_and_verify_quality(entries)

    if not quality:
        print("无匹配质量数据 (编译可能失败)")
        return

    perfect = []
    near = []
    size_mismatch = []
    low_match = []

    for func_name, q in quality.items():
        if q["total"] == 0:
            continue
        ratio = q["match"] / q["total"]
        if q["match"] == q["total"]:
            perfect.append((func_name, q))
        elif not q["size_ok"]:
            size_mismatch.append((func_name, q))
        elif ratio >= 0.9:
            near.append((func_name, q))
        else:
            low_match.append((func_name, q))

    total_verified = len(perfect) + len(near) + len(size_mismatch) + len(low_match)
    print(f"\n匹配质量 ({total_verified} 个已验证函数):")
    print(f"  100% 完美匹配:       {len(perfect):>4}")
    print(f"  >=90% (寄存器差异):  {len(near):>4}  (可接受)")
    print(f"  Size Mismatch:       {len(size_mismatch):>4}  (结构性差异，需重写)")
    print(f"  <90% 低匹配:         {len(low_match):>4}  (逻辑有差异)")

    if size_mismatch:
        print(f"\n  Size Mismatch 函数 (前20):")
        size_mismatch.sort(key=lambda x: -x[1]["total"])
        for name, q in size_mismatch[:20]:
            print(f"    {name:<50} {q['match']}/{q['total']}B")


def print_missing(entries, top_n=50):
    """Print unimplemented functions sorted by size."""
    missing = [e for e in entries
               if e.get("status") not in ("done", "stub", "not_needed", "auto")]
    missing.sort(key=lambda e: -e.get("size", 0))

    total_missing_bytes = sum(e.get("size", 0) for e in missing)
    named_missing = [e for e in missing if not e.get("name", "").startswith("sub_")]

    print(f"未实现函数: {len(missing)} 个, {total_missing_bytes/1024:.0f} KB")
    print(f"  其中有名称: {len(named_missing)} 个")
    print(f"  其中 sub_: {len(missing) - len(named_missing)} 个")
    print()
    print(f"有名称的未实现函数 (前 {top_n}, 按大小):")
    print(f"{'地址':<12} {'大小':>6} {'状态':<8} {'名称'}")
    print("-" * 80)

    shown = 0
    for e in missing:
        if e.get("name", "").startswith("sub_"):
            continue
        status = e.get("status", "?")
        print(f"{e['addr']:<12} {e.get('size',0):>5}B {status:<8} {e.get('name','?')}")
        shown += 1
        if shown >= top_n:
            break

    # Largest sub_ functions
    sub_missing = [e for e in missing if e.get("name", "").startswith("sub_")]
    if sub_missing:
        print(f"\n最大的 sub_ 函数 (前20):")
        for e in sub_missing[:20]:
            print(f"  {e['addr']:<12} {e.get('size',0):>5}B {e.get('name','?')}")


def print_by_class(entries):
    """Print progress grouped by class."""
    target = [e for e in entries if e.get("status") not in ("not_needed", "auto")]

    classes = defaultdict(list)
    for e in target:
        cls = get_class_name(e)
        classes[cls].append(e)

    print(f"{'类名':<30} {'总数':>5} {'done':>6} {'覆盖率':>7} {'缺失代码':>8}")
    print("-" * 65)

    rows = []
    for cls, cls_funcs in classes.items():
        total = len(cls_funcs)
        done = sum(1 for f in cls_funcs if f.get("status") == "done")
        missing_bytes = sum(f.get("size", 0) for f in cls_funcs
                           if f.get("status") not in ("done", "stub"))
        pct = 100 * done / total if total else 0
        rows.append((cls, total, done, pct, missing_bytes))

    rows.sort(key=lambda x: -x[4])
    for cls, total, done, pct, missing_bytes in rows:
        if missing_bytes > 0:
            print(f"{cls:<30} {total:>5} {done:>6} {pct:>6.1f}% {missing_bytes:>7}B")


def output_json(entries):
    """Write JSON progress report."""
    OUTPUT_JSON.parent.mkdir(parents=True, exist_ok=True)

    target = [e for e in entries if e.get("status") not in ("not_needed", "auto")]
    not_needed = [e for e in entries if e.get("status") in ("not_needed", "auto")]

    report = {
        "source": str(REGISTRY_FILE),
        "total_functions": len(entries),
        "excluded": len(not_needed),
        "target_functions": len(target),
        "done": sum(1 for e in target if e.get("status") == "done"),
        "stub": sum(1 for e in target if e.get("status") == "stub"),
        "todo": sum(1 for e in target if e.get("status") == "todo"),
        "unknown": sum(1 for e in target if e.get("status") == "unknown"),
        "done_bytes": sum(e.get("size", 0) for e in target if e.get("status") == "done"),
        "target_bytes": sum(e.get("size", 0) for e in target),
        "functions": [],
    }

    for e in entries:
        report["functions"].append({
            "addr": e.get("addr"),
            "size": e.get("size", 0),
            "name": e.get("name"),
            "status": e.get("status"),
            "file": e.get("file"),
            "class": get_class_name(e),
        })

    with open(OUTPUT_JSON, 'w') as fp:
        json.dump(report, fp, indent=2, ensure_ascii=False)
    print(f"Written: {OUTPUT_JSON}")


def main():
    parser = argparse.ArgumentParser(description='gbengine.dll 进度报告 (from registry)')
    parser.add_argument('--summary', action='store_true', help='简要摘要')
    parser.add_argument('--missing', nargs='?', const=50, type=int, help='未实现函数列表')
    parser.add_argument('--by-class', action='store_true', help='按类分组')
    parser.add_argument('--quality', action='store_true', help='字节匹配质量 (需编译)')
    parser.add_argument('--json', action='store_true', help='输出 JSON')
    args = parser.parse_args()

    entries = load_registry()

    if args.json:
        output_json(entries)
        return

    if args.summary:
        print_summary(entries)
    elif args.missing is not None:
        print_missing(entries, args.missing)
    elif args.by_class:
        print_by_class(entries)
    elif args.quality:
        print_summary(entries)
        print_quality(entries)
    else:
        print_summary(entries)
        print()
        print_by_class(entries)
        print()
        print_missing(entries, 30)


if __name__ == "__main__":
    main()
