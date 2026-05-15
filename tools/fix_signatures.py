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


def write_change_log(changes, changelog_path):
    today = datetime.now().strftime("%Y-%m-%d")

    entry = f"\n### [{today}] Phase 1.1: int this → ClassName *this ({len(changes)} functions)\n"
    entry += f"- **变更**: {len(changes)} 个 __thiscall 函数的 this 参数从 int 修正为 ClassName *\n"
    entry += f"- **置信度**: 95\n"
    entry += f"- **证据**:\n"
    entry += f"  1. [A] __thiscall 调用约定要求 ECX=this，参数类型必为类指针\n"
    entry += f"  2. [B] 函数名 ClassName:: 前缀匹配\n"
    entry += f"- **函数列表**: {len(changes)} 个函数已修正\n"

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

    args = parser.parse_args()

    if args.command == "fix-this-type":
        project_root = Path(__file__).parent.parent
        functions_json = project_root / "pipeline/data/annotations/functions.json"
        changelog = project_root / "pipeline/data/annotations/CHANGE_LOG.md"

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
            write_change_log(changes, changelog)
            print(f"\n✓ Applied changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
