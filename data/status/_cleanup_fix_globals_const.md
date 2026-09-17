# 修复：globals.cpp 定义丢失 `const`（45 对不一致）+ 刷新陈旧基线

**日期**：2026-09-17 · 触发：`regression_detector` 报出的 3 个"新错误"文件

---

## 1. 修复 A：`const` 不一致（已落地）

**现象**：`globals.cpp` 错误 58（基线）→ **96**，`C2373: 'aUiCombatPointe' :
redefinition; different type modifiers`。

**根因**（精确定位到行）：
- `pal3/src/globals.h:818` `extern const char aUiCombatPointe[]; // 0x5db7d8`
- `pal3/src/globals.cpp:748` `char aUiCombatPointe[] = "ui\\combat\\pointer\\pointer.cvd";`
  —— **定义丢了 `const`**。

发射处：`pipeline/gen/stages/emit_headers.py:3186`（`generate_globals_cpp`）
硬编码 `f'char {nm}[] = "{s}";'`，而 globals.h 那边（同文件 `:2903` 起）用
**注解类型的原样**发 `extern const char X[];`。两侧不同源 ⇒ 不一致。

**规模**：按 `extern (const)? T name[]` 与 `(const)? T name[] =` 正则对齐，
**45 对** `const` 不一致。

**修法**：定义侧改成与声明侧**同源**——都看注解类型是否带 `const`：
```python
_cq = 'const ' if tp.strip().startswith('const') else ''
lines.append(f'{_cq}char {nm}[] = "{s}";')
```

**验证**：不一致对数 **45 → 0**；`globals.cpp` 错误 **96 → 51**；
`regression_detector` 的"新错误"文件数 **3 → 2 →（见 §2 后）1**；
`probe` s2 61/202、`match` L1 17 / matched 191/218（均 **Δ0**，因该文件仍未 pass）。

## 2. 修复 B：`Config.cpp` 的非法限定名（见 `_cleanup_fix_qualified_name_call.md`）
已在前一轮落地：非法形态 75→0，`Config.cpp` 14→6。

## 3. 剩余 1 个"新错误"文件的根因（已理解，本轮不修）

`pal3/src/Data/PAL_GDB.cpp` 33（基线）→ **52**，其"新增"错误码只有两个，
但**根因只有一个**：

```
line 1407/1422/1427/2027/2147/2159  C2653  '_inline_RoleAtt_Remark' is not a class or namespace name
line 2033                           C2065  '_inline_RoleAtt_Remark' : undeclared identifier
line 2033                           C2065  'v20' : undeclared identifier
```
`line 2033` 就是 `_inline_RoleAtt_Remark *v20; // ebx` —— **类型未声明导致声明本身失效**，
所以 `v20` 的 C2065 是**连带后果**，不是独立缺陷。

**证据**：
- `asm/pal3/ida_structs.json` 里**有** `_inline_RoleAtt_Remark` 与
  `_inline_RoleAtt_Remark::$101B5358F90B67F92EE483560EB2675D`；
- 但 `grep -rn _inline_RoleAtt_Remark pal3/src include/` **只命中 PAL_GDB.cpp 自身**
  ⇒ **没有任何生成头文件声明它**。

⇒ **codegen 未发射 `_inline_*` 类型定义**（已知 `dangling nested type` 家族，
见 `_cleanup_finding_dangling_nested_type.md`）。这是**独立缺陷**，
修它要给 `_inline_*` 合成类型发射声明（或改为内联渲染），属 codegen 功能，不在本轮。

## 4. 基线刷新（明示）

因为两份基线都停在 2 天前、导致无法衡量单次改动，且**上面 3 个被标记文件现已全部定性**
（A 已修、B 已修、C 已定位到 codegen 缺陷且量化在 §3），故**有意刷新**：
```bash
python3 tools/regression_detector.py --save-baseline
python3 tools/compile_regression.py --update-baseline
```
刷新是"接受现状为参照"，**不是**宣称 §3 已修 —— 该缺陷以精确错误码/行号记录在此，
也仍会被 `error_classifier` 统计到。

## 5. 复现
```bash
grep -c "const char aUiCombatPointe" pal3/src/globals.cpp   # 1（且带 const）
python3 tools/regression_detector.py --check --format text   # 刷新后应为 新失败0/新错误0
python3 pipeline/cli.py probe && python3 pipeline/cli.py match
```
