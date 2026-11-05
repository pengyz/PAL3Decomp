"""first_diff — 首差定位薄 CLI（spec v2 §1.2·oot first_diff 借鉴）。

复核缩编裁定：s4_diff_detail partial 行已含 first_diff/diffs/obj/compiled_len
（compare_pal3.py:659-665）⇒ 本件=addr 键查找+展示+下一步指路，**非新比对引擎**
（比对语义=gbengine_compare 既有 reloc-aware/min_len 形·不另造签名）。
obj 生命周期（复核硬伤②）：/tmp/pal3_probe 每次 probe rmtree ⇒ obj 缺失时
给重算路径提示（必须 match hypothesis flags·cli.py:737·禁缺省 PROBE_FLAGS=假首差）。
"""
import json
import sys

_DETAIL = 'data/status/s4_diff_detail.json'


def norm_va(v):
    s = str(v or '').strip().lower()
    s = s[2:] if s.startswith('0x') else s
    return int(s, 16)


def find_row(detail, va):
    """addr → detail 行（跨 units·va 归一 int 比）。"""
    want = norm_va(va)
    for rows in (detail.get('units') or {}).values():
        for r in rows or []:
            try:
                if norm_va(r.get('va')) == want:
                    return r
            except (ValueError, TypeError):
                continue
    return None


def build_report(detail, va, obj_exists=None):
    """行 → 展示账（纯·无字节禁造窗口）。obj_exists=None 时按路径实测。"""
    row = find_row(detail, va)
    if row is None:
        return {'found': False, 'va': va, 'next': 'addr 不在 detail（非 partial 面或 va 错）'}
    obj = row.get('obj')
    if obj_exists is None:
        import os
        obj_exists = bool(obj) and os.path.exists(obj)
    if row.get('n_diff', 0) == 0:
        nxt = 'L1 行（n_diff=0）——无首差可展示'
    elif obj_exists:
        nxt = 'obj 在场 → fdiff.py %s（双侧 hex+capstone 既有件）' % obj
    else:
        nxt = ('obj 已清（probe rmtree）→ 重算须重跑 probe（**match hypothesis flags**'
               '·cli.py:737·禁 compare_pal3 缺省 PROBE_FLAGS 否则假首差）；'
               '或先看存储偏移账（first_diff/diffs）')
    nd = row.get('n_diff', 0)
    return {'found': True, 'va': row.get('va'), 'symbol': row.get('symbol'),
            'first_diff': (row.get('first_diff') if nd else None),
            'n_diff': nd,
            'diffs': (row.get('diffs') or [])[:64], 'size': row.get('size'),
            'compiled_len': row.get('compiled_len'), 'obj': obj,
            'obj_exists': obj_exists, 'window': [], 'next': nxt}


def main(argv):
    import argparse
    ap = argparse.ArgumentParser(description='首差定位（thin CLI over s4_diff_detail）')
    ap.add_argument('va', help='函数地址（如 0x0040CFE0）')
    ap.add_argument('--detail', default=_DETAIL)
    a = ap.parse_args(argv)
    detail = json.load(open(a.detail))
    rep = build_report(detail, a.va)
    if not rep['found']:
        print('MISS: %s — %s' % (rep['va'], rep['next']))
        return 1
    print('%s  %s' % (rep['va'], rep['symbol']))
    print('  first_diff=%s  n_diff=%s  size=%s compiled_len=%s  obj=%s (%s)' % (
        rep['first_diff'], rep['n_diff'], rep['size'], rep['compiled_len'],
        rep['obj'], '在场' if rep['obj_exists'] else '已清'))
    print('  diffs[:64]=%s' % rep['diffs'])
    print('  next: %s' % rep['next'])
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
