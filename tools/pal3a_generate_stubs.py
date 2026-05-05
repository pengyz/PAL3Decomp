"""
Batch-generate stub .h and .cpp files for PAL3A from PDB export.

Reads asm/pal3a/pdb_export.json and generates:
  - One .h per source file (class declarations + function signatures)
  - One .cpp per source file (stub function bodies)

Usage:
  python tools/pal3a_generate_stubs.py [--dry-run]
"""
import json
import os
import sys
import re
from collections import defaultdict

INPUT = "asm/pal3a/pdb_export.json"
OUTDIR = "src/pal3a"

# Directory name normalization (Windows case-insensitive merges)
DIR_NORMALIZE = {
    "Combat": "combat",
    "Effect": "effect",
    "GAMEBASE": "gamebase",
    "GameMainUI": "gamemainui",
    "GAMEMAINUI": "gamemainui",
    "GameUI": "gameui",
    "GAMEUI": "gameui",
    "Fight": "fight",
    "UI": "ui",
    "ArcInfo": "arcinfo",
    "CatchGhost": "catchghost",
    "Compose": "compose",
    "Assistant System": "assistant_system",
    "assistant system": "assistant_system",
}

# Files to skip (already implemented or not PAL3A source)
SKIP_PATTERNS = [
    "VisualStudio",
    "VC98",
    "INCLUDE\\\\",
    "INCLUDE/",
    "gbEngine9",
]

# Type sanitization rules
TYPE_REPLACEMENTS = {
    "HWND__": "HWND",
    "HINSTANCE__": "HINSTANCE",
    "HDC__": "HDC",
    "HBITMAP__": "HBITMAP",
    "HMENU__": "HMENU",
    "HICON__": "HICON",
    "HBRUSH__": "HBRUSH",
    "HFONT__": "HFONT",
    "HPEN__": "HPEN",
    "HRGN__": "HRGN",
    "HPALETTE__": "HPALETTE",
    "<NoType>": "void*",
}


def sanitize_type(t, is_member=False):
    """Clean up type strings for valid C++ compilation.
    If is_member=True, this is a data member by value (not a param) so unknown types become int.
    """
    if not t:
        return ""
    if t == "void":
        return "void"
    # Replace known type aliases
    for old, new in TYPE_REPLACEMENTS.items():
        t = t.replace(old, new)
    # Complex STL types -> void*
    if 'std::_Tree<' in t or 'std::_List<' in t or 'std::_Deque<' in t:
        if '*' in t:
            return "void*"
        return "void*"
    # Truncated std:: types (hash endings)
    if 'std::' in t and len(t) > 80:
        if '*' in t:
            return "void*"
        return "void*"
    # SubTask<...> with member function pointers - simplify
    if 'SubTask<' in t and '__thiscall' in t:
        if '*' in t:
            return "void*"
        return "void*"
    # CTaskTpl<...> - simplify
    if 'CTaskTpl<' in t:
        if '*' in t:
            return "void*"
        return "void*"
    # Fix pointer-to-array: "Type[N] *" -> "Type*" (wrong PDB format)
    arr_ptr = re.match(r'^(.+?)\[\d+\]\s*\*$', t)
    if arr_ptr:
        return arr_ptr.group(1).strip() + "*"
    # Fix "Type *[N]" -> "Type**" (array of pointers)
    arr_ptr2 = re.match(r'^(.+?)\s*\*\[\d+\]$', t)
    if arr_ptr2:
        return arr_ptr2.group(1).strip() + "**"
    # Fix "Type[N]" standalone (not as part of bigger expression) -> "Type*"
    arr_alone = re.match(r'^(.+?)\[(\d+)\]$', t)
    if arr_alone and '*' not in t:
        return arr_alone.group(1).strip() + "*"
    # Remove "enum " prefix from return types
    if t.startswith('enum '):
        t = t[5:]
    # Remove "struct " prefix
    if t.startswith('struct '):
        t = t[7:]
    # Remove "class " prefix
    if t.startswith('class '):
        t = t[6:]
    # Remove "virtual " prefix (appears in some demangled return types)
    if t.startswith('virtual '):
        t = t[8:]
    # Nested types (Class::Type) - replace with void* for pointers, int otherwise
    if '::' in t and not t.startswith('std::'):
        if '*' in t:
            return "void*"
        return "int"
    return t


def sanitize_param_str(params_str):
    """Sanitize all types in a parameter string."""
    if not params_str:
        return ""
    # Split on top-level commas (not inside angle brackets)
    parts = []
    depth = 0
    current = ""
    for ch in params_str:
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif ch == ',' and depth == 0:
            parts.append(current.strip())
            current = ""
            continue
        current += ch
    if current.strip():
        parts.append(current.strip())

    sanitized = []
    for part in parts:
        # Split into type and name (last word is the name)
        tokens = part.rsplit(' ', 1)
        if len(tokens) == 2:
            ptype, pname = tokens
            ptype = sanitize_type(ptype)
            sanitized.append(f"{ptype} {pname}")
        else:
            sanitized.append(sanitize_type(part))
    return ", ".join(sanitized)


def normalize_path(pdb_path):
    """Convert PDB source path to local relative path."""
    rel = pdb_path
    for prefix in ['D:\\PAL3A\\PAL3\\', 'd:\\PAL3A\\PAL3\\']:
        if rel.startswith(prefix):
            rel = rel[len(prefix):]
            break

    rel = rel.replace('\\', '/')
    parts = rel.split('/')
    if len(parts) > 1:
        if parts[0] in DIR_NORMALIZE:
            parts[0] = DIR_NORMALIZE[parts[0]]
        else:
            parts[0] = parts[0].lower()
    return '/'.join(parts)


def should_skip(source_path):
    """Check if this source file should be skipped."""
    for pat in SKIP_PATTERNS:
        if pat in source_path:
            return True
    return False


def get_return_default(return_type):
    """Generate default return statement for a type."""
    if not return_type or return_type == "void":
        return ""
    if '*' in return_type:
        return "    return NULL;"
    if return_type in ("int", "long", "short", "DWORD", "UINT", "LONG", "WORD", "BYTE",
                       "unsigned int", "unsigned long", "unsigned short", "ulong", "uint",
                       "ushort", "uchar", "unsigned char"):
        return "    return 0;"
    if return_type in ("BOOL", "bool"):
        return "    return FALSE;"
    if return_type in ("float", "double"):
        return "    return 0.0f;"
    if return_type == "HRESULT":
        return "    return S_OK;"
    # For struct/class types, use brace-initialization
    if return_type in ("gbVec3D", "gbVec2D", "gbVec4D", "gbMatrix4", "gbQuaternion",
                       "gbColorFlt", "gbColorQuad", "D3DXVECTOR3", "D3DXVECTOR2",
                       "D3DXVECTOR4", "D3DXMATRIX", "gbRay", "gbAABBox", "gbOBBox",
                       "gbSphere"):
        return f"    {return_type} _ret = {{0}}; return _ret;"
    # Template types - use default construction
    if '<' in return_type:
        return f"    static {return_type} _ret; return _ret;"
    # Enum types - return 0 cast
    if return_type.startswith('E') and return_type[1:2].isupper():
        return f"    return ({return_type})0;"
    # RECT, POINT etc
    if return_type in ("tagRECT", "tagPOINT", "RECT", "POINT"):
        return f"    {return_type} _ret = {{0}}; return _ret;"
    # Reference returns - use reinterpret_cast on static buffer
    if '&' in return_type:
        base = return_type.replace('&', '').replace('const ', '').strip()
        return f"    static char _buf[256] = {{0}}; return *({base}*)_buf;"
    # Enum-like types (all caps, short names - e.g. GAME_STATE, BOOL)
    if return_type.isupper() and len(return_type) <= 20:
        return f"    return ({return_type})0;"
    # Any other struct/class type (use static local - safe for both classes and structs)
    if return_type[0].isupper() or return_type.startswith('tag'):
        return f"    static {return_type} _ret; memset(&_ret, 0, sizeof(_ret)); return _ret;"
    return "    return 0;"


def make_guard(filename):
    """Generate include guard from filename."""
    base = os.path.splitext(os.path.basename(filename))[0]
    safe = re.sub(r'[^A-Za-z0-9_]', '_', base).upper()
    return f"PAL3A_{safe}_H"


def generate_header(rel_path, class_info, free_funcs, extra_methods=None, class_sizes=None):
    """Generate .h content with class definitions using char _data[] for members."""
    if class_sizes is None:
        class_sizes = {}
    guard = make_guard(rel_path)
    lines = [
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        '#include "pal3a_types.h"',
        "",
    ]

    # Class declarations with placeholder data and method signatures
    for cls_name, info in sorted(class_info.items()):
        size = class_sizes.get(cls_name, 64)
        if size <= 0:
            size = 64
        lines.append(f"class {cls_name} {{")
        lines.append("public:")
        lines.append(f"    char _data[{size}];")
        lines.append("")

        # Method declarations (dedup after sanitization)
        seen_sigs = set()
        for method in info.get("methods", []):
            mname = method["short_name"]
            params = sanitize_param_str(method.get("params_str", ""))
            ret = sanitize_type(method.get("return_type", "void"))
            sig = f"{mname}({params})"
            if sig in seen_sigs:
                continue
            seen_sigs.add(sig)
            if ret:
                lines.append(f"    {ret} {mname}({params});")
            else:
                lines.append(f"    {mname}({params});")

        lines.append("};")
        lines.append("")

    # Free function declarations (dedup after sanitization)
    seen_free = set()
    for func in free_funcs:
        name = func["short_name"]
        params = sanitize_param_str(func.get("params_str", ""))
        ret = sanitize_type(func.get("return_type", "void"))
        sig = f"{name}({params})"
        if sig in seen_free:
            continue
        seen_free.add(sig)
        if ret:
            lines.append(f"{ret} {name}({params});")
        else:
            lines.append(f"void {name}({params});")

    if free_funcs:
        lines.append("")

    lines.append(f"#endif // {guard}")
    return '\n'.join(lines) + '\n'


def generate_source(rel_path, class_info, free_funcs, extra_methods=None):
    """Generate .cpp content."""
    h_name = os.path.splitext(os.path.basename(rel_path))[0] + ".h"
    lines = [
        f'#include "{h_name}"',
        "",
    ]

    # Class method implementations (dedup after sanitization)
    for cls_name, info in sorted(class_info.items()):
        seen_sigs = set()
        for method in info.get("methods", []):
            mname = method["short_name"]
            params = sanitize_param_str(method.get("params_str", ""))
            ret = sanitize_type(method.get("return_type", "void"))
            sig = f"{cls_name}::{mname}({params})"
            if sig in seen_sigs:
                continue
            seen_sigs.add(sig)
            if ret:
                lines.append(f"{ret} {cls_name}::{mname}({params})")
            else:
                lines.append(f"{cls_name}::{mname}({params})")
            lines.append("{")
            lines.append("    /* stub */")
            if ret:
                ret_stmt = get_return_default(ret)
                if ret_stmt:
                    lines.append(ret_stmt)
            lines.append("}")
            lines.append("")

    # Free function implementations (dedup after sanitization)
    seen_free = set()
    for func in free_funcs:
        name = func["short_name"]
        params = sanitize_param_str(func.get("params_str", ""))
        ret = sanitize_type(func.get("return_type", "void"))
        sig = f"{name}({params})"
        if sig in seen_free:
            continue
        seen_free.add(sig)
        if ret:
            lines.append(f"{ret} {name}({params})")
        else:
            lines.append(f"void {name}({params})")
        lines.append("{")
        lines.append("    /* stub */")
        if ret:
            ret_stmt = get_return_default(ret)
            if ret_stmt:
                lines.append(ret_stmt)
        lines.append("}")
        lines.append("")

    # Extra methods (for classes defined in another header)
    if extra_methods:
        for cls_name, method in extra_methods:
            mname = method["short_name"]
            params = sanitize_param_str(method.get("params_str", ""))
            ret = sanitize_type(method.get("return_type", "void"))
            if ret:
                lines.append(f"{ret} {cls_name}::{mname}({params})")
            else:
                lines.append(f"{cls_name}::{mname}({params})")
            lines.append("{")
            lines.append("    /* stub */")
            if ret:
                ret_stmt = get_return_default(ret)
                if ret_stmt:
                    lines.append(ret_stmt)
            lines.append("}")
            lines.append("")

    return '\n'.join(lines) + '\n'


def process_functions(functions, classes_data):
    """Organize functions by source file, separating class methods from free funcs."""
    # Build class info lookup from PDB class data
    class_members = {}
    for cls in classes_data:
        cls_name = cls["name"]
        class_members[cls_name] = {
            "data_members": cls.get("data_members", []),
            "static_members": cls.get("static_members", []),
        }

    # Group functions by source file
    by_source = defaultdict(lambda: {"classes": defaultdict(lambda: {"methods": [], "data_members": []}),
                                      "free_funcs": []})

    seen_methods = set()  # avoid duplicates

    for func in functions:
        src = func.get("source_file", "")
        if not src or should_skip(src):
            continue
        if not ('PAL3A' in src and '.cpp' in src.lower()):
            continue

        rel = normalize_path(src)
        name = func["name"]
        cls_name = func.get("class", "")
        params = func.get("parameters", [])
        params_str = ", ".join(f'{p["type"]} {p["name"]}' for p in params if p.get("type"))

        # Determine short name (without class prefix)
        if cls_name and name.startswith(cls_name + "::"):
            short_name = name[len(cls_name) + 2:]
        elif "::" in name:
            parts = name.rsplit("::", 1)
            cls_name = parts[0]
            short_name = parts[1]
        else:
            short_name = name

        # Skip compiler-generated stuff
        if short_name.startswith('__') or short_name.startswith('`'):
            continue
        if '?' in short_name or '@' in short_name:
            continue
        if '$' in short_name:
            continue
        # Skip operator overloads (cause issues with forward-declared types)
        if short_name.startswith('operator'):
            continue
        # Skip nested classes (SceneObj::Common_State etc.)
        if cls_name and '::' in cls_name:
            continue
        # Skip WinMain (conflicts with Windows API definition)
        if short_name == 'WinMain' and not cls_name:
            continue

        # Get return type from demangled data
        ret_type = func.get("return_type", "")
        if not ret_type:
            ret_type = "void"
        # Constructor/destructor
        if short_name.startswith('~') or short_name == cls_name:
            ret_type = ""

        func_info = {
            "short_name": short_name,
            "full_name": name,
            "params_str": params_str,
            "return_type": ret_type,
            "size": func.get("size", 0),
        }

        method_key = f"{rel}::{name}({params_str})"
        if method_key in seen_methods:
            continue
        seen_methods.add(method_key)

        if cls_name:
            entry = by_source[rel]
            entry["classes"][cls_name]["methods"].append(func_info)
            # Add data members from class definitions
            if cls_name in class_members:
                entry["classes"][cls_name]["data_members"] = class_members[cls_name]["data_members"]
        else:
            by_source[rel]["free_funcs"].append(func_info)

    return by_source


def main():
    dry_run = "--dry-run" in sys.argv

    print(f"Loading {INPUT}...")
    with open(INPUT) as f:
        data = json.load(f)

    functions = data["functions"]
    classes = data.get("classes", [])

    # Build class size lookup
    class_sizes = {cls["name"]: cls.get("size", 64) for cls in classes}

    print(f"Processing {len(functions)} functions...")
    by_source = process_functions(functions, classes)

    print(f"Source files to generate: {len(by_source)}")
    if dry_run:
        print("\n[DRY RUN] Would create:")

    created = 0
    skipped = 0
    # First pass: merge classes that appear in multiple files into their first file
    class_canonical_file = {}  # class_name -> first rel_path
    for rel_path in sorted(by_source.keys()):
        info = by_source[rel_path]
        for cls_name in info["classes"]:
            if cls_name not in class_canonical_file:
                class_canonical_file[cls_name] = rel_path
            else:
                # Merge methods into the canonical file
                canonical = class_canonical_file[cls_name]
                by_source[canonical]["classes"][cls_name]["methods"].extend(
                    info["classes"][cls_name]["methods"])
                # Mark for removal from this file
                info["classes"][cls_name]["methods"] = []

    for rel_path, info in sorted(by_source.items()):
        cpp_path = os.path.join(OUTDIR, rel_path)
        h_path = os.path.splitext(cpp_path)[0] + ".h"

        # Remove empty classes (methods were merged elsewhere)
        class_info = {k: v for k, v in info["classes"].items() if v.get("methods")}
        free_funcs = info["free_funcs"]
        extra_methods = []  # not used anymore after merge approach

        total_methods = sum(len(ci["methods"]) for ci in class_info.values())
        total = total_methods + len(free_funcs)

        if total == 0:
            continue

        if dry_run:
            print(f"  {rel_path}: {len(class_info)} classes, {total} functions")
            created += 2
            continue

        # Skip if file already has real implementation
        if os.path.exists(cpp_path) and os.path.getsize(cpp_path) > 100:
            with open(cpp_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read(500)
                if '/* stub */' not in content and 'stub' not in content.lower():
                    skipped += 1
                    continue

        os.makedirs(os.path.dirname(cpp_path), exist_ok=True)

        # Generate header
        h_content = generate_header(rel_path, class_info, free_funcs, extra_methods, class_sizes)
        with open(h_path, 'w', encoding='utf-8') as f:
            f.write(h_content)

        # Generate source
        cpp_content = generate_source(rel_path, class_info, free_funcs, extra_methods)
        with open(cpp_path, 'w', encoding='utf-8') as f:
            f.write(cpp_content)

        created += 2
        print(f"  OK: {rel_path} ({total} funcs)")

    print(f"\nCreated: {created} files")
    print(f"Skipped: {skipped} (already implemented)")


if __name__ == "__main__":
    main()
