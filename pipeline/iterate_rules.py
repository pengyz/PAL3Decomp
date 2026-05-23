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
