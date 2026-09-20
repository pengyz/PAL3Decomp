"""Codegen snapshot system — capture state before/after codegen for regression tracking.

Captures the decomp export summary plus the latest S1/S2 probe census
fingerprint (data/status/probe_census.json, written by pipeline/probe_compile.py).
It does NOT recompile — run `python pipeline/cli.py probe` first if the census
may be stale (capture warns when it is).

Usage:
    python pipeline/snapshots/snapshot.py capture   # save current state
    python pipeline/snapshots/snapshot.py compare   # diff with previous
    python pipeline/snapshots/snapshot.py list      # show all snapshots
"""
import json
import os
import shutil
import subprocess
import time
from datetime import datetime
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent.parent
SNAPSHOTS_DIR = PROJECT_ROOT / "pipeline" / "snapshots" / "data"
MAX_SNAPSHOTS = 20

DECOMP_DIRS = [PROJECT_ROOT / "asm" / "pal3" / "decomp",
               PROJECT_ROOT / "data" / "decomp"]
CENSUS_FILE = PROJECT_ROOT / "data" / "status" / "probe_census.json"
CENSUS_MAX_AGE_MIN = 120


def _find_decomp_dir():
    for d in DECOMP_DIRS:
        if d.exists():
            return d
    return None


def _census_and_collect():
    """Fingerprint the latest probe census (no recompile).

    Returns the same artifact shape the cmake-era capture produced, so
    `compare` works unchanged. Raises if the census is missing."""
    if not CENSUS_FILE.exists():
        raise FileNotFoundError(
            "probe_census.json not found — run `python pipeline/cli.py probe` first")
    census = json.loads(CENSUS_FILE.read_text(encoding='utf-8'))

    generated_at = census.get('generated_at', '')
    age_min = None
    if generated_at:
        try:
            age_min = (datetime.now() -
                       datetime.fromisoformat(generated_at)).total_seconds() / 60
        except ValueError:
            pass
    if age_min is not None and age_min > CENSUS_MAX_AGE_MIN:
        print("  [WARN] probe_census.json is %.0f min old — run probe first "
              "for a meaningful snapshot" % age_min)

    results = census.get('s2', {}).get('results', [])
    from collections import Counter
    error_codes = Counter()
    file_errors = Counter()
    raw_errors = []
    pass_files, fail_files = [], []
    for r in results:
        unit = r.get('unit', '')
        errs = r.get('errors', [])
        if r.get('status') == 'ok':
            pass_files.append(unit)
            continue
        if r.get('status') == 'fail':
            fail_files.append(unit)
        for e in errs:
            error_codes[e['code']] += 1
            file_errors[unit] += 1
            raw_errors.append('%s(%d): error %s: %s'
                              % (unit, e.get('line', 0), e['code'], e['msg']))
    return {
        'generated_at': generated_at,
        's2_ok': census.get('s2', {}).get('ok'),
        's2_total': census.get('s2', {}).get('total'),
        's1_ok': census.get('s1', {}).get('ok'),
        's1_total': census.get('s1', {}).get('total'),
        'total_errors': sum(error_codes.values()),
        'failed_files': len(fail_files),
        'total_files': len(results),
        'pass_files': len(pass_files),
        'top_error_codes': error_codes.most_common(10),
        'errors_by_file': dict(file_errors),
        '_raw_errors': raw_errors,
        '_pass_files': sorted(pass_files),
        '_fail_files': sorted(fail_files),
    }


def capture():
    """Capture current state as a snapshot."""
    SNAPSHOTS_DIR.mkdir(parents=True, exist_ok=True)

    timestamp = time.strftime("%Y%m%d_%H%M%S")
    snap_dir = SNAPSHOTS_DIR / timestamp
    snap_dir.mkdir()

    # 0. Metadata: commit id + timestamp
    # NOTE: git 输出是 UTF-8（提交标题含中文）；Windows 上 `text=True` 会用
    # locale 编码（GBK）解码，ReaderThread 抛 UnicodeDecodeError 后 stdout 变
    # None ⇒ `codegen all` 的 snapshot 步骤整体失败。显式指定 UTF-8。
    commit_id = subprocess.run(
        ['git', 'rev-parse', '--short', 'HEAD'],
        capture_output=True, text=True,
        encoding='utf-8', errors='replace', cwd=str(PROJECT_ROOT)
    ).stdout.strip()
    meta = {
        'timestamp': time.strftime("%Y-%m-%d %H:%M:%S"),
        'commit': commit_id,
        'commit_full': subprocess.run(
            ['git', 'rev-parse', 'HEAD'],
            capture_output=True, text=True,
            encoding='utf-8', errors='replace', cwd=str(PROJECT_ROOT)
        ).stdout.strip(),
        'commit_msg': subprocess.run(
            ['git', 'log', '-1', '--format=%s'],
            capture_output=True, text=True,
            encoding='utf-8', errors='replace', cwd=str(PROJECT_ROOT)
        ).stdout.strip(),
    }
    (snap_dir / "meta.json").write_text(json.dumps(meta, indent=2),
                                        encoding='utf-8', errors='replace')

    # 1. Decomp summary
    decomp_dir = _find_decomp_dir()
    decomp_files = list(decomp_dir.glob("*.json")) if decomp_dir else []
    decomp_summary = {
        'n_files': len(decomp_files),
        'total_bytes': sum(f.stat().st_size for f in decomp_files),
    }
    (snap_dir / "decomp_summary.json").write_text(json.dumps(decomp_summary, indent=2),
                                                 encoding='utf-8', errors='replace')

    # 2. Probe census fingerprint (S1/S2 pass-fail + full error list)
    print("  Fingerprinting probe census...")
    compile_result = _census_and_collect()
    (snap_dir / "compile_result.json").write_text(json.dumps(compile_result, indent=2),
                                                  encoding='utf-8', errors='replace')

    # 3. Full error list (every error with file:line:code, for precise diff)
    (snap_dir / "all_errors.txt").write_text('\n'.join(compile_result['_raw_errors']),
                                             encoding='utf-8', errors='replace')

    # 4. Per-file error count (for identifying which files regressed)
    lines = ["%5d %s" % (v, k) for k, v in
             sorted(compile_result['errors_by_file'].items(), key=lambda x: -x[1])]
    (snap_dir / "errors_by_file.txt").write_text('\n'.join(lines),
                                                 encoding='utf-8', errors='replace')

    # 5. Pass/fail file lists (track which files flip between pass/fail)
    (snap_dir / "pass_files.txt").write_text('\n'.join(sorted(compile_result['_pass_files'])),
                                             encoding='utf-8', errors='replace')
    (snap_dir / "fail_files.txt").write_text('\n'.join(sorted(compile_result['_fail_files'])),
                                             encoding='utf-8', errors='replace')

    print("  Snapshot saved: %s" % timestamp)
    print("    S2 %s/%s, errors=%d, pass=%d/%d" % (
        compile_result.get('s2_ok'), compile_result.get('s2_total'),
        compile_result['total_errors'],
        compile_result['pass_files'], compile_result['total_files']))

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

    snaps = [s for s in sorted(SNAPSHOTS_DIR.iterdir())
             if (s / "compile_result.json").exists()]
    if len(snaps) < 2:
        print("Need at least 2 census-bearing snapshots. Have %d." % len(snaps))
        return

    prev = snaps[-2]
    curr = snaps[-1]

    prev_result = json.loads((prev / "compile_result.json").read_text(encoding='utf-8', errors='replace'))
    curr_result = json.loads((curr / "compile_result.json").read_text(encoding='utf-8', errors='replace'))

    delta_errors = curr_result['total_errors'] - prev_result['total_errors']
    delta_pass = curr_result['pass_files'] - prev_result['pass_files']

    print("=== Snapshot Comparison ===")
    print("  Previous: %s (S2 %s/%s, errors=%d, pass=%d)" % (
        prev.name, prev_result.get('s2_ok'), prev_result.get('s2_total'),
        prev_result['total_errors'], prev_result['pass_files']))
    print("  Current:  %s (S2 %s/%s, errors=%d, pass=%d)" % (
        curr.name, curr_result.get('s2_ok'), curr_result.get('s2_total'),
        curr_result['total_errors'], curr_result['pass_files']))
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

    # File-level regression: files that got worse or flipped pass→fail
    prev_pass = set((prev / "pass_files.txt").read_text(encoding='utf-8', errors='replace').split('\n')) if (prev / "pass_files.txt").exists() else set()
    curr_pass = set((curr / "pass_files.txt").read_text(encoding='utf-8', errors='replace').split('\n')) if (curr / "pass_files.txt").exists() else set()
    lost = prev_pass - curr_pass - {''}
    gained = curr_pass - prev_pass - {''}
    if lost:
        print("\n  Files LOST (pass→fail): %d" % len(lost))
        for f in sorted(lost)[:5]:
            print("    - %s" % f)
    if gained:
        print("\n  Files GAINED (fail→pass): %d" % len(gained))
        for f in sorted(gained)[:5]:
            print("    + %s" % f)

    # Per-file error delta (top regressions)
    prev_errs = json.loads((prev / "compile_result.json").read_text(encoding='utf-8', errors='replace')).get('errors_by_file', {})
    curr_errs = json.loads((curr / "compile_result.json").read_text(encoding='utf-8', errors='replace')).get('errors_by_file', {})
    all_files = set(prev_errs) | set(curr_errs)
    file_deltas = [(f, curr_errs.get(f, 0) - prev_errs.get(f, 0)) for f in all_files]
    file_deltas.sort(key=lambda x: -x[1])
    regressions = [(f, d) for f, d in file_deltas if d > 0]
    if regressions:
        print("\n  Top file regressions:")
        for f, d in regressions[:5]:
            print("    %s: +%d errors" % (f, d))


def list_snapshots():
    """List all snapshots."""
    if not SNAPSHOTS_DIR.exists():
        print("No snapshots.")
        return
    for snap in sorted(SNAPSHOTS_DIR.iterdir()):
        result_file = snap / "compile_result.json"
        meta_file = snap / "meta.json"
        if result_file.exists():
            r = json.loads(result_file.read_text(encoding='utf-8', errors='replace'))
            meta = json.loads(meta_file.read_text(encoding='utf-8', errors='replace')) if meta_file.exists() else {}
            commit = meta.get('commit', '?')
            ts = meta.get('timestamp', snap.name)
            msg = meta.get('commit_msg', '')[:40]
            print("  %s [%s] S2 %s/%s, pass=%d/%d  %s" % (
                ts, commit, r.get('s2_ok'), r.get('s2_total'),
                r['pass_files'], r['total_files'], msg))


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
