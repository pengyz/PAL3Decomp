#!/usr/bin/env python3
"""[static→flags 迁移 + 26 条矛盾裁决 2026-11-23] 用户方案落地.

背景: apply 链恢复后语料 signature 渲染, emit_headers P-A16 static 覆盖压过
thiscall ⇒ 头=static+显式this参 vs 定义/调用点=成员形 ⇒ C2511/C2660 显形.
用户裁定: static 标记迁移 flags(发射唯一决策源=flags), check 增前置门对
static+thiscall 矛盾组合拒绝准入.

裁决(三证: ①体 this 使用 ②原始二进制调用点 ecx 纪律 ③sig_model cc;
探针 tools/static_thiscall_adjudicator_20261123.py → 落档
data/status/static_thiscall_adjudication_20261123.json):

  A 组(19) static 错误 → 字段删除, 不入 flags, cc=thiscall 保留.
    证据: 调用点 ecx 装载实锤(thiscall ABI 真值; 静态形调用点编译产物
    push实参 无 ecx 装载 ⇒ 被调方读 ecx=垃圾 ⇒ 运行期 ABI 本就坏).
    AllocEffect 由 vtable 虚工厂成员资格补强(vtable 槽不可能 static).
  B 组(7) static 正确 → flags+=static, sig_model cc thiscall→cdecl/stdcall.
    证据: 全调用点无 ecx 写(carry-in)/fn 指针按值传递(RegisterCallbacks
    限定名裸引=static 才合法)/DLGPROC API 契约(stdcall, 反汇编定谳在册).
    目标形=ProcessMouse 在库先例(static+cdecl 渲染一致).
  其余(73) 合法组合 → 字段退役 flags+=static, 语义不变.
"""
import glob
import json
import os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCTS = os.path.join(REPO, 'data', 'annotations', 'structs')

# A 组: static 错误, cc=thiscall 真值 (19)
A_GROUP = [
    ('Actor.json', '0x00538d20', 'CompareModelName'),
    ('ArcLocaleRole.json', '0x004afd80', 'ParseLocaleData'),
    ('Array.json', '0x004115c0', 'PartialSort'),
    ('CCBLineupWindow.json', '0x0051d610', 'SetFaceLineup'),
    ('CCBUICtrl.json', '0x004e53c0', 'SendWindowMessage'),
    ('CCBUICtrl.json', '0x004e53e0', 'FormatCombatBuffer'),
    ('CEffModel.json', '0x004cfd00', 'AllocEffect'),
    ('Camera.json', '0x0041e7d0', 'CheckCollision1'),
    ('Camera.json', '0x0041ea00', 'CheckCollision2'),
    ('InputSystem.json', '0x00410360', 'ProcessFrame'),
    ('PalScript.json', '0x00433f90', 'ProcessGBKString'),
    ('PtrArray.json', '0x00433dc0', 'CopyRange'),
    ('RoleSystem.json', '0x00410430', 'RenderMainRole'),
    ('RoleSystem.json', '0x004126d0', 'GetAnimOffset'),
    ('RoleSystem.json', '0x004161e0', 'ScaleVector'),
    ('RoleSystem.json', '0x00532960', 'ScaleValue'),
    ('SceneObj.json', '0x0053ef60', 'LoadFromConfig'),
    ('UIScene.json', '0x004235b0', 'ProcessInput'),
    ('ScriptSystem.json', '0x0040cbd0', 'PassThrough'),
]
# B 组: static 真值, cc 改 (7)
B_GROUP = [
    ('PAL3.json', '0x00407180', 'StartWolf', 'cdecl'),
    ('PtrArray.json', '0x0040dcd0', 'CompareValues', 'cdecl'),
    ('ScriptSystem.json', '0x0040cbb0', 'GetScriptContext', 'cdecl'),
    ('ScriptSystem.json', '0x0040cc00', 'CheckEventType', 'cdecl'),
    ('SceneMgr.json', '0x00423500', 'ClearInactiveRoles', 'cdecl'),
    ('Logger.json', '0x0053ce20', 'WriteRoleNames', 'cdecl'),
    ('CCBStageCam.json', '0x004ea590', 'DlgProc', 'stdcall'),
]

EV = ' | [static裁决 20261123] 探针 static_thiscall_adjudicator_20261123'


def main():
    ledger = {'a_group_dropped': [], 'b_group_recsed': [], 'migrated': []}
    b_lookup = {(f, a): (nm, cc) for f, a, nm, cc in B_GROUP}
    a_lookup = {(f, a): nm for f, a, nm in A_GROUP}

    for fp in sorted(glob.glob(os.path.join(STRUCTS, '*.json'))):
        base = os.path.basename(fp)
        d = json.load(open(fp, encoding='utf-8'))
        dirty = False
        for a, m in (d.get('methods') or {}).items():
            if 'static' not in m:
                continue
            _anorm = a.lower()
            if (base, _anorm) in a_lookup:
                nm = a_lookup[(base, _anorm)]
                sm = m.get('sig_model') or {}
                assert sm.get('cc') == 'thiscall', \
                    '%s.%s A组cc=%r≠thiscall' % (base, a, sm.get('cc'))
                del m['static']
                m['name_note'] = ((m.get('name_note') or '') +
                                  EV + ' 调用点ecx装载实锤=thiscall ABI真值, '
                                  'static标记删除(静态形调用点push实参无ecx=运行期ABI坏). '
                                  'cc=thiscall保留').strip(' |')
                ledger['a_group_dropped'].append([base, _anorm, nm])
                dirty = True
            elif (base, _anorm) in b_lookup:
                nm, newcc = b_lookup[(base, _anorm)]
                sm = m.get('sig_model') or {}
                assert sm.get('cc') == 'thiscall', \
                    '%s.%s B组cc=%r≠thiscall' % (base, a, sm.get('cc'))
                m['flags'] = list(dict.fromkeys((m.get('flags') or []) + ['static']))
                oldcc = sm['cc']
                sm['cc'] = newcc
                del m['static']
                m['name_note'] = ((m.get('name_note') or '') +
                                  EV + ' 全调用点无ecx写/fn指针值传递/DLGPROC API契约'
                                  '——static成员形正确(ProcessMouse在库先例), '
                                  'sig_model cc %s→%s(IDB归属惯性矫正)' % (oldcc, newcc)).strip(' |')
                ledger['b_group_recsed'].append([base, _anorm, nm, oldcc, newcc])
                dirty = True
            else:
                m['flags'] = list(dict.fromkeys((m.get('flags') or []) + ['static']))
                sm = m.get('sig_model') or {}
                assert sm.get('cc') != 'thiscall', \
                    '%s.%s 迁移遇未裁决thiscall矛盾(cc=%r)——先裁决再迁移' % (base, a, sm.get('cc'))
                del m['static']
                m['name_note'] = ((m.get('name_note') or '') +
                                  ' | [static迁移 20261123] static:true字段退役→flags'
                                  '(发射唯一决策源=flags), 语义不变').strip(' |')
                ledger['migrated'].append([base, _anorm, str(m.get('name'))])
                dirty = True
        if dirty:
            json.dump(d, open(fp, 'w', encoding='utf-8'),
                      ensure_ascii=False, indent=1)

    out = os.path.join(REPO, 'data', 'status',
                       'static_flags_migration_20261123.json')
    json.dump(ledger, open(out, 'w', encoding='utf-8'),
              ensure_ascii=False, indent=1)
    print('A组删static: %d' % len(ledger['a_group_dropped']))
    print('B组改cc+留static: %d' % len(ledger['b_group_recsed']))
    print('迁移合法组合: %d' % len(ledger['migrated']))
    print('落档', out)


if __name__ == '__main__':
    main()
