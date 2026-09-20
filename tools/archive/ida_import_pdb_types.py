"""
IDAPython Script: Import PDB Types (Enums and Structs)

Phase 2, Step 2 of PAL3A IDA Quality Fix Pipeline

Imports class/struct/enum types from PDB export into IDA database so Hex-Rays
can resolve member accesses like `*(DWORD*)(this+N)` into `this->member`.

Input:
  - asm/pal3a/pdb_export.json (1057 classes, 351 enums)

Actions:
  1. Import enums (filter out std::/templates)
  2. Import structs (forward declare all, then define sorted by size)
  3. Mark class methods for re-decompilation (ida_hexrays.mark_cfunc_dirty)

Output:
  - Log: tools/ida/_logs/fix_types_log.txt
  - Modified IDA database with new types

Usage:
  IDA > File > Script File > ida_import_pdb_types.py
"""

import os
import re
import sys
import json
import builtins
import idc
import ida_funcs
import ida_hexrays

# Import shared module
try:
    import ida_common
except ImportError:
    SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
    sys.path.insert(0, SCRIPT_DIR)
    import ida_common

# Constants
LOG_FILE = os.path.join(ida_common.LOG_DIR, "fix_types_log.txt")
PDB_EXPORT_PATH = ida_common.PDB_EXPORT

# Type size estimates (for padding calculation)
TYPE_SIZES = {
    'char': 1, 'uchar': 1, 'unsigned char': 1, 'BYTE': 1, 'bool': 1,
    'short': 2, 'ushort': 2, 'unsigned short': 2, 'WORD': 2, '__int16': 2,
    'int': 4, 'uint': 4, 'unsigned int': 4, 'long': 4, 'ulong': 4,
    'unsigned long': 4, 'float': 4, 'DWORD': 4, 'BOOL': 4, '__int32': 4,
    'double': 8, '__int64': 8, 'unsigned __int64': 8,
}

# Basic type mappings (PDB -> C)
BASIC_TYPE_MAP = {
    'void': 'void',
    'int': 'int',
    'uint': 'unsigned int',
    'long': 'long',
    'ulong': 'unsigned long',
    'short': 'short',
    'ushort': 'unsigned short',
    'char': 'char',
    'uchar': 'unsigned char',
    'float': 'float',
    'double': 'double',
    'bool': 'bool',
    'BOOL': 'int',
    'BYTE': 'unsigned char',
    'WORD': 'unsigned short',
    'DWORD': 'unsigned long',
    'HWND': 'HWND__*',
    'HANDLE': 'void*',
    'LPCSTR': 'const char*',
    'LPSTR': 'char*',
    'LPCWSTR': 'const wchar_t*',
    'LPWSTR': 'wchar_t*',
    'LPVOID': 'void*',
    'LPDWORD': 'unsigned long*',
    'HMODULE': 'HINSTANCE__*',
    'HINSTANCE': 'HINSTANCE__*',
    'HDC': 'HDC__*',
    'HRESULT': 'long',
    '__int8': 'char',
    '__int16': 'short',
    '__int32': 'int',
    '__int64': 'long long',
    'unsigned __int64': 'unsigned long long',
}


def pdb_type_to_c(type_str, known_structs):
    """
    Convert PDB type string to C type declaration.

    Args:
        type_str: PDB type string (e.g., "class Foo *", "char[260]",
                  "gbPrintFont[5] *", "ulong[3]")
        known_structs: Set of known struct/class names

    Returns:
        str: C type declaration
    """
    if not type_str:
        return "void*"

    type_str = type_str.strip()

    # Handle "Type[N] *" pattern (pointer to array / array pointer)
    # e.g., "gbPrintFont[5] *" -> "gbPrintFont *" (treat as pointer to first element)
    # e.g., "gbTexture[6] *" -> "gbTexture *"
    arr_ptr_match = re.match(r'^(.+)\[\d+\]\s*\*$', type_str)
    if arr_ptr_match:
        base = arr_ptr_match.group(1).strip()
        base = re.sub(r'^(class|struct)\s+', '', base)
        base_c = pdb_type_to_c(base, known_structs)
        if base_c == "void*":
            return "void*"
        return f"{base_c} *"

    # Handle array types (e.g., "char[260]", "ulong[3]")
    array_match = re.match(r'^(.+)\[(\d+)\]$', type_str)
    if array_match:
        base_type = array_match.group(1).strip()
        array_size = array_match.group(2)
        base_c_type = pdb_type_to_c(base_type, known_structs)
        # Don't create arrays of void*
        if base_c_type == "void*":
            return f"int[{array_size}]"
        return f"{base_c_type}[{array_size}]"

    # Handle pointer types (ends with " *" or " **")
    if type_str.endswith(' *') or type_str.endswith(' **'):
        # Count pointer depth
        base = type_str
        stars = ''
        while base.endswith(' *'):
            base = base[:-2].strip()
            stars += '*'

        # Strip class/struct/enum prefix
        base = re.sub(r'^(class|struct|enum)\s+', '', base)

        # Handle template/complex types -> void*
        if '<' in base or '::' in base:
            return "void" + stars

        # Recurse on base
        base_c = pdb_type_to_c(base, known_structs)
        if base_c == "void*":
            return "void" + stars
        # Avoid double-pointer from recursion
        if base_c.endswith('*'):
            return base_c  # already a pointer
        return f"{base_c} " + stars

    # Strip class/struct/enum prefix
    type_str = re.sub(r'^(class|struct|enum)\s+', '', type_str)

    # Check basic type map first
    if type_str in BASIC_TYPE_MAP:
        return BASIC_TYPE_MAP[type_str]

    # Handle enums (treat as int) - including named enums like CURSOR_TYPE
    if '::__unnamed' in type_str or type_str.startswith('enum '):
        return "int"

    # Handle templates (treat as byte array placeholder)
    if '<' in type_str:
        return "int"

    # Handle std:: types (treat as int)
    if type_str.startswith('std::'):
        return "int"

    # If it's a known struct, use it directly
    if type_str in known_structs:
        return type_str

    # Simple identifier that might be an enum or type we haven't imported
    if type_str.replace('_', '').isalnum() and not type_str[0:1].isdigit():
        return type_str

    # Unknown type -> void*
    return "void*"


def sanitize_member_name(name):
    """
    Sanitize member name for C declaration.

    Args:
        name: Original member name

    Returns:
        str: Sanitized member name
    """
    # Replace non-alphanumeric chars with underscore
    sanitized = re.sub(r'[^a-zA-Z0-9_]', '_', name)
    # Prefix with f_ if starts with digit
    if sanitized and sanitized[0].isdigit():
        sanitized = f"f_{sanitized}"
    # Ensure not empty
    if not sanitized:
        sanitized = "field"
    return sanitized


def estimate_type_size(c_type, known_struct_sizes=None):
    """
    Estimate size of a C type in bytes.

    Args:
        c_type: C type string
        known_struct_sizes: dict of struct_name -> size (optional)

    Returns:
        int: Estimated size in bytes
    """
    # Remove pointer (any depth)
    if c_type.endswith('*'):
        return 4  # Pointer size on x86

    # Handle array
    array_match = re.match(r'^(.+)\[(\d+)\]$', c_type)
    if array_match:
        base_type = array_match.group(1).strip()
        array_size = int(array_match.group(2))
        base_size = estimate_type_size(base_type, known_struct_sizes)
        return base_size * array_size

    # Check known sizes
    if c_type in TYPE_SIZES:
        return TYPE_SIZES[c_type]

    # Check known struct sizes
    if known_struct_sizes and c_type in known_struct_sizes:
        return known_struct_sizes[c_type]

    # Unknown type (assume int-sized)
    return 4


def build_struct_decl(cls, known_structs, known_struct_sizes=None):
    """
    Build C struct declaration from PDB class data.

    Args:
        cls: Class dict from PDB export
        known_structs: Set of known struct/class names
        known_struct_sizes: dict of name -> size for known structs

    Returns:
        str: C struct declaration, or None if invalid
    """
    name = cls['name']
    size = cls['size']
    data_members = cls.get('data_members', [])

    if size <= 0 or not data_members:
        return None

    # Sort members by offset
    sorted_members = sorted(data_members, key=lambda m: m['offset'])

    # Build member declarations
    lines = [f"#pragma pack(push, 1)", f"struct {name} {{"]
    current_offset = 0

    for i, member in enumerate(sorted_members):
        member_offset = member['offset']
        member_name = sanitize_member_name(member['name'])
        member_type_str = member['type']

        # Skip members at invalid offsets
        if member_offset < current_offset:
            continue

        # Insert padding for gaps
        if member_offset > current_offset:
            gap_size = member_offset - current_offset
            lines.append(f"  char _gap_{current_offset:X}[{gap_size}];")
            current_offset = member_offset

        # Convert type
        c_type = pdb_type_to_c(member_type_str, known_structs)

        # For std::vector and other STL types used by value,
        # compute actual size from gap to next member (or struct end)
        if c_type == 'int' and ('<' in member_type_str or member_type_str.startswith('std::')):
            # Determine actual member size from next member offset or struct size
            if i + 1 < len(sorted_members):
                next_offset = sorted_members[i + 1]['offset']
            else:
                next_offset = size
            actual_size = next_offset - member_offset
            if actual_size > 4:
                # Replace with byte array of correct size
                c_type = f"char[{actual_size}]"

        # Separate array suffix
        array_suffix = ""
        base_type = c_type
        array_match = re.match(r'^(.+)(\[\d+\])$', c_type)
        if array_match:
            base_type = array_match.group(1)
            array_suffix = array_match.group(2)

        lines.append(f"  {base_type} {member_name}{array_suffix};")

        # Update current offset
        member_size = estimate_type_size(c_type, known_struct_sizes)
        current_offset = member_offset + member_size

    # Add trailing padding to reach declared size
    if current_offset < size:
        trailing_pad = size - current_offset
        lines.append(f"  char _pad_{current_offset:X}[{trailing_pad}];")

    lines.append("};")
    lines.append("#pragma pack(pop)")
    return "\n".join(lines)


def filter_valid_enums(enums):
    """
    Filter PDB enums to keep only valid ones for import.

    Args:
        enums: List of enum dicts from PDB export

    Returns:
        list: Filtered enum dicts
    """
    valid = []
    for enum in enums:
        name = enum['name']
        # Skip std:: types
        if name.startswith('std::'):
            continue
        # Skip templates
        if '<' in name:
            continue
        # Skip namespaced (except class-scoped)
        if '::' in name and not '::__unnamed' in name:
            continue
        valid.append(enum)
    return valid


def filter_valid_classes(classes):
    """
    Filter PDB classes to keep only valid ones for import.

    Args:
        classes: List of class dicts from PDB export

    Returns:
        list: Filtered class dicts
    """
    valid = []
    for cls in classes:
        name = cls['name']
        size = cls['size']

        # Skip std:: types
        if name.startswith('std::'):
            continue
        # Skip templates
        if '<' in name:
            continue
        # Skip zero-size
        if size <= 0:
            continue
        # Skip if no data members
        if not cls.get('data_members'):
            continue

        valid.append(cls)
    return valid


def import_enums(enums, log):
    """
    Import enums into IDA database.

    Args:
        enums: List of enum dicts
        log: Logging function

    Returns:
        (success_count, failure_count)
    """
    log("\n=== Phase A: Import Enums ===\n")

    success = 0
    failure = 0
    failure_samples = []

    for enum in enums:
        name = enum['name']
        values = enum.get('values', {})

        if not values:
            continue

        # Build enum declaration
        lines = [f"enum {name} {{"]
        for key, val in values.items():
            lines.append(f"  {key} = {val},")
        lines.append("};")
        decl = "\n".join(lines)

        # Try to parse
        result = idc.parse_decls(decl, idc.PT_TYP)
        if result == 0:
            success += 1
        else:
            failure += 1
            if len(failure_samples) < 5:
                failure_samples.append(name)

    log(f"Enums imported: {success}/{len(enums)} success, {failure} failures")
    if failure_samples:
        log(f"Failure samples: {', '.join(failure_samples)}")

    return (success, failure)


def topo_sort_classes(classes):
    """
    Topological sort: structs that are referenced by-value come first.

    Args:
        classes: List of class dicts

    Returns:
        list: Sorted class dicts (dependencies first)
    """
    name_set = set(c['name'] for c in classes)
    by_name = {c['name']: c for c in classes}

    # Build dependency graph: cls depends on types used by value (not pointer)
    deps = {}
    for cls in classes:
        name = cls['name']
        needed = set()
        for m in cls.get('data_members', []):
            m_type = m.get('type', '')
            # Strip class/struct prefix
            clean = re.sub(r'^(class|struct)\s+', '', m_type).strip()
            # By-value reference (no pointer, no array-pointer)
            if '*' not in clean and clean in name_set and clean != name:
                needed.add(clean)
            # Array of struct by value: "TypeName[N]"
            arr = re.match(r'^(\w+)\[\d+\]$', clean)
            if arr and arr.group(1) in name_set and arr.group(1) != name:
                needed.add(arr.group(1))
        deps[name] = needed

    # Kahn's algorithm
    in_degree = {n: 0 for n in name_set}
    for n, d in deps.items():
        for dep in d:
            if dep in name_set:
                pass  # dep is needed by n
    # in_degree[n] = number of deps n has that are in our set
    in_degree = {n: len(deps.get(n, set()) & name_set) for n in name_set}

    # reverse: if A depends on B, then B is depended-on by A
    reverse = {n: set() for n in name_set}
    for n, d in deps.items():
        for dep in d:
            if dep in reverse:
                reverse[dep].add(n)

    queue = sorted([n for n in name_set if in_degree[n] == 0],
                   key=lambda x: by_name[x].get('size', 0))
    result = []
    visited = set()

    while queue:
        n = queue.pop(0)
        if n in visited:
            continue
        visited.add(n)
        result.append(by_name[n])
        for dependent in sorted(reverse.get(n, set())):
            in_degree[dependent] -= 1
            if in_degree[dependent] <= 0 and dependent not in visited:
                queue.append(dependent)

    # Remaining (circular deps) - add by size
    for cls in sorted(classes, key=lambda c: c.get('size', 0)):
        if cls['name'] not in visited:
            result.append(cls)

    return result


def import_structs(classes, log):
    """
    Import structs into IDA database.

    Args:
        classes: List of class dicts
        log: Logging function

    Returns:
        (success_count, failure_count, known_structs_set)
    """
    log("\n=== Phase B: Import Structs ===\n")

    known_structs = set()
    known_struct_sizes = {}

    # Step 1: Forward declare all
    log(f"Forward declaring {len(classes)} structs...")
    for cls in classes:
        name = cls['name']
        decl = f"struct {name};"
        idc.parse_decls(decl, idc.PT_TYP)
        known_structs.add(name)
        known_struct_sizes[name] = cls.get('size', 4)

    # Step 2: Topological sort (dependencies first)
    sorted_classes = topo_sort_classes(classes)
    log(f"Topological sort done: {len(sorted_classes)} classes")

    # Step 3: Import actual definitions (two passes for circular deps)
    log(f"Importing struct definitions (pass 1)...")
    success = 0
    failure = 0
    failed_classes = []
    failure_samples = []

    for cls in sorted_classes:
        name = cls['name']
        decl = build_struct_decl(cls, known_structs, known_struct_sizes)

        if not decl:
            failure += 1
            continue

        result = idc.parse_decls(decl, idc.PT_TYP)
        if result == 0:
            success += 1
        else:
            failed_classes.append(cls)
            if len(failure_samples) < 10:
                failure_samples.append(name)

    # Pass 2: retry failures (deps may have been resolved in pass 1)
    if failed_classes:
        log(f"Retrying {len(failed_classes)} failures (pass 2)...")
        retry_ok = 0
        for cls in failed_classes:
            name = cls['name']
            decl = build_struct_decl(cls, known_structs, known_struct_sizes)
            if decl and idc.parse_decls(decl, idc.PT_TYP) == 0:
                retry_ok += 1
                success += 1
        failure = len(failed_classes) - retry_ok
        log(f"Pass 2 recovered: {retry_ok}")

    log(f"Structs imported: {success}/{len(classes)} success, {failure} failures")
    if failure_samples:
        log(f"Failure samples (first 10): {', '.join(failure_samples)}")

    return (success, failure, known_structs)


def mark_class_methods_dirty(functions, known_structs, log):
    """
    Mark class methods for re-decompilation.

    Args:
        functions: List of function dicts from PDB export
        known_structs: Set of known struct/class names
        log: Logging function

    Returns:
        int: Number of functions marked dirty
    """
    log("\n=== Phase C: Mark Class Methods for Re-decompilation ===\n")

    marked = 0
    skipped_no_func = 0
    skipped_no_class = 0

    for func in functions:
        # Check if function has class field matching known_structs
        class_name = func.get('class', '')
        if not class_name or class_name not in known_structs:
            skipped_no_class += 1
            continue

        # Parse address
        addr_str = func.get('address', '')
        if not addr_str:
            continue

        try:
            addr = int(addr_str, 16)
        except ValueError:
            continue

        # Check if address is in .text section
        if not ida_common.is_in_text(addr):
            continue

        # Check if function exists in IDA
        ida_func = ida_funcs.get_func(addr)
        if not ida_func:
            skipped_no_func += 1
            continue

        # Check if this is the function start
        if ida_func.start_ea != addr:
            continue

        # Mark for re-decompilation
        try:
            ida_hexrays.mark_cfunc_dirty(addr)
            marked += 1
        except Exception:
            pass

    log(f"Marked {marked} class methods for re-decompilation")
    log(f"Skipped: {skipped_no_class} (no matching class), {skipped_no_func} (no IDA function)")

    return marked


def main():
    """Main entry point"""
    # Setup logging
    log, save_log, _ = ida_common.make_logger(LOG_FILE)

    log("=" * 80)
    log("PAL3A IDA Pipeline - Phase 2 Step 2: Import PDB Types")
    log("=" * 80)

    # Check if running in pipeline mode
    if getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        log("\n[Pipeline Mode] Script will exit IDA after completion.\n")

    # Load PDB export
    log(f"\nLoading PDB export: {PDB_EXPORT_PATH}")
    try:
        with open(PDB_EXPORT_PATH, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)
    except Exception as e:
        log(f"ERROR: Failed to load PDB export: {e}")
        save_log()
        return

    enums = pdb_data.get('enums', [])
    classes = pdb_data.get('classes', [])
    functions = pdb_data.get('functions', [])

    log(f"Loaded: {len(classes)} classes, {len(enums)} enums, {len(functions)} functions")

    # Filter valid types
    valid_enums = filter_valid_enums(enums)
    valid_classes = filter_valid_classes(classes)

    log(f"Filtered: {len(valid_classes)} valid classes, {len(valid_enums)} valid enums")

    # Phase A: Import enums
    enum_success, enum_failure = import_enums(valid_enums, log)

    # Phase B: Import structs
    struct_success, struct_failure, known_structs = import_structs(valid_classes, log)

    # Phase C: Mark class methods dirty
    marked_count = mark_class_methods_dirty(functions, known_structs, log)

    # Summary
    log("\n" + "=" * 80)
    log("Summary:")
    log(f"  Enums:   {enum_success}/{len(valid_enums)} imported")
    log(f"  Structs: {struct_success}/{len(valid_classes)} imported")
    log(f"  Methods: {marked_count} marked for re-decompilation")
    log("=" * 80)

    # Save database
    log("\nSaving IDA database...")
    idc.save_database(idc.get_idb_path())
    log("Database saved.")

    # Save log
    save_log()
    log(f"\nLog saved to: {LOG_FILE}")

    # Exit if running in pipeline
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == "__main__":
    main()
