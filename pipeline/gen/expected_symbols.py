#!/usr/bin/env python3
"""[O4 前置载体门 2026-11-22] expected_symbols——生成树虚拟析构的期望符号清单。

单一事实源=**生成头本身**（pal3/src/**.h 的 `virtual ~Cls()` 两种发射点——
注入形与槽循环形——都产出同一文本）。VC6 对虚析构类确定性合成:
  ??1<Cls>@@UAE@XZ(完全形) + ??_G<Cls>@@UAEPAXI@Z(删除式)
期望清单 → match 载体盘点（coverage 维度可见化）→ 棘轮双账分账的 coverage 侧。

用法: python3 pipeline/gen/expected_symbols.py   # 写 data/status/expected_symbols.json
"""
import glob
import json
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC_DIR = os.path.join(REPO, 'pal3', 'src')
OUT_PATH = os.path.join(REPO, 'data', 'status', 'expected_symbols.json')

_VIRTUAL_DTOR_RE = re.compile(r'\bvirtual\s*~([A-Za-z_]\w*)\s*\(')


def _cls_chain(name):
    return '@'.join(reversed(name.split('::')))


def build_expected_symbols(src_dir=SRC_DIR):
    """扫描生成树 virtual ~Cls() → 每类期望符号。返回 rows(list)。"""
    found = {}
    for f in glob.glob(os.path.join(src_dir, '**', '*.h'), recursive=True):
        try:
            text = open(f, encoding='utf-8', errors='replace').read()
        except OSError:
            continue
        for m in _VIRTUAL_DTOR_RE.finditer(text):
            cls = m.group(1)
            if cls not in found:
                found[cls] = os.path.relpath(f, REPO).replace(os.sep, '/')
    rows = []
    for cls in sorted(found):
        rows.append({
            'cls': cls,
            'header': found[cls],
            'expected': ['??1%s@@UAE@XZ' % _cls_chain(cls),
                         '??_G%s@@UAEPAXI@Z' % _cls_chain(cls)],
        })
    return rows


def main():
    rows = build_expected_symbols()
    out = {
        '_doc': ('expected_symbols 2026-11-22 (O4 前置载体门)——生成树 virtual ~Cls() '
                 '的 VC6 确定性合成符号期望清单；match 载体盘点消费(coverage 维度)'),
        'count': len(rows),
        'rows': rows,
    }
    with open(OUT_PATH, 'w', encoding='utf-8') as f:
        json.dump(out, f, ensure_ascii=False, indent=1)
    print('[expected_symbols] %d 类 → %s' % (len(rows), OUT_PATH))


if __name__ == '__main__':
    main()
