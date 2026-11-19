#!/usr/bin/env python3
"""[lvar 修复实验 v2 2026-11-19] IDB 副本上验证: 清 saved user lvars 能否复原渲染。

案例组:
  A. 0x4c5d50 ~CEffectSystem (Blocka 族——语料半剥离病灶)
  B. 0x52aff0 UINote::RenderWithStack (C2197 族——裸槽名调用病灶)
方法: 清前直解 → 清 saved user lvars(空 uservec) + mark_cfunc_dirty → 清后直解。
判定: A 清后参数名是否复 a2 形; B 清后是否恢复成员调用形态。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_lvar_heal_test_20261119.py
"""
import shutil
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
TMP_IDB = Path('/tmp/pal3_heal_test.i64')
if not TMP_IDB.exists():
    shutil.copy(REPO / 'original/PAL3.exe.i64', TMP_IDB)
    print('副本已拷贝')

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
idapro.open_database(str(TMP_IDB), run_auto_analysis=False)

import ida_hexrays as hr
import ida_nalt
import ida_typeinf

hr.init_hexrays_plugin()

def render(va, label):
    cf = hr.decompile(va)
    if not cf:
        print('=== %s: DECOMPILE FAILED' % label)
        return
    txt = str(cf)
    lines = [l for l in txt.split('\n') if l.strip()][:12]
    print('=== %s (0x%X) ===' % (label, va))
    print('\n'.join(lines[:10]))
    print('   [Blocka]:', 'Blocka' in txt, ' [bare Push(]:', 'Push(' in txt and '->Push' not in txt,
          ' [member call ->.]:', bool(__import__('re').search(r'->(Push|Rotate|Pop|Translate)\(', txt)))
    print()

for va, label in [(0x4c5d50, 'A ~CEffectSystem'), (0x52aff0, 'B UINote::RenderWithStack')]:
    render(va, label + ' 清前')

for va, label in [(0x4c5d50, 'A'), (0x52aff0, 'B')]:
    uvec = hr.lvar_uservec_t()
    uvec.lvvec = hr.lvar_saved_infos_t()
    uvec.size = 0
    hr.save_user_lvar_settings(va, uvec)
    hr.mark_cfunc_dirty(va, True)

for va, label in [(0x4c5d50, 'A ~CEffectSystem'), (0x52aff0, 'B UINote::RenderWithStack')]:
    render(va, label + ' 清后')

idapro.close_database(False)
print('(副本关闭未保存, 原库未动)')
