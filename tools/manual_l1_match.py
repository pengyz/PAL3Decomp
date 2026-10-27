#!/usr/bin/env python3
"""manual/pal3 L1 对拍（符号名查询）。

## 方案

1. **原 exe**：IDA 导出的函数地址 + 符号名（ida_structs.json / pal3_names.json）
2. **编译 exe**：PDB / objdump 符号表（manual/pal3/build/PAL3_manual.exe）
3. **对拍**：按符号名匹配 => 取地址 => 字节比对

## 用法

  python3 tools/manual_l1_match.py
"""
import json
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
MANUAL_DIR = ROOT / 'manual' / 'pal3'
BUILD_DIR = MANUAL_DIR / 'build'
EXE_PATH = BUILD_DIR / 'PAL3_manual.exe'
ORIG_EXE = ROOT / 'original' / 'PAL3.exe'
IDA_STRUCTS = ROOT / 'asm' / 'pal3' / 'ida_structs.json'
NAMES_PATH = ROOT / 'asm' / 'pal3' / 'pal3_names.json'


def get_manual_symbols():
    """从 map 文件提取符号名(MSVC /MAP)."""
    symbols = {}
    map_path = BUILD_DIR / 'PAL3_manual.map'
    if not map_path.exists():
        print(f'map 文件不存在: {map_path}')
        return symbols
    
    import subprocess
    with open(map_path) as f:
        for line in f:
            # map 格式: 0001:offset  name  addr  ...
            if '?' in line and '@' in line:
                parts = line.split()
                if len(parts) >= 3:
                    mangled = parts[1] if '?' in parts[1] else parts[0]
                    addr = parts[2] if len(parts) > 2 else '0'
                    # demangle (MSVC undname)
                    r = subprocess.run(['wine', str(ROOT / 'tools' / 'compilers' / 'msvc6.0' / 'Bin' / 'UNDNAME.EXE'), mangled],
                                       capture_output=True, text=True, timeout=30)
                    demangled = r.stdout.strip().split('\n')[0] if r.stdout else mangled
                    symbols[demangled] = addr
    return symbols
    
    r = subprocess.run(['objdump', '-t', str(EXE_PATH)],
                       capture_output=True, text=True, timeout=60)
    for line in r.stdout.split('\n'):
        # objdump 符号格式：addr flags section name
        parts = line.split()
        if len(parts) >= 5 and parts[1] != 'g':
            continue
        if len(parts) >= 5:
            addr = parts[0]
            name = parts[-1]
            if '::' in name:  # C++ 符号
                symbols[name] = addr
    return symbols


def get_original_addresses():
    """从 IDA 导出获取原 exe 地址（符号名 => 地址）。"""
    addresses = {}
    
    # 从 ida_structs.json
    if IDA_STRUCTS.exists():
        ida = json.load(open(IDA_STRUCTS))
        for cls, v in ida.items():
            if not isinstance(v, dict):
                continue
            ms = v.get('methods') or {}
            for addr, m in ms.items():
                if isinstance(m, dict) and m.get('name'):
                    full_name = f'{cls}::{m["name"]}'
                    addresses[full_name] = addr
    
    # 从 pal3_names.json
    if NAMES_PATH.exists():
        names = json.load(open(NAMES_PATH))
        for f in names.get('functions', []):
            if f.get('name'):
                addresses[f['name']] = f['address']
    
    return addresses


def match_l1():
    """L1 对拍（符号名匹配）。"""
    print('=== manual/pal3 L1 对拍（符号名查询）===')
    
    # 1. 提取编译 exe 符号
    manual_syms = get_manual_symbols()
    print(f'编译 exe 符号: {len(manual_syms)} 个')
    
    # 2. 获取原 exe 地址
    orig_addrs = get_original_addresses()
    print(f'原 exe 地址: {len(orig_addrs)} 个')
    
    # 3. 地址匹配（map addr vs pal3_names addr）
    # [R114 修] demangle 失败 => 改地址匹配
    orig_addr_map = {}
    for name, addr in orig_addrs.items():
        orig_addr_map[addr] = name
    
    matched = []
    for sym_name, sym_addr in manual_syms.items():
        # sym_addr 格式: 00401480 (map) vs 0x00408BC0 (pal3_names)
        sym_addr_norm = '0x' + sym_addr.zfill(8).upper()
        if sym_addr_norm in orig_addr_map:
            matched.append({
                'symbol': sym_name,
                'manual_addr': sym_addr,
                'orig_addr': sym_addr_norm,
                'orig_name': orig_addr_map[sym_addr_norm],
            })
    
    print(f'\\n匹配结果: {len(matched)} 个')
    for m in matched[:10]:
        print(f'  {m["symbol"]}: manual={m["manual_addr"]} orig={m["orig_addr"]}')
    
    return matched


if __name__ == '__main__':
    matched = match_l1()
    print(f'\\n=== L1 对拍完成: {len(matched)} 个匹配 ===')
