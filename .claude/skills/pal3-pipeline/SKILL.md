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
