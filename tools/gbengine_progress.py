#!/usr/bin/env python3
"""
gbengine.dll - Function-level Progress Tracker

Classifies every function in the source code into one of four categories:
  IMPLEMENTED - Has substantial logic (>3 non-trivial lines, no stub markers)
  TRIVIAL     - Simple getter/setter/constructor (<=3 lines, real but minimal)
  INCOMPLETE  - Has code but contains stub/placeholder/simplified markers
  STUB        - Empty body or just returns 0/NULL/this

Usage:
    python tools/gbengine_progress.py              # Summary
    python tools/gbengine_progress.py --detail     # Per-class breakdown
    python tools/gbengine_progress.py --incomplete # List all incomplete functions
    python tools/gbengine_progress.py --stubs      # List all stubs
    python tools/gbengine_progress.py --class NAME # Single class detail
    python tools/gbengine_progress.py --json       # Write build/gbengine_progress.json
"""

import re
import os
import sys
import json
import argparse
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
DEF_FILE = SRC_DIR / "gbengine.def"
MATCHED_FILE = PROJECT_ROOT / "build" / "matched_exports_v4.txt"
OUTPUT_JSON = PROJECT_ROOT / "build" / "gbengine_progress.json"

# Markers that indicate a function body is not fully implemented
INCOMPLETE_MARKERS = [
    r'//.*\b[Ss]tub\b',
    r'//.*\b[Pp]laceholder\b',
    r'//.*\b[Ss]implified\b',
    r'//.*\bnot (fully )?impl',
    r'//.*\b[Ff]ake\b',
    r'//.*\b[Dd]ummy\b',
    r'//.*\b[Mm]inimal\b',
    r'//.*\bTODO\b',
    r'//.*\bFIXME\b',
    r'//.*\bHACK\b',
    r'//.*\b[Ii]ncomplete\b',
    r'//.*\b[Ww]ould\s+(allocate|calculate|create|construct|init|set)',
]
MARKER_RE = re.compile('|'.join(INCOMPLETE_MARKERS))


def analyze_cpp_file(filepath):
    """Analyze a .cpp file, return list of (func_name, line, status, body_size)."""
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    results = []
    i = 0
    while i < len(lines):
        stripped = lines[i].strip()

        # Match: [ReturnType] ClassName::MethodName(...)
        if re.match(r'^[\w:*& ~]+::\w', stripped) and '(' in stripped:
            func_name = stripped.split('(')[0].strip()
            parts = func_name.split()
            for p in parts:
                if '::' in p:
                    func_name = p
                    break

            # Find opening brace
            brace_line = i
            found_brace = '{' in lines[i]
            if not found_brace:
                for j in range(i + 1, min(i + 5, len(lines))):
                    if '{' in lines[j]:
                        brace_line = j
                        found_brace = True
                        break

            if not found_brace:
                i += 1
                continue

            # Read body
            depth = 0
            body_lines = []
            end_line = brace_line
            for k in range(brace_line, min(brace_line + 500, len(lines))):
                depth += lines[k].count('{') - lines[k].count('}')
                body_lines.append(lines[k])
                if depth == 0:
                    end_line = k
                    break

            # Classify
            # Handle single-line functions: extract body between { and }
            if len(body_lines) == 1:
                line_content = body_lines[0]
                brace_start = line_content.index('{')
                brace_end = line_content.rindex('}')
                inner = line_content[brace_start+1:brace_end].strip()
                # Split by semicolons to get statements
                non_empty = [s.strip() for s in inner.split(';') if s.strip()]
            else:
                non_empty = [l.strip() for l in body_lines[1:-1]
                             if l.strip() and not l.strip().startswith('//')]
            has_marker = any(MARKER_RE.search(l) for l in body_lines)

            if len(non_empty) == 0:
                status = 'STUB'
            elif len(non_empty) <= 2 and all(
                re.match(r'return\s+(0|NULL|this|false|0\.0f|\*this|E_NOTIMPL);?$', l)
                for l in non_empty
            ):
                status = 'STUB'
            elif has_marker:
                status = 'INCOMPLETE'
            elif len(non_empty) <= 3:
                status = 'TRIVIAL'
            else:
                status = 'IMPLEMENTED'

            results.append((func_name, i + 1, status, len(body_lines)))
            i = end_line + 1
            continue

        i += 1
    return results


def load_matched_exports():
    """Load byte-verified export symbols."""
    matched = set()
    if MATCHED_FILE.exists():
        with open(MATCHED_FILE, 'r', encoding='utf-8', errors='ignore') as f:
            for line in f:
                if line.strip():
                    matched.add(line.strip())
    return matched


def count_def_exports():
    """Count exports in .def file."""
    count = 0
    if DEF_FILE.exists():
        with open(DEF_FILE, 'r', encoding='utf-8', errors='ignore') as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith(';') and \
                   not line.startswith('LIBRARY') and not line.startswith('EXPORTS'):
                    count += 1
    return count


def main():
    parser = argparse.ArgumentParser(description='gbengine.dll function progress')
    parser.add_argument('--detail', action='store_true')
    parser.add_argument('--incomplete', action='store_true')
    parser.add_argument('--stubs', action='store_true')
    parser.add_argument('--class', dest='classname')
    parser.add_argument('--json', action='store_true')
    args = parser.parse_args()

    # Analyze all files
    all_results = {}  # filename -> [(func, line, status, size)]
    for cpp_file in sorted(SRC_DIR.glob('*.cpp')):
        results = analyze_cpp_file(cpp_file)
        if results:
            all_results[cpp_file.name] = results

    matched = load_matched_exports()
    n_exports = count_def_exports()

    # Totals
    totals = defaultdict(int)
    by_class = defaultdict(list)
    for fname, file_results in all_results.items():
        for func_name, line, status, size in file_results:
            totals[status] += 1
            cls = func_name.split('::')[0] if '::' in func_name else '(free)'
            by_class[cls].append((func_name, line, status, fname))

    grand_total = sum(totals.values())
    n_impl = totals['IMPLEMENTED']
    n_triv = totals['TRIVIAL']
    n_incmp = totals['INCOMPLETE']
    n_stub = totals['STUB']

    if args.json:
        report = {
            'generated': '2026-05-01',
            'summary': {
                'total_exports': n_exports,
                'byte_verified': len(matched),
                'total_functions': grand_total,
                'implemented': n_impl,
                'trivial': n_triv,
                'incomplete': n_incmp,
                'stub': n_stub,
            },
            'files': {
                fname: [{'function': f, 'line': l, 'status': s, 'body_lines': sz}
                        for f, l, s, sz in results]
                for fname, results in all_results.items()
            }
        }
        OUTPUT_JSON.parent.mkdir(parents=True, exist_ok=True)
        with open(OUTPUT_JSON, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)
        print(f"Written: {OUTPUT_JSON}")
        return

    if args.incomplete:
        print("\n=== INCOMPLETE functions (simplified/stub markers) ===\n")
        for fname in sorted(all_results.keys()):
            incomplete = [(f, l) for f, l, s, _ in all_results[fname] if s == 'INCOMPLETE']
            if incomplete:
                print(f"  {fname}:")
                for func_name, line_num in incomplete:
                    print(f"    L{line_num}: {func_name}")
                print()
        print(f"  Total: {n_incmp} incomplete functions")
        return

    if args.stubs:
        print("\n=== STUB functions (empty/return 0) ===\n")
        for fname in sorted(all_results.keys()):
            stubs = [(f, l) for f, l, s, _ in all_results[fname] if s == 'STUB']
            if stubs:
                print(f"  {fname}: ({len(stubs)} stubs)")
                for func_name, line_num in stubs:
                    print(f"    L{line_num}: {func_name}")
                print()
        print(f"  Total: {n_stub} stub functions")
        return

    if args.classname:
        cls = args.classname
        if cls not in by_class:
            print(f"Class not found: {cls}")
            print(f"Available: {', '.join(sorted(by_class.keys())[:20])}")
            return
        funcs = by_class[cls]
        print(f"\n=== {cls} ({len(funcs)} functions) ===\n")
        for func_name, line, status, source in sorted(funcs, key=lambda x: x[2]):
            icon = {'IMPLEMENTED': '[OK]', 'TRIVIAL': '[..]',
                    'INCOMPLETE': '[??]', 'STUB': '[  ]'}[status]
            method = func_name.split('::')[-1]
            print(f"  {icon} {method:<30} {status:<12} {source}:L{line}")
        return

    # Default: summary
    print("=" * 60)
    print("  gbengine.dll Function Progress Report")
    print("=" * 60)
    print()
    print(f"  DLL exports (DEF file):        {n_exports}")
    print(f"  Byte-level verified:            {len(matched)}")
    print()
    print(f"  Total function definitions:     {grand_total}")
    print(f"    IMPLEMENTED (real logic):     {n_impl:4d}  ({100*n_impl/grand_total:.1f}%)")
    print(f"    TRIVIAL (getter/ctor/=):      {n_triv:4d}  ({100*n_triv/grand_total:.1f}%)")
    print(f"    INCOMPLETE (has markers):     {n_incmp:4d}  ({100*n_incmp/grand_total:.1f}%)")
    print(f"    STUB (empty/return 0):        {n_stub:4d}  ({100*n_stub/grand_total:.1f}%)")
    print()
    print(f"  Remaining work:")
    print(f"    Functions needing implementation: {n_stub + n_incmp} ({n_stub} stubs + {n_incmp} incomplete)")
    print()

    if args.detail:
        print("\n--- Per-class detail ---\n")
        print(f"  {'Class':<25} {'Total':>5} {'Impl':>5} {'Triv':>5} {'Incm':>5} {'Stub':>5} {'Done%':>6}")
        print("  " + "-" * 58)
        for cls in sorted(by_class.keys()):
            funcs = by_class[cls]
            n = len(funcs)
            ni = sum(1 for f in funcs if f[2] == 'IMPLEMENTED')
            nt = sum(1 for f in funcs if f[2] == 'TRIVIAL')
            nc = sum(1 for f in funcs if f[2] == 'INCOMPLETE')
            ns = sum(1 for f in funcs if f[2] == 'STUB')
            pct = 100 * (ni + nt) / n if n > 0 else 0
            print(f"  {cls:<25} {n:5d} {ni:5d} {nt:5d} {nc:5d} {ns:5d} {pct:5.1f}%")
    else:
        # Top classes needing work
        print("--- Classes with most remaining work ---\n")
        print(f"  {'Class':<25} {'NeedWork':>8} {'Done':>5} {'Total':>5}")
        print("  " + "-" * 48)
        rankings = []
        for cls, funcs in by_class.items():
            need = sum(1 for f in funcs if f[2] in ('STUB', 'INCOMPLETE'))
            done = sum(1 for f in funcs if f[2] in ('IMPLEMENTED', 'TRIVIAL'))
            if need > 0:
                rankings.append((cls, need, done, len(funcs)))
        for cls, need, done, total in sorted(rankings, key=lambda x: -x[1])[:20]:
            print(f"  {cls:<25} {need:8d} {done:5d} {total:5d}")


if __name__ == '__main__':
    main()
