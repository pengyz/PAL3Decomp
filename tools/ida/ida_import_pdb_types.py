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
        type_str: PDB type string (e.g., "class Foo *", "char[260]")
        known_structs: Set of known struct/class names

    Returns:
        str: C type declaration
    """
    if not type_str:
        return "void*"

    type_str = type_str.strip()

    # Handle array types (e.g., "char[260]")
    array_match = re.match(r'^(.+)\[(\d+)\]$', type_str)
    if array_match:
        base_type = array_match.group(1).strip()
        array_size = array_match.group(2)
        base_c_type = pdb_type_to_c(base_type, known_structs)
        return f"{base_c_type}[{array_size}]"

    # Handle pointer types
    if type_str.endswith('*'):
        base_type = type_str[:-1].strip()
        # Strip class/struct prefix
        base_type = re.sub(r'^(class|struct|enum)\s+', '', base_type)
        # Handle template/complex types
        if '<' in base_type or '::' in base_type:
            return "void*"
        base_c_type = pdb_type_to_c(base_type, known_structs)
        if base_c_type == "void*":
            return "void*"
        return f"{base_c_type}*"

    # Strip class/struct/enum prefix
    type_str = re.sub(r'^(class|struct|enum)\s+', '', type_str)

    # Check basic type map first
    if type_str in BASIC_TYPE_MAP:
        return BASIC_TYPE_MAP[type_str]

    # Handle enums (treat as int)
    if '::__unnamed' in type_str or type_str.startswith('enum '):
        return "int"

    # Handle templates (treat as int/void*)
    if '<' in type_str:
        return "int"

    # Handle std:: types (treat as int)
    if type_str.startswith('std::'):
        return "int"

    # If it's a known struct, use it directly
    if type_str in known_structs:
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


def estimate_type_size(c_type):
    """
    Estimate size of a C type in bytes.

    Args:
        c_type: C type string

    Returns:
        int: Estimated size in bytes
    """
    # Remove pointer
    if c_type.endswith('*'):
        return 4  # Pointer size

    # Handle array
    array_match = re.match(r'^(.+)\[(\d+)\]$', c_type)
    if array_match:
        base_type = array_match.group(1).strip()
        array_size = int(array_match.group(2))
        base_size = estimate_type_size(base_type)
        return base_size * array_size

    # Check known sizes
    if c_type in TYPE_SIZES:
        return TYPE_SIZES[c_type]

    # Unknown type (assume pointer/int)
    return 4


def build_struct_decl(cls, known_structs):
    """
    Build C struct declaration from PDB class data.

    Args:
        cls: Class dict from PDB export
        known_structs: Set of known struct/class names

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
    lines = [f"struct {name} {{"]
    current_offset = 0

    for member in sorted_members:
        member_offset = member['offset']
        member_name = sanitize_member_name(member['name'])
        member_type_str = member['type']

        # Insert padding for gaps
        if member_offset > current_offset:
            gap_size = member_offset - current_offset
            lines.append(f"  char _gap_{current_offset:X}[{gap_size}];")
            current_offset = member_offset

        # Convert type
        c_type = pdb_type_to_c(member_type_str, known_structs)

        # Separate array suffix
        array_suffix = ""
        base_type = c_type
        array_match = re.match(r'^(.+)(\[\d+\])$', c_type)
        if array_match:
            base_type = array_match.group(1)
            array_suffix = array_match.group(2)

        lines.append(f"  {base_type} {member_name}{array_suffix};")

        # Update current offset
        member_size = estimate_type_size(c_type)
        current_offset = member_offset + member_size

    # Add trailing padding to reach declared size
    if current_offset < size:
        trailing_pad = size - current_offset
        lines.append(f"  char _pad_{current_offset:X}[{trailing_pad}];")

    lines.append("};")
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

    # Step 1: Forward declare all
    log(f"Forward declaring {len(classes)} structs...")
    for cls in classes:
        name = cls['name']
        decl = f"struct {name};"
        idc.parse_decls(decl, idc.PT_TYP)
        known_structs.add(name)

    # Step 2: Sort by size (smaller first for dependency order)
    sorted_classes = sorted(classes, key=lambda c: c['size'])

    # Step 3: Import actual definitions
    log(f"Importing {len(sorted_classes)} struct definitions...")
    success = 0
    failure = 0
    failure_samples = []

    for cls in sorted_classes:
        name = cls['name']
        decl = build_struct_decl(cls, known_structs)

        if not decl:
            failure += 1
            continue

        result = idc.parse_decls(decl, idc.PT_TYP)
        if result == 0:
            success += 1
        else:
            failure += 1
            if len(failure_samples) < 10:
                failure_samples.append(name)

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
