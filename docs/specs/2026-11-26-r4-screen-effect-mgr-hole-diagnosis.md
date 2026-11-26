# R4 立案：ScreenEffectMgr 355KB 洞区从零诊断

> **已被取代（superseded）**：本稿是 R4 立案历史稿，现行版为 [`data/status/screeneffect_diag_20261126.md`](../../data/status/screeneffect_diag_20261126.md)；其独有事实已在 canonical §7 对账（并入/未合并逐条列明）。保留作历史记录，勿在此新增内容。

- 卡片：`tsk_01M8BVF4T62R0V707HJ7BY`（R4 立案）
- 负责人：玄策（mem_coder）；QA 必检 5 项见 §7
- 基准日期：2026-11-26；census 产物 `data/status/struct_holes_20261125.json`（20:39 重跑，sha256 见 §1）
- 口径：`tools/census_struct_holes.py` v3（对齐感知 + 四修 + vptr 槽豁免 + overlay 孪生单列）

## 0. 结论摘要

| 项 | 结果 |
|---|---|
| 该类洞数 / 洞字节 | 2 处 / 363,820 B（其中 363,816 B 是同一个大洞） |
| 大洞是否「一片未知」 | **不是**。363,816 B 里 **363,800 B（占大洞 99.996%）可给出 A 级落位证据**，剩余 16 B 明确标「无证据」 |
| 最大单块 | `0x454–0x58DC0` = **362,860 B = 内嵌 `ParticleEffect` 实体**（占全洞 99.7%，362,860/363,820） |
| 金表 `binary_size=363968` | **双向核对通过**：堆分配点 `push 0x58DC0` + `probe_heap_alloc_census` + `0x454+362860=0x58DC0` |
| 小洞 `0x90–0x94`（4 B） | **无证据**（仅一处构造期零写，无任何消费点，语义不可知）→ 不落位 |
| 本轮 annotation | **未改任何 annotation**（QA 第 5 项，git 证据见 §7） |
| 未决 | 头区 `0x4–0x94` 的「fade 成员 vs 基类区」归属矛盾（§6），不影响尾区 ParticleEffect 落位 |

**一句话**：这 355 KB 不是散落未知字段，而是「一个 362,860 B 的粒子系统实体 + 约 940 B 的环形网格/四边形/动画状态 + 16 B 真空白」，可按「1 个大锚 + 1 个批 + 1 个逐案」三步施工。

## 1. ① census v3 重跑（可复现）

命令与输出（20:39，重跑前先确认无 `pipeline/cli.py`/`idalib`/`idat` 进程）：

```
$ python3 tools/census_struct_holes.py
-> /home/peng/workspace/PAL3Decomp/data/status/struct_holes_20261125.json
含洞类 201 | 总空洞 1142 处 | 1246 KB (1.22 MB) | unresolved=6 vptr豁免=59
overlay 孪生(单列): tagCpkAudioOvl,tagRoleSlot,tagTeamSlotsBOverlay,FightItemScriptBlock,RoleAttRemarkSkills = 897 KB
  ScreenEffectMgr          size=363968    holes=2      355 KB
```

**复现判据（确定性）**：重跑前 `sha256=8aa80d4df68d34db13e12939ac9e522ab248446f200acd2911998bfa373e095a`（19:06 产物，88,412 B）；20:39 重跑后 **同值同字节**（只有 mtime 变化）⇒ 同一输入下普查输出逐字节稳定，报告数字可被任何人复跑复核。

**并发写入后的第二次重跑（21:03，必须一起读）**：期间其他卡片在 20:52–21:02 修改了 `SaleUI.json`（`members 62→55`，洞 `23→3`，`hole_bytes 44,560→7,684`，−36,876 B），因此 21:03 重跑的全库总数为 **1,122 洞 / 1,239,032 B**（sha256 `512505fab6…`），与 20:39 的 `1,142 洞 / 1,275,908 B` 不同。
**本次比对只差 `SaleUI` 一个类**：对 20:39 与 21:03 两版逐类 diff，唯一变化类是 `SaleUI`，**`ScreenEffectMgr` 条目两版完全相同**（`size=363968, holes=[[0x90,0x94,4],[0x98,0x58dc0,363816]], hole_bytes=363820`）⇒ 本报告的类内结论不受他人并发修改影响，复现时请**以 `ScreenEffectMgr` 条目为准**，不要拿全库总数对照。

该类条目（`classes[]` 原样）：

```json
{"cls":"ScreenEffectMgr","size":363968,"members":16,"bases":0,
 "holes":[["0x90","0x94",4],["0x98","0x58dc0",363816]],
 "hole_bytes":363820,"total_holes":2,"vptr_slot_exempt":true}
```

账目闭合：`4 + 363,816 = 363,820`；`363,968 (binary_size) − 363,820 = 148`，恰好等于已标注的**末端** `0x94 m_nEffectCount(0x94–0x98)` 之前已落位前缀 `0x0–0x90` 的 144 B + 已落 `0x94–0x98` 4 B = 148 B。

> 说明：`--class ScreenEffectMgr` 能只算单类，但**仍会覆盖同一个输出文件**，因此本报告用整体重跑（与官方口径一致），未用 `--class` 偷懒。

## 2. ① 金表 `binary_size=363968` 核对

交接文档 `docs/handoff/2026-11-26-struct-hole-campaign-handoff.md:24` 记载：编译器 sizeof 金表修正 4 类，其中 `ScreenEffectMgr +363816`（旧值 152 → 363968）。三条独立证据：

1. **分配点实读**（工厂 `sub_4B70C0` 的 type 分支表，`jmp *0x4b720c(,%ecx,4)`）：
   - `0x4B7121: push $0x58dc0`（=363,968，**立即数**）
   - `0x4B7126: call 0x55353b`（`operator new` 族）
   - `0x4B7144: call 0x4bee60`（`??0ScreenEffectMgr@@QAE@XZ`）
2. **堆分配普查** `data/status/probe_heap_alloc_census_20261126.json`：
   `{"size": 363968, "ctor": "??0ScreenEffectMgr@@QAE@XZ", "caller": "sub_4B70C0", "site": "0x4b7126"}`
3. **算术闭合**：ctor 在 `0x4BEEF2 lea 0x454(%edi),%ecx` / `0x4BEEF8 call 0x4bc760`（`??0ParticleEffect`）构造内嵌粒子系统；
   `0x454 + 362,860 = 0x58DC0 = 363,968`（`ParticleEffect` 的 362,860 另有独立分配点：`probe_heap_alloc_census` 记 `size 362860, ctor ??0ParticleEffect, site 0x4c8aef`）。

**附带证据（ctor 自设 vtable）**：`0x4BEF01: movl $0x56f580,(%edi)` —— ctor 末尾把 vptr 设为 `ScreenEffectMgr` 注解表 `0x0056f580`（`data/annotations/structs/ScreenEffectMgr.json:556`），与「IDA 符号名 + 工厂尺寸 + 堆普查」三方一致，**类身份本身成立**。

## 3. ② 洞内分解与证据等级

证据等级定义（本卡口径）：**A** = 二进制指令直证（reg+disp32 / 立即数 / 调用目标）；**B** = 3 条以上 A 交叉；**C** = 仅 Hex-Rays 文本或弱写证据；**无证据** = 代码范围内零读写命中。

扫描命令（类代码区间 `0x4bde00–0x4bf800`，含本类全部 31 个方法）：

```
objdump -d --start-address=0x4bde00 --stop-address=0x4bf800 original/PAL3.exe \
  | grep -cE "<偏移>\(%"
```

| 偏移–结束 | 字节 | 判定 | 关键证据（指令 / 生成源行） | 等级 |
|---|---:|---|---|---|
| `0x90–0x94` | 4 | **无证据**：仅一处构造期零写，无任何消费点 | 零写 `0x4BE032: mov %edi,0x90(%esi)`（属 `0x4BDFB0`，即 IDA 命名的 `??0ScreenEffect` 构造体）；全类区间 `0x90(%` 命中数 = **1**（就是这条零写） | **无证据**（C 级写） |
| `0x98–0xA4` | 12 | **无证据**：ctor 不写、全类零读写 | `0x98/0x9c/0xa0(%` 命中数 = **0/0/0** | **无证据** |
| `0xA4` | 4 | `int` 状态位：ctor 置 0；资源装载成功后置 1；销毁路径清零 | ctor `0x4BEE8C: movl $0,0xa4(%edi)`；`LoadResources 0x4BF11B: movl $1,0xa4(%esi)`；`Destroy 0x4BF19E` 清 0；生成源 `pal3/src/Effect/ScreenEffectMgr.cpp:647/736` | **A**（写 + 判读） |
| `0xA8` | 4 | `gbRenderEffect *`：ctor 置 0；`LoadResources` 存 `NewRenderEffect("gfxscript\\Geom_Fx.gbf")`；`Render` 取它 `Begin/Pass/End`；`CleanupTextures` `Release` 后清 0 | ctor `0x4BEF07: movl $0,0xa8(%edi)`；`0x4BF0ED: mov %eax,0xa8(%esi)`；读点 `0x4BF2A2/0x4BF2B0/0x4BF2FF/0x4BF320/0x4BF37E/0x4BF45E/0x4BF4CE`（11 处 `0xa8(%`）；生成源 `:673/729/833/834/894/896` | **A**（写 + 多消费面） |
| `0xAC` | 4 | **无证据** | `0xac(%` 命中数 = 0 | **无证据** |
| `0xB0–0x248` | 408 | `gbGeomQuad[6]`（环 A）：ctor 循环 6 次调用 `gbVec3D` 子构造，指针步进 `add $0x44`（68 = `gbGeomQuad` 尺寸）；`LoadResources` `GenerateRingMesh(41.0,28.0,?,6,ptr,6,3.0)`；`Render` `RenderGeomQuad(ptr,6,…)` | ctor `0x4BEE96 lea 0xb0(%edi),%esi` + `0x4BEEAC call 0x401810`（vec3 ctor）+ `0x4BEEB1 add $0x44,%esi`；`0x4BEFxx` 侧 LoadResources；生成源 `:648/694/846` | **A**（stride 乘法链：6×68=408） |
| `0x248–0x3E0` | 408 | `gbGeomQuad[6]`（环 B）：同构，基址 `0x248`，内径参数 `GenerateRingMesh(34.0,18.0,…)` | ctor `0x4BEEB7 lea 0x248(%edi),%esi`，同样 `add $0x44` ×6；生成源 `:656/695/855` | **A**（6×68=408） |
| `0x3E0–0x424` | 68 | 单个 `gbGeomQuad`：ctor 只构造其 `gbVec3D[4]`（`add $0xc` ×4，到 `0x410`），`color` 在 `0x420`；`Render` 以 `count=1` 画；`LoadResources` 写 `0x3E0..0x423`（含颜色字节 `0x420–0x422`） | ctor `0x4BEEC2–0x4BEEF0` 循环 4 次 `add $0xc`；`Render` `0x4BFxxx RenderGeomQuad((gbGeomQuad*)(&count+211),1,…)`；生成源 `:664/712–728/845/881–886` | **A** |
| `0x424–0x454` | 48 | 动画状态块：`0x424` float 计时（`fVal` 累加、≥4 重置 2.0）、`0x428` float 派生速度、`0x42C–0x444` 6×float（`UpdateAnimation` 三组 stride 8 循环：阈值/进度/速度）、`0x444–0x454` 4×int 标志（`GetPageIndex` 清零 + `UpdateAnimation` 置位） | `UpdateAnimation 0x4BF4F0`：`+228/+229`（=0x424/0x428）、`+230…`（=0x42C 起）、`+236…+239`（=0x444…0x450）、`memset(+228,0,0x20)`；写点计数 `0x424`=7、`0x428`=2、`0x444`=3；生成源 `:918–984、:980` | **A**（消费面读点 + 写） |
| `0x454–0x58DC0` | **362,860** | **内嵌 `ParticleEffect` 实体** | ①分配点走查：ctor `0x4BEEF2 lea 0x454(%edi),%ecx` + `0x4BEEF8 call 0x4bc760`（`ParticleEffect::ParticleEffect`），语料 `asm/pal3/decomp/ParticleEffect_ParticleEffectvoid_004bc760.json`；②算术闭合 `0x454+362860=0x58DC0=363968`；③堆普查 `ParticleEffect size=362860`；④生成源 `:672` | **A（四条独立证据）** |

合计：`4 + 12 + 4 + 4 + 4 + 408 + 408 + 68 + 48 + 362,860 = 363,820` ✓ 与 census `hole_bytes` 一致。

## 4. ③ 落位方案

### 4.1 可闭合段

| 偏移 | 建议类型 / 尺寸 | 建议命名 | 依据 | 备注 |
|---|---|---|---|---|
| `0x454` | `ParticleEffect`（362,860 B，含内部全部子对象） | `m_particleEffect` | 构造调用 + 尺寸算术 + 堆普查（§3 四条） | **单条即可吃掉 99.7% 洞字节**；落位后 `ScreenEffectMgr` 的已知成员覆盖到 `0x58DC0` 末尾 |
| `0xB0` | `gbGeomQuad[6]`（408 B） | `m_ringQuadsA` | ctor 6×68 步进 + GenerateRingMesh 41/28 + Render count 6 | 命名取「环形网格四边形池 A」；如后续确认与内/外环对应可改名 |
| `0x248` | `gbGeomQuad[6]`（408 B） | `m_ringQuadsB` | 同上，参数 34/18 | 与 A 成对（两套环参数） |
| `0x3E0` | `gbGeomQuad`（68 B） | `m_singleQuad` | ctor 只构造 `gbVec3D[4]`、`color@0x420`、Render count 1 | 内部 `color` 已在 `0x420–0x424`，不单列成员 |
| `0x424` | `float` | `m_fAnimTime` | UpdateAnimation 累加、≥4 重置 2.0 | A |
| `0x428` | `float` | `m_fAnimSpeed` | 由 `cos(timer*0.25*pi)` 派生，Render 读 | A |
| `0x42C` | `float[6]` | `m_aAnimCurve` | UpdateAnimation 三组 stride-8 循环（`0x42C/0x434/0x43C` 写入，`0x430/0x438/0x440` 派生速度）；组内三分量语义（阈值/进度/速度）已 A 级，但逐分量命名建议留到专门一轮 | 若要求逐分量，可先落 `float m_aAnimCurve[6]` 一块，避免编造 6 个语义名 |
| `0x444` | `int[4]` | `m_aAnimFlags` | `UpdateAnimation` 置 1、`GetPageIndex` 四连清 0、`+236—+239` 直写 | A |
| `0xA4` | `int` | `m_nGeometryReady`（或 `m_nGeomResourceState`） | ctor 0 / LoadResources 成功后 1 / Destroy 清 0 | 语义「几何资源就绪标志」由三态直证；若嫌推断过强，可保留 `m_nStateA4`？**不建议**——命名铁律禁止伪语义，建议用 `m_bGeomResourceLoaded`（int 承载 bool 形态需注意与 `_DWORD` 写零/写一一致） |
| `0xA8` | `gbRenderEffect *` | `m_pGeomRenderEffect` | 存入 `NewRenderEffect("gfxscript\\Geom_Fx.gbf")`，Render 取用 Begin/Pass/End，Cleanup Release | A |

> 命名口径：`m_unk_<offset>` 只用于「无证据段」的显式留白；上述 A 级段一律给语义名并在 `source` 写证据指针（指令地址 + 生成源行 + 语料文件名）。

### 4.2 不可闭合段（明确「无证据」，不占位、不编造）

| 偏移 | 字节 | 原因 |
|---|---:|---|
| `0x90–0x94` | 4 | 全类唯一访问是 `0x4BE032` 的构造期零写（且在 `0x4BDFB0` 这条 IDA 命名为 `ScreenEffect` 的构造体里，不属于本类 `0x4BEE60` ctor）；**无消费点**，无法判定类型/语义。两选一：①留空（census 继续记洞）②按 `int m_unk_90` 留白并注明「仅构造零写」。本报告建议 **①留空**，避免用占位名掩盖缺口。 |
| `0x98–0xA4` | 12 | ctor 不写、全类区间 `0x98/0x9c/0xa0(%` 命中 0；`operator new` 不清零 ⇒ 语义完全不可知，**留空**。 |
| `0xAC` | 4 | 全类区间 `0xac(%` 命中 0，**留空**。 |

> 覆盖范围声明：以上「零命中」结论的扫描边界是**本类全部方法**（`0x4bde00–0x4bf800`，31 个方法）。成员为私有、消费点应在本类方法内；若有跨类内联访问（例如友元/friend 或宏内联），本扫描会漏，需在实施卡里用 IDA xref 对 `0x90/0x98–0xA4/0xAC` 再做一次全库引用检索确认。

## 5. ④ 下一步实施任务切分

| 卡 | 内容 | 可否批量 | 前置 | 预计产出 |
|---|---|---|---|---|
| **T1 大锚** | 落 `0x454 ParticleEffect m_particleEffect`（362,860 B） | 可批量（单条，机械） | 无（证据已 A） | 洞字节 −362,860（全库 −28.4%） |
| **T2 几何/动画批** | 落 `0xB0/0x248/0x3E0/0x424/0x428/0x42C/0x444/0xA4/0xA8`（合计 940 B） | 可批量（同族、同证据形态） | T1 之后（避免同文件多次改动的门禁重复跑） | 洞字节再 −940 |
| **T3 逐案（前置定谳）** | 头区归属：`0x4–0x94` 的 fade 成员 vs 基类区矛盾 + `0x90/0x98–0xA4/0xAC` 16 B 全库引用检索 | **不可批量**，需 IDA UDT/xref 逐案 | 独立取证卡（见 §6） | 决定这 16 B 是留空还是可落 |
| **旁证升级** | `MXTransport` 同为 363968 且 `0x454` 也已标 `ParticleEffect`，可借 T1 结论把其成员由 `unverified` 升 `verified` | 可批量 | T1 结果 | 提升另一类标注质量 |

施工顺序建议：**T1 → T2 →（并行）T3**；T3 不阻塞 T1/T2（尾区不依赖头区归属）。每张实施卡按战役 spec 过 `check` + `cli.py loop` 门禁；本卡不施工。

## 6. 未决点（如实记录，本卡不裁决）

1. **头区归属矛盾**：`ScreenEffectMgr` 的 `0x4/0x20/0x38/0x50` 标的 `ScreenFadeIn/Out/White/White2` 与 `Render/UpdateAnimation` 里对 `m_fadeWhite2` 的访问相互支持，但 ctor `0x4BEE60` 开头 `0x4BEE7F: call 0x4b6f70` 实际是 `PAL3VisNode::PAL3VisNode()`（其内部 `0x4B6F79: movl $0x56f37c,(%esi)` 设基类 vtable），而注解 `bases` 为空、vtable `base` 写的是 `UIRoleDialog`。基类若是 `PAL3VisNode`（binary_size 88），则 `0x4–0x50` 落在基区内 ⇒ 这些成员归属/偏移至少有一处注解错。**结论：头区成员先不动，交独立取证卡（IDA UDT readback + 构造链）定谳。**
   同一矛盾的另一面：`0x4BDFB0`（IDA 名 `??0ScreenEffect`，`GetInstance 0x4BE590` 用它初始化单例 `0xDE7DF8`）的构造体写到了 `0x90/0x94`，而 `ScreenEffect.binary_size=24` ⇒ `ScreenEffect` 的尺寸或该 ctor 归属二者之一有误（本卡不判）。
2. **`0x90` 的唯一零写来自 `0x4BDFB0` 而非本类 ctor**：这意味着堆上 363,968 B 实例的 `0x90` 在 ctor 路径下**未被初始化**；单例路径则被清零。该差异本身说明头区布局在两个构造路径间不完全一致，支持 §6.1 的定谳需求。
3. 类代码区间内 `0x450(%` 命中 0（该字段只被 `memset(+228,0,0x20)` 与 `+239` 直写覆盖），不影响落位（`int[4]` 块整体证据在 `+236…+239`）。

## 7. ⑤ 本轮边界与 QA 对照（5 项）

- **未改 annotation**：`git status --short` 中无任何 `data/annotations/structs/ScreenEffectMgr.json`（或其他本卡相关 annotation）变更；本轮只写本报告 + `data/status/struct_holes_20261125.json`（census 工具产物，重跑逐字节同值，见 §1）+ 证据台账 2 条（§8）。
- **未跑 loop、未改生成树、未 rebaseline**：本轮无代码/标注变更，不需要跑 `loop`；未触碰任何基线文件。
- 观测到**并发写入**（非本卡）：20:52–21:02 期间其他卡片改了 `data/annotations/structs/RoleStatePanel.json`、`UIFrameContainer.json`（各 +1 行 `base_size`）与 `SaleUI.json`（371+/358−，落位后洞 44,560→7,684 B）；本卡未参与、未修改任何 annotation。这些改动只影响 census 的全库总数（1,142→1,122 洞），`ScreenEffectMgr` 条目逐字节不变（§1）。

| QA 检查项 | 对照 |
|---|---|
| ① census v3 重跑数字与报告一致、洞清单可复现 | §1（命令/输出/重跑同 sha） |
| ② `binary_size=363968` 金表修正已核对 | §2（分配点立即数 + 堆普查 + 算术 + ctor 自设 vtable） |
| ③ 每段洞标证据等级，无证据段未编造命名/类型 | §3 表 + §4.2（三段明确「无证据」并建议留空） |
| ④ 落位方案区分可闭合/不可闭合，命名遵循 `m_unk_<offset>` | §4.1 / §4.2 |
| ⑤ 本轮未改 annotation；若有改动已过 loop 门禁并附输出 | 无改动，见本节 git 证据 |

## 8. 证据台账

| ev id | 主题 | 等级 | 状态 |
|---|---|---|---|
| `ev_0005` | ScreenEffectMgr 0x58DC0 对象 355KB 洞分解（363,800/363,816 B 可闭合，ParticleEffect@0x454） | A | open |
| `ev_0006` | ScreenEffectMgr 头区（0x4–0x94）归属/基链矛盾（PAL3VisNode ctor vs 空 bases；ScreenEffect 24B 与 0x4BDFB0 体矛盾） | B | open |

## 9. 复现命令清单

```bash
cd /home/peng/workspace/PAL3Decomp
# 1) 普查（确定性：同一 annotation 输入下逐字节稳定；若他人改了 annotation，全库总数会变，
#    但本报告只依赖 ScreenEffectMgr 条目——请用下面的单类条目核对）
python3 tools/census_struct_holes.py
python3 -c "import json;d=json.load(open('data/status/struct_holes_20261125.json'));print([e for e in d['classes'] if e['cls']=='ScreenEffectMgr'])"
python3 -c "import json;print(json.load(open('data/status/struct_holes_20261125.json'))['_meta']['total_holes'])"
# 20:39 全库 1142 洞/1,275,908B（当时 sha 8aa80d4d…，与 19:06 产物同值）；
# 21:03 因他人改 SaleUI 后为 1122 洞/1,239,032B（sha 512505fa…），ScreenEffectMgr 条目两版相同。

# 2) 金表：分配点 / 工厂 / ctor 自设 vtable
objdump -d --start-address=0x4b70c0 --stop-address=0x4b7180 original/PAL3.exe
objdump -d --start-address=0x4bde00 --stop-address=0x4bf800 original/PAL3.exe | grep -E "0x(90|98|9c|a0|a4|a8|ac)\(%"

# 3) 洞内关键指令
objdump -d --start-address=0x4bee60 --stop-address=0x4bef30 original/PAL3.exe   # ctor：0xA4/环A/环B/单quad/动画块/0x454 ParticleEffect/vtable
objdump -d --start-address=0x4befb0 --stop-address=0x4bf170 original/PAL3.exe   # LoadResources：环网格/0xA4=1/0xA8=NewRenderEffect
objdump -d --start-address=0x4bf260 --stop-address=0x4bf4f0 original/PAL3.exe   # Render：0xA8 Begin/Pass/End、三处 RenderGeomQuad
objdump -d --start-address=0x4bf4f0 --stop-address=0x4bf680 original/PAL3.exe   # UpdateAnimation：0x424/0x428/0x42C…/0x444…
objdump -d --start-address=0x4be590 --stop-address=0x4be5f0 original/PAL3.exe   # GetInstance → 0x4BDFB0 单例初始化

# 4) 交叉件
python3 -c "import json;d=json.load(open('data/status/probe_heap_alloc_census_20261126.json'));print([a for a in d['allocs'] if a['size'] in (363968,362860)])"
sed -n '636,760p' pal3/src/Effect/ScreenEffectMgr.cpp     # 生成源：ctor + LoadResources
sed -n '807,900p' pal3/src/Effect/ScreenEffectMgr.cpp     # Render
sed -n '900,1000p' pal3/src/Effect/ScreenEffectMgr.cpp    # UpdateAnimation / GetPageIndex
```
