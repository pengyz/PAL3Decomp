# Codegen Snapshots

每次 `codegen all` 运行时自动保存快照，保留最近 3 次。

每个快照包含：
- `decomp_summary.json`: export 数据摘要（函数数、总行数）
- `compile_result.json`: 编译结果（errors, pass, failed, top errors）
- `src_hash.txt`: 生成代码的 hash（用于 diff）
- `errors_by_file.txt`: 每文件错误数

比较命令：`python pipeline/snapshots/compare.py`
