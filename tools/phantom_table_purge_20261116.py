#!/usr/bin/env python3
"""[幻表 purge 2026-11-16] 16类普查伪影双表摘除(二进制实证批)。

判据(UITitle_YXXX先例推广):
1. 12字节对: 后址B[0:7]==前址A[3:10](移位视图) + ctor写后址(census实证) → A=幻表摘除
   (CEff族13类: A[1]=4c2850族共享槽1, B=A[3:]; UICaption: B=UIWnd七槽骨架445e70起)
2. TextureLib: 0x570A54=最全视图且slot1=55434f(purecall=抽象类标志) → 58/60=后缀视图摘除
3. CEffGroupNode: 0距离完全重复 → 去重
4. WeatherEffectNode: thunk区+浮点混杂非同款 → 跳过排队(需ctor证据)
"""
import json
import struct

data = open('original/PAL3.exe', 'rb').read()
e_lfanew = struct.unpack_from('<I', data, 0x3C)[0]
opt_off = e_lfanew + 24
image_base = struct.unpack_from('<I', data, opt_off + 28)[0]
n_sec = struct.unpack_from('<H', data, e_lfanew + 6)[0]
sec_off = opt_off + struct.unpack_from('<H', data, e_lfanew + 20)[0]
sections = []
for i in range(n_sec):
    o = sec_off + i * 40
    vsize, va, rsize, raw = struct.unpack_from('<IIII', data, o + 8)
    sections.append((va, vsize, raw, rsize))


def readt(va, n=10):
    rva = va - image_base
    for sva, vsize, raw, rsize in sections:
        if sva <= rva < sva + max(vsize, rsize):
            off = raw + (rva - sva)
            return ['%08x' % struct.unpack_from('<I', data, off + 4 * i)[0] for i in range(n)]
    return None


# (类, 摘除地址, 保留地址, 判据)
plan = []
ceff = ['CEffAction', 'CEffBink', 'CEffCallBack', 'CEffCylinder', 'CEffExplosive',
        'CEffGrid', 'CEffMeteor', 'CEffModel', 'CEffQuad', 'CEffQuake', 'CEffShock',
        'CEffgbParticle']
for cls in ceff:
    d = json.load(open('data/annotations/structs/%s.json' % cls, encoding='utf-8'))
    vts = d.get('vtables') or []
    if len(vts) != 2:
        continue
    a1 = int(vts[0].get('addr'), 16)
    a2 = int(vts[1].get('addr'), 16)
    lo, hi = min(a1, a2), max(a1, a2)
    # 移位视图验证: hi[0:7]==lo[3:10]
    if readt(hi, 7) == readt(lo, 10)[3:10]:
        plan.append((cls, '%s' % vts[[int(v.get('addr'), 16) for v in vts].index(lo)].get('addr'),
                     hi, '移位视图+ctor写后址(census)'))
    else:
        print('!! %s 移位验证失败, 跳过' % cls)
plan.append(('UICaption', '0x0056AFA4', 0x56AFB0, '后址=UIWnd七槽骨架(445e70/445b90/445d10)'))
plan.append(('TextureLib', '0x00570A58', 0x570A54, '最全视图+slot1=55434f(purecall抽象标志)'))
plan.append(('TextureLib', '0x00570A60', 0x570A54, '后缀视图'))
plan.append(('CEffGroupNode', '__DEDUP__', 0x56F3C0, '0距离完全重复'))

total = 0
for cls, drop_addr, keep, ev in plan:
    fp = 'data/annotations/structs/%s.json' % cls
    d = json.load(open(fp, encoding='utf-8'))
    vts = d.get('vtables') or []
    before = len(vts)
    if drop_addr == '__DEDUP__':
        seen = set()
        kept = []
        for v in vts:
            k = v.get('addr')
            if k in seen:
                continue
            seen.add(k)
            kept.append(v)
        d['vtables'] = kept
    else:
        d['vtables'] = [v for v in vts if str(v.get('addr')).upper() != drop_addr.upper()]
    if len(d['vtables']) == before:
        print('!! %s %s 无匹配(已摘?)' % (cls, drop_addr))
        continue
    d.setdefault('_phantom_tables_removed', []).append({
        'addr': drop_addr, 'keep': '%08x' % keep, 'date': '2026-11-16', 'evidence': ev})
    json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    total += 1
    print('摘除 %s %s (保留%08x)' % (cls, drop_addr, keep))
print('幻表摘除: %d 处' % total)
