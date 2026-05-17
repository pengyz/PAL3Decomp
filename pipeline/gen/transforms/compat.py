"""VC6 compatibility transforms.

Order 400-499: Final cleanup for MSVC 6.0 compilation.
"""
import re
from transforms import register
from data import store


# Note: calling convention removal from function def line is in signature.py (order=55)
# This module only handles CC removal from function pointer CASTS in body


@register(order=410)
def remove_thiscall_in_body(code, ctx):
    """Remove __thiscall from function pointer casts in body."""
    code = re.sub(r'__thiscall\s+', '', code)
    code = re.sub(r'__userpurge\s+', '', code)
    code = re.sub(r'__usercall\s+', '', code)
    return code


@register(order=420)
def fix_operator_new(code, ctx):
    """Fix broken operator new: ((operator *)0xNNu)->new() -> operator new(0xNN)."""
    return re.sub(
        r'\(\(operator \*\)(0x[0-9A-Fa-f]+u?)\)->new\(\)',
        r'operator new(\1)', code)


@register(order=430)
def fix_lodword_address(code, ctx):
    """LODWORD(x) = &symbol -> add (unsigned long) cast."""
    return re.sub(
        r'((?:LODWORD|HIDWORD)\s*\([^)]+\))\s*=\s*(&\w+)',
        r'\1 = (unsigned long)\2', code)


@register(order=440)
def fix_mfp_cast(code, ctx):
    """(int)Class::Method -> extract address or use 0 placeholder."""
    def _repl(m):
        cls_method = m.group(1)
        addr_m = re.search(r'_([0-9A-Fa-f]{5,})$', cls_method.split('::')[-1])
        if addr_m:
            return '0x%s' % addr_m.group(1)
        return '0 /* TODO: (int)%s */' % cls_method
    return re.sub(
        r'\(int\)\s*(\w+::(?:~?\w+))\b(?!\s*\()',
        _repl, code)


@register(order=450)
def fix_deref_syntax(code, ctx):
    """Fix Hex-Rays broken dereference: (*)var -> (*var)."""
    return re.sub(r'\(\*\)(\w+)', r'(*\1)', code)


@register(order=460)
def fix_ctor_return(code, ctx):
    """Replace ctor return pattern: return &this->__vftable -> return this."""
    code = re.sub(r'return\s+&this->__vftable\s*;', 'return this;', code)
    code = re.sub(r'return\s+\([^)]+\)\s*&this->__vftable\s*;', 'return this;', code)
    return code


@register(order=470)
def fix_stdiobuf(code, ctx):
    """Fix IDA stdiobuf/ios_base misidentification."""
    if ctx.is_free_function:
        code = code.replace('stdiobuf *', 'UIWnd *')
        code = code.replace('stdiobuf::', 'UIWnd::')
        code = code.replace('std::ios_base *', 'UIWnd *')
    return code
