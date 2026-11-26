# R6-T1：UITitle_JDHY 洞区落位（先裁尺寸 377,700 → 290,488，再落成员）

Task: `tsk_01M8C7XM594N6XS49XHJDM`（#23）· 执行：玄策 · 日期：2026-11-26/27
状态：**注解已落位、check PASS、loop 全链已跑、census 已落档**；本卡不改基线、不 rebaseline。

---

## §0 结论（先看这一段）

1. **尺寸定谳：0x46EB8 = 290,488**（注解旧值 377,700 / 0x5C364 在二进制里 0 命中）。
2. 成员从 28 员（全部 `unverified`、source 全为 `annotation`）重建为 **43 员**，每条 source 带 ctor/方法 VA 与证据等级。
3. census v3：该类洞 **19,396B → 8B**（14 段 → 1 段），满足「≤1,500B」验收线；全库洞字节 875,232 → 848,196。
4. 门禁：`cli.py check` = **0 new errors + 37 frozen(advisory) / 111 warnings — PASS**；loop 的 codegen rc=1 为已知恒红（TOLERATED），probe rc=1 由外部 SaleUI（#9 在途）+ ScreenEffectRingNode（#19 拆类）造成，**本卡单元无新失败**；`match` 单独补跑 RC=0，**L1 189 → 189，无 LOST，未 rebaseline**。
5. 独立对抗复核（workflow 单 agent，只读、未复用本卡脚本）抓出**四处被误判为「洞」的活跃成员**（0x11B0/0x25AF4-0x25B6C/0x45B38/0x45EAC），已全部补落位并复算；该类最终只剩 0x160–0x168 的 8B 无证据空档。

---

## §1 尺寸裁决（卡面要求①：三选二对账）

| 证据 | 内容 | 级别 |
|---|---|---|
| 分配点 | `original/PAL3.exe.asm:240584` `push 46EB8h` → `0x4A46DE call 0x4B01D0`（operator new + ctor）；全 `.text` 该立即数**唯一一处**（0x4A46B5 处指令，NEW 站点 0x4A46DE），调用者 `sub_4A4220`（=?Init@EquipUI）存入 EquipUI+0x2AFD0 | A |
| 构造闭包 | ctor `sub_4B01D0` 建链末端：3×UIRoleDialog @0x45EB0/0x46408/0x46960，`0x46960 + 0x558 = 0x46EB8` | A |
| 向量跨度 | Note_Item 向量参数 `push $0x24`(36)、`push $0xDE8`(3560B)、ptr 0x262C8 ⇒ `0x262C8 + 36×0xDE8 = 0x45768`，与下一个对象起点精确重合 | A |
| 反证 | `5C364h` / `377700` / `0x5C364` 全 disasm（471,544 行）命中 **0**；旧注解 28 员全部 `unverified` | A |

结论：**377,700 是跨构建形状（旧 99 项布局），本 exe 从未构造过它**；正确尺寸 290,488。

---

## §2 落位成员表（43 员，按偏移）

证据等级口径：A=指令里 reg+disp32/立即数直证；B=直证 + 一处语义推定（名字-偏移对应）；C=仅靠空档推定偏移；D=名字迁移但类型/位置均未取证。

| 偏移 | 名称 | 类型 | 级 | 依据（VA） |
|---|---|---|---|---|
| 0x48 | rc | tagRECT | B | 语料引用 14 次；0x48–0x58 恰为 16B 空档（旧注解同偏移同型） |
| 0x58 | m_nWidth | int | A | ctor `0x4B0200 movl $0x320`（800）；全库 17 个 UI ctor 同形 |
| 0x5c | m_nHeight | int | A | ctor `0x4B0207 movl $0x258`（600） |
| 0x60 | buf | char[256] | C | 语料引用 33 次；0x60–0x168 为 264B 无访问块，256B 可落（0x60+0x100=0x160）；**偏移为推定** |
| 0x168 | m_unk_0x168 | unsigned char | A | ctor `0x4B020E mov %bl(0)` |
| 0x16c | m_unk_0x16c | int | A | ctor `0x4B0214 mov %ebx(0)` |
| 0x170 | m_OutFrameT | UIFrameContainer | B | ctor `0x4B01F6 lea` + `call 0x4422E0`（vtable 0x56ADD0=UIFrameContainer，152B） |
| 0x208 | m_OutFrameR | UIFrameContainer | B | `0x4B021F`；步进 0x98 |
| 0x2a0 | m_OutFrameL | UIFrameContainer | B | `0x4B022F` |
| 0x338 | m_OutFrameB | UIFrameContainer | B | `0x4B023F`；与旧注解偏移精确重合（名字-偏移锚点） |
| 0x3d0 | m_background | UIFrameContainer | B | `0x4B024F` |
| 0x468 | m_unk_0x468 | UIFrameContainer | A | `0x4B025F`；无语料名，占位 |
| 0x500 | m_exit | unsigned char[344] | D | 语料引用 1 次；旧注解 UIButton@0x478 与 ctor 布局不符，迁到首个 344B 对象（`0x4B026F lea 0x500; call 0x43A770`，vtable 0x56AC70 未登记）；**类型未取证，不宣称 UIButton** |
| 0x658 | m_unk_0x658 | unsigned char[8][344] | A | `0x4B0276..0x4B02EF` 八次 lea + call 0x43A770；8×344=0xAC0 → 0x1118 |
| 0x1118 / 0x11c0 / 0x1258 | m_unk_* | UIFrameContainer | A | `0x4B02FF/0x4B030F/0x4B031F` + call 0x4422E0 |
| 0x11b0 | m_unk_0x11B0 | int[4] | A | 本类方法 `0x4B3E7A lea 0x11b0`、`0x4B3E80` 写 0x11b4、`0x4B3E8C` 写 0x11b8(0x94)、`0x4B3E8F` 起读写 0x11bc |
| 0x12f0 / 0x136f0 | m_unk_* | unsigned char[128][584] | A | 向量构造：`push $0x4B47E0`(dtor)/`$0x4B4690`(ctor)/`$0x80`(count)/`$0x248`(584B)/ptr；128×584=0x12400 |
| 0x25af0 | m_unk_0x25AF0 | int[8] | A | 本类方法成组写：`0x4B3ED2`(0x25AF4)、`0x4B3EDD`(0x25AF0)、`0x4B3EEC`(0x25AF8)、`0x4B3EFB`(0x25AFC)、`0x4B4025` 起(0x25B00/B04/B08/B0C) |
| 0x25b10 | m_unk_0x25B10 | int[6][4] | A | `0x4B4100-0x4B4249` 六组、步进 0x10、每组 +0/+4/+8/+0xC，最高 0x25B6C |
| 0x25b70 | m_unk_0x25B70 | unsigned char[12] | A | ctor `0x4B04D7 lea`、`0x4B04E7/ED` 写零 0/4、`0x4B04F5` 写零 0x25B78；字节索引消费 `0x4B2C7E/0x4B3A89/0x4B3BF5/0x4B4406` |
| 0x25b7c / 0x25c14 | m_unk_* | UIFrameContainer | A | `0x4B0379/0x4B0389` + call 0x4422E0 |
| 0x25cac / 0x25da4 | m_unk_* | UIPushButton | A | `0x4B0399/0x4B03A9` + call 0x440740（vtable 0x56AD88，248B） |
| 0x25e9c | m_unk_0x25E9C | unsigned char[3][344] | A | `0x4B03B9..0x4B03E4` 三次 lea + call 0x43A770；3×344=0x408 → 0x262A4 |
| 0x262a4 | m_isItemShow | unsigned char[36] | B | ctor `0x4B04E5 lea 0x262A4` + `rep stos` 9 dword=36B 清零；按项写 0/1（`0x4B18F9/0x4B1E6E`）、按索引读（`0x4B2110/0x4B2163`）；36 项与 Note_Item[36] 一一对应（对应关系为 B 级） |
| 0x262c8 | m_NoteItem | Note_Item[36] | A | 向量构造 `push $0x454AA0/$0x4549A0/$0x24/$0xDE8`；36×0xDE8=0x45768 |
| 0x45768 | m_unk_0x45768 | unsigned char[2][344] | A | `0x4B040B/0x4B041B` + call 0x43A770 |
| 0x45a18 | m_unk_0x45A18 | int[4] | A | `0x4B0C6A lea`；`0x4B0C76` 写 +4=0x42、`0x4B0C80` 写 +8=0x28E、`0x4B0C90` 写 +0xC=0x1F7 |
| 0x45a28 / 0x45b40 / 0x45c50 | m_unk_* | unsigned char[272] | A | ctor `0x4B042B/0x4B043B/0x4B044B` + call 0x43BCE0（vtable 0x56ACD8=UIScene）；`0x43BCE0` 本体最高写 0x10C ⇒ 272B；**UIScene.json 344B 与实测冲突，本卡不引用该类型尺寸** |
| 0x45b38 | m_unk_0x45B38 | int[2] | A | `0x4B1593`/`0x4B1599`（0x45b38/0x45b3c），`0x4B1EBA-1FFF`、`0x4B32D7-32F4` 反复读写，`0x4B2005 fildl` |
| 0x45d60 / 0x45df8 | m_unk_* | UIFrameContainer | A | `0x4B045B/0x4B046B` + call 0x4422E0 |
| 0x45e90 | m_unk_0x45E90 | int[7] | A | ctor `0x4B0486`=0x5C、`0x4B0490`=0x262、`0x4B049A-0x4B04AC` 清零 0x45E98/9C/A0/A4、`0x4B04FB` 清 0x45EA8；读点 0x4B0ED8/0x4B1607/0x4B1934 |
| 0x45eac | m_unk_0x45EAC | unsigned char | A | `0x4B38CF movb $1,0x45eac`（OnMessage 0x4B3470 内）；其后 3B 为对齐填充 |
| 0x45eb0 / 0x46408 / 0x46960 | m_unk_* | UIRoleDialog | A | `0x4B047B/0x4B04B7/0x4B04C7` + call 0x4A12F0（vtable 0x56E190，1368B） |

尺寸乘法链：`0xB0?` 不适用本节；本类链为
`0x170+6×0x98=0x500`、`0x500+9×0x158=0x1118`、`0x1118/0x11C0/0x1258`（三容器，首尾与 0x11B0/0x12F0 衔接）、`0x262C8+36×0xDE8=0x45768`、`0x45768+2×0x158=0x45A18`、`0x46960+0x558=0x46EB8`。

---

## §3 旧 14 段洞的去向（卡面要求②：逐段结论）

旧洞（19,396B）→ 新布局下的处置：

| # | 旧洞段 | 旧字节 | 处置 |
|---|---|---|---|
| 1 | 0x1f0–0x1f8 | 8 | **假缝**：旧注解把 UIStatic 按 0xA0 步进，真实 UIFrameContainer 按 0x98；0x1f0 落在容器 0x170–0x208 内 ⇒ 闭合 |
| 2 | 0x290–0x298 | 8 | 假缝，落在 0x208–0x2a0 内 ⇒ 闭合 |
| 3 | 0x330–0x338 | 8 | 假缝，落在 0x2a0–0x338 内 ⇒ 闭合 |
| 4 | 0x3d0–0x3d8 | 8 | 与真实容器 5 起点 0x3d0 重合 ⇒ 闭合 |
| 5 | 0x470–0x478 | 8 | 落在容器 0x468–0x500 内 ⇒ 闭合 |
| 6 | 0x566ec–0x5a7e4 | 16,632 | 整个 99 项布局在真布局中不存在（超出 0x46EB8）⇒ 随尺寸裁决消失 |
| 7–11 | 0x5a87c/0x5a91c/0x5a9bc/0x5aa5c/0x5aafc | 5×8 | 同上，全部 ≥0x5a7e4 > 0x46EB8 ⇒ 消失 |
| 12 | 0x5b4b4–0x5b4dc | 40 | 同上 ⇒ 消失 |
| 13 | 0x5b63c–0x5b64c | 16 | 同上 ⇒ 消失 |
| 14 | 0x5b920–0x5c364 | 2,628 | 同上 ⇒ 消失 |

新布局剩余 1 段：**0x160–0x168 = 8B**，原因见 §5。

---

## §4 census 与门禁读数（卡面要求③⑤）

### 4.1 census v3（2026-11-27 00:39 重跑）

- 该类：`{"cls":"UITitle_JDHY","size":290488,"members":43,"bases":1,"holes":[["0x160","0x168",8]],"hole_bytes":8,"total_holes":1}`
- 全库：`total_hole_bytes` 875,232 → **848,196**（−27,036）；`total_holes` 1,109 → 1,105。
- 逐类账（与 2026-11-26 23:15 快照 `data/status/archive/struct_holes_after_sefmgr_20261126.json` 对比）：
  `UITitle_JDHY −19,236`（本卡）、`SaleUI −7,684`（#9 在途）、`ScreenEffectMgr −16 / ScreenEffectNode −4 / ScreenEffectRingNode +64`（#19 拆类）、`CEffGroupNode −4 / UI3DModelNode −4`（其它在途），合计 −26,884；之后又发生并发改动，现总数 848,196。
- 产物：`data/status/struct_holes_20261125.json`（sha256 `802b3d824e88222e61d3066e924fdcdb40a4b743879289a2bec0f01bf1dc7361`）。

### 4.2 check / loop / match

| 门 | 读数 | 说明 |
|---|---|---|
| `cli.py check`（改后） | **0 new + 37 frozen(advisory), 111 warnings — PASS**（EXIT=0） | 首跑曾 8 new（语料仍引用旧名 rc/buf/m_OutFrameT-R-L-B/m_background/m_exit），按「名字保形、偏移按 ctor 改正」修复后归零 |
| loop（00:22–00:30） | apply rc=0/19.9s · export rc=0/157.4s · codegen rc=1/197.1s（恒红容错） · probe rc=1/91.1s（早停） | probe 失败非本卡单元 |
| probe 归因 | 新失败 0；真新增 6 条全在 `pal3/src/Misc/SaleUI.cpp`（C2107×4、C2102×2；#9 在途）；本卡单元 `UITitle_JDHY.cpp` 6 错 → **1 错** | 1 错 = L2042 `C2109`，来自 `(0x56F314)[v10]` 这种「常量当下标」的 Hex-Rays 产物，属 codegen 侧，不是注解 |
| `cli.py match` | RC=0；`matched 1139/1248 | L1 189 | partial 816 | unmatched 244 | unresolved-synth 134`；`previous 189→189`、`semantic 13→13`、`population 1139/1248→1139/1248`、`coverage 94→94` | **无 LOST、未 rebaseline** |
| `[metric]` | L1 字节 8191；重定位覆盖 2312(28.2%)；隐藏差异 1647(20.1%/71.2%)；站点值 ok=1901 mismatch=0；符号法 ok=101 mismatch=10 | 三限定随数字（截断/长度相等/重定位 don't-care） |
| population 变化归因 | 1262→1248 来自 #19 拆出 `ScreenEffectRingNode.cpp`（新单元 fail 1 条 C2039 pCullObj），非本批；本批前后两次 match population 完全一致（1139/1248） | — |

---

## §5 不可闭合段（卡面要求③的「给原因」）

**0x160–0x168（8B）**：类方法窗口 0x4B01D0–0x4B4800 内对 0x160..0x167 零访问；若 `buf` 取 264B（填满 0x60–0x168）则洞为 0，但 buf 的真实长度无二进制证据（旧注解写 256B，属 D/C 级）。本卡选择**保留 8B 洞并标注 C 级偏移推定**，不把猜测写成成员。

---

## §6 独立对抗复核（checklist⑥）与据此的修正

复核方式：workflow 单 agent（只读、未复用本卡落位脚本，独立 objdump + 独立洞复算）。结论 `pass_with_fixes`。

**已据其修正的四处（关键）**：
1. `0x11B0–0x11C0` 不是洞：`0x4B3E7A lea 0x11b0`、`0x4B3E80/0x4B3E8C` 写 0x11b4/0x11b8、`0x4B3E8F` 起读写 0x11bc ⇒ 落 `int[4]`。
2. `0x25AF4–0x25B70` 124B 不是洞：`0x4B3ED2/0x4B3EDD/0x4B3EEC/0x4B3EFB` 与 `0x4B4025` 起、`0x4B4100-0x4B4249` 成组写满 ⇒ 落 `int[8] + int[6][4]`。
3. `0x45B38–0x45B40` 8B 不是洞：`0x4B1593/0x4B1599` 写两 dword，ScrollDown/Up/UpdateTextPosition 反复用 ⇒ 落 `int[2]`。
4. `0x45EAC` 4B 不是洞：`0x4B38CF movb $1` ⇒ 落 `unsigned char`（其后 3B 对齐填充）。

**原文表述错误已改**：
- 报告/线程里「0x46960+3×0x558」算法写错，正确是 `0x46960+0x558=0x46EB8`（3 个 UIRoleDialog 起点 0x45EB0/0x46408/0x46960）。
- 0x25AF0 旧 source 写「其余 124B 无任何访问证据」——被 0x4B3ED2 起同函数写点直接证伪，已重写。
- 0x45A28 的「相邻步进 0x110」对首对不成立（0x45A28→0x45B40 跨 0x118，其中末尾 8B 是独立成员 0x45B38），已按 272B+8B 成员拆开。
- 0x468 的 source 原先复制了「名字沿用语料」的措辞（实际是 m_unk），已改为中性描述。

**复核指出但不在本卡写面裁决的既有缺陷（如实记录）**：
- `methods["0x0056f33c"]` 把 **vtable 地址**登记成 `UITitle_JDHY` ctor（该址在 .rdata，不可能是函数），而真 ctor `0x4B01D0` 被登记为 `DestroyPages`；
- 多个 method 的 `_misattrib_evidence.class_size` 是别类的尺寸（1208/4280/39240/204），与 `max_offset` 对账时失真；
- `InitPageState` 的 naming_note 仍写「extent (377,700B)」。

⇒ 建议单开「UITitle_JDHY methods 归属/尺寸证据清理」卡（写面含 `data/annotations/functions/`），本卡不动 methods。

---

## §7 台账

- `ev_0013`（A/open）：UITitle_JDHY 尺寸 = 0x46EB8/290,488；`push 46EB8h` 唯一 + ctor 末端闭合 + Note_Item 向量闭合；377,700 零命中。
- `ev_0014`（A/open）：43 员落位链闭合到 0x46EB8；含对抗复核更正的 0x11B0/0x25AF0 块/0x45B38/0x45EAC 四处「假洞」与 UIScene 272B 冲突处理。

---

## §8 复现命令

```bash
cd /home/peng/workspace/PAL3Decomp
# 1) 干跑/写入落位（幂等）
python3 data/status/archive/r6_t1_uititle_jdhy_placement_20261126.py        # dry-run
python3 data/status/archive/r6_t1_uititle_jdhy_placement_20261126.py --apply
# 2) 门禁
python3 pipeline/cli.py check
# 3) 全链（约 8 分钟；probe 会因外部 SaleUI 红早停）
python3 pipeline/cli.py loop
python3 tools/regression_detector.py --check --report
python3 pipeline/cli.py match
# 4) 普查
python3 tools/census_struct_holes.py
# 5) 尺寸/唯一分配反证
grep -c "push   \$0x46eb8" /tmp/pal3_full_disasm.txt   # =1（0x4A46B5 指令，NEW 在 0x4A46DE）
grep -c "5c364" /tmp/pal3_full_disasm.txt              # =0
```

---

## §9 边界自证

- 只改 `data/annotations/structs/UITitle_JDHY.json`（+ 新增落位脚本、报告、census 产物）；未碰 SaleUI.json、未碰 `pipeline/ida/`、未跑 `--rebaseline`。
- 基线 `data/status/s4_baseline.json` 未被本卡显式重锚；match 默认刷新 rows 属管线既有行为，`rebaseline` 字段仍是 R2@2026-11-26T14:17:46 的记录。
- 本卡未修改 `methods`/`vtables`/`note`/`bases`/`base_size` 字段；未删除函数注解。
