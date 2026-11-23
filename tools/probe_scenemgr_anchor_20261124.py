#!/usr/bin/env python3
"""[探针 2026-11-24] P0a SceneMgr 锚边界终审——binary_size 58692 vs docs 54116 矛盾。

矛盾:
  annotation binary_size = 0xE544 (58692) → 尾界 0xC1D284
  docs/scenemgr_layout.md = 0xD364 (54116) → 尾界 0xC116F4
  两界内部都有独立 anchor_object(g_palScript/g_UIManager/g_RoleSystemInstance...)
  m_nRoleCount@+0xE0E0 绝对地址 0xC12470 疑似落入 g_UIManager@0xC11758 范围

决定性判据:
  D1a 字节扫 B9 90 43 C0 (mov ecx,0xC04390) → 接收点; call 目标 = SceneMgr 方法集
  D1b 方法集体内 [ecx+disp] 扫描 → 每方法 max disp → 类真实成员域上界
  D1c 字节扫 E0E00000 → 全部触达偏移 0xE0E0 的指令及宿主函数
  D2  CRT init 表 → SceneMgr ctor 及其初始化写域
  D3  XrefsTo(0xC12470) 绝对引用全景
  D4  尾界区 [0xC116F4, 0xC1D284) IDA 命名条目全景(独立对象证据)

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_scenemgr_anchor_20261124.py
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
print('[probe] db opened:', db)

import idc
import ida_bytes
import ida_funcs
import ida_segment
import ida_name
import idautils

G_SCENEMGR = 0x00C04390
M_NROLECOUNT_ABS = G_SCENEMGR + 0xE0E0   # 0xC12470
DOCS_END = G_SCENEMGR + 0xD364           # 0xC116F4
ANN_END = G_SCENEMGR + 0xE544            # 0xC1D284

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


def text_seg():
    for seg_ea in idautils.Segments():
        s = ida_segment.getseg(seg_ea)
        if ida_segment.get_segm_name(s) == '.text':
            return s
    return None


# ---------------------------------------------------------------- D1a
say('\n========== D1a: mov ecx, 0xC04390 字节扫 → 方法集 ==========')
ts = text_seg()
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
base = ts.start_ea
recv_bytes = []
pat = struct.pack('<I', G_SCENEMGR)
i = blob.find(b'\xb9' + pat)           # mov ecx, imm32
while i >= 0:
    recv_bytes.append(base + i)
    i = blob.find(b'\xb9' + pat, i + 1)
say('mov ecx, 0xC04390 站点: %d' % len(recv_bytes))

method_set = collections.Counter()
for ea in recv_bytes:
    cur = idc.next_head(ea, ea + 32)
    text = idc.generate_disasm_line(cur, 0) or ''
    m = re.match(r'\s*call\s+([0-9A-Fa-f_]+)', text)
    if m:
        tgt = int(m.group(1), 16)
        method_set[tgt] += 1
    else:
        # 非紧跟 call: 记录原始行(可能是 lea/mov 转存)
        method_set[-1] += 1
say('紧跟 call 的目标数: %d (去重); 非直呼形态: %d' % (
    len([k for k in method_set if k > 0]), method_set.get(-1, 0)))
for tgt, cnt in method_set.most_common():
    if tgt > 0:
        say('  method %s (0x%X) x%d' % (func_name(tgt), tgt, cnt))

# ---------------------------------------------------------------- D1b
say('\n========== D1b: 方法集体内 [ecx+disp] 扫描 ==========')


def scan_this_disp(fstart):
    """函数体内 ecx 重载前的 [ecx+disp] 全集."""
    fs, fe = func_range(fstart)
    got = []
    cur = fs
    n = 0
    while cur < fe and n < 6000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        text = idc.generate_disasm_line(cur, 0) or ''
        mnem = text.split()[0] if text.split() else ''
        # ecx 重载 → 之后 ecx 不再是 ctor 期 this
        if mnem == 'mov' and re.match(r'\s*ecx\s*,', text[len(mnem):]):
            # mov ecx, X: X 为寄存器或非 0xC04390 立即数即重载
            rhs = text.split(',', 1)[1] if ',' in text else ''
            if '0xC04390' not in rhs and not re.search(
                    r',\s*(eax|ebx|edx|esi|edi|ebp|esp)', rhs):
                break
        if mnem in ('call', 'jmp'):
            break
        m = re.search(r'\[ecx\+([0-9A-Fa-f]+)h?\]', text)
        if m:
            got.append((int(m.group(1).rstrip('h'), 16), cur, text.strip()))
        elif re.search(r'\[ecx\]', text):
            got.append((0, cur, text.strip()))
        cur = idc.next_head(cur, fe)
        n += 1
    return got


per_method = {}
for tgt in [t for t in method_set if t > 0]:
    got = scan_this_disp(tgt)
    if got:
        mx = max(g[0] for g in got)
        per_method[tgt] = (mx, len(got), got)
all_max = sorted((v[0], t) for t, v in per_method.items() if v[0] > 0)
say('方法集 %d 个中有 [ecx+disp] 访问: %d' % (
    len([t for t in method_set if t > 0]), len(per_method)))
say('TOP-15 max disp:')
for mx, tgt in all_max[-15:]:
    say('  %s: max 0x%X (%d 站)' % (func_name(tgt), mx, per_method[tgt][1]))
docs_over = [(mx, t) for mx, t in all_max if mx >= 0xD364]
say('max disp >= 0xD364(docs 尾): %d 个方法' % len(docs_over))
say('max disp >= 0xE544(ann 尾): %d 个方法' % len(
    [1 for mx, _ in all_max if mx >= 0xE544]))
# 全类 disp 分布
alld = collections.Counter()
for tgt, (mx, n, got) in per_method.items():
    for d, ea, tx in got:
        alld[d] += 1
big = sorted(d for d in alld if d >= 0x4000)
say('全类 disp>=0x4000 清单: %s' % ['0x%X(x%d)' % (d, alld[d]) for d in big])

# ---------------------------------------------------------------- D1c
say('\n========== D1c: 偏移 0xE0E0 触达指令字节扫 ==========')
pat_e0e0 = struct.pack('<I', 0xE0E0)
hits = []
i = blob.find(pat_e0e0)
while i >= 0:
    # 指令起点: 向前找 item head
    ea = base + i
    head = ida_bytes.get_item_head(ea)
    if head and ida_bytes.is_code(ida_bytes.get_flags(head)):
        hits.append(head)
    i = blob.find(pat_e0e0, i + 1)
seen = set()
for h in hits:
    if h in seen:
        continue
    seen.add(h)
    f = ida_funcs.get_func(h)
    fs = f.start_ea if f else 0
    text = idc.generate_disasm_line(h, 0) or ''
    say('  %s+0x%X: %s' % (func_name(fs) if fs else '?',
                           h - fs if fs else 0, text.strip()))
say('0xE0E0 触达指令: %d 处 (%d 去重)' % (len(hits), len(seen)))

# ---------------------------------------------------------------- D2
say('\n========== D2: CRT init 表 → SceneMgr ctor ==========')
rdata = ida_segment.get_segm_by_name('.rdata')
cand_ctors = []
if rdata:
    rblob = ida_bytes.get_bytes(rdata.start_ea, rdata.end_ea - rdata.start_ea) or b''
    rbase = rdata.start_ea
    run = []
    for off in range(0, len(rblob) - 4, 4):
        v = struct.unpack('<I', rblob[off:off + 4])[0]
        f = ida_funcs.get_func(v) if v else None
        if f and f.start_ea == v and 0x401000 <= v < 0x5C0000:
            run.append((rbase + off, v))
        else:
            if len(run) >= 5:
                for tea, tv in run:
                    fs, fe = func_range(tv)
                    cur = fs
                    hit = 0
                    while cur < fe:
                        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
                            break
                        tx = idc.generate_disasm_line(cur, 0) or ''
                        if 'C04390' in tx:
                            hit += 1
                        cur = idc.next_head(cur, fe)
                    if hit:
                        cand_ctors.append((tea, tv, hit))
            run = []
say('CRT init 表中引用 0xC04390 的条目: %d' % len(cand_ctors))
for tea, tv, hit in cand_ctors:
    say('  init[0x%X] -> %s (0x%X) C04390 引用 x%d' % (tea, func_name(tv), tv, hit))
    # dump 该函数体内所有 C04390 相关行 + 紧邻写
    fs, fe = func_range(tv)
    cur = fs
    k = 0
    while cur < fe and k < 3000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        tx = idc.generate_disasm_line(cur, 0) or ''
        if 'C04390' in tx or ('stosd' in tx) or ('0xAA' in tx and 'mov' in tx):
            say('    +%#x: %s' % (cur - fs, tx.strip()))
        cur = idc.next_head(cur, fe)
        k += 1

# ---------------------------------------------------------------- D3
say('\n========== D3: XrefsTo(0xC12470) ==========')
n_ref = 0
for xref in idautils.XrefsTo(M_NROLECOUNT_ABS, 0):
    f = ida_funcs.get_func(xref.frm)
    fs = f.start_ea if f else xref.frm
    text = idc.generate_disasm_line(xref.frm, 0) or ''
    say('  %s+0x%X: %s' % (func_name(fs) if f else '?',
                           xref.frm - fs, text.strip()))
    n_ref += 1
say('绝对引用数: %d' % n_ref)
say('注: 0xC12470 - g_UIManager(0xC11758) = 0x%X' % (M_NROLECOUNT_ABS - 0xC11758))

# ---------------------------------------------------------------- D4
say('\n========== D4: 尾界区 [0xC116F4, 0xC1D284) IDA 命名条目 ==========')
ea = DOCS_END
named = 0
while ea < ANN_END:
    nm = ida_name.get_name(ea)
    if nm and not nm.startswith('dword_') and not nm.startswith('byte_') \
       and not nm.startswith('unk_') and not nm.startswith('word_'):
        flags = ida_bytes.get_flags(ea)
        kind = ('str' if ida_bytes.is_strlit(flags) else
                'data' if ida_bytes.is_data(flags) else
                'code' if ida_bytes.is_code(flags) else '?')
        say('  0x%08X %-42s %-4s (SceneMgr+%#x)' % (
            ea, nm[:42], kind, ea - G_SCENEMGR))
        named += 1
        sz = ida_bytes.get_item_size(ea)
        if sz > 4:
            ea += sz
            continue
    ea += 4
say('尾界区语义命名条目: %d' % named)

with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_scenemgr_anchor_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe] saved -> probe_scenemgr_anchor_out.txt')
idapro.close_database(False)
