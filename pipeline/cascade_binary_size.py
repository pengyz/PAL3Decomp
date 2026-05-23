"""Cascade binary_size changes through embedded struct relationships (recursive).

NOTE: This tool modifies annotation JSON. IDA's actual struct sizes depend on
TIL-level type resolution. Changing annotation binary_size alone does NOT
change IDA's struct size if embedded types have different sizes in TIL.

For safe application: start from leaf structs (not embedded in others),
then work up the hierarchy.

Usage:
    python pipeline/cascade_binary_size.py --apply UIStatic=152
    python pipeline/cascade_binary_size.py --dry-run UIStatic=152
    python pipeline/cascade_binary_size.py --check  # show PAL3patch mismatches
"""
import json
import os
import sys
import glob
from collections import defaultdict

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


def load_all_structs():
    structs = {}
    for f in glob.glob(os.path.join(STRUCTS_DIR, '*.json')):
        sname = os.path.basename(f).replace('.json', '')
        structs[sname] = json.load(open(f, encoding='utf-8'))
    return structs


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

    print("Use --check to show PAL3patch size mismatches")
    print("Binary_size cascade requires IDA TIL-level coordination.")
    print("See memory/project_binary_size_cascade.md for details.")


if __name__ == '__main__':
    main()
