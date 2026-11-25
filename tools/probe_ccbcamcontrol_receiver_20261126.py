#!/usr/bin/env python3
"""probe_ccbcamcontrol_receiver_20261126.py — 孪生案开放案①: 接收者 ecx 回溯。

裁决单体 430KB vs 对话框+池两对象:
  对 CCCTData 全部 22 方法 + CCBCamControl 全部 33 方法枚举调用点,
  回溯 ecx 装载形(anchor_boundary_audit 查一模式: 反扫 ≤24 条, 遇 call/jmp 停):
    STATIC_BASE  = mov ecx, offset g_CCBCamControlData / mov ecx, 0x17AAF64
    GLOBAL_PTR   = mov ecx, ds:g_XXX (其它全局指针)
    REG_CARRY    = mov ecx, e?? (寄存器携带, 记来源行)
    STACK_LOCAL  = lea ecx, [esp+...] (栈局部对象!)
    OTHER/UNKNOWN
关键: InsertTaskToList/SwapTask 的 ecx 来源 —— 与 CCBCamControl 方法
ecx 来源是否同源(单体)或指向另一对象(两对象)。
"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_receiver_20261126.json'
CCB = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CCBCamControl.json', encoding='utf-8'))
CCT = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CCCTData.json', encoding='utf-8'))

def ecx_backtrace(call_ea, window=24):
    """回溯 call 前的 ecx 装载, 返回 (form, detail, lines)"""
    cur = call_ea
    lines = []
    for _ in range(window):
        cur = idc.prev_head(cur, 0)
        if cur == idc.BADADDR:
            break
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        lines.append((hex(cur), t))
        base = t.split()[0] if t else ''
        if re.match(r'^(call|jmp|j[a-z]{2,3})\b', t):
            return ('BLOCKED', t, lines)
        m = re.match(r'^mov\s+ecx,\s*(.+)$', t)
        if m:
            op = m.group(1).strip()
            if 'g_CCBCamControlData' in op or '17AAF64' in op:
                return ('STATIC_BASE', op, lines)
            if op.startswith('ds:') or op.startswith('dword_') or op.startswith('g_'):
                return ('GLOBAL_PTR', op, lines)
            if op.startswith('e') or op in ('cx', 'ecx'):
                return ('REG_CARRY', op, lines)
            return ('OTHER', op, lines)
        m = re.match(r'^lea\s+ecx,\s*\[(esp|ebp)', t)
        if m:
            return ('STACK_LOCAL', t, lines)
        m = re.match(r'^lea\s+ecx,\s*(.+)$', t)
        if m:
            op = m.group(1).strip()
            if 'g_CCBCamControlData' in op or '17AAF64' in op:
                return ('STATIC_BASE_LEA', op, lines)
            return ('LEA_OTHER', op, lines)
    return ('UNKNOWN', '', lines)

def census(mmap, tag):
    rows = {}
    for a_str, m in sorted(mmap.items(), key=lambda x: int(x[0], 16)):
        ea = int(a_str, 16)
        nm = str(m.get('name') or a_str)
        f = ida_funcs.get_func(ea)
        if not f:
            continue
        callers = []
        for xr in idautils.CodeRefsTo(f.start_ea, 1):
            cf = ida_funcs.get_func(xr)
            cn = idc.get_func_name(cf.start_ea) if cf else '?'
            form, detail, lines = ecx_backtrace(xr)
            callers.append({'site': hex(xr), 'caller': cn, 'form': form,
                            'detail': detail[:80]})
        forms = collections.Counter(c['form'] for c in callers)
        rows[nm] = {'ea': hex(ea), 'n_callers': len(callers),
                    'forms': dict(forms), 'callers': callers[:16]}
    print('== %s ==' % tag)
    for nm, r in sorted(rows.items(), key=lambda x: -x[1]['n_callers'])[:14]:
        print('  %-26s callers=%-4d %s' % (nm, r['n_callers'], r['forms']))
        for c in r['callers'][:3]:
            print('      %-14s %-38s %s' % (c['form'], c['detail'], c['caller'][:28]))
    return rows

report = {}
report['CCCTData'] = census(CCT.get('methods') or {}, 'CCCTData')
report['CCBCamControl'] = census(CCB.get('methods') or {}, 'CCBCamControl')
json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
idapro.close_database(False)
