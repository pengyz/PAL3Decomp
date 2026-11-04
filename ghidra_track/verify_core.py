"""verify_core — B 转换证明纯函数核（独立投影/diff/归一）。

R1 铁则（spec v2 §1 docs/specs/2026-11-04-converter-proof-design.md）：
本模块**禁 import 转换器模块**（gen_plan/import_annotation/plan_to_changeset/
import_standard）——期望侧独立实现，防共享 bug 双侧一致=diff 假绿
（复核实锤例：变体键 int('144_1') 双侧同错把发明偏移证成"正确"）。
归并 tie-break 与 Task 2 同语义但代码独立：owner(==自类)>confirmed>sorted 文件名序>首个。
"""
import glob
import json
import os
import re

# B 侧自动分析产物名——extra 域过滤（否则恒红）
_AUTO_PREFIXES = ('FUN_', 'AUTO_', 'thunk_', 'Catch@', 'caseD_', 'DAT_', 'byte_', 'switchD_', 'j_', '_std_')
# B 侧可承载（可比）字段
_CMP_FIELDS = frozenset({'name', 'signature', 'class', 'adjudication', 'size', 'type'})
# B 侧无载体字段 → unverifiable（须带 reason，禁静默丢——R4）
_NOCARRIER_FIELDS = frozenset({'evidence', 'evidence_level', 'name_source', 'name_note', 'source'})
# B 侧应承载字段（readback 缺席=真缺口 missing，非 unverifiable——mutation field_delete 钉）
_CARRIER_FIELDS = frozenset({'name', 'signature', 'size', 'type'})

_DECIMAL_OFF = re.compile(r'[0-9]+$')


def norm_addr(s):
    """地址归一 → int（切片形——禁 lstrip('0x') 前导零陷阱；按 hex 解析）。"""
    if isinstance(s, int):
        return s  # 已是 int：禁 str 化再 hex 解析（双重扭曲 0x401000→0x4198400）
    t = str(s).strip().lower()
    if t.startswith('0x'):
        t = t[2:]
    return int(t, 16) if t else 0


def _is_auto(name):
    return isinstance(name, str) and name.startswith(_AUTO_PREFIXES)


def _parse_offset(k):
    """known_members 键 → 偏移 int（仅十进制纯数字）| None（变体/异形键=域外，T7/8 处置）。"""
    s = str(k)
    return int(s) if _DECIMAL_OFF.fullmatch(s) else None


def _norm_entry(v):
    if not isinstance(v, dict):
        return v
    return dict(v)


def norm_facts(facts):
    """事实形归一：地址键→int（函数/全局/跳过）、成员偏移→int。"""
    out = {}
    for domain, m in (facts or {}).items():
        if not isinstance(m, dict):
            out[domain] = m
            continue
        if domain == 'structs':
            ns = {}
            for k, v in m.items():
                v = dict(v) if isinstance(v, dict) else v
                if isinstance(v, dict) and isinstance(v.get('members'), dict):
                    v['members'] = {int(ok) if str(ok).isdigit() else ok: ov
                                    for ok, ov in v['members'].items()}
                ns[k] = v
            out[domain] = ns
        else:
            out[domain] = {norm_addr(k): _norm_entry(v) for k, v in m.items()}
    return out


def _merge_claims(ann_map):
    """{文件名: structdata} → {addr_str: claim}（独立实现·确定性）。"""
    out = {}
    for fname in sorted(ann_map.keys()):
        d = ann_map[fname] or {}
        cls = d.get('name')
        for addr, m in (d.get('methods') or {}).items():
            if not isinstance(m, dict) or not m.get('name'):
                continue
            claim = dict(m)
            claim['class'] = cls
            prev = out.get(addr)
            if prev is None:
                out[addr] = claim
            elif claim.get('owner') == cls and prev.get('owner') != prev.get('class'):
                out[addr] = claim
            elif claim.get('adjudication') == 'confirmed' and prev.get('adjudication') != 'confirmed':
                out[addr] = claim
    return out


def project_ann_facts(ann_dir):
    """annotation 目录 → canonical facts（独立解析·R1 铁则）。
    形：{'functions': {addr_int: {'name','signature','class','adjudication'}},
         'structs': {name: {'size','members': {offset_int: {'name','type'}}}},
         'globals': {addr_int: {'name','type'}},
         'skips': {addr_int: {'kind'}}}"""
    funcs = {}
    fp = os.path.join(ann_dir, 'functions.json')
    if os.path.exists(fp):
        raw = json.load(open(fp))
        items = raw.items() if isinstance(raw, dict) else \
            [(i.get('address') or i.get('addr'), i) for i in raw if isinstance(i, dict)]
        for addr, info in items:
            if isinstance(info, dict) and info.get('name'):
                funcs[norm_addr(addr)] = {
                    'name': info['name'],
                    'signature': info.get('signature') or '',
                    'class': info.get('class'),
                    'adjudication': info.get('adjudication'),
                }
    ann_map = {}
    structs = {}
    for f in sorted(glob.glob(os.path.join(ann_dir, 'structs', '*.json'))):
        d = json.load(open(f))
        n = d.get('name')
        if not n:
            continue
        ann_map[os.path.basename(f)] = d
        km = d.get('known_members')
        items = km.values() if isinstance(km, dict) else (km or [])
        members = {}
        for m in items:
            if not isinstance(m, dict) or not m.get('name'):
                continue
            off = _parse_offset(m.get('offset') if m.get('offset') is not None else '?')
            if off is None:
                continue  # 变体/异形键=域外（T7/8）
            ty = m.get('type')
            members[off] = {'name': m['name'],
                            'type': ty if isinstance(ty, str) else 'inline-dict'}
        structs[n] = {'size': d.get('size') or d.get('binary_size'), 'members': members}
    for addr, m in _merge_claims(ann_map).items():
        funcs[norm_addr(addr)] = {
            'name': m['name'],
            'signature': m.get('signature') or '',
            'class': m.get('class'),
            'adjudication': m.get('adjudication'),
        }
    globals_ = {}
    gp = os.path.join(ann_dir, 'globals.json')
    if os.path.exists(gp):
        raw = json.load(open(gp))
        items = raw.items() if isinstance(raw, dict) else \
            [(i.get('address') or i.get('addr'), i) for i in raw if isinstance(i, dict)]
        for addr, info in items:
            if isinstance(info, dict) and info.get('name'):
                globals_[norm_addr(addr)] = {'name': info['name'],
                                             'type': info.get('type')}
    skips = {}
    sp = os.path.join(ann_dir, 'skip_functions.json')
    if os.path.exists(sp):
        raw = json.load(open(sp))
        items = raw.items() if isinstance(raw, dict) else \
            [(a, {}) for a in raw]
        for addr, info in items:
            skips[norm_addr(addr)] = {'kind': 'skip',
                                      'reason': (info or {}).get('reason') if isinstance(info, dict) else None}
    for addr, info in funcs.items():
        if isinstance(info, dict) and info.get('skip'):
            skips[addr] = {'kind': 'skip', 'reason': info.get('skip_reason')}
    return {'functions': funcs, 'structs': structs, 'globals': globals_, 'skips': skips}


def _fmt_key(k):
    return hex(k) if isinstance(k, int) else str(k)


def _cmp_fields(ev, av, ep, res):
    """逐可比字段比较；nocarrier → unverifiable（带 reason）。返回是否有 changed。"""
    changed = False
    for f in sorted(set(ev) | set(av)):
        path = '%s.%s' % (ep, f)
        if f in _NOCARRIER_FIELDS:
            if f in ev and f not in av:
                res['unverifiable'].append({'path': path, 'expected': ev[f],
                                            'actual': None, 'reason': 'no carrier in B'})
            continue
        if f not in _CMP_FIELDS:
            # 未分类字段=必须显式处置（禁静默比/禁静默丢）
            if f in ev and f not in av:
                res['unverifiable'].append({'path': path, 'expected': ev[f],
                                            'actual': None, 'reason': 'field not classified'})
            continue
        if f not in av:
            if f in _CARRIER_FIELDS:
                # B 应承载字段缺席=真缺口（missing 抓红——禁以 unverifiable 豁免）
                res['missing'].append({'path': path, 'expected': ev.get(f),
                                       'actual': None,
                                       'reason': 'carrier field absent from B readback'})
                changed = True
                continue
            # 无载体/归属类字段缺席=无法验证（R4 unverifiable 语义）
            res['unverifiable'].append({'path': path, 'expected': ev.get(f),
                                        'actual': None,
                                        'reason': 'no carrier in B' if f in _NOCARRIER_FIELDS
                                        else 'field absent in B readback'})
            continue
        evv, avv = ev.get(f), av.get(f)
        if evv == avv:
            continue  # match=条目级（调用方在无 changed 时追加一条）
        res['changed'].append({'path': path, 'expected': evv, 'actual': avv, 'reason': None})
        changed = True
    return changed


def diff_facts(expected, actual):
    """五分类 diff：match/missing/changed/extra/unverifiable。
    每项 {'path','expected','actual','reason'}；extra 过滤 B 侧自动名（恒红防）。"""
    e = norm_facts(expected or {})
    a = norm_facts(actual or {})
    res = {'match': [], 'missing': [], 'changed': [], 'extra': [], 'unverifiable': []}
    for domain in sorted(set(e) | set(a)):
        if domain == 'skips':
            continue  # 设计性丢弃域（T7 契约：converter 不转 skip）——不入 verdict
        em = e.get(domain) or {}
        am = a.get(domain) or {}
        for key in sorted(em, key=str):
            ep = '%s/%s' % (domain, _fmt_key(key))
            if key not in am:
                res['missing'].append({'path': ep, 'expected': em[key],
                                       'actual': None, 'reason': None})
                continue
            ev, av = em[key], am[key]
            if domain == 'structs' and isinstance(ev, dict) and isinstance(av, dict):
                # size/type 级 + members 嵌套
                if not _cmp_fields({k: v for k, v in ev.items() if k != 'members'},
                                   {k: v for k, v in av.items() if k != 'members'}, ep, res):
                    res['match'].append({'path': ep, 'expected': ev, 'actual': av,
                                         'reason': None})
                emem = ev.get('members') or {}
                amem = av.get('members') or {}
                for off in sorted(set(emem) | set(amem), key=str):
                    mp = '%s.members[%s]' % (ep, off)
                    if off not in amem:
                        res['missing'].append({'path': mp, 'expected': emem[off],
                                               'actual': None, 'reason': None})
                    elif off not in emem:
                        if not _is_auto((amem[off] or {}).get('name')):
                            res['extra'].append({'path': mp, 'expected': None,
                                                 'actual': amem[off], 'reason': None})
                    else:
                        _cmp_fields(emem[off], amem[off], mp, res)
            elif isinstance(ev, dict) and isinstance(av, dict):
                if not _cmp_fields(ev, av, ep, res):
                    res['match'].append({'path': ep, 'expected': ev, 'actual': av,
                                         'reason': None})
            elif ev != av:
                res['changed'].append({'path': ep, 'expected': ev, 'actual': av,
                                       'reason': None})
            else:
                res['match'].append({'path': ep, 'expected': ev, 'actual': av,
                                     'reason': None})
        for key in sorted(am, key=str):
            if key in em:
                continue
            av = am[key]
            nm = av.get('name') if isinstance(av, dict) else None
            if _is_auto(nm) or (domain == 'structs' and _is_auto(str(key))):
                continue  # extra 域过滤：B 侧自动分析产物不计 extra
            item = {'path': '%s/%s' % (domain, _fmt_key(key)),
                    'expected': None, 'actual': av, 'reason': None}
            if domain in ('functions', 'globals'):
                # 覆盖信号非缺陷：B 必有未认领/CRT/自动面（spec §8 覆盖=A 面注解工作）
                res.setdefault('coverage_extra', []).append(item)
            else:
                res['extra'].append(item)
    return res
