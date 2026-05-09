# PAL3 Decompilation Project - Claude Code Context

## Project Overview

This is a **matching decompilation** project for 仙剑奇侠传3 (PAL3.exe).
The goal is to produce C/C++ source code that, when compiled with the original
compiler (MSVC), generates byte-identical machine code to the original binary.

## Directory Structure

- `original/` - Original PAL3.exe (not in git)
- `src/` - Decompiled source code, organized by build target:
  - `topo/` - topo.dll (数学库: gbVec3D, gbMatrix4, gbRotMatrix, gbQuaternion, gbMatrixStack)
  - `gbengine/` - gbengine.dll (引擎核心: 渲染、输入、音频、资源管理)
  - `pal3/` - PAL3.exe (游戏逻辑: 战斗、剧情、UI、脚本)
- `include/` - Header files and struct definitions
  - `pal3.h` - Master header (include this everywhere)
  - `pal3_config.h` - Compiler/platform macros
  - `pal3_types.h` - Fundamental types
  - `pal3_structs.h` - Game structures (from reverse engineering)
  - `pal3_globals.h` - Known global variables with addresses
- `tools/` - Automation scripts (export, compare, progress)
- `asm/` - Ghidra-exported function data (JSON per function)
- `build/` - Compilation output and comparison results
- `docs/` - Research notes and structure documentation

## Decompilation Targets

| Binary | Size | Status | Notes |
|--------|------|--------|-------|
| PAL3.exe | 1.8 MB | StarForce 加壳，需脱壳 | 游戏逻辑，VC6 SP0 (12.00.8168) |
| gbengine.dll | 1.2 MB | 无壳，可直接分析 | 引擎核心，74类1019导出，VC6 SP0 |
| topo.dll | 104 KB | 无壳，可直接分析 | 数学库，6类100导出，VC6 SP0 |

**优先级**: topo.dll (小、纯数学) → gbengine.dll (**有 PAL3A.PDB 完整符号！**) → PAL3.exe (需脱壳)

## Known Technical Details (from community RE)

- **Graphics**: DirectX 9 (IDirect3DDevice9), DirectX SDK Summer 2003
- **Audio**: Miles Sound System (AIL)
- **Video**: Bink Video (.bik)
- **Input**: DirectInput 8
- **File System**: CPK archive (LZO compression, CRC32 hashing)
- **Script**: SCE bytecode VM (~140 opcodes)
- **Compiler**: MSVC 6.0 SP0/RTM (cl.exe 12.00.8168) — 所有目标统一
- **Toolchain**: tools/compilers/msvc6.0/ (from decomp.me)
- **D3DX**: Statically linked D3DX9.LIB (from DirectX SDK Summer 2003)

## PAL3A Per-File Decompilation Workflow (Active)

PAL3A.exe 有完整 PDB 符号 (11412 functions, 1057 classes, 479 source files)。
使用 IDA Pro 9.2 + Hex-Rays 反编译，通过 IDAPython 管线持续优化输出质量。

### 核心原则

1. **IDA 层能解决的问题在 IDA 层解决** — 类型标注、结构体导入、函数签名、调用约定
2. **逐文件处理** — 每次处理一个 .cpp 文件，编译验证，解决所有问题
3. **累积收益** — 每次 IDA 侧的改进（结构体导入、签名修复）惠及所有文件
4. **正确是底线** — 代码必须能编译通过，不编译的代码没有价值
5. **后处理是最终兜底** — 只有确认 IDA 无法解决的问题才用后处理脚本

### 单文件工作流

```
1. 选择文件        python tools/pal3a_file_export.py show <path>
2. 检查 IDA 输出   查看 asm/pal3a/decomp/ 中对应函数的反编译质量
3. 识别问题        _gap_0 → 缺结构体, sub_XXX → 缺函数名, dword_XXX → 缺全局变量
4. IDA 侧修复      修改 tools/ida/ 管线脚本，重跑对应 Phase
5. 重新导出        Phase 6 (ida_reexport_all.py) 生成新的反编译 JSON
6. 填充 stub       python tools/pal3a_fill_stubs.py --file src/pal3a/<path>
7. 编译验证        确保文件能通过编译
8. 迭代            回到步骤 3 直到该文件完全正确
```

### IDA Pipeline (tools/ida/)

在 IDA 中执行: `idat.exe -A -S"ida_master_pipeline.py" PAL3A.exe.i64`

| Phase | 脚本 | 作用 |
|-------|------|------|
| 1 | ida_import_all.py | 导入 PDB 结构体 (1057 classes, 拓扑排序) |
| 2 | ida_define_base_types.py | 定义缺失基类 (UIWnd, NPCInfo 等) |
| 3 | ida_patch_base_classes.py | 修补 UI 类基类字段 |
| 4 | ida_rename_top_subs.py | 重命名高频 sub_ 函数 |
| 5 | ida_apply_signatures2.py | 应用 PDB 函数签名 (__thiscall + this 类型) |
| 6 | ida_reexport_all.py | 导出全部反编译结果到 asm/pal3a/decomp/ |
| 7 | ida_export_globals.py | 导出全局变量 (名称/类型/地址) |

### 关键发现: PDB 与二进制的关系 (2026-05-06)

PAL3A.PDB 对应的是**开发版/无保护版**二进制 (.text 约 3.4MB)。
发行版使用 StarForce 保护，.text 只有 1.4MB，其余代码在 StarForce 容器中。

PE 段布局 (发行版):
- `.text`:  0x401000-0x557C57 (1.4MB) — 可分析的代码
- `.rdata`: 0x558000-0x56FC0D
- `.data`:  0x570000-0x2294000 (30MB, StarForce 容器, 含加密代码)

PDB 函数分布:
- 在 .text 内: 4530 个函数 — **可用, 地址与 IDA 一致 (93%+ 验证通过)**
- 超出 .text: 6882 个函数 — **代码不在当前二进制中, 无法反编译**

PAL3patch 脱壳 (`extra/PAL3patch/extra/unpack/pal3a/`):
- 只恢复了 21 个被 StarForce thunk 替换的函数 (放入 .exttext 段)
- 这已是社区最优方案, 无法进一步恢复

**工作范围**: 4530 个 .text 内的函数 (地址 0x401000-0x557C57)。

### 常见 IDA 输出问题及修复方向

| IDA 输出 | 含义 | 修复方法 |
|----------|------|----------|
| `_gap_0[N]` | 结构体成员未定义 | IDA: 导入/完善结构体定义 |
| `*(DWORD*)(this+N)` | this 类型不正确 | IDA: 设置正确的 __thiscall + this 类型 |
| `sub_XXXXXX()` | 函数未命名 | IDA: 从 PDB 导入函数名 |
| `dword_XXXXXX` | 全局变量未命名 | IDA: 从 globals_export.json 替换 |
| `__userpurge` | 调用约定识别错误 | IDA: 修正函数签名 |
| `JUMPOUT` | 函数边界错误 | IDA: 修正函数边界 (Phase Q2) |
| `MEMORY[0x...]` | 无法识别的内存访问 | IDA: 创建对应地址的数据段 |

### 工具命令速查

```bash
# 查看模块状态
python tools/pal3a_file_export.py status

# 列出某模块的文件
python tools/pal3a_file_export.py list --module combat

# 查看文件的函数及质量
python tools/pal3a_file_export.py show combat/CBEditor.cpp

# 填充 (自动替换 stub 为 IDA 反编译结果)
python tools/pal3a_fill_stubs.py --file src/pal3a/Archive.cpp

# 质量报告
python tools/pal3a_fill_stubs.py --quality-report
```

### 进度跟踪

- `docs/pal3a_progress.md` — 按文件记录反编译进度 (185个.cpp文件, 4523个函数)
- 每完成一个函数的编译验证或字节匹配，必须更新此文件
- 格式: File | Functions | Status | Compiles | Matches | Notes

### 数据文件

- `asm/pal3a/pdb_export.json` — PDB 完整导出 (函数签名、类定义、source_file_index)
- `asm/pal3a/decomp/*.json` — 每个函数的 Hex-Rays 反编译结果
- `asm/pal3a/globals_export.json` — 全局变量映射 (地址→名称)

---

## Legacy: topo.dll/gbengine.dll Workflow

1. **Read the Ghidra export**: Look at `asm/FUNCNAME_ADDRESS.json`
2. **Rewrite as C/C++**: Transform Ghidra pseudocode into compilable code
3. **Compile**: Use MSVC with flags matching the original build
4. **Compare**: Check compiled output against original bytes
5. **Iterate**: Adjust code based on diff until match is achieved

## Key Rules

- **Compiler**: MSVC 6.0 SP0 (cl.exe 12.00.8168) — verified from Rich Header @comp.id
- **Optimization**: /O2 /Ob2 /Oi /Ot /Oy (to be fine-tuned per function)
- **Calling convention**: __cdecl (default), __thiscall for C++ methods
- **Target**: 32-bit x86 Windows

## When Rewriting Ghidra Output

1. Preserve the exact control flow structure
2. Match variable types to what the assembly implies
3. Pay attention to:
   - `if (ptr)` vs `if (ptr != NULL)` - generates different code
   - Loop forms (for/while/do-while) - different instruction patterns
   - Local variable declaration order - affects stack layout
   - Cast expressions - may change instruction selection
4. Mark uncertain parts with `/* UNCERTAIN */`
5. Record any new struct definitions in `include/pal3_structs.h`

## Tools (Cross-platform)

### Build & Verification (Linux + Wine)
- `bash tools/setup_wine_vc6.sh` - 一次性初始化 Wine + VC6 环境
- `source tools/wine_vc6.sh` - 加载 VC6 辅助函数 (vc6_cl, vc6_compile 等)
- `python tools/gbengine_compare.py --compile <src> --all` - 编译并字节对比（自动检测平台，Linux 用 Wine）

### Build & Verification (Windows)
- `./run_verify.bat` (Windows) - Build topo.dll and verify compilation
- `python verify_build.py` - Build verification script

### Progress Tracking
- `python tools/progress_report.py` - Show detailed progress report
  - Implemented vs total functions
  - Breakdown by source file
  - List of TODOs/stubs
  
### Binary Comparison
- `python tools/compare_function.py <address> [size]` - Compare specific function
  - Example: `python tools/compare_function.py 0x10001110 12`
  - Byte-by-byte comparison with original binary
  - Match rate calculation

### Legacy Tools (python run.py)
- `python run.py check` - Check environment is ready
- `python run.py setup-ghidra` - Auto-install Ghidra + Java
- `python run.py pe-info` - Analyze the original exe (Rich Header)
- `python run.py imports` - Parse import table, detect libraries
- `python run.py progress` - Show decompilation progress
- `python run.py queue` - Show prioritized work queue
- `python run.py decompile <json> [--dry-run]` - AI decompile one function
- `python run.py batch [--count N]` - Batch AI decompile
- `python run.py compare <src> <addr> <size>` - Compile and compare
- `python run.py rename` - Suggest function names

## Current Progress (2026-05-06)

```
topo.dll:     114/414 functions (27%) - Compiles successfully
PAL3A.exe:    IDA pipeline operational, 5012/5057 functions exported (99.1%)
              Per-file decompilation workflow established
              Next: pick file, fill, compile, iterate
```

### Active Focus: PAL3A Per-File Decompilation
- IDA pipeline (7 phases) produces ~20000 decompiled functions in asm/pal3a/decomp/
- PDB source_file_index maps functions to 479 original .cpp files
- Current bottleneck: IDA 类型标注质量 (结构体成员、函数签名)
- Strategy: 逐文件处理，遇到问题在 IDA 层修复，累积改进所有文件

## Important Context Files

- `docs/decompilation_workflow.md` - **Detailed workflow guide for matching decompilation**
- `docs/pal3a_pdb_guide.md` - **PAL3A.PDB 使用指南 (gbengine.dll 完整调试符号!)**
- `docs/unpack_guide.md` - **PAL3.exe 脱壳工具使用指南 (PAL3patch)**
- `docs/community_structs.md` - All known structures, addresses, RTTI classes
- `docs/sce_opcodes.md` - Complete SCE script opcode table
- `docs/file_formats.md` - CPK, SCN, SCE binary format documentation
- `docs/unpacking.md` - StarForce 脱壳指南和流程
- `include/pal3_structs.h` - C struct definitions ready for decompilation
- `include/pal3_globals.h` - Global variables with original addresses
- `build/project_config.json` - Project metadata
- `build/progress.json` - Function-level progress tracking
- `build/gbengine_exports.json` - gbengine.dll 1019 个 C++ 导出函数
- `build/topo_exports.json` - topo.dll 100 个导出函数

## Community Projects (Reference)

- **PAL3patch** (zhangboyang): C-based game patches, has all major struct definitions
  - `extra/PAL3patch/` - Added as git submodule
  - `extra/PAL3patch/extra/unpack/` - PAL3/PAL3A 脱壳工具
  - `extra/PAL3patch/notes/pal3/` - 逆向工程笔记（非常详细）
  - `/tmp/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h` - 1872 lines of RE data
- **OpenPAL3** (dontpanic92): Rust reimplementation with full file format parsers
  - `/tmp/OpenPAL3/yaobow/shared/src/scripting/sce/` - SCE VM implementation
