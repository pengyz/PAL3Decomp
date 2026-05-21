# PAL3patch 结构体定义导入总结

## 概述

PAL3patch 是 zhangboyang 的开源逆向项目，包含高质量的游戏结构体定义。
位置：`extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h`（1872 行）

## 解析结果

共解析出 **110 个结构体定义**，包括：

### 基础类型
- `gbVec3D` (12 bytes): float x, y, z
- `gbQuaternion` (16 bytes): float x, y, z, w
- `gbMatrix4` (64 bytes): 4x4 矩阵
- `gbColorQuad` (4 bytes): 颜色值
- `PtrArray` (16 bytes): 动态指针数组

### UI 类
- `UIWnd` (68 bytes) — **完全匹配我们的 annotations (0-64 offsets)**
- `UIFrameWnd` (1 field)
- `UIStatic` (16 fields)
- `UIButton` (16 fields)
- `UIListBox` (18 fields)
- `UIScrollBar` (16 fields)
- `UIProgressBar` (34 fields)
- `UIDialog`, `UITextArea`, `UIRoleSelect` 等

### 战斗系统类
- **`CCBUI`** (24 fields) — 战斗UI，包含大量语义字段名
  - 攻击序列面板指针数组
  - 角色状态面板指针数组（4个角色）
  - 各种状态图标（攻击↑↓、防御↑↓、幸运、速度、眠、乱、禁等19种状态×11个格子）
  - 血条/气条/神条进度条（HP/GP/MP）
  - 胜利/失败面板
  - 战斗结果面板（升级、获得物品等）
- `CCBSystem` (30 fields)
- `CCBAttackSequen` (7 fields)
- `tagRoleState`/`CCBRoleState`
- `tagCmdData`

### 3D 渲染类
- `gbCamera` (12 fields)
- `ObjectCamera` (13 fields)
- `gbGfxManager_D3D` (26 fields)
- `RenderTarget` (2 fields)
- `gbTexture`, `gbTexture_D3D`

### 其他游戏逻辑类
- `ScriptData`, `RestScript`, `TxtFile`
- `CPK`, `CPKHeader`, `CPKTable` (CPK 文件系统)
- `SoundMgr`, `gbAudioManager` (音频)
- `HeadMsg`, `UIEmote` (头顶消息、表情)
- `UIGameFrm`, `UISceneFrm`, `UIGameOver`

## 关键发现

### 1. UIWnd 定义验证

PAL3patch UIWnd (68 bytes):
```
   0: UIWndVtbl *          vfptr
   4: gbColorQuad          m_fontcolor
   8: gbColorQuad          m_wndcolor
  12: DWORD                m_id
  16: RECT                 m_rect
  32: UIWnd *              m_pfather
  36: PtrArray             m_childs
  52: int                  m_bcreateok
  56: int                  m_bvisible
  60: int                  m_benable
  64: int                  m_bfocus
```

**结论**：我们的 annotations (88 bytes) **更完整**，包含 offset 68-87 的额外字段：
- 68: _todo_044 (unsigned char)
- 72: _todo_048 (int)
- 76: m_fScaleX (float)
- 80: m_fScaleY (float)
- 84: _todo_054 (int)

offset 0-64 的定义**完全一致**（类型/偏移都匹配）。

### 2. 类型对应关系

| PAL3patch | annotations | 说明 |
|-----------|-------------|------|
| DWORD | unsigned int | 等价 |
| RECT | tagRECT | 等价 |
| UIWndVtbl * | int (vfptr) | annotations 简化为 int |
| struct T | T | annotations 不使用 struct 前缀 |

### 3. 我们 annotations 的优势

- **更完整的字段覆盖**：UIWnd 88 bytes vs PAL3patch 68 bytes
- **已有正确的类型**：offset 52-64 的 int 字段（之前误报为 float，现已修正）
- **包含运行时字段**：如 m_fScaleX/Y（缩放因子，PAL3patch 可能不关注）

## 导入策略

### 阶段 1：验证已有定义（完成）

✓ UIWnd 验证通过，offset 0-64 完全匹配

### 阶段 2：导入语义字段名（进行中）

对于包含 `_todo_` / `_field_` 占位符名称的字段，如果 PAL3patch 有对应偏移的语义名称，则导入。

**优先处理的结构体**：
1. **CCBUI** — 战斗UI，24个字段，全部有语义名称
2. **UIStatic** — 16个字段
3. **UIButton** — 16个字段
4. **UIListBox** — 18个字段
5. **UIProgressBar** — 34个字段
6. **CCBSystem** — 30个字段

### 阶段 3：填补空白结构体（TODO）

对于 annotations 中完全缺失的结构体，从 PAL3patch 创建初始定义：
- gbVec3D
- gbQuaternion
- gbCamera
- gbAudioManager

## 工具

已创建：
- `pipeline/parse_pal3patch_structs.py` — 解析 pal3.h 结构体定义
- `pipeline/merge_pal3patch_names.py` — 合并字段名到 annotations

## 下一步

1. 扩展 `merge_pal3patch_names.py` 的 `PAL3PATCH_DEFS` 字典，手动整理 CCBUI, UIStatic 等结构体的字段定义
2. 批量导入语义字段名
3. 验证导入后的定义是否影响编译
4. 提交更新

## 参考

- PAL3patch 项目：https://github.com/zhangboyang/PAL3patch
- 定义文件：`extra/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h`
- 逆向笔记：`extra/PAL3patch/notes/pal3/known_classes.txt`
