#!/usr/bin/env python3
"""Validate vc6_mangler against PDB ground truth extracted from the IDB.

Ground truth: /tmp/pdb_pairs_long.json — [ida_mangled, demangled_long]
pairs (3237) dumped by the IDA worker.

NOTE (2026-08-29, G1): the mangler is now aligned to cl.exe COFF output
(verified 10/10 against wine-compiled obj symbols — /tmp/mangle_probe/).
The PDB/IDA serialization differs from cl COFF form for void-parameter
tails ('X@Z' vs 'XXZ') and ctor parameter folding, so this validator's
absolute percentage is a dev metric, not the S4 gate. The authoritative
gate is compare_pal3.py matching OUR obj symbols.

IDA serializes ctors/dtors as '?Cls@Cls@@REST' / '?~Cls@Cls@@REST';
real MSVC6 COFF symbols are '??0Cls@@REST' / '??1Cls@@REST'. The
normalizer converts IDA form to real form where the mapping is known.

Usage: python3 pipeline/validate_mangler.py [--show N] [--only CAT]
"""

import argparse
import collections
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
sys.path.insert(0, str(REPO / 'pipeline' / 'ida'))
import vc6_mangler as vm  # noqa: E402

PAIRS = "/tmp/pdb_pairs_long.json"


def split_mangled(m):
    """'?METHOD@A@B@@REST' -> (method, ['B','A'], REST). None if malformed."""
    assert m.startswith('?')
    body = m[1:]
    parts = body.split('@')
    if len(parts) < 3:
        return None
    method = parts[0]
    chain_segs = []
    i = 1
    while i < len(parts):
        if parts[i] == '':
            break
        chain_segs.append(parts[i])
        i += 1
    consumed = sum(len(p) + 1 for p in [method] + chain_segs)
    rest = body[consumed + 1:]  # skip the second '@' of the '@@' terminator
    return method, list(reversed(chain_segs)), rest


def normalize_ida_mangled(m):
    """IDA '?Cls@Cls@@QAEX@Z' (ctor) / '?~Cls@Cls@@...' (dtor) -> real form."""
    if m.startswith('??'):
        return m
    sp = split_mangled(m)
    if not sp:
        return m
    method, chain, rest = sp
    if not chain:
        return m
    # IDA/PDB serializes void-void functions as 'X@Z'; cl.exe COFF symbols
    # use 'X' + 'XZ' (ret-X + void-param-X + Z). Verified against cl output.
    if rest == 'X@Z':
        rest = 'XXZ'
    last = chain[-1]
    if method == last or (method.startswith('~') and method[1:] == last):
        # IDA serializes ctors/dtors with a pseudo-return 'X' inserted
        # after the qualifier; real COFF = qual3 + '@' + params + tail,
        # where void params encode 'X' and the tail is 'Z' (void) or
        # '@Z' (with params). Measured against exe strings:
        #   ??0gbParticleEffect@@QAE@XZ / ??0gbActorMgr@@QAE@PAVgbGfxManager@@@Z
        q3, body = rest[:3], rest[3:]
        if body.startswith('X'):
            body = body[1:]
        if body == 'XZ' or body == 'Z' or body == '@Z':
            params = ''
        elif body.endswith('@Z'):
            params = body[:-2]
        elif body.endswith('Z'):
            params = body[:-1]
        else:
            params = body
        pre = '??0' if method == last else '??1'
        if params:
            return pre + '@'.join(chain) + '@@' + q3 + '@' + params + '@Z'
        return pre + '@'.join(chain) + '@@' + q3 + '@XZ'
    return m


_ACCESS_RE = re.compile(r'^(public|private|protected):\s*')
_CC_RE = re.compile(r'__(thiscall|cdecl|stdcall|fastcall)\b\s*')


def parse_pretty(d):
    """Long-form demangle:
    'public: void * __thiscall A::B::m(int)'
    -> (cls='A::B', method='m', sig='void * __thiscall(int)')"""
    s = d
    m = _ACCESS_RE.match(s)
    if m:
        s = s[m.end():]
    s = re.sub(r'^(virtual|static)\s+', '', s)
    is_static = ' static ' in d
    par = s.find('(')
    if par < 0:
        return None
    head = s[:par].strip()
    params = s[par:].strip()
    mc = _CC_RE.search(head)
    if mc:
        cc = '__' + mc.group(1)
        ret = head[:mc.start()].strip()
        qname = head[mc.end():].strip()
    else:
        # no cc keyword: return type is every token before the first
        # token that carries the '::' qualification
        toks = head.split()
        qstart = next((i for i, t in enumerate(toks) if '::' in t), None)
        if qstart is None:
            return None
        ret = ' '.join(toks[:qstart])
        qname = ' '.join(toks[qstart:])
    if '::' not in qname:
        return None
    cls, method = qname.rsplit('::', 1)
    # Special names (ctor/dtor): IDA's demangle presents the implied
    # this-pointer as the "return type" — fold it back into params.
    base_last = cls.split('::')[-1]
    if method in (base_last, '~' + base_last):
        if ret and ret != 'void':
            inner = params[1:-1].strip() if params.endswith(')') else params[1:].strip()
            params = '(%s%s)' % (ret, (', ' + inner) if inner else '')
        ret = 'void'
    sig = '%s %s%s' % (ret, cc if mc else '', params)
    cvm = re.search(r'\)\s*(const(?:\s+volatile)?)?\s*(volatile)?\s*$', params)
    cv = ''
    if cvm and (cvm.group(1) or cvm.group(2)):
        cv = ' '.join(x for x in (cvm.group(1), cvm.group(2)) if x)
    return cls, method, sig, cv, is_static


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--show', type=int, default=0)
    ap.add_argument('--only', default=None, help='substring filter on pretty name')
    args = ap.parse_args()

    pairs = json.load(open(PAIRS))
    cats = collections.Counter()
    misses = collections.defaultdict(list)
    n_ok = n_try = 0
    for m, d in pairs:
        if args.only and args.only not in d:
            continue
        parsed = parse_pretty(d)
        if not parsed:
            # empty demangles (IDA failed) and free functions (no '::')
            # are ground-truth artifacts, not mangler gaps
            cats['artifact (non-member/undemangled)'] += 1
            continue
        cls, method, sig, cv, is_static = parsed
        expect = normalize_ida_mangled(m)
        # virtuality is not visible in the demangled text — probe the
        # virtual variant when the plain form misses
        tries = [(False, is_static)]
        if not is_static:
            tries.append((True, False))
        got, hit_virtual = None, False
        for virt, stat in tries:
            try:
                got = vm.mangle(cls, method, sig, cv=cv, virtual_=virt, static_=stat)
            except Exception as e:
                cats['mangler-exception'] += 1
                misses['mangler-exception'].append((d, m, str(e)[:60]))
                got = None
                break
            if got == expect:
                hit_virtual = virt
                break
        n_try += 1
        if got == expect:
            n_ok += 1
            if hit_virtual:
                cats['exact (virtual probe)'] += 1
            continue
        if got is None:
            continue
        else:
            # categorize by first structural divergence
            if got[:1] != expect[:1] or (got.startswith('??') != expect.startswith('??')):
                cat = 'special-name-form'
            elif got.split('@@')[0] != expect.split('@@')[0]:
                cat = 'name-section'
            else:
                gq, eq = got.split('@@', 1)[1], expect.split('@@', 1)[1]
                if gq[:3] != eq[:3]:
                    cat = 'qualifier/cc (prefix 3)'
                else:
                    cat = 'params-or-return'
            cats[cat] += 1
            misses[cat].append((d, expect, got))
    print('tried %d, exact %d (%.1f%%)' % (n_try, n_ok, 100.0 * n_ok / max(n_try, 1)))
    for c, n in cats.most_common():
        print('  %-28s %5d' % (c, n))
    if args.show:
        for cat, items in misses.items():
            print('\n=== %s (showing %d) ===' % (cat, min(args.show, len(items))))
            for d, e, g in items[:args.show]:
                print('  pretty : %s' % d)
                print('  expect : %s' % e)
                print('  got    : %s' % g)


if __name__ == '__main__':
    main()
