#!/usr/bin/env python3
"""[探针 2026-11-24 #10] UIGameFrm 内嵌仲裁 + Scene 槽 RoleSystem 假说。

A 案: g_UIListBoxDlg(0xDBA260)/g_UISceneMapDlg(0xDBAF10)/g_CCBEditorInst(0xDBB364)
      的初始化者取证——gamefrm ctor 内嵌构造(this=基址+off) vs 独立对象(CRT/独立 init)
      判据: 谁首次写这些地址; 初始化函数是否是 UIGameFrm 方法/全周初始化器
B 案: Scene 槽元素=RoleSystem 假说(0x2200 步距=sizeof(RoleSystem) 三方吻合)
      判据: ?X@RoleSystem@@ mangle 调用点中, ecx 来自槽派生链([reg+0xE0E4]/
      UISceneUpdate 返回值算术)的站点
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_uigamefrm_slots_20261124.py
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
import ida_name
import idautils
import ida_segment

OUT = []


def say(s):
    print(s)
    OUT.append(s)


def func_range(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea, f.end_ea) if f else (ea, ea + 0x400)


def func_name(ea):
    n = ida_name.get_name(ea)
    return (n if n else 'sub_%X' % ea)[:56]


ts = None
for seg_ea in idautils.Segments():
    sg = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(sg) == '.text':
        ts = sg
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
base = ts.start_ea

# ---------------- A 案: 三对象绑定全景 ----------------
say('========== A: UIGameFrm 内嵌三对象绑定全景 ==========')
for addr, nm in ((0xDBA260, 'g_UIListBoxDlg'), (0xDBAF10, 'g_UISceneMapDlg'),
                 (0xDBB364, 'g_CCBEditorInst')):
    pat = struct.pack('<I', addr)
    hits = []
    i = blob.find(pat)
    while i >= 0:
        head = ida_bytes.get_item_head(base + i)
        if head and ida_bytes.is_code(ida_bytes.get_flags(head)):
            hits.append(head)
        i = blob.find(pat, i + 1)
    forms = collections.Counter()
    for h in hits[:30]:
        t = (idc.generate_disasm_line(h, 0) or '').strip()
        f = ida_funcs.get_func(h)
        fs = f.start_ea if f else h
        # 归一形态: 助记 + 寄存器槽位; 保留 call/jmp 目标类名
        key = re.sub(r'0x?[0-9A-Fa-f]+h?\b', '#', t)
        m = re.match(r'(call|jmp)\s+([^;\s]+)', t)
        if m:
            key = '%s -> %s' % (m.group(1), m.group(2)[:40])
        forms[(key, func_name(fs))] += 1
    say('%s (0x%X): %d 代码引用' % (nm, addr, len(hits)))
    for (key, host), c in forms.most_common(8):
        say('   x%d [%s] %s' % (c, host, key[:80]))
    say('')

# gamefrm ctor 嫌疑: 谁是 0xDB9FD0(g_gamefrm) 的接收者
say('--- g_gamefrm(0xDB9FD0) 接收者 ---')
pat = b'\xb9' + struct.pack('<I', 0xDB9FD0)
i = blob.find(pat)
gfrm_sites = []
while i >= 0:
    if ida_bytes.is_code(ida_bytes.get_flags(base + i)):
        gfrm_sites.append(base + i)
    i = blob.find(pat, i + 1)
say('mov ecx, 0xDB9FD0 站点: %d' % len(gfrm_sites))
tgts = collections.Counter()
for ea in gfrm_sites:
    cur = ea
    for k in range(8):
        cur = idc.next_head(cur, cur + 64)
        if cur == idc.BADADDR:
            break
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        if re.match(r'mov\s+ecx\s*,', t):
            break
        m = re.match(r'(call|jmp)\s+([^;\s]+)', t)
        if m:
            f = ida_funcs.get_func(ea)
            tgts[(m.group(2)[:44], func_name(f.start_ea if f else ea))] += 1
            break
for (tok, host), c in tgts.most_common(10):
    say('   x%d [%s] %s' % (c, host, tok))

# ---------------- B 案: Scene 槽 RoleSystem 假说 ----------------
say('\n========== B: RoleSystem mangle 调用的 ecx 来源普查 ==========')
# 收集全部 ?X@RoleSystem@@ 调用点, 检查 ecx 链中是否出现 +E0E4/+2200 算术
rs_calls = []
i = blob.find(b'\xe8')  # call rel32 太泛; 改: 全函数扫 call 目标名
for ea in idautils.Functions():
    fs, fe = func_range(ea)
    cur = fs
    n = 0
    while cur < fe and n < 4000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        m = re.match(r'call\s+(\S+)', t)
        if m and '@RoleSystem@@' in m.group(1):
            rs_calls.append((cur, m.group(1), ea))
        cur = idc.next_head(cur, fe)
        n += 1
say('RoleSystem mangle 调用点: %d' % len(rs_calls))

slot_derived = 0
for site, tok, host in rs_calls:
    # 回溯 12 条: ecx 链(任意寄存器)是否涉及 0xE0E4 立即数 或 UISceneUpdate 返回
    cur = site
    ctx = []
    for k in range(12):
        prev = idc.prev_head(cur, func_range(host)[0])
        if prev == idc.BADADDR:
            break
        cur = prev
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        ctx.append(t)
        if 'E0E4' in t.upper() or 'UISceneUpdate' in t:
            slot_derived += 1
            f = ida_funcs.get_func(site)
            say('SLOT-DERIVED %s @ %s+0x%X: %s' % (
                tok[:40], func_name(f.start_ea if f else site),
                site - (f.start_ea if f else site),
                ' | '.join(ctx[-3:])[:100]))
            break
say('槽派生 RoleSystem 调用: %d / %d' % (slot_derived, len(rs_calls)))

# 对照: UISceneUpdate 返回指针的方法调用(已知场景方法)里 +0xE0E4 槽数组的走查方式
say('\n--- UISceneUpdate 返回值的槽走查上下文(0xE0E4 基址算术全景) ---')
pat2 = struct.pack('<I', 0xE0E4)
i = blob.find(pat2)
hits2 = []
while i >= 0:
    head = ida_bytes.get_item_head(base + i)
    if head and ida_bytes.is_code(ida_bytes.get_flags(head)):
        hits2.append(head)
    i = blob.find(pat2, i + 1)
say('+0xE0E4 立即数站点: %d' % len(hits2))
for h in hits2[:10]:
    f = ida_funcs.get_func(h)
    fs = f.start_ea if f else h
    say('   [%s] %s' % (func_name(fs), (idc.generate_disasm_line(h, 0) or '').strip()[:70]))

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_uigamefrm_slots_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe10] saved')
idapro.close_database(False)
