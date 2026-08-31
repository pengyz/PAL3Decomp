---
name: gotcha-apply-silent-fail-idb-lock
description: MCP/IDA 会话持有 IDB 锁时 cli.py apply 静默失败——cmd_apply 不以非零退出终止 && 链，WARN 行易被 tail 吞掉
type: gotcha
created: 2026-08-31
updated: 2026-08-31
status: active
sources: [session-2026-08-31]
---

**现象**：标注改完跑 `cli.py apply && export && codegen && probe`，全程无报错，但结果完全没变；事后发现 apply 的 log 文件与 IDB 的 mtime 都没动——idat 根本没执行成功。另一变体：`[2] Globals: named=1027/1313` 之类部分计数偏低，或某个 struct 类型/尺寸在 til 里仍是旧值。

**为什么**：三层叠加。
1. IDA 的 `.i64` 是单写者文件——任何还开着的 idb_open MCP 会话（headless worker）都持有锁，之后 `idat -A` 会直接失败。
2. `cli.py:cmd_apply()` 对失败只打印 `-> WARN: non-zero exit`，**不 sys.exit**，所以 `apply && export && ...` 的 `&&` 链照常往下走；export 又把"未更新的 IDB"再导一遍，一切显得正常。
3. 复现排查时用 `| tail -2` 看输出，恰好把 WARN 行截掉，只留 `Next: ...`，看起来像成功。

**何时使用 / 操作规程**：
- 跑 apply 前先 `agent` 侧确认**没有存活的 IDA MCP 会话**（该关的 idb_close 都关了）。
- apply 后必查两样：`ls -la pipeline/ida/_logs/apply_annotations_log.txt original/PAL3.exe.i64`（mtime 应是刚刚）+ 日志里 `[2] Globals` / `[3] Structs` 行。mtime 不动 = 假成功，重跑。
- 想确认 struct 级变更真的进了 IDB：开 MCP 查 til（`tinfo_t.get_named_type` 后看 size/成员名），不要只信 CLI 的 OK 字样。
- 管线级修复方向（未做）：cmd_apply 失败应 sys.exit 非零；idat 前探测 IDB 是否被锁。

**连带教训**：IDB 里 item 的"名字"不是渲染命名的必要条件——codegen 会用 globals.json 的地址→名替换来出 `g_palScript` 这类名字；Hex-Rays 渲染质量取决于 item 上挂的**类型**。查"为什么代码里是 stru_XXXX"时先分清是 IDB 名字问题还是 codegen 替换问题。
