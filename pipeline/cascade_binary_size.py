"""Cascade binary_size changes through inheritance and embedding relationships.

Usage:
    python pipeline/cascade_binary_size.py --check              # show PAL3patch mismatches
    python pipeline/cascade_binary_size.py --dry-run UIWnd=68   # preview cascade
    python pipeline/cascade_binary_size.py --apply UIWnd=68     # apply cascade to JSON files
"""
import json
import os
import re
import sys
import glob
from collections import defaultdict, deque
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Set, Tuple

STRUCTS_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'data', 'annotations', 'structs')

PAL3PATCH_SIZES = {
    'CCBUI': 0xA48, 'UIStatic': 0x98, 'UI3DCtrl': 0x134,
    'LineupUI': 0x29CEC, 'UICaption': 0x60, 'UINote': 0x10C,
    'ScreenEffect': 0x18, 'UIRoleSelect': 0x5D0, 'UIGameFrm': 0x6E1C,
    'UISceneMap': 0x3F4, 'UISceneFrm': 0xB30, 'UIGameOver': 0xE8,
    'GRPinput': 0x2958, 'CCBSystem': 0x162D8, 'RenderTarget': 0xC8,
    'Role': 0x2200, 'UIEmote': 0x8E0, 'UIChatRest': 0x252C,
    'UIHeadDialog': 0x160, 'UIRoleDialog': 0x454, 'UISceneFace': 0x6F4,
    'HeadMsg': 0x24, 'ObjectCamera': 0x7C, 'UIStaticEXA': 0xC0,
    'CCBLineupWindow': 0x7C, 'UICursor': 0x20, 'UnderWater': 0x18,
    'CCBAttackSequen': 0x1C8,
}

PRIMITIVE_SIZES = {
    'int': 4, 'float': 4, 'double': 8, 'char': 1, 'bool': 1,
    'unsigned char': 1, 'unsigned short': 2, 'short': 2,
    'unsigned long': 4, 'unsigned int': 4, 'long': 4,
    'BYTE': 1, '_BYTE': 1, 'WORD': 2, '_WORD': 2,
    'DWORD': 4, '_DWORD': 4, 'LONG': 4, 'BOOL': 4,
    '__int64': 8, 'LARGE_INTEGER': 8,
}

KNOWN_TYPE_SIZES = {
    'gbVec2D': 8, 'gbVec3D': 12, 'gbVec4D': 16,
    'gbColorQuad': 4, 'gbColorFlt': 16,
    'gbMatrix4': 64, 'gbQuaternion': 16,
    'gbAABBox': 24, 'gbOBBox': 76, 'gbSphere': 16,
    'gbRay': 24, 'tagRECT': 16, 'RECT': 16,
    'POINT': 8, 'tagPOINT': 8, 'SIZE': 8,
    'PtrArray': 16, 'D3DXVECTOR3': 12, 'D3DXVECTOR2': 8,
}


@dataclass
class ShiftChange:
    struct_name: str
    old_offset: int
    new_offset: int
    field_name: str
    field_type: str


@dataclass
class ResizeChange:
    struct_name: str
    old_size: int
    new_size: int
    reason: str


@dataclass
class CascadeResult:
    resizes: List[ResizeChange] = field(default_factory=list)
    shifts: List[ShiftChange] = field(default_factory=list)
    errors: List[str] = field(default_factory=list)


def load_all_structs() -> Dict[str, dict]:
    structs = {}
    for f in glob.glob(os.path.join(STRUCTS_DIR, '*.json')):
        sname = os.path.basename(f).replace('.json', '')
        structs[sname] = json.load(open(f, encoding='utf-8'))
    return structs


def get_type_size(type_str: str, structs: Dict[str, dict]) -> Optional[int]:
    if not type_str:
        return None
    if '*' in type_str:
        return 4
    arr_match = re.match(r'(.+?)\[(\d+)\]$', type_str.strip())
    if arr_match:
        base = arr_match.group(1).strip()
        count = int(arr_match.group(2))
        base_size = get_type_size(base, structs)
        return base_size * count if base_size else None
    clean = type_str.replace('class ', '').replace('struct ', '').replace('enum ', '').strip()
    if clean in PRIMITIVE_SIZES:
        return PRIMITIVE_SIZES[clean]
    if clean in KNOWN_TYPE_SIZES:
        return KNOWN_TYPE_SIZES[clean]
    if clean in structs:
        return structs[clean].get('binary_size')
    return None


def parse_embedded_type(type_str: str) -> Tuple[Optional[str], int]:
    """Return (base_type_name, array_count) for value-type embeddings. None if pointer."""
    if '*' in type_str:
        return None, 0
    arr_match = re.match(r'(.+?)\[(\d+)\]$', type_str.strip())
    if arr_match:
        base = arr_match.group(1).strip()
        count = int(arr_match.group(2))
    else:
        base = type_str.strip()
        count = 1
    base = base.replace('class ', '').replace('struct ', '').replace('enum ', '').strip()
    return base, count


def build_inheritance_children(structs: Dict[str, dict]) -> Dict[str, List[str]]:
    """base_name -> [direct children]"""
    children = defaultdict(list)
    for sname, s in structs.items():
        base = s.get('base_class')
        if isinstance(base, list):
            for b in base:
                children[b].append(sname)
        elif base:
            children[base].append(sname)
    return dict(children)


def build_embedding_map(structs: Dict[str, dict]) -> Dict[str, List[Tuple[str, int, str, int]]]:
    """embedded_type -> [(parent_struct, embed_offset, field_name, array_count)]"""
    embedders = defaultdict(list)
    for sname, s in structs.items():
        members = s.get('known_members', {})
        for off_str, info in members.items():
            t = info.get('type', '')
            base_type, count = parse_embedded_type(t)
            if base_type and base_type in structs:
                embedders[base_type].append((sname, int(off_str), info.get('name', ''), count))
    return dict(embedders)


def calculate_cascade(structs: Dict[str, dict], target: str, new_size: int) -> CascadeResult:
    """Calculate all changes needed when target's binary_size changes to new_size."""
    result = CascadeResult()

    if target not in structs:
        result.errors.append(f'{target} not found in annotations')
        return result

    old_size = structs[target].get('binary_size') or 0
    if old_size == new_size:
        result.errors.append(f'{target} already has binary_size={new_size}')
        return result

    inh_children = build_inheritance_children(structs)
    embed_map = build_embedding_map(structs)

    result.resizes.append(ResizeChange(target, old_size, new_size, 'target'))

    # BFS queue: (struct_name, old_size, new_size, propagation_type)
    queue = deque()
    queue.append((target, old_size, new_size, 'target'))
    processed_resize = {target}

    while queue:
        sname, s_old, s_new, prop_type = queue.popleft()
        delta = s_new - s_old

        # Inheritance propagation: shift children's own fields
        for child in inh_children.get(sname, []):
            child_struct = structs[child]
            child_base_size = child_struct.get('base_size') or s_old
            members = child_struct.get('known_members', {})

            # Shift fields at offset >= old base size
            shifted_count = 0
            for off_str, info in members.items():
                off = int(off_str)
                if off >= child_base_size:
                    result.shifts.append(ShiftChange(
                        child, off, off + delta,
                        info.get('name', ''), info.get('type', '')))
                    shifted_count += 1

            # Resize child
            child_old_size = child_struct.get('binary_size') or 0
            child_new_size = child_old_size + delta
            if child not in processed_resize:
                result.resizes.append(ResizeChange(child, child_old_size, child_new_size,
                                                   f'inherits {sname}'))
                processed_resize.add(child)
                queue.append((child, child_old_size, child_new_size, 'inheritance'))

        # Embedding propagation: shift parent's fields after each embed point
        # Group all embeds of this type by parent, process from highest offset down
        embeds_by_parent = defaultdict(list)
        for parent, embed_offset, field_name, arr_count in embed_map.get(sname, []):
            if parent in processed_resize:
                continue
            embeds_by_parent[parent].append((embed_offset, field_name, arr_count))

        for parent, embed_list in embeds_by_parent.items():
            parent_struct = structs[parent]
            members = parent_struct.get('known_members', {})

            # Sort embeds from highest offset to lowest to process correctly
            embed_list.sort(key=lambda x: -x[0])

            # Calculate cumulative shift for each field:
            # A field at offset F is shifted by sum of (delta*count) for all embeds before it
            # Process from high to low: each embed shifts all fields after its end
            field_shifts = {}  # offset -> cumulative_delta
            total_parent_delta = 0

            for embed_offset, field_name_e, arr_count in embed_list:
                embed_delta = delta * arr_count
                old_embed_end = embed_offset + s_old * arr_count
                total_parent_delta += embed_delta

                for off_str in members:
                    off = int(off_str)
                    if off >= old_embed_end:
                        field_shifts[off] = field_shifts.get(off, 0) + embed_delta

            for off, shift_amount in field_shifts.items():
                info = members[str(off)]
                result.shifts.append(ShiftChange(
                    parent, off, off + shift_amount,
                    info.get('name', ''), info.get('type', '')))

            parent_old_size = parent_struct.get('binary_size') or 0
            parent_new_size = parent_old_size + total_parent_delta
            total_embeds = sum(c for _, _, c in embed_list)
            result.resizes.append(ResizeChange(parent, parent_old_size, parent_new_size,
                                               f'embeds {sname}x{total_embeds}'))
            processed_resize.add(parent)
            queue.append((parent, parent_old_size, parent_new_size, 'embedding'))

    return result


def apply_cascade(structs: Dict[str, dict], result: CascadeResult):
    """Apply cascade changes to struct dicts in memory."""
    # Group shifts by struct
    shifts_by_struct = defaultdict(list)
    for shift in result.shifts:
        shifts_by_struct[shift.struct_name].append(shift)

    # Apply resizes
    for resize in result.resizes:
        if resize.struct_name in structs:
            structs[resize.struct_name]['binary_size'] = resize.new_size

    # Apply field shifts (rebuild known_members with new offsets)
    for sname, shifts in shifts_by_struct.items():
        s = structs[sname]
        members = s.get('known_members', {})
        shift_map = {sh.old_offset: sh.new_offset for sh in shifts}

        new_members = {}
        for off_str, info in members.items():
            off = int(off_str)
            new_off = shift_map.get(off, off)
            new_members[str(new_off)] = info
        s['known_members'] = new_members

    # Update base_size for inheritance children
    for resize in result.resizes:
        for sname, s in structs.items():
            base = s.get('base_class')
            bases = [base] if isinstance(base, str) else (base or [])
            if resize.struct_name in bases:
                if s.get('base_size') == resize.old_size:
                    s['base_size'] = resize.new_size


def save_structs(structs: Dict[str, dict], names: Set[str]):
    """Write modified structs back to disk."""
    for sname in names:
        if sname in structs:
            fpath = os.path.join(STRUCTS_DIR, f'{sname}.json')
            with open(fpath, 'w', encoding='utf-8') as f:
                json.dump(structs[sname], f, indent=2, ensure_ascii=False)


def print_dry_run(target: str, new_size: int, result: CascadeResult):
    """Print formatted dry-run output."""
    old_size = None
    for r in result.resizes:
        if r.struct_name == target:
            old_size = r.old_size
            break

    print(f'\nBINARY SIZE CASCADE: {target} {old_size} -> {new_size} (delta = {new_size - old_size:+d})')
    print('=' * 64)

    if result.errors:
        for e in result.errors:
            print(f'  ERROR: {e}')
        return

    # Group resizes by reason
    inh_resizes = [r for r in result.resizes if 'inherits' in r.reason]
    emb_resizes = [r for r in result.resizes if 'embeds' in r.reason]

    # Count shifts per struct
    shifts_by_struct = defaultdict(int)
    for sh in result.shifts:
        shifts_by_struct[sh.struct_name] += 1

    if inh_resizes:
        print(f'\nPHASE 1: INHERITANCE ({len(inh_resizes)} structs)')
        print('-' * 64)
        for r in sorted(inh_resizes, key=lambda x: -shifts_by_struct.get(x.struct_name, 0)):
            n_shifts = shifts_by_struct.get(r.struct_name, 0)
            pal3 = PAL3PATCH_SIZES.get(r.struct_name)
            flag = ''
            if pal3:
                if r.new_size == pal3:
                    flag = ' [PAL3patch OK]'
                else:
                    flag = f' [PAL3patch expects {pal3}]'
            print(f'  {r.struct_name:25s}: shift {n_shifts:3d} fields, '
                  f'size {r.old_size}->{r.new_size}{flag}')

    if emb_resizes:
        print(f'\nPHASE 2: EMBEDDING ({len(emb_resizes)} structs)')
        print('-' * 64)
        for r in sorted(emb_resizes, key=lambda x: -shifts_by_struct.get(x.struct_name, 0)):
            n_shifts = shifts_by_struct.get(r.struct_name, 0)
            pal3 = PAL3PATCH_SIZES.get(r.struct_name)
            flag = ''
            if pal3:
                if r.new_size == pal3:
                    flag = ' [PAL3patch OK]'
                else:
                    flag = f' [PAL3patch expects {pal3}]'
            print(f'  {r.struct_name:25s}: shift {n_shifts:3d} fields, '
                  f'size {r.old_size}->{r.new_size} ({r.reason}){flag}')

    print(f'\nSUMMARY:')
    print(f'  Structs resized:  {len(result.resizes)}')
    print(f'  Fields shifted:   {len(result.shifts)}')
    total_affected = set(r.struct_name for r in result.resizes)
    print(f'  Files to modify:  {len(total_affected)}')

    # PAL3patch comparison
    matches = 0
    mismatches = []
    for r in result.resizes:
        if r.struct_name in PAL3PATCH_SIZES:
            if r.new_size == PAL3PATCH_SIZES[r.struct_name]:
                matches += 1
            else:
                mismatches.append((r.struct_name, r.new_size, PAL3PATCH_SIZES[r.struct_name]))
    if matches or mismatches:
        print(f'\n  PAL3patch validation: {matches} match, {len(mismatches)} mismatch')
        for name, got, exp in mismatches[:10]:
            print(f'    {name}: got {got}, expected {exp} (needs separate fix)')


def check_mismatches():
    structs = load_all_structs()
    print("PAL3patch verified sizes vs current annotations:\n")
    mismatched = []
    for name, expected in sorted(PAL3PATCH_SIZES.items()):
        if name not in structs:
            print(f"  {name:20s}: MISSING annotation file (expected 0x{expected:X})")
            continue
        current = structs[name].get('binary_size', 0)
        if current != expected:
            diff = expected - current
            mismatched.append((name, current, expected))
            print(f"  {name:20s}: current={current:6d} (0x{current:X}), "
                  f"expected={expected:6d} (0x{expected:X}), diff={diff:+d}")
        else:
            print(f"  {name:20s}: OK ({current})")
    print(f"\n{len(mismatched)} mismatches, "
          f"{len(PAL3PATCH_SIZES) - len(mismatched)} match")


def main():
    if '--check' in sys.argv:
        check_mismatches()
        return

    # Parse target=size argument
    target_arg = None
    for arg in sys.argv[1:]:
        if '=' in arg and not arg.startswith('--'):
            target_arg = arg
            break

    if not target_arg:
        print("Usage:")
        print("  python pipeline/cascade_binary_size.py --check")
        print("  python pipeline/cascade_binary_size.py --dry-run UIWnd=68")
        print("  python pipeline/cascade_binary_size.py --apply UIWnd=68")
        return

    parts = target_arg.split('=')
    target_name = parts[0]
    new_size = int(parts[1])

    dry_run = '--dry-run' in sys.argv
    do_apply = '--apply' in sys.argv

    if not dry_run and not do_apply:
        print("Specify --dry-run or --apply")
        return

    # Support --from=N to override old_size (for when target was already manually fixed)
    from_size = None
    for arg in sys.argv[1:]:
        if arg.startswith('--from='):
            from_size = int(arg.split('=')[1])

    structs = load_all_structs()
    if from_size is not None:
        structs[target_name]['binary_size'] = from_size
    result = calculate_cascade(structs, target_name, new_size)

    print_dry_run(target_name, new_size, result)

    if do_apply and not result.errors:
        print(f'\nAPPLYING changes...')
        apply_cascade(structs, result)
        affected = set(r.struct_name for r in result.resizes)
        affected.update(sh.struct_name for sh in result.shifts)
        save_structs(structs, affected)
        print(f'  Written {len(affected)} struct files.')
        print('  Run: python pipeline/check_annotations.py')


if __name__ == '__main__':
    main()
