#!/usr/bin/env python3
"""
Progress Tracking Tool for PAL3 Decompilation.

Tracks and reports decompilation progress across all modules.

Usage:
    python progress.py                 # Show overall summary
    python progress.py --module core   # Show progress for a specific module
    python progress.py --detail        # Show per-function detail
    python progress.py --export csv    # Export progress as CSV
    python progress.py --set-total N   # Set total function count (from Ghidra)
"""

import argparse
import csv
import json
import os
import subprocess
import sys
from collections import defaultdict
from datetime import datetime, timedelta
from pathlib import Path

# Project paths
PROJECT_ROOT = Path(__file__).parent.parent
BUILD_DIR = PROJECT_ROOT / "build"
ASM_DIR = PROJECT_ROOT / "asm"
SRC_DIR = PROJECT_ROOT / "src"
PROGRESS_DB = BUILD_DIR / "progress.json"
CONFIG_FILE = BUILD_DIR / "project_config.json"

TARGET_DEFAULTS = {
    'pal3': {
        'asm_dir': ASM_DIR / 'pal3',
        'src_dir': SRC_DIR / 'pal3',
        'progress_db': BUILD_DIR / 'progress.json',
        'config_keys': {
            'total_functions': 'total_functions',
            'text_section_size': 'text_section_size',
        },
        'display_name': 'PAL3',
    },
    'pal3a': {
        'asm_dir': ASM_DIR / 'pal3a',
        'src_dir': SRC_DIR / 'pal3a',
        'progress_db': BUILD_DIR / 'pal3a' / 'translation_status.json',
        'config_keys': {
            'total_functions': 'pal3a_total_functions',
            'text_section_size': 'pal3a_text_section_size',
        },
        'display_name': 'PAL3A',
    },
}

LEGACY_TARGET_TO_SCRIPT = {
    'topo': 'progress_report.py',
    'gbengine': 'gbengine_progress.py',
}


def get_target_defaults(target: str) -> dict:
    return TARGET_DEFAULTS[target]


def load_progress(target: str = 'pal3') -> dict:
    """Load the progress database."""
    progress_db = get_target_defaults(target)['progress_db']
    if progress_db.exists():
        with open(progress_db, 'r') as f:
            return json.load(f)
    return {'functions': {}, 'last_updated': ''}


def load_config() -> dict:
    """Load project configuration."""
    if CONFIG_FILE.exists():
        with open(CONFIG_FILE, 'r') as f:
            return json.load(f)
    return {
        'total_functions': 0,
        'text_section_size': 0,
        'pal3a_total_functions': 0,
        'pal3a_text_section_size': 0,
        'modules': {},
    }


def save_config(config: dict):
    """Save project configuration."""
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    with open(CONFIG_FILE, 'w') as f:
        json.dump(config, f, indent=2)


def count_exported_functions(target: str = 'pal3') -> int:
    """Count JSON files in the target asm/ directory."""
    asm_dir = get_target_defaults(target)['asm_dir']
    if not asm_dir.exists():
        return 0
    json_files = list(asm_dir.glob("*.json"))
    # Exclude summary/meta files
    return len([f for f in json_files if not f.name.startswith('_')])


def count_source_files(target: str = 'pal3') -> dict:
    """Count decompiled source files by module."""
    src_dir = get_target_defaults(target)['src_dir']
    counts = defaultdict(int)
    for src_file in src_dir.rglob("*.c"):
        module = src_file.parent.name
        counts[module] += 1
    for src_file in src_dir.rglob("*.cpp"):
        module = src_file.parent.name
        counts[module] += 1
    return dict(counts)


def get_target_config_value(config: dict, target: str, field: str, default=0):
    keys = get_target_defaults(target)['config_keys']
    return config.get(keys[field], default)


def set_target_config_value(config: dict, target: str, field: str, value):
    keys = get_target_defaults(target)['config_keys']
    config[keys[field]] = value


def get_progress_stats(progress: dict, config: dict, target: str = 'pal3') -> dict:
    """Calculate progress statistics."""
    functions = progress.get('functions', {})
    total_known = get_target_config_value(config, target, 'total_functions', 0)
    exported = count_exported_functions(target)

    stats = {
        'display_name': get_target_defaults(target)['display_name'],
        'total_functions': total_known,
        'exported': exported,
        'processed': len(functions),
        'matched_l1': 0,  # Byte-identical
        'matched_l2': 0,  # Instruction match
        'matched_l3': 0,  # Functional match
        'compiled_only': 0,
        'failed': 0,
        'in_review': 0,
        'total_bytes_matched': 0,
        'by_module': defaultdict(lambda: {'matched': 0, 'total': 0}),
        'by_date': defaultdict(int),
        'recent_activity': [],
    }

    for addr, func in functions.items():
        status = func.get('status', '')
        match_level = func.get('match_level', 0)

        if status == 'matched':
            if match_level == 1:
                stats['matched_l1'] += 1
            elif match_level == 2:
                stats['matched_l2'] += 1
            elif match_level == 3:
                stats['matched_l3'] += 1
        elif status == 'compiled':
            stats['compiled_only'] += 1
        elif status in ('failed', 'error'):
            stats['failed'] += 1

        # Track by module
        source = func.get('source_file', '')
        if source:
            module = Path(source).parent.name
            stats['by_module'][module]['total'] += 1
            if status == 'matched':
                stats['by_module'][module]['matched'] += 1

        # Track by date
        timestamp = func.get('timestamp', '')
        if timestamp:
            try:
                date = timestamp[:10]
                stats['by_date'][date] += 1
            except (IndexError, ValueError):
                pass

    # Sort recent activity
    recent = sorted(functions.items(),
                    key=lambda x: x[1].get('timestamp', ''), reverse=True)
    stats['recent_activity'] = recent[:10]

    return stats


def print_summary(stats: dict):
    """Print a formatted progress summary."""
    total = stats['total_functions'] or stats['exported'] or '?'
    matched_total = stats['matched_l1'] + stats['matched_l2'] + stats['matched_l3']

    print()
    print("=" * 60)
    print("  {} Decompilation Progress".format(stats.get('display_name', 'PAL3')))
    print("=" * 60)
    print()

    # Overall progress bar
    if isinstance(total, int) and total > 0:
        pct = 100 * matched_total / total
        bar_width = 40
        filled = int(bar_width * matched_total / total)
        bar = '#' * filled + '-' * (bar_width - filled)
        print("  Overall: [{}] {:.1f}%".format(bar, pct))
        print()

    print("  {:30s} {:>8s}   {:>6s}".format("Metric", "Count", "%"))
    print("  " + "-" * 50)
    print("  {:30s} {:>8}   {:>6s}".format("Total functions", total, ""))
    print("  {:30s} {:>8}   {:>6s}".format("Exported from Ghidra", stats['exported'], ""))
    print("  {:30s} {:>8}   {:>6s}".format("Processed by AI", stats['processed'], ""))
    print()

    if isinstance(total, int) and total > 0:
        fmt = "  {:30s} {:>8d}   {:>5.1f}%"
        print(fmt.format("Matched (byte-identical)", stats['matched_l1'],
                         100*stats['matched_l1']/total))
        print(fmt.format("Matched (instruction)", stats['matched_l2'],
                         100*stats['matched_l2']/total))
        print(fmt.format("Matched (functional)", stats['matched_l3'],
                         100*stats['matched_l3']/total))
        print(fmt.format("Compiled (not matching)", stats['compiled_only'],
                         100*stats['compiled_only']/total))
        print(fmt.format("Failed", stats['failed'],
                         100*stats['failed']/total))
    else:
        print("  {:30s} {:>8d}".format("Matched (byte-identical)", stats['matched_l1']))
        print("  {:30s} {:>8d}".format("Matched (instruction)", stats['matched_l2']))
        print("  {:30s} {:>8d}".format("Matched (functional)", stats['matched_l3']))
        print("  {:30s} {:>8d}".format("Compiled (not matching)", stats['compiled_only']))
        print("  {:30s} {:>8d}".format("Failed", stats['failed']))

    print()

    # Module breakdown
    if stats['by_module']:
        print("  By Module:")
        print("  " + "-" * 50)
        for module, data in sorted(stats['by_module'].items()):
            print("    {:20s}  {:>4d} matched / {:>4d} processed".format(
                module, data['matched'], data['total']))
        print()

    # Recent activity
    if stats['recent_activity']:
        print("  Recent Activity:")
        print("  " + "-" * 50)
        for addr, func in stats['recent_activity'][:5]:
            status_icon = {
                'matched': '+',
                'compiled': '~',
                'failed': '!',
                'error': 'X',
            }.get(func.get('status', ''), '?')
            print("    [{}] {} {} ({})".format(
                status_icon,
                func.get('name', addr),
                func.get('address', ''),
                func.get('timestamp', '')[:16],
            ))
        print()

    # Daily progress (last 7 days)
    if stats['by_date']:
        print("  Daily Progress (last 7 days):")
        print("  " + "-" * 50)
        today = datetime.now().date()
        for i in range(6, -1, -1):
            date = (today - timedelta(days=i)).isoformat()
            count = stats['by_date'].get(date, 0)
            bar = '#' * min(count, 30)
            print("    {} {:>3d} {}".format(date, count, bar))
        print()

    print("=" * 60)


def print_detail(progress: dict):
    """Print detailed per-function information."""
    functions = progress.get('functions', {})

    print("\n{:<12s} {:<30s} {:<10s} {:<8s} {:<10s}".format(
        "Address", "Name", "Status", "Level", "Confidence"))
    print("-" * 75)

    for addr in sorted(functions.keys()):
        func = functions[addr]
        print("{:<12s} {:<30s} {:<10s} {:<8s} {:<10s}".format(
            func.get('address', addr)[:12],
            func.get('name', '')[:30],
            func.get('status', '')[:10],
            str(func.get('match_level', ''))[:8],
            func.get('confidence', '')[:10],
        ))


def export_csv(progress: dict, output_path: str):
    """Export progress data as CSV."""
    functions = progress.get('functions', {})

    with open(output_path, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow([
            'Address', 'Name', 'Status', 'Match Level',
            'Confidence', 'Attempts', 'Source File', 'Timestamp', 'Notes'
        ])
        for addr in sorted(functions.keys()):
            func = functions[addr]
            writer.writerow([
                func.get('address', addr),
                func.get('name', ''),
                func.get('status', ''),
                func.get('match_level', ''),
                func.get('confidence', ''),
                func.get('attempts', ''),
                func.get('source_file', ''),
                func.get('timestamp', ''),
                func.get('notes', ''),
            ])

    print("Exported to: {}".format(output_path))


def main():
    parser = argparse.ArgumentParser(
        description="PAL3 Decompilation Progress Tracker"
    )
    parser.add_argument('--target', default='pal3', choices=sorted(set(TARGET_DEFAULTS.keys()) | set(LEGACY_TARGET_TO_SCRIPT.keys())))
    parser.add_argument('--module', '-m',
                        help='Filter by module')
    parser.add_argument('--detail', '-d', action='store_true',
                        help='Show per-function details')
    parser.add_argument('--export', '-e', choices=['csv', 'json'],
                        help='Export format')
    parser.add_argument('--output', '-o', default='',
                        help='Export output path')
    parser.add_argument('--set-total', type=int,
                        help='Set total function count')
    parser.add_argument('--set-text-size', type=int,
                        help='Set .text section size in bytes')

    args = parser.parse_args()

    if args.target in LEGACY_TARGET_TO_SCRIPT:
        script = PROJECT_ROOT / 'tools' / LEGACY_TARGET_TO_SCRIPT[args.target]
        legacy_args = sys.argv[1:]
        legacy_args = [arg for arg in legacy_args if arg != '--target' and arg != args.target]
        subprocess.run([sys.executable, str(script)] + legacy_args, check=False)
        return

    # Handle configuration updates
    config = load_config()
    if args.set_total:
        set_target_config_value(config, args.target, 'total_functions', args.set_total)
        save_config(config)
        print("Set total functions for {} to: {}".format(args.target, args.set_total))
        return
    if args.set_text_size:
        set_target_config_value(config, args.target, 'text_section_size', args.set_text_size)
        save_config(config)
        print("Set .text section size for {} to: {} bytes".format(args.target, args.set_text_size))
        return

    # Load data
    progress = load_progress(args.target)
    stats = get_progress_stats(progress, config, args.target)

    # Filter by module if requested
    if args.module:
        filtered_funcs = {}
        for addr, func in progress.get('functions', {}).items():
            source = func.get('source_file', '')
            if args.module in source:
                filtered_funcs[addr] = func
        progress = {'functions': filtered_funcs}
        stats = get_progress_stats(progress, config, args.target)

    # Output
    if args.export == 'csv':
        output_path = args.output or str(BUILD_DIR / "progress_export.csv")
        export_csv(progress, output_path)
    elif args.export == 'json':
        output_path = args.output or str(BUILD_DIR / "progress_export.json")
        with open(output_path, 'w') as f:
            json.dump({'stats': dict(stats), 'functions': progress.get('functions', {})},
                      f, indent=2, default=str)
        print("Exported to: {}".format(output_path))
    elif args.detail:
        print_detail(progress)
    else:
        print_summary(stats)


if __name__ == '__main__':
    main()
