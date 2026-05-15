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


def fix_this_type_in_funcs(funcs_data):
    """
    Fix int this → ClassName *this in function signatures (in-memory).

    Args:
        funcs_data: Dictionary of functions (address -> info)

    Returns:
        List of changes made
    """
    changes = []

    for address, info in funcs_data.items():
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

        funcs_data[address]["signature"] = new_sig

    return changes


def fix_this_type_in_file(json_path, dry_run=True):
    """
    Fix int this → ClassName *this in function signatures (file version).

    Args:
        json_path: Path to functions.json
        dry_run: If True, don't modify the file

    Returns:
        List of changes made
    """
    with open(json_path, 'r') as f:
        data = json.load(f)

    changes = fix_this_type_in_funcs(data)

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


def cross_ref_pal3a_in_funcs(pal3_data, pal3a_data):
    """
    Cross-reference PAL3 functions with PAL3A to improve parameter types (in-memory).

    Args:
        pal3_data: Dictionary of PAL3 functions (address -> info)
        pal3a_data: Dictionary with 'functions' key containing PAL3A function list

    Returns:
        List of changes made
    """

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

            pal3_data[address]["signature"] = new_sig

    return changes


def cross_ref_pal3a(pal3_funcs_path, pal3a_funcs_path, dry_run=True):
    """
    Cross-reference PAL3 functions with PAL3A to improve parameter types (file version).

    Args:
        pal3_funcs_path: Path to PAL3 functions.json
        pal3a_funcs_path: Path to PAL3A func_bytes_dump.json
        dry_run: If True, don't modify the file

    Returns:
        List of changes made
    """
    with open(pal3_funcs_path, 'r') as f:
        pal3_data = json.load(f)

    with open(pal3a_funcs_path, 'r') as f:
        pal3a_data = json.load(f)

    changes = cross_ref_pal3a_in_funcs(pal3_data, pal3a_data)

    if not dry_run and changes:
        with open(pal3_funcs_path, 'w') as f:
            json.dump(pal3_data, f, indent=2)

    return changes


def load_decomp_bodies():
    """
    Load all decomp JSON files and return {address: decompiled_c} mapping.

    Returns:
        dict: Mapping from address (e.g., "0x00401234") to decompiled C code.
    """
    project_root = Path(__file__).parent.parent
    decomp_dir = project_root / "asm" / "pal3" / "decomp"
    bodies = {}

    for f in decomp_dir.glob("*.json"):
        try:
            data = json.loads(f.read_text(encoding="utf-8"))
            addr = data.get("address", "")
            body = data.get("decompiled_c", "")
            if addr and body:
                bodies[addr] = body
        except:
            continue

    return bodies


def is_trivial_cast_type(type_str):
    """Check if a type is trivial/generic and should be skipped."""
    type_str = type_str.strip()
    trivial_types = [
        'void', 'char', 'int', 'unsigned', 'long',
        '_DWORD', '_BYTE', '_WORD', '_QWORD',
        'DWORD', 'BYTE', 'WORD'
    ]
    return type_str in trivial_types


def infer_void_star_types_in_funcs(funcs_data, decomp_bodies):
    """
    Infer actual types for void* parameters by analyzing cast patterns (in-memory).

    Args:
        funcs_data: Dictionary of functions (address -> info)
        decomp_bodies: Dict mapping address to decompiled_c

    Returns:
        List of changes made
    """
    changes = []

    for address, info in funcs_data.items():
        signature = info.get("signature", "")
        name = info.get("name", "")

        if "void *" not in signature:
            continue

        # Get function body
        body = decomp_bodies.get(address, "")
        if not body:
            continue

        # Parse signature
        try:
            parsed = parse_signature(signature)
        except:
            continue

        # Find void* parameters (skip 'this')
        for i, param in enumerate(parsed["params"]):
            param_type = param["type"]
            param_name = param["name"]

            # Skip 'this' parameter
            if param_name == "this":
                continue

            # Only process void* parameters
            if param_type not in ["void *", "void*"]:
                continue

            if not param_name:
                continue

            # Search for cast patterns: (ClassName *)param_name
            cast_pattern = re.compile(r'\((\w+(?:\s*\*+)?)\s*\)' + re.escape(param_name) + r'\b')
            casts = cast_pattern.findall(body)

            if not casts:
                continue

            # Count cast occurrences, filter out trivial types
            cast_counts = {}
            for cast_type in casts:
                cast_type = cast_type.strip()
                # Remove pointer markers for type checking
                base_type = cast_type.rstrip('*').strip()
                if is_trivial_cast_type(base_type):
                    continue
                cast_counts[cast_type] = cast_counts.get(cast_type, 0) + 1

            if not cast_counts:
                continue

            # Pick the most common cast type
            most_common = max(cast_counts.items(), key=lambda x: x[1])
            inferred_type = most_common[0]

            # Ensure it ends with * if not already
            if not inferred_type.endswith('*'):
                inferred_type += ' *'

            # Update parameter type
            old_sig = signature
            parsed["params"][i]["type"] = inferred_type
            new_sig = rebuild_signature(parsed)

            changes.append({
                "address": address,
                "name": name,
                "param_name": param_name,
                "old_type": param_type,
                "new_type": inferred_type,
                "cast_count": most_common[1],
                "old_signature": old_sig,
                "new_signature": new_sig
            })

            funcs_data[address]["signature"] = new_sig

            # Only fix one parameter per function per run (for safety)
            break


    return changes


def infer_void_star_types(functions_json_path, decomp_bodies, dry_run=True):
    """
    Infer actual types for void* parameters by analyzing cast patterns (file version).

    Args:
        functions_json_path: Path to functions.json
        decomp_bodies: Dict mapping address to decompiled_c
        dry_run: If True, don't modify the file

    Returns:
        List of changes made
    """
    with open(functions_json_path, 'r') as f:
        data = json.load(f)

    changes = infer_void_star_types_in_funcs(data, decomp_bodies)

    if not dry_run and changes:
        with open(functions_json_path, 'w') as f:
            json.dump(data, f, indent=2)

    return changes


def infer_int_pointer_types_in_funcs(funcs_data, decomp_bodies):
    """
    Infer that int parameters are actually pointers by analyzing cast patterns (in-memory).

    Args:
        funcs_data: Dictionary of functions (address -> info)
        decomp_bodies: Dict mapping address to decompiled_c

    Returns:
        List of changes made
    """
    changes = []

    for address, info in funcs_data.items():
        signature = info.get("signature", "")
        name = info.get("name", "")

        # Get function body
        body = decomp_bodies.get(address, "")
        if not body:
            continue

        # Parse signature
        try:
            parsed = parse_signature(signature)
        except:
            continue

        # Find int parameters (skip 'this')
        for i, param in enumerate(parsed["params"]):
            param_type = param["type"]
            param_name = param["name"]

            # Skip 'this' parameter
            if param_name == "this":
                continue

            # Only process int parameters
            if param_type != "int":
                continue

            if not param_name:
                continue

            # Pattern 1: (Type *)param - direct cast
            # Pattern 2: (Type *)(param + offset) - cast with offset/arithmetic
            # Pattern 3: ((Type *)param)-> - dereference (subset of pattern 1)
            # Match: (Type *) followed by param or (param...)
            pattern1 = re.compile(r'\((\w+)\s*\*+\s*\)' + re.escape(param_name) + r'\b')
            pattern2 = re.compile(r'\((\w+)\s*\*+\s*\)\s*\(' + re.escape(param_name) + r'\b')

            casts1 = pattern1.findall(body)
            casts2 = pattern2.findall(body)
            all_casts = casts1 + casts2

            if not all_casts:
                continue

            # Count cast occurrences, filter out trivial types
            cast_counts = {}
            for cast_type in all_casts:
                cast_type = cast_type.strip()
                if is_trivial_cast_type(cast_type):
                    continue
                cast_counts[cast_type] = cast_counts.get(cast_type, 0) + 1

            if not cast_counts:
                continue

            # Pick the most common cast type
            most_common = max(cast_counts.items(), key=lambda x: x[1])

            # Only accept if cast appears >= 2 times (confidence 80)
            if most_common[1] < 2:
                continue

            inferred_type = most_common[0] + ' *'

            # Update parameter type
            old_sig = signature
            parsed["params"][i]["type"] = inferred_type
            new_sig = rebuild_signature(parsed)

            changes.append({
                "address": address,
                "name": name,
                "param_name": param_name,
                "old_type": param_type,
                "new_type": inferred_type,
                "cast_count": most_common[1],
                "old_signature": old_sig,
                "new_signature": new_sig
            })

            funcs_data[address]["signature"] = new_sig

            # Only fix one parameter per function per run (for safety)
            break

    return changes


def infer_int_pointer_types(functions_json_path, decomp_bodies, dry_run=True):
    """
    Infer that int parameters are actually pointers by analyzing cast patterns (file version).

    Args:
        functions_json_path: Path to functions.json
        decomp_bodies: Dict mapping address to decompiled_c
        dry_run: If True, don't modify the file

    Returns:
        List of changes made
    """
    with open(functions_json_path, 'r') as f:
        data = json.load(f)

    changes = infer_int_pointer_types_in_funcs(data, decomp_bodies)

    if not dry_run and changes:
        with open(functions_json_path, 'w') as f:
            json.dump(data, f, indent=2)

    return changes


def simplify_class_name(type_str):
    """
    Simplify a class/type name for Hungarian notation parameter naming.

    Args:
        type_str: Type string (e.g., "gbMatrixStack *", "CEffect *", "const char *")

    Returns:
        Simplified name (e.g., "Stack", "Effect", "Name")
    """
    # Remove pointer markers and const/volatile qualifiers
    base = type_str.replace('*', '').replace('const', '').replace('volatile', '').strip()

    # Remove common prefixes
    prefixes = ['gb', 'C', 'tag', 'Arc', 'UI']
    for prefix in prefixes:
        if base.startswith(prefix) and len(base) > len(prefix):
            remainder = base[len(prefix):]
            # Only remove if remainder starts with uppercase (CEffect -> Effect, not char -> har)
            if remainder and remainder[0].isupper():
                return remainder

    return base


def get_semantic_param_name(param_type, index):
    """
    Generate a semantic parameter name based on Hungarian notation.

    Args:
        param_type: Parameter type string (e.g., "float", "gbMatrixStack *", "const char *")
        index: Parameter index for disambiguation (1-based)

    Returns:
        Semantic parameter name (e.g., "fVal1", "pStack1", "pszName1")
    """
    param_type = param_type.strip()

    # String types
    if param_type in ('const char *', 'const char*', 'LPCSTR'):
        return f"pszName{index}" if index > 1 else "pszName"
    if param_type in ('char *', 'char*', 'LPSTR'):
        return f"pszBuf{index}" if index > 1 else "pszBuf"

    # Pointer types (class/struct)
    if '*' in param_type:
        # Extract class name
        base = param_type.replace('*', '').replace('const', '').replace('volatile', '').strip()

        # Check if base type is a primitive type
        primitive_pointers = {
            'float': 'pfVal',
            'int': 'pnVal',
            'unsigned int': 'pdwVal',
            'unsigned long': 'pdwVal',
            'long': 'pnVal',
            'short': 'pnVal',
            'unsigned short': 'pwVal',
            'unsigned char': 'pbyVal',
            'void': 'pData',
            'DWORD': 'pdwVal',
            'BYTE': 'pbyVal',
            'WORD': 'pwVal',
            'BOOL': 'pbFlag',
            'bool': 'pbFlag',
            # MSVC-specific types
            '__int8': 'pnVal',
            'unsigned __int8': 'pbyVal',
            '__int16': 'pnVal',
            'unsigned __int16': 'pwVal',
            '__int32': 'pnVal',
            'unsigned __int32': 'pdwVal',
            '__int64': 'pnVal',
            'unsigned __int64': 'pdwVal',
        }

        if base in primitive_pointers:
            base_name = primitive_pointers[base]
            return f"{base_name}{index}" if index > 1 else base_name

        # Otherwise it's a class/struct pointer
        simplified = simplify_class_name(base)
        suffix = f"{index}" if index > 1 else ""
        return f"p{simplified}{suffix}"

    # Basic types
    type_map = {
        'float': 'fVal',
        'int': 'nVal',
        'unsigned int': 'dwVal',
        'DWORD': 'dwVal',
        'unsigned long': 'dwVal',
        'BOOL': 'bFlag',
        'bool': 'bFlag',
        'BYTE': 'byVal',
        'unsigned char': 'byVal',
        'WORD': 'wVal',
        'unsigned short': 'wVal',
    }

    if param_type in type_map:
        base_name = type_map[param_type]
        return f"{base_name}{index}" if index > 1 else base_name

    # Fallback for unknown types
    return f"pData{index}" if index > 1 else "pData"


def rename_params_in_funcs(funcs_data):
    """
    Rename generic parameter names (a1, a2, ...) to semantic Hungarian-style names (in-memory).

    Args:
        funcs_data: Dictionary of functions (address -> info)

    Returns:
        List of changes made
    """
    changes = []
    generic_param_pattern = re.compile(r'^[a-z]\d+$')

    for address, info in funcs_data.items():
        signature = info.get("signature", "")
        name = info.get("name", "")

        if not signature:
            continue

        # Parse signature
        try:
            parsed = parse_signature(signature)
        except:
            continue

        # Track changes for this function
        param_renames = []
        type_counts = {}  # Track count per type for disambiguation

        for i, param in enumerate(parsed["params"]):
            param_name = param["name"]
            param_type = param["type"]

            # Skip 'this' parameter
            if param_name == "this":
                continue

            # Skip if not a generic name (a1, a2, ...)
            if not param_name or not generic_param_pattern.match(param_name):
                continue

            # Count occurrences of this type for disambiguation
            type_counts[param_type] = type_counts.get(param_type, 0) + 1
            type_index = type_counts[param_type]

            # Generate semantic name
            new_name = get_semantic_param_name(param_type, type_index)

            # Update parameter
            old_name = param_name
            parsed["params"][i]["name"] = new_name
            param_renames.append({
                "old": old_name,
                "new": new_name,
                "type": param_type
            })

        # If any parameters were renamed, record the change
        if param_renames:
            old_sig = signature
            new_sig = rebuild_signature(parsed)

            changes.append({
                "address": address,
                "name": name,
                "old_signature": old_sig,
                "new_signature": new_sig,
                "renames": param_renames
            })

            funcs_data[address]["signature"] = new_sig

    return changes


def rename_params_in_file(json_path, dry_run=True):
    """
    Rename generic parameter names (a1, a2, ...) to semantic Hungarian-style names (file version).

    Args:
        json_path: Path to functions.json
        dry_run: If True, don't modify the file

    Returns:
        List of changes made
    """
    with open(json_path, 'r') as f:
        data = json.load(f)

    changes = rename_params_in_funcs(data)

    if not dry_run and changes:
        with open(json_path, 'w') as f:
            json.dump(data, f, indent=2)

    return changes


def find_functions_for_file(functions_data, cpp_filename):
    """
    Find all functions belonging to a class based on the cpp filename.

    Args:
        functions_data: Dict of function data from functions.json
        cpp_filename: Name of the cpp file (e.g., "CCBAI.cpp")

    Returns:
        List of (address, info) tuples for matching functions
    """
    # Extract class name from filename (e.g., "CCBAI.cpp" -> "CCBAI")
    class_name = Path(cpp_filename).stem

    # Find all functions that belong to this class
    matching_funcs = []
    for address, info in functions_data.items():
        name = info.get("name", "")

        # Match Class::Method pattern
        if name.startswith(f"{class_name}::"):
            matching_funcs.append((address, info))
            continue

        # Match mangled names: ?Method@Class@@...
        if name.startswith('?') and f"@{class_name}@@" in name:
            matching_funcs.append((address, info))
            continue

    return matching_funcs


def write_change_log(changes, changelog_path, phase_label, description, confidence):
    """
    Write a change log entry.

    Args:
        changes: List of change records
        changelog_path: Path to CHANGE_LOG.md
        phase_label: e.g., "Phase 1.1: int this → ClassName *this"
        description: List of evidence/description lines
        confidence: Confidence score (integer)
    """
    today = datetime.now().strftime("%Y-%m-%d")

    entry = f"\n### [{today}] {phase_label} ({len(changes)} functions)\n"
    entry += f"- **变更**: {len(changes)} 个函数的签名已改进\n"
    entry += f"- **置信度**: {confidence}\n"
    entry += f"- **证据**:\n"
    for i, desc in enumerate(description, 1):
        entry += f"  {i}. {desc}\n"
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

    cross_ref_parser = subparsers.add_parser("cross-ref-pal3a", help="Cross-reference with PAL3A to improve parameter types")
    cross_ref_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

    infer_void_parser = subparsers.add_parser("infer-void-star", help="Infer void* parameter types from cast patterns")
    infer_void_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

    infer_int_parser = subparsers.add_parser("infer-int-params", help="Infer int parameters that are actually pointers")
    infer_int_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

    rename_params_parser = subparsers.add_parser("rename-params", help="Rename generic parameter names (a1, a2, ...) to semantic Hungarian-style names")
    rename_params_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

    fix_file_parser = subparsers.add_parser("fix-file", help="Run all Phase 1 fixes on functions for a specific .cpp file")
    fix_file_parser.add_argument("cpp_file", help="Name of the cpp file (e.g., CCBAI.cpp)")
    fix_file_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

    run_all_parser = subparsers.add_parser("run-all", help="Run all Phase 1 fixes sequentially")
    run_all_parser.add_argument("--apply", action="store_true", help="Apply changes to files")

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
            write_change_log(
                changes, changelog,
                phase_label="Phase 1.1: int this → ClassName *this",
                description=[
                    "[A] __thiscall 调用约定要求 ECX=this，参数类型必为类指针",
                    "[B] 函数名 ClassName:: 前缀匹配"
                ],
                confidence=95
            )
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
            write_change_log(
                changes, changelog,
                phase_label="Phase 1.2: PAL3A cross-reference",
                description=[
                    "[A] PAL3A 官方 PDB 包含完整类型信息",
                    "[B] 函数名完全匹配，参数个数一致",
                    "[C] 仅替换 PAL3 中的泛化类型 (int/void*) 为 PAL3A 的具体类型"
                ],
                confidence=70
            )
            print(f"\n✓ Applied {len(changes)} changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")

    elif args.command == "infer-void-star":
        print("Loading decomp bodies...")
        decomp_bodies = load_decomp_bodies()
        print(f"Loaded {len(decomp_bodies)} function bodies")

        changes = infer_void_star_types(functions_json, decomp_bodies, dry_run=not args.apply)

        if not changes:
            print("No void* parameters to infer.")
            return

        print(f"Found {len(changes)} void* parameters to infer:")
        for change in changes[:20]:
            print(f"  {change['address']}: {change['name']}")
            print(f"    Parameter '{change['param_name']}': {change['old_type']} → {change['new_type']}")
            print(f"    Cast count: {change['cast_count']}")

        if len(changes) > 20:
            print(f"  ... ({len(changes) - 20} more)")

        if args.apply:
            write_change_log(
                changes, changelog,
                phase_label="Phase 1.3: void* parameter type inference",
                description=[
                    "[A] 函数体中显式 cast 为特定类型",
                    "[B] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)",
                    "[C] 选取出现频率最高的 cast 目标类型"
                ],
                confidence=80
            )
            print(f"\n✓ Applied {len(changes)} changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")

    elif args.command == "infer-int-params":
        print("Loading decomp bodies...")
        decomp_bodies = load_decomp_bodies()
        print(f"Loaded {len(decomp_bodies)} function bodies")

        changes = infer_int_pointer_types(functions_json, decomp_bodies, dry_run=not args.apply)

        if not changes:
            print("No int parameters inferred as pointers.")
            return

        print(f"Found {len(changes)} int parameters inferred as pointers:")
        for change in changes[:20]:
            print(f"  {change['address']}: {change['name']}")
            print(f"    Parameter '{change['param_name']}': {change['old_type']} → {change['new_type']}")
            print(f"    Cast count: {change['cast_count']}")

        if len(changes) > 20:
            print(f"  ... ({len(changes) - 20} more)")

        if args.apply:
            write_change_log(
                changes, changelog,
                phase_label="Phase 1.4: int parameter pointer inference",
                description=[
                    "[A] 函数体中 int 参数被 cast 为指针类型",
                    "[B] Cast 出现 ≥2 次才接受（置信度 80）",
                    "[C] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)"
                ],
                confidence=80
            )
            print(f"\n✓ Applied {len(changes)} changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")

    elif args.command == "rename-params":
        changes = rename_params_in_file(functions_json, dry_run=not args.apply)

        if not changes:
            print("No generic parameter names found to rename.")
            return

        print(f"Found {len(changes)} functions with generic parameter names:")
        for change in changes[:20]:
            print(f"  {change['address']}: {change['name']}")
            renames_str = ", ".join([f"{r['old']}→{r['new']}" for r in change['renames']])
            print(f"    {renames_str}")

        if len(changes) > 20:
            print(f"  ... ({len(changes) - 20} more)")

        if args.apply:
            write_change_log(
                changes, changelog,
                phase_label="Phase 1.5: Parameter semantic naming",
                description=[
                    "[A] 将泛化参数名 (a1, a2, ...) 替换为语义化的 Hungarian 风格命名",
                    "[B] 保留已有语义名 (如 fAngle, pStack) 和 this 参数",
                    "[C] 根据参数类型应用命名规则 (p前缀指针, f前缀浮点, n前缀整数等)"
                ],
                confidence=60
            )
            print(f"\n✓ Applied {len(changes)} changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")

    elif args.command == "run-all":
        print("=" * 70)
        print("Running all Phase 1 signature fixes")
        print("=" * 70)

        # Load functions.json once
        with open(functions_json, 'r') as f:
            funcs_data = json.load(f)

        # Load PAL3A data for cross-reference
        pal3a_funcs_path = project_root / "asm/pal3a/func_bytes_dump.json"
        if not pal3a_funcs_path.exists():
            print(f"Warning: PAL3A data not found at {pal3a_funcs_path}")
            print("Skipping cross-ref-pal3a step.")
            pal3a_data = None
        else:
            with open(pal3a_funcs_path, 'r') as f:
                pal3a_data = json.load(f)

        # Load decomp bodies for inference steps
        print("\nLoading decomp bodies...")
        decomp_bodies = load_decomp_bodies()
        print(f"Loaded {len(decomp_bodies)} function bodies\n")

        # Track all changes
        all_changes = {}

        # Step 1: fix-this-type
        print("\n[1/5] Running fix-this-type...")
        changes1 = fix_this_type_in_funcs(funcs_data)
        all_changes["fix-this-type"] = changes1
        print(f"      Fixed {len(changes1)} functions")

        # Step 2: cross-ref-pal3a
        print("\n[2/5] Running cross-ref-pal3a...")
        if pal3a_data:
            changes2 = cross_ref_pal3a_in_funcs(funcs_data, pal3a_data)
            all_changes["cross-ref-pal3a"] = changes2
            print(f"      Improved {len(changes2)} functions")
        else:
            all_changes["cross-ref-pal3a"] = []
            print("      Skipped (PAL3A data not available)")

        # Step 3: infer-void-star
        print("\n[3/5] Running infer-void-star...")
        changes3 = infer_void_star_types_in_funcs(funcs_data, decomp_bodies)
        all_changes["infer-void-star"] = changes3
        print(f"      Inferred {len(changes3)} void* parameters")

        # Step 4: infer-int-params
        print("\n[4/5] Running infer-int-params...")
        changes4 = infer_int_pointer_types_in_funcs(funcs_data, decomp_bodies)
        all_changes["infer-int-params"] = changes4
        print(f"      Inferred {len(changes4)} int parameters as pointers")

        # Step 5: rename-params
        print("\n[5/5] Running rename-params...")
        changes5 = rename_params_in_funcs(funcs_data)
        all_changes["rename-params"] = changes5
        print(f"      Renamed parameters in {len(changes5)} functions")

        # Print summary table
        print("\n" + "=" * 70)
        print("Summary")
        print("=" * 70)
        print(f"{'Step':<25} {'Changes':<10}")
        print("-" * 70)
        print(f"{'1. fix-this-type':<25} {len(all_changes['fix-this-type']):<10}")
        print(f"{'2. cross-ref-pal3a':<25} {len(all_changes['cross-ref-pal3a']):<10}")
        print(f"{'3. infer-void-star':<25} {len(all_changes['infer-void-star']):<10}")
        print(f"{'4. infer-int-params':<25} {len(all_changes['infer-int-params']):<10}")
        print(f"{'5. rename-params':<25} {len(all_changes['rename-params']):<10}")
        print("-" * 70)
        total_changes = sum(len(changes) for changes in all_changes.values())
        print(f"{'Total':<25} {total_changes:<10}")
        print("=" * 70)

        # Write to file if --apply
        if args.apply:
            print(f"\nWriting changes to {functions_json}...")
            with open(functions_json, 'w') as f:
                json.dump(funcs_data, f, indent=2)

            # Write change logs for each step
            if all_changes["fix-this-type"]:
                write_change_log(
                    all_changes["fix-this-type"], changelog,
                    phase_label="Phase 1.1: int this → ClassName *this",
                    description=[
                        "[A] __thiscall 调用约定要求 ECX=this，参数类型必为类指针",
                        "[B] 函数名 ClassName:: 前缀匹配"
                    ],
                    confidence=95
                )

            if all_changes["cross-ref-pal3a"]:
                write_change_log(
                    all_changes["cross-ref-pal3a"], changelog,
                    phase_label="Phase 1.2: PAL3A cross-reference",
                    description=[
                        "[A] PAL3A 官方 PDB 包含完整类型信息",
                        "[B] 函数名完全匹配，参数个数一致",
                        "[C] 仅替换 PAL3 中的泛化类型 (int/void*) 为 PAL3A 的具体类型"
                    ],
                    confidence=70
                )

            if all_changes["infer-void-star"]:
                write_change_log(
                    all_changes["infer-void-star"], changelog,
                    phase_label="Phase 1.3: void* parameter type inference",
                    description=[
                        "[A] 函数体中显式 cast 为特定类型",
                        "[B] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)",
                        "[C] 选取出现频率最高的 cast 目标类型"
                    ],
                    confidence=80
                )

            if all_changes["infer-int-params"]:
                write_change_log(
                    all_changes["infer-int-params"], changelog,
                    phase_label="Phase 1.4: int parameter pointer inference",
                    description=[
                        "[A] 函数体中 int 参数被 cast 为指针类型",
                        "[B] Cast 出现 ≥2 次才接受（置信度 80）",
                        "[C] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)"
                    ],
                    confidence=80
                )

            if all_changes["rename-params"]:
                write_change_log(
                    all_changes["rename-params"], changelog,
                    phase_label="Phase 1.5: Parameter semantic naming",
                    description=[
                        "[A] 将泛化参数名 (a1, a2, ...) 替换为语义化的 Hungarian 风格命名",
                        "[B] 保留已有语义名 (如 fAngle, pStack) 和 this 参数",
                        "[C] 根据参数类型应用命名规则 (p前缀指针, f前缀浮点, n前缀整数等)"
                    ],
                    confidence=60
                )

            print(f"✓ Applied {total_changes} changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        else:
            print("\nDry run mode. Use --apply to write changes.")


    elif args.command == "fix-file":
        # Load all functions
        with open(functions_json, 'r') as f:
            all_funcs = json.load(f)

        # Find functions for this file
        matching_funcs = find_functions_for_file(all_funcs, args.cpp_file)

        if not matching_funcs:
            print(f"No functions found for file {args.cpp_file}")
            return

        class_name = Path(args.cpp_file).stem
        print(f"Found {len(matching_funcs)} functions for {args.cpp_file} (class: {class_name})")

        # Create a subset dict for processing
        subset = {addr: dict(info) for addr, info in matching_funcs}

        # Track all changes
        all_changes = {
            "fix-this-type": [],
            "infer-void-star": [],
            "infer-int-params": [],
            "rename-params": []
        }

        # Phase 1: Fix this type
        print(f"\n=== Phase 1: fix-this-type ===")
        changes = fix_this_type_in_funcs(subset)
        all_changes["fix-this-type"] = changes
        if changes:
            print(f"  Fixed {len(changes)} functions")
            for change in changes[:5]:
                print(f"    {change['name']}")
            if len(changes) > 5:
                print(f"    ... and {len(changes) - 5} more")
        else:
            print("  No changes")

        # Phase 2: Infer void* types
        print(f"\n=== Phase 2: infer-void-star ===")
        decomp_bodies = load_decomp_bodies()
        void_star_changes = infer_void_star_types_in_funcs(subset, decomp_bodies)
        all_changes["infer-void-star"] = void_star_changes
        if void_star_changes:
            print(f"  Inferred {len(void_star_changes)} void* parameters")
            for change in void_star_changes[:5]:
                print(f"    {change['name']}: {change['param_name']} → {change['new_type']}")
            if len(void_star_changes) > 5:
                print(f"    ... and {len(void_star_changes) - 5} more")
        else:
            print("  No changes")

        # Phase 3: Infer int pointer types
        print(f"\n=== Phase 3: infer-int-params ===")
        int_param_changes = infer_int_pointer_types_in_funcs(subset, decomp_bodies)
        all_changes["infer-int-params"] = int_param_changes
        if int_param_changes:
            print(f"  Inferred {len(int_param_changes)} int parameters as pointers")
            for change in int_param_changes[:5]:
                print(f"    {change['name']}: {change['param_name']} → {change['new_type']}")
            if len(int_param_changes) > 5:
                print(f"    ... and {len(int_param_changes) - 5} more")
        else:
            print("  No changes")

        # Phase 4: Rename parameters
        print(f"\n=== Phase 4: rename-params ===")
        rename_changes = rename_params_in_funcs(subset)
        all_changes["rename-params"] = rename_changes
        if rename_changes:
            print(f"  Renamed parameters in {len(rename_changes)} functions")
            for change in rename_changes[:5]:
                renames_str = ", ".join([f"{r['old']}→{r['new']}" for r in change['renames']])
                print(f"    {change['name']}: {renames_str}")
            if len(rename_changes) > 5:
                print(f"    ... and {len(rename_changes) - 5} more")
        else:
            print("  No changes")

        # Summary
        total_changes = sum(len(v) for v in all_changes.values())
        print(f"\n=== Summary ===")
        print(f"Total changes: {total_changes}")
        for phase, changes in all_changes.items():
            if changes:
                print(f"  {phase}: {len(changes)}")

        # Apply changes if requested
        if args.apply and total_changes > 0:
            # Merge subset back into all_funcs
            for address, info in subset.items():
                all_funcs[address] = info

            # Write back
            with open(functions_json, 'w') as f:
                json.dump(all_funcs, f, indent=2)

            # Write changelog entries for each phase that had changes
            for phase, changes in all_changes.items():
                if not changes:
                    continue

                phase_labels = {
                    "fix-this-type": f"Phase 1.1: int this → ClassName *this [{class_name}]",
                    "infer-void-star": f"Phase 1.3: void* parameter inference [{class_name}]",
                    "infer-int-params": f"Phase 1.4: int parameter pointer inference [{class_name}]",
                    "rename-params": f"Phase 1.5: Parameter semantic naming [{class_name}]"
                }

                phase_descs = {
                    "fix-this-type": [
                        "[A] __thiscall 调用约定要求 ECX=this，参数类型必为类指针",
                        "[B] 函数名 ClassName:: 前缀匹配"
                    ],
                    "infer-void-star": [
                        "[A] 函数体中显式 cast 为特定类型",
                        "[B] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)",
                        "[C] 选取出现频率最高的 cast 目标类型"
                    ],
                    "infer-int-params": [
                        "[A] 函数体中 int 参数被 cast 为指针类型",
                        "[B] Cast 出现 ≥2 次才接受（置信度 80）",
                        "[C] 跳过泛化类型 (void/char/int/_DWORD/_BYTE)"
                    ],
                    "rename-params": [
                        "[A] 将泛化参数名 (a1, a2, ...) 替换为语义化的 Hungarian 风格命名",
                        "[B] 保留已有语义名 (如 fAngle, pStack) 和 this 参数",
                        "[C] 根据参数类型应用命名规则 (p前缀指针, f前缀浮点, n前缀整数等)"
                    ]
                }

                phase_confidence = {
                    "fix-this-type": 95,
                    "infer-void-star": 80,
                    "infer-int-params": 80,
                    "rename-params": 60
                }

                write_change_log(
                    changes, changelog,
                    phase_label=phase_labels[phase],
                    description=phase_descs[phase],
                    confidence=phase_confidence[phase]
                )

            print(f"\n✓ Applied changes to {functions_json}")
            print(f"✓ Updated {changelog}")
        elif args.apply:
            print("\nNo changes to apply.")
        else:
            print("\nDry run mode. Use --apply to write changes.")



    else:
        parser.print_help()


if __name__ == "__main__":
    main()
