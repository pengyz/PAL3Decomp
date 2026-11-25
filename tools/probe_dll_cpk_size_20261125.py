#!/usr/bin/env python3
"""probe_dll_cpk_size_20261125.py — DLL 侧 sizeof(CPK) 定谳。
gbengine.dll.i64: CPK 方法体 (??0CPK@@/SetOpenMode/IsValidCPK/Load/GetFileNum...)
this-form disp 普查 → CPK 真尺寸上/下界;
gbVFileSystem 方法体 disp → VFS 真尺寸对照。
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/gbengine.dll.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_dll_cpk_size_20261125.json'
report = {}

# DLL 侧 CPK 方法清单 (mangle 真值)
cpk_methods = []
for ea, name in idautils.Names():
    if re.match(r'^\?[A-Za-z_]+@CPK@@', name):
        f = ida_funcs.get_func(ea)
        if f:
            cpk_methods.append((ea, name, f))
vfs_methods = []
for ea, name in idautils.Names():
    if re.match(r'^\?[A-Za-z_]+@gbVFileSystem@@', name):
        f = ida_funcs.get_func(ea)
        if f:
            vfs_methods.append((ea, name, f))

def disp_census(methods, label, limit=60):
    all_disp = set()
    per = []
    scanned = 0
    for ea, name, f in methods[:limit]:
        cur = f.start_ea
        n = 0
        md = 0
        while cur < f.end_ea and n < 4000:
            t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
            mm = re.search(r'\[(?:e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]', t)
            if mm:
                off = int(mm.group(1), 16)
                if off < 0x200000:
                    all_disp.add(off)
                    md = max(md, off)
            cur = idc.next_head(cur, f.end_ea)
            n += 1
        scanned += 1
        per.append((hex(ea), name[:50], hex(md)))
    print('%s: 方法 %d (采样 %d), max disp = %s' % (label, len(methods), scanned, hex(max(all_disp) if all_disp else 0)))
    for p in sorted(per, key=lambda x: -int(x[2], 16))[:8]:
        print('   %s %s max=%s' % p)
    return max(all_disp) if all_disp else 0, per

print('DLL CPK 方法总数:', len(cpk_methods))
print('DLL gbVFileSystem 方法总数:', len(vfs_methods))
cpk_max, cpk_per = disp_census(cpk_methods, 'CPK')
vfs_max, vfs_per = disp_census(vfs_methods, 'gbVFileSystem')
report = {'cpk_methods_n': len(cpk_methods), 'cpk_max_disp': hex(cpk_max),
          'vfs_methods_n': len(vfs_methods), 'vfs_max_disp': hex(vfs_max),
          'cpk_per': cpk_per[:20], 'vfs_per': vfs_per[:20]}
json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
idapro.close_database(False)
