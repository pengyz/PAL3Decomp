# W3 退役审计·机制同形态重放底稿（2026-09-27，只读；fbe198d4 Q6-1 口径）

## 方法（口径修正记录）
`_try_struct_member_resolution`（stage4 真解析器）须先 `store.load()`——空 store ⇒ 解析恒 None
（cc7f9665a 已修机制侧；探针侧首跑踩同坑，1306 全不解析即此病）。双形态复放：
真名（`g_nTargetSlot`）与地址形态（`dword_%X`）分别过解析器。

## 读数（globals.json 1306 条）——与复核 fbe198d4 独立复算精确吻合
| 形态结果 | 计数 |
|---|---|
| 双形态皆不解析（无成员路径）| 1176 |
| 仅地址形态解析 | 113 |
| 双形态皆解析 | 17 |
| **可解析合计** | **130**（= 复核"130/17"）|

## 受害面（W3 核心账目）
1. **解析进串名伪实例（P0-a 活体层受害）= 9 条**（与复核实测一致）：
   FileName→aExplosive.m_DefaultUVSet[12].ev · g_nCombatRandSeed→aModel.m_fCurTime ·
   aRb→pEffMgr.m_fTimer · index→aShock.roleIdx · aSpeed12f→aModel.roleIdx ·
   unk_5DFDB4→aShock.m_fCurTime · unk_5DFDC0→aShock.m_fTimeScale ·
   unk_5DFDCC→aMeteor.m_fTimer · aWt→pEffMgr.m_fDeltaTime
   ⇒ W2-⑤（实例类型纠正 a*/p*→char[]）落地后这 9 条解析消失，extern 自动回归。
2. **解析进幻影成员路径**（g_nTargetSlot→g_EffMgr.m_nTargetSlot 族）= 29 条严格族
   （auto:overlap/global_analysis 源，见 _plan_review_corrections_p0.md）——W2-③④ 落地后
   解析消失，按 _forced_global_entries 机制回 extern。
3. 机制形态差异结论（fbe198d4 Q6-1 要求写成结论）：**真名形态恒难解析**（17/1306），
   退役主要经地址形态发生 ⇒ 命名全局的 extern 多数未被退役，其受害形态是
   **渲染层成员路径改写**而非 extern 丢失——W3 恢复账目须按此分列。

## W3 剩余工项
- 130 条可解析逐条裁定（真实成员退役=正确 / 幻影方向=恢复）；
- LPCSTR 双声明族修复（globals.json 4 条 LPCSTR 型 off_* × TU 合成 extern 类型不一致，
  codegen 实测 C2040×25/C2440×4 + C2065×2，见 _w4c0b_acceptance_and_attribution.md）；
- extern 数变化有账（分母统一：extern 2034 / globals 1306）。

## 附：双声明族病灶定位（2026-09-28，W3 修复设计输入，纯读实证）
**同根两族**（C2040×25 LPCSTR + C2371×5 byte_DE9*）= **TU 就地 extern 合成的类型源分裂**：
- `globals.h:2050` `extern unsigned char byte_DE93A8;`（注解型，权威）vs
  `CEffectSystem.cpp:26` `extern char byte_DE93A8;`（TU 就地合成——`_prefix_type` 按名字前缀
  猜型：`byte_`→char、`off_`→char*，**不查 globals.json 真型**）⇒ C2371 redefinition；
- 同理 `globals.json` 4 条 LPCSTR 型 off_* vs 合成 `char` ⇒ C2040 levels-of-indirection。
**修复（一处灭两族）**：TU 就地 extern / forced-global 的类型解析改为
**globals.json（注解型）优先，`_prefix_type` 前缀启发仅作最后回退**；两消费者
（emit_cpp 就地块 + emit_headers._forced_global_entries 的 _prefix_type 调用点）走同一解析函数。
预期收益：C2040 −25 / C2371 −5 / C2440 衍生 −4 ≈ **−34**。
另：C2371×5 是 PAL3 收缩释放 49 全局的合法副作用（释放区名字首见）——修后即消。

## 附：W 重编目预计算（同日只读，B 主线弹药）
- W 715 → **W' 697**（W2 首批移出 18 行占位）；W' 分级 A=188（全 WIDTH-4-MATCHED）/B=295/0=211/C=3；
- **9 行填充重定向**（7A+2B float，ff86c62f 全套）：从 PAL3 幻影成员 → **globals.json 独立全局**
  （g_nRenderTarget2_DE8DF8 族 @0xDE8DF8..）——float 证据真实（47 站点字节级 0 失配），
  归属改对后填充合法 ⇒ 需守卫 `global_retype` kind（与 W2 落地同轮加）；
- W' 内 A 级可直接填=0（与"证据诚实终局"一致）；其余增量走 T1b v3（≤19 预报）。
