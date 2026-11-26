---
name: gotcha-loop-reading-contamination
description: 验收只认当轮完整 loop 的 S2/总错误/L1/[metric]；并发 loop 会互相覆盖 ida_structs、pal3/src、probe_census、基线与固定日志，运行中取样曾出现 S2 0/229、总错误 4348 的中间态
type: gotcha
created: 2026-11-26
updated: 2026-11-26
status: active
sources: [session-2026-11-26, incident-2026-11-26T21:24]
---

# gotcha：loop 是唯一权威读数，并发/陈旧产物会污染 census

## 现象

同一棵源码树，隔几分钟读到的 S2、总错误、L1 可以差一个数量级：

| 时点 | 读数 | 性质 | 证据 |
|---|---|---|---|
| 2026-11-26 21:24:21 | S2 **0/229**、总错误 **4348** | 并发 loop 的编译中间态 | `docs/handoff/2026-11-26-struct-hole-campaign-handoff-errata.md:64` |
| 2026-11-26 19:14:46 | S2 157/229、总错误 633 | 同日完成态，仅作对照，不是当前验收 | `docs/knowledge/struct_hole_fill_campaign_20261126.md:27` |

21:24 那一眼是 `cli.py status` 从 `data/status/probe_census.json` 读到的，不是代码退化；但把它当结论，就会误判“全库崩塌”。
反过来，只跑 `codegen`/`probe`/`match` 中一步得到的“改善”，也不等于完整链路的验收读数。

## 规则

**任何“修好了 / 指标改善 / 可验收”只认当轮完整 `python pipeline/cli.py loop` 的 S2、总错误、L1 与 match `[metric]` 行。**

报告必须同时给出：

1. 实际命令（含 `--stages` 与否；只跑部分阶段只能标“诊断”，不能标验收）；
2. 当轮日志路径：`pipeline/_logs/loop_apply.log`、`pipeline/_logs/loop_export.log`、`pipeline/_logs/loop_codegen.log`、`pipeline/_logs/loop_probe.log`、`pipeline/_logs/loop_match.log`；
3. S2 `ok/total` 与总错误；
4. L1 与 `[L1 ratchet] population`（可比总体）；
5. `data/status/probe_census.json` 的 `generated_at`，以及日志的 mtime。

不能拿历史基线、上一轮日志或单阶段 stdout 代替当轮 loop 输出。

## 为什么：loop 是单通道，所有阶段写固定路径

`pipeline/cli.py:1088` 把顺序固定为：

```
LOOP_ORDER = ['apply', 'export', 'codegen', 'probe', 'match']
```

每个阶段是独立子进程（`pipeline/cli.py:1171`），但读写的是同一组固定路径：

| 阶段 | 写什么 | 代码证据 |
|---|---|---|
| `export` | `asm/pal3/ida_structs.json` | `pipeline/ida/export_full.py:982` |
| `codegen` | **先 `rmtree` 整个 `pal3/src/`，再重建** | `pipeline/gen/codegen.py:90-95` |
| `probe` | `data/status/probe_census.json` | `pipeline/probe_compile.py:227` |
| `match` | `data/status/s4_diff_detail.json`（compare 写回）；`data/status/s4_baseline.json` 在显式 `--rebaseline` **或** `pairing-infra` 自动对齐时都会被写 | `pipeline/compare_pal3.py:1002-1004`、`pipeline/cli.py:740`、`:811`、`:850-851` |
| 所有阶段 | 固定日志 `pipeline/_logs/loop_<stage>.log`，以 `w` 打开 | `pipeline/cli.py:1181-1183` |

所以两个 loop 并发时，会出现：

- A 的 `codegen` 正在 `rmtree pal3/src`，B 的 `probe` 正在编译这棵树 ⇒ 头文件缺失/半写；
- A 的 `export` 刚写完 `asm/pal3/ida_structs.json`，B 的 `codegen` 又按另一个 IDB 状态重建；
- A 的 `match` 在 B 的 `probe_census` 上算 L1，population 与上一轮不同；
- 同名 `loop_*.log` 被后一个 loop 截断重写，事后无法还原当时输出。

loop 自身没有跨进程互斥；它默认“工作区只属于我”。

## 21:24 事故：可复核部分与不可复核部分

**可复核：**

- 21:31 执行 `python3 pipeline/cli.py status` 时，`data/status/probe_census.json` 已被并发 loop 改写到 `2026-11-26T21:24:21`，S2 0/229、总错误 4348（`docs/handoff/2026-11-26-struct-hole-campaign-handoff-errata.md:64`）。
- 盘点期间约 21:18 起有另一轮 loop 在跑（`/tmp/r5_loop.log`，由并发卡启动），`data/status/probe_census.json` 的 mtime 21:24 属于该轮（`docs/audit/2026-11-26-r6-backlog-dossier.md:225`）。
- 生成头 `pal3/src/_ns_udts.h` 是未跟踪文件（`git ls-files pal3/src/_ns_udts.h` 无输出），坏副本不留在仓库里。

**机制（可复核）：**

并发窗口里，`pal3/src` 的清理/重建与另一路编译交错，头文件可能缺失或半写；生成头还必须维护 by-value 顺序：by-value 成员所需的完整定义要排在依赖块之前（`pipeline/gen/stages/emit_headers.py:4656-4659`）。顺序一旦被破坏，编译器先在头文件层 `C2146`/`C2011` 级联，probe 判大量单元 fail，聚合起来就是 S2 0/229、总错误数千。21:24 的现场形态符合这一点（S2 全 0、数千错误），但坏头未入库，具体行号不可复核（见下）。

**不可复核细节：**

任务交接把坏头定位到 `pal3/src/_ns_udts.h:127` 的 inline union 按值使用 `UIFrameContainer`、其 `#include` 在 `pal3/src/_ns_udts.h:182`。坏头未入库、事后已被回退/重新生成覆盖，这两个行号在仓库里无法复核，本文只把它们当事故线索，不作证据。结论不依赖它们：**21:24 是中间态，不是代码退化，不能算到 #6 或任何修复卡头上。**

## 判据：读任何一个数之前

### 1. 先确认没有第二个 loop

```bash
ps -eo pid,lstart,cmd | grep '[p]ipeline/cli.py loop'
```

看到第二个 `python3 ... pipeline/cli.py loop`（包括 `loop --stages ...`）就不要取样：等它跑完，或先停掉自己这一路。当前 shell 自己的命令行不算。

### 2. 确认 IDB 导出不旧于注解

```bash
find data/annotations -name '*.json' -newer asm/pal3/ida_structs.json -print -quit
```

**无输出** = `ida_structs` 比所有注解新；**有输出** = 导出陈旧，先 `apply` → `export`，再谈读数。

### 3. 确认 codegen 不旧于导出

```bash
find pal3/src -type f -newer asm/pal3/ida_structs.json -print -quit
```

无输出说明 `pal3/src` 里没有晚于 `ida_structs` 的文件，codegen 可能没在本轮跑过；此时 probe/match 读的是旧树。

### 4. 读 census 的 `generated_at`，不读“现在几点”

```bash
python3 -c "import json; d=json.load(open('data/status/probe_census.json')); print(d['generated_at'], d['s2']['ok'], d['s2']['total'])"
stat -c '%y %n' data/status/probe_census.json pipeline/_logs/loop_probe.log
```

两个时间必须对得上；`status` 只是读这个缓存，不重新编译。

### 5. L1 先看 population，再看数字

```bash
grep -nE 'S2-passing|\[L1 ratchet\] (previous|population)|\[metric\]' pipeline/_logs/loop_match.log | tail -20
```

`[metric]` 由 `pipeline/compare_pal3.py:799` 打印。若 `population: previous matched=…/… -> current matched=…/…` 变了，两次 L1 **不可直接比较**；此时说“L1 降了/升了”都不成立，先解释总体为什么变。

### 6. S2 全 0 时的排查顺序

```bash
grep -nE 'C2146|C2011|Cannot open include|_ns_udts' pipeline/_logs/loop_probe.log | head
```

先查生成头/包含顺序，再查是否有第二个 loop；只有**干净工作区 + 完整 loop** 复现出的 0/229 才能当代码退化。

## 边界

- 污染读数**不写基线**、**不算到某张修复卡头上**、**不据此 `--rebaseline`**。注意 `match` 的 `pairing-infra` 分支（`pipeline/cli.py:850-851`）会在 L1 与 coverage 同降且总体稳定时自动改写 `data/status/s4_baseline.json`：污染轮次若已跑过 `match`，先核对 `rebaseline` 字段与 detail 是否成对，按仓库双账纪律成对恢复后再跑干净 loop，不要手动改数字。
- `pal3/src/_ns_udts.h` 的生成顺序缺陷是另一个问题，不在本条知识的修复范围；不要手改生成头（下次 codegen 会覆盖）。
- `loop --stages ...` 是局部诊断，不是验收；单跑 `match` 得到的 L1 只能当线索。
- 历史基线不是当前读数；当前验收只认当轮完整 loop。
- 不要为了“并行省时间”同时跑两个 loop；需要并行时先串行化流水线，或等一方完全结束。

## 何时使用

- 准备在 Task/Thread/交接文档里写“S2 提升 / 错误下降 / L1 恢复 / 可验收”之前；
- 刚跑完 `codegen`、`probe`、`match` 中的任意一步，想拿它的输出下结论时；
- `status` 或日志出现 0/229、总错误突然数千、L1 大幅下降时；
- 看到同一时点两份产物（census 与日志、基线与 detail）数字对不上时。

## 最小报告模板

```text
命令：python3 pipeline/cli.py loop
完成时间：<YYYY-MM-DDTHH:MM:SS>
S2：<ok>/<total>（pipeline/_logs/loop_probe.log）
总错误：<n>（pipeline/_logs/loop_probe.log）
L1：<n>（pipeline/_logs/loop_match.log 的 [L1 ratchet]）
population：matched=<a>/<b>（与上一轮是否一致：是/否）
[metric]：<pipeline/_logs/loop_match.log 的 [metric] 行>
generated_at：<data/status/probe_census.json 的 generated_at>
并发检查：ps 输出无第二个 loop
```

## 引用

- 21:24 读数：`docs/handoff/2026-11-26-struct-hole-campaign-handoff-errata.md:64`
- 并发 loop 旁证：`docs/audit/2026-11-26-r6-backlog-dossier.md:225`
- 同日完成态对照：`docs/knowledge/struct_hole_fill_campaign_20261126.md:27`
- loop 顺序/日志：`pipeline/cli.py:1088`、`:1171`、`:1181-1183`
- 各阶段写点：`pipeline/ida/export_full.py:982`、`pipeline/gen/codegen.py:90-95`、`pipeline/probe_compile.py:227`、`pipeline/compare_pal3.py:1002-1004`、`pipeline/cli.py:740`、`:811`、`:850-851`
- match `[metric]`：`pipeline/compare_pal3.py:799`
- 生成头顺序：`pipeline/gen/stages/emit_headers.py:4656-4659`
- 相邻坑：`compile_regression` 只读缓存 census 的问题见 [gotcha_compile_regression_reads_cached_census.md](gotcha_compile_regression_reads_cached_census.md)；本条讲 loop 级并发与验收口径，不重复该条。
