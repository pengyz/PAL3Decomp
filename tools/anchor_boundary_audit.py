#!/usr/bin/env python3
"""[审计工具 20261124] 锚边界三查法——真尾界方法论落地(可复用, 非过程脚本)。

来源: SceneMgr(捏造实锤)/CEffMgr(尾结构闭合)/ScriptSystemData(真尾界 0x1020)
三案裁决的方法论沉淀, 用户指令"方法论落地"。

三查(单遍 .text 扫描 + 语料计数):
  查一(放置证据, 最高优先): `mov ecx, imm32` 且 imm ∈ [base, base+binary_size)
      且下一条 jmp/call 目标 mangle 类名 ≠ 本类 → **外来对象绑定** = 超界实锤
      (链接器放置互斥: 真类分配不可能含独立对象; 编译器 mangle = A 级证据)
  查二(接收者上界): `mov ecx, imm32(=base)` 接收点 → call 目标方法体
      this-form [ecx+disp] 全集 → max disp, 与 binary_size 对账
      (远小于 size 不必然超界——数组经计算指针访问; 远超 size = 结构性矛盾)
  查三(语料偏好): 声称域内双名地址(globals.json 条目 ∩ struct known_members)
      的语料引用形态: 裸全局名 vs `Base.member` 限定形 → 对称裁决输入
      (0x908 案例: 裸形 12 refs → 成员删全局留; 0x8D4 案例: 成员形 → 全局名删)

输出: data/status/anchor_boundary_audit.json + stdout 摘要
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/anchor_boundary_audit.py
      [--class CEffMgr]  (单类调试)
"""
import sys
import re
import json
import struct
import collections
import os

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idc
import ida_bytes
import ida_funcs
import ida_name
import ida_segment
import idautils

REPO = '/home/peng/workspace/PAL3Decomp'
OUT = []


def say(s):
    print(s)
    OUT.append(s)


def func_range(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea, f.end_ea) if f else (ea, ea + 0x400)


def func_name(ea):
    n = ida_name.get_name(ea)
    return (n if n else 'sub_%X' % ea)[:50]


# ---------------- 载入锚清单 ----------------
ONLY = None
for i, a in enumerate(sys.argv):
    if a == '--class':
        ONLY = sys.argv[i + 1]

gj = json.load(open(os.path.join(REPO, 'data/annotations/globals.json')))
anchors = {}
for k, e in gj.items():
    if not isinstance(e, dict):
        continue
    t = str(e.get('type', '')).strip()
    if not t or t.endswith('*') or '[' in t:
        continue
    sp = os.path.join(REPO, 'data/annotations/structs', '%s.json' % t)
    if not os.path.exists(sp):
        continue
    try:
        sj = json.load(open(sp))
    except Exception:
        continue
    if ONLY and t != ONLY:
        continue
    try:
        base = int(k, 16)
    except Exception:
        continue
    bs = sj.get('binary_size') or 0
    if bs <= 0 or bs > 0x100000:
        continue
    anchors.setdefault(t, {
        'name': t, 'base': base, 'size': bs,
        'members': sj.get('known_members', {}) or {},
        'members_note': str(sj.get('members_note', ''))[:80],
    })
say('锚清单: %d 个 struct-anchored globals' % len(anchors))

# ---------------- 单遍 .text 扫描: mov ecx, imm32 ----------------
ts = None
for seg_ea in idautils.Segments():
    sg = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(sg) == '.text':
        ts = sg
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
tbase = ts.start_ea

sites = []  # (ea, imm)
i = blob.find(b'\xb9')
n_scan = 0
while i >= 0 and len(blob) - i >= 5:
    imm = struct.unpack('<I', blob[i + 1:i + 5])[0]
    if 0x400000 <= imm <= 0xE00000:
        ea = tbase + i
        if ida_bytes.is_code(ida_bytes.get_flags(ea)):
            sites.append((ea, imm))
            n_scan += 1
    i = blob.find(b'\xb9', i + 1)
say('.text mov ecx,imm32 站点: %d' % n_scan)

# ---------------- 查一 + 查二归类 ----------------
MANGLE_RE = re.compile(r'\?\??(\w+)@(\w+)@@')


def mangle_class(name):
    m = MANGLE_RE.match(name)
    return m.group(2) if m else None



def find_call_after(ea):
    """站点后前向扫 8 条, 返回第一个 call/jmp 目标 token(遇 mov ecx 重载即停)."""
    cur = ea
    for _ in range(8):
        cur = idc.next_head(cur, cur + 64)
        if cur == idc.BADADDR:
            return None
        text = (idc.generate_disasm_line(cur, 0) or '').strip()
        if re.match(r'mov\s+ecx\s*,', text):
            return None
        m = re.match(r'(call|jmp)\s+([^;\s]+)', text)
        if m:
            return m.group(2)
    return None

foreign = collections.defaultdict(list)   # anchor -> [(imm, ea, tgt_name, tgt_class)]
embedded = collections.defaultdict(list)  # anchor -> [(imm, cls)] 合法内嵌
recv = collections.defaultdict(list)      # anchor -> [(ea, call_tgt)]
recv_addrs = set(a['base'] for a in anchors.values())

for ea, imm in sites:
    hit_anchor = None
    for t, a in anchors.items():
        if a['base'] <= imm < a['base'] + a['size']:
            hit_anchor = a
            break
    if hit_anchor is None:
        continue
    tgt_tok = find_call_after(ea)
    if not tgt_tok:
        continue
    tgt_name = None
    if tgt_tok.startswith('sub_') or re.match(r'^[0-9A-Fa-f]+$', tgt_tok.rstrip('h')):
        try:
            ta = int(tgt_tok.rstrip('h'), 16)
            tgt_name = ida_name.get_name(ta) or ''
        except Exception:
            tgt_name = ''
    else:
        tgt_name = tgt_tok
    cls = mangle_class(tgt_name or '')
    if cls and cls != hit_anchor['name']:
        # 内嵌子对象白名单: offset 落在类型==cls 的成员(或其数组元素)上 → 合法内嵌 thiscall
        off = imm - hit_anchor['base']
        legit = False
        for mk, mv in hit_anchor['members'].items():
            try:
                mo = int(mk, 16)
            except Exception:
                continue
            mt = str(mv.get('type', ''))
            base_t = mt.split('[')[0].strip()
            if base_t == cls:
                arr = re.search(r'\[(\d+)\]$', mt)
                if arr:
                    esp = os.path.join(REPO, 'data/annotations/structs', '%s.json' % cls)
                    esz = 0
                    try:
                        esz = json.load(open(esp)).get('binary_size') or 0
                    except Exception:
                        pass
                    if esz and mo <= off < mo + int(arr.group(1)) * esz:
                        legit = True
                        break
                elif mo <= off < mo + 0x400:  # 单对象: 粗界 1K
                    legit = True
                    break
        if legit:
            embedded[hit_anchor['name']].append((imm, cls))
        else:
            foreign[hit_anchor['name']].append((imm, ea, tgt_name, cls))
    elif imm == hit_anchor['base']:
        recv[hit_anchor['name']].append((ea, tgt_name or tgt_tok))

# ---------------- 查二: 方法体 this-form disp ----------------
def this_disp_max(fstart):
    fs, fe = func_range(fstart)
    got = 0
    cur = fs
    n = 0
    while cur < fe and n < 6000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        text = idc.generate_disasm_line(cur, 0) or ''
        parts = text.split(None, 1)
        mnem = parts[0].lower() if parts else ''
        rest = parts[1] if len(parts) > 1 else ''
        if mnem == 'mov' and re.match(r'\s*ecx\s*,', rest):
            rhs = rest.split(',', 1)[1] if ',' in rest else ''
            if not re.search(r',\s*(eax|ebx|edx|esi|edi|ebp|esp)\s*$', rhs):
                break
        if mnem in ('call', 'jmp', 'ret', 'retn'):
            break
        m = re.search(r'\[ecx\+([0-9A-Fa-f]+)h?\]', rest)
        if m:
            d = int(m.group(1).rstrip('h'), 16)
            if d > got:
                got = d
        cur = idc.next_head(cur, fe)
        n += 1
    return got


report = {}
for t, a in sorted(anchors.items()):
    row = {
        'base': '0x%08x' % a['base'], 'claimed_size': a['size'],
        'claimed_end': a['base'] + a['size'],
        'receivers': len(recv.get(t, [])),
        'embedded_calls': len(embedded.get(t, [])),
        'foreign_bindings': [],
        'method_extent_max': 0,
        'verdict': [],
    }
    # 查一
    fb = foreign.get(t, [])
    seen = set()
    for imm, ea, tgt_name, cls in fb:
        key = (imm, cls)
        if key in seen:
            continue
        seen.add(key)
        row['foreign_bindings'].append({
            'imm': '0x%08x' % imm, 'offset': imm - a['base'],
            'target': tgt_name[:60], 'class': cls,
        })
    if row['foreign_bindings']:
        row['verdict'].append(
            'PLACEMENT-CONFLICT: %d 外来类绑定(%s) → 超界嫌疑'
            % (len(row['foreign_bindings']),
               ','.join(sorted(set(f['class'] for f in row['foreign_bindings']))[:4])))
    # 查二 (取接收点 call 目标去重, 最多 12 方法)
    methods = []
    seen_t = set()
    for ea, tgt_tok in recv.get(t, [])[:24]:
        try:
            ta = int(tgt_tok.lstrip('?').split('@')[0], 16) if re.match(
                r'^[0-9A-Fa-f]+$', tgt_tok.lstrip('?').split('@')[0]) else None
        except Exception:
            ta = None
        tok = find_call_after(ea)
        ta = None
        if tok:
            if re.match(r'^[0-9A-Fa-f]+h?$', tok):
                ta = int(tok.rstrip('h'), 16)
            else:
                ea2 = idc.get_name_ea_simple(tok)
                if ea2 and ea2 != idc.BADADDR:
                    ta = ea2
        if ta and ta not in seen_t and ta != a['base']:
            seen_t.add(ta)
            tnm = ida_name.get_name(ta) or ''
            tcls = mangle_class(tnm)
            if tcls == a['name']:
                methods.append(ta)
                continue
            # 无名 callee: thiscall 序言形状守卫(前 12 条内 mov eX,ecx/[ecx...] 先于 call)
            tfs, tfe = func_range(ta)
            cur2 = tfs
            shaped = False
            for _ in range(12):
                if cur2 >= tfe or not ida_bytes.is_code(ida_bytes.get_flags(cur2)):
                    break
                tx = (idc.generate_disasm_line(cur2, 0) or '').strip()
                if re.match(r'(call|jmp)', tx):
                    break
                if re.search(r'mov\s+e[a-z]{2}\s*,\s*ecx', tx) or '[ecx' in tx:
                    shaped = True
                    break
                cur2 = idc.next_head(cur2, tfe)
            if shaped:
                methods.append(ta)
    mx = 0
    for ta in methods[:12]:
        d = this_disp_max(ta)
        if d > mx:
            mx = d
    row['method_extent_max'] = mx
    row['methods_scanned'] = len(methods[:12])
    if mx:
        if mx > a['size']:
            row['verdict'].append(
                'EXTENT-OVERFLOW: this-form max disp 0x%X > binary_size 0x%X' % (mx, a['size']))
        elif mx < a['size'] // 2:
            row['verdict'].append(
                'EXTENT-GAP: this-form max disp 0x%X << binary_size 0x%X (数组计算指针访问或超界, 待查三)'
                % (mx, a['size']))
        else:
            row['verdict'].append(
                'EXTENT-OK: max disp 0x%X ≈ binary_size 0x%X' % (mx, a['size']))
    if not row['verdict']:
        if row['receivers']:
            row['verdict'].append('CLEAN: 无外来绑定, 接收者 %d' % row['receivers'])
        else:
            row['verdict'].append('NO-RECEIVER: 无 thiscall 接收点(纯静态访问或捏造嫌疑, 需查三/动态初始化取证)')
    report[t] = row

# ---------------- 查三: 语料偏好(双名地址) ----------------
say('\n查三: 语料偏好计数...')
corpus_text = []
cdir = os.path.join(REPO, 'pal3', 'src')
for dirpath, _, files in os.walk(cdir):
    for f in files:
        if f.endswith(('.cpp', '.h')):
            try:
                corpus_text.append(open(os.path.join(dirpath, f), encoding='utf-8',
                                        errors='replace').read())
            except Exception:
                pass
corpus_all = '\n'.join(corpus_text)
# body-only 语料(排除 globals.h/cpp 定义)
_body_texts = []
for dirpath, _, files in os.walk(cdir):
    for f in files:
        if f.endswith(('.cpp', '.h')) and f not in ('globals.cpp', 'globals.h'):
            try:
                _body_texts.append(open(os.path.join(dirpath, f), encoding='utf-8',
                                        errors='replace').read())
            except Exception:
                pass
corpus_body = '\n'.join(_body_texts)


def count_pat(pat, text=None):
    return len(re.findall(pat, text if text is not None else corpus_all))


# 每锚实例名集 = 锚类名 + 全部 type==锚 的 globals 名
def instance_names(cls, base_addr):
    names = {cls}
    for k, e in gj.items():
        if isinstance(e, dict) and str(e.get('type', '')).strip() == cls:
            n = str(e.get('name', ''))
            if n:
                names.add(n)
    return names


for t, a in sorted(anchors.items()):
    row = report[t]
    duals = []
    for k, v in a['members'].items():
        try:
            off = int(k, 16)
        except Exception:
            continue
        addr = a['base'] + off
        kk = '0x%08x' % addr
        ge = gj.get(kk)
        if not isinstance(ge, dict):
            continue
        gname = str(ge.get('name', ''))
        mname = str(v.get('name', ''))
        gtype = str(ge.get('type', '')).strip()
        if not gname or not mname or gname == mname:
            continue
        # 同型实例假双名排除: global 条目 type == 锚类 → 实例名 vs 成员, 非竞争身份
        if gtype == t:
            continue
        insts = instance_names(t, a['base'])
        inst_pat = '|'.join(re.escape(n) for n in sorted(insts))
        # 全局形: 裸名 body 引用(排除定义文件)
        gp = count_pat(r'(?<![\w.])%s\b(?!\s*\.)' % re.escape(gname), corpus_body)
        # 成员形: 限定形 + 实例形 + 箭头形(->member, 指针解引用活引用)
        mp = count_pat(r'(?:%s)\.%s\b' % (inst_pat, re.escape(mname)))
        mp += count_pat(r'->\s*%s\b' % re.escape(mname))
        if gp or mp:
            duals.append({
                'addr': kk, 'offset': '0x%X' % off,
                'global': gname, 'member': mname,
                'global_form': gp, 'member_form': mp,
                'pref': 'GLOBAL' if gp > mp else ('MEMBER' if mp > gp else 'TIE'),
            })
    duals.sort(key=lambda d: -(d['global_form'] + d['member_form']))
    row['dual_names'] = duals[:12]
    row['dual_names_total'] = len(duals)
    if duals:
        mixed = sum(1 for d in duals if d['pref'] == 'GLOBAL')
        row['verdict'].append(
            'DUAL-NAMES: %d 双名地址(%d 裸全局形胜出) → 对称裁决待执行' % (
                len(duals), mixed))

# ---------------- 输出 ----------------
say('\n========== 锚边界审计报告 ==========')
conf = [t for t, r in report.items() if any('PLACEMENT-CONFLICT' in v for v in r['verdict'])]
norecv = [t for t, r in report.items() if any('NO-RECEIVER' in v for v in r['verdict'])]
gap = [t for t, r in report.items() if any('EXTENT-GAP' in v for v in r['verdict'])]
dual = [t for t, r in report.items() if r.get('dual_names')]
say('PLACEMENT-CONFLICT(超界实锤嫌疑): %d → %s' % (len(conf), conf[:15]))
say('NO-RECEIVER(纯静态/捏造嫌疑): %d → %s' % (len(norecv), norecv[:15]))
say('EXTENT-GAP(域缺口待查): %d → %s' % (len(gap), gap[:10]))
say('DUAL-NAMES(对称裁决待执行): %d → %s' % (len(dual), dual[:12]))

with open(os.path.join(REPO, 'data/status/anchor_boundary_audit.json'), 'w',
          encoding='utf-8') as f:
    json.dump({'generated': '2026-11-24', 'anchors': report}, f,
              ensure_ascii=False, indent=1)
with open(os.path.join(REPO, 'pipeline/ida/anchor_boundary_audit_out.txt'), 'w',
          encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[audit] report -> data/status/anchor_boundary_audit.json')
idapro.close_database(False)
