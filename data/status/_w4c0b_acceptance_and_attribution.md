# W4-C0b 验收与 codegen 回归归因（2026-09-27 23:35 codegen all 实测）

## 1. W4-C0b 验收 ✓ 达成
- `pal3/src/Scene/SceneMgr.h:124`：`_gap_C812[54]` → **`char _gap_C810[56]; // +0xC810`**
  （与 c34f38aa 裁定推演逐字吻合：打包 402 ⇒ start_off=0xC810 ⇒ gap[56]）；
- **audit_type_layout --only SceneMgr：167 成员 ✓ 一致，冲突合计 0**（原 1/167 唯一冲突归零）；
- S2 cpp **92/208 不变**（与 12:51 时点同）；新失败 0；3 单元转绿（CCBMagicWindow/UIDialog/InputSystem）。

## 2. 7 条"真新增"归因（对 03:40 陈旧基线；非 W4-C0b 所致）
逐条来源：**全局双声明族**——`data/annotations/globals.json` 4 条 `LPCSTR/const LPCSTR`
型 off_* 全局（:144/:256/:1620/:1652）与 TU 侧合成 extern（`_prefix_type` 回退 `char`/cast 形态）
**同名不同型** ⇒ C2040 `'LPCSTR' differs in levels of indirection from 'char'`（25 条净增，
5 单元：LineupUI/UIScenePanel/CGameData/CCBRoleState/RoleShadow）+ C2440 cast 衍生 4；
另 C2065 两条（accessor_00450A30@RoleCameraCtrl、dword_D8C360@PalScript）= 幻影全局跳过
把活代码引用的符号藏掉（forced_global_entries 模式未覆盖）。
因果排除 W4-C0b：①5 个单元的类**均不在** 11 个 inline union 站点/10 类与 2073 同偏移组内；
②错误语义=全局声明/类型，与成员尺寸记账正交；③该族属 03:40→今 retirement 窗口
（cc7f9665a/497f5b33b globals 发射改造）遗产。
处置：**W3 extern 面账目**承接（双声明统一类型源 + forced 模式补 accessor_/dword_ 形态）；
基线刷新（03:40→今）按 W7 棘轮决策走，不在本轮做。

### 2.1 副作用台账订正（复核 695bcbb4 条件①，2026-09-28）
- **L1 63→68 的 +5 = 语料增长非字节收益**：CCBMagicWindow（W4-C0b 窗口转绿）+ UIProgressBar
  （W6 转绿）的新符号入语料；**W2 本批字节贡献=0**（与 HEAD 记录共享 323 行 0/323 变化）。
- **CreateEff@CCBStageCam:1205 = W6 净新增**（未入账副作用）：显式 this 化暴露 Hex-Rays
  参数回收缺口（5 实参 vs 5 形参+this ⇒ 消费 recv 后剩 4）——归 W6 账，待参数回收修。
- **C2371 真新=4 条/3 单元**（非 5；第 5 条是行漂移假象 CCBStage 'Reset' 1119→1120）。
- **7 新全局已在 `_globals`**（此前记录"不在"为读数倒置——检查单原文实为通过）。
- 释放计数勘误：实测 **47**（非 49）：9 statics + 3 既有全局承接 + 12 IDA 结构对象 + 23 模式合成项；
  全部 ≥0xDE8DE8（收缩界之外）⇒ **零误释放**；0x3AC 空洞=纯 gap（无注解无引用）。
- C2040 族实为 **+30/6 单元**（漏计 free_functions）；LPCSTR 疑被当 class 声明而非 typedef（源可疑，W3 一并核）。

## 3. 台账
- W4-C0b 实现复核在飞（6dc45d18）；
- 存量 6 测试失败（ast_transform 域，stash 对照证实 HEAD 存量）挂 W6；
- W4 遗留：check 闸无回滚、4 文件封杀归一化（守卫返工记录 _guard_rework_round1）。
