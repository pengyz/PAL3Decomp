#!/usr/bin/env python3
"""[探针 2026-11-21] CCBUI 身份定谳——binary_size=100572(L1新判) vs 2648(旧值+0x525540误归属旗) 矛盾终审。

矛盾:
  H1(新): 0x525540=CCBUI完全dtor → 100572B    [反证: 0x52555D 写表 0x5706CC ≠ 登记表 0x5704C8]
  H2/H3(旧): 0x525540=异类(ShopUI/SaleUI簇) → 2648B 真身

决定性判据:
  D1 ~CCBUI@0x519360(删除式, slot5)的 call 目标 = 完全dtor身份
  D2 0x525540/0x519380 的 vtable 写入地址 + 全量 call 目标 + 最大 disp
  D3 XrefsTo(0x525540/0x519360/0x519380/0x519310)
  D4 双表字节(0x5704C8 / 0x5706CC)
  D5 0x519xxx 方法簇最大 disp(≤2648? = 2648类真身佐证)

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_ccbui_identity_20261121.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)
print('[probe] db opened:', db)

import idc
import ida_ua
import ida_bytes
import ida_funcs
import idautils

FUNCS = [
    ('ctor(CCBUI::CCBUI?)',   0x00519310),
    ('~CCBUI(删除式,slot5)',   0x00519360),
    ('Release(现名/unverif)',  0x00519380),
    ('InitShopUI(0x525540)',  0x00525540),
]

TABLES = [('CCBUI登记表', 0x005704C8, 7), ('0x525540写的表', 0x005706CC, 7)]


def func_range(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea, f.end_ea) if f else (ea, ea + 0x800)


def scan_body(name, start):
    fs, fe = func_range(start)
    print('\n=== %s @ 0x%08x (体 0x%08x..0x%08x, %dB) ==='
          % (name, start, fs, fe, fe - fs))
    calls, vtbl_writes, max_disp = [], [], 0
    cur = fs
    n = 0
    while cur < fe and n < 4000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        mnem = idc.print_insn_mnem(cur)
        text = idc.generate_disasm_line(cur, 0)
        if mnem == 'call':
            t = idc.get_operand_value(cur, 0)
            calls.append((cur, t))
        # vtable 写: mov dword ptr [reg], imm32 大地址
        if mnem == 'mov' and text and 'offset' in text:
            for opn in (0, 1):
                if idc.get_operand_type(cur, opn) == 5:  # imm
                    v = idc.get_operand_value(cur, opn)
                    if 0x00500000 <= v <= 0x00600000 and '[e' in text:
                        vtbl_writes.append((cur, v, text))
        # 最大 disp: [reg+disp] / [disp]
        if text and '[e' in text:
            import re
            for mm in re.finditer(r'\+0?([0-9A-Fa-f]{3,6})h?\]', text):
                d = int(mm.group(1), 16)
                if d < 0x200000 and d > max_disp:
                    max_disp = d
            for mm in re.finditer(r'\[0([0-9A-Fa-f]{5,6})h?\]', text):
                d = int(mm.group(1), 16)
                if 0x400000 < d < 0x600000:
                    continue  # 绝对地址非 disp
                if d > max_disp:
                    max_disp = d
        cur += idc.get_item_size(cur)
        n += 1
    print('  最大 disp = 0x%X (%d)' % (max_disp, max_disp))
    print('  vtable 写入:')
    for a, v, t in vtbl_writes[:8]:
        print('    0x%08x  -> 0x%06X   %s' % (a, v, t))
    print('  call 目标 (%d):' % len(calls))
    for a, t in calls:
        f = ida_funcs.get_func(t)
        nm = idc.get_func_name(t) or '?'
        inrange = '(体内)' if f and f.start_ea == fs else ''
        print('    0x%08x -> 0x%08x %s %s' % (a, t, nm, inrange))
    return max_disp


print('== D1/D2: 三函数体扫描 ==')
for nm, ea in FUNCS:
    scan_body(nm, ea)

print('\n== D3: 交叉引用 ==')
for nm, ea in [('0x525540', 0x00525540), ('0x519360', 0x00519360),
               ('0x519380', 0x00519380), ('0x519310', 0x00519310)]:
    print(' XrefsTo 0x%08x:' % ea)
    for x in idautils.XrefsTo(ea):
        f = ida_funcs.get_func(x.frm)
        print('   from 0x%08x (%s)' % (x.frm, idc.get_func_name(f.start_ea) if f else '?'))

print('\n== D4: 双表字节 ==')
for nm, ta, n in TABLES:
    print(' %s @ 0x%08X:' % (nm, ta))
    for i in range(n):
        v = ida_bytes.get_dword(ta + i * 4)
        f = ida_funcs.get_func(v)
        print('   slot%-2d 0x%08X %s' % (i, v, idc.get_func_name(v) or ''))

print('\n== D5: 0x519xxx 簇(0x519310..0x51BA00)逐函数最大disp ==')
cur = 0x00519310
while cur < 0x0051BA00:
    f = ida_funcs.get_func(cur)
    if f and f.start_ea == cur:
        fs, fe = f.start_ea, f.end_ea
        max_disp = 0
        c = fs
        while c < fe:
            text = idc.generate_disasm_line(c, 0)
            if text and '[e' in text:
                import re
                for mm in re.finditer(r'\+0?([0-9A-Fa-f]{3,6})h?\]', text):
                    d = int(mm.group(1), 16)
                    if d < 0x200000 and d > max_disp:
                        max_disp = d
            c += idc.get_item_size(c)
        print('   0x%08x %-24s %dB  maxdisp=0x%X(%d)'
              % (fs, idc.get_func_name(fs), fe - fs, max_disp, max_disp))
        cur = fe
    else:
        cur += 4

idapro.close_database(False)
print('\n[probe] done')
