---
name: annotation-batch-rename-no-evidence
description: 一次带 "A:cascade_sync" 标记、无 CHANGE_LOG 记录的批量重命名混进未提交改动，命中 CLAUDE.md 明文禁止的伪语义命名规则（m_nVal70/m_bFlagXXXX 地址后缀套壳）+ 跨结构体错误传播（把 float cluster 的字段名复制到不相关的 int 字段）
type: pattern
created: 2026-08-29
sources: [session-2026-08-29]
---

发现 26 个 struct JSON 里混有一批 `_todo_XXX` → 伪语义名的重命名，`source` 字段统一带 `A:cascade_sync` 标记，但全仓 grep 找不到任何脚本产出这个标记、CHANGE_LOG.md 也没有对应条目。命中两类问题：(1) 纯地址后缀套壳（`m_nTodo_070` → `m_nVal70`，`m_nTodo_4990` → `m_nInitVal2`），和 CLAUDE.md 禁止的 `m_nState_4968` 是同一模式；(2) 跨结构体误传播——CGameData 的 int 字段被改名 `m_fTimeAccum`，这个名字来自另一批共享同一 offset（100/108）的 CEff 任务模板类（`cluster: xxx` 来源），类型没跟着改成 float，纯粹因为 offset 数字撞车被复制过去。已全部 `git restore --staged --worktree` 撤销。

**为什么：** 没有留痕的批量操作绕开了 pal3-pipeline skill 定义的 Step V4（记录证据到 CHANGE_LOG）→ V5（修改+校验）→ V6（提交）流程；`check_annotations.py` 只校验结构合法性（对齐/重叠/JSON 格式），不校验命名语义，所以这批改动能通过校验却仍是垃圾数据——"0 errors PASS" 不等于"标注质量真实提升"。

**何时使用：** 看到 annotation diff 里出现批量、模式化的重命名（尤其是伴随一个从未见过的 source 标记）时，先怀疑是否有证据支撑，不要因为 `check_annotations.py` 通过就默认合法。判断伪语义命名的经验规则：字段名去掉 `m_n`/`m_f`/`m_b` 前缀后剩下的部分如果是十六进制/十进制数字本身（如 `Val70`、`Flag4988`），无论有没有 CHANGE_LOG 引用都要重新核实证据，而不是只看 source 字段"看起来有内容"就采信。

**后续加固**：`check_annotations.py` 已加精确检测（字段名后缀 == 自身 offset 的十六进制/十进制表示），跑出后在 HEAD（`aaf4e6d4c` 等更早的历史 commit）里额外揪出 9 处同类历史遗留问题（`CCBStage.m_bFlag99/9A/9B`、`CCBRoleState.m_bFlag2870`、`CGameData.m_bFlag280/281/282`），说明这个反模式在项目历史上发生过不止一次。这些历史遗留问题**未修复**——按规则改动需要重新走二进制证据核实，不能仅凭"名字像伪语义"就直接改回 `_todo_`，需要用户决定是否要投入核实。检测器目前只覆盖"数字==自身offset"这种可精确验证的情形，是高精度低召回，不能当全量扫描器用。
