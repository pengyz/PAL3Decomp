# A 重构方案复核

## 完整性
4 阶段不够，3 硬伤：
1. **直读清单失真**：实测绕过 `annotation_view` 的注解直读 **≥11 处/5 文件**（emit_headers×4(563,781,1427,4322)·stage4×4(2445,2513,2552,2585)·transform:67·stage3:177·ast_transform:337），方案只列 3 处，且 CLAUDE.md 引的 emit_headers:3259 已收敛（陈旧）⇒ 清单须重建。
2. **缺真因阶段**：今日 9 commit 定谳真因 = `_inline_PalScript_m_RoleSlotArray` 在 ida_structs.json 缺失（`_inline_*` 导出不对称），非数据源双写本身 ⇒ 应在 apply/IDA 层补 `_inline_*` UDT；codegen MERGE 仅兜底，export_full:798 直读注解 `_origin` 撞"export 不读 annotation"红线。
3. **缺防回潮闸**：单测仅覆盖 5 文件、只断言调用数 ≥N，pipeline/gen 零闸 ⇒ 修完必再腐；缺回滚判据、MERGE 前双源普查、CLAUDE.md 措辞同步。

## 成本估算
2-3 人月**低估**：阶段 1 实为 3→11 处（×3-4）；每步 P1-5 双验证（match ≥596s+全产物 diff，195 头静默变异）使验证≈编码 ⇒ **3.5-4.5 人月**。"-50% 摩擦"无测度（n=1 外推），回本期悬空（前提：验证提速先行）。

## 迁移路径
渐进可行但**顺序错**：阶段 4 前置 step 0——它是 1-3 的裁判（L1 不降/错误不增），而 S2 三口径并存（128/207·120/214·140/205）裁判未校准。①"三基线数字一致"不成立（L1 异度量+三限定+棘轮回写 ⇒ 当场读输出），改"单一权威口径"；②阶段 2 先出只读双源 diff、逐类开关，勿 MERGE 致 195 头同漂；③methods/known_methods 动 vtable 命名直触字节匹配，须独立字节门。

## 挑刺
- **度量盲区**：C1003 截断令"错误不增"对两单元失明；"C2039 -36"拍脑袋（今日归因含 `_inline_*` 缺失）。
- **撞在飞工作面**：generate_header 1720 行+每日迭代互踩，无分支/冻结约定。
- **数字又一组**：_GB_REF 实测 29/32/交集 28/非对称 5（GetAABBox↔gbOBBox::GetAABBox 疑同函数），方案写 34 = 第 5 组口径。
- **更优**：step 0（1-2 天）双源 diff+扩闸+口径对齐，零风险；阶段 2 逐类 kill-switch；`_inline_*` 走 apply 层，codegen MERGE 记 tombstone 限时退役。

## verdict
**方向对**（分叉确是摩擦源），**现稿漏 8 处直读、真因不闭合 ⇒ 有条件通过**。must-fix：①清单重建+pipeline/gen 扩闸；②apply 层 `_inline_*` 前置阶段 2；③阶段 4 前置、判据改"单一权威口径"；④成本 3.5-4.5 人月+验证提速先行，收益改可测度指标（union 类 bug 平均定位时长）。
