#!/usr/bin/env python3
"""[L-TAILADDR返回型裁决 2026-11-17] C2555八组批裁: 体分析定谳→语料signature修正。

判据( HideAll 首例三证推广 ):
1. 体语义: return未赋值变量/无return = VOID(出口eax残留伪影); return已赋值变量/
   字面量 = INT-ISH; return this = PTR
2. 原源码约束: override合法→基类派生返回型必一致 → 全组统一到体证据裁决值
3. 修正落点: 语料signature字段(管线单向律: decomp=codegen唯一真相源) + 注解
   methods sig_model同步(C9门禁读注解)
输出: data/status/ltailaddr_adjudications_20261117.json
"""
import json
import glob
import os
import re
import sys
import collections

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
OUT = os.path.join(ROOT, 'data', 'status', 'ltailaddr_adjudications_20261117.json')


def classify_return(body):
    """体返回语义分类: void_ish / int_ish / ptr_ish / none(无函数体)。"""
    if not body or not body.strip():
        return None
    rets = re.findall(r'return\s+([^;]+);', body)
    if not rets:
        return 'void_ish'
    verdicts = []
    for expr in rets:
        expr = expr.strip()
        if expr == 'this':
            verdicts.append('ptr_ish')
            continue
        if re.match(r'^-?\d+$', expr) or expr in ('0', '1', 'true', 'false'):
            verdicts.append('int_ish')
            continue
        m = re.match(r'^([A-Za-z_]\w*)$', expr)
        if m:
            var = m.group(1)
            if re.search(r'\b%s\s*=[^=]' % re.escape(var), body):
                verdicts.append('int_ish')
            else:
                verdicts.append('void_ish')  # 未赋值=eax残留伪影(HideAll三证首例)
        else:
            verdicts.append('int_ish')  # 复合表达式=计算值
    if 'int_ish' in verdicts:
        return 'int_ish'
    if 'ptr_ish' in verdicts:
        return 'ptr_ish'
    return 'void_ish'


def set_return(sig_str, new_ret):
    """改写signature字符串的返回型token。"""
    return re.sub(r'^(virtual\s+)([\w:]+(?:\s*\*)?)\s*',
                  lambda m: m.group(1) + new_ret + ' ', sig_str, count=1)


def main():
    # 目标组(新鲜census)
    r = json.load(open(os.path.join(ROOT, 'data', 'status', 'probe_census.json'), encoding='utf-8'))
    pairs = set()
    for u in r['s2']['results']:
        for e in (u.get('errors') or []):
            if e.get('code') == 'C2555':
                m = re.match(r"'([\w:]+)' : overriding virtual function differs from '([\w:]+)'",
                             e.get('msg') or '')
                if m:
                    pairs.add((m.group(2), m.group(1)))
    groups = collections.defaultdict(set)
    for base, derived in pairs:
        for full in (base, derived):
            c, mm = full.split('::')
            groups[(c, mm)].add(full)

    # 语料装载: name字段 → 组成员匹配
    corpus = {}   # (cls, method) -> list of (file, sig, body)
    for fp in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json')):
        try:
            d = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        nm = str(d.get('name') or '')
        m = re.match(r'^([\w:]+)::([\w~]+)\s*\(', nm)
        if not m:
            continue
        key = (m.group(1), m.group(2))
        corpus.setdefault(key, []).append((os.path.basename(fp), d.get('signature') or '',
                                           d.get('decompiled_c') or ''))

    report = {}
    manual = []
    for (bc, bm), members in sorted(groups.items()):
        evs = []
        verdicts = collections.Counter()
        for full in sorted(members):
            c, mm = full.split('::')
            for f, sig, body in corpus.get((c, mm), []):
                v = classify_return(body)
                verdicts[v] += 1
                evs.append({'member': full, 'file': f, 'sig': sig, 'verdict': v})
        if not evs:
            manual.append('%s::%s (无语料)' % (bc, bm))
            continue
        # 裁决: 体证据多数; 无body信息的成员不参与
        real = {k: v for k, v in verdicts.items() if k}
        if not real:
            manual.append('%s::%s (全组无体)' % (bc, bm))
            continue
        if len(real) == 1:
            verdict = list(real)[0]
        else:
            # 混合: int_ish优先(有真实返回); void_ish vs ptr_ish→人工
            if 'int_ish' in real:
                verdict = 'int_ish'
            elif 'void_ish' in real and 'ptr_ish' in real:
                manual.append('%s::%s (void/ptr冲突%s)' % (bc, bm, dict(real)))
                continue
            else:
                verdict = list(real)[0]
        ret_map = {'void_ish': 'void', 'int_ish': 'int', 'ptr_ish': 'void *'}
        new_ret = ret_map[verdict]
        report['%s::%s' % (bc, bm)] = {
            'verdict': verdict, 'new_return': new_ret,
            'verdict_dist': dict(real), 'members': evs,
            'fixes': []}

    # 应用: 语料signature改写 + 注解sig_model同步
    n_corpus = n_ann = 0
    for key, rep in report.items():
        new_ret = rep['new_return']
        for ev in rep['members']:
            fp = os.path.join(ROOT, 'asm', 'pal3', 'decomp', ev['file'])
            try:
                d = json.load(open(fp, encoding='utf-8'))
            except Exception:
                continue
            old_sig = d.get('signature') or ''
            new_sig = set_return(old_sig, new_ret)
            if new_sig != old_sig:
                d['signature'] = new_sig
                d['sig_note'] = ('L-TAILADDR定谳20261117: 返回型→%s(体=%s, '
                                 '组%s证据%s); 原sig=%r' % (new_ret, rep['verdict'],
                                                          key.rsplit('::', 1)[0],
                                                          rep['verdict_dist'], old_sig))
                json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
                rep['fixes'].append(ev['file'])
                n_corpus += 1
        # 注解同步: 组内所有成员名匹配的methods条目
        for full in rep['members'] and {m['member'] for m in rep['members']}:
            c, mm = full.split('::')
            afp = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % c)
            if not os.path.exists(afp):
                continue
            ad = json.load(open(afp, encoding='utf-8'))
            changed = False
            for a, e in (ad.get('methods') or {}).items():
                if str(e.get('name') or '').split('::')[-1] == mm:
                    sm = e.get('sig_model') or {}
                    if sm.get('return') != new_ret and not sm.get('pending'):
                        sm['return'] = new_ret
                        e['sig_model'] = sm
                        e['signature'] = '%s __thiscall(%s)' % (
                            new_ret, ', '.join(p.get('type', 'int') for p in (sm.get('params') or [])))
                        e['name_note'] = (e.get('name_note') or '') + \
                            ' | L-TAILADDR定谳20261117: 返回型→%s(体证据%s)' % (new_ret, rep['verdict_dist'])
                        changed = True
                        n_ann += 1
            if changed:
                json.dump(ad, open(afp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    out = {'date': '2026-11-17',
           'judgement': '体返回语义裁决: return未赋值/无return=void(出口eax伪影); '
                        '原源码override一致约束→全组统一',
           'groups': report, 'manual': manual,
           'stats': {'corpus_fixed': n_corpus, 'ann_fixed': n_ann}}
    json.dump(out, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    for k, rep in report.items():
        print('%-28s → %-6s (证据%s, 语料修%d)' % (k, rep['new_return'], rep['verdict_dist'], len(rep['fixes'])))
    for m in manual:
        print('人工队列: %s' % m)
    print('语料修%d 注解修%d → %s' % (n_corpus, n_ann, OUT))
    return 0


if __name__ == '__main__':
    sys.exit(main())
