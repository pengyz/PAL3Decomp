# 基线权威单一化（② P2——2026-10-07）

## 现状（三方基线——无单一权威）
| 基线 | 内容 | 更新点 |
|---|---|---|
| compile_baseline.json | ok/fail 快照 | codegen 后 |
| baselines/latest.json | (code,msg) 多重集 | probe 后 |
| s4_baseline.json | L1/partial | match 后（棘轮回写）|

## 单一权威方案
**baselines/latest.json = 权威**（(code,msg) 多重集——最全判据）：
- compile_baseline=派生（ok/fail 子集——快照闸）
- s4_baseline=派生（L1/partial——match 闸）
- **规则**：权威=latest.json·派生基线只读不写（棘轮回写仅限 s4 的 L1 前进）

## 防漂移
1. 三方基线一致性检查（check_annotations 扩）
2. 棘轮回写的显式 `--rebaseline`（带理由）
3. 基线 diff 的变更记录（CHANGE_LOG）

## 待办
- [ ] baselines/latest.json 的权威标注
- [ ] 派生基线的只读化（compile_baseline/s4_baseline 的写入点审计）
- [ ] 一致性检查接线（check_annotations）
