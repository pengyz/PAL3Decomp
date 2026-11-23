#!/usr/bin/env python3
"""[删除式dtor L1恢复 2026-11-21] 12个??_G wrapper定义解除压制——S4字节证伪C8压制前提。

S4 全量行对比(20261121 20:4x run vs 03:17 baseline, 106→96):
  match_L1 丢失13 = 12个??_G删除式dtor + DestroyPanel@UICaption/OnMessage@UIMap(=MoveWindow ABI错,
  已另行修复)。12个??_G 全部是 03:17基线 100.0% 字节完美匹配、其 wrapper 定义单元今日被
  C8 批次(declaration_only/type=skip)+清仓拔除后丢失。

相关性 12/12: wrapper单元在场→??_G L1保持; wrapper被压制→??_G L1丢失
(对照: CCBResultWindow/ParticleEffect 拔后不丢=其 ??1 完全形发射红利对冲, 但 ??_G 同样丢)。

裁定: C8"删除式=编译器包装无源体"前提对这些类被 S4 字节证据证伪——
  它们的 wrapper 定义编译产物=注册符号 ??_G 的字节完美匹配载体。
  100.0% 匹配=二进制级证据(最高证据级), 压制标记(20261121 C8批次)在此12例退役。

修: 每条删除 declaration_only + type='skip', name_note 落证据链。
用法: python3 tools/fix_deleteform_dtor_l1_restore_20261121.py [--dry]
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv
S = REPO / 'data' / 'annotations' / 'structs'

# 12 个 ??_G 删除式 dtor (S4 03:17 基线 match_L1 100.0%, 今日清仓拔除)
RESTORE = [
    ('CCBUIPanel.json',      '0x004461d0'),
    ('JusticeBookUI.json',   '0x005284c0'),
    ('RoleCameraCtrl.json',  '0x00450ab0'),
    ('TaskBookUI.json',      '0x00454980'),
    ('UI3DCtrl.json',        '0x0043d860'),
    ('CCBResultWindow.json', '0x00444aa0'),
    ('UILoadingFrm.json',    '0x00450770'),
    ('RenderTargetNode.json', '0x004bd850'),   # ParticleEffect ??_G (RenderTargetNode域)
    ('UIRoleDialog.json',    '0x004a13f0'),
    ('UISceneMap.json',      '0x00450070'),
    ('UITitle.json',         '0x0044acc0'),
    ('Role.json',            '0x00411bd0'),
]

EVID = (
    ' | L1恢复20261121: S4字节证据证伪C8压制前提——03:17基线本wrapper定义编译产物'
    '=?_G注册符号100.0%字节完美; 20261121 C8批次(decl_only/type=skip)+清仓拔除单元后'
    'S4全量对比??_G丢失(12/12相关性). 删除declaration_only+type=skip, wrapper定义恢复发射. '
    'C8模型修正: ??_G匹配载体=wrapper定义单元(非头声明合成)'
)

done, miss = [], []
for fname, addr in RESTORE:
    p = S / fname
    d = json.loads(p.read_text(encoding='utf-8'))
    m = (d.get('methods') or {}).get(addr)
    if m is None:
        miss.append((fname, addr))
        continue
    changed = False
    if m.get('declaration_only'):
        m.pop('declaration_only')
        changed = True
    if m.get('type') == 'skip':
        m.pop('type')
        changed = True
    if changed:
        m['name_note'] = (m.get('name_note') or '') + EVID
        done.append((fname, addr, m.get('name')))
    if not DRY:
        p.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')

for f, a, n in done:
    print('  恢复 %s %s (%s)' % (f, a, n))
for f, a in miss:
    print('  [!] 未找到 %s %s' % (f, a))
print('done: %d 恢复, %d 未命中 (dry=%s)' % (len(done), len(miss), DRY))
