#!/usr/bin/env python3
"""lvars 自动提案器(2026-11-11, IDB通路纯赢门放开后)。

census ⑦族错误 → 变量定位 → demanded-type 推断(三安全规则) → 提案表。
规则(窄门, 每条有编译器证据):
  R1 C2227/C2228 'left of ->M/.M' + 成员 M 在唯一类的 known_members 中
     → var: Cls *  (成员唯一归属反查)
  R2 C2109/C2100 下标/解引用 + 同函数内 var 有 (_DWORD *)var cast 形态
     → var: unsigned long *  (dword 槽, [i] 尺度=4B 与 dword 读一致)
  R3 其余一律跳过(歧义不提案——证据纪律)

输出: /tmp/lvars_auto_proposal.json {addr: {var: {"type": T, "rule": R, "evidence": [...]}}}
人工复核后由 --apply 落 structs/functions json(带 evidence_level=use_site_majority)。
"""
import json, os, re, sys, collections

CEN = 'data/status/probe_census.json'
SRC = 'pal3/src'

_cache = {}
def lines_of(p):
    if p not in _cache:
        try: _cache[p] = open(p, encoding='utf-8', errors='ignore').read().split('\n')
        except Exception: _cache[p] = []
    return _cache[p]

def enclosing_addr(lines, ln):
    for i in range(min(ln, len(lines)) - 1, -1, -1):
        m = re.match(r'^//\s*(0x[0-9A-Fa-f]{6,8})\s*$', lines[i].strip())
        if m: return m.group(1).upper().replace('0X', '0x')
    return None

def member_index():
    """成员名 → [(类, 型)] 唯一归属反查索引"""
    idx = collections.defaultdict(list)
    for f in os.listdir('data/annotations/structs'):
        if not f.endswith('.json'): continue
        try: d = json.load(open('data/annotations/structs/' + f, encoding='utf-8'))
        except Exception: continue
        cls = d.get('name') or f[:-5]
        for off, m in (d.get('known_members') or {}).items():
            if isinstance(m, dict) and m.get('name'):
                idx[m['name']].append((cls, off, m.get('type', '')))
    return idx

def main():
    apply = '--apply' in sys.argv
    d = json.load(open(CEN))
    s2 = d['s2']
    midx = member_index()
    proposal = collections.defaultdict(lambda: collections.defaultdict(dict))
    stats = collections.Counter()

    # R1 所需: 函数体内 var->M / var.M 用法收集
    for r in s2['results']:
        if r['status'] == 'ok': continue
        unit = r['unit']
        ls = lines_of(unit)
        if not ls: continue
        err_by_line = collections.defaultdict(list)
        for e in r['errors']:
            err_by_line[e['line']].append(e)
        for ln, errs in err_by_line.items():
            if ln > len(ls): continue
            line = ls[ln - 1]
            addr = enclosing_addr(ls, ln)
            if not addr: continue
            for e in errs:
                if e['code'] in ('C2227', 'C2228'):
                    m = re.search(r"left of '[-\>\.]*'?(\w+)'? must", e['msg'])
                    mem = m.group(1) if m else None
                    vm = re.search(r'\b([A-Za-z_]\w*)\s*[-\.\>]+%s\b' % re.escape(mem or '@'), line) \
                        if mem else re.search(r'\b([A-Za-z_]\w*)\s*->', line)
                    if mem and vm:
                        var = vm.group(1)
                        owners = midx.get(mem, [])
                        uniq_cls = {c for c, _, _ in owners}
                        if len(uniq_cls) == 1:
                            cls = uniq_cls.pop()
                            key = '%s|%s' % (addr, var)
                            cur = proposal[addr][var]
                            if 'type' not in cur:
                                cur['type'] = '%s *' % cls
                                cur['rule'] = 'R1'
                                cur['evidence'] = []
                            cur['evidence'].append('%s:%d 成员%s唯一归属%s' % (
                                unit.split('/')[-1], ln, mem, cls))
                            stats['R1提案'] += 1
                        else:
                            stats['R1跳过(成员归属%d类)' % len(uniq_cls)] += 1
                    continue
                if e['code'] in ('C2109', 'C2100'):
                    vm = re.search(r'\b(v\d+)\b', line)
                    if not vm: continue
                    var = vm.group(1)
                    # R2 证据: 同函数体内 (_DWORD *)var 形态
                    dword_cast = False
                    for i in range(max(0, ln - 40), min(len(ls), ln + 40)):
                        if re.search(r'\(_DWORD \*\)' + re.escape(var) + r'\b|\b' + re.escape(var) + r'\s*-\s*\d', ls[i]):
                            dword_cast = True; break
                    if dword_cast:
                        cur = proposal[addr][var]
                        if 'type' not in cur:
                            cur['type'] = 'unsigned long *'
                            cur['rule'] = 'R2'
                            cur['evidence'] = []
                        cur['evidence'].append('%s:%d 下标/解引用+同函数dword cast形态' % (
                            unit.split('/')[-1], ln))
                        stats['R2提案'] += 1
                    else:
                        stats['R2跳过(无dword形态证据)'] += 1

    out = {a: {v: ts for v, ts in vars_.items()} for a, vars_ in proposal.items()}
    json.dump(out, open('/tmp/lvars_auto_proposal.json', 'w', encoding='utf-8'),
              ensure_ascii=False, indent=1)
    print('统计:', dict(stats.most_common(8)))
    print('提案函数数: %d, /tmp/lvars_auto_proposal.json 已写' % len(out))
    n_show = 0
    for addr, vars_ in sorted(out.items()):
        for var, info in vars_.items():
            if n_show >= 14: break
            print('  %s %s -> %s [%s]' % (addr, var, info['type'], info['rule']))
            n_show += 1

if __name__ == '__main__':
    main()
