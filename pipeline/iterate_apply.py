"""Apply annotation fixes with overlap checking and rollback."""
import json
import subprocess
import sys
from pathlib import Path
from dataclasses import dataclass
from typing import List, Optional

PROJECT_ROOT = Path(__file__).parent.parent
ANN_DIR = PROJECT_ROOT / 'data' / 'annotations'


@dataclass
class Fix:
    type: str
    target: str
    old_value: str
    new_value: str
    evidence: str
    confidence: int
    cls_name: str = ""
    offset: int = 0
    addr: str = ""
    param_idx: int = 0
    old_class: str = ""
    new_class: str = ""


def overlap_check(cls_name: str, offset: int, new_type: str) -> bool:
    struct_path = ANN_DIR / 'structs' / f'{cls_name}.json'
    if not struct_path.exists():
        return False
    ann = json.load(open(struct_path, encoding='utf-8'))
    members = ann.get('known_members', {})
    binary_size = ann.get('binary_size') or ann.get('gen_size') or 0
    type_size = _get_type_size(new_type)
    if type_size is None:
        return False
    next_offset = binary_size
    for off_str in members:
        off = int(off_str)
        if off > offset:
            next_offset = min(next_offset, off)
    return offset + type_size <= next_offset


def _get_type_size(type_name: str) -> Optional[int]:
    if type_name in ('int', 'float', 'unsigned long', 'DWORD', '_DWORD'):
        return 4
    if type_name in ('char', 'unsigned char', 'BYTE', '_BYTE', 'bool'):
        return 1
    if type_name in ('short', 'unsigned short', 'WORD', '_WORD'):
        return 2
    if type_name in ('double', '__int64'):
        return 8
    if '*' in type_name:
        return 4
    KNOWN = {
        'gbVec3D': 12, 'gbVec2D': 8, 'gbVec4D': 16,
        'gbColorQuad': 4, 'gbColorFlt': 16,
        'gbMatrix4': 64, 'gbQuaternion': 16,
        'gbAABBox': 24, 'gbOBBox': 76, 'gbSphere': 16, 'gbRay': 24,
    }
    if type_name in KNOWN:
        return KNOWN[type_name]
    struct_path = ANN_DIR / 'structs' / f'{type_name}.json'
    if struct_path.exists():
        try:
            s = json.load(open(struct_path, encoding='utf-8'))
            return s.get('binary_size') or s.get('gen_size')
        except:
            pass
    return None


def apply_fixes(fixes: List[Fix]) -> List[Fix]:
    applied = []
    for fix in fixes:
        if fix.type == 'signature':
            ok = _apply_signature_fix(fix)
        elif fix.type == 'field_type':
            ok = _apply_field_type_fix(fix)
        elif fix.type == 'attribution':
            ok = _apply_attribution_fix(fix)
        else:
            continue
        if not ok:
            continue
        if not _run_check():
            _revert_fix(fix)
            continue
        applied.append(fix)
    return applied


def _apply_signature_fix(fix: Fix) -> bool:
    fpath = ANN_DIR / 'functions.json'
    fns = json.load(open(fpath, encoding='utf-8'))
    if fix.addr not in fns:
        return False
    sig = fns[fix.addr].get('signature', '')
    # Only replace in the parameter section (after first '('), not in return type or this
    paren_idx = sig.find('(')
    if paren_idx < 0:
        return False
    prefix = sig[:paren_idx + 1]
    params = sig[paren_idx + 1:]
    # Skip 'this' param (first param in __thiscall)
    if '*this' in params:
        this_end = params.find(',')
        if this_end < 0:
            return False  # Only this param, nothing to fix
        this_part = params[:this_end + 1]
        rest = params[this_end + 1:]
        new_rest = rest.replace(fix.old_value, fix.new_value, 1)
        if new_rest == rest:
            return False
        new_sig = prefix + this_part + new_rest
    else:
        new_sig = prefix + params.replace(fix.old_value, fix.new_value, 1)
        if new_sig == sig:
            return False
    fns[fix.addr]['signature'] = new_sig
    json.dump(fns, open(fpath, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
    return True


def _apply_field_type_fix(fix: Fix) -> bool:
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
    fpath = ANN_DIR / 'functions.json'
    fns = json.load(open(fpath, encoding='utf-8'))
    if fix.addr not in fns:
        return False
    old_name = fns[fix.addr].get('name', '')
    if fix.old_class + '::' not in old_name:
        return False
    # Fix name
    fns[fix.addr]['name'] = old_name.replace(fix.old_class + '::', fix.new_class + '::', 1)
    # Fix signature this type to match new class
    sig = fns[fix.addr].get('signature', '')
    if fix.old_class + ' *this' in sig:
        fns[fix.addr]['signature'] = sig.replace(
            fix.old_class + ' *this', fix.new_class + ' *this', 1)
    json.dump(fns, open(fpath, 'w', encoding='utf-8'), indent=2, ensure_ascii=False)
    return True


def _run_check() -> bool:
    result = subprocess.run(
        [sys.executable, str(PROJECT_ROOT / 'pipeline' / 'check_annotations.py')],
        capture_output=True, text=True)
    return '0 errors' in result.stdout


def _revert_fix(fix: Fix):
    if fix.type in ('signature', 'attribution'):
        subprocess.run(['git', 'checkout', '--', str(ANN_DIR / 'functions.json')],
                       cwd=str(PROJECT_ROOT))
    elif fix.type == 'field_type':
        subprocess.run(['git', 'checkout', '--',
                        str(ANN_DIR / 'structs' / f'{fix.cls_name}.json')],
                       cwd=str(PROJECT_ROOT))


def rollback_all():
    subprocess.run(['git', 'checkout', '--', str(ANN_DIR)], cwd=str(PROJECT_ROOT))
