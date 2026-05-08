#!/usr/bin/env python3
"""
gbengine 函数注册表初始化脚本

从 IDA 索引 + 编译符号 + DEF 文件生成初始 data/gbengine_registry.jsonl。

步骤:
1. 读取 asm/gbengine_ida/*.json → 生成全量条目 (status=unknown)
2. 地址 >= 0x100D0000 → status=not_needed, note="CRT/thirdparty"
3. 名字匹配 AIL_* / D3DX patterns → status=not_needed
4. 匹配编译器生成的函数 → status=auto
5. 编译源码收集符号 → 匹配到的标 status=done
6. 输出 data/gbengine_registry.jsonl (按地址排序)

用法:
    python tools/registry_init.py              # 生成注册表 (快速模式，仅分析源码)
    python tools/registry_init.py --compile    # 编译源码并匹配 (更准确但慢)
    python tools/registry_init.py --dry-run    # 不写入，仅统计
"""

import json
import glob
import os
import re
import sys
import subprocess
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
IDA_DIR = PROJECT_ROOT / "asm" / "gbengine_ida"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
DEF_FILE = SRC_DIR / "gbengine.def"
OUTPUT_FILE = PROJECT_ROOT / "data" / "gbengine_registry.jsonl"
COMPARE_TOOL = PROJECT_ROOT / "tools" / "gbengine_compare.py"

# Address threshold for thirdparty code (D3DX/CRT)
THIRDPARTY_ADDR = 0x100D0000

# Patterns that indicate thirdparty/not-needed functions
THIRDPARTY_PREFIXES = [
    "AIL_", "_AIL_", "MSS_", "_MSS_",
]

THIRDPARTY_PATTERNS = [
    r"^_(?:malloc|free|realloc|calloc|msize)$",
    r"^_(?:exit|abort|atexit|onexit)$",
    r"^__(?:alloca|chkstk|security_check|report)",
    r"^_(?:ftol|CIpow|CIlog|CIexp|CIsqrt|CIatan)",
    r"^_(?:fltused|except_handler)",
    r"^_(?:purecall|nmsg_write)",
]

# Patterns for auto-generated functions
AUTO_PATTERNS = [
    r"vector deleting destructor",
    r"scalar deleting destructor",
    r"default constructor closure",
    r"`vftable'",
    r"`vbtable'",
    r"`RTTI ",
    r"__vec_dtor",
    r"`eh vector ",
    r"`dynamic initializer",
    r"`dynamic atexit destructor",
]


def load_def_exports():
    """Load exported symbol names from DEF file."""
    exports = set()
    if DEF_FILE.exists():
        with open(DEF_FILE) as f:
            for line in f.readlines()[2:]:  # skip LIBRARY and EXPORTS lines
                sym = line.strip().split()[0] if line.strip() else ""
                if sym and sym != "stamp":
                    exports.add(sym)
    return exports


def load_ida_functions():
    """Load all IDA function data."""
    funcs = []
    ida_files = sorted(glob.glob(str(IDA_DIR / "*.json")))

    for fpath in ida_files:
        basename = os.path.basename(fpath)
        if basename == "_export_summary.json":  # skip metadata file
            continue

        with open(fpath) as fp:
            d = json.load(fp)

        if "address" not in d:
            continue

        funcs.append({
            "addr": d["address"],
            "size": d.get("size_bytes", 0) or 0,
            "name": d.get("name", ""),
            "mangled": d.get("mangled_name", ""),
        })

    return funcs


def is_thirdparty_name(name):
    """Check if function name indicates thirdparty code."""
    for prefix in THIRDPARTY_PREFIXES:
        if name.startswith(prefix):
            return True
    for pat in THIRDPARTY_PATTERNS:
        if re.match(pat, name):
            return True
    return False


def is_auto_generated(name):
    """Check if function name indicates compiler-generated code."""
    for pat in AUTO_PATTERNS:
        if re.search(pat, name):
            return True
    return False


def fast_source_analysis():
    """Parse source files to collect implemented function names."""
    # Returns a dict: short_name -> source_file
    symbols = {}
    for cpp in sorted(SRC_DIR.glob("*.cpp")):
        with open(cpp, 'r', errors='ignore') as f:
            content = f.read()

        # Find class::method patterns
        for m in re.finditer(r'(?:^|\n)\s*(?:[\w*&\s]+\s+)?(\w+::~?\w+)\s*\(', content):
            func = m.group(1)
            symbols[func] = cpp.name

        # Find global function definitions
        for line in content.split('\n'):
            line_s = line.strip()
            if '::' in line_s or line_s.startswith('//') or line_s.startswith('#'):
                continue
            m = re.match(
                r'(?:static\s+)?(?:void|int|float|double|char|unsigned|const|long|BOOL|HRESULT|LRESULT|'
                r'gbVec3D|gbMatrix4|gbColorFlt|DWORD|BYTE|WORD)\s*\*?\s+(\w+)\s*\(',
                line_s
            )
            if m:
                func = m.group(1)
                # Only include plausible gbengine functions
                if (func.startswith('gb') or func.startswith('Profile') or
                    func.startswith('CPK') or func.startswith('CIni') or
                    func.startswith('D3D') or func.startswith('BEZIER') or
                    func.startswith('Dll') or func == 'fn'):
                    symbols[func] = cpp.name

    return symbols


def compile_and_collect_symbols():
    """Compile all source files and collect mangled symbol names."""
    # Returns dict: mangled_name -> source_file
    symbols = {}
    src_files = sorted(glob.glob(str(SRC_DIR / "*.cpp")))

    for src in src_files:
        try:
            r = subprocess.run(
                [sys.executable, str(COMPARE_TOOL), "--compile", src, "--all"],
                capture_output=True, text=True, timeout=120,
                cwd=str(PROJECT_ROOT)
            )
        except (subprocess.TimeoutExpired, Exception):
            continue

        basename = os.path.basename(src)
        current_func = None
        for line in r.stdout.split("\n"):
            m = re.match(r"^\s+(\S.*?):\s*$", line)
            if m:
                current_func = m.group(1)
                symbols[current_func] = basename
                continue

    return symbols


def match_compiled_to_ida(funcs, compiled_symbols):
    """Match compiled symbols to IDA functions, return set of matched addresses."""
    # Build lookup by short name (without params)
    matched = {}  # addr -> source_file

    for func in funcs:
        name = func["name"]
        mangled = func["mangled"]
        addr = func["addr"]

        # Try exact mangled match
        if mangled in compiled_symbols:
            matched[addr] = compiled_symbols[mangled]
            continue

        # Try short name match (strip parameter list)
        short_name = name.split("(")[0] if "(" in name else name
        if short_name in compiled_symbols:
            matched[addr] = compiled_symbols[short_name]
            continue

        # Try name match (full)
        if name in compiled_symbols:
            matched[addr] = compiled_symbols[name]

    return matched


def build_registry(funcs, matched, def_exports):
    """Build registry entries with status assignments."""
    entries = []

    for func in funcs:
        addr_str = func["addr"]
        addr_int = int(addr_str, 16) if isinstance(addr_str, str) else addr_str
        name = func["name"]
        mangled = func["mangled"]
        size = func["size"]

        entry = {
            "addr": addr_str if isinstance(addr_str, str) else f"0x{addr_str:08X}",
            "size": size,
            "name": name,
            "mangled": mangled,
            "status": "unknown",
            "file": None,
            "our_name": None,
            "note": None,
        }

        # Rule 1: thirdparty by address
        if addr_int >= THIRDPARTY_ADDR:
            entry["status"] = "not_needed"
            entry["note"] = "CRT/thirdparty (high address)"

        # Rule 2: thirdparty by name
        elif is_thirdparty_name(name):
            entry["status"] = "not_needed"
            entry["note"] = "thirdparty library"

        # Rule 3: auto-generated
        elif is_auto_generated(name):
            entry["status"] = "auto"
            entry["note"] = "compiler-generated"

        # Rule 4: matched from compilation
        elif addr_str in matched:
            entry["status"] = "done"
            entry["file"] = matched[addr_str]
            short_name = name.split("(")[0] if "(" in name else name
            entry["our_name"] = short_name

        # Rule 5: remaining named functions → todo
        elif not name.startswith("sub_"):
            entry["status"] = "todo"

        # Rule 6: unnamed sub_ functions
        else:
            entry["status"] = "unknown"

        entries.append(entry)

    return entries


def print_stats(entries):
    """Print statistics about the registry."""
    by_status = defaultdict(int)
    by_status_bytes = defaultdict(int)
    for e in entries:
        by_status[e["status"]] += 1
        by_status_bytes[e["status"]] += e["size"]

    total = len(entries)
    print(f"\n{'='*60}")
    print(f" gbengine 函数注册表统计")
    print(f"{'='*60}")
    print(f"  总函数数: {total}")
    print()
    print(f"  {'状态':<12} {'数量':>6} {'代码量':>10}")
    print(f"  {'-'*35}")
    for status in ["done", "stub", "todo", "not_needed", "auto", "unknown"]:
        count = by_status.get(status, 0)
        bytes_val = by_status_bytes.get(status, 0)
        if count > 0:
            print(f"  {status:<12} {count:>6} {bytes_val/1024:>8.1f} KB")

    # Progress calculation
    not_needed = by_status.get("not_needed", 0)
    auto = by_status.get("auto", 0)
    target = total - not_needed - auto
    done = by_status.get("done", 0)
    stub = by_status.get("stub", 0)

    target_bytes = sum(e["size"] for e in entries
                       if e["status"] not in ("not_needed", "auto"))
    done_bytes = sum(e["size"] for e in entries if e["status"] == "done")

    print()
    print(f"  目标函数: {target} (排除 not_needed + auto)")
    print(f"  已完成: {done} ({100*done/target:.1f}%)")
    print(f"  代码覆盖: {done_bytes/1024:.1f} / {target_bytes/1024:.1f} KB "
          f"({100*done_bytes/target_bytes:.1f}%)")
    print()


def main():
    import argparse
    parser = argparse.ArgumentParser(description="初始化 gbengine 函数注册表")
    parser.add_argument("--compile", action="store_true",
                        help="编译源码匹配 (更准确但慢)")
    parser.add_argument("--dry-run", action="store_true",
                        help="不写入文件，仅显示统计")
    args = parser.parse_args()

    print("加载 IDA 索引...", file=sys.stderr)
    funcs = load_ida_functions()
    print(f"  {len(funcs)} 个函数", file=sys.stderr)

    print("加载 DEF 导出...", file=sys.stderr)
    def_exports = load_def_exports()
    print(f"  {len(def_exports)} 个导出符号", file=sys.stderr)

    if args.compile:
        print("编译源码收集符号...", file=sys.stderr)
        compiled_symbols = compile_and_collect_symbols()
    else:
        print("快速模式: 分析源码...", file=sys.stderr)
        compiled_symbols = fast_source_analysis()
    print(f"  {len(compiled_symbols)} 个已实现符号", file=sys.stderr)

    print("匹配函数...", file=sys.stderr)
    matched = match_compiled_to_ida(funcs, compiled_symbols)
    print(f"  {len(matched)} 个匹配成功", file=sys.stderr)

    print("构建注册表...", file=sys.stderr)
    entries = build_registry(funcs, matched, def_exports)

    # Sort by address
    entries.sort(key=lambda e: int(e["addr"], 16))

    print_stats(entries)

    if args.dry_run:
        print("(dry-run 模式, 未写入文件)")
        return

    # Write JSONL
    OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(OUTPUT_FILE, 'w') as f:
        for entry in entries:
            # Remove None values to keep JSONL compact
            clean = {k: v for k, v in entry.items() if v is not None}
            f.write(json.dumps(clean, ensure_ascii=False) + "\n")

    print(f"已写入: {OUTPUT_FILE}")
    print(f"  共 {len(entries)} 条记录")


if __name__ == "__main__":
    main()
