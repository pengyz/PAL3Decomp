#!/usr/bin/env python3
"""globals.json 非语义名批量语义化（专项治理第②层，2026-11-09）。

数据直读取证（零猜测原则——内容读不出语义的符号一律不动，留待写点取证）：
  asc_<VA>   : .rdata/.data 字符串内容直读。可打印 ASCII → g_str_<CamelCase 内容>；
               GBK 中文/不可打印 → 保留原名，内容写 comment（可读性解决，诚实保留）。
  flt_<VA>   : float 初始值直读 → g_flt_<值表示>（0.5 → 0p5；有名常量 0.5/1.0/2.0 等不动名，
               comment 记值）。
  off_<VA>   : 读指向目标——指向字符串 → g_pStr_<目标内容>；指向 vtable/代码 → 记证据待人工。
  dword_/byte_/word_/unk_ : 不在本工具范围（BSS 运行时符号需写点取证，见专项方案 ②-b）。

用法:
  python3 tools/semantic_rename_batch.py            # dry-run 预览
  python3 tools/semantic_rename_batch.py --apply    # 写回 globals.json
"""
import json, os, re, struct, sys, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
ANN = os.path.join(ROOT, 'data', 'annotations', 'globals.json')

# PE 节映射（VA→file offset），ImageBase 0x400000——2026-11-09 复核修正版
SECTIONS = [
    ('.rdata', 0x56A000, 0x17F178, 0x16A000, 0x15178),
    ('.data',  0x580000, 0x1897000, 0x180000, 0x8C000),
]

def va2off(va):
    """VA→file offset；无 raw 背护（BSS）返回 None。"""
    for name, va_lo, va_hi, raw, rsz in SECTIONS:
        if va_lo <= va < va_lo + rsz:
            off = raw + (va - va_lo)
            if off + 1 <= len(data):
                return off
    return None

def read_cstr(va, maxlen=120):
    o = va2off(va)
    if o is None:
        return None
    end = data.find(b'\0', o, o + maxlen)
    if end < 0:
        end = o + maxlen
    raw = data[o:end]
    if not raw:
        return None
    try:
        s = raw.decode('ascii')
        kind = 'ascii'
    except UnicodeDecodeError:
        try:
            s = raw.decode('gbk')
            kind = 'gbk'
        except UnicodeDecodeError:
            return None
    # 可打印率守卫
    printable = sum(1 for c in s if c.isprintable())
    if printable < max(1, len(s) - 1):
        return None
    return s, kind

def to_ident(s, maxlen=24):
    """字符串→合法标识符尾巴（CamelCase，非字母数字丢弃）。"""
    parts = re.split(r'[^A-Za-z0-9]+', s)
    ident = ''.join(p[:1].upper() + p[1:] for p in parts if p)
    return ident[:maxlen]

def read_flt(va):
    o = va2off(va)
    if o is None:
        return None
    return struct.unpack('<f', data[o:o+4])[0]

def read_ptr_target_str(va):
    o = va2off(va)
    if o is None:
        return None
    tgt = struct.unpack('<I', data[o:o+4])[0]
    r = read_cstr(tgt, 60)
    return (tgt, r[0]) if r else None

def main():
    global data
    data = open(EXE, 'rb').read()
    apply = '--apply' in sys.argv
    g = json.load(open(ANN, encoding='utf-8'))
    stats = {'renamed': 0, 'commented': 0, 'skipped': 0}
    plan = []
    for addr_s, info in g.items():
        name = info.get('name', '')
        if not any(name.startswith(p) for p in ('asc_', 'flt_', 'off_')):
            continue
        try:
            va = int(addr_s, 16)
        except ValueError:
            continue
        if name.startswith('asc_'):
            r = read_cstr(va)
            if r is None:
                stats['skipped'] += 1
                continue
            s, kind = r
            if kind == 'ascii' and to_ident(s):
                new = 'g_str_' + to_ident(s)
                plan.append((addr_s, name, new, '字符串内容直读: %r' % s[:60], 'rename'))
                stats['renamed'] += 1
            else:
                plan.append((addr_s, name, None, 'GBK/中文串内容: %r' % s[:60], 'comment'))
                stats['commented'] += 1
        elif name.startswith('flt_'):
            v = read_flt(va)
            if v is None or v == 0:
                stats['skipped'] += 1
                continue
            plan.append((addr_s, name, None, 'float 值 = %r' % v, 'comment'))
            stats['commented'] += 1
        elif name.startswith('off_'):
            r = read_ptr_target_str(va)
            if r:
                tgt, s = r
                new = 'g_pStr_' + to_ident(s, 20)
                plan.append((addr_s, name, new, '指向字符串 0x%X: %r' % (tgt, s[:50]), 'rename'))
                stats['renamed'] += 1
            else:
                stats['skipped'] += 1
    # 重名唯一化: 同内容指针可有多个引用点(不同地址),extern 同名必撞——
    # 首个保留裸名,后续加地址后缀(诚实标记惯例)
    seen_new = collections.Counter()
    for i, (a, old, new, ev, act) in enumerate(plan):
        if act == 'rename' and new:
            seen_new[new] += 1
            if seen_new[new] > 1:
                plan[i] = (a, old, '%s_%s' % (new, a.replace('0x','')), ev, act)
    print('=== dry-run 统计:', stats)
    for a, old, new, ev, act in plan[:40]:
        print('  %s: %s -> %s | %s' % (a, old, new or '(comment)', ev[:60]))
    print('  ... 共 %d 项计划' % len(plan))
    if apply:
        for a, old, new, ev, act in plan:
            e = g[a]
            if act == 'rename' and new:
                e['name'] = new
                e['name_source'] = 'IDA语义分析 2026-11-09 数据直读批量治理'
                e['name_note'] = ev
            else:
                e.setdefault('comment', ev)
        json.dump(g, open(ANN, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('=== APPLIED to globals.json')

if __name__ == '__main__':
    main()
