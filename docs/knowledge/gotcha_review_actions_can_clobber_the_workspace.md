---
name: gotcha-review-actions-can-clobber-the-workspace
description: 审查/对比动作本身会写坏工作区——`--help` 探测无 argparse 的工具会覆盖受跟踪产物；`ln -s` 指向受跟踪文件后重定向会"写穿符号链接"；两者都静默、都在"只读"意图下发生
type: gotcha
created: 2026-09-20
updated: 2026-09-20
status: active
sources: [session-2026-09-20]
---

# gotcha：审查动作会写坏工作区（两起 `--help` 事故 + 一起符号链接写穿）

## 形态一：`--help` 探测无 argparse 的工具 ⇒ 覆盖受跟踪产物

本仓**至少 4 个工具没有 argparse**，`--help` 会被当作**普通参数执行**，而它们**无条件写盘** ✗：

| 事故 | 后果 |
|---|---|
| `tools/sig_evidence.py --help` | 受跟踪证据包 **6931 → 1648 行**（`-6020`），判级 456 → 144 ✗ |
| `tools/misattribution_ledger.py --help` | 台账 **197 → 3 clusters** ✗ |

两起都发生在**只读审计意图**下 ✓；事后靠"与 HEAD 逐字节比对"确认并恢复 ✓。
**残留静态风险（实测仍有 5 个）**：`tools/benchmark_eval.py`、`tools/mcp_query.py`、
`pipeline/decomp_quality.py`、`pipeline/extract_type_errors.py`、`pipeline/scan_class_members.py`
（无 argparse + 写盘 + 无 `--help` 守卫 ✗）。
**护栏范式**（见 `tools/_land_sizes.py`）：**任何以 `-` 开头且不是已知开关的参数 ⇒ 拒绝执行并退出** ✓。

## 形态二：`ln -s` 指向受跟踪文件 + shell 重定向 ⇒ **写穿符号链接** ✗

2026-09-20 由一实现子代理**主动披露**：它为做 HEAD 对比，先建
`ln -s` 指向仓库的 `pipeline/cli.py`，再 `git show HEAD:pipeline/cli.py > $T/pipeline/cli.py`
⇒ 重定向**穿过符号链接**，把**工作区**的 `pipeline/cli.py` 覆盖成 HEAD 内容 ✗，
**它当时的实现编辑被静默抹掉** ✗。它自行发现、恢复、重做并逐项复核 ✓。
**正确做法**：要对比副本就**真实复制到 `/tmp`** ✓（`cp` 而非 `ln -s`）；
或直接用 `git show HEAD:<path>` 输出到 **`/tmp` 下的新文件名** ✓。

## 共同教训

1. **"只读"是意图，不是保证** ✗ —— 必须靠**工具自身护栏**（拒绝未知开关 ✓、写盘需显式 `--json <path>` ✓）
   与**动作规范**（不在仓库内建符号链接再重定向 ✓）来保证。
2. **回滚成功 ≠ 门禁能防住下一次** ✗ —— 两起事故的"恢复"是逐字节比对 ✓，但当时**没有留下注入式负例** ✗
   ⇒ 真正的收口是：给每个写盘工具加护栏 + 每个门禁配**注入式负例**（本仓后来为 L1 棘轮补上了 ✓）。
3. **改完立刻自查**：这类事故**静默** ✗，只有 `git status --porcelain` + 与 HEAD 的 `diff` 能发现 ✓。
