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


def overlap_check(cls_name: str, offset: int, new_type: str) -> bool:
    """Return True if the new type fits without overlapping the next field."""
    struct_path = ANN_DIR / 'structs' / f'{cls_name}.json'
    if not struct_path.exists():
        return False
    ann = json.load(open(struct_path, encoding='utf-8'))
    members = ann.get('known_members', {})
    binary_size = ann.get('binary_size') or 0

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
            return s.get('binary_size')
        except:
            pass
    return None


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
