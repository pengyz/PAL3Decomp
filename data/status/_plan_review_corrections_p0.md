# 方案复核中期警报修正台账（2026-09-27，acfd56b8 P0-1/P0-2；编排者独立复验 ✓）

## P0-1 我方 S1-3 "Array 小件吞邻"**不成立** —— 撤回（编排者复验 ✓）
- 二进制实证：`Array::Size @0x4111C0` = `mov eax,[ecx+4]; mov ecx,[ecx+8]; sub; imul 0x2AAAAAAB`
  （÷12 元素步长）；`mov ecx,0xC04350; call 0x4111C0`（@0x4095AD）等 4 件均以自身基址物化 this。
- ⇒ +4/+8/+0xC 是 **Array 自身 begin/end/cap 字段**；"被吞邻接全局"（g_RoleTeam1/arr/
  g_nSceneMode/g_nSceneState_0 等 12 个）是**字段被误登记为独立全局**（方向与我原判相反）。
- **W2 修正**：删除"Array 件 binary_size 收缩"（=删真成员）；改为"12 个伪独立全局恢复为
  Array 字段视图/退役独立 extern"（与 W3 同类）。S3 明细"Array 件 12"改注为该方向。

## P0-2 方案漏掉幻影容器的**最大活体层**：ida_structs.json _globals 的串名容器实例（编排者复验 ✓）
- `asm/pal3/ida_structs.json _globals`（2613 条）中 **11 个串字面量/unk 名被登记为容器实例**：
  aShock/aMeteor/aGrid/aModel/pEffMgr = CEffMgr；aBink/aCallback/pTarget = RenderTarget2；
  aExplosive = CEffectSystem；aQuad = CEffModel；unk_C05F30 = CCBStage(673988)。
  全部位于 0x5D548C..0x5D54F8 串表区（幻影 g_EffMgr 声称区间内）。
- codegen 真正吃的容器表是 `store.struct_instances`（pipeline/gen/data.py:166-188，源自
  ida_structs.json _globals + 类型 size）；stage4 `_try_struct_member_resolution`
  （stage4_substitution.py:207-232）按"落在区间⇒成员"消费 ⇒ 实测 1306 条 globals.json
  有 9 条被解析进 aShock/aModel/aMeteor/aExplosive/pEffMgr。
- **W1/W2 修正**：裁定门与清理批必须把 **ida_structs.json 的 _globals/size 层**纳入
  （只清 data/annotations/structs/*.json 清不掉这一层，幻影成员路径照旧生成）。

## 数字对账（复核复算结论）
- 精确复算 ✓：auto:overlap 37（16/12/5/2/2）· 键谱系 dec 9745/hex 51/N_N 4 · _gap_ 1673 ·
  S3 明细逐项（CEffMgr169/SceneMgr40/RoleSystem16/SSD12/PAL312/gbGfxDriverInfo11/Array12）·
  S4 幻影方向 29 条（复放 34 中恰 29 = 严格 auto:overlap/global_analysis 子集）✓。
- 不自洽项（终报后修）：S3 头号 288 vs 明细和 298 vs 复核复算 300（我方探针按
  "structs/{type}.json 存在"过滤，漏 g_CPKPackFiles 19 等无 struct 文件容器）；
  S4 的 45/26 未能复算（口径：other_src 桶的归类边界）。

## 处置
1. 本台账先行固化（事实层）；`_systemic_audit_and_fix_plan.md` 的对应措辞待 acfd56b8
   终报（含修订措辞）到后**一并修订**（现编辑会违反在读不改纪律）；
2. W2 任务描述两处方向性修改（P0-1/P0-2）**立即生效**，后续实施以本台账为准；
3. 288 口径统一为"探针口径=288（struct 文件过滤）/全口径≈300（含 CPK 等）"，终报后定稿。
