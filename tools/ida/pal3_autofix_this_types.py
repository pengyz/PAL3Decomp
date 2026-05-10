"""
IDAPython: Automatically fix this-pointer types for ALL named thiscall functions.

For every function named "ClassName::MethodName" with __thiscall convention,
if the first parameter is NOT "ClassName *", fix it to be "ClassName *this".

This is the #1 ROI fix: Hex-Rays will then propagate correct types to
all callers' local variables, eliminating (int) casts and type errors.

Usage:
  idat.exe -A -S"pal3_autofix_this_types.py" original/PAL3.exe.i64
"""
import ida_auto
import ida_funcs
import ida_hexrays
import ida_name
import ida_typeinf
import idautils
import idc
import os
import re
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_autofix_this_types_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()
    log("[*] Auto-fix this types for all named thiscall methods")
    log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

    # First: collect all class names and ensure forward declarations exist
    class_names = set()
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        name = ida_name.get_name(ea) or ""
        cls = extract_class_name(name)
        if cls:
            class_names.add(cls)

    # Import forward declarations for all classes
    for cls in sorted(class_names):
        decl = "struct %s;" % cls
        tinfo = ida_typeinf.tinfo_t()
        ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
    log("[*] Forward declarations: %d classes" % len(class_names))

    # Now fix this types
    fixed = 0
    already_correct = 0
    errors = 0
    no_type = 0

    for ea in idautils.Functions(TEXT_START, TEXT_END):
        name = ida_name.get_name(ea) or ""
        cls_name = extract_class_name(name)
        if not cls_name:
            continue

        # Get current type string
        cur_type = idc.get_type(ea)
        if not cur_type:
            no_type += 1
            continue

        # Check if thiscall
        if '__thiscall' not in cur_type:
            continue

        # Check if this param already has correct type
        expected_this = '%s *' % cls_name
        # Parse params: everything between first ( and last )
        paren_start = cur_type.find('(')
        if paren_start < 0:
            continue
        params_str = cur_type[paren_start+1:cur_type.rfind(')')]

        # First param is the this pointer
        if not params_str:
            continue

        # Check if first param already correct
        if params_str.strip().startswith(cls_name + ' *'):
            already_correct += 1
            continue

        # Fix: replace first param type with ClassName *this
        # Split at first comma to isolate first param
        comma_pos = find_first_comma(params_str)
        if comma_pos > 0:
            rest_params = params_str[comma_pos:]  # includes the comma
            new_params = '%s *this%s' % (cls_name, rest_params)
        else:
            # Only one param (this)
            new_params = '%s *this' % cls_name

        # Extract demangled method name for SetType (requires full declaration)
        method_name = None
        if name.startswith('?'):
            inner = name[1:]
            if inner.startswith('?0') or inner.startswith('?1'):
                method_name = cls_name if inner[1] == '0' else '~' + cls_name
            else:
                at_pos = inner.find('@')
                if at_pos > 0:
                    method_name = inner[:at_pos]
        elif '::' in name:
            method_name = name.split('::', 1)[1]

        if not method_name:
            continue

        # Build full declaration: ret __thiscall ClassName::Method(params)
        ret_and_cc = cur_type[:paren_start].strip()  # e.g. "int __thiscall"
        new_type = '%s %s::%s(%s)' % (ret_and_cc, cls_name, method_name, new_params)

        if idc.SetType(ea, new_type):
            fixed += 1
            if fixed <= 30:
                log("  [+] 0x%08X %s" % (ea, cls_name))
        else:
            errors += 1
            if errors <= 10:
                log("  [!] 0x%08X %s: SetType failed" % (ea, name))
                log("      tried: %s" % new_type[:100])

    log("")
    log("[*] Results:")
    log("  Fixed: %d" % fixed)
    log("  Already correct: %d" % already_correct)
    log("  No type info: %d" % no_type)
    log("  Errors: %d" % errors)

    ida_auto.auto_wait()
    log("[*] Done. Run pal3_reexport_all.py next.")
    idc.qexit(0)


def extract_class_name(name):
    """Extract class name from function name (demangled or mangled)."""
    if not name:
        return None
    if name.startswith('sub_') or name.startswith('nullsub_'):
        return None

    if name.startswith('?'):
        inner = name[1:]
        if inner.startswith('?0') or inner.startswith('?1'):
            rest = inner[2:]
            at_pos = rest.find('@')
            if at_pos > 0:
                cls = rest[:at_pos]
                if cls and cls[0].isalpha() and '$' not in cls and '<' not in cls:
                    return cls
        else:
            at_pos = inner.find('@')
            if at_pos > 0:
                rest = inner[at_pos+1:]
                at_pos2 = rest.find('@')
                if at_pos2 > 0:
                    cls = rest[:at_pos2]
                    if cls and cls[0].isalpha() and '$' not in cls and '<' not in cls:
                        return cls
    elif '::' in name:
        cls = name.split('::')[0]
        if cls and cls[0].isalpha() and '$' not in cls and '<' not in cls:
            return cls

    return None


def find_first_comma(params_str):
    """Find first comma at depth 0 (respecting parens/templates)."""
    depth = 0
    for i, ch in enumerate(params_str):
        if ch in '(<':
            depth += 1
        elif ch in ')>':
            depth -= 1
        elif ch == ',' and depth == 0:
            return i
    return -1


try:
    main()
except Exception as e:
    log("[ERROR] %s" % str(e))
    import traceback
    log(traceback.format_exc())
finally:
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w') as f:
        f.write('\n'.join(log_lines))
