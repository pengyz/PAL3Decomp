# PAL3 Decompilation Project - Claude Code Context

## Project Overview

This is a **matching decompilation** project for 仙剑奇侠传3 (PAL3.exe).
The goal is to produce C/C++ source code that, when compiled with the original
compiler (MSVC), generates byte-identical machine code to the original binary.

## Directory Structure

- `original/` - Original PAL3.exe (not in git)
- `src/` - Decompiled source code, organized by module:
  - `core/` - Engine core (rendering, input, audio)
  - `game/` - Game logic (combat, story, UI)
  - `script/` - Script engine (SCE interpreter)
  - `third_party/` - Third-party library stubs
- `include/` - Header files and struct definitions
- `tools/` - Automation scripts (export, compare, progress)
- `asm/` - Ghidra-exported function data (JSON per function)
- `build/` - Compilation output and comparison results
- `docs/` - Research notes and structure documentation

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
5. Record any new struct definitions in `docs/structs.md`

## Tools (Cross-platform)

All commands use `python run.py <command>`, works on both Windows and Linux:

- `python run.py check` - Check environment is ready
- `python run.py pe-info` - Analyze the original exe (Rich Header)
- `python run.py imports` - Parse import table, detect libraries
- `python run.py progress` - Show decompilation progress
- `python run.py queue` - Show prioritized work queue
- `python run.py decompile <json> [--dry-run]` - AI decompile one function
- `python run.py batch [--count N]` - Batch AI decompile
- `python run.py compare <src> <addr> <size>` - Compile and compare
- `python run.py rename` - Suggest function names

## Important Context Files

- `docs/structs.md` - All known data structures
- `build/project_config.json` - Project metadata (compiler, total functions, etc.)
- `build/progress.json` - Function-level progress tracking
