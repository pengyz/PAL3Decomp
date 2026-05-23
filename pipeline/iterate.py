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

from pipeline.cli import cmd_init, cmd_export, cmd_codegen, _run_ida
from pipeline.snapshots.snapshot import _compile_and_collect
from pipeline.iterate_rules import analyze_evidence
from pipeline.iterate_apply import apply_fixes, rollback_all, Fix
from pipeline.config import cfg


def run_ida_queries():
    """Run IDA query scripts to gather evidence."""
    idb = str(cfg.idb_work)
    print("  Running IDA queries...")
    _run_ida('query_todo_fields.py', idb)
    _run_ida('_query_lea_batch.py', idb)


def evaluate():
    """Compile and return (total_errors, pass_files)."""
    result = _compile_and_collect()
    return result['total_errors'], result['pass_files']


def save_build_output():
    """Run compile and save output for rule analysis."""
    result = subprocess.run(
        'cmake --build build --target PAL3 -- -k 9999',
        shell=True, capture_output=True, text=True, cwd=str(PROJECT_ROOT))
    output = result.stdout + result.stderr
    (PROJECT_ROOT / 'build_output.txt').write_text(output, encoding='utf-8')
    return output.count('error C')


def commit(msg: str):
    """Commit annotation changes."""
    subprocess.run(['git', 'add', 'data/annotations/'], cwd=str(PROJECT_ROOT))
    subprocess.run(['git', 'commit', '-m', msg], cwd=str(PROJECT_ROOT))


def main():
    parser = argparse.ArgumentParser(description='PAL3 Annotation Iteration Engine')
    parser.add_argument('--max-rounds', type=int, default=20)
    parser.add_argument('--stale-limit', type=int, default=3)
    parser.add_argument('--target-errors', type=int, default=1000)
    parser.add_argument('--target-pass', type=int, default=100)
    parser.add_argument('--dry-run', action='store_true',
                        help='Analyze and show candidates without applying')
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

    # Get baseline
    print("Getting baseline...")
    prev_errors = save_build_output()
    print(f"  Baseline: {prev_errors} errors")
    print()

    stale = 0
    for round_num in range(1, args.max_rounds + 1):
        print(f"{'='*60}")
        print(f"ROUND {round_num} (baseline: {prev_errors} errors, stale: {stale})")
        print(f"{'='*60}")

        # Step 1: IDA queries
        run_ida_queries()

        # Step 2: Analyze evidence
        print("  Analyzing evidence...")
        fixes = analyze_evidence()
        print(f"  Candidates: {len(fixes)}")
        for f in fixes[:10]:
            print(f"    [{f.type}] {f.target}: {f.old_value} \u2192 {f.new_value} ({f.evidence})")
        if len(fixes) > 10:
            print(f"    ... and {len(fixes) - 10} more")

        if not fixes:
            print("  No candidates. STOPPING (exhausted).")
            break

        if args.dry_run:
            print(f"\n  DRY RUN: would apply {len(fixes)} fixes. Stopping.")
            break

        # Step 3: Apply fixes
        print("  Applying fixes...")
        applied = apply_fixes(fixes)
        print(f"  Applied: {len(applied)}/{len(fixes)}")

        if not applied:
            print("  All fixes rejected by check_annotations. STOPPING.")
            break

        # Step 4: Full pipeline rebuild
        print("  Rebuilding pipeline (init \u2014force \u2192 export \u2192 codegen)...")
        cmd_init(force=True)
        cmd_export()
        cmd_codegen(['all'])

        # Step 5: Evaluate
        errors = save_build_output()
        # Count pass files from last compile
        result = _compile_and_collect()
        passes = result['pass_files']
        print(f"  Result: {errors} errors, {passes} pass files")

        # Step 6: Convergence check
        if errors < args.target_errors or passes > args.target_pass:
            commit(f"iterate: target reached ({errors} errors, {passes} pass)")
            print(f"\n  TARGET REACHED. Stopping.")
            break
        elif errors < prev_errors:
            delta = prev_errors - errors
            commit(f"iterate(round {round_num}): -{delta} errors ({errors} total, {passes} pass)")
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
