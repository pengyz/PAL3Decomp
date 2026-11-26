---
name: commit-isolation-under-shared-worktree
description: 共享工作树的 pre-commit check 读整棵树而非暂存区；被他人未验收改动挡下时，先四分类、只逐文件暂存本卡已验收文件，红源不在本卡就撤回暂存，禁用 -A/commit -a/--no-verify
type: pattern
created: 2026-11-26
sources: [session-2026-11-26, pipeline/hooks/pre-commit, pipeline/check_annotations.py, 7f9d6a636..9f4436c2b]
---

# pattern：共享工作树下只提交本卡已验收改动

pre-commit 的 `check` 读**当前工作树**的注解目录，不读 `git index`。多人共用同一棵工作树时，它会把别人未验收的改动一起判红；只 `git add` 本卡文件，并不能让红消失。

**为什么：** 门禁要阻止任何新增违规进入历史；共享工作树下“要提交的暂存面”和“门禁看到的工作树”不是同一个集合，红可能来自别人的半成品。

**何时使用：** 多个 agent 共用一个 worktree，pre-commit 红了但错误行里没有本卡文件；准备提交注解、测试或文档之前。

类型选 **pattern** 而不是 gotcha：主体是可照做的提交流程，坑只放在“现象”和“禁止项”两节里。

## 1. 现象：pre-commit 红了，但不是本卡坏

2026-11-26 23:39，工作树里 #6/#8 的改动已验收但未提交，#19 的 ScreenEffectMgr 改动仍在进行。此时跑 `check`，`/tmp/r4/chk1.log`（23:39，26,026B）末尾是：

```text
15 new errors + 37 frozen (advisory), 111 warnings — FAIL (新增违规阻断)
```

15 条新增错误全部落在 #19 的类上，例如 `CANON:C1:ScreenEffectRingNode 6/15 槽缺name`、`CANON:C8:~ScreenEffectMgr orphan_family`、`DATA:N13a:ScreenEffectMgr::m_particleEffect`；没有一条提到 RoleStatePanel、UIFrameContainer 或 stage5。HEAD 仍停在 `9f4436c2b`，`git log 9f4436c2b..HEAD` 为空，说明这次提交没有落库。

同一条命令在 00:12 重跑却是 `0 new errors + 37 frozen, 110 warnings — PASS`。阻断是**时间窗状态**，不是本卡的永久结论；既不能把它当成本卡退化，也不能拿一次绿当永久通过。

机制在代码里：

- `.git/hooks/pre-commit` 是 `pipeline/hooks/pre-commit` 的符号链接；后者 `:12` 执行 `PYTHONUTF8=1 exec python pipeline/cli.py check`。
- `pipeline/check_annotations.py:94` 的 `load_annotations(struct_dir=None)` 默认读注解目录（`:237` 以 `_struct_dir` 调起），不是读 index。
- `:2540-2549` 把**全部** errors 与 `data/status/check_baseline_errors.json` 比对，得到 `_new_errors`；没有“只检查暂存文件”的分支。

所以：**check 红 ≠ 本卡坏；check 绿 ≠ 全链通过**（check 只查注解契约，不代替 codegen/probe/match）。

## 2. 先分四类，再决定暂存谁

| 类型 | 怎么认 | 2026-11-26 实例 | 动作 |
|---|---|---|---|
| 本卡已验收未提交 | task 为 done 且 QA 已接受；路径在本卡 `writeScopes`；`git status` 为 `M`/`??` | #6/#8 的 `RoleStatePanel.json`、`UIFrameContainer.json`、`stage5_fixup.py`、两个新测试 | 只暂存这些，过 check 后提交 |
| 他人未验收在改 | 别的 task 仍 in_progress；路径在对方 `writeScopes`；mtime 很新 | `#19`（`tsk_01M8C7D2YHYXXVKFWFK0VD`）的 `ScreenEffectMgr.json`、`ScreenEffectRingNode.json`、`PAL3VisNode.json`、`functions.json` | 不暂存、不提交；等对方验收或清理 |
| loop 刷新产物 | 固定写点、时间戳随 loop 变；常为 `M` 或 `??` | `probe_census.json`、`asm/pal3/ida_structs.json`、`s4_baseline.json`、`s4_diff_detail.json`、`pal3/src` | 永不作为本卡提交面 |
| 无关改动 | 不在任何在跑卡 `writeScopes`；文档、第三方、历史归档等 | `README.md`、thirdparty、别的 handoff | 不暂存；不要顺手清理 |

把“文件属于谁”落到命令上：

```bash
git status --porcelain=v1      # XY：X=暂存区，Y=工作树；M =已暂存， M=未暂存，??=未跟踪
git diff --cached --name-only  # 只看暂存区
git diff --name-only           # 只看未暂存的已跟踪文件
git diff --stat                # 看改动规模，辅助判断是不是 loop 产物
```

然后拿输出逐条对照本卡 `writeScopes`；对不上的一律不 `add`。

## 3. 正确顺序

```bash
# 0. 确认 task 已 done、QA 已接受，记下 writeScopes
# 1. 暂存区必须是空的；有别人的就先按路径撤，不要整片撤
git diff --cached --name-only

# 2. 只逐文件 add，禁止 -A / .
git add data/annotations/structs/RoleStatePanel.json \
        data/annotations/structs/UIFrameContainer.json \
        pipeline/gen/stages/stage5_fixup.py

# 3. 核对暂存面恰好等于本卡文件
git diff --cached --name-only
git diff --cached --stat

# 4. 挑一个没有 loop 在写的窗口，再跑门禁
pgrep -af 'pipeline/cli.py (loop|codegen|probe|match)' || true
PYTHONUTF8=1 python pipeline/cli.py check
```

- **PASS**：`git commit -m '<本卡说明>'`，随后 `git show --stat --oneline HEAD` 确认提交面只有本卡文件。
- **FAIL 且错误类名不在本卡文件里**：`git restore --staged <本卡文件...>` 撤回暂存，**不提交**；把失败摘要和阻塞 task id 发给主理人，等对方验收/清理后重跑。
- **FAIL 且错误就在本卡文件里**：修本卡，修完从第 1 步重来；不要用 `--no-verify`。

撤回暂存只撤自己刚 add 的路径；`git restore --staged .` 会把别人暂存的东西一起撤掉，不能用来图省事。

## 4. 禁止项

| 禁止 | 后果 |
|---|---|
| `git add -A` / `git add .` | 把 #19 的半成品、loop 产物、无关文档一起带进暂存面 |
| `git commit -a` | 绕过“逐文件确认”，等价于全量混提 |
| `git commit --no-verify` | 别人的未验收违规会以你的提交进入历史，门禁失去意义 |
| 暂存 `probe_census.json`、`ida_structs.json`、`s4_baseline.json`、`pal3/src` | 把时间窗读数当成本卡成果，下一轮 loop 立刻覆盖 |
| `git restore --staged .` | 可能撤掉别人已暂存的改动 |
| 对别人的文件 `git checkout --` / `git restore` | 直接丢别人的工作 |
| 把“已验收”写成“已生效/已提交” | 验收、提交、生效是三种不同状态 |
| 用 check 绿宣称全链通过 | check 只查注解契约，不跑 codegen/probe/match |

## 5. 并发 loop 的交互

`loop` 是单通道 `apply → export → codegen → probe → match`，固定写 `asm/pal3/ida_structs.json`、`pal3/src`、`data/status/probe_census.json`、`s4_baseline.json`、`s4_diff_detail.json`、`s4_l1_identity_cur.json`。2026-11-26 深夜这些文件的 mtime 在 00:03–00:09 之间跳动，就是 loop 在刷新的痕迹。

提交前至少看一眼：

```bash
pgrep -af 'pipeline/cli.py (loop|codegen|probe|match)' || true
stat -c '%y %n' asm/pal3/ida_structs.json data/status/probe_census.json data/status/s4_baseline.json
grep -o '"generated_at": "[^"]*"' data/status/probe_census.json | head -1
```

有 loop 在跑时，不要提交任何生成物；只提交注解/测试也要意识到 check 可能读到别人的中间态，宁可等窗口。loop 读数被污染的完整判据见 [`gotcha_loop_reading_contamination.md`](gotcha_loop_reading_contamination.md)。

## 6. 当天两次对照：R5 干净提交 vs #6/#8 被 #19 挡住

| 对照 | R5（成功） | #6/#8（被挡） |
|---|---|---|
| 卡状态 | 已验收，按卡提交 | #6/#8 已验收；#19 仍 in_progress |
| 提交面 | 六提交 `7f9d6a636` 21:49 → `9f4436c2b` 23:37，全部在 `origin/master` | 暂存区复核为空；改动仍在工作树 |
| 门禁 | 六提交均已落库，HEAD 正常前进（commit 记录可复核） | 23:39 `15 new errors` 全属 #19，FAIL |
| 结果 | 六提交已推送，`git branch -r --contains 9f4436c2b` 见 `origin/master` | 撤回暂存，HEAD 停在 `9f4436c2b`，未产生提交 |

这次被挡下后没有产生提交、HEAD 也未前进，正是“撤回暂存、不提交、等阻塞卡”的处置结果。R5 的命令与时间可用 `git log --reverse e4378a1c4..9f4436c2b` 复核；#6/#8 的失败摘要可用 `/tmp/r4/chk1.log` 复核（临时日志，仅作现场指针）。两次的差别不在命令，而在同一个注解目录里有没有别人未验收的 WIP。

## 7. 一页清单

提交前 8 项：

1. task 已 done，QA 已接受。
2. 已抄下本卡 `writeScopes`。
3. `git diff --cached --name-only` 为空，或只剩本卡文件。
4. 只按路径 `git add`，没有 `-A`/`.`。
5. 暂存面逐项等于本卡文件。
6. 没有 loop 在写生成物。
7. `check` PASS；若红，错误类名已逐条对照本卡文件。
8. 提交后 `git show --stat` 只列本卡文件。

失败后 4 步：

1. 看 `git diff --cached --name-only`，确认混入了谁。
2. 在失败日志里找第一条 `ERROR`，记下类名/文件。
3. 类名不在本卡 → `git restore --staged <本卡文件>`，不提交，报阻塞 task id。
4. 等阻塞卡验收/清理后，从“干净窗口 check”重来。

## 8. 引用

- `pipeline/hooks/pre-commit:12` — 门禁入口。
- `pipeline/check_annotations.py:94`、`:237`、`:2540-2549` — 读整棵工作树注解、与基线比对。
- `docs/knowledge/gotcha_loop_reading_contamination.md` — 并发/陈旧 loop 读数的完整判据。
- `docs/knowledge/README.md:69-98` — 知识条目格式与索引流程。
- task `tsk_01M8BYKHXM15J0SRFP2F57`（#8）、`tsk_01M8BX8WS2XASCCC5Z9VXV`（#6）、`tsk_01M8C7D2YHYXXVKFWFK0VD`（#19，in_progress）；R5 范围 `e4378a1c4..9f4436c2b`。
