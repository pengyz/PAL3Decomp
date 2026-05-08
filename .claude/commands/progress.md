查询 gbengine.dll 二进制对齐的整体进展。

遍历 `.claude/iterations/` 下所有迭代日志，汇总整体进展。

## 流程

1. 读取游标 `.claude/align_cursor.json` 获取全局状态
2. 遍历 `.claude/iterations/*.json` 所有迭代日志
3. 汇总统计并输出报告

## 输出格式

```
═══ gbengine.dll 对齐进度 ═══

整体: XXX/952 exact (YY.Y%), ZZZ equiv
完成文件: AA/55
跳过文件: BB/55
剩余文件: CC/55

累计迭代: NN 次
累计用时: HH 小时 MM 分钟
平均每次: MM 分钟

═══ 最近 5 次迭代 ═══

#42 [2026-05-08 23:45] gbCamera.cpp      26→29/53  +3 exact  (abc1234)
#41 [2026-05-08 23:20] gbEffectMgr.cpp   7→7/9     +0        (def5678)
#40 [2026-05-08 22:55] gbActor.cpp       18→20/35  +2 exact  (ghi9012)
...

═══ 按文件汇总 ═══

文件                     函数   Exact  Equiv  剩余  状态
gbGfxManager_D3D.cpp     10     10     0      0     ✓ done
gbEffectMgr.cpp          9      7      2      0     ✓ done
gbActor.cpp              35     20     8      7     进行中
gbCamera.cpp             53     29     12     12    待处理
...

═══ 变更统计 ═══

总计实现函数: XX (从 stub)
总计修正逻辑: YY
总计等价确认: ZZ
总计质量修复: WW

═══ 关键 Commits ═══

abc1234  feat(gbengine): align gbCamera.cpp — 29/53 exact
def5678  feat(gbengine): align gbEffectMgr.cpp — 7/9 exact
...
```

## 数据来源

- 全局状态: `.claude/align_cursor.json`
- 迭代详情: `.claude/iterations/NNNN.json`
- 实时验证（可选）: 对剩余文件跑 `python tools/gbengine_compare.py --compile ... --all` 获取最新数据

## 可选参数

- `/progress` — 完整报告
- `/progress brief` — 仅显示整体数字和最近 3 次迭代
- `/progress <文件名>` — 显示某文件的所有相关迭代历史
