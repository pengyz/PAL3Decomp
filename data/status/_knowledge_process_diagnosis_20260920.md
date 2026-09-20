# 知识与方法论沉淀诊断 + B34 事故复盘（2026-09-20）

> 来源：① 用户发起的"知识/方法论沉淀"统一诊断（只读子 agent，报告全文见会话）；
> ② B34 事故的独立对抗性复核（只读子 agent，含 `/tmp` 隔离编译实验）；
> ③ 主 agent 的再核实。**本文件只固化结论与证据指针；子 agent 报告全文未落盘（教训见 §5）。**

## 0. ⚠️ 先更正主 agent 自己的一处**错误声明**（已证伪）
`CLAUDE.md` 中"2026-09-20 已把它们（codegen 注解直读）**全部收敛**到 `annotation_view`"——
**被独立复核证伪** ✗。实测**仍有 3 处直读**：
| 位置 | 读什么 |
|---|---|
| `pipeline/gen/stages/emit_headers.py:3259-3260` | `data/annotations/globals.json` |
| `pipeline/gen/ast_transform.py:336-342` | `structs/*.json`（`json.load(open(...))`）|
| **`pipeline/gen/stages/stage3_cleanup.py:107-110`** | `structs/<Cls>.json`（**此前不在任何违规清单里** ✓ 新发现）|
⇒ **待办**：修完这 3 处后，才能把 `CLAUDE.md` 的措辞改回"全部收敛"；**当前应改为"尚有 3 处"**。

## 1. B34 事故复盘（P0：此前**全仓零文档** ✗）
**做了什么**：一批 5 处注解改动（4 处 `reattribute` + 给 `Scene` 加按值成员 `m_combatTaskData: tagCombatTaskData`）。
**结果**：`probe` **新失败 76、S2 ok 76→0、总错误 2150→2354**；`s2_total` 206→208。
**根因（独立复核的隔离编译实验，决定性）**：
- 罪魁是**把 `0x004236D0` 的新名写成 `tagRoleSlot`（= 类名）** ⇒ codegen 发成**构造函数声明** ⇒
  `tagRoleSlot` 从 trivial 变 **non-trivial**；而它是 `PalScript` 的 `union { tagRoleSlot slot; … }`
  （`PalScript.json` `known_members["396"]` → 生成 `pal3/src/Script/PalScript.h:94-95`）的**按值成员**，
  而 `globals.h:24` 让**每个 TU** 都包含它 ⇒ **208 个单元各报一次 C2620** ✓
- **实验（仓内 MSVC6 SP0，/tmp）**：平凡→通过；**只加 ctor（名=类名）→ C2620**（消息逐字一致）；
  **只加 dtor→C2623**（不同码）；ctor+dtor→只报 C2620；**普通成员函数名→通过**
  ⇒ **充分条件是"类有 ctor/dtor"，与"方法属不属于该类"无关。**
- **附带故障**：改归属**新增 2 个 TU**（`tagRoleSlot.cpp`/`tagCombatTaskData.cpp`）⇒ 新 TU 的 include
  集缺 `free_functions.h` ⇒ `tagRoleSlot.cpp(122) C2065 'GetActorMgr'`。
- **主 agent 的两处误判（已更正）**：① 我曾断言"按值成员 `m_combatTaskData` 导致 C2079" ✗ ——
  三份 census 里 `C2079` **全为 0**，且 `emit_headers.py:1045-1051` 表明 **codegen 本就会为按值成员自动补 include** ✓
  ⇒ **"补 include"处方无效** ✓；真缺陷是 `Scene` 的 5 个尾部成员与 `tagCombatTaskData` 对
  `[0x78650,0x78664)` **同字节双重主张** ✗；② 我把错误地址当成 `UISystem.cpp:95` ✗ ——
  真址是 **`pal3/src/Script/PalScript.h:95`** ✓（`pipeline/snapshots/snapshot.py:77` 用 `unit` 而非
  `e['file']` 拼 `_raw_errors`，把**头文件错误压平成"当前单元名+头文件行号"** ✗✓）
**恢复**：注解回退 **不够** ✗ ⇒ 必须 **`apply → export → codegen → probe`**（IDB + `asm/pal3/ida_structs.json`
都是 stale 层 ✓）⇒ 实测 **15:44→15:48 四步回到 76/2150/719** ✓，**无需** `init --force`/清 IDB ✓
**证据归档**：B34 的**唯一原始记录**是 `pipeline/snapshots/data/20260920_153924/`（gitignore ✗）⇒
已复制到 **tracked** `data/status/archive/20260920_b34_incident/`（commit `29f83ecc6`）✓
（指纹：`s2_ok=0 s2_total=208 total_errors=2354 C2620×208` ✓）
**新增门禁**：`tools/check_union_member_triviality.py` ✓ —— 扫"被按值用作 union 成员的类"，
禁止其有 ctor/dtor 形态方法（名=类名 或 `~类名`）。**全集只有 2 个**（`tagRoleSlot`/`tagTeamSlotsBOverlay`）⇒
一条小检查即可永久拦住整类事故 ✓ **注入式自检通过**（给 `tagRoleSlot` 注入 `tagRoleSlot()` ⇒ 报错 ✓）

## 2. 过程性知识**基本没有沉淀**（诊断报告的核心结论）
- **工作流 SOP 不存在** ✗：流程碎在 **7 处**且互不一致（`CLAUDE.md` 检查点表**缺 probe 一步**且已自知未修；
  `pattern_annotation_fix_batching.md` 最接近 SOP 但**无回退判据**；`pipeline/cli.py:806-810` 才是 Canon 五步；
  skill/command 的流程**完全没有 probe/match** ✗；`_longterm_plan.md:3` 自称"唯一前进路线"却是**孤儿文档（0 入链）** ✗）
- **调查方法**未沉淀（`docs/knowledge` 零命中）：`??_L` 定位元素 ctor/dtor · 构造/分配点字面量锁尺寸 ·
  **asm `[reg+imm]` 优先于 decomp `this+N`**（会按错误元素尺寸缩放 ✗）· 注入式负例 · 对抗性复核
- **两起事故都不在 `docs/knowledge`** ✗（含审计已记录的 `--help` 覆盖产物事故 ✗）——
  **违反 `docs/knowledge/README.md:13` 自己的规则**（"门禁失效/流程漏洞这类最贵"）
- **知识库类型退化**：32 条中 **gotcha 24 条（75%）**、**debug 0 条**、decision 只有 1 条且被误放在 References ✗
- **索引不全**：**5 条未进 `MEMORY.md`**（含唯一近似 SOP 的 `pattern_annotation_fix_batching` ✗）、
  **7 条 frontmatter 不合规**（其中 1 条完全无 frontmatter ✗）、**kairos 断档 23/32**（09-18 一天产生 14 条却无 kairos ✗）
- **沉淀断层**：`_audit_toolchain_pipeline_20260920.md`（12K 高价值审计）**没有被蒸馏进 knowledge** ✗
  ⇒ **审计 → status → 消失**，没有 status → knowledge 的通路 ✗
- **元教训**：两起 `--help` 事故的回滚验证是"与 HEAD 逐字节一致" ✓，但**没有留下注入式负例** ✗
  ⇒ **"回滚成功" ≠ "门禁能防住下一次"** ✓

## 3. 过时清单（P0 摘要，完整清单见会话内诊断报告）
| # | 内容 | 硬证据 | 处置 |
|---|---|---|---|
| 1 | `docs/decompilation_workflow.md:75` 判据"L1 ≥ 5、ok ≥ 53/198" | 实测基线 **L1 34 / ok 76/206** | 改写 |
| 2 | `CLAUDE.md:172-176` "146 个失败文件 + 四项占比" | 实测失败 **130** | 改写/加时间戳 |
| 3 | `CLAUDE.md:44` "**无实时字节验证**" | 与 `cli.py match` + `compare_pal3.py` + `s4_baseline.json` 直接矛盾 ✗ | 删除该条 |
| 4 | `.claude/hooks/check-gstack.sh:4` 要求 `$HOME/.claude/skills/gstack/bin` | 该目录**不存在** ⇒ 在 Claude Code 下**所有 Skill 调用被恒 deny** ✗ | 修/删 |
| 5 | `.project/project.yaml:6` `ida_path: /opt/ida/idat64` | 不存在；真身 `/home/peng/ida-pro-9.1/idat` | 改正 |
| 6 | `.project/plugins/.../annotation-guide/SKILL.md` 的 `name:` 写成 **`pal3-pipeline`** | 与 `.claude/skills/annotation-guide`（116 行）不同 | 删除/重命名 |
| 7 | `.gitignore:114 docs/superpowers/` 与"已跟踪 35 个文件"自相矛盾 | 与刚修过的 `tools/ghidra` 同型 | 统一 |
| 8 | `docs/superpowers/**` **45 文件**（2026-05-01~**06-22** ✗ 不止 5 月）、**35/45 零入链**、引用不存在路径 214/74 次 | `asm/pal3a/` 已不存在 | 归档（不删）|
| 9 | `docs/pal3/**`(5, Ghidra 期)、`docs/iterations/**`、`docs/requirements/**`、`.claude/pal3_workarounds.md`、`.aide/project-design.md`、`.omo/plans/*` | 引用不存在命令/路径；数字作废 | 归档 |
| 10 | `.project/knowledge/knowledge.db`（SQLite schema 完整但 **4 表全 0 行**，05-22 后无写入）| 第三套知识库已死 ✗ | 显式废弃 |
| 11 | 文档腐化 **70 个不同路径 / 330 次引用**（含 `data/status` 则 77 个）| 本轮实测 | 加 `tools/check_doc_paths.py` 防复发 |

## 4. 冲突与重复（危险项）
1. **gbUI 修复方向冲突**：`arch_gbui_seven_slot_vtables_inheritance_chain.md:38`（"补 `base_class` 继承链"）vs
   `decision_sceneobj_composition_not_inheritance.md:34`（"**不是 base_class，是行表注册制**"）⇒ **应遵循后者** ✓
   （前者是**被后续轮次推翻的 v2**；其自称 `confidence: 85` **反而高于**乙方的 80 ✗ ⇒ **该字段无仲裁力** ✓）
2. **"唯一前进路线"的归属**：`_longterm_plan.md:3` 自称唯一且优先，却从未被作废 ✗，而今天在用/已交付的是
   `_architecture_cleanup_plan_20260920.md` 系列 ⇒ **接手者会读到一份自称权威的旧路线图** ✗ —— **最危险的隐性冲突** ✓
3. **`export` 红线措辞**：`CLAUDE.md:74` 绝对禁止 vs `export_full.py` 的 **8 处 `[t4-DECLARED-EXCEPTION]`**（已复核"合理，不删" ✓）⇒ 措辞应改为"仅经声明的 8 处例外" ✓
4. **证据等级**：全仓并存 **8 套**（不是 6 套）且**无映射表** ✗；`CLAUDE.md:77` 指向的"置信度规则表"**有两份互相冲突的定义**（skill 的 A–D vs command 的 A/A+/B/C/D ✗）；注解里有 **~95 处 `A:decomp_*` 自标 A** ✗ 而 taxonomy 规定"Hex-Rays 文本 = C、禁止单独用于偏移修改" ✗ ⇒ **偏移合法性无法机械复核** ✓

## 5. 本文件自身的教训（沉淀通路问题）
诊断报告与复核报告**全文只存在于会话上下文里** ✗ —— 若会话结束即丢失 ✓
⇒ 这正说明缺的是**通路**：**subagent 报告 → status 文档 → knowledge 条目** 三步里，
我只做了第一步的"读"，没有落盘 ✗（本文件是补救 ✓，但仍是**摘要**而非全文 ✗）
⇒ **建议**：以后派 subagent 做审计时，**要求它把报告写入指定 tracked 路径** ✓（而不是只发消息 ✓）

---

# 附加：第三份复核（"两层验证"架构方案）的**决定性更正**（2026-09-20）

> 来源：用户发起的"两层验证"方案对抗性复核（只读子 agent，含 3 个已确认无写盘的只读工具与 asm 实读）。
> **它推翻了我（主 agent）的一处关键证据，并纠正了框架** ✓

## A. 我的断言被**证伪**的
| 我的断言 | 裁定 | 复核证据 |
|---|---|---|
| P1 "`Scene` 的 1100000 是**几何比值**检查发现的" | **证据错** ✗（结论"存活 113 天"对 ✓） | `tools/audit_layout.py:70-71` 阈值 3×/50×，而 `git show 32326e886^` 的 `Scene.json` 前缀比值 = 1,100,000/1,099,748 = **1.0 ⇒ 永不触发** ✗（该函数 docstring `:451-461` **自己就写明这个盲区**）；真值来自 **asm**（BSS 跨度 `0x16932C = 493156×3`），而**线索来自一条编译错误** C2664 ⇒ **编译层是"触发者"**，迟钝的是**所有以 `binary_size` 为界的检查** ✗ |
| P2 自洽≠正确 | **成立且远比我说得严重** ✓ | pre-fix `Scene.json`：14 成员、递增、**0 重叠**、末端 1,099,748、余量仅 252 ⇒ 内部完全自洽却 **2.231× 偏大** ✓；更强的是：**`check_annotations.py` 现在报 `0 errors, 13 warnings — PASS`，而全库 881 个 struct 里有 91 个 `binary_size > 3× 最大成员末端`** ✗（9 个精确 = 2×，即 `safe_size = max_offset*2` 指纹 ✗）⇒ **现有闸的判别力 ≈ 0** ✓ 仓库自己的 `pipeline/decomp_quality.py:105-112` 原文："this check is DILUTED… **zero power**… needs an **IDB-independent size source**" ✓ |
| P4 "`audit_structural_attribution` 应与 asm `[reg+imm]` 一致" | **部分成立，其中一条是重复劳动** ✗ | ✓ check1 同源恒真；✓ 该工具的偏移取自 decomp `this+N`（报 2571，asm 真值 `[ebp+505Ch]`=20572，**8× 差**）；**但** `tools/attribution_offset_match.py:8-13` **早已**用 asm `[reg+imm]` 并**就举了 CIniFile×8 这个例子** ✓，实跑 `--func 0x4EC700` 得正确字节偏移 ✓ —— 它**只缺一个 `--scan`** ✗；另 `scan_misattribution` 的分子是**真二进制**，弱的是**参照物**（取注解 `binary_size` ⇒ 循环 ✗）|
| P5 杠杆选择 | **杠杆选错** ✗ | "一致性门禁"这条杠杆**已被占满且有反证**（0 errors PASS 而 91 个尺寸污染 ✗）；"修偏移来源"**已有实现** ✗ ⇒ **唯一真正缺的是"独立于注解的尺寸/归属证据源"** ✓ |

## B. 复核者发现的、我**没提到**的两个窗口
1. **`tools/codegen_invariants.py` 完全零调用** ✗（grep 无调用者；`audit_layout` 只被 `test_smoke.py:72` 断言"能跑"；`--strict-geometry` 默认关 ✗）⇒ 一个**秒级、可判别**的门禁**根本没接线** ✓
2. **`alloc_sizeof.json` 已有 17 条 ctor-anchored 尺寸 MISMATCH** ✗（Camera 544 vs **12956**、ScreenEffectNode 1060 vs 220、UIListBox 1760 vs 1208、JusticeBookUI 56192 vs 11404…），而 `_land_sizes.py` **只硬编码落地了 8 条** ⇒ **8 个类仍未落地** ✓

## C. **框架的准确表述**（原"两个层面"需修正）
C++ 结构体布局**由注解直接生成**（`emit_headers.py` 发 `_gap_*`/`_tail_*`，`:1780/:1895/:1995`），Hex-Rays 缺口（stage1–5）**只补语句、从不补布局** ✓；且 `export_full.py` 的 **8 处 `[t4-DECLARED-EXCEPTION]`** 直读注解 ⇒ `ida_structs.json` 是"**注解的复制**"（761/761 ✓）——**这正是 check1 同源恒真的根** ✓
**⇒ 准确模型**：**一个声明源（注解）+ 两个消费者（IDB→Hex-Rays；codegen→C++）+ 一个裁判（exe/asm）** ✓
**⇒ 错误有三类**：**(a) 注解主张错**；**(b) 注解正确但通路错**（C2208 型）；**(c) codegen 改写错** ✓
⚠️ **其中 (b) 对任何"层 1 门禁"天生不可见** ✗✓ —— **这是原方案最大的未言明盲区** ✓
（复核还列举：`gotcha_codegen_multi_inheritance_anon_member` 明载"注解数据本身没错"，是 apply 写入侧未调 `set_baseclass()` + export 读取侧用 `umoffset==0` 猜基类 ⇒ **经 globals.h 炸穿全部 205 个 .cpp** ✗；另有 include 图、vfptr 隐式 +4 位移、`_variants` 致 −20 漂移、**归属双源 27 条**）

## D. "问题都压到编译层"**不成立** ✗
编译前**已有**：`check_annotations`（仅内部一致性）、`audit_layout` 的 1b+2/3/4、`codegen_invariants`（秒级、可判别）、`alloc_sizeof`/`alloc_point_size`（真·二进制）、`mi_base_offsets`（真·二进制）、`attribution_offset_match`（asm）、`audit_vftable_offset0` ✓
**真问题三件**：**(i) 接线缺失** ✗；**(ii) 参照物用错**（4–5 个消费点全以**被污染的 `binary_size`** 为界；A 级纪要 **AT-200**（`_cleanup_scan_attribution.json`）已判"binary_size 被撑大/占位值污染，使 attribution/misattribution 门禁**全部失效**：52 个 struct" ✗）；**(iii) 缺独立尺寸源** ✗

## E. "函数归属"**不能**用用户提的判据独立验证 ✗
① **MI/子对象**：本文件 §1 的 CCBRoleState 就是实例（`this` 是基类子对象 ⇒ `this->m_x` 解析不到 ⇒ 净 +6 ✗，两次尝试全回退 ✓）；② **δ 不可换算**：实测 **179 个有基类的类只有 11 个带 base offset（94% 缺）** ✗，`mi_base_offsets.py` 自述该缺口 = 741 错误 / 38 文件 / 23% ✓；③ **参照物污染** ✗；④ **函数名不可信**（`gotcha_attribution_signal_limits`：`?GetEditorTaskDescription@CEffShock@@` 实为 ctor、`??0CEffShock` 实为工厂 ✗）✓
**⇒ 更强判据（用本仓既有积木）**：vtable 写表签名 ∧ `operator new(N)`+ctor（alloc_sizeof）∧ **`??_L/??_M` 元素尺寸字面量**（133 站点；实读 `PAL3.exe.asm:11956-11963` 的 `push 0x2200; push 5; call ??_L` ⇒ **sizeof(Role)=8704**，正是 8928 的反证 ✓）∧ ctor vfptr 安装次序 ⇒ **偏移越界只能作"侦察信号"，不能作结论** ✓

## F. 成本（实测，非估）
整轮 ≈ **11–20 min**（git 时间戳实测；文档化"~15 分钟" ✓）；分解：**export 是重活**（"数分钟到十几分钟" ✗）+ codegen 83s + probe 93s + match 131s ≈ 5 min；`probe s2` = 21s ✓
**⇒ 挂在 `cli.py check`（apply/export **之前**）才省得多** ✓；只挪到 codegen 前只省 ~4 min ✗；**真正收益是避免用被污染的 `binary_size` 定修正方向** ✓
**拦得住**：Role/Scene 通胀（**提前 113 天** ✓）、AT-200 的 52 个、17 条 MISMATCH、27 条 signature/JSON 矛盾、`CCBProtectWindow` 176 vs 2632 ✓ **拦不住**：C2208 型、include 图、C2620、vtable 深水区 ✗

## G. 复核者给出的**应做清单（ROI 序）** —— 与我原方案不同 ✓
1. **接线 `codegen_invariants.py`（含 check C）到 check/codegen** ✓ 分钟级零新逻辑；拦 27 条 signature/JSON 类名矛盾、`__vftable` 残留、`sub_` 形参不一致（check C 先 WARN+白名单 ✓）
2. **新增 `??_L/??_M` 元素尺寸审计器** ✓（133 站点；取 ptr/size/count/ctor/dtor，**用 ctor 指针锚定元素类**再比对 `binary_size`）—— 拦 Role 8928→8704 及全部内嵌数组元素尺寸 ✓⚠️ 风险：**弱判据无效**（8704 同时匹配 `RoleSystem` ✗）⇒ **必须 ctor 锚**；而 **ctor 归属本身可能错**（`sub_411CA0` 被注成 `~PalScript` ✗）
3. **把 `alloc_sizeof` 的 17 条 MISMATCH 做成显式台账门禁** ✓（替代 `_land_sizes.py` 的 8 条硬编码）—— 拦 Camera 12956 vs 544 等 ✓⚠️ **不可自动落地**（混有 base-subobject/phantom：UIStatic 248 vs 152、CCBUI 116 与 2632 ✗）
4. **`binary_size` 证据分级 + placeholder 标记**（2× 指纹 / 无独立源）⇒ 让所有 offsets-vs-size 判据在 placeholder 类上**拒绝出结论** ✓（消费点：`decomp_quality.py:102`、`audit_layout`、`check_annotations:600`、`scan_misattribution:142`、`audit_structural_attribution`）
5. **`attribution_offset_match` 加 `--scan`；作废 `_structural_contradictions.json`** 并把引用改指 asm 重算产物 ✓（含 `_attribution_evidence_20260919.md`/`_size_evidence_20260919.md` 的 max_offset 数字，3/20 已过期 ✓）
6. 把 1–5 **挂到 `cli.py check`（apply/export 之前）**，并让 `apply_annotation_batch.py --run-pipeline` 也过这道门 ✓（审计已指出它绕过钩子且跳过 L1 ✗）
7. （可选）全局相邻地址/BSS 跨度上界：`binary_size(T) ≤ next_global_addr − this_addr` ✓

## H. **不应该做**（复核明确）
❌ 再造"一致性/重叠/越界"门禁（**已存在，0 errors PASS 而 91 个尺寸污染，边际收益 ≈0** ✓）
❌ 把几何比值当尺寸真值（**1.0 永不触发**；14 条 HIGH 已被裁定为"成员缺失、尺寸可能正确" ✓）
❌ 只修 `audit_structural_attribution` 就算完 ✗ ❌ 把"前置省 15 分钟"当主要动机 ✗（省的是**跑错方向那一轮**，不是每轮 ✓）
❌ 用 `check`/`audit_layout` 的 PASS 当"布局正确"证据 ✗ ❌ 未建锚点前批量改 `binary_size` ✗
❌ 继续引用 `_structural_contradictions.json` 及派生文档的数字 ✗
⚠️ **复核对我漏掉的风险的两条点名**：① **层 1 门禁对"注解正确但通路错"（C2208，炸穿 205 个 .cpp）完全无判别力** ✗；② **层 1 自身的"归属双源矛盾（27 条）"无人消费** ✗ —— 这比"能否从二进制验证"**更便宜也更该先修** ✓

## I. 复核者主动交代的**自我证伪**（值得学习）
它最初怀疑 `CIniFile` 是"array-of-self ⇒ 假阳性"，**读 asm 后推翻**：`add edi,4` 写 4 字节值（`gbVFile*[100]` 形态），0x4ED0 属一个 ~20.6KB 对象 ⇒ **该条是真阳性** ✓（与仓库既有裁定一致 ✓）⇒ 维度错的方向是**假阴性**（k·N>N 只会漏报 ✓）；但该工具 docstring 那句"可证明…必然不属于该类"**仍不成立**（无法区分"尺寸错"与"归属错"，必须靠第二判据消歧 ✓）
