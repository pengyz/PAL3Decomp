# A 定向重构方案：统一数据源

**created**: 2026-10-23（架构决策 L1 保持 + A 重构）

## 目标

**消除数据源分叉**（IDA vs 注解）⇒ 减少分支/例外 ⇒ 降调试摩擦

## 病灶（活证据）

**今日 8 commit 追同一「union 双源 bug」**：
- `emit_headers.py` L2266 读 `_get_ida_structs()`（IDA data_members）
- 注解 `known_members`（含 dict-union）在 `_annview.struct_by_class`
- **6 次修尝试未生效** ≈ 1 天/例

## 4 阶段（渐进，禁大爆炸）

### 阶段 1：清 3 处直读（1-2 周）

| 位置 | 现状 | 目标 |
|---|---|---|
| `emit_headers.py:3259` | 直读 `globals.json` | 走 `annotation_view` |
| `ast_transform.py:336` | 直读 `structs/*.json` | 走 `annotation_view` |
| `stage3_cleanup.py:107` | 直读 `structs/<Cls>.json` | 走 `annotation_view` |

**验证**：P1-5 双验证（逻辑等价 + 产物字节 diff + L1 不降 + 总错误不增）

### 阶段 2：结构体数据源统一（2-4 周）

**统一到注解 `known_members`**（含 dict-union）：
- `ann_members` 构造改用 `_annview.struct_by_class`
- 保留 `data_members` 作为 fallback（兼容）
- **MERGE 策略**：dict-union 优先，其他补

**验证**：同上 + C2039 消除（预期 -36 条）

### 阶段 3：逻辑表收敛（1-2 周）

| 表 | 现状 | 目标 |
|---|---|---|
| `_GB_REF_PARAM_FUNCS` | stage3 29 / stage5 34（分叉 5）| 单一表 + 双侧一致性测试 |
| `_MACRO_CONFLICTS` | 双定义（:2822 / :2929）| 单一定义 |
| `methods` vs `known_methods` | 双注册表 | 统一 |

**验证**：双侧一致性测试（键集合相等）

### 阶段 4：三基线归一（1 周）

| 基线 | 现状 | 目标 |
|---|---|---|
| `compile_baseline.json` | S2 120/214 | 统一 |
| `baselines/latest.json` | S2 140/205 | 统一 |
| `s4_baseline.json` | L1=194 | 统一 |

**验证**：三基线数字一致

## 成本/收益

| 项 | 值 |
|---|---|
| **总成本** | **2-3 人月** |
| **预期收益** | 调试摩擦 **-50%**（近 40 commit ~25% 是调试）|
| **回本周期** | **2-3 个月** |

## 迁移路径（渐进，禁大爆炸）

```
阶段 1（直读收尾）→ 阶段 2（数据源统一）→ 阶段 3（逻辑表收敛）→ 阶段 4（基线归一）
每步：P1-5 双验证 + L1 不降 + 总错误不增
```

**禁大爆炸**：`match` 是唯一裁判，每迭代 ≥596s ⇒ 重写期指标盲飞

## 风险

| 风险 | 概率 | 缓解 |
|---|---|---|
| 重构失败 | 中 | 渐进 + P1-5 双验证 |
| L1 不升 | 中 | 再评估触发器（4-6 周 <25% ⇒ 切 T2）|
| gotcha 丢失 | 低 | 114 条 gotcha 是负载行为，重构不动 |

## 再评估触发器

**重构后 4-6 周 L1 < 25%** 或 **oracle 基建就绪** ⇒ 启动 T2-F/VM 差分
