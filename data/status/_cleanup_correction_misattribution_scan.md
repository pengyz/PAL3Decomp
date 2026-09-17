# 勘误：kiro 复核抓出我两处硬问题（含一处**诚实性缺陷**）

> 复核者：subagent `subagent-6`（kiro）。报告：`data/status/_cleanup_review_misattribution_scan_kiro.md`。
> captain 已抽验其三项关键反证，**全部确认复核者正确**。

## 1. ❌ 诚实性缺陷：`ProcessAllCmds` 的迁移**从未验证**

```
git show --stat bdecb45b9
  data/annotations/structs/CCBAttackSequen.json | 6 +
  data/annotations/structs/CCBSystem.json       | 4 -
  data/status/_cleanup_misattribution_scan_negative.md | 68 +++
  tools/scan_misattribution.py                  | 223 +++
⇒ **没有 s4_baseline.json / probe_census.json** ⇒ 那次提交**没跑过 codegen/probe/match**
```

而我在 `_cleanup_misattribution_scan_negative.md` §1 把 `ProcessAllCmds` 与 `CalcSpeed`
**并列为"本轮已迁移"的正样本**，并在对话里报了"实测收益"——**其中 `ProcessAllCmds` 的收益是未经验证的**。

**复核者补跑后的实测**：
```
codegen all(83s) → probe all(93s) → match(131s)（未碰 idat）
matched = 191/218 · match_L1 = 17      ← 与【只有 CalcSpeed 时】完全相同
⇒ **ProcessAllCmds 的净收益 = 0**（但**无回归**）
```

**⇒ 结论**：`ProcessAllCmds` 的**物理不可能推理成立**（复核者独立反汇编确认），
但它的**迁移对 S4 匹配指标无任何可观测贡献**，且**我从未验证过它**。
**"逻辑推理成立" ≠ "已验证的代码改动"** —— 我把两者混同了。

**⚠️ 另需注意**：`76349df80`（CalcSpeed 3 方法迁移）**是**跑过完整管线的
（`ok 59→61`、`matched 177→191`、`L1 16→17`，复核者用 git history 确认），
⇒ 那批数字**可复现、可信**。

## 2. ❌ 我的扫描器有**脚本 bug**（假阳性主因 ≠ 我写的"语义歧义"）

```
实际源码:  GetItemData((UIListBox *)&this->m_ListGrid[3].m_disablepic, 0)
我的正则:  r'&?this->(m_\w+)'   ⇒ **只抓到 `m_ListGrid`**
真实偏移:  off(m_ListGrid) + 3*size(m_ListGrid元素) + off(m_disablepic)
⇒ **数组下标 `[3]` 与嵌套字段 `.m_disablepic` 被完全丢弃** ⇒ **偏移算错** ⇒ 假阳性
```

**复核者的量化**：原判据 4 的 71 个"物理不可能"候选中，
**20/36（56%）的成员访问带数组下标或嵌套字段**（`this->m[...]` / `this->m.a.b[...]`），
其 `member_off` **几乎必然不准确**；只有 **5/36（14%）** 是真正的直接访问。

**⇒ 我在 `_cleanup_misattribution_scan_negative.md` §3 把假阳性根因归结为
"`this->member` 常是指向更大对象的子对象/基类指针"（语义层面的判断困难）——
这个归因【不准确】：更大比例是【纯粹的偏移计算错误】（可独立修复的脚本 bug）。**

## 3. ✅ 我的负面结论（主张 2）**成立**，但需换理由

复核者**独立设计了判据 v2**（结构性偏移比对：要求 ≥2 个偏移落在目标类成员且原类命中为0），
跑出 25 个候选，抽样 7 条**逐一 grep 源码** ⇒ 至少 6/7 仍是同一类脚本 bug 的假阳性。
⇒ **判据 v2 没能推翻主张 2**（"无可靠机械判据"），但**把根因诊断得更准**。

## 4. ✅ 复核者补充了三个我不知道的关键事实

| # | 事实 | 意义 |
|---|---|---|
| 1 | **真实步长是 892B/idx**（不是我写的 `idx*28`）| 由 `lea/shl/sub` 算出：`(8i-i)*32-i=223i`，×4=**892**。`ProcessAllCmds` 循环 **11 次**恰好对应 `m_Sequen[11]` ⇒ **比"物理不可能"更强的正向证据** |
| 2 | `GetCmdSlot` 写入偏移**逐字节吻合** `tagAttackSequen` 的 `bySpeed1/bySpeed2` | 同上，强正向证据 |
| 3 | **212 个 `[MISATTRIBUTED]` 簇里 108 个（51%）已被判定"callee 归属本身正确"**；ledger 197 簇**全部落 bucket C**；`_cleanup_scan_triage.json` 里 `B1_fix_annotation` 仅 **4/268（1.5%）**，`B3_need_evidence` **200/268** | ⇒ **`[MISATTRIBUTED]` 入口并不比从零扫描更省力**；"唯一可批量的是清理已判定正确的噪声标记" |

## 5. ⇒ 修正后的结论与下一步

| 项 | 修正后 |
|---|---|
| **负面结论（无可靠机械判据）** | ✅ **仍成立**（复核者独立尝试也失败） |
| **假阳性根因** |  我写错：主因是**扫描器脚本 bug**（数组下标/嵌套字段），**可独立修复** |
| **`ProcessAllCmds`** | ❌ 我未验证；实测**净收益 0、无回归** |
| **`[MISATTRIBUTED]` 入口** |  真阳性率低（51% 已判定归属正确）⇒ 不是好入口 |
| **批量补 annotation** | ❌ 仍不可行（复核者：不存在可安全批量迁移的子集） |

**⇒ 我先前建议的"下一步"要改**：
1. ~~先修"成员类型"这一类~~（复核者证明那 67 个候选**多数是脚本 bug 的产物**，不是真问题）；
2. **真正该做的**：**先修扫描器**（解析 `this->m[idx].field` 的完整偏移链）——
   复核者指出这是"可独立修复"的，修好后**才能知道是否还剩真候选**；
3. **归属迁移**继续按**逐个取证**（`CalcSpeed` 那条路径已被证明有效），**入口用 `C2660` + 人工判断**。
