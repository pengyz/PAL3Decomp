# PropUI 洞区落位交付报告（R7-T1 / #52）

- 日期：2026-11-27
- 卡号：`#52` tsk_01M8CKPBPG9BHJWGXWM9J2
- 结论一句话：**只要“尺寸定谳”一证不成立，后续所有成员偏移都不作数**；本卡先把 `sizeof` 收敛到二进制真值 28,892，再按 `#48` 执行清单逐段落位，洞 18,652B → **292B（12 段，全部为对齐间隙/未写区）**，并给出每段不能名字化的原因。
- 依据：`docs/audit/2026-11-27-propui-expectation-baseline.md`（#36）、`docs/audit/2026-11-27-propui-placement-exec-plan.md`（#48）、`docs/ui-inventory/2026-11-27-propui-span-ui-semantics.md`（#37）。

## §0 结论（六条，均可复跑）

1. **尺寸**：`binary_size` 从 29,056 改为 **28,892 = 0x70DC**。三证：①全镜像 `push 0x70DC` 仅 2 处（VA 0x45974f、0x523422，均 `push; call 0x55353b` 分配）②ctor `0x46D140` 最大写位移 `[esi+0x70D8]`（`0x46d49f` 写 1，随后 ret）③旧值 29,056 的溢出段（`mb_OK` 52B、`mb_OKRc` 16B、尾填 96B）在真 sizeof 之外，已删除。
2. **成员表**：`known_members` 95 → **50**；按 `#48` 48 行清单逐行映射（4 行间隙不落成员；B-/C 行只按 N 字节占位）。
3. **洞**：`PropUI.holes` 18,652B/45 段 → **292B/12 段**；12 段坐标与长度见 §3。全部为对齐间隙（16/20/32B）与 ctor 未写区（0x4D68 104B、0x70D0 8B）。
4. **全库洞**：前基线 820,294B（按 PropUI 差 18,360B=18,652−292 折算的期望值 801,934B）与实测 802,176B 并排；**折算值 ≠ 实测值（差 242B）**，这 242B 归并发卡对其它类的改动，全库差值不单独归因本卡。
5. **门禁**：`check` 0 new + 37 frozen / 111 warnings **PASS**；`apply`/`export` rc=0；`codegen` rc=1（已知恒红）；`probe` rc=1 且 S2 **159/230**（与基线等价）；`match` rc=0，L1 **192→192**（previous 192），无 LOST，未 rebaseline。
6. **独立复核已执行并落盘**：verdict `pass_with_fixes`；已按复核把 `m_aNum` 从 `int[3]` 改 `int[7]`（吸收 0x68A8–0x68B8 的 16B 且解释 float/byte 视图）；其余两条（bases 继承链、9 段“间隙有写点”）作为**已知债**记入 §6，不在本卡强断。

## §1 尺寸定谳（证据原文）

| 证据 | 指令/地址 | 说明 |
|---|---|---|
| 分配立即数 | `0x45974f`、`0x523422`: `push 0x70DC; call 0x55353b` | 全镜像仅 2 处；调用后均 `call 0x46D140`（PropUI ctor） |
| ctor 写界 | `0x46d49f: c6 86 d8 70 00 00 01` = `mov BYTE PTR [esi+0x70D8],1` | ctor 内最大位移=0x70D8 ⇒ 最小 extent 0x70DC；0x70D9 起无写（0x70D9–0x70DC 为尾部对齐） |
| 旧值反证 | 旧 `binary_size=29056(0x7180)` | 尾部 `mb_OK@0x6FB8`(344B)+`mb_OKRc@0x7110`(16B) 越出真 sizeof；旧值无任何 asm 立即数支持 |

## §2 落位表（50 员，按 #48 行号对照）

| 偏移 | 类型 | 名 | 级 | #48 行 | 说明 |
|---|---|---|---|---|---|
| 0x48/0x4c/0x50/0x54 | int×4 | bkWndX/bkWndY/m_ListWidth/m_ListHeight | 原 unverified | 2 | asm:163222-163226 写 800/600/300/400；名沿用既有语料名 |
| 0x58 | unsigned char[17504] | m_PropData | A | 3 | ctor `0x46d407 mov ecx,0x1118` + `0x46d44a rep stos`（0x4460=17504B 整块零填）；UpdateItemList `0x46dd41 rep movs` 同尺寸拷贝。**未用 st_Manager 类型**：st_Manager 仅 244B，会把 0x4460 容量判错；union 视图会让生成头 include `_ns_udts.h`，触发 `class tagRECT;` 前向声明缺陷（实测 _ns_udts.h 18→24 条 C2501/C2146），故用字节容量视图。 |
| 0x44B8–0x46DC | 13 员 | p_DealData/buf/remarkbuf/…/_isCreatable | 原 unverified | 4 | 保留既有（#48 行4 逐员待定；语料引用 p_DealData/buf/remarkbuf，不能删名） |
| 0x46E0 | UIFrameContainer | m_propPanelBk | A | 5 | `0x46d…` 构造 sub_4422E0；Frame.tga |
| 0x4778 | unsigned char[84] | m_frameBar | B- | 6 | 构造 sub_43D830(vt 0x56ACFC)；类名未证不写 UIFlexBar |
| 0x47CC | UIFrameContainer | m_buyFlag | A | 7 | BuyFlag.tga（只证“买”侧） |
| 0x4874 | unsigned char[344] | m_exitBtn | A- | 9 | sub_43A770；StpCtl\Exit；id 202h |
| 0x49CC | unsigned char[164] | m_categoryWord | A- | 10 | sub_43A160；6 个 *_word |
| 0x4A70 | UIFrameContainer[5] | m_unk_0x4A70 | A | 11 | `??_L 0x98×5`；用途未证 |
| 0x4DD0 | UIRoleDialog | m_roleDialog | A | 13 | sub_4A12F0；0x558 |
| 0x5328 | unsigned char[308] | m_modelView | B- | 14 | sub_439030(vt 0x56AC20)；Item\%s\%s.pol |
| 0x545C/0x5504/0x559C/0x5634/0x56CC/0x5774 | UIFrameContainer | m_unk_0x545C / m_topFrameL / m_topFrameRM / m_topFrameR / m_unk_0x56CC / m_listFrame | A | 15/17/18/19/20/22 | 各 152B，贴图证据见 #48 |
| 0x580C | UIFrameContainer[13] | m_itemGrid | A | 23 | `??_L 0x98×13` 止于 0x5FC4；旧 m_ListGrid[14] 数量/偏移都不符 |
| 0x5FC4/0x605C | UIFrameContainer | m_propTitleBk / m_unk_0x605C | A | 24/25 | — |
| 0x6104 | unsigned char[1208] | m_propListBox | A- | 27 | sub_43DFC0(vt 0x56AD40)，ctor 最大 +0x4B4 ⇒ 0x4B8=1208；类名待正名 |
| 0x65CC | int[8] | m_unk_0x65CC | C | 29 | 组头 32B，逐员待证 |
| 0x65EC/0x6744 | unsigned char[344] | m_btnSub/m_btnAdd | A- | 29 | `0x46d342/0x46d352` 两次 call sub_43A770，间距 344 |
| 0x689C | int[7] | m_aNum | C | 29 | 0x689C–0x68B8；复核指出 0x68B0 当 float 读、0x68B4/5 当 byte 写 ⇒ 混合视图，逐员待证 |
| 0x68B8/0x6950/0x69E8/0x6A80/0x6B28 | UIFrameContainer | m_infoPanel / m_unk_0x6950 / m_unk_0x69E8 / m_unk_0x6A80 / m_attrHead | A | 31/32/33/34/36 | — |
| 0x6BD0/0x6D3C/0x6EA4 | unsigned char[344] | m_yesBtn/m_dickerBtn/m_noBtn | A- | 38/40/42 | sub_43A770；Normal\Yes id206 / UnDicker / Normal\No id207 |
| 0x701C | UIFrameContainer | m_titleBar | A | 44 | Prop_word.tga |
| 0x70B4 | unsigned char[28] | m_unk_0x70B4 | C | 45 | 7 个标量，逐员待证 |
| 0x70D8 | unsigned char | m_bInitFlag | A | 47 | `0x46d49f` 置 1；读点 0x46ea8a 等 |

## §3 洞（12 段 292B）与“为什么不能闭合”

| 洞 | 长度 | 性质 | 为什么不落成员 |
|---|---|---|---|
| 0x4864–0x4874 | 16 | Exit 矩形复用区 | 该 16B 由 Exit 矩形（0x4864–0x4870）覆盖，属上一容器（0x4874 起）的矩形域，独立建模会与其语义重复 |
| 0x4D68–0x4DD0 | 104 | **有写点的间隙** | ctor `0x46d457/460/469/46f/475/47b/481/48b/495` 写 9 个字段（含 rect 68,150,65,86 + flags）；成员级语义无名字证据，按 #48 行12 不落；**不是空区**，见 §6 |
| 0x54F4–0x5504 / 0x5764–0x5774 / 0x60F4–0x6104 / 0x65BC–0x65CC / 0x6B18–0x6B28 / 0x6BC0–0x6BD0 / 0x6E94–0x6EA4 | 各 16 | 对齐间隙 | #48 判定为对齐 pad；其中 0x65BC/0x6B18/0x6BC0/0x6FFC 有 rect 写点（复核指出），成员级语义待证 |
| 0x6D28–0x6D3C | 20 | Yes 矩形复用 | 属 m_yesBtn 的矩形域 |
| 0x6FFC–0x701C | 32 | No 矩形复用 | 属 m_noBtn 的矩形域 |
| 0x70D0–0x70D8 | 8 | **有读点的未写区** | 0x46f2c8/2d6/2e5 读 [0x70cc]/[0x70d4]/[0x70d0]，OnMessage 有 `*(UIFrameWnd **)&this->m_unk_0x70B4[28]` ⇒ 0x70D0 是对象指针域；语义待证，暂不落 |

合计 292B（工具口径）；若把 0x46DD[3] 与尾 0x70D9[3] 两段 char pad 计入则 298B，均 ≤1,500B 目标。

## §4 门禁读数（本卡实测）

| 阶段 | 结果 |
|---|---|
| `python3 pipeline/cli.py check` | `0 new errors + 37 frozen (advisory), 110–111 warnings — PASS`（并发卡改动导致 warning 数波动；归档 `data/status/archive/r7_t1_propui_check_20261127.log` sha256 4f036710…，该次 110 warnings/0 new） |
| `apply` | rc=0（20.8s） |
| `export` | rc=0（146.1s，后因 m_aNum 修正再跑一次 rc=0） |
| `codegen all` | rc=1（已知恒红，非本次引入） |
| `probe all` | rc=1；S2 **159/230** |
| `regression_detector --check --report` | 新失败 0；真新增仅 `pal3/src/Misc/SaleUI.cpp` 6 条（C2107×4+C2102×2，#9 在途既有 codegen 族）；本卡单元 `PropUI.cpp` **4→1**（剩余 1 条为 `0x118[this->i]` 常量当下标的既有 codegen 族），`UITitle_JDHY 6→1`、`UIGameFrm 12→9` |
| `cli.py match` | rc=0；`matched 1154/1265 | L1 192 | partial 826 | unmatched 248 | compile-skip 0 | unresolved-synth 136`；`[metric] L1 字节 8317 / reloc 2320(27.9%) / hidden 1653(19.9%/71.2%)`；棘轮 previous 192→192、semantic 13→13、population 1154/1265 稳定；**无 LOST、未 rebaseline** |
| census | 前快照 `data/status/archive/struct_holes_before_propui_20261127.json`（sha256 `18c3bcfdd169d655…`，由 git HEAD 版注解按 v3 口径内存重算）：`29056 / 95 员 / 18,652B / 45 洞`；后快照 `struct_holes_after_propui_20261127.json`（sha256 `75f55e881ca4ec4f…`）：`28892 / 50 员 / 292B / 12 洞`；全库前基线 `820,294B`，按其减 PropUI 差得到的折算值 `801,934B`；实测 `802,176B / 1,040 洞`（**折算值 ≠ 实测，差 242B 归并发卡对其它类的改动**；全库数不单独归因本卡）；文件 `data/status/struct_holes_20261125.json` sha256 `75f55e881ca4ec4fdf7daf34d3179b6d4945f1b179db5a3c5b37d90a31588c2d`；快照 `data/status/archive/struct_holes_after_propui_20261127.json`（同 sha） |

## §5 与 #48 清单的对账（差异及原因）

- 清单 48 行 → 注解 50 员：行2 拆 4 个 int、行4 保留 13 个既有员、行29 拆 4 段（扁平化，避免 inline struct 让生成头 include `_ns_udts.h`）、行3 直接用字节容量视图（不用 st_Manager 类型，原因见 §2）。
- 清单 39 段口径与本表 12 段的差异：`#36` 的 39 段是「按 span 粗分」，落位后洞的计算口径（census v3 对齐感知）只把**未被任何成员覆盖**的字节算洞；0x58 块 21 段、0x64BC–0x6950 等段已被整块/单员覆盖，故不再计入。
- 旧成员删除 73 条、新增 25 条、改名 26 条（大小写/语义），逐条 diff 见 `git diff data/annotations/structs/PropUI.json`。

## §6 独立对抗复核（只读 agent，非本卡脚本）与处置

- verdict `pass_with_fixes`；A/C/D 通过（尺寸、0x58 块、0x580C/0x4DD0/0x6104/0x65EC/0x6744/三按钮/0x70D8 均独立复现）。
- **已修**：`m_aNum int[3] → int[7]`（复核证据：ctor `0x46d371` 写 `[edi+0x2dc]`=0x68A8 第 4 dword；OnMessage `0x46f53f` 把 0x68B0 当 float 读；`0x46f4f7/fd` 写 0x68B4/5）⇒ 洞 308B→292B，消除生成代码越界索引。
- **未在本卡裁决（记为已知债，建议单开卡）**：
  1. `bases` 仍是 `UIFrameWnd`，但 ctor 首调 `0x46d162→0x43dcd0` 写 vtable **0x56AD20=UIListBox**（UIFrameWnd ctor 写 0x56ACB8）；两者均 72B，sizeof 不受影响，但继承链与二进制不符（#48 行1 已明“改 bases 另证”）。
  2. 上述 9 段“间隙有写点”：0x4D68（9 写点）、0x65BC/0x6B18/0x6BC0/0x6FFC（rect 写点）、0x68A8（已被 m_aNum int[7] 吸收）、0x6D28（0x6D38 写）、0x70D0（对象指针读）。它们的**字节归属**已在 §3 说明，但成员级语义/类型需逐案取证。
  3. `m_unk_0x*` 9 处命名：本卡按卡面“命名留白走 `m_unk_<offset>`”执行；复核引用 2026-11-15 命名铁律认为应正名——两者冲突，按“证据是否足够命名”逐条待证后正名（正名卡）。
  4. `methods` 缺 `0x46F2C0`（读 0x70CC/0x70D0/0x70D4），本卡不越界补。

## §7 台账

- `ev_0023`（已登记，A/open）：PropUI 真 sizeof=0x70DC 三证 + 50 员落位与 12 段洞逐段性质。
- `ev_0024`（已登记，A/open）：0x58 块必须用 17504B 容量视图（st_Manager 244B 不足；union 视图触发 `_ns_udts.h`/`tagRECT` 生成缺陷）。

## §8 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp
# 1) 尺寸与 ctor 写界
objdump -d -M intel original/PAL3.exe | grep -n "70dc" | head
objdump -d -M intel --start-address=0x46d140 --stop-address=0x46d4b0 original/PAL3.exe
# 2) 0x58 块整块清零
objdump -d -M intel --start-address=0x46d3f0 --stop-address=0x46d460 original/PAL3.exe
# 3) 落位脚本（干跑 / 写盘）
python3 data/status/archive/r7_t1_propui_placement_20261127.py
python3 data/status/archive/r7_t1_propui_placement_20261127.py --apply
# 4) 改名收口路径（语料刷新后才能过 check）
APPLY_GATE_OFF=1 python3 pipeline/cli.py apply && python3 pipeline/cli.py export
python3 pipeline/cli.py check
# 5) census / 回归 / match
python3 tools/census_struct_holes.py
python3 tools/regression_detector.py --check --report
python3 pipeline/cli.py match   # 读 [metric] 行与 L1 ratchet
```

## §9 边界自证

- 仅改 `data/annotations/structs/PropUI.json`、`data/status/archive/`（脚本/日志/快照）、本报告；
- **未**改任何基线文件、**未** `--rebaseline`、**未**改 `pipeline/` 与 `st_Manager.json`（后者非本卡写面，块容量用 PropUI 内字节视图表达）；
- S4 `s4_baseline.json` rows 的 population 变化来自并发卡（#19 等）与 match 默认刷新，本卡未显式重锚。
