#!/usr/bin/env python3
"""[IDB til 审计 2026-11-19] S4 L1 衰退(49→43)根因定位——IDB 类型系统退化验证。

背景: 19:44 rebaseline (L1 49, matched 458) 与 20:45 run A 之间语料状态一次性转换。
丢失类 CEffectSystem/C3DSpark 的 TU 编译失败, 渲染退化 this[682] (sizeof≈1 特征)。
本审计在 IDB 副本上只读检查: til 类型数量/目标类尺寸/ctor 签名 this 类型。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_idb_til_audit_20261119.py
输出: data/status/idb_til_audit_20261119.json
"""
import json
import shutil
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
SRC_IDB = REPO / 'original/PAL3.exe.i64'
TMP_IDB = Path('/tmp/pal3_audit_til.i64')

if not TMP_IDB.exists():
    print('拷贝 IDB 到 /tmp (只读审计, 不碰原库)...')
    shutil.copy(SRC_IDB, TMP_IDB)

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database(str(TMP_IDB), run_auto_analysis=False)
print('[audit] db opened:', db)

import ida_typeinf
import ida_nalt
import ida_funcs

out = {}

til = ida_typeinf.get_idati()
out['til_type_count'] = ida_typeinf.get_ordinal_limit(til)

for cls, expect in [('CEffectSystem', 360), ('C3DSpark', None), ('UIWnd', None),
                    ('CEffMgr', None), ('gbMatrixStack', None), ('sg_emitter', None)]:
    tif = ida_typeinf.tinfo_t()
    if tif.get_named_type(til, cls):
        out[cls] = {'size': tif.get_size()}
        if expect:
            out[cls]['expected'] = expect
            out[cls]['size_ok'] = (tif.get_size() == expect)
    else:
        out[cls] = 'NOT IN TIL'

for va, label in [(0x4c61a0, 'CEffectSystem::ctor'),
                  (0x4D6670, 'C3DSpark::C3DSpark'),
                  (0x4D6AC0, 'C3DSpark::CreateOne')]:
    ftif = ida_typeinf.tinfo_t()
    ok = ida_nalt.get_tinfo(ftif, va)
    out['fn_%s' % label] = {
        'name': ida_funcs.get_func_name(va),
        'has_tinfo': bool(ok),
        'type': str(ftif) if ok else None,
    }

# 4. 决定性测试: 在副本上直接 hexrays 反编译, 看 IDB 自身渲染是好是坏
import ida_hexrays
ida_hexrays.init_hexrays_plugin()
for va, label in [(0x4c61a0, 'CEffectSystem::ctor'),
                  (0x4D6670, 'C3DSpark::C3DSpark')]:
    cf = ida_hexrays.decompile(va)
    if cf:
        txt = str(cf)
        # 抓签名行 + 前 12 行体
        lines = txt.split('\n')
        out['decompile_%s' % label] = '\n'.join(lines[:14])
        out['decompile_%s_degraded' % label] = ('this[682]' in txt or 'this[6' in txt)
    else:
        out['decompile_%s' % label] = 'DECOMPILE FAILED'

print(json.dumps(out, ensure_ascii=False, indent=1))
Path(REPO / 'data/status/idb_til_audit_20261119.json').write_text(
    json.dumps(out, ensure_ascii=False, indent=1), encoding='utf-8')
idapro.close_database(False)
print('audit -> data/status/idb_til_audit_20261119.json (副本关闭未保存, 原库未动)')
