# R4 施工图：PAL3VisNode 级联 + ScreenEffectMgr 拆类/成员补全

> 卡片：#16（tsk_01M8C57MHSA8FVE53WQY5G）· 只读施工图 · 不跑管线、不改数据
> 证据源：`original/PAL3.exe`、`asm/pal3/ida_structs.json`、`asm/pal3/decomp`、
> `data/status/_disasm_cache.txt`、`data/status/struct_holes_20261125.json`、
> `data/annotations/structs/*.json`、#11/#15 报告。
> 全部读数为本机现场命令产出（§7 可逐条复算）。不引用正在被 #6 重生成的 `pal3/src`。

---

## §0 结论（先看这七条）

1. **拆类裁决：A 保留 `ScreenEffectMgr`（152B = 0x98），B 用行为推导名 `ScreenEffectRingNode`（363,968B）。**
   现注解里名为 `ScreenEffectNode` 的是另一个 1060B 类（注解尺寸 220 偏小，证据见 §1.3.2），**本方案不动它**。
   A 是静态单例（`GetInstance` 0x4BE590 + atexit thunk 0x4BE5D0 → `jmp 0x4BE080` + 实例 0xDE7DF8），
   152B 由 16 个成员精确闭合（末员 `m_nEffectCount`@0x94 +4 = 0x98，与 `binary_size_source` 记的旧值 152 一致）；
   B 由 vis-node 工厂创建（0x4B7121 `push 0x58DC0` → `call 0x4BEE60`），基类 PAL3VisNode（0x4BEE7F `call 0x4B6F70`），
   vtable 0x56F580（15 槽，全为本类方法/adjthunk）。
2. **现 `ScreenEffect` 的 vtable/ctor/dtor 三件归属错**：0x56F508 / 0x4BDFB0 / 0x4BE060 属 A；
   ScreenEffect 真正的 ctor 是 **0x4BDF10**（写 vptr **0x56F4F0**，`[8]=1`，`[4]/[0xC]/[0x10]=0`，`[0x14]=0` 字节），
   24B 成员 `m_nType@8 / m_life@0xC / m_age@0x10 / m_hold@0x14` 恰好就是它写的四个字段 ⇒
   **ScreenEffect 的成员布局是对的，错的是函数与 vtable 的归属**。
3. **0x4BE080 是 complete dtor，不是 `ClearAllEffects`**：入口写 vptr 0x56F508、按成员逆声明序析构
   `+0x50 → +0x38 → +0x20 → +0x4`、释放 0x6C..0x94 分配器块；`0x4BE5D0` 是 atexit thunk（`mov ecx,0xDE7DF8; jmp 0x4BE080`）。
   ⇒ `ClearAllEffects` 与 functions.json 的 `InitScreenEffectSingleton` 都是错名（D-2 见 §6，本卡已定谳）。
4. **B 需新增 3 个前缀成员**（0x5C float 累加量、0x60/0x64 两个资源句柄），其余 0xA4..0x454 现有成员保留。
   洞账分两步：B1（只拆类、不补成员）census **76B** / 严格 96B；B2（补完 3 员）census **64B** / 严格 84B。
   余下的 0x68..0xA4（60B）、0xAC..0xB0（4B）、0x410..0x424（20B）**保持洞**，交后续取证卡命名（见 §5）。
5. **级联是四文件各 1–2 行**：PAL3VisNode `binary_size 88→92` + `m_nState@0x58`；三派生 `base_size 88→92`。
   census 已在 `CEffGroupNode` / `UI3DModelNode` 各自暴露 `[0x58,0x5c,4]` 洞——正是这个 4B 缺口，修复后自动闭合（独立佐证）。
6. **B 的剩余洞不得用 `m_unk_0xNN` 占位**（命名铁律禁伪语义名），列入后续取证卡；
   本卡给出的洞账：0x68..0xA4（60B）、0xAC..0xB0（4B）、0x410..0x424（20B）。
7. **执行顺序 A → B1 → B2**，每阶段独立可回滚；不重锚四份基线，不与 #6 的 QA 复跑并发。

---

## §1 拆类裁决（①）

### 1.1 两个实体的证据矩阵

| 锚点 | A（152B 单例） | B（363,968B 渲染节点） | 证据 |
|---|---|---|---|
| ctor | 0x4BDFB0 | 0x4BEE60 | `asm/pal3/ida_structs.json` methods 键；A 尾 `4be03e mov [esi],0x56f508` |
| dtor | 0x4BE060（deleting）→ 0x4BE080（complete） | 0x4BEF30（deleting）→ 0x4BEF50（complete，现名 `_UIWnd`） | `4be063 call 0x4be080`；`4bef33 call 0x4bef50` |
| vtable | 0x56F508（1 槽：0x4BE060） | 0x56F580（15 槽，含 6 个 adjthunk） | ida_structs `vtables`；`0x56F580` 现归 `ScreenEffectMgr` |
| 实例/生命周期 | 0xDE7DF8 + guard 0xDE7E90；`GetInstance` 0x4BE590；atexit thunk 0x4BE5D0 | 工厂按类型号 new（0x4B7121 `push 0x58DC0`） | `4be5d0 mov ecx,0xde7df8; jmp 0x4be080`；工厂在 0x4B70EB..0x4B71F6 |
| 基类 | 无（CMO 单继承自 PalScriptWaitObj 的是 ScreenEffect，不是 A） | **PAL3VisNode**（0x4BEE7F `call 0x4B6F70`） | ctor 首条实调用 |
| 体量 | 0x98 = 152 | 0x58DC0 = 363,968 | 16 员闭合；`push 0x58DC0` |

### 1.2 为什么 A 不能是 `ScreenEffect`

`ScreenEffect` 现在是 24B、成员 0x8..0x14；而 A 的成员 `m_fadeIn@0x4`（类型 ScreenFadeIn，28B，跨 0x4..0x20）会与
`m_nType@0x8/m_life@0xC/m_age@0x10/m_hold@0x14` **完全重叠**。若把 16 员迁给 ScreenEffect，则
`ScreenFadeIn : ScreenEffect`（现 bases 正确）与「ScreenEffect 内含 ScreenFadeIn 成员」同时成立 ⇒ 循环包含，不可能。

反过来：A = `ScreenEffectMgr`、ScreenEffect 保持 24B 参数基类、ScreenFadeIn/Out/White/White2（28/24/24/24）
作为 A 的四个成员排在 0x4/0x20/0x38/0x50（间距 0x1C/0x18/0x18/0x18 与尺寸逐一吻合），
余下成员一路闭合到 0x98 ⇒ **无矛盾、无需新造名**。

### 1.3 命名与代价

- **A 保留 `ScreenEffectMgr`**：PDB 有 `??1ScreenEffectMgr@@UAE@XZ` / `??_GScreenEffectMgr@@UAEPAXI@Z` /
  `pal3/src/Effect/ScreenEffectMgr.h`；Mgr + 单例 + 分配器/队列，语义自洽。
- **B 取名 `ScreenEffectRingNode`（行为推导名，非 PDB 名）**：B 由 vis-node 工厂创建、PAL3VisNode 派生，
  `LoadResources` 两处调 `GenerateRingMesh(41.0f,28.0f,50.0f,6, base=0xB0, 6)` 与
  `GenerateRingMesh(34.0f,18.0f,68.0f,6, base=0x248, 6)`，各生成 6 片 0x44 的环形网格；另有 1 个 `gbGeomQuad`（4×gbVec3D）
  与就地的 `ParticleEffect@0x454`。name_note 记：**环形网格 2×6 + 单 quad + 粒子**（选择与渲染链见 §2.3 各行 VA）。
  命名铁律允许「体语义推导名 + name_note 证据链」，本名不用 `slot_N/_todo_/m_unk_0xNN` 形态。
- **为什么不让 B 占用 `ScreenEffectNode`（D-1 结论）**：现注解的 `ScreenEffectNode` 是另一个类，其 ctor `0x4B7C30`
  在 `[edi+0xA0]` 置 0、`lea esi,[edi+0xAC]` 起 4×0xC、`lea esi,[edi+0xF0]` 起 12×0x44 直到 **0x420**；
  工厂 0x4B715A 又是 `push 0x424` 再 `call 0x4B7C30` ⇒ 该类真实尺寸 **0x424=1060**，注解的 220 只是「成员只到 0xA8」的
  陈旧值（§7 C9）。若让 B 占用这个 PDB 名，必须同时把该类改挂（候选 `WeatherEffectNode`，PDB 存在但本卡无天气链路证据），
  并把它的 vtable `0x56F450`（14 槽）与 10 个方法整体迁走、尺寸 220→1060 重写——这是一张独立卡的工作量。
- **备选路径（若后续证明该 1060B 类确为 `WeatherEffectNode`）**：则 B 可改用 PDB 名 `ScreenEffectNode`，
  代价＝上一条描述的整套迁移；迁移清单字段与 §4 同构，本卡不展开。
### 1.4 拆类后的方法归属（B 侧迁出，A 侧保留）

- B（迁到 `ScreenEffectRingNode`）：ctor 0x4BEE60、deleting dtor 0x4BEF30、complete dtor 0x4BEF50（现名 `_UIWnd`）、
  LoadResources 0x4BEFB0、CleanupTextures 0x4BF170、Create 0x4BF1C0、Destroy 0x4BF1D0、Render 0x4BF260、
  UpdateAnimation 0x4BF4F0、GetPageIndex 0x4BF680、SetFadeParams 0x4BF6C0、ResetFadeState 0x4BF760、
  ProcessInstance 0x52F310、IsFadeActive 0x52F330；vtable 0x56F580。
- A（保留 `ScreenEffectMgr`）：0x4BDF30（计时累加，现名 `_todo_4BDF30` 须正名）、IsScriptDelNeeded 0x4BDF60、
  StartFade 0x4BDF70、complete dtor 0x4BE080（现名 ClearAllEffects，须改名）、ProcessEffect 0x4BE1A0、
  UpdateFrontEffect 0x4BE4A0、GetInstance 0x4BE590、IsFadeWhiteHolding 0x4BE5E0、DrainQueue 0x4BE5F0、
  AllocEffectBlock 0x4BE6B0、GetFadeFlags 0x4BE810、RenderFadeOut 0x4BE920、ToggleFade 0x4BE9C0、
  StartFadeIn 0x4BE9E0、RenderFadeIn 0x4BEAB0、RenderFadeWhiteOut 0x4BEC00、RenderFadeWhiteIn 0x4BED50、
  ctor 0x4BDFB0、deleting dtor 0x4BE060；vtable 0x56F508。

---

## §2 成员映射表（②）

### 2.1 A（`ScreenEffectMgr`，152B，16 员全部保留原位）

| off | 成员 | 类型 | size | 证据等级 | 依据 |
|---|---|---|---|---|---|
| 0x0 | m_pVtable | void* | 4 | A | ctor 尾写 0x56F508 |
| 0x4 | m_fadeIn | ScreenFadeIn | 28 | A | ctor 0x4BE8D0 构造；ProcessEffect +0x4 虚调用 |
| 0x20 | m_fadeOut | ScreenFadeOut | 24 | A | ctor 0x4BEA60；+0x20 虚调用 |
| 0x38 | m_fadeWhite | ScreenFadeWhite | 24 | A | ctor 0x4BEBB0；+0x38 |
| 0x50 | m_fadeWhite2 | ScreenFadeWhite2 | 24 | A | ctor 0x4BED00；+0x50 |
| 0x68 | m_activeQueue | char[4] | 4 | B | UpdateFrontEffect/ProcessEffect 队列游标（类型待细化） |
| 0x6C–0x7C | 分配器五元组 | void*×5 | 20 | A | ClearAllEffects(D) 释放；AllocEffectBlock 推进 |
| 0x80/0x84 | m_nAllocFlag1/2 | int | 8 | B | 清零/置位点 |
| 0x88 | m_fAllocFactor | int(位面 float) | 4 | B | LoadResources 写 1065353216(1.0f) |
| 0x8C | m_pEffect | char* | 4 | B | 队列块头 |
| 0x90 | —（洞） | — | 4 | — | 无访问点；census 记为洞 |
| 0x94 | m_nEffectCount | int | 4 | A | 0x4BE5E0 `mov eax,[ecx+0x94]; test` |

### 2.2 ScreenEffect（24B，不动成员，仅迁走函数/vtable）

| off | 成员 | 类型 | 依据 |
|---|---|---|---|
| 0x0 | m_pVtable | void* | ctor 0x4BDF10 写 **0x56F4F0** |
| 0x8 | m_nType | int | ctor `[eax+8]=1` |
| 0xC | m_life | int | ctor 清零；0x4BDF30 `fcomp [ecx+0xc]` |
| 0x10 | m_age | float | 0x4BDF30 `fadd/fst [ecx+0x10]` |
| 0x14 | m_hold | BYTE | ctor `[eax+0x14]=cl` |

### 2.3 B（`ScreenEffectRingNode`，363,968B）

| off | 成员 | 类型 | size | 等级 | 依据（VA） |
|---|---|---|---|---|---|
| 0x0 | （基类 PAL3VisNode） | — | 0x5C | A | 0x4BEE7F `call 0x4B6F70` |
| 0x5C | m_fAnimAccum（新增） | float | 4 | A | 0x4BF519 `fadd [edi+0x5c]` / 0x4BF51F `fstp` |
| 0x60 | m_hResLarge（新增） | void* | 4 | A | LoadResources 0x4BF139 `mov [esi+0x60],eax`；Cleanup 0x4BF19B/0x4BF1AA；Render 0x4BF2F4/0x4BF464 |
| 0x64 | m_hResSmall（新增） | void* | 4 | A | LoadResources 0x4BF116；Cleanup 0x4BF18F/0x4BF198；Render 0x4BF326 `lea ebx,[esi+0x64]` |
| 0x68..0xA4 | —（洞 60B） | — | — | — | B 方法域 806 条指令内无 `[reg+0x68..0xA0]` 访问（仅栈槽命中） |
| 0xA4 | m_nGeometryReady | int | 4 | A | ctor 置 0；LoadResources 置 1；Cleanup 清 0 |
| 0xA8 | m_pGeomRenderEffect | gbRenderEffect* | 4 | A | NewRenderEffect 返回值落此；11 处访问 |
| 0xB0 | m_ringQuadsLarge | gbGeomQuad[6] | 0x198 | A | ctor 6×`call 0x401810`，步长 0x44；GenerateRingMesh(41,28,50,6) |
| 0x248 | m_ringQuadsSmall | gbGeomQuad[6] | 0x198 | A | ctor 0x4BEEB7 同型；GenerateRingMesh(34,18,68,6) |
| 0x3E0 | m_singleQuad | gbGeomQuad（4×gbVec3D=48B） | 0x30 | A | ctor 0x4BEED9 循环 4×`call [0x56a56c]`，步长 0xC |
| 0x410..0x424 | —（洞 20B，有访问无名） | — | — | — | 0x410/0x414 清零、0x418/0x41C=1.0f、0x420=0xFFFFFFFF 且按字节写 0x420..0x422；无命名证据 ⇒ 不许 `m_unk_0x410` |
| 0x424 | m_fAnimTime | float | 4 | A | 0x4BF519 累加、0x4BF531 置 4.0f |
| 0x428 | m_fAnimSpeed | float | 4 | A | 0x4BF587 `fstp`；0x4BF3CE 取址传 Render |
| 0x42C | m_aAnimCurve | float[6] | 0x18 | A | 0x4BF593 起三次 `add 8`，cur=0x42C/0x434/0x43C |
| 0x444 | m_aAnimFlags | int[4] | 0x10 | A | 0x4BF53B 写 1；0x4BF58D 起 `add 4` 遍历 |
| 0x454 | m_particleEffect | ParticleEffect | 0x5896C | A | ctor 0x4BEEF2/0x4BEEF8 就地构造；IDB methods 0x004BC760 ctor A 级 |

**洞账（B 侧，两阶段）**：

| 时点 | 成员覆盖 | census 口径洞 | 严格布局洞 |
|---|---|---|---|
| B1 完成（只拆类，未补 3 员） | base 0x5C + 0xA4/0xA8 + 0xB0..0x410 + 0x424..0x454 + 0x454 尾 | **76B**（0x5C..0xA4 72 + 0xAC..0xB0 4） | 96B（再加 0x410..0x424 20） |
| B2 完成（补 0x5C/0x60/0x64） | 同上 + 0x5C/0x60/0x64 | **64B**（0x68..0xA4 60 + 0xAC..0xB0 4） | 84B（再加 0x410..0x424 20） |

余下三段（0x68..0xA4 60B、0xAC..0xB0 4B、0x410..0x424 20B）在 B2 后**仍是洞**，本卡不填：
- 0x68..0xA0：B 方法域 806 条指令内无 `[reg+0x68..0xA0]` 访问（仅栈槽命中），无证据不命名；
- 0xAC..0xB0：同上 4B 对齐空隙；
- 0x410..0x424：有写入（0x410/0x414 清零、0x418/0x41C=1.0f、0x420=0xFFFFFFFF 且按字节写 0x420..0x422），
  但缺读点语义，禁止 `m_unk_0x410` 式占位（命名铁律），留后续卡。
census 与严格口径差额来自 census「未知类型成员按下一成员 offset 兜底」规则（§7 C6 复算），不是矛盾。

---

## §3 PAL3VisNode 级联清单（③）

| 文件 | 字段 | 现值 | 新值 | 说明 |
|---|---|---|---|---|
| `data/annotations/structs/PAL3VisNode.json` | `binary_size` | 88 | **92** | ctor 在 +0x58 写 4B；派生自有首员在 0x5C |
| 同上 | `known_members` | `{}` | 增 `"0x58": {"name":"m_nState","type":"int","evidence_level":"B","source":"..."}` | 值为 0/1/-1；getter 0x4B7020；RenderTargetNode 0x4BD92B/0x4BD997、B 0x4BF39F/0x4BF680 读写 |
| 同上 | `base_size` | 88 | **保持 88** | 语义=直接基类 gbVisNode 的 binary_size（`pipeline/ida/apply_annotations.py:497` 以 `offset >= base_size` 过滤成员；`tools/cascade_plan.py:236` `newbase = 直接基类 binary_size`） |
| `CEffGroupNode.json` | `base_size` | 88 | **92** | sizeof 116 不变（0x5C+6×4） |
| `UI3DModelNode.json` | `base_size` | 88 | **92** | sizeof 248 不变（0x5C+0x9C） |
| `ScreenEffectNode.json`（1060B 类，**不是** B） | `base_size` | 88 | **92** | 阶段 A 只改这一行；该文件尺寸 220→1060 属独立卡（§1.3.2 / C9），本卡不动 |
| `ScreenEffectRingNode.json`（新建，B） | 全文件 | 不存在 | 新建 | 阶段 B1 创建：base PAL3VisNode、binary_size 363,968、vtable 0x56F580、成员见 §2.3；不覆盖 `ScreenEffectNode.json` |
| `RenderTargetNode.json` | — | bases 缺失、`_tail_000 char[96]` | **不动** | 不在级联：IDA 未给 bases，补 bases 属另一张卡（导出缺口 G3） |

**census 佐证**：`CEffGroupNode` / `UI3DModelNode` 现在都有 `["0x58","0x5c",4]` 洞，正是缺失的 `m_nState`；
级联落地后这两个 4B 洞应自动消失（UI3DModelNode 另有一个 `[0xA8,0xE8,64]` 与本卡无关）。

---

## §4 functions.json / vtables.json 迁移清单（④）

> `data/annotations/functions.json` 是**扁平 dict**（键=`"0x00401810"` 形式，243 条），只登记自由函数；
> 类方法在 `structs/<Cls>.json` 的 `methods`。因此下表的「源」= 当前所属 json，「旧条目」=
> 需从源 `methods` 删除的键；`owner` 门（structs merge 按 owner 过滤）要求**先删旧条再写新条**，否则新条被静默丢弃。

| # | VA | 现名 | 现所属 | 目标类 | 删旧条目 | 槽名/改名依据 |
|---|---|---|---|---|---|---|
| 1 | 0x004BDF10 | （缺，现误挂 RenderTarget::Destroy） | RenderTarget.methods | **ScreenEffect（ctor）** | 是 | 写 vptr 0x56F4F0、`[8]=1` ⇒ ScreenEffect ctor |
| 2 | 0x004BDFB0 | ScreenEffect | ScreenEffect | **ScreenEffectMgr（ctor）** | 是 | 尾写 vptr 0x56F508；构造 4 fade + 分配器 |
| 3 | 0x004BE060 | ~ScreenEffect | ScreenEffect | **~ScreenEffectMgr（deleting）** | 是 | 调 0x4BE080 后 `operator delete` |
| 4 | 0x004BE080 | ClearAllEffects | ScreenEffectMgr | **~ScreenEffectMgr（complete）** | 改名 | 入口写 vptr + 逆序析构成员 |
| 5 | 0x004BE5D0 | InitScreenEffectSingleton(自由函数) | functions.json | 改名 `DestroyScreenEffectSingleton` | 改名 | `mov ecx,0xDE7DF8; jmp 0x4BE080`（atexit thunk） |
| 6 | 0x004BEE60 | ScreenEffectMgr | ScreenEffectMgr | **ScreenEffectRingNode（ctor）** | 是 | `push 0x58DC0` 工厂创建；base PAL3VisNode |
| 7 | 0x004BEF30 | ~ScreenEffectMgr | ScreenEffectMgr | **~ScreenEffectRingNode（deleting）** | 是 | 调用 0x4BEF50 后 delete |
| 8 | 0x004BEF50 | _UIWnd | ScreenEffectMgr(+known_methods) | **~ScreenEffectRingNode（complete）** | 是（含 known_methods 条目） | 写 vptr 0x56F580、调 CleanupTextures/ParticleEffect dtor/PAL3VisNode dtor |
| 9 | 0x004BEFB0 | LoadResources | ScreenEffectMgr | ScreenEffectRingNode | 是 | vtable 槽 10 |
| 10 | 0x004BF170 | CleanupTextures | 同上 | ScreenEffectRingNode | 是 | 槽 11 |
| 11 | 0x004BF1C0 | Create | 同上 | ScreenEffectRingNode | 是 | 槽 4 |
| 12 | 0x004BF1D0 | Destroy | 同上 | ScreenEffectRingNode | 是 | 槽 3 |
| 13 | 0x004BF260 | Render | 同上 | ScreenEffectRingNode | 是 | 槽 1 |
| 14 | 0x004BF4F0 | UpdateAnimation | 同上 | ScreenEffectRingNode | 是 | 槽 12 |
| 15 | 0x004BF680 | GetPageIndex | 同上 | ScreenEffectRingNode | 是 | 槽 13 |
| 16 | 0x004BF6C0 | SetFadeParams | 同上 | ScreenEffectRingNode | 是 | 槽 14 |
| 17 | 0x004BF760 | ResetFadeState | 同上 | ScreenEffectRingNode | 是 | 非虚方法，体在 B 区 |
| 18 | 0x0052F310 | ProcessInstance | 同上 | ScreenEffectRingNode（待复核） | **条件**：有 call 点则删旧；无则暂留并标 `pending`（D-4） | 0x52F3xx 独立小块，需 call 点确认后再迁 |
| 19 | 0x0052F330 | IsFadeActive | 同上 | ScreenEffectRingNode（待复核） | **条件**：同上 | 同上 |

**vtable 迁移**：

| vtable | 现归属 | 目标 | 依据 |
|---|---|---|---|
| 0x0056F508（1 槽 0x4BE060） | ScreenEffect.vtables | **ScreenEffectMgr.vtables** | 槽 0 = A 的 deleting dtor |
| 0x0056F4F0（新增登记） | 未登记 | **ScreenEffect.vtables** | ctor 0x4BDF10 写入；ScreenFade* 的 0x56F510/0x56F52C/0x56F548/0x56F564 各自成表（间距 0x1C=6 槽+RTTI） |

> **文件落点**：本仓没有独立的 `vtables.json`——vtable 内嵌在 `data/annotations/structs/<Cls>.json` 的 `vtables` 数组里
> （`pipeline/ida/apply_annotations.py:508-511` 读的就是 `struct_info['vtables']`）。所以「vtable 迁移」= 在对应 structs json 之间移动该数组条目；
> `data/annotations/` 下确有 `functions.json`（扁平 dict），§4 第 5 行的改名落在这里。
| 0x0056F580（15 槽） | ScreenEffectMgr.vtables | **ScreenEffectRingNode.vtables** | ctor 0x4BEE60 写；base 字段现为 `UIRoleDialog`，与「基类 PAL3VisNode」矛盾 ⇒ 同步改 base 字段或留待 B2 复核（D-3） |

**函数名修正（不迁移，仅改名）**：0x004BDF30 现 `_todo_4BDF30`，体为 `fadd [ecx+0x10]; fcomp [ecx+0xc]`（计时累加 +
阈值比较）⇒ 应正名为语义名（候选 `AdvanceAge`，name_note 记该体证据；命名铁律禁 `_todo_`）。

---

## §5 执行顺序（⑤）

前置：确认 #6 不在 QA 复跑窗口（写 `data/status/*` 与 `tests/`，与本卡清单有交叠风险）；确认工作区干净到只剩已知他人产物。

### 阶段 A：PAL3VisNode 级联（4 文件 5 行）

```bash
# A1 改动（4 个 json，字段见 §3）
python pipeline/cli.py apply
python pipeline/cli.py export
python pipeline/cli.py codegen all
python pipeline/cli.py probe
python pipeline/cli.py match
```

- 预期读数（基线=本机实读，§7 C7）：S2 ok **158/229**、fail_own 71（±0）；`match_L1` **189**（±0）；
  `CEffGroupNode.hole_bytes` 4→0、`UI3DModelNode.hole_bytes` 68→64（0x58 洞消失）。
- 停止条件：S2 ok <158 或 match_L1 <189 或 `ScreenEffectMgr`/B 的 hole 变大 ⇒ 立即按 A-rollback 回退。
- A-rollback（只回阶段 A 的 4 个 json）：`git checkout -- data/annotations/structs/PAL3VisNode.json
  data/annotations/structs/CEffGroupNode.json data/annotations/structs/UI3DModelNode.json
  data/annotations/structs/ScreenEffectNode.json` → 重跑 `apply` + `export`。

### 阶段 B1：拆类 + 命名迁移（不补成员）

```bash
python pipeline/cli.py apply && python pipeline/cli.py export
python pipeline/cli.py codegen all && python pipeline/cli.py probe && python pipeline/cli.py match
```

- 内容：**新建** `ScreenEffectRingNode.json`（B：base PAL3VisNode、363,968B、vtable 0x56F580，成员=§2.3 中既有的
  0xA4..0x454；此阶段不加 0x5C/0x60/0x64）；`ScreenEffectMgr.json` 收缩为 A（152B、vtable 0x56F508、16 员）；
  `ScreenEffect.json` 去掉 ctor/dtor/vtable；`ScreenEffectNode.json`（1060B 类）**只保留阶段 A 的 base_size 改动**；
  §4 的 19 条函数迁移 + 4 条改名（落 `functions.json`：owner 迁移 + `InitScreenEffectSingleton`→`DestroyScreenEffectSingleton`）。
- 预期读数：S2 ok 158±0（拆类只动注解归属，不动签名形）；match_L1 189±0；
  `ScreenEffectMgr.hole_bytes` 20→4；B（`ScreenEffectRingNode`）hole **76**（census 口径）/96（严格口径）。
- 停止条件：出现新的 C2011/C2039（类型未定义）或 S2 下降 ⇒ 停；**不得靠加 include 硬解**（先查 `pipeline/gen` 的发抖顺序）。

- **B1-rollback**（新建文件不能 checkout，必须显式删）：
  ```bash
  rm -f data/annotations/structs/ScreenEffectRingNode.json       # B1 新建的未跟踪文件
  git checkout -- data/annotations/structs/ScreenEffectMgr.json \
                  data/annotations/structs/ScreenEffect.json \
                  data/annotations/functions.json
  python pipeline/cli.py apply && python pipeline/cli.py export
  ```
  B1 真正改过的**已跟踪文件只有 3 个**：`ScreenEffectMgr.json`（收缩为 A）、`ScreenEffect.json`（去掉 ctor/dtor/vtable）、
  `functions.json`（§4 第 5 行的 `InitScreenEffectSingleton`→`DestroyScreenEffectSingleton` 及方法 owner 迁移）。
  `ScreenEffectNode.json` **不在回滚清单**——它只在阶段 A 改过 `base_size`，B1 不动它，checkout 会连带撤销级联。
  `PAL3VisNode.json`/`CEffGroupNode.json`/`UI3DModelNode.json` 同属阶段 A 产物，同样不动。
  ⚠️ 禁止 `git clean -fd`/`git stash -u` 之类通配清理：工作区已有他人未跟踪产物（如 `data/annotations/archive/*.json`），会被误删；
  若 #6 正在写 `data/status/` 或 `structs/`，先 `cp` 快照再回滚，避免双方互相覆盖（写域/时窗纪律见 §5 基线纪律与 D-3/D-4）。

### 阶段 B2：补 B 的 3 个前缀成员（洞不清零）

- 内容：§2.3 的 0x5C/0x60/0x64 三员（A 级证据已备）。0x68..0xA4、0xAC..0xB0、0x410..0x424 **保持洞**，
  在 `ScreenEffectRingNode.json` 的 `note` 里写明三段缺口与已排除的候选（不得写 `m_unk_0xNN` 占位）。
- 预期读数：B 的 hole 76→**64**（census 口径）/96→**84**（严格口径）；`ScreenEffectMgr` 4B 不变；match_L1 189±0。
- 注意：本阶段**不追求洞归零**；洞归零需要另开「0x68/0xAC/0x410 三段取证命名」卡（§6 D-8）。
- 停止条件同 B1。
- **B2 前置备份**（`ScreenEffectRingNode.json` 在 B1 才新建，仍是未跟踪文件，checkout 恢复不了）：
  ```bash
  cp data/annotations/structs/ScreenEffectRingNode.json /tmp/ScreenEffectRingNode.b1.json
  ```
- **B2-rollback**（恢复备份，不能 checkout）：
  ```bash
  cp /tmp/ScreenEffectRingNode.b1.json data/annotations/structs/ScreenEffectRingNode.json
  python pipeline/cli.py apply && python pipeline/cli.py export
  ```
  备份只放 `/tmp`、不进仓；B2 只改这一个文件，无需回退 `ScreenEffectMgr.json`。

### 基线纪律

- 全程**不跑 `--rebaseline`、不 `--update-baseline`**；四份基线（`s4_baseline.json`、`s4_diff_detail.json`、
  `compile_baseline.json`、`baselines/latest.json`）保持 2026-11-26 状态。
- 每阶段结束记录 `git status --porcelain` 与四份基线 status 输出（空=未动）。

---

## §6 风险与待决策清单（⑥）

| ID | 事项 | 判定所需证据 | 建议 |
|---|---|---|---|
| D-1 | B 的类名（已定主方案，非阻塞） | 若要让 B 占 PDB 名 `ScreenEffectNode`，需先证明现 1060B 类另有其名（候选 `WeatherEffectNode`） | **主方案**：B=`ScreenEffectRingNode`（name_note 见 §1.3），现 `ScreenEffectNode` 类不动，零迁移；**备选**：B=`ScreenEffectNode` 时须把现类的 vtable 0x56F450 + 10 方法 + 成员整体迁走并改尺寸 220→1060（独立卡） |
| D-2 | 0x4BE080 = complete dtor（已定谳） | 入口写 vptr + 逆序析构 + 分配器释放 + atexit thunk | 已定：改名 `~ScreenEffectMgr`；`InitScreenEffectSingleton`→`DestroyScreenEffectSingleton`；#10/#11/#4 报告中的 `ClearAllEffects` 措辞需勘误（另卡） |
| D-3 | B 的 vtable base 字段现为 `UIRoleDialog` | 槽 2/5..9 是 adjthunk，需确认它是否多继承 | 阶段 B1 先改 base 为 `PAL3VisNode` 观察编译/布局；若报错再挂账 |
| D-4 | functions 归属误挂（0x52F310/0x52F330） | call 点 xref（谁调 ProcessInstance） | 阶段 B1 前跑一次 xref；无调用点则暂留 ScreenEffectMgr 并标 `pending` |
| D-5 | `_ns_udts.h` include 顺序 | codegen 头文件拓扑（`pipeline/gen/stages/emit_headers.py` 的拓扑序） | 拆类新增父子关系前先确认 PAL3VisNode 声明在 ScreenEffectRingNode 之前 |
| D-6 | `sizeof` 断言 | `tools/audit_type_layout.py --only <Cls>` 编译器裁判 | 阶段 A/B 各跑一次；`sizeof(ScreenEffectMgr)==152`、`sizeof(ScreenEffectRingNode)==363968` |
| D-8 | B 的三段洞（0x68..0xA4 60B / 0xAC..0xB0 4B / 0x410..0x424 20B） | 0x68 区段需更宽的跨类扫描（B 方法域内无访问，可能被外部代码或 vtable thunk 触碰）；0x410 区段需读点语义 | 另开「洞段取证命名」卡，禁 `m_unk_0xNN` 占位；本卡只保证洞账数字准确 |
| D-7 | A 类 16 员中 0x68 `m_activeQueue` 类型 | deque 三指针 vs char[4] 的访问形 | 非本卡；留 `char[4]` 并在后续成员细化卡处理 |

---

## §7 复现命令与实测输出

> 全部在本仓根目录执行，只读。

**C1 两实体锚点**

```bash
python3 - <<'PY'
import json
s=json.load(open('asm/pal3/ida_structs.json'))
for c in ('ScreenEffect','ScreenEffectMgr','ScreenEffectNode'):  # 后者是 1060B 类，不是 B
    v=s[c]; print(c, v['size'], [b['name'] for b in (v.get('bases') or [])],
                  [(vt['addr'],len(vt['slots'])) for vt in (v.get('vtables') or [])])
PY
```
实读：`ScreenEffect 24 ['PalScriptWaitObj'] [('0x0056f508',1)]`；`ScreenEffectMgr 363968 [] [('0x0056f580',15)]`；
`ScreenEffectNode 220 ['PAL3VisNode'] [('0x0056f450',14)]`（该 220 是陈旧值，见 C9）。

**C2 三个 ctor 的 vptr 写入**

```bash
grep -nE '^\s*(4bdf10|4bdfb0|4bee60):' data/status/_disasm_cache.txt
grep -nE 'mov\s+DWORD PTR \[(eax|esi)\],0x56f(4f0|508|580)' data/status/_disasm_cache.txt
```
实读：`4bdf17 c7 00 f0 f4 56 00 → [eax]=0x56f4f0`；`4be03e c7 06 08 f5 56 00 → [esi]=0x56f508`；
B 的 ctor 尾由 `4bef01 mov [edi],0x56f580` 落 vptr。

**C3 atexit thunk**

```bash
grep -nA2 -E '^\s*4be5d0:' data/status/_disasm_cache.txt
```
实读：`4be5d0 mov ecx,0xde7df8` / `4be5d5 jmp 0x4be080`。

**C4 0x4BE080 逆序析构**

```bash
grep -nE '^\s*4be1[5-7][0-9a-f]:' data/status/_disasm_cache.txt | grep -E 'lea\s+ecx,\[esi\+0x(50|38|20|4)\]|call'
```
实读：`+0x50 → call 0x4bed40`、`+0x38 → 0x4bebf0`、`+0x20 → 0x4beaa0`、`+0x4 → 0x4be910`（逆声明序）。

**C5 四个 fade ctor 的 vtable**

```bash
for a in 4be8d0 4bea60 4bebb0 4bed00; do grep -A6 -E "^\s*${a}:" data/status/_disasm_cache.txt | grep -E 'call 0x4bdf10|mov\s+DWORD PTR \[esi\],0x56f'; done
```
实读：四个都先 `call 0x4bdf10`（ScreenEffect base ctor），再写 `0x56f510 / 0x56f52c / 0x56f548 / 0x56f564`。

**C6 洞账复算**

```bash
python3 - <<'PY'
A=[(0,4),(4,28),(0x20,24),(0x38,24),(0x50,24),(0x68,4)]+[(o,4) for o in (0x6c,0x70,0x74,0x78,0x7c,0x80,0x84,0x88,0x8c)]+[(0x94,4)]
B=[(0,0x5c),(0x5c,4),(0x60,4),(0x64,4),(0xa4,4),(0xa8,4),(0xb0,0x198),(0x248,0x198),(0x3e0,0x30),
   (0x424,4),(0x428,4),(0x42c,0x18),(0x444,0x10),(0x454,0x58dc0-0x454)]
def gaps(ms,size):
    cur=0; out=[]
    for o,s in sorted(ms):
        if o>cur: out.append((hex(cur),hex(o),o-cur))
        cur=max(cur,o+s)
    if cur<size: out.append((hex(cur),hex(size),size-cur))
    return out
print('A',gaps(A,0x98)); print('B',gaps(B,0x58dc0))
PY
```
实读：`A [('0x90','0x94',4)]`；`B [('0x68','0xa4',60),('0xac','0xb0',4),('0x410','0x424',20)]`。

**C7 census 现状**

```bash
python3 - <<'PY'
import json
h=json.load(open('data/status/struct_holes_20261125.json'))
d={c['cls']:c for c in h['classes']}
for n in ('ScreenEffectMgr','CEffGroupNode','UI3DModelNode','ScreenEffectNode'):  # 末项=1060B 类，B 拆出前挂在它名下
    c=d[n]; print(n,c['size'],c['holes'],c['hole_bytes'])
PY
```
实读：`ScreenEffectMgr 363968 [['0x90','0x94',4],['0x98','0xa4',12],['0xac','0xb0',4]] 20`；
`CEffGroupNode 116 [['0x58','0x5c',4]] 4`；`UI3DModelNode 248 [['0x58','0x5c',4],['0xa8','0xe8',64]] 68`；
`ScreenEffectNode 220 [['0x58','0xa4',76],['0xac','0xdc',48]] 124`（现存类，尺寸 220 陈旧）。

**C8 基线与体量读数（本卡未改动，仅供阶段验收对照）**

```bash
python3 - <<'PY'
import json
cb=json.load(open('data/status/compile_baseline.json'))
pc=json.load(open('data/status/probe_census.json'))
s4=json.load(open('data/status/s4_baseline.json'))
print('s2',pc['s2']['ok'],'/',pc['s2']['total'],'fail_own',pc['s2']['fail_own'])
st=s4['stats']; print('L1',st['match_L1'],'matched',st['matched'],'symbols',st['symbols'])
PY
```
实读：`s2 158 / 229 fail_own 71`；`L1 189 matched 1152 symbols 1262`。

**C9 现 `ScreenEffectNode`（1060B 类）的真实尺寸**

```bash
grep -nE 'push\s+0x424\s*$|call\s+0x4b7c30' data/status/_disasm_cache.txt | sed -n '1,2p'
grep -nE '^\s*4b7c[0-9a-f]{2}:' data/status/_disasm_cache.txt | grep -E 'lea\s+esi,\[edi\+(0xac|0xf0)\]|mov\s+DWORD PTR \[edi\+0xa0\]|call\s+0x401810'
```
实读：`230843: 4b715a push 0x424`、`230852: 4b7179 call 0x4b7c30`（工厂 new 后直调 ctor）；
ctor 内 `lea esi,[edi+0xac]`（4×0xC 循环）、`lea esi,[edi+0xf0]`（12×0x44 循环，0x401810 ArrayCtor）、`[edi+0xa0]=0`，
12×0x44 止于 **0x420** ⇒ 真实尺寸 ≥0x424=1060，注解 220 只覆盖到成员末 0xA8，属陈旧值（本卡不改）。

---

## §8 自检（对照 QA 五条）

1. **拆类裁决有 vtable/ctor/GetInstance/实例地址证据**：§1.1 矩阵 6 行锚点，§7 C1–C3 实读；
   B 用行为推导名 `ScreenEffectRingNode` 且 name_note 写清「两圈环形网格 + 单 quad + 粒子」与对应 VA；
   不占用 PDB 名 `ScreenEffectNode` 的理由与代价写在 §1.3（含 1060B 类的 C9 证据），不硬编。
2. **编辑清单精确到文件与字段**：§2.1/§2.3 成员表（offset/类型/size/等级/VA），§3 五文件字段表（含新建 B 的 json），
   §2.3 洞账按 B1/B2 两阶段给 census 与严格两组数字（76/96 → 64/84），并声明余下三段洞不填。
3. **functions/vtables 迁移逐条列全**：§4 19 条函数（VA/现名/现所属/目标类/删旧/依据）+ 3 条 vtable + 1 条改名。
4. **执行顺序分阶段且有读数/停止条件/回滚**：§5 A/B1/B2 三段，命令、预期 s2 158·L1 189、停止条件；
   三段回滚**分别**写明——A 用 `git checkout` 回 4 个已跟踪 json；B1 用 `rm -f` 删新建的 `ScreenEffectRingNode.json` + checkout **3 个**已跟踪 json（`ScreenEffectMgr.json`/`ScreenEffect.json`/`functions.json`，**不含** `ScreenEffectNode.json`）；
   B2 因为改的是**未跟踪文件**，先用 `cp` 备份到 `/tmp`、失败时 `cp` 恢复（checkout 无法恢复未跟踪文件）；
   并禁止 `git clean -fd` 一类通配清理（会误删他人未跟踪产物）。B1 预期 hole 76/96、B2 预期 64/84（不再声称「洞收口」）；明确不重锚、不同 #6 并发。
5. **只新增本文件**：本卡未跑 apply/export/codegen/probe/match，未改 `data/annotations`、`pal3/src`、`pipeline`、基线。
   提交前 `git status` 里确有多条 `M`（含 `s4_baseline.json`/`s4_diff_detail.json`，mtime 22:41:52；
   `ScreenEffectMgr.json`，mtime 21:56:11），这些是并发管线与其他成员在办卡的产物，**不是本卡动作**——
   本卡唯一新增是 `docs/specs/2026-11-26-r4-fill-change-plan.md`（`??`；本版 436 行，`wc -l` 实读）。
