#!/usr/bin/env python3
"""
清理CCBUI中无二进制验证的PDB字段，导入PAL3patch union定义
"""
import json
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
CCBUI_FILE = PROJECT_ROOT / 'data/annotations/structs/CCBUI.json'

# 需要删除的offset（无二进制访问）
OFFSETS_TO_DELETE = [
    204, 248, 292, 380, 424, 468, 512, 556,
    644, 688, 732, 776, 820, 864, 908, 952, 996
]


def main():
    with open(CCBUI_FILE) as f:
        ccbui = json.load(f)

    deleted = []
    for offset in OFFSETS_TO_DELETE:
        offset_str = str(offset)
        if offset_str in ccbui['known_members']:
            member = ccbui['known_members'][offset_str]
            deleted.append((offset, member['name']))
            del ccbui['known_members'][offset_str]

    # 添加PAL3patch union定义（placeholder）
    # Union从256开始，包含19个UIStatic *[11]数组
    ccbui['known_members']['256'] = {
        'name': 'm_pRoleSpecState',
        'type': 'UIStatic *[19][11]',
        'source': 'PAL3patch:pal3.h union definition (19 state arrays, 836 bytes total)',
        'note': 'Union of 19 state effect arrays: AttackInc/Dec, DefenceInc/Dec, LuckInc/Dec, SpeedInc/Dec, Stable, Blank, Forbid, Sleep, Chaos, Mad, Mirror, Wall, Bound, Hermit, Immunity. All arrays overlap at same memory location.',
    }

    # 保存
    with open(CCBUI_FILE, 'w') as f:
        json.dump(ccbui, f, indent=2, ensure_ascii=False)

    print(f'删除了 {len(deleted)} 个无二进制访问的PDB字段:')
    for offset, name in deleted:
        print(f'  offset {offset}: {name}')

    print()
    print('添加了 PAL3patch union 定义:')
    print('  offset 256: m_pRoleSpecState (UIStatic *[19][11], 836 bytes)')
    print()
    print(f'更新完成: {CCBUI_FILE}')


if __name__ == '__main__':
    main()
