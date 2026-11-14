#!/usr/bin/env python3
"""[IDB 成员类型钉回 2026-11-14] 标注回退≠IDB回退铁律的补完。

病灶: fix_vtable_types(历史会话)把 CCBUIPanel.m_pVfTable 钉成 vtbl_0056B22C*,
其后注解战役裁定 char*(IDB struct compat) 但**钉回从未执行**(标注回退≠IDB回退)。
IDB vtbl 类型 ⇒ Hex-Rays 渲染 vtbl 成员访问 callshape ⇒ 发射器无法编译
(vtbl 类型被项目定谳不发射: 'vtable是编译器内部机制') ⇒ C2228。

修法: 通用扫描注解 known_members 与 IDB UDT 成员类型分歧, 按**注解真值**钉回。
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/pinback_idb_member_types_20261114.py [--apply]
"""
import sys, os, json, glob

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64', run_auto_analysis=False)

import ida_typeinf
til = ida_typeinf.get_idati()
APPLY = '--apply' in sys.argv
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# 扫描: 注解成员 vs IDB UDT 类型
fixes = []
for fp in sorted(glob.glob(os.path.join(ROOT, 'data/annotations/structs/*.json'))):
    cls = os.path.basename(fp)[:-5]
    try:
        d = json.load(open(fp, encoding='utf-8'))
    except Exception:
        continue
    km = d.get('known_members') or {}
    if not km:
        continue
    tif = ida_typeinf.tinfo_t()
    if not tif.get_named_type(til, cls):
        continue
    ud = ida_typeinf.udt_type_data_t()
    if not tif.get_udt_details(ud):
        continue
    changed = False
    for i in range(ud.size()):
        m = ud[i]
        off = str(m.offset // 8)
        ann = km.get(off)
        if not (isinstance(ann, dict) and ann.get('type')):
            continue
        ann_t = ann['type']
        if isinstance(ann_t, dict):
            ann_t = json.dumps(ann_t, ensure_ascii=False)  # 变体层: 仅报告
        ann_t = str(ann_t)
        idb_t = str(m.type)
        # 规范化比对: 空格无关
        if ann_t.replace(' ', '') == idb_t.replace(' ', ''):
            continue
        # 本轮只钉: m_pVfTable vtbl* → 注解 char* (语义分歧); 其余=typedef别名噪声跳过
        if ann.get('name') == 'm_pVfTable' and 'vtbl_' in idb_t:
            fixes.append((cls, off, ann.get('name'), idb_t, ann_t, True))
            ptr = ida_typeinf.tinfo_t()
            base = ida_typeinf.tinfo_t()
            base.create_simple_type(ida_typeinf.BTF_CHAR)
            ptr.create_ptr(base)
            if APPLY:
                m.type = ptr
                changed = True
    if APPLY and changed:
        r = ida_typeinf.tinfo_t()
        if r.create_udt(ud, ida_typeinf.BTF_STRUCT):
            r.set_named_type(til, cls, ida_typeinf.NTF_REPLACE)
            print('[钉回] %s UDT 已重建' % cls)

print('=== 分歧清单 (%d) ===' % len(fixes))
for cls, off, nm, idb_t, ann_t, do in fixes:
    print('%-16s +%-6s %-14s IDB=%-28s 注解=%-14s %s' % (cls, off, nm or '?', idb_t, ann_t, '钉回' if do else '(仅报告)'))
if not APPLY:
    print('\n[dry-run] 加 --apply 执行钉回')
idapro.close_database(False)
