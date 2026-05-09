#!/usr/bin/env python3
"""
PAL3.exe 调用图管理工具

以 WinMain (0x00541900) 为根，BFS 展开调用链，管理反编译工作队列。

用法:
    python tools/pal3_callgraph.py init         # 初始化调用图
    python tools/pal3_callgraph.py status       # 显示进度统计
    python tools/pal3_callgraph.py frontier     # 列出当前 frontier
    python tools/pal3_callgraph.py next         # 选取下一个目标 (JSON)
    python tools/pal3_callgraph.py expand <addr>  # 标记完成并展开 callees
    python tools/pal3_callgraph.py update <addr> --status <s> [--match-rate <r>] [--source <p>]
    python tools/pal3_callgraph.py show <addr>  # 显示节点详情
    python tools/pal3_callgraph.py validate     # 验证数据一致性
"""

import argparse
import json
import os
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
CALLGRAPH_PATH = PROJECT_ROOT / "asm" / "pal3" / "call_graph.json"
NAMES_PATH = PROJECT_ROOT / "asm" / "pal3" / "pal3_names.json"
PDB_EXPORT_PATH = PROJECT_ROOT / "asm" / "pal3a" / "pdb_export.json"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
SRC_DIR = PROJECT_ROOT / "src" / "pal3"

# PAL3.exe .text range
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

# Known external/CRT functions to exclude from call graph
EXTERNAL_PREFIXES = [
    # Windows API
    "GetModuleHandle", "LoadLibrary", "GetProcAddress", "CreateWindow",
    "ShowWindow", "UpdateWindow", "PeekMessage", "GetMessage", "TranslateMessage",
    "DispatchMessage", "PostQuitMessage", "DefWindowProc", "RegisterClass",
    "FindWindow", "IsWindow", "SetWindowsHookEx", "UnhookWindowsHookEx",
    "CallNextHookEx", "LoadCursor", "GetDriveType", "GetModuleFileName",
    "RegOpenKeyEx", "RegQueryValueEx", "RegCloseKey", "MessageBox",
    "GetActiveWindow", "Sleep", "GetKeyState", "SetCursor",
    # CRT
    "operator new", "operator delete", "memset", "memcpy", "memmove",
    "sprintf", "printf", "strlen", "strcpy", "strcat", "strrchr", "strcmp",
    "strchr", "strncpy", "strncmp", "atoi", "atof", "sscanf",
    "malloc", "free", "calloc", "realloc",
    "_purecall", "__CxxFrameHandler",
    # gbengine.dll imports (via IAT)
    "gbUpdateCurTime", "gbTimeCounterInit",
]

# Patterns that indicate external/imported functions
EXTERNAL_PATTERNS = [
    r"^__imp_",          # IAT imports
    r"^_imp_",
    r"^\?\?[0-3]",       # RTTI/type_info constructors
    r"^__ehhandler",
    r"^__unwindfunclet",
]


def load_names():
    """Load pal3_names.json function database."""
    with open(NAMES_PATH) as f:
        data = json.load(f)
    # Build address -> info map
    addr_map = {}
    for func in data["functions"]:
        addr = int(func["address"], 16)
        addr_map[addr] = func
    return addr_map


_source_map_cache = None


def load_source_map():
    """从 PAL3A PDB 构建 class -> source file 映射。

    PAL3A 与 PAL3 共享大量类和源文件结构，PDB 中的 source_file 字段
    提供了原始开发时的目录布局，用于指导 PAL3 反编译代码的文件放置。
    """
    global _source_map_cache
    if _source_map_cache is not None:
        return _source_map_cache

    _source_map_cache = {}
    if not PDB_EXPORT_PATH.exists():
        return _source_map_cache

    with open(PDB_EXPORT_PATH) as f:
        pdb = json.load(f)

    # class -> set of .cpp source files
    class_to_files = {}
    for func in pdb.get("functions", []):
        cls = func.get("class", "")
        sf = func.get("source_file", "")
        if not cls or not sf:
            continue
        # Only game source (D:\PAL3A\PAL3\...)
        if sf.startswith("D:\\PAL3A\\PAL3\\"):
            rel = sf[len("D:\\PAL3A\\PAL3\\"):]
        elif sf.startswith("D:\\pal3a\\pal3\\") or sf.startswith("d:\\PAL3A\\PAL3\\"):
            rel = sf[14:]
        else:
            continue
        # Skip deeply nested relative paths
        if "..\\..\\.." in rel:
            continue
        # Only .cpp files
        if not (rel.lower().endswith(".cpp")):
            continue
        # Normalize separators
        rel = rel.replace("\\", "/")
        if cls not in class_to_files:
            class_to_files[cls] = set()
        class_to_files[cls].add(rel)

    # For each class, pick the primary .cpp file (most functions, or shortest path)
    for cls, files in class_to_files.items():
        # Prefer file matching class name
        best = None
        for f in files:
            basename = f.rsplit("/", 1)[-1].lower().replace(".cpp", "")
            if basename == cls.lower() or cls.lower() in basename:
                best = f
                break
        if not best:
            best = min(files, key=len)
        _source_map_cache[cls] = best

    return _source_map_cache


def infer_source_path(func_name):
    """根据 PAL3A PDB 映射推断函数应放置的源文件路径。

    Returns: 相对于 src/pal3/ 的路径 (如 "gamebase/PAL3.cpp") 或 None。
    """
    source_map = load_source_map()

    # Extract class name from demangled function name
    cls_match = re.match(r"(\w+)::", func_name)
    if cls_match:
        cls = cls_match.group(1)
        if cls in source_map:
            return source_map[cls]

    return None


def load_callgraph():
    """Load existing call graph."""
    if not CALLGRAPH_PATH.exists():
        return None
    with open(CALLGRAPH_PATH) as f:
        return json.load(f)


def save_callgraph(cg):
    """Save call graph to disk."""
    CALLGRAPH_PATH.parent.mkdir(parents=True, exist_ok=True)
    with open(CALLGRAPH_PATH, "w") as f:
        json.dump(cg, f, indent=2)


def get_decomp_file(addr, names_map):
    """Find the decomp JSON file for a given address."""
    # Search decomp directory for matching address
    addr_hex = f"{addr:08x}"
    for f in DECOMP_DIR.iterdir():
        if f.suffix == ".json" and addr_hex in f.name:
            return f
    return None


def extract_callees_from_decomp(decomp_path):
    """Extract called function addresses from decompiled C code."""
    with open(decomp_path) as f:
        data = json.load(f)

    code = data.get("decompiled_c", "")
    callees = set()

    # Match sub_XXXXXX patterns (unnamed functions)
    for m in re.finditer(r"\bsub_([0-9A-Fa-f]{5,8})\b", code):
        addr = int(m.group(1), 16)
        if TEXT_START <= addr <= TEXT_END:
            callees.add(addr)

    return callees


def is_external(name, addr):
    """Check if a function is external (should not be in call graph)."""
    if not (TEXT_START <= addr <= TEXT_END):
        return True

    for prefix in EXTERNAL_PREFIXES:
        if prefix in name:
            return True

    for pat in EXTERNAL_PATTERNS:
        if re.match(pat, name):
            return True

    return False


def get_function_name(addr, names_map):
    """Get best available name for a function address."""
    if addr in names_map:
        info = names_map[addr]
        if info.get("demangled"):
            return info["demangled"]
        if info.get("named") and info.get("mangled"):
            return info["mangled"]
    return f"sub_{addr:X}"


def compute_stats(cg):
    """Compute statistics from call graph."""
    nodes = cg["nodes"]
    stats = {
        "total_nodes": len(nodes),
        "matched": 0,
        "compiled": 0,
        "wip": 0,
        "pending": 0,
        "stub": 0,
        "skipped": 0,
        "blocked": 0,
        "frontier_size": len(cg.get("frontier", [])),
        "max_depth": 0,
    }
    for node in nodes.values():
        status = node.get("status", "pending")
        if status in stats:
            stats[status] += 1
        depth = node.get("depth", 0)
        if depth > stats["max_depth"]:
            stats["max_depth"] = depth
    return stats


def cmd_init(args):
    """Initialize call graph from WinMain."""
    names_map = load_names()

    # Root: WinMain
    root_addr = 0x00541900
    root_info = names_map.get(root_addr, {})

    # Find WinMain's decomp file
    root_decomp = get_decomp_file(root_addr, names_map)
    has_decomp = root_decomp is not None

    # Create root node
    root_node = {
        "name": "WinMain",
        "address": f"0x{root_addr:08X}",
        "size": root_info.get("size", 824),
        "status": "pending",
        "source": "src/pal3/WinMain.cpp",
        "match_rate": None,
        "calls": [],
        "called_by": [],
        "depth": 0,
        "has_decomp": has_decomp,
        "is_named": True,
    }

    # Extract callees from WinMain decomp
    callees = set()
    if root_decomp:
        callees = extract_callees_from_decomp(root_decomp)

    # Also extract from the source file if it exists (more reliable)
    winmain_src = SRC_DIR / "WinMain.cpp"
    if winmain_src.exists():
        with open(winmain_src) as f:
            src_code = f.read()
        # Extract sub_XXXXXX from source
        for m in re.finditer(r"\bsub_([0-9A-Fa-f]{5,8})\b", src_code):
            addr = int(m.group(1), 16)
            if TEXT_START <= addr <= TEXT_END:
                callees.add(addr)
        # Extract known named function addresses from comments
        for m in re.finditer(r"//.*?0x([0-9A-Fa-f]{8})", src_code):
            addr = int(m.group(1), 16)
            if TEXT_START <= addr <= TEXT_END and addr != root_addr:
                callees.add(addr)

    # Filter out externals and build frontier
    frontier = []
    nodes = {}

    for callee_addr in sorted(callees):
        name = get_function_name(callee_addr, names_map)
        if is_external(name, callee_addr):
            continue

        callee_info = names_map.get(callee_addr, {})
        callee_decomp = get_decomp_file(callee_addr, names_map)
        addr_str = f"0x{callee_addr:08X}"

        suggested = infer_source_path(name)
        node = {
            "name": name,
            "address": addr_str,
            "size": callee_info.get("size", 0),
            "status": "pending",
            "source": None,
            "suggested_source": suggested,
            "match_rate": None,
            "calls": [],
            "called_by": [f"0x{root_addr:08X}"],
            "depth": 1,
            "has_decomp": callee_decomp is not None,
            "is_named": callee_info.get("named", False),
        }
        nodes[addr_str] = node
        frontier.append(addr_str)
        root_node["calls"].append(addr_str)

    # Add root
    nodes[f"0x{root_addr:08X}"] = root_node

    # Mark WinMain as already having source
    root_node["status"] = "compiled"

    # Build call graph
    cg = {
        "version": 1,
        "root": f"0x{root_addr:08X}",
        "nodes": nodes,
        "frontier": frontier,
        "stats": compute_stats({"nodes": nodes, "frontier": frontier}),
    }

    # Update stats
    cg["stats"] = compute_stats(cg)

    save_callgraph(cg)
    print(f"Initialized call graph:")
    print(f"  Root: WinMain (0x{root_addr:08X})")
    print(f"  Nodes: {len(nodes)}")
    print(f"  Frontier: {len(frontier)} functions")
    for addr_str in frontier[:10]:
        node = nodes[addr_str]
        print(f"    {addr_str} {node['name']} ({node['size']} bytes) decomp={node['has_decomp']}")
    if len(frontier) > 10:
        print(f"    ... and {len(frontier) - 10} more")


def cmd_status(args):
    """Show call graph progress."""
    cg = load_callgraph()
    if cg is None:
        print("No call graph found. Run 'init' first.")
        sys.exit(1)

    stats = compute_stats(cg)
    cg["stats"] = stats
    save_callgraph(cg)

    print("=== PAL3.exe Call Graph Status ===")
    print(f"  Total nodes:    {stats['total_nodes']}")
    print(f"  Matched:        {stats['matched']}")
    print(f"  Compiled:       {stats['compiled']}")
    print(f"  WIP:            {stats['wip']}")
    print(f"  Pending:        {stats['pending']}")
    print(f"  Skipped:        {stats['skipped']}")
    print(f"  Blocked:        {stats['blocked']}")
    print(f"  Frontier size:  {stats['frontier_size']}")
    print(f"  Max BFS depth:  {stats['max_depth']}")

    # Completion rate
    done = stats["matched"] + stats["compiled"]
    total = stats["total_nodes"]
    if total > 0:
        print(f"  Completion:     {done}/{total} ({100*done/total:.1f}%)")


def cmd_frontier(args):
    """List current frontier sorted by priority."""
    cg = load_callgraph()
    if cg is None:
        print("No call graph found. Run 'init' first.")
        sys.exit(1)

    frontier = cg.get("frontier", [])
    nodes = cg["nodes"]

    # Sort by priority: depth ASC, has_decomp DESC, size ASC
    def priority_key(addr_str):
        node = nodes.get(addr_str, {})
        return (
            node.get("depth", 999),
            0 if node.get("has_decomp") else 1,
            0 if node.get("is_named") else 1,
            node.get("size", 99999),
        )

    sorted_frontier = sorted(frontier, key=priority_key)

    limit = args.limit if hasattr(args, "limit") and args.limit else 20
    print(f"=== Frontier ({len(sorted_frontier)} functions) ===")
    print(f"{'Addr':<14} {'Name':<40} {'Size':>6} {'Depth':>5} {'Decomp':>6}")
    print("-" * 75)
    for addr_str in sorted_frontier[:limit]:
        node = nodes.get(addr_str, {})
        print(
            f"{addr_str:<14} {node.get('name', '?'):<40} "
            f"{node.get('size', 0):>6} "
            f"{node.get('depth', '?'):>5} "
            f"{'yes' if node.get('has_decomp') else 'no':>6}"
        )
    if len(sorted_frontier) > limit:
        print(f"... and {len(sorted_frontier) - limit} more")


def cmd_next(args):
    """Select highest-priority frontier function (JSON output)."""
    cg = load_callgraph()
    if cg is None:
        print(json.dumps({"error": "No call graph found"}))
        sys.exit(1)

    frontier = cg.get("frontier", [])
    nodes = cg["nodes"]

    if not frontier:
        print(json.dumps({"error": "Frontier is empty"}))
        sys.exit(0)

    # Sort by priority
    def priority_key(addr_str):
        node = nodes.get(addr_str, {})
        return (
            node.get("depth", 999),
            0 if node.get("has_decomp") else 1,
            0 if node.get("is_named") else 1,
            node.get("size", 99999),
        )

    sorted_frontier = sorted(frontier, key=priority_key)
    best = sorted_frontier[0]
    node = nodes[best]

    # Find decomp file path
    decomp_file = None
    addr_int = int(best, 16)
    addr_hex = f"{addr_int:08x}"
    for f in DECOMP_DIR.iterdir():
        if f.suffix == ".json" and addr_hex in f.name:
            decomp_file = str(f.relative_to(PROJECT_ROOT))
            break

    # Infer suggested source path from PDB if not already set
    suggested = node.get("suggested_source") or infer_source_path(node["name"])

    result = {
        "address": best,
        "name": node["name"],
        "size": node["size"],
        "depth": node["depth"],
        "has_decomp": node["has_decomp"],
        "is_named": node["is_named"],
        "decomp_file": decomp_file,
        "source": node.get("source"),
        "suggested_source": suggested,
        "frontier_remaining": len(frontier),
    }
    print(json.dumps(result, indent=2))


def cmd_expand(args):
    """Mark function as done and expand its callees into the graph."""
    cg = load_callgraph()
    if cg is None:
        print("No call graph found. Run 'init' first.")
        sys.exit(1)

    addr_str = normalize_addr(args.addr)
    nodes = cg["nodes"]

    if addr_str not in nodes:
        print(f"Error: {addr_str} not in call graph")
        sys.exit(1)

    node = nodes[addr_str]
    names_map = load_names()

    # Find decomp file for this function
    addr_int = int(addr_str, 16)
    decomp_path = get_decomp_file(addr_int, names_map)

    new_callees = []
    if decomp_path:
        raw_callees = extract_callees_from_decomp(decomp_path)

        for callee_addr in sorted(raw_callees):
            callee_addr_str = f"0x{callee_addr:08X}"

            # Skip if already in graph
            if callee_addr_str in nodes:
                # Just update called_by
                if addr_str not in nodes[callee_addr_str].get("called_by", []):
                    nodes[callee_addr_str]["called_by"].append(addr_str)
                # Add to calls list if not there
                if callee_addr_str not in node.get("calls", []):
                    node["calls"].append(callee_addr_str)
                continue

            name = get_function_name(callee_addr, names_map)
            if is_external(name, callee_addr):
                continue

            callee_info = names_map.get(callee_addr, {})
            callee_decomp = get_decomp_file(callee_addr, names_map)

            suggested = infer_source_path(name)
            new_node = {
                "name": name,
                "address": callee_addr_str,
                "size": callee_info.get("size", 0),
                "status": "pending",
                "source": None,
                "suggested_source": suggested,
                "match_rate": None,
                "calls": [],
                "called_by": [addr_str],
                "depth": node["depth"] + 1,
                "has_decomp": callee_decomp is not None,
                "is_named": callee_info.get("named", False),
            }
            nodes[callee_addr_str] = new_node
            new_callees.append(callee_addr_str)

            # Add to parent's calls
            if callee_addr_str not in node.get("calls", []):
                node["calls"].append(callee_addr_str)

            # Add to frontier
            if callee_addr_str not in cg["frontier"]:
                cg["frontier"].append(callee_addr_str)

    # Remove this node from frontier
    if addr_str in cg["frontier"]:
        cg["frontier"].remove(addr_str)

    # Update stats
    cg["stats"] = compute_stats(cg)
    save_callgraph(cg)

    print(f"Expanded {addr_str} ({node['name']}):")
    print(f"  New callees added: {len(new_callees)}")
    print(f"  Frontier: {len(cg['frontier'])} functions")
    for c in new_callees[:10]:
        n = nodes[c]
        print(f"    {c} {n['name']} ({n['size']} bytes)")
    if len(new_callees) > 10:
        print(f"    ... and {len(new_callees) - 10} more")


def cmd_update(args):
    """Update a node's status/metadata."""
    cg = load_callgraph()
    if cg is None:
        print("No call graph found. Run 'init' first.")
        sys.exit(1)

    addr_str = normalize_addr(args.addr)
    nodes = cg["nodes"]

    if addr_str not in nodes:
        print(f"Error: {addr_str} not in call graph")
        sys.exit(1)

    node = nodes[addr_str]

    if args.status:
        node["status"] = args.status
    if args.match_rate is not None:
        node["match_rate"] = args.match_rate
    if args.source:
        node["source"] = args.source
    if args.name:
        node["name"] = args.name

    cg["stats"] = compute_stats(cg)
    save_callgraph(cg)
    print(f"Updated {addr_str} ({node['name']}): status={node['status']}, match_rate={node['match_rate']}")


def cmd_add(args):
    """Add a new node (stub) to the call graph."""
    cg = load_callgraph()
    if cg is None:
        print("No call graph found. Run 'init' first.")
        sys.exit(1)

    addr_str = normalize_addr(args.addr)
    nodes = cg["nodes"]

    if addr_str in nodes:
        # Node already exists, just update if needed
        node = nodes[addr_str]
        if args.status:
            node["status"] = args.status
        if args.source:
            node["source"] = args.source
        if args.name:
            node["name"] = args.name
        if args.signature:
            node["signature"] = args.signature
        print(f"Updated existing node {addr_str} ({node['name']})")
    else:
        # Create new node
        node = {
            "name": args.name or f"sub_{int(addr_str, 16):X}",
            "address": addr_str,
            "size": args.size or 0,
            "status": args.status or "stub",
            "source": args.source,
            "signature": args.signature or "",
            "match_rate": 0.0,
            "calls": [],
            "called_by": [],
            "depth": 99,  # Will be recalculated
            "has_decomp": False,
            "is_named": bool(args.name and not args.name.startswith("sub_")),
        }
        # Check if decomp file exists
        decomp_dir = Path(__file__).parent.parent / "asm" / "pal3" / "decomp"
        for f in decomp_dir.glob(f"*_{int(addr_str, 16):08x}.json"):
            node["has_decomp"] = True
            break
        nodes[addr_str] = node
        # Add to frontier
        if addr_str not in cg["frontier"]:
            cg["frontier"].append(addr_str)
        print(f"Added node {addr_str} ({node['name']}): status={node['status']}, source={node['source']}")

    cg["stats"] = compute_stats(cg)
    save_callgraph(cg)


def cmd_show(args):
    """Show details of a specific node."""
    cg = load_callgraph()
    if cg is None:
        print("No call graph found. Run 'init' first.")
        sys.exit(1)

    addr_str = normalize_addr(args.addr)
    nodes = cg["nodes"]

    if addr_str not in nodes:
        print(f"Error: {addr_str} not in call graph")
        sys.exit(1)

    node = nodes[addr_str]
    print(f"=== {node['name']} ===")
    print(f"  Address:     {node['address']}")
    print(f"  Size:        {node['size']} bytes")
    print(f"  Status:      {node['status']}")
    print(f"  Match rate:  {node['match_rate']}")
    print(f"  Source:      {node.get('source', 'None')}")
    suggested = node.get("suggested_source") or infer_source_path(node["name"])
    if suggested:
        print(f"  Suggested:   src/pal3/{suggested}  (from PAL3A PDB)")
    print(f"  Depth:       {node['depth']}")
    print(f"  Has decomp:  {node['has_decomp']}")
    print(f"  Is named:    {node['is_named']}")
    print(f"  Calls ({len(node.get('calls', []))}):")
    for c in node.get("calls", [])[:15]:
        cn = nodes.get(c, {})
        print(f"    {c} {cn.get('name', '?')} [{cn.get('status', '?')}]")
    if len(node.get("calls", [])) > 15:
        print(f"    ... and {len(node['calls']) - 15} more")
    print(f"  Called by ({len(node.get('called_by', []))}):")
    for c in node.get("called_by", []):
        cn = nodes.get(c, {})
        print(f"    {c} {cn.get('name', '?')}")


def cmd_validate(args):
    """Validate call graph data consistency."""
    cg = load_callgraph()
    if cg is None:
        print("No call graph found. Run 'init' first.")
        sys.exit(1)

    nodes = cg["nodes"]
    errors = []
    warnings = []

    for addr_str, node in nodes.items():
        # Check address format
        try:
            addr_int = int(addr_str, 16)
        except ValueError:
            errors.append(f"{addr_str}: invalid address format")
            continue

        # Check address in .text range
        if not (TEXT_START <= addr_int <= TEXT_END):
            warnings.append(f"{addr_str} ({node['name']}): address outside .text range")

        # Check source file exists if specified
        if node.get("source"):
            src_path = PROJECT_ROOT / node["source"]
            if not src_path.exists():
                errors.append(f"{addr_str} ({node['name']}): source file not found: {node['source']}")

        # Check calls reference valid nodes
        for callee in node.get("calls", []):
            if callee not in nodes:
                warnings.append(f"{addr_str} ({node['name']}): calls non-existent node {callee}")

        # Check called_by reference valid nodes
        for caller in node.get("called_by", []):
            if caller not in nodes:
                warnings.append(f"{addr_str} ({node['name']}): called_by non-existent node {caller}")

        # Check status is valid
        valid_statuses = {"pending", "matched", "compiled", "wip", "skipped", "blocked"}
        if node.get("status") not in valid_statuses:
            errors.append(f"{addr_str} ({node['name']}): invalid status '{node.get('status')}'")

    # Check frontier nodes exist
    for addr_str in cg.get("frontier", []):
        if addr_str not in nodes:
            errors.append(f"Frontier references non-existent node: {addr_str}")

    # Report
    if errors:
        print(f"ERRORS ({len(errors)}):")
        for e in errors:
            print(f"  - {e}")
    if warnings:
        print(f"WARNINGS ({len(warnings)}):")
        for w in warnings[:20]:
            print(f"  - {w}")
        if len(warnings) > 20:
            print(f"  ... and {len(warnings) - 20} more")

    if not errors and not warnings:
        print("Validation PASSED - no issues found")
    elif not errors:
        print(f"\nValidation PASSED with {len(warnings)} warnings")
    else:
        print(f"\nValidation FAILED: {len(errors)} errors, {len(warnings)} warnings")
        sys.exit(1)


def normalize_addr(addr_str):
    """Normalize address string to 0xXXXXXXXX format."""
    if addr_str.startswith("0x") or addr_str.startswith("0X"):
        addr_int = int(addr_str, 16)
    else:
        addr_int = int(addr_str, 16)
    return f"0x{addr_int:08X}"


def main():
    parser = argparse.ArgumentParser(description="PAL3.exe 调用图管理工具")
    subparsers = parser.add_subparsers(dest="command", help="子命令")

    # init
    subparsers.add_parser("init", help="初始化调用图")

    # status
    subparsers.add_parser("status", help="显示进度统计")

    # frontier
    p_frontier = subparsers.add_parser("frontier", help="列出当前 frontier")
    p_frontier.add_argument("--limit", type=int, default=20, help="最多显示几个")

    # next
    subparsers.add_parser("next", help="选取下一个目标 (JSON)")

    # expand
    p_expand = subparsers.add_parser("expand", help="展开节点的 callees")
    p_expand.add_argument("addr", help="函数地址 (如 0x00404800)")

    # update
    p_update = subparsers.add_parser("update", help="更新节点状态")
    p_update.add_argument("addr", help="函数地址")
    p_update.add_argument("--status", choices=["pending", "stub", "matched", "compiled", "wip", "skipped", "blocked"])
    p_update.add_argument("--match-rate", type=float, dest="match_rate")
    p_update.add_argument("--source", help="源文件路径")
    p_update.add_argument("--name", help="函数名")

    # add
    p_add = subparsers.add_parser("add", help="添加 stub 节点")
    p_add.add_argument("addr", help="函数地址 (如 0x00404800)")
    p_add.add_argument("--name", help="函数名")
    p_add.add_argument("--size", type=int, help="函数大小 (字节)")
    p_add.add_argument("--status", default="stub", choices=["pending", "stub", "skipped"])
    p_add.add_argument("--source", help="源文件路径 (如 src/pal3/gamebase/PAL3.cpp)")
    p_add.add_argument("--signature", help="函数签名 (如 'void __cdecl PAL3::CreateGfxWindow(void)')")

    # show
    p_show = subparsers.add_parser("show", help="显示节点详情")
    p_show.add_argument("addr", help="函数地址")

    # validate
    subparsers.add_parser("validate", help="验证数据一致性")

    args = parser.parse_args()

    if args.command == "init":
        cmd_init(args)
    elif args.command == "status":
        cmd_status(args)
    elif args.command == "frontier":
        cmd_frontier(args)
    elif args.command == "next":
        cmd_next(args)
    elif args.command == "expand":
        cmd_expand(args)
    elif args.command == "update":
        cmd_update(args)
    elif args.command == "add":
        cmd_add(args)
    elif args.command == "show":
        cmd_show(args)
    elif args.command == "validate":
        cmd_validate(args)
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
