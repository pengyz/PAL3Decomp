# Pre-state 归档：2026-09-17 15:49 生成树 + 两份基线产物

**来源**：`/tmp/c2660bak/`（对抗性复核子 agent `bc0a67e9` 第二轮穷尽搜索发现）。
**为什么必须入仓**：这是目前**唯一**的一套"改前"产物集，且原本只在 `/tmp`（会被清理）。
2026-09-17 16:00–20:10 之间**没有任何 census/baseline 产物**
（`data/status/baselines/` 在 Sep-15 23:23 与 Sep-17 20:16 之间为空），
所以缺了它，本会话所有 Δ 声明都只能靠文档、无法做真正的 A-B-A。

## 内容
| 文件 | 说明 |
|---|---|
| `pal3_src_20260917_1549.tar.gz` | 15:49:23 的完整生成树（202 .cpp + 751 .h），解包后可 `diff` 或**独立重编译单文件**（include 指向解包根）|
| `probe_census.json` | 同刻 census（`generated_at 2026-09-17T15:49:23`）：**s1 731/751、s2 56/202** |
| `s4_baseline.json` | 15:52：**L1 16 · matched 170/196 · partial 129 · symbols 196** |
| `s4_baseline_after_calcspeed.json` | 17:22:29：**L1 17 · matched 191/218 · partial 149**，与提交 `76349df80` 内容字节相同 |
| `latest.json` | 15:49 的对账基线 |
| `pal3_registry.jsonl` | 15:49 的注册表 |

## 用法
```bash
tar -xzf data/status/archive/20260917_1549/pal3_src_20260917_1549.tar.gz -C /tmp/pre1549
diff /tmp/pre1549/pal3_src/UI/UIWnd.h pal3/src/UI/UIWnd.h      # 例：改动面核对
```
