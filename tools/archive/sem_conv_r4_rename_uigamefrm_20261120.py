#!/usr/bin/env python3
"""[R4 类改名 2026-11-20·用户裁定] CGameData → UIGameFrm（幻影壳档案合并）。

裁定证据（用户认可执行）:
  1. 实例名 g_gamefrm = game frame（38 调用点）
  2. UI*Frm 命名族同款（UISceneFrm/UICoverFrm/UILoadingFrm/UIGameOver 均在档）
  3. 旧 patch 注 globals source "PAL3patch:UIGameFrm*"
  4. "CGameData" 名无二进制证据（PDB 无档, note 自证 "size estimated"）
真类档案: vtable 0x56B094, ctor 0x44EF4F, 6 真方法 this=0xDB9FD0 直证。

合并: CGameData.json 全量 → UIGameFrm.json（幻影壳吸收真身）;
  bases=[UIWnd]（证据档; 幻影的 PalScriptWaitObj@68 无证据弃置注记）。
联动: globals g_gamefrm type→UIGameFrm; skip_functions 2 名重写;
  fcg_tail_allowlist 路径更新（Data/CGameData.cpp → Misc/UIGameFrm.cpp）。

用法: python3 tools/sem_conv_r4_rename_uigamefrm_20261120.py [--dry]
归档: data/annotations/archive/rename_uigamefrm_20261120.json
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data/annotations'
archive = {'_doc': 'CGameData→UIGameFrm 类改名 2026-11-20 (用户裁定)', 'ops': []}

# 1. 合并档案
cg = json.loads((S / 'structs/CGameData.json').read_text(encoding='utf-8'))
phantom = json.loads((S / 'structs/UIGameFrm.json').read_text(encoding='utf-8'))
cg['name'] = 'UIGameFrm'
cg['note'] = ('类改名20261120(用户裁定): CGameData→UIGameFrm——证据=实例名g_gamefrm(game frame)+'
    'UI*Frm命名族+旧patch注PAL3patch:UIGameFrm*; CGameData名=早期误读(Large game data container,'
    'PDB无档)。真身=游戏主框架窗口(模式切换中枢+场景装载+子对象族)。'
    + ' | ' + str(cg.get('note') or ''))
cg['_phantom_absorbed'] = ('幻影壳档案吸收20261120: 原UIGameFrm.json(方法尽迁RoleStatePanel后空壳)——'
    '其 bases PalScriptWaitObj@68 无证据弃置(真bases=[UIWnd]: dtor调UIWnd dtor+slot0指纹), '
    'size 28448 弃置(真size=28268: ctor/dtor链)')
if not DRY:
    (S / 'structs/UIGameFrm.json').write_text(json.dumps(cg, ensure_ascii=False, indent=1), encoding='utf-8')
    (S / 'structs/CGameData.json').unlink()
archive['ops'].append('structs/CGameData.json → UIGameFrm.json (合并幻影壳, bases=[UIWnd])')

# 2. globals: g_gamefrm type
g = json.loads((S / 'globals.json').read_text(encoding='utf-8'))
it = g.get('0x00DB9FD0')
if it and it.get('name') == 'g_gamefrm':
    it['type'] = 'UIGameFrm'
    it['source'] = (it.get('source') or '') + ' | type定谳20261120: UIGameFrm(类改名裁定+38调用点this直证)'
    archive['ops'].append('globals g_gamefrm type int→UIGameFrm')

# 3. skip_functions 2 名
sk = json.loads((S / 'skip_functions.json').read_text(encoding='utf-8'))
n = 0
for a, e in sk.items():
    nm = e.get('name') or ''
    if nm.startswith('CGameData::'):
        e['name'] = 'UIGameFrm::' + nm.split('::', 1)[1]
        n += 1
archive['ops'].append('skip_functions 改名 %d 条' % n)

# 4. fcg_tail_allowlist 路径
try:
    al = json.loads((S / 'fcg_tail_allowlist.json').read_text(encoding='utf-8'))
    m = 0
    def _walk(o):
        global m
        if isinstance(o, dict):
            for k, v in o.items():
                if isinstance(v, str) and 'Data/CGameData.cpp' in v:
                    o[k] = v.replace('Data/CGameData.cpp', 'Misc/UIGameFrm.cpp'); m += 1
                else:
                    _walk(v)
        elif isinstance(o, list):
            for i, v in enumerate(o):
                if isinstance(v, str) and 'Data/CGameData.cpp' in v:
                    o[i] = v.replace('Data/CGameData.cpp', 'Misc/UIGameFrm.cpp'); m += 1
                elif isinstance(v, (dict, list)):
                    _walk(v)
    _walk(al)
    if not DRY:
        (S / 'fcg_tail_allowlist.json').write_text(json.dumps(al, ensure_ascii=False, indent=1), encoding='utf-8')
    archive['ops'].append('fcg_tail_allowlist 路径更新 %d 处' % m)
except FileNotFoundError:
    archive['ops'].append('fcg_tail_allowlist 缺失跳过')

if not DRY:
    (S / 'globals.json').write_text(json.dumps(g, ensure_ascii=False, indent=1), encoding='utf-8')
    (S / 'skip_functions.json').write_text(json.dumps(sk, ensure_ascii=False, indent=1), encoding='utf-8')
    (S / 'archive/rename_uigamefrm_20261120.json').write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
for op in archive['ops']:
    print(' ', op)
print('done (dry=%s)' % DRY)
