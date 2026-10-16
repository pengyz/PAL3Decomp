# gotcha：idalib（idapro MCP）与 idat（管线）抢锁同一 IDB —— apply 静默 EXIT=4

**type**: gotcha · **2026-10-16** 实测（PAL3Decomp）

## 症状
`pipeline/cli.py apply` 报 `apply FAILED (apply_annotations.py exited non-zero)`，
但 `pipeline/ida/_logs/apply_annotations_log.txt` **内容完整且无 FATAL**（mtime 陈旧）。
直跑 `idat -A -S"apply_annotations.py" original/PAL3.exe.i64` ⇒ **EXIT=4 零输出**；
换成最小探针脚本（写文件+qexit(0)）**同样 EXIT=4 且脚本根本没执行**。

## 根因
**idalib（idapro MCP supervisor 的 worker）与 idat 争用同一 `original/PAL3.exe.i64`**：
MCP 的 `idb_open` 会话持有 IDB 文件锁（worker 常驻）⇒ 后续任何 `idat` 打开同一 IDB
即静默失败（IDA 退出码 4，无输出、脚本不执行、日志不刷新）。

## 定位手法（两步）
1. `stat` 日志 mtime：**未刷新** ⇒ 脚本没跑（不是脚本逻辑问题）
2. 最小探针脚本（`idc.qexit(0)` + 写标记文件）复现 EXIT=4 ⇒ 锁定为 **IDA 启动层**
3. `ps aux | grep idalib` 发现 `ida_pro_mcp.idalib_server` worker 持有 ⇒ kill 后 idat 立即正常

## 修复/预防
- **用完 MCP 会话后**（或跑管线前）结束 idalib worker：
  `ps aux | grep idalib_server` → `kill <pid>`（supervisor 会在下次 idb_open 时按需重启 worker）
- 病灶层三问修正：EXIT=4 ≠ `s_fail`（apply_annotations.py 的 qexit(4) 分支会先写日志
  `[FATAL] N struct(s) failed`；本例日志无该行 ⇒ 不是脚本分支，是 IDA 启动失败）
- 长期方向：idapro MCP 改用 **IDB 副本**（copy-on-open）与管线物理隔离

## 同型风险
R14（data/status/_d1_ledger.md：管线持有 IDB 期间不得并发 idat）的**镜像形态**：
MCP 持有 IDB 期间不得跑管线。二者共享同一把文件锁。
