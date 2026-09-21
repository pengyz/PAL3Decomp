#!/usr/bin/env python3
"""审核：**自由函数里的 `this`**（只读）。

## 规则（使用者 2026-09-21 明确）

**自由函数的形参名不允许是 `this`** —— C++ 里 `this` 是关键字，写了就是**语法错误**
（实证：`pal3/src/free_functions.cpp:1702/1751/1897` 报 `C2143 missing ')' before 'this'` 共 9 条）。
`_this` 是合法名字，但**语义上仍是"显式 this"** —— 它对自由函数而言是**模型错误**：
被调函数在 IDB 里是 `__thiscall`（`this` 走 ECX），发射成 `__cdecl` 自由函数 ⇒ **ABI 不同 ⇒ 字节永不匹配**
（见 `docs/knowledge/gotcha_thiscall_free_function_is_model_error.md`）。

## 两段输出

* **[A] 非法**（硬失败）：文件作用域函数，形参名叫 `this` ⇒ 当前就报语法错。
* **[B] 可疑**（advisory）：文件作用域函数，形参含 `_this`/`*this` ⇒ ABI/归属待裁；
  按"是否已被归属"（同一地址已在 `structs/*.json` 的 `methods` 里）与"this 类型是否为已知类"再分三类。

用法::

    python3 tools/audit_this_in_free_functions.py            # 报告
    python3 tools/audit_this_in_free_functions.py --json     # 机器可读
退出码: [A] 非空 ⇒ 1；否则 0（[B] 不阻断）。
"""
import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, 'pal3', 'src')
DECOMP = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
CENSUS = os.path.join(ROOT, 'data', 'status', 'probe_census.json')

# 文件作用域函数头：列 0 起、首个 '(' 之前没有 '::'、且不是语句/注释
HEAD = re.compile(r'^(?P<pre>[A-Za-z_][\w \t\*&]*?)\b(?P<name>[A-Za-z_]\w*)\s*\((?P<params>[^;{}]*)\)\s*(?P<tail>[;{]|$)')


def split_params(s):
    out, d, cur = [], 0, ''
    for ch in s:
        if ch in '(<[':
            d += 1
        elif ch in ')>]':
            d -= 1
        if ch == ',' and d == 0:
            out.append(cur.strip()); cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def param_name(p):
    """取形参名（最后一个标识符，去掉数组/指针/默认值噪声）。"""
    p = p.split('=')[0].strip()
    m = re.findall(r'[A-Za-z_]\w*', p)
    return m[-1] if m else ''


def scan_source():
    """→ ([A] 列表, [B] 列表)（文件作用域、非成员、非注释）"""
    illegal, suspect = [], []
    for p in sorted(glob.glob(os.path.join(SRC, '**', '*.[ch]pp'), recursive=True)
                    + glob.glob(os.path.join(SRC, '**', '*.h'), recursive=True)):
        rel = os.path.relpath(p, ROOT)
        try:
            lines = open(p, encoding='utf-8', errors='replace').read().split('\n')
        except OSError:
            continue
        for i, line in enumerate(lines, 1):
            if not line or line[0] in ' \t/*#':            # 仅列 0 起（文件作用域）
                continue
            m = HEAD.match(line)
            if not m or '::' in m.group('pre'):
                continue
            params = m.group('params')
            if not params.strip() or params.strip() == 'void':
                continue
            names = [param_name(x) for x in split_params(params)]
            rec = {'file': rel, 'line': i, 'name': m.group('name'),
                   'params': params.strip()[:110], 'tail': m.group('tail')}
            if 'this' in names:
                illegal.append(rec)
            elif '_this' in names or 'this' in params:
                suspect.append(rec)
    return illegal, suspect


def decomp_free_this():
    """decomp 语料：名字无 '::' 却带 this 槽的条目 → 分类。"""
    attributed = {}
    for p in glob.glob(os.path.join(STRUCTS, '*.json')):
        cls = os.path.basename(p)[:-5]
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        for addr, info in (d.get('methods') or {}).items():
            if isinstance(info, dict):
                attributed.setdefault(addr.upper(), (cls, info.get('name')))
    out = []
    for p in glob.glob(os.path.join(DECOMP, '*.json')):
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        sig = d.get('signature') or ''
        name = (d.get('name') or '').split('(')[0]
        if 'this' not in sig or '::' in name:
            continue
        m = re.match(r'^.*?\b(__thiscall|__cdecl|__stdcall|__fastcall)\b\s*\(\s*([^,)]*)', sig)
        cc = m.group(1) if m else '?'
        first = (m.group(2).strip() if m else '')
        cls = None
        mm = re.match(r'^([A-Za-z_]\w*)\s*\*+', first)
        if mm:
            cls = mm.group(1)
        addr = (d.get('address') or '').upper()
        known = [os.path.basename(x)[:-5] for x in glob.glob(os.path.join(STRUCTS, '*.json'))]
        kind = ('①地址已归属(纯重复发射)' if addr in attributed else
                ('②this类型=已知类(归属可恢复)' if cls in known else
                 '③类型丢失(需 IDA 取证)'))
        out.append({'name': name, 'addr': addr, 'cc': cc, 'first': first[:34],
                    'kind': kind, 'attributed_to': attributed.get(addr, (None, None))[0]})
    return out


def census_hits():
    try:
        d = json.load(open(CENSUS, encoding='utf-8'))
    except Exception:
        return []
    hits = []
    for u in (d.get('s2') or {}).get('results') or []:
        for e in u.get('errors') or []:
            if 'this' in (e.get('msg') or '') and e.get('code') in ('C2143', 'C2059', 'C2062', 'C2146'):
                hits.append({'unit': u.get('unit'), 'line': e.get('line'),
                             'code': e.get('code'), 'msg': e.get('msg')})
    return hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args()
    illegal, suspect = scan_source()
    dec = decomp_free_this()
    cen = census_hits()
    kinds = {}
    for r in dec:
        kinds[r['kind']] = kinds.get(r['kind'], 0) + 1
    rep = {'illegal_param_named_this': illegal, 'suspect_explicit_this': suspect,
           'decomp_free_this': dec, 'decomp_kinds': kinds, 'census_syntax_hits': cen}
    if a.json:
        print(json.dumps(rep, ensure_ascii=False, indent=1))
    else:
        print('=' * 78)
        print('[A] **非法**：自由函数形参名叫 `this`（C++ 关键字）—— %d 处' % len(illegal))
        print('    （当前普查里对应 %d 条语法错，见末尾）' % len(cen))
        for r in illegal[:20]:
            print('    %-44s:%-6d %s(%s)' % (r['file'], r['line'], r['name'], r['params'][:60]))
        print()
        print('[B] **可疑**：自由函数带显式 this 形参（`_this`/`*this`）—— %d 处' % len(suspect))
        for r in suspect[:12]:
            print('    %-44s:%-6d %s(%s)' % (r['file'], r['line'], r['name'], r['params'][:56]))
        if len(suspect) > 12:
            print('    … 其余 %d 处' % (len(suspect) - 12))
        print()
        print('[C] decomp 语料：名字无 `::` 却带 this 槽 —— %d 条' % len(dec))
        for k, v in sorted(kinds.items()):
            print('      %-26s %d' % (k, v))
        print()
        print('[D] 普查中与 `this` 相关的语法错（当前代价）—— %d 条' % len(cen))
        for h in cen[:8]:
            print('      %-22s:%-6d %-6s %s' % (os.path.basename(h['unit']), h['line'],
                                                h['code'], h['msg'][:52]))
        print('=' * 78)
    return 1 if illegal else 0


if __name__ == '__main__':
    sys.exit(main())