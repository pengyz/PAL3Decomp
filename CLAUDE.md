# PAL3 Decompilation Project - Claude Code Context

## Core Principle

**质量优先，核心逻辑字节匹配。** 目标是高质量还原游戏核心逻辑，使其行为与原始二进制一致。

- **聚焦核心逻辑**：战斗系统、脚本引擎、场景管理、角色系统等核心游戏逻辑追求字节匹配。边角小函数、系统库 stub、CRT 初始化等不值得花大量时间
- **ROI 驱动**：字节匹配存在宽容度——核心逻辑一致是目标，对于行为等价但字节不完全一致的边缘代码可以接受
- **IDA 优先**：代码质量问题（硬编码偏移、void* 参数、类型强转）的正确修复路径是在 IDA 中完善类型/签名，然后重新导出
- **后处理仅做等价变换**：codegen pipeline 只做不改变语义的代码转换（基于 tree-sitter AST），不编造信息
- **不降级已有信息**：不把已知类型改为 void*、char[]、int 等泛化类型
- **不允许破坏性 workaround**：不为了编译通过而丢失类型信息或结构定义

## Project Overview

This is a **matching decompilation** project for 仙剑奇侠传3 (PAL3.exe).
The goal is to produce C/C++ source code that, when compiled with the original
compiler (MSVC 6.0 SP0), generates byte-identical machine code to the original binary.

## Technical Details

- **Compiler**: MSVC 6.0 SP0 (cl.exe 12.00.8168) — `tools/compilers/msvc6.0/`
- **Optimization**: /O2 /Ob2 /Oi /Ot /Oy
- **Graphics**: DirectX 9, D3DX Summer 2003
- **Audio**: Miles Sound System (AIL)
- **Video**: Bink Video (.bik)
- **Input**: DirectInput 8
- **Script**: SCE bytecode VM (~140 opcodes)
- **Toolchain**: cmake/toolchain-vc6.cmake

## PAL3.exe Decompilation Workflow (Active)

使用 IDA Pro 9.2 + Hex-Rays 反编译 PAL3.exe，通过 IDAPython 管线导出，后处理生成源码。

### 工作流

```
1. IDA 标注   → pipeline/ida/*.py (函数命名、结构体导入、全局变量类型)
2. IDA 导出   → pipeline/ida/export_full.py → asm/pal3/decomp/*.json
3. 代码生成   → python pipeline/gen/codegen.py all → include/ + src/
4. 编译验证   → VC6 (cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake)
5. 字节对比   → python tools/pal3_compare.py
6. 迭代       → 回到步骤 1，在 IDA 中修复类型/签名问题
```

### 核心原则

1. **IDA 层能解决的问题在 IDA 层解决** — 类型标注、结构体导入、函数签名
2. **累积收益** — 每次 IDA 侧的改进（结构体/签名）惠及所有引用该类型的函数
3. **codegen 全量生成** — 每次从 decomp JSON 全量重新生成，无增量缓存

### IDA 中需要做的事情

| 问题表现 | Root Cause | IDA 修复方向 |
|----------|-----------|-------------|
| `*((_DWORD*)this + 23)` | 类结构体成员缺失 | 导入/完善结构体定义 |
| `void *` 参数 | 函数签名未设置 | SetType 设置正确参数类型 |
| `sub_XXXXXX` 调用 | 函数未命名 | set_name 标注函数名 |
| `dword_XXXXXX` | 全局变量未标注 | 命名 + 设置类型 |
| `stdiobuf *` | IDA 类型误判 | 修正为正确类型 (UIWnd*) |
| `this->m_pUtil[88]` | CUtil 是 forward decl | 需要完整的 CUtil 布局定义 |

### 数据文件

- `asm/pal3a/pdb_export.json` — PAL3A PDB 完整导出 (1503 classes, 含继承+成员+方法)
- `asm/pal3/decomp/*.json` — PAL3.exe 5414 函数的 Hex-Rays 反编译结果
- `original/PAL3.exe.i64` — IDA 数据库 (含结构体/函数名/全局变量标注)

### 代码生成工具

- `pipeline/gen/codegen.py all` — 全量生成 headers + cpp (tree-sitter AST pipeline)
- `pipeline/gen/codegen.py headers` — 只生成 .h
- `pipeline/gen/codegen.py cpp` — 只生成 .cpp
- `pipeline/gen/codegen.py cpp ClassName` — 只生成指定类
- `tools/dia_export_structs.py` — 从 PDB 导出结构体 (DIA SDK)
- `tools/dia_export_bases.py` — 从 PDB 导出继承关系

### 当前进度 (2026-05-10)

```
PAL3.exe:
  IDA 标注: 1964 函数已命名 / 5413 总函数 (36%)
  结构体: 869 个精确导入 IDA
  生成: 113 .cpp 文件, 184 头文件
  VC6 编译: 3/113 通过（管线基础设施已建立）
  主要阻塞: IDA 中结构体成员/函数签名不完整
```

## Directory Structure

- `data/annotations/` — 标注数据（项目核心资产：structs, functions, globals, vtables）
- `data/pdb/` — PAL3A PDB 导出（只读参考）
- `pipeline/gen/` — 代码生成管线（4-stage tree-sitter AST pipeline）
- `pipeline/ida/` — IDA Pro 脚本（master_pipeline, apply_annotations, export, query）
- `pipeline/` — 管线工具（check_annotations, verify_offset, compare）
- `tools/` — 独立命令行工具（字节对比, 进度统计, DIA 导出）
- `src/pal3/` — 生成的 PAL3.exe 源码（按模块: Combat/, Effect/, UI/）
- `include/pal3/gen/` — 自动生成的类头文件
- `include/gbengine/` — gbengine.dll 头文件
- `asm/pal3/decomp/` — IDA 导出的反编译 JSON（gitignored 运行产物）
- `original/` — 原始二进制 + IDA 数据库
- `cmake/` — VC6 工具链配置

## gstack

Use the `/browse` skill from gstack for all web browsing. Never use `mcp__claude-in-chrome__*` tools.

Available skills: `/office-hours`, `/plan-ceo-review`, `/plan-eng-review`, `/plan-design-review`, `/design-consultation`, `/design-shotgun`, `/design-html`, `/review`, `/ship`, `/land-and-deploy`, `/canary`, `/benchmark`, `/browse`, `/connect-chrome`, `/qa`, `/qa-only`, `/design-review`, `/setup-browser-cookies`, `/setup-deploy`, `/setup-gbrain`, `/retro`, `/investigate`, `/document-release`, `/document-generate`, `/codex`, `/cso`, `/autoplan`, `/plan-devex-review`, `/devex-review`, `/careful`, `/freeze`, `/guard`, `/unfreeze`, `/gstack-upgrade`, `/learn`.

## Skill routing

When the user's request matches an available skill, invoke it via the Skill tool. When in doubt, invoke the skill.

Key routing rules:
- Product ideas/brainstorming → invoke /office-hours
- Strategy/scope → invoke /plan-ceo-review
- Architecture → invoke /plan-eng-review
- Design system/plan review → invoke /design-consultation or /plan-design-review
- Full review pipeline → invoke /autoplan
- Bugs/errors → invoke /investigate
- QA/testing site behavior → invoke /qa or /qa-only
- Code review/diff check → invoke /review
- Visual polish → invoke /design-review
- Ship/deploy/PR → invoke /ship or /land-and-deploy
- Save progress → invoke /context-save
- Resume context → invoke /context-restore

## Community Projects (Reference)

- **PAL3patch** (zhangboyang): `extra/PAL3patch/` — 结构体定义、逆向笔记
- **OpenPAL3** (dontpanic92): Rust 重实现，文件格式解析器
