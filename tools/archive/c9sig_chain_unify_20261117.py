#!/usr/bin/env python3
"""[C9 sig 链统一 2026-11-17] 家族投票裁决器落地到注解层——C9 sig 67清偿。

判据: 原源码override一致约束(编译事实) → 链内所有条目签名统一到家族投票获胜签名
(真体票=body证据加权; 桩位/回填条目禁票; 分歧=人工队列不猜)。
特殊族: 删除式dtor槽(MSVC标准形 void* __thiscall(int)) 全链规范形统一。
每条修正: sig_model=canonical解析 + signature=正名账渲染 + ev=chain_unified + name_note证据。
输出: data/status/c9sig_unify_20261117.json
"""
import json
import glob
import os
import re
import sys
import collections

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
OUT = os.path.join(ROOT, 'data', 'status', 'c9sig_unify_20261117.json')

sys.path.insert(0, ROOT)
sys.path.insert(0, os.path.join(ROOT, 'pipeline', 'gen', 'stages'))
sys.path.insert(0, os.path.join(ROOT, 'pipeline', 'gen'))
import importlib.util
_spec = importlib.util.spec_from_file_location('eh', os.path.join(ROOT, 'pipeline', 'gen', 'stages', 'emit_headers.py'))
_eh = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_eh)

try:
    from pipeline.sigmodel import parse_signature, render
except ImportError:
    from sigmodel import parse_signature, render

DTOR_RE = re.compile(r'^(~|_sdtor_|_scalar_dtor|.*scalar_deleting|`scalar deleting)')
DTOR_CANON = 'void * __thiscall(int)'


def load_ann():
    anns = {}
    for fp in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(fp)[:-5]
        anns[cls] = (fp, json.load(open(fp, encoding='utf-8')))
    return anns


def main():
    # C9 sig违规清单(check输出解析)
    pairs = []
    for ln in open('/tmp/chk_now.out', encoding='utf-8'):
        m = re.search(r'CANON:C9:(\S+):(\S+):sig (\S+) (\S+) 签名与基类不一致', ln)
        if m:
            pairs.append((m.group(1), m.group(2), m.group(4)))
    pairs = sorted(set(pairs))
    print('C9 sig违规: %d' % len(pairs))

    anns = load_ann()
    fixed, manual = [], []
    touched = set()
    for cls, addr, name in pairs:
        # dtor族: 全链规范形
        if DTOR_RE.search(name):
            canon_sig, canon_src = DTOR_CANON, 'MSVC删除式dtor标准形(ret 4=1参flags+返回this)'
            targets = [(cls, addr)]  # 派生条目; 基条目由同名搜索补
        else:
            canon_sig = _eh._family_slot_sig_full(cls, name, addr)
            canon_src = '家族投票获胜签名(真体票body证据加权)'
            targets = [(cls, addr)]
            if not canon_sig:
                # 派生侧无票→试基侧地址(基条目可能是正名账所在)
                manual.append('%s::%s@%s (投票分歧/无票)' % (cls, name, addr))
                continue
        # 解析canonical
        node = parse_signature(canon_sig)
        if node is None or node.get('pending'):
            manual.append('%s::%s@%s (canonical解析失败: %r)' % (cls, name, addr, canon_sig))
            continue
        # 目标条目集: 本地址条目 + 同链同名条目(家族内全部同名, 链一致约束)
        fam = _eh._family_graph().get(cls) or {cls}
        for c in sorted(fam):
            fp, d = anns[c]
            ms = d.get('methods') or {}
            for a, e in ms.items():
                nm = str(e.get('name') or '').split('::')[-1]
                if nm != name:
                    continue
                sm = e.get('sig_model') or {}
                if sm.get('pending'):
                    continue
                # 写canonical(保留参数名? — canonical渲染丢参数名, 用原params名+新类型:
                # render用sig_model, 参数类型来自canonical, 名字保留原条目)
                new_params = node.get('params') or []
                old_params = sm.get('params') or []
                if len(new_params) == len(old_params):
                    merged = []
                    for np_, op_ in zip(new_params, old_params):
                        merged.append({'type': np_.get('type'), 'name': op_.get('name')})
                    sm['params'] = merged
                else:
                    sm['params'] = new_params
                sm['return'] = node.get('return')
                sm['cc'] = node.get('cc') or sm.get('cc') or 'thiscall'
                sm['varargs'] = bool(node.get('varargs'))
                sm['pending'] = False
                e['sig_model'] = sm
                e['signature'] = render(sm)
                e['evidence_level'] = 'chain_unified'
                e['name_note'] = (e.get('name_note') or '') + (
                    ' | C9sig链统一20261117→%s: %s' % (render(sm), canon_src))
                touched.add((c, fp))
                fixed.append('%s::%s@%s' % (c, name, a))
    for c, fp in sorted(touched):
        json.dump(anns[c][1], open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    out = {'date': '2026-11-17', 'fixed': fixed, 'manual': manual,
           'stats': {'pairs': len(pairs), 'entries_fixed': len(fixed), 'manual': len(manual)}}
    json.dump(out, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('条目修正: %d | 人工队列: %d' % (len(fixed), len(manual)))
    for m in manual[:8]:
        print('  人工:', m)
    print('输出: %s' % OUT)
    return 0


if __name__ == '__main__':
    sys.exit(main())
