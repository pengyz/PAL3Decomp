#!/usr/bin/env python3
"""[R4-T2c 2026-11-20] tagStageRoleData 26 名渐进正名——装载槽组数组化+调用链派生名。

证据链 (A 级, 调用链直证):
  0x1C-0x28 ← CCBStage::Proceed(写519×4) ← CCBStageEffect::LoadLinker
  0x2C-0x38 ← CCBStage::SetMaxBlend(写[128,323,519,716]) ← CCBStage::SetAlive
  0x3C-0x48 ← CCBStage::SetPause(写545×4) ← CCBStage::SetVisible
  0x4C-0x58 ← CCBStage::CheckAction(写[121,316,512,709]) ← CCBStage::OnChangeAction
  结构: 四组 int[4], stride 0x10; 组内等差~195/组间恒差7 (查表数学)
  读取方: PAL3 语料 0 读取 (写入通道; 消费方在 DLL 侧/ScriptVM) ⇒ 值语义阻塞

三段式: m_nEffParamXX(伪语义) → m_n<TriggerAPI>Params[4](调用链派生, 本轮)
        → 真语义名(待读取方定谳, 挂账)
另: 0x88 m_fRoleTargetParam type float→int (下标用法直证: 4*idx+24 数组寻址)

用法: python3 tools/sem_conv_r4_stageroledata_20261120.py [--dry]
归档: data/annotations/archive/stageroledata_rename_20261120.json
"""
import json
import sys
from pathlib import Path

REPO = Path(__file__).parent.parent
DRY = '--dry' in sys.argv

fp = REPO / 'data/annotations/structs/tagStageRoleData.json'
d = json.loads(fp.read_text(encoding='utf-8'))
km = d['known_members']

GROUPS = [
    ('0x1c', ['0x1c', '0x20', '0x24', '0x28'], 'm_nLoadLinkerParams',
     'CCBStage::Proceed 写519×4 ← CCBStageEffect::LoadLinker 调链'),
    ('0x2c', ['0x2c', '0x30', '0x34', '0x38'], 'm_nSetAliveParams',
     'CCBStage::SetMaxBlend 写[128,323,519,716] ← CCBStage::SetAlive 调链'),
    ('0x3c', ['0x3c', '0x40', '0x44', '0x48'], 'm_nSetVisibleParams',
     'CCBStage::SetPause 写545×4 ← CCBStage::SetVisible 调链'),
    ('0x4c', ['0x4c', '0x50', '0x54', '0x58'], 'm_nOnChangeActionParams',
     'CCBStage::CheckAction 写[121,316,512,709] ← CCBStage::OnChangeAction 调链'),
]

archive = {'_doc': 'tagStageRoleData 渐进正名 2026-11-20 (三段式中间态)',
           'renamed_groups': [], 'type_fix': None, 'kept': []}

for base_off, offs, new_name, ev in GROUPS:
    old_names = [km[o]['name'] for o in offs]
    assert all(o in km for o in offs), offs
    # 数组化: 基偏移一条 int[4]
    km[base_off] = {
        'name': new_name,
        'type': 'int[4]',
        'source': '装载槽组数组化: %s | 值语义阻塞(读取方 DLL 侧, 语料0读取)——'
                  '真语义名待读取方定谳' % ev,
        'evidence_level': 'binary_call_chain',
        'superseded': old_names,
    }
    for o in offs[1:]:
        del km[o]
    archive['renamed_groups'].append({'base': base_off, 'new': new_name,
                                      'superseded': old_names, 'evidence': ev})

# 0x88 type 修正: float→int (下标用法 A 级直证)
m88 = km.get('0x88') or {}
if m88.get('type') == 'float':
    m88['type'] = 'int'
    m88['source'] = (m88.get('source') or '') + ' | type修正float→int 20261120: ' \
        'UpdateSlotTimer 下标用法直证(4*LODWORD+24 数组寻址)'
    archive['type_fix'] = {'offset': '0x88', 'change': 'float→int',
                           'evidence': '4*LODWORD(m_fRoleTargetParam)+24 下标寻址'}

if not DRY:
    fp.write_text(json.dumps(d, ensure_ascii=False, indent=1), encoding='utf-8')
    outp = REPO / 'data/annotations/archive/stageroledata_rename_20261120.json'
    outp.write_text(json.dumps(archive, ensure_ascii=False, indent=1), encoding='utf-8')
    print('归档 ->', outp.name)
print('组正名 %d 组(12成员→4数组成员) (dry=%s)' % (len(archive['renamed_groups']), DRY))
for g in archive['renamed_groups']:
    print('  %s: %s -> %s[4]' % (g['base'], '+'.join(g['superseded']), g['new']))
