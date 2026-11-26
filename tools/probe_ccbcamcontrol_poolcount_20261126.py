#!/usr/bin/env python3
"""probe_ccbcamcontrol_poolcount_20261126.py — 池计数取证。
三查: ①池初始化函数族的 0x7D0/2000 字面量(push/cmp/mov imm)
②句柄表区 [0x64190,0x68FB0) 的 -1 哨兵与上界 cmp 常量
③m_nCurList/m_nCurTask@0x68FD0/D4 写入点的常量上界
归因规则 v1(机器层, 本脚本自动产出): literal_hits 仅当命中函数 ∈ 池方法族
(含 0x506020/0x4a8770/0x5058f0)或为该族某函数的直接调用者时,
才计为池证据(pool_evidence)。
归因规则 v2(复核门①裁定, 手工落账): 池对象(=CCBCamControl this)的
init/持久化/分配路径上的字面量均属池证据; 判定需双条件——
接收者=池对象 且 字面量参与 2000 迭代结构。
落账注意: 报告 JSON 的 pool_count_evidence(v2 层)为手工裁定产物; 本脚本重跑
只会重写 v1 机器层(hits/counts/pool_count_evidence_detail), v2 层须按报告
task-1-report fix round 1 重录, 勿以重跑输出直接覆盖。
判定: pool_count_evidence ∈ {"literal":"0x7D0"} | {"bound":N} | {"unresolved":true}
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64', run_auto_analysis=False)
import idc, ida_funcs, idautils
OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_poolcount_20261126.json'
TARGETS = {0x5075e0:'InsertTaskToList', 0x507b20:'SwapTask', 0x508190:'ClearList',
           0x5061a0:'Init', 0x506020:'Create', 0x44d780:'InitEntries',
           0x4a6f10:'CCCTData_6F10', 0x4a8770:'Create_8770', 0x5058f0:'copyctor_58f0'}
TBL_LO, TBL_HI = 0x64190, 0x68FB0          # 句柄表区
CUR_OFFS = (0x68FD0, 0x68FD4)              # m_nCurList / m_nCurTask

report = {'literal_hits': [], 'bound_hits': [], 'table_sentinel': [],
          'curfield_hits': [], 'table_ctx_funcs': []}

# ---- 池方法族解析 + 直接调用者集合(xref) ----
pool_family_eas, pool_family_info = set(), {}
for ea, label in TARGETS.items():
    f = ida_funcs.get_func(ea)
    if f is None:
        pool_family_info[hex(ea)] = {'label': label, 'resolved': False}
        continue
    start = f.start_ea
    pool_family_eas.add(start)
    pool_family_info[hex(ea)] = {'label': label, 'resolved': True,
        'start': hex(start), 'name': idc.get_func_name(start)}
pool_caller_eas, pool_callsites = set(), []
for ea, label in TARGETS.items():
    for ref in idautils.CodeRefsTo(ea, 0):
        f = ida_funcs.get_func(ref)
        if f is None or f.start_ea in pool_family_eas:
            continue
        pool_caller_eas.add(f.start_ea)
        if len(pool_callsites) < 60:
            pool_callsites.append({'callee': label, 'caller': idc.get_func_name(f.start_ea),
                                   'caller_ea': hex(f.start_ea), 'site': hex(ref)})

# ---- 行内十六进制/十进制数值 token 提取 ----
num_tok = re.compile(r'\b([0-9A-Fa-f]{1,6})(h?)\b')
def nums_in(text):
    """[(span, value)] — 带h按16进制, 否则按10进制; 6位以上(地址形)不取。"""
    out = []
    for m in num_tok.finditer(text):
        s = m.group(1)
        v = int(s, 16) if m.group(2) else (int(s, 10) if s.isdigit() else None)
        if v is not None:
            out.append((m.span(), v))
    return out

def in_spans(pos, spans):
    return any(a <= pos < b for a, b in spans)

mem_ctx = re.compile(r'\[[^\]]*\]|ds:\w+_(?=[0-9A-Fa-f]{5})')  # 内存操作数上下文
LIT_VAL = re.compile(r'\b(7D0h|2000)\b')

nfam, ncalls, nfunc = len(pool_family_eas), len(pool_caller_eas), 0
print('pool_family resolved: %d/9, direct callers: %d' % (nfam, ncalls), file=sys.stderr)

for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f: continue
    cn = idc.get_func_name(f.start_ea)
    is_fam = f.start_ea in pool_family_eas
    is_caller = f.start_ea in pool_caller_eas
    table_ctx = False
    fn_bound, fn_cur = [], []
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 5000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        mems = [m.span() for m in mem_ctx.finditer(t)]
        # 该函数是否触碰句柄表区 / cur 字段(内存操作数中的区间偏移)
        for span, v in nums_in(t):
            if not in_spans(span[0], mems): continue
            if TBL_LO <= v < TBL_HI: table_ctx = True
            if v in CUR_OFFS:
                lm = re.search(r'\b(mov|cmp)\b', t)
                vm = re.search(r',\s*(-?(?:[0-9A-Fa-f]+h?))\s*$', t)
                if lm and vm:
                    s = vm.group(1)
                    val = int(s[:-1], 16) if s.endswith('h') else int(s, 10)
                    fn_cur.append(
                        {'func': cn, 'site': hex(cur), 'off': hex(v), 'val': val, 'line': t})
        # ① 0x7D0/2000 字面量(brief 原样 regex; imm=值不在内存操作数内)
        for m in LIT_VAL.finditer(t):
            tok = m.group(1)
            imm = not in_spans(m.start(1), mems)
            report['literal_hits'].append({'func': cn, 'site': hex(cur), 'token': tok,
                'imm': imm, 'pool_family': is_fam, 'caller_of_pool': is_caller,
                'pool_evidence': is_fam or is_caller, 'line': t})
        # ② cmp 上界(brief 原样 regex; table_ctx 在函数级定稿)
        m = re.search(r'cmp\s+e?[a-z]{2},\s*([0-9A-Fa-f]{1,4})h', t)
        if m:
            v = int(m.group(1), 16)
            if 32 <= v <= 4096:
                fn_bound.append({'func': cn, 'site': hex(cur), 'val': v,
                    'pool_family': is_fam, 'caller_of_pool': is_caller, 'line': t})
        # ② 句柄表区 -1 哨兵写入
        if t.startswith('mov') and mems and re.search(r',\s*(0FFFFFFFFh|-1)\b', t):
            for span, v in nums_in(t):
                if in_spans(span[0], mems) and TBL_LO <= v < TBL_HI:
                    report['table_sentinel'].append({'func': cn, 'site': hex(cur), 'line': t})
                    break
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    if table_ctx:
        for h in fn_bound: h['table_ctx'] = True
        report['table_ctx_funcs'].append({'ea': hex(f.start_ea), 'name': cn})
    for h in fn_bound:
        h.setdefault('table_ctx', False)
        report['bound_hits'].append(h)
    report['curfield_hits'].extend(fn_cur)
    nfunc += 1
    if nfunc % 2000 == 0:
        print('  ...%d funcs scanned' % nfunc, file=sys.stderr)

# ---- Step 1.3 判定 ----
detail = {'rule': 'literal: 池方法族或其直接调用者的 imm 0x7D0/2000; '
                  'bound: 句柄表区访问同函数的 cmp val==2000'}
ev_lit = [h for h in report['literal_hits'] if h['pool_evidence'] and h['imm']]
ev_bd  = [h for h in report['bound_hits'] if h['table_ctx'] and h['val'] == 2000]
cur2000 = [h for h in report['curfield_hits'] if h['val'] == 2000]
if ev_lit:
    evidence = {'literal': '0x7D0'}
    first = ev_lit[0]
    detail.update(kind='literal', site=first['site'], func=first['func'],
                  hits=len(ev_lit),
                  samples=[{k: h[k] for k in ('func', 'site', 'line')} for h in ev_lit[:10]])
elif ev_bd:
    evidence = {'bound': 2000}
    detail.update(kind='bound', val=2000, hits=len(ev_bd),
                  samples=[{k: h[k] for k in ('func', 'site', 'line')} for h in ev_bd[:10]])
else:
    evidence = {'unresolved': True}
    detail.update(kind='unresolved',
                  curfield_2000_hits=len(cur2000),
                  curfield_samples=[{k: h[k] for k in ('func', 'site', 'off', 'val', 'line')}
                                    for h in cur2000[:10]])

report.update({
    'probe': 'probe_ccbcamcontrol_poolcount_20261126',
    'date': '2026-11-26',
    'db': 'original/PAL3.exe.i64',
    'pool_family': pool_family_info,
    'pool_callers_count': ncalls,
    'pool_callsites': pool_callsites,
    'counts': {
        'functions_scanned': nfunc,
        'literal_hits': len(report['literal_hits']),
        'literal_imm': sum(1 for h in report['literal_hits'] if h['imm']),
        'literal_pool_evidence': len(ev_lit),
        'bound_hits': len(report['bound_hits']),
        'bound_table_ctx': len(ev_bd),
        'bound_val2000': sum(1 for h in report['bound_hits'] if h['val'] == 2000),
        'table_sentinel': len(report['table_sentinel']),
        'curfield_hits': len(report['curfield_hits']),
        'curfield_val2000': len(cur2000),
        'table_ctx_funcs': len(report['table_ctx_funcs']),
    },
    'pool_count_evidence': evidence,
    'pool_count_evidence_detail': detail,
})
# v2 层(pool_count_evidence)为手工裁定产物, 不由本脚本产出; 此 dump 仅重写 v1
# 机器层, 重跑后 v2 需按 task-1-report fix round 1 重录回填。
json.dump(report, open(OUT, 'w'), indent=1)
print('literal_hits:', len(report['literal_hits']),
      '(imm:', report['counts']['literal_imm'],
      ', pool_evidence:', len(ev_lit), ')')
print('bound_hits:', len(report['bound_hits']),
      '(table_ctx:', len(ev_bd), ')')
print('table_sentinel:', len(report['table_sentinel']),
      'curfield_hits:', len(report['curfield_hits']),
      'table_ctx_funcs:', len(report['table_ctx_funcs']))
print('pool_count_evidence:', json.dumps(evidence))
idapro.close_database(False)
