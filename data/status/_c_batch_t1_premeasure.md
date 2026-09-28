# C 批 T1 信号预实测（2026-09-27，只读探针，R6 定谳依据）

问题：C1 成员化的 263/129 个缺口偏移，其宽度/类型证据是 T1（绝对地址承载）还是
必须等 T1b（this+disp32）？_b_batch_premeasure 的"CEffMgr 访问全是 [reg+disp32]"
说的是**既有 known_members**；缺口是**带名 extern**（数据对象形态），须独立实测。

方法：tools/type_evidence.py（现版）scan_t1 扫 census B2 行的 extern VA 并集，
decomp 函数区间线性反汇编边界表（342,417 条指令边界）过滤。

## 读数
| 容器 | 缺口 | T1 有承载 | 仅裸命中(歧义/未解码) | 宽度信号 | 浮点族偏移 | 1B 偏移 | 2B 偏移 |
|---|---|---|---|---|---|---|---|
| g_EffMgr | 263 | **197 (75%)** | 17 | 4B×177 · 1B×7 | 0 | 2 | 0 |
| g_SceneMgr | 129 | **120 (93%)** | 23 | 4B×292 · 1B×27 | 11 | 7 | 0 |

## 裁定（R6）
- **T1b 不是 C1 前置**：75–93% 的缺口成员有 T1 直接宽度证据（extern 被绝对地址引用，
  与 tagEffMgrData 93/93 的数据对象信号地图一致）。
- 残余（g_EffMgr ~49 零信号 + 17 裸命中 / g_SceneMgr ~9 + 23）走三形态工具
  （audit_member_semantics.py）兜底或**诚实不填**（降 B8/padding）。
- T1b 仍是既有方法型成员（W 工作集 ~70% 盲区）的后续扩展，不影响 C 批。
- 11 个 SceneMgr 浮点族偏移 ⇒ 走 B 批分级（float 填充需 ≥2 浮点站点或单站点 B 级报告）。

## 备注
- 本探针复用现版 type_evidence（读取式调用，未改受审文件）；填充批次可直接用
  `--write` 产守卫批次（type_change/add_member）。
- g_EffMgr 浮点族 0：效果管理器内部是 int/指针/字节主导（与 C 批命名预期一致）。
