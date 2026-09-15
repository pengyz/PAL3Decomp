# K 落地记录：FLIRT 把游戏函数误命名为 CRT 命名空间函数

> **任务**：`docs/specs/2026-09-15-annotation-tombstone-task.md` §6 的 K
> **日期**：2026-09-15 · **执行**：captain
> **缘起**：t7 删除 `_IDA_MISID_PATTERNS` 后 `ExternalStatistics.cpp` ok→fail
> （`L62 C2653 'Concurrency' : is not a class or namespace name` + `C2065 'MarkInactive' : undeclared identifier`），
> 由独立对抗性复核子 agent `2c66861a` 指出这是 t7 的**未披露后果**，且属**半成品恢复**

---

## 1. 根因：一次仅凭「名字」的误判，导致真实游戏函数被跳过反编译

### 被误命名的地址

`0x00532D50` 的 IDA 名是 `?MarkInactive@ExternalStatistics@details@Concurrency@@QAEXXZ`。
前一轮会话据此把整组 4 个地址写入 `skip_functions.json`（`reason: crt_runtime`），
其 `CHANGE_LOG.md` 自载理由与置信度：

> `- **置信度**: 90`
> `  - CRT 函数: 函数名明确属于 MSVC Concurrency Runtime (非游戏逻辑)`

**该判断只有名字，没有任何函数体取证** —— 这是错误的。

### 函数体取证（决定性，`idat` 探针实测）

```
0x00532D50  C7 41 18 00 00 00 00  C3      size=8
            mov dword [ecx+0x18], 0 ; retn      （ecx = this，thiscall）
0x00532D30  8B 41 50 89 41 18  C3         GetStateMode  size=7
            mov eax,[ecx+0x50] ; mov [ecx+0x18],eax ; retn
```

**两者操作同一字段 `this+0x18`** —— `0x532D30` 是「取 `+0x50` 写入 `+0x18`」，
`0x532D50` 是「把 `+0x18` 清零」。这是同一族的游戏逻辑，**不是 CRT**。

### 位置证据

`0x00532D50` 的邻居**全是游戏函数**（`data/annotations/functions.json`）：

```
0x00532CF0  CalcAngleBetweenVectors
0x00532D30  GetStateMode
0x00532D50  ← 被误命名为 Concurrency::...::MarkInactive
0x00532E10  ResetPathState
```

对照：另 3 个同批被 skip 的地址（`0x004790F0` / `0x00479250` / `0x004B4830`）
**都不在 `functions.json`** 里——它们才是真正的 CRT 区域。

### 调用点证据

```
xrefs_to(0x00532D50) = 0x534EA9   ← 落在 ExternalStatistics::UpdateFromRole(0x00534E60) 内
```

同函数三个分支（decomp 原文）：

| 分支 | 调用 |
|---|---|
| `CheckKeyPress(this, 2)` | `GetStateMode(*(RoleSystem **)this)` |
| `CheckKeyPress(this, 3)` | `RoleSystem::NegateStateMode(*(RoleSystem **)this)` |
| `Reset(this,2) \|\| Reset(this,3)` | **`Concurrency::details::ExternalStatistics::MarkInactive(*(Concurrency::details::ExternalStatistics **)this)`** |

前两个分支**都取 `*(RoleSystem **)this`** ⇒ 第三个分支的目标也是 `RoleSystem` 的方法。
FLIRT 的名字与 `*(RoleSystem **)this` 强转在类型上自相矛盾。

### 为什么 t7 之后才暴露

原 `[IDA_MISID]` 机制**把这行整行注释掉**，于是垃圾名从不出现在可编译代码里。
t7 删除 6 个硬编码模式表后原样解除注释 ⇒ 垃圾名直接暴露。
扫描清单 `AT-212` 对子类 (ii) 的原始建议原文是「**应重命名保留**」——
t7 做的是**原样解除注释**，属**半成品恢复**（captain 在此确认该定性成立）。

---

## 2. 修法：重命名保留（符合项目既定的证据门槛）

**改动 1**：`data/annotations/functions.json` 的 `0x00532D50`（此前**不存在**该条目）：

```json
"0x00532D50": {
  "name": "ClearStateMode",
  "signature": "void __thiscall RoleSystem::ClearStateMode(RoleSystem *this)",
  "class": "RoleSystem",
  "_flirt_correction": "…（完整取证与理由，含字节、邻居、xrefs、与 GetStateMode 的同字段论证）"
}
```

命名理由：`C7 41 18`（`mov dword [ecx+0x18], 0`）与邻居 `GetStateMode` 的
`8B 41 50 89 41 18`（`mov eax,[ecx+0x50]; mov [ecx+0x18],eax`）操作**同一字段 `0x18`**，
故本函数是该字段的「清零」变体。类归属取 `RoleSystem`（与同族 `GetStateMode`/`ResetPathState` 一致，
且与调用点的 `*(RoleSystem **)this` 一致）。

**改动 2**：`data/annotations/skip_functions.json` **删除** `0x00532D50` 条目
（其名字是 FLIRT 误命名，现已作废；保留会让该真实游戏函数继续被跳过反编译）。

**为什么这不违反证据门槛**：CLAUDE.md 要求「每一处 annotation 修改必须有二进制直接证据」。
本改动的证据是**函数体字节 + 同字段邻居 + xrefs 调用点**（均 A 级），
且**只改名字、不改任何偏移/类型/结构布局**。改名不影响字节匹配：
`call rel32` 的操作数是相对地址，与符号名无关，目标字节不变。

---

## 3. 实测验证

### 决定性读数

| 项 | K 前 | K 后 |
|---|---|---|
| `pal3/src/Misc/ExternalStatistics.cpp` | **fail**（`err=3`：`C2653`×2 + `C2065`） | **ok**（`err=0`） |
| `decomp` JSON 数 | 3594 | **3595**（被误 skip 的函数重新进入反编译，新增 `ClearStateMode_00532d50.json`） |
| 导出名 | `?MarkInactive@ExternalStatistics@details@Concurrency@@QAEXXZ` | **`ClearStateMode`**（`void __thiscall(RoleSystem *this)`） |

### 生成源码（与同函数其它分支形态一致）

```cpp
// K 前
Concurrency::details::ExternalStatistics::MarkInactive(*(Concurrency::details::ExternalStatistics **)this);
// K 后
ClearStateMode(*(RoleSystem **)this);
```

### 判据

| 判据 | 硬线 | 起点 | **K 后** |
|---|---|---|---|
| `ok` | ≥53/198 | 53 | **54/198** ✅ **净提升** |
| `L1` | ≥5 | 5 | **6** ✅ |
| `oob` | ==0 | 0 | **0** ✅ |
| struct import | 881/881 | 881/881 | **881/881** ✅ |

---

## 4. 过程中的事故与处置（如实记录）

captain 的 IDA 探针脚本在写出结果后**崩溃（exit 134）**并留下 5 个崩溃边车
（`original/PAL3.exe.{id0,id1,id2,nam,til}`）。处置：

1. 按 `comm` 名精确清理残留 `idat` 进程（**注意**：先前用 `pkill -f`/`kill -9` 配 `ps|grep` 两次误杀了 captain 自己的 shell —— 改用 `ps -eo pid,comm | awk '$2=="idat"'` 才安全）
2. 清除 5 个边车
3. **幂等性验证**：重跑 `apply` → `[3] Structs: 881/881 (fail=0)`、`FATAL=0`、**无边车、干净退出**
   ⇒ IDB 未损坏

---

## 5. 登记的新缺陷（本轮不修）

| 项 | 说明 |
|---|---|
| **其余 3 个被 skip 的 Concurrency 命名** | `0x004790F0` / `0x00479250` / `0x004B4830` **不在 `functions.json`**，需逐条做同样的函数体取证，判断是真 CRT 还是同为误命名。**未验证。** |
| **`_IDA_MISID` 子类 (ii) 的其它站点** | AT-212 记 `Concurrency` 49 处、`std::_Xlen` 11 处、`std::_Xran` 9 处。`_Xlen`/`_Xran` 在 decomp 里**不存在同名函数记录**，属 Hex-Rays 在越界检查分支上贴的 STL 库名（`if (v4-1 > 0xFFFFFFFD) { std::_Xlen(); }`）——这类**是否需要保留调用**未逐条裁定 |
| **`skip_functions.json` 的 `crt_runtime` 判据无取证要求** | 本缺陷的入口就是「仅凭名字即可标 skip」。建议加判据：标 `crt_runtime` 必须有函数体或区域证据 |

---

## 6. 相关文件

- 任务书：`docs/specs/2026-09-15-annotation-tombstone-task.md`
- 修改：`data/annotations/functions.json`（新增 `0x00532D50`）、`data/annotations/skip_functions.json`（删除 `0x00532D50`）
- 扫描清单原建议：`data/status/_cleanup_scan_attribution.json` 的 `AT-212`
- 复核来源：`data/status/_cleanup_review_arc_locale_dangling.json` 的
  `independent_findings_not_reported_by_captain`