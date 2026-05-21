#!/usr/bin/env python3
"""
从 PAL3patch 导入字段名到 annotations
策略：保留 annotations 的偏移和类型（更完整），导入 PAL3patch 的语义字段名
"""
import json
from pathlib import Path
from typing import Dict, List, Tuple

PROJECT_ROOT = Path(__file__).parent.parent
ANN_DIR = PROJECT_ROOT / 'data/annotations/structs'

# PAL3patch 结构体定义（手动整理，确保偏移正确）
PAL3PATCH_DEFS = {
    'UIWnd': [
        (0, 'vfptr', 'UIWndVtbl *'),
        (4, 'm_fontcolor', 'gbColorQuad'),
        (8, 'm_wndcolor', 'gbColorQuad'),
        (12, 'm_id', 'unsigned int'),
        (16, 'm_rect', 'tagRECT'),
        (32, 'm_pfather', 'UIWnd *'),
        (36, 'm_childs', 'PtrArray'),
        (52, 'm_bcreateok', 'int'),
        (56, 'm_bvisible', 'int'),
        (60, 'm_benable', 'int'),
        (64, 'm_bfocus', 'int'),
    ],
    'CCBUI': [
        # 基础面板和序列（152-255）
        (152, 'm_pAttackSequenBack', 'UIStatic *'),
        (156, 'm_pAttackSequenFace', 'UIStatic *[11]'),
        (200, 'm_pRoleStatePanel', 'UIStatic *[4]'),
        (216, 'm_pRoleStateFace', 'UIStatic *[5]'),
        (236, 'm_pRoleStateFaceName', 'UIStatic *[5]'),
        # Union: 19 种状态数组（256-1091，共享内存）
        (256, 'm_pRoleStateAttackInc', 'UIStatic *[11]'),
        (256, 'm_pRoleStateAttackDec', 'UIStatic *[11]'),
        (256, 'm_pRoleStateDefenceInc', 'UIStatic *[11]'),
        (256, 'm_pRoleStateDefenceDec', 'UIStatic *[11]'),
        (256, 'm_pRoleStateLuckInc', 'UIStatic *[11]'),
        (256, 'm_pRoleStateLuckDec', 'UIStatic *[11]'),
        (256, 'm_pRoleStateSpeedInc', 'UIStatic *[11]'),
        (256, 'm_pRoleStateSpeedDec', 'UIStatic *[11]'),
        (256, 'm_pRoleStateStable', 'UIStatic *[11]'),
        (256, 'm_pRoleStateBlank', 'UIStatic *[11]'),
        (256, 'm_pRoleStateForbid', 'UIStatic *[11]'),
        (256, 'm_pRoleStateSleep', 'UIStatic *[11]'),
        (256, 'm_pRoleStateChaos', 'UIStatic *[11]'),
        (256, 'm_pRoleStateMad', 'UIStatic *[11]'),
        (256, 'm_pRoleStateMirror', 'UIStatic *[11]'),
        (256, 'm_pRoleStateWall', 'UIStatic *[11]'),
        (256, 'm_pRoleStateBound', 'UIStatic *[11]'),
        (256, 'm_pRoleStateHermit', 'UIStatic *[11]'),
        (256, 'm_pRoleStateImmunity', 'UIStatic *[11]'),
        (256, 'm_pRoleSpecState', 'UIStatic *[19][11]'),
        # Union 后继续（1092-1247）
        (1092, 'm_pWinPanel', 'UIStatic *'),
        (1096, 'm_pLosePanel', 'UIStatic *'),
        (1100, 'm_pRoleStateHP', 'UIProgressBar *[4]'),
        (1116, 'm_pRoleStateGP', 'UIProgressBar *[4]'),
        (1132, 'm_pRoleStateMP', 'UIProgressBar *[4]'),
        (1148, 'm_pRoleStateSword', 'UIProgressBar *'),
        (1152, 'm_pTrickName', 'UIStaticCB *'),
        (1156, 'm_pTrickName2', 'UIStaticCB *'),
        (1160, 'm_pDialogBack', 'UIStatic *'),
        (1164, 'm_pResultLevelup', 'UIStatic *'),
        (1168, 'm_pResultWindLvup', 'UIStatic *'),
        (1172, 'm_pResultThunderLvup', 'UIStatic *'),
        (1176, 'm_pResultWaterLvup', 'UIStatic *'),
        (1180, 'm_pResultFireLvup', 'UIStatic *'),
        (1184, 'm_pResultEarthLvup', 'UIStatic *'),
        (1188, 'm_pResultDoubleLvup', 'UIStatic *'),
        (1192, 'm_pResultGetItem', 'UIStatic *'),
        (1196, 'm_pMain', 'CCBControlWindow *'),
        (1200, 'm_pItemWindow', 'CCBItemWindow *'),
        (1204, 'm_pMagicWindow', 'CCBMagicWindow *'),
        (1208, 'm_pSkillWindow', 'CCBSkillWindow *'),
        (1212, 'm_pAIWindow', 'CCBAIWindow *'),
        (1216, 'm_pLineupWindow', 'CCBLineupWindow *'),
        (1220, 'm_pProtectWindow', 'CCBProtectWindow *'),
        (1224, 'm_pResultWindow', 'CCBResultWindow *[4]'),
        (1240, 'm_pCBSystem', 'CCBSystem *'),
        (1244, 'm_pUtil', 'CUtil *'),
        (1248, 'm_Task', 'tagUITask[20]'),
    ],
}


def load_annotation(struct_name: str) -> Dict:
    """加载 annotation"""
    ann_file = ANN_DIR / f'{struct_name}.json'
    with open(ann_file, encoding='utf-8') as f:
        return json.load(f)


def save_annotation(struct_name: str, data: Dict):
    """保存 annotation"""
    ann_file = ANN_DIR / f'{struct_name}.json'
    with open(ann_file, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)


def merge_pal3patch_names(struct_name: str, pal3patch_fields: List[Tuple[int, str, str]]):
    """
    合并 PAL3patch 字段名到 annotations
    """
    # 加载现有 annotation
    ann = load_annotation(struct_name)
    members = ann['known_members']

    changes = []

    for offset, pal3_name, pal3_type in pal3patch_fields:
        offset_str = str(offset)

        if offset_str not in members:
            print(f'  ⊘ offset {offset}: PAL3patch 有但 annotations 无')
            continue

        member = members[offset_str]
        old_name = member['name']
        old_type = member['type']

        # 检查是否需要更新名称
        name_changed = False
        if old_name.startswith('_todo_') or old_name.startswith('_field_'):
            # 当前是占位符名称，使用 PAL3patch 的语义名称
            member['name'] = pal3_name
            name_changed = True

        # 检查类型是否匹配（标准化后比较）
        normalized_old = old_type.replace('unsigned int', 'DWORD').replace('tagRECT', 'RECT')
        normalized_new = pal3_type.replace('DWORD', 'unsigned int').replace('RECT', 'tagRECT')

        type_mismatch = (normalized_old != normalized_new and
                        normalized_old != pal3_type and
                        old_type != normalized_new)

        if name_changed:
            changes.append({
                'offset': offset,
                'old_name': old_name,
                'new_name': pal3_name,
                'type': old_type,
                'type_match': not type_mismatch,
            })

            # 更新 source
            member['source'] = f'PAL3patch:pal3.h → {member.get("source", "unknown")}'

        elif type_mismatch:
            print(f'  ⚠ offset {offset} ({old_name}): 类型不匹配')
            print(f'      annotations: {old_type}')
            print(f'      PAL3patch:   {pal3_type}')

    if changes:
        print(f'\n  ✓ 更新 {len(changes)} 个字段名:')
        for change in changes:
            match_mark = '✓' if change['type_match'] else '⚠'
            print(f'    {match_mark} {change["offset"]:4d}: {change["old_name"]:20s} → {change["new_name"]:20s} ({change["type"]})')

        # 保存更新后的 annotation
        save_annotation(struct_name, ann)
        print(f'\n  💾 已保存: {struct_name}.json')

        return len(changes)
    else:
        print(f'  ℹ 无需更新')
        return 0


def main():
    """主函数"""
    print('从 PAL3patch 导入字段名到 annotations\n')

    total_updated = 0

    for struct_name, pal3patch_fields in PAL3PATCH_DEFS.items():
        print(f'=== {struct_name} ===')
        count = merge_pal3patch_names(struct_name, pal3patch_fields)
        total_updated += count
        print()

    print(f'总计更新: {total_updated} 个字段')

    return 0


if __name__ == '__main__':
    exit(main())
