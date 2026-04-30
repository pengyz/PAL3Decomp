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
| PAL3.exe | 1.8 MB | StarForce 加壳，需脱壳 | 游戏逻辑，MSVC 7.0 编译 |
| gbengine.dll | 1.2 MB | 无壳，可直接分析 | 引擎核心，74类1019导出，MSVC 6.0 SP5 |
| topo.dll | 104 KB | 无壳，可直接分析 | 数学库，6类100导出，MSVC 6.0 SP5 |

**优先级**: topo.dll (小、纯数学) → gbengine.dll (有符号) → PAL3.exe (需脱壳)

## Known Technical Details (from community RE)

- **Graphics**: DirectX 9 (IDirect3DDevice9)
- **Audio**: Miles Sound System (AIL)
- **Video**: Bink Video (.bik)
- **Input**: DirectInput 8
- **File System**: CPK archive (LZO compression, CRC32 hashing)
- **Script**: SCE bytecode VM (~140 opcodes)
- **Compiler**: MSVC 6.0 SP5 (gbengine/topo), MSVC 7.0 (PAL3.exe code)
- **Linker**: MSVC 7.1 (VS2003)

## Workflow for Decompiling a Function

1. **Read the Ghidra export**: Look at `asm/FUNCNAME_ADDRESS.json`
2. **Rewrite as C/C++**: Transform Ghidra pseudocode into compilable code
3. **Compile**: Use MSVC with flags matching the original build
4. **Compare**: Check compiled output against original bytes
5. **Iterate**: Adjust code based on diff until match is achieved

## Key Rules

- **Compiler**: MSVC 7.1 (Visual Studio .NET 2003) - verify from Rich Header
- **Optimization**: /O2 (to be confirmed)
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

All commands use `python run.py <command>`, works on both Windows and Linux:

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

## Important Context Files

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
  - `/tmp/PAL3patch/src/PAL3patch/include/PAL3patch/pal3.h` - 1872 lines of RE data
- **OpenPAL3** (dontpanic92): Rust reimplementation with full file format parsers
  - `/tmp/OpenPAL3/yaobow/shared/src/scripting/sce/` - SCE VM implementation
