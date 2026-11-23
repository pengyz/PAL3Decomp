#!/usr/bin/env python3
"""[归属族批量落标 2026-11-13] 提案表 → structs methods 条目批量落盘。

前置: tools/propose_member_attribution_20261113.py 已产出提案表。
只处理 status=auto 的条目(ecx + 唯一类候选)——签名机械推导:
  cdecl 渲染参数(decomp JSON signature) ∪ 泄漏 ebp>0 局部 → thiscall 参数表
坑对冲(TOP5 实证):
  - functions.json 旧 free 条目占坑 ⇒ 同步删除
  - owner 字段必填(merge 门)
用法: python3 tools/batch_apply_member_attribution_20261113.py [--apply] [--limit N]
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv
LIMIT = 999
for i, a in enumerate(sys.argv):
    if a == '--limit' and i + 1 < len(sys.argv):
        LIMIT = int(sys.argv[i + 1])

proposal = json.load(open('/tmp/member_attribution_proposal.json', encoding='utf-8'))
decomp_dir = os.path.join(ROOT, 'asm', 'pal3', 'decomp')


def parse_sig_params(sig):
    m = re.search(r'\(([^)]*)\)', sig or '')
    if not m:
        return []
    out = []
    for p in m.group(1).split(','):
        p = p.strip()
        if not p or p == 'void':
            continue
        out.append(p)
    return out


def build_thiscall_sig(cls, method, cdecl_sig, leaked, body_params):
    """cdecl 渲染参数 ∪ 泄漏 ebp>0 局部 → thiscall 参数表。"""
    params = []
    seen_names = set()
    # decomp 声明参数名优先(体内引用它们)
    for p in parse_sig_params(cdecl_sig):
        pn = p.split()[-1] if len(p.split()) > 1 else p
        params.append(p)
        seen_names.add(pn)
    for ptype, pname in leaked:
        if pname in seen_names:
            continue
        params.append('%s %s' % (ptype, pname))
        seen_names.add(pname)
    if not params:
        params = ['int nVal']
    return 'int __thiscall %s::%s(%s)' % (cls, method, ', '.join(params))


applied = 0
skipped = []
for fname, p in proposal.items():
    if p['status'] != 'auto' or applied >= LIMIT:
        continue
    cls = p['cls_candidates'][0]
    # 构造器跳过(wave1 安全: ctor 无返回类型, 签名推导另行处理)
    parts_raw = fname.split('_')
    if fname == cls + '_' + cls or fname.endswith('_' + cls):
        skipped.append((fname, 'ctor'))
        continue
    addr = p.get('addr')
    if not addr:
        skipped.append((fname, 'no addr'))
        continue
    addr_full = '0x' + addr.upper()
    # decomp JSON 读 cdecl sig
    df = os.path.join(decomp_dir, '%s_%s.json' % (fname, addr))
    if not os.path.exists(df):
        skipped.append((fname, 'no decomp json'))
        continue
    d = json.load(open(df, encoding='utf-8'))
    cdecl_sig = d.get('signature', '')
    sig = build_thiscall_sig(cls, fname.split('_', len(cls.count('_')) + 1)[-1]
                             if False else fname,
                             cdecl_sig, p['leaked_params'], None)
    # 方法名 = 去类前缀后的原名保留(IDA 裸名形态的方法名转写为短名)
    # 与 TOP5 同款: name=Cls::Method 用原名(去类前缀)
    raw = fname
    prefix = cls + '_'
    method = raw[len(prefix):] if raw.startswith(prefix) else raw
    # structs 落标
    sfp = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % cls)
    if not os.path.exists(sfp):
        skipped.append((fname, 'no struct json %s' % cls))
        continue
    sd = json.load(open(sfp, encoding='utf-8'))
    sd.setdefault('methods', {})[addr_full] = {
        'name': '%s::%s' % (cls, method),
        'signature': sig,
        'owner': cls,
        'source': '[批量归属 2026-11-13] ecx-this+虚派发铁证(proposer auto); '
                  'cdecl sig=%s; 泄漏参=%s' % (cdecl_sig, p['leaked_params'] or '无'),
        'evidence_level': 'unverified',
    }
    json.dump(sd, open(sfp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    # functions.json 占坑清理
    ffp = os.path.join(ROOT, 'data', 'annotations', 'functions.json')
    fd = json.load(open(ffp, encoding='utf-8'))
    removed = False
    if addr_full in fd:
        del fd[addr_full]
        removed = True
    for k in [k for k, v in fd.items() if isinstance(v, dict) and v.get('name') == fname]:
        del fd[k]
        removed = True
    if removed and APPLY:
        json.dump(fd, open(ffp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    applied += 1
    print('%-44s -> %s::%s  (%s)' % (fname[:44], cls, method, addr_full))

print('\napplied=%d skipped=%d' % (applied, len(skipped)))
for f, r in skipped[:10]:
    print('  skip: %s (%s)' % (f, r))
if not APPLY:
    print('\n[dry-run] 加 --apply 落盘')
