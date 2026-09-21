---
name: gotcha-three-competing-baselines-make-gates-permanently-red
description: 管线有 3 份互不相干的基线（compile_baseline/latest/s4_baseline），实测互相矛盾 ⇒ 在干净 HEAD 上 codegen all 与 match 恒 exit 1，自动化循环分不清信号与噪声
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：三份互相矛盾的基线 ⇒ 门禁恒红 ⇒ 循环不可自动化

## 现象

在**干净 HEAD、零改动**上跑一轮完整管线，有两个阶段**恒 exit 1**：

| 阶段 | 报出的"退化" | 真值 |
|---|---|---|
| `codegen all`（末尾 `compile_regression`）| `⚠️ REGRESSIONS (1 files): pal3/src/Misc/UIStatic.cpp` · `Baseline S2: 76/204` vs `Current 75/205` | **真实回归 0**（同一轮 `regression_detector`：新失败 0 · 真新增 0 · 收敛 0）|
| `match`（末尾 L1 棘轮）| `[L1 ratchet] previous 38 -> current 35` · `REGRESSION: byte-perfect functions lost` | 记录值 38 来自**更早的树**；实况 34→35（本轮反而 +1）|

根因：仓里有**三份互不相干的"基线真相源"**，各自被不同工具消费，且互不同步：

| 文件 | 记录 | 消费者 |
|---|---|---|
| `data/status/compile_baseline.json` | S2 `76/206` | `tools/compile_regression.py`（`codegen all` 内部）|
| `data/status/baselines/latest.json` | S2 `75/205` | `tools/regression_detector.py`（`probe` 内部）|
| `data/status/s4_baseline.json` | `stats.match_L1` `38` | `pipeline/compare_pal3.py` 的 L1 棘轮 |

第一份的"回归"来自**文件集变化**（204/206 → 205 个 cpp，多出 `UIStatic.cpp`）被当成"新失败文件" ✗，
不是错误数变化。

## **为什么**这是"不可持续"的根因

* 自动化循环需要一个**可判定的通过/失败信号**；两个阶段恒红 ⇒ 真退化与假失败**无法区分** ✗
  （人会开始习惯性忽略 exit code ⇒ 门禁实际失效 ✗）；
* 三份基线各说各话 ⇒ 事后查文件**不能**判断退化（本仓早已有此纪律：必须当场读管线输出）✓，
  但"当场读输出"要求人**知道哪条是噪声** —— 这条知识原本只散落在台账里。

## 处置（2026-09-21 已落地）

1. **`python3 pipeline/cli.py status`**（新增，**只读**）：打印一次迭代的**唯一权威顺序**、
   三份基线的对照与时间戳、以及**已知恒红门禁**（含"记录 X / 实况 Y / 为什么 / 怎么处理"）✓
   `--strict` 时基线不一致或有恒红 ⇒ exit 1（给脚本用）✓
2. **`python3 pipeline/cli.py loop [--expect-s2 75/205 --expect-errors 2150 --expect-l1 35]`**（新增）：
   一条命令跑完 `apply→export→codegen→probe→match`，把**"先断言基线再测量"这条纪律机械化** ✓；
   已知恒红阶段被**显式标注 `[TOLERATED]`**（绝不静默吞掉 ✓），非容错失败立即中止后续阶段 ✓；
   阶段耗时与 `match` 的 L1 写入 `data/status/_loop_last.json`（gitignored）供 `status` 显示 ✓
3. `CLAUDE.md` 的强制检查点表加入这两条，并写明"干净 HEAD 上恒红"这一事实 ✓

⚠️ **刷新棘轮基线没有做**（`compile_regression --update-baseline` / 推进 L1 棘轮）——
那是**决策**，会改变门禁的判据，必须由人确认后再执行 ✓。

## **何时使用**

* 任何"自动化/循环/批量迭代"的设想之前：**先跑 `cli.py status`** ✓ ——
  不知道恒红门禁，任何循环都会被两个假失败淹没；
* 看到 `codegen all` 或 `match` exit 1 时：**先看是不是这两个已知恒红**，再判真伪 ✓；
* 要刷新任何基线时：先确认"真实回归量 = 0"（用同一轮的另一份门禁交叉验证 ✓），再显式刷新 ✓。