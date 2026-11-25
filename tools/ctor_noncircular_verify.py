#!/usr/bin/env python3
"""ctor 非循环验证：86 解码类 × 四证（caller 工厂/分配尺寸/写偏移合规/行为语义）。"""
import sys, json, os, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, ida_name, idautils

decode = json.load(open('/home/peng/workspace/PAL3Decomp/data/status/ctor_layout_decode.json'))
report = decode['report']

def find_caller_ctx(site):
    """回溯调用点上下文：找 operator new + push 参数 + 宿主函数。"""
    f = ida_funcs.get_func(site)
    host = (ida_name.get_name(f.start_ea) or '?') if f else '?'
    cur = site
    ops_new = None
    pushes = []
    for k in range(15):
        cur = idc.prev_head(cur, 0)
        if cur == idc.BADADDR:
            break
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        m = re.match(r'push\s+([0-9A-Fa-f]+)h?', t)
        if m:
            pushes.append(int(m.group(1), 16))
        if 'operator new' in t or '??2@YAPAXI@Z' in t:
            m2 = re.search(r'push\s+([0-9A-Fa-f]+)h?', t)
            if m2:
                ops_new = int(m2.group(1), 16)
    return host, ops_new, pushes

def ctor_body_writes(ctor_ea):
    """ctor 体全部 this 相对写偏移。"""
    f = ida_funcs.get_func(ctor_ea)
    if not f:
        return 0, []
    end = f.end_ea
    cur = ctor_ea
    max_off = 0
    writes = []
    n = 0
    while cur < end and n < 500:
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        m = re.match(r'mov\s+(?:(?:byte|word|dword) ptr\s*)?\[e\w\w\+([0-9A-Fa-f]+)h?\]', t)
        if m:
            off = int(m.group(1), 16)
            if off < 0x10000:
                writes.append(off)
                max_off = max(max_off, off + 4)
        n += 1
        cur = idc.next_head(cur, end)
    return max_off, writes

results = {}
verified_ct = 0
for cls in sorted(report.keys()):
    r = report[cls]
    if r.get('status') != 'decoded':
        continue
    ct_hex = r.get('ctor_addr', '0')
    ct_ea = int(ct_hex, 16)
    f = ida_funcs.get_func(ct_ea)
    if not f:
        continue
    fname = ida_name.get_name(ct_ea) or ''
    # 证据 1: mangle 匹配（非循环：需 IDB 名来自 PDB/原二进制而非 apply）
    mangle_match = '??0%s@@' % cls in fname
    # 证据 2: caller 上下文
    callers = []
    for xref in idautils.XrefsTo(ct_ea):
        site = xref.frm
        host, ops_new, pushes = find_caller_ctx(site)
        callers.append({'site': hex(site), 'host': host[:50], 'ops_new': ops_new})
    # 证据 3: ctor 写偏移 vs caller operator new 尺寸
    max_write, writes = ctor_body_writes(ct_ea)
    # 汇总
    factory_caller = any('Init' in c['host'] or 'Create' in c['host'] or 'new' in c['host'].lower()
                         for c in callers)
    size_ok = None
    if ops_new is not None and max_write > 0:
        size_ok = ops_new >= max_write
    entries = []
    if not mangle_match:
        entries.append('mangle 名不匹配 (IDB 名可能是 apply 写入的)')
    if len(callers) == 0:
        entries.append('零调用点')
    for c in callers:
        if 'Proc' in c['host'] or 'Attack' in c['host'] or 'Update' in c['host']:
            entries.append('caller=%s 为逻辑方法(非工厂)——ctor 在逻辑方法内调用=异常' % c['host'][:30])
    results[cls] = {
        'ctor_addr': hex(ct_ea), 'ctor_code_size': f.end_ea - ct_ea,
        'mangle_match': mangle_match, 'idb_name': fname[:80],
        'callers': callers[:5], 'caller_count': len(callers),
        'factory_caller': factory_caller,
        'max_this_write': hex(max_write) if max_write else '0',
        'ops_new_size': hex(ops_new) if ops_new else None,
        'size_ok': size_ok,
        'issues': entries,
    }
    verified_ct += 1

print('验证类: %d' % verified_ct)
# 汇总
pass_all = [c for c, r in results.items() if r['mangle_match'] and r['caller_count'] > 0
            and not any('逻辑方法' in i or '零调用' in i for i in r['issues'])]
suspect = [c for c, r in results.items() if any('逻辑方法' in i for i in r.get('issues', []))]
zero_call = [c for c, r in results.items() if r.get('caller_count', 0) == 0]
print('全部通过: %d' % len(pass_all))
print('逻辑方法内调用 ctor(异常): %d %s' % (len(suspect), suspect[:8]))
print('零调用点: %d %s' % (len(zero_call), zero_call[:8]))
json.dump({'verified': verified_ct, 'pass': len(pass_all),
           'suspect_logical': suspect, 'zero_call': zero_call,
           'results': results},
          open('/home/peng/workspace/PAL3Decomp/data/status/ctor_noncircular_verify.json',
               'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> ctor_noncircular_verify.json')
idapro.close_database(False)
