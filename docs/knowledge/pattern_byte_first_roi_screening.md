---
name: pattern-byte-first-roi-screening
description: 唯一能把"修复"转成 L1 的筛选法——在 s4 的 partial 行里取「编译长度≈原始长度 且 n_diff 小」的那些，再从差异偏移读出真实字节并用 IDA MCP 对照原指令，按"寄存器选择/偏移/结构"分类；其余 190 条 partial（匹配度<50%）任何小修都不会产生字节收益
type: pattern
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# pattern：字节优先的 ROI 筛选（唯一能把修复变成 L1 的入口）

## 规则

要拿到**字节收益**（L1 ↑），候选必须**同时**满足：

1. **在 S2 绿单元里**（否则 `match` 根本不编译/比对它 ⇒ 无读数）；
2. **编译长度 / 原始长度 ≈ 1.0**（结构完整；否则源码缺一大截，小修无意义）；
3. **`n_diff` 小**（`s4_diff_detail.json` 的 `diffs` 给出**精确偏移**）。

然后从 `diffs` 偏移处读出**原始字节**与**我们的字节**，再用 IDA MCP `disasm` 看该偏移落在哪条指令 ⇒ 分类：

| 分类 | 判据 | 修法 |
|---|---|---|
| **偏移错** | 位移字节不同（如 `0D60h` vs `0D90h`）| 改注解成员偏移（A 级证据：指令里的 `reg+disp32`）|
| **寄存器选择** | ModRM 不同、位移相同（如 `8B 41 3C` vs `8B 40 3C` = `[ecx+3Ch]` vs `[eax+3Ch]`）| 源码形状（循环/变量类型）微调，**难** |
| **结构/归属** | 位移**远超**注解里的类大小（如访问 `+0xD60` 而类只有 268 字节）| 归属或注解需要重建 ⇒ 不是小修 |

## 2026-09-21 实测（本仓当前状态）

* partial **198** 条中：编译/原始长度比 `≥0.95` 者 **135** 条；**`match_pct ≥ 80%` 且比值≥0.95 者 10 条**；`≥50%` 者 27 条。
* **3 条各只差 1 个字节**：

| 函数 | VA | size | 差异偏移 | 原因 |
|---|---|---|---|---|
| `AStarPathFinder::FindInOpen(int)` | `0x00401500` | 34 | @22 | **寄存器选择**：原 `mov eax,[ecx+3Ch]` / 我们 `mov eax,[eax+3Ch]` |
| `AStarPathFinder::FindInClosed(int)` | `0x00401530` | 34 | @22 | 同上 |
| `UINote::GetEntryPtr(int)` | `0x00528D30` | 17 | @10 | **结构/归属**：原访问 `[this+0xD60+nIndex*0x100]`，而注解 `UINote` 仅 **268** 字节 ⇒ 归属错或注解严重不完整 |

* 另有 `RoleCamera::UpdateAudioListener`(95B, 4 diff) · `SceneMgr::ClearInactiveRoles`(58B, 3) · `Scene::_todo_421870`(53B, 4) 等。

⇒ **这 10 条（尤其 3 条单字节）才是"修了就能看到 L1 上升"的地方**；
其余 ~190 条 partial 匹配度 <50% ⇒ **任何小修都不会产生字节收益** ✗

## **为什么**必须这样筛（本会话两次教训）

* F5 寄存器族：167 条错误看似可修，但修掉会**揭开**被遮蔽的 `C2094`，且函数**不可编译 ⇒ 无字节判定** ⇒ 假收益；
* 27 条"显式 this 重复发射"：改写 `ResetPathState` 调用形式后实测 **5.5% → 5.2%**（**略降**），
  因为该函数编译长度 **160 / 原始 343** ⇒ 结构只有一半，小修无意义 ✗

## **何时使用**

* 任何时候想"修一族拿 N 条错误收益"时：**先跑这个筛选**，确认字节落点与结构完整性；
* 迭代循环：改一处 → `python3 pipeline/cli.py loop --stages codegen,probe,match` → 读 `s4_baseline.json` 的
  `match_L1`（**唯一有效判据**）与 `s4_diff_detail.json` 的 `diffs` 偏移 ✓
