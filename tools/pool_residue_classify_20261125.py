#!/usr/bin/env python3
"""pool_residue_classify_20261125.py — Wave0 数据卫生: 池余部 991 条字节取证分类入账。

方法论: Family B (93 条 gap 修正) + literal_pool 手工裁定的规模化形态。
判据:
  1. PE 节表映射: VA→文件背书(.data/.rdata) vs BSS(raw 尾之后, 零初始化)
  2. 文件背书区读真字节: ASCII 串(≥4 可打印+NUL)→literal_pool; off_→ptr_table;
     其余→const_data(带字节预览证据)
  3. BSS 区: 零初始化运行态→game_state; 类型按前缀(dword/word/byte/flt/unk)
  4. 名=decomp 引用原形(消 name_drift), 不发明语义名(N12)
"""
import re, glob, json, struct, collections

EXE = 'original/PAL3.exe'
data = open(EXE, 'rb').read()
pe = struct.unpack_from('<I', data, 0x3C)[0]
numsec = struct.unpack_from('<H', data, pe + 6)[0]
opt_size = struct.unpack_from('<H', data, pe + 20)[0]
base = struct.unpack_from('<I', data, pe + 24 + 28)[0]
sec0 = pe + 24 + opt_size
sections = []
for i in range(numsec):
    o = sec0 + i * 40
    name = data[o:o+8].rstrip(b'\0').decode('ascii', 'replace')
    vsz, va, rsz, praw = struct.unpack_from('<IIII', data, o + 8)
    sections.append((name, base + va, vsz, praw, rsz))
    print('节 %-8s VA=%08X VSZ=%08X RAW=%08X RSZ=%08X' % (name, base+va, vsz, praw, rsz))

def va_to_off(va):
    for name, sva, vsz, praw, rsz in sections:
        if sva <= va < sva + rsz and rsz > 0:
            return va - sva + praw, name
    return None, None

def is_string(b):
    if len(b) < 5: return False
    nul = b.find(b'\0')
    if nul < 4: return False
    s = b[:nul]
    return all(0x20 <= c < 0x7F or c in (0x0A, 0x0D, 0x09) or c >= 0x81 for c in s)

TYPE_BY_PREFIX = {'dword': 'unsigned int', 'word': 'unsigned short', 'byte': 'char',
                  'flt': 'float', 'unk': 'int', 'off': 'unsigned int', 'asc': None,
                  'dbl': 'double', 'stru': 'int', 'qword': 'unsigned __int64'}
CAT_BY_PREFIX = {'off': 'ptr_table'}

tok_re = re.compile(r'\b[a-zA-Z_]\w*\b')
addr_re = re.compile(r'^(?:byte|word|dword|qword|off|flt|dbl|stru|unk|asc)_([0-9A-Fa-f]{6,8})$')
toks = set()
for f in glob.glob('asm/pal3/decomp/*.json'):
    c = json.load(open(f, encoding='utf-8')).get('decompiled_c', '')
    toks.update(tok_re.findall(c))
isd = json.load(open('asm/pal3/ida_structs.json'))
ida_names = {str(v.get('name','')) for v in (isd.get('_globals') or {}).values()}
g = json.load(open('data/annotations/globals.json'))
ann_names = {str(v.get('name','')) for v in g.values() if isinstance(v, dict)}
ann_addrs = {('0x%08X' % int(k, 16)).lower() for k in g if isinstance(g[k], dict)}
lp = json.load(open('data/annotations/literal_pool.json'))
lp_entries = lp.setdefault('entries', {})
pool_addrs = {('0x%08X' % int(k, 16)).lower() for k in lp_entries}

lp = json.load(open('data/annotations/literal_pool.json'))
lp_entries = lp.setdefault('entries', {})

new_entries = []
new_strings = []
seen_addrs = set()  # 本轮已入账地址(pool 优先)
stats = collections.Counter()
for t in sorted(toks):
    m = addr_re.match(t)
    if not m or t in ida_names or t in ann_names:
        continue
    addr = int(m.group(1), 16)
    if ('0x%08X' % addr).lower() in ann_addrs or ('0x%08X' % addr).lower() in pool_addrs:
        stats['pool-owned-skip'] += 1
        continue
    prefix = t.split('_')[0]
    if addr in seen_addrs:
        stats['dup-in-run'] += 1
        continue
    off, sec = va_to_off(addr)
    ev = ''
    if off is not None:
        # 文件背书
        raw = data[off:off+32]
        if is_string(raw):
            nul = raw.find(b'\0')
            lp_entries['0x%08x' % addr] = {
                'ida_name': t, 'type': 'char[%d]' % nul,
                '_value_preview': raw[:nul].decode('gbk', 'replace')[:48]}
            new_strings.append(t)
            seen_addrs.add(addr)
            stats['string→literal_pool'] += 1
            continue
        if prefix == 'asc':
            typ = 'char'
        else:
            typ = TYPE_BY_PREFIX.get(prefix, 'int')
        cat = CAT_BY_PREFIX.get(prefix, 'const_data')
        ev = '文件背书[%s] 字节=%s' % (sec, raw[:8].hex())
    else:
        typ = TYPE_BY_PREFIX.get(prefix, 'int')
        cat = 'game_state'
        ev = 'BSS 零初始化域'
    seen_addrs.add(addr)
    new_entries.append((addr, {
        'name': t, 'type': typ, 'category': cat,
        'source': ' | [Wave0 池余部 2026-11-25] decomp 引用 %s; %s' % (t, ev)}))
    stats[cat if off is None else 'file:' + cat] += 1

print('分类: %s' % dict(stats))
print('新 globals 条目: %d, 新 literal_pool: %d' % (len(new_entries), len(new_strings)))
# 写入
for addr, e in new_entries:
    g['0x%08x' % addr] = e
json.dump(g, open('data/annotations/globals.json', 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
json.dump(lp, open('data/annotations/literal_pool.json', 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('已写入 globals.json +%d, literal_pool +%d' % (len(new_entries), len(new_strings)))
