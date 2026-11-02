"""C++ 重载铁律缺陷探测器（2026-11-02）。
铁律：同(类,名,签名)双址=C++ 不可能共存 ⇒ 必为注解缺陷（归属错/语义名错）；
合成物（_scalar_dtor/thunk 等）另账不入缺陷。__ovl_ 机制曾遮盖此类问题——
归一化即揭盖。用法: python3 tools/cxx_collision_detector.py
"""
import glob
import json
import re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SIG_TAIL = re.compile(r'\([^()]*\)\s*$')
OVL_SUFFIX = re.compile(r'__ovl_.*$')
PARAM_NAME = re.compile(r'(\w)\s+\w+\s*$')
SYNTH = re.compile(r'(_scalar_dtor|_vector_dtor|_sdtor|~|thunk|_init_)', re.I)


def canon_name(name):
    """归一名：剥签名尾巴 (void) → 剥 __ovl_ 全后缀（hex/非hex/无尾三形）。
    真名内嵌 _x/_y 段保留（Method_x__ovl_1 → Method_x）。"""
    n = SIG_TAIL.sub('', (name or '').strip())
    n = OVL_SUFFIX.sub('', n)
    return n.strip()


def sig_key(sig):
    """归一签名：去参名/空白（int __thiscall(int a2) ≡ int __thiscall(int)）。"""
    s = re.sub(r'\s+', ' ', (sig or '').strip())
    s = re.sub(r'(\w)\s+\w+([,)])', r'\1\2', s)   # 参数名剥
    s = s.replace(', ', ',')
    return s


def find_collisions(entries):
    """同(class, canon_name, sig_key) 多址=铁律违反组。entries=[{class,name,sig,addr}]。"""
    groups = defaultdict(list)
    for e in entries:
        if SYNTH.search(e.get('name') or ''):
            continue                     # 合成物另账
        key = (e.get('class') or '', canon_name(e.get('name')), sig_key(e.get('sig')))
        groups[key].append(e['addr'])
    return [{'class': k[0], 'name': k[1], 'sig': k[2], 'addrs': v}
            for k, v in groups.items() if len(v) > 1]


def main():
    entries = []
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        cls = d.get('name') or ''
        for addr, m in (d.get('methods') or {}).items():
            if isinstance(m, dict) and m.get('name'):
                entries.append({'class': cls, 'name': m['name'],
                                'sig': m.get('signature') or '', 'addr': addr})
    for addr, m in (json.load(open(ROOT / 'data/annotations/functions.json'))).items():
        if isinstance(m, dict) and m.get('name'):
            entries.append({'class': '', 'name': m['name'],
                            'sig': m.get('signature') or '', 'addr': addr})
    coll = find_collisions(entries)
    out = {'total_entries': len(entries), 'collision_groups': len(coll), 'groups': coll}
    Path(ROOT / 'data/status/cxx_collision_census.json').write_text(
        json.dumps(out, ensure_ascii=False, indent=2))
    print('探测量 %d | 铁律违反组 %d' % (len(entries), len(coll)))
    for c in coll[:15]:
        print('  [%s] %s(%s) ×%d %s' % (c['class'] or 'global', c['name'], c['sig'],
                                        len(c['addrs']), c['addrs'][:3]))


if __name__ == '__main__':
    main()


def cxx_sig_key(sig):
    """C++ 严格重载键：返回型不参与 · this 剥 · virtual/static 非签 · cv 参与。"""
    s = re.sub(r'\b(virtual|static)\b', '', sig or '')
    s = re.sub(r'\b\w+\s*\*\s*(?:__hidden\s+)?this\s*,?\s*', '', s)   # this 剥
    paren = s.find('(')
    if paren == -1:
        return ('', s.strip())
    cc = ''
    for c in ('__thiscall', '__cdecl', '__stdcall', '__fastcall'):
        if c in s[:paren]:
            cc = c
            break
    cv = 'const' if re.search(r'\)\s*const\s*$', s) else ''
    if re.search(r'\)\s*volatile\s*$', s):
        cv += ' volatile'
    params = s[paren + 1:s.rfind(')')] if s.rfind(')') > paren else ''
    params = re.sub(r'(\w)\s+\w+\s*([,)])', r'\1\2', params)
    params = re.sub(r'\s+', '', params)
    return (cc, cv, params)
