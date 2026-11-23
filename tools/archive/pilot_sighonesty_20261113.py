#!/usr/bin/env python3
"""[签名诚实化 pilot 2026-11-13] SUSPECT-type 无虚派发子集批量落标。

范围(用户指令: 先做一批看效果):
  census SUSPECT-type ∧ vt_dispatch==0 ∧ ecx_leak=True ∧ 类单元内(定义带::)
  ⇒ 无搬移风险(已在类文件), 纯 sig 诚实化。
配方(TOP5 实证): decomp cdecl 渲染 sig → __thiscall Cls::M(参数原样)。
  decomp 渲染参数 = Hex-Rays 活体栈参分析(含泄漏参), 是最诚实的参数证据。
对冲: pilot manifest 落盘(addr清单)供衰退定位; structs/functions 双清。

用法: python3 tools/pilot_sighonesty_20261113.py [--apply] [--limit 24]
"""
import json
import os
import re
import glob
import sys
import collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
APPLY = '--apply' in sys.argv
LIMIT = 24
for i, a in enumerate(sys.argv):
    if a == '--limit' and i + 1 < len(sys.argv):
        LIMIT = int(sys.argv[i + 1])

census = json.load(open(os.path.join(ROOT, 'data', 'status',
                                     'attribution_census_20261113.json'),
                        encoding='utf-8'))
structs_dir = os.path.join(ROOT, 'data', 'annotations', 'structs')

_CTRL = ('if', 'for', 'while', 'switch', 'return', 'else', 'do')

def decomp_sig_fix(cdecl, cls, method):
    """int __cdecl X(int a) / int __cdecl X(int a) → int __thiscall Cls::M(int a)"""
    sig = cdecl
    sig = re.sub(r'__cdecl\s+\w+\s*\(', '__thiscall %s::%s(' % (cls, method), sig)
    sig = re.sub(r'__cdecl\s*\(', '__thiscall %s::%s(' % (cls, method), sig)
    return sig

picked = []
for f in census['functions']:
    if f['verdict'] != 'SUSPECT-type':
        continue
    if f['vt_dispatch'] != 0 or not f['ecx_leak']:
        continue
    nm = f['name'].split('::')[-1].split('(')[0]
    method_short = nm
    # 类名 = 类单元文件名(SUSPECT-type 均在类单元内)
    cls = os.path.basename(f['file'])[:-4]
    if method_short in _CTRL or method_short.startswith('_') or method_short.startswith('sub_'):
        continue
    picked.append((f, cls, method_short))

# 去重(同名多定义取一)
seen = set()
pilot = []
for f, cls, method in picked:
    key = (cls, method)
    if key in seen:
        continue
    seen.add(key)
    pilot.append((f, cls, method))
print('候选(%d) → pilot 取前 %d' % (len(pilot), min(LIMIT, len(pilot))))

manifest = []
patched = 0
fails = collections.Counter()
for f, cls, method in pilot:
    if patched >= LIMIT:
        break
    sfp = os.path.join(structs_dir, '%s.json' % cls)
    if not os.path.exists(sfp):
        fails['no_struct'] += 1
        continue
    sd = json.load(open(sfp, encoding='utf-8'))
    # 找 methods 条目(短名匹配)
    hit = None
    for a, m in (sd.get('methods') or {}).items():
        mn = str(m.get('name', ''))
        if mn.split('::')[-1].split('(')[0] == method:
            hit = (a, m)
            break
    if hit is None:
        fails['no_methods_entry'] += 1
        continue
    a, m = hit
    old_sig = m.get('signature', '')
    # decomp JSON 找 cdecl 渲染
    df = None
    au = '0x%X' % int(a, 16)
    _a8 = au[2:].lower().zfill(8)
    for cand in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp',
                                       '*_%s.json' % _a8)):
        df = cand
        break
    if not df:
        fails['no_decomp'] += 1
        continue
    dd = json.load(open(df, encoding='utf-8'))
    cdecl = dd.get('signature', '')
    if '__cdecl' not in cdecl:
        fails['sig_not_cdecl'] += 1
        continue  # 非 cdecl 渲染(已是 thiscall 形)——跳过避免双改
    new_sig = decomp_sig_fix(cdecl, cls, method)
    m['signature'] = new_sig
    m['owner'] = cls
    if 'this' in old_sig and 'this' not in new_sig:
        pass  # 旧 this 形参数混乱, 以 decomp 活体为准
    m['source'] = (m.get('source', '') +
                   ' | [签名诚实化pilot 2026-11-13] cdecl渲染→thiscall类限定 '
                   '(旧sig=%s; 泄漏参证据=census)' % old_sig[:40]).strip(' |')
    manifest.append({'cls': cls, 'method': method, 'addr': a,
                     'old_sig': old_sig, 'new_sig': new_sig,
                     'file': f['file'], 'line': f['line']})
    if APPLY:
        json.dump(sd, open(sfp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    patched += 1
    print('%-22s %-28s %r -> %r' % (cls, method[:28], old_sig[:36], new_sig[:44]))
    # functions.json 占坑清理
    ffp = os.path.join(ROOT, 'data', 'annotations', 'functions.json')
    fd = json.load(open(ffp, encoding='utf-8'))
    removed = False
    if a in fd:
        del fd[a]
        removed = True
    for k in [k for k, v in fd.items()
              if isinstance(v, dict) and v.get('name', '').split('::')[-1].split('(')[0] == method]:
        del fd[k]
        removed = True
    if removed and APPLY:
        json.dump(fd, open(ffp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

json.dump(manifest, open('/tmp/pilot_sighonesty_manifest.json', 'w',
                         encoding='utf-8'), ensure_ascii=False, indent=1)
print('\npatched=%d manifest=/tmp/pilot_sighonesty_manifest.json' % patched)
if not APPLY:
    print('[dry-run] 加 --apply 落盘')
