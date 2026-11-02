"""case 注解 → types.h（丑C 编译用头）。用法: python3 gen_types.py <annotations_dir> <out.h>"""
import json, glob, re, sys
ann, outp = sys.argv[1], sys.argv[2]
lines = ['#ifndef T', '#define T', 'typedef unsigned char _BYTE;', 'typedef unsigned short _WORD;',
         'typedef unsigned int _DWORD;', 'typedef unsigned long long _QWORD;',
         'typedef unsigned char undefined1;', 'typedef unsigned short undefined2;',
         'typedef unsigned int undefined4;', 'typedef unsigned long long undefined8;', 'typedef void code;']
seen = {}
for f in glob.glob(ann + '/structs/*.json'):
    d = json.load(open(f))
    if d.get('name') and d['name'] not in seen: seen[d['name']] = d
san = lambda s: re.sub(r'[^0-9A-Za-z_]', '_', s or '')
for n, d in seen.items():
    size = d.get('size') or d.get('binary_size') or 4
    km = d.get('known_members') or {}
    ent = []
    for k, m in (km.items() if isinstance(km, dict) else [(m.get('offset'), m) for m in km]):
        try: ent.append((int(k), m))
        except Exception: pass
    ent.sort(key=lambda x: x[0])
    body = ['typedef struct %s {' % n]; pos = 0
    for i, (off, m) in enumerate(ent):
        nm = san(m.get('name') or 'f%d' % off)
        ty = m.get('type'); nxt = ent[i+1][0] if i+1 < len(ent) else size
        if off > pos: body.append('  _BYTE _pad%d[%d];' % (pos, off - pos)); pos = off
        if isinstance(ty, (dict, list)):
            w = max(nxt - off, 4); body.append('  _BYTE %s[%d];' % (nm, w)); pos += w; continue
        ts = (ty if isinstance(ty, str) else 'int').strip(); isptr = '*' in ts
        base = san(ts.rstrip(' *').strip())
        if isptr: body.append('  void *%s;' % nm); pos += 8
        elif base in ('float',): body.append('  float %s;' % nm); pos += 4
        elif base in ('double',): body.append('  double %s;' % nm); pos += 8
        elif base in ('char','byte','BYTE','unsigned char','bool','BOOL','_BYTE'): body.append('  _BYTE %s;' % nm); pos += 1
        elif base in ('short','WORD','unsigned short','_WORD'): body.append('  _WORD %s;' % nm); pos += 2
        else: body.append('  _DWORD %s;' % nm); pos += 4
    if size and pos < size: body.append('  _BYTE _tail[%d];' % (size - pos))
    body.append('} %s;' % n); lines.append('\n'.join(body))
lines.append('#endif')
open(outp, 'w').write('\n'.join(lines))
print('types.h:', len(seen), 'structs')
