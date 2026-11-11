#!/usr/bin/env python3
"""lvars 覆盖候选取证提取器（2026-11-11，L-VAR annotation 层填充的取证面）。

从 probe census 提取"槽位类型家族"错误的候选 lvar 覆盖：
  1. 定位错误站点 → 在生成 cpp 中回溯宿主函数（`// 0x...` 头注释）
  2. 提取候选变量 + 编译器要求的类型（demanded-type，编译器即神谕）
  3. 拉出该变量在宿主函数内的**全部使用行**（纯赢/双生命期人工裁决依据）

错误类 → 候选规则（窄门，逐类有编译器证据）：
  C2440 "from 'float' to 'Cls *'" + 行内 `(Cls *)vN`   → vN: Cls *（cast 目标即需求类型）
  C2440 "from 'float' to 'unsigned long *'" + 行内 cast → 同上（unsigned long *）
  C2440 "from 'void *'" 且行内 `vN = <GetAt/setAt 等>`  → vN: <cast 目标或左值旧类型>
  C2440 "from 'char *'" (L-TAILADDR 残差)               → 赋值左值 var: char *
  C2446/'==' "from 'char *' to 'Cls *'"                 → 比较双方 var: Cls *

输出: /tmp/lvar_draft.json  {addr: {var: {"type": T, "evidence": [...], "uses": [...]}}}
用法: python3 tools/extract_lvar_candidates.py [--filter UNITNAME]
"""
import json, os, re, sys, collections

CEN = 'data/status/probe_census.json'
SRC = 'pal3/src'

_lines_cache = {}
def unit_lines(unit):
    if unit not in _lines_cache:
        try:
            _lines_cache[unit] = open(os.path.join(SRC, unit.replace('pal3/src/', '')),
                                      encoding='utf-8', errors='ignore').read().split('\n')
        except Exception:
            _lines_cache[unit] = []
    return _lines_cache[unit]

def enclosing_addr(lines, ln):
    """回溯宿主函数地址（最近的 `// 0x...` 行注释）。"""
    for i in range(min(ln, len(lines)) - 1, -1, -1):
        m = re.match(r'^//\s*(0x[0-9A-Fa-f]{6,8})\s*$', lines[i].strip())
        if m:
            return m.group(1)
    return None

def candidate_var_uses(lines, addr, var):
    """宿主函数体内 var 的全部使用行（地址段截取）。"""
    # 定位函数体边界（下一个 // 0x 头）
    start = None
    for i, l in enumerate(lines):
        if l.strip() == '// %s' % addr:
            start = i + 1
            break
    if start is None:
        return []
    end = len(lines)
    for i in range(start, len(lines)):
        if re.match(r'^//\s*0x[0-9A-Fa-f]{6,8}\s*$', lines[i].strip()):
            end = i
            break
    return ['%d: %s' % (i + 1, lines[i].strip()[:100])
            for i in range(start, end) if re.search(r'\b%s\b' % re.escape(var), lines[i])]

def main():
    flt = None
    for a in sys.argv[1:]:
        if a.startswith('--filter='):
            flt = a.split('=', 1)[1]
    d = json.load(open(CEN))
    s2 = d['s2']
    draft = collections.defaultdict(lambda: collections.defaultdict(dict))
    n_sites = 0
    for r in s2['results']:
        if r['status'] == 'ok':
            continue
        unit = r['unit']
        if flt and flt not in unit:
            continue
        lines = unit_lines(unit)
        if not lines:
            continue
        for e in (r.get('errors') or []):
            msg = e['msg']
            ln = e['line']
            if ln > len(lines):
                continue
            srcline = lines[ln - 1]
            var = None; typ = None; ev = None
            # 规则1: float→Cls* cast（S1）
            m = re.search(r"from 'float' to '([\w ]+?)\s*\*'", msg)
            cm = re.search(r'\(([\w ]+?)\s*\*\)\s*([A-Za-z_]\w*)', srcline)
            if m and cm and re.match(r'\s*v\d+$', cm.group(2)):
                var = cm.group(2); typ = cm.group(1).strip() + ' *'
                ev = 'S1: C2440 float→%s, 行内 (%s *)%s' % (typ, cm.group(1).strip(), var)
            # 规则2: void*→int 比较族（nIndex 槽）
            elif "from 'void *'" in msg and ("'<' " in msg[:12] or "'!=' " in msg[:12] or "'==' " in msg[:12]):
                for mm in re.finditer(r'\b([A-Za-z_]\w*)\b', srcline):
                    w = mm.group(1)
                    if w in ('if', 'while', 'for', 'int', 'return', 'sizeof', 'const'):
                        continue
                    var = w; typ = 'int'
                    ev = 'V: %s 与 int 比较失败（void*槽）' % var
                    break
            # 规则3: void*→标量 赋值族 `vN = nIndex` (V '=' void*→int/long)
            elif "from 'void *'" in msg and "'=' " in msg[:12]:
                m2 = re.match(r"[\w ]*:\s*cannot convert from 'void \*' to '(\w+ ?\*?)'", msg)
                m3 = re.search(r'\b([A-Za-z_]\w*)\s*;\s*$', srcline)
                # 赋值右值 var（如 v8 = nIndex）——取行内末尾标识符
                m4 = re.search(r'=\s*([A-Za-z_]\w*)\s*;', srcline)
                if m4 and m2:
                    var = m4.group(1); typ = m2.group(1)
                    ev = 'V: %s(右值void*槽) 赋给 %s 类型' % (var, typ)
            # 规则4: char*→Cls* 比较（L-TAILADDR 残差 K 族）
            elif re.search(r"from 'char \*' to 'class ([\w]+) \*'", msg) and ('!=' in msg[:12] or '==' in msg[:12]):
                cls = re.search(r"to 'class ([\w]+) \*'", msg).group(1)
                # 比较双方里找非成员访问侧的裸标识符
                m5 = re.search(r'([A-Za-z_]\w*)\s*(!=|==)', srcline)
                if m5:
                    var = m5.group(1); typ = '%s *' % cls
                    ev = 'K: char*(L-TAILADDR残差)与 %s* 比较' % cls
            if not var:
                continue
            addr = enclosing_addr(lines, ln)
            if not addr:
                continue
            slot = draft[addr][var]
            if typ not in slot:
                slot[typ] = {'unit': unit, 'evidence': [], 'uses': []}
            if len(slot[typ]['evidence']) < 3:
                slot[typ]['evidence'].append('%s:%d %s' % (unit.split('/')[-1], ln, ev))
            if not slot[typ]['uses']:
                slot[typ]['uses'] = candidate_var_uses(lines, addr, var)[:14]
            n_sites += 1
    out = {}
    for addr, vars_ in draft.items():
        out[addr] = {v: ts for v, ts in vars_.items()}
    json.dump(out, open('/tmp/lvar_draft.json', 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('站点=%d, 候选函数=%d, /tmp/lvar_draft.json 已写' % (n_sites, len(out)))
    for addr, vars_ in list(out.items())[:12]:
        for var, ts in vars_.items():
            for typ, info in ts.items():
                print('\n%s  %s -> %s  [%s]' % (addr, var, typ, info['unit'].split('/')[-1]))
                for evd in info['evidence'][:2]:
                    print('   证: %s' % evd)
                for u in info['uses'][:6]:
                    print('   用: %s' % u)

if __name__ == '__main__':
    main()
