#!/usr/bin/env python3
"""manual/pal3 L1 对拍（符号名查询）。

## 方案

1. **原 exe**：IDA 导出的函数地址 + 符号名（ida_structs.json / pal3_names.json）
2. **编译 exe**：PDB / objdump 符号表（manual/pal3/build/PAL3_manual.exe）
3. **对拍**：按符号名匹配 => 取地址 => 语义比对 + 字节比对

## L1 对拍两维

- **语义一致性**：汇编操作码序列比对（寄存器名归一化，忽略寄存器分配）
- **字节一致性**：objdump 全字节比对（similarity + diff_bytes）

## 用法

  python3 tools/manual_l1_match.py
"""
import json
import os
import re
import subprocess
import sys
from pathlib import Path


def demangle_msvc(mangled):
    """MSVC C++ 符号 demangle(简化)."""
    if not mangled.startswith('?'):
        return mangled
    s = mangled[1:]
    if '@@' in s:
        parts = s.split('@@')[0].split('@')
        if len(parts) >= 2:
            return f'{parts[1]}::{parts[0]}'
        else:
            return parts[0]
    return mangled

ROOT = Path(__file__).parent.parent
MANUAL_DIR = ROOT / 'manual' / 'pal3'
BUILD_DIR = MANUAL_DIR / 'build'
EXE_PATH = BUILD_DIR / 'PAL3_manual.exe'
ORIG_EXE = ROOT / 'original' / 'PAL3.exe'
IDA_STRUCTS = ROOT / 'asm' / 'pal3' / 'ida_structs.json'
NAMES_PATH = ROOT / 'asm' / 'pal3' / 'pal3_names.json'

# 对拍窗口（双侧同窗口；函数体截断/邻函数污染对称存在，不影响"全同 ⇒ 100%"）
WINDOW = 0x100


def get_manual_symbols():
    """从 map 文件提取符号名(MSVC /MAP)."""
    symbols = {}
    map_path = BUILD_DIR / 'PAL3_manual.map'
    if not map_path.exists():
        print(f'map 文件不存在: {map_path}')
        return symbols
    
    with open(map_path) as f:
        for line in f:
            # map 格式: 0001:offset  name  addr  ...
            if '?' in line and '@' in line:
                parts = line.split()
                if len(parts) >= 3:
                    mangled = parts[1] if '?' in parts[1] else parts[0]
                    addr = parts[2] if len(parts) > 2 else '0'
                    # demangle (Python)
                    demangled = demangle_msvc(mangled)
                    symbols[demangled] = addr
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


def _disasm_lines(addr, exe_path, window=WINDOW):
    """objdump 反汇编行（addr 起 window 字节）。"""
    addr_int = int(addr, 16) if isinstance(addr, str) else addr
    r = subprocess.run(['objdump', '-d', f'--start-address=0x{addr_int:x}',
                       f'--stop-address=0x{addr_int + window:x}', str(exe_path)],
                      capture_output=True, text=True, timeout=60)
    lines = []
    for line in r.stdout.split('\n'):
        if ':' in line and '\t' in line:
            parts = line.split('\t')
            if len(parts) >= 2:
                lines.append(parts)
    return lines


def get_opcodes(addr, exe_path, window=WINDOW):
    """汇编操作码序列（寄存器名归一化，忽略寄存器分配）。"""
    opcodes = []
    for parts in _disasm_lines(addr, exe_path, window):
        if len(parts) >= 3:
            asm = parts[2].strip()
            asm = re.sub(r'%\w+', '%REG', asm)
            opcodes.append(asm)
    return opcodes


def compare_semantic(sym_name, manual_addr, orig_addr):
    """语义一致性比对（忽略寄存器分配）。

    方法：比较汇编操作码（忽略寄存器名），返回 0.0~1.0。
    """
    manual_ops = get_opcodes(manual_addr, EXE_PATH)
    orig_ops = get_opcodes(orig_addr, ORIG_EXE)
    
    if manual_ops and orig_ops:
        max_len = max(len(manual_ops), len(orig_ops))
        match_count = sum(1 for a, b in zip(manual_ops, orig_ops) if a == b)
        return match_count / max_len if max_len > 0 else 0.0
    return 0.0


def extract_bytes(addr, exe_path, window=WINDOW):
    """提取字节(objdump，全字节).

    [修 2026-10-27] 原 `parts[1].split(' ')[0]` 每指令行只取首字节
    ⇒ 字节相似度虚高（实测 InitVFileSystem 28.8% vs 全字节 10.2%）。
    改为取行内全部字节，"字节一致性"才是真字节级比对。
    """
    bytes_list = []
    for parts in _disasm_lines(addr, exe_path, window):
        bytes_list.extend(parts[1].split())
    return bytes_list


def compare_bytes(manual_addr, orig_addr):
    """字节一致性比对（全字节）。返回 (similarity 0.0~1.0, diff_bytes)。"""
    manual_bytes = extract_bytes(manual_addr, EXE_PATH)
    orig_bytes = extract_bytes(orig_addr, ORIG_EXE)
    if manual_bytes and orig_bytes:
        max_len = max(len(manual_bytes), len(orig_bytes))
        match_count = sum(1 for a, b in zip(manual_bytes, orig_bytes) if a == b)
        similarity = match_count / max_len if max_len > 0 else 0.0
        return similarity, max_len - match_count
    return 0.0, 0


def match_l1():
    """L1 对拍（符号名匹配：语义一致性 + 字节一致性）。"""
    print('=== manual/pal3 L1 对拍（符号名查询）===')
    
    # 1. 提取编译 exe 符号
    manual_syms = get_manual_symbols()
    print(f'编译 exe 符号: {len(manual_syms)} 个')
    
    # 2. 获取原 exe 地址
    orig_addrs = get_original_addresses()
    print(f'原 exe 地址: {len(orig_addrs)} 个')
    
    # 3. 按符号名匹配（demangle 后）
    # [R115 修] 地址匹配是巧合 => 按符号名匹配
    matched = []
    for sym_name, sym_addr in manual_syms.items():
        # sym_name 已 demangle（如 PAL3::InitVolModNode）
        if sym_name in orig_addrs:
            orig_addr = orig_addrs[sym_name]
            # 字节一致性比对（全字节）
            similarity, diff_bytes = compare_bytes(sym_addr, orig_addr)
            # 语义一致性比对（操作码，忽略寄存器分配）
            semantic_match = compare_semantic(sym_name, sym_addr, orig_addr)
            
            matched.append({
                'symbol': sym_name,
                'manual_addr': sym_addr,
                'orig_addr': orig_addr,
                'semantic_match': semantic_match,
                'similarity': similarity,
                'diff_bytes': diff_bytes,
            })
    
    print(f'\n匹配结果: {len(matched)} 个')
    for m in matched[:10]:
        print(f'  {m["symbol"]}: manual={m["manual_addr"]} orig={m["orig_addr"]} '
              f'语义={m["semantic_match"]*100:.1f}% 字节={m["similarity"]*100:.1f}%')
    
    return matched


if __name__ == '__main__':
    matched = match_l1()
    n = len(matched)
    if n:
        sem_avg = sum(m['semantic_match'] for m in matched) / n * 100
        byte_avg = sum(m['similarity'] for m in matched) / n * 100
        print(f'\n  平均语义相似度: {sem_avg:.1f}%')
        print(f'  平均字节相似度: {byte_avg:.1f}%')
    print(f'\n=== L1 对拍完成: {n} 个匹配 ===')
