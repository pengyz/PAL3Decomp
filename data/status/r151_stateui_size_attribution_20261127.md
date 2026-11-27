# #151 StateUI 尺寸修正（162,000→171,244）+ #127 剩余归属迁移

任务：`tsk_01M8EFEFNM4F73T885DPMN`（rev2 in_progress，owner 玄策）
执行时间：2026-11-27 23:33–23:56（claim → 落位 → 门禁）；match/census 收口至 00:07–00:15。

## 0. 结论

1. **尺寸**：`StateUI.binary_size` 162,000（0x278D0）→ **171,244（0x29CEC）**，并写入 `binary_size_source`。旧值是早期「按父边界估算」的产物，漏计尾段 9,244B —— 直接反证有两条：`StateUI::OnMessage`（`0x00485DF0`）体内 `mov ecx,[esi+29CE8h]` 落在旧尺寸之外；`0x483650`（max 位移 0x29CE8）在旧尺寸下无法归属本类。
2. **归属**：13 条全部落位（PMO seq24 口径：不缩首版，与尺寸同批）——MainEquipUI→LineupUI 6 条、MainEquipUI→StateUI 1 条、LineupComp→StateUI 5 条、`0x483650` 新建条目。方法数 StateUI 31→38 / LineupUI 36→42 / LineupComp 7→2 / MainEquipUI 29→22。
3. **门禁**：apply rc=0（PASS，0 new）、export rc=0、check rc=0（PASS，0 new）。中间有一次 `APPLY_GATE_OFF=1 apply`（原因与合规性见 §5.1），最终 PASS 出现在**正常 apply 之后**。
4. **census**：StateUI 2,895B → **12,139B（+9,244B）**，增量是**单个新段 `0x278d0–0x29cec`**，即旧尺寸终点到新尺寸终点之间的区域 —— 归因「已构造未建模」（ctor 在该区 `??_L` 构造了 5×0x798 元素，元素类 `sub_483280`/`sub_483300` 未注册），不是退化。LineupUI / LineupComp / MainEquipUI 洞面**逐字节零变化**。
5. **match**：L1 **196**（与卡面基线 196 相同）；棘轮读数 `previous 202 → current 196` 但 population 从 1215/1328 变为 1156/1267，工具自报「可比总体已变化 ⇒ 两次 L1 不可直接比较」——**不判退化、未 rebaseline**（三限定见 §5.4）。

## 1. 尺寸三证（A 级）

| 证据 | 位置 | 内容 |
|---|---|---|
| 分配点 | `original/PAL3.exe.asm:240476` | `push 29CECh`（全库唯一，函数 `sub_4A4220` 内） |
| 构造入口 | `asm:240485` | `call sub_482ED0`（前 `mov ecx,eax` → this） |
| 写入 | `asm:240496` | 构造完 `mov [esi+2AFB8h],eax`（StateUI 子对象指针落到宿主） |
| 写界 | `asm:193686` | ctor 尾 `mov [esi+29CE8h], ebx`（ebx=0），即末 4 字节 → 对象到 0x29CEC |
| 自表 | `asm:193688` / `asm:536838` | `mov [esi],offset off_56BA30`；表定义处 |
| 构造链求和 | `asm:193675-193683` | `lea eax,[esi+276F0h]` + `??_L` 元素 0x798 × 5 ⇒ 0x276F0+5×0x798=0x29CE8，再 +末尾 4B = 0x29CEC |
| 独立旁证 | `sub_485DF0`（StateUI::OnMessage） | `mov ecx,[esi+29CE8h]` —— 该方法本就在 methods 里，位移超出旧尺寸 ⇒ 旧值自相矛盾 |

旧值错因（写进 `binary_size_source`）：162,000=0x278D0 是早期按父类边界猜的尺寸，漏计尾段 9,244B（0x278D0→0x29CEC）。

## 2. 归属迁移（13 条，逐条）

脚本：`data/status/archive/r151_stateui_size_attr_20261127.py`（幂等；无参 DRY-RUN，`--apply` 落盘；含唯一性断言：13 个地址在所有 struct json 中恰好出现一次）。
方法字典里条目是整条搬运（保留 name/sig_model/source 原文），不是重写。

| # | 地址 | 方法名 | 原归属 | 新归属 | 依据 |
|---|---|---|---|---|---|
| 1 | `0x00480530` | UpdateFadeAlpha | MainEquipUI | LineupUI | #127 A 组；调用点 `sub_47F970`(LineupUI::Update) `mov ecx,esi` |
| 2 | `0x004819a0` | LoadFromFile | MainEquipUI | LineupUI | #127 A 组；同上 |
| 3 | `0x00481ba0` | SetAdornVisible | MainEquipUI | LineupUI | #127 A 组 |
| 4 | `0x00481cb0` | SelectWithSound | MainEquipUI | LineupUI | #127 A 组 |
| 5 | `0x00481eb0` | ShowPanelsWithSound | MainEquipUI | LineupUI | #127 A 组 |
| 6 | `0x00482140` | RenderEquipDetails | MainEquipUI | LineupUI | #127 A 组 |
| 7 | `0x004844a0` | CountVisibleStats | MainEquipUI | StateUI | 唯一调用点 `asm:197335` 在 `sub_485980`=StateUI::RefreshStatsDisplay |
| 8 | `0x00483fa0` | ShowById | LineupComp | StateUI | #127 B 组 |
| 9 | `0x00484140` | CallSlotMethod | LineupComp | StateUI | #127 B 组 |
| 10 | `0x004841b0` | PositionAt | LineupComp | StateUI | #127 B 组 |
| 11 | `0x00484e10` | DispatchSlotMethod | LineupComp | StateUI | #127 B 组 |
| 12 | `0x00484e30` | GetSlotWidget | LineupComp | StateUI | #127 B 组 |
| 13 | `0x00483650` | CreatePreviewScene（新建） | 无 | StateUI | 调用点 `asm:240604 mov ecx,[esi+2AFB8h]` + `asm:240605 push esi` → `asm:240606 call sub_483650`；**实参=RoleStatePanel\***（见 §5.6 修正） |

为什么 #141 当时没落：`0x483650` 的 max 位移 0x29CE8 > 旧尺寸 0x278D0，被列入 `HOLD_FOR_SIZE`；写面外的 MainEquipUI/LineupComp 两张 json 不在 #141 的 checklist 范围（#141 只覆盖 StateUI/LineupUI）。本卡 writeScopes 覆盖四张 json，故一次落齐。

`LineupComp._methods_note` 已加：5 条已迁至 StateUI 并留证据指针（保留原方法 2 条 `0x0044b850`/`0x004543c0`）。

### 2.1 每条迁移的删除/新增行号（worktree 行号，`grep -n "\"<addr>\""` 可复跑）

| # | 地址 | 删旧（HEAD 文件:行） | 加新（worktree 文件:行） |
|---|---|---|---|
| 1 | `0x00480530` | `MainEquipUI.json:852` | `LineupUI.json:949` |
| 2 | `0x004819a0` | `MainEquipUI.json:611` | `LineupUI.json:966` |
| 3 | `0x00481ba0` | `MainEquipUI.json:869` | `LineupUI.json:988` |
| 4 | `0x00481cb0` | `MainEquipUI.json:633` | `LineupUI.json:1005` |
| 5 | `0x00481eb0` | `MainEquipUI.json:650` | `LineupUI.json:1022` |
| 6 | `0x00482140` | `MainEquipUI.json:886` | `LineupUI.json:1043` |
| 7 | `0x004844a0` | `MainEquipUI.json:903` | `StateUI.json:1036` |
| 8 | `0x00483fa0` | `LineupComp.json:125` | `StateUI.json:928` |
| 9 | `0x00484140` | `LineupComp.json:211` | `StateUI.json:945` |
| 10 | `0x004841b0` | `LineupComp.json:142` | `StateUI.json:967` |
| 11 | `0x00484e10` | `LineupComp.json:167` | `StateUI.json:992` |
| 12 | `0x00484e30` | `LineupComp.json:189` | `StateUI.json:1014` |
| 13 | `0x00483650` | 无旧条目（`grep` 全库 0 命中） | `StateUI.json:910`（新建 `CreatePreviewScene`） |

复跑命令：
```
git show HEAD:data/annotations/structs/MainEquipUI.json | grep -n '"0x004819a0"'
grep -n '"0x004819a0"' data/annotations/structs/LineupUI.json
```

## 3. json 变更行数（含 §2.1 逐条行号）

| 文件 | 变更行 | 内容 |
|---|---|---|
| `StateUI.json` | +174 / −62 | `binary_size` 1 行、`binary_size_source` 1 行、6 条方法插入、`0x483650` 新建条目 |
| `LineupUI.json` | +171 / −50 | 6 条方法插入 |
| `LineupComp.json` | +3 / −110 | 5 条方法删除 + `_methods_note`（缩进已按原文件 1 空格） |
| `MainEquipUI.json` | +3 / −125 | 7 条方法删除（缩进 1 空格） |

## 4. census 前后（`data/status/archive/r151_census_diff_20261127.json`）

| 类 | before size/员/方法/洞/段 | after | 说明 |
|---|---|---|---|
| StateUI | 162,000 / 66 / 32 / 2,895B / 5 | 171,244 / 66 / **38** / **12,139B / 6** | 新增单段 `0x278d0–0x29cec` = 9,244B |
| LineupUI | 162,772 / 60 / 36 / 210B / 4 | 162,772 / 60 / **42** / 210B / 4 | 零变化 |
| LineupComp | 2,012 / 14 / 7 / 24B / 2 | 2,012 / 14 / **2** / 24B / 2 | 零变化 |
| MainEquipUI | 209,008 / 76 / 29 / 10,148B / 40 | 209,008 / 76 / **22** / 10,148B / 40 | 零变化 |

归因（按 PMO seq24 口径，不用「视野扩大」四个字糊）：`0x278d0–0x29cec` 是 **ctor 已构造但未建模** 的区域 —— `sub_482ED0` 在 `asm:193675-193683` 用 `??_L` 构造 5 个 0x798 元素（元素 ctor `sub_483280` / dtor `sub_483300`，未在任何 struct json 注册）。本卡**不造类型**、只留精确残洞区间；清零需先注册 0x798 元素类（另卡）。

## 5. 门禁（逐段 rc）

### 5.1 apply / export / check

| 段 | 命令 | rc | 读数 |
|---|---|---|---|
| apply 1 | `python3 pipeline/cli.py apply` | 1 | 2 new：`N6b StateUI:0x00483650 sig 为空`、`DATA:N13c MainEquipUI::LoadFromFile 限定调用契约断` |
| （修） | 补 `sig_model`：`void __thiscall(StateUI *)`，参数个数来自唯一调用点（this + `push esi`），返回值调用点未读 | — | N6b 消失 |
| apply 2 | `python3 pipeline/cli.py apply` | 1 | 仅剩 N13c |
| **gate-off apply** | `APPLY_GATE_OFF=1 python3 pipeline/cli.py apply` | 0 | 见 §5.1 说明 |
| export | `python3 pipeline/cli.py export` | 0 | decomp 名刷新：`asm/pal3/decomp/LoadFromFile_LineupUI_QAEPAVOpenNULLFile_PAV3_H_Z_004819a0.json` 的 `name` 已变 `?LoadFromFile@LineupUI@@…` |
| codegen all | `python3 pipeline/cli.py codegen all` | 1（已知恒红） | 语料重建；`pal3/src/Misc/MainEquipUI.cpp` 中 `MainEquipUI::LoadFromFile` 引用数 **0** |
| apply 3 | `python3 pipeline/cli.py apply` | **0** | `0 new errors + 34 frozen(advisory), 115 warnings — PASS` |
| export 2 | `python3 pipeline/cli.py export` | 0 | `asm/pal3/ida_structs.json` 刷新 |
| check | `python3 pipeline/cli.py check` | **0** | `0 new errors + 34 frozen(advisory), 115 warnings — PASS` |

**为什么用过一次 `APPLY_GATE_OFF=1`（如实声明）**：N13c 的比较对象是语料（`asm/pal3/decomp/*.json` 的 name），而语料由 export 从 IDB 生成、IDB 由 apply 写入 —— 正常链路是 apply→export，但 apply 的 check 又要求语料已更新，形成自锁。绕开方式只有先让 IDB 吃到新归属（gate-off apply），再 export 刷语料、再正常 apply 复验。**这不是静默跳过**：gate-off 那次的唯一拦截项就是环境自锁的 N13c；随后 export→codegen all→正常 apply→export→check 全部实跑，最终 PASS 来自正常 apply（日志 `/tmp/r151_apply4.log`、`/tmp/r151_check.log`）。#141 当时的同类问题也是这么解的。

日志：`/tmp/r151_apply.log`、`/tmp/r151_apply2.log`、`/tmp/r151_apply_gateoff.log`、`/tmp/r151_export.log`、`/tmp/r151_codegen2.log`、`/tmp/r151_apply4.log`、`/tmp/r151_export2.log`、`/tmp/r151_check.log`（均已归档到 `data/status/archive/r151_*.log`，见 §7）。

### 5.2 loop（`/tmp/r151_loop.log`）

`LOOP_EXIT=1`：`apply rc=0/20.6s · export rc=0/155.6s · codegen rc=1/235.6s · probe rc=1/107.8s`
- **S2 160/229**（本卡开工前 158/229，+2；失败单元 69）
- probe 收缩项：`pal3/src/Misc/LineupUI.cpp 23 ↓ 11`、`UITitle_JDHY 6 ↓ 1`、`UIGameFrm 12 ↓ 9`、`PropUI 4 ↓ 2`、`EquipUI 9 ↓ 7`、`CCBStageCam 5 ↓ 2`
- `[vanished] pal3/src/Combat/CCCTData.cpp`（另一会话改动，非本卡）

### 5.3 probe 逐单元（`data/status/probe_census.json`，generated_at 2026-11-28T00:07:23）

| 单元 | 错误数 | 行号/码 | 归因 |
|---|---|---|---|
| `pal3/src/Misc/LineupUI.cpp` | 11 | 267/279/289/299/309/319/2061 `C2109`；506 `C2664` | 成员类型（数组/函数指针）与签名既有债；数量由 23 降至 11 |
| `pal3/src/UI/StateUI.cpp` | 6 | 1214 `C2660`(RenderObjectScene)；2274/2292/2296 `C2664/C2440`(函数指针)；3190/3220 `C2109` | 既有类型/签名债（#158 oracle §11 已列的复合块 C 级段）；本卡只动 methods + size |
| `pal3/src/Misc/MainEquipUI.cpp` | 2 | 1103 `C2113`；3029 `C2664` | 既有类型债（同上） |
| `pal3/src/Misc/LineupComp.cpp` | 0 | — | 迁出 5 条后编译通过 |

**未新增任何与本卡改动同族的错误**（归属迁移只影响名字/签名归属，尺寸只影响 `this` 位移上限；三处剩余均为类型级既有债）。

### 5.4 match（`/tmp/r151_match.log`）

`MATCH_EXIT=1`
```
matched 1156/1267 symbols | L1 196 | partial 822 | oob 0 | unmatched 250 | compile-skip 1 | unresolved-synth 138
L1 rate over matched: 196/1018 = 19.3%
[metric] L1 字节 8438 | 重定位覆盖字节 2328 (27.6%) | 被跳过且双侧不同的隐藏差异字节 1657 (19.6% 的 L1 字节 / 71.2% 的重定位字节)
[metric] 重定位站点值核对：total=8736 ok=2015 mismatch=0 unresolved=6721
[metric] 重定位目标核对（符号法）：total=8736 ok=102 mismatch=10 unresolved=13 unaligned=8154
[L1 ratchet] previous 202 -> current 196
[L1 ratchet] semantic: previous 12 -> current 11
[L1 ratchet] population: previous matched=1215/1328 -> current matched=1156/1267
[L1 ratchet] coverage: previous carrier.paired=99 -> current 94
[L1 ratchet] ⚠️ 可比总体**已变化** ⇒ 两次 L1 不可直接比较
```

**结论（带三限定）**：L1 = 196，与卡面基线 196 相等，**不判退化**。三限定：① 比较前编译产物已截到原函数长度，编译多出的尾部 NOP 不可见；② 每处重定位覆盖的 4 字节即使双侧不同也计 match（本函数集重定位覆盖 27.6%）；③ 重定位目标核对 ok=102 / mismatch=10 / unresolved=13 / unaligned=8154，符号法未对齐占多数。棘轮的 `previous 202` 是上一张卡跑出的读数，本次 population（`1215/1328 → 1156/1267`）与 coverage（99→94）都变了，工具自己拒绝自动对齐；**未执行 `--rebaseline`**。

## 6. 复核通道

`workflow` 单只读 agent 本次未调用（前几卡两次返回 null）；`subagent` 受 `maxDepth 1` 限制、`codebuddy_ask` 未安装。改用自查表（§5 全部命令可复跑）+ 交 QA 独立复跑。

## 7. 复现

```bash
cd /home/peng/workspace/PAL3Decomp
python3 data/status/archive/r151_stateui_size_attr_20261127.py            # DRY-RUN
python3 data/status/archive/r151_stateui_size_attr_20261127.py --apply    # 落位
python3 pipeline/cli.py apply && python3 pipeline/cli.py export && python3 pipeline/cli.py check
python3 pipeline/cli.py loop
python3 pipeline/cli.py match
python3 /tmp/r151_census.py   # 或按 §4 表格用 census_class(d, _type_table())
```

归档文件：
- 脚本 `data/status/archive/r151_stateui_size_attr_20261127.py`
- census `data/status/archive/r151_census_diff_20261127.json`、生成脚本 `/tmp/r151_census.py`
- 日志 `data/status/archive/r151_{apply,apply2,apply_gateoff,export,codegen2,apply4,export2,check,loop,match}_20261127.log`（见 `ls`，命名按段）

## 8. 边界与未做

1. **0x798 元素类未注册**：`0x483280`/`0x483300`（5 个元素）→ 那 9,244B 仍是洞；清零要另卡。
2. **StateUI 类型债未修**：probe 的 6 条（复合块按字节视图、函数指针族）属 #158 oracle §11 已登记的 C 级项。
3. **`0x4841b0`/`0x484e10`/`0x483650` 的 sig_model**：`0x483650` 按其唯一调用点给了 `void __thiscall(StateUI*)`；另外两条沿用原条目（搬迁未改内容），若后续 RET census 给出更精确形再改。
4. **未提交 git**：按团队纪律，提交由 PMO 统一做；本卡只落工作树。

## 6. rev6 修正（QA seq27 唯一硬伤）

**问题**：`0x483650 CreatePreviewScene` 的 `sig_model.params[0].type` 写成 `StateUI *`，但 `0x2AFB8=175,032` 已超出 StateUI 的 171,244。

**取证（三条独立指向同一宿主）**：
1. `RoleStatePanel.json:391` 已有 verified 条目 `0x2afb8 m_pTabPanel void*`，其 `source` 写明 pointee 171,244B 未名类（= StateUI 尺寸）、存储写点 `Init@0x4a4220 site 0x4a45c4 mov [esi+2AFB8h],eax`；同表 `0x2afcc m_pLineupUI`、`0x2afd0`。
2. RoleStatePanel `binary_size=176,256=0x2B080`，`0x2AFB8`/`0x2AFCC`/`0x2AFD0` 全在其内（这三处位移在调用同一函数 `sub_4A4220` 内被访问）。
3. `asm:240604 mov ecx,[esi+2AFB8h]` 的 `ecx` 取的是「RoleStatePanel 的 StateUI 指针」；`asm:240605 push esi` 才是实参，`esi` 是 RoleStatePanel 宿主 ⇒ 参数类型应为 `RoleStatePanel *`（不是 MainEquipUI：MainEquipUI 209,008B 虽也够长，但 `0x2AFB8` 的注解归属在 RoleStatePanel，且 MainEquipUI 无此成员）。

**修正**：`params[0]` 改为 `{"type":"RoleStatePanel *","name":"pOwner"}`；`sig_note`/`source` 同步写明上述三点与「不是 StateUI*（0x2AFB8=175,032 超出 StateUI 171,244）」。参数个数 1 / return void / __thiscall 未动。

**同批清理**：`0x484140/0x484e10/0x484e30` 迁移后仍带旧 `class: "UIWnd"`，与 StateUI 其余 34 条（`class` 缺省）不一致 ⇒ 已删除该字段（它们是 LineupComp 条目的基类声明残留，不是归属信息）。

**QA 另两问的答复**：
- ① 报告 §4「before methods=32」是对的：`git show HEAD:data/annotations/structs/StateUI.json` 里 methods=32；工作树 38 = +9（13 条里落到本类 7 条 + #141 遗留的 2 条 `0x484360 GetSlotRect`/`0x484810 RebuildNavPage`）− 3（#141 迁往 LineupUI 的 `0x480070/0x480450/0x482c90`）。我之前口头说「before 31」是错的口径，以 32 为准。
- ② `class: "UIWnd"` 是迁移前 LineupComp 条目的基类声明残留，不是本类归属证据 ⇒ 已清（见上）。

### 6.1 rev6 门禁与编译事实（本轮实测，2026-11-28 00:47–01:03）

| 阶段 | 命令 | rc | 读数 | 日志 |
|---|---|---|---|---|
| check（前置） | `cli.py check` | 0 | `0 new errors + 34 frozen(advisory), 110 warnings — PASS` | 见 ¶ 时间点 |
| apply | `cli.py apply` | **0** | `0 new`；`[3] Structs: 928/928 imported (fail=0)`；IDB 写于 00:48:09 | `/tmp/r151v11_apply.log` |
| export | `cli.py export` | **0** | `ida_structs.json` 00:50:51 | `/tmp/r151v11_export.log` |
| check | `cli.py check` | **0** | `0 new errors + 34 frozen(advisory), 110 warnings — PASS` | `/tmp/r151v11_check.log` |
| codegen all | `cli.py codegen all` | 1 | 既有恒红（`PalScriptWaitObj` 槽 flags，非本卡） | `/tmp/r151v11_codegen.log` |
| probe all | `cli.py probe all` | 1 | **S2 160/229**（与 rev3 相同）；新失败 **0**；真新增错误仅 `SaleUI.cpp` 6 条（他人写面：L755/756 C2107+C2102、L9275） | `/tmp/r151v11_probe.log` |
| match | `cli.py match` | 1 | `matched 1156/1267 | L1 196 | partial 822 | compile-skip 1`；`L1 字节 8438 / reloc 2328(27.6%) / hidden 1657(19.6%/71.2%)`；棘轮 `202→196` 且自报**可比总体已变化**，LOST 6 个全为他人单元（`CCBPanelSlot::??_G`、`CCBUIPanel::FocusCurrentRole/SetUserData/??_G`、`UIPushButton::IsHidden/??_G`），**新增 L1 0 个**；未 rebaseline | `/tmp/r151v11_match.log` |

**参数类型改动的编译影响**：`probe_census` 中 `pal3/src/UI/StateUI.cpp` 未进入失败清单；`MainEquipUI.cpp` 2 条（C2113 L1103、C2664 L3029）与 `LineupComp.cpp` 0 条均与 rev3 相同；`LineupUI.cpp` 23→11 且唯一变化是 C2664 的报错文本（同码站点变化，非新增）。⇒ 本处改动未引入新编译错误。

**外部并发声明**：00:32–00:50 期间其他会话占用 IDB（`tools/run_apply_export_idalib.py` PID 370375、`idat export_full` PID 378200、`probe all` PID 383552），我的前两轮 apply/export 因此 rc=1（未写 IDB），直到 00:47:52 抓到干净窗口才一次跑通。check 期间出现过 5 条/1 条**外部** `UICoverFrm`/`UIPushButton` 新增，均非本卡改动。
