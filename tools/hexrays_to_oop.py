"""
Hex-Rays 输出后处理：将 Class::Method(this, args) 转为 OOP 形式

Hex-Rays 对 thiscall 的输出格式:
  gbMatrixStack::Push(v2);              -> v2->Push();
  GRPinput_SetMode(&ppvOut, 0x40000000) -> ppvOut.SetMode(0x40000000);
  sub_402270(&ppvOut, 0, 0, w, h)       -> ppvOut.sub_402270(0, 0, w, h);  (if thiscall known)

规则:
  1. Class::Method(ptr, args)  -> ptr->Method(args)
  2. Class::Method(&obj, args) -> obj.Method(args)
  3. func(&obj, args) where func is known thiscall -> obj.func(args)

输入: Hex-Rays 反编译文本 (从 decomp JSON 的 decompiled_c 字段)
输出: 转换后的 C++ 代码

用法:
  python tools/hexrays_to_oop.py --input asm/pal3/decomp/xxx.json --output src/pal3/xxx.cpp
  python tools/hexrays_to_oop.py --test  # 运行自测
"""

import re
import json
import sys
import os
from pathlib import Path


# Known thiscall functions: address -> (class_name, method_name)
# These are identified from IDA's own analysis (signature field contains __thiscall)
KNOWN_THISCALL = {}  # populated from decomp JSONs


def load_thiscall_db(decomp_dir):
    """From decomp JSONs, build a map of known thiscall functions."""
    db = {}
    for f in Path(decomp_dir).glob("*.json"):
        if f.name.startswith("_"):
            continue
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
            sig = d.get('signature', '')
            name = d.get('name', '')
            if '__thiscall' in sig and name:
                # Extract class::method if available
                if '::' in name:
                    parts = name.split('::', 1)
                    db[name] = (parts[0], parts[1])
                else:
                    db[name] = (None, name)
        except:
            pass
    return db


def transform_class_method_call(line, thiscall_db):
    """
    Transform Class::Method(this_expr, args) -> this_expr->Method(args)
    Transform Class::Method(&obj, args) -> obj.Method(args)
    """
    # Pattern: ClassName::MethodName(expr, ...)
    # Match: word::word( followed by first arg
    pattern = r'(\w+)::(\w+)\(\s*([^,)]+)\s*(?:,\s*(.*))?\)'

    def replacer(m):
        cls = m.group(1)
        method = m.group(2)
        first_arg = m.group(3).strip()
        rest_args = m.group(4)

        if first_arg.startswith('&'):
            # &obj -> obj.Method(rest)
            obj = first_arg[1:]
            if rest_args:
                return f'{obj}.{method}({rest_args})'
            else:
                return f'{obj}.{method}()'
        elif first_arg.startswith('(') and '*' in first_arg:
            # (Type *)expr -> expr->Method(rest) with cast
            return m.group(0)  # too complex, leave as-is
        else:
            # ptr -> ptr->Method(rest)
            if rest_args:
                return f'{first_arg}->{method}({rest_args})'
            else:
                return f'{first_arg}->{method}()'

    return re.sub(pattern, replacer, line)


def transform_named_thiscall(line, thiscall_db):
    """
    Transform NamedFunc(&obj, args) -> obj.NamedFunc(args)  [if in thiscall_db]
    Transform NamedFunc(ptr, args) -> ptr->NamedFunc(args)
    """
    # Pattern: known_func_name(&expr, ...) or known_func_name(expr, ...)
    for func_name, (cls, method) in thiscall_db.items():
        if func_name not in line:
            continue
        # Match: func_name(first_arg, rest...)
        pattern = rf'\b{re.escape(func_name)}\(\s*([^,)]+)\s*(?:,\s*(.*))?\)'

        def replacer(m):
            first_arg = m.group(1).strip()
            rest_args = m.group(2)
            display_method = method if cls else func_name

            if first_arg.startswith('&'):
                obj = first_arg[1:]
                if rest_args:
                    return f'{obj}.{display_method}({rest_args})'
                else:
                    return f'{obj}.{display_method}()'
            else:
                if rest_args:
                    return f'{first_arg}->{display_method}({rest_args})'
                else:
                    return f'{first_arg}->{display_method}()'

        line = re.sub(pattern, replacer, line, count=1)
    return line


def transform_code(code, thiscall_db=None):
    """Transform entire decompiled function code."""
    if thiscall_db is None:
        thiscall_db = {}

    lines = code.split('\n')
    result = []
    for line in lines:
        # Skip function signature line and comments
        if line.strip().startswith('//') or '__thiscall' in line:
            result.append(line)
            continue
        # Apply Class::Method transform
        line = transform_class_method_call(line, thiscall_db)
        # Apply named thiscall transform
        if thiscall_db:
            line = transform_named_thiscall(line, thiscall_db)
        result.append(line)
    return '\n'.join(result)


def test():
    """Self-test with known patterns."""
    cases = [
        # Class::Method(ptr, args) -> ptr->Method(args)
        ("  gbMatrixStack::Push(v2);", "  v2->Push();"),
        ("  gbMatrixStack::Pop(v2);", "  v2->Pop();"),
        ("  gbCamera::SetLookAt(v4, v5, v6, v7);", "  v4->SetLookAt(v5, v6, v7);"),
        # Class::Method(&obj, args) -> obj.Method(args)
        ("  GRPinput::SetMode(&ppvOut, 0x40000000);", "  ppvOut.SetMode(0x40000000);"),
        # Class::Method(ptr) -> ptr->Method() (no extra args)
        ("  gbSceneGraph::End(v2);", "  v2->End();"),
    ]

    print("Running self-tests...")
    passed = 0
    for input_line, expected in cases:
        result = transform_class_method_call(input_line, {})
        if result == expected:
            passed += 1
            print(f"  PASS: {input_line.strip()}")
        else:
            print(f"  FAIL: {input_line.strip()}")
            print(f"    Expected: {expected.strip()}")
            print(f"    Got:      {result.strip()}")

    print(f"\n{passed}/{len(cases)} tests passed")
    return passed == len(cases)


if __name__ == '__main__':
    if '--test' in sys.argv:
        success = test()
        sys.exit(0 if success else 1)

    if '--input' in sys.argv:
        idx = sys.argv.index('--input')
        input_path = sys.argv[idx + 1]

        with open(input_path, 'r', encoding='utf-8') as f:
            if input_path.endswith('.json'):
                d = json.load(f)
                code = d['decompiled_c']
            else:
                code = f.read()

        # Load thiscall database
        decomp_dir = 'asm/pal3/decomp'
        if os.path.isdir(decomp_dir):
            thiscall_db = load_thiscall_db(decomp_dir)
            print(f"Loaded {len(thiscall_db)} thiscall functions", file=sys.stderr)
        else:
            thiscall_db = {}

        result = transform_code(code, thiscall_db)

        if '--output' in sys.argv:
            out_idx = sys.argv.index('--output')
            out_path = sys.argv[out_idx + 1]
            with open(out_path, 'w', encoding='utf-8') as f:
                f.write(result)
            print(f"Written to {out_path}", file=sys.stderr)
        else:
            print(result)
    else:
        print("Usage:")
        print("  python tools/hexrays_to_oop.py --test")
        print("  python tools/hexrays_to_oop.py --input <file.json|file.c> [--output <file.cpp>]")
