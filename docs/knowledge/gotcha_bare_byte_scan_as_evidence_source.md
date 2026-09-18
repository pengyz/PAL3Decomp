---
name: gotcha-bare-byte-scan-as-evidence-source
description: 用"在原始字节里搜 0xC2/0xC3"找函数尾 retn，会把指令操作数里的同值字节当函数尾；对 3395 个注解方法与指令级真值分歧 367 个（11.6%），且幅度可达 105 个假 slots
type: gotcha
created: 2026-09-18
updated: 2026-09-18
status: active
sources: [session-2026-09-18]
---

**现象**：`pipeline/gen/ast_transform.py` 的 `ret_n_at()` 在 `original/PAL3.exe` 的
**原始字节**里从函数起点往前搜第一个 `0xC2`（`retn imm16`）或 `0xC3`（`retn`），
拿它当函数尾、换算出 `__thiscall` 的栈参数个数。这喂给"显式 this 证据门"，
而那个门决定全仓的生成文本。

**问题**：x86 指令的**操作数里**完全可能出现 `0xC2`/`0xC3` 字节。搜到的第一个
往往不是函数尾。代码注释自己写着"conditional returns"的盲区，但实际远不止条件返回。

**量化（A 级对照）**：拿 `original/PAL3.exe.asm` 做**指令级**取值（IDA 自己的清单、
同一个不可变 exe），对 3395 个注解方法：

| | 数量 |
|---|---|
| 指令级可用 | 3178（93.6%） |
| 与裸扫描**一致** | 2810 |
| **与裸扫描分歧** | **367（11.6%）** |
| asm 里是 COLLAPSED（无指令行） | 136（4.0%） |
| asm 里找不到 | 81（2.4%） |

分歧幅度极大，不是抖动：

| 方法 | 指令级真值 | 裸扫描 | 后果 |
|---|---|---|---|
| `Actor::LoadActorModel` | `retn 4` → 1 slot | **420** | 105 个假 slots |
| `Actor::SetVisible` | `retn 12` → 3 slots | **0** | 门拿不到正确值 |
| `Actor::InsertAction` | `retn 8` → 2 slots | **0** | 同上 |
| `RoleSystem::RecalcAggregatedStats` | `retn 4` → 1 slot | 16 | 门拿不到正确值 |

**修法**：以 `original/PAL3.exe.asm` 的**指令级**取值为**主源**，裸扫描降为 asm 不可用时的
**回退**，并把来源分布**打印到 stderr**（不静默）：

```python
n = ret_n_at_asm(va)
if n is None:
    n = ret_n_at(va)                      # 回退
    _ASM_SRC_STATS['byte' if n is not None else 'none'] += 1
else:
    _ASM_SRC_STATS['asm'] += 1
```

实测分布：**指令级 3126 / 裸扫描回退 202 / 无证据 11**。

**实现要点（都是踩过的）**：
1. **一次遍历建表**，不要在 `ret_n_at_asm` 里逐函数重新打开 18MB 清单 ——
   3395 × 45 万行会直接超时（我第一版就是这样，>60s 被 kill）。改成 `_asm_retn_map()`
   一次遍历成 `label -> [retn...]`，总耗时 **0.37s**。
2. **值不唯一 ⇒ 无证据**（保守），不要随便取一个。
3. `as child` 的 `proc near`/`endp` 定界与 IDA API 的 `disassemble_function`
   **不完全等价**（实测 `Role::CalcXueJianInit` asm 得 `[0]×4`、MCP 得 `[0]×5`），
   且 asm 里有 715 个函数是 COLLAPSED ⇒ asm 是**离线回退**，不是等价替代。
4. **不变量要写成测试**：`tests/test_retn_evidence_source.py` 断言"缓存值 ==
   另一套独立实现（`tools/sig_evidence.rets_of_asm`）对同一份 asm 的指令级读取 / 4"，
   从而暴露两套读取实现的分歧，而**不编码 annotation 状态**。

**效果**：`SwordUI.cpp` 转 ok（S2 65→66），错误普查里**只有 C2660 −1**，
L1 按多重集恒等；生成文本变化仅 7 个文件。
