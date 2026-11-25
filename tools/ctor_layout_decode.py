#!/usr/bin/env python3
"""ctor_layout_decode.py — 全量标注类构造函数布局解码。

原理: ctor = 编译器写死的类布局定义。逐指令分类→推导布局→与注解对比。
输出: per-class 解码报告 → 三类问题全量清单。
"""
import sys, json, os, re, struct, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_bytes, ida_funcs, ida_name, ida_segment, idautils

ANNO_DIR = '/home/peng/workspace/PAL3Decomp/data/annotations/structs'
OUT_PATH = '/home/peng/workspace/PAL3Decomp/data/status/ctor_layout_decode.json'

# ---- 收集标注类与其 ctor 地址 ----
classes = {}
for sp in sorted(os.listdir(ANNO_DIR)):
    if not sp.endswith('.json'):
        continue
    d = json.load(open(os.path.join(ANNO_DIR, sp), encoding='utf-8'))
    cls = d.get('name') or sp[:-5]
    size = d.get('binary_size') or 0
    ctors = []
    for a, m in (d.get('methods') or {}).items():
        if m.get('name') == cls or (m.get('flags') and 'ctor' in (m.get('flags') or [])):
            ctors.append(int(a, 16))
    km = d.get('known_members') or {}
    member_offs = set()
    for k, v in km.items():
        if k.startswith('_'):
            continue
        try:
            member_offs.add(int(k, 16))
        except Exception:
            pass
    classes[cls] = {
        'size': size, 'ctor_addrs': ctors, 'member_offs': member_offs,
        'path': os.path.join(ANNO_DIR, sp),
    }

print('标注类: %d' % len(classes))

# ---- this 寄存器链跟踪 ----
def walk_ctor(ctor_ea):
    """解码 ctor 体, 返回布局证据。"""
    f = ida_funcs.get_func(ctor_ea)
    if not f:
        return None
    end = f.end_ea
    this_regs = {'ecx'}   # 初始 this 寄存器链
    vtable_writes = []
    scalar_writes = []
    embedded_calls = []   # (this_offset_or_disp, target_name, target_class)
    ehvec_calls = []      # (base_disp, elem_size, count, elem_class)
    max_off = 0
    cur = ctor_ea
    n = 0
    while cur < end and n < 500:
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        # this 寄存器链扩展: mov ebx, ecx / mov esi, ebx 等
        m = re.match(r'mov\s+(e\w\w),\s*(e\w\w)$', t)
        if m and m.group(2) in this_regs:
            this_regs.add(m.group(1))
        # lea reg, [this_reg + disp] → 产生新 this 基址
        m = re.match(r'lea\s+(e\w\w),\s*\[(e\w\w)\+([0-9A-Fa-f]+)h?\]', t)
        if m and m.group(2) in this_regs:
            # 子对象基址: 后续如果 mov ecx, reg; call → embedded ctor
            off = int(m.group(3), 16)
            this_regs.add(m.group(1))
        # vtable 写: mov dword ptr [this_reg], offset_label
        m = re.match(r'mov\s+(?:dword ptr\s*)?\[(e\w\w)\],\s*offset\s+(\w+)', t)
        if m and m.group(1) in this_regs:
            vtable_writes.append({'offset': 0, 'target': m.group(2)})
            max_off = max(max_off, 4)
        # 域写: mov [this_reg+disp], val/reg
        m = re.match(r'mov\s+(?:(?:byte|word|dword) ptr\s*)?\[(e\w\w)\+([0-9A-Fa-f]+)h?\],\s*(.+)', t)
        if m and m.group(1) in this_regs:
            off = int(m.group(2), 16)
            sz = 4
            if 'byte ptr' in t: sz = 1
            elif 'word ptr' in t: sz = 2
            scalar_writes.append({'offset': off, 'size': sz, 'val': m.group(3)[:30]})
            max_off = max(max_off, off + sz)
        # 嵌入 ctor 调用: call ??0ClassName@@...
        m = re.match(r'call\s+\?\?0(\w+)@@', t)
        if m:
            tgt_cls = m.group(1)
            # 回溯找 lea ecx/ecx来源
            embedded_calls.append({'target_class': tgt_cls, 'ea': hex(cur)})
        # ??_L eh vector ctor: 回溯 push 序列
        if '??_L@' in t or 'eh vector constructor' in t:
            # 回溯找 push 序列: dtor, ctor, count, elem_size, base
            pushes = []
            pcur = cur
            for k in range(8):
                pcur = idc.prev_head(pcur, 0)
                if pcur == idc.BADADDR:
                    break
                pt = (idc.generate_disasm_line(pcur, 0) or '').strip()
                if pt.startswith('push'):
                    pushes.append(pt)
                if re.match(r'lea\s+e\w\w,\s*\[e\w\w\+', pt):
                    pushes.append(pt)
                    break
            # 解析: push offset ??0ClassName → elem class; push NNNh → size/count
            elem_cls = None
            elem_sz = None
            count = None
            base_disp = None
            for p in pushes:
                m2 = re.search(r'\?\?0(\w+)@@', p)
                if m2:
                    elem_cls = m2.group(1)
                m2 = re.search(r'push\s+([0-9A-Fa-f]+)h?', p)
                if m2 and elem_sz is None:
                    val = int(m2.group(1), 16)
                    if val > 16:  # count 通常 < 100, size > 16
                        elem_sz = val
                    elif val < 200:
                        count = val
                m2 = re.search(r'lea\s+e\w\w,\s*\[e\w\w\+([0-9A-Fa-f]+)h?\]', p)
                if m2:
                    base_disp = int(m2.group(1), 16)
            ehvec_calls.append({'base_disp': base_disp, 'elem_size': elem_sz,
                                'count': count, 'elem_class': elem_cls})
            if base_disp is not None and elem_sz is not None and count is not None:
                max_off = max(max_off, base_disp + count * elem_sz)
        # ArraySort: ArraySort(base, count, elem, ctor) → base+count*elem
        if 'ArraySort' in t:
            pcur = cur
            args = []
            for k in range(6):
                pcur = idc.prev_head(pcur, 0)
                if pcur == idc.BADADDR:
                    break
                pt = (idc.generate_disasm_line(pcur, 0) or '').strip()
                m2 = re.match(r'(?:push|mov)\s+e\w\w,\s*\[e\w\w\+([0-9A-Fa-f]+)h?\]', pt)
                if m2:
                    args.append(int(m2.group(1), 16))
            if args:
                max_off = max(max_off, max(args) + 0x44)
        n += 1
        cur = idc.next_head(cur, end)
    return {
        'ctor_ea': hex(ctor_ea), 'ctor_size': end - ctor_ea,
        'this_regs': sorted(this_regs),
        'vtable_writes': vtable_writes,
        'scalar_writes': scalar_writes[:20],
        'embedded_calls': embedded_calls[:10],
        'ehvec_calls': ehvec_calls[:5],
        'max_write_offset': hex(max_off) if max_off > 0 else '0',
        'derived_min_size': max_off,
    }

# ---- 全量扫描 ----
report = {}
scanned = 0
decoded = 0
no_ctor = 0
for cls in sorted(classes):
    info = classes[cls]
    if not info['ctor_addrs']:
        no_ctor += 1
        report[cls] = {'status': 'no-ctor', 'annotated_size': info['size']}
        continue
    # 用第一个 ctor 地址
    ct = info['ctor_addrs'][0]
    result = walk_ctor(ct)
    if result is None:
        report[cls] = {'status': 'no-func', 'annotated_size': info['size']}
        continue
    scanned += 1
    derived = result['derived_min_size']
    annotated = info['size']
    delta = annotated - derived
    # 分类
    issues = []
    if derived > annotated and annotated > 0:
        issues.append('ctor-write-beyond-annotation: derived 0x%X > annotated 0x%X' % (derived, annotated))
    if derived < annotated and derived > 0 and annotated - derived > 0x100:
        issues.append('ctor-writes-far-less-than-annotated: derived 0x%X << annotated 0x%X (gap 0x%X)' % (derived, annotated, annotated - derived))
    if result['vtable_writes']:
        issues.append('vtable-write: %s' % json.dumps(result['vtable_writes']))
    report[cls] = {
        'status': 'decoded', 'annotated_size': annotated,
        'ctor_addr': hex(ct), 'ctor_size': result['ctor_size'],
        'derived_min_size': hex(derived), 'size_delta': delta,
        'max_write_offset': result['max_write_offset'],
        'vtable_writes': result['vtable_writes'],
        'embedded_calls': result['embedded_calls'],
        'ehvec_calls': result['ehvec_calls'],
        'scalar_write_count': len(result['scalar_writes']),
        'issues': issues,
        'member_offs_count': len(info['member_offs']),
    }

print('解码: %d/%d (no-ctor: %d)' % (scanned, len(classes), no_ctor))
# 汇总
issues_all = collections.Counter()
for cls, r in report.items():
    for i in (r.get('issues') or []):
        key = i.split(':')[0]
        issues_all[key] += 1
print('问题分布:', dict(issues_all.most_common()))
print()
# size 差异 top 10
sizes = [(cls, r.get('annotated_size', 0), int(r.get('derived_min_size', '0'), 16) if isinstance(r.get('derived_min_size'), str) else r.get('derived_min_size', 0))
         for cls, r in report.items() if r.get('status') == 'decoded']
big_diff = sorted(sizes, key=lambda x: -abs(x[1] - x[2]))[:10]
print('size delta top 10:')
for cls, ann, der in big_diff:
    print('  %-24s annotated=%-6d derived=%-6d delta=%d' % (cls, ann, der, ann - der))
# no-ctor 清单
noc = [cls for cls, r in report.items() if r.get('status') == 'no-ctor']
print('no-ctor 类(%d): %s' % (len(noc), ', '.join(noc[:20])))
# 保存
json.dump({'generated': '2026-11-25', 'total': len(classes), 'decoded': scanned,
           'no_ctor': no_ctor, 'issue_dist': dict(issues_all.most_common()),
           'report': report},
          open(OUT_PATH, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT_PATH)
idapro.close_database(False)
