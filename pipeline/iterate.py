#!/usr/bin/env python3
"""PAL3 Annotation Iteration Engine.

Automatically applies annotation fixes based on evidence rules,
rebuilds the pipeline, and iterates until convergence.

Usage:
    python pipeline/iterate.py                    # default run
    python pipeline/iterate.py --dry-run          # analyze only
    python pipeline/iterate.py --max-rounds 5     # limit rounds
    python pipeline/iterate.py --target-errors 500
"""
import argparse
import subprocess
import sys
import os
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
sys.path.insert(0, str(PROJECT_ROOT))
os.chdir(str(PROJECT_ROOT))

from pipeline.config import cfg
from pipeline.cli import cmd_init, cmd_export, cmd_codegen, _run_ida
from pipeline.snapshots.snapshot import _compile_and_collect
from pipeline.iterate_rules import analyze_evidence
from pipeline.iterate_apply import apply_fixes, rollback_all


def run_ida_queries():
    idb = str(cfg.idb_work)
    print("  Running IDA queries...")
    _run_ida('query_todo_fields.py', idb)
    _run_ida('_query_lea_batch.py', idb)


def save_build_output() -> int:
    result = subprocess.run(
        'cmake --build build --target PAL3 -- -k 9999',
        shell=True, capture_output=True, text=True, cwd=str(PROJECT_ROOT))
    output = result.stdout + result.stderr
    (PROJECT_ROOT / 'build_output.txt').write_text(output, encoding='utf-8')
    return output.count('error C')


def evaluate():
    result = _compile_and_collect()
    return result['total_errors'], result['pass_files']


def commit(msg: str):
    subprocess.run(['git', 'add', 'data/annotations/'], cwd=str(PROJECT_ROOT))
    subprocess.run(['git', 'commit', '-m', f'iterate(auto): {msg}',
                    '-m', 'Co-Authored-By: Claude Opus 4.6 (1M context) <noreply@anthropic.com>'],
                   cwd=str(PROJECT_ROOT))


def main():
    parser = argparse.ArgumentParser(description='PAL3 Annotation Iteration Engine')
    parser.add_argument('--max-rounds', type=int, default=20)
    parser.add_argument('--stale-limit', type=int, default=3)
    parser.add_argument('--target-errors', type=int, default=1000)
    parser.add_argument('--target-pass', type=int, default=100)
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()

    print("=" * 60)
    print("PAL3 Annotation Iteration Engine")
    print("=" * 60)
    print(f"  max_rounds:    {args.max_rounds}")
    print(f"  stale_limit:   {args.stale_limit}")
    print(f"  target_errors: {args.target_errors}")
    print(f"  target_pass:   {args.target_pass}")
    print(f"  dry_run:       {args.dry_run}")
    print()

    print("Getting baseline...")
    prev_errors = save_build_output()
    print(f"  Baseline: {prev_errors} errors")
    print()

    stale = 0
    for round_num in range(1, args.max_rounds + 1):
        print(f"{'=' * 60}")
        print(f"ROUND {round_num} (baseline: {prev_errors} errors, stale: {stale})")
        print(f"{'=' * 60}")

        run_ida_queries()

        print("  Analyzing evidence...")
        fixes = analyze_evidence()
        print(f"  Candidates: {len(fixes)}")
        for f in fixes[:10]:
            print(f"    [{f.type}] {f.target}: {f.old_value} -> {f.new_value} ({f.evidence})")
        if len(fixes) > 10:
            print(f"    ... and {len(fixes) - 10} more")

        if not fixes:
            print("  No candidates. STOPPING (exhausted).")
            break

        if args.dry_run:
            print(f"\n  DRY RUN: would apply {len(fixes)} fixes. Stopping.")
            break

        print("  Applying fixes...")
        applied = apply_fixes(fixes)
        print(f"  Applied: {len(applied)}/{len(fixes)}")

        if not applied:
            print("  All fixes rejected. STOPPING.")
            break

        print("  Rebuilding pipeline (init --force -> export -> codegen)...")
        cmd_init(force=True)
        cmd_export()
        cmd_codegen(['all'])

        errors = save_build_output()
        result = _compile_and_collect()
        passes = result['pass_files']
        print(f"  Result: {errors} errors, {passes} pass files")

        if errors < args.target_errors or passes > args.target_pass:
            commit(f"target reached ({errors} errors, {passes} pass)")
            print(f"\n  TARGET REACHED. Stopping.")
            break
        elif errors < prev_errors:
            delta = prev_errors - errors
            commit(f"round {round_num}: -{delta} errors ({errors} total, {passes} pass)")
            print(f"  IMPROVED: -{delta} errors")
            stale = 0
            prev_errors = errors
        else:
            print(f"  NO IMPROVEMENT ({errors} >= {prev_errors}). Rolling back.")
            rollback_all()
            stale += 1
            if stale >= args.stale_limit:
                print(f"\n  CONVERGED: {stale} stale rounds. Stopping.")
                break

    print()
    print("=" * 60)
    print(f"DONE. Final: {prev_errors} errors")
    print("=" * 60)


if __name__ == '__main__':
    main()
