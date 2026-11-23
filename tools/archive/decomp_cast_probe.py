#!/usr/bin/env python3
"""decomp cast 探测器 —— 把编译错误机械分档为「标注缺型」/「有意类型擦除」。

## 为什么需要这个（2026-10-20 用户第一性论点 → 数据证实）

先前我建议「同宽型失配补 cast」，被用户以第一性论点驳回：
  · Hex-Rays 能力足够强 ⇒ annotation 正确时它自己能推断，不需补 cast
  · 需补 cast 要么是原代码用了类型擦除（**有意**），要么是标注错
  · 有意擦除必然少数（到处 void* 代码没法写）

实测数据（472 条 C2440/C2664「不能转换」）：
  · 涉及 SDK/CRT 真 API（有意擦除）：**13 条 = 2%**   ← 用户论点成立
  · 涉及占位型 token（_todo_/_BYTE/地址名）：117 条 = 24%
  · 成员函数签名/参型：342 条 = 72%

## 决定性判据（机械、可判、无需 gold 集）

看 **decomp 原文在该站点是否自带 cast**：

| decomp 形 | 含义 | 处置 |
|---|---|---|
| **无 cast**（`lstrcpyA(byte_X, byte_Y)`）| 原代码类型本就正确 | **补 annotation**（调用点签名即证据）|
| **有 cast**（`lstrcpyA((char*)buf, …)`）| 原代码就是强转 | **保留 cast**，不补不删 |

实证：decomp `lstrcpyA(byte_DE54D4, byte_DD9E3C);` 无 cast ⇒ `byte_DE54D4` 真实型是
`char[]`（lstrcpyA 参数 LPSTR 即二进制证据），是 annotation 没标出来。

## 为什么这比「归因分类器」好

2026-10-20 对抗评审给归因分类器判 PASS-WITH-CHANGES，6 项阻断级（无 gold 集、
codegen 自造名 1846 处误导、双重根因 6%、头文件错误禁判…）。本判据**全部绕开**：
  · 不需 gold 集（判据机械：decomp 有无 cast）
  · 不受 codegen 自造名影响（读 decomp，不读生成源）
  · 双重根因自然可判（cast 在就是有）
  · 头文件错误也可判（decomp 同样有表达式）

## 用法

    python tools/decomp_cast_probe.py            # 全量统计 + 样本
    python tools/decomp_cast_probe.py --json     # JSON 明细
    python tools/decomp_cast_probe.py --dump ANNOTATION_GAP  # 落盘某一档的站点清单

## 纯函数（R15 单测见 tests/test_decomp_cast_probe.py）
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(HERE)
CENSUS = os.path.join(PROJECT_ROOT, 'data', 'status', 'probe_census.json')
DECOMP_DIR = os.path.join(PROJECT_ROOT, 'asm', 'pal3', 'decomp')

# ---------------------------------------------------------------- 纯函数部分

# 生成源的函数入口锚：`// 0x0051DD80` 形（reviewer 实测：2947 函数里 2878 有锚 = 97%）
_RE_ANCHOR = re.compile(r'//\s*0x([0-9A-Fa-f]{6,})')
# 强转表达式：`(T)` / `(T *)` / `(const T *)` 形
_RE_CAST = re.compile(
    r'\(\s*(?:const\s+)?[A-Za-z_]\w*(?:::\w+)*\s*\**\s*\)')
# 类型名/标识符提取（从错误 msg）
_RE_FROM_TO = re.compile(r"from '([^']*)' to '([^']*)'")


def normalize_addr(hexstr):
    """地址归一：'0051DD80' -> '0x0051dd80'（小写、补 0x）。"""
    h = hexstr.lower().lstrip('0x')
    return '0x' + h.zfill(8)


def build_decomp_index(decomp_dir=DECOMP_DIR):
    """address -> decomp 记录索引。"""
    idx = {}
    if not os.path.isdir(decomp_dir):
        return idx
    for fn in os.listdir(decomp_dir):
        if not fn.endswith('.json'):
            continue
        fp = os.path.join(decomp_dir, fn)
        try:
            with open(fp, encoding='utf-8', errors='replace') as fh:
                d = json.load(fh)
        except (OSError, ValueError):
            continue
        a = d.get('address')
        if not a:
            continue
        idx[normalize_addr(str(a))] = d
    return idx


def find_function_anchor(src_lines, line_no):
    """从 line_no 向上找最近的 `// 0xADDR` 函数入口锚（reviewer 验证的映射法）。

    返回 (addr, anchor_line) 或 (None, None)。
    """
    for i in range(min(line_no - 1, len(src_lines) - 1), -1, -1):
        m = _RE_ANCHOR.search(src_lines[i])
        if m:
            return normalize_addr(m.group(1)), i + 1
    return None, None


def extract_identifiers(text, min_len=3):
    """抽标识符（排除关键字/数字）——用于在 decomp 里定位同名实体。"""
    out = []
    for w in re.findall(r'\b[A-Za-z_]\w+\b', text or ''):
        if len(w) >= min_len and not w.isdigit():
            out.append(w)
    return out


def decomp_cast_verdict(decompiled_c, identifiers):
    """判 decomp 里该实体的表达式是否自带 cast。

    返回 ('CAST_PRESENT', hits) / ('NO_CAST', hits) / ('NOT_FOUND', [])。
    判据：decomp 文本里存在 `(<T>)ident` 形（ident 紧随强转）⇒ 原代码自带强转。
    """
    if not decompiled_c:
        return 'NOT_FOUND', []
    hits = []
    for ident in set(identifiers or ()):
        # 紧随强转：`(T)ident` 或 `(T *)ident` 或 `(T *)&ident`
        pat = re.compile(r'\(\s*(?:const\s+)?[A-Za-z_]\w*(?:::\w+)*\s*\**\s*\)\s*'
                         r'&?\s*' + re.escape(ident))
        for m in pat.finditer(decompiled_c):
            line = decompiled_c.count('\n', 0, m.start()) + 1
            hits.append((ident, line, m.group(0)[:60]))
    if hits:
        return 'CAST_PRESENT', hits
    # 找到了标识符但无 cast
    any_found = any(i in decompiled_c for i in set(identifiers or ()))
    return ('NO_CAST', []) if any_found else ('NOT_FOUND', [])


# ---------------------------------------------------------------- 扫描部分

def classify_census(census_path=CENSUS, decomp_dir=DECOMP_DIR):
    """全量分类 C2440/C2664「不能转换」站点。"""
    with open(census_path, encoding='utf-8') as fh:
        d = json.load(fh)
    idx = build_decomp_index(decomp_dir)
    rows = []
    for item in d.get('s2', {}).get('results', []):
        if not isinstance(item, dict):
            continue
        unit = item.get('unit')
        try:
            with open(os.path.join(PROJECT_ROOT, unit), encoding='utf-8',
                      errors='replace') as fh:
                src_lines = fh.read().split('\n')
        except OSError:
            src_lines = []
        for e in item.get('errors', []):
            if not isinstance(e, dict):
                continue
            code = e.get('code')
            if code not in ('C2440', 'C2664'):
                continue
            msg = str(e.get('msg', ''))
            if 'cannot convert' not in msg:
                continue
            line = e.get('line') or 0
            addr, anchor_line = find_function_anchor(src_lines, line)
            rec = idx.get(addr) if addr else None
            # 站点上下文（源码 ±3 行）与 msg 里的型名，作为 decomp 定位用的标识符
            ctx = '\n'.join(src_lines[max(0, line - 4):line]) if src_lines else ''
            idents = extract_identifiers(ctx) + extract_identifiers(msg)
            verdict, hits = ('NOT_FOUND', [])
            if rec is not None:
                verdict, hits = decomp_cast_verdict(
                    rec.get('decompiled_c', ''), idents)
            rows.append({
                'unit': unit, 'line': line, 'code': code, 'msg': msg[:120],
                'addr': addr, 'anchor_line': anchor_line,
                'decomp': bool(rec), 'verdict': verdict,
                'cast_hits': hits[:2],
            })
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--json', action='store_true')
    ap.add_argument('--dump', metavar='VERDICT',
                    help='只输出某档站点（CAST_PRESENT/NO_CAST/NOT_FOUND）')
    args = ap.parse_args()

    rows = classify_census()
    from collections import Counter
    v = Counter(r['verdict'] for r in rows)
    de = Counter(r['decomp'] for r in rows)
    total = len(rows)

    print(f'=== decomp cast 探测（{total} 站点）===')
    print(f'  decomp 可定位: {de.get(True,0)}  |  不可定位: {de.get(False,0)}')
    print()
    print('判档:')
    print(f'  NO_CAST      （decomp 无 cast ⇒ **标注缺型**，调用点签名即证据）: {v.get("NO_CAST",0)}')
    print(f'  CAST_PRESENT （decomp 自带 cast ⇒ **有意类型擦除**，保留不改）  : {v.get("CAST_PRESENT",0)}')
    print(f'  NOT_FOUND    （decomp 不可定位/标识符未命中，需人工）            : {v.get("NOT_FOUND",0)}')

    if args.dump:
        for r in rows:
            if r['verdict'] == args.dump:
                print(f"  {r['unit']}:L{r['line']}  {r['msg']}")
        return 0

    if args.json:
        print(json.dumps({'rows': rows}, ensure_ascii=False, indent=2))
        return 0

    print()
    for tag in ('NO_CAST', 'CAST_PRESENT'):
        print(f'--- {tag} 样本 ---')
        n = 0
        for r in rows:
            if r['verdict'] == tag:
                print(f"  {r['unit'].split('/')[-1]}:L{r['line']}  {r['msg'][:64]}")
                if r['cast_hits']:
                    print(f"      decomp cast: {r['cast_hits'][0][2]}")
                n += 1
                if n >= 5:
                    break
    return 0


if __name__ == '__main__':
    sys.exit(main())
