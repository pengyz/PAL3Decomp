#!/usr/bin/env python3
"""probe_rolestatepanel_holes_20261126.py — RoleStatePanel 9 残洞独立重扫（R3 Task 3）。

背景: Task 2 落位后 struct_holes_20261125 census RoleStatePanel 残 9 洞 556B
      (16/252/16/128/16/16/16/80/16)；实现者初判均无 ctor 写无 disp 触场。
      门②要求逐洞独立重扫（idalib：全方法 disp 触场 + ctor 写序），
      有证据者落位（verified），零证据者诚实留洞。

独立性声明: 本脚本不从 probe_rolestatepanel_layout_20261126.json 读任何数据，
      全部证据从 original/PAL3.exe.i64 现扫重derive；方法集=RoleStatePanel.json
      methods + DB ?*RoleStatePanel* + vtable 0x56F040 七槽目标（含继承槽
      ShowClipped/Create — Task2 十八法集的超集）。

证据通道（逐洞）:
  A ctor 写序: InitUI@0x4a1e40 THIS-form 写序列（site+disp+width+序号）入洞判定
  B ctor 子对象构造对: lea ecx,[esi+d] + call 入洞判定（含 ??_L 数组 span / rep stosd span）
  C 全方法 disp 触场: THIS/SUBPTR/OTHER 三类 provenance（线性溯源），入洞逐条记录
     （含 THIS-form lea 地址形成触场单列）
  D dtor 拆解序: ~RoleStatePanel(0x4a2450/0x4a2150) THIS 写 + lea-call 对入洞判定
裁决: 通道 A/B/D 命中 或 C 的 THIS/SUBPTR 命中 → 有证据（落位候选）；
      仅 C-OTHER 命中 → 弱信号（不落位，记录形式留档）；全零 → 诚实留洞。

产出: data/status/probe_rolestatepanel_holes_20261126.json
"""
import sys, os, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

ROOT = '/home/peng/workspace/PAL3Decomp'
OUT = ROOT + '/data/status/probe_rolestatepanel_holes_20261126.json'
STRUCTS_DIR = ROOT + '/data/annotations/structs'
BAD = idc.BADADDR

ANN = json.load(open(STRUCTS_DIR + '/RoleStatePanel.json', encoding='utf-8'))
HOLES_FILE = json.load(open(ROOT + '/data/status/struct_holes_20261125.json',
                            encoding='utf-8'))

SIZE = ANN['binary_size']            # 0x2B080
VT = 0x56F040                        # RoleStatePanel vtable
CTOR_EA = 0x4A1E40                   # InitUI (ctor 体)
DTOR_EA = 0x4A2450
DTOR_DELETING_EA = 0x4A2150

census_row = None
for c in HOLES_FILE.get('classes', []):
    if c.get('cls') == 'RoleStatePanel':
        census_row = c
assert census_row, 'RoleStatePanel row missing in struct_holes_20261125.json'
HOLES = [(int(lo, 16), int(hi, 16), nb) for lo, hi, nb in census_row['holes']]

def clean(ea):
    return (idc.generate_disasm_line(ea, 0) or '').split(';')[0].strip()

def body_lines(ea, limit=40000):
    f = ida_funcs.get_func(ea)
    if not f:
        return []
    out, cur, n = [], f.start_ea, 0
    while cur < f.end_ea and n < limit:
        out.append((cur, clean(cur)))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    return out

def is_fn_ea(v):
    if v is None or v == BAD:
        return False
    f = ida_funcs.get_func(v)
    return f is not None and f.start_ea == v

def fname(ea):
    f = ida_funcs.get_func(ea)
    return idc.get_func_name(f.start_ea) if f else '?'

# ---------------- provenance 溯源（线性，本实现独立重写） ----------------
class Prov:
    def __init__(self):
        self.this_regs = {'ecx'}
        self.sub_regs = set()
    def feed(self, t):
        m = re.match(r'^mov\s+(e[a-z]{2}),\s*(e[a-z]{2}|cx|ecx)$', t)
        if m:
            if m.group(2) in ('ecx', 'cx') or m.group(2) in self.this_regs:
                self.this_regs.add(m.group(1))
            return
        m = re.match(r'^mov\s+(e[a-z]{2}),\s*(?:dword ptr\s+)?\[(e[a-z]{2})\]'
                     r'(?:\+([0-9A-Fa-f]{1,8})h?)?$', t)
        if m and m.group(2) in self.this_regs:
            self.sub_regs.add(m.group(1))
    def cls(self, reg):
        if reg in self.this_regs:
            return 'THIS'
        if reg in self.sub_regs:
            return 'SUBPTR'
        return 'OTHER'

WIDTH_RE = re.compile(r'(byte|word|dword)\s+ptr')
R8 = re.compile(r'^[a-d][lh]$')
R16 = re.compile(r'^[a-d]x$|^[sd]i$|^bp$')

def access_width(t):
    m = WIDTH_RE.search(t)
    if m:
        return {'byte': 1, 'word': 2, 'dword': 4}[m.group(1)]
    # mov/cmp/test al, [..] / mov [..], bl 等: 由寄存器操作数推断
    for tok in re.findall(r'\b(e?[a-d][lh]|[a-d]x|[sd]i|bp|e[a-z]{2})\b', t):
        if R8.match(tok):
            return 1
        if R16.match(tok):
            return 2
    return 4

DISP_RE = re.compile(r'\[(e[a-z]{2})\+(?:([0-9A-Fa-f]{1,8})h?)?\]')
LEA_THIS_RE = re.compile(r'^lea\s+(e[a-z]{2}),\s*\[(e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]')

# ---------------- 方法集（超集：十八法 + vtable 七槽目标） ----------------
method_addrs = {}
for k, m in ANN['methods'].items():
    ea = int(k, 16)
    if is_fn_ea(ea):
        method_addrs[ea] = str(m.get('name') or k)
slot_targets = []
for i in range(7):
    tgt = idc.get_wide_dword(VT + 4 * i)
    slot_targets.append(hex(tgt))
    if is_fn_ea(tgt) and tgt not in method_addrs:
        method_addrs[tgt] = 'vtable_slot%d@%s' % (i, hex(tgt))
for ea, nm in idautils.Names():
    if ('RoleStatePanel' in nm and nm.startswith('?') and is_fn_ea(ea)
            and ea not in method_addrs):
        method_addrs[ea] = nm

method_set_meta = {
    'n_methods': len(method_addrs),
    'methods': sorted('%s=%s' % (hex(a), n) for a, n in method_addrs.items()),
    'vtable_slot_targets': slot_targets,
    'superset_note': 'Task2 十八法集 + vtable 继承槽 ShowClipped(0x445e70)/'
                     'Create(0x445b90)（若未已在集内）',
}

# ---------------- 通道 C: 全方法 disp 触场 ----------------
disp_touch = []          # {'disp','cls','method','site','form','width'}
lea_this = []            # THIS-form lea 地址形成
for ea, mname in sorted(method_addrs.items()):
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    prov = Prov()
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 25000:
        t = clean(cur)
        prov.feed(t)
        if t.startswith('lea'):
            lm = LEA_THIS_RE.match(t)
            if lm and lm.group(2) in prov.this_regs:
                d = int(lm.group(3), 16)
                if 0 <= d < SIZE:
                    lea_this.append({'disp': hex(d), 'method': mname,
                                     'site': hex(cur), 'form': t[:90]})
        for bm in DISP_RE.finditer(t):
            reg, dhex = bm.group(1), bm.group(2)
            d = int(dhex, 16) if dhex else 0
            if 0 <= d < SIZE:
                disp_touch.append({'disp': hex(d), 'cls': prov.cls(reg),
                                   'method': mname, 'site': hex(cur),
                                   'form': t[:90], 'width': access_width(t)})
        cur = idc.next_head(cur, f.end_ea)
        n += 1

# ---------------- 通道 A/B: ctor 写序 + 子对象构造对 ----------------
def decode_ctor_dtor(ea, label):
    out = {'ea': hex(ea), 'label': label,
           'this_writes': [], 'call_pairs': [], 'array_spans': [],
           'stosd_spans': []}
    if not is_fn_ea(ea):
        out['missing'] = True
        return out
    body = body_lines(ea)
    prov = Prov()
    ecx_state = None
    pending = []
    regmodel = {}
    recent = []
    IMM_RE = re.compile(r'^push\s+((?:[0-9A-Fa-f]+)h|[0-9]+)$')
    LEA_ECX = re.compile(r'^lea\s+ecx,\s*\[esi(?:\+([0-9A-Fa-f]+)h?)?\]$/i'.replace('/i', ''))
    for idx, (a, t) in enumerate(body):
        recent.append((a, t))
        recent = recent[-8:]
        prov.feed(t)
        lm = re.match(r'^lea\s+ecx,\s*\[esi(?:\+([0-9A-Fa-f]+)h?)?\]$', t)
        if lm:
            ecx_state = int(lm.group(1), 16) if lm.group(1) else 0
        if t.startswith('rep stosd'):
            edi = None
            ecx = None
            for sa, st in body[max(0, idx - 6):idx]:
                em = re.match(r'^lea\s+edi,\s*\[esi(?:\+([0-9A-Fa-f]+)h?)?\]$', st)
                if em:
                    edi = int(em.group(1), 16) if em.group(1) else 0
                cm2 = re.match(r'^mov\s+ecx,\s*([0-9A-Fa-f]+)h$', st)
                if cm2:
                    ecx = int(cm2.group(1), 16)
                am = re.match(r'^add\s+edi,\s*([0-9A-Fa-f]+)h$', st)
                if am and edi is not None:
                    edi += int(am.group(1), 16)
            if edi is not None and ecx:
                out['stosd_spans'].append(
                    {'span': [hex(edi), hex(edi + 4 * ecx)], 'count': ecx,
                     'site': hex(a)})
            continue
        if t.startswith('call'):
            cm = re.match(r'^call\s+(\S+)', t)
            tgt_tok = cm.group(1) if cm else ''
            tgt = idc.get_name_ea_simple(tgt_tok.strip())
            pair = {'site': hex(a), 'target': tgt_tok[:80],
                    'target_ea': hex(tgt) if tgt != BAD and tgt is not None else None,
                    'this_disp': hex(ecx_state) if ecx_state is not None else None,
                    'window': [{'site': hex(x[0]), 'form': x[1]}
                               for x in recent[:-1]]}
            if len(pending) >= 5:
                d5 = pending[-5:]
                if (d5[0][0] == 'fn' and d5[1][0] == 'fn' and d5[2][0] == 'imm'
                        and d5[3][0] == 'imm' and d5[4][0] in ('ptr', 'imm')):
                    disp, count, size = d5[4][1], d5[2][1], d5[3][1]
                    pair['eh_helper_array'] = {
                        'offset': hex(disp), 'count': count, 'stride': size,
                        'span': [hex(disp), hex(disp + size * count)],
                        'ctor': d5[1][2][:60], 'dtor': d5[0][2][:60]}
                    out['array_spans'].append(pair['eh_helper_array'])
            out['call_pairs'].append(pair)
            ecx_state = None
            pending, regmodel = [], {}
            recent = []
            continue
        m = IMM_RE.match(t)
        if m:
            tok = m.group(1)
            v = int(tok[:-1], 16) if tok.endswith('h') else int(tok)
            if is_fn_ea(v):
                pending.append(('fn', v, idc.get_name(v) or 'sub_%X' % v))
            else:
                pending.append(('imm', v))
            continue
        m = re.match(r'^push\s+offset\s+(\S+)$', t)
        if m:
            v = idc.get_name_ea_simple(m.group(1))
            pending.append(('fn', v if v != BAD else None, m.group(1)))
            continue
        m = re.match(r'^lea\s+(e[a-z]{2}),\s*\[(e[a-z]{2})\+([0-9A-Fa-f]+)h?\]$', t)
        if m:
            regmodel[m.group(1)] = int(m.group(3), 16)
            continue
        m = re.match(r'^push\s+(e[a-z]{2})$', t)
        if m:
            r = m.group(1)
            pending.append(('ptr', regmodel[r]) if r in regmodel else ('reg', r))
            continue
        md = re.match(r'^(?:mov|xor|add|sub|and|or|pop|inc|dec|neg|not)\s+(e[a-z]{2})\b', t)
        if md:
            regmodel.pop(md.group(1), None)
            if md.group(1) == 'ecx':
                ecx_state = None
            continue
        if t.startswith('pop ') or t.startswith('add esp') or t.startswith('mov esp'):
            pending = []
            continue
        wm = re.match(r'^mov\s+((?:(dword|word|byte)\s+ptr\s+)?)'
                      r'\[(e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]\s*,\s*(\S+)', t)
        if wm:
            reg, disp = wm.group(3), int(wm.group(4), 16)
            pfx, src = wm.group(2), wm.group(5)
            if pfx == 'byte':
                nb = 1
            elif pfx == 'word':
                nb = 2
            elif pfx == 'dword':
                nb = 4
            elif R8.match(src):
                nb = 1
            elif R16.match(src):
                nb = 2
            else:
                nb = 4
            out['this_writes'].append({'site': hex(a), 'disp': hex(disp),
                                       'bytes': nb, 'cls': prov.cls(reg),
                                       'form': t[:90],
                                       'order': len(out['this_writes'])})
    return out

ctor_dec = decode_ctor_dtor(CTOR_EA, 'InitUI(ctor)')
dtor_dec = decode_ctor_dtor(DTOR_EA, '~RoleStatePanel')
dtor_del_dec = decode_ctor_dtor(DTOR_DELETING_EA, '~RoleStatePanel(deleting)')

# ---------------- 逐洞裁决 ----------------
def in_range(rec, lo, hi, key='disp'):
    v = int(rec[key], 16)
    return lo <= v < hi

holes_out = []
for lo, hi, nb in HOLES:
    w = [x for x in ctor_dec['this_writes'] if lo <= int(x['disp'], 16) < hi]
    dw = [x for x in dtor_dec['this_writes'] if lo <= int(x['disp'], 16) < hi]
    cp = [x for x in ctor_dec['call_pairs']
          if x['this_disp'] and lo <= int(x['this_disp'], 16) < hi]
    dp = [x for x in dtor_dec['call_pairs']
          if x['this_disp'] and lo <= int(x['this_disp'], 16) < hi]
    arr = [x for x in ctor_dec['array_spans']
           if int(x['span'][0], 16) < hi and lo < int(x['span'][1], 16)]
    sto = [x for x in ctor_dec['stosd_spans']
           if int(x['span'][0], 16) < hi and lo < int(x['span'][1], 16)]
    dt = [x for x in disp_touch if lo <= int(x['disp'], 16) < hi]
    dt_this = [x for x in dt if x['cls'] in ('THIS', 'SUBPTR')]
    dt_other = [x for x in dt if x['cls'] == 'OTHER']
    lt = [x for x in lea_this if lo <= int(x['disp'], 16) < hi]
    channels = {
        'ctor_this_writes': w, 'ctor_write_order_in_hole':
            ['write#%d %s @%s %s' % (x['order'], x['disp'], x['site'], x['form'])
             for x in w],
        'ctor_subobject_pairs': cp, 'ctor_array_spans': arr,
        'ctor_stosd_spans': sto,
        'dtor_this_writes': dw, 'dtor_subobject_pairs': dp,
        'disp_this_subptr': dt_this, 'disp_other': dt_other,
        'lea_this_addr': lt,
    }
    strong = bool(w or dw or cp or dp or arr or sto or dt_this or lt)
    weak_other = bool(dt_other) and not strong
    verdict = ('evidence' if strong else
               'weak_other_only' if weak_other else 'zero_evidence')
    # nearest live disp context（诚实留洞的邻域坐标）
    keys = sorted(set(int(x['disp'], 16) for x in disp_touch))
    below = max((k for k in keys if k < lo), default=None)
    above = min((k for k in keys if k >= hi), default=None)
    holes_out.append({
        'range': [hex(lo), hex(hi)], 'bytes': nb,
        'channels': channels,
        'verdict': verdict,
        'nearest_disp_below': hex(below) if below is not None else None,
        'nearest_disp_above': hex(above) if above is not None else None,
    })

report = {
    'meta': {
        'tool': 'tools/probe_rolestatepanel_holes_20261126.py',
        'db': 'original/PAL3.exe.i64', 'run_auto_analysis': False,
        'date': '2026-11-26',
        'class': 'RoleStatePanel', 'binary_size': SIZE,
        'method': ('R3 Task3 9 残洞独立重扫: 通道 A=ctor 写序 B=ctor 子对象对/'
                   '??_L span/stosd C=全方法 disp 触场(THIS/SUBPTR/OTHER+lea 地址形成) '
                   'D=dtor 拆解序; 独立现扫，不读 Task2 probe JSON'),
        'inputs': ['data/annotations/structs/RoleStatePanel.json',
                   'data/status/struct_holes_20261125.json'],
    },
    'method_set': method_set_meta,
    'ctor_decode': {'this_writes': ctor_dec['this_writes'],
                    'n_this_writes': len(ctor_dec['this_writes']),
                    'subobject_pairs_in_class_extent': [
                        p for p in ctor_dec['call_pairs']
                        if p['this_disp'] and int(p['this_disp'], 16) < SIZE],
                    'array_spans': ctor_dec['array_spans'],
                    'stosd_spans': ctor_dec['stosd_spans']},
    'dtor_decode': {'this_writes': dtor_dec['this_writes'],
                    'subobject_pairs': [p for p in dtor_dec['call_pairs']
                                        if p['this_disp']],
                    'deleting_thunk_writes': dtor_del_dec['this_writes'],
                    'deleting_thunk_pairs': [p for p in dtor_del_dec['call_pairs']
                                             if p['this_disp']]},
    'disp_touch_summary': {
        'n_touches': len(disp_touch),
        'by_cls': dict(collections.Counter(x['cls'] for x in disp_touch)),
        'n_lea_this': len(lea_this),
    },
    'holes': holes_out,
    'summary': {
        'n_holes': len(holes_out),
        'n_evidence': sum(1 for h in holes_out if h['verdict'] == 'evidence'),
        'n_weak_other_only': sum(1 for h in holes_out
                                 if h['verdict'] == 'weak_other_only'),
        'n_zero_evidence': sum(1 for h in holes_out
                               if h['verdict'] == 'zero_evidence'),
        'hole_bytes_total': sum(nb for _, _, nb in HOLES),
    },
}
with open(OUT, 'w', encoding='utf-8') as fh:
    json.dump(report, fh, ensure_ascii=False, indent=1)

print('== 方法集 ==')
print(' n=%d slots=%s' % (method_set_meta['n_methods'], slot_targets))
print('== ctor 写序 (%d) ==' % len(ctor_dec['this_writes']))
for w in ctor_dec['this_writes']:
    print('  #%-2d %s %s @%s [%s]' % (w['order'], w['disp'],
          '%dB' % w['bytes'], w['site'], w['form'][:60]))
print('  subobject pairs:', [(p['site'], p['this_disp'], p['target'][:40])
      for p in ctor_dec['call_pairs'] if p['this_disp']])
print('  array spans:', json.dumps(ctor_dec['array_spans']))
print('  stosd spans:', json.dumps(ctor_dec['stosd_spans']))
print('== dtor 拆解 ==')
print('  dtor writes:', [(x['disp'], x['site']) for x in dtor_dec['this_writes']])
print('  dtor pairs:', [(p['site'], p['this_disp'], p['target'][:44])
      for p in dtor_dec['call_pairs'] if p['this_disp']])
print('  deleting thunk pairs:', [(p['site'], p['this_disp'], p['target'][:40])
      for p in dtor_del_dec['call_pairs'] if p['this_disp']])
print('== disp 触场 ==')
print(' total=%s by_cls=%s lea_this=%s' % (
    len(disp_touch),
    dict(collections.Counter(x['cls'] for x in disp_touch)), len(lea_this)))
print('== 9 洞逐洞裁决 ==')
for h in holes_out:
    ch = h['channels']
    print(' %s..%s (%3dB) verdict=%s' % (h['range'][0], h['range'][1],
                                         h['bytes'], h['verdict']))
    print('   ctor_writes=%d dtor_writes=%d ctor_pairs=%d dtor_pairs=%d '
          'arr=%d stosd=%d disp_this=%d disp_other=%d lea_this=%d' % (
          len(ch['ctor_this_writes']), len(ch['dtor_this_writes']),
          len(ch['ctor_subobject_pairs']), len(ch['dtor_subobject_pairs']),
          len(ch['ctor_array_spans']), len(ch['ctor_stosd_spans']),
          len(ch['disp_this_subptr']), len(ch['disp_other']),
          len(ch['lea_this_addr'])))
    for x in ch['disp_other']:
        print('   OTHER: %s %s %s [%s]' % (x['disp'], x['method'][:36],
                                           x['site'], x['form'][:60]))
    for x in ch['disp_this_subptr']:
        print('   THIS/SUBPTR: %s %s %s w=%d [%s]' % (x['disp'],
              x['method'][:36], x['site'], x['width'], x['form'][:60]))
    for x in ch['lea_this_addr']:
        print('   LEA-THIS: %s %s %s [%s]' % (x['disp'], x['method'][:36],
                                              x['site'], x['form'][:60]))
    print('   nearest below=%s above=%s' % (h['nearest_disp_below'],
                                            h['nearest_disp_above']))
print('summary:', json.dumps(report['summary']))
print('written:', OUT)
idapro.close_database(False)
