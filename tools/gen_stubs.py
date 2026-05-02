#!/usr/bin/env python3
"""
Generate stub implementations for unimplemented gbengine.dll exports.

Reads:
  - build/gbengine_demangled.txt (tab-separated: ordinal, offset, mangled, demangled)
  - build/matched_exports.txt (one mangled symbol per line, already implemented)

Writes:
  - src/gbengine/gbengine_stubs.cpp
"""

import os
import re
import sys
from collections import defaultdict

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)

DEMANGLED_FILE = os.path.join(PROJECT_DIR, "build", "gbengine_demangled.txt")
MATCHED_FILE = os.path.join(PROJECT_DIR, "build", "matched_exports.txt")
OUTPUT_FILE = os.path.join(PROJECT_DIR, "src", "gbengine", "gbengine_stubs.cpp")


def load_demangled(path):
    """Load demangled exports. Returns list of (ordinal, offset, mangled, demangled)."""
    entries = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.rstrip("\n\r")
            if not line:
                continue
            parts = line.split("\t")
            if len(parts) < 4:
                continue
            # Format: line_no \t ordinal \t offset \t mangled \t demangled
            # Actually from the file it seems: col1=line_no, col2=ordinal, col3=offset, col4=mangled, col5=demangled
            # Let me check: "1\t1\t0x000241E0\t??0BEZIER@@QAE@PAUgbVec3D@@@Z\tpublic: ..."
            if len(parts) >= 5:
                ordinal = parts[1].strip()
                offset = parts[2].strip()
                mangled = parts[3].strip()
                demangled = parts[4].strip()
            elif len(parts) == 4:
                ordinal = parts[0].strip()
                offset = parts[1].strip()
                mangled = parts[2].strip()
                demangled = parts[3].strip()
            else:
                continue
            entries.append((ordinal, offset, mangled, demangled))
    return entries


def load_matched(path):
    """Load matched (already implemented) symbols. Returns set of mangled names."""
    matched = set()
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            # Lines may have line numbers: "1\t??_7gbActor@@6B@"
            parts = line.split("\t")
            if len(parts) >= 2:
                matched.add(parts[-1].strip())
            else:
                matched.add(parts[0].strip())
    return matched


def is_vtable(mangled):
    """Check if symbol is a vtable (??_7...@@6B@)."""
    return mangled.startswith("??_7")


def is_default_constructor_closure(mangled):
    """Check if symbol is a default constructor closure (??_F...)."""
    return mangled.startswith("??_F")


def parse_demangled_signature(demangled, mangled):
    """
    Parse a demangled signature into structured info.
    Returns dict with keys: kind, class_name, method_name, return_type, params,
                           access, is_virtual, is_static, is_const, calling_conv
    """
    info = {
        "kind": "unknown",
        "class_name": None,
        "method_name": None,
        "return_type": None,
        "params": None,
        "access": "public",
        "is_virtual": False,
        "is_static": False,
        "is_const": False,
        "is_private": False,
        "calling_conv": "__thiscall",
        "raw": demangled,
        "mangled": mangled,
    }

    # Check for vtable
    if "`vftable'" in demangled:
        info["kind"] = "vtable"
        m = re.match(r"const\s+(\w+)::`vftable'", demangled)
        if m:
            info["class_name"] = m.group(1)
        return info

    # Check for default constructor closure
    if "`default constructor closure'" in demangled:
        info["kind"] = "default_constructor_closure"
        m = re.match(r".*?(\w+)::`default constructor closure'\(void\)", demangled)
        if m:
            info["class_name"] = m.group(1)
        return info

    # Check access specifier
    if demangled.startswith("private:"):
        info["access"] = "private"
        info["is_private"] = True
        demangled_body = demangled[len("private:"):].strip()
    elif demangled.startswith("protected:"):
        info["access"] = "protected"
        demangled_body = demangled[len("protected:"):].strip()
    elif demangled.startswith("public:"):
        info["access"] = "public"
        demangled_body = demangled[len("public:"):].strip()
    else:
        demangled_body = demangled.strip()

    # Check virtual
    if demangled_body.startswith("virtual "):
        info["is_virtual"] = True
        demangled_body = demangled_body[len("virtual "):].strip()

    # Check static
    if demangled_body.startswith("static "):
        info["is_static"] = True
        demangled_body = demangled_body[len("static "):].strip()
        info["kind"] = "static_member"
        # Static data member: "type ClassName::memberName"
        # Check if it has parentheses (function) or not (data)
        if "(" not in demangled_body:
            # Static data member
            # Pattern: "type Class::name"
            m = re.match(r"(.+?)\s+(\w+)::(\w+)$", demangled_body)
            if m:
                info["return_type"] = m.group(1)
                info["class_name"] = m.group(2)
                info["method_name"] = m.group(3)
                info["kind"] = "static_data"
            return info
        else:
            # Static member function
            info["kind"] = "static_method"

    # Check for global variable (no parentheses, no class::)
    if "::" not in demangled_body and "(" not in demangled_body:
        info["kind"] = "global_var"
        # Pattern: "type varname"
        m = re.match(r"(.+?)\s+(\w+)$", demangled_body)
        if m:
            info["return_type"] = m.group(1)
            info["method_name"] = m.group(2)
        return info

    # Check for global function (has parens but no :: before them)
    # Pattern: "return_type __cdecl functionName(params)"
    m = re.match(r"(.+?)\s+__cdecl\s+(\w+)\((.*)\)$", demangled_body)
    if m and "::" not in m.group(2):
        info["kind"] = "global_function"
        info["return_type"] = m.group(1)
        info["method_name"] = m.group(2)
        info["params"] = m.group(3)
        info["calling_conv"] = "__cdecl"
        return info

    # Check for variadic global function
    m = re.match(r"(.+?)\s+__cdecl\s+(\w+)\((.*),\.\.\.\)$", demangled_body)
    if m and "::" not in m.group(2):
        info["kind"] = "global_function_variadic"
        info["return_type"] = m.group(1)
        info["method_name"] = m.group(2)
        info["params"] = m.group(3) + ",..."
        info["calling_conv"] = "__cdecl"
        return info

    # Member function patterns
    # Calling convention
    calling_conv = "__thiscall"
    if "__cdecl" in demangled_body:
        calling_conv = "__cdecl"

    info["calling_conv"] = calling_conv

    # Constructor: "__thiscall ClassName::ClassName(params)"
    m = re.match(r"__thiscall\s+(\w+)::(\w+)\((.*)\)(const\s*)?$", demangled_body)
    if m:
        class_name = m.group(1)
        method_name = m.group(2)
        params = m.group(3)
        is_const = bool(m.group(4))
        info["class_name"] = class_name
        info["method_name"] = method_name
        info["params"] = params
        info["is_const"] = is_const
        if method_name == class_name:
            info["kind"] = "constructor"
        elif method_name == "~" + class_name or demangled_body.find("~" + class_name) >= 0:
            info["kind"] = "destructor"
        else:
            info["kind"] = "method"
        return info

    # Destructor: "__thiscall ClassName::~ClassName(void)"
    m = re.match(r"__thiscall\s+(\w+)::~(\w+)\((.*)\)$", demangled_body)
    if m:
        info["class_name"] = m.group(1)
        info["method_name"] = "~" + m.group(2)
        info["params"] = m.group(3)
        info["kind"] = "destructor"
        return info

    # Method with return type: "return_type __thiscall ClassName::MethodName(params)const"
    m = re.match(r"(.+?)\s+__thiscall\s+(\w+)::(\w+)\((.*)\)(const\s*)?$", demangled_body)
    if m:
        info["return_type"] = m.group(1)
        info["class_name"] = m.group(2)
        info["method_name"] = m.group(3)
        info["params"] = m.group(4)
        info["is_const"] = bool(m.group(5))
        info["kind"] = "method"
        return info

    # Operator with return type: "return_type __thiscall ClassName::operator<op>(params)const"
    m = re.match(r"(.+?)\s+__thiscall\s+(\w+)::(operator.+?)\((.*)\)(const\s*)?$", demangled_body)
    if m:
        info["return_type"] = m.group(1)
        info["class_name"] = m.group(2)
        info["method_name"] = m.group(3)
        info["params"] = m.group(4)
        info["is_const"] = bool(m.group(5))
        info["kind"] = "operator"
        return info

    # __cdecl member function: "return_type __cdecl ClassName::method(params)"
    m = re.match(r"(.+?)\s+__cdecl\s+(\w+)::(\w+)\((.*)\)(const\s*)?$", demangled_body)
    if m:
        info["return_type"] = m.group(1)
        info["class_name"] = m.group(2)
        info["method_name"] = m.group(3)
        info["params"] = m.group(4)
        info["is_const"] = bool(m.group(5))
        info["calling_conv"] = "__cdecl"
        info["kind"] = "method"
        return info

    # Fallback: try to parse operator= style things
    # "class X & __thiscall X::operator=(class X const &)"
    m = re.match(r"(.+?)\s+__thiscall\s+(\w+)::(operator\S+)\((.*)\)(const\s*)?$", demangled_body)
    if m:
        info["return_type"] = m.group(1)
        info["class_name"] = m.group(2)
        info["method_name"] = m.group(3)
        info["params"] = m.group(4)
        info["is_const"] = bool(m.group(5))
        info["kind"] = "operator"
        return info

    return info


def type_to_cpp(type_str):
    """Convert a demangled type string to valid C++ type for parameter/return."""
    if not type_str:
        return "void"
    return type_str.strip()


def get_default_return(return_type):
    """Generate a default return statement for the given type."""
    if not return_type or return_type == "void":
        return ""

    rt = return_type.strip()

    # Reference returns
    if rt.endswith("&"):
        return None  # Handled specially

    # Pointer returns
    if rt.endswith("*"):
        return "return 0;"

    # Bool
    if rt in ("bool", "_Bool"):
        return "return false;"

    # Float types
    if rt in ("float",):
        return "return 0.0f;"
    if rt in ("double",):
        return "return 0.0;"

    # Integer types
    if rt in ("int", "long", "short", "char", "unsigned int", "unsigned long",
              "unsigned short", "unsigned char", "unsigned __int64", "__int64",
              "DWORD", "HRESULT", "BOOL"):
        return "return 0;"

    # Enum
    if rt.startswith("enum "):
        return "return ({})(0);".format(rt)

    # Struct by value
    if rt.startswith("struct ") or rt.startswith("class "):
        # Return a zero-initialized struct
        return "{} tmp = {{}}; return tmp;".format(rt)

    # Default for unknown types (e.g., typedef'd types)
    return "return 0;"


def parse_param_list(params_str):
    """Parse a comma-separated parameter list, handling nested templates/brackets."""
    if not params_str or params_str.strip() == "void":
        return []

    params = []
    depth = 0
    current = ""
    for ch in params_str:
        if ch in ("<", "("):
            depth += 1
            current += ch
        elif ch in (">", ")"):
            depth -= 1
            current += ch
        elif ch == "," and depth == 0:
            params.append(current.strip())
            current = ""
        else:
            current += ch
    if current.strip():
        params.append(current.strip())
    return params


def param_to_decl(param_str, idx):
    """Convert a parameter type string to a C++ parameter declaration."""
    p = param_str.strip()
    if p == "void":
        return ""
    if p == "...":
        return "..."

    # Already has a name? Check if it ends with a word that's a param name
    # In demangled signatures, params are just types, no names
    # Give it a name
    return "{} p{}".format(p, idx)


def format_params_for_decl(params_str):
    """Format parameter string for a function declaration."""
    if not params_str or params_str.strip() == "void":
        return "void"
    if params_str.strip() == "":
        return "void"

    params = parse_param_list(params_str)
    decls = []
    for i, p in enumerate(params):
        if p == "...":
            decls.append("...")
        else:
            decls.append(format_single_param(p, i))
    return ", ".join(decls)


def format_single_param(type_str, idx):
    """Format a single parameter, handling function pointer types correctly."""
    # Check for function pointer: "void (__cdecl*)(int,int)" pattern
    # The name goes inside: "void (__cdecl*name)(int,int)"
    m = re.match(r'^(.*\(\s*(?:__cdecl|__stdcall|__fastcall)?\s*\*)\)(\(.*\))$', type_str)
    if m:
        # Function pointer: insert name before the closing paren of the pointer part
        return "{}p{}){}".format(m.group(1), idx, m.group(2))

    # Check for array types: "type name[]" or "type (*)[N]"
    # These are rare in this codebase, handle basic case
    return "{} p{}".format(type_str, idx)


def classify_operator(mangled):
    """Classify operator from mangled name prefix."""
    # ??0 = constructor, ??1 = destructor, ??4 = operator=
    # ??8 = operator==, ??9 = operator!=
    # ??A = operator[], ??G = operator- (unary), ??R = operator()
    # ??X = operator*=, ??Y = operator+=, ??Z = operator-=
    # ??_0 = operator/=
    if mangled.startswith("??0"):
        return "constructor"
    elif mangled.startswith("??1"):
        return "destructor"
    elif mangled.startswith("??4"):
        return "operator="
    elif mangled.startswith("??8"):
        return "operator=="
    elif mangled.startswith("??9"):
        return "operator!="
    elif mangled.startswith("??A"):
        return "operator[]"
    elif mangled.startswith("??G"):
        return "operator-"
    elif mangled.startswith("??R"):
        return "operator()"
    elif mangled.startswith("??X"):
        return "operator*="
    elif mangled.startswith("??Y"):
        return "operator+="
    elif mangled.startswith("??Z"):
        return "operator-="
    elif mangled.startswith("??_0"):
        return "operator/="
    elif mangled.startswith("??_7"):
        return "vtable"
    elif mangled.startswith("??_F"):
        return "default_ctor_closure"
    return None


def extract_class_name_from_mangled(mangled):
    """Extract class name from mangled symbol."""
    # Constructors: ??0ClassName@@...
    # Destructors: ??1ClassName@@...
    # Operators: ??4ClassName@@..., ??8ClassName@@..., etc.
    # Methods: ?MethodName@ClassName@@...
    # Vtables: ??_7ClassName@@6B@
    # Static data: ?name@ClassName@@2...

    if mangled.startswith("??_7"):
        # vtable
        m = re.match(r"\?\?_7(\w+)@@", mangled)
        return m.group(1) if m else None

    if mangled.startswith("??_F"):
        # default ctor closure
        m = re.match(r"\?\?_F(\w+)@@", mangled)
        return m.group(1) if m else None

    if mangled.startswith("??"):
        # ??0ClassName@@, ??1ClassName@@, ??4ClassName@@, etc.
        m = re.match(r"\?\?[0-9A-Z_]+(\w+)@@", mangled)
        return m.group(1) if m else None

    if mangled.startswith("?"):
        # ?MethodName@ClassName@@...
        m = re.match(r"\?(\w+)@(\w+)@@", mangled)
        if m:
            return m.group(2)
        # Global: ?name@@...
        m = re.match(r"\?(\w+)@@", mangled)
        if m:
            return None  # global, no class

    return None


def is_struct_type(class_name):
    """Determine if a class name should be a struct (from demangled type info)."""
    struct_types = {
        "gbVec3D", "gbVec2D", "gbVec4D", "gbColorQuad", "gbColorFlt",
        "gbMatrix4", "gbRotMatrix", "gbQuaternion", "gbRay", "gbAABBox",
        "gbOBBox", "gbSphere", "gbPlane", "gbUIRect", "gbPixelFormat",
        "gbEmitterData", "gbEmitterSquare", "gbDropDesc", "gbDropUnit",
        "gbPartGroupParam", "gbParticleUnit", "gbAudioMgrDesc",
        "gbImage2DInfo", "gbTextureArray", "gbStaticChainNode",
        "gbRealWorldTime", "gbNodeMsgObj", "gbRenderInfoObj",
        "gbActorExpNode", "gbMixActInfo", "gbGfxDriverInfo",
        "gbGfxCaps", "gbFogParam", "gbLight", "gbMeshMemCache",
        "GeomNodeDesc",
    }
    return class_name in struct_types


def generate_stubs(entries, matched):
    """Generate stub source code for unimplemented symbols."""

    # Filter out matched and vtable symbols
    unmatched = []
    for ordinal, offset, mangled, demangled in entries:
        if mangled in matched:
            continue
        if is_vtable(mangled):
            continue
        unmatched.append((ordinal, offset, mangled, demangled))

    print(f"Total exports: {len(entries)}")
    print(f"Already matched: {len(matched)}")
    print(f"Vtables (skipped): {sum(1 for _, _, m, _ in entries if is_vtable(m))}")
    print(f"Symbols to stub: {len(unmatched)}")

    # Determine which classes have at least one matched symbol
    # (i.e., partially implemented in existing .cpp files)
    classes_with_matched = set()
    for ordinal, offset, mangled, demangled in entries:
        if mangled in matched:
            cn = extract_class_name_from_mangled(mangled)
            if cn:
                classes_with_matched.add(cn)

    # Parse all symbols and group by class
    class_symbols = defaultdict(list)  # class_name -> list of parsed info
    global_symbols = []  # non-class symbols

    for ordinal, offset, mangled, demangled in unmatched:
        info = parse_demangled_signature(demangled, mangled)
        info["ordinal"] = ordinal
        info["offset"] = offset

        if info["kind"] == "vtable":
            continue  # Skip vtables

        class_name = info.get("class_name")
        if class_name:
            class_symbols[class_name].append(info)
        else:
            global_symbols.append(info)

    # Collect all class names referenced as types (for forward declarations)
    all_class_names = set(class_symbols.keys())

    # Collect type references from parameters and return types
    type_refs = set()
    for class_name, symbols in class_symbols.items():
        for info in symbols:
            if info.get("params"):
                type_refs.add(info["params"])
            if info.get("return_type"):
                type_refs.add(info["return_type"])
    for info in global_symbols:
        if info.get("params"):
            type_refs.add(info["params"])
        if info.get("return_type"):
            type_refs.add(info["return_type"])

    # Extract class/struct names from type references
    forward_classes = set()
    forward_structs = set()
    for tref in type_refs:
        for m in re.finditer(r'\bclass\s+(\w+)', tref):
            forward_classes.add(m.group(1))
        for m in re.finditer(r'\bstruct\s+(\w+)', tref):
            forward_structs.add(m.group(1))

    # Also add enum types (but exclude qualified names like "enum ClassName::EnumName")
    forward_enums = set()
    for tref in type_refs:
        for m in re.finditer(r'\benum\s+(\w+)(?:::(\w+))?', tref):
            if m.group(2):
                # This is a qualified enum like gbLightObj::LIGHT_TYPE
                # The actual enum name is the full qualified name; skip it
                # (nested enums will be declared inside their class)
                pass
            else:
                forward_enums.add(m.group(1))

    # Remove any enum names that are actually classes we're defining
    forward_enums -= all_class_names

    # Types already defined in gbengine_types.h - don't redeclare these as classes
    defined_in_header = {
        "gbVec2D", "gbVec3D", "gbVec4D", "gbColorQuad", "gbColorFlt",
        "gbMatrix4", "gbRotMatrix", "gbQuaternion", "gbRay", "gbAABBox",
        "gbOBBox", "gbSphere", "gbPlane", "gbUIRect", "gbPixelFormat",
        "gbPixelFmtType", "gbAxis",
    }

    # Collect nested enums (enum ClassName::EnumName)
    nested_enums = defaultdict(set)  # class_name -> set of enum names
    for tref in type_refs:
        for m in re.finditer(r'\benum\s+(\w+)::(\w+)', tref):
            nested_enums[m.group(1)].add(m.group(2))

    # Generate output
    lines = []
    lines.append("/**")
    lines.append(" * gbengine.dll - Stub implementations for unimplemented exports")
    lines.append(" * Auto-generated by tools/gen_stubs.py")
    lines.append(" * DO NOT EDIT MANUALLY")
    lines.append(" */")
    lines.append("")
    lines.append('#include "gbengine/gbengine_types.h"')
    lines.append("#include <windows.h>")
    lines.append("#include <stdarg.h>")
    lines.append("")
    lines.append("#pragma warning(disable: 4100 4731 4716 4101)")
    lines.append("")

    # Forward declarations for enums
    if forward_enums - defined_in_header:
        lines.append("// Enum forward declarations")
        for en in sorted(forward_enums - defined_in_header):
            lines.append("enum {} {{}};".format(en))
        lines.append("")

    # Collect all names that will be defined as stub classes/structs
    stub_defined_names = set()
    for c in all_class_names:
        if c not in defined_in_header:
            stub_defined_names.add(c)

    # Forward declarations for structs (exclude those defined as stub classes)
    structs_to_declare = forward_structs - defined_in_header - stub_defined_names
    if structs_to_declare:
        lines.append("// Struct forward declarations")
        for s in sorted(structs_to_declare):
            lines.append("struct {};".format(s))
        lines.append("")

    # Forward declarations for classes (exclude those defined as stub classes)
    classes_to_declare = forward_classes - all_class_names - defined_in_header - structs_to_declare
    if classes_to_declare:
        lines.append("// Class forward declarations")
        for c in sorted(classes_to_declare):
            lines.append("class {};".format(c))
        lines.append("")

    # Forward-declare all stub classes (unified list, no duplicates)
    lines.append("// Stub class forward declarations")
    for c in sorted(all_class_names):
        if c not in defined_in_header:
            if is_struct_type(c):
                lines.append("struct {};".format(c))
            else:
                lines.append("class {};".format(c))
    lines.append("")

    # Generate class stubs
    for class_name in sorted(class_symbols.keys()):
        symbols = class_symbols[class_name]

        # Skip classes that are defined in header as structs with different layout
        if class_name in defined_in_header:
            # These are simple structs defined in the header.
            # We need to add methods to them - use a separate block outside the struct
            lines.append("")
            lines.append("// ========= {} (methods for header-defined type) =========".format(class_name))
            for info in symbols:
                _generate_freestanding_method(lines, info, class_name)
            continue

        # For classes that already have some matched symbols (partially implemented),
        # we cannot redefine them here. Skip them - their missing methods need to be
        # added to their existing source files.
        if class_name in classes_with_matched:
            lines.append("")
            lines.append("// ========= {} (SKIP: partially implemented elsewhere) =========".format(class_name))
            lines.append("// Missing {} methods - add to existing source file:".format(len(symbols)))
            for info in symbols:
                lines.append("//   {} ({})".format(info.get("method_name", "?"), info["mangled"]))
            continue

        lines.append("")
        lines.append("// ========= {} =========".format(class_name))

        # Determine if this class needs virtual methods
        has_virtual = any(info.get("is_virtual") for info in symbols)
        has_destructor = any(info["kind"] == "destructor" for info in symbols)

        # Use struct for known struct types
        keyword = "struct" if is_struct_type(class_name) else "class"

        lines.append("{} {} {{".format(keyword, class_name))
        if keyword == "class":
            lines.append("public:")

        # Declare nested enums if any
        if class_name in nested_enums:
            for enum_name in sorted(nested_enums[class_name]):
                lines.append("    enum {} {{}};".format(enum_name))

        # Add a data member to give the class some size
        lines.append("    char _stub_data[128];")
        lines.append("")

        # If we have a virtual destructor or virtual methods but no destructor in stubs,
        # add a virtual destructor to ensure vtable generation
        virtual_dtor_needed = has_virtual and not has_destructor

        # Generate members
        # First: constructors
        for info in symbols:
            if info["kind"] == "constructor":
                _generate_method_in_class(lines, info, class_name)

        # Destructor
        for info in symbols:
            if info["kind"] == "destructor":
                _generate_method_in_class(lines, info, class_name)

        if virtual_dtor_needed:
            lines.append("    virtual ~{}() {{}}".format(class_name))
            lines.append("")

        # Operators
        for info in symbols:
            if info["kind"] == "operator":
                _generate_method_in_class(lines, info, class_name)

        # Regular methods
        for info in symbols:
            if info["kind"] == "method":
                _generate_method_in_class(lines, info, class_name)

        # Default constructor closure
        for info in symbols:
            if info["kind"] == "default_constructor_closure":
                # This is auto-generated by compiler when there are default member initializers
                # We don't need to explicitly define it - but we can't skip it either
                # Actually ??_F is generated automatically, skip it
                pass

        # Static data members
        for info in symbols:
            if info["kind"] == "static_data":
                _generate_static_data_decl(lines, info)

        # Static methods
        for info in symbols:
            if info["kind"] == "static_method":
                _generate_method_in_class(lines, info, class_name)

        lines.append("};")

        # Static data member definitions (outside class)
        for info in symbols:
            if info["kind"] == "static_data":
                _generate_static_data_def(lines, info, class_name)

    # Generate global symbols
    if global_symbols:
        lines.append("")
        lines.append("// ========= Global Functions and Variables =========")
        for info in global_symbols:
            if info["kind"] == "global_function" or info["kind"] == "global_function_variadic":
                _generate_global_function(lines, info)
            elif info["kind"] == "global_var":
                _generate_global_var(lines, info)
            elif info["kind"] == "unknown":
                lines.append("// UNHANDLED: {} ({})".format(info["mangled"], info["raw"]))

    return "\n".join(lines) + "\n"


def _generate_method_in_class(lines, info, class_name):
    """Generate a method definition inside a class body."""
    kind = info["kind"]
    is_virtual = info.get("is_virtual", False)
    is_const = info.get("is_const", False)
    is_static = info.get("is_static", False)
    is_private = info.get("is_private", False)
    access = info.get("access", "public")
    params = info.get("params", "void")
    return_type = info.get("return_type", "void")
    method_name = info.get("method_name", "")

    # Access specifier change
    if is_private or access == "private":
        lines.append("private:")
    elif access == "protected":
        lines.append("protected:")
    else:
        lines.append("public:")

    if kind == "constructor":
        # Constructor
        params_decl = format_params_for_decl(params)
        if params_decl == "void":
            params_decl = ""
        prefix = "    "
        lines.append("{}{}({}) {{}}".format(prefix, class_name, params_decl))

    elif kind == "destructor":
        prefix = "    "
        virt = "virtual " if is_virtual else ""
        lines.append("{}{}~{}() {{}}".format(prefix, virt, class_name))

    elif kind == "operator":
        params_decl = format_params_for_decl(params)
        if params_decl == "void":
            params_decl = ""
        prefix = "    "
        virt = "virtual " if is_virtual else ""
        static = "static " if is_static else ""
        const_suffix = " const" if is_const else ""
        ret = type_to_cpp(return_type)

        # Special handling for operator= returning reference to self
        if method_name == "operator=" and "&" in ret:
            lines.append("{}{}{}{} {}({}){} {{ return *this; }}".format(
                prefix, static, virt, ret, method_name, params_decl, const_suffix))
        elif method_name in ("operator+=", "operator-=", "operator*=", "operator/=") and (ret == "void" or not ret):
            lines.append("{}{}{}{} {}({}){} {{}}".format(
                prefix, static, virt, "void", method_name, params_decl, const_suffix))
        elif "&" in ret and class_name in ret:
            # Returns reference to self
            lines.append("{}{}{}{} {}({}){} {{ return *this; }}".format(
                prefix, static, virt, ret, method_name, params_decl, const_suffix))
        else:
            body = _get_return_body(ret)
            lines.append("{}{}{}{} {}({}){} {{ {} }}".format(
                prefix, static, virt, ret, method_name, params_decl, const_suffix, body))

    elif kind == "method" or kind == "static_method":
        params_decl = format_params_for_decl(params)
        if params_decl == "void":
            params_decl = ""
        prefix = "    "
        virt = "virtual " if is_virtual else ""
        static = "static " if is_static else ""
        const_suffix = " const" if is_const else ""
        ret = type_to_cpp(return_type)

        body = _get_return_body(ret)
        lines.append("{}{}{}{} {}({}){} {{ {} }}".format(
            prefix, static, virt, ret, method_name, params_decl, const_suffix, body))

    lines.append("")


def _generate_freestanding_method(lines, info, class_name):
    """Generate method definition for a class already defined in a header."""
    kind = info["kind"]
    is_virtual = info.get("is_virtual", False)
    is_const = info.get("is_const", False)
    params = info.get("params", "void")
    return_type = info.get("return_type", "void")
    method_name = info.get("method_name", "")

    params_decl = format_params_for_decl(params)
    if params_decl == "void":
        params_decl = ""
    const_suffix = " const" if is_const else ""

    if kind == "constructor":
        lines.append("{}::{}({}) {{}}".format(class_name, class_name, params_decl))
    elif kind == "destructor":
        lines.append("{}::~{}() {{}}".format(class_name, class_name))
    elif kind == "operator":
        ret = type_to_cpp(return_type)
        if "operator=" in method_name and "&" in ret:
            lines.append("{} {}::{}({}){} {{ return *this; }}".format(
                ret, class_name, method_name, params_decl, const_suffix))
        else:
            body = _get_return_body(ret)
            lines.append("{} {}::{}({}){} {{ {} }}".format(
                ret, class_name, method_name, params_decl, const_suffix, body))
    elif kind == "method":
        ret = type_to_cpp(return_type)
        body = _get_return_body(ret)
        lines.append("{} {}::{}({}){} {{ {} }}".format(
            ret, class_name, method_name, params_decl, const_suffix, body))
    elif kind == "static_data":
        ret = type_to_cpp(return_type)
        lines.append("{} {}::{};".format(ret, class_name, method_name))
    elif kind == "default_constructor_closure":
        # Skip - auto-generated
        pass
    else:
        lines.append("// UNHANDLED: {} ({})".format(info["mangled"], info["raw"]))


def _generate_static_data_decl(lines, info):
    """Generate static data member declaration inside class."""
    ret = type_to_cpp(info.get("return_type", "int"))
    name = info.get("method_name", "unknown")
    lines.append("    static {} {};".format(ret, name))


def _generate_static_data_def(lines, info, class_name):
    """Generate static data member definition outside class."""
    ret = type_to_cpp(info.get("return_type", "int"))
    name = info.get("method_name", "unknown")

    # Default initialization
    if "*" in ret:
        lines.append("{} {}::{} = 0;".format(ret, class_name, name))
    elif ret in ("int", "long", "short", "unsigned int", "unsigned long",
                 "unsigned short", "float", "double"):
        lines.append("{} {}::{} = 0;".format(ret, class_name, name))
    elif ret == "char *" or ret == "char*":
        lines.append("{} {}::{} = 0;".format(ret, class_name, name))
    else:
        # Try zero-init
        lines.append("{} {}::{} = {{}};".format(ret, class_name, name))


def _generate_global_function(lines, info):
    """Generate a global (free) function stub."""
    ret = type_to_cpp(info.get("return_type", "void"))
    name = info.get("method_name", "unknown")
    params = info.get("params", "void")
    params_decl = format_params_for_decl(params)
    if params_decl == "void":
        params_decl = "void"

    body = _get_return_body(ret)
    lines.append("{} __cdecl {}({}) {{ {} }}".format(ret, name, params_decl, body))


def _generate_global_var(lines, info):
    """Generate a global variable definition."""
    ret = type_to_cpp(info.get("return_type", "int"))
    name = info.get("method_name", "unknown")

    if "*" in ret:
        lines.append("{} {} = 0;".format(ret, name))
    elif ret in ("int", "long", "short", "unsigned int", "unsigned long",
                 "float", "double"):
        lines.append("{} {} = 0;".format(ret, name))
    else:
        lines.append("{} {} = {{}};".format(ret, name))


def _get_return_body(return_type):
    """Get the body of a stub function for a given return type."""
    if not return_type or return_type == "void":
        return ""

    rt = return_type.strip()

    # Reference - return *(type*)0 pattern won't work. Use static local.
    if rt.endswith("&"):
        base_type = rt[:-1].strip()
        return "static {} _stub; return _stub;".format(base_type)

    # Pointer
    if rt.endswith("*"):
        return "return 0;"

    if rt == "bool" or rt == "_Bool":
        return "return false;"

    if rt == "float":
        return "return 0.0f;"

    if rt == "double":
        return "return 0.0;"

    if rt in ("int", "long", "short", "char", "unsigned int", "unsigned long",
              "unsigned short", "unsigned char", "DWORD", "HRESULT", "BOOL",
              "LONG", "UINT"):
        return "return 0;"

    if rt.startswith("enum "):
        return "return ({})(0);".format(rt)

    # Struct/class by value
    if rt.startswith("struct ") or rt.startswith("class "):
        return "static {} _stub = {{}}; return _stub;".format(rt)

    # Unknown type - could be typedef
    return "return 0;"


def collect_header_type_methods(entries, matched, defined_in_header):
    """
    Collect all methods (including already-matched ones) for header-defined types.
    Returns dict: class_name -> list of method declaration strings.
    """
    methods = defaultdict(list)

    for ordinal, offset, mangled, demangled in entries:
        info = parse_demangled_signature(demangled, mangled)
        class_name = info.get("class_name")
        if not class_name or class_name not in defined_in_header:
            continue
        if info["kind"] == "vtable":
            continue

        kind = info["kind"]
        is_virtual = info.get("is_virtual", False)
        is_const = info.get("is_const", False)
        is_static = info.get("is_static", False)
        params = info.get("params", "void")
        return_type = info.get("return_type", "void")
        method_name = info.get("method_name", "")

        params_decl = format_params_for_decl(params)
        if params_decl == "void":
            params_decl = ""
        const_suffix = " const" if is_const else ""
        virt = "virtual " if is_virtual else ""
        static = "static " if is_static else ""

        if kind == "constructor":
            methods[class_name].append("    {}({});".format(class_name, params_decl))
        elif kind == "destructor":
            methods[class_name].append("    {}~{}();".format(virt, class_name))
        elif kind == "default_constructor_closure":
            # Auto-generated, skip
            pass
        elif kind == "operator":
            ret = type_to_cpp(return_type)
            methods[class_name].append("    {}{}{} {}({}){};".format(
                static, virt, ret, method_name, params_decl, const_suffix))
        elif kind == "method" or kind == "static_method":
            ret = type_to_cpp(return_type)
            methods[class_name].append("    {}{}{} {}({}){};".format(
                static, virt, ret, method_name, params_decl, const_suffix))
        elif kind == "static_data":
            ret = type_to_cpp(return_type)
            methods[class_name].append("    static {} {};".format(ret, method_name))

    return methods


def generate_updated_header(header_path, entries, matched, defined_in_header):
    """Generate an updated gbengine_types.h with method declarations."""
    methods = collect_header_type_methods(entries, matched, defined_in_header)

    with open(header_path, "r", encoding="utf-8") as f:
        content = f.read()

    # Remove any existing auto-generated method sections to avoid duplication
    content = re.sub(
        r'\n    // Methods \(auto-generated\)\n(?:    [^\n]*\n)*',
        '\n',
        content
    )

    # For each type, find its closing brace and insert methods before it
    for type_name, method_list in sorted(methods.items()):
        if not method_list:
            continue

        # Fix class/struct mismatch: if the type is a struct in the header,
        # replace "class TypeName" with "struct TypeName" in method declarations
        fixed_methods = []
        has_non_default_ctor = False
        has_default_ctor = False
        for decl in method_list:
            decl = decl.replace("class {} &".format(type_name),
                              "struct {} &".format(type_name))
            decl = decl.replace("class {} const &".format(type_name),
                              "struct {} const &".format(type_name))
            decl = decl.replace("class {} *".format(type_name),
                              "struct {} *".format(type_name))
            fixed_methods.append(decl)
            # Check if we have constructors
            if "    {}(".format(type_name) in decl:
                if "{}()".format(type_name) in decl:
                    has_default_ctor = True
                else:
                    has_non_default_ctor = True

        # If there's a non-default constructor but no default one,
        # add a default constructor to preserve POD-like usage
        if has_non_default_ctor and not has_default_ctor:
            fixed_methods.insert(0, "    {}() {{}}".format(type_name))

        # Find the struct/class definition: "struct TypeName {"
        pattern = r"(struct\s+" + re.escape(type_name) + r"\s*\{[^}]*)"
        match = re.search(pattern, content, re.DOTALL)
        if match:
            # Insert methods before the closing brace
            insertion_point = match.end()
            method_block = "\n    // Methods (auto-generated)\n" + "\n".join(fixed_methods) + "\n"
            content = content[:insertion_point] + method_block + content[insertion_point:]

    return content


def main():
    if not os.path.exists(DEMANGLED_FILE):
        print(f"Error: {DEMANGLED_FILE} not found")
        sys.exit(1)
    if not os.path.exists(MATCHED_FILE):
        print(f"Error: {MATCHED_FILE} not found")
        sys.exit(1)

    print("Loading demangled exports...")
    entries = load_demangled(DEMANGLED_FILE)
    print(f"  Loaded {len(entries)} entries")

    print("Loading matched exports...")
    matched = load_matched(MATCHED_FILE)
    print(f"  Loaded {len(matched)} matched symbols")

    print("Generating stubs...")
    output = generate_stubs(entries, matched)

    os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.write(output)
    print(f"  Stubs written to: {OUTPUT_FILE}")

    # Update header with method declarations
    HEADER_FILE = os.path.join(PROJECT_DIR, "include", "gbengine", "gbengine_types.h")
    print("Updating header with method declarations...")
    defined_in_header = {
        "gbVec2D", "gbVec3D", "gbVec4D", "gbColorQuad", "gbColorFlt",
        "gbMatrix4", "gbRotMatrix", "gbQuaternion", "gbRay", "gbAABBox",
        "gbOBBox", "gbSphere", "gbPlane", "gbUIRect", "gbPixelFormat",
    }
    updated_header = generate_updated_header(HEADER_FILE, entries, matched, defined_in_header)
    with open(HEADER_FILE, "w", encoding="utf-8") as f:
        f.write(updated_header)
    print(f"  Header updated: {HEADER_FILE}")

    print("Done!")


if __name__ == "__main__":
    main()
