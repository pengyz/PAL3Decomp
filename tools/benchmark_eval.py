#!/usr/bin/env python3
"""Benchmark function evaluation for PAL3 decompilation.

Evaluates a set of benchmark functions against gate metrics:
  1. Offset access count  (*(_DWORD*)(this + N))
  2. vtable bare dispatch (vfptr[N])
  3. void* / fnptr casts
  4. sub_/todo_/crt_sub_ references
  5. _gap_/_field_ member ratio
  6. Named member access ratio

Usage:
  python tools/benchmark_eval.py          # run all benchmarks (full report)
  python tools/benchmark_eval.py --json   # JSON output for CI
"""

import json
import os
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
SRC_DIR = PROJECT_ROOT / "src" / "pal3"
FUNCTIONS_ANN = PROJECT_ROOT / "data" / "annotations" / "functions.json"
STRUCTS_DIR = PROJECT_ROOT / "data" / "annotations" / "structs"

# ============================================================
# Benchmark definitions
# ============================================================
BENCHMARKS = [
    {
        "name": "CCBSystem::CombatUpdate",
        "addr": "0x00513060",
        "module": "Combat",
        "reason": "Combat main loop",
    },
    {
        "name": "CEffMgr::CreateEffect",
        "addr": "0x004CDCA0",
        "module": "Effect",
        "reason": "Effect creation dispatch",
    },
    {
        "name": "PalScriptMgr::ExecuteFrame",
        "addr": "0x0042F460",
        "module": "Script",
        "reason": "Script engine frame execution",
    },
    {
        "name": "RoleSystem::UpdateFollowerMovement",
        "addr": "0x0041A450",
        "module": "Role",
        "reason": "Follower movement logic",
    },
    {
        "name": "CCBRoleState::ProcessActions",
        "addr": "0x004F7910",
        "module": "Combat",
        "reason": "Combat role action processing",
    },
]


def find_decomp_json(name):
    """Find decomp JSON file by function name."""
    # Build search terms from name
    terms = name.replace("::", "_").replace(" ", "_")
    for f in DECOMP_DIR.glob(f"*.json"):
        try:
            with open(f, encoding="utf-8") as fh:
                d = json.load(fh)
            if d.get("name") == name:
                return d
        except (json.JSONDecodeError, OSError):
            continue
    return None


def find_generated_cpp(name, module):
    """Find the generated .cpp file for a class."""
    cls_name = name.split("::")[0]
    cpp_name = f"{cls_name}.cpp"
    for f in SRC_DIR.rglob(cpp_name):
        return f
    return None


def extract_function_code(cpp_path, name):
    """Extract a specific function body from generated .cpp."""
    if not cpp_path or not cpp_path.exists():
        return None
    content = cpp_path.read_text(encoding="utf-8")
    method_name = name.split("::", 1)[1].split("(")[0]
    # Find function definition: match from signature to matching brace
    cls = re.escape(name.split("::")[0])
    method = re.escape(method_name)
    # Find the function signature
    sig_pattern = re.compile(
        r"^" + cls + r"::" + method + r"\s*\([^)]*\)\s*\n\s*\{",
        re.MULTILINE,
    )
    sig_match = sig_pattern.search(content)
    if not sig_match:
        return None
    # From the opening brace, count depth to find closing brace
    start = sig_match.end() - 1  # position of '{'
    depth = 1
    i = start + 1
    while i < len(content) and depth > 0:
        if content[i] == '{':
            depth += 1
        elif content[i] == '}':
            depth -= 1
        i += 1
    if depth == 0:
        # From return type line to closing brace
        # Find the return type line (search backwards from sig_match)
        func_start = content.rfind('\n', 0, sig_match.start())
        if func_start == -1:
            func_start = 0
        else:
            func_start += 1  # skip the newline
        return content[func_start:i]
    return None


def count_metrics(name, code):
    """Count gate metrics for a function code string."""
    if not code:
        return None

    metrics = {}

    # 1. Offset access: *(_DWORD *)(this + 0xXXXX)
    metrics["offset_access"] = len(
        re.findall(r'\*\(_[A-Z0-9_]+\s*\*\)\(this\s*\+\s*0x[0-9A-Fa-f]+\)', code)
    )
    # Also catch: *(_DWORD *)((char *)this + NNN)
    metrics["offset_access"] += len(
        re.findall(r'\*\(_[A-Z0-9_]+\s*\*\)\(\(char\s*\*\)this\s*\+\s*\d+\)', code)
    )
    # And general base+offset patterns
    metrics["offset_access"] += len(
        re.findall(r'\*\(_[A-Z0-9_]+\s*\*\)\(\(_DWORD\s*\*\)this\s*\+\s*\d+\)', code)
    )

    # 2. _misattrib_ prefix (uncertain attribution)
    metrics["misattrib_refs"] = len(re.findall(r'_?misattrib_\w+', code))

    # 4. Cast issues
    metrics["void_cast"] = len(
        re.findall(r'\(void\s*\*\)', code)
    )
    metrics["fnptr_cast"] = len(
        re.findall(r'\(\s*int\s*\(\s*\*?\s*__\w+\s*\*?\s*\)', code)
    )
    metrics["bad_cast_total"] = metrics["void_cast"] + metrics["fnptr_cast"]

    # 5. sub_ / todo_ / crt_sub_ / unknown_libname_ references
    metrics["sub_refs"] = len(re.findall(r'\bsub_[0-9A-Fa-f]+\b', code))
    metrics["todo_refs"] = len(re.findall(r'\btodo_[0-9A-Fa-f]+\b', code))
    metrics["crt_sub_refs"] = len(re.findall(r'\bcrt_sub_[0-9A-Fa-f]+\b', code))
    metrics["unknown_lib_refs"] = len(re.findall(r'\bunknown_libname_\d+\b', code))
    metrics["unnamed_refs_total"] = (
        metrics["sub_refs"]
        + metrics["todo_refs"]
        + metrics["crt_sub_refs"]
        + metrics["unknown_lib_refs"]
    )

    # 6. LODWORD/HIDWORD (type confusion markers)
    metrics["lodword_refs"] = len(re.findall(r'\b(?:LODWORD|HIDWORD)\b', code))

    # 7. _gap_ / _field_ / _todo_ naming in struct member access
    metrics["gap_access"] = len(re.findall(r'\b(?:_gap_|_field_|_todo_)\b', code))

    # 8. Named member access (this->m_Xxx etc.)
    metrics["named_this_access"] = len(
        re.findall(r'this->m_[A-Za-z]', code)
    )

    # 9. Hardcoded numeric offset in code (not annotation offset field)
    metrics["hardcoded_offset"] = len(
        re.findall(r'\(this\s*\+\s*\d+\)|\(\(char\s*\*\)this\s*\+\s*\d+\)', code)
    )

    # 7. Lines of code
    body_match = re.search(r'\{(.*)\}', code, re.DOTALL)
    if body_match:
        body_lines = [l.strip() for l in body_match.group(1).split("\n") if l.strip() and not l.strip().startswith("//")]
        metrics["loc"] = len(body_lines)
    else:
        metrics["loc"] = 0

    # 8. Hardcoded offset to named member ratio
    total_member_access = metrics["named_this_access"] + metrics["gap_access"] + metrics["offset_access"]
    if total_member_access > 0:
        metrics["named_ratio"] = metrics["named_this_access"] / total_member_access
    else:
        metrics["named_ratio"] = 1.0 if metrics["loc"] == 0 else 0.0

    return metrics


def annot_overall_score():
    """Compute annotation-level metrics across all structs."""
    total_members = 0
    total_named = 0
    total_gap = 0
    total_field = 0
    total_todo = 0

    if not STRUCTS_DIR.exists():
        return None

    for f in sorted(STRUCTS_DIR.glob("*.json")):
        try:
            with open(f, encoding="utf-8") as fh:
                d = json.load(fh)
        except (json.JSONDecodeError, OSError):
            continue

        members = d.get("known_members", {})
        if not members:
            continue

        for mname, minfo in members.items():
            total_members += 1
            if mname.startswith("_gap_"):
                total_gap += 1
            elif mname.startswith("_field_"):
                total_field += 1
            elif mname.startswith("_todo_"):
                total_todo += 1
            else:
                total_named += 1

    if total_members == 0:
        return None

    return {
        "total_members": total_members,
        "named": total_named,
        "_gap_": total_gap,
        "_field_": total_field,
        "_todo_": total_todo,
        "semantic_ratio": total_named / total_members,
    }


def generate_report(benchmark_results, annotation_score, fmt="text"):
    """Generate a structured report."""
    if fmt == "json":
        return json.dumps(
            {"benchmarks": benchmark_results, "annotations": annotation_score},
            indent=2,
        )

    lines = []
    lines.append("=" * 72)
    lines.append("  PAL3 Decomp Benchmark Evaluation")
    lines.append("=" * 72)
    lines.append("")

    for b in benchmark_results:
        name = b["name"]
        m = b["metrics"]
        status = "PASS" if m and m["loc"] > 0 else "NOT FOUND"

        if status == "NOT FOUND":
            lines.append(f"  ⏭️  {name} — function body not found in generated code")
            lines.append("")
            continue

        lines.append(f"  📊 {name} ({b['reason']})")
        lines.append(f"      LOC: {m['loc']}")
        lines.append(f"      Offset accesses:      {m['offset_access']}")
        lines.append(f"      _misattrib_ refs:      {m['misattrib_refs']}")
        lines.append(f"      Casts for review:      {m['bad_cast_total']} (void*:{m['void_cast']}, fnptr:{m['fnptr_cast']})")
        lines.append(f"      LODWORD/HIDWORD:       {m['lodword_refs']}")
        lines.append(f"      Unnamed refs:          {m['unnamed_refs_total']} (sub:{m['sub_refs']}, todo:{m['todo_refs']}, crt_sub:{m['crt_sub_refs']})")
        lines.append(f"      _gap_/_field_ access:  {m['gap_access']}")
        lines.append(f"      Named this->m_*:       {m['named_this_access']}")
        lines.append(f"      Hardcoded offsets:     {m['hardcoded_offset']}")
        lines.append("")

    if annotation_score:
        lines.append("  📊 Annotation overall")
        lines.append(f"      Total members:  {annotation_score['total_members']}")
        lines.append(f"      Named:          {annotation_score['named']}")
        lines.append(f"      _gap_:          {annotation_score['_gap_']}")
        lines.append(f"      _field_:        {annotation_score['_field_']}")
        lines.append(f"      _todo_:         {annotation_score['_todo_']}")
        lines.append(f"      Semantic ratio: {annotation_score['semantic_ratio']:.1%}")
        lines.append("")

    lines.append("=" * 72)
    return "\n".join(lines)


def main():
    fmt = "json" if "--json" in sys.argv else "text"

    results = []
    for bm in BENCHMARKS:
        name = bm["name"]

        # Get generated cpp code (post-codegen, reflects final output quality)
        decomp = find_decomp_json(name)
        cpp_path = find_generated_cpp(name, bm["module"])
        cpp_code = extract_function_code(cpp_path, name)

        if cpp_code:
            code = cpp_code
            src = "generated"
        elif decomp:
            code = decomp.get("decompiled_c", "")
            src = "decomp_only"
        else:
            results.append({"name": name, "metrics": None, "error": "not_found"})
            continue

        metrics = count_metrics(name, code)

        results.append(
            {
                "name": name,
                "reason": bm["reason"],
                "class": name.split("::")[0],
                "method": name.split("::", 1)[1],
                "addr": decomp.get("address") if decomp else None,
                "size_bytes": decomp.get("size_bytes") if decomp else None,
                "metrics": metrics,
                "src": src,
            }
        )

    ann_score = annot_overall_score()
    report = generate_report(results, ann_score, fmt=fmt)
    print(report)


if __name__ == "__main__":
    main()
