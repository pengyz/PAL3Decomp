"""diff 字节形聚类原型（方案：拓扑 x 字节形联合聚类）——先打 len-delta 246 桶。
复现编译用 s4 同 flag；双侧字节：PAL3.exe（VA）vs 现编 obj（符号字节）。
输出：首差点位 opcode 对签名分布 + 形态桶分布（聚类，不判因）。"""
import json
import struct
import sys
from collections import Counter

sys.path.insert(0, 'tools')
sys.path.insert(0, 'pipeline')
from gbengine_compare import parse_coff_obj
import probe_compile as pc

FLAGS = ['/nologo', '/TP', '/c', '/W3', '/O2', '/Ob2', '/Oi', '/Ot', '/Oy',
         '/GF', '/Gy', '/GX', '/GR', '/MT', '/Gd']


class Exe:
    def __init__(self, path):
        self.data = open(path, 'rb').read()
        pe = struct.unpack_from('<I', self.data, 0x3C)[0]
        nsec = struct.unpack_from('<H', self.data, pe + 6)[0]
        optsz = struct.unpack_from('<H', self.data, pe + 20)[0]
        self.base = struct.unpack_from('<I', self.data, pe + 24 + 28)[0]
        self.secs = []
        for i in range(nsec):
            off = pe + 24 + optsz + i * 40
            vsz, va, rsz, ptr = struct.unpack_from('<IIII', self.data, off + 8)
            self.secs.append((va, vsz, ptr, rsz))

    def head(self, va, n):
        rva = va - self.base
        for v, vsz, ptr, rsz in self.secs:
            if v <= rva < v + max(vsz, rsz):
                return self.data[ptr + (rva - v):ptr + (rva - v) + n]
        return b''


def classify_form(o, u):
    """首差点位形态（两侧各取 8B 窗口）——纯形签名，不判因。"""
    if not u or u[0] in (0xC3, 0xC2):
        return 'ours-early-ret'
    if not o:
        return 'orig-missing'
    if o[0] == 0xE8 or (o[0] == 0xFF and len(o) > 1 and o[1] in (0x15, 0x25, 0xD0, 0xD1, 0xD2, 0xD3)):
        return 'orig-call-site'
    if o[:2] == b'\x6a\xff' or o[:2] == b'\x68\xff':
        return 'orig-seh-form'
    if o[0] == 0xE9 or (o[0] == 0x0F and len(o) > 1 and 0x80 <= o[1] <= 0x8F):
        return 'orig-branch'
    return 'generic'


def main():
    d = json.load(open('data/status/s4_diff_detail.json', encoding='utf-8'))
    ents = []
    for unit, us in d['units'].items():
        for e in us:
            if e['compiled_len'] < e['size']:
                ents.append((unit, e))
    print('len-delta(shorter) 函数:', len(ents))

    exe = Exe('original/PAL3.exe')
    by_unit = {}
    for unit, e in ents:
        by_unit.setdefault(unit, []).append(e)

    incs = ['/I' + pc.wpath(x) for x in pc.INCLUDE_DIRS]
    op_pair = Counter()
    form_c = Counter()
    form_zone = Counter()
    miss_bytes = Counter()
    done = fail = 0
    samples = {}
    for unit, es in by_unit.items():
        obj = 'build/obj/%s.obj' % unit.replace('/', '_')
        out, err = pc.run_cl(incs + ['/Fo' + pc.wpath(obj), '/c', pc.wpath(unit)],
                             timeout=120, flags=FLAGS)
        if err or ' error ' in out:
            fail += 1
            continue
        try:
            funcs = parse_coff_obj(obj)
        except Exception:
            fail += 1
            continue
        for e in es:
            fi = funcs.get(e['symbol'])
            if not fi:
                continue
            ob = bytearray(exe.head(int(e['va'], 16), e['size']))
            ub = bytearray(fi['bytes'])
            # [原型修] reloc 站点掩码——obj 占位值 vs exe 实值必然不同（假差之源）；
            # reloc 位置双侧同 offset，掩 4B 窗口即同值。
            for roff in fi.get('relocs', ()):
                for b in range(4):
                    if roff + b < len(ob):
                        ob[roff + b] = 0
                    if roff + b < len(ub):
                        ub[roff + b] = 0
            n = min(len(ob), len(ub))
            i = 0
            while i < n and ob[i] == ub[i]:
                i += 1
            if i >= n and len(ob) == len(ub):
                continue
            form_c[classify_form(ob[i:i + 8], ub[i:i + 8])] += 1
            zone = 'prologue' if i < 16 else ('tail' if i >= n - 8 else 'body')
            form_zone[(classify_form(ob[i:i + 8], ub[i:i + 8]), zone)] += 1
            miss_bytes[e['size'] - e['compiled_len']] += 1
            op_pair[(ob[i] if i < len(ob) else -1, ub[i] if i < len(ub) else -1)] += 1
            done += 1
            if form_c.total() <= 12:
                samples.setdefault(classify_form(ob[i:i + 8], ub[i:i + 8]),
                                   (e['name'][:40], e['va'], ob[i:i + 8].hex(), ub[i:i + 8].hex()))

    print('已聚类 %d | 编译失败单元 %d' % (done, fail))
    print('--- 首差点位形态分布 ---')
    for k, v in form_c.most_common():
        print('  %-20s %4d  %5.1f%%' % (k, v, 100.0 * v / max(done, 1)))
    print('--- opcode 对 top12（orig,ours）---')
    for (a, b), v in op_pair.most_common(12):
        print('  %02x -> %02x  %4d' % (a, b, v))
    print('--- 首差点位形态 x 分区 ---')
    for (f, z), v in form_zone.most_common(12):
        print('  %-18s %-9s %4d' % (f, z, v))
    print('--- 缺质量直方图（size-compiled_len，非零 top8）---')
    for k, v in sorted(miss_bytes.items(), key=lambda kv: -kv[1])[:8]:
        print('  缺 %3dB  %4d' % (k, v))
    print('--- 样本 ---')
    for k, s in samples.items():
        print('  %-20s %s %s | orig %s | ours %s' % (k, s[0], s[1], s[2], s[3]))


if __name__ == '__main__':
    main()
