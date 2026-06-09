# PAL3 Decompilation Project

**匹配反编译**：目标为 MSVC 6.0 SP0 编译的 PAL3.exe 生成字节匹配的 C/C++ 源码。

## Project Overview

- **Compiler**: MSVC 6.0 SP0 (`tools/compilers/msvc6.0/`), `/O2 /Ob2 /Oi /Ot /Oy`
- **Toolchain**: `cmake/toolchain-vc6.cmake` — Ninja + wine_cl.sh
- **Graphics**: DirectX 9, D3DX Summer 2003
- **Audio**: Miles Sound System, **Video**: Bink
- **Script**: SCE bytecode VM (~140 opcodes)

## Pipeline Architecture

所有操作通过 `python pipeline/cli.py` 统一入口执行。

```
annotations/          data/annotations/ — 唯一手工维护的数据源
    │
    ▼  apply          python pipeline/cli.py init / apply
    │                (内部调用 apply_annotations.py, 写入 IDB)
IDB                   original/PAL3.exe.i64 — 生成物，可随时重建
    │
    ▼  export         python pipeline/cli.py export
    │                (内部调用 export_full.py, 从 IDB 导出)
decomp JSONs          asm/pal3/decomp/*.json
ida_structs.json      asm/pal3/ida_structs.json (结构体 + 全局变量)
thunks.json           asm/pal3/extra/thunks.json
    │
    ▼  codegen        python pipeline/cli.py codegen all
    │                (codegen 只读 decomp JSONs/ida_structs.json)
src/ + include/       生成的 .h + .cpp
    │
    ▼  compile        python pipeline/cli.py compile
                     (cmake + ninja -k 9999)
```

**关键分层规则：**
- `annotations/` → `apply_annotations.py` → IDB 是唯一写入路径
- IDB → `export_full.py` → JSON 文件是下阶段的唯一输入
- codegen 只读 JSON 文件，**绝不直接读 `data/annotations/`**
- 所有代码修正路径：annotate → SetType → IDB → re-export → codegen
- 编译错误是 codegen 适配度指标，不是标注正确性指标

## Phantom Global Rule

全局变量地址落在某个 `struct_instance` 范围内时（如 `Buffer` 在 `g_SceneMgr` 内）：
- **绝不能有 `extern` 声明**（地址与父结构体重叠）
- 访问通过 `struct_instances` → `_resolve_offset` 解析为 `g_Parent.field`
- 不经过 `thunk_map` 改名（thunk_map 只用于函数调用替换）
- `globals_map` / `global_addrs` 提供地址查询支持

## 项目强约束

以下规则**必须严格遵守**，任何违反都将导致代码质量下降或字节不匹配：

### 管线规则
- **严格按照管线流程工作**：annotation → apply → export → codegen → compile。不得跳过步骤，不得在生成物上直接修改。
- **codegen 不读 annotation**：codegen 只能读 export 产出的 JSON 文件（`asm/pal3/decomp/*.json`、`asm/pal3/ida_structs.json`、`asm/pal3/extra/thunks.json`），绝不允许导入 `data/annotations/` 中的数据。
- **编译错误不是 annotation 回退理由**：更精确的类型标注可能暴露 codegen 适配问题，导致更多编译错误——这是正常的，不构成回退标注的理由。
- **export 不读 annotation**：`export_full.py` 只能从 IDB 读取数据，不能直接读 `data/annotations/` JSON 文件。

### annotation 规则
- **每一处 annotation 修改必须有二进制直接证据**。证据等级见 pal3-pipeline skill 的置信度规则表。A 级证据（指令中的 reg+disp32、绝对地址）是偏移修改的最低门槛。
- **禁止猜测性修改**。没有二进制证据不能修改偏移、类型、函数签名。PDB 数据只能作参考（来自 PAL3A，偏移可能与 PAL3 不同），不能单独作为证据。
- **禁止批量修改未验证字段**。每个偏移/类型变更必须逐一验证，不能批量推断。
- **禁止伪语义命名**：`m_nState_4968`、`m_fParam_0A0` 这类用地址后缀伪装的名字没有语义价值，和 `_todo_` 没有区别。不确定含义时保留 `_todo_`。
- **禁止仅凭 Hex-Rays 反编译文本推断偏移**——除非 IDB 已 apply_annotations 且结构体正确。
- **禁止仅凭 signature this 修正函数归属**——必须有 decomp member access evidence（函数内 this->member 引用的成员在目标类中存在且不在原类中存在）。

### workaround 规则
- **禁止破坏性 workaround**：不为了编译通过而丢失类型信息或结构体定义。`void*`、`int`、`char[]` 等泛化类型只在确实不知道真实类型时使用。
- **后处理只做等价变换**：codegen pipeline 只做不改变语义的代码转换，不编造信息。
- **IDA 层能解决的问题在 IDA 层解决**：类型标注、结构体导入、函数签名等应该在 IDA 中通过 annotation 完成，不在 codegen 层打补丁。

## Directory Structure

```
data/annotations/     标注数据（核心资产：structs, functions, globals）
pipeline/
  cli.py              统一入口（init/apply/export/codegen/compile/iterate）
  config.py           管线配置
  check_annotations.py 标注校验
  decomp_quality.py   反编译质量指标
  verify_offset.py    偏移验证
  iterate.py + rules + apply  自动迭代引擎
  gen/                codegen（10 个 stage 文件）
  ida/                IDA Pro 脚本
    master_pipeline.py    IDB 初始化（PDB + FLIRT）
    apply_annotations.py  应用标注到 IDB
    export_full.py        完整导出（decomp JSON + structs + thunks）
    query_*.py (16)       查询工具（只读）
include/pal3/gen/     自动生成的 .h
src/pal3/gen/         自动生成的 .cpp
asm/pal3/
  decomp/*.json       IDA 反编译导出（gitignored）
  ida_structs.json    结构体/全局变量导出
  extra/thunks.json   thunk 函数导出
original/             原始二进制 + IDB 数据库
docs/superpowers/
  specs/              设计文档
  plans/              实施计划
tools/                独立工具（DIA 导出等）
```

## Codegen Data Sources

| codegen 数据 | 来源 | 说明 |
|-------------|------|------|
| `globals_map` | `ida_structs.json._globals` | dword_XXX → 命名全局 |
| `global_addrs` | `ida_structs.json._globals` | 命名全局 → 地址 |
| `struct_instances` | `_globals` + struct sizes | 地址范围，伪全局解析 |
| `struct_members` | `ida_structs.json.data_members` | 偏移 → 字段名 |
| `thunks` | `asm/pal3/extra/thunks.json` | j_ 函数 → 目标函数 |
| `static_methods` | decomp JSONs | __cdecl 类方法 |
| `free_func_sigs` | decomp JSONs | 自由函数签名 |

## Community References

- **PAL3patch** (`extra/PAL3patch/`): 结构体定义、逆向笔记
- **OpenPAL3** (dontpanic92): Rust 重实现，文件格式解析器

## Skill Routing

管线、annotation、IDA 查询、编译错误分析 → 加载 `pal3-pipeline` skill
