#!/usr/bin/env python3
"""probe_equipui_arrays_20261126.py — Task 1(R2): 九数组元素类鉴定探针。

背景: EquipUI ctor(0x498820) 内联 9 笔 ??_L 原位数组构造铺满尾区
      [0x1414,0x40FC4)。??_L@YGXPAXIHP6EX0@Z1@Z = eh vector ctor iterator
      (void *ptr, unsigned size, int count, void(*ctor)(void*), void(*dtor)(void*)),
      stdcall 右起压栈序: dtor, ctor, count, size, ptr。
      SceneBuf 先例: ctor 回调函数名 = 元素类名钥匙 (?Reset@SystemUI@@ → SystemUI)。
做法: 前向扫 ??0EquipUI 全函数, 精确压栈模型 (push imm / push offset / push reg /
      lea reg,[base+disp] / call 清栈), 每个 ??_L 现场解五参 →
      ctor_ea/ctor_name/dtor_ea/dtor_name, 反 mangle + 注解 corpus 反查地址主人得类名,
      与 data/annotations/structs/<类名>.json binary_size==stride 对账。
产出: data/status/probe_equipui_arrays_20261126.json
"""
import sys, os, json, re, glob
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs

ROOT = '/home/peng/workspace/PAL3Decomp'
OUT = ROOT + '/data/status/probe_equipui_arrays_20261126.json'
STRUCTS_DIR = ROOT + '/data/annotations/structs'

CTOR_EA = idc.get_name_ea_simple('??0EquipUI@@QAE@XZ')
HELPER = '??_L@YGXPAXIHP6EX0@Z1@Z'
HELPER_EA = idc.get_name_ea_simple(HELPER)
assert CTOR_EA != idc.BADADDR, 'EquipUI ctor not found'
assert HELPER_EA != idc.BADADDR, '??_L helper not found'

# 九笔既知 (offset,count,stride) — 侦查探针 data/status/probe_equipui_tail_20261126.json。
# 注意 0x2D3F0 一笔乘积同值 (12*152==152*12), 任务书转写为 (152,0xC) 系转置;
# 以 ABI 压栈序为准: 第3推=count, 第4推=size。
EXPECT = [
    (0x1414, 128, 584),
    (0x13814, 128, 584),
    (0x261F8, 5, 0x131C),
    (0x2C48C, 6, 0x158),
    (0x2CC9C, 6, 0xF8),
    (0x2D3F0, 152, 0xC),
    (0x2F760, 5, 52),
    (0x2FE04, 60, 584),
    (0x386E4, 60, 584),
]

# ---------- 注解 corpus 反查索引: ea -> [(class, method_name, evidence_level)] ----------
CORPUS = {}
ANN_CACHE = {}
for p in glob.glob(os.path.join(STRUCTS_DIR, '*.json')):
    cls = os.path.basename(p)[:-5]
    try:
        d = json.load(open(p, encoding='utf-8'))
    except Exception:
        continue
    ANN_CACHE[cls] = d
    for a, m in (d.get('methods') or {}).items():
        try:
            ea = int(a, 16)
        except Exception:
            continue
        CORPUS.setdefault(ea, []).append(
            (cls, m.get('name'), (m.get('evidence_level') or '')))

def corpus_owner(ea):
    claims = CORPUS.get(ea, [])
    if len(claims) == 1:
        return {'class': claims[0][0], 'method': claims[0][1],
                'evidence_level': claims[0][2], 'n_claims': 1}
    if claims:
        return {'class': None, 'method': None, 'n_claims': len(claims),
                'claims': [(c[0], c[1]) for c in claims]}
    return {'class': None, 'method': None, 'n_claims': 0}

def clean(ea):
    return (idc.generate_disasm_line(ea, 0) or '').split(';')[0].strip()

LONG_DN = idc.get_inf_attr(idc.INF_LONG_DN)

def demangle(name):
    d = idc.demangle_name(name, LONG_DN)
    return d or name

def class_from_mangled(m):
    """mangled → 所属类: ??0X@@/??1X@@/??_GX@@ → X; ?Fn@Cls@@ → Cls;
    ?Fn@Cls@Ns@@ → Cls(最内层); 非成员符号(裸名) → None"""
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
    parts = t.split('@')
    chain = []
    for p in parts[1:]:          # '@@' 终止符 = 第一个空段, 截断
        if p == '':
            break
        chain.append(p)
    return chain[-1] if chain else None

def resolve_sym(tok):
    tok = tok.strip()
    return idc.get_name_ea_simple(tok)

IMM_RE = re.compile(r'^push\s+((?:0[0-9A-Fa-f]*|[0-9A-Fa-f]+)h|[0-9]+)$')
SYM_RE = re.compile(r'^push\s+offset\s+(\S+)$')
REG_RE = re.compile(r'^push\s+(e[a-z]{2}|cx|c[sd]s)$')
LEA_RE = re.compile(r'^lea\s+(e[a-z]{2}),\s*\[(e[a-z]{2}|\w+)\+([0-9A-Fa-f]+)h?\]$')
MOVDST_RE = re.compile(r'^(?:mov|xor|add|sub|and|or|pop|inc|dec|neg|not)\s+(e[a-z]{2}|cx)\b')
CALL_RE = re.compile(r'^call\s+(\S+)')

def body_lines(ea, limit=20000):
    f = ida_funcs.get_func(ea)
    assert f, 'no func at %s' % hex(ea)
    out, cur, n = [], f.start_ea, 0
    while cur < f.end_ea and n < limit:
        out.append((cur, clean(cur)))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    return out

def is_fn_ea(v):
    if v is None or v == idc.BADADDR:
        return False
    f = ida_funcs.get_func(v)
    return f is not None and f.start_ea == v

# ---------- 前向压栈模型扫描 ----------
pending = []   # 程序序 push: ('imm',v) / ('fn',ea,mangled) / ('ptr',disp) / ('reg',name)
regmodel = {}  # reg → ('thisdisp', disp)
arrays = []
recent = []    # 最近 8 行现场(审计用)

for a, t in body_lines(CTOR_EA):
    recent.append((hex(a), t))
    recent = recent[-8:]
    cm = CALL_RE.match(t)
    if cm:
        tgt_ea = resolve_sym(cm.group(1))
        if tgt_ea == HELPER_EA or HELPER in cm.group(1):
            rec = {'site': hex(a), 'n_pending': len(pending),
                   'push_window': list(recent)}
            if len(pending) >= 5:
                d5 = pending[-5:]     # 程序序尾五 = [dtor, ctor, count, size, ptr]
                k_dt, k_ct, k_cnt, k_sz, k_ptr = d5
                ok = (k_dt[0] == 'fn' and k_ct[0] == 'fn'
                      and k_cnt[0] == 'imm' and k_sz[0] == 'imm'
                      and k_ptr[0] in ('ptr', 'imm'))
                rec['stack_form_ok'] = ok
                if ok:
                    disp, count, size = k_ptr[1], k_cnt[1], k_sz[1]
                    ctor_ea, ctor_m = k_ct[1], k_ct[2]
                    dtor_ea, dtor_m = k_dt[1], k_dt[2]
                    rec.update({
                        'offset': disp, 'count': count, 'stride': size,
                        'ctor_ea': hex(ctor_ea), 'ctor_name': ctor_m,
                        'ctor_class_mangled': class_from_mangled(ctor_m),
                        'dtor_ea': hex(dtor_ea), 'dtor_name': dtor_m,
                        'dtor_class_mangled': class_from_mangled(dtor_m),
                        'span_end': hex(disp + size * count),
                    })
                    arrays.append(rec)
            else:
                rec['stack_form_ok'] = False
            arrays_trace = rec
            pending = []
            regmodel = {}
        else:
            pending = []
            for r in ('eax', 'ecx', 'edx'):
                regmodel.pop(r, None)
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
        pending.append(('fn', ea2 if ea2 != idc.BADADDR else None, m.group(1)))
        continue
    m = LEA_RE.match(t)
    if m:
        regmodel[m.group(1)] = ('thisdisp', int(m.group(3), 16))
        continue
    m = REG_RE.match(t)
    if m:
        r = m.group(1)
        if r in regmodel and regmodel[r][0] == 'thisdisp':
            pending.append(('ptr', regmodel[r][1]))
        else:
            pending.append(('reg', r))
        continue
    md = MOVDST_RE.match(t)
    if md:
        regmodel.pop(md.group(1), None)
        continue
    if t.startswith('pop ') or t.startswith('add esp') or t.startswith('mov esp'):
        pending = []

# ---------- 类名钥匙定夺 + 注解对账 ----------
DISP_RE = re.compile(r'\[e[a-z]{2}\+([0-9A-Fa-f]+)h?\]')

def cb_field_extent(ea):
    """回调函数体内 [reg+disp] 最大位移 → 元素字段足迹佐证"""
    f = ida_funcs.get_func(ea)
    if not f:
        return None
    mx = -1
    cur = f.start_ea
    while cur < f.end_ea:
        t = clean(cur)
        for m in DISP_RE.finditer(t):
            mx = max(mx, int(m.group(1), 16))
        cur = idc.next_head(cur, f.end_ea)
    return mx

def ann_of(cls):
    d = ANN_CACHE.get(cls)
    if d is None:
        return None
    return {'annotation': True, 'binary_size': d.get('binary_size'),
            'base_size': d.get('base_size')}

def finish(rec, e_off, e_cnt, e_str):
    stride = rec['stride']
    # corpus 反查主人类(权威, 含裸名符号); mangle 解析为备援
    ct_own = corpus_owner(int(rec['ctor_ea'], 16))
    dt_own = corpus_owner(int(rec['dtor_ea'], 16))
    rec['ctor_owner'] = ct_own
    rec['dtor_owner'] = dt_own
    rec['ctor_class'] = ct_own.get('class') or rec['ctor_class_mangled']
    rec['dtor_class'] = dt_own.get('class') or rec['dtor_class_mangled']
    rec['ctor_demangled'] = demangle(rec['ctor_name'])
    rec['dtor_demangled'] = demangle(rec['dtor_name'])
    rec['callback_owners_agree'] = (
        rec['ctor_class'] is not None and
        rec['ctor_class'] == rec['dtor_class'])

    rec['expect_check'] = {
        'offset_ok': rec['offset'] == e_off,
        'count_ok': rec['count'] == e_cnt,
        'stride_ok': rec['stride'] == e_str,
        'expect': {'offset': hex(e_off), 'count': e_cnt, 'stride': e_str},
    }
    if rec['count'] == e_str and rec['stride'] == e_cnt and not (
            rec['count'] == e_cnt and rec['stride'] == e_str):
        rec['expect_check']['note'] = ('expect 的 count/stride 互为转置 '
                                       '(乘积相同, 以 ABI 压栈序第3推=count/第4推=size 为准)')

    a_ct, a_dt = ann_of(rec['ctor_class']), ann_of(rec['dtor_class'])
    for side, ann in (('ctor', a_ct), ('dtor', a_dt)):
        if ann is not None:
            ann['stride_equal'] = (ann.get('binary_size') == stride)
    verdict = 'none'
    ct_ok = a_ct is not None and a_ct.get('stride_equal')
    dt_ok = a_dt is not None and a_dt.get('stride_equal')
    if ct_ok and dt_ok:
        verdict = 'both'
    elif ct_ok:
        verdict = 'ctor'
    elif dt_ok:
        verdict = 'dtor'
    rec['annotation_match'] = {'ctor': a_ct, 'dtor': a_dt, 'verdict': verdict}
    if verdict in ('ctor', 'both'):
        rec['element_class_candidate'] = rec['ctor_class']  # SceneBuf 先例: ctor 回调类名是钥匙
        rec['candidate_usable'] = True
        rec['candidate_basis'] = 'ctor_callback_owner'
    elif verdict == 'dtor':
        rec['element_class_candidate'] = rec['dtor_class']
        rec['candidate_usable'] = True
        rec['candidate_basis'] = 'dtor_callback_owner'
    else:
        rec['element_class_candidate'] = 'unknown'
        rec['candidate_usable'] = False
        rec['candidate_basis'] = None

    notes = []
    if idc.print_insn_mnem(int(rec['dtor_ea'], 16)) == 'retn':
        notes.append('dtor 回调为空函数(retn)= no-op 析构, 其类名钥匙弱')
    if 'PAV' in rec['ctor_name'] or 'CPAV' in rec['ctor_name']:
        notes.append('ctor 回调签名带返回指针(非 void(void*) 形态), 名字钥匙存疑')
    if verdict == 'none' and rec['callback_owners_agree']:
        bs = (a_ct or a_dt or {}).get('binary_size')
        notes.append('双回调同主类(强类名信号)但 binary_size(%s)!=stride(%d), 差 %+d 字节, '
                     'Task2 需尺寸调和' % (bs, stride, (bs or 0) - stride))
    # ctor 回调字段足迹佐证
    ext = cb_field_extent(int(rec['ctor_ea'], 16))
    if ext is not None:
        fit = (ext + 4) <= stride
        rec['ctor_cb_max_this_disp'] = hex(ext)
        rec['ctor_cb_extent_fits_stride'] = fit
        if fit:
            notes.append('ctor 回调字段足迹 [0..0x%X) ⊆ stride(%d), 佐证元素尺寸' % (ext + 4, stride))
        else:
            notes.append('ctor 回调字段足迹 0x%X 超出 stride(%d), 名字/尺寸需复核' % (ext + 4, stride))
    rec['notes'] = notes

ctor_f = ida_funcs.get_func(CTOR_EA)
report = {
    'meta': {
        'tool': 'tools/probe_equipui_arrays_20261126.py',
        'db': 'original/PAL3.exe.i64',
        'date': '2026-11-26',
        'ctor_ea': hex(CTOR_EA),
        'ctor_range': [hex(ctor_f.start_ea), hex(ctor_f.end_ea)],
        'helper': HELPER, 'helper_ea': hex(HELPER_EA),
        'method': 'forward push-model scan of ??0EquipUI; ??_L stdcall args '
                  '(ptr,size,count,ctor,dtor) pushed right-to-left: '
                  'push dtor; push ctor; push count; push size; push ptr; call ??_L',
        'class_key_rule': 'SceneBuf 先例: ctor 回调函数名主人类 = 元素类钥匙; '
                          'usable 判据 = 注解存在且 binary_size==stride',
        'expect_basis': 'data/status/probe_equipui_tail_20261126.json 九笔 (offset,count,stride)',
    },
    'n_helper_calls_found': len(arrays),
    'arrays': [],
}

for rec, (e_off, e_cnt, e_str) in zip(arrays, EXPECT):
    finish(rec, e_off, e_cnt, e_str)

# 邻接自检
for i, rec in enumerate(arrays):
    adj = []
    if i + 1 < len(arrays) and arrays[i + 1]['offset'] == int(rec['span_end'], 16):
        adj.append('next_starts_at_span_end')
    if i > 0 and int(arrays[i - 1]['span_end'], 16) == rec['offset']:
        adj.append('starts_at_prev_span_end')
    rec['adjacency'] = adj

report['arrays'] = arrays
report['expect_summary'] = {
    'all_offset_match': all(r['expect_check']['offset_ok'] for r in arrays),
    'all_count_match': all(r['expect_check']['count_ok'] for r in arrays),
    'all_stride_match': all(r['expect_check']['stride_ok'] for r in arrays),
}

os.makedirs(os.path.dirname(OUT), exist_ok=True)
with open(OUT, 'w', encoding='utf-8') as fh:
    json.dump(report, fh, ensure_ascii=False, indent=1)
print('sites found:', len(arrays))
print('expect:', json.dumps(report['expect_summary']))
for r in arrays:
    print('%s off=%s cnt=%-3d str=%-5d ctor=%-18s dtor=%-18s cand=%-16s verdict=%s %s' % (
        r['site'], r['offset'], r['count'], r['stride'], str(r['ctor_class']),
        str(r['dtor_class']), r['element_class_candidate'],
        r['annotation_match']['verdict'], '; '.join(r['notes'])))
print('written:', OUT)
