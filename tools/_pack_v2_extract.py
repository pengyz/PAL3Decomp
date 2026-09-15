#!/usr/bin/env python3
"""Pack v2: extend _sig_evidence_pack.json with ret-N for no-evidence clusters.
Read-only MCP usage. Updates entries in place; appends new ones."""
import json, re, sys
sys.path.insert(0, 'tools')
from mcp_query import call

RET_RE = re.compile(r'^(?:retn|ret)(?:\s+([0-9A-Fa-f]+)h?)?\s*$')

def parse_ret_num(rest):
    if not rest: return 0
    if rest.lower().endswith('h'): return int(rest[:-1], 16)
    return int(rest)

def rets_of(addr):
    r = call('disassemble_function', {'start_address': addr}, 90)
    res = r.get('result', r)
    if isinstance(res, dict) and res.get('lines') is None and 'content' in res:
        res = res['content']
    lines = res.get('lines') or []
    rets = []
    for l in lines:
        ins = (l.get('instruction') or '').strip()
        m = RET_RE.match(ins)
        if m: rets.append(parse_ret_num(m.group(1)))
    return rets, len(lines)

wl = json.load(open('data/status/_c2660_adjudication_worklist.json', encoding='utf-8'))
pack = json.load(open('data/status/_sig_evidence_pack.json', encoding='utf-8'))
by_key = {(c['cls'], c['method']): c for c in pack['graded']}

targets = [r for r in wl['noevidence'] if r['addrs'] and len(r['addrs']) == 1]
print('targets:', len(targets))
done = err = 0
for r in targets:
    key = (r['cls'], r['method'])
    addr = r['addrs'][0]
    try:
        rets, nl = rets_of(addr)
    except Exception as ex:
        entry = by_key.setdefault(key, {'cls': r['cls'], 'method': r['method'],
                                        'sites': r['sites'], 'args': r['rendered'],
                                        'addrs': r['addrs']})
        entry['grade'] = 'C-DISASM-ERR'; entry['err'] = str(ex)[:80]
        err += 1
        continue
    entry = by_key.setdefault(key, {'cls': r['cls'], 'method': r['method'],
                                    'sites': r['sites'], 'args': r['rendered'],
                                    'addrs': r['addrs']})
    entry['rets'] = rets
    entry['sites'] = r['sites']; entry['args'] = r['rendered']; entry['addrs'] = r['addrs']
    if not rets:
        entry['grade'] = 'B-NORET'
    elif len(set(rets)) != 1:
        entry['grade'] = 'B-MIXEDRET'
    elif rets[0] % 4 != 0:
        entry['grade'] = 'B-ODDRET'
    else:
        entry['slots'] = rets[0] // 4
        entry['grade'] = 'A-V2'
    done += 1

json.dump(pack, open('data/status/_sig_evidence_pack.json', 'w', encoding='utf-8'),
          ensure_ascii=False, indent=1)
import collections
g = collections.Counter(c.get('grade') for c in pack['graded'])
print('done=%d err=%d' % (done, err))
print('grades now:', dict(g))
slots_new = sum(1 for c in pack['graded'] if c.get('grade') == 'A-V2')
print('new slots entries:', slots_new)
