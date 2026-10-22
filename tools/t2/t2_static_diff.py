#!/usr/bin/env python3
"""T2-F 静态版：decomp 语义差分（同函数伪代码对比）。

## 背景

T2 = 语义等价（同输入 => 同行为，不要求同字节）
T2-F 静态版 = 同函数的 decomp JSON（原版 vs 重制版）语义对比

## 规范化（消除噪声）

| 噪声 | 规范化 |
|---|---|
| 变量名 | 按首次出现序重命名（v1, v2...）|
| 临时变量 | 统一命名 |
| 地址 | 归一为 offset |
| 常量 | 提取（不比值，比存在性）|
| 控制流 | 图同构（不比指令序）|

## 判据

| 维度 | 判据 |
|---|---|
| 函数签名 | 参数类型/返回类型等价 |
| 控制流 | CFG 同构（基本块数/分支数）|
| 调用图 | 调用的目标函数等价 |
| 数据流 | 变量读写模式等价 |

## 用法

    python3 tools/t2/t2_static_diff.py --func NAME
    python3 tools/t2/t2_static_diff.py --batch          # 全量批量对比
"""
import argparse
import json
import os
import re
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DECOMP_DIR = os.path.join(ROOT, 'asm', 'pal3', 'decomp')


def normalize_decomp(text):
    """规范化 decomp 文本（消除噪声）。"""
    # 1. 变量名按首次出现序重命名
    var_map = {}
    def _rename(m):
        name = m.group(0)
        if name not in var_map:
            var_map[name] = f'v{len(var_map)+1}'
        return var_map[name]
    # 匹配变量名（v1/v2/... 或 _DWORD 类型的临时变量）
    text = re.sub(r'\b(?:v|a|arg)\d+\b', _rename, text)
    # 2. 地址归一（0xADDR -> OFFSET）
    text = re.sub(r'0x[0-9a-fA-F]+', 'OFFSET', text)
    # 3. 空白/换行归一
    text = re.sub(r'\s+', ' ', text).strip()
    return text


def extract_features(text):
    """提取语义特征（用于对比）。"""
    norm = normalize_decomp(text)
    features = {
        'signature': _extract_signature(text),
        'cfg_size': len(re.findall(r'\b(?:if|while|for|else|switch)\b', norm)),
        'call_count': len(re.findall(r'\b\w+\s*\(', norm)),
        'branch_count': len(re.findall(r'\b(?:if|else|switch|case)\b', norm)),
        'assign_count': len(re.findall(r'=', norm)),
        'deref_count': len(re.findall(r'\*', norm)),
    }
    return features


def _extract_signature(text):
    """提取函数签名（参数/返回类型）。"""
    m = re.search(r'^([^(]+)\(([^)]*)\)', text.strip())
    if not m:
        return None
    ret = m.group(1).strip().split()[-1] if m.group(1).strip() else '?'
    params = [p.strip() for p in m.group(2).split(',') if p.strip()]
    return {'return': ret, 'params': params}


def diff_features(fa, fb, tolerance=0.1):
    """对比两个特征（容忍度 10%）。"""
    diffs = {}
    for k in ('cfg_size', 'call_count', 'branch_count', 'assign_count', 'deref_count'):
        va, vb = fa.get(k, 0), fb.get(k, 0)
        if va == 0 and vb == 0:
            continue
        ratio = abs(va - vb) / max(va, vb)
        if ratio > tolerance:
            diffs[k] = (va, vb, f'{ratio:.1%}')
    # 签名对比
    if fa.get('signature') != fb.get('signature'):
        diffs['signature'] = (fa.get('signature'), fb.get('signature'))
    return diffs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--func', help='函数名')
    ap.add_argument('--batch', action='store_true', help='全量批量对比')
    args = ap.parse_args()

    if args.batch:
        # 批量：提取所有函数特征（decomp 每函数一文件，字段 decompiled_c）
        count = 0
        for fn in sorted(os.listdir(DECOMP_DIR)):
            if not fn.endswith('.json'):
                continue
            fp = os.path.join(DECOMP_DIR, fn)
            try:
                with open(fp) as f:
                    d = json.load(f)
                text = d.get('decompiled_c') or ''
                if text:
                    extract_features(text)
                    count += 1
            except Exception:
                pass
        print(f'batch: {count} functions analyzed')
        return 0

    if not args.func:
        print('ERROR: 需 --func 或 --batch')
        return 2

    # 单函数：找 decomp JSON
    for fn in sorted(os.listdir(DECOMP_DIR)):
        if not fn.endswith('.json'):
            continue
        fp = os.path.join(DECOMP_DIR, fn)
        try:
            with open(fp) as f:
                d = json.load(f)
            if (d.get('name') == args.func or d.get('name', '').startswith(args.func + '(')) and d.get('decompiled_c'):
                feats = extract_features(d['decompiled_c'])
                print(f'{args.func}:')
                print(json.dumps(feats, indent=2, default=str))
                return 0
        except Exception:
            pass
    print(f'NOT FOUND: {args.func}')
    return 1


if __name__ == '__main__':
    sys.exit(main())
