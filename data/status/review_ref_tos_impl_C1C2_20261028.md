# 攻击式验收复核：ref-TOS 合并 C1+C2 实现（2026-10-28）

复核对象：C1 `acdc5594b`（ref_params.py 纯新增 + tests/test_ref_params_tos.py 5 测）· C2 `6db24144c`（stage5 重接线 -254 行 + 测试契约进化 6 测）。
基准：`data/status/review_ref_tos_merge_design_20261028.md`（C1-C5 切分、D0/D0' 修法、3.1 文件级操作清单、3.2 测试清单 T1-T8）。
方法：`git show` 历史取证 + AST 逐函数/逐常量比对 + 243,022 行真实语料旧新差分 + 哈希法复原与溯源 + sys.modules 双注册实证 + 测试实跑。**全程零产品文件改动**；实验在 /tmp 与只读命令内完成。

---

## 1. 总裁决

**ACCEPT-WITH-FIXES**

两提交的核心主张经独立验证**成立**：
- 迁移逐字性：`_fix_single_ref_arg`/`_build_var_types`/`_split_top_commas` AST 逐字同，`_GB_REF_PARAM_TYPES`/`_NON_POINTER_LOCAL_KINDS`/`_DECL_KEYWORDS` AST 常量逐字同，`_fix_ref_params` 唯一差异 = 尾折叠随迁 2 行（D0 修法件）；
- C2 零行为：pal3/src 全树 manifest 哈希 A/B 全等（**方法独立复原逐字吻合**：`find pal3/src -type f | sort | xargs sha256sum | sha256sum` = `9e0498c8…`，与 /tmp/gen_before.txt、gen_after.txt 两文件一致），旧新实现在 243,022 行真实生成语料上差分 = **0 行**，终树可折叠 `->_tail_000` 残形 = **0**（1144 处全是 `(?!\[)` 跳过的下标形/声明形）；读数 S2 133/214 · errors 1137 · L1 147 · 880/1141 与设计基线逐字同，且 s4_baseline.json ratchet 前值（14:33，TOS 动工前）= 147/880-1141 独立佐证；
- 导入安全：双注册面实证封死（sys.modules 单注册、store/表对象三同一，见攻击点 4）；
- 范围纪律：C2 仅 3 hunk（旧域 562-906）+ 测试两处，C4/C5 件（`_strip_outer_parens`/`_call_return_type`）零触碰，stage3 零污染（D0' 预告成立）。

但**设计定稿的多项明确处置未执行**，且 C2 的「契约进化」使 test5（D0' 锁）**静默空转而未声明**——行为面无回归，安全网有缺口。C3 是唯一行为变更提交，其「禁静默改判」契约目前缺机器看护 ⇒ 必须按下述第 3 节补锁后方可开工。

---

## 2. 逐攻击点 verdict

### 攻击点 1 —— ref_params.py 内容完备性：**PARTIAL**

7 件 + 尾折叠逐件对账（源 = `git show acdc5594b:pipeline/gen/stages/stage5_fixup.py` / stage3_cleanup.py:2248，AST 级比对非目测）：

| 设计清单件 | 裁定 | 证据 |
|---|---|---|
| `_GB_REF_PARAM_FUNCS` 不迁、绝对形 import | ✓ | ref_params:14 `from pipeline.gen.tables import _GB_REF_PARAM_FUNCS` |
| `_GB_REF_PARAM_TYPES` 迁 dict + F1b/F3 删键史块随迁 | ✓（dict AST-identical；F1b 12 行/F3 16 行两块逐字在 ref_params） | AST 常量 dump 相等；块级逐行比对 True/True |
| `_NON_POINTER_LOCAL_KINDS` 原样迁 | ✓ AST-identical | 同上 |
| `_fix_ref_params(code, ctx=None)`：stage5 基 + **丢 `_ref_positions`** + 尾折叠（stage3 逐字） | **✗ 半项** | ①`_ref_positions` 死闭包**未丢**——随 verbatim segment 混入 ref_params（AST diff 全函数仅差尾折叠 2 行，无删除行）；②尾折叠正则/替换逐字 ✓（`(\w+)->_tail_000\b(?!\[)` → `*(void**)(\1)`，位序=实参循环后、return 前，与 stage3 一致）但**注释非 stage3 逐字**（定稿要求「逐字，含 `# _tail_000 兼容转换` 注释」；实际为 `[TOS 2026-10-28] …兼容折叠…` 改写） |
| `_fix_single_ref_arg` 原样迁 | ✓ VERBATIM（difflib 零差异） | AST 逐行同 |
| `_DECL_KEYWORDS` / `_split_top_commas` | ✓ AST-identical / VERBATIM | 同上 |
| `_build_var_types` 原样迁 | ✓ VERBATIM | 同上 |

- **`_ref_positions` 死闭包裁定（问题原文：是否按定稿丢弃？）：随 segment 混入，未丢弃**。定稿 3.1 明文「丢 `_ref_positions` 死闭包（653-656）」、缺陷表 D5「C1 下沉时丢弃（零行为 diff）」——未执行。实测新旧两版函数体逐字同（含该 def），且 def 在 for 循环体内每轮重建、零调用（死代码坐实）。
- **遗漏件**（设计 C1 交付清单有、实现无）：①`pipeline/gen/tables.py` 姊妹表注释（定稿攻击点 3「tables.py 头注释加互指」）——`git diff 4629573ab HEAD -- pipeline/gen/tables.py` = **0 行**；②`tests/test_tos_stage_isolation.py`（T6-T8 守卫）**完全未建**；③`pipeline/gen/test_ref_params_ab_corpus.py`（慢测语料）未建。
- **多余件**：`_ref_positions`（应丢未丢）；测试落位 `tests/test_ref_params_tos.py` 而非定稿的 `pipeline/gen/test_ref_params_tos.py`（与任务书口径一致，记信息级）。
- **charter 契合度**：docstring 覆盖 D0/D0'/导入约定，但**缺 D6 要求句**（`_build_var_types` 族供 stage5 C2440 修复器共用——防「C2440 修复器 import ref_params」误判跨界）与尾折叠幂等依据句；**设计缺陷表 D6 处置栏「C1 docstring 已列」与实物不符（失实）**。

### 攻击点 2 —— 零行为证明审计：**CONFIRMED**（方法可信；三类疑点盲区逐一核销，残余 2 项低危）

- **读数面**：working-tree loop 日志（apply 16:02 → export 16:05 → codegen 16:09 → probe 16:15 → match 16:20，完整链）报 `S2 cpp: 133/214 ok | errors=1137`、`matched 880/1141 symbols | L1 147`、ratchet `previous 147 -> current 147`——与 C2 主张、设计基线（status 实测 133/214·1137·147）逐字同。独立佐证：`git diff data/status/s4_baseline.json` 显示 ratchet 前值记录于 **14:33（TOS 动工前）**即为 147 / 880-1141。
- **哈希面**：/tmp/gen_before.txt（15:59:04）与 gen_after.txt（16:20:58）均为 `9e0498c866b4…d838` 单根摘要；**独立复原命令逐字命中**（`find pal3/src -type f | sort | xargs sha256sum | sha256sum`）⇒ 哈希域 = pal3/src 全树 996 文件（782 .h + 214 .cpp），**无扩展过滤、无排除项**。
- **盲区三问核销**：
  1. `__pycache__`：不在哈希域但非生成物；对**验证运行本身**的陈旧 pyc 风险实测干净——`stage5_fixup.pyc` 16:00:22 > 源文件 16:00:07（C2 改动时刻），loop 16:02 后才跑 ⇒ 跑的是新码；`ref_params.pyc` 15:52:08 = 源 15:52:08（C1 落盘即编）。
  2. 非 .cpp/.h 文件：树内实测零此类文件 ⇒ 该盲区为空集。
  3. 「时间戳不入 hash 故漏模板块」：哈希是纯内容 sha256、**零文件被排除**（复原命令无过滤）；若生成物含 wall-clock 时间戳会**假阳**（diff≠0）而非假阴——diff=0 反证生成物内容确定性。「因怕时间戳而跳过文件致漏」的通道不存在。
- **溯源闭合**：stage5 源 mtime 16:00:07 **晚于** gen_before 15:59:04 ⇒ before 哈希确系旧 stage5 本地产物（非重写后产物）✓。
- **补强独立验证**（我方自跑）：①AST 逐函数/逐常量比对（如攻击点 1）；②旧 stage5（git 取体）vs 共享体对 243,022 行 pal3/src 真实语料逐行差分 = **0 差异**；③终树 `(\w+)->_tail_000\b(?!\[)` 可折叠形 = **0** ⇒ 尾折叠对 stage5 输入域确为空转（设计未复验 #3 的「推论」至此有实测双兜底）。
- **残余低危**：①before 侧完整 loop 日志被 after 轮覆盖（before 读数仅存 ratchet 字段+设计文档记录）；②pal3/src_error、pal3/src_fake 两目录在哈希域外——全仓 grep 无 python 写入者（非 codegen 产物），但非 python 途径未穷尽（记入未复验）。

### 攻击点 3 —— 测试质量：**PARTIAL**（6 测 4 真锁 2 空转；「契约进化」掩盖的是锁失效而非已发生回归）

6 测逐一验真（实跑 6/6 绿 + 断言力分析 + C1/C2 版对比）：

| # | 测试 | 设计对应 | 锁力裁定 |
|---|---|---|---|
| 1 | `test_shared_fixer_behavior_locked`（5 形） | T2 子集 | **真锁**（Case1/Case2/尾折叠/下标形/无关码） |
| 2 | `test_ab_parity_legacy_is_shared_post_c2` | 「全案平价」 | **空转**：C2 后 `_s5_legacy is _fix_ref_params`（实测 True）⇒ 断言化为 test1 复写；commit 自认「契约进化」但称「全案平价断言」措辞夸大 |
| 3 | `test_single_apply_contract_double_apply_is_hazard` | 单次应用危险性 | **真锁**（`Translate(&vec)→vec→*vec` 腐蚀形钉死） |
| 4 | `test_tail_fold_does_not_touch_non_tail_names` | T5 子集 | 半锁（非尾名不动）；**幂等 `f(f(s))==f(s)` 无任何断言**——设计 T5 明文要求，未落地 |
| 5 | `test_case3_no_gate_degradation_matches_legacy` | D0'/T2 | **C2 后空转且 docstring 误导**：断言 `_fix_ref_params(src) == _s5_legacy(src)` 即 f(x)==f(x) 恒真；docstring 仍宣称「与 legacy 完全一致（防静默改判）」——该锁 C1 期对比的是独立实现（有漂移检测力），C2 别名化后**静默失效而 commit message 未声明**（message 只提 test2 的契约进化） |
| 6 | `test_c2_stage5_rewired_identity` | T1 子集 | 真锁（`_fix_ref_params`/`_build_var_types`/`_GB_REF_PARAM_TYPES` 身份）；**缺 `_fix_single_ref_arg` 断言**（T1 列了） |

- **「契约进化掩盖真回归？」裁定：掩盖面 = 锁失效，非已发生回归**。C2 测试 diff 仅 test2 重写 + test6 新增（`git diff acdc 6db -- tests/` 逐行核）；行为回归不存在（AST verbatim + 语料 0 差分 + 哈希全等三证）。但 test5 由真锁退化为恒真式**未经声明**，且设计 T2 要求的**绝对期望断言**（裸 `v15` + vt{value}→原样 / vt{array}→`v15[0]` / vt{ptr}→`*v15` / vt{}→`*v15` / Case2b `*stru_12AB`+ref_type→`*(struct gbVec3D *)&stru_12AB`）**从未落地**——当前 no-ctx 退化形仅由 test1 的 `GetAABBox(pBox)→*pBox` 一例间接覆盖。今后任何人「顺手修正」无门退化行为，**全绿测试不会红** = 禁静默改判契约失守。
- **ctx 证据门（F1a）路径绿测面零覆盖**：6 测全走无 ctx；test_ref_param_table_b 传 `None`；带 `_Ctx()` 的门测试在 `tests/codegen/test_stage5.py` 但**整模块 skip**（先存债 `4ab0a8535`，非本次引入）——而 C3 启用的恰是 ctx 路径。
- 设计 T3（`_build_var_types` kinds 五形断言）无专属测试（部分由 test_cast_reg_assignments 的 C2440 侧 51 测间接携带，实跑 51 passed）；T2 的 Case2b **改写行为**无断言（test_ref_param_table_b③ 仅锁表键存在）。
- **T6-T8（`tests/test_tos_stage_isolation.py`，同名双定义/阶段隔离/共享层禁上行三守卫）完全未建**——设计 C1 交付项，也是「双副本分叉」的机器棘轮，缺失使攻击点 5 的同类风险无自维护闸。
- 存量面核对：`test_ref_param_table_b` 实跑 **5 collected / 4 passed / 1 failed**（失败=设计 D1 存量红 `test_getaabox_cross_class_form_split`，GetAABBox 表未落，C8 范围）；C2 commit message「零收集」表述**与实测不符**（误述，非掩盖——4 条绿测实际仍在消费再导出面）。
- 既有 `tests/test_vtable_call_transform.py`（含 `test_form3_existing_tail_000_fold_is_preserved` 直调 s3）51 测全绿 ✓。

### 攻击点 4 —— 导入安全（双注册面）：**CONFIRMED SAFE（实证）**

- **sys.modules 全景审计**（复现测试文件 sys.path 三插 + 导入序）：`data`→`pipeline/gen/data.py` 单注册（repo 根 `data/` 无 `__init__.py`，namespace 份额被正规模块胜出——解析落点实证）；`pipeline.gen.tables`、`pipeline.gen.ref_params` 单注册；平铺 `tables`/`ref_params`/`stage5_fixup` 键**均 absent** ⇒ 无双执行面。
- **对象同一性**：`stage5.store is ref_params.store is data.store`（三同 id 实证）；`_GB_REF_PARAM_FUNCS` / `_GB_REF_PARAM_TYPES` 在 stage5↔ref_params 间 `is` 相同。stage5 用 `from data import store`（平铺）与 ref_params 同形 ⇒ 同键同对象；两处 `from pipeline.gen.tables import …` 同包形 ⇒ 同 dict。
- **导入形纪律**：全仓 ref_params 消费方仅 stage5（绝对形）+ tests/test_ref_params_tos.py（绝对形）——**无相对形/平铺形**，双注册陷阱（D7）结构上封死。stage5 平铺加载（`stages.stage5_fixup`）与 ref_params 包形加载并存时对象同一性成立（即问题所指场景，实测通过）。

### 攻击点 5 —— 遗漏面（孤儿引用/死 import）：**PARTIAL**（功能无碍，卫生与文档双副本不达标）

- **死 import 清点**（grep 消费面 + AST；pyflakes 未安装，代位执行）：stage5:566-567 导入 7 名中——`_NON_POINTER_LOCAL_KINDS`/`_DECL_KEYWORDS`/`_split_top_commas` **全仓零消费者**（设计 C2 明示「无外部消费者，不需再导出」，仍被导入）；`_fix_single_ref_arg` 仅被 skip 的 tests/codegen/test_stage5.py 消费；`_GB_REF_PARAM_FUNCS`（564）stage5 代码已不用，但被 test_ref_param_table_b / test_stage5 经再导出消费（设计允许「二选一注明」——**未注明**）；`_build_var_types`/`_fix_ref_params` 真消费（163/1127/1183 与 1357）✓。
- **孤儿注释三件**：①F81 引言块（569-573，描述已迁走的 `_GB_REF_PARAM_TYPES`）滞留 stage5；②`# Local kinds that are positive evidence…`（605-606）悬空（主语 `_NON_POINTER_LOCAL_KINDS` 已删，其后 5 空行）；③**F1b/F3 删键史注释块双份逐字并存**（stage5:575-603 与 ref_params 各一份，12/12、16/16 行全同）——定稿 C2 删除清单明文「F1b/F3 注释块（566-625 内随表走）」应**随表迁走**，实现改为「复制未删」⇒ 正是 `gotcha_dual_copy_table_divergence` 类登记证据漂移面（「误登代价>漏登代价」的史料将来会修一漏一）。
- `_GB_REF_PARAM_FUNCS` 是否仍被用（问题原文）：stage5 本体**不再用**；经再导出被测试用——判「测试兼容再导出」而非纯死 import，但须注明（现状仅 `[R99 阶段 3] 共享表` 旧注）。
- 回归面实跑：TOS 6/6 绿 · cast_reg+vtable 51/51 绿 · table_b 4 绿 1 存量红。

### 攻击点 6 —— D0' 预告核对：**CONFIRMED**（零越界、零污染）

- stage3_cleanup.py 状态：本地 `_fix_ref_params(code)`（:2166）+ 调用点（:2061）无 ctx + 尾折叠原件（:2248-2249）**全部原样**——C3 范围未被 C2 触碰 ✓。
- **引用污染扫描**：stage3/stage4/stage1/stage2/transform 对 `ref_params` **零 import/零引用** ✓；全仓 ref_params 导入方仅 stage5+测试（攻击点 4）。
- C2 范围核对：diff = stage5 3 hunk（旧域 562-906，恰覆盖 7 本地件+表块）+ tests 两处；`_strip_outer_parens`（C4）/`_call_return_type`（C5）仍在 stage5 原位原体未动 ✓ 单变量纪律成立。
- 补充：尾折叠对 stage5 幂等的「输入零残形」推论（设计未复验 #3）本次以终树 0 可折叠形 + 哈希全等 + 语料 0 差分三重实测销案。

---

## 3. 缺陷清单 + C3 开工前必修项

| # | 级别 | 缺陷 | 处置 |
|---|---|---|---|
| E1 | **高（C3 安全网）** | D0' 无门退化行为失去显式锁：test5 C2 后恒真（`_s5_legacy is _fix_ref_params`），docstring 仍宣称「防静默改判」；设计 T2 的绝对期望断言（vt 五形 + Case2b 形）从未落地 ⇒ 未来静默改判零机器看护 | **C3 前必修**：补绝对断言组（`Rotate(v10, v15)`(no ctx)→`Rotate(v10, *v15)`、vt{value}/array/ptr 三形、`*stru_12AB`+ref_type→`*(struct gbVec3D *)&stru_12AB`）；test5 改写为绝对断言或显式标注「仅身份自检」 |
| E2 | 高（C3 安全网） | 尾折叠幂等 `f(f(s))==f(s)` 无断言（设计 T5 明文）；幂等论证只剩 C2 哈希单兜底 | C3 前补 T5 幂等断言（含 `obj->_tail_000[3]` 二次应用仍跳过） |
| E3 | 高（C3 前置方法） | C1 态激活面普查（设计攻击点 1 修法第 3 步）未跑，Case2/2b/3 在 stage3 语料的差集分母未知 ⇒ C3 行为归因无对照系 | **C3 开工第一件事**：普查脚本对 decomp 语料双实现对拍出 (file, case-kind) 多重集 |
| E4 | 中 | F1b/F3 删键史块双份并存（stage5 未随表走）+ F81 悬空引言 + Local-kinds 悬空注释 | C3 前（或独立卫生微批）删 stage5 侧副本，史料留 ref_params 单份 |
| E5 | 中 | `_ref_positions` 死闭包未按 D5 丢弃，随迁入 ref_params（循环内每轮重建的死代码） | 补执行 D5：删 ref_params 内该 def（零行为 diff） |
| E6 | 中 | stage5 死 import：`_NON_POINTER_LOCAL_KINDS`/`_DECL_KEYWORDS`/`_split_top_commas` 零消费者仍导入（设计明示不必）；`_GB_REF_PARAM_FUNCS`/`_fix_single_ref_arg` 再导出未注明用途 | 删 3 死件；余 2 件加「测试兼容再导出」注释或随测试改源清理 |
| E7 | 中 | T6-T8 守卫测试（test_tos_stage_isolation.py）未建——同名双定义/阶段隔离/共享层禁上行三闸缺失（设计 C1 交付） | C3 前落地（否则 D3/D4 类双副本无机器棘轮）；本次 F1b/F3 双份即其价值实证 |
| E8 | 低 | 定稿 D6 处置失实：缺陷表称「C1 docstring 已列」，实物 charter 无 `_build_var_types`/C2440 共用声明，亦缺尾折叠幂等依据句 | ref_params docstring 补两句；设计文档 D6 处置栏更正 |
| E9 | 低 | tables.py 姊妹表互指注释未加（设计 C1 明确项，diff=0 实证） | 补一行注释（零行为） |
| E10 | 低 | 测试身份断言缺 `_fix_single_ref_arg`（T1 列名）；测试落位 tests/ 与定稿 pipeline/gen/ 不同（与任务书口径一致，仅记） | 补断言一行 |
| E11 | 信息 | C2 commit「test_ref_param_table_b 零收集」误述（实测 5 collected/4 绿/1 存量红）；test5 空转未在 message 声明 | 提交叙述勘误（不动代码） |

**C3 开工前必修（最小集）**：E1、E2、E3、E7（安全网+对照系）；E4-E6 建议同批顺手（皆零行为）；E8-E10 可并入 C3 提交前的卫生小节。另按设计纪律：C3 验证前必 `apply→export`，读数当场读，L1 数字带三限定。

---

## 4. 未复验清单

1. **C1 态行为差集普查的量**（Case2/2b/3 在 stage3 语料实际触发条数）——方法已给（设计攻击点 1 修法 3），本次未跑；C3 归因分母未知（=E3）。
2. **before 侧完整 loop 日志**已被 after 轮覆盖（同一路径覆写）；before 读数面靠 s4_baseline.json ratchet 前值（14:33）+ 设计文档记录间接佐证。建议 C3 轮起保留 before 快照（日志/哈希/manifest 三件套存档）。
3. **pal3/src_error、pal3/src_fake**：全仓 grep 无 python 写入者，但 shell/手工途径未穷尽；若属生成物则在哈希域外（当前无证据指向 stage5 影响面）。
4. **pyflakes 未安装**，import 卫生以 grep/AST 代位清点；正式 lint 未跑（E6 判定依据为消费面清点而非 lint 器）。
5. **解释器一致性**：本次测试语境跑于 `/usr/bin/python3`（3.10.12，pyenv shim 路由）；loop 生产语境的解释器与 pyc 缓存隔离面未逐一核对（两者各自实证干净，但「同一缓存」未证）。
6. `tests/codegen/test_stage5.py` 全模块 skip 的债（4ab0a8535）未考古：其「契约刷新」弱化断言（`assert 'Rotate(' in out` 形）是否仍符合现行契约未复核；该文件是当前唯一带 ctx 的门测试载体。
7. D1 存量红（test_getaabox_cross_class_form_split）形成时点未考古（设计未复验 #6 同源延续）。
8. 哈希法复原依赖 `sort` 语序与 `xargs` 分批稳定性——本机命中根摘要，跨环境复算未试（不影响本次结论，影响他人复现成本）。
