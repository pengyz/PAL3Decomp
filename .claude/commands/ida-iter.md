---
name: ida-iter
description: 持续执行 IDA 标注迭代。从已知函数出发，BFS 遍历 callee，分析逻辑，标注函数名+签名+全局变量类型。
---

## 核心机制

**图遍历标注模型**:
```
读取已标注函数的反编译 → 找出其 sub_ callee → 分析每个 callee 的逻辑
→ 确定类名+方法名+签名 → 写 IDA 脚本标注 → 运行 IDA → 更新工作栈 → 继续
```

**数据结构**:
- 工作栈: `.claude/ida_annotation_stack.json`
- IDA 脚本: `tools/ida/pal3_manual_iterN.py`
- 反编译数据: `asm/pal3/decomp/*.json`

## 单次迭代流程

```
1. 从工作栈选取下一个目标函数（优先大函数、核心路径）
2. 读取该函数的 decomp JSON
3. 提取所有 sub_XXXXX callee
4. 对每个 callee:
   a. 读取其 decomp JSON（签名 + 函数体前几行）
   b. 分析 this-source: 调用时传入的第一参数是哪个全局变量？
      - func(g_pSceneMgr, ...) → SceneMgr::Method
      - func(&g_Logger, ...) → Logger::Method
      - func(&g_GameData, ...) → CGameData::Method
   c. 分析函数体逻辑确定方法名（Init/Destroy/Render/Update/Create/Load等）
   d. 确定完整签名: 返回类型 + 调用约定 + this类型 + 参数类型
5. 生成 IDA 标注脚本 (tools/ida/pal3_manual_iterN.py)
6. 运行 IDA 执行标注
7. 更新工作栈
8. 继续下一个目标

## 标注规则

### 函数名格式
- 类方法: `ClassName::MethodName` (IDA 支持 :: 在函数名中)
- 自由函数: `ModuleName` (如 `InitLogFiles`, `PopMatrixStacks`)
- 构造函数: `ClassName::ClassName`
- 析构函数: `ClassName::~ClassName` (可能不支持 ~, 用 Destroy)

### 签名格式
```c
// thiscall 方法
"return_type __thiscall ClassName::Method(this_type *this, param_type param, ...)"

// cdecl 自由函数
"return_type __cdecl FuncName(param_type param, ...)"

// this 类型: 如果类定义已导入用具体类型, 否则用 void*
```

### 全局变量
- 发现新的全局变量时同步命名: `ida_name.set_name(addr, "g_VarName")`
- 格式: `g_` 前缀 + 驼峰
- 已知全局列表在 `ida_annotation_stack.json` 的 globals 字段

## 分析方法（确定函数身份）

### 1. This-Source 验证（最可靠）
```
PAL3::Render 调用 sub_4CDBF0(g_pSceneMgr)
→ g_pSceneMgr 是 SceneMgr 实例
→ sub_4CDBF0 是 SceneMgr 的方法
→ 看函数体确定具体是什么方法
```

### 2. 参数模式识别
```
sub_4503D0(1002, 180, 50, this, "ui\\dlg\\headbk.tga")
→ 有 ID + 坐标 + 纹理路径 → UIDialog::Create
```

### 3. 函数体特征
```
- strlen + memcpy + _Tidy → std::string 方法 (不标注, 是 CRT)
- gbVFile + fread → LoadFromFile 类方法
- atexit + guard flag → GetInstance 单例
- memset(this, 0, size) → 构造函数
- Release + delete + =0 → Destroy/析构
```

### 4. 大小对比验证（辅助）
如果同一个类有 PDB 数据，可以按函数大小粗略对应。但不可靠——仅作辅助参考。

## 跳过策略

以下情况标记 skip 并继续:
- `__userpurge` 函数（IDA 调用约定分析错误）
- STL/CRT 区域 (0x430000-0x446000, 0x540000-0x560000)
- size <= 5B 的 thunk/jump
- 纯数学函数（sin/cos/sqrt 等）

## 质量要求

- **每个标注必须有可验证的理由**（this-source / 参数模式 / 函数体逻辑）
- **禁止聚类推断**（"被 ClassA 调用所以属于 ClassA" 是错误的）
- **签名必须完整**（返回类型 + 调用约定 + 所有参数类型）
- **全局变量同步标注**（发现新全局时立即命名）

## 工作栈结构

```json
{
  "annotated": { "0xADDR": {"name": "...", "reason": "...", "depth": N} },
  "frontier": [ {"addr": "...", "parent": "...", "depth": N, "status": "pending|done"} ],
  "globals": { "named": N, "unnamed": N, "known_names": [...] },
  "stats": { "total_annotated": N, "current_depth": N }
}
```

## 迭代终止条件

当所有游戏逻辑区域 (0x401000-0x430000, 0x446000-0x540000) 的函数都已标注或标记为 skip 时，标注工作完成。之后执行一次全量导出 + hexrays_to_oop.py 后处理，生成最终源码。
