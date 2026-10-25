#!/usr/bin/env python3
"""寄存器差异数量分析（一次性诊断）。"""
import json, subprocess, os, sys
sys.path.insert(0, 'tools'); sys.path.insert(0, 'pipeline')
import gbengine_compare as gc

ROOT = r'D:\workspace\PAL3Decomp'
d = json.load(open(os.path.join(ROOT, 'data', 'status', 's4_diff_detail.json'), encoding='utf-8'))
samples = []
for unit, fns in d['units'].items():
    for f in fns:
        if f.get('n_diff') in (2, 3, 4, 5) and f.get('size', 0) > 20:
            samples.append((unit, f))
        if len(samples) >= 6:
            break
    if len(samples) >= 6:
        break

data = open(os.path.join(ROOT, 'original', 'PAL3.exe'), 'rb').read()
pe = int.from_bytes(data[0x3C:0x40], 'little')
opt_size = int.from_bytes(data[pe+20:pe+22], 'little')
image_base = int.from_bytes(data[pe+24+28:pe+24+32], 'little')
sec0 = pe + 24 + opt_size
for i in range(int.from_bytes(data[pe+6:pe+8], 'little')):
    off = sec0 + i*40
    if data[off:off+8].rstrip(b'\x00') == b'.text':
        vaddr = int.from_bytes(data[off+12:off+16], 'little')
        rptr = int.from_bytes(data[off+20:off+24], 'little')
        text = data[rptr:rptr+int.from_bytes(data[off+16:off+20], 'little')]
        break

CL = ROOT + r'\tools\compilers\msvc6.0\Bin\CL.EXE'
incs = [r'/ID:\workspace\PAL3Decomp\include', r'/ID:\workspace\PAL3Decomp\pal3\src',
        r'/ID:\workspace\PAL3Decomp\tools\compilers\msvc6.0\Include', r'/ID:\workspace\PAL3Decomp\tools\vc6\Include']
flags = ['/nologo','/TP','/c','/O2','/Ob2','/Oi','/Ot','/Oy','/GF','/Gy','/GX','/GR','/MT','/Gd']
obj = ROOT + r'\data\status\_reg_test.obj'

results = []
for unit, f in samples:
    src = os.path.join(ROOT, unit)
    if os.path.exists(obj): os.remove(obj)
    r = subprocess.run([CL] + flags + incs + ['/Fo' + obj, src],
                       capture_output=True, text=True, errors='replace')
    if not os.path.exists(obj): continue
    funcs = gc.parse_coff_obj(obj)
    sym = funcs.get(f.get('symbol', ''))
    if not sym: continue

    va = int(f['va'], 16)
    o = va - image_base - vaddr
    ob = text[o:o+f['size']]
    cb = sym['bytes']

    reg_diffs = 0; other_diffs = 0
    for do in f.get('diffs', []):
        do = int(do)
        if do >= min(len(ob), len(cb)): continue
        xor_val = ob[do] ^ cb[do]
        if xor_val < 0x3F:
            reg_diffs += 1
        else:
            other_diffs += 1

    name = f['name'][:38]
    pct = round(100.0*reg_diffs/max(f['n_diff'],1), 0)
    results.append((name, f['n_diff'], reg_diffs, other_diffs, pct))
    print('%-38s nd=%-3d reg=%d other=%d (%d%% reg)' % (name, f['n_diff'], reg_diffs, other_diffs, pct))

total_reg = sum(r[2] for r in results)
total_other = sum(r[3] for r in results)
total = total_reg + total_other
print('\nTotal: reg=%d (%.0f%%) other=%d (%.0f%%)' % (
    total_reg, 100.0*total_reg/max(total,1), total_other, 100.0*total_other/max(total,1)))
