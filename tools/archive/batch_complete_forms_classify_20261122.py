#!/usr/bin/env python3
"""[未注解完全形批量预检 2026-11-22] ??1 收复空间分类器。

输入: data/status/dtor_pair_adjacency_20261122.json (target_ann_state=未注解)
分类:
  CLEAN      类注解无该址 claim/无既有 ~Cls 冲突/语料前缀=类名 → 可直注
  MULTI_CLAIM 该址被其他类/函数注解认领 → 需删认领或 ledger
  C8_RISK    类内已有 ~Cls 或 complete_dtor 条目(他址) → 需逐案裁决
  CORPUS_PREFIX_MISMATCH 语料前缀≠类名(如 gbChain1DNode 前缀的 PAL3VisNode 完全形)
             → 需 functions.json 改名链(apply→IDB→export) 或留待
  SKIP_CPK   CPK 回滚区休眠风险 → 单独定谳
输出: 分类清单 + 每类语料单元现名(改名涟漪预评估)
"""
import glob
import json
import os

REPO = '/home/peng/workspace/PAL3Decomp'
STRUCTS = REPO + '/data/annotations/structs'
CORPUS = REPO + '/asm/pal3/decomp'


def main():
    probe = json.load(open(REPO + '/data/status/dtor_pair_adjacency_20261122.json'))
    pairs = [p for p in probe['pairs'] if p['target_ann_state'] == '未注解' and p['complete_target']]
    # 全注解反查索引: addr → [(cls, name, flags)]
    ann_by_addr = {}
    cls_dtor_addrs = {}   # cls → {va: (name, flags)}
    for f in glob.glob(STRUCTS + '/*.json'):
        d = json.load(open(f, encoding='utf-8'))
        cls = d.get('name') or os.path.basename(f)[:-5]
        for a, m in (d.get('methods') or {}).items():
            try:
                va = int(a, 16)
            except (ValueError, TypeError):
                continue
            ann_by_addr.setdefault(va, []).append((cls, m.get('name'), m.get('flags')))
            if 'dtor' in (m.get('flags') or []) or str(m.get('name', '')).startswith('~'):
                cls_dtor_addrs.setdefault(cls, {})[va] = (m.get('name'), m.get('flags'))
    # functions.json 反查
    funcs = json.load(open(REPO + '/data/annotations/functions.json', encoding='utf-8'))
    fns = funcs.get('functions') or funcs
    # 语料名反查
    corpus = {}
    for f in glob.glob(CORPUS + '/*.json'):
        d = json.load(open(f, encoding='utf-8'))
        try:
            va = int(d.get('address'), 16)
        except (ValueError, TypeError):
            continue
        corpus[va] = (os.path.basename(f), d.get('name'))

    out = {'CLEAN': [], 'MULTI_CLAIM': [], 'C8_RISK': [], 'CORPUS_PREFIX_MISMATCH': [],
           'SKIP_CPK': []}
    for p in pairs:
        cls = p['cls']
        va = int(p['complete_target'], 16)
        if cls == 'CPK':
            out['SKIP_CPK'].append(p)
            continue
        claims = [c for c in ann_by_addr.get(va, []) if c[0] != cls]
        my_dtor = {v: nf for v, nf in (cls_dtor_addrs.get(cls) or {}).items()
                   if v != va}
        corpus_name = corpus.get(va, (None, None))[1] or ''
        prefix = corpus_name.split('::')[0] if corpus_name else ''
        if claims:
            out['MULTI_CLAIM'].append({'cls': cls, 'va': p['complete_target'],
                                       'claims': claims, 'corpus_name': corpus_name})
        elif my_dtor:
            out['C8_RISK'].append({'cls': cls, 'va': p['complete_target'],
                                   'other_dtor_entries': my_dtor,
                                   'corpus_name': corpus_name})
        elif prefix and prefix != cls:
            out['CORPUS_PREFIX_MISMATCH'].append({'cls': cls, 'va': p['complete_target'],
                                                  'corpus_name': corpus_name,
                                                  'fn_entry': fns.get(p['complete_target'])})
        else:
            out['CLEAN'].append({'cls': cls, 'va': p['complete_target'],
                                 'corpus_name': corpus_name})
    for k, v in out.items():
        print('== %s %d ==' % (k, len(v)))
        for e in v:
            if k == 'CLEAN':
                print('  %-16s %s 语料=%r' % (e['cls'], e['va'], e['corpus_name'][:44]))
            elif k == 'MULTI_CLAIM':
                print('  %-16s %s claims=%s 语料=%r' % (e['cls'], e['va'],
                      [(c[0], c[1]) for c in e['claims']], e['corpus_name'][:40]))
            elif k == 'C8_RISK':
                print('  %-16s %s 既有dtor=%s 语料=%r' % (e['cls'], e['va'],
                      e['other_dtor_entries'], e['corpus_name'][:40]))
            elif k == 'CORPUS_PREFIX_MISMATCH':
                print('  %-16s %s 语料=%r' % (e['cls'], e['va'], e['corpus_name'][:44]))
            else:
                print('  %-16s %s' % (e['cls'], e['complete_target']))
    outp = REPO + '/data/status/complete_forms_classification_20261122.json'
    json.dump(out, open(outp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1,
              default=str)
    print('分类 →', outp)


if __name__ == '__main__':
    main()
