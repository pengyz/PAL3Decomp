"""Remove IDA compiler-internal artifacts from decompiled output.

Order 0-99: Runs first to clean invalid code before other transforms process it.
"""
import re
from transforms import register
from data import store


_BACKTICK_PATTERNS = (
    "`eh vector constructor iterator'",
    "`eh vector destructor iterator'",
    "`default constructor closure'",
    "`scalar deleting destructor'",
    "`vftable'",
)


@register(order=10)
def remove_backtick_calls(code, ctx):
    """Remove compiler-internal backtick function calls."""
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
        out.append(line)
    return '\n'.join(out)


@register(order=20)
def remove_vftable_assigns(code, ctx):
    """Remove vtable pointer assignments (compiler-generated in ctor/dtor)."""
    lines = code.split('\n')
    out = []
    for line in lines:
        s = line.strip()
        if re.match(r'.*->?__vftable\s*=\s*', s) or re.match(r'.*__vftable\s*=\s*', s):
            continue
        out.append(line)
    return '\n'.join(out)


@register(order=350)
def comment_vftable_calls(code, ctx):
    """Comment out __vftable-based virtual calls (IDA artifact, not valid C++)."""
    lines = code.split('\n')
    out = []
    for line in lines:
        s = line.strip()
        if ('->__vftable->' in s or '->__vftable)' in s) and s.endswith(';') \
                and not s.startswith('//'):
            indent = line[:len(line) - len(line.lstrip())]
            out.append(indent + '// [IDA_VFTABLE] ' + s)
            continue
        out.append(line)
    return '\n'.join(out)


@register(order=250)
def remove_explicit_ctor_dtor_calls(code, ctx):
    """Comment out explicit ctor/dtor calls: ((Type*)expr)->Type(args)."""
    lines = code.split('\n')
    out = []
    for line in lines:
        s = line.strip()
        indent = line[:len(line) - len(line.lstrip())]
        ctor_m = re.match(r'\s*\(\((\w+)\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
        if ctor_m and ctor_m.group(1) == ctor_m.group(2):
            out.append(indent + '// [AUTO-COMMENTED] ' + s)
            continue
        ctor_m2 = re.match(r'\s*\(\((\w+)\s*\*\)\s*\(\w+\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
        if ctor_m2 and ctor_m2.group(1) == ctor_m2.group(2):
            out.append(indent + '// [AUTO-COMMENTED] ' + s)
            continue
        out.append(line)
    return '\n'.join(out)


@register(order=260)
def handle_explicit_ctor_in_expressions(code, ctx):
    """Comment out explicit ctor calls: ->ClassName() where ClassName is a known class.

    Matches two patterns:
    1. ((ClassName *)expr)->ClassName(args) — cast type == method (strict)
    2. expr->ClassName(args) — ClassName in game_classes (like old gen_cpp.py)
    """
    lines = code.split('\n')
    out = []
    for line in lines:
        stripped = line.strip()
        if not stripped.endswith(';'):
            out.append(line)
            continue

        # Pattern 1: cast type matches method name
        ctor_pattern = re.search(
            r'\(\(\s*(\w+)\s*\*\s*\)[^)]*\)\s*->\s*(\w+)\s*\(', stripped)
        is_ctor = (ctor_pattern and ctor_pattern.group(1) == ctor_pattern.group(2))

        # Pattern 2: ->ClassName( where ClassName is a known game class
        if not is_ctor:
            m = re.search(r'->\s*([A-Z_]\w+)\s*\(', stripped)
            if m and m.group(1) in store.game_classes:
                is_ctor = True
                ctor_pattern = m  # reuse for name extraction

        if is_ctor:
            called_name = ctor_pattern.group(1) if ctor_pattern else ''
            indent = line[:len(line) - len(line.lstrip())]
            if stripped.startswith('return'):
                cast_m = re.match(
                    r'return\s+(.+?)\s*->\s*%s\s*\(' % re.escape(called_name), stripped)
                if cast_m:
                    out.append(indent + 'return %s; // ctor auto-called' % cast_m.group(1).rstrip())
                    continue
                out.append(indent + 'return this; // [ctor replaced]')
                continue
            elif '=' not in stripped and not stripped.startswith('if') \
                    and not stripped.startswith('while'):
                out.append(indent + '// [AUTO-COMMENTED] ' + stripped)
                continue
            elif '=' in stripped:
                out.append(indent + '// [AUTO-COMMENTED] ' + stripped)
                continue
        out.append(line)
    return '\n'.join(out)
