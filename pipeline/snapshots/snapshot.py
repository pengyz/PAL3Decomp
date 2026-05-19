"""Codegen snapshot system — capture state before/after codegen for regression tracking.

Usage:
    python pipeline/snapshots/snapshot.py capture   # save current state
    python pipeline/snapshots/snapshot.py compare   # diff with previous
    python pipeline/snapshots/snapshot.py list      # show all snapshots
"""
import json
import os
import shutil
import subprocess
import hashlib
import time
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
SNAPSHOTS_DIR = PROJECT_ROOT / "pipeline" / "snapshots" / "data"
MAX_SNAPSHOTS = 3

SRC_DIR = PROJECT_ROOT / "src" / "pal3"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
BUILD_DIR = PROJECT_ROOT / "build"


def _hash_dir(d):
    """Hash all files in directory for quick diff detection."""
    h = hashlib.md5()
    if not d.exists():
        return "empty"
    for f in sorted(d.rglob("*")):
        if f.is_file() and f.suffix in ('.cpp', '.h', '.json'):
            h.update(f.read_bytes())
    return h.hexdigest()[:12]


def _compile_and_collect():
    """Run compile, collect error stats."""
    result = subprocess.run(
        'cmake --build build --target PAL3 -- -k 9999',
        shell=True, capture_output=True, text=True, cwd=str(PROJECT_ROOT))
    output = result.stdout + result.stderr

    errors = [l for l in output.split('\n') if 'error C' in l]
    failed = [l for l in output.split('\n') if 'FAILED:' in l]
    total_steps = len([l for l in output.split('\n') if l.startswith('[')])

    # Errors by file
    from collections import Counter
    file_errors = Counter()
    for e in errors:
        import re
        m = re.search(r'\\src\\pal3\\([^(]+)\(', e)
        if m:
            file_errors[m.group(1)] += 1

    # Error code distribution
    error_codes = Counter()
    for e in errors:
        m = re.search(r'error (C\d+)', e)
        if m:
            error_codes[m.group(1)] += 1

    return {
        'total_errors': len(errors),
        'failed_files': len(failed),
        'total_files': total_steps,
        'pass_files': total_steps - len(failed),
        'top_error_codes': error_codes.most_common(10),
        'errors_by_file': dict(file_errors.most_common(20)),
    }


def capture():
    """Capture current state as a snapshot."""
    SNAPSHOTS_DIR.mkdir(parents=True, exist_ok=True)

    timestamp = time.strftime("%Y%m%d_%H%M%S")
    snap_dir = SNAPSHOTS_DIR / timestamp
    snap_dir.mkdir()

    # 1. Decomp summary
    decomp_files = list(DECOMP_DIR.glob("*.json")) if DECOMP_DIR.exists() else []
    decomp_summary = {
        'n_files': len(decomp_files),
        'total_bytes': sum(f.stat().st_size for f in decomp_files),
    }
    (snap_dir / "decomp_summary.json").write_text(json.dumps(decomp_summary, indent=2))

    # 2. Source hash
    src_hash = _hash_dir(SRC_DIR)
    (snap_dir / "src_hash.txt").write_text(src_hash)

    # 3. Compile result
    print("  Compiling for snapshot...")
    compile_result = _compile_and_collect()
    (snap_dir / "compile_result.json").write_text(json.dumps(compile_result, indent=2))

    # 4. Errors by file (full list)
    lines = ["%5d %s" % (v, k) for k, v in
             sorted(compile_result['errors_by_file'].items(), key=lambda x: -x[1])]
    (snap_dir / "errors_by_file.txt").write_text('\n'.join(lines))

    print("  Snapshot saved: %s" % timestamp)
    print("    errors=%d, pass=%d/%d" % (
        compile_result['total_errors'],
        compile_result['pass_files'],
        compile_result['total_files']))

    # Prune old snapshots
    all_snaps = sorted(SNAPSHOTS_DIR.iterdir())
    while len(all_snaps) > MAX_SNAPSHOTS:
        old = all_snaps.pop(0)
        shutil.rmtree(old)
        print("  Pruned old snapshot: %s" % old.name)

    return snap_dir


def compare():
    """Compare latest two snapshots."""
    if not SNAPSHOTS_DIR.exists():
        print("No snapshots found.")
        return

    snaps = sorted(SNAPSHOTS_DIR.iterdir())
    if len(snaps) < 2:
        print("Need at least 2 snapshots to compare. Have %d." % len(snaps))
        return

    prev = snaps[-2]
    curr = snaps[-1]

    prev_result = json.loads((prev / "compile_result.json").read_text())
    curr_result = json.loads((curr / "compile_result.json").read_text())

    delta_errors = curr_result['total_errors'] - prev_result['total_errors']
    delta_pass = curr_result['pass_files'] - prev_result['pass_files']

    print("=== Snapshot Comparison ===")
    print("  Previous: %s (errors=%d, pass=%d)" % (
        prev.name, prev_result['total_errors'], prev_result['pass_files']))
    print("  Current:  %s (errors=%d, pass=%d)" % (
        curr.name, curr_result['total_errors'], curr_result['pass_files']))
    print("  Delta: errors %+d, pass %+d" % (delta_errors, delta_pass))

    if delta_errors > 0:
        print("\n  [REGRESSION] %d more errors!" % delta_errors)
    elif delta_errors < 0:
        print("\n  [IMPROVEMENT] %d fewer errors" % (-delta_errors))

    # Show top error code changes
    prev_codes = dict(prev_result['top_error_codes'])
    curr_codes = dict(curr_result['top_error_codes'])
    all_codes = set(prev_codes) | set(curr_codes)
    changes = []
    for code in all_codes:
        d = curr_codes.get(code, 0) - prev_codes.get(code, 0)
        if d != 0:
            changes.append((code, d))
    changes.sort(key=lambda x: -abs(x[1]))
    if changes:
        print("\n  Error code changes:")
        for code, d in changes[:5]:
            print("    %s: %+d" % (code, d))


def list_snapshots():
    """List all snapshots."""
    if not SNAPSHOTS_DIR.exists():
        print("No snapshots.")
        return
    for snap in sorted(SNAPSHOTS_DIR.iterdir()):
        result_file = snap / "compile_result.json"
        if result_file.exists():
            r = json.loads(result_file.read_text())
            print("  %s: errors=%d, pass=%d/%d" % (
                snap.name, r['total_errors'], r['pass_files'], r['total_files']))


if __name__ == '__main__':
    import sys
    cmd = sys.argv[1] if len(sys.argv) > 1 else 'capture'
    if cmd == 'capture':
        capture()
    elif cmd == 'compare':
        compare()
    elif cmd == 'list':
        list_snapshots()
    else:
        print("Usage: snapshot.py [capture|compare|list]")
