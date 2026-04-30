#!/usr/bin/env python3
"""
Quick helper to decompile a single function interactively.

Cross-platform replacement for decompile_func.sh.

Usage:
    python tools/decompile_func.py asm/FUN_00401000_00401000.json
    python tools/decompile_func.py asm/FUN_00401000_00401000.json --dry-run
"""

import json
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
TOOLS_DIR = PROJECT_ROOT / "tools"
ASM_DIR = PROJECT_ROOT / "asm"


def show_function_info(json_path):
    """Display function summary before processing."""
    with open(json_path, 'r', encoding='utf-8') as f:
        data = json.load(f)

    print("=" * 50)
    print("  PAL3 Function Decompilation")
    print("=" * 50)
    print()
    print("  Function: {} ({})".format(data.get('name', '?'), data.get('address', '?')))
    print("  Size:     {} bytes".format(data.get('size_bytes', '?')))
    print("  Callees:  {}".format(len(data.get('callees', []))))
    print("  Callers:  {}".format(len(data.get('callers', []))))
    print("  Globals:  {}".format(len(data.get('global_refs', []))))
    print()

    dc = data.get('decompiled_c', '')
    if dc:
        lines = dc.split('\n')
        print("  Ghidra output ({} lines):".format(len(lines)))
        for line in lines[:15]:
            print("    " + line)
        if len(lines) > 15:
            print("    ... ({} more lines)".format(len(lines) - 15))
        print()


def main():
    if len(sys.argv) < 2:
        print("用法: python tools/decompile_func.py <function_json_file> [--dry-run]")
        print()

        # List available functions
        json_files = sorted(ASM_DIR.glob("*.json"))
        json_files = [f for f in json_files if not f.name.startswith('_')]
        if json_files:
            print("可用函数:")
            for f in json_files[:20]:
                print("  {}".format(f))
            if len(json_files) > 20:
                print("  ... ({} more)".format(len(json_files) - 20))
        else:
            print("（尚无导出函数，请先运行 Ghidra 导出）")
        sys.exit(1)

    json_file = sys.argv[1]
    extra_args = sys.argv[2:]

    json_path = Path(json_file)
    if not json_path.exists():
        print("错误: 文件不存在: {}".format(json_file))
        sys.exit(1)

    # Show info
    show_function_info(json_path)

    # Run ai_decompile
    print("Processing with AI pipeline...")
    print()

    cmd = [
        sys.executable,
        str(TOOLS_DIR / "ai_decompile.py"),
        "process",
        "--function", str(json_path),
    ] + extra_args

    result = subprocess.run(cmd, cwd=str(PROJECT_ROOT))
    sys.exit(result.returncode)


if __name__ == "__main__":
    main()
