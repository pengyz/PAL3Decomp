---
name: pal3-pipeline
description: "PAL3 标注迭代管线 — IDA 标注→导出→codegen→编译→对比的完整工作流"
tags: [reverse-engineering, pal3, annotations, pipeline]
when_to_use: "当用户需要执行 PAL3 反编译管线流程（标注、导出、codegen、编译、字节对比）时加载"
---

# PAL3 标注迭代管线

<CRITICAL-INSTRUCTION>
**阶段分离原则**：反编译项目明确拆分为两个独立阶段：

1. **标注阶段**（当前）：还原编译过程中丢失的信息（类型、名称、结构、继承关系）。
   评价指标：check_annotations 0 errors + decomp_quality 四维指标。
   **不关注**：codegen 输出、编译错误。

2. **codegen 阶段**（未来）：将标注成果转化为可编译源码。
   评价指标：编译错误数、pass rate、字节匹配率。
   **前提**：标注质量足够高。

编译错误是 codegen 适配度的指标，不是标注正确性的指标。更精确的标注可能导致更多
编译错误（因为 codegen 尚未适配强类型代码），这是正常现象，不构成标注回退的理由。

**Annotation 是唯一手工维护的数据源**。所有修改回到 annotation，不走 IDB 直接编辑。
</CRITICAL-INSTRUCTION>

## 管线操作

所有操作通过 `python pipeline/cli.py` 统一入口：

```bash
# 完整重建（从零开始）
python pipeline/cli.py init --force      # raw IDB → 导入 PDB + FLIRT + 应用 annotation
python pipeline/cli.py export            # IDB → decomp JSONs + ida_structs.json + thunks
python pipeline/cli.py codegen all       # JSONs → .h + .cpp
python pipeline/cli.py compile           # VC6 编译

# 日常迭代（仅 annotation 更新后）
python pipeline/cli.py init              # 只 apply annotation（不重建 raw）
python pipeline/cli.py export
python pipeline/cli.py codegen all
python pipeline/cli.py compile

# 仅修改了 codegen（annotation 未变）
python pipeline/cli.py codegen all
python pipeline/cli.py compile
```

**注意**：`cli.py` 调用 IDA 时 stdout 不显示输出，运行时间 30s-5min。日志在 `pipeline/ida/_logs/`。

## 数据架构

```
data/annotations/
  ├── functions.json        — {addr: {name, signature}}
  ├── globals.json          — {addr: {name, type, overlaps_with, decomp_name}}
  ├── skip_functions.json   — {addr: {name, reason, target_name}}
  ├── structs/ClassName.json — {name, binary_size, known_members: {offset: {name, type}}}
  └── CHANGE_LOG.md         — 变更审计记录（证据+置信度）

asm/pal3/
  ├── decomp/*.json         — IDA 反编译导出（codegen 输入）
  ├── ida_structs.json      — 结构体 + 全局变量导出
  └── extra/thunks.json     — thunk 函数导出
```

## IDA 查询工具（只读）

所有脚本在 `pipeline/ida/` 下，在 IDA 中运行：

```bash
# 由 cli.py 自动调用 IDA，无需手动指定 IDA 路径
python pipeline/cli.py tool query_todo_fields     # 全局 _todo_ 字段扫描
python pipeline/cli.py tool query_class_full Name # 指定类全部方法扫描
python pipeline/cli.py tool query_highref_fields  # 补充高引用字段上下文
```

| 脚本 | 用途 | 输出位置 |
|------|------|---------|
| `query_todo_fields.py` | 全局 _todo_ 字段扫描 | `_logs/todo_field_context.json` |
| `query_highref_fields.py` | 补充高引用字段上下文 | `_logs/highref_field_context.json` |
| `query_class_full.py Name` | 指定类全部方法 | `_logs/class_full_context.json` |
| `find_strides.py` | 嵌入子对象 stride 分析 | `_logs/stride_analysis.json` |

IDA 脚本的 `print()` 不显示在终端，所有输出写入 `pipeline/ida/_logs/` 目录。

## 置信度规则

| 等级 | 类型 | 分值 | 示例 |
|------|------|------|------|
| A | 二进制指令 reg+disp32 | 85 | `mov byte [esi+0xD1], 1` 且 esi=this |
| A+ | apply 后 Hex-Rays 偏移 | 85 | 结构体正确时 `this+484` |
| B | 3+ 条 A 级交叉确认 | 80+ | 多函数同偏移同访问模式 |
| C | Hex-Rays 文本推断（未 apply） | 50 | 不可单独用于偏移修改 |
| D | 语义推断 | 30 | 从调用上下文猜测 |

**提交阈值**：偏移修改≥80，类型修改≥70，字段命名≥60，结构体 size≥85。

## 禁止行为

1. **禁止从 Hex-Rays 反编译文本推断偏移**——除非 IDB 已 apply_annotations 且结构体正确
2. **禁止批量修改未验证字段**——每个偏移/类型变更必须逐一验证
3. **禁止仅凭 PDB 数据修改**——PAL3A PDB 偏移可能与 PAL3 不同
4. **禁止提交无 A 级证据的偏移/类型修改**
5. **禁止伪语义命名**——`m_nState_4968` 没有语义价值，不如 `_todo_`
6. **禁止对 IDA 查询工具输出不加验证直接命名**——工具提供候选，人工判断拍板
7. **禁止仅凭 signature this 类型修正函数归属**——必须有 decomp member access evidence
8. **禁止用编译错误评判标注质量**——codegen 适配问题，不是标注问题

## Phantom Global 处理

`globals.json` 中某些全局变量的地址落在更大的结构体内部（如 `g_ScriptRoleBuf` 在 `g_SceneMgr` 内）。

**处理流程**：
1. 确认地址落在某 `struct_instance` 范围内
2. 在父结构体的 `known_members` 中添加对应偏移的字段定义
3. 在 `globals.json` 中将该全局标记为 `"type": "skip"`，`reason` 注明父结构体
4. 重新 export + codegen 后通过 `_resolve_offset` 递归解析为 `g_StructName.member.sub_member`

**必要条件**：父结构体必须有 `binary_size`、每级结构体需有 `known_members`、struct_instances 中需有地址范围。

## 字段验证流程

1. 定位二进制证据（query_todo_fields 或 verify_offset.py）
2. 确认寄存器来源（函数头部 this 赋值模式）
3. 确认访问宽度（指令前缀：8B=4字节, C6=1字节, 66 8B=2字节, D9=float）
4. 记录证据到 CHANGE_LOG.md
5. 修改 annotation → `python pipeline/check_annotations.py` 验证
6. 提交

## 关键方法论

### 嵌入子对象发现

构造函数中 `lea ecx,[esi+offset]; call CtorFunc` 模式：
- 连续 LEA 的 stride = 子对象大小
- 调用目标 = 子对象构造函数
- stride > binary_size 时：每个 slot 含子对象 + 额外数据
- **二进制 LEA 是嵌入偏移的最终权威**，apply 后的 Hex-Rays 也可能因结构体布局错误给出偏差

### 管理器 vs 元素判别

包含对象数组的类：
- **管理器方法**：访问 count 字段 + stride 循环
- **元素方法**：在 vtable 中定义，操作单个元素内偏移
- 管理器字段在数组起始前，元素字段在 stride 范围内

### 反编译器伪像识别

`this+N` 超标函数中，约 25% 是反编译器伪像：
- ESI max ≈ 审计 max_off → 真实字段访问
- ESI max << 审计 max_off → 伪像（来自指针强制转换）
- ESI max = 0 → 伪像

处理审计条目时先过 ESI 筛子，伪像直接跳过。

## 退出条件

- 对齐违规 = 0
- `_todo_` + `_field_` 数趋于稳定
- 重建一致性 ≥95%
- sub_ 数趋于稳定

然后切换到：编译修复 → 字节匹配阶段。
