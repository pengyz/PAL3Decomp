# Annotation Iteration Engine Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build `pipeline/iterate.py` that automatically iterates annotation fixes until compile errors converge.

**Architecture:** Three files: `iterate.py` (CLI + main loop), `iterate_rules.py` (evidence analysis rules), `iterate_apply.py` (fix application + overlap check). Reuses existing `cli.py` commands, `_compile_and_collect()`, and `check_annotations.py`.

**Tech Stack:** Python 3.8+, subprocess (IDA headless), json, argparse, git

---

### Task 1: iterate_apply.py — Fix Application + Safety

**Files:**
- Create: `pipeline/iterate_apply.py`

- [ ] **Step 1: Create iterate_apply.py with core data types**

```python
"""Apply annotation fixes with overlap checking and rollback."""
import json
import os
import subprocess
import sys
from pathlib import Path
from dataclasses import dataclass, field
from typing import List, Optional

PROJECT_ROOT = Path(__file__).parent.parent
ANN_DIR = PROJECT_ROOT / 'data' / 'annotations'


@dataclass
class Fix:
    type: str           # "signature" | "field_type" | "attribution"
    target: str         # e.g. "CCBStage+296" or "0x0040CF60"
    old_value: str      # previous type/name
    new_value: str      # new type/name
    evidence: str       # one-line evidence summary
    confidence: int     # 80-90
    # For field_type fixes
    cls_name: str = ""
    offset: int = 0
    # For signature fixes
    addr: str = ""
    param_idx: int = 0
    # For attribution fixes
    old_class: str = ""
    new_class: str = ""
```

- [ ] **Step 2: Add overlap_check function**

```python
def overlap_check(cls_name: str, offset: int, new_type: str) -> bool:
    """Return True if the new type fits without overlapping the next field."""
    struct_path = ANN_DIR / 'structs' / f'{cls_name}.json'
    if not struct_path.exists():
        return False
    ann = json.load(open(struct_path, encoding='utf-8'))
    members = ann.get('known_members', {})
    binary_size = ann.get('binary_size') or ann.get('gen_size') or 0

    # Determine size of new type
    type_size = _get_type_size(new_type)
    if type_size is None:
        return False

    # Find next field after this offset
    next_offset = binary_size  # default to end of struct
    for off_str in members:
        off = int(off_str)
        if off > offset:
            next_offset = min(next_offset, off)

    return offset + type_size <= next_offset


def _get_type_size(type_name: str) -> Optional[int]:
    """Get size of a type. Returns None if unknown."""
    # Primitives
    if type_name in ('int', 'float', 'unsigned long', 'DWORD', '_DWORD'):
        return 4
    if type_name in ('char', 'unsigned char', 'BYTE', '_BYTE', 'bool'):
        return 1
    if type_name in ('short', 'unsigned short', 'WORD', '_WORD'):
        return 2
    if type_name in ('double', '__int64'):
        return 8
    if '*' in type_name:
        return 4  # 32-bit pointers

    # Known engine types
    KNOWN_SIZES = {
        'gbVec3D': 12, 'gbVec2D': 8, 'gbVec4D': 16,
        'gbColorQuad': 4, 'gbColorFlt': 16,
        'gbMatrix4': 64, 'gbQuaternion': 16,
        'gbAABBox': 24, 'gbOBBox': 76, 'gbSphere': 16,
        'gbRay': 24,
    }
    if type_name in KNOWN_SIZES:
        return KNOWN_SIZES[type_name]

    # Look up from annotations
    struct_path = ANN_DIR / 'structs' / f'{type_name}.json'
    if struct_path.exists():
        try:
            s = json.load(open(struct_path, encoding='utf-8'))
            return s.get('binary_size') or s.get('gen_size')
        except:
            pass
    return None
```

- [ ] **Step 3: Add apply_fixes function**

```python
def apply_fixes(fixes: List[Fix]) -> List[Fix]:
    """Apply fixes one by one. Skip any that fail check_annotations."""
    applied = []
    for fix in fixes:
        if fix.type == 'signature':
            success = _apply_signature_fix(fix)
        elif fix.type == 'field_type':
            success = _apply_field_type_fix(fix)
        elif fix.type == 'attribution':
            success = _apply_attribution_fix(fix)
        else:
            continue

        if not success:
            continue

        # Validate
        if not _run_check():
            _revert_fix(fix)
            continue

        applied.append(fix)
    return applied


def _apply_signature_fix(fix: Fix) -> bool:
    """Modify function signature in functions.json."""
    fpath = ANN_DIR / 'functions.json'
    fns = json.load(open(fpath, encoding='utf-8'))
    if fix.addr not in fns:
        return False
    sig = fns[fix.addr].get('signature', '')
    new_sig = sig.replace(fix.old_value, fix.new_value, 1)
    if new_sig == sig:
        return False
    fns[fix.addr]['signature'] = new_sig
    json.dump(fns, open(fpath, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
    return True


def _apply_field_type_fix(fix: Fix) -> bool:
    """Modify struct field type."""
    if not overlap_check(fix.cls_name, fix.offset, fix.new_value):
        return False
    struct_path = ANN_DIR / 'structs' / f'{fix.cls_name}.json'
    ann = json.load(open(struct_path, encoding='utf-8'))
    members = ann.get('known_members', {})
    off_str = str(fix.offset)
    if off_str not in members:
        return False
    members[off_str]['type'] = fix.new_value
    members[off_str]['source'] = f'iterate:{fix.evidence}'
    ann['name'] = fix.cls_name
    json.dump(ann, open(struct_path, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
    return True


def _apply_attribution_fix(fix: Fix) -> bool:
    """Change function class attribution."""
    fpath = ANN_DIR / 'functions.json'
    fns = json.load(open(fpath, encoding='utf-8'))
    if fix.addr not in fns:
        return False
    old_name = fns[fix.addr].get('name', '')
    if fix.old_class + '::' not in old_name:
        return False
    new_name = old_name.replace(fix.old_class + '::', fix.new_class + '::', 1)
    fns[fix.addr]['name'] = new_name
    json.dump(fns, open(fpath, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
    return True


def _run_check() -> bool:
    """Run check_annotations, return True if 0 errors."""
    result = subprocess.run(
        [sys.executable, str(PROJECT_ROOT / 'pipeline' / 'check_annotations.py')],
        capture_output=True, text=True)
    return '0 errors' in result.stdout


def _revert_fix(fix: Fix):
    """Revert the specific file touched by this fix."""
    if fix.type == 'signature' or fix.type == 'attribution':
        subprocess.run(['git', 'checkout', '--', str(ANN_DIR / 'functions.json')],
                       cwd=str(PROJECT_ROOT))
    elif fix.type == 'field_type':
        subprocess.run(['git', 'checkout', '--', str(ANN_DIR / 'structs' / f'{fix.cls_name}.json')],
                       cwd=str(PROJECT_ROOT))


def rollback_all():
    """Revert all annotation changes."""
    subprocess.run(['git', 'checkout', '--', str(ANN_DIR)], cwd=str(PROJECT_ROOT))
```

- [ ] **Step 4: Verify module imports work**

Run: `cd D:/workspace/PAL3Decomp && python -c "from pipeline.iterate_apply import Fix, apply_fixes, overlap_check; print('OK')"`
Expected: `OK`

- [ ] **Step 5: Commit**

```bash
git add pipeline/iterate_apply.py
git commit -m "feat(iterate): add iterate_apply.py — fix application with overlap safety"
```

---

### Task 2: iterate_rules.py — Evidence Analysis Rules

**Files:**
- Create: `pipeline/iterate_rules.py`

- [ ] **Step 1: Create iterate_rules.py with Rule 1 (signature unification)**

```python
"""Rules engine: extract annotation fixes from IDA query output + compile errors."""
import json
import re
import subprocess
import sys
from pathlib import Path
from collections import defaultdict, Counter
from typing import List

from pipeline.iterate_apply import Fix

PROJECT_ROOT = Path(__file__).parent.parent
ANN_DIR = PROJECT_ROOT / 'data' / 'annotations'
LOGS_DIR = PROJECT_ROOT / 'pipeline' / 'ida' / '_logs'
BUILD_OUTPUT = PROJECT_ROOT / 'build_output.txt'


def rule_signature_from_callers() -> List[Fix]:
    """Rule 1: Fix function signatures where 3+ callers disagree with declaration."""
    if not BUILD_OUTPUT.exists():
        return []

    errors = BUILD_OUTPUT.read_text(encoding='utf-8', errors='replace')
    fns = json.load(open(ANN_DIR / 'functions.json', encoding='utf-8'))

    # Parse C2664 errors: extract function name, param index, from_type, to_type
    caller_evidence = defaultdict(lambda: defaultdict(Counter))
    for line in errors.split('\n'):
        if 'C2664' not in line:
            continue
        func_m = re.search(r"'(\w+)'\s*:", line)
        param_m = re.search(r"parameter (\d+) from '([^']+)' to '([^']+)'", line)
        if func_m and param_m:
            func_name = func_m.group(1)
            param_idx = int(param_m.group(1))
            from_type = param_m.group(2)
            to_type = param_m.group(3)
            # Skip void* callers (too generic)
            if from_type == 'void *':
                continue
            caller_evidence[func_name][param_idx][(from_type, to_type)] += 1

    fixes = []
    for func_name, params in caller_evidence.items():
        for param_idx, type_pairs in params.items():
            # Find dominant pattern (3+ callers agree)
            for (from_type, to_type), count in type_pairs.items():
                if count < 3:
                    continue
                # Find this function in annotations
                for addr, info in fns.items():
                    name = info.get('name', '')
                    method = name.split('::')[-1] if '::' in name else name
                    if method == func_name and to_type in info.get('signature', ''):
                        # Clean types for replacement
                        clean_from = re.sub(r'^(?:class|struct)\s+', '', from_type)
                        clean_to = re.sub(r'^(?:class|struct)\s+', '', to_type)
                        fixes.append(Fix(
                            type='signature',
                            target=f'{name} param{param_idx}',
                            old_value=clean_to,
                            new_value=clean_from,
                            evidence=f'{count}x callers pass {clean_from} (decl: {clean_to})',
                            confidence=80,
                            addr=addr,
                            param_idx=param_idx,
                        ))
                        break
    return fixes
```

- [ ] **Step 2: Add Rule 2 (embedded type from constructor)**

```python
def rule_embed_from_ctor() -> List[Fix]:
    """Rule 2: Fix field types where LEA + constructor call proves embedded object."""
    lea_path = LOGS_DIR / 'lea_batch_analysis.json'
    if not lea_path.exists():
        return []

    lea_data = json.load(open(lea_path, encoding='utf-8'))
    fixes = []

    for key, info in lea_data.items():
        calls = info.get('calls_found', [])
        if not calls:
            continue
        cur_type = info.get('cur_type', '')
        cls_name = info.get('class', '')
        offset = info.get('offset', 0)

        for call in calls:
            call_name = call.get('call_name', '')
            # Parse constructor pattern: ??_F<ClassName>@@QAEXXZ or ClassName::ClassName
            inferred_type = _parse_ctor_type(call_name)
            if not inferred_type:
                continue
            if inferred_type == cur_type:
                continue  # Already correct

            fixes.append(Fix(
                type='field_type',
                target=key,
                old_value=cur_type,
                new_value=inferred_type,
                evidence=f'ctor_call({call_name})',
                confidence=85,
                cls_name=cls_name,
                offset=offset,
            ))
            break  # One fix per field

    return fixes


def _parse_ctor_type(call_name: str) -> str:
    """Extract class name from constructor/destructor mangled name."""
    # Pattern: ??_F<Name>@@QAEXXZ (default ctor closure)
    m = re.match(r'\?\?_F(\w+)@@', call_name)
    if m:
        return m.group(1)
    # Pattern: ??0<Name>@@QAE (constructor)
    m = re.match(r'\?\?0(\w+)@@', call_name)
    if m:
        return m.group(1)
    # Pattern: ??1<Name>@@QAE (destructor)
    m = re.match(r'\?\?1(\w+)@@', call_name)
    if m:
        return m.group(1)
    # Pattern: ClassName::ClassName or ClassName::~ClassName
    m = re.match(r'(\w+)::[~]?\1', call_name)
    if m:
        return m.group(1)
    # Pattern: ClassName::_nearby_XXXX (likely ctor variant)
    # Not reliable enough — skip
    return ""
```

- [ ] **Step 3: Add Rule 3 (function attribution)**

```python
def rule_attribution_from_access() -> List[Fix]:
    """Rule 3: Fix function attribution based on member access evidence."""
    if not BUILD_OUTPUT.exists():
        return []

    errors = BUILD_OUTPUT.read_text(encoding='utf-8', errors='replace')
    fns = json.load(open(ANN_DIR / 'functions.json', encoding='utf-8'))

    # Load struct member lists for matching
    struct_members = {}
    structs_dir = ANN_DIR / 'structs'
    for f in structs_dir.glob('*.json'):
        try:
            s = json.load(open(f, encoding='utf-8'))
            name = s.get('name', f.stem)
            members = set()
            for m in s.get('known_members', {}).values():
                members.add(m.get('name', ''))
            struct_members[name] = members
        except:
            continue

    # Find C2673 errors: "global functions do not have 'this' pointers"
    c2673_funcs = set()
    for line in errors.split('\n'):
        if 'C2673' in line:
            m = re.search(r"'(\w+)'", line)
            if m:
                c2673_funcs.add(m.group(1))

    if not c2673_funcs:
        return []

    # For each C2673 function, check decomp for member access
    fixes = []
    decomp_dir = PROJECT_ROOT / 'asm' / 'pal3' / 'decomp'

    for addr, info in fns.items():
        name = info.get('name', '')
        if '::' not in name:
            continue
        cur_class, method = name.split('::', 1)
        if method not in c2673_funcs:
            continue

        # Read decomp for this function
        decomp_file = None
        for f in decomp_dir.glob(f'*{method}*{addr[2:].lower()}*.json'):
            decomp_file = f
            break
        if not decomp_file or not decomp_file.exists():
            continue

        try:
            d = json.load(open(decomp_file, encoding='utf-8'))
            code = d.get('decompiled_c', '')
        except:
            continue

        # Find this->member accesses
        accessed_members = set(re.findall(r'this->(\w+)', code))
        if len(accessed_members) < 3:
            continue

        # Check which class has the most matching members
        best_class = None
        best_count = 0
        for cls, members in struct_members.items():
            if cls == cur_class:
                continue
            match_count = len(accessed_members & members)
            if match_count > best_count and match_count >= 3:
                best_count = match_count
                best_class = cls

        if best_class:
            fixes.append(Fix(
                type='attribution',
                target=f'{addr}: {name}',
                old_value=cur_class,
                new_value=best_class,
                evidence=f'{best_count} members match {best_class}',
                confidence=80,
                addr=addr,
                old_class=cur_class,
                new_class=best_class,
            ))

    return fixes


def analyze_evidence() -> List[Fix]:
    """Run all rules and return combined fix list."""
    fixes = []
    fixes += rule_signature_from_callers()
    fixes += rule_embed_from_ctor()
    fixes += rule_attribution_from_access()
    return fixes
```

- [ ] **Step 4: Verify module imports**

Run: `cd D:/workspace/PAL3Decomp && python -c "from pipeline.iterate_rules import analyze_evidence; print('OK')"`
Expected: `OK`

- [ ] **Step 5: Commit**

```bash
git add pipeline/iterate_rules.py
git commit -m "feat(iterate): add iterate_rules.py — 3 evidence analysis rules"
```

---

### Task 3: iterate.py — Main Loop + CLI

**Files:**
- Create: `pipeline/iterate.py`

- [ ] **Step 1: Create iterate.py with argument parsing and main loop**

```python
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
            print(f"    [{f.type}] {f.target}: {f.old_value} → {f.new_value} ({f.evidence})")
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
        print("  Rebuilding pipeline (init --force → export → codegen)...")
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
```

- [ ] **Step 2: Verify script runs with --help**

Run: `cd D:/workspace/PAL3Decomp && python pipeline/iterate.py --help`
Expected: Shows usage with all arguments listed

- [ ] **Step 3: Verify --dry-run works**

Run: `cd D:/workspace/PAL3Decomp && python pipeline/iterate.py --dry-run`
Expected: Runs IDA queries, shows candidates, stops without modifying anything

- [ ] **Step 4: Commit**

```bash
git add pipeline/iterate.py
git commit -m "feat(iterate): add iterate.py — main loop with convergence control"
```

---

### Task 4: Integration Test — One Full Round

**Files:**
- No new files (integration test of existing)

- [ ] **Step 1: Run one real round with --max-rounds 1**

Run: `cd D:/workspace/PAL3Decomp && python pipeline/iterate.py --max-rounds 1`
Expected: Completes one full cycle (query → analyze → apply → rebuild → evaluate)

- [ ] **Step 2: Verify git state is clean or committed**

Run: `git status --short | grep "^[MADR]"`
Expected: Either empty (rolled back) or committed (improved)

- [ ] **Step 3: Commit any remaining changes and push**

```bash
git push
```

---

### Task 5: CLI Integration — Add to pipeline/cli.py

**Files:**
- Modify: `pipeline/cli.py`

- [ ] **Step 1: Add `iterate` command to cli.py**

Add to the command dispatch in `main()`:

```python
elif command == 'iterate':
    from pipeline.iterate import main as iterate_main
    sys.argv = ['iterate'] + args[1:]  # pass remaining args
    iterate_main()
```

Add to docstring:
```
  iterate [opts]      自动迭代引擎（annotation 修正直到收敛）
```

- [ ] **Step 2: Verify `python pipeline/cli.py iterate --help` works**

Run: `cd D:/workspace/PAL3Decomp && python pipeline/cli.py iterate --help`
Expected: Shows iterate usage

- [ ] **Step 3: Commit**

```bash
git add pipeline/cli.py
git commit -m "feat(cli): add 'iterate' command for annotation auto-iteration"
git push
```
