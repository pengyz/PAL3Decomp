#!/usr/bin/env python3
"""
gbengine 函数注册表初始化脚本

从 IDA 索引 + linker map 文件 + DEF 文件生成 data/gbengine_registry.jsonl。

数据源优先级:
1. build/gbengine.map — 链接器输出，精确的 mangled name → 地址 + obj 文件映射
2. asm/gbengine_ida/*.json — IDA 反编译导出，提供函数名/大小/地址
3. src/gbengine/gbengine.def — DLL 导出符号列表

步骤:
1. 读取 IDA 索引 → 全量函数列表 (addr, size, name, mangled)
2. 解析 map 文件 → 精确匹配已编译符号 (mangled → addr → obj file)
3. 分类 not_needed (带详细原因):
   - CRT runtime (地址 >= 0x100D0000)
   - D3DX9 静态库 (obj 名含 d3dx/D3DX/cprogram 等)
   - Miles Sound System (AIL_* 前缀)
   - 编译器辅助 (vector ctor/dtor helper, __ehvec 等)
4. 分类 auto (编译器自动生成, 不需手写):
   - vector/scalar deleting destructor
   - default constructor closure
   - dynamic initializer/atexit destructor
5. 已编译且在 map 中的 → done (带 file 和 our_name)
6. 输出排序后的 JSONL

用法:
    python tools/registry_init.py              # 生成注册表 (使用 map 文件)
    python tools/registry_init.py --dry-run    # 不写入，仅统计
"""

import json
import glob
import os
import re
import sys
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
IDA_DIR = PROJECT_ROOT / "asm" / "gbengine_ida"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
DEF_FILE = SRC_DIR / "gbengine.def"
MAP_FILE = PROJECT_ROOT / "build" / "gbengine.map"
OUTPUT_FILE = PROJECT_ROOT / "data" / "gbengine_registry.jsonl"

# ─── not_needed 分类规则 ───────────────────────────────────────────────────────

# 地址阈值: >= 此地址的函数属于 CRT/compiler runtime
CRT_ADDR_THRESHOLD = 0x100D0000

# Map 文件中 obj 名匹配 → 第三方静态库 (obj_name → reason)
THIRDPARTY_OBJ_RULES = [
    (r"^d3dx9:", "D3DX9 静态库"),
    (r"^LIBCMT:", "MSVC CRT (LIBCMT.lib)"),
    (r"^d3d9:", "D3D9 导入库 (thunk)"),
    (r"^kernel32:", "kernel32 导入库 (thunk)"),
    (r"^ijl15:", "Intel JPEG Library (thunk)"),
    (r"(?i)minilzo", "LZO 压缩库 (minilzo)"),
]

# 函数名前缀 → not_needed + 原因
NOT_NEEDED_NAME_RULES = [
    (["AIL_", "_AIL_"], "Miles Sound System (静态链接)"),
    (["MSS_", "_MSS_"], "Miles Sound System"),
    (["_LZO_", "lzo_", "lzo1"], "LZO 压缩库"),
]

# 函数名正则 → not_needed + 原因
NOT_NEEDED_REGEX_RULES = [
    (r"^_(?:malloc|free|realloc|calloc|msize|expand|heapchk|heapmin)$", "CRT 堆管理"),
    (r"^_(?:exit|abort|atexit|_?onexit|cexit|c_exit)$", "CRT 进程控制"),
    (r"^__?(?:alloca_probe|chkstk|security_check|report_)", "CRT 栈保护/安全"),
    (r"^_(?:ftol2?|CIpow|CIlog|CIexp|CIsqrt|CIatan|CIsin|CIcos|CIfmod)", "CRT 浮点数学"),
    (r"^_(?:fltused|fpmath|clearfp|control87|statusfp)", "CRT 浮点控制"),
    (r"^__?except_handler\d?", "SEH 异常处理 (CRT)"),
    (r"^_(?:purecall|amsg_exit|NMSG_WRITE|nmsg_write)", "CRT 错误处理"),
    (r"^_(?:initterm|cinit|initp|wctomb|mbtowc|mbstowcs)", "CRT 初始化/locale"),
    (r"^_?(?:setjmp|longjmp)\d?$", "CRT setjmp/longjmp"),
    (r"^__?CxxFrameHandler", "C++ 异常处理 (编译器运行时)"),
    (r"^__?CxxThrowException", "C++ throw (编译器运行时)"),
    (r"^__?(?:Unwind|unwind)", "SEH unwind (编译器运行时)"),
    (r"^_?(?:RTC_|_RTC_)", "运行时错误检查 (编译器)"),
    (r"^__security_", "安全 cookie (编译器)"),
]

# ─── auto 分类规则 (编译器自动生成，不需手写) ─────────────────────────────────

AUTO_PATTERNS = [
    (r"`vector deleting destructor'", "编译器生成: vector deleting destructor"),
    (r"`scalar deleting destructor'", "编译器生成: scalar deleting destructor"),
    (r"`default constructor closure'", "编译器生成: default constructor closure"),
    (r"`vftable'", "虚函数表数据"),
    (r"`vbtable'", "虚基类表数据"),
    (r"`RTTI ", "RTTI 类型信息"),
    (r"`eh vector constructor iterator'", "编译器生成: eh vector ctor"),
    (r"`eh vector destructor iterator'", "编译器生成: eh vector dtor"),
    (r"`vector constructor iterator'", "编译器生成: vector ctor iterator"),
    (r"`vector destructor iterator'", "编译器生成: vector dtor iterator"),
    (r"`dynamic initializer for", "编译器生成: 动态初始化"),
    (r"`dynamic atexit destructor for", "编译器生成: 动态析构"),
    (r"__vec_ctor", "编译器生成: vector ctor helper"),
    (r"__vec_dtor", "编译器生成: vector dtor helper"),
    (r"\?\?_[EG]", "编译器生成: vector/scalar dtor (mangled)"),
    (r"\?\?_H@", "编译器生成: vector new helper (??_H)"),
    (r"\?\?_L@", "编译器生成: vector delete helper (??_L)"),
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
        if basename == "_export_summary.json":
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


def parse_map_file():
    """Parse linker map file for compiled symbols.

    Returns dict: mangled_name -> (addr_str, obj_file)
    """
    symbols = {}
    if not MAP_FILE.exists():
        print(f"  警告: map 文件不存在: {MAP_FILE}", file=sys.stderr)
        print(f"  请先编译 gbengine.dll 生成 map 文件", file=sys.stderr)
        return symbols

    with open(MAP_FILE) as f:
        in_publics = False
        for line in f:
            if "Publics by Value" in line:
                in_publics = True
                continue
            if in_publics and line.strip():
                # Format: ' 0001:00000000       ??0BEZIER@@QAE@PAUgbVec3D@@@Z 10001000 f   BEZIER.cpp.obj'
                m = re.match(r"\s+\w+:\w+\s+(\S+)\s+([\da-fA-F]+)\s+f\s+(\S+)", line)
                if m:
                    mangled = m.group(1)
                    addr = int(m.group(2), 16)
                    obj = m.group(3)
                    symbols[mangled] = (f"0x{addr:08X}", obj)

    return symbols


def obj_to_source_file(obj_name):
    """Convert obj file name to source file name.

    E.g. 'BEZIER.cpp.obj' -> 'BEZIER.cpp'
         'gbCamera.cpp.obj' -> 'gbCamera.cpp'
         'i' -> None (internal/thirdparty)
    """
    if obj_name in ("i", "f"):
        return None
    if obj_name.endswith(".cpp.obj"):
        return obj_name[:-4]  # strip .obj
    if obj_name.endswith(".obj"):
        return obj_name[:-4] + ".cpp"  # guess .cpp
    return None


def classify_thirdparty_obj(obj_name):
    """Check if obj belongs to a thirdparty library.

    Returns (is_thirdparty: bool, reason: str or None)
    """
    if not obj_name:
        return False, None
    for pat, reason in THIRDPARTY_OBJ_RULES:
        if re.search(pat, obj_name):
            return True, reason
    return False, None


def classify_not_needed(name, mangled, addr_int, obj_name=None):
    """Determine if function is not_needed and return reason.

    Returns (is_not_needed: bool, reason: str or None)
    """
    # Rule 1: CRT by address
    if addr_int >= CRT_ADDR_THRESHOLD:
        return True, "CRT/compiler runtime (地址 >= 0x100D0000)"

    # Rule 2: thirdparty by obj name (from map file)
    is_tp, tp_reason = classify_thirdparty_obj(obj_name)
    if is_tp:
        return True, tp_reason

    # Rule 3: name prefix rules
    for prefixes, reason in NOT_NEEDED_NAME_RULES:
        for prefix in prefixes:
            if name.startswith(prefix):
                return True, reason

    # Rule 4: name regex rules
    for pat, reason in NOT_NEEDED_REGEX_RULES:
        if re.match(pat, name):
            return True, reason
        if re.match(pat, mangled):
            return True, reason

    return False, None


def classify_auto(name, mangled):
    """Determine if function is auto-generated and return reason.

    Returns (is_auto: bool, reason: str or None)
    """
    for pat, reason in AUTO_PATTERNS:
        if re.search(pat, name):
            return True, reason
        if re.search(pat, mangled):
            return True, reason
    return False, None


def build_registry(funcs, map_symbols, def_exports):
    """Build registry entries with proper classification."""
    entries = []

    # NOTE: map 地址和原始 DLL 地址布局不同（我们的编译产物函数排列不同），
    # 所以 **只能用 mangled name 匹配**，不能用地址匹配。

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

        # Check if this function exists in our compiled map (by mangled name ONLY)
        # NOTE: map 地址和原始 DLL 地址不同，只能用 mangled name 做匹配。
        map_info = map_symbols.get(mangled)
        obj_name = map_info[1] if map_info else None

        # 如果 mangled 是 sub_XXXXXXXX 格式，在 map 中肯定找不到，跳过
        # (IDA 中未识别的函数无法用 mangled 匹配)

        # ─── Classification priority ───

        # 1. not_needed check (with detailed reason)
        is_nn, nn_reason = classify_not_needed(name, mangled, addr_int, obj_name)
        if is_nn:
            entry["status"] = "not_needed"
            entry["note"] = nn_reason
            entries.append(entry)
            continue

        # 2. auto-generated check
        is_auto, auto_reason = classify_auto(name, mangled)
        if is_auto:
            entry["status"] = "auto"
            entry["note"] = auto_reason
            entries.append(entry)
            continue

        # 3. Matched in our compiled code (map file has it)
        if map_info:
            source_file = obj_to_source_file(obj_name) if obj_name else None
            if source_file:
                # Verify source file actually exists
                if (SRC_DIR / source_file).exists():
                    entry["status"] = "done"
                    entry["file"] = source_file
                    short_name = name.split("(")[0] if "(" in name else name
                    entry["our_name"] = short_name
                else:
                    # Obj exists in map but source file not found → might be library
                    entry["status"] = "done"
                    entry["file"] = source_file
                    short_name = name.split("(")[0] if "(" in name else name
                    entry["our_name"] = short_name
            else:
                # obj is 'i' (internal/imported) — likely CRT helper or thunk
                # These are linker-generated, not from our source
                entry["status"] = "auto"
                entry["note"] = f"链接器内部生成 (obj={obj_name})"

            entries.append(entry)
            continue

        # 4. Named but not implemented → todo
        if not name.startswith("sub_"):
            entry["status"] = "todo"
            entries.append(entry)
            continue

        # 5. Unnamed sub_ → unknown
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

    # not_needed 原因细分
    nn_entries = [e for e in entries if e["status"] == "not_needed"]
    reasons = defaultdict(int)
    for e in nn_entries:
        # 取原因的大类
        note = e.get("note", "unknown")
        if "CRT" in note or "compiler runtime" in note:
            reasons["CRT/编译器运行时"] += 1
        elif "D3DX" in note:
            reasons["D3DX9 静态库"] += 1
        elif "Miles" in note:
            reasons["Miles Sound System"] += 1
        elif "LZO" in note:
            reasons["LZO 压缩库"] += 1
        else:
            reasons[note] += 1

    if reasons:
        print()
        print(f"  not_needed 原因细分:")
        for reason, count in sorted(reasons.items(), key=lambda x: -x[1]):
            print(f"    {reason:<35} {count:>5}")

    # auto 原因细分
    auto_entries = [e for e in entries if e["status"] == "auto"]
    auto_reasons = defaultdict(int)
    for e in auto_entries:
        note = e.get("note", "unknown")
        if "vector" in note or "scalar" in note:
            auto_reasons["deleting destructor"] += 1
        elif "链接器" in note:
            auto_reasons["链接器内部生成"] += 1
        elif "ctor" in note or "dtor" in note:
            auto_reasons["vector ctor/dtor iterator"] += 1
        elif "动态" in note:
            auto_reasons["动态初始化/析构"] += 1
        else:
            auto_reasons[note[:30]] += 1

    if auto_entries:
        print()
        print(f"  auto 原因细分:")
        for reason, count in sorted(auto_reasons.items(), key=lambda x: -x[1]):
            print(f"    {reason:<35} {count:>5}")

    # Progress
    not_needed = by_status.get("not_needed", 0)
    auto = by_status.get("auto", 0)
    target = total - not_needed - auto
    done = by_status.get("done", 0)

    target_bytes = sum(e["size"] for e in entries
                       if e["status"] not in ("not_needed", "auto"))
    done_bytes = sum(e["size"] for e in entries if e["status"] == "done")

    print()
    print(f"  {'─'*40}")
    print(f"  目标函数: {target} (排除 {not_needed} not_needed + {auto} auto)")
    print(f"  已完成 (done): {done} ({100*done/target:.1f}%)")
    print(f"  代码覆盖: {done_bytes/1024:.1f} / {target_bytes/1024:.1f} KB "
          f"({100*done_bytes/target_bytes:.1f}%)")
    print()


def main():
    import argparse
    parser = argparse.ArgumentParser(description="初始化 gbengine 函数注册表")
    parser.add_argument("--dry-run", action="store_true",
                        help="不写入文件，仅显示统计")
    args = parser.parse_args()

    print("加载 IDA 索引...", file=sys.stderr)
    funcs = load_ida_functions()
    print(f"  {len(funcs)} 个函数", file=sys.stderr)

    print("加载 DEF 导出...", file=sys.stderr)
    def_exports = load_def_exports()
    print(f"  {len(def_exports)} 个导出符号", file=sys.stderr)

    print("解析 map 文件...", file=sys.stderr)
    map_symbols = parse_map_file()
    print(f"  {len(map_symbols)} 个已编译符号", file=sys.stderr)

    print("构建注册表...", file=sys.stderr)
    entries = build_registry(funcs, map_symbols, def_exports)

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
