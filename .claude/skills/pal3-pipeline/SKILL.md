---
name: pal3-pipeline
description: "PAL3 标注迭代管线 — IDA 标注→导出→codegen→编译→对比的完整工作流"
tags: [reverse-engineering, pal3, annotations, pipeline]
when_to_use: "当需要执行 PAL3 反编译管线流程时加载"
---

# PAL3 标注迭代管线

## Pipeline CLI

```bash
# 完整重建
python pipeline/cli.py init --force   # raw→PDB→FLIRT→annotations→IDB
python pipeline/cli.py export         # IDB→decomp JSONs
python pipeline/cli.py codegen all    # JSONs→.h+.cpp
python pipeline/cli.py compile        # VC6 编译

# 日常迭代（只改 annotation）
python pipeline/cli.py init           # 只 apply（不重建 raw）
python pipeline/cli.py export
python pipeline/cli.py codegen all
python pipeline/cli.py compile

# 只改 codegen（annotation 未变）
python pipeline/cli.py codegen all
python pipeline/cli.py compile
```

## IDA 查询工具

```bash
python pipeline/cli.py tool query_todo_fields       # 全局 _todo_ 扫描
python pipeline/cli.py tool query_class_full Name   # 指定类全量扫描
python pipeline/cli.py tool query_highref_fields    # 补充上下文
python pipeline/cli.py tool find_strides            # stride 分析
```

输出在 `pipeline/ida/_logs/*.json`。IDA 脚本的 print() 不显示在终端。

## 证据等级（提交阈值）

- **A 级**：二进制指令 reg+disp32（偏移修改≥85）
- **B 级**：3+ 条 A 级交叉确认（≥80）
- **C 级**：Hex-Rays 文本推断（仅标注参考，不可单独用于偏移修改）
- **D 级**：语义推断（命名≥60，不可用于偏移/类型修改）

## 关键方法提醒

- **ESI 验证法**：函数内 `[esi+disp]` 最大 disp 接近审计 max_off → 真实字段；远小于 → 反编译器伪像
- **嵌入子对象**：构造函数中 `lea ecx,[esi+off]; call Ctor` → 连续 LEA 的 stride = 子对象大小。**二进制 LEA 是最终权威**，Hex-Rays 可能因结构体布局错误给出偏移偏差
- **归属判别**：函数访问大偏移(>原类 size) + 小偏移(<原类 size) → 嵌入模式，不是归属错误
- **签名修正**：仅有 signature this 类型不够，必须有 decomp member access evidence（this->member 在目标类中存在且不在原类中存在）

## data/annotations/ 文件格式

```
functions.json     {addr: {name, signature}}
globals.json       {addr: {name, type, overlaps_with, decomp_name}}
skip_functions.json {addr: {name, reason, target_name}}
structs/*.json     {name, binary_size, known_members: {offset: {name, type}}}
template_bases.json  {sanitized_name: {template: "full_expression"}}
```

## 模板基类处理（重要！）

模板基类（如 `CTaskTpl<tagEffTaskParam, ...>`）在 PAL3 反编译管线中有特殊的处理流程，**不要误解或误删**。

### 数据流

```
structs/CEffSParticle.json          template_bases.json
  base_class: [                       CTaskTpl_tagEffTaskParam_CEffSParticle:
    "CEffObj",                          {"template": "CTaskTpl<tagEffTaskParam, unsigned long (...)>"}
    "CTaskTpl_tagEffTaskParam_CEffSParticle"  ← 注意：这是 sanitized 名
  ]                                   ← 映射到完整模板表达式
          │                                      │
          ▼                                      ▼
    apply_annotations.py (IDB)       codegen emit_headers.py (源码生成)
    - 写入 IDB struct 定义            - 读 template_bases.json
    - 设继承为 sanizited 名           - 反查完整模板表达式
                                      - 生成: class CEffSParticle :
                                               public CTaskTpl<tagEffTaskParam, ...>
```

### 关键约束

| 规则 | 说明 |
|------|------|
| **struct/*.json 中的 base_class 必须使用 sanitized 名** | 替换 `<>` `::` `*` 为 `_`，如 `CTaskTpl_tagEffTaskParam_CEffSParticle` |
| **永远不要删除模板基类** | 删除会破坏 codegen 生成的继承链，导致 class 缺少基类 |
| **template_bases.json 是唯一权威映射** | 新增模板特化时，必须同时在此注册 sanitized 名 → 完整表达式 |
| **apply_annotations.py 会忽略含 `<>` 的 base_class** | 以前老格式用完整表达式会被丢弃，新格式必须用 sanitized 名 |
| **check_annotations.py 只检查名称存在性** | 它查的是 `all_struct_names`（structs/*.json 的文件名列表），sanitized 名对应的文件存在即为有效（如 `CTaskTpl_tagEffTaskParam_CEffSParticle.json`） |

### 错误修复示例

```python
# ❌ 错误：删除了模板基类（破坏了继承链）
"base_class": ["CEffObj"]  # CTaskTpl<...> 被删了！

# ✅ 正确：用 sanitized 名替换完整表达式
"base_class": ["CEffObj", "CTaskTpl_tagEffTaskParam_CEffSParticle"]
```

### 判断方法

如果看到 struct 的 `base_class` 中有类似 `CTaskTpl<...>` 或 `gbSingleton<...>` 格式的条目：
1. 在 `template_bases.json` 中找到对应的 sanitized 名
2. 用 sanitized 名替换完整表达式
3. 如无对应条目，需手动注册

**顶层原则**：codegen 层依赖 `template_bases.json` 做反向映射以生成正确的模板继承代码。annotation 层只需要用 sanitized 名指向这个注册表即可。

## Phantom Global 处理

### 什么是 Phantom Global

某些 annotation `globals.json` 中的全局变量的实际地址落在另一个更大结构体的内存
范围内。它们在 IDB 中可能有独立命名，但实际上是父结构体的内部字段。

例如 `g_ScriptRoleBuf`（地址 0xC04920）落在 `g_SceneMgr`（0xC04390, size=6904）范围内。
它没有独立存储，不能有 `extern` 声明。

### 识别方法

- 编译报 C2065 + 级联 C2228（变量名.member）
- annotation `globals.json` 中有 `overlaps_with` 字段标记
- 地址计算：变量地址是否在某个已知 struct_instance 范围内（差值即为父结构体内的偏移）

### 处理流程

1. **验证**：计算变量地址和父结构体基址的差值，确认偏移落在父结构体 size 内
2. **父 struct 补成员**：在 `structs/ParentStruct.json` 的 `known_members` 中
   添加对应偏移的字段定义（类型、名称）
3. **标记 skip**：在 `globals.json` 中设 `"type": "skip"`，`"reason"` 注明所属父结构体
4. **重新导出**：`export → codegen → compile`

### 禁止行为

- ❌ 加 `extern` 声明——地址冲突
- ❌ 通过 thunk_map 重命名——无法通过地址验证
- ❌ 保留独立全局声明——编译器允许但运行时地址错误

### 典型场景：g_ScriptRoleBuf

```
g_SceneMgr    0xC04390  size=6904
g_ScriptRoleBuf 0xC04920 → g_SceneMgr + 0x590

annotation 中:
1. 在 SceneMgr.json 的 known_members 补偏移 0x590 的 RoleSystem 字段
2. 在 globals.json 中将 g_ScriptRoleBuf 标记为 "type": "skip"
3. 重新 export 后，codegen 自动解析为 g_SceneMgr.fieldName.subField
```

## 字段验证

1. 定位二进制证据（query_todo_fields / verify_offset.py）
2. 确认 reg 来源（函数头部 ecx 赋值：`mov esi, ecx` / `lea esi, [ecx+X]`）
3. 确认访问宽度（指令前缀：8B=4B, C6=1B, 66 8B=2B, D9=float, DD=double）
4. 记录证据到 `CHANGE_LOG.md`
5. 修改 annotation → `check_annotations.py` 验证 → 提交
