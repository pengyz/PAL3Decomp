#!/usr/bin/env python3
"""Track B audit: annotation method signatures vs decomp-signature projection.

Compares every structs/*.json methods-table entry against the current
asm/pal3/decomp/*.json signature for the same address, after normalizing:
- hidden this: decomp signatures carry an explicit __hidden this param
  (injected by the pipeline's definite-type adoption); annotation
  signatures don't. Compared param counts are decomp_n - 1.
- type spellings: unsigned __int8 == unsigned char == uchar etc.

Output: agreement counts + data/status/signature_conflicts.json
"""
import json, glob, re, sys, collections

ROOT = __file__.rsplit('/tools/', 1)[0]
import os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

ALIAS = {
    'unsigned __int8': 'unsigned char', 'uchar': 'unsigned char', 'unchar': 'unsigned char',
    '_BYTE': 'unsigned char', 'BYTE': 'unsigned char', 'BOOL': 'int',
    'unsigned __int16': 'unsigned short', 'ushort': 'unsigned short', '_WORD': 'unsigned short',
    'WORD': 'unsigned short',
    'unsigned __int32': 'unsigned int', 'uint': 'unsigned int', '_DWORD': 'unsigned int',
    'DWORD': 'unsigned int', 'UINT': 'unsigned int',
    '__int16': 'short', 'bool': 'char', 'unsigned': 'unsigned int', 'long': 'int', 'ULONG': 'unsigned int',
    '__int32': 'int', '_LONG': 'long', 'LONG': 'long',
    '__int64': 'long long',
    'unsigned long': 'unsigned int',
}


def canon(t):
    if t is None:
        return '?'
    t = t.strip()
    t = re.sub(r'__attribute__\s*\(\(.*\)\)', '', t).strip()
    m = re.match(r'^(.*?)(\w+)?\s*\[[^\]]*\]$', t)
    if m and m.group(1).strip():
        # array param decays to pointer
        t = (m.group(1).strip().rstrip('*') + '*')
    stars = len(t) - len(t.rstrip('*'))
    t = re.sub(r'\*+\s*$', '', t).strip()
    t = re.sub(r'^(struct|class|enum|union)\s+', '', t)
    t = ALIAS.get(t, t)
    return (t or 'void') + '*' * stars


def split_params(params):
    """Top-level comma split respecting nesting."""
    out, depth, cur = [], 0, ''
    for ch in params:
        if ch in '<([':
            depth += 1
        elif ch in '>)]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return [p.strip() for p in out if p.strip()]


def sig_shape(sig, drop_this=False):
    """Return (canon_ret, [canon_params]) or None."""
    sig = sig.strip()
    pm = re.search(r'\((.*)\)', sig, re.S)
    if not pm:
        return None
    head = sig[:sig.index('(')].strip()
    head = re.sub(r'^virtual\s+', '', head)
    # strip trailing qualified method name FIRST (it may sit after the cc),
    # then the calling convention. '(?:~)?' handles dtors ('Cls::~Cls');
    # loop handles doubly-qualified tails ('Cls::Nested::Method').
    while True:
        h2 = re.sub(r'\s*[A-Za-z_]\w*(?:::~?[A-Za-z_]\w*)+\s*$', '', head).strip()
        if h2 == head:
            break
        head = h2
    head = re.sub(r'\s+__(?:noreturn|spoils<[^>]*>)\s*$', '', head).strip()
    # strip trailing unqualified function name (free-function style heads like
    # 'int __cdecl RandomPickValues') BEFORE the cc strip — the cc may not sit
    # at the head end when a name follows it. Keyword-guarded so 'unsigned int'
    # survives.
    _TYPE_KW = {'int','void','char','short','long','float','double','unsigned','signed','bool',
                'BYTE','WORD','DWORD','BOOL','UINT','HRESULT','__int8','__int16','__int32','__int64'}
    _toks = head.split()
    if len(_toks) > 1 and _toks[-1] not in _TYPE_KW and re.match(r'^[A-Za-z_]\w*$', _toks[-1]):
        head = ' '.join(_toks[:-1])
    head = re.sub(r'\b(__userpurge|__usercall|__thiscall|__cdecl|__stdcall|__fastcall)(@<[^>]*>)?\s*$', '', head).strip()
    ret = canon(head)
    params = pm.group(1).strip()
    plist = split_params(params) if params not in ('', 'void') else []
    if drop_this and plist and re.match(r'^[A-Za-z_]\w*\s*\*\s*(__hidden\s+)?this', plist[0]):
        plist = plist[1:]
    return (ret, [canon(re.sub(r'\s*\w+\s*$', '', p).strip() or p) for p in plist])


def main():
    decomp_sigs = {}
    for fp in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json')):
        m2 = re.search(r'_([0-9a-f]{8})\.json$', fp)
        if m2:
            decomp_sigs['0x' + m2.group(1).upper()] = (os.path.basename(fp), json.load(open(fp)).get('signature', ''))

    methods = {}
    funcs_json = {}
    fp_fj = os.path.join(ROOT, 'data', 'annotations', 'functions.json')
    if os.path.exists(fp_fj):
        funcs_json = json.load(open(fp_fj))
    for fp in glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json')):
        cls = os.path.basename(fp)[:-5]
        s = json.load(open(fp))
        for addr, info in s.get('methods', {}).items():
            k = (addr if addr.startswith('0x') else '0x' + addr).upper().replace('0X', '0x')
            methods.setdefault(k, []).append((cls, info))

    agree = dr = dn = both = nskip = 0
    rows = []
    for addr, entries in sorted(methods.items()):
        if addr not in decomp_sigs:
            continue
        fj = funcs_json.get(addr)
        if fj and fj.get('type') == 'skip':
            # deliberately demoted (e.g. misattribution evidence) — the decomp
            # generic form is the accepted state; count separately, not a conflict
            nskip += 1
            continue
        cls, info = entries[0]
        ann = info.get('signature', '')
        if not ann:
            continue
        # 'this' is a C++ keyword — an explicit Cls *this param is the implicit
        # this spelled out (old-format signatures); drop on BOTH sides
        a = sig_shape(ann, drop_this=True)
        b = sig_shape(decomp_sigs[addr][1], drop_this=True)
        if not a or not b:
            continue
        both += 1
        fname = decomp_sigs[addr][0]
        mname = info.get('name', '')
        is_special = mname.startswith('~') or mname in ('_scalar_dtor', '_sdtor') or mname == cls or mname.endswith('_' + cls)
        malformed = False
        head_txt = ann.split('(', 1)[0]
        ccs = re.findall(r'__(?:thiscall|cdecl|stdcall|fastcall|userpurge|usercall)', head_txt)
        if len(ccs) > 1 or re.search(r'\)\s*\)\s*$', ann):
            malformed = True
        if malformed:
            rows.append(['MALFORMED', addr, cls, mname, ann[:40], '', fname])
            continue
        if a[0] != b[0]:
            if is_special and b[0] == 'int':
                # ctor/dtor decomp 'int' return = EAX=this display artifact
                pass
            else:
                dr += 1
                rows.append(['RET', addr, cls, mname, a[0], b[0], fname])
        elif a[1] != b[1]:
            if len(a[1]) == len(b[1]):
                # equal counts: report per-param type diffs
                diffs = []
                for i, (pa, pb) in enumerate(zip(a[1], b[1])):
                    if pa != pb:
                        diffs.append('#%d %s!=%s' % (i, pa[:14], pb[:14]))
                rows.append(['PTYPE', addr, cls, mname, str(len(a[1])), ' | '.join(diffs), fname])
            else:
                dn += 1
                rows.append(['NARGS', addr, cls, mname, str(len(a[1])), str(len(b[1])), fname])
        else:
            agree += 1

    print('methods with decomp counterpart:', both)
    print('agree: %d | ret-disagree: %d | param-disagree: %d' % (agree, dr, dn))
    for r in rows[:25]:
        print(' %-6s %s %-16s %-26s ann=%s decomp=%s' % (r[0], r[1], r[2], r[3][:26], r[4][:22], r[5][:22]))
    out = os.path.join(ROOT, 'data', 'status', 'signature_conflicts.json')
    json.dump(rows, open(out, 'w'), indent=1)
    print('saved %d conflicts -> %s' % (len(rows), out))


if __name__ == '__main__':
    main()
