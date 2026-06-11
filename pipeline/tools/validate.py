#!/usr/bin/env python3
"""
Full validation: clean rebuild + compile + quality report.

Usage:
    python pipeline/tools/validate.py                      # Full run
    python pipeline/tools/validate.py --no-init            # Skip init --force
    python pipeline/tools/validate.py --class RoleSystem   # Focus report on one class
"""

import subprocess, sys, os, json, shutil
from datetime import datetime

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PROGRESS_DIR = os.path.join(os.path.dirname(__file__), '..', 'progress')
os.makedirs(PROGRESS_DIR, exist_ok=True)

HISTORY_FILE = os.path.join(PROGRESS_DIR, 'history.json')
CURRENT_FILE = os.path.join(PROGRESS_DIR, 'current.json')

SCAN_SCRIPT = os.path.join(os.path.dirname(__file__), 'scan_progress.py')


def run(cmd, desc, timeout=3600, cwd=None):
    print(f"\n=== {desc} ===")
    print(f"  $ {cmd}")
    cwd = cwd or PROJECT_ROOT
    try:
        r = subprocess.run(cmd, shell=True, cwd=cwd, timeout=timeout,
                           capture_output=True, text=True)
        if r.returncode != 0:
            print(f"  WARN: exit code {r.returncode}")
            for line in r.stderr.split('\n')[-5:]:
                if line.strip():
                    print(f"  stderr: {line.strip()}")
        return r.returncode == 0, r.stdout, r.stderr
    except subprocess.TimeoutExpired:
        print(f"  TIMEOUT after {timeout}s")
        return False, '', ''


def load_history():
    if os.path.exists(HISTORY_FILE):
        with open(HISTORY_FILE) as f:
            return json.load(f)
    return {'runs': []}


def save_history(runs):
    with open(HISTORY_FILE, 'w') as f:
        json.dump(runs, f, indent=2)


def count_compile_errors(stdout):
    return sum(1 for line in stdout.split('\n') if 'error C' in line)


def main():
    args = sys.argv[1:]
    skip_init = '--no-init' in args
    focus_class = None
    if '--class' in args:
        idx = args.index('--class')
        focus_class = args[idx + 1] if idx + 1 < len(args) else None

    print("=" * 60)
    print(f"VALIDATE — {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print("=" * 60)

    # ── Step 1: Clean generated artifacts ──
    gen_dir = os.path.join(PROJECT_ROOT, 'src', 'pal3', 'gen')
    inc_dir = os.path.join(PROJECT_ROOT, 'include', 'pal3', 'gen')
    decomp_dir = os.path.join(PROJECT_ROOT, 'asm', 'pal3', 'decomp')

    for d in [gen_dir, inc_dir, decomp_dir]:
        if os.path.exists(d):
            shutil.rmtree(d)
            print(f"\n  Cleaned: {os.path.relpath(d, PROJECT_ROOT)}")

    # ── Step 2: init --force ──
    if not skip_init:
        ok, _, _ = run(
            'python3 pipeline/cli.py init --force 2>&1',
            'init --force (fresh IDB)',
            timeout=3600
        )
        if not ok:
            print("\n[FAIL] init --force failed. Aborting.")
            sys.exit(1)

    # ── Step 3: export ──
    ok, _, _ = run(
        'python3 pipeline/cli.py export 2>&1',
        'export decomp JSONs',
        timeout=1800
    )
    if not ok:
        print("\n[WARN] export had warnings")

    # ── Step 4: codegen ──
    ok, co_stout, co_stderr = run(
        'python3 pipeline/cli.py codegen all 2>&1',
        'codegen headers + cpp',
        timeout=600
    )

    # Extract snapshot error count
    snap_match = None
    for line in co_stout.split('\n'):
        if 'errors=' in line:
            snap_match = line.strip()
    if snap_match:
        print(f"  Snapshot: {snap_match}")

    # ── Step 5: compile ──
    ok, cc_stdout, cc_stderr = run(
        'ninja -C build -k 0 2>&1',
        'compile (ninja -k 0)',
        timeout=3600
    )
    compile_errors = count_compile_errors(cc_stdout)
    print(f"  Compile errors: {compile_errors}")

    # ── Step 6: scan progress ──
    run(
        f'python3 {SCAN_SCRIPT}',
        'scan progress (hardcoded offsets)',
        timeout=120
    )

    with open(CURRENT_FILE) as f:
        scan_data = json.load(f)
    total_hc = scan_data['total_hc']

    # ── Step 7: report ──
    history = load_history()
    last_hc = history['runs'][-1]['hc'] if history['runs'] else None
    hc_delta = total_hc - last_hc if last_hc is not None else 0

    print("\n" + "=" * 60)
    print("QUALITY REPORT")
    print("=" * 60)
    print(f"  Compile errors:   {compile_errors}")
    print(f"  Hardcoded offsets: {total_hc}", end='')
    if last_hc is not None:
        direction = '+' if hc_delta > 0 else ''
        print(f"  ({direction}{hc_delta} vs previous {last_hc})")
    else:
        print("  (baseline)")
    print(f"  Files w/ HC:       {scan_data['files_scanned']}")

    # Top offenders
    print(f"\n  Top 10 classes by HC:")
    for c in scan_data['classes'][:10]:
        print(f"    {c['class']:35s} HC={c['hc']:4d}")

    # Focus class detail if requested
    if focus_class:
        print(f"\n  Focus: {focus_class}")
        for c in scan_data['classes']:
            if c['class'] == focus_class:
                d = c['details']
                print(f"    File: {c['file']}")
                print(f"    HC:   {c['hc']}")
                print(f"    DWORD={d['DWORD']} BYTE={d['BYTE']} WORD={d['WORD']} "
                      f"float={d['float']} LODWORD={d['LODWORD']}")
                break

    # ── Step 8: Save history ──
    entry = {
        'date': datetime.now().strftime('%Y-%m-%d %H:%M'),
        'hc': total_hc,
        'compile_errors': compile_errors,
        'files_with_hc': scan_data['files_scanned'],
    }
    history['runs'].append(entry)
    save_history(history)

    print(f"\n  History saved: {HISTORY_FILE}")
    print("=" * 60)


if __name__ == '__main__':
    main()
