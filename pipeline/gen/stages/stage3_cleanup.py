"""Stage 3: Post-OOP cleanup (depends on Stage 2 output).

Removes/comments IDA artifacts that Stage 2 may have introduced or exposed:
- this variable declarations
- operator new fixes
- CC removal from body (function pointer casts)
- COERCE_FLOAT literal coercion
- explicit ctor/dtor call commenting
- _replace_ida_internals (backtick, vftable, standalone ctor/dtor)
"""
import re
import struct as _struct
from data import store


# --- Explicit ctor call detection (matches old _comment_out_explicit_ctor_calls) ---

def _comment_out_explicit_ctor_calls(code):
    """Comment out ->ClassName() where ClassName is a known game class."""
    lines = code.split('\n')
    out = []
    for line in lines:
        stripped = line.strip()
        m = re.search(r'->\s*([A-Z_]\w+)\s*\(', stripped)
        if m:
            called_name = m.group(1)
            if called_name in store.game_classes and stripped.endswith(';'):
                indent = line[:len(line) - len(line.lstrip())]
                if '=' not in stripped and not stripped.startswith('return') \
                        and not stripped.startswith('if') \
                        and not stripped.startswith('while'):
                    out.append(indent + '// [AUTO-COMMENTED] ' + stripped)
                    continue
                elif stripped.startswith('return'):
                    cast_m = re.match(
                        r'return\s+(.+?)\s*->\s*%s\s*\(' % re.escape(called_name), stripped)
                    if cast_m:
                        out.append(indent + 'return %s; // ctor auto-called' % cast_m.group(1).rstrip())
                        continue
                    out.append(indent + 'return this; // [ctor replaced]')
                    continue
                elif '=' in stripped:
                    out.append(indent + '// [AUTO-COMMENTED] ' + stripped)
                    continue
        out.append(line)
    return '\n'.join(out)


# --- IDA internals (matches old _replace_ida_internals) ---

_BACKTICK_PATTERNS = (
    "`eh vector constructor iterator'",
    "`eh vector destructor iterator'",
    "`default constructor closure'",
    "`scalar deleting destructor'",
    "`vftable'",
)


def _replace_ida_internals(code):
    """Remove IDA compiler-internal artifacts."""
    lines = code.split('\n')
    out = []
    skip_until_semicolon = False
    for line in lines:
        s = line.strip()
        if skip_until_semicolon:
            if ';' in s:
                skip_until_semicolon = False
            continue
        if any(p in s for p in _BACKTICK_PATTERNS):
            if ';' not in s:
                skip_until_semicolon = True
            continue
        # Remove __vftable assignments (vtable init in ctor/dtor)
        if re.match(r'.*->?__vftable\s*=\s*', s) or re.match(r'.*__vftable\s*=\s*', s):
            continue
        # Comment out __vftable-based virtual calls
        if ('->__vftable->' in s or '->__vftable)' in s) and s.endswith(';') \
                and not s.startswith('//'):
            indent = line[:len(line) - len(line.lstrip())]
            out.append(indent + '// [IDA_VFTABLE] ' + s)
            continue
        # Delete standalone explicit ctor/dtor: ((Type *)expr)->Type(args);
        _ctor_m = re.match(r'\s*\(\((\w+)\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
        if _ctor_m and _ctor_m.group(1) == _ctor_m.group(2):
            continue
        _ctor_m2 = re.match(r'\s*\(\((\w+)\s*\*\)\s*\(\w+\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
        if _ctor_m2 and _ctor_m2.group(1) == _ctor_m2.group(2):
            continue
        out.append(line)
    return '\n'.join(out)


# --- Main stage entry ---

def run(code, ctx):
    """Apply post-OOP cleanup transforms (exact order from old gen_cpp.py)."""
    cls_name = ctx.cls_name

    # TODO: free functions should get full cleanup (ctor comment, COERCE_FLOAT, etc.)
    # Currently minimal path to match old gen_cpp.py behavior exactly
    if ctx.is_free_function:
        code = re.sub(r'\(\*\)(\w+)', r'(*\1)', code)
        code = _replace_ida_internals(code)
        return code

    # --- Class method full cleanup ---

    # 1. Remove 'this' variable declaration
    if cls_name:
        code = re.sub(r'^\s*%s\s*\*\s*this\s*;.*$' % re.escape(cls_name), '', code, flags=re.MULTILINE)

    # 2. Fix operator new
    code = re.sub(r'\(\(operator \*\)(0x[0-9A-Fa-f]+u?)\)->new\(\)',
                  r'operator new(\1)', code)

    # 3. Remove CC from function pointer casts in body
    code = re.sub(r'__thiscall\s+', '', code)
    code = re.sub(r'__userpurge\s+', '', code)
    code = re.sub(r'__usercall\s+', '', code)

    # 4. COERCE_FLOAT(literal) → inline float
    def _fix_coerce_float(m):
        arg = m.group(1).strip()
        try:
            ival = int(arg, 0)
            if abs(ival) <= 100:
                return '%d.0f' % ival
            fval = _struct.unpack('f', _struct.pack('I', ival & 0xFFFFFFFF))[0]
            if abs(fval) < 1e10 and (abs(fval) > 1e-10 or fval == 0.0):
                if fval == int(fval) and abs(fval) < 1000000:
                    return '%d.0f' % int(fval)
                return '%.7gf' % fval
        except (ValueError, OverflowError):
            pass
        return m.group(0)
    code = re.sub(r'COERCE_FLOAT\((\s*-?(?:0x[0-9A-Fa-f]+|\d+)\s*)\)', _fix_coerce_float, code)

    # 5. Fix (*)var → (*var)
    code = re.sub(r'\(\*\)(\w+)', r'(*\1)', code)

    # 6. Ctor return → this
    code = re.sub(r'return\s+&this->__vftable\s*;', 'return this;', code)
    code = re.sub(r'return\s+\([^)]+\)\s*&this->__vftable\s*;', 'return this;', code)

    # 7. Comment out explicit ctor calls (only for class methods, not free functions)
    if not ctx.is_free_function:
        code = _comment_out_explicit_ctor_calls(code)

    # 8. LODWORD/HIDWORD address cast
    code = re.sub(
        r'((?:LODWORD|HIDWORD)\s*\([^)]+\))\s*=\s*(&\w+)',
        r'\1 = (unsigned long)\2', code)

    # 9. (int)Class::Method → address extraction
    def _fix_mfp_cast(m):
        cls_method = m.group(1)
        addr_m = re.search(r'_([0-9A-Fa-f]{5,})$', cls_method.split('::')[-1])
        if addr_m:
            return '0x%s' % addr_m.group(1)
        return '0 /* TODO: (int)%s */' % cls_method
    code = re.sub(r'\(int\)\s*(\w+::(?:~?\w+))\b(?!\s*\()', _fix_mfp_cast, code)

    # 10. Remove IDA internals (backtick, vftable, standalone ctor/dtor)
    code = _replace_ida_internals(code)

    return code
