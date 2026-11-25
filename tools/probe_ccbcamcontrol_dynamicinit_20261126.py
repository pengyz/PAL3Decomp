#!/usr/bin/env python3
"""probe_ccbcamcontrol_dynamicinit_20261126.py — g_CCBCamControlData 真尺寸/结构定谳 v4。

对决模型:
  (A) 单对象 430KB 巨构(CCT 任务池域 + 相机控制域复合, 31 独立名=成员双重注解)
  (B) 小对象 + 独立全局区 + CCCTData 方法错挂(双注解瓜分)
裁决证据:
  1. CRT 动态初始化表: 谁引用 0x17AAF64/g_CCBCamControlData → ??_L 形
     字面量(type,count,size,ctor,dtor) = 编译器 sizeof A 级(SystemUI/Scene 案同法)
  2. CCCTData ctor@0x5058f0 全写序(bound) + Create@0x506020
  3. InsertTaskToList/SwapTask 池步距解码: imul 0xCC/0xCD 常量
  4. 独立名双用面对决: 8 个样本名的 own-name 引用 vs +disp 成员形引用
"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

BASE = 0x17AAF64
OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_dynamicinit_20261126.json'
report = {}

# ---- 1. 全二进制找引用 BASE / g_CCBCamControlData 的代码点 ----
ref_sites = []
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    cn = idc.get_func_name(f.start_ea)
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 4000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        if '17AAF64' in t or 'g_CCBCamControlData' in t:
            ref_sites.append((hex(cur), cn, t))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
report['ref_sites_n'] = len(ref_sites)
report['ref_sites'] = ref_sites[:200]
# 唯一外部函数集(非写访问的绑定形)
binds = [r for r in ref_sites if re.search(r'\boffset\b|push.*17AAF64|mov\s+e[a-z]{2},\s*0x?17AAF64', r[2], re.I)]
report['bind_form_sites'] = binds[:60]

# ---- 2. CCCTData ctor 写序 ----
MEM_RX = re.compile(r'\[(e[a-z]{2}|cx|si|di)(?:\+(e[a-z]{2}|cx|si|di)(?:\*([1248]))?)?'
                    r'(\+(0[xX][0-9A-Fa-f]+|[0-9A-Fa-f]{1,8}h?))?\]')
def decode_writes(ea, cap=4000):
    f = ida_funcs.get_func(ea)
    if not f:
        return []
    out = []
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < cap:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        m = MEM_RX.search(t)
        if m and (t.startswith('mov') or t.startswith('fst') or t.startswith('lea')):
            d = 0
            if m.group(4):
                g = m.group(5)
                d = int(g, 16) if g.lower().startswith('0x') else int(g.rstrip('h]'), 16)
            out.append((hex(cur), d, t))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    return out
report['cct_ctor_writes'] = decode_writes(0x5058f0)[:200]
report['cct_create_writes'] = decode_writes(0x506020)[:150]

# ---- 3. 池步距: 池方法 imul/push 常量 ----
strides = collections.Counter()
for ea, nm in ((0x5075e0, 'InsertTaskToList'), (0x507b20, 'SwapTask'),
               (0x508190, 'ClearList'), (0x5081a0, 'IsTaskValid'),
               (0x5081c0, 'GetTaskNumInList'), (0x5081c0, 'GetFreeSpace')):
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 4000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        m = re.search(r'\b(imul|push|mov)\s+.*?0?x?([0-9A-Fa-f]{2,6})h?\b', t)
        if m and t.startswith('imul'):
            strides[m.group(2)] += 1
        cur = idc.next_head(cur, f.end_ea)
        n += 1
report['pool_imul_consts'] = dict(strides)

# ---- 4. 独立名双用面: own-name vs +disp 形 ----
SAMPLES = [('g_nCBFormation1', 0x624), ('g_nCBRoleAttackTable', 0x784),
           ('g_StageRoleData', 0xcfc), ('g_CCBStageSceneData', 0xf9c),
           ('g_CCBProtectData', 0x2660), ('g_fSceneScale', 0x5388),
           ('g_InputState', 0x6f5c), ('g_CScreenMode', 0x9284)]
dual = {}
name_sets = {nm: 0 for nm, _ in SAMPLES}
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 4000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        for nm, off in SAMPLES:
            if nm in t:
                name_sets[nm] += 1
        cur = idc.next_head(cur, f.end_ea)
        n += 1
report['sample_own_name_refs'] = {nm: c for nm, c in name_sets.items()}

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
print('引用 0x17AAF64 的站点: %d; 绑定形(offset/push/mov imm): %d' % (
    len(ref_sites), len(binds)))
for a, cn, t in binds[:20]:
    print('  bind:', cn, a, t[:70])
print('== CCCTData ctor 写序(前24) ==')
for a, d, t in report['cct_ctor_writes'][:24]:
    print('  %s +%s %s' % (a, hex(d), t[:60]))
print('ctor max disp:', hex(max((d for _, d, _ in report['cct_ctor_writes']), default=0)))
print('== imul 常量 ==', dict(strides))
print('== 独立名 own-name 引用 ==', report['sample_own_name_refs'])
idapro.close_database(False)
