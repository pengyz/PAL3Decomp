#!/usr/bin/env python3
"""
gbengine.dll - 全面进度跟踪工具

跟踪 IDA 索引中所有函数的实现状态，包括：
  - 导出函数 (DEF)
  - 内部函数 (非导出，被内部调用)
  - 第三方库函数 (AIL/D3DX/CRT, 不需要实现)

通过编译所有源文件并将 .obj 符号与 IDA 函数索引匹配。

用法:
    python tools/gbengine_progress.py                # 完整报告
    python tools/gbengine_progress.py --summary      # 简要摘要
    python tools/gbengine_progress.py --missing      # 未实现函数 (按大小排序)
    python tools/gbengine_progress.py --missing 100  # 前100个
    python tools/gbengine_progress.py --by-class     # 按类分组
    python tools/gbengine_progress.py --quality      # 字节匹配质量
    python tools/gbengine_progress.py --fast         # 快速模式 (不编译, 仅分析源码)
    python tools/gbengine_progress.py --json         # 输出 JSON 到 build/
"""

import re
import os
import sys
import json
import glob
import subprocess
import argparse
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
IDA_DIR = PROJECT_ROOT / "asm" / "gbengine_ida"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
DEF_FILE = SRC_DIR / "gbengine.def"
COMPARE_TOOL = PROJECT_ROOT / "tools" / "gbengine_compare.py"
OUTPUT_JSON = PROJECT_ROOT / "build" / "gbengine_progress.json"

# Thirdparty address threshold (D3DX/CRT code lives at high addresses)
THIRDPARTY_ADDR = 0x100D0000


def load_ida_index():
    """Load all IDA function data and categorize."""
    ida_files = sorted(glob.glob(str(IDA_DIR / "*.json")))

    # Load DEF exports
    def_exports = set()
    if DEF_FILE.exists():
        with open(DEF_FILE) as f:
            for line in f.readlines()[2:]:
                sym = line.strip().split()[0] if line.strip() else ""
                if sym and sym != "stamp":
                    def_exports.add(sym)

    funcs = []
    for fpath in ida_files:
        with open(fpath) as fp:
            d = json.load(fp)

        mangled = d.get("mangled_name", "")
        name = d.get("name", "")
        addr_str = d.get("address", "0")
        addr = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
        size = d.get("size_bytes", 0) or 0

        # Categorize
        if mangled in def_exports:
            category = "exported"
        elif name.startswith("AIL_") or name.startswith("_AIL_"):
            category = "thirdparty"
        elif addr >= THIRDPARTY_ADDR:
            category = "thirdparty"
        elif name.startswith("sub_"):
            category = "internal_unnamed"
        else:
            category = "internal_named"

        # Extract class name
        if "::" in name:
            cls = name.split("::")[0]
        else:
            cls = "(global)"

        funcs.append({
            "mangled": mangled,
            "name": name,
            "address": addr,
            "size": size,
            "category": category,
            "class": cls,
        })

    return funcs, def_exports


def compile_and_collect_symbols():
    """Compile all source files, collect symbols + byte-match quality."""
    symbols = {}  # demangled_name -> {match, total, size_ok, source}
    src_files = sorted(glob.glob(str(SRC_DIR / "*.cpp")))

    for src in src_files:
        r = subprocess.run(
            [sys.executable, str(COMPARE_TOOL), "--compile", src, "--all"],
            capture_output=True, text=True, timeout=120,
            cwd=str(PROJECT_ROOT)
        )

        current_func = None
        for line in r.stdout.split("\n"):
            m = re.match(r"^\s+(\S.*?):\s*$", line)
            if m:
                current_func = m.group(1)
                symbols[current_func] = {
                    "match": 0, "total": 0, "size_ok": True,
                    "source": os.path.basename(src)
                }
                continue

            if current_func:
                if "Size: MISMATCH" in line:
                    symbols[current_func]["size_ok"] = False
                m2 = re.search(r"Match: (\d+)/(\d+) bytes", line)
                if m2:
                    symbols[current_func]["match"] = int(m2.group(1))
                    symbols[current_func]["total"] = int(m2.group(2))

    return symbols


def fast_source_analysis():
    """Quick mode: just parse source files for function definitions (no compilation)."""
    symbols = {}
    for cpp in sorted(SRC_DIR.glob("*.cpp")):
        with open(cpp, 'r', errors='ignore') as f:
            content = f.read()
        # Find class::method patterns (e.g. gbTexture::LoadTexture)
        for m in re.finditer(r'(?:^|\n)\s*(?:[\w*& ]+\s+)?(\w+::~?\w+)\s*\(', content):
            func = m.group(1)
            symbols[func] = {"source": cpp.name, "match": 0, "total": 0, "size_ok": True}
        # Find global function definitions
        # Simple line-by-line scan for known function name patterns
        for line in content.split('\n'):
            line_s = line.strip()
            if '::' in line_s or line_s.startswith('//') or line_s.startswith('#'):
                continue
            m = re.match(r'(?:static\s+)?(?:void|int|float|double|char|unsigned|const|long|BOOL|HRESULT|gbVec3D|gbMatrix4)\s*\*?\s+(\w+)\s*\(', line_s)
            if m:
                func = m.group(1)
                if (func.startswith('gb') or func.startswith('Profile') or
                    func.startswith('CPK') or func.startswith('CIni') or
                    func.startswith('D3D') or func.startswith('BEZIER')):
                    symbols[func] = {"source": cpp.name, "match": 0, "total": 0, "size_ok": True}
    return symbols


def match_functions(funcs, compiled_symbols):
    """Mark which IDA functions are implemented."""
    # Build a set of short names (without parameter list) from compiled symbols
    # Also keep the full compiled_symbols for exact match
    for func in funcs:
        name = func["name"]
        # IDA names look like "gbTexture::LoadTexture(int)"
        # Source names look like "gbTexture::LoadTexture"
        # Strip parameter list for matching
        short_name = name.split("(")[0] if "(" in name else name
        if name in compiled_symbols:
            func["implemented"] = True
            func["quality"] = compiled_symbols[name]
        elif short_name in compiled_symbols:
            func["implemented"] = True
            func["quality"] = compiled_symbols[short_name]
        else:
            func["implemented"] = False
            func["quality"] = None


def print_summary(funcs):
    """Print progress summary."""
    cats = {"exported": [], "internal": [], "thirdparty": []}
    for f in funcs:
        cat = f["category"]
        if cat.startswith("internal"):
            cats["internal"].append(f)
        else:
            cats[cat].append(f)

    print("=" * 68)
    print(" gbengine.dll 反编译进度")
    print("=" * 68)
    print(f"{'类别':<20} {'总数':>5} {'已实现':>6} {'覆盖率':>7} {'代码(已/总)':>14}")
    print("-" * 68)

    target_total = 0
    target_impl = 0
    target_bytes = 0
    target_impl_bytes = 0

    for cat_name, display in [("exported", "导出函数"),
                               ("internal", "内部函数"),
                               ("thirdparty", "第三方库(不需实现)")]:
        cat_funcs = cats.get(cat_name, [])
        impl = sum(1 for f in cat_funcs if f.get("implemented"))
        total_bytes = sum(f["size"] for f in cat_funcs)
        impl_bytes = sum(f["size"] for f in cat_funcs if f.get("implemented"))
        pct = 100 * impl / len(cat_funcs) if cat_funcs else 0

        print(f"{display:<20} {len(cat_funcs):>5} {impl:>6} {pct:>6.1f}% "
              f"{impl_bytes/1024:>5.0f}/{total_bytes/1024:.0f} KB")

        if cat_name != "thirdparty":
            target_total += len(cat_funcs)
            target_impl += impl
            target_bytes += total_bytes
            target_impl_bytes += impl_bytes

    print("-" * 68)
    pct = 100 * target_impl / target_total if target_total else 0
    pct_bytes = 100 * target_impl_bytes / target_bytes if target_bytes else 0
    print(f"{'目标合计':<20} {target_total:>5} {target_impl:>6} {pct:>6.1f}% "
          f"{target_impl_bytes/1024:>5.0f}/{target_bytes/1024:.0f} KB")
    print()
    print(f"  按代码量: {pct_bytes:.1f}% 已实现 "
          f"({target_impl_bytes/1024:.0f} / {target_bytes/1024:.0f} KB)")
    print()

    # Internal function breakdown
    unnamed = [f for f in cats["internal"] if f["category"] == "internal_unnamed"]
    named = [f for f in cats["internal"] if f["category"] == "internal_named"]
    print(f"  内部函数细分:")
    print(f"    有名称: {len(named)} 个 ({sum(f['size'] for f in named)/1024:.0f} KB)")
    print(f"    sub_XX: {len(unnamed)} 个 ({sum(f['size'] for f in unnamed)/1024:.0f} KB)")


def print_quality(funcs):
    """Print byte-match quality breakdown."""
    implemented = [f for f in funcs if f.get("implemented") and f.get("quality")]

    perfect = []
    near = []
    size_mismatch = []
    low_match = []

    for f in implemented:
        q = f["quality"]
        if q["total"] == 0:
            continue
        ratio = q["match"] / q["total"]
        if q["match"] == q["total"]:
            perfect.append(f)
        elif not q["size_ok"]:
            size_mismatch.append(f)
        elif ratio >= 0.9:
            near.append(f)
        else:
            low_match.append(f)

    print(f"\n匹配质量 ({len(implemented)} 个已实现函数):")
    print(f"  100% 完美匹配:       {len(perfect):>4}")
    print(f"  >=90% (寄存器差异):  {len(near):>4}  (可接受)")
    print(f"  Size Mismatch:       {len(size_mismatch):>4}  (结构性差异，需重写)")
    print(f"  <90% 低匹配:         {len(low_match):>4}  (逻辑有差异)")

    if size_mismatch:
        print(f"\n  Size Mismatch 函数 (前20):")
        for f in sorted(size_mismatch, key=lambda x: -x["size"])[:20]:
            q = f["quality"]
            print(f"    {f['name']:<50} {q['match']}/{q['total']}B "
                  f"[{f['quality']['source']}]")


def print_missing(funcs, top_n=50):
    """Print unimplemented functions sorted by size."""
    missing = [f for f in funcs
               if not f.get("implemented") and f["category"] != "thirdparty"]
    missing.sort(key=lambda x: -x["size"])

    total_missing_bytes = sum(f["size"] for f in missing)
    named_missing = [f for f in missing if not f["name"].startswith("sub_")]

    print(f"未实现函数: {len(missing)} 个, {total_missing_bytes/1024:.0f} KB")
    print(f"  其中有名称: {len(named_missing)} 个")
    print(f"  其中 sub_: {len(missing) - len(named_missing)} 个")
    print()
    print(f"有名称的未实现函数 (前 {top_n}, 按大小):")
    print(f"{'地址':<12} {'大小':>6} {'类型':<5} {'名称'}")
    print("-" * 80)

    shown = 0
    for f in missing:
        if f["name"].startswith("sub_"):
            continue
        cat_short = "EXP" if f["category"] == "exported" else "INT"
        print(f"0x{f['address']:08X} {f['size']:>5}B {cat_short:<5} {f['name']}")
        shown += 1
        if shown >= top_n:
            break

    # Also show largest sub_ functions
    sub_missing = [f for f in missing if f["name"].startswith("sub_")]
    if sub_missing:
        print(f"\n最大的 sub_ 函数 (前20):")
        for f in sub_missing[:20]:
            print(f"  0x{f['address']:08X} {f['size']:>5}B {f['name']}")


def print_by_class(funcs):
    """Print progress grouped by class."""
    classes = {}
    for f in funcs:
        if f["category"] == "thirdparty":
            continue
        cls = f["class"]
        classes.setdefault(cls, []).append(f)

    print(f"{'类名':<30} {'总数':>5} {'已实现':>6} {'覆盖率':>7} {'缺失代码':>8}")
    print("-" * 65)

    rows = []
    for cls, cls_funcs in classes.items():
        total = len(cls_funcs)
        impl = sum(1 for f in cls_funcs if f.get("implemented"))
        missing_bytes = sum(f["size"] for f in cls_funcs if not f.get("implemented"))
        pct = 100 * impl / total if total else 0
        rows.append((cls, total, impl, pct, missing_bytes))

    rows.sort(key=lambda x: -x[4])
    for cls, total, impl, pct, missing_bytes in rows:
        if missing_bytes > 0:
            print(f"{cls:<30} {total:>5} {impl:>6} {pct:>6.1f}% {missing_bytes:>7}B")


def output_json(funcs):
    """Write JSON progress report."""
    OUTPUT_JSON.parent.mkdir(parents=True, exist_ok=True)

    report = {
        "total_ida_functions": len(funcs),
        "categories": {},
        "functions": [],
    }

    cats = defaultdict(lambda: {"total": 0, "implemented": 0, "bytes_total": 0, "bytes_impl": 0})
    for f in funcs:
        cat = f["category"] if not f["category"].startswith("internal") else "internal"
        cats[cat]["total"] += 1
        cats[cat]["bytes_total"] += f["size"]
        if f.get("implemented"):
            cats[cat]["implemented"] += 1
            cats[cat]["bytes_impl"] += f["size"]

        report["functions"].append({
            "name": f["name"],
            "address": f"0x{f['address']:08X}",
            "size": f["size"],
            "category": f["category"],
            "class": f["class"],
            "implemented": f.get("implemented", False),
        })

    report["categories"] = dict(cats)
    with open(OUTPUT_JSON, 'w') as fp:
        json.dump(report, fp, indent=2, ensure_ascii=False)
    print(f"Written: {OUTPUT_JSON}")


def main():
    parser = argparse.ArgumentParser(description='gbengine.dll 全面进度跟踪')
    parser.add_argument('--summary', action='store_true', help='简要摘要')
    parser.add_argument('--missing', nargs='?', const=50, type=int, help='未实现函数列表')
    parser.add_argument('--by-class', action='store_true', help='按类分组')
    parser.add_argument('--quality', action='store_true', help='字节匹配质量')
    parser.add_argument('--fast', action='store_true', help='快速模式 (不编译)')
    parser.add_argument('--json', action='store_true', help='输出 JSON')
    args = parser.parse_args()

    print("加载 IDA 索引...", file=sys.stderr)
    funcs, def_exports = load_ida_index()
    print(f"  {len(funcs)} 个函数, {len(def_exports)} 个导出", file=sys.stderr)

    if args.fast:
        print("快速模式: 分析源码...", file=sys.stderr)
        compiled = fast_source_analysis()
    else:
        print("编译源文件并收集符号...", file=sys.stderr)
        compiled = compile_and_collect_symbols()
    print(f"  {len(compiled)} 个已编译符号", file=sys.stderr)

    match_functions(funcs, compiled)

    if args.json:
        output_json(funcs)
        return

    print()  # separator after stderr

    if args.summary:
        print_summary(funcs)
    elif args.missing is not None:
        print_missing(funcs, args.missing)
    elif args.by_class:
        print_by_class(funcs)
    elif args.quality:
        print_summary(funcs)
        print()
        print_quality(funcs)
    else:
        print_summary(funcs)
        print()
        print_quality(funcs)
        print()
        print_by_class(funcs)
        print()
        print_missing(funcs, 30)


if __name__ == "__main__":
    main()
