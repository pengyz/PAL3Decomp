#!/usr/bin/env python3
"""
Hex-Rays output post-processor: convert thiscall flattened calls to OOP.

Hex-Rays outputs thiscall as:
  Class::Method(this_ptr, args)    -> this_ptr->Method(args)
  Class::Method(&this_obj, args)   -> this_obj.Method(args)

Edge cases handled:
  - Cast in first arg: func((int)&obj, args) -> obj.func(args)
  - No extra args: Class::Method(ptr) -> ptr->Method()
  - Nested parens in args: preserved correctly
  - &obj.member: NOT converted (not a this pointer, it's member address)
  - Constructor calls: Class::Class(&obj) -> placement new / leave as-is
  - Assignment from call: v = Class::Method(ptr, a) -> v = ptr->Method(a)

Usage:
  python tools/hexrays_to_oop.py --test
  python tools/hexrays_to_oop.py --input <file.json|file.c> [--output <file.cpp>]
"""

import re
import json
import sys
import os
from pathlib import Path

# Set of function names confirmed as __thiscall (loaded from decomp)
# Only these will be converted to OOP form
THISCALL_FUNCS = set()


def load_thiscall_db(decomp_dir):
    """Build set of confirmed thiscall function names from decomp JSONs."""
    global THISCALL_FUNCS
    for f in Path(decomp_dir).glob("*.json"):
        if f.name.startswith("_"):
            continue
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
            name = d.get('name', '')
            sig = d.get('signature', '')
            if name and '__thiscall' in sig:
                THISCALL_FUNCS.add(name)
        except:
            pass


def extract_first_arg_and_rest(args_str):
    """
    Split argument string into (first_arg, rest_args) respecting nested parens.
    Returns (first_arg, rest_args_or_None)
    """
    depth = 0
    for i, ch in enumerate(args_str):
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        elif ch == ',' and depth == 0:
            return args_str[:i].strip(), args_str[i+1:].strip()
    return args_str.strip(), None


def parse_this_arg(first_arg):
    """
    Parse the first argument to determine:
    - Is it a 'this' pointer or '&this' object reference?
    - Strip casts like (int), (void*) etc.

    Returns (obj_expr, is_ref)
      obj_expr: the object/pointer expression
      is_ref: True if &obj (use .), False if ptr (use ->)
      None if we can't parse / shouldn't convert
    """
    arg = first_arg.strip()

    # Strip outer cast: (type)expr -> expr
    # Pattern: (word [*])expr or (word [*] [*])&expr
    cast_pattern = r'^\([^)]+\)\s*(.+)$'
    m = re.match(cast_pattern, arg)
    if m:
        arg = m.group(1).strip()

    # Check if it's &something
    if arg.startswith('&'):
        obj = arg[1:].strip()
        # Reject &obj.member or &obj->member (taking address of member, not this)
        if '.' in obj or '->' in obj:
            return None, False
        return obj, True
    else:
        # It's a pointer expression
        # Reject complex expressions like *(int*)(x+4)
        if arg.startswith('*') or arg.startswith('('):
            return None, False
        return arg, False


def transform_line(line):
    """
    Transform a single line. Handles:
      Class::Method(this, args)  -> this->Method(args) or this.Method(args)
      result = Class::Method(this, args) -> result = this->Method(args)
    """
    # Don't touch comments or preprocessor
    stripped = line.strip()
    if stripped.startswith('//') or stripped.startswith('#') or stripped.startswith('/*'):
        return line

    # Don't touch function signatures (definitions/declarations)
    if '__thiscall' in line or '__cdecl' in line or '__stdcall' in line:
        return line

    # Pattern: optional_prefix Class::Method( args )  optional_suffix
    # Only convert if function is confirmed __thiscall (or THISCALL_FUNCS is empty = convert all)
    # Strategy: find Class::Method( and then balance parens to find full call

    result = line
    # Find all Class::Method( occurrences
    pattern = r'(\w+)::(\w+)\s*\('
    offset = 0

    for m in re.finditer(pattern, line):
        cls = m.group(1)
        method = m.group(2)
        call_start = m.start()
        paren_start = m.end() - 1  # position of '('

        # Skip constructor calls: Class::Class(
        if cls == method:
            continue

        # Skip if not confirmed thiscall (when database is loaded)
        full_name = "%s::%s" % (cls, method)
        if THISCALL_FUNCS and full_name not in THISCALL_FUNCS:
            # Also check partial match (Class::sub_XXXX style)
            if not any(n.startswith(cls + "::") for n in THISCALL_FUNCS if method in n):
                continue

        # Find matching closing paren
        depth = 0
        pos = paren_start
        while pos < len(line):
            if line[pos] == '(':
                depth += 1
            elif line[pos] == ')':
                depth -= 1
                if depth == 0:
                    break
            pos += 1

        if depth != 0:
            continue  # unbalanced, skip

        # Extract full args string
        args_str = line[paren_start+1:pos]

        if not args_str.strip():
            continue  # no args at all? unlikely for thiscall but skip

        # Parse first arg
        first_arg, rest = extract_first_arg_and_rest(args_str)
        obj_expr, is_ref = parse_this_arg(first_arg)

        if obj_expr is None:
            continue  # can't convert

        # Build replacement
        if is_ref:
            access = '.'
        else:
            access = '->'

        if rest:
            new_call = f'{obj_expr}{access}{method}({rest})'
        else:
            new_call = f'{obj_expr}{access}{method}()'

        # Replace in line: from call_start to pos+1
        old_call = line[call_start:pos+1]
        result = result.replace(old_call, new_call, 1)

    return result


def transform_code(code):
    """Transform entire decompiled function."""
    lines = code.split('\n')
    return '\n'.join(transform_line(line) for line in lines)


# ============================================================
# Tests
# ============================================================

TEST_CASES = [
    # Basic Class::Method(ptr, args) -> ptr->Method(args)
    ("  gbMatrixStack::Push(v2);",
     "  v2->Push();"),

    ("  gbMatrixStack::Pop(v2);",
     "  v2->Pop();"),

    ("  gbCamera::SetLookAt(v4, v5, v6, v7);",
     "  v4->SetLookAt(v5, v6, v7);"),

    # &obj -> obj.Method()
    ("  GRPinput::SetMode(&ppvOut, 0x40000000);",
     "  ppvOut.SetMode(0x40000000);"),

    ("  GRPinput::SetMouseLimits(&stru_BFAD70, 0, 0, w, h);",
     "  stru_BFAD70.SetMouseLimits(0, 0, w, h);"),

    # No extra args
    ("  gbSceneGraph::End(v2);",
     "  v2->End();"),

    ("  Logger::RegisterCallbacks(&g_Logger);",
     "  g_Logger.RegisterCallbacks();"),

    # Non-class functions with cast: NOT converted (no :: = unknown if thiscall)
    # These would need external thiscall DB to convert
    ("  sub_44F130((int)&g_GameData);",
     "  sub_44F130((int)&g_GameData);"),

    ("  CGameData_Load((int)&g_GameData, 4);",
     "  CGameData_Load((int)&g_GameData, 4);"),

    # Cast (type)ptr -> ptr->Method()
    ("  CRenderTarget::Destroy((CRenderTarget *)ptr);",
     "  ptr->Destroy();"),

    # Assignment
    ("  v5 = CScreenMode::GetWidth(&g_DisplayConfig);",
     "  v5 = g_DisplayConfig.GetWidth();"),

    ("  result = gbEffectMgr::NewRenderEffect(pMgr, aGlow, 0);",
     "  result = pMgr->NewRenderEffect(aGlow, 0);"),

    # if() containing call
    ("  if ( !GRPinput::Create(&stru_BFAD70, hInstance, (int)v5, 0) )",
     "  if ( !stru_BFAD70.Create(hInstance, (int)v5, 0) )"),

    # Constructor call: Class::Class(&obj) -> NOT converted
    ("  OpenBaseFile::OpenBaseFile(&v32);",
     "  OpenBaseFile::OpenBaseFile(&v32);"),

    # &obj.member -> NOT converted (not this, it's member address)
    ("  sub_53C5A0(&g_DisplayConfig.m_nFlags, 1);",
     "  sub_53C5A0(&g_DisplayConfig.m_nFlags, 1);"),

    # Complex: nested call in args (should preserve)
    ("  Logger::Write(&g_Logger, \"%s %s\", aV104, aDate);",
     "  g_Logger.Write(\"%s %s\", aV104, aDate);"),

    # Don't touch signatures
    ("int __thiscall GRPinput::SetMode(GRPinput *this, int mode)",
     "int __thiscall GRPinput::SetMode(GRPinput *this, int mode)"),
]


def test():
    print("Running tests...")
    passed = 0
    failed = 0
    for input_line, expected in TEST_CASES:
        result = transform_line(input_line)
        if result == expected:
            passed += 1
            print(f"  PASS: {input_line.strip()[:70]}")
        else:
            failed += 1
            print(f"  FAIL: {input_line.strip()[:70]}")
            print(f"    Expected: {expected.strip()}")
            print(f"    Got:      {result.strip()}")

    print(f"\n{passed}/{passed+failed} tests passed")
    if failed:
        print(f"{failed} FAILED")
    return failed == 0


if __name__ == '__main__':
    if '--test' in sys.argv:
        success = test()
        sys.exit(0 if success else 1)

    if '--input' in sys.argv:
        idx = sys.argv.index('--input')
        input_path = sys.argv[idx + 1]

        # Load thiscall database
        decomp_dir = 'asm/pal3/decomp'
        if os.path.isdir(decomp_dir):
            load_thiscall_db(decomp_dir)
            print(f"Loaded {len(THISCALL_FUNCS)} thiscall functions", file=sys.stderr)

        with open(input_path, 'r', encoding='utf-8') as f:
            if input_path.endswith('.json'):
                d = json.load(f)
                code = d['decompiled_c']
            else:
                code = f.read()

        result = transform_code(code)

        if '--output' in sys.argv:
            out_idx = sys.argv.index('--output')
            out_path = sys.argv[out_idx + 1]
            with open(out_path, 'w', encoding='utf-8') as f:
                f.write(result)
            print(f"Written to {out_path}", file=sys.stderr)
        else:
            print(result)
    else:
        print(__doc__)
