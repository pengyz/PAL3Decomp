#!/usr/bin/env python3
"""[decomp索引归一化 2026-11-15] address字段双形态(int/str)统一装载。
事故: 字符串索引层漏读int形态文件→sub_0045xxx族"空体"假象(B4深化批实证)。
"""
import json, glob, os, re

def norm_addr(a):
    """规范形断言: 非 ^0x[0-9a-f]{8}$ 直接抛错(N11同哲学, 不静默归一不擦屁股)。"""
    s = a if isinstance(a, str) else None
    if s is None or not re.match(r'^0x[0-9a-f]{8}$', s):
        raise ValueError('非规范地址形(须0x+8位小写hex, 见N11门禁): %r' % (a,))
    return s

def load_decomp_index(root=None):
    root = root or os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
    idx = {}
    for p in glob.glob(os.path.join(root, 'asm', 'pal3', 'decomp', '*.json')):
        d = json.load(open(p, encoding='utf-8'))
        try: a = norm_addr(d.get('address'))
        except Exception: continue
        idx[a] = {'name': d.get('name', ''), 'body': d.get('decompiled_c') or '',
                  'signature': d.get('signature', ''), 'file': os.path.basename(p)}
    return idx


def _selftest():
    """用例钉死: 双形态归一化 [2026-11-15 纪律补课]"""
    for good in ('0x00459fa0', '0x00401000'):
        assert norm_addr(good) == good
    for bad in (0x459fa0, '0x459fa0', '459fa0', '0x00459FA0', None, '', 'xyz'):
        try:
            norm_addr(bad)
            raise AssertionError('FAIL 越轨输入未拒绝: %r' % (bad,))
        except (ValueError, TypeError):
            pass
    print('norm_addr 响败断言: 规范形直通+7类越轨全拒 全过')


if __name__ == '__main__':
    _selftest()
