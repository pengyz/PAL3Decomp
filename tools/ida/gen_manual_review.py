#!/usr/bin/env python3
"""
Manual Review Report Generator for PAL3A IDA Quality Diagnosis

Reads diagnosis_report.json and generates a human-readable Markdown report
for manual review of flagged functions.

This is a standalone script (NOT IDAPython) that runs outside IDA.

Output: _logs/manual_review_YYYYMMDD.md
"""

import sys
import os
import json
from datetime import datetime

# ============================================================================
# Constants
# ============================================================================

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
DIAGNOSIS_REPORT = os.path.join(LOG_DIR, "diagnosis_report.json")

# Category mappings for manual review items
LABEL_CATEGORIES = {
    "BOUNDARY_OVERLAP": "Boundary Unclear",
    "UNPACK_ARTIFACT": "Possible Unpack Damage",
    "SP_CORRUPT": "SP Analysis Failures",
    "USERPURGE_WRONG": "Calling Convention Issues",
    "STRUCT_NEEDED": "Missing Struct Definitions",
}

MAX_ITEMS_PER_SECTION = 50

# ============================================================================
# Helper Functions
# ============================================================================


def load_diagnosis_report(report_path):
    """
    Load diagnosis_report.json

    Returns:
        (report_dict, success: bool, error_msg: str)
    """
    if not os.path.exists(report_path):
        return None, False, f"Report not found: {report_path}"

    try:
        with open(report_path, "r", encoding="utf-8-sig") as f:
            report = json.load(f)
        return report, True, None
    except json.JSONDecodeError as e:
        return None, False, f"Invalid JSON: {e}"
    except Exception as e:
        return None, False, f"Error reading report: {e}"


def categorize_manual_review_items(manual_review_list):
    """
    Categorize manual review items by label.

    Args:
        manual_review_list: List of dicts from report["manual_review"]

    Returns:
        dict: {category_name: [items]}
    """
    categories = {}

    for item in manual_review_list:
        label = item.get("label", "UNKNOWN")
        category = LABEL_CATEGORIES.get(label, label)

        if category not in categories:
            categories[category] = []

        categories[category].append(item)

    return categories


def find_eh_funclets(functions_dict):
    """
    Find EH_FUNCLET functions with low confidence (< 0.8).

    Args:
        functions_dict: Dict from report["functions"]

    Returns:
        list: [{"addr": "0x...", "name": "...", "confidence": 0.X, "details": {...}}]
    """
    ambiguous_funclets = []

    for addr_str, func_info in functions_dict.items():
        labels = func_info.get("labels", [])

        for label_entry in labels:
            if isinstance(label_entry, (list, tuple)) and len(label_entry) >= 3:
                label, confidence, details = label_entry[0], label_entry[1], label_entry[2]
            else:
                continue

            if label == "EH_FUNCLET" and confidence < 0.8:
                ambiguous_funclets.append({
                    "addr": addr_str,
                    "name": func_info.get("name", "???"),
                    "confidence": confidence,
                    "size": func_info.get("ida_size", 0),
                    "details": details
                })

    # Sort by confidence ascending (lowest first)
    ambiguous_funclets.sort(key=lambda x: x["confidence"])

    return ambiguous_funclets


def format_evidence_from_item(item):
    """
    Extract human-readable evidence from a manual review item.

    Args:
        item: Single manual review item dict

    Returns:
        str: Evidence description
    """
    reason = item.get("reason", "")
    if reason:
        return reason

    # Fallback: construct from other fields
    label = item.get("label", "")
    conf = item.get("confidence", 0)
    return f"(label={label}, conf={conf:.2f})"


def render_section(title, items, category_description=""):
    """
    Render a single Markdown section.

    Args:
        title: Section heading
        items: List of dicts with addr, name, details
        category_description: Optional description paragraph

    Returns:
        str: Markdown text
    """
    if not items:
        return ""

    lines = []
    lines.append(f"\n## {title} ({len(items)} functions)\n")

    if category_description:
        lines.append(category_description)
        lines.append("")

    # Show up to MAX_ITEMS_PER_SECTION items
    shown_items = items[:MAX_ITEMS_PER_SECTION]
    truncated_count = len(items) - len(shown_items)

    for item in shown_items:
        addr = item.get("address", item.get("addr", "0x???"))
        name = item.get("name", "???")
        conf = item.get("confidence", 0)
        reason = item.get("reason", "")
        details = item.get("details", {})

        # Build summary line
        evidence_str = reason or ""
        if not evidence_str:
            # Try to extract from details
            if isinstance(details, dict):
                if "evidence" in details:
                    evidence_str = ", ".join(details["evidence"]) if isinstance(details["evidence"], list) else str(details["evidence"])
                elif "overlap_bytes" in details:
                    evidence_str = f"overlap_bytes={details['overlap_bytes']}, next_pdb={details.get('next_pdb_addr', '?')}"
                elif "missing_frame" in details:
                    evidence_str = "missing_frame_pointer"
                elif "class" in details:
                    evidence_str = f"class={details['class']}"

        line = f"- `{addr}` **{name}** — conf={conf:.2f}"
        if evidence_str:
            line += f", {evidence_str}"
        lines.append(line)

    if truncated_count > 0:
        lines.append(f"\n... and {truncated_count} more ({len(items)} total)")

    lines.append("")

    return "\n".join(lines)


def render_eh_funclets_section(funclets):
    """
    Render EH funclets section with specific format.

    Args:
        funclets: List of EH funclet dicts

    Returns:
        str: Markdown text
    """
    if not funclets:
        return ""

    lines = []
    lines.append(f"\n## Ambiguous EH Funclets ({len(funclets)} functions)\n")
    lines.append("These might be EH funclets or might be real functions. Low confidence classification.\n")

    shown_items = funclets[:MAX_ITEMS_PER_SECTION]
    truncated_count = len(funclets) - len(shown_items)

    for item in shown_items:
        addr = item.get("addr", "0x???")
        name = item.get("name", "???")
        conf = item.get("confidence", 0)
        size = item.get("size", 0)
        details = item.get("details", {})

        # Check for jumpout evidence
        jumpout = False
        evidence = details.get("evidence", [])
        if isinstance(evidence, list):
            jumpout = any("jumpout" in str(e) for e in evidence)

        line = f"- `{addr}` **{name}** — conf={conf:.2f}, size={size}B, jumpout={jumpout}"
        lines.append(line)

    if truncated_count > 0:
        lines.append(f"\n... and {truncated_count} more ({len(funclets)} total)")

    lines.append("")

    return "\n".join(lines)


def generate_report(report, output_path):
    """
    Generate Markdown report from diagnosis data.

    Args:
        report: Loaded diagnosis report dict
        output_path: Path to write Markdown to

    Returns:
        bool: Success
    """
    now = datetime.now()
    timestamp = now.strftime("%Y-%m-%d %H:%M:%S")

    lines = []
    lines.append("# PAL3A Manual Review Report\n")
    lines.append(f"Generated: {timestamp}\n")

    # Get data
    manual_review = report.get("manual_review", [])
    functions_dict = report.get("functions", {})
    summary = report.get("summary", {})

    total_items = len(manual_review)
    lines.append(f"Total items needing review: {total_items}\n")

    if total_items == 0:
        lines.append("✓ No manual review items found. All functions classified cleanly.\n")
        output_text = "\n".join(lines)
    else:
        # Categorize manual review items
        categories = categorize_manual_review_items(manual_review)

        # Render sections for each category (in order of LABEL_CATEGORIES)
        for label, category_name in LABEL_CATEGORIES.items():
            if category_name in categories:
                items = categories[category_name]
                description = ""

                if label == "BOUNDARY_OVERLAP":
                    description = "These functions have overlapping boundaries but the split point could not be verified."
                elif label == "UNPACK_ARTIFACT":
                    description = "These functions are located outside PE sections, possibly from unpack damage or analysis errors."
                elif label == "SP_CORRUPT":
                    description = "Stack pointer analysis failed for these functions (missing frame pointer or frame data)."
                elif label == "USERPURGE_WRONG":
                    description = "These functions have __userpurge/__usercall calling conventions that may need correction."
                elif label == "STRUCT_NEEDED":
                    description = "These class methods need struct definitions to be properly analyzed."

                section_text = render_section(category_name, items, description)
                lines.append(section_text)

        # Find and render ambiguous EH funclets
        funclets = find_eh_funclets(functions_dict)
        if funclets:
            funclet_section = render_eh_funclets_section(funclets)
            lines.append(funclet_section)

        output_text = "\n".join(lines)

    # Write output
    try:
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        with open(output_path, "w", encoding="utf-8") as f:
            f.write(output_text)
        return True
    except Exception as e:
        print(f"Error writing output: {e}", file=sys.stderr)
        return False


# ============================================================================
# Main
# ============================================================================

def main():
    print("=" * 80)
    print("PAL3A Manual Review Report Generator")
    print("=" * 80)

    # Load diagnosis report
    print(f"\nReading: {DIAGNOSIS_REPORT}")
    report, success, error = load_diagnosis_report(DIAGNOSIS_REPORT)

    if not success:
        print(f"ERROR: {error}", file=sys.stderr)
        return 1

    print(f"[OK] Loaded diagnosis report")

    # Generate output filename
    now = datetime.now()
    date_str = now.strftime("%Y%m%d")
    output_filename = f"manual_review_{date_str}.md"
    output_path = os.path.join(LOG_DIR, output_filename)

    print(f"Generating report...")

    # Generate report
    success = generate_report(report, output_path)
    if not success:
        print("ERROR: Failed to generate report", file=sys.stderr)
        return 1

    # Print summary
    manual_review = report.get("manual_review", [])
    functions_dict = report.get("functions", {})
    summary = report.get("summary", {})

    print(f"\n[OK] Report written to: {output_path}")

    print("\n" + "=" * 80)
    print("SUMMARY")
    print("=" * 80)

    print(f"Total unique functions: {summary.get('total_unique_functions', '?')}")
    print(f"Items needing manual review: {len(manual_review)}")

    # Count EH funclets with low confidence
    ambiguous_funclets = find_eh_funclets(functions_dict)
    if ambiguous_funclets:
        print(f"Ambiguous EH funclets (conf < 0.8): {len(ambiguous_funclets)}")

    # Show category breakdown
    if manual_review:
        categories = categorize_manual_review_items(manual_review)
        print("\nManual review breakdown:")
        for category in LABEL_CATEGORIES.values():
            if category in categories:
                print(f"  {category:40s}: {len(categories[category]):3d}")

    print("\n" + "=" * 80)
    print("Report generation complete!")
    print("=" * 80)

    return 0


if __name__ == "__main__":
    sys.exit(main())
