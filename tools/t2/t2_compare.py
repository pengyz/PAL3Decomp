#!/usr/bin/env python3
"""T2-F 静态对比：原版 decomp vs 重制版 C++（语义等价判据）。

## 对比对象

| 侧 | 来源 | 说明 |
|---|---|---|
| **原版** | `asm/pal3/decomp/*.json`（decompiled_c）| Hex-Rays 反编译 |
| **重制版** | `pal3/src/**/*.cpp` | codegen 生成 |

## 判据（T2 = 语义等价）

| 维度 | 判据 | 容忍度 |
|---|---|---|
| 函数签名 | 参数类型/返回类型 | 严格 |
| 控制流 | CFG 大小（if/while/for）| 10% |
| 调用 | 调用次数 | 10% |
| 分支 | 分支数 | 10% |
| 赋值 | 赋值数 | 10% |
| 解引用 | * 次数 | 10% |

## 用法

    python3 tools/t2/t2_compare.py --func NAME
    python3 tools/t2/t2_compare.py --batch          # 全量
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DECOMP_DIR = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
SRC_DIR = os.path.join(ROOT, 'pal3', 'src')


def extract_features(text):
    """提取语义特征（与 t2_static_diff 一致）。"""
    norm = re.sub(r'\s+', ' ', text).strip()
    return {
        'signature': _extract_signature(text),
        'cfg_size': len(re.findall(r'\b(?:if|while|for|else|switch)\b', norm)),
        'call_count': len(re.findall(r'\b\w+\s*\(', norm)),
        'branch_count': len(re.findall(r'\b(?:if|else|switch|case)\b', norm)),
        'assign_count': len(re.findall(r'=', norm)),
        'deref_count': len(re.findall(r'\*', norm)),
    }


def _extract_signature(text):
    m = re.search(r'^([^(]+)\(([^)]*)\)', text.strip())
    if not m:
        return None
    ret = m.group(1).strip().split()[-1] if m.group(1).strip() else '?'
    params = [p.strip() for p in m.group(2).split(',') if p.strip()]
    return {'return': ret, 'params': params}


def diff_features(fa, fb, tolerance=0.1):
    diffs = {}
    for k in ('cfg_size', 'call_count', 'branch_count', 'assign_count', 'deref_count'):
        va, vb = fa.get(k, 0), fb.get(k, 0)
        if va == 0 and vb == 0:
            continue
        ratio = abs(va - vb) / max(va, vb)
        if ratio > tolerance:
            diffs[k] = (va, vb, f'{ratio:.1%}')
    return diffs


def find_cpp_for_function(func_name):
    """在 pal3/src 找函数的 C++ 实现。"""
    # 函数名可能带类前缀（Class::Method）
    short = func_name.split('::')[-1] if '::' in func_name else func_name
    short = short.split('(')[0]  # 去签名
    for dirpath, _, filenames in os.walk(SRC_DIR):
        for fn in filenames:
            if not fn.endswith('.cpp'):
                continue
            fp = os.path.join(dirpath, fn)
            try:
                with open(fp) as f:
                    content = f.read()
                # 找函数定义（形如 ret_type short(...）{）
                pattern = r'\b' + re.escape(short) + r'\s*\([^)]*\)\s*\{'
                m = re.search(pattern, content)
                if m:
                    # 提取函数体（粗略：到匹配的 }）
                    start = m.start()
                    depth = 0
                    end = start
                    for i, ch in enumerate(content[start:], start):
                        if ch == '{':
                            depth += 1
                        elif ch == '}':
                            depth -= 1
                            if depth == 0:
                                end = i + 1
                                break
                    return content[start:end]
            except Exception:
                pass
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--func', help='函数名')
    ap.add_argument('--batch', action='store_true', help='全量对比')
    args = ap.parse_args()

    if args.batch:
        total = matched = equivalent = 0
        for fn in sorted(os.listdir(DECOMP_DIR)):
            if not fn.endswith('.json'):
                continue
            fp = os.path.join(DECOMP_DIR, fn)
            try:
                with open(fp) as f:
                    d = json.load(f)
                func_name = d.get('name', '')
                decomp_text = d.get('decompiled_c', '')
                if not func_name or not decomp_text:
                    continue
                total += 1
                cpp_text = find_cpp_for_function(func_name)
                if cpp_text:
                    matched += 1
                    f_orig = extract_features(decomp_text)
                    f_remake = extract_features(cpp_text)
                    diffs = diff_features(f_orig, f_remake)
                    if not diffs:
                        equivalent += 1
            except Exception:
                pass
        print(f'batch: total={total} matched={matched} equivalent={equivalent}')
        if matched > 0:
            print(f'  T2-F 等价率: {equivalent}/{matched} = {equivalent/matched*100:.1f}%')
        return 0

    if not args.func:
        print('ERROR: 需 --func 或 --batch')
        return 2

    # 单函数对比
    for fn in sorted(os.listdir(DECOMP_DIR)):
        if not fn.endswith('.json'):
            continue
        fp = os.path.join(DECOMP_DIR, fn)
        try:
            with open(fp) as f:
                d = json.load(f)
            if d.get('name', '').startswith(args.func) and d.get('decompiled_c'):
                decomp_text = d['decompiled_c']
                cpp_text = find_cpp_for_function(args.func)
                if not cpp_text:
                    print(f'NOT FOUND in C++: {args.func}')
                    return 1
                f_orig = extract_features(decomp_text)
                f_remake = extract_features(cpp_text)
                diffs = diff_features(f_orig, f_remake)
                print(f'{args.func}:')
                print(f'  orig:   {f_orig}')
                print(f'  remake: {f_remake}')
                print(f'  diffs:  {diffs if diffs else "NONE (equivalent)"}')
                return 0
        except Exception:
            pass
    print(f'NOT FOUND: {args.func}')
    return 1


if __name__ == '__main__':
    sys.exit(main())
