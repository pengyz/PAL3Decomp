#!/usr/bin/env python3
"""
PAL3.exe Decompilation Progress Tracker

Analyzes the decompilation progress by:
- Scanning source files for implemented functions
- Comparing against known function list from Ghidra exports
- Reporting overall and per-module progress
- Identifying stubs, TODOs, and incomplete implementations

Usage:
    python progress_pal3.py
    python progress_pal3.py --detail
    python progress_pal3.py --by-module
"""

import json
import re
import argparse
from pathlib import Path
from collections import defaultdict
from typing import Dict, List, Set, Tuple


class FunctionInfo:
    """Information about a single function."""

    def __init__(self, address: str, name: str = "", size: int = 0, module: str = ""):
        self.address = address.upper()  # Normalize to uppercase
        self.name = name
        self.size = size
        self.module = module  # Source module (e.g., "main", "combat", "ui")
        self.file = ""  # Source file path
        self.line = 0  # Line number in source file
        self.is_stub = False  # Is this a stub implementation?
        self.has_todo = False  # Does this have TODO markers?
        self.implemented = False  # Is this implemented?


class ProgressTracker:
    """Track decompilation progress for PAL3.exe."""

    def __init__(self, project_root: Path):
        self.project_root = project_root
        self.src_dir = project_root / "src" / "pal3"
        self.asm_dir = project_root / "asm" / "pal3"

        self.functions: Dict[str, FunctionInfo] = {}
        self.implemented_funcs: Dict[str, FunctionInfo] = {}
        self.exported_funcs: List[FunctionInfo] = []

    def scan_source_files(self):
        """Scan C/C++ source files for implemented functions."""
        print("Scanning source files...")

        # Pattern to match function address comments
        # Examples: // 0x00401000  or  /* address: 0x00401000 */
        address_pattern = re.compile(r'//\s*0x([0-9A-Fa-f]+)|/\*.*address:\s*0x([0-9A-Fa-f]+)', re.IGNORECASE)

        # Pattern to detect stubs
        stub_pattern = re.compile(r'\b(STUB|stub)\b', re.IGNORECASE)
        todo_pattern = re.compile(r'\b(TODO|FIXME|XXX|INCOMPLETE|UNCERTAIN)\b', re.IGNORECASE)

        if not self.src_dir.exists():
            print(f"Warning: Source directory not found: {self.src_dir}")
            return

        # Scan all .cpp and .c files
        for src_file in self.src_dir.rglob("*.cpp"):
            self._scan_file(src_file, address_pattern, stub_pattern, todo_pattern)

        for src_file in self.src_dir.rglob("*.c"):
            self._scan_file(src_file, address_pattern, stub_pattern, todo_pattern)

        print(f"Found {len(self.implemented_funcs)} implemented functions")

    def _scan_file(self, src_file: Path, address_pattern, stub_pattern, todo_pattern):
        """Scan a single source file for functions."""
        try:
            with open(src_file, 'r', encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()

            current_func = None

            for i, line in enumerate(lines, 1):
                # Check for function address comment
                match = address_pattern.search(line)
                if match:
                    address_hex = match.group(1) or match.group(2)
                    address = f"0x{address_hex.upper()}"

                    # Try to extract function name from following line
                    func_name = self._extract_function_name(lines, i)

                    # Get module name from file path
                    module_name = src_file.stem

                    func_info = FunctionInfo(
                        address=address,
                        name=func_name,
                        module=module_name
                    )
                    func_info.file = str(src_file.relative_to(self.project_root))
                    func_info.line = i
                    func_info.implemented = True

                    current_func = func_info
                    self.implemented_funcs[address] = func_info

                # Check if current function is stub or has TODO
                if current_func:
                    if stub_pattern.search(line):
                        current_func.is_stub = True
                    if todo_pattern.search(line):
                        current_func.has_todo = True

                    # Assume function ends at next function or large gap
                    if i > current_func.line + 50:  # Arbitrary threshold
                        current_func = None

        except Exception as e:
            print(f"Warning: Failed to scan {src_file}: {e}")

    def _extract_function_name(self, lines: List[str], start_line: int) -> str:
        """Try to extract function name from lines following address comment."""
        # Look at the next few lines for function signature
        for i in range(start_line, min(start_line + 5, len(lines))):
            line = lines[i].strip()

            # Match function signature patterns
            # Examples: int WinMain(...)  or  static void UpdateFrame(...)
            match = re.match(r'(?:static\s+)?(?:inline\s+)?(?:\w+\s+)+(\w+)\s*\(', line)
            if match:
                return match.group(1)

        return "unknown"

    def load_exported_functions(self):
        """Load exported function list from Ghidra JSON files."""
        print("Loading exported functions from Ghidra...")

        if not self.asm_dir.exists():
            print(f"Warning: Assembly directory not found: {self.asm_dir}")
            print("Ghidra export not performed yet - skipping")
            return

        json_files = list(self.asm_dir.glob("*.json"))
        if not json_files:
            print("No function exports found - Ghidra analysis not performed yet")
            return

        for json_file in json_files:
            try:
                with open(json_file, 'r', encoding='utf-8') as f:
                    data = json.load(f)

                func_info = FunctionInfo(
                    address=data.get('address', '').upper(),
                    name=data.get('name', ''),
                    size=data.get('size_bytes', 0)
                )

                self.exported_funcs.append(func_info)

            except Exception as e:
                print(f"Warning: Failed to parse {json_file}: {e}")

        print(f"Found {len(self.exported_funcs)} exported functions")

    def generate_report(self, detail: bool = False, by_module: bool = False):
        """Generate progress report."""
        print("\n" + "=" * 70)
        print("PAL3.exe Decompilation Progress Report")
        print("=" * 70)

        # Overall statistics
        total_export = len(self.exported_funcs)
        total_impl = len(self.implemented_funcs)

        # Count complete vs stub implementations
        complete_funcs = [f for f in self.implemented_funcs.values() if not f.is_stub]
        stub_funcs = [f for f in self.implemented_funcs.values() if f.is_stub]
        todo_funcs = [f for f in self.implemented_funcs.values() if f.has_todo]

        print(f"\n[STATS] Overall Progress:")
        print(f"  Implemented:  {total_impl:4d} functions")

        if total_export > 0:
            print(f"  Total target: {total_export:4d} functions")
            progress_pct = (total_impl * 100) // total_export
            print(f"  Progress:     {total_impl}/{total_export} ({progress_pct}%)")
            print(f"  Remaining:    {total_export - total_impl:4d} functions")
        else:
            print(f"  Total target: Unknown (Ghidra export not performed)")
            print(f"  Progress:     {total_impl} functions (no baseline)")

        print(f"\n[QUALITY] Implementation Quality:")
        print(f"  Complete:     {len(complete_funcs):4d} functions")
        print(f"  Stubs:        {len(stub_funcs):4d} functions")
        print(f"  With TODOs:   {len(todo_funcs):4d} functions")

        # By-module breakdown
        if by_module or detail:
            print(f"\n[MODULES] By Module:")
            module_stats = defaultdict(list)

            for func in self.implemented_funcs.values():
                module_stats[func.module].append(func)

            for module_name in sorted(module_stats.keys()):
                funcs = module_stats[module_name]
                complete = sum(1 for f in funcs if not f.is_stub)
                stubs = sum(1 for f in funcs if f.is_stub)
                todos = sum(1 for f in funcs if f.has_todo)

                print(f"  {module_name:<20} {len(funcs):4d} total "
                      f"({complete:3d} complete, {stubs:3d} stubs, {todos:3d} TODOs)")

        # Detailed listing
        if detail:
            print(f"\n[DETAIL] Implemented Functions:")

            # Group by module
            for module_name in sorted(module_stats.keys()):
                funcs = sorted(module_stats[module_name], key=lambda f: f.address)

                print(f"\n  {module_name}:")
                for func in funcs[:10]:  # Show first 10 per module
                    status = []
                    if func.is_stub:
                        status.append("STUB")
                    if func.has_todo:
                        status.append("TODO")
                    status_str = f" [{', '.join(status)}]" if status else ""

                    print(f"    {func.address}  {func.name:<30} "
                          f"({func.file}:{func.line}){status_str}")

                if len(funcs) > 10:
                    print(f"    ... and {len(funcs) - 10} more")

        # Next steps
        print(f"\n[TODO] Next Steps:")
        if total_export == 0:
            print(f"  1. Run Ghidra analysis to export function list")
            print(f"     python tools/ghidra_export.py --target PAL3.exe")
        elif total_impl == 0:
            print(f"  1. Start implementing functions in src/pal3/")
            print(f"  2. Add address comments like // 0x00401000")
        else:
            print(f"  1. Implement remaining {total_export - total_impl if total_export > 0 else '?'} functions")
            if len(stub_funcs) > 0:
                print(f"  2. Complete {len(stub_funcs)} stub implementations")
            if len(todo_funcs) > 0:
                print(f"  3. Resolve {len(todo_funcs)} TODOs")
            print(f"  4. Verify byte-matching with original binary")
            print(f"     python tools/compare_exe.py --address <addr> --size <size>")

        print("\n" + "=" * 70)


def main():
    parser = argparse.ArgumentParser(
        description='Track PAL3.exe decompilation progress'
    )
    parser.add_argument('--detail', action='store_true',
                        help='Show detailed function list')
    parser.add_argument('--by-module', action='store_true',
                        help='Show breakdown by module')

    args = parser.parse_args()

    # Get project root
    project_root = Path(__file__).parent.parent

    # Create tracker and run analysis
    tracker = ProgressTracker(project_root)
    tracker.load_exported_functions()
    tracker.scan_source_files()
    tracker.generate_report(detail=args.detail, by_module=args.by_module)


if __name__ == "__main__":
    main()
