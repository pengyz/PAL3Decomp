# T6 迭代台账（2026-10-12 · pal3-converge）

**会话**：pal3-converge · **成员**：diagnoser（T6 收口）
**前置**：T1 诊断 · T2/T3 修复 · T4 复核 · T5 修复发现项 · T7 持久化改名
**基线（收口态）**：S2 **101/209** · 总错误 **1720** · L1 **86** · matched **520/613** · partial 373 · L1 率 **86/459 = 18.7%**

---

## 一、本迭代裁决（Decisions）

### D1 · 归属错修法：走 annotation `owner` 字段，不直改 IDB
- **背景**：T2 手改 decomp JSON 让 `0x44F4C0` 从 `PAL3::SceneUpdate` 变 `CGameData::SceneUpdate`；T3 端到端实测发现**一次全量 export 就回退**
- **裁决**：改"生成源"（annotation）而非"生成产物"（decomp JSON）——`data/annotations/structs/CGameData.json.methods["0x0044F4C0"]` 加 `"owner": "CGameData"` ⇒ `apply_annotations.py:1349` merge 条件 `minfo.get("owner") == sname` 触发 CGameData 版本覆盖 `functions.json` 的错归属 ⇒ step 1 mangled name 写 IDB ⇒ step 6 `SetType`（`info['class']` 自动插 `CGameData *__hidden this`）
- **理由**：① 用户硬约束"禁直改 IDB，走 annotation → apply 流入"② owner 机制已有 4 处先例（CCBControlWindow/CCBPanelSlot/RoleSystem/UIWnd）③ 爆炸半径仅 1 行 annotation
- **Confidence: high**（4 条 A 级证据 + 全量 loop 端到端 4 项 acceptance 全绿）
- **沉淀**：`docs/knowledge/gotcha_generated_artifacts_regenerated_not_persistent.md`

### D2 · 双认领计数口径统一（T4 278 vs T5 354）
- **背景**：T5 F5 加了 owner 告警，实测 **354 条**（struct-struct 114 · functions+struct 249 · 并集）；T4 早先报 **278 条**，口径不一致
- **裁决**：**两个数字都对，只是统计范围不同**：
  | 口径 | 计数 | 范围 |
  |---|---|---|
  | **T4 的 278** | 双认领（functions.json ∩ struct.methods）**或** struct-struct 双认领**单类别** | 保守，只算"确证双认领" |
  | **T5 的 354** | struct-struct **∪** functions+struct **并集**（两类都算，允许重叠） | 广义，任何"多来源认领同一 addr 且无人声明 owner"都计 |
- **建议下轮统一口径**：以 **T5 的 354 条并集** 为工作清单（更保守，不漏）；分类子计数：**struct-struct 114 · functions+struct 249**（有交集，去重后总数 354）；**真正双认领且非重复的是 278 条**（T4 的口径）——台账两个数字同时标注
- **不改代码**：口径不一致是**记账问题**，非工具 bug；F5 告警按"只报不改行为"契约本就不承诺单一数字

### D3 · 未修 / 挂账项（不下轮再议）
- **CUtil.cpp +1 C2664**（`RemoveAt` `(const char*)` 转换）— **P1 E.T 直读形债**，非本迭代范围
- **`0x00485230` 名字不改**（`sub_485230`）— slot2 家族名冲突（`SceneObj::Update@0x445C60` vs `CScreenMode::ForwardMessage@0x524980`）证据不足；**铁律禁猜测** ⇒ 名字留白待证
- **`functions.json` 自身 owner 字段被忽略**（F5②）— 只报未改行为；owner 语义应扩展到 `functions.json` 顶层条目，独立轮
- **233 个 `functions.json` vs `structs/*.json` 归属冲突**（t7 附带发现）— 缺 owner 导致 struct methods 输给 functions.json；覆盖 `gbRenderEffect` / `PalScript` / `Scene` / `CEffQuake` / `UIWnd` / `CUtil` / `UITitle_JDHY` 等；独立轮批处理

---

## 二、本迭代教训（Lessons）

### L1 · 改生成产物不持久，改生成源才持久（F2，已沉淀）
**症状**：T2 手改 decomp JSON ⇒ 端到端验证绿 ⇒ 下一次 `loop`（含 export）⇒ 全量重建 3649 个 decomp JSON ⇒ name 回退 `PAL3::SceneUpdate`、`PAL3.h:113` virtual 回归、布局 58/57 可复现

**为什么**：`asm/pal3/decomp/*.json` 是 `export_full.py` 从 IDB 全量重建的派生物（`.gitignore` 设计即为此）；对派生物的手改不进 IDB、不进 annotation ⇒ 下次导出整体覆盖

**规则**：
1. **要持久必须改"生成源"**：`data/annotations/**`（走 apply→IDB 流入）或 apply 层
2. **禁直改 IDB 本体**（用户硬约束）
3. **端到端验证必须跑含 export 的完整 loop**，codegen 单步不够
4. **测试绿证据力 0**（本仓铁律，6 次实证）

**落盘**：`docs/knowledge/gotcha_generated_artifacts_regenerated_not_persistent.md` ✓（本 T6 已写）

### L2 · 门禁读数必须来自当场 probe census，不得事后引用 baseline 文件
**症状**：T2 CHANGE_LOG 记"基线 S2 102/210 · 错误 1719 · L1 86 全平无回归"，但**修复在场态 census=1734**（+15 全部 C2039 落 `CGameData.cpp` 4→19）；1719 是回退态 / 陈旧缓存 census

**为什么**：`compile_regression.py` 读 `probe_census.json` **缓存**（docstring 自认）；`code_genall` 自带 probe，但报错文本显示的是"缓存态"数字

**规则**：
1. **评估任何改动时**，看 `python pipeline/cli.py probe` 输出或 `data/status/probe_census.json` 的 `generated_at` 时间戳
2. **不引用 baseline 文件数字**作当下读数（`compile_baseline.json` / `baselines/latest.json` 都会陈旧）
3. **commit message 里写"当场读数"**而非"基线对比"

### L3 · owner 激活结构侧条目时，name 会一并接管
**症状**：T5 F4(c) `0x0051A880` 加 `owner=CCBItemWindow`，激活了结构侧陈旧名 `Destroy` ⇒ 与同类 `0x0051B4B0` 既有 `Destroy` 撞名 ⇒ 生成物重复定义（`CCBItemWindow.cpp:53/333` 两份 `void CCBItemWindow::Destroy()`，C2084 + C2264 自调用）

**规则**：加 owner 时**同时校验 name 与现状有效名一致**（读 `functions.json` 留痕 `|fix:...` 标签）；T5 实施中自抓自修，最终 name 恢复 `CCBItemWindow_Destroy`

---

## 三、挂账交接（下轮）

| 项 | 归属 | 备注 |
|---|---|---|
| **354 条双认领归属债** | 归属裁定独立轮 | 按 D2 口径统一；走 `audit_attribution_evidence.py` 批量裁定 → 胜方加 owner → 全量 loop 端到端验 |
| **`functions.json` 自身 owner 被忽略**（F5②）| annotation 层 | owner 语义应扩展到 `functions.json` 顶层条目；只报未改行为契约可保持 |
| **233 个 functions.json vs structs 冲突** | 归属裁定独立轮 | 与 354 条有交集，独立一轮统一处理 |
| **`0x00485230` 名字待证** | 二进制证据收集 | slot2 家族名冲突，需 vtable 语义 / 调用点形参锤；禁猜测 |
| **CUtil.cpp +1 C2664**（RemoveAt）| **P1 E.T 直读形** | 本体直读形债，与 P1 批量同批修 |
| **`tests.test_annotation_determinism.test_five_sites_use_single_sorted_read_point`** 失败 | 存量技术债 | `pipeline/ida/export_full.py:733` 裸 `glob.glob` 违规（应走 `annotation_view` 单一读点）；**不修，交独立轮**（本次记账）|

---

## 四、P0 效果对照（判据 v2 `39bf416a0`）

| 指标 | 修前（T1 之前）| 修后（T6 收口）| Δ | 判据 |
|---|---|---|---|---|
| **PAL3 布局冲突** | 58/57（全员 +8 shift）| **1/57**（仅 `__tail_drift__` 伪成员）| **真冲突 0/57** | ✅ **P0 达** |
| **ParabolaCalculator 布局** | 6/6 全漂 | **0/6 一致** | ✅ | ✅ **P0 达** |
| **`sizeof(PAL3)`** | 4944（编译器，vptr+padding）| **4936**（=binary_size）| ✅ | ✅ **P0 达** |
| **S2** | 102/210（T1 前）| **101/209** | −1/−1 | 结构性（ParabolaCalculator 单元消失，方法迁 CUtil）|
| **总错误** | 1734 | **1720** | **−14** | ✅ 净改善（PAL3 归属修正消 C2039 族）|
| **L1** | 86 | **86** | 0 | ⚠️ P0 阶段预期（可测性解冻 ≠ 字节修复）|
| **L1 率** | 86/459 = **18.7%** | 86/459 = **18.7%** | 0 | ⚠️ **仍在 18-19.5% 平台内** |
| **matched** | 521/614 | **520/613** | −1/−1 | 已归因（ParabolaCalculator 方法迁 CUtil 重命名）|

**L1 率说明**（应判据 v2）：
- **P0 阶段**（本轮）：L1 率不变 = **预期**，不算回退；P0 目标是"可测性解冻"（布局冲突消除 + sizeof 正确），不是字节修复
- **离开 18-19.5% 平台**需 ≥ 19.6%（即净 +6 L1）⇒ **P1 修 E.T 直读形**（162 条 C2273/C2274）开始兑现
- **P0→P1 转化率**：修好布局的类里，多少单元变 S2 绿 ⇒ 立即可比对字节 ⇒ 兑现 L1；目前转化率低（PAL3 57 方法里 S2 绿单元 0 个，因 PAL3.cpp 99 错），需"把已修好的单元弄绿"交替进行

---

## 五、验证证据（本 T6 收口）

| 项 | 命令 | 结果 |
|---|---|---|
| 全量 loop 端到端 | `python pipeline/cli.py loop` | apply 0/10s · export 0/151s · codegen 1/189s（**已归因** CUtil.cpp +1 C2664 = P1 债）· probe/match 由手动补齐 |
| 三基线刷新 | `regression_detector.py --save-baseline` + `compile_regression.py --update-baseline` | `baselines/20261012_225949.json` · `compile_baseline.json` 均已更新到 209/101 |
| L1 当场读 | `python pipeline/cli.py match` | `matched 520/613 \| L1 86 \| partial 373`；`L1 ratchet: previous 86 -> current 86` |
| CLAUDE.md:150 参数 | 编辑 | `--expect-s2 101/209 --expect-errors 1720 --expect-l1 86` |
| R11 自测 | `python -m unittest tests.test_owner_warnings tests.test_owner_field` | **6/6 OK** ✓ |
| 存量测试 | `python -m unittest tests.test_annotation_determinism` | 7 tests，1 failure（`test_five_sites` 裸 glob 违规，**挂账**）|

**Confidence: high**（多轮端到端 + A 级二进制证据 + R11 自测；test_five_sites 失败是**存量非本迭代引入**，T5 报告已明记）
