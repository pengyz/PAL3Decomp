"""
IDAPython Phase 1: Diagnostic Engine for PAL3A Quality Classification

Classifies all functions in the IDA database and generates a comprehensive
JSON report for the quality fix pipeline.

Classification Labels:
  - EH_FUNCLET: Exception handler funclets ($E, $L)
  - BOUNDARY_OVERLAP: Function extends beyond next PDB function
  - UNPACK_ARTIFACT: Function outside PE sections
  - SP_CORRUPT: Stack pointer analysis failed
  - USERPURGE_WRONG: __userpurge/__usercall calling convention issues
  - STRUCT_NEEDED: Class method needing struct definitions
  - CLEAN: No issues detected

Output: _logs/diagnosis_report.json
"""

import sys
import os
import json
import bisect
import builtins
import re
from datetime import datetime

# IDA imports
import idc
import idaapi
import idautils
import ida_funcs
import ida_ua
import ida_allins
import ida_bytes
import ida_name

# Add tools/ida to path for ida_common
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SCRIPT_DIR)

import ida_common

# ============================================================================
# Constants
# ============================================================================

SCRIPT_VERSION = "1.0"
PROGRESS_INTERVAL = 2000

# Standard library classes and templates to exclude from STRUCT_NEEDED
STD_PREFIXES = (
    "std::", "ATL::", "WTL::", "_com_", "__", "CComPtr", "CComObject",
    "basic_string", "basic_iostream", "allocator", "char_traits"
)

# ============================================================================
# Helper Functions
# ============================================================================

def load_pdb_data():
    """Load PDB export JSON and build lookup structures"""
    print(f"Loading PDB data from: {ida_common.PDB_EXPORT}")

    with open(ida_common.PDB_EXPORT, "r", encoding="utf-8") as f:
        pdb_data = json.load(f)

    # Build address -> function map
    addr_to_func = {}
    for func in pdb_data.get("functions", []):
        addr = int(func["address"], 16)
        addr_to_func[addr] = func

    # Build sorted list of .text addresses for bisect
    text_addrs = sorted([addr for addr in addr_to_func.keys()
                         if ida_common.is_in_text(addr)])

    # Build set of class names (excluding std/system classes)
    class_names = set()
    for func in pdb_data.get("functions", []):
        cls = func.get("class", "")
        if cls and not any(cls.startswith(prefix) for prefix in STD_PREFIXES):
            class_names.add(cls)

    print(f"Loaded {len(addr_to_func)} PDB functions")
    print(f"Found {len(text_addrs)} .text addresses")
    print(f"Found {len(class_names)} non-std classes")

    return pdb_data, addr_to_func, text_addrs, class_names


def get_all_ida_functions():
    """Get all unique IDA functions, deduplicated by address"""
    print("Enumerating IDA functions...")

    addr_to_name = {}
    for func_addr in idautils.Functions():
        func_name = ida_name.get_name(func_addr)

        # Deduplicate by address
        if func_addr in addr_to_name:
            # Keep PDB name over sub_ name
            existing_name = addr_to_name[func_addr]
            if existing_name.startswith("sub_") and not func_name.startswith("sub_"):
                addr_to_name[func_addr] = func_name
        else:
            addr_to_name[func_addr] = func_name

    print(f"Found {len(addr_to_name)} unique functions")
    return addr_to_name


def is_eh_funclet_name(name):
    """Check if name matches exception handler funclet pattern"""
    return bool(re.match(r'\$[EL]\d+', name))


def count_eh_funclet_criteria(addr, func_name, func_size):
    """
    Count how many EH funclet criteria are met.

    Returns (criteria_count, evidence_list)
    """
    criteria = 0
    evidence = []

    # Criterion (a): JUMPOUT to parent function
    # Detect if function ends with jmp to another address
    func = ida_funcs.get_func(addr)
    if func:
        end_addr = func.end_ea
        # Check last few instructions for jmp
        check_addr = max(addr, end_addr - 20)
        while check_addr < end_addr:
            insn = ida_ua.insn_t()
            if ida_ua.decode_insn(insn, check_addr) > 0:
                if insn.itype == ida_allins.NN_jmp:
                    criteria += 1
                    evidence.append(f"jumpout at 0x{check_addr:08X}")
                    break
                check_addr += insn.size
            else:
                check_addr += 1

    # Criterion (b): size < 64 bytes
    if func_size < 64:
        criteria += 1
        evidence.append(f"size={func_size} < 64")

    # Criterion (c): outside .text
    if not ida_common.is_in_text(addr):
        criteria += 1
        evidence.append(f"outside .text (0x{addr:08X})")

    # Criterion (d): tiny with indirect jumps
    if func_size < 32:
        # Check for indirect jumps in tiny functions
        check_addr = addr
        while check_addr < addr + func_size:
            insn = ida_ua.insn_t()
            if ida_ua.decode_insn(insn, check_addr) > 0:
                if insn.itype in (ida_allins.NN_jmp, ida_allins.NN_call):
                    # Check if indirect (operand type is register or memory)
                    if insn.Op1.type in (ida_ua.o_reg, ida_ua.o_phrase, ida_ua.o_displ):
                        criteria += 1
                        evidence.append(f"tiny + indirect jmp/call")
                        break
                check_addr += insn.size
            else:
                check_addr += 1

    return criteria, evidence


def classify_eh_funclet(addr, func_name, func_size):
    """
    Classify potential EH funclet.

    Returns (is_funclet, confidence, evidence_dict) or None if not a funclet
    """
    # Strict name check first
    if not is_eh_funclet_name(func_name):
        return None

    criteria_count, evidence = count_eh_funclet_criteria(addr, func_name, func_size)

    # Confidence based on criteria count
    if criteria_count >= 3:
        confidence = 0.95
    elif criteria_count >= 2:
        confidence = 0.75
    elif func_size < 200:
        # Name match + reasonable size
        confidence = 0.6
    else:
        # Name match but large function - suspicious
        confidence = 0.4

    details = {
        "criteria_met": criteria_count,
        "evidence": evidence,
        "size": func_size
    }

    return (True, confidence, details)


def find_next_pdb_addr(addr, text_addrs):
    """Find next PDB function address after given address using bisect"""
    idx = bisect.bisect_right(text_addrs, addr)
    if idx < len(text_addrs):
        return text_addrs[idx]
    return None


def classify_boundary_overlap(addr, func, text_addrs):
    """
    Check if function overlaps with next PDB-known function.

    Returns (has_overlap, confidence, evidence_dict) or None if no overlap
    """
    func_end = func.end_ea
    next_addr = find_next_pdb_addr(addr, text_addrs)

    if next_addr is None:
        return None

    if func_end > next_addr:
        # Overlap detected - check if split point is valid
        is_valid, evidence_str = ida_common.is_valid_split_point(next_addr)

        confidence = 0.95 if is_valid else 0.4

        details = {
            "func_end": f"0x{func_end:08X}",
            "next_pdb_addr": f"0x{next_addr:08X}",
            "overlap_bytes": func_end - next_addr,
            "valid_split": is_valid,
            "split_evidence": evidence_str
        }

        return (True, confidence, details)

    return None


def classify_sp_corrupt(addr):
    """
    Check if function has stack pointer corruption issues.

    Returns (is_corrupt, confidence, evidence_dict) or None if clean
    """
    func = ida_funcs.get_func(addr)
    if not func:
        return None

    flags = idc.get_func_attr(addr, idc.FUNCATTR_FLAGS)
    if flags == idc.BADADDR:
        return None

    # Check for SP analysis failure indicators
    # FUNC_NORET (0x01): function doesn't return
    # FUNC_FAR (0x02): far function
    # FUNC_USERFAR (0x04): user far function
    # FUNC_STATICDEF (0x08): static function
    # FUNC_FRAME (0x10): function has frame pointer - if NOT set, suspicious
    # FUNC_BOTTOMBP (0x20): BP points to bottom of frame

    has_frame = bool(flags & 0x10)

    if not has_frame:
        # Missing frame pointer - potential SP corruption
        details = {
            "flags": f"0x{flags:04X}",
            "missing_frame": True
        }
        return (True, 0.7, details)

    return None


def classify_userpurge_wrong(addr, addr_to_func):
    """
    Check for __userpurge/__usercall calling convention issues.

    Returns (has_issue, confidence, evidence_dict) or None if clean
    """
    # Get function type string from IDA (idc.get_type works in IDA 9.x)
    type_str = idc.get_type(addr)
    if not type_str:
        return None

    # Check for userpurge/usercall
    if "__userpurge" not in type_str and "__usercall" not in type_str:
        return None

    # Check if PDB has a proper signature
    pdb_func = addr_to_func.get(addr)
    has_pdb_sig = bool(pdb_func and pdb_func.get("mangled_name"))

    confidence = 0.9 if has_pdb_sig else 0.6

    details = {
        "ida_type": type_str,
        "has_pdb_signature": has_pdb_sig
    }

    if pdb_func:
        details["pdb_name"] = pdb_func.get("name", "")

    return (True, confidence, details)


def classify_struct_needed(addr, addr_to_func, class_names):
    """
    Check if function is a class method needing struct definitions.

    Returns (needs_struct, confidence, evidence_dict) or None if not applicable
    """
    pdb_func = addr_to_func.get(addr)
    if not pdb_func:
        return None

    cls = pdb_func.get("class", "")
    if not cls:
        return None

    # Exclude standard library and system classes
    if any(cls.startswith(prefix) for prefix in STD_PREFIXES):
        return None

    # Check if it's in our known classes set
    if cls not in class_names:
        return None

    details = {
        "class": cls,
        "method": pdb_func.get("name", "")
    }

    return (True, 0.8, details)


def classify_function(addr, func_name, addr_to_func, text_addrs, class_names):
    """
    Classify a single function and return all applicable labels.

    Returns list of (label, confidence, details) tuples
    """
    labels = []

    func = ida_funcs.get_func(addr)
    if not func:
        return labels

    func_size = func.end_ea - func.start_ea

    # Check UNPACK_ARTIFACT first (early return)
    if not ida_common.is_in_pe(addr):
        labels.append(("UNPACK_ARTIFACT", 0.99, {
            "address": f"0x{addr:08X}",
            "reason": "outside PE sections"
        }))
        return labels

    # Check EH_FUNCLET (early return if high confidence)
    eh_result = classify_eh_funclet(addr, func_name, func_size)
    if eh_result:
        is_funclet, confidence, details = eh_result
        if is_funclet:
            labels.append(("EH_FUNCLET", confidence, details))
            if confidence >= 0.75:
                return labels

    # Check BOUNDARY_OVERLAP
    overlap_result = classify_boundary_overlap(addr, func, text_addrs)
    if overlap_result:
        has_overlap, confidence, details = overlap_result
        if has_overlap:
            labels.append(("BOUNDARY_OVERLAP", confidence, details))

    # Check SP_CORRUPT
    sp_result = classify_sp_corrupt(addr)
    if sp_result:
        is_corrupt, confidence, details = sp_result
        if is_corrupt:
            labels.append(("SP_CORRUPT", confidence, details))

    # Check USERPURGE_WRONG
    userpurge_result = classify_userpurge_wrong(addr, addr_to_func)
    if userpurge_result:
        has_issue, confidence, details = userpurge_result
        if has_issue:
            labels.append(("USERPURGE_WRONG", confidence, details))

    # Check STRUCT_NEEDED
    struct_result = classify_struct_needed(addr, addr_to_func, class_names)
    if struct_result:
        needs_struct, confidence, details = struct_result
        if needs_struct:
            labels.append(("STRUCT_NEEDED", confidence, details))

    # If no labels, mark as CLEAN
    if not labels:
        labels.append(("CLEAN", 1.0, {}))

    return labels


def build_report(addr_to_name, classifications, duplicates):
    """Build comprehensive JSON report"""

    # Count by label
    by_label = {}
    auto_fixable = 0
    manual_review_list = []

    for addr, labels in classifications.items():
        func_name = addr_to_name[addr]

        for label, confidence, details in labels:
            if label not in by_label:
                by_label[label] = 0
            by_label[label] += 1

            # Track auto-fixable (high confidence, not CLEAN)
            if confidence >= ida_common.CONF_AUTO_FIX and label != "CLEAN":
                auto_fixable += 1

            # Track manual review (medium confidence)
            if (ida_common.CONF_MANUAL_REVIEW <= confidence < ida_common.CONF_AUTO_FIX
                and label != "CLEAN"):
                manual_review_list.append({
                    "address": f"0x{addr:08X}",
                    "name": func_name,
                    "label": label,
                    "confidence": confidence,
                    "reason": details.get("evidence", details.get("reason", ""))
                })

    # Build summary
    summary = {
        "total_unique_functions": len(addr_to_name),
        "by_label": by_label,
        "auto_fixable": auto_fixable,
        "needs_manual_review": len(manual_review_list),
        "duplicates": duplicates
    }

    # Build functions dict
    functions_dict = {}
    for addr, labels in classifications.items():
        func_name = addr_to_name[addr]
        func = ida_funcs.get_func(addr)
        func_size = func.end_ea - func.start_ea if func else 0

        functions_dict[f"0x{addr:08X}"] = {
            "name": func_name,
            "ida_size": func_size,
            "labels": [[label, confidence, details] for label, confidence, details in labels]
        }

    # Build metadata
    meta = {
        "ida_db": idc.get_idb_path(),
        "script_version": SCRIPT_VERSION,
        "timestamp": datetime.now().isoformat(),
        "pe_sections": {
            "text": {"start": f"0x{ida_common.TEXT_START:08X}",
                    "end": f"0x{ida_common.TEXT_END:08X}"},
            "rdata": {"start": f"0x{ida_common.RDATA_START:08X}",
                     "end": f"0x{ida_common.RDATA_END:08X}"},
            "data": {"start": f"0x{ida_common.DATA_START:08X}",
                    "end": f"0x{ida_common.DATA_END:08X}"}
        }
    }

    report = {
        "meta": meta,
        "summary": summary,
        "functions": functions_dict,
        "manual_review": manual_review_list
    }

    return report


# ============================================================================
# Main Execution
# ============================================================================

def main():
    """Main diagnostic engine entry point"""
    print("=" * 80)
    print("PAL3A IDA Phase 1: Quality Diagnostic Engine")
    print("=" * 80)

    # Load PDB data
    pdb_data, addr_to_func, text_addrs, class_names = load_pdb_data()

    # Get all IDA functions
    addr_to_name = get_all_ida_functions()

    # Count duplicates (multiple names for same address)
    total_ida_funcs = sum(1 for _ in idautils.Functions())
    duplicates = total_ida_funcs - len(addr_to_name)
    print(f"Found {duplicates} duplicate addresses (PDB name overriding sub_)")

    # Classify all functions
    print("\nClassifying functions...")
    classifications = {}

    progress_count = 0
    for addr, func_name in sorted(addr_to_name.items()):
        labels = classify_function(addr, func_name, addr_to_func, text_addrs, class_names)
        classifications[addr] = labels

        progress_count += 1
        if progress_count % PROGRESS_INTERVAL == 0:
            print(f"  Processed {progress_count}/{len(addr_to_name)} functions...")

    print(f"  Processed {len(classifications)} functions (complete)")

    # Build report
    print("\nBuilding report...")
    report = build_report(addr_to_name, classifications, duplicates)

    # Write to JSON
    os.makedirs(ida_common.LOG_DIR, exist_ok=True)
    report_path = os.path.join(ida_common.LOG_DIR, "diagnosis_report.json")

    with open(report_path, "w", encoding="utf-8") as f:
        json.dump(report, f, indent=2)

    print(f"\nReport written to: {report_path}")

    # Print summary
    print("\n" + "=" * 80)
    print("SUMMARY")
    print("=" * 80)
    print(f"Total unique functions: {report['summary']['total_unique_functions']}")
    print(f"Auto-fixable (conf >= {ida_common.CONF_AUTO_FIX}): {report['summary']['auto_fixable']}")
    print(f"Needs manual review: {report['summary']['needs_manual_review']}")
    print(f"Duplicates: {report['summary']['duplicates']}")
    print("\nBy label:")
    for label, count in sorted(report['summary']['by_label'].items(), key=lambda x: -x[1]):
        print(f"  {label:20s}: {count:6d}")

    print("\n" + "=" * 80)
    print("Phase 1 diagnostic complete!")
    print("=" * 80)


if __name__ == "__main__":
    main()

    # Standard pipeline exit pattern
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        idc.qexit(0)
