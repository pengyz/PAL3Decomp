# PAL3 Decompilation Project - Claude Code Context

## Core Principle

**质量优先，字节匹配还原。** 目标不是"能编译的代码"，而是高质量的、与原始二进制字节匹配的 C++ 源码。

- **不允许 workaround**：不绕过问题，不用 hack 让代码编译通过
- **IDA 优先**：代码质量问题（硬编码偏移、void* 参数、类型强转）的正确修复路径是在 IDA 中完善类型/签名，然后重新导出
- **后处理仅做等价变换**：gen_cpp.py 只做不改变语义的代码转换（OOP 调用转换、MEMORY[] 替换、命名替换），不编造信息
- **不降级已有信息**：不把已知类型改为 void*、char[]、int 等泛化类型

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
1. IDA 标注   → tools/ida/pal3_*.py (函数命名、结构体导入、全局变量类型)
2. IDA 导出   → tools/ida/pal3_export_only.py → asm/pal3/decomp/*.json
3. 头文件生成 → python tools/gen_headers.py → include/pal3/gen/*.h
4. 代码生成   → python tools/gen_cpp.py → src/pal3/**/*.cpp
5. 编译验证   → VC6 (cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vc6.cmake)
6. 字节对比   → python tools/pal3_compare.py
7. 迭代       → 回到步骤 1，在 IDA 中修复类型/签名问题
```

### 核心原则

1. **IDA 层能解决的问题在 IDA 层解决** — 类型标注、结构体导入、函数签名
2. **累积收益** — 每次 IDA 侧的改进（结构体/签名）惠及所有引用该类型的函数
3. **gen_cpp.py 支持增量更新** — 手动修改的文件不会被覆盖（除非 `--force`）

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

- `tools/gen_headers.py` — 从 PDB + IDA 生成头文件 (类定义+方法声明)
- `tools/gen_cpp.py` — 从 IDA decomp 生成 .cpp (OOP 转换+后处理)
- `tools/gen_cpp.py --force-all` — 全量重新生成
- `tools/gen_cpp.py ClassName` — 只重新生成指定类
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

- `src/pal3/` — 生成的 PAL3.exe 源码 (按模块: Combat/, Effect/, UI/, etc.)
- `include/pal3/gen/` — 自动生成的类头文件
- `include/pal3/globals.h` — 全局变量声明
- `include/pal3/ida_defs.h` — IDA 兼容宏 (LOBYTE/HIDWORD/etc)
- `include/gbengine/` — gbengine.dll 头文件
- `asm/pal3/decomp/` — IDA 导出的反编译 JSON
- `tools/ida/` — IDAPython 脚本 (标注/导出)
- `tools/compilers/msvc6.0/` — VC6 编译器
- `original/` — 原始二进制 + IDA 数据库

## Community Projects (Reference)

- **PAL3patch** (zhangboyang): `extra/PAL3patch/` — 结构体定义、逆向笔记
- **OpenPAL3** (dontpanic92): Rust 重实现，文件格式解析器
