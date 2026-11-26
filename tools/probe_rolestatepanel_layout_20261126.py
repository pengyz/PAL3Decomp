#!/usr/bin/env python3
"""probe_rolestatepanel_layout_20261126.py — RoleStatePanel 布局五查(R3 计划前置取证)。

背景: RoleStatePanel binary_size=176256(0x2B080 金表闭合: operator new(0x2B080)@
      UIGameFrm::InitUIComponents 0x44f1d5 + store esi+0x6E14); 现 16 员含七模块
      指针 @[0x2AFB8,0x2AFD4); struct_holes_20261125 census 6 洞 156433B
      (主体大洞 ~153852B); bases=['UIWnd'] (C11 门挂裁决条目)。
五查:
  1 ctor 全量解码: 定位分配链 call(≈0x44f1f1) 真 ctor — ??0RoleStatePanel 存在性 +
      ?InitUI@RoleStatePanel@@QAEHXZ 全量反汇编: 基类构造调用(??0UIWnd=bases 裁决
      素材)、memset/rep stosd 范围、成员写序列、??_L 原位数组构造五参全解
      (R2 九数组同法 probe_equipui_arrays_20261126)。
  2 全方法 disp 普查: RoleStatePanel.json methods + Init/InitUI 族 + DB ?*RoleStatePanel*
      全名, this-form [reg+disp] disp∈[0,0x2B080) 直方图(this/subptr 溯源) → 聚类
      边界候选。
  3 洞清单精确化: census 六洞坐标 × ctor 写序列/数组 span/stosd span/直方图交叉 →
      每洞分类(ctor 覆盖=可落位 vs 零证据=诚实留)。
  4 C11 bases 证据: ctor 首段是否直调 ??0UIWnd(0x445aa0) + dtor 收尾基析构 +
      表 0x56F040 slot0/4 与 UIWnd 表 0x56AEC8 字节逐槽对账。
  5 UIWnd 基类尺寸: UIWnd.json binary_size(68=0x44) + [0,0x44) 基子对象区覆盖现状
      + RoleStatePanel 方法对基区 disp 使用。
产出: data/status/probe_rolestatepanel_layout_20261126.json
"""
import sys, os, json, re, glob, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

ROOT = '/home/peng/workspace/PAL3Decomp'
OUT = ROOT + '/data/status/probe_rolestatepanel_layout_20261126.json'
STRUCTS_DIR = ROOT + '/data/annotations/structs'
BAD = idc.BADADDR

ANN = json.load(open(STRUCTS_DIR + '/RoleStatePanel.json', encoding='utf-8'))
UIWND = json.load(open(STRUCTS_DIR + '/UIWnd.json', encoding='utf-8'))
HOLES_CENSUS = json.load(open(ROOT + '/data/status/struct_holes_20261125.json',
                              encoding='utf-8'))

SIZE = ANN['binary_size']                      # 176256 = 0x2B080
SIZE_LO, SIZE_HI = 0, SIZE
BASE_LO, BASE_HI = 0, UIWND['binary_size']     # [0, 0x44)
DERIVED_LO = BASE_HI
VT = 0x56F040                                  # RoleStatePanel vtable
UIWND_VT = 0x56AEC8                            # UIWnd vtable
UIWND_CTOR_EA = idc.get_name_ea_simple('??0UIWnd@@QAE@XZ')       # 0x445aa0
UIWND_DTOR_EA = idc.get_name_ea_simple('??1UIWnd@@QAE@XZ')       # 0x445b40
ALLOC_CALLER_NAME = '?InitUIComponents@UIGameFrm@@QAEXXZ'
CTOR_MANGLE = '?InitUI@RoleStatePanel@@QAEHXZ'

def clean(ea):
    return (idc.generate_disasm_line(ea, 0) or '').split(';')[0].strip()

def body_lines(ea, limit=30000):
    f = ida_funcs.get_func(ea)
    if not f:
        return []
    out, cur, n = [], f.start_ea, 0
    while cur < f.end_ea and n < limit:
        out.append((cur, clean(cur)))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    return out

def fname(ea):
    f = ida_funcs.get_func(ea)
    return idc.get_func_name(f.start_ea) if f else '?'

def is_fn_ea(v):
    if v is None or v == BAD:
        return False
    f = ida_funcs.get_func(v)
    return f is not None and f.start_ea == v

LONG_DN = idc.get_inf_attr(idc.INF_LONG_DN)
def demangle(name):
    return idc.demangle_name(name, LONG_DN) or name

def class_from_mangled(m):
    t = m
    if t.startswith('??_'):
        t = t[3:]
    elif t.startswith('??'):
        t = t[2:]
    elif t.startswith('?'):
        t = t[1:]
    else:
        return None
    if t[:2] in ('_G', '_E', '_U'):
        t = t[2:]
    elif t[:1].isdigit():
        t = t[1:]
    chain = []
    for p in t.split('@')[1:]:
        if p == '':
            break
        chain.append(p)
    return chain[-1] if chain else None

class Prov:
    """线性寄存器溯源: this 寄存器集 + 子对象指针寄存器集 (probe_equipui_tail 同法)"""
    def __init__(self):
        self.this_regs = {'ecx'}
        self.sub_regs = set()
    def feed(self, t):
        m = re.match(r'^mov\s+(e[a-z]{2}),\s*(e[a-z]{2}|cx|ecx)$', t)
        if m:
            if m.group(2) in ('ecx', 'cx') or m.group(2) in self.this_regs:
                self.this_regs.add(m.group(1))
            return
        m = re.match(r'^mov\s+(e[a-z]{2}),\s*(?:dword ptr\s+)?\[(e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]$', t)
        if m and m.group(2) in self.this_regs:
            self.sub_regs.add(m.group(1))
    def base_cls(self, reg):
        if reg in self.this_regs:
            return 'THIS'
        if reg in self.sub_regs:
            return 'SUBPTR'
        return 'OTHER'

IMM_RE = re.compile(r'^push\s+((?:[0-9A-Fa-f]+)h|[0-9]+)$')
SYM_RE = re.compile(r'^push\s+offset\s+(\S+)$')
REG_RE = re.compile(r'^push\s+(e[a-z]{2})$')
LEA_RE = re.compile(r'^lea\s+(e[a-z]{2}),\s*\[(e[a-z]{2})\+([0-9A-Fa-f]+)h?\]$')
MOVDST_RE = re.compile(r'^(?:mov|xor|add|sub|and|or|pop|inc|dec|neg|not)\s+(e[a-z]{2})\b')
CALL_RE = re.compile(r'^call\s+(\S+)')
HELPER_RE = re.compile(r'\?\?_[LMHE][@A-Z]')

def resolve_sym(tok):
    return idc.get_name_ea_simple(tok.strip())

# ================================================================
# 查1a: 分配链现场 (UIGameFrm::InitUIComponents ≈0x44f1d5..0x44f1f1)
# ================================================================
alloc_caller_ea = idc.get_name_ea_simple(ALLOC_CALLER_NAME)
alloc_chain = {'caller_ea': hex(alloc_caller_ea) if alloc_caller_ea != BAD else None,
               'caller': ALLOC_CALLER_NAME}
ctor_call_ea = None
ctor_target_sym = None
if alloc_caller_ea != BAD:
    lines = body_lines(alloc_caller_ea)
    win = []
    for a, t in lines:
        win.append((a, t))
        if '??2@YAPAXI@Z' in t:
            idx = len(win) - 1
            ctx = win[max(0, idx - 3): idx + 9]
            alloc_chain['new_ctx'] = [{'site': hex(x[0]), 'form': x[1]} for x in ctx]
            for a2, t2 in ctx:
                pm = re.match(r'^push\s+([0-9A-Fa-f]+)h$', t2)
                if pm and int(pm.group(1), 16) == SIZE:
                    alloc_chain['push_size_site'] = hex(a2)
                if a2 > a and t2.startswith('call') and '??2@' not in t2:
                    cm = CALL_RE.match(t2)
                    ctor_call_ea = a2
                    ctor_target_sym = cm.group(1) if cm else None
                    alloc_chain['ctor_call_site'] = hex(a2)
                    alloc_chain['ctor_call_form'] = t2
                sm = re.match(r'^mov\s+\[(e[a-z]{2})\+([0-9A-Fa-f]+)h\],\s*eax$', t2)
                if sm and ctor_call_ea and a2 > ctor_call_ea:
                    alloc_chain['store'] = '%s+0x%s' % (sm.group(1), sm.group(2))
                    alloc_chain['store_site'] = hex(a2)
            break

# ================================================================
# 查1b: ctor 身份 — ??0RoleStatePanel 存在性 + DB 全名清单
# ================================================================
ctor_identity = {'ctor_mangle_expect': CTOR_MANGLE}
e0 = idc.get_name_ea_simple('??0RoleStatePanel@@QAE@XZ')
ctor_identity['mangled_ctor_exists'] = (e0 != BAD)
ctor_identity['mangled_ctor_ea'] = hex(e0) if e0 != BAD else None
ctor_ea = resolve_sym(CTOR_MANGLE)
ctor_identity['initui_sym_ea'] = hex(ctor_ea) if ctor_ea != BAD else None
ctor_identity['alloc_call_target_sym'] = ctor_target_sym
ctor_identity['alloc_call_target_is_initui'] = (
    ctor_ea != BAD and ctor_target_sym == CTOR_MANGLE)
names_rp = []
for ea, nm in idautils.Names():
    if 'RoleStatePanel' in nm:
        names_rp.append({'ea': hex(ea), 'name': nm, 'is_func': is_fn_ea(ea)})
ctor_identity['db_names_containing_RoleStatePanel'] = names_rp
ctor_identity['ctor_func_range'] = None
if ctor_ea != BAD:
    f = ida_funcs.get_func(ctor_ea)
    if f:
        ctor_identity['ctor_func_range'] = [hex(f.start_ea), hex(f.end_ea)]

# ================================================================
# 查1c: ctor 全量解码
# ================================================================
ctor_decode = {'ea': hex(ctor_ea) if ctor_ea != BAD else None}
array_ctls = []
TW_FULL = []
WROWS = []
if ctor_ea != BAD:
    body = body_lines(ctor_ea)
    ctor_decode['n_instructions'] = len(body)
    ctor_decode['head_lines'] = [{'site': hex(a), 'form': t} for a, t in body[:24]]

    vt_installs, base_ctor_calls, calls, sub_ctor_pairs = [], [], [], []
    rep_stosd, writes = [], []
    prov = Prov()
    pending, regmodel, recent = [], {}, []
    ecx_state = None   # 最近 lea ecx,[esi+disp] / mov ecx,esi → disp(None=未知)
    for idx, (a, t) in enumerate(body):
        recent.append((a, t))
        recent = recent[-8:]
        prov.feed(t)
        lm3 = re.match(r'^lea\s+ecx,\s*\[esi(?:\+([0-9A-Fa-f]+)h?)?\]$', t)
        if lm3:
            ecx_state = int(lm3.group(1), 16) if lm3.group(1) else 0
        mv3 = re.match(r'^mov\s+ecx,\s*esi$', t)
        if mv3:
            ecx_state = 0
        cm = CALL_RE.match(t)
        if cm:
            tgt = resolve_sym(cm.group(1))
            pair_disp = ecx_state
            ecx_state = None      # callee 会 clobber ecx
            sub_ctor_pairs.append({'site': hex(a), 'target': cm.group(1)[:64],
                                   'this_disp': hex(pair_disp) if pair_disp is not None
                                   else None,
                                   'window': [{'site': hex(x[0]), 'form': x[1]}
                                              for x in body[max(0, idx - 3): idx]]})
            row = {'site': hex(a), 'target': cm.group(1)[:80],
                   'target_ea': hex(tgt) if tgt != BAD else None}
            if HELPER_RE.search(cm.group(1)) or (
                    tgt != BAD and '??_' in (idc.get_name(tgt) or '')):
                row['kind'] = 'eh_helper'
                rec = {'site': hex(a), 'helper': cm.group(1),
                       'push_window': [{'site': hex(x[0]), 'form': x[1]}
                                       for x in recent]}
                if len(pending) >= 5:
                    d5 = pending[-5:]   # 程序序尾五 = [dtor, ctor, count, size, ptr]
                    k_dt, k_ct, k_cnt, k_sz, k_ptr = d5
                    ok = (k_dt[0] == 'fn' and k_ct[0] == 'fn'
                          and k_cnt[0] == 'imm' and k_sz[0] == 'imm'
                          and k_ptr[0] in ('ptr', 'imm'))
                    rec['stack_form_ok'] = ok
                    if ok:
                        disp, count, size = k_ptr[1], k_cnt[1], k_sz[1]
                        rec.update({
                            'offset': disp, 'count': count, 'stride': size,
                            'ctor_ea': hex(k_ct[1]), 'ctor_name': k_ct[2],
                            'ctor_class_mangled': class_from_mangled(k_ct[2]),
                            'dtor_ea': hex(k_dt[1]), 'dtor_name': k_dt[2],
                            'dtor_class_mangled': class_from_mangled(k_dt[2]),
                            'span': [hex(disp), hex(disp + size * count)],
                        })
                        array_ctls.append(rec)
                else:
                    rec['stack_form_ok'] = False
                    rec['n_pending'] = len(pending)
            elif tgt == UIWND_CTOR_EA or '??0UIWnd' in cm.group(1):
                row['kind'] = 'base_ctor'
                base_ctor_calls.append(row)
            else:
                row['kind'] = 'other'
            calls.append(row)
            pending, regmodel = [], {}
            continue
        if t.startswith('rep stosd'):
            rep_stosd.append({'site': hex(a),
                              'window': [{'site': hex(x[0]), 'form': x[1]}
                                         for x in body[max(0, idx - 5): idx + 1]]})
            continue
        m = IMM_RE.match(t)
        if m:
            tok = m.group(1)
            v = int(tok[:-1], 16) if tok.endswith('h') else int(tok)
            if is_fn_ea(v):
                pending.append(('fn', v, idc.get_name(v) or ('sub_%X' % v)))
            else:
                pending.append(('imm', v))
            continue
        m = SYM_RE.match(t)
        if m:
            ea2 = resolve_sym(m.group(1))
            pending.append(('fn', ea2 if ea2 != BAD else None, m.group(1)))
            continue
        m = LEA_RE.match(t)
        if m:
            regmodel[m.group(1)] = int(m.group(3), 16)
            continue
        m = REG_RE.match(t)
        if m:
            r = m.group(1)
            pending.append(('ptr', regmodel[r]) if r in regmodel else ('reg', r))
            continue
        md = MOVDST_RE.match(t)
        if md:
            regmodel.pop(md.group(1), None)
            if md.group(1) == 'ecx':
                ecx_state = None
            continue
        if t.startswith('pop ') or t.startswith('add esp') or t.startswith('mov esp'):
            pending = []
            continue
        vm = re.match(r'^mov\s+(?:dword ptr\s+)?\[(e[a-z]{2})\],\s*offset\s+(\S+)', t)
        if vm:
            vt_installs.append({'site': hex(a), 'form': t[:90], 'vt_name': vm.group(2)})
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
            elif re.match(r'^[a-d][hl]$', src):
                nb = 1
            elif re.match(r'^[a-d]x$|^[sd]i$|^bp$', src):
                nb = 2
            else:
                nb = 4
            writes.append({'site': hex(a), 'disp': hex(disp), 'bytes': nb,
                           'cls': prov.base_cls(reg), 'form': t[:90]})

    ctor_decode['vtable_installs'] = vt_installs
    ctor_decode['base_ctor_calls'] = base_ctor_calls
    ctor_decode['calls'] = calls[:120]
    ctor_decode['n_calls'] = len(calls)
    ctor_decode['sub_ctor_pairs'] = sub_ctor_pairs
    ctor_decode['rep_stosd'] = rep_stosd
    tw = sorted(int(w['disp'], 16) for w in writes if w['cls'] == 'THIS')
    sw = [w for w in writes if w['cls'] == 'SUBPTR']
    ctor_decode['this_write_disps'] = [hex(x) for x in tw][:400]
    ctor_decode['this_write_min'] = hex(tw[0]) if tw else None
    ctor_decode['this_write_max'] = hex(tw[-1]) if tw else None
    ctor_decode['n_this_writes'] = len(tw)
    ctor_decode['subptr_writes'] = sw[:60]
    TW_FULL = tw
    WROWS = [(int(w['disp'], 16), w.get('bytes', 4))
             for w in writes if w['cls'] == 'THIS']

    # ctor xref 调用者(=分配链复证)
    ctor_xrefs = []
    for xr in idautils.CodeRefsTo(ctor_ea, 1):
        ctor_xrefs.append({'site': hex(xr), 'caller': fname(xr)})
    ctor_identity['ctor_xrefs'] = ctor_xrefs

    # ---- ??_L 数组注解对账 (R2 同法: corpus 反查 + binary_size==stride) ----
    CORPUS = {}
    SIZES = {}
    for p in glob.glob(os.path.join(STRUCTS_DIR, '*.json')):
        cls_n = os.path.basename(p)[:-5]
        try:
            d = json.load(open(p, encoding='utf-8'))
        except Exception:
            continue
        if d.get('binary_size'):
            SIZES[cls_n] = d['binary_size']
        for aa, mm in (d.get('methods') or {}).items():
            try:
                ea = int(aa, 16)
            except Exception:
                continue
            CORPUS.setdefault(ea, []).append((cls_n, mm.get('name'),
                                              (mm.get('evidence_level') or '')))
    def corpus_owner(ea_s):
        claims = CORPUS.get(int(ea_s, 16), [])
        if len(claims) == 1:
            return {'class': claims[0][0], 'method': claims[0][1],
                    'evidence_level': claims[0][2], 'n_claims': 1}
        if claims:
            return {'class': None, 'n_claims': len(claims),
                    'claims': [(c[0], c[1]) for c in claims]}
        return {'class': None, 'n_claims': 0}
    for rec in array_ctls:
        ct_own = corpus_owner(rec['ctor_ea'])
        dt_own = corpus_owner(rec['dtor_ea'])
        rec['ctor_owner'] = ct_own
        rec['dtor_owner'] = dt_own
        rec['ctor_class'] = ct_own.get('class') or rec['ctor_class_mangled']
        rec['dtor_class'] = dt_own.get('class') or rec['dtor_class_mangled']
        rec['ctor_demangled'] = demangle(rec['ctor_name'])
        rec['dtor_demangled'] = demangle(rec['dtor_name'])
        rec['callback_owners_agree'] = (rec['ctor_class'] is not None and
                                        rec['ctor_class'] == rec['dtor_class'])
        a_ct_p = os.path.join(STRUCTS_DIR, '%s.json' % rec['ctor_class']) \
            if rec['ctor_class'] else None
        a_dt_p = os.path.join(STRUCTS_DIR, '%s.json' % rec['dtor_class']) \
            if rec['dtor_class'] else None
        a_ct = json.load(open(a_ct_p, encoding='utf-8')).get('binary_size') \
            if a_ct_p and os.path.exists(a_ct_p) else None
        a_dt = json.load(open(a_dt_p, encoding='utf-8')).get('binary_size') \
            if a_dt_p and os.path.exists(a_dt_p) else None
        verdict = 'none'
        ct_ok = a_ct is not None and a_ct == rec['stride']
        dt_ok = a_dt is not None and a_dt == rec['stride']
        if ct_ok and dt_ok:
            verdict = 'both'
        elif ct_ok:
            verdict = 'ctor'
        elif dt_ok:
            verdict = 'dtor'
        rec['annotation_match'] = {'ctor_binary_size': a_ct,
                                   'dtor_binary_size': a_dt, 'verdict': verdict}
        if verdict in ('ctor', 'both'):
            rec['element_class'] = rec['ctor_class']
            rec['candidate_basis'] = 'ctor_callback_owner'
        elif verdict == 'dtor':
            rec['element_class'] = rec['dtor_class']
            rec['candidate_basis'] = 'dtor_callback_owner'
        else:
            rec['element_class'] = (rec['ctor_class'] or rec['dtor_class']
                                    or 'unknown')
            rec['candidate_basis'] = None
        rec['candidate_usable'] = verdict in ('ctor', 'dtor', 'both')
        # ctor 回调字段足迹佐证
        ext = -1
        fcb = ida_funcs.get_func(int(rec['ctor_ea'], 16))
        if fcb:
            cur = fcb.start_ea
            while cur < fcb.end_ea:
                for mm in re.finditer(r'\[e[a-z]{2}\+([0-9A-Fa-f]+)h?\]', clean(cur)):
                    ext = max(ext, int(mm.group(1), 16))
                cur = idc.next_head(cur, fcb.end_ea)
        if ext >= 0:
            rec['ctor_cb_max_this_disp'] = hex(ext)
            rec['ctor_cb_extent_fits_stride'] = (ext + 4) <= rec['stride']
        # stride 全档对账: binary_size==stride 的全部注解类(消歧: 152 可能双类)
        rec['stride_classes'] = sorted(
            c for c, sz in SIZES.items() if sz == rec['stride'])
    array_ctls.sort(key=lambda r: r['offset'])

# ================================================================
# 查2: 全方法 disp 普查
# ================================================================
method_addrs = {}
for k, m in ANN['methods'].items():
    ea = int(k, 16)
    if is_fn_ea(ea):
        method_addrs[ea] = str(m.get('name') or k)
for ea, nm in idautils.Names():
    if ('RoleStatePanel' in nm and nm.startswith('?') and is_fn_ea(ea)
            and ea not in method_addrs):
        method_addrs[ea] = nm

hist = collections.defaultdict(lambda: {'n': 0, 'cls': collections.Counter(),
                                        'sites': [], 'methods': set()})
zone_counts = {'base': 0, 'derived': 0}
n_methods_scanned = 0
for ea, mname in sorted(method_addrs.items()):
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    n_methods_scanned += 1
    prov = Prov()
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 20000:
        t = clean(cur)
        prov.feed(t)
        for bm in re.finditer(r'\[(e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]', t):
            d = int(bm.group(2), 16)
            if SIZE_LO <= d < SIZE_HI:
                zone = 'base' if d < BASE_HI else 'derived'
                zone_counts[zone] += 1
                h = hist[d]
                h['n'] += 1
                h['cls'][prov.base_cls(bm.group(1))] += 1
                h['sites'].append(hex(cur))
                h['methods'].add(mname)
        cur = idc.next_head(cur, f.end_ea)
        n += 1

hist_out = {}
for d in sorted(hist):
    h = hist[d]
    hist_out[hex(d)] = {'n': h['n'], 'cls': dict(h['cls']),
                        'methods': sorted(h['methods'])[:8],
                        'n_sites': len(h['sites'])}

def gaps_of(keys, min_gap=0x40):
    ds = sorted(keys)
    out = []
    for i in range(1, len(ds)):
        g = ds[i] - ds[i - 1]
        if g >= min_gap:
            out.append({'lo': hex(ds[i - 1]), 'hi': hex(ds[i]), 'gap': hex(g)})
    out.sort(key=lambda x: -int(x['gap'], 16))
    return out

all_keys = [d for d in hist if d >= DERIVED_LO]
this_keys = [d for d in all_keys if hist[d]['cls'].get('THIS', 0) > 0]

# stride 序列检测: 相邻 this-disp 等差 ≥3 连(等差=0x158 即 members_note 344 系)
def stride_series(keys, min_run=3):
    ds = sorted(keys)
    out, i = [], 0
    while i < len(ds) - 1:
        st = ds[i] - (ds[i + 1] - ds[i])   # 序列首(外推一项)
        stp = ds[i + 1] - ds[i]
        if stp <= 0:
            i += 1
            continue
        run = [ds[i]]
        j = i + 1
        while j < len(ds) and ds[j] - run[-1] == stp:
            run.append(ds[j])
            j += 1
        if len(run) >= min_run:
            out.append({'start': hex(run[0]), 'stride': hex(stp),
                        'n': len(run), 'end': hex(run[-1]),
                        'extrapolated_series_start': hex(st),
                        'members': [hex(x) for x in run]})
            i = j
        else:
            i += 1
    return out

disp_histogram = {
    'range': [hex(SIZE_LO), hex(SIZE_HI)],
    'n_methods_scanned': n_methods_scanned,
    'method_addrs': sorted(hex(a) for a in method_addrs),
    'zone_counts': zone_counts,
    'n_unique_disps': len(hist_out),
    'n_unique_disps_derived': len(all_keys),
    'n_unique_disps_this_derived': len(this_keys),
    'hist': hist_out,
    'derived_disp_keys_sorted': [hex(x) for x in sorted(all_keys)],
    'derived_this_disp_keys_sorted': [hex(x) for x in sorted(this_keys)],
    'stride_series_this': stride_series(this_keys),
    'gaps_all_top': gaps_of(all_keys)[:32],
    'gaps_this_top': gaps_of(this_keys)[:32],
    'annotated_members_hit': [
        {'off': hex(int(k, 16)), 'name': v.get('name'),
         'hist_n': hist[int(k, 16)]['n'] if int(k, 16) in hist else 0}
        for k, v in sorted((ANN.get('known_members') or {}).items(),
                           key=lambda kv: int(kv[0], 16))],
}

# ================================================================
# 查3: 洞清单精确化 (census 六洞 × ctor 证据交叉)
# ================================================================
census_row = None
for c in HOLES_CENSUS.get('classes', []):
    if c.get('cls') == 'RoleStatePanel':
        census_row = c
assert census_row, 'RoleStatePanel row missing in struct_holes_20261125.json'

ctor_spans = []
stosd_spans = []
for rec in array_ctls:
    ctor_spans.append({'kind': 'array_eh_ctor', 'lo': rec['offset'],
                       'hi': rec['offset'] + rec['stride'] * rec['count'],
                       'site': rec['site'], 'elem': rec.get('element_class')})
for rs in ctor_decode.get('rep_stosd', []):
    edi = ecx = None
    edi_reg = None
    for ln in rs['window']:
        fm = ln['form']
        lm = re.match(r'^lea\s+edi,\s*\[(e[a-z]{2})\+([0-9A-Fa-f]+)h?\]$', fm)
        if lm:
            edi, edi_reg = int(lm.group(2), 16), lm.group(1)
        mv = re.match(r'^mov\s+edi,\s*(e[a-z]{2})$', fm)
        if mv:
            edi_reg = mv.group(1) if edi is None else edi_reg
        am = re.match(r'^add\s+edi,\s*([0-9A-Fa-f]+)h$', fm)
        if am and edi is None and edi_reg:
            edi = int(am.group(1), 16)
        cm2 = re.match(r'^mov\s+ecx,\s*([0-9A-Fa-f]+)h$', fm)
        if cm2:
            ecx = int(cm2.group(1), 16)
    if edi is not None and ecx:
        stosd_spans.append({'kind': 'rep_stosd', 'lo': edi,
                            'hi': edi + 4 * ecx, 'site': rs['site'],
                            'count': ecx})
ctor_spans.extend(stosd_spans)
tw_disps = TW_FULL

holes_cross = {'census_row': {'size': census_row['size'],
                              'members': census_row['members'],
                              'hole_bytes': census_row['hole_bytes'],
                              'total_holes': census_row['total_holes']},
               'holes': []}
for lo_s, hi_s, nbytes in census_row['holes']:
    lo, hi = int(lo_s, 16), int(hi_s, 16)
    in_arrays = [s for s in ctor_spans if s['kind'] == 'array_eh_ctor'
                 and s['lo'] < hi and lo < s['hi']]
    in_stosd = [s for s in ctor_spans if s['kind'] == 'rep_stosd'
                and s['lo'] < hi and lo < s['hi']]
    in_writes = [hex(x) for x in tw_disps if lo <= x < hi]
    ds = [d for d in hist if lo <= d < hi]
    ds_this = [d for d in ds if hist[d]['cls'].get('THIS', 0) > 0]
    below = max((d for d in hist if d < lo), default=None)
    above = min((d for d in hist if d >= hi), default=None)
    tags = []
    if in_arrays:
        tags.append('ctor_array_span')
    if in_stosd:
        tags.append('ctor_stosd_span')
    if in_writes:
        tags.append('ctor_this_writes')
    if ds:
        tags.append('disp_live')
    if not tags:
        tags.append('zero_evidence')
    holes_cross['holes'].append({
        'range': [lo_s, hi_s], 'bytes': nbytes,
        'ctor_array_spans': [{'span': [hex(s['lo']), hex(s['hi'])],
                              'elem': s['elem'], 'site': s['site']}
                             for s in in_arrays],
        'ctor_stosd_spans': [{'span': [hex(s['lo']), hex(s['hi'])],
                              'count': s['count']} for s in in_stosd],
        'ctor_this_write_disps_in_hole': in_writes[:40],
        'n_ctor_this_writes_in_hole': len(in_writes),
        'hist_unique_disps': len(ds), 'hist_this_unique': len(ds_this),
        'hist_total_n': sum(hist[d]['n'] for d in ds),
        'hist_disps': [hex(x) for x in sorted(ds)][:24],
        'nearest_hist_below_lo': hex(below) if below is not None else None,
        'nearest_hist_above_hi': hex(above) if above is not None else None,
        'tags': tags,
        'placeable': bool(in_arrays or in_stosd or ds),
    })
holes_cross['ctor_evidence_spans'] = [
    {'kind': s['kind'], 'span': [hex(s['lo']), hex(s['hi'])],
     'elem': s.get('elem'), 'site': s['site']} for s in ctor_spans]
holes_cross['summary'] = {
    'n_placeable': sum(1 for h in holes_cross['holes'] if h['placeable']),
    'n_zero_evidence': sum(1 for h in holes_cross['holes'] if not h['placeable']),
}

# ---- ctor 布局图: 构造证据段并查 → 每洞残余未解释子区段 ----
CTOR_SEG_KINDS = ('base_subobject', 'array', 'inplace_obj_152B',
                  'inplace_obj_344B', 'field_write')
ctor_segments = [{'range': ['0x0', hex(BASE_HI)], 'kind': 'base_subobject',
                  'note': ('UIWnd binary_size=68; 直调基构造=??0UIListBox-named '
                           '@this+0 (bases C11 张力: UIListBox.json binary_size=72 '
                           'vs 其 size_evidence 1208 裁决, R3 需调和)')}]
for p in ctor_decode.get('sub_ctor_pairs', []):
    if p['this_disp'] is None or p['target'].startswith('??_L'):
        continue
    disp = int(p['this_disp'], 16)
    if disp == 0 or 'UIListBox@@QAE' in p['target']:
        continue    # 基构造(另行记录)
    if p['target'].startswith('?GetSys@NameSys'):
        ctor_segments.append({'range': [hex(disp), hex(disp + 344)],
                              'kind': 'inplace_obj_344B',
                              'cb': '?GetSys@NameSys-named(0x43a770)',
                              'stride_classes': ['gbRain', 'UIButton', 'UIScene'],
                              'site': p['site']})
    else:
        ctor_segments.append({'range': [hex(disp), hex(disp + 152)],
                              'kind': 'inplace_obj_152B',
                              'cb': 'ResetContainerState(0x4422e0)',
                              'owner': 'UIFrameContainer(A)',
                              'site': p['site']})
for rec in array_ctls:
    ctor_segments.append({'range': rec['span'], 'kind': 'array',
                          'elem': rec['element_class'], 'count': rec['count'],
                          'stride': rec['stride'],
                          'candidate_usable': rec['candidate_usable'],
                          'site': rec['site']})
for disp, nb in WROWS:
    ctor_segments.append({'range': [hex(disp), hex(disp + nb)],
                          'kind': 'field_write', 'bytes': nb})

def merge_cover(segs):
    ivs = sorted((int(s['range'][0], 16), int(s['range'][1], 16))
                 for s in segs if s['kind'] in CTOR_SEG_KINDS)
    out = []
    for lo, hi in ivs:
        if out and lo <= out[-1][1]:
            out[-1][1] = max(out[-1][1], hi)
        else:
            out.append([lo, hi])
    return out

ctor_cover = merge_cover(ctor_segments)
ctor_layout_map = {'segments': sorted(
    ctor_segments,
    key=lambda s: (int(s['range'][0], 16), int(s['range'][1], 16))),
    'ctor_cover_merged': [[hex(a), hex(b)] for a, b in ctor_cover]}
resid_total = 0
for h in holes_cross['holes']:
    lo, hi = int(h['range'][0], 16), int(h['range'][1], 16)
    resid = []
    cur = lo
    for clo, chi in ctor_cover:
        if chi <= cur:
            continue
        if clo > cur:
            resid.append([hex(cur), hex(min(clo, hi))])
        cur = max(cur, chi)
        if cur >= hi:
            break
    if cur < hi:
        resid.append([hex(cur), hex(hi)])
    rb = sum(int(r[1], 16) - int(r[0], 16) for r in resid)
    h['ctor_residual_unexplained'] = {'bytes': rb, 'subranges': resid}
    resid_total += rb
ctor_layout_map['total_residual_unexplained_bytes'] = resid_total
holes_cross['ctor_layout_map'] = ctor_layout_map

# ================================================================
# 查4: C11 bases 证据
# ================================================================
bases_evidence = {'uiwnd_ctor_ea': hex(UIWND_CTOR_EA),
                  'uiwnd_dtor_ea': hex(UIWND_DTOR_EA)}
if ctor_ea != BAD:
    bases_evidence['ctor_first_calls'] = ctor_decode.get('calls', [])[:6]
    bc = ctor_decode.get('base_ctor_calls', [])
    bases_evidence['ctor_calls_uiwnd_ctor'] = bool(bc)
    bases_evidence['ctor_uiwnd_call'] = bc[0] if bc else None
    this_pass = []
    for hl in ctor_decode.get('head_lines', []):
        if re.match(r'^mov\s+ecx,\s*(e[a-z]{2}|ecx)$', hl['form']):
            this_pass.append(hl)
        if 'call' in hl['form']:
            break
    bases_evidence['ctor_this_pass_lines'] = this_pass[:3]
DTOR_EA = 0x4A2450
dtor_calls = []
if is_fn_ea(DTOR_EA):
    dbody = body_lines(DTOR_EA)
    for a, t in dbody:
        if t.startswith('call'):
            cm2 = CALL_RE.match(t)
            tgt = resolve_sym(cm2.group(1)) if cm2 else BAD
            dtor_calls.append({'site': hex(a),
                               'target': (cm2.group(1)[:80] if cm2 else t),
                               'target_ea': hex(tgt) if tgt != BAD else None})
    bases_evidence['dtor_calls_tail'] = dtor_calls[-6:]
    bases_evidence['dtor_calls_uiwnd_dtor'] = any(
        c['target_ea'] == hex(UIWND_DTOR_EA) for c in dtor_calls)
    bases_evidence['dtor_this_pass_lines'] = [
        {'site': hex(a), 'form': t} for a, t in dbody[:10]
        if re.match(r'^mov\s+ecx,\s*(e[a-z]{2}|ecx)$', t)][:3]
try:
    rp_slots = [hex(idc.get_wide_dword(VT + 4 * i)) for i in range(7)]
    ui_slots = [hex(idc.get_wide_dword(UIWND_VT + 4 * i)) for i in range(7)]
    bases_evidence['vtable_fingerprint'] = {
        'rolestatepanel_vt_0x56f040_slots': rp_slots,
        'uiwnd_vt_0x56aec8_slots': ui_slots,
        'slot0_equal': rp_slots[0] == ui_slots[0],
        'slot4_equal': rp_slots[4] == ui_slots[4],
        'inherit_fingerprint': (rp_slots[0] == ui_slots[0]
                                and rp_slots[4] == ui_slots[4]),
    }
except Exception as ex:
    bases_evidence['vtable_fingerprint'] = {'error': str(ex)}
# 4d: 基链直调链 —— ctor 首调 ??0UIListBox@@QAE@XZ (this-form, offset 0)
UILB_CTOR_EA = idc.get_name_ea_simple('??0UIListBox@@QAE@XZ')
bases_evidence['ctor_first_call_is_uiListBox_ctor'] = None
bases_evidence['uilib_ct'] = {}
if UILB_CTOR_EA != BAD:
    bases_evidence['ctor_first_call_is_uiListBox_ctor'] = any(
        c.get('target_ea') == hex(UILB_CTOR_EA)
        for c in ctor_decode.get('calls', []))
    lb = {'ea': hex(UILB_CTOR_EA)}
    lf = ida_funcs.get_func(UILB_CTOR_EA)
    if lf:
        lb['func_range'] = [hex(lf.start_ea), hex(lf.end_ea)]
        lbody = body_lines(UILB_CTOR_EA)
        lb['head_calls'] = []
        lb['calls_uiwnd_ctor'] = False
        lb['vt_installs'] = []
        for a, t in lbody:
            if t.startswith('call'):
                cm3 = CALL_RE.match(t)
                tg3 = resolve_sym(cm3.group(1)) if cm3 else BAD
                lb['head_calls'].append({'site': hex(a),
                                         'target': cm3.group(1)[:60] if cm3 else t,
                                         'is_uiwnd_ctor': tg3 == UIWND_CTOR_EA})
                if tg3 == UIWND_CTOR_EA:
                    lb['calls_uiwnd_ctor'] = True
            vm3 = re.match(r'^mov\s+(?:dword ptr\s+)?\[(e[a-z]{2})\],\s*offset\s+(\S+)', t)
            if vm3:
                lb['vt_installs'].append({'site': hex(a), 'vt': vm3.group(2)[:48]})
        lb['head_calls'] = lb['head_calls'][:8]
    try:
        lb_slots = [hex(idc.get_wide_dword(0x56AD20 + 4 * i)) for i in range(7)]
        lb['vtable_0x56ad20_slots'] = lb_slots
        lb['vt_slot0_eq_uiwnd'] = lb_slots[0] == ui_slots[0]
        lb['vt_slot4_eq_uiwnd'] = lb_slots[4] == ui_slots[4]
    except Exception as ex:
        lb['vtable_error'] = str(ex)
    lb_ann_path = os.path.join(STRUCTS_DIR, 'UIListBox.json')
    if os.path.exists(lb_ann_path):
        lb_ann = json.load(open(lb_ann_path, encoding='utf-8'))
        lb['annotation_binary_size'] = lb_ann.get('binary_size')
        lb['annotation_bases'] = lb_ann.get('bases')
        lb['annotation_size_evidence_head'] = (lb_ann.get('size_evidence') or '')[:220]
    bases_evidence['uilib_ct'] = lb
# 4e: dtor 全调用链找基析构 (UIListBox/UIWnd)
bases_evidence['dtor_chain_names'] = sorted(set(
    c['target'].split('(')[0] for c in dtor_calls))[:24]
bases_evidence['dtor_calls_uilib_dtor'] = any(
    '??1UIListBox' in c['target'] for c in dtor_calls)

# ================================================================
# 查5: UIWnd 基类尺寸 + [0,0x44) 覆盖
# ================================================================
def type_size(t):
    if t is None:
        return None
    t = t.strip()
    m = re.match(r'^(.+?)\[(\d+)\]$', t)
    if m:
        base = type_size(m.group(1))
        return base * int(m.group(2)) if base else None
    if t.endswith('*'):
        return 4
    tbl = {'int': 4, 'unsigned int': 4, 'long': 4, 'unsigned long': 4,
           'float': 4, 'BOOL': 4, 'char': 1, 'unsigned char': 1, 'bool': 1,
           'short': 2, 'unsigned short': 2, 'double': 8, 'tagRECT': 16,
           'gbColorQuad': 4}
    if t in tbl:
        return tbl[t]
    p = os.path.join(STRUCTS_DIR, t + '.json')
    if os.path.exists(p):
        try:
            return json.load(open(p, encoding='utf-8')).get('binary_size')
        except Exception:
            return None
    return None

uiwnd_members = []
covered = []
for k, v in sorted((UIWND.get('known_members') or {}).items(),
                   key=lambda kv: int(kv[0], 16)):
    off = int(k, 16)
    sz = type_size(v.get('type'))
    uiwnd_members.append({'off': hex(off), 'name': v.get('name'),
                          'type': v.get('type'), 'size': sz})
    if sz:
        covered.append((off, off + sz))
covered.sort()
gaps = []
curpos = 4   # vptr [0,4) 豁免(多态确证), 不计洞
for lo, hi in covered:
    if lo > curpos:
        gaps.append([hex(curpos), hex(lo)])
    curpos = max(curpos, hi)
if curpos < BASE_HI:
    gaps.append([hex(curpos), hex(BASE_HI)])
base_hit = {hex(d): {'n': hist[d]['n'],
                     'cls': dict(hist[d]['cls']),
                     'methods': sorted(hist[d]['methods'])[:6]}
            for d in sorted(hist) if d < BASE_HI}
uiwnd_size = {
    'uiwnd_binary_size': UIWND['binary_size'],
    'base_subobject': [hex(BASE_LO), hex(BASE_HI)],
    'uiwnd_members': uiwnd_members,
    'coverage_gaps_in_base': gaps,
    'vptr_exempt': ['0x0', '0x4'],
    'fully_covered': not gaps,
    'rolestatepanel_disp_in_base': base_hit,
}

# ================================================================
# 汇总落盘
# ================================================================
report = {
    'meta': {
        'tool': 'tools/probe_rolestatepanel_layout_20261126.py',
        'db': 'original/PAL3.exe.i64', 'run_auto_analysis': False,
        'date': '2026-11-26',
        'class': 'RoleStatePanel', 'binary_size': SIZE,
        'method': ('R3 五查: ①ctor 全量解码(??_L 五参=R2 九数组同法 '
                   'probe_equipui_arrays_20261126) ②全方法 disp 直方图(Prov this/subptr '
                   '溯源, probe_equipui_tail_20261126 同法) ③census 六洞交叉 ④C11 bases '
                   '证据(ctor/dtor 基构造直调+表字节指纹) ⑤UIWnd 基类尺寸覆盖'),
        'inputs': ['data/annotations/structs/RoleStatePanel.json',
                   'data/annotations/structs/UIWnd.json',
                   'data/status/struct_holes_20261125.json'],
    },
    'alloc_chain': alloc_chain,
    'ctor_identity': ctor_identity,
    'ctor_decode': ctor_decode,
    'array_ctls': array_ctls,
    'disp_histogram': disp_histogram,
    'holes_cross': holes_cross,
    'bases_evidence': bases_evidence,
    'uiwnd_size': uiwnd_size,
}
os.makedirs(os.path.dirname(OUT), exist_ok=True)
with open(OUT, 'w', encoding='utf-8') as fh:
    json.dump(report, fh, ensure_ascii=False, indent=1)

# ---------------- stdout 摘要 ----------------
print('== 分配链 ==')
print(json.dumps({k: v for k, v in alloc_chain.items()
                  if k != 'new_ctx'}, ensure_ascii=False))
print('== ctor 身份 ==')
print(' ??0RoleStatePanel 存在:', ctor_identity['mangled_ctor_exists'],
      '| InitUI sym:', ctor_identity['initui_sym_ea'],
      '| xrefs:', [(x['site'], x['caller'][:40]) for x in ctor_identity.get('ctor_xrefs', [])])
print('== 查1 ctor 解码 ==')
print(' 指令数 %s | this写 %s (min=%s max=%s) | 基构造直调 %s | vtable装 %s' % (
    ctor_decode.get('n_instructions'), ctor_decode.get('n_this_writes'),
    ctor_decode.get('this_write_min'), ctor_decode.get('this_write_max'),
    bool(ctor_decode.get('base_ctor_calls')),
    [v['vt_name'][:40] for v in ctor_decode.get('vtable_installs', [])]))
print(' rep stosd:', len(ctor_decode.get('rep_stosd', [])),
      json.dumps([{'span': [hex(s['lo']), hex(s['hi'])], 'n': s['count']}
                  for s in ctor_spans if s['kind'] == 'rep_stosd']))
print('== 数组构造 (%d) ==' % len(array_ctls))
for r in array_ctls:
    print('  off=%s cnt=%-3d str=%-5s span=%s elem=%-14s verdict=%s stride_classes=%s' % (
        hex(r['offset']), r['count'], r['stride'], r['span'],
        r['element_class'], r['annotation_match']['verdict'],
        r.get('stride_classes')))
print('== ctor 子对象构造对 (this_disp) ==')
print(' ', [(p['site'], p['this_disp'], p['target'][:36])
            for p in ctor_decode.get('sub_ctor_pairs', [])
            if p['this_disp'] is not None][:24])
print('== 查2 disp 普查 ==')
print(' 方法 %d | 唯一 disp %d (derived %d, this %d) | zone %s' % (
    n_methods_scanned, len(hist_out), len(all_keys), len(this_keys), zone_counts))
print('== 查3 六洞交叉 ==')
for h in holes_cross['holes']:
    print('  %s..%s (%6dB) tags=%s arr=%d stosd=%d disp=%d writes=%d' % (
        h['range'][0], h['range'][1], h['bytes'], ','.join(h['tags']),
        len(h['ctor_array_spans']), len(h['ctor_stosd_spans']),
        h['hist_unique_disps'], h['n_ctor_this_writes_in_hole']))
print('== 查4 bases ==')
print(' ctor→UIWnd ctor:', bases_evidence.get('ctor_calls_uiwnd_ctor'),
      bases_evidence.get('ctor_uiwnd_call'))
print(' ctor 首调 UIListBox ctor:', bases_evidence.get('ctor_first_call_is_uiListBox_ctor'))
lb = bases_evidence.get('uilib_ct', {})
print(' UIListBox ctor:', lb.get('ea'), '| calls ??0UIWnd:', lb.get('calls_uiwnd_ctor'),
      '| vt装:', [v['vt'][:30] for v in lb.get('vt_installs', [])])
print(' UIListBox vt slot0/4 eq UIWnd:', lb.get('vt_slot0_eq_uiwnd'),
      lb.get('vt_slot4_eq_uiwnd'), '| ann binary_size:', lb.get('annotation_binary_size'),
      '| bases:', lb.get('annotation_bases'))
print(' dtor→UIWnd dtor:', bases_evidence.get('dtor_calls_uiwnd_dtor'),
      '| dtor→UIListBox dtor:', bases_evidence.get('dtor_calls_uilib_dtor'))
fp = bases_evidence.get('vtable_fingerprint', {})
print(' 表指纹 slot0=%s slot4=%s inherit=%s' % (
    fp.get('slot0_equal'), fp.get('slot4_equal'), fp.get('inherit_fingerprint')))
print('== 查2 stride 序列 ==')
for s in disp_histogram['stride_series_this']:
    print(' ', json.dumps({k: s[k] for k in
                           ('start', 'stride', 'n', 'end')}))
print('== 查5 UIWnd ==')
print(' binary_size=%d [0,0x%x) gaps=%s base_disp_hit=%d' % (
    UIWND['binary_size'], BASE_HI, gaps, len(base_hit)))
print('written:', OUT)
idapro.close_database(False)
