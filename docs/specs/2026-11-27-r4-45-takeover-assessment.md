# R4 #45 失败现场接手评估

- 卡：#49（tsk_01M8CT7W0RHC7KWG94FVGZ），只读评估，writeScope 仅本文件。
- 评估对象：#45（tsk_01M8CMJ2J93KAHRP57QPH9，玄策，status=failed，卡仍 in_progress）。
- 取证时点：2026-11-27 04:55–05:0x（+08:00）；只跑只读命令与 `/tmp` 脚本 dry-run，未改仓库、未跑 apply/export/codegen/probe/loop、未重派/未关闭任何卡、未 commit。

## §0 结论

1. **A 落地一步都没开始**：`PalScriptWaitObj.json`（mtime 2026-11-23 17:31:21）与 `UICaption.json`（mtime 2026-11-23 23:13:24）对 HEAD 的 `git status` 与 `git diff --stat` 都是空 ⇒ 玄策停在「patch 与测试就绪」这一步（#45 seq2: 2 passed / 3 failed），04:52 截止后没有回退动作可做，因为从未写入。
2. **失败不是时间不够，是缺「写盘 + 全链」这一段**：patch45.py 只做 dry-run、测试仍是 3 红；A 的四条边界里，第①步（改两个 JSON）未执行，第③步（独占全链）未启动。
3. **A 的剩余工作比 patch 本身多**：除删 PSWO 的 0x0 成员、加 0x56AFA4 三槽表、删 UICaption 第二表外，还要补 slot0 的 name_note、处理「虚声明名来自 slot.name 而签名/定义走 methods」的断链、以及 `link_probe`（probe 只编译不链接，会漏 LNK2001）。
4. **baseline 的 192 与 #45 无关**：工作树 `s4_baseline.json` mtime **04:45:07**，同秒被写的还有 `pal3_registry.jsonl` / `s4_l1_identity_cur.json` / `s4_diff_detail.json`（一次 `cli.py match` 的四件产物）；`loop_match.log` 停在 03:12，04:45 这次是直跑 match；ratchet 行自报「可比总体已变化（symbols 1259→1265）」⇒ 两次 L1 不可直接比。因此 A 的验收条件「sha=f3aa8279」在现值上**不可执行**，必须换判据（见 §4）。
5. **建议**：lead 按 B 关闭 #45（交付物已齐，见 §2），另开一张「A 落地」卡（writeScopes 只含 3 个具体文件 + 独占窗口 + 允许 link_probe）；**不建议**直接重派 #45——team 无 `task.reassign` 动作、原卡写域不含 PSWO/UICaption、验收含已失效 sha（详见 §4）。

## §1 A 还差什么（逐项）

| # | 缺口 | 现状证据 | 补齐动作 | 风险/验证 |
|---|------|----------|----------|-----------|
| A1 | PSWO 仍是非多态 | `binary_size 8`、`vtables None`、members `['0x4','0x0']`（C2） | 删 `0x0 m_nTodo_000`；加 `vtables:[{addr:"0x0056afa4", slots:[3]}]`；`binary_size` 保持 8 | 布局回 24/28/24/24/24/152（#39 探针已证） |
| A2 | UICaption 仍带重复第二表 | `vtables` 两张：`0x0056afb0`(0 槽) 与 `0x0056afa4`(3 槽，`[None,None,None]`)，C3 | 删 `0x56afa4` 那张 | 删后 `UICaption.h` 不再发三个 virtual；需确认 IDB 旧表被清（见 A5） |
| A3 | slot0 未定名、无 name_note | patch45 里 slot0 写作 `PalScriptWaitObj_adjthunk`，字段只有 `source`，无 `name_note`（C5） | 按 PMO seq4：slot0 沿用 thunk 约定 + `name_note` 写同址证据；slot1=`GetType`、slot2=`UpdateFrame` | 命名铁律：不得新造无语义名，也不得落 `slot_N` |
| A4 | 虚声明的签名/定义断链 | 发声明时名字取 `_sl.get('name')`（`pipeline/gen/stages/emit_headers.py:3342`），但签名在无 methods 条目时回落 `void __thiscall()`（同文件 :3389 一带）；PSWO.methods 只有 `0x004a68d0`（C2），三槽地址不在其中 | 给 PSWO 补三条 methods 条目（或证明代码走「按名族投票」能取到正确签名），并确认生成的定义落在 PSWO | S2 只编译不链接 ⇒ 要 `link_probe --check`；否则 LNK2001/C2555 会被 S2 绿灯掩盖 |
| A5 | 删 UICaption 第二表后的 IDB 同步未验证 | `pipeline/ida/apply_annotations.py:508-511` 只对**无基类**类把 `vtables[0].slots` 注入 `virtual_methods`；UICaption 有基类 ⇒ 该路径不走 | 独占窗口 apply→export 后核 `UICaption.vtables` 只剩 1 张；否则 export 会把旧表带回来，codegen 再生成 dup（回路） | 这是 A 的验收里没写的必检项 |
| A6 | 验收判据不可执行 | 卡面写 `s4_baseline.json` sha=`f3aa8279…`；现值 `66c193fe…`（192，C6）；S2 需当场重取 | 删 sha 断言，换成「loop 无 REBASELINE 行 + L1 不低于现场读数 + 总体未变」；S2/错误/L1 全用当场读数 | 现场：S2 159/230、总错误 622、L1 192（03:49/04:45 读数，执行前须重取） |

> 补充：`tests/test_r4_screenfade_sizes.py`（156 行，untracked）本身是**正确的红测试**，不需要改它——A1/A2 落地后它会转绿。接管卡若只想让它变绿，不必写 `tests/`。

## §2 B 能交付什么（现有即可交）

| # | 交付物 | 证据 |
|---|--------|------|
| B1 | 五类尺寸真值已核，五个 fade/Mgr JSON **本来就不需要改** | #45 seq1 实测：`ScreenFadeIn` 28/base 24/1 员；`Out/White/White2` 24/base 24/0 员；`Mgr` 152/16 员；与 #34 二进制、#39 探针三方一致 |
| B2 | 病灶结论：PSWO 被标 POD 导致派生类 vfptr 抢 0、基类后移 4 | #34 §3 探针 + #45 seq1 反向控制（28/32/28/28/168、`m_nType@12`、`m_first@28`） |
| B3 | 红测试文件与其失败原因 | 现跑 `3 failed, 2 passed in 3.64s`；失败即 `test_pal_script_wait_obj_is_polymorphic`、`test_uicaption_has_single_base_vtable`、`test_generated_header_sizes_match_binary`（C2118 负下标，测试文件 :142，C4） |
| B4 | 可复用的补丁脚本（dry-run 安全） | `/tmp/r45/patch45.py` 跑完 rc=0、两 JSON mtime 与字节**未变**（C5） |
| B5 | 缺口清单与建议 | 本文件 §1/§4 |

⇒ #46 需要的是「尺寸已核 + 病灶 + 交接」，B 全覆盖；B 不包含「注解落地」，不应按 A 的绿测试验收。

## §3 写域与冲突

| 文件/目录 | 归属 | 接管 A 是否需要写 | 冲突判断 |
|-----------|------|------------------|----------|
| `data/annotations/structs/PalScriptWaitObj.json` | 当前无人持有（#45 原 writeScopes 不含它，PMO seq4 才扩权） | 是（A1） | 与所有在跑卡无交集 |
| `data/annotations/structs/UICaption.json` | 同上 | 是（A2） | 同上 |
| `tests/test_r4_screenfade_sizes.py` | #45（untracked 产物） | 不必写（只需跑） | 若接管卡把 `tests/` 写进 writeScopes，会与 #45/#46 的 tests 通道重叠 |
| `data/annotations/structs/ScreenFade*.json`、`ScreenEffectMgr.json` | #45 writeScopes | 否（值已对） | 接管卡不应重复纳入 |
| `data/status/s4_baseline.json` | 管线（match 写） | 否 | A 卡明确不重锚；恢复/接受 192 由 PMO 决定（§5 第 5 步） |
| `docs/knowledge/**` | #46 | 否 | #46 blockedBy #45；#45 关掉即解锁 |

结论：**只接 PSWO + UICaption 两项即可绕开 `tests/` 锁**——两个文件不在任何在跑卡写域里，红测试用现成文件跑（只读），不需要改测试。

## §4 两条路径与代价

### 路径 1（推荐）：关 #45 按 B 收口 + 新开「A 落地」卡

- 卡面：`writeScopes=[data/annotations/structs/PalScriptWaitObj.json, data/annotations/structs/UICaption.json]`（若允许补测试再加 tests 文件）；`blockedBy=[]`；允许跑 `link_probe`；要求独占窗口。
- 验收（可执行版）：
  1. `pytest tests/test_r4_screenfade_sizes.py -q` 5/5 绿；
  2. 编译期 `sizeof`：PSWO 8 / ScreenEffect 24 / FadeIn 28 / Out·White·White2 24 / Mgr 152 / UICaption 96 / Role 8704 / ChoseCompose 3772；
  3. apply→export 后 `UICaption.vtables` 长度 1、PSWO `vtables[0].slots` 3 且带 name/name_note；
  4. S2/总错误/L1 当场重取、不劣于读数基线（S2 159/230、错误 622、L1 192）；
  5. `link_probe --check` 不新增 LNK2001/LNK2005；
  6. `git diff --stat data/status/` 为空（不重锚）。
- 代价：一次卡流转（约 5 分钟）；收益：责任清晰、验收可执行、不污染 #45 的历史。

### 路径 2（不推荐）：直接重派 #45

- team 工具**没有** `task.reassign` 动作（此前实测，只能 close/新建）；
- 即使能改 owner，原卡写域仍是「五个 fade/Mgr JSON + tests/」，**不含** PSWO/UICaption（PMO 的扩权只在 thread 文本里）；
- 原卡验收含 `s4_baseline.json` sha=`f3aa8279…`，该值已不可达（现值 66c193fe）；
- #45 与 #46 的 blockedBy 关系需要一并重写，否则 #46 继续卡在 failed owner 上。

### 路径 3（否决）：把 A 塞进 #45 由 PMO 代跑

45 分钟时间盒已过期，且 A 从未开始；代跑与「成员不得替 owner 提交」的边界冲突。

## §5 给 PMO / lead 的一页动作清单

1. **关闭 #45，按 B 验收**：交付物＝五类尺寸已核（§2 B1）、病灶结论（B2）、红测试及失败原因（B3）、patch dry-run 证据（B4）、缺口清单（B5）。关闭理由写「A 未落地，B 内容已齐」。
2. **新开「A 落地」卡**：writeScopes 只写 `PalScriptWaitObj.json`、`UICaption.json`（如需要再单列测试文件）；`blockedBy=[]`；写清「独占窗口 + 允许 link_probe」。
3. **把命名裁决写进卡面**：slot1 `GetType`、slot2 `UpdateFrame` 准用；slot0 沿用 thunk 约定 + `name_note` 记同址证据，不许落 `slot_N`。
4. **替换验收判据**：删 sha 断言；加「export 后 UICaption 只剩 1 张表」「PSWO 三槽有 name/name_note」「link_probe 无新增」。
5. **baseline 处置二选一**（Human/PMO 定）：`git checkout -- data/status/s4_baseline.json` 回到 189，或书面接受 192 为当前基线；无论哪种，A 卡都不重锚，`loop_match.log` 已记录「总体已变」的理由（C8）。

## §6 复现命令与原样输出

C1（两文件时点与工作树状态）：

```
$ stat -c '%y %n' data/annotations/structs/PalScriptWaitObj.json data/annotations/structs/UICaption.json
2026-11-23 17:31:21.779253232 +0800 data/annotations/structs/PalScriptWaitObj.json
2026-11-23 23:13:24.131978745 +0800 data/annotations/structs/UICaption.json
$ git status --porcelain data/annotations/structs/PalScriptWaitObj.json data/annotations/structs/UICaption.json
（空）
```

C2（PSWO 注解结构）：

```
$ python3 -c "import json;d=json.load(open('data/annotations/structs/PalScriptWaitObj.json'));print('keys',list(d));print('binary_size',d.get('binary_size'),'vtables',d.get('vtables'));print('members',list((d.get('known_members') or {})));print('methods',len(d.get('methods') or {}), list((d.get('methods') or {})))"
keys ['name', 'binary_size', 'known_members', 'methods', '_adjudicated_tables']
binary_size 8 vtables None
members ['0x4', '0x0']
methods 1 ['0x004a68d0']
```

C3（UICaption 两张表、槽无 name）：

```
$ python3 -c "import json;d=json.load(open('data/annotations/structs/UICaption.json'));print('binary_size',d.get('binary_size'));[print(v.get('addr'),len(v.get('slots') or []),[s.get('name') for s in v.get('slots') or []]) for v in d.get('vtables') or []]"
binary_size 96
0x0056afb0 0 []
0x0056afa4 3 [None, None, None]
```

C4（红测试现状）：

```
$ PYTHONDONTWRITEBYTECODE=1 python3 -m pytest tests/test_r4_screenfade_sizes.py -p no:cacheprovider -q
tests/test_r4_screenfade_sizes.py:142: AssertionError
FAILED tests/test_r4_screenfade_sizes.py::test_pal_script_wait_obj_is_polymorphic
FAILED tests/test_r4_screenfade_sizes.py::test_uicaption_has_single_base_vtable
FAILED tests/test_r4_screenfade_sizes.py::test_generated_header_sizes_match_binary
3 failed, 2 passed in 3.64s
```

C5（patch45 dry-run 不写盘）：

```
$ stat -c '%y %s %n' data/annotations/structs/PalScriptWaitObj.json
2026-11-23 17:31:21.779253232 +0800 1727 data/annotations/structs/PalScriptWaitObj.json
$ python3 /tmp/r45/patch45.py
== PalScriptWaitObj changed: True
{...打印改后 JSON...}
== UICaption changed: True
{...打印改后 JSON...}
rc=0
$ stat -c '%y %s %n' data/annotations/structs/PalScriptWaitObj.json
2026-11-23 17:31:21.779253232 +0800 1727 data/annotations/structs/PalScriptWaitObj.json
```

C6（baseline 工作树 vs HEAD）：

```
worktree L1 192 symbols 1265 matched 1154 partial 826 sem 13
worktree sha 66c193fe51cd4752
HEAD L1 189 symbols 1259 matched 1152 partial 827
HEAD sha f3aa8279df6d0440
```

C7（04:45 写入集与 loop 日志时点）：

```
04:45:07.4465450730 s4_baseline.json
04:45:07.4495451730 pal3_registry.jsonl
04:45:07.4505452070 s4_l1_identity_cur.json
04:45:07.4655457070 s4_diff_detail.json
04:31:39 loop_apply.log
04:34:06 loop_export.log
04:37:12 loop_codegen.log
04:38:38 loop_probe.log
03:12:24 loop_match.log
```

C8（棘轮行，证明总体也变了）：

```
[L1 ratchet] previous 189 -> current 192
[L1 ratchet] semantic: previous 12 -> current 13 (L1+sem: 201 -> 205)
[L1 ratchet] population: previous matched=1152/1259 -> current matched=1154/1265
[L1 ratchet] coverage: previous carrier.paired=93 -> current 94
[L1 ratchet] ⚠️ 可比总体**已变化** ⇒ 两次 L1 不可直接比较
```

## §7 边界与自检

- 只读：本卡只读注解/测试/日志/代码与 `/tmp` 脚本 dry-run；未跑 apply/export/codegen/probe/loop/match；未改任何仓库文件（唯一新增本文件）；未重派/关闭卡；未 commit。
- 未覆盖：A 落地后的真实全链读数、IDB 旧表是否被 apply 清除（需独占窗口）、`link_probe` 结果——全部留给接管卡。
- 自述数字均由 §6 命令当场产出；四个时点（04:31/04:34/04:37/04:38 loop 链、04:45:07 match 写入）与 03:12 loop_match 的差异在 C7 中原样列出。
