---
name: annotation-hook-never-wired
description: .claude/hooks/validate-annotations.py 写好了但从未接入 .claude/settings.json（只有 check-gstack.sh 被挂载），且内部路径常量写的是过期的 pipeline/data/annotations（真实路径是 data/annotations），双重失效导致 annotation 结构校验从未真正拦截过任何写入
type: gotcha
created: 2026-08-29
sources: [session-2026-08-29]
---

`validate-annotations.py` 的 PreToolUse hook 逻辑本身是对的（检查 struct 对齐/重叠/JSON 格式、拦截 Bash 绕过 Edit/Write 直接写 annotations），但 `.claude/settings.json` 里只注册了 `check-gstack.sh`，这个 hook 从未被调用；即使调用，内部 `ANNOTATIONS_PATH = 'pipeline/data/annotations'` 也匹配不上真实路径 `data/annotations`（项目结构变过，hook 没跟着更新）。两个问题已修复（路径改对 + 接入 settings.json 的 `Write|Edit|Bash` matcher）。

**为什么：** 这类"写了但没生效"的防线比"没写"更危险——它给人一种已经有防护的错觉，实际上和没有一样。这也是 `pattern_annotation_batch_rename_no_evidence.md` 提到的批量违规重命名能够被 commit 进 git index 的直接原因之一（虽然那批改动的问题主要是语义层面，结构 hook 本来也拦不住，但至少 JSON 格式/对齐层面的防线应该是生效的）。

**何时使用：** 每次怀疑"这里应该有个门禁在拦"时，不要只看 hook 脚本存不存在，必须验证：(1) `.claude/settings.json` 里确实注册了它 (2) 脚本内部路径常量匹配当前真实目录结构。可以用构造的假 stdin JSON 直接 `cat fake_input.json | python3 .claude/hooks/xxx.py; echo $?` 实测退出码，比读代码更可靠。注意这道 hook 只查结构合法性，不查命名语义质量——语义问题需要另外的检测手段。
