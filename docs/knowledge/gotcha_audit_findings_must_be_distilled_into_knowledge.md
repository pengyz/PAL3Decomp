---
name: gotcha-audit-findings-must-be-distilled-into-knowledge
description: 本仓的高价值审计结论**落盘了却落错了面**——`data/status/` 有 373 文件/293 tracked，而知识库对它只有 2 处引用且都当"基线输入路径"；于是"审计 → status → 消失"，下一个会话从 docs/knowledge/ 起步就永远看不到它们
type: gotcha
created: 2026-09-20
updated: 2026-09-20
status: active
sources: [session-2026-09-20, docs/knowledge/README.md]
---

# gotcha：审计结论必须蒸馏进 `docs/knowledge/`，否则会"落盘但消失"

## 症状（不是"没落盘"，而是"落错面"）

- `data/status/` **373 文件 / 293 tracked**（`git ls-files data/status/ | wc -l` = 293）。
- 知识库（`CLAUDE.md` / `docs/knowledge/README.md` / `MEMORY.md`）对 `data/status` 的引用**只有 2 处**
  （`CLAUDE.md:159,162`），且都当作**"基线输入的路径"**，**不是知识入口** ✗。
- `docs/knowledge/README.md:13` 明令："发现**门禁失效或流程漏洞** → 写 `gotcha`（**这类往往最贵，一旦漏掉会重复踩**）"。
  而实践中最贵的一类结论（工具被 `--help` 覆盖产物、门禁恒真、闸写了但不失败…）**一条都没进 knowledge** ✗。

## 实证（2026-09-20）

- `data/status/_audit_toolchain_pipeline_20260920.md`（12KB，4 维度多 agent 审计 + 交叉复核，tracked，
  commit `2c3467912`）**没有被蒸馏进 `docs/knowledge/`** ✗ —— 一个从知识库起步的 AI 实例**永远不会看到它**。
- 同一天发生的两起事故（审计子代理用 `--help` 探测无 argparse 的工具 ⇒ 覆盖受跟踪产物 ✗）
  证据齐全地记在 `data/status/` 的三个文件里，**knowledge 里 0 条** ✗。
- 本 gotcha 自身也是同一病灶的产物：它要记录的结论最初只存在于
  `data/status/_knowledge_process_diagnosis_20260920.md` ✗ —— **递归地证明了这条规则必须存在** ✓。

## 正确做法（三条可检查要求）

1. **落盘面**：通用规律 / 门禁坑 / 被纠正的方法 / 确认有效的取舍 ⇒ 写进 `docs/knowledge/`（6 类 type）；
   **单字段证据**仍归 `data/annotations/CHANGE_LOG.md`（边界见 README:127-135）。
   **跨边界的产物**（如"证据台账"）必须显式指定归属，不能默认扔进 `data/status/` ✗。
2. **写入触发器**：审计/诊断结束时**必须**问一句"其中哪些是通用规律而非一次性产物？"
   把这些提炼成条目 ✓；并在 `MEMORY.md` 对应 type 段**追加一行** ✓（README:97 的第 4 步）。
3. **可发现性**：条目落盘后**必须在 `MEMORY.md` 有入链** ✓（实测曾有 **5 条条目未入索引** ✗，
   其中恰包括"唯一近似 SOP"的那条 ✗）。

## 相关

- 索引与 frontmatter 的实际不完整度（实测）：**5 条未入 `MEMORY.md`**、**7 条 frontmatter 不合规**
  （1 条完全无 frontmatter ✗）、**kairos 断档 23/32**（09-18 单日产生 14 条却无 kairos ✗）。
- `docs/knowledge/README.md` 要求 frontmatter 含 `name/description/type/created/sources`；
  6 条条目用的是另一套字段（`title/type/date/confidence`）✗ ⇒ 任何按 `created` 建时间线的工具会漏掉它们。
