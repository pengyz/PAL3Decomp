持续执行 PAL3.exe 反编译迭代，直到 frontier 耗尽或被中断。

## 机制

- 调用图: `asm/pal3/call_graph.json` — BFS 展开的函数调用图
- 游标: `.claude/pal3_cursor.json` — 记录迭代进度
- 迭代日志: `.claude/pal3_iterations/NNNN.json` — 每次迭代详细记录

## 游标格式

```json
{
  "iteration_count": 0,
  "stats": {
    "total_matched": 1,
    "total_compiled": 0,
    "total_skipped": 0,
    "last_run": "2026-05-09T12:00:00"
  }
}
```

## 迭代日志格式

每次迭代结束写入 `.claude/pal3_iterations/NNNN.json`:

```json
{
  "iteration": 1,
  "timestamp": "2026-05-09T12:00:00",
  "function": {
    "name": "PAL3::Create",
    "address": "0x00404800",
    "size": 1331
  },
  "result": {
    "judgment": "exact",
    "match_rate": 100.0,
    "source": "src/pal3/PAL3_Create.cpp"
  },
  "build_gate": "PASS",
  "commit_hash": "abc1234",
  "frontier_before": 10,
  "frontier_after": 17,
  "new_callees": 7
}
```

## 主循环

```
while (frontier 非空):
    1. 读取/创建游标
    2. 执行完整 /pal3-step 逻辑:
       - 选择目标 (python tools/pal3_callgraph.py next)
       - 反编译 (读取 decomp JSON → 重写为 C++)
       - 字节对比 (python tools/pal3_compare.py --compile ...)
       - 匹配度门控
       - 质量门控
       - 强检查 (全量编译 + BFS更新 + commit+push)
    3. 写入迭代日志
    4. 更新游标 (iteration_count++, stats)
    5. 输出迭代摘要
    6. 继续下一个
```

## 每次迭代完成后输出

```
═══ PAL3 Iteration #N ═══
函数: <Name> (0x<ADDR>, <SIZE> bytes)
匹配: <judgment> (<rate>%)
构建: PASS
推送: origin/master <hash>
Frontier: <before> → <after> (+<new> callees)
═══════════════════════════════
```

## 门控规则

### 匹配度门控

| 结果 | 判定 | 后续动作 |
|------|------|----------|
| **exact** (100%) | ✅ 通过 | 标记 matched，展开 callees |
| **equiv** (≥95%, 大小相同) | ✅ 通过 | 标记 compiled，展开 callees |
| **≥90%, 大小相同** | ⚠️ 条件通过 | 标记 wip，展开 callees |
| **<90% 或 Size MISMATCH** | ❌ 不通过 | 标记 wip，尝试修正(最多3轮)，仍失败则跳过 |
| **无 decomp** | ⏭️ 跳过 | 标记 skipped，仍展开 callees |
| **编译失败** | ❌ 不通过 | 尝试修正(最多3轮)，仍失败则标记 blocked |

### 质量门控（硬性要求，不通过不得提交）

匹配通过后、commit 前执行:
1. **禁止 IDA 变量名** — v1/v2/v3... 必须全部替换为语义名称（不影响匹配）
2. **禁止无意义函数名** — 已实现函数禁止使用 `sub_XXXXXX`/`stub_XXXX`，必须根据功能命名
3. **禁止裸偏移** → 结构体成员 `this->m_field`
4. **禁止魔数** → 命名常量/sizeof/enum
5. **gbengine 引用使用头文件** — 不允许 extern 前向声明 gbengine 导出，必须 #include
6. **源文件路径** — 必须按 PAL3A PDB suggested_source 放置
7. 重新对比确认未破坏匹配（如果破坏则回退质量修改）

### 构建门控

```bash
python tools/pal3_compare.py --compile-all
```

所有 src/pal3/*.cpp 文件编译通过。

## 跳过策略

以下情况标记 skipped 并继续（不阻塞 BFS）:
- `has_decomp=false` — 无反编译数据
- 函数 size ≤ 5 bytes — 太小，可能是 thunk/jump
- 3轮修正仍 <90% 且 size_mismatch — 结构性问题，待后续处理

## 注意事项

- 不要中断，持续运行直到 frontier 耗尽
- 每次迭代必须完成强检查（编译+更新+commit+push）
- 迭代日志和游标不提交到 git
- 修改 header 时确认不破坏其他文件编译
- 优先处理 has_decomp=true 且 is_named=true 的函数
