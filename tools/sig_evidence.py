#!/usr/bin/env python3
"""Phase-1 evidence pack generator for C2660 signature mismatches.

For every C2660 ("function does not take N parameters") error:
  1. attribute the callee to its true class (call-site text: `Cls::M(`
     prefix, else the caller file's own class for unqualified calls);
  2. collect the callee's ret instructions via MCP disassembly
     (instruction-accurate, not byte-grep);
  3. grade the cluster:
       A   rets unanimous, N%4==0, param slots == caller arg count
       B   anything structurally ambiguous (mixed rets, N%4!=0,
           call sites disagreeing on arg count, sret suspected)
       C   attribution failed (multi-address binding / object call
           without type context)
No annotation is modified here - output is a graded evidence pack for
human review (A-grade bulk, B-grade per-item, C deferred).
"""
import json, glob, re, sys
from collections import Counter, defaultdict

sys.path.insert(0, 'tools')
from mcp_query import call

BASE = 'data/status/baselines/latest.json'
OUT = 'data/status/_sig_evidence_pack.json'

RET_RE = re.compile(r'^(?:retn|ret)(?:\s+([0-9A-Fa-f]+)h?)?\s*$')


def parse_ret_num(rest):
    if not rest:
        return 0
    if rest.lower().endswith('h'):
        return int(rest[:-1], 16)
    return int(rest)


def load_errors():
    n = json.load(open(BASE, encoding='utf-8'))['results']
    errs = []
    for u, r in n.items():
        cls = None
        m = re.search(r'/([A-Za-z_][\w]*)\.cpp$', u)
        if m:
            cls = m.group(1)
        for e in r.get('errors', []):
            if e['code'] != 'C2660':
                continue
            mm = re.search(r"'([\w:~=]+)' : function does not take (\d+) parameters", e['msg'])
            if not mm:
                continue
            errs.append({'file': u, 'line': e.get('line'), 'cls': cls,
                         'method': mm.group(1), 'caller_args': int(mm.group(2))})
    return errs


def load_method_addrs():
    """(cls, method) -> [addr, ...] from structs annotations."""
    m2a = {}
    for p in glob.glob('data/annotations/structs/*.json'):
        d = json.load(open(p, encoding='utf-8'))
        cls = d.get('name')
        for a, m in (d.get('methods') or {}).items():
            mn = str(m.get('name', ''))
            m2a.setdefault((cls, mn), []).append(int(a, 16))
            # operator= style: '=' annotates as 'operator=' or '='
            if mn in ('operator=',):
                m2a.setdefault((cls, '='), []).append(int(a, 16))
    return m2a


def call_site_class(file, line, method):
    """Read the generated cpp call site; return the class of the callee."""
    try:
        t = open(file, encoding='utf-8', errors='replace').read().split('\n')
        txt = t[line - 1] if line and line <= len(t) else ''
    except Exception:
        return None
    m = re.search(r'([\w]+)::' + re.escape(method) + r'\s*\(', txt)
    if m:
        return m.group(1)
    return None


def rets_of(addr):
    r = call('disassemble_function', {'start_address': '0x%08X' % addr}, 90)
    res = r.get('result', r)
    lines = res.get('lines') or []
    rets = []
    for l in lines:
        ins = l.get('instruction', '').strip()
        m = RET_RE.match(ins)
        if m:
            rets.append(parse_ret_num(m.group(1)))
    return rets, len(lines)


def main():
    errs = load_errors()
    print('C2660 errors parsed:', len(errs))
    m2a = load_method_addrs()

    # group by (attributed class, method)
    clusters = defaultdict(list)
    unattr = []
    for e in errs:
        cls = call_site_class(e['file'], e['line'], e['method'])
        if cls is None:
            cls = e['cls']
        if cls is None:
            unattr.append(e)
            continue
        clusters[(cls, e['method'])].append(e)
    print('clusters:', len(clusters), '| unattributed:', len(unattr))

    pack = {'graded': [], 'unattributed': len(unattr)}
    disasm_cache = {}

    for (cls, meth), sites in sorted(clusters.items()):
        addrs = sorted(set(m2a.get((cls, meth), [])))
        entry = {'cls': cls, 'method': meth, 'sites': len(sites),
                 'args': sorted(set(s['caller_args'] for s in sites)),
                 'addrs': ['0x%08X' % a for a in addrs]}
        if not addrs:
            entry['grade'] = 'C-NOADDR'
            pack['graded'].append(entry)
            continue
        if len(addrs) > 1:
            entry['grade'] = 'C-MULTIADDR'
            entry['addrs_detail'] = entry['addrs']
            pack['graded'].append(entry)
            continue
        addr = addrs[0]
        if addr in disasm_cache:
            rets = disasm_cache[addr]
        else:
            try:
                rets, nl = rets_of(addr)
                disasm_cache[addr] = rets
            except Exception as ex:
                entry['grade'] = 'C-DISASM-ERR'
                entry['err'] = str(ex)[:80]
                pack['graded'].append(entry)
                continue
        entry['rets'] = rets
        caller_args = entry['args']
        if not rets:
            entry['grade'] = 'B-NORET'
        elif len(set(rets)) != 1:
            entry['grade'] = 'B-MIXEDRET'
        elif rets[0] % 4 != 0:
            entry['grade'] = 'B-ODDRET'
        else:
            slots = rets[0] // 4
            entry['slots'] = slots
            if len(caller_args) == 1 and slots == caller_args[0]:
                entry['grade'] = 'A'
            elif len(caller_args) > 1:
                entry['grade'] = 'B-ARGCONFLICT'
            else:
                entry['grade'] = 'B-SLOTMISMATCH'
        pack['graded'].append(entry)

    grades = Counter(g['grade'] for g in pack['graded'])
    print('grades:', dict(grades))
    json.dump(pack, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('pack ->', OUT)
    return pack


if __name__ == '__main__':
    main()
