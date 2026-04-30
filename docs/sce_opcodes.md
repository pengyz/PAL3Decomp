# SCE 脚本引擎 Opcode 表

来源：OpenPAL3 (dontpanic92) - yaobow/shared/src/scripting/sce/vm.rs

## 概述

PAL3 使用自定义的 SCE (Script Engine) 字节码虚拟机。
- 基于栈/寄存器混合模型
- 每条指令由 2 字节 opcode + 2 字节 flags + 可变参数组成
- 局部变量使用 int16 索引（负数为全局变量）
- 全局变量 -32768 (0x8000) 为主线剧情进度

## 指令格式

```
[opcode: i16] [access_local_var: i16] [params...]
```

## 完整 Opcode 列表

### 流程控制 (Control Flow)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 1 | Idle | f32 length | 等待指定时间(秒) |
| 2 | ScriptRunMode | i32 mode | 设置脚本执行模式 (0=连续, 1=逐命令) |
| 3 | Goto | u32 offset | 无条件跳转到偏移 |
| 12 | TestGoto | u32 offset | 条件跳转（检查上一个比较结果） |
| 16 | Call | u32 proc_id | 调用子过程 |

### 比较指令 (Comparison)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 5 | FOP | i32 op | 标志位操作 |
| 6 | GT | i16 var, i32 value | 大于比较 |
| 7 | LS | i16 var, i32 value | 小于比较 |
| 8 | EQ | i16 var, i32 value | 等于比较 |
| 9 | NEQ | i16 var, i32 value | 不等于比较 |
| 10 | GEQ | i16 var, i32 value | 大于等于比较 |
| 11 | LEQ | i16 var, i32 value | 小于等于比较 |
| 19 | Between | i16 var, i32 lb, i32 rh | 区间判断 (lb <= var <= rh) |

### 变量操作 (Variables)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 13 | Let | i16 var, i32 value | 设置变量值 |
| 17 | Rnd | i16 var, i32 value | 随机数 (0~value) 赋给变量 |

### 角色控制 (Role)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 20 | RolePathTo | i32 role, i32 x, i32 y, i32 unknown | 角色寻路移动到坐标 |
| 21 | RoleSetPos | i32 role, i32 x, i32 y | 直接设置角色位置 |
| 22 | RoleShowAction | i32 role, string action, i32 repeat | 播放角色动作 |
| 23 | RoleSetFace | i32 role, i32 direction | 设置角色朝向 |
| 24 | RoleTurnFace | i32 role, i32 degree | 角色转身 |
| 25 | TeamOpen | 无 | 队伍跟随开启 |
| 26 | TeamClose | 无 | 队伍跟随关闭 |
| 27 | RoleInput | i32 enable | 启用/禁用玩家输入 |
| 28 | RoleActive | i32 role, i32 active | 角色激活/隐藏 |
| 29 | RoleScript | i32 role, i32 proc_id | 绑定脚本到角色 |
| 71 | RoleStop | i32 role_id | 停止角色行为 |
| 72 | RoleEmote | i32 role, i32 emote_id | 角色表情动画 |
| 74 | Climb | i32, i32 | 攀爬 |

### 镜头控制 (Camera)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 30 | CameraFocusRole | i32 role | 镜头聚焦角色 |
| 31 | CameraFocusPoint | f32 x, f32 y, f32 z | 镜头聚焦点 |
| 32 | CameraPush | f32, f32, i32 | 镜头推进 |
| 33 | CameraRotate | f32 rot_x, f32 rot_y, f32 duration, i32 unknown | 镜头旋转 |
| 34 | CameraMove | f32 x, f32 y, f32 z, f32 unk1, f32 unk2 | 镜头移动 |
| 35 | CameraWag | f32, f32, f32, i32 | 镜头晃动 |
| 36 | CameraSet | f32 y_rot, f32 x_rot, f32 unk, f32 x, f32 y, f32 z | 直接设置镜头 |
| 37 | CameraDefault | i32 unknown | 恢复默认镜头 |
| 38 | CameraPushState | 无 | 保存镜头状态 |
| 39 | CameraPopState | 无 | 恢复镜头状态 |

### 对话系统 (Dialog)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 62 | Dlg | string text | 显示对话文本 |
| 65 | DlgSel | list options | 显示选项列表 |
| 66 | GetDlgSel | i16 var | 获取玩家选择结果 |
| 67 | DlgFace | i32 id, string face, i32 left_right | 设置对话头像 |
| 68 | Note | string text | 显示提示文本 |
| 76 | DlgTime | string text | 限时对话 |
| 77 | GetTimeSel | i16 var | 获取限时选择结果 |
| 86 | Caption | string text, i32 | 字幕 |

### 场景控制 (Scene)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 63 | LoadScene | string name, string sub_name | 加载场景 |
| 69 | FadeOut | 无 | 黑色淡出 |
| 70 | FadeIn | 无 | 黑色淡入 |
| 81 | FadeOutWhite | 无 | 白色淡出 |
| 91 | FadeInWhite | 无 | 白色淡入 |
| 85 | ObjectActive | i32 obj_id, i32 active | 场景物体激活 |
| 87 | OpenDoor | i32 door_id | 开门 |
| 90 | ObjectMove | i32, f32, f32, f32, f32 | 物体移动 |
| 118 | Quake | f32 duration, f32 amplitude | 屏幕震动 |
| 124 | Trigger | i32 | 触发器 |

### 物品/经济 (Items/Economy)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 46 | AddItem | i32 item_id, i32 count | 添加物品 |
| 47 | RemoveItem | i32 item_id | 移除物品 |
| 48 | AddMoney | i32 amount | 增加金钱 |
| 49 | GetMoney | i16 var | 获取金钱数 |
| 50 | GetFavor | i16 var, i32 role | 获取好感度 |
| 51 | AddSkill | i32 role, i32 skill_id | 学会技能 |
| 52 | GetFavorite | i16 var | 获取收藏品 |
| 78 | HaveItem | i32 item_id | 检查是否有物品 |

### 战斗 (Combat)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 80 | CombatBoss | i32*6 | Boss 战设定 |
| 82 | CombatMaxRound | i32 rounds | 设定最大回合数 |
| 83 | CombatMustFail | 无 | 必败战斗 |
| 113 | StartHideFight | 无 | 开始暗雷战 |
| 131 | CombatNotGameOver | 无 | 战败不结束游戏 |
| 132 | GetCombat | i16 var | 获取战斗结果 |

### 特殊功能 (Special)

| Opcode | 名称 | 参数 | 说明 |
|--------|------|------|------|
| 42 | LK_Ghost | i32 | 锁妖塔相关 |
| 43 | FavorAdd | i32 role, i32 amount | 增加好感度 |
| 54 | FullRoleAtt | i32 role, i32 type | 恢复角色属性 |
| 79 | PlaySound | string name, i32 repeat | 播放音效 |
| 88 | HY_Mode | i32 mode | 花盈模式 |
| 89 | HY_FLY | f32 x, f32 y, f32 z | 花盈飞行 |
| 102 | SwitchRS | i32 | 切换渲染状态 |
| 104 | APPREntry | 无 | 鉴定入口 |
| 106 | ENCAMP_Entry | i32 | 安营入口 |
| 107 | SKEE_Entry | i32 | 滑雪入口 |
| 108 | GetAppr | i16 var | 获取鉴定结果 |
| 109 | EnableSword | i32 | 启用/禁用仙剑 |
| 111 | SpecifyCompos | i32 | 指定合成配方 |
| 115 | Movie | string name | 播放过场视频(.bik) |
| 116 | SetRoleTexture | i32 role, string tex | 设置角色贴图 |
| 117 | Rotate | i32, i32, i32 | 旋转 |
| 119 | ShowChatRest | string config, u32 enough_proc, u32 not_enough_proc, u32 after_rest_proc | 显示客栈 |
| 125 | SetBigMapElement | i32 id, i32 option | 设置大地图元素 |
| 126 | GetSwitch | string, i32, i16 | 获取开关状态 |
| 127 | EntryRow | i32 id, i32 proc_id | 划船入口 |
| 128 | RotateInv | i32, i32, i32 | 反向旋转 |
| 130 | Dist | i16, i16 | 距离计算 |

## 数据类型读取

SCE 二进制中的参数按照以下方式编码：
- `i16`: 2 字节有符号整数（小端序）
- `i32`: 4 字节有符号整数（小端序）
- `u32`: 4 字节无符号整数（小端序）
- `f32`: 4 字节 IEEE 浮点（小端序）
- `string`: 以 0x00 结尾的 GBK 编码字符串
- `list`: 字符串列表（多个以 0x00 分隔的字符串，以双 0x00 结束）

## 全局变量约定

- 变量索引 < 0: 全局变量
- 变量索引 >= 0: 局部变量（每个 proc 独立）
- 变量 -32768 (0x8000): 主线剧情进度 (MainStory)
