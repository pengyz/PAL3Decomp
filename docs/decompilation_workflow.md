# Decompilation Workflow Guide

> 本文件顶部（2026-09-15 由 t5「门禁与基建」任务写入）描述 **PAL3.exe + IDA IDB**
> 的可复现工作流。文件末尾保留的旧内容是 2026-05-01 的 topo.dll/Ghidra 工作流，**已过期**。
>
> 一句话结论：**判断"IDB / 产物是不是当前状态"，只认 `original/PAL3.exe.i64` 的 mtime
> 刷新 + `pipeline/ida/_logs/apply_annotations_log.txt` 的 `[3] Structs: N/881` 行；
> 不要用 `*_status.json`。**

## 0. 单写者纪律（先读这条）

- `original/PAL3.exe.i64` 是**单写者资源**：同一时刻只允许一个执行单元触碰它。
- 写**共享产物**的命令（等价于"占窗口"）：
  `python pipeline/cli.py apply|export|codegen|probe|match`
  → 会写 `original/PAL3.exe.i64`、`asm/pal3/decomp/`、`asm/pal3/ida_structs.json`、
  `pal3/src/`、`data/status/probe_census.json`、`data/status/baselines/`、`data/status/s4_baseline.json`。
- 直接经 `idat` 跑的 IDAPython 脚本（`pipeline/ida/*.py`）同样是写者：
  IDA 可执行文件在 `/home/peng/ida-pro-9.1/idat`，**不在 PATH**；调用形式见 `pipeline/cli.py:138-150`
  （`"<ida>" -A -S"<script>" "<idb>"`，并设 `TVHEADLESS=1`）。
- 生产者**开始与结束都要通报**；读者在自己的分析期间先 `cp -r` 快照到 `/tmp`。
  （教训：一次未通报的重新生成会让全队的计数基线作废。）

## 1. 前置产物，以及缺失时的失败形态

| 产物 | 产出者 | 入库? | 缺失时 |
|---|---|---|---|
| `original/PAL3.exe.raw.i64` | `init` 步骤 1（`idat -B PAL3.exe`） | 否 | `init` 从 exe 重建（最慢的一步） |
| `original/PAL3.exe.i64`（work IDB） | `init` / `apply`（IDA 保存时写） | 否 | 各命令报 `Work IDB not found` 并退出 1 |
| `asm/pal3/decomp/*.json` | `export`（`export_full.py`） | 否 | `codegen cpp/all` 退出 1 |
| `asm/pal3/ida_structs.json` | `export`（`export_full.py:520`/`:787`） | 否 | `tools/audit_type_layout.py` **退出 2**（2026-09-15 起；此前是 WARN+exit 0 假通过） |
| `data/status/probe_census.json` | `probe s1/s2` | 是 | `compare_pal3.py` 退出 2；`compile_regression.py` 退出 1 |
| `pipeline.toml` | 人工 `cp pipeline.toml.example pipeline.toml` | 否（设计上 gitignored） | `pipeline/config.py:132-139` 打印 `PIPELINE CONFIG ERROR` 并退出 1（**无 traceback**） |
| `tools/vc6/{Include,Lib}` 小写 shim | `bash tools/setup_wine_vc6.sh` | 否（`.gitignore:87-88` 刻意排除） | `source tools/wine_vc6.sh` 打印缺哪个 shim 并返回 2；漏跑 setup 时 probe 会报 `C1083: Cannot open include file: 'windows.h'` |

> `asm/` **整树**被 `.gitignore:119` 忽略 → 一切基于 `asm/pal3/decomp`、`ida_structs.json`
> 的结论**只在本工作副本可复现**；干净检出必须先跑 `export`。

## 2. 从 raw IDB 重建的最小路径

### 2.1 全量（从 `PAL3.exe` 开始）

```bash
python pipeline/cli.py init --force
# (1) idat -B original/PAL3.exe        -> original/PAL3.exe.i64 -> 改名为 .raw.i64
# (2) cp raw.i64  -> original/PAL3.exe.i64   (work IDB)
# (3) idat -A -S pipeline/ida/master_pipeline.py  <work IDB>   (PDB 类型 + FLIRT)
# (4) idat -A -S pipeline/ida/apply_annotations.py <work IDB>  (注解入库)
# (5) idat -A -S pipeline/ida/fix_vtable_types.py  <work IDB>  (vtable 指针类型)
```

### 2.2 最小（复用已有 raw IDB，跳过最贵的一步）

```bash
python pipeline/cli.py init          # raw IDB 已存在 -> 只做 (2)(3)(4)(5)
```

等价的逐步手工形式（与 `_run_ida` 完全相同）：

```bash
IDAT=/home/peng/ida-pro-9.1/idat
TVHEADLESS=1 "$IDAT" -A -S pipeline/ida/master_pipeline.py   original/PAL3.exe.i64
TVHEADLESS=1 "$IDAT" -A -S pipeline/ida/apply_annotations.py original/PAL3.exe.i64
TVHEADLESS=1 "$IDAT" -A -S pipeline/ida/fix_vtable_types.py  original/PAL3.exe.i64
```

### 2.3 重建后的取证链

```bash
python pipeline/cli.py export;      echo "export=$?"
python pipeline/cli.py codegen all; echo "codegen=$?"
python pipeline/cli.py probe all;   echo "probe=$?"
python pipeline/cli.py match;       echo "match=$?"
```

判据（不得回退，交接文档快照值）：**L1 ≥ 5**、**ok ≥ 53/198**——分母变化即判不可比。

## 3. 「apply 真成功」的观测点

**看这两个，不要只看 `apply_status.json`：**

1. **`original/PAL3.exe.i64` 的 mtime 刷新。**
   机制依据：apply 脚本最后由 IDA 保存数据库，日志末行为 `[*] Done. Database saved.`，
   保存动作刷新 `.i64`。实测快照：`.i64` mtime `2026-09-15 15:44:39`
   **晚于** apply 日志 mtime `2026-09-15 15:40:47`。
2. **`pipeline/ida/_logs/apply_annotations_log.txt` 的 `[3] Structs: N/881` 行。**
   实测：第 98 行 `[3] Structs: 881/881 imported successfully (fail=0)`。

**为什么不能只看 `_logs/apply_status.json`：**

- 它**不是 `apply` 写的**。全仓库唯一的写入者是独立 IDAPython 脚本
  `pipeline/ida/check_apply_status.py`（`:16 OUTPUT_FILE`、`:84 json.dump`），
  需要单独跑：`idat -A -S pipeline/ida/check_apply_status.py original/PAL3.exe.i64`。
  `apply_annotations.py` 内**没有**任何对它的写入（`grep -n apply_status pipeline/ida/apply_annotations.py` 无命中）。
- 因此它**可能是上一轮的陈旧值**。实测陈旧证据（本工作副本）：
  `apply_status.json` mtime **15:14:42**，而 apply 日志 15:40:47、`.i64` 15:44:39 → **落后约 26 分钟**。
- 它描述的是"注解 ↔ IDA 成员数/尺寸"，不能证明"没人开过库"，也不能证明尺寸正确
  （`binary_size vs IDA size` 是同源比较，见 §5）。

**边车文件不是指纹：** `.til/.nam/.id0/.id1/.id2` **只在 IDA 非正常退出时残留**
（"边车存在 = 上次崩过"），干净退出会删除它们。所以：

- 边车**存在** → 上次 IDA 崩过（值得警惕）；
- 边车**不存在** → **不能**推断"没人开过库"（干净退出也会删）。实测本工作副本当前 0 个边车，
  与 15:44:39 的干净保存一致。

**失败长什么样（2026-09-15 起）：** `python pipeline/cli.py apply` 在
`apply_annotations.py` 非零退出时**不再返回 0**，而是打印 ERROR 并退出 1，
以保护 `apply && export && codegen all && probe all && match` 门禁链；
`fix_vtable_types.py` 失败会打印显式 WARN（vtable 类型可能陈旧）。
`python pipeline/cli.py init` 任一步失败会打印 `INIT INCOMPLETE` 并退出 1（不再谎报 "INIT COMPLETE"）。

## 4. 门禁退出码语义速查（2026-09-15 收紧后）

| 命令 | 0 | 非 0 |
|---|---|---|
| `tools/audit_type_layout.py` | 无 ERROR 级问题（可含 WARNING） | 1 = 有 ERROR；**2 = 缺 `asm/pal3/ida_structs.json` 等前置产物（拒绝假通过）** |
| `pipeline/decomp_quality.py --threshold` | 无回归告警 | 1 = 有回归告警 |
| `tools/annotation_diff.py` | git 可读（报告 `verdict: clean|changed`） | **3 = git/commit 不可读（≠「无变更」）**；2 = 其它错误 |
| `pipeline/compare_pal3.py` | 正常 | **2 = `probe_census.json` 缺失/畸形/条目缺字段** |
| `tools/compile_regression.py` | 相对棘轮基线无回归 | 1 = 有回归（或基线陈旧） |
| `source tools/wine_vc6.sh` | shim 存在 | **2 = 小写 shim 缺失（提示 `bash tools/setup_wine_vc6.sh`）** |

纪律：**退出码一律 `cmd; echo "exit=$?"` 或 `cmd; echo "exit=${PIPESTATUS[0]}"`**。
`cmd | tail` 会让 `$?` 变成 `tail` 的退出码（本会话已因此误判过两次）。

## 5. 已知「看起来通过、其实没查」的地方（诚实清单）

- `audit_type_layout.py` 的 `binary_size vs IDA size`：annotation → apply → IDB → export 是
  **同一条数据通路**，相等是构造必然。实测 818/818 相等、0 不等 → **该检查无判别力**，
  只把"不等"当作 stale-IDB 信号；尺寸正确性必须用 IDB 无关来源
  （指令级 `reg+disp32` 访问上界、分配点尺寸）判断。见
  `docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md` 裁决 (b)。
- `decomp_quality.py` 的 misattrib 判据被**膨胀的 `cls_size` 稀释**：
  `gbVFileSystem`（917972）与 `SoundMgr`（918796）在任何倍率下阈值都不可达
  （且 `gbVFileSystem` 在 decomp 里 **0 个函数**、`SoundMgr` 的 2 个函数没有任何
  `this+N` 裸偏移）。收紧倍率（`*2 → *1`）能恢复 7→16 的检出，但**不能**覆盖这两个类。
- `audit_type_layout.py` 新增的"声明尺寸几何"信号（`binary_size > 3×` 声明成员末端）是
  **待复核标记而非证据**，且有一个已知盲区：当尺寸被"按值嵌套成员"一致地撑大时
  （例：`gbVFileSystem = 24 + sizeof(CPK 917948)`）比值为 1.0，看不到问题。
- `pipeline/gen/` 读 `data/annotations/` 的红线违规（裁决 (a)）仍未收口。

---

# 附录：历史内容（topo/gbengine 早期工作流，2026-05-01，**已过期**）

> 以下内容描述的是 **topo.dll + Ghidra** 的旧工作流（`src/topo/`、`asm/topo/*.json`、
> `run_verify.bat`），与当前 PAL3.exe + IDB 管线（`pal3/src/`、`asm/pal3/`）**无关**，
> 保留仅作历史参考。请以上文为准。

## Overview

This document describes the workflow for matching decompilation of PAL3 topo.dll.
The goal is to produce C/C++ code that compiles to byte-identical machine code.

## Current Status (as of 2026-05-01)

```
Implemented: 114/414 functions (27%)
Build status: ✅ Compiles successfully
Binary size: 96,768 bytes
```

## Workflow Steps

### 1. Choose a Function to Decompile

```bash
# View progress report
python tools/progress_report.py

# List available JSON exports
ls asm/topo/*.json | head -20

# Pick a function based on:
# - Complexity (start with smaller functions)
# - Dependencies (implement called functions first)
# - Priority (exported/public API functions first)
```

### 2. Analyze the Ghidra Export

```bash
# Read the function's JSON data
cat asm/topo/FunctionName_address.json | jq .
```

The JSON contains:
- `address`: Function start address (RVA)
- `size_bytes`: Function size
- `signature`: Function signature with types
- `decompiled_c`: Ghidra's C pseudocode
- `assembly`: Raw x86 assembly listing
- `callees`: Functions this function calls
- `callers`: Functions that call this function

### 3. Implement in C/C++

#### Create or update the appropriate source file:

```cpp
// src/topo/gbMatrix4.cpp

// ============================================================================
// 0x10001110  gbMatrix4()  (12 bytes)
// public: __thiscall gbMatrix4::gbMatrix4(void)
// ============================================================================
gbMatrix4::gbMatrix4(void)
{
    LoadIdentity();
}
```

#### Key principles:

1. **Preserve exact structure**: Use Ghidra's control flow structure
2. **Match types**: Ensure types match assembly (int vs uint, pointer sizes)
3. **Calling convention**: __cdecl, __thiscall, __fastcall must match
4. **Local variable order**: Affects stack layout
5. **Expression form**: `if (ptr)` vs `if (ptr != NULL)` generates different code

### 4. Compile and Test

```bash
# Build the DLL
./run_verify.bat

# Check for errors
echo $?  # Should be 0 on success
```

### 5. Compare Binary Output

```bash
# Compare specific function
python tools/compare_function.py 0x10001110 12

# Expected output:
# Match rate: 12/12 bytes (100.0%)
# ✓ PERFECT MATCH!
```

### 6. Iterate Until Match

If not matching:

#### Common causes:
- **Wrong optimization level**: /O1 vs /O2 affects code generation
- **Compiler version mismatch**: MSVC 6.0 vs MSVC 2022 differences
- **Calling convention**: Missing __thiscall, __fastcall annotations
- **Register allocation**: Try reordering local variables
- **Constant folding**: Compiler may optimize constants differently
- **Padding/alignment**: struct packing affects layout

#### Debugging steps:
1. Generate assembly listing: `/FA` flag in CMakeLists.txt
2. Compare assembly: `diff original.asm compiled.asm`
3. Look for instruction pattern differences
4. Adjust C code to guide compiler

### 7. Document and Commit

```bash
# Stage changes
git add src/topo/filename.cpp

# Commit with function info
git commit -m "Implement FunctionName (0x10001110, 12 bytes)

- Matches original binary exactly
- Verified with compare_function.py
- Dependencies: LoadIdentity()
"
```

## Tips for Matching

### Compiler Quirks

#### MSVC 6.0 specifics:
```cpp
// Use old-style for loops for better matching
for (int i = 0; i != count; i++)  // Better than i < count
    
// Prefer pointer arithmetic over array indexing
*pDst++ = *pSrc++;  // Better than dst[i] = src[i]

// Use explicit casts
(float)sqrt(x)  // Not just sqrt(x)
```

### Common Patterns

#### Memory copy loops:
```cpp
// Pattern 1: Manual loop (12 dwords)
for (int i = 12; i != 0; i--) {
    *pDst++ = *pSrc++;
}

// Pattern 2: REP MOVSD equivalent
memcpy(dst, src, 48);  // May not match! Use manual loop
```

#### Conditional assignment:
```cpp
// Pattern 1: Ternary (may generate different code)
result = (x > 0) ? a : b;

// Pattern 2: If-else (more predictable)
if (x > 0) {
    result = a;
} else {
    result = b;
}
```

## Testing Checklist

Before marking a function as complete:

- [ ] Compiles without errors or warnings
- [ ] Function signature matches JSON export
- [ ] Byte-perfect match with original binary
- [ ] All dependencies are implemented
- [ ] Comments include address and size
- [ ] Calling convention is correct
- [ ] Local variable types are accurate

## Priority Queue

### High Priority (Exported/Public API):
1. CreateTopoGeom (0x100034B0)
2. DestroyTopoGeom (0x10003570)
3. TopoGeom_Init (0x10007620)

### Medium Priority (Internal but commonly used):
1. TopoFaceVector_Insert (0x10008940) - 714 bytes, complex
2. gbMatrix4 operations (various)
3. gbVec3D operations (various)

### Low Priority (Utilities):
1. Helper functions
2. Internal constructors
3. Rarely called functions

## References

- **Ghidra exports**: `asm/topo/*.json`
- **Original structs**: `docs/community_structs.md`
- **Compiler docs**: VS2003/MSVC 6.0 documentation
- **PAL3patch**: `/tmp/PAL3patch/src/PAL3patch/include/`

## Getting Help

Common issues:

1. **Can't match a function**: Try different optimization flags, reorder code
2. **Linker errors**: Check for missing extern declarations
3. **Crashes at runtime**: Verify struct layouts match original
4. **Wrong calling convention**: Check __thiscall vs __cdecl vs __fastcall

Document your findings in `docs/decompilation_notes.md` for future reference.
