---
name: gotcha-ida-defs-register-macros-are-zero
description: include/pal3/ida_defs.h 把 Hex-Rays 寄存器伪变量 `_EAX/_ESI/_ET1...` 定义成字面量 0 —— 这一个 hack 造成 167 条编译错误（占全部 7.8%），且集中在 2 个单元共 150 条
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：`#define _EAX 0` 一个 hack = 167 条错误（7.8%），且无单一类型可修

## 现象

`include/pal3/ida_defs.h:75-84`（**手维头文件，是编译输入**）：

```c
// IDA decompiler artifacts (Hex-Rays pseudo-code that leaked through codegen)
typedef void _UNKNOWN;
#define _EAX 0
#define _EBX 0
...
#define _ESI 0
#define _EDI 0
#define _EBP 0
#define _AX 0
#define _ET1 0
#define Func 0
```

文本替换后：

| 生成源码 | 展开 | 错误 |
|---|---|---|
| `_ESI = &flt_C0816C;` | `0 = &flt_C0816C;` | `C2106` left operand must be l-value |
| `_ESI += 2176;` | `0 += 2176;` | `C2106` |
| `_ESI[1].m_teamSlotsB...` | `0[1].m_teamSlotsB...` | `C2109` / `C2228` |
| `v19 = _EDI[38];` | `v19 = 0[38];` | `C2109` subscript requires array or pointer type |
| `(_DWORD *)_EDI` | `(unsigned long *)0` | 合法（不报错）|

实测规模（基线普查 2150 条）：**源码行**含 `_E??`/`_ET?` 的错误 **167 条 = 7.8%**，
按码 `C2440` 40 · `C2228` 38 · `C2106` 36 · `C2109` 34 · `C2100` 14 …
**只集中在 6 个单元，其中 2 个占 150 条**：
`pal3/src/Role/RoleSystem.cpp` 88 · `pal3/src/Misc/ScriptVM.cpp` 62
（另 UIScene 10 · PAL3 3 · ScriptSystem 3 · CCBSystem 1）。

✅ 这两个单元**不在** `C1003 --errorlimit 102` 截断名单里（截断的是
`CCBStage.cpp`/`CCBUI.cpp`/`free_functions.cpp`）⇒ 这两个数字是**真实计数**，
不是"去掉后隐藏错误会浮出来"的假收益。

## **为什么**：没有任何**单一全局类型**能修好

同一个伪寄存器在不同函数里被赋予不同指针类型：

* `_ESI = &flt_C0816C;`（`float *`）
* `_ESI = &g_SceneMgr...`（别的类型）
* `_ESI += 2176;`（要指针算术）
* `_ESI[1].m_teamSlotsB.combat...`（要求 pointee 是带该成员的 struct，如 `RoleSystem`）
* `(((RoleSystem *)_ESI))->RoleSystem::UpdateMovement(...)`（显式 cast，说明 Hex-Rays 自己也不确定）

逐个候选类型的后果：

| 声明 | 结果 |
|---|---|
| `unsigned long _ESI;` | `= &x` → `C2440`（指针→整数）|
| `void *_ESI;` | `+= 2176` / `[1]` → **`C2036 'void *' : unknown size`**（换一类错误，非修好）|
| `char *_ESI;` | `= &flt_...`（`float*`→`char*`）→ `C2440` |

⇒ **必须按函数推断类型**（codegen 侧）或**修 IDB 的函数签名/寄存器建模**（annotation 侧），
二者都不是一行改动。这正是 CLAUDE.md"IDA 层能解决的问题在 IDA 层解决"的适用场景：
`_EAX/_ESI` 出现说明 Hex-Rays 无法把该寄存器建模成命名参数/局部
（多为 `__usercall` 或寄存器变量跨调用存活），根治在签名。

## **何时使用**

* 想把"总错误 2150"往下压时：这是**单簇最大**（167 条，7.8%），且集中在 2 个文件；
* 看到生成代码里出现 `_EAX/_ESI/_EDI/_ET1`：不要以为它们是真变量 —— 它们在预处理后是 `0`，
  任何"给它一个类型就行"的想法都会撞上上表；
* 改动 `include/pal3/ida_defs.h` 时：它同时含其它已声明 workaround
  （`JUMPOUT(x)` 展开为空、`qmemcpy`→`memcpy`、`COERCE_*` 取地址要求 lvalue 等），
  改一处要顺带确认没有别的宏依赖同一形态。