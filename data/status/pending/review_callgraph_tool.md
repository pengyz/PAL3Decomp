# 综合调用图工具复核

## 工具正确性
BFS 方向（WinMain 根向下扩 callees）与根地址正确：IDA 裁决 `_WinMain@16`@0x541900、size=824 ✓。三处致命伤：
1. **边提取错**（:86）：`extract_callees` 抓 decompiled_c 的 `0x` 字面量当 callee，而 Hex-Rays 真实调用是具名语法 `Cls::Method()`。全量实测 3694 个 decomp：抓到 417 个十六进制引用仅 3 个是函数，414 个是常量（`0x7FFFFFFF`×92、`0x40000000`×29…）⇒ 只会生成垃圾节点，一条真实边也抓不到。
2. **BFS 死在根**：WinMain 无 decomp JSON ⇒ expand 报"无新 callees（L0 已到底）"是假到底。真值（IDA xrefs）：WinMain 有 27 个真实 callee（`?Update@PAL3@@QAEXM@Z` 等）。
3. **元信息不全**：根节点类/签名/字节数全 None；`size` 两元数据源均无（0/613、0/3930）⇒ 字节数恒 0，decomp 的 `size_bytes` 未读；180 个 meta 键因大小写不归一不可达（`0x005015c0`≠归一形 `0x005015C0`）；NAMES_PATH 死代码。另 callers 只记首发现者（:135）；expand 只扩 layers[max_depth]，无 decomp 节点永不扩；find_decomp 每节点全目录扫 3694 个 JSON。

## check 功能
**L1 对拍是 no-op**：代码读 s4_baseline 的 `address`/`match_rate`/`diff_bytes`（:256-259），实际 schema 是 `va`/`match_pct`/`status`/`size`，637 行 0 行有 address ⇒ join 恒空。docstring 称"编译→比对字节"，实际不跑 compare_pal3，只读静态基线（CLAUDE.md：该基线被棘轮回写，事后读会陈旧）。量纲错位：match_pct 为 0–100，阈值按 0–1 设计 ⇒ 键修好后人人 done；且 repo L1 是二值"字节全同"（三限定），95% 相似率标 done 违背"字节匹配>一切"。

## 自跑验证
init ✓；expand×2 → "无新 callees（L0 已到底）"（假）；check → "已检查: 0/1"、类聚合空；node → 类/签名/字节数 None。跑前备份状态文件，跑后 sha256 一致还原（8f62c8d9…），未改产品文件。

## 挑刺
- 调用边应取 IDA xrefs（idapro MCP 一条 callees 即得 WinMain 27 边）或 objdump 兜底；仓里 call_graph.json/bfs_callgraph.json 已是两代死根，勿迭代第三版。
- 若用 decomp：应解析具名调用+符号→地址映射，而非抓十六进制字面量。
- check 应改跑 `pipeline/cli.py match` 当场读 `[metric]`（本仓纪律），join 键用 `va`、以 status=='perfect' 判 L1。
- 小 bug：mark 缺 --status 写 None；layer N 非整数 crash；节点名直用 `sub_*`/`_todo_*` 噪声名。

## verdict
**不通过**。方向与根地址对，但边提取、BFS 生长、check 集成三处致命缺陷（均有实测证据）。先以 IDA xrefs 重建边提取、check 接 match 当场输出，再复审。
