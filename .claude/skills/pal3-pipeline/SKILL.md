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
python pipeline/cli.py tool check_annotation_names  # 对比 annotation vs decomp 类归属
```

输出在 `pipeline/ida/_logs/*.json`。IDA 脚本的 print() 不显示在终端。

## IDA Headless 查询技术

在不打开 IDA GUI 的情况下查询二进制证据的关键方法：

```python
# 运行 IDA 脚本查 raw IDB（纯 auto-analysis，无 PDB 类型干扰）
ida_path = '/home/peng/ida-pro-9.1/idat'
raw_idb = 'original/PAL3.exe.raw.i64'
subprocess.run(f'"{ida_path}" -A -S"script.py" "{raw_idb}"', shell=True)
```

**三种 IDB 状态各有用途：**

| IDB | 类型信息 | 用途 |
|-----|---------|------|
| `PAL3.exe.raw.i64` | FLIRT 签名 | 原始调用约定（不受 annotation 干扰） |
| `PAL3.exe.i64` (init 后) | PDB + Annotation | 完整类型信息，query 用这个 |
| `PAL3.exe.i64` (init 前) | PDB only | 无 annotation 干扰的原始 PDB 类型 |

**IDA 9.x API 注意点：**
- `idc.get_member_name(sid, member_offset)` — 参数是 (struct_id, offset)，不是 member_id
- `idc.get_member_offset(sid, member_name)` — 参数是 (struct_id, name_str)
- `idc.get_member_by_idx(sid, idx)` — 返回 member_t 对象
- `idc.get_member_qty(sid)` — 成员数量
- `ida_hexrays.decompile(addr, hf)` — Hex-Rays 反编译单函数
- `ida_funcs.get_func_name(addr)` — 获取 PDB mangled name（全限定类名）
- `idc.get_type(addr)` — 获取函数类型签名

## 证据等级（提交阈值）

- **A 级**：二进制指令 reg+disp32（偏移修改≥85）
- **B 级**：3+ 条 A 级交叉确认（≥80）
- **C 级**：Hex-Rays 文本推断（仅标注参考，不可单独用于偏移修改）
- **D 级**：语义推断（命名≥60，不可用于偏移/类型修改）

## 反编译核心原则

### 编译错误不是问题本身

C2440/C2664/C2065 等编译错误是 annotation 标注错误的**表象**。任务是理解原始代码的意图——内存布局、复用模式、生命周期——然后让 annotation 正确表达。盯着错误码修是治标不治本，错误自然消失。

**修复层次（从优先到降级）：**
1. **annotation 层**（struct 成员类型、函数签名、全局变量类型）—— 第一选择
2. **export 层**（`export_full.py` 的类型映射/过滤）—— 当 annotation 不完整时
3. **codegen 层**（Stage 3/4 的 AST 变换）—— 仅当以上两层无法解决时

### 禁止试错式修改

不理解内存布局之前不修改 annotation。先用 IDA 查全所有访问点，画出完整使用图景，确认场景和约束，再动 annotation。

### 开发者意图优先

二进制不是真理——开发者的设计意图才是。如果二进制的某种现象（如 `int *` 存指针）与合理开发实践矛盾，更可能是 IDA/Hex-Rays 读错了，而不是开发者写了垃圾代码。

具体体现：
- **C2440 类型转换**：真实转型在 C++ 项目里应该很少。大量 C2440 往往意味着 annotation 类型错误（IDA 把指针字段标成了 `int`，把 `DWORD` 用途标成了 `char *` 等），不是开发者到处写 cast。
- **多继承指针偏移**：`((SceneObj *)this)->HideAll()` 在多继承中不是 C 转型——是编译器调整 `this` 以指向 SceneObj 子对象。第一反应不是"这是个转型"，而是**这个类少标了一个基类**。这种模式出现在反编译中就意味着缺失的继承关系。
- **成员复用与指针存储**：代码在结构体中间位置（如 `m_szLogPath[48]` 处）存取指针，说明该位置被复用。先检查是否指针字段被 IDA 分割到 char 数组中，再考虑是否标注错误。`*(gbRefObject **)&this->field[N]` 模式意味 `field` 的 `offset + N` 处应该是一个指针类型。
- **内存复用**：同一块内存不同时作不同类型用，先考虑是否被 IDA 错误分割（gap），再考虑是否是分时复用，最后才考虑 union。

### 信息流约束

```
annotation 层:   决定每个全局/成员的归属和类型 (globals.json, structs/*.json)
    ↓ init → apply_annotations
export 层:      合并 IDB 数据 + annotation 信息到 export (export_full.py → ida_structs.json)
    ↓ export
codegen 层:     读 export 数据生成代码 (不直接读 annotation)
```

- codegen **不能**有地址段判断（`.rdata` / `.data` 不是 codegen 的维度）
- codegen **不能**绕过 annotation 状态做决策（`type: skip` 的替换应在 export 层完成）
- annotation 标记 `type: skip` 的全局，如果代码引用它，应该在 export 层处理（替换为字面量或自动声明），不是 codegen 加 fallback

## PE 内存布局（地址分析基础）

```
段      起始       结束        内容
.text  0x401000   0x5695D0   代码段
.rdata 0x56A000   0x57FFFF   只读数据（字符串常量、vtable、IAT）
.data  0x580000   0x1897000  可读写数据（全局变量）
.rsrc  0x1897000  0x18ED000  资源
```

**关键应用：**
- 地址 < 0x401000 → 非真实地址，是 IDA 误识别的字面量（如 `byte_1010101` 实际上是 `0x01010101`）
- 地址在 .rdata 且名称为 `dword_*`/`asc_*` → 大概率是字符串字面量
- 地址在 .data → 真实可变全局变量

## data/annotations/ 文件格式

```
functions.json     {addr: {name, signature}}
globals.json       {addr: {name, type, overlaps_with, decomp_name}}
skip_functions.json {addr: {name, reason, target_name}}
structs/*.json     {name, binary_size, known_members: {offset: {name, type}}}
template_bases.json  {sanitized_name: {template: "full_expression"}}
```

## 关键方法提醒

- **ESI 验证法**：函数内 `[esi+disp]` 最大 disp 接近 struct size → 真实字段；远小于 → 反编译器伪像
- **嵌入子对象**：构造函数中 `lea ecx,[esi+off]; call Ctor` → 连续 LEA 的 stride = 子对象大小
- **归属判别**：函数访问大偏移(>原类 size) + 小偏移(<原类 size) → 嵌入模式，不是归属错误
- **签名修正**：仅有 signature this 类型不够，必须有 decomp member access evidence
- **raw IDB 调用约定验证**：annotation 标了 `__thiscall` 但 raw IDB 显示 `__stdcall` → 应优先相信 raw（FLIRT 可能误判，需 PDB 交叉确认）
- **PDB mangled name 确认归属**：`ida_funcs.get_func_name(addr)` 返回 mangled name → 可解析归属类

## CRT 边界判断

区分 CRT 函数和游戏逻辑函数的依据：

| 证据 | 判断 |
|------|------|
| 函数名以 `crt_sub_` 或 `_old_sbh_` 开头 | CRT，skip |
| 函数体访问游戏全局变量（如 `g_ScriptSystemData`、`g_SceneMgr`） | 游戏逻辑，需分析 |
| 函数体只有 `operator delete` / `operator new` 等 | 编译器生成，skip |
| `_sdtor_*` 函数（标量删除析构器） | 编译器生成，skip |
| `_initterm` 表条目中的构造函数 | 需判断：C++ 全局对象构造 → 游戏逻辑 |

## 模板基类处理

### 数据流

```
structs/CEffSParticle.json          template_bases.json
  base_class: [                       CTaskTpl_tagEffTaskParam_CEffSParticle:
    "CEffObj",                          {"template": "CTaskTpl<tagEffTaskParam, ...>"}
    "CTaskTpl_tagEffTaskParam_CEffSParticle"
  ]
          │                                      │
          ▼                                      ▼
    apply_annotations.py               codegen emit_headers.py
    - 写入 IDB struct 继承             - 读 template_bases.json
    - 用 sanitized 名                  - 反查完整模板表达式
                                       - 生成: class CEffSParticle :
                                                public CTaskTpl<tagEffTaskParam, ...>
```

### 关键约束

- base_class 必须使用 sanitized 名（`CTaskTpl_tagEffTaskParam_CEffSParticle`），不是完整表达式
- 永远不要删除模板基类——会破坏继承链
- template_bases.json 是唯一权威映射
- apply_annotations.py 会忽略含 `<>` 的完整表达式

## 全局变量标注

### 基本原则

- 二进制中存在的全局就应该可标注，不取决于 IDA 是否将其列为 `_globals`
- 标注质量直接影响 Hex-Rays 输出：`g_GlobalName.field` 优于 `*(DWORD*)0xADDR`
- codegen 的就地 extern 机制是合理的 fallback，不需要强制所有全局进入 globals.h

### codegen 过滤规则

`emit_headers.py` 中 `generate_globals()` 的过滤链：

1. type=skip → 跳过
2. 名称匹配 `^(dword|byte|flt|word|off|stru|unk|asc)_` → 跳过（IDA 自动名，不进入 globals.h）
3. 类型含 `::` → 跳过（PDB 旧类型名）
4. 函数指针类型 → 跳过（WinAPI 重声明）
5. 其余进入 globals.h

被过滤的全局变量（如 `dword_17A89C8`）由 codegen 在 .cpp 中就地生成 `extern` 声明。

### Phantom Global

地址落在 struct_instance 范围内的全局变量：
- 不能有独立 `extern` 声明（地址与父结构体重叠）
- 访问通过 struct_instances → _resolve_offset 解析为 g_Parent.field
- 在 globals.json 中标记 type=skip

## 字面量还原

IDA 有时会把数值常量错误识别为全局变量（特别是 `byte_`/`dword_` 名称的）：

```python
# stage4_substitution.py 中的判断逻辑：
if name.startswith('byte_'):
    va = int(name.split('_')[1], 16)
    if va < 0x401000:  # 低于 .text 段起始
        # 不是真实地址，是字面量
        replacement = '0x%08X' % va
```

调用链：`_try_literal_replacement(name)` → stage4 AST 替换 + emit_cpp 跳过 extern

## 字段验证

1. 定位二进制证据（query_todo_fields / verify_offset.py）
2. 确认 reg 来源（函数头部 ecx 赋值：`mov esi, ecx` / `lea esi, [ecx+X]`）
3. 确认访问宽度（指令前缀：8B=4B, C6=1B, 66 8B=2B, D9=float, DD=double）
4. 记录证据到 `CHANGE_LOG.md`
5. 修改 annotation → `check_annotations.py` 验证 → 提交

## 领域知识：CCBStageRole 任务槽位分配

### tagCmdData 内存复用

`tagCmdData.bDestRole[11]` 的最后 4 字节（bDestRole[7..10]）在部分任务槽中被复用作指针：

```
偏移:   +0  +1  +2  +3  +4  +5  +6  +7  +8  +9 +10
        [  bDestRole（11 个角色索引槽位） ]
槽 57:                         128  64          ← 整数
槽 62:                           0   0          ← 清零
槽 63:             CRC("flydown")  0/ptr        ← CRC + 指针
槽 48:                                funcptr   ← 回调
槽  2:                               arrayptr  ← 音效数组
槽  3:                               funcptr   ← 回调(this[1])
```

解决：在 `tagCmdData` 中加 `pDestRoleOverlay@+0x24 : void*`，标注 `_flexible` + source 含 "overlap"。

### 任务槽位用途表

CCBStageRole.m_Task = tagRoleTask[64]，每槽 96 字节。槽位按索引固定分配用途：

| 槽位 | 所在文件 | 主要用途 | 特征访问 |
|------|---------|---------|---------|
| 2 | StageRole | cmd.pDestRoleOverlay = gbSound2DNode 数组 | stride=20 遍历，Pause/Resume |
| 3 | StageRole | cmd.pDestRoleOverlay = 回调函数(this[1]) | 双重解引用后调用 |
| 13 | StageCam | fp[1],fp[2] = HWND | SendMessage 窗口消息 |
| 19 | StageRole | eMode 状态管理 | 任务模式切换 |
| 22 | StageRole | fTemp + bValid 计时/有效性 | 频繁定时访问 |
| 48 | StageRole | cmd.pDestRoleOverlay = 函数回调 | `(*ptr)(...)` 调用 |
| 57 | StageRole | cmd.pDestRoleOverlay = 64 | 配置值（需 void* cast） |
| 62 | StageRole | dwID + fTemp + fTemp2 | 通用数据存储 |
| 63 | StageRole | fp[0..3] + pDestRoleOverlay = EditorTaskDescription | 编辑器功能 |

### 分析原则

- **编译错误不是问题本身**：C2440/C2664 是标注错误的**表象**。任务是理解原始代码意图——内存布局、复用模式、生命周期——然后让 annotation 正确表达，错误自然消失。
- **禁止试错式修改**：不理解内存布局之前不修改 annotation。先用 IDA 查全所有访问点，画出完整使用图景，确认场景和约束，再动 annotation。
- **内存复用的判断**：同一字段在不同上下文中被当作不同类型使用时，先区分是分时复用还是按索引固定分配。CCBStageRole.m_Task 的槽位是后者——每个索引有固定语义。
