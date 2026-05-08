持续执行 gbengine.dll 二进制对齐迭代，直到所有文件处理完毕。

## 机制

- 游标: `.claude/align_cursor.json` — 记录整体进度
- 迭代日志: `.claude/iterations/NNNN.json` — 每次迭代的详细记录
- 每次迭代处理一个文件，完成后更新游标 + 写入迭代日志

## 游标格式

```json
{
  "current_file": "当前正在处理的文件名",
  "completed": ["已完成的文件列表"],
  "skipped": ["跳过的文件"],
  "iteration_count": 42,
  "stats": {
    "total_exact": 506,
    "total_equiv": 0,
    "total_functions": 952,
    "last_run": "2026-05-08T23:30:00"
  }
}
```

## 迭代日志格式

每次迭代结束时写入 `.claude/iterations/NNNN.json`:

```json
{
  "iteration": 1,
  "timestamp_start": "2026-05-08T23:30:00",
  "timestamp_end": "2026-05-08T23:45:00",
  "duration_minutes": 15,
  "file": "gbCamera.cpp",
  "before": { "exact": 26, "total": 53 },
  "after": { "exact": 29, "total": 53 },
  "changes": [
    {
      "function": "gbCamera::ClipOBBox",
      "action": "implemented",
      "result": "exact",
      "note": "从 IDA JSON 实现，Size MISMATCH → 100%"
    },
    {
      "function": "gbCamera::GetRayToScreen",
      "action": "implemented",
      "result": "equiv",
      "note": "实现完成，寄存器分配差异"
    },
    {
      "function": "gbCamera::PointEyeToScr",
      "action": "fixed_logic",
      "result": "exact",
      "note": "修正 float 转换顺序，匹配率 15% → 100%"
    }
  ],
  "new_files": ["include/gbengine/gbengine_constants.h"],
  "quality_issues_fixed": 3,
  "compile_status": "PASS",
  "commit_hash": "abc1234",
  "summary": "gbCamera.cpp: 26/53 → 29/53 exact (+3), 实现2个stub, 修正1个逻辑错误"
}
```

### changes 中 action 的取值

| action | 含义 |
|--------|------|
| `implemented` | 从 stub 实现了完整函数 |
| `fixed_logic` | 修正了逻辑错误（控制流/常量/调用） |
| `fixed_quality` | 质量优化（消除偏移/魔数）且未破坏匹配 |
| `skipped_equiv` | 审查后确认为等价匹配，无需修正 |
| `skipped_no_data` | 无 IDA 数据，无法实现 |

### changes 中 result 的取值

| result | 含义 |
|--------|------|
| `exact` | 100% 字节匹配 |
| `equiv` | 等价匹配（仅寄存器/布局差异） |
| `improved` | 匹配率上升但未达 exact/equiv |
| `unchanged` | 未能改善 |

## 主循环

```
while (有未处理的文件):
    1. 读取游标
    2. 记录开始时间
    3. 选择下一个文件
    4. 执行 /align 完整逻辑 (match → quality → verify → commit+push)
    5. 记录结束时间 + 收集变更信息
    6. 写入迭代日志 (.claude/iterations/NNNN.json)
    7. 更新游标 (iteration_count++, stats, completed/skipped)
    8. 输出迭代摘要
    9. 继续下一个
```

## 文件选择优先级

扫描 `src/gbengine/*.cpp`，排除 completed + skipped:
1. 有 Size MISMATCH 的（有 stub 可填充）
2. 函数少的（快速完成）
3. 匹配率高但未满的（接近完成）

## 每个文件的处理（/align 逻辑）

**Phase 1 - Match:**
- 字节对比，记录 before 状态
- 实现 stub（Size MISMATCH，从 IDA JSON）
- 修正逻辑错误（Size OK 但不匹配）
- 等价的跳过并记录
- 编译验证

**Phase 2 - Quality:**
- 消除裸偏移 → 结构体成员
- 消除魔数 → 命名常量/sizeof
- 消除 vtable hack → 虚函数声明

**Phase 3 - Verify:**
- 重新字节对比，记录 after 状态
- 确认匹配率 >= Phase 1 结束时
- 如有下降则回退质量修改

**Phase 4 - Commit:**
- git add + commit + push
- commit message: `feat(gbengine): align <文件> — X/N exact`
- 记录 commit hash

## 迭代结束时输出

每次迭代完成后打印摘要:
```
═══ Iteration #42 完成 ═══
文件: gbCamera.cpp
用时: 15 分钟
匹配: 26/53 → 29/53 exact (+3)
变更:
  + gbCamera::ClipOBBox — implemented → exact
  + gbCamera::GetRayToScreen — implemented → equiv
  * gbCamera::PointEyeToScr — fixed_logic → exact
  ~ gbCamera::Update — skipped_equiv
质量: 3 issues fixed
提交: abc1234
═══════════════════════════
```

## 文件完成标准

- 所有 Size MISMATCH 已处理
- 所有 Size OK 不匹配的已审查
- 质量验收通过
- 编译通过 + commit + push

## 注意事项

- 每个文件处理完必须 commit + push
- 迭代日志目录 `.claude/iterations/` 不提交到 git
- 修改 header 时先确认其他文件编译不受影响
- 如果上下文快满，在写完迭代日志和游标后安全中断
