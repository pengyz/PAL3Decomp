#!/usr/bin/env python3
"""
CCBUI 完整字段列表（手动计算偏移）
UIFrameWnd baseclass = 152 bytes
"""

# 从 152 开始的 CCBUI 字段
CCBUI_FIELDS = [
    # 基础面板和序列
    (152, 'm_pAttackSequenBack', 'UIStatic *'),
    (156, 'm_pAttackSequenFace', 'UIStatic *[11]'),  # 11 × 4 = 44 bytes
    (200, 'm_pRoleStatePanel', 'UIStatic *[4]'),     # 4 × 4 = 16 bytes
    (216, 'm_pRoleStateFace', 'UIStatic *[5]'),      # 5 × 4 = 20 bytes
    (236, 'm_pRoleStateFaceName', 'UIStatic *[5]'),  # 5 × 4 = 20 bytes

    # Union: 19 种状态 × 11 个槽位 = 836 bytes (256-1091)
    # 所有状态数组共享同一块内存，都从 256 开始
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
    (256, 'm_pRoleSpecState', 'UIStatic *[19][11]'),  # 整个 union 的数组表示

    # Union 后继续
    (1092, 'm_pWinPanel', 'UIStatic *'),
    (1096, 'm_pLosePanel', 'UIStatic *'),

    # 进度条
    (1100, 'm_pRoleStateHP', 'UIProgressBar *[4]'),
    (1116, 'm_pRoleStateGP', 'UIProgressBar *[4]'),
    (1132, 'm_pRoleStateMP', 'UIProgressBar *[4]'),
    (1148, 'm_pRoleStateSword', 'UIProgressBar *'),

    # 招式名称和对话
    (1152, 'm_pTrickName', 'UIStaticCB *'),
    (1156, 'm_pTrickName2', 'UIStaticCB *'),
    (1160, 'm_pDialogBack', 'UIStatic *'),

    # 战斗结果面板（升级提示）
    (1164, 'm_pResultLevelup', 'UIStatic *'),
    (1168, 'm_pResultWindLvup', 'UIStatic *'),
    (1172, 'm_pResultThunderLvup', 'UIStatic *'),
    (1176, 'm_pResultWaterLvup', 'UIStatic *'),
    (1180, 'm_pResultFireLvup', 'UIStatic *'),
    (1184, 'm_pResultEarthLvup', 'UIStatic *'),
    (1188, 'm_pResultDoubleLvup', 'UIStatic *'),
    (1192, 'm_pResultGetItem', 'UIStatic *'),

    # 战斗子窗口
    (1196, 'm_pMain', 'CCBControlWindow *'),
    (1200, 'm_pItemWindow', 'CCBItemWindow *'),
    (1204, 'm_pMagicWindow', 'CCBMagicWindow *'),
    (1208, 'm_pSkillWindow', 'CCBSkillWindow *'),
    (1212, 'm_pAIWindow', 'CCBAIWindow *'),
    (1216, 'm_pLineupWindow', 'CCBLineupWindow *'),
    (1220, 'm_pProtectWindow', 'CCBProtectWindow *'),
    (1224, 'm_pResultWindow', 'CCBResultWindow *[4]'),

    # 战斗系统和工具
    (1240, 'm_pCBSystem', 'CCBSystem *'),
    (1244, 'm_pUtil', 'CUtil *'),

    # UI任务队列（20个，每个72字节）
    (1248, 'm_Task', 'tagUITask[20]'),  # 20 × 72 = 1440 bytes, 结束于 2688
]

# 打印验证
print("CCBUI 字段列表 (152-2688):")
print(f"共 {len(CCBUI_FIELDS)} 个字段")
print("\n前 10 个字段:")
for offset, name, type_ in CCBUI_FIELDS[:10]:
    print(f"  {offset:4d}: {name:30s} ({type_})")

print("\n最后 5 个字段:")
for offset, name, type_ in CCBUI_FIELDS[-5:]:
    print(f"  {offset:4d}: {name:30s} ({type_})")

print(f"\n总大小: {1248 + 1440} bytes (152 base + {1248 + 1440 - 152} CCBUI fields)")
