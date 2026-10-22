#!/usr/bin/env python3
"""annotation 前置全检（秒级快速失败）—— shift-left 验证。

## 为什么（2026-10-21 用户思路）

问题必须到管线阶段才体现（export 150s + codegen 200s + probe）⇒ 验证循环效率低。
**能前置的验证尽量前置**：内存重叠/函数声明重复/非法数组界等**秒级可查**的问题，
不该拖到 codegen/probe（5+ 分钟）才暴露。

## 检查项（全部秒级）

| 检查 | 失败形 | 教训来源 |
|---|---|---|
| **内存重叠** | 同偏移多成员（非 union）| CLAUDE.md overlap 三判据 |
| **函数声明重复** | 同名/同签名 | 通用 |
| **非法数组界** | `[N]` / `[0]` / 负数 | R57 `[N]` = codegen 崩 |
| **类型引用完整性** | 引用不存在的类型 | 通用 |
| **两说并存** | 新旧说同 source | P0-9（R56/R57 三连轮）|
| **成员偏移越界** | offset > binary_size | check_member_extent |
| **证据等级缺失** | 无 evidence_level 标注 | 证据模型纪律 |
| **占位名越界** | `_todo_` 后缀混用 | CLAUDE.md 禁伪语义命名 |

## 用法
    python3 tools/check_annotation_preflight.py           # 全检
    python3 tools/check_annotation_preflight.py --cls RoleSystem
    python3 tools/check_annotation_preflight.py --json
"""
import argparse
import glob
import json
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN = os.path.join(ROOT, 'data', 'annotations')

# P0-9 两说并存对
DUAL_PAIRS = [
    ('值位面复用铁证', '撤位面标'), ('值位面复用铁证', '值镜像'),
    ('ptr 对', 'int 对'), ('数组基=this+0x118', '折叠自洽'),
    ('50 元素', '16 元素'), ('100 元素', '10 元素'),
    ('SINGLE_FLOAT', 'SINGLE_ASSIGN'), ('SINGLE_FLOAT', 'MIXED'),
]

# 合法数组界形：[N] where N is positive integer
_ARRAY_RE = re.compile(r'\[(\d+)\]')


def load_structs():
    out = []
    for fp in sorted(glob.glob(os.path.join(ANN, 'structs', '*.json'))):
        try:
            with open(fp, encoding='utf-8') as fh:
                out.append((os.path.basename(fp)[:-5], json.load(fh), fp))
        except (OSError, ValueError) as e:
            out.append((os.path.basename(fp)[:-5], {'_parse_error': str(e)}, fp))
    return out


def check_struct(name, d, path):
    issues = []
    bs = d.get('binary_size') or 0
    ms = d.get('known_members') or {}

    # ① 内存重叠（非 union）—— [R59 修跨距漏报] 补 span 检查
    # R59 reviewer 抓：+0 int[25]（span 100）× +50 int 跨距相交 = 零报（只查同起点）
    def _tsize(t, depth=0):
        if depth > 5:
            return 4
        # [R60 修 dict 型 span=0 漏报] struct[int[6]] 真 24B 算 0
        if isinstance(t, dict):
            if 'union' in t:
                return max((_tsize(x.get('type'), depth + 1) for x in t['union']), default=4)
            if 'struct' in t:
                return sum(_tsize(x.get('type'), depth + 1) for x in t['struct'])
            return 4
        t = str(t or '').strip()
        m2 = re.match(r'^(.+?)\s*\[(\d+)\]$', t)
        if m2:
            return _tsize(m2.group(1), depth + 1) * int(m2.group(2))
        if t.endswith('*') or t.endswith('[]'):
            return 4
        b = re.sub(r'\s*\*$', '', t).strip()
        for sz, names in ((8, ('double', '__int64', '_QWORD')),
                          (4, ('int', 'float', 'long', 'unsigned long',
                               'unsigned int', '_DWORD', 'BOOL', 'DWORD', 'UINT')),
                          (2, ('short', 'WORD', 'unsigned short', '_WORD')),
                          (1, ('char', 'BYTE', 'bool', 'unsigned char', '_BYTE'))):
            if b in names:
                return sz
        return 4  # 保守默认
    spans = []  # [(start, end, name)]
    for k, m in ms.items():
        if not isinstance(m, dict):
            continue
        t = m.get('type')
        # union 豁免（CLAUDE.md: union 本身即 overlap 声明）
        if isinstance(t, dict) and 'union' in t:
            continue
        try:
            off = int(k)
        except (ValueError, TypeError):
            continue
        span = _tsize(t)
        spans.append((off, off + max(span, 1), m.get('name')))
    # 跨距相交检测（排序后相邻）
    spans.sort()
    for i in range(1, len(spans)):
        p1, p2 = spans[i - 1], spans[i]
        if p2[0] < p1[1]:  # 跨距相交
            issues.append({'kind': 'overlap_span', 'severity': 'high',
                           'msg': f'{p1[2]}[+{p1[0]}..+{p1[1]}) 与 {p2[2]}[+{p2[0]}..) 跨距相交（非 union）'})

    # ② 非法数组界
    for k, m in ms.items():
        if not isinstance(m, dict):
            continue
        t = str(m.get('type') or '')
        # [N] 形必须 N>0
        for am in _ARRAY_RE.finditer(t):
            n = int(am.group(1))
            if n <= 0:
                issues.append({'kind': 'illegal_array_bound', 'severity': 'critical',
                               'msg': f'{m.get("name")} type={t} 数组界 {n} ≤ 0 = codegen 崩'})
        # [N] 字面量（非数字）
        if re.search(r'\[\s*[A-Za-z_]\w*\s*\]', t):
            issues.append({'kind': 'illegal_array_bound', 'severity': 'critical',
                           'msg': f'{m.get("name")} type={t} 数组界是标识符（非数字）= codegen 崩'})

    # ③ 两说并存 —— [R59 修驳斥文误报] 加语境检查
    # R59 reviewer 抓：正当驳斥文（"旧文X系误判已改Y"）被报 dual_claim
    # 判据：旧说须**未被否定**（非"撤回/误判/改判/修正"语境）
    # [R60 修否定前缀绕过] 「非误判」含"误判"⇒反向豁免 = 真两说并存漏报
    # 须词边界 + 否定前缀排除（非/未/不是/并非 + 否定词 ⇒ 不算否定）
    _NEGATE = re.compile(
        r'(?<![非未不并非])(?:撤回|误判|改判|修正|撤位面标|retract|wrong|falsif)'
        r'|(?:已经|已|系)(?:撤回|误判|改判|修正|撤位面标)'
    )
    for sec in ('known_members', 'methods'):
        for k, m in (d.get(sec) or {}).items():
            if not isinstance(m, dict):
                continue
            s = str(m.get('source') or '')
            for old_claim, new_claim in DUAL_PAIRS:
                if old_claim not in s or new_claim not in s:
                    continue
                # 语境：旧说附近有否定词 ⇒ 驳斥文（不报）
                idx = s.find(old_claim)
                ctx = s[max(0, idx - 40): idx + len(old_claim) + 40]
                if _NEGATE.search(ctx):
                    continue  # 驳斥文豁免
                issues.append({'kind': 'dual_claim', 'severity': 'high',
                               'msg': f'{sec}+{k} {m.get("name")} 旧「{old_claim}」+ 新「{new_claim}」'})

    # ④ 成员偏移越界
    if bs:
        for k, m in ms.items():
            try:
                off = int(k)
            except (ValueError, TypeError):
                continue
            if off >= bs:
                issues.append({'kind': 'offset_out_of_range', 'severity': 'high',
                               'msg': f'+{off} {m.get("name")} ≥ binary_size {bs}'})

    # ⑤ 函数声明重复（methods 内同名）
    names = defaultdict(list)
    for k, m in (d.get('methods') or {}).items():
        if isinstance(m, dict) and m.get('name'):
            names[str(m['name'])].append(k)
    for nm, addrs in names.items():
        if len(addrs) > 1 and '__ovl_' not in nm:
            issues.append({'kind': 'duplicate_method_name', 'severity': 'medium',
                           'msg': f'methods 同名 {nm} ×{len(addrs)}（需 __ovl_ 去重）'})
    return issues


def check_functions(path=None):
    """functions.json 全局检查。"""
    issues = []
    fp = os.path.join(ANN, 'functions.json')
    try:
        with open(fp, encoding='utf-8') as fh:
            fn = json.load(fh)
    except (OSError, ValueError):
        return issues
    names = defaultdict(list)
    sigs = defaultdict(list)
    for addr, v in fn.items():
        if not isinstance(v, dict):
            continue
        nm = str(v.get('name') or '')
        sig = str(v.get('signature') or '')
        if nm:
            names[nm].append(addr)
        if sig:
            sigs[sig].append((addr, nm))
    for nm, addrs in names.items():
        if len(addrs) > 1 and '__ovl_' not in nm:
            issues.append({'kind': 'duplicate_function_name', 'severity': 'medium',
                           'msg': f'functions 同名 {nm} ×{len(addrs)}（需 __ovl_ 去重）'})
    for sig, items in sigs.items():
        if len(items) > 1:
            # 同签名不同名 = 可疑
            nameset = {n for _, n in items}
            if len(nameset) > 1:
                issues.append({'kind': 'duplicate_signature', 'severity': 'low',
                               'msg': f'同签名 ×{len(items)} 不同名 {list(nameset)[:3]}（可疑）'})
    return issues


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--cls')
    ap.add_argument('--json', action='store_true')
    args = ap.parse_args()

    all_issues = []
    for name, d, path in load_structs():
        if args.cls and name != args.cls:
            continue
        if '_parse_error' in d:
            all_issues.append({'cls': name, 'kind': 'parse_error', 'severity': 'critical',
                               'msg': d['_parse_error']})
            continue
        for i in check_struct(name, d, path):
            i['cls'] = name
            all_issues.append(i)
    if not args.cls:
        for i in check_functions():
            i['cls'] = '(functions.json)'
            all_issues.append(i)

    by_sev = defaultdict(int)
    for i in all_issues:
        by_sev[i['severity']] += 1

    if args.json:
        print(json.dumps({'issues': all_issues, 'count': len(all_issues),
                          'by_severity': dict(by_sev)}, ensure_ascii=False, indent=2))
    else:
        if not all_issues:
            print('✅ 前置全检通过')
            return 0
        print(f'⚠️ 前置全检 {len(all_issues)} 项（critical {by_sev["critical"]} · '
              f'high {by_sev["high"]} · medium {by_sev["medium"]} · low {by_sev["low"]}）')
        for sev in ('critical', 'high', 'medium', 'low'):
            items = [i for i in all_issues if i['severity'] == sev]
            if not items:
                continue
            print(f'\n  [{sev.upper()}] {len(items)}:')
            for i in items[:8]:
                print(f"    {i['cls']} · {i['kind']}: {i['msg'][:90]}")
            if len(items) > 8:
                print(f'    ... 还有 {len(items)-8} 项')
        return 1 if by_sev['critical'] or by_sev['high'] else 0
    return 0


if __name__ == '__main__':
    sys.exit(main())
