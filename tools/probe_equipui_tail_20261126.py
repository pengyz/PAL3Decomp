#!/usr/bin/env python3
"""probe_equipui_tail_20261126.py — EquipUI 尾区四查(R2 计划前置取证)。

背景: EquipUI.json binary_size=266260(0x41014, 金表 ??0EquipUI+push 0x41014);
      90 员末端仅 0x8E80; 尾区 [0x8E80,0x41014)≈229KB 未注解;
      Init 堆分配七大模块存入 [esi+0x2AFB8..0x2AFD0]。
四查:
  1 Init 接收者身份: ?Init@EquipUI 地址 + 调用者 ecx 回溯(≤24 条,遇 call/jmp 停,
      REG_CARRY 深挖至源) + ctor/Create 链调用检查 + esi==this 关系。
  2 七指针消费面: 全库扫 [reg+0x2AFB8..0x2AFD0] 读点+call 形态 → 活成员/死存储。
  3 尾区 disp 普查: EquipUI.json 全部 methods + Init/Create 族,
      [reg+disp] disp∈[0x8E80,0x41014) 直方图(带 this/subptr 溯源) → 边界候选。
  4 ctor 写界: ??0EquipUI 全量反汇编 — memset/rep stosd/??_L 数组构造 +
      成员写序列(this 写 vs 子对象写) vs 0x8E80。
产出: data/status/probe_equipui_tail_20261126.json
"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

ROOT = '/home/peng/workspace/PAL3Decomp'
OUT = ROOT + '/data/status/probe_equipui_tail_20261126.json'
ANN = json.load(open(ROOT + '/data/annotations/structs/EquipUI.json', encoding='utf-8'))

BAD = idc.BADADDR
INIT_EA = idc.get_name_ea_simple('?Init@EquipUI@@QAEXXZ')
CTOR_EA = idc.get_name_ea_simple('??0EquipUI@@QAE@XZ')
DTOR1_EA = idc.get_name_ea_simple('??1EquipUI@@QAE@XZ')
INITUI_EA = idc.get_name_ea_simple('?InitEquipUI@EquipUI@@QAEHH@Z')
SEVEN = [0x2AFB8, 0x2AFBC, 0x2AFC0, 0x2AFC4, 0x2AFC8, 0x2AFCC, 0x2AFD0]
SEVEN_RE = re.compile(r'(?i)\b2af(b8|bc|c0|c4|c8|cc|d0)h\b')
SEVEN_MAP = {'b8': 0x2AFB8, 'bc': 0x2AFBC, 'c0': 0x2AFC0, 'c4': 0x2AFC4,
             'c8': 0x2AFC8, 'cc': 0x2AFCC, 'd0': 0x2AFD0}
TAIL_LO, TAIL_HI = 0x8E80, 0x41014
BRACKET_RE = re.compile(r'\[(e[a-z]{2})(?:\+(?:e[a-z]{2}|\*[1248])|\+)\s*([0-9A-Fa-f]{1,8})h?\]')

def clean(ea):
    return (idc.generate_disasm_line(ea, 0) or '').split(';')[0].strip()

def body_lines(ea, limit=16000):
    """[(addr, text)] 从函数头走到函数尾"""
    f = ida_funcs.get_func(ea)
    if not f:
        return []
    lines, n = [], 0
    cur = f.start_ea
    while cur < f.end_ea and n < limit:
        lines.append((cur, clean(cur)))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    return lines

def ecx_backtrace(call_ea, window=24):
    """回溯 call 前 ecx 装载, ≤24 条, 遶 call/jmp 停 (anchor_boundary_audit 模式)"""
    cur, lines = call_ea, []
    for _ in range(window):
        cur = idc.prev_head(cur, 0)
        if cur == BAD:
            break
        t = clean(cur)
        lines.append((hex(cur), t))
        if re.match(r'^(call|jmp|j[a-z]{2,3})\b', t):
            return ('BLOCKED', t, lines)
        m = re.match(r'^mov\s+ecx,\s*(.+)$', t)
        if m:
            op = m.group(1).strip()
            if op.startswith('ds:') or op.startswith('dword_') or op.startswith('g_'):
                return ('GLOBAL_PTR', op, lines)
            if op.startswith('e') or op == 'cx':
                return ('REG_CARRY', op, lines)
            return ('IMM_OTHER', op, lines)
        if re.match(r'^lea\s+ecx,\s*\[(esp|ebp)', t):
            return ('STACK_LOCAL', t, lines)
        m = re.match(r'^lea\s+ecx,\s*(.+)$', t)
        if m:
            return ('LEA_OTHER', m.group(1).strip(), lines)
    return ('UNKNOWN', '', lines)

def deep_backtrace(call_ea, window=24):
    """ecx_backtrace + REG_CARRY 时继续反扫窗口(穿过 xor/jmp 卫哨形, 不早停),
    后处理提取: new 尺寸/分配 call/ctor call/缓存槽。"""
    form, detail, lines = ecx_backtrace(call_ea, window)
    deep = {'form': form, 'detail': detail, 'lines': lines}
    if form == 'REG_CARRY' and re.match(r'^e[a-z]{2}$', detail):
        src = detail
        cur = int(lines[-1][0], 16)   # mov ecx, src 所在行
        extra = []
        for _ in range(window):
            cur = idc.prev_head(cur, 0)
            if cur == BAD:
                break
            t = clean(cur)
            extra.append((hex(cur), t))
        deep['deep_lines'] = extra
        # 后处理: 窗口内找分配现场(??2)与构造 call 与缓存槽
        deep['receiver_new_size'] = None
        deep['receiver_alloc_call'] = None
        deep['receiver_ctor_call'] = None
        deep['receiver_cache_slots'] = []
        for i, (sa, st) in enumerate(extra):
            if '??2@YAPAXI@Z' in st and deep['receiver_alloc_call'] is None:
                deep['receiver_alloc_call'] = {'site': sa, 'form': st[:80]}
                for j in range(i + 1, min(i + 6, len(extra))):
                    pm = re.match(r'^push\s+([0-9A-Fa-f]+)h$', extra[j][1])
                    if pm:
                        deep['receiver_new_size'] = '0x%s' % pm.group(1)
                        break
            cm = re.match(r'^call\s+(\?\?0\S+|\?\S+@\S+@)?', st)
            if cm and '??2@' not in st and deep['receiver_ctor_call'] is None:
                deep['receiver_ctor_call'] = {'site': sa, 'form': st[:80]}
            sm = re.search(r'^mov\s+\[(e[a-z]{2})\+([0-9A-Fa-f]+)h\],\s*%s$' % src, st)
            if sm:
                deep['receiver_cache_slots'].append(
                    {'site': sa, 'slot': '%s+0x%s' % (sm.group(1), sm.group(2))})
    return deep

def fname(ea):
    f = ida_funcs.get_func(ea)
    return idc.get_func_name(f.start_ea) if f else '?'

class Prov:
    """线性寄存器溯源: this 寄存器集 + 子对象指针寄存器集。"""
    def __init__(self, thiscall=True):
        self.this_regs = {'ecx'} if thiscall else set()
        self.sub_regs = set()
    def feed(self, t):
        m = re.match(r'^mov\s+(e[a-z]{2}),\s*(e[a-z]{2}|cx|ecx)$', t)
        if m:
            dst, src = m.group(1), m.group(2)
            if src in ('ecx', 'cx') or src in self.this_regs:
                self.this_regs.add(dst)
            return
        m = re.match(r'^mov\s+(e[a-z]{2}),\s*(?:dword ptr\s+)?\[(e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]$', t)
        if m and m.group(2) in self.this_regs:
            # 从 this 成员载入的寄存器 → 子对象指针候选
            self.sub_regs.add(m.group(1))
    def base_cls(self, reg):
        if reg in self.this_regs:
            return 'THIS'
        if reg in self.sub_regs:
            return 'SUBPTR'
        return 'OTHER'

report = {}

# ============ 查1: Init 接收者身份 ============
init_receiver = {'init_ea': hex(INIT_EA), 'mangle': '?Init@EquipUI@@QAEXXZ',
                 'ctor_ea': hex(CTOR_EA), 'dtor_ea': hex(DTOR1_EA),
                 'initequipui_ea': hex(INITUI_EA) if INITUI_EA != BAD else None}
callers = []
for xr in idautils.CodeRefsTo(INIT_EA, 1):
    cf = ida_funcs.get_func(xr)
    cn = idc.get_func_name(cf.start_ea) if cf else '?'
    deep = deep_backtrace(xr)
    callers.append({'site': hex(xr), 'caller': cn, 'form': deep['form'],
                    'detail': deep['detail'][:80],
                    'deep': {k: v for k, v in deep.items()
                             if k not in ('lines', 'deep_lines')},
                    'deep_lines': deep.get('deep_lines'),
                    'backtrace': deep['lines'][:6]})
init_receiver['n_callers'] = len(callers)
init_receiver['callers'] = callers
forms = collections.Counter(c['form'] for c in callers)
init_receiver['form_counts'] = dict(forms)
ctor_lo, ctor_hi = CTOR_EA, CTOR_EA + 0x800
init_receiver['called_by_ctor'] = any(
    c['caller'].startswith('??0EquipUI') and ctor_lo <= int(c['site'], 16) < ctor_hi
    for c in callers)
init_receiver['create_chain_callers'] = [c for c in callers if 'Create' in c['caller']]

# 调用者的上游(接收者分配链): ?InitUIComponents@UIGameFrm 的调用者
init_receiver['caller_upstream'] = []
if callers:
    up_ea = int(callers[0]['site'], 16)
    cf = ida_funcs.get_func(up_ea)
    if cf:
        for xr in idautils.CodeRefsTo(cf.start_ea, 1):
            uf = ida_funcs.get_func(xr)
            deep = deep_backtrace(xr)
            init_receiver['caller_upstream'].append({
                'site': hex(xr), 'caller': idc.get_func_name(uf.start_ea) if uf else '?',
                'form': deep['form'], 'detail': deep['detail'][:60]})

# ctor 体是否内联调用 Init
ctor_calls_init, ctor_calls = [], []
for a, t in body_lines(CTOR_EA):
    if 'call' in t:
        ctor_calls.append((hex(a), t))
        if 'Init@EquipUI' in t:
            ctor_calls_init.append((hex(a), t))
init_receiver['ctor_calls_Init'] = ctor_calls_init
init_receiver['ctor_call_list'] = [list(c) for c in ctor_calls[:60]]

# Init 体 esi==this 关系 + 七槽存储现场 + EquipUI 分配现场
init_lines = body_lines(INIT_EA)
esi_from_ecx, esi_writes, seven_store_sites = [], [], []
for a, t in init_lines:
    if re.match(r'^(mov|lea)\s+esi,', t):
        esi_writes.append((hex(a), t))
        if re.match(r'^mov\s+esi,\s*ecx$', t):
            esi_from_ecx.append((hex(a), t))
    sm = SEVEN_RE.search(t)
    if sm:
        off = SEVEN_MAP[sm.group(1).lower()]
        bm = re.search(r'\[(e[a-z]{2})\+', t)
        seven_store_sites.append({'site': hex(a), 'form': t, 'off': hex(off),
                                  'base_reg': bm.group(1) if bm else None})
esi_tail = collections.Counter(s['off'] for s in seven_store_sites
                               if s['base_reg'] == 'esi')
init_receiver['esi_from_ecx'] = [{'site': s, 'form': t} for s, t in esi_from_ecx]
init_receiver['esi_write_count'] = len(esi_writes)
init_receiver['esi_writes_first'] = [{'site': s, 'form': t} for s, t in esi_writes[:6]]
init_receiver['seven_store_sites'] = seven_store_sites
init_receiver['seven_store_via_esi'] = dict(esi_tail)

# EquipUI(0x41014) 在 Init 内的分配现场: push 41014h → new → ctor → store
alloc_ctx = []
for i, (a, t) in enumerate(init_lines):
    if re.match(r'^push\s+41014h$', t):
        alloc_ctx = [{'site': hex(x[0]), 'form': x[1][:80]}
                     for x in init_lines[max(0, i - 2):i + 26]]
        break
init_receiver['equipui_alloc_context'] = alloc_ctx
# Init 内是否有 memset/rep 清零(0x41014 缓冲)
init_zero = [({'site': hex(a), 'form': t[:80]}) for a, t in init_lines
             if 'memset' in t or 'stos' in t]
init_receiver['init_memset_or_stos'] = init_zero[:10]
report['init_receiver'] = init_receiver

# ============ 查4: ctor 写界(溯源版) ============
ctor_writes = {'ctor_ea': hex(CTOR_EA)}
ctor_body = body_lines(CTOR_EA)
ctor_writes['n_heads'] = len(ctor_body)
prov = Prov(thiscall=True)
memset_ev, rep_ev, arr_iter_ev, other_calls = [], [], [], []
recent = []   # 最近 8 条 (addr, text) — ??_L 参数提取
for a, t in ctor_body:
    prov.feed(t)
    if 'stosd' in t or 'stosb' in t:
        rep_ev.append({'site': hex(a), 'form': t[:80]})
    if t.startswith('call'):
        row = {'site': hex(a), 'form': t[:90]}
        if '??_L@' in t or '??_H@' in t:
            # ??_L@YGXPAXIHP6EX0@Z1@Z = ehvec_ctor(ptr, size, count, ctor, dtor)
            # push 序(右起): dtor, ctor, count, [lea ptr], size, ptr
            base_disp = elem_size = elem_count = fn = None
            after_lea = False
            for sa, st in reversed(recent):
                lm = re.match(r'^lea\s+e[a-z]{2},\s*\[esi\+([0-9A-Fa-f]+)h?\]$', st)
                if lm:
                    base_disp = int(lm.group(1), 16)
                    after_lea = True
                    continue
                pm = re.match(r'^push\s+(?:offset\s+)?(\S+)$', st)
                if pm:
                    tok = pm.group(1)
                    if tok.startswith('?'):
                        fn = tok[:60]
                    elif re.match(r'^[0-9A-Fa-f]+h$', tok):
                        v = int(tok[:-1], 16)
                    elif re.match(r'^[0-9]+$', tok):
                        v = int(tok)          # IDA: <0xA 无 h 后缀=十进制
                    else:
                        v = None
                    if re.match(r'^[0-9A-Fa-f]+h$', tok) or re.match(r'^[0-9]+$', tok):
                        # 反向遍历: after_lea=True = 程序序在 lea 之前 = ABI 的 count
                        if after_lea and elem_count is None:
                            elem_count = v
                        elif elem_size is None:
                            elem_size = v     # lea 与 ptr 之间 = ABI 的 size
                # 不提前 break: 走完窗口把 fn 也抓到
            row['base_disp'] = hex(base_disp) if base_disp is not None else None
            row['elem_size'] = elem_size
            row['elem_count'] = elem_count
            row['ctor_fn'] = fn
            if base_disp is not None and elem_size and elem_count:
                row['span_end'] = hex(base_disp + elem_size * elem_count)
            arr_iter_ev.append(row)
        elif '??2@' not in t and 'memset' not in t:
            other_calls.append(row)
    recent.append((hex(a), t))
    recent = recent[-8:]
ctor_writes['push_41014_sites'] = [ {'site': hex(a), 'form': t} for a, t in ctor_body
                                    if re.match(r'^push\s+41014h$', t)]
ctor_writes['stosd_sites'] = rep_ev[:8]
ctor_writes['array_iterator_calls'] = arr_iter_ev[:16]
ctor_writes['call_counts'] = dict(collections.Counter(
    c['form'].split()[1].split('(')[0][:48] for c in other_calls))
ctor_writes['n_other_calls'] = len(other_calls)

tw, sw, ow = [], [], []
for a, t in ctor_body:
    m = re.match(r'^mov\s+(?:dword ptr\s+|byte ptr\s+|word ptr\s+)?\[(e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]\s*,', t)
    if not m:
        m = re.match(r'^mov\s+\[(e[a-z]{2})\],', t)
        if m:
            continue
        continue
    reg, disp = m.group(1), int(m.group(2), 16)
    cls = prov.base_cls(reg)
    row = {'site': hex(a), 'disp': hex(disp), 'cls': cls, 'form': t[:90]}
    (tw if cls == 'THIS' else sw if cls == 'SUBPTR' else ow).append(row)
ctor_writes['this_writes'] = tw[:500]
ctor_writes['subptr_writes'] = sw[:200]
ctor_writes['other_writes'] = ow[:100]
ctor_writes['n_this_writes'] = len(tw)
ctor_writes['n_subptr_writes'] = len(sw)
tw_d = sorted(int(w['disp'], 16) for w in tw)
ctor_writes['this_write_disp_max'] = hex(tw_d[-1]) if tw_d else None
ctor_writes['this_write_disp_min'] = hex(tw_d[0]) if tw_d else None
ctor_writes['this_write_disps_ge_8E80'] = [hex(x) for x in tw_d if x >= TAIL_LO][:60]
ctor_writes['this_write_tail_max'] = hex(max(tw_d)) if tw_d else None
report['ctor_writes'] = ctor_writes

# ============ ctor 调用上下文(分配链) ============
ctor_callers = []
for xr in idautils.CodeRefsTo(CTOR_EA, 1):
    cf = ida_funcs.get_func(xr)
    cn = idc.get_func_name(cf.start_ea) if cf else '?'
    deep = deep_backtrace(xr)
    store = None
    cur = xr
    fend = ida_funcs.get_func(xr).end_ea if ida_funcs.get_func(xr) else BAD
    for _ in range(10):
        cur = idc.next_head(cur, fend)
        if cur == BAD:
            break
        tt = clean(cur)
        sm = re.match(r'^mov\s+\[(e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\],\s*e[a-z]{2}$', tt)
        if sm:
            store = '%s+0x%s' % (sm.group(1), sm.group(2))
            break
    ctor_callers.append({'site': hex(xr), 'caller': cn, 'ecx_form': deep['form'],
                         'ecx_detail': deep['detail'][:60], 'store': store})
report['ctor_callers'] = {'n': len(ctor_callers), 'callers': ctor_callers}

# ============ 全库单遍扫描: 查2(七指针) + 查3(尾区直方图, EquipUI 方法族) ============
method_addrs = {int(k, 16): str(m.get('name') or k) for k, m in ANN['methods'].items()}
family = {}
for ea in (INIT_EA, CTOR_EA, DTOR1_EA, INITUI_EA):
    if ea != BAD:
        family[ea] = idc.get_func_name(ea)
thunk = idc.get_name_ea_simple('_EquipUI_0')   # vtable 槽 _scalar_dtor_8C70
if thunk != BAD:
    family[thunk] = '_EquipUI_0'

consumers = {hex(o): [] for o in SEVEN}
hist = collections.defaultdict(lambda: {'n': 0, 'cls': collections.Counter(),
                                        'sites': [], 'methods': set()})
nfun = 0
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    nfun += 1
    cn = idc.get_func_name(f.start_ea)
    in_equip = fea in method_addrs or fea in family
    mname = method_addrs.get(fea) or family.get(fea) or cn
    prov = Prov(thiscall=True)   # EquipUI 方法族全为 thiscall (QA..)
    lines, n = [], 0
    cur = f.start_ea
    while cur < f.end_ea and n < 9000:
        t = clean(cur)
        prov.feed(t)
        # 查2: 七指针任意访问
        sm = SEVEN_RE.search(t)
        if sm:
            off = SEVEN_MAP[sm.group(1).lower()]
            kind = 'OTHER'
            if re.match(r'^mov\s+e[a-z]{2},\s*(?:dword ptr\s+)?\[e[a-z]{2}\+', t):
                kind = 'READ'
            elif re.match(r'^mov\s+(?:dword ptr\s+)?\[e[a-z]{2}\+', t):
                kind = 'WRITE'
            elif t.startswith('lea'):
                kind = 'LEA'
            elif t.startswith(('cmp', 'test', 'push')):
                kind = 'READ'
            nxt = ''
            c2, k2 = cur, 0
            while k2 < 8:
                c2 = idc.next_head(c2, f.end_ea)
                if c2 == BAD:
                    break
                t2 = clean(c2)
                if t2.startswith('call'):
                    nxt = t2[:80]
                    break
                k2 += 1
            consumers[hex(off)].append({'func': cn, 'site': hex(cur),
                                        'form': t[:90], 'kind': kind,
                                        'next_call': nxt})
        # 查3: 尾区 disp 直方图(仅 EquipUI 方法+族, 带溯源分类)
        if in_equip:
            for bm in BRACKET_RE.finditer(t):
                d = int(bm.group(2), 16)
                if TAIL_LO <= d < TAIL_HI:
                    h = hist[d]
                    h['n'] += 1
                    h['cls'][prov.base_cls(bm.group(1))] += 1
                    h['sites'].append(hex(cur))
                    h['methods'].add(mname)
        cur = idc.next_head(cur, f.end_ea)
        n += 1

seven_ptr = {}
for off in SEVEN:
    rows = consumers[hex(off)]
    reads = [r for r in rows if r['kind'] == 'READ']
    writes = [r for r in rows if r['kind'] == 'WRITE']
    leas = [r for r in rows if r['kind'] == 'LEA']
    seven_ptr[hex(off)] = {
        'n_reads': len(reads), 'n_writes': len(writes), 'n_lea': len(leas),
        'n_other': len(rows) - len(reads) - len(writes) - len(leas),
        'reader_funcs': sorted(set(r['func'] for r in reads))[:20],
        'reads': reads[:50], 'writes': writes[:30], 'leas': leas[:15],
    }
report['seven_ptr_consumers'] = seven_ptr

hist_out = {}
for d in sorted(hist):
    h = hist[d]
    hist_out[hex(d)] = {'n': h['n'], 'cls': dict(h['cls']),
                        'methods': sorted(h['methods'])[:24]}
report['tail_disp_histogram'] = {
    'range': [hex(TAIL_LO), hex(TAIL_HI)],
    'funcs_scanned': nfun,
    'equip_funcs_scanned': sorted(hex(a) for a in (set(method_addrs) | set(family))),
    'n_unique_disps': len(hist_out),
    'hist': hist_out,
}

# 聚类: 全体与 THIS-only 两套边界候选
def gaps_of(keys, min_gap=0x100):
    ds = sorted(keys)
    out = []
    for i in range(1, len(ds)):
        g = ds[i] - ds[i - 1]
        if g >= min_gap:
            out.append({'lo': hex(ds[i - 1]), 'hi': hex(ds[i]), 'gap': hex(g)})
    out.sort(key=lambda x: -int(x['gap'], 16))
    return out

all_keys = list(hist.keys())
this_keys = [d for d, h in hist.items() if h['cls'].get('THIS', 0) > 0]
report['tail_disp_histogram']['gaps_all_top'] = gaps_of(all_keys)[:24]
report['tail_disp_histogram']['gaps_this_top'] = gaps_of(this_keys)[:24]

km = {int(k, 16): v.get('name') for k, v in (ANN.get('known_members') or {}).items()
      if isinstance(v, dict)}
ann_in_tail = sorted(o for o in km if TAIL_LO <= o < TAIL_HI)
report['tail_disp_histogram']['annotated_members_in_tail'] = [
    {'off': hex(o), 'name': km[o], 'hist_n': hist[o]['n'] if o in hist else 0}
    for o in ann_in_tail]

# ============ 裁决 ============
live = {hex(o): len([r for r in consumers[hex(o)] if r['kind'] == 'READ']) for o in SEVEN}
reader_union = set()
for o in SEVEN:
    reader_union |= set(seven_ptr[hex(o)]['reader_funcs'])
verdicts = {
    'init_receiver': {
        'ea': hex(INIT_EA),
        'n_callers': len(callers),
        'caller_forms': dict(forms),
        'called_by_ctor': init_receiver['called_by_ctor'],
        'create_chain': bool(init_receiver['create_chain_callers']),
        'esi_eq_ecx': bool(esi_from_ecx),
        'esi_eq_ecx_site': esi_from_ecx[0][0] if esi_from_ecx else None,
        'esi_write_count': len(esi_writes),
        'seven_stored_via_esi': dict(esi_tail),
        'receiver_provenance': (
            callers[0]['deep'] if callers else None),
        'receiver_cache_slot_lines': (
            [l for l in callers[0]['backtrace']
             if re.search(r'mov\s+\[e[a-z]{2}\+[0-9A-Fa-f]+h\],\s*eax', l[1])]
            if callers else []),
        'note': ('Init this=ecx→esi 全程一致; 接收者为调用者上游 new 出的容器对象'
                 if esi_from_ecx else 'esi 溯源失败'),
    },
    'seven_ptr_liveness': {
        'reads_per_slot': live,
        'writes_per_slot': {hex(o): len([r for r in consumers[hex(o)]
                                         if r['kind'] == 'WRITE']) for o in SEVEN},
        'all_slots_live': all(v > 0 for v in live.values()),
        'reader_union_funcs': sorted(reader_union),
        'note': '全部七槽有 [reg+disp]→ecx 装载+立即 call 方法 的活分派形',
    },
    'tail_boundaries': {
        'n_unique_disps': len(hist_out),
        'n_this_disps': len(this_keys),
        'gaps_this_top6': gaps_of(this_keys)[:6],
        'annotated_in_tail': {'n': len(ann_in_tail),
                              'max_annotated': hex(max(ann_in_tail)) if ann_in_tail else None},
        'note': 'Init(容器接收者)的 0x2AFB8..0x2AFD0 命中属容器类, 非 EquipUI 尾员',
    },
    'ctor_write_bound': {
        'memset_in_ctor': bool(memset_ev),
        'stosd_in_ctor': bool(rep_ev),
        'array_iterator_calls': len(arr_iter_ev),
        'array_coverage': [
            {k: r[k] for k in ('site', 'base_disp', 'elem_size', 'elem_count', 'span_end', 'ctor_fn')}
            for r in arr_iter_ev if r.get('span_end')],
        'this_write_disp_max': ctor_writes['this_write_disp_max'],
        'this_write_max_vs_8E80': (int(ctor_writes['this_write_disp_max'], 16) <= TAIL_LO)
                                   if ctor_writes['this_write_disp_max'] else None,
        'note': ('push 41014h 是 Init 内 operator new 尺寸参; ctor 无 memset/rep stosd, '
                 '尾区由 ??_L 原位数组构造(批量子对象)+直接 this 写(至 max)填满'),
    },
}
report['verdicts'] = verdicts

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
print('查1 Init %s callers=%d forms=%s esi==ecx=%s@%s ctor内联Init=%s' % (
    hex(INIT_EA), len(callers), dict(forms), bool(esi_from_ecx),
    esi_from_ecx[0][0] if esi_from_ecx else '-', init_receiver['called_by_ctor']))
print('   接收者溯源:', verdicts['init_receiver']['receiver_provenance'])
print('查2 七指针读点: %s' % live)
print('查3 尾区唯一 disp=%d THIS=%d gaps_this_top3=%s' % (
    len(hist_out), len(this_keys),
    [(g['lo'], g['hi'], g['gap']) for g in gaps_of(this_keys)[:3]]))
print('查4 ctor this写界 max=%s (vs 0x8E80) memset=%s stosd=%s ??_数组构造=%d' % (
    ctor_writes['this_write_disp_max'],
    verdicts['ctor_write_bound']['this_write_max_vs_8E80'], bool(rep_ev), len(arr_iter_ev)))
idapro.close_database(False)
