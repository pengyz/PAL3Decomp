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
