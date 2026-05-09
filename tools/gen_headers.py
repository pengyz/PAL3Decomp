#!/usr/bin/env python3
"""
Generate C++ header files from IDA decomp JSONs.

For each class found in decomp, generates:
  include/pal3/gen/<ClassName>.h

Each header contains:
  - Class declaration with all method signatures
  - Proper __thiscall/static annotations
  - Address comments for each method

Usage:
  python tools/gen_headers.py
"""

import json
import os
import re
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "include" / "pal3" / "gen"

# Classes to skip (STL/CRT/gbengine - not our code)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'gbMatrixStack', 'gbSceneGraph', 'gbCamera',
    'gbEffectMgr', 'gbRefObject', 'gbActor', 'gbVisNode', 'gbTexture',
    'gbGfxManager', 'gbActorMgr', 'gbVFileSystem', 'gbDynVertBuf',
    'gbVertPoolMgr', 'gbPrintFont', 'gbPrintFontMgr', 'gbBinkVideo',
    'gbMatrixStack', 'gbSoundData', 'gbResManager',
    'UIListBox',  # likely std container
}


def parse_signature(sig):
    """Parse IDA signature into return type + params."""
    # Pattern: return_type __thiscall(params)
    # or: return_type __cdecl(params)
    m = re.match(r'(.+?)\s+(__\w+)\s*\((.+)\)', sig)
    if m:
        ret = m.group(1).strip()
        cc = m.group(2)
        params = m.group(3).strip()
        return ret, cc, params
    return sig, '', ''


def generate_class_header(cls_name, methods):
    """Generate header file content for a class."""
    lines = []
    lines.append("#pragma once")
    lines.append(f"// Auto-generated from IDA decomp - {cls_name}")
    lines.append(f"// {len(methods)} methods")
    lines.append("")
    lines.append(f"class {cls_name} {{")
    lines.append("public:")

    for method_name, sig, addr in sorted(methods, key=lambda x: x[2]):
        ret, cc, params = parse_signature(sig)

        # Determine if static (cdecl without this) or member (thiscall)
        is_thiscall = '__thiscall' in cc
        is_static = not is_thiscall

        # Clean params: remove "ClassName *this, " from thiscall
        if is_thiscall and params:
            # Remove first param (this)
            param_list = []
            depth = 0
            current = ''
            for ch in params:
                if ch == ',' and depth == 0:
                    param_list.append(current.strip())
                    current = ''
                else:
                    if ch == '(': depth += 1
                    elif ch == ')': depth -= 1
                    current += ch
            if current.strip():
                param_list.append(current.strip())
            # Remove first param (this pointer)
            if param_list and ('this' in param_list[0] or '*this' in param_list[0]):
                param_list = param_list[1:]
            params = ', '.join(param_list)

        # Build declaration
        prefix = "    static " if is_static else "    "
        decl = f"{prefix}{ret} {method_name}({params});"
        comment = f"  // {addr}"

        lines.append(f"{decl}{comment}")

    lines.append("};")
    lines.append("")
    return '\n'.join(lines)


def main():
    # Collect all class methods
    classes = defaultdict(list)

    for f in sorted(DECOMP_DIR.glob("*.json")):
        if f.name.startswith("_"):
            continue
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
        except:
            continue

        name = d.get('name', '')
        sig = d.get('signature', '')
        addr = d.get('address', '')

        if '::' not in name or name.startswith('sub_'):
            continue

        parts = name.split('::', 1)
        cls = parts[0]
        method = parts[1].split('(')[0] if '(' in parts[1] else parts[1]

        if cls in SKIP_CLASSES:
            continue

        classes[cls].append((method, sig, addr))

    # Generate headers
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    generated = 0
    for cls_name, methods in sorted(classes.items()):
        if len(methods) < 2:
            continue  # Skip single-method classes

        content = generate_class_header(cls_name, methods)
        output_path = OUTPUT_DIR / f"{cls_name}.h"
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(content)
        generated += 1

    print(f"Generated {generated} header files in {OUTPUT_DIR}")
    print(f"Total methods: {sum(len(m) for m in classes.values() if len(m) >= 2)}")


if __name__ == '__main__':
    main()
