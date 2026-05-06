"""
IDAPython Phase 2 Step 1: Function Boundary Overlap Fixer

Fixes BOUNDARY_OVERLAP entries from diagnosis_report.json by:
  1. Truncating parent functions at split points
  2. Creating new functions at PDB-specified addresses
  3. Applying PDB names to new functions

By default, runs in dry-run mode (logging only).
Pass '--execute' in sys.argv to actually modify the database.

Reads: _logs/diagnosis_report.json (from ida_diagnose_quality.py)
Loads PDB names from: asm/pal3a/pdb_export.json

Report structure (filtered for BOUNDARY_OVERLAP with conf >= 0.8):
  {
    "functions": {
      "0xADDR": {
        "name": "func_name",
        "labels": [
          ["BOUNDARY_OVERLAP", 0.95, {"next_pdb_addr": "0x...", ...}]
        ]
      }
    }
  }
"""

import sys
import os
import json
import traceback
import builtins

# IDA imports
import idc
import ida_auto
import ida_funcs
import ida_name

# Add tools/ida to path for ida_common
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SCRIPT_DIR)

import ida_common

# ============================================================================
# Constants
# ============================================================================

DIAGNOSIS_REPORT = os.path.join(ida_common.LOG_DIR, "diagnosis_report.json")
LOG_FILE = os.path.join(ida_common.LOG_DIR, "fix_boundaries_log.txt")
PDB_EXPORT = ida_common.PDB_EXPORT
CONF_THRESHOLD = ida_common.CONF_AUTO_FIX

# ============================================================================
# Utility Functions
# ============================================================================


def load_pdb_names():
    """Load PDB export and build address -> name map"""
    if not os.path.exists(PDB_EXPORT):
        return {}

    try:
        with open(PDB_EXPORT, "r", encoding="utf-8") as f:
            pdb_data = json.load(f)

        addr_to_name = {}
        for func in pdb_data.get("functions", []):
            addr_str = func.get("address", "")
            name = func.get("name", "")
            if addr_str and name:
                try:
                    addr = int(addr_str, 16)
                    addr_to_name[addr] = name
                except (ValueError, KeyError):
                    pass

        return addr_to_name
    except Exception as e:
        print(f"[!] Error loading PDB names: {e}")
        return {}


def sanitize_name(name):
    """Convert PDB name to valid IDA identifier"""
    # Replace :: with _
    safe = name.replace("::", "_")
    # Replace ~ with _dtor_
    safe = safe.replace("~", "_dtor_")
    # Replace template brackets
    safe = safe.replace("<", "_").replace(">", "_")
    # Replace spaces
    safe = safe.replace(" ", "_")
    # Replace backticks and quotes (adjustor thunks)
    safe = safe.replace("`", "_").replace("'", "_")
    return safe


def load_diagnosis_report():
    """Load diagnosis report and extract BOUNDARY_OVERLAP entries"""
    if not os.path.exists(DIAGNOSIS_REPORT):
        return []

    try:
        with open(DIAGNOSIS_REPORT, "r", encoding="utf-8") as f:
            report = json.load(f)

        overlaps = []
        for addr_str, func_info in report.get("functions", {}).items():
            try:
                addr = int(addr_str, 16)
            except (ValueError, KeyError):
                continue

            func_name = func_info.get("name", f"sub_{addr:08X}")

            for label_entry in func_info.get("labels", []):
                if len(label_entry) < 3:
                    continue

                label, confidence, details = label_entry[0], label_entry[1], label_entry[2]

                # Filter: only BOUNDARY_OVERLAP with confidence >= threshold
                if label == "BOUNDARY_OVERLAP" and confidence >= CONF_THRESHOLD:
                    next_pdb_addr_str = details.get("next_pdb_addr", "")
                    if next_pdb_addr_str:
                        try:
                            split_addr = int(next_pdb_addr_str, 16)
                            overlaps.append({
                                "parent_addr": addr,
                                "parent_name": func_name,
                                "split_addr": split_addr,
                                "confidence": confidence,
                                "details": details
                            })
                        except (ValueError, KeyError):
                            pass

        return overlaps
    except Exception as e:
        print(f"[!] Error loading diagnosis report: {e}")
        return []


def fix_boundary_overlap(parent_addr, split_addr, log_func, dry_run=True):
    """
    Attempt to fix a boundary overlap by truncating parent and creating new func.

    Returns:
        (success, message): (bool, str)
    """
    try:
        parent_func = ida_funcs.get_func(parent_addr)
        if not parent_func:
            return (False, f"Parent function not found at 0x{parent_addr:08X}")

        old_end = parent_func.end_ea

        # Verify split point is valid
        is_valid, evidence = ida_common.is_valid_split_point(split_addr)
        if not is_valid:
            return (False, f"Split point 0x{split_addr:08X} invalid: {evidence}")

        if dry_run:
            msg = (f"[DRY-RUN] Would truncate 0x{parent_addr:08X} "
                   f"(end 0x{old_end:08X} -> 0x{split_addr:08X}), "
                   f"create new at 0x{split_addr:08X}")
            return (True, msg)

        # Actually perform the fix
        # Step 1: Truncate parent function
        if not ida_funcs.set_func_end(parent_addr, split_addr):
            return (False, f"Failed to truncate parent at 0x{parent_addr:08X}")

        # Step 2: Create new function at split point
        if ida_funcs.add_func(split_addr, old_end):
            msg = (f"[SUCCESS] Truncated 0x{parent_addr:08X} "
                   f"(end 0x{old_end:08X} -> 0x{split_addr:08X}), "
                   f"created new at 0x{split_addr:08X}")
            return (True, msg)
        else:
            # Rollback: restore original end
            if ida_funcs.set_func_end(parent_addr, old_end):
                return (False, f"Failed to create new function at 0x{split_addr:08X} (rolled back)")
            else:
                return (False, f"Failed to create new function at 0x{split_addr:08X} "
                        f"(ROLLBACK FAILED - database may be corrupted!)")

    except Exception as e:
        return (False, f"Exception: {str(e)}")


# ============================================================================
# Main Execution
# ============================================================================


def main():
    log_lines = []

    def log(msg):
        msg_str = str(msg)
        log_lines.append(msg_str)
        print(msg_str)

    try:
        # Check if we're in dry-run mode
        dry_run = "--execute" not in sys.argv
        mode_str = "[DRY-RUN]" if dry_run else "[EXECUTE]"

        log(f"{mode_str} IDA Fix Boundaries Phase 2 Step 1")
        log(f"Confidence threshold: {CONF_THRESHOLD}")

        # Wait for IDA to be ready
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        # Load PDB names
        pdb_names = load_pdb_names()
        log(f"[*] Loaded {len(pdb_names)} PDB function names")

        # Load diagnosis report
        overlaps = load_diagnosis_report()
        log(f"[*] Found {len(overlaps)} BOUNDARY_OVERLAP entries (conf >= {CONF_THRESHOLD})")

        if not overlaps:
            log("[*] No overlaps to fix, exiting")
        else:
            # Group by parent for reporting
            by_parent = {}
            for overlap in overlaps:
                parent = overlap["parent_addr"]
                if parent not in by_parent:
                    by_parent[parent] = []
                by_parent[parent].append(overlap)

            log(f"[*] Overlaps in {len(by_parent)} parent functions")

            # Process each overlap
            success_count = 0
            skipped_count = 0
            failed_count = 0
            rollback_count = 0

            for overlap in overlaps:
                parent_addr = overlap["parent_addr"]
                split_addr = overlap["split_addr"]
                parent_name = overlap["parent_name"]
                confidence = overlap["confidence"]

                log(f"\n[*] Processing: 0x{parent_addr:08X} {parent_name}")
                log(f"    Split point: 0x{split_addr:08X} (confidence: {confidence:.2f})")

                is_success, msg = fix_boundary_overlap(
                    parent_addr, split_addr, log, dry_run=dry_run
                )

                log(f"    {msg}")

                if is_success:
                    if "[DRY-RUN]" in msg:
                        skipped_count += 1
                    elif "[SUCCESS]" in msg:
                        success_count += 1
                        # Apply PDB name to new function if available
                        if split_addr in pdb_names:
                            pdb_name = pdb_names[split_addr]
                            safe_name = sanitize_name(pdb_name)
                            try:
                                ida_name.set_name(split_addr, safe_name,
                                                ida_name.SN_NOWARN | ida_name.SN_NOCHECK)
                                log(f"    Named: {safe_name}")
                            except Exception as e:
                                log(f"    [!] Failed to name: {e}")
                else:
                    if "rolled back" in msg or "ROLLBACK" in msg:
                        rollback_count += 1
                    else:
                        failed_count += 1

            # Summary
            log("\n" + "=" * 70)
            log("[*] Fix Boundaries Summary:")
            log(f"  Total processed: {len(overlaps)}")
            log(f"  Successful: {success_count}")
            log(f"  Dry-run (skipped): {skipped_count}")
            log(f"  Failed: {failed_count}")
            log(f"  Rollbacks: {rollback_count}")

            # Save database if we made changes
            if not dry_run and success_count > 0:
                log("[*] Saving database...")
                ida_auto.auto_wait()
                idc.save_database(idc.get_idb_path(), 0)
                log("[*] Database saved")

    except Exception as e:
        log(f"[!] Fatal error: {e}")
        log(traceback.format_exc())

    # Write log file
    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    print(f"\n[*] Log written to: {LOG_FILE}")

    # Standard exit pattern
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except Exception:
            pass


if __name__ == '__main__':
    main()
