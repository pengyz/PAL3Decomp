"""VC6 mangled name generator for PAL3 decompilation pipeline.
Shared between apply_annotations.py and export_full.py."""
import re

_TC = {
    'void': 'X', 'char': 'D', 'unsigned char': 'E',
    'short': 'F', 'unsigned short': 'G',
    'int': 'H', 'unsigned int': 'I',
    'long': 'J', 'unsigned long': 'K',
    'float': 'M', 'double': 'N', 'bool': '_N',
    'BYTE': 'E', 'WORD': 'G', 'DWORD': 'K', 'BOOL': 'I', 'UINT': 'I',
}
_CC = {'__thiscall': 'A', '__cdecl': 'C', '__stdcall': 'G', '__fastcall': 'I'}


def encode_type(t):
    t = t.strip()
    is_const = t.startswith('const ')
    if is_const: t = t[6:].strip()
    is_ref = t.endswith('&')
    if is_ref: t = t[:-1].strip()
    ptr = 0
    while t.endswith('*'):
        t = t[:-1].strip(); ptr += 1
    tag = None
    if t.startswith('struct '):
        tag = 'U'; t = t[7:].strip()
    elif t.startswith('class '):
        tag = 'V'; t = t[6:].strip()
    code = _TC.get(t)
    if code is None and ptr > 0:
        code = 'U' + t + '@@'
    elif code is None and tag:
        code = tag + t + '@@'
    elif code is None:
        if t.startswith('unsigned '):
            code = _TC.get(t[9:].strip())
        if code is None:
            code = 'H'
    if is_ref:
        code = 'A' + code
    for _ in range(ptr):
        code = 'P' + ('B' if (is_const and _ == 0) else 'A') + code
    return code


def strip_param_name(p):
    m = re.match(r'^(.+\*)\s*\w*$', p)
    if m: return m.group(1).strip()
    m = re.match(r'^(.+?)\s+\w+$', p)
    if m: return m.group(1).strip()
    return p.strip()


def _mangle_class_chain(cls_name):
    """Convert 'AStarPathFinder::NODE' to 'NODE@AStarPathFinder' (MSVC format)."""
    parts = cls_name.split('::')
    return '@'.join(reversed(parts))


def mangle(cls_name, method_name, sig):
    """Compute VC6 mangled name for a class method.
    
    Args:
        cls_name: Class name — may include :: for nested (e.g. 'AStarPathFinder::NODE')
        method_name: Method name (e.g. 'FindInOpen')
        sig: Signature string (e.g. 'int __thiscall(int nTileIdx)')
    
    Returns:
        Mangled name string (e.g. '?FindInOpen@NODE@AStarPathFinder@@QAEHH@Z')
    """
    cls_chain = _mangle_class_chain(cls_name)
    
    paren = sig.find('(') if sig else -1
    if paren == -1:
        return '?' + method_name + '@' + cls_chain + '@@QAEXXZ'
    
    prefix = sig[:paren].strip()
    pstr = sig[paren + 1:sig.rfind(')')] if sig.rfind(')') > paren else ''
    
    cc = '__thiscall'
    for c in ['__thiscall', '__cdecl', '__stdcall', '__fastcall']:
        if c in prefix: cc = c; break
    
    ret = prefix.replace(cc, '').strip()
    ret = re.sub(r'\w+::\w+', '', ret).strip()
    pstr = re.sub(r'\w+\s*\*\s*(?:__hidden\s+)?this\s*,?\s*', '', pstr)
    
    params = []
    if pstr and pstr.strip() not in ('', 'void'):
        depth = 0; cur = ''
        for ch in pstr:
            if ch in '<([': depth += 1; cur += ch
            elif ch in '>)]': depth -= 1; cur += ch
            elif ch == ',' and depth == 0:
                if cur.strip(): params.append(cur.strip()); cur = ''
            else: cur += ch
        if cur.strip(): params.append(cur.strip())
    
    r = '?' + method_name + '@' + cls_chain + '@@'
    r += 'Q' + _CC.get(cc, 'A') + 'E'
    r += encode_type(ret)
    for p in params:
        r += encode_type(strip_param_name(p))
    r += '@Z'
    return r
