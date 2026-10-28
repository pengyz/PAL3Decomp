# 攻击式验收复核：ref-TOS 合并 C3-C8 六提交（2026-10-28）

复核对象：C3 `0593e8f60`（stage3 重接线+ctx，唯一行为提交）· C4 `ce260b929`（`_strip_outer_parens` 下沉 textutil）·
C5 `826cc06b0`（`_call_return_type` 双改名）· C7+E5 `2390f6bbf`（死体切除）· C6 `4cd3ea64e`（sig_resolve.py 下沉）·
C8 `b3ae31e00`（GetAABBox 表拆分落表）。基线：`data/status/review_ref_tos_impl_C1C2_20261028.md`（E1-E7 必修集）+
`data/status/review_ref_tos_merge_design_20261028.md`（C1-C8 切分/测试清单 T1-T8）。
方法：git 考古 + **三态 A/B 全量再生成**（pre_C3 / C3 / C6 三 worktree 隔离 codegen + 主树 HEAD 复原第四态）+
错误多重集逐提交对账（baselines 快照 5 组）+ 20 万随机串等价 fuzz + AST/全仓 grep + 测试实跑（含控制组）。
**产品文件零改动**；实验产物在 /tmp（worktree + manifest），主树 pal3/src 已复原并逐字验证。

---

## 1. 总裁决

**ACCEPT-WITH-FIXES**

六个提交的**实现本体全部成立**，且本次 A/B 把 C3 归因缺口（E3 挂账项）**彻底闭合**：

- **C3 行为差集 = 8 文件 14 行纯空白等价形**（whitespace-normalized 全等实证），编译字节不可见 ⇒
  错误多重集 214 单元逐条全等、L1 147 / 880-1141 不动全部得到机理解释；**无任何 token 级语义改写**。
- **C4+C5+C6+C7+E5 四提交全树逐字节零差**（C3 态 vs C6 态 996 文件 manifest 全等）——
  「零行为」主张拿到比 loop 读数强得多的全树等价证明。
- **C8 影响面 = 1 文件 1 行**（`ScreenEffectMgr.cpp:849` `*pBox`→`pBox`，即目标 C2664 的消失），且
  gbOBBox 4 生产站点**逐字节保持**（限定键精确承接裸键的既有修复）；A 级 mangled 证据（PAU/AAU）与表拆分吻合。

但三项纪律失守须修：①**C8 致 3 条测试转红而 commit 声称「19+1 断言全过」失实**（活体破坏 E1 绝对锁）；
②**E7 守卫只落 1/3 闸且 scanner 有盲区**（`from stages import X` 形 5 条真实边不可见；同名双定义闸缺位，
活证据 = test_c3 双定义遮蔽 1 测）；③C3 commit message 的**机制归因写错**（称「Case2/3 ctx 门激活」，
实测为 arg 前导空白保留差异，ctx 门在语料上零 token 级激活）。缺陷均非行为级，修复成本低 ⇒ ACCEPT-WITH-FIXES，
**第 3 节 P0 项修完前不建议开 PlanA-T2'**。

---

## 2. 逐攻击点 verdict

### 攻击点 1 —— C3 行为差集归因裁决：**归因可接受（本次已补做；commit 机制表述须更正）**

**实验**：`git worktree` 三态（`248ccf2ee`=C3 前 / `0593e8f60`=C3 / `4cd3ea64e`=C6）+ 主树 HEAD（C8）共四态，
各自 `python3 pipeline/gen/codegen.py all` 全量再生成，`find pal3/src -type f | sort | xargs sha256sum` 逐文件 manifest 比对。
方法学核对：C3 态输出与实现者当时记录的树哈希 `013ab196` **逐字命中**（同环境同输入）⇒ 复原法可信。

**差集（pre_C3 → C3）= 8 文件 14 行对，全部为空白**：

| 文件 | 行对 | 单元态（180559 快照） | 差形 |
|---|---|---|---|
| Combat/CCBStage.cpp | 1 | fail(101) | `, * (T*)x` → `,  * (T*)x` |
| Effect/CEffModel.cpp | 3 | fail(1) | 同上 |
| GameBase/GRPinput.cpp | 1 | fail(15) | `, v7 + 1` → `,  v7 + 1`（args 1/2） |
| Misc/RoleCamera.cpp | 1 | **ok** | `,  *p_z` → `,   *p_z` |
| Misc/UIAnimateCtrlEX.cpp | 1 | **ok** | `, * (T*)x` → `,  * (T*)x` |
| Role/Object3D.cpp | 5 | fail(8) | 同上 |
| Role/RoleSystem.cpp | 1 | fail(51) | 同上 |
| Scene/Camera.cpp | 1 | **ok** | 同上 |

- **不是「只在 fail 单元」**（3 ok + 5 fail），**但全部是等价形**：8 文件 whitespace-normalized 全等
  （`re.sub(r'\s+',' ')` 后逐字节相等，实测 True×8）⇒ MSVC 编译字节不变 ⇒ L1/错误面全等是**必然而非巧合**。
- **机理（与 commit message 不同）**：旧 stage3 子集版对 ref 位实参无条件 `arg.lstrip()`；共享版
  `_fix_single_ref_arg` 非 Case1 分支**保留前导空白** ⇒ `, ` 分隔符 + 原有前导空 = 双空格。
  Case2/2b/3 在 stage3 位点**零 token 级激活**——stage5 下游同一修复器会再跑一遍，语义被吸收
  （`*pBox` 形在 stage3 或 stage5 产出同终形），故 C3 的语义增量 = 「同一变换提前一步」（幂等重排），
  唯一可见差就是空白归一。**commit message「哈希变 = Case2/3（ctx 门）激活的预期变化」机制归因错误**（记缺陷 F3）。
- 与 C1 态普查（E3 锚 `ref_fix_census_C1_20261028.json`，36 文件激活面/粗计数器）的关系：
  36 = 激活面分母（含 ref-param 调用点的文件），8 = 空白可见子集；粗计数器 pre/post 全等是真话，
  但它本就不具备判别力（`strip_amp_approx/tail_fold` 两计数均为 0）。**逐文件归因至此挂账清零**，
  本节表格即 E3 修法（per-file 快照法）的交付物，建议连 manifest 一起归档。
- 读数面独立佐证：baselines 快照 5 组（16:09/17:17/17:42/18:04/19:14）错误多重集逐单元比对：
  **C3/C4/C5 三步 214 单元多重集逐字全等**；末步仅 1 条 C2664 消失（归 C8，见攻击点 5）。

### 攻击点 2 —— C4 零行为：**CONFIRMED（强于主张）**

- **正典体逐字**：textutil.py `_strip_outer_parens` 与 stage3 原版**逐行零差**（def 体 + docstring 同）✓。
- **两原版等价**：stage3 版 vs stage5 版对字符串输入语义同构——**穷举 `()ab ` 字母表 len≤6 全量 + 20 万随机串
  fuzz = 0 差异**（/tmp/c4exp/fuzz.py），边角件（`(a)+(b)` 不剥 / `((a))` / `()` / 括号不平衡 / 空白包裹）全等。
  「10 边角件实证」成立且被更强证据覆盖。
- **None 安全差异**：正典 `str(text or '')`，stage5 原版 `e.strip()` 遇 None 崩。调用面清点：
  stage5 唯一调用点 `_expr_is_pointer`（:743）的 3 个上游（:814 切片 / :885 `line[p:rhs_end]` / :934）
  **全部为 str 切片，无 None 通道** ⇒ 差异真无影响（仅防御性加固）。stage3 6 调用点全为 regex group/字符串 ✓。
- 全树等价证明：C3 态 vs C6 态（含 C4）manifest **逐字节全等** ⇒ C4 生产面零差 ✓。
- 附注：C4 无新增测试（「10/10 测绿」= 存量测试未红），等价实证未入库——建议把 fuzz 收编成 1 条回归测（记 F6）。

### 攻击点 3 —— C5 改名完备：**CONFIRMED COMPLETE**

- 全仓 grep 旧名 `_call_return_type`：**代码面 0 残留**（唯一命中是测试函数名 `test_c5_call_return_type_disambiguated`
  自身，非引用）✓；新名消费面各 3 处（stage4 def+1 调用、stage5 def+2 调用），**跨文件零互引实测**（调用面自闭）。
- diff 仅 6 行 def/调用行（`-def _call_return_type(node)` → `+def _node_call_return_type(node)` 等），
  **函数体/签名参数零触碰** ✓ 语义未动。
- 测试锁 `test_c5_call_return_type_disambiguated` 双向断言（hasattr 新 + not hasattr 旧）真锁 ✓；
  全树等价（C3==C6）再次佐证零行为 ✓。

### 攻击点 4 —— C6 迁移完备性：**PARTIAL（迁移本体完美；回导卫生与守卫收紧有缺）**

- **迁移逐字性 ✓**：5 函数 + 4 常量（=9 件）AST 级比对，`_anon_aggregate`/`_resolve_offset`/
  `rewrite_thiscall_fnptr_param(_ex)` **diff=0 行**；`_try_struct_member_resolution`→`try_struct_member_resolution`
  仅 def 名 1 行差（公有化改名，调用点同步）✓。
- **外依闭合 ✓**：sig_resolve.py imports 仅 `re` + `from data import store`（9 件闭合）✓；
  全仓旧名 `_try_struct_member_resolution` 零残留（仅 docstring 史料）✓。
- **emit_headers 两调用点 ✓**：`rewrite_thiscall_fnptr_param(p, cls_name)`（2 形参）与
  `try_struct_member_resolution(prefix_name)`（1 形参）与新 def 形参逐一对齐；两处导入均改走
  `pipeline.gen.sig_resolve` 绝对形 ⇒ 单注册（同 `gotcha_dual_copy` 教训的注释仍在，路径注已随迁更新）✓。
- **✗ stage4 回导名单冗余坐实（9 件全回导 = 6 件死 import）**：`_ANON_PTR_ARG_RE`/`_ELEM_SIZES`/
  `_FPTR_PARAM_RE`/`_THIS_NAME_RE`/`_anon_aggregate`/`rewrite_thiscall_fnptr_param` 在 stage4 **零消费**
  （AST Name 计数 = 0；仅 `_resolve_offset`×3 / `try_struct_member_resolution`×1 / `rewrite_thiscall_fnptr_param_ex`×1 真用）。
  「回导（如需）」注释自认预留，但 E6 刚在 stage5 清过同型死 import——同型卫生债复发（F4）。
- **守卫冻结集 6→5 收紧方向正确**（删 `('emit_headers','stage4_substitution')` = 违例边移除后防回流 ✓；
  5 条既定分层豁免与设计清单逐一对上）；**但冻结集本身建立在有盲区的 scanner 上**（见攻击点 6）。

### 攻击点 5 —— C8 表变更风险面：**CONFIRMED CORRECT（证据链完整）；测试面有洞**

- **mangled A 级证据吻合**：`gbengine.def` 4 形全录——`gbBaseMesh`=返回 PAU 无参 · `gbGeomNode`/`gbVisNode`=
  **PAU 指针形** · `gbOBBox`=`AAU 引用形` ⇒ 「裸键出表、gbOBBox 限定键留表」与权威形参形态**完全一致** ✓。
- **裸形调用点普查（出表后不再修复=潜在 C2664 留存？）**：decomp 语料 GetAABBox 全部 9 处 =
  `gbOBBox::`×4（调用）· `gbVisNode::`×1（调用）· `gbLightObj::`×2（定义+调用）· `ScreenEffectMgr::`×2（定义+调用），
  **0 处裸 `->GetAABBox(`/`.GetAABBox(`**；出表丢掉的修复仅作用于 PAU 形站点，而 PAU 形修复本来就是错的
  （`pBox`→`*pBox` = C2664）⇒ **无「该修未修」留存** ✓。终树唯一受影响点 = ScreenEffectMgr.cpp:849，
  A/B 实测其差 = 1 行 `*pBox`→`pBox`，恰与错误多重集 −1（`C2664 'GetAABBox' cannot convert … gbAABBox → gbAABBox*`，
  ScreenEffectMgr）**同点对上** ✓✓。
- **gbOBBox ref@0 与生产 4 站点形吻合**：`RoleSystem:8126(v55)`（BYREF 值局部 → 裸形 ✓）· `Role:179(*pBox)`（指针解引用 ✓）·
  `gbLightObj:30(*p)`（✓）· `UIBigMap:1026(*(gbAABBox *)&v20.z)`（cast 解引用 ✓）——**限定键 `gbOBBox::GetAABBox\s*\(`
  4/4 命中且 C6→HEAD manifest 这 4 文件逐字节不变**（RoleSystem/Role/gbLightObj/UIBigMap 均不在 C8 差集内）⇒
  限定键精确承接裸键既有修复，零丢失零误改 ✓。
- **SetBlend 教训反向审计（误登=静默坏码）**：限定键按 mangled 名只在 `gbOBBox::GetAABBox(` 文本上触发，
  该渲染只可能来自 gbOBBox 接收者（= 该方法唯一签名 AAU 引用形，def 文件里无重载）⇒ **指针形误伤面结构性闭合** ✓。
  两处残余（低危，非 C8 引入）：①plain-set `{0}` 不感知元数——若某站点以 **static 二元形** `gbOBBox::GetAABBox(&recv, arg)`
  进入修复器（stage2 OOP 未转换），{0} 会咬 receiver 剥 `&`（F1b 同族）；当前语料 0 站点（stage2 先行已转 OOP），
  建议改元数感知形 `{1: {0}}`（F7）。②`('gbOBBox::GetAABBox', 0)` 未入 `_GB_REF_PARAM_TYPES` ⇒ Case2b/F81b
  `*stru_XXXX`→`*(T*)&stru` 面在该键缺失（存量缺口，非回归）。
- **✗ 测试面**：`test_getaabox_cross_class_form_split` 转绿 ✓（5/5），但其 `code_ref` 断言是 **no-op 形**
  （`*pBox` 对任意实现恒不变，锁不住「AAU 形被正确修复」）；4 生产站点形只锁了 1 形，缺剥 `&` 形/裸值形/cast 形（F5）。
- **✗✗ 连带破坏（本复核最大发现）**：C8 删裸键让 `tests/test_ref_params_tos.py` 3 条测试**当场转红**——
  `test_shared_fixer_behavior_locked`（CASES 钉 `GetAABBox(pBox)→*pBox`）· `test_ab_parity_legacy_is_shared_post_c2`（同）·
  `test_e1_noctx_degradation_absolute`（E1 绝对锁）。控制组实证：C6 态 15 绿 1 红（仅 D1 活红），HEAD 态 3 红——
  **C8 commit「19+1 断言全过」失实**（只跑了 table_b 5/5 就外推）。锁红是好事（E1 真锁生效 = 禁静默改判被守住），
  但正确动作是**随行为变更同步更新绝对断言并注明理由**，而非留红 + 失实叙述（F1）。

### 攻击点 6 —— E5/E7 死体与守卫：**E5/C7 完成；E7 PARTIAL（1/3 闸 + scanner 盲区）**

- **E5 ✓ 零残留**：`_ref_positions` 全仓 grep 仅 0 命中（ref_params 内 def 已切，2390f6bbf）；「表捕获 ref_indices 形参」
  为循环真变量非遗留。
- **C7 ✓ 零残留**：`_resolve_ordinal_type` 全文件仅 1 def（:383）+ 1 调用（:1659），自影首体（旧 :375-379）已删；
  两体逐字同的前提由 git show 核过 ✓。
- **E7 ✗ 只落 T6 一闸**（`test_stage_edges_frozen_no_new_cross_refs`）：设计 T6-T8 三闸中
  **同名双定义闸、共享层禁上行闸（ref_params/textutil/sig_resolve 禁 import stages）均未建**——
  同名双定义闸缺位的活证据已在仓内：`tests/test_ref_params_tos.py` 两个 `test_c3_stage3_rewired_ctx_gate`
  同名双定义（后者遮蔽前者，pytest 实测只收 9 测）。
- **T6 scanner 盲区（实测）**：`transform.py` 用 `from stages import stage1_structural, …, stage5_fixup` 形
  （ast.ImportFrom 的 `n.module='stages'`，目标在 alias 里）⇒ guard 的 `_edges()` **完全看不见这 5 条真实
  stage↔stage 边**（transform→stage1/2/3/4/5）。全边集 = 5 冻结边 + 5 隐形边 = 10 对，guard 视野仅 5 对；
  **任何人用 `from stages import X` 形加新违例边不会红**——棘轮声称「新增边必红」对半数导入形失效（F2）。

### 攻击点 7 —— 单变量纪律 / 可 bisect / 测试掩盖面：**基本成立，三处瑕疵**

- **bisect 可行 ✓**：六提交各改独立文件集，单提交可 revert 不互相纠缠；我的四态 A/B 即按提交粒度二分复原 ✓。
- **测试演进掩盖面（实测）**：①`test_c3_stage3_rewired_ctx_gate` **同名双定义**——pytest 收集 9 测而 C3/C5 message
  声称「10/10」「11/11」（按 def 数计数，遮蔽的那条从不见天日）；②test5 `test_case3_no_gate_degradation_matches_legacy`
  维持恒真（f(x)==f(x)，docstring 仍称「防静默改判」）——E1 修了新增绝对锁 test_e1 但未按要求改写/标注 test5（半项）；
  ③测试序污染（**既有，非本批引入**）：`tests/` 全套 + `pipeline/gen/test_pipeline.py` 同跑时
  `test_vftable_offset4_call_stubbed` 红、单独跑绿（TOS 两件与之同跑不复现 ⇒ 污染源在 tests/ 其他用例的 store 状态残留），
  与 `test_hang3_nails::test_rename_fingerprint`（数据陈旧红，三态全红）同列已知红清单。
- **验证纪律**：每提交带 loop 5/5 + 读数，但①C7+E5 **无独立 loop**（仅 11 测+语法自检）——其零行为事后由
  C3==C6 全树等价补证 ✓ 可豁免；②C6/C7+E5/C8 三提交共享 19:14 一次 loop（混批验证），好在错误多重集差
  仅 1 条且全归 C8 机理、其余两提交零差由 A/B 补证；③C8「读数全等」措辞不确（errors 1137→1136，
  −1 = 预期修复；L1·880-1141·S2 确实全等）。
- **E1-E7 兑现对账**（前批必修集，逐条）：E1 半（test_e1 新增 ✓ / test5 未改写未标注 ✗）· E2 半（幂等断言 ✓ /
  `obj->_tail_000[3]` 二次应用形未含 ✗）· E3 弱（36 文件计数锚 ✓ / (file,case-kind) 多重集 ✗，由本次 A/B 补齐）·
  **E4 未做**（F1b/F3 史料块 stage5+ref_params 双份逐字并存 + F81 悬空引言 + Local-kinds 悬空注释，实测仍在）·
  E5 ✓ · E6 半（3 死 import 删 ✓ / 「测试兼容再导出」注释未加 ✗；且 C6 又新增 6 死 import）·
  E7 半（T6 ✓ / T7-T8 ✗ + 盲区）。E8/E9/E10 均未做（docstring D6/幂等句缺、tables.py 互指注释 diff=0、
  `_fix_single_ref_arg` 身份断言缺）。

---

## 3. 缺陷清单 + PlanA-T2' 开工前必修

| # | 级别 | 缺陷 | 处置 |
|---|---|---|---|
| F1 | **高（T2' 前必修）** | C8 致 3 测转红未修未声明：`test_shared_fixer_behavior_locked`/`test_ab_parity_legacy_is_shared_post_c2`/`test_e1_noctx_degradation_absolute` 钉的 `GetAABBox(pBox)→*pBox` 已被 B 修补条合法废止；commit「19+1 断言全过」失实（控制组：C6 态 15 绿 1 红 / HEAD 态 3 红） | 随行为变更同步更新 CASES/E1 期望为 post-C8 真值（`GetAABBox(pBox)` 不动），**显式注记「锁更新 = B 修补条行为变更」**；补 gbOBBox 限定形断言（剥&/裸值/cast 三形） |
| F2 | **高（T2' 前必修）** | E7 守卫 1/3 闸 + scanner 盲区：`from stages import X` 形 5 条真实边不可见（transform→stage1..5），同形新违例不红；同名双定义闸/共享层禁上行闸缺位（活证据：test_c3 双定义遮蔽 1 测） | scanner 补 alias-name 边捕获；补 T7（同名双定义，tests+pipeline 双域）/T8（pipeline/gen 非 stage 模块禁 import stages）；修 test_c3 双定义（改名或删一） |
| F3 | **中（T2' 前必修）** | C3 commit message 机制归因错误：空白差被表述为「Case2/3（ctx 门）激活」；ctx 门语料零 token 级激活（stage5 下游同修复吸收），真正机理 = arg 前导空白保留 vs lstrip | message 勘误（不动代码）；把本报告第 2 节 8 文件归因表 + 四态 manifest 归档为 E3 的 per-file 快照台账 |
| F4 | 中 | C6 回导 6/9 死 import（stage4：`_ANON_PTR_ARG_RE`/`_ELEM_SIZES`/`_FPTR_PARAM_RE`/`_THIS_NAME_RE`/`_anon_aggregate`/`rewrite_thiscall_fnptr_param`）；stage5 侧 `_GB_REF_PARAM_FUNCS`/`_fix_single_ref_arg`「测试兼容再导出」注释仍缺（E6 半项） | 删 6 件或注明预留用途；stage5 两件加注释 |
| F5 | 中 | E4 未执行：F1b/F3 删键史块 stage5 双份并存（12/12、16/16 行逐字同）+ F81 悬空引言 + Local-kinds 悬空注释——`gotcha_dual_copy_table_divergence` 史料漂移面 | 删 stage5 侧副本，史料留 ref_params 单份（零行为） |
| F6 | 中 | F1a「双空格 = 二次应用指纹」判据失效：共享实现自然产 `,  * (T*)x` 双空格 15 处（本批 8 文件实证）⇒ 指纹不再诊断性；C4 等价 fuzz 证据未入库 | ref_params docstring 更新判据（或恢复空白归一）；fuzz 收编 1 条回归测 |
| F7 | 低 | gbOBBox 限定键 plain-set `{0}` 不感知元数：static 二元形（未经 stage2 OOP）会误剥 receiver `&`（F1b 同族；当前语料 0 站点）；`('gbOBBox::GetAABBox',0)` 未入 `_GB_REF_PARAM_TYPES` | 改 `{1: {0}}` 元数感知形 + TYPES 补键（各有 A 级证据后动） |
| F8 | 低 | 测试计数虚高（C3「10/10」实收 9、C5「11/11」实收 10，同名遮蔽）；C7+E5 无独立 loop（零行为由 A/B 补证可豁免）；C8「读数全等」措辞（errors −1）；test5 恒真未标注（E1 半项）；E2 少 `obj->_tail_000[3]` 二次应用断言 | 叙述勘误 + 小补断言（均零行为） |
| F9 | 信息 | 既有红×2 与本批无关但会污染「全绿」判读：`test_hang3_nails::test_rename_fingerprint`（数据陈旧，三态全红）、`test_pipeline::test_vftable_offset4_call_stubbed`（tests/ 序污染，单跑绿） | 入已知红清单；序污染独立排查（勿挂 TOS 账） |
| F10 | 信息 | `pipeline/gen/ast_transform.py:101` OSError 兜底自身 `NameError: _sys`（输入缺失时崩而非降级警告）；本次 worktree 实验亲历 | 独立卫生微批（`import sys`） |

**PlanA-T2' 开工前必修最小集**：F1、F2、F3（测试真值 + 守卫补闸 + 归因台账落盘）；
F4/F5/F6 建议同批顺手（皆零行为）；F7-F10 可挂账。

---

## 4. 未复验清单

1. **C3 归因的环境残差**：A/B 在缺 `include/pal3/gen/globals.h`（gitignored 生成件）的 worktree 输入集下跑，
   该缺口使 RoleAtt.cpp / s_RoleState.cpp 两文件的 `extern char aBasedataSkeePa[];` 行在四态间成对抖动
   （噪声已定位、双侧对称、不进差集）；8 文件空白差与 C8 1 行差均在噪声外独立成立，且 C3 态输出与记录哈希
   `013ab196` 逐字命中（=同输入复原验证），但**严格字节级 A/B 复跑（补 globals.h 输入）未做**。
2. **C1/C2 记录的 C2 态哈希 9e0498c8** 未逐字复算（pre_C3 清洁态因同一输入缺口为 463d1e1a，差 2 文件噪声）；
   差集推断依赖「C2 态 = pre_C3 态」这一传递假设（E1-E7 提交皆零行为前提），未独立验证。
3. **L1 逐提交读数**只从 s4_baseline.json（本区间未变，ratchet 14:33=147）与 commit message 引用面间接佐证；
   各提交 match 日志已被后轮覆盖，`[metric]` 三分账逐提交对账未做。
4. **`tests/` 序污染源**（test_vftable_offset4_call_stubbed 仅套件序红）未二分定位到具体用例；
   worktree 控制实验因 7 个测试文件收集依赖主树未跟踪件而未完成。
5. **pyflakes/ruff 正式 lint 未跑**（死 import 判定为 AST 消费面清点）；`__pycache__` 双语境缓存隔离面未逐一核对。
6. **static 二元形残余风险（F7）**的生产面「永不出现」只由「stage2 OOP 先行」当下事实担保，无机器锁；
   若未来 OOP 转换放宽，需先落元数感知形。
7. **pal3/src_error、pal3/src_fake** 两目录生成面归属未穷尽（延续 C1/C2 未复验 #3）。
8. **worktree 再生成法的跨环境可复现性**（sort/xargs 语序、toml 路径形）未在第二台机复算；
   另：实验期主树 pal3/src 曾被 3 并发 worktree 泄写污染（`store.project_root` 随绝对 annotations 路径漂移），
   已按 HEAD 复原并经 manifest 逐字验证（franken vs 复原态差 = 仅 C8 的 1 文件）——**当前主树 = 规范 C8 态**。

---

## 附：关键读数台账（baselines 快照逐提交对账）

| 提交 | 提交时刻 | loop 快照 | S2 | errors | L1 | 880/1141 | 错误多重集 vs 前态 |
|---|---|---|---|---|---|---|---|
| C3 0593e8f60 | 17:31 | 17:17/17:19 | 133/214 | 1137 | 147 | ✓ | **214 单元全等** |
| C4 ce260b929 | 17:53 | 17:42/17:43 | 133/214 | 1137 | 147 | ✓ | **全等** |
| C5 826cc06b0 | 18:16 | 18:04/18:05 | 133/214 | 1137 | 147 | ✓ | **全等** |
| C7+E5 2390f6bbf | 19:04 | （无独立 loop） | — | — | — | — | A/B 补证：零差 |
| C6 4cd3ea64e | 19:06 | 19:14/19:15（与 C8 共享） | 133/214 | 1136 | 147 | ✓ | −1×`C2664 GetAABBox`（ScreenEffectMgr，归 C8） |
| C8 b3ae31e00 | 19:26 | 同上 | 133/214 | 1136 | 147 | ✓ | 同上（=预期修复） |

全树 manifest 四态：pre_C3 463d1e1a（清洁）· C3 366b7048 · C6 366b7048（**与 C3 全等**）· HEAD-C8 dadbf65b
（= C3 态 + C8 1 行 + 2 文件输入噪声剔除后逐字闭合）。记录哈希复原核对：C3 态同输入输出 = `013ab196` 逐字命中。
