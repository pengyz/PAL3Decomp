#!/usr/bin/env python3
"""[探针 2026-11-24 #5] 真 SceneManager 类(堆对象, g_pSceneManager@0xBFDA78)取证。

D1 InitGame+0x2D6 前文 40 条 → 工厂形态(new+ctor / thiscall)
D2 全部 `mov ecx, g_pSceneManager` 站点 → 紧跟 call 目标 = 真 SceneManager 方法集
D3 方法集体内 [ecx+disp] 扫描 → 每方法 max disp → 真类成员域上界
D4 工厂函数体全量 dump(operator new 尺寸字面量)
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_real_scenemgr_20261124.py
"""
import sys
import re
import struct
import collections

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idc
import ida_bytes
import ida_funcs
import ida_segment
import ida_name
import idautils

G_P_SCENEMGR = 0x00BFDA78

OUT = []


def say(s):
    print(s)
    OUT.append(s)


def func_range(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea, f.end_ea) if f else (ea, ea + 0x800)


def func_name(ea):
    n = ida_name.get_name(ea)
    return (n if n else 'sub_%X' % ea)[:60]


# ---------------------------------------------------------------- D1
say('=== D1: InitGame 工厂溯源 ===')
init_game = None
for ea in idautils.Functions():
    if ida_name.get_name(ea) == 'InitGame':
        init_game = ea
        break
say('InitGame @ 0x%X' % init_game)
fs, fe = func_range(init_game)
cur = fs
while cur < fe:
    if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
        break
    text = (idc.generate_disasm_line(cur, 0) or '').strip()
    if 'g_pSceneManager' in text:
        say('\n-- 工厂点 %s+0x%X --' % (func_name(fs), cur - fs))
        # 回溯 30 条
        back = cur
        rows = []
        for k in range(30):
            prev = idc.prev_head(back, fs)
            if prev == idc.BADADDR:
                break
            back = prev
            rows.append((back, (idc.generate_disasm_line(back, 0) or '').strip()))
        for a, tx in rows:
            say('   +%#05x %s' % (a - fs, tx))
        say('   +%#05x %s   <<< 工厂赋值' % (cur - fs, text))
        # 工厂点前最后一个 call
        last_call = None
        for a, tx in rows:
            if tx.startswith('call'):
                last_call = (a, tx)
        say('\n工厂 call = %s @ +%#x' % (last_call[1], last_call[0] - fs)
            if last_call else '无直接 call')
        factory_ea = last_call[0] if last_call else None
        if factory_ea:
            m = re.match(r'call\s+([0-9A-Fa-f]+)', last_call[1])
            if m:
                fac = int(m.group(1), 16)
                ffs, ffe = func_range(fac)
                say('\n=== D4: 工厂函数 %s (0x%X, %dB) 全量 ===' % (
                    func_name(fac), fac, ffe - ffs))
                c2 = ffs
                n = 0
                while c2 < ffe and n < 400:
                    if not ida_bytes.is_code(ida_bytes.get_flags(c2)):
                        break
                    tx = (idc.generate_disasm_line(c2, 0) or '').strip()
                    say('   +%#05x %s' % (c2 - ffs, tx))
                    c2 = idc.next_head(c2, ffe)
                    n += 1
        break
    cur = idc.next_head(cur, fe)

# ---------------------------------------------------------------- D2
say('\n=== D2: mov ecx, g_pSceneManager → 方法集 ===')
ts = None
for seg_ea in idautils.Segments():
    s = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(s) == '.text':
        ts = s
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
base = ts.start_ea
# mov ecx, [g_pSceneManager] 的机器码: 8B 0D 78 DA BF 00
pat = b'\x8b\x0d' + struct.pack('<I', G_P_SCENEMGR)
sites = []
i = blob.find(pat)
while i >= 0:
    sites.append(base + i)
    i = blob.find(pat, i + 1)
say('mov ecx, g_pSceneManager 站点: %d' % len(sites))
methods = collections.Counter()
non_call = []
for ea in sites:
    cur = idc.next_head(ea, ea + 32)
    text = (idc.generate_disasm_line(cur, 0) or '').strip()
    m = re.match(r'call\s+([0-9A-Fa-f_]+)', text)
    if m:
        methods[int(m.group(1), 16)] += 1
    else:
        non_call.append((ea, text))
for tgt, cnt in sorted(methods.items()):
    say('  method %s (0x%X) x%d' % (func_name(tgt), tgt, cnt))
for ea, tx in non_call:
    f = ida_funcs.get_func(ea)
    fs = f.start_ea if f else ea
    say('  [非直呼] %s+0x%X: %s' % (func_name(fs), ea - fs, tx))

# ---------------------------------------------------------------- D3
say('\n=== D3: 方法集 [ecx+disp] 成员域 ====')


def scan_this_disp(fstart):
    fs, fe = func_range(fstart)
    got = []
    cur = fs
    n = 0
    while cur < fe and n < 8000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        text = idc.generate_disasm_line(cur, 0) or ''
        parts = text.split(None, 1)
        mnem = parts[0] if parts else ''
        if mnem == 'mov' and re.match(r'\s*ecx\s*,', text[len(mnem):]):
            rhs = text.split(',', 1)[1] if ',' in text else ''
            if not re.search(r',\s*(eax|ebx|edx|esi|edi|ebp|esp|[YZ]H?\b)',
                             rhs) and 'ecx' not in rhs:
                break  # ecx 被重载
        if mnem in ('call', 'jmp', 'ret', 'retn'):
            break
        m = re.search(r'\[ecx\+([0-9A-Fa-f]+)h?\]', text)
        if m:
            got.append((int(m.group(1).rstrip('h'), 16), cur, text.strip()))
        cur = idc.next_head(cur, fe)
        n += 1
    return got


all_max = []
for tgt in sorted(methods):
    got = scan_this_disp(tgt)
    if got:
        mx = max(g[0] for g in got)
        all_max.append((mx, tgt, len(got)))
all_max.sort()
say('方法 %d 个, 有 [ecx+disp]: %d' % (len(methods), len(all_max)))
for mx, tgt, n in all_max[-12:]:
    say('  %-40s max 0x%X (%d 站)' % (func_name(tgt), mx, n))
alld = collections.Counter()
for mx, tgt, n in all_max:
    for d, ea, tx in scan_this_disp(tgt):
        alld[d] += 1
say('全类 disp TOP-30: %s' % ['0x%X(x%d)' % (d, c)
                              for d, c in sorted(alld.items())[-30:]])
say('全类 max disp = 0x%X' % (max(alld) if alld else 0))

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_real_scenemgr_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe5] saved')
idapro.close_database(False)
