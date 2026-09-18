---
name: gotcha-codegen-output-path-not-anchored-to-project-root
description: 输出路径由 store.project_root / PIPELINE_ROOT.parent 决定，而 pipeline.toml 里的 annotations/decomp/pdb 是绝对路径 ⇒ 在别的目录（如 git worktree）里跑 codegen，会去写主仓库的 pal3/src
type: gotcha
created: 2026-09-18
updated: 2026-09-18
status: active
sources: [session-2026-09-18]
---

**现象**：为了做 A-B-A（同一份 `asm/pal3/decomp` 输入，用「落地前」与「落地后」两套 pipeline 各生成一棵树
再逐文件 diff），我建了一个 `git worktree add /tmp/pal3_pre HEAD`（分离头指针，非破坏性），
把 gitignored 的 `asm/` 与 `pipeline.toml` 拷进去，在 worktree 里跑 `python3 pipeline/gen/codegen.py all`。
结果是：**worktree 的 `pal3/src` 里只有 751 个 `.h`（+ `globals.cpp`），而那 201 个 `.cpp` 写到了主仓库**，
把主仓库刚验证完的落地态覆盖成了 pre-state（`Rotate(v10,  v15)` 退回 `Rotate(v10,  *v15)`）。

**为什么**：输出目录和输入目录用了**两套互不相干的路径解析**：

| 位置 | 解析方式 | worktree 里解析成 |
|---|---|---|
| `pipeline/config.py` `PROJECT_ROOT` | `_find_project_root()`：从 `config.py` 向上找 `pipeline.toml` | worktree（我拷了 toml） |
| `emit_headers.py:117` | `PROJECT_ROOT = PIPELINE_ROOT.parent` | worktree |
| `emit_cpp.py:486` | `output_dir = store.project_root / "pal3" / "src"` | **主仓库** |
| `pipeline.toml` 的 `annotations` / `decomp` / `pdb` | 本机就是**绝对路径**（指向主仓库） | 主仓库（恰好是想要的） |

`store.project_root` 与 `pipeline.toml` 的 `output_src`（`"pal3/src"`，相对）**不是同一个来源**，
所以 header 与 cpp 会落到不同地方；而 `pipeline.toml` 本身是 **gitignored** 的
（worktree 默认没有它 ⇒ 第一次直接 `ConfigError`，报 `output_src = "src/pal3"` 的示例值）。

**危险点**：`codegen.py` 的 `cmd_clean()` 是 `shutil.rmtree(pal3/src)` ——
所以这个路径错位不是"多写一份"，而是**先删掉目标树再重建**：主仓库的落地态被无声替换，
任何"我上一轮验证过"的记忆都随之失效（且 `pal3/src` 被 gitignore，`git status` 看不见）。

**规避**：

1. **不要用 `git worktree` 做本项目的 A-B-A 对照**。要对照就：
   （a）落地前**归档整棵 `pal3/src` 的内容**（不是只存 md5——见
   `gotcha_globals_cpp_nondeterministic_order.md`），或
   （b）给 codegen 一个显式的 `--out-dir`（**目前没有**，这是建议项）。
2. 若一定要在别处跑 pipeline，**先确认** `store.project_root`、`emit_headers.OUTPUT_DIR`、
   `cfg.output_src` 三者指向同一处，并在 `cmd_clean()` 之前检查它没指向主仓库。
3. 判别信号：跑完 codegen 后，如果目标目录里 `.h` 数量对而 `.cpp` 数量不对（例如 1 个），
   就是打到了别处——立刻停下，不要去"重跑一遍"，先找 `.cpp` 去了哪里。

（本轮已恢复：重新在**主仓库**跑 `codegen all` 回到落地态，并用被覆盖的那棵树正好等于
pre-state 这一点补回了内容快照，30 个文件的 A-B-A 内容 diff 仍然拿到。
`codegen all` 对相同输入是确定性的，`globals.cpp` 行序除外。）