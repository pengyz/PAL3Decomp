#!/usr/bin/env python3
"""[IAT 全量普查 2026-11-22] 注解 methods 地址 × 全部导入 thunk 地址批扫。

判据律(域判定先查 IAT): 符号在 IAT = 实现域外(DLL 提供)。
CPK 案教训: 注册为"类方法"的地址若实为导入 thunk/域外实现, 发射=以错身份编译。

普查:
  Q-I1 注解 methods 地址 ∈ IAT 槽地址集 → 注册指向导入槽(实现域外, 误注册)
  Q-I2 注解 methods 地址落在 .idata 段区间 → 同上(区间兜底)
  Q-I3 GBENGINE 导入符号的 demangled 类名 × 注解注册类 → 域外类清单
       (类级域归属参考——实现全在 DLL 的类, 其 structs 注册逐个需审)

输出: 控制台报告 + data/status/iat_census_20261122.json

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/iat_census_20261122.py
"""
import sys
import json
from pathlib import Path

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                     run_auto_analysis=False)
import ida_nalt
import ida_segment

REPO = Path(__file__).parent.parent

# ── 1. IAT 槽地址集 + 模块×符号 ─────────────────────────────
iat = {}          # slot_ea → (module, symbol)
mod_syms = {}     # module → [(ea, symbol)]
n = ida_nalt.get_import_module_qty()
for i in range(n):
    mod = ida_nalt.get_import_module_name(i) or ('#%d' % i)
    syms = []
    def cb(ea, name, ordinal, _mod=mod, _syms=syms):
        syms.append((ea, name or ('#%d' % ordinal)))
        iat[ea] = (_mod, name or ('#%d' % ordinal))
        return True
    ida_nalt.enum_import_names(i, cb)
    mod_syms[mod] = syms
print('[probe] 导入模块 %d, IAT 槽 %d' % (n, len(iat)))

# .idata 段区间(区间兜底)
_idata = ida_segment.get_segm_by_name('.idata')
idata_lo, idata_hi = (_idata.start_ea, _idata.end_ea) if _idata else (None, None)

idapro.close_database(False)

# ── 2. 注解 methods × IAT ──────────────────────────────────
import glob
q1, q2, q3_byclass = [], [], {}
for fp in sorted(glob.glob(str(REPO / 'data' / 'annotations' / 'structs' / '*.json'))):
    d = json.load(open(fp, encoding='utf-8'))
    cls = d.get('name') or Path(fp).stem
    for a, m in (d.get('methods') or {}).items():
        try:
            ai = int(str(a), 16)
        except (ValueError, TypeError):
            continue
        if ai in iat:
            q1.append((cls, a, m.get('name'), iat[ai]))
        elif idata_lo and idata_lo <= ai < idata_hi:
            q2.append((cls, a, m.get('name')))

print('\n== Q-I1 注解地址=IAT槽(误注册) %d ==' % len(q1))
for cls, a, nm, (mod, sym) in q1:
    print('  %-14s %s %-24s → IAT[%s] %s' % (cls, a[-8:], str(nm)[:22], mod, str(sym)[:40]))

print('\n== Q-I2 注解地址∈.idata区间 %d ==' % len(q2))
for cls, a, nm in q2[:10]:
    print('  %-14s %s %s' % (cls, a[-8:], nm))

# ── 3. GBENGINE 导入符号 demangled 类名清单(域外实现类) ────
gb = mod_syms.get('GBENGINE') or []
cls_names = set()
for ea, sym in gb:
    # mangle 形三类: ?Method@Cls@@... / ??0Cls@@... / ??_7Cls@@6B@(vtable)
    if sym.startswith('??_7'):
        cls_names.add(sym[4:].split('@')[0])
        continue
    if sym.startswith('??0') or sym.startswith('??1') or sym.startswith('??_E'):
        cls_names.add(sym[4:].split('@')[0])
        continue
    if sym.startswith('?') and '@' in sym:
        parts = sym.split('@')
        if len(parts) >= 2 and parts[1] and not parts[1].startswith(('Q', 'U', 'Y')):
            cls_names.add(parts[1])
print('\n== Q-I3 GBENGINE 导入涉及类 %d 个(实现域外参考清单) ==' % len(cls_names))
print('  ', ', '.join(sorted(cls_names)))

out = {
    '_doc': 'IAT 全量普查 2026-11-22 (判据工具化: 域判定先查 IAT)',
    'iat_total': len(iat),
    'modules': {k: len(v) for k, v in mod_syms.items()},
    'q1_misregistered': [{'cls': c, 'addr': a, 'name': n, 'iat': [mod, s]}
                         for c, a, n, (mod, s) in q1],
    'q2_idata_range': [{'cls': c, 'addr': a, 'name': n} for c, a, n in q2],
    'q3_gbengine_classes': sorted(cls_names),
}
outp = REPO / 'data' / 'status' / 'iat_census_20261122.json'
outp.write_text(json.dumps(out, ensure_ascii=False, indent=1), encoding='utf-8')
print('\n报告 →', outp)
