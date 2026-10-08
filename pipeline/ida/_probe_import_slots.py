"""init 拆解探针：dump gbengine 导入哨兵槽的 (is_func, name, type) 状态。

用法: idat -S"_probe_import_slots.py <stage>" work.i64
输出: pipeline/ida/_logs/slot_probe_<stage>.json
一次性调研脚本（不提交）。
"""
import json, os, sys
import ida_auto, ida_funcs, ida_name, ida_nalt, idc, ida_pro

ida_auto.auto_wait()

SENTINELS = {
    0x56A584: 'RenderGeomQuad',
    0x56A30C: 'op_eq_gbMatrix4',
    0x56A540: 'Read',
    0x56A230: 'TransformPlane',
    0x56A26C: 'EnableShadow',
}

stage = os.environ.get('PROBE_STAGE', 'X')
out = {'stage': stage, 'slots': {}, 'summary': {}}

n_member_total = 0
n_member_typed = 0
n_member_func = 0
for i in range(ida_nalt.get_import_module_qty()):
    mod = ida_nalt.get_import_module_name(i)
    if not mod or 'gbengine' not in mod.lower():
        continue

    def _cb(ea, name, ordinal):
        global n_member_total, n_member_typed, n_member_func
        n_member_total += 1
        f = ida_funcs.get_func(ea)
        t = idc.get_type(ea) or ''
        if t:
            n_member_typed += 1
        if f:
            n_member_func += 1
        if ea in SENTINELS:
            out['slots']['0x%08X' % ea] = {
                'probe': SENTINELS[ea], 'name': name,
                'is_func': bool(f), 'type': t,
            }
        return True

    ida_nalt.enum_import_names(i, _cb)

out['summary'] = {'member_total': n_member_total, 'member_typed': n_member_typed,
                  'member_is_func': n_member_func}

LOG_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), '_logs')
os.makedirs(LOG_DIR, exist_ok=True)
with open(os.path.join(LOG_DIR, 'slot_probe_%s.json' % stage), 'w', encoding='utf-8') as f:
    json.dump(out, f, indent=1, ensure_ascii=False)
print('[probe] stage=%s %s' % (stage, out['summary']))
ida_pro.qexit(0)
