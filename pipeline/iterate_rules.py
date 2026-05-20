"""Rules engine: extract annotation fixes from IDA query output + compile errors."""
import json
import re
import sys
from pathlib import Path
from collections import defaultdict, Counter
from typing import List

sys.path.insert(0, str(Path(__file__).parent.parent))
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
            if from_type == 'void *':
                continue
            caller_evidence[func_name][param_idx][(from_type, to_type)] += 1

    fixes = []
    for func_name, params in caller_evidence.items():
        for param_idx, type_pairs in params.items():
            for (from_type, to_type), count in type_pairs.items():
                if count < 3:
                    continue
                for addr, info in fns.items():
                    name = info.get('name', '')
                    method = name.split('::')[-1] if '::' in name else name
                    if method == func_name and to_type in info.get('signature', ''):
                        clean_from = re.sub(r'^(?:class|struct)\s+', '', from_type)
                        clean_to = re.sub(r'^(?:class|struct)\s+', '', to_type)
                        fixes.append(Fix(
                            type='signature',
                            target=f'{name} param{param_idx}',
                            old_value=clean_to,
                            new_value=clean_from,
                            evidence=f'{count}x callers pass {clean_from}',
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
            inferred_type = _parse_ctor_type(call_name)
            if not inferred_type or inferred_type == cur_type:
                continue
            fixes.append(Fix(
                type='field_type',
                target=key,
                old_value=cur_type,
                new_value=inferred_type,
                evidence=f'ctor_call({call_name[:40]})',
                confidence=85,
                cls_name=cls_name,
                offset=offset,
            ))
            break
    return fixes


def _parse_ctor_type(call_name: str) -> str:
    m = re.match(r'\?\?_F(\w+)@@', call_name)
    if m:
        return m.group(1)
    m = re.match(r'\?\?0(\w+)@@', call_name)
    if m:
        return m.group(1)
    m = re.match(r'\?\?1(\w+)@@', call_name)
    if m:
        return m.group(1)
    m = re.match(r'(\w+)::[~]?\1\b', call_name)
    if m:
        return m.group(1)
    return ""


def rule_attribution_from_access() -> List[Fix]:
    """Rule 3: Fix function attribution based on member access evidence."""
    if not BUILD_OUTPUT.exists():
        return []
    errors = BUILD_OUTPUT.read_text(encoding='utf-8', errors='replace')
    fns = json.load(open(ANN_DIR / 'functions.json', encoding='utf-8'))

    struct_members = {}
    structs_dir = ANN_DIR / 'structs'
    for f in structs_dir.glob('*.json'):
        try:
            s = json.load(open(f, encoding='utf-8'))
            name = s.get('name', f.stem)
            members = set(m.get('name', '') for m in s.get('known_members', {}).values())
            struct_members[name] = members
        except:
            continue

    c2673_funcs = set()
    for line in errors.split('\n'):
        if 'C2673' in line:
            m = re.search(r"'(\w+)'", line)
            if m:
                c2673_funcs.add(m.group(1))

    if not c2673_funcs:
        return []

    fixes = []
    decomp_dir = PROJECT_ROOT / 'asm' / 'pal3' / 'decomp'

    for addr, info in fns.items():
        name = info.get('name', '')
        if '::' not in name:
            continue
        cur_class, method = name.split('::', 1)
        if method not in c2673_funcs:
            continue

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

        accessed_members = set(re.findall(r'this->(\w+)', code))
        if len(accessed_members) < 3:
            continue

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
