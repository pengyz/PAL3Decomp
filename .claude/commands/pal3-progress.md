显示 PAL3.exe 反编译工作流的当前进度。

## 输出内容

### 1. 调用图状态

```bash
python tools/pal3_callgraph.py status
```

### 2. 当前 Frontier (前 10 个)

```bash
python tools/pal3_callgraph.py frontier --limit 10
```

### 3. 最近迭代日志

读取 `.claude/pal3_iterations/` 目录，显示最近 5 次迭代摘要:
- 函数名、地址
- 判定结果 (exact/equiv/wip/skipped)
- frontier 变化

### 4. BFS 深度分布

从 `asm/pal3/call_graph.json` 中按 depth 分组统计节点数:
```
Depth 0: 1 nodes (root)
Depth 1: 10 nodes
Depth 2: 35 nodes
...
```

### 5. 门控通过率

从迭代日志统计:
- 编译通过率
- 匹配通过率 (exact + equiv + conditional)
- 质量通过率

### 6. 游标信息

读取 `.claude/pal3_cursor.json` 显示:
- 总迭代次数
- 最后运行时间
- 累计 matched/compiled/skipped

## 格式

```
═══ PAL3.exe Decompilation Progress ═══

Call Graph:
  Nodes: 42 | Matched: 5 | Compiled: 3 | WIP: 2 | Pending: 30 | Skipped: 2
  Completion: 8/42 (19.0%)
  Max depth: 3

Frontier (10/32):
  0x004055D0 PAL3::Update           1531 bytes  depth=1
  0x00405C00 PAL3::Render           1542 bytes  depth=1
  ...

Recent Iterations:
  #5 PAL3::Destroy     exact  100%  frontier +3
  #4 CCBSystem::...    equiv   97%  frontier +5
  #3 sub_5382D0        skip    -    frontier +0
  ...

Depth Distribution:
  0: 1  |  1: 10  |  2: 25  |  3: 6

═══════════════════════════════════════
```
