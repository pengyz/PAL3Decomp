# SCE 虚拟机内部实现分析

## 概述

PAL3 的 SCE (Script Engine) 是一个自定义字节码虚拟机，用于驱动游戏剧情、对话、镜头、战斗触发等。

- **架构**: 栈/寄存器混合模型
- **操作码数量**: 162 个（opcode 1-162）
- **实现位置**: `0x004329B0`（注册表初始化）+ `0x00424C20`（主执行循环）
- **handler 地址范围**: `0x00434000 - 0x00440000`

## 指令编码格式

```
+0: [opcode: int16]        — 操作码编号 (1-162)
+2: [param_flags: int16]   — 参数类型标志
+4: [params...]            — 变长参数数据
```

每条指令以 4 字节头部开始（2 字节 opcode + 2 字节参数标志），后跟变长参数。

## 参数类型

| 类型 ID | 名称 | 大小 | 说明 |
|---------|------|------|------|
| 1 | VAR_INT | 4 字节 | 有符号 32 位整数 |
| 2 | VAR_FLOAT | 4 字节 | IEEE 754 单精度浮点 |
| 3 | VAR_STRING | 变长 | 2 字节长度 + GBK 数据 + NUL |
| 4 | VAR_JMPFLAG | 4 字节 | 跳转偏移（字节码文件内偏移） |
| 5 | VAR_USERVAR | 2 字节 | 变量引用索引 |

## 变量系统

### 索引规则
- **局部变量**: 索引 >= 0（每个过程独立作用域）
- **全局变量**: 索引 < 0（高位 0x8000 设置时为全局）
- **特殊变量**: -32768 (0x8000) = 主线剧情进度 (MainStory)

### 访问模式
```c
uint16_t udata = read_word();
if (udata & 0x8000) {
    // 全局变量: $!%04X
    access_global(udata & 0x7FFF);
} else {
    // 局部变量: $var_%04X
    access_local(udata);
}
```

## Opcode 分派机制

### 注册表初始化 (`sub_4329B0` / 0x004329B0)

游戏启动时调用此函数，将 162 个 handler 函数指针写入全局数组：

```c
// 全局 handler 表基址: stru_D8B628._todo_C00 + 148
// 每个条目 4 字节（函数指针）
// 布局: [handler_ptr][param_type_1][param_type_2]...[param_count]

*(&table + 148) = (int)PalScript::Op_Idle;          // opcode 1
*(&table + 152) = (int)PalScript::Op_ScriptRunMode;  // opcode 2
*(&table + 156) = (int)PalScript::Op_GoTo;           // opcode 3
// ...
```

### 主执行循环 (`PalScriptMgr::ExecuteBlock` / 0x00424C20)

- 60185 字符的巨型函数
- 使用 `m_nCmdType` 字段区分命令执行阶段（40 个 case）
- 每个 case 处理特定命令类型的状态机逻辑（等待动画完成、等待移动到达等）

### 帧执行 (`PalScriptMgr::ExecuteFrame` / 0x0042F460)

- 每帧调用，处理当前命令的进度更新
- 7 个 case 处理不同的过渡动画类型

### Opcode 执行 (`PalScriptMgr::ExecuteOpcode` / 0x0042EBE0)

- 从 handler 表读取函数指针
- 通过间接调用执行对应的 opcode handler

## SCE 文件格式

### 文件头

```c
struct SceHeader {
    char    magic[4];    // "SCE\0"
    uint8_t version;     // 1
    uint16_t blocknum;   // 过程数量
};
```

### 过程索引

```c
struct SceIndex {
    uint32_t id;         // 过程 ID
    uint32_t offset;     // 字节码偏移
    char     desc[64];   // 过程名（GBK 编码）
};
```

### 过程体

- 局部变量声明区（类型 + 初始值）
- 字节码指令区（变长指令序列）

## 字符串池

- **位置**: 全局地址 `stru_D8B628` + 固定偏移
- **元素大小**: 8 字节（指针 + 元数据）
- **访问方式**: 栈式（`PalScript::GetString` 每次递减计数器返回下一个）
- **编码**: GBK（中文 GB 扩展）

## 完整 Opcode → Handler 映射表

| Opcode | 名称 | Handler 地址 | 函数名 |
|--------|------|-------------|--------|
| 1 | Idle | 0x00434CE0 | PalScript::Op_Idle |
| 2 | ScriptRunMode | 0x00434D70 | PalScript::Op_ScriptRunMode |
| 3 | GoTo | 0x00436710 | PalScript::Op_GoTo |
| 4 | FC | 0x00436730 | PalScript::Op_FC |
| 5 | FNOT | 0x00436740 | PalScript::Op_FNOT |
| 6 | FOP | 0x00436760 | PalScript::Op_FOP |
| 7 | GT | 0x00436780 | PalScript::Op_GT |
| 8 | LS | 0x004367B0 | PalScript::Op_LS |
| 9 | EQ | 0x004367E0 | PalScript::Op_EQ |
| 10 | NEQ | 0x00436860 | PalScript::Op_NEQ |
| 11 | GEQ | 0x00436890 | PalScript::Op_GEQ |
| 12 | LEQ | 0x004368E0 | PalScript::Op_LEQ |
| 13 | TestGoto | 0x00436910 | PalScript::Op_TestGoto |
| 14 | Let | 0x00436360 | PalScript::Op_Let |
| 15 | Add | 0x00436380 | PalScript::Op_Add |
| 16 | Sub | 0x004363B0 | PalScript::Op_Sub |
| 17 | Call | 0x00436A60 | PalScript::Op_Call |
| 18 | Rand | 0x00436410 | PalScript::Op_Rand |
| 19 | Between | 0x00436810 | PalScript::Op_Between |
| 20 | RolePathTo | 0x00434F90 | PalScript::Op_RolePathTo |
| 21 | RolePathOut | 0x00434ED0 | PalScript::Op_RolePathOut |
| 22 | RoleSetPos | 0x00434D90 | PalScript::Op_RoleSetPos |
| 23 | RoleShowAction | 0x00435080 | PalScript::Op_RoleShowAction |
| 24 | RoleEndAction | 0x00436190 | PalScript::Op_RoleEndAction |
| 25 | RoleSetFace | 0x00436280 | PalScript::Op_RoleSetFace |
| 26 | RoleTurnFace | 0x004365A0 | PalScript::Op_RoleTurnFace |
| 27 | TeamOpen | 0x004365B0 | PalScript::Op_TeamOpen |
| 28 | TeamClose | 0x00436600 | PalScript::Op_TeamClose |
| 29 | RoleInput | 0x00436680 | PalScript::Op_RoleInput |
| 30 | RoleActive | 0x004351A0 | PalScript::Op_RoleActive |
| 31 | RoleScript | 0x00434E50 | PalScript::Op_RoleScript |
| 32 | InTeam | 0x00437AC0 | PalScript::Op_InTeam |
| 33 | RoleSetLayer | 0x00437AE0 | PalScript::Op_RoleSetLayer |
| 34 | RoleCtrl | 0x00434E90 | PalScript::Op_RoleCtrl |
| 35 | RoleOverlap | 0x004350F0 | PalScript::Op_RoleOverlap |
| 36 | RoleScale | 0x00436240 | PalScript::Op_RoleScale |
| 37 | ShowActAutoStand | 0x004362D0 | PalScript::Op_ShowActAutoStand |
| 38 | RoleMoveBack | 0x00436130 | PalScript::Op_RoleMoveBack |
| 39 | RoleFaceRole | 0x004365C0 | PalScript::Op_RoleFaceRole |
| 40 | RoleTurnFaceA | 0x004365D0 | PalScript::Op_RoleTurnFaceA |
| 41 | TeamOpenA | 0x004387D0 | PalScript::Op_TeamOpenA |
| 42 | TeamCloseA | 0x00435010 | PalScript::Op_TeamCloseA |
| 43 | RoleSpaceWalk | 0x004353F0 | PalScript::Op_RoleSpaceWalk |
| 44 | RoleMoveTo | 0x004354F0 | PalScript::Op_RoleMoveTo |
| 45 | CameraFocusRole | 0x00435470 | PalScript::Op_CameraFocusRole |
| 46 | CameraFocusPoint | 0x00435570 | PalScript::Op_CameraFocusPoint |
| 47 | CameraPush | 0x00435600 | PalScript::Op_CameraPush |
| 48 | CameraRotate | 0x004356C0 | PalScript::Op_CameraRotate |

（完整表格见 `data/annotations/functions.json` 中 `PalScript::Op_*` 条目）

## 参考文件

- **操作码定义**: `extra/PAL3patch/extra/common/asmtool/scAsmTool/cmd_PAL3.cpp`
- **SCE 结构定义**: `extra/PAL3patch/extra/common/asmtool/scAsmTool/scAsmDefinition.h`
- **反汇编器**: `extra/PAL3patch/extra/common/asmtool/scAsmTool/scAsmDisassembler.cpp`
- **操作码说明表**: `docs/sce_opcodes.md`
- **handler 实现**: `asm/pal3/decomp/PalScript_Op_*.json`
