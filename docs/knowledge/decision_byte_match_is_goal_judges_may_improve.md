# decision · 字节匹配仍是目标与唯一进度指标；裁判可增、目标不改

**type**: decision
**created**: 2026-10-10
**status**: active
**supersedes**: （无 —— 本决策**不改目标**，故不 supersede `decision_goal_metric_over_proxy_metric.md`）
**related**: `decision_goal_metric_over_proxy_metric.md` · `decision_binary_as_sole_sot_closed_loop.md` · `decision_layout_is_substrate_two_axis_progress.md`

## 一句话
字节匹配仍是**目标和唯一进度指标**；新增裁判（指令对齐差分、重定位目标校验、长期运行时 trace）**只用来定位问题**，不改目标、不改判据。

## 背景（2026-10-10 方法论对抗复核）

四路独立分析（A 方法论对比 / B 困境诊断 / C 迁移可行性 / kiro 最终对抗复核）+ 参考项目 `~/workspace/xiyou_remake`（Nokia J2ME RPG → Rust 重制，像素级一致 + 机器差分裁判）。

**用户提出的问题**：「方法论是否错了？一次性全量导出+纯管线自动化是否错了？是否该换 Rust + harness 对拍做字节一致性检查？」

## 定性结论

**方法论有病，但病灶比「四处硬伤」更精确**：

| # | 病灶 | 证据 |
|---|---|---|
| ① | **目标指标（L1 率）从未收敛** | 09-21 15.0% → 09-25 18.7% → 10-09 **19.1%**，09-25 起停在 18-19.5% 平台；66 个提交里 partial 中位 match_pct 始终 21.7-27.8%，**从未改善** |
| ② | **度量不平稳** | 三基线互斥（`gotcha_three_competing_baselines.md`）· census 非源码纯函数 · 棘轮自损坏史 · **L1 的 25.4% 是重定位通配**（`gbengine_compare.py:258-260` 不校验调用目标）· 18/85 个 L1 非重定位字节 ≤2 个（17 个是 E9 跳板）|
| ③ | **可测性被布局冲突冻结** | `decision_layout_is_substrate_two_axis_progress.md:23` 实测布局冲突覆盖 **1501/3598（42%）** 函数；一次修好 5 个类解锁 140 个函数，**其中只有 2 个能当场测（1.4%）** |
| ④ | **裁判不定层** | 错误信号不区分「注解错 / codegen 错 / Hex-Rays 上限」，只能靠「病灶层检查」人肉补位 |

**⇒ 「持续不收敛」对代理指标（S2/总错误）是假的**（22 天：错误 3876→1492 = −61%、S2 45→108、L1 35→86）**，对目标指标（L1 率）是真的；「不可拆分/项目太大」是借口**（71/108 红单元只差 ≤10 错、中位 6；`fail_imported_only: 0`；102 个绿单元就是逐个拆出来的）。

## 被证伪的方案（诚实记录）

| 方案 | 判决 | 反证 |
|---|---|---|
| **换 Rust + harness 对拍** | ❌ **否决** | 「harness 对拍做**字节**一致性检查」是**范畴错误**（行为判据证不了字节目标）；且 rustc/LLVM **做不到** MSVC6 的名字修饰（`?GetTargetRole@CCBAI@@QAEPAXPAX@Z`）、`__thiscall`/`__stdcall` thunk 形状、vtable 布局+COMDAT 折叠+调整 thunk、寄存器分配、内联、浮点代码生成 ⇒ **换 = 永远 0 字节匹配**。另：OpenPAL3 已是 Rust 重实现（Rust 90.9%），换 = 重做一遍，且丢掉唯一能逐函数验证的产物 |
| **录制型 `gbGfxManager`（29 slot）当裁判** | ❌ **不可执行** | 覆盖面错位：PAL3.exe 经 vptr 调用 29 slot 约 77 处（**51 处是 slot 2 `NewTexture`**），**`DrawIndexedPrimitive` 0 处、`DrawPrimitive` 1 处**；绕过虚表直接访问字段 **135 处**；绘制全在 **gbengine.dll 内部**（PAL3.exe 导入表**无 d3d9.dll**）；且 S2 **102/210 链接不了 ⇒ 判决数 0** |
| **字节匹配降级为 stretch 指标** | ❌ **绕过改目标程序** | 与 `decision_goal_metric_over_proxy_metric.md:42`「唯一进度指标 = match_L1」冲突；且与「不改目标」自相矛盾 |
| **E9 thunk 结构性不可匹配** | ❌ **证伪** | 引的是**第二天就被覆盖的旧结论**（`_completeness_convergence_ledger.md:92-94` 记录「thunk 契约正名 → E9 → L1 兑现，L1 92→94」）；HEAD 里 **17 个 E9 跳板是 L1** |

## 决策

1. **L1 仍是目标和唯一进度指标**（沿用 `decision_goal_metric_over_proxy_metric.md:42`，**不改目标**）
2. **新增裁判只作诊断**，不改判据：
   - **短期**：指令对齐差分（`reccmp` 已支持老 MSVC x86）替代逐位置比对的 `match_pct`（现行 `gbengine_compare.py:255-265` 中间插 1 字节就全错位 ⇒ 指标本身无效）
   - **短期**：重定位目标校验（现行 25.4% 的 L1 字节是重定位通配、不校验调用目标）
   - **长期**：运行时 trace（边界 = **249 个按名导入 + d3d9 层**，非 29 slot）—— 前置：exe 可链接或热替换 harness
3. **优先级重排**（替代「按错误码族排序」）：
   - **P0 解冻可测性** —— 布局冲突（42% 函数受阻）优先于错误码族
   - **P1 修真瓶颈** —— `stage4_substitution.py:483-493` 的 `E.T` 直读形（162 条 C2273/C2274、26 单元）⚠️ **须先过字节裁决**（`_completeness_convergence_ledger.md:33-35` 实锤该改写对非零偏移基类**丢偏移** −72，「须 match 裁决」）
   - **P2 类型坍缩** —— 422 条 ≈ 25%（成员/局部被标成标量或 `void*`），逐站点取证
4. **门禁基线数字须随实况刷新**（2026-10-10 实证：`76/205 · 2140 · 38` 陈旧 3 周恒红 ⇒ 门禁失去判别力；刷三基线后全链 rc=0 + L1 86）

## 应保留的资产（四路一致）

| 资产 | 价值 |
|---|---|
| **注解体系与证据纪律** | A/B/C 证据分级 · disp32 全二进制扫描 · `audit_type_layout`/`audit_member_semantics`/`verify_fix` 工具链 · 「禁止猜测性修改/伪语义命名」⇒ **换任何目标直接复用** |
| **C++ 重建件** | = xiyou 的 **D3 参考版**（「必须存在、永不删除」）⇒ 降为「辅」**违反范例自己最核心的决策** |
| **MSVC6 工具链** | `cmake/toolchain-vc6.cmake` + `wine_cl.sh`，独一份基础设施 |
| **compare_pal3 诚实规则** | unmatched 从不静默丢弃 |
| **知识库/证伪更正文化** | 已外溢到 xiyou（`gates/cli.py:4` 自述「移植自 PAL3Decomp 教训」）|
| **射程化改造** | export 9× / codegen 5.3× / probe-match 射程，方向正确继续走 |

## 程序合规说明

本决策**不改目标**，故不走「改目标」的决策流程（`decision_goal_metric_over_proxy_metric.md` 保持 active）。若未来要改目标，须：
1. owner 明确拍板（AI 合成无权改目标）
2. 新写 decision 文档取代旧的，旧的标 superseded
3. 对 `CLAUDE.md` 做带日期更正
4. 保留 L1 棘轮和全部历史
5. 做方案复核和效果复核

## 一句话总裁决

**字节匹配是目标、L1 是唯一进度指标 —— 两者都不改；要改的是「可测性」（布局冲突 42%）与「裁判精度」（指令对齐差分 + 重定位校验），不是目标本身。**

---

## 附：目标指标陷阱（2026-10-10 Goal Round 13 实测发现）

**实测基线**：L1 = 86 · partial = 374 · **L1 率 = 86/460 = 18.7%**（仍在 18-19.5% 平台内）。
**离开平台判据**：≥ 19.6% ⇒ partial 不变下需 **净 +6 个 L1**。

**⚠️ 陷阱**：**P0「解冻可测性」会让 L1 率暂时下降**。
- L1 率 = L1/(L1+partial)；P0 解锁的是**可测性**（`matched` 增加），新解锁函数首先进 **partial** ⇒ **分母变大**
- 若 L1 不同步增加 ⇒ **L1 率反而从 18.7% 降到 18.x%**
- **这是预期，不是回退！**

**⇒ 每轮 T3/T4 的 acceptance 判据必须拆开**：
| 阶段 | 成功判据 |
|---|---|
| **P0 解冻**（可测性）| ✅ `matched` 增加 + 可比字节增加 + 布局等价；**L1 率下降是预期，不算回退** |
| **P1/P2 字节修复** | ✅ L1 率上升 |

**若不拆开，会把 P0 的成功误判为回退** —— 这是 kiro 终审警告的「度量不平稳」陷阱的新形态。

**L1 质量注**（kiro 终审）：86 个 L1 中 **29 个 ≤16B**（thunk/桩）· 总字节 **2,569 B** ·
**25.4% 的 L1 字节是重定位通配**（`gbengine_compare.py:258-260` 不校验调用目标）⇒ 未来提升 L1 质量（重定位目标校验）与提升 L1 数量同等重要。
