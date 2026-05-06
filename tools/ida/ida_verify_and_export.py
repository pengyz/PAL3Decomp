"""
IDAPython Phase 3: Quality Verification and Re-export Engine

After boundaries are fixed, types imported, and calling conventions corrected,
this script verifies decompilation quality and re-exports qualified functions.

Quality Gate (HARD REJECT - do not export):
  - __userpurge/__usercall (calling convention still broken)
  - positive sp value (stack corruption still present)
  - JUMPOUT (incomplete function boundaries)

Soft Issues (still export, but track):
  - raw_memory (*(_DWORD *), *(_BYTE *), *(_WORD *)) - missing type info

Output: asm/pal3a/decomp/{safe_name}_{address:08x}.json
        _logs/verify_export_log.txt
        _logs/quality_comparison.md
"""

import sys
import os
import json
import re
import time
from datetime import datetime

# IDA imports
import idc
import idaapi
import idautils
import ida_funcs
import ida_hexrays
import ida_name
import builtins

# Add tools/ida to path for ida_common
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SCRIPT_DIR)

import ida_common

# ============================================================================
# Constants
# ============================================================================

SCRIPT_VERSION = "1.0"
PROGRESS_INTERVAL = 500
EH_FUNCLET_PATTERN = re.compile(r'^\$[EL]\d+$|^_\$E\d+$')
SAFE_NAME_PATTERN = re.compile(r'[^a-zA-Z0-9_]')
MAX_NAME_LENGTH = 100

OUTPUT_DIR = os.path.join(ida_common.PROJECT_ROOT, "asm", "pal3a", "decomp")
LOG_FILE = os.path.join(ida_common.LOG_DIR, "verify_export_log.txt")
COMPARISON_REPORT = os.path.join(ida_common.LOG_DIR, "quality_comparison.md")
OLD_DIAGNOSIS_PATH = os.path.join(ida_common.LOG_DIR, "diagnosis_report.json")

# ============================================================================
# Quality Check Functions
# ============================================================================

def check_decompilation_quality(code):
    """
    Check decompiled code for quality issues.

    Returns list of issue tags:
      - 'userpurge': __userpurge/__usercall present
      - 'sp_positive': positive sp value pattern
      - 'jumpout': JUMPOUT pattern
      - 'raw_memory': raw memory access patterns
    """
    issues = []

    # Check for userpurge/usercall
    if '__userpurge' in code or '__usercall' in code:
        issues.append('userpurge')

    # Check for positive sp value (e.g., "*((_DWORD *)&savedregs + 1)")
    if re.search(r'\*\([^)]*&savedregs[^)]*\+', code):
        issues.append('sp_positive')

    # Check for JUMPOUT
    if 'JUMPOUT' in code:
        issues.append('jumpout')

    # Check for raw memory access patterns
    raw_memory_patterns = [
        r'\*\(_DWORD \*\)',
        r'\*\(_BYTE \*\)',
        r'\*\(_WORD \*\)',
        r'\*\(_QWORD \*\)'
    ]
    for pattern in raw_memory_patterns:
        if re.search(pattern, code):
            issues.append('raw_memory')
            break

    return issues


def is_export_qualified(issues):
    """
    Determine if function should be exported based on quality issues.

    HARD REJECT: userpurge, sp_positive, jumpout
    SOFT (still export): raw_memory

    Returns (should_export, reject_reason)
    """
    hard_rejects = {'userpurge', 'sp_positive', 'jumpout'}

    for issue in issues:
        if issue in hard_rejects:
            return (False, issue)

    return (True, None)


def make_safe_name(name):
    """
    Convert function name to safe filename.

    - Replace non-alphanumeric chars with _
    - Truncate to MAX_NAME_LENGTH chars
    """
    safe = SAFE_NAME_PATTERN.sub('_', name)
    if len(safe) > MAX_NAME_LENGTH:
        safe = safe[:MAX_NAME_LENGTH]
    return safe


# ============================================================================
# Collection and Export
# ============================================================================

def collect_export_targets():
    """
    Collect all named functions in .text for export.

    Skip:
      - nullsub_*
      - sub_* (unnamed)
      - EH funclets (^$[EL]\d+ or _$E\d+)

    Returns list of (ea, name, size)
    """
    log("Collecting export targets...")

    targets = []
    skipped = {'nullsub': 0, 'unnamed': 0, 'eh_funclet': 0}

    for ea in idautils.Functions(ida_common.TEXT_START, ida_common.TEXT_END):
        name = ida_name.get_name(ea)

        # Skip nullsub
        if name.startswith('nullsub_'):
            skipped['nullsub'] += 1
            continue

        # Skip unnamed (sub_)
        if name.startswith('sub_'):
            skipped['unnamed'] += 1
            continue

        # Skip EH funclets
        if EH_FUNCLET_PATTERN.match(name):
            skipped['eh_funclet'] += 1
            continue

        # Get size
        func = ida_funcs.get_func(ea)
        if not func:
            continue

        size = func.end_ea - func.start_ea
        targets.append((ea, name, size))

    log(f"Found {len(targets)} export targets")
    log(f"  Skipped: {skipped['nullsub']} nullsub, {skipped['unnamed']} unnamed, {skipped['eh_funclet']} EH funclets")

    return targets


def export_function(ea, name, size, output_dir):
    """
    Decompile and export a single function to JSON.

    Returns (success, quality_issues, reject_reason)
    """
    try:
        # Decompile
        cfunc = ida_hexrays.decompile(ea)
        if not cfunc:
            return (False, [], 'decompile_failed')

        code = str(cfunc)

        # Get signature
        type_str = idc.get_type(ea)
        signature = type_str if type_str else "void __cdecl (void)"

        # Quality check
        issues = check_decompilation_quality(code)
        should_export, reject_reason = is_export_qualified(issues)

        if not should_export:
            return (False, issues, reject_reason)

        # Build JSON
        safe_name = make_safe_name(name)
        filename = f"{safe_name}_{ea:08x}.json"
        filepath = os.path.join(output_dir, filename)

        data = {
            "name": name,
            "address": f"0x{ea:08X}",
            "size_bytes": size,
            "signature": signature,
            "decompiled_c": code,
            "quality_issues": issues
        }

        # Write
        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)

        return (True, issues, None)

    except Exception as e:
        return (False, [], f'exception: {str(e)}')


def export_loop(targets, output_dir):
    """
    Export all targets with progress tracking.

    Returns quality stats dict
    """
    log(f"\nExporting {len(targets)} functions to {output_dir}")
    log("=" * 80)

    stats = {
        'total_candidates': len(targets),
        'exported': 0,
        'rejected_userpurge': 0,
        'rejected_sp': 0,
        'rejected_jumpout': 0,
        'has_raw_memory': 0,
        'clean': 0,
        'errors': 0
    }

    start_time = time.time()

    for idx, (ea, name, size) in enumerate(targets):
        success, issues, reject_reason = export_function(ea, name, size, output_dir)

        if success:
            stats['exported'] += 1
            if 'raw_memory' in issues:
                stats['has_raw_memory'] += 1
            else:
                stats['clean'] += 1
        else:
            if reject_reason == 'userpurge':
                stats['rejected_userpurge'] += 1
            elif reject_reason == 'sp_positive':
                stats['rejected_sp'] += 1
            elif reject_reason == 'jumpout':
                stats['rejected_jumpout'] += 1
            else:
                stats['errors'] += 1

        # Progress report every PROGRESS_INTERVAL functions
        if (idx + 1) % PROGRESS_INTERVAL == 0:
            elapsed = time.time() - start_time
            rate = (idx + 1) / elapsed
            remaining = len(targets) - (idx + 1)
            eta_seconds = remaining / rate if rate > 0 else 0
            eta_minutes = eta_seconds / 60

            log(f"Progress: {idx + 1}/{len(targets)} "
                f"({100 * (idx + 1) / len(targets):.1f}%) | "
                f"Exported: {stats['exported']} | "
                f"Rejected: {stats['rejected_userpurge'] + stats['rejected_sp'] + stats['rejected_jumpout']} | "
                f"Rate: {rate:.1f} func/s | "
                f"ETA: {eta_minutes:.1f} min")

    log("=" * 80)
    log(f"Export complete: {stats['exported']}/{len(targets)} functions exported")

    return stats


# ============================================================================
# Comparison and Reporting
# ============================================================================

def load_old_diagnosis():
    """Load old diagnosis report for comparison, if exists"""
    if not os.path.exists(OLD_DIAGNOSIS_PATH):
        return None

    try:
        with open(OLD_DIAGNOSIS_PATH, 'r', encoding='utf-8') as f:
            return json.load(f)
    except Exception as e:
        log(f"Warning: Failed to load old diagnosis: {e}")
        return None


def generate_comparison_report(stats, old_diagnosis):
    """
    Generate markdown comparison report.

    Compares before (from old diagnosis) vs after (current export) metrics.
    """
    lines = []
    lines.append("# PAL3A Quality Fix Pipeline - Comparison Report")
    lines.append("")
    lines.append(f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    lines.append("")
    lines.append("=" * 80)
    lines.append("")

    # Before/After comparison
    if old_diagnosis:
        old_summary = old_diagnosis.get('summary', {})
        old_by_label = old_summary.get('by_label', {})

        lines.append("## Before/After Comparison")
        lines.append("")
        lines.append("| Metric | Before | After | Change |")
        lines.append("|--------|--------|-------|--------|")

        # Total functions
        old_total = old_summary.get('total_unique_functions', 0)
        lines.append(f"| Total functions | {old_total} | {stats['total_candidates']} | - |")

        # USERPURGE_WRONG
        old_userpurge = old_by_label.get('USERPURGE_WRONG', 0)
        new_userpurge = stats['rejected_userpurge']
        diff_userpurge = new_userpurge - old_userpurge
        sign = '+' if diff_userpurge > 0 else ''
        lines.append(f"| Userpurge issues | {old_userpurge} | {new_userpurge} | {sign}{diff_userpurge} |")

        # SP_CORRUPT
        old_sp = old_by_label.get('SP_CORRUPT', 0)
        new_sp = stats['rejected_sp']
        diff_sp = new_sp - old_sp
        sign = '+' if diff_sp > 0 else ''
        lines.append(f"| SP corruption | {old_sp} | {new_sp} | {sign}{diff_sp} |")

        # BOUNDARY_OVERLAP (approximated by jumpout)
        old_boundary = old_by_label.get('BOUNDARY_OVERLAP', 0)
        new_jumpout = stats['rejected_jumpout']
        diff_boundary = new_jumpout - old_boundary
        sign = '+' if diff_boundary > 0 else ''
        lines.append(f"| Boundary issues | {old_boundary} | {new_jumpout} | {sign}{diff_boundary} |")

        # CLEAN
        old_clean = old_by_label.get('CLEAN', 0)
        new_clean = stats['clean']
        diff_clean = new_clean - old_clean
        sign = '+' if diff_clean > 0 else ''
        lines.append(f"| Clean functions | {old_clean} | {new_clean} | {sign}{diff_clean} |")

        lines.append("")
    else:
        lines.append("## No Previous Diagnosis Available")
        lines.append("")
        lines.append("No `diagnosis_report.json` found for comparison.")
        lines.append("")

    # Export results
    lines.append("## Export Results")
    lines.append("")
    lines.append(f"- **Total candidates**: {stats['total_candidates']}")
    lines.append(f"- **Successfully exported**: {stats['exported']} ({100 * stats['exported'] / stats['total_candidates']:.1f}%)")
    lines.append(f"- **Rejected (userpurge)**: {stats['rejected_userpurge']}")
    lines.append(f"- **Rejected (sp corruption)**: {stats['rejected_sp']}")
    lines.append(f"- **Rejected (jumpout)**: {stats['rejected_jumpout']}")
    lines.append(f"- **Errors**: {stats['errors']}")
    lines.append("")

    # Quality breakdown of exported functions
    lines.append("## Exported Function Quality")
    lines.append("")
    if stats['exported'] > 0:
        lines.append(f"- **Clean** (no issues): {stats['clean']} ({100 * stats['clean'] / stats['exported']:.1f}%)")
        lines.append(f"- **Has raw memory** (soft issue): {stats['has_raw_memory']} ({100 * stats['has_raw_memory'] / stats['exported']:.1f}%)")
    else:
        lines.append("- No functions exported yet")
    lines.append("")

    lines.append("=" * 80)
    lines.append("")
    lines.append("## Summary")
    lines.append("")

    if stats['exported'] > 0:
        lines.append(f"✅ Successfully exported {stats['exported']} qualified functions to `asm/pal3a/decomp/`")
    else:
        lines.append("❌ No functions qualified for export!")

    rejected_total = stats['rejected_userpurge'] + stats['rejected_sp'] + stats['rejected_jumpout']
    if rejected_total > 0:
        lines.append("")
        lines.append(f"⚠️ {rejected_total} functions rejected due to quality issues:")
        if stats['rejected_userpurge'] > 0:
            lines.append(f"  - {stats['rejected_userpurge']} with calling convention issues")
        if stats['rejected_sp'] > 0:
            lines.append(f"  - {stats['rejected_sp']} with stack corruption")
        if stats['rejected_jumpout'] > 0:
            lines.append(f"  - {stats['rejected_jumpout']} with boundary issues")

    if stats['errors'] > 0:
        lines.append("")
        lines.append(f"⚠️ {stats['errors']} functions failed to decompile")

    return '\n'.join(lines)


# ============================================================================
# Logging
# ============================================================================

log, save_log, log_lines = ida_common.make_logger(LOG_FILE)


# ============================================================================
# Main Execution
# ============================================================================

def main():
    """Main verify and export entry point"""
    log("=" * 80)
    log("PAL3A IDA Phase 3: Quality Verification and Re-export Engine")
    log("=" * 80)
    log(f"Script version: {SCRIPT_VERSION}")
    log(f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    log("")

    # Ensure output directory exists
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    log(f"Output directory: {OUTPUT_DIR}")
    log("")

    # Load old diagnosis for comparison
    old_diagnosis = load_old_diagnosis()
    if old_diagnosis:
        log("Loaded previous diagnosis report for comparison")
    else:
        log("No previous diagnosis report found (first run)")
    log("")

    # Collect export targets
    targets = collect_export_targets()
    log("")

    # Export loop
    stats = export_loop(targets, OUTPUT_DIR)
    log("")

    # Generate comparison report
    log("Generating comparison report...")
    comparison_md = generate_comparison_report(stats, old_diagnosis)
    with open(COMPARISON_REPORT, 'w', encoding='utf-8') as f:
        f.write(comparison_md)
    log(f"Comparison report written to: {COMPARISON_REPORT}")
    log("")

    # Save log
    save_log()
    log(f"Log saved to: {LOG_FILE}")

    # Save database
    log("")
    log("Saving IDA database...")
    idc.save_database(idc.get_idb_path())

    # Summary
    log("")
    log("=" * 80)
    log("SUMMARY")
    log("=" * 80)
    log(f"Total candidates: {stats['total_candidates']}")
    log(f"Exported: {stats['exported']} ({100 * stats['exported'] / stats['total_candidates']:.1f}%)")
    log(f"Rejected: {stats['rejected_userpurge'] + stats['rejected_sp'] + stats['rejected_jumpout']}")
    log(f"  - Userpurge: {stats['rejected_userpurge']}")
    log(f"  - SP corruption: {stats['rejected_sp']}")
    log(f"  - Jumpout: {stats['rejected_jumpout']}")
    log(f"Errors: {stats['errors']}")
    log("")
    log(f"Exported function quality:")
    if stats['exported'] > 0:
        log(f"  - Clean: {stats['clean']} ({100 * stats['clean'] / stats['exported']:.1f}%)")
        log(f"  - Has raw memory: {stats['has_raw_memory']} ({100 * stats['has_raw_memory'] / stats['exported']:.1f}%)")
    else:
        log(f"  - No functions exported")
    log("")
    log("=" * 80)
    log("Phase 3 verification and export complete!")
    log("=" * 80)


if __name__ == "__main__":
    main()

    # Standard pipeline exit pattern
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        idc.qexit(0)
