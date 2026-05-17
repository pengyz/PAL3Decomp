"""Type system fixes for IDA/Hex-Rays output.

Order 100-199: Fix type representations before name resolution.
"""
import re
import struct as _struct
from transforms import register


@register(order=100)
def fix_coerce_float(code, ctx):
    """COERCE_FLOAT(literal) -> inline float value (can't take & of literal)."""
    def _repl(m):
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
    return re.sub(r'COERCE_FLOAT\((\s*-?(?:0x[0-9A-Fa-f]+|\d+)\s*)\)', _repl, code)


@register(order=110)
def fix_ida_int_types(code, ctx):
    """IDA __int8/__int16 -> standard C types."""
    code = code.replace('unsigned __int8', 'unsigned char')
    code = code.replace('signed __int8', 'signed char')
    code = code.replace('unsigned __int16', 'unsigned short')
    code = code.replace('signed __int16', 'short')
    code = re.sub(r'\b__int8\b', 'char', code)
    code = re.sub(r'\b__int16\b', 'short', code)
    return code


@register(order=120)
def fix_ll_suffix(code, ctx):
    """VC6 compatibility: LL suffix -> i64, uLL -> ui64."""
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)uLL\b', r'\1ui64', code)
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)LL\b', r'\1i64', code)
    code = re.sub(r'(\b\d+)LL\b', r'\1i64', code)
    return code


@register(order=130)
def fix_vtable_types(code, ctx):
    """Replace IDA vtable struct types with void (not real C++ types)."""
    return re.sub(r'\bvtbl_[0-9A-Fa-f]+\b', 'void', code)


@register(order=140)
def fix_throwinfo(code, ctx):
    """Fix IDA exception type name: _ThrowInfo -> _s__ThrowInfo (MSVC6 CRT)."""
    return code.replace('(_ThrowInfo *)', '(_s__ThrowInfo *)')
