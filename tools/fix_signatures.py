#!/usr/bin/env python3

import json
import re
import argparse
from pathlib import Path
from datetime import datetime


def parse_signature(sig):
    sig = sig.strip()

    match = re.match(r'^(.+?)\s+(__\w+)\s*\((.*)?\)$', sig)
    if match:
        return_type = match.group(1).strip()
        convention = match.group(2).strip()
        params_str = match.group(3) or ""
    else:
        match = re.match(r'^(.+?)\s*\((.*)?\)$', sig)
        if match:
            return_type = match.group(1).strip()
            convention = None
            params_str = match.group(2) or ""
        else:
            raise ValueError(f"Cannot parse signature: {sig}")

    params = []
    if params_str.strip():
        parts = []
        paren_depth = 0
        current = []

        for char in params_str:
            if char == ',' and paren_depth == 0:
                parts.append(''.join(current).strip())
                current = []
            else:
                if char == '(':
                    paren_depth += 1
                elif char == ')':
                    paren_depth -= 1
                current.append(char)

        if current:
            parts.append(''.join(current).strip())

        for part in parts:
            part = part.strip()
            if not part:
                continue

            tokens = part.rsplit(None, 1)
            if len(tokens) == 2:
                param_type, param_name = tokens
                if param_name.startswith('*'):
                    param_type = param_type + ' *'
                    param_name = param_name[1:]
                params.append({"type": param_type, "name": param_name})
            else:
                params.append({"type": part, "name": ""})

    return {
        "return_type": return_type,
        "convention": convention,
        "params": params
    }


def rebuild_signature(parsed):
    param_strs = []
    for param in parsed["params"]:
        if param["name"]:
            ptype = param['type']
            if ptype.endswith('*') or ptype.endswith('**'):
                param_strs.append(f"{ptype}{param['name']}")
            else:
                param_strs.append(f"{ptype} {param['name']}")
        else:
            param_strs.append(param["type"])

    params_joined = ", ".join(param_strs)

    if parsed["convention"]:
        return f"{parsed['return_type']} {parsed['convention']}({params_joined})"
    else:
        return f"{parsed['return_type']}({params_joined})"


def extract_class_from_function_name(name):
    if '<' in name or '>' in name or '$' in name:
        return None

    if name.startswith('?'):
        match = re.match(r'\?\w+@(\w+)@@', name)
        if match:
            return match.group(1)
        return None

    if '::' in name:
        parts = name.split('::')
        if len(parts) >= 2:
            return parts[0]

    return None


def fix_this_type_in_file(json_path, dry_run=True):
    with open(json_path, 'r') as f:
        data = json.load(f)

    changes = []

    for address, info in data.items():
        signature = info.get("signature", "")
        name = info.get("name", "")

        if "__thiscall" not in signature:
            continue

        parsed = parse_signature(signature)

        if not parsed["params"] or parsed["params"][0]["type"] != "int" or parsed["params"][0]["name"] != "this":
            continue

        class_name = extract_class_from_function_name(name)
        if not class_name:
            continue

        new_type = f"{class_name} *"
        old_sig = signature
        parsed["params"][0]["type"] = new_type
        new_sig = rebuild_signature(parsed)

        changes.append({
            "address": address,
            "name": name,
            "old_signature": old_sig,
            "new_signature": new_sig,
            "class_name": class_name
        })

        if not dry_run:
            data[address]["signature"] = new_sig

    if not dry_run and changes:
        with open(json_path, 'w') as f:
            json.dump(data, f, indent=2)

    return changes


def demangle_msvc_params(mangled):
    """
    Decode MSVC mangled name to extract class, method, return type, and parameter types.
    Returns: {"class_name": "...", "method_name": "...", "return_type": "...", "param_types": [...]}
    or None if not a valid MSVC mangled name.
    """
    if not mangled or not mangled.startswith('?'):
        return None

    # Simple type mappings
    type_map = {
        'X': 'void', 'D': 'char', 'E': 'unsigned char',
        'F': 'short', 'G': 'unsigned short',
        'H': 'int', 'I': 'unsigned int',
        'J': 'long', 'K': 'unsigned long',
        'M': 'float', 'N': 'double', '_N': 'bool'
    }

    # Handle constructor/destructor
    # Format: ??0Class@@... (constructor) or ??1Class@@... (destructor)
    ctor_dtor_match = re.match(r'\?\?([0-9])(\w+)@@', mangled)
    if ctor_dtor_match:
        ctor_dtor = ctor_dtor_match.group(1)
        class_name = ctor_dtor_match.group(2)
        if ctor_dtor == '0':
            method_name = class_name  # constructor
        elif ctor_dtor == '1':
            method_name = '~' + class_name  # destructor
        else:
            return None

        # For constructor/destructor, return type is always void
        # and parameters start after @@ qualifier
        parts = mangled.split('@@')
        if len(parts) < 2:
            return None

        type_part = parts[1]
        if not type_part or len(type_part) < 3:
            return None

        # Skip qualifier (QAE/UAE/etc - 3 chars) and @ before params
        type_part = type_part[3:]
        if type_part and type_part[0] == '@':
            type_part = type_part[1:]

        return_type = 'void'
    else:
        # Regular method: ?Method@Class@@...
        match = re.match(r'\?(\w+)@(\w+)@@', mangled)
        if not match:
            return None

        method_name = match.group(1)
        class_name = match.group(2)

        # Find the type encoding part (after @@)
        parts = mangled.split('@@')
        if len(parts) < 2:
            return None

        type_part = parts[1]
        if not type_part or len(type_part) < 3:
            return None

        # Skip qualifier (QAE/IAE/UAE/etc - 3 chars)
        type_part = type_part[3:]
        return_type = None

    # Decode types
    def decode_type(s, idx):
        """Decode a single type, return (type_str, next_idx)"""
        if idx >= len(s):
            return None, idx

        c = s[idx]

        # Simple types
        if c in type_map:
            return type_map[c], idx + 1

        # bool special case
        if idx + 1 < len(s) and s[idx:idx+2] == '_N':
            return 'bool', idx + 2

        # Pointer
        if c == 'P':
            idx += 1
            if idx >= len(s):
                return None, idx

            # PA = pointer, PAV = class pointer, PAU = struct pointer
            modifier = s[idx]
            idx += 1

            if modifier == 'A':
                # Simple pointer
                base_type, idx = decode_type(s, idx)
                if base_type:
                    return base_type + ' *', idx
            elif modifier == 'E' and idx < len(s) and s[idx] == 'A':
                # Reference (PAE -> reference, but rare)
                idx += 1
                base_type, idx = decode_type(s, idx)
                if base_type:
                    return base_type + ' &', idx

            return None, idx

        # Class (V) or Struct (U)
        if c in ('V', 'U'):
            idx += 1
            # Extract name until @ delimiter
            name_end = s.find('@', idx)
            if name_end == -1:
                return None, len(s)
            name = s[idx:name_end]
            # Skip trailing @@ or @
            idx = name_end + 1
            while idx < len(s) and s[idx] == '@':
                idx += 1
            return name + ' *' if c == 'V' else name + ' *', idx

        # Backreference (0-9)
        if c.isdigit():
            # This refers to a previously seen class name
            # For simplicity, we'll just skip it
            return None, idx + 1

        # End marker
        if c == '@' or c == 'Z':
            return None, idx + 1

        return None, idx + 1

    # Decode return type (unless it's a constructor/destructor)
    if return_type is None:
        return_type, idx = decode_type(type_part, 0)
        if not return_type:
            return_type = 'void'
    else:
        idx = 0

    # Remaining types are parameters
    param_types = []
    while idx < len(type_part):
        if type_part[idx] in ('@', 'Z'):
            break
        # X after @ means no parameters (e.g., @XZ for void parameter list)
        if type_part[idx] == 'X' and (idx + 1 >= len(type_part) or type_part[idx + 1] == 'Z'):
            break
        param_type, idx = decode_type(type_part, idx)
        if param_type:
            param_types.append(param_type)
        else:
            # If we can't decode, stop
            break

    return {
        "class_name": class_name,
        "method_name": method_name,
        "return_type": return_type,
        "param_types": param_types
    }


def is_generic_type(type_str):
    """Check if a type is generic (int, void*, etc) and should be improved."""
    type_str = type_str.strip()
    # Generic types we want to replace
    generic_types = ['int', 'void *', 'void*', 'char *', 'char*', 'unsigned int', 'long']
    return type_str in generic_types


def cross_ref_pal3a(pal3_funcs_path, pal3a_funcs_path, dry_run=True):
    """
    Cross-reference PAL3 functions with PAL3A to improve parameter types.
    """
    with open(pal3_funcs_path, 'r') as f:
        pal3_data = json.load(f)

    with open(pal3a_funcs_path, 'r') as f:
        pal3a_data = json.load(f)

    # Build PAL3A lookup by Class::Method name
    pal3a_lookup = {}
    for func in pal3a_data.get('functions', []):
        name = func.get('name', '')
        mangled = func.get('mangled', '')
        if name and mangled:
            pal3a_lookup[name] = mangled

    changes = []

    for address, info in pal3_data.items():
        pal3_name = info.get("name", "")
        pal3_sig = info.get("signature", "")

        if not pal3_name or not pal3_sig:
            continue

        # Check if we have matching PAL3A function
        if pal3_name not in pal3a_lookup:
            continue

        # Demangle PAL3A function to get parameter types
        pal3a_mangled = pal3a_lookup[pal3_name]
        demangled = demangle_msvc_params(pal3a_mangled)

        if not demangled or not demangled.get('param_types'):
            continue

        # Parse PAL3 signature
        try:
            parsed = parse_signature(pal3_sig)
        except:
            continue

        pal3_params = parsed["params"]
        pal3a_params = demangled["param_types"]

        # Check if parameter counts match (excluding 'this' for thiscall)
        pal3_param_count = len(pal3_params)
        if "__thiscall" in pal3_sig and pal3_params:
            pal3_param_count -= 1  # Exclude 'this'

        if pal3_param_count != len(pal3a_params):
            continue

        # Try to improve parameter types
        improved = False
        new_params = list(pal3_params)

        start_idx = 1 if "__thiscall" in pal3_sig and pal3_params else 0

        for i in range(start_idx, len(pal3_params)):
            pal3_type = pal3_params[i]["type"]
            pal3a_idx = i - start_idx

            if pal3a_idx >= len(pal3a_params):
                break

            pal3a_type = pal3a_params[pal3a_idx]

            # Only replace if PAL3 type is generic and PAL3A type is more specific
            if is_generic_type(pal3_type) and not is_generic_type(pal3a_type):
                new_params[i] = {"type": pal3a_type, "name": pal3_params[i]["name"]}
                improved = True

        if improved:
            old_sig = pal3_sig
            parsed["params"] = new_params
            new_sig = rebuild_signature(parsed)

            changes.append({
                "address": address,
                "name": pal3_name,
                "old_signature": old_sig,
                "new_signature": new_sig,
                "pal3a_mangled": pal3a_mangled
            })

            if not dry_run:
                pal3_data[address]["signature"] = new_sig

    if not dry_run and changes:
        with open(pal3_funcs_path, 'w') as f:
            json.dump(pal3_data, f, indent=2)

    return changes


def write_change_log(changes, changelog_path, phase="1.1"):
    today = datetime.now().strftime("%Y-%m-%d")

    if phase == "1.1":
        entry = f"\n### [{today}] Phase 1.1: int this → ClassName *this ({len(changes)} functions)\n"
        entry += f"- **变更**: {len(changes)} 个 __thiscall 函数的 this 参数从 int 修正为 ClassName *\n"
        entry += f"- **置信度**: 95\n"
        entry += f"- **证据**:\n"
        entry += f"  1. [A] __thiscall 调用约定要求 ECX=this，参数类型必为类指针\n"
        entry += f"  2. [B] 函数名 ClassName:: 前缀匹配\n"
        entry += f"- **函数列表**: {len(changes)} 个函数已修正\n"
    elif phase == "1.2":
        entry = f"\n### [{today}] Phase 1.2: PAL3A cross-reference ({len(changes)} functions)\n"
        entry += f"- **变更**: {len(changes)} 个函数通过 PAL3A 反编译签名改进参数类型\n"
        entry += f"- **置信度**: 70\n"
        entry += f"- **证据**:\n"
        entry += f"  1. [A] PAL3A 官方 PDB 包含完整类型信息\n"
        entry += f"  2. [B] 函数名完全匹配，参数个数一致\n"
        entry += f"  3. [C] 仅替换 PAL3 中的泛化类型 (int/void*) 为 PAL3A 的具体类型\n"
        entry += f"- **函数列表**: {len(changes)} 个函数已改进\n"

    for change in changes[:10]:
        entry += f"  - {change['address']}: {change['name']}\n"

    if len(changes) > 10:
        entry += f"  - ... ({len(changes) - 10} more)\n"

    with open(changelog_path, 'a') as f:
        f.write(entry)


def main():
    parser = argparse.ArgumentParser(description="Fix function signatures in annotations")
    subparsers = parser.add_subparsers(dest="command", help="Subcommands")

    fix_parser = subparsers.add_parser("fix-this-type", help="Fix int this → ClassName *this")
    fix_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

    cross_ref_parser = subparsers.add_parser("cross-ref-pal3a", help="Cross-reference with PAL3A to improve parameter types")
    cross_ref_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

    args = parser.parse_args()

    project_root = Path(__file__).parent.parent
    functions_json = project_root / "pipeline/data/annotations/functions.json"
    changelog = project_root / "pipeline/data/annotations/CHANGE_LOG.md"

    if args.command == "fix-this-type":
        changes = fix_this_type_in_file(functions_json, dry_run=not args.apply)

        if not changes:
            print("No functions need fixing.")
            return

        print(f"Found {len(changes)} functions to fix:")
        for change in changes:
            print(f"  {change['address']}: {change['name']}")
            print(f"    {change['old_signature']}")
            print(f"    → {change['new_signature']}")

        if args.apply:
            write_change_log(changes, changelog, phase="1.1")
            print(f"\n✓ Applied changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")

    elif args.command == "cross-ref-pal3a":
        pal3a_funcs = project_root / "asm/pal3a/func_bytes_dump.json"

        if not pal3a_funcs.exists():
            print(f"Error: PAL3A data not found at {pal3a_funcs}")
            return

        changes = cross_ref_pal3a(functions_json, pal3a_funcs, dry_run=not args.apply)

        if not changes:
            print("No functions improved from PAL3A cross-reference.")
            return

        print(f"Found {len(changes)} functions to improve from PAL3A:")
        for change in changes[:20]:
            print(f"  {change['address']}: {change['name']}")
            print(f"    {change['old_signature']}")
            print(f"    → {change['new_signature']}")

        if len(changes) > 20:
            print(f"  ... ({len(changes) - 20} more)")

        if args.apply:
            write_change_log(changes, changelog, phase="1.2")
            print(f"\n✓ Applied {len(changes)} changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")

    else:
        parser.print_help()


if __name__ == "__main__":
    main()
