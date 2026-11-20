#!/usr/bin/env python3
"""[审计 2026-11-18] 语义覆盖普查——全库结构已命名成员字节覆盖率。

口径:
  覆盖字节 = Σ成员(type 可估尺寸), 伪语义名(_todo_*/_field_*/_gap_*/unk_*/无语义后缀)
  不计入覆盖但计入占用 → 两套数: 命名覆盖率 / 占位率。
  方法层另算: methods 条目数 (语料归属方法数对账在 N13 门禁, 此处只报库存)。

用法: python3 tools/audit_semantic_coverage_20261118.py [--min-size N] [--top N]
"""
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
SDIR = REPO / 'data/annotations/structs'

# 简易类型尺寸表 (MSVC6 x86)
PTR = 4
# [R6 audit 改造 20261120] structs name→binary_size 索引——嵌套类型取真尺寸
# (CPK.m_CPKTable[32768]×tagCPKTable(28)=0xE0000 等——老 type_size 对自定义类型
#  返回 None→4 严重低估大数组实际尺寸, 是字节口径 0% 假象的根因之一)
_struct_sizes = {}
def _build_struct_sizes():
    if _struct_sizes:
        return
    import glob as _g
    for _fp in _g.glob(str(SDIR / '*.json')):
        try:
            _d = json.loads(Path(_fp).read_text(encoding='utf-8'))
            _n, _b = _d.get('name'), _d.get('binary_size')
            if _n and _b:
                _struct_sizes[_n] = _b
        except Exception:
            pass

def type_size(t):
    t = str(t).strip()
    _build_struct_sizes()
    if t.endswith('*'):
        return PTR
    # 数组: TYPE[N] / TYPE[N][M]
    m = re.match(r'^(.*)\[(\d+)\]$', t)
    if m:
        inner = type_size(m.group(1))
        return (inner if inner else 0) * int(m.group(2))
    # 嵌套类型: 查 structs 索引取 binary_size(真尺寸)
    if t in _struct_sizes:
        return _struct_sizes[t]
    base = {
        'char': 1, 'signed char': 1, 'unsigned char': 1, '_BYTE': 1, 'BYTE': 1, 'bool': 1,
        'short': 2, 'unsigned short': 2, 'short int': 2, '_WORD': 2, 'WORD': 2,
        'int': 4, 'unsigned int': 4, 'signed int': 4, '_DWORD': 4, 'DWORD': 4,
        'long': 4, 'unsigned long': 4, 'float': 4, 'BOOL': 4,
        'double': 8, '__int64': 8, 'LONGLONG': 8,
        'tagPOINT': 8, 'RECT': 16,
    }
    if t in base:
        return base[t]
    return None

PSEUDO = re.compile(r'^(_todo_\w*|_field_\w*|_gap_\w*|unk_\w*|_nearby_\w*|slot_unk\w*|method_\w*|stru_\w*|byte_\w*|word_\w*|dword_\w*|off_\w*)$', re.I)

rows = []
for f in sorted(SDIR.glob('*.json')):
    try:
        d = json.loads(f.read_text(encoding='utf-8'))
    except Exception:
        continue
    name = d.get('name') or f.stem
    size = d.get('binary_size') or 0
    if size < 256:
        continue
    km = d.get('known_members') or {}
    named_bytes = 0
    pseudo_bytes = 0
    pseudo_cnt = 0
    named_cnt = 0
    unestimated = 0
    for off, m in km.items():
        sz = type_size(m.get('type'))
        if sz is None:
            unestimated += 1
            sz = 4
        if PSEUDO.match(str(m.get('name') or '')):
            pseudo_bytes += sz
            pseudo_cnt += 1
        else:
            named_bytes += sz
            named_cnt += 1
    cov = named_bytes / size if size else 0
    rows.append({
        'name': name, 'size': size,
        'named_cnt': named_cnt, 'pseudo_cnt': pseudo_cnt, 'unestimated': unestimated,
        'named_bytes': named_bytes, 'pseudo_bytes': pseudo_bytes,
        'cover': cov,
        'methods': len([m for m in (d.get('methods') or {}).values() if isinstance(m, dict)]),
    })

rows.sort(key=lambda r: (r['cover'], -r['size']))
min_size = int(sys.argv[sys.argv.index('--min-size') + 1]) if '--min-size' in sys.argv else 256
top = int(sys.argv[sys.argv.index('--top') + 1]) if '--top' in sys.argv else 40

print('=== 语义覆盖最差结构 (size≥%d, 命名覆盖率升序, top %d) ===' % (min_size, top))
print('%9s  %-42s %6s  %5s %5s %5s  %7s' % ('size', '结构', '覆盖%', '命名', '占位', '方法', '未估型'))
shown = 0
for r in rows:
    if r['size'] < min_size:
        continue
    if shown >= top:
        break
    print('%9d  %-42s %5.1f%%  %5d %5d %5d  %7d' % (
        r['size'], r['name'][:42], r['cover'] * 100, r['named_cnt'],
        r['pseudo_cnt'], r['methods'], r['unestimated']))
    shown += 1

# 汇总
tot_named = sum(r['named_bytes'] for r in rows)
tot_pseudo = sum(r['pseudo_bytes'] for r in rows)
tot_size = sum(r['size'] for r in rows)
print()
print('=== 全库汇总 (size≥256 的 %d 个结构) ===' % len(rows))
print('总字节: %d | 语义命名字节: %d (%.1f%%) | 伪语义占位字节: %d (%.1f%%) | 未命名: %.1f%%' % (
    tot_size, tot_named, tot_named / tot_size * 100,
    tot_pseudo, tot_pseudo / tot_size * 100,
    (1 - (tot_named + tot_pseudo) / tot_size) * 100))
big_missing = [r for r in rows if r['size'] >= 1000 and r['cover'] < 0.5]
print('size≥1000 且覆盖<50%%: %d 个, 合计未命名 %d 字节' % (
    len(big_missing), sum(r['size'] - r['named_bytes'] for r in big_missing)))
