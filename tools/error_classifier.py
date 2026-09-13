#!/usr/bin/env python3
"""Error Classification Tool for PAL3 Decompilation Pipeline.

Analyzes failed compilation files and classizes errors by root cause:
- annotation_fix: fixable via annotation changes (type errors, missing members)
- codegen_fix: fixable via codegen changes (ptr→ref, operator new cast)
- hexrays_limit: Hex-Rays decompilation quality issues (syntax errors, lost params)
- manual_idb: needs manual IDB investigation (missing vtable methods, struct layout)

Usage:
    python3 tools/error_classifier.py [--json] [--summary]
"""

import json
import os
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
PROBE_FILE = PROJECT_ROOT / "data" / "status" / "probe_census.json"
OUTPUT_FILE = PROJECT_ROOT / "data" / "status" / "error_classification.json"

# Error classification rules
# Format: (code, msg_pattern) → (category, description)
RULES = [
    # === annotation_fix ===
    ("C2440", r"cannot convert from.*to.*unsigned long", "annotation_fix",
     "Pointer→unsigned long: struct member type annotation error"),
    ("C2440", r"cannot convert from.*char\s*\*.*to.*char\s*\*", "annotation_fix",
     "char* type mismatch: annotation type error"),
    ("C2039", r"is not a member of", "annotation_fix",
     "Missing member: struct annotation incomplete"),
    ("C2511", r"overloaded member function.*not found", "annotation_fix",
     "Wrong function signature: annotation method type error"),
    ("C2679", r"no operator defined.*takes.*right-hand operand", "annotation_fix",
     "Missing operator: struct needs operator overload"),

    # === codegen_fix ===
    ("C2664", r"cannot convert parameter.*from.*\*.*to.*&", "codegen_fix",
     "Ptr→ref: codegen needs * dereference for reference params"),
    ("C2664", r"cannot convert parameter.*from.*to.*const.*&", "codegen_fix",
     "Ptr→const ref: codegen needs * dereference"),
    ("C2273", r"function-style cast.*illegal.*right side of", "codegen_fix",
     "Function-style cast after '.': Hex-Rays artifact"),
    ("C2100", r"illegal indirection", "codegen_fix",
     "Illegal indirection: Hex-Rays pointer artifact"),
    ("C2106", r"left operand", "codegen_fix",
     "Left operand error: Hex-Rays expression artifact"),

    # === hexrays_limit ===
    ("C2059", r"syntax error.*\)", "hexrays_limit",
     "Syntax error ')': Hex-Rays lost expression context"),
    ("C2059", r"syntax error.*\}", "hexrays_limit",
     "Syntax error '}': Hex-Rays lost block context"),
    ("C2059", r"syntax error.*this", "hexrays_limit",
     "Syntax error 'this': Hex-Rays this pointer issue"),
    ("C2660", r"function does not take.*parameters", "hexrays_limit",
     "Wrong param count: Hex-Rays lost parameter info"),
    ("C2660", r"no overloaded function takes", "hexrays_limit",
     "No matching overload: Hex-Rays type inference error"),
    ("C2065", r"undeclared identifier", "hexrays_limit",
     "Undeclared identifier: Hex-Rays missed declaration"),
    ("C2228", r"left of.*must have class", "hexrays_limit",
     "Left of '.' not class: Hex-Rays type confusion"),
    ("C2227", r"left of.*must point to class", "hexrays_limit",
     "Left of '->' not class: Hex-Rays pointer type error"),
    ("C2676", r"does not define this operator", "hexrays_limit",
     "Missing operator: Hex-Rays needs operator[] etc."),
    ("C2040", r"differs in levels of indirection", "hexrays_limit",
     "Indirection mismatch: Hex-Rays pointer level error"),
    ("C2102", r"requires l-value", "hexrays_limit",
     "L-value required: Hex-Rays expression artifact"),
    ("C2109", r"subscript requires array or pointer", "hexrays_limit",
     "Subscript error: Hex-Rays array/pointer confusion"),
    ("C2882", r"illegal use of namespace", "hexrays_limit",
     "Namespace error: Hex-Rays namespace confusion"),
    ("C2784", r"could not deduce", "hexrays_limit",
     "Template deduction: Hex-Rays template limitation"),
    ("C2143", r"syntax error.*missing", "hexrays_limit",
     "Missing syntax: Hex-Rays structural error"),
    ("C2512", r"no appropriate default constructor", "hexrays_limit",
     "No constructor: Hex-Rays object creation issue"),
    ("C2198", r"too few actual parameters", "hexrays_limit",
     "Too few params: Hex-Rays lost arguments"),
    ("C2440", r"cannot convert", "annotation_fix",
     "Type conversion: annotation type mismatch"),
    ("C2664", r"cannot convert parameter", "codegen_fix",
     "Param conversion: codegen type mismatch or ptr→ref"),
    ("C2660", r"function does not take", "hexrays_limit",
     "Wrong param count: Hex-Rays lost parameter info"),
    ("C2065", r"undeclared identifier", "hexrays_limit",
     "Undeclared: missing declaration or Hex-Rays artifact"),
    ("C2059", r"syntax error", "hexrays_limit",
     "Syntax error: Hex-Rays structural artifact"),
    ("C2143", r"syntax error", "hexrays_limit",
     "Syntax error: Hex-Rays structural artifact"),
    ("C2100", r"illegal indirection", "codegen_fix",
     "Illegal indirection: Hex-Rays pointer artifact"),
    ("C2106", r"left operand", "codegen_fix",
     "Left operand error: Hex-Rays expression artifact"),
    ("C2274", r"function-style cast", "codegen_fix",
     "Function-style cast: Hex-Rays artifact"),
    ("C2227", r"left of.*must point to class", "hexrays_limit",
     "Left of '->' not class: Hex-Rays pointer type error"),
    ("C2661", r"no overloaded function", "hexrays_limit",
     "No matching overload: Hex-Rays type inference"),
    ("C2679", r"no operator defined", "annotation_fix",
     "Missing operator: struct needs operator overload"),
    ("C2676", r"does not define this operator", "hexrays_limit",
     "Missing operator: Hex-Rays needs operator[] etc."),
    ("C2385", r"ambiguous", "manual_idb",
     "Ambiguous access: inheritance diamond issue"),
    ("C2501", r"missing storage-class", "hexrays_limit",
     "Missing type: Hex-Rays declaration error"),
    ("C2040", r"differs in levels of indirection", "hexrays_limit",
     "Indirection mismatch: Hex-Rays pointer level error"),
    ("C2102", r"requires l-value", "hexrays_limit",
     "L-value required: Hex-Rays expression artifact"),
    ("C2109", r"subscript requires array or pointer", "hexrays_limit",
     "Subscript error: Hex-Rays array/pointer confusion"),
    ("C2882", r"illegal use of namespace", "hexrays_limit",
     "Namespace error: Hex-Rays namespace confusion"),
    ("C2079", r"uses undefined class", "manual_idb",
     "Undefined class: IDB type issue"),

    # === manual_idb ===
    ("C2584", r"direct base.*is inaccessible", "manual_idb",
     "Inaccessible base: inheritance access issue"),
    ("C2011", r"redefinition.*different basic types", "manual_idb",
     "Type redefinition: IDB type conflict"),
    ("C2555", r"overriding virtual function differs", "manual_idb",
     "Virtual override conflict: vtable layout issue"),
    ("C2913", r"explicit specialization.*not a class template", "manual_idb",
     "Template specialization: IDB template issue"),
    ("C4234", r"nonstandard extension.*__thiscall", "manual_idb",
     "__thiscall warning: MSVC6 keyword reservation"),
]


def classify_error(code, msg):
    """Classify a single error by its code and message."""
    for rule_code, pattern, category, description in RULES:
        if code == rule_code and re.search(pattern, msg):
            return category, description
    # Default: unknown
    return "unknown", f"Unclassified {code} error"


CASCADE_CODES = {"C2227", "C2228", "C2660", "C2653"}
_IDA_GLOBAL_PREFIX_RE = re.compile(r"^(?:a[A-Z]|dword_|byte_|word_|off_|unk_|qword_|flt_)")
# member name extractors per cascade code
_C2039_RE = re.compile(r"'(\w+)' : is not a member of")
_C2228_RE = re.compile(r"left of '\.\s*(\w+)'")
_C2227_RE = re.compile(r"left of '->\s*(\w+)'")
_C2660_RE = re.compile(r"'(\w+)' : (?:function does not take|no overloaded function)")


def _cascade_reclassify(details):
    """Cascade-aware pass.

    C2227/C2228/C2660/C2653 errors ride on unknown member types: when the
    file also reports a missing member (C2039), the object expression's
    type is unknown BECAUSE of that missing member, and the per-error rule
    set would misfile the cascade as a decompiler limit. The cascade message
    names the field being accessed (not the missing member), so exact
    member matching only works for direct forms; for the rest, file-level
    presence of C2039 is the pragmatic root-cause test (audit 2026-09-13:
    66/76 hexrays_limit-dominant files contain C2039 roots).

    C2065 undeclared identifiers matching IDA data-name patterns
    (aFooBar/dword_XXXX/...) are missing-global annotations, not
    decompiler limits.
    """
    has_missing_member = any(d["code"] == "C2039" for d in details)
    missing_members = set()
    for d in details:
        if d["code"] == "C2039":
            m = _C2039_RE.search(d["msg"])
            if m:
                missing_members.add(m.group(1))
    for d in details:
        if d["code"] in CASCADE_CODES and d["category"] == "hexrays_limit" \
                and has_missing_member:
            m = (_C2228_RE.search(d["msg"]) or _C2227_RE.search(d["msg"])
                 or _C2660_RE.search(d["msg"]))
            member = m.group(1) if m else None
            if member is not None and member in missing_members:
                d["description"] = ("cascade of missing member '%s' (C2039 same file)"
                                    % member)
            else:
                d["description"] = "cascade of unknown member type (C2039 in file)"
            d["category"] = "annotation_fix"
        elif d["code"] == "C2065" and d["category"] == "hexrays_limit":
            m = re.search(r"'([^']+)'", d["msg"])
            if m and _IDA_GLOBAL_PREFIX_RE.match(m.group(1)):
                d["category"] = "annotation_fix"
                d["description"] = "missing global declaration: %s not emitted" % m.group(1)
    return details


def classify_file(file_errors):
    """Classify all errors in a file. Return dominant category."""
    categories = Counter()
    details = []
    for err in file_errors:
        code = err.get("code", "")
        msg = err.get("msg", "")
        cat, desc = classify_error(code, msg)
        categories[cat] += 1
        details.append({
            "code": code,
            "msg": msg[:100],
            "category": cat,
            "description": desc,
        })
    details = _cascade_reclassify(details)
    categories = Counter(d["category"] for d in details)
    # Dominant category
    if categories:
        dominant = categories.most_common(1)[0][0]
    else:
        dominant = "unknown"
    return dominant, categories, details


def main():
    import argparse
    parser = argparse.ArgumentParser(description="Classify compilation errors by root cause")
    parser.add_argument("--json", action="store_true", help="Output JSON report")
    parser.add_argument("--summary", action="store_true", help="Show summary only")
    args = parser.parse_args()

    if not PROBE_FILE.exists():
        print(f"Error: {PROBE_FILE} not found. Run probe_compile.py first.")
        sys.exit(1)

    with open(PROBE_FILE) as f:
        data = json.load(f)

    results = []
    category_counts = Counter()
    category_files = defaultdict(list)

    for file_info in data.get("s2", {}).get("results", []):
        if file_info.get("status") != "fail":
            continue

        unit = file_info.get("unit", "")
        errors = file_info.get("errors", [])
        if not errors:
            continue

        dominant, categories, details = classify_file(errors)
        category_counts[dominant] += 1
        category_files[dominant].append(unit)

        results.append({
            "unit": unit,
            "dominant_category": dominant,
            "error_count": len(errors),
            "categories": dict(categories),
            "details": details,
        })

    # Save JSON report
    report = {
        "total_files": len(results),
        "category_counts": dict(category_counts),
        "category_files": {k: v for k, v in category_files.items()},
        "files": results,
    }
    OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(OUTPUT_FILE, "w") as f:
        json.dump(report, f, indent=2, ensure_ascii=False)

    # Print summary
    print(f"Error Classification Report")
    print(f"{'='*50}")
    print(f"Total failed files: {len(results)}")
    print()
    print("Category Distribution:")
    for cat in ["annotation_fix", "codegen_fix", "hexrays_limit", "manual_idb", "unknown"]:
        count = category_counts.get(cat, 0)
        pct = 100 * count / len(results) if results else 0
        print(f"  {cat:20s}: {count:4d} ({pct:5.1f}%)")
    print()

    if not args.summary:
        print("Sample files per category:")
        for cat in ["annotation_fix", "codegen_fix", "hexrays_limit", "manual_idb", "unknown"]:
            files = category_files.get(cat, [])
            print(f"\n  {cat} ({len(files)} files):")
            for f in files[:5]:
                print(f"    - {f}")
            if len(files) > 5:
                print(f"    ... and {len(files)-5} more")

    print(f"\nFull report saved to: {OUTPUT_FILE}")


if __name__ == "__main__":
    main()
