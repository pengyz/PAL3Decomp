#!/usr/bin/env python3
"""
Function Prioritization Tool for PAL3 Decompilation.

Analyzes exported function data and produces an ordered work queue
optimized for highest match rate and incremental progress.

Priority logic:
  1. Leaf functions (no internal callees) — minimal dependencies
  2. Smaller functions first — higher match probability
  3. Functions with known API patterns — easier to recognize
  4. Functions with string references — more context clues
  5. Functions whose callees are already decompiled — dependency satisfaction

Usage:
    python prioritize.py                           # Default: top 50
    python prioritize.py --top 100                 # Top 100
    python prioritize.py --module core/render      # Filter by module
    python prioritize.py --max-size 200            # Only functions <= 200 bytes
    python prioritize.py --output queue.json       # Save work queue
"""

import argparse
import json
import sys
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm"
BUILD_DIR = PROJECT_ROOT / "build"
PROGRESS_DB = BUILD_DIR / "progress.json"


def load_functions():
    """Load function data from asm/ directory."""
    functions = []

    # Try _function_list.json first (from initial_analysis.py)
    func_list = ASM_DIR / "_function_list.json"
    if func_list.exists():
        with open(func_list) as f:
            return json.load(f)

    # Fallback: load individual JSON files
    for json_file in ASM_DIR.glob("*.json"):
        if json_file.name.startswith('_'):
            continue
        try:
            with open(json_file) as f:
                data = json.load(f)
                data['_source_file'] = str(json_file)
                functions.append(data)
        except (json.JSONDecodeError, IOError):
            continue

    return functions


def load_completed():
    """Load set of already-completed function addresses."""
    if not PROGRESS_DB.exists():
        return set()

    with open(PROGRESS_DB) as f:
        progress = json.load(f)

    completed = set()
    for addr, info in progress.get('functions', {}).items():
        if info.get('status') == 'matched':
            completed.add(addr)
    return completed


def score_function(func, completed_addrs):
    """
    Score a function for prioritization.

    Higher score = should be processed first.
    Returns (score, reasons) tuple.
    """
    score = 0
    reasons = []

    size = func.get('size_bytes', 9999)
    is_leaf = func.get('is_leaf', False)
    is_thunk = func.get('is_thunk', False)
    callees_internal = func.get('callees_internal_count', 0)
    callees_external = func.get('callees_external', [])
    caller_count = func.get('caller_count', 0)
    string_refs = func.get('string_refs', [])
    has_name = func.get('has_custom_name', False)

    # Skip thunks — they're trivial wrappers
    if is_thunk:
        return -1, ["thunk (skip)"]

    # Leaf functions get a big boost
    if is_leaf:
        score += 500
        reasons.append("leaf function (+500)")

    # Size-based scoring: smaller is better
    if size <= 20:
        score += 300
        reasons.append("tiny (<= 20 bytes, +300)")
    elif size <= 50:
        score += 250
        reasons.append("very small (<= 50 bytes, +250)")
    elif size <= 100:
        score += 200
        reasons.append("small (<= 100 bytes, +200)")
    elif size <= 200:
        score += 100
        reasons.append("medium (<= 200 bytes, +100)")
    elif size <= 500:
        score += 50
        reasons.append("moderate (<= 500 bytes, +50)")
    elif size <= 1000:
        score += 10
        reasons.append("large (<= 1000 bytes, +10)")
    else:
        score -= 100
        reasons.append("very large (> 1000 bytes, -100)")

    # Functions that call known APIs are easier to understand
    known_api_patterns = {
        'DirectX': ['d3d', 'direct3d', 'directinput', 'directsound'],
        'Win32': ['createfile', 'readfile', 'getprocaddress', 'loadlibrary'],
        'CRT': ['malloc', 'free', 'memcpy', 'sprintf', 'strlen', 'strcmp'],
        'Math': ['sin', 'cos', 'sqrt', 'atan2', 'pow'],
    }
    for category, patterns in known_api_patterns.items():
        for ext_call in callees_external:
            if any(p in ext_call.lower() for p in patterns):
                score += 30
                reasons.append("known API: {} (+30)".format(category))
                break

    # String references provide naming/context clues
    if string_refs:
        bonus = min(len(string_refs) * 20, 80)
        score += bonus
        reasons.append("{} string refs (+{})".format(len(string_refs), bonus))

    # Already-named functions are partially understood
    if has_name:
        score += 50
        reasons.append("has custom name (+50)")

    # Dependency satisfaction: if all internal callees are already done
    # For now use a simplified check
    if callees_internal == 0:
        score += 100
        reasons.append("no internal dependencies (+100)")

    # More callers = more important (but don't prioritize too early)
    if caller_count > 10:
        score += 30
        reasons.append("widely called ({} callers, +30)".format(caller_count))
    elif caller_count > 3:
        score += 15
        reasons.append("{} callers (+15)".format(caller_count))

    return score, reasons


def prioritize(functions, completed, max_size=None, module_filter=None):
    """Score and sort functions by priority."""
    scored = []

    for func in functions:
        addr = func.get('address', '')

        # Skip already completed
        if addr in completed:
            continue

        # Filter by module
        if module_filter:
            if module_filter not in func.get('module', ''):
                continue

        # Filter by size
        if max_size and func.get('size_bytes', 0) > max_size:
            continue

        score, reasons = score_function(func, completed)
        if score < 0:
            continue

        scored.append({
            'address': addr,
            'name': func.get('name', ''),
            'size_bytes': func.get('size_bytes', 0),
            'is_leaf': func.get('is_leaf', False),
            'module': func.get('module', 'unknown'),
            'score': score,
            'reasons': reasons,
            '_source_file': func.get('_source_file', ''),
        })

    # Sort by score (descending), then by size (ascending) as tiebreaker
    scored.sort(key=lambda x: (-x['score'], x['size_bytes']))

    return scored


def print_queue(queue, top_n=50):
    """Print the prioritized work queue."""
    print()
    print("=" * 75)
    print("  PAL3 Decompilation Work Queue")
    print("=" * 75)
    print()
    print("  {:>4s}  {:<12s} {:<25s} {:>6s} {:>6s} {:<20s}".format(
        "#", "Address", "Name", "Size", "Score", "Module"))
    print("  " + "-" * 70)

    for i, item in enumerate(queue[:top_n]):
        print("  {:>4d}  {:<12s} {:<25s} {:>5d}B {:>5d}  {:<20s}".format(
            i + 1,
            item['address'][:12],
            item['name'][:25],
            item['size_bytes'],
            item['score'],
            item['module'][:20],
        ))

    print()
    print("  Showing top {} of {} eligible functions".format(
        min(top_n, len(queue)), len(queue)))

    # Category summary
    leaf_count = sum(1 for f in queue if f['is_leaf'])
    modules = defaultdict(int)
    for f in queue:
        modules[f['module']] += 1

    print()
    print("  Queue breakdown:")
    print("    Leaf functions: {}".format(leaf_count))
    for mod, count in sorted(modules.items(), key=lambda x: -x[1]):
        print("    {:25s} {}".format(mod, count))

    print()
    print("=" * 75)


def main():
    parser = argparse.ArgumentParser(
        description="Prioritize functions for PAL3 decompilation"
    )
    parser.add_argument('--top', '-t', type=int, default=50,
                        help='Show top N functions (default: 50)')
    parser.add_argument('--module', '-m',
                        help='Filter by module name')
    parser.add_argument('--max-size', '-s', type=int,
                        help='Maximum function size in bytes')
    parser.add_argument('--output', '-o',
                        help='Save work queue to JSON file')
    parser.add_argument('--show-reasons', '-r', action='store_true',
                        help='Show scoring reasons for each function')

    args = parser.parse_args()

    # Load data
    functions = load_functions()
    if not functions:
        print("No function data found in {}/".format(ASM_DIR))
        print("Run Ghidra export first, or initial_analysis.py")
        sys.exit(1)

    completed = load_completed()

    # Prioritize
    queue = prioritize(
        functions, completed,
        max_size=args.max_size,
        module_filter=args.module,
    )

    if not queue:
        print("No eligible functions found with current filters.")
        sys.exit(0)

    # Output
    if args.output:
        with open(args.output, 'w') as f:
            json.dump(queue[:args.top], f, indent=2)
        print("Saved {} items to: {}".format(min(args.top, len(queue)), args.output))
    else:
        print_queue(queue, args.top)

    if args.show_reasons:
        print("\nDetailed Scoring:")
        print("-" * 60)
        for item in queue[:args.top]:
            print("\n  {} ({})  Score: {}".format(
                item['name'], item['address'], item['score']))
            for reason in item['reasons']:
                print("    - {}".format(reason))


if __name__ == '__main__':
    main()
