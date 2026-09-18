---
type: pattern
date: 2026-09-18
---

# 注解修正要**攒批**跑管线：改一次跑一次的成本不可持续

## 成本事实

完整管线 `annotation → apply → export → codegen all → probe all → match` 里，
**`export` 是对全量函数重跑 Hex-Rays**，是重活（本会话实测单次约数分钟到十几分钟，
且其间不能并行做别的 IDA 操作）。而 annotation 修正是**以几十条为规模**反复进行的
（例如"归属无据候选"一次就筛出 339 条）⇒ **一条一跑**会把时间全花在等待上。

## 做法

1. **修正写入批次文件** `data/status/annotation_fix_batch.json`（每条含 `evidence`）；
2. **用 `tools/apply_annotation_batch.py` 一次落盘 + `check` 校验**（**不动 IDB**）；
3. 攒够一批后，**只跑一次** `--run-pipeline`；
4. 跑完做一次对账（`regression_detector --before`）与 `match`（L1）。

## 硬约束（必须保留，否则会重演历史事故）

`tools/apply_annotation_batch.py` **拒绝**下列条目（宁可不做，也不写无据改动）：

* **`evidence` 为空** —— 依据 `CLAUDE.md`「每一处 annotation 修改必须有二进制直接证据」，
  以及 `pattern_annotation_batch_rename_no_evidence.md` 记载的**一次无证据批量改名被整体撤销**；
* **重归属缺成员访问证据** —— 项目规则：不能仅凭 signature 的 `this` 修归属；
* **改名后仍无语义且缺 `name_evidence`** —— 见下。

## 与"函数名合理性"的配合

重归属的同时**必须复核函数名**：若名字仍无语义（`_sdtor*`/`sub_*`/尾部十六进制如
`Destroy_c880`/`Update_bbc0`），要给出 `name_evidence`（依据它**做什么**：成员访问、调用、
与哪个已知函数同构）。**给不出语义就写"含义未定"并保留 `_todo_` 风格的诚实占位名** ——
**禁止**为了"看起来有语义"而造名（这正是被撤销那次的做法）。
